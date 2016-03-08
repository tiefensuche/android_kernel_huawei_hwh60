/*******************************************************************
* (c) Copyright 2011-2012 Discretix Technologies Ltd.              *
* This software is protected by copyright, international           *
* treaties and patents, and distributed under multiple licenses.   *
* Any use of this Software as part of the Discretix CryptoCell or  *
* Packet Engine products requires a commercial license.            *
* Copies of this Software that are distributed with the Discretix  *
* CryptoCell or Packet Engine product drivers, may be used in      *
* accordance with a commercial license, or at the user's option,   *
* used and redistributed under the terms and conditions of the GNU *
* General Public License ("GPL") version 2, as published by the    *
* Free Software Foundation.                                        *
* This program is distributed in the hope that it will be useful,  *
* but WITHOUT ANY LIABILITY AND WARRANTY; without even the implied *
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. *
* See the GNU General Public License version 2 for more details.   *
* You should have received a copy of the GNU General Public        *
* License version 2 along with this Software; if not, please write *
* to the Free Software Foundation, Inc., 59 Temple Place - Suite   *
* 330, Boston, MA 02111-1307, USA.                                 *
* Any copy or reproduction of this Software, as permitted under    *
* the GNU General Public License version 2, must include this      *
* Copyright Notice as well as any other notices provided under     *
* the said license.                                                *
********************************************************************/

#include <linux/platform_device.h>
#include <crypto/ctr.h>
#include "dx_config.h"
#include "dx_driver.h"
#include "dx_ivgen.h"
#include "dx_request_mgr.h"
#include "dx_sram_mgr.h"

/* The max. size of pool *MUST* be <= SRAM total size */
#define DX_IVPOOL_SIZE 1024
/* The first 32B fraction of pool are dedicated to the
   next encryption "key" & "IV" for pool regeneration */
#define DX_IVPOOL_META_SIZE (SEP_AES_IV_SIZE + AES_KEYSIZE_128)


/**
 * struct dx_ivgen_ctx -IV pool generation context
 * @pool:          the start address of the iv-pool resides in internal RAM
 * @ctr_key_dma:   address of pool's encryption key material in internal RAM
 * @ctr_iv_dma:    address of pool's counter iv in internal RAM
 * @next_iv_ofs:   the offset to the next available IV in pool
 * @pool_meta:     virt. address of the initial enc. key/IV
 * @pool_meta_dma: phys. address of the initial enc. key/IV
 */
struct dx_ivgen_ctx {
	uint32_t pool;
	uint32_t ctr_key;
	uint32_t ctr_iv;
	uint32_t next_iv_ofs;
	uint8_t *pool_meta;
	dma_addr_t pool_meta_dma;
};

/*!
 * Generates DX_IVPOOL_SIZE of random bytes by
 * encrypting 0's using AES128-CTR.
 *
 * \param ivgen iv-pool context
 * \param iv_seq IN/OUT array to the descriptors sequence
 * \param iv_seq_len IN/OUT pointer to the sequence length
 */
static void dx_ivgen_generate_pool(
	struct dx_ivgen_ctx *ivgen_ctx,
	HwDesc_s iv_seq[],
	unsigned int *iv_seq_len)
{
	unsigned int idx = *iv_seq_len;

	/* Setup key */
	HW_DESC_INIT(&iv_seq[idx]);
	HW_DESC_SET_DIN_SRAM(&iv_seq[idx], ivgen_ctx->ctr_key, AES_KEYSIZE_128);
	HW_DESC_SET_SETUP_MODE(&iv_seq[idx], SETUP_LOAD_KEY0);
	HW_DESC_SET_CIPHER_CONFIG0(&iv_seq[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_FLOW_MODE(&iv_seq[idx], S_DIN_to_AES);
	HW_DESC_SET_KEY_SIZE_AES(&iv_seq[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_CIPHER_MODE(&iv_seq[idx], SEP_CIPHER_CTR);
	idx++;

	/* Setup cipher state */
	HW_DESC_INIT(&iv_seq[idx]);
	HW_DESC_SET_DIN_SRAM(&iv_seq[idx], ivgen_ctx->ctr_iv, SEP_AES_IV_SIZE);
	HW_DESC_SET_CIPHER_CONFIG0(&iv_seq[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	HW_DESC_SET_FLOW_MODE(&iv_seq[idx], S_DIN_to_AES);
	HW_DESC_SET_SETUP_MODE(&iv_seq[idx], SETUP_LOAD_STATE1);
	HW_DESC_SET_KEY_SIZE_AES(&iv_seq[idx], SEP_AES_128_BIT_KEY_SIZE);
	HW_DESC_SET_CIPHER_MODE(&iv_seq[idx], SEP_CIPHER_CTR);
	idx++;

	/* Perform dummy encrypt to skip first block */
	HW_DESC_INIT(&iv_seq[idx]);
	HW_DESC_SET_DIN_CONST(&iv_seq[idx], 0, SEP_AES_IV_SIZE);
	HW_DESC_SET_DOUT_SRAM(&iv_seq[idx], ivgen_ctx->pool, SEP_AES_IV_SIZE);
	HW_DESC_SET_FLOW_MODE(&iv_seq[idx], DIN_AES_DOUT);
	idx++;

	/* Generate IV pool */
	HW_DESC_INIT(&iv_seq[idx]);
	HW_DESC_SET_DIN_CONST(&iv_seq[idx], 0, DX_IVPOOL_SIZE);
	HW_DESC_SET_DOUT_SRAM(&iv_seq[idx], ivgen_ctx->pool, DX_IVPOOL_SIZE);
	HW_DESC_SET_FLOW_MODE(&iv_seq[idx], DIN_AES_DOUT);
	idx++;

	*iv_seq_len = idx; /* Update sequence length */

	/* queue ordering assures pool readiness */
	ivgen_ctx->next_iv_ofs = DX_IVPOOL_META_SIZE;
}

/*!
 * Generates the initial pool in SRAM.
 * This function should be invoked when resuming DX driver.
 *
 * \param drvdata
 *
 * \return int Zero for success, negative value otherwise.
 */
int dx_ivgen_init_sram_pool(struct dx_drvdata *drvdata)
{
	struct dx_ivgen_ctx *ivgen_ctx = drvdata->ivgen_handle;
	HwDesc_s iv_seq[DX_IVPOOL_SEQ_LEN];
	struct dx_crypto_req dx_req = {0};
	unsigned int iv_seq_len = 0;

	/* Generate initial enc. key/iv */
	get_random_bytes(ivgen_ctx->pool_meta, DX_IVPOOL_META_SIZE);

	/* The first 32B reserved for the enc. Key/IV */
	ivgen_ctx->ctr_key = ivgen_ctx->pool;
	ivgen_ctx->ctr_iv = ivgen_ctx->pool + AES_KEYSIZE_128;

	/* Copy initial enc. key and IV to SRAM at a single descriptor */
	HW_DESC_INIT(&iv_seq[iv_seq_len]);
	HW_DESC_SET_DIN_TYPE(&iv_seq[iv_seq_len], DMA_DLLI,
		ivgen_ctx->pool_meta_dma, DX_IVPOOL_META_SIZE,
		AXI_ID, NS_BIT);
	HW_DESC_SET_DOUT_SRAM(&iv_seq[iv_seq_len], ivgen_ctx->pool,
		DX_IVPOOL_META_SIZE);
	HW_DESC_SET_FLOW_MODE(&iv_seq[iv_seq_len], BYPASS);
	iv_seq_len++;

	/* Generate initial pool */
	dx_ivgen_generate_pool(ivgen_ctx, iv_seq, &iv_seq_len);

	/* Fire-and-forget */
	return send_request(drvdata, &dx_req, iv_seq, iv_seq_len, 0);
}

/*!
 * Free iv-pool and ivgen context.
 *
 * \param drvdata
 */
void dx_ivgen_fini(struct dx_drvdata *drvdata)
{
	struct dx_ivgen_ctx *ivgen_ctx = drvdata->ivgen_handle;
	struct device *device = &(drvdata->plat_dev->dev);

	if (ivgen_ctx == NULL)
		return;

	if (ivgen_ctx->pool_meta != NULL) {
		memset(ivgen_ctx->pool_meta, 0, DX_IVPOOL_META_SIZE);
		dma_free_coherent(device, DX_IVPOOL_META_SIZE,
			ivgen_ctx->pool_meta, ivgen_ctx->pool_meta_dma);
	}

	ivgen_ctx->pool = -1;

	/* release "this" context */
	kfree(ivgen_ctx);
}

/*!
 * Allocates iv-pool and maps resources.
 * This function generates the first IV pool.
 *
 * \param drvdata Driver's private context
 *
 * \return int Zero for success, negative value otherwise.
 */
int dx_ivgen_init(struct dx_drvdata *drvdata)
{
	struct dx_ivgen_ctx *ivgen_ctx;
	struct device *device = &drvdata->plat_dev->dev;
	int rc;

	/* Allocate "this" context */
	drvdata->ivgen_handle = kzalloc(sizeof(struct dx_ivgen_ctx), GFP_KERNEL);
	if (!drvdata->ivgen_handle) {
		DX_LOG_ERR("Not enough memory to allocate IVGEN context(%d)\n",
			sizeof(struct dx_ivgen_ctx));
		rc = -ENOMEM;
		goto out;
	}
	ivgen_ctx = drvdata->ivgen_handle;

	/* Allocate pool's header for intial enc. key/IV */
	ivgen_ctx->pool_meta = dma_alloc_coherent(device, DX_IVPOOL_META_SIZE,
			&ivgen_ctx->pool_meta_dma, GFP_KERNEL);
	if (!ivgen_ctx->pool_meta) {
		DX_LOG_ERR("Not enough memory to allocate DMA(%d)\n",
			DX_IVPOOL_META_SIZE);
		rc = -ENOMEM;
		goto out;
	}

	/* Allocate IV pool in SRAM */
	ivgen_ctx->pool = (uint32_t)dx_sram_mgr_alloc(drvdata, DX_IVPOOL_SIZE);
	if (!ivgen_ctx->pool) {
		DX_LOG_ERR("SRAM pool exhausted\n");
		rc = -ENOMEM;
		goto out;
	}

	return dx_ivgen_init_sram_pool(drvdata);

out:
	dx_ivgen_fini(drvdata);
	return rc;
}

/*!
 * Acquires 16 Bytes IV from the iv-pool
 *
 * \param drvdata Driver private context
 * \param iv_out_dma The phys. IV out address
 * \param iv_out_size May be 8 or 16 bytes long
 * \param iv_seq IN/OUT array to the descriptors sequence
 * \param iv_seq_len IN/OUT pointer to the sequence length
 *
 * \return int Zero for success, negative value otherwise.
 */
int dx_ivgen_getiv(
	struct dx_drvdata *drvdata,
	dma_addr_t iv_out_dma,
	unsigned int iv_out_size,
	HwDesc_s iv_seq[],
	unsigned int *iv_seq_len)
{
	struct dx_ivgen_ctx *ivgen_ctx = drvdata->ivgen_handle;
	unsigned int idx = *iv_seq_len;

	if ((iv_out_size != SEP_AES_IV_SIZE) &&
	    (iv_out_size != CTR_RFC3686_IV_SIZE)) {
		return -EINVAL;
	}

	/* Acquire IV from pool */
	HW_DESC_INIT(&iv_seq[idx]);
	HW_DESC_SET_DIN_SRAM(&iv_seq[idx],
		ivgen_ctx->pool + ivgen_ctx->next_iv_ofs,
		iv_out_size);
	HW_DESC_SET_DOUT_DLLI(&iv_seq[idx], iv_out_dma,
		iv_out_size, AXI_ID, NS_BIT, 0);
	HW_DESC_SET_FLOW_MODE(&iv_seq[idx], BYPASS);
	idx++;

	/* Bypass operation is proceeded by crypto sequence, hence must
	*  assure bypass-write-transaction by a memory barrier */
	HW_DESC_INIT(&iv_seq[idx]);
	HW_DESC_SET_DIN_NO_DMA(&iv_seq[idx], 0, 0xfffff0);
	HW_DESC_SET_DOUT_NO_DMA(&iv_seq[idx], 0, 0, 1);
	idx++;

	*iv_seq_len = idx; /* update seq length */

	/* Update iv index */
	ivgen_ctx->next_iv_ofs += iv_out_size;

	if ((DX_IVPOOL_SIZE - ivgen_ctx->next_iv_ofs) < SEP_AES_IV_SIZE) {
		DX_LOG_DEBUG("Pool exhausted, regenerating iv-pool\n");
		/* pool is drained -regenerate it! */
		dx_ivgen_generate_pool(ivgen_ctx, iv_seq, iv_seq_len);
	}

	return 0;
}