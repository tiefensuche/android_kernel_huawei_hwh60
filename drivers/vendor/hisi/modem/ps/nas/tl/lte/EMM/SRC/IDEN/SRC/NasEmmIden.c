

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmIden.h"
#include    "NasLmmPubMInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_NASEMMIDEN_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_EMM_IdenInit
 Discription    : IDEN模块初始化函数
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_IdenInit(VOS_VOID)
{
    /*IDEN目前没有需要初始化的信息,暂时为空*/

    return;
}
VOS_VOID  NAS_EMM_FreeIdenDyn( VOS_VOID )
{
    /*IDEN目前为空*/

    return;
}
/*lint -e960*/
VOS_UINT32 NAS_EMM_AnyStateMsgIdenReq(VOS_UINT32  ulMsgId,
                                      VOS_VOID   *pMsgStru)
{

    NAS_EMM_IDEN_REQ_STRU              *pstIdenReqMsg;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pstIdenRspMsg = NAS_EMM_NULL_PTR;
    VOS_UINT8                           ucIdenType;
    VOS_UINT32                          ulDataReqLenNoHeader;

    (VOS_VOID)ulMsgId;

    /*获取空口消息，结构转化 */
    pstIdenReqMsg = (NAS_EMM_IDEN_REQ_STRU*)pMsgStru;
    ucIdenType    = pstIdenReqMsg->ucIdenType;

    /*以最小消息长度，申请消息内存,主要是看是否队列有空间*/
    pstIdenRspMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)NAS_LMM_MEM_ALLOC( \
                                                NAS_EMM_INTRA_MSG_MAX_SIZE);
    if(NAS_EMM_NULL_PTR == pstIdenRspMsg)
    {
        NAS_EMM_IDEN_ERROR_LOG("NAS_EMM_AnyStateMsgIdenReq: Alloc Msg Fail!");
        return NAS_LMM_MSG_HANDLED;
    }

    /*依据解析结果，获取网侧请求的身份识别参数*/
    NAS_EMM_IdenTypeGet(ucIdenType, &(pstIdenRspMsg->stNasMsg));

    /*内部消息长度计算*/
    ulDataReqLenNoHeader = NAS_EMM_CountMrrcDataReqLen( \
                                        pstIdenRspMsg->stNasMsg.ulNasMsgSize);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqLenNoHeader )
    {
        /* 打印错误信息 */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_AnyStateMsgIdenReq, Size error");
        NAS_LMM_MEM_FREE(pstIdenRspMsg);
        return NAS_LMM_MSG_HANDLED;
    }

    /*打包VOS消息头,NAS_EMM_MRRC_DATA_REQ_STRU */
    NAS_EMM_INTRA_MSG_HEADER(pstIdenRspMsg, ulDataReqLenNoHeader);

    /*填充消息ID    */
    pstIdenRspMsg->ulMsgId              = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*填充消息内容*/
    pstIdenRspMsg->enEstCaue            = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pstIdenRspMsg->enCallType           = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pstIdenRspMsg->enEmmMsgType         = NAS_EMM_MSG_IDEN_RSP;

    pstIdenRspMsg->enDataCnf            = LRRC_LMM_DATA_CNF_NEED;

    /*空口消息上报 IDEN RSP*/
    /*lint -e961*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_IDEN_RSP,  (NAS_MSG_STRU*)&(pstIdenRspMsg->stNasMsg));
    /*lint +e961*/

    /*关键事件上报 IDEN RSP*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_IDEN_RSP);

    /* 给MRRC发送MRRC_DATA_REQ */
    NAS_EMM_SndUplinkNasMsg(             pstIdenRspMsg);

    NAS_LMM_MEM_FREE(pstIdenRspMsg);

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name  : NAS_EMM_CompCnIdenRsp
 Discription    : 给CN NAS消息头赋值
 Input          : 消息
 Output         : None
 Return         : None
 History:
     1.   zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_CompCnIdenRsp( LRRC_LNAS_MSG_STRU *pNasMsg)
{
    /*IDEN RSP的CN消息头赋值*/
    pNasMsg->aucNasMsg[0]   = EMM_CN_MSG_PD_EMM;
    pNasMsg->aucNasMsg[0]  |= NAS_EMM_CN_MSG_SE_EMM;
    pNasMsg->aucNasMsg[1]   = NAS_EMM_CN_MT_IDEN_RSP;

    return;
}
VOS_UINT32  NAS_EMM_GetTmsiStatus(VOS_VOID)
{
    NAS_GUMM_INFO_STRU                  stGuInfo;
    stGuInfo.u.ulTmsiStatus           = MMC_LMM_TMSI_STATUS_INVALID;
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* 获取TMSI状态失败*/
    if (MMC_LMM_FAIL == NAS_EMM_GetGuInfo(NAS_GUMM_TMSI_STATUS, &stGuInfo))
    {
        NAS_EMM_IDEN_NORMAL_LOG("NAS_EMM_GetTmsi: GetGuInfo FAIL .");
        return NAS_EMM_FAIL;
    }

    /* TMSI状态无效*/
    if (MMC_LMM_TMSI_STATUS_INVALID == stGuInfo.u.ulTmsiStatus)
    {
        NAS_EMM_IDEN_NORMAL_LOG("NAS_EMM_GetTmsi: TMSI status invalid .");
        return NAS_EMM_FAIL;
    }

    /*PC REPLAY MODIFY BY LEILI END*/
    return NAS_EMM_SUCC;

}

/* lihong00150010 emergency tau&service begin */

VOS_VOID NAS_EMM_IdenImsi
(
    LRRC_LNAS_MSG_STRU                     *pNasMsg,
    VOS_UINT32                             *ulMsgLen
)
{
    /*如果无卡或者卡无效，则返回NO IDENTITY*/
    if ((NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
        || (NAS_LMM_SIM_INVALID == NAS_LMM_GetPsSimValidity()))
    {
        /*No Identity时长度为3个字节 */
        pNasMsg->aucNasMsg[2]         = NAS_EMM_NO_IDENTITY_LEN;
        pNasMsg->aucNasMsg[3]         = (NAS_EMM_ODD_BIT<<3) | (NAS_EMM_MOBILE_ID_NONE);

        *ulMsgLen += (NAS_EMM_NO_IDENTITY_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

        return;
    }

    NAS_LMM_MEM_CPY(&pNasMsg->aucNasMsg[2],
                     &NAS_EMM_IDEN_IMSI_GLOBAL(0),
                     (NAS_EMM_IDEN_IMSI_GLOBAL(0) + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN));

    *ulMsgLen += (NAS_EMM_IDEN_IMSI_GLOBAL(0) + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

    return;
}
/* lihong00150010 emergency tau&service end */

/*****************************************************************************
 Function Name  : NAS_EMM_IdenImei
 Discription    : 获取Imei
 Input          : 消息
 Output         : None
 Return         : None
 History:
     1.   zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_IdenImei(LRRC_LNAS_MSG_STRU *pNasMsg)
{

    NAS_LMM_MEM_CPY(&pNasMsg->aucNasMsg[2],
                    &NAS_EMM_IDEN_IMEI_GLOBAL(0),
                     NAS_EMM_IDEN_IMEI_GLOBAL(0) + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

    return;
}
/*****************************************************************************
 Function Name  : NAS_EMM_IdenImeisv
 Discription    : 获取ImeiSV
 Input          : 消息
 Output         : None
 Return         : None
 History:
     1.   zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_IdenImeisv(LRRC_LNAS_MSG_STRU *pNasMsg)
{

    NAS_LMM_MEM_CPY(&pNasMsg->aucNasMsg[2],
                     &NAS_EMM_IDEN_IMEISV_GLOBAL(0),
                      NAS_EMM_IDEN_IMEISV_GLOBAL(0) + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

    return;
}

VOS_VOID  NAS_EMM_EncodeTmsi
(
    LRRC_LNAS_MSG_STRU  *pNasMsg,
    VOS_UINT32          *ulMsgLen
)
{
    NAS_EMM_IDEN_INFO_LOG("NAS_EMM_EncodeTmsi   is  entered.");

    /* 如果获取TMSI失败或者TMSI无效 */
    if(NAS_EMM_FAIL ==  NAS_EMM_GetTmsiStatus())
    {
        /*No Identity时长度为3个字节 */
        pNasMsg->aucNasMsg[2]         = NAS_EMM_NO_IDENTITY_LEN;
        pNasMsg->aucNasMsg[3]         = (NAS_EMM_ODD_BIT<<3) | (NAS_EMM_MOBILE_ID_NONE);

        *ulMsgLen += (NAS_EMM_NO_IDENTITY_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);
    }
    else
    {
        /* 获取TMSI成功且有效 */
        /* 长度 */
        pNasMsg->aucNasMsg[2]         = NAS_EMM_TMSI_LEN;

        /* Identity digit 1 | O/D | Type of identity 共占1个字节 */
        /* 24008,  10.5.1.4节:
              if the mobile identity is TMSI/P-TMSI/M-TMSI,
              then bit5 to bit8 of octet 3 are code as "1111" */
        pNasMsg->aucNasMsg[3]         = ((NAS_EMM_EVEN_BIT<<3) | (NAS_EMM_MOBILE_ID_TMSI))|0xF0;

        /* 拷贝TMSI的值，长度为4字节 */
        NAS_LMM_MEM_CPY(&pNasMsg->aucNasMsg[4],
                       NAS_MML_GetUeIdTmsi(),
                       NAS_EMM_TMSI_LEN -1);    //lint !e419 !e826 !e950

        *ulMsgLen += (NAS_EMM_TMSI_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

         /* 打印获取到的TMSI值 */
        NAS_EMM_IDEN_NORMAL_LOG("NAS_EMM_GetTmsi: TMSI value is :");
        NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                       NAS_MML_GetUeIdTmsi(),
                       NAS_EMM_TMSI_LEN -1);
    }

    return;

}
/*lint +e960*/

VOS_VOID NAS_EMM_IdenTypeGet(VOS_UINT8 ucIdenType, LRRC_LNAS_MSG_STRU *pNasMsg)
{
    VOS_UINT32              ulIndex         = 0;
    LRRC_LNAS_MSG_STRU       *pTempNasMsg     =pNasMsg;

    pTempNasMsg->aucNasMsg[ulIndex]     = EMM_CN_MSG_PD_EMM;
    pTempNasMsg->aucNasMsg[ulIndex++]  |= NAS_EMM_CN_MSG_SE_EMM;
    pTempNasMsg->aucNasMsg[ulIndex++]   = NAS_EMM_CN_MT_IDEN_RSP;

    /* lihong00150010 emergency tau&service begin */
    switch (ucIdenType)
    {
        case    NAS_EMM_MOBILE_ID_IMSI:           /*获取IMSI*/
                NAS_EMM_IdenImsi(pTempNasMsg, &ulIndex);

                break;

        case    NAS_EMM_MOBILE_ID_IMEI:           /*获取IMEI*/
                NAS_EMM_IdenImei(pTempNasMsg);

                ulIndex += (NAS_EMM_IMEI_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);
                break;

        case    NAS_EMM_MOBILE_ID_IMEISV:         /*获取IMEISV*/
                NAS_EMM_IdenImeisv(pTempNasMsg);

                ulIndex += (NAS_EMM_IMEISV_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);
                break;

        case    NAS_EMM_MOBILE_ID_TMSI:           /*获取TMSI*/
                NAS_EMM_EncodeTmsi(pTempNasMsg, &ulIndex);

                break;

        default:
                NAS_EMM_IdenImsi(pTempNasMsg, &ulIndex);       /*others作为IMSI处理*/

                break;
    }

    pTempNasMsg->ulNasMsgSize = ulIndex;
    /* lihong00150010 emergency tau&service end */
    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of 子系统+模块+文件名.c */
