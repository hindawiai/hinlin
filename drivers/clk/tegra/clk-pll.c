<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, 2013, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>

#समावेश "clk.h"

#घोषणा PLL_BASE_BYPASS BIT(31)
#घोषणा PLL_BASE_ENABLE BIT(30)
#घोषणा PLL_BASE_REF_ENABLE BIT(29)
#घोषणा PLL_BASE_OVERRIDE BIT(28)

#घोषणा PLL_BASE_DIVP_SHIFT 20
#घोषणा PLL_BASE_DIVP_WIDTH 3
#घोषणा PLL_BASE_DIVN_SHIFT 8
#घोषणा PLL_BASE_DIVN_WIDTH 10
#घोषणा PLL_BASE_DIVM_SHIFT 0
#घोषणा PLL_BASE_DIVM_WIDTH 5
#घोषणा PLLU_POST_DIVP_MASK 0x1

#घोषणा PLL_MISC_DCCON_SHIFT 20
#घोषणा PLL_MISC_CPCON_SHIFT 8
#घोषणा PLL_MISC_CPCON_WIDTH 4
#घोषणा PLL_MISC_CPCON_MASK ((1 << PLL_MISC_CPCON_WIDTH) - 1)
#घोषणा PLL_MISC_LFCON_SHIFT 4
#घोषणा PLL_MISC_LFCON_WIDTH 4
#घोषणा PLL_MISC_LFCON_MASK ((1 << PLL_MISC_LFCON_WIDTH) - 1)
#घोषणा PLL_MISC_VCOCON_SHIFT 0
#घोषणा PLL_MISC_VCOCON_WIDTH 4
#घोषणा PLL_MISC_VCOCON_MASK ((1 << PLL_MISC_VCOCON_WIDTH) - 1)

#घोषणा OUT_OF_TABLE_CPCON 8

#घोषणा PMC_PLLP_WB0_OVERRIDE 0xf8
#घोषणा PMC_PLLP_WB0_OVERRIDE_PLLM_ENABLE BIT(12)
#घोषणा PMC_PLLP_WB0_OVERRIDE_PLLM_OVERRIDE BIT(11)

#घोषणा PLL_POST_LOCK_DELAY 50

#घोषणा PLLDU_LFCON_SET_DIVN 600

#घोषणा PLLE_BASE_DIVCML_SHIFT 24
#घोषणा PLLE_BASE_DIVCML_MASK 0xf
#घोषणा PLLE_BASE_DIVP_SHIFT 16
#घोषणा PLLE_BASE_DIVP_WIDTH 6
#घोषणा PLLE_BASE_DIVN_SHIFT 8
#घोषणा PLLE_BASE_DIVN_WIDTH 8
#घोषणा PLLE_BASE_DIVM_SHIFT 0
#घोषणा PLLE_BASE_DIVM_WIDTH 8
#घोषणा PLLE_BASE_ENABLE BIT(31)

#घोषणा PLLE_MISC_SETUP_BASE_SHIFT 16
#घोषणा PLLE_MISC_SETUP_BASE_MASK (0xffff << PLLE_MISC_SETUP_BASE_SHIFT)
#घोषणा PLLE_MISC_LOCK_ENABLE BIT(9)
#घोषणा PLLE_MISC_READY BIT(15)
#घोषणा PLLE_MISC_SETUP_EX_SHIFT 2
#घोषणा PLLE_MISC_SETUP_EX_MASK (3 << PLLE_MISC_SETUP_EX_SHIFT)
#घोषणा PLLE_MISC_SETUP_MASK (PLLE_MISC_SETUP_BASE_MASK |	\
			      PLLE_MISC_SETUP_EX_MASK)
#घोषणा PLLE_MISC_SETUP_VALUE (7 << PLLE_MISC_SETUP_BASE_SHIFT)

#घोषणा PLLE_SS_CTRL 0x68
#घोषणा PLLE_SS_CNTL_BYPASS_SS BIT(10)
#घोषणा PLLE_SS_CNTL_INTERP_RESET BIT(11)
#घोषणा PLLE_SS_CNTL_SSC_BYP BIT(12)
#घोषणा PLLE_SS_CNTL_CENTER BIT(14)
#घोषणा PLLE_SS_CNTL_INVERT BIT(15)
#घोषणा PLLE_SS_DISABLE (PLLE_SS_CNTL_BYPASS_SS | PLLE_SS_CNTL_INTERP_RESET |\
				PLLE_SS_CNTL_SSC_BYP)
#घोषणा PLLE_SS_MAX_MASK 0x1ff
#घोषणा PLLE_SS_MAX_VAL_TEGRA114 0x25
#घोषणा PLLE_SS_MAX_VAL_TEGRA210 0x21
#घोषणा PLLE_SS_INC_MASK (0xff << 16)
#घोषणा PLLE_SS_INC_VAL (0x1 << 16)
#घोषणा PLLE_SS_INCINTRV_MASK (0x3f << 24)
#घोषणा PLLE_SS_INCINTRV_VAL_TEGRA114 (0x20 << 24)
#घोषणा PLLE_SS_INCINTRV_VAL_TEGRA210 (0x23 << 24)
#घोषणा PLLE_SS_COEFFICIENTS_MASK \
	(PLLE_SS_MAX_MASK | PLLE_SS_INC_MASK | PLLE_SS_INCINTRV_MASK)
#घोषणा PLLE_SS_COEFFICIENTS_VAL_TEGRA114 \
	(PLLE_SS_MAX_VAL_TEGRA114 | PLLE_SS_INC_VAL |\
	 PLLE_SS_INCINTRV_VAL_TEGRA114)
#घोषणा PLLE_SS_COEFFICIENTS_VAL_TEGRA210 \
	(PLLE_SS_MAX_VAL_TEGRA210 | PLLE_SS_INC_VAL |\
	 PLLE_SS_INCINTRV_VAL_TEGRA210)

#घोषणा PLLE_AUX_PLLP_SEL	BIT(2)
#घोषणा PLLE_AUX_USE_LOCKDET	BIT(3)
#घोषणा PLLE_AUX_ENABLE_SWCTL	BIT(4)
#घोषणा PLLE_AUX_SS_SWCTL	BIT(6)
#घोषणा PLLE_AUX_SEQ_ENABLE	BIT(24)
#घोषणा PLLE_AUX_SEQ_START_STATE BIT(25)
#घोषणा PLLE_AUX_PLLRE_SEL	BIT(28)
#घोषणा PLLE_AUX_SS_SEQ_INCLUDE	BIT(31)

#घोषणा XUSBIO_PLL_CFG0		0x51c
#घोषणा XUSBIO_PLL_CFG0_PADPLL_RESET_SWCTL	BIT(0)
#घोषणा XUSBIO_PLL_CFG0_CLK_ENABLE_SWCTL	BIT(2)
#घोषणा XUSBIO_PLL_CFG0_PADPLL_USE_LOCKDET	BIT(6)
#घोषणा XUSBIO_PLL_CFG0_SEQ_ENABLE		BIT(24)
#घोषणा XUSBIO_PLL_CFG0_SEQ_START_STATE		BIT(25)

#घोषणा SATA_PLL_CFG0		0x490
#घोषणा SATA_PLL_CFG0_PADPLL_RESET_SWCTL	BIT(0)
#घोषणा SATA_PLL_CFG0_PADPLL_USE_LOCKDET	BIT(2)
#घोषणा SATA_PLL_CFG0_SEQ_ENABLE		BIT(24)
#घोषणा SATA_PLL_CFG0_SEQ_START_STATE		BIT(25)

#घोषणा PLLE_MISC_PLLE_PTS	BIT(8)
#घोषणा PLLE_MISC_IDDQ_SW_VALUE	BIT(13)
#घोषणा PLLE_MISC_IDDQ_SW_CTRL	BIT(14)
#घोषणा PLLE_MISC_VREG_BG_CTRL_SHIFT	4
#घोषणा PLLE_MISC_VREG_BG_CTRL_MASK	(3 << PLLE_MISC_VREG_BG_CTRL_SHIFT)
#घोषणा PLLE_MISC_VREG_CTRL_SHIFT	2
#घोषणा PLLE_MISC_VREG_CTRL_MASK	(2 << PLLE_MISC_VREG_CTRL_SHIFT)

#घोषणा PLLCX_MISC_STROBE	BIT(31)
#घोषणा PLLCX_MISC_RESET	BIT(30)
#घोषणा PLLCX_MISC_SDM_DIV_SHIFT 28
#घोषणा PLLCX_MISC_SDM_DIV_MASK (0x3 << PLLCX_MISC_SDM_DIV_SHIFT)
#घोषणा PLLCX_MISC_FILT_DIV_SHIFT 26
#घोषणा PLLCX_MISC_FILT_DIV_MASK (0x3 << PLLCX_MISC_FILT_DIV_SHIFT)
#घोषणा PLLCX_MISC_ALPHA_SHIFT 18
#घोषणा PLLCX_MISC_DIV_LOW_RANGE \
		((0x1 << PLLCX_MISC_SDM_DIV_SHIFT) | \
		(0x1 << PLLCX_MISC_FILT_DIV_SHIFT))
#घोषणा PLLCX_MISC_DIV_HIGH_RANGE \
		((0x2 << PLLCX_MISC_SDM_DIV_SHIFT) | \
		(0x2 << PLLCX_MISC_FILT_DIV_SHIFT))
#घोषणा PLLCX_MISC_COEF_LOW_RANGE \
		((0x14 << PLLCX_MISC_KA_SHIFT) | (0x38 << PLLCX_MISC_KB_SHIFT))
#घोषणा PLLCX_MISC_KA_SHIFT 2
#घोषणा PLLCX_MISC_KB_SHIFT 9
#घोषणा PLLCX_MISC_DEFAULT (PLLCX_MISC_COEF_LOW_RANGE | \
			    (0x19 << PLLCX_MISC_ALPHA_SHIFT) | \
			    PLLCX_MISC_DIV_LOW_RANGE | \
			    PLLCX_MISC_RESET)
#घोषणा PLLCX_MISC1_DEFAULT 0x000d2308
#घोषणा PLLCX_MISC2_DEFAULT 0x30211200
#घोषणा PLLCX_MISC3_DEFAULT 0x200

#घोषणा PMC_SATA_PWRGT 0x1ac
#घोषणा PMC_SATA_PWRGT_PLLE_IDDQ_VALUE BIT(5)
#घोषणा PMC_SATA_PWRGT_PLLE_IDDQ_SWCTL BIT(4)

#घोषणा PLLSS_MISC_KCP		0
#घोषणा PLLSS_MISC_KVCO		0
#घोषणा PLLSS_MISC_SETUP	0
#घोषणा PLLSS_EN_SDM		0
#घोषणा PLLSS_EN_SSC		0
#घोषणा PLLSS_EN_DITHER2	0
#घोषणा PLLSS_EN_DITHER		1
#घोषणा PLLSS_SDM_RESET		0
#घोषणा PLLSS_CLAMP		0
#घोषणा PLLSS_SDM_SSC_MAX	0
#घोषणा PLLSS_SDM_SSC_MIN	0
#घोषणा PLLSS_SDM_SSC_STEP	0
#घोषणा PLLSS_SDM_DIN		0
#घोषणा PLLSS_MISC_DEFAULT ((PLLSS_MISC_KCP << 25) | \
			    (PLLSS_MISC_KVCO << 24) | \
			    PLLSS_MISC_SETUP)
#घोषणा PLLSS_CFG_DEFAULT ((PLLSS_EN_SDM << 31) | \
			   (PLLSS_EN_SSC << 30) | \
			   (PLLSS_EN_DITHER2 << 29) | \
			   (PLLSS_EN_DITHER << 28) | \
			   (PLLSS_SDM_RESET) << 27 | \
			   (PLLSS_CLAMP << 22))
#घोषणा PLLSS_CTRL1_DEFAULT \
			((PLLSS_SDM_SSC_MAX << 16) | PLLSS_SDM_SSC_MIN)
#घोषणा PLLSS_CTRL2_DEFAULT \
			((PLLSS_SDM_SSC_STEP << 16) | PLLSS_SDM_DIN)
#घोषणा PLLSS_LOCK_OVERRIDE	BIT(24)
#घोषणा PLLSS_REF_SRC_SEL_SHIFT	25
#घोषणा PLLSS_REF_SRC_SEL_MASK	(3 << PLLSS_REF_SRC_SEL_SHIFT)

#घोषणा UTMIP_PLL_CFG1 0x484
#घोषणा UTMIP_PLL_CFG1_XTAL_FREQ_COUNT(x) (((x) & 0xfff) << 0)
#घोषणा UTMIP_PLL_CFG1_ENABLE_DLY_COUNT(x) (((x) & 0x1f) << 27)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLL_ACTIVE_POWERDOWN BIT(12)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERDOWN BIT(14)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERUP BIT(15)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLLU_POWERDOWN BIT(16)
#घोषणा UTMIP_PLL_CFG1_FORCE_PLLU_POWERUP BIT(17)

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
#घोषणा UTMIP_PLL_CFG2_PHY_XTAL_CLOCKEN BIT(30)

#घोषणा UTMIPLL_HW_PWRDN_CFG0 0x52c
#घोषणा UTMIPLL_HW_PWRDN_CFG0_IDDQ_SWCTL BIT(0)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_IDDQ_OVERRIDE BIT(1)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_CLK_ENABLE_SWCTL BIT(2)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_SEQ_IN_SWCTL BIT(4)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_SEQ_RESET_INPUT_VALUE BIT(5)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_USE_LOCKDET BIT(6)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_SEQ_ENABLE BIT(24)
#घोषणा UTMIPLL_HW_PWRDN_CFG0_SEQ_START_STATE BIT(25)

#घोषणा PLLU_HW_PWRDN_CFG0 0x530
#घोषणा PLLU_HW_PWRDN_CFG0_CLK_SWITCH_SWCTL BIT(0)
#घोषणा PLLU_HW_PWRDN_CFG0_CLK_ENABLE_SWCTL BIT(2)
#घोषणा PLLU_HW_PWRDN_CFG0_USE_LOCKDET BIT(6)
#घोषणा PLLU_HW_PWRDN_CFG0_USE_SWITCH_DETECT BIT(7)
#घोषणा PLLU_HW_PWRDN_CFG0_SEQ_ENABLE BIT(24)
#घोषणा PLLU_HW_PWRDN_CFG0_IDDQ_PD_INCLUDE BIT(28)

#घोषणा XUSB_PLL_CFG0 0x534
#घोषणा XUSB_PLL_CFG0_UTMIPLL_LOCK_DLY 0x3ff
#घोषणा XUSB_PLL_CFG0_PLLU_LOCK_DLY (0x3ff << 14)

#घोषणा PLLU_BASE_CLKENABLE_USB BIT(21)
#घोषणा PLLU_BASE_OVERRIDE BIT(24)

#घोषणा pll_पढ़ोl(offset, p) पढ़ोl_relaxed(p->clk_base + offset)
#घोषणा pll_पढ़ोl_base(p) pll_पढ़ोl(p->params->base_reg, p)
#घोषणा pll_पढ़ोl_misc(p) pll_पढ़ोl(p->params->misc_reg, p)
#घोषणा pll_override_पढ़ोl(offset, p) पढ़ोl_relaxed(p->pmc + offset)
#घोषणा pll_पढ़ोl_sdm_din(p) pll_पढ़ोl(p->params->sdm_din_reg, p)
#घोषणा pll_पढ़ोl_sdm_ctrl(p) pll_पढ़ोl(p->params->sdm_ctrl_reg, p)

#घोषणा pll_ग_लिखोl(val, offset, p) ग_लिखोl_relaxed(val, p->clk_base + offset)
#घोषणा pll_ग_लिखोl_base(val, p) pll_ग_लिखोl(val, p->params->base_reg, p)
#घोषणा pll_ग_लिखोl_misc(val, p) pll_ग_लिखोl(val, p->params->misc_reg, p)
#घोषणा pll_override_ग_लिखोl(val, offset, p) ग_लिखोl(val, p->pmc + offset)
#घोषणा pll_ग_लिखोl_sdm_din(val, p) pll_ग_लिखोl(val, p->params->sdm_din_reg, p)
#घोषणा pll_ग_लिखोl_sdm_ctrl(val, p) pll_ग_लिखोl(val, p->params->sdm_ctrl_reg, p)

#घोषणा mask(w) ((1 << (w)) - 1)
#घोषणा भागm_mask(p) mask(p->params->भाग_nmp->भागm_width)
#घोषणा भागn_mask(p) mask(p->params->भाग_nmp->भागn_width)
#घोषणा भागp_mask(p) (p->params->flags & TEGRA_PLLU ? PLLU_POST_DIVP_MASK :\
		      mask(p->params->भाग_nmp->भागp_width))
#घोषणा sdm_din_mask(p) p->params->sdm_din_mask
#घोषणा sdm_en_mask(p) p->params->sdm_ctrl_en_mask

#घोषणा भागm_shअगरt(p) (p)->params->भाग_nmp->भागm_shअगरt
#घोषणा भागn_shअगरt(p) (p)->params->भाग_nmp->भागn_shअगरt
#घोषणा भागp_shअगरt(p) (p)->params->भाग_nmp->भागp_shअगरt

#घोषणा भागm_mask_shअगरted(p) (भागm_mask(p) << भागm_shअगरt(p))
#घोषणा भागn_mask_shअगरted(p) (भागn_mask(p) << भागn_shअगरt(p))
#घोषणा भागp_mask_shअगरted(p) (भागp_mask(p) << भागp_shअगरt(p))

#घोषणा भागm_max(p) (भागm_mask(p))
#घोषणा भागn_max(p) (भागn_mask(p))
#घोषणा भागp_max(p) (1 << (भागp_mask(p)))

#घोषणा sdin_din_to_data(din)	((u16)((din) ? : 0xFFFFU))
#घोषणा sdin_data_to_din(dat)	(((dat) == 0xFFFFU) ? 0 : (s16)dat)

अटल काष्ठा भाग_nmp शेष_nmp = अणु
	.भागn_shअगरt = PLL_BASE_DIVN_SHIFT,
	.भागn_width = PLL_BASE_DIVN_WIDTH,
	.भागm_shअगरt = PLL_BASE_DIVM_SHIFT,
	.भागm_width = PLL_BASE_DIVM_WIDTH,
	.भागp_shअगरt = PLL_BASE_DIVP_SHIFT,
	.भागp_width = PLL_BASE_DIVP_WIDTH,
पूर्ण;

अटल व्योम clk_pll_enable_lock(काष्ठा tegra_clk_pll *pll)
अणु
	u32 val;

	अगर (!(pll->params->flags & TEGRA_PLL_USE_LOCK))
		वापस;

	अगर (!(pll->params->flags & TEGRA_PLL_HAS_LOCK_ENABLE))
		वापस;

	val = pll_पढ़ोl_misc(pll);
	val |= BIT(pll->params->lock_enable_bit_idx);
	pll_ग_लिखोl_misc(val, pll);
पूर्ण

अटल पूर्णांक clk_pll_रुको_क्रम_lock(काष्ठा tegra_clk_pll *pll)
अणु
	पूर्णांक i;
	u32 val, lock_mask;
	व्योम __iomem *lock_addr;

	अगर (!(pll->params->flags & TEGRA_PLL_USE_LOCK)) अणु
		udelay(pll->params->lock_delay);
		वापस 0;
	पूर्ण

	lock_addr = pll->clk_base;
	अगर (pll->params->flags & TEGRA_PLL_LOCK_MISC)
		lock_addr += pll->params->misc_reg;
	अन्यथा
		lock_addr += pll->params->base_reg;

	lock_mask = pll->params->lock_mask;

	क्रम (i = 0; i < pll->params->lock_delay; i++) अणु
		val = पढ़ोl_relaxed(lock_addr);
		अगर ((val & lock_mask) == lock_mask) अणु
			udelay(PLL_POST_LOCK_DELAY);
			वापस 0;
		पूर्ण
		udelay(2); /* समयout = 2 * lock समय */
	पूर्ण

	pr_err("%s: Timed out waiting for pll %s lock\n", __func__,
	       clk_hw_get_name(&pll->hw));

	वापस -1;
पूर्ण

पूर्णांक tegra_pll_रुको_क्रम_lock(काष्ठा tegra_clk_pll *pll)
अणु
	वापस clk_pll_रुको_क्रम_lock(pll);
पूर्ण

अटल bool pllm_clk_is_gated_by_pmc(काष्ठा tegra_clk_pll *pll)
अणु
	u32 val = पढ़ोl_relaxed(pll->pmc + PMC_PLLP_WB0_OVERRIDE);

	वापस (val & PMC_PLLP_WB0_OVERRIDE_PLLM_OVERRIDE) &&
	      !(val & PMC_PLLP_WB0_OVERRIDE_PLLM_ENABLE);
पूर्ण

अटल पूर्णांक clk_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val;

	/*
	 * Power Management Controller (PMC) can override the PLLM घड़ी
	 * settings, including the enable-state. The PLLM is enabled when
	 * PLLM's CaR state is ON and when PLLM isn't gated by PMC.
	 */
	अगर ((pll->params->flags & TEGRA_PLLM) && pllm_clk_is_gated_by_pmc(pll))
		वापस 0;

	val = pll_पढ़ोl_base(pll);

	वापस val & PLL_BASE_ENABLE ? 1 : 0;
पूर्ण

अटल व्योम _clk_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val;

	अगर (pll->params->iddq_reg) अणु
		val = pll_पढ़ोl(pll->params->iddq_reg, pll);
		val &= ~BIT(pll->params->iddq_bit_idx);
		pll_ग_लिखोl(val, pll->params->iddq_reg, pll);
		udelay(5);
	पूर्ण

	अगर (pll->params->reset_reg) अणु
		val = pll_पढ़ोl(pll->params->reset_reg, pll);
		val &= ~BIT(pll->params->reset_bit_idx);
		pll_ग_लिखोl(val, pll->params->reset_reg, pll);
	पूर्ण

	clk_pll_enable_lock(pll);

	val = pll_पढ़ोl_base(pll);
	अगर (pll->params->flags & TEGRA_PLL_BYPASS)
		val &= ~PLL_BASE_BYPASS;
	val |= PLL_BASE_ENABLE;
	pll_ग_लिखोl_base(val, pll);

	अगर (pll->params->flags & TEGRA_PLLM) अणु
		val = पढ़ोl_relaxed(pll->pmc + PMC_PLLP_WB0_OVERRIDE);
		val |= PMC_PLLP_WB0_OVERRIDE_PLLM_ENABLE;
		ग_लिखोl_relaxed(val, pll->pmc + PMC_PLLP_WB0_OVERRIDE);
	पूर्ण
पूर्ण

अटल व्योम _clk_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val;

	val = pll_पढ़ोl_base(pll);
	अगर (pll->params->flags & TEGRA_PLL_BYPASS)
		val &= ~PLL_BASE_BYPASS;
	val &= ~PLL_BASE_ENABLE;
	pll_ग_लिखोl_base(val, pll);

	अगर (pll->params->flags & TEGRA_PLLM) अणु
		val = पढ़ोl_relaxed(pll->pmc + PMC_PLLP_WB0_OVERRIDE);
		val &= ~PMC_PLLP_WB0_OVERRIDE_PLLM_ENABLE;
		ग_लिखोl_relaxed(val, pll->pmc + PMC_PLLP_WB0_OVERRIDE);
	पूर्ण

	अगर (pll->params->reset_reg) अणु
		val = pll_पढ़ोl(pll->params->reset_reg, pll);
		val |= BIT(pll->params->reset_bit_idx);
		pll_ग_लिखोl(val, pll->params->reset_reg, pll);
	पूर्ण

	अगर (pll->params->iddq_reg) अणु
		val = pll_पढ़ोl(pll->params->iddq_reg, pll);
		val |= BIT(pll->params->iddq_bit_idx);
		pll_ग_लिखोl(val, pll->params->iddq_reg, pll);
		udelay(2);
	पूर्ण
पूर्ण

अटल व्योम pll_clk_start_ss(काष्ठा tegra_clk_pll *pll)
अणु
	अगर (pll->params->शेषs_set && pll->params->ssc_ctrl_reg) अणु
		u32 val = pll_पढ़ोl(pll->params->ssc_ctrl_reg, pll);

		val |= pll->params->ssc_ctrl_en_mask;
		pll_ग_लिखोl(val, pll->params->ssc_ctrl_reg, pll);
	पूर्ण
पूर्ण

अटल व्योम pll_clk_stop_ss(काष्ठा tegra_clk_pll *pll)
अणु
	अगर (pll->params->शेषs_set && pll->params->ssc_ctrl_reg) अणु
		u32 val = pll_पढ़ोl(pll->params->ssc_ctrl_reg, pll);

		val &= ~pll->params->ssc_ctrl_en_mask;
		pll_ग_लिखोl(val, pll->params->ssc_ctrl_reg, pll);
	पूर्ण
पूर्ण

अटल पूर्णांक clk_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	अगर (clk_pll_is_enabled(hw))
		वापस 0;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_clk_pll_enable(hw);

	ret = clk_pll_रुको_क्रम_lock(pll);

	pll_clk_start_ss(pll);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम clk_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ flags = 0;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	pll_clk_stop_ss(pll);

	_clk_pll_disable(hw);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);
पूर्ण

अटल पूर्णांक _p_भाग_प्रकारo_hw(काष्ठा clk_hw *hw, u8 p_भाग)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा pभाग_map *p_tohw = pll->params->pभाग_प्रकारohw;

	अगर (p_tohw) अणु
		जबतक (p_tohw->pभाग) अणु
			अगर (p_भाग <= p_tohw->pभाग)
				वापस p_tohw->hw_val;
			p_tohw++;
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक tegra_pll_p_भाग_प्रकारo_hw(काष्ठा tegra_clk_pll *pll, u8 p_भाग)
अणु
	वापस _p_भाग_प्रकारo_hw(&pll->hw, p_भाग);
पूर्ण

अटल पूर्णांक _hw_to_p_भाग(काष्ठा clk_hw *hw, u8 p_भाग_hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा pभाग_map *p_tohw = pll->params->pभाग_प्रकारohw;

	अगर (p_tohw) अणु
		जबतक (p_tohw->pभाग) अणु
			अगर (p_भाग_hw == p_tohw->hw_val)
				वापस p_tohw->pभाग;
			p_tohw++;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस 1 << p_भाग_hw;
पूर्ण

अटल पूर्णांक _get_table_rate(काष्ठा clk_hw *hw,
			   काष्ठा tegra_clk_pll_freq_table *cfg,
			   अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table *sel;
	पूर्णांक p;

	क्रम (sel = pll->params->freq_table; sel->input_rate != 0; sel++)
		अगर (sel->input_rate == parent_rate &&
		    sel->output_rate == rate)
			अवरोध;

	अगर (sel->input_rate == 0)
		वापस -EINVAL;

	अगर (pll->params->pभाग_प्रकारohw) अणु
		p = _p_भाग_प्रकारo_hw(hw, sel->p);
		अगर (p < 0)
			वापस p;
	पूर्ण अन्यथा अणु
		p = ilog2(sel->p);
	पूर्ण

	cfg->input_rate = sel->input_rate;
	cfg->output_rate = sel->output_rate;
	cfg->m = sel->m;
	cfg->n = sel->n;
	cfg->p = p;
	cfg->cpcon = sel->cpcon;
	cfg->sdm_data = sel->sdm_data;

	वापस 0;
पूर्ण

अटल पूर्णांक _calc_rate(काष्ठा clk_hw *hw, काष्ठा tegra_clk_pll_freq_table *cfg,
		      अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ cfreq;
	u32 p_भाग = 0;
	पूर्णांक ret;

	चयन (parent_rate) अणु
	हाल 12000000:
	हाल 26000000:
		cfreq = (rate <= 1000000 * 1000) ? 1000000 : 2000000;
		अवरोध;
	हाल 13000000:
		cfreq = (rate <= 1000000 * 1000) ? 1000000 : 2600000;
		अवरोध;
	हाल 16800000:
	हाल 19200000:
		cfreq = (rate <= 1200000 * 1000) ? 1200000 : 2400000;
		अवरोध;
	हाल 9600000:
	हाल 28800000:
		/*
		 * PLL_P_OUT1 rate is not listed in PLLA table
		 */
		cfreq = parent_rate / (parent_rate / 1000000);
		अवरोध;
	शेष:
		pr_err("%s Unexpected reference rate %lu\n",
		       __func__, parent_rate);
		BUG();
	पूर्ण

	/* Raise VCO to guarantee 0.5% accuracy */
	क्रम (cfg->output_rate = rate; cfg->output_rate < 200 * cfreq;
	     cfg->output_rate <<= 1)
		p_भाग++;

	cfg->m = parent_rate / cfreq;
	cfg->n = cfg->output_rate / cfreq;
	cfg->cpcon = OUT_OF_TABLE_CPCON;

	अगर (cfg->m == 0 || cfg->m > भागm_max(pll) ||
	    cfg->n > भागn_max(pll) || (1 << p_भाग) > भागp_max(pll) ||
	    cfg->output_rate > pll->params->vco_max) अणु
		वापस -EINVAL;
	पूर्ण

	cfg->output_rate = cfg->n * DIV_ROUND_UP(parent_rate, cfg->m);
	cfg->output_rate >>= p_भाग;

	अगर (pll->params->pभाग_प्रकारohw) अणु
		ret = _p_भाग_प्रकारo_hw(hw, 1 << p_भाग);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			cfg->p = ret;
	पूर्ण अन्यथा
		cfg->p = p_भाग;

	वापस 0;
पूर्ण

/*
 * SDM (Sigma Delta Modulator) भागisor is 16-bit 2's complement चिन्हित number
 * within (-2^12 ... 2^12-1) range. Represented in PLL data काष्ठाure as
 * अचिन्हित 16-bit value, with "0" भागisor mapped to 0xFFFF. Data "0" is used
 * to indicate that SDM is disabled.
 *
 * Effective nभाग value when SDM is enabled: nभाग + 1/2 + sdm_din/2^13
 */
अटल व्योम clk_pll_set_sdm_data(काष्ठा clk_hw *hw,
				 काष्ठा tegra_clk_pll_freq_table *cfg)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val;
	bool enabled;

	अगर (!pll->params->sdm_din_reg)
		वापस;

	अगर (cfg->sdm_data) अणु
		val = pll_पढ़ोl_sdm_din(pll) & (~sdm_din_mask(pll));
		val |= sdin_data_to_din(cfg->sdm_data) & sdm_din_mask(pll);
		pll_ग_लिखोl_sdm_din(val, pll);
	पूर्ण

	val = pll_पढ़ोl_sdm_ctrl(pll);
	enabled = (val & sdm_en_mask(pll));

	अगर (cfg->sdm_data == 0 && enabled)
		val &= ~pll->params->sdm_ctrl_en_mask;

	अगर (cfg->sdm_data != 0 && !enabled)
		val |= pll->params->sdm_ctrl_en_mask;

	pll_ग_लिखोl_sdm_ctrl(val, pll);
पूर्ण

अटल व्योम _update_pll_mnp(काष्ठा tegra_clk_pll *pll,
			    काष्ठा tegra_clk_pll_freq_table *cfg)
अणु
	u32 val;
	काष्ठा tegra_clk_pll_params *params = pll->params;
	काष्ठा भाग_nmp *भाग_nmp = params->भाग_nmp;

	अगर ((params->flags & (TEGRA_PLLM | TEGRA_PLLMB)) &&
		(pll_override_पढ़ोl(PMC_PLLP_WB0_OVERRIDE, pll) &
			PMC_PLLP_WB0_OVERRIDE_PLLM_OVERRIDE)) अणु
		val = pll_override_पढ़ोl(params->pmc_भागp_reg, pll);
		val &= ~(भागp_mask(pll) << भाग_nmp->override_भागp_shअगरt);
		val |= cfg->p << भाग_nmp->override_भागp_shअगरt;
		pll_override_ग_लिखोl(val, params->pmc_भागp_reg, pll);

		val = pll_override_पढ़ोl(params->pmc_भागnm_reg, pll);
		val &= ~((भागm_mask(pll) << भाग_nmp->override_भागm_shअगरt) |
			(भागn_mask(pll) << भाग_nmp->override_भागn_shअगरt));
		val |= (cfg->m << भाग_nmp->override_भागm_shअगरt) |
			(cfg->n << भाग_nmp->override_भागn_shअगरt);
		pll_override_ग_लिखोl(val, params->pmc_भागnm_reg, pll);
	पूर्ण अन्यथा अणु
		val = pll_पढ़ोl_base(pll);

		val &= ~(भागm_mask_shअगरted(pll) | भागn_mask_shअगरted(pll) |
			 भागp_mask_shअगरted(pll));

		val |= (cfg->m << भागm_shअगरt(pll)) |
		       (cfg->n << भागn_shअगरt(pll)) |
		       (cfg->p << भागp_shअगरt(pll));

		pll_ग_लिखोl_base(val, pll);

		clk_pll_set_sdm_data(&pll->hw, cfg);
	पूर्ण
पूर्ण

अटल व्योम _get_pll_mnp(काष्ठा tegra_clk_pll *pll,
			 काष्ठा tegra_clk_pll_freq_table *cfg)
अणु
	u32 val;
	काष्ठा tegra_clk_pll_params *params = pll->params;
	काष्ठा भाग_nmp *भाग_nmp = params->भाग_nmp;

	*cfg = (काष्ठा tegra_clk_pll_freq_table) अणु पूर्ण;

	अगर ((params->flags & (TEGRA_PLLM | TEGRA_PLLMB)) &&
		(pll_override_पढ़ोl(PMC_PLLP_WB0_OVERRIDE, pll) &
			PMC_PLLP_WB0_OVERRIDE_PLLM_OVERRIDE)) अणु
		val = pll_override_पढ़ोl(params->pmc_भागp_reg, pll);
		cfg->p = (val >> भाग_nmp->override_भागp_shअगरt) & भागp_mask(pll);

		val = pll_override_पढ़ोl(params->pmc_भागnm_reg, pll);
		cfg->m = (val >> भाग_nmp->override_भागm_shअगरt) & भागm_mask(pll);
		cfg->n = (val >> भाग_nmp->override_भागn_shअगरt) & भागn_mask(pll);
	पूर्ण  अन्यथा अणु
		val = pll_पढ़ोl_base(pll);

		cfg->m = (val >> भाग_nmp->भागm_shअगरt) & भागm_mask(pll);
		cfg->n = (val >> भाग_nmp->भागn_shअगरt) & भागn_mask(pll);
		cfg->p = (val >> भाग_nmp->भागp_shअगरt) & भागp_mask(pll);

		अगर (pll->params->sdm_din_reg) अणु
			अगर (sdm_en_mask(pll) & pll_पढ़ोl_sdm_ctrl(pll)) अणु
				val = pll_पढ़ोl_sdm_din(pll);
				val &= sdm_din_mask(pll);
				cfg->sdm_data = sdin_din_to_data(val);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _update_pll_cpcon(काष्ठा tegra_clk_pll *pll,
			      काष्ठा tegra_clk_pll_freq_table *cfg,
			      अचिन्हित दीर्घ rate)
अणु
	u32 val;

	val = pll_पढ़ोl_misc(pll);

	val &= ~(PLL_MISC_CPCON_MASK << PLL_MISC_CPCON_SHIFT);
	val |= cfg->cpcon << PLL_MISC_CPCON_SHIFT;

	अगर (pll->params->flags & TEGRA_PLL_SET_LFCON) अणु
		val &= ~(PLL_MISC_LFCON_MASK << PLL_MISC_LFCON_SHIFT);
		अगर (cfg->n >= PLLDU_LFCON_SET_DIVN)
			val |= 1 << PLL_MISC_LFCON_SHIFT;
	पूर्ण अन्यथा अगर (pll->params->flags & TEGRA_PLL_SET_DCCON) अणु
		val &= ~(1 << PLL_MISC_DCCON_SHIFT);
		अगर (rate >= (pll->params->vco_max >> 1))
			val |= 1 << PLL_MISC_DCCON_SHIFT;
	पूर्ण

	pll_ग_लिखोl_misc(val, pll);
पूर्ण

अटल पूर्णांक _program_pll(काष्ठा clk_hw *hw, काष्ठा tegra_clk_pll_freq_table *cfg,
			अचिन्हित दीर्घ rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table old_cfg;
	पूर्णांक state, ret = 0;

	state = clk_pll_is_enabled(hw);

	अगर (state && pll->params->pre_rate_change) अणु
		ret = pll->params->pre_rate_change();
		अगर (WARN_ON(ret))
			वापस ret;
	पूर्ण

	_get_pll_mnp(pll, &old_cfg);

	अगर (state && pll->params->शेषs_set && pll->params->dyn_ramp &&
			(cfg->m == old_cfg.m) && (cfg->p == old_cfg.p)) अणु
		ret = pll->params->dyn_ramp(pll, cfg);
		अगर (!ret)
			जाओ करोne;
	पूर्ण

	अगर (state) अणु
		pll_clk_stop_ss(pll);
		_clk_pll_disable(hw);
	पूर्ण

	अगर (!pll->params->शेषs_set && pll->params->set_शेषs)
		pll->params->set_शेषs(pll);

	_update_pll_mnp(pll, cfg);

	अगर (pll->params->flags & TEGRA_PLL_HAS_CPCON)
		_update_pll_cpcon(pll, cfg, rate);

	अगर (state) अणु
		_clk_pll_enable(hw);
		ret = clk_pll_रुको_क्रम_lock(pll);
		pll_clk_start_ss(pll);
	पूर्ण

करोne:
	अगर (state && pll->params->post_rate_change)
		pll->params->post_rate_change();

	वापस ret;
पूर्ण

अटल पूर्णांक clk_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table cfg, old_cfg;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = 0;

	अगर (pll->params->flags & TEGRA_PLL_FIXED) अणु
		अगर (rate != pll->params->fixed_rate) अणु
			pr_err("%s: Can not change %s fixed rate %lu to %lu\n",
				__func__, clk_hw_get_name(hw),
				pll->params->fixed_rate, rate);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (_get_table_rate(hw, &cfg, rate, parent_rate) &&
	    pll->params->calc_rate(hw, &cfg, rate, parent_rate)) अणु
		pr_err("%s: Failed to set %s rate %lu\n", __func__,
		       clk_hw_get_name(hw), rate);
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_get_pll_mnp(pll, &old_cfg);
	अगर (pll->params->flags & TEGRA_PLL_VCO_OUT)
		cfg.p = old_cfg.p;

	अगर (old_cfg.m != cfg.m || old_cfg.n != cfg.n || old_cfg.p != cfg.p ||
		old_cfg.sdm_data != cfg.sdm_data)
		ret = _program_pll(hw, &cfg, rate);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल दीर्घ clk_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *prate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table cfg;

	अगर (pll->params->flags & TEGRA_PLL_FIXED) अणु
		/* PLLM/MB are used क्रम memory; we करो not change rate */
		अगर (pll->params->flags & (TEGRA_PLLM | TEGRA_PLLMB))
			वापस clk_hw_get_rate(hw);
		वापस pll->params->fixed_rate;
	पूर्ण

	अगर (_get_table_rate(hw, &cfg, rate, *prate) &&
	    pll->params->calc_rate(hw, &cfg, rate, *prate))
		वापस -EINVAL;

	वापस cfg.output_rate;
पूर्ण

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table cfg;
	u32 val;
	u64 rate = parent_rate;
	पूर्णांक pभाग;

	val = pll_पढ़ोl_base(pll);

	अगर ((pll->params->flags & TEGRA_PLL_BYPASS) && (val & PLL_BASE_BYPASS))
		वापस parent_rate;

	अगर ((pll->params->flags & TEGRA_PLL_FIXED) &&
	    !(pll->params->flags & (TEGRA_PLLM | TEGRA_PLLMB)) &&
			!(val & PLL_BASE_OVERRIDE)) अणु
		काष्ठा tegra_clk_pll_freq_table sel;
		अगर (_get_table_rate(hw, &sel, pll->params->fixed_rate,
					parent_rate)) अणु
			pr_err("Clock %s has unknown fixed frequency\n",
			       clk_hw_get_name(hw));
			BUG();
		पूर्ण
		वापस pll->params->fixed_rate;
	पूर्ण

	_get_pll_mnp(pll, &cfg);

	अगर (pll->params->flags & TEGRA_PLL_VCO_OUT) अणु
		pभाग = 1;
	पूर्ण अन्यथा अणु
		pभाग = _hw_to_p_भाग(hw, cfg.p);
		अगर (pभाग < 0) अणु
			WARN(1, "Clock %s has invalid pdiv value : 0x%x\n",
			     clk_hw_get_name(hw), cfg.p);
			pभाग = 1;
		पूर्ण
	पूर्ण

	अगर (pll->params->set_gain)
		pll->params->set_gain(&cfg);

	cfg.m *= pभाग;

	rate *= cfg.n;
	करो_भाग(rate, cfg.m);

	वापस rate;
पूर्ण

अटल पूर्णांक clk_plle_training(काष्ठा tegra_clk_pll *pll)
अणु
	u32 val;
	अचिन्हित दीर्घ समयout;

	अगर (!pll->pmc)
		वापस -ENOSYS;

	/*
	 * PLLE is alपढ़ोy disabled, and setup cleared;
	 * create falling edge on PLLE IDDQ input.
	 */
	val = पढ़ोl(pll->pmc + PMC_SATA_PWRGT);
	val |= PMC_SATA_PWRGT_PLLE_IDDQ_VALUE;
	ग_लिखोl(val, pll->pmc + PMC_SATA_PWRGT);

	val = पढ़ोl(pll->pmc + PMC_SATA_PWRGT);
	val |= PMC_SATA_PWRGT_PLLE_IDDQ_SWCTL;
	ग_लिखोl(val, pll->pmc + PMC_SATA_PWRGT);

	val = पढ़ोl(pll->pmc + PMC_SATA_PWRGT);
	val &= ~PMC_SATA_PWRGT_PLLE_IDDQ_VALUE;
	ग_लिखोl(val, pll->pmc + PMC_SATA_PWRGT);

	val = pll_पढ़ोl_misc(pll);

	समयout = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (1) अणु
		val = pll_पढ़ोl_misc(pll);
		अगर (val & PLLE_MISC_READY)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			pr_err("%s: timeout waiting for PLLE\n", __func__);
			वापस -EBUSY;
		पूर्ण
		udelay(300);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक clk_plle_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table sel;
	अचिन्हित दीर्घ input_rate;
	u32 val;
	पूर्णांक err;

	अगर (clk_pll_is_enabled(hw))
		वापस 0;

	input_rate = clk_hw_get_rate(clk_hw_get_parent(hw));

	अगर (_get_table_rate(hw, &sel, pll->params->fixed_rate, input_rate))
		वापस -EINVAL;

	clk_pll_disable(hw);

	val = pll_पढ़ोl_misc(pll);
	val &= ~(PLLE_MISC_LOCK_ENABLE | PLLE_MISC_SETUP_MASK);
	pll_ग_लिखोl_misc(val, pll);

	val = pll_पढ़ोl_misc(pll);
	अगर (!(val & PLLE_MISC_READY)) अणु
		err = clk_plle_training(pll);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pll->params->flags & TEGRA_PLLE_CONFIGURE) अणु
		/* configure भागiders */
		val = pll_पढ़ोl_base(pll);
		val &= ~(भागp_mask_shअगरted(pll) | भागn_mask_shअगरted(pll) |
			 भागm_mask_shअगरted(pll));
		val &= ~(PLLE_BASE_DIVCML_MASK << PLLE_BASE_DIVCML_SHIFT);
		val |= sel.m << भागm_shअगरt(pll);
		val |= sel.n << भागn_shअगरt(pll);
		val |= sel.p << भागp_shअगरt(pll);
		val |= sel.cpcon << PLLE_BASE_DIVCML_SHIFT;
		pll_ग_लिखोl_base(val, pll);
	पूर्ण

	val = pll_पढ़ोl_misc(pll);
	val |= PLLE_MISC_SETUP_VALUE;
	val |= PLLE_MISC_LOCK_ENABLE;
	pll_ग_लिखोl_misc(val, pll);

	val = पढ़ोl(pll->clk_base + PLLE_SS_CTRL);
	val &= ~PLLE_SS_COEFFICIENTS_MASK;
	val |= PLLE_SS_DISABLE;
	ग_लिखोl(val, pll->clk_base + PLLE_SS_CTRL);

	val = pll_पढ़ोl_base(pll);
	val |= (PLL_BASE_BYPASS | PLL_BASE_ENABLE);
	pll_ग_लिखोl_base(val, pll);

	clk_pll_रुको_क्रम_lock(pll);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_plle_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val = pll_पढ़ोl_base(pll);
	u32 भागn = 0, भागm = 0, भागp = 0;
	u64 rate = parent_rate;

	भागp = (val >> pll->params->भाग_nmp->भागp_shअगरt) & (भागp_mask(pll));
	भागn = (val >> pll->params->भाग_nmp->भागn_shअगरt) & (भागn_mask(pll));
	भागm = (val >> pll->params->भाग_nmp->भागm_shअगरt) & (भागm_mask(pll));
	भागm *= भागp;

	rate *= भागn;
	करो_भाग(rate, भागm);
	वापस rate;
पूर्ण

अटल व्योम tegra_clk_pll_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	अचिन्हित दीर्घ parent_rate = clk_hw_get_rate(parent);
	अचिन्हित दीर्घ rate = clk_hw_get_rate(hw);

	अगर (clk_pll_is_enabled(hw))
		वापस;

	अगर (pll->params->set_शेषs)
		pll->params->set_शेषs(pll);

	clk_pll_set_rate(hw, rate, parent_rate);

	अगर (!__clk_get_enable_count(hw->clk))
		clk_pll_disable(hw);
	अन्यथा
		clk_pll_enable(hw);
पूर्ण

स्थिर काष्ठा clk_ops tegra_clk_pll_ops = अणु
	.is_enabled = clk_pll_is_enabled,
	.enable = clk_pll_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pll_recalc_rate,
	.round_rate = clk_pll_round_rate,
	.set_rate = clk_pll_set_rate,
	.restore_context = tegra_clk_pll_restore_context,
पूर्ण;

स्थिर काष्ठा clk_ops tegra_clk_plle_ops = अणु
	.recalc_rate = clk_plle_recalc_rate,
	.is_enabled = clk_pll_is_enabled,
	.disable = clk_pll_disable,
	.enable = clk_plle_enable,
पूर्ण;

/*
 * Structure defining the fields क्रम USB UTMI घड़ीs Parameters.
 */
काष्ठा uपंचांगi_clk_param अणु
	/* Oscillator Frequency in Hz */
	u32 osc_frequency;
	/* UTMIP PLL Enable Delay Count  */
	u8 enable_delay_count;
	/* UTMIP PLL Stable count */
	u8 stable_count;
	/*  UTMIP PLL Active delay count */
	u8 active_delay_count;
	/* UTMIP PLL Xtal frequency count */
	u8 xtal_freq_count;
पूर्ण;

अटल स्थिर काष्ठा uपंचांगi_clk_param uपंचांगi_parameters[] = अणु
	अणु
		.osc_frequency = 13000000, .enable_delay_count = 0x02,
		.stable_count = 0x33, .active_delay_count = 0x05,
		.xtal_freq_count = 0x7f
	पूर्ण, अणु
		.osc_frequency = 19200000, .enable_delay_count = 0x03,
		.stable_count = 0x4b, .active_delay_count = 0x06,
		.xtal_freq_count = 0xbb
	पूर्ण, अणु
		.osc_frequency = 12000000, .enable_delay_count = 0x02,
		.stable_count = 0x2f, .active_delay_count = 0x04,
		.xtal_freq_count = 0x76
	पूर्ण, अणु
		.osc_frequency = 26000000, .enable_delay_count = 0x04,
		.stable_count = 0x66, .active_delay_count = 0x09,
		.xtal_freq_count = 0xfe
	पूर्ण, अणु
		.osc_frequency = 16800000, .enable_delay_count = 0x03,
		.stable_count = 0x41, .active_delay_count = 0x0a,
		.xtal_freq_count = 0xa4
	पूर्ण, अणु
		.osc_frequency = 38400000, .enable_delay_count = 0x0,
		.stable_count = 0x0, .active_delay_count = 0x6,
		.xtal_freq_count = 0x80
	पूर्ण,
पूर्ण;

अटल पूर्णांक clk_pllu_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा clk_hw *pll_ref = clk_hw_get_parent(hw);
	काष्ठा clk_hw *osc = clk_hw_get_parent(pll_ref);
	स्थिर काष्ठा uपंचांगi_clk_param *params = शून्य;
	अचिन्हित दीर्घ flags = 0, input_rate;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;
	u32 value;

	अगर (!osc) अणु
		pr_err("%s: failed to get OSC clock\n", __func__);
		वापस -EINVAL;
	पूर्ण

	input_rate = clk_hw_get_rate(osc);

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_clk_pll_enable(hw);

	ret = clk_pll_रुको_क्रम_lock(pll);
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(uपंचांगi_parameters); i++) अणु
		अगर (input_rate == uपंचांगi_parameters[i].osc_frequency) अणु
			params = &uपंचांगi_parameters[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!params) अणु
		pr_err("%s: unexpected input rate %lu Hz\n", __func__,
		       input_rate);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	value = pll_पढ़ोl_base(pll);
	value &= ~PLLU_BASE_OVERRIDE;
	pll_ग_लिखोl_base(value, pll);

	value = पढ़ोl_relaxed(pll->clk_base + UTMIP_PLL_CFG2);
	/* Program UTMIP PLL stable and active counts */
	value &= ~UTMIP_PLL_CFG2_STABLE_COUNT(~0);
	value |= UTMIP_PLL_CFG2_STABLE_COUNT(params->stable_count);
	value &= ~UTMIP_PLL_CFG2_ACTIVE_DLY_COUNT(~0);
	value |= UTMIP_PLL_CFG2_ACTIVE_DLY_COUNT(params->active_delay_count);
	/* Remove घातer करोwns from UTMIP PLL control bits */
	value &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_A_POWERDOWN;
	value &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_B_POWERDOWN;
	value &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_C_POWERDOWN;
	ग_लिखोl_relaxed(value, pll->clk_base + UTMIP_PLL_CFG2);

	value = पढ़ोl_relaxed(pll->clk_base + UTMIP_PLL_CFG1);
	/* Program UTMIP PLL delay and oscillator frequency counts */
	value &= ~UTMIP_PLL_CFG1_ENABLE_DLY_COUNT(~0);
	value |= UTMIP_PLL_CFG1_ENABLE_DLY_COUNT(params->enable_delay_count);
	value &= ~UTMIP_PLL_CFG1_XTAL_FREQ_COUNT(~0);
	value |= UTMIP_PLL_CFG1_XTAL_FREQ_COUNT(params->xtal_freq_count);
	/* Remove घातer करोwns from UTMIP PLL control bits */
	value &= ~UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERDOWN;
	value &= ~UTMIP_PLL_CFG1_FORCE_PLL_ACTIVE_POWERDOWN;
	value &= ~UTMIP_PLL_CFG1_FORCE_PLLU_POWERDOWN;
	ग_लिखोl_relaxed(value, pll->clk_base + UTMIP_PLL_CFG1);

out:
	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_clk_pllu_ops = अणु
	.is_enabled = clk_pll_is_enabled,
	.enable = clk_pllu_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pll_recalc_rate,
	.round_rate = clk_pll_round_rate,
	.set_rate = clk_pll_set_rate,
पूर्ण;

अटल पूर्णांक _pll_fixed_mभाग(काष्ठा tegra_clk_pll_params *pll_params,
			   अचिन्हित दीर्घ parent_rate)
अणु
	u16 mभाग = parent_rate / pll_params->cf_min;

	अगर (pll_params->flags & TEGRA_MDIV_NEW)
		वापस (!pll_params->mभाग_शेष ? mभाग :
			min(mभाग, pll_params->mभाग_शेष));

	अगर (pll_params->mभाग_शेष)
		वापस pll_params->mभाग_शेष;

	अगर (parent_rate > pll_params->cf_max)
		वापस 2;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक _calc_dynamic_ramp_rate(काष्ठा clk_hw *hw,
				काष्ठा tegra_clk_pll_freq_table *cfg,
				अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित पूर्णांक p;
	पूर्णांक p_भाग;

	अगर (!rate)
		वापस -EINVAL;

	p = DIV_ROUND_UP(pll->params->vco_min, rate);
	cfg->m = _pll_fixed_mभाग(pll->params, parent_rate);
	cfg->output_rate = rate * p;
	cfg->n = cfg->output_rate * cfg->m / parent_rate;
	cfg->input_rate = parent_rate;

	p_भाग = _p_भाग_प्रकारo_hw(hw, p);
	अगर (p_भाग < 0)
		वापस p_भाग;

	cfg->p = p_भाग;

	अगर (cfg->n > भागn_max(pll) || cfg->output_rate > pll->params->vco_max)
		वापस -EINVAL;

	वापस 0;
पूर्ण

#अगर defined(CONFIG_ARCH_TEGRA_114_SOC) || \
	defined(CONFIG_ARCH_TEGRA_124_SOC) || \
	defined(CONFIG_ARCH_TEGRA_132_SOC) || \
	defined(CONFIG_ARCH_TEGRA_210_SOC)

u16 tegra_pll_get_fixed_mभाग(काष्ठा clk_hw *hw, अचिन्हित दीर्घ input_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);

	वापस (u16)_pll_fixed_mभाग(pll->params, input_rate);
पूर्ण

अटल अचिन्हित दीर्घ _clip_vco_min(अचिन्हित दीर्घ vco_min,
				   अचिन्हित दीर्घ parent_rate)
अणु
	वापस DIV_ROUND_UP(vco_min, parent_rate) * parent_rate;
पूर्ण

अटल पूर्णांक _setup_dynamic_ramp(काष्ठा tegra_clk_pll_params *pll_params,
			       व्योम __iomem *clk_base,
			       अचिन्हित दीर्घ parent_rate)
अणु
	u32 val;
	u32 step_a, step_b;

	चयन (parent_rate) अणु
	हाल 12000000:
	हाल 13000000:
	हाल 26000000:
		step_a = 0x2B;
		step_b = 0x0B;
		अवरोध;
	हाल 16800000:
		step_a = 0x1A;
		step_b = 0x09;
		अवरोध;
	हाल 19200000:
		step_a = 0x12;
		step_b = 0x08;
		अवरोध;
	शेष:
		pr_err("%s: Unexpected reference rate %lu\n",
			__func__, parent_rate);
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	val = step_a << pll_params->stepa_shअगरt;
	val |= step_b << pll_params->stepb_shअगरt;
	ग_लिखोl_relaxed(val, clk_base + pll_params->dyn_ramp_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक _pll_ramp_calc_pll(काष्ठा clk_hw *hw,
			      काष्ठा tegra_clk_pll_freq_table *cfg,
			      अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	पूर्णांक err = 0;

	err = _get_table_rate(hw, cfg, rate, parent_rate);
	अगर (err < 0)
		err = _calc_dynamic_ramp_rate(hw, cfg, rate, parent_rate);
	अन्यथा अणु
		अगर (cfg->m != _pll_fixed_mभाग(pll->params, parent_rate)) अणु
			WARN_ON(1);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (cfg->p >  pll->params->max_p)
		err = -EINVAL;

out:
	वापस err;
पूर्ण

अटल पूर्णांक clk_pllxc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table cfg, old_cfg;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	ret = _pll_ramp_calc_pll(hw, &cfg, rate, parent_rate);
	अगर (ret < 0)
		वापस ret;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_get_pll_mnp(pll, &old_cfg);
	अगर (pll->params->flags & TEGRA_PLL_VCO_OUT)
		cfg.p = old_cfg.p;

	अगर (old_cfg.m != cfg.m || old_cfg.n != cfg.n || old_cfg.p != cfg.p)
		ret = _program_pll(hw, &cfg, rate);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल दीर्घ clk_pll_ramp_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table cfg;
	पूर्णांक ret, p_भाग;
	u64 output_rate = *prate;

	ret = _pll_ramp_calc_pll(hw, &cfg, rate, *prate);
	अगर (ret < 0)
		वापस ret;

	p_भाग = _hw_to_p_भाग(hw, cfg.p);
	अगर (p_भाग < 0)
		वापस p_भाग;

	अगर (pll->params->set_gain)
		pll->params->set_gain(&cfg);

	output_rate *= cfg.n;
	करो_भाग(output_rate, cfg.m * p_भाग);

	वापस output_rate;
पूर्ण

अटल व्योम _pllcx_strobe(काष्ठा tegra_clk_pll *pll)
अणु
	u32 val;

	val = pll_पढ़ोl_misc(pll);
	val |= PLLCX_MISC_STROBE;
	pll_ग_लिखोl_misc(val, pll);
	udelay(2);

	val &= ~PLLCX_MISC_STROBE;
	pll_ग_लिखोl_misc(val, pll);
पूर्ण

अटल पूर्णांक clk_pllc_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags = 0;

	अगर (clk_pll_is_enabled(hw))
		वापस 0;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_clk_pll_enable(hw);
	udelay(2);

	val = pll_पढ़ोl_misc(pll);
	val &= ~PLLCX_MISC_RESET;
	pll_ग_लिखोl_misc(val, pll);
	udelay(2);

	_pllcx_strobe(pll);

	ret = clk_pll_रुको_क्रम_lock(pll);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम _clk_pllc_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val;

	_clk_pll_disable(hw);

	val = pll_पढ़ोl_misc(pll);
	val |= PLLCX_MISC_RESET;
	pll_ग_लिखोl_misc(val, pll);
	udelay(2);
पूर्ण

अटल व्योम clk_pllc_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ flags = 0;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_clk_pllc_disable(hw);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);
पूर्ण

अटल पूर्णांक _pllcx_update_dynamic_coef(काष्ठा tegra_clk_pll *pll,
					अचिन्हित दीर्घ input_rate, u32 n)
अणु
	u32 val, n_threshold;

	चयन (input_rate) अणु
	हाल 12000000:
		n_threshold = 70;
		अवरोध;
	हाल 13000000:
	हाल 26000000:
		n_threshold = 71;
		अवरोध;
	हाल 16800000:
		n_threshold = 55;
		अवरोध;
	हाल 19200000:
		n_threshold = 48;
		अवरोध;
	शेष:
		pr_err("%s: Unexpected reference rate %lu\n",
			__func__, input_rate);
		वापस -EINVAL;
	पूर्ण

	val = pll_पढ़ोl_misc(pll);
	val &= ~(PLLCX_MISC_SDM_DIV_MASK | PLLCX_MISC_FILT_DIV_MASK);
	val |= n <= n_threshold ?
		PLLCX_MISC_DIV_LOW_RANGE : PLLCX_MISC_DIV_HIGH_RANGE;
	pll_ग_लिखोl_misc(val, pll);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_pllc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll_freq_table cfg, old_cfg;
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक state, ret = 0;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	ret = _pll_ramp_calc_pll(hw, &cfg, rate, parent_rate);
	अगर (ret < 0)
		जाओ out;

	_get_pll_mnp(pll, &old_cfg);

	अगर (cfg.m != old_cfg.m) अणु
		WARN_ON(1);
		जाओ out;
	पूर्ण

	अगर (old_cfg.n == cfg.n && old_cfg.p == cfg.p)
		जाओ out;

	state = clk_pll_is_enabled(hw);
	अगर (state)
		_clk_pllc_disable(hw);

	ret = _pllcx_update_dynamic_coef(pll, parent_rate, cfg.n);
	अगर (ret < 0)
		जाओ out;

	_update_pll_mnp(pll, &cfg);

	अगर (state)
		ret = clk_pllc_enable(hw);

out:
	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल दीर्घ _pllre_calc_rate(काष्ठा tegra_clk_pll *pll,
			     काष्ठा tegra_clk_pll_freq_table *cfg,
			     अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	u16 m, n;
	u64 output_rate = parent_rate;

	m = _pll_fixed_mभाग(pll->params, parent_rate);
	n = rate * m / parent_rate;

	output_rate *= n;
	करो_भाग(output_rate, m);

	अगर (cfg) अणु
		cfg->m = m;
		cfg->n = n;
	पूर्ण

	वापस output_rate;
पूर्ण

अटल पूर्णांक clk_pllre_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll_freq_table cfg, old_cfg;
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक state, ret = 0;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_pllre_calc_rate(pll, &cfg, rate, parent_rate);
	_get_pll_mnp(pll, &old_cfg);
	cfg.p = old_cfg.p;

	अगर (cfg.m != old_cfg.m || cfg.n != old_cfg.n) अणु
		state = clk_pll_is_enabled(hw);
		अगर (state)
			_clk_pll_disable(hw);

		_update_pll_mnp(pll, &cfg);

		अगर (state) अणु
			_clk_pll_enable(hw);
			ret = clk_pll_रुको_क्रम_lock(pll);
		पूर्ण
	पूर्ण

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ clk_pllre_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll_freq_table cfg;
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u64 rate = parent_rate;

	_get_pll_mnp(pll, &cfg);

	rate *= cfg.n;
	करो_भाग(rate, cfg.m);

	वापस rate;
पूर्ण

अटल दीर्घ clk_pllre_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *prate)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);

	वापस _pllre_calc_rate(pll, शून्य, rate, *prate);
पूर्ण

अटल पूर्णांक clk_plle_tegra114_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table sel;
	u32 val;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ input_rate;

	input_rate = clk_hw_get_rate(clk_hw_get_parent(hw));

	अगर (_get_table_rate(hw, &sel, pll->params->fixed_rate, input_rate))
		वापस -EINVAL;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	val = pll_पढ़ोl_base(pll);
	val &= ~BIT(29); /* Disable lock override */
	pll_ग_लिखोl_base(val, pll);

	val = pll_पढ़ोl(pll->params->aux_reg, pll);
	val |= PLLE_AUX_ENABLE_SWCTL;
	val &= ~PLLE_AUX_SEQ_ENABLE;
	pll_ग_लिखोl(val, pll->params->aux_reg, pll);
	udelay(1);

	val = pll_पढ़ोl_misc(pll);
	val |= PLLE_MISC_LOCK_ENABLE;
	val |= PLLE_MISC_IDDQ_SW_CTRL;
	val &= ~PLLE_MISC_IDDQ_SW_VALUE;
	val |= PLLE_MISC_PLLE_PTS;
	val &= ~(PLLE_MISC_VREG_BG_CTRL_MASK | PLLE_MISC_VREG_CTRL_MASK);
	pll_ग_लिखोl_misc(val, pll);
	udelay(5);

	val = pll_पढ़ोl(PLLE_SS_CTRL, pll);
	val |= PLLE_SS_DISABLE;
	pll_ग_लिखोl(val, PLLE_SS_CTRL, pll);

	val = pll_पढ़ोl_base(pll);
	val &= ~(भागp_mask_shअगरted(pll) | भागn_mask_shअगरted(pll) |
		 भागm_mask_shअगरted(pll));
	val &= ~(PLLE_BASE_DIVCML_MASK << PLLE_BASE_DIVCML_SHIFT);
	val |= sel.m << भागm_shअगरt(pll);
	val |= sel.n << भागn_shअगरt(pll);
	val |= sel.cpcon << PLLE_BASE_DIVCML_SHIFT;
	pll_ग_लिखोl_base(val, pll);
	udelay(1);

	_clk_pll_enable(hw);
	ret = clk_pll_रुको_क्रम_lock(pll);

	अगर (ret < 0)
		जाओ out;

	val = pll_पढ़ोl(PLLE_SS_CTRL, pll);
	val &= ~(PLLE_SS_CNTL_CENTER | PLLE_SS_CNTL_INVERT);
	val &= ~PLLE_SS_COEFFICIENTS_MASK;
	val |= PLLE_SS_COEFFICIENTS_VAL_TEGRA114;
	pll_ग_लिखोl(val, PLLE_SS_CTRL, pll);
	val &= ~(PLLE_SS_CNTL_SSC_BYP | PLLE_SS_CNTL_BYPASS_SS);
	pll_ग_लिखोl(val, PLLE_SS_CTRL, pll);
	udelay(1);
	val &= ~PLLE_SS_CNTL_INTERP_RESET;
	pll_ग_लिखोl(val, PLLE_SS_CTRL, pll);
	udelay(1);

	/* Enable HW control of XUSB brick PLL */
	val = pll_पढ़ोl_misc(pll);
	val &= ~PLLE_MISC_IDDQ_SW_CTRL;
	pll_ग_लिखोl_misc(val, pll);

	val = pll_पढ़ोl(pll->params->aux_reg, pll);
	val |= (PLLE_AUX_USE_LOCKDET | PLLE_AUX_SEQ_START_STATE);
	val &= ~(PLLE_AUX_ENABLE_SWCTL | PLLE_AUX_SS_SWCTL);
	pll_ग_लिखोl(val, pll->params->aux_reg, pll);
	udelay(1);
	val |= PLLE_AUX_SEQ_ENABLE;
	pll_ग_लिखोl(val, pll->params->aux_reg, pll);

	val = pll_पढ़ोl(XUSBIO_PLL_CFG0, pll);
	val |= (XUSBIO_PLL_CFG0_PADPLL_USE_LOCKDET |
		XUSBIO_PLL_CFG0_SEQ_START_STATE);
	val &= ~(XUSBIO_PLL_CFG0_CLK_ENABLE_SWCTL |
		 XUSBIO_PLL_CFG0_PADPLL_RESET_SWCTL);
	pll_ग_लिखोl(val, XUSBIO_PLL_CFG0, pll);
	udelay(1);
	val |= XUSBIO_PLL_CFG0_SEQ_ENABLE;
	pll_ग_लिखोl(val, XUSBIO_PLL_CFG0, pll);

	/* Enable HW control of SATA PLL */
	val = pll_पढ़ोl(SATA_PLL_CFG0, pll);
	val &= ~SATA_PLL_CFG0_PADPLL_RESET_SWCTL;
	val |= SATA_PLL_CFG0_PADPLL_USE_LOCKDET;
	val |= SATA_PLL_CFG0_SEQ_START_STATE;
	pll_ग_लिखोl(val, SATA_PLL_CFG0, pll);

	udelay(1);

	val = pll_पढ़ोl(SATA_PLL_CFG0, pll);
	val |= SATA_PLL_CFG0_SEQ_ENABLE;
	pll_ग_लिखोl(val, SATA_PLL_CFG0, pll);

out:
	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम clk_plle_tegra114_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_clk_pll_disable(hw);

	val = pll_पढ़ोl_misc(pll);
	val |= PLLE_MISC_IDDQ_SW_CTRL | PLLE_MISC_IDDQ_SW_VALUE;
	pll_ग_लिखोl_misc(val, pll);
	udelay(1);

	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);
पूर्ण

अटल पूर्णांक clk_pllu_tegra114_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा uपंचांगi_clk_param *params = शून्य;
	काष्ठा clk *osc = __clk_lookup("osc");
	अचिन्हित दीर्घ flags = 0, input_rate;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;
	u32 value;

	अगर (!osc) अणु
		pr_err("%s: failed to get OSC clock\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (clk_pll_is_enabled(hw))
		वापस 0;

	input_rate = clk_hw_get_rate(__clk_get_hw(osc));

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	_clk_pll_enable(hw);

	ret = clk_pll_रुको_क्रम_lock(pll);
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(uपंचांगi_parameters); i++) अणु
		अगर (input_rate == uपंचांगi_parameters[i].osc_frequency) अणु
			params = &uपंचांगi_parameters[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!params) अणु
		pr_err("%s: unexpected input rate %lu Hz\n", __func__,
		       input_rate);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	value = pll_पढ़ोl_base(pll);
	value &= ~PLLU_BASE_OVERRIDE;
	pll_ग_लिखोl_base(value, pll);

	value = पढ़ोl_relaxed(pll->clk_base + UTMIP_PLL_CFG2);
	/* Program UTMIP PLL stable and active counts */
	value &= ~UTMIP_PLL_CFG2_STABLE_COUNT(~0);
	value |= UTMIP_PLL_CFG2_STABLE_COUNT(params->stable_count);
	value &= ~UTMIP_PLL_CFG2_ACTIVE_DLY_COUNT(~0);
	value |= UTMIP_PLL_CFG2_ACTIVE_DLY_COUNT(params->active_delay_count);
	/* Remove घातer करोwns from UTMIP PLL control bits */
	value &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_A_POWERDOWN;
	value &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_B_POWERDOWN;
	value &= ~UTMIP_PLL_CFG2_FORCE_PD_SAMP_C_POWERDOWN;
	ग_लिखोl_relaxed(value, pll->clk_base + UTMIP_PLL_CFG2);

	value = पढ़ोl_relaxed(pll->clk_base + UTMIP_PLL_CFG1);
	/* Program UTMIP PLL delay and oscillator frequency counts */
	value &= ~UTMIP_PLL_CFG1_ENABLE_DLY_COUNT(~0);
	value |= UTMIP_PLL_CFG1_ENABLE_DLY_COUNT(params->enable_delay_count);
	value &= ~UTMIP_PLL_CFG1_XTAL_FREQ_COUNT(~0);
	value |= UTMIP_PLL_CFG1_XTAL_FREQ_COUNT(params->xtal_freq_count);
	/* Remove घातer करोwns from UTMIP PLL control bits */
	value &= ~UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERDOWN;
	value &= ~UTMIP_PLL_CFG1_FORCE_PLL_ACTIVE_POWERDOWN;
	value &= ~UTMIP_PLL_CFG1_FORCE_PLLU_POWERUP;
	value &= ~UTMIP_PLL_CFG1_FORCE_PLLU_POWERDOWN;
	ग_लिखोl_relaxed(value, pll->clk_base + UTMIP_PLL_CFG1);

	/* Setup HW control of UTMIPLL */
	value = पढ़ोl_relaxed(pll->clk_base + UTMIPLL_HW_PWRDN_CFG0);
	value |= UTMIPLL_HW_PWRDN_CFG0_USE_LOCKDET;
	value &= ~UTMIPLL_HW_PWRDN_CFG0_CLK_ENABLE_SWCTL;
	value |= UTMIPLL_HW_PWRDN_CFG0_SEQ_START_STATE;
	ग_लिखोl_relaxed(value, pll->clk_base + UTMIPLL_HW_PWRDN_CFG0);

	value = पढ़ोl_relaxed(pll->clk_base + UTMIP_PLL_CFG1);
	value &= ~UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERUP;
	value &= ~UTMIP_PLL_CFG1_FORCE_PLL_ENABLE_POWERDOWN;
	ग_लिखोl_relaxed(value, pll->clk_base + UTMIP_PLL_CFG1);

	udelay(1);

	/*
	 * Setup SW override of UTMIPLL assuming USB2.0 ports are asचिन्हित
	 * to USB2
	 */
	value = पढ़ोl_relaxed(pll->clk_base + UTMIPLL_HW_PWRDN_CFG0);
	value |= UTMIPLL_HW_PWRDN_CFG0_IDDQ_SWCTL;
	value &= ~UTMIPLL_HW_PWRDN_CFG0_IDDQ_OVERRIDE;
	ग_लिखोl_relaxed(value, pll->clk_base + UTMIPLL_HW_PWRDN_CFG0);

	udelay(1);

	/* Enable HW control of UTMIPLL */
	value = पढ़ोl_relaxed(pll->clk_base + UTMIPLL_HW_PWRDN_CFG0);
	value |= UTMIPLL_HW_PWRDN_CFG0_SEQ_ENABLE;
	ग_लिखोl_relaxed(value, pll->clk_base + UTMIPLL_HW_PWRDN_CFG0);

out:
	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम _clk_plle_tegra_init_parent(काष्ठा tegra_clk_pll *pll)
अणु
	u32 val, val_aux;

	/* ensure parent is set to pll_ref */
	val = pll_पढ़ोl_base(pll);
	val_aux = pll_पढ़ोl(pll->params->aux_reg, pll);

	अगर (val & PLL_BASE_ENABLE) अणु
		अगर ((val_aux & PLLE_AUX_PLLRE_SEL) ||
		    (val_aux & PLLE_AUX_PLLP_SEL))
			WARN(1, "pll_e enabled with unsupported parent %s\n",
			     (val_aux & PLLE_AUX_PLLP_SEL) ? "pllp_out0" :
			     "pll_re_vco");
	पूर्ण अन्यथा अणु
		val_aux &= ~(PLLE_AUX_PLLRE_SEL | PLLE_AUX_PLLP_SEL);
		pll_ग_लिखोl(val_aux, pll->params->aux_reg, pll);
		fence_udelay(1, pll->clk_base);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा tegra_clk_pll *_tegra_init_pll(व्योम __iomem *clk_base,
		व्योम __iomem *pmc, काष्ठा tegra_clk_pll_params *pll_params,
		spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->clk_base = clk_base;
	pll->pmc = pmc;

	pll->params = pll_params;
	pll->lock = lock;

	अगर (!pll_params->भाग_nmp)
		pll_params->भाग_nmp = &शेष_nmp;

	वापस pll;
पूर्ण

अटल काष्ठा clk *_tegra_clk_रेजिस्टर_pll(काष्ठा tegra_clk_pll *pll,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		स्थिर काष्ठा clk_ops *ops)
अणु
	काष्ठा clk_init_data init;

	init.name = name;
	init.ops = ops;
	init.flags = flags;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	/* Default to _calc_rate अगर unspecअगरied */
	अगर (!pll->params->calc_rate) अणु
		अगर (pll->params->flags & TEGRA_PLLM)
			pll->params->calc_rate = _calc_dynamic_ramp_rate;
		अन्यथा
			pll->params->calc_rate = _calc_rate;
	पूर्ण

	अगर (pll->params->set_शेषs)
		pll->params->set_शेषs(pll);

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	pll->hw.init = &init;

	वापस clk_रेजिस्टर(शून्य, &pll->hw);
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_pll(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *clk_base, व्योम __iomem *pmc,
		अचिन्हित दीर्घ flags, काष्ठा tegra_clk_pll_params *pll_params,
		spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk;

	pll_params->flags |= TEGRA_PLL_BYPASS;

	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pll_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

अटल काष्ठा भाग_nmp pll_e_nmp = अणु
	.भागn_shअगरt = PLLE_BASE_DIVN_SHIFT,
	.भागn_width = PLLE_BASE_DIVN_WIDTH,
	.भागm_shअगरt = PLLE_BASE_DIVM_SHIFT,
	.भागm_width = PLLE_BASE_DIVM_WIDTH,
	.भागp_shअगरt = PLLE_BASE_DIVP_SHIFT,
	.भागp_width = PLLE_BASE_DIVP_WIDTH,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_plle(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *clk_base, व्योम __iomem *pmc,
		अचिन्हित दीर्घ flags, काष्ठा tegra_clk_pll_params *pll_params,
		spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk;

	pll_params->flags |= TEGRA_PLL_BYPASS;

	अगर (!pll_params->भाग_nmp)
		pll_params->भाग_nmp = &pll_e_nmp;

	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_plle_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_pllu(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
		काष्ठा tegra_clk_pll_params *pll_params, spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk;

	pll_params->flags |= TEGRA_PLLU;

	pll = _tegra_init_pll(clk_base, शून्य, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pllu_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

#अगर defined(CONFIG_ARCH_TEGRA_114_SOC) || \
	defined(CONFIG_ARCH_TEGRA_124_SOC) || \
	defined(CONFIG_ARCH_TEGRA_132_SOC) || \
	defined(CONFIG_ARCH_TEGRA_210_SOC)
अटल स्थिर काष्ठा clk_ops tegra_clk_pllxc_ops = अणु
	.is_enabled = clk_pll_is_enabled,
	.enable = clk_pll_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pll_recalc_rate,
	.round_rate = clk_pll_ramp_round_rate,
	.set_rate = clk_pllxc_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_clk_pllc_ops = अणु
	.is_enabled = clk_pll_is_enabled,
	.enable = clk_pllc_enable,
	.disable = clk_pllc_disable,
	.recalc_rate = clk_pll_recalc_rate,
	.round_rate = clk_pll_ramp_round_rate,
	.set_rate = clk_pllc_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_clk_pllre_ops = अणु
	.is_enabled = clk_pll_is_enabled,
	.enable = clk_pll_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pllre_recalc_rate,
	.round_rate = clk_pllre_round_rate,
	.set_rate = clk_pllre_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_clk_plle_tegra114_ops = अणु
	.is_enabled =  clk_pll_is_enabled,
	.enable = clk_plle_tegra114_enable,
	.disable = clk_plle_tegra114_disable,
	.recalc_rate = clk_pll_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_clk_pllu_tegra114_ops = अणु
	.is_enabled =  clk_pll_is_enabled,
	.enable = clk_pllu_tegra114_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pll_recalc_rate,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_pllxc(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			  व्योम __iomem *clk_base, व्योम __iomem *pmc,
			  अचिन्हित दीर्घ flags,
			  काष्ठा tegra_clk_pll_params *pll_params,
			  spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk, *parent;
	अचिन्हित दीर्घ parent_rate;
	u32 val, val_iddq;

	parent = __clk_lookup(parent_name);
	अगर (!parent) अणु
		WARN(1, "parent clk %s of %s must be registered first\n",
			parent_name, name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!pll_params->pभाग_प्रकारohw)
		वापस ERR_PTR(-EINVAL);

	parent_rate = clk_get_rate(parent);

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	अगर (pll_params->adjust_vco)
		pll_params->vco_min = pll_params->adjust_vco(pll_params,
							     parent_rate);

	/*
	 * If the pll has a set_शेषs callback, it will take care of
	 * configuring dynamic ramping and setting IDDQ in that path.
	 */
	अगर (!pll_params->set_शेषs) अणु
		पूर्णांक err;

		err = _setup_dynamic_ramp(pll_params, clk_base, parent_rate);
		अगर (err)
			वापस ERR_PTR(err);

		val = पढ़ोl_relaxed(clk_base + pll_params->base_reg);
		val_iddq = पढ़ोl_relaxed(clk_base + pll_params->iddq_reg);

		अगर (val & PLL_BASE_ENABLE)
			WARN_ON(val_iddq & BIT(pll_params->iddq_bit_idx));
		अन्यथा अणु
			val_iddq |= BIT(pll_params->iddq_bit_idx);
			ग_लिखोl_relaxed(val_iddq,
				       clk_base + pll_params->iddq_reg);
		पूर्ण
	पूर्ण

	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pllxc_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_pllre(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			  व्योम __iomem *clk_base, व्योम __iomem *pmc,
			  अचिन्हित दीर्घ flags,
			  काष्ठा tegra_clk_pll_params *pll_params,
			  spinlock_t *lock, अचिन्हित दीर्घ parent_rate)
अणु
	u32 val;
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk;

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	अगर (pll_params->adjust_vco)
		pll_params->vco_min = pll_params->adjust_vco(pll_params,
							     parent_rate);

	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	/* program minimum rate by शेष */

	val = pll_पढ़ोl_base(pll);
	अगर (val & PLL_BASE_ENABLE)
		WARN_ON(पढ़ोl_relaxed(clk_base + pll_params->iddq_reg) &
				BIT(pll_params->iddq_bit_idx));
	अन्यथा अणु
		पूर्णांक m;

		m = _pll_fixed_mभाग(pll_params, parent_rate);
		val = m << भागm_shअगरt(pll);
		val |= (pll_params->vco_min / parent_rate) << भागn_shअगरt(pll);
		pll_ग_लिखोl_base(val, pll);
	पूर्ण

	/* disable lock override */

	val = pll_पढ़ोl_misc(pll);
	val &= ~BIT(29);
	pll_ग_लिखोl_misc(val, pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pllre_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_pllm(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			  व्योम __iomem *clk_base, व्योम __iomem *pmc,
			  अचिन्हित दीर्घ flags,
			  काष्ठा tegra_clk_pll_params *pll_params,
			  spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk, *parent;
	अचिन्हित दीर्घ parent_rate;

	अगर (!pll_params->pभाग_प्रकारohw)
		वापस ERR_PTR(-EINVAL);

	parent = __clk_lookup(parent_name);
	अगर (!parent) अणु
		WARN(1, "parent clk %s of %s must be registered first\n",
			parent_name, name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	parent_rate = clk_get_rate(parent);

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	अगर (pll_params->adjust_vco)
		pll_params->vco_min = pll_params->adjust_vco(pll_params,
							     parent_rate);

	pll_params->flags |= TEGRA_PLL_BYPASS;
	pll_params->flags |= TEGRA_PLLM;
	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pll_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_pllc(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			  व्योम __iomem *clk_base, व्योम __iomem *pmc,
			  अचिन्हित दीर्घ flags,
			  काष्ठा tegra_clk_pll_params *pll_params,
			  spinlock_t *lock)
अणु
	काष्ठा clk *parent, *clk;
	स्थिर काष्ठा pभाग_map *p_tohw = pll_params->pभाग_प्रकारohw;
	काष्ठा tegra_clk_pll *pll;
	काष्ठा tegra_clk_pll_freq_table cfg;
	अचिन्हित दीर्घ parent_rate;

	अगर (!p_tohw)
		वापस ERR_PTR(-EINVAL);

	parent = __clk_lookup(parent_name);
	अगर (!parent) अणु
		WARN(1, "parent clk %s of %s must be registered first\n",
			parent_name, name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	parent_rate = clk_get_rate(parent);

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	pll_params->flags |= TEGRA_PLL_BYPASS;
	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	/*
	 * Most of PLLC रेजिस्टर fields are shaकरोwed, and can not be पढ़ो
	 * directly from PLL h/w. Hence, actual PLLC boot state is unknown.
	 * Initialize PLL to शेष state: disabled, reset; shaकरोw रेजिस्टरs
	 * loaded with शेष parameters; भागiders are preset क्रम half of
	 * minimum VCO rate (the latter assured that shaकरोwed भागider settings
	 * are within supported range).
	 */

	cfg.m = _pll_fixed_mभाग(pll_params, parent_rate);
	cfg.n = cfg.m * pll_params->vco_min / parent_rate;

	जबतक (p_tohw->pभाग) अणु
		अगर (p_tohw->pभाग == 2) अणु
			cfg.p = p_tohw->hw_val;
			अवरोध;
		पूर्ण
		p_tohw++;
	पूर्ण

	अगर (!p_tohw->pभाग) अणु
		WARN_ON(1);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pll_ग_लिखोl_base(0, pll);
	_update_pll_mnp(pll, &cfg);

	pll_ग_लिखोl_misc(PLLCX_MISC_DEFAULT, pll);
	pll_ग_लिखोl(PLLCX_MISC1_DEFAULT, pll_params->ext_misc_reg[0], pll);
	pll_ग_लिखोl(PLLCX_MISC2_DEFAULT, pll_params->ext_misc_reg[1], pll);
	pll_ग_लिखोl(PLLCX_MISC3_DEFAULT, pll_params->ext_misc_reg[2], pll);

	_pllcx_update_dynamic_coef(pll, parent_rate, cfg.n);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pllc_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_plle_tegra114(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name,
				व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk;

	pll = _tegra_init_pll(clk_base, शून्य, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	_clk_plle_tegra_init_parent(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_plle_tegra114_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *
tegra_clk_रेजिस्टर_pllu_tegra114(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				 व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				 काष्ठा tegra_clk_pll_params *pll_params,
				 spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk;

	pll_params->flags |= TEGRA_PLLU;

	pll = _tegra_init_pll(clk_base, शून्य, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pllu_tegra114_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_124_SOC) || defined(CONFIG_ARCH_TEGRA_132_SOC) || defined(CONFIG_ARCH_TEGRA_210_SOC)
अटल स्थिर काष्ठा clk_ops tegra_clk_pllss_ops = अणु
	.is_enabled = clk_pll_is_enabled,
	.enable = clk_pll_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pll_recalc_rate,
	.round_rate = clk_pll_ramp_round_rate,
	.set_rate = clk_pllxc_set_rate,
	.restore_context = tegra_clk_pll_restore_context,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_pllss(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk, *parent;
	काष्ठा tegra_clk_pll_freq_table cfg;
	अचिन्हित दीर्घ parent_rate;
	u32 val, val_iddq;
	पूर्णांक i;

	अगर (!pll_params->भाग_nmp)
		वापस ERR_PTR(-EINVAL);

	parent = __clk_lookup(parent_name);
	अगर (!parent) अणु
		WARN(1, "parent clk %s of %s must be registered first\n",
			parent_name, name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pll = _tegra_init_pll(clk_base, शून्य, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	val = pll_पढ़ोl_base(pll);
	val &= ~PLLSS_REF_SRC_SEL_MASK;
	pll_ग_लिखोl_base(val, pll);

	parent_rate = clk_get_rate(parent);

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	/* initialize PLL to minimum rate */

	cfg.m = _pll_fixed_mभाग(pll_params, parent_rate);
	cfg.n = cfg.m * pll_params->vco_min / parent_rate;

	क्रम (i = 0; pll_params->pभाग_प्रकारohw[i].pभाग; i++)
		;
	अगर (!i) अणु
		kमुक्त(pll);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	cfg.p = pll_params->pभाग_प्रकारohw[i-1].hw_val;

	_update_pll_mnp(pll, &cfg);

	pll_ग_लिखोl_misc(PLLSS_MISC_DEFAULT, pll);
	pll_ग_लिखोl(PLLSS_CFG_DEFAULT, pll_params->ext_misc_reg[0], pll);
	pll_ग_लिखोl(PLLSS_CTRL1_DEFAULT, pll_params->ext_misc_reg[1], pll);
	pll_ग_लिखोl(PLLSS_CTRL1_DEFAULT, pll_params->ext_misc_reg[2], pll);

	val = pll_पढ़ोl_base(pll);
	val_iddq = पढ़ोl_relaxed(clk_base + pll_params->iddq_reg);
	अगर (val & PLL_BASE_ENABLE) अणु
		अगर (val_iddq & BIT(pll_params->iddq_bit_idx)) अणु
			WARN(1, "%s is on but IDDQ set\n", name);
			kमुक्त(pll);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		val_iddq |= BIT(pll_params->iddq_bit_idx);
		ग_लिखोl_relaxed(val_iddq, clk_base + pll_params->iddq_reg);
	पूर्ण

	val &= ~PLLSS_LOCK_OVERRIDE;
	pll_ग_लिखोl_base(val, pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
					&tegra_clk_pllss_ops);

	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
काष्ठा clk *tegra_clk_रेजिस्टर_pllre_tegra210(स्थिर अक्षर *name,
			  स्थिर अक्षर *parent_name, व्योम __iomem *clk_base,
			  व्योम __iomem *pmc, अचिन्हित दीर्घ flags,
			  काष्ठा tegra_clk_pll_params *pll_params,
			  spinlock_t *lock, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk;

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	अगर (pll_params->adjust_vco)
		pll_params->vco_min = pll_params->adjust_vco(pll_params,
							     parent_rate);

	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pll_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

अटल पूर्णांक clk_plle_tegra210_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	u32 val;

	val = pll_पढ़ोl_base(pll);

	वापस val & PLLE_BASE_ENABLE ? 1 : 0;
पूर्ण

अटल पूर्णांक clk_plle_tegra210_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	काष्ठा tegra_clk_pll_freq_table sel;
	u32 val;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ input_rate;

	अगर (clk_plle_tegra210_is_enabled(hw))
		वापस 0;

	input_rate = clk_hw_get_rate(clk_hw_get_parent(hw));

	अगर (_get_table_rate(hw, &sel, pll->params->fixed_rate, input_rate))
		वापस -EINVAL;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	val = pll_पढ़ोl(pll->params->aux_reg, pll);
	अगर (val & PLLE_AUX_SEQ_ENABLE)
		जाओ out;

	val = pll_पढ़ोl_base(pll);
	val &= ~BIT(30); /* Disable lock override */
	pll_ग_लिखोl_base(val, pll);

	val = pll_पढ़ोl_misc(pll);
	val |= PLLE_MISC_LOCK_ENABLE;
	val |= PLLE_MISC_IDDQ_SW_CTRL;
	val &= ~PLLE_MISC_IDDQ_SW_VALUE;
	val |= PLLE_MISC_PLLE_PTS;
	val &= ~(PLLE_MISC_VREG_BG_CTRL_MASK | PLLE_MISC_VREG_CTRL_MASK);
	pll_ग_लिखोl_misc(val, pll);
	udelay(5);

	val = pll_पढ़ोl(PLLE_SS_CTRL, pll);
	val |= PLLE_SS_DISABLE;
	pll_ग_लिखोl(val, PLLE_SS_CTRL, pll);

	val = pll_पढ़ोl_base(pll);
	val &= ~(भागp_mask_shअगरted(pll) | भागn_mask_shअगरted(pll) |
		 भागm_mask_shअगरted(pll));
	val &= ~(PLLE_BASE_DIVCML_MASK << PLLE_BASE_DIVCML_SHIFT);
	val |= sel.m << भागm_shअगरt(pll);
	val |= sel.n << भागn_shअगरt(pll);
	val |= sel.cpcon << PLLE_BASE_DIVCML_SHIFT;
	pll_ग_लिखोl_base(val, pll);
	udelay(1);

	val = pll_पढ़ोl_base(pll);
	val |= PLLE_BASE_ENABLE;
	pll_ग_लिखोl_base(val, pll);

	ret = clk_pll_रुको_क्रम_lock(pll);

	अगर (ret < 0)
		जाओ out;

	val = pll_पढ़ोl(PLLE_SS_CTRL, pll);
	val &= ~(PLLE_SS_CNTL_CENTER | PLLE_SS_CNTL_INVERT);
	val &= ~PLLE_SS_COEFFICIENTS_MASK;
	val |= PLLE_SS_COEFFICIENTS_VAL_TEGRA210;
	pll_ग_लिखोl(val, PLLE_SS_CTRL, pll);
	val &= ~(PLLE_SS_CNTL_SSC_BYP | PLLE_SS_CNTL_BYPASS_SS);
	pll_ग_लिखोl(val, PLLE_SS_CTRL, pll);
	udelay(1);
	val &= ~PLLE_SS_CNTL_INTERP_RESET;
	pll_ग_लिखोl(val, PLLE_SS_CTRL, pll);
	udelay(1);

out:
	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम clk_plle_tegra210_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	अगर (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	/* If PLLE HW sequencer is enabled, SW should not disable PLLE */
	val = pll_पढ़ोl(pll->params->aux_reg, pll);
	अगर (val & PLLE_AUX_SEQ_ENABLE)
		जाओ out;

	val = pll_पढ़ोl_base(pll);
	val &= ~PLLE_BASE_ENABLE;
	pll_ग_लिखोl_base(val, pll);

	val = pll_पढ़ोl(pll->params->aux_reg, pll);
	val |= PLLE_AUX_ENABLE_SWCTL | PLLE_AUX_SS_SWCTL;
	pll_ग_लिखोl(val, pll->params->aux_reg, pll);

	val = pll_पढ़ोl_misc(pll);
	val |= PLLE_MISC_IDDQ_SW_CTRL | PLLE_MISC_IDDQ_SW_VALUE;
	pll_ग_लिखोl_misc(val, pll);
	udelay(1);

out:
	अगर (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);
पूर्ण

अटल व्योम tegra_clk_plle_t210_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll *pll = to_clk_pll(hw);

	_clk_plle_tegra_init_parent(pll);
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_clk_plle_tegra210_ops = अणु
	.is_enabled =  clk_plle_tegra210_is_enabled,
	.enable = clk_plle_tegra210_enable,
	.disable = clk_plle_tegra210_disable,
	.recalc_rate = clk_pll_recalc_rate,
	.restore_context = tegra_clk_plle_t210_restore_context,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_plle_tegra210(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name,
				व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk;

	pll = _tegra_init_pll(clk_base, शून्य, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	_clk_plle_tegra_init_parent(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_plle_tegra210_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_pllc_tegra210(स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name, व्योम __iomem *clk_base,
			व्योम __iomem *pmc, अचिन्हित दीर्घ flags,
			काष्ठा tegra_clk_pll_params *pll_params,
			spinlock_t *lock)
अणु
	काष्ठा clk *parent, *clk;
	स्थिर काष्ठा pभाग_map *p_tohw = pll_params->pभाग_प्रकारohw;
	काष्ठा tegra_clk_pll *pll;
	अचिन्हित दीर्घ parent_rate;

	अगर (!p_tohw)
		वापस ERR_PTR(-EINVAL);

	parent = __clk_lookup(parent_name);
	अगर (!parent) अणु
		WARN(1, "parent clk %s of %s must be registered first\n",
			name, parent_name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	parent_rate = clk_get_rate(parent);

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	अगर (pll_params->adjust_vco)
		pll_params->vco_min = pll_params->adjust_vco(pll_params,
							     parent_rate);

	pll_params->flags |= TEGRA_PLL_BYPASS;
	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pll_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_pllss_tegra210(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name, व्योम __iomem *clk_base,
				अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk, *parent;
	अचिन्हित दीर्घ parent_rate;
	u32 val;

	अगर (!pll_params->भाग_nmp)
		वापस ERR_PTR(-EINVAL);

	parent = __clk_lookup(parent_name);
	अगर (!parent) अणु
		WARN(1, "parent clk %s of %s must be registered first\n",
			name, parent_name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	val = पढ़ोl_relaxed(clk_base + pll_params->base_reg);
	अगर (val & PLLSS_REF_SRC_SEL_MASK) अणु
		WARN(1, "not supported reference clock for %s\n", name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	parent_rate = clk_get_rate(parent);

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	अगर (pll_params->adjust_vco)
		pll_params->vco_min = pll_params->adjust_vco(pll_params,
							     parent_rate);

	pll_params->flags |= TEGRA_PLL_BYPASS;
	pll = _tegra_init_pll(clk_base, शून्य, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
					&tegra_clk_pll_ops);

	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_pllmb(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			  व्योम __iomem *clk_base, व्योम __iomem *pmc,
			  अचिन्हित दीर्घ flags,
			  काष्ठा tegra_clk_pll_params *pll_params,
			  spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll *pll;
	काष्ठा clk *clk, *parent;
	अचिन्हित दीर्घ parent_rate;

	अगर (!pll_params->pभाग_प्रकारohw)
		वापस ERR_PTR(-EINVAL);

	parent = __clk_lookup(parent_name);
	अगर (!parent) अणु
		WARN(1, "parent clk %s of %s must be registered first\n",
			parent_name, name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	parent_rate = clk_get_rate(parent);

	pll_params->vco_min = _clip_vco_min(pll_params->vco_min, parent_rate);

	अगर (pll_params->adjust_vco)
		pll_params->vco_min = pll_params->adjust_vco(pll_params,
							     parent_rate);

	pll_params->flags |= TEGRA_PLL_BYPASS;
	pll_params->flags |= TEGRA_PLLMB;
	pll = _tegra_init_pll(clk_base, pmc, pll_params, lock);
	अगर (IS_ERR(pll))
		वापस ERR_CAST(pll);

	clk = _tegra_clk_रेजिस्टर_pll(pll, name, parent_name, flags,
				      &tegra_clk_pll_ops);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण

#पूर्ण_अगर
