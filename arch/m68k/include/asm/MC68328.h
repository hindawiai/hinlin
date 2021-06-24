<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* include/यंत्र-m68knommu/MC68328.h: '328 control रेजिस्टरs
 *
 * Copyright (C) 1999  Vladimir Gurevich <vgurevic@cisco.com>
 *                     Bear & Hare Software, Inc.
 *
 * Based on include/यंत्र-m68knommu/MC68332.h
 * Copyright (C) 1998  Kenneth Albanowski <kjahds@kjahds.com>,
 *
 */
#समावेश <linux/compiler.h>

#अगर_अघोषित _MC68328_H_
#घोषणा _MC68328_H_

#घोषणा BYTE_REF(addr) (*((अस्थिर अचिन्हित अक्षर*)addr))
#घोषणा WORD_REF(addr) (*((अस्थिर अचिन्हित लघु*)addr))
#घोषणा LONG_REF(addr) (*((अस्थिर अचिन्हित दीर्घ*)addr))

#घोषणा PUT_FIELD(field, val) (((val) << field##_SHIFT) & field##_MASK)
#घोषणा GET_FIELD(reg, field) (((reg) & field##_MASK) >> field##_SHIFT)

/********** 
 *
 * 0xFFFFF0xx -- System Control
 *
 **********/
 
/*
 * System Control Register (SCR)
 */
#घोषणा SCR_ADDR	0xfffff000
#घोषणा SCR		BYTE_REF(SCR_ADDR)

#घोषणा SCR_WDTH8	0x01	/* 8-Bit Width Select */
#घोषणा SCR_DMAP	0x04	/* Double Map */
#घोषणा SCR_SO		0x08	/* Supervisor Only */
#घोषणा SCR_BETEN	0x10	/* Bus-Error Time-Out Enable */
#घोषणा SCR_PRV		0x20	/* Privilege Violation */
#घोषणा SCR_WPV		0x40	/* Write Protect Violation */
#घोषणा SCR_BETO	0x80	/* Bus-Error TimeOut */

/*
 * Mask Revision Register
 */
#घोषणा MRR_ADDR 0xfffff004
#घोषणा MRR      LONG_REF(MRR_ADDR)
 
/********** 
 *
 * 0xFFFFF1xx -- Chip-Select logic
 *
 **********/

/********** 
 *
 * 0xFFFFF2xx -- Phase Locked Loop (PLL) & Power Control
 *
 **********/

/*
 * Group Base Address Registers
 */
#घोषणा GRPBASEA_ADDR	0xfffff100
#घोषणा GRPBASEB_ADDR	0xfffff102
#घोषणा GRPBASEC_ADDR	0xfffff104
#घोषणा GRPBASED_ADDR	0xfffff106

#घोषणा GRPBASEA	WORD_REF(GRPBASEA_ADDR)
#घोषणा GRPBASEB	WORD_REF(GRPBASEB_ADDR)
#घोषणा GRPBASEC	WORD_REF(GRPBASEC_ADDR)
#घोषणा GRPBASED	WORD_REF(GRPBASED_ADDR)

#घोषणा GRPBASE_V	  0x0001	/* Valid */
#घोषणा GRPBASE_GBA_MASK  0xfff0	/* Group Base Address (bits 31-20) */

/*
 * Group Base Address Mask Registers 
 */
#घोषणा GRPMASKA_ADDR	0xfffff108
#घोषणा GRPMASKB_ADDR	0xfffff10a
#घोषणा GRPMASKC_ADDR	0xfffff10c
#घोषणा GRPMASKD_ADDR	0xfffff10e

#घोषणा GRPMASKA	WORD_REF(GRPMASKA_ADDR)
#घोषणा GRPMASKB	WORD_REF(GRPMASKB_ADDR)
#घोषणा GRPMASKC	WORD_REF(GRPMASKC_ADDR)
#घोषणा GRPMASKD	WORD_REF(GRPMASKD_ADDR)

#घोषणा GRMMASK_GMA_MASK 0xfffff0	/* Group Base Mask (bits 31-20) */

/*
 * Chip-Select Option Registers (group A)
 */
#घोषणा CSA0_ADDR	0xfffff110
#घोषणा CSA1_ADDR	0xfffff114
#घोषणा CSA2_ADDR	0xfffff118
#घोषणा CSA3_ADDR	0xfffff11c

#घोषणा CSA0		LONG_REF(CSA0_ADDR)
#घोषणा CSA1		LONG_REF(CSA1_ADDR)
#घोषणा CSA2		LONG_REF(CSA2_ADDR)
#घोषणा CSA3		LONG_REF(CSA3_ADDR)

#घोषणा CSA_WAIT_MASK	0x00000007	/* Wait State Selection */
#घोषणा CSA_WAIT_SHIFT	0
#घोषणा CSA_RO		0x00000008	/* Read-Only */
#घोषणा CSA_AM_MASK	0x0000ff00	/* Address Mask (bits 23-16) */
#घोषणा CSA_AM_SHIFT	8
#घोषणा CSA_BUSW	0x00010000	/* Bus Width Select */
#घोषणा CSA_AC_MASK	0xff000000	/* Address Compare (bits 23-16) */
#घोषणा CSA_AC_SHIFT	24

/*
 * Chip-Select Option Registers (group B)
 */
#घोषणा CSB0_ADDR	0xfffff120
#घोषणा CSB1_ADDR	0xfffff124
#घोषणा CSB2_ADDR	0xfffff128
#घोषणा CSB3_ADDR	0xfffff12c

#घोषणा CSB0		LONG_REF(CSB0_ADDR)
#घोषणा CSB1		LONG_REF(CSB1_ADDR)
#घोषणा CSB2		LONG_REF(CSB2_ADDR)
#घोषणा CSB3		LONG_REF(CSB3_ADDR)

#घोषणा CSB_WAIT_MASK	0x00000007	/* Wait State Selection */
#घोषणा CSB_WAIT_SHIFT	0
#घोषणा CSB_RO		0x00000008	/* Read-Only */
#घोषणा CSB_AM_MASK	0x0000ff00	/* Address Mask (bits 23-16) */
#घोषणा CSB_AM_SHIFT	8
#घोषणा CSB_BUSW	0x00010000	/* Bus Width Select */
#घोषणा CSB_AC_MASK	0xff000000	/* Address Compare (bits 23-16) */
#घोषणा CSB_AC_SHIFT	24

/*
 * Chip-Select Option Registers (group C)
 */
#घोषणा CSC0_ADDR	0xfffff130
#घोषणा CSC1_ADDR	0xfffff134
#घोषणा CSC2_ADDR	0xfffff138
#घोषणा CSC3_ADDR	0xfffff13c

#घोषणा CSC0		LONG_REF(CSC0_ADDR)
#घोषणा CSC1		LONG_REF(CSC1_ADDR)
#घोषणा CSC2		LONG_REF(CSC2_ADDR)
#घोषणा CSC3		LONG_REF(CSC3_ADDR)

#घोषणा CSC_WAIT_MASK	0x00000007	/* Wait State Selection */
#घोषणा CSC_WAIT_SHIFT	0
#घोषणा CSC_RO		0x00000008	/* Read-Only */
#घोषणा CSC_AM_MASK	0x0000fff0	/* Address Mask (bits 23-12) */
#घोषणा CSC_AM_SHIFT	4
#घोषणा CSC_BUSW	0x00010000	/* Bus Width Select */
#घोषणा CSC_AC_MASK	0xfff00000	/* Address Compare (bits 23-12) */
#घोषणा CSC_AC_SHIFT	20

/*
 * Chip-Select Option Registers (group D)
 */
#घोषणा CSD0_ADDR	0xfffff140
#घोषणा CSD1_ADDR	0xfffff144
#घोषणा CSD2_ADDR	0xfffff148
#घोषणा CSD3_ADDR	0xfffff14c

#घोषणा CSD0		LONG_REF(CSD0_ADDR)
#घोषणा CSD1		LONG_REF(CSD1_ADDR)
#घोषणा CSD2		LONG_REF(CSD2_ADDR)
#घोषणा CSD3		LONG_REF(CSD3_ADDR)

#घोषणा CSD_WAIT_MASK	0x00000007	/* Wait State Selection */
#घोषणा CSD_WAIT_SHIFT	0
#घोषणा CSD_RO		0x00000008	/* Read-Only */
#घोषणा CSD_AM_MASK	0x0000fff0	/* Address Mask (bits 23-12) */
#घोषणा CSD_AM_SHIFT	4
#घोषणा CSD_BUSW	0x00010000	/* Bus Width Select */
#घोषणा CSD_AC_MASK	0xfff00000	/* Address Compare (bits 23-12) */
#घोषणा CSD_AC_SHIFT	20

/**********
 *
 * 0xFFFFF2xx -- Phase Locked Loop (PLL) & Power Control
 *
 **********/
 
/*
 * PLL Control Register 
 */
#घोषणा PLLCR_ADDR	0xfffff200
#घोषणा PLLCR		WORD_REF(PLLCR_ADDR)

#घोषणा PLLCR_DISPLL	       0x0008	/* Disable PLL */
#घोषणा PLLCR_CLKEN	       0x0010	/* Clock (CLKO pin) enable */
#घोषणा PLLCR_SYSCLK_SEL_MASK  0x0700	/* System Clock Selection */
#घोषणा PLLCR_SYSCLK_SEL_SHIFT 8
#घोषणा PLLCR_PIXCLK_SEL_MASK  0x3800	/* LCD Clock Selection */
#घोषणा PLLCR_PIXCLK_SEL_SHIFT 11

/* 'EZ328-compatible definitions */
#घोषणा PLLCR_LCDCLK_SEL_MASK	PLLCR_PIXCLK_SEL_MASK
#घोषणा PLLCR_LCDCLK_SEL_SHIFT	PLLCR_PIXCLK_SEL_SHIFT

/*
 * PLL Frequency Select Register
 */
#घोषणा PLLFSR_ADDR	0xfffff202
#घोषणा PLLFSR		WORD_REF(PLLFSR_ADDR)

#घोषणा PLLFSR_PC_MASK	0x00ff		/* P Count */
#घोषणा PLLFSR_PC_SHIFT 0
#घोषणा PLLFSR_QC_MASK	0x0f00		/* Q Count */
#घोषणा PLLFSR_QC_SHIFT 8
#घोषणा PLLFSR_PROT	0x4000		/* Protect P & Q */
#घोषणा PLLFSR_CLK32	0x8000		/* Clock 32 (kHz) */

/*
 * Power Control Register
 */
#घोषणा PCTRL_ADDR	0xfffff207
#घोषणा PCTRL		BYTE_REF(PCTRL_ADDR)

#घोषणा PCTRL_WIDTH_MASK	0x1f	/* CPU Clock bursts width */
#घोषणा PCTRL_WIDTH_SHIFT	0
#घोषणा PCTRL_STOP		0x40	/* Enter घातer-save mode immediately */ 
#घोषणा PCTRL_PCEN		0x80	/* Power Control Enable */

/**********
 *
 * 0xFFFFF3xx -- Interrupt Controller
 *
 **********/

/* 
 * Interrupt Vector Register
 */
#घोषणा IVR_ADDR	0xfffff300
#घोषणा IVR		BYTE_REF(IVR_ADDR)

#घोषणा IVR_VECTOR_MASK 0xF8

/*
 * Interrupt control Register
 */
#घोषणा ICR_ADRR	0xfffff302
#घोषणा ICR		WORD_REF(ICR_ADDR)

#घोषणा ICR_ET6		0x0100	/* Edge Trigger Select क्रम IRQ6 */
#घोषणा ICR_ET3		0x0200	/* Edge Trigger Select क्रम IRQ3 */
#घोषणा ICR_ET2		0x0400	/* Edge Trigger Select क्रम IRQ2 */
#घोषणा ICR_ET1		0x0800	/* Edge Trigger Select क्रम IRQ1 */
#घोषणा ICR_POL6	0x1000	/* Polarity Control क्रम IRQ6 */
#घोषणा ICR_POL3	0x2000	/* Polarity Control क्रम IRQ3 */
#घोषणा ICR_POL2	0x4000	/* Polarity Control क्रम IRQ2 */
#घोषणा ICR_POL1	0x8000	/* Polarity Control क्रम IRQ1 */

/*
 * Interrupt Mask Register
 */
#घोषणा IMR_ADDR	0xfffff304
#घोषणा IMR		LONG_REF(IMR_ADDR)
 
/*
 * Define the names क्रम bit positions first. This is useful क्रम
 * request_irq
 */
#घोषणा SPIM_IRQ_NUM	0	/* SPI Master पूर्णांकerrupt */
#घोषणा	TMR2_IRQ_NUM	1	/* Timer 2 पूर्णांकerrupt */
#घोषणा UART_IRQ_NUM	2	/* UART पूर्णांकerrupt */	
#घोषणा	WDT_IRQ_NUM	3	/* Watchकरोg Timer पूर्णांकerrupt */
#घोषणा RTC_IRQ_NUM	4	/* RTC पूर्णांकerrupt */
#घोषणा	KB_IRQ_NUM	6	/* Keyboard Interrupt */
#घोषणा PWM_IRQ_NUM	7	/* Pulse-Width Modulator पूर्णांक. */
#घोषणा	INT0_IRQ_NUM	8	/* External INT0 */
#घोषणा	INT1_IRQ_NUM	9	/* External INT1 */
#घोषणा	INT2_IRQ_NUM	10	/* External INT2 */
#घोषणा	INT3_IRQ_NUM	11	/* External INT3 */
#घोषणा	INT4_IRQ_NUM	12	/* External INT4 */
#घोषणा	INT5_IRQ_NUM	13	/* External INT5 */
#घोषणा	INT6_IRQ_NUM	14	/* External INT6 */
#घोषणा	INT7_IRQ_NUM	15	/* External INT7 */
#घोषणा IRQ1_IRQ_NUM	16	/* IRQ1 */
#घोषणा IRQ2_IRQ_NUM	17	/* IRQ2 */
#घोषणा IRQ3_IRQ_NUM	18	/* IRQ3 */
#घोषणा IRQ6_IRQ_NUM	19	/* IRQ6 */
#घोषणा PEN_IRQ_NUM	20	/* Pen Interrupt */
#घोषणा SPIS_IRQ_NUM	21	/* SPI Slave Interrupt */
#घोषणा TMR1_IRQ_NUM	22	/* Timer 1 पूर्णांकerrupt */
#घोषणा IRQ7_IRQ_NUM	23	/* IRQ7 */

/* '328-compatible definitions */
#घोषणा SPI_IRQ_NUM	SPIM_IRQ_NUM
#घोषणा TMR_IRQ_NUM	TMR1_IRQ_NUM
 
/*
 * Here go the biपंचांगasks themselves
 */
#घोषणा IMR_MSPIM 	(1 << SPIM_IRQ_NUM)	/* Mask SPI Master पूर्णांकerrupt */
#घोषणा	IMR_MTMR2	(1 << TMR2_IRQ_NUM)	/* Mask Timer 2 पूर्णांकerrupt */
#घोषणा IMR_MUART	(1 << UART_IRQ_NUM)	/* Mask UART पूर्णांकerrupt */	
#घोषणा	IMR_MWDT	(1 << WDT_IRQ_NUM)	/* Mask Watchकरोg Timer पूर्णांकerrupt */
#घोषणा IMR_MRTC	(1 << RTC_IRQ_NUM)	/* Mask RTC पूर्णांकerrupt */
#घोषणा	IMR_MKB		(1 << KB_IRQ_NUM)	/* Mask Keyboard Interrupt */
#घोषणा IMR_MPWM	(1 << PWM_IRQ_NUM)	/* Mask Pulse-Width Modulator पूर्णांक. */
#घोषणा	IMR_MINT0	(1 << INT0_IRQ_NUM)	/* Mask External INT0 */
#घोषणा	IMR_MINT1	(1 << INT1_IRQ_NUM)	/* Mask External INT1 */
#घोषणा	IMR_MINT2	(1 << INT2_IRQ_NUM)	/* Mask External INT2 */
#घोषणा	IMR_MINT3	(1 << INT3_IRQ_NUM)	/* Mask External INT3 */
#घोषणा	IMR_MINT4	(1 << INT4_IRQ_NUM)	/* Mask External INT4 */
#घोषणा	IMR_MINT5	(1 << INT5_IRQ_NUM)	/* Mask External INT5 */
#घोषणा	IMR_MINT6	(1 << INT6_IRQ_NUM)	/* Mask External INT6 */
#घोषणा	IMR_MINT7	(1 << INT7_IRQ_NUM)	/* Mask External INT7 */
#घोषणा IMR_MIRQ1	(1 << IRQ1_IRQ_NUM)	/* Mask IRQ1 */
#घोषणा IMR_MIRQ2	(1 << IRQ2_IRQ_NUM)	/* Mask IRQ2 */
#घोषणा IMR_MIRQ3	(1 << IRQ3_IRQ_NUM)	/* Mask IRQ3 */
#घोषणा IMR_MIRQ6	(1 << IRQ6_IRQ_NUM)	/* Mask IRQ6 */
#घोषणा IMR_MPEN	(1 << PEN_IRQ_NUM)	/* Mask Pen Interrupt */
#घोषणा IMR_MSPIS	(1 << SPIS_IRQ_NUM)	/* Mask SPI Slave Interrupt */
#घोषणा IMR_MTMR1	(1 << TMR1_IRQ_NUM)	/* Mask Timer 1 पूर्णांकerrupt */
#घोषणा IMR_MIRQ7	(1 << IRQ7_IRQ_NUM)	/* Mask IRQ7 */

/* 'EZ328-compatible definitions */
#घोषणा IMR_MSPI	IMR_MSPIM
#घोषणा IMR_MTMR	IMR_MTMR1

/* 
 * Interrupt Wake-Up Enable Register
 */
#घोषणा IWR_ADDR	0xfffff308
#घोषणा IWR		LONG_REF(IWR_ADDR)

#घोषणा IWR_SPIM 	(1 << SPIM_IRQ_NUM)	/* SPI Master पूर्णांकerrupt */
#घोषणा	IWR_TMR2	(1 << TMR2_IRQ_NUM)	/* Timer 2 पूर्णांकerrupt */
#घोषणा IWR_UART	(1 << UART_IRQ_NUM)	/* UART पूर्णांकerrupt */	
#घोषणा	IWR_WDT		(1 << WDT_IRQ_NUM)	/* Watchकरोg Timer पूर्णांकerrupt */
#घोषणा IWR_RTC		(1 << RTC_IRQ_NUM)	/* RTC पूर्णांकerrupt */
#घोषणा	IWR_KB		(1 << KB_IRQ_NUM)	/* Keyboard Interrupt */
#घोषणा IWR_PWM		(1 << PWM_IRQ_NUM)	/* Pulse-Width Modulator पूर्णांक. */
#घोषणा	IWR_INT0	(1 << INT0_IRQ_NUM)	/* External INT0 */
#घोषणा	IWR_INT1	(1 << INT1_IRQ_NUM)	/* External INT1 */
#घोषणा	IWR_INT2	(1 << INT2_IRQ_NUM)	/* External INT2 */
#घोषणा	IWR_INT3	(1 << INT3_IRQ_NUM)	/* External INT3 */
#घोषणा	IWR_INT4	(1 << INT4_IRQ_NUM)	/* External INT4 */
#घोषणा	IWR_INT5	(1 << INT5_IRQ_NUM)	/* External INT5 */
#घोषणा	IWR_INT6	(1 << INT6_IRQ_NUM)	/* External INT6 */
#घोषणा	IWR_INT7	(1 << INT7_IRQ_NUM)	/* External INT7 */
#घोषणा IWR_IRQ1	(1 << IRQ1_IRQ_NUM)	/* IRQ1 */
#घोषणा IWR_IRQ2	(1 << IRQ2_IRQ_NUM)	/* IRQ2 */
#घोषणा IWR_IRQ3	(1 << IRQ3_IRQ_NUM)	/* IRQ3 */
#घोषणा IWR_IRQ6	(1 << IRQ6_IRQ_NUM)	/* IRQ6 */
#घोषणा IWR_PEN		(1 << PEN_IRQ_NUM)	/* Pen Interrupt */
#घोषणा IWR_SPIS	(1 << SPIS_IRQ_NUM)	/* SPI Slave Interrupt */
#घोषणा IWR_TMR1	(1 << TMR1_IRQ_NUM)	/* Timer 1 पूर्णांकerrupt */
#घोषणा IWR_IRQ7	(1 << IRQ7_IRQ_NUM)	/* IRQ7 */

/* 
 * Interrupt Status Register 
 */
#घोषणा ISR_ADDR	0xfffff30c
#घोषणा ISR		LONG_REF(ISR_ADDR)

#घोषणा ISR_SPIM 	(1 << SPIM_IRQ_NUM)	/* SPI Master पूर्णांकerrupt */
#घोषणा	ISR_TMR2	(1 << TMR2_IRQ_NUM)	/* Timer 2 पूर्णांकerrupt */
#घोषणा ISR_UART	(1 << UART_IRQ_NUM)	/* UART पूर्णांकerrupt */	
#घोषणा	ISR_WDT		(1 << WDT_IRQ_NUM)	/* Watchकरोg Timer पूर्णांकerrupt */
#घोषणा ISR_RTC		(1 << RTC_IRQ_NUM)	/* RTC पूर्णांकerrupt */
#घोषणा	ISR_KB		(1 << KB_IRQ_NUM)	/* Keyboard Interrupt */
#घोषणा ISR_PWM		(1 << PWM_IRQ_NUM)	/* Pulse-Width Modulator पूर्णांक. */
#घोषणा	ISR_INT0	(1 << INT0_IRQ_NUM)	/* External INT0 */
#घोषणा	ISR_INT1	(1 << INT1_IRQ_NUM)	/* External INT1 */
#घोषणा	ISR_INT2	(1 << INT2_IRQ_NUM)	/* External INT2 */
#घोषणा	ISR_INT3	(1 << INT3_IRQ_NUM)	/* External INT3 */
#घोषणा	ISR_INT4	(1 << INT4_IRQ_NUM)	/* External INT4 */
#घोषणा	ISR_INT5	(1 << INT5_IRQ_NUM)	/* External INT5 */
#घोषणा	ISR_INT6	(1 << INT6_IRQ_NUM)	/* External INT6 */
#घोषणा	ISR_INT7	(1 << INT7_IRQ_NUM)	/* External INT7 */
#घोषणा ISR_IRQ1	(1 << IRQ1_IRQ_NUM)	/* IRQ1 */
#घोषणा ISR_IRQ2	(1 << IRQ2_IRQ_NUM)	/* IRQ2 */
#घोषणा ISR_IRQ3	(1 << IRQ3_IRQ_NUM)	/* IRQ3 */
#घोषणा ISR_IRQ6	(1 << IRQ6_IRQ_NUM)	/* IRQ6 */
#घोषणा ISR_PEN		(1 << PEN_IRQ_NUM)	/* Pen Interrupt */
#घोषणा ISR_SPIS	(1 << SPIS_IRQ_NUM)	/* SPI Slave Interrupt */
#घोषणा ISR_TMR1	(1 << TMR1_IRQ_NUM)	/* Timer 1 पूर्णांकerrupt */
#घोषणा ISR_IRQ7	(1 << IRQ7_IRQ_NUM)	/* IRQ7 */

/* 'EZ328-compatible definitions */
#घोषणा ISR_SPI	ISR_SPIM
#घोषणा ISR_TMR	ISR_TMR1

/* 
 * Interrupt Pending Register 
 */
#घोषणा IPR_ADDR	0xfffff310
#घोषणा IPR		LONG_REF(IPR_ADDR)

#घोषणा IPR_SPIM 	(1 << SPIM_IRQ_NUM)	/* SPI Master पूर्णांकerrupt */
#घोषणा	IPR_TMR2	(1 << TMR2_IRQ_NUM)	/* Timer 2 पूर्णांकerrupt */
#घोषणा IPR_UART	(1 << UART_IRQ_NUM)	/* UART पूर्णांकerrupt */	
#घोषणा	IPR_WDT		(1 << WDT_IRQ_NUM)	/* Watchकरोg Timer पूर्णांकerrupt */
#घोषणा IPR_RTC		(1 << RTC_IRQ_NUM)	/* RTC पूर्णांकerrupt */
#घोषणा	IPR_KB		(1 << KB_IRQ_NUM)	/* Keyboard Interrupt */
#घोषणा IPR_PWM		(1 << PWM_IRQ_NUM)	/* Pulse-Width Modulator पूर्णांक. */
#घोषणा	IPR_INT0	(1 << INT0_IRQ_NUM)	/* External INT0 */
#घोषणा	IPR_INT1	(1 << INT1_IRQ_NUM)	/* External INT1 */
#घोषणा	IPR_INT2	(1 << INT2_IRQ_NUM)	/* External INT2 */
#घोषणा	IPR_INT3	(1 << INT3_IRQ_NUM)	/* External INT3 */
#घोषणा	IPR_INT4	(1 << INT4_IRQ_NUM)	/* External INT4 */
#घोषणा	IPR_INT5	(1 << INT5_IRQ_NUM)	/* External INT5 */
#घोषणा	IPR_INT6	(1 << INT6_IRQ_NUM)	/* External INT6 */
#घोषणा	IPR_INT7	(1 << INT7_IRQ_NUM)	/* External INT7 */
#घोषणा IPR_IRQ1	(1 << IRQ1_IRQ_NUM)	/* IRQ1 */
#घोषणा IPR_IRQ2	(1 << IRQ2_IRQ_NUM)	/* IRQ2 */
#घोषणा IPR_IRQ3	(1 << IRQ3_IRQ_NUM)	/* IRQ3 */
#घोषणा IPR_IRQ6	(1 << IRQ6_IRQ_NUM)	/* IRQ6 */
#घोषणा IPR_PEN		(1 << PEN_IRQ_NUM)	/* Pen Interrupt */
#घोषणा IPR_SPIS	(1 << SPIS_IRQ_NUM)	/* SPI Slave Interrupt */
#घोषणा IPR_TMR1	(1 << TMR1_IRQ_NUM)	/* Timer 1 पूर्णांकerrupt */
#घोषणा IPR_IRQ7	(1 << IRQ7_IRQ_NUM)	/* IRQ7 */

/* 'EZ328-compatible definitions */
#घोषणा IPR_SPI	IPR_SPIM
#घोषणा IPR_TMR	IPR_TMR1

/**********
 *
 * 0xFFFFF4xx -- Parallel Ports
 *
 **********/

/*
 * Port A
 */
#घोषणा PAसूची_ADDR	0xfffff400		/* Port A direction reg */
#घोषणा PADATA_ADDR	0xfffff401		/* Port A data रेजिस्टर */
#घोषणा PASEL_ADDR	0xfffff403		/* Port A Select रेजिस्टर */

#घोषणा PAसूची		BYTE_REF(PAसूची_ADDR)
#घोषणा PADATA		BYTE_REF(PADATA_ADDR)
#घोषणा PASEL		BYTE_REF(PASEL_ADDR)

#घोषणा PA(x)           (1 << (x))
#घोषणा PA_A(x)		PA((x) - 16)	/* This is specअगरic to PA only! */

#घोषणा PA_A16		PA(0)		/* Use A16 as PA(0) */
#घोषणा PA_A17		PA(1)		/* Use A17 as PA(1) */
#घोषणा PA_A18		PA(2)		/* Use A18 as PA(2) */
#घोषणा PA_A19		PA(3)		/* Use A19 as PA(3) */
#घोषणा PA_A20		PA(4)		/* Use A20 as PA(4) */
#घोषणा PA_A21		PA(5)		/* Use A21 as PA(5) */
#घोषणा PA_A22		PA(6)		/* Use A22 as PA(6) */
#घोषणा PA_A23		PA(7)		/* Use A23 as PA(7) */

/* 
 * Port B
 */
#घोषणा PBसूची_ADDR	0xfffff408		/* Port B direction reg */
#घोषणा PBDATA_ADDR	0xfffff409		/* Port B data रेजिस्टर */
#घोषणा PBSEL_ADDR	0xfffff40b		/* Port B Select Register */

#घोषणा PBसूची		BYTE_REF(PBसूची_ADDR)
#घोषणा PBDATA		BYTE_REF(PBDATA_ADDR)
#घोषणा PBSEL		BYTE_REF(PBSEL_ADDR)

#घोषणा PB(x)           (1 << (x))
#घोषणा PB_D(x)		PB(x)		/* This is specअगरic to port B only */

#घोषणा PB_D0		PB(0)		/* Use D0 as PB(0) */
#घोषणा PB_D1		PB(1)		/* Use D1 as PB(1) */
#घोषणा PB_D2		PB(2)		/* Use D2 as PB(2) */
#घोषणा PB_D3		PB(3)		/* Use D3 as PB(3) */
#घोषणा PB_D4		PB(4)		/* Use D4 as PB(4) */
#घोषणा PB_D5		PB(5)		/* Use D5 as PB(5) */
#घोषणा PB_D6		PB(6)		/* Use D6 as PB(6) */
#घोषणा PB_D7		PB(7)		/* Use D7 as PB(7) */

/* 
 * Port C
 */
#घोषणा PCसूची_ADDR	0xfffff410		/* Port C direction reg */
#घोषणा PCDATA_ADDR	0xfffff411		/* Port C data रेजिस्टर */
#घोषणा PCSEL_ADDR	0xfffff413		/* Port C Select Register */

#घोषणा PCसूची		BYTE_REF(PCसूची_ADDR)
#घोषणा PCDATA		BYTE_REF(PCDATA_ADDR)
#घोषणा PCSEL		BYTE_REF(PCSEL_ADDR)

#घोषणा PC(x)           (1 << (x))

#घोषणा PC_WE		PC(6)		/* Use WE    as PC(6) */
#घोषणा PC_DTACK	PC(5)		/* Use DTACK as PC(5) */
#घोषणा PC_IRQ7		PC(4)		/* Use IRQ7  as PC(4) */
#घोषणा PC_LDS		PC(2)		/* Use LDS   as PC(2) */
#घोषणा PC_UDS		PC(1)		/* Use UDS   as PC(1) */
#घोषणा PC_MOCLK	PC(0)		/* Use MOCLK as PC(0) */

/* 
 * Port D
 */
#घोषणा PDसूची_ADDR	0xfffff418		/* Port D direction reg */
#घोषणा PDDATA_ADDR	0xfffff419		/* Port D data रेजिस्टर */
#घोषणा PDPUEN_ADDR	0xfffff41a		/* Port D Pull-Up enable reg */
#घोषणा PDPOL_ADDR	0xfffff41c		/* Port D Polarity Register */
#घोषणा PसूचीQEN_ADDR	0xfffff41d		/* Port D IRQ enable रेजिस्टर */
#घोषणा	PDIQEG_ADDR	0xfffff41f		/* Port D IRQ Edge Register */

#घोषणा PDसूची		BYTE_REF(PDसूची_ADDR)
#घोषणा PDDATA		BYTE_REF(PDDATA_ADDR)
#घोषणा PDPUEN		BYTE_REF(PDPUEN_ADDR)
#घोषणा	PDPOL		BYTE_REF(PDPOL_ADDR)
#घोषणा PसूचीQEN		BYTE_REF(PसूचीQEN_ADDR)
#घोषणा PDIQEG		BYTE_REF(PDIQEG_ADDR)

#घोषणा PD(x)           (1 << (x))
#घोषणा PD_KB(x)	PD(x)		/* This is specअगरic क्रम Port D only */

#घोषणा PD_KB0		PD(0)	/* Use KB0 as PD(0) */
#घोषणा PD_KB1		PD(1)	/* Use KB1 as PD(1) */
#घोषणा PD_KB2		PD(2)	/* Use KB2 as PD(2) */
#घोषणा PD_KB3		PD(3)	/* Use KB3 as PD(3) */
#घोषणा PD_KB4		PD(4)	/* Use KB4 as PD(4) */
#घोषणा PD_KB5		PD(5)	/* Use KB5 as PD(5) */
#घोषणा PD_KB6		PD(6)	/* Use KB6 as PD(6) */
#घोषणा PD_KB7		PD(7)	/* Use KB7 as PD(7) */

/* 
 * Port E
 */
#घोषणा PEसूची_ADDR	0xfffff420		/* Port E direction reg */
#घोषणा PEDATA_ADDR	0xfffff421		/* Port E data रेजिस्टर */
#घोषणा PEPUEN_ADDR	0xfffff422		/* Port E Pull-Up enable reg */
#घोषणा PESEL_ADDR	0xfffff423		/* Port E Select Register */

#घोषणा PEसूची		BYTE_REF(PEसूची_ADDR)
#घोषणा PEDATA		BYTE_REF(PEDATA_ADDR)
#घोषणा PEPUEN		BYTE_REF(PEPUEN_ADDR)
#घोषणा PESEL		BYTE_REF(PESEL_ADDR)

#घोषणा PE(x)           (1 << (x))

#घोषणा PE_CSA1		PE(1)	/* Use CSA1 as PE(1) */
#घोषणा PE_CSA2		PE(2)	/* Use CSA2 as PE(2) */
#घोषणा PE_CSA3		PE(3)	/* Use CSA3 as PE(3) */
#घोषणा PE_CSB0		PE(4)	/* Use CSB0 as PE(4) */
#घोषणा PE_CSB1		PE(5)	/* Use CSB1 as PE(5) */
#घोषणा PE_CSB2		PE(6)	/* Use CSB2 as PE(6) */
#घोषणा PE_CSB3		PE(7)	/* Use CSB3 as PE(7) */

/* 
 * Port F
 */
#घोषणा PFसूची_ADDR	0xfffff428		/* Port F direction reg */
#घोषणा PFDATA_ADDR	0xfffff429		/* Port F data रेजिस्टर */
#घोषणा PFPUEN_ADDR	0xfffff42a		/* Port F Pull-Up enable reg */
#घोषणा PFSEL_ADDR	0xfffff42b		/* Port F Select Register */

#घोषणा PFसूची		BYTE_REF(PFसूची_ADDR)
#घोषणा PFDATA		BYTE_REF(PFDATA_ADDR)
#घोषणा PFPUEN		BYTE_REF(PFPUEN_ADDR)
#घोषणा PFSEL		BYTE_REF(PFSEL_ADDR)

#घोषणा PF(x)           (1 << (x))
#घोषणा PF_A(x)		PF((x) - 24)	/* This is Port F specअगरic only */

#घोषणा PF_A24		PF(0)	/* Use A24 as PF(0) */
#घोषणा PF_A25		PF(1)	/* Use A25 as PF(1) */
#घोषणा PF_A26		PF(2)	/* Use A26 as PF(2) */
#घोषणा PF_A27		PF(3)	/* Use A27 as PF(3) */
#घोषणा PF_A28		PF(4)	/* Use A28 as PF(4) */
#घोषणा PF_A29		PF(5)	/* Use A29 as PF(5) */
#घोषणा PF_A30		PF(6)	/* Use A30 as PF(6) */
#घोषणा PF_A31		PF(7)	/* Use A31 as PF(7) */

/* 
 * Port G
 */
#घोषणा PGसूची_ADDR	0xfffff430		/* Port G direction reg */
#घोषणा PGDATA_ADDR	0xfffff431		/* Port G data रेजिस्टर */
#घोषणा PGPUEN_ADDR	0xfffff432		/* Port G Pull-Up enable reg */
#घोषणा PGSEL_ADDR	0xfffff433		/* Port G Select Register */

#घोषणा PGसूची		BYTE_REF(PGसूची_ADDR)
#घोषणा PGDATA		BYTE_REF(PGDATA_ADDR)
#घोषणा PGPUEN		BYTE_REF(PGPUEN_ADDR)
#घोषणा PGSEL		BYTE_REF(PGSEL_ADDR)

#घोषणा PG(x)           (1 << (x))

#घोषणा PG_UART_TXD	PG(0)	/* Use UART_TXD as PG(0) */
#घोषणा PG_UART_RXD	PG(1)	/* Use UART_RXD as PG(1) */
#घोषणा PG_PWMOUT	PG(2)	/* Use PWMOUT   as PG(2) */
#घोषणा PG_TOUT2	PG(3)   /* Use TOUT2    as PG(3) */
#घोषणा PG_TIN2		PG(4)	/* Use TIN2     as PG(4) */
#घोषणा PG_TOUT1	PG(5)   /* Use TOUT1    as PG(5) */
#घोषणा PG_TIN1		PG(6)	/* Use TIN1     as PG(6) */
#घोषणा PG_RTCOUT	PG(7)	/* Use RTCOUT   as PG(7) */

/* 
 * Port J
 */
#घोषणा PJसूची_ADDR	0xfffff438		/* Port J direction reg */
#घोषणा PJDATA_ADDR	0xfffff439		/* Port J data रेजिस्टर */
#घोषणा PJSEL_ADDR	0xfffff43b		/* Port J Select Register */

#घोषणा PJसूची		BYTE_REF(PJसूची_ADDR)
#घोषणा PJDATA		BYTE_REF(PJDATA_ADDR)
#घोषणा PJSEL		BYTE_REF(PJSEL_ADDR)

#घोषणा PJ(x)           (1 << (x)) 

#घोषणा PJ_CSD3		PJ(7)	/* Use CSD3 as PJ(7) */

/* 
 * Port K
 */
#घोषणा PKसूची_ADDR	0xfffff440		/* Port K direction reg */
#घोषणा PKDATA_ADDR	0xfffff441		/* Port K data रेजिस्टर */
#घोषणा PKPUEN_ADDR	0xfffff442		/* Port K Pull-Up enable reg */
#घोषणा PKSEL_ADDR	0xfffff443		/* Port K Select Register */

#घोषणा PKसूची		BYTE_REF(PKसूची_ADDR)
#घोषणा PKDATA		BYTE_REF(PKDATA_ADDR)
#घोषणा PKPUEN		BYTE_REF(PKPUEN_ADDR)
#घोषणा PKSEL		BYTE_REF(PKSEL_ADDR)

#घोषणा PK(x)           (1 << (x))

/* 
 * Port M
 */
#घोषणा PMसूची_ADDR	0xfffff438		/* Port M direction reg */
#घोषणा PMDATA_ADDR	0xfffff439		/* Port M data रेजिस्टर */
#घोषणा PMPUEN_ADDR	0xfffff43a		/* Port M Pull-Up enable reg */
#घोषणा PMSEL_ADDR	0xfffff43b		/* Port M Select Register */

#घोषणा PMसूची		BYTE_REF(PMसूची_ADDR)
#घोषणा PMDATA		BYTE_REF(PMDATA_ADDR)
#घोषणा PMPUEN		BYTE_REF(PMPUEN_ADDR)
#घोषणा PMSEL		BYTE_REF(PMSEL_ADDR)

#घोषणा PM(x)           (1 << (x))

/**********
 *
 * 0xFFFFF5xx -- Pulse-Width Modulator (PWM)
 *
 **********/

/*
 * PWM Control Register 
 */
#घोषणा PWMC_ADDR	0xfffff500
#घोषणा PWMC		WORD_REF(PWMC_ADDR)

#घोषणा PWMC_CLKSEL_MASK	0x0007	/* Clock Selection */
#घोषणा PWMC_CLKSEL_SHIFT	0
#घोषणा PWMC_PWMEN		0x0010	/* Enable PWM */
#घोषणा PMNC_POL		0x0020	/* PWM Output Bit Polarity */
#घोषणा PWMC_PIN		0x0080	/* Current PWM output pin status */
#घोषणा PWMC_LOAD		0x0100	/* Force a new period */
#घोषणा PWMC_IRQEN		0x4000	/* Interrupt Request Enable */
#घोषणा PWMC_CLKSRC		0x8000	/* Clock Source Select */

/* 'EZ328-compatible definitions */
#घोषणा PWMC_EN	PWMC_PWMEN

/*
 * PWM Period Register
 */
#घोषणा PWMP_ADDR	0xfffff502
#घोषणा PWMP		WORD_REF(PWMP_ADDR)

/* 
 * PWM Width Register 
 */
#घोषणा PWMW_ADDR	0xfffff504
#घोषणा PWMW		WORD_REF(PWMW_ADDR)

/*
 * PWM Counter Register
 */
#घोषणा PWMCNT_ADDR	0xfffff506
#घोषणा PWMCNT		WORD_REF(PWMCNT_ADDR)

/**********
 *
 * 0xFFFFF6xx -- General-Purpose Timers
 *
 **********/

/* 
 * Timer Unit 1 and 2 Control Registers
 */
#घोषणा TCTL1_ADDR	0xfffff600
#घोषणा TCTL1		WORD_REF(TCTL1_ADDR)
#घोषणा TCTL2_ADDR	0xfffff60c
#घोषणा TCTL2		WORD_REF(TCTL2_ADDR)

#घोषणा	TCTL_TEN		0x0001	/* Timer Enable  */
#घोषणा TCTL_CLKSOURCE_MASK 	0x000e	/* Clock Source: */
#घोषणा   TCTL_CLKSOURCE_STOP	   0x0000	/* Stop count (disabled)    */
#घोषणा   TCTL_CLKSOURCE_SYSCLK	   0x0002	/* SYSCLK to prescaler      */
#घोषणा   TCTL_CLKSOURCE_SYSCLK_16 0x0004	/* SYSCLK/16 to prescaler   */
#घोषणा   TCTL_CLKSOURCE_TIN	   0x0006	/* TIN to prescaler         */
#घोषणा   TCTL_CLKSOURCE_32KHZ	   0x0008	/* 32kHz घड़ी to prescaler */
#घोषणा TCTL_IRQEN		0x0010	/* IRQ Enable    */
#घोषणा TCTL_OM			0x0020	/* Output Mode   */
#घोषणा TCTL_CAP_MASK		0x00c0	/* Capture Edge: */
#घोषणा	  TCTL_CAP_RE		0x0040		/* Capture on rizing edge   */
#घोषणा   TCTL_CAP_FE		0x0080		/* Capture on falling edge  */
#घोषणा TCTL_FRR		0x0010	/* Free-Run Mode */

/* 'EZ328-compatible definitions */
#घोषणा TCTL_ADDR	TCTL1_ADDR
#घोषणा TCTL		TCTL1

/*
 * Timer Unit 1 and 2 Prescaler Registers
 */
#घोषणा TPRER1_ADDR	0xfffff602
#घोषणा TPRER1		WORD_REF(TPRER1_ADDR)
#घोषणा TPRER2_ADDR	0xfffff60e
#घोषणा TPRER2		WORD_REF(TPRER2_ADDR)

/* 'EZ328-compatible definitions */
#घोषणा TPRER_ADDR	TPRER1_ADDR
#घोषणा TPRER		TPRER1

/*
 * Timer Unit 1 and 2 Compare Registers
 */
#घोषणा TCMP1_ADDR	0xfffff604
#घोषणा TCMP1		WORD_REF(TCMP1_ADDR)
#घोषणा TCMP2_ADDR	0xfffff610
#घोषणा TCMP2		WORD_REF(TCMP2_ADDR)

/* 'EZ328-compatible definitions */
#घोषणा TCMP_ADDR	TCMP1_ADDR
#घोषणा TCMP		TCMP1

/*
 * Timer Unit 1 and 2 Capture Registers
 */
#घोषणा TCR1_ADDR	0xfffff606
#घोषणा TCR1		WORD_REF(TCR1_ADDR)
#घोषणा TCR2_ADDR	0xfffff612
#घोषणा TCR2		WORD_REF(TCR2_ADDR)

/* 'EZ328-compatible definitions */
#घोषणा TCR_ADDR	TCR1_ADDR
#घोषणा TCR		TCR1

/*
 * Timer Unit 1 and 2 Counter Registers
 */
#घोषणा TCN1_ADDR	0xfffff608
#घोषणा TCN1		WORD_REF(TCN1_ADDR)
#घोषणा TCN2_ADDR	0xfffff614
#घोषणा TCN2		WORD_REF(TCN2_ADDR)

/* 'EZ328-compatible definitions */
#घोषणा TCN_ADDR	TCN1_ADDR
#घोषणा TCN		TCN1

/*
 * Timer Unit 1 and 2 Status Registers
 */
#घोषणा TSTAT1_ADDR	0xfffff60a
#घोषणा TSTAT1		WORD_REF(TSTAT1_ADDR)
#घोषणा TSTAT2_ADDR	0xfffff616
#घोषणा TSTAT2		WORD_REF(TSTAT2_ADDR)

#घोषणा TSTAT_COMP	0x0001		/* Compare Event occurred */
#घोषणा TSTAT_CAPT	0x0001		/* Capture Event occurred */

/* 'EZ328-compatible definitions */
#घोषणा TSTAT_ADDR	TSTAT1_ADDR
#घोषणा TSTAT		TSTAT1

/*
 * Watchकरोg Compare Register 
 */
#घोषणा WRR_ADDR	0xfffff61a
#घोषणा WRR		WORD_REF(WRR_ADDR)

/*
 * Watchकरोg Counter Register 
 */
#घोषणा WCN_ADDR	0xfffff61c
#घोषणा WCN		WORD_REF(WCN_ADDR)

/*
 * Watchकरोg Control and Status Register
 */
#घोषणा WCSR_ADDR	0xfffff618
#घोषणा WCSR		WORD_REF(WCSR_ADDR)

#घोषणा WCSR_WDEN	0x0001	/* Watchकरोg Enable */
#घोषणा WCSR_FI		0x0002	/* Forced Interrupt (instead of SW reset)*/
#घोषणा WCSR_WRST	0x0004	/* Watchकरोg Reset */

/**********
 *
 * 0xFFFFF7xx -- Serial Peripheral Interface Slave (SPIS)
 *
 **********/

/*
 * SPI Slave Register
 */
#घोषणा SPISR_ADDR	0xfffff700
#घोषणा SPISR		WORD_REF(SPISR_ADDR)

#घोषणा SPISR_DATA_ADDR	0xfffff701
#घोषणा SPISR_DATA	BYTE_REF(SPISR_DATA_ADDR)

#घोषणा SPISR_DATA_MASK	 0x00ff	/* Shअगरted data from the बाह्यal device */
#घोषणा SPISR_DATA_SHIFT 0
#घोषणा SPISR_SPISEN	 0x0100	/* SPIS module enable */
#घोषणा SPISR_POL	 0x0200	/* SPSCLK polarity control */
#घोषणा SPISR_PHA	 0x0400	/* Phase relationship between SPSCLK & SPSRxD */
#घोषणा SPISR_OVWR	 0x0800	/* Data buffer has been overwritten */
#घोषणा SPISR_DATARDY	 0x1000	/* Data पढ़ोy */
#घोषणा SPISR_ENPOL	 0x2000	/* Enable Polarity */
#घोषणा SPISR_IRQEN	 0x4000	/* SPIS IRQ Enable */
#घोषणा SPISR_SPISIRQ	 0x8000	/* SPIS IRQ posted */

/**********
 *
 * 0xFFFFF8xx -- Serial Peripheral Interface Master (SPIM)
 *
 **********/

/*
 * SPIM Data Register
 */
#घोषणा SPIMDATA_ADDR	0xfffff800
#घोषणा SPIMDATA	WORD_REF(SPIMDATA_ADDR)

/*
 * SPIM Control/Status Register
 */
#घोषणा SPIMCONT_ADDR	0xfffff802
#घोषणा SPIMCONT	WORD_REF(SPIMCONT_ADDR)

#घोषणा SPIMCONT_BIT_COUNT_MASK	 0x000f	/* Transfer Length in Bytes */
#घोषणा SPIMCONT_BIT_COUNT_SHIFT 0
#घोषणा SPIMCONT_POL		 0x0010	/* SPMCLK Signel Polarity */
#घोषणा	SPIMCONT_PHA		 0x0020	/* Clock/Data phase relationship */
#घोषणा SPIMCONT_IRQEN		 0x0040 /* IRQ Enable */
#घोषणा SPIMCONT_SPIMIRQ	 0x0080	/* Interrupt Request */
#घोषणा SPIMCONT_XCH		 0x0100	/* Exchange */
#घोषणा SPIMCONT_RSPIMEN	 0x0200	/* Enable SPIM */
#घोषणा SPIMCONT_DATA_RATE_MASK	 0xe000	/* SPIM Data Rate */
#घोषणा SPIMCONT_DATA_RATE_SHIFT 13

/* 'EZ328-compatible definitions */
#घोषणा SPIMCONT_IRQ	SPIMCONT_SPIMIRQ
#घोषणा SPIMCONT_ENABLE	SPIMCONT_SPIMEN
/**********
 *
 * 0xFFFFF9xx -- UART
 *
 **********/

/*
 * UART Status/Control Register
 */
#घोषणा USTCNT_ADDR	0xfffff900
#घोषणा USTCNT		WORD_REF(USTCNT_ADDR)

#घोषणा USTCNT_TXAVAILEN	0x0001	/* Transmitter Available Int Enable */
#घोषणा USTCNT_TXHALFEN		0x0002	/* Transmitter Half Empty Int Enable */
#घोषणा USTCNT_TXEMPTYEN	0x0004	/* Transmitter Empty Int Enable */
#घोषणा USTCNT_RXREADYEN	0x0008	/* Receiver Ready Interrupt Enable */
#घोषणा USTCNT_RXHALFEN		0x0010	/* Receiver Half-Full Int Enable */
#घोषणा USTCNT_RXFULLEN		0x0020	/* Receiver Full Interrupt Enable */
#घोषणा USTCNT_CTSDELTAEN	0x0040	/* CTS Delta Interrupt Enable */
#घोषणा USTCNT_GPIODELTAEN	0x0080	/* Old Data Interrupt Enable */
#घोषणा USTCNT_8_7		0x0100	/* Eight or seven-bit transmission */
#घोषणा USTCNT_STOP		0x0200	/* Stop bit transmission */
#घोषणा USTCNT_ODD_EVEN		0x0400	/* Odd Parity */
#घोषणा	USTCNT_PARITYEN		0x0800	/* Parity Enable */
#घोषणा USTCNT_CLKMODE		0x1000	/* Clock Mode Select */
#घोषणा	USTCNT_TXEN		0x2000	/* Transmitter Enable */
#घोषणा USTCNT_RXEN		0x4000	/* Receiver Enable */
#घोषणा USTCNT_UARTEN		0x8000	/* UART Enable */

/* 'EZ328-compatible definitions */
#घोषणा USTCNT_TXAE	USTCNT_TXAVAILEN 
#घोषणा USTCNT_TXHE	USTCNT_TXHALFEN
#घोषणा USTCNT_TXEE	USTCNT_TXEMPTYEN
#घोषणा USTCNT_RXRE	USTCNT_RXREADYEN
#घोषणा USTCNT_RXHE	USTCNT_RXHALFEN
#घोषणा USTCNT_RXFE	USTCNT_RXFULLEN
#घोषणा USTCNT_CTSD	USTCNT_CTSDELTAEN
#घोषणा USTCNT_ODD	USTCNT_ODD_EVEN
#घोषणा USTCNT_PEN	USTCNT_PARITYEN
#घोषणा USTCNT_CLKM	USTCNT_CLKMODE
#घोषणा USTCNT_UEN	USTCNT_UARTEN

/*
 * UART Baud Control Register
 */
#घोषणा UBAUD_ADDR	0xfffff902
#घोषणा UBAUD		WORD_REF(UBAUD_ADDR)

#घोषणा UBAUD_PRESCALER_MASK	0x003f	/* Actual भागisor is 65 - PRESCALER */
#घोषणा UBAUD_PRESCALER_SHIFT	0
#घोषणा UBAUD_DIVIDE_MASK	0x0700	/* Baud Rate freq. भागisor */
#घोषणा UBAUD_DIVIDE_SHIFT	8
#घोषणा UBAUD_BAUD_SRC		0x0800	/* Baud Rate Source */
#घोषणा UBAUD_GPIOSRC		0x1000	/* GPIO source */
#घोषणा UBAUD_GPIOसूची		0x2000	/* GPIO Direction */
#घोषणा UBAUD_GPIO		0x4000	/* Current GPIO pin status */
#घोषणा UBAUD_GPIODELTA		0x8000	/* GPIO pin value changed */

/*
 * UART Receiver Register 
 */
#घोषणा URX_ADDR	0xfffff904
#घोषणा URX		WORD_REF(URX_ADDR)

#घोषणा URX_RXDATA_ADDR	0xfffff905
#घोषणा URX_RXDATA	BYTE_REF(URX_RXDATA_ADDR)

#घोषणा URX_RXDATA_MASK	 0x00ff	/* Received data */
#घोषणा URX_RXDATA_SHIFT 0
#घोषणा URX_PARITY_ERROR 0x0100	/* Parity Error */
#घोषणा URX_BREAK	 0x0200	/* Break Detected */
#घोषणा URX_FRAME_ERROR	 0x0400	/* Framing Error */
#घोषणा URX_OVRUN	 0x0800	/* Serial Overrun */
#घोषणा URX_DATA_READY	 0x2000	/* Data Ready (FIFO not empty) */
#घोषणा URX_FIFO_HALF	 0x4000 /* FIFO is Half-Full */
#घोषणा URX_FIFO_FULL	 0x8000	/* FIFO is Full */

/*
 * UART Transmitter Register 
 */
#घोषणा UTX_ADDR	0xfffff906
#घोषणा UTX		WORD_REF(UTX_ADDR)

#घोषणा UTX_TXDATA_ADDR	0xfffff907
#घोषणा UTX_TXDATA	BYTE_REF(UTX_TXDATA_ADDR)

#घोषणा UTX_TXDATA_MASK	 0x00ff	/* Data to be transmitted */
#घोषणा UTX_TXDATA_SHIFT 0
#घोषणा UTX_CTS_DELTA	 0x0100	/* CTS changed */
#घोषणा UTX_CTS_STATUS	 0x0200	/* CTS State */
#घोषणा	UTX_IGNORE_CTS	 0x0800	/* Ignore CTS */
#घोषणा UTX_SEND_BREAK	 0x1000	/* Send a BREAK */
#घोषणा UTX_TX_AVAIL	 0x2000	/* Transmit FIFO has a slot available */
#घोषणा UTX_FIFO_HALF	 0x4000	/* Transmit FIFO is half empty */
#घोषणा UTX_FIFO_EMPTY	 0x8000	/* Transmit FIFO is empty */

/* 'EZ328-compatible definitions */
#घोषणा UTX_CTS_STAT	UTX_CTS_STATUS
#घोषणा UTX_NOCTS	UTX_IGNORE_CTS

/*
 * UART Miscellaneous Register 
 */
#घोषणा UMISC_ADDR	0xfffff908
#घोषणा UMISC		WORD_REF(UMISC_ADDR)

#घोषणा UMISC_TX_POL	 0x0004	/* Transmit Polarity */
#घोषणा UMISC_RX_POL	 0x0008	/* Receive Polarity */
#घोषणा UMISC_IRDA_LOOP	 0x0010	/* IrDA Loopback Enable */
#घोषणा UMISC_IRDA_EN	 0x0020	/* Infra-Red Enable */
#घोषणा UMISC_RTS	 0x0040	/* Set RTS status */
#घोषणा UMISC_RTSCONT	 0x0080	/* Choose RTS control */
#घोषणा UMISC_LOOP	 0x1000	/* Serial Loopback Enable */
#घोषणा UMISC_FORCE_PERR 0x2000	/* Force Parity Error */
#घोषणा UMISC_CLKSRC	 0x4000	/* Clock Source */


/* generalization of uart control रेजिस्टरs to support multiple ports: */
प्रकार अस्थिर काष्ठा अणु
  अस्थिर अचिन्हित लघु पूर्णांक ustcnt;
  अस्थिर अचिन्हित लघु पूर्णांक ubaud;
  जोड़ अणु
    अस्थिर अचिन्हित लघु पूर्णांक w;
    काष्ठा अणु
      अस्थिर अचिन्हित अक्षर status;
      अस्थिर अचिन्हित अक्षर rxdata;
    पूर्ण b;
  पूर्ण urx;
  जोड़ अणु
    अस्थिर अचिन्हित लघु पूर्णांक w;
    काष्ठा अणु
      अस्थिर अचिन्हित अक्षर status;
      अस्थिर अचिन्हित अक्षर txdata;
    पूर्ण b;
  पूर्ण utx;
  अस्थिर अचिन्हित लघु पूर्णांक umisc;
  अस्थिर अचिन्हित लघु पूर्णांक pad1;
  अस्थिर अचिन्हित लघु पूर्णांक pad2;
  अस्थिर अचिन्हित लघु पूर्णांक pad3;
पूर्ण __packed m68328_uart;


/**********
 *
 * 0xFFFFFAxx -- LCD Controller
 *
 **********/

/*
 * LCD Screen Starting Address Register 
 */
#घोषणा LSSA_ADDR	0xfffffa00
#घोषणा LSSA		LONG_REF(LSSA_ADDR)

#घोषणा LSSA_SSA_MASK	0xfffffffe	/* Bit 0 is reserved */

/*
 * LCD Virtual Page Width Register 
 */
#घोषणा LVPW_ADDR	0xfffffa05
#घोषणा LVPW		BYTE_REF(LVPW_ADDR)

/*
 * LCD Screen Width Register (not compatible with 'EZ328 !!!)
 */
#घोषणा LXMAX_ADDR	0xfffffa08
#घोषणा LXMAX		WORD_REF(LXMAX_ADDR)

#घोषणा LXMAX_XM_MASK	0x02ff		/* Bits 0-3 are reserved */

/*
 * LCD Screen Height Register
 */
#घोषणा LYMAX_ADDR	0xfffffa0a
#घोषणा LYMAX		WORD_REF(LYMAX_ADDR)

#घोषणा LYMAX_YM_MASK	0x02ff		/* Bits 10-15 are reserved */

/*
 * LCD Cursor X Position Register
 */
#घोषणा LCXP_ADDR	0xfffffa18
#घोषणा LCXP		WORD_REF(LCXP_ADDR)

#घोषणा LCXP_CC_MASK	0xc000		/* Cursor Control */
#घोषणा   LCXP_CC_TRAMSPARENT	0x0000
#घोषणा   LCXP_CC_BLACK		0x4000
#घोषणा   LCXP_CC_REVERSED	0x8000
#घोषणा   LCXP_CC_WHITE		0xc000
#घोषणा LCXP_CXP_MASK	0x02ff		/* Cursor X position */

/*
 * LCD Cursor Y Position Register
 */
#घोषणा LCYP_ADDR	0xfffffa1a
#घोषणा LCYP		WORD_REF(LCYP_ADDR)

#घोषणा LCYP_CYP_MASK	0x01ff		/* Cursor Y Position */

/*
 * LCD Cursor Width and Heigth Register
 */
#घोषणा LCWCH_ADDR	0xfffffa1c
#घोषणा LCWCH		WORD_REF(LCWCH_ADDR)

#घोषणा LCWCH_CH_MASK	0x001f		/* Cursor Height */
#घोषणा LCWCH_CH_SHIFT	0
#घोषणा LCWCH_CW_MASK	0x1f00		/* Cursor Width */
#घोषणा LCWCH_CW_SHIFT	8

/*
 * LCD Blink Control Register
 */
#घोषणा LBLKC_ADDR	0xfffffa1f
#घोषणा LBLKC		BYTE_REF(LBLKC_ADDR)

#घोषणा LBLKC_BD_MASK	0x7f	/* Blink Divisor */
#घोषणा LBLKC_BD_SHIFT	0
#घोषणा LBLKC_BKEN	0x80	/* Blink Enabled */

/*
 * LCD Panel Interface Configuration Register 
 */
#घोषणा LPICF_ADDR	0xfffffa20
#घोषणा LPICF		BYTE_REF(LPICF_ADDR)

#घोषणा LPICF_GS_MASK	 0x01	 /* Gray-Scale Mode */
#घोषणा	  LPICF_GS_BW	   0x00
#घोषणा   LPICF_GS_GRAY_4  0x01
#घोषणा LPICF_PBSIZ_MASK 0x06	/* Panel Bus Width */
#घोषणा   LPICF_PBSIZ_1	   0x00
#घोषणा   LPICF_PBSIZ_2    0x02
#घोषणा   LPICF_PBSIZ_4    0x04

/*
 * LCD Polarity Configuration Register 
 */
#घोषणा LPOLCF_ADDR	0xfffffa21
#घोषणा LPOLCF		BYTE_REF(LPOLCF_ADDR)

#घोषणा LPOLCF_PIXPOL	0x01	/* Pixel Polarity */
#घोषणा LPOLCF_LPPOL	0x02	/* Line Pulse Polarity */
#घोषणा LPOLCF_FLMPOL	0x04	/* Frame Marker Polarity */
#घोषणा LPOLCF_LCKPOL	0x08	/* LCD Shअगरt Lock Polarity */

/*
 * LACD (LCD Alternate Crystal Direction) Rate Control Register
 */
#घोषणा LACDRC_ADDR	0xfffffa23
#घोषणा LACDRC		BYTE_REF(LACDRC_ADDR)

#घोषणा LACDRC_ACD_MASK	 0x0f	/* Alternate Crystal Direction Control */
#घोषणा LACDRC_ACD_SHIFT 0

/*
 * LCD Pixel Clock Divider Register
 */
#घोषणा LPXCD_ADDR	0xfffffa25
#घोषणा LPXCD		BYTE_REF(LPXCD_ADDR)

#घोषणा	LPXCD_PCD_MASK	0x3f 	/* Pixel Clock Divider */
#घोषणा LPXCD_PCD_SHIFT	0

/*
 * LCD Clocking Control Register
 */
#घोषणा LCKCON_ADDR	0xfffffa27
#घोषणा LCKCON		BYTE_REF(LCKCON_ADDR)

#घोषणा LCKCON_PCDS	 0x01	/* Pixel Clock Divider Source Select */
#घोषणा LCKCON_DWIDTH	 0x02	/* Display Memory Width  */
#घोषणा LCKCON_DWS_MASK	 0x3c	/* Display Wait-State */
#घोषणा LCKCON_DWS_SHIFT 2
#घोषणा LCKCON_DMA16	 0x40	/* DMA burst length */
#घोषणा LCKCON_LCDON	 0x80	/* Enable LCD Controller */

/* 'EZ328-compatible definitions */
#घोषणा LCKCON_DW_MASK	LCKCON_DWS_MASK
#घोषणा LCKCON_DW_SHIFT	LCKCON_DWS_SHIFT

/*
 * LCD Last Buffer Address Register
 */
#घोषणा LLBAR_ADDR	0xfffffa29
#घोषणा LLBAR		BYTE_REF(LLBAR_ADDR)

#घोषणा LLBAR_LBAR_MASK	 0x7f	/* Number of memory words to fill 1 line */
#घोषणा LLBAR_LBAR_SHIFT 0

/*
 * LCD Octet Terminal Count Register 
 */
#घोषणा LOTCR_ADDR	0xfffffa2b
#घोषणा LOTCR		BYTE_REF(LOTCR_ADDR)

/*
 * LCD Panning Offset Register
 */
#घोषणा LPOSR_ADDR	0xfffffa2d
#घोषणा LPOSR		BYTE_REF(LPOSR_ADDR)

#घोषणा LPOSR_BOS	0x08	/* Byte offset (क्रम B/W mode only */
#घोषणा LPOSR_POS_MASK	0x07	/* Pixel Offset Code */
#घोषणा LPOSR_POS_SHIFT	0

/*
 * LCD Frame Rate Control Modulation Register
 */
#घोषणा LFRCM_ADDR	0xfffffa31
#घोषणा LFRCM		BYTE_REF(LFRCM_ADDR)

#घोषणा LFRCM_YMOD_MASK	 0x0f	/* Vertical Modulation */
#घोषणा LFRCM_YMOD_SHIFT 0
#घोषणा LFRCM_XMOD_MASK	 0xf0	/* Horizontal Modulation */
#घोषणा LFRCM_XMOD_SHIFT 4

/*
 * LCD Gray Palette Mapping Register
 */
#घोषणा LGPMR_ADDR	0xfffffa32
#घोषणा LGPMR		WORD_REF(LGPMR_ADDR)

#घोषणा LGPMR_GLEVEL3_MASK	0x000f
#घोषणा LGPMR_GLEVEL3_SHIFT	0 
#घोषणा LGPMR_GLEVEL2_MASK	0x00f0
#घोषणा LGPMR_GLEVEL2_SHIFT	4 
#घोषणा LGPMR_GLEVEL0_MASK	0x0f00
#घोषणा LGPMR_GLEVEL0_SHIFT	8 
#घोषणा LGPMR_GLEVEL1_MASK	0xf000
#घोषणा LGPMR_GLEVEL1_SHIFT	12

/**********
 *
 * 0xFFFFFBxx -- Real-Time Clock (RTC)
 *
 **********/

/*
 * RTC Hours Minutes and Seconds Register
 */
#घोषणा RTCTIME_ADDR	0xfffffb00
#घोषणा RTCTIME		LONG_REF(RTCTIME_ADDR)

#घोषणा RTCTIME_SECONDS_MASK	0x0000003f	/* Seconds */
#घोषणा RTCTIME_SECONDS_SHIFT	0
#घोषणा RTCTIME_MINUTES_MASK	0x003f0000	/* Minutes */
#घोषणा RTCTIME_MINUTES_SHIFT	16
#घोषणा RTCTIME_HOURS_MASK	0x1f000000	/* Hours */
#घोषणा RTCTIME_HOURS_SHIFT	24

/*
 *  RTC Alarm Register 
 */
#घोषणा RTCALRM_ADDR    0xfffffb04
#घोषणा RTCALRM         LONG_REF(RTCALRM_ADDR)

#घोषणा RTCALRM_SECONDS_MASK    0x0000003f      /* Seconds */
#घोषणा RTCALRM_SECONDS_SHIFT   0
#घोषणा RTCALRM_MINUTES_MASK    0x003f0000      /* Minutes */
#घोषणा RTCALRM_MINUTES_SHIFT   16
#घोषणा RTCALRM_HOURS_MASK      0x1f000000      /* Hours */
#घोषणा RTCALRM_HOURS_SHIFT     24

/*
 * RTC Control Register
 */
#घोषणा RTCCTL_ADDR	0xfffffb0c
#घोषणा RTCCTL		WORD_REF(RTCCTL_ADDR)

#घोषणा RTCCTL_384	0x0020	/* Crystal Selection */
#घोषणा RTCCTL_ENABLE	0x0080	/* RTC Enable */

/* 'EZ328-compatible definitions */
#घोषणा RTCCTL_XTL	RTCCTL_384
#घोषणा RTCCTL_EN	RTCCTL_ENABLE

/*
 * RTC Interrupt Status Register 
 */
#घोषणा RTCISR_ADDR	0xfffffb0e
#घोषणा RTCISR		WORD_REF(RTCISR_ADDR)

#घोषणा RTCISR_SW	0x0001	/* Stopwatch समयd out */
#घोषणा RTCISR_MIN	0x0002	/* 1-minute पूर्णांकerrupt has occurred */
#घोषणा RTCISR_ALM	0x0004	/* Alarm पूर्णांकerrupt has occurred */
#घोषणा RTCISR_DAY	0x0008	/* 24-hour rollover पूर्णांकerrupt has occurred */
#घोषणा RTCISR_1HZ	0x0010	/* 1Hz पूर्णांकerrupt has occurred */

/*
 * RTC Interrupt Enable Register
 */
#घोषणा RTCIENR_ADDR	0xfffffb10
#घोषणा RTCIENR		WORD_REF(RTCIENR_ADDR)

#घोषणा RTCIENR_SW	0x0001	/* Stopwatch पूर्णांकerrupt enable */
#घोषणा RTCIENR_MIN	0x0002	/* 1-minute पूर्णांकerrupt enable */
#घोषणा RTCIENR_ALM	0x0004	/* Alarm पूर्णांकerrupt enable */
#घोषणा RTCIENR_DAY	0x0008	/* 24-hour rollover पूर्णांकerrupt enable */
#घोषणा RTCIENR_1HZ	0x0010	/* 1Hz पूर्णांकerrupt enable */

/* 
 * Stopwatch Minutes Register
 */
#घोषणा STPWCH_ADDR	0xfffffb12
#घोषणा STPWCH		WORD_REF(STPWCH)

#घोषणा STPWCH_CNT_MASK	 0x00ff	/* Stopwatch countकरोwn value */
#घोषणा SPTWCH_CNT_SHIFT 0

#पूर्ण_अगर /* _MC68328_H_ */
