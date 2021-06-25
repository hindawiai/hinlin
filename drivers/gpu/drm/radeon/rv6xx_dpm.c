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
#समावेश "rv6xxd.h"
#समावेश "r600_dpm.h"
#समावेश "rv6xx_dpm.h"
#समावेश "atom.h"
#समावेश <linux/seq_file.h>

अटल u32 rv6xx_scale_count_given_unit(काष्ठा radeon_device *rdev,
					u32 unscaled_count, u32 unit);

अटल काष्ठा rv6xx_ps *rv6xx_get_ps(काष्ठा radeon_ps *rps)
अणु
	काष्ठा rv6xx_ps *ps = rps->ps_priv;

	वापस ps;
पूर्ण

अटल काष्ठा rv6xx_घातer_info *rv6xx_get_pi(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rdev->pm.dpm.priv;

	वापस pi;
पूर्ण

अटल व्योम rv6xx_क्रमce_pcie_gen1(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	पंचांगp &= LC_GEN2_EN;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	पंचांगp |= LC_INITIATE_LINK_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (!(RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL) & LC_CURRENT_DATA_RATE))
			अवरोध;
		udelay(1);
	पूर्ण

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);
	पंचांगp &= ~LC_INITIATE_LINK_SPEED_CHANGE;
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
पूर्ण

अटल व्योम rv6xx_enable_pcie_gen2_support(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);

	अगर ((पंचांगp & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
	    (पंचांगp & LC_OTHER_SIDE_SUPPORTS_GEN2)) अणु
		पंचांगp |= LC_GEN2_EN;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम rv6xx_enable_bअगर_dynamic_pcie_gen2(काष्ठा radeon_device *rdev,
					       bool enable)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL) & ~LC_HW_VOLTAGE_IF_CONTROL_MASK;
	अगर (enable)
		पंचांगp |= LC_HW_VOLTAGE_IF_CONTROL(1);
	अन्यथा
		पंचांगp |= LC_HW_VOLTAGE_IF_CONTROL(0);
	WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, पंचांगp);
पूर्ण

अटल व्योम rv6xx_enable_l0s(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL) & ~LC_L0S_INACTIVITY_MASK;
	पंचांगp |= LC_L0S_INACTIVITY(3);
	WREG32_PCIE_PORT(PCIE_LC_CNTL, पंचांगp);
पूर्ण

अटल व्योम rv6xx_enable_l1(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_PCIE_PORT(PCIE_LC_CNTL);
	पंचांगp &= ~LC_L1_INACTIVITY_MASK;
	पंचांगp |= LC_L1_INACTIVITY(4);
	पंचांगp &= ~LC_PMI_TO_L1_DIS;
	पंचांगp &= ~LC_ASPM_TO_L1_DIS;
	WREG32_PCIE_PORT(PCIE_LC_CNTL, पंचांगp);
पूर्ण

अटल व्योम rv6xx_enable_pll_sleep_in_l1(काष्ठा radeon_device *rdev)
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

अटल पूर्णांक rv6xx_convert_घड़ी_प्रकारo_stepping(काष्ठा radeon_device *rdev,
					   u32 घड़ी, काष्ठा rv6xx_sclk_stepping *step)
अणु
	पूर्णांक ret;
	काष्ठा atom_घड़ी_भागiders भागiders;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     घड़ी, false, &भागiders);
	अगर (ret)
		वापस ret;

	अगर (भागiders.enable_post_भाग)
		step->post_भागider = 2 + (भागiders.post_भाग & 0xF) + (भागiders.post_भाग >> 4);
	अन्यथा
		step->post_भागider = 1;

	step->vco_frequency = घड़ी * step->post_भागider;

	वापस 0;
पूर्ण

अटल व्योम rv6xx_output_stepping(काष्ठा radeon_device *rdev,
				  u32 step_index, काष्ठा rv6xx_sclk_stepping *step)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	u32 ref_clk = rdev->घड़ी.spll.reference_freq;
	u32 fb_भागider;
	u32 spll_step_count = rv6xx_scale_count_given_unit(rdev,
							   R600_SPLLSTEPTIME_DFLT *
							   pi->spll_ref_भाग,
							   R600_SPLLSTEPUNIT_DFLT);

	r600_engine_घड़ी_entry_enable(rdev, step_index, true);
	r600_engine_घड़ी_entry_enable_pulse_skipping(rdev, step_index, false);

	अगर (step->post_भागider == 1)
		r600_engine_घड़ी_entry_enable_post_भागider(rdev, step_index, false);
	अन्यथा अणु
		u32 lo_len = (step->post_भागider - 2) / 2;
		u32 hi_len = step->post_भागider - 2 - lo_len;

		r600_engine_घड़ी_entry_enable_post_भागider(rdev, step_index, true);
		r600_engine_घड़ी_entry_set_post_भागider(rdev, step_index, (hi_len << 4) | lo_len);
	पूर्ण

	fb_भागider = ((step->vco_frequency * pi->spll_ref_भाग) / ref_clk) >>
		pi->fb_भाग_scale;

	r600_engine_घड़ी_entry_set_reference_भागider(rdev, step_index,
						      pi->spll_ref_भाग - 1);
	r600_engine_घड़ी_entry_set_feedback_भागider(rdev, step_index, fb_भागider);
	r600_engine_घड़ी_entry_set_step_समय(rdev, step_index, spll_step_count);

पूर्ण

अटल काष्ठा rv6xx_sclk_stepping rv6xx_next_vco_step(काष्ठा radeon_device *rdev,
						      काष्ठा rv6xx_sclk_stepping *cur,
						      bool increasing_vco, u32 step_size)
अणु
	काष्ठा rv6xx_sclk_stepping next;

	next.post_भागider = cur->post_भागider;

	अगर (increasing_vco)
		next.vco_frequency = (cur->vco_frequency * (100 + step_size)) / 100;
	अन्यथा
		next.vco_frequency = (cur->vco_frequency * 100 + 99 + step_size) / (100 + step_size);

	वापस next;
पूर्ण

अटल bool rv6xx_can_step_post_भाग(काष्ठा radeon_device *rdev,
				    काष्ठा rv6xx_sclk_stepping *cur,
				    काष्ठा rv6xx_sclk_stepping *target)
अणु
	वापस (cur->post_भागider > target->post_भागider) &&
		((cur->vco_frequency * target->post_भागider) <=
		 (target->vco_frequency * (cur->post_भागider - 1)));
पूर्ण

अटल काष्ठा rv6xx_sclk_stepping rv6xx_next_post_भाग_step(काष्ठा radeon_device *rdev,
							   काष्ठा rv6xx_sclk_stepping *cur,
							   काष्ठा rv6xx_sclk_stepping *target)
अणु
	काष्ठा rv6xx_sclk_stepping next = *cur;

	जबतक (rv6xx_can_step_post_भाग(rdev, &next, target))
		next.post_भागider--;

	वापस next;
पूर्ण

अटल bool rv6xx_reached_stepping_target(काष्ठा radeon_device *rdev,
					  काष्ठा rv6xx_sclk_stepping *cur,
					  काष्ठा rv6xx_sclk_stepping *target,
					  bool increasing_vco)
अणु
	वापस (increasing_vco && (cur->vco_frequency >= target->vco_frequency)) ||
		(!increasing_vco && (cur->vco_frequency <= target->vco_frequency));
पूर्ण

अटल व्योम rv6xx_generate_steps(काष्ठा radeon_device *rdev,
				 u32 low, u32 high,
				 u32 start_index, u8 *end_index)
अणु
	काष्ठा rv6xx_sclk_stepping cur;
	काष्ठा rv6xx_sclk_stepping target;
	bool increasing_vco;
	u32 step_index = start_index;

	rv6xx_convert_घड़ी_प्रकारo_stepping(rdev, low, &cur);
	rv6xx_convert_घड़ी_प्रकारo_stepping(rdev, high, &target);

	rv6xx_output_stepping(rdev, step_index++, &cur);

	increasing_vco = (target.vco_frequency >= cur.vco_frequency);

	अगर (target.post_भागider > cur.post_भागider)
		cur.post_भागider = target.post_भागider;

	जबतक (1) अणु
		काष्ठा rv6xx_sclk_stepping next;

		अगर (rv6xx_can_step_post_भाग(rdev, &cur, &target))
			next = rv6xx_next_post_भाग_step(rdev, &cur, &target);
		अन्यथा
			next = rv6xx_next_vco_step(rdev, &cur, increasing_vco, R600_VCOSTEPPCT_DFLT);

		अगर (rv6xx_reached_stepping_target(rdev, &next, &target, increasing_vco)) अणु
			काष्ठा rv6xx_sclk_stepping tiny =
				rv6xx_next_vco_step(rdev, &target, !increasing_vco, R600_ENDINGVCOSTEPPCT_DFLT);
			tiny.post_भागider = next.post_भागider;

			अगर (!rv6xx_reached_stepping_target(rdev, &tiny, &cur, !increasing_vco))
				rv6xx_output_stepping(rdev, step_index++, &tiny);

			अगर ((next.post_भागider != target.post_भागider) &&
			    (next.vco_frequency != target.vco_frequency)) अणु
				काष्ठा rv6xx_sclk_stepping final_vco;

				final_vco.vco_frequency = target.vco_frequency;
				final_vco.post_भागider = next.post_भागider;

				rv6xx_output_stepping(rdev, step_index++, &final_vco);
			पूर्ण

			rv6xx_output_stepping(rdev, step_index++, &target);
			अवरोध;
		पूर्ण अन्यथा
			rv6xx_output_stepping(rdev, step_index++, &next);

		cur = next;
	पूर्ण

	*end_index = (u8)step_index - 1;

पूर्ण

अटल व्योम rv6xx_generate_single_step(काष्ठा radeon_device *rdev,
				       u32 घड़ी, u32 index)
अणु
	काष्ठा rv6xx_sclk_stepping step;

	rv6xx_convert_घड़ी_प्रकारo_stepping(rdev, घड़ी, &step);
	rv6xx_output_stepping(rdev, index, &step);
पूर्ण

अटल व्योम rv6xx_invalidate_पूर्णांकermediate_steps_range(काष्ठा radeon_device *rdev,
						      u32 start_index, u32 end_index)
अणु
	u32 step_index;

	क्रम (step_index = start_index + 1; step_index < end_index; step_index++)
		r600_engine_घड़ी_entry_enable(rdev, step_index, false);
पूर्ण

अटल व्योम rv6xx_set_engine_spपढ़ो_spectrum_clk_s(काष्ठा radeon_device *rdev,
						   u32 index, u32 clk_s)
अणु
	WREG32_P(CG_SPLL_SPREAD_SPECTRUM_LOW + (index * 4),
		 CLKS(clk_s), ~CLKS_MASK);
पूर्ण

अटल व्योम rv6xx_set_engine_spपढ़ो_spectrum_clk_v(काष्ठा radeon_device *rdev,
						   u32 index, u32 clk_v)
अणु
	WREG32_P(CG_SPLL_SPREAD_SPECTRUM_LOW + (index * 4),
		 CLKV(clk_v), ~CLKV_MASK);
पूर्ण

अटल व्योम rv6xx_enable_engine_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
						u32 index, bool enable)
अणु
	अगर (enable)
		WREG32_P(CG_SPLL_SPREAD_SPECTRUM_LOW + (index * 4),
			 SSEN, ~SSEN);
	अन्यथा
		WREG32_P(CG_SPLL_SPREAD_SPECTRUM_LOW + (index * 4),
			 0, ~SSEN);
पूर्ण

अटल व्योम rv6xx_set_memory_spपढ़ो_spectrum_clk_s(काष्ठा radeon_device *rdev,
						   u32 clk_s)
अणु
	WREG32_P(CG_MPLL_SPREAD_SPECTRUM, CLKS(clk_s), ~CLKS_MASK);
पूर्ण

अटल व्योम rv6xx_set_memory_spपढ़ो_spectrum_clk_v(काष्ठा radeon_device *rdev,
						   u32 clk_v)
अणु
	WREG32_P(CG_MPLL_SPREAD_SPECTRUM, CLKV(clk_v), ~CLKV_MASK);
पूर्ण

अटल व्योम rv6xx_enable_memory_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
						bool enable)
अणु
	अगर (enable)
		WREG32_P(CG_MPLL_SPREAD_SPECTRUM, SSEN, ~SSEN);
	अन्यथा
		WREG32_P(CG_MPLL_SPREAD_SPECTRUM, 0, ~SSEN);
पूर्ण

अटल व्योम rv6xx_enable_dynamic_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
						 bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, DYN_SPREAD_SPECTRUM_EN, ~DYN_SPREAD_SPECTRUM_EN);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~DYN_SPREAD_SPECTRUM_EN);
पूर्ण

अटल व्योम rv6xx_memory_घड़ी_entry_enable_post_भागider(काष्ठा radeon_device *rdev,
							 u32 index, bool enable)
अणु
	अगर (enable)
		WREG32_P(MPLL_FREQ_LEVEL_0 + (index * 4),
			 LEVEL0_MPLL_DIV_EN, ~LEVEL0_MPLL_DIV_EN);
	अन्यथा
		WREG32_P(MPLL_FREQ_LEVEL_0 + (index * 4), 0, ~LEVEL0_MPLL_DIV_EN);
पूर्ण

अटल व्योम rv6xx_memory_घड़ी_entry_set_post_भागider(काष्ठा radeon_device *rdev,
						      u32 index, u32 भागider)
अणु
	WREG32_P(MPLL_FREQ_LEVEL_0 + (index * 4),
		 LEVEL0_MPLL_POST_DIV(भागider), ~LEVEL0_MPLL_POST_DIV_MASK);
पूर्ण

अटल व्योम rv6xx_memory_घड़ी_entry_set_feedback_भागider(काष्ठा radeon_device *rdev,
							  u32 index, u32 भागider)
अणु
	WREG32_P(MPLL_FREQ_LEVEL_0 + (index * 4), LEVEL0_MPLL_FB_DIV(भागider),
		 ~LEVEL0_MPLL_FB_DIV_MASK);
पूर्ण

अटल व्योम rv6xx_memory_घड़ी_entry_set_reference_भागider(काष्ठा radeon_device *rdev,
							   u32 index, u32 भागider)
अणु
	WREG32_P(MPLL_FREQ_LEVEL_0 + (index * 4),
		 LEVEL0_MPLL_REF_DIV(भागider), ~LEVEL0_MPLL_REF_DIV_MASK);
पूर्ण

अटल व्योम rv6xx_vid_response_set_brt(काष्ठा radeon_device *rdev, u32 rt)
अणु
	WREG32_P(VID_RT, BRT(rt), ~BRT_MASK);
पूर्ण

अटल व्योम rv6xx_enable_engine_feedback_and_reference_sync(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(SPLL_CNTL_MODE, SPLL_DIV_SYNC, ~SPLL_DIV_SYNC);
पूर्ण

अटल u32 rv6xx_घड़ीs_per_unit(u32 unit)
अणु
	u32 पंचांगp = 1 << (2 * unit);

	वापस पंचांगp;
पूर्ण

अटल u32 rv6xx_scale_count_given_unit(काष्ठा radeon_device *rdev,
					u32 unscaled_count, u32 unit)
अणु
	u32 count_per_unit = rv6xx_घड़ीs_per_unit(unit);

	वापस (unscaled_count + count_per_unit - 1) / count_per_unit;
पूर्ण

अटल u32 rv6xx_compute_count_क्रम_delay(काष्ठा radeon_device *rdev,
					 u32 delay_us, u32 unit)
अणु
	u32 ref_clk = rdev->घड़ी.spll.reference_freq;

	वापस rv6xx_scale_count_given_unit(rdev, delay_us * (ref_clk / 100), unit);
पूर्ण

अटल व्योम rv6xx_calculate_engine_speed_stepping_parameters(काष्ठा radeon_device *rdev,
							     काष्ठा rv6xx_ps *state)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	pi->hw.sclks[R600_POWER_LEVEL_LOW] =
		state->low.sclk;
	pi->hw.sclks[R600_POWER_LEVEL_MEDIUM] =
		state->medium.sclk;
	pi->hw.sclks[R600_POWER_LEVEL_HIGH] =
		state->high.sclk;

	pi->hw.low_sclk_index = R600_POWER_LEVEL_LOW;
	pi->hw.medium_sclk_index = R600_POWER_LEVEL_MEDIUM;
	pi->hw.high_sclk_index = R600_POWER_LEVEL_HIGH;
पूर्ण

अटल व्योम rv6xx_calculate_memory_घड़ी_stepping_parameters(काष्ठा radeon_device *rdev,
							     काष्ठा rv6xx_ps *state)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	pi->hw.mclks[R600_POWER_LEVEL_CTXSW] =
		state->high.mclk;
	pi->hw.mclks[R600_POWER_LEVEL_HIGH] =
		state->high.mclk;
	pi->hw.mclks[R600_POWER_LEVEL_MEDIUM] =
		state->medium.mclk;
	pi->hw.mclks[R600_POWER_LEVEL_LOW] =
		state->low.mclk;

	pi->hw.high_mclk_index = R600_POWER_LEVEL_HIGH;

	अगर (state->high.mclk == state->medium.mclk)
		pi->hw.medium_mclk_index =
			pi->hw.high_mclk_index;
	अन्यथा
		pi->hw.medium_mclk_index = R600_POWER_LEVEL_MEDIUM;


	अगर (state->medium.mclk == state->low.mclk)
		pi->hw.low_mclk_index =
			pi->hw.medium_mclk_index;
	अन्यथा
		pi->hw.low_mclk_index = R600_POWER_LEVEL_LOW;
पूर्ण

अटल व्योम rv6xx_calculate_voltage_stepping_parameters(काष्ठा radeon_device *rdev,
							काष्ठा rv6xx_ps *state)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	pi->hw.vddc[R600_POWER_LEVEL_CTXSW] = state->high.vddc;
	pi->hw.vddc[R600_POWER_LEVEL_HIGH] = state->high.vddc;
	pi->hw.vddc[R600_POWER_LEVEL_MEDIUM] = state->medium.vddc;
	pi->hw.vddc[R600_POWER_LEVEL_LOW] = state->low.vddc;

	pi->hw.backbias[R600_POWER_LEVEL_CTXSW] =
		(state->high.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ? true : false;
	pi->hw.backbias[R600_POWER_LEVEL_HIGH] =
		(state->high.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ? true : false;
	pi->hw.backbias[R600_POWER_LEVEL_MEDIUM] =
		(state->medium.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ? true : false;
	pi->hw.backbias[R600_POWER_LEVEL_LOW] =
		(state->low.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ? true : false;

	pi->hw.pcie_gen2[R600_POWER_LEVEL_HIGH] =
		(state->high.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? true : false;
	pi->hw.pcie_gen2[R600_POWER_LEVEL_MEDIUM] =
		(state->medium.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? true : false;
	pi->hw.pcie_gen2[R600_POWER_LEVEL_LOW] =
		(state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) ? true : false;

	pi->hw.high_vddc_index = R600_POWER_LEVEL_HIGH;

	अगर ((state->high.vddc == state->medium.vddc) &&
	    ((state->high.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ==
	     (state->medium.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE)))
		pi->hw.medium_vddc_index =
			pi->hw.high_vddc_index;
	अन्यथा
		pi->hw.medium_vddc_index = R600_POWER_LEVEL_MEDIUM;

	अगर ((state->medium.vddc == state->low.vddc) &&
	    ((state->medium.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) ==
	     (state->low.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE)))
		pi->hw.low_vddc_index =
			pi->hw.medium_vddc_index;
	अन्यथा
		pi->hw.medium_vddc_index = R600_POWER_LEVEL_LOW;
पूर्ण

अटल अंतरभूत u32 rv6xx_calculate_vco_frequency(u32 ref_घड़ी,
						काष्ठा atom_घड़ी_भागiders *भागiders,
						u32 fb_भागider_scale)
अणु
	वापस ref_घड़ी * ((भागiders->fb_भाग & ~1) << fb_भागider_scale) /
		(भागiders->ref_भाग + 1);
पूर्ण

अटल अंतरभूत u32 rv6xx_calculate_spपढ़ो_spectrum_clk_v(u32 vco_freq, u32 ref_freq,
							u32 ss_rate, u32 ss_percent,
							u32 fb_भागider_scale)
अणु
	u32 fb_भागider = vco_freq / ref_freq;

	वापस (ss_percent * ss_rate * 4 * (fb_भागider * fb_भागider) /
		(5375 * ((vco_freq * 10) / (4096 >> fb_भागider_scale))));
पूर्ण

अटल अंतरभूत u32 rv6xx_calculate_spपढ़ो_spectrum_clk_s(u32 ss_rate, u32 ref_freq)
अणु
	वापस (((ref_freq * 10) / (ss_rate * 2)) - 1) / 4;
पूर्ण

अटल व्योम rv6xx_program_engine_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
						 u32 घड़ी, क्रमागत r600_घातer_level level)
अणु
	u32 ref_clk = rdev->घड़ी.spll.reference_freq;
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	काष्ठा atom_घड़ी_भागiders भागiders;
	काष्ठा radeon_atom_ss ss;
	u32 vco_freq, clk_v, clk_s;

	rv6xx_enable_engine_spपढ़ो_spectrum(rdev, level, false);

	अगर (घड़ी && pi->sclk_ss) अणु
		अगर (radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM, घड़ी, false, &भागiders) == 0) अणु
			vco_freq = rv6xx_calculate_vco_frequency(ref_clk, &भागiders,
								 pi->fb_भाग_scale);

			अगर (radeon_atombios_get_asic_ss_info(rdev, &ss,
							     ASIC_INTERNAL_ENGINE_SS, vco_freq)) अणु
				clk_v = rv6xx_calculate_spपढ़ो_spectrum_clk_v(vco_freq,
									      (ref_clk / (भागiders.ref_भाग + 1)),
									      ss.rate,
									      ss.percentage,
									      pi->fb_भाग_scale);

				clk_s = rv6xx_calculate_spपढ़ो_spectrum_clk_s(ss.rate,
									      (ref_clk / (भागiders.ref_भाग + 1)));

				rv6xx_set_engine_spपढ़ो_spectrum_clk_v(rdev, level, clk_v);
				rv6xx_set_engine_spपढ़ो_spectrum_clk_s(rdev, level, clk_s);
				rv6xx_enable_engine_spपढ़ो_spectrum(rdev, level, true);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rv6xx_program_sclk_spपढ़ो_spectrum_parameters_except_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	rv6xx_program_engine_spपढ़ो_spectrum(rdev,
					     pi->hw.sclks[R600_POWER_LEVEL_HIGH],
					     R600_POWER_LEVEL_HIGH);

	rv6xx_program_engine_spपढ़ो_spectrum(rdev,
					     pi->hw.sclks[R600_POWER_LEVEL_MEDIUM],
					     R600_POWER_LEVEL_MEDIUM);

पूर्ण

अटल पूर्णांक rv6xx_program_mclk_stepping_entry(काष्ठा radeon_device *rdev,
					     u32 entry, u32 घड़ी)
अणु
	काष्ठा atom_घड़ी_भागiders भागiders;

	अगर (radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_MEMORY_PLL_PARAM, घड़ी, false, &भागiders))
	    वापस -EINVAL;


	rv6xx_memory_घड़ी_entry_set_reference_भागider(rdev, entry, भागiders.ref_भाग);
	rv6xx_memory_घड़ी_entry_set_feedback_भागider(rdev, entry, भागiders.fb_भाग);
	rv6xx_memory_घड़ी_entry_set_post_भागider(rdev, entry, भागiders.post_भाग);

	अगर (भागiders.enable_post_भाग)
		rv6xx_memory_घड़ी_entry_enable_post_भागider(rdev, entry, true);
	अन्यथा
		rv6xx_memory_घड़ी_entry_enable_post_भागider(rdev, entry, false);

	वापस 0;
पूर्ण

अटल व्योम rv6xx_program_mclk_stepping_parameters_except_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	पूर्णांक i;

	क्रम (i = 1; i < R600_PM_NUMBER_OF_MCLKS; i++) अणु
		अगर (pi->hw.mclks[i])
			rv6xx_program_mclk_stepping_entry(rdev, i,
							  pi->hw.mclks[i]);
	पूर्ण
पूर्ण

अटल व्योम rv6xx_find_memory_घड़ी_with_highest_vco(काष्ठा radeon_device *rdev,
						     u32 requested_memory_घड़ी,
						     u32 ref_clk,
						     काष्ठा atom_घड़ी_भागiders *भागiders,
						     u32 *vco_freq)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	काष्ठा atom_घड़ी_भागiders req_भागiders;
	u32 vco_freq_temp;

	अगर (radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_MEMORY_PLL_PARAM,
					   requested_memory_घड़ी, false, &req_भागiders) == 0) अणु
		vco_freq_temp = rv6xx_calculate_vco_frequency(ref_clk, &req_भागiders,
							      pi->fb_भाग_scale);

		अगर (vco_freq_temp > *vco_freq) अणु
			*भागiders = req_भागiders;
			*vco_freq = vco_freq_temp;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rv6xx_program_mclk_spपढ़ो_spectrum_parameters(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	u32 ref_clk = rdev->घड़ी.mpll.reference_freq;
	काष्ठा atom_घड़ी_भागiders भागiders;
	काष्ठा radeon_atom_ss ss;
	u32 vco_freq = 0, clk_v, clk_s;

	rv6xx_enable_memory_spपढ़ो_spectrum(rdev, false);

	अगर (pi->mclk_ss) अणु
		rv6xx_find_memory_घड़ी_with_highest_vco(rdev,
							 pi->hw.mclks[pi->hw.high_mclk_index],
							 ref_clk,
							 &भागiders,
							 &vco_freq);

		rv6xx_find_memory_घड़ी_with_highest_vco(rdev,
							 pi->hw.mclks[pi->hw.medium_mclk_index],
							 ref_clk,
							 &भागiders,
							 &vco_freq);

		rv6xx_find_memory_घड़ी_with_highest_vco(rdev,
							 pi->hw.mclks[pi->hw.low_mclk_index],
							 ref_clk,
							 &भागiders,
							 &vco_freq);

		अगर (vco_freq) अणु
			अगर (radeon_atombios_get_asic_ss_info(rdev, &ss,
							     ASIC_INTERNAL_MEMORY_SS, vco_freq)) अणु
				clk_v = rv6xx_calculate_spपढ़ो_spectrum_clk_v(vco_freq,
									     (ref_clk / (भागiders.ref_भाग + 1)),
									     ss.rate,
									     ss.percentage,
									     pi->fb_भाग_scale);

				clk_s = rv6xx_calculate_spपढ़ो_spectrum_clk_s(ss.rate,
									     (ref_clk / (भागiders.ref_भाग + 1)));

				rv6xx_set_memory_spपढ़ो_spectrum_clk_v(rdev, clk_v);
				rv6xx_set_memory_spपढ़ो_spectrum_clk_s(rdev, clk_s);
				rv6xx_enable_memory_spपढ़ो_spectrum(rdev, true);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rv6xx_program_voltage_stepping_entry(काष्ठा radeon_device *rdev,
						u32 entry, u16 voltage)
अणु
	u32 mask, set_pins;
	पूर्णांक ret;

	ret = radeon_atom_get_voltage_gpio_settings(rdev, voltage,
						    SET_VOLTAGE_TYPE_ASIC_VDDC,
						    &set_pins, &mask);
	अगर (ret)
		वापस ret;

	r600_voltage_control_program_voltages(rdev, entry, set_pins);

	वापस 0;
पूर्ण

अटल व्योम rv6xx_program_voltage_stepping_parameters_except_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	पूर्णांक i;

	क्रम (i = 1; i < R600_PM_NUMBER_OF_VOLTAGE_LEVELS; i++)
		rv6xx_program_voltage_stepping_entry(rdev, i,
						     pi->hw.vddc[i]);

पूर्ण

अटल व्योम rv6xx_program_backbias_stepping_parameters_except_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	अगर (pi->hw.backbias[1])
		WREG32_P(VID_UPPER_GPIO_CNTL, MEDIUM_BACKBIAS_VALUE, ~MEDIUM_BACKBIAS_VALUE);
	अन्यथा
		WREG32_P(VID_UPPER_GPIO_CNTL, 0, ~MEDIUM_BACKBIAS_VALUE);

	अगर (pi->hw.backbias[2])
		WREG32_P(VID_UPPER_GPIO_CNTL, HIGH_BACKBIAS_VALUE, ~HIGH_BACKBIAS_VALUE);
	अन्यथा
		WREG32_P(VID_UPPER_GPIO_CNTL, 0, ~HIGH_BACKBIAS_VALUE);
पूर्ण

अटल व्योम rv6xx_program_sclk_spपढ़ो_spectrum_parameters_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	rv6xx_program_engine_spपढ़ो_spectrum(rdev,
					     pi->hw.sclks[R600_POWER_LEVEL_LOW],
					     R600_POWER_LEVEL_LOW);
पूर्ण

अटल व्योम rv6xx_program_mclk_stepping_parameters_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	अगर (pi->hw.mclks[0])
		rv6xx_program_mclk_stepping_entry(rdev, 0,
						  pi->hw.mclks[0]);
पूर्ण

अटल व्योम rv6xx_program_voltage_stepping_parameters_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	rv6xx_program_voltage_stepping_entry(rdev, 0,
					     pi->hw.vddc[0]);

पूर्ण

अटल व्योम rv6xx_program_backbias_stepping_parameters_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	अगर (pi->hw.backbias[0])
		WREG32_P(VID_UPPER_GPIO_CNTL, LOW_BACKBIAS_VALUE, ~LOW_BACKBIAS_VALUE);
	अन्यथा
		WREG32_P(VID_UPPER_GPIO_CNTL, 0, ~LOW_BACKBIAS_VALUE);
पूर्ण

अटल u32 calculate_memory_refresh_rate(काष्ठा radeon_device *rdev,
					 u32 engine_घड़ी)
अणु
	u32 dram_rows, dram_refresh_rate;
	u32 पंचांगp;

	पंचांगp = (RREG32(RAMCFG) & NOOFROWS_MASK) >> NOOFROWS_SHIFT;
	dram_rows = 1 << (पंचांगp + 10);
	dram_refresh_rate = 1 << ((RREG32(MC_SEQ_RESERVE_M) & 0x3) + 3);

	वापस ((engine_घड़ी * 10) * dram_refresh_rate / dram_rows - 32) / 64;
पूर्ण

अटल व्योम rv6xx_program_memory_timing_parameters(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	u32 sqm_ratio;
	u32 arb_refresh_rate;
	u32 high_घड़ी;

	अगर (pi->hw.sclks[R600_POWER_LEVEL_HIGH] <
	    (pi->hw.sclks[R600_POWER_LEVEL_LOW] * 0xFF / 0x40))
		high_घड़ी = pi->hw.sclks[R600_POWER_LEVEL_HIGH];
	अन्यथा
		high_घड़ी =
			pi->hw.sclks[R600_POWER_LEVEL_LOW] * 0xFF / 0x40;

	radeon_atom_set_engine_dram_timings(rdev, high_घड़ी, 0);

	sqm_ratio = (STATE0(64 * high_घड़ी / pi->hw.sclks[R600_POWER_LEVEL_LOW]) |
		     STATE1(64 * high_घड़ी / pi->hw.sclks[R600_POWER_LEVEL_MEDIUM]) |
		     STATE2(64 * high_घड़ी / pi->hw.sclks[R600_POWER_LEVEL_HIGH]) |
		     STATE3(64 * high_घड़ी / pi->hw.sclks[R600_POWER_LEVEL_HIGH]));
	WREG32(SQM_RATIO, sqm_ratio);

	arb_refresh_rate =
		(POWERMODE0(calculate_memory_refresh_rate(rdev,
							  pi->hw.sclks[R600_POWER_LEVEL_LOW])) |
		 POWERMODE1(calculate_memory_refresh_rate(rdev,
							  pi->hw.sclks[R600_POWER_LEVEL_MEDIUM])) |
		 POWERMODE2(calculate_memory_refresh_rate(rdev,
							  pi->hw.sclks[R600_POWER_LEVEL_HIGH])) |
		 POWERMODE3(calculate_memory_refresh_rate(rdev,
							  pi->hw.sclks[R600_POWER_LEVEL_HIGH])));
	WREG32(ARB_RFSH_RATE, arb_refresh_rate);
पूर्ण

अटल व्योम rv6xx_program_mpll_timing_parameters(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	r600_set_mpll_lock_समय(rdev, R600_MPLLLOCKTIME_DFLT *
				pi->mpll_ref_भाग);
	r600_set_mpll_reset_समय(rdev, R600_MPLLRESETTIME_DFLT);
पूर्ण

अटल व्योम rv6xx_program_bsp(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	u32 ref_clk = rdev->घड़ी.spll.reference_freq;

	r600_calculate_u_and_p(R600_ASI_DFLT,
			       ref_clk, 16,
			       &pi->bsp,
			       &pi->bsu);

	r600_set_bsp(rdev, pi->bsu, pi->bsp);
पूर्ण

अटल व्योम rv6xx_program_at(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	r600_set_at(rdev,
		    (pi->hw.rp[0] * pi->bsp) / 200,
		    (pi->hw.rp[1] * pi->bsp) / 200,
		    (pi->hw.lp[2] * pi->bsp) / 200,
		    (pi->hw.lp[1] * pi->bsp) / 200);
पूर्ण

अटल व्योम rv6xx_program_git(काष्ठा radeon_device *rdev)
अणु
	r600_set_git(rdev, R600_GICST_DFLT);
पूर्ण

अटल व्योम rv6xx_program_tp(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < R600_PM_NUMBER_OF_TC; i++)
		r600_set_tc(rdev, i, r600_utc[i], r600_dtc[i]);

	r600_select_td(rdev, R600_TD_DFLT);
पूर्ण

अटल व्योम rv6xx_program_vc(काष्ठा radeon_device *rdev)
अणु
	r600_set_vrc(rdev, R600_VRC_DFLT);
पूर्ण

अटल व्योम rv6xx_clear_vc(काष्ठा radeon_device *rdev)
अणु
	r600_set_vrc(rdev, 0);
पूर्ण

अटल व्योम rv6xx_program_tpp(काष्ठा radeon_device *rdev)
अणु
	r600_set_tpu(rdev, R600_TPU_DFLT);
	r600_set_tpc(rdev, R600_TPC_DFLT);
पूर्ण

अटल व्योम rv6xx_program_sstp(काष्ठा radeon_device *rdev)
अणु
	r600_set_sstu(rdev, R600_SSTU_DFLT);
	r600_set_sst(rdev, R600_SST_DFLT);
पूर्ण

अटल व्योम rv6xx_program_fcp(काष्ठा radeon_device *rdev)
अणु
	r600_set_fctu(rdev, R600_FCTU_DFLT);
	r600_set_fct(rdev, R600_FCT_DFLT);
पूर्ण

अटल व्योम rv6xx_program_vddc3d_parameters(काष्ठा radeon_device *rdev)
अणु
	r600_set_vddc3d_oorsu(rdev, R600_VDDC3DOORSU_DFLT);
	r600_set_vddc3d_oorphc(rdev, R600_VDDC3DOORPHC_DFLT);
	r600_set_vddc3d_oorsdc(rdev, R600_VDDC3DOORSDC_DFLT);
	r600_set_ctxcgtt3d_rphc(rdev, R600_CTXCGTT3DRPHC_DFLT);
	r600_set_ctxcgtt3d_rsdc(rdev, R600_CTXCGTT3DRSDC_DFLT);
पूर्ण

अटल व्योम rv6xx_program_voltage_timing_parameters(काष्ठा radeon_device *rdev)
अणु
	u32 rt;

	r600_vid_rt_set_vru(rdev, R600_VRU_DFLT);

	r600_vid_rt_set_vrt(rdev,
			    rv6xx_compute_count_क्रम_delay(rdev,
							  rdev->pm.dpm.voltage_response_समय,
							  R600_VRU_DFLT));

	rt = rv6xx_compute_count_क्रम_delay(rdev,
					   rdev->pm.dpm.backbias_response_समय,
					   R600_VRU_DFLT);

	rv6xx_vid_response_set_brt(rdev, (rt + 0x1F) >> 5);
पूर्ण

अटल व्योम rv6xx_program_engine_speed_parameters(काष्ठा radeon_device *rdev)
अणु
	r600_vid_rt_set_ssu(rdev, R600_SPLLSTEPUNIT_DFLT);
	rv6xx_enable_engine_feedback_and_reference_sync(rdev);
पूर्ण

अटल u64 rv6xx_get_master_voltage_mask(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	u64 master_mask = 0;
	पूर्णांक i;

	क्रम (i = 0; i < R600_PM_NUMBER_OF_VOLTAGE_LEVELS; i++) अणु
		u32 पंचांगp_mask, पंचांगp_set_pins;
		पूर्णांक ret;

		ret = radeon_atom_get_voltage_gpio_settings(rdev,
							    pi->hw.vddc[i],
							    SET_VOLTAGE_TYPE_ASIC_VDDC,
							    &पंचांगp_set_pins, &पंचांगp_mask);

		अगर (ret == 0)
			master_mask |= पंचांगp_mask;
	पूर्ण

	वापस master_mask;
पूर्ण

अटल व्योम rv6xx_program_voltage_gpio_pins(काष्ठा radeon_device *rdev)
अणु
	r600_voltage_control_enable_pins(rdev,
					 rv6xx_get_master_voltage_mask(rdev));
पूर्ण

अटल व्योम rv6xx_enable_अटल_voltage_control(काष्ठा radeon_device *rdev,
						काष्ठा radeon_ps *new_ps,
						bool enable)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);

	अगर (enable)
		radeon_atom_set_voltage(rdev,
					new_state->low.vddc,
					SET_VOLTAGE_TYPE_ASIC_VDDC);
	अन्यथा
		r600_voltage_control_deactivate_अटल_control(rdev,
							       rv6xx_get_master_voltage_mask(rdev));
पूर्ण

अटल व्योम rv6xx_enable_display_gap(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable) अणु
		u32 पंचांगp = (DISP1_GAP(R600_PM_DISPLAY_GAP_VBLANK_OR_WM) |
			   DISP2_GAP(R600_PM_DISPLAY_GAP_VBLANK_OR_WM) |
			   DISP1_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE) |
			   DISP2_GAP_MCHG(R600_PM_DISPLAY_GAP_IGNORE) |
			   VBI_TIMER_COUNT(0x3FFF) |
			   VBI_TIMER_UNIT(7));
		WREG32(CG_DISPLAY_GAP_CNTL, पंचांगp);

		WREG32_P(MCLK_PWRMGT_CNTL, USE_DISPLAY_GAP, ~USE_DISPLAY_GAP);
	पूर्ण अन्यथा
		WREG32_P(MCLK_PWRMGT_CNTL, 0, ~USE_DISPLAY_GAP);
पूर्ण

अटल व्योम rv6xx_program_घातer_level_enter_state(काष्ठा radeon_device *rdev)
अणु
	r600_घातer_level_set_enter_index(rdev, R600_POWER_LEVEL_MEDIUM);
पूर्ण

अटल व्योम rv6xx_calculate_t(u32 l_f, u32 h_f, पूर्णांक h,
			      पूर्णांक d_l, पूर्णांक d_r, u8 *l, u8 *r)
अणु
	पूर्णांक a_n, a_d, h_r, l_r;

	h_r = d_l;
	l_r = 100 - d_r;

	a_n = (पूर्णांक)h_f * d_l + (पूर्णांक)l_f * (h - d_r);
	a_d = (पूर्णांक)l_f * l_r + (पूर्णांक)h_f * h_r;

	अगर (a_d != 0) अणु
		*l = d_l - h_r * a_n / a_d;
		*r = d_r + l_r * a_n / a_d;
	पूर्ण
पूर्ण

अटल व्योम rv6xx_calculate_ap(काष्ठा radeon_device *rdev,
			       काष्ठा rv6xx_ps *state)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	pi->hw.lp[0] = 0;
	pi->hw.rp[R600_PM_NUMBER_OF_ACTIVITY_LEVELS - 1]
		= 100;

	rv6xx_calculate_t(state->low.sclk,
			  state->medium.sclk,
			  R600_AH_DFLT,
			  R600_LMP_DFLT,
			  R600_RLP_DFLT,
			  &pi->hw.lp[1],
			  &pi->hw.rp[0]);

	rv6xx_calculate_t(state->medium.sclk,
			  state->high.sclk,
			  R600_AH_DFLT,
			  R600_LHP_DFLT,
			  R600_RMP_DFLT,
			  &pi->hw.lp[2],
			  &pi->hw.rp[1]);

पूर्ण

अटल व्योम rv6xx_calculate_stepping_parameters(काष्ठा radeon_device *rdev,
						काष्ठा radeon_ps *new_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);

	rv6xx_calculate_engine_speed_stepping_parameters(rdev, new_state);
	rv6xx_calculate_memory_घड़ी_stepping_parameters(rdev, new_state);
	rv6xx_calculate_voltage_stepping_parameters(rdev, new_state);
	rv6xx_calculate_ap(rdev, new_state);
पूर्ण

अटल व्योम rv6xx_program_stepping_parameters_except_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	rv6xx_program_mclk_stepping_parameters_except_lowest_entry(rdev);
	अगर (pi->voltage_control)
		rv6xx_program_voltage_stepping_parameters_except_lowest_entry(rdev);
	rv6xx_program_backbias_stepping_parameters_except_lowest_entry(rdev);
	rv6xx_program_sclk_spपढ़ो_spectrum_parameters_except_lowest_entry(rdev);
	rv6xx_program_mclk_spपढ़ो_spectrum_parameters(rdev);
	rv6xx_program_memory_timing_parameters(rdev);
पूर्ण

अटल व्योम rv6xx_program_stepping_parameters_lowest_entry(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	rv6xx_program_mclk_stepping_parameters_lowest_entry(rdev);
	अगर (pi->voltage_control)
		rv6xx_program_voltage_stepping_parameters_lowest_entry(rdev);
	rv6xx_program_backbias_stepping_parameters_lowest_entry(rdev);
	rv6xx_program_sclk_spपढ़ो_spectrum_parameters_lowest_entry(rdev);
पूर्ण

अटल व्योम rv6xx_program_घातer_level_low(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	r600_घातer_level_set_voltage_index(rdev, R600_POWER_LEVEL_LOW,
					   pi->hw.low_vddc_index);
	r600_घातer_level_set_mem_घड़ी_index(rdev, R600_POWER_LEVEL_LOW,
					     pi->hw.low_mclk_index);
	r600_घातer_level_set_eng_घड़ी_index(rdev, R600_POWER_LEVEL_LOW,
					     pi->hw.low_sclk_index);
	r600_घातer_level_set_watermark_id(rdev, R600_POWER_LEVEL_LOW,
					  R600_DISPLAY_WATERMARK_LOW);
	r600_घातer_level_set_pcie_gen2(rdev, R600_POWER_LEVEL_LOW,
				       pi->hw.pcie_gen2[R600_POWER_LEVEL_LOW]);
पूर्ण

अटल व्योम rv6xx_program_घातer_level_low_to_lowest_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	r600_घातer_level_set_voltage_index(rdev, R600_POWER_LEVEL_LOW, 0);
	r600_घातer_level_set_mem_घड़ी_index(rdev, R600_POWER_LEVEL_LOW, 0);
	r600_घातer_level_set_eng_घड़ी_index(rdev, R600_POWER_LEVEL_LOW, 0);

	r600_घातer_level_set_watermark_id(rdev, R600_POWER_LEVEL_LOW,
					  R600_DISPLAY_WATERMARK_LOW);

	r600_घातer_level_set_pcie_gen2(rdev, R600_POWER_LEVEL_LOW,
				       pi->hw.pcie_gen2[R600_POWER_LEVEL_LOW]);

पूर्ण

अटल व्योम rv6xx_program_घातer_level_medium(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	r600_घातer_level_set_voltage_index(rdev, R600_POWER_LEVEL_MEDIUM,
					  pi->hw.medium_vddc_index);
	r600_घातer_level_set_mem_घड़ी_index(rdev, R600_POWER_LEVEL_MEDIUM,
					    pi->hw.medium_mclk_index);
	r600_घातer_level_set_eng_घड़ी_index(rdev, R600_POWER_LEVEL_MEDIUM,
					    pi->hw.medium_sclk_index);
	r600_घातer_level_set_watermark_id(rdev, R600_POWER_LEVEL_MEDIUM,
					 R600_DISPLAY_WATERMARK_LOW);
	r600_घातer_level_set_pcie_gen2(rdev, R600_POWER_LEVEL_MEDIUM,
				      pi->hw.pcie_gen2[R600_POWER_LEVEL_MEDIUM]);
पूर्ण

अटल व्योम rv6xx_program_घातer_level_medium_क्रम_transition(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	rv6xx_program_mclk_stepping_entry(rdev,
					  R600_POWER_LEVEL_CTXSW,
					  pi->hw.mclks[pi->hw.low_mclk_index]);

	r600_घातer_level_set_voltage_index(rdev, R600_POWER_LEVEL_MEDIUM, 1);

	r600_घातer_level_set_mem_घड़ी_index(rdev, R600_POWER_LEVEL_MEDIUM,
					     R600_POWER_LEVEL_CTXSW);
	r600_घातer_level_set_eng_घड़ी_index(rdev, R600_POWER_LEVEL_MEDIUM,
					     pi->hw.medium_sclk_index);

	r600_घातer_level_set_watermark_id(rdev, R600_POWER_LEVEL_MEDIUM,
					  R600_DISPLAY_WATERMARK_LOW);

	rv6xx_enable_engine_spपढ़ो_spectrum(rdev, R600_POWER_LEVEL_MEDIUM, false);

	r600_घातer_level_set_pcie_gen2(rdev, R600_POWER_LEVEL_MEDIUM,
				       pi->hw.pcie_gen2[R600_POWER_LEVEL_LOW]);
पूर्ण

अटल व्योम rv6xx_program_घातer_level_high(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	r600_घातer_level_set_voltage_index(rdev, R600_POWER_LEVEL_HIGH,
					   pi->hw.high_vddc_index);
	r600_घातer_level_set_mem_घड़ी_index(rdev, R600_POWER_LEVEL_HIGH,
					     pi->hw.high_mclk_index);
	r600_घातer_level_set_eng_घड़ी_index(rdev, R600_POWER_LEVEL_HIGH,
					     pi->hw.high_sclk_index);

	r600_घातer_level_set_watermark_id(rdev, R600_POWER_LEVEL_HIGH,
					  R600_DISPLAY_WATERMARK_HIGH);

	r600_घातer_level_set_pcie_gen2(rdev, R600_POWER_LEVEL_HIGH,
				       pi->hw.pcie_gen2[R600_POWER_LEVEL_HIGH]);
पूर्ण

अटल व्योम rv6xx_enable_backbias(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, BACKBIAS_PAD_EN | BACKBIAS_DPM_CNTL,
			 ~(BACKBIAS_PAD_EN | BACKBIAS_DPM_CNTL));
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0,
			 ~(BACKBIAS_VALUE | BACKBIAS_PAD_EN | BACKBIAS_DPM_CNTL));
पूर्ण

अटल व्योम rv6xx_program_display_gap(काष्ठा radeon_device *rdev)
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

अटल व्योम rv6xx_set_sw_voltage_to_safe(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_ps *new_ps,
					 काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_ps *old_state = rv6xx_get_ps(old_ps);
	u16 safe_voltage;

	safe_voltage = (new_state->low.vddc >= old_state->low.vddc) ?
		new_state->low.vddc : old_state->low.vddc;

	rv6xx_program_voltage_stepping_entry(rdev, R600_POWER_LEVEL_CTXSW,
					     safe_voltage);

	WREG32_P(GENERAL_PWRMGT, SW_GPIO_INDEX(R600_POWER_LEVEL_CTXSW),
		 ~SW_GPIO_INDEX_MASK);
पूर्ण

अटल व्योम rv6xx_set_sw_voltage_to_low(काष्ठा radeon_device *rdev,
					काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *old_state = rv6xx_get_ps(old_ps);

	rv6xx_program_voltage_stepping_entry(rdev, R600_POWER_LEVEL_CTXSW,
					     old_state->low.vddc);

	WREG32_P(GENERAL_PWRMGT, SW_GPIO_INDEX(R600_POWER_LEVEL_CTXSW),
		~SW_GPIO_INDEX_MASK);
पूर्ण

अटल व्योम rv6xx_set_safe_backbias(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_ps *new_ps,
				    काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_ps *old_state = rv6xx_get_ps(old_ps);

	अगर ((new_state->low.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE) &&
	    (old_state->low.flags & ATOM_PPLIB_R600_FLAGS_BACKBIASENABLE))
		WREG32_P(GENERAL_PWRMGT, BACKBIAS_VALUE, ~BACKBIAS_VALUE);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~BACKBIAS_VALUE);
पूर्ण

अटल व्योम rv6xx_set_safe_pcie_gen2(काष्ठा radeon_device *rdev,
				     काष्ठा radeon_ps *new_ps,
				     काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_ps *old_state = rv6xx_get_ps(old_ps);

	अगर ((new_state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) !=
	    (old_state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2))
		rv6xx_क्रमce_pcie_gen1(rdev);
पूर्ण

अटल व्योम rv6xx_enable_dynamic_voltage_control(काष्ठा radeon_device *rdev,
						 bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, VOLT_PWRMGT_EN, ~VOLT_PWRMGT_EN);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~VOLT_PWRMGT_EN);
पूर्ण

अटल व्योम rv6xx_enable_dynamic_backbias_control(काष्ठा radeon_device *rdev,
						  bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, BACKBIAS_DPM_CNTL, ~BACKBIAS_DPM_CNTL);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~BACKBIAS_DPM_CNTL);
पूर्ण

अटल पूर्णांक rv6xx_step_sw_voltage(काष्ठा radeon_device *rdev,
				 u16 initial_voltage,
				 u16 target_voltage)
अणु
	u16 current_voltage;
	u16 true_target_voltage;
	u16 voltage_step;
	पूर्णांक चिन्हित_voltage_step;

	अगर ((radeon_atom_get_voltage_step(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					  &voltage_step)) ||
	    (radeon_atom_round_to_true_voltage(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					       initial_voltage, &current_voltage)) ||
	    (radeon_atom_round_to_true_voltage(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC,
					       target_voltage, &true_target_voltage)))
		वापस -EINVAL;

	अगर (true_target_voltage < current_voltage)
		चिन्हित_voltage_step = -(पूर्णांक)voltage_step;
	अन्यथा
		चिन्हित_voltage_step = voltage_step;

	जबतक (current_voltage != true_target_voltage) अणु
		current_voltage += चिन्हित_voltage_step;
		rv6xx_program_voltage_stepping_entry(rdev, R600_POWER_LEVEL_CTXSW,
						     current_voltage);
		msleep((rdev->pm.dpm.voltage_response_समय + 999) / 1000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv6xx_step_voltage_अगर_increasing(काष्ठा radeon_device *rdev,
					    काष्ठा radeon_ps *new_ps,
					    काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_ps *old_state = rv6xx_get_ps(old_ps);

	अगर (new_state->low.vddc > old_state->low.vddc)
		वापस rv6xx_step_sw_voltage(rdev,
					     old_state->low.vddc,
					     new_state->low.vddc);

	वापस 0;
पूर्ण

अटल पूर्णांक rv6xx_step_voltage_अगर_decreasing(काष्ठा radeon_device *rdev,
					    काष्ठा radeon_ps *new_ps,
					    काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_ps *old_state = rv6xx_get_ps(old_ps);

	अगर (new_state->low.vddc < old_state->low.vddc)
		वापस rv6xx_step_sw_voltage(rdev,
					     old_state->low.vddc,
					     new_state->low.vddc);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम rv6xx_enable_high(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	अगर ((pi->restricted_levels < 1) ||
	    (pi->restricted_levels == 3))
		r600_घातer_level_enable(rdev, R600_POWER_LEVEL_HIGH, true);
पूर्ण

अटल व्योम rv6xx_enable_medium(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	अगर (pi->restricted_levels < 2)
		r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, true);
पूर्ण

अटल व्योम rv6xx_set_dpm_event_sources(काष्ठा radeon_device *rdev, u32 sources)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
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

अटल व्योम rv6xx_enable_स्वतः_throttle_source(काष्ठा radeon_device *rdev,
					      क्रमागत radeon_dpm_स्वतः_throttle_src source,
					      bool enable)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	अगर (enable) अणु
		अगर (!(pi->active_स्वतः_throttle_sources & (1 << source))) अणु
			pi->active_स्वतः_throttle_sources |= 1 << source;
			rv6xx_set_dpm_event_sources(rdev, pi->active_स्वतः_throttle_sources);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pi->active_स्वतः_throttle_sources & (1 << source)) अणु
			pi->active_स्वतः_throttle_sources &= ~(1 << source);
			rv6xx_set_dpm_event_sources(rdev, pi->active_स्वतः_throttle_sources);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम rv6xx_enable_thermal_protection(काष्ठा radeon_device *rdev,
					    bool enable)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	अगर (pi->active_स्वतः_throttle_sources)
		r600_enable_thermal_protection(rdev, enable);
पूर्ण

अटल व्योम rv6xx_generate_transition_stepping(काष्ठा radeon_device *rdev,
					       काष्ठा radeon_ps *new_ps,
					       काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_ps *old_state = rv6xx_get_ps(old_ps);
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	rv6xx_generate_steps(rdev,
			     old_state->low.sclk,
			     new_state->low.sclk,
			     0, &pi->hw.medium_sclk_index);
पूर्ण

अटल व्योम rv6xx_generate_low_step(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_ps *new_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	pi->hw.low_sclk_index = 0;
	rv6xx_generate_single_step(rdev,
				   new_state->low.sclk,
				   0);
पूर्ण

अटल व्योम rv6xx_invalidate_पूर्णांकermediate_steps(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	rv6xx_invalidate_पूर्णांकermediate_steps_range(rdev, 0,
						  pi->hw.medium_sclk_index);
पूर्ण

अटल व्योम rv6xx_generate_stepping_table(काष्ठा radeon_device *rdev,
					  काष्ठा radeon_ps *new_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	pi->hw.low_sclk_index = 0;

	rv6xx_generate_steps(rdev,
			     new_state->low.sclk,
			     new_state->medium.sclk,
			     0,
			     &pi->hw.medium_sclk_index);
	rv6xx_generate_steps(rdev,
			     new_state->medium.sclk,
			     new_state->high.sclk,
			     pi->hw.medium_sclk_index,
			     &pi->hw.high_sclk_index);
पूर्ण

अटल व्योम rv6xx_enable_spपढ़ो_spectrum(काष्ठा radeon_device *rdev,
					 bool enable)
अणु
	अगर (enable)
		rv6xx_enable_dynamic_spपढ़ो_spectrum(rdev, true);
	अन्यथा अणु
		rv6xx_enable_engine_spपढ़ो_spectrum(rdev, R600_POWER_LEVEL_LOW, false);
		rv6xx_enable_engine_spपढ़ो_spectrum(rdev, R600_POWER_LEVEL_MEDIUM, false);
		rv6xx_enable_engine_spपढ़ो_spectrum(rdev, R600_POWER_LEVEL_HIGH, false);
		rv6xx_enable_dynamic_spपढ़ो_spectrum(rdev, false);
		rv6xx_enable_memory_spपढ़ो_spectrum(rdev, false);
	पूर्ण
पूर्ण

अटल व्योम rv6xx_reset_lvपंचांग_data_sync(काष्ठा radeon_device *rdev)
अणु
	अगर (ASIC_IS_DCE3(rdev))
		WREG32_P(DCE3_LVTMA_DATA_SYNCHRONIZATION, LVTMA_PFREQCHG, ~LVTMA_PFREQCHG);
	अन्यथा
		WREG32_P(LVTMA_DATA_SYNCHRONIZATION, LVTMA_PFREQCHG, ~LVTMA_PFREQCHG);
पूर्ण

अटल व्योम rv6xx_enable_dynamic_pcie_gen2(काष्ठा radeon_device *rdev,
					   काष्ठा radeon_ps *new_ps,
					   bool enable)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);

	अगर (enable) अणु
		rv6xx_enable_bअगर_dynamic_pcie_gen2(rdev, true);
		rv6xx_enable_pcie_gen2_support(rdev);
		r600_enable_dynamic_pcie_gen2(rdev, true);
	पूर्ण अन्यथा अणु
		अगर (!(new_state->low.flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2))
			rv6xx_क्रमce_pcie_gen1(rdev);
		rv6xx_enable_bअगर_dynamic_pcie_gen2(rdev, false);
		r600_enable_dynamic_pcie_gen2(rdev, false);
	पूर्ण
पूर्ण

अटल व्योम rv6xx_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(काष्ठा radeon_device *rdev,
						     काष्ठा radeon_ps *new_ps,
						     काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_ps *current_state = rv6xx_get_ps(old_ps);

	अगर ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		वापस;

	अगर (new_state->high.sclk >= current_state->high.sclk)
		वापस;

	radeon_set_uvd_घड़ीs(rdev, new_ps->vclk, new_ps->dclk);
पूर्ण

अटल व्योम rv6xx_set_uvd_घड़ी_after_set_eng_घड़ी(काष्ठा radeon_device *rdev,
						    काष्ठा radeon_ps *new_ps,
						    काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा rv6xx_ps *new_state = rv6xx_get_ps(new_ps);
	काष्ठा rv6xx_ps *current_state = rv6xx_get_ps(old_ps);

	अगर ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		वापस;

	अगर (new_state->high.sclk < current_state->high.sclk)
		वापस;

	radeon_set_uvd_घड़ीs(rdev, new_ps->vclk, new_ps->dclk);
पूर्ण

पूर्णांक rv6xx_dpm_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	काष्ठा radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;

	अगर (r600_dynamicpm_enabled(rdev))
		वापस -EINVAL;

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_enable_backbias(rdev, true);

	अगर (pi->dynamic_ss)
		rv6xx_enable_spपढ़ो_spectrum(rdev, true);

	rv6xx_program_mpll_timing_parameters(rdev);
	rv6xx_program_bsp(rdev);
	rv6xx_program_git(rdev);
	rv6xx_program_tp(rdev);
	rv6xx_program_tpp(rdev);
	rv6xx_program_sstp(rdev);
	rv6xx_program_fcp(rdev);
	rv6xx_program_vddc3d_parameters(rdev);
	rv6xx_program_voltage_timing_parameters(rdev);
	rv6xx_program_engine_speed_parameters(rdev);

	rv6xx_enable_display_gap(rdev, true);
	अगर (pi->display_gap == false)
		rv6xx_enable_display_gap(rdev, false);

	rv6xx_program_घातer_level_enter_state(rdev);

	rv6xx_calculate_stepping_parameters(rdev, boot_ps);

	अगर (pi->voltage_control)
		rv6xx_program_voltage_gpio_pins(rdev);

	rv6xx_generate_stepping_table(rdev, boot_ps);

	rv6xx_program_stepping_parameters_except_lowest_entry(rdev);
	rv6xx_program_stepping_parameters_lowest_entry(rdev);

	rv6xx_program_घातer_level_low(rdev);
	rv6xx_program_घातer_level_medium(rdev);
	rv6xx_program_घातer_level_high(rdev);
	rv6xx_program_vc(rdev);
	rv6xx_program_at(rdev);

	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, true);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_HIGH, true);

	rv6xx_enable_स्वतः_throttle_source(rdev, RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL, true);

	r600_start_dpm(rdev);

	अगर (pi->voltage_control)
		rv6xx_enable_अटल_voltage_control(rdev, boot_ps, false);

	अगर (pi->dynamic_pcie_gen2)
		rv6xx_enable_dynamic_pcie_gen2(rdev, boot_ps, true);

	अगर (pi->gfx_घड़ी_gating)
		r600_gfx_घड़ीgating_enable(rdev, true);

	वापस 0;
पूर्ण

व्योम rv6xx_dpm_disable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	काष्ठा radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;

	अगर (!r600_dynamicpm_enabled(rdev))
		वापस;

	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, true);
	rv6xx_enable_display_gap(rdev, false);
	rv6xx_clear_vc(rdev);
	r600_set_at(rdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);

	अगर (pi->thermal_protection)
		r600_enable_thermal_protection(rdev, false);

	r600_रुको_क्रम_घातer_level(rdev, R600_POWER_LEVEL_LOW);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_HIGH, false);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_enable_backbias(rdev, false);

	rv6xx_enable_spपढ़ो_spectrum(rdev, false);

	अगर (pi->voltage_control)
		rv6xx_enable_अटल_voltage_control(rdev, boot_ps, true);

	अगर (pi->dynamic_pcie_gen2)
		rv6xx_enable_dynamic_pcie_gen2(rdev, boot_ps, false);

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	पूर्ण

	अगर (pi->gfx_घड़ी_gating)
		r600_gfx_घड़ीgating_enable(rdev, false);

	r600_stop_dpm(rdev);
पूर्ण

पूर्णांक rv6xx_dpm_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	काष्ठा radeon_ps *old_ps = rdev->pm.dpm.current_ps;
	पूर्णांक ret;

	pi->restricted_levels = 0;

	rv6xx_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(rdev, new_ps, old_ps);

	rv6xx_clear_vc(rdev);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_set_at(rdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);

	अगर (pi->thermal_protection)
		r600_enable_thermal_protection(rdev, false);

	r600_रुको_क्रम_घातer_level(rdev, R600_POWER_LEVEL_LOW);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_HIGH, false);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);

	rv6xx_generate_transition_stepping(rdev, new_ps, old_ps);
	rv6xx_program_घातer_level_medium_क्रम_transition(rdev);

	अगर (pi->voltage_control) अणु
		rv6xx_set_sw_voltage_to_safe(rdev, new_ps, old_ps);
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
			rv6xx_set_sw_voltage_to_low(rdev, old_ps);
	पूर्ण

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_set_safe_backbias(rdev, new_ps, old_ps);

	अगर (pi->dynamic_pcie_gen2)
		rv6xx_set_safe_pcie_gen2(rdev, new_ps, old_ps);

	अगर (pi->voltage_control)
		rv6xx_enable_dynamic_voltage_control(rdev, false);

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_enable_dynamic_backbias_control(rdev, false);

	अगर (pi->voltage_control) अणु
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC)
			rv6xx_step_voltage_अगर_increasing(rdev, new_ps, old_ps);
		msleep((rdev->pm.dpm.voltage_response_समय + 999) / 1000);
	पूर्ण

	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, true);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_LOW, false);
	r600_रुको_क्रम_घातer_level_unequal(rdev, R600_POWER_LEVEL_LOW);

	rv6xx_generate_low_step(rdev, new_ps);
	rv6xx_invalidate_पूर्णांकermediate_steps(rdev);
	rv6xx_calculate_stepping_parameters(rdev, new_ps);
	rv6xx_program_stepping_parameters_lowest_entry(rdev);
	rv6xx_program_घातer_level_low_to_lowest_state(rdev);

	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_रुको_क्रम_घातer_level(rdev, R600_POWER_LEVEL_LOW);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);

	अगर (pi->voltage_control) अणु
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC) अणु
			ret = rv6xx_step_voltage_अगर_decreasing(rdev, new_ps, old_ps);
			अगर (ret)
				वापस ret;
		पूर्ण
		rv6xx_enable_dynamic_voltage_control(rdev, true);
	पूर्ण

	अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS)
		rv6xx_enable_dynamic_backbias_control(rdev, true);

	अगर (pi->dynamic_pcie_gen2)
		rv6xx_enable_dynamic_pcie_gen2(rdev, new_ps, true);

	rv6xx_reset_lvपंचांग_data_sync(rdev);

	rv6xx_generate_stepping_table(rdev, new_ps);
	rv6xx_program_stepping_parameters_except_lowest_entry(rdev);
	rv6xx_program_घातer_level_low(rdev);
	rv6xx_program_घातer_level_medium(rdev);
	rv6xx_program_घातer_level_high(rdev);
	rv6xx_enable_medium(rdev);
	rv6xx_enable_high(rdev);

	अगर (pi->thermal_protection)
		rv6xx_enable_thermal_protection(rdev, true);
	rv6xx_program_vc(rdev);
	rv6xx_program_at(rdev);

	rv6xx_set_uvd_घड़ी_after_set_eng_घड़ी(rdev, new_ps, old_ps);

	वापस 0;
पूर्ण

व्योम rv6xx_setup_asic(काष्ठा radeon_device *rdev)
अणु
	r600_enable_acpi_pm(rdev);

	अगर (radeon_aspm != 0) अणु
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_ASPM_L0s)
			rv6xx_enable_l0s(rdev);
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_ASPM_L1)
			rv6xx_enable_l1(rdev);
		अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_TURNOFFPLL_ASPML1)
			rv6xx_enable_pll_sleep_in_l1(rdev);
	पूर्ण
पूर्ण

व्योम rv6xx_dpm_display_configuration_changed(काष्ठा radeon_device *rdev)
अणु
	rv6xx_program_display_gap(rdev);
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

अटल व्योम rv6xx_parse_pplib_non_घड़ी_info(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ps *rps,
					     काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info)
अणु
	rps->caps = le32_to_cpu(non_घड़ी_info->ulCapsAndSettings);
	rps->class = le16_to_cpu(non_घड़ी_info->usClassअगरication);
	rps->class2 = le16_to_cpu(non_घड़ी_info->usClassअगरication2);

	अगर (r600_is_uvd_state(rps->class, rps->class2)) अणु
		rps->vclk = RV6XX_DEFAULT_VCLK_FREQ;
		rps->dclk = RV6XX_DEFAULT_DCLK_FREQ;
	पूर्ण अन्यथा अणु
		rps->vclk = 0;
		rps->dclk = 0;
	पूर्ण

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT)
		rdev->pm.dpm.boot_ps = rps;
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		rdev->pm.dpm.uvd_ps = rps;
पूर्ण

अटल व्योम rv6xx_parse_pplib_घड़ी_info(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_ps *rps, पूर्णांक index,
					 जोड़ pplib_घड़ी_info *घड़ी_info)
अणु
	काष्ठा rv6xx_ps *ps = rv6xx_get_ps(rps);
	u32 sclk, mclk;
	u16 vddc;
	काष्ठा rv6xx_pl *pl;

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

	sclk = le16_to_cpu(घड़ी_info->r600.usEngineClockLow);
	sclk |= घड़ी_info->r600.ucEngineClockHigh << 16;
	mclk = le16_to_cpu(घड़ी_info->r600.usMemoryClockLow);
	mclk |= घड़ी_info->r600.ucMemoryClockHigh << 16;

	pl->mclk = mclk;
	pl->sclk = sclk;
	pl->vddc = le16_to_cpu(घड़ी_info->r600.usVDDC);
	pl->flags = le32_to_cpu(घड़ी_info->r600.ulFlags);

	/* patch up vddc अगर necessary */
	अगर (pl->vddc == 0xff01) अणु
		अगर (radeon_atom_get_max_vddc(rdev, 0, 0, &vddc) == 0)
			pl->vddc = vddc;
	पूर्ण

	/* fix up pcie gen2 */
	अगर (pl->flags & ATOM_PPLIB_R600_FLAGS_PCIEGEN2) अणु
		अगर ((rdev->family == CHIP_RV610) || (rdev->family == CHIP_RV630)) अणु
			अगर (pl->vddc < 1100)
				pl->flags &= ~ATOM_PPLIB_R600_FLAGS_PCIEGEN2;
		पूर्ण
	पूर्ण

	/* patch up boot state */
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) अणु
		u16 vddc, vddci, mvdd;
		radeon_atombios_get_शेष_voltages(rdev, &vddc, &vddci, &mvdd);
		pl->mclk = rdev->घड़ी.शेष_mclk;
		pl->sclk = rdev->घड़ी.शेष_sclk;
		pl->vddc = vddc;
	पूर्ण
पूर्ण

अटल पूर्णांक rv6xx_parse_घातer_table(काष्ठा radeon_device *rdev)
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
	काष्ठा rv6xx_ps *ps;

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
			ps = kzalloc(माप(काष्ठा rv6xx_ps), GFP_KERNEL);
			अगर (ps == शून्य) अणु
				kमुक्त(rdev->pm.dpm.ps);
				वापस -ENOMEM;
			पूर्ण
			rdev->pm.dpm.ps[i].ps_priv = ps;
			rv6xx_parse_pplib_non_घड़ी_info(rdev, &rdev->pm.dpm.ps[i],
							 non_घड़ी_info);
			idx = (u8 *)&घातer_state->v1.ucClockStateIndices[0];
			क्रम (j = 0; j < (घातer_info->pplib.ucStateEntrySize - 1); j++) अणु
				घड़ी_info = (जोड़ pplib_घड़ी_info *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(घातer_info->pplib.usClockInfoArrayOffset) +
					 (idx[j] * घातer_info->pplib.ucClockInfoSize));
				rv6xx_parse_pplib_घड़ी_info(rdev,
							     &rdev->pm.dpm.ps[i], j,
							     घड़ी_info);
			पूर्ण
		पूर्ण
	पूर्ण
	rdev->pm.dpm.num_ps = घातer_info->pplib.ucNumStates;
	वापस 0;
पूर्ण

पूर्णांक rv6xx_dpm_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_atom_ss ss;
	काष्ठा atom_घड़ी_भागiders भागiders;
	काष्ठा rv6xx_घातer_info *pi;
	पूर्णांक ret;

	pi = kzalloc(माप(काष्ठा rv6xx_घातer_info), GFP_KERNEL);
	अगर (pi == शून्य)
		वापस -ENOMEM;
	rdev->pm.dpm.priv = pi;

	ret = r600_get_platक्रमm_caps(rdev);
	अगर (ret)
		वापस ret;

	ret = rv6xx_parse_घातer_table(rdev);
	अगर (ret)
		वापस ret;

	अगर (rdev->pm.dpm.voltage_response_समय == 0)
		rdev->pm.dpm.voltage_response_समय = R600_VOLTAGERESPONSETIME_DFLT;
	अगर (rdev->pm.dpm.backbias_response_समय == 0)
		rdev->pm.dpm.backbias_response_समय = R600_BACKBIASRESPONSETIME_DFLT;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     0, false, &भागiders);
	अगर (ret)
		pi->spll_ref_भाग = भागiders.ref_भाग + 1;
	अन्यथा
		pi->spll_ref_भाग = R600_REFERENCEDIVIDER_DFLT;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_MEMORY_PLL_PARAM,
					     0, false, &भागiders);
	अगर (ret)
		pi->mpll_ref_भाग = भागiders.ref_भाग + 1;
	अन्यथा
		pi->mpll_ref_भाग = R600_REFERENCEDIVIDER_DFLT;

	अगर (rdev->family >= CHIP_RV670)
		pi->fb_भाग_scale = 1;
	अन्यथा
		pi->fb_भाग_scale = 0;

	pi->voltage_control =
		radeon_atom_is_voltage_gpio(rdev, SET_VOLTAGE_TYPE_ASIC_VDDC, 0);

	pi->gfx_घड़ी_gating = true;

	pi->sclk_ss = radeon_atombios_get_asic_ss_info(rdev, &ss,
						       ASIC_INTERNAL_ENGINE_SS, 0);
	pi->mclk_ss = radeon_atombios_get_asic_ss_info(rdev, &ss,
						       ASIC_INTERNAL_MEMORY_SS, 0);

	/* Disable sclk ss, causes hangs on a lot of प्रणालीs */
	pi->sclk_ss = false;

	अगर (pi->sclk_ss || pi->mclk_ss)
		pi->dynamic_ss = true;
	अन्यथा
		pi->dynamic_ss = false;

	pi->dynamic_pcie_gen2 = true;

	अगर (pi->gfx_घड़ी_gating &&
	    (rdev->pm.पूर्णांक_thermal_type != THERMAL_TYPE_NONE))
		pi->thermal_protection = true;
	अन्यथा
		pi->thermal_protection = false;

	pi->display_gap = true;

	वापस 0;
पूर्ण

व्योम rv6xx_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_ps *rps)
अणु
	काष्ठा rv6xx_ps *ps = rv6xx_get_ps(rps);
	काष्ठा rv6xx_pl *pl;

	r600_dpm_prपूर्णांक_class_info(rps->class, rps->class2);
	r600_dpm_prपूर्णांक_cap_info(rps->caps);
	prपूर्णांकk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	pl = &ps->low;
	prपूर्णांकk("\t\tpower level 0    sclk: %u mclk: %u vddc: %u\n",
	       pl->sclk, pl->mclk, pl->vddc);
	pl = &ps->medium;
	prपूर्णांकk("\t\tpower level 1    sclk: %u mclk: %u vddc: %u\n",
	       pl->sclk, pl->mclk, pl->vddc);
	pl = &ps->high;
	prपूर्णांकk("\t\tpower level 2    sclk: %u mclk: %u vddc: %u\n",
	       pl->sclk, pl->mclk, pl->vddc);
	r600_dpm_prपूर्णांक_ps_status(rdev, rps);
पूर्ण

व्योम rv6xx_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						       काष्ठा seq_file *m)
अणु
	काष्ठा radeon_ps *rps = rdev->pm.dpm.current_ps;
	काष्ठा rv6xx_ps *ps = rv6xx_get_ps(rps);
	काष्ठा rv6xx_pl *pl;
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
		seq_म_लिखो(m, "power level %d    sclk: %u mclk: %u vddc: %u\n",
			   current_index, pl->sclk, pl->mclk, pl->vddc);
	पूर्ण
पूर्ण

/* get the current sclk in 10 khz units */
u32 rv6xx_dpm_get_current_sclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ps *rps = rdev->pm.dpm.current_ps;
	काष्ठा rv6xx_ps *ps = rv6xx_get_ps(rps);
	काष्ठा rv6xx_pl *pl;
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
		वापस pl->sclk;
	पूर्ण
पूर्ण

/* get the current mclk in 10 khz units */
u32 rv6xx_dpm_get_current_mclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ps *rps = rdev->pm.dpm.current_ps;
	काष्ठा rv6xx_ps *ps = rv6xx_get_ps(rps);
	काष्ठा rv6xx_pl *pl;
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
		वापस pl->mclk;
	पूर्ण
पूर्ण

व्योम rv6xx_dpm_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		kमुक्त(rdev->pm.dpm.ps[i].ps_priv);
	पूर्ण
	kमुक्त(rdev->pm.dpm.ps);
	kमुक्त(rdev->pm.dpm.priv);
पूर्ण

u32 rv6xx_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा rv6xx_ps *requested_state = rv6xx_get_ps(rdev->pm.dpm.requested_ps);

	अगर (low)
		वापस requested_state->low.sclk;
	अन्यथा
		वापस requested_state->high.sclk;
पूर्ण

u32 rv6xx_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा rv6xx_ps *requested_state = rv6xx_get_ps(rdev->pm.dpm.requested_ps);

	अगर (low)
		वापस requested_state->low.mclk;
	अन्यथा
		वापस requested_state->high.mclk;
पूर्ण

पूर्णांक rv6xx_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				      क्रमागत radeon_dpm_क्रमced_level level)
अणु
	काष्ठा rv6xx_घातer_info *pi = rv6xx_get_pi(rdev);

	अगर (level == RADEON_DPM_FORCED_LEVEL_HIGH) अणु
		pi->restricted_levels = 3;
	पूर्ण अन्यथा अगर (level == RADEON_DPM_FORCED_LEVEL_LOW) अणु
		pi->restricted_levels = 2;
	पूर्ण अन्यथा अणु
		pi->restricted_levels = 0;
	पूर्ण

	rv6xx_clear_vc(rdev);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_LOW, true);
	r600_set_at(rdev, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
	r600_रुको_क्रम_घातer_level(rdev, R600_POWER_LEVEL_LOW);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_HIGH, false);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);
	rv6xx_enable_medium(rdev);
	rv6xx_enable_high(rdev);
	अगर (pi->restricted_levels == 3)
		r600_घातer_level_enable(rdev, R600_POWER_LEVEL_LOW, false);
	rv6xx_program_vc(rdev);
	rv6xx_program_at(rdev);

	rdev->pm.dpm.क्रमced_level = level;

	वापस 0;
पूर्ण
