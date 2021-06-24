<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 * Parts of this file were based on sources as follows:
 *
 * Copyright (C) 2006-2008 Intel Corporation
 * Copyright (C) 2007 Amos Lee <amos_lee@storlinksemi.com>
 * Copyright (C) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (C) 2011 Texas Instruments
 * Copyright (C) 2017 Eric Anholt
 */

/**
 * DOC: Faraday TV Encoder TVE200 DRM Driver
 *
 * The Faraday TV Encoder TVE200 is also known as the Gemini TV Interface
 * Controller (TVC) and is found in the Gemini Chipset from Storlink
 * Semiconductor (later Storm Semiconductor, later Cortina Systems)
 * but also in the Grain Media GM8180 chipset. On the Gemini the module
 * is connected to 8 data lines and a single घड़ी line, comprising an
 * 8-bit BT.656 पूर्णांकerface.
 *
 * This is a very basic YUV display driver. The datasheet specअगरies that
 * it supports the ITU BT.656 standard. It requires a 27 MHz घड़ी which is
 * the hallmark of any TV encoder supporting both PAL and NTSC.
 *
 * This driver exposes a standard KMS पूर्णांकerface क्रम this TV encoder.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/slab.h>

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

#समावेश "tve200_drm.h"

#घोषणा DRIVER_DESC      "DRM module for Faraday TVE200"

अटल स्थिर काष्ठा drm_mode_config_funcs mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक tve200_modeset_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_mode_config *mode_config;
	काष्ठा tve200_drm_dev_निजी *priv = dev->dev_निजी;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret = 0;

	drm_mode_config_init(dev);
	mode_config = &dev->mode_config;
	mode_config->funcs = &mode_config_funcs;
	mode_config->min_width = 352;
	mode_config->max_width = 720;
	mode_config->min_height = 240;
	mode_config->max_height = 576;

	ret = drm_of_find_panel_or_bridge(dev->dev->of_node,
					  0, 0, &panel, &bridge);
	अगर (ret && ret != -ENODEV)
		वापस ret;
	अगर (panel) अणु
		bridge = drm_panel_bridge_add_typed(panel,
						    DRM_MODE_CONNECTOR_Unknown);
		अगर (IS_ERR(bridge)) अणु
			ret = PTR_ERR(bridge);
			जाओ out_bridge;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * TODO: when we are using a dअगरferent bridge than a panel
		 * (such as a dumb VGA connector) we need to devise a dअगरferent
		 * method to get the connector out of the bridge.
		 */
		dev_err(dev->dev, "the bridge is not a panel\n");
		जाओ out_bridge;
	पूर्ण

	ret = tve200_display_init(dev);
	अगर (ret) अणु
		dev_err(dev->dev, "failed to init display\n");
		जाओ out_bridge;
	पूर्ण

	ret = drm_simple_display_pipe_attach_bridge(&priv->pipe,
						    bridge);
	अगर (ret) अणु
		dev_err(dev->dev, "failed to attach bridge\n");
		जाओ out_bridge;
	पूर्ण

	priv->panel = panel;
	priv->connector = drm_panel_bridge_connector(bridge);
	priv->bridge = bridge;

	dev_info(dev->dev, "attached to panel %s\n",
		 dev_name(panel->dev));

	ret = drm_vblank_init(dev, 1);
	अगर (ret) अणु
		dev_err(dev->dev, "failed to init vblank\n");
		जाओ out_bridge;
	पूर्ण

	drm_mode_config_reset(dev);
	drm_kms_helper_poll_init(dev);

	जाओ finish;

out_bridge:
	अगर (panel)
		drm_panel_bridge_हटाओ(bridge);
	drm_mode_config_cleanup(dev);
finish:
	वापस ret;
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(drm_fops);

अटल स्थिर काष्ठा drm_driver tve200_drm_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.ioctls = शून्य,
	.fops = &drm_fops,
	.name = "tve200",
	.desc = DRIVER_DESC,
	.date = "20170703",
	.major = 1,
	.minor = 0,
	.patchlevel = 0,
	DRM_GEM_CMA_DRIVER_OPS,
पूर्ण;

अटल पूर्णांक tve200_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tve200_drm_dev_निजी *priv;
	काष्ठा drm_device *drm;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	drm = drm_dev_alloc(&tve200_drm_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);
	platक्रमm_set_drvdata(pdev, drm);
	priv->drm = drm;
	drm->dev_निजी = priv;

	/* Clock the silicon so we can access the रेजिस्टरs */
	priv->pclk = devm_clk_get(dev, "PCLK");
	अगर (IS_ERR(priv->pclk)) अणु
		dev_err(dev, "unable to get PCLK\n");
		ret = PTR_ERR(priv->pclk);
		जाओ dev_unref;
	पूर्ण
	ret = clk_prepare_enable(priv->pclk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable PCLK\n");
		जाओ dev_unref;
	पूर्ण

	/* This घड़ी is क्रम the pixels (27MHz) */
	priv->clk = devm_clk_get(dev, "TVE");
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "unable to get TVE clock\n");
		ret = PTR_ERR(priv->clk);
		जाओ clk_disable;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->regs)) अणु
		dev_err(dev, "%s failed mmio\n", __func__);
		ret = -EINVAL;
		जाओ clk_disable;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ clk_disable;
	पूर्ण

	/* turn off पूर्णांकerrupts beक्रमe requesting the irq */
	ग_लिखोl(0, priv->regs + TVE200_INT_EN);

	ret = devm_request_irq(dev, irq, tve200_irq, 0, "tve200", priv);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq %d\n", ret);
		जाओ clk_disable;
	पूर्ण

	ret = tve200_modeset_init(drm);
	अगर (ret)
		जाओ clk_disable;

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0)
		जाओ clk_disable;

	/*
	 * Passing in 16 here will make the RGB565 mode the शेष
	 * Passing in 32 will use XRGB8888 mode
	 */
	drm_fbdev_generic_setup(drm, 16);

	वापस 0;

clk_disable:
	clk_disable_unprepare(priv->pclk);
dev_unref:
	drm_dev_put(drm);
	वापस ret;
पूर्ण

अटल पूर्णांक tve200_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);
	काष्ठा tve200_drm_dev_निजी *priv = drm->dev_निजी;

	drm_dev_unरेजिस्टर(drm);
	अगर (priv->panel)
		drm_panel_bridge_हटाओ(priv->bridge);
	drm_mode_config_cleanup(drm);
	clk_disable_unprepare(priv->pclk);
	drm_dev_put(drm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tve200_of_match[] = अणु
	अणु
		.compatible = "faraday,tve200",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tve200_driver = अणु
	.driver = अणु
		.name           = "tve200",
		.of_match_table = of_match_ptr(tve200_of_match),
	पूर्ण,
	.probe = tve200_probe,
	.हटाओ = tve200_हटाओ,
पूर्ण;
module_platक्रमm_driver(tve200_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_LICENSE("GPL");
