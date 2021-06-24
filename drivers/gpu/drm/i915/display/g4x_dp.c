<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 *
 * DisplayPort support क्रम G4x,ILK,SNB,IVB,VLV,CHV (HSW+ handled by the DDI code).
 */

#समावेश "g4x_dp.h"
#समावेश "intel_audio.h"
#समावेश "intel_connector.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp.h"
#समावेश "intel_dp_link_training.h"
#समावेश "intel_dpio_phy.h"
#समावेश "intel_fifo_underrun.h"
#समावेश "intel_hdmi.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_panel.h"
#समावेश "intel_pps.h"
#समावेश "intel_sideband.h"

काष्ठा dp_link_dpll अणु
	पूर्णांक घड़ी;
	काष्ठा dpll dpll;
पूर्ण;

अटल स्थिर काष्ठा dp_link_dpll g4x_dpll[] = अणु
	अणु 162000,
		अणु .p1 = 2, .p2 = 10, .n = 2, .m1 = 23, .m2 = 8 पूर्ण पूर्ण,
	अणु 270000,
		अणु .p1 = 1, .p2 = 10, .n = 1, .m1 = 14, .m2 = 2 पूर्ण पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dp_link_dpll pch_dpll[] = अणु
	अणु 162000,
		अणु .p1 = 2, .p2 = 10, .n = 1, .m1 = 12, .m2 = 9 पूर्ण पूर्ण,
	अणु 270000,
		अणु .p1 = 1, .p2 = 10, .n = 2, .m1 = 14, .m2 = 8 पूर्ण पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dp_link_dpll vlv_dpll[] = अणु
	अणु 162000,
		अणु .p1 = 3, .p2 = 2, .n = 5, .m1 = 3, .m2 = 81 पूर्ण पूर्ण,
	अणु 270000,
		अणु .p1 = 2, .p2 = 2, .n = 1, .m1 = 2, .m2 = 27 पूर्ण पूर्ण
पूर्ण;

/*
 * CHV supports eDP 1.4 that have  more link rates.
 * Below only provides the fixed rate but exclude variable rate.
 */
अटल स्थिर काष्ठा dp_link_dpll chv_dpll[] = अणु
	/*
	 * CHV requires to program fractional भागision क्रम m2.
	 * m2 is stored in fixed poपूर्णांक क्रमmat using क्रमmula below
	 * (m2_पूर्णांक << 22) | m2_fraction
	 */
	अणु 162000,	/* m2_पूर्णांक = 32, m2_fraction = 1677722 */
		अणु .p1 = 4, .p2 = 2, .n = 1, .m1 = 2, .m2 = 0x819999a पूर्ण पूर्ण,
	अणु 270000,	/* m2_पूर्णांक = 27, m2_fraction = 0 */
		अणु .p1 = 4, .p2 = 1, .n = 1, .m1 = 2, .m2 = 0x6c00000 पूर्ण पूर्ण,
पूर्ण;

स्थिर काष्ठा dpll *vlv_get_dpll(काष्ठा drm_i915_निजी *i915)
अणु
	वापस IS_CHERRYVIEW(i915) ? &chv_dpll[0].dpll : &vlv_dpll[0].dpll;
पूर्ण

व्योम g4x_dp_set_घड़ी(काष्ठा पूर्णांकel_encoder *encoder,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	स्थिर काष्ठा dp_link_dpll *भागisor = शून्य;
	पूर्णांक i, count = 0;

	अगर (IS_G4X(dev_priv)) अणु
		भागisor = g4x_dpll;
		count = ARRAY_SIZE(g4x_dpll);
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		भागisor = pch_dpll;
		count = ARRAY_SIZE(pch_dpll);
	पूर्ण अन्यथा अगर (IS_CHERRYVIEW(dev_priv)) अणु
		भागisor = chv_dpll;
		count = ARRAY_SIZE(chv_dpll);
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv)) अणु
		भागisor = vlv_dpll;
		count = ARRAY_SIZE(vlv_dpll);
	पूर्ण

	अगर (भागisor && count) अणु
		क्रम (i = 0; i < count; i++) अणु
			अगर (pipe_config->port_घड़ी == भागisor[i].घड़ी) अणु
				pipe_config->dpll = भागisor[i].dpll;
				pipe_config->घड़ी_set = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dp_prepare(काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	क्रमागत port port = encoder->port;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;

	पूर्णांकel_dp_set_link_params(पूर्णांकel_dp,
				 pipe_config->port_घड़ी,
				 pipe_config->lane_count);

	/*
	 * There are four kinds of DP रेजिस्टरs:
	 * IBX PCH
	 * SNB CPU
	 * IVB CPU
	 * CPT PCH
	 *
	 * IBX PCH and CPU are the same क्रम almost everything,
	 * except that the CPU DP PLL is configured in this
	 * रेजिस्टर
	 *
	 * CPT PCH is quite dअगरferent, having many bits moved
	 * to the TRANS_DP_CTL रेजिस्टर instead. That
	 * configuration happens (oddly) in ilk_pch_enable
	 */

	/* Preserve the BIOS-computed detected bit. This is
	 * supposed to be पढ़ो-only.
	 */
	पूर्णांकel_dp->DP = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg) & DP_DETECTED;

	/* Handle DP bits in common between all three रेजिस्टर क्रमmats */
	पूर्णांकel_dp->DP |= DP_VOLTAGE_0_4 | DP_PRE_EMPHASIS_0;
	पूर्णांकel_dp->DP |= DP_PORT_WIDTH(pipe_config->lane_count);

	/* Split out the IBX/CPU vs CPT settings */

	अगर (IS_IVYBRIDGE(dev_priv) && port == PORT_A) अणु
		अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
			पूर्णांकel_dp->DP |= DP_SYNC_HS_HIGH;
		अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
			पूर्णांकel_dp->DP |= DP_SYNC_VS_HIGH;
		पूर्णांकel_dp->DP |= DP_LINK_TRAIN_OFF_CPT;

		अगर (drm_dp_enhanced_frame_cap(पूर्णांकel_dp->dpcd))
			पूर्णांकel_dp->DP |= DP_ENHANCED_FRAMING;

		पूर्णांकel_dp->DP |= DP_PIPE_SEL_IVB(crtc->pipe);
	पूर्ण अन्यथा अगर (HAS_PCH_CPT(dev_priv) && port != PORT_A) अणु
		u32 trans_dp;

		पूर्णांकel_dp->DP |= DP_LINK_TRAIN_OFF_CPT;

		trans_dp = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DP_CTL(crtc->pipe));
		अगर (drm_dp_enhanced_frame_cap(पूर्णांकel_dp->dpcd))
			trans_dp |= TRANS_DP_ENH_FRAMING;
		अन्यथा
			trans_dp &= ~TRANS_DP_ENH_FRAMING;
		पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DP_CTL(crtc->pipe), trans_dp);
	पूर्ण अन्यथा अणु
		अगर (IS_G4X(dev_priv) && pipe_config->limited_color_range)
			पूर्णांकel_dp->DP |= DP_COLOR_RANGE_16_235;

		अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
			पूर्णांकel_dp->DP |= DP_SYNC_HS_HIGH;
		अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
			पूर्णांकel_dp->DP |= DP_SYNC_VS_HIGH;
		पूर्णांकel_dp->DP |= DP_LINK_TRAIN_OFF;

		अगर (drm_dp_enhanced_frame_cap(पूर्णांकel_dp->dpcd))
			पूर्णांकel_dp->DP |= DP_ENHANCED_FRAMING;

		अगर (IS_CHERRYVIEW(dev_priv))
			पूर्णांकel_dp->DP |= DP_PIPE_SEL_CHV(crtc->pipe);
		अन्यथा
			पूर्णांकel_dp->DP |= DP_PIPE_SEL(crtc->pipe);
	पूर्ण
पूर्ण

अटल व्योम निश्चित_dp_port(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp, bool state)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	bool cur_state = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg) & DP_PORT_EN;

	I915_STATE_WARN(cur_state != state,
			"[ENCODER:%d:%s] state assertion failure (expected %s, current %s)\n",
			dig_port->base.base.base.id, dig_port->base.base.name,
			onoff(state), onoff(cur_state));
पूर्ण
#घोषणा निश्चित_dp_port_disabled(d) निश्चित_dp_port((d), false)

अटल व्योम निश्चित_edp_pll(काष्ठा drm_i915_निजी *dev_priv, bool state)
अणु
	bool cur_state = पूर्णांकel_de_पढ़ो(dev_priv, DP_A) & DP_PLL_ENABLE;

	I915_STATE_WARN(cur_state != state,
			"eDP PLL state assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
पूर्ण
#घोषणा निश्चित_edp_pll_enabled(d) निश्चित_edp_pll((d), true)
#घोषणा निश्चित_edp_pll_disabled(d) निश्चित_edp_pll((d), false)

अटल व्योम ilk_edp_pll_on(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	निश्चित_pipe_disabled(dev_priv, pipe_config->cpu_transcoder);
	निश्चित_dp_port_disabled(पूर्णांकel_dp);
	निश्चित_edp_pll_disabled(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "enabling eDP PLL for clock %d\n",
		    pipe_config->port_घड़ी);

	पूर्णांकel_dp->DP &= ~DP_PLL_FREQ_MASK;

	अगर (pipe_config->port_घड़ी == 162000)
		पूर्णांकel_dp->DP |= DP_PLL_FREQ_162MHZ;
	अन्यथा
		पूर्णांकel_dp->DP |= DP_PLL_FREQ_270MHZ;

	पूर्णांकel_de_ग_लिखो(dev_priv, DP_A, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DP_A);
	udelay(500);

	/*
	 * [DevILK] Work around required when enabling DP PLL
	 * जबतक a pipe is enabled going to FDI:
	 * 1. Wait क्रम the start of vertical blank on the enabled pipe going to FDI
	 * 2. Program DP PLL enable
	 */
	अगर (IS_IRONLAKE(dev_priv))
		पूर्णांकel_रुको_क्रम_vblank_अगर_active(dev_priv, !crtc->pipe);

	पूर्णांकel_dp->DP |= DP_PLL_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, DP_A, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DP_A);
	udelay(200);
पूर्ण

अटल व्योम ilk_edp_pll_off(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	निश्चित_pipe_disabled(dev_priv, old_crtc_state->cpu_transcoder);
	निश्चित_dp_port_disabled(पूर्णांकel_dp);
	निश्चित_edp_pll_enabled(dev_priv);

	drm_dbg_kms(&dev_priv->drm, "disabling eDP PLL\n");

	पूर्णांकel_dp->DP &= ~DP_PLL_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, DP_A, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DP_A);
	udelay(200);
पूर्ण

अटल bool cpt_dp_port_selected(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत port port, क्रमागत pipe *pipe)
अणु
	क्रमागत pipe p;

	क्रम_each_pipe(dev_priv, p) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DP_CTL(p));

		अगर ((val & TRANS_DP_PORT_SEL_MASK) == TRANS_DP_PORT_SEL(port)) अणु
			*pipe = p;
			वापस true;
		पूर्ण
	पूर्ण

	drm_dbg_kms(&dev_priv->drm, "No pipe for DP port %c found\n",
		    port_name(port));

	/* must initialize pipe to something क्रम the निश्चितs */
	*pipe = PIPE_A;

	वापस false;
पूर्ण

bool g4x_dp_port_enabled(काष्ठा drm_i915_निजी *dev_priv,
			 i915_reg_t dp_reg, क्रमागत port port,
			 क्रमागत pipe *pipe)
अणु
	bool ret;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, dp_reg);

	ret = val & DP_PORT_EN;

	/* निश्चितs want to know the pipe even अगर the port is disabled */
	अगर (IS_IVYBRIDGE(dev_priv) && port == PORT_A)
		*pipe = (val & DP_PIPE_SEL_MASK_IVB) >> DP_PIPE_SEL_SHIFT_IVB;
	अन्यथा अगर (HAS_PCH_CPT(dev_priv) && port != PORT_A)
		ret &= cpt_dp_port_selected(dev_priv, port, pipe);
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		*pipe = (val & DP_PIPE_SEL_MASK_CHV) >> DP_PIPE_SEL_SHIFT_CHV;
	अन्यथा
		*pipe = (val & DP_PIPE_SEL_MASK) >> DP_PIPE_SEL_SHIFT;

	वापस ret;
पूर्ण

अटल bool पूर्णांकel_dp_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				  क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     encoder->घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret = g4x_dp_port_enabled(dev_priv, पूर्णांकel_dp->output_reg,
				  encoder->port, pipe);

	पूर्णांकel_display_घातer_put(dev_priv, encoder->घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_dp_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	u32 पंचांगp, flags = 0;
	क्रमागत port port = encoder->port;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);

	अगर (encoder->type == INTEL_OUTPUT_EDP)
		pipe_config->output_types |= BIT(INTEL_OUTPUT_EDP);
	अन्यथा
		pipe_config->output_types |= BIT(INTEL_OUTPUT_DP);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

	pipe_config->has_audio = पंचांगp & DP_AUDIO_OUTPUT_ENABLE && port != PORT_A;

	अगर (HAS_PCH_CPT(dev_priv) && port != PORT_A) अणु
		u32 trans_dp = पूर्णांकel_de_पढ़ो(dev_priv,
					     TRANS_DP_CTL(crtc->pipe));

		अगर (trans_dp & TRANS_DP_HSYNC_ACTIVE_HIGH)
			flags |= DRM_MODE_FLAG_PHSYNC;
		अन्यथा
			flags |= DRM_MODE_FLAG_NHSYNC;

		अगर (trans_dp & TRANS_DP_VSYNC_ACTIVE_HIGH)
			flags |= DRM_MODE_FLAG_PVSYNC;
		अन्यथा
			flags |= DRM_MODE_FLAG_NVSYNC;
	पूर्ण अन्यथा अणु
		अगर (पंचांगp & DP_SYNC_HS_HIGH)
			flags |= DRM_MODE_FLAG_PHSYNC;
		अन्यथा
			flags |= DRM_MODE_FLAG_NHSYNC;

		अगर (पंचांगp & DP_SYNC_VS_HIGH)
			flags |= DRM_MODE_FLAG_PVSYNC;
		अन्यथा
			flags |= DRM_MODE_FLAG_NVSYNC;
	पूर्ण

	pipe_config->hw.adjusted_mode.flags |= flags;

	अगर (IS_G4X(dev_priv) && पंचांगp & DP_COLOR_RANGE_16_235)
		pipe_config->limited_color_range = true;

	pipe_config->lane_count =
		((पंचांगp & DP_PORT_WIDTH_MASK) >> DP_PORT_WIDTH_SHIFT) + 1;

	पूर्णांकel_dp_get_m_n(crtc, pipe_config);

	अगर (port == PORT_A) अणु
		अगर ((पूर्णांकel_de_पढ़ो(dev_priv, DP_A) & DP_PLL_FREQ_MASK) == DP_PLL_FREQ_162MHZ)
			pipe_config->port_घड़ी = 162000;
		अन्यथा
			pipe_config->port_घड़ी = 270000;
	पूर्ण

	pipe_config->hw.adjusted_mode.crtc_घड़ी =
		पूर्णांकel_करोtघड़ी_calculate(pipe_config->port_घड़ी,
					 &pipe_config->dp_m_n);

	अगर (पूर्णांकel_dp_is_edp(पूर्णांकel_dp) && dev_priv->vbt.edp.bpp &&
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
पूर्ण

अटल व्योम
पूर्णांकel_dp_link_करोwn(काष्ठा पूर्णांकel_encoder *encoder,
		   स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	क्रमागत port port = encoder->port;
	u32 DP = पूर्णांकel_dp->DP;

	अगर (drm_WARN_ON(&dev_priv->drm,
			(पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg) &
			 DP_PORT_EN) == 0))
		वापस;

	drm_dbg_kms(&dev_priv->drm, "\n");

	अगर ((IS_IVYBRIDGE(dev_priv) && port == PORT_A) ||
	    (HAS_PCH_CPT(dev_priv) && port != PORT_A)) अणु
		DP &= ~DP_LINK_TRAIN_MASK_CPT;
		DP |= DP_LINK_TRAIN_PAT_IDLE_CPT;
	पूर्ण अन्यथा अणु
		DP &= ~DP_LINK_TRAIN_MASK;
		DP |= DP_LINK_TRAIN_PAT_IDLE;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

	DP &= ~(DP_PORT_EN | DP_AUDIO_OUTPUT_ENABLE);
	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

	/*
	 * HW workaround क्रम IBX, we need to move the port
	 * to transcoder A after disabling it to allow the
	 * matching HDMI port to be enabled on transcoder A.
	 */
	अगर (HAS_PCH_IBX(dev_priv) && crtc->pipe == PIPE_B && port != PORT_A) अणु
		/*
		 * We get CPU/PCH FIFO underruns on the other pipe when
		 * करोing the workaround. Sweep them under the rug.
		 */
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, PIPE_A, false);
		पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, false);

		/* always enable with pattern 1 (as per spec) */
		DP &= ~(DP_PIPE_SEL_MASK | DP_LINK_TRAIN_MASK);
		DP |= DP_PORT_EN | DP_PIPE_SEL(PIPE_A) |
			DP_LINK_TRAIN_PAT_1;
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, DP);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

		DP &= ~DP_PORT_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, DP);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

		पूर्णांकel_रुको_क्रम_vblank_अगर_active(dev_priv, PIPE_A);
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, PIPE_A, true);
		पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, true);
	पूर्ण

	msleep(पूर्णांकel_dp->pps.panel_घातer_करोwn_delay);

	पूर्णांकel_dp->DP = DP;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		पूर्णांकel_wakeref_t wakeref;

		with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref)
			पूर्णांकel_dp->pps.active_pipe = INVALID_PIPE;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			     स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);

	पूर्णांकel_dp->link_trained = false;

	अगर (old_crtc_state->has_audio)
		पूर्णांकel_audio_codec_disable(encoder,
					  old_crtc_state, old_conn_state);

	/*
	 * Make sure the panel is off beक्रमe trying to change the mode.
	 * But also ensure that we have vdd जबतक we चयन off the panel.
	 */
	पूर्णांकel_pps_vdd_on(पूर्णांकel_dp);
	पूर्णांकel_edp_backlight_off(old_conn_state);
	पूर्णांकel_dp_set_घातer(पूर्णांकel_dp, DP_SET_POWER_D3);
	पूर्णांकel_pps_off(पूर्णांकel_dp);
पूर्ण

अटल व्योम g4x_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			   स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_disable_dp(state, encoder, old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम vlv_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			   स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_disable_dp(state, encoder, old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम g4x_post_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	क्रमागत port port = encoder->port;

	/*
	 * Bspec करोes not list a specअगरic disable sequence क्रम g4x DP.
	 * Follow the ilk+ sequence (disable pipe beक्रमe the port) क्रम
	 * g4x DP as it करोes not suffer from underruns like the normal
	 * g4x modeset sequence (disable pipe after the port).
	 */
	पूर्णांकel_dp_link_करोwn(encoder, old_crtc_state);

	/* Only ilk+ has port A */
	अगर (port == PORT_A)
		ilk_edp_pll_off(पूर्णांकel_dp, old_crtc_state);
पूर्ण

अटल व्योम vlv_post_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_dp_link_करोwn(encoder, old_crtc_state);
पूर्ण

अटल व्योम chv_post_disable_dp(काष्ठा पूर्णांकel_atomic_state *state,
				काष्ठा पूर्णांकel_encoder *encoder,
				स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	पूर्णांकel_dp_link_करोwn(encoder, old_crtc_state);

	vlv_dpio_get(dev_priv);

	/* Assert data lane reset */
	chv_data_lane_soft_reset(encoder, old_crtc_state, true);

	vlv_dpio_put(dev_priv);
पूर्ण

अटल व्योम
cpt_set_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		   u8 dp_train_pat)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 *DP = &पूर्णांकel_dp->DP;

	*DP &= ~DP_LINK_TRAIN_MASK_CPT;

	चयन (पूर्णांकel_dp_training_pattern_symbol(dp_train_pat)) अणु
	हाल DP_TRAINING_PATTERN_DISABLE:
		*DP |= DP_LINK_TRAIN_OFF_CPT;
		अवरोध;
	हाल DP_TRAINING_PATTERN_1:
		*DP |= DP_LINK_TRAIN_PAT_1_CPT;
		अवरोध;
	हाल DP_TRAINING_PATTERN_2:
		*DP |= DP_LINK_TRAIN_PAT_2_CPT;
		अवरोध;
	शेष:
		MISSING_CASE(पूर्णांकel_dp_training_pattern_symbol(dp_train_pat));
		वापस;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);
पूर्ण

अटल व्योम
g4x_set_link_train(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		   u8 dp_train_pat)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u32 *DP = &पूर्णांकel_dp->DP;

	*DP &= ~DP_LINK_TRAIN_MASK;

	चयन (पूर्णांकel_dp_training_pattern_symbol(dp_train_pat)) अणु
	हाल DP_TRAINING_PATTERN_DISABLE:
		*DP |= DP_LINK_TRAIN_OFF;
		अवरोध;
	हाल DP_TRAINING_PATTERN_1:
		*DP |= DP_LINK_TRAIN_PAT_1;
		अवरोध;
	हाल DP_TRAINING_PATTERN_2:
		*DP |= DP_LINK_TRAIN_PAT_2;
		अवरोध;
	शेष:
		MISSING_CASE(पूर्णांकel_dp_training_pattern_symbol(dp_train_pat));
		वापस;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);
पूर्ण

अटल व्योम पूर्णांकel_dp_enable_port(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);

	/* enable with pattern 1 (as per spec) */

	पूर्णांकel_dp_program_link_training_pattern(पूर्णांकel_dp, crtc_state,
					       DP_TRAINING_PATTERN_1);

	/*
	 * Magic क्रम VLV/CHV. We _must_ first set up the रेजिस्टर
	 * without actually enabling the port, and then करो another
	 * ग_लिखो to enable the port. Otherwise link training will
	 * fail when the घातer sequencer is freshly used क्रम this port.
	 */
	पूर्णांकel_dp->DP |= DP_PORT_EN;
	अगर (crtc_state->has_audio)
		पूर्णांकel_dp->DP |= DP_AUDIO_OUTPUT_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);
पूर्ण

अटल व्योम पूर्णांकel_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			    स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	u32 dp_reg = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांकel_wakeref_t wakeref;

	अगर (drm_WARN_ON(&dev_priv->drm, dp_reg & DP_PORT_EN))
		वापस;

	with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref) अणु
		अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
			vlv_pps_init(encoder, pipe_config);

		पूर्णांकel_dp_enable_port(पूर्णांकel_dp, pipe_config);

		पूर्णांकel_pps_vdd_on_unlocked(पूर्णांकel_dp);
		पूर्णांकel_pps_on_unlocked(पूर्णांकel_dp);
		पूर्णांकel_pps_vdd_off_unlocked(पूर्णांकel_dp, true);
	पूर्ण

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		अचिन्हित पूर्णांक lane_mask = 0x0;

		अगर (IS_CHERRYVIEW(dev_priv))
			lane_mask = पूर्णांकel_dp_unused_lane_mask(pipe_config->lane_count);

		vlv_रुको_port_पढ़ोy(dev_priv, dp_to_dig_port(पूर्णांकel_dp),
				    lane_mask);
	पूर्ण

	पूर्णांकel_dp_set_घातer(पूर्णांकel_dp, DP_SET_POWER_D0);
	पूर्णांकel_dp_configure_protocol_converter(पूर्णांकel_dp, pipe_config);
	पूर्णांकel_dp_check_frl_training(पूर्णांकel_dp);
	पूर्णांकel_dp_pcon_dsc_configure(पूर्णांकel_dp, pipe_config);
	पूर्णांकel_dp_start_link_train(पूर्णांकel_dp, pipe_config);
	पूर्णांकel_dp_stop_link_train(पूर्णांकel_dp, pipe_config);

	अगर (pipe_config->has_audio) अणु
		drm_dbg(&dev_priv->drm, "Enabling DP audio on pipe %c\n",
			pipe_name(pipe));
		पूर्णांकel_audio_codec_enable(encoder, pipe_config, conn_state);
	पूर्ण
पूर्ण

अटल व्योम g4x_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_encoder *encoder,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांकel_enable_dp(state, encoder, pipe_config, conn_state);
	पूर्णांकel_edp_backlight_on(pipe_config, conn_state);
पूर्ण

अटल व्योम vlv_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_encoder *encoder,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांकel_edp_backlight_on(pipe_config, conn_state);
पूर्ण

अटल व्योम g4x_pre_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	क्रमागत port port = encoder->port;

	पूर्णांकel_dp_prepare(encoder, pipe_config);

	/* Only ilk+ has port A */
	अगर (port == PORT_A)
		ilk_edp_pll_on(पूर्णांकel_dp, pipe_config);
पूर्ण

अटल व्योम vlv_pre_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	vlv_phy_pre_encoder_enable(encoder, pipe_config);

	पूर्णांकel_enable_dp(state, encoder, pipe_config, conn_state);
पूर्ण

अटल व्योम vlv_dp_pre_pll_enable(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांकel_dp_prepare(encoder, pipe_config);

	vlv_phy_pre_pll_enable(encoder, pipe_config);
पूर्ण

अटल व्योम chv_pre_enable_dp(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	chv_phy_pre_encoder_enable(encoder, pipe_config);

	पूर्णांकel_enable_dp(state, encoder, pipe_config, conn_state);

	/* Second common lane will stay alive on its own now */
	chv_phy_release_cl2_override(encoder);
पूर्ण

अटल व्योम chv_dp_pre_pll_enable(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांकel_dp_prepare(encoder, pipe_config);

	chv_phy_pre_pll_enable(encoder, pipe_config);
पूर्ण

अटल व्योम chv_dp_post_pll_disable(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				    स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	chv_phy_post_pll_disable(encoder, old_crtc_state);
पूर्ण

अटल u8 पूर्णांकel_dp_voltage_max_2(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस DP_TRAIN_VOLTAGE_SWING_LEVEL_2;
पूर्ण

अटल u8 पूर्णांकel_dp_voltage_max_3(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस DP_TRAIN_VOLTAGE_SWING_LEVEL_3;
पूर्ण

अटल u8 पूर्णांकel_dp_preemph_max_2(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस DP_TRAIN_PRE_EMPH_LEVEL_2;
पूर्ण

अटल u8 पूर्णांकel_dp_preemph_max_3(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	वापस DP_TRAIN_PRE_EMPH_LEVEL_3;
पूर्ण

अटल व्योम vlv_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	अचिन्हित दीर्घ demph_reg_value, preemph_reg_value,
		uniqtranscale_reg_value;
	u8 train_set = पूर्णांकel_dp->train_set[0];

	चयन (train_set & DP_TRAIN_PRE_EMPHASIS_MASK) अणु
	हाल DP_TRAIN_PRE_EMPH_LEVEL_0:
		preemph_reg_value = 0x0004000;
		चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			demph_reg_value = 0x2B405555;
			uniqtranscale_reg_value = 0x552AB83A;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			demph_reg_value = 0x2B404040;
			uniqtranscale_reg_value = 0x5548B83A;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
			demph_reg_value = 0x2B245555;
			uniqtranscale_reg_value = 0x5560B83A;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_3:
			demph_reg_value = 0x2B405555;
			uniqtranscale_reg_value = 0x5598DA3A;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_1:
		preemph_reg_value = 0x0002000;
		चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			demph_reg_value = 0x2B404040;
			uniqtranscale_reg_value = 0x5552B83A;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			demph_reg_value = 0x2B404848;
			uniqtranscale_reg_value = 0x5580B83A;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
			demph_reg_value = 0x2B404040;
			uniqtranscale_reg_value = 0x55ADDA3A;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_2:
		preemph_reg_value = 0x0000000;
		चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			demph_reg_value = 0x2B305555;
			uniqtranscale_reg_value = 0x5570B83A;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			demph_reg_value = 0x2B2B4040;
			uniqtranscale_reg_value = 0x55ADDA3A;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_3:
		preemph_reg_value = 0x0006000;
		चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			demph_reg_value = 0x1B405555;
			uniqtranscale_reg_value = 0x55ADDA3A;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	vlv_set_phy_संकेत_level(encoder, crtc_state,
				 demph_reg_value, preemph_reg_value,
				 uniqtranscale_reg_value, 0);
पूर्ण

अटल व्योम chv_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	u32 deemph_reg_value, margin_reg_value;
	bool uniq_trans_scale = false;
	u8 train_set = पूर्णांकel_dp->train_set[0];

	चयन (train_set & DP_TRAIN_PRE_EMPHASIS_MASK) अणु
	हाल DP_TRAIN_PRE_EMPH_LEVEL_0:
		चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			deemph_reg_value = 128;
			margin_reg_value = 52;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			deemph_reg_value = 128;
			margin_reg_value = 77;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
			deemph_reg_value = 128;
			margin_reg_value = 102;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_3:
			deemph_reg_value = 128;
			margin_reg_value = 154;
			uniq_trans_scale = true;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_1:
		चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			deemph_reg_value = 85;
			margin_reg_value = 78;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			deemph_reg_value = 85;
			margin_reg_value = 116;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
			deemph_reg_value = 85;
			margin_reg_value = 154;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_2:
		चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			deemph_reg_value = 64;
			margin_reg_value = 104;
			अवरोध;
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			deemph_reg_value = 64;
			margin_reg_value = 154;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_3:
		चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
		हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			deemph_reg_value = 43;
			margin_reg_value = 154;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	chv_set_phy_संकेत_level(encoder, crtc_state,
				 deemph_reg_value, margin_reg_value,
				 uniq_trans_scale);
पूर्ण

अटल u32 g4x_संकेत_levels(u8 train_set)
अणु
	u32 संकेत_levels = 0;

	चयन (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) अणु
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
	शेष:
		संकेत_levels |= DP_VOLTAGE_0_4;
		अवरोध;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
		संकेत_levels |= DP_VOLTAGE_0_6;
		अवरोध;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
		संकेत_levels |= DP_VOLTAGE_0_8;
		अवरोध;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_3:
		संकेत_levels |= DP_VOLTAGE_1_2;
		अवरोध;
	पूर्ण
	चयन (train_set & DP_TRAIN_PRE_EMPHASIS_MASK) अणु
	हाल DP_TRAIN_PRE_EMPH_LEVEL_0:
	शेष:
		संकेत_levels |= DP_PRE_EMPHASIS_0;
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_1:
		संकेत_levels |= DP_PRE_EMPHASIS_3_5;
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_2:
		संकेत_levels |= DP_PRE_EMPHASIS_6;
		अवरोध;
	हाल DP_TRAIN_PRE_EMPH_LEVEL_3:
		संकेत_levels |= DP_PRE_EMPHASIS_9_5;
		अवरोध;
	पूर्ण
	वापस संकेत_levels;
पूर्ण

अटल व्योम
g4x_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u8 train_set = पूर्णांकel_dp->train_set[0];
	u32 संकेत_levels;

	संकेत_levels = g4x_संकेत_levels(train_set);

	drm_dbg_kms(&dev_priv->drm, "Using signal levels %08x\n",
		    संकेत_levels);

	पूर्णांकel_dp->DP &= ~(DP_VOLTAGE_MASK | DP_PRE_EMPHASIS_MASK);
	पूर्णांकel_dp->DP |= संकेत_levels;

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);
पूर्ण

/* SNB CPU eDP voltage swing and pre-emphasis control */
अटल u32 snb_cpu_edp_संकेत_levels(u8 train_set)
अणु
	u8 संकेत_levels = train_set & (DP_TRAIN_VOLTAGE_SWING_MASK |
					DP_TRAIN_PRE_EMPHASIS_MASK);

	चयन (संकेत_levels) अणु
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_0:
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_0:
		वापस EDP_LINK_TRAIN_400_600MV_0DB_SNB_B;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_1:
		वापस EDP_LINK_TRAIN_400MV_3_5DB_SNB_B;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_2:
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_2:
		वापस EDP_LINK_TRAIN_400_600MV_6DB_SNB_B;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_1:
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2 | DP_TRAIN_PRE_EMPH_LEVEL_1:
		वापस EDP_LINK_TRAIN_600_800MV_3_5DB_SNB_B;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2 | DP_TRAIN_PRE_EMPH_LEVEL_0:
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_3 | DP_TRAIN_PRE_EMPH_LEVEL_0:
		वापस EDP_LINK_TRAIN_800_1200MV_0DB_SNB_B;
	शेष:
		MISSING_CASE(संकेत_levels);
		वापस EDP_LINK_TRAIN_400_600MV_0DB_SNB_B;
	पूर्ण
पूर्ण

अटल व्योम
snb_cpu_edp_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u8 train_set = पूर्णांकel_dp->train_set[0];
	u32 संकेत_levels;

	संकेत_levels = snb_cpu_edp_संकेत_levels(train_set);

	drm_dbg_kms(&dev_priv->drm, "Using signal levels %08x\n",
		    संकेत_levels);

	पूर्णांकel_dp->DP &= ~EDP_LINK_TRAIN_VOL_EMP_MASK_SNB;
	पूर्णांकel_dp->DP |= संकेत_levels;

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);
पूर्ण

/* IVB CPU eDP voltage swing and pre-emphasis control */
अटल u32 ivb_cpu_edp_संकेत_levels(u8 train_set)
अणु
	u8 संकेत_levels = train_set & (DP_TRAIN_VOLTAGE_SWING_MASK |
					DP_TRAIN_PRE_EMPHASIS_MASK);

	चयन (संकेत_levels) अणु
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_0:
		वापस EDP_LINK_TRAIN_400MV_0DB_IVB;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_1:
		वापस EDP_LINK_TRAIN_400MV_3_5DB_IVB;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_0 | DP_TRAIN_PRE_EMPH_LEVEL_2:
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_2:
		वापस EDP_LINK_TRAIN_400MV_6DB_IVB;

	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_0:
		वापस EDP_LINK_TRAIN_600MV_0DB_IVB;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_1 | DP_TRAIN_PRE_EMPH_LEVEL_1:
		वापस EDP_LINK_TRAIN_600MV_3_5DB_IVB;

	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2 | DP_TRAIN_PRE_EMPH_LEVEL_0:
		वापस EDP_LINK_TRAIN_800MV_0DB_IVB;
	हाल DP_TRAIN_VOLTAGE_SWING_LEVEL_2 | DP_TRAIN_PRE_EMPH_LEVEL_1:
		वापस EDP_LINK_TRAIN_800MV_3_5DB_IVB;

	शेष:
		MISSING_CASE(संकेत_levels);
		वापस EDP_LINK_TRAIN_500MV_0DB_IVB;
	पूर्ण
पूर्ण

अटल व्योम
ivb_cpu_edp_set_संकेत_levels(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	u8 train_set = पूर्णांकel_dp->train_set[0];
	u32 संकेत_levels;

	संकेत_levels = ivb_cpu_edp_संकेत_levels(train_set);

	drm_dbg_kms(&dev_priv->drm, "Using signal levels %08x\n",
		    संकेत_levels);

	पूर्णांकel_dp->DP &= ~EDP_LINK_TRAIN_VOL_EMP_MASK_IVB;
	पूर्णांकel_dp->DP |= संकेत_levels;

	पूर्णांकel_de_ग_लिखो(dev_priv, पूर्णांकel_dp->output_reg, पूर्णांकel_dp->DP);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);
पूर्ण

/*
 * If display is now connected check links status,
 * there has been known issues of link loss triggering
 * दीर्घ pulse.
 *
 * Some sinks (eg. ASUS PB287Q) seem to perक्रमm some
 * weird HPD ping pong during modesets. So we can apparently
 * end up with HPD going low during a modeset, and then
 * going back up soon after. And once that happens we must
 * retrain the link to get a picture. That's in हाल no
 * userspace component reacted to पूर्णांकermittent HPD dip.
 */
अटल क्रमागत पूर्णांकel_hotplug_state
पूर्णांकel_dp_hotplug(काष्ठा पूर्णांकel_encoder *encoder,
		 काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
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
	 * Keeping it consistent with पूर्णांकel_ddi_hotplug() and
	 * पूर्णांकel_hdmi_hotplug().
	 */
	अगर (state == INTEL_HOTPLUG_UNCHANGED && !connector->hotplug_retries)
		state = INTEL_HOTPLUG_RETRY;

	वापस state;
पूर्ण

अटल bool ibx_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 bit = dev_priv->hotplug.pch_hpd[encoder->hpd_pin];

	वापस पूर्णांकel_de_पढ़ो(dev_priv, SDEISR) & bit;
पूर्ण

अटल bool g4x_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 bit;

	चयन (encoder->hpd_pin) अणु
	हाल HPD_PORT_B:
		bit = PORTB_HOTPLUG_LIVE_STATUS_G4X;
		अवरोध;
	हाल HPD_PORT_C:
		bit = PORTC_HOTPLUG_LIVE_STATUS_G4X;
		अवरोध;
	हाल HPD_PORT_D:
		bit = PORTD_HOTPLUG_LIVE_STATUS_G4X;
		अवरोध;
	शेष:
		MISSING_CASE(encoder->hpd_pin);
		वापस false;
	पूर्ण

	वापस पूर्णांकel_de_पढ़ो(dev_priv, PORT_HOTPLUG_STAT) & bit;
पूर्ण

अटल bool gm45_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 bit;

	चयन (encoder->hpd_pin) अणु
	हाल HPD_PORT_B:
		bit = PORTB_HOTPLUG_LIVE_STATUS_GM45;
		अवरोध;
	हाल HPD_PORT_C:
		bit = PORTC_HOTPLUG_LIVE_STATUS_GM45;
		अवरोध;
	हाल HPD_PORT_D:
		bit = PORTD_HOTPLUG_LIVE_STATUS_GM45;
		अवरोध;
	शेष:
		MISSING_CASE(encoder->hpd_pin);
		वापस false;
	पूर्ण

	वापस पूर्णांकel_de_पढ़ो(dev_priv, PORT_HOTPLUG_STAT) & bit;
पूर्ण

अटल bool ilk_digital_port_connected(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 bit = dev_priv->hotplug.hpd[encoder->hpd_pin];

	वापस पूर्णांकel_de_पढ़ो(dev_priv, DEISR) & bit;
पूर्ण

अटल व्योम पूर्णांकel_dp_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	पूर्णांकel_dp_encoder_flush_work(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(enc_to_dig_port(to_पूर्णांकel_encoder(encoder)));
पूर्ण

क्रमागत pipe vlv_active_pipe(काष्ठा पूर्णांकel_dp *पूर्णांकel_dp)
अणु
	काष्ठा drm_i915_निजी *dev_priv = dp_to_i915(पूर्णांकel_dp);
	काष्ठा पूर्णांकel_encoder *encoder = &dp_to_dig_port(पूर्णांकel_dp)->base;
	क्रमागत pipe pipe;

	अगर (g4x_dp_port_enabled(dev_priv, पूर्णांकel_dp->output_reg,
				encoder->port, &pipe))
		वापस pipe;

	वापस INVALID_PIPE;
पूर्ण

अटल व्योम पूर्णांकel_dp_encoder_reset(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->dev);
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(to_पूर्णांकel_encoder(encoder));

	पूर्णांकel_dp->DP = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dp->output_reg);

	पूर्णांकel_dp->reset_link_params = true;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		पूर्णांकel_wakeref_t wakeref;

		with_पूर्णांकel_pps_lock(पूर्णांकel_dp, wakeref)
			पूर्णांकel_dp->pps.active_pipe = vlv_active_pipe(पूर्णांकel_dp);
	पूर्ण

	पूर्णांकel_pps_encoder_reset(पूर्णांकel_dp);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_dp_enc_funcs = अणु
	.reset = पूर्णांकel_dp_encoder_reset,
	.destroy = पूर्णांकel_dp_encoder_destroy,
पूर्ण;

bool g4x_dp_init(काष्ठा drm_i915_निजी *dev_priv,
		 i915_reg_t output_reg, क्रमागत port port)
अणु
	काष्ठा पूर्णांकel_digital_port *dig_port;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा drm_encoder *encoder;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;

	dig_port = kzalloc(माप(*dig_port), GFP_KERNEL);
	अगर (!dig_port)
		वापस false;

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector)
		जाओ err_connector_alloc;

	पूर्णांकel_encoder = &dig_port->base;
	encoder = &पूर्णांकel_encoder->base;

	mutex_init(&dig_port->hdcp_mutex);

	अगर (drm_encoder_init(&dev_priv->drm, &पूर्णांकel_encoder->base,
			     &पूर्णांकel_dp_enc_funcs, DRM_MODE_ENCODER_TMDS,
			     "DP %c", port_name(port)))
		जाओ err_encoder_init;

	पूर्णांकel_encoder->hotplug = पूर्णांकel_dp_hotplug;
	पूर्णांकel_encoder->compute_config = पूर्णांकel_dp_compute_config;
	पूर्णांकel_encoder->get_hw_state = पूर्णांकel_dp_get_hw_state;
	पूर्णांकel_encoder->get_config = पूर्णांकel_dp_get_config;
	पूर्णांकel_encoder->sync_state = पूर्णांकel_dp_sync_state;
	पूर्णांकel_encoder->initial_fastset_check = पूर्णांकel_dp_initial_fastset_check;
	पूर्णांकel_encoder->update_pipe = पूर्णांकel_panel_update_backlight;
	पूर्णांकel_encoder->suspend = पूर्णांकel_dp_encoder_suspend;
	पूर्णांकel_encoder->shutकरोwn = पूर्णांकel_dp_encoder_shutकरोwn;
	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		पूर्णांकel_encoder->pre_pll_enable = chv_dp_pre_pll_enable;
		पूर्णांकel_encoder->pre_enable = chv_pre_enable_dp;
		पूर्णांकel_encoder->enable = vlv_enable_dp;
		पूर्णांकel_encoder->disable = vlv_disable_dp;
		पूर्णांकel_encoder->post_disable = chv_post_disable_dp;
		पूर्णांकel_encoder->post_pll_disable = chv_dp_post_pll_disable;
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv)) अणु
		पूर्णांकel_encoder->pre_pll_enable = vlv_dp_pre_pll_enable;
		पूर्णांकel_encoder->pre_enable = vlv_pre_enable_dp;
		पूर्णांकel_encoder->enable = vlv_enable_dp;
		पूर्णांकel_encoder->disable = vlv_disable_dp;
		पूर्णांकel_encoder->post_disable = vlv_post_disable_dp;
	पूर्ण अन्यथा अणु
		पूर्णांकel_encoder->pre_enable = g4x_pre_enable_dp;
		पूर्णांकel_encoder->enable = g4x_enable_dp;
		पूर्णांकel_encoder->disable = g4x_disable_dp;
		पूर्णांकel_encoder->post_disable = g4x_post_disable_dp;
	पूर्ण

	अगर ((IS_IVYBRIDGE(dev_priv) && port == PORT_A) ||
	    (HAS_PCH_CPT(dev_priv) && port != PORT_A))
		dig_port->dp.set_link_train = cpt_set_link_train;
	अन्यथा
		dig_port->dp.set_link_train = g4x_set_link_train;

	अगर (IS_CHERRYVIEW(dev_priv))
		dig_port->dp.set_संकेत_levels = chv_set_संकेत_levels;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		dig_port->dp.set_संकेत_levels = vlv_set_संकेत_levels;
	अन्यथा अगर (IS_IVYBRIDGE(dev_priv) && port == PORT_A)
		dig_port->dp.set_संकेत_levels = ivb_cpu_edp_set_संकेत_levels;
	अन्यथा अगर (IS_SANDYBRIDGE(dev_priv) && port == PORT_A)
		dig_port->dp.set_संकेत_levels = snb_cpu_edp_set_संकेत_levels;
	अन्यथा
		dig_port->dp.set_संकेत_levels = g4x_set_संकेत_levels;

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv) ||
	    (HAS_PCH_SPLIT(dev_priv) && port != PORT_A)) अणु
		dig_port->dp.preemph_max = पूर्णांकel_dp_preemph_max_3;
		dig_port->dp.voltage_max = पूर्णांकel_dp_voltage_max_3;
	पूर्ण अन्यथा अणु
		dig_port->dp.preemph_max = पूर्णांकel_dp_preemph_max_2;
		dig_port->dp.voltage_max = पूर्णांकel_dp_voltage_max_2;
	पूर्ण

	dig_port->dp.output_reg = output_reg;
	dig_port->max_lanes = 4;

	पूर्णांकel_encoder->type = INTEL_OUTPUT_DP;
	पूर्णांकel_encoder->घातer_करोमुख्य = पूर्णांकel_port_to_घातer_करोमुख्य(port);
	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		अगर (port == PORT_D)
			पूर्णांकel_encoder->pipe_mask = BIT(PIPE_C);
		अन्यथा
			पूर्णांकel_encoder->pipe_mask = BIT(PIPE_A) | BIT(PIPE_B);
	पूर्ण अन्यथा अणु
		पूर्णांकel_encoder->pipe_mask = ~0;
	पूर्ण
	पूर्णांकel_encoder->cloneable = 0;
	पूर्णांकel_encoder->port = port;
	पूर्णांकel_encoder->hpd_pin = पूर्णांकel_hpd_pin_शेष(dev_priv, port);

	dig_port->hpd_pulse = पूर्णांकel_dp_hpd_pulse;

	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (IS_GM45(dev_priv))
			dig_port->connected = gm45_digital_port_connected;
		अन्यथा
			dig_port->connected = g4x_digital_port_connected;
	पूर्ण अन्यथा अणु
		अगर (port == PORT_A)
			dig_port->connected = ilk_digital_port_connected;
		अन्यथा
			dig_port->connected = ibx_digital_port_connected;
	पूर्ण

	अगर (port != PORT_A)
		पूर्णांकel_infoframe_init(dig_port);

	dig_port->aux_ch = पूर्णांकel_bios_port_aux_ch(dev_priv, port);
	अगर (!पूर्णांकel_dp_init_connector(dig_port, पूर्णांकel_connector))
		जाओ err_init_connector;

	वापस true;

err_init_connector:
	drm_encoder_cleanup(encoder);
err_encoder_init:
	kमुक्त(पूर्णांकel_connector);
err_connector_alloc:
	kमुक्त(dig_port);
	वापस false;
पूर्ण
