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
#समावेश "rv740d.h"
#समावेश "r600_dpm.h"
#समावेश "rv770.h"
#समावेश "rv770_dpm.h"
#समावेश "atom.h"

u32 rv740_get_decoded_reference_भागider(u32 encoded_ref)
अणु
	u32 ref = 0;

	चयन (encoded_ref) अणु
	हाल 0:
		ref = 1;
		अवरोध;
	हाल 16:
		ref = 2;
		अवरोध;
	हाल 17:
		ref = 3;
		अवरोध;
	हाल 18:
		ref = 2;
		अवरोध;
	हाल 19:
		ref = 3;
		अवरोध;
	हाल 20:
		ref = 4;
		अवरोध;
	हाल 21:
		ref = 5;
		अवरोध;
	शेष:
		DRM_ERROR("Invalid encoded Reference Divider\n");
		ref = 0;
		अवरोध;
	पूर्ण

	वापस ref;
पूर्ण

काष्ठा dll_speed_setting अणु
	u16 min;
	u16 max;
	u32 dll_speed;
पूर्ण;

अटल काष्ठा dll_speed_setting dll_speed_table[16] =
अणु
	अणु 270, 320, 0x0f पूर्ण,
	अणु 240, 270, 0x0e पूर्ण,
	अणु 200, 240, 0x0d पूर्ण,
	अणु 180, 200, 0x0c पूर्ण,
	अणु 160, 180, 0x0b पूर्ण,
	अणु 140, 160, 0x0a पूर्ण,
	अणु 120, 140, 0x09 पूर्ण,
	अणु 110, 120, 0x08 पूर्ण,
	अणु  95, 110, 0x07 पूर्ण,
	अणु  85,  95, 0x06 पूर्ण,
	अणु  78,  85, 0x05 पूर्ण,
	अणु  70,  78, 0x04 पूर्ण,
	अणु  65,  70, 0x03 पूर्ण,
	अणु  60,  65, 0x02 पूर्ण,
	अणु  42,  60, 0x01 पूर्ण,
	अणु  00,  42, 0x00 पूर्ण
पूर्ण;

u32 rv740_get_dll_speed(bool is_gddr5, u32 memory_घड़ी)
अणु
	पूर्णांक i;
	u32 factor;
	u16 data_rate;

	अगर (is_gddr5)
		factor = 4;
	अन्यथा
		factor = 2;

	data_rate = (u16)(memory_घड़ी * factor / 1000);

	अगर (data_rate < dll_speed_table[0].max) अणु
		क्रम (i = 0; i < 16; i++) अणु
			अगर (data_rate > dll_speed_table[i].min &&
			    data_rate <= dll_speed_table[i].max)
				वापस dll_speed_table[i].dll_speed;
		पूर्ण
	पूर्ण

	DRM_DEBUG_KMS("Target MCLK greater than largest MCLK in DLL speed table\n");

	वापस 0x0f;
पूर्ण

पूर्णांक rv740_populate_sclk_value(काष्ठा radeon_device *rdev, u32 engine_घड़ी,
			      RV770_SMC_SCLK_VALUE *sclk)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 spll_func_cntl = pi->clk_regs.rv770.cg_spll_func_cntl;
	u32 spll_func_cntl_2 = pi->clk_regs.rv770.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 = pi->clk_regs.rv770.cg_spll_func_cntl_3;
	u32 cg_spll_spपढ़ो_spectrum = pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2 = pi->clk_regs.rv770.cg_spll_spपढ़ो_spectrum_2;
	u64 पंचांगp;
	u32 reference_घड़ी = rdev->घड़ी.spll.reference_freq;
	u32 reference_भागider;
	u32 fbभाग;
	पूर्णांक ret;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     engine_घड़ी, false, &भागiders);
	अगर (ret)
		वापस ret;

	reference_भागider = 1 + भागiders.ref_भाग;

	पंचांगp = (u64) engine_घड़ी * reference_भागider * भागiders.post_भाग * 16384;
	करो_भाग(पंचांगp, reference_घड़ी);
	fbभाग = (u32) पंचांगp;

	spll_func_cntl &= ~(SPLL_PDIV_A_MASK | SPLL_REF_DIV_MASK);
	spll_func_cntl |= SPLL_REF_DIV(भागiders.ref_भाग);
	spll_func_cntl |= SPLL_PDIV_A(भागiders.post_भाग);

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(2);

	spll_func_cntl_3 &= ~SPLL_FB_DIV_MASK;
	spll_func_cntl_3 |= SPLL_FB_DIV(fbभाग);
	spll_func_cntl_3 |= SPLL_DITHEN;

	अगर (pi->sclk_ss) अणु
		काष्ठा radeon_atom_ss ss;
		u32 vco_freq = engine_घड़ी * भागiders.post_भाग;

		अगर (radeon_atombios_get_asic_ss_info(rdev, &ss,
						     ASIC_INTERNAL_ENGINE_SS, vco_freq)) अणु
			u32 clk_s = reference_घड़ी * 5 / (reference_भागider * ss.rate);
			u32 clk_v = 4 * ss.percentage * fbभाग / (clk_s * 10000);

			cg_spll_spपढ़ो_spectrum &= ~CLK_S_MASK;
			cg_spll_spपढ़ो_spectrum |= CLK_S(clk_s);
			cg_spll_spपढ़ो_spectrum |= SSEN;

			cg_spll_spपढ़ो_spectrum_2 &= ~CLK_V_MASK;
			cg_spll_spपढ़ो_spectrum_2 |= CLK_V(clk_v);
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

पूर्णांक rv740_populate_mclk_value(काष्ठा radeon_device *rdev,
			      u32 engine_घड़ी, u32 memory_घड़ी,
			      RV7XX_SMC_MCLK_VALUE *mclk)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 mpll_ad_func_cntl = pi->clk_regs.rv770.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 = pi->clk_regs.rv770.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl = pi->clk_regs.rv770.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 = pi->clk_regs.rv770.mpll_dq_func_cntl_2;
	u32 mclk_pwrmgt_cntl = pi->clk_regs.rv770.mclk_pwrmgt_cntl;
	u32 dll_cntl = pi->clk_regs.rv770.dll_cntl;
	u32 mpll_ss1 = pi->clk_regs.rv770.mpll_ss1;
	u32 mpll_ss2 = pi->clk_regs.rv770.mpll_ss2;
	काष्ठा atom_घड़ी_भागiders भागiders;
	u32 ibias;
	u32 dll_speed;
	पूर्णांक ret;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_MEMORY_PLL_PARAM,
					     memory_घड़ी, false, &भागiders);
	अगर (ret)
		वापस ret;

	ibias = rv770_map_clkf_to_ibias(rdev, भागiders.whole_fb_भाग);

	mpll_ad_func_cntl &= ~(CLKR_MASK |
			       YCLK_POST_DIV_MASK |
			       CLKF_MASK |
			       CLKFRAC_MASK |
			       IBIAS_MASK);
	mpll_ad_func_cntl |= CLKR(भागiders.ref_भाग);
	mpll_ad_func_cntl |= YCLK_POST_DIV(भागiders.post_भाग);
	mpll_ad_func_cntl |= CLKF(भागiders.whole_fb_भाग);
	mpll_ad_func_cntl |= CLKFRAC(भागiders.frac_fb_भाग);
	mpll_ad_func_cntl |= IBIAS(ibias);

	अगर (भागiders.vco_mode)
		mpll_ad_func_cntl_2 |= VCO_MODE;
	अन्यथा
		mpll_ad_func_cntl_2 &= ~VCO_MODE;

	अगर (pi->mem_gddr5) अणु
		mpll_dq_func_cntl &= ~(CLKR_MASK |
				       YCLK_POST_DIV_MASK |
				       CLKF_MASK |
				       CLKFRAC_MASK |
				       IBIAS_MASK);
		mpll_dq_func_cntl |= CLKR(भागiders.ref_भाग);
		mpll_dq_func_cntl |= YCLK_POST_DIV(भागiders.post_भाग);
		mpll_dq_func_cntl |= CLKF(भागiders.whole_fb_भाग);
		mpll_dq_func_cntl |= CLKFRAC(भागiders.frac_fb_भाग);
		mpll_dq_func_cntl |= IBIAS(ibias);

		अगर (भागiders.vco_mode)
			mpll_dq_func_cntl_2 |= VCO_MODE;
		अन्यथा
			mpll_dq_func_cntl_2 &= ~VCO_MODE;
	पूर्ण

	अगर (pi->mclk_ss) अणु
		काष्ठा radeon_atom_ss ss;
		u32 vco_freq = memory_घड़ी * भागiders.post_भाग;

		अगर (radeon_atombios_get_asic_ss_info(rdev, &ss,
						     ASIC_INTERNAL_MEMORY_SS, vco_freq)) अणु
			u32 reference_घड़ी = rdev->घड़ी.mpll.reference_freq;
			u32 decoded_ref = rv740_get_decoded_reference_भागider(भागiders.ref_भाग);
			u32 clk_s = reference_घड़ी * 5 / (decoded_ref * ss.rate);
			u32 clk_v = 0x40000 * ss.percentage *
				(भागiders.whole_fb_भाग + (भागiders.frac_fb_भाग / 8)) / (clk_s * 10000);

			mpll_ss1 &= ~CLKV_MASK;
			mpll_ss1 |= CLKV(clk_v);

			mpll_ss2 &= ~CLKS_MASK;
			mpll_ss2 |= CLKS(clk_s);
		पूर्ण
	पूर्ण

	dll_speed = rv740_get_dll_speed(pi->mem_gddr5,
					memory_घड़ी);

	mclk_pwrmgt_cntl &= ~DLL_SPEED_MASK;
	mclk_pwrmgt_cntl |= DLL_SPEED(dll_speed);

	mclk->mclk770.mclk_value = cpu_to_be32(memory_घड़ी);
	mclk->mclk770.vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	mclk->mclk770.vMPLL_AD_FUNC_CNTL_2 = cpu_to_be32(mpll_ad_func_cntl_2);
	mclk->mclk770.vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	mclk->mclk770.vMPLL_DQ_FUNC_CNTL_2 = cpu_to_be32(mpll_dq_func_cntl_2);
	mclk->mclk770.vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	mclk->mclk770.vDLL_CNTL = cpu_to_be32(dll_cntl);
	mclk->mclk770.vMPLL_SS = cpu_to_be32(mpll_ss1);
	mclk->mclk770.vMPLL_SS2 = cpu_to_be32(mpll_ss2);

	वापस 0;
पूर्ण

व्योम rv740_पढ़ो_घड़ी_रेजिस्टरs(काष्ठा radeon_device *rdev)
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
	pi->clk_regs.rv770.mpll_ss1 = RREG32(MPLL_SS1);
	pi->clk_regs.rv770.mpll_ss2 = RREG32(MPLL_SS2);
पूर्ण

पूर्णांक rv740_populate_smc_acpi_state(काष्ठा radeon_device *rdev,
				  RV770_SMC_STATETABLE *table)
अणु
	काष्ठा rv7xx_घातer_info *pi = rv770_get_pi(rdev);
	u32 mpll_ad_func_cntl = pi->clk_regs.rv770.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 = pi->clk_regs.rv770.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl = pi->clk_regs.rv770.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 = pi->clk_regs.rv770.mpll_dq_func_cntl_2;
	u32 spll_func_cntl = pi->clk_regs.rv770.cg_spll_func_cntl;
	u32 spll_func_cntl_2 = pi->clk_regs.rv770.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 = pi->clk_regs.rv770.cg_spll_func_cntl_3;
	u32 mclk_pwrmgt_cntl = pi->clk_regs.rv770.mclk_pwrmgt_cntl;
	u32 dll_cntl = pi->clk_regs.rv770.dll_cntl;

	table->ACPIState = table->initialState;

	table->ACPIState.flags &= ~PPSMC_SWSTATE_FLAG_DC;

	अगर (pi->acpi_vddc) अणु
		rv770_populate_vddc_value(rdev, pi->acpi_vddc,
					  &table->ACPIState.levels[0].vddc);
		table->ACPIState.levels[0].gen2PCIE =
			pi->pcie_gen2 ?
			pi->acpi_pcie_gen2 : 0;
		table->ACPIState.levels[0].gen2XSP =
			pi->acpi_pcie_gen2;
	पूर्ण अन्यथा अणु
		rv770_populate_vddc_value(rdev, pi->min_vddc_in_table,
					  &table->ACPIState.levels[0].vddc);
		table->ACPIState.levels[0].gen2PCIE = 0;
	पूर्ण

	mpll_ad_func_cntl_2 |= BIAS_GEN_PDNB | RESET_EN;

	mpll_dq_func_cntl_2 |= BYPASS | BIAS_GEN_PDNB | RESET_EN;

	mclk_pwrmgt_cntl |= (MRDCKA0_RESET |
			     MRDCKA1_RESET |
			     MRDCKB0_RESET |
			     MRDCKB1_RESET |
			     MRDCKC0_RESET |
			     MRDCKC1_RESET |
			     MRDCKD0_RESET |
			     MRDCKD1_RESET);

	dll_cntl |= (MRDCKA0_BYPASS |
		     MRDCKA1_BYPASS |
		     MRDCKB0_BYPASS |
		     MRDCKB1_BYPASS |
		     MRDCKC0_BYPASS |
		     MRDCKC1_BYPASS |
		     MRDCKD0_BYPASS |
		     MRDCKD1_BYPASS);

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

	table->ACPIState.levels[1] = table->ACPIState.levels[0];
	table->ACPIState.levels[2] = table->ACPIState.levels[0];

	rv770_populate_mvdd_value(rdev, 0, &table->ACPIState.levels[0].mvdd);

	वापस 0;
पूर्ण

व्योम rv740_enable_mclk_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
				       bool enable)
अणु
	अगर (enable)
		WREG32_P(MPLL_CNTL_MODE, SS_SSEN, ~SS_SSEN);
	अन्यथा
		WREG32_P(MPLL_CNTL_MODE, 0, ~SS_SSEN);
पूर्ण

u8 rv740_get_mclk_frequency_ratio(u32 memory_घड़ी)
अणु
	u8 mc_para_index;

	अगर ((memory_घड़ी < 10000) || (memory_घड़ी > 47500))
		mc_para_index = 0x00;
	अन्यथा
		mc_para_index = (u8)((memory_घड़ी - 10000) / 2500);

	वापस mc_para_index;
पूर्ण
