<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-pxa/include/mach/pxa3xx-regs.h
 *
 * PXA3xx specअगरic रेजिस्टर definitions
 *
 * Copyright (C) 2007 Marvell International Ltd.
 */

#अगर_अघोषित __ASM_ARCH_PXA3XX_REGS_H
#घोषणा __ASM_ARCH_PXA3XX_REGS_H

#समावेश <mach/hardware.h>

/*
 * Oscillator Configuration Register (OSCC)
 */
#घोषणा OSCC           io_p2v(0x41350000)  /* Oscillator Configuration Register */

#घोषणा OSCC_PEN       (1 << 11)       /* 13MHz POUT */


/*
 * Service Power Management Unit (MPMU)
 */
#घोषणा PMCR		__REG(0x40F50000)	/* Power Manager Control Register */
#घोषणा PSR		__REG(0x40F50004)	/* Power Manager S2 Status Register */
#घोषणा PSPR		__REG(0x40F50008)	/* Power Manager Scratch Pad Register */
#घोषणा PCFR		__REG(0x40F5000C)	/* Power Manager General Configuration Register */
#घोषणा PWER		__REG(0x40F50010)	/* Power Manager Wake-up Enable Register */
#घोषणा PWSR		__REG(0x40F50014)	/* Power Manager Wake-up Status Register */
#घोषणा PECR		__REG(0x40F50018)	/* Power Manager EXT_WAKEUP[1:0] Control Register */
#घोषणा DCDCSR		__REG(0x40F50080)	/* DC-DC Controller Status Register */
#घोषणा PVCR		__REG(0x40F50100)	/* Power Manager Voltage Change Control Register */
#घोषणा PCMD(x)		__REG(0x40F50110 + ((x) << 2))

/*
 * Slave Power Management Unit
 */
#घोषणा ASCR		__REG(0x40f40000)	/* Application Subप्रणाली Power Status/Configuration */
#घोषणा ARSR		__REG(0x40f40004)	/* Application Subप्रणाली Reset Status */
#घोषणा AD3ER		__REG(0x40f40008)	/* Application Subप्रणाली Wake-Up from D3 Enable */
#घोषणा AD3SR		__REG(0x40f4000c)	/* Application Subप्रणाली Wake-Up from D3 Status */
#घोषणा AD2D0ER		__REG(0x40f40010)	/* Application Subप्रणाली Wake-Up from D2 to D0 Enable */
#घोषणा AD2D0SR		__REG(0x40f40014)	/* Application Subप्रणाली Wake-Up from D2 to D0 Status */
#घोषणा AD2D1ER		__REG(0x40f40018)	/* Application Subप्रणाली Wake-Up from D2 to D1 Enable */
#घोषणा AD2D1SR		__REG(0x40f4001c)	/* Application Subप्रणाली Wake-Up from D2 to D1 Status */
#घोषणा AD1D0ER		__REG(0x40f40020)	/* Application Subप्रणाली Wake-Up from D1 to D0 Enable */
#घोषणा AD1D0SR		__REG(0x40f40024)	/* Application Subप्रणाली Wake-Up from D1 to D0 Status */
#घोषणा AGENP		__REG(0x40f4002c)	/* Application Subप्रणाली General Purpose */
#घोषणा AD3R		__REG(0x40f40030)	/* Application Subप्रणाली D3 Configuration */
#घोषणा AD2R		__REG(0x40f40034)	/* Application Subप्रणाली D2 Configuration */
#घोषणा AD1R		__REG(0x40f40038)	/* Application Subप्रणाली D1 Configuration */

/*
 * Application Subप्रणाली Configuration bits.
 */
#घोषणा ASCR_RDH		(1 << 31)
#घोषणा ASCR_D1S		(1 << 2)
#घोषणा ASCR_D2S		(1 << 1)
#घोषणा ASCR_D3S		(1 << 0)

/*
 * Application Reset Status bits.
 */
#घोषणा ARSR_GPR		(1 << 3)
#घोषणा ARSR_LPMR		(1 << 2)
#घोषणा ARSR_WDT		(1 << 1)
#घोषणा ARSR_HWR		(1 << 0)

/*
 * Application Subप्रणाली Wake-Up bits.
 */
#घोषणा ADXER_WRTC		(1 << 31)	/* RTC */
#घोषणा ADXER_WOST		(1 << 30)	/* OS Timer */
#घोषणा ADXER_WTSI		(1 << 29)	/* Touchscreen */
#घोषणा ADXER_WUSBH		(1 << 28)	/* USB host */
#घोषणा ADXER_WUSB2		(1 << 26)	/* USB client 2.0 */
#घोषणा ADXER_WMSL0		(1 << 24)	/* MSL port 0*/
#घोषणा ADXER_WDMUX3		(1 << 23)	/* USB EDMUX3 */
#घोषणा ADXER_WDMUX2		(1 << 22)	/* USB EDMUX2 */
#घोषणा ADXER_WKP		(1 << 21)	/* Keypad */
#घोषणा ADXER_WUSIM1		(1 << 20)	/* USIM Port 1 */
#घोषणा ADXER_WUSIM0		(1 << 19)	/* USIM Port 0 */
#घोषणा ADXER_WOTG		(1 << 16)	/* USBOTG input */
#घोषणा ADXER_MFP_WFLASH	(1 << 15)	/* MFP: Data flash busy */
#घोषणा ADXER_MFP_GEN12		(1 << 14)	/* MFP: MMC3/GPIO/OST inमाला_दो */
#घोषणा ADXER_MFP_WMMC2		(1 << 13)	/* MFP: MMC2 */
#घोषणा ADXER_MFP_WMMC1		(1 << 12)	/* MFP: MMC1 */
#घोषणा ADXER_MFP_WI2C		(1 << 11)	/* MFP: I2C */
#घोषणा ADXER_MFP_WSSP4		(1 << 10)	/* MFP: SSP4 */
#घोषणा ADXER_MFP_WSSP3		(1 << 9)	/* MFP: SSP3 */
#घोषणा ADXER_MFP_WMAXTRIX	(1 << 8)	/* MFP: matrix keypad */
#घोषणा ADXER_MFP_WUART3	(1 << 7)	/* MFP: UART3 */
#घोषणा ADXER_MFP_WUART2	(1 << 6)	/* MFP: UART2 */
#घोषणा ADXER_MFP_WUART1	(1 << 5)	/* MFP: UART1 */
#घोषणा ADXER_MFP_WSSP2		(1 << 4)	/* MFP: SSP2 */
#घोषणा ADXER_MFP_WSSP1		(1 << 3)	/* MFP: SSP1 */
#घोषणा ADXER_MFP_WAC97		(1 << 2)	/* MFP: AC97 */
#घोषणा ADXER_WEXTWAKE1		(1 << 1)	/* External Wake 1 */
#घोषणा ADXER_WEXTWAKE0		(1 << 0)	/* External Wake 0 */

/*
 * AD3R/AD2R/AD1R bits.  R2-R5 are only defined क्रम PXA320.
 */
#घोषणा ADXR_L2			(1 << 8)
#घोषणा ADXR_R5			(1 << 5)
#घोषणा ADXR_R4			(1 << 4)
#घोषणा ADXR_R3			(1 << 3)
#घोषणा ADXR_R2			(1 << 2)
#घोषणा ADXR_R1			(1 << 1)
#घोषणा ADXR_R0			(1 << 0)

/*
 * Values क्रम PWRMODE CP15 रेजिस्टर
 */
#घोषणा PXA3xx_PM_S3D4C4	0x07	/* aka deep sleep */
#घोषणा PXA3xx_PM_S2D3C4	0x06	/* aka sleep */
#घोषणा PXA3xx_PM_S0D2C2	0x03	/* aka standby */
#घोषणा PXA3xx_PM_S0D1C2	0x02	/* aka LCD refresh */
#घोषणा PXA3xx_PM_S0D0C1	0x01

/*
 * Application Subप्रणाली Clock
 */
#घोषणा ACCR		__REG(0x41340000)	/* Application Subप्रणाली Clock Configuration Register */
#घोषणा ACSR		__REG(0x41340004)	/* Application Subप्रणाली Clock Status Register */
#घोषणा AICSR		__REG(0x41340008)	/* Application Subप्रणाली Interrupt Control/Status Register */
#घोषणा CKENA		__REG(0x4134000C)	/* A Clock Enable Register */
#घोषणा CKENB		__REG(0x41340010)	/* B Clock Enable Register */
#घोषणा CKENC		__REG(0x41340024)	/* C Clock Enable Register */
#घोषणा AC97_DIV	__REG(0x41340014)	/* AC97 घड़ी भागisor value रेजिस्टर */

#घोषणा ACCR_XPDIS		(1 << 31)	/* Core PLL Output Disable */
#घोषणा ACCR_SPDIS		(1 << 30)	/* System PLL Output Disable */
#घोषणा ACCR_D0CS		(1 << 26)	/* D0 Mode Clock Select */
#घोषणा ACCR_PCCE		(1 << 11)	/* Power Mode Change Clock Enable */
#घोषणा ACCR_DDR_D0CS		(1 << 7)	/* DDR SDRAM घड़ी frequency in D0CS (PXA31x only) */

#घोषणा ACCR_SMCFS_MASK		(0x7 << 23)	/* Static Memory Controller Frequency Select */
#घोषणा ACCR_SFLFS_MASK		(0x3 << 18)	/* Frequency Select क्रम Internal Memory Controller */
#घोषणा ACCR_XSPCLK_MASK	(0x3 << 16)	/* Core Frequency during Frequency Change */
#घोषणा ACCR_HSS_MASK		(0x3 << 14)	/* System Bus-Clock Frequency Select */
#घोषणा ACCR_DMCFS_MASK		(0x3 << 12)	/* Dynamic Memory Controller Clock Frequency Select */
#घोषणा ACCR_XN_MASK		(0x7 << 8)	/* Core PLL Turbo-Mode-to-Run-Mode Ratio */
#घोषणा ACCR_XL_MASK		(0x1f)		/* Core PLL Run-Mode-to-Oscillator Ratio */

#घोषणा ACCR_SMCFS(x)		(((x) & 0x7) << 23)
#घोषणा ACCR_SFLFS(x)		(((x) & 0x3) << 18)
#घोषणा ACCR_XSPCLK(x)		(((x) & 0x3) << 16)
#घोषणा ACCR_HSS(x)		(((x) & 0x3) << 14)
#घोषणा ACCR_DMCFS(x)		(((x) & 0x3) << 12)
#घोषणा ACCR_XN(x)		(((x) & 0x7) << 8)
#घोषणा ACCR_XL(x)		((x) & 0x1f)

/*
 * Clock Enable Bit
 */
#घोषणा CKEN_LCD	1	/* < LCD Clock Enable */
#घोषणा CKEN_USBH	2	/* < USB host घड़ी enable */
#घोषणा CKEN_CAMERA	3	/* < Camera पूर्णांकerface घड़ी enable */
#घोषणा CKEN_न_अंकD	4	/* < न_अंकD Flash Controller Clock Enable */
#घोषणा CKEN_USB2	6	/* < USB 2.0 client घड़ी enable. */
#घोषणा CKEN_DMC	8	/* < Dynamic Memory Controller घड़ी enable */
#घोषणा CKEN_SMC	9	/* < Static Memory Controller घड़ी enable */
#घोषणा CKEN_ISC	10	/* < Internal SRAM Controller घड़ी enable */
#घोषणा CKEN_BOOT	11	/* < Boot rom घड़ी enable */
#घोषणा CKEN_MMC1	12	/* < MMC1 Clock enable */
#घोषणा CKEN_MMC2	13	/* < MMC2 घड़ी enable */
#घोषणा CKEN_KEYPAD	14	/* < Keypand Controller Clock Enable */
#घोषणा CKEN_CIR	15	/* < Consumer IR Clock Enable */
#घोषणा CKEN_USIM0	17	/* < USIM[0] Clock Enable */
#घोषणा CKEN_USIM1	18	/* < USIM[1] Clock Enable */
#घोषणा CKEN_TPM	19	/* < TPM घड़ी enable */
#घोषणा CKEN_UDC	20	/* < UDC घड़ी enable */
#घोषणा CKEN_BTUART	21	/* < BTUART घड़ी enable */
#घोषणा CKEN_FFUART	22	/* < FFUART घड़ी enable */
#घोषणा CKEN_STUART	23	/* < STUART घड़ी enable */
#घोषणा CKEN_AC97	24	/* < AC97 घड़ी enable */
#घोषणा CKEN_TOUCH	25	/* < Touch screen Interface Clock Enable */
#घोषणा CKEN_SSP1	26	/* < SSP1 घड़ी enable */
#घोषणा CKEN_SSP2	27	/* < SSP2 घड़ी enable */
#घोषणा CKEN_SSP3	28	/* < SSP3 घड़ी enable */
#घोषणा CKEN_SSP4	29	/* < SSP4 घड़ी enable */
#घोषणा CKEN_MSL0	30	/* < MSL0 घड़ी enable */
#घोषणा CKEN_PWM0	32	/* < PWM[0] घड़ी enable */
#घोषणा CKEN_PWM1	33	/* < PWM[1] घड़ी enable */
#घोषणा CKEN_I2C	36	/* < I2C घड़ी enable */
#घोषणा CKEN_INTC	38	/* < Interrupt controller घड़ी enable */
#घोषणा CKEN_GPIO	39	/* < GPIO घड़ी enable */
#घोषणा CKEN_1WIRE	40	/* < 1-wire घड़ी enable */
#घोषणा CKEN_HSIO2	41	/* < HSIO2 घड़ी enable */
#घोषणा CKEN_MINI_IM	48	/* < Mini-IM */
#घोषणा CKEN_MINI_LCD	49	/* < Mini LCD */

#घोषणा CKEN_MMC3	5	/* < MMC3 Clock Enable */
#घोषणा CKEN_MVED	43	/* < MVED घड़ी enable */

/* Note: GCU घड़ी enable bit dअगरfers on PXA300/PXA310 and PXA320 */
#घोषणा CKEN_PXA300_GCU		42	/* Graphics controller घड़ी enable */
#घोषणा CKEN_PXA320_GCU		7	/* Graphics controller घड़ी enable */

#पूर्ण_अगर /* __ASM_ARCH_PXA3XX_REGS_H */
