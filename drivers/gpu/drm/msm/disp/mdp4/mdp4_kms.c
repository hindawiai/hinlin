<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/delay.h>

#समावेश <drm/drm_vblank.h>

#समावेश "msm_drv.h"
#समावेश "msm_gem.h"
#समावेश "msm_mmu.h"
#समावेश "mdp4_kms.h"

अटल काष्ठा mdp4_platक्रमm_config *mdp4_get_config(काष्ठा platक्रमm_device *dev);

अटल पूर्णांक mdp4_hw_init(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	काष्ठा drm_device *dev = mdp4_kms->dev;
	uपूर्णांक32_t version, major, minor, dmap_cfg, vg_cfg;
	अचिन्हित दीर्घ clk;
	पूर्णांक ret = 0;

	pm_runसमय_get_sync(dev->dev);

	mdp4_enable(mdp4_kms);
	version = mdp4_पढ़ो(mdp4_kms, REG_MDP4_VERSION);
	mdp4_disable(mdp4_kms);

	major = FIELD(version, MDP4_VERSION_MAJOR);
	minor = FIELD(version, MDP4_VERSION_MINOR);

	DBG("found MDP4 version v%d.%d", major, minor);

	अगर (major != 4) अणु
		DRM_DEV_ERROR(dev->dev, "unexpected MDP version: v%d.%d\n",
				major, minor);
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	mdp4_kms->rev = minor;

	अगर (mdp4_kms->rev > 1) अणु
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_CS_CONTROLLER0, 0x0707ffff);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_CS_CONTROLLER1, 0x03073f3f);
	पूर्ण

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PORTMAP_MODE, 0x3);

	/* max पढ़ो pending cmd config, 3 pending requests: */
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_READ_CNFG, 0x02222);

	clk = clk_get_rate(mdp4_kms->clk);

	अगर ((mdp4_kms->rev >= 1) || (clk >= 90000000)) अणु
		dmap_cfg = 0x47;     /* 16 bytes-burst x 8 req */
		vg_cfg = 0x47;       /* 16 bytes-burs x 8 req */
	पूर्ण अन्यथा अणु
		dmap_cfg = 0x27;     /* 8 bytes-burst x 8 req */
		vg_cfg = 0x43;       /* 16 bytes-burst x 4 req */
	पूर्ण

	DBG("fetch config: dmap=%02x, vg=%02x", dmap_cfg, vg_cfg);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_FETCH_CONFIG(DMA_P), dmap_cfg);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_FETCH_CONFIG(DMA_E), dmap_cfg);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_FETCH_CONFIG(VG1), vg_cfg);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_FETCH_CONFIG(VG2), vg_cfg);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_FETCH_CONFIG(RGB1), vg_cfg);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_FETCH_CONFIG(RGB2), vg_cfg);

	अगर (mdp4_kms->rev >= 2)
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LAYERMIXER_IN_CFG_UPDATE_METHOD, 1);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LAYERMIXER_IN_CFG, 0);

	/* disable CSC matrix / YUV by शेष: */
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_OP_MODE(VG1), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_PIPE_OP_MODE(VG2), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_P_OP_MODE, 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_S_OP_MODE, 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_CSC_CONFIG(1), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_CSC_CONFIG(2), 0);

	अगर (mdp4_kms->rev > 1)
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_RESET_STATUS, 1);

	dev->mode_config.allow_fb_modअगरiers = true;

out:
	pm_runसमय_put_sync(dev->dev);

	वापस ret;
पूर्ण

अटल व्योम mdp4_enable_commit(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	mdp4_enable(mdp4_kms);
पूर्ण

अटल व्योम mdp4_disable_commit(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	mdp4_disable(mdp4_kms);
पूर्ण

अटल व्योम mdp4_prepare_commit(काष्ठा msm_kms *kms, काष्ठा drm_atomic_state *state)
अणु
	पूर्णांक i;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;

	/* see 119ecb7fd */
	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i)
		drm_crtc_vblank_get(crtc);
पूर्ण

अटल व्योम mdp4_flush_commit(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	/* TODO */
पूर्ण

अटल व्योम mdp4_रुको_flush(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	काष्ठा drm_crtc *crtc;

	क्रम_each_crtc_mask(mdp4_kms->dev, crtc, crtc_mask)
		mdp4_crtc_रुको_क्रम_commit_करोne(crtc);
पूर्ण

अटल व्योम mdp4_complete_commit(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	काष्ठा drm_crtc *crtc;

	/* see 119ecb7fd */
	क्रम_each_crtc_mask(mdp4_kms->dev, crtc, crtc_mask)
		drm_crtc_vblank_put(crtc);
पूर्ण

अटल दीर्घ mdp4_round_pixclk(काष्ठा msm_kms *kms, अचिन्हित दीर्घ rate,
		काष्ठा drm_encoder *encoder)
अणु
	/* अगर we had >1 encoder, we'd need something more clever: */
	चयन (encoder->encoder_type) अणु
	हाल DRM_MODE_ENCODER_TMDS:
		वापस mdp4_dtv_round_pixclk(encoder, rate);
	हाल DRM_MODE_ENCODER_LVDS:
	हाल DRM_MODE_ENCODER_DSI:
	शेष:
		वापस rate;
	पूर्ण
पूर्ण

अटल व्योम mdp4_destroy(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	काष्ठा device *dev = mdp4_kms->dev->dev;
	काष्ठा msm_gem_address_space *aspace = kms->aspace;

	अगर (mdp4_kms->blank_cursor_iova)
		msm_gem_unpin_iova(mdp4_kms->blank_cursor_bo, kms->aspace);
	drm_gem_object_put(mdp4_kms->blank_cursor_bo);

	अगर (aspace) अणु
		aspace->mmu->funcs->detach(aspace->mmu);
		msm_gem_address_space_put(aspace);
	पूर्ण

	अगर (mdp4_kms->rpm_enabled)
		pm_runसमय_disable(dev);

	mdp_kms_destroy(&mdp4_kms->base);

	kमुक्त(mdp4_kms);
पूर्ण

अटल स्थिर काष्ठा mdp_kms_funcs kms_funcs = अणु
	.base = अणु
		.hw_init         = mdp4_hw_init,
		.irq_preinstall  = mdp4_irq_preinstall,
		.irq_postinstall = mdp4_irq_postinstall,
		.irq_uninstall   = mdp4_irq_uninstall,
		.irq             = mdp4_irq,
		.enable_vblank   = mdp4_enable_vblank,
		.disable_vblank  = mdp4_disable_vblank,
		.enable_commit   = mdp4_enable_commit,
		.disable_commit  = mdp4_disable_commit,
		.prepare_commit  = mdp4_prepare_commit,
		.flush_commit    = mdp4_flush_commit,
		.रुको_flush      = mdp4_रुको_flush,
		.complete_commit = mdp4_complete_commit,
		.get_क्रमmat      = mdp_get_क्रमmat,
		.round_pixclk    = mdp4_round_pixclk,
		.destroy         = mdp4_destroy,
	पूर्ण,
	.set_irqmask         = mdp4_set_irqmask,
पूर्ण;

पूर्णांक mdp4_disable(काष्ठा mdp4_kms *mdp4_kms)
अणु
	DBG("");

	clk_disable_unprepare(mdp4_kms->clk);
	अगर (mdp4_kms->pclk)
		clk_disable_unprepare(mdp4_kms->pclk);
	अगर (mdp4_kms->lut_clk)
		clk_disable_unprepare(mdp4_kms->lut_clk);
	अगर (mdp4_kms->axi_clk)
		clk_disable_unprepare(mdp4_kms->axi_clk);

	वापस 0;
पूर्ण

पूर्णांक mdp4_enable(काष्ठा mdp4_kms *mdp4_kms)
अणु
	DBG("");

	clk_prepare_enable(mdp4_kms->clk);
	अगर (mdp4_kms->pclk)
		clk_prepare_enable(mdp4_kms->pclk);
	अगर (mdp4_kms->lut_clk)
		clk_prepare_enable(mdp4_kms->lut_clk);
	अगर (mdp4_kms->axi_clk)
		clk_prepare_enable(mdp4_kms->axi_clk);

	वापस 0;
पूर्ण


अटल पूर्णांक mdp4_modeset_init_पूर्णांकf(काष्ठा mdp4_kms *mdp4_kms,
				  पूर्णांक पूर्णांकf_type)
अणु
	काष्ठा drm_device *dev = mdp4_kms->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	काष्ठा device_node *panel_node;
	पूर्णांक dsi_id;
	पूर्णांक ret;

	चयन (पूर्णांकf_type) अणु
	हाल DRM_MODE_ENCODER_LVDS:
		/*
		 * bail out early अगर there is no panel node (no need to
		 * initialize LCDC encoder and LVDS connector)
		 */
		panel_node = of_graph_get_remote_node(dev->dev->of_node, 0, 0);
		अगर (!panel_node)
			वापस 0;

		encoder = mdp4_lcdc_encoder_init(dev, panel_node);
		अगर (IS_ERR(encoder)) अणु
			DRM_DEV_ERROR(dev->dev, "failed to construct LCDC encoder\n");
			वापस PTR_ERR(encoder);
		पूर्ण

		/* LCDC can be hooked to DMA_P (TODO: Add DMA_S later?) */
		encoder->possible_crtcs = 1 << DMA_P;

		connector = mdp4_lvds_connector_init(dev, panel_node, encoder);
		अगर (IS_ERR(connector)) अणु
			DRM_DEV_ERROR(dev->dev, "failed to initialize LVDS connector\n");
			वापस PTR_ERR(connector);
		पूर्ण

		priv->encoders[priv->num_encoders++] = encoder;
		priv->connectors[priv->num_connectors++] = connector;

		अवरोध;
	हाल DRM_MODE_ENCODER_TMDS:
		encoder = mdp4_dtv_encoder_init(dev);
		अगर (IS_ERR(encoder)) अणु
			DRM_DEV_ERROR(dev->dev, "failed to construct DTV encoder\n");
			वापस PTR_ERR(encoder);
		पूर्ण

		/* DTV can be hooked to DMA_E: */
		encoder->possible_crtcs = 1 << 1;

		अगर (priv->hdmi) अणु
			/* Conकाष्ठा bridge/connector क्रम HDMI: */
			ret = msm_hdmi_modeset_init(priv->hdmi, dev, encoder);
			अगर (ret) अणु
				DRM_DEV_ERROR(dev->dev, "failed to initialize HDMI: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण

		priv->encoders[priv->num_encoders++] = encoder;

		अवरोध;
	हाल DRM_MODE_ENCODER_DSI:
		/* only DSI1 supported क्रम now */
		dsi_id = 0;

		अगर (!priv->dsi[dsi_id])
			अवरोध;

		encoder = mdp4_dsi_encoder_init(dev);
		अगर (IS_ERR(encoder)) अणु
			ret = PTR_ERR(encoder);
			DRM_DEV_ERROR(dev->dev,
				"failed to construct DSI encoder: %d\n", ret);
			वापस ret;
		पूर्ण

		/* TODO: Add DMA_S later? */
		encoder->possible_crtcs = 1 << DMA_P;
		priv->encoders[priv->num_encoders++] = encoder;

		ret = msm_dsi_modeset_init(priv->dsi[dsi_id], dev, encoder);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to initialize DSI: %d\n",
				ret);
			वापस ret;
		पूर्ण

		अवरोध;
	शेष:
		DRM_DEV_ERROR(dev->dev, "Invalid or unsupported interface\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक modeset_init(काष्ठा mdp4_kms *mdp4_kms)
अणु
	काष्ठा drm_device *dev = mdp4_kms->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_plane *plane;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i, ret;
	अटल स्थिर क्रमागत mdp4_pipe rgb_planes[] = अणु
		RGB1, RGB2,
	पूर्ण;
	अटल स्थिर क्रमागत mdp4_pipe vg_planes[] = अणु
		VG1, VG2,
	पूर्ण;
	अटल स्थिर क्रमागत mdp4_dma mdp4_crtcs[] = अणु
		DMA_P, DMA_E,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर mdp4_crtc_names[] = अणु
		"DMA_P", "DMA_E",
	पूर्ण;
	अटल स्थिर पूर्णांक mdp4_पूर्णांकfs[] = अणु
		DRM_MODE_ENCODER_LVDS,
		DRM_MODE_ENCODER_DSI,
		DRM_MODE_ENCODER_TMDS,
	पूर्ण;

	/* स्थिरruct non-निजी planes: */
	क्रम (i = 0; i < ARRAY_SIZE(vg_planes); i++) अणु
		plane = mdp4_plane_init(dev, vg_planes[i], false);
		अगर (IS_ERR(plane)) अणु
			DRM_DEV_ERROR(dev->dev,
				"failed to construct plane for VG%d\n", i + 1);
			ret = PTR_ERR(plane);
			जाओ fail;
		पूर्ण
		priv->planes[priv->num_planes++] = plane;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mdp4_crtcs); i++) अणु
		plane = mdp4_plane_init(dev, rgb_planes[i], true);
		अगर (IS_ERR(plane)) अणु
			DRM_DEV_ERROR(dev->dev,
				"failed to construct plane for RGB%d\n", i + 1);
			ret = PTR_ERR(plane);
			जाओ fail;
		पूर्ण

		crtc  = mdp4_crtc_init(dev, plane, priv->num_crtcs, i,
				mdp4_crtcs[i]);
		अगर (IS_ERR(crtc)) अणु
			DRM_DEV_ERROR(dev->dev, "failed to construct crtc for %s\n",
				mdp4_crtc_names[i]);
			ret = PTR_ERR(crtc);
			जाओ fail;
		पूर्ण

		priv->crtcs[priv->num_crtcs++] = crtc;
	पूर्ण

	/*
	 * we currently set up two relatively fixed paths:
	 *
	 * LCDC/LVDS path: RGB1 -> DMA_P -> LCDC -> LVDS
	 *			or
	 * DSI path: RGB1 -> DMA_P -> DSI1 -> DSI Panel
	 *
	 * DTV/HDMI path: RGB2 -> DMA_E -> DTV -> HDMI
	 */

	क्रम (i = 0; i < ARRAY_SIZE(mdp4_पूर्णांकfs); i++) अणु
		ret = mdp4_modeset_init_पूर्णांकf(mdp4_kms, mdp4_पूर्णांकfs[i]);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to initialize intf: %d, %d\n",
				i, ret);
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	वापस ret;
पूर्ण

काष्ठा msm_kms *mdp4_kms_init(काष्ठा drm_device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	काष्ठा mdp4_platक्रमm_config *config = mdp4_get_config(pdev);
	काष्ठा mdp4_kms *mdp4_kms;
	काष्ठा msm_kms *kms = शून्य;
	काष्ठा msm_gem_address_space *aspace;
	पूर्णांक irq, ret;

	mdp4_kms = kzalloc(माप(*mdp4_kms), GFP_KERNEL);
	अगर (!mdp4_kms) अणु
		DRM_DEV_ERROR(dev->dev, "failed to allocate kms\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	ret = mdp_kms_init(&mdp4_kms->base, &kms_funcs);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "failed to init kms\n");
		जाओ fail;
	पूर्ण

	kms = &mdp4_kms->base.base;

	mdp4_kms->dev = dev;

	mdp4_kms->mmio = msm_ioremap(pdev, शून्य, "MDP4");
	अगर (IS_ERR(mdp4_kms->mmio)) अणु
		ret = PTR_ERR(mdp4_kms->mmio);
		जाओ fail;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		DRM_DEV_ERROR(dev->dev, "failed to get irq: %d\n", ret);
		जाओ fail;
	पूर्ण

	kms->irq = irq;

	/* NOTE: driver क्रम this regulator still missing upstream.. use
	 * _get_exclusive() and ignore the error अगर it करोes not exist
	 * (and hope that the bootloader left it on क्रम us)
	 */
	mdp4_kms->vdd = devm_regulator_get_exclusive(&pdev->dev, "vdd");
	अगर (IS_ERR(mdp4_kms->vdd))
		mdp4_kms->vdd = शून्य;

	अगर (mdp4_kms->vdd) अणु
		ret = regulator_enable(mdp4_kms->vdd);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to enable regulator vdd: %d\n", ret);
			जाओ fail;
		पूर्ण
	पूर्ण

	mdp4_kms->clk = devm_clk_get(&pdev->dev, "core_clk");
	अगर (IS_ERR(mdp4_kms->clk)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to get core_clk\n");
		ret = PTR_ERR(mdp4_kms->clk);
		जाओ fail;
	पूर्ण

	mdp4_kms->pclk = devm_clk_get(&pdev->dev, "iface_clk");
	अगर (IS_ERR(mdp4_kms->pclk))
		mdp4_kms->pclk = शून्य;

	अगर (mdp4_kms->rev >= 2) अणु
		mdp4_kms->lut_clk = devm_clk_get(&pdev->dev, "lut_clk");
		अगर (IS_ERR(mdp4_kms->lut_clk)) अणु
			DRM_DEV_ERROR(dev->dev, "failed to get lut_clk\n");
			ret = PTR_ERR(mdp4_kms->lut_clk);
			जाओ fail;
		पूर्ण
	पूर्ण

	mdp4_kms->axi_clk = devm_clk_get(&pdev->dev, "bus_clk");
	अगर (IS_ERR(mdp4_kms->axi_clk)) अणु
		DRM_DEV_ERROR(dev->dev, "failed to get axi_clk\n");
		ret = PTR_ERR(mdp4_kms->axi_clk);
		जाओ fail;
	पूर्ण

	clk_set_rate(mdp4_kms->clk, config->max_clk);
	अगर (mdp4_kms->lut_clk)
		clk_set_rate(mdp4_kms->lut_clk, config->max_clk);

	pm_runसमय_enable(dev->dev);
	mdp4_kms->rpm_enabled = true;

	/* make sure things are off beक्रमe attaching iommu (bootloader could
	 * have left things on, in which हाल we'll start getting faults अगर
	 * we करोn't disable):
	 */
	mdp4_enable(mdp4_kms);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DTV_ENABLE, 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LCDC_ENABLE, 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DSI_ENABLE, 0);
	mdp4_disable(mdp4_kms);
	mdelay(16);

	अगर (config->iommu) अणु
		काष्ठा msm_mmu *mmu = msm_iommu_new(&pdev->dev,
			config->iommu);

		aspace  = msm_gem_address_space_create(mmu,
			"mdp4", 0x1000, 0x100000000 - 0x1000);

		अगर (IS_ERR(aspace)) अणु
			अगर (!IS_ERR(mmu))
				mmu->funcs->destroy(mmu);
			ret = PTR_ERR(aspace);
			जाओ fail;
		पूर्ण

		kms->aspace = aspace;
	पूर्ण अन्यथा अणु
		DRM_DEV_INFO(dev->dev, "no iommu, fallback to phys "
				"contig buffers for scanout\n");
		aspace = शून्य;
	पूर्ण

	ret = modeset_init(mdp4_kms);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "modeset_init failed: %d\n", ret);
		जाओ fail;
	पूर्ण

	mdp4_kms->blank_cursor_bo = msm_gem_new(dev, SZ_16K, MSM_BO_WC | MSM_BO_SCANOUT);
	अगर (IS_ERR(mdp4_kms->blank_cursor_bo)) अणु
		ret = PTR_ERR(mdp4_kms->blank_cursor_bo);
		DRM_DEV_ERROR(dev->dev, "could not allocate blank-cursor bo: %d\n", ret);
		mdp4_kms->blank_cursor_bo = शून्य;
		जाओ fail;
	पूर्ण

	ret = msm_gem_get_and_pin_iova(mdp4_kms->blank_cursor_bo, kms->aspace,
			&mdp4_kms->blank_cursor_iova);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "could not pin blank-cursor bo: %d\n", ret);
		जाओ fail;
	पूर्ण

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 2048;
	dev->mode_config.max_height = 2048;

	वापस kms;

fail:
	अगर (kms)
		mdp4_destroy(kms);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा mdp4_platक्रमm_config *mdp4_get_config(काष्ठा platक्रमm_device *dev)
अणु
	अटल काष्ठा mdp4_platक्रमm_config config = अणुपूर्ण;

	/* TODO: Chips that aren't apq8064 have a 200 Mhz max_clk */
	config.max_clk = 266667000;
	config.iommu = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);

	वापस &config;
पूर्ण
