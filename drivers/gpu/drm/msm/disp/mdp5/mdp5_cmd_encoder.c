<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "mdp5_kms.h"

अटल काष्ठा mdp5_kms *get_kms(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा msm_drm_निजी *priv = encoder->dev->dev_निजी;
	वापस to_mdp5_kms(to_mdp_kms(priv->kms));
पूर्ण

#घोषणा VSYNC_CLK_RATE 19200000
अटल पूर्णांक pingpong_tearcheck_setup(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(encoder);
	काष्ठा device *dev = encoder->dev->dev;
	u32 total_lines, vclks_line, cfg;
	दीर्घ vsync_clk_speed;
	काष्ठा mdp5_hw_mixer *mixer = mdp5_crtc_get_mixer(encoder->crtc);
	पूर्णांक pp_id = mixer->pp;

	अगर (IS_ERR_OR_शून्य(mdp5_kms->vsync_clk)) अणु
		DRM_DEV_ERROR(dev, "vsync_clk is not initialized\n");
		वापस -EINVAL;
	पूर्ण

	total_lines = mode->vtotal * drm_mode_vrefresh(mode);
	अगर (!total_lines) अणु
		DRM_DEV_ERROR(dev, "%s: vtotal(%d) or vrefresh(%d) is 0\n",
			      __func__, mode->vtotal, drm_mode_vrefresh(mode));
		वापस -EINVAL;
	पूर्ण

	vsync_clk_speed = clk_round_rate(mdp5_kms->vsync_clk, VSYNC_CLK_RATE);
	अगर (vsync_clk_speed <= 0) अणु
		DRM_DEV_ERROR(dev, "vsync_clk round rate failed %ld\n",
							vsync_clk_speed);
		वापस -EINVAL;
	पूर्ण
	vclks_line = vsync_clk_speed / total_lines;

	cfg = MDP5_PP_SYNC_CONFIG_VSYNC_COUNTER_EN
		| MDP5_PP_SYNC_CONFIG_VSYNC_IN_EN;
	cfg |= MDP5_PP_SYNC_CONFIG_VSYNC_COUNT(vclks_line);

	/*
	 * Tearcheck emits a blanking संकेत every vclks_line * vtotal * 2 ticks on
	 * the vsync_clk equating to roughly half the desired panel refresh rate.
	 * This is only necessary as stability fallback अगर पूर्णांकerrupts from the
	 * panel arrive too late or not at all, but is currently used by शेष
	 * because these panel पूर्णांकerrupts are not wired up yet.
	 */
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PP_SYNC_CONFIG_VSYNC(pp_id), cfg);
	mdp5_ग_लिखो(mdp5_kms,
		REG_MDP5_PP_SYNC_CONFIG_HEIGHT(pp_id), (2 * mode->vtotal));

	mdp5_ग_लिखो(mdp5_kms,
		REG_MDP5_PP_VSYNC_INIT_VAL(pp_id), mode->vdisplay);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PP_RD_PTR_IRQ(pp_id), mode->vdisplay + 1);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PP_START_POS(pp_id), mode->vdisplay);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PP_SYNC_THRESH(pp_id),
			MDP5_PP_SYNC_THRESH_START(4) |
			MDP5_PP_SYNC_THRESH_CONTINUE(4));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PP_AUTOREFRESH_CONFIG(pp_id), 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक pingpong_tearcheck_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(encoder);
	काष्ठा mdp5_hw_mixer *mixer = mdp5_crtc_get_mixer(encoder->crtc);
	पूर्णांक pp_id = mixer->pp;
	पूर्णांक ret;

	ret = clk_set_rate(mdp5_kms->vsync_clk,
		clk_round_rate(mdp5_kms->vsync_clk, VSYNC_CLK_RATE));
	अगर (ret) अणु
		DRM_DEV_ERROR(encoder->dev->dev,
			"vsync_clk clk_set_rate failed, %d\n", ret);
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(mdp5_kms->vsync_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(encoder->dev->dev,
			"vsync_clk clk_prepare_enable failed, %d\n", ret);
		वापस ret;
	पूर्ण

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PP_TEAR_CHECK_EN(pp_id), 1);

	वापस 0;
पूर्ण

अटल व्योम pingpong_tearcheck_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(encoder);
	काष्ठा mdp5_hw_mixer *mixer = mdp5_crtc_get_mixer(encoder->crtc);
	पूर्णांक pp_id = mixer->pp;

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PP_TEAR_CHECK_EN(pp_id), 0);
	clk_disable_unprepare(mdp5_kms->vsync_clk);
पूर्ण

व्योम mdp5_cmd_encoder_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु
	mode = adjusted_mode;

	DBG("set mode: " DRM_MODE_FMT, DRM_MODE_ARG(mode));
	pingpong_tearcheck_setup(encoder, mode);
	mdp5_crtc_set_pipeline(encoder->crtc);
पूर्ण

व्योम mdp5_cmd_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_cmd_enc = to_mdp5_encoder(encoder);
	काष्ठा mdp5_ctl *ctl = mdp5_cmd_enc->ctl;
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_cmd_enc->पूर्णांकf;
	काष्ठा mdp5_pipeline *pipeline = mdp5_crtc_get_pipeline(encoder->crtc);

	अगर (WARN_ON(!mdp5_cmd_enc->enabled))
		वापस;

	pingpong_tearcheck_disable(encoder);

	mdp5_ctl_set_encoder_state(ctl, pipeline, false);
	mdp5_ctl_commit(ctl, pipeline, mdp_ctl_flush_mask_encoder(पूर्णांकf), true);

	mdp5_cmd_enc->enabled = false;
पूर्ण

व्योम mdp5_cmd_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_cmd_enc = to_mdp5_encoder(encoder);
	काष्ठा mdp5_ctl *ctl = mdp5_cmd_enc->ctl;
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_cmd_enc->पूर्णांकf;
	काष्ठा mdp5_pipeline *pipeline = mdp5_crtc_get_pipeline(encoder->crtc);

	अगर (WARN_ON(mdp5_cmd_enc->enabled))
		वापस;

	अगर (pingpong_tearcheck_enable(encoder))
		वापस;

	mdp5_ctl_commit(ctl, pipeline, mdp_ctl_flush_mask_encoder(पूर्णांकf), true);

	mdp5_ctl_set_encoder_state(ctl, pipeline, true);

	mdp5_cmd_enc->enabled = true;
पूर्ण

पूर्णांक mdp5_cmd_encoder_set_split_display(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_encoder *slave_encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_cmd_enc = to_mdp5_encoder(encoder);
	काष्ठा mdp5_kms *mdp5_kms;
	काष्ठा device *dev;
	पूर्णांक पूर्णांकf_num;
	u32 data = 0;

	अगर (!encoder || !slave_encoder)
		वापस -EINVAL;

	mdp5_kms = get_kms(encoder);
	पूर्णांकf_num = mdp5_cmd_enc->पूर्णांकf->num;

	/* Switch slave encoder's trigger MUX, to use the master's
	 * start संकेत क्रम the slave encoder
	 */
	अगर (पूर्णांकf_num == 1)
		data |= MDP5_SPLIT_DPL_UPPER_INTF2_SW_TRG_MUX;
	अन्यथा अगर (पूर्णांकf_num == 2)
		data |= MDP5_SPLIT_DPL_UPPER_INTF1_SW_TRG_MUX;
	अन्यथा
		वापस -EINVAL;

	/* Smart Panel, Sync mode */
	data |= MDP5_SPLIT_DPL_UPPER_SMART_PANEL;

	dev = &mdp5_kms->pdev->dev;

	/* Make sure घड़ीs are on when connectors calling this function. */
	pm_runसमय_get_sync(dev);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SPLIT_DPL_UPPER, data);

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SPLIT_DPL_LOWER,
		   MDP5_SPLIT_DPL_LOWER_SMART_PANEL);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SPLIT_DPL_EN, 1);
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण
