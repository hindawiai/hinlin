<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Alex Deucher
 */

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "rv770.h"
#समावेश "rv770d.h"
#समावेश "r600_dpm.h"
#समावेश "rv770_dpm.h"
#समावेश "cypress_dpm.h"
#समावेश "atom.h"
#समावेश "evergreen.h"
#समावेश <linux/seq_file.h>

#घोषणा MC_CG_ARB_FREQ_F0           0x0a
#घोषणा MC_CG_ARB_FREQ_F1           0x0b
#घोषणा MC_CG_ARB_FREQ_F2           0x0c
#घोषणा MC_CG_ARB_FREQ_F3           0x0d

#घोषणा MC_CG_SEQ_DRAMCONF_S0       0x05
#घोषणा MC_CG_SEQ_DRAMCONF_S1       0x06

#घोषणा PCIE_BUS_CLK                10000
#घोषणा TCLK                        (PCIE_BUS_CLK / 10)

#घोषणा SMC_RAM_END 0xC000

काष्ठा rv7xx_ps *rv770_get_ps(काष्ठा radeon_ps *rps)
अणु
	काष्ठा rv7xx_ps *ps = rps->ps_priv;

	वापस ps;
पूर्ण

काष्ठा rv7xx_घातer_info *rv770_get_pi(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rdev->pm.dpm.priv;

	वापस pi;
पूर्ण

काष्ठा evergreen_घातer_info *evergreen_get_pi(काष्ठा radeon_device *rdev)
अणु
	काष्ठा evergreen_घातer_info *pi = rdev->pm.dpm.priv;

	वापस pi;
पूर्ण

अटल व्योम rv770_enable_bअगर_dynamic_pcie_gen2(काष्ठा radeon_device *rdev,
					       bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	अगर (enable) अणु
		पंचांगp &= ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
		पंचांगp |= LC_HW_VOLTAGE_IF_CONTROL(1);
		पंचांगp |= LC_GEN2_EN_STRAP;
	पूर्ण अन्यथा अणु
		अगर (!pi->boot_in_gen2) अणु
			पंचांगp &= ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
			पंचांगp &= ~LC_GEN2_EN_STRAP;
		पूर्ण
	पूर्ण
	अगर ((पंचांगp & LC_OTHER_SIDE_EVER_SENT_GEN2) ||
	    (पंचांगp & LC_OTHER_SIDE_SUPPORTS_GEN2))
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);

पूर्ण

अटल व्योम rv770_enable_l0s(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL) & ~LC_L0S_INACTIVITY_MASK;
	पंचांगp |= LC_L0S_INACTIVITY(3);
	WREG32_PCIE_PORT(PCIE_LC_CNTL, पंचांगp);
पूर्ण

अटल व्योम rv770_enable_l1(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL);
	पंचांगp &= ~LC_L1_INACTIVITY_MASK;
	पंचांगp |= LC_L1_INACTIVITY(4);
	पंचांगp &= ~LC_PMI_TO_L1_DIS;
	पंचांगp &= ~LC_ASPM_TO_L1_DIS;
	WREG32_PCIE_PORT(PCIE_LC_CNTL, पंचांगp);
पूर्ण

अटल व्योम rv770_enable_pll_sleep_in_l1(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL) & ~LC_L1_INACTIVITY_MASK;
	पंचांगp |= LC_L1_INACTIVITY(8);
	WREG32_PCIE_PORT(PCIE_LC_CNTL, पंचांगp);

	/* NOTE, this is a PCIE indirect reg, not PCIE PORT */
	पंचांगp = RREG32_PCIE(PCIE_P_CNTL);
	पंचांगp |= P_PLL_PWRDN_IN_L1L23;
	पंचांगp &= ~P_PLL_BUF_PDNB;
	पंचांगp &= ~P_PLL_PDNB;
	पंचांगp |= P_ALLOW_PRX_FRONTEND_SHUTOFF;
	WREG32_PCIE(PCIE_P_CNTL, पंचांगp);
पूर्ण

अटल व्योम rv770_gfx_घड़ी_gating_enable(काष्ठा radeon_device *rdev,
					  bool enable)
अणु
	अगर (enable)
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);
	अन्यथा अणु
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);
		WREG32_P(SCLK_PWRMGT_CNTL, GFX_CLK_FORCE_ON, ~GFX_CLK_FORCE_ON);
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~GFX_CLK_FORCE_ON);
		RREG32(GB_TILING_CONFIG);
	पूर्ण
पूर्ण

अटल व्योम rv770_mg_घड़ी_gating_enable(काष्ठा radeon_device *rdev,
					 bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (enable) अणु
		u32 mgcg_cgtt_local0;

		अगर (rdev->family == CHIP_RV770)
			mgcg_cgtt_local0 = RV770_MGCGTTLOCAL0_DFLT;
		अन्यथा
			mgcg_cgtt_local0 = RV7XX_MGCGTTLOCAL0_DFLT;

		WREG32(CG_CGTT_LOCAL_0, mgcg_cgtt_local0);
		WREG32(CG_CGTT_LOCAL_1, (RV770_MGCGTTLOCAL1_DFLT & 0xFFFFCFFF));

		अगर (pi->mgcgtssm)
			WREG32(CGTS_SM_CTRL_REG, RV770_MGCGCGTSSMCTRL_DFLT);
	पूर्ण अन्यथा अणु
		WREG32(CG_CGTT_LOCAL_0, 0xFFFFFFFF);
		WREG32(CG_CGTT_LOCAL_1, 0xFFFFCFFF);
	पूर्ण
पूर्ण

व्योम rv770_restore_cgcg(काष्ठा radeon_device *rdev)
अणु
	bool dpm_en = false, cg_en = false;

	अगर (RREG32(GENERAL_PWRMGT) & GLOBAL_PWRMGT_EN)
		dpm_en = true;
	अगर (RREG32(SCLK_PWRMGT_CNTL) & DYN_GFX_CLK_OFF_EN)
		cg_en = true;

	अगर (dpm_en && !cg_en)
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);
पूर्ण

अटल व्योम rv770_start_dpm(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SCLK_PWRMGT_CNTL, 0, ~SCLK_PWRMGT_OFF);

	WREG32_P(MCLK_PWRMGT_CNTL, 0, ~MPLL_PWRMGT_OFF);

	WREG32_P(GENERAL_PWRMGT, GLOBAL_PWRMGT_EN, ~GLOBAL_PWRMGT_EN);
पूर्ण

व्योम rv770_stop_dpm(काष्ठा radeon_device *rdev)
अणु
	PPSMC_Result result;

	result = rv770_send_msg_to_smc(rdev, PPSMC_MSG_TwoLevelsDisabled);

	अगर (result != PPSMC_Result_OK)
		DRM_DEBUG("Could not force DPM to low.\n");

	WREG32_P(GENERAL_PWRMGT, 0, ~GLOBAL_PWRMGT_EN);

	WREG32_P(SCLK_PWRMGT_CNTL, SCLK_PWRMGT_OFF, ~SCLK_PWRMGT_OFF);

	WREG32_P(MCLK_PWRMGT_CNTL, MPLL_PWRMGT_OFF, ~MPLL_PWRMGT_OFF);
पूर्ण

bool rv770_dpm_enabled(काष्ठा radeon_device *rdev)
अणु
	अगर (RREG32(GENERAL_PWRMGT) & GLOBAL_PWRMGT_EN)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

व्योम rv770_enable_thermal_protection(काष्ठा radeon_device *rdev,
				     bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, 0, ~THERMAL_PROTECTION_DIS);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, THERMAL_PROTECTION_DIS, ~THERMAL_PROTECTION_DIS);
पूर्ण

व्योम rv770_enable_acpi_pm(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(GENERAL_PWRMGT, STATIC_PM_EN, ~STATIC_PM_EN);
पूर्ण

u8 rv770_get_seq_value(काष्ठा radeon_device *rdev,
		       काष्ठा rv7xx_pl *pl)
अणु
	वापस (pl->flags & ATOM_PPLIB_R600_FLAGS_LOWPOWER) ?
		MC_CG_SEQ_DRAMCONF_S0 : MC_CG_SEQ_DRAMCONF_S1;
पूर्ण

#अगर 0
पूर्णांक rv770_पढ़ो_smc_soft_रेजिस्टर(काष्ठा radeon_device *rdev,
				 u16 reg_offset, u32 *value)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	वापस rv770_पढ़ो_smc_sram_dword(rdev,
					 pi->soft_regs_start + reg_offset,
					 value, pi->sram_end);
पूर्ण
#पूर्ण_अगर

पूर्णांक rv770_ग_लिखो_smc_soft_रेजिस्टर(काष्ठा radeon_device *rdev,
				  u16 reg_offset, u32 value)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	वापस rv770_ग_लिखो_smc_sram_dword(rdev,
					  pi->soft_regs_start + reg_offset,
					  value, pi->sram_end);
पूर्ण

पूर्णांक rv770_populate_smc_t(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ps *radeon_state,
			 RV770_SMC_SWSTATE *smc_state)
अणु
	काष्ठा rv7xx_ps *state = rv770_get_ps(radeon_state);
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	पूर्णांक i;
	पूर्णांक a_n;
	पूर्णांक a_d;
	u8 l[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
	u8 r[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
	u32 a_t;

	l[0] = 0;
	r[2] = 100;

	a_n = (पूर्णांक)state->medium.sclk * pi->lmp +
		(पूर्णांक)state->low.sclk * (R600_AH_DFLT - pi->rlp);
	a_d = (पूर्णांक)state->low.sclk * (100 - (पूर्णांक)pi->rlp) +
		(पूर्णांक)state->medium.sclk * pi->lmp;

	l[1] = (u8)(pi->lmp - (पूर्णांक)pi->lmp * a_n / a_d);
	r[0] = (u8)(pi->rlp + (100 - (पूर्णांक)pi->rlp) * a_n / a_d);

	a_n = (पूर्णांक)state->high.sclk * pi->lhp + (पूर्णांक)state->medium.sclk *
		(R600_AH_DFLT - pi->rmp);
	a_d = (पूर्णांक)state->medium.sclk * (100 - (पूर्णांक)pi->rmp) +
		(पूर्णांक)state->high.sclk * pi->lhp;

	l[2] = (u8)(pi->lhp - (पूर्णांक)pi->lhp * a_n / a_d);
	r[1] = (u8)(pi->rmp + (100 - (पूर्णांक)pi->rmp) * a_n / a_d);

	क्रम (i = 0; i < (RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1); i++) अणु
		a_t = CG_R(r[i] * pi->bsp / 200) | CG_L(l[i] * pi->bsp / 200);
		smc_state->levels[i].aT = cpu_to_be32(a_t);
	पूर्ण

	a_t = CG_R(r[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1] * pi->pbsp / 200) |
		CG_L(l[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1] * pi->pbsp / 200);

	smc_state->levels[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1].aT =
		cpu_to_be32(a_t);

	वापस 0;
पूर्ण

पूर्णांक rv770_populate_smc_sp(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_ps *radeon_state,
			  RV770_SMC_SWSTATE *smc_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	पूर्णांक i;

	क्रम (i = 0; i < (RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1); i++)
		smc_state->levels[i].bSP = cpu_to_be32(pi->dsp);

	smc_state->levels[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1].bSP =
		cpu_to_be32(pi->psp);

	वापस 0;
पूर्ण

अटल व्योम rv770_calculate_fractional_mpll_feedback_भागider(u32 memory_घड़ी,
							     u32 reference_घड़ी,
							     bool gddr5,
							     काष्ठा atom_घड़ी_भागiders *भागiders,
							     u32 *clkf,
							     u32 *clkfrac)
अणु
	u32 post_भागider, reference_भागider, feedback_भागider8;
	u32 fyclk;

	अगर (gddr5)
		fyclk = (memory_घड़ी * 8) / 2;
	अन्यथा
		fyclk = (memory_घड़ी * 4) / 2;

	post_भागider = भागiders->post_भाग;
	reference_भागider = भागiders->ref_भाग;

	feedback_भागider8 =
		(8 * fyclk * reference_भागider * post_भागider) / reference_घड़ी;

	*clkf = feedback_भागider8 / 8;
	*clkfrac = feedback_भागider8 % 8;
पूर्ण

अटल पूर्णांक rv770_encode_yclk_post_भाग(u32 postभाग, u32 *encoded_postभाग)
अणु
	पूर्णांक ret = 0;

	चयन (postभाग) अणु
	हाल 1:
		*encoded_postभाग = 0;
		अवरोध;
	हाल 2:
		*encoded_postभाग = 1;
		अवरोध;
	हाल 4:
		*encoded_postभाग = 2;
		अवरोध;
	हाल 8:
		*encoded_postभाग = 3;
		अवरोध;
	हाल 16:
		*encoded_postभाग = 4;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

u32 rv770_map_clkf_to_ibias(काष्ठा radeon_device *rdev, u32 clkf)
अणु
	अगर (clkf <= 0x10)
		वापस 0x4B;
	अगर (clkf <= 0x19)
		वापस 0x5B;
	अगर (clkf <= 0x21)
		वापस 0x2B;
	अगर (clkf <= 0x27)
		वापस 0x6C;
	अगर (clkf <= 0x31)
		वापस 0x9D;
	वापस 0xC6;
पूर्ण

अटल पूर्णांक rv770_populate_mclk_value(काष्ठा radeon_device *rdev,
				     u32 engine_घड़ी, u32 memory_घड़ी,
				     RV7XX_SMC_MCLK_VALUE *mclk)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u8 encoded_reference_भागiders[] = अणु 0, 16, 17, 20, 21 पूर्ण;
	u32 mpll_ad_func_cntl =
		pi->clk_regs.rv770.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 =
		pi->clk_regs.rv770.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl =
		pi->clk_regs.rv770.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 =
		pi->clk_regs.rv770.mpll_dq_func_cntl_2;
	u32 mclk_pwrmgt_cntl =
		pi->clk_regs.rv770.mclk_pwrmgt_cntl;
	u32 dll_cntl = pi->clk_regs.rv770.dll_cntl;
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 reference_घड़ी = rdev->घड़ी.mpll.reference_freq;
	u32 clkf, clkfrac;
	u32 postभाग_yclk;
	u32 ibias;
	पूर्णांक ret;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_MEMORY_PLL_PARAM,
					     memory_घड़ी, false, &भागiders);
	अगर (ret)
		वापस ret;

	अगर ((भागiders.ref_भाग < 1) || (भागiders.ref_भाग > 5))
		वापस -EINVAL;

	rv770_calculate_fractional_mpll_feedback_भागider(memory_घड़ी, reference_घड़ी,
							 pi->mem_gddr5,
							 &भागiders, &clkf, &clkfrac);

	ret = rv770_encode_yclk_post_भाग(भागiders.post_भाग, &postभाग_yclk);
	अगर (ret)
		वापस ret;

	ibias = rv770_map_clkf_to_ibias(rdev, clkf);

	mpll_ad_func_cntl &= ~(CLKR_MASK |
			       YCLK_POST_DIV_MASK |
			       CLKF_MASK |
			       CLKFRAC_MASK |
			       IBIAS_MASK);
	mpll_ad_func_cntl |= CLKR(encoded_reference_भागiders[भागiders.ref_भाग - 1]);
	mpll_ad_func_cntl |= YCLK_POST_DIV(postभाग_yclk);
	mpll_ad_func_cntl |= CLKF(clkf);
	mpll_ad_func_cntl |= CLKFRAC(clkfrac);
	mpll_ad_func_cntl |= IBIAS(ibias);

	अगर (भागiders.vco_mode)
		mpll_ad_func_cntl_2 |= VCO_MODE;
	अन्यथा
		mpll_ad_func_cntl_2 &= ~VCO_MODE;

	अगर (pi->mem_gddr5) अणु
		rv770_calculate_fractional_mpll_feedback_भागider(memory_घड़ी,
								 reference_घड़ी,
								 pi->mem_gddr5,
								 &भागiders, &clkf, &clkfrac);

		ibias = rv770_map_clkf_to_ibias(rdev, clkf);

		ret = rv770_encode_yclk_post_भाग(भागiders.post_भाग, &postभाग_yclk);
		अगर (ret)
			वापस ret;

		mpll_dq_func_cntl &= ~(CLKR_MASK |
				       YCLK_POST_DIV_MASK |
				       CLKF_MASK |
				       CLKFRAC_MASK |
				       IBIAS_MASK);
		mpll_dq_func_cntl |= CLKR(encoded_reference_भागiders[भागiders.ref_भाग - 1]);
		mpll_dq_func_cntl |= YCLK_POST_DIV(postभाग_yclk);
		mpll_dq_func_cntl |= CLKF(clkf);
		mpll_dq_func_cntl |= CLKFRAC(clkfrac);
		mpll_dq_func_cntl |= IBIAS(ibias);

		अगर (भागiders.vco_mode)
			mpll_dq_func_cntl_2 |= VCO_MODE;
		अन्यथा
			mpll_dq_func_cntl_2 &= ~VCO_MODE;
	पूर्ण

	mclk->mclk770.mclk_value = cpu_to_be32(memory_घड़ी);
	mclk->mclk770.vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	mclk->mclk770.vMPLL_AD_FUNC_CNTL_2 = cpu_to_be32(mpll_ad_func_cntl_2);
	mclk->mclk770.vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	mclk->mclk770.vMPLL_DQ_FUNC_CNTL_2 = cpu_to_be32(mpll_dq_func_cntl_2);
	mclk->mclk770.vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	mclk->mclk770.vDLL_CNTL = cpu_to_be32(dll_cntl);

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_populate_sclk_value(काष्ठा radeon_device *rdev,
				     u32 engine_घड़ी,
				     RV770_SMC_SCLK_VALUE *sclk)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 spll_func_cntl =
		pi->clk_regs.rv770.cg_spll_func_cntl;
	u32 spll_func_cntl_2 =
		pi->clk_regs.rv770.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 =
		pi->clk_regs.rv770.cg_spll_func_cntl_3;
	u32 cg_spll_spपढ़ो_spectrum =
		pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2 =
		pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum_2;
	u64 पंचांगp;
	u32 reference_घड़ी = rdev->घड़ी.spll.reference_freq;
	u32 reference_भागider, post_भागider;
	u32 fbभाग;
	पूर्णांक ret;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     engine_घड़ी, false, &भागiders);
	अगर (ret)
		वापस ret;

	reference_भागider = 1 + भागiders.ref_भाग;

	अगर (भागiders.enable_post_भाग)
		post_भागider = (0x0f & (भागiders.post_भाग >> 4)) + (0x0f & भागiders.post_भाग) + 2;
	अन्यथा
		post_भागider = 1;

	पंचांगp = (u64) engine_घड़ी * reference_भागider * post_भागider * 16384;
	करो_भाग(पंचांगp, reference_घड़ी);
	fbभाग = (u32) पंचांगp;

	अगर (भागiders.enable_post_भाग)
		spll_func_cntl |= SPLL_DIVEN;
	अन्यथा
		spll_func_cntl &= ~SPLL_DIVEN;
	spll_func_cntl &= ~(SPLL_HILEN_MASK | SPLL_LOLEN_MASK | SPLL_REF_DIV_MASK);
	spll_func_cntl |= SPLL_REF_DIV(भागiders.ref_भाग);
	spll_func_cntl |= SPLL_HILEN((भागiders.post_भाग >> 4) & 0xf);
	spll_func_cntl |= SPLL_LOLEN(भागiders.post_भाग & 0xf);

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(2);

	spll_func_cntl_3 &= ~SPLL_FB_DIV_MASK;
	spll_func_cntl_3 |= SPLL_FB_DIV(fbभाग);
	spll_func_cntl_3 |= SPLL_DITHEN;

	अगर (pi->sclk_ss) अणु
		काष्ठा radeon_atom_ss ss;
		u32 vco_freq = engine_घड़ी * post_भागider;

		अगर (radeon_atombios_get_asic_ss_info(rdev, &ss,
						     ASIC_INTERNAL_ENGINE_SS, vco_freq)) अणु
			u32 clk_s = reference_घड़ी * 5 / (reference_भागider * ss.rate);
			u32 clk_v = ss.percentage * fbभाग / (clk_s * 10000);

			cg_spll_spपढ़ो_spectrum &= ~CLKS_MASK;
			cg_spll_spपढ़ो_spectrum |= CLKS(clk_s);
			cg_spll_spपढ़ो_spectrum |= SSEN;

			cg_spll_spपढ़ो_spectrum_2 &= ~CLKV_MASK;
			cg_spll_spपढ़ो_spectrum_2 |= CLKV(clk_v);
		पूर्ण
	पूर्ण

	sclk->sclk_value = cpu_to_be32(engine_घड़ी);
	sclk->vCG_SPLL_FUNC_CNTL = cpu_to_be32(spll_func_cntl);
	sclk->vCG_SPLL_FUNC_CNTL_2 = cpu_to_be32(spll_func_cntl_2);
	sclk->vCG_SPLL_FUNC_CNTL_3 = cpu_to_be32(spll_func_cntl_3);
	sclk->vCG_SPLL_SPREAD_SPECTRUM = cpu_to_be32(cg_spll_spपढ़ो_spectrum);
	sclk->vCG_SPLL_SPREAD_SPECTRUM_2 = cpu_to_be32(cg_spll_spपढ़ो_spectrum_2);

	वापस 0;
पूर्ण

पूर्णांक rv770_populate_vddc_value(काष्ठा radeon_device *rdev, u16 vddc,
			      RV770_SMC_VOLTAGE_VALUE *voltage)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	पूर्णांक i;

	अगर (!pi->voltage_control) अणु
		voltage->index = 0;
		voltage->value = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < pi->valid_vddc_entries; i++) अणु
		अगर (vddc <= pi->vddc_table[i].vddc) अणु
			voltage->index = pi->vddc_table[i].vddc_index;
			voltage->value = cpu_to_be16(vddc);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == pi->valid_vddc_entries)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक rv770_populate_mvdd_value(काष्ठा radeon_device *rdev, u32 mclk,
			      RV770_SMC_VOLTAGE_VALUE *voltage)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (!pi->mvdd_control) अणु
		voltage->index = MVDD_HIGH_INDEX;
		voltage->value = cpu_to_be16(MVDD_HIGH_VALUE);
		वापस 0;
	पूर्ण

	अगर (mclk <= pi->mvdd_split_frequency) अणु
		voltage->index = MVDD_LOW_INDEX;
		voltage->value = cpu_to_be16(MVDD_LOW_VALUE);
	पूर्ण अन्यथा अणु
		voltage->index = MVDD_HIGH_INDEX;
		voltage->value = cpu_to_be16(MVDD_HIGH_VALUE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_convert_घातer_level_to_smc(काष्ठा radeon_device *rdev,
					    काष्ठा rv7xx_pl *pl,
					    RV770_SMC_HW_PERFORMANCE_LEVEL *level,
					    u8 watermark_level)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	पूर्णांक ret;

	level->gen2PCIE = pi->pcie_gen2 ?
		((pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0) : 0;
	level->gen2XSP  = (pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? 1 : 0;
	level->backbias = (pl->flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ? 1 : 0;
	level->displayWatermark = watermark_level;

	अगर (rdev->family == CHIP_RV740)
		ret = rv740_populate_sclk_value(rdev, pl->sclk,
						&level->sclk);
	अन्यथा अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		ret = rv730_populate_sclk_value(rdev, pl->sclk,
						&level->sclk);
	अन्यथा
		ret = rv770_populate_sclk_value(rdev, pl->sclk,
						&level->sclk);
	अगर (ret)
		वापस ret;

	अगर (rdev->family == CHIP_RV740) अणु
		अगर (pi->mem_gddr5) अणु
			अगर (pl->mclk <= pi->mclk_strobe_mode_threshold)
				level->strobeMode =
					rv740_get_mclk_frequency_ratio(pl->mclk) | 0x10;
			अन्यथा
				level->strobeMode = 0;

			अगर (pl->mclk > pi->mclk_edc_enable_threshold)
				level->mcFlags = SMC_MC_EDC_RD_FLAG | SMC_MC_EDC_WR_FLAG;
			अन्यथा
				level->mcFlags =  0;
		पूर्ण
		ret = rv740_populate_mclk_value(rdev, pl->sclk,
						pl->mclk, &level->mclk);
	पूर्ण अन्यथा अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		ret = rv730_populate_mclk_value(rdev, pl->sclk,
						pl->mclk, &level->mclk);
	अन्यथा
		ret = rv770_populate_mclk_value(rdev, pl->sclk,
						pl->mclk, &level->mclk);
	अगर (ret)
		वापस ret;

	ret = rv770_populate_vddc_value(rdev, pl->vddc,
					&level->vddc);
	अगर (ret)
		वापस ret;

	ret = rv770_populate_mvdd_value(rdev, pl->mclk, &level->mvdd);

	वापस ret;
पूर्ण

अटल पूर्णांक rv770_convert_घातer_state_to_smc(काष्ठा radeon_device *rdev,
					    काष्ठा radeon_ps *radeon_state,
					    RV770_SMC_SWSTATE *smc_state)
अणु
	काष्ठा rv7xx_ps *state = rv770_get_ps(radeon_state);
	पूर्णांक ret;

	अगर (!(radeon_state->caps & ATOM_PPLIB_DISALLOW_ON_DC))
		smc_state->flags |= PPSMC_SWSTATE_FLAG_DC;

	ret = rv770_convert_घातer_level_to_smc(rdev,
					       &state->low,
					       &smc_state->levels[0],
					       PPSMC_DISPLAY_WATERMARK_LOW);
	अगर (ret)
		वापस ret;

	ret = rv770_convert_घातer_level_to_smc(rdev,
					       &state->medium,
					       &smc_state->levels[1],
					       PPSMC_DISPLAY_WATERMARK_LOW);
	अगर (ret)
		वापस ret;

	ret = rv770_convert_घातer_level_to_smc(rdev,
					       &state->high,
					       &smc_state->levels[2],
					       PPSMC_DISPLAY_WATERMARK_HIGH);
	अगर (ret)
		वापस ret;

	smc_state->levels[0].arbValue = MC_CG_ARB_FREQ_F1;
	smc_state->levels[1].arbValue = MC_CG_ARB_FREQ_F2;
	smc_state->levels[2].arbValue = MC_CG_ARB_FREQ_F3;

	smc_state->levels[0].seqValue = rv770_get_seq_value(rdev,
							    &state->low);
	smc_state->levels[1].seqValue = rv770_get_seq_value(rdev,
							    &state->medium);
	smc_state->levels[2].seqValue = rv770_get_seq_value(rdev,
							    &state->high);

	rv770_populate_smc_sp(rdev, radeon_state, smc_state);

	वापस rv770_populate_smc_t(rdev, radeon_state, smc_state);

पूर्ण

u32 rv770_calculate_memory_refresh_rate(काष्ठा radeon_device *rdev,
					u32 engine_घड़ी)
अणु
	u32 dram_rows;
	u32 dram_refresh_rate;
	u32 mc_arb_rfsh_rate;
	u32 पंचांगp;

	पंचांगp = (RREG32(MC_ARB_RAMCFG) & NOOFROWS_MASK) >> NOOFROWS_SHIFT;
	dram_rows = 1 << (पंचांगp + 10);
	पंचांगp = RREG32(MC_SEQ_MISC0) & 3;
	dram_refresh_rate = 1 << (पंचांगp + 3);
	mc_arb_rfsh_rate = ((engine_घड़ी * 10) * dram_refresh_rate / dram_rows - 32) / 64;

	वापस mc_arb_rfsh_rate;
पूर्ण

अटल व्योम rv770_program_memory_timing_parameters(काष्ठा radeon_device *rdev,
						   काष्ठा radeon_ps *radeon_state)
अणु
	काष्ठा rv7xx_ps *state = rv770_get_ps(radeon_state);
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 sqm_ratio;
	u32 arb_refresh_rate;
	u32 high_घड़ी;

	अगर (state->high.sclk < (state->low.sclk * 0xFF / 0x40))
		high_घड़ी = state->high.sclk;
	अन्यथा
		high_घड़ी = (state->low.sclk * 0xFF / 0x40);

	radeon_atom_set_engine_dram_timings(rdev, high_घड़ी,
					    state->high.mclk);

	sqm_ratio =
		STATE0(64 * high_घड़ी / pi->boot_sclk) |
		STATE1(64 * high_घड़ी / state->low.sclk) |
		STATE2(64 * high_घड़ी / state->medium.sclk) |
		STATE3(64 * high_घड़ी / state->high.sclk);
	WREG32(MC_ARB_SQM_RATIO, sqm_ratio);

	arb_refresh_rate =
		POWERMODE0(rv770_calculate_memory_refresh_rate(rdev, pi->boot_sclk)) |
		POWERMODE1(rv770_calculate_memory_refresh_rate(rdev, state->low.sclk)) |
		POWERMODE2(rv770_calculate_memory_refresh_rate(rdev, state->medium.sclk)) |
		POWERMODE3(rv770_calculate_memory_refresh_rate(rdev, state->high.sclk));
	WREG32(MC_ARB_RFSH_RATE, arb_refresh_rate);
पूर्ण

व्योम rv770_enable_backbias(काष्ठा radeon_device *rdev,
			   bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, BACKBIAS_PAD_EN, ~BACKBIAS_PAD_EN);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~(BACKBIAS_VALUE | BACKBIAS_PAD_EN));
पूर्ण

अटल व्योम rv770_enable_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
					 bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (enable) अणु
		अगर (pi->sclk_ss)
			WREG32_P(GENERAL_PWRMGT, DYN_SPREAD_SPECTRUM_EN, ~DYN_SPREAD_SPECTRUM_EN);

		अगर (pi->mclk_ss) अणु
			अगर (rdev->family == CHIP_RV740)
				rv740_enable_mclk_spपढ़ो_spectrum(rdev, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32_P(CG_SPLL_SPREAD_SPECTRUM, 0, ~SSEN);

		WREG32_P(GENERAL_PWRMGT, 0, ~DYN_SPREAD_SPECTRUM_EN);

		WREG32_P(CG_MPLL_SPREAD_SPECTRUM, 0, ~SSEN);

		अगर (rdev->family == CHIP_RV740)
			rv740_enable_mclk_spपढ़ो_spectrum(rdev, false);
	पूर्ण
पूर्ण

अटल व्योम rv770_program_mpll_timing_parameters(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर ((rdev->family == CHIP_RV770) && !pi->mem_gddr5) अणु
		WREG32(MPLL_TIME,
		       (MPLL_LOCK_TIME(R600_MPLLLOCKTIME_DFLT * pi->ref_भाग) |
			MPLL_RESET_TIME(R600_MPLLRESETTIME_DFLT)));
	पूर्ण
पूर्ण

व्योम rv770_setup_bsp(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 xclk = radeon_get_xclk(rdev);

	r600_calculate_u_and_p(pi->asi,
			       xclk,
			       16,
			       &pi->bsp,
			       &pi->bsu);

	r600_calculate_u_and_p(pi->pasi,
			       xclk,
			       16,
			       &pi->pbsp,
			       &pi->pbsu);

	pi->dsp = BSP(pi->bsp) | BSU(pi->bsu);
	pi->psp = BSP(pi->pbsp) | BSU(pi->pbsu);

	WREG32(CG_BSP, pi->dsp);

पूर्ण

व्योम rv770_program_git(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(CG_GIT, CG_GICST(R600_GICST_DFLT), ~CG_GICST_MASK);
पूर्ण

व्योम rv770_program_tp(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;
	क्रमागत r600_td td = R600_TD_DFLT;

	क्रम (i = 0; i < R600_PM_NUMBER_OF_TC; i++)
		WREG32(CG_FFCT_0 + (i * 4), (UTC_0(r600_utc[i]) | DTC_0(r600_dtc[i])));

	अगर (td == R600_TD_AUTO)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_FORCE_TREND_SEL);
	अन्यथा
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_FORCE_TREND_SEL, ~FIR_FORCE_TREND_SEL);
	अगर (td == R600_TD_UP)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_TREND_MODE);
	अगर (td == R600_TD_DOWN)
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_TREND_MODE, ~FIR_TREND_MODE);
पूर्ण

व्योम rv770_program_tpp(काष्ठा radeon_device *rdev)
अणु
	WREG32(CG_TPC, R600_TPC_DFLT);
पूर्ण

व्योम rv770_program_sstp(काष्ठा radeon_device *rdev)
अणु
	WREG32(CG_SSP, (SSTU(R600_SSTU_DFLT) | SST(R600_SST_DFLT)));
पूर्ण

व्योम rv770_program_engine_speed_parameters(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SPLL_CNTL_MODE, SPLL_DIV_SYNC, ~SPLL_DIV_SYNC);
पूर्ण

अटल व्योम rv770_enable_display_gap(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32(CG_DISPLAY_GAP_CNTL);

	पंचांगp &= ~(DISP1_GAP_MCHG_MASK | DISP2_GAP_MCHG_MASK);
	पंचांगp |= (DISP1_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE) |
		DISP2_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE));
	WREG32(CG_DISPLAY_GAP_CNTL, पंचांगp);
पूर्ण

व्योम rv770_program_vc(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	WREG32(CG_FTV, pi->vrc);
पूर्ण

व्योम rv770_clear_vc(काष्ठा radeon_device *rdev)
अणु
	WREG32(CG_FTV, 0);
पूर्ण

पूर्णांक rv770_upload_firmware(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	पूर्णांक ret;

	rv770_reset_smc(rdev);
	rv770_stop_smc_घड़ी(rdev);

	ret = rv770_load_smc_ucode(rdev, pi->sram_end);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_populate_smc_acpi_state(काष्ठा radeon_device *rdev,
					 RV770_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	u32 mpll_ad_func_cntl =
		pi->clk_regs.rv770.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 =
		pi->clk_regs.rv770.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl =
		pi->clk_regs.rv770.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 =
		pi->clk_regs.rv770.mpll_dq_func_cntl_2;
	u32 spll_func_cntl =
		pi->clk_regs.rv770.cg_spll_func_cntl;
	u32 spll_func_cntl_2 =
		pi->clk_regs.rv770.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 =
		pi->clk_regs.rv770.cg_spll_func_cntl_3;
	u32 mclk_pwrmgt_cntl;
	u32 dll_cntl;

	table->ACPIState = table->initialState;

	table->ACPIState.flags &= ~PPSMC_SWSTATE_FLAG_DC;

	अगर (pi->acpi_vddc) अणु
		rv770_populate_vddc_value(rdev, pi->acpi_vddc,
					  &table->ACPIState.levels[0].vddc);
		अगर (pi->pcie_gen2) अणु
			अगर (pi->acpi_pcie_gen2)
				table->ACPIState.levels[0].gen2PCIE = 1;
			अन्यथा
				table->ACPIState.levels[0].gen2PCIE = 0;
		पूर्ण अन्यथा
			table->ACPIState.levels[0].gen2PCIE = 0;
		अगर (pi->acpi_pcie_gen2)
			table->ACPIState.levels[0].gen2XSP = 1;
		अन्यथा
			table->ACPIState.levels[0].gen2XSP = 0;
	पूर्ण अन्यथा अणु
		rv770_populate_vddc_value(rdev, pi->min_vddc_in_table,
					  &table->ACPIState.levels[0].vddc);
		table->ACPIState.levels[0].gen2PCIE = 0;
	पूर्ण


	mpll_ad_func_cntl_2 |= BIAS_GEN_PDNB | RESET_EN;

	mpll_dq_func_cntl_2 |= BIAS_GEN_PDNB | RESET_EN;

	mclk_pwrmgt_cntl = (MRDCKA0_RESET |
			    MRDCKA1_RESET |
			    MRDCKB0_RESET |
			    MRDCKB1_RESET |
			    MRDCKC0_RESET |
			    MRDCKC1_RESET |
			    MRDCKD0_RESET |
			    MRDCKD1_RESET);

	dll_cntl = 0xff000000;

	spll_func_cntl |= SPLL_RESET | SPLL_SLEEP | SPLL_BYPASS_EN;

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(4);

	table->ACPIState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL_2 = cpu_to_be32(mpll_ad_func_cntl_2);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL_2 = cpu_to_be32(mpll_dq_func_cntl_2);

	table->ACPIState.levels[0].mclk.mclk770.vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	table->ACPIState.levels[0].mclk.mclk770.vDLL_CNTL = cpu_to_be32(dll_cntl);

	table->ACPIState.levels[0].mclk.mclk770.mclk_value = 0;

	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL = cpu_to_be32(spll_func_cntl);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 = cpu_to_be32(spll_func_cntl_2);
	table->ACPIState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 = cpu_to_be32(spll_func_cntl_3);

	table->ACPIState.levels[0].sclk.sclk_value = 0;

	rv770_populate_mvdd_value(rdev, 0, &table->ACPIState.levels[0].mvdd);

	table->ACPIState.levels[1] = table->ACPIState.levels[0];
	table->ACPIState.levels[2] = table->ACPIState.levels[0];

	वापस 0;
पूर्ण

पूर्णांक rv770_populate_initial_mvdd_value(काष्ठा radeon_device *rdev,
				      RV770_SMC_VOLTAGE_VALUE *voltage)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर ((pi->s0_vid_lower_smio_cntl & pi->mvdd_mask_low) ==
	     (pi->mvdd_low_smio[MVDD_LOW_INDEX] & pi->mvdd_mask_low) ) अणु
		voltage->index = MVDD_LOW_INDEX;
		voltage->value = cpu_to_be16(MVDD_LOW_VALUE);
	पूर्ण अन्यथा अणु
		voltage->index = MVDD_HIGH_INDEX;
		voltage->value = cpu_to_be16(MVDD_HIGH_VALUE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_populate_smc_initial_state(काष्ठा radeon_device *rdev,
					    काष्ठा radeon_ps *radeon_state,
					    RV770_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_ps *initial_state = rv770_get_ps(radeon_state);
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 a_t;

	table->initialState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ad_func_cntl);
	table->initialState.levels[0].mclk.mclk770.vMPLL_AD_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ad_func_cntl_2);
	table->initialState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mpll_dq_func_cntl);
	table->initialState.levels[0].mclk.mclk770.vMPLL_DQ_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_dq_func_cntl_2);
	table->initialState.levels[0].mclk.mclk770.vMCLK_PWRMGT_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.mclk_pwrmgt_cntl);
	table->initialState.levels[0].mclk.mclk770.vDLL_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.dll_cntl);

	table->initialState.levels[0].mclk.mclk770.vMPLL_SS =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ss1);
	table->initialState.levels[0].mclk.mclk770.vMPLL_SS2 =
		cpu_to_be32(pi->clk_regs.rv770.mpll_ss2);

	table->initialState.levels[0].mclk.mclk770.mclk_value =
		cpu_to_be32(initial_state->low.mclk);

	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_2 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl_2);
	table->initialState.levels[0].sclk.vCG_SPLL_FUNC_CNTL_3 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_func_cntl_3);
	table->initialState.levels[0].sclk.vCG_SPLL_SPREAD_SPECTRUM =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum);
	table->initialState.levels[0].sclk.vCG_SPLL_SPREAD_SPECTRUM_2 =
		cpu_to_be32(pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum_2);

	table->initialState.levels[0].sclk.sclk_value =
		cpu_to_be32(initial_state->low.sclk);

	table->initialState.levels[0].arbValue = MC_CG_ARB_FREQ_F0;

	table->initialState.levels[0].seqValue =
		rv770_get_seq_value(rdev, &initial_state->low);

	rv770_populate_vddc_value(rdev,
				  initial_state->low.vddc,
				  &table->initialState.levels[0].vddc);
	rv770_populate_initial_mvdd_value(rdev,
					  &table->initialState.levels[0].mvdd);

	a_t = CG_R(0xffff) | CG_L(0);
	table->initialState.levels[0].aT = cpu_to_be32(a_t);

	table->initialState.levels[0].bSP = cpu_to_be32(pi->dsp);

	अगर (pi->boot_in_gen2)
		table->initialState.levels[0].gen2PCIE = 1;
	अन्यथा
		table->initialState.levels[0].gen2PCIE = 0;
	अगर (initial_state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2)
		table->initialState.levels[0].gen2XSP = 1;
	अन्यथा
		table->initialState.levels[0].gen2XSP = 0;

	अगर (rdev->family == CHIP_RV740) अणु
		अगर (pi->mem_gddr5) अणु
			अगर (initial_state->low.mclk <= pi->mclk_strobe_mode_threshold)
				table->initialState.levels[0].strobeMode =
					rv740_get_mclk_frequency_ratio(initial_state->low.mclk) | 0x10;
			अन्यथा
				table->initialState.levels[0].strobeMode = 0;

			अगर (initial_state->low.mclk >= pi->mclk_edc_enable_threshold)
				table->initialState.levels[0].mcFlags = SMC_MC_EDC_RD_FLAG | SMC_MC_EDC_WR_FLAG;
			अन्यथा
				table->initialState.levels[0].mcFlags =  0;
		पूर्ण
	पूर्ण

	table->initialState.levels[1] = table->initialState.levels[0];
	table->initialState.levels[2] = table->initialState.levels[0];

	table->initialState.flags |= PPSMC_SWSTATE_FLAG_DC;

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_populate_smc_vddc_table(काष्ठा radeon_device *rdev,
					 RV770_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	पूर्णांक i;

	क्रम (i = 0; i < pi->valid_vddc_entries; i++) अणु
		table->highSMIO[pi->vddc_table[i].vddc_index] =
			pi->vddc_table[i].high_smio;
		table->lowSMIO[pi->vddc_table[i].vddc_index] =
			cpu_to_be32(pi->vddc_table[i].low_smio);
	पूर्ण

	table->voltageMaskTable.highMask[RV770_SMC_VOLTAGEMASK_VDDC] = 0;
	table->voltageMaskTable.lowMask[RV770_SMC_VOLTAGEMASK_VDDC] =
		cpu_to_be32(pi->vddc_mask_low);

	क्रम (i = 0;
	     ((i < pi->valid_vddc_entries) &&
	      (pi->max_vddc_in_table >
	       pi->vddc_table[i].vddc));
	     i++);

	table->maxVDDCIndexInPPTable =
		pi->vddc_table[i].vddc_index;

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_populate_smc_mvdd_table(काष्ठा radeon_device *rdev,
					 RV770_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (pi->mvdd_control) अणु
		table->lowSMIO[MVDD_HIGH_INDEX] |=
			cpu_to_be32(pi->mvdd_low_smio[MVDD_HIGH_INDEX]);
		table->lowSMIO[MVDD_LOW_INDEX] |=
			cpu_to_be32(pi->mvdd_low_smio[MVDD_LOW_INDEX]);

		table->voltageMaskTable.highMask[RV770_SMC_VOLTAGEMASK_MVDD] = 0;
		table->voltageMaskTable.lowMask[RV770_SMC_VOLTAGEMASK_MVDD] =
			cpu_to_be32(pi->mvdd_mask_low);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_init_smc_table(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ps *radeon_boot_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा rv7xx_ps *boot_state = rv770_get_ps(radeon_boot_state);
	RV770_SMC_STATETABLE *table = &pi->smc_statetable;
	पूर्णांक ret;

	स_रखो(table, 0, माप(RV770_SMC_STATETABLE));

	pi->boot_sclk = boot_state->low.sclk;

	rv770_populate_smc_vddc_table(rdev, table);
	rv770_populate_smc_mvdd_table(rdev, table);

	चयन (rdev->pm.पूर्णांक_thermal_type) अणु
	हाल THERMAL_TYPE_RV770:
	हाल THERMAL_TYPE_ADT7473_WITH_INTERNAL:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_INTERNAL;
		अवरोध;
	हाल THERMAL_TYPE_NONE:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_NONE;
		अवरोध;
	हाल THERMAL_TYPE_EXTERNAL_GPIO:
	शेष:
		table->thermalProtectType = PPSMC_THERMAL_PROTECT_TYPE_EXTERNAL;
		अवरोध;
	पूर्ण

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_HARDWAREDC) अणु
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;

		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_DONT_WAIT_FOR_VBLANK_ON_ALERT)
			table->extraFlags |= PPSMC_EXTRAFLAGS_AC2DC_DONT_WAIT_FOR_VBLANK;

		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_GOTO_BOOT_ON_ALERT)
			table->extraFlags |= PPSMC_EXTRAFLAGS_AC2DC_ACTION_GOTOINITIALSTATE;
	पूर्ण

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	अगर (pi->mem_gddr5)
		table->प्रणालीFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		ret = rv730_populate_smc_initial_state(rdev, radeon_boot_state, table);
	अन्यथा
		ret = rv770_populate_smc_initial_state(rdev, radeon_boot_state, table);
	अगर (ret)
		वापस ret;

	अगर (rdev->family == CHIP_RV740)
		ret = rv740_populate_smc_acpi_state(rdev, table);
	अन्यथा अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		ret = rv730_populate_smc_acpi_state(rdev, table);
	अन्यथा
		ret = rv770_populate_smc_acpi_state(rdev, table);
	अगर (ret)
		वापस ret;

	table->driverState = table->initialState;

	वापस rv770_copy_bytes_to_smc(rdev,
				       pi->state_table_start,
				       (स्थिर u8 *)table,
				       माप(RV770_SMC_STATETABLE),
				       pi->sram_end);
पूर्ण

अटल पूर्णांक rv770_स्थिरruct_vddc_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u16 min, max, step;
	u32 steps = 0;
	u8 vddc_index = 0;
	u32 i;

	radeon_atom_get_min_voltage(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, &min);
	radeon_atom_get_max_voltage(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, &max);
	radeon_atom_get_voltage_step(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, &step);

	steps = (max - min) / step + 1;

	अगर (steps > MAX_NO_VREG_STEPS)
		वापस -EINVAL;

	क्रम (i = 0; i < steps; i++) अणु
		u32 gpio_pins, gpio_mask;

		pi->vddc_table[i].vddc = (u16)(min + i * step);
		radeon_atom_get_voltage_gpio_settings(rdev,
						      pi->vddc_table[i].vddc,
						      SET_VOLTAGE_TYPE_ASIC_VDDC,
						      &gpio_pins, &gpio_mask);
		pi->vddc_table[i].low_smio = gpio_pins & gpio_mask;
		pi->vddc_table[i].high_smio = 0;
		pi->vddc_mask_low = gpio_mask;
		अगर (i > 0) अणु
			अगर ((pi->vddc_table[i].low_smio !=
			     pi->vddc_table[i - 1].low_smio ) ||
			     (pi->vddc_table[i].high_smio !=
			      pi->vddc_table[i - 1].high_smio))
				vddc_index++;
		पूर्ण
		pi->vddc_table[i].vddc_index = vddc_index;
	पूर्ण

	pi->valid_vddc_entries = (u8)steps;

	वापस 0;
पूर्ण

अटल u32 rv770_get_mclk_split_poपूर्णांक(काष्ठा atom_memory_info *memory_info)
अणु
	अगर (memory_info->mem_type == MEM_TYPE_GDDR3)
		वापस 30000;

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_get_mvdd_pin_configuration(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 gpio_pins, gpio_mask;

	radeon_atom_get_voltage_gpio_settings(rdev,
					      MVDD_HIGH_VALUE, SET_VOLTAGE_TYPE_ASIC_MVDDC,
					      &gpio_pins, &gpio_mask);
	pi->mvdd_mask_low = gpio_mask;
	pi->mvdd_low_smio[MVDD_HIGH_INDEX] =
		gpio_pins & gpio_mask;

	radeon_atom_get_voltage_gpio_settings(rdev,
					      MVDD_LOW_VALUE, SET_VOLTAGE_TYPE_ASIC_MVDDC,
					      &gpio_pins, &gpio_mask);
	pi->mvdd_low_smio[MVDD_LOW_INDEX] =
		gpio_pins & gpio_mask;

	वापस 0;
पूर्ण

u8 rv770_get_memory_module_index(काष्ठा radeon_device *rdev)
अणु
	वापस (u8) ((RREG32(BIOS_SCRATCH_4) >> 16) & 0xff);
पूर्ण

अटल पूर्णांक rv770_get_mvdd_configuration(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u8 memory_module_index;
	काष्ठा atom_memory_info memory_info;

	memory_module_index = rv770_get_memory_module_index(rdev);

	अगर (radeon_atom_get_memory_info(rdev, memory_module_index, &memory_info)) अणु
		pi->mvdd_control = false;
		वापस 0;
	पूर्ण

	pi->mvdd_split_frequency =
		rv770_get_mclk_split_poपूर्णांक(&memory_info);

	अगर (pi->mvdd_split_frequency == 0) अणु
		pi->mvdd_control = false;
		वापस 0;
	पूर्ण

	वापस rv770_get_mvdd_pin_configuration(rdev);
पूर्ण

व्योम rv770_enable_voltage_control(काष्ठा radeon_device *rdev,
				  bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, VOLT_PWRMGT_EN, ~VOLT_PWRMGT_EN);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~VOLT_PWRMGT_EN);
पूर्ण

अटल व्योम rv770_program_display_gap(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp = RREG32(CG_DISPLAY_GAP_CNTL);

	पंचांगp &= ~(DISP1_GAP_MCHG_MASK | DISP2_GAP_MCHG_MASK);
	अगर (rdev->pm.dpm.new_active_crtcs & 1) अणु
		पंचांगp |= DISP1_GAP_MCHG(R600_PM_DISPLAY_GAP_VBLANK);
		पंचांगp |= DISP2_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE);
	पूर्ण अन्यथा अगर (rdev->pm.dpm.new_active_crtcs & 2) अणु
		पंचांगp |= DISP1_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE);
		पंचांगp |= DISP2_GAP_MCHG(R600_PM_DISPLAY_GAP_VBLANK);
	पूर्ण अन्यथा अणु
		पंचांगp |= DISP1_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE);
		पंचांगp |= DISP2_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE);
	पूर्ण
	WREG32(CG_DISPLAY_GAP_CNTL, पंचांगp);
पूर्ण

अटल व्योम rv770_enable_dynamic_pcie_gen2(काष्ठा radeon_device *rdev,
					   bool enable)
अणु
	rv770_enable_bअगर_dynamic_pcie_gen2(rdev, enable);

	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, ENABLE_GEN2PCIE, ~ENABLE_GEN2PCIE);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~ENABLE_GEN2PCIE);
पूर्ण

अटल व्योम r7xx_program_memory_timing_parameters(काष्ठा radeon_device *rdev,
						  काष्ठा radeon_ps *radeon_new_state)
अणु
	अगर ((rdev->family == CHIP_RV730) ||
	    (rdev->family == CHIP_RV710) ||
	    (rdev->family == CHIP_RV740))
		rv730_program_memory_timing_parameters(rdev, radeon_new_state);
	अन्यथा
		rv770_program_memory_timing_parameters(rdev, radeon_new_state);
पूर्ण

अटल पूर्णांक rv770_upload_sw_state(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_ps *radeon_new_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u16 address = pi->state_table_start +
		दुरत्व(RV770_SMC_STATETABLE, driverState);
	RV770_SMC_SWSTATE state = अणु 0 पूर्ण;
	पूर्णांक ret;

	ret = rv770_convert_घातer_state_to_smc(rdev, radeon_new_state, &state);
	अगर (ret)
		वापस ret;

	वापस rv770_copy_bytes_to_smc(rdev, address, (स्थिर u8 *)&state,
				       माप(RV770_SMC_SWSTATE),
				       pi->sram_end);
पूर्ण

पूर्णांक rv770_halt_smc(काष्ठा radeon_device *rdev)
अणु
	अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_Halt) != PPSMC_Result_OK)
		वापस -EINVAL;

	अगर (rv770_रुको_क्रम_smc_inactive(rdev) != PPSMC_Result_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक rv770_resume_smc(काष्ठा radeon_device *rdev)
अणु
	अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_Resume) != PPSMC_Result_OK)
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक rv770_set_sw_state(काष्ठा radeon_device *rdev)
अणु
	अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_SwitchToSwState) != PPSMC_Result_OK)
		DRM_DEBUG("rv770_set_sw_state failed\n");
	वापस 0;
पूर्ण

पूर्णांक rv770_set_boot_state(काष्ठा radeon_device *rdev)
अणु
	अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_SwitchToInitialState) != PPSMC_Result_OK)
		वापस -EINVAL;
	वापस 0;
पूर्ण

व्योम rv770_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(काष्ठा radeon_device *rdev,
					      काष्ठा radeon_ps *new_ps,
					      काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv7xx_ps *new_state = rv770_get_ps(new_ps);
	काष्ठा rv7xx_ps *current_state = rv770_get_ps(old_ps);

	अगर ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		वापस;

	अगर (new_state->high.sclk >= current_state->high.sclk)
		वापस;

	radeon_set_uvd_घड़ीs(rdev, new_ps->vclk, new_ps->dclk);
पूर्ण

व्योम rv770_set_uvd_घड़ी_after_set_eng_घड़ी(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ps *new_ps,
					     काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv7xx_ps *new_state = rv770_get_ps(new_ps);
	काष्ठा rv7xx_ps *current_state = rv770_get_ps(old_ps);

	अगर ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		वापस;

	अगर (new_state->high.sclk < current_state->high.sclk)
		वापस;

	radeon_set_uvd_घड़ीs(rdev, new_ps->vclk, new_ps->dclk);
पूर्ण

पूर्णांक rv770_restrict_perक्रमmance_levels_beक्रमe_चयन(काष्ठा radeon_device *rdev)
अणु
	अगर (rv770_send_msg_to_smc(rdev, (PPSMC_Msg)(PPSMC_MSG_NoForcedLevel)) != PPSMC_Result_OK)
		वापस -EINVAL;

	अगर (rv770_send_msg_to_smc(rdev, (PPSMC_Msg)(PPSMC_MSG_TwoLevelsDisabled)) != PPSMC_Result_OK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक rv770_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				      क्रमागत radeon_dpm_क्रमced_level level)
अणु
	PPSMC_Msg msg;

	अगर (level == RADEON_DPM_FORCED_LEVEL_HIGH) अणु
		अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_ZeroLevelsDisabled) != PPSMC_Result_OK)
			वापस -EINVAL;
		msg = PPSMC_MSG_ForceHigh;
	पूर्ण अन्यथा अगर (level == RADEON_DPM_FORCED_LEVEL_LOW) अणु
		अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_NoForcedLevel) != PPSMC_Result_OK)
			वापस -EINVAL;
		msg = (PPSMC_Msg)(PPSMC_MSG_TwoLevelsDisabled);
	पूर्ण अन्यथा अणु
		अगर (rv770_send_msg_to_smc(rdev, PPSMC_MSG_NoForcedLevel) != PPSMC_Result_OK)
			वापस -EINVAL;
		msg = (PPSMC_Msg)(PPSMC_MSG_ZeroLevelsDisabled);
	पूर्ण

	अगर (rv770_send_msg_to_smc(rdev, msg) != PPSMC_Result_OK)
		वापस -EINVAL;

	rdev->pm.dpm.क्रमced_level = level;

	वापस 0;
पूर्ण

व्योम r7xx_start_smc(काष्ठा radeon_device *rdev)
अणु
	rv770_start_smc(rdev);
	rv770_start_smc_घड़ी(rdev);
पूर्ण


व्योम r7xx_stop_smc(काष्ठा radeon_device *rdev)
अणु
	rv770_reset_smc(rdev);
	rv770_stop_smc_घड़ी(rdev);
पूर्ण

अटल व्योम rv770_पढ़ो_घड़ी_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	pi->clk_regs.rv770.cg_spll_func_cntl =
		RREG32(CG_SPLL_FUNC_CNTL);
	pi->clk_regs.rv770.cg_spll_func_cntl_2 =
		RREG32(CG_SPLL_FUNC_CNTL_2);
	pi->clk_regs.rv770.cg_spll_func_cntl_3 =
		RREG32(CG_SPLL_FUNC_CNTL_3);
	pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum =
		RREG32(CG_SPLL_SPREAD_SPECTRUM);
	pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum_2 =
		RREG32(CG_SPLL_SPREAD_SPECTRUM_2);
	pi->clk_regs.rv770.mpll_ad_func_cntl =
		RREG32(MPLL_AD_FUNC_CNTL);
	pi->clk_regs.rv770.mpll_ad_func_cntl_2 =
		RREG32(MPLL_AD_FUNC_CNTL_2);
	pi->clk_regs.rv770.mpll_dq_func_cntl =
		RREG32(MPLL_DQ_FUNC_CNTL);
	pi->clk_regs.rv770.mpll_dq_func_cntl_2 =
		RREG32(MPLL_DQ_FUNC_CNTL_2);
	pi->clk_regs.rv770.mclk_pwrmgt_cntl =
		RREG32(MCLK_PWRMGT_CNTL);
	pi->clk_regs.rv770.dll_cntl = RREG32(DLL_CNTL);
पूर्ण

अटल व्योम r7xx_पढ़ो_घड़ी_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->family == CHIP_RV740)
		rv740_पढ़ो_घड़ी_रेजिस्टरs(rdev);
	अन्यथा अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		rv730_पढ़ो_घड़ी_रेजिस्टरs(rdev);
	अन्यथा
		rv770_पढ़ो_घड़ी_रेजिस्टरs(rdev);
पूर्ण

व्योम rv770_पढ़ो_voltage_smio_रेजिस्टरs(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	pi->s0_vid_lower_smio_cntl =
		RREG32(S0_VID_LOWER_SMIO_CNTL);
पूर्ण

व्योम rv770_reset_smio_status(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 sw_smio_index, vid_smio_cntl;

	sw_smio_index =
		(RREG32(GENERAL_PWRMGT) & SW_SMIO_INDEX_MASK) >> SW_SMIO_INDEX_SHIFT;
	चयन (sw_smio_index) अणु
	हाल 3:
		vid_smio_cntl = RREG32(S3_VID_LOWER_SMIO_CNTL);
		अवरोध;
	हाल 2:
		vid_smio_cntl = RREG32(S2_VID_LOWER_SMIO_CNTL);
		अवरोध;
	हाल 1:
		vid_smio_cntl = RREG32(S1_VID_LOWER_SMIO_CNTL);
		अवरोध;
	हाल 0:
		वापस;
	शेष:
		vid_smio_cntl = pi->s0_vid_lower_smio_cntl;
		अवरोध;
	पूर्ण

	WREG32(S0_VID_LOWER_SMIO_CNTL, vid_smio_cntl);
	WREG32_P(GENERAL_PWRMGT, SW_SMIO_INDEX(0), ~SW_SMIO_INDEX_MASK);
पूर्ण

व्योम rv770_get_memory_type(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 पंचांगp;

	पंचांगp = RREG32(MC_SEQ_MISC0);

	अगर (((पंचांगp & MC_SEQ_MISC0_GDDR5_MASK) >> MC_SEQ_MISC0_GDDR5_SHIFT) ==
	    MC_SEQ_MISC0_GDDR5_VALUE)
		pi->mem_gddr5 = true;
	अन्यथा
		pi->mem_gddr5 = false;

पूर्ण

व्योम rv770_get_pcie_gen2_status(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);

	अगर ((पंचांगp & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
	    (पंचांगp & LC_OTHER_SIDE_SUPPORTS_GEN2))
		pi->pcie_gen2 = true;
	अन्यथा
		pi->pcie_gen2 = false;

	अगर (pi->pcie_gen2) अणु
		अगर (पंचांगp & LC_CURRENT_DATA_RATE)
			pi->boot_in_gen2 = true;
		अन्यथा
			pi->boot_in_gen2 = false;
	पूर्ण अन्यथा
		pi->boot_in_gen2 = false;
पूर्ण

#अगर 0
अटल पूर्णांक rv770_enter_ulp_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (pi->gfx_घड़ी_gating) अणु
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);
		WREG32_P(SCLK_PWRMGT_CNTL, GFX_CLK_FORCE_ON, ~GFX_CLK_FORCE_ON);
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~GFX_CLK_FORCE_ON);
		RREG32(GB_TILING_CONFIG);
	पूर्ण

	WREG32_P(SMC_MSG, HOST_SMC_MSG(PPSMC_MSG_SwitchToMinimumPower),
		 ~HOST_SMC_MSG_MASK);

	udelay(7000);

	वापस 0;
पूर्ण

अटल पूर्णांक rv770_निकास_ulp_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	पूर्णांक i;

	WREG32_P(SMC_MSG, HOST_SMC_MSG(PPSMC_MSG_ResumeFromMinimumPower),
		 ~HOST_SMC_MSG_MASK);

	udelay(7000);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (((RREG32(SMC_MSG) & HOST_SMC_RESP_MASK) >> HOST_SMC_RESP_SHIFT) == 1)
			अवरोध;
		udelay(1000);
	पूर्ण

	अगर (pi->gfx_घड़ी_gating)
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम rv770_get_mclk_odt_threshold(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u8 memory_module_index;
	काष्ठा atom_memory_info memory_info;

	pi->mclk_odt_threshold = 0;

	अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710)) अणु
		memory_module_index = rv770_get_memory_module_index(rdev);

		अगर (radeon_atom_get_memory_info(rdev, memory_module_index, &memory_info))
			वापस;

		अगर (memory_info.mem_type == MEM_TYPE_DDR2 ||
		    memory_info.mem_type == MEM_TYPE_DDR3)
			pi->mclk_odt_threshold = 30000;
	पूर्ण
पूर्ण

व्योम rv770_get_max_vddc(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u16 vddc;

	अगर (radeon_atom_get_max_vddc(rdev, 0, 0, &vddc))
		pi->max_vddc = 0;
	अन्यथा
		pi->max_vddc = vddc;
पूर्ण

व्योम rv770_program_response_बार(काष्ठा radeon_device *rdev)
अणु
	u32 voltage_response_समय, backbias_response_समय;
	u32 acpi_delay_समय, vbi_समय_out;
	u32 vddc_dly, bb_dly, acpi_dly, vbi_dly;
	u32 reference_घड़ी;

	voltage_response_समय = (u32)rdev->pm.dpm.voltage_response_समय;
	backbias_response_समय = (u32)rdev->pm.dpm.backbias_response_समय;

	अगर (voltage_response_समय == 0)
		voltage_response_समय = 1000;

	अगर (backbias_response_समय == 0)
		backbias_response_समय = 1000;

	acpi_delay_समय = 15000;
	vbi_समय_out = 100000;

	reference_घड़ी = radeon_get_xclk(rdev);

	vddc_dly = (voltage_response_समय  * reference_घड़ी) / 1600;
	bb_dly = (backbias_response_समय * reference_घड़ी) / 1600;
	acpi_dly = (acpi_delay_समय * reference_घड़ी) / 1600;
	vbi_dly = (vbi_समय_out * reference_घड़ी) / 1600;

	rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
				      RV770_SMC_SOFT_REGISTER_delay_vreg, vddc_dly);
	rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
				      RV770_SMC_SOFT_REGISTER_delay_bbias, bb_dly);
	rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
				      RV770_SMC_SOFT_REGISTER_delay_acpi, acpi_dly);
	rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
				      RV770_SMC_SOFT_REGISTER_mclk_chg_समयout, vbi_dly);
#अगर 0
	/* XXX look up hw revision */
	अगर (WEKIVA_A21)
		rv770_ग_लिखो_smc_soft_रेजिस्टर(rdev,
					      RV770_SMC_SOFT_REGISTER_baby_step_समयr,
					      0x10);
#पूर्ण_अगर
पूर्ण

अटल व्योम rv770_program_dcodt_beक्रमe_state_चयन(काष्ठा radeon_device *rdev,
						    काष्ठा radeon_ps *radeon_new_state,
						    काष्ठा radeon_ps *radeon_current_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा rv7xx_ps *new_state = rv770_get_ps(radeon_new_state);
	काष्ठा rv7xx_ps *current_state = rv770_get_ps(radeon_current_state);
	bool current_use_dc = false;
	bool new_use_dc = false;

	अगर (pi->mclk_odt_threshold == 0)
		वापस;

	अगर (current_state->high.mclk <= pi->mclk_odt_threshold)
		current_use_dc = true;

	अगर (new_state->high.mclk <= pi->mclk_odt_threshold)
		new_use_dc = true;

	अगर (current_use_dc == new_use_dc)
		वापस;

	अगर (!current_use_dc && new_use_dc)
		वापस;

	अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		rv730_program_dcodt(rdev, new_use_dc);
पूर्ण

अटल व्योम rv770_program_dcodt_after_state_चयन(काष्ठा radeon_device *rdev,
						   काष्ठा radeon_ps *radeon_new_state,
						   काष्ठा radeon_ps *radeon_current_state)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा rv7xx_ps *new_state = rv770_get_ps(radeon_new_state);
	काष्ठा rv7xx_ps *current_state = rv770_get_ps(radeon_current_state);
	bool current_use_dc = false;
	bool new_use_dc = false;

	अगर (pi->mclk_odt_threshold == 0)
		वापस;

	अगर (current_state->high.mclk <= pi->mclk_odt_threshold)
		current_use_dc = true;

	अगर (new_state->high.mclk <= pi->mclk_odt_threshold)
		new_use_dc = true;

	अगर (current_use_dc == new_use_dc)
		वापस;

	अगर (current_use_dc && !new_use_dc)
		वापस;

	अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		rv730_program_dcodt(rdev, new_use_dc);
पूर्ण

अटल व्योम rv770_retrieve_odt_values(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (pi->mclk_odt_threshold == 0)
		वापस;

	अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		rv730_get_odt_values(rdev);
पूर्ण

अटल व्योम rv770_set_dpm_event_sources(काष्ठा radeon_device *rdev, u32 sources)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	bool want_thermal_protection;
	क्रमागत radeon_dpm_event_src dpm_event_src;

	चयन (sources) अणु
	हाल 0:
	शेष:
		want_thermal_protection = false;
		अवरोध;
	हाल (1 << RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL):
		want_thermal_protection = true;
		dpm_event_src = RADEON_DPM_EVENT_SRC_DIGITAL;
		अवरोध;

	हाल (1 << RADEON_DPM_AUTO_THROTTLE_SRC_EXTERNAL):
		want_thermal_protection = true;
		dpm_event_src = RADEON_DPM_EVENT_SRC_EXTERNAL;
		अवरोध;

	हाल ((1 << RADEON_DPM_AUTO_THROTTLE_SRC_EXTERNAL) |
	      (1 << RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL)):
		want_thermal_protection = true;
		dpm_event_src = RADEON_DPM_EVENT_SRC_DIGIAL_OR_EXTERNAL;
		अवरोध;
	पूर्ण

	अगर (want_thermal_protection) अणु
		WREG32_P(CG_THERMAL_CTRL, DPM_EVENT_SRC(dpm_event_src), ~DPM_EVENT_SRC_MASK);
		अगर (pi->thermal_protection)
			WREG32_P(GENERAL_PWRMGT, 0, ~THERMAL_PROTECTION_DIS);
	पूर्ण अन्यथा अणु
		WREG32_P(GENERAL_PWRMGT, THERMAL_PROTECTION_DIS, ~THERMAL_PROTECTION_DIS);
	पूर्ण
पूर्ण

व्योम rv770_enable_स्वतः_throttle_source(काष्ठा radeon_device *rdev,
				       क्रमागत radeon_dpm_स्वतः_throttle_src source,
				       bool enable)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (enable) अणु
		अगर (!(pi->active_स्वतः_throttle_sources & (1 << source))) अणु
			pi->active_स्वतः_throttle_sources |= 1 << source;
			rv770_set_dpm_event_sources(rdev, pi->active_स्वतः_throttle_sources);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pi->active_स्वतः_throttle_sources & (1 << source)) अणु
			pi->active_स्वतः_throttle_sources &= ~(1 << source);
			rv770_set_dpm_event_sources(rdev, pi->active_स्वतः_throttle_sources);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rv770_set_thermal_temperature_range(काष्ठा radeon_device *rdev,
					       पूर्णांक min_temp, पूर्णांक max_temp)
अणु
	पूर्णांक low_temp = 0 * 1000;
	पूर्णांक high_temp = 255 * 1000;

	अगर (low_temp < min_temp)
		low_temp = min_temp;
	अगर (high_temp > max_temp)
		high_temp = max_temp;
	अगर (high_temp < low_temp) अणु
		DRM_ERROR("invalid thermal range: %d - %d\n", low_temp, high_temp);
		वापस -EINVAL;
	पूर्ण

	WREG32_P(CG_THERMAL_INT, DIG_THERM_INTH(high_temp / 1000), ~DIG_THERM_INTH_MASK);
	WREG32_P(CG_THERMAL_INT, DIG_THERM_INTL(low_temp / 1000), ~DIG_THERM_INTL_MASK);
	WREG32_P(CG_THERMAL_CTRL, DIG_THERM_DPM(high_temp / 1000), ~DIG_THERM_DPM_MASK);

	rdev->pm.dpm.thermal.min_temp = low_temp;
	rdev->pm.dpm.thermal.max_temp = high_temp;

	वापस 0;
पूर्ण

पूर्णांक rv770_dpm_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;
	पूर्णांक ret;

	अगर (pi->gfx_घड़ी_gating)
		rv770_restore_cgcg(rdev);

	अगर (rv770_dpm_enabled(rdev))
		वापस -EINVAL;

	अगर (pi->voltage_control) अणु
		rv770_enable_voltage_control(rdev, true);
		ret = rv770_स्थिरruct_vddc_table(rdev);
		अगर (ret) अणु
			DRM_ERROR("rv770_construct_vddc_table failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pi->dcodt)
		rv770_retrieve_odt_values(rdev);

	अगर (pi->mvdd_control) अणु
		ret = rv770_get_mvdd_configuration(rdev);
		अगर (ret) अणु
			DRM_ERROR("rv770_get_mvdd_configuration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv770_enable_backbias(rdev, true);

	rv770_enable_spपढ़ो_spectrum(rdev, true);

	अगर (pi->thermal_protection)
		rv770_enable_thermal_protection(rdev, true);

	rv770_program_mpll_timing_parameters(rdev);
	rv770_setup_bsp(rdev);
	rv770_program_git(rdev);
	rv770_program_tp(rdev);
	rv770_program_tpp(rdev);
	rv770_program_sstp(rdev);
	rv770_program_engine_speed_parameters(rdev);
	rv770_enable_display_gap(rdev);
	rv770_program_vc(rdev);

	अगर (pi->dynamic_pcie_gen2)
		rv770_enable_dynamic_pcie_gen2(rdev, true);

	ret = rv770_upload_firmware(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_upload_firmware failed\n");
		वापस ret;
	पूर्ण
	ret = rv770_init_smc_table(rdev, boot_ps);
	अगर (ret) अणु
		DRM_ERROR("rv770_init_smc_table failed\n");
		वापस ret;
	पूर्ण

	rv770_program_response_बार(rdev);
	r7xx_start_smc(rdev);

	अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		rv730_start_dpm(rdev);
	अन्यथा
		rv770_start_dpm(rdev);

	अगर (pi->gfx_घड़ी_gating)
		rv770_gfx_घड़ी_gating_enable(rdev, true);

	अगर (pi->mg_घड़ी_gating)
		rv770_mg_घड़ी_gating_enable(rdev, true);

	rv770_enable_स्वतः_throttle_source(rdev, RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	वापस 0;
पूर्ण

पूर्णांक rv770_dpm_late_enable(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		PPSMC_Result result;

		ret = rv770_set_thermal_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
		अगर (ret)
			वापस ret;
		rdev->irq.dpm_thermal = true;
		radeon_irq_set(rdev);
		result = rv770_send_msg_to_smc(rdev, PPSMC_MSG_EnableThermalInterrupt);

		अगर (result != PPSMC_Result_OK)
			DRM_DEBUG_KMS("Could not enable thermal interrupts.\n");
	पूर्ण

	वापस 0;
पूर्ण

व्योम rv770_dpm_disable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	अगर (!rv770_dpm_enabled(rdev))
		वापस;

	rv770_clear_vc(rdev);

	अगर (pi->thermal_protection)
		rv770_enable_thermal_protection(rdev, false);

	rv770_enable_spपढ़ो_spectrum(rdev, false);

	अगर (pi->dynamic_pcie_gen2)
		rv770_enable_dynamic_pcie_gen2(rdev, false);

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	पूर्ण

	अगर (pi->gfx_घड़ी_gating)
		rv770_gfx_घड़ी_gating_enable(rdev, false);

	अगर (pi->mg_घड़ी_gating)
		rv770_mg_घड़ी_gating_enable(rdev, false);

	अगर ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710))
		rv730_stop_dpm(rdev);
	अन्यथा
		rv770_stop_dpm(rdev);

	r7xx_stop_smc(rdev);
	rv770_reset_smio_status(rdev);
पूर्ण

पूर्णांक rv770_dpm_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	काष्ठा radeon_ps *old_ps = rdev->pm.dpm.current_ps;
	पूर्णांक ret;

	ret = rv770_restrict_perक्रमmance_levels_beक्रमe_चयन(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_restrict_performance_levels_before_switch failed\n");
		वापस ret;
	पूर्ण
	rv770_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(rdev, new_ps, old_ps);
	ret = rv770_halt_smc(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_halt_smc failed\n");
		वापस ret;
	पूर्ण
	ret = rv770_upload_sw_state(rdev, new_ps);
	अगर (ret) अणु
		DRM_ERROR("rv770_upload_sw_state failed\n");
		वापस ret;
	पूर्ण
	r7xx_program_memory_timing_parameters(rdev, new_ps);
	अगर (pi->dcodt)
		rv770_program_dcodt_beक्रमe_state_चयन(rdev, new_ps, old_ps);
	ret = rv770_resume_smc(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_resume_smc failed\n");
		वापस ret;
	पूर्ण
	ret = rv770_set_sw_state(rdev);
	अगर (ret) अणु
		DRM_ERROR("rv770_set_sw_state failed\n");
		वापस ret;
	पूर्ण
	अगर (pi->dcodt)
		rv770_program_dcodt_after_state_चयन(rdev, new_ps, old_ps);
	rv770_set_uvd_घड़ी_after_set_eng_घड़ी(rdev, new_ps, old_ps);

	वापस 0;
पूर्ण

#अगर 0
व्योम rv770_dpm_reset_asic(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;

	rv770_restrict_perक्रमmance_levels_beक्रमe_चयन(rdev);
	अगर (pi->dcodt)
		rv770_program_dcodt_beक्रमe_state_चयन(rdev, boot_ps, boot_ps);
	rv770_set_boot_state(rdev);
	अगर (pi->dcodt)
		rv770_program_dcodt_after_state_चयन(rdev, boot_ps, boot_ps);
पूर्ण
#पूर्ण_अगर

व्योम rv770_dpm_setup_asic(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);

	r7xx_पढ़ो_घड़ी_रेजिस्टरs(rdev);
	rv770_पढ़ो_voltage_smio_रेजिस्टरs(rdev);
	rv770_get_memory_type(rdev);
	अगर (pi->dcodt)
		rv770_get_mclk_odt_threshold(rdev);
	rv770_get_pcie_gen2_status(rdev);

	rv770_enable_acpi_pm(rdev);

	अगर (radeon_aspm != 0) अणु
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_ASPM_L0s)
			rv770_enable_l0s(rdev);
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_ASPM_L1)
			rv770_enable_l1(rdev);
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_TURNOFFPLL_ASPML1)
			rv770_enable_pll_sleep_in_l1(rdev);
	पूर्ण
पूर्ण

व्योम rv770_dpm_display_configuration_changed(काष्ठा radeon_device *rdev)
अणु
	rv770_program_display_gap(rdev);
पूर्ण

जोड़ घातer_info अणु
	काष्ठा _ATOM_POWERPLAY_INFO info;
	काष्ठा _ATOM_POWERPLAY_INFO_V2 info_2;
	काष्ठा _ATOM_POWERPLAY_INFO_V3 info_3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE pplib;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE2 pplib2;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3 pplib3;
पूर्ण;

जोड़ pplib_घड़ी_info अणु
	काष्ठा _ATOM_PPLIB_R600_CLOCK_INFO r600;
	काष्ठा _ATOM_PPLIB_RS780_CLOCK_INFO rs780;
	काष्ठा _ATOM_PPLIB_EVERGREEN_CLOCK_INFO evergreen;
	काष्ठा _ATOM_PPLIB_SUMO_CLOCK_INFO sumo;
पूर्ण;

जोड़ pplib_घातer_state अणु
	काष्ठा _ATOM_PPLIB_STATE v1;
	काष्ठा _ATOM_PPLIB_STATE_V2 v2;
पूर्ण;

अटल व्योम rv7xx_parse_pplib_non_घड़ी_info(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ps *rps,
					     काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info,
					     u8 table_rev)
अणु
	rps->caps = le32_to_cpu(non_घड़ी_info->ulCapsAndSettings);
	rps->class = le16_to_cpu(non_घड़ी_info->usClassअगरication);
	rps->class2 = le16_to_cpu(non_घड़ी_info->usClassअगरication2);

	अगर (ATOM_PPLIB_NONCLOCKINFO_VER1 < table_rev) अणु
		rps->vclk = le32_to_cpu(non_घड़ी_info->ulVCLK);
		rps->dclk = le32_to_cpu(non_घड़ी_info->ulDCLK);
	पूर्ण अन्यथा अणु
		rps->vclk = 0;
		rps->dclk = 0;
	पूर्ण

	अगर (r600_is_uvd_state(rps->class, rps->class2)) अणु
		अगर ((rps->vclk == 0) || (rps->dclk == 0)) अणु
			rps->vclk = RV770_DEFAULT_VCLK_FREQ;
			rps->dclk = RV770_DEFAULT_DCLK_FREQ;
		पूर्ण
	पूर्ण

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT)
		rdev->pm.dpm.boot_ps = rps;
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		rdev->pm.dpm.uvd_ps = rps;
पूर्ण

अटल व्योम rv7xx_parse_pplib_घड़ी_info(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_ps *rps, पूर्णांक index,
					 जोड़ pplib_घड़ी_info *घड़ी_info)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा evergreen_घातer_info *eg_pi = evergreen_get_pi(rdev);
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	u32 sclk, mclk;
	काष्ठा rv7xx_pl *pl;

	चयन (index) अणु
	हाल 0:
		pl = &ps->low;
		अवरोध;
	हाल 1:
		pl = &ps->medium;
		अवरोध;
	हाल 2:
	शेष:
		pl = &ps->high;
		अवरोध;
	पूर्ण

	अगर (rdev->family >= CHIP_CEDAR) अणु
		sclk = le16_to_cpu(घड़ी_info->evergreen.usEngineClockLow);
		sclk |= घड़ी_info->evergreen.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(घड़ी_info->evergreen.usMemoryClockLow);
		mclk |= घड़ी_info->evergreen.ucMemoryClockHigh << 16;

		pl->vddc = le16_to_cpu(घड़ी_info->evergreen.usVDDC);
		pl->vddci = le16_to_cpu(घड़ी_info->evergreen.usVDDCI);
		pl->flags = le32_to_cpu(घड़ी_info->evergreen.ulFlags);
	पूर्ण अन्यथा अणु
		sclk = le16_to_cpu(घड़ी_info->r600.usEngineClockLow);
		sclk |= घड़ी_info->r600.ucEngineClockHigh << 16;
		mclk = le16_to_cpu(घड़ी_info->r600.usMemoryClockLow);
		mclk |= घड़ी_info->r600.ucMemoryClockHigh << 16;

		pl->vddc = le16_to_cpu(घड़ी_info->r600.usVDDC);
		pl->flags = le32_to_cpu(घड़ी_info->r600.ulFlags);
	पूर्ण

	pl->mclk = mclk;
	pl->sclk = sclk;

	/* patch up vddc अगर necessary */
	अगर (pl->vddc == 0xff01) अणु
		अगर (pi->max_vddc)
			pl->vddc = pi->max_vddc;
	पूर्ण

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_ACPI) अणु
		pi->acpi_vddc = pl->vddc;
		अगर (rdev->family >= CHIP_CEDAR)
			eg_pi->acpi_vddci = pl->vddci;
		अगर (ps->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2)
			pi->acpi_pcie_gen2 = true;
		अन्यथा
			pi->acpi_pcie_gen2 = false;
	पूर्ण

	अगर (rps->class2 & ATOM_PPLIB_CLASSIFICATION2_ULV) अणु
		अगर (rdev->family >= CHIP_BARTS) अणु
			eg_pi->ulv.supported = true;
			eg_pi->ulv.pl = pl;
		पूर्ण
	पूर्ण

	अगर (pi->min_vddc_in_table > pl->vddc)
		pi->min_vddc_in_table = pl->vddc;

	अगर (pi->max_vddc_in_table < pl->vddc)
		pi->max_vddc_in_table = pl->vddc;

	/* patch up boot state */
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) अणु
		u16 vddc, vddci, mvdd;
		radeon_atombios_get_शेष_voltages(rdev, &vddc, &vddci, &mvdd);
		pl->mclk = rdev->घड़ी.शेष_mclk;
		pl->sclk = rdev->घड़ी.शेष_sclk;
		pl->vddc = vddc;
		pl->vddci = vddci;
	पूर्ण

	अगर ((rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) ==
	    ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE) अणु
		rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.sclk = pl->sclk;
		rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.mclk = pl->mclk;
		rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.vddc = pl->vddc;
		rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_ac.vddci = pl->vddci;
	पूर्ण
पूर्ण

पूर्णांक rv7xx_parse_घातer_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info;
	जोड़ pplib_घातer_state *घातer_state;
	पूर्णांक i, j;
	जोड़ pplib_घड़ी_info *घड़ी_info;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	काष्ठा rv7xx_ps *ps;

	अगर (!atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस -EINVAL;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	rdev->pm.dpm.ps = kसुस्मृति(घातer_info->pplib.ucNumStates,
				  माप(काष्ठा radeon_ps),
				  GFP_KERNEL);
	अगर (!rdev->pm.dpm.ps)
		वापस -ENOMEM;

	क्रम (i = 0; i < घातer_info->pplib.ucNumStates; i++) अणु
		घातer_state = (जोड़ pplib_घातer_state *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(घातer_info->pplib.usStateArrayOffset) +
			 i * घातer_info->pplib.ucStateEntrySize);
		non_घड़ी_info = (काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(घातer_info->pplib.usNonClockInfoArrayOffset) +
			 (घातer_state->v1.ucNonClockStateIndex *
			  घातer_info->pplib.ucNonClockSize));
		अगर (घातer_info->pplib.ucStateEntrySize - 1) अणु
			u8 *idx;
			ps = kzalloc(माप(काष्ठा rv7xx_ps), GFP_KERNEL);
			अगर (ps == शून्य) अणु
				kमुक्त(rdev->pm.dpm.ps);
				वापस -ENOMEM;
			पूर्ण
			rdev->pm.dpm.ps[i].ps_priv = ps;
			rv7xx_parse_pplib_non_घड़ी_info(rdev, &rdev->pm.dpm.ps[i],
							 non_घड़ी_info,
							 घातer_info->pplib.ucNonClockSize);
			idx = (u8 *)&घातer_state->v1.ucClockStateIndices[0];
			क्रम (j = 0; j < (घातer_info->pplib.ucStateEntrySize - 1); j++) अणु
				घड़ी_info = (जोड़ pplib_घड़ी_info *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(घातer_info->pplib.usClockInfoArrayOffset) +
					 (idx[j] * घातer_info->pplib.ucClockInfoSize));
				rv7xx_parse_pplib_घड़ी_info(rdev,
							     &rdev->pm.dpm.ps[i], j,
							     घड़ी_info);
			पूर्ण
		पूर्ण
	पूर्ण
	rdev->pm.dpm.num_ps = घातer_info->pplib.ucNumStates;
	वापस 0;
पूर्ण

व्योम rv770_get_engine_memory_ss(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा radeon_atom_ss ss;

	pi->sclk_ss = radeon_atombios_get_asic_ss_info(rdev, &ss,
						       ASIC_INTERNAL_ENGINE_SS, 0);
	pi->mclk_ss = radeon_atombios_get_asic_ss_info(rdev, &ss,
						       ASIC_INTERNAL_MEMORY_SS, 0);

	अगर (pi->sclk_ss || pi->mclk_ss)
		pi->dynamic_ss = true;
	अन्यथा
		pi->dynamic_ss = false;
पूर्ण

पूर्णांक rv770_dpm_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv7xx_घातer_info *pi;
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;

	pi = kzalloc(माप(काष्ठा rv7xx_घातer_info), GFP_KERNEL);
	अगर (pi == शून्य)
		वापस -ENOMEM;
	rdev->pm.dpm.priv = pi;

	rv770_get_max_vddc(rdev);

	pi->acpi_vddc = 0;
	pi->min_vddc_in_table = 0;
	pi->max_vddc_in_table = 0;

	ret = r600_get_platक्रमm_caps(rdev);
	अगर (ret)
		वापस ret;

	ret = rv7xx_parse_घातer_table(rdev);
	अगर (ret)
		वापस ret;

	अगर (rdev->pm.dpm.voltage_response_समय == 0)
		rdev->pm.dpm.voltage_response_समय = R600_VOLTAGERESPONSETIME_DFLT;
	अगर (rdev->pm.dpm.backbias_response_समय == 0)
		rdev->pm.dpm.backbias_response_समय = R600_BACKBIASRESPONSETIME_DFLT;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &भागiders);
	अगर (ret)
		pi->ref_भाग = भागiders.ref_भाग + 1;
	अन्यथा
		pi->ref_भाग = R600_REFERENCEDIVIDER_DFLT;

	pi->mclk_strobe_mode_threshold = 30000;
	pi->mclk_edc_enable_threshold = 30000;

	pi->rlp = RV770_RLP_DFLT;
	pi->rmp = RV770_RMP_DFLT;
	pi->lhp = RV770_LHP_DFLT;
	pi->lmp = RV770_LMP_DFLT;

	pi->voltage_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_MVDDC, 0);

	rv770_get_engine_memory_ss(rdev);

	pi->asi = RV770_ASI_DFLT;
	pi->pasi = RV770_HASI_DFLT;
	pi->vrc = RV770_VRC_DFLT;

	pi->घातer_gating = false;

	pi->gfx_घड़ी_gating = true;

	pi->mg_घड़ी_gating = true;
	pi->mgcgtssm = true;

	pi->dynamic_pcie_gen2 = true;

	अगर (rdev->pm.पूर्णांक_thermal_type != THERMAL_TYPE_NONE)
		pi->thermal_protection = true;
	अन्यथा
		pi->thermal_protection = false;

	pi->display_gap = true;

	अगर (rdev->flags & RADEON_IS_MOBILITY)
		pi->dcodt = true;
	अन्यथा
		pi->dcodt = false;

	pi->ulps = true;

	pi->mclk_stutter_mode_threshold = 0;

	pi->sram_end = SMC_RAM_END;
	pi->state_table_start = RV770_SMC_TABLE_ADDRESS;
	pi->soft_regs_start = RV770_SMC_SOFT_REGISTERS_START;

	वापस 0;
पूर्ण

व्योम rv770_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_ps *rps)
अणु
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	काष्ठा rv7xx_pl *pl;

	r600_dpm_prपूर्णांक_class_info(rps->class, rps->class2);
	r600_dpm_prपूर्णांक_cap_info(rps->caps);
	prपूर्णांकk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	अगर (rdev->family >= CHIP_CEDAR) अणु
		pl = &ps->low;
		prपूर्णांकk("\t\tpower level 0    sclk: %u mclk: %u vddc: %u vddci: %u\n",
		       pl->sclk, pl->mclk, pl->vddc, pl->vddci);
		pl = &ps->medium;
		prपूर्णांकk("\t\tpower level 1    sclk: %u mclk: %u vddc: %u vddci: %u\n",
		       pl->sclk, pl->mclk, pl->vddc, pl->vddci);
		pl = &ps->high;
		prपूर्णांकk("\t\tpower level 2    sclk: %u mclk: %u vddc: %u vddci: %u\n",
		       pl->sclk, pl->mclk, pl->vddc, pl->vddci);
	पूर्ण अन्यथा अणु
		pl = &ps->low;
		prपूर्णांकk("\t\tpower level 0    sclk: %u mclk: %u vddc: %u\n",
		       pl->sclk, pl->mclk, pl->vddc);
		pl = &ps->medium;
		prपूर्णांकk("\t\tpower level 1    sclk: %u mclk: %u vddc: %u\n",
		       pl->sclk, pl->mclk, pl->vddc);
		pl = &ps->high;
		prपूर्णांकk("\t\tpower level 2    sclk: %u mclk: %u vddc: %u\n",
		       pl->sclk, pl->mclk, pl->vddc);
	पूर्ण
	r600_dpm_prपूर्णांक_ps_status(rdev, rps);
पूर्ण

व्योम rv770_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						       काष्ठा seq_file *m)
अणु
	काष्ठा radeon_ps *rps = rdev->pm.dpm.current_ps;
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	काष्ठा rv7xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_PROखाता_INDEX_MASK) >>
		CURRENT_PROखाता_INDEX_SHIFT;

	अगर (current_index > 2) अणु
		seq_म_लिखो(m, "invalid dpm profile %d\n", current_index);
	पूर्ण अन्यथा अणु
		अगर (current_index == 0)
			pl = &ps->low;
		अन्यथा अगर (current_index == 1)
			pl = &ps->medium;
		अन्यथा /* current_index == 2 */
			pl = &ps->high;
		seq_म_लिखो(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
		अगर (rdev->family >= CHIP_CEDAR) अणु
			seq_म_लिखो(m, "power level %d    sclk: %u mclk: %u vddc: %u vddci: %u\n",
				   current_index, pl->sclk, pl->mclk, pl->vddc, pl->vddci);
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m, "power level %d    sclk: %u mclk: %u vddc: %u\n",
				   current_index, pl->sclk, pl->mclk, pl->vddc);
		पूर्ण
	पूर्ण
पूर्ण

u32 rv770_dpm_get_current_sclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ps *rps = rdev->pm.dpm.current_ps;
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	काष्ठा rv7xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_PROखाता_INDEX_MASK) >>
		CURRENT_PROखाता_INDEX_SHIFT;

	अगर (current_index > 2) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (current_index == 0)
			pl = &ps->low;
		अन्यथा अगर (current_index == 1)
			pl = &ps->medium;
		अन्यथा /* current_index == 2 */
			pl = &ps->high;
		वापस  pl->sclk;
	पूर्ण
पूर्ण

u32 rv770_dpm_get_current_mclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ps *rps = rdev->pm.dpm.current_ps;
	काष्ठा rv7xx_ps *ps = rv770_get_ps(rps);
	काष्ठा rv7xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_PROखाता_INDEX_MASK) >>
		CURRENT_PROखाता_INDEX_SHIFT;

	अगर (current_index > 2) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (current_index == 0)
			pl = &ps->low;
		अन्यथा अगर (current_index == 1)
			pl = &ps->medium;
		अन्यथा /* current_index == 2 */
			pl = &ps->high;
		वापस  pl->mclk;
	पूर्ण
पूर्ण

व्योम rv770_dpm_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		kमुक्त(rdev->pm.dpm.ps[i].ps_priv);
	पूर्ण
	kमुक्त(rdev->pm.dpm.ps);
	kमुक्त(rdev->pm.dpm.priv);
पूर्ण

u32 rv770_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा rv7xx_ps *requested_state = rv770_get_ps(rdev->pm.dpm.requested_ps);

	अगर (low)
		वापस requested_state->low.sclk;
	अन्यथा
		वापस requested_state->high.sclk;
पूर्ण

u32 rv770_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा rv7xx_ps *requested_state = rv770_get_ps(rdev->pm.dpm.requested_ps);

	अगर (low)
		वापस requested_state->low.mclk;
	अन्यथा
		वापस requested_state->high.mclk;
पूर्ण

bool rv770_dpm_vblank_too_लघु(काष्ठा radeon_device *rdev)
अणु
	u32 vblank_समय = r600_dpm_get_vblank_समय(rdev);
	u32 चयन_limit = 200; /* 300 */

	/* RV770 */
	/* mclk चयनing करोesn't seem to work reliably on desktop RV770s */
	अगर ((rdev->family == CHIP_RV770) &&
	    !(rdev->flags & RADEON_IS_MOBILITY))
		चयन_limit = 0xffffffff; /* disable mclk चयनing */

	अगर (vblank_समय < चयन_limit)
		वापस true;
	अन्यथा
		वापस false;

पूर्ण
