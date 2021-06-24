<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 *
 * HDMI support क्रम G4x,ILK,SNB,IVB,VLV,CHV (HSW+ handled by the DDI code).
 */

#समावेश "g4x_hdmi.h"
#समावेश "intel_audio.h"
#समावेश "intel_connector.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dpio_phy.h"
#समावेश "intel_fifo_underrun.h"
#समावेश "intel_hdmi.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_sideband.h"
#समावेश "intel_sdvo.h"

अटल व्योम पूर्णांकel_hdmi_prepare(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &crtc_state->hw.adjusted_mode;
	u32 hdmi_val;

	पूर्णांकel_dp_dual_mode_set_पंचांगds_output(पूर्णांकel_hdmi, true);

	hdmi_val = SDVO_ENCODING_HDMI;
	अगर (!HAS_PCH_SPLIT(dev_priv) && crtc_state->limited_color_range)
		hdmi_val |= HDMI_COLOR_RANGE_16_235;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		hdmi_val |= SDVO_VSYNC_ACTIVE_HIGH;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		hdmi_val |= SDVO_HSYNC_ACTIVE_HIGH;

	अगर (crtc_state->pipe_bpp > 24)
		hdmi_val |= HDMI_COLOR_FORMAT_12bpc;
	अन्यथा
		hdmi_val |= SDVO_COLOR_FORMAT_8bpc;

	अगर (crtc_state->has_hdmi_sink)
		hdmi_val |= HDMI_MODE_SELECT_HDMI;

	अगर (HAS_PCH_CPT(dev_priv))
		hdmi_val |= SDVO_PIPE_SEL_CPT(crtc->pipe);
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		hdmi_val |= SDVO_PIPE_SEL_CHV(crtc->pipe);
	अन्यथा
		hdmi_val |= SDVO_PIPE_SEL(crtc->pipe);

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, hdmi_val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);
पूर्ण

अटल bool पूर्णांकel_hdmi_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				    क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     encoder->घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret = पूर्णांकel_sdvo_port_enabled(dev_priv, पूर्णांकel_hdmi->hdmi_reg, pipe);

	पूर्णांकel_display_घातer_put(dev_priv, encoder->घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_hdmi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 पंचांगp, flags = 0;
	पूर्णांक करोtघड़ी;

	pipe_config->output_types |= BIT(INTEL_OUTPUT_HDMI);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	अगर (पंचांगp & SDVO_HSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_NHSYNC;

	अगर (पंचांगp & SDVO_VSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_NVSYNC;

	अगर (पंचांगp & HDMI_MODE_SELECT_HDMI)
		pipe_config->has_hdmi_sink = true;

	pipe_config->infoframes.enable |=
		पूर्णांकel_hdmi_infoframes_enabled(encoder, pipe_config);

	अगर (pipe_config->infoframes.enable)
		pipe_config->has_infoframe = true;

	अगर (पंचांगp & HDMI_AUDIO_ENABLE)
		pipe_config->has_audio = true;

	अगर (!HAS_PCH_SPLIT(dev_priv) &&
	    पंचांगp & HDMI_COLOR_RANGE_16_235)
		pipe_config->limited_color_range = true;

	pipe_config->hw.adjusted_mode.flags |= flags;

	अगर ((पंचांगp & SDVO_COLOR_FORMAT_MASK) == HDMI_COLOR_FORMAT_12bpc)
		करोtघड़ी = pipe_config->port_घड़ी * 2 / 3;
	अन्यथा
		करोtघड़ी = pipe_config->port_घड़ी;

	अगर (pipe_config->pixel_multiplier)
		करोtघड़ी /= pipe_config->pixel_multiplier;

	pipe_config->hw.adjusted_mode.crtc_घड़ी = करोtघड़ी;

	pipe_config->lane_count = 4;

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
पूर्ण

अटल व्योम पूर्णांकel_enable_hdmi_audio(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);

	drm_WARN_ON(&i915->drm, !pipe_config->has_hdmi_sink);
	drm_dbg_kms(&i915->drm, "Enabling HDMI audio on pipe %c\n",
		    pipe_name(crtc->pipe));
	पूर्णांकel_audio_codec_enable(encoder, pipe_config, conn_state);
पूर्ण

अटल व्योम g4x_enable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	u32 temp;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	temp |= SDVO_ENABLE;
	अगर (pipe_config->has_audio)
		temp |= HDMI_AUDIO_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	अगर (pipe_config->has_audio)
		पूर्णांकel_enable_hdmi_audio(encoder, pipe_config, conn_state);
पूर्ण

अटल व्योम ibx_enable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	u32 temp;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	temp |= SDVO_ENABLE;
	अगर (pipe_config->has_audio)
		temp |= HDMI_AUDIO_ENABLE;

	/*
	 * HW workaround, need to ग_लिखो this twice क्रम issue
	 * that may result in first ग_लिखो getting masked.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);
	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	/*
	 * HW workaround, need to toggle enable bit off and on
	 * क्रम 12bpc with pixel repeat.
	 *
	 * FIXME: BSpec says this should be करोne at the end of
	 * the modeset sequence, so not sure अगर this isn't too soon.
	 */
	अगर (pipe_config->pipe_bpp > 24 &&
	    pipe_config->pixel_multiplier > 1) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg,
			       temp & ~SDVO_ENABLE);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

		/*
		 * HW workaround, need to ग_लिखो this twice क्रम issue
		 * that may result in first ग_लिखो getting masked.
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);
	पूर्ण

	अगर (pipe_config->has_audio)
		पूर्णांकel_enable_hdmi_audio(encoder, pipe_config, conn_state);
पूर्ण

अटल व्योम cpt_enable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	क्रमागत pipe pipe = crtc->pipe;
	u32 temp;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	temp |= SDVO_ENABLE;
	अगर (pipe_config->has_audio)
		temp |= HDMI_AUDIO_ENABLE;

	/*
	 * WaEnableHDMI8bpcBeक्रमe12bpc:snb,ivb
	 *
	 * The procedure क्रम 12bpc is as follows:
	 * 1. disable HDMI घड़ी gating
	 * 2. enable HDMI with 8bpc
	 * 3. enable HDMI with 12bpc
	 * 4. enable HDMI घड़ी gating
	 */

	अगर (pipe_config->pipe_bpp > 24) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_CHICKEN1(pipe),
			       पूर्णांकel_de_पढ़ो(dev_priv, TRANS_CHICKEN1(pipe)) | TRANS_CHICKEN1_HDMIUNIT_GC_DISABLE);

		temp &= ~SDVO_COLOR_FORMAT_MASK;
		temp |= SDVO_COLOR_FORMAT_8bpc;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	अगर (pipe_config->pipe_bpp > 24) अणु
		temp &= ~SDVO_COLOR_FORMAT_MASK;
		temp |= HDMI_COLOR_FORMAT_12bpc;

		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

		पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_CHICKEN1(pipe),
			       पूर्णांकel_de_पढ़ो(dev_priv, TRANS_CHICKEN1(pipe)) & ~TRANS_CHICKEN1_HDMIUNIT_GC_DISABLE);
	पूर्ण

	अगर (pipe_config->has_audio)
		पूर्णांकel_enable_hdmi_audio(encoder, pipe_config, conn_state);
पूर्ण

अटल व्योम vlv_enable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
पूर्ण

अटल व्योम पूर्णांकel_disable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			       स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_hdmi *पूर्णांकel_hdmi = enc_to_पूर्णांकel_hdmi(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port =
		hdmi_to_dig_port(पूर्णांकel_hdmi);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	u32 temp;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	temp &= ~(SDVO_ENABLE | HDMI_AUDIO_ENABLE);
	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

	/*
	 * HW workaround क्रम IBX, we need to move the port
	 * to transcoder A after disabling it to allow the
	 * matching DP port to be enabled on transcoder A.
	 */
	अगर (HAS_PCH_IBX(dev_priv) && crtc->pipe == PIPE_B) अणु
		/*
		 * We get CPU/PCH FIFO underruns on the other pipe when
		 * करोing the workaround. Sweep them under the rug.
		 */
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, PIPE_A, false);
		पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, false);

		temp &= ~SDVO_PIPE_SEL_MASK;
		temp |= SDVO_ENABLE | SDVO_PIPE_SEL(PIPE_A);
		/*
		 * HW workaround, need to ग_लिखो this twice क्रम issue
		 * that may result in first ग_लिखो getting masked.
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

		temp &= ~SDVO_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_hdmi->hdmi_reg, temp);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_hdmi->hdmi_reg);

		पूर्णांकel_रुको_क्रम_vblank_अगर_active(dev_priv, PIPE_A);
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, PIPE_A, true);
		पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, true);
	पूर्ण

	dig_port->set_infoframes(encoder,
				       false,
				       old_crtc_state, old_conn_state);

	पूर्णांकel_dp_dual_mode_set_पंचांगds_output(पूर्णांकel_hdmi, false);
पूर्ण

अटल व्योम g4x_disable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			     स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	अगर (old_crtc_state->has_audio)
		पूर्णांकel_audio_codec_disable(encoder,
					  old_crtc_state, old_conn_state);

	पूर्णांकel_disable_hdmi(state, encoder, old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम pch_disable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			     स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	अगर (old_crtc_state->has_audio)
		पूर्णांकel_audio_codec_disable(encoder,
					  old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम pch_post_disable_hdmi(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				  स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_disable_hdmi(state, encoder, old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम पूर्णांकel_hdmi_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port =
		enc_to_dig_port(encoder);

	पूर्णांकel_hdmi_prepare(encoder, pipe_config);

	dig_port->set_infoframes(encoder,
				       pipe_config->has_infoframe,
				       pipe_config, conn_state);
पूर्ण

अटल व्योम vlv_hdmi_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	vlv_phy_pre_encoder_enable(encoder, pipe_config);

	/* HDMI 1.0V-2dB */
	vlv_set_phy_संकेत_level(encoder, pipe_config,
				 0x2b245f5f, 0x00002000,
				 0x5578b83a, 0x2b247878);

	dig_port->set_infoframes(encoder,
			      pipe_config->has_infoframe,
			      pipe_config, conn_state);

	g4x_enable_hdmi(state, encoder, pipe_config, conn_state);

	vlv_रुको_port_पढ़ोy(dev_priv, dig_port, 0x0);
पूर्ण

अटल व्योम vlv_hdmi_pre_pll_enable(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांकel_hdmi_prepare(encoder, pipe_config);

	vlv_phy_pre_pll_enable(encoder, pipe_config);
पूर्ण

अटल व्योम chv_hdmi_pre_pll_enable(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांकel_hdmi_prepare(encoder, pipe_config);

	chv_phy_pre_pll_enable(encoder, pipe_config);
पूर्ण

अटल व्योम chv_hdmi_post_pll_disable(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_encoder *encoder,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				      स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	chv_phy_post_pll_disable(encoder, old_crtc_state);
पूर्ण

अटल व्योम vlv_hdmi_post_disable(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				  स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	/* Reset lanes to aव्योम HDMI flicker (VLV w/a) */
	vlv_phy_reset_lanes(encoder, old_crtc_state);
पूर्ण

अटल व्योम chv_hdmi_post_disable(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				  स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	vlv_dpio_get(dev_priv);

	/* Assert data lane reset */
	chv_data_lane_soft_reset(encoder, old_crtc_state, true);

	vlv_dpio_put(dev_priv);
पूर्ण

अटल व्योम chv_hdmi_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = enc_to_dig_port(encoder);
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	chv_phy_pre_encoder_enable(encoder, pipe_config);

	/* FIXME: Program the support xxx V-dB */
	/* Use 800mV-0dB */
	chv_set_phy_संकेत_level(encoder, pipe_config, 128, 102, false);

	dig_port->set_infoframes(encoder,
			      pipe_config->has_infoframe,
			      pipe_config, conn_state);

	g4x_enable_hdmi(state, encoder, pipe_config, conn_state);

	vlv_रुको_port_पढ़ोy(dev_priv, dig_port, 0x0);

	/* Second common lane will stay alive on its own now */
	chv_phy_release_cl2_override(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_hdmi_enc_funcs = अणु
	.destroy = पूर्णांकel_encoder_destroy,
पूर्ण;

अटल क्रमागत पूर्णांकel_hotplug_state
पूर्णांकel_hdmi_hotplug(काष्ठा पूर्णांकel_encoder *encoder,
		   काष्ठा पूर्णांकel_connector *connector)
अणु
	क्रमागत पूर्णांकel_hotplug_state state;

	state = पूर्णांकel_encoder_hotplug(encoder, connector);

	/*
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
	 */
	अगर (state == INTEL_HOTPLUG_UNCHANGED && !connector->hotplug_retries)
		state = INTEL_HOTPLUG_RETRY;

	वापस state;
पूर्ण

व्योम g4x_hdmi_init(काष्ठा drm_i915_निजी *dev_priv,
		   i915_reg_t hdmi_reg, क्रमागत port port)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;

	dig_port = kzalloc(माप(*dig_port), GFP_KERNEL);
	अगर (!dig_port)
		वापस;

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector) अणु
		kमुक्त(dig_port);
		वापस;
	पूर्ण

	पूर्णांकel_encoder = &dig_port->base;

	mutex_init(&dig_port->hdcp_mutex);

	drm_encoder_init(&dev_priv->drm, &पूर्णांकel_encoder->base,
			 &पूर्णांकel_hdmi_enc_funcs, DRM_MODE_ENCODER_TMDS,
			 "HDMI %c", port_name(port));

	पूर्णांकel_encoder->hotplug = पूर्णांकel_hdmi_hotplug;
	पूर्णांकel_encoder->compute_config = पूर्णांकel_hdmi_compute_config;
	अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		पूर्णांकel_encoder->disable = pch_disable_hdmi;
		पूर्णांकel_encoder->post_disable = pch_post_disable_hdmi;
	पूर्ण अन्यथा अणु
		पूर्णांकel_encoder->disable = g4x_disable_hdmi;
	पूर्ण
	पूर्णांकel_encoder->get_hw_state = पूर्णांकel_hdmi_get_hw_state;
	पूर्णांकel_encoder->get_config = पूर्णांकel_hdmi_get_config;
	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		पूर्णांकel_encoder->pre_pll_enable = chv_hdmi_pre_pll_enable;
		पूर्णांकel_encoder->pre_enable = chv_hdmi_pre_enable;
		पूर्णांकel_encoder->enable = vlv_enable_hdmi;
		पूर्णांकel_encoder->post_disable = chv_hdmi_post_disable;
		पूर्णांकel_encoder->post_pll_disable = chv_hdmi_post_pll_disable;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv)) अणु
		पूर्णांकel_encoder->pre_pll_enable = vlv_hdmi_pre_pll_enable;
		पूर्णांकel_encoder->pre_enable = vlv_hdmi_pre_enable;
		पूर्णांकel_encoder->enable = vlv_enable_hdmi;
		पूर्णांकel_encoder->post_disable = vlv_hdmi_post_disable;
	पूर्ण अन्यथा अणु
		पूर्णांकel_encoder->pre_enable = पूर्णांकel_hdmi_pre_enable;
		अगर (HAS_PCH_CPT(dev_priv))
			पूर्णांकel_encoder->enable = cpt_enable_hdmi;
		अन्यथा अगर (HAS_PCH_IBX(dev_priv))
			पूर्णांकel_encoder->enable = ibx_enable_hdmi;
		अन्यथा
			पूर्णांकel_encoder->enable = g4x_enable_hdmi;
	पूर्ण

	पूर्णांकel_encoder->type = INTEL_OUTPUT_HDMI;
	पूर्णांकel_encoder->घातer_करोमुख्य = पूर्णांकel_port_to_घातer_करोमुख्य(port);
	पूर्णांकel_encoder->port = port;
	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		अगर (port == PORT_D)
			पूर्णांकel_encoder->pipe_mask = BIT(PIPE_C);
		अन्यथा
			पूर्णांकel_encoder->pipe_mask = BIT(PIPE_A) | BIT(PIPE_B);
	पूर्ण अन्यथा अणु
		पूर्णांकel_encoder->pipe_mask = ~0;
	पूर्ण
	पूर्णांकel_encoder->cloneable = 1 << INTEL_OUTPUT_ANALOG;
	पूर्णांकel_encoder->hpd_pin = पूर्णांकel_hpd_pin_शेष(dev_priv, port);
	/*
	 * BSpec is unclear about HDMI+HDMI cloning on g4x, but it seems
	 * to work on real hardware. And since g4x can send infoframes to
	 * only one port anyway, nothing is lost by allowing it.
	 */
	अगर (IS_G4X(dev_priv))
		पूर्णांकel_encoder->cloneable |= 1 << INTEL_OUTPUT_HDMI;

	dig_port->hdmi.hdmi_reg = hdmi_reg;
	dig_port->dp.output_reg = INVALID_MMIO_REG;
	dig_port->max_lanes = 4;

	पूर्णांकel_infoframe_init(dig_port);

	dig_port->aux_ch = पूर्णांकel_bios_port_aux_ch(dev_priv, port);
	पूर्णांकel_hdmi_init_connector(dig_port, पूर्णांकel_connector);
पूर्ण
