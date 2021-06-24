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
#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_fixed.h>
#समावेश "amdgpu.h"
#समावेश "atom.h"
#समावेश "atom-bits.h"
#समावेश "atombios_encoders.h"
#समावेश "atombios_crtc.h"
#समावेश "amdgpu_atombios.h"
#समावेश "amdgpu_pll.h"
#समावेश "amdgpu_connectors.h"

व्योम amdgpu_atombios_crtc_overscan_setup(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	SET_CRTC_OVERSCAN_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetCRTC_OverScan);
	पूर्णांक a1, a2;

	स_रखो(&args, 0, माप(args));

	args.ucCRTC = amdgpu_crtc->crtc_id;

	चयन (amdgpu_crtc->rmx_type) अणु
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
		args.usOverscanRight = cpu_to_le16(amdgpu_crtc->h_border);
		args.usOverscanLeft = cpu_to_le16(amdgpu_crtc->h_border);
		args.usOverscanBottom = cpu_to_le16(amdgpu_crtc->v_border);
		args.usOverscanTop = cpu_to_le16(amdgpu_crtc->v_border);
		अवरोध;
	पूर्ण
	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम amdgpu_atombios_crtc_scaler_setup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	ENABLE_SCALER_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableScaler);

	स_रखो(&args, 0, माप(args));

	args.ucScaler = amdgpu_crtc->crtc_id;

	चयन (amdgpu_crtc->rmx_type) अणु
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
		args.ucEnable = ATOM_SCALER_DISABLE;
		अवरोध;
	पूर्ण
	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम amdgpu_atombios_crtc_lock(काष्ठा drm_crtc *crtc, पूर्णांक lock)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक index =
	    GetIndexIntoMasterTable(COMMAND, UpdateCRTC_DoubleBufferRegisters);
	ENABLE_CRTC_PS_ALLOCATION args;

	स_रखो(&args, 0, माप(args));

	args.ucCRTC = amdgpu_crtc->crtc_id;
	args.ucEnable = lock;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम amdgpu_atombios_crtc_enable(काष्ठा drm_crtc *crtc, पूर्णांक state)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableCRTC);
	ENABLE_CRTC_PS_ALLOCATION args;

	स_रखो(&args, 0, माप(args));

	args.ucCRTC = amdgpu_crtc->crtc_id;
	args.ucEnable = state;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम amdgpu_atombios_crtc_blank(काष्ठा drm_crtc *crtc, पूर्णांक state)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, BlankCRTC);
	BLANK_CRTC_PS_ALLOCATION args;

	स_रखो(&args, 0, माप(args));

	args.ucCRTC = amdgpu_crtc->crtc_id;
	args.ucBlanking = state;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम amdgpu_atombios_crtc_घातergate(काष्ठा drm_crtc *crtc, पूर्णांक state)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableDispPowerGating);
	ENABLE_DISP_POWER_GATING_PS_ALLOCATION args;

	स_रखो(&args, 0, माप(args));

	args.ucDispPipeId = amdgpu_crtc->crtc_id;
	args.ucEnable = state;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम amdgpu_atombios_crtc_घातergate_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableDispPowerGating);
	ENABLE_DISP_POWER_GATING_PS_ALLOCATION args;

	स_रखो(&args, 0, माप(args));

	args.ucEnable = ATOM_INIT;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम amdgpu_atombios_crtc_set_dtd_timing(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	SET_CRTC_USING_DTD_TIMING_PARAMETERS args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetCRTC_UsingDTDTiming);
	u16 misc = 0;

	स_रखो(&args, 0, माप(args));
	args.usH_Size = cpu_to_le16(mode->crtc_hdisplay - (amdgpu_crtc->h_border * 2));
	args.usH_Blanking_Time =
		cpu_to_le16(mode->crtc_hblank_end - mode->crtc_hdisplay + (amdgpu_crtc->h_border * 2));
	args.usV_Size = cpu_to_le16(mode->crtc_vdisplay - (amdgpu_crtc->v_border * 2));
	args.usV_Blanking_Time =
		cpu_to_le16(mode->crtc_vblank_end - mode->crtc_vdisplay + (amdgpu_crtc->v_border * 2));
	args.usH_SyncOffset =
		cpu_to_le16(mode->crtc_hsync_start - mode->crtc_hdisplay + amdgpu_crtc->h_border);
	args.usH_SyncWidth =
		cpu_to_le16(mode->crtc_hsync_end - mode->crtc_hsync_start);
	args.usV_SyncOffset =
		cpu_to_le16(mode->crtc_vsync_start - mode->crtc_vdisplay + amdgpu_crtc->v_border);
	args.usV_SyncWidth =
		cpu_to_le16(mode->crtc_vsync_end - mode->crtc_vsync_start);
	args.ucH_Border = amdgpu_crtc->h_border;
	args.ucV_Border = amdgpu_crtc->v_border;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		misc |= ATOM_VSYNC_POLARITY;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		misc |= ATOM_HSYNC_POLARITY;
	अगर (mode->flags & DRM_MODE_FLAG_CSYNC)
		misc |= ATOM_COMPOSITESYNC;
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		misc |= ATOM_INTERLACE;
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		misc |= ATOM_DOUBLE_CLOCK_MODE;

	args.susModeMiscInfo.usAccess = cpu_to_le16(misc);
	args.ucCRTC = amdgpu_crtc->crtc_id;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

जोड़ atom_enable_ss अणु
	ENABLE_SPREAD_SPECTRUM_ON_PPLL_PS_ALLOCATION v1;
	ENABLE_SPREAD_SPECTRUM_ON_PPLL_V2 v2;
	ENABLE_SPREAD_SPECTRUM_ON_PPLL_V3 v3;
पूर्ण;

अटल व्योम amdgpu_atombios_crtc_program_ss(काष्ठा amdgpu_device *adev,
				     पूर्णांक enable,
				     पूर्णांक pll_id,
				     पूर्णांक crtc_id,
				     काष्ठा amdgpu_atom_ss *ss)
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
		क्रम (i = 0; i < adev->mode_info.num_crtc; i++) अणु
			अगर (adev->mode_info.crtcs[i] &&
			    adev->mode_info.crtcs[i]->enabled &&
			    i != crtc_id &&
			    pll_id == adev->mode_info.crtcs[i]->pll_id) अणु
				/* one other crtc is using this pll करोn't turn
				 * off spपढ़ो spectrum as it might turn off
				 * display on active crtc
				 */
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	स_रखो(&args, 0, माप(args));

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

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

जोड़ adjust_pixel_घड़ी अणु
	ADJUST_DISPLAY_PLL_PS_ALLOCATION v1;
	ADJUST_DISPLAY_PLL_PS_ALLOCATION_V3 v3;
पूर्ण;

अटल u32 amdgpu_atombios_crtc_adjust_pll(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_encoder *encoder = amdgpu_crtc->encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);
	u32 adjusted_घड़ी = mode->घड़ी;
	पूर्णांक encoder_mode = amdgpu_atombios_encoder_get_encoder_mode(encoder);
	u32 dp_घड़ी = mode->घड़ी;
	u32 घड़ी = mode->घड़ी;
	पूर्णांक bpc = amdgpu_crtc->bpc;
	bool is_duallink = amdgpu_dig_monitor_is_duallink(encoder, mode->घड़ी);
	जोड़ adjust_pixel_घड़ी args;
	u8 frev, crev;
	पूर्णांक index;

	amdgpu_crtc->pll_flags = AMDGPU_PLL_USE_FRAC_FB_DIV;

	अगर ((amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT | ATOM_DEVICE_DFP_SUPPORT)) ||
	    (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)) अणु
		अगर (connector) अणु
			काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
			काष्ठा amdgpu_connector_atom_dig *dig_connector =
				amdgpu_connector->con_priv;

			dp_घड़ी = dig_connector->dp_घड़ी;
		पूर्ण
	पूर्ण

	/* use recommended ref_भाग क्रम ss */
	अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
		अगर (amdgpu_crtc->ss_enabled) अणु
			अगर (amdgpu_crtc->ss.refभाग) अणु
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_REF_DIV;
				amdgpu_crtc->pll_reference_भाग = amdgpu_crtc->ss.refभाग;
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_FRAC_FB_DIV;
			पूर्ण
		पूर्ण
	पूर्ण

	/* DVO wants 2x pixel घड़ी अगर the DVO chip is in 12 bit mode */
	अगर (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1)
		adjusted_घड़ी = mode->घड़ी * 2;
	अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
		amdgpu_crtc->pll_flags |= AMDGPU_PLL_PREFER_CLOSEST_LOWER;
	अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
		amdgpu_crtc->pll_flags |= AMDGPU_PLL_IS_LCD;


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
	index = GetIndexIntoMasterTable(COMMAND, AdjustDisplayPll);
	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev,
				   &crev))
		वापस adjusted_घड़ी;

	स_रखो(&args, 0, माप(args));

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
		हाल 2:
			args.v1.usPixelClock = cpu_to_le16(घड़ी / 10);
			args.v1.ucTransmitterID = amdgpu_encoder->encoder_id;
			args.v1.ucEncodeMode = encoder_mode;
			अगर (amdgpu_crtc->ss_enabled && amdgpu_crtc->ss.percentage)
				args.v1.ucConfig |=
					ADJUST_DISPLAY_CONFIG_SS_ENABLE;

			amdgpu_atom_execute_table(adev->mode_info.atom_context,
					   index, (uपूर्णांक32_t *)&args);
			adjusted_घड़ी = le16_to_cpu(args.v1.usPixelClock) * 10;
			अवरोध;
		हाल 3:
			args.v3.sInput.usPixelClock = cpu_to_le16(घड़ी / 10);
			args.v3.sInput.ucTransmitterID = amdgpu_encoder->encoder_id;
			args.v3.sInput.ucEncodeMode = encoder_mode;
			args.v3.sInput.ucDispPllConfig = 0;
			अगर (amdgpu_crtc->ss_enabled && amdgpu_crtc->ss.percentage)
				args.v3.sInput.ucDispPllConfig |=
					DISPPLL_CONFIG_SS_ENABLE;
			अगर (ENCODER_MODE_IS_DP(encoder_mode)) अणु
				args.v3.sInput.ucDispPllConfig |=
					DISPPLL_CONFIG_COHERENT_MODE;
				/* 16200 or 27000 */
				args.v3.sInput.usPixelClock = cpu_to_le16(dp_घड़ी / 10);
			पूर्ण अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
				अगर (dig->coherent_mode)
					args.v3.sInput.ucDispPllConfig |=
						DISPPLL_CONFIG_COHERENT_MODE;
				अगर (is_duallink)
					args.v3.sInput.ucDispPllConfig |=
						DISPPLL_CONFIG_DUAL_LINK;
			पूर्ण
			अगर (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) !=
			    ENCODER_OBJECT_ID_NONE)
				args.v3.sInput.ucExtTransmitterID =
					amdgpu_encoder_get_dp_bridge_encoder_id(encoder);
			अन्यथा
				args.v3.sInput.ucExtTransmitterID = 0;

			amdgpu_atom_execute_table(adev->mode_info.atom_context,
					   index, (uपूर्णांक32_t *)&args);
			adjusted_घड़ी = le32_to_cpu(args.v3.sOutput.ulDispPllFreq) * 10;
			अगर (args.v3.sOutput.ucRefDiv) अणु
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_FRAC_FB_DIV;
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_REF_DIV;
				amdgpu_crtc->pll_reference_भाग = args.v3.sOutput.ucRefDiv;
			पूर्ण
			अगर (args.v3.sOutput.ucPostDiv) अणु
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_FRAC_FB_DIV;
				amdgpu_crtc->pll_flags |= AMDGPU_PLL_USE_POST_DIV;
				amdgpu_crtc->pll_post_भाग = args.v3.sOutput.ucPostDiv;
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

	वापस adjusted_घड़ी;
पूर्ण

जोड़ set_pixel_घड़ी अणु
	SET_PIXEL_CLOCK_PS_ALLOCATION base;
	PIXEL_CLOCK_PARAMETERS v1;
	PIXEL_CLOCK_PARAMETERS_V2 v2;
	PIXEL_CLOCK_PARAMETERS_V3 v3;
	PIXEL_CLOCK_PARAMETERS_V5 v5;
	PIXEL_CLOCK_PARAMETERS_V6 v6;
	PIXEL_CLOCK_PARAMETERS_V7 v7;
पूर्ण;

/* on DCE5, make sure the voltage is high enough to support the
 * required disp clk.
 */
व्योम amdgpu_atombios_crtc_set_disp_eng_pll(काष्ठा amdgpu_device *adev,
					   u32 dispclk)
अणु
	u8 frev, crev;
	पूर्णांक index;
	जोड़ set_pixel_घड़ी args;

	स_रखो(&args, 0, माप(args));

	index = GetIndexIntoMasterTable(COMMAND, SetPixelClock);
	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev,
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
			अगर (adev->asic_type == CHIP_TAHITI ||
			    adev->asic_type == CHIP_PITCAIRN ||
			    adev->asic_type == CHIP_VERDE ||
			    adev->asic_type == CHIP_OLAND)
				args.v6.ucPpll = ATOM_PPLL0;
			अन्यथा
				args.v6.ucPpll = ATOM_EXT_PLL1;
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
	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

जोड़ set_dce_घड़ी अणु
	SET_DCE_CLOCK_PS_ALLOCATION_V1_1 v1_1;
	SET_DCE_CLOCK_PS_ALLOCATION_V2_1 v2_1;
पूर्ण;

u32 amdgpu_atombios_crtc_set_dce_घड़ी(काष्ठा amdgpu_device *adev,
				       u32 freq, u8 clk_type, u8 clk_src)
अणु
	u8 frev, crev;
	पूर्णांक index;
	जोड़ set_dce_घड़ी args;
	u32 ret_freq = 0;

	स_रखो(&args, 0, माप(args));

	index = GetIndexIntoMasterTable(COMMAND, SetDCEClock);
	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev,
				   &crev))
		वापस 0;

	चयन (frev) अणु
	हाल 2:
		चयन (crev) अणु
		हाल 1:
			args.v2_1.asParam.ulDCEClkFreq = cpu_to_le32(freq); /* 10kHz units */
			args.v2_1.asParam.ucDCEClkType = clk_type;
			args.v2_1.asParam.ucDCEClkSrc = clk_src;
			amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
			ret_freq = le32_to_cpu(args.v2_1.asParam.ulDCEClkFreq) * 10;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d %d\n", frev, crev);
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d %d\n", frev, crev);
		वापस 0;
	पूर्ण

	वापस ret_freq;
पूर्ण

अटल bool is_pixel_घड़ी_source_from_pll(u32 encoder_mode, पूर्णांक pll_id)
अणु
	अगर (ENCODER_MODE_IS_DP(encoder_mode)) अणु
		अगर (pll_id < ATOM_EXT_PLL1)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण अन्यथा अणु
		वापस true;
	पूर्ण
पूर्ण

व्योम amdgpu_atombios_crtc_program_pll(काष्ठा drm_crtc *crtc,
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
				      काष्ठा amdgpu_atom_ss *ss)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	u8 frev, crev;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SetPixelClock);
	जोड़ set_pixel_घड़ी args;

	स_रखो(&args, 0, माप(args));

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev,
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
			अगर ((ss_enabled && (ss->type & ATOM_EXTERNAL_SS_MASK)) &&
			    (pll_id < ATOM_EXT_PLL1))
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
			अगर ((ss_enabled && (ss->type & ATOM_EXTERNAL_SS_MASK)) &&
			    (pll_id < ATOM_EXT_PLL1) &&
			    !is_pixel_घड़ी_source_from_pll(encoder_mode, pll_id))
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
		हाल 7:
			args.v7.ulPixelClock = cpu_to_le32(घड़ी * 10); /* 100 hz units */
			args.v7.ucMiscInfo = 0;
			अगर ((encoder_mode == ATOM_ENCODER_MODE_DVI) &&
			    (घड़ी > 165000))
				args.v7.ucMiscInfo |= PIXEL_CLOCK_V7_MISC_DVI_DUALLINK_EN;
			args.v7.ucCRTC = crtc_id;
			अगर (encoder_mode == ATOM_ENCODER_MODE_HDMI) अणु
				चयन (bpc) अणु
				हाल 8:
				शेष:
					args.v7.ucDeepColorRatio = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_DIS;
					अवरोध;
				हाल 10:
					args.v7.ucDeepColorRatio = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_5_4;
					अवरोध;
				हाल 12:
					args.v7.ucDeepColorRatio = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_3_2;
					अवरोध;
				हाल 16:
					args.v7.ucDeepColorRatio = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_2_1;
					अवरोध;
				पूर्ण
			पूर्ण
			args.v7.ucTransmitterID = encoder_id;
			args.v7.ucEncoderMode = encoder_mode;
			args.v7.ucPpll = pll_id;
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

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

पूर्णांक amdgpu_atombios_crtc_prepare_pll(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder =
		to_amdgpu_encoder(amdgpu_crtc->encoder);
	पूर्णांक encoder_mode = amdgpu_atombios_encoder_get_encoder_mode(amdgpu_crtc->encoder);

	amdgpu_crtc->bpc = 8;
	amdgpu_crtc->ss_enabled = false;

	अगर ((amdgpu_encoder->active_device & (ATOM_DEVICE_LCD_SUPPORT | ATOM_DEVICE_DFP_SUPPORT)) ||
	    (amdgpu_encoder_get_dp_bridge_encoder_id(amdgpu_crtc->encoder) != ENCODER_OBJECT_ID_NONE)) अणु
		काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
		काष्ठा drm_connector *connector =
			amdgpu_get_connector_क्रम_encoder(amdgpu_crtc->encoder);
		काष्ठा amdgpu_connector *amdgpu_connector =
			to_amdgpu_connector(connector);
		काष्ठा amdgpu_connector_atom_dig *dig_connector =
			amdgpu_connector->con_priv;
		पूर्णांक dp_घड़ी;

		/* Assign mode घड़ी क्रम hdmi deep color max घड़ी limit check */
		amdgpu_connector->pixelघड़ी_क्रम_modeset = mode->घड़ी;
		amdgpu_crtc->bpc = amdgpu_connector_get_monitor_bpc(connector);

		चयन (encoder_mode) अणु
		हाल ATOM_ENCODER_MODE_DP_MST:
		हाल ATOM_ENCODER_MODE_DP:
			/* DP/eDP */
			dp_घड़ी = dig_connector->dp_घड़ी / 10;
			amdgpu_crtc->ss_enabled =
				amdgpu_atombios_get_asic_ss_info(adev, &amdgpu_crtc->ss,
								 ASIC_INTERNAL_SS_ON_DP,
								 dp_घड़ी);
			अवरोध;
		हाल ATOM_ENCODER_MODE_LVDS:
			amdgpu_crtc->ss_enabled =
				amdgpu_atombios_get_asic_ss_info(adev,
								 &amdgpu_crtc->ss,
								 dig->lcd_ss_id,
								 mode->घड़ी / 10);
			अवरोध;
		हाल ATOM_ENCODER_MODE_DVI:
			amdgpu_crtc->ss_enabled =
				amdgpu_atombios_get_asic_ss_info(adev,
								 &amdgpu_crtc->ss,
								 ASIC_INTERNAL_SS_ON_TMDS,
								 mode->घड़ी / 10);
			अवरोध;
		हाल ATOM_ENCODER_MODE_HDMI:
			amdgpu_crtc->ss_enabled =
				amdgpu_atombios_get_asic_ss_info(adev,
								 &amdgpu_crtc->ss,
								 ASIC_INTERNAL_SS_ON_HDMI,
								 mode->घड़ी / 10);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* adjust pixel घड़ी as needed */
	amdgpu_crtc->adjusted_घड़ी = amdgpu_atombios_crtc_adjust_pll(crtc, mode);

	वापस 0;
पूर्ण

व्योम amdgpu_atombios_crtc_set_pll(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder =
		to_amdgpu_encoder(amdgpu_crtc->encoder);
	u32 pll_घड़ी = mode->घड़ी;
	u32 घड़ी = mode->घड़ी;
	u32 ref_भाग = 0, fb_भाग = 0, frac_fb_भाग = 0, post_भाग = 0;
	काष्ठा amdgpu_pll *pll;
	पूर्णांक encoder_mode = amdgpu_atombios_encoder_get_encoder_mode(amdgpu_crtc->encoder);

	/* pass the actual घड़ी to amdgpu_atombios_crtc_program_pll क्रम HDMI */
	अगर ((encoder_mode == ATOM_ENCODER_MODE_HDMI) &&
	    (amdgpu_crtc->bpc > 8))
		घड़ी = amdgpu_crtc->adjusted_घड़ी;

	चयन (amdgpu_crtc->pll_id) अणु
	हाल ATOM_PPLL1:
		pll = &adev->घड़ी.ppll[0];
		अवरोध;
	हाल ATOM_PPLL2:
		pll = &adev->घड़ी.ppll[1];
		अवरोध;
	हाल ATOM_PPLL0:
	हाल ATOM_PPLL_INVALID:
	शेष:
		pll = &adev->घड़ी.ppll[2];
		अवरोध;
	पूर्ण

	/* update pll params */
	pll->flags = amdgpu_crtc->pll_flags;
	pll->reference_भाग = amdgpu_crtc->pll_reference_भाग;
	pll->post_भाग = amdgpu_crtc->pll_post_भाग;

	amdgpu_pll_compute(pll, amdgpu_crtc->adjusted_घड़ी, &pll_घड़ी,
			    &fb_भाग, &frac_fb_भाग, &ref_भाग, &post_भाग);

	amdgpu_atombios_crtc_program_ss(adev, ATOM_DISABLE, amdgpu_crtc->pll_id,
				 amdgpu_crtc->crtc_id, &amdgpu_crtc->ss);

	amdgpu_atombios_crtc_program_pll(crtc, amdgpu_crtc->crtc_id, amdgpu_crtc->pll_id,
				  encoder_mode, amdgpu_encoder->encoder_id, घड़ी,
				  ref_भाग, fb_भाग, frac_fb_भाग, post_भाग,
				  amdgpu_crtc->bpc, amdgpu_crtc->ss_enabled, &amdgpu_crtc->ss);

	अगर (amdgpu_crtc->ss_enabled) अणु
		/* calculate ss amount and step size */
		u32 step_size;
		u32 amount = (((fb_भाग * 10) + frac_fb_भाग) *
			      (u32)amdgpu_crtc->ss.percentage) /
			(100 * (u32)amdgpu_crtc->ss.percentage_भागider);
		amdgpu_crtc->ss.amount = (amount / 10) & ATOM_PPLL_SS_AMOUNT_V2_FBDIV_MASK;
		amdgpu_crtc->ss.amount |= ((amount - (amount / 10)) << ATOM_PPLL_SS_AMOUNT_V2_NFRAC_SHIFT) &
			ATOM_PPLL_SS_AMOUNT_V2_NFRAC_MASK;
		अगर (amdgpu_crtc->ss.type & ATOM_PPLL_SS_TYPE_V2_CENTRE_SPREAD)
			step_size = (4 * amount * ref_भाग * ((u32)amdgpu_crtc->ss.rate * 2048)) /
				(125 * 25 * pll->reference_freq / 100);
		अन्यथा
			step_size = (2 * amount * ref_भाग * ((u32)amdgpu_crtc->ss.rate * 2048)) /
				(125 * 25 * pll->reference_freq / 100);
		amdgpu_crtc->ss.step = step_size;

		amdgpu_atombios_crtc_program_ss(adev, ATOM_ENABLE, amdgpu_crtc->pll_id,
					 amdgpu_crtc->crtc_id, &amdgpu_crtc->ss);
	पूर्ण
पूर्ण

