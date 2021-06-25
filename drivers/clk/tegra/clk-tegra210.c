<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/clk/tegra.h>
#समावेश <dt-bindings/घड़ी/tegra210-car.h>
#समावेश <dt-bindings/reset/tegra210-car.h>
#समावेश <linux/sizes.h>
#समावेश <soc/tegra/pmc.h>

#समावेश "clk.h"
#समावेश "clk-id.h"

/*
 * TEGRA210_CAR_BANK_COUNT: the number of peripheral घड़ी रेजिस्टर
 * banks present in the Tegra210 CAR IP block.  The banks are
 * identअगरied by single letters, e.g.: L, H, U, V, W, X, Y.  See
 * periph_regs[] in drivers/clk/tegra/clk.c
 */
#घोषणा TEGRA210_CAR_BANK_COUNT			7

#घोषणा CLK_SOURCE_CSITE 0x1d4
#घोषणा CLK_SOURCE_EMC 0x19c
#घोषणा CLK_SOURCE_SOR1 0x410
#घोषणा CLK_SOURCE_SOR0 0x414
#घोषणा CLK_SOURCE_LA 0x1f8
#घोषणा CLK_SOURCE_SDMMC2 0x154
#घोषणा CLK_SOURCE_SDMMC4 0x164
#घोषणा CLK_SOURCE_EMC_DLL 0x664

#घोषणा PLLC_BASE 0x80
#घोषणा PLLC_OUT 0x84
#घोषणा PLLC_MISC0 0x88
#घोषणा PLLC_MISC1 0x8c
#घोषणा PLLC_MISC2 0x5d0
#घोषणा PLLC_MISC3 0x5d4

#घोषणा PLLC2_BASE 0x4e8
#घोषणा PLLC2_MISC0 0x4ec
#घोषणा PLLC2_MISC1 0x4f0
#घोषणा PLLC2_MISC2 0x4f4
#घोषणा PLLC2_MISC3 0x4f8

#घोषणा PLLC3_BASE 0x4fc
#घोषणा PLLC3_MISC0 0x500
#घोषणा PLLC3_MISC1 0x504
#घोषणा PLLC3_MISC2 0x508
#घोषणा PLLC3_MISC3 0x50c

#घोषणा PLLM_BASE 0x90
#घोषणा PLLM_MISC1 0x98
#घोषणा PLLM_MISC2 0x9c
#घोषणा PLLP_BASE 0xa0
#घोषणा PLLP_MISC0 0xac
#घोषणा PLLP_MISC1 0x680
#घोषणा PLLA_BASE 0xb0
#घोषणा PLLA_MISC0 0xbc
#घोषणा PLLA_MISC1 0xb8
#घोषणा PLLA_MISC2 0x5d8
#घोषणा PLLD_BASE 0xd0
#घोषणा PLLD_MISC0 0xdc
#घोषणा PLLD_MISC1 0xd8
#घोषणा PLLU_BASE 0xc0
#घोषणा PLLU_OUTA 0xc4
#घोषणा PLLU_MISC0 0xcc
#घोषणा PLLU_MISC1 0xc8
#घोषणा PLLX_BASE 0xe0
#घोषणा PLLX_MISC0 0xe4
#घोषणा PLLX_MISC1 0x510
#घोषणा PLLX_MISC2 0x514
#घोषणा PLLX_MISC3 0x518
#घोषणा PLLX_MISC4 0x5f0
#घोषणा PLLX_MISC5 0x5f4
#घोषणा PLLE_BASE 0xe8
#घोषणा PLLE_MISC0 0xec
#घोषणा PLLD2_BASE 0x4b8
#घोषणा PLLD2_MISC0 0x4bc
#घोषणा PLLD2_MISC1 0x570
#घोषणा PLLD2_MISC2 0x574
#घोषणा PLLD2_MISC3 0x578
#घोषणा PLLE_AUX 0x48c
#घोषणा PLLRE_BASE 0x4c4
#घोषणा PLLRE_MISC0 0x4c8
#घोषणा PLLRE_OUT1 0x4cc
#घोषणा PLLDP_BASE 0x590
#घोषणा PLLDP_MISC 0x594

#घोषणा PLLC4_BASE 0x5a4
#घोषणा PLLC4_MISC0 0x5a8
#घोषणा PLLC4_OUT 0x5e4
#घोषणा PLLMB_BASE 0x5e8
#घोषणा PLLMB_MISC1 0x5ec
#घोषणा PLLA1_BASE 0x6a4
#घोषणा PLLA1_MISC0 0x6a8
#घोषणा PLLA1_MISC1 0x6ac
#घोषणा PLLA1_MISC2 0x6b0
#घोषणा PLLA1_MISC3 0x6b4

#घोषणा PLLU_IDDQ_BIT 31
#घोषणा PLLCX_IDDQ_BIT 27
#घोषणा PLLRE_IDDQ_BIT 24
#घोषणा PLLA_IDDQ_BIT 25
#घोषणा PLLD_IDDQ_BIT 20
#घोषणा PLLSS_IDDQ_BIT 18
#घोषणा PLLM_IDDQ_BIT 5
#घोषणा PLLMB_IDDQ_BIT 17
#घोषणा PLLXP_IDDQ_BIT 3

#घोषणा PLLCX_RESET_BIT 30

#घोषणा PLL_BASE_LOCK BIT(27)
#घोषणा PLLCX_BASE_LOCK BIT(26)
#घोषणा PLLE_MISC_LOCK BIT(11)
#घोषणा PLLRE_MISC_LOCK BIT(27)

#घोषणा PLL_MISC_LOCK_ENABLE 18
#घोषणा PLLC_MISC_LOCK_ENABLE 24
#घोषणा PLLDU_MISC_LOCK_ENABLE 22
#घोषणा PLLU_MISC_LOCK_ENABLE 29
#घोषणा PLLE_MISC_LOCK_ENABLE 9
#घोषणा PLLRE_MISC_LOCK_ENABLE 30
#घोषणा PLLSS_MISC_LOCK_ENABLE 30
#घोषणा PLLP_MISC_LOCK_ENABLE 18
#घोषणा PLLM_MISC_LOCK_ENABLE 4
#घोषणा PLLMB_MISC_LOCK_ENABLE 16
#घोषणा PLLA_MISC_LOCK_ENABLE 28
#घोषणा PLLU_MISC_LOCK_ENABLE 29
#घोषणा PLLD_MISC_LOCK_ENABLE 18

#घोषणा PLLA_SDM_DIN_MASK 0xffff
#घोषणा PLLA_SDM_EN_MASK BIT(26)

#घोषणा PLLD_SDM_EN_MASK BIT(16)

#घोषणा PLLD2_SDM_EN_MASK BIT(31)
#घोषणा PLLD2_SSC_EN_MASK 0

#घोषणा PLLDP_SS_CFG	0x598
#घोषणा PLLDP_SDM_EN_MASK BIT(31)
#घोषणा PLLDP_SSC_EN_MASK BIT(30)
#घोषणा PLLDP_SS_CTRL1	0x59c
#घोषणा PLLDP_SS_CTRL2	0x5a0

#घोषणा PMC_PLLM_WB0_OVERRIDE 0x1dc
#घोषणा PMC_PLLM_WB0_OVERRIDE_2 0x2b0

#घोषणा UTMIP_PLL_CFG2 0x488
#घोषणा UTMIP_PLL_CFG2_STABLE_COUNT(x) (((x) & 0xfff) << 6)
#घोषणा UTMIP_PLL_CFG2_ACTIVE_DLY_COUNT(x) (((x) & 0x3f) << 18)
#घोषणा UTMIP_PLL_CFG2_FORCE_PD_SAMP_A_POWERDOWN BIT(0)
#घोषणा UTMIP_PLL_CFG2_FORCE_PD_SAMP_A_POWERUP BIT(1)
#घोषणा UTMIP_PLL_CFG2_FORCE_PD_SAMP_B_POWERDOWN BIT(2)
#घोषणा UTMIP_PLL_CFG2_FORCE_PD_SAMP_B_POWERUP BIT(3)
#घोषणा UTMIP_PLL_CFG2_FORCE_PD_SAMP_C_POWERDOWN BIT(4)
#घोषणा UTMIP_PLL_CFG2_FORCE_PD_SAMP_C_POWERUP BIT(5)
#घोषणा UTMIP_PLL_CFG2_FORCE_PD_SAMP_D_POWERDOWN BIT(24)
#घोषणा UTMIP_PLL_CFG2_FORCE_PD_SAMP_D_POWERUP BIT(25)

#घोषणा UTMIP_PLL_CFG1 0x484
#घोषणा UTMIP_PLL_CFG1_ENABLE_DLY_COUNT(x) (((x) & 0x1f) << 27)
#घोषणा UTMIP_PLL_CFG1_XTAL_FREQ_COUNT(x) (((x) & 0xfff) << 0)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLLU_POWERUP BIT(17)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLLU_POWERDOWN BIT(16)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERUP BIT(15)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERDOWN BIT(14)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLL_ACTIVE_POWERDOWN BIT(12)

#घोषणा SATA_PLL_CFG0				0x490
#घोषणा SATA_PLL_CFG0_PADPLL_RESET_SWCTL	BIT(0)
#घोषणा SATA_PLL_CFG0_PADPLL_USE_LOCKDET	BIT(2)
#घोषणा SATA_PLL_CFG0_SATA_SEQ_IN_SWCTL		BIT(4)
#घोषणा SATA_PLL_CFG0_SATA_SEQ_RESET_INPUT_VALUE	BIT(5)
#घोषणा SATA_PLL_CFG0_SATA_SEQ_LANE_PD_INPUT_VALUE	BIT(6)
#घोषणा SATA_PLL_CFG0_SATA_SEQ_PADPLL_PD_INPUT_VALUE	BIT(7)

#घोषणा SATA_PLL_CFG0_PADPLL_SLEEP_IDDQ		BIT(13)
#घोषणा SATA_PLL_CFG0_SEQ_ENABLE		BIT(24)

#घोषणा XUSBIO_PLL_CFG0				0x51c
#घोषणा XUSBIO_PLL_CFG0_PADPLL_RESET_SWCTL	BIT(0)
#घोषणा XUSBIO_PLL_CFG0_CLK_ENABLE_SWCTL	BIT(2)
#घोषणा XUSBIO_PLL_CFG0_PADPLL_USE_LOCKDET	BIT(6)
#घोषणा XUSBIO_PLL_CFG0_PADPLL_SLEEP_IDDQ	BIT(13)
#घोषणा XUSBIO_PLL_CFG0_SEQ_ENABLE		BIT(24)

#घोषणा UTMIPLL_HW_PWRDN_CFG0			0x52c
#घोषणा UTMIPLL_HW_PWRDN_CFG0_UTMIPLL_LOCK	BIT(31)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_SEQ_START_STATE	BIT(25)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_SEQ_ENABLE	BIT(24)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_IDDQ_PD_INCLUDE	BIT(7)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_USE_LOCKDET	BIT(6)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_SEQ_RESET_INPUT_VALUE	BIT(5)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_SEQ_IN_SWCTL	BIT(4)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_CLK_ENABLE_SWCTL	BIT(2)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_IDDQ_OVERRIDE	BIT(1)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_IDDQ_SWCTL	BIT(0)

#घोषणा PLLU_HW_PWRDN_CFG0			0x530
#घोषणा PLLU_HW_PWRDN_CFG0_IDDQ_PD_INCLUDE	BIT(28)
#घोषणा PLLU_HW_PWRDN_CFG0_SEQ_ENABLE		BIT(24)
#घोषणा PLLU_HW_PWRDN_CFG0_USE_SWITCH_DETECT	BIT(7)
#घोषणा PLLU_HW_PWRDN_CFG0_USE_LOCKDET		BIT(6)
#घोषणा PLLU_HW_PWRDN_CFG0_CLK_ENABLE_SWCTL	BIT(2)
#घोषणा PLLU_HW_PWRDN_CFG0_CLK_SWITCH_SWCTL	BIT(0)

#घोषणा XUSB_PLL_CFG0				0x534
#घोषणा XUSB_PLL_CFG0_UTMIPLL_LOCK_DLY		0x3ff
#घोषणा XUSB_PLL_CFG0_PLLU_LOCK_DLY_MASK	(0x3ff << 14)

#घोषणा SPARE_REG0 0x55c
#घोषणा CLK_M_DIVISOR_SHIFT 2
#घोषणा CLK_M_DIVISOR_MASK 0x3

#घोषणा CLK_MASK_ARM	0x44
#घोषणा MISC_CLK_ENB	0x48

#घोषणा RST_DFLL_DVCO 0x2f4
#घोषणा DVFS_DFLL_RESET_SHIFT 0

#घोषणा CLK_RST_CONTROLLER_CLK_OUT_ENB_X_SET	0x284
#घोषणा CLK_RST_CONTROLLER_CLK_OUT_ENB_X_CLR	0x288
#घोषणा CLK_OUT_ENB_X_CLK_ENB_EMC_DLL		BIT(14)

#घोषणा CLK_RST_CONTROLLER_RST_DEV_Y_SET 0x2a8
#घोषणा CLK_RST_CONTROLLER_RST_DEV_Y_CLR 0x2ac
#घोषणा CPU_SOFTRST_CTRL 0x380

#घोषणा LVL2_CLK_GATE_OVRA 0xf8
#घोषणा LVL2_CLK_GATE_OVRC 0x3a0
#घोषणा LVL2_CLK_GATE_OVRD 0x3a4
#घोषणा LVL2_CLK_GATE_OVRE 0x554

/* I2S रेजिस्टरs to handle during APE MBIST WAR */
#घोषणा TEGRA210_I2S_BASE  0x1000
#घोषणा TEGRA210_I2S_SIZE  0x100
#घोषणा TEGRA210_I2S_CTRLS 5
#घोषणा TEGRA210_I2S_CG    0x88
#घोषणा TEGRA210_I2S_CTRL  0xa0

/* DISPA रेजिस्टरs to handle during MBIST WAR */
#घोषणा DC_CMD_DISPLAY_COMMAND 0xc8
#घोषणा DC_COM_DSC_TOP_CTL 0xcf8

/* VIC रेजिस्टर to handle during MBIST WAR */
#घोषणा NV_PVIC_THI_SLCG_OVERRIDE_LOW 0x8c

/* APE, DISPA and VIC base addesses needed क्रम MBIST WAR */
#घोषणा TEGRA210_AHUB_BASE  0x702d0000
#घोषणा TEGRA210_DISPA_BASE 0x54200000
#घोषणा TEGRA210_VIC_BASE  0x54340000

/*
 * SDM fractional भागisor is 16-bit 2's complement चिन्हित number within
 * (-2^12 ... 2^12-1) range. Represented in PLL data काष्ठाure as अचिन्हित
 * 16-bit value, with "0" भागisor mapped to 0xFFFF. Data "0" is used to
 * indicate that SDM is disabled.
 *
 * Effective nभाग value when SDM is enabled: nभाग + 1/2 + sdm_din/2^13
 */
#घोषणा PLL_SDM_COEFF BIT(13)
#घोषणा sdin_din_to_data(din)	((u16)((din) ? : 0xFFFFU))
#घोषणा sdin_data_to_din(dat)	(((dat) == 0xFFFFU) ? 0 : (s16)dat)
/* This macro वापसs nभाग effective scaled to SDM range */
#घोषणा sdin_get_n_eff(cfg)	((cfg)->n * PLL_SDM_COEFF + ((cfg)->sdm_data ? \
		(PLL_SDM_COEFF/2 + sdin_data_to_din((cfg)->sdm_data)) : 0))

/* Tegra CPU घड़ी and reset control regs */
#घोषणा CLK_RST_CONTROLLER_CPU_CMPLX_STATUS	0x470

#अगर_घोषित CONFIG_PM_SLEEP
अटल काष्ठा cpu_clk_suspend_context अणु
	u32 clk_csite_src;
पूर्ण tegra210_cpu_clk_sctx;
#पूर्ण_अगर

काष्ठा tegra210_करोमुख्य_mbist_war अणु
	व्योम (*handle_lvl2_ovr)(काष्ठा tegra210_करोमुख्य_mbist_war *mbist);
	स्थिर u32 lvl2_offset;
	स्थिर u32 lvl2_mask;
	स्थिर अचिन्हित पूर्णांक num_clks;
	स्थिर अचिन्हित पूर्णांक *clk_init_data;
	काष्ठा clk_bulk_data *clks;
पूर्ण;

अटल काष्ठा clk **clks;

अटल व्योम __iomem *clk_base;
अटल व्योम __iomem *pmc_base;
अटल व्योम __iomem *ahub_base;
अटल व्योम __iomem *dispa_base;
अटल व्योम __iomem *vic_base;

अटल अचिन्हित दीर्घ osc_freq;
अटल अचिन्हित दीर्घ pll_ref_freq;

अटल DEFINE_SPINLOCK(pll_d_lock);
अटल DEFINE_SPINLOCK(pll_e_lock);
अटल DEFINE_SPINLOCK(pll_re_lock);
अटल DEFINE_SPINLOCK(pll_u_lock);
अटल DEFINE_SPINLOCK(sor0_lock);
अटल DEFINE_SPINLOCK(sor1_lock);
अटल DEFINE_SPINLOCK(emc_lock);
अटल DEFINE_MUTEX(lvl2_ovr_lock);

/* possible OSC frequencies in Hz */
अटल अचिन्हित दीर्घ tegra210_input_freq[] = अणु
	[5] = 38400000,
	[8] = 12000000,
पूर्ण;

#घोषणा PLL_ENABLE			(1 << 30)

#घोषणा PLLCX_MISC1_IDDQ		(1 << 27)
#घोषणा PLLCX_MISC0_RESET		(1 << 30)

#घोषणा PLLCX_MISC0_DEFAULT_VALUE	0x40080000
#घोषणा PLLCX_MISC0_WRITE_MASK		0x400ffffb
#घोषणा PLLCX_MISC1_DEFAULT_VALUE	0x08000000
#घोषणा PLLCX_MISC1_WRITE_MASK		0x08003cff
#घोषणा PLLCX_MISC2_DEFAULT_VALUE	0x1f720f05
#घोषणा PLLCX_MISC2_WRITE_MASK		0xffffff17
#घोषणा PLLCX_MISC3_DEFAULT_VALUE	0x000000c4
#घोषणा PLLCX_MISC3_WRITE_MASK		0x00ffffff

/* PLLA */
#घोषणा PLLA_BASE_IDDQ			(1 << 25)
#घोषणा PLLA_BASE_LOCK			(1 << 27)

#घोषणा PLLA_MISC0_LOCK_ENABLE		(1 << 28)
#घोषणा PLLA_MISC0_LOCK_OVERRIDE	(1 << 27)

#घोषणा PLLA_MISC2_EN_SDM		(1 << 26)
#घोषणा PLLA_MISC2_EN_DYNRAMP		(1 << 25)

#घोषणा PLLA_MISC0_DEFAULT_VALUE	0x12000020
#घोषणा PLLA_MISC0_WRITE_MASK		0x7fffffff
#घोषणा PLLA_MISC2_DEFAULT_VALUE	0x0
#घोषणा PLLA_MISC2_WRITE_MASK		0x06ffffff

/* PLLD */
#घोषणा PLLD_BASE_CSI_CLKSOURCE		(1 << 23)

#घोषणा PLLD_MISC0_EN_SDM		(1 << 16)
#घोषणा PLLD_MISC0_LOCK_OVERRIDE	(1 << 17)
#घोषणा PLLD_MISC0_LOCK_ENABLE		(1 << 18)
#घोषणा PLLD_MISC0_IDDQ			(1 << 20)
#घोषणा PLLD_MISC0_DSI_CLKENABLE	(1 << 21)

#घोषणा PLLD_MISC0_DEFAULT_VALUE	0x00140000
#घोषणा PLLD_MISC0_WRITE_MASK		0x3ff7ffff
#घोषणा PLLD_MISC1_DEFAULT_VALUE	0x20
#घोषणा PLLD_MISC1_WRITE_MASK		0x00ffffff

/* PLLD2 and PLLDP  and PLLC4 */
#घोषणा PLLDSS_BASE_LOCK		(1 << 27)
#घोषणा PLLDSS_BASE_LOCK_OVERRIDE	(1 << 24)
#घोषणा PLLDSS_BASE_IDDQ		(1 << 18)
#घोषणा PLLDSS_BASE_REF_SEL_SHIFT	25
#घोषणा PLLDSS_BASE_REF_SEL_MASK	(0x3 << PLLDSS_BASE_REF_SEL_SHIFT)

#घोषणा PLLDSS_MISC0_LOCK_ENABLE	(1 << 30)

#घोषणा PLLDSS_MISC1_CFG_EN_SDM		(1 << 31)
#घोषणा PLLDSS_MISC1_CFG_EN_SSC		(1 << 30)

#घोषणा PLLD2_MISC0_DEFAULT_VALUE	0x40000020
#घोषणा PLLD2_MISC1_CFG_DEFAULT_VALUE	0x10000000
#घोषणा PLLD2_MISC2_CTRL1_DEFAULT_VALUE	0x0
#घोषणा PLLD2_MISC3_CTRL2_DEFAULT_VALUE	0x0

#घोषणा PLLDP_MISC0_DEFAULT_VALUE	0x40000020
#घोषणा PLLDP_MISC1_CFG_DEFAULT_VALUE	0xc0000000
#घोषणा PLLDP_MISC2_CTRL1_DEFAULT_VALUE	0xf400f0da
#घोषणा PLLDP_MISC3_CTRL2_DEFAULT_VALUE	0x2004f400

#घोषणा PLLDSS_MISC0_WRITE_MASK		0x47ffffff
#घोषणा PLLDSS_MISC1_CFG_WRITE_MASK	0xf8000000
#घोषणा PLLDSS_MISC2_CTRL1_WRITE_MASK	0xffffffff
#घोषणा PLLDSS_MISC3_CTRL2_WRITE_MASK	0xffffffff

#घोषणा PLLC4_MISC0_DEFAULT_VALUE	0x40000000

/* PLLRE */
#घोषणा PLLRE_MISC0_LOCK_ENABLE		(1 << 30)
#घोषणा PLLRE_MISC0_LOCK_OVERRIDE	(1 << 29)
#घोषणा PLLRE_MISC0_LOCK		(1 << 27)
#घोषणा PLLRE_MISC0_IDDQ		(1 << 24)

#घोषणा PLLRE_BASE_DEFAULT_VALUE	0x0
#घोषणा PLLRE_MISC0_DEFAULT_VALUE	0x41000000

#घोषणा PLLRE_BASE_DEFAULT_MASK		0x1c000000
#घोषणा PLLRE_MISC0_WRITE_MASK		0x67ffffff

/* PLLE */
#घोषणा PLLE_MISC_IDDQ_SW_CTRL		(1 << 14)
#घोषणा PLLE_AUX_USE_LOCKDET		(1 << 3)
#घोषणा PLLE_AUX_SS_SEQ_INCLUDE		(1 << 31)
#घोषणा PLLE_AUX_ENABLE_SWCTL		(1 << 4)
#घोषणा PLLE_AUX_SS_SWCTL		(1 << 6)
#घोषणा PLLE_AUX_SEQ_ENABLE		(1 << 24)

/* PLLX */
#घोषणा PLLX_USE_DYN_RAMP		1
#घोषणा PLLX_BASE_LOCK			(1 << 27)

#घोषणा PLLX_MISC0_FO_G_DISABLE		(0x1 << 28)
#घोषणा PLLX_MISC0_LOCK_ENABLE		(0x1 << 18)

#घोषणा PLLX_MISC2_DYNRAMP_STEPB_SHIFT	24
#घोषणा PLLX_MISC2_DYNRAMP_STEPB_MASK	(0xFF << PLLX_MISC2_DYNRAMP_STEPB_SHIFT)
#घोषणा PLLX_MISC2_DYNRAMP_STEPA_SHIFT	16
#घोषणा PLLX_MISC2_DYNRAMP_STEPA_MASK	(0xFF << PLLX_MISC2_DYNRAMP_STEPA_SHIFT)
#घोषणा PLLX_MISC2_NDIV_NEW_SHIFT	8
#घोषणा PLLX_MISC2_NDIV_NEW_MASK	(0xFF << PLLX_MISC2_NDIV_NEW_SHIFT)
#घोषणा PLLX_MISC2_LOCK_OVERRIDE	(0x1 << 4)
#घोषणा PLLX_MISC2_DYNRAMP_DONE		(0x1 << 2)
#घोषणा PLLX_MISC2_EN_DYNRAMP		(0x1 << 0)

#घोषणा PLLX_MISC3_IDDQ			(0x1 << 3)

#घोषणा PLLX_MISC0_DEFAULT_VALUE	PLLX_MISC0_LOCK_ENABLE
#घोषणा PLLX_MISC0_WRITE_MASK		0x10c40000
#घोषणा PLLX_MISC1_DEFAULT_VALUE	0x20
#घोषणा PLLX_MISC1_WRITE_MASK		0x00ffffff
#घोषणा PLLX_MISC2_DEFAULT_VALUE	0x0
#घोषणा PLLX_MISC2_WRITE_MASK		0xffffff11
#घोषणा PLLX_MISC3_DEFAULT_VALUE	PLLX_MISC3_IDDQ
#घोषणा PLLX_MISC3_WRITE_MASK		0x01ff0f0f
#घोषणा PLLX_MISC4_DEFAULT_VALUE	0x0
#घोषणा PLLX_MISC4_WRITE_MASK		0x8000ffff
#घोषणा PLLX_MISC5_DEFAULT_VALUE	0x0
#घोषणा PLLX_MISC5_WRITE_MASK		0x0000ffff

#घोषणा PLLX_HW_CTRL_CFG		0x548
#घोषणा PLLX_HW_CTRL_CFG_SWCTRL		(0x1 << 0)

/* PLLMB */
#घोषणा PLLMB_BASE_LOCK			(1 << 27)

#घोषणा PLLMB_MISC1_LOCK_OVERRIDE	(1 << 18)
#घोषणा PLLMB_MISC1_IDDQ		(1 << 17)
#घोषणा PLLMB_MISC1_LOCK_ENABLE		(1 << 16)

#घोषणा PLLMB_MISC1_DEFAULT_VALUE	0x00030000
#घोषणा PLLMB_MISC1_WRITE_MASK		0x0007ffff

/* PLLP */
#घोषणा PLLP_BASE_OVERRIDE		(1 << 28)
#घोषणा PLLP_BASE_LOCK			(1 << 27)

#घोषणा PLLP_MISC0_LOCK_ENABLE		(1 << 18)
#घोषणा PLLP_MISC0_LOCK_OVERRIDE	(1 << 17)
#घोषणा PLLP_MISC0_IDDQ			(1 << 3)

#घोषणा PLLP_MISC1_HSIO_EN_SHIFT	29
#घोषणा PLLP_MISC1_HSIO_EN		(1 << PLLP_MISC1_HSIO_EN_SHIFT)
#घोषणा PLLP_MISC1_XUSB_EN_SHIFT	28
#घोषणा PLLP_MISC1_XUSB_EN		(1 << PLLP_MISC1_XUSB_EN_SHIFT)

#घोषणा PLLP_MISC0_DEFAULT_VALUE	0x00040008
#घोषणा PLLP_MISC1_DEFAULT_VALUE	0x0

#घोषणा PLLP_MISC0_WRITE_MASK		0xdc6000f
#घोषणा PLLP_MISC1_WRITE_MASK		0x70ffffff

/* PLLU */
#घोषणा PLLU_BASE_LOCK			(1 << 27)
#घोषणा PLLU_BASE_OVERRIDE		(1 << 24)
#घोषणा PLLU_BASE_CLKENABLE_USB		(1 << 21)
#घोषणा PLLU_BASE_CLKENABLE_HSIC	(1 << 22)
#घोषणा PLLU_BASE_CLKENABLE_ICUSB	(1 << 23)
#घोषणा PLLU_BASE_CLKENABLE_48M		(1 << 25)
#घोषणा PLLU_BASE_CLKENABLE_ALL		(PLLU_BASE_CLKENABLE_USB |\
					 PLLU_BASE_CLKENABLE_HSIC |\
					 PLLU_BASE_CLKENABLE_ICUSB |\
					 PLLU_BASE_CLKENABLE_48M)

#घोषणा PLLU_MISC0_IDDQ			(1 << 31)
#घोषणा PLLU_MISC0_LOCK_ENABLE		(1 << 29)
#घोषणा PLLU_MISC1_LOCK_OVERRIDE	(1 << 0)

#घोषणा PLLU_MISC0_DEFAULT_VALUE	0xa0000000
#घोषणा PLLU_MISC1_DEFAULT_VALUE	0x0

#घोषणा PLLU_MISC0_WRITE_MASK		0xbfffffff
#घोषणा PLLU_MISC1_WRITE_MASK		0x00000007

bool tegra210_plle_hw_sequence_is_enabled(व्योम)
अणु
	u32 value;

	value = पढ़ोl_relaxed(clk_base + PLLE_AUX);
	अगर (value & PLLE_AUX_SEQ_ENABLE)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_plle_hw_sequence_is_enabled);

पूर्णांक tegra210_plle_hw_sequence_start(व्योम)
अणु
	u32 value;

	अगर (tegra210_plle_hw_sequence_is_enabled())
		वापस 0;

	/* skip अगर PLLE is not enabled yet */
	value = पढ़ोl_relaxed(clk_base + PLLE_MISC0);
	अगर (!(value & PLLE_MISC_LOCK))
		वापस -EIO;

	value &= ~PLLE_MISC_IDDQ_SW_CTRL;
	ग_लिखोl_relaxed(value, clk_base + PLLE_MISC0);

	value = पढ़ोl_relaxed(clk_base + PLLE_AUX);
	value |= (PLLE_AUX_USE_LOCKDET | PLLE_AUX_SS_SEQ_INCLUDE);
	value &= ~(PLLE_AUX_ENABLE_SWCTL | PLLE_AUX_SS_SWCTL);
	ग_लिखोl_relaxed(value, clk_base + PLLE_AUX);

	fence_udelay(1, clk_base);

	value |= PLLE_AUX_SEQ_ENABLE;
	ग_लिखोl_relaxed(value, clk_base + PLLE_AUX);

	fence_udelay(1, clk_base);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_plle_hw_sequence_start);

व्योम tegra210_xusb_pll_hw_control_enable(व्योम)
अणु
	u32 val;

	val = पढ़ोl_relaxed(clk_base + XUSBIO_PLL_CFG0);
	val &= ~(XUSBIO_PLL_CFG0_CLK_ENABLE_SWCTL |
		 XUSBIO_PLL_CFG0_PADPLL_RESET_SWCTL);
	val |= XUSBIO_PLL_CFG0_PADPLL_USE_LOCKDET |
	       XUSBIO_PLL_CFG0_PADPLL_SLEEP_IDDQ;
	ग_लिखोl_relaxed(val, clk_base + XUSBIO_PLL_CFG0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_xusb_pll_hw_control_enable);

व्योम tegra210_xusb_pll_hw_sequence_start(व्योम)
अणु
	u32 val;

	val = पढ़ोl_relaxed(clk_base + XUSBIO_PLL_CFG0);
	val |= XUSBIO_PLL_CFG0_SEQ_ENABLE;
	ग_लिखोl_relaxed(val, clk_base + XUSBIO_PLL_CFG0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_xusb_pll_hw_sequence_start);

व्योम tegra210_sata_pll_hw_control_enable(व्योम)
अणु
	u32 val;

	val = पढ़ोl_relaxed(clk_base + SATA_PLL_CFG0);
	val &= ~SATA_PLL_CFG0_PADPLL_RESET_SWCTL;
	val |= SATA_PLL_CFG0_PADPLL_USE_LOCKDET |
	       SATA_PLL_CFG0_PADPLL_SLEEP_IDDQ;
	ग_लिखोl_relaxed(val, clk_base + SATA_PLL_CFG0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_sata_pll_hw_control_enable);

व्योम tegra210_sata_pll_hw_sequence_start(व्योम)
अणु
	u32 val;

	val = पढ़ोl_relaxed(clk_base + SATA_PLL_CFG0);
	val |= SATA_PLL_CFG0_SEQ_ENABLE;
	ग_लिखोl_relaxed(val, clk_base + SATA_PLL_CFG0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_sata_pll_hw_sequence_start);

व्योम tegra210_set_sata_pll_seq_sw(bool state)
अणु
	u32 val;

	val = पढ़ोl_relaxed(clk_base + SATA_PLL_CFG0);
	अगर (state) अणु
		val |= SATA_PLL_CFG0_SATA_SEQ_IN_SWCTL;
		val |= SATA_PLL_CFG0_SATA_SEQ_RESET_INPUT_VALUE;
		val |= SATA_PLL_CFG0_SATA_SEQ_LANE_PD_INPUT_VALUE;
		val |= SATA_PLL_CFG0_SATA_SEQ_PADPLL_PD_INPUT_VALUE;
	पूर्ण अन्यथा अणु
		val &= ~SATA_PLL_CFG0_SATA_SEQ_IN_SWCTL;
		val &= ~SATA_PLL_CFG0_SATA_SEQ_RESET_INPUT_VALUE;
		val &= ~SATA_PLL_CFG0_SATA_SEQ_LANE_PD_INPUT_VALUE;
		val &= ~SATA_PLL_CFG0_SATA_SEQ_PADPLL_PD_INPUT_VALUE;
	पूर्ण
	ग_लिखोl_relaxed(val, clk_base + SATA_PLL_CFG0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_set_sata_pll_seq_sw);

व्योम tegra210_clk_emc_dll_enable(bool flag)
अणु
	u32 offset = flag ? CLK_RST_CONTROLLER_CLK_OUT_ENB_X_SET :
		     CLK_RST_CONTROLLER_CLK_OUT_ENB_X_CLR;

	ग_लिखोl_relaxed(CLK_OUT_ENB_X_CLK_ENB_EMC_DLL, clk_base + offset);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_clk_emc_dll_enable);

व्योम tegra210_clk_emc_dll_update_setting(u32 emc_dll_src_value)
अणु
	ग_लिखोl_relaxed(emc_dll_src_value, clk_base + CLK_SOURCE_EMC_DLL);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_clk_emc_dll_update_setting);

व्योम tegra210_clk_emc_update_setting(u32 emc_src_value)
अणु
	ग_लिखोl_relaxed(emc_src_value, clk_base + CLK_SOURCE_EMC);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_clk_emc_update_setting);

अटल व्योम tegra210_generic_mbist_war(काष्ठा tegra210_करोमुख्य_mbist_war *mbist)
अणु
	u32 val;

	val = पढ़ोl_relaxed(clk_base + mbist->lvl2_offset);
	ग_लिखोl_relaxed(val | mbist->lvl2_mask, clk_base + mbist->lvl2_offset);
	fence_udelay(1, clk_base);
	ग_लिखोl_relaxed(val, clk_base + mbist->lvl2_offset);
	fence_udelay(1, clk_base);
पूर्ण

अटल व्योम tegra210_venc_mbist_war(काष्ठा tegra210_करोमुख्य_mbist_war *mbist)
अणु
	u32 csi_src, ovra, ovre;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&pll_d_lock, flags);

	csi_src = पढ़ोl_relaxed(clk_base + PLLD_BASE);
	ग_लिखोl_relaxed(csi_src | PLLD_BASE_CSI_CLKSOURCE, clk_base + PLLD_BASE);
	fence_udelay(1, clk_base);

	ovra = पढ़ोl_relaxed(clk_base + LVL2_CLK_GATE_OVRA);
	ग_लिखोl_relaxed(ovra | BIT(15), clk_base + LVL2_CLK_GATE_OVRA);
	ovre = पढ़ोl_relaxed(clk_base + LVL2_CLK_GATE_OVRE);
	ग_लिखोl_relaxed(ovre | BIT(3), clk_base + LVL2_CLK_GATE_OVRE);
	fence_udelay(1, clk_base);

	ग_लिखोl_relaxed(ovra, clk_base + LVL2_CLK_GATE_OVRA);
	ग_लिखोl_relaxed(ovre, clk_base + LVL2_CLK_GATE_OVRE);
	ग_लिखोl_relaxed(csi_src, clk_base + PLLD_BASE);
	fence_udelay(1, clk_base);

	spin_unlock_irqrestore(&pll_d_lock, flags);
पूर्ण

अटल व्योम tegra210_disp_mbist_war(काष्ठा tegra210_करोमुख्य_mbist_war *mbist)
अणु
	u32 ovra, dsc_top_ctrl;

	ovra = पढ़ोl_relaxed(clk_base + LVL2_CLK_GATE_OVRA);
	ग_लिखोl_relaxed(ovra | BIT(1), clk_base + LVL2_CLK_GATE_OVRA);
	fence_udelay(1, clk_base);

	dsc_top_ctrl = पढ़ोl_relaxed(dispa_base + DC_COM_DSC_TOP_CTL);
	ग_लिखोl_relaxed(dsc_top_ctrl | BIT(2), dispa_base + DC_COM_DSC_TOP_CTL);
	पढ़ोl_relaxed(dispa_base + DC_CMD_DISPLAY_COMMAND);
	ग_लिखोl_relaxed(dsc_top_ctrl, dispa_base + DC_COM_DSC_TOP_CTL);
	पढ़ोl_relaxed(dispa_base + DC_CMD_DISPLAY_COMMAND);

	ग_लिखोl_relaxed(ovra, clk_base + LVL2_CLK_GATE_OVRA);
	fence_udelay(1, clk_base);
पूर्ण

अटल व्योम tegra210_vic_mbist_war(काष्ठा tegra210_करोमुख्य_mbist_war *mbist)
अणु
	u32 ovre, val;

	ovre = पढ़ोl_relaxed(clk_base + LVL2_CLK_GATE_OVRE);
	ग_लिखोl_relaxed(ovre | BIT(5), clk_base + LVL2_CLK_GATE_OVRE);
	fence_udelay(1, clk_base);

	val = पढ़ोl_relaxed(vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);
	ग_लिखोl_relaxed(val | BIT(0) | GENMASK(7, 2) | BIT(24),
			vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);
	fence_udelay(1, vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);

	ग_लिखोl_relaxed(val, vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);
	पढ़ोl(vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);

	ग_लिखोl_relaxed(ovre, clk_base + LVL2_CLK_GATE_OVRE);
	fence_udelay(1, clk_base);
पूर्ण

अटल व्योम tegra210_ape_mbist_war(काष्ठा tegra210_करोमुख्य_mbist_war *mbist)
अणु
	व्योम __iomem *i2s_base;
	अचिन्हित पूर्णांक i;
	u32 ovrc, ovre;

	ovrc = पढ़ोl_relaxed(clk_base + LVL2_CLK_GATE_OVRC);
	ovre = पढ़ोl_relaxed(clk_base + LVL2_CLK_GATE_OVRE);
	ग_लिखोl_relaxed(ovrc | BIT(1), clk_base + LVL2_CLK_GATE_OVRC);
	ग_लिखोl_relaxed(ovre | BIT(10) | BIT(11),
			clk_base + LVL2_CLK_GATE_OVRE);
	fence_udelay(1, clk_base);

	i2s_base = ahub_base + TEGRA210_I2S_BASE;

	क्रम (i = 0; i < TEGRA210_I2S_CTRLS; i++) अणु
		u32 i2s_ctrl;

		i2s_ctrl = पढ़ोl_relaxed(i2s_base + TEGRA210_I2S_CTRL);
		ग_लिखोl_relaxed(i2s_ctrl | BIT(10),
				i2s_base + TEGRA210_I2S_CTRL);
		ग_लिखोl_relaxed(0, i2s_base + TEGRA210_I2S_CG);
		पढ़ोl(i2s_base + TEGRA210_I2S_CG);
		ग_लिखोl_relaxed(1, i2s_base + TEGRA210_I2S_CG);
		ग_लिखोl_relaxed(i2s_ctrl, i2s_base + TEGRA210_I2S_CTRL);
		पढ़ोl(i2s_base + TEGRA210_I2S_CTRL);

		i2s_base += TEGRA210_I2S_SIZE;
	पूर्ण

	ग_लिखोl_relaxed(ovrc, clk_base + LVL2_CLK_GATE_OVRC);
	ग_लिखोl_relaxed(ovre, clk_base + LVL2_CLK_GATE_OVRE);
	fence_udelay(1, clk_base);
पूर्ण

अटल अंतरभूत व्योम _pll_misc_chk_शेष(व्योम __iomem *base,
					काष्ठा tegra_clk_pll_params *params,
					u8 misc_num, u32 शेष_val, u32 mask)
अणु
	u32 boot_val = पढ़ोl_relaxed(base + params->ext_misc_reg[misc_num]);

	boot_val &= mask;
	शेष_val &= mask;
	अगर (boot_val != शेष_val) अणु
		pr_warn("boot misc%d 0x%x: expected 0x%x\n",
			misc_num, boot_val, शेष_val);
		pr_warn(" (comparison mask = 0x%x)\n", mask);
		params->शेषs_set = false;
	पूर्ण
पूर्ण

/*
 * PLLCX: PLLC, PLLC2, PLLC3, PLLA1
 * Hybrid PLLs with dynamic ramp. Dynamic ramp is allowed क्रम any transition
 * that changes NDIV only, जबतक PLL is alपढ़ोy locked.
 */
अटल व्योम pllcx_check_शेषs(काष्ठा tegra_clk_pll_params *params)
अणु
	u32 शेष_val;

	शेष_val = PLLCX_MISC0_DEFAULT_VALUE & (~PLLCX_MISC0_RESET);
	_pll_misc_chk_शेष(clk_base, params, 0, शेष_val,
			PLLCX_MISC0_WRITE_MASK);

	शेष_val = PLLCX_MISC1_DEFAULT_VALUE & (~PLLCX_MISC1_IDDQ);
	_pll_misc_chk_शेष(clk_base, params, 1, शेष_val,
			PLLCX_MISC1_WRITE_MASK);

	शेष_val = PLLCX_MISC2_DEFAULT_VALUE;
	_pll_misc_chk_शेष(clk_base, params, 2, शेष_val,
			PLLCX_MISC2_WRITE_MASK);

	शेष_val = PLLCX_MISC3_DEFAULT_VALUE;
	_pll_misc_chk_शेष(clk_base, params, 3, शेष_val,
			PLLCX_MISC3_WRITE_MASK);
पूर्ण

अटल व्योम tegra210_pllcx_set_शेषs(स्थिर अक्षर *name,
					काष्ठा tegra_clk_pll *pllcx)
अणु
	pllcx->params->शेषs_set = true;

	अगर (पढ़ोl_relaxed(clk_base + pllcx->params->base_reg) & PLL_ENABLE) अणु
		/* PLL is ON: only check अगर शेषs alपढ़ोy set */
		pllcx_check_शेषs(pllcx->params);
		अगर (!pllcx->params->शेषs_set)
			pr_warn("%s already enabled. Postponing set full defaults\n",
				name);
		वापस;
	पूर्ण

	/* Defaults निश्चित PLL reset, and set IDDQ */
	ग_लिखोl_relaxed(PLLCX_MISC0_DEFAULT_VALUE,
			clk_base + pllcx->params->ext_misc_reg[0]);
	ग_लिखोl_relaxed(PLLCX_MISC1_DEFAULT_VALUE,
			clk_base + pllcx->params->ext_misc_reg[1]);
	ग_लिखोl_relaxed(PLLCX_MISC2_DEFAULT_VALUE,
			clk_base + pllcx->params->ext_misc_reg[2]);
	ग_लिखोl_relaxed(PLLCX_MISC3_DEFAULT_VALUE,
			clk_base + pllcx->params->ext_misc_reg[3]);
	udelay(1);
पूर्ण

अटल व्योम _pllc_set_शेषs(काष्ठा tegra_clk_pll *pllcx)
अणु
	tegra210_pllcx_set_शेषs("PLL_C", pllcx);
पूर्ण

अटल व्योम _pllc2_set_शेषs(काष्ठा tegra_clk_pll *pllcx)
अणु
	tegra210_pllcx_set_शेषs("PLL_C2", pllcx);
पूर्ण

अटल व्योम _pllc3_set_शेषs(काष्ठा tegra_clk_pll *pllcx)
अणु
	tegra210_pllcx_set_शेषs("PLL_C3", pllcx);
पूर्ण

अटल व्योम _plla1_set_शेषs(काष्ठा tegra_clk_pll *pllcx)
अणु
	tegra210_pllcx_set_शेषs("PLL_A1", pllcx);
पूर्ण

/*
 * PLLA
 * PLL with dynamic ramp and fractional SDM. Dynamic ramp is not used.
 * Fractional SDM is allowed to provide exact audio rates.
 */
अटल व्योम tegra210_plla_set_शेषs(काष्ठा tegra_clk_pll *plla)
अणु
	u32 mask;
	u32 val = पढ़ोl_relaxed(clk_base + plla->params->base_reg);

	plla->params->शेषs_set = true;

	अगर (val & PLL_ENABLE) अणु
		/*
		 * PLL is ON: check अगर शेषs alपढ़ोy set, then set those
		 * that can be updated in flight.
		 */
		अगर (val & PLLA_BASE_IDDQ) अणु
			pr_warn("PLL_A boot enabled with IDDQ set\n");
			plla->params->शेषs_set = false;
		पूर्ण

		pr_warn("PLL_A already enabled. Postponing set full defaults\n");

		val = PLLA_MISC0_DEFAULT_VALUE;	/* ignore lock enable */
		mask = PLLA_MISC0_LOCK_ENABLE | PLLA_MISC0_LOCK_OVERRIDE;
		_pll_misc_chk_शेष(clk_base, plla->params, 0, val,
				~mask & PLLA_MISC0_WRITE_MASK);

		val = PLLA_MISC2_DEFAULT_VALUE; /* ignore all but control bit */
		_pll_misc_chk_शेष(clk_base, plla->params, 2, val,
				PLLA_MISC2_EN_DYNRAMP);

		/* Enable lock detect */
		val = पढ़ोl_relaxed(clk_base + plla->params->ext_misc_reg[0]);
		val &= ~mask;
		val |= PLLA_MISC0_DEFAULT_VALUE & mask;
		ग_लिखोl_relaxed(val, clk_base + plla->params->ext_misc_reg[0]);
		udelay(1);

		वापस;
	पूर्ण

	/* set IDDQ, enable lock detect, disable dynamic ramp and SDM */
	val |= PLLA_BASE_IDDQ;
	ग_लिखोl_relaxed(val, clk_base + plla->params->base_reg);
	ग_लिखोl_relaxed(PLLA_MISC0_DEFAULT_VALUE,
			clk_base + plla->params->ext_misc_reg[0]);
	ग_लिखोl_relaxed(PLLA_MISC2_DEFAULT_VALUE,
			clk_base + plla->params->ext_misc_reg[2]);
	udelay(1);
पूर्ण

/*
 * PLLD
 * PLL with fractional SDM.
 */
अटल व्योम tegra210_plld_set_शेषs(काष्ठा tegra_clk_pll *plld)
अणु
	u32 val;
	u32 mask = 0xffff;

	plld->params->शेषs_set = true;

	अगर (पढ़ोl_relaxed(clk_base + plld->params->base_reg) &
			PLL_ENABLE) अणु

		/*
		 * PLL is ON: check अगर शेषs alपढ़ोy set, then set those
		 * that can be updated in flight.
		 */
		val = PLLD_MISC1_DEFAULT_VALUE;
		_pll_misc_chk_शेष(clk_base, plld->params, 1,
				val, PLLD_MISC1_WRITE_MASK);

		/* ignore lock, DSI and SDM controls, make sure IDDQ not set */
		val = PLLD_MISC0_DEFAULT_VALUE & (~PLLD_MISC0_IDDQ);
		mask |= PLLD_MISC0_DSI_CLKENABLE | PLLD_MISC0_LOCK_ENABLE |
			PLLD_MISC0_LOCK_OVERRIDE | PLLD_MISC0_EN_SDM;
		_pll_misc_chk_शेष(clk_base, plld->params, 0, val,
				~mask & PLLD_MISC0_WRITE_MASK);

		अगर (!plld->params->शेषs_set)
			pr_warn("PLL_D already enabled. Postponing set full defaults\n");

		/* Enable lock detect */
		mask = PLLD_MISC0_LOCK_ENABLE | PLLD_MISC0_LOCK_OVERRIDE;
		val = पढ़ोl_relaxed(clk_base + plld->params->ext_misc_reg[0]);
		val &= ~mask;
		val |= PLLD_MISC0_DEFAULT_VALUE & mask;
		ग_लिखोl_relaxed(val, clk_base + plld->params->ext_misc_reg[0]);
		udelay(1);

		वापस;
	पूर्ण

	val = पढ़ोl_relaxed(clk_base + plld->params->ext_misc_reg[0]);
	val &= PLLD_MISC0_DSI_CLKENABLE;
	val |= PLLD_MISC0_DEFAULT_VALUE;
	/* set IDDQ, enable lock detect, disable SDM */
	ग_लिखोl_relaxed(val, clk_base + plld->params->ext_misc_reg[0]);
	ग_लिखोl_relaxed(PLLD_MISC1_DEFAULT_VALUE, clk_base +
			plld->params->ext_misc_reg[1]);
	udelay(1);
पूर्ण

/*
 * PLLD2, PLLDP
 * PLL with fractional SDM and Spपढ़ो Spectrum (SDM is a must अगर SSC is used).
 */
अटल व्योम plldss_शेषs(स्थिर अक्षर *pll_name, काष्ठा tegra_clk_pll *plldss,
		u32 misc0_val, u32 misc1_val, u32 misc2_val, u32 misc3_val)
अणु
	u32 शेष_val;
	u32 val = पढ़ोl_relaxed(clk_base + plldss->params->base_reg);

	plldss->params->शेषs_set = true;

	अगर (val & PLL_ENABLE) अणु

		/*
		 * PLL is ON: check अगर शेषs alपढ़ोy set, then set those
		 * that can be updated in flight.
		 */
		अगर (val & PLLDSS_BASE_IDDQ) अणु
			pr_warn("plldss boot enabled with IDDQ set\n");
			plldss->params->शेषs_set = false;
		पूर्ण

		/* ignore lock enable */
		शेष_val = misc0_val;
		_pll_misc_chk_शेष(clk_base, plldss->params, 0, शेष_val,
				     PLLDSS_MISC0_WRITE_MASK &
				     (~PLLDSS_MISC0_LOCK_ENABLE));

		/*
		 * If SSC is used, check all settings, otherwise just confirm
		 * that SSC is not used on boot as well. Do nothing when using
		 * this function क्रम PLLC4 that has only MISC0.
		 */
		अगर (plldss->params->ssc_ctrl_en_mask) अणु
			शेष_val = misc1_val;
			_pll_misc_chk_शेष(clk_base, plldss->params, 1,
				शेष_val, PLLDSS_MISC1_CFG_WRITE_MASK);
			शेष_val = misc2_val;
			_pll_misc_chk_शेष(clk_base, plldss->params, 2,
				शेष_val, PLLDSS_MISC2_CTRL1_WRITE_MASK);
			शेष_val = misc3_val;
			_pll_misc_chk_शेष(clk_base, plldss->params, 3,
				शेष_val, PLLDSS_MISC3_CTRL2_WRITE_MASK);
		पूर्ण अन्यथा अगर (plldss->params->ext_misc_reg[1]) अणु
			शेष_val = misc1_val;
			_pll_misc_chk_शेष(clk_base, plldss->params, 1,
				शेष_val, PLLDSS_MISC1_CFG_WRITE_MASK &
				(~PLLDSS_MISC1_CFG_EN_SDM));
		पूर्ण

		अगर (!plldss->params->शेषs_set)
			pr_warn("%s already enabled. Postponing set full defaults\n",
				 pll_name);

		/* Enable lock detect */
		अगर (val & PLLDSS_BASE_LOCK_OVERRIDE) अणु
			val &= ~PLLDSS_BASE_LOCK_OVERRIDE;
			ग_लिखोl_relaxed(val, clk_base +
					plldss->params->base_reg);
		पूर्ण

		val = पढ़ोl_relaxed(clk_base + plldss->params->ext_misc_reg[0]);
		val &= ~PLLDSS_MISC0_LOCK_ENABLE;
		val |= misc0_val & PLLDSS_MISC0_LOCK_ENABLE;
		ग_लिखोl_relaxed(val, clk_base + plldss->params->ext_misc_reg[0]);
		udelay(1);

		वापस;
	पूर्ण

	/* set IDDQ, enable lock detect, configure SDM/SSC  */
	val |= PLLDSS_BASE_IDDQ;
	val &= ~PLLDSS_BASE_LOCK_OVERRIDE;
	ग_लिखोl_relaxed(val, clk_base + plldss->params->base_reg);

	/* When using this function क्रम PLLC4 निकास here */
	अगर (!plldss->params->ext_misc_reg[1]) अणु
		ग_लिखोl_relaxed(misc0_val, clk_base +
				plldss->params->ext_misc_reg[0]);
		udelay(1);
		वापस;
	पूर्ण

	ग_लिखोl_relaxed(misc0_val, clk_base +
			plldss->params->ext_misc_reg[0]);
	/* अगर SSC used set by 1st enable */
	ग_लिखोl_relaxed(misc1_val & (~PLLDSS_MISC1_CFG_EN_SSC),
			clk_base + plldss->params->ext_misc_reg[1]);
	ग_लिखोl_relaxed(misc2_val, clk_base + plldss->params->ext_misc_reg[2]);
	ग_लिखोl_relaxed(misc3_val, clk_base + plldss->params->ext_misc_reg[3]);
	udelay(1);
पूर्ण

अटल व्योम tegra210_plld2_set_शेषs(काष्ठा tegra_clk_pll *plld2)
अणु
	plldss_शेषs("PLL_D2", plld2, PLLD2_MISC0_DEFAULT_VALUE,
			PLLD2_MISC1_CFG_DEFAULT_VALUE,
			PLLD2_MISC2_CTRL1_DEFAULT_VALUE,
			PLLD2_MISC3_CTRL2_DEFAULT_VALUE);
पूर्ण

अटल व्योम tegra210_plldp_set_शेषs(काष्ठा tegra_clk_pll *plldp)
अणु
	plldss_शेषs("PLL_DP", plldp, PLLDP_MISC0_DEFAULT_VALUE,
			PLLDP_MISC1_CFG_DEFAULT_VALUE,
			PLLDP_MISC2_CTRL1_DEFAULT_VALUE,
			PLLDP_MISC3_CTRL2_DEFAULT_VALUE);
पूर्ण

/*
 * PLLC4
 * Base and misc0 layout is the same as PLLD2/PLLDP, but no SDM/SSC support.
 * VCO is exposed to the घड़ी tree via fixed 1/3 and 1/5 भागiders.
 */
अटल व्योम tegra210_pllc4_set_शेषs(काष्ठा tegra_clk_pll *pllc4)
अणु
	plldss_शेषs("PLL_C4", pllc4, PLLC4_MISC0_DEFAULT_VALUE, 0, 0, 0);
पूर्ण

/*
 * PLLRE
 * VCO is exposed to the घड़ी tree directly aदीर्घ with post-भागider output
 */
अटल व्योम tegra210_pllre_set_शेषs(काष्ठा tegra_clk_pll *pllre)
अणु
	u32 mask;
	u32 val = पढ़ोl_relaxed(clk_base + pllre->params->base_reg);

	pllre->params->शेषs_set = true;

	अगर (val & PLL_ENABLE) अणु
		/*
		 * PLL is ON: check अगर शेषs alपढ़ोy set, then set those
		 * that can be updated in flight.
		 */
		val &= PLLRE_BASE_DEFAULT_MASK;
		अगर (val != PLLRE_BASE_DEFAULT_VALUE) अणु
			pr_warn("pllre boot base 0x%x : expected 0x%x\n",
				val, PLLRE_BASE_DEFAULT_VALUE);
			pr_warn("(comparison mask = 0x%x)\n",
				PLLRE_BASE_DEFAULT_MASK);
			pllre->params->शेषs_set = false;
		पूर्ण

		/* Ignore lock enable */
		val = PLLRE_MISC0_DEFAULT_VALUE & (~PLLRE_MISC0_IDDQ);
		mask = PLLRE_MISC0_LOCK_ENABLE | PLLRE_MISC0_LOCK_OVERRIDE;
		_pll_misc_chk_शेष(clk_base, pllre->params, 0, val,
				~mask & PLLRE_MISC0_WRITE_MASK);

		/* The PLL करोesn't work if it's in IDDQ. */
		val = पढ़ोl_relaxed(clk_base + pllre->params->ext_misc_reg[0]);
		अगर (val & PLLRE_MISC0_IDDQ)
			pr_warn("unexpected IDDQ bit set for enabled clock\n");

		/* Enable lock detect */
		val &= ~mask;
		val |= PLLRE_MISC0_DEFAULT_VALUE & mask;
		ग_लिखोl_relaxed(val, clk_base + pllre->params->ext_misc_reg[0]);
		udelay(1);

		अगर (!pllre->params->शेषs_set)
			pr_warn("PLL_RE already enabled. Postponing set full defaults\n");

		वापस;
	पूर्ण

	/* set IDDQ, enable lock detect */
	val &= ~PLLRE_BASE_DEFAULT_MASK;
	val |= PLLRE_BASE_DEFAULT_VALUE & PLLRE_BASE_DEFAULT_MASK;
	ग_लिखोl_relaxed(val, clk_base + pllre->params->base_reg);
	ग_लिखोl_relaxed(PLLRE_MISC0_DEFAULT_VALUE,
			clk_base + pllre->params->ext_misc_reg[0]);
	udelay(1);
पूर्ण

अटल व्योम pllx_get_dyn_steps(काष्ठा clk_hw *hw, u32 *step_a, u32 *step_b)
अणु
	अचिन्हित दीर्घ input_rate;

	/* cf rate */
	अगर (!IS_ERR_OR_शून्य(hw->clk))
		input_rate = clk_hw_get_rate(clk_hw_get_parent(hw));
	अन्यथा
		input_rate = 38400000;

	input_rate /= tegra_pll_get_fixed_mभाग(hw, input_rate);

	चयन (input_rate) अणु
	हाल 12000000:
	हाल 12800000:
	हाल 13000000:
		*step_a = 0x2B;
		*step_b = 0x0B;
		वापस;
	हाल 19200000:
		*step_a = 0x12;
		*step_b = 0x08;
		वापस;
	हाल 38400000:
		*step_a = 0x04;
		*step_b = 0x05;
		वापस;
	शेष:
		pr_err("%s: Unexpected reference rate %lu\n",
			__func__, input_rate);
		BUG();
	पूर्ण
पूर्ण

अटल व्योम pllx_check_शेषs(काष्ठा tegra_clk_pll *pll)
अणु
	u32 शेष_val;

	शेष_val = PLLX_MISC0_DEFAULT_VALUE;
	/* ignore lock enable */
	_pll_misc_chk_शेष(clk_base, pll->params, 0, शेष_val,
			PLLX_MISC0_WRITE_MASK & (~PLLX_MISC0_LOCK_ENABLE));

	शेष_val = PLLX_MISC1_DEFAULT_VALUE;
	_pll_misc_chk_शेष(clk_base, pll->params, 1, शेष_val,
			PLLX_MISC1_WRITE_MASK);

	/* ignore all but control bit */
	शेष_val = PLLX_MISC2_DEFAULT_VALUE;
	_pll_misc_chk_शेष(clk_base, pll->params, 2,
			शेष_val, PLLX_MISC2_EN_DYNRAMP);

	शेष_val = PLLX_MISC3_DEFAULT_VALUE & (~PLLX_MISC3_IDDQ);
	_pll_misc_chk_शेष(clk_base, pll->params, 3, शेष_val,
			PLLX_MISC3_WRITE_MASK);

	शेष_val = PLLX_MISC4_DEFAULT_VALUE;
	_pll_misc_chk_शेष(clk_base, pll->params, 4, शेष_val,
			PLLX_MISC4_WRITE_MASK);

	शेष_val = PLLX_MISC5_DEFAULT_VALUE;
	_pll_misc_chk_शेष(clk_base, pll->params, 5, शेष_val,
			PLLX_MISC5_WRITE_MASK);
पूर्ण

अटल व्योम tegra210_pllx_set_शेषs(काष्ठा tegra_clk_pll *pllx)
अणु
	u32 val;
	u32 step_a, step_b;

	pllx->params->शेषs_set = true;

	/* Get पढ़ोy dyn ramp state machine settings */
	pllx_get_dyn_steps(&pllx->hw, &step_a, &step_b);
	val = PLLX_MISC2_DEFAULT_VALUE & (~PLLX_MISC2_DYNRAMP_STEPA_MASK) &
		(~PLLX_MISC2_DYNRAMP_STEPB_MASK);
	val |= step_a << PLLX_MISC2_DYNRAMP_STEPA_SHIFT;
	val |= step_b << PLLX_MISC2_DYNRAMP_STEPB_SHIFT;

	अगर (पढ़ोl_relaxed(clk_base + pllx->params->base_reg) & PLL_ENABLE) अणु

		/*
		 * PLL is ON: check अगर शेषs alपढ़ोy set, then set those
		 * that can be updated in flight.
		 */
		pllx_check_शेषs(pllx);

		अगर (!pllx->params->शेषs_set)
			pr_warn("PLL_X already enabled. Postponing set full defaults\n");
		/* Configure dyn ramp, disable lock override */
		ग_लिखोl_relaxed(val, clk_base + pllx->params->ext_misc_reg[2]);

		/* Enable lock detect */
		val = पढ़ोl_relaxed(clk_base + pllx->params->ext_misc_reg[0]);
		val &= ~PLLX_MISC0_LOCK_ENABLE;
		val |= PLLX_MISC0_DEFAULT_VALUE & PLLX_MISC0_LOCK_ENABLE;
		ग_लिखोl_relaxed(val, clk_base + pllx->params->ext_misc_reg[0]);
		udelay(1);

		वापस;
	पूर्ण

	/* Enable lock detect and CPU output */
	ग_लिखोl_relaxed(PLLX_MISC0_DEFAULT_VALUE, clk_base +
			pllx->params->ext_misc_reg[0]);

	/* Setup */
	ग_लिखोl_relaxed(PLLX_MISC1_DEFAULT_VALUE, clk_base +
			pllx->params->ext_misc_reg[1]);

	/* Configure dyn ramp state machine, disable lock override */
	ग_लिखोl_relaxed(val, clk_base + pllx->params->ext_misc_reg[2]);

	/* Set IDDQ */
	ग_लिखोl_relaxed(PLLX_MISC3_DEFAULT_VALUE, clk_base +
			pllx->params->ext_misc_reg[3]);

	/* Disable SDM */
	ग_लिखोl_relaxed(PLLX_MISC4_DEFAULT_VALUE, clk_base +
			pllx->params->ext_misc_reg[4]);
	ग_लिखोl_relaxed(PLLX_MISC5_DEFAULT_VALUE, clk_base +
			pllx->params->ext_misc_reg[5]);
	udelay(1);
पूर्ण

/* PLLMB */
अटल व्योम tegra210_pllmb_set_शेषs(काष्ठा tegra_clk_pll *pllmb)
अणु
	u32 mask, val = पढ़ोl_relaxed(clk_base + pllmb->params->base_reg);

	pllmb->params->शेषs_set = true;

	अगर (val & PLL_ENABLE) अणु

		/*
		 * PLL is ON: check अगर शेषs alपढ़ोy set, then set those
		 * that can be updated in flight.
		 */
		val = PLLMB_MISC1_DEFAULT_VALUE & (~PLLMB_MISC1_IDDQ);
		mask = PLLMB_MISC1_LOCK_ENABLE | PLLMB_MISC1_LOCK_OVERRIDE;
		_pll_misc_chk_शेष(clk_base, pllmb->params, 0, val,
				~mask & PLLMB_MISC1_WRITE_MASK);

		अगर (!pllmb->params->शेषs_set)
			pr_warn("PLL_MB already enabled. Postponing set full defaults\n");
		/* Enable lock detect */
		val = पढ़ोl_relaxed(clk_base + pllmb->params->ext_misc_reg[0]);
		val &= ~mask;
		val |= PLLMB_MISC1_DEFAULT_VALUE & mask;
		ग_लिखोl_relaxed(val, clk_base + pllmb->params->ext_misc_reg[0]);
		udelay(1);

		वापस;
	पूर्ण

	/* set IDDQ, enable lock detect */
	ग_लिखोl_relaxed(PLLMB_MISC1_DEFAULT_VALUE,
			clk_base + pllmb->params->ext_misc_reg[0]);
	udelay(1);
पूर्ण

/*
 * PLLP
 * VCO is exposed to the घड़ी tree directly aदीर्घ with post-भागider output.
 * Both VCO and post-भागider output rates are fixed at 408MHz and 204MHz,
 * respectively.
 */
अटल व्योम pllp_check_शेषs(काष्ठा tegra_clk_pll *pll, bool enabled)
अणु
	u32 val, mask;

	/* Ignore lock enable (will be set), make sure not in IDDQ अगर enabled */
	val = PLLP_MISC0_DEFAULT_VALUE & (~PLLP_MISC0_IDDQ);
	mask = PLLP_MISC0_LOCK_ENABLE | PLLP_MISC0_LOCK_OVERRIDE;
	अगर (!enabled)
		mask |= PLLP_MISC0_IDDQ;
	_pll_misc_chk_शेष(clk_base, pll->params, 0, val,
			~mask & PLLP_MISC0_WRITE_MASK);

	/* Ignore branch controls */
	val = PLLP_MISC1_DEFAULT_VALUE;
	mask = PLLP_MISC1_HSIO_EN | PLLP_MISC1_XUSB_EN;
	_pll_misc_chk_शेष(clk_base, pll->params, 1, val,
			~mask & PLLP_MISC1_WRITE_MASK);
पूर्ण

अटल व्योम tegra210_pllp_set_शेषs(काष्ठा tegra_clk_pll *pllp)
अणु
	u32 mask;
	u32 val = पढ़ोl_relaxed(clk_base + pllp->params->base_reg);

	pllp->params->शेषs_set = true;

	अगर (val & PLL_ENABLE) अणु

		/*
		 * PLL is ON: check अगर शेषs alपढ़ोy set, then set those
		 * that can be updated in flight.
		 */
		pllp_check_शेषs(pllp, true);
		अगर (!pllp->params->शेषs_set)
			pr_warn("PLL_P already enabled. Postponing set full defaults\n");

		/* Enable lock detect */
		val = पढ़ोl_relaxed(clk_base + pllp->params->ext_misc_reg[0]);
		mask = PLLP_MISC0_LOCK_ENABLE | PLLP_MISC0_LOCK_OVERRIDE;
		val &= ~mask;
		val |= PLLP_MISC0_DEFAULT_VALUE & mask;
		ग_लिखोl_relaxed(val, clk_base + pllp->params->ext_misc_reg[0]);
		udelay(1);

		वापस;
	पूर्ण

	/* set IDDQ, enable lock detect */
	ग_लिखोl_relaxed(PLLP_MISC0_DEFAULT_VALUE,
			clk_base + pllp->params->ext_misc_reg[0]);

	/* Preserve branch control */
	val = पढ़ोl_relaxed(clk_base + pllp->params->ext_misc_reg[1]);
	mask = PLLP_MISC1_HSIO_EN | PLLP_MISC1_XUSB_EN;
	val &= mask;
	val |= ~mask & PLLP_MISC1_DEFAULT_VALUE;
	ग_लिखोl_relaxed(val, clk_base + pllp->params->ext_misc_reg[1]);
	udelay(1);
पूर्ण

/*
 * PLLU
 * VCO is exposed to the घड़ी tree directly aदीर्घ with post-भागider output.
 * Both VCO and post-भागider output rates are fixed at 480MHz and 240MHz,
 * respectively.
 */
अटल व्योम pllu_check_शेषs(काष्ठा tegra_clk_pll_params *params,
				bool hw_control)
अणु
	u32 val, mask;

	/* Ignore lock enable (will be set) and IDDQ अगर under h/w control */
	val = PLLU_MISC0_DEFAULT_VALUE & (~PLLU_MISC0_IDDQ);
	mask = PLLU_MISC0_LOCK_ENABLE | (hw_control ? PLLU_MISC0_IDDQ : 0);
	_pll_misc_chk_शेष(clk_base, params, 0, val,
			~mask & PLLU_MISC0_WRITE_MASK);

	val = PLLU_MISC1_DEFAULT_VALUE;
	mask = PLLU_MISC1_LOCK_OVERRIDE;
	_pll_misc_chk_शेष(clk_base, params, 1, val,
			~mask & PLLU_MISC1_WRITE_MASK);
पूर्ण

अटल व्योम tegra210_pllu_set_शेषs(काष्ठा tegra_clk_pll_params *pllu)
अणु
	u32 val = पढ़ोl_relaxed(clk_base + pllu->base_reg);

	pllu->शेषs_set = true;

	अगर (val & PLL_ENABLE) अणु

		/*
		 * PLL is ON: check अगर शेषs alपढ़ोy set, then set those
		 * that can be updated in flight.
		 */
		pllu_check_शेषs(pllu, false);
		अगर (!pllu->शेषs_set)
			pr_warn("PLL_U already enabled. Postponing set full defaults\n");

		/* Enable lock detect */
		val = पढ़ोl_relaxed(clk_base + pllu->ext_misc_reg[0]);
		val &= ~PLLU_MISC0_LOCK_ENABLE;
		val |= PLLU_MISC0_DEFAULT_VALUE & PLLU_MISC0_LOCK_ENABLE;
		ग_लिखोl_relaxed(val, clk_base + pllu->ext_misc_reg[0]);

		val = पढ़ोl_relaxed(clk_base + pllu->ext_misc_reg[1]);
		val &= ~PLLU_MISC1_LOCK_OVERRIDE;
		val |= PLLU_MISC1_DEFAULT_VALUE & PLLU_MISC1_LOCK_OVERRIDE;
		ग_लिखोl_relaxed(val, clk_base + pllu->ext_misc_reg[1]);
		udelay(1);

		वापस;
	पूर्ण

	/* set IDDQ, enable lock detect */
	ग_लिखोl_relaxed(PLLU_MISC0_DEFAULT_VALUE,
			clk_base + pllu->ext_misc_reg[0]);
	ग_लिखोl_relaxed(PLLU_MISC1_DEFAULT_VALUE,
			clk_base + pllu->ext_misc_reg[1]);
	udelay(1);
पूर्ण

#घोषणा mask(w) ((1 << (w)) - 1)
#घोषणा भागm_mask(p) mask(p->params->भाग_nmp->भागm_width)
#घोषणा भागn_mask(p) mask(p->params->भाग_nmp->भागn_width)
#घोषणा भागp_mask(p) (p->params->flags & TEGRA_PLLU ? PLLU_POST_DIVP_MASK :\
		      mask(p->params->भाग_nmp->भागp_width))

#घोषणा भागm_shअगरt(p) ((p)->params->भाग_nmp->भागm_shअगरt)
#घोषणा भागn_shअगरt(p) ((p)->params->भाग_nmp->भागn_shअगरt)
#घोषणा भागp_shअगरt(p) ((p)->params->भाग_nmp->भागp_shअगरt)

#घोषणा भागm_mask_shअगरted(p) (भागm_mask(p) << भागm_shअगरt(p))
#घोषणा भागn_mask_shअगरted(p) (भागn_mask(p) << भागn_shअगरt(p))
#घोषणा भागp_mask_shअगरted(p) (भागp_mask(p) << भागp_shअगरt(p))

#घोषणा PLL_LOCKDET_DELAY 2	/* Lock detection safety delays */
अटल पूर्णांक tegra210_रुको_क्रम_mask(काष्ठा tegra_clk_pll *pll,
				  u32 reg, u32 mask)
अणु
	पूर्णांक i;
	u32 val = 0;

	क्रम (i = 0; i < pll->params->lock_delay / PLL_LOCKDET_DELAY + 1; i++) अणु
		udelay(PLL_LOCKDET_DELAY);
		val = पढ़ोl_relaxed(clk_base + reg);
		अगर ((val & mask) == mask) अणु
			udelay(PLL_LOCKDET_DELAY);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra210_pllx_dyn_ramp(काष्ठा tegra_clk_pll *pllx,
		काष्ठा tegra_clk_pll_freq_table *cfg)
अणु
	u32 val, base, nभाग_new_mask;

	nभाग_new_mask = (भागn_mask(pllx) >> pllx->params->भाग_nmp->भागn_shअगरt)
			 << PLLX_MISC2_NDIV_NEW_SHIFT;

	val = पढ़ोl_relaxed(clk_base + pllx->params->ext_misc_reg[2]);
	val &= (~nभाग_new_mask);
	val |= cfg->n << PLLX_MISC2_NDIV_NEW_SHIFT;
	ग_लिखोl_relaxed(val, clk_base + pllx->params->ext_misc_reg[2]);
	udelay(1);

	val = पढ़ोl_relaxed(clk_base + pllx->params->ext_misc_reg[2]);
	val |= PLLX_MISC2_EN_DYNRAMP;
	ग_लिखोl_relaxed(val, clk_base + pllx->params->ext_misc_reg[2]);
	udelay(1);

	tegra210_रुको_क्रम_mask(pllx, pllx->params->ext_misc_reg[2],
			       PLLX_MISC2_DYNRAMP_DONE);

	base = पढ़ोl_relaxed(clk_base + pllx->params->base_reg) &
		(~भागn_mask_shअगरted(pllx));
	base |= cfg->n << pllx->params->भाग_nmp->भागn_shअगरt;
	ग_लिखोl_relaxed(base, clk_base + pllx->params->base_reg);
	udelay(1);

	val &= ~PLLX_MISC2_EN_DYNRAMP;
	ग_लिखोl_relaxed(val, clk_base + pllx->params->ext_misc_reg[2]);
	udelay(1);

	pr_debug("%s: dynamic ramp to m = %u n = %u p = %u, Fout = %lu kHz\n",
		 __clk_get_name(pllx->hw.clk), cfg->m, cfg->n, cfg->p,
		 cfg->input_rate / cfg->m * cfg->n /
		 pllx->params->pभाग_प्रकारohw[cfg->p].pभाग / 1000);

	वापस 0;
पूर्ण

/*
 * Common configuration क्रम PLLs with fixed input भागider policy:
 * - always set fixed M-value based on the reference rate
 * - always set P-value value 1:1 क्रम output rates above VCO minimum, and
 *   choose minimum necessary P-value क्रम output rates below VCO maximum
 * - calculate N-value based on selected M and P
 * - calculate SDM_DIN fractional part
 */
अटल पूर्णांक tegra210_pll_fixed_mभाग_cfg(काष्ठा clk_hw *hw,
			       काष्ठा tegra_clk_pll_freq_table *cfg,
			       अचिन्हित दीर्घ rate, अचिन्हित दीर्घ input_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_params *params = pll->params;
	पूर्णांक p;
	अचिन्हित दीर्घ cf, p_rate;
	u32 pभाग;

	अगर (!rate)
		वापस -EINVAL;

	अगर (!(params->flags & TEGRA_PLL_VCO_OUT)) अणु
		p = DIV_ROUND_UP(params->vco_min, rate);
		p = params->round_p_to_pभाग(p, &pभाग);
	पूर्ण अन्यथा अणु
		p = rate >= params->vco_min ? 1 : -EINVAL;
	पूर्ण

	अगर (p < 0)
		वापस -EINVAL;

	cfg->m = tegra_pll_get_fixed_mभाग(hw, input_rate);
	cfg->p = p;

	/* Store P as HW value, as that is what is expected */
	cfg->p = tegra_pll_p_भाग_प्रकारo_hw(pll, cfg->p);

	p_rate = rate * p;
	अगर (p_rate > params->vco_max)
		p_rate = params->vco_max;
	cf = input_rate / cfg->m;
	cfg->n = p_rate / cf;

	cfg->sdm_data = 0;
	cfg->output_rate = input_rate;
	अगर (params->sdm_ctrl_reg) अणु
		अचिन्हित दीर्घ rem = p_rate - cf * cfg->n;
		/* If ssc is enabled SDM enabled as well, even क्रम पूर्णांकeger n */
		अगर (rem || params->ssc_ctrl_reg) अणु
			u64 s = rem * PLL_SDM_COEFF;

			करो_भाग(s, cf);
			s -= PLL_SDM_COEFF / 2;
			cfg->sdm_data = sdin_din_to_data(s);
		पूर्ण
		cfg->output_rate *= sdin_get_n_eff(cfg);
		cfg->output_rate /= p * cfg->m * PLL_SDM_COEFF;
	पूर्ण अन्यथा अणु
		cfg->output_rate *= cfg->n;
		cfg->output_rate /= p * cfg->m;
	पूर्ण

	cfg->input_rate = input_rate;

	वापस 0;
पूर्ण

/*
 * clk_pll_set_gain - set gain to m, n to calculate correct VCO rate
 *
 * @cfg: काष्ठा tegra_clk_pll_freq_table * cfg
 *
 * For Normal mode:
 *     Fvco = Fref * NDIV / MDIV
 *
 * For fractional mode:
 *     Fvco = Fref * (NDIV + 0.5 + SDM_DIN / PLL_SDM_COEFF) / MDIV
 */
अटल व्योम tegra210_clk_pll_set_gain(काष्ठा tegra_clk_pll_freq_table *cfg)
अणु
	cfg->n = sdin_get_n_eff(cfg);
	cfg->m *= PLL_SDM_COEFF;
पूर्ण

अटल अचिन्हित दीर्घ
tegra210_clk_adjust_vco_min(काष्ठा tegra_clk_pll_params *params,
			    अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ vco_min = params->vco_min;

	params->vco_min += DIV_ROUND_UP(parent_rate, PLL_SDM_COEFF);
	vco_min = min(vco_min, params->vco_min);

	वापस vco_min;
पूर्ण

अटल काष्ठा भाग_nmp pllx_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 5,
पूर्ण;
/*
 * PLL post भागider maps - two types: quasi-linear and exponential
 * post भागider.
 */
#घोषणा PLL_QLIN_PDIV_MAX	16
अटल स्थिर काष्ठा pभाग_map pll_qlin_pभाग_प्रकारo_hw[] = अणु
	अणु .pभाग =  1, .hw_val =  0 पूर्ण,
	अणु .pभाग =  2, .hw_val =  1 पूर्ण,
	अणु .pभाग =  3, .hw_val =  2 पूर्ण,
	अणु .pभाग =  4, .hw_val =  3 पूर्ण,
	अणु .pभाग =  5, .hw_val =  4 पूर्ण,
	अणु .pभाग =  6, .hw_val =  5 पूर्ण,
	अणु .pभाग =  8, .hw_val =  6 पूर्ण,
	अणु .pभाग =  9, .hw_val =  7 पूर्ण,
	अणु .pभाग = 10, .hw_val =  8 पूर्ण,
	अणु .pभाग = 12, .hw_val =  9 पूर्ण,
	अणु .pभाग = 15, .hw_val = 10 पूर्ण,
	अणु .pभाग = 16, .hw_val = 11 पूर्ण,
	अणु .pभाग = 18, .hw_val = 12 पूर्ण,
	अणु .pभाग = 20, .hw_val = 13 पूर्ण,
	अणु .pभाग = 24, .hw_val = 14 पूर्ण,
	अणु .pभाग = 30, .hw_val = 15 पूर्ण,
	अणु .pभाग = 32, .hw_val = 16 पूर्ण,
पूर्ण;

अटल u32 pll_qlin_p_to_pभाग(u32 p, u32 *pभाग)
अणु
	पूर्णांक i;

	अगर (p) अणु
		क्रम (i = 0; i <= PLL_QLIN_PDIV_MAX; i++) अणु
			अगर (p <= pll_qlin_pभाग_प्रकारo_hw[i].pभाग) अणु
				अगर (pभाग)
					*pभाग = i;
				वापस pll_qlin_pभाग_प्रकारo_hw[i].pभाग;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

#घोषणा PLL_EXPO_PDIV_MAX	7
अटल स्थिर काष्ठा pभाग_map pll_expo_pभाग_प्रकारo_hw[] = अणु
	अणु .pभाग =   1, .hw_val = 0 पूर्ण,
	अणु .pभाग =   2, .hw_val = 1 पूर्ण,
	अणु .pभाग =   4, .hw_val = 2 पूर्ण,
	अणु .pभाग =   8, .hw_val = 3 पूर्ण,
	अणु .pभाग =  16, .hw_val = 4 पूर्ण,
	अणु .pभाग =  32, .hw_val = 5 पूर्ण,
	अणु .pभाग =  64, .hw_val = 6 पूर्ण,
	अणु .pभाग = 128, .hw_val = 7 पूर्ण,
पूर्ण;

अटल u32 pll_expo_p_to_pभाग(u32 p, u32 *pभाग)
अणु
	अगर (p) अणु
		u32 i = fls(p);

		अगर (i == ffs(p))
			i--;

		अगर (i <= PLL_EXPO_PDIV_MAX) अणु
			अगर (pभाग)
				*pभाग = i;
			वापस 1 << i;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल काष्ठा tegra_clk_pll_freq_table pll_x_freq_table[] = अणु
	/* 1 GHz */
	अणु 12000000, 1000000000, 166, 1, 2, 0 पूर्ण, /* actual: 996.0 MHz */
	अणु 13000000, 1000000000, 153, 1, 2, 0 पूर्ण, /* actual: 994.0 MHz */
	अणु 38400000, 1000000000, 156, 3, 2, 0 पूर्ण, /* actual: 998.4 MHz */
	अणु        0,          0,   0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_x_params = अणु
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 1350000000,
	.vco_max = 3000000000UL,
	.base_reg = PLLX_BASE,
	.misc_reg = PLLX_MISC0,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLL_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.ext_misc_reg[0] = PLLX_MISC0,
	.ext_misc_reg[1] = PLLX_MISC1,
	.ext_misc_reg[2] = PLLX_MISC2,
	.ext_misc_reg[3] = PLLX_MISC3,
	.ext_misc_reg[4] = PLLX_MISC4,
	.ext_misc_reg[5] = PLLX_MISC5,
	.iddq_reg = PLLX_MISC3,
	.iddq_bit_idx = PLLXP_IDDQ_BIT,
	.max_p = PLL_QLIN_PDIV_MAX,
	.mभाग_शेष = 2,
	.dyn_ramp_reg = PLLX_MISC2,
	.stepa_shअगरt = 16,
	.stepb_shअगरt = 24,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.भाग_nmp = &pllx_nmp,
	.freq_table = pll_x_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
	.dyn_ramp = tegra210_pllx_dyn_ramp,
	.set_शेषs = tegra210_pllx_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा भाग_nmp pllc_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 10,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 5,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_cx_freq_table[] = अणु
	अणु 12000000, 510000000, 85, 1, 2, 0 पूर्ण,
	अणु 13000000, 510000000, 78, 1, 2, 0 पूर्ण, /* actual: 507.0 MHz */
	अणु 38400000, 510000000, 79, 3, 2, 0 पूर्ण, /* actual: 505.6 MHz */
	अणु        0,         0,  0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_c_params = अणु
	.input_min = 12000000,
	.input_max = 700000000,
	.cf_min = 12000000,
	.cf_max = 50000000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLC_BASE,
	.misc_reg = PLLC_MISC0,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 300,
	.iddq_reg = PLLC_MISC1,
	.iddq_bit_idx = PLLCX_IDDQ_BIT,
	.reset_reg = PLLC_MISC0,
	.reset_bit_idx = PLLCX_RESET_BIT,
	.max_p = PLL_QLIN_PDIV_MAX,
	.ext_misc_reg[0] = PLLC_MISC0,
	.ext_misc_reg[1] = PLLC_MISC1,
	.ext_misc_reg[2] = PLLC_MISC2,
	.ext_misc_reg[3] = PLLC_MISC3,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.mभाग_शेष = 3,
	.भाग_nmp = &pllc_nmp,
	.freq_table = pll_cx_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
	.set_शेषs = _pllc_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा भाग_nmp pllcx_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 10,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 5,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_c2_params = अणु
	.input_min = 12000000,
	.input_max = 700000000,
	.cf_min = 12000000,
	.cf_max = 50000000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLC2_BASE,
	.misc_reg = PLLC2_MISC0,
	.iddq_reg = PLLC2_MISC1,
	.iddq_bit_idx = PLLCX_IDDQ_BIT,
	.reset_reg = PLLC2_MISC0,
	.reset_bit_idx = PLLCX_RESET_BIT,
	.lock_mask = PLLCX_BASE_LOCK,
	.lock_delay = 300,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.mभाग_शेष = 3,
	.भाग_nmp = &pllcx_nmp,
	.max_p = PLL_QLIN_PDIV_MAX,
	.ext_misc_reg[0] = PLLC2_MISC0,
	.ext_misc_reg[1] = PLLC2_MISC1,
	.ext_misc_reg[2] = PLLC2_MISC2,
	.ext_misc_reg[3] = PLLC2_MISC3,
	.freq_table = pll_cx_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
	.set_शेषs = _pllc2_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_c3_params = अणु
	.input_min = 12000000,
	.input_max = 700000000,
	.cf_min = 12000000,
	.cf_max = 50000000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLC3_BASE,
	.misc_reg = PLLC3_MISC0,
	.lock_mask = PLLCX_BASE_LOCK,
	.lock_delay = 300,
	.iddq_reg = PLLC3_MISC1,
	.iddq_bit_idx = PLLCX_IDDQ_BIT,
	.reset_reg = PLLC3_MISC0,
	.reset_bit_idx = PLLCX_RESET_BIT,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.mभाग_शेष = 3,
	.भाग_nmp = &pllcx_nmp,
	.max_p = PLL_QLIN_PDIV_MAX,
	.ext_misc_reg[0] = PLLC3_MISC0,
	.ext_misc_reg[1] = PLLC3_MISC1,
	.ext_misc_reg[2] = PLLC3_MISC2,
	.ext_misc_reg[3] = PLLC3_MISC3,
	.freq_table = pll_cx_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
	.set_शेषs = _pllc3_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा भाग_nmp pllss_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 19,
	.भागp_width = 5,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_c4_vco_freq_table[] = अणु
	अणु 12000000, 600000000, 50, 1, 1, 0 पूर्ण,
	अणु 13000000, 600000000, 46, 1, 1, 0 पूर्ण, /* actual: 598.0 MHz */
	अणु 38400000, 600000000, 62, 4, 1, 0 पूर्ण, /* actual: 595.2 MHz */
	अणु        0,         0,  0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable pll_vco_post_भाग_प्रकारable[] = अणु
	अणु .val =  0, .भाग =  1 पूर्ण,
	अणु .val =  1, .भाग =  2 पूर्ण,
	अणु .val =  2, .भाग =  3 पूर्ण,
	अणु .val =  3, .भाग =  4 पूर्ण,
	अणु .val =  4, .भाग =  5 पूर्ण,
	अणु .val =  5, .भाग =  6 पूर्ण,
	अणु .val =  6, .भाग =  8 पूर्ण,
	अणु .val =  7, .भाग = 10 पूर्ण,
	अणु .val =  8, .भाग = 12 पूर्ण,
	अणु .val =  9, .भाग = 16 पूर्ण,
	अणु .val = 10, .भाग = 12 पूर्ण,
	अणु .val = 11, .भाग = 16 पूर्ण,
	अणु .val = 12, .भाग = 20 पूर्ण,
	अणु .val = 13, .भाग = 24 पूर्ण,
	अणु .val = 14, .भाग = 32 पूर्ण,
	अणु .val =  0, .भाग =  0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_c4_vco_params = अणु
	.input_min = 9600000,
	.input_max = 800000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 500000000,
	.vco_max = 1080000000,
	.base_reg = PLLC4_BASE,
	.misc_reg = PLLC4_MISC0,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 300,
	.max_p = PLL_QLIN_PDIV_MAX,
	.ext_misc_reg[0] = PLLC4_MISC0,
	.iddq_reg = PLLC4_BASE,
	.iddq_bit_idx = PLLSS_IDDQ_BIT,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.mभाग_शेष = 3,
	.भाग_nmp = &pllss_nmp,
	.freq_table = pll_c4_vco_freq_table,
	.set_शेषs = tegra210_pllc4_set_शेषs,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_VCO_OUT,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_m_freq_table[] = अणु
	अणु 12000000,  800000000,  66, 1, 1, 0 पूर्ण, /* actual: 792.0 MHz */
	अणु 13000000,  800000000,  61, 1, 1, 0 पूर्ण, /* actual: 793.0 MHz */
	अणु 38400000,  297600000,  93, 4, 3, 0 पूर्ण,
	अणु 38400000,  400000000, 125, 4, 3, 0 पूर्ण,
	अणु 38400000,  532800000, 111, 4, 2, 0 पूर्ण,
	अणु 38400000,  665600000, 104, 3, 2, 0 पूर्ण,
	अणु 38400000,  800000000, 125, 3, 2, 0 पूर्ण,
	अणु 38400000,  931200000,  97, 4, 1, 0 पूर्ण,
	अणु 38400000, 1065600000, 111, 4, 1, 0 पूर्ण,
	अणु 38400000, 1200000000, 125, 4, 1, 0 पूर्ण,
	अणु 38400000, 1331200000, 104, 3, 1, 0 पूर्ण,
	अणु 38400000, 1459200000,  76, 2, 1, 0 पूर्ण,
	अणु 38400000, 1600000000, 125, 3, 1, 0 पूर्ण,
	अणु        0,          0,   0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा भाग_nmp pllm_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.override_भागm_shअगरt = 0,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.override_भागn_shअगरt = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 5,
	.override_भागp_shअगरt = 27,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_m_params = अणु
	.input_min = 9600000,
	.input_max = 500000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 800000000,
	.vco_max = 1866000000,
	.base_reg = PLLM_BASE,
	.misc_reg = PLLM_MISC2,
	.lock_mask = PLL_BASE_LOCK,
	.lock_enable_bit_idx = PLLM_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.iddq_reg = PLLM_MISC2,
	.iddq_bit_idx = PLLM_IDDQ_BIT,
	.max_p = PLL_QLIN_PDIV_MAX,
	.ext_misc_reg[0] = PLLM_MISC2,
	.ext_misc_reg[1] = PLLM_MISC1,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.भाग_nmp = &pllm_nmp,
	.pmc_भागnm_reg = PMC_PLLM_WB0_OVERRIDE,
	.pmc_भागp_reg = PMC_PLLM_WB0_OVERRIDE_2,
	.freq_table = pll_m_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_HAS_LOCK_ENABLE,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_mb_params = अणु
	.input_min = 9600000,
	.input_max = 500000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 800000000,
	.vco_max = 1866000000,
	.base_reg = PLLMB_BASE,
	.misc_reg = PLLMB_MISC1,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 300,
	.iddq_reg = PLLMB_MISC1,
	.iddq_bit_idx = PLLMB_IDDQ_BIT,
	.max_p = PLL_QLIN_PDIV_MAX,
	.ext_misc_reg[0] = PLLMB_MISC1,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.भाग_nmp = &pllm_nmp,
	.freq_table = pll_m_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
	.set_शेषs = tegra210_pllmb_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;


अटल काष्ठा tegra_clk_pll_freq_table pll_e_freq_table[] = अणु
	/* PLLE special हाल: use cpcon field to store cml भागider value */
	अणु 672000000, 100000000, 125, 42, 0, 13 पूर्ण,
	अणु 624000000, 100000000, 125, 39, 0, 13 पूर्ण,
	अणु 336000000, 100000000, 125, 21, 0, 13 पूर्ण,
	अणु 312000000, 100000000, 200, 26, 0, 14 पूर्ण,
	अणु  38400000, 100000000, 125,  2, 0, 14 पूर्ण,
	अणु  12000000, 100000000, 200,  1, 0, 14 पूर्ण,
	अणु         0,         0,   0,  0, 0,  0 पूर्ण,
पूर्ण;

अटल काष्ठा भाग_nmp plle_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 24,
	.भागp_width = 5,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_e_params = अणु
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 1600000000,
	.vco_max = 2500000000U,
	.base_reg = PLLE_BASE,
	.misc_reg = PLLE_MISC0,
	.aux_reg = PLLE_AUX,
	.lock_mask = PLLE_MISC_LOCK,
	.lock_enable_bit_idx = PLLE_MISC_LOCK_ENABLE,
	.lock_delay = 300,
	.भाग_nmp = &plle_nmp,
	.freq_table = pll_e_freq_table,
	.flags = TEGRA_PLL_FIXED | TEGRA_PLL_LOCK_MISC | TEGRA_PLL_USE_LOCK |
		 TEGRA_PLL_HAS_LOCK_ENABLE,
	.fixed_rate = 100000000,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_re_vco_freq_table[] = अणु
	अणु 12000000, 672000000, 56, 1, 1, 0 पूर्ण,
	अणु 13000000, 672000000, 51, 1, 1, 0 पूर्ण, /* actual: 663.0 MHz */
	अणु 38400000, 672000000, 70, 4, 1, 0 पूर्ण,
	अणु        0,         0,  0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा भाग_nmp pllre_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 16,
	.भागp_width = 5,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_re_vco_params = अणु
	.input_min = 9600000,
	.input_max = 800000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 350000000,
	.vco_max = 700000000,
	.base_reg = PLLRE_BASE,
	.misc_reg = PLLRE_MISC0,
	.lock_mask = PLLRE_MISC_LOCK,
	.lock_delay = 300,
	.max_p = PLL_QLIN_PDIV_MAX,
	.ext_misc_reg[0] = PLLRE_MISC0,
	.iddq_reg = PLLRE_MISC0,
	.iddq_bit_idx = PLLRE_IDDQ_BIT,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.भाग_nmp = &pllre_nmp,
	.freq_table = pll_re_vco_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_PLL_LOCK_MISC | TEGRA_PLL_VCO_OUT,
	.set_शेषs = tegra210_pllre_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा भाग_nmp pllp_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 10,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 5,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_p_freq_table[] = अणु
	अणु 12000000, 408000000, 34, 1, 1, 0 पूर्ण,
	अणु 38400000, 408000000, 85, 8, 1, 0 पूर्ण, /* cf = 4.8MHz, allowed exception */
	अणु        0,         0,  0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_p_params = अणु
	.input_min = 9600000,
	.input_max = 800000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 350000000,
	.vco_max = 700000000,
	.base_reg = PLLP_BASE,
	.misc_reg = PLLP_MISC0,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 300,
	.iddq_reg = PLLP_MISC0,
	.iddq_bit_idx = PLLXP_IDDQ_BIT,
	.ext_misc_reg[0] = PLLP_MISC0,
	.ext_misc_reg[1] = PLLP_MISC1,
	.भाग_nmp = &pllp_nmp,
	.freq_table = pll_p_freq_table,
	.fixed_rate = 408000000,
	.flags = TEGRA_PLL_FIXED | TEGRA_PLL_USE_LOCK | TEGRA_PLL_VCO_OUT,
	.set_शेषs = tegra210_pllp_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_a1_params = अणु
	.input_min = 12000000,
	.input_max = 700000000,
	.cf_min = 12000000,
	.cf_max = 50000000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_reg = PLLA1_BASE,
	.misc_reg = PLLA1_MISC0,
	.lock_mask = PLLCX_BASE_LOCK,
	.lock_delay = 300,
	.iddq_reg = PLLA1_MISC1,
	.iddq_bit_idx = PLLCX_IDDQ_BIT,
	.reset_reg = PLLA1_MISC0,
	.reset_bit_idx = PLLCX_RESET_BIT,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.भाग_nmp = &pllc_nmp,
	.ext_misc_reg[0] = PLLA1_MISC0,
	.ext_misc_reg[1] = PLLA1_MISC1,
	.ext_misc_reg[2] = PLLA1_MISC2,
	.ext_misc_reg[3] = PLLA1_MISC3,
	.freq_table = pll_cx_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
	.set_शेषs = _plla1_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
पूर्ण;

अटल काष्ठा भाग_nmp plla_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 5,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_a_freq_table[] = अणु
	अणु 12000000, 282240000, 47, 1, 2, 1, 0xf148 पूर्ण, /* actual: 282240234 */
	अणु 12000000, 368640000, 61, 1, 2, 1, 0xfe15 पूर्ण, /* actual: 368640381 */
	अणु 12000000, 240000000, 60, 1, 3, 1,      0 पूर्ण,
	अणु 13000000, 282240000, 43, 1, 2, 1, 0xfd7d पूर्ण, /* actual: 282239807 */
	अणु 13000000, 368640000, 56, 1, 2, 1, 0x06d8 पूर्ण, /* actual: 368640137 */
	अणु 13000000, 240000000, 55, 1, 3, 1,      0 पूर्ण, /* actual: 238.3 MHz */
	अणु 38400000, 282240000, 44, 3, 2, 1, 0xf333 पूर्ण, /* actual: 282239844 */
	अणु 38400000, 368640000, 57, 3, 2, 1, 0x0333 पूर्ण, /* actual: 368639844 */
	अणु 38400000, 240000000, 75, 3, 3, 1,      0 पूर्ण,
	अणु        0,         0,  0, 0, 0, 0,      0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_a_params = अणु
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 19200000,
	.vco_min = 500000000,
	.vco_max = 1000000000,
	.base_reg = PLLA_BASE,
	.misc_reg = PLLA_MISC0,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 300,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.iddq_reg = PLLA_BASE,
	.iddq_bit_idx = PLLA_IDDQ_BIT,
	.भाग_nmp = &plla_nmp,
	.sdm_din_reg = PLLA_MISC1,
	.sdm_din_mask = PLLA_SDM_DIN_MASK,
	.sdm_ctrl_reg = PLLA_MISC2,
	.sdm_ctrl_en_mask = PLLA_SDM_EN_MASK,
	.ext_misc_reg[0] = PLLA_MISC0,
	.ext_misc_reg[1] = PLLA_MISC1,
	.ext_misc_reg[2] = PLLA_MISC2,
	.freq_table = pll_a_freq_table,
	.flags = TEGRA_PLL_USE_LOCK | TEGRA_MDIV_NEW,
	.set_शेषs = tegra210_plla_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
	.set_gain = tegra210_clk_pll_set_gain,
	.adjust_vco = tegra210_clk_adjust_vco_min,
पूर्ण;

अटल काष्ठा भाग_nmp plld_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 11,
	.भागn_width = 8,
	.भागp_shअगरt = 20,
	.भागp_width = 3,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_d_freq_table[] = अणु
	अणु 12000000, 594000000, 99, 1, 2, 0,      0 पूर्ण,
	अणु 13000000, 594000000, 91, 1, 2, 0, 0xfc4f पूर्ण, /* actual: 594000183 */
	अणु 38400000, 594000000, 30, 1, 2, 0, 0x0e00 पूर्ण,
	अणु        0,         0,  0, 0, 0, 0,      0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_d_params = अणु
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 750000000,
	.vco_max = 1500000000,
	.base_reg = PLLD_BASE,
	.misc_reg = PLLD_MISC0,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 1000,
	.iddq_reg = PLLD_MISC0,
	.iddq_bit_idx = PLLD_IDDQ_BIT,
	.round_p_to_pभाग = pll_expo_p_to_pभाग,
	.pभाग_प्रकारohw = pll_expo_pभाग_प्रकारo_hw,
	.भाग_nmp = &plld_nmp,
	.sdm_din_reg = PLLD_MISC0,
	.sdm_din_mask = PLLA_SDM_DIN_MASK,
	.sdm_ctrl_reg = PLLD_MISC0,
	.sdm_ctrl_en_mask = PLLD_SDM_EN_MASK,
	.ext_misc_reg[0] = PLLD_MISC0,
	.ext_misc_reg[1] = PLLD_MISC1,
	.freq_table = pll_d_freq_table,
	.flags = TEGRA_PLL_USE_LOCK,
	.mभाग_शेष = 1,
	.set_शेषs = tegra210_plld_set_शेषs,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
	.set_gain = tegra210_clk_pll_set_gain,
	.adjust_vco = tegra210_clk_adjust_vco_min,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table tegra210_pll_d2_freq_table[] = अणु
	अणु 12000000, 594000000, 99, 1, 2, 0, 0xf000 पूर्ण,
	अणु 13000000, 594000000, 91, 1, 2, 0, 0xfc4f पूर्ण, /* actual: 594000183 */
	अणु 38400000, 594000000, 30, 1, 2, 0, 0x0e00 पूर्ण,
	अणु        0,         0,  0, 0, 0, 0,      0 पूर्ण,
पूर्ण;

/* s/w policy, always tegra_pll_ref */
अटल काष्ठा tegra_clk_pll_params pll_d2_params = अणु
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 750000000,
	.vco_max = 1500000000,
	.base_reg = PLLD2_BASE,
	.misc_reg = PLLD2_MISC0,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 300,
	.iddq_reg = PLLD2_BASE,
	.iddq_bit_idx = PLLSS_IDDQ_BIT,
	.sdm_din_reg = PLLD2_MISC3,
	.sdm_din_mask = PLLA_SDM_DIN_MASK,
	.sdm_ctrl_reg = PLLD2_MISC1,
	.sdm_ctrl_en_mask = PLLD2_SDM_EN_MASK,
	/* disable spपढ़ो-spectrum क्रम pll_d2 */
	.ssc_ctrl_reg = 0,
	.ssc_ctrl_en_mask = 0,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.भाग_nmp = &pllss_nmp,
	.ext_misc_reg[0] = PLLD2_MISC0,
	.ext_misc_reg[1] = PLLD2_MISC1,
	.ext_misc_reg[2] = PLLD2_MISC2,
	.ext_misc_reg[3] = PLLD2_MISC3,
	.max_p = PLL_QLIN_PDIV_MAX,
	.mभाग_शेष = 1,
	.freq_table = tegra210_pll_d2_freq_table,
	.set_शेषs = tegra210_plld2_set_शेषs,
	.flags = TEGRA_PLL_USE_LOCK,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
	.set_gain = tegra210_clk_pll_set_gain,
	.adjust_vco = tegra210_clk_adjust_vco_min,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_dp_freq_table[] = अणु
	अणु 12000000, 270000000, 90, 1, 4, 0, 0xf000 पूर्ण,
	अणु 13000000, 270000000, 83, 1, 4, 0, 0xf000 पूर्ण, /* actual: 269.8 MHz */
	अणु 38400000, 270000000, 28, 1, 4, 0, 0xf400 पूर्ण,
	अणु        0,         0,  0, 0, 0, 0,      0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_dp_params = अणु
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 750000000,
	.vco_max = 1500000000,
	.base_reg = PLLDP_BASE,
	.misc_reg = PLLDP_MISC,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 300,
	.iddq_reg = PLLDP_BASE,
	.iddq_bit_idx = PLLSS_IDDQ_BIT,
	.sdm_din_reg = PLLDP_SS_CTRL2,
	.sdm_din_mask = PLLA_SDM_DIN_MASK,
	.sdm_ctrl_reg = PLLDP_SS_CFG,
	.sdm_ctrl_en_mask = PLLDP_SDM_EN_MASK,
	.ssc_ctrl_reg = PLLDP_SS_CFG,
	.ssc_ctrl_en_mask = PLLDP_SSC_EN_MASK,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.भाग_nmp = &pllss_nmp,
	.ext_misc_reg[0] = PLLDP_MISC,
	.ext_misc_reg[1] = PLLDP_SS_CFG,
	.ext_misc_reg[2] = PLLDP_SS_CTRL1,
	.ext_misc_reg[3] = PLLDP_SS_CTRL2,
	.max_p = PLL_QLIN_PDIV_MAX,
	.mभाग_शेष = 1,
	.freq_table = pll_dp_freq_table,
	.set_शेषs = tegra210_plldp_set_शेषs,
	.flags = TEGRA_PLL_USE_LOCK,
	.calc_rate = tegra210_pll_fixed_mभाग_cfg,
	.set_gain = tegra210_clk_pll_set_gain,
	.adjust_vco = tegra210_clk_adjust_vco_min,
पूर्ण;

अटल काष्ठा भाग_nmp pllu_nmp = अणु
	.भागm_shअगरt = 0,
	.भागm_width = 8,
	.भागn_shअगरt = 8,
	.भागn_width = 8,
	.भागp_shअगरt = 16,
	.भागp_width = 5,
पूर्ण;

अटल काष्ठा tegra_clk_pll_freq_table pll_u_freq_table[] = अणु
	अणु 12000000, 480000000, 40, 1, 1, 0 पूर्ण,
	अणु 13000000, 480000000, 36, 1, 1, 0 पूर्ण, /* actual: 468.0 MHz */
	अणु 38400000, 480000000, 25, 2, 1, 0 पूर्ण,
	अणु        0,         0,  0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_pll_params pll_u_vco_params = अणु
	.input_min = 9600000,
	.input_max = 800000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 350000000,
	.vco_max = 700000000,
	.base_reg = PLLU_BASE,
	.misc_reg = PLLU_MISC0,
	.lock_mask = PLL_BASE_LOCK,
	.lock_delay = 1000,
	.iddq_reg = PLLU_MISC0,
	.iddq_bit_idx = PLLU_IDDQ_BIT,
	.ext_misc_reg[0] = PLLU_MISC0,
	.ext_misc_reg[1] = PLLU_MISC1,
	.round_p_to_pभाग = pll_qlin_p_to_pभाग,
	.pभाग_प्रकारohw = pll_qlin_pभाग_प्रकारo_hw,
	.भाग_nmp = &pllu_nmp,
	.freq_table = pll_u_freq_table,
	.flags = TEGRA_PLLU | TEGRA_PLL_USE_LOCK | TEGRA_PLL_VCO_OUT,
पूर्ण;

काष्ठा uपंचांगi_clk_param अणु
	/* Oscillator Frequency in KHz */
	u32 osc_frequency;
	/* UTMIP PLL Enable Delay Count  */
	u8 enable_delay_count;
	/* UTMIP PLL Stable count */
	u16 stable_count;
	/*  UTMIP PLL Active delay count */
	u8 active_delay_count;
	/* UTMIP PLL Xtal frequency count */
	u16 xtal_freq_count;
पूर्ण;

अटल स्थिर काष्ठा uपंचांगi_clk_param uपंचांगi_parameters[] = अणु
	अणु
		.osc_frequency = 38400000, .enable_delay_count = 0x0,
		.stable_count = 0x0, .active_delay_count = 0x6,
		.xtal_freq_count = 0x80
	पूर्ण, अणु
		.osc_frequency = 13000000, .enable_delay_count = 0x02,
		.stable_count = 0x33, .active_delay_count = 0x05,
		.xtal_freq_count = 0x7f
	पूर्ण, अणु
		.osc_frequency = 19200000, .enable_delay_count = 0x03,
		.stable_count = 0x4b, .active_delay_count = 0x06,
		.xtal_freq_count = 0xbb
	पूर्ण, अणु
		.osc_frequency = 12000000, .enable_delay_count = 0x02,
		.stable_count = 0x2f, .active_delay_count = 0x08,
		.xtal_freq_count = 0x76
	पूर्ण, अणु
		.osc_frequency = 26000000, .enable_delay_count = 0x04,
		.stable_count = 0x66, .active_delay_count = 0x09,
		.xtal_freq_count = 0xfe
	पूर्ण, अणु
		.osc_frequency = 16800000, .enable_delay_count = 0x03,
		.stable_count = 0x41, .active_delay_count = 0x0a,
		.xtal_freq_count = 0xa4
	पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk tegra210_clks[tegra_clk_max] __initdata = अणु
	[tegra_clk_ispb] = अणु .dt_id = TEGRA210_CLK_ISPB, .present = true पूर्ण,
	[tegra_clk_rtc] = अणु .dt_id = TEGRA210_CLK_RTC, .present = true पूर्ण,
	[tegra_clk_समयr] = अणु .dt_id = TEGRA210_CLK_TIMER, .present = true पूर्ण,
	[tegra_clk_uarta_8] = अणु .dt_id = TEGRA210_CLK_UARTA, .present = true पूर्ण,
	[tegra_clk_i2s1] = अणु .dt_id = TEGRA210_CLK_I2S1, .present = true पूर्ण,
	[tegra_clk_i2c1] = अणु .dt_id = TEGRA210_CLK_I2C1, .present = true पूर्ण,
	[tegra_clk_sdmmc1_9] = अणु .dt_id = TEGRA210_CLK_SDMMC1, .present = true पूर्ण,
	[tegra_clk_pwm] = अणु .dt_id = TEGRA210_CLK_PWM, .present = true पूर्ण,
	[tegra_clk_i2s2] = अणु .dt_id = TEGRA210_CLK_I2S2, .present = true पूर्ण,
	[tegra_clk_usbd] = अणु .dt_id = TEGRA210_CLK_USBD, .present = true पूर्ण,
	[tegra_clk_isp_9] = अणु .dt_id = TEGRA210_CLK_ISP, .present = true पूर्ण,
	[tegra_clk_disp2_8] = अणु .dt_id = TEGRA210_CLK_DISP2, .present = true पूर्ण,
	[tegra_clk_disp1_8] = अणु .dt_id = TEGRA210_CLK_DISP1, .present = true पूर्ण,
	[tegra_clk_host1x_9] = अणु .dt_id = TEGRA210_CLK_HOST1X, .present = true पूर्ण,
	[tegra_clk_i2s0] = अणु .dt_id = TEGRA210_CLK_I2S0, .present = true पूर्ण,
	[tegra_clk_apbdma] = अणु .dt_id = TEGRA210_CLK_APBDMA, .present = true पूर्ण,
	[tegra_clk_kfuse] = अणु .dt_id = TEGRA210_CLK_KFUSE, .present = true पूर्ण,
	[tegra_clk_sbc1_9] = अणु .dt_id = TEGRA210_CLK_SBC1, .present = true पूर्ण,
	[tegra_clk_sbc2_9] = अणु .dt_id = TEGRA210_CLK_SBC2, .present = true पूर्ण,
	[tegra_clk_sbc3_9] = अणु .dt_id = TEGRA210_CLK_SBC3, .present = true पूर्ण,
	[tegra_clk_i2c5] = अणु .dt_id = TEGRA210_CLK_I2C5, .present = true पूर्ण,
	[tegra_clk_csi] = अणु .dt_id = TEGRA210_CLK_CSI, .present = true पूर्ण,
	[tegra_clk_i2c2] = अणु .dt_id = TEGRA210_CLK_I2C2, .present = true पूर्ण,
	[tegra_clk_uartc_8] = अणु .dt_id = TEGRA210_CLK_UARTC, .present = true पूर्ण,
	[tegra_clk_mipi_cal] = अणु .dt_id = TEGRA210_CLK_MIPI_CAL, .present = true पूर्ण,
	[tegra_clk_usb2] = अणु .dt_id = TEGRA210_CLK_USB2, .present = true पूर्ण,
	[tegra_clk_bsev] = अणु .dt_id = TEGRA210_CLK_BSEV, .present = true पूर्ण,
	[tegra_clk_uartd_8] = अणु .dt_id = TEGRA210_CLK_UARTD, .present = true पूर्ण,
	[tegra_clk_i2c3] = अणु .dt_id = TEGRA210_CLK_I2C3, .present = true पूर्ण,
	[tegra_clk_sbc4_9] = अणु .dt_id = TEGRA210_CLK_SBC4, .present = true पूर्ण,
	[tegra_clk_sdmmc3_9] = अणु .dt_id = TEGRA210_CLK_SDMMC3, .present = true पूर्ण,
	[tegra_clk_pcie] = अणु .dt_id = TEGRA210_CLK_PCIE, .present = true पूर्ण,
	[tegra_clk_owr_8] = अणु .dt_id = TEGRA210_CLK_OWR, .present = true पूर्ण,
	[tegra_clk_afi] = अणु .dt_id = TEGRA210_CLK_AFI, .present = true पूर्ण,
	[tegra_clk_csite_8] = अणु .dt_id = TEGRA210_CLK_CSITE, .present = true पूर्ण,
	[tegra_clk_soc_therm_8] = अणु .dt_id = TEGRA210_CLK_SOC_THERM, .present = true पूर्ण,
	[tegra_clk_dtv] = अणु .dt_id = TEGRA210_CLK_DTV, .present = true पूर्ण,
	[tegra_clk_i2cslow] = अणु .dt_id = TEGRA210_CLK_I2CSLOW, .present = true पूर्ण,
	[tegra_clk_tsec_8] = अणु .dt_id = TEGRA210_CLK_TSEC, .present = true पूर्ण,
	[tegra_clk_xusb_host] = अणु .dt_id = TEGRA210_CLK_XUSB_HOST, .present = true पूर्ण,
	[tegra_clk_csus] = अणु .dt_id = TEGRA210_CLK_CSUS, .present = true पूर्ण,
	[tegra_clk_mselect] = अणु .dt_id = TEGRA210_CLK_MSELECT, .present = true पूर्ण,
	[tegra_clk_tsensor] = अणु .dt_id = TEGRA210_CLK_TSENSOR, .present = true पूर्ण,
	[tegra_clk_i2s3] = अणु .dt_id = TEGRA210_CLK_I2S3, .present = true पूर्ण,
	[tegra_clk_i2s4] = अणु .dt_id = TEGRA210_CLK_I2S4, .present = true पूर्ण,
	[tegra_clk_i2c4] = अणु .dt_id = TEGRA210_CLK_I2C4, .present = true पूर्ण,
	[tegra_clk_d_audio] = अणु .dt_id = TEGRA210_CLK_D_AUDIO, .present = true पूर्ण,
	[tegra_clk_hda2codec_2x_8] = अणु .dt_id = TEGRA210_CLK_HDA2CODEC_2X, .present = true पूर्ण,
	[tegra_clk_spdअगर_2x] = अणु .dt_id = TEGRA210_CLK_SPDIF_2X, .present = true पूर्ण,
	[tegra_clk_acपंचांगon] = अणु .dt_id = TEGRA210_CLK_ACTMON, .present = true पूर्ण,
	[tegra_clk_बाह्य1] = अणु .dt_id = TEGRA210_CLK_EXTERN1, .present = true पूर्ण,
	[tegra_clk_बाह्य2] = अणु .dt_id = TEGRA210_CLK_EXTERN2, .present = true पूर्ण,
	[tegra_clk_बाह्य3] = अणु .dt_id = TEGRA210_CLK_EXTERN3, .present = true पूर्ण,
	[tegra_clk_sata_oob_8] = अणु .dt_id = TEGRA210_CLK_SATA_OOB, .present = true पूर्ण,
	[tegra_clk_sata_8] = अणु .dt_id = TEGRA210_CLK_SATA, .present = true पूर्ण,
	[tegra_clk_hda_8] = अणु .dt_id = TEGRA210_CLK_HDA, .present = true पूर्ण,
	[tegra_clk_hda2hdmi] = अणु .dt_id = TEGRA210_CLK_HDA2HDMI, .present = true पूर्ण,
	[tegra_clk_cilab] = अणु .dt_id = TEGRA210_CLK_CILAB, .present = true पूर्ण,
	[tegra_clk_cilcd] = अणु .dt_id = TEGRA210_CLK_CILCD, .present = true पूर्ण,
	[tegra_clk_cile] = अणु .dt_id = TEGRA210_CLK_CILE, .present = true पूर्ण,
	[tegra_clk_dsialp] = अणु .dt_id = TEGRA210_CLK_DSIALP, .present = true पूर्ण,
	[tegra_clk_dsiblp] = अणु .dt_id = TEGRA210_CLK_DSIBLP, .present = true पूर्ण,
	[tegra_clk_entropy_8] = अणु .dt_id = TEGRA210_CLK_ENTROPY, .present = true पूर्ण,
	[tegra_clk_xusb_ss] = अणु .dt_id = TEGRA210_CLK_XUSB_SS, .present = true पूर्ण,
	[tegra_clk_i2c6] = अणु .dt_id = TEGRA210_CLK_I2C6, .present = true पूर्ण,
	[tegra_clk_vim2_clk] = अणु .dt_id = TEGRA210_CLK_VIM2_CLK, .present = true पूर्ण,
	[tegra_clk_clk72Mhz_8] = अणु .dt_id = TEGRA210_CLK_CLK72MHZ, .present = true पूर्ण,
	[tegra_clk_vic03_8] = अणु .dt_id = TEGRA210_CLK_VIC03, .present = true पूर्ण,
	[tegra_clk_dpaux] = अणु .dt_id = TEGRA210_CLK_DPAUX, .present = true पूर्ण,
	[tegra_clk_dpaux1] = अणु .dt_id = TEGRA210_CLK_DPAUX1, .present = true पूर्ण,
	[tegra_clk_sor0] = अणु .dt_id = TEGRA210_CLK_SOR0, .present = true पूर्ण,
	[tegra_clk_sor0_out] = अणु .dt_id = TEGRA210_CLK_SOR0_OUT, .present = true पूर्ण,
	[tegra_clk_sor1] = अणु .dt_id = TEGRA210_CLK_SOR1, .present = true पूर्ण,
	[tegra_clk_sor1_out] = अणु .dt_id = TEGRA210_CLK_SOR1_OUT, .present = true पूर्ण,
	[tegra_clk_gpu] = अणु .dt_id = TEGRA210_CLK_GPU, .present = true पूर्ण,
	[tegra_clk_pll_g_ref] = अणु .dt_id = TEGRA210_CLK_PLL_G_REF, .present = true, पूर्ण,
	[tegra_clk_uartb_8] = अणु .dt_id = TEGRA210_CLK_UARTB, .present = true पूर्ण,
	[tegra_clk_spdअगर_in_8] = अणु .dt_id = TEGRA210_CLK_SPDIF_IN, .present = true पूर्ण,
	[tegra_clk_spdअगर_out] = अणु .dt_id = TEGRA210_CLK_SPDIF_OUT, .present = true पूर्ण,
	[tegra_clk_vi_10] = अणु .dt_id = TEGRA210_CLK_VI, .present = true पूर्ण,
	[tegra_clk_vi_sensor_8] = अणु .dt_id = TEGRA210_CLK_VI_SENSOR, .present = true पूर्ण,
	[tegra_clk_fuse] = अणु .dt_id = TEGRA210_CLK_FUSE, .present = true पूर्ण,
	[tegra_clk_fuse_burn] = अणु .dt_id = TEGRA210_CLK_FUSE_BURN, .present = true पूर्ण,
	[tegra_clk_clk_32k] = अणु .dt_id = TEGRA210_CLK_CLK_32K, .present = true पूर्ण,
	[tegra_clk_clk_m] = अणु .dt_id = TEGRA210_CLK_CLK_M, .present = true पूर्ण,
	[tegra_clk_osc] = अणु .dt_id = TEGRA210_CLK_OSC, .present = true पूर्ण,
	[tegra_clk_osc_भाग2] = अणु .dt_id = TEGRA210_CLK_OSC_DIV2, .present = true पूर्ण,
	[tegra_clk_osc_भाग4] = अणु .dt_id = TEGRA210_CLK_OSC_DIV4, .present = true पूर्ण,
	[tegra_clk_pll_ref] = अणु .dt_id = TEGRA210_CLK_PLL_REF, .present = true पूर्ण,
	[tegra_clk_pll_c] = अणु .dt_id = TEGRA210_CLK_PLL_C, .present = true पूर्ण,
	[tegra_clk_pll_c_out1] = अणु .dt_id = TEGRA210_CLK_PLL_C_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_c2] = अणु .dt_id = TEGRA210_CLK_PLL_C2, .present = true पूर्ण,
	[tegra_clk_pll_c3] = अणु .dt_id = TEGRA210_CLK_PLL_C3, .present = true पूर्ण,
	[tegra_clk_pll_m] = अणु .dt_id = TEGRA210_CLK_PLL_M, .present = true पूर्ण,
	[tegra_clk_pll_p] = अणु .dt_id = TEGRA210_CLK_PLL_P, .present = true पूर्ण,
	[tegra_clk_pll_p_out1] = अणु .dt_id = TEGRA210_CLK_PLL_P_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_p_out3] = अणु .dt_id = TEGRA210_CLK_PLL_P_OUT3, .present = true पूर्ण,
	[tegra_clk_pll_p_out4_cpu] = अणु .dt_id = TEGRA210_CLK_PLL_P_OUT4, .present = true पूर्ण,
	[tegra_clk_pll_p_out_hsio] = अणु .dt_id = TEGRA210_CLK_PLL_P_OUT_HSIO, .present = true पूर्ण,
	[tegra_clk_pll_p_out_xusb] = अणु .dt_id = TEGRA210_CLK_PLL_P_OUT_XUSB, .present = true पूर्ण,
	[tegra_clk_pll_p_out_cpu] = अणु .dt_id = TEGRA210_CLK_PLL_P_OUT_CPU, .present = true पूर्ण,
	[tegra_clk_pll_p_out_adsp] = अणु .dt_id = TEGRA210_CLK_PLL_P_OUT_ADSP, .present = true पूर्ण,
	[tegra_clk_pll_a] = अणु .dt_id = TEGRA210_CLK_PLL_A, .present = true पूर्ण,
	[tegra_clk_pll_a_out0] = अणु .dt_id = TEGRA210_CLK_PLL_A_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_d] = अणु .dt_id = TEGRA210_CLK_PLL_D, .present = true पूर्ण,
	[tegra_clk_pll_d_out0] = अणु .dt_id = TEGRA210_CLK_PLL_D_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_d2] = अणु .dt_id = TEGRA210_CLK_PLL_D2, .present = true पूर्ण,
	[tegra_clk_pll_d2_out0] = अणु .dt_id = TEGRA210_CLK_PLL_D2_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_u] = अणु .dt_id = TEGRA210_CLK_PLL_U, .present = true पूर्ण,
	[tegra_clk_pll_u_out] = अणु .dt_id = TEGRA210_CLK_PLL_U_OUT, .present = true पूर्ण,
	[tegra_clk_pll_u_out1] = अणु .dt_id = TEGRA210_CLK_PLL_U_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_u_out2] = अणु .dt_id = TEGRA210_CLK_PLL_U_OUT2, .present = true पूर्ण,
	[tegra_clk_pll_u_480m] = अणु .dt_id = TEGRA210_CLK_PLL_U_480M, .present = true पूर्ण,
	[tegra_clk_pll_u_60m] = अणु .dt_id = TEGRA210_CLK_PLL_U_60M, .present = true पूर्ण,
	[tegra_clk_pll_u_48m] = अणु .dt_id = TEGRA210_CLK_PLL_U_48M, .present = true पूर्ण,
	[tegra_clk_pll_x] = अणु .dt_id = TEGRA210_CLK_PLL_X, .present = true पूर्ण,
	[tegra_clk_pll_x_out0] = अणु .dt_id = TEGRA210_CLK_PLL_X_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_re_vco] = अणु .dt_id = TEGRA210_CLK_PLL_RE_VCO, .present = true पूर्ण,
	[tegra_clk_pll_re_out] = अणु .dt_id = TEGRA210_CLK_PLL_RE_OUT, .present = true पूर्ण,
	[tegra_clk_spdअगर_in_sync] = अणु .dt_id = TEGRA210_CLK_SPDIF_IN_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s0_sync] = अणु .dt_id = TEGRA210_CLK_I2S0_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s1_sync] = अणु .dt_id = TEGRA210_CLK_I2S1_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s2_sync] = अणु .dt_id = TEGRA210_CLK_I2S2_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s3_sync] = अणु .dt_id = TEGRA210_CLK_I2S3_SYNC, .present = true पूर्ण,
	[tegra_clk_i2s4_sync] = अणु .dt_id = TEGRA210_CLK_I2S4_SYNC, .present = true पूर्ण,
	[tegra_clk_vimclk_sync] = अणु .dt_id = TEGRA210_CLK_VIMCLK_SYNC, .present = true पूर्ण,
	[tegra_clk_audio0] = अणु .dt_id = TEGRA210_CLK_AUDIO0, .present = true पूर्ण,
	[tegra_clk_audio1] = अणु .dt_id = TEGRA210_CLK_AUDIO1, .present = true पूर्ण,
	[tegra_clk_audio2] = अणु .dt_id = TEGRA210_CLK_AUDIO2, .present = true पूर्ण,
	[tegra_clk_audio3] = अणु .dt_id = TEGRA210_CLK_AUDIO3, .present = true पूर्ण,
	[tegra_clk_audio4] = अणु .dt_id = TEGRA210_CLK_AUDIO4, .present = true पूर्ण,
	[tegra_clk_spdअगर] = अणु .dt_id = TEGRA210_CLK_SPDIF, .present = true पूर्ण,
	[tegra_clk_xusb_gate] = अणु .dt_id = TEGRA210_CLK_XUSB_GATE, .present = true पूर्ण,
	[tegra_clk_xusb_host_src_8] = अणु .dt_id = TEGRA210_CLK_XUSB_HOST_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_falcon_src_8] = अणु .dt_id = TEGRA210_CLK_XUSB_FALCON_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_fs_src] = अणु .dt_id = TEGRA210_CLK_XUSB_FS_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_ss_src_8] = अणु .dt_id = TEGRA210_CLK_XUSB_SS_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_ss_भाग2] = अणु .dt_id = TEGRA210_CLK_XUSB_SS_DIV2, .present = true पूर्ण,
	[tegra_clk_xusb_dev_src_8] = अणु .dt_id = TEGRA210_CLK_XUSB_DEV_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_dev] = अणु .dt_id = TEGRA210_CLK_XUSB_DEV, .present = true पूर्ण,
	[tegra_clk_xusb_hs_src_4] = अणु .dt_id = TEGRA210_CLK_XUSB_HS_SRC, .present = true पूर्ण,
	[tegra_clk_xusb_ssp_src] = अणु .dt_id = TEGRA210_CLK_XUSB_SSP_SRC, .present = true पूर्ण,
	[tegra_clk_usb2_hsic_trk] = अणु .dt_id = TEGRA210_CLK_USB2_HSIC_TRK, .present = true पूर्ण,
	[tegra_clk_hsic_trk] = अणु .dt_id = TEGRA210_CLK_HSIC_TRK, .present = true पूर्ण,
	[tegra_clk_usb2_trk] = अणु .dt_id = TEGRA210_CLK_USB2_TRK, .present = true पूर्ण,
	[tegra_clk_sclk] = अणु .dt_id = TEGRA210_CLK_SCLK, .present = true पूर्ण,
	[tegra_clk_sclk_mux] = अणु .dt_id = TEGRA210_CLK_SCLK_MUX, .present = true पूर्ण,
	[tegra_clk_hclk] = अणु .dt_id = TEGRA210_CLK_HCLK, .present = true पूर्ण,
	[tegra_clk_pclk] = अणु .dt_id = TEGRA210_CLK_PCLK, .present = true पूर्ण,
	[tegra_clk_cclk_g] = अणु .dt_id = TEGRA210_CLK_CCLK_G, .present = true पूर्ण,
	[tegra_clk_cclk_lp] = अणु .dt_id = TEGRA210_CLK_CCLK_LP, .present = true पूर्ण,
	[tegra_clk_dfll_ref] = अणु .dt_id = TEGRA210_CLK_DFLL_REF, .present = true पूर्ण,
	[tegra_clk_dfll_soc] = अणु .dt_id = TEGRA210_CLK_DFLL_SOC, .present = true पूर्ण,
	[tegra_clk_vi_sensor2_8] = अणु .dt_id = TEGRA210_CLK_VI_SENSOR2, .present = true पूर्ण,
	[tegra_clk_pll_p_out5] = अणु .dt_id = TEGRA210_CLK_PLL_P_OUT5, .present = true पूर्ण,
	[tegra_clk_pll_c4] = अणु .dt_id = TEGRA210_CLK_PLL_C4, .present = true पूर्ण,
	[tegra_clk_pll_dp] = अणु .dt_id = TEGRA210_CLK_PLL_DP, .present = true पूर्ण,
	[tegra_clk_audio0_mux] = अणु .dt_id = TEGRA210_CLK_AUDIO0_MUX, .present = true पूर्ण,
	[tegra_clk_audio1_mux] = अणु .dt_id = TEGRA210_CLK_AUDIO1_MUX, .present = true पूर्ण,
	[tegra_clk_audio2_mux] = अणु .dt_id = TEGRA210_CLK_AUDIO2_MUX, .present = true पूर्ण,
	[tegra_clk_audio3_mux] = अणु .dt_id = TEGRA210_CLK_AUDIO3_MUX, .present = true पूर्ण,
	[tegra_clk_audio4_mux] = अणु .dt_id = TEGRA210_CLK_AUDIO4_MUX, .present = true पूर्ण,
	[tegra_clk_spdअगर_mux] = अणु .dt_id = TEGRA210_CLK_SPDIF_MUX, .present = true पूर्ण,
	[tegra_clk_maud] = अणु .dt_id = TEGRA210_CLK_MAUD, .present = true पूर्ण,
	[tegra_clk_mipibअगर] = अणु .dt_id = TEGRA210_CLK_MIPIBIF, .present = true पूर्ण,
	[tegra_clk_qspi] = अणु .dt_id = TEGRA210_CLK_QSPI, .present = true पूर्ण,
	[tegra_clk_sdmmc_legacy] = अणु .dt_id = TEGRA210_CLK_SDMMC_LEGACY, .present = true पूर्ण,
	[tegra_clk_tsecb] = अणु .dt_id = TEGRA210_CLK_TSECB, .present = true पूर्ण,
	[tegra_clk_uartape] = अणु .dt_id = TEGRA210_CLK_UARTAPE, .present = true पूर्ण,
	[tegra_clk_vi_i2c] = अणु .dt_id = TEGRA210_CLK_VI_I2C, .present = true पूर्ण,
	[tegra_clk_ape] = अणु .dt_id = TEGRA210_CLK_APE, .present = true पूर्ण,
	[tegra_clk_dbgapb] = अणु .dt_id = TEGRA210_CLK_DBGAPB, .present = true पूर्ण,
	[tegra_clk_nvdec] = अणु .dt_id = TEGRA210_CLK_NVDEC, .present = true पूर्ण,
	[tegra_clk_nvenc] = अणु .dt_id = TEGRA210_CLK_NVENC, .present = true पूर्ण,
	[tegra_clk_nvjpg] = अणु .dt_id = TEGRA210_CLK_NVJPG, .present = true पूर्ण,
	[tegra_clk_pll_c4_out0] = अणु .dt_id = TEGRA210_CLK_PLL_C4_OUT0, .present = true पूर्ण,
	[tegra_clk_pll_c4_out1] = अणु .dt_id = TEGRA210_CLK_PLL_C4_OUT1, .present = true पूर्ण,
	[tegra_clk_pll_c4_out2] = अणु .dt_id = TEGRA210_CLK_PLL_C4_OUT2, .present = true पूर्ण,
	[tegra_clk_pll_c4_out3] = अणु .dt_id = TEGRA210_CLK_PLL_C4_OUT3, .present = true पूर्ण,
	[tegra_clk_apb2ape] = अणु .dt_id = TEGRA210_CLK_APB2APE, .present = true पूर्ण,
	[tegra_clk_pll_a1] = अणु .dt_id = TEGRA210_CLK_PLL_A1, .present = true पूर्ण,
	[tegra_clk_ispa] = अणु .dt_id = TEGRA210_CLK_ISPA, .present = true पूर्ण,
	[tegra_clk_cec] = अणु .dt_id = TEGRA210_CLK_CEC, .present = true पूर्ण,
	[tegra_clk_dmic1] = अणु .dt_id = TEGRA210_CLK_DMIC1, .present = true पूर्ण,
	[tegra_clk_dmic2] = अणु .dt_id = TEGRA210_CLK_DMIC2, .present = true पूर्ण,
	[tegra_clk_dmic3] = अणु .dt_id = TEGRA210_CLK_DMIC3, .present = true पूर्ण,
	[tegra_clk_dmic1_sync_clk] = अणु .dt_id = TEGRA210_CLK_DMIC1_SYNC_CLK, .present = true पूर्ण,
	[tegra_clk_dmic2_sync_clk] = अणु .dt_id = TEGRA210_CLK_DMIC2_SYNC_CLK, .present = true पूर्ण,
	[tegra_clk_dmic3_sync_clk] = अणु .dt_id = TEGRA210_CLK_DMIC3_SYNC_CLK, .present = true पूर्ण,
	[tegra_clk_dmic1_sync_clk_mux] = अणु .dt_id = TEGRA210_CLK_DMIC1_SYNC_CLK_MUX, .present = true पूर्ण,
	[tegra_clk_dmic2_sync_clk_mux] = अणु .dt_id = TEGRA210_CLK_DMIC2_SYNC_CLK_MUX, .present = true पूर्ण,
	[tegra_clk_dmic3_sync_clk_mux] = अणु .dt_id = TEGRA210_CLK_DMIC3_SYNC_CLK_MUX, .present = true पूर्ण,
	[tegra_clk_dp2] = अणु .dt_id = TEGRA210_CLK_DP2, .present = true पूर्ण,
	[tegra_clk_iqc1] = अणु .dt_id = TEGRA210_CLK_IQC1, .present = true पूर्ण,
	[tegra_clk_iqc2] = अणु .dt_id = TEGRA210_CLK_IQC2, .present = true पूर्ण,
	[tegra_clk_pll_a_out_adsp] = अणु .dt_id = TEGRA210_CLK_PLL_A_OUT_ADSP, .present = true पूर्ण,
	[tegra_clk_pll_a_out0_out_adsp] = अणु .dt_id = TEGRA210_CLK_PLL_A_OUT0_OUT_ADSP, .present = true पूर्ण,
	[tegra_clk_adsp] = अणु .dt_id = TEGRA210_CLK_ADSP, .present = true पूर्ण,
	[tegra_clk_adsp_neon] = अणु .dt_id = TEGRA210_CLK_ADSP_NEON, .present = true पूर्ण,
पूर्ण;

अटल काष्ठा tegra_devclk devclks[] __initdata = अणु
	अणु .con_id = "clk_m", .dt_id = TEGRA210_CLK_CLK_M पूर्ण,
	अणु .con_id = "pll_ref", .dt_id = TEGRA210_CLK_PLL_REF पूर्ण,
	अणु .con_id = "clk_32k", .dt_id = TEGRA210_CLK_CLK_32K पूर्ण,
	अणु .con_id = "osc", .dt_id = TEGRA210_CLK_OSC पूर्ण,
	अणु .con_id = "osc_div2", .dt_id = TEGRA210_CLK_OSC_DIV2 पूर्ण,
	अणु .con_id = "osc_div4", .dt_id = TEGRA210_CLK_OSC_DIV4 पूर्ण,
	अणु .con_id = "pll_c", .dt_id = TEGRA210_CLK_PLL_C पूर्ण,
	अणु .con_id = "pll_c_out1", .dt_id = TEGRA210_CLK_PLL_C_OUT1 पूर्ण,
	अणु .con_id = "pll_c2", .dt_id = TEGRA210_CLK_PLL_C2 पूर्ण,
	अणु .con_id = "pll_c3", .dt_id = TEGRA210_CLK_PLL_C3 पूर्ण,
	अणु .con_id = "pll_p", .dt_id = TEGRA210_CLK_PLL_P पूर्ण,
	अणु .con_id = "pll_p_out1", .dt_id = TEGRA210_CLK_PLL_P_OUT1 पूर्ण,
	अणु .con_id = "pll_p_out2", .dt_id = TEGRA210_CLK_PLL_P_OUT2 पूर्ण,
	अणु .con_id = "pll_p_out3", .dt_id = TEGRA210_CLK_PLL_P_OUT3 पूर्ण,
	अणु .con_id = "pll_p_out4", .dt_id = TEGRA210_CLK_PLL_P_OUT4 पूर्ण,
	अणु .con_id = "pll_m", .dt_id = TEGRA210_CLK_PLL_M पूर्ण,
	अणु .con_id = "pll_x", .dt_id = TEGRA210_CLK_PLL_X पूर्ण,
	अणु .con_id = "pll_x_out0", .dt_id = TEGRA210_CLK_PLL_X_OUT0 पूर्ण,
	अणु .con_id = "pll_u", .dt_id = TEGRA210_CLK_PLL_U पूर्ण,
	अणु .con_id = "pll_u_out", .dt_id = TEGRA210_CLK_PLL_U_OUT पूर्ण,
	अणु .con_id = "pll_u_out1", .dt_id = TEGRA210_CLK_PLL_U_OUT1 पूर्ण,
	अणु .con_id = "pll_u_out2", .dt_id = TEGRA210_CLK_PLL_U_OUT2 पूर्ण,
	अणु .con_id = "pll_u_480M", .dt_id = TEGRA210_CLK_PLL_U_480M पूर्ण,
	अणु .con_id = "pll_u_60M", .dt_id = TEGRA210_CLK_PLL_U_60M पूर्ण,
	अणु .con_id = "pll_u_48M", .dt_id = TEGRA210_CLK_PLL_U_48M पूर्ण,
	अणु .con_id = "pll_d", .dt_id = TEGRA210_CLK_PLL_D पूर्ण,
	अणु .con_id = "pll_d_out0", .dt_id = TEGRA210_CLK_PLL_D_OUT0 पूर्ण,
	अणु .con_id = "pll_d2", .dt_id = TEGRA210_CLK_PLL_D2 पूर्ण,
	अणु .con_id = "pll_d2_out0", .dt_id = TEGRA210_CLK_PLL_D2_OUT0 पूर्ण,
	अणु .con_id = "pll_a", .dt_id = TEGRA210_CLK_PLL_A पूर्ण,
	अणु .con_id = "pll_a_out0", .dt_id = TEGRA210_CLK_PLL_A_OUT0 पूर्ण,
	अणु .con_id = "pll_re_vco", .dt_id = TEGRA210_CLK_PLL_RE_VCO पूर्ण,
	अणु .con_id = "pll_re_out", .dt_id = TEGRA210_CLK_PLL_RE_OUT पूर्ण,
	अणु .con_id = "spdif_in_sync", .dt_id = TEGRA210_CLK_SPDIF_IN_SYNC पूर्ण,
	अणु .con_id = "i2s0_sync", .dt_id = TEGRA210_CLK_I2S0_SYNC पूर्ण,
	अणु .con_id = "i2s1_sync", .dt_id = TEGRA210_CLK_I2S1_SYNC पूर्ण,
	अणु .con_id = "i2s2_sync", .dt_id = TEGRA210_CLK_I2S2_SYNC पूर्ण,
	अणु .con_id = "i2s3_sync", .dt_id = TEGRA210_CLK_I2S3_SYNC पूर्ण,
	अणु .con_id = "i2s4_sync", .dt_id = TEGRA210_CLK_I2S4_SYNC पूर्ण,
	अणु .con_id = "vimclk_sync", .dt_id = TEGRA210_CLK_VIMCLK_SYNC पूर्ण,
	अणु .con_id = "audio0", .dt_id = TEGRA210_CLK_AUDIO0 पूर्ण,
	अणु .con_id = "audio1", .dt_id = TEGRA210_CLK_AUDIO1 पूर्ण,
	अणु .con_id = "audio2", .dt_id = TEGRA210_CLK_AUDIO2 पूर्ण,
	अणु .con_id = "audio3", .dt_id = TEGRA210_CLK_AUDIO3 पूर्ण,
	अणु .con_id = "audio4", .dt_id = TEGRA210_CLK_AUDIO4 पूर्ण,
	अणु .con_id = "spdif", .dt_id = TEGRA210_CLK_SPDIF पूर्ण,
	अणु .con_id = "spdif_2x", .dt_id = TEGRA210_CLK_SPDIF_2X पूर्ण,
	अणु .con_id = "extern1", .dt_id = TEGRA210_CLK_EXTERN1 पूर्ण,
	अणु .con_id = "extern2", .dt_id = TEGRA210_CLK_EXTERN2 पूर्ण,
	अणु .con_id = "extern3", .dt_id = TEGRA210_CLK_EXTERN3 पूर्ण,
	अणु .con_id = "cclk_g", .dt_id = TEGRA210_CLK_CCLK_G पूर्ण,
	अणु .con_id = "cclk_lp", .dt_id = TEGRA210_CLK_CCLK_LP पूर्ण,
	अणु .con_id = "sclk", .dt_id = TEGRA210_CLK_SCLK पूर्ण,
	अणु .con_id = "hclk", .dt_id = TEGRA210_CLK_HCLK पूर्ण,
	अणु .con_id = "pclk", .dt_id = TEGRA210_CLK_PCLK पूर्ण,
	अणु .con_id = "fuse", .dt_id = TEGRA210_CLK_FUSE पूर्ण,
	अणु .dev_id = "rtc-tegra", .dt_id = TEGRA210_CLK_RTC पूर्ण,
	अणु .dev_id = "timer", .dt_id = TEGRA210_CLK_TIMER पूर्ण,
	अणु .con_id = "pll_c4_out0", .dt_id = TEGRA210_CLK_PLL_C4_OUT0 पूर्ण,
	अणु .con_id = "pll_c4_out1", .dt_id = TEGRA210_CLK_PLL_C4_OUT1 पूर्ण,
	अणु .con_id = "pll_c4_out2", .dt_id = TEGRA210_CLK_PLL_C4_OUT2 पूर्ण,
	अणु .con_id = "pll_c4_out3", .dt_id = TEGRA210_CLK_PLL_C4_OUT3 पूर्ण,
	अणु .con_id = "dpaux", .dt_id = TEGRA210_CLK_DPAUX पूर्ण,
पूर्ण;

अटल काष्ठा tegra_audio_clk_info tegra210_audio_plls[] = अणु
	अणु "pll_a", &pll_a_params, tegra_clk_pll_a, "pll_ref" पूर्ण,
	अणु "pll_a1", &pll_a1_params, tegra_clk_pll_a1, "pll_ref" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर aclk_parents[] = अणु
	"pll_a1", "pll_c", "pll_p", "pll_a_out0", "pll_c2", "pll_c3",
	"clk_m"
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक nvjpg_slcg_clkids[] = अणु TEGRA210_CLK_NVDEC पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nvdec_slcg_clkids[] = अणु TEGRA210_CLK_NVJPG पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sor_slcg_clkids[] = अणु TEGRA210_CLK_HDA2CODEC_2X,
	TEGRA210_CLK_HDA2HDMI, TEGRA210_CLK_DISP1, TEGRA210_CLK_DISP2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक disp_slcg_clkids[] = अणु TEGRA210_CLK_LA,
	TEGRA210_CLK_HOST1Xपूर्ण;
अटल स्थिर अचिन्हित पूर्णांक xusba_slcg_clkids[] = अणु TEGRA210_CLK_XUSB_HOST,
	TEGRA210_CLK_XUSB_DEV पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक xusbb_slcg_clkids[] = अणु TEGRA210_CLK_XUSB_HOST,
	TEGRA210_CLK_XUSB_SS पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक xusbc_slcg_clkids[] = अणु TEGRA210_CLK_XUSB_DEV,
	TEGRA210_CLK_XUSB_SS पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक venc_slcg_clkids[] = अणु TEGRA210_CLK_HOST1X,
	TEGRA210_CLK_PLL_D पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ape_slcg_clkids[] = अणु TEGRA210_CLK_ACLK,
	TEGRA210_CLK_I2S0, TEGRA210_CLK_I2S1, TEGRA210_CLK_I2S2,
	TEGRA210_CLK_I2S3, TEGRA210_CLK_I2S4, TEGRA210_CLK_SPDIF_OUT,
	TEGRA210_CLK_D_AUDIO पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vic_slcg_clkids[] = अणु TEGRA210_CLK_HOST1X पूर्ण;

अटल काष्ठा tegra210_करोमुख्य_mbist_war tegra210_pg_mbist_war[] = अणु
	[TEGRA_POWERGATE_VENC] = अणु
		.handle_lvl2_ovr = tegra210_venc_mbist_war,
		.num_clks = ARRAY_SIZE(venc_slcg_clkids),
		.clk_init_data = venc_slcg_clkids,
	पूर्ण,
	[TEGRA_POWERGATE_SATA] = अणु
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRC,
		.lvl2_mask = BIT(0) | BIT(17) | BIT(19),
	पूर्ण,
	[TEGRA_POWERGATE_MPE] = अणु
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRE,
		.lvl2_mask = BIT(29),
	पूर्ण,
	[TEGRA_POWERGATE_SOR] = अणु
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.num_clks = ARRAY_SIZE(sor_slcg_clkids),
		.clk_init_data = sor_slcg_clkids,
		.lvl2_offset = LVL2_CLK_GATE_OVRA,
		.lvl2_mask = BIT(1) | BIT(2),
	पूर्ण,
	[TEGRA_POWERGATE_DIS] = अणु
		.handle_lvl2_ovr = tegra210_disp_mbist_war,
		.num_clks = ARRAY_SIZE(disp_slcg_clkids),
		.clk_init_data = disp_slcg_clkids,
	पूर्ण,
	[TEGRA_POWERGATE_DISB] = अणु
		.num_clks = ARRAY_SIZE(disp_slcg_clkids),
		.clk_init_data = disp_slcg_clkids,
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRA,
		.lvl2_mask = BIT(2),
	पूर्ण,
	[TEGRA_POWERGATE_XUSBA] = अणु
		.num_clks = ARRAY_SIZE(xusba_slcg_clkids),
		.clk_init_data = xusba_slcg_clkids,
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRC,
		.lvl2_mask = BIT(30) | BIT(31),
	पूर्ण,
	[TEGRA_POWERGATE_XUSBB] = अणु
		.num_clks = ARRAY_SIZE(xusbb_slcg_clkids),
		.clk_init_data = xusbb_slcg_clkids,
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRC,
		.lvl2_mask = BIT(30) | BIT(31),
	पूर्ण,
	[TEGRA_POWERGATE_XUSBC] = अणु
		.num_clks = ARRAY_SIZE(xusbc_slcg_clkids),
		.clk_init_data = xusbc_slcg_clkids,
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRC,
		.lvl2_mask = BIT(30) | BIT(31),
	पूर्ण,
	[TEGRA_POWERGATE_VIC] = अणु
		.num_clks = ARRAY_SIZE(vic_slcg_clkids),
		.clk_init_data = vic_slcg_clkids,
		.handle_lvl2_ovr = tegra210_vic_mbist_war,
	पूर्ण,
	[TEGRA_POWERGATE_NVDEC] = अणु
		.num_clks = ARRAY_SIZE(nvdec_slcg_clkids),
		.clk_init_data = nvdec_slcg_clkids,
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRE,
		.lvl2_mask = BIT(9) | BIT(31),
	पूर्ण,
	[TEGRA_POWERGATE_NVJPG] = अणु
		.num_clks = ARRAY_SIZE(nvjpg_slcg_clkids),
		.clk_init_data = nvjpg_slcg_clkids,
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRE,
		.lvl2_mask = BIT(9) | BIT(31),
	पूर्ण,
	[TEGRA_POWERGATE_AUD] = अणु
		.num_clks = ARRAY_SIZE(ape_slcg_clkids),
		.clk_init_data = ape_slcg_clkids,
		.handle_lvl2_ovr = tegra210_ape_mbist_war,
	पूर्ण,
	[TEGRA_POWERGATE_VE2] = अणु
		.handle_lvl2_ovr = tegra210_generic_mbist_war,
		.lvl2_offset = LVL2_CLK_GATE_OVRD,
		.lvl2_mask = BIT(22),
	पूर्ण,
पूर्ण;

पूर्णांक tegra210_clk_handle_mbist_war(अचिन्हित पूर्णांक id)
अणु
	पूर्णांक err;
	काष्ठा tegra210_करोमुख्य_mbist_war *mbist_war;

	अगर (id >= ARRAY_SIZE(tegra210_pg_mbist_war)) अणु
		WARN(1, "unknown domain id in MBIST WAR handler\n");
		वापस -EINVAL;
	पूर्ण

	mbist_war = &tegra210_pg_mbist_war[id];
	अगर (!mbist_war->handle_lvl2_ovr)
		वापस 0;

	अगर (mbist_war->num_clks && !mbist_war->clks)
		वापस -ENODEV;

	err = clk_bulk_prepare_enable(mbist_war->num_clks, mbist_war->clks);
	अगर (err < 0)
		वापस err;

	mutex_lock(&lvl2_ovr_lock);

	mbist_war->handle_lvl2_ovr(mbist_war);

	mutex_unlock(&lvl2_ovr_lock);

	clk_bulk_disable_unprepare(mbist_war->num_clks, mbist_war->clks);

	वापस 0;
पूर्ण

व्योम tegra210_put_uपंचांगipll_in_iddq(व्योम)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(clk_base + UTMIPLL_HW_PWRDN_CFG0);

	अगर (reg & UTMIPLL_HW_PWRDN_CFG0_UTMIPLL_LOCK) अणु
		pr_err("trying to assert IDDQ while UTMIPLL is locked\n");
		वापस;
	पूर्ण

	reg |= UTMIPLL_HW_PWRDN_CFG0_IDDQ_OVERRIDE;
	ग_लिखोl_relaxed(reg, clk_base + UTMIPLL_HW_PWRDN_CFG0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_put_uपंचांगipll_in_iddq);

व्योम tegra210_put_uपंचांगipll_out_iddq(व्योम)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(clk_base + UTMIPLL_HW_PWRDN_CFG0);
	reg &= ~UTMIPLL_HW_PWRDN_CFG0_IDDQ_OVERRIDE;
	ग_लिखोl_relaxed(reg, clk_base + UTMIPLL_HW_PWRDN_CFG0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_put_uपंचांगipll_out_iddq);

अटल व्योम tegra210_uपंचांगi_param_configure(व्योम)
अणु
	u32 reg;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(uपंचांगi_parameters); i++) अणु
		अगर (osc_freq == uपंचांगi_parameters[i].osc_frequency)
			अवरोध;
	पूर्ण

	अगर (i >= ARRAY_SIZE(uपंचांगi_parameters)) अणु
		pr_err("%s: Unexpected oscillator freq %lu\n", __func__,
			osc_freq);
		वापस;
	पूर्ण

	reg = पढ़ोl_relaxed(clk_base + UTMIPLL_HW_PWRDN_CFG0);
	reg &= ~UTMIPLL_HW_PWRDN_CFG0_IDDQ_OVERRIDE;
	ग_लिखोl_relaxed(reg, clk_base + UTMIPLL_HW_PWRDN_CFG0);

	udelay(10);

	reg = पढ़ोl_relaxed(clk_base + UTMIP_PLL_CFG2);

	/* Program UTMIP PLL stable and active counts */
	/* [FIXME] arclk_rst.h says WRONG! This should be 1ms -> 0x50 Check! */
	reg &= ~UTMIP_PLL_CFG2_STABLE_COUNT(~0);
	reg |= UTMIP_PLL_CFG2_STABLE_COUNT(uपंचांगi_parameters[i].stable_count);

	reg &= ~UTMIP_PLL_CFG2_ACTIVE_DLY_COUNT(~0);
	reg |=
	UTMIP_PLL_CFG2_ACTIVE_DLY_COUNT(uपंचांगi_parameters[i].active_delay_count);
	ग_लिखोl_relaxed(reg, clk_base + UTMIP_PLL_CFG2);

	/* Program UTMIP PLL delay and oscillator frequency counts */
	reg = पढ़ोl_relaxed(clk_base + UTMIP_PLL_CFG1);

	reg &= ~UTMIP_PLL_CFG1_ENABLE_DLY_COUNT(~0);
	reg |=
	UTMIP_PLL_CFG1_ENABLE_DLY_COUNT(uपंचांगi_parameters[i].enable_delay_count);

	reg &= ~UTMIP_PLL_CFG1_XTAL_FREQ_COUNT(~0);
	reg |=
	UTMIP_PLL_CFG1_XTAL_FREQ_COUNT(uपंचांगi_parameters[i].xtal_freq_count);

	reg |= UTMIP_PLL_CFG1_FORCE_PLLU_POWERDOWN;
	ग_लिखोl_relaxed(reg, clk_base + UTMIP_PLL_CFG1);

	/* Remove घातer करोwns from UTMIP PLL control bits */
	reg = पढ़ोl_relaxed(clk_base + UTMIP_PLL_CFG1);
	reg &= ~UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERDOWN;
	reg |= UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERUP;
	ग_लिखोl_relaxed(reg, clk_base + UTMIP_PLL_CFG1);

	udelay(20);

	/* Enable samplers क्रम SNPS, XUSB_HOST, XUSB_DEV */
	reg = पढ़ोl_relaxed(clk_base + UTMIP_PLL_CFG2);
	reg |= UTMIP_PLL_CFG2_FORCE_PD_SAMP_A_POWERUP;
	reg |= UTMIP_PLL_CFG2_FORCE_PD_SAMP_B_POWERUP;
	reg |= UTMIP_PLL_CFG2_FORCE_PD_SAMP_D_POWERUP;
	reg &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_A_POWERDOWN;
	reg &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_B_POWERDOWN;
	reg &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_D_POWERDOWN;
	ग_लिखोl_relaxed(reg, clk_base + UTMIP_PLL_CFG2);

	/* Setup HW control of UTMIPLL */
	reg = पढ़ोl_relaxed(clk_base + UTMIP_PLL_CFG1);
	reg &= ~UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERDOWN;
	reg &= ~UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERUP;
	ग_लिखोl_relaxed(reg, clk_base + UTMIP_PLL_CFG1);

	reg = पढ़ोl_relaxed(clk_base + UTMIPLL_HW_PWRDN_CFG0);
	reg |= UTMIPLL_HW_PWRDN_CFG0_USE_LOCKDET;
	reg &= ~UTMIPLL_HW_PWRDN_CFG0_CLK_ENABLE_SWCTL;
	ग_लिखोl_relaxed(reg, clk_base + UTMIPLL_HW_PWRDN_CFG0);

	udelay(1);

	reg = पढ़ोl_relaxed(clk_base + XUSB_PLL_CFG0);
	reg &= ~XUSB_PLL_CFG0_UTMIPLL_LOCK_DLY;
	ग_लिखोl_relaxed(reg, clk_base + XUSB_PLL_CFG0);

	udelay(1);

	/* Enable HW control UTMIPLL */
	reg = पढ़ोl_relaxed(clk_base + UTMIPLL_HW_PWRDN_CFG0);
	reg |= UTMIPLL_HW_PWRDN_CFG0_SEQ_ENABLE;
	ग_लिखोl_relaxed(reg, clk_base + UTMIPLL_HW_PWRDN_CFG0);
पूर्ण

अटल पूर्णांक tegra210_enable_pllu(व्योम)
अणु
	काष्ठा tegra_clk_pll_freq_table *fentry;
	काष्ठा tegra_clk_pll pllu;
	u32 reg;
	पूर्णांक ret;

	क्रम (fentry = pll_u_freq_table; fentry->input_rate; fentry++) अणु
		अगर (fentry->input_rate == pll_ref_freq)
			अवरोध;
	पूर्ण

	अगर (!fentry->input_rate) अणु
		pr_err("Unknown PLL_U reference frequency %lu\n", pll_ref_freq);
		वापस -EINVAL;
	पूर्ण

	/* clear IDDQ bit */
	pllu.params = &pll_u_vco_params;
	reg = पढ़ोl_relaxed(clk_base + pllu.params->ext_misc_reg[0]);
	reg &= ~BIT(pllu.params->iddq_bit_idx);
	ग_लिखोl_relaxed(reg, clk_base + pllu.params->ext_misc_reg[0]);
	fence_udelay(5, clk_base);

	reg = पढ़ोl_relaxed(clk_base + PLLU_BASE);
	reg &= ~GENMASK(20, 0);
	reg |= fentry->m;
	reg |= fentry->n << 8;
	reg |= fentry->p << 16;
	ग_लिखोl(reg, clk_base + PLLU_BASE);
	fence_udelay(1, clk_base);
	reg |= PLL_ENABLE;
	ग_लिखोl(reg, clk_base + PLLU_BASE);

	/*
	 * During घड़ीs resume, same PLLU init and enable sequence get
	 * executed. So, पढ़ोx_poll_समयout_atomic can't be used here as it
	 * uses kसमय_get() and समयkeeping resume करोesn't happen by that
	 * समय. So, using tegra210_रुको_क्रम_mask क्रम PLL LOCK.
	 */
	ret = tegra210_रुको_क्रम_mask(&pllu, PLLU_BASE, PLL_BASE_LOCK);
	अगर (ret) अणु
		pr_err("Timed out waiting for PLL_U to lock\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_init_pllu(व्योम)
अणु
	u32 reg;
	पूर्णांक err;

	tegra210_pllu_set_शेषs(&pll_u_vco_params);
	/* skip initialization when pllu is in hw controlled mode */
	reg = पढ़ोl_relaxed(clk_base + PLLU_BASE);
	अगर (reg & PLLU_BASE_OVERRIDE) अणु
		अगर (!(reg & PLL_ENABLE)) अणु
			err = tegra210_enable_pllu();
			अगर (err < 0) अणु
				WARN_ON(1);
				वापस err;
			पूर्ण
		पूर्ण
		/* enable hw controlled mode */
		reg = पढ़ोl_relaxed(clk_base + PLLU_BASE);
		reg &= ~PLLU_BASE_OVERRIDE;
		ग_लिखोl(reg, clk_base + PLLU_BASE);

		reg = पढ़ोl_relaxed(clk_base + PLLU_HW_PWRDN_CFG0);
		reg |= PLLU_HW_PWRDN_CFG0_IDDQ_PD_INCLUDE |
		       PLLU_HW_PWRDN_CFG0_USE_SWITCH_DETECT |
		       PLLU_HW_PWRDN_CFG0_USE_LOCKDET;
		reg &= ~(PLLU_HW_PWRDN_CFG0_CLK_ENABLE_SWCTL |
			PLLU_HW_PWRDN_CFG0_CLK_SWITCH_SWCTL);
		ग_लिखोl_relaxed(reg, clk_base + PLLU_HW_PWRDN_CFG0);

		reg = पढ़ोl_relaxed(clk_base + XUSB_PLL_CFG0);
		reg &= ~XUSB_PLL_CFG0_PLLU_LOCK_DLY_MASK;
		ग_लिखोl_relaxed(reg, clk_base + XUSB_PLL_CFG0);
		fence_udelay(1, clk_base);

		reg = पढ़ोl_relaxed(clk_base + PLLU_HW_PWRDN_CFG0);
		reg |= PLLU_HW_PWRDN_CFG0_SEQ_ENABLE;
		ग_लिखोl_relaxed(reg, clk_base + PLLU_HW_PWRDN_CFG0);
		fence_udelay(1, clk_base);

		reg = पढ़ोl_relaxed(clk_base + PLLU_BASE);
		reg &= ~PLLU_BASE_CLKENABLE_USB;
		ग_लिखोl_relaxed(reg, clk_base + PLLU_BASE);
	पूर्ण

	/* enable UTMIPLL hw control अगर not yet करोne by the bootloader */
	reg = पढ़ोl_relaxed(clk_base + UTMIPLL_HW_PWRDN_CFG0);
	अगर (!(reg & UTMIPLL_HW_PWRDN_CFG0_SEQ_ENABLE))
		tegra210_uपंचांगi_param_configure();

	वापस 0;
पूर्ण

/*
 * The SOR hardware blocks are driven by two घड़ीs: a module घड़ी that is
 * used to access रेजिस्टरs and a pixel घड़ी that is sourced from the same
 * pixel घड़ी that also drives the head attached to the SOR. The module
 * घड़ी is typically called sorX (with X being the SOR instance) and the
 * pixel घड़ी is called sorX_out. The source क्रम the SOR pixel घड़ी is
 * referred to as the "parent" घड़ी.
 *
 * On Tegra186 and newer, घड़ीs are provided by the BPMP. Unक्रमtunately the
 * BPMP implementation क्रम the SOR घड़ीs करोesn't exactly match the above in
 * some aspects. For example, the SOR module is really घड़ीed by the pad or
 * sor_safe घड़ीs, but BPMP models the sorX घड़ी as being sourced by the
 * pixel घड़ीs. Conversely the sorX_out घड़ी is sourced by the sor_safe or
 * pad घड़ीs on BPMP.
 *
 * In order to allow the display driver to deal with all SoC generations in
 * a unअगरied way, implement the BPMP semantics in this driver.
 */

अटल स्थिर अक्षर * स्थिर sor0_parents[] = अणु
	"pll_d_out0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sor0_out_parents[] = अणु
	"sor_safe", "sor0_pad_clkout",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sor1_parents[] = अणु
	"pll_p", "pll_d_out0", "pll_d2_out0", "clk_m",
पूर्ण;

अटल u32 sor1_parents_idx[] = अणु 0, 2, 5, 6 पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable mc_भाग_प्रकारable_tegra210[] = अणु
	अणु .val = 0, .भाग = 2 पूर्ण,
	अणु .val = 1, .भाग = 4 पूर्ण,
	अणु .val = 2, .भाग = 1 पूर्ण,
	अणु .val = 3, .भाग = 2 पूर्ण,
	अणु .val = 0, .भाग = 0 पूर्ण,
पूर्ण;

अटल व्योम tegra210_clk_रेजिस्टर_mc(स्थिर अक्षर *name,
				     स्थिर अक्षर *parent_name)
अणु
	काष्ठा clk *clk;

	clk = clk_रेजिस्टर_भागider_table(शून्य, name, parent_name,
					 CLK_IS_CRITICAL,
					 clk_base + CLK_SOURCE_EMC,
					 15, 2, CLK_DIVIDER_READ_ONLY,
					 mc_भाग_प्रकारable_tegra210, &emc_lock);
	clks[TEGRA210_CLK_MC] = clk;
पूर्ण

अटल स्थिर अक्षर * स्थिर sor1_out_parents[] = अणु
	/*
	 * Bit 0 of the mux selects sor1_pad_clkout, irrespective of bit 1, so
	 * the sor1_pad_clkout parent appears twice in the list below. This is
	 * merely to support clk_get_parent() अगर firmware happened to set
	 * these bits to 0b11. While not an invalid setting, code should
	 * always set the bits to 0b01 to select sor1_pad_clkout.
	 */
	"sor_safe", "sor1_pad_clkout", "sor1_out", "sor1_pad_clkout",
पूर्ण;

अटल काष्ठा tegra_periph_init_data tegra210_periph[] = अणु
	/*
	 * On Tegra210, the sor0 घड़ी करोesn't have a mux it bitfield 31:29,
	 * but it is hardwired to the pll_d_out0 घड़ी.
	 */
	TEGRA_INIT_DATA_TABLE("sor0", शून्य, शून्य, sor0_parents,
			      CLK_SOURCE_SOR0, 29, 0x0, 0, 0, 0, 0,
			      0, 182, 0, tegra_clk_sor0, शून्य, 0,
			      &sor0_lock),
	TEGRA_INIT_DATA_TABLE("sor0_out", शून्य, शून्य, sor0_out_parents,
			      CLK_SOURCE_SOR0, 14, 0x1, 0, 0, 0, 0,
			      0, 0, TEGRA_PERIPH_NO_GATE, tegra_clk_sor0_out,
			      शून्य, 0, &sor0_lock),
	TEGRA_INIT_DATA_TABLE("sor1", शून्य, शून्य, sor1_parents,
			      CLK_SOURCE_SOR1, 29, 0x7, 0, 0, 8, 1,
			      TEGRA_DIVIDER_ROUND_UP, 183, 0,
			      tegra_clk_sor1, sor1_parents_idx, 0,
			      &sor1_lock),
	TEGRA_INIT_DATA_TABLE("sor1_out", शून्य, शून्य, sor1_out_parents,
			      CLK_SOURCE_SOR1, 14, 0x3, 0, 0, 0, 0,
			      0, 0, TEGRA_PERIPH_NO_GATE,
			      tegra_clk_sor1_out, शून्य, 0, &sor1_lock),
पूर्ण;

अटल स्थिर अक्षर * स्थिर la_parents[] = अणु
	"pll_p", "pll_c2", "pll_c", "pll_c3", "pll_re_out1", "pll_a1", "clk_m", "pll_c4_out0"
पूर्ण;

अटल काष्ठा tegra_clk_periph tegra210_la =
	TEGRA_CLK_PERIPH(29, 7, 9, 0, 8, 1, TEGRA_DIVIDER_ROUND_UP, 76, 0, शून्य, शून्य);

अटल __init व्योम tegra210_periph_clk_init(काष्ठा device_node *np,
					    व्योम __iomem *clk_base,
					    व्योम __iomem *pmc_base)
अणु
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;

	/* xusb_ss_भाग2 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "xusb_ss_div2", "xusb_ss_src", 0,
					1, 2);
	clks[TEGRA210_CLK_XUSB_SS_DIV2] = clk;

	clk = tegra_clk_रेजिस्टर_periph_fixed("sor_safe", "pll_p", 0, clk_base,
					      1, 17, 222);
	clks[TEGRA210_CLK_SOR_SAFE] = clk;

	clk = tegra_clk_रेजिस्टर_periph_fixed("dpaux", "sor_safe", 0, clk_base,
					      1, 17, 181);
	clks[TEGRA210_CLK_DPAUX] = clk;

	clk = tegra_clk_रेजिस्टर_periph_fixed("dpaux1", "sor_safe", 0, clk_base,
					      1, 17, 207);
	clks[TEGRA210_CLK_DPAUX1] = clk;

	/* pll_d_dsi_out */
	clk = clk_रेजिस्टर_gate(शून्य, "pll_d_dsi_out", "pll_d_out0", 0,
				clk_base + PLLD_MISC0, 21, 0, &pll_d_lock);
	clks[TEGRA210_CLK_PLL_D_DSI_OUT] = clk;

	/* dsia */
	clk = tegra_clk_रेजिस्टर_periph_gate("dsia", "pll_d_dsi_out", 0,
					     clk_base, 0, 48,
					     periph_clk_enb_refcnt);
	clks[TEGRA210_CLK_DSIA] = clk;

	/* dsib */
	clk = tegra_clk_रेजिस्टर_periph_gate("dsib", "pll_d_dsi_out", 0,
					     clk_base, 0, 82,
					     periph_clk_enb_refcnt);
	clks[TEGRA210_CLK_DSIB] = clk;

	/* csi_tpg */
	clk = clk_रेजिस्टर_gate(शून्य, "csi_tpg", "pll_d",
				CLK_SET_RATE_PARENT, clk_base + PLLD_BASE,
				23, 0, &pll_d_lock);
	clk_रेजिस्टर_clkdev(clk, "csi_tpg", शून्य);
	clks[TEGRA210_CLK_CSI_TPG] = clk;

	/* la */
	clk = tegra_clk_रेजिस्टर_periph("la", la_parents,
			ARRAY_SIZE(la_parents), &tegra210_la, clk_base,
			CLK_SOURCE_LA, 0);
	clks[TEGRA210_CLK_LA] = clk;

	/* cml0 */
	clk = clk_रेजिस्टर_gate(शून्य, "cml0", "pll_e", 0, clk_base + PLLE_AUX,
				0, 0, &pll_e_lock);
	clk_रेजिस्टर_clkdev(clk, "cml0", शून्य);
	clks[TEGRA210_CLK_CML0] = clk;

	/* cml1 */
	clk = clk_रेजिस्टर_gate(शून्य, "cml1", "pll_e", 0, clk_base + PLLE_AUX,
				1, 0, &pll_e_lock);
	clk_रेजिस्टर_clkdev(clk, "cml1", शून्य);
	clks[TEGRA210_CLK_CML1] = clk;

	clk = tegra_clk_रेजिस्टर_super_clk("aclk", aclk_parents,
				ARRAY_SIZE(aclk_parents), 0, clk_base + 0x6e0,
				0, शून्य);
	clks[TEGRA210_CLK_ACLK] = clk;

	clk = tegra_clk_रेजिस्टर_sdmmc_mux_भाग("sdmmc2", clk_base,
					    CLK_SOURCE_SDMMC2, 9,
					    TEGRA_DIVIDER_ROUND_UP, 0, शून्य);
	clks[TEGRA210_CLK_SDMMC2] = clk;

	clk = tegra_clk_रेजिस्टर_sdmmc_mux_भाग("sdmmc4", clk_base,
					    CLK_SOURCE_SDMMC4, 15,
					    TEGRA_DIVIDER_ROUND_UP, 0, शून्य);
	clks[TEGRA210_CLK_SDMMC4] = clk;

	क्रम (i = 0; i < ARRAY_SIZE(tegra210_periph); i++) अणु
		काष्ठा tegra_periph_init_data *init = &tegra210_periph[i];
		काष्ठा clk **clkp;

		clkp = tegra_lookup_dt_id(init->clk_id, tegra210_clks);
		अगर (!clkp) अणु
			pr_warn("clock %u not found\n", init->clk_id);
			जारी;
		पूर्ण

		clk = tegra_clk_रेजिस्टर_periph_data(clk_base, init);
		*clkp = clk;
	पूर्ण

	tegra_periph_clk_init(clk_base, pmc_base, tegra210_clks, &pll_p_params);

	/* emc */
	clk = tegra210_clk_रेजिस्टर_emc(np, clk_base);
	clks[TEGRA210_CLK_EMC] = clk;

	/* mc */
	tegra210_clk_रेजिस्टर_mc("mc", "emc");
पूर्ण

अटल व्योम __init tegra210_pll_init(व्योम __iomem *clk_base,
				     व्योम __iomem *pmc)
अणु
	काष्ठा clk *clk;

	/* PLLC */
	clk = tegra_clk_रेजिस्टर_pllc_tegra210("pll_c", "pll_ref", clk_base,
			pmc, 0, &pll_c_params, शून्य);
	अगर (!WARN_ON(IS_ERR(clk)))
		clk_रेजिस्टर_clkdev(clk, "pll_c", शून्य);
	clks[TEGRA210_CLK_PLL_C] = clk;

	/* PLLC_OUT1 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_c_out1_div", "pll_c",
			clk_base + PLLC_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
			8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_c_out1", "pll_c_out1_div",
				clk_base + PLLC_OUT, 1, 0,
				CLK_SET_RATE_PARENT, 0, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c_out1", शून्य);
	clks[TEGRA210_CLK_PLL_C_OUT1] = clk;

	/* PLLC_UD */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_c_ud", "pll_c",
					CLK_SET_RATE_PARENT, 1, 1);
	clk_रेजिस्टर_clkdev(clk, "pll_c_ud", शून्य);
	clks[TEGRA210_CLK_PLL_C_UD] = clk;

	/* PLLC2 */
	clk = tegra_clk_रेजिस्टर_pllc_tegra210("pll_c2", "pll_ref", clk_base,
			     pmc, 0, &pll_c2_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c2", शून्य);
	clks[TEGRA210_CLK_PLL_C2] = clk;

	/* PLLC3 */
	clk = tegra_clk_रेजिस्टर_pllc_tegra210("pll_c3", "pll_ref", clk_base,
			     pmc, 0, &pll_c3_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c3", शून्य);
	clks[TEGRA210_CLK_PLL_C3] = clk;

	/* PLLM */
	clk = tegra_clk_रेजिस्टर_pllm("pll_m", "osc", clk_base, pmc,
			     CLK_SET_RATE_GATE, &pll_m_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_m", शून्य);
	clks[TEGRA210_CLK_PLL_M] = clk;

	/* PLLMB */
	clk = tegra_clk_रेजिस्टर_pllmb("pll_mb", "osc", clk_base, pmc,
			     CLK_SET_RATE_GATE, &pll_mb_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_mb", शून्य);
	clks[TEGRA210_CLK_PLL_MB] = clk;

	/* PLLM_UD */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_m_ud", "pll_m",
					CLK_SET_RATE_PARENT, 1, 1);
	clk_रेजिस्टर_clkdev(clk, "pll_m_ud", शून्य);
	clks[TEGRA210_CLK_PLL_M_UD] = clk;

	/* PLLMB_UD */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_mb_ud", "pll_mb",
					CLK_SET_RATE_PARENT, 1, 1);
	clk_रेजिस्टर_clkdev(clk, "pll_mb_ud", शून्य);
	clks[TEGRA210_CLK_PLL_MB_UD] = clk;

	/* PLLP_UD */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_p_ud", "pll_p",
					0, 1, 1);
	clks[TEGRA210_CLK_PLL_P_UD] = clk;

	/* PLLU_VCO */
	अगर (!tegra210_init_pllu()) अणु
		clk = clk_रेजिस्टर_fixed_rate(शून्य, "pll_u_vco", "pll_ref", 0,
					      480*1000*1000);
		clk_रेजिस्टर_clkdev(clk, "pll_u_vco", शून्य);
		clks[TEGRA210_CLK_PLL_U] = clk;
	पूर्ण

	/* PLLU_OUT */
	clk = clk_रेजिस्टर_भागider_table(शून्य, "pll_u_out", "pll_u_vco", 0,
					 clk_base + PLLU_BASE, 16, 4, 0,
					 pll_vco_post_भाग_प्रकारable, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_u_out", शून्य);
	clks[TEGRA210_CLK_PLL_U_OUT] = clk;

	/* PLLU_OUT1 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_u_out1_div", "pll_u_out",
				clk_base + PLLU_OUTA, 0,
				TEGRA_DIVIDER_ROUND_UP,
				8, 8, 1, &pll_u_lock);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_u_out1", "pll_u_out1_div",
				clk_base + PLLU_OUTA, 1, 0,
				CLK_SET_RATE_PARENT, 0, &pll_u_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_u_out1", शून्य);
	clks[TEGRA210_CLK_PLL_U_OUT1] = clk;

	/* PLLU_OUT2 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_u_out2_div", "pll_u_out",
				clk_base + PLLU_OUTA, 0,
				TEGRA_DIVIDER_ROUND_UP,
				24, 8, 1, &pll_u_lock);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_u_out2", "pll_u_out2_div",
				clk_base + PLLU_OUTA, 17, 16,
				CLK_SET_RATE_PARENT, 0, &pll_u_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_u_out2", शून्य);
	clks[TEGRA210_CLK_PLL_U_OUT2] = clk;

	/* PLLU_480M */
	clk = clk_रेजिस्टर_gate(शून्य, "pll_u_480M", "pll_u_vco",
				CLK_SET_RATE_PARENT, clk_base + PLLU_BASE,
				22, 0, &pll_u_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_u_480M", शून्य);
	clks[TEGRA210_CLK_PLL_U_480M] = clk;

	/* PLLU_60M */
	clk = clk_रेजिस्टर_gate(शून्य, "pll_u_60M", "pll_u_out2",
				CLK_SET_RATE_PARENT, clk_base + PLLU_BASE,
				23, 0, &pll_u_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_u_60M", शून्य);
	clks[TEGRA210_CLK_PLL_U_60M] = clk;

	/* PLLU_48M */
	clk = clk_रेजिस्टर_gate(शून्य, "pll_u_48M", "pll_u_out1",
				CLK_SET_RATE_PARENT, clk_base + PLLU_BASE,
				25, 0, &pll_u_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_u_48M", शून्य);
	clks[TEGRA210_CLK_PLL_U_48M] = clk;

	/* PLLD */
	clk = tegra_clk_रेजिस्टर_pll("pll_d", "pll_ref", clk_base, pmc, 0,
			    &pll_d_params, &pll_d_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_d", शून्य);
	clks[TEGRA210_CLK_PLL_D] = clk;

	/* PLLD_OUT0 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_d_out0", "pll_d",
					CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll_d_out0", शून्य);
	clks[TEGRA210_CLK_PLL_D_OUT0] = clk;

	/* PLLRE */
	clk = tegra_clk_रेजिस्टर_pllre_tegra210("pll_re_vco", "pll_ref",
						clk_base, pmc, 0,
						&pll_re_vco_params,
						&pll_re_lock, pll_ref_freq);
	clk_रेजिस्टर_clkdev(clk, "pll_re_vco", शून्य);
	clks[TEGRA210_CLK_PLL_RE_VCO] = clk;

	clk = clk_रेजिस्टर_भागider_table(शून्य, "pll_re_out", "pll_re_vco", 0,
					 clk_base + PLLRE_BASE, 16, 5, 0,
					 pll_vco_post_भाग_प्रकारable, &pll_re_lock);
	clk_रेजिस्टर_clkdev(clk, "pll_re_out", शून्य);
	clks[TEGRA210_CLK_PLL_RE_OUT] = clk;

	clk = tegra_clk_रेजिस्टर_भागider("pll_re_out1_div", "pll_re_vco",
					 clk_base + PLLRE_OUT1, 0,
					 TEGRA_DIVIDER_ROUND_UP,
					 8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_re_out1", "pll_re_out1_div",
					 clk_base + PLLRE_OUT1, 1, 0,
					 CLK_SET_RATE_PARENT, 0, शून्य);
	clks[TEGRA210_CLK_PLL_RE_OUT1] = clk;

	/* PLLE */
	clk = tegra_clk_रेजिस्टर_plle_tegra210("pll_e", "pll_ref",
				      clk_base, 0, &pll_e_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_e", शून्य);
	clks[TEGRA210_CLK_PLL_E] = clk;

	/* PLLC4 */
	clk = tegra_clk_रेजिस्टर_pllre("pll_c4_vco", "pll_ref", clk_base, pmc,
			     0, &pll_c4_vco_params, शून्य, pll_ref_freq);
	clk_रेजिस्टर_clkdev(clk, "pll_c4_vco", शून्य);
	clks[TEGRA210_CLK_PLL_C4] = clk;

	/* PLLC4_OUT0 */
	clk = clk_रेजिस्टर_भागider_table(शून्य, "pll_c4_out0", "pll_c4_vco", 0,
					 clk_base + PLLC4_BASE, 19, 4, 0,
					 pll_vco_post_भाग_प्रकारable, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c4_out0", शून्य);
	clks[TEGRA210_CLK_PLL_C4_OUT0] = clk;

	/* PLLC4_OUT1 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_c4_out1", "pll_c4_vco",
					CLK_SET_RATE_PARENT, 1, 3);
	clk_रेजिस्टर_clkdev(clk, "pll_c4_out1", शून्य);
	clks[TEGRA210_CLK_PLL_C4_OUT1] = clk;

	/* PLLC4_OUT2 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_c4_out2", "pll_c4_vco",
					CLK_SET_RATE_PARENT, 1, 5);
	clk_रेजिस्टर_clkdev(clk, "pll_c4_out2", शून्य);
	clks[TEGRA210_CLK_PLL_C4_OUT2] = clk;

	/* PLLC4_OUT3 */
	clk = tegra_clk_रेजिस्टर_भागider("pll_c4_out3_div", "pll_c4_out0",
			clk_base + PLLC4_OUT, 0, TEGRA_DIVIDER_ROUND_UP,
			8, 8, 1, शून्य);
	clk = tegra_clk_रेजिस्टर_pll_out("pll_c4_out3", "pll_c4_out3_div",
				clk_base + PLLC4_OUT, 1, 0,
				CLK_SET_RATE_PARENT, 0, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_c4_out3", शून्य);
	clks[TEGRA210_CLK_PLL_C4_OUT3] = clk;

	/* PLLDP */
	clk = tegra_clk_रेजिस्टर_pllss_tegra210("pll_dp", "pll_ref", clk_base,
					0, &pll_dp_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_dp", शून्य);
	clks[TEGRA210_CLK_PLL_DP] = clk;

	/* PLLD2 */
	clk = tegra_clk_रेजिस्टर_pllss_tegra210("pll_d2", "pll_ref", clk_base,
					0, &pll_d2_params, शून्य);
	clk_रेजिस्टर_clkdev(clk, "pll_d2", शून्य);
	clks[TEGRA210_CLK_PLL_D2] = clk;

	/* PLLD2_OUT0 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_d2_out0", "pll_d2",
					CLK_SET_RATE_PARENT, 1, 1);
	clk_रेजिस्टर_clkdev(clk, "pll_d2_out0", शून्य);
	clks[TEGRA210_CLK_PLL_D2_OUT0] = clk;

	/* PLLP_OUT2 */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pll_p_out2", "pll_p",
					CLK_SET_RATE_PARENT, 1, 2);
	clk_रेजिस्टर_clkdev(clk, "pll_p_out2", शून्य);
	clks[TEGRA210_CLK_PLL_P_OUT2] = clk;

पूर्ण

/* Tegra210 CPU घड़ी and reset control functions */
अटल व्योम tegra210_रुको_cpu_in_reset(u32 cpu)
अणु
	अचिन्हित पूर्णांक reg;

	करो अणु
		reg = पढ़ोl(clk_base + CLK_RST_CONTROLLER_CPU_CMPLX_STATUS);
		cpu_relax();
	पूर्ण जबतक (!(reg & (1 << cpu)));  /* check CPU been reset or not */
पूर्ण

अटल व्योम tegra210_disable_cpu_घड़ी(u32 cpu)
अणु
	/* flow controller would take care in the घातer sequence. */
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा car_पढ़ोl(_base, _off) पढ़ोl_relaxed(clk_base + (_base) + ((_off) * 4))
#घोषणा car_ग_लिखोl(_val, _base, _off) \
		ग_लिखोl_relaxed(_val, clk_base + (_base) + ((_off) * 4))

अटल u32 spare_reg_ctx, misc_clk_enb_ctx, clk_msk_arm_ctx;
अटल u32 cpu_softrst_ctx[3];

अटल पूर्णांक tegra210_clk_suspend(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	clk_save_context();

	/*
	 * Save the bootloader configured घड़ी रेजिस्टरs SPARE_REG0,
	 * MISC_CLK_ENB, CLK_MASK_ARM, CPU_SOFTRST_CTRL.
	 */
	spare_reg_ctx = पढ़ोl_relaxed(clk_base + SPARE_REG0);
	misc_clk_enb_ctx = पढ़ोl_relaxed(clk_base + MISC_CLK_ENB);
	clk_msk_arm_ctx = पढ़ोl_relaxed(clk_base + CLK_MASK_ARM);

	क्रम (i = 0; i < ARRAY_SIZE(cpu_softrst_ctx); i++)
		cpu_softrst_ctx[i] = car_पढ़ोl(CPU_SOFTRST_CTRL, i);

	tegra_clk_periph_suspend();
	वापस 0;
पूर्ण

अटल व्योम tegra210_clk_resume(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	tegra_clk_osc_resume(clk_base);

	/*
	 * Restore the bootloader configured घड़ी रेजिस्टरs SPARE_REG0,
	 * MISC_CLK_ENB, CLK_MASK_ARM, CPU_SOFTRST_CTRL from saved context.
	 */
	ग_लिखोl_relaxed(spare_reg_ctx, clk_base + SPARE_REG0);
	ग_लिखोl_relaxed(misc_clk_enb_ctx, clk_base + MISC_CLK_ENB);
	ग_लिखोl_relaxed(clk_msk_arm_ctx, clk_base + CLK_MASK_ARM);

	क्रम (i = 0; i < ARRAY_SIZE(cpu_softrst_ctx); i++)
		car_ग_लिखोl(cpu_softrst_ctx[i], CPU_SOFTRST_CTRL, i);

	/*
	 * Tegra घड़ी programming sequence recommends peripheral घड़ी to
	 * be enabled prior to changing its घड़ी source and भागider to
	 * prevent glitchless frequency चयन.
	 * So, enable all peripheral घड़ीs beक्रमe restoring their source
	 * and भागiders.
	 */
	ग_लिखोl_relaxed(TEGRA210_CLK_ENB_VLD_MSK_L, clk_base + CLK_OUT_ENB_L);
	ग_लिखोl_relaxed(TEGRA210_CLK_ENB_VLD_MSK_H, clk_base + CLK_OUT_ENB_H);
	ग_लिखोl_relaxed(TEGRA210_CLK_ENB_VLD_MSK_U, clk_base + CLK_OUT_ENB_U);
	ग_लिखोl_relaxed(TEGRA210_CLK_ENB_VLD_MSK_V, clk_base + CLK_OUT_ENB_V);
	ग_लिखोl_relaxed(TEGRA210_CLK_ENB_VLD_MSK_W, clk_base + CLK_OUT_ENB_W);
	ग_लिखोl_relaxed(TEGRA210_CLK_ENB_VLD_MSK_X, clk_base + CLK_OUT_ENB_X);
	ग_लिखोl_relaxed(TEGRA210_CLK_ENB_VLD_MSK_Y, clk_base + CLK_OUT_ENB_Y);

	/* रुको क्रम all ग_लिखोs to happen to have all the घड़ीs enabled */
	fence_udelay(2, clk_base);

	/* restore PLLs and all peripheral घड़ी rates */
	tegra210_init_pllu();
	clk_restore_context();

	/* restore saved context of peripheral घड़ीs and reset state */
	tegra_clk_periph_resume();
पूर्ण

अटल व्योम tegra210_cpu_घड़ी_suspend(व्योम)
अणु
	/* चयन coresite to clk_m, save off original source */
	tegra210_cpu_clk_sctx.clk_csite_src =
				पढ़ोl(clk_base + CLK_SOURCE_CSITE);
	ग_लिखोl(3 << 30, clk_base + CLK_SOURCE_CSITE);
पूर्ण

अटल व्योम tegra210_cpu_घड़ी_resume(व्योम)
अणु
	ग_लिखोl(tegra210_cpu_clk_sctx.clk_csite_src,
				clk_base + CLK_SOURCE_CSITE);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा syscore_ops tegra_clk_syscore_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend = tegra210_clk_suspend,
	.resume = tegra210_clk_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा tegra_cpu_car_ops tegra210_cpu_car_ops = अणु
	.रुको_क्रम_reset	= tegra210_रुको_cpu_in_reset,
	.disable_घड़ी	= tegra210_disable_cpu_घड़ी,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= tegra210_cpu_घड़ी_suspend,
	.resume		= tegra210_cpu_घड़ी_resume,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा of_device_id pmc_match[] __initस्थिर = अणु
	अणु .compatible = "nvidia,tegra210-pmc" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा tegra_clk_init_table init_table[] __initdata = अणु
	अणु TEGRA210_CLK_UARTA, TEGRA210_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA210_CLK_UARTB, TEGRA210_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA210_CLK_UARTC, TEGRA210_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA210_CLK_UARTD, TEGRA210_CLK_PLL_P, 408000000, 0 पूर्ण,
	अणु TEGRA210_CLK_PLL_A, TEGRA210_CLK_CLK_MAX, 564480000, 0 पूर्ण,
	अणु TEGRA210_CLK_PLL_A_OUT0, TEGRA210_CLK_CLK_MAX, 11289600, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S0, TEGRA210_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S1, TEGRA210_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S2, TEGRA210_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S3, TEGRA210_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S4, TEGRA210_CLK_PLL_A_OUT0, 11289600, 0 पूर्ण,
	अणु TEGRA210_CLK_HOST1X, TEGRA210_CLK_PLL_P, 136000000, 1 पूर्ण,
	अणु TEGRA210_CLK_SCLK_MUX, TEGRA210_CLK_PLL_P, 0, 1 पूर्ण,
	अणु TEGRA210_CLK_SCLK, TEGRA210_CLK_CLK_MAX, 102000000, 0 पूर्ण,
	अणु TEGRA210_CLK_DFLL_SOC, TEGRA210_CLK_PLL_P, 51000000, 1 पूर्ण,
	अणु TEGRA210_CLK_DFLL_REF, TEGRA210_CLK_PLL_P, 51000000, 1 पूर्ण,
	अणु TEGRA210_CLK_SBC4, TEGRA210_CLK_PLL_P, 12000000, 1 पूर्ण,
	अणु TEGRA210_CLK_PLL_U_OUT1, TEGRA210_CLK_CLK_MAX, 48000000, 1 पूर्ण,
	अणु TEGRA210_CLK_XUSB_GATE, TEGRA210_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA210_CLK_XUSB_SS_SRC, TEGRA210_CLK_PLL_U_480M, 120000000, 0 पूर्ण,
	अणु TEGRA210_CLK_XUSB_FS_SRC, TEGRA210_CLK_PLL_U_48M, 48000000, 0 पूर्ण,
	अणु TEGRA210_CLK_XUSB_HS_SRC, TEGRA210_CLK_XUSB_SS_SRC, 120000000, 0 पूर्ण,
	अणु TEGRA210_CLK_XUSB_SSP_SRC, TEGRA210_CLK_XUSB_SS_SRC, 120000000, 0 पूर्ण,
	अणु TEGRA210_CLK_XUSB_FALCON_SRC, TEGRA210_CLK_PLL_P_OUT_XUSB, 204000000, 0 पूर्ण,
	अणु TEGRA210_CLK_XUSB_HOST_SRC, TEGRA210_CLK_PLL_P_OUT_XUSB, 102000000, 0 पूर्ण,
	अणु TEGRA210_CLK_XUSB_DEV_SRC, TEGRA210_CLK_PLL_P_OUT_XUSB, 102000000, 0 पूर्ण,
	अणु TEGRA210_CLK_SATA, TEGRA210_CLK_PLL_P, 104000000, 0 पूर्ण,
	अणु TEGRA210_CLK_SATA_OOB, TEGRA210_CLK_PLL_P, 204000000, 0 पूर्ण,
	अणु TEGRA210_CLK_MSELECT, TEGRA210_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA210_CLK_CSITE, TEGRA210_CLK_CLK_MAX, 0, 1 पूर्ण,
	/* TODO find a way to enable this on-demand */
	अणु TEGRA210_CLK_DBGAPB, TEGRA210_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA210_CLK_TSENSOR, TEGRA210_CLK_CLK_M, 400000, 0 पूर्ण,
	अणु TEGRA210_CLK_I2C1, TEGRA210_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA210_CLK_I2C2, TEGRA210_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA210_CLK_I2C3, TEGRA210_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA210_CLK_I2C4, TEGRA210_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA210_CLK_I2C5, TEGRA210_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA210_CLK_I2C6, TEGRA210_CLK_PLL_P, 0, 0 पूर्ण,
	अणु TEGRA210_CLK_PLL_DP, TEGRA210_CLK_CLK_MAX, 270000000, 0 पूर्ण,
	अणु TEGRA210_CLK_SOC_THERM, TEGRA210_CLK_PLL_P, 51000000, 0 पूर्ण,
	अणु TEGRA210_CLK_CCLK_G, TEGRA210_CLK_CLK_MAX, 0, 1 पूर्ण,
	अणु TEGRA210_CLK_PLL_U_OUT2, TEGRA210_CLK_CLK_MAX, 60000000, 1 पूर्ण,
	अणु TEGRA210_CLK_SPDIF_IN_SYNC, TEGRA210_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S0_SYNC, TEGRA210_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S1_SYNC, TEGRA210_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S2_SYNC, TEGRA210_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S3_SYNC, TEGRA210_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA210_CLK_I2S4_SYNC, TEGRA210_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA210_CLK_VIMCLK_SYNC, TEGRA210_CLK_CLK_MAX, 24576000, 0 पूर्ण,
	अणु TEGRA210_CLK_HDA, TEGRA210_CLK_PLL_P, 51000000, 0 पूर्ण,
	अणु TEGRA210_CLK_HDA2CODEC_2X, TEGRA210_CLK_PLL_P, 48000000, 0 पूर्ण,
	/* This MUST be the last entry. */
	अणु TEGRA210_CLK_CLK_MAX, TEGRA210_CLK_CLK_MAX, 0, 0 पूर्ण,
पूर्ण;

/**
 * tegra210_घड़ी_apply_init_table - initialize घड़ीs on Tegra210 SoCs
 *
 * Program an initial घड़ी rate and enable or disable घड़ीs needed
 * by the rest of the kernel, क्रम Tegra210 SoCs.  It is पूर्णांकended to be
 * called by assigning a poपूर्णांकer to it to tegra_clk_apply_init_table -
 * this will be called as an arch_initcall.  No वापस value.
 */
अटल व्योम __init tegra210_घड़ी_apply_init_table(व्योम)
अणु
	tegra_init_from_table(init_table, clks, TEGRA210_CLK_CLK_MAX);
पूर्ण

/**
 * tegra210_car_barrier - रुको क्रम pending ग_लिखोs to the CAR to complete
 *
 * Wait क्रम any outstanding ग_लिखोs to the CAR MMIO space from this CPU
 * to complete beक्रमe continuing execution.  No वापस value.
 */
अटल व्योम tegra210_car_barrier(व्योम)
अणु
	पढ़ोl_relaxed(clk_base + RST_DFLL_DVCO);
पूर्ण

/**
 * tegra210_घड़ी_निश्चित_dfll_dvco_reset - निश्चित the DFLL's DVCO reset
 *
 * Assert the reset line of the DFLL's DVCO.  No वापस value.
 */
अटल व्योम tegra210_घड़ी_निश्चित_dfll_dvco_reset(व्योम)
अणु
	u32 v;

	v = पढ़ोl_relaxed(clk_base + RST_DFLL_DVCO);
	v |= (1 << DVFS_DFLL_RESET_SHIFT);
	ग_लिखोl_relaxed(v, clk_base + RST_DFLL_DVCO);
	tegra210_car_barrier();
पूर्ण

/**
 * tegra210_घड़ी_deनिश्चित_dfll_dvco_reset - deनिश्चित the DFLL's DVCO reset
 *
 * Deनिश्चित the reset line of the DFLL's DVCO, allowing the DVCO to
 * operate.  No वापस value.
 */
अटल व्योम tegra210_घड़ी_deनिश्चित_dfll_dvco_reset(व्योम)
अणु
	u32 v;

	v = पढ़ोl_relaxed(clk_base + RST_DFLL_DVCO);
	v &= ~(1 << DVFS_DFLL_RESET_SHIFT);
	ग_लिखोl_relaxed(v, clk_base + RST_DFLL_DVCO);
	tegra210_car_barrier();
पूर्ण

अटल पूर्णांक tegra210_reset_निश्चित(अचिन्हित दीर्घ id)
अणु
	अगर (id == TEGRA210_RST_DFLL_DVCO)
		tegra210_घड़ी_निश्चित_dfll_dvco_reset();
	अन्यथा अगर (id == TEGRA210_RST_ADSP)
		ग_लिखोl(GENMASK(26, 21) | BIT(7),
			clk_base + CLK_RST_CONTROLLER_RST_DEV_Y_SET);
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_reset_deनिश्चित(अचिन्हित दीर्घ id)
अणु
	अगर (id == TEGRA210_RST_DFLL_DVCO)
		tegra210_घड़ी_deनिश्चित_dfll_dvco_reset();
	अन्यथा अगर (id == TEGRA210_RST_ADSP) अणु
		ग_लिखोl(BIT(21), clk_base + CLK_RST_CONTROLLER_RST_DEV_Y_CLR);
		/*
		 * Considering adsp cpu घड़ी (min: 12.5MHZ, max: 1GHz)
		 * a delay of 5us ensures that it's at least
		 * 6 * adsp_cpu_cycle_period दीर्घ.
		 */
		udelay(5);
		ग_लिखोl(GENMASK(26, 22) | BIT(7),
			clk_base + CLK_RST_CONTROLLER_RST_DEV_Y_CLR);
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम tegra210_mbist_clk_init(व्योम)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(tegra210_pg_mbist_war); i++) अणु
		अचिन्हित पूर्णांक num_clks = tegra210_pg_mbist_war[i].num_clks;
		काष्ठा clk_bulk_data *clk_data;

		अगर (!num_clks)
			जारी;

		clk_data = kदो_स्मृति_array(num_clks, माप(*clk_data),
					 GFP_KERNEL);
		अगर (WARN_ON(!clk_data))
			वापस;

		tegra210_pg_mbist_war[i].clks = clk_data;
		क्रम (j = 0; j < num_clks; j++) अणु
			पूर्णांक clk_id = tegra210_pg_mbist_war[i].clk_init_data[j];
			काष्ठा clk *clk = clks[clk_id];

			अगर (WARN(IS_ERR(clk), "clk_id: %d\n", clk_id)) अणु
				kमुक्त(clk_data);
				tegra210_pg_mbist_war[i].clks = शून्य;
				अवरोध;
			पूर्ण
			clk_data[j].clk = clk;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * tegra210_घड़ी_init - Tegra210-specअगरic घड़ी initialization
 * @np: काष्ठा device_node * of the DT node क्रम the SoC CAR IP block
 *
 * Register most SoC घड़ीs क्रम the Tegra210 प्रणाली-on-chip.  Intended
 * to be called by the OF init code when a DT node with the
 * "nvidia,tegra210-car" string is encountered, and declared with
 * CLK_OF_DECLARE.  No वापस value.
 */
अटल व्योम __init tegra210_घड़ी_init(काष्ठा device_node *np)
अणु
	काष्ठा device_node *node;
	u32 value, clk_m_भाग;

	clk_base = of_iomap(np, 0);
	अगर (!clk_base) अणु
		pr_err("ioremap tegra210 CAR failed\n");
		वापस;
	पूर्ण

	node = of_find_matching_node(शून्य, pmc_match);
	अगर (!node) अणु
		pr_err("Failed to find pmc node\n");
		WARN_ON(1);
		वापस;
	पूर्ण

	pmc_base = of_iomap(node, 0);
	अगर (!pmc_base) अणु
		pr_err("Can't map pmc registers\n");
		WARN_ON(1);
		वापस;
	पूर्ण

	ahub_base = ioremap(TEGRA210_AHUB_BASE, SZ_64K);
	अगर (!ahub_base) अणु
		pr_err("ioremap tegra210 APE failed\n");
		वापस;
	पूर्ण

	dispa_base = ioremap(TEGRA210_DISPA_BASE, SZ_256K);
	अगर (!dispa_base) अणु
		pr_err("ioremap tegra210 DISPA failed\n");
		वापस;
	पूर्ण

	vic_base = ioremap(TEGRA210_VIC_BASE, SZ_256K);
	अगर (!vic_base) अणु
		pr_err("ioremap tegra210 VIC failed\n");
		वापस;
	पूर्ण

	clks = tegra_clk_init(clk_base, TEGRA210_CLK_CLK_MAX,
			      TEGRA210_CAR_BANK_COUNT);
	अगर (!clks)
		वापस;

	value = पढ़ोl(clk_base + SPARE_REG0) >> CLK_M_DIVISOR_SHIFT;
	clk_m_भाग = (value & CLK_M_DIVISOR_MASK) + 1;

	अगर (tegra_osc_clk_init(clk_base, tegra210_clks, tegra210_input_freq,
			       ARRAY_SIZE(tegra210_input_freq), clk_m_भाग,
			       &osc_freq, &pll_ref_freq) < 0)
		वापस;

	tegra_fixed_clk_init(tegra210_clks);
	tegra210_pll_init(clk_base, pmc_base);
	tegra210_periph_clk_init(np, clk_base, pmc_base);
	tegra_audio_clk_init(clk_base, pmc_base, tegra210_clks,
			     tegra210_audio_plls,
			     ARRAY_SIZE(tegra210_audio_plls), 24576000);

	/* For Tegra210, PLLD is the only source क्रम DSIA & DSIB */
	value = पढ़ोl(clk_base + PLLD_BASE);
	value &= ~BIT(25);
	ग_लिखोl(value, clk_base + PLLD_BASE);

	tegra_clk_apply_init_table = tegra210_घड़ी_apply_init_table;

	tegra_super_clk_gen5_init(clk_base, pmc_base, tegra210_clks,
				  &pll_x_params);
	tegra_init_special_resets(2, tegra210_reset_निश्चित,
				  tegra210_reset_deनिश्चित);

	tegra_add_of_provider(np, of_clk_src_onecell_get);
	tegra_रेजिस्टर_devclks(devclks, ARRAY_SIZE(devclks));

	tegra210_mbist_clk_init();

	tegra_cpu_car_ops = &tegra210_cpu_car_ops;

	रेजिस्टर_syscore_ops(&tegra_clk_syscore_ops);
पूर्ण
CLK_OF_DECLARE(tegra210, "nvidia,tegra210-car", tegra210_घड़ी_init);
