/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : fr_etsi_op.h
  版 本 号   : 初稿
  作    者   : 谢明辉 58441
  生成日期   : 2011年5月4日
  最近修改   :
  功能描述   : FR 基本运算转定义头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月4日
    作    者   : 谢明辉 58441
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __FR_ETSI_OP_H__
#define __FR_ETSI_OP_H__

#include  "codec_op_etsi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define  gsm_add(var1, var2)            add(var1, var2)
#define  gsm_sub(var1, var2)            sub(var1, var2)
#define  gsm_mult(var1, var2)           mult(var1, var2)
#define  gsm_mult_r(var1, var2)         mult_r(var1, var2)
#define  gsm_abs(var1)                  abs_s(var1)
#define  gsm_L_mult(var1, var2)         L_mult(var1, var2)
#define  gsm_L_add(var1, var2)          L_add(var1, var2)
#define  gsm_L_sub(var1, var2)          L_sub(var1, var2)
#define  gsm_norm(var1)                 norm_l(var1)
#define  gsm_L_asl(var1, var2)          L_shl(var1, var2)
#define  gsm_asl(var1, var2)            shl(var1, var2)
#define  gsm_L_asr(var1, var2)          L_shr(var1, var2)
#define  gsm_asr(var1, var2)            shr(var1, var2)
#define  gsm_div(var1, var2)            div_s(var1, var2)

#define  GSM_MULT_R(var1, var2)         mult_r(var1, var2)
#define  GSM_MULT(var1, var2)           mult(var1, var2)
#define  GSM_L_MULT(var1, var2)         L_mult(var1, var2)
#define  GSM_L_ADD(var1, var2)          L_add(var1, var2)
#define  GSM_ADD(var1, var2)            add(var1, var2)
#define  GSM_SUB(var1, var2)            sub(var1, var2)
#define  GSM_ABS(var1)                  abs_s(var1)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of fr_etsi_op.h */
