<शैली गुरु>
/*
 * Copyright तऊ 2008 Intel Corporation
 *             2014 Red Hat Inc.
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
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_audio.h"
#समावेश "intel_connector.h"
#समावेश "intel_ddi.h"
#समावेश "intel_display_types.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_dp.h"
#समावेश "intel_dp_mst.h"
#समावेश "intel_dpio_phy.h"
#समावेश "intel_hdcp.h"
#समावेश "skl_scaler.h"

अटल पूर्णांक पूर्णांकel_dp_mst_compute_link_config(काष्ठा पूर्णांकel_encoder *encoder,
					    काष्ठा पूर्णांकel_crtc_state *crtc_state,
					    काष्ठा drm_connector_state *conn_state,
					    काष्ठा link_config_limits *limits)
अणु
	काष्ठा drm_atomic_state *state = crtc_state->uapi.state;
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &पूर्णांकel_mst->primary->dp;
	काष्ठा पूर्णांकel_connector *connector =
		to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	bool स्थिरant_n = drm_dp_has_quirk(&पूर्णांकel_dp->desc, DP_DPCD_QUIRK_CONSTANT_N);
	पूर्णांक bpp, slots = -EINVAL;

	crtc_state->lane_count = limits->max_lane_count;
	crtc_state->port_घड़ी = limits->max_घड़ी;

	क्रम (bpp = limits->max_bpp; bpp >= limits->min_bpp; bpp -= 2 * 3) अणु
		crtc_state->pipe_bpp = bpp;

		crtc_state->pbn = drm_dp_calc_pbn_mode(adjusted_mode->crtc_घड़ी,
						       crtc_state->pipe_bpp,
						       false);

		slots = drm_dp_atomic_find_vcpi_slots(state, &पूर्णांकel_dp->mst_mgr,
						      connector->port,
						      crtc_state->pbn,
						      drm_dp_get_vc_payload_bw(crtc_state->port_घड़ी,
									       crtc_state->lane_count));
		अगर (slots == -EDEADLK)
			वापस slots;
		अगर (slots >= 0)
			अवरोध;
	पूर्ण

	अगर (slots < 0) अणु
		drm_dbg_kms(&i915->drm, "failed finding vcpi slots:%d\n",
			    slots);
		वापस slots;
	पूर्ण

	पूर्णांकel_link_compute_m_n(crtc_state->pipe_bpp,
			       crtc_state->lane_count,
			       adjusted_mode->crtc_घड़ी,
			       crtc_state->port_घड़ी,
			       &crtc_state->dp_m_n,
			       स्थिरant_n, crtc_state->fec_enable);
	crtc_state->dp_m_n.tu = slots;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_mst_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				       काष्ठा पूर्णांकel_crtc_state *pipe_config,
				       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &पूर्णांकel_mst->primary->dp;
	काष्ठा पूर्णांकel_connector *connector =
		to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा पूर्णांकel_digital_connector_state *पूर्णांकel_conn_state =
		to_पूर्णांकel_digital_connector_state(conn_state);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	काष्ठा link_config_limits limits;
	पूर्णांक ret;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;
	pipe_config->has_pch_encoder = false;

	अगर (पूर्णांकel_conn_state->क्रमce_audio == HDMI_AUDIO_AUTO)
		pipe_config->has_audio = connector->port->has_audio;
	अन्यथा
		pipe_config->has_audio =
			पूर्णांकel_conn_state->क्रमce_audio == HDMI_AUDIO_ON;

	/*
	 * क्रम MST we always configure max link bw - the spec करोesn't
	 * seem to suggest we should करो otherwise.
	 */
	limits.min_घड़ी =
	limits.max_घड़ी = पूर्णांकel_dp_max_link_rate(पूर्णांकel_dp);

	limits.min_lane_count =
	limits.max_lane_count = पूर्णांकel_dp_max_lane_count(पूर्णांकel_dp);

	limits.min_bpp = पूर्णांकel_dp_min_bpp(pipe_config->output_क्रमmat);
	/*
	 * FIXME: If all the streams can't fit पूर्णांकo the link with
	 * their current pipe_bpp we should reduce pipe_bpp across
	 * the board until things start to fit. Until then we
	 * limit to <= 8bpc since that's what was hardcoded क्रम all
	 * MST streams previously. This hack should be हटाओd once
	 * we have the proper retry logic in place.
	 */
	limits.max_bpp = min(pipe_config->pipe_bpp, 24);

	पूर्णांकel_dp_adjust_compliance_config(पूर्णांकel_dp, pipe_config, &limits);

	ret = पूर्णांकel_dp_mst_compute_link_config(encoder, pipe_config,
					       conn_state, &limits);
	अगर (ret)
		वापस ret;

	pipe_config->limited_color_range =
		पूर्णांकel_dp_limited_color_range(pipe_config, conn_state);

	अगर (IS_GEN9_LP(dev_priv))
		pipe_config->lane_lat_optim_mask =
			bxt_ddi_phy_calc_lane_lat_optim_mask(pipe_config->lane_count);

	पूर्णांकel_ddi_compute_min_voltage_level(dev_priv, pipe_config);

	वापस 0;
पूर्ण

/*
 * Iterate over all connectors and वापस a mask of
 * all CPU transcoders streaming over the same DP link.
 */
अटल अचिन्हित पूर्णांक
पूर्णांकel_dp_mst_transcoder_mask(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_dp *mst_port)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_digital_connector_state *conn_state;
	काष्ठा पूर्णांकel_connector *connector;
	u8 transcoders = 0;
	पूर्णांक i;

	अगर (DISPLAY_VER(dev_priv) < 12)
		वापस 0;

	क्रम_each_new_पूर्णांकel_connector_in_state(state, connector, conn_state, i) अणु
		स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state;
		काष्ठा पूर्णांकel_crtc *crtc;

		अगर (connector->mst_port != mst_port || !conn_state->base.crtc)
			जारी;

		crtc = to_पूर्णांकel_crtc(conn_state->base.crtc);
		crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

		अगर (!crtc_state->hw.active)
			जारी;

		transcoders |= BIT(crtc_state->cpu_transcoder);
	पूर्ण

	वापस transcoders;
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_mst_compute_config_late(काष्ठा पूर्णांकel_encoder *encoder,
					    काष्ठा पूर्णांकel_crtc_state *crtc_state,
					    काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(conn_state->state);
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &पूर्णांकel_mst->primary->dp;

	/* lowest numbered transcoder will be designated master */
	crtc_state->mst_master_transcoder =
		ffs(पूर्णांकel_dp_mst_transcoder_mask(state, पूर्णांकel_dp)) - 1;

	वापस 0;
पूर्ण

/*
 * If one of the connectors in a MST stream needs a modeset, mark all CRTCs
 * that shares the same MST stream as mode changed,
 * पूर्णांकel_modeset_pipe_config()+पूर्णांकel_crtc_check_fastset() will take care to करो
 * a fastset when possible.
 */
अटल पूर्णांक
पूर्णांकel_dp_mst_atomic_master_trans_check(काष्ठा पूर्णांकel_connector *connector,
				       काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा drm_connector_list_iter connector_list_iter;
	काष्ठा पूर्णांकel_connector *connector_iter;

	अगर (DISPLAY_VER(dev_priv) < 12)
		वापस  0;

	अगर (!पूर्णांकel_connector_needs_modeset(state, &connector->base))
		वापस 0;

	drm_connector_list_iter_begin(&dev_priv->drm, &connector_list_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector_iter, &connector_list_iter) अणु
		काष्ठा पूर्णांकel_digital_connector_state *conn_iter_state;
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		काष्ठा पूर्णांकel_crtc *crtc;
		पूर्णांक ret;

		अगर (connector_iter->mst_port != connector->mst_port ||
		    connector_iter == connector)
			जारी;

		conn_iter_state = पूर्णांकel_atomic_get_digital_connector_state(state,
									   connector_iter);
		अगर (IS_ERR(conn_iter_state)) अणु
			drm_connector_list_iter_end(&connector_list_iter);
			वापस PTR_ERR(conn_iter_state);
		पूर्ण

		अगर (!conn_iter_state->base.crtc)
			जारी;

		crtc = to_पूर्णांकel_crtc(conn_iter_state->base.crtc);
		crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, crtc);
		अगर (IS_ERR(crtc_state)) अणु
			drm_connector_list_iter_end(&connector_list_iter);
			वापस PTR_ERR(crtc_state);
		पूर्ण

		ret = drm_atomic_add_affected_planes(&state->base, &crtc->base);
		अगर (ret) अणु
			drm_connector_list_iter_end(&connector_list_iter);
			वापस ret;
		पूर्ण
		crtc_state->uapi.mode_changed = true;
	पूर्ण
	drm_connector_list_iter_end(&connector_list_iter);

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_mst_atomic_check(काष्ठा drm_connector *connector,
			  काष्ठा drm_atomic_state *_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(_state);
	काष्ठा drm_connector_state *new_conn_state =
		drm_atomic_get_new_connector_state(&state->base, connector);
	काष्ठा drm_connector_state *old_conn_state =
		drm_atomic_get_old_connector_state(&state->base, connector);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector =
		to_पूर्णांकel_connector(connector);
	काष्ठा drm_crtc *new_crtc = new_conn_state->crtc;
	काष्ठा drm_dp_mst_topology_mgr *mgr;
	पूर्णांक ret;

	ret = पूर्णांकel_digital_connector_atomic_check(connector, &state->base);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_dp_mst_atomic_master_trans_check(पूर्णांकel_connector, state);
	अगर (ret)
		वापस ret;

	अगर (!old_conn_state->crtc)
		वापस 0;

	/* We only want to मुक्त VCPI अगर this state disables the CRTC on this
	 * connector
	 */
	अगर (new_crtc) अणु
		काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(new_crtc);
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			पूर्णांकel_atomic_get_new_crtc_state(state, पूर्णांकel_crtc);

		अगर (!crtc_state ||
		    !drm_atomic_crtc_needs_modeset(&crtc_state->uapi) ||
		    crtc_state->uapi.enable)
			वापस 0;
	पूर्ण

	mgr = &enc_to_mst(to_पूर्णांकel_encoder(old_conn_state->best_encoder))->primary->dp.mst_mgr;
	ret = drm_dp_atomic_release_vcpi_slots(&state->base, mgr,
					       पूर्णांकel_connector->port);

	वापस ret;
पूर्ण

अटल व्योम clear_act_sent(काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);

	पूर्णांकel_de_ग_लिखो(i915, dp_tp_status_reg(encoder, crtc_state),
		       DP_TP_STATUS_ACT_SENT);
पूर्ण

अटल व्योम रुको_क्रम_act_sent(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &पूर्णांकel_mst->primary->dp;

	अगर (पूर्णांकel_de_रुको_क्रम_set(i915, dp_tp_status_reg(encoder, crtc_state),
				  DP_TP_STATUS_ACT_SENT, 1))
		drm_err(&i915->drm, "Timed out waiting for ACT sent\n");

	drm_dp_check_act_status(&पूर्णांकel_dp->mst_mgr);
पूर्ण

अटल व्योम पूर्णांकel_mst_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				 स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_mst->primary;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	काष्ठा पूर्णांकel_connector *connector =
		to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);
	पूर्णांक ret;

	drm_dbg_kms(&i915->drm, "active links %d\n",
		    पूर्णांकel_dp->active_mst_links);

	पूर्णांकel_hdcp_disable(पूर्णांकel_mst->connector);

	drm_dp_mst_reset_vcpi_slots(&पूर्णांकel_dp->mst_mgr, connector->port);

	ret = drm_dp_update_payload_part1(&पूर्णांकel_dp->mst_mgr);
	अगर (ret) अणु
		drm_dbg_kms(&i915->drm, "failed to update payload %d\n", ret);
	पूर्ण
	अगर (old_crtc_state->has_audio)
		पूर्णांकel_audio_codec_disable(encoder,
					  old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम पूर्णांकel_mst_post_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_encoder *encoder,
				      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				      स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_mst->primary;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	काष्ठा पूर्णांकel_connector *connector =
		to_पूर्णांकel_connector(old_conn_state->connector);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);
	bool last_mst_stream;
	u32 val;

	पूर्णांकel_dp->active_mst_links--;
	last_mst_stream = पूर्णांकel_dp->active_mst_links == 0;
	drm_WARN_ON(&dev_priv->drm,
		    DISPLAY_VER(dev_priv) >= 12 && last_mst_stream &&
		    !पूर्णांकel_dp_mst_is_master_trans(old_crtc_state));

	पूर्णांकel_crtc_vblank_off(old_crtc_state);

	पूर्णांकel_disable_pipe(old_crtc_state);

	drm_dp_update_payload_part2(&पूर्णांकel_dp->mst_mgr);

	clear_act_sent(encoder, old_crtc_state);

	val = पूर्णांकel_de_पढ़ो(dev_priv,
			    TRANS_DDI_FUNC_CTL(old_crtc_state->cpu_transcoder));
	val &= ~TRANS_DDI_DP_VC_PAYLOAD_ALLOC;
	पूर्णांकel_de_ग_लिखो(dev_priv,
		       TRANS_DDI_FUNC_CTL(old_crtc_state->cpu_transcoder),
		       val);

	रुको_क्रम_act_sent(encoder, old_crtc_state);

	drm_dp_mst_deallocate_vcpi(&पूर्णांकel_dp->mst_mgr, connector->port);

	पूर्णांकel_ddi_disable_transcoder_func(old_crtc_state);

	अगर (DISPLAY_VER(dev_priv) >= 9)
		skl_scaler_disable(old_crtc_state);
	अन्यथा
		ilk_pfit_disable(old_crtc_state);

	/*
	 * Power करोwn mst path beक्रमe disabling the port, otherwise we end
	 * up getting पूर्णांकerrupts from the sink upon detecting link loss.
	 */
	drm_dp_send_घातer_upकरोwn_phy(&पूर्णांकel_dp->mst_mgr, connector->port,
				     false);

	/*
	 * BSpec 4287: disable DIP after the transcoder is disabled and beक्रमe
	 * the transcoder घड़ी select is set to none.
	 */
	अगर (last_mst_stream)
		पूर्णांकel_dp_set_infoframes(&dig_port->base, false,
					old_crtc_state, शून्य);
	/*
	 * From TGL spec: "If multi-stream slave transcoder: Configure
	 * Transcoder Clock Select to direct no घड़ी to the transcoder"
	 *
	 * From older GENs spec: "Configure Transcoder Clock Select to direct
	 * no घड़ी to the transcoder"
	 */
	अगर (DISPLAY_VER(dev_priv) < 12 || !last_mst_stream)
		पूर्णांकel_ddi_disable_pipe_घड़ी(old_crtc_state);


	पूर्णांकel_mst->connector = शून्य;
	अगर (last_mst_stream)
		dig_port->base.post_disable(state, &dig_port->base,
						  old_crtc_state, शून्य);

	drm_dbg_kms(&dev_priv->drm, "active links %d\n",
		    पूर्णांकel_dp->active_mst_links);
पूर्ण

अटल व्योम पूर्णांकel_mst_pre_pll_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
					काष्ठा पूर्णांकel_encoder *encoder,
					स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
					स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_mst->primary;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;

	अगर (पूर्णांकel_dp->active_mst_links == 0)
		dig_port->base.pre_pll_enable(state, &dig_port->base,
						    pipe_config, शून्य);
पूर्ण

अटल व्योम पूर्णांकel_mst_pre_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_mst->primary;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_connector *connector =
		to_पूर्णांकel_connector(conn_state->connector);
	पूर्णांक ret;
	bool first_mst_stream;

	/* MST encoders are bound to a crtc, not to a connector,
	 * क्रमce the mapping here क्रम get_hw_state.
	 */
	connector->encoder = encoder;
	पूर्णांकel_mst->connector = connector;
	first_mst_stream = पूर्णांकel_dp->active_mst_links == 0;
	drm_WARN_ON(&dev_priv->drm,
		    DISPLAY_VER(dev_priv) >= 12 && first_mst_stream &&
		    !पूर्णांकel_dp_mst_is_master_trans(pipe_config));

	drm_dbg_kms(&dev_priv->drm, "active links %d\n",
		    पूर्णांकel_dp->active_mst_links);

	अगर (first_mst_stream)
		पूर्णांकel_dp_set_घातer(पूर्णांकel_dp, DP_SET_POWER_D0);

	drm_dp_send_घातer_upकरोwn_phy(&पूर्णांकel_dp->mst_mgr, connector->port, true);

	अगर (first_mst_stream)
		dig_port->base.pre_enable(state, &dig_port->base,
						pipe_config, शून्य);

	ret = drm_dp_mst_allocate_vcpi(&पूर्णांकel_dp->mst_mgr,
				       connector->port,
				       pipe_config->pbn,
				       pipe_config->dp_m_n.tu);
	अगर (!ret)
		drm_err(&dev_priv->drm, "failed to allocate vcpi\n");

	पूर्णांकel_dp->active_mst_links++;

	ret = drm_dp_update_payload_part1(&पूर्णांकel_dp->mst_mgr);

	/*
	 * Beक्रमe Gen 12 this is not करोne as part of
	 * dig_port->base.pre_enable() and should be करोne here. For
	 * Gen 12+ the step in which this should be करोne is dअगरferent क्रम the
	 * first MST stream, so it's करोne on the DDI क्रम the first stream and
	 * here क्रम the following ones.
	 */
	अगर (DISPLAY_VER(dev_priv) < 12 || !first_mst_stream)
		पूर्णांकel_ddi_enable_pipe_घड़ी(encoder, pipe_config);

	पूर्णांकel_ddi_set_dp_msa(pipe_config, conn_state);

	पूर्णांकel_dp_set_m_n(pipe_config, M1_N1);
पूर्ण

अटल व्योम पूर्णांकel_mst_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_mst->primary;
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 val;

	drm_WARN_ON(&dev_priv->drm, pipe_config->has_pch_encoder);

	clear_act_sent(encoder, pipe_config);

	पूर्णांकel_ddi_enable_transcoder_func(encoder, pipe_config);

	val = पूर्णांकel_de_पढ़ो(dev_priv,
			    TRANS_DDI_FUNC_CTL(pipe_config->cpu_transcoder));
	val |= TRANS_DDI_DP_VC_PAYLOAD_ALLOC;
	पूर्णांकel_de_ग_लिखो(dev_priv,
		       TRANS_DDI_FUNC_CTL(pipe_config->cpu_transcoder),
		       val);

	drm_dbg_kms(&dev_priv->drm, "active links %d\n",
		    पूर्णांकel_dp->active_mst_links);

	रुको_क्रम_act_sent(encoder, pipe_config);

	drm_dp_update_payload_part2(&पूर्णांकel_dp->mst_mgr);

	पूर्णांकel_enable_pipe(pipe_config);

	पूर्णांकel_crtc_vblank_on(pipe_config);

	अगर (pipe_config->has_audio)
		पूर्णांकel_audio_codec_enable(encoder, pipe_config, conn_state);

	/* Enable hdcp अगर it's desired */
	अगर (conn_state->content_protection ==
	    DRM_MODE_CONTENT_PROTECTION_DESIRED)
		पूर्णांकel_hdcp_enable(to_पूर्णांकel_connector(conn_state->connector),
				  pipe_config,
				  (u8)conn_state->hdcp_content_type);
पूर्ण

अटल bool पूर्णांकel_dp_mst_enc_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				      क्रमागत pipe *pipe)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	*pipe = पूर्णांकel_mst->pipe;
	अगर (पूर्णांकel_mst->connector)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम पूर्णांकel_dp_mst_enc_get_config(काष्ठा पूर्णांकel_encoder *encoder,
					काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_mst->primary;

	dig_port->base.get_config(&dig_port->base, pipe_config);
पूर्ण

अटल bool पूर्णांकel_dp_mst_initial_fastset_check(काष्ठा पूर्णांकel_encoder *encoder,
					       काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = पूर्णांकel_mst->primary;

	वापस पूर्णांकel_dp_initial_fastset_check(&dig_port->base, crtc_state);
पूर्ण

अटल पूर्णांक पूर्णांकel_dp_mst_get_ddc_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_connector->mst_port;
	काष्ठा edid *edid;
	पूर्णांक ret;

	अगर (drm_connector_is_unरेजिस्टरed(connector))
		वापस पूर्णांकel_connector_update_modes(connector, शून्य);

	edid = drm_dp_mst_get_edid(connector, &पूर्णांकel_dp->mst_mgr, पूर्णांकel_connector->port);
	ret = पूर्णांकel_connector_update_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_mst_connector_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	पूर्णांक ret;

	ret = drm_dp_mst_connector_late_रेजिस्टर(connector,
						 पूर्णांकel_connector->port);
	अगर (ret < 0)
		वापस ret;

	ret = पूर्णांकel_connector_रेजिस्टर(connector);
	अगर (ret < 0)
		drm_dp_mst_connector_early_unरेजिस्टर(connector,
						      पूर्णांकel_connector->port);

	वापस ret;
पूर्ण

अटल व्योम
पूर्णांकel_dp_mst_connector_early_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);

	पूर्णांकel_connector_unरेजिस्टर(connector);
	drm_dp_mst_connector_early_unरेजिस्टर(connector,
					      पूर्णांकel_connector->port);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_dp_mst_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_get_property = पूर्णांकel_digital_connector_atomic_get_property,
	.atomic_set_property = पूर्णांकel_digital_connector_atomic_set_property,
	.late_रेजिस्टर = पूर्णांकel_dp_mst_connector_late_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_dp_mst_connector_early_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = पूर्णांकel_digital_connector_duplicate_state,
पूर्ण;

अटल पूर्णांक पूर्णांकel_dp_mst_get_modes(काष्ठा drm_connector *connector)
अणु
	वापस पूर्णांकel_dp_mst_get_ddc_modes(connector);
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_mst_mode_valid_ctx(काष्ठा drm_connector *connector,
			    काष्ठा drm_display_mode *mode,
			    काष्ठा drm_modeset_acquire_ctx *ctx,
			    क्रमागत drm_mode_status *status)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_connector->mst_port;
	काष्ठा drm_dp_mst_topology_mgr *mgr = &पूर्णांकel_dp->mst_mgr;
	काष्ठा drm_dp_mst_port *port = पूर्णांकel_connector->port;
	स्थिर पूर्णांक min_bpp = 18;
	पूर्णांक max_करोtclk = to_i915(connector->dev)->max_करोtclk_freq;
	पूर्णांक max_rate, mode_rate, max_lanes, max_link_घड़ी;
	पूर्णांक ret;

	अगर (drm_connector_is_unरेजिस्टरed(connector)) अणु
		*status = MODE_ERROR;
		वापस 0;
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN) अणु
		*status = MODE_NO_DBLESCAN;
		वापस 0;
	पूर्ण

	max_link_घड़ी = पूर्णांकel_dp_max_link_rate(पूर्णांकel_dp);
	max_lanes = पूर्णांकel_dp_max_lane_count(पूर्णांकel_dp);

	max_rate = पूर्णांकel_dp_max_data_rate(max_link_घड़ी, max_lanes);
	mode_rate = पूर्णांकel_dp_link_required(mode->घड़ी, min_bpp);

	ret = drm_modeset_lock(&mgr->base.lock, ctx);
	अगर (ret)
		वापस ret;

	अगर (mode_rate > max_rate || mode->घड़ी > max_करोtclk ||
	    drm_dp_calc_pbn_mode(mode->घड़ी, min_bpp, false) > port->full_pbn) अणु
		*status = MODE_CLOCK_HIGH;
		वापस 0;
	पूर्ण

	अगर (mode->घड़ी < 10000) अणु
		*status = MODE_CLOCK_LOW;
		वापस 0;
	पूर्ण

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK) अणु
		*status = MODE_H_ILLEGAL;
		वापस 0;
	पूर्ण

	*status = पूर्णांकel_mode_valid_max_plane_size(dev_priv, mode, false);
	वापस 0;
पूर्ण

अटल काष्ठा drm_encoder *पूर्णांकel_mst_atomic_best_encoder(काष्ठा drm_connector *connector,
							 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *connector_state = drm_atomic_get_new_connector_state(state,
											 connector);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_connector->mst_port;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(connector_state->crtc);

	वापस &पूर्णांकel_dp->mst_encoders[crtc->pipe]->base.base;
पूर्ण

अटल पूर्णांक
पूर्णांकel_dp_mst_detect(काष्ठा drm_connector *connector,
		    काष्ठा drm_modeset_acquire_ctx *ctx, bool क्रमce)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = पूर्णांकel_connector->mst_port;

	अगर (!INTEL_DISPLAY_ENABLED(i915))
		वापस connector_status_disconnected;

	अगर (drm_connector_is_unरेजिस्टरed(connector))
		वापस connector_status_disconnected;

	वापस drm_dp_mst_detect_port(connector, ctx, &पूर्णांकel_dp->mst_mgr,
				      पूर्णांकel_connector->port);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_dp_mst_connector_helper_funcs = अणु
	.get_modes = पूर्णांकel_dp_mst_get_modes,
	.mode_valid_ctx = पूर्णांकel_dp_mst_mode_valid_ctx,
	.atomic_best_encoder = पूर्णांकel_mst_atomic_best_encoder,
	.atomic_check = पूर्णांकel_dp_mst_atomic_check,
	.detect_ctx = पूर्णांकel_dp_mst_detect,
पूर्ण;

अटल व्योम पूर्णांकel_dp_mst_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst = enc_to_mst(to_पूर्णांकel_encoder(encoder));

	drm_encoder_cleanup(encoder);
	kमुक्त(पूर्णांकel_mst);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_dp_mst_enc_funcs = अणु
	.destroy = पूर्णांकel_dp_mst_encoder_destroy,
पूर्ण;

अटल bool पूर्णांकel_dp_mst_get_hw_state(काष्ठा पूर्णांकel_connector *connector)
अणु
	अगर (पूर्णांकel_attached_encoder(connector) && connector->base.state->crtc) अणु
		क्रमागत pipe pipe;
		अगर (!पूर्णांकel_attached_encoder(connector)->get_hw_state(पूर्णांकel_attached_encoder(connector), &pipe))
			वापस false;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा drm_connector *पूर्णांकel_dp_add_mst_connector(काष्ठा drm_dp_mst_topology_mgr *mgr, काष्ठा drm_dp_mst_port *port, स्थिर अक्षर *pathprop)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = container_of(mgr, काष्ठा पूर्णांकel_dp, mst_mgr);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_device *dev = dig_port->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा drm_connector *connector;
	क्रमागत pipe pipe;
	पूर्णांक ret;

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector)
		वापस शून्य;

	पूर्णांकel_connector->get_hw_state = पूर्णांकel_dp_mst_get_hw_state;
	पूर्णांकel_connector->mst_port = पूर्णांकel_dp;
	पूर्णांकel_connector->port = port;
	drm_dp_mst_get_port_दो_स्मृति(port);

	connector = &पूर्णांकel_connector->base;
	ret = drm_connector_init(dev, connector, &पूर्णांकel_dp_mst_connector_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	अगर (ret) अणु
		पूर्णांकel_connector_मुक्त(पूर्णांकel_connector);
		वापस शून्य;
	पूर्ण

	drm_connector_helper_add(connector, &पूर्णांकel_dp_mst_connector_helper_funcs);

	क्रम_each_pipe(dev_priv, pipe) अणु
		काष्ठा drm_encoder *enc =
			&पूर्णांकel_dp->mst_encoders[pipe]->base.base;

		ret = drm_connector_attach_encoder(&पूर्णांकel_connector->base, enc);
		अगर (ret)
			जाओ err;
	पूर्ण

	drm_object_attach_property(&connector->base, dev->mode_config.path_property, 0);
	drm_object_attach_property(&connector->base, dev->mode_config.tile_property, 0);

	ret = drm_connector_set_path_property(connector, pathprop);
	अगर (ret)
		जाओ err;

	पूर्णांकel_attach_क्रमce_audio_property(connector);
	पूर्णांकel_attach_broadcast_rgb_property(connector);

	अगर (DISPLAY_VER(dev_priv) <= 12) अणु
		ret = पूर्णांकel_dp_init_hdcp(dig_port, पूर्णांकel_connector);
		अगर (ret)
			drm_dbg_kms(&dev_priv->drm, "[%s:%d] HDCP MST init failed, skipping.\n",
				    connector->name, connector->base.id);
	पूर्ण

	/*
	 * Reuse the prop from the SST connector because we're
	 * not allowed to create new props after device registration.
	 */
	connector->max_bpc_property =
		पूर्णांकel_dp->attached_connector->base.max_bpc_property;
	अगर (connector->max_bpc_property)
		drm_connector_attach_max_bpc_property(connector, 6, 12);

	वापस connector;

err:
	drm_connector_cleanup(connector);
	वापस शून्य;
पूर्ण

अटल व्योम
पूर्णांकel_dp_mst_poll_hpd_irq(काष्ठा drm_dp_mst_topology_mgr *mgr)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = container_of(mgr, काष्ठा पूर्णांकel_dp, mst_mgr);

	पूर्णांकel_hpd_trigger_irq(dp_to_dig_port(पूर्णांकel_dp));
पूर्ण

अटल स्थिर काष्ठा drm_dp_mst_topology_cbs mst_cbs = अणु
	.add_connector = पूर्णांकel_dp_add_mst_connector,
	.poll_hpd_irq = पूर्णांकel_dp_mst_poll_hpd_irq,
पूर्ण;

अटल काष्ठा पूर्णांकel_dp_mst_encoder *
पूर्णांकel_dp_create_fake_mst_encoder(काष्ठा पूर्णांकel_digital_port *dig_port, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_dp_mst_encoder *पूर्णांकel_mst;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा drm_device *dev = dig_port->base.base.dev;

	पूर्णांकel_mst = kzalloc(माप(*पूर्णांकel_mst), GFP_KERNEL);

	अगर (!पूर्णांकel_mst)
		वापस शून्य;

	पूर्णांकel_mst->pipe = pipe;
	पूर्णांकel_encoder = &पूर्णांकel_mst->base;
	पूर्णांकel_mst->primary = dig_port;

	drm_encoder_init(dev, &पूर्णांकel_encoder->base, &पूर्णांकel_dp_mst_enc_funcs,
			 DRM_MODE_ENCODER_DPMST, "DP-MST %c", pipe_name(pipe));

	पूर्णांकel_encoder->type = INTEL_OUTPUT_DP_MST;
	पूर्णांकel_encoder->घातer_करोमुख्य = dig_port->base.घातer_करोमुख्य;
	पूर्णांकel_encoder->port = dig_port->base.port;
	पूर्णांकel_encoder->cloneable = 0;
	/*
	 * This is wrong, but broken userspace uses the पूर्णांकersection
	 * of possible_crtcs of all the encoders of a given connector
	 * to figure out which crtcs can drive said connector. What
	 * should be used instead is the जोड़ of possible_crtcs.
	 * To keep such userspace functioning we must misconfigure
	 * this to make sure the पूर्णांकersection is not empty :(
	 */
	पूर्णांकel_encoder->pipe_mask = ~0;

	पूर्णांकel_encoder->compute_config = पूर्णांकel_dp_mst_compute_config;
	पूर्णांकel_encoder->compute_config_late = पूर्णांकel_dp_mst_compute_config_late;
	पूर्णांकel_encoder->disable = पूर्णांकel_mst_disable_dp;
	पूर्णांकel_encoder->post_disable = पूर्णांकel_mst_post_disable_dp;
	पूर्णांकel_encoder->update_pipe = पूर्णांकel_ddi_update_pipe;
	पूर्णांकel_encoder->pre_pll_enable = पूर्णांकel_mst_pre_pll_enable_dp;
	पूर्णांकel_encoder->pre_enable = पूर्णांकel_mst_pre_enable_dp;
	पूर्णांकel_encoder->enable = पूर्णांकel_mst_enable_dp;
	पूर्णांकel_encoder->get_hw_state = पूर्णांकel_dp_mst_enc_get_hw_state;
	पूर्णांकel_encoder->get_config = पूर्णांकel_dp_mst_enc_get_config;
	पूर्णांकel_encoder->initial_fastset_check = पूर्णांकel_dp_mst_initial_fastset_check;

	वापस पूर्णांकel_mst;

पूर्ण

अटल bool
पूर्णांकel_dp_create_fake_mst_encoders(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe)
		पूर्णांकel_dp->mst_encoders[pipe] = पूर्णांकel_dp_create_fake_mst_encoder(dig_port, pipe);
	वापस true;
पूर्ण

पूर्णांक
पूर्णांकel_dp_mst_encoder_active_links(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	वापस dig_port->dp.active_mst_links;
पूर्ण

पूर्णांक
पूर्णांकel_dp_mst_encoder_init(काष्ठा पूर्णांकel_digital_port *dig_port, पूर्णांक conn_base_id)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dig_port->base.base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;
	क्रमागत port port = dig_port->base.port;
	पूर्णांक ret;

	अगर (!HAS_DP_MST(i915) || पूर्णांकel_dp_is_edp(पूर्णांकel_dp))
		वापस 0;

	अगर (DISPLAY_VER(i915) < 12 && port == PORT_A)
		वापस 0;

	अगर (DISPLAY_VER(i915) < 11 && port == PORT_E)
		वापस 0;

	पूर्णांकel_dp->mst_mgr.cbs = &mst_cbs;

	/* create encoders */
	पूर्णांकel_dp_create_fake_mst_encoders(dig_port);
	ret = drm_dp_mst_topology_mgr_init(&पूर्णांकel_dp->mst_mgr, &i915->drm,
					   &पूर्णांकel_dp->aux, 16, 3, conn_base_id);
	अगर (ret)
		वापस ret;

	पूर्णांकel_dp->can_mst = true;

	वापस 0;
पूर्ण

व्योम
पूर्णांकel_dp_mst_encoder_cleanup(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = &dig_port->dp;

	अगर (!पूर्णांकel_dp->can_mst)
		वापस;

	drm_dp_mst_topology_mgr_destroy(&पूर्णांकel_dp->mst_mgr);
	/* encoders will get समाप्तed by normal cleanup */
पूर्ण

bool पूर्णांकel_dp_mst_is_master_trans(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस crtc_state->mst_master_transcoder == crtc_state->cpu_transcoder;
पूर्ण

bool पूर्णांकel_dp_mst_is_slave_trans(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस crtc_state->mst_master_transcoder != INVALID_TRANSCODER &&
	       crtc_state->mst_master_transcoder != crtc_state->cpu_transcoder;
पूर्ण
