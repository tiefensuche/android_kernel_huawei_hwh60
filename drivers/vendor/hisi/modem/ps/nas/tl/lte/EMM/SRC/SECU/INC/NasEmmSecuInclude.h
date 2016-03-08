

#ifndef __NASEMMSECUINCLUDE_H__
#define __NASEMMSECUINCLUDE_H__



/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "AppNasComm.h"
#include    "NasLmmPubMFsm.h"
#include    "NasLmmPubMOsa.h"
#include    "NasLmmPubMOm.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmPubUCnMsgDecode.h"
#include    "NasLmmPubMTimer.h"
#include    "NasLmmPubMEntry.h"

#include    "NasEmmSecuInterface.h"
#include    "NasEmmIdenPubInterface.h"
#include    "LRabmPdcpInterface.h"
#include    "LRrcLNasInterface.h"
#include    "NasEmmMrrcPubInterface.h"


#include    "NasEmmSecuAuth.h"
#include    "NasEmmSecuOm.h"
#include    "NasEmmSecuProtect.h"
#include    "NasEmmSecuSmc.h"
#include    "NasEmmSecuSoftUsim.h"
#include    "LPsOm.h"
#include    "DrvInterface.h"
#include    "LPsNvInterface.h"
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 Macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
结构名称    :NAS_LMM_SECU_CONTROL_STRU
使用说明    :MM的安全模块的控制结构
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/










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

#endif /* end of NasEmmSecuInclude */
