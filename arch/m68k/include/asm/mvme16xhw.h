<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_MVME16xHW_H_
#घोषणा _M68K_MVME16xHW_H_

#समावेश <यंत्र/irq.h>


प्रकार काष्ठा अणु
	u_अक्षर	ack_icr,
		flt_icr,
		sel_icr,
		pe_icr,
		bsy_icr,
		spare1,
		isr,
		cr,
		spare2,
		spare3,
		spare4,
		data;
पूर्ण MVMElp, *MVMElpPtr;

#घोषणा MVME_LPR_BASE	0xfff42030

#घोषणा mvmelp   ((*(अस्थिर MVMElpPtr)(MVME_LPR_BASE)))

प्रकार काष्ठा अणु
	अचिन्हित अक्षर
		ctrl,
		bcd_sec,
		bcd_min,
		bcd_hr,
		bcd_करोw,
		bcd_करोm,
		bcd_mth,
		bcd_year;
पूर्ण MK48T08_t, *MK48T08ptr_t;

#घोषणा RTC_WRITE	0x80
#घोषणा RTC_READ	0x40
#घोषणा RTC_STOP	0x20

#घोषणा MVME_RTC_BASE	0xfffc1ff8

#घोषणा MVME_I596_BASE	0xfff46000

#घोषणा MVME_SCC_A_ADDR	0xfff45005
#घोषणा MVME_SCC_B_ADDR	0xfff45001
#घोषणा MVME_SCC_PCLK	10000000

#घोषणा MVME162_IRQ_TYPE_PRIO	0

#घोषणा MVME167_IRQ_PRN		(IRQ_USER+20)
#घोषणा MVME16x_IRQ_I596	(IRQ_USER+23)
#घोषणा MVME16x_IRQ_SCSI	(IRQ_USER+21)
#घोषणा MVME16x_IRQ_FLY		(IRQ_USER+63)
#घोषणा MVME167_IRQ_SER_ERR	(IRQ_USER+28)
#घोषणा MVME167_IRQ_SER_MODEM	(IRQ_USER+29)
#घोषणा MVME167_IRQ_SER_TX	(IRQ_USER+30)
#घोषणा MVME167_IRQ_SER_RX	(IRQ_USER+31)
#घोषणा MVME16x_IRQ_TIMER	(IRQ_USER+25)
#घोषणा MVME167_IRQ_ABORT	(IRQ_USER+46)
#घोषणा MVME162_IRQ_ABORT	(IRQ_USER+30)

/* SCC पूर्णांकerrupts, क्रम MVME162 */
#घोषणा MVME162_IRQ_SCC_BASE		(IRQ_USER+0)
#घोषणा MVME162_IRQ_SCCB_TX		(IRQ_USER+0)
#घोषणा MVME162_IRQ_SCCB_STAT		(IRQ_USER+2)
#घोषणा MVME162_IRQ_SCCB_RX		(IRQ_USER+4)
#घोषणा MVME162_IRQ_SCCB_SPCOND		(IRQ_USER+6)
#घोषणा MVME162_IRQ_SCCA_TX		(IRQ_USER+8)
#घोषणा MVME162_IRQ_SCCA_STAT		(IRQ_USER+10)
#घोषणा MVME162_IRQ_SCCA_RX		(IRQ_USER+12)
#घोषणा MVME162_IRQ_SCCA_SPCOND		(IRQ_USER+14)

/* MVME162 version रेजिस्टर */

#घोषणा MVME162_VERSION_REG	0xfff4202e

बाह्य अचिन्हित लघु mvme16x_config;

/* Lower 8 bits must match the revision रेजिस्टर in the MC2 chip */

#घोषणा MVME16x_CONFIG_SPEED_32		0x0001
#घोषणा MVME16x_CONFIG_NO_VMECHIP2	0x0002
#घोषणा MVME16x_CONFIG_NO_SCSICHIP	0x0004
#घोषणा MVME16x_CONFIG_NO_ETHERNET	0x0008
#घोषणा MVME16x_CONFIG_GOT_FPU		0x0010

#घोषणा MVME16x_CONFIG_GOT_LP		0x0100
#घोषणा MVME16x_CONFIG_GOT_CD2401	0x0200
#घोषणा MVME16x_CONFIG_GOT_SCCA		0x0400
#घोषणा MVME16x_CONFIG_GOT_SCCB		0x0800

#पूर्ण_अगर
