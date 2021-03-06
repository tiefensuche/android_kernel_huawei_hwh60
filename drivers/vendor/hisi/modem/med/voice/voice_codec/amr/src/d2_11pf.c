/*
********************************************************************************
*
*      GSM AMR-NB speech codec   R98   Version 7.6.0   December 12, 2001
*                                R99   Version 3.3.0
*                                REL-4 Version 4.1.0
*
********************************************************************************
*
*      File             : d2_11pf.c
*      Purpose          : Algebraic codebook decoder
*
********************************************************************************
*/

/*
********************************************************************************
*                         MODULE INCLUDE FILE AND VERSION ID
********************************************************************************
*/
#include "d2_11pf.h"

/*
********************************************************************************
*                         INCLUDE FILES
********************************************************************************
*/
#include "codec_op_etsi.h"
#include "codec_op_vec.h"
#include "cnst.h"

/*
********************************************************************************
*                         LOCAL VARIABLES AND TABLES
********************************************************************************
*/
#define NB_PULSE 2           /* number of pulses */

/*
********************************************************************************
*                         PUBLIC PROGRAM CODE
********************************************************************************
*/
/*************************************************************************
 *
 *  FUNCTION:  decode_2i40_11bits (decod_ACELP())
 *
 *  PURPOSE:   Algebraic codebook decoder
 *
 *************************************************************************/

void decode_2i40_11bits(
    Word16 sign,   /* i : signs of 2 pulses.                       */
    Word16 index,  /* i : Positions of the 2 pulses.               */
    Word16 cod[]   /* o : algebraic (fixed) codebook excitation    */
)
{
    Word16 i, j;
    Word16 pos[NB_PULSE];

    /* Decode the positions */

    j = index & 1;
    index = shr(index, 1);
    i = index & 7;

    i = add(i, shl(i, 2));        /* pos0 =i*5+1+j*2 */
    i = add(i, 1);
    j = shl(j, 1);
    pos[0] = add(i, j);

    index = shr(index, 3);
    j = index & 3;
    index = shr(index, 2);
    i = index & 7;

	if ( 3 == j)
    {
       i = add(i, shl(i, 2));        /* pos1 =i*5+4 */
       pos[1] = add(i, 4);
    }
    else
    {
       i = add(i, shl(i, 2));        /* pos1 =i*5+j */
       pos[1] = add(i, j);
    }

    /* decode the signs  and build the codeword */
    CODEC_OpVecSet(&cod[0], L_SUBFR, 0);

    for (j = 0; j < NB_PULSE; j++) {
        i = sign & 1;
        sign = shr(sign, 1);

        if (i != 0) {
            cod[pos[j]] = 8191;                           /* +1.0 */
        } else {
            cod[pos[j]] = -8192;                          /* -1.0 */
        }
    }

    return;
}
