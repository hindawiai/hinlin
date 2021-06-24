<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fixed.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "atom.h"
#समावेश "atom-bits.h"

अटल व्योम atombios_overscan_setup(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_display_mode *mode,
				    काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	SET_CRTC_OVERSCAN_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetCRTC_OverScan);
	पूर्णांक a1, a2;

	स_रखो(&args, 0, माप(args));

	args.ucCRTC = radeon_crtc->crtc_id;

	चयन (radeon_crtc->rmx_type) अणु
	हाल RMX_CENTER:
		args.usOverscanTop = cpu_to_le16((adjusted_mode->crtc_vdisplay - mode->crtc_vdisplay) / 2);
		args.usOverscanBottom = cpu_to_le16((adjusted_mode->crtc_vdisplay - mode->crtc_vdisplay) / 2);
		args.usOverscanLeft = cpu_to_le16((adjusted_mode->crtc_hdisplay - mode->crtc_hdisplay) / 2);
		args.usOverscanRight = cpu_to_le16((adjusted_mode->crtc_hdisplay - mode->crtc_hdisplay) / 2);
		अवरोध;
	हाल RMX_ASPECT:
		a1 = mode->crtc_vdisplay * adjusted_mode->crtc_hdisplay;
		a2 = adjusted_mode->crtc_vdisplay * mode->crtc_hdisplay;

		अगर (a1 > a2) अणु
			args.usOverscanLeft = cpu_to_le16((adjusted_mode->crtc_hdisplay - (a2 / mode->crtc_vdisplay)) / 2);
			args.usOverscanRight = cpu_to_le16((adjusted_mode->crtc_hdisplay - (a2 / mode->crtc_vdisplay)) / 2);
		पूर्ण अन्यथा अगर (a2 > a1) अणु
			args.usOverscanTop = cpu_to_le16((adjusted_mode->crtc_vdisplay - (a1 / mode->crtc_hdisplay)) / 2);
			args.usOverscanBottom = cpu_to_le16((adjusted_mode->crtc_vdisplay - (a1 / mode->crtc_hdisplay)) / 2);
		पूर्ण
		अवरोध;
	हाल RMX_FULL:
	शेष:
		args.usOverscanRight = cpu_to_le16(radeon_crtc->h_border);
		args.usOverscanLeft = cpu_to_le16(radeon_crtc->h_border);
		args.usOverscanBottom = cpu_to_le16(radeon_crtc->v_border);
		args.usOverscanTop = cpu_to_le16(radeon_crtc->v_border);
		अवरोध;
	पूर्ण
	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम atombios_scaler_setup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	ENABLE_SCALER_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableScaler);
	काष्ठा radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	/* fixme - fill in enc_priv क्रम atom dac */
	क्रमागत radeon_tv_std tv_std = TV_STD_NTSC;
	bool is_tv = false, is_cv = false;

	अगर (!ASIC_IS_AVIVO(rdev) && radeon_crtc->crtc_id)
		वापस;

	अगर (radeon_encoder->active_device & ATOM_DEVICE_TV_SUPPORT) अणु
		काष्ठा radeon_encoder_atom_dac *tv_dac = radeon_encoder->enc_priv;
		tv_std = tv_dac->tv_std;
		is_tv = true;
	पूर्ण

	स_रखो(&args, 0, माप(args));

	args.ucScaler = radeon_crtc->crtc_id;

	अगर (is_tv) अणु
		चयन (tv_std) अणु
		हाल TV_STD_NTSC:
		शेष:
			args.ucTVStandard = ATOM_TV_NTSC;
			अवरोध;
		हाल TV_STD_PAL:
			args.ucTVStandard = ATOM_TV_PAL;
			अवरोध;
		हाल TV_STD_PAL_M:
			args.ucTVStandard = ATOM_TV_PALM;
			अवरोध;
		हाल TV_STD_PAL_60:
			args.ucTVStandard = ATOM_TV_PAL60;
			अवरोध;
		हाल TV_STD_NTSC_J:
			args.ucTVStandard = ATOM_TV_NTSCJ;
			अवरोध;
		हाल TV_STD_SCART_PAL:
			args.ucTVStandard = ATOM_TV_PAL; /* ??? */
			अवरोध;
		हाल TV_STD_SECAM:
			args.ucTVStandard = ATOM_TV_SECAM;
			अवरोध;
		हाल TV_STD_PAL_CN:
			args.ucTVStandard = ATOM_TV_PALCN;
			अवरोध;
		पूर्ण
		args.ucEnable = SCALER_ENABLE_MULTITAP_MODE;
	पूर्ण अन्यथा अगर (is_cv) अणु
		args.ucTVStandard = ATOM_TV_CV;
		args.ucEnable = SCALER_ENABLE_MULTITAP_MODE;
	पूर्ण अन्यथा अणु
		चयन (radeon_crtc->rmx_type) अणु
		हाल RMX_FULL:
			args.ucEnable = ATOM_SCALER_EXPANSION;
			अवरोध;
		हाल RMX_CENTER:
			args.ucEnable = ATOM_SCALER_CENTER;
			अवरोध;
		हाल RMX_ASPECT:
			args.ucEnable = ATOM_SCALER_EXPANSION;
			अवरोध;
		शेष:
			अगर (ASIC_IS_AVIVO(rdev))
				args.ucEnable = ATOM_SCALER_DISABLE;
			अन्यथा
				args.ucEnable = ATOM_SCALER_CENTER;
			अवरोध;
		पूर्ण
	पूर्ण
	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
	अगर ((is_tv || is_cv)
	    && rdev->family >= CHIP_RV515 && rdev->family <= CHIP_R580) अणु
		atom_rv515_क्रमce_tv_scaler(rdev, radeon_crtc);
	पूर्ण
पूर्ण

अटल व्योम atombios_lock_crtc(काष्ठा drm_crtc *crtc, पूर्णांक lock)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक index =
	    GetIndexIntoMasterTable(COMMAND, UpdateCRTC_DoubleBufferRegisters);
	ENABLE_CRTC_PS_ALLOCATION args;

	स_रखो(&args, 0, माप(args));

	args.ucCRTC = radeon_crtc->crtc_id;
	args.ucEnable = lock;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम atombios_enable_crtc(काष्ठा drm_crtc *crtc, पूर्णांक state)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableCRTC);
	ENABLE_CRTC_PS_ALLOCATION args;

	स_रखो(&args, 0, माप(args));

	args.ucCRTC = radeon_crtc->crtc_id;
	args.ucEnable = state;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम atombios_enable_crtc_memreq(काष्ठा drm_crtc *crtc, पूर्णांक state)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableCRTCMemReq);
	ENABLE_CRTC_PS_ALLOCATION args;

	स_रखो(&args, 0, माप(args));

	args.ucCRTC = radeon_crtc->crtc_id;
	args.ucEnable = state;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल स्थिर u32 vga_control_regs[6] =
अणु
	AVIVO_D1VGA_CONTROL,
	AVIVO_D2VGA_CONTROL,
	EVERGREEN_D3VGA_CONTROL,
	EVERGREEN_D4VGA_CONTROL,
	EVERGREEN_D5VGA_CONTROL,
	EVERGREEN_D6VGA_CONTROL,
पूर्ण;

अटल व्योम atombios_blank_crtc(काष्ठा drm_crtc *crtc, पूर्णांक state)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, BlankCRTC);
	BLANK_CRTC_PS_ALLOCATION args;
	u32 vga_control = 0;

	स_रखो(&args, 0, माप(args));

	अगर (ASIC_IS_DCE8(rdev)) अणु
		vga_control = RREG32(vga_control_regs[radeon_crtc->crtc_id]);
		WREG32(vga_control_regs[radeon_crtc->crtc_id], vga_control | 1);
	पूर्ण

	args.ucCRTC = radeon_crtc->crtc_id;
	args.ucBlanking = state;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

	अगर (ASIC_IS_DCE8(rdev))
		WREG32(vga_control_regs[radeon_crtc->crtc_id], vga_control);
पूर्ण

अटल व्योम atombios_घातergate_crtc(काष्ठा drm_crtc *crtc, पूर्णांक state)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableDispPowerGating);
	ENABLE_DISP_POWER_GATING_PARAMETERS_V2_1 args;

	स_रखो(&args, 0, माप(args));

	args.ucDispPipeId = radeon_crtc->crtc_id;
	args.ucEnable = state;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम atombios_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		radeon_crtc->enabled = true;
		atombios_enable_crtc(crtc, ATOM_ENABLE);
		अगर (ASIC_IS_DCE3(rdev) && !ASIC_IS_DCE6(rdev))
			atombios_enable_crtc_memreq(crtc, ATOM_ENABLE);
		atombios_blank_crtc(crtc, ATOM_DISABLE);
		अगर (dev->num_crtcs > radeon_crtc->crtc_id)
			drm_crtc_vblank_on(crtc);
		radeon_crtc_load_lut(crtc);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		अगर (dev->num_crtcs > radeon_crtc->crtc_id)
			drm_crtc_vblank_off(crtc);
		अगर (radeon_crtc->enabled)
			atombios_blank_crtc(crtc, ATOM_ENABLE);
		अगर (ASIC_IS_DCE3(rdev) && !ASIC_IS_DCE6(rdev))
			atombios_enable_crtc_memreq(crtc, ATOM_DISABLE);
		atombios_enable_crtc(crtc, ATOM_DISABLE);
		radeon_crtc->enabled = false;
		अवरोध;
	पूर्ण
	/* adjust pm to dpms */
	radeon_pm_compute_घड़ीs(rdev);
पूर्ण

अटल व्योम
atombios_set_crtc_dtd_timing(काष्ठा drm_crtc *crtc,
			     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	SET_CRTC_USING_DTD_TIMING_PARAMETERS args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetCRTC_UsingDTDTiming);
	u16 misc = 0;

	स_रखो(&args, 0, माप(args));
	args.usH_Size = cpu_to_le16(mode->crtc_hdisplay - (radeon_crtc->h_border * 2));
	args.usH_Blanking_Time =
		cpu_to_le16(mode->crtc_hblank_end - mode->crtc_hdisplay + (radeon_crtc->h_border * 2));
	args.usV_Size = cpu_to_le16(mode->crtc_vdisplay - (radeon_crtc->v_border * 2));
	args.usV_Blanking_Time =
		cpu_to_le16(mode->crtc_vblank_end - mode->crtc_vdisplay + (radeon_crtc->v_border * 2));
	args.usH_SyncOffset =
		cpu_to_le16(mode->crtc_hsync_start - mode->crtc_hdisplay + radeon_crtc->h_border);
	args.usH_SyncWidth =
		cpu_to_le16(mode->crtc_hsync_end - mode->crtc_hsync_start);
	args.usV_SyncOffset =
		cpu_to_le16(mode->crtc_vsync_start - mode->crtc_vdisplay + radeon_crtc->v_border);
	args.usV_SyncWidth =
		cpu_to_le16(mode->crtc_vsync_end - mode->crtc_vsync_start);
	args.ucH_Border = radeon_crtc->h_border;
	args.ucV_Border = radeon_crtc->v_border;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		misc |= ATOM_VSYNC_POLARITY;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		misc |= ATOM_HSYNC_POLARITY;
	अगर (mode->flags & DRM_MODE_FLAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		misc |= ATOM_INTERLACE;
	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		misc |= ATOM_DOUBLE_CLOCK_MODE;
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		misc |= ATOM_H_REPLICATIONBY2 | ATOM_V_REPLICATIONBY2;

	args.susModeMiscInfo.usAccess = cpu_to_le16(misc);
	args.ucCRTC = radeon_crtc->crtc_id;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम atombios_crtc_set_timing(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	SET_CRTC_TIMING_PARAMETERS_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetCRTC_Timing);
	u16 misc = 0;

	स_रखो(&args, 0, माप(args));
	args.usH_Total = cpu_to_le16(mode->crtc_htotal);
	args.usH_Disp = cpu_to_le16(mode->crtc_hdisplay);
	args.usH_SyncStart = cpu_to_le16(mode->crtc_hsync_start);
	args.usH_SyncWidth =
		cpu_to_le16(mode->crtc_hsync_end - mode->crtc_hsync_start);
	args.usV_Total = cpu_to_le16(mode->crtc_vtotal);
	args.usV_Disp = cpu_to_le16(mode->crtc_vdisplay);
	args.usV_SyncStart = cpu_to_le16(mode->crtc_vsync_start);
	args.usV_SyncWidth =
		cpu_to_le16(mode->crtc_vsync_end - mode->crtc_vsync_start);

	args.ucOverscanRight = radeon_crtc->h_border;
	args.ucOverscanLeft = radeon_crtc->h_border;
	args.ucOverscanBottom = radeon_crtc->v_border;
	args.ucOverscanTop = radeon_crtc->v_border;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		misc |= ATOM_VSYNC_POLARITY;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		misc |= ATOM_HSYNC_POLARITY;
	अगर (mode->flags & DRM_MODE_FLAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		misc |= ATOM_INTERLACE;
	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		misc |= ATOM_DOUBLE_CLOCK_MODE;
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		misc |= ATOM_H_REPLICATIONBY2 | ATOM_V_REPLICATIONBY2;

	args.susModeMiscInfo.usAccess = cpu_to_le16(misc);
	args.ucCRTC = radeon_crtc->crtc_id;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम atombios_disable_ss(काष्ठा radeon_device *rdev, पूर्णांक pll_id)
अणु
	u32 ss_cntl;

	अगर (ASIC_IS_DCE4(rdev)) अणु
		चयन (pll_id) अणु
		हाल ATOM_PPLL1:
			ss_cntl = RREG32(EVERGREEN_P1PLL_SS_CNTL);
			ss_cntl &= ~EVERGREEN_PxPLL_SS_EN;
			WREG32(EVERGREEN_P1PLL_SS_CNTL, ss_cntl);
			अवरोध;
		हाल ATOM_PPLL2:
			ss_cntl = RREG32(EVERGREEN_P2PLL_SS_CNTL);
			ss_cntl &= ~EVERGREEN_PxPLL_SS_EN;
			WREG32(EVERGREEN_P2PLL_SS_CNTL, ss_cntl);
			अवरोध;
		हाल ATOM_DCPLL:
		हाल ATOM_PPLL_INVALID:
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		चयन (pll_id) अणु
		हाल ATOM_PPLL1:
			ss_cntl = RREG32(AVIVO_P1PLL_INT_SS_CNTL);
			ss_cntl &= ~1;
			WREG32(AVIVO_P1PLL_INT_SS_CNTL, ss_cntl);
			अवरोध;
		हाल ATOM_PPLL2:
			ss_cntl = RREG32(AVIVO_P2PLL_INT_SS_CNTL);
			ss_cntl &= ~1;
			WREG32(AVIVO_P2PLL_INT_SS_CNTL, ss_cntl);
			अवरोध;
		हाल ATOM_DCPLL:
		हाल ATOM_PPLL_INVALID:
			वापस;
		पूर्ण
	पूर्ण
पूर्ण


जोड़ atom_enable_ss अणु
	ENABLE_LVDS_SS_PARAMETERS lvds_ss;
	ENABLE_LVDS_SS_PARAMETERS_V2 lvds_ss_2;
	ENABLE_SPREAD_SPECTRUM_ON_PPLL_PS_ALLOCATION v1;
	ENABLE_SPREAD_SPECTRUM_ON_PPLL_V2 v2;
	ENABLE_SPREAD_SPECTRUM_ON_PPLL_V3 v3;
पूर्ण;

अटल व्योम atombios_crtc_program_ss(काष्ठा radeon_device *rdev,
				     पूर्णांक enable,
				     पूर्णांक pll_id,
				     पूर्णांक crtc_id,
				     काष्ठा radeon_atom_ss *ss)
अणु
	अचिन्हित i;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableSpपढ़ोSpectrumOnPPLL);
	जोड़ atom_enable_ss args;

	अगर (enable) अणु
		/* Don't mess with SS अगर percentage is 0 or बाह्यal ss.
		 * SS is alपढ़ोy disabled previously, and disabling it
		 * again can cause display problems अगर the pll is alपढ़ोy
		 * programmed.
		 */
		अगर (ss->percentage == 0)
			वापस;
		अगर (ss->type & ATOM_EXTERNAL_SS_MASK)
			वापस;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < rdev->num_crtc; i++) अणु
			अगर (rdev->mode_info.crtcs[i] &&
			    rdev->mode_info.crtcs[i]->enabled &&
			    i != crtc_id &&
			    pll_id == rdev->mode_info.crtcs[i]->pll_id) अणु
				/* one other crtc is using this pll करोn't turn
				 * off spपढ़ो spectrum as it might turn off
				 * display on active crtc
				 */
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	स_रखो(&args, 0, माप(args));

	अगर (ASIC_IS_DCE5(rdev)) अणु
		args.v3.usSpपढ़ोSpectrumAmountFrac = cpu_to_le16(0);
		args.v3.ucSpपढ़ोSpectrumType = ss->type & ATOM_SS_CENTRE_SPREAD_MODE_MASK;
		चयन (pll_id) अणु
		हाल ATOM_PPLL1:
			args.v3.ucSpपढ़ोSpectrumType |= ATOM_PPLL_SS_TYPE_V3_P1PLL;
			अवरोध;
		हाल ATOM_PPLL2:
			args.v3.ucSpपढ़ोSpectrumType |= ATOM_PPLL_SS_TYPE_V3_P2PLL;
			अवरोध;
		हाल ATOM_DCPLL:
			args.v3.ucSpपढ़ोSpectrumType |= ATOM_PPLL_SS_TYPE_V3_DCPLL;
			अवरोध;
		हाल ATOM_PPLL_INVALID:
			वापस;
		पूर्ण
		args.v3.usSpपढ़ोSpectrumAmount = cpu_to_le16(ss->amount);
		args.v3.usSpपढ़ोSpectrumStep = cpu_to_le16(ss->step);
		args.v3.ucEnable = enable;
	पूर्ण अन्यथा अगर (ASIC_IS_DCE4(rdev)) अणु
		args.v2.usSpपढ़ोSpectrumPercentage = cpu_to_le16(ss->percentage);
		args.v2.ucSpपढ़ोSpectrumType = ss->type & ATOM_SS_CENTRE_SPREAD_MODE_MASK;
		चयन (pll_id) अणु
		हाल ATOM_PPLL1:
			args.v2.ucSpपढ़ोSpectrumType |= ATOM_PPLL_SS_TYPE_V2_P1PLL;
			अवरोध;
		हाल ATOM_PPLL2:
			args.v2.ucSpपढ़ोSpectrumType |= ATOM_PPLL_SS_TYPE_V2_P2PLL;
			अवरोध;
		हाल ATOM_DCPLL:
			args.v2.ucSpपढ़ोSpectrumType |= ATOM_PPLL_SS_TYPE_V2_DCPLL;
			अवरोध;
		हाल ATOM_PPLL_INVALID:
			वापस;
		पूर्ण
		args.v2.usSpपढ़ोSpectrumAmount = cpu_to_le16(ss->amount);
		args.v2.usSpपढ़ोSpectrumStep = cpu_to_le16(ss->step);
		args.v2.ucEnable = enable;
	पूर्ण अन्यथा अगर (ASIC_IS_DCE3(rdev)) अणु
		args.v1.usSpपढ़ोSpectrumPercentage = cpu_to_le16(ss->percentage);
		args.v1.ucSpपढ़ोSpectrumType = ss->type & ATOM_SS_CENTRE_SPREAD_MODE_MASK;
		args.v1.ucSpपढ़ोSpectrumStep = ss->step;
		args.v1.ucSpपढ़ोSpectrumDelay = ss->delay;
		args.v1.ucSpपढ़ोSpectrumRange = ss->range;
		args.v1.ucPpll = pll_id;
		args.v1.ucEnable = enable;
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		अगर ((enable == ATOM_DISABLE) || (ss->percentage == 0) ||
		    (ss->type & ATOM_EXTERNAL_SS_MASK)) अणु
			atombios_disable_ss(rdev, pll_id);
			वापस;
		पूर्ण
		args.lvds_ss_2.usSpपढ़ोSpectrumPercentage = cpu_to_le16(ss->percentage);
		args.lvds_ss_2.ucSpपढ़ोSpectrumType = ss->type & ATOM_SS_CENTRE_SPREAD_MODE_MASK;
		args.lvds_ss_2.ucSpपढ़ोSpectrumStep = ss->step;
		args.lvds_ss_2.ucSpपढ़ोSpectrumDelay = ss->delay;
		args.lvds_ss_2.ucSpपढ़ोSpectrumRange = ss->range;
		args.lvds_ss_2.ucEnable = enable;
	पूर्ण अन्यथा अणु
		अगर (enable == ATOM_DISABLE) अणु
			atombios_disable_ss(rdev, pll_id);
			वापस;
		पूर्ण
		args.lvds_ss.usSpपढ़ोSpectrumPercentage = cpu_to_le16(ss->percentage);
		args.lvds_ss.ucSpपढ़ोSpectrumType = ss->type & ATOM_SS_CENTRE_SPREAD_MODE_MASK;
		args.lvds_ss.ucSpपढ़ोSpectrumStepSize_Delay = (ss->step & 3) << 2;
		args.lvds_ss.ucSpपढ़ोSpectrumStepSize_Delay |= (ss->delay & 7) << 4;
		args.lvds_ss.ucEnable = enable;
	पूर्ण
	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

जोड़ adjust_pixel_घड़ी अणु
	ADJUST_DISPLAY_PLL_PS_ALLOCATION v1;
	ADJUST_DISPLAY_PLL_PS_ALLOCATION_V3 v3;
पूर्ण;

अटल u32 atombios_adjust_pll(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_encoder *encoder = radeon_crtc->encoder;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	u32 adjusted_घड़ी = mode->घड़ी;
	पूर्णांक encoder_mode = atombios_get_encoder_mode(encoder);
	u32 dp_घड़ी = mode->घड़ी;
	u32 घड़ी = mode->घड़ी;
	पूर्णांक bpc = radeon_crtc->bpc;
	bool is_duallink = radeon_dig_monitor_is_duallink(encoder, mode->घड़ी);

	/* reset the pll flags */
	radeon_crtc->pll_flags = 0;

	अगर (ASIC_IS_AVIVO(rdev)) अणु
		अगर ((rdev->family == CHIP_RS600) ||
		    (rdev->family == CHIP_RS690) ||
		    (rdev->family == CHIP_RS740))
			radeon_crtc->pll_flags |= (/*RADEON_PLL_USE_FRAC_FB_DIV |*/
				RADEON_PLL_PREFER_CLOSEST_LOWER);

		अगर (ASIC_IS_DCE32(rdev) && mode->घड़ी > 200000)	/* range limits??? */
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_HIGH_FB_DIV;
		अन्यथा
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_LOW_REF_DIV;

		अगर (rdev->family < CHIP_RV770)
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_MINM_OVER_MAXP;
		/* use frac fb भाग on APUs */
		अगर (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE61(rdev) || ASIC_IS_DCE8(rdev))
			radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
		/* use frac fb भाग on RS780/RS880 */
		अगर (((rdev->family == CHIP_RS780) || (rdev->family == CHIP_RS880))
		    && !radeon_crtc->ss_enabled)
			radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
		अगर (ASIC_IS_DCE32(rdev) && mode->घड़ी > 165000)
			radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
	पूर्ण अन्यथा अणु
		radeon_crtc->pll_flags |= RADEON_PLL_LEGACY;

		अगर (mode->घड़ी > 200000)	/* range limits??? */
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_HIGH_FB_DIV;
		अन्यथा
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_LOW_REF_DIV;
	पूर्ण

	अगर ((radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT | ATOM_DEVICE_DFP_SUPPORT)) ||
	    (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)) अणु
		अगर (connector) अणु
			काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
			काष्ठा radeon_connector_atom_dig *dig_connector =
				radeon_connector->con_priv;

			dp_घड़ी = dig_connector->dp_घड़ी;
		पूर्ण
	पूर्ण

	अगर (radeon_encoder->is_mst_encoder) अणु
		काष्ठा radeon_encoder_mst *mst_enc = radeon_encoder->enc_priv;
		काष्ठा radeon_connector_atom_dig *dig_connector = mst_enc->connector->con_priv;

		dp_घड़ी = dig_connector->dp_घड़ी;
	पूर्ण

	/* use recommended ref_भाग क्रम ss */
	अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
		अगर (radeon_crtc->ss_enabled) अणु
			अगर (radeon_crtc->ss.refभाग) अणु
				radeon_crtc->pll_flags |= RADEON_PLL_USE_REF_DIV;
				radeon_crtc->pll_reference_भाग = radeon_crtc->ss.refभाग;
				अगर (ASIC_IS_AVIVO(rdev) &&
				    rdev->family != CHIP_RS780 &&
				    rdev->family != CHIP_RS880)
					radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ASIC_IS_AVIVO(rdev)) अणु
		/* DVO wants 2x pixel घड़ी अगर the DVO chip is in 12 bit mode */
		अगर (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1)
			adjusted_घड़ी = mode->घड़ी * 2;
		अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
			radeon_crtc->pll_flags |= RADEON_PLL_PREFER_CLOSEST_LOWER;
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			radeon_crtc->pll_flags |= RADEON_PLL_IS_LCD;
	पूर्ण अन्यथा अणु
		अगर (encoder->encoder_type != DRM_MODE_ENCODER_DAC)
			radeon_crtc->pll_flags |= RADEON_PLL_NO_ODD_POST_DIV;
		अगर (encoder->encoder_type == DRM_MODE_ENCODER_LVDS)
			radeon_crtc->pll_flags |= RADEON_PLL_USE_REF_DIV;
	पूर्ण

	/* adjust pll क्रम deep color modes */
	अगर (encoder_mode == ATOM_ENCODER_MODE_HDMI) अणु
		चयन (bpc) अणु
		हाल 8:
		शेष:
			अवरोध;
		हाल 10:
			घड़ी = (घड़ी * 5) / 4;
			अवरोध;
		हाल 12:
			घड़ी = (घड़ी * 3) / 2;
			अवरोध;
		हाल 16:
			घड़ी = घड़ी * 2;
			अवरोध;
		पूर्ण
	पूर्ण

	/* DCE3+ has an AdjustDisplayPll that will adjust the pixel घड़ी
	 * accordingly based on the encoder/transmitter to work around
	 * special hw requirements.
	 */
	अगर (ASIC_IS_DCE3(rdev)) अणु
		जोड़ adjust_pixel_घड़ी args;
		u8 frev, crev;
		पूर्णांक index;

		index = GetIndexIntoMasterTable(COMMAND, AdjustDisplayPll);
		अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev,
					   &crev))
			वापस adjusted_घड़ी;

		स_रखो(&args, 0, माप(args));

		चयन (frev) अणु
		हाल 1:
			चयन (crev) अणु
			हाल 1:
			हाल 2:
				args.v1.usPixelClock = cpu_to_le16(घड़ी / 10);
				args.v1.ucTransmitterID = radeon_encoder->encoder_id;
				args.v1.ucEncodeMode = encoder_mode;
				अगर (radeon_crtc->ss_enabled && radeon_crtc->ss.percentage)
					args.v1.ucConfig |=
						ADJUST_DISPLAY_CONFIG_SS_ENABLE;

				atom_execute_table(rdev->mode_info.atom_context,
						   index, (uपूर्णांक32_t *)&args);
				adjusted_घड़ी = le16_to_cpu(args.v1.usPixelClock) * 10;
				अवरोध;
			हाल 3:
				args.v3.sInput.usPixelClock = cpu_to_le16(घड़ी / 10);
				args.v3.sInput.ucTransmitterID = radeon_encoder->encoder_id;
				args.v3.sInput.ucEncodeMode = encoder_mode;
				args.v3.sInput.ucDispPllConfig = 0;
				अगर (radeon_crtc->ss_enabled && radeon_crtc->ss.percentage)
					args.v3.sInput.ucDispPllConfig |=
						DISPPLL_CONFIG_SS_ENABLE;
				अगर (ENCODER_MODE_IS_DP(encoder_mode)) अणु
					args.v3.sInput.ucDispPllConfig |=
						DISPPLL_CONFIG_COHERENT_MODE;
					/* 16200 or 27000 */
					args.v3.sInput.usPixelClock = cpu_to_le16(dp_घड़ी / 10);
				पूर्ण अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
					काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
					अगर (dig->coherent_mode)
						args.v3.sInput.ucDispPllConfig |=
							DISPPLL_CONFIG_COHERENT_MODE;
					अगर (is_duallink)
						args.v3.sInput.ucDispPllConfig |=
							DISPPLL_CONFIG_DUAL_LINK;
				पूर्ण
				अगर (radeon_encoder_get_dp_bridge_encoder_id(encoder) !=
				    ENCODER_OBJECT_ID_NONE)
					args.v3.sInput.ucExtTransmitterID =
						radeon_encoder_get_dp_bridge_encoder_id(encoder);
				अन्यथा
					args.v3.sInput.ucExtTransmitterID = 0;

				atom_execute_table(rdev->mode_info.atom_context,
						   index, (uपूर्णांक32_t *)&args);
				adjusted_घड़ी = le32_to_cpu(args.v3.sOutput.ulDispPllFreq) * 10;
				अगर (args.v3.sOutput.ucRefDiv) अणु
					radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
					radeon_crtc->pll_flags |= RADEON_PLL_USE_REF_DIV;
					radeon_crtc->pll_reference_भाग = args.v3.sOutput.ucRefDiv;
				पूर्ण
				अगर (args.v3.sOutput.ucPostDiv) अणु
					radeon_crtc->pll_flags |= RADEON_PLL_USE_FRAC_FB_DIV;
					radeon_crtc->pll_flags |= RADEON_PLL_USE_POST_DIV;
					radeon_crtc->pll_post_भाग = args.v3.sOutput.ucPostDiv;
				पूर्ण
				अवरोध;
			शेष:
				DRM_ERROR("Unknown table version %d %d\n", frev, crev);
				वापस adjusted_घड़ी;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d %d\n", frev, crev);
			वापस adjusted_घड़ी;
		पूर्ण
	पूर्ण
	वापस adjusted_घड़ी;
पूर्ण

जोड़ set_pixel_घड़ी अणु
	SET_PIXEL_CLOCK_PS_ALLOCATION base;
	PIXEL_CLOCK_PARAMETERS v1;
	PIXEL_CLOCK_PARAMETERS_V2 v2;
	PIXEL_CLOCK_PARAMETERS_V3 v3;
	PIXEL_CLOCK_PARAMETERS_V5 v5;
	PIXEL_CLOCK_PARAMETERS_V6 v6;
पूर्ण;

/* on DCE5, make sure the voltage is high enough to support the
 * required disp clk.
 */
अटल व्योम atombios_crtc_set_disp_eng_pll(काष्ठा radeon_device *rdev,
				    u32 dispclk)
अणु
	u8 frev, crev;
	पूर्णांक index;
	जोड़ set_pixel_घड़ी args;

	स_रखो(&args, 0, माप(args));

	index = GetIndexIntoMasterTable(COMMAND, SetPixelClock);
	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev,
				   &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 5:
			/* अगर the शेष dcpll घड़ी is specअगरied,
			 * SetPixelClock provides the भागiders
			 */
			args.v5.ucCRTC = ATOM_CRTC_INVALID;
			args.v5.usPixelClock = cpu_to_le16(dispclk);
			args.v5.ucPpll = ATOM_DCPLL;
			अवरोध;
		हाल 6:
			/* अगर the शेष dcpll घड़ी is specअगरied,
			 * SetPixelClock provides the भागiders
			 */
			args.v6.ulDispEngClkFreq = cpu_to_le32(dispclk);
			अगर (ASIC_IS_DCE61(rdev) || ASIC_IS_DCE8(rdev))
				args.v6.ucPpll = ATOM_EXT_PLL1;
			अन्यथा अगर (ASIC_IS_DCE6(rdev))
				args.v6.ucPpll = ATOM_PPLL0;
			अन्यथा
				args.v6.ucPpll = ATOM_DCPLL;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d %d\n", frev, crev);
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d %d\n", frev, crev);
		वापस;
	पूर्ण
	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम atombios_crtc_program_pll(काष्ठा drm_crtc *crtc,
				      u32 crtc_id,
				      पूर्णांक pll_id,
				      u32 encoder_mode,
				      u32 encoder_id,
				      u32 घड़ी,
				      u32 ref_भाग,
				      u32 fb_भाग,
				      u32 frac_fb_भाग,
				      u32 post_भाग,
				      पूर्णांक bpc,
				      bool ss_enabled,
				      काष्ठा radeon_atom_ss *ss)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	u8 frev, crev;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetPixelClock);
	जोड़ set_pixel_घड़ी args;

	स_रखो(&args, 0, माप(args));

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev,
				   &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
			अगर (घड़ी == ATOM_DISABLE)
				वापस;
			args.v1.usPixelClock = cpu_to_le16(घड़ी / 10);
			args.v1.usRefDiv = cpu_to_le16(ref_भाग);
			args.v1.usFbDiv = cpu_to_le16(fb_भाग);
			args.v1.ucFracFbDiv = frac_fb_भाग;
			args.v1.ucPostDiv = post_भाग;
			args.v1.ucPpll = pll_id;
			args.v1.ucCRTC = crtc_id;
			args.v1.ucRefDivSrc = 1;
			अवरोध;
		हाल 2:
			args.v2.usPixelClock = cpu_to_le16(घड़ी / 10);
			args.v2.usRefDiv = cpu_to_le16(ref_भाग);
			args.v2.usFbDiv = cpu_to_le16(fb_भाग);
			args.v2.ucFracFbDiv = frac_fb_भाग;
			args.v2.ucPostDiv = post_भाग;
			args.v2.ucPpll = pll_id;
			args.v2.ucCRTC = crtc_id;
			args.v2.ucRefDivSrc = 1;
			अवरोध;
		हाल 3:
			args.v3.usPixelClock = cpu_to_le16(घड़ी / 10);
			args.v3.usRefDiv = cpu_to_le16(ref_भाग);
			args.v3.usFbDiv = cpu_to_le16(fb_भाग);
			args.v3.ucFracFbDiv = frac_fb_भाग;
			args.v3.ucPostDiv = post_भाग;
			args.v3.ucPpll = pll_id;
			अगर (crtc_id == ATOM_CRTC2)
				args.v3.ucMiscInfo = PIXEL_CLOCK_MISC_CRTC_SEL_CRTC2;
			अन्यथा
				args.v3.ucMiscInfo = PIXEL_CLOCK_MISC_CRTC_SEL_CRTC1;
			अगर (ss_enabled && (ss->type & ATOM_EXTERNAL_SS_MASK))
				args.v3.ucMiscInfo |= PIXEL_CLOCK_MISC_REF_DIV_SRC;
			args.v3.ucTransmitterId = encoder_id;
			args.v3.ucEncoderMode = encoder_mode;
			अवरोध;
		हाल 5:
			args.v5.ucCRTC = crtc_id;
			args.v5.usPixelClock = cpu_to_le16(घड़ी / 10);
			args.v5.ucRefDiv = ref_भाग;
			args.v5.usFbDiv = cpu_to_le16(fb_भाग);
			args.v5.ulFbDivDecFrac = cpu_to_le32(frac_fb_भाग * 100000);
			args.v5.ucPostDiv = post_भाग;
			args.v5.ucMiscInfo = 0; /* HDMI depth, etc. */
			अगर (ss_enabled && (ss->type & ATOM_EXTERNAL_SS_MASK))
				args.v5.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_REF_DIV_SRC;
			अगर (encoder_mode == ATOM_ENCODER_MODE_HDMI) अणु
				चयन (bpc) अणु
				हाल 8:
				शेष:
					args.v5.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_HDMI_24BPP;
					अवरोध;
				हाल 10:
					/* yes this is correct, the atom define is wrong */
					args.v5.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_HDMI_32BPP;
					अवरोध;
				हाल 12:
					/* yes this is correct, the atom define is wrong */
					args.v5.ucMiscInfo |= PIXEL_CLOCK_V5_MISC_HDMI_30BPP;
					अवरोध;
				पूर्ण
			पूर्ण
			args.v5.ucTransmitterID = encoder_id;
			args.v5.ucEncoderMode = encoder_mode;
			args.v5.ucPpll = pll_id;
			अवरोध;
		हाल 6:
			args.v6.ulDispEngClkFreq = cpu_to_le32(crtc_id << 24 | घड़ी / 10);
			args.v6.ucRefDiv = ref_भाग;
			args.v6.usFbDiv = cpu_to_le16(fb_भाग);
			args.v6.ulFbDivDecFrac = cpu_to_le32(frac_fb_भाग * 100000);
			args.v6.ucPostDiv = post_भाग;
			args.v6.ucMiscInfo = 0; /* HDMI depth, etc. */
			अगर (ss_enabled && (ss->type & ATOM_EXTERNAL_SS_MASK))
				args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_REF_DIV_SRC;
			अगर (encoder_mode == ATOM_ENCODER_MODE_HDMI) अणु
				चयन (bpc) अणु
				हाल 8:
				शेष:
					args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_24BPP;
					अवरोध;
				हाल 10:
					args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_30BPP_V6;
					अवरोध;
				हाल 12:
					args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_36BPP_V6;
					अवरोध;
				हाल 16:
					args.v6.ucMiscInfo |= PIXEL_CLOCK_V6_MISC_HDMI_48BPP;
					अवरोध;
				पूर्ण
			पूर्ण
			args.v6.ucTransmitterID = encoder_id;
			args.v6.ucEncoderMode = encoder_mode;
			args.v6.ucPpll = pll_id;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d %d\n", frev, crev);
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d %d\n", frev, crev);
		वापस;
	पूर्ण

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल bool atombios_crtc_prepare_pll(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	पूर्णांक encoder_mode = atombios_get_encoder_mode(radeon_crtc->encoder);

	radeon_crtc->bpc = 8;
	radeon_crtc->ss_enabled = false;

	अगर (radeon_encoder->is_mst_encoder) अणु
		radeon_dp_mst_prepare_pll(crtc, mode);
	पूर्ण अन्यथा अगर ((radeon_encoder->active_device & (ATOM_DEVICE_LCD_SUPPORT | ATOM_DEVICE_DFP_SUPPORT)) ||
	    (radeon_encoder_get_dp_bridge_encoder_id(radeon_crtc->encoder) != ENCODER_OBJECT_ID_NONE)) अणु
		काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
		काष्ठा drm_connector *connector =
			radeon_get_connector_क्रम_encoder(radeon_crtc->encoder);
		काष्ठा radeon_connector *radeon_connector =
			to_radeon_connector(connector);
		काष्ठा radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;
		पूर्णांक dp_घड़ी;

		/* Assign mode घड़ी क्रम hdmi deep color max घड़ी limit check */
		radeon_connector->pixelघड़ी_क्रम_modeset = mode->घड़ी;
		radeon_crtc->bpc = radeon_get_monitor_bpc(connector);

		चयन (encoder_mode) अणु
		हाल ATOM_ENCODER_MODE_DP_MST:
		हाल ATOM_ENCODER_MODE_DP:
			/* DP/eDP */
			dp_घड़ी = dig_connector->dp_घड़ी / 10;
			अगर (ASIC_IS_DCE4(rdev))
				radeon_crtc->ss_enabled =
					radeon_atombios_get_asic_ss_info(rdev, &radeon_crtc->ss,
									 ASIC_INTERNAL_SS_ON_DP,
									 dp_घड़ी);
			अन्यथा अणु
				अगर (dp_घड़ी == 16200) अणु
					radeon_crtc->ss_enabled =
						radeon_atombios_get_ppll_ss_info(rdev,
										 &radeon_crtc->ss,
										 ATOM_DP_SS_ID2);
					अगर (!radeon_crtc->ss_enabled)
						radeon_crtc->ss_enabled =
							radeon_atombios_get_ppll_ss_info(rdev,
											 &radeon_crtc->ss,
											 ATOM_DP_SS_ID1);
				पूर्ण अन्यथा अणु
					radeon_crtc->ss_enabled =
						radeon_atombios_get_ppll_ss_info(rdev,
										 &radeon_crtc->ss,
										 ATOM_DP_SS_ID1);
				पूर्ण
				/* disable spपढ़ो spectrum on DCE3 DP */
				radeon_crtc->ss_enabled = false;
			पूर्ण
			अवरोध;
		हाल ATOM_ENCODER_MODE_LVDS:
			अगर (ASIC_IS_DCE4(rdev))
				radeon_crtc->ss_enabled =
					radeon_atombios_get_asic_ss_info(rdev,
									 &radeon_crtc->ss,
									 dig->lcd_ss_id,
									 mode->घड़ी / 10);
			अन्यथा
				radeon_crtc->ss_enabled =
					radeon_atombios_get_ppll_ss_info(rdev,
									 &radeon_crtc->ss,
									 dig->lcd_ss_id);
			अवरोध;
		हाल ATOM_ENCODER_MODE_DVI:
			अगर (ASIC_IS_DCE4(rdev))
				radeon_crtc->ss_enabled =
					radeon_atombios_get_asic_ss_info(rdev,
									 &radeon_crtc->ss,
									 ASIC_INTERNAL_SS_ON_TMDS,
									 mode->घड़ी / 10);
			अवरोध;
		हाल ATOM_ENCODER_MODE_HDMI:
			अगर (ASIC_IS_DCE4(rdev))
				radeon_crtc->ss_enabled =
					radeon_atombios_get_asic_ss_info(rdev,
									 &radeon_crtc->ss,
									 ASIC_INTERNAL_SS_ON_HDMI,
									 mode->घड़ी / 10);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* adjust pixel घड़ी as needed */
	radeon_crtc->adjusted_घड़ी = atombios_adjust_pll(crtc, mode);

	वापस true;
पूर्ण

अटल व्योम atombios_crtc_set_pll(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	u32 pll_घड़ी = mode->घड़ी;
	u32 घड़ी = mode->घड़ी;
	u32 ref_भाग = 0, fb_भाग = 0, frac_fb_भाग = 0, post_भाग = 0;
	काष्ठा radeon_pll *pll;
	पूर्णांक encoder_mode = atombios_get_encoder_mode(radeon_crtc->encoder);

	/* pass the actual घड़ी to atombios_crtc_program_pll क्रम DCE5,6 क्रम HDMI */
	अगर (ASIC_IS_DCE5(rdev) &&
	    (encoder_mode == ATOM_ENCODER_MODE_HDMI) &&
	    (radeon_crtc->bpc > 8))
		घड़ी = radeon_crtc->adjusted_घड़ी;

	चयन (radeon_crtc->pll_id) अणु
	हाल ATOM_PPLL1:
		pll = &rdev->घड़ी.p1pll;
		अवरोध;
	हाल ATOM_PPLL2:
		pll = &rdev->घड़ी.p2pll;
		अवरोध;
	हाल ATOM_DCPLL:
	हाल ATOM_PPLL_INVALID:
	शेष:
		pll = &rdev->घड़ी.dcpll;
		अवरोध;
	पूर्ण

	/* update pll params */
	pll->flags = radeon_crtc->pll_flags;
	pll->reference_भाग = radeon_crtc->pll_reference_भाग;
	pll->post_भाग = radeon_crtc->pll_post_भाग;

	अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
		/* TV seems to prefer the legacy algo on some boards */
		radeon_compute_pll_legacy(pll, radeon_crtc->adjusted_घड़ी, &pll_घड़ी,
					  &fb_भाग, &frac_fb_भाग, &ref_भाग, &post_भाग);
	अन्यथा अगर (ASIC_IS_AVIVO(rdev))
		radeon_compute_pll_avivo(pll, radeon_crtc->adjusted_घड़ी, &pll_घड़ी,
					 &fb_भाग, &frac_fb_भाग, &ref_भाग, &post_भाग);
	अन्यथा
		radeon_compute_pll_legacy(pll, radeon_crtc->adjusted_घड़ी, &pll_घड़ी,
					  &fb_भाग, &frac_fb_भाग, &ref_भाग, &post_भाग);

	atombios_crtc_program_ss(rdev, ATOM_DISABLE, radeon_crtc->pll_id,
				 radeon_crtc->crtc_id, &radeon_crtc->ss);

	atombios_crtc_program_pll(crtc, radeon_crtc->crtc_id, radeon_crtc->pll_id,
				  encoder_mode, radeon_encoder->encoder_id, घड़ी,
				  ref_भाग, fb_भाग, frac_fb_भाग, post_भाग,
				  radeon_crtc->bpc, radeon_crtc->ss_enabled, &radeon_crtc->ss);

	अगर (radeon_crtc->ss_enabled) अणु
		/* calculate ss amount and step size */
		अगर (ASIC_IS_DCE4(rdev)) अणु
			u32 step_size;
			u32 amount = (((fb_भाग * 10) + frac_fb_भाग) *
				      (u32)radeon_crtc->ss.percentage) /
				(100 * (u32)radeon_crtc->ss.percentage_भागider);
			radeon_crtc->ss.amount = (amount / 10) & ATOM_PPLL_SS_AMOUNT_V2_FBDIV_MASK;
			radeon_crtc->ss.amount |= ((amount - (amount / 10)) << ATOM_PPLL_SS_AMOUNT_V2_NFRAC_SHIFT) &
				ATOM_PPLL_SS_AMOUNT_V2_NFRAC_MASK;
			अगर (radeon_crtc->ss.type & ATOM_PPLL_SS_TYPE_V2_CENTRE_SPREAD)
				step_size = (4 * amount * ref_भाग * ((u32)radeon_crtc->ss.rate * 2048)) /
					(125 * 25 * pll->reference_freq / 100);
			अन्यथा
				step_size = (2 * amount * ref_भाग * ((u32)radeon_crtc->ss.rate * 2048)) /
					(125 * 25 * pll->reference_freq / 100);
			radeon_crtc->ss.step = step_size;
		पूर्ण

		atombios_crtc_program_ss(rdev, ATOM_ENABLE, radeon_crtc->pll_id,
					 radeon_crtc->crtc_id, &radeon_crtc->ss);
	पूर्ण
पूर्ण

अटल पूर्णांक dce4_crtc_करो_set_base(काष्ठा drm_crtc *crtc,
				 काष्ठा drm_framebuffer *fb,
				 पूर्णांक x, पूर्णांक y, पूर्णांक atomic)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_framebuffer *target_fb;
	काष्ठा drm_gem_object *obj;
	काष्ठा radeon_bo *rbo;
	uपूर्णांक64_t fb_location;
	uपूर्णांक32_t fb_क्रमmat, fb_pitch_pixels, tiling_flags;
	अचिन्हित bankw, bankh, mtaspect, tile_split;
	u32 fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_NONE);
	u32 पंचांगp, viewport_w, viewport_h;
	पूर्णांक r;
	bool bypass_lut = false;

	/* no fb bound */
	अगर (!atomic && !crtc->primary->fb) अणु
		DRM_DEBUG_KMS("No FB bound\n");
		वापस 0;
	पूर्ण

	अगर (atomic)
		target_fb = fb;
	अन्यथा
		target_fb = crtc->primary->fb;

	/* If atomic, assume fb object is pinned & idle & fenced and
	 * just update base poपूर्णांकers
	 */
	obj = target_fb->obj[0];
	rbo = gem_to_radeon_bo(obj);
	r = radeon_bo_reserve(rbo, false);
	अगर (unlikely(r != 0))
		वापस r;

	अगर (atomic)
		fb_location = radeon_bo_gpu_offset(rbo);
	अन्यथा अणु
		r = radeon_bo_pin(rbo, RADEON_GEM_DOMAIN_VRAM, &fb_location);
		अगर (unlikely(r != 0)) अणु
			radeon_bo_unreserve(rbo);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	radeon_bo_get_tiling_flags(rbo, &tiling_flags, शून्य);
	radeon_bo_unreserve(rbo);

	चयन (target_fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_8BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_INDEXED));
		अवरोध;
	हाल DRM_FORMAT_XRGB4444:
	हाल DRM_FORMAT_ARGB4444:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_16BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB4444));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN16);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_ARGB1555:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_16BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB1555));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN16);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_BGRX5551:
	हाल DRM_FORMAT_BGRA5551:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_16BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_BGRA5551));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN16);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_16BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB565));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN16);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_32BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB8888));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN32);
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_ARGB2101010:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_32BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB2101010));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN32);
#पूर्ण_अगर
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		अवरोध;
	हाल DRM_FORMAT_BGRX1010102:
	हाल DRM_FORMAT_BGRA1010102:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_32BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_BGRA1010102));
#अगर_घोषित __BIG_ENDIAN
		fb_swap = EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN32);
#पूर्ण_अगर
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		fb_क्रमmat = (EVERGREEN_GRPH_DEPTH(EVERGREEN_GRPH_DEPTH_32BPP) |
			     EVERGREEN_GRPH_FORMAT(EVERGREEN_GRPH_FORMAT_ARGB8888));
		fb_swap = (EVERGREEN_GRPH_RED_CROSSBAR(EVERGREEN_GRPH_RED_SEL_B) |
			   EVERGREEN_GRPH_BLUE_CROSSBAR(EVERGREEN_GRPH_BLUE_SEL_R));
#अगर_घोषित __BIG_ENDIAN
		fb_swap |= EVERGREEN_GRPH_ENDIAN_SWAP(EVERGREEN_GRPH_ENDIAN_8IN32);
#पूर्ण_अगर
		अवरोध;
	शेष:
		DRM_ERROR("Unsupported screen format %p4cc\n",
			  &target_fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (tiling_flags & RADEON_TILING_MACRO) अणु
		evergreen_tiling_fields(tiling_flags, &bankw, &bankh, &mtaspect, &tile_split);

		/* Set NUM_BANKS. */
		अगर (rdev->family >= CHIP_TAHITI) अणु
			अचिन्हित index, num_banks;

			अगर (rdev->family >= CHIP_BONAIRE) अणु
				अचिन्हित tileb, tile_split_bytes;

				/* Calculate the macrotile mode index. */
				tile_split_bytes = 64 << tile_split;
				tileb = 8 * 8 * target_fb->क्रमmat->cpp[0];
				tileb = min(tile_split_bytes, tileb);

				क्रम (index = 0; tileb > 64; index++)
					tileb >>= 1;

				अगर (index >= 16) अणु
					DRM_ERROR("Wrong screen bpp (%u) or tile split (%u)\n",
						  target_fb->क्रमmat->cpp[0] * 8,
						  tile_split);
					वापस -EINVAL;
				पूर्ण

				num_banks = (rdev->config.cik.macrotile_mode_array[index] >> 6) & 0x3;
			पूर्ण अन्यथा अणु
				चयन (target_fb->क्रमmat->cpp[0] * 8) अणु
				हाल 8:
					index = 10;
					अवरोध;
				हाल 16:
					index = SI_TILE_MODE_COLOR_2D_SCANOUT_16BPP;
					अवरोध;
				शेष:
				हाल 32:
					index = SI_TILE_MODE_COLOR_2D_SCANOUT_32BPP;
					अवरोध;
				पूर्ण

				num_banks = (rdev->config.si.tile_mode_array[index] >> 20) & 0x3;
			पूर्ण

			fb_क्रमmat |= EVERGREEN_GRPH_NUM_BANKS(num_banks);
		पूर्ण अन्यथा अणु
			/* NI and older. */
			अगर (rdev->family >= CHIP_CAYMAN)
				पंचांगp = rdev->config.cayman.tile_config;
			अन्यथा
				पंचांगp = rdev->config.evergreen.tile_config;

			चयन ((पंचांगp & 0xf0) >> 4) अणु
			हाल 0: /* 4 banks */
				fb_क्रमmat |= EVERGREEN_GRPH_NUM_BANKS(EVERGREEN_ADDR_SURF_4_BANK);
				अवरोध;
			हाल 1: /* 8 banks */
			शेष:
				fb_क्रमmat |= EVERGREEN_GRPH_NUM_BANKS(EVERGREEN_ADDR_SURF_8_BANK);
				अवरोध;
			हाल 2: /* 16 banks */
				fb_क्रमmat |= EVERGREEN_GRPH_NUM_BANKS(EVERGREEN_ADDR_SURF_16_BANK);
				अवरोध;
			पूर्ण
		पूर्ण

		fb_क्रमmat |= EVERGREEN_GRPH_ARRAY_MODE(EVERGREEN_GRPH_ARRAY_2D_TILED_THIN1);
		fb_क्रमmat |= EVERGREEN_GRPH_TILE_SPLIT(tile_split);
		fb_क्रमmat |= EVERGREEN_GRPH_BANK_WIDTH(bankw);
		fb_क्रमmat |= EVERGREEN_GRPH_BANK_HEIGHT(bankh);
		fb_क्रमmat |= EVERGREEN_GRPH_MACRO_TILE_ASPECT(mtaspect);
		अगर (rdev->family >= CHIP_BONAIRE) अणु
			/* XXX need to know more about the surface tiling mode */
			fb_क्रमmat |= CIK_GRPH_MICRO_TILE_MODE(CIK_DISPLAY_MICRO_TILING);
		पूर्ण
	पूर्ण अन्यथा अगर (tiling_flags & RADEON_TILING_MICRO)
		fb_क्रमmat |= EVERGREEN_GRPH_ARRAY_MODE(EVERGREEN_GRPH_ARRAY_1D_TILED_THIN1);

	अगर (rdev->family >= CHIP_BONAIRE) अणु
		/* Read the pipe config from the 2D TILED SCANOUT mode.
		 * It should be the same क्रम the other modes too, but not all
		 * modes set the pipe config field. */
		u32 pipe_config = (rdev->config.cik.tile_mode_array[10] >> 6) & 0x1f;

		fb_क्रमmat |= CIK_GRPH_PIPE_CONFIG(pipe_config);
	पूर्ण अन्यथा अगर ((rdev->family == CHIP_TAHITI) ||
		   (rdev->family == CHIP_PITCAIRN))
		fb_क्रमmat |= SI_GRPH_PIPE_CONFIG(SI_ADDR_SURF_P8_32x32_8x16);
	अन्यथा अगर ((rdev->family == CHIP_VERDE) ||
		 (rdev->family == CHIP_OLAND) ||
		 (rdev->family == CHIP_HAIन_अंक)) /* क्रम completeness.  HAIन_अंक has no display hw */
		fb_क्रमmat |= SI_GRPH_PIPE_CONFIG(SI_ADDR_SURF_P4_8x16);

	चयन (radeon_crtc->crtc_id) अणु
	हाल 0:
		WREG32(AVIVO_D1VGA_CONTROL, 0);
		अवरोध;
	हाल 1:
		WREG32(AVIVO_D2VGA_CONTROL, 0);
		अवरोध;
	हाल 2:
		WREG32(EVERGREEN_D3VGA_CONTROL, 0);
		अवरोध;
	हाल 3:
		WREG32(EVERGREEN_D4VGA_CONTROL, 0);
		अवरोध;
	हाल 4:
		WREG32(EVERGREEN_D5VGA_CONTROL, 0);
		अवरोध;
	हाल 5:
		WREG32(EVERGREEN_D6VGA_CONTROL, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Make sure surface address is updated at vertical blank rather than
	 * horizontal blank
	 */
	WREG32(EVERGREEN_GRPH_FLIP_CONTROL + radeon_crtc->crtc_offset, 0);

	WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH + radeon_crtc->crtc_offset,
	       upper_32_bits(fb_location));
	WREG32(EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH + radeon_crtc->crtc_offset,
	       upper_32_bits(fb_location));
	WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32)fb_location & EVERGREEN_GRPH_SURFACE_ADDRESS_MASK);
	WREG32(EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32) fb_location & EVERGREEN_GRPH_SURFACE_ADDRESS_MASK);
	WREG32(EVERGREEN_GRPH_CONTROL + radeon_crtc->crtc_offset, fb_क्रमmat);
	WREG32(EVERGREEN_GRPH_SWAP_CONTROL + radeon_crtc->crtc_offset, fb_swap);

	/*
	 * The LUT only has 256 slots क्रम indexing by a 8 bpc fb. Bypass the LUT
	 * क्रम > 8 bpc scanout to aव्योम truncation of fb indices to 8 msb's, to
	 * retain the full precision throughout the pipeline.
	 */
	WREG32_P(EVERGREEN_GRPH_LUT_10BIT_BYPASS_CONTROL + radeon_crtc->crtc_offset,
		 (bypass_lut ? EVERGREEN_LUT_10BIT_BYPASS_EN : 0),
		 ~EVERGREEN_LUT_10BIT_BYPASS_EN);

	अगर (bypass_lut)
		DRM_DEBUG_KMS("Bypassing hardware LUT due to 10 bit fb scanout.\n");

	WREG32(EVERGREEN_GRPH_SURFACE_OFFSET_X + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_GRPH_SURFACE_OFFSET_Y + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_GRPH_X_START + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_GRPH_Y_START + radeon_crtc->crtc_offset, 0);
	WREG32(EVERGREEN_GRPH_X_END + radeon_crtc->crtc_offset, target_fb->width);
	WREG32(EVERGREEN_GRPH_Y_END + radeon_crtc->crtc_offset, target_fb->height);

	fb_pitch_pixels = target_fb->pitches[0] / target_fb->क्रमmat->cpp[0];
	WREG32(EVERGREEN_GRPH_PITCH + radeon_crtc->crtc_offset, fb_pitch_pixels);
	WREG32(EVERGREEN_GRPH_ENABLE + radeon_crtc->crtc_offset, 1);

	अगर (rdev->family >= CHIP_BONAIRE)
		WREG32(CIK_LB_DESKTOP_HEIGHT + radeon_crtc->crtc_offset,
		       target_fb->height);
	अन्यथा
		WREG32(EVERGREEN_DESKTOP_HEIGHT + radeon_crtc->crtc_offset,
		       target_fb->height);
	x &= ~3;
	y &= ~1;
	WREG32(EVERGREEN_VIEWPORT_START + radeon_crtc->crtc_offset,
	       (x << 16) | y);
	viewport_w = crtc->mode.hdisplay;
	viewport_h = (crtc->mode.vdisplay + 1) & ~1;
	अगर ((rdev->family >= CHIP_BONAIRE) &&
	    (crtc->mode.flags & DRM_MODE_FLAG_INTERLACE))
		viewport_h *= 2;
	WREG32(EVERGREEN_VIEWPORT_SIZE + radeon_crtc->crtc_offset,
	       (viewport_w << 16) | viewport_h);

	/* set pageflip to happen anywhere in vblank पूर्णांकerval */
	WREG32(EVERGREEN_MASTER_UPDATE_MODE + radeon_crtc->crtc_offset, 0);

	अगर (!atomic && fb && fb != crtc->primary->fb) अणु
		rbo = gem_to_radeon_bo(fb->obj[0]);
		r = radeon_bo_reserve(rbo, false);
		अगर (unlikely(r != 0))
			वापस r;
		radeon_bo_unpin(rbo);
		radeon_bo_unreserve(rbo);
	पूर्ण

	/* Bytes per pixel may have changed */
	radeon_bandwidth_update(rdev);

	वापस 0;
पूर्ण

अटल पूर्णांक avivo_crtc_करो_set_base(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_framebuffer *fb,
				  पूर्णांक x, पूर्णांक y, पूर्णांक atomic)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_gem_object *obj;
	काष्ठा radeon_bo *rbo;
	काष्ठा drm_framebuffer *target_fb;
	uपूर्णांक64_t fb_location;
	uपूर्णांक32_t fb_क्रमmat, fb_pitch_pixels, tiling_flags;
	u32 fb_swap = R600_D1GRPH_SWAP_ENDIAN_NONE;
	u32 viewport_w, viewport_h;
	पूर्णांक r;
	bool bypass_lut = false;

	/* no fb bound */
	अगर (!atomic && !crtc->primary->fb) अणु
		DRM_DEBUG_KMS("No FB bound\n");
		वापस 0;
	पूर्ण

	अगर (atomic)
		target_fb = fb;
	अन्यथा
		target_fb = crtc->primary->fb;

	obj = target_fb->obj[0];
	rbo = gem_to_radeon_bo(obj);
	r = radeon_bo_reserve(rbo, false);
	अगर (unlikely(r != 0))
		वापस r;

	/* If atomic, assume fb object is pinned & idle & fenced and
	 * just update base poपूर्णांकers
	 */
	अगर (atomic)
		fb_location = radeon_bo_gpu_offset(rbo);
	अन्यथा अणु
		r = radeon_bo_pin(rbo, RADEON_GEM_DOMAIN_VRAM, &fb_location);
		अगर (unlikely(r != 0)) अणु
			radeon_bo_unreserve(rbo);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	radeon_bo_get_tiling_flags(rbo, &tiling_flags, शून्य);
	radeon_bo_unreserve(rbo);

	चयन (target_fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		fb_क्रमmat =
		    AVIVO_D1GRPH_CONTROL_DEPTH_8BPP |
		    AVIVO_D1GRPH_CONTROL_8BPP_INDEXED;
		अवरोध;
	हाल DRM_FORMAT_XRGB4444:
	हाल DRM_FORMAT_ARGB4444:
		fb_क्रमmat =
		    AVIVO_D1GRPH_CONTROL_DEPTH_16BPP |
		    AVIVO_D1GRPH_CONTROL_16BPP_ARGB4444;
#अगर_घोषित __BIG_ENDIAN
		fb_swap = R600_D1GRPH_SWAP_ENDIAN_16BIT;
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		fb_क्रमmat =
		    AVIVO_D1GRPH_CONTROL_DEPTH_16BPP |
		    AVIVO_D1GRPH_CONTROL_16BPP_ARGB1555;
#अगर_घोषित __BIG_ENDIAN
		fb_swap = R600_D1GRPH_SWAP_ENDIAN_16BIT;
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		fb_क्रमmat =
		    AVIVO_D1GRPH_CONTROL_DEPTH_16BPP |
		    AVIVO_D1GRPH_CONTROL_16BPP_RGB565;
#अगर_घोषित __BIG_ENDIAN
		fb_swap = R600_D1GRPH_SWAP_ENDIAN_16BIT;
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		fb_क्रमmat =
		    AVIVO_D1GRPH_CONTROL_DEPTH_32BPP |
		    AVIVO_D1GRPH_CONTROL_32BPP_ARGB8888;
#अगर_घोषित __BIG_ENDIAN
		fb_swap = R600_D1GRPH_SWAP_ENDIAN_32BIT;
#पूर्ण_अगर
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_ARGB2101010:
		fb_क्रमmat =
		    AVIVO_D1GRPH_CONTROL_DEPTH_32BPP |
		    AVIVO_D1GRPH_CONTROL_32BPP_ARGB2101010;
#अगर_घोषित __BIG_ENDIAN
		fb_swap = R600_D1GRPH_SWAP_ENDIAN_32BIT;
#पूर्ण_अगर
		/* Greater 8 bpc fb needs to bypass hw-lut to retain precision */
		bypass_lut = true;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		fb_क्रमmat =
		    AVIVO_D1GRPH_CONTROL_DEPTH_32BPP |
		    AVIVO_D1GRPH_CONTROL_32BPP_ARGB8888;
		अगर (rdev->family >= CHIP_R600)
			fb_swap =
			    (R600_D1GRPH_RED_CROSSBAR(R600_D1GRPH_RED_SEL_B) |
			     R600_D1GRPH_BLUE_CROSSBAR(R600_D1GRPH_BLUE_SEL_R));
		अन्यथा /* DCE1 (R5xx) */
			fb_क्रमmat |= AVIVO_D1GRPH_SWAP_RB;
#अगर_घोषित __BIG_ENDIAN
		fb_swap |= R600_D1GRPH_SWAP_ENDIAN_32BIT;
#पूर्ण_अगर
		अवरोध;
	शेष:
		DRM_ERROR("Unsupported screen format %p4cc\n",
			  &target_fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (rdev->family >= CHIP_R600) अणु
		अगर (tiling_flags & RADEON_TILING_MACRO)
			fb_क्रमmat |= R600_D1GRPH_ARRAY_MODE_2D_TILED_THIN1;
		अन्यथा अगर (tiling_flags & RADEON_TILING_MICRO)
			fb_क्रमmat |= R600_D1GRPH_ARRAY_MODE_1D_TILED_THIN1;
	पूर्ण अन्यथा अणु
		अगर (tiling_flags & RADEON_TILING_MACRO)
			fb_क्रमmat |= AVIVO_D1GRPH_MACRO_ADDRESS_MODE;

		अगर (tiling_flags & RADEON_TILING_MICRO)
			fb_क्रमmat |= AVIVO_D1GRPH_TILED;
	पूर्ण

	अगर (radeon_crtc->crtc_id == 0)
		WREG32(AVIVO_D1VGA_CONTROL, 0);
	अन्यथा
		WREG32(AVIVO_D2VGA_CONTROL, 0);

	/* Make sure surface address is update at vertical blank rather than
	 * horizontal blank
	 */
	WREG32(AVIVO_D1GRPH_FLIP_CONTROL + radeon_crtc->crtc_offset, 0);

	अगर (rdev->family >= CHIP_RV770) अणु
		अगर (radeon_crtc->crtc_id) अणु
			WREG32(R700_D2GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, upper_32_bits(fb_location));
			WREG32(R700_D2GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, upper_32_bits(fb_location));
		पूर्ण अन्यथा अणु
			WREG32(R700_D1GRPH_PRIMARY_SURFACE_ADDRESS_HIGH, upper_32_bits(fb_location));
			WREG32(R700_D1GRPH_SECONDARY_SURFACE_ADDRESS_HIGH, upper_32_bits(fb_location));
		पूर्ण
	पूर्ण
	WREG32(AVIVO_D1GRPH_PRIMARY_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
	       (u32) fb_location);
	WREG32(AVIVO_D1GRPH_SECONDARY_SURFACE_ADDRESS +
	       radeon_crtc->crtc_offset, (u32) fb_location);
	WREG32(AVIVO_D1GRPH_CONTROL + radeon_crtc->crtc_offset, fb_क्रमmat);
	अगर (rdev->family >= CHIP_R600)
		WREG32(R600_D1GRPH_SWAP_CONTROL + radeon_crtc->crtc_offset, fb_swap);

	/* LUT only has 256 slots क्रम 8 bpc fb. Bypass क्रम > 8 bpc scanout क्रम precision */
	WREG32_P(AVIVO_D1GRPH_LUT_SEL + radeon_crtc->crtc_offset,
		 (bypass_lut ? AVIVO_LUT_10BIT_BYPASS_EN : 0), ~AVIVO_LUT_10BIT_BYPASS_EN);

	अगर (bypass_lut)
		DRM_DEBUG_KMS("Bypassing hardware LUT due to 10 bit fb scanout.\n");

	WREG32(AVIVO_D1GRPH_SURFACE_OFFSET_X + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_D1GRPH_SURFACE_OFFSET_Y + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_D1GRPH_X_START + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_D1GRPH_Y_START + radeon_crtc->crtc_offset, 0);
	WREG32(AVIVO_D1GRPH_X_END + radeon_crtc->crtc_offset, target_fb->width);
	WREG32(AVIVO_D1GRPH_Y_END + radeon_crtc->crtc_offset, target_fb->height);

	fb_pitch_pixels = target_fb->pitches[0] / target_fb->क्रमmat->cpp[0];
	WREG32(AVIVO_D1GRPH_PITCH + radeon_crtc->crtc_offset, fb_pitch_pixels);
	WREG32(AVIVO_D1GRPH_ENABLE + radeon_crtc->crtc_offset, 1);

	WREG32(AVIVO_D1MODE_DESKTOP_HEIGHT + radeon_crtc->crtc_offset,
	       target_fb->height);
	x &= ~3;
	y &= ~1;
	WREG32(AVIVO_D1MODE_VIEWPORT_START + radeon_crtc->crtc_offset,
	       (x << 16) | y);
	viewport_w = crtc->mode.hdisplay;
	viewport_h = (crtc->mode.vdisplay + 1) & ~1;
	WREG32(AVIVO_D1MODE_VIEWPORT_SIZE + radeon_crtc->crtc_offset,
	       (viewport_w << 16) | viewport_h);

	/* set pageflip to happen only at start of vblank पूर्णांकerval (front porch) */
	WREG32(AVIVO_D1MODE_MASTER_UPDATE_MODE + radeon_crtc->crtc_offset, 3);

	अगर (!atomic && fb && fb != crtc->primary->fb) अणु
		rbo = gem_to_radeon_bo(fb->obj[0]);
		r = radeon_bo_reserve(rbo, false);
		अगर (unlikely(r != 0))
			वापस r;
		radeon_bo_unpin(rbo);
		radeon_bo_unreserve(rbo);
	पूर्ण

	/* Bytes per pixel may have changed */
	radeon_bandwidth_update(rdev);

	वापस 0;
पूर्ण

पूर्णांक atombios_crtc_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
			   काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (ASIC_IS_DCE4(rdev))
		वापस dce4_crtc_करो_set_base(crtc, old_fb, x, y, 0);
	अन्यथा अगर (ASIC_IS_AVIVO(rdev))
		वापस avivo_crtc_करो_set_base(crtc, old_fb, x, y, 0);
	अन्यथा
		वापस radeon_crtc_करो_set_base(crtc, old_fb, x, y, 0);
पूर्ण

पूर्णांक atombios_crtc_set_base_atomic(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_framebuffer *fb,
				  पूर्णांक x, पूर्णांक y, क्रमागत mode_set_atomic state)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (ASIC_IS_DCE4(rdev))
		वापस dce4_crtc_करो_set_base(crtc, fb, x, y, 1);
	अन्यथा अगर (ASIC_IS_AVIVO(rdev))
		वापस avivo_crtc_करो_set_base(crtc, fb, x, y, 1);
	अन्यथा
		वापस radeon_crtc_करो_set_base(crtc, fb, x, y, 1);
पूर्ण

/* properly set additional regs when using atombios */
अटल व्योम radeon_legacy_atom_fixup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	u32 disp_merge_cntl;

	चयन (radeon_crtc->crtc_id) अणु
	हाल 0:
		disp_merge_cntl = RREG32(RADEON_DISP_MERGE_CNTL);
		disp_merge_cntl &= ~RADEON_DISP_RGB_OFFSET_EN;
		WREG32(RADEON_DISP_MERGE_CNTL, disp_merge_cntl);
		अवरोध;
	हाल 1:
		disp_merge_cntl = RREG32(RADEON_DISP2_MERGE_CNTL);
		disp_merge_cntl &= ~RADEON_DISP2_RGB_OFFSET_EN;
		WREG32(RADEON_DISP2_MERGE_CNTL, disp_merge_cntl);
		WREG32(RADEON_FP_H2_SYNC_STRT_WID,   RREG32(RADEON_CRTC2_H_SYNC_STRT_WID));
		WREG32(RADEON_FP_V2_SYNC_STRT_WID,   RREG32(RADEON_CRTC2_V_SYNC_STRT_WID));
		अवरोध;
	पूर्ण
पूर्ण

/**
 * radeon_get_pll_use_mask - look up a mask of which pplls are in use
 *
 * @crtc: drm crtc
 *
 * Returns the mask of which PPLLs (Pixel PLLs) are in use.
 */
अटल u32 radeon_get_pll_use_mask(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_crtc *test_crtc;
	काष्ठा radeon_crtc *test_radeon_crtc;
	u32 pll_in_use = 0;

	list_क्रम_each_entry(test_crtc, &dev->mode_config.crtc_list, head) अणु
		अगर (crtc == test_crtc)
			जारी;

		test_radeon_crtc = to_radeon_crtc(test_crtc);
		अगर (test_radeon_crtc->pll_id != ATOM_PPLL_INVALID)
			pll_in_use |= (1 << test_radeon_crtc->pll_id);
	पूर्ण
	वापस pll_in_use;
पूर्ण

/**
 * radeon_get_shared_dp_ppll - वापस the PPLL used by another crtc क्रम DP
 *
 * @crtc: drm crtc
 *
 * Returns the PPLL (Pixel PLL) used by another crtc/encoder which is
 * also in DP mode.  For DP, a single PPLL can be used क्रम all DP
 * crtcs/encoders.
 */
अटल पूर्णांक radeon_get_shared_dp_ppll(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_crtc *test_crtc;
	काष्ठा radeon_crtc *test_radeon_crtc;

	list_क्रम_each_entry(test_crtc, &dev->mode_config.crtc_list, head) अणु
		अगर (crtc == test_crtc)
			जारी;
		test_radeon_crtc = to_radeon_crtc(test_crtc);
		अगर (test_radeon_crtc->encoder &&
		    ENCODER_MODE_IS_DP(atombios_get_encoder_mode(test_radeon_crtc->encoder))) अणु
			/* PPLL2 is exclusive to UNIPHYA on DCE61 */
			अगर (ASIC_IS_DCE61(rdev) && !ASIC_IS_DCE8(rdev) &&
			    test_radeon_crtc->pll_id == ATOM_PPLL2)
				जारी;
			/* क्रम DP use the same PLL क्रम all */
			अगर (test_radeon_crtc->pll_id != ATOM_PPLL_INVALID)
				वापस test_radeon_crtc->pll_id;
		पूर्ण
	पूर्ण
	वापस ATOM_PPLL_INVALID;
पूर्ण

/**
 * radeon_get_shared_nondp_ppll - वापस the PPLL used by another non-DP crtc
 *
 * @crtc: drm crtc
 *
 * Returns the PPLL (Pixel PLL) used by another non-DP crtc/encoder which can
 * be shared (i.e., same घड़ी).
 */
अटल पूर्णांक radeon_get_shared_nondp_ppll(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_crtc *test_crtc;
	काष्ठा radeon_crtc *test_radeon_crtc;
	u32 adjusted_घड़ी, test_adjusted_घड़ी;

	adjusted_घड़ी = radeon_crtc->adjusted_घड़ी;

	अगर (adjusted_घड़ी == 0)
		वापस ATOM_PPLL_INVALID;

	list_क्रम_each_entry(test_crtc, &dev->mode_config.crtc_list, head) अणु
		अगर (crtc == test_crtc)
			जारी;
		test_radeon_crtc = to_radeon_crtc(test_crtc);
		अगर (test_radeon_crtc->encoder &&
		    !ENCODER_MODE_IS_DP(atombios_get_encoder_mode(test_radeon_crtc->encoder))) अणु
			/* PPLL2 is exclusive to UNIPHYA on DCE61 */
			अगर (ASIC_IS_DCE61(rdev) && !ASIC_IS_DCE8(rdev) &&
			    test_radeon_crtc->pll_id == ATOM_PPLL2)
				जारी;
			/* check अगर we are alपढ़ोy driving this connector with another crtc */
			अगर (test_radeon_crtc->connector == radeon_crtc->connector) अणु
				/* अगर we are, वापस that pll */
				अगर (test_radeon_crtc->pll_id != ATOM_PPLL_INVALID)
					वापस test_radeon_crtc->pll_id;
			पूर्ण
			/* क्रम non-DP check the घड़ी */
			test_adjusted_घड़ी = test_radeon_crtc->adjusted_घड़ी;
			अगर ((crtc->mode.घड़ी == test_crtc->mode.घड़ी) &&
			    (adjusted_घड़ी == test_adjusted_घड़ी) &&
			    (radeon_crtc->ss_enabled == test_radeon_crtc->ss_enabled) &&
			    (test_radeon_crtc->pll_id != ATOM_PPLL_INVALID))
				वापस test_radeon_crtc->pll_id;
		पूर्ण
	पूर्ण
	वापस ATOM_PPLL_INVALID;
पूर्ण

/**
 * radeon_atom_pick_pll - Allocate a PPLL क्रम use by the crtc.
 *
 * @crtc: drm crtc
 *
 * Returns the PPLL (Pixel PLL) to be used by the crtc.  For DP monitors
 * a single PPLL can be used क्रम all DP crtcs/encoders.  For non-DP
 * monitors a dedicated PPLL must be used.  If a particular board has
 * an बाह्यal DP PLL, वापस ATOM_PPLL_INVALID to skip PLL programming
 * as there is no need to program the PLL itself.  If we are not able to
 * allocate a PLL, वापस ATOM_PPLL_INVALID to skip PLL programming to
 * aव्योम messing up an existing monitor.
 *
 * Asic specअगरic PLL inक्रमmation
 *
 * DCE 8.x
 * KB/KV
 * - PPLL1, PPLL2 are available क्रम all UNIPHY (both DP and non-DP)
 * CI
 * - PPLL0, PPLL1, PPLL2 are available क्रम all UNIPHY (both DP and non-DP) and DAC
 *
 * DCE 6.1
 * - PPLL2 is only available to UNIPHYA (both DP and non-DP)
 * - PPLL0, PPLL1 are available क्रम UNIPHYB/C/D/E/F (both DP and non-DP)
 *
 * DCE 6.0
 * - PPLL0 is available to all UNIPHY (DP only)
 * - PPLL1, PPLL2 are available क्रम all UNIPHY (both DP and non-DP) and DAC
 *
 * DCE 5.0
 * - DCPLL is available to all UNIPHY (DP only)
 * - PPLL1, PPLL2 are available क्रम all UNIPHY (both DP and non-DP) and DAC
 *
 * DCE 3.0/4.0/4.1
 * - PPLL1, PPLL2 are available क्रम all UNIPHY (both DP and non-DP) and DAC
 *
 */
अटल पूर्णांक radeon_atom_pick_pll(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	u32 pll_in_use;
	पूर्णांक pll;

	अगर (ASIC_IS_DCE8(rdev)) अणु
		अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder))) अणु
			अगर (rdev->घड़ी.dp_extclk)
				/* skip PPLL programming अगर using ext घड़ी */
				वापस ATOM_PPLL_INVALID;
			अन्यथा अणु
				/* use the same PPLL क्रम all DP monitors */
				pll = radeon_get_shared_dp_ppll(crtc);
				अगर (pll != ATOM_PPLL_INVALID)
					वापस pll;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* use the same PPLL क्रम all monitors with the same घड़ी */
			pll = radeon_get_shared_nondp_ppll(crtc);
			अगर (pll != ATOM_PPLL_INVALID)
				वापस pll;
		पूर्ण
		/* otherwise, pick one of the plls */
		अगर ((rdev->family == CHIP_KABINI) ||
		    (rdev->family == CHIP_MULLINS)) अणु
			/* KB/ML has PPLL1 and PPLL2 */
			pll_in_use = radeon_get_pll_use_mask(crtc);
			अगर (!(pll_in_use & (1 << ATOM_PPLL2)))
				वापस ATOM_PPLL2;
			अगर (!(pll_in_use & (1 << ATOM_PPLL1)))
				वापस ATOM_PPLL1;
			DRM_ERROR("unable to allocate a PPLL\n");
			वापस ATOM_PPLL_INVALID;
		पूर्ण अन्यथा अणु
			/* CI/KV has PPLL0, PPLL1, and PPLL2 */
			pll_in_use = radeon_get_pll_use_mask(crtc);
			अगर (!(pll_in_use & (1 << ATOM_PPLL2)))
				वापस ATOM_PPLL2;
			अगर (!(pll_in_use & (1 << ATOM_PPLL1)))
				वापस ATOM_PPLL1;
			अगर (!(pll_in_use & (1 << ATOM_PPLL0)))
				वापस ATOM_PPLL0;
			DRM_ERROR("unable to allocate a PPLL\n");
			वापस ATOM_PPLL_INVALID;
		पूर्ण
	पूर्ण अन्यथा अगर (ASIC_IS_DCE61(rdev)) अणु
		काष्ठा radeon_encoder_atom_dig *dig =
			radeon_encoder->enc_priv;

		अगर ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_UNIPHY) &&
		    (dig->linkb == false))
			/* UNIPHY A uses PPLL2 */
			वापस ATOM_PPLL2;
		अन्यथा अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder))) अणु
			/* UNIPHY B/C/D/E/F */
			अगर (rdev->घड़ी.dp_extclk)
				/* skip PPLL programming अगर using ext घड़ी */
				वापस ATOM_PPLL_INVALID;
			अन्यथा अणु
				/* use the same PPLL क्रम all DP monitors */
				pll = radeon_get_shared_dp_ppll(crtc);
				अगर (pll != ATOM_PPLL_INVALID)
					वापस pll;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* use the same PPLL क्रम all monitors with the same घड़ी */
			pll = radeon_get_shared_nondp_ppll(crtc);
			अगर (pll != ATOM_PPLL_INVALID)
				वापस pll;
		पूर्ण
		/* UNIPHY B/C/D/E/F */
		pll_in_use = radeon_get_pll_use_mask(crtc);
		अगर (!(pll_in_use & (1 << ATOM_PPLL0)))
			वापस ATOM_PPLL0;
		अगर (!(pll_in_use & (1 << ATOM_PPLL1)))
			वापस ATOM_PPLL1;
		DRM_ERROR("unable to allocate a PPLL\n");
		वापस ATOM_PPLL_INVALID;
	पूर्ण अन्यथा अगर (ASIC_IS_DCE41(rdev)) अणु
		/* Don't share PLLs on DCE4.1 chips */
		अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder))) अणु
			अगर (rdev->घड़ी.dp_extclk)
				/* skip PPLL programming अगर using ext घड़ी */
				वापस ATOM_PPLL_INVALID;
		पूर्ण
		pll_in_use = radeon_get_pll_use_mask(crtc);
		अगर (!(pll_in_use & (1 << ATOM_PPLL1)))
			वापस ATOM_PPLL1;
		अगर (!(pll_in_use & (1 << ATOM_PPLL2)))
			वापस ATOM_PPLL2;
		DRM_ERROR("unable to allocate a PPLL\n");
		वापस ATOM_PPLL_INVALID;
	पूर्ण अन्यथा अगर (ASIC_IS_DCE4(rdev)) अणु
		/* in DP mode, the DP ref घड़ी can come from PPLL, DCPLL, or ext घड़ी,
		 * depending on the asic:
		 * DCE4: PPLL or ext घड़ी
		 * DCE5: PPLL, DCPLL, or ext घड़ी
		 * DCE6: PPLL, PPLL0, or ext घड़ी
		 *
		 * Setting ATOM_PPLL_INVALID will cause SetPixelClock to skip
		 * PPLL/DCPLL programming and only program the DP DTO क्रम the
		 * crtc भव pixel घड़ी.
		 */
		अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder))) अणु
			अगर (rdev->घड़ी.dp_extclk)
				/* skip PPLL programming अगर using ext घड़ी */
				वापस ATOM_PPLL_INVALID;
			अन्यथा अगर (ASIC_IS_DCE6(rdev))
				/* use PPLL0 क्रम all DP */
				वापस ATOM_PPLL0;
			अन्यथा अगर (ASIC_IS_DCE5(rdev))
				/* use DCPLL क्रम all DP */
				वापस ATOM_DCPLL;
			अन्यथा अणु
				/* use the same PPLL क्रम all DP monitors */
				pll = radeon_get_shared_dp_ppll(crtc);
				अगर (pll != ATOM_PPLL_INVALID)
					वापस pll;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* use the same PPLL क्रम all monitors with the same घड़ी */
			pll = radeon_get_shared_nondp_ppll(crtc);
			अगर (pll != ATOM_PPLL_INVALID)
				वापस pll;
		पूर्ण
		/* all other हालs */
		pll_in_use = radeon_get_pll_use_mask(crtc);
		अगर (!(pll_in_use & (1 << ATOM_PPLL1)))
			वापस ATOM_PPLL1;
		अगर (!(pll_in_use & (1 << ATOM_PPLL2)))
			वापस ATOM_PPLL2;
		DRM_ERROR("unable to allocate a PPLL\n");
		वापस ATOM_PPLL_INVALID;
	पूर्ण अन्यथा अणु
		/* on pre-R5xx asics, the crtc to pll mapping is hardcoded */
		/* some atombios (observed in some DCE2/DCE3) code have a bug,
		 * the matching btw pll and crtc is करोne through
		 * PCLK_CRTC[1|2]_CNTL (0x480/0x484) but atombios code use the
		 * pll (1 or 2) to select which रेजिस्टर to ग_लिखो. ie अगर using
		 * pll1 it will use PCLK_CRTC1_CNTL (0x480) and अगर using pll2
		 * it will use PCLK_CRTC2_CNTL (0x484), it then use crtc id to
		 * choose which value to ग_लिखो. Which is reverse order from
		 * रेजिस्टर logic. So only हाल that works is when pllid is
		 * same as crtcid or when both pll and crtc are enabled and
		 * both use same घड़ी.
		 *
		 * So just वापस crtc id as अगर crtc and pll were hard linked
		 * together even अगर they aren't
		 */
		वापस radeon_crtc->crtc_id;
	पूर्ण
पूर्ण

व्योम radeon_atom_disp_eng_pll_init(काष्ठा radeon_device *rdev)
अणु
	/* always set DCPLL */
	अगर (ASIC_IS_DCE6(rdev))
		atombios_crtc_set_disp_eng_pll(rdev, rdev->घड़ी.शेष_dispclk);
	अन्यथा अगर (ASIC_IS_DCE4(rdev)) अणु
		काष्ठा radeon_atom_ss ss;
		bool ss_enabled = radeon_atombios_get_asic_ss_info(rdev, &ss,
								   ASIC_INTERNAL_SS_ON_DCPLL,
								   rdev->घड़ी.शेष_dispclk);
		अगर (ss_enabled)
			atombios_crtc_program_ss(rdev, ATOM_DISABLE, ATOM_DCPLL, -1, &ss);
		/* XXX: DCE5, make sure voltage, dispclk is high enough */
		atombios_crtc_set_disp_eng_pll(rdev, rdev->घड़ी.शेष_dispclk);
		अगर (ss_enabled)
			atombios_crtc_program_ss(rdev, ATOM_ENABLE, ATOM_DCPLL, -1, &ss);
	पूर्ण

पूर्ण

पूर्णांक atombios_crtc_mode_set(काष्ठा drm_crtc *crtc,
			   काष्ठा drm_display_mode *mode,
			   काष्ठा drm_display_mode *adjusted_mode,
			   पूर्णांक x, पूर्णांक y, काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder =
		to_radeon_encoder(radeon_crtc->encoder);
	bool is_tvcv = false;

	अगर (radeon_encoder->active_device &
	    (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT))
		is_tvcv = true;

	अगर (!radeon_crtc->adjusted_घड़ी)
		वापस -EINVAL;

	atombios_crtc_set_pll(crtc, adjusted_mode);

	अगर (ASIC_IS_DCE4(rdev))
		atombios_set_crtc_dtd_timing(crtc, adjusted_mode);
	अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		अगर (is_tvcv)
			atombios_crtc_set_timing(crtc, adjusted_mode);
		अन्यथा
			atombios_set_crtc_dtd_timing(crtc, adjusted_mode);
	पूर्ण अन्यथा अणु
		atombios_crtc_set_timing(crtc, adjusted_mode);
		अगर (radeon_crtc->crtc_id == 0)
			atombios_set_crtc_dtd_timing(crtc, adjusted_mode);
		radeon_legacy_atom_fixup(crtc);
	पूर्ण
	atombios_crtc_set_base(crtc, x, y, old_fb);
	atombios_overscan_setup(crtc, mode, adjusted_mode);
	atombios_scaler_setup(crtc);
	radeon_cursor_reset(crtc);
	/* update the hw version fpr dpm */
	radeon_crtc->hw_mode = *adjusted_mode;

	वापस 0;
पूर्ण

अटल bool atombios_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				     स्थिर काष्ठा drm_display_mode *mode,
				     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_encoder *encoder;

	/* assign the encoder to the radeon crtc to aव्योम repeated lookups later */
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->crtc == crtc) अणु
			radeon_crtc->encoder = encoder;
			radeon_crtc->connector = radeon_get_connector_क्रम_encoder(encoder);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर ((radeon_crtc->encoder == शून्य) || (radeon_crtc->connector == शून्य)) अणु
		radeon_crtc->encoder = शून्य;
		radeon_crtc->connector = शून्य;
		वापस false;
	पूर्ण
	अगर (radeon_crtc->encoder) अणु
		काष्ठा radeon_encoder *radeon_encoder =
			to_radeon_encoder(radeon_crtc->encoder);

		radeon_crtc->output_csc = radeon_encoder->output_csc;
	पूर्ण
	अगर (!radeon_crtc_scaling_mode_fixup(crtc, mode, adjusted_mode))
		वापस false;
	अगर (!atombios_crtc_prepare_pll(crtc, adjusted_mode))
		वापस false;
	/* pick pll */
	radeon_crtc->pll_id = radeon_atom_pick_pll(crtc);
	/* अगर we can't get a PPLL क्रम a non-DP encoder, fail */
	अगर ((radeon_crtc->pll_id == ATOM_PPLL_INVALID) &&
	    !ENCODER_MODE_IS_DP(atombios_get_encoder_mode(radeon_crtc->encoder)))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम atombios_crtc_prepare(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	/* disable crtc pair घातer gating beक्रमe programming */
	अगर (ASIC_IS_DCE6(rdev))
		atombios_घातergate_crtc(crtc, ATOM_DISABLE);

	atombios_lock_crtc(crtc, ATOM_ENABLE);
	atombios_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम atombios_crtc_commit(काष्ठा drm_crtc *crtc)
अणु
	atombios_crtc_dpms(crtc, DRM_MODE_DPMS_ON);
	atombios_lock_crtc(crtc, ATOM_DISABLE);
पूर्ण

अटल व्योम atombios_crtc_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_atom_ss ss;
	पूर्णांक i;

	atombios_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
	अगर (crtc->primary->fb) अणु
		पूर्णांक r;
		काष्ठा radeon_bo *rbo;

		rbo = gem_to_radeon_bo(crtc->primary->fb->obj[0]);
		r = radeon_bo_reserve(rbo, false);
		अगर (unlikely(r))
			DRM_ERROR("failed to reserve rbo before unpin\n");
		अन्यथा अणु
			radeon_bo_unpin(rbo);
			radeon_bo_unreserve(rbo);
		पूर्ण
	पूर्ण
	/* disable the GRPH */
	अगर (ASIC_IS_DCE4(rdev))
		WREG32(EVERGREEN_GRPH_ENABLE + radeon_crtc->crtc_offset, 0);
	अन्यथा अगर (ASIC_IS_AVIVO(rdev))
		WREG32(AVIVO_D1GRPH_ENABLE + radeon_crtc->crtc_offset, 0);

	अगर (ASIC_IS_DCE6(rdev))
		atombios_घातergate_crtc(crtc, ATOM_ENABLE);

	क्रम (i = 0; i < rdev->num_crtc; i++) अणु
		अगर (rdev->mode_info.crtcs[i] &&
		    rdev->mode_info.crtcs[i]->enabled &&
		    i != radeon_crtc->crtc_id &&
		    radeon_crtc->pll_id == rdev->mode_info.crtcs[i]->pll_id) अणु
			/* one other crtc is using this pll करोn't turn
			 * off the pll
			 */
			जाओ करोne;
		पूर्ण
	पूर्ण

	चयन (radeon_crtc->pll_id) अणु
	हाल ATOM_PPLL1:
	हाल ATOM_PPLL2:
		/* disable the ppll */
		atombios_crtc_program_pll(crtc, radeon_crtc->crtc_id, radeon_crtc->pll_id,
					  0, 0, ATOM_DISABLE, 0, 0, 0, 0, 0, false, &ss);
		अवरोध;
	हाल ATOM_PPLL0:
		/* disable the ppll */
		अगर ((rdev->family == CHIP_ARUBA) ||
		    (rdev->family == CHIP_KAVERI) ||
		    (rdev->family == CHIP_BONAIRE) ||
		    (rdev->family == CHIP_HAWAII))
			atombios_crtc_program_pll(crtc, radeon_crtc->crtc_id, radeon_crtc->pll_id,
						  0, 0, ATOM_DISABLE, 0, 0, 0, 0, 0, false, &ss);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
करोne:
	radeon_crtc->pll_id = ATOM_PPLL_INVALID;
	radeon_crtc->adjusted_घड़ी = 0;
	radeon_crtc->encoder = शून्य;
	radeon_crtc->connector = शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs atombios_helper_funcs = अणु
	.dpms = atombios_crtc_dpms,
	.mode_fixup = atombios_crtc_mode_fixup,
	.mode_set = atombios_crtc_mode_set,
	.mode_set_base = atombios_crtc_set_base,
	.mode_set_base_atomic = atombios_crtc_set_base_atomic,
	.prepare = atombios_crtc_prepare,
	.commit = atombios_crtc_commit,
	.disable = atombios_crtc_disable,
	.get_scanout_position = radeon_get_crtc_scanout_position,
पूर्ण;

व्योम radeon_atombios_init_crtc(काष्ठा drm_device *dev,
			       काष्ठा radeon_crtc *radeon_crtc)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (ASIC_IS_DCE4(rdev)) अणु
		चयन (radeon_crtc->crtc_id) अणु
		हाल 0:
		शेष:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC0_REGISTER_OFFSET;
			अवरोध;
		हाल 1:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC1_REGISTER_OFFSET;
			अवरोध;
		हाल 2:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC2_REGISTER_OFFSET;
			अवरोध;
		हाल 3:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC3_REGISTER_OFFSET;
			अवरोध;
		हाल 4:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC4_REGISTER_OFFSET;
			अवरोध;
		हाल 5:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC5_REGISTER_OFFSET;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (radeon_crtc->crtc_id == 1)
			radeon_crtc->crtc_offset =
				AVIVO_D2CRTC_H_TOTAL - AVIVO_D1CRTC_H_TOTAL;
		अन्यथा
			radeon_crtc->crtc_offset = 0;
	पूर्ण
	radeon_crtc->pll_id = ATOM_PPLL_INVALID;
	radeon_crtc->adjusted_घड़ी = 0;
	radeon_crtc->encoder = शून्य;
	radeon_crtc->connector = शून्य;
	drm_crtc_helper_add(&radeon_crtc->base, &atombios_helper_funcs);
पूर्ण
