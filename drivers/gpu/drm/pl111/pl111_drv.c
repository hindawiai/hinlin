<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) COPYRIGHT 2012-2013 ARM Limited. All rights reserved.
 *
 * Parts of this file were based on sources as follows:
 *
 * Copyright (c) 2006-2008 Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (C) 2011 Texas Instruments
 */

/**
 * DOC: ARM PrimeCell PL110 and PL111 CLCD Driver
 *
 * The PL110/PL111 is a simple LCD controller that can support TFT
 * and STN displays. This driver exposes a standard KMS पूर्णांकerface
 * क्रम them.
 *
 * The driver currently करोesn't expose the cursor.  The DRM API क्रम
 * cursors requires support क्रम 64x64 ARGB8888 cursor images, जबतक
 * the hardware can only support 64x64 monochrome with masking
 * cursors.  While one could imagine trying to hack something together
 * to look at the ARGB8888 and program reasonable in monochrome, we
 * just करोn't expose the cursor at all instead, and leave cursor
 * support to the application software cursor layer.
 *
 * TODO:
 *
 * - Fix race between setting plane base address and getting IRQ क्रम
 *   vsync firing the pageflip completion.
 *
 * - Read back hardware state at boot to skip reprogramming the
 *   hardware when करोing a no-op modeset.
 *
 * - Use the CLKSEL bit to support चयनing between the two बाह्यal
 *   घड़ी parents.
 */

#समावेश <linux/amba/bus.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/version.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "pl111_drm.h"
#समावेश "pl111_versatile.h"
#समावेश "pl111_nomadik.h"

#घोषणा DRIVER_DESC      "DRM module for PL111"

अटल स्थिर काष्ठा drm_mode_config_funcs mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक pl111_modeset_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_mode_config *mode_config;
	काष्ठा pl111_drm_dev_निजी *priv = dev->dev_निजी;
	काष्ठा device_node *np = dev->dev->of_node;
	काष्ठा device_node *remote;
	काष्ठा drm_panel *panel = शून्य;
	काष्ठा drm_bridge *bridge = शून्य;
	bool defer = false;
	पूर्णांक ret;
	पूर्णांक i;

	ret = drmm_mode_config_init(dev);
	अगर (ret)
		वापस ret;

	mode_config = &dev->mode_config;
	mode_config->funcs = &mode_config_funcs;
	mode_config->min_width = 1;
	mode_config->max_width = 1024;
	mode_config->min_height = 1;
	mode_config->max_height = 768;

	i = 0;
	क्रम_each_endpoपूर्णांक_of_node(np, remote) अणु
		काष्ठा drm_panel *पंचांगp_panel;
		काष्ठा drm_bridge *पंचांगp_bridge;

		dev_dbg(dev->dev, "checking endpoint %d\n", i);

		ret = drm_of_find_panel_or_bridge(dev->dev->of_node,
						  0, i,
						  &पंचांगp_panel,
						  &पंचांगp_bridge);
		अगर (ret) अणु
			अगर (ret == -EPROBE_DEFER) अणु
				/*
				 * Something deferred, but that is often just
				 * another way of saying -ENODEV, but let's
				 * cast a vote क्रम later deferral.
				 */
				defer = true;
			पूर्ण अन्यथा अगर (ret != -ENODEV) अणु
				/* Continue, maybe something अन्यथा is working */
				dev_err(dev->dev,
					"endpoint %d returns %d\n", i, ret);
			पूर्ण
		पूर्ण

		अगर (पंचांगp_panel) अणु
			dev_info(dev->dev,
				 "found panel on endpoint %d\n", i);
			panel = पंचांगp_panel;
		पूर्ण
		अगर (पंचांगp_bridge) अणु
			dev_info(dev->dev,
				 "found bridge on endpoint %d\n", i);
			bridge = पंचांगp_bridge;
		पूर्ण

		i++;
	पूर्ण

	/*
	 * If we can't find neither panel nor bridge on any of the
	 * endpoपूर्णांकs, and any of them retured -EPROBE_DEFER, then
	 * let's defer this driver too.
	 */
	अगर ((!panel && !bridge) && defer)
		वापस -EPROBE_DEFER;

	अगर (panel) अणु
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_Unknown);
		अगर (IS_ERR(bridge)) अणु
			ret = PTR_ERR(bridge);
			जाओ finish;
		पूर्ण
	पूर्ण अन्यथा अगर (bridge) अणु
		dev_info(dev->dev, "Using non-panel bridge\n");
	पूर्ण अन्यथा अणु
		dev_err(dev->dev, "No bridge, exiting\n");
		वापस -ENODEV;
	पूर्ण

	priv->bridge = bridge;
	अगर (panel) अणु
		priv->panel = panel;
		priv->connector = drm_panel_bridge_connector(bridge);
	पूर्ण

	ret = pl111_display_init(dev);
	अगर (ret != 0) अणु
		dev_err(dev->dev, "Failed to init display\n");
		जाओ out_bridge;
	पूर्ण

	ret = drm_simple_display_pipe_attach_bridge(&priv->pipe,
						    bridge);
	अगर (ret)
		वापस ret;

	अगर (!priv->variant->broken_vblank) अणु
		ret = drm_vblank_init(dev, 1);
		अगर (ret != 0) अणु
			dev_err(dev->dev, "Failed to init vblank\n");
			जाओ out_bridge;
		पूर्ण
	पूर्ण

	drm_mode_config_reset(dev);

	drm_kms_helper_poll_init(dev);

	जाओ finish;

out_bridge:
	अगर (panel)
		drm_panel_bridge_हटाओ(bridge);
finish:
	वापस ret;
पूर्ण

अटल काष्ठा drm_gem_object *
pl111_gem_import_sg_table(काष्ठा drm_device *dev,
			  काष्ठा dma_buf_attachment *attach,
			  काष्ठा sg_table *sgt)
अणु
	काष्ठा pl111_drm_dev_निजी *priv = dev->dev_निजी;

	/*
	 * When using device-specअगरic reserved memory we can't import
	 * DMA buffers: those are passed by reference in any global
	 * memory and we can only handle a specअगरic range of memory.
	 */
	अगर (priv->use_device_memory)
		वापस ERR_PTR(-EINVAL);

	वापस drm_gem_cma_prime_import_sg_table(dev, attach, sgt);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(drm_fops);

अटल स्थिर काष्ठा drm_driver pl111_drm_driver = अणु
	.driver_features =
		DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.ioctls = शून्य,
	.fops = &drm_fops,
	.name = "pl111",
	.desc = DRIVER_DESC,
	.date = "20170317",
	.major = 1,
	.minor = 0,
	.patchlevel = 0,
	.dumb_create = drm_gem_cma_dumb_create,
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = pl111_gem_import_sg_table,
	.gem_prime_mmap = drm_gem_prime_mmap,

#अगर defined(CONFIG_DEBUG_FS)
	.debugfs_init = pl111_debugfs_init,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक pl111_amba_probe(काष्ठा amba_device *amba_dev,
			    स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा device *dev = &amba_dev->dev;
	काष्ठा pl111_drm_dev_निजी *priv;
	स्थिर काष्ठा pl111_variant_data *variant = id->data;
	काष्ठा drm_device *drm;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	drm = drm_dev_alloc(&pl111_drm_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);
	amba_set_drvdata(amba_dev, drm);
	priv->drm = drm;
	drm->dev_निजी = priv;
	priv->variant = variant;

	ret = of_reserved_mem_device_init(dev);
	अगर (!ret) अणु
		dev_info(dev, "using device-specific reserved memory\n");
		priv->use_device_memory = true;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "max-memory-bandwidth",
				 &priv->memory_bw)) अणु
		dev_info(dev, "no max memory bandwidth specified, assume unlimited\n");
		priv->memory_bw = 0;
	पूर्ण

	/* The two मुख्य variants swap this रेजिस्टर */
	अगर (variant->is_pl110 || variant->is_lcdc) अणु
		priv->ienb = CLCD_PL110_IENB;
		priv->ctrl = CLCD_PL110_CNTL;
	पूर्ण अन्यथा अणु
		priv->ienb = CLCD_PL111_IENB;
		priv->ctrl = CLCD_PL111_CNTL;
	पूर्ण

	priv->regs = devm_ioremap_resource(dev, &amba_dev->res);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "%s failed mmio\n", __func__);
		ret = PTR_ERR(priv->regs);
		जाओ dev_put;
	पूर्ण

	/* This may override some variant settings */
	ret = pl111_versatile_init(dev, priv);
	अगर (ret)
		जाओ dev_put;

	pl111_nomadik_init(dev);

	/* turn off पूर्णांकerrupts beक्रमe requesting the irq */
	ग_लिखोl(0, priv->regs + priv->ienb);

	ret = devm_request_irq(dev, amba_dev->irq[0], pl111_irq, 0,
			       variant->name, priv);
	अगर (ret != 0) अणु
		dev_err(dev, "%s failed irq %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = pl111_modeset_init(drm);
	अगर (ret != 0)
		जाओ dev_put;

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0)
		जाओ dev_put;

	drm_fbdev_generic_setup(drm, priv->variant->fb_bpp);

	वापस 0;

dev_put:
	drm_dev_put(drm);
	of_reserved_mem_device_release(dev);

	वापस ret;
पूर्ण

अटल व्योम pl111_amba_हटाओ(काष्ठा amba_device *amba_dev)
अणु
	काष्ठा device *dev = &amba_dev->dev;
	काष्ठा drm_device *drm = amba_get_drvdata(amba_dev);
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;

	drm_dev_unरेजिस्टर(drm);
	अगर (priv->panel)
		drm_panel_bridge_हटाओ(priv->bridge);
	drm_dev_put(drm);
	of_reserved_mem_device_release(dev);
पूर्ण

/*
 * This early variant lacks the 565 and 444 pixel क्रमmats.
 */
अटल स्थिर u32 pl110_pixel_क्रमmats[] = अणु
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
पूर्ण;

अटल स्थिर काष्ठा pl111_variant_data pl110_variant = अणु
	.name = "PL110",
	.is_pl110 = true,
	.क्रमmats = pl110_pixel_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(pl110_pixel_क्रमmats),
	.fb_bpp = 16,
पूर्ण;

/* RealView, Versatile Express etc use this modern variant */
अटल स्थिर u32 pl111_pixel_क्रमmats[] = अणु
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_XBGR4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_XRGB4444,
पूर्ण;

अटल स्थिर काष्ठा pl111_variant_data pl111_variant = अणु
	.name = "PL111",
	.क्रमmats = pl111_pixel_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(pl111_pixel_क्रमmats),
	.fb_bpp = 32,
पूर्ण;

अटल स्थिर u32 pl110_nomadik_pixel_क्रमmats[] = अणु
	DRM_FORMAT_RGB888,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_XBGR4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_XRGB4444,
पूर्ण;

अटल स्थिर काष्ठा pl111_variant_data pl110_nomadik_variant = अणु
	.name = "LCDC (PL110 Nomadik)",
	.क्रमmats = pl110_nomadik_pixel_क्रमmats,
	.nक्रमmats = ARRAY_SIZE(pl110_nomadik_pixel_क्रमmats),
	.is_lcdc = true,
	.st_biपंचांगux_control = true,
	.broken_vblank = true,
	.fb_bpp = 16,
पूर्ण;

अटल स्थिर काष्ठा amba_id pl111_id_table[] = अणु
	अणु
		.id = 0x00041110,
		.mask = 0x000fffff,
		.data = (व्योम *)&pl110_variant,
	पूर्ण,
	अणु
		.id = 0x00180110,
		.mask = 0x00fffffe,
		.data = (व्योम *)&pl110_nomadik_variant,
	पूर्ण,
	अणु
		.id = 0x00041111,
		.mask = 0x000fffff,
		.data = (व्योम *)&pl111_variant,
	पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(amba, pl111_id_table);

अटल काष्ठा amba_driver pl111_amba_driver __maybe_unused = अणु
	.drv = अणु
		.name = "drm-clcd-pl111",
	पूर्ण,
	.probe = pl111_amba_probe,
	.हटाओ = pl111_amba_हटाओ,
	.id_table = pl111_id_table,
पूर्ण;

#अगर_घोषित CONFIG_ARM_AMBA
module_amba_driver(pl111_amba_driver);
#पूर्ण_अगर

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("ARM Ltd.");
MODULE_LICENSE("GPL");
