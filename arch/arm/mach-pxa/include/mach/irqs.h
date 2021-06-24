<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-pxa/include/mach/irqs.h
 *
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */
#अगर_अघोषित __ASM_MACH_IRQS_H
#घोषणा __ASM_MACH_IRQS_H

#समावेश <यंत्र/irq.h>

#घोषणा PXA_ISA_IRQ(x)	(x)
#घोषणा PXA_IRQ(x)	(NR_IRQS_LEGACY + (x))

#घोषणा IRQ_SSP3	PXA_IRQ(0)	/* SSP3 service request */
#घोषणा IRQ_MSL		PXA_IRQ(1)	/* MSL Interface पूर्णांकerrupt */
#घोषणा IRQ_USBH2	PXA_IRQ(2)	/* USB Host पूर्णांकerrupt 1 (OHCI,PXA27x) */
#घोषणा IRQ_USBH1	PXA_IRQ(3)	/* USB Host पूर्णांकerrupt 2 (non-OHCI,PXA27x) */
#घोषणा IRQ_KEYPAD	PXA_IRQ(4)	/* Key pad controller */
#घोषणा IRQ_MEMSTK	PXA_IRQ(5)	/* Memory Stick पूर्णांकerrupt (PXA27x) */
#घोषणा IRQ_ACIPC0	PXA_IRQ(5)	/* AP-CP Communication (PXA930) */
#घोषणा IRQ_PWRI2C	PXA_IRQ(6)	/* Power I2C पूर्णांकerrupt */
#घोषणा IRQ_HWUART	PXA_IRQ(7)	/* HWUART Transmit/Receive/Error (PXA26x) */
#घोषणा IRQ_OST_4_11	PXA_IRQ(7)	/* OS समयr 4-11 matches (PXA27x) */
#घोषणा	IRQ_GPIO0	PXA_IRQ(8)	/* GPIO0 Edge Detect */
#घोषणा	IRQ_GPIO1	PXA_IRQ(9)	/* GPIO1 Edge Detect */
#घोषणा	IRQ_GPIO_2_x	PXA_IRQ(10)	/* GPIO[2-x] Edge Detect */
#घोषणा	IRQ_USB		PXA_IRQ(11)	/* USB Service */
#घोषणा	IRQ_PMU		PXA_IRQ(12)	/* Perक्रमmance Monitoring Unit */
#घोषणा	IRQ_I2S		PXA_IRQ(13)	/* I2S Interrupt (PXA27x) */
#घोषणा IRQ_SSP4	PXA_IRQ(13)	/* SSP4 service request (PXA3xx) */
#घोषणा	IRQ_AC97	PXA_IRQ(14)	/* AC97 Interrupt */
#घोषणा IRQ_ASSP	PXA_IRQ(15)	/* Audio SSP Service Request (PXA25x) */
#घोषणा IRQ_USIM	PXA_IRQ(15)     /* Smart Card पूर्णांकerface पूर्णांकerrupt (PXA27x) */
#घोषणा IRQ_NSSP	PXA_IRQ(16)	/* Network SSP Service Request (PXA25x) */
#घोषणा IRQ_SSP2	PXA_IRQ(16)	/* SSP2 पूर्णांकerrupt (PXA27x) */
#घोषणा	IRQ_LCD		PXA_IRQ(17)	/* LCD Controller Service Request */
#घोषणा	IRQ_I2C		PXA_IRQ(18)	/* I2C Service Request */
#घोषणा	IRQ_ICP		PXA_IRQ(19)	/* ICP Transmit/Receive/Error */
#घोषणा IRQ_ACIPC2	PXA_IRQ(19)	/* AP-CP Communication (PXA930) */
#घोषणा	IRQ_STUART	PXA_IRQ(20)	/* STUART Transmit/Receive/Error */
#घोषणा	IRQ_BTUART	PXA_IRQ(21)	/* BTUART Transmit/Receive/Error */
#घोषणा	IRQ_FFUART	PXA_IRQ(22)	/* FFUART Transmit/Receive/Error*/
#घोषणा	IRQ_MMC		PXA_IRQ(23)	/* MMC Status/Error Detection */
#घोषणा	IRQ_SSP		PXA_IRQ(24)	/* SSP Service Request */
#घोषणा	IRQ_DMA 	PXA_IRQ(25)	/* DMA Channel Service Request */
#घोषणा	IRQ_OST0 	PXA_IRQ(26)	/* OS Timer match 0 */
#घोषणा	IRQ_OST1 	PXA_IRQ(27)	/* OS Timer match 1 */
#घोषणा	IRQ_OST2 	PXA_IRQ(28)	/* OS Timer match 2 */
#घोषणा	IRQ_OST3 	PXA_IRQ(29)	/* OS Timer match 3 */
#घोषणा	IRQ_RTC1Hz	PXA_IRQ(30)	/* RTC HZ Clock Tick */
#घोषणा	IRQ_RTCAlrm	PXA_IRQ(31)	/* RTC Alarm */

#घोषणा IRQ_TPM		PXA_IRQ(32)	/* TPM पूर्णांकerrupt */
#घोषणा IRQ_CAMERA	PXA_IRQ(33)	/* Camera Interface */
#घोषणा IRQ_CIR		PXA_IRQ(34)	/* Consumer IR */
#घोषणा IRQ_COMM_WDT	PXA_IRQ(35) 	/* Comm WDT पूर्णांकerrupt */
#घोषणा IRQ_TSI		PXA_IRQ(36)	/* Touch Screen Interface (PXA320) */
#घोषणा IRQ_ENHROT	PXA_IRQ(37)	/* Enhanced Rotary (PXA930) */
#घोषणा IRQ_USIM2	PXA_IRQ(38)	/* USIM2 Controller */
#घोषणा IRQ_GCU		PXA_IRQ(39)	/* Graphics Controller (PXA3xx) */
#घोषणा IRQ_ACIPC1	PXA_IRQ(40)	/* AP-CP Communication (PXA930) */
#घोषणा IRQ_MMC2	PXA_IRQ(41)	/* MMC2 Controller */
#घोषणा IRQ_TRKBALL	PXA_IRQ(43)	/* Track Ball (PXA930) */
#घोषणा IRQ_1WIRE	PXA_IRQ(44)	/* 1-Wire Controller */
#घोषणा IRQ_न_अंकD	PXA_IRQ(45)	/* न_अंकD Controller */
#घोषणा IRQ_USB2	PXA_IRQ(46)	/* USB 2.0 Device Controller */
#घोषणा IRQ_WAKEUP0	PXA_IRQ(49)	/* EXT_WAKEUP0 */
#घोषणा IRQ_WAKEUP1	PXA_IRQ(50)	/* EXT_WAKEUP1 */
#घोषणा IRQ_DMEMC	PXA_IRQ(51)	/* Dynamic Memory Controller */
#घोषणा IRQ_MMC3	PXA_IRQ(55)	/* MMC3 Controller (PXA310) */

#घोषणा IRQ_U2O		PXA_IRQ(64)	/* USB OTG 2.0 Controller (PXA935) */
#घोषणा IRQ_U2H		PXA_IRQ(65)	/* USB Host 2.0 Controller (PXA935) */
#घोषणा IRQ_PXA935_MMC0	PXA_IRQ(72)	/* MMC0 Controller (PXA935) */
#घोषणा IRQ_PXA935_MMC1	PXA_IRQ(73)	/* MMC1 Controller (PXA935) */
#घोषणा IRQ_PXA935_MMC2	PXA_IRQ(74)	/* MMC2 Controller (PXA935) */
#घोषणा IRQ_U2P		PXA_IRQ(93)	/* USB PHY D+/D- Lines (PXA935) */

#घोषणा PXA_GPIO_IRQ_BASE	PXA_IRQ(96)
#घोषणा PXA_NR_BUILTIN_GPIO	(192)
#घोषणा PXA_GPIO_TO_IRQ(x)	(PXA_GPIO_IRQ_BASE + (x))

/*
 * The following पूर्णांकerrupts are क्रम board specअगरic purposes. Since
 * the kernel can only run on one machine at a समय, we can re-use
 * these.
 * By शेष, no board IRQ is reserved. It should be finished in
 * custom board since sparse IRQ is alपढ़ोy enabled.
 */
#घोषणा IRQ_BOARD_START		(PXA_GPIO_IRQ_BASE + PXA_NR_BUILTIN_GPIO)

#घोषणा PXA_NR_IRQS		(IRQ_BOARD_START)

#अगर_अघोषित __ASSEMBLY__
काष्ठा irq_data;
काष्ठा pt_regs;

व्योम pxa_mask_irq(काष्ठा irq_data *);
व्योम pxa_unmask_irq(काष्ठा irq_data *);
व्योम icip_handle_irq(काष्ठा pt_regs *);
व्योम ichp_handle_irq(काष्ठा pt_regs *);

व्योम pxa_init_irq(पूर्णांक irq_nr, पूर्णांक (*set_wake)(काष्ठा irq_data *, अचिन्हित पूर्णांक));
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_IRQS_H */
