
#ifndef _TAF_SPM_FSM_PREPROC_TBL_H_
#define _TAF_SPM_FSM_PREPROC_TBL_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

extern TAF_STA_STRU                     g_astTafSpmPreProcessFsmTbl[];


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_SPM_GetPreProcessStaTbl()   (g_astTafSpmPreProcessFsmTbl)


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
#if (FEATURE_ON == FEATURE_IMS)
typedef VOS_UINT32 (*TAF_SPM_PROC_IMSA_CALL_MSG_FUNC)(struct MsgCB *pstMsg);

typedef struct
{
    VOS_UINT32                          ulMsgEvtType;
    TAF_SPM_PROC_IMSA_CALL_MSG_FUNC     pfMsgFun;
} TAF_SPM_PROC_IMSA_CALL_MSG_STRU;
#endif

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetPreProcessStaTblSize( VOS_VOID  );

TAF_FSM_DESC_STRU * TAF_SPM_GetPreFsmDescAddr( VOS_VOID );

#if (FEATURE_ON == FEATURE_IMS)
TAF_SPM_PROC_IMSA_CALL_MSG_STRU *TAF_SPM_GetImsaCallMsgTabAddr( VOS_VOID );

VOS_UINT32 TAF_SPM_GetImsaCallMsgTabSize( VOS_VOID );
#endif


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafMmaPreProcTbl.h */
