/*************************************************************************
*   ��Ȩ����(C) 1987-2011, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  DrvInterface.h
*
*   ��    �� :  yangzhi
*
*   ��    �� :  ���ļ�����Ϊ"DrvInterface.h", ����V7R1������Э��ջ֮���API�ӿ�ͳ��
*
*   �޸ļ�¼ :  2011��1��18��  v1.00  yangzhi����
*************************************************************************/

#ifndef __DRV_UDI_H__
#define __DRV_UDI_H__

#include "drv_comm.h"
#include "acm_cmd.h"

/*************************UDI START***********************************/

/**************************************************************************
  �궨��
**************************************************************************/
#define UDI_INVALID_HANDLE     (-1)

#define UDI_CAPA_BLOCK_READ    ((BSP_U32)(1<<0)) /* ���豸��read�ӿ�Ϊ�����ӿ� */
#define UDI_CAPA_BLOCK_WRITE   ((BSP_U32)(1<<1)) /* ���豸��write�ӿ�Ϊ�����ӿ� */
#define UDI_CAPA_READ_CB       ((BSP_U32)(1<<2)) /* ���豸֧��read �ص����� */
#define UDI_CAPA_WRITE_CB      ((BSP_U32)(1<<3)) /* ���豸֧��write �ص����� */
#define UDI_CAPA_BUFFER_LIST   ((BSP_U32)(1<<4)) /* ���豸�Ķ�дbufferΪ�ڴ������ṹ(Ĭ��Ϊ��ͨ�ڴ��) */
#define UDI_CAPA_CTRL_OPT      ((BSP_U32)(1<<5)) /* ���豸֧�ֿ��Ʋ��� */

#define MIN_UDI_HANDLE     0x5a0000
#define MAX_UDI_HANDLE     0x5a003f

/**************************************************************************
  �ṹ����
**************************************************************************/
#define UDI_BUILD_DEV_ID(dev, type) (((BSP_U32)(dev) << 8) | ((BSP_U32)(type) & 0x00ff))
#define UDI_BUILD_CMD_ID(dev, cmd) (((BSP_U32)(dev) << 8) | ((BSP_U32)(cmd) & 0xffff))


/* ���豸���� */
typedef enum tagUDI_DEVICE_MAIN_ID
{
    UDI_DEV_USB_ACM = 0,
    UDI_DEV_USB_NCM,
    UDI_DEV_ICC,
    UDI_DEV_UART,
    UDI_DEV_HSUART,
    UDI_DEV_MAX                 /* ���������, ���ڱ߽�ֵ */
}UDI_DEVICE_MAIN_ID;

/* ���豸���Ͷ���(Ҫ�� usb ���豸��̬ͳһ����) */
/* ACM */
typedef enum tagUDI_ACM_DEV_TYPE
{
    UDI_USB_ACM_CTRL,
    UDI_USB_ACM_AT,
    UDI_USB_ACM_SHELL,
    UDI_USB_ACM_LTE_DIAG,
    UDI_USB_ACM_OM,
    UDI_USB_ACM_MODEM,
    UDI_USB_ACM_GPS,      /*HISO*/
    UDI_USB_ACM_3G_GPS,   /*ashell*/
    UDI_USB_ACM_3G_PCVOICE, /*Ԥ��*/
    UDI_USB_ACM_PCVOICE,    /*Ԥ��*/
    /*UDI_USB_ACM_3G_AT,    //3G AT*/
    /*UDI_USB_ACM_3G_MODEM, //3G PPP*/
    UDI_USB_HSIC_ACM0,
    UDI_USB_HSIC_ACM1,
    UDI_USB_HSIC_ACM2,
    UDI_USB_HSIC_ACM3,
    UDI_USB_HSIC_ACM4,
    UDI_USB_HSIC_ACM5,
    UDI_USB_HSIC_ACM6,
    UDI_USB_HSIC_ACM7,
    UDI_USB_HSIC_ACM8,
    UDI_USB_HSIC_ACM9,
    UDI_USB_HSIC_ACM10,
    UDI_USB_HSIC_ACM11,
    UDI_USB_HSIC_ACM12,
    UDI_USB_HSIC_ACM13,
	UDI_USB_HSIC_ACM14,
	UDI_USB_HSIC_MODEM0,
    UDI_USB_ACM_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_ACM_DEV_TYPE;

/* NCM */
typedef enum tagUDI_NCM_DEV_TYPE
{
    UDI_USB_NCM_NDIS,
    UDI_USB_NCM_CTRL,
    UDI_USB_NCM_NDIS1,
    UDI_USB_NCM_CTRL1,
	UDI_USB_NCM_NDIS2,
	UDI_USB_NCM_CTRL2,
	UDI_USB_NCM_NDIS3,
	UDI_USB_NCM_CTRL3,
    UDI_USB_NCM_BOTTOM,
    UDI_USB_HSIC_NCM0,
    UDI_USB_HSIC_NCM1,
    UDI_USB_HSIC_NCM2,

    UDI_USB_NCM_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_NCM_DEV_TYPE;

/* ICC */
typedef enum tagUDI_ICC_DEV_TYPE
{
    UDI_ICC_GUOM0 = 3,
    UDI_ICC_GUOM1,
    UDI_ICC_GUOM2,
    UDI_ICC_GUOM3,
    UDI_ICC_GUOM4,

    UDI_ICC_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_ICC_DEV_TYPE;


/* �豸ID�Ŷ��� */
typedef enum tagUDI_DEVICE_ID
{
    /* USB ACM */
    UDI_ACM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_CTRL),
    UDI_ACM_AT_ID =    UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_AT),
    UDI_ACM_SHELL_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_SHELL),
    UDI_ACM_LTE_DIAG_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_LTE_DIAG),
    UDI_ACM_OM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_OM),
    UDI_ACM_MODEM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_MODEM),
    UDI_ACM_GPS_ID      = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_GPS),     /*HISO*/
    UDI_ACM_3G_GPS_ID   = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_GPS),  /*ashell*/
    UDI_ACM_3G_PCVOICE_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_PCVOICE), /*Ԥ��*/
    UDI_ACM_PCVOICE_ID    = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_PCVOICE),    /*Ԥ��*/
    /*UDI_ACM_3G_AT_ID      = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_AT),    //3G AT*/
    /*UDI_ACM_3G_MODEM_ID   = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_MODEM), //3G PPP*/
    UDI_ACM_HSIC_ACM0_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM0),
    UDI_ACM_HSIC_ACM1_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM1),
    UDI_ACM_HSIC_ACM2_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM2),
    UDI_ACM_HSIC_ACM3_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM3),
    UDI_ACM_HSIC_ACM4_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM4),
    UDI_ACM_HSIC_ACM5_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM5),
    UDI_ACM_HSIC_ACM6_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM6),
    UDI_ACM_HSIC_ACM7_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM7),
    UDI_ACM_HSIC_ACM8_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM8),
    UDI_ACM_HSIC_ACM9_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM9),
    UDI_ACM_HSIC_ACM10_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM10),
    UDI_ACM_HSIC_ACM11_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM11),
    UDI_ACM_HSIC_ACM12_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM12),
    UDI_ACM_HSIC_ACM13_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM13),
	UDI_ACM_HSIC_ACM14_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_ACM14),
	UDI_ACM_HSIC_MODEM0_ID=UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_HSIC_MODEM0),

    /* USB NCM */
    UDI_NCM_NDIS_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_NDIS),
    UDI_NCM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_CTRL),
    UDI_NCM_NDIS1_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_NDIS1),
    UDI_NCM_CTRL1_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_CTRL1),
	UDI_NCM_NDIS2_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_NDIS2),
	UDI_NCM_CTRL2_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_CTRL2),
	UDI_NCM_NDIS3_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_NDIS3),
	UDI_NCM_CTRL3_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_CTRL3),
    UDI_NCM_HSIC_NCM0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM0),
    UDI_NCM_HSIC_NCM1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM1),
    UDI_NCM_HSIC_NCM2_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_HSIC_NCM2),

    /* UART */
    UDI_UART_0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_UART, 0),
    UDI_UART_1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_UART, 1),

    /* HSUART */
    UDI_HSUART_0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_HSUART, 0),
    UDI_HSUART_1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_HSUART, 1),

    /* ICC */
    UDI_ICC_IFC_ID  =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 0),
    UDI_ICC_IPM_ID  =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 1),
    UDI_ICC_LMSP_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, 2),

    UDI_ICC_GUOM0_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM0),
    UDI_ICC_GUOM1_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM1),
    UDI_ICC_GUOM2_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM2),
    UDI_ICC_GUOM3_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM3),
    UDI_ICC_GUOM4_ID =  UDI_BUILD_DEV_ID(UDI_DEV_ICC, UDI_ICC_GUOM4),

    /* MUST BE LAST */
    UDI_INVAL_DEV_ID = 0xFFFF
} UDI_DEVICE_ID;


/* �豸�Ĵ򿪲��� */
typedef struct tagUDI_OPEN_PARAM
{
    UDI_DEVICE_ID devid;                        /* �豸ID */
    void   *pPrivate;                            /* ģ�����е����� */
} UDI_OPEN_PARAM;


/**************************************************************************
  ��������
**************************************************************************/
/*****************************************************************************
* �� �� ��  : udi_get_capability
*
* ��������  : �����豸ID��ȡ��ǰ�豸֧�ֵ�����
*
* �������  : devId: �豸ID
* �������  : ��
* �� �� ֵ  : ֧�ֵ�����ֵ
*****************************************************************************/
BSP_S32 udi_get_capability(UDI_DEVICE_ID devId);

/*****************************************************************************
* �� �� ��  : udi_open
*
* ��������  : ���豸(����ͨ��)
*
* �������  : pParam: �豸�Ĵ����ò���
* �������  : ��
* �� �� ֵ  : -1:ʧ�� / ����:�ɹ�
*****************************************************************************/
UDI_HANDLE udi_open(UDI_OPEN_PARAM *pParam);
#define DRV_UDI_OPEN(pParam)    udi_open(pParam)

/*****************************************************************************
* �� �� ��  : udi_close
*
* ��������  : �ر��豸(����ͨ��)
*
* �������  : handle: �豸��handle
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_close(UDI_HANDLE handle);
#define DRV_UDI_CLOSE(handle)    udi_close(handle)

/*****************************************************************************
* �� �� ��  : udi_write
*
* ��������  : ����д
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ���������
*             u32Size: ����д�ߴ� �� �ڴ���������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_write(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);
#define  DRV_UDI_WRITE(handle,pMemObj,u32Size)     udi_write (handle,pMemObj,u32Size)

/*****************************************************************************
* �� �� ��  : udi_read
*
* ��������  : ���ݶ�
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ���������
*             u32Size: ���ݶ��ߴ� �� �ڴ���������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_read(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);
#define DRV_UDI_READ(handle,pMemObj,u32Size)  udi_read(handle,pMemObj,u32Size)

/*****************************************************************************
* �� �� ��  : udi_ioctl
*
* ��������  : ����ͨ����������
*
* �������  : handle: �豸��handle
*             u32Cmd: IOCTL������
*             pParam: ��������
* �������  :
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_ioctl(UDI_HANDLE handle, BSP_U32 u32Cmd, BSP_VOID* pParam);
#define DRV_UDI_IOCTL(handle,u32Cmd,pParam)    udi_ioctl(handle,u32Cmd,pParam)

/*************************UDI END*************************************/

#endif
