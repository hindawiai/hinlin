<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* include/यंत्र-m68knommu/MC68EZ328.h: 'EZ328 control रेजिस्टरs
 *
 * Copyright (C) 1999  Vladimir Gurevich <vgurevic@cisco.com>
 *                     Bear & Hare Software, Inc.
 *
 * Based on include/यंत्र-m68knommu/MC68332.h
 * Copyright (C) 1998  Kenneth Albanowski <kjahds@kjahds.com>,
 *                     The Silver Hammer Group, Ltd.
 *
 */
#समावेश <linux/compiler.h>

#अगर_अघोषित _MC68EZ328_H_
#घोषणा _MC68EZ328_H_

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
 * Silicon ID Register (Mask Revision Register (MRR) क्रम '328 Compatibility)
 */
#घोषणा MRR_ADDR 0xfffff004
#घोषणा MRR	 LONG_REF(MRR_ADDR)

/********** 
 *
 * 0xFFFFF1xx -- Chip-Select logic
 *
 **********/
 
/*
 * Chip Select Group Base Registers 
 */
#घोषणा CSGBA_ADDR	0xfffff100
#घोषणा CSGBB_ADDR	0xfffff102

#घोषणा CSGBC_ADDR	0xfffff104
#घोषणा CSGBD_ADDR	0xfffff106

#घोषणा CSGBA		WORD_REF(CSGBA_ADDR)
#घोषणा CSGBB		WORD_REF(CSGBB_ADDR)
#घोषणा CSGBC		WORD_REF(CSGBC_ADDR)
#घोषणा CSGBD		WORD_REF(CSGBD_ADDR)

/*
 * Chip Select Registers 
 */
#घोषणा CSA_ADDR	0xfffff110
#घोषणा CSB_ADDR	0xfffff112
#घोषणा CSC_ADDR	0xfffff114
#घोषणा CSD_ADDR	0xfffff116

#घोषणा CSA		WORD_REF(CSA_ADDR)
#घोषणा CSB		WORD_REF(CSB_ADDR)
#घोषणा CSC		WORD_REF(CSC_ADDR)
#घोषणा CSD		WORD_REF(CSD_ADDR)

#घोषणा CSA_EN		0x0001		/* Chip-Select Enable */
#घोषणा CSA_SIZ_MASK	0x000e		/* Chip-Select Size */
#घोषणा CSA_SIZ_SHIFT   1
#घोषणा CSA_WS_MASK	0x0070		/* Wait State */
#घोषणा CSA_WS_SHIFT    4
#घोषणा CSA_BSW		0x0080		/* Data Bus Width */
#घोषणा CSA_FLASH	0x0100		/* FLASH Memory Support */
#घोषणा CSA_RO		0x8000		/* Read-Only */

#घोषणा CSB_EN		0x0001		/* Chip-Select Enable */
#घोषणा CSB_SIZ_MASK	0x000e		/* Chip-Select Size */
#घोषणा CSB_SIZ_SHIFT   1
#घोषणा CSB_WS_MASK	0x0070		/* Wait State */
#घोषणा CSB_WS_SHIFT    4
#घोषणा CSB_BSW		0x0080		/* Data Bus Width */
#घोषणा CSB_FLASH	0x0100		/* FLASH Memory Support */
#घोषणा CSB_UPSIZ_MASK	0x1800		/* Unरक्षित memory block size */
#घोषणा CSB_UPSIZ_SHIFT 11
#घोषणा CSB_ROP		0x2000		/* Reaकरोnly अगर रक्षित */
#घोषणा CSB_SOP		0x4000		/* Supervisor only अगर रक्षित */
#घोषणा CSB_RO		0x8000		/* Read-Only */

#घोषणा CSC_EN		0x0001		/* Chip-Select Enable */
#घोषणा CSC_SIZ_MASK	0x000e		/* Chip-Select Size */
#घोषणा CSC_SIZ_SHIFT   1
#घोषणा CSC_WS_MASK	0x0070		/* Wait State */
#घोषणा CSC_WS_SHIFT    4
#घोषणा CSC_BSW		0x0080		/* Data Bus Width */
#घोषणा CSC_FLASH	0x0100		/* FLASH Memory Support */
#घोषणा CSC_UPSIZ_MASK	0x1800		/* Unरक्षित memory block size */
#घोषणा CSC_UPSIZ_SHIFT 11
#घोषणा CSC_ROP		0x2000		/* Reaकरोnly अगर रक्षित */
#घोषणा CSC_SOP		0x4000		/* Supervisor only अगर रक्षित */
#घोषणा CSC_RO		0x8000		/* Read-Only */

#घोषणा CSD_EN		0x0001		/* Chip-Select Enable */
#घोषणा CSD_SIZ_MASK	0x000e		/* Chip-Select Size */
#घोषणा CSD_SIZ_SHIFT   1
#घोषणा CSD_WS_MASK	0x0070		/* Wait State */
#घोषणा CSD_WS_SHIFT    4
#घोषणा CSD_BSW		0x0080		/* Data Bus Width */
#घोषणा CSD_FLASH	0x0100		/* FLASH Memory Support */
#घोषणा CSD_DRAM	0x0200		/* Dram Selection */
#घोषणा	CSD_COMB	0x0400		/* Combining */
#घोषणा CSD_UPSIZ_MASK	0x1800		/* Unरक्षित memory block size */
#घोषणा CSD_UPSIZ_SHIFT 11
#घोषणा CSD_ROP		0x2000		/* Reaकरोnly अगर रक्षित */
#घोषणा CSD_SOP		0x4000		/* Supervisor only अगर रक्षित */
#घोषणा CSD_RO		0x8000		/* Read-Only */

/*
 * Emulation Chip-Select Register 
 */
#घोषणा EMUCS_ADDR	0xfffff118
#घोषणा EMUCS		WORD_REF(EMUCS_ADDR)

#घोषणा EMUCS_WS_MASK	0x0070
#घोषणा EMUCS_WS_SHIFT	4

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
#घोषणा PLLCR_PRESC	       0x0020	/* VCO prescaler */
#घोषणा PLLCR_SYSCLK_SEL_MASK  0x0700	/* System Clock Selection */
#घोषणा PLLCR_SYSCLK_SEL_SHIFT 8
#घोषणा PLLCR_LCDCLK_SEL_MASK  0x3800	/* LCD Clock Selection */
#घोषणा PLLCR_LCDCLK_SEL_SHIFT 11

/* '328-compatible definitions */
#घोषणा PLLCR_PIXCLK_SEL_MASK	PLLCR_LCDCLK_SEL_MASK
#घोषणा PLLCR_PIXCLK_SEL_SHIFT	PLLCR_LCDCLK_SEL_SHIFT

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
#घोषणा ICR_ADDR	0xfffff302
#घोषणा ICR		WORD_REF(ICR_ADDR)

#घोषणा ICR_POL5	0x0080	/* Polarity Control क्रम IRQ5 */
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
#घोषणा SPI_IRQ_NUM	0	/* SPI पूर्णांकerrupt */
#घोषणा TMR_IRQ_NUM	1	/* Timer पूर्णांकerrupt */
#घोषणा UART_IRQ_NUM	2	/* UART पूर्णांकerrupt */	
#घोषणा	WDT_IRQ_NUM	3	/* Watchकरोg Timer पूर्णांकerrupt */
#घोषणा RTC_IRQ_NUM	4	/* RTC पूर्णांकerrupt */
#घोषणा	KB_IRQ_NUM	6	/* Keyboard Interrupt */
#घोषणा PWM_IRQ_NUM	7	/* Pulse-Width Modulator पूर्णांक. */
#घोषणा	INT0_IRQ_NUM	8	/* External INT0 */
#घोषणा	INT1_IRQ_NUM	9	/* External INT1 */
#घोषणा	INT2_IRQ_NUM	10	/* External INT2 */
#घोषणा	INT3_IRQ_NUM	11	/* External INT3 */
#घोषणा IRQ1_IRQ_NUM	16	/* IRQ1 */
#घोषणा IRQ2_IRQ_NUM	17	/* IRQ2 */
#घोषणा IRQ3_IRQ_NUM	18	/* IRQ3 */
#घोषणा IRQ6_IRQ_NUM	19	/* IRQ6 */
#घोषणा IRQ5_IRQ_NUM	20	/* IRQ5 */
#घोषणा SAM_IRQ_NUM	22	/* Sampling Timer क्रम RTC */
#घोषणा EMIQ_IRQ_NUM	23	/* Emulator Interrupt */

/* '328-compatible definitions */
#घोषणा SPIM_IRQ_NUM	SPI_IRQ_NUM
#घोषणा TMR1_IRQ_NUM	TMR_IRQ_NUM

/* 
 * Here go the biपंचांगasks themselves
 */
#घोषणा IMR_MSPI 	(1 << SPI_IRQ_NUM)	/* Mask SPI पूर्णांकerrupt */
#घोषणा	IMR_MTMR	(1 << TMR_IRQ_NUM)	/* Mask Timer पूर्णांकerrupt */
#घोषणा IMR_MUART	(1 << UART_IRQ_NUM)	/* Mask UART पूर्णांकerrupt */	
#घोषणा	IMR_MWDT	(1 << WDT_IRQ_NUM)	/* Mask Watchकरोg Timer पूर्णांकerrupt */
#घोषणा IMR_MRTC	(1 << RTC_IRQ_NUM)	/* Mask RTC पूर्णांकerrupt */
#घोषणा	IMR_MKB		(1 << KB_IRQ_NUM)	/* Mask Keyboard Interrupt */
#घोषणा IMR_MPWM	(1 << PWM_IRQ_NUM)	/* Mask Pulse-Width Modulator पूर्णांक. */
#घोषणा	IMR_MINT0	(1 << INT0_IRQ_NUM)	/* Mask External INT0 */
#घोषणा	IMR_MINT1	(1 << INT1_IRQ_NUM)	/* Mask External INT1 */
#घोषणा	IMR_MINT2	(1 << INT2_IRQ_NUM)	/* Mask External INT2 */
#घोषणा	IMR_MINT3	(1 << INT3_IRQ_NUM)	/* Mask External INT3 */
#घोषणा IMR_MIRQ1	(1 << IRQ1_IRQ_NUM)	/* Mask IRQ1 */
#घोषणा IMR_MIRQ2	(1 << IRQ2_IRQ_NUM)	/* Mask IRQ2 */
#घोषणा IMR_MIRQ3	(1 << IRQ3_IRQ_NUM)	/* Mask IRQ3 */
#घोषणा IMR_MIRQ6	(1 << IRQ6_IRQ_NUM)	/* Mask IRQ6 */
#घोषणा IMR_MIRQ5	(1 << IRQ5_IRQ_NUM)	/* Mask IRQ5 */
#घोषणा IMR_MSAM	(1 << SAM_IRQ_NUM)	/* Mask Sampling Timer क्रम RTC */
#घोषणा IMR_MEMIQ	(1 << EMIQ_IRQ_NUM)	/* Mask Emulator Interrupt */

/* '328-compatible definitions */
#घोषणा IMR_MSPIM	IMR_MSPI
#घोषणा IMR_MTMR1	IMR_MTMR

/* 
 * Interrupt Status Register 
 */
#घोषणा ISR_ADDR	0xfffff30c
#घोषणा ISR		LONG_REF(ISR_ADDR)

#घोषणा ISR_SPI 	(1 << SPI_IRQ_NUM)	/* SPI पूर्णांकerrupt */
#घोषणा	ISR_TMR		(1 << TMR_IRQ_NUM)	/* Timer पूर्णांकerrupt */
#घोषणा ISR_UART	(1 << UART_IRQ_NUM)	/* UART पूर्णांकerrupt */	
#घोषणा	ISR_WDT		(1 << WDT_IRQ_NUM)	/* Watchकरोg Timer पूर्णांकerrupt */
#घोषणा ISR_RTC		(1 << RTC_IRQ_NUM)	/* RTC पूर्णांकerrupt */
#घोषणा	ISR_KB		(1 << KB_IRQ_NUM)	/* Keyboard Interrupt */
#घोषणा ISR_PWM		(1 << PWM_IRQ_NUM)	/* Pulse-Width Modulator पूर्णांकerrupt */
#घोषणा	ISR_INT0	(1 << INT0_IRQ_NUM)	/* External INT0 */
#घोषणा	ISR_INT1	(1 << INT1_IRQ_NUM)	/* External INT1 */
#घोषणा	ISR_INT2	(1 << INT2_IRQ_NUM)	/* External INT2 */
#घोषणा	ISR_INT3	(1 << INT3_IRQ_NUM)	/* External INT3 */
#घोषणा ISR_IRQ1	(1 << IRQ1_IRQ_NUM)	/* IRQ1 */
#घोषणा ISR_IRQ2	(1 << IRQ2_IRQ_NUM)	/* IRQ2 */
#घोषणा ISR_IRQ3	(1 << IRQ3_IRQ_NUM)	/* IRQ3 */
#घोषणा ISR_IRQ6	(1 << IRQ6_IRQ_NUM)	/* IRQ6 */
#घोषणा ISR_IRQ5	(1 << IRQ5_IRQ_NUM)	/* IRQ5 */
#घोषणा ISR_SAM		(1 << SAM_IRQ_NUM)	/* Sampling Timer क्रम RTC */
#घोषणा ISR_EMIQ	(1 << EMIQ_IRQ_NUM)	/* Emulator Interrupt */

/* '328-compatible definitions */
#घोषणा ISR_SPIM	ISR_SPI
#घोषणा ISR_TMR1	ISR_TMR

/* 
 * Interrupt Pending Register 
 */
#घोषणा IPR_ADDR	0xfffff30c
#घोषणा IPR		LONG_REF(IPR_ADDR)

#घोषणा IPR_SPI 	(1 << SPI_IRQ_NUM)	/* SPI पूर्णांकerrupt */
#घोषणा	IPR_TMR		(1 << TMR_IRQ_NUM)	/* Timer पूर्णांकerrupt */
#घोषणा IPR_UART	(1 << UART_IRQ_NUM)	/* UART पूर्णांकerrupt */	
#घोषणा	IPR_WDT		(1 << WDT_IRQ_NUM)	/* Watchकरोg Timer पूर्णांकerrupt */
#घोषणा IPR_RTC		(1 << RTC_IRQ_NUM)	/* RTC पूर्णांकerrupt */
#घोषणा	IPR_KB		(1 << KB_IRQ_NUM)	/* Keyboard Interrupt */
#घोषणा IPR_PWM		(1 << PWM_IRQ_NUM)	/* Pulse-Width Modulator पूर्णांकerrupt */
#घोषणा	IPR_INT0	(1 << INT0_IRQ_NUM)	/* External INT0 */
#घोषणा	IPR_INT1	(1 << INT1_IRQ_NUM)	/* External INT1 */
#घोषणा	IPR_INT2	(1 << INT2_IRQ_NUM)	/* External INT2 */
#घोषणा	IPR_INT3	(1 << INT3_IRQ_NUM)	/* External INT3 */
#घोषणा IPR_IRQ1	(1 << IRQ1_IRQ_NUM)	/* IRQ1 */
#घोषणा IPR_IRQ2	(1 << IRQ2_IRQ_NUM)	/* IRQ2 */
#घोषणा IPR_IRQ3	(1 << IRQ3_IRQ_NUM)	/* IRQ3 */
#घोषणा IPR_IRQ6	(1 << IRQ6_IRQ_NUM)	/* IRQ6 */
#घोषणा IPR_IRQ5	(1 << IRQ5_IRQ_NUM)	/* IRQ5 */
#घोषणा IPR_SAM		(1 << SAM_IRQ_NUM)	/* Sampling Timer क्रम RTC */
#घोषणा IPR_EMIQ	(1 << EMIQ_IRQ_NUM)	/* Emulator Interrupt */

/* '328-compatible definitions */
#घोषणा IPR_SPIM	IPR_SPI
#घोषणा IPR_TMR1	IPR_TMR

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
#घोषणा PAPUEN_ADDR	0xfffff402		/* Port A Pull-Up enable reg */

#घोषणा PAसूची		BYTE_REF(PAसूची_ADDR)
#घोषणा PADATA		BYTE_REF(PADATA_ADDR)
#घोषणा PAPUEN		BYTE_REF(PAPUEN_ADDR)

#घोषणा PA(x)		(1 << (x))

/* 
 * Port B
 */
#घोषणा PBसूची_ADDR	0xfffff408		/* Port B direction reg */
#घोषणा PBDATA_ADDR	0xfffff409		/* Port B data रेजिस्टर */
#घोषणा PBPUEN_ADDR	0xfffff40a		/* Port B Pull-Up enable reg */
#घोषणा PBSEL_ADDR	0xfffff40b		/* Port B Select Register */

#घोषणा PBसूची		BYTE_REF(PBसूची_ADDR)
#घोषणा PBDATA		BYTE_REF(PBDATA_ADDR)
#घोषणा PBPUEN		BYTE_REF(PBPUEN_ADDR)
#घोषणा PBSEL		BYTE_REF(PBSEL_ADDR)

#घोषणा PB(x)		(1 << (x))

#घोषणा PB_CSB0		0x01	/* Use CSB0      as PB[0] */
#घोषणा PB_CSB1		0x02	/* Use CSB1      as PB[1] */
#घोषणा PB_CSC0_RAS0	0x04    /* Use CSC0/RAS0 as PB[2] */	
#घोषणा PB_CSC1_RAS1	0x08    /* Use CSC1/RAS1 as PB[3] */	
#घोषणा PB_CSD0_CAS0	0x10    /* Use CSD0/CAS0 as PB[4] */	
#घोषणा PB_CSD1_CAS1	0x20    /* Use CSD1/CAS1 as PB[5] */
#घोषणा PB_TIN_TOUT	0x40	/* Use TIN/TOUT  as PB[6] */
#घोषणा PB_PWMO		0x80	/* Use PWMO      as PB[7] */

/* 
 * Port C
 */
#घोषणा PCसूची_ADDR	0xfffff410		/* Port C direction reg */
#घोषणा PCDATA_ADDR	0xfffff411		/* Port C data रेजिस्टर */
#घोषणा PCPDEN_ADDR	0xfffff412		/* Port C Pull-Down enb. reg */
#घोषणा PCSEL_ADDR	0xfffff413		/* Port C Select Register */

#घोषणा PCसूची		BYTE_REF(PCसूची_ADDR)
#घोषणा PCDATA		BYTE_REF(PCDATA_ADDR)
#घोषणा PCPDEN		BYTE_REF(PCPDEN_ADDR)
#घोषणा PCSEL		BYTE_REF(PCSEL_ADDR)

#घोषणा PC(x)		(1 << (x))

#घोषणा PC_LD0		0x01	/* Use LD0  as PC[0] */
#घोषणा PC_LD1		0x02	/* Use LD1  as PC[1] */
#घोषणा PC_LD2		0x04	/* Use LD2  as PC[2] */
#घोषणा PC_LD3		0x08	/* Use LD3  as PC[3] */
#घोषणा PC_LFLM		0x10	/* Use LFLM as PC[4] */
#घोषणा PC_LLP 		0x20	/* Use LLP  as PC[5] */
#घोषणा PC_LCLK		0x40	/* Use LCLK as PC[6] */
#घोषणा PC_LACD		0x80	/* Use LACD as PC[7] */

/* 
 * Port D
 */
#घोषणा PDसूची_ADDR	0xfffff418		/* Port D direction reg */
#घोषणा PDDATA_ADDR	0xfffff419		/* Port D data रेजिस्टर */
#घोषणा PDPUEN_ADDR	0xfffff41a		/* Port D Pull-Up enable reg */
#घोषणा PDSEL_ADDR	0xfffff41b		/* Port D Select Register */
#घोषणा PDPOL_ADDR	0xfffff41c		/* Port D Polarity Register */
#घोषणा PसूचीQEN_ADDR	0xfffff41d		/* Port D IRQ enable रेजिस्टर */
#घोषणा PDKBEN_ADDR	0xfffff41e		/* Port D Keyboard Enable reg */
#घोषणा	PDIQEG_ADDR	0xfffff41f		/* Port D IRQ Edge Register */

#घोषणा PDसूची		BYTE_REF(PDसूची_ADDR)
#घोषणा PDDATA		BYTE_REF(PDDATA_ADDR)
#घोषणा PDPUEN		BYTE_REF(PDPUEN_ADDR)
#घोषणा PDSEL		BYTE_REF(PDSEL_ADDR)
#घोषणा	PDPOL		BYTE_REF(PDPOL_ADDR)
#घोषणा PसूचीQEN		BYTE_REF(PसूचीQEN_ADDR)
#घोषणा PDKBEN		BYTE_REF(PDKBEN_ADDR)
#घोषणा PDIQEG		BYTE_REF(PDIQEG_ADDR)

#घोषणा PD(x)		(1 << (x))

#घोषणा PD_INT0		0x01	/* Use INT0 as PD[0] */
#घोषणा PD_INT1		0x02	/* Use INT1 as PD[1] */
#घोषणा PD_INT2		0x04	/* Use INT2 as PD[2] */
#घोषणा PD_INT3		0x08	/* Use INT3 as PD[3] */
#घोषणा PD_IRQ1		0x10	/* Use IRQ1 as PD[4] */
#घोषणा PD_IRQ2		0x20	/* Use IRQ2 as PD[5] */
#घोषणा PD_IRQ3		0x40	/* Use IRQ3 as PD[6] */
#घोषणा PD_IRQ6		0x80	/* Use IRQ6 as PD[7] */

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

#घोषणा PE(x)		(1 << (x))

#घोषणा PE_SPMTXD	0x01	/* Use SPMTXD as PE[0] */
#घोषणा PE_SPMRXD	0x02	/* Use SPMRXD as PE[1] */
#घोषणा PE_SPMCLK	0x04	/* Use SPMCLK as PE[2] */
#घोषणा PE_DWE		0x08	/* Use DWE    as PE[3] */
#घोषणा PE_RXD		0x10	/* Use RXD    as PE[4] */
#घोषणा PE_TXD		0x20	/* Use TXD    as PE[5] */
#घोषणा PE_RTS		0x40	/* Use RTS    as PE[6] */
#घोषणा PE_CTS		0x80	/* Use CTS    as PE[7] */

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

#घोषणा PF(x)		(1 << (x))

#घोषणा PF_LCONTRAST	0x01	/* Use LCONTRAST as PF[0] */
#घोषणा PF_IRQ5         0x02    /* Use IRQ5      as PF[1] */
#घोषणा PF_CLKO         0x04    /* Use CLKO      as PF[2] */
#घोषणा PF_A20          0x08    /* Use A20       as PF[3] */
#घोषणा PF_A21          0x10    /* Use A21       as PF[4] */
#घोषणा PF_A22          0x20    /* Use A22       as PF[5] */
#घोषणा PF_A23          0x40    /* Use A23       as PF[6] */
#घोषणा PF_CSA1		0x80    /* Use CSA1      as PF[7] */

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

#घोषणा PG(x)		(1 << (x))

#घोषणा PG_BUSW_DTACK	0x01	/* Use BUSW/DTACK as PG[0] */
#घोषणा PG_A0		0x02	/* Use A0         as PG[1] */
#घोषणा PG_EMUIRQ	0x04	/* Use EMUIRQ     as PG[2] */
#घोषणा PG_HIZ_P_D	0x08	/* Use HIZ/P/D    as PG[3] */
#घोषणा PG_EMUCS        0x10	/* Use EMUCS      as PG[4] */
#घोषणा PG_EMUBRK	0x20	/* Use EMUBRK     as PG[5] */

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

#घोषणा PWMC_CLKSEL_MASK	0x0003	/* Clock Selection */
#घोषणा PWMC_CLKSEL_SHIFT	0
#घोषणा PWMC_REPEAT_MASK	0x000c	/* Sample Repeats */
#घोषणा PWMC_REPEAT_SHIFT	2
#घोषणा PWMC_EN			0x0010	/* Enable PWM */
#घोषणा PMNC_FIFOAV		0x0020	/* FIFO Available */
#घोषणा PWMC_IRQEN		0x0040	/* Interrupt Request Enable */
#घोषणा PWMC_IRQ		0x0080	/* Interrupt Request (FIFO empty) */
#घोषणा PWMC_PRESCALER_MASK	0x7f00	/* Incoming Clock prescaler */
#घोषणा PWMC_PRESCALER_SHIFT	8
#घोषणा PWMC_CLKSRC		0x8000	/* Clock Source Select */

/* '328-compatible definitions */
#घोषणा PWMC_PWMEN	PWMC_EN

/*
 * PWM Sample Register 
 */
#घोषणा PWMS_ADDR	0xfffff502
#घोषणा PWMS		WORD_REF(PWMS_ADDR)

/*
 * PWM Period Register
 */
#घोषणा PWMP_ADDR	0xfffff504
#घोषणा PWMP		BYTE_REF(PWMP_ADDR)

/*
 * PWM Counter Register
 */
#घोषणा PWMCNT_ADDR	0xfffff505
#घोषणा PWMCNT		BYTE_REF(PWMCNT_ADDR)

/**********
 *
 * 0xFFFFF6xx -- General-Purpose Timer
 *
 **********/

/* 
 * Timer Control रेजिस्टर
 */
#घोषणा TCTL_ADDR	0xfffff600
#घोषणा TCTL		WORD_REF(TCTL_ADDR)

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

/* '328-compatible definitions */
#घोषणा TCTL1_ADDR	TCTL_ADDR
#घोषणा TCTL1		TCTL

/*
 * Timer Prescaler Register
 */
#घोषणा TPRER_ADDR	0xfffff602
#घोषणा TPRER		WORD_REF(TPRER_ADDR)

/* '328-compatible definitions */
#घोषणा TPRER1_ADDR	TPRER_ADDR
#घोषणा TPRER1		TPRER

/*
 * Timer Compare Register
 */
#घोषणा TCMP_ADDR	0xfffff604
#घोषणा TCMP		WORD_REF(TCMP_ADDR)

/* '328-compatible definitions */
#घोषणा TCMP1_ADDR	TCMP_ADDR
#घोषणा TCMP1		TCMP

/*
 * Timer Capture रेजिस्टर
 */
#घोषणा TCR_ADDR	0xfffff606
#घोषणा TCR		WORD_REF(TCR_ADDR)

/* '328-compatible definitions */
#घोषणा TCR1_ADDR	TCR_ADDR
#घोषणा TCR1		TCR

/*
 * Timer Counter Register
 */
#घोषणा TCN_ADDR	0xfffff608
#घोषणा TCN		WORD_REF(TCN_ADDR)

/* '328-compatible definitions */
#घोषणा TCN1_ADDR	TCN_ADDR
#घोषणा TCN1		TCN

/*
 * Timer Status Register
 */
#घोषणा TSTAT_ADDR	0xfffff60a
#घोषणा TSTAT		WORD_REF(TSTAT_ADDR)

#घोषणा TSTAT_COMP	0x0001		/* Compare Event occurred */
#घोषणा TSTAT_CAPT	0x0001		/* Capture Event occurred */

/* '328-compatible definitions */
#घोषणा TSTAT1_ADDR	TSTAT_ADDR
#घोषणा TSTAT1		TSTAT

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
#घोषणा SPIMCONT_IRQ		 0x0080	/* Interrupt Request */
#घोषणा SPIMCONT_XCH		 0x0100	/* Exchange */
#घोषणा SPIMCONT_ENABLE		 0x0200	/* Enable SPIM */
#घोषणा SPIMCONT_DATA_RATE_MASK	 0xe000	/* SPIM Data Rate */
#घोषणा SPIMCONT_DATA_RATE_SHIFT 13

/* '328-compatible definitions */
#घोषणा SPIMCONT_SPIMIRQ	SPIMCONT_IRQ
#घोषणा SPIMCONT_SPIMEN		SPIMCONT_ENABLE

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

#घोषणा USTCNT_TXAE	0x0001	/* Transmitter Available Interrupt Enable */
#घोषणा USTCNT_TXHE	0x0002	/* Transmitter Half Empty Enable */
#घोषणा USTCNT_TXEE	0x0004	/* Transmitter Empty Interrupt Enable */
#घोषणा USTCNT_RXRE	0x0008	/* Receiver Ready Interrupt Enable */
#घोषणा USTCNT_RXHE	0x0010	/* Receiver Half-Full Interrupt Enable */
#घोषणा USTCNT_RXFE	0x0020	/* Receiver Full Interrupt Enable */
#घोषणा USTCNT_CTSD	0x0040	/* CTS Delta Interrupt Enable */
#घोषणा USTCNT_ODEN	0x0080	/* Old Data Interrupt Enable */
#घोषणा USTCNT_8_7	0x0100	/* Eight or seven-bit transmission */
#घोषणा USTCNT_STOP	0x0200	/* Stop bit transmission */
#घोषणा USTCNT_ODD	0x0400	/* Odd Parity */
#घोषणा	USTCNT_PEN	0x0800	/* Parity Enable */
#घोषणा USTCNT_CLKM	0x1000	/* Clock Mode Select */
#घोषणा	USTCNT_TXEN	0x2000	/* Transmitter Enable */
#घोषणा USTCNT_RXEN	0x4000	/* Receiver Enable */
#घोषणा USTCNT_UEN	0x8000	/* UART Enable */

/* '328-compatible definitions */
#घोषणा USTCNT_TXAVAILEN	USTCNT_TXAE
#घोषणा USTCNT_TXHALFEN		USTCNT_TXHE
#घोषणा USTCNT_TXEMPTYEN	USTCNT_TXEE
#घोषणा USTCNT_RXREADYEN	USTCNT_RXRE
#घोषणा USTCNT_RXHALFEN		USTCNT_RXHE
#घोषणा USTCNT_RXFULLEN		USTCNT_RXFE
#घोषणा USTCNT_CTSDELTAEN	USTCNT_CTSD
#घोषणा USTCNT_ODD_EVEN		USTCNT_ODD
#घोषणा USTCNT_PARITYEN		USTCNT_PEN
#घोषणा USTCNT_CLKMODE		USTCNT_CLKM
#घोषणा USTCNT_UARTEN		USTCNT_UEN

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
#घोषणा UBAUD_UCLKसूची		0x2000	/* UCLK Direction */

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
#घोषणा URX_OLD_DATA	 0x1000	/* Old data in FIFO */
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
#घोषणा UTX_CTS_STAT	 0x0200	/* CTS State */
#घोषणा	UTX_BUSY	 0x0400	/* FIFO is busy, sending a अक्षरacter */
#घोषणा	UTX_NOCTS	 0x0800	/* Ignore CTS */
#घोषणा UTX_SEND_BREAK	 0x1000	/* Send a BREAK */
#घोषणा UTX_TX_AVAIL	 0x2000	/* Transmit FIFO has a slot available */
#घोषणा UTX_FIFO_HALF	 0x4000	/* Transmit FIFO is half empty */
#घोषणा UTX_FIFO_EMPTY	 0x8000	/* Transmit FIFO is empty */

/* '328-compatible definitions */
#घोषणा UTX_CTS_STATUS	UTX_CTS_STAT
#घोषणा UTX_IGNORE_CTS	UTX_NOCTS

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
#घोषणा UMISC_IR_TEST	 0x0400	/* IRDA Test Enable */
#घोषणा UMISC_BAUD_RESET 0x0800	/* Reset Baud Rate Generation Counters */
#घोषणा UMISC_LOOP	 0x1000	/* Serial Loopback Enable */
#घोषणा UMISC_FORCE_PERR 0x2000	/* Force Parity Error */
#घोषणा UMISC_CLKSRC	 0x4000	/* Clock Source */
#घोषणा UMISC_BAUD_TEST	 0x8000	/* Enable Baud Test Mode */

/* 
 * UART Non-पूर्णांकeger Prescaler Register
 */
#घोषणा NIPR_ADDR	0xfffff90a
#घोषणा NIPR		WORD_REF(NIPR_ADDR)

#घोषणा NIPR_STEP_VALUE_MASK	0x00ff	/* NI prescaler step value */
#घोषणा NIPR_STEP_VALUE_SHIFT	0
#घोषणा NIPR_SELECT_MASK	0x0700	/* Tap Selection */
#घोषणा NIPR_SELECT_SHIFT	8
#घोषणा NIPR_PRE_SEL		0x8000	/* Non-पूर्णांकeger prescaler select */


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
  अस्थिर अचिन्हित लघु पूर्णांक nipr;
  अस्थिर अचिन्हित लघु पूर्णांक pad1;
  अस्थिर अचिन्हित लघु पूर्णांक pad2;
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

#घोषणा LSSA_SSA_MASK	0x1ffffffe	/* Bits 0 and 29-31 are reserved */

/*
 * LCD Virtual Page Width Register 
 */
#घोषणा LVPW_ADDR	0xfffffa05
#घोषणा LVPW		BYTE_REF(LVPW_ADDR)

/*
 * LCD Screen Width Register (not compatible with '328 !!!) 
 */
#घोषणा LXMAX_ADDR	0xfffffa08
#घोषणा LXMAX		WORD_REF(LXMAX_ADDR)

#घोषणा LXMAX_XM_MASK	0x02f0		/* Bits 0-3 and 10-15 are reserved */

/*
 * LCD Screen Height Register
 */
#घोषणा LYMAX_ADDR	0xfffffa0a
#घोषणा LYMAX		WORD_REF(LYMAX_ADDR)

#घोषणा LYMAX_YM_MASK	0x01ff		/* Bits 9-15 are reserved */

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

#घोषणा LPICF_GS_MASK	 0x03	 /* Gray-Scale Mode */
#घोषणा	  LPICF_GS_BW	   0x00
#घोषणा   LPICF_GS_GRAY_4  0x01
#घोषणा   LPICF_GS_GRAY_16 0x02
#घोषणा LPICF_PBSIZ_MASK 0x0c	/* Panel Bus Width */
#घोषणा   LPICF_PBSIZ_1	   0x00
#घोषणा   LPICF_PBSIZ_2    0x04
#घोषणा   LPICF_PBSIZ_4    0x08

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

#घोषणा LACDRC_ACDSLT	 0x80	/* Signal Source Select */
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

#घोषणा LCKCON_DWS_MASK	 0x0f	/* Display Wait-State */
#घोषणा LCKCON_DWS_SHIFT 0
#घोषणा LCKCON_DWIDTH	 0x40	/* Display Memory Width  */
#घोषणा LCKCON_LCDON	 0x80	/* Enable LCD Controller */

/* '328-compatible definitions */
#घोषणा LCKCON_DW_MASK  LCKCON_DWS_MASK
#घोषणा LCKCON_DW_SHIFT LCKCON_DWS_SHIFT
 
/*
 * LCD Refresh Rate Adjusपंचांगent Register 
 */
#घोषणा LRRA_ADDR	0xfffffa29
#घोषणा LRRA		BYTE_REF(LRRA_ADDR)

/*
 * LCD Panning Offset Register
 */
#घोषणा LPOSR_ADDR	0xfffffa2d
#घोषणा LPOSR		BYTE_REF(LPOSR_ADDR)

#घोषणा LPOSR_POS_MASK	0x0f	/* Pixel Offset Code */
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
#घोषणा LGPMR_ADDR	0xfffffa33
#घोषणा LGPMR		BYTE_REF(LGPMR_ADDR)

#घोषणा LGPMR_G1_MASK	0x0f
#घोषणा LGPMR_G1_SHIFT	0
#घोषणा LGPMR_G2_MASK	0xf0
#घोषणा LGPMR_G2_SHIFT	4

/* 
 * PWM Contrast Control Register
 */
#घोषणा PWMR_ADDR	0xfffffa36
#घोषणा PWMR		WORD_REF(PWMR_ADDR)

#घोषणा PWMR_PW_MASK	0x00ff	/* Pulse Width */
#घोषणा PWMR_PW_SHIFT	0
#घोषणा PWMR_CCPEN	0x0100	/* Contrast Control Enable */
#घोषणा PWMR_SRC_MASK	0x0600	/* Input Clock Source */
#घोषणा   PWMR_SRC_LINE	  0x0000	/* Line Pulse  */
#घोषणा   PWMR_SRC_PIXEL  0x0200	/* Pixel Clock */
#घोषणा   PWMR_SRC_LCD    0x4000	/* LCD घड़ी   */

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
 * Watchकरोg Timer Register 
 */
#घोषणा WATCHDOG_ADDR	0xfffffb0a
#घोषणा WATCHDOG	WORD_REF(WATCHDOG_ADDR)

#घोषणा WATCHDOG_EN	0x0001	/* Watchकरोg Enabled */
#घोषणा WATCHDOG_ISEL	0x0002	/* Select the watchकरोg पूर्णांकerrupt */
#घोषणा WATCHDOG_INTF	0x0080	/* Watchकरोg पूर्णांकerrupt occurred */
#घोषणा WATCHDOG_CNT_MASK  0x0300	/* Watchकरोg Counter */
#घोषणा WATCHDOG_CNT_SHIFT 8

/*
 * RTC Control Register
 */
#घोषणा RTCCTL_ADDR	0xfffffb0c
#घोषणा RTCCTL		WORD_REF(RTCCTL_ADDR)

#घोषणा RTCCTL_XTL	0x0020	/* Crystal Selection */
#घोषणा RTCCTL_EN	0x0080	/* RTC Enable */

/* '328-compatible definitions */
#घोषणा RTCCTL_384	RTCCTL_XTL
#घोषणा RTCCTL_ENABLE	RTCCTL_EN

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
#घोषणा RTCISR_HR	0x0020	/* 1-hour पूर्णांकerrupt has occurred */
#घोषणा RTCISR_SAM0	0x0100	/*   4Hz /   4.6875Hz पूर्णांकerrupt has occurred */ 
#घोषणा RTCISR_SAM1	0x0200	/*   8Hz /   9.3750Hz पूर्णांकerrupt has occurred */ 
#घोषणा RTCISR_SAM2	0x0400	/*  16Hz /  18.7500Hz पूर्णांकerrupt has occurred */ 
#घोषणा RTCISR_SAM3	0x0800	/*  32Hz /  37.5000Hz पूर्णांकerrupt has occurred */ 
#घोषणा RTCISR_SAM4	0x1000	/*  64Hz /  75.0000Hz पूर्णांकerrupt has occurred */ 
#घोषणा RTCISR_SAM5	0x2000	/* 128Hz / 150.0000Hz पूर्णांकerrupt has occurred */ 
#घोषणा RTCISR_SAM6	0x4000	/* 256Hz / 300.0000Hz पूर्णांकerrupt has occurred */ 
#घोषणा RTCISR_SAM7	0x8000	/* 512Hz / 600.0000Hz पूर्णांकerrupt has occurred */ 

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
#घोषणा RTCIENR_HR	0x0020	/* 1-hour पूर्णांकerrupt enable */
#घोषणा RTCIENR_SAM0	0x0100	/*   4Hz /   4.6875Hz पूर्णांकerrupt enable */ 
#घोषणा RTCIENR_SAM1	0x0200	/*   8Hz /   9.3750Hz पूर्णांकerrupt enable */ 
#घोषणा RTCIENR_SAM2	0x0400	/*  16Hz /  18.7500Hz पूर्णांकerrupt enable */ 
#घोषणा RTCIENR_SAM3	0x0800	/*  32Hz /  37.5000Hz पूर्णांकerrupt enable */ 
#घोषणा RTCIENR_SAM4	0x1000	/*  64Hz /  75.0000Hz पूर्णांकerrupt enable */ 
#घोषणा RTCIENR_SAM5	0x2000	/* 128Hz / 150.0000Hz पूर्णांकerrupt enable */ 
#घोषणा RTCIENR_SAM6	0x4000	/* 256Hz / 300.0000Hz पूर्णांकerrupt enable */ 
#घोषणा RTCIENR_SAM7	0x8000	/* 512Hz / 600.0000Hz पूर्णांकerrupt enable */ 

/* 
 * Stopwatch Minutes Register
 */
#घोषणा STPWCH_ADDR	0xfffffb12
#घोषणा STPWCH		WORD_REF(STPWCH)

#घोषणा STPWCH_CNT_MASK	 0x003f	/* Stopwatch countकरोwn value */
#घोषणा SPTWCH_CNT_SHIFT 0

/*
 * RTC Day Count Register 
 */
#घोषणा DAYR_ADDR	0xfffffb1a
#घोषणा DAYR		WORD_REF(DAYR_ADDR)

#घोषणा DAYR_DAYS_MASK	0x1ff	/* Day Setting */
#घोषणा DAYR_DAYS_SHIFT 0

/*
 * RTC Day Alarm Register 
 */
#घोषणा DAYALARM_ADDR	0xfffffb1c
#घोषणा DAYALARM	WORD_REF(DAYALARM_ADDR)

#घोषणा DAYALARM_DAYSAL_MASK	0x01ff	/* Day Setting of the Alarm */
#घोषणा DAYALARM_DAYSAL_SHIFT 	0

/**********
 *
 * 0xFFFFFCxx -- DRAM Controller
 *
 **********/

/*
 * DRAM Memory Configuration Register 
 */
#घोषणा DRAMMC_ADDR	0xfffffc00
#घोषणा DRAMMC		WORD_REF(DRAMMC_ADDR)

#घोषणा DRAMMC_ROW12_MASK	0xc000	/* Row address bit क्रम MD12 */
#घोषणा   DRAMMC_ROW12_PA10	0x0000
#घोषणा   DRAMMC_ROW12_PA21	0x4000	
#घोषणा   DRAMMC_ROW12_PA23	0x8000
#घोषणा	DRAMMC_ROW0_MASK	0x3000	/* Row address bit क्रम MD0 */
#घोषणा	  DRAMMC_ROW0_PA11	0x0000
#घोषणा   DRAMMC_ROW0_PA22	0x1000
#घोषणा   DRAMMC_ROW0_PA23	0x2000
#घोषणा DRAMMC_ROW11		0x0800	/* Row address bit क्रम MD11 PA20/PA22 */
#घोषणा DRAMMC_ROW10		0x0400	/* Row address bit क्रम MD10 PA19/PA21 */
#घोषणा	DRAMMC_ROW9		0x0200	/* Row address bit क्रम MD9  PA9/PA19  */
#घोषणा DRAMMC_ROW8		0x0100	/* Row address bit क्रम MD8  PA10/PA20 */
#घोषणा DRAMMC_COL10		0x0080	/* Col address bit क्रम MD10 PA11/PA0  */
#घोषणा DRAMMC_COL9		0x0040	/* Col address bit क्रम MD9  PA10/PA0  */
#घोषणा DRAMMC_COL8		0x0020	/* Col address bit क्रम MD8  PA9/PA0   */
#घोषणा DRAMMC_REF_MASK		0x001f	/* Refresh Cycle */
#घोषणा DRAMMC_REF_SHIFT	0

/*
 * DRAM Control Register
 */
#घोषणा DRAMC_ADDR	0xfffffc02
#घोषणा DRAMC		WORD_REF(DRAMC_ADDR)

#घोषणा DRAMC_DWE	   0x0001	/* DRAM Write Enable */
#घोषणा DRAMC_RST	   0x0002	/* Reset Burst Refresh Enable */
#घोषणा DRAMC_LPR	   0x0004	/* Low-Power Refresh Enable */
#घोषणा DRAMC_SLW	   0x0008	/* Slow RAM */
#घोषणा DRAMC_LSP	   0x0010	/* Light Sleep */
#घोषणा DRAMC_MSW	   0x0020	/* Slow Multiplexing */
#घोषणा DRAMC_WS_MASK	   0x00c0	/* Wait-states */
#घोषणा DRAMC_WS_SHIFT	   6
#घोषणा DRAMC_PGSZ_MASK    0x0300	/* Page Size क्रम fast page mode */
#घोषणा DRAMC_PGSZ_SHIFT   8
#घोषणा   DRAMC_PGSZ_256K  0x0000	
#घोषणा   DRAMC_PGSZ_512K  0x0100
#घोषणा   DRAMC_PGSZ_1024K 0x0200
#घोषणा	  DRAMC_PGSZ_2048K 0x0300
#घोषणा DRAMC_EDO	   0x0400	/* EDO DRAM */
#घोषणा DRAMC_CLK	   0x0800	/* Refresh Timer Clock source select */
#घोषणा DRAMC_BC_MASK	   0x3000	/* Page Access Clock Cycle (FP mode) */
#घोषणा DRAMC_BC_SHIFT	   12
#घोषणा DRAMC_RM	   0x4000	/* Refresh Mode */
#घोषणा DRAMC_EN	   0x8000	/* DRAM Controller enable */


/**********
 *
 * 0xFFFFFDxx -- In-Circuit Emulation (ICE)
 *
 **********/

/*
 * ICE Module Address Compare Register
 */
#घोषणा ICEMACR_ADDR	0xfffffd00
#घोषणा ICEMACR		LONG_REF(ICEMACR_ADDR)

/*
 * ICE Module Address Mask Register
 */
#घोषणा ICEMAMR_ADDR	0xfffffd04
#घोषणा ICEMAMR		LONG_REF(ICEMAMR_ADDR)

/*
 * ICE Module Control Compare Register
 */
#घोषणा ICEMCCR_ADDR	0xfffffd08
#घोषणा ICEMCCR		WORD_REF(ICEMCCR_ADDR)

#घोषणा ICEMCCR_PD	0x0001	/* Program/Data Cycle Selection */
#घोषणा ICEMCCR_RW	0x0002	/* Read/Write Cycle Selection */

/*
 * ICE Module Control Mask Register
 */
#घोषणा ICEMCMR_ADDR	0xfffffd0a
#घोषणा ICEMCMR		WORD_REF(ICEMCMR_ADDR)

#घोषणा ICEMCMR_PDM	0x0001	/* Program/Data Cycle Mask */
#घोषणा ICEMCMR_RWM	0x0002	/* Read/Write Cycle Mask */

/*
 * ICE Module Control Register 
 */
#घोषणा ICEMCR_ADDR	0xfffffd0c
#घोषणा ICEMCR		WORD_REF(ICEMCR_ADDR)

#घोषणा ICEMCR_CEN	0x0001	/* Compare Enable */
#घोषणा ICEMCR_PBEN	0x0002	/* Program Break Enable */
#घोषणा ICEMCR_SB	0x0004	/* Single Breakpoपूर्णांक */
#घोषणा ICEMCR_HMDIS	0x0008	/* HardMap disable */
#घोषणा ICEMCR_BBIEN	0x0010	/* Bus Break Interrupt Enable */

/*
 * ICE Module Status Register 
 */
#घोषणा ICEMSR_ADDR	0xfffffd0e
#घोषणा ICEMSR		WORD_REF(ICEMSR_ADDR)

#घोषणा ICEMSR_EMUEN	0x0001	/* Emulation Enable */
#घोषणा ICEMSR_BRKIRQ	0x0002	/* A-Line Vector Fetch Detected */
#घोषणा ICEMSR_BBIRQ	0x0004	/* Bus Break Interrupt Detected */
#घोषणा ICEMSR_EMIRQ	0x0008	/* EMUIRQ Falling Edge Detected */

#पूर्ण_अगर /* _MC68EZ328_H_ */
