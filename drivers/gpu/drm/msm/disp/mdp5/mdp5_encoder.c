<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "mdp5_kms.h"

अटल काष्ठा mdp5_kms *get_kms(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा msm_drm_निजी *priv = encoder->dev->dev_निजी;
	वापस to_mdp5_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल व्योम mdp5_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	drm_encoder_cleanup(encoder);
	kमुक्त(mdp5_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs mdp5_encoder_funcs = अणु
	.destroy = mdp5_encoder_destroy,
पूर्ण;

अटल व्योम mdp5_vid_encoder_mode_set(काष्ठा drm_encoder *encoder,
				      काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(encoder);
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_connector *connector;
	पूर्णांक पूर्णांकf = mdp5_encoder->पूर्णांकf->num;
	uपूर्णांक32_t dtv_hsync_skew, vsync_period, vsync_len, ctrl_pol;
	uपूर्णांक32_t display_v_start, display_v_end;
	uपूर्णांक32_t hsync_start_x, hsync_end_x;
	uपूर्णांक32_t क्रमmat = 0x2100;
	अचिन्हित दीर्घ flags;

	mode = adjusted_mode;

	DBG("set mode: " DRM_MODE_FMT, DRM_MODE_ARG(mode));

	ctrl_pol = 0;

	/* DSI controller cannot handle active-low sync संकेतs. */
	अगर (mdp5_encoder->पूर्णांकf->type != INTF_DSI) अणु
		अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
			ctrl_pol |= MDP5_INTF_POLARITY_CTL_HSYNC_LOW;
		अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
			ctrl_pol |= MDP5_INTF_POLARITY_CTL_VSYNC_LOW;
	पूर्ण
	/* probably need to get DATA_EN polarity from panel.. */

	dtv_hsync_skew = 0;  /* get this from panel? */

	/* Get color क्रमmat from panel, शेष is 8bpc */
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		अगर (connector->encoder == encoder) अणु
			चयन (connector->display_info.bpc) अणु
			हाल 4:
				क्रमmat |= 0;
				अवरोध;
			हाल 5:
				क्रमmat |= 0x15;
				अवरोध;
			हाल 6:
				क्रमmat |= 0x2A;
				अवरोध;
			हाल 8:
			शेष:
				क्रमmat |= 0x3F;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	hsync_start_x = (mode->htotal - mode->hsync_start);
	hsync_end_x = mode->htotal - (mode->hsync_start - mode->hdisplay) - 1;

	vsync_period = mode->vtotal * mode->htotal;
	vsync_len = (mode->vsync_end - mode->vsync_start) * mode->htotal;
	display_v_start = (mode->vtotal - mode->vsync_start) * mode->htotal + dtv_hsync_skew;
	display_v_end = vsync_period - ((mode->vsync_start - mode->vdisplay) * mode->htotal) + dtv_hsync_skew - 1;

	/*
	 * For edp only:
	 * DISPLAY_V_START = (VBP * HCYCLE) + HBP
	 * DISPLAY_V_END = (VBP + VACTIVE) * HCYCLE - 1 - HFP
	 */
	अगर (mdp5_encoder->पूर्णांकf->type == INTF_eDP) अणु
		display_v_start += mode->htotal - mode->hsync_start;
		display_v_end -= mode->hsync_start - mode->hdisplay;
	पूर्ण

	spin_lock_irqsave(&mdp5_encoder->पूर्णांकf_lock, flags);

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_HSYNC_CTL(पूर्णांकf),
			MDP5_INTF_HSYNC_CTL_PULSEW(mode->hsync_end - mode->hsync_start) |
			MDP5_INTF_HSYNC_CTL_PERIOD(mode->htotal));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_VSYNC_PERIOD_F0(पूर्णांकf), vsync_period);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_VSYNC_LEN_F0(पूर्णांकf), vsync_len);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_DISPLAY_HCTL(पूर्णांकf),
			MDP5_INTF_DISPLAY_HCTL_START(hsync_start_x) |
			MDP5_INTF_DISPLAY_HCTL_END(hsync_end_x));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_DISPLAY_VSTART_F0(पूर्णांकf), display_v_start);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_DISPLAY_VEND_F0(पूर्णांकf), display_v_end);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_BORDER_COLOR(पूर्णांकf), 0);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_UNDERFLOW_COLOR(पूर्णांकf), 0xff);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_HSYNC_SKEW(पूर्णांकf), dtv_hsync_skew);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_POLARITY_CTL(पूर्णांकf), ctrl_pol);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_ACTIVE_HCTL(पूर्णांकf),
			MDP5_INTF_ACTIVE_HCTL_START(0) |
			MDP5_INTF_ACTIVE_HCTL_END(0));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_ACTIVE_VSTART_F0(पूर्णांकf), 0);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_ACTIVE_VEND_F0(पूर्णांकf), 0);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_PANEL_FORMAT(पूर्णांकf), क्रमmat);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_FRAME_LINE_COUNT_EN(पूर्णांकf), 0x3);  /* frame+line? */

	spin_unlock_irqrestore(&mdp5_encoder->पूर्णांकf_lock, flags);

	mdp5_crtc_set_pipeline(encoder->crtc);
पूर्ण

अटल व्योम mdp5_vid_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(encoder);
	काष्ठा mdp5_ctl *ctl = mdp5_encoder->ctl;
	काष्ठा mdp5_pipeline *pipeline = mdp5_crtc_get_pipeline(encoder->crtc);
	काष्ठा mdp5_hw_mixer *mixer = mdp5_crtc_get_mixer(encoder->crtc);
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_encoder->पूर्णांकf;
	पूर्णांक पूर्णांकfn = mdp5_encoder->पूर्णांकf->num;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!mdp5_encoder->enabled))
		वापस;

	mdp5_ctl_set_encoder_state(ctl, pipeline, false);

	spin_lock_irqsave(&mdp5_encoder->पूर्णांकf_lock, flags);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_TIMING_ENGINE_EN(पूर्णांकfn), 0);
	spin_unlock_irqrestore(&mdp5_encoder->पूर्णांकf_lock, flags);
	mdp5_ctl_commit(ctl, pipeline, mdp_ctl_flush_mask_encoder(पूर्णांकf), true);

	/*
	 * Wait क्रम a vsync so we know the ENABLE=0 latched beक्रमe
	 * the (connector) source of the vsync's माला_लो disabled,
	 * otherwise we end up in a funny state अगर we re-enable
	 * beक्रमe the disable latches, which results that some of
	 * the settings changes क्रम the new modeset (like new
	 * scanout buffer) करोn't latch properly..
	 */
	mdp_irq_रुको(&mdp5_kms->base, पूर्णांकf2vblank(mixer, पूर्णांकf));

	mdp5_encoder->enabled = false;
पूर्ण

अटल व्योम mdp5_vid_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(encoder);
	काष्ठा mdp5_ctl *ctl = mdp5_encoder->ctl;
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_encoder->पूर्णांकf;
	काष्ठा mdp5_pipeline *pipeline = mdp5_crtc_get_pipeline(encoder->crtc);
	पूर्णांक पूर्णांकfn = पूर्णांकf->num;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(mdp5_encoder->enabled))
		वापस;

	spin_lock_irqsave(&mdp5_encoder->पूर्णांकf_lock, flags);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_TIMING_ENGINE_EN(पूर्णांकfn), 1);
	spin_unlock_irqrestore(&mdp5_encoder->पूर्णांकf_lock, flags);
	mdp5_ctl_commit(ctl, pipeline, mdp_ctl_flush_mask_encoder(पूर्णांकf), true);

	mdp5_ctl_set_encoder_state(ctl, pipeline, true);

	mdp5_encoder->enabled = true;
पूर्ण

अटल व्योम mdp5_encoder_mode_set(काष्ठा drm_encoder *encoder,
				  काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_encoder->पूर्णांकf;

	अगर (पूर्णांकf->mode == MDP5_INTF_DSI_MODE_COMMAND)
		mdp5_cmd_encoder_mode_set(encoder, mode, adjusted_mode);
	अन्यथा
		mdp5_vid_encoder_mode_set(encoder, mode, adjusted_mode);
पूर्ण

अटल व्योम mdp5_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_encoder->पूर्णांकf;

	अगर (पूर्णांकf->mode == MDP5_INTF_DSI_MODE_COMMAND)
		mdp5_cmd_encoder_disable(encoder);
	अन्यथा
		mdp5_vid_encoder_disable(encoder);
पूर्ण

अटल व्योम mdp5_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_encoder->पूर्णांकf;
	/* this isn't right I think */
	काष्ठा drm_crtc_state *cstate = encoder->crtc->state;

	mdp5_encoder_mode_set(encoder, &cstate->mode, &cstate->adjusted_mode);

	अगर (पूर्णांकf->mode == MDP5_INTF_DSI_MODE_COMMAND)
		mdp5_cmd_encoder_enable(encoder);
	अन्यथा
		mdp5_vid_encoder_enable(encoder);
पूर्ण

अटल पूर्णांक mdp5_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				     काष्ठा drm_crtc_state *crtc_state,
				     काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc_state);
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_encoder->पूर्णांकf;
	काष्ठा mdp5_ctl *ctl = mdp5_encoder->ctl;

	mdp5_cstate->ctl = ctl;
	mdp5_cstate->pipeline.पूर्णांकf = पूर्णांकf;

	/*
	 * This is a bit awkward, but we want to flush the CTL and hit the
	 * START bit at most once क्रम an atomic update.  In the non-full-
	 * modeset हाल, this is करोne from crtc->atomic_flush(), but that
	 * is too early in the हाल of full modeset, in which हाल we
	 * defer to encoder->enable().  But we need to *know* whether
	 * encoder->enable() will be called to करो this:
	 */
	अगर (drm_atomic_crtc_needs_modeset(crtc_state))
		mdp5_cstate->defer_start = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs mdp5_encoder_helper_funcs = अणु
	.disable = mdp5_encoder_disable,
	.enable = mdp5_encoder_enable,
	.atomic_check = mdp5_encoder_atomic_check,
पूर्ण;

पूर्णांक mdp5_encoder_get_linecount(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(encoder);
	पूर्णांक पूर्णांकf = mdp5_encoder->पूर्णांकf->num;

	वापस mdp5_पढ़ो(mdp5_kms, REG_MDP5_INTF_LINE_COUNT(पूर्णांकf));
पूर्ण

u32 mdp5_encoder_get_framecount(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(encoder);
	पूर्णांक पूर्णांकf = mdp5_encoder->पूर्णांकf->num;

	वापस mdp5_पढ़ो(mdp5_kms, REG_MDP5_INTF_FRAME_COUNT(पूर्णांकf));
पूर्ण

पूर्णांक mdp5_vid_encoder_set_split_display(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_encoder *slave_encoder)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_encoder *mdp5_slave_enc = to_mdp5_encoder(slave_encoder);
	काष्ठा mdp5_kms *mdp5_kms;
	काष्ठा device *dev;
	पूर्णांक पूर्णांकf_num;
	u32 data = 0;

	अगर (!encoder || !slave_encoder)
		वापस -EINVAL;

	mdp5_kms = get_kms(encoder);
	पूर्णांकf_num = mdp5_encoder->पूर्णांकf->num;

	/* Switch slave encoder's TimingGen Sync mode,
	 * to use the master's enable संकेत क्रम the slave encoder.
	 */
	अगर (पूर्णांकf_num == 1)
		data |= MDP5_SPLIT_DPL_LOWER_INTF2_TG_SYNC;
	अन्यथा अगर (पूर्णांकf_num == 2)
		data |= MDP5_SPLIT_DPL_LOWER_INTF1_TG_SYNC;
	अन्यथा
		वापस -EINVAL;

	dev = &mdp5_kms->pdev->dev;
	/* Make sure घड़ीs are on when connectors calling this function. */
	pm_runसमय_get_sync(dev);

	/* Dumb Panel, Sync mode */
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SPLIT_DPL_UPPER, 0);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SPLIT_DPL_LOWER, data);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_SPLIT_DPL_EN, 1);

	mdp5_ctl_pair(mdp5_encoder->ctl, mdp5_slave_enc->ctl, true);

	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

व्योम mdp5_encoder_set_पूर्णांकf_mode(काष्ठा drm_encoder *encoder, bool cmd_mode)
अणु
	काष्ठा mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	काष्ठा mdp5_पूर्णांकerface *पूर्णांकf = mdp5_encoder->पूर्णांकf;

	/* TODO: Expand this to set ग_लिखोback modes too */
	अगर (cmd_mode) अणु
		WARN_ON(पूर्णांकf->type != INTF_DSI);
		पूर्णांकf->mode = MDP5_INTF_DSI_MODE_COMMAND;
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकf->type == INTF_DSI)
			पूर्णांकf->mode = MDP5_INTF_DSI_MODE_VIDEO;
		अन्यथा
			पूर्णांकf->mode = MDP5_INTF_MODE_NONE;
	पूर्ण
पूर्ण

/* initialize encoder */
काष्ठा drm_encoder *mdp5_encoder_init(काष्ठा drm_device *dev,
				      काष्ठा mdp5_पूर्णांकerface *पूर्णांकf,
				      काष्ठा mdp5_ctl *ctl)
अणु
	काष्ठा drm_encoder *encoder = शून्य;
	काष्ठा mdp5_encoder *mdp5_encoder;
	पूर्णांक enc_type = (पूर्णांकf->type == INTF_DSI) ?
		DRM_MODE_ENCODER_DSI : DRM_MODE_ENCODER_TMDS;
	पूर्णांक ret;

	mdp5_encoder = kzalloc(माप(*mdp5_encoder), GFP_KERNEL);
	अगर (!mdp5_encoder) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	encoder = &mdp5_encoder->base;
	mdp5_encoder->ctl = ctl;
	mdp5_encoder->पूर्णांकf = पूर्णांकf;

	spin_lock_init(&mdp5_encoder->पूर्णांकf_lock);

	drm_encoder_init(dev, encoder, &mdp5_encoder_funcs, enc_type, शून्य);

	drm_encoder_helper_add(encoder, &mdp5_encoder_helper_funcs);

	वापस encoder;

fail:
	अगर (encoder)
		mdp5_encoder_destroy(encoder);

	वापस ERR_PTR(ret);
पूर्ण
