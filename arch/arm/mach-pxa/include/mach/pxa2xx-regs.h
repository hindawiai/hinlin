<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-pxa/include/mach/pxa2xx-regs.h
 *
 *  Taken from pxa-regs.h by Russell King
 *
 *  Author:	Nicolas Pitre
 *  Copyright:	MontaVista Software Inc.
 */

#अगर_अघोषित __PXA2XX_REGS_H
#घोषणा __PXA2XX_REGS_H

#समावेश <mach/hardware.h>

/*
 * Power Manager
 */

#घोषणा PMCR		__REG(0x40F00000)  /* Power Manager Control Register */
#घोषणा PSSR		__REG(0x40F00004)  /* Power Manager Sleep Status Register */
#घोषणा PSPR		__REG(0x40F00008)  /* Power Manager Scratch Pad Register */
#घोषणा PWER		__REG(0x40F0000C)  /* Power Manager Wake-up Enable Register */
#घोषणा PRER		__REG(0x40F00010)  /* Power Manager GPIO Rising-Edge Detect Enable Register */
#घोषणा PFER		__REG(0x40F00014)  /* Power Manager GPIO Falling-Edge Detect Enable Register */
#घोषणा PEDR		__REG(0x40F00018)  /* Power Manager GPIO Edge Detect Status Register */
#घोषणा PCFR		__REG(0x40F0001C)  /* Power Manager General Configuration Register */
#घोषणा PGSR0		__REG(0x40F00020)  /* Power Manager GPIO Sleep State Register क्रम GP[31-0] */
#घोषणा PGSR1		__REG(0x40F00024)  /* Power Manager GPIO Sleep State Register क्रम GP[63-32] */
#घोषणा PGSR2		__REG(0x40F00028)  /* Power Manager GPIO Sleep State Register क्रम GP[84-64] */
#घोषणा PGSR3		__REG(0x40F0002C)  /* Power Manager GPIO Sleep State Register क्रम GP[118-96] */
#घोषणा RCSR		__REG(0x40F00030)  /* Reset Controller Status Register */

#घोषणा PSLR		__REG(0x40F00034)	/* Power Manager Sleep Config Register */
#घोषणा PSTR		__REG(0x40F00038)	/* Power Manager Standby Config Register */
#घोषणा PSNR		__REG(0x40F0003C)	/* Power Manager Sense Config Register */
#घोषणा PVCR		__REG(0x40F00040)	/* Power Manager VoltageControl Register */
#घोषणा PKWR		__REG(0x40F00050)	/* Power Manager KB Wake-up Enable Reg */
#घोषणा PKSR		__REG(0x40F00054)	/* Power Manager KB Level-Detect Register */
#घोषणा PCMD(x)	__REG2(0x40F00080, (x)<<2)
#घोषणा PCMD0	__REG(0x40F00080 + 0 * 4)
#घोषणा PCMD1	__REG(0x40F00080 + 1 * 4)
#घोषणा PCMD2	__REG(0x40F00080 + 2 * 4)
#घोषणा PCMD3	__REG(0x40F00080 + 3 * 4)
#घोषणा PCMD4	__REG(0x40F00080 + 4 * 4)
#घोषणा PCMD5	__REG(0x40F00080 + 5 * 4)
#घोषणा PCMD6	__REG(0x40F00080 + 6 * 4)
#घोषणा PCMD7	__REG(0x40F00080 + 7 * 4)
#घोषणा PCMD8	__REG(0x40F00080 + 8 * 4)
#घोषणा PCMD9	__REG(0x40F00080 + 9 * 4)
#घोषणा PCMD10	__REG(0x40F00080 + 10 * 4)
#घोषणा PCMD11	__REG(0x40F00080 + 11 * 4)
#घोषणा PCMD12	__REG(0x40F00080 + 12 * 4)
#घोषणा PCMD13	__REG(0x40F00080 + 13 * 4)
#घोषणा PCMD14	__REG(0x40F00080 + 14 * 4)
#घोषणा PCMD15	__REG(0x40F00080 + 15 * 4)
#घोषणा PCMD16	__REG(0x40F00080 + 16 * 4)
#घोषणा PCMD17	__REG(0x40F00080 + 17 * 4)
#घोषणा PCMD18	__REG(0x40F00080 + 18 * 4)
#घोषणा PCMD19	__REG(0x40F00080 + 19 * 4)
#घोषणा PCMD20	__REG(0x40F00080 + 20 * 4)
#घोषणा PCMD21	__REG(0x40F00080 + 21 * 4)
#घोषणा PCMD22	__REG(0x40F00080 + 22 * 4)
#घोषणा PCMD23	__REG(0x40F00080 + 23 * 4)
#घोषणा PCMD24	__REG(0x40F00080 + 24 * 4)
#घोषणा PCMD25	__REG(0x40F00080 + 25 * 4)
#घोषणा PCMD26	__REG(0x40F00080 + 26 * 4)
#घोषणा PCMD27	__REG(0x40F00080 + 27 * 4)
#घोषणा PCMD28	__REG(0x40F00080 + 28 * 4)
#घोषणा PCMD29	__REG(0x40F00080 + 29 * 4)
#घोषणा PCMD30	__REG(0x40F00080 + 30 * 4)
#घोषणा PCMD31	__REG(0x40F00080 + 31 * 4)

#घोषणा PCMD_MBC	(1<<12)
#घोषणा PCMD_DCE	(1<<11)
#घोषणा PCMD_LC	(1<<10)
/* FIXME:  PCMD_SQC need be checked.   */
#घोषणा PCMD_SQC	(3<<8)	/* currently only bit 8 is changeable,
				   bit 9 should be 0 all day. */
#घोषणा PVCR_VCSA	(0x1<<14)
#घोषणा PVCR_CommandDelay (0xf80)
#घोषणा PCFR_PI2C_EN	(0x1 << 6)

#घोषणा PSSR_OTGPH	(1 << 6)	/* OTG Peripheral control Hold */
#घोषणा PSSR_RDH	(1 << 5)	/* Read Disable Hold */
#घोषणा PSSR_PH		(1 << 4)	/* Peripheral Control Hold */
#घोषणा PSSR_STS	(1 << 3)	/* Standby Mode Status */
#घोषणा PSSR_VFS	(1 << 2)	/* VDD Fault Status */
#घोषणा PSSR_BFS	(1 << 1)	/* Battery Fault Status */
#घोषणा PSSR_SSS	(1 << 0)	/* Software Sleep Status */

#घोषणा PSLR_SL_ROD	(1 << 20)	/* Sleep-Mode/Depp-Sleep Mode nRESET_OUT Disable */

#घोषणा PCFR_RO		(1 << 15)	/* RDH Override */
#घोषणा PCFR_PO		(1 << 14)	/* PH Override */
#घोषणा PCFR_GPROD	(1 << 12)	/* GPIO nRESET_OUT Disable */
#घोषणा PCFR_L1_EN	(1 << 11)	/* Sleep Mode L1 converter Enable */
#घोषणा PCFR_FVC	(1 << 10)	/* Frequency/Voltage Change */
#घोषणा PCFR_DC_EN	(1 << 7)	/* Sleep/deep-sleep DC-DC Converter Enable */
#घोषणा PCFR_PI2CEN	(1 << 6)	/* Enable PI2C controller */
#घोषणा PCFR_GPR_EN	(1 << 4)	/* nRESET_GPIO Pin Enable */
#घोषणा PCFR_DS		(1 << 3)	/* Deep Sleep Mode */
#घोषणा PCFR_FS		(1 << 2)	/* Float Static Chip Selects */
#घोषणा PCFR_FP		(1 << 1)	/* Float PCMCIA controls */
#घोषणा PCFR_OPDE	(1 << 0)	/* 3.6864 MHz oscillator घातer-करोwn enable */

#घोषणा RCSR_GPR	(1 << 3)	/* GPIO Reset */
#घोषणा RCSR_SMR	(1 << 2)	/* Sleep Mode */
#घोषणा RCSR_WDR	(1 << 1)	/* Watchकरोg Reset */
#घोषणा RCSR_HWR	(1 << 0)	/* Hardware Reset */

#घोषणा PWER_GPIO(Nb)	(1 << Nb)	/* GPIO [0..15] wake-up enable     */
#घोषणा PWER_GPIO0	PWER_GPIO (0)	/* GPIO  [0] wake-up enable        */
#घोषणा PWER_GPIO1	PWER_GPIO (1)	/* GPIO  [1] wake-up enable        */
#घोषणा PWER_GPIO2	PWER_GPIO (2)	/* GPIO  [2] wake-up enable        */
#घोषणा PWER_GPIO3	PWER_GPIO (3)	/* GPIO  [3] wake-up enable        */
#घोषणा PWER_GPIO4	PWER_GPIO (4)	/* GPIO  [4] wake-up enable        */
#घोषणा PWER_GPIO5	PWER_GPIO (5)	/* GPIO  [5] wake-up enable        */
#घोषणा PWER_GPIO6	PWER_GPIO (6)	/* GPIO  [6] wake-up enable        */
#घोषणा PWER_GPIO7	PWER_GPIO (7)	/* GPIO  [7] wake-up enable        */
#घोषणा PWER_GPIO8	PWER_GPIO (8)	/* GPIO  [8] wake-up enable        */
#घोषणा PWER_GPIO9	PWER_GPIO (9)	/* GPIO  [9] wake-up enable        */
#घोषणा PWER_GPIO10	PWER_GPIO (10)	/* GPIO [10] wake-up enable        */
#घोषणा PWER_GPIO11	PWER_GPIO (11)	/* GPIO [11] wake-up enable        */
#घोषणा PWER_GPIO12	PWER_GPIO (12)	/* GPIO [12] wake-up enable        */
#घोषणा PWER_GPIO13	PWER_GPIO (13)	/* GPIO [13] wake-up enable        */
#घोषणा PWER_GPIO14	PWER_GPIO (14)	/* GPIO [14] wake-up enable        */
#घोषणा PWER_GPIO15	PWER_GPIO (15)	/* GPIO [15] wake-up enable        */
#घोषणा PWER_RTC	0x80000000	/* RTC alarm wake-up enable        */

/*
 * PXA2xx specअगरic Core घड़ी definitions
 */
#घोषणा CCCR		io_p2v(0x41300000)  /* Core Clock Configuration Register */
#घोषणा CCSR		io_p2v(0x4130000C)  /* Core Clock Status Register */
#घोषणा CKEN		io_p2v(0x41300004)  /* Clock Enable Register */
#घोषणा OSCC		io_p2v(0x41300008)  /* Oscillator Configuration Register */

#घोषणा CCCR_N_MASK	0x0380	/* Run Mode Frequency to Turbo Mode Frequency Multiplier */
#घोषणा CCCR_M_MASK	0x0060	/* Memory Frequency to Run Mode Frequency Multiplier */
#घोषणा CCCR_L_MASK	0x001f	/* Crystal Frequency to Memory Frequency Multiplier */

#घोषणा CCCR_CPDIS_BIT	(31)
#घोषणा CCCR_PPDIS_BIT	(30)
#घोषणा CCCR_LCD_26_BIT	(27)
#घोषणा CCCR_A_BIT	(25)

#घोषणा CCSR_N2_MASK	CCCR_N_MASK
#घोषणा CCSR_M_MASK	CCCR_M_MASK
#घोषणा CCSR_L_MASK	CCCR_L_MASK
#घोषणा CCSR_N2_SHIFT	7

#घोषणा CKEN_AC97CONF   (31)    /* AC97 Controller Configuration */
#घोषणा CKEN_CAMERA	(24)	/* Camera Interface Clock Enable */
#घोषणा CKEN_SSP1	(23)	/* SSP1 Unit Clock Enable */
#घोषणा CKEN_MEMC	(22)	/* Memory Controller Clock Enable */
#घोषणा CKEN_MEMSTK	(21)	/* Memory Stick Host Controller */
#घोषणा CKEN_IM		(20)	/* Internal Memory Clock Enable */
#घोषणा CKEN_KEYPAD	(19)	/* Keypad Interface Clock Enable */
#घोषणा CKEN_USIM	(18)	/* USIM Unit Clock Enable */
#घोषणा CKEN_MSL	(17)	/* MSL Unit Clock Enable */
#घोषणा CKEN_LCD	(16)	/* LCD Unit Clock Enable */
#घोषणा CKEN_PWRI2C	(15)	/* PWR I2C Unit Clock Enable */
#घोषणा CKEN_I2C	(14)	/* I2C Unit Clock Enable */
#घोषणा CKEN_FICP	(13)	/* FICP Unit Clock Enable */
#घोषणा CKEN_MMC	(12)	/* MMC Unit Clock Enable */
#घोषणा CKEN_USB	(11)	/* USB Unit Clock Enable */
#घोषणा CKEN_ASSP	(10)	/* ASSP (SSP3) Clock Enable */
#घोषणा CKEN_USBHOST	(10)	/* USB Host Unit Clock Enable */
#घोषणा CKEN_OSTIMER	(9)	/* OS Timer Unit Clock Enable */
#घोषणा CKEN_NSSP	(9)	/* NSSP (SSP2) Clock Enable */
#घोषणा CKEN_I2S	(8)	/* I2S Unit Clock Enable */
#घोषणा CKEN_BTUART	(7)	/* BTUART Unit Clock Enable */
#घोषणा CKEN_FFUART	(6)	/* FFUART Unit Clock Enable */
#घोषणा CKEN_STUART	(5)	/* STUART Unit Clock Enable */
#घोषणा CKEN_HWUART	(4)	/* HWUART Unit Clock Enable */
#घोषणा CKEN_SSP3	(4)	/* SSP3 Unit Clock Enable */
#घोषणा CKEN_SSP	(3)	/* SSP Unit Clock Enable */
#घोषणा CKEN_SSP2	(3)	/* SSP2 Unit Clock Enable */
#घोषणा CKEN_AC97	(2)	/* AC97 Unit Clock Enable */
#घोषणा CKEN_PWM1	(1)	/* PWM1 Clock Enable */
#घोषणा CKEN_PWM0	(0)	/* PWM0 Clock Enable */

#घोषणा OSCC_OON	(1 << 1)	/* 32.768kHz OON (ग_लिखो-once only bit) */
#घोषणा OSCC_OOK	(1 << 0)	/* 32.768kHz OOK (पढ़ो-only bit) */

/* PWRMODE रेजिस्टर M field values */

#घोषणा PWRMODE_IDLE		0x1
#घोषणा PWRMODE_STANDBY		0x2
#घोषणा PWRMODE_SLEEP		0x3
#घोषणा PWRMODE_DEEPSLEEP	0x7

#पूर्ण_अगर
