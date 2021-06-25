<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 *
 */

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_vrr.h"

bool पूर्णांकel_vrr_is_capable(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp;
	स्थिर काष्ठा drm_display_info *info = &connector->display_info;
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);

	अगर (connector->connector_type != DRM_MODE_CONNECTOR_eDP &&
	    connector->connector_type != DRM_MODE_CONNECTOR_DisplayPort)
		वापस false;

	पूर्णांकel_dp = पूर्णांकel_attached_dp(to_पूर्णांकel_connector(connector));
	/*
	 * DP Sink is capable of VRR video timings अगर
	 * Ignore MSA bit is set in DPCD.
	 * EDID monitor range also should be atleast 10 क्रम reasonable
	 * Adaptive Sync or Variable Refresh Rate end user experience.
	 */
	वापस HAS_VRR(i915) &&
		drm_dp_sink_can_करो_video_without_timing_msa(पूर्णांकel_dp->dpcd) &&
		info->monitor_range.max_vfreq - info->monitor_range.min_vfreq > 10;
पूर्ण

व्योम
पूर्णांकel_vrr_check_modeset(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	पूर्णांक i;
	काष्ठा पूर्णांकel_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (new_crtc_state->uapi.vrr_enabled !=
		    old_crtc_state->uapi.vrr_enabled)
			new_crtc_state->uapi.mode_changed = true;
	पूर्ण
पूर्ण

/*
 * Without VRR रेजिस्टरs get latched at:
 *  vblank_start
 *
 * With VRR the earliest रेजिस्टरs can get latched is:
 *  पूर्णांकel_vrr_vmin_vblank_start(), which अगर we want to मुख्यtain
 *  the correct min vtotal is >=vblank_start+1
 *
 * The latest poपूर्णांक रेजिस्टरs can get latched is the vmax decision boundary:
 *  पूर्णांकel_vrr_vmax_vblank_start()
 *
 * Between those two poपूर्णांकs the vblank निकास starts (and hence रेजिस्टरs get
 * latched) ASAP after a push is sent.
 *
 * framestart_delay is programmable 0-3.
 */
अटल पूर्णांक पूर्णांकel_vrr_vblank_निकास_length(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);

	/* The hw imposes the extra scanline beक्रमe frame start */
	वापस crtc_state->vrr.pipeline_full + i915->framestart_delay + 1;
पूर्ण

पूर्णांक पूर्णांकel_vrr_vmin_vblank_start(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	/* Min vblank actually determined by flipline that is always >=vmin+1 */
	वापस crtc_state->vrr.vmin + 1 - पूर्णांकel_vrr_vblank_निकास_length(crtc_state);
पूर्ण

पूर्णांक पूर्णांकel_vrr_vmax_vblank_start(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस crtc_state->vrr.vmax - पूर्णांकel_vrr_vblank_निकास_length(crtc_state);
पूर्ण

व्योम
पूर्णांकel_vrr_compute_config(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_connector *connector =
		to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->hw.adjusted_mode;
	स्थिर काष्ठा drm_display_info *info = &connector->base.display_info;
	पूर्णांक vmin, vmax;

	अगर (!पूर्णांकel_vrr_is_capable(&connector->base))
		वापस;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस;

	अगर (!crtc_state->uapi.vrr_enabled)
		वापस;

	vmin = DIV_ROUND_UP(adjusted_mode->crtc_घड़ी * 1000,
			    adjusted_mode->crtc_htotal * info->monitor_range.max_vfreq);
	vmax = adjusted_mode->crtc_घड़ी * 1000 /
		(adjusted_mode->crtc_htotal * info->monitor_range.min_vfreq);

	vmin = max_t(पूर्णांक, vmin, adjusted_mode->crtc_vtotal);
	vmax = max_t(पूर्णांक, vmax, adjusted_mode->crtc_vtotal);

	अगर (vmin >= vmax)
		वापस;

	/*
	 * flipline determines the min vblank length the hardware will
	 * generate, and flipline>=vmin+1, hence we reduce vmin by one
	 * to make sure we can get the actual min vblank length.
	 */
	crtc_state->vrr.vmin = vmin - 1;
	crtc_state->vrr.vmax = vmax;
	crtc_state->vrr.enable = true;

	crtc_state->vrr.flipline = crtc_state->vrr.vmin + 1;

	/*
	 * FIXME: s/4/framestart_delay+1/ to get consistent
	 * earliest/latest poपूर्णांकs क्रम रेजिस्टर latching regardless
	 * of the framestart_delay used?
	 *
	 * FIXME: this really needs the extra scanline to provide consistent
	 * behaviour क्रम all framestart_delay values. Otherwise with
	 * framestart_delay==3 we will end up extending the min vblank by
	 * one extra line.
	 */
	crtc_state->vrr.pipeline_full =
		min(255, crtc_state->vrr.vmin - adjusted_mode->crtc_vdisplay - 4 - 1);

	crtc_state->mode_flags |= I915_MODE_FLAG_VRR;
पूर्ण

व्योम पूर्णांकel_vrr_enable(काष्ठा पूर्णांकel_encoder *encoder,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 trans_vrr_ctl;

	अगर (!crtc_state->vrr.enable)
		वापस;

	trans_vrr_ctl = VRR_CTL_VRR_ENABLE |
		VRR_CTL_IGN_MAX_SHIFT | VRR_CTL_FLIP_LINE_EN |
		VRR_CTL_PIPELINE_FULL(crtc_state->vrr.pipeline_full) |
		VRR_CTL_PIPELINE_FULL_OVERRIDE;

	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_VRR_VMIN(cpu_transcoder), crtc_state->vrr.vmin - 1);
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_VRR_VMAX(cpu_transcoder), crtc_state->vrr.vmax - 1);
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_VRR_CTL(cpu_transcoder), trans_vrr_ctl);
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_VRR_FLIPLINE(cpu_transcoder), crtc_state->vrr.flipline - 1);
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_PUSH(cpu_transcoder), TRANS_PUSH_EN);
पूर्ण

व्योम पूर्णांकel_vrr_send_push(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	अगर (!crtc_state->vrr.enable)
		वापस;

	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_PUSH(cpu_transcoder),
		       TRANS_PUSH_EN | TRANS_PUSH_SEND);
पूर्ण

व्योम पूर्णांकel_vrr_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = old_crtc_state->cpu_transcoder;

	अगर (!old_crtc_state->vrr.enable)
		वापस;

	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_VRR_CTL(cpu_transcoder), 0);
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_PUSH(cpu_transcoder), 0);
पूर्ण

व्योम पूर्णांकel_vrr_get_config(काष्ठा पूर्णांकel_crtc *crtc,
			  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 trans_vrr_ctl;

	trans_vrr_ctl = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_VRR_CTL(cpu_transcoder));
	crtc_state->vrr.enable = trans_vrr_ctl & VRR_CTL_VRR_ENABLE;
	अगर (!crtc_state->vrr.enable)
		वापस;

	अगर (trans_vrr_ctl & VRR_CTL_PIPELINE_FULL_OVERRIDE)
		crtc_state->vrr.pipeline_full = REG_FIELD_GET(VRR_CTL_PIPELINE_FULL_MASK, trans_vrr_ctl);
	अगर (trans_vrr_ctl & VRR_CTL_FLIP_LINE_EN)
		crtc_state->vrr.flipline = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_VRR_FLIPLINE(cpu_transcoder)) + 1;
	crtc_state->vrr.vmax = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_VRR_VMAX(cpu_transcoder)) + 1;
	crtc_state->vrr.vmin = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_VRR_VMIN(cpu_transcoder)) + 1;

	crtc_state->mode_flags |= I915_MODE_FLAG_VRR;
पूर्ण
