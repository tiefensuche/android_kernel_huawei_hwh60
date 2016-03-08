

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasCcInclude.h"
#include  "NasOmInterface.h"
#include  "NasOmTrans.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


#define THIS_FILE_ID PS_FILE_ID_NASCC_MMCCSEND_C


/*NAS上行空口消息ID和上报给OM的消息ID对应表*/
NAS_CC_OTA_MSG_ID_STRU    g_astNasOtaMsgIdM2N[] = {

    {NAS_CC_MSG_CONNECT_ACK,      NAS_OTA_MSG_CC_CONNECT_ACK_UP},
    {NAS_CC_MSG_DISCONNECT,       NAS_OTA_MSG_CC_DISCONNECT_UP},
    {NAS_CC_MSG_RELEASE,          NAS_OTA_MSG_CC_RELEASE_UP},
    {NAS_CC_MSG_RELEASE_COMPLETE, NAS_OTA_MSG_CC_RELEASE_COMPLETE_UP},
    {NAS_CC_MSG_START_DTMF,       NAS_OTA_MSG_CC_START_DTMF},
    {NAS_CC_MSG_STOP_DTMF,        NAS_OTA_MSG_CC_STOP_DTMF},
    {NAS_CC_MSG_STATUS,           NAS_OTA_MSG_CC_STATUS_UP},
    {NAS_CC_MSG_CALL_CNF,         NAS_OTA_MSG_CC_CALL_CONFIRM},
    {NAS_CC_MSG_SETUP,            NAS_OTA_MSG_CC_SETUP_UP},
    {NAS_CC_MSG_EMERGENCY_SETUP,  NAS_OTA_MSG_CC_SETUP_UP},
    {NAS_CC_MSG_ALERTING,         NAS_OTA_MSG_CC_ALERTING_UP},
    {NAS_CC_MSG_CONNECT,          NAS_OTA_MSG_CC_CONNECT_UP},
    {NAS_CC_MSG_FACILITY,         NAS_OTA_MSG_CC_FACILITY_UP},
    {NAS_CC_MSG_HOLD,             NAS_OTA_MSG_CC_HOLD},
    {NAS_CC_MSG_RETRIEVE,         NAS_OTA_MSG_CC_RETREIVE},
    {NAS_CC_MSG_MODIFY,           NAS_OTA_MSG_CC_MODIFY_UP},
    {NAS_CC_MSG_MODIFY_COMPLETE,  NAS_OTA_MSG_CC_MODIFY_COMPLETE_UP},
    {NAS_CC_MSG_MODIFY_REJ,       NAS_OTA_MSG_CC_MODIFY_REJ_UP},
    {NAS_CC_MSG_CC_EST_CNF,       NAS_OTA_MSG_CC_CCBS_EST_CNF},

};

/*****************************************************************************
  2 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_CC_AllocMmccPrim
 功能描述  : 申请MMCC原语消息
 输入参数  : ulMsgName  - 消息名称
              ulMsgLen   - 消息长度
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
LOCAL VOS_VOID * NAS_CC_AllocMmccPrim(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulMsgLen
)
{
    MSG_HEADER_STRU * pstMsg =
        (MSG_HEADER_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_CC, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_CC_ERR_LOG("NAS_CC_AllocMmccPrim: Failed to alloc VOS message.");
        return VOS_NULL_PTR;
    }

    /* 填写VOS消息头 */
    pstMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid = WUEPS_PID_CC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid = WUEPS_PID_MM;

    pstMsg->ulMsgName = ulMsgName;

    return pstMsg;
}
LOCAL VOS_VOID  NAS_CC_SendMmccPrim(
    VOS_VOID                            *pMsg
)
{
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CC, pMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_CC, "NAS_CC_SendMmccPrim():WARNING:SEND MSG FIAL");
    }       
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccAbortReq
 功能描述  : 发送MMCC_ABORT_REQ原语
 输入参数  : ucTi - Transaction ID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccAbortReq(
    VOS_UINT8                           ucTi
)
{
    MMCC_ABORT_REQ_STRU * pstMsg =
        (MMCC_ABORT_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_ABORT_REQ, sizeof(MMCC_ABORT_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    NAS_CC_SendMmccPrim(pstMsg);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccRelReq
 功能描述  : 发送MMCC_REL_REQ原语
 输入参数  : ucTi      - Transaction ID
              ulRelType - 释放的类型(MMCC_RELEASE_ALL/MMCC_RELEASE_SPECIFIC)
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccRelReq(
    VOS_UINT8                           ucTi,
    VOS_UINT32                          ulRelType
)
{
    MMCC_REL_REQ_STRU * pstMsg =
        (MMCC_REL_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_REL_REQ, sizeof(MMCC_REL_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    pstMsg->ulReleaseType = ulRelType;

    NAS_CC_SendMmccPrim(pstMsg);
}



VOS_VOID  NAS_CC_SendMmccEstReq(
    VOS_UINT8                           ucTi,
    VOS_UINT32                          ulCallType,
    VOS_UINT32                          ulCallMode,
    VOS_UINT32                          ulPriority
)
{
    MMCC_EST_REQ_STRU * pstMsg =
        (MMCC_EST_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_EST_REQ, sizeof(MMCC_EST_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    pstMsg->ulCallType = ulCallType;
    pstMsg->ulCallPri = ulPriority;
    pstMsg->ulCallMode = ulCallMode;

    NAS_CC_SendMmccPrim(pstMsg);
}


VOS_VOID NAS_CC_ReportM2NOtaMsg(
    CC_MSG_STRU                         *pNasMsg
)
{
    NAS_OTA_MSG_ID_ENUM_UINT16          enNasOtaMsyId;
    VOS_UINT32                          i;

    enNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;
    NAS_CC_NORM_LOG1("NAS_CC_ReportM2NOtaMsg:NORMAL: msg id is", pNasMsg->aucCcMsg[1]);

    /*在NAS上行空口消息ID和上报给OM的消息ID对应表查找该消息是否需要通过OM进行勾取显示*/
    for (i = 0; i < (sizeof(g_astNasOtaMsgIdM2N) / sizeof(NAS_CC_OTA_MSG_ID_STRU)); i++)
    {
        if (g_astNasOtaMsgIdM2N[i].enCcMsgId == pNasMsg->aucCcMsg[1])
        {
            enNasOtaMsyId = g_astNasOtaMsgIdM2N[i].enOtaMsgId;
            break;
        }
    }

    if (NAS_OTA_MSG_ID_BUTT == enNasOtaMsyId)
    {
        NAS_CC_WARN_LOG1("NAS_CC_ReportM2NOtaMsg:WARNING: invalid msg id is ",enNasOtaMsyId);
        /*不属于CC模块的空口消息，不在trace中显示*/
        return;
    }

    /*上报空口消息给OM*/
    NAS_SendAirMsgToOM(WUEPS_PID_CC, enNasOtaMsyId, NAS_OTA_DIRECTION_UP, pNasMsg->ulCcMsgSize + 4, (VOS_UINT8*)pNasMsg);
}
VOS_VOID  NAS_CC_SendMmccDataReq(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           *pucCcMsg,
    VOS_UINT32                          ulCcMsgSize
)
{
    MMCC_DATA_REQ_STRU * pstMsg =
        (MMCC_DATA_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_DATA_REQ, (sizeof(MMCC_DATA_REQ_STRU) - 4) + ulCcMsgSize);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    pstMsg->SendCcMsg.ulCcMsgSize = ulCcMsgSize;
    PS_MEM_CPY(pstMsg->SendCcMsg.aucCcMsg, pucCcMsg, ulCcMsgSize);

    /*通过OM钩取CC空口消息*/
    NAS_CC_ReportM2NOtaMsg(&pstMsg->SendCcMsg);


    NAS_CC_SendMmccPrim(pstMsg);
}

/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccPromptRej
 功能描述  : 发送MMCC_PROMPT_REJ原语
 输入参数  : ulCause - 拒绝的原因
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccPromptRej(
    VOS_UINT32                          ulCause
)
{
    MMCC_PROMPT_REJ_STRU * pstMsg =
        (MMCC_PROMPT_REJ_STRU *)NAS_CC_AllocMmccPrim(MMCC_PROMPT_REJ, sizeof(MMCC_PROMPT_REJ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulRefuseCause = ulCause;

    NAS_CC_SendMmccPrim(pstMsg);
}


/*****************************************************************************
 函 数 名  : NAS_CC_SendMmccReestReq
 功能描述  : 发送MMCC_REEST_REQ原语
 输入参数  : ucTi - Transaction ID
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月17日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_CC_SendMmccReestReq(
    VOS_UINT8                           ucTi
)
{
    MMCC_REEST_REQ_STRU * pstMsg =
        (MMCC_REEST_REQ_STRU *)NAS_CC_AllocMmccPrim(MMCC_REEST_REQ, sizeof(MMCC_REEST_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    NAS_CC_SendMmccPrim(pstMsg);
}


VOS_VOID  NAS_CC_SendMmccStartCc(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           *pucCcMsg,
    VOS_UINT32                          ulCcMsgSize
)
{
    MMCC_DATA_REQ_STRU* pstMsg =
        (MMCC_DATA_REQ_STRU*)NAS_CC_AllocMmccPrim(MMCC_START_CC,
                                                  sizeof(MMCC_DATA_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
    /* pstMsg->ulTransactionId = ucTi; */
    pstMsg->ulTransactionId = (ucTi ^ 0x8);

    pstMsg->SendCcMsg.ulCcMsgSize = ulCcMsgSize;
    PS_MEM_CPY(pstMsg->SendCcMsg.aucCcMsg, pucCcMsg, ulCcMsgSize);

    NAS_CC_SendMmccPrim(pstMsg);
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID  NAS_CC_SendMmccSrvccCallInfoNtf(
    VOS_UINT8                           ucSyncTiNum,
    VOS_UINT8                          *pucSyncTi 
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTi;
    
    MMCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstMsg =
        (MMCC_SRVCC_CALL_INFO_NOTIFY_STRU*)NAS_CC_AllocMmccPrim(MMCC_SRVCC_CALL_INFO_NOTIFY,
                                                  sizeof(MMCC_SRVCC_CALL_INFO_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }
  
    for (i= 0 ; i< ucSyncTiNum; i++)
    {
        ucTi = pucSyncTi[i];
    
        /* TI 的维护需要和MM统一：网侧发起的呼叫TI标志为0，MS发起的呼叫TI标志为1。 */
        pstMsg->aucTransactionId[i] = ucTi ^ 0x08;
    } 

    pstMsg->ucTiNum = ucSyncTiNum;

    NAS_CC_SendMmccPrim(pstMsg);
}
#endif




#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

