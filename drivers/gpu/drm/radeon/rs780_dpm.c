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

#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>

#समावेश "atom.h"
#समावेश "r600_dpm.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "rs780_dpm.h"
#समावेश "rs780d.h"

अटल काष्ठा igp_ps *rs780_get_ps(काष्ठा radeon_ps *rps)
अणु
	काष्ठा igp_ps *ps = rps->ps_priv;

	वापस ps;
पूर्ण

अटल काष्ठा igp_घातer_info *rs780_get_pi(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi = rdev->pm.dpm.priv;

	वापस pi;
पूर्ण

अटल व्योम rs780_get_pm_mode_parameters(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);
	काष्ठा radeon_mode_info *minfo = &rdev->mode_info;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	पूर्णांक i;

	/* शेषs */
	pi->crtc_id = 0;
	pi->refresh_rate = 60;

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		crtc = (काष्ठा drm_crtc *)minfo->crtcs[i];
		अगर (crtc && crtc->enabled) अणु
			radeon_crtc = to_radeon_crtc(crtc);
			pi->crtc_id = radeon_crtc->crtc_id;
			अगर (crtc->mode.htotal && crtc->mode.vtotal)
				pi->refresh_rate = drm_mode_vrefresh(&crtc->mode);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rs780_voltage_scaling_enable(काष्ठा radeon_device *rdev, bool enable);

अटल पूर्णांक rs780_initialize_dpm_घातer_state(काष्ठा radeon_device *rdev,
					    काष्ठा radeon_ps *boot_ps)
अणु
	काष्ठा atom_घड़ी_भागiders भागiders;
	काष्ठा igp_ps *शेष_state = rs780_get_ps(boot_ps);
	पूर्णांक i, ret;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     शेष_state->sclk_low, false, &भागiders);
	अगर (ret)
		वापस ret;

	r600_engine_घड़ी_entry_set_reference_भागider(rdev, 0, भागiders.ref_भाग);
	r600_engine_घड़ी_entry_set_feedback_भागider(rdev, 0, भागiders.fb_भाग);
	r600_engine_घड़ी_entry_set_post_भागider(rdev, 0, भागiders.post_भाग);

	अगर (भागiders.enable_post_भाग)
		r600_engine_घड़ी_entry_enable_post_भागider(rdev, 0, true);
	अन्यथा
		r600_engine_घड़ी_entry_enable_post_भागider(rdev, 0, false);

	r600_engine_घड़ी_entry_set_step_समय(rdev, 0, R600_SST_DFLT);
	r600_engine_घड़ी_entry_enable_pulse_skipping(rdev, 0, false);

	r600_engine_घड़ी_entry_enable(rdev, 0, true);
	क्रम (i = 1; i < R600_PM_NUMBER_OF_SCLKS; i++)
		r600_engine_घड़ी_entry_enable(rdev, i, false);

	r600_enable_mclk_control(rdev, false);
	r600_voltage_control_enable_pins(rdev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rs780_initialize_dpm_parameters(काष्ठा radeon_device *rdev,
					   काष्ठा radeon_ps *boot_ps)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	r600_set_bsp(rdev, R600_BSU_DFLT, R600_BSP_DFLT);

	r600_set_at(rdev, 0, 0, 0, 0);

	r600_set_git(rdev, R600_GICST_DFLT);

	क्रम (i = 0; i < R600_PM_NUMBER_OF_TC; i++)
		r600_set_tc(rdev, i, 0, 0);

	r600_select_td(rdev, R600_TD_DFLT);
	r600_set_vrc(rdev, 0);

	r600_set_tpu(rdev, R600_TPU_DFLT);
	r600_set_tpc(rdev, R600_TPC_DFLT);

	r600_set_sstu(rdev, R600_SSTU_DFLT);
	r600_set_sst(rdev, R600_SST_DFLT);

	r600_set_fctu(rdev, R600_FCTU_DFLT);
	r600_set_fct(rdev, R600_FCT_DFLT);

	r600_set_vddc3d_oorsu(rdev, R600_VDDC3DOORSU_DFLT);
	r600_set_vddc3d_oorphc(rdev, R600_VDDC3DOORPHC_DFLT);
	r600_set_vddc3d_oorsdc(rdev, R600_VDDC3DOORSDC_DFLT);
	r600_set_ctxcgtt3d_rphc(rdev, R600_CTXCGTT3DRPHC_DFLT);
	r600_set_ctxcgtt3d_rsdc(rdev, R600_CTXCGTT3DRSDC_DFLT);

	r600_vid_rt_set_vru(rdev, R600_VRU_DFLT);
	r600_vid_rt_set_vrt(rdev, R600_VOLTAGERESPONSETIME_DFLT);
	r600_vid_rt_set_ssu(rdev, R600_SPLLSTEPUNIT_DFLT);

	ret = rs780_initialize_dpm_घातer_state(rdev, boot_ps);

	r600_घातer_level_set_voltage_index(rdev, R600_POWER_LEVEL_LOW,     0);
	r600_घातer_level_set_voltage_index(rdev, R600_POWER_LEVEL_MEDIUM,  0);
	r600_घातer_level_set_voltage_index(rdev, R600_POWER_LEVEL_HIGH,    0);

	r600_घातer_level_set_mem_घड़ी_index(rdev, R600_POWER_LEVEL_LOW,    0);
	r600_घातer_level_set_mem_घड़ी_index(rdev, R600_POWER_LEVEL_MEDIUM, 0);
	r600_घातer_level_set_mem_घड़ी_index(rdev, R600_POWER_LEVEL_HIGH,   0);

	r600_घातer_level_set_eng_घड़ी_index(rdev, R600_POWER_LEVEL_LOW,    0);
	r600_घातer_level_set_eng_घड़ी_index(rdev, R600_POWER_LEVEL_MEDIUM, 0);
	r600_घातer_level_set_eng_घड़ी_index(rdev, R600_POWER_LEVEL_HIGH,   0);

	r600_घातer_level_set_watermark_id(rdev, R600_POWER_LEVEL_LOW,    R600_DISPLAY_WATERMARK_HIGH);
	r600_घातer_level_set_watermark_id(rdev, R600_POWER_LEVEL_MEDIUM, R600_DISPLAY_WATERMARK_HIGH);
	r600_घातer_level_set_watermark_id(rdev, R600_POWER_LEVEL_HIGH,   R600_DISPLAY_WATERMARK_HIGH);

	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_CTXSW, false);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_HIGH, false);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_MEDIUM, false);
	r600_घातer_level_enable(rdev, R600_POWER_LEVEL_LOW, true);

	r600_घातer_level_set_enter_index(rdev, R600_POWER_LEVEL_LOW);

	r600_set_vrc(rdev, RS780_CGFTV_DFLT);

	वापस ret;
पूर्ण

अटल व्योम rs780_start_dpm(काष्ठा radeon_device *rdev)
अणु
	r600_enable_sclk_control(rdev, false);
	r600_enable_mclk_control(rdev, false);

	r600_dynamicpm_enable(rdev, true);

	radeon_रुको_क्रम_vblank(rdev, 0);
	radeon_रुको_क्रम_vblank(rdev, 1);

	r600_enable_spll_bypass(rdev, true);
	r600_रुको_क्रम_spll_change(rdev);
	r600_enable_spll_bypass(rdev, false);
	r600_रुको_क्रम_spll_change(rdev);

	r600_enable_spll_bypass(rdev, true);
	r600_रुको_क्रम_spll_change(rdev);
	r600_enable_spll_bypass(rdev, false);
	r600_रुको_क्रम_spll_change(rdev);

	r600_enable_sclk_control(rdev, true);
पूर्ण


अटल व्योम rs780_preset_ranges_slow_clk_fbभाग_en(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(FVTHROT_SLOW_CLK_FEEDBACK_DIV_REG1, RANGE_SLOW_CLK_FEEDBACK_DIV_EN,
		 ~RANGE_SLOW_CLK_FEEDBACK_DIV_EN);

	WREG32_P(FVTHROT_SLOW_CLK_FEEDBACK_DIV_REG1,
		 RANGE0_SLOW_CLK_FEEDBACK_DIV(RS780_SLOWCLKFEEDBACKDIV_DFLT),
		 ~RANGE0_SLOW_CLK_FEEDBACK_DIV_MASK);
पूर्ण

अटल व्योम rs780_preset_starting_fbभाग(काष्ठा radeon_device *rdev)
अणु
	u32 fbभाग = (RREG32(CG_SPLL_FUNC_CNTL) & SPLL_FB_DIV_MASK) >> SPLL_FB_DIV_SHIFT;

	WREG32_P(FVTHROT_FBDIV_REG1, STARTING_FEEDBACK_DIV(fbभाग),
		 ~STARTING_FEEDBACK_DIV_MASK);

	WREG32_P(FVTHROT_FBDIV_REG2, FORCED_FEEDBACK_DIV(fbभाग),
		 ~FORCED_FEEDBACK_DIV_MASK);

	WREG32_P(FVTHROT_FBDIV_REG1, FORCE_FEEDBACK_DIV, ~FORCE_FEEDBACK_DIV);
पूर्ण

अटल व्योम rs780_voltage_scaling_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);
	u32 fv_throt_pwm_fb_भाग_range[3];
	u32 fv_throt_pwm_range[4];

	अगर (rdev->pdev->device == 0x9614) अणु
		fv_throt_pwm_fb_भाग_range[0] = RS780D_FVTHROTPWMFBDIVRANGEREG0_DFLT;
		fv_throt_pwm_fb_भाग_range[1] = RS780D_FVTHROTPWMFBDIVRANGEREG1_DFLT;
		fv_throt_pwm_fb_भाग_range[2] = RS780D_FVTHROTPWMFBDIVRANGEREG2_DFLT;
	पूर्ण अन्यथा अगर ((rdev->pdev->device == 0x9714) ||
		   (rdev->pdev->device == 0x9715)) अणु
		fv_throt_pwm_fb_भाग_range[0] = RS880D_FVTHROTPWMFBDIVRANGEREG0_DFLT;
		fv_throt_pwm_fb_भाग_range[1] = RS880D_FVTHROTPWMFBDIVRANGEREG1_DFLT;
		fv_throt_pwm_fb_भाग_range[2] = RS880D_FVTHROTPWMFBDIVRANGEREG2_DFLT;
	पूर्ण अन्यथा अणु
		fv_throt_pwm_fb_भाग_range[0] = RS780_FVTHROTPWMFBDIVRANGEREG0_DFLT;
		fv_throt_pwm_fb_भाग_range[1] = RS780_FVTHROTPWMFBDIVRANGEREG1_DFLT;
		fv_throt_pwm_fb_भाग_range[2] = RS780_FVTHROTPWMFBDIVRANGEREG2_DFLT;
	पूर्ण

	अगर (pi->pwm_voltage_control) अणु
		fv_throt_pwm_range[0] = pi->min_voltage;
		fv_throt_pwm_range[1] = pi->min_voltage;
		fv_throt_pwm_range[2] = pi->max_voltage;
		fv_throt_pwm_range[3] = pi->max_voltage;
	पूर्ण अन्यथा अणु
		fv_throt_pwm_range[0] = pi->invert_pwm_required ?
			RS780_FVTHROTPWMRANGE3_GPIO_DFLT : RS780_FVTHROTPWMRANGE0_GPIO_DFLT;
		fv_throt_pwm_range[1] = pi->invert_pwm_required ?
			RS780_FVTHROTPWMRANGE2_GPIO_DFLT : RS780_FVTHROTPWMRANGE1_GPIO_DFLT;
		fv_throt_pwm_range[2] = pi->invert_pwm_required ?
			RS780_FVTHROTPWMRANGE1_GPIO_DFLT : RS780_FVTHROTPWMRANGE2_GPIO_DFLT;
		fv_throt_pwm_range[3] = pi->invert_pwm_required ?
			RS780_FVTHROTPWMRANGE0_GPIO_DFLT : RS780_FVTHROTPWMRANGE3_GPIO_DFLT;
	पूर्ण

	WREG32_P(FVTHROT_PWM_CTRL_REG0,
		 STARTING_PWM_HIGHTIME(pi->max_voltage),
		 ~STARTING_PWM_HIGHTIME_MASK);

	WREG32_P(FVTHROT_PWM_CTRL_REG0,
		 NUMBER_OF_CYCLES_IN_PERIOD(pi->num_of_cycles_in_period),
		 ~NUMBER_OF_CYCLES_IN_PERIOD_MASK);

	WREG32_P(FVTHROT_PWM_CTRL_REG0, FORCE_STARTING_PWM_HIGHTIME,
		 ~FORCE_STARTING_PWM_HIGHTIME);

	अगर (pi->invert_pwm_required)
		WREG32_P(FVTHROT_PWM_CTRL_REG0, INVERT_PWM_WAVEFORM, ~INVERT_PWM_WAVEFORM);
	अन्यथा
		WREG32_P(FVTHROT_PWM_CTRL_REG0, 0, ~INVERT_PWM_WAVEFORM);

	rs780_voltage_scaling_enable(rdev, true);

	WREG32(FVTHROT_PWM_CTRL_REG1,
	       (MIN_PWM_HIGHTIME(pi->min_voltage) |
		MAX_PWM_HIGHTIME(pi->max_voltage)));

	WREG32(FVTHROT_PWM_US_REG0, RS780_FVTHROTPWMUSREG0_DFLT);
	WREG32(FVTHROT_PWM_US_REG1, RS780_FVTHROTPWMUSREG1_DFLT);
	WREG32(FVTHROT_PWM_DS_REG0, RS780_FVTHROTPWMDSREG0_DFLT);
	WREG32(FVTHROT_PWM_DS_REG1, RS780_FVTHROTPWMDSREG1_DFLT);

	WREG32_P(FVTHROT_PWM_FEEDBACK_DIV_REG1,
		 RANGE0_PWM_FEEDBACK_DIV(fv_throt_pwm_fb_भाग_range[0]),
		 ~RANGE0_PWM_FEEDBACK_DIV_MASK);

	WREG32(FVTHROT_PWM_FEEDBACK_DIV_REG2,
	       (RANGE1_PWM_FEEDBACK_DIV(fv_throt_pwm_fb_भाग_range[1]) |
		RANGE2_PWM_FEEDBACK_DIV(fv_throt_pwm_fb_भाग_range[2])));

	WREG32(FVTHROT_PWM_FEEDBACK_DIV_REG3,
	       (RANGE0_PWM(fv_throt_pwm_range[1]) |
		RANGE1_PWM(fv_throt_pwm_range[2])));
	WREG32(FVTHROT_PWM_FEEDBACK_DIV_REG4,
	       (RANGE2_PWM(fv_throt_pwm_range[1]) |
		RANGE3_PWM(fv_throt_pwm_range[2])));
पूर्ण

अटल व्योम rs780_clk_scaling_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(FVTHROT_CNTRL_REG, ENABLE_FV_THROT | ENABLE_FV_UPDATE,
			 ~(ENABLE_FV_THROT | ENABLE_FV_UPDATE));
	अन्यथा
		WREG32_P(FVTHROT_CNTRL_REG, 0,
			 ~(ENABLE_FV_THROT | ENABLE_FV_UPDATE));
पूर्ण

अटल व्योम rs780_voltage_scaling_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(FVTHROT_CNTRL_REG, ENABLE_FV_THROT_IO, ~ENABLE_FV_THROT_IO);
	अन्यथा
		WREG32_P(FVTHROT_CNTRL_REG, 0, ~ENABLE_FV_THROT_IO);
पूर्ण

अटल व्योम rs780_set_engine_घड़ी_wfc(काष्ठा radeon_device *rdev)
अणु
	WREG32(FVTHROT_UTC0, RS780_FVTHROTUTC0_DFLT);
	WREG32(FVTHROT_UTC1, RS780_FVTHROTUTC1_DFLT);
	WREG32(FVTHROT_UTC2, RS780_FVTHROTUTC2_DFLT);
	WREG32(FVTHROT_UTC3, RS780_FVTHROTUTC3_DFLT);
	WREG32(FVTHROT_UTC4, RS780_FVTHROTUTC4_DFLT);

	WREG32(FVTHROT_DTC0, RS780_FVTHROTDTC0_DFLT);
	WREG32(FVTHROT_DTC1, RS780_FVTHROTDTC1_DFLT);
	WREG32(FVTHROT_DTC2, RS780_FVTHROTDTC2_DFLT);
	WREG32(FVTHROT_DTC3, RS780_FVTHROTDTC3_DFLT);
	WREG32(FVTHROT_DTC4, RS780_FVTHROTDTC4_DFLT);
पूर्ण

अटल व्योम rs780_set_engine_घड़ी_sc(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(FVTHROT_FBDIV_REG2,
		 FB_DIV_TIMER_VAL(RS780_FBDIVTIMERVAL_DFLT),
		 ~FB_DIV_TIMER_VAL_MASK);

	WREG32_P(FVTHROT_CNTRL_REG,
		 REFRESH_RATE_DIVISOR(0) | MINIMUM_CIP(0xf),
		 ~(REFRESH_RATE_DIVISOR_MASK | MINIMUM_CIP_MASK));
पूर्ण

अटल व्योम rs780_set_engine_घड़ी_प्रकारdc(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(FVTHROT_CNTRL_REG, 0, ~(FORCE_TREND_SEL | TREND_SEL_MODE));
पूर्ण

अटल व्योम rs780_set_engine_घड़ी_ssc(काष्ठा radeon_device *rdev)
अणु
	WREG32(FVTHROT_FB_US_REG0, RS780_FVTHROTFBUSREG0_DFLT);
	WREG32(FVTHROT_FB_US_REG1, RS780_FVTHROTFBUSREG1_DFLT);
	WREG32(FVTHROT_FB_DS_REG0, RS780_FVTHROTFBDSREG0_DFLT);
	WREG32(FVTHROT_FB_DS_REG1, RS780_FVTHROTFBDSREG1_DFLT);

	WREG32_P(FVTHROT_FBDIV_REG1, MAX_FEEDBACK_STEP(1), ~MAX_FEEDBACK_STEP_MASK);
पूर्ण

अटल व्योम rs780_program_at(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);

	WREG32(FVTHROT_TARGET_REG, 30000000 / pi->refresh_rate);
	WREG32(FVTHROT_CB1, 1000000 * 5 / pi->refresh_rate);
	WREG32(FVTHROT_CB2, 1000000 * 10 / pi->refresh_rate);
	WREG32(FVTHROT_CB3, 1000000 * 30 / pi->refresh_rate);
	WREG32(FVTHROT_CB4, 1000000 * 50 / pi->refresh_rate);
पूर्ण

अटल व्योम rs780_disable_vbios_घातersaving(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(CG_INTGFX_MISC, 0, ~0xFFF00000);
पूर्ण

अटल व्योम rs780_क्रमce_voltage(काष्ठा radeon_device *rdev, u16 voltage)
अणु
	काष्ठा igp_ps *current_state = rs780_get_ps(rdev->pm.dpm.current_ps);

	अगर ((current_state->max_voltage == RS780_VDDC_LEVEL_HIGH) &&
	    (current_state->min_voltage == RS780_VDDC_LEVEL_HIGH))
		वापस;

	WREG32_P(GFX_MACRO_BYPASS_CNTL, SPLL_BYPASS_CNTL, ~SPLL_BYPASS_CNTL);

	udelay(1);

	WREG32_P(FVTHROT_PWM_CTRL_REG0,
		 STARTING_PWM_HIGHTIME(voltage),
		 ~STARTING_PWM_HIGHTIME_MASK);

	WREG32_P(FVTHROT_PWM_CTRL_REG0,
		 FORCE_STARTING_PWM_HIGHTIME, ~FORCE_STARTING_PWM_HIGHTIME);

	WREG32_P(FVTHROT_PWM_FEEDBACK_DIV_REG1, 0,
		~RANGE_PWM_FEEDBACK_DIV_EN);

	udelay(1);

	WREG32_P(GFX_MACRO_BYPASS_CNTL, 0, ~SPLL_BYPASS_CNTL);
पूर्ण

अटल व्योम rs780_क्रमce_fbभाग(काष्ठा radeon_device *rdev, u32 fb_भाग)
अणु
	काष्ठा igp_ps *current_state = rs780_get_ps(rdev->pm.dpm.current_ps);

	अगर (current_state->sclk_low == current_state->sclk_high)
		वापस;

	WREG32_P(GFX_MACRO_BYPASS_CNTL, SPLL_BYPASS_CNTL, ~SPLL_BYPASS_CNTL);

	WREG32_P(FVTHROT_FBDIV_REG2, FORCED_FEEDBACK_DIV(fb_भाग),
		 ~FORCED_FEEDBACK_DIV_MASK);
	WREG32_P(FVTHROT_FBDIV_REG1, STARTING_FEEDBACK_DIV(fb_भाग),
		 ~STARTING_FEEDBACK_DIV_MASK);
	WREG32_P(FVTHROT_FBDIV_REG1, FORCE_FEEDBACK_DIV, ~FORCE_FEEDBACK_DIV);

	udelay(100);

	WREG32_P(GFX_MACRO_BYPASS_CNTL, 0, ~SPLL_BYPASS_CNTL);
पूर्ण

अटल पूर्णांक rs780_set_engine_घड़ी_scaling(काष्ठा radeon_device *rdev,
					  काष्ठा radeon_ps *new_ps,
					  काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा atom_घड़ी_भागiders min_भागiders, max_भागiders, current_max_भागiders;
	काष्ठा igp_ps *new_state = rs780_get_ps(new_ps);
	काष्ठा igp_ps *old_state = rs780_get_ps(old_ps);
	पूर्णांक ret;

	अगर ((new_state->sclk_high == old_state->sclk_high) &&
	    (new_state->sclk_low == old_state->sclk_low))
		वापस 0;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     new_state->sclk_low, false, &min_भागiders);
	अगर (ret)
		वापस ret;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     new_state->sclk_high, false, &max_भागiders);
	अगर (ret)
		वापस ret;

	ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     old_state->sclk_high, false, &current_max_भागiders);
	अगर (ret)
		वापस ret;

	अगर ((min_भागiders.ref_भाग != max_भागiders.ref_भाग) ||
	    (min_भागiders.post_भाग != max_भागiders.post_भाग) ||
	    (max_भागiders.ref_भाग != current_max_भागiders.ref_भाग) ||
	    (max_भागiders.post_भाग != current_max_भागiders.post_भाग))
		वापस -EINVAL;

	rs780_क्रमce_fbभाग(rdev, max_भागiders.fb_भाग);

	अगर (max_भागiders.fb_भाग > min_भागiders.fb_भाग) अणु
		WREG32_P(FVTHROT_FBDIV_REG0,
			 MIN_FEEDBACK_DIV(min_भागiders.fb_भाग) |
			 MAX_FEEDBACK_DIV(max_भागiders.fb_भाग),
			 ~(MIN_FEEDBACK_DIV_MASK | MAX_FEEDBACK_DIV_MASK));

		WREG32_P(FVTHROT_FBDIV_REG1, 0, ~FORCE_FEEDBACK_DIV);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rs780_set_engine_घड़ी_spc(काष्ठा radeon_device *rdev,
				       काष्ठा radeon_ps *new_ps,
				       काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा igp_ps *new_state = rs780_get_ps(new_ps);
	काष्ठा igp_ps *old_state = rs780_get_ps(old_ps);
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);

	अगर ((new_state->sclk_high == old_state->sclk_high) &&
	    (new_state->sclk_low == old_state->sclk_low))
		वापस;

	अगर (pi->crtc_id == 0)
		WREG32_P(CG_INTGFX_MISC, 0, ~FVTHROT_VBLANK_SEL);
	अन्यथा
		WREG32_P(CG_INTGFX_MISC, FVTHROT_VBLANK_SEL, ~FVTHROT_VBLANK_SEL);

पूर्ण

अटल व्योम rs780_activate_engine_clk_scaling(काष्ठा radeon_device *rdev,
					      काष्ठा radeon_ps *new_ps,
					      काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा igp_ps *new_state = rs780_get_ps(new_ps);
	काष्ठा igp_ps *old_state = rs780_get_ps(old_ps);

	अगर ((new_state->sclk_high == old_state->sclk_high) &&
	    (new_state->sclk_low == old_state->sclk_low))
		वापस;

	अगर (new_state->sclk_high == new_state->sclk_low)
		वापस;

	rs780_clk_scaling_enable(rdev, true);
पूर्ण

अटल u32 rs780_get_voltage_क्रम_vddc_level(काष्ठा radeon_device *rdev,
					    क्रमागत rs780_vddc_level vddc)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);

	अगर (vddc == RS780_VDDC_LEVEL_HIGH)
		वापस pi->max_voltage;
	अन्यथा अगर (vddc == RS780_VDDC_LEVEL_LOW)
		वापस pi->min_voltage;
	अन्यथा
		वापस pi->max_voltage;
पूर्ण

अटल व्योम rs780_enable_voltage_scaling(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_ps *new_ps)
अणु
	काष्ठा igp_ps *new_state = rs780_get_ps(new_ps);
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);
	क्रमागत rs780_vddc_level vddc_high, vddc_low;

	udelay(100);

	अगर ((new_state->max_voltage == RS780_VDDC_LEVEL_HIGH) &&
	    (new_state->min_voltage == RS780_VDDC_LEVEL_HIGH))
		वापस;

	vddc_high = rs780_get_voltage_क्रम_vddc_level(rdev,
						     new_state->max_voltage);
	vddc_low = rs780_get_voltage_क्रम_vddc_level(rdev,
						    new_state->min_voltage);

	WREG32_P(GFX_MACRO_BYPASS_CNTL, SPLL_BYPASS_CNTL, ~SPLL_BYPASS_CNTL);

	udelay(1);
	अगर (vddc_high > vddc_low) अणु
		WREG32_P(FVTHROT_PWM_FEEDBACK_DIV_REG1,
			 RANGE_PWM_FEEDBACK_DIV_EN, ~RANGE_PWM_FEEDBACK_DIV_EN);

		WREG32_P(FVTHROT_PWM_CTRL_REG0, 0, ~FORCE_STARTING_PWM_HIGHTIME);
	पूर्ण अन्यथा अगर (vddc_high == vddc_low) अणु
		अगर (pi->max_voltage != vddc_high) अणु
			WREG32_P(FVTHROT_PWM_CTRL_REG0,
				 STARTING_PWM_HIGHTIME(vddc_high),
				 ~STARTING_PWM_HIGHTIME_MASK);

			WREG32_P(FVTHROT_PWM_CTRL_REG0,
				 FORCE_STARTING_PWM_HIGHTIME,
				 ~FORCE_STARTING_PWM_HIGHTIME);
		पूर्ण
	पूर्ण

	WREG32_P(GFX_MACRO_BYPASS_CNTL, 0, ~SPLL_BYPASS_CNTL);
पूर्ण

अटल व्योम rs780_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(काष्ठा radeon_device *rdev,
						     काष्ठा radeon_ps *new_ps,
						     काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा igp_ps *new_state = rs780_get_ps(new_ps);
	काष्ठा igp_ps *current_state = rs780_get_ps(old_ps);

	अगर ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		वापस;

	अगर (new_state->sclk_high >= current_state->sclk_high)
		वापस;

	radeon_set_uvd_घड़ीs(rdev, new_ps->vclk, new_ps->dclk);
पूर्ण

अटल व्योम rs780_set_uvd_घड़ी_after_set_eng_घड़ी(काष्ठा radeon_device *rdev,
						    काष्ठा radeon_ps *new_ps,
						    काष्ठा radeon_ps *old_ps)
अणु
	काष्ठा igp_ps *new_state = rs780_get_ps(new_ps);
	काष्ठा igp_ps *current_state = rs780_get_ps(old_ps);

	अगर ((new_ps->vclk == old_ps->vclk) &&
	    (new_ps->dclk == old_ps->dclk))
		वापस;

	अगर (new_state->sclk_high < current_state->sclk_high)
		वापस;

	radeon_set_uvd_घड़ीs(rdev, new_ps->vclk, new_ps->dclk);
पूर्ण

पूर्णांक rs780_dpm_enable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);
	काष्ठा radeon_ps *boot_ps = rdev->pm.dpm.boot_ps;
	पूर्णांक ret;

	rs780_get_pm_mode_parameters(rdev);
	rs780_disable_vbios_घातersaving(rdev);

	अगर (r600_dynamicpm_enabled(rdev))
		वापस -EINVAL;
	ret = rs780_initialize_dpm_parameters(rdev, boot_ps);
	अगर (ret)
		वापस ret;
	rs780_start_dpm(rdev);

	rs780_preset_ranges_slow_clk_fbभाग_en(rdev);
	rs780_preset_starting_fbभाग(rdev);
	अगर (pi->voltage_control)
		rs780_voltage_scaling_init(rdev);
	rs780_clk_scaling_enable(rdev, true);
	rs780_set_engine_घड़ी_sc(rdev);
	rs780_set_engine_घड़ी_wfc(rdev);
	rs780_program_at(rdev);
	rs780_set_engine_घड़ी_प्रकारdc(rdev);
	rs780_set_engine_घड़ी_ssc(rdev);

	अगर (pi->gfx_घड़ी_gating)
		r600_gfx_घड़ीgating_enable(rdev, true);

	वापस 0;
पूर्ण

व्योम rs780_dpm_disable(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);

	r600_dynamicpm_enable(rdev, false);

	rs780_clk_scaling_enable(rdev, false);
	rs780_voltage_scaling_enable(rdev, false);

	अगर (pi->gfx_घड़ी_gating)
		r600_gfx_घड़ीgating_enable(rdev, false);

	अगर (rdev->irq.installed &&
	    (rdev->pm.पूर्णांक_thermal_type == THERMAL_TYPE_RV6XX)) अणु
		rdev->irq.dpm_thermal = false;
		radeon_irq_set(rdev);
	पूर्ण
पूर्ण

पूर्णांक rs780_dpm_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);
	काष्ठा radeon_ps *new_ps = rdev->pm.dpm.requested_ps;
	काष्ठा radeon_ps *old_ps = rdev->pm.dpm.current_ps;
	पूर्णांक ret;

	rs780_get_pm_mode_parameters(rdev);

	rs780_set_uvd_घड़ी_beक्रमe_set_eng_घड़ी(rdev, new_ps, old_ps);

	अगर (pi->voltage_control) अणु
		rs780_क्रमce_voltage(rdev, pi->max_voltage);
		mdelay(5);
	पूर्ण

	ret = rs780_set_engine_घड़ी_scaling(rdev, new_ps, old_ps);
	अगर (ret)
		वापस ret;
	rs780_set_engine_घड़ी_spc(rdev, new_ps, old_ps);

	rs780_activate_engine_clk_scaling(rdev, new_ps, old_ps);

	अगर (pi->voltage_control)
		rs780_enable_voltage_scaling(rdev, new_ps);

	rs780_set_uvd_घड़ी_after_set_eng_घड़ी(rdev, new_ps, old_ps);

	वापस 0;
पूर्ण

व्योम rs780_dpm_setup_asic(काष्ठा radeon_device *rdev)
अणु

पूर्ण

व्योम rs780_dpm_display_configuration_changed(काष्ठा radeon_device *rdev)
अणु
	rs780_get_pm_mode_parameters(rdev);
	rs780_program_at(rdev);
पूर्ण

जोड़ igp_info अणु
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO info;
	काष्ठा _ATOM_INTEGRATED_SYSTEM_INFO_V2 info_2;
पूर्ण;

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

अटल व्योम rs780_parse_pplib_non_घड़ी_info(काष्ठा radeon_device *rdev,
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
			rps->vclk = RS780_DEFAULT_VCLK_FREQ;
			rps->dclk = RS780_DEFAULT_DCLK_FREQ;
		पूर्ण
	पूर्ण

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT)
		rdev->pm.dpm.boot_ps = rps;
	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		rdev->pm.dpm.uvd_ps = rps;
पूर्ण

अटल व्योम rs780_parse_pplib_घड़ी_info(काष्ठा radeon_device *rdev,
					 काष्ठा radeon_ps *rps,
					 जोड़ pplib_घड़ी_info *घड़ी_info)
अणु
	काष्ठा igp_ps *ps = rs780_get_ps(rps);
	u32 sclk;

	sclk = le16_to_cpu(घड़ी_info->rs780.usLowEngineClockLow);
	sclk |= घड़ी_info->rs780.ucLowEngineClockHigh << 16;
	ps->sclk_low = sclk;
	sclk = le16_to_cpu(घड़ी_info->rs780.usHighEngineClockLow);
	sclk |= घड़ी_info->rs780.ucHighEngineClockHigh << 16;
	ps->sclk_high = sclk;
	चयन (le16_to_cpu(घड़ी_info->rs780.usVDDC)) अणु
	हाल ATOM_PPLIB_RS780_VOLTAGE_NONE:
	शेष:
		ps->min_voltage = RS780_VDDC_LEVEL_UNKNOWN;
		ps->max_voltage = RS780_VDDC_LEVEL_UNKNOWN;
		अवरोध;
	हाल ATOM_PPLIB_RS780_VOLTAGE_LOW:
		ps->min_voltage = RS780_VDDC_LEVEL_LOW;
		ps->max_voltage = RS780_VDDC_LEVEL_LOW;
		अवरोध;
	हाल ATOM_PPLIB_RS780_VOLTAGE_HIGH:
		ps->min_voltage = RS780_VDDC_LEVEL_HIGH;
		ps->max_voltage = RS780_VDDC_LEVEL_HIGH;
		अवरोध;
	हाल ATOM_PPLIB_RS780_VOLTAGE_VARIABLE:
		ps->min_voltage = RS780_VDDC_LEVEL_LOW;
		ps->max_voltage = RS780_VDDC_LEVEL_HIGH;
		अवरोध;
	पूर्ण
	ps->flags = le32_to_cpu(घड़ी_info->rs780.ulFlags);

	अगर (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) अणु
		ps->sclk_low = rdev->घड़ी.शेष_sclk;
		ps->sclk_high = rdev->घड़ी.शेष_sclk;
		ps->min_voltage = RS780_VDDC_LEVEL_HIGH;
		ps->max_voltage = RS780_VDDC_LEVEL_HIGH;
	पूर्ण
पूर्ण

अटल पूर्णांक rs780_parse_घातer_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	काष्ठा _ATOM_PPLIB_NONCLOCK_INFO *non_घड़ी_info;
	जोड़ pplib_घातer_state *घातer_state;
	पूर्णांक i;
	जोड़ pplib_घड़ी_info *घड़ी_info;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	काष्ठा igp_ps *ps;

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
			घड़ी_info = (जोड़ pplib_घड़ी_info *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib.usClockInfoArrayOffset) +
				 (घातer_state->v1.ucClockStateIndices[0] *
				  घातer_info->pplib.ucClockInfoSize));
			ps = kzalloc(माप(काष्ठा igp_ps), GFP_KERNEL);
			अगर (ps == शून्य) अणु
				kमुक्त(rdev->pm.dpm.ps);
				वापस -ENOMEM;
			पूर्ण
			rdev->pm.dpm.ps[i].ps_priv = ps;
			rs780_parse_pplib_non_घड़ी_info(rdev, &rdev->pm.dpm.ps[i],
							 non_घड़ी_info,
							 घातer_info->pplib.ucNonClockSize);
			rs780_parse_pplib_घड़ी_info(rdev,
						     &rdev->pm.dpm.ps[i],
						     घड़ी_info);
		पूर्ण
	पूर्ण
	rdev->pm.dpm.num_ps = घातer_info->pplib.ucNumStates;
	वापस 0;
पूर्ण

पूर्णांक rs780_dpm_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, IntegratedSystemInfo);
	जोड़ igp_info *info;
	u16 data_offset;
	u8 frev, crev;
	पूर्णांक ret;

	pi = kzalloc(माप(काष्ठा igp_घातer_info), GFP_KERNEL);
	अगर (pi == शून्य)
		वापस -ENOMEM;
	rdev->pm.dpm.priv = pi;

	ret = r600_get_platक्रमm_caps(rdev);
	अगर (ret)
		वापस ret;

	ret = rs780_parse_घातer_table(rdev);
	अगर (ret)
		वापस ret;

	pi->voltage_control = false;
	pi->gfx_घड़ी_gating = true;

	अगर (atom_parse_data_header(rdev->mode_info.atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		info = (जोड़ igp_info *)(rdev->mode_info.atom_context->bios + data_offset);

		/* Get various प्रणाली inक्रमmations from bios */
		चयन (crev) अणु
		हाल 1:
			pi->num_of_cycles_in_period =
				info->info.ucNumberOfCyclesInPeriod;
			pi->num_of_cycles_in_period |=
				info->info.ucNumberOfCyclesInPeriodHi << 8;
			pi->invert_pwm_required =
				(pi->num_of_cycles_in_period & 0x8000) ? true : false;
			pi->boot_voltage = info->info.ucStartingPWM_HighTime;
			pi->max_voltage = info->info.ucMaxNBVoltage;
			pi->max_voltage |= info->info.ucMaxNBVoltageHigh << 8;
			pi->min_voltage = info->info.ucMinNBVoltage;
			pi->min_voltage |= info->info.ucMinNBVoltageHigh << 8;
			pi->पूर्णांकer_voltage_low =
				le16_to_cpu(info->info.usInterNBVoltageLow);
			pi->पूर्णांकer_voltage_high =
				le16_to_cpu(info->info.usInterNBVoltageHigh);
			pi->voltage_control = true;
			pi->bootup_uma_clk = info->info.usK8MemoryClock * 100;
			अवरोध;
		हाल 2:
			pi->num_of_cycles_in_period =
				le16_to_cpu(info->info_2.usNumberOfCyclesInPeriod);
			pi->invert_pwm_required =
				(pi->num_of_cycles_in_period & 0x8000) ? true : false;
			pi->boot_voltage =
				le16_to_cpu(info->info_2.usBootUpNBVoltage);
			pi->max_voltage =
				le16_to_cpu(info->info_2.usMaxNBVoltage);
			pi->min_voltage =
				le16_to_cpu(info->info_2.usMinNBVoltage);
			pi->प्रणाली_config =
				le32_to_cpu(info->info_2.ulSystemConfig);
			pi->pwm_voltage_control =
				(pi->प्रणाली_config & 0x4) ? true : false;
			pi->voltage_control = true;
			pi->bootup_uma_clk = le32_to_cpu(info->info_2.ulBootUpUMAClock);
			अवरोध;
		शेष:
			DRM_ERROR("No integrated system info for your GPU\n");
			वापस -EINVAL;
		पूर्ण
		अगर (pi->min_voltage > pi->max_voltage)
			pi->voltage_control = false;
		अगर (pi->pwm_voltage_control) अणु
			अगर ((pi->num_of_cycles_in_period == 0) ||
			    (pi->max_voltage == 0) ||
			    (pi->min_voltage == 0))
				pi->voltage_control = false;
		पूर्ण अन्यथा अणु
			अगर ((pi->num_of_cycles_in_period == 0) ||
			    (pi->max_voltage == 0))
				pi->voltage_control = false;
		पूर्ण

		वापस 0;
	पूर्ण
	radeon_dpm_fini(rdev);
	वापस -EINVAL;
पूर्ण

व्योम rs780_dpm_prपूर्णांक_घातer_state(काष्ठा radeon_device *rdev,
				 काष्ठा radeon_ps *rps)
अणु
	काष्ठा igp_ps *ps = rs780_get_ps(rps);

	r600_dpm_prपूर्णांक_class_info(rps->class, rps->class2);
	r600_dpm_prपूर्णांक_cap_info(rps->caps);
	prपूर्णांकk("\tuvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);
	prपूर्णांकk("\t\tpower level 0    sclk: %u vddc_index: %d\n",
	       ps->sclk_low, ps->min_voltage);
	prपूर्णांकk("\t\tpower level 1    sclk: %u vddc_index: %d\n",
	       ps->sclk_high, ps->max_voltage);
	r600_dpm_prपूर्णांक_ps_status(rdev, rps);
पूर्ण

व्योम rs780_dpm_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->pm.dpm.num_ps; i++) अणु
		kमुक्त(rdev->pm.dpm.ps[i].ps_priv);
	पूर्ण
	kमुक्त(rdev->pm.dpm.ps);
	kमुक्त(rdev->pm.dpm.priv);
पूर्ण

u32 rs780_dpm_get_sclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा igp_ps *requested_state = rs780_get_ps(rdev->pm.dpm.requested_ps);

	अगर (low)
		वापस requested_state->sclk_low;
	अन्यथा
		वापस requested_state->sclk_high;
पूर्ण

u32 rs780_dpm_get_mclk(काष्ठा radeon_device *rdev, bool low)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);

	वापस pi->bootup_uma_clk;
पूर्ण

व्योम rs780_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(काष्ठा radeon_device *rdev,
						       काष्ठा seq_file *m)
अणु
	काष्ठा radeon_ps *rps = rdev->pm.dpm.current_ps;
	काष्ठा igp_ps *ps = rs780_get_ps(rps);
	u32 current_fb_भाग = RREG32(FVTHROT_STATUS_REG0) & CURRENT_FEEDBACK_DIV_MASK;
	u32 func_cntl = RREG32(CG_SPLL_FUNC_CNTL);
	u32 ref_भाग = ((func_cntl & SPLL_REF_DIV_MASK) >> SPLL_REF_DIV_SHIFT) + 1;
	u32 post_भाग = ((func_cntl & SPLL_SW_HILEN_MASK) >> SPLL_SW_HILEN_SHIFT) + 1 +
		((func_cntl & SPLL_SW_LOLEN_MASK) >> SPLL_SW_LOLEN_SHIFT) + 1;
	u32 sclk = (rdev->घड़ी.spll.reference_freq * current_fb_भाग) /
		(post_भाग * ref_भाग);

	seq_म_लिखो(m, "uvd    vclk: %d dclk: %d\n", rps->vclk, rps->dclk);

	/* guess based on the current sclk */
	अगर (sclk < (ps->sclk_low + 500))
		seq_म_लिखो(m, "power level 0    sclk: %u vddc_index: %d\n",
			   ps->sclk_low, ps->min_voltage);
	अन्यथा
		seq_म_लिखो(m, "power level 1    sclk: %u vddc_index: %d\n",
			   ps->sclk_high, ps->max_voltage);
पूर्ण

/* get the current sclk in 10 khz units */
u32 rs780_dpm_get_current_sclk(काष्ठा radeon_device *rdev)
अणु
	u32 current_fb_भाग = RREG32(FVTHROT_STATUS_REG0) & CURRENT_FEEDBACK_DIV_MASK;
	u32 func_cntl = RREG32(CG_SPLL_FUNC_CNTL);
	u32 ref_भाग = ((func_cntl & SPLL_REF_DIV_MASK) >> SPLL_REF_DIV_SHIFT) + 1;
	u32 post_भाग = ((func_cntl & SPLL_SW_HILEN_MASK) >> SPLL_SW_HILEN_SHIFT) + 1 +
		((func_cntl & SPLL_SW_LOLEN_MASK) >> SPLL_SW_LOLEN_SHIFT) + 1;
	u32 sclk = (rdev->घड़ी.spll.reference_freq * current_fb_भाग) /
		(post_भाग * ref_भाग);

	वापस sclk;
पूर्ण

/* get the current mclk in 10 khz units */
u32 rs780_dpm_get_current_mclk(काष्ठा radeon_device *rdev)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);

	वापस pi->bootup_uma_clk;
पूर्ण

पूर्णांक rs780_dpm_क्रमce_perक्रमmance_level(काष्ठा radeon_device *rdev,
				      क्रमागत radeon_dpm_क्रमced_level level)
अणु
	काष्ठा igp_घातer_info *pi = rs780_get_pi(rdev);
	काष्ठा radeon_ps *rps = rdev->pm.dpm.current_ps;
	काष्ठा igp_ps *ps = rs780_get_ps(rps);
	काष्ठा atom_घड़ी_भागiders भागiders;
	पूर्णांक ret;

	rs780_clk_scaling_enable(rdev, false);
	rs780_voltage_scaling_enable(rdev, false);

	अगर (level == RADEON_DPM_FORCED_LEVEL_HIGH) अणु
		अगर (pi->voltage_control)
			rs780_क्रमce_voltage(rdev, pi->max_voltage);

		ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
						     ps->sclk_high, false, &भागiders);
		अगर (ret)
			वापस ret;

		rs780_क्रमce_fbभाग(rdev, भागiders.fb_भाग);
	पूर्ण अन्यथा अगर (level == RADEON_DPM_FORCED_LEVEL_LOW) अणु
		ret = radeon_atom_get_घड़ी_भागiders(rdev, COMPUTE_ENGINE_PLL_PARAM,
						     ps->sclk_low, false, &भागiders);
		अगर (ret)
			वापस ret;

		rs780_क्रमce_fbभाग(rdev, भागiders.fb_भाग);

		अगर (pi->voltage_control)
			rs780_क्रमce_voltage(rdev, pi->min_voltage);
	पूर्ण अन्यथा अणु
		अगर (pi->voltage_control)
			rs780_क्रमce_voltage(rdev, pi->max_voltage);

		अगर (ps->sclk_high != ps->sclk_low) अणु
			WREG32_P(FVTHROT_FBDIV_REG1, 0, ~FORCE_FEEDBACK_DIV);
			rs780_clk_scaling_enable(rdev, true);
		पूर्ण

		अगर (pi->voltage_control) अणु
			rs780_voltage_scaling_enable(rdev, true);
			rs780_enable_voltage_scaling(rdev, rps);
		पूर्ण
	पूर्ण

	rdev->pm.dpm.क्रमced_level = level;

	वापस 0;
पूर्ण
