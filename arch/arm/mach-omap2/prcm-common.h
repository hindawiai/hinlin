<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __ARCH_ASM_MACH_OMAP2_PRCM_COMMON_H
#घोषणा __ARCH_ASM_MACH_OMAP2_PRCM_COMMON_H

/*
 * OMAP2/3 PRCM base and module definitions
 *
 * Copyright (C) 2007-2009, 2011 Texas Instruments, Inc.
 * Copyright (C) 2007-2009 Nokia Corporation
 *
 * Written by Paul Walmsley
 */

/* Module offsets from both CM_BASE & PRM_BASE */

/*
 * Offsets that are the same on 24xx and 34xx
 *
 * Technically, in terms of the TRM, OCP_MOD is 34xx only; PLL_MOD is
 * CCR_MOD on 3430; and GFX_MOD only exists < 3430ES2.
 */
#घोषणा OCP_MOD						0x000
#घोषणा MPU_MOD						0x100
#घोषणा CORE_MOD					0x200
#घोषणा GFX_MOD						0x300
#घोषणा WKUP_MOD					0x400
#घोषणा PLL_MOD						0x500


/* Chip-specअगरic module offsets */
#घोषणा OMAP24XX_GR_MOD					OCP_MOD
#घोषणा OMAP24XX_DSP_MOD				0x800

#घोषणा OMAP2430_MDM_MOD				0xc00

/* IVA2 module is < base on 3430 */
#घोषणा OMAP3430_IVA2_MOD				-0x800
#घोषणा OMAP3430ES2_SGX_MOD				GFX_MOD
#घोषणा OMAP3430_CCR_MOD				PLL_MOD
#घोषणा OMAP3430_DSS_MOD				0x600
#घोषणा OMAP3430_CAM_MOD				0x700
#घोषणा OMAP3430_PER_MOD				0x800
#घोषणा OMAP3430_EMU_MOD				0x900
#घोषणा OMAP3430_GR_MOD					0xa00
#घोषणा OMAP3430_NEON_MOD				0xb00
#घोषणा OMAP3430ES2_USBHOST_MOD				0xc00

/*
 * TI81XX PRM module offsets
 */
#घोषणा TI814X_PRM_DSP_MOD				0x0a00
#घोषणा TI814X_PRM_HDVICP_MOD				0x0c00
#घोषणा TI814X_PRM_ISP_MOD				0x0d00
#घोषणा TI814X_PRM_HDVPSS_MOD				0x0e00
#घोषणा TI814X_PRM_GFX_MOD				0x0f00

#घोषणा TI81XX_PRM_DEVICE_MOD			0x0000
#घोषणा TI816X_PRM_ACTIVE_MOD			0x0a00
#घोषणा TI81XX_PRM_DEFAULT_MOD			0x0b00
#घोषणा TI816X_PRM_IVAHD0_MOD			0x0c00
#घोषणा TI816X_PRM_IVAHD1_MOD			0x0d00
#घोषणा TI816X_PRM_IVAHD2_MOD			0x0e00
#घोषणा TI816X_PRM_SGX_MOD				0x0f00
#घोषणा TI81XX_PRM_ALWON_MOD			0x1800

/* 24XX रेजिस्टर bits shared between CM & PRM रेजिस्टरs */

/* CM_FCLKEN1_CORE, CM_ICLKEN1_CORE, PM_WKEN1_CORE shared bits */
#घोषणा OMAP2420_EN_MMC_SHIFT				26
#घोषणा OMAP2420_EN_MMC_MASK				(1 << 26)
#घोषणा OMAP24XX_EN_UART2_SHIFT				22
#घोषणा OMAP24XX_EN_UART2_MASK				(1 << 22)
#घोषणा OMAP24XX_EN_UART1_SHIFT				21
#घोषणा OMAP24XX_EN_UART1_MASK				(1 << 21)
#घोषणा OMAP24XX_EN_MCSPI2_SHIFT			18
#घोषणा OMAP24XX_EN_MCSPI2_MASK				(1 << 18)
#घोषणा OMAP24XX_EN_MCSPI1_SHIFT			17
#घोषणा OMAP24XX_EN_MCSPI1_MASK				(1 << 17)
#घोषणा OMAP24XX_EN_MCBSP2_SHIFT			16
#घोषणा OMAP24XX_EN_MCBSP2_MASK				(1 << 16)
#घोषणा OMAP24XX_EN_MCBSP1_SHIFT			15
#घोषणा OMAP24XX_EN_MCBSP1_MASK				(1 << 15)
#घोषणा OMAP24XX_EN_GPT12_SHIFT				14
#घोषणा OMAP24XX_EN_GPT12_MASK				(1 << 14)
#घोषणा OMAP24XX_EN_GPT11_SHIFT				13
#घोषणा OMAP24XX_EN_GPT11_MASK				(1 << 13)
#घोषणा OMAP24XX_EN_GPT10_SHIFT				12
#घोषणा OMAP24XX_EN_GPT10_MASK				(1 << 12)
#घोषणा OMAP24XX_EN_GPT9_SHIFT				11
#घोषणा OMAP24XX_EN_GPT9_MASK				(1 << 11)
#घोषणा OMAP24XX_EN_GPT8_SHIFT				10
#घोषणा OMAP24XX_EN_GPT8_MASK				(1 << 10)
#घोषणा OMAP24XX_EN_GPT7_SHIFT				9
#घोषणा OMAP24XX_EN_GPT7_MASK				(1 << 9)
#घोषणा OMAP24XX_EN_GPT6_SHIFT				8
#घोषणा OMAP24XX_EN_GPT6_MASK				(1 << 8)
#घोषणा OMAP24XX_EN_GPT5_SHIFT				7
#घोषणा OMAP24XX_EN_GPT5_MASK				(1 << 7)
#घोषणा OMAP24XX_EN_GPT4_SHIFT				6
#घोषणा OMAP24XX_EN_GPT4_MASK				(1 << 6)
#घोषणा OMAP24XX_EN_GPT3_SHIFT				5
#घोषणा OMAP24XX_EN_GPT3_MASK				(1 << 5)
#घोषणा OMAP24XX_EN_GPT2_SHIFT				4
#घोषणा OMAP24XX_EN_GPT2_MASK				(1 << 4)
#घोषणा OMAP2420_EN_VLYNQ_SHIFT				3
#घोषणा OMAP2420_EN_VLYNQ_MASK				(1 << 3)

/* CM_FCLKEN2_CORE, CM_ICLKEN2_CORE, PM_WKEN2_CORE shared bits */
#घोषणा OMAP2430_EN_GPIO5_SHIFT				10
#घोषणा OMAP2430_EN_GPIO5_MASK				(1 << 10)
#घोषणा OMAP2430_EN_MCSPI3_SHIFT			9
#घोषणा OMAP2430_EN_MCSPI3_MASK				(1 << 9)
#घोषणा OMAP2430_EN_MMCHS2_SHIFT			8
#घोषणा OMAP2430_EN_MMCHS2_MASK				(1 << 8)
#घोषणा OMAP2430_EN_MMCHS1_SHIFT			7
#घोषणा OMAP2430_EN_MMCHS1_MASK				(1 << 7)
#घोषणा OMAP24XX_EN_UART3_SHIFT				2
#घोषणा OMAP24XX_EN_UART3_MASK				(1 << 2)
#घोषणा OMAP24XX_EN_USB_SHIFT				0
#घोषणा OMAP24XX_EN_USB_MASK				(1 << 0)

/* CM_ICLKEN2_CORE, PM_WKEN2_CORE shared bits */
#घोषणा OMAP2430_EN_MDM_INTC_SHIFT			11
#घोषणा OMAP2430_EN_MDM_INTC_MASK			(1 << 11)
#घोषणा OMAP2430_EN_USBHS_SHIFT				6
#घोषणा OMAP2430_EN_USBHS_MASK				(1 << 6)
#घोषणा OMAP24XX_EN_GPMC_SHIFT				1
#घोषणा OMAP24XX_EN_GPMC_MASK				(1 << 1)

/* CM_IDLEST1_CORE, PM_WKST1_CORE shared bits */
#घोषणा OMAP2420_ST_MMC_SHIFT				26
#घोषणा OMAP2420_ST_MMC_MASK				(1 << 26)
#घोषणा OMAP24XX_ST_UART2_SHIFT				22
#घोषणा OMAP24XX_ST_UART2_MASK				(1 << 22)
#घोषणा OMAP24XX_ST_UART1_SHIFT				21
#घोषणा OMAP24XX_ST_UART1_MASK				(1 << 21)
#घोषणा OMAP24XX_ST_MCSPI2_SHIFT			18
#घोषणा OMAP24XX_ST_MCSPI2_MASK				(1 << 18)
#घोषणा OMAP24XX_ST_MCSPI1_SHIFT			17
#घोषणा OMAP24XX_ST_MCSPI1_MASK				(1 << 17)
#घोषणा OMAP24XX_ST_MCBSP2_SHIFT			16
#घोषणा OMAP24XX_ST_MCBSP2_MASK				(1 << 16)
#घोषणा OMAP24XX_ST_MCBSP1_SHIFT			15
#घोषणा OMAP24XX_ST_MCBSP1_MASK				(1 << 15)
#घोषणा OMAP24XX_ST_GPT12_SHIFT				14
#घोषणा OMAP24XX_ST_GPT12_MASK				(1 << 14)
#घोषणा OMAP24XX_ST_GPT11_SHIFT				13
#घोषणा OMAP24XX_ST_GPT11_MASK				(1 << 13)
#घोषणा OMAP24XX_ST_GPT10_SHIFT				12
#घोषणा OMAP24XX_ST_GPT10_MASK				(1 << 12)
#घोषणा OMAP24XX_ST_GPT9_SHIFT				11
#घोषणा OMAP24XX_ST_GPT9_MASK				(1 << 11)
#घोषणा OMAP24XX_ST_GPT8_SHIFT				10
#घोषणा OMAP24XX_ST_GPT8_MASK				(1 << 10)
#घोषणा OMAP24XX_ST_GPT7_SHIFT				9
#घोषणा OMAP24XX_ST_GPT7_MASK				(1 << 9)
#घोषणा OMAP24XX_ST_GPT6_SHIFT				8
#घोषणा OMAP24XX_ST_GPT6_MASK				(1 << 8)
#घोषणा OMAP24XX_ST_GPT5_SHIFT				7
#घोषणा OMAP24XX_ST_GPT5_MASK				(1 << 7)
#घोषणा OMAP24XX_ST_GPT4_SHIFT				6
#घोषणा OMAP24XX_ST_GPT4_MASK				(1 << 6)
#घोषणा OMAP24XX_ST_GPT3_SHIFT				5
#घोषणा OMAP24XX_ST_GPT3_MASK				(1 << 5)
#घोषणा OMAP24XX_ST_GPT2_SHIFT				4
#घोषणा OMAP24XX_ST_GPT2_MASK				(1 << 4)
#घोषणा OMAP2420_ST_VLYNQ_SHIFT				3
#घोषणा OMAP2420_ST_VLYNQ_MASK				(1 << 3)

/* CM_IDLEST2_CORE, PM_WKST2_CORE shared bits */
#घोषणा OMAP2430_ST_MDM_INTC_SHIFT			11
#घोषणा OMAP2430_ST_MDM_INTC_MASK			(1 << 11)
#घोषणा OMAP2430_ST_GPIO5_SHIFT				10
#घोषणा OMAP2430_ST_GPIO5_MASK				(1 << 10)
#घोषणा OMAP2430_ST_MCSPI3_SHIFT			9
#घोषणा OMAP2430_ST_MCSPI3_MASK				(1 << 9)
#घोषणा OMAP2430_ST_MMCHS2_SHIFT			8
#घोषणा OMAP2430_ST_MMCHS2_MASK				(1 << 8)
#घोषणा OMAP2430_ST_MMCHS1_SHIFT			7
#घोषणा OMAP2430_ST_MMCHS1_MASK				(1 << 7)
#घोषणा OMAP2430_ST_USBHS_SHIFT				6
#घोषणा OMAP2430_ST_USBHS_MASK				(1 << 6)
#घोषणा OMAP24XX_ST_UART3_SHIFT				2
#घोषणा OMAP24XX_ST_UART3_MASK				(1 << 2)
#घोषणा OMAP24XX_ST_USB_SHIFT				0
#घोषणा OMAP24XX_ST_USB_MASK				(1 << 0)

/* CM_FCLKEN_WKUP, CM_ICLKEN_WKUP, PM_WKEN_WKUP shared bits */
#घोषणा OMAP24XX_EN_GPIOS_SHIFT				2
#घोषणा OMAP24XX_EN_GPIOS_MASK				(1 << 2)
#घोषणा OMAP24XX_EN_GPT1_SHIFT				0
#घोषणा OMAP24XX_EN_GPT1_MASK				(1 << 0)

/* PM_WKST_WKUP, CM_IDLEST_WKUP shared bits */
#घोषणा OMAP24XX_ST_GPIOS_SHIFT				2
#घोषणा OMAP24XX_ST_GPIOS_MASK				(1 << 2)
#घोषणा OMAP24XX_ST_32KSYNC_SHIFT			1
#घोषणा OMAP24XX_ST_32KSYNC_MASK			(1 << 1)
#घोषणा OMAP24XX_ST_GPT1_SHIFT				0
#घोषणा OMAP24XX_ST_GPT1_MASK				(1 << 0)

/* CM_IDLEST_MDM and PM_WKST_MDM shared bits */
#घोषणा OMAP2430_ST_MDM_SHIFT				0
#घोषणा OMAP2430_ST_MDM_MASK				(1 << 0)


/* 3430 रेजिस्टर bits shared between CM & PRM रेजिस्टरs */

/* CM_REVISION, PRM_REVISION shared bits */
#घोषणा OMAP3430_REV_SHIFT				0
#घोषणा OMAP3430_REV_MASK				(0xff << 0)

/* CM_SYSCONFIG, PRM_SYSCONFIG shared bits */
#घोषणा OMAP3430_AUTOIDLE_MASK				(1 << 0)

/* CM_FCLKEN1_CORE, CM_ICLKEN1_CORE, PM_WKEN1_CORE shared bits */
#घोषणा OMAP3430_EN_MMC3_MASK				(1 << 30)
#घोषणा OMAP3430_EN_MMC3_SHIFT				30
#घोषणा OMAP3430_EN_MMC2_MASK				(1 << 25)
#घोषणा OMAP3430_EN_MMC2_SHIFT				25
#घोषणा OMAP3430_EN_MMC1_MASK				(1 << 24)
#घोषणा OMAP3430_EN_MMC1_SHIFT				24
#घोषणा AM35XX_EN_UART4_MASK				(1 << 23)
#घोषणा AM35XX_EN_UART4_SHIFT				23
#घोषणा OMAP3430_EN_MCSPI4_MASK				(1 << 21)
#घोषणा OMAP3430_EN_MCSPI4_SHIFT			21
#घोषणा OMAP3430_EN_MCSPI3_MASK				(1 << 20)
#घोषणा OMAP3430_EN_MCSPI3_SHIFT			20
#घोषणा OMAP3430_EN_MCSPI2_MASK				(1 << 19)
#घोषणा OMAP3430_EN_MCSPI2_SHIFT			19
#घोषणा OMAP3430_EN_MCSPI1_MASK				(1 << 18)
#घोषणा OMAP3430_EN_MCSPI1_SHIFT			18
#घोषणा OMAP3430_EN_I2C3_MASK				(1 << 17)
#घोषणा OMAP3430_EN_I2C3_SHIFT				17
#घोषणा OMAP3430_EN_I2C2_MASK				(1 << 16)
#घोषणा OMAP3430_EN_I2C2_SHIFT				16
#घोषणा OMAP3430_EN_I2C1_MASK				(1 << 15)
#घोषणा OMAP3430_EN_I2C1_SHIFT				15
#घोषणा OMAP3430_EN_UART2_MASK				(1 << 14)
#घोषणा OMAP3430_EN_UART2_SHIFT				14
#घोषणा OMAP3430_EN_UART1_MASK				(1 << 13)
#घोषणा OMAP3430_EN_UART1_SHIFT				13
#घोषणा OMAP3430_EN_GPT11_MASK				(1 << 12)
#घोषणा OMAP3430_EN_GPT11_SHIFT				12
#घोषणा OMAP3430_EN_GPT10_MASK				(1 << 11)
#घोषणा OMAP3430_EN_GPT10_SHIFT				11
#घोषणा OMAP3430_EN_MCBSP5_MASK				(1 << 10)
#घोषणा OMAP3430_EN_MCBSP5_SHIFT			10
#घोषणा OMAP3430_EN_MCBSP1_MASK				(1 << 9)
#घोषणा OMAP3430_EN_MCBSP1_SHIFT			9
#घोषणा OMAP3430_EN_FSHOSTUSB_MASK			(1 << 5)
#घोषणा OMAP3430_EN_FSHOSTUSB_SHIFT			5
#घोषणा OMAP3430_EN_D2D_MASK				(1 << 3)
#घोषणा OMAP3430_EN_D2D_SHIFT				3

/* CM_ICLKEN1_CORE, PM_WKEN1_CORE shared bits */
#घोषणा OMAP3430_EN_HSOTGUSB_MASK			(1 << 4)
#घोषणा OMAP3430_EN_HSOTGUSB_SHIFT			4

/* PM_WKST1_CORE, CM_IDLEST1_CORE shared bits */
#घोषणा OMAP3430_ST_MMC3_SHIFT				30
#घोषणा OMAP3430_ST_MMC3_MASK				(1 << 30)
#घोषणा OMAP3430_ST_MMC2_SHIFT				25
#घोषणा OMAP3430_ST_MMC2_MASK				(1 << 25)
#घोषणा OMAP3430_ST_MMC1_SHIFT				24
#घोषणा OMAP3430_ST_MMC1_MASK				(1 << 24)
#घोषणा OMAP3430_ST_MCSPI4_SHIFT			21
#घोषणा OMAP3430_ST_MCSPI4_MASK				(1 << 21)
#घोषणा OMAP3430_ST_MCSPI3_SHIFT			20
#घोषणा OMAP3430_ST_MCSPI3_MASK				(1 << 20)
#घोषणा OMAP3430_ST_MCSPI2_SHIFT			19
#घोषणा OMAP3430_ST_MCSPI2_MASK				(1 << 19)
#घोषणा OMAP3430_ST_MCSPI1_SHIFT			18
#घोषणा OMAP3430_ST_MCSPI1_MASK				(1 << 18)
#घोषणा OMAP3430_ST_I2C3_SHIFT				17
#घोषणा OMAP3430_ST_I2C3_MASK				(1 << 17)
#घोषणा OMAP3430_ST_I2C2_SHIFT				16
#घोषणा OMAP3430_ST_I2C2_MASK				(1 << 16)
#घोषणा OMAP3430_ST_I2C1_SHIFT				15
#घोषणा OMAP3430_ST_I2C1_MASK				(1 << 15)
#घोषणा OMAP3430_ST_UART2_SHIFT				14
#घोषणा OMAP3430_ST_UART2_MASK				(1 << 14)
#घोषणा OMAP3430_ST_UART1_SHIFT				13
#घोषणा OMAP3430_ST_UART1_MASK				(1 << 13)
#घोषणा OMAP3430_ST_GPT11_SHIFT				12
#घोषणा OMAP3430_ST_GPT11_MASK				(1 << 12)
#घोषणा OMAP3430_ST_GPT10_SHIFT				11
#घोषणा OMAP3430_ST_GPT10_MASK				(1 << 11)
#घोषणा OMAP3430_ST_MCBSP5_SHIFT			10
#घोषणा OMAP3430_ST_MCBSP5_MASK				(1 << 10)
#घोषणा OMAP3430_ST_MCBSP1_SHIFT			9
#घोषणा OMAP3430_ST_MCBSP1_MASK				(1 << 9)
#घोषणा OMAP3430ES1_ST_FSHOSTUSB_SHIFT			5
#घोषणा OMAP3430ES1_ST_FSHOSTUSB_MASK			(1 << 5)
#घोषणा OMAP3430ES1_ST_HSOTGUSB_SHIFT			4
#घोषणा OMAP3430ES1_ST_HSOTGUSB_MASK			(1 << 4)
#घोषणा OMAP3430ES2_ST_HSOTGUSB_IDLE_SHIFT		5
#घोषणा OMAP3430ES2_ST_HSOTGUSB_IDLE_MASK		(1 << 5)
#घोषणा OMAP3430ES2_ST_HSOTGUSB_STDBY_SHIFT		4
#घोषणा OMAP3430ES2_ST_HSOTGUSB_STDBY_MASK		(1 << 4)
#घोषणा OMAP3430_ST_D2D_SHIFT				3
#घोषणा OMAP3430_ST_D2D_MASK				(1 << 3)

/* CM_FCLKEN_WKUP, CM_ICLKEN_WKUP, PM_WKEN_WKUP shared bits */
#घोषणा OMAP3430_EN_GPIO1_MASK				(1 << 3)
#घोषणा OMAP3430_EN_GPIO1_SHIFT				3
#घोषणा OMAP3430_EN_GPT12_MASK				(1 << 1)
#घोषणा OMAP3430_EN_GPT12_SHIFT				1
#घोषणा OMAP3430_EN_GPT1_MASK				(1 << 0)
#घोषणा OMAP3430_EN_GPT1_SHIFT				0

/* CM_FCLKEN_WKUP, PM_WKEN_WKUP shared bits */
#घोषणा OMAP3430_EN_SR2_MASK				(1 << 7)
#घोषणा OMAP3430_EN_SR2_SHIFT				7
#घोषणा OMAP3430_EN_SR1_MASK				(1 << 6)
#घोषणा OMAP3430_EN_SR1_SHIFT				6

/* CM_ICLKEN_WKUP, PM_WKEN_WKUP shared bits */
#घोषणा OMAP3430_EN_GPT12_MASK				(1 << 1)
#घोषणा OMAP3430_EN_GPT12_SHIFT				1

/* CM_IDLEST_WKUP, PM_WKST_WKUP shared bits */
#घोषणा OMAP3430_ST_SR2_SHIFT				7
#घोषणा OMAP3430_ST_SR2_MASK				(1 << 7)
#घोषणा OMAP3430_ST_SR1_SHIFT				6
#घोषणा OMAP3430_ST_SR1_MASK				(1 << 6)
#घोषणा OMAP3430_ST_GPIO1_SHIFT				3
#घोषणा OMAP3430_ST_GPIO1_MASK				(1 << 3)
#घोषणा OMAP3430_ST_32KSYNC_SHIFT			2
#घोषणा OMAP3430_ST_32KSYNC_MASK			(1 << 2)
#घोषणा OMAP3430_ST_GPT12_SHIFT				1
#घोषणा OMAP3430_ST_GPT12_MASK				(1 << 1)
#घोषणा OMAP3430_ST_GPT1_SHIFT				0
#घोषणा OMAP3430_ST_GPT1_MASK				(1 << 0)

/*
 * CM_SLEEPDEP_GFX, CM_SLEEPDEP_DSS, CM_SLEEPDEP_CAM,
 * CM_SLEEPDEP_PER, PM_WKDEP_IVA2, PM_WKDEP_GFX,
 * PM_WKDEP_DSS, PM_WKDEP_CAM, PM_WKDEP_PER, PM_WKDEP_NEON shared bits
 */
#घोषणा OMAP3430_EN_MPU_MASK				(1 << 1)
#घोषणा OMAP3430_EN_MPU_SHIFT				1

/* CM_FCLKEN_PER, CM_ICLKEN_PER, PM_WKEN_PER shared bits */

#घोषणा OMAP3630_EN_UART4_MASK				(1 << 18)
#घोषणा OMAP3630_EN_UART4_SHIFT				18
#घोषणा OMAP3430_EN_GPIO6_MASK				(1 << 17)
#घोषणा OMAP3430_EN_GPIO6_SHIFT				17
#घोषणा OMAP3430_EN_GPIO5_MASK				(1 << 16)
#घोषणा OMAP3430_EN_GPIO5_SHIFT				16
#घोषणा OMAP3430_EN_GPIO4_MASK				(1 << 15)
#घोषणा OMAP3430_EN_GPIO4_SHIFT				15
#घोषणा OMAP3430_EN_GPIO3_MASK				(1 << 14)
#घोषणा OMAP3430_EN_GPIO3_SHIFT				14
#घोषणा OMAP3430_EN_GPIO2_MASK				(1 << 13)
#घोषणा OMAP3430_EN_GPIO2_SHIFT				13
#घोषणा OMAP3430_EN_UART3_MASK				(1 << 11)
#घोषणा OMAP3430_EN_UART3_SHIFT				11
#घोषणा OMAP3430_EN_GPT9_MASK				(1 << 10)
#घोषणा OMAP3430_EN_GPT9_SHIFT				10
#घोषणा OMAP3430_EN_GPT8_MASK				(1 << 9)
#घोषणा OMAP3430_EN_GPT8_SHIFT				9
#घोषणा OMAP3430_EN_GPT7_MASK				(1 << 8)
#घोषणा OMAP3430_EN_GPT7_SHIFT				8
#घोषणा OMAP3430_EN_GPT6_MASK				(1 << 7)
#घोषणा OMAP3430_EN_GPT6_SHIFT				7
#घोषणा OMAP3430_EN_GPT5_MASK				(1 << 6)
#घोषणा OMAP3430_EN_GPT5_SHIFT				6
#घोषणा OMAP3430_EN_GPT4_MASK				(1 << 5)
#घोषणा OMAP3430_EN_GPT4_SHIFT				5
#घोषणा OMAP3430_EN_GPT3_MASK				(1 << 4)
#घोषणा OMAP3430_EN_GPT3_SHIFT				4
#घोषणा OMAP3430_EN_GPT2_MASK				(1 << 3)
#घोषणा OMAP3430_EN_GPT2_SHIFT				3

/* CM_FCLKEN_PER, CM_ICLKEN_PER, PM_WKEN_PER, PM_WKST_PER shared bits */
/* XXX Possible TI करोcumentation bug: should the PM_WKST_PER EN_* bits
 * be ST_* bits instead? */
#घोषणा OMAP3430_EN_MCBSP4_MASK				(1 << 2)
#घोषणा OMAP3430_EN_MCBSP4_SHIFT			2
#घोषणा OMAP3430_EN_MCBSP3_MASK				(1 << 1)
#घोषणा OMAP3430_EN_MCBSP3_SHIFT			1
#घोषणा OMAP3430_EN_MCBSP2_MASK				(1 << 0)
#घोषणा OMAP3430_EN_MCBSP2_SHIFT			0

/* CM_IDLEST_PER, PM_WKST_PER shared bits */
#घोषणा OMAP3630_ST_UART4_SHIFT				18
#घोषणा OMAP3630_ST_UART4_MASK				(1 << 18)
#घोषणा OMAP3430_ST_GPIO6_SHIFT				17
#घोषणा OMAP3430_ST_GPIO6_MASK				(1 << 17)
#घोषणा OMAP3430_ST_GPIO5_SHIFT				16
#घोषणा OMAP3430_ST_GPIO5_MASK				(1 << 16)
#घोषणा OMAP3430_ST_GPIO4_SHIFT				15
#घोषणा OMAP3430_ST_GPIO4_MASK				(1 << 15)
#घोषणा OMAP3430_ST_GPIO3_SHIFT				14
#घोषणा OMAP3430_ST_GPIO3_MASK				(1 << 14)
#घोषणा OMAP3430_ST_GPIO2_SHIFT				13
#घोषणा OMAP3430_ST_GPIO2_MASK				(1 << 13)
#घोषणा OMAP3430_ST_UART3_SHIFT				11
#घोषणा OMAP3430_ST_UART3_MASK				(1 << 11)
#घोषणा OMAP3430_ST_GPT9_SHIFT				10
#घोषणा OMAP3430_ST_GPT9_MASK				(1 << 10)
#घोषणा OMAP3430_ST_GPT8_SHIFT				9
#घोषणा OMAP3430_ST_GPT8_MASK				(1 << 9)
#घोषणा OMAP3430_ST_GPT7_SHIFT				8
#घोषणा OMAP3430_ST_GPT7_MASK				(1 << 8)
#घोषणा OMAP3430_ST_GPT6_SHIFT				7
#घोषणा OMAP3430_ST_GPT6_MASK				(1 << 7)
#घोषणा OMAP3430_ST_GPT5_SHIFT				6
#घोषणा OMAP3430_ST_GPT5_MASK				(1 << 6)
#घोषणा OMAP3430_ST_GPT4_SHIFT				5
#घोषणा OMAP3430_ST_GPT4_MASK				(1 << 5)
#घोषणा OMAP3430_ST_GPT3_SHIFT				4
#घोषणा OMAP3430_ST_GPT3_MASK				(1 << 4)
#घोषणा OMAP3430_ST_GPT2_SHIFT				3
#घोषणा OMAP3430_ST_GPT2_MASK				(1 << 3)

/* CM_SLEEPDEP_PER, PM_WKDEP_IVA2, PM_WKDEP_MPU, PM_WKDEP_PER shared bits */
#घोषणा OMAP3430_EN_CORE_SHIFT				0
#घोषणा OMAP3430_EN_CORE_MASK				(1 << 0)



/*
 * Maximum समय(us) it takes to output the संकेत WUCLKOUT of the last
 * pad of the I/O ring after निश्चितing WUCLKIN high.  Tero measured
 * the actual समय at 7 to 8 microseconds on OMAP3 and 2 to 4
 * microseconds on OMAP4, so this समयout may be too high.
 */
#घोषणा MAX_IOPAD_LATCH_TIME			100
# अगरndef __ASSEMBLER__

#समावेश <linux/delay.h>

/**
 * omap_test_समयout - busy-loop, testing a condition
 * @cond: condition to test until it evaluates to true
 * @समयout: maximum number of microseconds in the समयout
 * @index: loop index (पूर्णांकeger)
 *
 * Loop रुकोing क्रम @cond to become true or until at least @समयout
 * microseconds have passed.  To use, define some पूर्णांकeger @index in the
 * calling code.  After running, अगर @index == @समयout, then the loop has
 * समयd out.
 */
#घोषणा omap_test_समयout(cond, समयout, index)			\
(अणु								\
	क्रम (index = 0; index < समयout; index++) अणु		\
		अगर (cond)					\
			अवरोध;					\
		udelay(1);					\
	पूर्ण							\
पूर्ण)

/**
 * काष्ठा omap_prcm_irq - describes a PRCM पूर्णांकerrupt bit
 * @name: a लघु name describing the पूर्णांकerrupt type, e.g. "wkup" or "io"
 * @offset: the bit shअगरt of the पूर्णांकerrupt inside the IRQअणुENABLE,STATUSपूर्ण regs
 * @priority: should this पूर्णांकerrupt be handled beक्रमe @priority=false IRQs?
 *
 * Describes पूर्णांकerrupt bits inside the PRM_IRQअणुENABLE,STATUSपूर्ण_MPU* रेजिस्टरs.
 * On प्रणालीs with multiple PRM MPU IRQ रेजिस्टरs, the bitfields पढ़ो from
 * the रेजिस्टरs are concatenated, so @offset could be > 31 on these प्रणालीs -
 * see omap_prm_irq_handler() क्रम more details.  I/O ring पूर्णांकerrupts should
 * have @priority set to true.
 */
काष्ठा omap_prcm_irq अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक offset;
	bool priority;
पूर्ण;

/**
 * काष्ठा omap_prcm_irq_setup - PRCM पूर्णांकerrupt controller details
 * @ack: PRM रेजिस्टर offset क्रम the first PRM_IRQSTATUS_MPU रेजिस्टर
 * @mask: PRM रेजिस्टर offset क्रम the first PRM_IRQENABLE_MPU रेजिस्टर
 * @pm_ctrl: PRM रेजिस्टर offset क्रम the PRM_IO_PMCTRL रेजिस्टर
 * @nr_regs: number of PRM_IRQअणुSTATUS,ENABLEपूर्ण_MPU* रेजिस्टरs
 * @nr_irqs: number of entries in the @irqs array
 * @irqs: ptr to an array of PRCM पूर्णांकerrupt bits (see @nr_irqs)
 * @irq: MPU IRQ निश्चितed when a PRCM पूर्णांकerrupt arrives
 * @पढ़ो_pending_irqs: fn ptr to determine अगर any PRCM IRQs are pending
 * @ocp_barrier: fn ptr to क्रमce buffered PRM ग_लिखोs to complete
 * @save_and_clear_irqen: fn ptr to save and clear IRQENABLE regs
 * @restore_irqen: fn ptr to save and clear IRQENABLE regs
 * @reconfigure_io_chain: fn ptr to reconfigure IO chain
 * @saved_mask: IRQENABLE regs are saved here during suspend
 * @priority_mask: 1 bit per IRQ, set to 1 अगर omap_prcm_irq.priority = true
 * @base_irq: base dynamic IRQ number, वापसed from irq_alloc_descs() in init
 * @suspended: set to true after Linux suspend code has called our ->prepare()
 * @suspend_save_flag: set to true after IRQ masks have been saved and disabled
 *
 * @saved_mask, @priority_mask, @base_irq, @suspended, and
 * @suspend_save_flag are populated dynamically, and are not to be
 * specअगरied in अटल initializers.
 */
काष्ठा omap_prcm_irq_setup अणु
	u16 ack;
	u16 mask;
	u16 pm_ctrl;
	u8 nr_regs;
	u8 nr_irqs;
	स्थिर काष्ठा omap_prcm_irq *irqs;
	पूर्णांक irq;
	व्योम (*पढ़ो_pending_irqs)(अचिन्हित दीर्घ *events);
	व्योम (*ocp_barrier)(व्योम);
	व्योम (*save_and_clear_irqen)(u32 *saved_mask);
	व्योम (*restore_irqen)(u32 *saved_mask);
	व्योम (*reconfigure_io_chain)(व्योम);
	u32 *saved_mask;
	u32 *priority_mask;
	पूर्णांक base_irq;
	bool suspended;
	bool suspend_save_flag;
पूर्ण;

/* OMAP_PRCM_IRQ: convenience macro क्रम creating काष्ठा omap_prcm_irq records */
#घोषणा OMAP_PRCM_IRQ(_name, _offset, _priority) अणु	\
	.name = _name,					\
	.offset = _offset,				\
	.priority = _priority				\
	पूर्ण

काष्ठा omap_करोमुख्य_base अणु
	u32 pa;
	व्योम __iomem *va;
	s16 offset;
पूर्ण;

/**
 * काष्ठा omap_prcm_init_data - PRCM driver init data
 * @index: घड़ी memory mapping index to be used
 * @mem: IO mem poपूर्णांकer क्रम this module
 * @phys: IO mem physical base address क्रम this module
 * @offset: module base address offset from the IO base
 * @flags: PRCM module init flags
 * @device_inst_offset: device instance offset within the module address space
 * @init: low level PRCM init function क्रम this module
 * @np: device node क्रम this PRCM module
 */
काष्ठा omap_prcm_init_data अणु
	पूर्णांक index;
	व्योम __iomem *mem;
	u32 phys;
	s16 offset;
	u16 flags;
	s32 device_inst_offset;
	पूर्णांक (*init)(स्थिर काष्ठा omap_prcm_init_data *data);
	काष्ठा device_node *np;
पूर्ण;

बाह्य व्योम omap_prcm_irq_cleanup(व्योम);
बाह्य पूर्णांक omap_prcm_रेजिस्टर_chain_handler(
	काष्ठा omap_prcm_irq_setup *irq_setup);
बाह्य पूर्णांक omap_prcm_event_to_irq(स्थिर अक्षर *event);
बाह्य व्योम omap_prcm_irq_prepare(व्योम);
बाह्य व्योम omap_prcm_irq_complete(व्योम);

# endअगर

#पूर्ण_अगर

