<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/of_irq.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_vblank.h>

#समावेश "msm_drv.h"
#समावेश "msm_gem.h"
#समावेश "msm_mmu.h"
#समावेश "mdp5_kms.h"

अटल पूर्णांक mdp5_hw_init(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा device *dev = &mdp5_kms->pdev->dev;
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(dev);

	/* Magic unknown रेजिस्टर ग_लिखोs:
	 *
	 *    W VBIF:0x004 00000001      (mdss_mdp.c:839)
	 *    W MDP5:0x2e0 0xe9          (mdss_mdp.c:839)
	 *    W MDP5:0x2e4 0x55          (mdss_mdp.c:839)
	 *    W MDP5:0x3ac 0xc0000ccc    (mdss_mdp.c:839)
	 *    W MDP5:0x3b4 0xc0000ccc    (mdss_mdp.c:839)
	 *    W MDP5:0x3bc 0xcccccc      (mdss_mdp.c:839)
	 *    W MDP5:0x4a8 0xcccc0c0     (mdss_mdp.c:839)
	 *    W MDP5:0x4b0 0xccccc0c0    (mdss_mdp.c:839)
	 *    W MDP5:0x4b8 0xccccc000    (mdss_mdp.c:839)
	 *
	 * Downstream fbdev driver माला_लो these रेजिस्टर offsets/values
	 * from DT.. not really sure what these रेजिस्टरs are or अगर
	 * dअगरferent values क्रम dअगरferent boards/SoC's, etc.  I guess
	 * they are the golden रेजिस्टरs.
	 *
	 * Not setting these करोes not seem to cause any problem.  But
	 * we may be getting lucky with the bootloader initializing
	 * them क्रम us.  OTOH, अगर we can always count on the bootloader
	 * setting the golden रेजिस्टरs, then perhaps we करोn't need to
	 * care.
	 */

	spin_lock_irqsave(&mdp5_kms->resource_lock, flags);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_DISP_INTF_SEL, 0);
	spin_unlock_irqrestore(&mdp5_kms->resource_lock, flags);

	mdp5_ctlm_hw_reset(mdp5_kms->ctlm);

	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

/* Global/shared object state funcs */

/*
 * This is a helper that वापसs the निजी state currently in operation.
 * Note that this would वापस the "old_state" अगर called in the atomic check
 * path, and the "new_state" after the atomic swap has been करोne.
 */
काष्ठा mdp5_global_state *
mdp5_get_existing_global_state(काष्ठा mdp5_kms *mdp5_kms)
अणु
	वापस to_mdp5_global_state(mdp5_kms->glob_state.state);
पूर्ण

/*
 * This acquires the modeset lock set aside क्रम global state, creates
 * a new duplicated निजी object state.
 */
काष्ठा mdp5_global_state *mdp5_get_global_state(काष्ठा drm_atomic_state *s)
अणु
	काष्ठा msm_drm_निजी *priv = s->dev->dev_निजी;
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(priv->kms));
	काष्ठा drm_निजी_state *priv_state;
	पूर्णांक ret;

	ret = drm_modeset_lock(&mdp5_kms->glob_state_lock, s->acquire_ctx);
	अगर (ret)
		वापस ERR_PTR(ret);

	priv_state = drm_atomic_get_निजी_obj_state(s, &mdp5_kms->glob_state);
	अगर (IS_ERR(priv_state))
		वापस ERR_CAST(priv_state);

	वापस to_mdp5_global_state(priv_state);
पूर्ण

अटल काष्ठा drm_निजी_state *
mdp5_global_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा mdp5_global_state *state;

	state = kmemdup(obj->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &state->base);

	वापस &state->base;
पूर्ण

अटल व्योम mdp5_global_destroy_state(काष्ठा drm_निजी_obj *obj,
				      काष्ठा drm_निजी_state *state)
अणु
	काष्ठा mdp5_global_state *mdp5_state = to_mdp5_global_state(state);

	kमुक्त(mdp5_state);
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs mdp5_global_state_funcs = अणु
	.atomic_duplicate_state = mdp5_global_duplicate_state,
	.atomic_destroy_state = mdp5_global_destroy_state,
पूर्ण;

अटल पूर्णांक mdp5_global_obj_init(काष्ठा mdp5_kms *mdp5_kms)
अणु
	काष्ठा mdp5_global_state *state;

	drm_modeset_lock_init(&mdp5_kms->glob_state_lock);

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->mdp5_kms = mdp5_kms;

	drm_atomic_निजी_obj_init(mdp5_kms->dev, &mdp5_kms->glob_state,
				    &state->base,
				    &mdp5_global_state_funcs);
	वापस 0;
पूर्ण

अटल व्योम mdp5_enable_commit(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	pm_runसमय_get_sync(&mdp5_kms->pdev->dev);
पूर्ण

अटल व्योम mdp5_disable_commit(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	pm_runसमय_put_sync(&mdp5_kms->pdev->dev);
पूर्ण

अटल व्योम mdp5_prepare_commit(काष्ठा msm_kms *kms, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा mdp5_global_state *global_state;

	global_state = mdp5_get_existing_global_state(mdp5_kms);

	अगर (mdp5_kms->smp)
		mdp5_smp_prepare_commit(mdp5_kms->smp, &global_state->smp);
पूर्ण

अटल व्योम mdp5_flush_commit(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	/* TODO */
पूर्ण

अटल व्योम mdp5_रुको_flush(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा drm_crtc *crtc;

	क्रम_each_crtc_mask(mdp5_kms->dev, crtc, crtc_mask)
		mdp5_crtc_रुको_क्रम_commit_करोne(crtc);
पूर्ण

अटल व्योम mdp5_complete_commit(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा mdp5_global_state *global_state;

	global_state = mdp5_get_existing_global_state(mdp5_kms);

	अगर (mdp5_kms->smp)
		mdp5_smp_complete_commit(mdp5_kms->smp, &global_state->smp);
पूर्ण

अटल दीर्घ mdp5_round_pixclk(काष्ठा msm_kms *kms, अचिन्हित दीर्घ rate,
		काष्ठा drm_encoder *encoder)
अणु
	वापस rate;
पूर्ण

अटल पूर्णांक mdp5_set_split_display(काष्ठा msm_kms *kms,
		काष्ठा drm_encoder *encoder,
		काष्ठा drm_encoder *slave_encoder,
		bool is_cmd_mode)
अणु
	अगर (is_cmd_mode)
		वापस mdp5_cmd_encoder_set_split_display(encoder,
							slave_encoder);
	अन्यथा
		वापस mdp5_vid_encoder_set_split_display(encoder,
							  slave_encoder);
पूर्ण

अटल व्योम mdp5_set_encoder_mode(काष्ठा msm_kms *kms,
				  काष्ठा drm_encoder *encoder,
				  bool cmd_mode)
अणु
	mdp5_encoder_set_पूर्णांकf_mode(encoder, cmd_mode);
पूर्ण

अटल व्योम mdp5_kms_destroy(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा msm_gem_address_space *aspace = kms->aspace;
	पूर्णांक i;

	क्रम (i = 0; i < mdp5_kms->num_hwmixers; i++)
		mdp5_mixer_destroy(mdp5_kms->hwmixers[i]);

	क्रम (i = 0; i < mdp5_kms->num_hwpipes; i++)
		mdp5_pipe_destroy(mdp5_kms->hwpipes[i]);

	अगर (aspace) अणु
		aspace->mmu->funcs->detach(aspace->mmu);
		msm_gem_address_space_put(aspace);
	पूर्ण

	mdp_kms_destroy(&mdp5_kms->base);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक smp_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(priv->kms));
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	अगर (!mdp5_kms->smp) अणु
		drm_म_लिखो(&p, "no SMP pool\n");
		वापस 0;
	पूर्ण

	mdp5_smp_dump(mdp5_kms->smp, &p);

	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list mdp5_debugfs_list[] = अणु
		अणु"smp", smp_show पूर्ण,
पूर्ण;

अटल पूर्णांक mdp5_kms_debugfs_init(काष्ठा msm_kms *kms, काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(mdp5_debugfs_list,
				 ARRAY_SIZE(mdp5_debugfs_list),
				 minor->debugfs_root, minor);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा mdp_kms_funcs kms_funcs = अणु
	.base = अणु
		.hw_init         = mdp5_hw_init,
		.irq_preinstall  = mdp5_irq_preinstall,
		.irq_postinstall = mdp5_irq_postinstall,
		.irq_uninstall   = mdp5_irq_uninstall,
		.irq             = mdp5_irq,
		.enable_vblank   = mdp5_enable_vblank,
		.disable_vblank  = mdp5_disable_vblank,
		.flush_commit    = mdp5_flush_commit,
		.enable_commit   = mdp5_enable_commit,
		.disable_commit  = mdp5_disable_commit,
		.prepare_commit  = mdp5_prepare_commit,
		.रुको_flush      = mdp5_रुको_flush,
		.complete_commit = mdp5_complete_commit,
		.get_क्रमmat      = mdp_get_क्रमmat,
		.round_pixclk    = mdp5_round_pixclk,
		.set_split_display = mdp5_set_split_display,
		.set_encoder_mode = mdp5_set_encoder_mode,
		.destroy         = mdp5_kms_destroy,
#अगर_घोषित CONFIG_DEBUG_FS
		.debugfs_init    = mdp5_kms_debugfs_init,
#पूर्ण_अगर
	पूर्ण,
	.set_irqmask         = mdp5_set_irqmask,
पूर्ण;

अटल पूर्णांक mdp5_disable(काष्ठा mdp5_kms *mdp5_kms)
अणु
	DBG("");

	mdp5_kms->enable_count--;
	WARN_ON(mdp5_kms->enable_count < 0);

	अगर (mdp5_kms->tbu_rt_clk)
		clk_disable_unprepare(mdp5_kms->tbu_rt_clk);
	अगर (mdp5_kms->tbu_clk)
		clk_disable_unprepare(mdp5_kms->tbu_clk);
	clk_disable_unprepare(mdp5_kms->ahb_clk);
	clk_disable_unprepare(mdp5_kms->axi_clk);
	clk_disable_unprepare(mdp5_kms->core_clk);
	अगर (mdp5_kms->lut_clk)
		clk_disable_unprepare(mdp5_kms->lut_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mdp5_enable(काष्ठा mdp5_kms *mdp5_kms)
अणु
	DBG("");

	mdp5_kms->enable_count++;

	clk_prepare_enable(mdp5_kms->ahb_clk);
	clk_prepare_enable(mdp5_kms->axi_clk);
	clk_prepare_enable(mdp5_kms->core_clk);
	अगर (mdp5_kms->lut_clk)
		clk_prepare_enable(mdp5_kms->lut_clk);
	अगर (mdp5_kms->tbu_clk)
		clk_prepare_enable(mdp5_kms->tbu_clk);
	अगर (mdp5_kms->tbu_rt_clk)
		clk_prepare_enable(mdp5_kms->tbu_rt_clk);

	वापस 0;
पूर्ण

अटल काष्ठा drm_encoder *स्थिरruct_encoder(काष्ठा mdp5_kms *mdp5_kms,
					     काष्ठा mdp5_पूर्णांकerface *पूर्णांकf,
					     काष्ठा mdp5_ctl *ctl)
अणु
	काष्ठा drm_device *dev = mdp5_kms->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_encoder *encoder;

	encoder = mdp5_encoder_init(dev, पूर्णांकf, ctl);
	अगर (IS_ERR(encoder)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to construct encoder\n");
		वापस encoder;
	पूर्ण

	priv->encoders[priv->num_encoders++] = encoder;

	वापस encoder;
पूर्ण

अटल पूर्णांक get_dsi_id_from_पूर्णांकf(स्थिर काष्ठा mdp5_cfg_hw *hw_cfg, पूर्णांक पूर्णांकf_num)
अणु
	स्थिर क्रमागत mdp5_पूर्णांकf_type *पूर्णांकfs = hw_cfg->पूर्णांकf.connect;
	स्थिर पूर्णांक पूर्णांकf_cnt = ARRAY_SIZE(hw_cfg->पूर्णांकf.connect);
	पूर्णांक id = 0, i;

	क्रम (i = 0; i < पूर्णांकf_cnt; i++) अणु
		अगर (पूर्णांकfs[i] == INTF_DSI) अणु
			अगर (पूर्णांकf_num == i)
				वापस id;

			id++;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक modeset_init_पूर्णांकf(काष्ठा mdp5_kms *mdp5_kms,
			     काष्ठा mdp5_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा drm_device *dev = mdp5_kms->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा mdp5_ctl_manager *ctlm = mdp5_kms->ctlm;
	काष्ठा mdp5_ctl *ctl;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret = 0;

	चयन (पूर्णांकf->type) अणु
	हाल INTF_eDP:
		अगर (!priv->edp)
			अवरोध;

		ctl = mdp5_ctlm_request(ctlm, पूर्णांकf->num);
		अगर (!ctl) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		encoder = स्थिरruct_encoder(mdp5_kms, पूर्णांकf, ctl);
		अगर (IS_ERR(encoder)) अणु
			ret = PTR_ERR(encoder);
			अवरोध;
		पूर्ण

		ret = msm_edp_modeset_init(priv->edp, dev, encoder);
		अवरोध;
	हाल INTF_HDMI:
		अगर (!priv->hdmi)
			अवरोध;

		ctl = mdp5_ctlm_request(ctlm, पूर्णांकf->num);
		अगर (!ctl) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		encoder = स्थिरruct_encoder(mdp5_kms, पूर्णांकf, ctl);
		अगर (IS_ERR(encoder)) अणु
			ret = PTR_ERR(encoder);
			अवरोध;
		पूर्ण

		ret = msm_hdmi_modeset_init(priv->hdmi, dev, encoder);
		अवरोध;
	हाल INTF_DSI:
	अणु
		स्थिर काष्ठा mdp5_cfg_hw *hw_cfg =
					mdp5_cfg_get_hw_config(mdp5_kms->cfg);
		पूर्णांक dsi_id = get_dsi_id_from_पूर्णांकf(hw_cfg, पूर्णांकf->num);

		अगर ((dsi_id >= ARRAY_SIZE(priv->dsi)) || (dsi_id < 0)) अणु
			DRM_DEV_ERROR(dev->dev, "failed to find dsi from intf %d\n",
				पूर्णांकf->num);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!priv->dsi[dsi_id])
			अवरोध;

		ctl = mdp5_ctlm_request(ctlm, पूर्णांकf->num);
		अगर (!ctl) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		encoder = स्थिरruct_encoder(mdp5_kms, पूर्णांकf, ctl);
		अगर (IS_ERR(encoder)) अणु
			ret = PTR_ERR(encoder);
			अवरोध;
		पूर्ण

		ret = msm_dsi_modeset_init(priv->dsi[dsi_id], dev, encoder);
		अवरोध;
	पूर्ण
	शेष:
		DRM_DEV_ERROR(dev->dev, "unknown intf: %d\n", पूर्णांकf->type);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक modeset_init(काष्ठा mdp5_kms *mdp5_kms)
अणु
	काष्ठा drm_device *dev = mdp5_kms->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित पूर्णांक num_crtcs;
	पूर्णांक i, ret, pi = 0, ci = 0;
	काष्ठा drm_plane *primary[MAX_BASES] = अणु शून्य पूर्ण;
	काष्ठा drm_plane *cursor[MAX_BASES] = अणु शून्य पूर्ण;

	/*
	 * Conकाष्ठा encoders and modeset initialize connector devices
	 * क्रम each बाह्यal display पूर्णांकerface.
	 */
	क्रम (i = 0; i < mdp5_kms->num_पूर्णांकfs; i++) अणु
		ret = modeset_init_पूर्णांकf(mdp5_kms, mdp5_kms->पूर्णांकfs[i]);
		अगर (ret)
			जाओ fail;
	पूर्ण

	/*
	 * We should ideally have less number of encoders (set up by parsing
	 * the MDP5 पूर्णांकerfaces) than the number of layer mixers present in HW,
	 * but let's be safe here anyway
	 */
	num_crtcs = min(priv->num_encoders, mdp5_kms->num_hwmixers);

	/*
	 * Conकाष्ठा planes equaling the number of hw pipes, and CRTCs क्रम the
	 * N encoders set up by the driver. The first N planes become primary
	 * planes क्रम the CRTCs, with the reमुख्यder as overlay planes:
	 */
	क्रम (i = 0; i < mdp5_kms->num_hwpipes; i++) अणु
		काष्ठा mdp5_hw_pipe *hwpipe = mdp5_kms->hwpipes[i];
		काष्ठा drm_plane *plane;
		क्रमागत drm_plane_type type;

		अगर (i < num_crtcs)
			type = DRM_PLANE_TYPE_PRIMARY;
		अन्यथा अगर (hwpipe->caps & MDP_PIPE_CAP_CURSOR)
			type = DRM_PLANE_TYPE_CURSOR;
		अन्यथा
			type = DRM_PLANE_TYPE_OVERLAY;

		plane = mdp5_plane_init(dev, type);
		अगर (IS_ERR(plane)) अणु
			ret = PTR_ERR(plane);
			DRM_DEV_ERROR(dev->dev, "failed to construct plane %d (%d)\n", i, ret);
			जाओ fail;
		पूर्ण
		priv->planes[priv->num_planes++] = plane;

		अगर (type == DRM_PLANE_TYPE_PRIMARY)
			primary[pi++] = plane;
		अगर (type == DRM_PLANE_TYPE_CURSOR)
			cursor[ci++] = plane;
	पूर्ण

	क्रम (i = 0; i < num_crtcs; i++) अणु
		काष्ठा drm_crtc *crtc;

		crtc  = mdp5_crtc_init(dev, primary[i], cursor[i], i);
		अगर (IS_ERR(crtc)) अणु
			ret = PTR_ERR(crtc);
			DRM_DEV_ERROR(dev->dev, "failed to construct crtc %d (%d)\n", i, ret);
			जाओ fail;
		पूर्ण
		priv->crtcs[priv->num_crtcs++] = crtc;
	पूर्ण

	/*
	 * Now that we know the number of crtcs we've created, set the possible
	 * crtcs क्रम the encoders
	 */
	क्रम (i = 0; i < priv->num_encoders; i++) अणु
		काष्ठा drm_encoder *encoder = priv->encoders[i];

		encoder->possible_crtcs = (1 << priv->num_crtcs) - 1;
	पूर्ण

	वापस 0;

fail:
	वापस ret;
पूर्ण

अटल व्योम पढ़ो_mdp_hw_revision(काष्ठा mdp5_kms *mdp5_kms,
				 u32 *major, u32 *minor)
अणु
	काष्ठा device *dev = &mdp5_kms->pdev->dev;
	u32 version;

	pm_runसमय_get_sync(dev);
	version = mdp5_पढ़ो(mdp5_kms, REG_MDP5_HW_VERSION);
	pm_runसमय_put_sync(dev);

	*major = FIELD(version, MDP5_HW_VERSION_MAJOR);
	*minor = FIELD(version, MDP5_HW_VERSION_MINOR);

	DRM_DEV_INFO(dev, "MDP5 version v%d.%d", *major, *minor);
पूर्ण

अटल पूर्णांक get_clk(काष्ठा platक्रमm_device *pdev, काष्ठा clk **clkp,
		स्थिर अक्षर *name, bool mandatory)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *clk = msm_clk_get(pdev, name);
	अगर (IS_ERR(clk) && mandatory) अणु
		DRM_DEV_ERROR(dev, "failed to get %s (%ld)\n", name, PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण
	अगर (IS_ERR(clk))
		DBG("skipping %s", name);
	अन्यथा
		*clkp = clk;

	वापस 0;
पूर्ण

काष्ठा msm_kms *mdp5_kms_init(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mdp5_kms *mdp5_kms;
	काष्ठा mdp5_cfg *config;
	काष्ठा msm_kms *kms;
	काष्ठा msm_gem_address_space *aspace;
	पूर्णांक irq, i, ret;
	काष्ठा device *iommu_dev;

	/* priv->kms would have been populated by the MDP5 driver */
	kms = priv->kms;
	अगर (!kms)
		वापस शून्य;

	mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	pdev = mdp5_kms->pdev;

	ret = mdp_kms_init(&mdp5_kms->base, &kms_funcs);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "failed to init kms\n");
		जाओ fail;
	पूर्ण

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (irq < 0) अणु
		ret = irq;
		DRM_DEV_ERROR(&pdev->dev, "failed to get irq: %d\n", ret);
		जाओ fail;
	पूर्ण

	kms->irq = irq;

	config = mdp5_cfg_get_config(mdp5_kms->cfg);

	/* make sure things are off beक्रमe attaching iommu (bootloader could
	 * have left things on, in which हाल we'll start getting faults अगर
	 * we करोn't disable):
	 */
	pm_runसमय_get_sync(&pdev->dev);
	क्रम (i = 0; i < MDP5_INTF_NUM_MAX; i++) अणु
		अगर (mdp5_cfg_पूर्णांकf_is_भव(config->hw->पूर्णांकf.connect[i]) ||
		    !config->hw->पूर्णांकf.base[i])
			जारी;
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_TIMING_ENGINE_EN(i), 0);

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTF_FRAME_LINE_COUNT_EN(i), 0x3);
	पूर्ण
	mdelay(16);

	अगर (config->platक्रमm.iommu) अणु
		काष्ठा msm_mmu *mmu;

		iommu_dev = &pdev->dev;
		अगर (!dev_iommu_fwspec_get(iommu_dev))
			iommu_dev = iommu_dev->parent;

		mmu = msm_iommu_new(iommu_dev, config->platक्रमm.iommu);

		aspace = msm_gem_address_space_create(mmu, "mdp5",
			0x1000, 0x100000000 - 0x1000);

		अगर (IS_ERR(aspace)) अणु
			अगर (!IS_ERR(mmu))
				mmu->funcs->destroy(mmu);
			ret = PTR_ERR(aspace);
			जाओ fail;
		पूर्ण

		kms->aspace = aspace;
	पूर्ण अन्यथा अणु
		DRM_DEV_INFO(&pdev->dev,
			 "no iommu, fallback to phys contig buffers for scanout\n");
		aspace = शून्य;
	पूर्ण

	pm_runसमय_put_sync(&pdev->dev);

	ret = modeset_init(mdp5_kms);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "modeset_init failed: %d\n", ret);
		जाओ fail;
	पूर्ण

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 0xffff;
	dev->mode_config.max_height = 0xffff;

	dev->max_vblank_count = 0; /* max_vblank_count is set on each CRTC */
	dev->vblank_disable_immediate = true;

	वापस kms;
fail:
	अगर (kms)
		mdp5_kms_destroy(kms);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम mdp5_destroy(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdp5_kms *mdp5_kms = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	अगर (mdp5_kms->ctlm)
		mdp5_ctlm_destroy(mdp5_kms->ctlm);
	अगर (mdp5_kms->smp)
		mdp5_smp_destroy(mdp5_kms->smp);
	अगर (mdp5_kms->cfg)
		mdp5_cfg_destroy(mdp5_kms->cfg);

	क्रम (i = 0; i < mdp5_kms->num_पूर्णांकfs; i++)
		kमुक्त(mdp5_kms->पूर्णांकfs[i]);

	अगर (mdp5_kms->rpm_enabled)
		pm_runसमय_disable(&pdev->dev);

	drm_atomic_निजी_obj_fini(&mdp5_kms->glob_state);
	drm_modeset_lock_fini(&mdp5_kms->glob_state_lock);
पूर्ण

अटल पूर्णांक स्थिरruct_pipes(काष्ठा mdp5_kms *mdp5_kms, पूर्णांक cnt,
		स्थिर क्रमागत mdp5_pipe *pipes, स्थिर uपूर्णांक32_t *offsets,
		uपूर्णांक32_t caps)
अणु
	काष्ठा drm_device *dev = mdp5_kms->dev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < cnt; i++) अणु
		काष्ठा mdp5_hw_pipe *hwpipe;

		hwpipe = mdp5_pipe_init(pipes[i], offsets[i], caps);
		अगर (IS_ERR(hwpipe)) अणु
			ret = PTR_ERR(hwpipe);
			DRM_DEV_ERROR(dev->dev, "failed to construct pipe for %s (%d)\n",
					pipe2name(pipes[i]), ret);
			वापस ret;
		पूर्ण
		hwpipe->idx = mdp5_kms->num_hwpipes;
		mdp5_kms->hwpipes[mdp5_kms->num_hwpipes++] = hwpipe;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hwpipe_init(काष्ठा mdp5_kms *mdp5_kms)
अणु
	अटल स्थिर क्रमागत mdp5_pipe rgb_planes[] = अणु
			SSPP_RGB0, SSPP_RGB1, SSPP_RGB2, SSPP_RGB3,
	पूर्ण;
	अटल स्थिर क्रमागत mdp5_pipe vig_planes[] = अणु
			SSPP_VIG0, SSPP_VIG1, SSPP_VIG2, SSPP_VIG3,
	पूर्ण;
	अटल स्थिर क्रमागत mdp5_pipe dma_planes[] = अणु
			SSPP_DMA0, SSPP_DMA1,
	पूर्ण;
	अटल स्थिर क्रमागत mdp5_pipe cursor_planes[] = अणु
			SSPP_CURSOR0, SSPP_CURSOR1,
	पूर्ण;
	स्थिर काष्ठा mdp5_cfg_hw *hw_cfg;
	पूर्णांक ret;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);

	/* Conकाष्ठा RGB pipes: */
	ret = स्थिरruct_pipes(mdp5_kms, hw_cfg->pipe_rgb.count, rgb_planes,
			hw_cfg->pipe_rgb.base, hw_cfg->pipe_rgb.caps);
	अगर (ret)
		वापस ret;

	/* Conकाष्ठा video (VIG) pipes: */
	ret = स्थिरruct_pipes(mdp5_kms, hw_cfg->pipe_vig.count, vig_planes,
			hw_cfg->pipe_vig.base, hw_cfg->pipe_vig.caps);
	अगर (ret)
		वापस ret;

	/* Conकाष्ठा DMA pipes: */
	ret = स्थिरruct_pipes(mdp5_kms, hw_cfg->pipe_dma.count, dma_planes,
			hw_cfg->pipe_dma.base, hw_cfg->pipe_dma.caps);
	अगर (ret)
		वापस ret;

	/* Conकाष्ठा cursor pipes: */
	ret = स्थिरruct_pipes(mdp5_kms, hw_cfg->pipe_cursor.count,
			cursor_planes, hw_cfg->pipe_cursor.base,
			hw_cfg->pipe_cursor.caps);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक hwmixer_init(काष्ठा mdp5_kms *mdp5_kms)
अणु
	काष्ठा drm_device *dev = mdp5_kms->dev;
	स्थिर काष्ठा mdp5_cfg_hw *hw_cfg;
	पूर्णांक i, ret;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);

	क्रम (i = 0; i < hw_cfg->lm.count; i++) अणु
		काष्ठा mdp5_hw_mixer *mixer;

		mixer = mdp5_mixer_init(&hw_cfg->lm.instances[i]);
		अगर (IS_ERR(mixer)) अणु
			ret = PTR_ERR(mixer);
			DRM_DEV_ERROR(dev->dev, "failed to construct LM%d (%d)\n",
				i, ret);
			वापस ret;
		पूर्ण

		mixer->idx = mdp5_kms->num_hwmixers;
		mdp5_kms->hwmixers[mdp5_kms->num_hwmixers++] = mixer;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerface_init(काष्ठा mdp5_kms *mdp5_kms)
अणु
	काष्ठा drm_device *dev = mdp5_kms->dev;
	स्थिर काष्ठा mdp5_cfg_hw *hw_cfg;
	स्थिर क्रमागत mdp5_पूर्णांकf_type *पूर्णांकf_types;
	पूर्णांक i;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);
	पूर्णांकf_types = hw_cfg->पूर्णांकf.connect;

	क्रम (i = 0; i < ARRAY_SIZE(hw_cfg->पूर्णांकf.connect); i++) अणु
		काष्ठा mdp5_पूर्णांकerface *पूर्णांकf;

		अगर (पूर्णांकf_types[i] == INTF_DISABLED)
			जारी;

		पूर्णांकf = kzalloc(माप(*पूर्णांकf), GFP_KERNEL);
		अगर (!पूर्णांकf) अणु
			DRM_DEV_ERROR(dev->dev, "failed to construct INTF%d\n", i);
			वापस -ENOMEM;
		पूर्ण

		पूर्णांकf->num = i;
		पूर्णांकf->type = पूर्णांकf_types[i];
		पूर्णांकf->mode = MDP5_INTF_MODE_NONE;
		पूर्णांकf->idx = mdp5_kms->num_पूर्णांकfs;
		mdp5_kms->पूर्णांकfs[mdp5_kms->num_पूर्णांकfs++] = पूर्णांकf;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mdp5_init(काष्ठा platक्रमm_device *pdev, काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा mdp5_kms *mdp5_kms;
	काष्ठा mdp5_cfg *config;
	u32 major, minor;
	पूर्णांक ret;

	mdp5_kms = devm_kzalloc(&pdev->dev, माप(*mdp5_kms), GFP_KERNEL);
	अगर (!mdp5_kms) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mdp5_kms);

	spin_lock_init(&mdp5_kms->resource_lock);

	mdp5_kms->dev = dev;
	mdp5_kms->pdev = pdev;

	ret = mdp5_global_obj_init(mdp5_kms);
	अगर (ret)
		जाओ fail;

	mdp5_kms->mmio = msm_ioremap(pdev, "mdp_phys", "MDP5");
	अगर (IS_ERR(mdp5_kms->mmio)) अणु
		ret = PTR_ERR(mdp5_kms->mmio);
		जाओ fail;
	पूर्ण

	/* mandatory घड़ीs: */
	ret = get_clk(pdev, &mdp5_kms->axi_clk, "bus", true);
	अगर (ret)
		जाओ fail;
	ret = get_clk(pdev, &mdp5_kms->ahb_clk, "iface", true);
	अगर (ret)
		जाओ fail;
	ret = get_clk(pdev, &mdp5_kms->core_clk, "core", true);
	अगर (ret)
		जाओ fail;
	ret = get_clk(pdev, &mdp5_kms->vsync_clk, "vsync", true);
	अगर (ret)
		जाओ fail;

	/* optional घड़ीs: */
	get_clk(pdev, &mdp5_kms->lut_clk, "lut", false);
	get_clk(pdev, &mdp5_kms->tbu_clk, "tbu", false);
	get_clk(pdev, &mdp5_kms->tbu_rt_clk, "tbu_rt", false);

	/* we need to set a शेष rate beक्रमe enabling.  Set a safe
	 * rate first, then figure out hw revision, and then set a
	 * more optimal rate:
	 */
	clk_set_rate(mdp5_kms->core_clk, 200000000);

	pm_runसमय_enable(&pdev->dev);
	mdp5_kms->rpm_enabled = true;

	पढ़ो_mdp_hw_revision(mdp5_kms, &major, &minor);

	mdp5_kms->cfg = mdp5_cfg_init(mdp5_kms, major, minor);
	अगर (IS_ERR(mdp5_kms->cfg)) अणु
		ret = PTR_ERR(mdp5_kms->cfg);
		mdp5_kms->cfg = शून्य;
		जाओ fail;
	पूर्ण

	config = mdp5_cfg_get_config(mdp5_kms->cfg);
	mdp5_kms->caps = config->hw->mdp.caps;

	/* TODO: compute core घड़ी rate at runसमय */
	clk_set_rate(mdp5_kms->core_clk, config->hw->max_clk);

	/*
	 * Some chipsets have a Shared Memory Pool (SMP), जबतक others
	 * have dedicated latency buffering per source pipe instead;
	 * this section initializes the SMP:
	 */
	अगर (mdp5_kms->caps & MDP_CAP_SMP) अणु
		mdp5_kms->smp = mdp5_smp_init(mdp5_kms, &config->hw->smp);
		अगर (IS_ERR(mdp5_kms->smp)) अणु
			ret = PTR_ERR(mdp5_kms->smp);
			mdp5_kms->smp = शून्य;
			जाओ fail;
		पूर्ण
	पूर्ण

	mdp5_kms->ctlm = mdp5_ctlm_init(dev, mdp5_kms->mmio, mdp5_kms->cfg);
	अगर (IS_ERR(mdp5_kms->ctlm)) अणु
		ret = PTR_ERR(mdp5_kms->ctlm);
		mdp5_kms->ctlm = शून्य;
		जाओ fail;
	पूर्ण

	ret = hwpipe_init(mdp5_kms);
	अगर (ret)
		जाओ fail;

	ret = hwmixer_init(mdp5_kms);
	अगर (ret)
		जाओ fail;

	ret = पूर्णांकerface_init(mdp5_kms);
	अगर (ret)
		जाओ fail;

	/* set uninit-ed kms */
	priv->kms = &mdp5_kms->base.base;

	वापस 0;
fail:
	अगर (mdp5_kms)
		mdp5_destroy(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक mdp5_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(master);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	DBG("");

	वापस mdp5_init(pdev, ddev);
पूर्ण

अटल व्योम mdp5_unbind(काष्ठा device *dev, काष्ठा device *master,
			व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	mdp5_destroy(pdev);
पूर्ण

अटल स्थिर काष्ठा component_ops mdp5_ops = अणु
	.bind   = mdp5_bind,
	.unbind = mdp5_unbind,
पूर्ण;

अटल पूर्णांक mdp5_setup_पूर्णांकerconnect(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा icc_path *path0 = of_icc_get(&pdev->dev, "mdp0-mem");
	काष्ठा icc_path *path1 = of_icc_get(&pdev->dev, "mdp1-mem");
	काष्ठा icc_path *path_rot = of_icc_get(&pdev->dev, "rotator-mem");

	अगर (IS_ERR(path0))
		वापस PTR_ERR(path0);

	अगर (!path0) अणु
		/* no पूर्णांकerconnect support is not necessarily a fatal
		 * condition, the platक्रमm may simply not have an
		 * पूर्णांकerconnect driver yet.  But warn about it in हाल
		 * bootloader didn't setup bus घड़ीs high enough क्रम
		 * scanout.
		 */
		dev_warn(&pdev->dev, "No interconnect support may cause display underflows!\n");
		वापस 0;
	पूर्ण

	icc_set_bw(path0, 0, MBps_to_icc(6400));

	अगर (!IS_ERR_OR_शून्य(path1))
		icc_set_bw(path1, 0, MBps_to_icc(6400));
	अगर (!IS_ERR_OR_शून्य(path_rot))
		icc_set_bw(path_rot, 0, MBps_to_icc(6400));

	वापस 0;
पूर्ण

अटल पूर्णांक mdp5_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	DBG("");

	ret = mdp5_setup_पूर्णांकerconnect(pdev);
	अगर (ret)
		वापस ret;

	वापस component_add(&pdev->dev, &mdp5_ops);
पूर्ण

अटल पूर्णांक mdp5_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	DBG("");
	component_del(&pdev->dev, &mdp5_ops);
	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक mdp5_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा mdp5_kms *mdp5_kms = platक्रमm_get_drvdata(pdev);

	DBG("");

	वापस mdp5_disable(mdp5_kms);
पूर्ण

अटल __maybe_unused पूर्णांक mdp5_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा mdp5_kms *mdp5_kms = platक्रमm_get_drvdata(pdev);

	DBG("");

	वापस mdp5_enable(mdp5_kms);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mdp5_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mdp5_runसमय_suspend, mdp5_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mdp5_dt_match[] = अणु
	अणु .compatible = "qcom,mdp5", पूर्ण,
	/* to support करोwnstream DT files */
	अणु .compatible = "qcom,mdss_mdp", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mdp5_dt_match);

अटल काष्ठा platक्रमm_driver mdp5_driver = अणु
	.probe = mdp5_dev_probe,
	.हटाओ = mdp5_dev_हटाओ,
	.driver = अणु
		.name = "msm_mdp",
		.of_match_table = mdp5_dt_match,
		.pm = &mdp5_pm_ops,
	पूर्ण,
पूर्ण;

व्योम __init msm_mdp_रेजिस्टर(व्योम)
अणु
	DBG("");
	platक्रमm_driver_रेजिस्टर(&mdp5_driver);
पूर्ण

व्योम __निकास msm_mdp_unरेजिस्टर(व्योम)
अणु
	DBG("");
	platक्रमm_driver_unरेजिस्टर(&mdp5_driver);
पूर्ण
