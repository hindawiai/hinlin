<शैली गुरु>
/*
 * Copyright तऊ 2012 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Eugeni Doकरोnov <eugeni.करोकरोnov@पूर्णांकel.com>
 *
 */

#समावेश <drm/drm_scdc_helper.h>

#समावेश "i915_drv.h"
#समावेश "intel_audio.h"
#समावेश "intel_combo_phy.h"
#समावेश "intel_connector.h"
#समावेश "intel_ddi.h"
#समावेश "intel_ddi_buf_trans.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp.h"
#समावेश "intel_dp_link_training.h"
#समावेश "intel_dp_mst.h"
#समावेश "intel_dpio_phy.h"
#समावेश "intel_dsi.h"
#समावेश "intel_fdi.h"
#समावेश "intel_fifo_underrun.h"
#समावेश "intel_gmbus.h"
#समावेश "intel_hdcp.h"
#समावेश "intel_hdmi.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_lspcon.h"
#समावेश "intel_panel.h"
#समावेश "intel_pps.h"
#समावेश "intel_psr.h"
#समावेश "intel_sprite.h"
#समावेश "intel_tc.h"
#समावेश "intel_vdsc.h"
#समावेश "intel_vrr.h"
#समावेश "skl_scaler.h"
#समावेश "skl_universal_plane.h"

अटल स्थिर u8 index_to_dp_संकेत_levels[] = अणु
	[0] = DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_0,
	[1] = DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_1,
	[2] = DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_2,
	[3] = DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_3,
	[4] = DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_0,
	[5] = DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_1,
	[6] = DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_2,
	[7] = DP_TRAIN_VOLTAGE_SWING_LEVEL_2 | DP_TRAIN_PRE_EMPH_LEVEL_0,
	[8] = DP_TRAIN_VOLTAGE_SWING_LEVEL_2 | DP_TRAIN_PRE_EMPH_LEVEL_1,
	[9] = DP_TRAIN_VOLTAGE_SWING_LEVEL_3 | DP_TRAIN_PRE_EMPH_LEVEL_0,
पूर्ण;

अटल पूर्णांक पूर्णांकel_ddi_hdmi_level(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	पूर्णांक n_entries, level, शेष_entry;

	n_entries = पूर्णांकel_ddi_hdmi_num_entries(encoder, crtc_state, &शेष_entry);
	अगर (n_entries == 0)
		वापस 0;
	level = पूर्णांकel_bios_hdmi_level_shअगरt(encoder);
	अगर (level < 0)
		level = शेष_entry;

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, level >= n_entries))
		level = n_entries - 1;

	वापस level;
पूर्ण

/*
 * Starting with Haswell, DDI port buffers must be programmed with correct
 * values in advance. This function programs the correct values क्रम
 * DP/eDP/FDI use हालs.
 */
व्योम पूर्णांकel_prepare_dp_ddi_buffers(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 iboost_bit = 0;
	पूर्णांक i, n_entries;
	क्रमागत port port = encoder->port;
	स्थिर काष्ठा ddi_buf_trans *ddi_translations;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG))
		ddi_translations = पूर्णांकel_ddi_get_buf_trans_fdi(dev_priv,
							       &n_entries);
	अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
		ddi_translations = पूर्णांकel_ddi_get_buf_trans_edp(encoder,
							       &n_entries);
	अन्यथा
		ddi_translations = पूर्णांकel_ddi_get_buf_trans_dp(encoder,
							      &n_entries);

	/* If we're boosting the current, set bit 31 of trans1 */
	अगर (IS_GEN9_BC(dev_priv) && पूर्णांकel_bios_encoder_dp_boost_level(encoder->devdata))
		iboost_bit = DDI_BUF_BALANCE_LEG_ENABLE;

	क्रम (i = 0; i < n_entries; i++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_TRANS_LO(port, i),
			       ddi_translations[i].trans1 | iboost_bit);
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_TRANS_HI(port, i),
			       ddi_translations[i].trans2);
	पूर्ण
पूर्ण

/*
 * Starting with Haswell, DDI port buffers must be programmed with correct
 * values in advance. This function programs the correct values क्रम
 * HDMI/DVI use हालs.
 */
अटल व्योम पूर्णांकel_prepare_hdmi_ddi_buffers(काष्ठा पूर्णांकel_encoder *encoder,
					   पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 iboost_bit = 0;
	पूर्णांक n_entries;
	क्रमागत port port = encoder->port;
	स्थिर काष्ठा ddi_buf_trans *ddi_translations;

	ddi_translations = पूर्णांकel_ddi_get_buf_trans_hdmi(encoder, &n_entries);

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !ddi_translations))
		वापस;
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, level >= n_entries))
		level = n_entries - 1;

	/* If we're boosting the current, set bit 31 of trans1 */
	अगर (IS_GEN9_BC(dev_priv) && पूर्णांकel_bios_encoder_hdmi_boost_level(encoder->devdata))
		iboost_bit = DDI_BUF_BALANCE_LEG_ENABLE;

	/* Entry 9 is क्रम HDMI: */
	पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_TRANS_LO(port, 9),
		       ddi_translations[level].trans1 | iboost_bit);
	पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_TRANS_HI(port, 9),
		       ddi_translations[level].trans2);
पूर्ण

व्योम पूर्णांकel_रुको_ddi_buf_idle(काष्ठा drm_i915_निजी *dev_priv,
			     क्रमागत port port)
अणु
	अगर (IS_BROXTON(dev_priv)) अणु
		udelay(16);
		वापस;
	पूर्ण

	अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port)) &
			 DDI_BUF_IS_IDLE), 8))
		drm_err(&dev_priv->drm, "Timeout waiting for DDI BUF %c to get idle\n",
			port_name(port));
पूर्ण

अटल व्योम पूर्णांकel_रुको_ddi_buf_active(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत port port)
अणु
	/* Wait > 518 usecs क्रम DDI_BUF_CTL to be non idle */
	अगर (DISPLAY_VER(dev_priv) < 10 && !IS_GEMINILAKE(dev_priv)) अणु
		usleep_range(518, 1000);
		वापस;
	पूर्ण

	अगर (रुको_क्रम_us(!(पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port)) &
			  DDI_BUF_IS_IDLE), 500))
		drm_err(&dev_priv->drm, "Timeout waiting for DDI BUF %c to get active\n",
			port_name(port));
पूर्ण

अटल u32 hsw_pll_to_ddi_pll_sel(स्थिर काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	चयन (pll->info->id) अणु
	हाल DPLL_ID_WRPLL1:
		वापस PORT_CLK_SEL_WRPLL1;
	हाल DPLL_ID_WRPLL2:
		वापस PORT_CLK_SEL_WRPLL2;
	हाल DPLL_ID_SPLL:
		वापस PORT_CLK_SEL_SPLL;
	हाल DPLL_ID_LCPLL_810:
		वापस PORT_CLK_SEL_LCPLL_810;
	हाल DPLL_ID_LCPLL_1350:
		वापस PORT_CLK_SEL_LCPLL_1350;
	हाल DPLL_ID_LCPLL_2700:
		वापस PORT_CLK_SEL_LCPLL_2700;
	शेष:
		MISSING_CASE(pll->info->id);
		वापस PORT_CLK_SEL_NONE;
	पूर्ण
पूर्ण

अटल u32 icl_pll_to_ddi_clk_sel(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	पूर्णांक घड़ी = crtc_state->port_घड़ी;
	स्थिर क्रमागत पूर्णांकel_dpll_id id = pll->info->id;

	चयन (id) अणु
	शेष:
		/*
		 * DPLL_ID_ICL_DPLL0 and DPLL_ID_ICL_DPLL1 should not be used
		 * here, so करो warn अगर this get passed in
		 */
		MISSING_CASE(id);
		वापस DDI_CLK_SEL_NONE;
	हाल DPLL_ID_ICL_TBTPLL:
		चयन (घड़ी) अणु
		हाल 162000:
			वापस DDI_CLK_SEL_TBT_162;
		हाल 270000:
			वापस DDI_CLK_SEL_TBT_270;
		हाल 540000:
			वापस DDI_CLK_SEL_TBT_540;
		हाल 810000:
			वापस DDI_CLK_SEL_TBT_810;
		शेष:
			MISSING_CASE(घड़ी);
			वापस DDI_CLK_SEL_NONE;
		पूर्ण
	हाल DPLL_ID_ICL_MGPLL1:
	हाल DPLL_ID_ICL_MGPLL2:
	हाल DPLL_ID_ICL_MGPLL3:
	हाल DPLL_ID_ICL_MGPLL4:
	हाल DPLL_ID_TGL_MGPLL5:
	हाल DPLL_ID_TGL_MGPLL6:
		वापस DDI_CLK_SEL_MG;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_ddi_init_dp_buf_reg(काष्ठा पूर्णांकel_encoder *encoder,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);

	पूर्णांकel_dp->DP = dig_port->saved_port_bits |
		DDI_BUF_CTL_ENABLE | DDI_BUF_TRANS_SELECT(0);
	पूर्णांकel_dp->DP |= DDI_PORT_WIDTH(crtc_state->lane_count);
पूर्ण

अटल पूर्णांक icl_calc_tbt_pll_link(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत port port)
अणु
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, DDI_CLK_SEL(port)) & DDI_CLK_SEL_MASK;

	चयन (val) अणु
	हाल DDI_CLK_SEL_NONE:
		वापस 0;
	हाल DDI_CLK_SEL_TBT_162:
		वापस 162000;
	हाल DDI_CLK_SEL_TBT_270:
		वापस 270000;
	हाल DDI_CLK_SEL_TBT_540:
		वापस 540000;
	हाल DDI_CLK_SEL_TBT_810:
		वापस 810000;
	शेष:
		MISSING_CASE(val);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ddi_करोtघड़ी_get(काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	पूर्णांक करोtघड़ी;

	अगर (pipe_config->has_pch_encoder)
		करोtघड़ी = पूर्णांकel_करोtघड़ी_calculate(pipe_config->port_घड़ी,
						    &pipe_config->fdi_m_n);
	अन्यथा अगर (पूर्णांकel_crtc_has_dp_encoder(pipe_config))
		करोtघड़ी = पूर्णांकel_करोtघड़ी_calculate(pipe_config->port_घड़ी,
						    &pipe_config->dp_m_n);
	अन्यथा अगर (pipe_config->has_hdmi_sink && pipe_config->pipe_bpp > 24)
		करोtघड़ी = pipe_config->port_घड़ी * 24 / pipe_config->pipe_bpp;
	अन्यथा
		करोtघड़ी = pipe_config->port_घड़ी;

	अगर (pipe_config->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420 &&
	    !पूर्णांकel_crtc_has_dp_encoder(pipe_config))
		करोtघड़ी *= 2;

	अगर (pipe_config->pixel_multiplier)
		करोtघड़ी /= pipe_config->pixel_multiplier;

	pipe_config->hw.adjusted_mode.crtc_घड़ी = करोtघड़ी;
पूर्ण

व्योम पूर्णांकel_ddi_set_dp_msa(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 temp;

	अगर (!पूर्णांकel_crtc_has_dp_encoder(crtc_state))
		वापस;

	drm_WARN_ON(&dev_priv->drm, transcoder_is_dsi(cpu_transcoder));

	temp = DP_MSA_MISC_SYNC_CLOCK;

	चयन (crtc_state->pipe_bpp) अणु
	हाल 18:
		temp |= DP_MSA_MISC_6_BPC;
		अवरोध;
	हाल 24:
		temp |= DP_MSA_MISC_8_BPC;
		अवरोध;
	हाल 30:
		temp |= DP_MSA_MISC_10_BPC;
		अवरोध;
	हाल 36:
		temp |= DP_MSA_MISC_12_BPC;
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->pipe_bpp);
		अवरोध;
	पूर्ण

	/* nonsense combination */
	drm_WARN_ON(&dev_priv->drm, crtc_state->limited_color_range &&
		    crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB);

	अगर (crtc_state->limited_color_range)
		temp |= DP_MSA_MISC_COLOR_CEA_RGB;

	/*
	 * As per DP 1.2 spec section 2.3.4.3 जबतक sending
	 * YCBCR 444 संकेतs we should program MSA MISC1/0 fields with
	 * colorspace inक्रमmation.
	 */
	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR444)
		temp |= DP_MSA_MISC_COLOR_YCBCR_444_BT709;

	/*
	 * As per DP 1.4a spec section 2.2.4.3 [MSA Field क्रम Indication
	 * of Color Encoding Format and Content Color Gamut] जबतक sending
	 * YCBCR 420, HDR BT.2020 संकेतs we should program MSA MISC1 fields
	 * which indicate VSC SDP क्रम the Pixel Encoding/Colorimetry Format.
	 */
	अगर (पूर्णांकel_dp_needs_vsc_sdp(crtc_state, conn_state))
		temp |= DP_MSA_MISC_COLOR_VSC_SDP;

	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_MSA_MISC(cpu_transcoder), temp);
पूर्ण

अटल u32 bdw_trans_port_sync_master_select(क्रमागत transcoder master_transcoder)
अणु
	अगर (master_transcoder == TRANSCODER_EDP)
		वापस 0;
	अन्यथा
		वापस master_transcoder + 1;
पूर्ण

/*
 * Returns the TRANS_DDI_FUNC_CTL value based on CRTC state.
 *
 * Only पूर्णांकended to be used by पूर्णांकel_ddi_enable_transcoder_func() and
 * पूर्णांकel_ddi_config_transcoder_func().
 */
अटल u32
पूर्णांकel_ddi_transcoder_func_reg_val_get(काष्ठा पूर्णांकel_encoder *encoder,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	क्रमागत port port = encoder->port;
	u32 temp;

	/* Enable TRANS_DDI_FUNC_CTL क्रम the pipe to work in HDMI mode */
	temp = TRANS_DDI_FUNC_ENABLE;
	अगर (DISPLAY_VER(dev_priv) >= 12)
		temp |= TGL_TRANS_DDI_SELECT_PORT(port);
	अन्यथा
		temp |= TRANS_DDI_SELECT_PORT(port);

	चयन (crtc_state->pipe_bpp) अणु
	हाल 18:
		temp |= TRANS_DDI_BPC_6;
		अवरोध;
	हाल 24:
		temp |= TRANS_DDI_BPC_8;
		अवरोध;
	हाल 30:
		temp |= TRANS_DDI_BPC_10;
		अवरोध;
	हाल 36:
		temp |= TRANS_DDI_BPC_12;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (crtc_state->hw.adjusted_mode.flags & DRM_MODE_FLAG_PVSYNC)
		temp |= TRANS_DDI_PVSYNC;
	अगर (crtc_state->hw.adjusted_mode.flags & DRM_MODE_FLAG_PHSYNC)
		temp |= TRANS_DDI_PHSYNC;

	अगर (cpu_transcoder == TRANSCODER_EDP) अणु
		चयन (pipe) अणु
		हाल PIPE_A:
			/* On Haswell, can only use the always-on घातer well क्रम
			 * eDP when not using the panel fitter, and when not
			 * using motion blur mitigation (which we करोn't
			 * support). */
			अगर (crtc_state->pch_pfit.क्रमce_thru)
				temp |= TRANS_DDI_EDP_INPUT_A_ONOFF;
			अन्यथा
				temp |= TRANS_DDI_EDP_INPUT_A_ON;
			अवरोध;
		हाल PIPE_B:
			temp |= TRANS_DDI_EDP_INPUT_B_ONOFF;
			अवरोध;
		हाल PIPE_C:
			temp |= TRANS_DDI_EDP_INPUT_C_ONOFF;
			अवरोध;
		शेष:
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) अणु
		अगर (crtc_state->has_hdmi_sink)
			temp |= TRANS_DDI_MODE_SELECT_HDMI;
		अन्यथा
			temp |= TRANS_DDI_MODE_SELECT_DVI;

		अगर (crtc_state->hdmi_scrambling)
			temp |= TRANS_DDI_HDMI_SCRAMBLING;
		अगर (crtc_state->hdmi_high_पंचांगds_घड़ी_ratio)
			temp |= TRANS_DDI_HIGH_TMDS_CHAR_RATE;
	पूर्ण अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG)) अणु
		temp |= TRANS_DDI_MODE_SELECT_FDI;
		temp |= (crtc_state->fdi_lanes - 1) << 1;
	पूर्ण अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST)) अणु
		temp |= TRANS_DDI_MODE_SELECT_DP_MST;
		temp |= DDI_PORT_WIDTH(crtc_state->lane_count);

		अगर (DISPLAY_VER(dev_priv) >= 12) अणु
			क्रमागत transcoder master;

			master = crtc_state->mst_master_transcoder;
			drm_WARN_ON(&dev_priv->drm,
				    master == INVALID_TRANSCODER);
			temp |= TRANS_DDI_MST_TRANSPORT_SELECT(master);
		पूर्ण
	पूर्ण अन्यथा अणु
		temp |= TRANS_DDI_MODE_SELECT_DP_SST;
		temp |= DDI_PORT_WIDTH(crtc_state->lane_count);
	पूर्ण

	अगर (IS_DISPLAY_RANGE(dev_priv, 8, 10) &&
	    crtc_state->master_transcoder != INVALID_TRANSCODER) अणु
		u8 master_select =
			bdw_trans_port_sync_master_select(crtc_state->master_transcoder);

		temp |= TRANS_DDI_PORT_SYNC_ENABLE |
			TRANS_DDI_PORT_SYNC_MASTER_SELECT(master_select);
	पूर्ण

	वापस temp;
पूर्ण

व्योम पूर्णांकel_ddi_enable_transcoder_func(काष्ठा पूर्णांकel_encoder *encoder,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		क्रमागत transcoder master_transcoder = crtc_state->master_transcoder;
		u32 ctl2 = 0;

		अगर (master_transcoder != INVALID_TRANSCODER) अणु
			u8 master_select =
				bdw_trans_port_sync_master_select(master_transcoder);

			ctl2 |= PORT_SYNC_MODE_ENABLE |
				PORT_SYNC_MODE_MASTER_SELECT(master_select);
		पूर्ण

		पूर्णांकel_de_ग_लिखो(dev_priv,
			       TRANS_DDI_FUNC_CTL2(cpu_transcoder), ctl2);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder),
		       पूर्णांकel_ddi_transcoder_func_reg_val_get(encoder,
							     crtc_state));
पूर्ण

/*
 * Same as पूर्णांकel_ddi_enable_transcoder_func(), but it करोes not set the enable
 * bit.
 */
अटल व्योम
पूर्णांकel_ddi_config_transcoder_func(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 ctl;

	ctl = पूर्णांकel_ddi_transcoder_func_reg_val_get(encoder, crtc_state);
	ctl &= ~TRANS_DDI_FUNC_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder), ctl);
पूर्ण

व्योम पूर्णांकel_ddi_disable_transcoder_func(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 ctl;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       TRANS_DDI_FUNC_CTL2(cpu_transcoder), 0);

	ctl = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder));

	drm_WARN_ON(crtc->base.dev, ctl & TRANS_DDI_HDCP_SIGNALLING);

	ctl &= ~TRANS_DDI_FUNC_ENABLE;

	अगर (IS_DISPLAY_RANGE(dev_priv, 8, 10))
		ctl &= ~(TRANS_DDI_PORT_SYNC_ENABLE |
			 TRANS_DDI_PORT_SYNC_MASTER_SELECT_MASK);

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		अगर (!पूर्णांकel_dp_mst_is_master_trans(crtc_state)) अणु
			ctl &= ~(TGL_TRANS_DDI_PORT_MASK |
				 TRANS_DDI_MODE_SELECT_MASK);
		पूर्ण
	पूर्ण अन्यथा अणु
		ctl &= ~(TRANS_DDI_PORT_MASK | TRANS_DDI_MODE_SELECT_MASK);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder), ctl);

	अगर (dev_priv->quirks & QUIRK_INCREASE_DDI_DISABLED_TIME &&
	    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Quirk Increase DDI disabled time\n");
		/* Quirk समय at 100ms क्रम reliable operation */
		msleep(100);
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_ddi_toggle_hdcp_bits(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
			       क्रमागत transcoder cpu_transcoder,
			       bool enable, u32 hdcp_mask)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक ret = 0;
	u32 पंचांगp;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     पूर्णांकel_encoder->घातer_करोमुख्य);
	अगर (drm_WARN_ON(dev, !wakeref))
		वापस -ENXIO;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder));
	अगर (enable)
		पंचांगp |= hdcp_mask;
	अन्यथा
		पंचांगp &= ~hdcp_mask;
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder), पंचांगp);
	पूर्णांकel_display_घातer_put(dev_priv, पूर्णांकel_encoder->घातer_करोमुख्य, wakeref);
	वापस ret;
पूर्ण

bool पूर्णांकel_ddi_connector_get_hw_state(काष्ठा पूर्णांकel_connector *पूर्णांकel_connector)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_connector->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_encoder *encoder = पूर्णांकel_attached_encoder(पूर्णांकel_connector);
	पूर्णांक type = पूर्णांकel_connector->base.connector_type;
	क्रमागत port port = encoder->port;
	क्रमागत transcoder cpu_transcoder;
	पूर्णांकel_wakeref_t wakeref;
	क्रमागत pipe pipe = 0;
	u32 पंचांगp;
	bool ret;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     encoder->घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	अगर (!encoder->get_hw_state(encoder, &pipe)) अणु
		ret = false;
		जाओ out;
	पूर्ण

	अगर (HAS_TRANSCODER(dev_priv, TRANSCODER_EDP) && port == PORT_A)
		cpu_transcoder = TRANSCODER_EDP;
	अन्यथा
		cpu_transcoder = (क्रमागत transcoder) pipe;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder));

	चयन (पंचांगp & TRANS_DDI_MODE_SELECT_MASK) अणु
	हाल TRANS_DDI_MODE_SELECT_HDMI:
	हाल TRANS_DDI_MODE_SELECT_DVI:
		ret = type == DRM_MODE_CONNECTOR_HDMIA;
		अवरोध;

	हाल TRANS_DDI_MODE_SELECT_DP_SST:
		ret = type == DRM_MODE_CONNECTOR_eDP ||
		      type == DRM_MODE_CONNECTOR_DisplayPort;
		अवरोध;

	हाल TRANS_DDI_MODE_SELECT_DP_MST:
		/* अगर the transcoder is in MST state then
		 * connector isn't connected */
		ret = false;
		अवरोध;

	हाल TRANS_DDI_MODE_SELECT_FDI:
		ret = type == DRM_MODE_CONNECTOR_VGA;
		अवरोध;

	शेष:
		ret = false;
		अवरोध;
	पूर्ण

out:
	पूर्णांकel_display_घातer_put(dev_priv, encoder->घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_ddi_get_encoder_pipes(काष्ठा पूर्णांकel_encoder *encoder,
					u8 *pipe_mask, bool *is_dp_mst)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत port port = encoder->port;
	पूर्णांकel_wakeref_t wakeref;
	क्रमागत pipe p;
	u32 पंचांगp;
	u8 mst_pipe_mask;

	*pipe_mask = 0;
	*is_dp_mst = false;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     encoder->घातer_करोमुख्य);
	अगर (!wakeref)
		वापस;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port));
	अगर (!(पंचांगp & DDI_BUF_CTL_ENABLE))
		जाओ out;

	अगर (HAS_TRANSCODER(dev_priv, TRANSCODER_EDP) && port == PORT_A) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
				    TRANS_DDI_FUNC_CTL(TRANSCODER_EDP));

		चयन (पंचांगp & TRANS_DDI_EDP_INPUT_MASK) अणु
		शेष:
			MISSING_CASE(पंचांगp & TRANS_DDI_EDP_INPUT_MASK);
			fallthrough;
		हाल TRANS_DDI_EDP_INPUT_A_ON:
		हाल TRANS_DDI_EDP_INPUT_A_ONOFF:
			*pipe_mask = BIT(PIPE_A);
			अवरोध;
		हाल TRANS_DDI_EDP_INPUT_B_ONOFF:
			*pipe_mask = BIT(PIPE_B);
			अवरोध;
		हाल TRANS_DDI_EDP_INPUT_C_ONOFF:
			*pipe_mask = BIT(PIPE_C);
			अवरोध;
		पूर्ण

		जाओ out;
	पूर्ण

	mst_pipe_mask = 0;
	क्रम_each_pipe(dev_priv, p) अणु
		क्रमागत transcoder cpu_transcoder = (क्रमागत transcoder)p;
		अचिन्हित पूर्णांक port_mask, ddi_select;
		पूर्णांकel_wakeref_t trans_wakeref;

		trans_wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
								   POWER_DOMAIN_TRANSCODER(cpu_transcoder));
		अगर (!trans_wakeref)
			जारी;

		अगर (DISPLAY_VER(dev_priv) >= 12) अणु
			port_mask = TGL_TRANS_DDI_PORT_MASK;
			ddi_select = TGL_TRANS_DDI_SELECT_PORT(port);
		पूर्ण अन्यथा अणु
			port_mask = TRANS_DDI_PORT_MASK;
			ddi_select = TRANS_DDI_SELECT_PORT(port);
		पूर्ण

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
				    TRANS_DDI_FUNC_CTL(cpu_transcoder));
		पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_TRANSCODER(cpu_transcoder),
					trans_wakeref);

		अगर ((पंचांगp & port_mask) != ddi_select)
			जारी;

		अगर ((पंचांगp & TRANS_DDI_MODE_SELECT_MASK) ==
		    TRANS_DDI_MODE_SELECT_DP_MST)
			mst_pipe_mask |= BIT(p);

		*pipe_mask |= BIT(p);
	पूर्ण

	अगर (!*pipe_mask)
		drm_dbg_kms(&dev_priv->drm,
			    "No pipe for [ENCODER:%d:%s] found\n",
			    encoder->base.base.id, encoder->base.name);

	अगर (!mst_pipe_mask && hweight8(*pipe_mask) > 1) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Multiple pipes for [ENCODER:%d:%s] (pipe_mask %02x)\n",
			    encoder->base.base.id, encoder->base.name,
			    *pipe_mask);
		*pipe_mask = BIT(ffs(*pipe_mask) - 1);
	पूर्ण

	अगर (mst_pipe_mask && mst_pipe_mask != *pipe_mask)
		drm_dbg_kms(&dev_priv->drm,
			    "Conflicting MST and non-MST state for [ENCODER:%d:%s] (pipe_mask %02x mst_pipe_mask %02x)\n",
			    encoder->base.base.id, encoder->base.name,
			    *pipe_mask, mst_pipe_mask);
	अन्यथा
		*is_dp_mst = mst_pipe_mask;

out:
	अगर (*pipe_mask && IS_GEN9_LP(dev_priv)) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_PHY_CTL(port));
		अगर ((पंचांगp & (BXT_PHY_CMNLANE_POWERDOWN_ACK |
			    BXT_PHY_LANE_POWERDOWN_ACK |
			    BXT_PHY_LANE_ENABLED)) != BXT_PHY_LANE_ENABLED)
			drm_err(&dev_priv->drm,
				"[ENCODER:%d:%s] enabled but PHY powered down? (PHY_CTL %08x)\n",
				encoder->base.base.id, encoder->base.name, पंचांगp);
	पूर्ण

	पूर्णांकel_display_घातer_put(dev_priv, encoder->घातer_करोमुख्य, wakeref);
पूर्ण

bool पूर्णांकel_ddi_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
			    क्रमागत pipe *pipe)
अणु
	u8 pipe_mask;
	bool is_mst;

	पूर्णांकel_ddi_get_encoder_pipes(encoder, &pipe_mask, &is_mst);

	अगर (is_mst || !pipe_mask)
		वापस false;

	*pipe = ffs(pipe_mask) - 1;

	वापस true;
पूर्ण

अटल क्रमागत पूर्णांकel_display_घातer_करोमुख्य
पूर्णांकel_ddi_मुख्य_link_aux_करोमुख्य(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	/* CNL+ HW requires corresponding AUX IOs to be घातered up क्रम PSR with
	 * DC states enabled at the same समय, जबतक क्रम driver initiated AUX
	 * transfers we need the same AUX IOs to be घातered but with DC states
	 * disabled. Accordingly use the AUX घातer करोमुख्य here which leaves DC
	 * states enabled.
	 * However, क्रम non-A AUX ports the corresponding non-EDP transcoders
	 * would have alपढ़ोy enabled घातer well 2 and DC_OFF. This means we can
	 * acquire a wider POWER_DOMAIN_AUX_अणुB,C,D,Fपूर्ण reference instead of a
	 * specअगरic AUX_IO reference without घातering up any extra wells.
	 * Note that PSR is enabled only on Port A even though this function
	 * वापसs the correct करोमुख्य क्रम other ports too.
	 */
	वापस dig_port->aux_ch == AUX_CH_A ? POWER_DOMAIN_AUX_IO_A :
					      पूर्णांकel_aux_घातer_करोमुख्य(dig_port);
पूर्ण

अटल व्योम पूर्णांकel_ddi_get_घातer_करोमुख्यs(काष्ठा पूर्णांकel_encoder *encoder,
					काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);

	/*
	 * TODO: Add support क्रम MST encoders. Aपंचांग, the following should never
	 * happen since fake-MST encoders करोn't set their get_घातer_करोमुख्यs()
	 * hook.
	 */
	अगर (drm_WARN_ON(&dev_priv->drm,
			पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST)))
		वापस;

	dig_port = enc_to_dig_port(encoder);

	अगर (!पूर्णांकel_phy_is_tc(dev_priv, phy) ||
	    dig_port->tc_mode != TC_PORT_TBT_ALT) अणु
		drm_WARN_ON(&dev_priv->drm, dig_port->ddi_io_wakeref);
		dig_port->ddi_io_wakeref = पूर्णांकel_display_घातer_get(dev_priv,
								   dig_port->ddi_io_घातer_करोमुख्य);
	पूर्ण

	/*
	 * AUX घातer is only needed क्रम (e)DP mode, and क्रम HDMI mode on TC
	 * ports.
	 */
	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state) ||
	    पूर्णांकel_phy_is_tc(dev_priv, phy)) अणु
		drm_WARN_ON(&dev_priv->drm, dig_port->aux_wakeref);
		dig_port->aux_wakeref =
			पूर्णांकel_display_घातer_get(dev_priv,
						पूर्णांकel_ddi_मुख्य_link_aux_करोमुख्य(dig_port));
	पूर्ण
पूर्ण

व्योम पूर्णांकel_ddi_enable_pipe_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत port port = encoder->port;
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	अगर (cpu_transcoder != TRANSCODER_EDP) अणु
		अगर (DISPLAY_VER(dev_priv) >= 12)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       TRANS_CLK_SEL(cpu_transcoder),
				       TGL_TRANS_CLK_SEL_PORT(port));
		अन्यथा
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       TRANS_CLK_SEL(cpu_transcoder),
				       TRANS_CLK_SEL_PORT(port));
	पूर्ण
पूर्ण

व्योम पूर्णांकel_ddi_disable_pipe_घड़ी(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	अगर (cpu_transcoder != TRANSCODER_EDP) अणु
		अगर (DISPLAY_VER(dev_priv) >= 12)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       TRANS_CLK_SEL(cpu_transcoder),
				       TGL_TRANS_CLK_SEL_DISABLED);
		अन्यथा
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       TRANS_CLK_SEL(cpu_transcoder),
				       TRANS_CLK_SEL_DISABLED);
	पूर्ण
पूर्ण

अटल व्योम _skl_ddi_set_iboost(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत port port, u8 iboost)
अणु
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DISPIO_CR_TX_BMU_CR0);
	पंचांगp &= ~(BALANCE_LEG_MASK(port) | BALANCE_LEG_DISABLE(port));
	अगर (iboost)
		पंचांगp |= iboost << BALANCE_LEG_SHIFT(port);
	अन्यथा
		पंचांगp |= BALANCE_LEG_DISABLE(port);
	पूर्णांकel_de_ग_लिखो(dev_priv, DISPIO_CR_TX_BMU_CR0, पंचांगp);
पूर्ण

अटल व्योम skl_ddi_set_iboost(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       पूर्णांक level)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u8 iboost;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		iboost = पूर्णांकel_bios_encoder_hdmi_boost_level(encoder->devdata);
	अन्यथा
		iboost = पूर्णांकel_bios_encoder_dp_boost_level(encoder->devdata);

	अगर (iboost == 0) अणु
		स्थिर काष्ठा ddi_buf_trans *ddi_translations;
		पूर्णांक n_entries;

		अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
			ddi_translations = पूर्णांकel_ddi_get_buf_trans_hdmi(encoder, &n_entries);
		अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
			ddi_translations = पूर्णांकel_ddi_get_buf_trans_edp(encoder, &n_entries);
		अन्यथा
			ddi_translations = पूर्णांकel_ddi_get_buf_trans_dp(encoder, &n_entries);

		अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !ddi_translations))
			वापस;
		अगर (drm_WARN_ON_ONCE(&dev_priv->drm, level >= n_entries))
			level = n_entries - 1;

		iboost = ddi_translations[level].i_boost;
	पूर्ण

	/* Make sure that the requested I_boost is valid */
	अगर (iboost && iboost != 0x1 && iboost != 0x3 && iboost != 0x7) अणु
		drm_err(&dev_priv->drm, "Invalid I_boost value %u\n", iboost);
		वापस;
	पूर्ण

	_skl_ddi_set_iboost(dev_priv, encoder->port, iboost);

	अगर (encoder->port == PORT_A && dig_port->max_lanes == 4)
		_skl_ddi_set_iboost(dev_priv, PORT_E, iboost);
पूर्ण

अटल व्योम bxt_ddi_vswing_sequence(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	स्थिर काष्ठा bxt_ddi_buf_trans *ddi_translations;
	क्रमागत port port = encoder->port;
	पूर्णांक n_entries;

	ddi_translations = bxt_get_buf_trans(encoder, crtc_state, &n_entries);
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !ddi_translations))
		वापस;
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, level >= n_entries))
		level = n_entries - 1;

	bxt_ddi_phy_set_संकेत_level(dev_priv, port,
				     ddi_translations[level].margin,
				     ddi_translations[level].scale,
				     ddi_translations[level].enable,
				     ddi_translations[level].deemphasis);
पूर्ण

अटल u8 पूर्णांकel_ddi_dp_voltage_max(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, port);
	पूर्णांक n_entries;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		अगर (पूर्णांकel_phy_is_combo(dev_priv, phy))
			tgl_get_combo_buf_trans(encoder, crtc_state, &n_entries);
		अन्यथा
			tgl_get_dkl_buf_trans(encoder, crtc_state, &n_entries);
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11)) अणु
		अगर (IS_PLATFORM(dev_priv, INTEL_JASPERLAKE))
			jsl_get_combo_buf_trans(encoder, crtc_state, &n_entries);
		अन्यथा अगर (IS_PLATFORM(dev_priv, INTEL_ELKHARTLAKE))
			ehl_get_combo_buf_trans(encoder, crtc_state, &n_entries);
		अन्यथा अगर (पूर्णांकel_phy_is_combo(dev_priv, phy))
			icl_get_combo_buf_trans(encoder, crtc_state, &n_entries);
		अन्यथा
			icl_get_mg_buf_trans(encoder, crtc_state, &n_entries);
	पूर्ण अन्यथा अगर (IS_CANNONLAKE(dev_priv)) अणु
		cnl_get_buf_trans(encoder, crtc_state, &n_entries);
	पूर्ण अन्यथा अगर (IS_GEN9_LP(dev_priv)) अणु
		bxt_get_buf_trans(encoder, crtc_state, &n_entries);
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP))
			पूर्णांकel_ddi_get_buf_trans_edp(encoder, &n_entries);
		अन्यथा
			पूर्णांकel_ddi_get_buf_trans_dp(encoder, &n_entries);
	पूर्ण

	अगर (drm_WARN_ON(&dev_priv->drm, n_entries < 1))
		n_entries = 1;
	अगर (drm_WARN_ON(&dev_priv->drm,
			n_entries > ARRAY_SIZE(index_to_dp_संकेत_levels)))
		n_entries = ARRAY_SIZE(index_to_dp_संकेत_levels);

	वापस index_to_dp_संकेत_levels[n_entries - 1] &
		DP_TRAIN_VOLTAGE_SWING_MASK;
पूर्ण

/*
 * We assume that the full set of pre-emphasis values can be
 * used on all DDI platक्रमms. Should that change we need to
 * rethink this code.
 */
अटल u8 पूर्णांकel_ddi_dp_preemph_max(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस DP_TRAIN_PRE_EMPH_LEVEL_3;
पूर्ण

अटल व्योम cnl_ddi_vswing_program(काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	स्थिर काष्ठा cnl_ddi_buf_trans *ddi_translations;
	क्रमागत port port = encoder->port;
	पूर्णांक n_entries, ln;
	u32 val;

	ddi_translations = cnl_get_buf_trans(encoder, crtc_state, &n_entries);

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !ddi_translations))
		वापस;
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, level >= n_entries))
		level = n_entries - 1;

	/* Set PORT_TX_DW5 Scaling Mode Sel to 010b. */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_TX_DW5_LN0(port));
	val &= ~SCALING_MODE_SEL_MASK;
	val |= SCALING_MODE_SEL(2);
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_TX_DW5_GRP(port), val);

	/* Program PORT_TX_DW2 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_TX_DW2_LN0(port));
	val &= ~(SWING_SEL_LOWER_MASK | SWING_SEL_UPPER_MASK |
		 RCOMP_SCALAR_MASK);
	val |= SWING_SEL_UPPER(ddi_translations[level].dw2_swing_sel);
	val |= SWING_SEL_LOWER(ddi_translations[level].dw2_swing_sel);
	/* Rcomp scalar is fixed as 0x98 क्रम every table entry */
	val |= RCOMP_SCALAR(0x98);
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_TX_DW2_GRP(port), val);

	/* Program PORT_TX_DW4 */
	/* We cannot ग_लिखो to GRP. It would overrite inभागidual loadgen */
	क्रम (ln = 0; ln < 4; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_TX_DW4_LN(ln, port));
		val &= ~(POST_CURSOR_1_MASK | POST_CURSOR_2_MASK |
			 CURSOR_COEFF_MASK);
		val |= POST_CURSOR_1(ddi_translations[level].dw4_post_cursor_1);
		val |= POST_CURSOR_2(ddi_translations[level].dw4_post_cursor_2);
		val |= CURSOR_COEFF(ddi_translations[level].dw4_cursor_coeff);
		पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_TX_DW4_LN(ln, port), val);
	पूर्ण

	/* Program PORT_TX_DW5 */
	/* All DW5 values are fixed क्रम every table entry */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_TX_DW5_LN0(port));
	val &= ~RTERM_SELECT_MASK;
	val |= RTERM_SELECT(6);
	val |= TAP3_DISABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_TX_DW5_GRP(port), val);

	/* Program PORT_TX_DW7 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_TX_DW7_LN0(port));
	val &= ~N_SCALAR_MASK;
	val |= N_SCALAR(ddi_translations[level].dw7_n_scalar);
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_TX_DW7_GRP(port), val);
पूर्ण

अटल व्योम cnl_ddi_vswing_sequence(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	पूर्णांक width, rate, ln;
	u32 val;

	width = crtc_state->lane_count;
	rate = crtc_state->port_घड़ी;

	/*
	 * 1. If port type is eDP or DP,
	 * set PORT_PCS_DW1 cmnkeeper_enable to 1b,
	 * अन्यथा clear to 0b.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_PCS_DW1_LN0(port));
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		val &= ~COMMON_KEEPER_EN;
	अन्यथा
		val |= COMMON_KEEPER_EN;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_PCS_DW1_GRP(port), val);

	/* 2. Program loadgen select */
	/*
	 * Program PORT_TX_DW4_LN depending on Bit rate and used lanes
	 * <= 6 GHz and 4 lanes (LN0=0, LN1=1, LN2=1, LN3=1)
	 * <= 6 GHz and 1,2 lanes (LN0=0, LN1=1, LN2=1, LN3=0)
	 * > 6 GHz (LN0=0, LN1=0, LN2=0, LN3=0)
	 */
	क्रम (ln = 0; ln <= 3; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_TX_DW4_LN(ln, port));
		val &= ~LOADGEN_SELECT;

		अगर ((rate <= 600000 && width == 4 && ln >= 1)  ||
		    (rate <= 600000 && width < 4 && (ln == 1 || ln == 2))) अणु
			val |= LOADGEN_SELECT;
		पूर्ण
		पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_TX_DW4_LN(ln, port), val);
	पूर्ण

	/* 3. Set PORT_CL_DW5 SUS Clock Config to 11b */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_CL1CM_DW5);
	val |= SUS_CLOCK_CONFIG;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_CL1CM_DW5, val);

	/* 4. Clear training enable to change swing values */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_TX_DW5_LN0(port));
	val &= ~TX_TRAINING_EN;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_TX_DW5_GRP(port), val);

	/* 5. Program swing and de-emphasis */
	cnl_ddi_vswing_program(encoder, crtc_state, level);

	/* 6. Set training enable to trigger update */
	val = पूर्णांकel_de_पढ़ो(dev_priv, CNL_PORT_TX_DW5_LN0(port));
	val |= TX_TRAINING_EN;
	पूर्णांकel_de_ग_लिखो(dev_priv, CNL_PORT_TX_DW5_GRP(port), val);
पूर्ण

अटल व्योम icl_ddi_combo_vswing_program(काष्ठा पूर्णांकel_encoder *encoder,
					 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					 पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	स्थिर काष्ठा cnl_ddi_buf_trans *ddi_translations;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);
	पूर्णांक n_entries, ln;
	u32 val;

	अगर (DISPLAY_VER(dev_priv) >= 12)
		ddi_translations = tgl_get_combo_buf_trans(encoder, crtc_state, &n_entries);
	अन्यथा अगर (IS_PLATFORM(dev_priv, INTEL_JASPERLAKE))
		ddi_translations = jsl_get_combo_buf_trans(encoder, crtc_state, &n_entries);
	अन्यथा अगर (IS_PLATFORM(dev_priv, INTEL_ELKHARTLAKE))
		ddi_translations = ehl_get_combo_buf_trans(encoder, crtc_state, &n_entries);
	अन्यथा
		ddi_translations = icl_get_combo_buf_trans(encoder, crtc_state, &n_entries);

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !ddi_translations))
		वापस;
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, level >= n_entries))
		level = n_entries - 1;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_EDP)) अणु
		काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

		val = EDP4K2K_MODE_OVRD_EN | EDP4K2K_MODE_OVRD_OPTIMIZED;
		पूर्णांकel_dp->hobl_active = is_hobl_buf_trans(ddi_translations);
		पूर्णांकel_de_rmw(dev_priv, ICL_PORT_CL_DW10(phy), val,
			     पूर्णांकel_dp->hobl_active ? val : 0);
	पूर्ण

	/* Set PORT_TX_DW5 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_LN0(phy));
	val &= ~(SCALING_MODE_SEL_MASK | RTERM_SELECT_MASK |
		  TAP2_DISABLE | TAP3_DISABLE);
	val |= SCALING_MODE_SEL(0x2);
	val |= RTERM_SELECT(0x6);
	val |= TAP3_DISABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_GRP(phy), val);

	/* Program PORT_TX_DW2 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW2_LN0(phy));
	val &= ~(SWING_SEL_LOWER_MASK | SWING_SEL_UPPER_MASK |
		 RCOMP_SCALAR_MASK);
	val |= SWING_SEL_UPPER(ddi_translations[level].dw2_swing_sel);
	val |= SWING_SEL_LOWER(ddi_translations[level].dw2_swing_sel);
	/* Program Rcomp scalar क्रम every table entry */
	val |= RCOMP_SCALAR(0x98);
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW2_GRP(phy), val);

	/* Program PORT_TX_DW4 */
	/* We cannot ग_लिखो to GRP. It would overग_लिखो inभागidual loadgen. */
	क्रम (ln = 0; ln <= 3; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW4_LN(ln, phy));
		val &= ~(POST_CURSOR_1_MASK | POST_CURSOR_2_MASK |
			 CURSOR_COEFF_MASK);
		val |= POST_CURSOR_1(ddi_translations[level].dw4_post_cursor_1);
		val |= POST_CURSOR_2(ddi_translations[level].dw4_post_cursor_2);
		val |= CURSOR_COEFF(ddi_translations[level].dw4_cursor_coeff);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW4_LN(ln, phy), val);
	पूर्ण

	/* Program PORT_TX_DW7 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW7_LN0(phy));
	val &= ~N_SCALAR_MASK;
	val |= N_SCALAR(ddi_translations[level].dw7_n_scalar);
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW7_GRP(phy), val);
पूर्ण

अटल व्योम icl_combo_phy_ddi_vswing_sequence(काष्ठा पूर्णांकel_encoder *encoder,
					      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					      पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);
	पूर्णांक width, rate, ln;
	u32 val;

	width = crtc_state->lane_count;
	rate = crtc_state->port_घड़ी;

	/*
	 * 1. If port type is eDP or DP,
	 * set PORT_PCS_DW1 cmnkeeper_enable to 1b,
	 * अन्यथा clear to 0b.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_PCS_DW1_LN0(phy));
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		val &= ~COMMON_KEEPER_EN;
	अन्यथा
		val |= COMMON_KEEPER_EN;
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_PCS_DW1_GRP(phy), val);

	/* 2. Program loadgen select */
	/*
	 * Program PORT_TX_DW4_LN depending on Bit rate and used lanes
	 * <= 6 GHz and 4 lanes (LN0=0, LN1=1, LN2=1, LN3=1)
	 * <= 6 GHz and 1,2 lanes (LN0=0, LN1=1, LN2=1, LN3=0)
	 * > 6 GHz (LN0=0, LN1=0, LN2=0, LN3=0)
	 */
	क्रम (ln = 0; ln <= 3; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW4_LN(ln, phy));
		val &= ~LOADGEN_SELECT;

		अगर ((rate <= 600000 && width == 4 && ln >= 1) ||
		    (rate <= 600000 && width < 4 && (ln == 1 || ln == 2))) अणु
			val |= LOADGEN_SELECT;
		पूर्ण
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW4_LN(ln, phy), val);
	पूर्ण

	/* 3. Set PORT_CL_DW5 SUS Clock Config to 11b */
	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_CL_DW5(phy));
	val |= SUS_CLOCK_CONFIG;
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_CL_DW5(phy), val);

	/* 4. Clear training enable to change swing values */
	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_LN0(phy));
	val &= ~TX_TRAINING_EN;
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_GRP(phy), val);

	/* 5. Program swing and de-emphasis */
	icl_ddi_combo_vswing_program(encoder, crtc_state, level);

	/* 6. Set training enable to trigger update */
	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_LN0(phy));
	val |= TX_TRAINING_EN;
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_GRP(phy), val);
पूर्ण

अटल व्योम icl_mg_phy_ddi_vswing_sequence(काष्ठा पूर्णांकel_encoder *encoder,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					   पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(dev_priv, encoder->port);
	स्थिर काष्ठा icl_mg_phy_ddi_buf_trans *ddi_translations;
	पूर्णांक n_entries, ln;
	u32 val;

	अगर (enc_to_dig_port(encoder)->tc_mode == TC_PORT_TBT_ALT)
		वापस;

	ddi_translations = icl_get_mg_buf_trans(encoder, crtc_state, &n_entries);

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !ddi_translations))
		वापस;
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, level >= n_entries))
		level = n_entries - 1;

	/* Set MG_TX_LINK_PARAMS cri_use_fs32 to 0. */
	क्रम (ln = 0; ln < 2; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_TX1_LINK_PARAMS(ln, tc_port));
		val &= ~CRI_USE_FS32;
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX1_LINK_PARAMS(ln, tc_port), val);

		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_TX2_LINK_PARAMS(ln, tc_port));
		val &= ~CRI_USE_FS32;
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX2_LINK_PARAMS(ln, tc_port), val);
	पूर्ण

	/* Program MG_TX_SWINGCTRL with values from vswing table */
	क्रम (ln = 0; ln < 2; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_TX1_SWINGCTRL(ln, tc_port));
		val &= ~CRI_TXDEEMPH_OVERRIDE_17_12_MASK;
		val |= CRI_TXDEEMPH_OVERRIDE_17_12(
			ddi_translations[level].cri_txdeemph_override_17_12);
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX1_SWINGCTRL(ln, tc_port), val);

		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_TX2_SWINGCTRL(ln, tc_port));
		val &= ~CRI_TXDEEMPH_OVERRIDE_17_12_MASK;
		val |= CRI_TXDEEMPH_OVERRIDE_17_12(
			ddi_translations[level].cri_txdeemph_override_17_12);
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX2_SWINGCTRL(ln, tc_port), val);
	पूर्ण

	/* Program MG_TX_DRVCTRL with values from vswing table */
	क्रम (ln = 0; ln < 2; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_TX1_DRVCTRL(ln, tc_port));
		val &= ~(CRI_TXDEEMPH_OVERRIDE_11_6_MASK |
			 CRI_TXDEEMPH_OVERRIDE_5_0_MASK);
		val |= CRI_TXDEEMPH_OVERRIDE_5_0(
			ddi_translations[level].cri_txdeemph_override_5_0) |
			CRI_TXDEEMPH_OVERRIDE_11_6(
				ddi_translations[level].cri_txdeemph_override_11_6) |
			CRI_TXDEEMPH_OVERRIDE_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX1_DRVCTRL(ln, tc_port), val);

		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_TX2_DRVCTRL(ln, tc_port));
		val &= ~(CRI_TXDEEMPH_OVERRIDE_11_6_MASK |
			 CRI_TXDEEMPH_OVERRIDE_5_0_MASK);
		val |= CRI_TXDEEMPH_OVERRIDE_5_0(
			ddi_translations[level].cri_txdeemph_override_5_0) |
			CRI_TXDEEMPH_OVERRIDE_11_6(
				ddi_translations[level].cri_txdeemph_override_11_6) |
			CRI_TXDEEMPH_OVERRIDE_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX2_DRVCTRL(ln, tc_port), val);

		/* FIXME: Program CRI_LOADGEN_SEL after the spec is updated */
	पूर्ण

	/*
	 * Program MG_CLKHUB<LN, port being used> with value from frequency table
	 * In हाल of Legacy mode on MG PHY, both TX1 and TX2 enabled so use the
	 * values from table क्रम which TX1 and TX2 enabled.
	 */
	क्रम (ln = 0; ln < 2; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_CLKHUB(ln, tc_port));
		अगर (crtc_state->port_घड़ी < 300000)
			val |= CFG_LOW_RATE_LKREN_EN;
		अन्यथा
			val &= ~CFG_LOW_RATE_LKREN_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_CLKHUB(ln, tc_port), val);
	पूर्ण

	/* Program the MG_TX_DCC<LN, port being used> based on the link frequency */
	क्रम (ln = 0; ln < 2; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_TX1_DCC(ln, tc_port));
		val &= ~CFG_AMI_CK_DIV_OVERRIDE_VAL_MASK;
		अगर (crtc_state->port_घड़ी <= 500000) अणु
			val &= ~CFG_AMI_CK_DIV_OVERRIDE_EN;
		पूर्ण अन्यथा अणु
			val |= CFG_AMI_CK_DIV_OVERRIDE_EN |
				CFG_AMI_CK_DIV_OVERRIDE_VAL(1);
		पूर्ण
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX1_DCC(ln, tc_port), val);

		val = पूर्णांकel_de_पढ़ो(dev_priv, MG_TX2_DCC(ln, tc_port));
		val &= ~CFG_AMI_CK_DIV_OVERRIDE_VAL_MASK;
		अगर (crtc_state->port_घड़ी <= 500000) अणु
			val &= ~CFG_AMI_CK_DIV_OVERRIDE_EN;
		पूर्ण अन्यथा अणु
			val |= CFG_AMI_CK_DIV_OVERRIDE_EN |
				CFG_AMI_CK_DIV_OVERRIDE_VAL(1);
		पूर्ण
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX2_DCC(ln, tc_port), val);
	पूर्ण

	/* Program MG_TX_PISO_READLOAD with values from vswing table */
	क्रम (ln = 0; ln < 2; ln++) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    MG_TX1_PISO_READLOAD(ln, tc_port));
		val |= CRI_CALCINIT;
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX1_PISO_READLOAD(ln, tc_port),
			       val);

		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    MG_TX2_PISO_READLOAD(ln, tc_port));
		val |= CRI_CALCINIT;
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_TX2_PISO_READLOAD(ln, tc_port),
			       val);
	पूर्ण
पूर्ण

अटल व्योम icl_ddi_vswing_sequence(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);

	अगर (पूर्णांकel_phy_is_combo(dev_priv, phy))
		icl_combo_phy_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा
		icl_mg_phy_ddi_vswing_sequence(encoder, crtc_state, level);
पूर्ण

अटल व्योम
tgl_dkl_phy_ddi_vswing_sequence(काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(dev_priv, encoder->port);
	स्थिर काष्ठा tgl_dkl_phy_ddi_buf_trans *ddi_translations;
	u32 val, dpcnt_mask, dpcnt_val;
	पूर्णांक n_entries, ln;

	अगर (enc_to_dig_port(encoder)->tc_mode == TC_PORT_TBT_ALT)
		वापस;

	ddi_translations = tgl_get_dkl_buf_trans(encoder, crtc_state, &n_entries);

	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, !ddi_translations))
		वापस;
	अगर (drm_WARN_ON_ONCE(&dev_priv->drm, level >= n_entries))
		level = n_entries - 1;

	dpcnt_mask = (DKL_TX_PRESHOOT_COEFF_MASK |
		      DKL_TX_DE_EMPAHSIS_COEFF_MASK |
		      DKL_TX_VSWING_CONTROL_MASK);
	dpcnt_val = DKL_TX_VSWING_CONTROL(ddi_translations[level].dkl_vswing_control);
	dpcnt_val |= DKL_TX_DE_EMPHASIS_COEFF(ddi_translations[level].dkl_de_emphasis_control);
	dpcnt_val |= DKL_TX_PRESHOOT_COEFF(ddi_translations[level].dkl_preshoot_control);

	क्रम (ln = 0; ln < 2; ln++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, HIP_INDEX_REG(tc_port),
			       HIP_INDEX_VAL(tc_port, ln));

		पूर्णांकel_de_ग_लिखो(dev_priv, DKL_TX_PMD_LANE_SUS(tc_port), 0);

		/* All the रेजिस्टरs are RMW */
		val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_TX_DPCNTL0(tc_port));
		val &= ~dpcnt_mask;
		val |= dpcnt_val;
		पूर्णांकel_de_ग_लिखो(dev_priv, DKL_TX_DPCNTL0(tc_port), val);

		val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_TX_DPCNTL1(tc_port));
		val &= ~dpcnt_mask;
		val |= dpcnt_val;
		पूर्णांकel_de_ग_लिखो(dev_priv, DKL_TX_DPCNTL1(tc_port), val);

		val = पूर्णांकel_de_पढ़ो(dev_priv, DKL_TX_DPCNTL2(tc_port));
		val &= ~DKL_TX_DP20BITMODE;
		पूर्णांकel_de_ग_लिखो(dev_priv, DKL_TX_DPCNTL2(tc_port), val);
	पूर्ण
पूर्ण

अटल व्योम tgl_ddi_vswing_sequence(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    पूर्णांक level)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);

	अगर (पूर्णांकel_phy_is_combo(dev_priv, phy))
		icl_combo_phy_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा
		tgl_dkl_phy_ddi_vswing_sequence(encoder, crtc_state, level);
पूर्ण

अटल पूर्णांक translate_संकेत_level(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  u8 संकेत_levels)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(index_to_dp_संकेत_levels); i++) अणु
		अगर (index_to_dp_संकेत_levels[i] == संकेत_levels)
			वापस i;
	पूर्ण

	drm_WARN(&i915->drm, 1,
		 "Unsupported voltage swing/pre-emphasis level: 0x%x\n",
		 संकेत_levels);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_ddi_dp_level(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	u8 train_set = पूर्णांकel_dp->train_set[0];
	u8 संकेत_levels = train_set & (DP_TRAIN_VOLTAGE_SWING_MASK |
					DP_TRAIN_PRE_EMPHASIS_MASK);

	वापस translate_संकेत_level(पूर्णांकel_dp, संकेत_levels);
पूर्ण

अटल व्योम
tgl_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	पूर्णांक level = पूर्णांकel_ddi_dp_level(पूर्णांकel_dp);

	tgl_ddi_vswing_sequence(encoder, crtc_state, level);
पूर्ण

अटल व्योम
icl_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	पूर्णांक level = पूर्णांकel_ddi_dp_level(पूर्णांकel_dp);

	icl_ddi_vswing_sequence(encoder, crtc_state, level);
पूर्ण

अटल व्योम
cnl_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	पूर्णांक level = पूर्णांकel_ddi_dp_level(पूर्णांकel_dp);

	cnl_ddi_vswing_sequence(encoder, crtc_state, level);
पूर्ण

अटल व्योम
bxt_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	पूर्णांक level = पूर्णांकel_ddi_dp_level(पूर्णांकel_dp);

	bxt_ddi_vswing_sequence(encoder, crtc_state, level);
पूर्ण

अटल व्योम
hsw_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	पूर्णांक level = पूर्णांकel_ddi_dp_level(पूर्णांकel_dp);
	क्रमागत port port = encoder->port;
	u32 संकेत_levels;

	संकेत_levels = DDI_BUF_TRANS_SELECT(level);

	drm_dbg_kms(&dev_priv->drm, "Using signal levels %08x\n",
		    संकेत_levels);

	पूर्णांकel_dp->DP &= ~DDI_BUF_EMP_MASK;
	पूर्णांकel_dp->DP |= संकेत_levels;

	अगर (IS_GEN9_BC(dev_priv))
		skl_ddi_set_iboost(encoder, crtc_state, level);

	पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(port), पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DDI_BUF_CTL(port));
पूर्ण

अटल व्योम _cnl_ddi_enable_घड़ी(काष्ठा drm_i915_निजी *i915, i915_reg_t reg,
				  u32 clk_sel_mask, u32 clk_sel, u32 clk_off)
अणु
	mutex_lock(&i915->dpll.lock);

	पूर्णांकel_de_rmw(i915, reg, clk_sel_mask, clk_sel);

	/*
	 * "This step and the step beक्रमe must be
	 *  करोne with separate रेजिस्टर ग_लिखोs."
	 */
	पूर्णांकel_de_rmw(i915, reg, clk_off, 0);

	mutex_unlock(&i915->dpll.lock);
पूर्ण

अटल व्योम _cnl_ddi_disable_घड़ी(काष्ठा drm_i915_निजी *i915, i915_reg_t reg,
				   u32 clk_off)
अणु
	mutex_lock(&i915->dpll.lock);

	पूर्णांकel_de_rmw(i915, reg, 0, clk_off);

	mutex_unlock(&i915->dpll.lock);
पूर्ण

अटल bool _cnl_ddi_is_घड़ी_enabled(काष्ठा drm_i915_निजी *i915, i915_reg_t reg,
				      u32 clk_off)
अणु
	वापस !(पूर्णांकel_de_पढ़ो(i915, reg) & clk_off);
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *
_cnl_ddi_get_pll(काष्ठा drm_i915_निजी *i915, i915_reg_t reg,
		 u32 clk_sel_mask, u32 clk_sel_shअगरt)
अणु
	क्रमागत पूर्णांकel_dpll_id id;

	id = (पूर्णांकel_de_पढ़ो(i915, reg) & clk_sel_mask) >> clk_sel_shअगरt;

	वापस पूर्णांकel_get_shared_dpll_by_id(i915, id);
पूर्ण

अटल व्योम adls_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	_cnl_ddi_enable_घड़ी(i915, ADLS_DPCLKA_CFGCR(phy),
			      ADLS_DPCLKA_CFGCR_DDI_CLK_SEL_MASK(phy),
			      pll->info->id << ADLS_DPCLKA_CFGCR_DDI_SHIFT(phy),
			      ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल व्योम adls_ddi_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	_cnl_ddi_disable_घड़ी(i915, ADLS_DPCLKA_CFGCR(phy),
			       ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल bool adls_ddi_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	वापस _cnl_ddi_is_घड़ी_enabled(i915, ADLS_DPCLKA_CFGCR(phy),
					 ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *adls_ddi_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	वापस _cnl_ddi_get_pll(i915, ADLS_DPCLKA_CFGCR(phy),
				ADLS_DPCLKA_CFGCR_DDI_CLK_SEL_MASK(phy),
				ADLS_DPCLKA_CFGCR_DDI_SHIFT(phy));
पूर्ण

अटल व्योम rkl_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	_cnl_ddi_enable_घड़ी(i915, ICL_DPCLKA_CFGCR0,
			      RKL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy),
			      RKL_DPCLKA_CFGCR0_DDI_CLK_SEL(pll->info->id, phy),
			      RKL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल व्योम rkl_ddi_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	_cnl_ddi_disable_घड़ी(i915, ICL_DPCLKA_CFGCR0,
			       RKL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल bool rkl_ddi_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	वापस _cnl_ddi_is_घड़ी_enabled(i915, ICL_DPCLKA_CFGCR0,
					 RKL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *rkl_ddi_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	वापस _cnl_ddi_get_pll(i915, ICL_DPCLKA_CFGCR0,
				RKL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy),
				RKL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy));
पूर्ण

अटल व्योम dg1_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	/*
	 * If we fail this, something went very wrong: first 2 PLLs should be
	 * used by first 2 phys and last 2 PLLs by last phys
	 */
	अगर (drm_WARN_ON(&i915->drm,
			(pll->info->id < DPLL_ID_DG1_DPLL2 && phy >= PHY_C) ||
			(pll->info->id >= DPLL_ID_DG1_DPLL2 && phy < PHY_C)))
		वापस;

	_cnl_ddi_enable_घड़ी(i915, DG1_DPCLKA_CFGCR0(phy),
			      DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy),
			      DG1_DPCLKA_CFGCR0_DDI_CLK_SEL(pll->info->id, phy),
			      DG1_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल व्योम dg1_ddi_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	_cnl_ddi_disable_घड़ी(i915, DG1_DPCLKA_CFGCR0(phy),
			       DG1_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल bool dg1_ddi_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	वापस _cnl_ddi_is_घड़ी_enabled(i915, DG1_DPCLKA_CFGCR0(phy),
					 DG1_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *dg1_ddi_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	वापस _cnl_ddi_get_pll(i915, DG1_DPCLKA_CFGCR0(phy),
				DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy),
				DG1_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy));
पूर्ण

अटल व्योम icl_ddi_combo_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	_cnl_ddi_enable_घड़ी(i915, ICL_DPCLKA_CFGCR0,
			      ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy),
			      ICL_DPCLKA_CFGCR0_DDI_CLK_SEL(pll->info->id, phy),
			      ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल व्योम icl_ddi_combo_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	_cnl_ddi_disable_घड़ी(i915, ICL_DPCLKA_CFGCR0,
			       ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

अटल bool icl_ddi_combo_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	वापस _cnl_ddi_is_घड़ी_enabled(i915, ICL_DPCLKA_CFGCR0,
					 ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy));
पूर्ण

काष्ठा पूर्णांकel_shared_dpll *icl_ddi_combo_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	वापस _cnl_ddi_get_pll(i915, ICL_DPCLKA_CFGCR0,
				ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy),
				ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(phy));
पूर्ण

अटल व्योम jsl_ddi_tc_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत port port = encoder->port;

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	/*
	 * "For DDIC and DDID, program DDI_CLK_SEL to map the MG घड़ी to the port.
	 *  MG करोes not exist, but the programming is required to ungate DDIC and DDID."
	 */
	पूर्णांकel_de_ग_लिखो(i915, DDI_CLK_SEL(port), DDI_CLK_SEL_MG);

	icl_ddi_combo_enable_घड़ी(encoder, crtc_state);
पूर्ण

अटल व्योम jsl_ddi_tc_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;

	icl_ddi_combo_disable_घड़ी(encoder);

	पूर्णांकel_de_ग_लिखो(i915, DDI_CLK_SEL(port), DDI_CLK_SEL_NONE);
पूर्ण

अटल bool jsl_ddi_tc_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(i915, DDI_CLK_SEL(port));

	अगर ((पंचांगp & DDI_CLK_SEL_MASK) == DDI_CLK_SEL_NONE)
		वापस false;

	वापस icl_ddi_combo_is_घड़ी_enabled(encoder);
पूर्ण

अटल व्योम icl_ddi_tc_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(i915, encoder->port);
	क्रमागत port port = encoder->port;

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	पूर्णांकel_de_ग_लिखो(i915, DDI_CLK_SEL(port),
		       icl_pll_to_ddi_clk_sel(encoder, crtc_state));

	mutex_lock(&i915->dpll.lock);

	पूर्णांकel_de_rmw(i915, ICL_DPCLKA_CFGCR0,
		     ICL_DPCLKA_CFGCR0_TC_CLK_OFF(tc_port), 0);

	mutex_unlock(&i915->dpll.lock);
पूर्ण

अटल व्योम icl_ddi_tc_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(i915, encoder->port);
	क्रमागत port port = encoder->port;

	mutex_lock(&i915->dpll.lock);

	पूर्णांकel_de_rmw(i915, ICL_DPCLKA_CFGCR0,
		     0, ICL_DPCLKA_CFGCR0_TC_CLK_OFF(tc_port));

	mutex_unlock(&i915->dpll.lock);

	पूर्णांकel_de_ग_लिखो(i915, DDI_CLK_SEL(port), DDI_CLK_SEL_NONE);
पूर्ण

अटल bool icl_ddi_tc_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(i915, encoder->port);
	क्रमागत port port = encoder->port;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(i915, DDI_CLK_SEL(port));

	अगर ((पंचांगp & DDI_CLK_SEL_MASK) == DDI_CLK_SEL_NONE)
		वापस false;

	पंचांगp = पूर्णांकel_de_पढ़ो(i915, ICL_DPCLKA_CFGCR0);

	वापस !(पंचांगp & ICL_DPCLKA_CFGCR0_TC_CLK_OFF(tc_port));
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *icl_ddi_tc_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(i915, encoder->port);
	क्रमागत port port = encoder->port;
	क्रमागत पूर्णांकel_dpll_id id;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(i915, DDI_CLK_SEL(port));

	चयन (पंचांगp & DDI_CLK_SEL_MASK) अणु
	हाल DDI_CLK_SEL_TBT_162:
	हाल DDI_CLK_SEL_TBT_270:
	हाल DDI_CLK_SEL_TBT_540:
	हाल DDI_CLK_SEL_TBT_810:
		id = DPLL_ID_ICL_TBTPLL;
		अवरोध;
	हाल DDI_CLK_SEL_MG:
		id = icl_tc_port_to_pll_id(tc_port);
		अवरोध;
	शेष:
		MISSING_CASE(पंचांगp);
		fallthrough;
	हाल DDI_CLK_SEL_NONE:
		वापस शून्य;
	पूर्ण

	वापस पूर्णांकel_get_shared_dpll_by_id(i915, id);
पूर्ण

अटल व्योम cnl_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत port port = encoder->port;

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	_cnl_ddi_enable_घड़ी(i915, DPCLKA_CFGCR0,
			      DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(port),
			      DPCLKA_CFGCR0_DDI_CLK_SEL(pll->info->id, port),
			      DPCLKA_CFGCR0_DDI_CLK_OFF(port));
पूर्ण

अटल व्योम cnl_ddi_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;

	_cnl_ddi_disable_घड़ी(i915, DPCLKA_CFGCR0,
			       DPCLKA_CFGCR0_DDI_CLK_OFF(port));
पूर्ण

अटल bool cnl_ddi_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;

	वापस _cnl_ddi_is_घड़ी_enabled(i915, DPCLKA_CFGCR0,
					 DPCLKA_CFGCR0_DDI_CLK_OFF(port));
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *cnl_ddi_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;

	वापस _cnl_ddi_get_pll(i915, DPCLKA_CFGCR0,
				DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(port),
				DPCLKA_CFGCR0_DDI_CLK_SEL_SHIFT(port));
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *bxt_ddi_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत पूर्णांकel_dpll_id id;

	चयन (encoder->port) अणु
	हाल PORT_A:
		id = DPLL_ID_SKL_DPLL0;
		अवरोध;
	हाल PORT_B:
		id = DPLL_ID_SKL_DPLL1;
		अवरोध;
	हाल PORT_C:
		id = DPLL_ID_SKL_DPLL2;
		अवरोध;
	शेष:
		MISSING_CASE(encoder->port);
		वापस शून्य;
	पूर्ण

	वापस पूर्णांकel_get_shared_dpll_by_id(i915, id);
पूर्ण

अटल व्योम skl_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत port port = encoder->port;

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	mutex_lock(&i915->dpll.lock);

	पूर्णांकel_de_rmw(i915, DPLL_CTRL2,
		     DPLL_CTRL2_DDI_CLK_OFF(port) |
		     DPLL_CTRL2_DDI_CLK_SEL_MASK(port),
		     DPLL_CTRL2_DDI_CLK_SEL(pll->info->id, port) |
		     DPLL_CTRL2_DDI_SEL_OVERRIDE(port));

	mutex_unlock(&i915->dpll.lock);
पूर्ण

अटल व्योम skl_ddi_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;

	mutex_lock(&i915->dpll.lock);

	पूर्णांकel_de_rmw(i915, DPLL_CTRL2,
		     0, DPLL_CTRL2_DDI_CLK_OFF(port));

	mutex_unlock(&i915->dpll.lock);
पूर्ण

अटल bool skl_ddi_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;

	/*
	 * FIXME Not sure अगर the override affects both
	 * the PLL selection and the CLK_OFF bit.
	 */
	वापस !(पूर्णांकel_de_पढ़ो(i915, DPLL_CTRL2) & DPLL_CTRL2_DDI_CLK_OFF(port));
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *skl_ddi_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	क्रमागत पूर्णांकel_dpll_id id;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(i915, DPLL_CTRL2);

	/*
	 * FIXME Not sure अगर the override affects both
	 * the PLL selection and the CLK_OFF bit.
	 */
	अगर ((पंचांगp & DPLL_CTRL2_DDI_SEL_OVERRIDE(port)) == 0)
		वापस शून्य;

	id = (पंचांगp & DPLL_CTRL2_DDI_CLK_SEL_MASK(port)) >>
		DPLL_CTRL2_DDI_CLK_SEL_SHIFT(port);

	वापस पूर्णांकel_get_shared_dpll_by_id(i915, id);
पूर्ण

व्योम hsw_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	स्थिर काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत port port = encoder->port;

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	पूर्णांकel_de_ग_लिखो(i915, PORT_CLK_SEL(port), hsw_pll_to_ddi_pll_sel(pll));
पूर्ण

व्योम hsw_ddi_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;

	पूर्णांकel_de_ग_लिखो(i915, PORT_CLK_SEL(port), PORT_CLK_SEL_NONE);
पूर्ण

bool hsw_ddi_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;

	वापस पूर्णांकel_de_पढ़ो(i915, PORT_CLK_SEL(port)) != PORT_CLK_SEL_NONE;
पूर्ण

अटल काष्ठा पूर्णांकel_shared_dpll *hsw_ddi_get_pll(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	क्रमागत पूर्णांकel_dpll_id id;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(i915, PORT_CLK_SEL(port));

	चयन (पंचांगp & PORT_CLK_SEL_MASK) अणु
	हाल PORT_CLK_SEL_WRPLL1:
		id = DPLL_ID_WRPLL1;
		अवरोध;
	हाल PORT_CLK_SEL_WRPLL2:
		id = DPLL_ID_WRPLL2;
		अवरोध;
	हाल PORT_CLK_SEL_SPLL:
		id = DPLL_ID_SPLL;
		अवरोध;
	हाल PORT_CLK_SEL_LCPLL_810:
		id = DPLL_ID_LCPLL_810;
		अवरोध;
	हाल PORT_CLK_SEL_LCPLL_1350:
		id = DPLL_ID_LCPLL_1350;
		अवरोध;
	हाल PORT_CLK_SEL_LCPLL_2700:
		id = DPLL_ID_LCPLL_2700;
		अवरोध;
	शेष:
		MISSING_CASE(पंचांगp);
		fallthrough;
	हाल PORT_CLK_SEL_NONE:
		वापस शून्य;
	पूर्ण

	वापस पूर्णांकel_get_shared_dpll_by_id(i915, id);
पूर्ण

व्योम पूर्णांकel_ddi_enable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (encoder->enable_घड़ी)
		encoder->enable_घड़ी(encoder, crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_ddi_disable_घड़ी(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	अगर (encoder->disable_घड़ी)
		encoder->disable_घड़ी(encoder);
पूर्ण

व्योम पूर्णांकel_ddi_sanitize_encoder_pll_mapping(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	u32 port_mask;
	bool ddi_clk_needed;

	/*
	 * In हाल of DP MST, we sanitize the primary encoder only, not the
	 * भव ones.
	 */
	अगर (encoder->type == INTEL_OUTPUT_DP_MST)
		वापस;

	अगर (!encoder->base.crtc && पूर्णांकel_encoder_is_dp(encoder)) अणु
		u8 pipe_mask;
		bool is_mst;

		पूर्णांकel_ddi_get_encoder_pipes(encoder, &pipe_mask, &is_mst);
		/*
		 * In the unlikely हाल that BIOS enables DP in MST mode, just
		 * warn since our MST HW पढ़ोout is incomplete.
		 */
		अगर (drm_WARN_ON(&i915->drm, is_mst))
			वापस;
	पूर्ण

	port_mask = BIT(encoder->port);
	ddi_clk_needed = encoder->base.crtc;

	अगर (encoder->type == INTEL_OUTPUT_DSI) अणु
		काष्ठा पूर्णांकel_encoder *other_encoder;

		port_mask = पूर्णांकel_dsi_encoder_ports(encoder);
		/*
		 * Sanity check that we haven't incorrectly रेजिस्टरed another
		 * encoder using any of the ports of this DSI encoder.
		 */
		क्रम_each_पूर्णांकel_encoder(&i915->drm, other_encoder) अणु
			अगर (other_encoder == encoder)
				जारी;

			अगर (drm_WARN_ON(&i915->drm,
					port_mask & BIT(other_encoder->port)))
				वापस;
		पूर्ण
		/*
		 * For DSI we keep the ddi घड़ीs gated
		 * except during enable/disable sequence.
		 */
		ddi_clk_needed = false;
	पूर्ण

	अगर (ddi_clk_needed || !encoder->disable_घड़ी ||
	    !encoder->is_घड़ी_enabled(encoder))
		वापस;

	drm_notice(&i915->drm,
		   "[ENCODER:%d:%s] is disabled/in DSI mode with an ungated DDI clock, gate it\n",
		   encoder->base.base.id, encoder->base.name);

	encoder->disable_घड़ी(encoder);
पूर्ण

अटल व्योम
icl_program_mg_dp_mode(काष्ठा पूर्णांकel_digital_port *dig_port,
		       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(dev_priv, dig_port->base.port);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, dig_port->base.port);
	u32 ln0, ln1, pin_assignment;
	u8 width;

	अगर (!पूर्णांकel_phy_is_tc(dev_priv, phy) ||
	    dig_port->tc_mode == TC_PORT_TBT_ALT)
		वापस;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, HIP_INDEX_REG(tc_port),
			       HIP_INDEX_VAL(tc_port, 0x0));
		ln0 = पूर्णांकel_de_पढ़ो(dev_priv, DKL_DP_MODE(tc_port));
		पूर्णांकel_de_ग_लिखो(dev_priv, HIP_INDEX_REG(tc_port),
			       HIP_INDEX_VAL(tc_port, 0x1));
		ln1 = पूर्णांकel_de_पढ़ो(dev_priv, DKL_DP_MODE(tc_port));
	पूर्ण अन्यथा अणु
		ln0 = पूर्णांकel_de_पढ़ो(dev_priv, MG_DP_MODE(0, tc_port));
		ln1 = पूर्णांकel_de_पढ़ो(dev_priv, MG_DP_MODE(1, tc_port));
	पूर्ण

	ln0 &= ~(MG_DP_MODE_CFG_DP_X1_MODE | MG_DP_MODE_CFG_DP_X2_MODE);
	ln1 &= ~(MG_DP_MODE_CFG_DP_X1_MODE | MG_DP_MODE_CFG_DP_X2_MODE);

	/* DPPATC */
	pin_assignment = पूर्णांकel_tc_port_get_pin_assignment_mask(dig_port);
	width = crtc_state->lane_count;

	चयन (pin_assignment) अणु
	हाल 0x0:
		drm_WARN_ON(&dev_priv->drm,
			    dig_port->tc_mode != TC_PORT_LEGACY);
		अगर (width == 1) अणु
			ln1 |= MG_DP_MODE_CFG_DP_X1_MODE;
		पूर्ण अन्यथा अणु
			ln0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			ln1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		पूर्ण
		अवरोध;
	हाल 0x1:
		अगर (width == 4) अणु
			ln0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			ln1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		पूर्ण
		अवरोध;
	हाल 0x2:
		अगर (width == 2) अणु
			ln0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			ln1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		पूर्ण
		अवरोध;
	हाल 0x3:
	हाल 0x5:
		अगर (width == 1) अणु
			ln0 |= MG_DP_MODE_CFG_DP_X1_MODE;
			ln1 |= MG_DP_MODE_CFG_DP_X1_MODE;
		पूर्ण अन्यथा अणु
			ln0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			ln1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		पूर्ण
		अवरोध;
	हाल 0x4:
	हाल 0x6:
		अगर (width == 1) अणु
			ln0 |= MG_DP_MODE_CFG_DP_X1_MODE;
			ln1 |= MG_DP_MODE_CFG_DP_X1_MODE;
		पूर्ण अन्यथा अणु
			ln0 |= MG_DP_MODE_CFG_DP_X2_MODE;
			ln1 |= MG_DP_MODE_CFG_DP_X2_MODE;
		पूर्ण
		अवरोध;
	शेष:
		MISSING_CASE(pin_assignment);
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, HIP_INDEX_REG(tc_port),
			       HIP_INDEX_VAL(tc_port, 0x0));
		पूर्णांकel_de_ग_लिखो(dev_priv, DKL_DP_MODE(tc_port), ln0);
		पूर्णांकel_de_ग_लिखो(dev_priv, HIP_INDEX_REG(tc_port),
			       HIP_INDEX_VAL(tc_port, 0x1));
		पूर्णांकel_de_ग_लिखो(dev_priv, DKL_DP_MODE(tc_port), ln1);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_DP_MODE(0, tc_port), ln0);
		पूर्णांकel_de_ग_लिखो(dev_priv, MG_DP_MODE(1, tc_port), ln1);
	पूर्ण
पूर्ण

अटल क्रमागत transcoder
tgl_dp_tp_transcoder(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST))
		वापस crtc_state->mst_master_transcoder;
	अन्यथा
		वापस crtc_state->cpu_transcoder;
पूर्ण

i915_reg_t dp_tp_ctl_reg(काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		वापस TGL_DP_TP_CTL(tgl_dp_tp_transcoder(crtc_state));
	अन्यथा
		वापस DP_TP_CTL(encoder->port);
पूर्ण

i915_reg_t dp_tp_status_reg(काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		वापस TGL_DP_TP_STATUS(tgl_dp_tp_transcoder(crtc_state));
	अन्यथा
		वापस DP_TP_STATUS(encoder->port);
पूर्ण

अटल व्योम पूर्णांकel_dp_sink_set_msa_timing_par_ignore_state(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
							  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
							  bool enable)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	अगर (!crtc_state->vrr.enable)
		वापस;

	अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_DOWNSPREAD_CTRL,
			       enable ? DP_MSA_TIMING_PAR_IGNORE_EN : 0) <= 0)
		drm_dbg_kms(&i915->drm,
			    "Failed to set MSA_TIMING_PAR_IGNORE %s in the sink\n",
			    enable ? "enable" : "disable");
पूर्ण

अटल व्योम पूर्णांकel_dp_sink_set_fec_पढ़ोy(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = dp_to_i915(पूर्णांकel_dp);

	अगर (!crtc_state->fec_enable)
		वापस;

	अगर (drm_dp_dpcd_ग_लिखोb(&पूर्णांकel_dp->aux, DP_FEC_CONFIGURATION, DP_FEC_READY) <= 0)
		drm_dbg_kms(&i915->drm,
			    "Failed to set FEC_READY in the sink\n");
पूर्ण

अटल व्योम पूर्णांकel_ddi_enable_fec(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;
	u32 val;

	अगर (!crtc_state->fec_enable)
		वापस;

	पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	val = पूर्णांकel_de_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));
	val |= DP_TP_CTL_FEC_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state), val);
पूर्ण

अटल व्योम पूर्णांकel_ddi_disable_fec_state(काष्ठा पूर्णांकel_encoder *encoder,
					स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;
	u32 val;

	अगर (!crtc_state->fec_enable)
		वापस;

	पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	val = पूर्णांकel_de_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));
	val &= ~DP_TP_CTL_FEC_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state), val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));
पूर्ण

अटल व्योम पूर्णांकel_ddi_घातer_up_lanes(काष्ठा पूर्णांकel_encoder *encoder,
				     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);

	अगर (पूर्णांकel_phy_is_combo(i915, phy)) अणु
		bool lane_reversal =
			dig_port->saved_port_bits & DDI_BUF_PORT_REVERSAL;

		पूर्णांकel_combo_phy_घातer_up_lanes(i915, phy, false,
					       crtc_state->lane_count,
					       lane_reversal);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_ddi_mso_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				     काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 dss1;

	अगर (!HAS_MSO(i915))
		वापस;

	dss1 = पूर्णांकel_de_पढ़ो(i915, ICL_PIPE_DSS_CTL1(pipe));

	pipe_config->splitter.enable = dss1 & SPLITTER_ENABLE;
	अगर (!pipe_config->splitter.enable)
		वापस;

	/* Splitter enable is supported क्रम pipe A only. */
	अगर (drm_WARN_ON(&i915->drm, pipe != PIPE_A)) अणु
		pipe_config->splitter.enable = false;
		वापस;
	पूर्ण

	चयन (dss1 & SPLITTER_CONFIGURATION_MASK) अणु
	शेष:
		drm_WARN(&i915->drm, true,
			 "Invalid splitter configuration, dss1=0x%08x\n", dss1);
		fallthrough;
	हाल SPLITTER_CONFIGURATION_2_SEGMENT:
		pipe_config->splitter.link_count = 2;
		अवरोध;
	हाल SPLITTER_CONFIGURATION_4_SEGMENT:
		pipe_config->splitter.link_count = 4;
		अवरोध;
	पूर्ण

	pipe_config->splitter.pixel_overlap = REG_FIELD_GET(OVERLAP_PIXELS_MASK, dss1);
पूर्ण

अटल व्योम पूर्णांकel_ddi_mso_configure(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 dss1 = 0;

	अगर (!HAS_MSO(i915))
		वापस;

	अगर (crtc_state->splitter.enable) अणु
		/* Splitter enable is supported क्रम pipe A only. */
		अगर (drm_WARN_ON(&i915->drm, pipe != PIPE_A))
			वापस;

		dss1 |= SPLITTER_ENABLE;
		dss1 |= OVERLAP_PIXELS(crtc_state->splitter.pixel_overlap);
		अगर (crtc_state->splitter.link_count == 2)
			dss1 |= SPLITTER_CONFIGURATION_2_SEGMENT;
		अन्यथा
			dss1 |= SPLITTER_CONFIGURATION_4_SEGMENT;
	पूर्ण

	पूर्णांकel_de_rmw(i915, ICL_PIPE_DSS_CTL1(pipe),
		     SPLITTER_ENABLE | SPLITTER_CONFIGURATION_MASK |
		     OVERLAP_PIXELS_MASK, dss1);
पूर्ण

अटल व्योम tgl_ddi_pre_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	bool is_mst = पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST);
	पूर्णांक level = पूर्णांकel_ddi_dp_level(पूर्णांकel_dp);

	पूर्णांकel_dp_set_link_params(पूर्णांकel_dp,
				 crtc_state->port_घड़ी,
				 crtc_state->lane_count);

	/*
	 * 1. Enable Power Wells
	 *
	 * This was handled at the beginning of पूर्णांकel_atomic_commit_tail(),
	 * beक्रमe we called करोwn पूर्णांकo this function.
	 */

	/* 2. Enable Panel Power अगर PPS is required */
	पूर्णांकel_pps_on(पूर्णांकel_dp);

	/*
	 * 3. For non-TBT Type-C ports, set FIA lane count
	 * (DFLEXDPSP.DPX4TXLATC)
	 *
	 * This was करोne beक्रमe tgl_ddi_pre_enable_dp by
	 * hsw_crtc_enable()->पूर्णांकel_encoders_pre_pll_enable().
	 */

	/*
	 * 4. Enable the port PLL.
	 *
	 * The PLL enabling itself was alपढ़ोy करोne beक्रमe this function by
	 * hsw_crtc_enable()->पूर्णांकel_enable_shared_dpll().  We need only
	 * configure the PLL to port mapping here.
	 */
	पूर्णांकel_ddi_enable_घड़ी(encoder, crtc_state);

	/* 5. If IO घातer is controlled through PWR_WELL_CTL, Enable IO Power */
	अगर (!पूर्णांकel_phy_is_tc(dev_priv, phy) ||
	    dig_port->tc_mode != TC_PORT_TBT_ALT) अणु
		drm_WARN_ON(&dev_priv->drm, dig_port->ddi_io_wakeref);
		dig_port->ddi_io_wakeref = पूर्णांकel_display_घातer_get(dev_priv,
								   dig_port->ddi_io_घातer_करोमुख्य);
	पूर्ण

	/* 6. Program DP_MODE */
	icl_program_mg_dp_mode(dig_port, crtc_state);

	/*
	 * 7. The rest of the below are substeps under the bspec's "Enable and
	 * Train Display Port" step.  Note that steps that are specअगरic to
	 * MST will be handled by पूर्णांकel_mst_pre_enable_dp() beक्रमe/after it
	 * calls पूर्णांकo this function.  Also पूर्णांकel_mst_pre_enable_dp() only calls
	 * us when active_mst_links==0, so any steps designated क्रम "single
	 * stream or multi-stream master transcoder" can just be perक्रमmed
	 * unconditionally here.
	 */

	/*
	 * 7.a Configure Transcoder Clock Select to direct the Port घड़ी to the
	 * Transcoder.
	 */
	पूर्णांकel_ddi_enable_pipe_घड़ी(encoder, crtc_state);

	/*
	 * 7.b Configure TRANS_DDI_FUNC_CTL DDI Select, DDI Mode Select & MST
	 * Transport Select
	 */
	पूर्णांकel_ddi_config_transcoder_func(encoder, crtc_state);

	/*
	 * 7.c Configure & enable DP_TP_CTL with link training pattern 1
	 * selected
	 *
	 * This will be handled by the पूर्णांकel_dp_start_link_train() farther
	 * करोwn this function.
	 */

	/* 7.e Configure voltage swing and related IO settings */
	tgl_ddi_vswing_sequence(encoder, crtc_state, level);

	/*
	 * 7.f Combo PHY: Configure PORT_CL_DW10 Static Power Down to घातer up
	 * the used lanes of the DDI.
	 */
	पूर्णांकel_ddi_घातer_up_lanes(encoder, crtc_state);

	/*
	 * 7.g Program CoG/MSO configuration bits in DSS_CTL1 अगर selected.
	 */
	पूर्णांकel_ddi_mso_configure(crtc_state);

	/*
	 * 7.g Configure and enable DDI_BUF_CTL
	 * 7.h Wait क्रम DDI_BUF_CTL DDI Idle Status = 0b (Not Idle), समयout
	 *     after 500 us.
	 *
	 * We only configure what the रेजिस्टर value will be here.  Actual
	 * enabling happens during link training farther करोwn.
	 */
	पूर्णांकel_ddi_init_dp_buf_reg(encoder, crtc_state);

	अगर (!is_mst)
		पूर्णांकel_dp_set_घातer(पूर्णांकel_dp, DP_SET_POWER_D0);

	पूर्णांकel_dp_configure_protocol_converter(पूर्णांकel_dp, crtc_state);
	पूर्णांकel_dp_sink_set_decompression_state(पूर्णांकel_dp, crtc_state, true);
	/*
	 * DDI FEC: "anticipates enabling FEC encoding sets the FEC_READY bit
	 * in the FEC_CONFIGURATION रेजिस्टर to 1 beक्रमe initiating link
	 * training
	 */
	पूर्णांकel_dp_sink_set_fec_पढ़ोy(पूर्णांकel_dp, crtc_state);

	पूर्णांकel_dp_check_frl_training(पूर्णांकel_dp);
	पूर्णांकel_dp_pcon_dsc_configure(पूर्णांकel_dp, crtc_state);

	/*
	 * 7.i Follow DisplayPort specअगरication training sequence (see notes क्रम
	 *     failure handling)
	 * 7.j If DisplayPort multi-stream - Set DP_TP_CTL link training to Idle
	 *     Pattern, रुको क्रम 5 idle patterns (DP_TP_STATUS Min_Idles_Sent)
	 *     (समयout after 800 us)
	 */
	पूर्णांकel_dp_start_link_train(पूर्णांकel_dp, crtc_state);

	/* 7.k Set DP_TP_CTL link training to Normal */
	अगर (!is_trans_port_sync_mode(crtc_state))
		पूर्णांकel_dp_stop_link_train(पूर्णांकel_dp, crtc_state);

	/* 7.l Configure and enable FEC अगर needed */
	पूर्णांकel_ddi_enable_fec(encoder, crtc_state);
	अगर (!crtc_state->bigjoiner)
		पूर्णांकel_dsc_enable(encoder, crtc_state);
पूर्ण

अटल व्योम hsw_ddi_pre_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, port);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	bool is_mst = पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST);
	पूर्णांक level = पूर्णांकel_ddi_dp_level(पूर्णांकel_dp);

	अगर (DISPLAY_VER(dev_priv) < 11)
		drm_WARN_ON(&dev_priv->drm,
			    is_mst && (port == PORT_A || port == PORT_E));
	अन्यथा
		drm_WARN_ON(&dev_priv->drm, is_mst && port == PORT_A);

	पूर्णांकel_dp_set_link_params(पूर्णांकel_dp,
				 crtc_state->port_घड़ी,
				 crtc_state->lane_count);

	पूर्णांकel_pps_on(पूर्णांकel_dp);

	पूर्णांकel_ddi_enable_घड़ी(encoder, crtc_state);

	अगर (!पूर्णांकel_phy_is_tc(dev_priv, phy) ||
	    dig_port->tc_mode != TC_PORT_TBT_ALT) अणु
		drm_WARN_ON(&dev_priv->drm, dig_port->ddi_io_wakeref);
		dig_port->ddi_io_wakeref = पूर्णांकel_display_घातer_get(dev_priv,
								   dig_port->ddi_io_घातer_करोमुख्य);
	पूर्ण

	icl_program_mg_dp_mode(dig_port, crtc_state);

	अगर (DISPLAY_VER(dev_priv) >= 11)
		icl_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा अगर (IS_CANNONLAKE(dev_priv))
		cnl_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		bxt_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा
		पूर्णांकel_prepare_dp_ddi_buffers(encoder, crtc_state);

	पूर्णांकel_ddi_घातer_up_lanes(encoder, crtc_state);

	पूर्णांकel_ddi_init_dp_buf_reg(encoder, crtc_state);
	अगर (!is_mst)
		पूर्णांकel_dp_set_घातer(पूर्णांकel_dp, DP_SET_POWER_D0);
	पूर्णांकel_dp_configure_protocol_converter(पूर्णांकel_dp, crtc_state);
	पूर्णांकel_dp_sink_set_decompression_state(पूर्णांकel_dp, crtc_state,
					      true);
	पूर्णांकel_dp_sink_set_fec_पढ़ोy(पूर्णांकel_dp, crtc_state);
	पूर्णांकel_dp_start_link_train(पूर्णांकel_dp, crtc_state);
	अगर ((port != PORT_A || DISPLAY_VER(dev_priv) >= 9) &&
	    !is_trans_port_sync_mode(crtc_state))
		पूर्णांकel_dp_stop_link_train(पूर्णांकel_dp, crtc_state);

	पूर्णांकel_ddi_enable_fec(encoder, crtc_state);

	अगर (!is_mst)
		पूर्णांकel_ddi_enable_pipe_घड़ी(encoder, crtc_state);

	अगर (!crtc_state->bigjoiner)
		पूर्णांकel_dsc_enable(encoder, crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_ddi_pre_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		tgl_ddi_pre_enable_dp(state, encoder, crtc_state, conn_state);
	अन्यथा
		hsw_ddi_pre_enable_dp(state, encoder, crtc_state, conn_state);

	/* MST will call a setting of MSA after an allocating of Virtual Channel
	 * from MST encoder pre_enable callback.
	 */
	अगर (!पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST)) अणु
		पूर्णांकel_ddi_set_dp_msa(crtc_state, conn_state);

		पूर्णांकel_dp_set_m_n(crtc_state, M1_N1);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_ddi_pre_enable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_encoder *encoder,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = &dig_port->hdmi;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	पूर्णांकel_dp_dual_mode_set_पंचांगds_output(पूर्णांकel_hdmi, true);
	पूर्णांकel_ddi_enable_घड़ी(encoder, crtc_state);

	drm_WARN_ON(&dev_priv->drm, dig_port->ddi_io_wakeref);
	dig_port->ddi_io_wakeref = पूर्णांकel_display_घातer_get(dev_priv,
							   dig_port->ddi_io_घातer_करोमुख्य);

	icl_program_mg_dp_mode(dig_port, crtc_state);

	पूर्णांकel_ddi_enable_pipe_घड़ी(encoder, crtc_state);

	dig_port->set_infoframes(encoder,
				 crtc_state->has_infoframe,
				 crtc_state, conn_state);
पूर्ण

अटल व्योम पूर्णांकel_ddi_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/*
	 * When called from DP MST code:
	 * - conn_state will be शून्य
	 * - encoder will be the मुख्य encoder (ie. mst->primary)
	 * - the मुख्य connector associated with this port
	 *   won't be active or linked to a crtc
	 * - crtc_state will be the state of the first stream to
	 *   be activated on this port, and it may not be the same
	 *   stream that will be deactivated last, but each stream
	 *   should have a state that is identical when it comes to
	 *   the DP link parameteres
	 */

	drm_WARN_ON(&dev_priv->drm, crtc_state->has_pch_encoder);

	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, true);

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) अणु
		पूर्णांकel_ddi_pre_enable_hdmi(state, encoder, crtc_state,
					  conn_state);
	पूर्ण अन्यथा अणु
		काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);

		पूर्णांकel_ddi_pre_enable_dp(state, encoder, crtc_state,
					conn_state);

		/* FIXME precompute everything properly */
		/* FIXME how करो we turn infoframes off again? */
		अगर (dig_port->lspcon.active && dig_port->dp.has_hdmi_sink)
			dig_port->set_infoframes(encoder,
						 crtc_state->has_infoframe,
						 crtc_state, conn_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_disable_ddi_buf(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	bool रुको = false;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port));
	अगर (val & DDI_BUF_CTL_ENABLE) अणु
		val &= ~DDI_BUF_CTL_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(port), val);
		रुको = true;
	पूर्ण

	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state)) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));
		val &= ~(DP_TP_CTL_ENABLE | DP_TP_CTL_LINK_TRAIN_MASK);
		val |= DP_TP_CTL_LINK_TRAIN_PAT1;
		पूर्णांकel_de_ग_लिखो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state), val);
	पूर्ण

	/* Disable FEC in DP Sink */
	पूर्णांकel_ddi_disable_fec_state(encoder, crtc_state);

	अगर (रुको)
		पूर्णांकel_रुको_ddi_buf_idle(dev_priv, port);
पूर्ण

अटल व्योम पूर्णांकel_ddi_post_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_encoder *encoder,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				      स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	bool is_mst = पूर्णांकel_crtc_has_type(old_crtc_state,
					  INTEL_OUTPUT_DP_MST);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);

	अगर (!is_mst)
		पूर्णांकel_dp_set_infoframes(encoder, false,
					old_crtc_state, old_conn_state);

	/*
	 * Power करोwn sink beक्रमe disabling the port, otherwise we end
	 * up getting पूर्णांकerrupts from the sink on detecting link loss.
	 */
	पूर्णांकel_dp_set_घातer(पूर्णांकel_dp, DP_SET_POWER_D3);

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		अगर (is_mst) अणु
			क्रमागत transcoder cpu_transcoder = old_crtc_state->cpu_transcoder;
			u32 val;

			val = पूर्णांकel_de_पढ़ो(dev_priv,
					    TRANS_DDI_FUNC_CTL(cpu_transcoder));
			val &= ~(TGL_TRANS_DDI_PORT_MASK |
				 TRANS_DDI_MODE_SELECT_MASK);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       TRANS_DDI_FUNC_CTL(cpu_transcoder),
				       val);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!is_mst)
			पूर्णांकel_ddi_disable_pipe_घड़ी(old_crtc_state);
	पूर्ण

	पूर्णांकel_disable_ddi_buf(encoder, old_crtc_state);

	/*
	 * From TGL spec: "If single stream or multi-stream master transcoder:
	 * Configure Transcoder Clock select to direct no घड़ी to the
	 * transcoder"
	 */
	अगर (DISPLAY_VER(dev_priv) >= 12)
		पूर्णांकel_ddi_disable_pipe_घड़ी(old_crtc_state);

	पूर्णांकel_pps_vdd_on(पूर्णांकel_dp);
	पूर्णांकel_pps_off(पूर्णांकel_dp);

	अगर (!पूर्णांकel_phy_is_tc(dev_priv, phy) ||
	    dig_port->tc_mode != TC_PORT_TBT_ALT)
		पूर्णांकel_display_घातer_put(dev_priv,
					dig_port->ddi_io_घातer_करोमुख्य,
					fetch_and_zero(&dig_port->ddi_io_wakeref));

	पूर्णांकel_ddi_disable_घड़ी(encoder);
पूर्ण

अटल व्योम पूर्णांकel_ddi_post_disable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
					काष्ठा पूर्णांकel_encoder *encoder,
					स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
					स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = &dig_port->hdmi;

	dig_port->set_infoframes(encoder, false,
				 old_crtc_state, old_conn_state);

	पूर्णांकel_ddi_disable_pipe_घड़ी(old_crtc_state);

	पूर्णांकel_disable_ddi_buf(encoder, old_crtc_state);

	पूर्णांकel_display_घातer_put(dev_priv,
				dig_port->ddi_io_घातer_करोमुख्य,
				fetch_and_zero(&dig_port->ddi_io_wakeref));

	पूर्णांकel_ddi_disable_घड़ी(encoder);

	पूर्णांकel_dp_dual_mode_set_पंचांगds_output(पूर्णांकel_hdmi, false);
पूर्ण

अटल व्योम पूर्णांकel_ddi_post_disable(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				   स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);
	bool is_tc_port = पूर्णांकel_phy_is_tc(dev_priv, phy);

	अगर (!पूर्णांकel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_DP_MST)) अणु
		पूर्णांकel_crtc_vblank_off(old_crtc_state);

		पूर्णांकel_disable_pipe(old_crtc_state);

		पूर्णांकel_vrr_disable(old_crtc_state);

		पूर्णांकel_ddi_disable_transcoder_func(old_crtc_state);

		पूर्णांकel_dsc_disable(old_crtc_state);

		अगर (DISPLAY_VER(dev_priv) >= 9)
			skl_scaler_disable(old_crtc_state);
		अन्यथा
			ilk_pfit_disable(old_crtc_state);
	पूर्ण

	अगर (old_crtc_state->bigjoiner_linked_crtc) अणु
		काष्ठा पूर्णांकel_atomic_state *state =
			to_पूर्णांकel_atomic_state(old_crtc_state->uapi.state);
		काष्ठा पूर्णांकel_crtc *slave =
			old_crtc_state->bigjoiner_linked_crtc;
		स्थिर काष्ठा पूर्णांकel_crtc_state *old_slave_crtc_state =
			पूर्णांकel_atomic_get_old_crtc_state(state, slave);

		पूर्णांकel_crtc_vblank_off(old_slave_crtc_state);

		पूर्णांकel_dsc_disable(old_slave_crtc_state);
		skl_scaler_disable(old_slave_crtc_state);
	पूर्ण

	/*
	 * When called from DP MST code:
	 * - old_conn_state will be शून्य
	 * - encoder will be the मुख्य encoder (ie. mst->primary)
	 * - the मुख्य connector associated with this port
	 *   won't be active or linked to a crtc
	 * - old_crtc_state will be the state of the last stream to
	 *   be deactivated on this port, and it may not be the same
	 *   stream that was activated last, but each stream
	 *   should have a state that is identical when it comes to
	 *   the DP link parameteres
	 */

	अगर (पूर्णांकel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_HDMI))
		पूर्णांकel_ddi_post_disable_hdmi(state, encoder, old_crtc_state,
					    old_conn_state);
	अन्यथा
		पूर्णांकel_ddi_post_disable_dp(state, encoder, old_crtc_state,
					  old_conn_state);

	अगर (पूर्णांकel_crtc_has_dp_encoder(old_crtc_state) || is_tc_port)
		पूर्णांकel_display_घातer_put(dev_priv,
					पूर्णांकel_ddi_मुख्य_link_aux_करोमुख्य(dig_port),
					fetch_and_zero(&dig_port->aux_wakeref));

	अगर (is_tc_port)
		पूर्णांकel_tc_port_put_link(dig_port);
पूर्ण

व्योम पूर्णांकel_ddi_fdi_post_disable(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 val;

	/*
	 * Bspec lists this as both step 13 (beक्रमe DDI_BUF_CTL disable)
	 * and step 18 (after clearing PORT_CLK_SEL). Based on a BUN,
	 * step 13 is the correct place क्रम it. Step 18 is where it was
	 * originally beक्रमe the BUN.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_A));
	val &= ~FDI_RX_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CTL(PIPE_A), val);

	पूर्णांकel_disable_ddi_buf(encoder, old_crtc_state);
	पूर्णांकel_ddi_disable_घड़ी(encoder);

	val = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_MISC(PIPE_A));
	val &= ~(FDI_RX_PWRDN_LANE1_MASK | FDI_RX_PWRDN_LANE0_MASK);
	val |= FDI_RX_PWRDN_LANE1_VAL(2) | FDI_RX_PWRDN_LANE0_VAL(2);
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_MISC(PIPE_A), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_A));
	val &= ~FDI_PCDCLK;
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CTL(PIPE_A), val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_A));
	val &= ~FDI_RX_PLL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_CTL(PIPE_A), val);
पूर्ण

अटल व्योम trans_port_sync_stop_link_train(काष्ठा पूर्णांकel_atomic_state *state,
					    काष्ठा पूर्णांकel_encoder *encoder,
					    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	अगर (!crtc_state->sync_mode_slaves_mask)
		वापस;

	क्रम_each_new_connector_in_state(&state->base, conn, conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *slave_encoder =
			to_पूर्णांकel_encoder(conn_state->best_encoder);
		काष्ठा पूर्णांकel_crtc *slave_crtc = to_पूर्णांकel_crtc(conn_state->crtc);
		स्थिर काष्ठा पूर्णांकel_crtc_state *slave_crtc_state;

		अगर (!slave_crtc)
			जारी;

		slave_crtc_state =
			पूर्णांकel_atomic_get_new_crtc_state(state, slave_crtc);

		अगर (slave_crtc_state->master_transcoder !=
		    crtc_state->cpu_transcoder)
			जारी;

		पूर्णांकel_dp_stop_link_train(enc_to_पूर्णांकel_dp(slave_encoder),
					 slave_crtc_state);
	पूर्ण

	usleep_range(200, 400);

	पूर्णांकel_dp_stop_link_train(enc_to_पूर्णांकel_dp(encoder),
				 crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_enable_ddi_dp(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	क्रमागत port port = encoder->port;

	अगर (port == PORT_A && DISPLAY_VER(dev_priv) < 9)
		पूर्णांकel_dp_stop_link_train(पूर्णांकel_dp, crtc_state);

	पूर्णांकel_edp_backlight_on(crtc_state, conn_state);
	पूर्णांकel_psr_enable(पूर्णांकel_dp, crtc_state, conn_state);

	अगर (!dig_port->lspcon.active || dig_port->dp.has_hdmi_sink)
		पूर्णांकel_dp_set_infoframes(encoder, true, crtc_state, conn_state);

	पूर्णांकel_edp_drrs_enable(पूर्णांकel_dp, crtc_state);

	अगर (crtc_state->has_audio)
		पूर्णांकel_audio_codec_enable(encoder, crtc_state, conn_state);

	trans_port_sync_stop_link_train(state, encoder, crtc_state);
पूर्ण

अटल i915_reg_t
gen9_chicken_trans_reg_by_port(काष्ठा drm_i915_निजी *dev_priv,
			       क्रमागत port port)
अणु
	अटल स्थिर क्रमागत transcoder trans[] = अणु
		[PORT_A] = TRANSCODER_EDP,
		[PORT_B] = TRANSCODER_A,
		[PORT_C] = TRANSCODER_B,
		[PORT_D] = TRANSCODER_C,
		[PORT_E] = TRANSCODER_A,
	पूर्ण;

	drm_WARN_ON(&dev_priv->drm, DISPLAY_VER(dev_priv) < 9);

	अगर (drm_WARN_ON(&dev_priv->drm, port < PORT_A || port > PORT_E))
		port = PORT_A;

	वापस CHICKEN_TRANS(trans[port]);
पूर्ण

अटल व्योम पूर्णांकel_enable_ddi_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_connector *connector = conn_state->connector;
	पूर्णांक level = पूर्णांकel_ddi_hdmi_level(encoder, crtc_state);
	क्रमागत port port = encoder->port;

	अगर (!पूर्णांकel_hdmi_handle_sink_scrambling(encoder, connector,
					       crtc_state->hdmi_high_पंचांगds_घड़ी_ratio,
					       crtc_state->hdmi_scrambling))
		drm_dbg_kms(&dev_priv->drm,
			    "[CONNECTOR:%d:%s] Failed to configure sink scrambling/TMDS bit clock ratio\n",
			    connector->base.id, connector->name);

	अगर (DISPLAY_VER(dev_priv) >= 12)
		tgl_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11))
		icl_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा अगर (IS_CANNONLAKE(dev_priv))
		cnl_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		bxt_ddi_vswing_sequence(encoder, crtc_state, level);
	अन्यथा
		पूर्णांकel_prepare_hdmi_ddi_buffers(encoder, level);

	अगर (IS_GEN9_BC(dev_priv))
		skl_ddi_set_iboost(encoder, crtc_state, level);

	/* Display WA #1143: skl,kbl,cfl */
	अगर (IS_GEN9_BC(dev_priv)) अणु
		/*
		 * For some reason these chicken bits have been
		 * stuffed पूर्णांकo a transcoder रेजिस्टर, event though
		 * the bits affect a specअगरic DDI port rather than
		 * a specअगरic transcoder.
		 */
		i915_reg_t reg = gen9_chicken_trans_reg_by_port(dev_priv, port);
		u32 val;

		val = पूर्णांकel_de_पढ़ो(dev_priv, reg);

		अगर (port == PORT_E)
			val |= DDIE_TRAINING_OVERRIDE_ENABLE |
				DDIE_TRAINING_OVERRIDE_VALUE;
		अन्यथा
			val |= DDI_TRAINING_OVERRIDE_ENABLE |
				DDI_TRAINING_OVERRIDE_VALUE;

		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

		udelay(1);

		अगर (port == PORT_E)
			val &= ~(DDIE_TRAINING_OVERRIDE_ENABLE |
				 DDIE_TRAINING_OVERRIDE_VALUE);
		अन्यथा
			val &= ~(DDI_TRAINING_OVERRIDE_ENABLE |
				 DDI_TRAINING_OVERRIDE_VALUE);

		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण

	पूर्णांकel_ddi_घातer_up_lanes(encoder, crtc_state);

	/* In HDMI/DVI mode, the port width, and swing/emphasis values
	 * are ignored so nothing special needs to be करोne besides
	 * enabling the port.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(port),
		       dig_port->saved_port_bits | DDI_BUF_CTL_ENABLE);

	अगर (crtc_state->has_audio)
		पूर्णांकel_audio_codec_enable(encoder, crtc_state, conn_state);
पूर्ण

अटल व्योम पूर्णांकel_enable_ddi(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	drm_WARN_ON(state->base.dev, crtc_state->has_pch_encoder);

	अगर (!crtc_state->bigjoiner_slave)
		पूर्णांकel_ddi_enable_transcoder_func(encoder, crtc_state);

	पूर्णांकel_vrr_enable(encoder, crtc_state);

	पूर्णांकel_enable_pipe(crtc_state);

	पूर्णांकel_crtc_vblank_on(crtc_state);

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		पूर्णांकel_enable_ddi_hdmi(state, encoder, crtc_state, conn_state);
	अन्यथा
		पूर्णांकel_enable_ddi_dp(state, encoder, crtc_state, conn_state);

	/* Enable hdcp अगर it's desired */
	अगर (conn_state->content_protection ==
	    DRM_MODE_CONTENT_PROTECTION_DESIRED)
		पूर्णांकel_hdcp_enable(to_पूर्णांकel_connector(conn_state->connector),
				  crtc_state,
				  (u8)conn_state->hdcp_content_type);
पूर्ण

अटल व्योम पूर्णांकel_disable_ddi_dp(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				 स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

	पूर्णांकel_dp->link_trained = false;

	अगर (old_crtc_state->has_audio)
		पूर्णांकel_audio_codec_disable(encoder,
					  old_crtc_state, old_conn_state);

	पूर्णांकel_edp_drrs_disable(पूर्णांकel_dp, old_crtc_state);
	पूर्णांकel_psr_disable(पूर्णांकel_dp, old_crtc_state);
	पूर्णांकel_edp_backlight_off(old_conn_state);
	/* Disable the decompression in DP Sink */
	पूर्णांकel_dp_sink_set_decompression_state(पूर्णांकel_dp, old_crtc_state,
					      false);
	/* Disable Ignore_MSA bit in DP Sink */
	पूर्णांकel_dp_sink_set_msa_timing_par_ignore_state(पूर्णांकel_dp, old_crtc_state,
						      false);
पूर्ण

अटल व्योम पूर्णांकel_disable_ddi_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				   स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा drm_connector *connector = old_conn_state->connector;

	अगर (old_crtc_state->has_audio)
		पूर्णांकel_audio_codec_disable(encoder,
					  old_crtc_state, old_conn_state);

	अगर (!पूर्णांकel_hdmi_handle_sink_scrambling(encoder, connector,
					       false, false))
		drm_dbg_kms(&i915->drm,
			    "[CONNECTOR:%d:%s] Failed to reset sink scrambling/TMDS bit clock ratio\n",
			    connector->base.id, connector->name);
पूर्ण

अटल व्योम पूर्णांकel_disable_ddi(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			      स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_hdcp_disable(to_पूर्णांकel_connector(old_conn_state->connector));

	अगर (पूर्णांकel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_HDMI))
		पूर्णांकel_disable_ddi_hdmi(state, encoder, old_crtc_state,
				       old_conn_state);
	अन्यथा
		पूर्णांकel_disable_ddi_dp(state, encoder, old_crtc_state,
				     old_conn_state);
पूर्ण

अटल व्योम पूर्णांकel_ddi_update_pipe_dp(काष्ठा पूर्णांकel_atomic_state *state,
				     काष्ठा पूर्णांकel_encoder *encoder,
				     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

	पूर्णांकel_ddi_set_dp_msa(crtc_state, conn_state);

	पूर्णांकel_psr_update(पूर्णांकel_dp, crtc_state, conn_state);
	पूर्णांकel_dp_set_infoframes(encoder, true, crtc_state, conn_state);
	पूर्णांकel_edp_drrs_update(पूर्णांकel_dp, crtc_state);

	पूर्णांकel_panel_update_backlight(state, encoder, crtc_state, conn_state);
पूर्ण

व्योम पूर्णांकel_ddi_update_pipe(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा drm_connector_state *conn_state)
अणु

	अगर (!पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI) &&
	    !पूर्णांकel_encoder_is_mst(encoder))
		पूर्णांकel_ddi_update_pipe_dp(state, encoder, crtc_state,
					 conn_state);

	पूर्णांकel_hdcp_update_pipe(state, encoder, crtc_state, conn_state);
पूर्ण

अटल व्योम
पूर्णांकel_ddi_update_prepare(काष्ठा पूर्णांकel_atomic_state *state,
			 काष्ठा पूर्णांकel_encoder *encoder,
			 काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		crtc ? पूर्णांकel_atomic_get_new_crtc_state(state, crtc) : शून्य;
	पूर्णांक required_lanes = crtc_state ? crtc_state->lane_count : 1;

	drm_WARN_ON(state->base.dev, crtc && crtc->active);

	पूर्णांकel_tc_port_get_link(enc_to_dig_port(encoder),
		               required_lanes);
	अगर (crtc_state && crtc_state->hw.active)
		पूर्णांकel_update_active_dpll(state, crtc, encoder);
पूर्ण

अटल व्योम
पूर्णांकel_ddi_update_complete(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_encoder *encoder,
			  काष्ठा पूर्णांकel_crtc *crtc)
अणु
	पूर्णांकel_tc_port_put_link(enc_to_dig_port(encoder));
पूर्ण

अटल व्योम
पूर्णांकel_ddi_pre_pll_enable(काष्ठा पूर्णांकel_atomic_state *state,
			 काष्ठा पूर्णांकel_encoder *encoder,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);
	bool is_tc_port = पूर्णांकel_phy_is_tc(dev_priv, phy);

	अगर (is_tc_port)
		पूर्णांकel_tc_port_get_link(dig_port, crtc_state->lane_count);

	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state) || is_tc_port) अणु
		drm_WARN_ON(&dev_priv->drm, dig_port->aux_wakeref);
		dig_port->aux_wakeref =
			पूर्णांकel_display_घातer_get(dev_priv,
						पूर्णांकel_ddi_मुख्य_link_aux_करोमुख्य(dig_port));
	पूर्ण

	अगर (is_tc_port && dig_port->tc_mode != TC_PORT_TBT_ALT)
		/*
		 * Program the lane count क्रम अटल/dynamic connections on
		 * Type-C ports.  Skip this step क्रम TBT.
		 */
		पूर्णांकel_tc_port_set_fia_lane_count(dig_port, crtc_state->lane_count);
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		bxt_ddi_phy_set_lane_optim_mask(encoder,
						crtc_state->lane_lat_optim_mask);
पूर्ण

अटल व्योम पूर्णांकel_ddi_prepare_link_retrain(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	u32 dp_tp_ctl, ddi_buf_ctl;
	bool रुको = false;

	dp_tp_ctl = पूर्णांकel_de_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));

	अगर (dp_tp_ctl & DP_TP_CTL_ENABLE) अणु
		ddi_buf_ctl = पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port));
		अगर (ddi_buf_ctl & DDI_BUF_CTL_ENABLE) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(port),
				       ddi_buf_ctl & ~DDI_BUF_CTL_ENABLE);
			रुको = true;
		पूर्ण

		dp_tp_ctl &= ~(DP_TP_CTL_ENABLE | DP_TP_CTL_LINK_TRAIN_MASK);
		dp_tp_ctl |= DP_TP_CTL_LINK_TRAIN_PAT1;
		पूर्णांकel_de_ग_लिखो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state), dp_tp_ctl);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));

		अगर (रुको)
			पूर्णांकel_रुको_ddi_buf_idle(dev_priv, port);
	पूर्ण

	dp_tp_ctl = DP_TP_CTL_ENABLE | DP_TP_CTL_LINK_TRAIN_PAT1;
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST)) अणु
		dp_tp_ctl |= DP_TP_CTL_MODE_MST;
	पूर्ण अन्यथा अणु
		dp_tp_ctl |= DP_TP_CTL_MODE_SST;
		अगर (drm_dp_enhanced_frame_cap(पूर्णांकel_dp->dpcd))
			dp_tp_ctl |= DP_TP_CTL_ENHANCED_FRAME_ENABLE;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state), dp_tp_ctl);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));

	पूर्णांकel_dp->DP |= DDI_BUF_CTL_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(port), पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DDI_BUF_CTL(port));

	पूर्णांकel_रुको_ddi_buf_active(dev_priv, port);
पूर्ण

अटल व्योम पूर्णांकel_ddi_set_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     u8 dp_train_pat)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 temp;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));

	temp &= ~DP_TP_CTL_LINK_TRAIN_MASK;
	चयन (पूर्णांकel_dp_training_pattern_symbol(dp_train_pat)) अणु
	हाल DP_TRAINING_PATTERN_DISABLE:
		temp |= DP_TP_CTL_LINK_TRAIN_NORMAL;
		अवरोध;
	हाल DP_TRAINING_PATTERN_1:
		temp |= DP_TP_CTL_LINK_TRAIN_PAT1;
		अवरोध;
	हाल DP_TRAINING_PATTERN_2:
		temp |= DP_TP_CTL_LINK_TRAIN_PAT2;
		अवरोध;
	हाल DP_TRAINING_PATTERN_3:
		temp |= DP_TP_CTL_LINK_TRAIN_PAT3;
		अवरोध;
	हाल DP_TRAINING_PATTERN_4:
		temp |= DP_TP_CTL_LINK_TRAIN_PAT4;
		अवरोध;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state), temp);
पूर्ण

अटल व्योम पूर्णांकel_ddi_set_idle_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
					  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state));
	val &= ~DP_TP_CTL_LINK_TRAIN_MASK;
	val |= DP_TP_CTL_LINK_TRAIN_IDLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, dp_tp_ctl_reg(encoder, crtc_state), val);

	/*
	 * Until TGL on PORT_A we can have only eDP in SST mode. There the only
	 * reason we need to set idle transmission mode is to work around a HW
	 * issue where we enable the pipe जबतक not in idle link-training mode.
	 * In this हाल there is requirement to रुको क्रम a minimum number of
	 * idle patterns to be sent.
	 */
	अगर (port == PORT_A && DISPLAY_VER(dev_priv) < 12)
		वापस;

	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv,
				  dp_tp_status_reg(encoder, crtc_state),
				  DP_TP_STATUS_IDLE_DONE, 1))
		drm_err(&dev_priv->drm,
			"Timed out waiting for DP idle patterns\n");
पूर्ण

अटल bool पूर्णांकel_ddi_is_audio_enabled(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत transcoder cpu_transcoder)
अणु
	अगर (cpu_transcoder == TRANSCODER_EDP)
		वापस false;

	अगर (!पूर्णांकel_display_घातer_is_enabled(dev_priv, POWER_DOMAIN_AUDIO))
		वापस false;

	वापस पूर्णांकel_de_पढ़ो(dev_priv, HSW_AUD_PIN_ELD_CP_VLD) &
		AUDIO_OUTPUT_ENABLE(cpu_transcoder);
पूर्ण

व्योम पूर्णांकel_ddi_compute_min_voltage_level(काष्ठा drm_i915_निजी *dev_priv,
					 काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 12 && crtc_state->port_घड़ी > 594000)
		crtc_state->min_voltage_level = 2;
	अन्यथा अगर (IS_JSL_EHL(dev_priv) && crtc_state->port_घड़ी > 594000)
		crtc_state->min_voltage_level = 3;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11 && crtc_state->port_घड़ी > 594000)
		crtc_state->min_voltage_level = 1;
	अन्यथा अगर (IS_CANNONLAKE(dev_priv) && crtc_state->port_घड़ी > 594000)
		crtc_state->min_voltage_level = 2;
पूर्ण

अटल क्रमागत transcoder bdw_transcoder_master_पढ़ोout(काष्ठा drm_i915_निजी *dev_priv,
						     क्रमागत transcoder cpu_transcoder)
अणु
	u32 master_select;

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		u32 ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL2(cpu_transcoder));

		अगर ((ctl2 & PORT_SYNC_MODE_ENABLE) == 0)
			वापस INVALID_TRANSCODER;

		master_select = REG_FIELD_GET(PORT_SYNC_MODE_MASTER_SELECT_MASK, ctl2);
	पूर्ण अन्यथा अणु
		u32 ctl = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder));

		अगर ((ctl & TRANS_DDI_PORT_SYNC_ENABLE) == 0)
			वापस INVALID_TRANSCODER;

		master_select = REG_FIELD_GET(TRANS_DDI_PORT_SYNC_MASTER_SELECT_MASK, ctl);
	पूर्ण

	अगर (master_select == 0)
		वापस TRANSCODER_EDP;
	अन्यथा
		वापस master_select - 1;
पूर्ण

अटल व्योम bdw_get_trans_port_sync_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	u32 transcoders = BIT(TRANSCODER_A) | BIT(TRANSCODER_B) |
		BIT(TRANSCODER_C) | BIT(TRANSCODER_D);
	क्रमागत transcoder cpu_transcoder;

	crtc_state->master_transcoder =
		bdw_transcoder_master_पढ़ोout(dev_priv, crtc_state->cpu_transcoder);

	क्रम_each_cpu_transcoder_masked(dev_priv, cpu_transcoder, transcoders) अणु
		क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
		पूर्णांकel_wakeref_t trans_wakeref;

		घातer_करोमुख्य = POWER_DOMAIN_TRANSCODER(cpu_transcoder);
		trans_wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
								   घातer_करोमुख्य);

		अगर (!trans_wakeref)
			जारी;

		अगर (bdw_transcoder_master_पढ़ोout(dev_priv, cpu_transcoder) ==
		    crtc_state->cpu_transcoder)
			crtc_state->sync_mode_slaves_mask |= BIT(cpu_transcoder);

		पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, trans_wakeref);
	पूर्ण

	drm_WARN_ON(&dev_priv->drm,
		    crtc_state->master_transcoder != INVALID_TRANSCODER &&
		    crtc_state->sync_mode_slaves_mask);
पूर्ण

अटल व्योम पूर्णांकel_ddi_पढ़ो_func_ctl(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	क्रमागत transcoder cpu_transcoder = pipe_config->cpu_transcoder;
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	u32 temp, flags = 0;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(cpu_transcoder));
	अगर (temp & TRANS_DDI_PHSYNC)
		flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_NHSYNC;
	अगर (temp & TRANS_DDI_PVSYNC)
		flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_NVSYNC;

	pipe_config->hw.adjusted_mode.flags |= flags;

	चयन (temp & TRANS_DDI_BPC_MASK) अणु
	हाल TRANS_DDI_BPC_6:
		pipe_config->pipe_bpp = 18;
		अवरोध;
	हाल TRANS_DDI_BPC_8:
		pipe_config->pipe_bpp = 24;
		अवरोध;
	हाल TRANS_DDI_BPC_10:
		pipe_config->pipe_bpp = 30;
		अवरोध;
	हाल TRANS_DDI_BPC_12:
		pipe_config->pipe_bpp = 36;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (temp & TRANS_DDI_MODE_SELECT_MASK) अणु
	हाल TRANS_DDI_MODE_SELECT_HDMI:
		pipe_config->has_hdmi_sink = true;

		pipe_config->infoframes.enable |=
			पूर्णांकel_hdmi_infoframes_enabled(encoder, pipe_config);

		अगर (pipe_config->infoframes.enable)
			pipe_config->has_infoframe = true;

		अगर (temp & TRANS_DDI_HDMI_SCRAMBLING)
			pipe_config->hdmi_scrambling = true;
		अगर (temp & TRANS_DDI_HIGH_TMDS_CHAR_RATE)
			pipe_config->hdmi_high_पंचांगds_घड़ी_ratio = true;
		fallthrough;
	हाल TRANS_DDI_MODE_SELECT_DVI:
		pipe_config->output_types |= BIT(INTEL_OUTPUT_HDMI);
		pipe_config->lane_count = 4;
		अवरोध;
	हाल TRANS_DDI_MODE_SELECT_FDI:
		pipe_config->output_types |= BIT(INTEL_OUTPUT_ANALOG);
		अवरोध;
	हाल TRANS_DDI_MODE_SELECT_DP_SST:
		अगर (encoder->type == INTEL_OUTPUT_EDP)
			pipe_config->output_types |= BIT(INTEL_OUTPUT_EDP);
		अन्यथा
			pipe_config->output_types |= BIT(INTEL_OUTPUT_DP);
		pipe_config->lane_count =
			((temp & DDI_PORT_WIDTH_MASK) >> DDI_PORT_WIDTH_SHIFT) + 1;
		पूर्णांकel_dp_get_m_n(पूर्णांकel_crtc, pipe_config);

		अगर (DISPLAY_VER(dev_priv) >= 11) अणु
			i915_reg_t dp_tp_ctl = dp_tp_ctl_reg(encoder, pipe_config);

			pipe_config->fec_enable =
				पूर्णांकel_de_पढ़ो(dev_priv, dp_tp_ctl) & DP_TP_CTL_FEC_ENABLE;

			drm_dbg_kms(&dev_priv->drm,
				    "[ENCODER:%d:%s] Fec status: %u\n",
				    encoder->base.base.id, encoder->base.name,
				    pipe_config->fec_enable);
		पूर्ण

		अगर (dig_port->lspcon.active && dig_port->dp.has_hdmi_sink)
			pipe_config->infoframes.enable |=
				पूर्णांकel_lspcon_infoframes_enabled(encoder, pipe_config);
		अन्यथा
			pipe_config->infoframes.enable |=
				पूर्णांकel_hdmi_infoframes_enabled(encoder, pipe_config);
		अवरोध;
	हाल TRANS_DDI_MODE_SELECT_DP_MST:
		pipe_config->output_types |= BIT(INTEL_OUTPUT_DP_MST);
		pipe_config->lane_count =
			((temp & DDI_PORT_WIDTH_MASK) >> DDI_PORT_WIDTH_SHIFT) + 1;

		अगर (DISPLAY_VER(dev_priv) >= 12)
			pipe_config->mst_master_transcoder =
					REG_FIELD_GET(TRANS_DDI_MST_TRANSPORT_SELECT_MASK, temp);

		पूर्णांकel_dp_get_m_n(पूर्णांकel_crtc, pipe_config);

		pipe_config->infoframes.enable |=
			पूर्णांकel_hdmi_infoframes_enabled(encoder, pipe_config);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत transcoder cpu_transcoder = pipe_config->cpu_transcoder;

	/* XXX: DSI transcoder paranoia */
	अगर (drm_WARN_ON(&dev_priv->drm, transcoder_is_dsi(cpu_transcoder)))
		वापस;

	अगर (pipe_config->bigjoiner_slave) अणु
		/* पढ़ो out pipe settings from master */
		क्रमागत transcoder save = pipe_config->cpu_transcoder;

		/* Our own transcoder needs to be disabled when पढ़ोing it in पूर्णांकel_ddi_पढ़ो_func_ctl() */
		WARN_ON(pipe_config->output_types);
		pipe_config->cpu_transcoder = (क्रमागत transcoder)pipe_config->bigjoiner_linked_crtc->pipe;
		पूर्णांकel_ddi_पढ़ो_func_ctl(encoder, pipe_config);
		pipe_config->cpu_transcoder = save;
	पूर्ण अन्यथा अणु
		पूर्णांकel_ddi_पढ़ो_func_ctl(encoder, pipe_config);
	पूर्ण

	पूर्णांकel_ddi_mso_get_config(encoder, pipe_config);

	pipe_config->has_audio =
		पूर्णांकel_ddi_is_audio_enabled(dev_priv, cpu_transcoder);

	अगर (encoder->type == INTEL_OUTPUT_EDP && dev_priv->vbt.edp.bpp &&
	    pipe_config->pipe_bpp > dev_priv->vbt.edp.bpp) अणु
		/*
		 * This is a big fat ugly hack.
		 *
		 * Some machines in UEFI boot mode provide us a VBT that has 18
		 * bpp and 1.62 GHz link bandwidth क्रम eDP, which क्रम reasons
		 * unknown we fail to light up. Yet the same BIOS boots up with
		 * 24 bpp and 2.7 GHz link. Use the same bpp as the BIOS uses as
		 * max, not what it tells us to use.
		 *
		 * Note: This will still be broken अगर the eDP panel is not lit
		 * up by the BIOS, and thus we can't get the mode at module
		 * load.
		 */
		drm_dbg_kms(&dev_priv->drm,
			    "pipe has %d bpp for eDP panel, overriding BIOS-provided max %d bpp\n",
			    pipe_config->pipe_bpp, dev_priv->vbt.edp.bpp);
		dev_priv->vbt.edp.bpp = pipe_config->pipe_bpp;
	पूर्ण

	अगर (!pipe_config->bigjoiner_slave)
		ddi_करोtघड़ी_get(pipe_config);

	अगर (IS_GEN9_LP(dev_priv))
		pipe_config->lane_lat_optim_mask =
			bxt_ddi_phy_get_lane_lat_optim_mask(encoder);

	पूर्णांकel_ddi_compute_min_voltage_level(dev_priv, pipe_config);

	पूर्णांकel_hdmi_पढ़ो_gcp_infoframe(encoder, pipe_config);

	पूर्णांकel_पढ़ो_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_AVI,
			     &pipe_config->infoframes.avi);
	पूर्णांकel_पढ़ो_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_SPD,
			     &pipe_config->infoframes.spd);
	पूर्णांकel_पढ़ो_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_VENDOR,
			     &pipe_config->infoframes.hdmi);
	पूर्णांकel_पढ़ो_infoframe(encoder, pipe_config,
			     HDMI_INFOFRAME_TYPE_DRM,
			     &pipe_config->infoframes.drm);

	अगर (DISPLAY_VER(dev_priv) >= 8)
		bdw_get_trans_port_sync_config(pipe_config);

	पूर्णांकel_पढ़ो_dp_sdp(encoder, pipe_config, HDMI_PACKET_TYPE_GAMUT_METADATA);
	पूर्णांकel_पढ़ो_dp_sdp(encoder, pipe_config, DP_SDP_VSC);
पूर्ण

व्योम पूर्णांकel_ddi_get_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
			 काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत icl_port_dpll_id port_dpll_id = ICL_PORT_DPLL_DEFAULT;
	काष्ठा icl_port_dpll *port_dpll = &crtc_state->icl_port_dplls[port_dpll_id];
	bool pll_active;

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	port_dpll->pll = pll;
	pll_active = पूर्णांकel_dpll_get_hw_state(i915, pll, &port_dpll->hw_state);
	drm_WARN_ON(&i915->drm, !pll_active);

	icl_set_active_port_dpll(crtc_state, port_dpll_id);

	crtc_state->port_घड़ी = पूर्णांकel_dpll_get_freq(i915, crtc_state->shared_dpll,
						     &crtc_state->dpll_hw_state);
पूर्ण

अटल व्योम adls_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_ddi_get_घड़ी(encoder, crtc_state, adls_ddi_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

अटल व्योम rkl_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_ddi_get_घड़ी(encoder, crtc_state, rkl_ddi_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

अटल व्योम dg1_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_ddi_get_घड़ी(encoder, crtc_state, dg1_ddi_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

अटल व्योम icl_ddi_combo_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				     काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_ddi_get_घड़ी(encoder, crtc_state, icl_ddi_combo_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

अटल व्योम icl_ddi_tc_get_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 काष्ठा पूर्णांकel_shared_dpll *pll)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	क्रमागत icl_port_dpll_id port_dpll_id;
	काष्ठा icl_port_dpll *port_dpll;
	bool pll_active;

	अगर (drm_WARN_ON(&i915->drm, !pll))
		वापस;

	अगर (पूर्णांकel_get_shared_dpll_id(i915, pll) == DPLL_ID_ICL_TBTPLL)
		port_dpll_id = ICL_PORT_DPLL_DEFAULT;
	अन्यथा
		port_dpll_id = ICL_PORT_DPLL_MG_PHY;

	port_dpll = &crtc_state->icl_port_dplls[port_dpll_id];

	port_dpll->pll = pll;
	pll_active = पूर्णांकel_dpll_get_hw_state(i915, pll, &port_dpll->hw_state);
	drm_WARN_ON(&i915->drm, !pll_active);

	icl_set_active_port_dpll(crtc_state, port_dpll_id);

	अगर (पूर्णांकel_get_shared_dpll_id(i915, crtc_state->shared_dpll) == DPLL_ID_ICL_TBTPLL)
		crtc_state->port_घड़ी = icl_calc_tbt_pll_link(i915, encoder->port);
	अन्यथा
		crtc_state->port_घड़ी = पूर्णांकel_dpll_get_freq(i915, crtc_state->shared_dpll,
							     &crtc_state->dpll_hw_state);
पूर्ण

अटल व्योम icl_ddi_tc_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	icl_ddi_tc_get_घड़ी(encoder, crtc_state, icl_ddi_tc_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

अटल व्योम cnl_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_ddi_get_घड़ी(encoder, crtc_state, cnl_ddi_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

अटल व्योम bxt_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_ddi_get_घड़ी(encoder, crtc_state, bxt_ddi_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

अटल व्योम skl_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_ddi_get_घड़ी(encoder, crtc_state, skl_ddi_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

व्योम hsw_ddi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
			काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांकel_ddi_get_घड़ी(encoder, crtc_state, hsw_ddi_get_pll(encoder));
	पूर्णांकel_ddi_get_config(encoder, crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_ddi_sync_state(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state))
		पूर्णांकel_dp_sync_state(encoder, crtc_state);
पूर्ण

अटल bool पूर्णांकel_ddi_initial_fastset_check(काष्ठा पूर्णांकel_encoder *encoder,
					    काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state))
		वापस पूर्णांकel_dp_initial_fastset_check(encoder, crtc_state);

	वापस true;
पूर्ण

अटल क्रमागत पूर्णांकel_output_type
पूर्णांकel_ddi_compute_output_type(काष्ठा पूर्णांकel_encoder *encoder,
			      काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      काष्ठा drm_connector_state *conn_state)
अणु
	चयन (conn_state->connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_HDMIA:
		वापस INTEL_OUTPUT_HDMI;
	हाल DRM_MODE_CONNECTOR_eDP:
		वापस INTEL_OUTPUT_EDP;
	हाल DRM_MODE_CONNECTOR_DisplayPort:
		वापस INTEL_OUTPUT_DP;
	शेष:
		MISSING_CASE(conn_state->connector->connector_type);
		वापस INTEL_OUTPUT_UNUSED;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_ddi_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत port port = encoder->port;
	पूर्णांक ret;

	अगर (HAS_TRANSCODER(dev_priv, TRANSCODER_EDP) && port == PORT_A)
		pipe_config->cpu_transcoder = TRANSCODER_EDP;

	अगर (पूर्णांकel_crtc_has_type(pipe_config, INTEL_OUTPUT_HDMI)) अणु
		ret = पूर्णांकel_hdmi_compute_config(encoder, pipe_config, conn_state);
	पूर्ण अन्यथा अणु
		ret = पूर्णांकel_dp_compute_config(encoder, pipe_config, conn_state);
	पूर्ण

	अगर (ret)
		वापस ret;

	अगर (IS_HASWELL(dev_priv) && crtc->pipe == PIPE_A &&
	    pipe_config->cpu_transcoder == TRANSCODER_EDP)
		pipe_config->pch_pfit.क्रमce_thru =
			pipe_config->pch_pfit.enabled ||
			pipe_config->crc_enabled;

	अगर (IS_GEN9_LP(dev_priv))
		pipe_config->lane_lat_optim_mask =
			bxt_ddi_phy_calc_lane_lat_optim_mask(pipe_config->lane_count);

	पूर्णांकel_ddi_compute_min_voltage_level(dev_priv, pipe_config);

	वापस 0;
पूर्ण

अटल bool mode_equal(स्थिर काष्ठा drm_display_mode *mode1,
		       स्थिर काष्ठा drm_display_mode *mode2)
अणु
	वापस drm_mode_match(mode1, mode2,
			      DRM_MODE_MATCH_TIMINGS |
			      DRM_MODE_MATCH_FLAGS |
			      DRM_MODE_MATCH_3D_FLAGS) &&
		mode1->घड़ी == mode2->घड़ी; /* we want an exact match */
पूर्ण

अटल bool m_n_equal(स्थिर काष्ठा पूर्णांकel_link_m_n *m_n_1,
		      स्थिर काष्ठा पूर्णांकel_link_m_n *m_n_2)
अणु
	वापस m_n_1->tu == m_n_2->tu &&
		m_n_1->gmch_m == m_n_2->gmch_m &&
		m_n_1->gmch_n == m_n_2->gmch_n &&
		m_n_1->link_m == m_n_2->link_m &&
		m_n_1->link_n == m_n_2->link_n;
पूर्ण

अटल bool crtcs_port_sync_compatible(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state1,
				       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state2)
अणु
	वापस crtc_state1->hw.active && crtc_state2->hw.active &&
		crtc_state1->output_types == crtc_state2->output_types &&
		crtc_state1->output_क्रमmat == crtc_state2->output_क्रमmat &&
		crtc_state1->lane_count == crtc_state2->lane_count &&
		crtc_state1->port_घड़ी == crtc_state2->port_घड़ी &&
		mode_equal(&crtc_state1->hw.adjusted_mode,
			   &crtc_state2->hw.adjusted_mode) &&
		m_n_equal(&crtc_state1->dp_m_n, &crtc_state2->dp_m_n);
पूर्ण

अटल u8
पूर्णांकel_ddi_port_sync_transcoders(स्थिर काष्ठा पूर्णांकel_crtc_state *ref_crtc_state,
				पूर्णांक tile_group_id)
अणु
	काष्ठा drm_connector *connector;
	स्थिर काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(ref_crtc_state->uapi.crtc->dev);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(ref_crtc_state->uapi.state);
	u8 transcoders = 0;
	पूर्णांक i;

	/*
	 * We करोn't enable port sync on BDW due to missing w/as and
	 * due to not having adjusted the modeset sequence appropriately.
	 */
	अगर (DISPLAY_VER(dev_priv) < 9)
		वापस 0;

	अगर (!पूर्णांकel_crtc_has_type(ref_crtc_state, INTEL_OUTPUT_DP))
		वापस 0;

	क्रम_each_new_connector_in_state(&state->base, connector, conn_state, i) अणु
		काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(conn_state->crtc);
		स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state;

		अगर (!crtc)
			जारी;

		अगर (!connector->has_tile ||
		    connector->tile_group->id !=
		    tile_group_id)
			जारी;
		crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state,
							     crtc);
		अगर (!crtcs_port_sync_compatible(ref_crtc_state,
						crtc_state))
			जारी;
		transcoders |= BIT(crtc_state->cpu_transcoder);
	पूर्ण

	वापस transcoders;
पूर्ण

अटल पूर्णांक पूर्णांकel_ddi_compute_config_late(काष्ठा पूर्णांकel_encoder *encoder,
					 काष्ठा पूर्णांकel_crtc_state *crtc_state,
					 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा drm_connector *connector = conn_state->connector;
	u8 port_sync_transcoders = 0;

	drm_dbg_kms(&i915->drm, "[ENCODER:%d:%s] [CRTC:%d:%s]",
		    encoder->base.base.id, encoder->base.name,
		    crtc_state->uapi.crtc->base.id, crtc_state->uapi.crtc->name);

	अगर (connector->has_tile)
		port_sync_transcoders = पूर्णांकel_ddi_port_sync_transcoders(crtc_state,
									connector->tile_group->id);

	/*
	 * EDP Transcoders cannot be ensalved
	 * make them a master always when present
	 */
	अगर (port_sync_transcoders & BIT(TRANSCODER_EDP))
		crtc_state->master_transcoder = TRANSCODER_EDP;
	अन्यथा
		crtc_state->master_transcoder = ffs(port_sync_transcoders) - 1;

	अगर (crtc_state->master_transcoder == crtc_state->cpu_transcoder) अणु
		crtc_state->master_transcoder = INVALID_TRANSCODER;
		crtc_state->sync_mode_slaves_mask =
			port_sync_transcoders & ~BIT(crtc_state->cpu_transcoder);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_ddi_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(to_पूर्णांकel_encoder(encoder));

	पूर्णांकel_dp_encoder_flush_work(encoder);

	drm_encoder_cleanup(encoder);
	अगर (dig_port)
		kमुक्त(dig_port->hdcp_port_data.streams);
	kमुक्त(dig_port);
पूर्ण

अटल व्योम पूर्णांकel_ddi_encoder_reset(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(to_पूर्णांकel_encoder(encoder));

	पूर्णांकel_dp->reset_link_params = true;

	पूर्णांकel_pps_encoder_reset(पूर्णांकel_dp);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_ddi_funcs = अणु
	.reset = पूर्णांकel_ddi_encoder_reset,
	.destroy = पूर्णांकel_ddi_encoder_destroy,
पूर्ण;

अटल काष्ठा पूर्णांकel_connector *
पूर्णांकel_ddi_init_dp_connector(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_connector *connector;
	क्रमागत port port = dig_port->base.port;

	connector = पूर्णांकel_connector_alloc();
	अगर (!connector)
		वापस शून्य;

	dig_port->dp.output_reg = DDI_BUF_CTL(port);
	dig_port->dp.prepare_link_retrain = पूर्णांकel_ddi_prepare_link_retrain;
	dig_port->dp.set_link_train = पूर्णांकel_ddi_set_link_train;
	dig_port->dp.set_idle_link_train = पूर्णांकel_ddi_set_idle_link_train;

	अगर (DISPLAY_VER(dev_priv) >= 12)
		dig_port->dp.set_संकेत_levels = tgl_set_संकेत_levels;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11)
		dig_port->dp.set_संकेत_levels = icl_set_संकेत_levels;
	अन्यथा अगर (IS_CANNONLAKE(dev_priv))
		dig_port->dp.set_संकेत_levels = cnl_set_संकेत_levels;
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		dig_port->dp.set_संकेत_levels = bxt_set_संकेत_levels;
	अन्यथा
		dig_port->dp.set_संकेत_levels = hsw_set_संकेत_levels;

	dig_port->dp.voltage_max = पूर्णांकel_ddi_dp_voltage_max;
	dig_port->dp.preemph_max = पूर्णांकel_ddi_dp_preemph_max;

	अगर (!पूर्णांकel_dp_init_connector(dig_port, connector)) अणु
		kमुक्त(connector);
		वापस शून्य;
	पूर्ण

	वापस connector;
पूर्ण

अटल पूर्णांक modeset_pipe(काष्ठा drm_crtc *crtc,
			काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;

	state = drm_atomic_state_alloc(crtc->dev);
	अगर (!state)
		वापस -ENOMEM;

	state->acquire_ctx = ctx;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(crtc_state)) अणु
		ret = PTR_ERR(crtc_state);
		जाओ out;
	पूर्ण

	crtc_state->connectors_changed = true;

	ret = drm_atomic_commit(state);
out:
	drm_atomic_state_put(state);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_hdmi_reset_link(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_hdmi *hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	काष्ठा पूर्णांकel_connector *connector = hdmi->attached_connector;
	काष्ठा i2c_adapter *adapter =
		पूर्णांकel_gmbus_get_adapter(dev_priv, hdmi->ddc_bus);
	काष्ठा drm_connector_state *conn_state;
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	u8 config;
	पूर्णांक ret;

	अगर (!connector || connector->base.status != connector_status_connected)
		वापस 0;

	ret = drm_modeset_lock(&dev_priv->drm.mode_config.connection_mutex,
			       ctx);
	अगर (ret)
		वापस ret;

	conn_state = connector->base.state;

	crtc = to_पूर्णांकel_crtc(conn_state->crtc);
	अगर (!crtc)
		वापस 0;

	ret = drm_modeset_lock(&crtc->base.mutex, ctx);
	अगर (ret)
		वापस ret;

	crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);

	drm_WARN_ON(&dev_priv->drm,
		    !पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI));

	अगर (!crtc_state->hw.active)
		वापस 0;

	अगर (!crtc_state->hdmi_high_पंचांगds_घड़ी_ratio &&
	    !crtc_state->hdmi_scrambling)
		वापस 0;

	अगर (conn_state->commit &&
	    !try_रुको_क्रम_completion(&conn_state->commit->hw_करोne))
		वापस 0;

	ret = drm_scdc_पढ़ोb(adapter, SCDC_TMDS_CONFIG, &config);
	अगर (ret < 0) अणु
		drm_err(&dev_priv->drm, "Failed to read TMDS config: %d\n",
			ret);
		वापस 0;
	पूर्ण

	अगर (!!(config & SCDC_TMDS_BIT_CLOCK_RATIO_BY_40) ==
	    crtc_state->hdmi_high_पंचांगds_घड़ी_ratio &&
	    !!(config & SCDC_SCRAMBLING_ENABLE) ==
	    crtc_state->hdmi_scrambling)
		वापस 0;

	/*
	 * HDMI 2.0 says that one should not send scrambled data
	 * prior to configuring the sink scrambling, and that
	 * TMDS घड़ी/data transmission should be suspended when
	 * changing the TMDS घड़ी rate in the sink. So let's
	 * just करो a full modeset here, even though some sinks
	 * would be perfectly happy अगर were to just reconfigure
	 * the SCDC settings on the fly.
	 */
	वापस modeset_pipe(&crtc->base, ctx);
पूर्ण

अटल क्रमागत पूर्णांकel_hotplug_state
पूर्णांकel_ddi_hotplug(काष्ठा पूर्णांकel_encoder *encoder,
		  काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(i915, encoder->port);
	bool is_tc = पूर्णांकel_phy_is_tc(i915, phy);
	काष्ठा drm_modeset_acquire_ctx ctx;
	क्रमागत पूर्णांकel_hotplug_state state;
	पूर्णांक ret;

	अगर (पूर्णांकel_dp->compliance.test_active &&
	    पूर्णांकel_dp->compliance.test_type == DP_TEST_LINK_PHY_TEST_PATTERN) अणु
		पूर्णांकel_dp_phy_test(encoder);
		/* just करो the PHY test and nothing अन्यथा */
		वापस INTEL_HOTPLUG_UNCHANGED;
	पूर्ण

	state = पूर्णांकel_encoder_hotplug(encoder, connector);

	drm_modeset_acquire_init(&ctx, 0);

	क्रम (;;) अणु
		अगर (connector->base.connector_type == DRM_MODE_CONNECTOR_HDMIA)
			ret = पूर्णांकel_hdmi_reset_link(encoder, &ctx);
		अन्यथा
			ret = पूर्णांकel_dp_retrain_link(encoder, &ctx);

		अगर (ret == -EDEADLK) अणु
			drm_modeset_backoff(&ctx);
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
	drm_WARN(encoder->base.dev, ret,
		 "Acquiring modeset locks failed with %i\n", ret);

	/*
	 * Unघातered type-c करोngles can take some समय to boot and be
	 * responsible, so here giving some समय to those करोngles to घातer up
	 * and then retrying the probe.
	 *
	 * On many platक्रमms the HDMI live state संकेत is known to be
	 * unreliable, so we can't use it to detect अगर a sink is connected or
	 * not. Instead we detect अगर it's connected based on whether we can
	 * पढ़ो the EDID or not. That in turn has a problem during disconnect,
	 * since the HPD पूर्णांकerrupt may be उठाओd beक्रमe the DDC lines get
	 * disconnected (due to how the required length of DDC vs. HPD
	 * connector pins are specअगरied) and so we'll still be able to get a
	 * valid EDID. To solve this schedule another detection cycle अगर this
	 * समय around we didn't detect any change in the sink's connection
	 * status.
	 *
	 * Type-c connectors which get their HPD संकेत deनिश्चितed then
	 * reनिश्चितed, without unplugging/replugging the sink from the
	 * connector, पूर्णांकroduce a delay until the AUX channel communication
	 * becomes functional. Retry the detection क्रम 5 seconds on type-c
	 * connectors to account क्रम this delay.
	 */
	अगर (state == INTEL_HOTPLUG_UNCHANGED &&
	    connector->hotplug_retries < (is_tc ? 5 : 1) &&
	    !dig_port->dp.is_mst)
		state = INTEL_HOTPLUG_RETRY;

	वापस state;
पूर्ण

अटल bool lpt_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 bit = dev_priv->hotplug.pch_hpd[encoder->hpd_pin];

	वापस पूर्णांकel_de_पढ़ो(dev_priv, SDEISR) & bit;
पूर्ण

अटल bool hsw_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 bit = dev_priv->hotplug.hpd[encoder->hpd_pin];

	वापस पूर्णांकel_de_पढ़ो(dev_priv, DEISR) & bit;
पूर्ण

अटल bool bdw_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 bit = dev_priv->hotplug.hpd[encoder->hpd_pin];

	वापस पूर्णांकel_de_पढ़ो(dev_priv, GEN8_DE_PORT_ISR) & bit;
पूर्ण

अटल काष्ठा पूर्णांकel_connector *
पूर्णांकel_ddi_init_hdmi_connector(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा पूर्णांकel_connector *connector;
	क्रमागत port port = dig_port->base.port;

	connector = पूर्णांकel_connector_alloc();
	अगर (!connector)
		वापस शून्य;

	dig_port->hdmi.hdmi_reg = DDI_BUF_CTL(port);
	पूर्णांकel_hdmi_init_connector(dig_port, connector);

	वापस connector;
पूर्ण

अटल bool पूर्णांकel_ddi_a_क्रमce_4_lanes(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);

	अगर (dig_port->base.port != PORT_A)
		वापस false;

	अगर (dig_port->saved_port_bits & DDI_A_4_LANES)
		वापस false;

	/* Broxton/Geminilake: Bspec says that DDI_A_4_LANES is the only
	 *                     supported configuration
	 */
	अगर (IS_GEN9_LP(dev_priv))
		वापस true;

	/* Cannonlake: Most of SKUs करोn't support DDI_E, and the only
	 *             one who करोes also have a full A/E split called
	 *             DDI_F what makes DDI_E useless. However क्रम this
	 *             हाल let's trust VBT info.
	 */
	अगर (IS_CANNONLAKE(dev_priv) &&
	    !पूर्णांकel_bios_is_port_present(dev_priv, PORT_E))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक
पूर्णांकel_ddi_max_lanes(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	क्रमागत port port = dig_port->base.port;
	पूर्णांक max_lanes = 4;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		वापस max_lanes;

	अगर (port == PORT_A || port == PORT_E) अणु
		अगर (पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(PORT_A)) & DDI_A_4_LANES)
			max_lanes = port == PORT_A ? 4 : 0;
		अन्यथा
			/* Both A and E share 2 lanes */
			max_lanes = 2;
	पूर्ण

	/*
	 * Some BIOS might fail to set this bit on port A अगर eDP
	 * wasn't lit up at boot.  Force this bit set when needed
	 * so we use the proper lane count क्रम our calculations.
	 */
	अगर (पूर्णांकel_ddi_a_क्रमce_4_lanes(dig_port)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Forcing DDI_A_4_LANES for port A\n");
		dig_port->saved_port_bits |= DDI_A_4_LANES;
		max_lanes = 4;
	पूर्ण

	वापस max_lanes;
पूर्ण

अटल bool hti_uses_phy(काष्ठा drm_i915_निजी *i915, क्रमागत phy phy)
अणु
	वापस i915->hti_state & HDPORT_ENABLED &&
	       i915->hti_state & HDPORT_DDI_USED(phy);
पूर्ण

अटल क्रमागत hpd_pin dg1_hpd_pin(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत port port)
अणु
	अगर (port >= PORT_TC1)
		वापस HPD_PORT_C + port - PORT_TC1;
	अन्यथा
		वापस HPD_PORT_A + port - PORT_A;
पूर्ण

अटल क्रमागत hpd_pin tgl_hpd_pin(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत port port)
अणु
	अगर (port >= PORT_TC1)
		वापस HPD_PORT_TC1 + port - PORT_TC1;
	अन्यथा
		वापस HPD_PORT_A + port - PORT_A;
पूर्ण

अटल क्रमागत hpd_pin rkl_hpd_pin(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत port port)
अणु
	अगर (HAS_PCH_TGP(dev_priv))
		वापस tgl_hpd_pin(dev_priv, port);

	अगर (port >= PORT_TC1)
		वापस HPD_PORT_C + port - PORT_TC1;
	अन्यथा
		वापस HPD_PORT_A + port - PORT_A;
पूर्ण

अटल क्रमागत hpd_pin icl_hpd_pin(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत port port)
अणु
	अगर (port >= PORT_C)
		वापस HPD_PORT_TC1 + port - PORT_C;
	अन्यथा
		वापस HPD_PORT_A + port - PORT_A;
पूर्ण

अटल क्रमागत hpd_pin ehl_hpd_pin(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत port port)
अणु
	अगर (port == PORT_D)
		वापस HPD_PORT_A;

	अगर (HAS_PCH_MCC(dev_priv))
		वापस icl_hpd_pin(dev_priv, port);

	वापस HPD_PORT_A + port - PORT_A;
पूर्ण

अटल क्रमागत hpd_pin cnl_hpd_pin(काष्ठा drm_i915_निजी *dev_priv,
				क्रमागत port port)
अणु
	अगर (port == PORT_F)
		वापस HPD_PORT_E;

	वापस HPD_PORT_A + port - PORT_A;
पूर्ण

अटल क्रमागत hpd_pin skl_hpd_pin(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	अगर (HAS_PCH_TGP(dev_priv))
		वापस icl_hpd_pin(dev_priv, port);

	वापस HPD_PORT_A + port - PORT_A;
पूर्ण

अटल bool पूर्णांकel_ddi_is_tc(काष्ठा drm_i915_निजी *i915, क्रमागत port port)
अणु
	अगर (DISPLAY_VER(i915) >= 12)
		वापस port >= PORT_TC1;
	अन्यथा अगर (DISPLAY_VER(i915) >= 11)
		वापस port >= PORT_C;
	अन्यथा
		वापस false;
पूर्ण

#घोषणा port_tc_name(port) ((port) - PORT_TC1 + '1')
#घोषणा tc_port_name(tc_port) ((tc_port) - TC_PORT_1 + '1')

व्योम पूर्णांकel_ddi_init(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port;
	काष्ठा पूर्णांकel_encoder *encoder;
	स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata;
	bool init_hdmi, init_dp;
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, port);

	/*
	 * On platक्रमms with HTI (aka HDPORT), अगर it's enabled at boot it may
	 * have taken over some of the PHYs and made them unavailable to the
	 * driver.  In that हाल we should skip initializing the corresponding
	 * outमाला_दो.
	 */
	अगर (hti_uses_phy(dev_priv, phy)) अणु
		drm_dbg_kms(&dev_priv->drm, "PORT %c / PHY %c reserved by HTI\n",
			    port_name(port), phy_name(phy));
		वापस;
	पूर्ण

	devdata = पूर्णांकel_bios_encoder_data_lookup(dev_priv, port);
	अगर (!devdata) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "VBT says port %c is not present\n",
			    port_name(port));
		वापस;
	पूर्ण

	init_hdmi = पूर्णांकel_bios_encoder_supports_dvi(devdata) ||
		पूर्णांकel_bios_encoder_supports_hdmi(devdata);
	init_dp = पूर्णांकel_bios_encoder_supports_dp(devdata);

	अगर (पूर्णांकel_bios_is_lspcon_present(dev_priv, port)) अणु
		/*
		 * Lspcon device needs to be driven with DP connector
		 * with special detection sequence. So make sure DP
		 * is initialized beक्रमe lspcon.
		 */
		init_dp = true;
		init_hdmi = false;
		drm_dbg_kms(&dev_priv->drm, "VBT says port %c has lspcon\n",
			    port_name(port));
	पूर्ण

	अगर (!init_dp && !init_hdmi) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "VBT says port %c is not DVI/HDMI/DP compatible, respect it\n",
			    port_name(port));
		वापस;
	पूर्ण

	dig_port = kzalloc(माप(*dig_port), GFP_KERNEL);
	अगर (!dig_port)
		वापस;

	encoder = &dig_port->base;
	encoder->devdata = devdata;

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(dev_priv, port);

		drm_encoder_init(&dev_priv->drm, &encoder->base, &पूर्णांकel_ddi_funcs,
				 DRM_MODE_ENCODER_TMDS,
				 "DDI %s%c/PHY %s%c",
				 port >= PORT_TC1 ? "TC" : "",
				 port >= PORT_TC1 ? port_tc_name(port) : port_name(port),
				 tc_port != TC_PORT_NONE ? "TC" : "",
				 tc_port != TC_PORT_NONE ? tc_port_name(tc_port) : phy_name(phy));
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		क्रमागत tc_port tc_port = पूर्णांकel_port_to_tc(dev_priv, port);

		drm_encoder_init(&dev_priv->drm, &encoder->base, &पूर्णांकel_ddi_funcs,
				 DRM_MODE_ENCODER_TMDS,
				 "DDI %c%s/PHY %s%c",
				 port_name(port),
				 port >= PORT_C ? " (TC)" : "",
				 tc_port != TC_PORT_NONE ? "TC" : "",
				 tc_port != TC_PORT_NONE ? tc_port_name(tc_port) : phy_name(phy));
	पूर्ण अन्यथा अणु
		drm_encoder_init(&dev_priv->drm, &encoder->base, &पूर्णांकel_ddi_funcs,
				 DRM_MODE_ENCODER_TMDS,
				 "DDI %c/PHY %c", port_name(port),  phy_name(phy));
	पूर्ण

	mutex_init(&dig_port->hdcp_mutex);
	dig_port->num_hdcp_streams = 0;

	encoder->hotplug = पूर्णांकel_ddi_hotplug;
	encoder->compute_output_type = पूर्णांकel_ddi_compute_output_type;
	encoder->compute_config = पूर्णांकel_ddi_compute_config;
	encoder->compute_config_late = पूर्णांकel_ddi_compute_config_late;
	encoder->enable = पूर्णांकel_enable_ddi;
	encoder->pre_pll_enable = पूर्णांकel_ddi_pre_pll_enable;
	encoder->pre_enable = पूर्णांकel_ddi_pre_enable;
	encoder->disable = पूर्णांकel_disable_ddi;
	encoder->post_disable = पूर्णांकel_ddi_post_disable;
	encoder->update_pipe = पूर्णांकel_ddi_update_pipe;
	encoder->get_hw_state = पूर्णांकel_ddi_get_hw_state;
	encoder->sync_state = पूर्णांकel_ddi_sync_state;
	encoder->initial_fastset_check = पूर्णांकel_ddi_initial_fastset_check;
	encoder->suspend = पूर्णांकel_dp_encoder_suspend;
	encoder->shutकरोwn = पूर्णांकel_dp_encoder_shutकरोwn;
	encoder->get_घातer_करोमुख्यs = पूर्णांकel_ddi_get_घातer_करोमुख्यs;

	encoder->type = INTEL_OUTPUT_DDI;
	encoder->घातer_करोमुख्य = पूर्णांकel_port_to_घातer_करोमुख्य(port);
	encoder->port = port;
	encoder->cloneable = 0;
	encoder->pipe_mask = ~0;

	अगर (IS_ALDERLAKE_S(dev_priv)) अणु
		encoder->enable_घड़ी = adls_ddi_enable_घड़ी;
		encoder->disable_घड़ी = adls_ddi_disable_घड़ी;
		encoder->is_घड़ी_enabled = adls_ddi_is_घड़ी_enabled;
		encoder->get_config = adls_ddi_get_config;
	पूर्ण अन्यथा अगर (IS_ROCKETLAKE(dev_priv)) अणु
		encoder->enable_घड़ी = rkl_ddi_enable_घड़ी;
		encoder->disable_घड़ी = rkl_ddi_disable_घड़ी;
		encoder->is_घड़ी_enabled = rkl_ddi_is_घड़ी_enabled;
		encoder->get_config = rkl_ddi_get_config;
	पूर्ण अन्यथा अगर (IS_DG1(dev_priv)) अणु
		encoder->enable_घड़ी = dg1_ddi_enable_घड़ी;
		encoder->disable_घड़ी = dg1_ddi_disable_घड़ी;
		encoder->is_घड़ी_enabled = dg1_ddi_is_घड़ी_enabled;
		encoder->get_config = dg1_ddi_get_config;
	पूर्ण अन्यथा अगर (IS_JSL_EHL(dev_priv)) अणु
		अगर (पूर्णांकel_ddi_is_tc(dev_priv, port)) अणु
			encoder->enable_घड़ी = jsl_ddi_tc_enable_घड़ी;
			encoder->disable_घड़ी = jsl_ddi_tc_disable_घड़ी;
			encoder->is_घड़ी_enabled = jsl_ddi_tc_is_घड़ी_enabled;
			encoder->get_config = icl_ddi_combo_get_config;
		पूर्ण अन्यथा अणु
			encoder->enable_घड़ी = icl_ddi_combo_enable_घड़ी;
			encoder->disable_घड़ी = icl_ddi_combo_disable_घड़ी;
			encoder->is_घड़ी_enabled = icl_ddi_combo_is_घड़ी_enabled;
			encoder->get_config = icl_ddi_combo_get_config;
		पूर्ण
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		अगर (पूर्णांकel_ddi_is_tc(dev_priv, port)) अणु
			encoder->enable_घड़ी = icl_ddi_tc_enable_घड़ी;
			encoder->disable_घड़ी = icl_ddi_tc_disable_घड़ी;
			encoder->is_घड़ी_enabled = icl_ddi_tc_is_घड़ी_enabled;
			encoder->get_config = icl_ddi_tc_get_config;
		पूर्ण अन्यथा अणु
			encoder->enable_घड़ी = icl_ddi_combo_enable_घड़ी;
			encoder->disable_घड़ी = icl_ddi_combo_disable_घड़ी;
			encoder->is_घड़ी_enabled = icl_ddi_combo_is_घड़ी_enabled;
			encoder->get_config = icl_ddi_combo_get_config;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_CANNONLAKE(dev_priv)) अणु
		encoder->enable_घड़ी = cnl_ddi_enable_घड़ी;
		encoder->disable_घड़ी = cnl_ddi_disable_घड़ी;
		encoder->is_घड़ी_enabled = cnl_ddi_is_घड़ी_enabled;
		encoder->get_config = cnl_ddi_get_config;
	पूर्ण अन्यथा अगर (IS_GEN9_LP(dev_priv)) अणु
		/* BXT/GLK have fixed PLL->port mapping */
		encoder->get_config = bxt_ddi_get_config;
	पूर्ण अन्यथा अगर (IS_GEN9_BC(dev_priv)) अणु
		encoder->enable_घड़ी = skl_ddi_enable_घड़ी;
		encoder->disable_घड़ी = skl_ddi_disable_घड़ी;
		encoder->is_घड़ी_enabled = skl_ddi_is_घड़ी_enabled;
		encoder->get_config = skl_ddi_get_config;
	पूर्ण अन्यथा अगर (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv)) अणु
		encoder->enable_घड़ी = hsw_ddi_enable_घड़ी;
		encoder->disable_घड़ी = hsw_ddi_disable_घड़ी;
		encoder->is_घड़ी_enabled = hsw_ddi_is_घड़ी_enabled;
		encoder->get_config = hsw_ddi_get_config;
	पूर्ण

	अगर (IS_DG1(dev_priv))
		encoder->hpd_pin = dg1_hpd_pin(dev_priv, port);
	अन्यथा अगर (IS_ROCKETLAKE(dev_priv))
		encoder->hpd_pin = rkl_hpd_pin(dev_priv, port);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12)
		encoder->hpd_pin = tgl_hpd_pin(dev_priv, port);
	अन्यथा अगर (IS_JSL_EHL(dev_priv))
		encoder->hpd_pin = ehl_hpd_pin(dev_priv, port);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11))
		encoder->hpd_pin = icl_hpd_pin(dev_priv, port);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 10))
		encoder->hpd_pin = cnl_hpd_pin(dev_priv, port);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 9))
		encoder->hpd_pin = skl_hpd_pin(dev_priv, port);
	अन्यथा
		encoder->hpd_pin = पूर्णांकel_hpd_pin_शेष(dev_priv, port);

	अगर (DISPLAY_VER(dev_priv) >= 11)
		dig_port->saved_port_bits =
			पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port))
			& DDI_BUF_PORT_REVERSAL;
	अन्यथा
		dig_port->saved_port_bits =
			पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port))
			& (DDI_BUF_PORT_REVERSAL | DDI_A_4_LANES);

	अगर (पूर्णांकel_bios_is_lane_reversal_needed(dev_priv, port))
		dig_port->saved_port_bits |= DDI_BUF_PORT_REVERSAL;

	dig_port->dp.output_reg = INVALID_MMIO_REG;
	dig_port->max_lanes = पूर्णांकel_ddi_max_lanes(dig_port);
	dig_port->aux_ch = पूर्णांकel_bios_port_aux_ch(dev_priv, port);

	अगर (पूर्णांकel_phy_is_tc(dev_priv, phy)) अणु
		bool is_legacy =
			!पूर्णांकel_bios_encoder_supports_typec_usb(devdata) &&
			!पूर्णांकel_bios_encoder_supports_tbt(devdata);

		पूर्णांकel_tc_port_init(dig_port, is_legacy);

		encoder->update_prepare = पूर्णांकel_ddi_update_prepare;
		encoder->update_complete = पूर्णांकel_ddi_update_complete;
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, port > PORT_I);
	dig_port->ddi_io_घातer_करोमुख्य = POWER_DOMAIN_PORT_DDI_A_IO +
					      port - PORT_A;

	अगर (init_dp) अणु
		अगर (!पूर्णांकel_ddi_init_dp_connector(dig_port))
			जाओ err;

		dig_port->hpd_pulse = पूर्णांकel_dp_hpd_pulse;

		/* Splitter enable क्रम eDP MSO is supported क्रम pipe A only. */
		अगर (dig_port->dp.mso_link_count)
			encoder->pipe_mask = BIT(PIPE_A);
	पूर्ण

	/* In theory we करोn't need the encoder->type check, but leave it just in
	 * हाल we have some really bad VBTs... */
	अगर (encoder->type != INTEL_OUTPUT_EDP && init_hdmi) अणु
		अगर (!पूर्णांकel_ddi_init_hdmi_connector(dig_port))
			जाओ err;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		अगर (पूर्णांकel_phy_is_tc(dev_priv, phy))
			dig_port->connected = पूर्णांकel_tc_port_connected;
		अन्यथा
			dig_port->connected = lpt_digital_port_connected;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 8) अणु
		अगर (port == PORT_A || IS_GEN9_LP(dev_priv))
			dig_port->connected = bdw_digital_port_connected;
		अन्यथा
			dig_port->connected = lpt_digital_port_connected;
	पूर्ण अन्यथा अणु
		अगर (port == PORT_A)
			dig_port->connected = hsw_digital_port_connected;
		अन्यथा
			dig_port->connected = lpt_digital_port_connected;
	पूर्ण

	पूर्णांकel_infoframe_init(dig_port);

	वापस;

err:
	drm_encoder_cleanup(&encoder->base);
	kमुक्त(dig_port);
पूर्ण
