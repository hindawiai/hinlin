<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) STMicroelectronics 2009
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Kumar Sanghvi <kumar.sanghvi@stericsson.com>
 * Author: Sundar Iyer <sundar.iyer@stericsson.com>
 *
 * PRCM Unit रेजिस्टरs
 */

#अगर_अघोषित __DB8500_PRCMU_REGS_H
#घोषणा __DB8500_PRCMU_REGS_H

#घोषणा BITS(_start, _end) ((BIT(_end) - BIT(_start)) + BIT(_end))

#घोषणा PRCM_ACLK_MGT		(0x004)
#घोषणा PRCM_SVAMMCSPCLK_MGT	(0x008)
#घोषणा PRCM_SIAMMDSPCLK_MGT	(0x00C)
#घोषणा PRCM_SGACLK_MGT		(0x014)
#घोषणा PRCM_UARTCLK_MGT	(0x018)
#घोषणा PRCM_MSP02CLK_MGT	(0x01C)
#घोषणा PRCM_I2CCLK_MGT		(0x020)
#घोषणा PRCM_SDMMCCLK_MGT	(0x024)
#घोषणा PRCM_SLIMCLK_MGT	(0x028)
#घोषणा PRCM_PER1CLK_MGT	(0x02C)
#घोषणा PRCM_PER2CLK_MGT	(0x030)
#घोषणा PRCM_PER3CLK_MGT	(0x034)
#घोषणा PRCM_PER5CLK_MGT	(0x038)
#घोषणा PRCM_PER6CLK_MGT	(0x03C)
#घोषणा PRCM_PER7CLK_MGT	(0x040)
#घोषणा PRCM_LCDCLK_MGT		(0x044)
#घोषणा PRCM_BMLCLK_MGT		(0x04C)
#घोषणा PRCM_HSITXCLK_MGT	(0x050)
#घोषणा PRCM_HSIRXCLK_MGT	(0x054)
#घोषणा PRCM_HDMICLK_MGT	(0x058)
#घोषणा PRCM_APEATCLK_MGT	(0x05C)
#घोषणा PRCM_APETRACECLK_MGT	(0x060)
#घोषणा PRCM_MCDECLK_MGT	(0x064)
#घोषणा PRCM_IPI2CCLK_MGT	(0x068)
#घोषणा PRCM_DSIALTCLK_MGT	(0x06C)
#घोषणा PRCM_DMACLK_MGT		(0x074)
#घोषणा PRCM_B2R2CLK_MGT	(0x078)
#घोषणा PRCM_TVCLK_MGT		(0x07C)
#घोषणा PRCM_UNIPROCLK_MGT	(0x278)
#घोषणा PRCM_SSPCLK_MGT		(0x280)
#घोषणा PRCM_RNGCLK_MGT		(0x284)
#घोषणा PRCM_UICCCLK_MGT	(0x27C)
#घोषणा PRCM_MSP1CLK_MGT	(0x288)

#घोषणा PRCM_ARM_PLLDIVPS	(prcmu_base + 0x118)
#घोषणा PRCM_ARM_PLLDIVPS_ARM_BRM_RATE		0x3f
#घोषणा PRCM_ARM_PLLDIVPS_MAX_MASK		0xf

#घोषणा PRCM_PLLARM_LOCKP       (prcmu_base + 0x0a8)
#घोषणा PRCM_PLLARM_LOCKP_PRCM_PLLARM_LOCKP3	0x2

#घोषणा PRCM_ARM_CHGCLKREQ	(prcmu_base + 0x114)
#घोषणा PRCM_ARM_CHGCLKREQ_PRCM_ARM_CHGCLKREQ	BIT(0)
#घोषणा PRCM_ARM_CHGCLKREQ_PRCM_ARM_DIVSEL	BIT(16)

#घोषणा PRCM_PLLARM_ENABLE	(prcmu_base + 0x98)
#घोषणा PRCM_PLLARM_ENABLE_PRCM_PLLARM_ENABLE	0x1
#घोषणा PRCM_PLLARM_ENABLE_PRCM_PLLARM_COUNTON	0x100

#घोषणा PRCM_ARMCLKFIX_MGT	(prcmu_base + 0x0)
#घोषणा PRCM_A9PL_FORCE_CLKEN	(prcmu_base + 0x19C)
#घोषणा PRCM_A9_RESETN_CLR	(prcmu_base + 0x1f4)
#घोषणा PRCM_A9_RESETN_SET	(prcmu_base + 0x1f0)
#घोषणा PRCM_ARM_LS_CLAMP	(prcmu_base + 0x30c)
#घोषणा PRCM_SRAM_A9		(prcmu_base + 0x308)

#घोषणा PRCM_A9PL_FORCE_CLKEN_PRCM_A9PL_FORCE_CLKEN BIT(0)
#घोषणा PRCM_A9PL_FORCE_CLKEN_PRCM_A9AXI_FORCE_CLKEN BIT(1)

/* CPU mailbox रेजिस्टरs */
#घोषणा PRCM_MBOX_CPU_VAL	(prcmu_base + 0x0fc)
#घोषणा PRCM_MBOX_CPU_SET	(prcmu_base + 0x100)
#घोषणा PRCM_MBOX_CPU_CLR	(prcmu_base + 0x104)

#घोषणा PRCM_HOSTACCESS_REQ	(prcmu_base + 0x334)
#घोषणा PRCM_HOSTACCESS_REQ_HOSTACCESS_REQ 0x1
#घोषणा PRCM_HOSTACCESS_REQ_WAKE_REQ	BIT(16)
#घोषणा ARM_WAKEUP_MODEM	0x1

#घोषणा PRCM_ARM_IT1_CLR	(prcmu_base + 0x48C)
#घोषणा PRCM_ARM_IT1_VAL	(prcmu_base + 0x494)
#घोषणा PRCM_HOLD_EVT		(prcmu_base + 0x174)

#घोषणा PRCM_MOD_AWAKE_STATUS	(prcmu_base + 0x4A0)
#घोषणा PRCM_MOD_AWAKE_STATUS_PRCM_MOD_COREPD_AWAKE	BIT(0)
#घोषणा PRCM_MOD_AWAKE_STATUS_PRCM_MOD_AAPD_AWAKE	BIT(1)
#घोषणा PRCM_MOD_AWAKE_STATUS_PRCM_MOD_VMODEM_OFF_ISO	BIT(2)

#घोषणा PRCM_ITSTATUS0		(prcmu_base + 0x148)
#घोषणा PRCM_ITSTATUS1		(prcmu_base + 0x150)
#घोषणा PRCM_ITSTATUS2		(prcmu_base + 0x158)
#घोषणा PRCM_ITSTATUS3		(prcmu_base + 0x160)
#घोषणा PRCM_ITSTATUS4		(prcmu_base + 0x168)
#घोषणा PRCM_ITSTATUS5		(prcmu_base + 0x484)
#घोषणा PRCM_ITCLEAR5		(prcmu_base + 0x488)
#घोषणा PRCM_ARMIT_MASKXP70_IT	(prcmu_base + 0x1018)

/* System reset रेजिस्टर */
#घोषणा PRCM_APE_SOFTRST	(prcmu_base + 0x228)

/* Level shअगरter and clamp control रेजिस्टरs */
#घोषणा PRCM_MMIP_LS_CLAMP_SET     (prcmu_base + 0x420)
#घोषणा PRCM_MMIP_LS_CLAMP_CLR     (prcmu_base + 0x424)

#घोषणा PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMP		BIT(11)
#घोषणा PRCM_MMIP_LS_CLAMP_DSIPLL_CLAMPI	BIT(22)

/* PRCMU घड़ी/PLL/reset रेजिस्टरs */
#घोषणा PRCM_PLLSOC0_FREQ	   (prcmu_base + 0x080)
#घोषणा PRCM_PLLSOC1_FREQ	   (prcmu_base + 0x084)
#घोषणा PRCM_PLLARM_FREQ	   (prcmu_base + 0x088)
#घोषणा PRCM_PLLDDR_FREQ	   (prcmu_base + 0x08C)
#घोषणा PRCM_PLL_FREQ_D_SHIFT	0
#घोषणा PRCM_PLL_FREQ_D_MASK	BITS(0, 7)
#घोषणा PRCM_PLL_FREQ_N_SHIFT	8
#घोषणा PRCM_PLL_FREQ_N_MASK	BITS(8, 13)
#घोषणा PRCM_PLL_FREQ_R_SHIFT	16
#घोषणा PRCM_PLL_FREQ_R_MASK	BITS(16, 18)
#घोषणा PRCM_PLL_FREQ_SELDIV2	BIT(24)
#घोषणा PRCM_PLL_FREQ_DIV2EN	BIT(25)

#घोषणा PRCM_PLLDSI_FREQ           (prcmu_base + 0x500)
#घोषणा PRCM_PLLDSI_ENABLE         (prcmu_base + 0x504)
#घोषणा PRCM_PLLDSI_LOCKP          (prcmu_base + 0x508)
#घोषणा PRCM_DSI_PLLOUT_SEL        (prcmu_base + 0x530)
#घोषणा PRCM_DSITVCLK_DIV          (prcmu_base + 0x52C)
#घोषणा PRCM_PLLDSI_LOCKP          (prcmu_base + 0x508)
#घोषणा PRCM_APE_RESETN_SET        (prcmu_base + 0x1E4)
#घोषणा PRCM_APE_RESETN_CLR        (prcmu_base + 0x1E8)

#घोषणा PRCM_PLLDSI_ENABLE_PRCM_PLLDSI_ENABLE BIT(0)

#घोषणा PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP10	BIT(0)
#घोषणा PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP3	BIT(1)

#घोषणा PRCM_DSI_PLLOUT_SEL_DSI0_PLLOUT_DIVSEL_SHIFT	0
#घोषणा PRCM_DSI_PLLOUT_SEL_DSI0_PLLOUT_DIVSEL_MASK	BITS(0, 2)
#घोषणा PRCM_DSI_PLLOUT_SEL_DSI1_PLLOUT_DIVSEL_SHIFT	8
#घोषणा PRCM_DSI_PLLOUT_SEL_DSI1_PLLOUT_DIVSEL_MASK	BITS(8, 10)

#घोषणा PRCM_DSI_PLLOUT_SEL_OFF		0
#घोषणा PRCM_DSI_PLLOUT_SEL_PHI		1
#घोषणा PRCM_DSI_PLLOUT_SEL_PHI_2	2
#घोषणा PRCM_DSI_PLLOUT_SEL_PHI_4	3

#घोषणा PRCM_DSITVCLK_DIV_DSI0_ESC_CLK_DIV_SHIFT	0
#घोषणा PRCM_DSITVCLK_DIV_DSI0_ESC_CLK_DIV_MASK		BITS(0, 7)
#घोषणा PRCM_DSITVCLK_DIV_DSI1_ESC_CLK_DIV_SHIFT	8
#घोषणा PRCM_DSITVCLK_DIV_DSI1_ESC_CLK_DIV_MASK		BITS(8, 15)
#घोषणा PRCM_DSITVCLK_DIV_DSI2_ESC_CLK_DIV_SHIFT	16
#घोषणा PRCM_DSITVCLK_DIV_DSI2_ESC_CLK_DIV_MASK		BITS(16, 23)
#घोषणा PRCM_DSITVCLK_DIV_DSI0_ESC_CLK_EN		BIT(24)
#घोषणा PRCM_DSITVCLK_DIV_DSI1_ESC_CLK_EN		BIT(25)
#घोषणा PRCM_DSITVCLK_DIV_DSI2_ESC_CLK_EN		BIT(26)

#घोषणा PRCM_APE_RESETN_DSIPLL_RESETN BIT(14)

#घोषणा PRCM_CLKOCR		   (prcmu_base + 0x1CC)
#घोषणा PRCM_CLKOCR_CLKOUT0_REF_CLK	(1 << 0)
#घोषणा PRCM_CLKOCR_CLKOUT0_MASK	BITS(0, 13)
#घोषणा PRCM_CLKOCR_CLKOUT1_REF_CLK	(1 << 16)
#घोषणा PRCM_CLKOCR_CLKOUT1_MASK	BITS(16, 29)

/* ePOD and memory घातer संकेत control रेजिस्टरs */
#घोषणा PRCM_EPOD_C_SET            (prcmu_base + 0x410)
#घोषणा PRCM_SRAM_LS_SLEEP         (prcmu_base + 0x304)

/* Debug घातer control unit रेजिस्टरs */
#घोषणा PRCM_POWER_STATE_SET       (prcmu_base + 0x254)

/* Miscellaneous unit रेजिस्टरs */
#घोषणा PRCM_DSI_SW_RESET          (prcmu_base + 0x324)
#घोषणा PRCM_GPIOCR                (prcmu_base + 0x138)
#घोषणा PRCM_GPIOCR_DBG_STM_MOD_CMD1            0x800
#घोषणा PRCM_GPIOCR_DBG_UARTMOD_CMD0            0x1

/* PRCMU HW semaphore */
#घोषणा PRCM_SEM                   (prcmu_base + 0x400)
#घोषणा PRCM_SEM_PRCM_SEM BIT(0)

#घोषणा PRCM_TCR                   (prcmu_base + 0x1C8)
#घोषणा PRCM_TCR_TENSEL_MASK       BITS(0, 7)
#घोषणा PRCM_TCR_STOP_TIMERS       BIT(16)
#घोषणा PRCM_TCR_DOZE_MODE         BIT(17)

#घोषणा PRCM_CLKOCR_CLKODIV0_SHIFT	0
#घोषणा PRCM_CLKOCR_CLKODIV0_MASK	BITS(0, 5)
#घोषणा PRCM_CLKOCR_CLKOSEL0_SHIFT	6
#घोषणा PRCM_CLKOCR_CLKOSEL0_MASK	BITS(6, 8)
#घोषणा PRCM_CLKOCR_CLKODIV1_SHIFT	16
#घोषणा PRCM_CLKOCR_CLKODIV1_MASK	BITS(16, 21)
#घोषणा PRCM_CLKOCR_CLKOSEL1_SHIFT	22
#घोषणा PRCM_CLKOCR_CLKOSEL1_MASK	BITS(22, 24)
#घोषणा PRCM_CLKOCR_CLK1TYPE		BIT(28)

#घोषणा PRCM_CLK_MGT_CLKPLLDIV_MASK		BITS(0, 4)
#घोषणा PRCM_CLK_MGT_CLKPLLSW_SOC0		BIT(5)
#घोषणा PRCM_CLK_MGT_CLKPLLSW_SOC1		BIT(6)
#घोषणा PRCM_CLK_MGT_CLKPLLSW_DDR		BIT(7)
#घोषणा PRCM_CLK_MGT_CLKPLLSW_MASK		BITS(5, 7)
#घोषणा PRCM_CLK_MGT_CLKEN			BIT(8)
#घोषणा PRCM_CLK_MGT_CLK38			BIT(9)
#घोषणा PRCM_CLK_MGT_CLK38DIV			BIT(11)
#घोषणा PRCM_SGACLK_MGT_SGACLKDIV_BY_2_5_EN	BIT(12)

/* GPIOCR रेजिस्टर */
#घोषणा PRCM_GPIOCR_SPI2_SELECT BIT(23)

#घोषणा PRCM_DDR_SUBSYS_APE_MINBW	(prcmu_base + 0x438)
#घोषणा PRCM_CGATING_BYPASS		(prcmu_base + 0x134)
#घोषणा PRCM_CGATING_BYPASS_ICN2	BIT(6)

/* Miscellaneous unit रेजिस्टरs */
#घोषणा PRCM_RESOUTN_SET		(prcmu_base + 0x214)
#घोषणा PRCM_RESOUTN_CLR		(prcmu_base + 0x218)

/* System reset रेजिस्टर */
#घोषणा PRCM_APE_SOFTRST		(prcmu_base + 0x228)

#पूर्ण_अगर /* __DB8500_PRCMU_REGS_H */
