<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र/sunbpp.h
 */

#अगर_अघोषित _ASM_SPARC_SUNBPP_H
#घोषणा _ASM_SPARC_SUNBPP_H

काष्ठा bpp_regs अणु
  /* DMA रेजिस्टरs */
  __अस्थिर__ __u32 p_csr;		/* DMA Control/Status Register */
  __अस्थिर__ __u32 p_addr;		/* Address Register */
  __अस्थिर__ __u32 p_bcnt;		/* Byte Count Register */
  __अस्थिर__ __u32 p_tst_csr;		/* Test Control/Status (DMA2 only) */
  /* Parallel Port रेजिस्टरs */
  __अस्थिर__ __u16 p_hcr;		/* Hardware Configuration Register */
  __अस्थिर__ __u16 p_ocr;		/* Operation Configuration Register */
  __अस्थिर__ __u8 p_dr;		/* Parallel Data Register */
  __अस्थिर__ __u8 p_tcr;		/* Transfer Control Register */
  __अस्थिर__ __u8 p_or;		/* Output Register */
  __अस्थिर__ __u8 p_ir;		/* Input Register */
  __अस्थिर__ __u16 p_icr;		/* Interrupt Control Register */
पूर्ण;

/* P_HCR. Time is in increments of SBus घड़ी. */
#घोषणा P_HCR_TEST      0x8000      /* Allows buried counters to be पढ़ो */
#घोषणा P_HCR_DSW       0x7f00      /* Data strobe width (in ticks) */
#घोषणा P_HCR_DDS       0x007f      /* Data setup beक्रमe strobe (in ticks) */

/* P_OCR. */
#घोषणा P_OCR_MEM_CLR   0x8000
#घोषणा P_OCR_DATA_SRC  0x4000      /* )                  */
#घोषणा P_OCR_DS_DSEL   0x2000      /* )  Bidirectional      */
#घोषणा P_OCR_BUSY_DSEL 0x1000      /* )    selects            */
#घोषणा P_OCR_ACK_DSEL  0x0800      /* )                  */
#घोषणा P_OCR_EN_DIAG   0x0400
#घोषणा P_OCR_BUSY_OP   0x0200      /* Busy operation */
#घोषणा P_OCR_ACK_OP    0x0100      /* Ack operation */
#घोषणा P_OCR_SRST      0x0080      /* Reset state machines. Not selfcleaning. */
#घोषणा P_OCR_IDLE      0x0008      /* PP data transfer state machine is idle */
#घोषणा P_OCR_V_ILCK    0x0002      /* Versatec faded. Zebra only. */
#घोषणा P_OCR_EN_VER    0x0001      /* Enable Versatec (0 - enable). Zebra only. */

/* P_TCR */
#घोषणा P_TCR_सूची       0x08
#घोषणा P_TCR_BUSY      0x04
#घोषणा P_TCR_ACK       0x02
#घोषणा P_TCR_DS        0x01        /* Strobe */

/* P_OR */
#घोषणा P_OR_V3         0x20        /* )                 */
#घोषणा P_OR_V2         0x10        /* ) on Zebra only   */
#घोषणा P_OR_V1         0x08        /* )                 */
#घोषणा P_OR_INIT       0x04
#घोषणा P_OR_AFXN       0x02        /* Auto Feed */
#घोषणा P_OR_SLCT_IN    0x01

/* P_IR */
#घोषणा P_IR_PE         0x04
#घोषणा P_IR_SLCT       0x02
#घोषणा P_IR_ERR        0x01

/* P_ICR */
#घोषणा P_DS_IRQ        0x8000      /* RW1  */
#घोषणा P_ACK_IRQ       0x4000      /* RW1  */
#घोषणा P_BUSY_IRQ      0x2000      /* RW1  */
#घोषणा P_PE_IRQ        0x1000      /* RW1  */
#घोषणा P_SLCT_IRQ      0x0800      /* RW1  */
#घोषणा P_ERR_IRQ       0x0400      /* RW1  */
#घोषणा P_DS_IRQ_EN     0x0200      /* RW   Always on rising edge */
#घोषणा P_ACK_IRQ_EN    0x0100      /* RW   Always on rising edge */
#घोषणा P_BUSY_IRP      0x0080      /* RW   1= rising edge */
#घोषणा P_BUSY_IRQ_EN   0x0040      /* RW   */
#घोषणा P_PE_IRP        0x0020      /* RW   1= rising edge */
#घोषणा P_PE_IRQ_EN     0x0010      /* RW   */
#घोषणा P_SLCT_IRP      0x0008      /* RW   1= rising edge */
#घोषणा P_SLCT_IRQ_EN   0x0004      /* RW   */
#घोषणा P_ERR_IRP       0x0002      /* RW1  1= rising edge */
#घोषणा P_ERR_IRQ_EN    0x0001      /* RW   */

#पूर्ण_अगर /* !(_ASM_SPARC_SUNBPP_H) */
