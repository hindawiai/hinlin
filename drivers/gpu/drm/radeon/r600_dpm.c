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
#समावेश "r600d.h"
#समावेश "r600_dpm.h"
#समावेश "atom.h"

स्थिर u32 r600_utc[R600_PM_NUMBER_OF_TC] =
अणु
	R600_UTC_DFLT_00,
	R600_UTC_DFLT_01,
	R600_UTC_DFLT_02,
	R600_UTC_DFLT_03,
	R600_UTC_DFLT_04,
	R600_UTC_DFLT_05,
	R600_UTC_DFLT_06,
	R600_UTC_DFLT_07,
	R600_UTC_DFLT_08,
	R600_UTC_DFLT_09,
	R600_UTC_DFLT_10,
	R600_UTC_DFLT_11,
	R600_UTC_DFLT_12,
	R600_UTC_DFLT_13,
	R600_UTC_DFLT_14,
पूर्ण;

स्थिर u32 r600_dtc[R600_PM_NUMBER_OF_TC] =
अणु
	R600_DTC_DFLT_00,
	R600_DTC_DFLT_01,
	R600_DTC_DFLT_02,
	R600_DTC_DFLT_03,
	R600_DTC_DFLT_04,
	R600_DTC_DFLT_05,
	R600_DTC_DFLT_06,
	R600_DTC_DFLT_07,
	R600_DTC_DFLT_08,
	R600_DTC_DFLT_09,
	R600_DTC_DFLT_10,
	R600_DTC_DFLT_11,
	R600_DTC_DFLT_12,
	R600_DTC_DFLT_13,
	R600_DTC_DFLT_14,
पूर्ण;

व्योम r600_dpm_prपूर्णांक_class_info(u32 class, u32 class2)
अणु
	स्थिर अक्षर *s;

	चयन (class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) अणु
	हाल ATOM_PPLIB_CLASSIFICATION_UI_NONE:
	शेष:
		s = "none";
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_BATTERY:
		s = "battery";
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_BALANCED:
		s = "balanced";
		अवरोध;
	हाल ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE:
		s = "performance";
		अवरोध;
	पूर्ण
	prपूर्णांकk("\tui class: %s\n", s);

	prपूर्णांकk("\tinternal class:");
	अगर (((class & ~ATOM_PPLIB_CLASSIFICATION_UI_MASK) == 0) &&
	    (class2 == 0))
		pr_cont(" none");
	अन्यथा अणु
		अगर (class & ATOM_PPLIB_CLASSIFICATION_BOOT)
			pr_cont(" boot");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
			pr_cont(" thermal");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE)
			pr_cont(" limited_pwr");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_REST)
			pr_cont(" rest");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_FORCED)
			pr_cont(" forced");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
			pr_cont(" 3d_perf");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_OVERDRIVETEMPLATE)
			pr_cont(" ovrdrv");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
			pr_cont(" uvd");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_3DLOW)
			pr_cont(" 3d_low");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_ACPI)
			pr_cont(" acpi");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
			pr_cont(" uvd_hd2");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
			pr_cont(" uvd_hd");
		अगर (class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
			pr_cont(" uvd_sd");
		अगर (class2 & ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2)
			pr_cont(" limited_pwr2");
		अगर (class2 & ATOM_PPLIB_CLASSIFICATION2_ULV)
			pr_cont(" ulv");
		अगर (class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
			pr_cont(" uvd_mvc");
	पूर्ण
	pr_cont("\n");
पूर्ण

व्योम r600_dpm_prपूर्णांक_cap_info(u32 caps)
अणु
	prपूर्णांकk("\tcaps:");
	अगर (caps & ATOM_PPLIB_SINGLE_DISPLAY_ONLY)
		pr_cont(" single_disp");
	अगर (caps & ATOM_PPLIB_SUPPORTS_VIDEO_PLAYBACK)
		pr_cont(" video");
	अगर (caps & ATOM_PPLIB_DISALLOW_ON_DC)
		pr_cont(" no_dc");
	pr_cont("\n");
पूर्ण

व्योम r600_dpm_prपूर्णांक_ps_status(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ps *rps)
अणु
	prपूर्णांकk("\tstatus:");
	अगर (rps == rdev->pm.dpm.current_ps)
		pr_cont(" c");
	अगर (rps == rdev->pm.dpm.requested_ps)
		pr_cont(" r");
	अगर (rps == rdev->pm.dpm.boot_ps)
		pr_cont(" b");
	pr_cont("\n");
पूर्ण

u32 r600_dpm_get_vblank_समय(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	u32 vblank_in_pixels;
	u32 vblank_समय_us = 0xffffffff; /* अगर the displays are off, vblank समय is max */

	अगर (rdev->num_crtc && rdev->mode_info.mode_config_initialized) अणु
		list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
			radeon_crtc = to_radeon_crtc(crtc);
			अगर (crtc->enabled && radeon_crtc->enabled && radeon_crtc->hw_mode.घड़ी) अणु
				vblank_in_pixels =
					radeon_crtc->hw_mode.crtc_htotal *
					(radeon_crtc->hw_mode.crtc_vblank_end -
					 radeon_crtc->hw_mode.crtc_vdisplay +
					 (radeon_crtc->v_border * 2));

				vblank_समय_us = vblank_in_pixels * 1000 / radeon_crtc->hw_mode.घड़ी;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस vblank_समय_us;
पूर्ण

u32 r600_dpm_get_vrefresh(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	u32 vrefresh = 0;

	अगर (rdev->num_crtc && rdev->mode_info.mode_config_initialized) अणु
		list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
			radeon_crtc = to_radeon_crtc(crtc);
			अगर (crtc->enabled && radeon_crtc->enabled && radeon_crtc->hw_mode.घड़ी) अणु
				vrefresh = drm_mode_vrefresh(&radeon_crtc->hw_mode);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस vrefresh;
पूर्ण

व्योम r600_calculate_u_and_p(u32 i, u32 r_c, u32 p_b,
			    u32 *p, u32 *u)
अणु
	u32 b_c = 0;
	u32 i_c;
	u32 पंचांगp;

	i_c = (i * r_c) / 100;
	पंचांगp = i_c >> p_b;

	जबतक (पंचांगp) अणु
		b_c++;
		पंचांगp >>= 1;
	पूर्ण

	*u = (b_c + 1) / 2;
	*p = i_c / (1 << (2 * (*u)));
पूर्ण

पूर्णांक r600_calculate_at(u32 t, u32 h, u32 fh, u32 fl, u32 *tl, u32 *th)
अणु
	u32 k, a, ah, al;
	u32 t1;

	अगर ((fl == 0) || (fh == 0) || (fl > fh))
		वापस -EINVAL;

	k = (100 * fh) / fl;
	t1 = (t * (k - 100));
	a = (1000 * (100 * h + t1)) / (10000 + (t1 / 100));
	a = (a + 5) / 10;
	ah = ((a * t) + 5000) / 10000;
	al = a - ah;

	*th = t - ah;
	*tl = t + al;

	वापस 0;
पूर्ण

व्योम r600_gfx_घड़ीgating_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	पूर्णांक i;

	अगर (enable) अणु
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);
	पूर्ण अन्यथा अणु
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);

		WREG32(CG_RLC_REQ_AND_RSP, 0x2);

		क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
			अगर (((RREG32(CG_RLC_REQ_AND_RSP) & CG_RLC_RSP_TYPE_MASK) >> CG_RLC_RSP_TYPE_SHIFT) == 1)
				अवरोध;
			udelay(1);
		पूर्ण

		WREG32(CG_RLC_REQ_AND_RSP, 0x0);

		WREG32(GRBM_PWR_CNTL, 0x1);
		RREG32(GRBM_PWR_CNTL);
	पूर्ण
पूर्ण

व्योम r600_dynamicpm_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, GLOBAL_PWRMGT_EN, ~GLOBAL_PWRMGT_EN);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~GLOBAL_PWRMGT_EN);
पूर्ण

व्योम r600_enable_thermal_protection(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, 0, ~THERMAL_PROTECTION_DIS);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, THERMAL_PROTECTION_DIS, ~THERMAL_PROTECTION_DIS);
पूर्ण

व्योम r600_enable_acpi_pm(काष्ठा radeon_device *rdev)
अणु
	WREG32_P(GENERAL_PWRMGT, STATIC_PM_EN, ~STATIC_PM_EN);
पूर्ण

व्योम r600_enable_dynamic_pcie_gen2(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(GENERAL_PWRMGT, ENABLE_GEN2PCIE, ~ENABLE_GEN2PCIE);
	अन्यथा
		WREG32_P(GENERAL_PWRMGT, 0, ~ENABLE_GEN2PCIE);
पूर्ण

bool r600_dynamicpm_enabled(काष्ठा radeon_device *rdev)
अणु
	अगर (RREG32(GENERAL_PWRMGT) & GLOBAL_PWRMGT_EN)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

व्योम r600_enable_sclk_control(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~SCLK_PWRMGT_OFF);
	अन्यथा
		WREG32_P(SCLK_PWRMGT_CNTL, SCLK_PWRMGT_OFF, ~SCLK_PWRMGT_OFF);
पूर्ण

व्योम r600_enable_mclk_control(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(MCLK_PWRMGT_CNTL, 0, ~MPLL_PWRMGT_OFF);
	अन्यथा
		WREG32_P(MCLK_PWRMGT_CNTL, MPLL_PWRMGT_OFF, ~MPLL_PWRMGT_OFF);
पूर्ण

व्योम r600_enable_spll_bypass(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_P(CG_SPLL_FUNC_CNTL, SPLL_BYPASS_EN, ~SPLL_BYPASS_EN);
	अन्यथा
		WREG32_P(CG_SPLL_FUNC_CNTL, 0, ~SPLL_BYPASS_EN);
पूर्ण

व्योम r600_रुको_क्रम_spll_change(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(CG_SPLL_FUNC_CNTL) & SPLL_CHG_STATUS)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

व्योम r600_set_bsp(काष्ठा radeon_device *rdev, u32 u, u32 p)
अणु
	WREG32(CG_BSP, BSP(p) | BSU(u));
पूर्ण

व्योम r600_set_at(काष्ठा radeon_device *rdev,
		 u32 l_to_m, u32 m_to_h,
		 u32 h_to_m, u32 m_to_l)
अणु
	WREG32(CG_RT, FLS(l_to_m) | FMS(m_to_h));
	WREG32(CG_LT, FHS(h_to_m) | FMS(m_to_l));
पूर्ण

व्योम r600_set_tc(काष्ठा radeon_device *rdev,
		 u32 index, u32 u_t, u32 d_t)
अणु
	WREG32(CG_FFCT_0 + (index * 4), UTC_0(u_t) | DTC_0(d_t));
पूर्ण

व्योम r600_select_td(काष्ठा radeon_device *rdev,
		    क्रमागत r600_td td)
अणु
	अगर (td == R600_TD_AUTO)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_FORCE_TREND_SEL);
	अन्यथा
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_FORCE_TREND_SEL, ~FIR_FORCE_TREND_SEL);
	अगर (td == R600_TD_UP)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_TREND_MODE);
	अगर (td == R600_TD_DOWN)
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_TREND_MODE, ~FIR_TREND_MODE);
पूर्ण

व्योम r600_set_vrc(काष्ठा radeon_device *rdev, u32 vrv)
अणु
	WREG32(CG_FTV, vrv);
पूर्ण

व्योम r600_set_tpu(काष्ठा radeon_device *rdev, u32 u)
अणु
	WREG32_P(CG_TPC, TPU(u), ~TPU_MASK);
पूर्ण

व्योम r600_set_tpc(काष्ठा radeon_device *rdev, u32 c)
अणु
	WREG32_P(CG_TPC, TPCC(c), ~TPCC_MASK);
पूर्ण

व्योम r600_set_sstu(काष्ठा radeon_device *rdev, u32 u)
अणु
	WREG32_P(CG_SSP, CG_SSTU(u), ~CG_SSTU_MASK);
पूर्ण

व्योम r600_set_sst(काष्ठा radeon_device *rdev, u32 t)
अणु
	WREG32_P(CG_SSP, CG_SST(t), ~CG_SST_MASK);
पूर्ण

व्योम r600_set_git(काष्ठा radeon_device *rdev, u32 t)
अणु
	WREG32_P(CG_GIT, CG_GICST(t), ~CG_GICST_MASK);
पूर्ण

व्योम r600_set_fctu(काष्ठा radeon_device *rdev, u32 u)
अणु
	WREG32_P(CG_FC_T, FC_TU(u), ~FC_TU_MASK);
पूर्ण

व्योम r600_set_fct(काष्ठा radeon_device *rdev, u32 t)
अणु
	WREG32_P(CG_FC_T, FC_T(t), ~FC_T_MASK);
पूर्ण

व्योम r600_set_ctxcgtt3d_rphc(काष्ठा radeon_device *rdev, u32 p)
अणु
	WREG32_P(CG_CTX_CGTT3D_R, PHC(p), ~PHC_MASK);
पूर्ण

व्योम r600_set_ctxcgtt3d_rsdc(काष्ठा radeon_device *rdev, u32 s)
अणु
	WREG32_P(CG_CTX_CGTT3D_R, SDC(s), ~SDC_MASK);
पूर्ण

व्योम r600_set_vddc3d_oorsu(काष्ठा radeon_device *rdev, u32 u)
अणु
	WREG32_P(CG_VDDC3D_OOR, SU(u), ~SU_MASK);
पूर्ण

व्योम r600_set_vddc3d_oorphc(काष्ठा radeon_device *rdev, u32 p)
अणु
	WREG32_P(CG_VDDC3D_OOR, PHC(p), ~PHC_MASK);
पूर्ण

व्योम r600_set_vddc3d_oorsdc(काष्ठा radeon_device *rdev, u32 s)
अणु
	WREG32_P(CG_VDDC3D_OOR, SDC(s), ~SDC_MASK);
पूर्ण

व्योम r600_set_mpll_lock_समय(काष्ठा radeon_device *rdev, u32 lock_समय)
अणु
	WREG32_P(MPLL_TIME, MPLL_LOCK_TIME(lock_समय), ~MPLL_LOCK_TIME_MASK);
पूर्ण

व्योम r600_set_mpll_reset_समय(काष्ठा radeon_device *rdev, u32 reset_समय)
अणु
	WREG32_P(MPLL_TIME, MPLL_RESET_TIME(reset_समय), ~MPLL_RESET_TIME_MASK);
पूर्ण

व्योम r600_engine_घड़ी_entry_enable(काष्ठा radeon_device *rdev,
				    u32 index, bool enable)
अणु
	अगर (enable)
		WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART2 + (index * 4 * 2),
			 STEP_0_SPLL_ENTRY_VALID, ~STEP_0_SPLL_ENTRY_VALID);
	अन्यथा
		WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART2 + (index * 4 * 2),
			 0, ~STEP_0_SPLL_ENTRY_VALID);
पूर्ण

व्योम r600_engine_घड़ी_entry_enable_pulse_skipping(काष्ठा radeon_device *rdev,
						   u32 index, bool enable)
अणु
	अगर (enable)
		WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART2 + (index * 4 * 2),
			 STEP_0_SPLL_STEP_ENABLE, ~STEP_0_SPLL_STEP_ENABLE);
	अन्यथा
		WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART2 + (index * 4 * 2),
			 0, ~STEP_0_SPLL_STEP_ENABLE);
पूर्ण

व्योम r600_engine_घड़ी_entry_enable_post_भागider(काष्ठा radeon_device *rdev,
						 u32 index, bool enable)
अणु
	अगर (enable)
		WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART2 + (index * 4 * 2),
			 STEP_0_POST_DIV_EN, ~STEP_0_POST_DIV_EN);
	अन्यथा
		WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART2 + (index * 4 * 2),
			 0, ~STEP_0_POST_DIV_EN);
पूर्ण

व्योम r600_engine_घड़ी_entry_set_post_भागider(काष्ठा radeon_device *rdev,
					      u32 index, u32 भागider)
अणु
	WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART1 + (index * 4 * 2),
		 STEP_0_SPLL_POST_DIV(भागider), ~STEP_0_SPLL_POST_DIV_MASK);
पूर्ण

व्योम r600_engine_घड़ी_entry_set_reference_भागider(काष्ठा radeon_device *rdev,
						   u32 index, u32 भागider)
अणु
	WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART1 + (index * 4 * 2),
		 STEP_0_SPLL_REF_DIV(भागider), ~STEP_0_SPLL_REF_DIV_MASK);
पूर्ण

व्योम r600_engine_घड़ी_entry_set_feedback_भागider(काष्ठा radeon_device *rdev,
						  u32 index, u32 भागider)
अणु
	WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART1 + (index * 4 * 2),
		 STEP_0_SPLL_FB_DIV(भागider), ~STEP_0_SPLL_FB_DIV_MASK);
पूर्ण

व्योम r600_engine_घड़ी_entry_set_step_समय(काष्ठा radeon_device *rdev,
					   u32 index, u32 step_समय)
अणु
	WREG32_P(SCLK_FREQ_SETTING_STEP_0_PART1 + (index * 4 * 2),
		 STEP_0_SPLL_STEP_TIME(step_समय), ~STEP_0_SPLL_STEP_TIME_MASK);
पूर्ण

व्योम r600_vid_rt_set_ssu(काष्ठा radeon_device *rdev, u32 u)
अणु
	WREG32_P(VID_RT, SSTU(u), ~SSTU_MASK);
पूर्ण

व्योम r600_vid_rt_set_vru(काष्ठा radeon_device *rdev, u32 u)
अणु
	WREG32_P(VID_RT, VID_CRTU(u), ~VID_CRTU_MASK);
पूर्ण

व्योम r600_vid_rt_set_vrt(काष्ठा radeon_device *rdev, u32 rt)
अणु
	WREG32_P(VID_RT, VID_CRT(rt), ~VID_CRT_MASK);
पूर्ण

व्योम r600_voltage_control_enable_pins(काष्ठा radeon_device *rdev,
				      u64 mask)
अणु
	WREG32(LOWER_GPIO_ENABLE, mask & 0xffffffff);
	WREG32(UPPER_GPIO_ENABLE, upper_32_bits(mask));
पूर्ण


व्योम r600_voltage_control_program_voltages(काष्ठा radeon_device *rdev,
					   क्रमागत r600_घातer_level index, u64 pins)
अणु
	u32 पंचांगp, mask;
	u32 ix = 3 - (3 & index);

	WREG32(CTXSW_VID_LOWER_GPIO_CNTL + (ix * 4), pins & 0xffffffff);

	mask = 7 << (3 * ix);
	पंचांगp = RREG32(VID_UPPER_GPIO_CNTL);
	पंचांगp = (पंचांगp & ~mask) | ((pins >> (32 - (3 * ix))) & mask);
	WREG32(VID_UPPER_GPIO_CNTL, पंचांगp);
पूर्ण

व्योम r600_voltage_control_deactivate_अटल_control(काष्ठा radeon_device *rdev,
						    u64 mask)
अणु
	u32 gpio;

	gpio = RREG32(GPIOPAD_MASK);
	gpio &= ~mask;
	WREG32(GPIOPAD_MASK, gpio);

	gpio = RREG32(GPIOPAD_EN);
	gpio &= ~mask;
	WREG32(GPIOPAD_EN, gpio);

	gpio = RREG32(GPIOPAD_A);
	gpio &= ~mask;
	WREG32(GPIOPAD_A, gpio);
पूर्ण

व्योम r600_घातer_level_enable(काष्ठा radeon_device *rdev,
			     क्रमागत r600_घातer_level index, bool enable)
अणु
	u32 ix = 3 - (3 & index);

	अगर (enable)
		WREG32_P(CTXSW_PROखाता_INDEX + (ix * 4), CTXSW_FREQ_STATE_ENABLE,
			 ~CTXSW_FREQ_STATE_ENABLE);
	अन्यथा
		WREG32_P(CTXSW_PROखाता_INDEX + (ix * 4), 0,
			 ~CTXSW_FREQ_STATE_ENABLE);
पूर्ण

व्योम r600_घातer_level_set_voltage_index(काष्ठा radeon_device *rdev,
					क्रमागत r600_घातer_level index, u32 voltage_index)
अणु
	u32 ix = 3 - (3 & index);

	WREG32_P(CTXSW_PROखाता_INDEX + (ix * 4),
		 CTXSW_FREQ_VIDS_CFG_INDEX(voltage_index), ~CTXSW_FREQ_VIDS_CFG_INDEX_MASK);
पूर्ण

व्योम r600_घातer_level_set_mem_घड़ी_index(काष्ठा radeon_device *rdev,
					  क्रमागत r600_घातer_level index, u32 mem_घड़ी_index)
अणु
	u32 ix = 3 - (3 & index);

	WREG32_P(CTXSW_PROखाता_INDEX + (ix * 4),
		 CTXSW_FREQ_MCLK_CFG_INDEX(mem_घड़ी_index), ~CTXSW_FREQ_MCLK_CFG_INDEX_MASK);
पूर्ण

व्योम r600_घातer_level_set_eng_घड़ी_index(काष्ठा radeon_device *rdev,
					  क्रमागत r600_घातer_level index, u32 eng_घड़ी_index)
अणु
	u32 ix = 3 - (3 & index);

	WREG32_P(CTXSW_PROखाता_INDEX + (ix * 4),
		 CTXSW_FREQ_SCLK_CFG_INDEX(eng_घड़ी_index), ~CTXSW_FREQ_SCLK_CFG_INDEX_MASK);
पूर्ण

व्योम r600_घातer_level_set_watermark_id(काष्ठा radeon_device *rdev,
				       क्रमागत r600_घातer_level index,
				       क्रमागत r600_display_watermark watermark_id)
अणु
	u32 ix = 3 - (3 & index);
	u32 पंचांगp = 0;

	अगर (watermark_id == R600_DISPLAY_WATERMARK_HIGH)
		पंचांगp = CTXSW_FREQ_DISPLAY_WATERMARK;
	WREG32_P(CTXSW_PROखाता_INDEX + (ix * 4), पंचांगp, ~CTXSW_FREQ_DISPLAY_WATERMARK);
पूर्ण

व्योम r600_घातer_level_set_pcie_gen2(काष्ठा radeon_device *rdev,
				    क्रमागत r600_घातer_level index, bool compatible)
अणु
	u32 ix = 3 - (3 & index);
	u32 पंचांगp = 0;

	अगर (compatible)
		पंचांगp = CTXSW_FREQ_GEN2PCIE_VOLT;
	WREG32_P(CTXSW_PROखाता_INDEX + (ix * 4), पंचांगp, ~CTXSW_FREQ_GEN2PCIE_VOLT);
पूर्ण

क्रमागत r600_घातer_level r600_घातer_level_get_current_index(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & CURRENT_PROखाता_INDEX_MASK;
	पंचांगp >>= CURRENT_PROखाता_INDEX_SHIFT;
	वापस पंचांगp;
पूर्ण

क्रमागत r600_घातer_level r600_घातer_level_get_target_index(काष्ठा radeon_device *rdev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(TARGET_AND_CURRENT_PROखाता_INDEX) & TARGET_PROखाता_INDEX_MASK;
	पंचांगp >>= TARGET_PROखाता_INDEX_SHIFT;
	वापस पंचांगp;
पूर्ण

व्योम r600_घातer_level_set_enter_index(काष्ठा radeon_device *rdev,
				      क्रमागत r600_घातer_level index)
अणु
	WREG32_P(TARGET_AND_CURRENT_PROखाता_INDEX, DYN_PWR_ENTER_INDEX(index),
		 ~DYN_PWR_ENTER_INDEX_MASK);
पूर्ण

व्योम r600_रुको_क्रम_घातer_level_unequal(काष्ठा radeon_device *rdev,
				       क्रमागत r600_घातer_level index)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (r600_घातer_level_get_target_index(rdev) != index)
			अवरोध;
		udelay(1);
	पूर्ण

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (r600_घातer_level_get_current_index(rdev) != index)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

व्योम r600_रुको_क्रम_घातer_level(काष्ठा radeon_device *rdev,
			       क्रमागत r600_घातer_level index)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (r600_घातer_level_get_target_index(rdev) == index)
			अवरोध;
		udelay(1);
	पूर्ण

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (r600_घातer_level_get_current_index(rdev) == index)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

व्योम r600_start_dpm(काष्ठा radeon_device *rdev)
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
	r600_enable_mclk_control(rdev, true);
पूर्ण

व्योम r600_stop_dpm(काष्ठा radeon_device *rdev)
अणु
	r600_dynamicpm_enable(rdev, false);
पूर्ण

पूर्णांक r600_dpm_pre_set_घातer_state(काष्ठा radeon_device *rdev)
अणु
	वापस 0;
पूर्ण

व्योम r600_dpm_post_set_घातer_state(काष्ठा radeon_device *rdev)
अणु

पूर्ण

bool r600_is_uvd_state(u32 class, u32 class2)
अणु
	अगर (class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		वापस true;
	अगर (class & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
		वापस true;
	अगर (class & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
		वापस true;
	अगर (class & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
		वापस true;
	अगर (class2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक r600_set_thermal_temperature_range(काष्ठा radeon_device *rdev,
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

bool r600_is_पूर्णांकernal_thermal_sensor(क्रमागत radeon_पूर्णांक_thermal_type sensor)
अणु
	चयन (sensor) अणु
	हाल THERMAL_TYPE_RV6XX:
	हाल THERMAL_TYPE_RV770:
	हाल THERMAL_TYPE_EVERGREEN:
	हाल THERMAL_TYPE_SUMO:
	हाल THERMAL_TYPE_NI:
	हाल THERMAL_TYPE_SI:
	हाल THERMAL_TYPE_CI:
	हाल THERMAL_TYPE_KV:
		वापस true;
	हाल THERMAL_TYPE_ADT7473_WITH_INTERNAL:
	हाल THERMAL_TYPE_EMC2103_WITH_INTERNAL:
		वापस false; /* need special handling */
	हाल THERMAL_TYPE_NONE:
	हाल THERMAL_TYPE_EXTERNAL:
	हाल THERMAL_TYPE_EXTERNAL_GPIO:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

पूर्णांक r600_dpm_late_enable(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;

	अगर (rdev->irq.installed &&
	    r600_is_पूर्णांकernal_thermal_sensor(rdev->pm.पूर्णांक_thermal_type)) अणु
		ret = r600_set_thermal_temperature_range(rdev, R600_TEMP_RANGE_MIN, R600_TEMP_RANGE_MAX);
		अगर (ret)
			वापस ret;
		rdev->irq.dpm_thermal = true;
		radeon_irq_set(rdev);
	पूर्ण

	वापस 0;
पूर्ण

जोड़ घातer_info अणु
	काष्ठा _ATOM_POWERPLAY_INFO info;
	काष्ठा _ATOM_POWERPLAY_INFO_V2 info_2;
	काष्ठा _ATOM_POWERPLAY_INFO_V3 info_3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE pplib;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE2 pplib2;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3 pplib3;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE4 pplib4;
	काष्ठा _ATOM_PPLIB_POWERPLAYTABLE5 pplib5;
पूर्ण;

जोड़ fan_info अणु
	काष्ठा _ATOM_PPLIB_FANTABLE fan;
	काष्ठा _ATOM_PPLIB_FANTABLE2 fan2;
	काष्ठा _ATOM_PPLIB_FANTABLE3 fan3;
पूर्ण;

अटल पूर्णांक r600_parse_clk_voltage_dep_table(काष्ठा radeon_घड़ी_voltage_dependency_table *radeon_table,
					    ATOM_PPLIB_Clock_Voltage_Dependency_Table *atom_table)
अणु
	u32 size = atom_table->ucNumEntries *
		माप(काष्ठा radeon_घड़ी_voltage_dependency_entry);
	पूर्णांक i;
	ATOM_PPLIB_Clock_Voltage_Dependency_Record *entry;

	radeon_table->entries = kzalloc(size, GFP_KERNEL);
	अगर (!radeon_table->entries)
		वापस -ENOMEM;

	entry = &atom_table->entries[0];
	क्रम (i = 0; i < atom_table->ucNumEntries; i++) अणु
		radeon_table->entries[i].clk = le16_to_cpu(entry->usClockLow) |
			(entry->ucClockHigh << 16);
		radeon_table->entries[i].v = le16_to_cpu(entry->usVoltage);
		entry = (ATOM_PPLIB_Clock_Voltage_Dependency_Record *)
			((u8 *)entry + माप(ATOM_PPLIB_Clock_Voltage_Dependency_Record));
	पूर्ण
	radeon_table->count = atom_table->ucNumEntries;

	वापस 0;
पूर्ण

पूर्णांक r600_get_platक्रमm_caps(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	जोड़ घातer_info *घातer_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;

	अगर (!atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस -EINVAL;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	rdev->pm.dpm.platक्रमm_caps = le32_to_cpu(घातer_info->pplib.ulPlatक्रमmCaps);
	rdev->pm.dpm.backbias_response_समय = le16_to_cpu(घातer_info->pplib.usBackbiasTime);
	rdev->pm.dpm.voltage_response_समय = le16_to_cpu(घातer_info->pplib.usVoltageTime);

	वापस 0;
पूर्ण

/* माप(ATOM_PPLIB_EXTENDEDHEADER) */
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2 12
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3 14
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4 16
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5 18
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6 20
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7 22

पूर्णांक r600_parse_extended_घातer_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_mode_info *mode_info = &rdev->mode_info;
	जोड़ घातer_info *घातer_info;
	जोड़ fan_info *fan_info;
	ATOM_PPLIB_Clock_Voltage_Dependency_Table *dep_table;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);
	u16 data_offset;
	u8 frev, crev;
	पूर्णांक ret, i;

	अगर (!atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset))
		वापस -EINVAL;
	घातer_info = (जोड़ घातer_info *)(mode_info->atom_context->bios + data_offset);

	/* fan table */
	अगर (le16_to_cpu(घातer_info->pplib.usTableSize) >=
	    माप(काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		अगर (घातer_info->pplib3.usFanTableOffset) अणु
			fan_info = (जोड़ fan_info *)(mode_info->atom_context->bios + data_offset +
						      le16_to_cpu(घातer_info->pplib3.usFanTableOffset));
			rdev->pm.dpm.fan.t_hyst = fan_info->fan.ucTHyst;
			rdev->pm.dpm.fan.t_min = le16_to_cpu(fan_info->fan.usTMin);
			rdev->pm.dpm.fan.t_med = le16_to_cpu(fan_info->fan.usTMed);
			rdev->pm.dpm.fan.t_high = le16_to_cpu(fan_info->fan.usTHigh);
			rdev->pm.dpm.fan.pwm_min = le16_to_cpu(fan_info->fan.usPWMMin);
			rdev->pm.dpm.fan.pwm_med = le16_to_cpu(fan_info->fan.usPWMMed);
			rdev->pm.dpm.fan.pwm_high = le16_to_cpu(fan_info->fan.usPWMHigh);
			अगर (fan_info->fan.ucFanTableFormat >= 2)
				rdev->pm.dpm.fan.t_max = le16_to_cpu(fan_info->fan2.usTMax);
			अन्यथा
				rdev->pm.dpm.fan.t_max = 10900;
			rdev->pm.dpm.fan.cycle_delay = 100000;
			अगर (fan_info->fan.ucFanTableFormat >= 3) अणु
				rdev->pm.dpm.fan.control_mode = fan_info->fan3.ucFanControlMode;
				rdev->pm.dpm.fan.शेष_max_fan_pwm =
					le16_to_cpu(fan_info->fan3.usFanPWMMax);
				rdev->pm.dpm.fan.शेष_fan_output_sensitivity = 4836;
				rdev->pm.dpm.fan.fan_output_sensitivity =
					le16_to_cpu(fan_info->fan3.usFanOutputSensitivity);
			पूर्ण
			rdev->pm.dpm.fan.ucode_fan_control = true;
		पूर्ण
	पूर्ण

	/* घड़ी dependancy tables, shedding tables */
	अगर (le16_to_cpu(घातer_info->pplib.usTableSize) >=
	    माप(काष्ठा _ATOM_PPLIB_POWERPLAYTABLE4)) अणु
		अगर (घातer_info->pplib4.usVddcDependencyOnSCLKOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usVddcDependencyOnSCLKOffset));
			ret = r600_parse_clk_voltage_dep_table(&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk,
							       dep_table);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (घातer_info->pplib4.usVddciDependencyOnMCLKOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usVddciDependencyOnMCLKOffset));
			ret = r600_parse_clk_voltage_dep_table(&rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk,
							       dep_table);
			अगर (ret) अणु
				kमुक्त(rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usVddcDependencyOnMCLKOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usVddcDependencyOnMCLKOffset));
			ret = r600_parse_clk_voltage_dep_table(&rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk,
							       dep_table);
			अगर (ret) अणु
				kमुक्त(rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries);
				kमुक्त(rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk.entries);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usMvddDependencyOnMCLKOffset) अणु
			dep_table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usMvddDependencyOnMCLKOffset));
			ret = r600_parse_clk_voltage_dep_table(&rdev->pm.dpm.dyn_state.mvdd_dependency_on_mclk,
							       dep_table);
			अगर (ret) अणु
				kमुक्त(rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries);
				kमुक्त(rdev->pm.dpm.dyn_state.vddci_dependency_on_mclk.entries);
				kमुक्त(rdev->pm.dpm.dyn_state.vddc_dependency_on_mclk.entries);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usMaxClockVoltageOnDCOffset) अणु
			ATOM_PPLIB_Clock_Voltage_Limit_Table *clk_v =
				(ATOM_PPLIB_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usMaxClockVoltageOnDCOffset));
			अगर (clk_v->ucNumEntries) अणु
				rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.sclk =
					le16_to_cpu(clk_v->entries[0].usSclkLow) |
					(clk_v->entries[0].ucSclkHigh << 16);
				rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.mclk =
					le16_to_cpu(clk_v->entries[0].usMclkLow) |
					(clk_v->entries[0].ucMclkHigh << 16);
				rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.vddc =
					le16_to_cpu(clk_v->entries[0].usVddc);
				rdev->pm.dpm.dyn_state.max_घड़ी_voltage_on_dc.vddci =
					le16_to_cpu(clk_v->entries[0].usVddci);
			पूर्ण
		पूर्ण
		अगर (घातer_info->pplib4.usVddcPhaseShedLimitsTableOffset) अणु
			ATOM_PPLIB_PhaseSheddingLimits_Table *psl =
				(ATOM_PPLIB_PhaseSheddingLimits_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib4.usVddcPhaseShedLimitsTableOffset));
			ATOM_PPLIB_PhaseSheddingLimits_Record *entry;

			rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries =
				kसुस्मृति(psl->ucNumEntries,
					माप(काष्ठा radeon_phase_shedding_limits_entry),
					GFP_KERNEL);
			अगर (!rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries) अणु
				r600_मुक्त_extended_घातer_table(rdev);
				वापस -ENOMEM;
			पूर्ण

			entry = &psl->entries[0];
			क्रम (i = 0; i < psl->ucNumEntries; i++) अणु
				rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].sclk =
					le16_to_cpu(entry->usSclkLow) | (entry->ucSclkHigh << 16);
				rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].mclk =
					le16_to_cpu(entry->usMclkLow) | (entry->ucMclkHigh << 16);
				rdev->pm.dpm.dyn_state.phase_shedding_limits_table.entries[i].voltage =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_PhaseSheddingLimits_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_PhaseSheddingLimits_Record));
			पूर्ण
			rdev->pm.dpm.dyn_state.phase_shedding_limits_table.count =
				psl->ucNumEntries;
		पूर्ण
	पूर्ण

	/* cac data */
	अगर (le16_to_cpu(घातer_info->pplib.usTableSize) >=
	    माप(काष्ठा _ATOM_PPLIB_POWERPLAYTABLE5)) अणु
		rdev->pm.dpm.tdp_limit = le32_to_cpu(घातer_info->pplib5.ulTDPLimit);
		rdev->pm.dpm.near_tdp_limit = le32_to_cpu(घातer_info->pplib5.ulNearTDPLimit);
		rdev->pm.dpm.near_tdp_limit_adjusted = rdev->pm.dpm.near_tdp_limit;
		rdev->pm.dpm.tdp_od_limit = le16_to_cpu(घातer_info->pplib5.usTDPODLimit);
		अगर (rdev->pm.dpm.tdp_od_limit)
			rdev->pm.dpm.घातer_control = true;
		अन्यथा
			rdev->pm.dpm.घातer_control = false;
		rdev->pm.dpm.tdp_adjusपंचांगent = 0;
		rdev->pm.dpm.sq_ramping_threshold = le32_to_cpu(घातer_info->pplib5.ulSQRampingThreshold);
		rdev->pm.dpm.cac_leakage = le32_to_cpu(घातer_info->pplib5.ulCACLeakage);
		rdev->pm.dpm.load_line_slope = le16_to_cpu(घातer_info->pplib5.usLoadLineSlope);
		अगर (घातer_info->pplib5.usCACLeakageTableOffset) अणु
			ATOM_PPLIB_CAC_Leakage_Table *cac_table =
				(ATOM_PPLIB_CAC_Leakage_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(घातer_info->pplib5.usCACLeakageTableOffset));
			ATOM_PPLIB_CAC_Leakage_Record *entry;
			u32 size = cac_table->ucNumEntries * माप(काष्ठा radeon_cac_leakage_table);
			rdev->pm.dpm.dyn_state.cac_leakage_table.entries = kzalloc(size, GFP_KERNEL);
			अगर (!rdev->pm.dpm.dyn_state.cac_leakage_table.entries) अणु
				r600_मुक्त_extended_घातer_table(rdev);
				वापस -ENOMEM;
			पूर्ण
			entry = &cac_table->entries[0];
			क्रम (i = 0; i < cac_table->ucNumEntries; i++) अणु
				अगर (rdev->pm.dpm.platक्रमm_caps & ATOM_PP_PLATFORM_CAP_EVV) अणु
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc1 =
						le16_to_cpu(entry->usVddc1);
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc2 =
						le16_to_cpu(entry->usVddc2);
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc3 =
						le16_to_cpu(entry->usVddc3);
				पूर्ण अन्यथा अणु
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].vddc =
						le16_to_cpu(entry->usVddc);
					rdev->pm.dpm.dyn_state.cac_leakage_table.entries[i].leakage =
						le32_to_cpu(entry->ulLeakageValue);
				पूर्ण
				entry = (ATOM_PPLIB_CAC_Leakage_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_CAC_Leakage_Record));
			पूर्ण
			rdev->pm.dpm.dyn_state.cac_leakage_table.count = cac_table->ucNumEntries;
		पूर्ण
	पूर्ण

	/* ext tables */
	अगर (le16_to_cpu(घातer_info->pplib.usTableSize) >=
	    माप(काष्ठा _ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		ATOM_PPLIB_EXTENDEDHEADER *ext_hdr = (ATOM_PPLIB_EXTENDEDHEADER *)
			(mode_info->atom_context->bios + data_offset +
			 le16_to_cpu(घातer_info->pplib3.usExtendendedHeaderOffset));
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2) &&
			ext_hdr->usVCETableOffset) अणु
			VCEClockInfoArray *array = (VCEClockInfoArray *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1);
			ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1 +
				 1 + array->ucNumEntries * माप(VCEClockInfo));
			ATOM_PPLIB_VCE_State_Table *states =
				(ATOM_PPLIB_VCE_State_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usVCETableOffset) + 1 +
				 1 + (array->ucNumEntries * माप (VCEClockInfo)) +
				 1 + (limits->numEntries * माप(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record)));
			ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record *entry;
			ATOM_PPLIB_VCE_State_Record *state_entry;
			VCEClockInfo *vce_clk;
			u32 size = limits->numEntries *
				माप(काष्ठा radeon_vce_घड़ी_voltage_dependency_entry);
			rdev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			अगर (!rdev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries) अणु
				r600_मुक्त_extended_घातer_table(rdev);
				वापस -ENOMEM;
			पूर्ण
			rdev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			state_entry = &states->entries[0];
			क्रम (i = 0; i < limits->numEntries; i++) अणु
				vce_clk = (VCEClockInfo *)
					((u8 *)&array->entries[0] +
					 (entry->ucVCEClockInfoIndex * माप(VCEClockInfo)));
				rdev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries[i].evclk =
					le16_to_cpu(vce_clk->usEVClkLow) | (vce_clk->ucEVClkHigh << 16);
				rdev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries[i].ecclk =
					le16_to_cpu(vce_clk->usECClkLow) | (vce_clk->ucECClkHigh << 16);
				rdev->pm.dpm.dyn_state.vce_घड़ी_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record));
			पूर्ण
			क्रम (i = 0; i < states->numEntries; i++) अणु
				अगर (i >= RADEON_MAX_VCE_LEVELS)
					अवरोध;
				vce_clk = (VCEClockInfo *)
					((u8 *)&array->entries[0] +
					 (state_entry->ucVCEClockInfoIndex * माप(VCEClockInfo)));
				rdev->pm.dpm.vce_states[i].evclk =
					le16_to_cpu(vce_clk->usEVClkLow) | (vce_clk->ucEVClkHigh << 16);
				rdev->pm.dpm.vce_states[i].ecclk =
					le16_to_cpu(vce_clk->usECClkLow) | (vce_clk->ucECClkHigh << 16);
				rdev->pm.dpm.vce_states[i].clk_idx =
					state_entry->ucClockInfoIndex & 0x3f;
				rdev->pm.dpm.vce_states[i].pstate =
					(state_entry->ucClockInfoIndex & 0xc0) >> 6;
				state_entry = (ATOM_PPLIB_VCE_State_Record *)
					((u8 *)state_entry + माप(ATOM_PPLIB_VCE_State_Record));
			पूर्ण
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3) &&
			ext_hdr->usUVDTableOffset) अणु
			UVDClockInfoArray *array = (UVDClockInfoArray *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usUVDTableOffset) + 1);
			ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usUVDTableOffset) + 1 +
				 1 + (array->ucNumEntries * माप (UVDClockInfo)));
			ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				माप(काष्ठा radeon_uvd_घड़ी_voltage_dependency_entry);
			rdev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			अगर (!rdev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries) अणु
				r600_मुक्त_extended_घातer_table(rdev);
				वापस -ENOMEM;
			पूर्ण
			rdev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			क्रम (i = 0; i < limits->numEntries; i++) अणु
				UVDClockInfo *uvd_clk = (UVDClockInfo *)
					((u8 *)&array->entries[0] +
					 (entry->ucUVDClockInfoIndex * माप(UVDClockInfo)));
				rdev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries[i].vclk =
					le16_to_cpu(uvd_clk->usVClkLow) | (uvd_clk->ucVClkHigh << 16);
				rdev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries[i].dclk =
					le16_to_cpu(uvd_clk->usDClkLow) | (uvd_clk->ucDClkHigh << 16);
				rdev->pm.dpm.dyn_state.uvd_घड़ी_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_UVD_Clock_Voltage_Limit_Record));
			पूर्ण
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4) &&
			ext_hdr->usSAMUTableOffset) अणु
			ATOM_PPLIB_SAMClk_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_SAMClk_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usSAMUTableOffset) + 1);
			ATOM_PPLIB_SAMClk_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				माप(काष्ठा radeon_घड़ी_voltage_dependency_entry);
			rdev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			अगर (!rdev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.entries) अणु
				r600_मुक्त_extended_घातer_table(rdev);
				वापस -ENOMEM;
			पूर्ण
			rdev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			क्रम (i = 0; i < limits->numEntries; i++) अणु
				rdev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.entries[i].clk =
					le16_to_cpu(entry->usSAMClockLow) | (entry->ucSAMClockHigh << 16);
				rdev->pm.dpm.dyn_state.samu_घड़ी_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_SAMClk_Voltage_Limit_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_SAMClk_Voltage_Limit_Record));
			पूर्ण
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5) &&
		    ext_hdr->usPPMTableOffset) अणु
			ATOM_PPLIB_PPM_Table *ppm = (ATOM_PPLIB_PPM_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usPPMTableOffset));
			rdev->pm.dpm.dyn_state.ppm_table =
				kzalloc(माप(काष्ठा radeon_ppm_table), GFP_KERNEL);
			अगर (!rdev->pm.dpm.dyn_state.ppm_table) अणु
				r600_मुक्त_extended_घातer_table(rdev);
				वापस -ENOMEM;
			पूर्ण
			rdev->pm.dpm.dyn_state.ppm_table->ppm_design = ppm->ucPpmDesign;
			rdev->pm.dpm.dyn_state.ppm_table->cpu_core_number =
				le16_to_cpu(ppm->usCpuCoreNumber);
			rdev->pm.dpm.dyn_state.ppm_table->platक्रमm_tdp =
				le32_to_cpu(ppm->ulPlatक्रमmTDP);
			rdev->pm.dpm.dyn_state.ppm_table->small_ac_platक्रमm_tdp =
				le32_to_cpu(ppm->ulSmallACPlatक्रमmTDP);
			rdev->pm.dpm.dyn_state.ppm_table->platक्रमm_tdc =
				le32_to_cpu(ppm->ulPlatक्रमmTDC);
			rdev->pm.dpm.dyn_state.ppm_table->small_ac_platक्रमm_tdc =
				le32_to_cpu(ppm->ulSmallACPlatक्रमmTDC);
			rdev->pm.dpm.dyn_state.ppm_table->apu_tdp =
				le32_to_cpu(ppm->ulApuTDP);
			rdev->pm.dpm.dyn_state.ppm_table->dgpu_tdp =
				le32_to_cpu(ppm->ulDGpuTDP);
			rdev->pm.dpm.dyn_state.ppm_table->dgpu_ulv_घातer =
				le32_to_cpu(ppm->ulDGpuUlvPower);
			rdev->pm.dpm.dyn_state.ppm_table->tj_max =
				le32_to_cpu(ppm->ulTjmax);
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6) &&
			ext_hdr->usACPTableOffset) अणु
			ATOM_PPLIB_ACPClk_Voltage_Limit_Table *limits =
				(ATOM_PPLIB_ACPClk_Voltage_Limit_Table *)
				(mode_info->atom_context->bios + data_offset +
				 le16_to_cpu(ext_hdr->usACPTableOffset) + 1);
			ATOM_PPLIB_ACPClk_Voltage_Limit_Record *entry;
			u32 size = limits->numEntries *
				माप(काष्ठा radeon_घड़ी_voltage_dependency_entry);
			rdev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.entries =
				kzalloc(size, GFP_KERNEL);
			अगर (!rdev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.entries) अणु
				r600_मुक्त_extended_घातer_table(rdev);
				वापस -ENOMEM;
			पूर्ण
			rdev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.count =
				limits->numEntries;
			entry = &limits->entries[0];
			क्रम (i = 0; i < limits->numEntries; i++) अणु
				rdev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.entries[i].clk =
					le16_to_cpu(entry->usACPClockLow) | (entry->ucACPClockHigh << 16);
				rdev->pm.dpm.dyn_state.acp_घड़ी_voltage_dependency_table.entries[i].v =
					le16_to_cpu(entry->usVoltage);
				entry = (ATOM_PPLIB_ACPClk_Voltage_Limit_Record *)
					((u8 *)entry + माप(ATOM_PPLIB_ACPClk_Voltage_Limit_Record));
			पूर्ण
		पूर्ण
		अगर ((le16_to_cpu(ext_hdr->usSize) >= SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7) &&
			ext_hdr->usPowerTuneTableOffset) अणु
			u8 rev = *(u8 *)(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
			ATOM_PowerTune_Table *pt;
			rdev->pm.dpm.dyn_state.cac_tdp_table =
				kzalloc(माप(काष्ठा radeon_cac_tdp_table), GFP_KERNEL);
			अगर (!rdev->pm.dpm.dyn_state.cac_tdp_table) अणु
				r600_मुक्त_extended_घातer_table(rdev);
				वापस -ENOMEM;
			पूर्ण
			अगर (rev > 0) अणु
				ATOM_PPLIB_POWERTUNE_Table_V1 *ppt = (ATOM_PPLIB_POWERTUNE_Table_V1 *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
				rdev->pm.dpm.dyn_state.cac_tdp_table->maximum_घातer_delivery_limit =
					le16_to_cpu(ppt->usMaximumPowerDeliveryLimit);
				pt = &ppt->घातer_tune_table;
			पूर्ण अन्यथा अणु
				ATOM_PPLIB_POWERTUNE_Table *ppt = (ATOM_PPLIB_POWERTUNE_Table *)
					(mode_info->atom_context->bios + data_offset +
					 le16_to_cpu(ext_hdr->usPowerTuneTableOffset));
				rdev->pm.dpm.dyn_state.cac_tdp_table->maximum_घातer_delivery_limit = 255;
				pt = &ppt->घातer_tune_table;
			पूर्ण
			rdev->pm.dpm.dyn_state.cac_tdp_table->tdp = le16_to_cpu(pt->usTDP);
			rdev->pm.dpm.dyn_state.cac_tdp_table->configurable_tdp =
				le16_to_cpu(pt->usConfigurableTDP);
			rdev->pm.dpm.dyn_state.cac_tdp_table->tdc = le16_to_cpu(pt->usTDC);
			rdev->pm.dpm.dyn_state.cac_tdp_table->battery_घातer_limit =
				le16_to_cpu(pt->usBatteryPowerLimit);
			rdev->pm.dpm.dyn_state.cac_tdp_table->small_घातer_limit =
				le16_to_cpu(pt->usSmallPowerLimit);
			rdev->pm.dpm.dyn_state.cac_tdp_table->low_cac_leakage =
				le16_to_cpu(pt->usLowCACLeakage);
			rdev->pm.dpm.dyn_state.cac_tdp_table->high_cac_leakage =
				le16_to_cpu(pt->usHighCACLeakage);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम r600_मुक्त_extended_घातer_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_dpm_dynamic_state *dyn_state = &rdev->pm.dpm.dyn_state;

	kमुक्त(dyn_state->vddc_dependency_on_sclk.entries);
	kमुक्त(dyn_state->vddci_dependency_on_mclk.entries);
	kमुक्त(dyn_state->vddc_dependency_on_mclk.entries);
	kमुक्त(dyn_state->mvdd_dependency_on_mclk.entries);
	kमुक्त(dyn_state->cac_leakage_table.entries);
	kमुक्त(dyn_state->phase_shedding_limits_table.entries);
	kमुक्त(dyn_state->ppm_table);
	kमुक्त(dyn_state->cac_tdp_table);
	kमुक्त(dyn_state->vce_घड़ी_voltage_dependency_table.entries);
	kमुक्त(dyn_state->uvd_घड़ी_voltage_dependency_table.entries);
	kमुक्त(dyn_state->samu_घड़ी_voltage_dependency_table.entries);
	kमुक्त(dyn_state->acp_घड़ी_voltage_dependency_table.entries);
पूर्ण

क्रमागत radeon_pcie_gen r600_get_pcie_gen_support(काष्ठा radeon_device *rdev,
					       u32 sys_mask,
					       क्रमागत radeon_pcie_gen asic_gen,
					       क्रमागत radeon_pcie_gen शेष_gen)
अणु
	चयन (asic_gen) अणु
	हाल RADEON_PCIE_GEN1:
		वापस RADEON_PCIE_GEN1;
	हाल RADEON_PCIE_GEN2:
		वापस RADEON_PCIE_GEN2;
	हाल RADEON_PCIE_GEN3:
		वापस RADEON_PCIE_GEN3;
	शेष:
		अगर ((sys_mask & RADEON_PCIE_SPEED_80) && (शेष_gen == RADEON_PCIE_GEN3))
			वापस RADEON_PCIE_GEN3;
		अन्यथा अगर ((sys_mask & RADEON_PCIE_SPEED_50) && (शेष_gen == RADEON_PCIE_GEN2))
			वापस RADEON_PCIE_GEN2;
		अन्यथा
			वापस RADEON_PCIE_GEN1;
	पूर्ण
	वापस RADEON_PCIE_GEN1;
पूर्ण

u16 r600_get_pcie_lane_support(काष्ठा radeon_device *rdev,
			       u16 asic_lanes,
			       u16 शेष_lanes)
अणु
	चयन (asic_lanes) अणु
	हाल 0:
	शेष:
		वापस शेष_lanes;
	हाल 1:
		वापस 1;
	हाल 2:
		वापस 2;
	हाल 4:
		वापस 4;
	हाल 8:
		वापस 8;
	हाल 12:
		वापस 12;
	हाल 16:
		वापस 16;
	पूर्ण
पूर्ण

u8 r600_encode_pci_lane_width(u32 lanes)
अणु
	u8 encoded_lanes[] = अणु 0, 1, 2, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6 पूर्ण;

	अगर (lanes > 16)
		वापस 0;

	वापस encoded_lanes[lanes];
पूर्ण
