<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Marek Vasut <marex@denx.de>
 *
 * This code is based on drivers/video/fbdev/mxsfb.c :
 * Copyright (C) 2010 Juergen Beisert, Pengutronix
 * Copyright (C) 2008-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2008 Embedded Alley Solutions, Inc All Rights Reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_mode_config.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "mxsfb_drv.h"
#समावेश "mxsfb_regs.h"

क्रमागत mxsfb_devtype अणु
	MXSFB_V3,
	MXSFB_V4,
	/*
	 * Starting at i.MX6 the hardware version रेजिस्टर is gone, use the
	 * i.MX family number as the version.
	 */
	MXSFB_V6,
पूर्ण;

अटल स्थिर काष्ठा mxsfb_devdata mxsfb_devdata[] = अणु
	[MXSFB_V3] = अणु
		.transfer_count	= LCDC_V3_TRANSFER_COUNT,
		.cur_buf	= LCDC_V3_CUR_BUF,
		.next_buf	= LCDC_V3_NEXT_BUF,
		.hs_wdth_mask	= 0xff,
		.hs_wdth_shअगरt	= 24,
		.has_overlay	= false,
	पूर्ण,
	[MXSFB_V4] = अणु
		.transfer_count	= LCDC_V4_TRANSFER_COUNT,
		.cur_buf	= LCDC_V4_CUR_BUF,
		.next_buf	= LCDC_V4_NEXT_BUF,
		.hs_wdth_mask	= 0x3fff,
		.hs_wdth_shअगरt	= 18,
		.has_overlay	= false,
	पूर्ण,
	[MXSFB_V6] = अणु
		.transfer_count	= LCDC_V4_TRANSFER_COUNT,
		.cur_buf	= LCDC_V4_CUR_BUF,
		.next_buf	= LCDC_V4_NEXT_BUF,
		.hs_wdth_mask	= 0x3fff,
		.hs_wdth_shअगरt	= 18,
		.has_overlay	= true,
	पूर्ण,
पूर्ण;

व्योम mxsfb_enable_axi_clk(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	अगर (mxsfb->clk_axi)
		clk_prepare_enable(mxsfb->clk_axi);
पूर्ण

व्योम mxsfb_disable_axi_clk(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	अगर (mxsfb->clk_axi)
		clk_disable_unprepare(mxsfb->clk_axi);
पूर्ण

अटल काष्ठा drm_framebuffer *
mxsfb_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
		स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;

	info = drm_get_क्रमmat_info(dev, mode_cmd);
	अगर (!info)
		वापस ERR_PTR(-EINVAL);

	अगर (mode_cmd->width * info->cpp[0] != mode_cmd->pitches[0]) अणु
		dev_dbg(dev->dev, "Invalid pitch: fb width must match pitch\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस drm_gem_fb_create(dev, file_priv, mode_cmd);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs mxsfb_mode_config_funcs = अणु
	.fb_create		= mxsfb_fb_create,
	.atomic_check		= drm_atomic_helper_check,
	.atomic_commit		= drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_helper_funcs mxsfb_mode_config_helpers = अणु
	.atomic_commit_tail = drm_atomic_helper_commit_tail_rpm,
पूर्ण;

अटल पूर्णांक mxsfb_attach_bridge(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	काष्ठा drm_device *drm = mxsfb->drm;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret;

	ret = drm_of_find_panel_or_bridge(drm->dev->of_node, 0, 0, &panel,
					  &bridge);
	अगर (ret)
		वापस ret;

	अगर (panel) अणु
		bridge = devm_drm_panel_bridge_add_typed(drm->dev, panel,
							 DRM_MODE_CONNECTOR_DPI);
		अगर (IS_ERR(bridge))
			वापस PTR_ERR(bridge);
	पूर्ण

	अगर (!bridge)
		वापस -ENODEV;

	ret = drm_bridge_attach(&mxsfb->encoder, bridge, शून्य, 0);
	अगर (ret)
		वापस dev_err_probe(drm->dev, ret, "Failed to attach bridge\n");

	mxsfb->bridge = bridge;

	/*
	 * Get hold of the connector. This is a bit of a hack, until the bridge
	 * API gives us bus flags and क्रमmats.
	 */
	drm_connector_list_iter_begin(drm, &iter);
	mxsfb->connector = drm_connector_list_iter_next(&iter);
	drm_connector_list_iter_end(&iter);

	वापस 0;
पूर्ण

अटल पूर्णांक mxsfb_load(काष्ठा drm_device *drm,
		      स्थिर काष्ठा mxsfb_devdata *devdata)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(drm->dev);
	काष्ठा mxsfb_drm_निजी *mxsfb;
	काष्ठा resource *res;
	पूर्णांक ret;

	mxsfb = devm_kzalloc(&pdev->dev, माप(*mxsfb), GFP_KERNEL);
	अगर (!mxsfb)
		वापस -ENOMEM;

	mxsfb->drm = drm;
	drm->dev_निजी = mxsfb;
	mxsfb->devdata = devdata;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mxsfb->base = devm_ioremap_resource(drm->dev, res);
	अगर (IS_ERR(mxsfb->base))
		वापस PTR_ERR(mxsfb->base);

	mxsfb->clk = devm_clk_get(drm->dev, शून्य);
	अगर (IS_ERR(mxsfb->clk))
		वापस PTR_ERR(mxsfb->clk);

	mxsfb->clk_axi = devm_clk_get(drm->dev, "axi");
	अगर (IS_ERR(mxsfb->clk_axi))
		mxsfb->clk_axi = शून्य;

	mxsfb->clk_disp_axi = devm_clk_get(drm->dev, "disp_axi");
	अगर (IS_ERR(mxsfb->clk_disp_axi))
		mxsfb->clk_disp_axi = शून्य;

	ret = dma_set_mask_and_coherent(drm->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(drm->dev);

	/* Modeset init */
	drm_mode_config_init(drm);

	ret = mxsfb_kms_init(mxsfb);
	अगर (ret < 0) अणु
		dev_err(drm->dev, "Failed to initialize KMS pipeline\n");
		जाओ err_vblank;
	पूर्ण

	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	अगर (ret < 0) अणु
		dev_err(drm->dev, "Failed to initialise vblank\n");
		जाओ err_vblank;
	पूर्ण

	/* Start with vertical blanking पूर्णांकerrupt reporting disabled. */
	drm_crtc_vblank_off(&mxsfb->crtc);

	ret = mxsfb_attach_bridge(mxsfb);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(drm->dev, "Cannot connect bridge: %d\n", ret);
		जाओ err_vblank;
	पूर्ण

	drm->mode_config.min_width	= MXSFB_MIN_XRES;
	drm->mode_config.min_height	= MXSFB_MIN_YRES;
	drm->mode_config.max_width	= MXSFB_MAX_XRES;
	drm->mode_config.max_height	= MXSFB_MAX_YRES;
	drm->mode_config.funcs		= &mxsfb_mode_config_funcs;
	drm->mode_config.helper_निजी	= &mxsfb_mode_config_helpers;

	drm_mode_config_reset(drm);

	pm_runसमय_get_sync(drm->dev);
	ret = drm_irq_install(drm, platक्रमm_get_irq(pdev, 0));
	pm_runसमय_put_sync(drm->dev);

	अगर (ret < 0) अणु
		dev_err(drm->dev, "Failed to install IRQ handler\n");
		जाओ err_vblank;
	पूर्ण

	drm_kms_helper_poll_init(drm);

	platक्रमm_set_drvdata(pdev, drm);

	drm_helper_hpd_irq_event(drm);

	वापस 0;

err_vblank:
	pm_runसमय_disable(drm->dev);

	वापस ret;
पूर्ण

अटल व्योम mxsfb_unload(काष्ठा drm_device *drm)
अणु
	drm_kms_helper_poll_fini(drm);
	drm_mode_config_cleanup(drm);

	pm_runसमय_get_sync(drm->dev);
	drm_irq_uninstall(drm);
	pm_runसमय_put_sync(drm->dev);

	drm->dev_निजी = शून्य;

	pm_runसमय_disable(drm->dev);
पूर्ण

अटल व्योम mxsfb_irq_disable(काष्ठा drm_device *drm)
अणु
	काष्ठा mxsfb_drm_निजी *mxsfb = drm->dev_निजी;

	mxsfb_enable_axi_clk(mxsfb);
	mxsfb->crtc.funcs->disable_vblank(&mxsfb->crtc);
	mxsfb_disable_axi_clk(mxsfb);
पूर्ण

अटल irqवापस_t mxsfb_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा mxsfb_drm_निजी *mxsfb = drm->dev_निजी;
	u32 reg;

	reg = पढ़ोl(mxsfb->base + LCDC_CTRL1);

	अगर (reg & CTRL1_CUR_FRAME_DONE_IRQ)
		drm_crtc_handle_vblank(&mxsfb->crtc);

	ग_लिखोl(CTRL1_CUR_FRAME_DONE_IRQ, mxsfb->base + LCDC_CTRL1 + REG_CLR);

	वापस IRQ_HANDLED;
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(fops);

अटल स्थिर काष्ठा drm_driver mxsfb_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.irq_handler		= mxsfb_irq_handler,
	.irq_preinstall		= mxsfb_irq_disable,
	.irq_uninstall		= mxsfb_irq_disable,
	DRM_GEM_CMA_DRIVER_OPS,
	.fops	= &fops,
	.name	= "mxsfb-drm",
	.desc	= "MXSFB Controller DRM",
	.date	= "20160824",
	.major	= 1,
	.minor	= 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxsfb_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-lcdif", .data = &mxsfb_devdata[MXSFB_V3], पूर्ण,
	अणु .compatible = "fsl,imx28-lcdif", .data = &mxsfb_devdata[MXSFB_V4], पूर्ण,
	अणु .compatible = "fsl,imx6sx-lcdif", .data = &mxsfb_devdata[MXSFB_V6], पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxsfb_dt_ids);

अटल पूर्णांक mxsfb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm;
	स्थिर काष्ठा of_device_id *of_id =
			of_match_device(mxsfb_dt_ids, &pdev->dev);
	पूर्णांक ret;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	drm = drm_dev_alloc(&mxsfb_driver, &pdev->dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	ret = mxsfb_load(drm, of_id->data);
	अगर (ret)
		जाओ err_मुक्त;

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ err_unload;

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

err_unload:
	mxsfb_unload(drm);
err_मुक्त:
	drm_dev_put(drm);

	वापस ret;
पूर्ण

अटल पूर्णांक mxsfb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(drm);
	mxsfb_unload(drm);
	drm_dev_put(drm);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mxsfb_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm);
पूर्ण

अटल पूर्णांक mxsfb_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(drm);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mxsfb_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mxsfb_suspend, mxsfb_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver mxsfb_platक्रमm_driver = अणु
	.probe		= mxsfb_probe,
	.हटाओ		= mxsfb_हटाओ,
	.driver	= अणु
		.name		= "mxsfb",
		.of_match_table	= mxsfb_dt_ids,
		.pm		= &mxsfb_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mxsfb_platक्रमm_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("Freescale MXS DRM/KMS driver");
MODULE_LICENSE("GPL");
