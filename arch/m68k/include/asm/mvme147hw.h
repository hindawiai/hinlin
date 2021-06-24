<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MVME147HW_H_
#घोषणा _MVME147HW_H_

#समावेश <यंत्र/irq.h>

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
पूर्ण MK48T02;

#घोषणा RTC_WRITE	0x80
#घोषणा RTC_READ	0x40
#घोषणा RTC_STOP	0x20

#घोषणा m147_rtc ((MK48T02 * अस्थिर)0xfffe07f8)


काष्ठा pcc_regs अणु
   अस्थिर u_दीर्घ	dma_tadr;
   अस्थिर u_दीर्घ	dma_dadr;
   अस्थिर u_दीर्घ	dma_bcr;
   अस्थिर u_दीर्घ	dma_hr;
   अस्थिर u_लघु	t1_preload;
   अस्थिर u_लघु	t1_count;
   अस्थिर u_लघु	t2_preload;
   अस्थिर u_लघु	t2_count;
   अस्थिर u_अक्षर	t1_पूर्णांक_cntrl;
   अस्थिर u_अक्षर	t1_cntrl;
   अस्थिर u_अक्षर	t2_पूर्णांक_cntrl;
   अस्थिर u_अक्षर	t2_cntrl;
   अस्थिर u_अक्षर	ac_fail;
   अस्थिर u_अक्षर	watchकरोg;
   अस्थिर u_अक्षर	lpt_पूर्णांकr;
   अस्थिर u_अक्षर	lpt_cntrl;
   अस्थिर u_अक्षर	dma_पूर्णांकr;
   अस्थिर u_अक्षर	dma_cntrl;
   अस्थिर u_अक्षर	bus_error;
   अस्थिर u_अक्षर	dma_status;
   अस्थिर u_अक्षर	पात;
   अस्थिर u_अक्षर	ta_fnctl;
   अस्थिर u_अक्षर	serial_cntrl;
   अस्थिर u_अक्षर	general_cntrl;
   अस्थिर u_अक्षर	lan_cntrl;
   अस्थिर u_अक्षर	general_status;
   अस्थिर u_अक्षर	scsi_पूर्णांकerrupt;
   अस्थिर u_अक्षर	slave;
   अस्थिर u_अक्षर	soft1_cntrl;
   अस्थिर u_अक्षर	पूर्णांक_base;
   अस्थिर u_अक्षर	soft2_cntrl;
   अस्थिर u_अक्षर	revision_level;
   अस्थिर u_अक्षर	lpt_data;
   अस्थिर u_अक्षर	lpt_status;
   पूर्ण;

#घोषणा m147_pcc ((काष्ठा pcc_regs * अस्थिर)0xfffe1000)


#घोषणा PCC_INT_ENAB		0x08

#घोषणा PCC_TIMER_INT_CLR	0x80

#घोषणा PCC_TIMER_TIC_EN	0x01
#घोषणा PCC_TIMER_COC_EN	0x02
#घोषणा PCC_TIMER_CLR_OVF	0x04

#घोषणा PCC_LEVEL_ABORT		0x07
#घोषणा PCC_LEVEL_SERIAL	0x04
#घोषणा PCC_LEVEL_ETH		0x04
#घोषणा PCC_LEVEL_TIMER1	0x04
#घोषणा PCC_LEVEL_SCSI_PORT	0x04
#घोषणा PCC_LEVEL_SCSI_DMA	0x04

#घोषणा PCC_IRQ_AC_FAIL		(IRQ_USER+0)
#घोषणा PCC_IRQ_BERR		(IRQ_USER+1)
#घोषणा PCC_IRQ_ABORT		(IRQ_USER+2)
/* #घोषणा PCC_IRQ_SERIAL	(IRQ_USER+3) */
#घोषणा PCC_IRQ_PRINTER		(IRQ_USER+7)
#घोषणा PCC_IRQ_TIMER1		(IRQ_USER+8)
#घोषणा PCC_IRQ_TIMER2		(IRQ_USER+9)
#घोषणा PCC_IRQ_SOFTWARE1	(IRQ_USER+10)
#घोषणा PCC_IRQ_SOFTWARE2	(IRQ_USER+11)


#घोषणा M147_SCC_A_ADDR		0xfffe3002
#घोषणा M147_SCC_B_ADDR		0xfffe3000
#घोषणा M147_SCC_PCLK		5000000

#घोषणा MVME147_IRQ_SCSI_PORT	(IRQ_USER+0x45)
#घोषणा MVME147_IRQ_SCSI_DMA	(IRQ_USER+0x46)

/* SCC पूर्णांकerrupts, क्रम MVME147 */

#घोषणा MVME147_IRQ_TYPE_PRIO	0
#घोषणा MVME147_IRQ_SCC_BASE		(IRQ_USER+32)
#घोषणा MVME147_IRQ_SCCB_TX		(IRQ_USER+32)
#घोषणा MVME147_IRQ_SCCB_STAT		(IRQ_USER+34)
#घोषणा MVME147_IRQ_SCCB_RX		(IRQ_USER+36)
#घोषणा MVME147_IRQ_SCCB_SPCOND		(IRQ_USER+38)
#घोषणा MVME147_IRQ_SCCA_TX		(IRQ_USER+40)
#घोषणा MVME147_IRQ_SCCA_STAT		(IRQ_USER+42)
#घोषणा MVME147_IRQ_SCCA_RX		(IRQ_USER+44)
#घोषणा MVME147_IRQ_SCCA_SPCOND		(IRQ_USER+46)

#घोषणा MVME147_LANCE_BASE	0xfffe1800
#घोषणा MVME147_LANCE_IRQ	(IRQ_USER+4)

#घोषणा ETHERNET_ADDRESS 0xfffe0778

#पूर्ण_अगर
