
#ifndef __DRV_MAILBOX_STUB_H__
#define __DRV_MAILBOX_STUB_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* ����ռ��memory����ַ */
#define MAILBOX_MEM_BASEADDR            ((int)&g_MAILBOX_BST_HEAD0[0])

/* ����ռ��memoryԤ���ܳ���, �����������ͷ��������л��� */
#define MAILBOX_MEM_LENGTH              mailbox_memory_length()

/*PC�������Ĺ����ڴ�ͨ���ռ�ӳ�䵽��̬����ռ�*/
extern  int g_MAILBOX_BST_HEAD0[];                      
#define MAILBOX_HEAD_ADDR_MCU2ACPU_MSG           MAILBOX_MEM_BASEADDR                                         
#define MAILBOX_HEAD_ADDR_ACPU2MCU_MSG          (MAILBOX_HEAD_ADDR_MCU2ACPU_MSG +  MAILBOX_HEAD_LEN)
                                                                                                                
#define MAILBOX_HEAD_ADDR_ACPU2HIFI_MSG         (MAILBOX_HEAD_ADDR_ACPU2MCU_MSG +  MAILBOX_HEAD_LEN)
#define MAILBOX_HEAD_ADDR_HIFI2ACPU_MSG         (MAILBOX_HEAD_ADDR_ACPU2HIFI_MSG + MAILBOX_HEAD_LEN)
                                                                                                                                                                                                    
#define MAILBOX_HEAD_ADDR_MCU2CCPU_MSG          (MAILBOX_HEAD_ADDR_HIFI2ACPU_MSG +  MAILBOX_HEAD_LEN)
#define MAILBOX_HEAD_ADDR_CCPU2MCU_MSG          (MAILBOX_HEAD_ADDR_MCU2CCPU_MSG +  MAILBOX_HEAD_LEN)
                                                                                                                
#define MAILBOX_HEAD_ADDR_CCPU2HIFI_MSG         (MAILBOX_HEAD_ADDR_CCPU2MCU_MSG +  MAILBOX_HEAD_LEN)
#define MAILBOX_HEAD_ADDR_HIFI2CCPU_MSG         (MAILBOX_HEAD_ADDR_CCPU2HIFI_MSG +  MAILBOX_HEAD_LEN)

#define MAILBOX_HEAD_ADDR_CCPU2ACPU_MSG             (MAILBOX_HEAD_ADDR_HIFI2CCPU_MSG +  MAILBOX_HEAD_LEN)
#define MAILBOX_HEAD_ADDR_ACPU2CCPU_MSG             (MAILBOX_HEAD_ADDR_CCPU2ACPU_MSG +  MAILBOX_HEAD_LEN)

#define MAILBOX_HEAD_ADDR_CCPU2ACPU_IFC             (MAILBOX_HEAD_ADDR_ACPU2CCPU_MSG +  MAILBOX_HEAD_LEN)
#define MAILBOX_HEAD_ADDR_ACPU2CCPU_IFC             (MAILBOX_HEAD_ADDR_CCPU2ACPU_IFC +  MAILBOX_HEAD_LEN)

#define MAILBOX_HEAD_ADDR_CCPU2MCU_IFC             (MAILBOX_HEAD_ADDR_ACPU2CCPU_IFC +  MAILBOX_HEAD_LEN)
#define MAILBOX_HEAD_ADDR_MCU2CCPU_IFC             (MAILBOX_HEAD_ADDR_CCPU2MCU_IFC +  MAILBOX_HEAD_LEN)

#define MAILBOX_HEAD_ADDR_ACPU2MCU_IFC             (MAILBOX_HEAD_ADDR_MCU2CCPU_IFC +  MAILBOX_HEAD_LEN)
#define MAILBOX_HEAD_ADDR_MCU2ACPU_IFC             (MAILBOX_HEAD_ADDR_ACPU2MCU_IFC +  MAILBOX_HEAD_LEN)

#define MAILBOX_HEAD_BOTTOM_ADDR                    (MAILBOX_HEAD_ADDR_MCU2ACPU_IFC +  MAILBOX_HEAD_LEN)    

#define MAILBOX_QUEUE_ADDR_MCU2ACPU_MSG         (MAILBOX_MEM_BASEADDR + MAILBOX_MEM_HEAD_LEN)
#define MAILBOX_QUEUE_ADDR_ACPU2MCU_MSG         (MAILBOX_QUEUE_ADDR_MCU2ACPU_MSG +  MAILBOX_QUEUE_SIZE(MCU,  ACPU ,MSG))
                                                                                                                
#define MAILBOX_QUEUE_ADDR_ACPU2HIFI_MSG        (MAILBOX_QUEUE_ADDR_ACPU2MCU_MSG +  MAILBOX_QUEUE_SIZE(ACPU, MCU  ,MSG))
#define MAILBOX_QUEUE_ADDR_HIFI2ACPU_MSG        (MAILBOX_QUEUE_ADDR_ACPU2HIFI_MSG + MAILBOX_QUEUE_SIZE(ACPU ,HIFI ,MSG))
                                                                                                                
#define MAILBOX_QUEUE_ADDR_MCU2CCPU_MSG         (MAILBOX_QUEUE_ADDR_HIFI2ACPU_MSG +  MAILBOX_QUEUE_SIZE(HIFI ,ACPU  ,MSG) )
#define MAILBOX_QUEUE_ADDR_CCPU2MCU_MSG         (MAILBOX_QUEUE_ADDR_MCU2CCPU_MSG +  MAILBOX_QUEUE_SIZE(MCU  ,CCPU ,MSG) )
                                                                                                                
#define MAILBOX_QUEUE_ADDR_CCPU2HIFI_MSG        (MAILBOX_QUEUE_ADDR_CCPU2MCU_MSG +  MAILBOX_QUEUE_SIZE(CCPU ,MCU  ,MSG) )
#define MAILBOX_QUEUE_ADDR_HIFI2CCPU_MSG        (MAILBOX_QUEUE_ADDR_CCPU2HIFI_MSG+  MAILBOX_QUEUE_SIZE(CCPU ,HIFI ,MSG))

#define MAILBOX_QUEUE_ADDR_CCPU2ACPU_MSG            (MAILBOX_QUEUE_ADDR_HIFI2CCPU_MSG +  MAILBOX_QUEUE_SIZE(HIFI, CCPU, MSG) )
#define MAILBOX_QUEUE_ADDR_ACPU2CCPU_MSG            (MAILBOX_QUEUE_ADDR_CCPU2ACPU_MSG +  MAILBOX_QUEUE_SIZE(CCPU ,ACPU ,MSG))

#define MAILBOX_QUEUE_ADDR_CCPU2ACPU_IFC            (MAILBOX_QUEUE_ADDR_ACPU2CCPU_MSG +  MAILBOX_QUEUE_SIZE(ACPU, CCPU, MSG) )
#define MAILBOX_QUEUE_ADDR_ACPU2CCPU_IFC            (MAILBOX_QUEUE_ADDR_CCPU2ACPU_IFC+  MAILBOX_QUEUE_SIZE(CCPU, ACPU, IFC))

#define MAILBOX_QUEUE_ADDR_CCPU2MCU_IFC            (MAILBOX_QUEUE_ADDR_ACPU2CCPU_IFC +  MAILBOX_QUEUE_SIZE(ACPU, CCPU, IFC) )
#define MAILBOX_QUEUE_ADDR_MCU2CCPU_IFC            (MAILBOX_QUEUE_ADDR_CCPU2MCU_IFC+  MAILBOX_QUEUE_SIZE(CCPU, MCU, IFC))

#define MAILBOX_QUEUE_ADDR_ACPU2MCU_IFC            (MAILBOX_QUEUE_ADDR_MCU2CCPU_IFC +  MAILBOX_QUEUE_SIZE(MCU, CCPU, IFC) )
#define MAILBOX_QUEUE_ADDR_MCU2ACPU_IFC            (MAILBOX_QUEUE_ADDR_ACPU2MCU_IFC+  MAILBOX_QUEUE_SIZE(ACPU, MCU, IFC))
  
#define MAILBOX_MEMORY_BOTTOM_ADDR                  (MAILBOX_QUEUE_ADDR_MCU2CCPU_IFC + MAILBOX_QUEUE_SIZE(MCU, ACPU, IFC))

int mailbox_memory_length(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of __DRV_MAILBOX_STUB_H__.h */
