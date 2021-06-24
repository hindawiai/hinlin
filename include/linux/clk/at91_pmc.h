<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/clk/at91_pmc.h
 *
 * Copyright (C) 2005 Ivan Kokshaysky
 * Copyright (C) SAN People
 *
 * Power Management Controller (PMC) - System peripherals रेजिस्टरs.
 * Based on AT91RM9200 datasheet revision E.
 */

#अगर_अघोषित AT91_PMC_H
#घोषणा AT91_PMC_H

#घोषणा AT91_PMC_V1		(1)			/* PMC version 1 */
#घोषणा AT91_PMC_V2		(2)			/* PMC version 2 [SAM9X60] */

#घोषणा	AT91_PMC_SCER		0x00			/* System Clock Enable Register */
#घोषणा	AT91_PMC_SCDR		0x04			/* System Clock Disable Register */

#घोषणा	AT91_PMC_SCSR		0x08			/* System Clock Status Register */
#घोषणा		AT91_PMC_PCK		(1 <<  0)		/* Processor Clock */
#घोषणा		AT91RM9200_PMC_UDP	(1 <<  1)		/* USB Devcice Port Clock [AT91RM9200 only] */
#घोषणा		AT91RM9200_PMC_MCKUDP	(1 <<  2)		/* USB Device Port Master Clock Automatic Disable on Suspend [AT91RM9200 only] */
#घोषणा		AT91RM9200_PMC_UHP	(1 <<  4)		/* USB Host Port Clock [AT91RM9200 only] */
#घोषणा		AT91SAM926x_PMC_UHP	(1 <<  6)		/* USB Host Port Clock [AT91SAM926x only] */
#घोषणा		AT91SAM926x_PMC_UDP	(1 <<  7)		/* USB Devcice Port Clock [AT91SAM926x only] */
#घोषणा		AT91_PMC_PCK0		(1 <<  8)		/* Programmable Clock 0 */
#घोषणा		AT91_PMC_PCK1		(1 <<  9)		/* Programmable Clock 1 */
#घोषणा		AT91_PMC_PCK2		(1 << 10)		/* Programmable Clock 2 */
#घोषणा		AT91_PMC_PCK3		(1 << 11)		/* Programmable Clock 3 */
#घोषणा		AT91_PMC_PCK4		(1 << 12)		/* Programmable Clock 4 [AT572D940HF only] */
#घोषणा		AT91_PMC_HCK0		(1 << 16)		/* AHB Clock (USB host) [AT91SAM9261 only] */
#घोषणा		AT91_PMC_HCK1		(1 << 17)		/* AHB Clock (LCD) [AT91SAM9261 only] */

#घोषणा AT91_PMC_PLL_CTRL0		0x0C		/* PLL Control Register 0 [क्रम SAM9X60] */
#घोषणा		AT91_PMC_PLL_CTRL0_ENPLL	(1 << 28)	/* Enable PLL */
#घोषणा		AT91_PMC_PLL_CTRL0_ENPLLCK	(1 << 29)	/* Enable PLL घड़ी क्रम PMC */
#घोषणा		AT91_PMC_PLL_CTRL0_ENLOCK	(1 << 31)	/* Enable PLL lock */

#घोषणा AT91_PMC_PLL_CTRL1		0x10		/* PLL Control Register 1 [क्रम SAM9X60] */

#घोषणा	AT91_PMC_PCER		0x10			/* Peripheral Clock Enable Register */
#घोषणा	AT91_PMC_PCDR		0x14			/* Peripheral Clock Disable Register */
#घोषणा	AT91_PMC_PCSR		0x18			/* Peripheral Clock Status Register */

#घोषणा AT91_PMC_PLL_ACR	0x18			/* PLL Analog Control Register [क्रम SAM9X60] */
#घोषणा		AT91_PMC_PLL_ACR_DEFAULT_UPLL	0x12020010UL	/* Default PLL ACR value क्रम UPLL */
#घोषणा		AT91_PMC_PLL_ACR_DEFAULT_PLLA	0x00020010UL	/* Default PLL ACR value क्रम PLLA */
#घोषणा		AT91_PMC_PLL_ACR_UTMIVR		(1 << 12)	/* UPLL Voltage regulator Control */
#घोषणा		AT91_PMC_PLL_ACR_UTMIBG		(1 << 13)	/* UPLL Bandgap Control */

#घोषणा	AT91_CKGR_UCKR		0x1C			/* UTMI Clock Register [some SAM9] */
#घोषणा		AT91_PMC_UPLLEN		(1   << 16)		/* UTMI PLL Enable */
#घोषणा		AT91_PMC_UPLLCOUNT	(0xf << 20)		/* UTMI PLL Start-up Time */
#घोषणा		AT91_PMC_BIASEN		(1   << 24)		/* UTMI BIAS Enable */
#घोषणा		AT91_PMC_BIASCOUNT	(0xf << 28)		/* UTMI BIAS Start-up Time */

#घोषणा AT91_PMC_PLL_UPDT		0x1C		/* PMC PLL update रेजिस्टर [क्रम SAM9X60] */
#घोषणा		AT91_PMC_PLL_UPDT_UPDATE	(1 << 8)	/* Update PLL settings */
#घोषणा		AT91_PMC_PLL_UPDT_ID		(1 << 0)	/* PLL ID */
#घोषणा		AT91_PMC_PLL_UPDT_ID_MSK	(0xf)		/* PLL ID mask */
#घोषणा		AT91_PMC_PLL_UPDT_STUPTIM	(0xff << 16)	/* Startup समय */

#घोषणा	AT91_CKGR_MOR		0x20			/* Main Oscillator Register [not on SAM9RL] */
#घोषणा		AT91_PMC_MOSCEN		(1    <<  0)		/* Main Oscillator Enable */
#घोषणा		AT91_PMC_OSCBYPASS	(1    <<  1)		/* Oscillator Bypass */
#घोषणा		AT91_PMC_WAITMODE	(1    <<  2)		/* Wait Mode Command */
#घोषणा		AT91_PMC_MOSCRCEN	(1    <<  3)		/* Main On-Chip RC Oscillator Enable [some SAM9] */
#घोषणा		AT91_PMC_OSCOUNT	(0xff <<  8)		/* Main Oscillator Start-up Time */
#घोषणा		AT91_PMC_KEY_MASK	(0xff << 16)
#घोषणा		AT91_PMC_KEY		(0x37 << 16)		/* MOR Writing Key */
#घोषणा		AT91_PMC_MOSCSEL	(1    << 24)		/* Main Oscillator Selection [some SAM9] */
#घोषणा		AT91_PMC_CFDEN		(1    << 25)		/* Clock Failure Detector Enable [some SAM9] */

#घोषणा	AT91_CKGR_MCFR		0x24			/* Main Clock Frequency Register */
#घोषणा		AT91_PMC_MAINF		(0xffff <<  0)		/* Main Clock Frequency */
#घोषणा		AT91_PMC_MAINRDY	(1	<< 16)		/* Main Clock Ready */

#घोषणा	AT91_CKGR_PLLAR		0x28			/* PLL A Register */
#घोषणा	AT91_CKGR_PLLBR		0x2c			/* PLL B Register */
#घोषणा		AT91_PMC_DIV		(0xff  <<  0)		/* Divider */
#घोषणा		AT91_PMC_PLLCOUNT	(0x3f  <<  8)		/* PLL Counter */
#घोषणा		AT91_PMC_OUT		(3     << 14)		/* PLL Clock Frequency Range */
#घोषणा		AT91_PMC_MUL		(0x7ff << 16)		/* PLL Multiplier */
#घोषणा		AT91_PMC_MUL_GET(n)	((n) >> 16 & 0x7ff)
#घोषणा		AT91_PMC3_MUL		(0x7f  << 18)		/* PLL Multiplier [SAMA5 only] */
#घोषणा		AT91_PMC3_MUL_GET(n)	((n) >> 18 & 0x7f)
#घोषणा		AT91_PMC_USBDIV		(3     << 28)		/* USB Divisor (PLLB only) */
#घोषणा			AT91_PMC_USBDIV_1		(0 << 28)
#घोषणा			AT91_PMC_USBDIV_2		(1 << 28)
#घोषणा			AT91_PMC_USBDIV_4		(2 << 28)
#घोषणा		AT91_PMC_USB96M		(1     << 28)		/* Divider by 2 Enable (PLLB only) */

#घोषणा AT91_PMC_CPU_CKR	0x28			/* CPU Clock Register */

#घोषणा	AT91_PMC_MCKR		0x30			/* Master Clock Register */
#घोषणा		AT91_PMC_CSS		(3 <<  0)		/* Master Clock Selection */
#घोषणा			AT91_PMC_CSS_SLOW		(0 << 0)
#घोषणा			AT91_PMC_CSS_MAIN		(1 << 0)
#घोषणा			AT91_PMC_CSS_PLLA		(2 << 0)
#घोषणा			AT91_PMC_CSS_PLLB		(3 << 0)
#घोषणा			AT91_PMC_CSS_UPLL		(3 << 0)	/* [some SAM9 only] */
#घोषणा		PMC_PRES_OFFSET		2
#घोषणा		AT91_PMC_PRES		(7 <<  PMC_PRES_OFFSET)		/* Master Clock Prescaler */
#घोषणा			AT91_PMC_PRES_1			(0 << PMC_PRES_OFFSET)
#घोषणा			AT91_PMC_PRES_2			(1 << PMC_PRES_OFFSET)
#घोषणा			AT91_PMC_PRES_4			(2 << PMC_PRES_OFFSET)
#घोषणा			AT91_PMC_PRES_8			(3 << PMC_PRES_OFFSET)
#घोषणा			AT91_PMC_PRES_16		(4 << PMC_PRES_OFFSET)
#घोषणा			AT91_PMC_PRES_32		(5 << PMC_PRES_OFFSET)
#घोषणा			AT91_PMC_PRES_64		(6 << PMC_PRES_OFFSET)
#घोषणा		PMC_ALT_PRES_OFFSET	4
#घोषणा		AT91_PMC_ALT_PRES	(7 <<  PMC_ALT_PRES_OFFSET)		/* Master Clock Prescaler [alternate location] */
#घोषणा			AT91_PMC_ALT_PRES_1		(0 << PMC_ALT_PRES_OFFSET)
#घोषणा			AT91_PMC_ALT_PRES_2		(1 << PMC_ALT_PRES_OFFSET)
#घोषणा			AT91_PMC_ALT_PRES_4		(2 << PMC_ALT_PRES_OFFSET)
#घोषणा			AT91_PMC_ALT_PRES_8		(3 << PMC_ALT_PRES_OFFSET)
#घोषणा			AT91_PMC_ALT_PRES_16		(4 << PMC_ALT_PRES_OFFSET)
#घोषणा			AT91_PMC_ALT_PRES_32		(5 << PMC_ALT_PRES_OFFSET)
#घोषणा			AT91_PMC_ALT_PRES_64		(6 << PMC_ALT_PRES_OFFSET)
#घोषणा		AT91_PMC_MDIV		(3 <<  8)		/* Master Clock Division */
#घोषणा			AT91RM9200_PMC_MDIV_1		(0 << 8)	/* [AT91RM9200 only] */
#घोषणा			AT91RM9200_PMC_MDIV_2		(1 << 8)
#घोषणा			AT91RM9200_PMC_MDIV_3		(2 << 8)
#घोषणा			AT91RM9200_PMC_MDIV_4		(3 << 8)
#घोषणा			AT91SAM9_PMC_MDIV_1		(0 << 8)	/* [SAM9 only] */
#घोषणा			AT91SAM9_PMC_MDIV_2		(1 << 8)
#घोषणा			AT91SAM9_PMC_MDIV_4		(2 << 8)
#घोषणा			AT91SAM9_PMC_MDIV_6		(3 << 8)	/* [some SAM9 only] */
#घोषणा			AT91SAM9_PMC_MDIV_3		(3 << 8)	/* [some SAM9 only] */
#घोषणा		AT91_PMC_PDIV		(1 << 12)		/* Processor Clock Division [some SAM9 only] */
#घोषणा			AT91_PMC_PDIV_1			(0 << 12)
#घोषणा			AT91_PMC_PDIV_2			(1 << 12)
#घोषणा		AT91_PMC_PLLADIV2	(1 << 12)		/* PLLA भागisor by 2 [some SAM9 only] */
#घोषणा			AT91_PMC_PLLADIV2_OFF		(0 << 12)
#घोषणा			AT91_PMC_PLLADIV2_ON		(1 << 12)
#घोषणा		AT91_PMC_H32MXDIV	BIT(24)

#घोषणा AT91_PMC_XTALF		0x34			/* Main XTAL Frequency Register [SAMA7G5 only] */

#घोषणा	AT91_PMC_USB		0x38			/* USB Clock Register [some SAM9 only] */
#घोषणा		AT91_PMC_USBS		(0x1 <<  0)		/* USB OHCI Input घड़ी selection */
#घोषणा			AT91_PMC_USBS_PLLA		(0 << 0)
#घोषणा			AT91_PMC_USBS_UPLL		(1 << 0)
#घोषणा			AT91_PMC_USBS_PLLB		(1 << 0)	/* [AT91SAMN12 only] */
#घोषणा		AT91_PMC_OHCIUSBDIV	(0xF <<  8)		/* Divider क्रम USB OHCI Clock */
#घोषणा			AT91_PMC_OHCIUSBDIV_1	(0x0 <<  8)
#घोषणा			AT91_PMC_OHCIUSBDIV_2	(0x1 <<  8)

#घोषणा	AT91_PMC_SMD		0x3c			/* Soft Modem Clock Register [some SAM9 only] */
#घोषणा		AT91_PMC_SMDS		(0x1  <<  0)		/* SMD input घड़ी selection */
#घोषणा		AT91_PMC_SMD_DIV	(0x1f <<  8)		/* SMD input घड़ी भागider */
#घोषणा		AT91_PMC_SMDDIV(n)	(((n) <<  8) & AT91_PMC_SMD_DIV)

#घोषणा	AT91_PMC_PCKR(n)	(0x40 + ((n) * 4))	/* Programmable Clock 0-N Registers */
#घोषणा		AT91_PMC_ALT_PCKR_CSS	(0x7 <<  0)		/* Programmable Clock Source Selection [alternate length] */
#घोषणा			AT91_PMC_CSS_MASTER		(4 << 0)	/* [some SAM9 only] */
#घोषणा		AT91_PMC_CSSMCK		(0x1 <<  8)		/* CSS or Master Clock Selection */
#घोषणा			AT91_PMC_CSSMCK_CSS		(0 << 8)
#घोषणा			AT91_PMC_CSSMCK_MCK		(1 << 8)

#घोषणा	AT91_PMC_IER		0x60			/* Interrupt Enable Register */
#घोषणा	AT91_PMC_IDR		0x64			/* Interrupt Disable Register */
#घोषणा	AT91_PMC_SR		0x68			/* Status Register */
#घोषणा		AT91_PMC_MOSCS		(1 <<  0)		/* MOSCS Flag */
#घोषणा		AT91_PMC_LOCKA		(1 <<  1)		/* PLLA Lock */
#घोषणा		AT91_PMC_LOCKB		(1 <<  2)		/* PLLB Lock */
#घोषणा		AT91_PMC_MCKRDY		(1 <<  3)		/* Master Clock */
#घोषणा		AT91_PMC_LOCKU		(1 <<  6)		/* UPLL Lock [some SAM9] */
#घोषणा		AT91_PMC_OSCSEL		(1 <<  7)		/* Slow Oscillator Selection [some SAM9] */
#घोषणा		AT91_PMC_PCK0RDY	(1 <<  8)		/* Programmable Clock 0 */
#घोषणा		AT91_PMC_PCK1RDY	(1 <<  9)		/* Programmable Clock 1 */
#घोषणा		AT91_PMC_PCK2RDY	(1 << 10)		/* Programmable Clock 2 */
#घोषणा		AT91_PMC_PCK3RDY	(1 << 11)		/* Programmable Clock 3 */
#घोषणा		AT91_PMC_MOSCSELS	(1 << 16)		/* Main Oscillator Selection [some SAM9] */
#घोषणा		AT91_PMC_MOSCRCS	(1 << 17)		/* Main On-Chip RC [some SAM9] */
#घोषणा		AT91_PMC_CFDEV		(1 << 18)		/* Clock Failure Detector Event [some SAM9] */
#घोषणा		AT91_PMC_GCKRDY		(1 << 24)		/* Generated Clocks */
#घोषणा		AT91_PMC_MCKXRDY	(1 << 26)		/* Master Clock x [x=1..4] Ready Status */
#घोषणा	AT91_PMC_IMR		0x6c			/* Interrupt Mask Register */

#घोषणा AT91_PMC_FSMR		0x70		/* Fast Startup Mode Register */
#घोषणा AT91_PMC_FSTT(n)	BIT(n)
#घोषणा AT91_PMC_RTTAL		BIT(16)
#घोषणा AT91_PMC_RTCAL		BIT(17)		/* RTC Alarm Enable */
#घोषणा AT91_PMC_USBAL		BIT(18)		/* USB Resume Enable */
#घोषणा AT91_PMC_SDMMC_CD	BIT(19)		/* SDMMC Card Detect Enable */
#घोषणा AT91_PMC_LPM		BIT(20)		/* Low-घातer Mode */
#घोषणा AT91_PMC_RXLP_MCE	BIT(24)		/* Backup UART Receive Enable */
#घोषणा AT91_PMC_ACC_CE		BIT(25)		/* ACC Enable */

#घोषणा AT91_PMC_FSPR		0x74		/* Fast Startup Polarity Reg */

#घोषणा AT91_PMC_FS_INPUT_MASK  0x7ff

#घोषणा AT91_PMC_PLLICPR	0x80			/* PLL Charge Pump Current Register */

#घोषणा AT91_PMC_PROT		0xe4			/* Write Protect Mode Register [some SAM9] */
#घोषणा		AT91_PMC_WPEN		(0x1  <<  0)		/* Write Protect Enable */
#घोषणा		AT91_PMC_WPKEY		(0xffffff << 8)		/* Write Protect Key */
#घोषणा		AT91_PMC_PROTKEY	(0x504d43 << 8)		/* Activation Code */

#घोषणा AT91_PMC_WPSR		0xe8			/* Write Protect Status Register [some SAM9] */
#घोषणा		AT91_PMC_WPVS		(0x1  <<  0)		/* Write Protect Violation Status */
#घोषणा		AT91_PMC_WPVSRC		(0xffff  <<  8)		/* Write Protect Violation Source */

#घोषणा AT91_PMC_PLL_ISR0	0xEC			/* PLL Interrupt Status Register 0 [SAM9X60 only] */

#घोषणा AT91_PMC_PCER1		0x100			/* Peripheral Clock Enable Register 1 [SAMA5 only]*/
#घोषणा AT91_PMC_PCDR1		0x104			/* Peripheral Clock Enable Register 1 */
#घोषणा AT91_PMC_PCSR1		0x108			/* Peripheral Clock Enable Register 1 */

#घोषणा AT91_PMC_PCR		0x10c			/* Peripheral Control Register [some SAM9 and SAMA5] */
#घोषणा		AT91_PMC_PCR_PID_MASK		0x3f
#घोषणा		AT91_PMC_PCR_CMD		(0x1  <<  12)				/* Command (पढ़ो=0, ग_लिखो=1) */
#घोषणा		AT91_PMC_PCR_GCKDIV_MASK	GENMASK(27, 20)
#घोषणा		AT91_PMC_PCR_EN			(0x1  <<  28)				/* Enable */
#घोषणा		AT91_PMC_PCR_GCKEN		(0x1  <<  29)				/* GCK Enable */

#घोषणा AT91_PMC_AUDIO_PLL0	0x14c
#घोषणा		AT91_PMC_AUDIO_PLL_PLLEN	(1  <<  0)
#घोषणा		AT91_PMC_AUDIO_PLL_PADEN	(1  <<  1)
#घोषणा		AT91_PMC_AUDIO_PLL_PMCEN	(1  <<  2)
#घोषणा		AT91_PMC_AUDIO_PLL_RESETN	(1  <<  3)
#घोषणा		AT91_PMC_AUDIO_PLL_ND_OFFSET	8
#घोषणा		AT91_PMC_AUDIO_PLL_ND_MASK	(0x7f << AT91_PMC_AUDIO_PLL_ND_OFFSET)
#घोषणा		AT91_PMC_AUDIO_PLL_ND(n)	((n)  << AT91_PMC_AUDIO_PLL_ND_OFFSET)
#घोषणा		AT91_PMC_AUDIO_PLL_QDPMC_OFFSET	16
#घोषणा		AT91_PMC_AUDIO_PLL_QDPMC_MASK	(0x7f << AT91_PMC_AUDIO_PLL_QDPMC_OFFSET)
#घोषणा		AT91_PMC_AUDIO_PLL_QDPMC(n)	((n)  << AT91_PMC_AUDIO_PLL_QDPMC_OFFSET)

#घोषणा AT91_PMC_AUDIO_PLL1	0x150
#घोषणा		AT91_PMC_AUDIO_PLL_FRACR_MASK		0x3fffff
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_OFFSET		24
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_MASK		(0x7f << AT91_PMC_AUDIO_PLL_QDPAD_OFFSET)
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD(n)		((n)  << AT91_PMC_AUDIO_PLL_QDPAD_OFFSET)
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_DIV_OFFSET	AT91_PMC_AUDIO_PLL_QDPAD_OFFSET
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_DIV_MASK	(0x3  << AT91_PMC_AUDIO_PLL_QDPAD_DIV_OFFSET)
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_DIV(n)		((n)  << AT91_PMC_AUDIO_PLL_QDPAD_DIV_OFFSET)
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV_OFFSET	26
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV_MAX	0x1f
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV_MASK	(AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV_MAX << AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV_OFFSET)
#घोषणा		AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV(n)	((n)  << AT91_PMC_AUDIO_PLL_QDPAD_EXTDIV_OFFSET)

#पूर्ण_अगर
