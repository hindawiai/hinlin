<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Texas Instruments
 * Author: Rob Clark <robdclark@gmail.com>
 */

/* LCDC DRM driver, based on da8xx-fb */

#समावेश <linux/component.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_mm.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>


#समावेश "tilcdc_drv.h"
#समावेश "tilcdc_external.h"
#समावेश "tilcdc_panel.h"
#समावेश "tilcdc_regs.h"

अटल LIST_HEAD(module_list);

अटल स्थिर u32 tilcdc_rev1_क्रमmats[] = अणु DRM_FORMAT_RGB565 पूर्ण;

अटल स्थिर u32 tilcdc_straight_क्रमmats[] = अणु DRM_FORMAT_RGB565,
					       DRM_FORMAT_BGR888,
					       DRM_FORMAT_XBGR8888 पूर्ण;

अटल स्थिर u32 tilcdc_crossed_क्रमmats[] = अणु DRM_FORMAT_BGR565,
					      DRM_FORMAT_RGB888,
					      DRM_FORMAT_XRGB8888 पूर्ण;

अटल स्थिर u32 tilcdc_legacy_क्रमmats[] = अणु DRM_FORMAT_RGB565,
					     DRM_FORMAT_RGB888,
					     DRM_FORMAT_XRGB8888 पूर्ण;

व्योम tilcdc_module_init(काष्ठा tilcdc_module *mod, स्थिर अक्षर *name,
		स्थिर काष्ठा tilcdc_module_ops *funcs)
अणु
	mod->name = name;
	mod->funcs = funcs;
	INIT_LIST_HEAD(&mod->list);
	list_add(&mod->list, &module_list);
पूर्ण

व्योम tilcdc_module_cleanup(काष्ठा tilcdc_module *mod)
अणु
	list_del(&mod->list);
पूर्ण

अटल काष्ठा of_device_id tilcdc_of_match[];

अटल पूर्णांक tilcdc_atomic_check(काष्ठा drm_device *dev,
			       काष्ठा drm_atomic_state *state)
अणु
	पूर्णांक ret;

	ret = drm_atomic_helper_check_modeset(dev, state);
	अगर (ret)
		वापस ret;

	ret = drm_atomic_helper_check_planes(dev, state);
	अगर (ret)
		वापस ret;

	/*
	 * tilcdc ->atomic_check can update ->mode_changed अगर pixel क्रमmat
	 * changes, hence will we check modeset changes again.
	 */
	ret = drm_atomic_helper_check_modeset(dev, state);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = tilcdc_atomic_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल व्योम modeset_init(काष्ठा drm_device *dev)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	काष्ठा tilcdc_module *mod;

	list_क्रम_each_entry(mod, &module_list, list) अणु
		DBG("loading module: %s", mod->name);
		mod->funcs->modeset_init(mod, dev);
	पूर्ण

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = priv->max_width;
	dev->mode_config.max_height = 2048;
	dev->mode_config.funcs = &mode_config_funcs;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
अटल पूर्णांक cpufreq_transition(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा tilcdc_drm_निजी *priv = container_of(nb,
			काष्ठा tilcdc_drm_निजी, freq_transition);

	अगर (val == CPUFREQ_POSTCHANGE)
		tilcdc_crtc_update_clk(priv->crtc);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * DRM operations:
 */

अटल व्योम tilcdc_fini(काष्ठा drm_device *dev)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;

#अगर_घोषित CONFIG_CPU_FREQ
	अगर (priv->freq_transition.notअगरier_call)
		cpufreq_unरेजिस्टर_notअगरier(&priv->freq_transition,
					    CPUFREQ_TRANSITION_NOTIFIER);
#पूर्ण_अगर

	अगर (priv->crtc)
		tilcdc_crtc_shutकरोwn(priv->crtc);

	अगर (priv->is_रेजिस्टरed)
		drm_dev_unरेजिस्टर(dev);

	drm_kms_helper_poll_fini(dev);
	drm_irq_uninstall(dev);
	drm_mode_config_cleanup(dev);

	अगर (priv->clk)
		clk_put(priv->clk);

	अगर (priv->mmio)
		iounmap(priv->mmio);

	अगर (priv->wq) अणु
		flush_workqueue(priv->wq);
		destroy_workqueue(priv->wq);
	पूर्ण

	dev->dev_निजी = शून्य;

	pm_runसमय_disable(dev->dev);

	drm_dev_put(dev);
पूर्ण

अटल पूर्णांक tilcdc_init(स्थिर काष्ठा drm_driver *ddrv, काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *node = dev->of_node;
	काष्ठा tilcdc_drm_निजी *priv;
	काष्ठा resource *res;
	u32 bpp = 0;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ddev = drm_dev_alloc(ddrv, dev);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	ddev->dev_निजी = priv;
	platक्रमm_set_drvdata(pdev, ddev);
	drm_mode_config_init(ddev);

	priv->is_componentized =
		tilcdc_get_बाह्यal_components(dev, शून्य) > 0;

	priv->wq = alloc_ordered_workqueue("tilcdc", 0);
	अगर (!priv->wq) अणु
		ret = -ENOMEM;
		जाओ init_failed;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "failed to get memory resource\n");
		ret = -EINVAL;
		जाओ init_failed;
	पूर्ण

	priv->mmio = ioremap(res->start, resource_size(res));
	अगर (!priv->mmio) अणु
		dev_err(dev, "failed to ioremap\n");
		ret = -ENOMEM;
		जाओ init_failed;
	पूर्ण

	priv->clk = clk_get(dev, "fck");
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get functional clock\n");
		ret = -ENODEV;
		जाओ init_failed;
	पूर्ण

	pm_runसमय_enable(dev);

	/* Determine LCD IP Version */
	pm_runसमय_get_sync(dev);
	चयन (tilcdc_पढ़ो(ddev, LCDC_PID_REG)) अणु
	हाल 0x4c100102:
		priv->rev = 1;
		अवरोध;
	हाल 0x4f200800:
	हाल 0x4f201000:
		priv->rev = 2;
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown PID Reg value 0x%08x, "
			"defaulting to LCD revision 1\n",
			tilcdc_पढ़ो(ddev, LCDC_PID_REG));
		priv->rev = 1;
		अवरोध;
	पूर्ण

	pm_runसमय_put_sync(dev);

	अगर (priv->rev == 1) अणु
		DBG("Revision 1 LCDC supports only RGB565 format");
		priv->pixelक्रमmats = tilcdc_rev1_क्रमmats;
		priv->num_pixelक्रमmats = ARRAY_SIZE(tilcdc_rev1_क्रमmats);
		bpp = 16;
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *str = "\0";

		of_property_पढ़ो_string(node, "blue-and-red-wiring", &str);
		अगर (0 == म_भेद(str, "crossed")) अणु
			DBG("Configured for crossed blue and red wires");
			priv->pixelक्रमmats = tilcdc_crossed_क्रमmats;
			priv->num_pixelक्रमmats =
				ARRAY_SIZE(tilcdc_crossed_क्रमmats);
			bpp = 32; /* Choose bpp with RGB support क्रम fbdef */
		पूर्ण अन्यथा अगर (0 == म_भेद(str, "straight")) अणु
			DBG("Configured for straight blue and red wires");
			priv->pixelक्रमmats = tilcdc_straight_क्रमmats;
			priv->num_pixelक्रमmats =
				ARRAY_SIZE(tilcdc_straight_क्रमmats);
			bpp = 16; /* Choose bpp with RGB support क्रम fbdef */
		पूर्ण अन्यथा अणु
			DBG("Blue and red wiring '%s' unknown, use legacy mode",
			    str);
			priv->pixelक्रमmats = tilcdc_legacy_क्रमmats;
			priv->num_pixelक्रमmats =
				ARRAY_SIZE(tilcdc_legacy_क्रमmats);
			bpp = 16; /* This is just a guess */
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "max-bandwidth", &priv->max_bandwidth))
		priv->max_bandwidth = TILCDC_DEFAULT_MAX_BANDWIDTH;

	DBG("Maximum Bandwidth Value %d", priv->max_bandwidth);

	अगर (of_property_पढ़ो_u32(node, "max-width", &priv->max_width)) अणु
		अगर (priv->rev == 1)
			priv->max_width = TILCDC_DEFAULT_MAX_WIDTH_V1;
		अन्यथा
			priv->max_width = TILCDC_DEFAULT_MAX_WIDTH_V2;
	पूर्ण

	DBG("Maximum Horizontal Pixel Width Value %dpixels", priv->max_width);

	अगर (of_property_पढ़ो_u32(node, "max-pixelclock",
				 &priv->max_pixelघड़ी))
		priv->max_pixelघड़ी = TILCDC_DEFAULT_MAX_PIXELCLOCK;

	DBG("Maximum Pixel Clock Value %dKHz", priv->max_pixelघड़ी);

	ret = tilcdc_crtc_create(ddev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to create crtc\n");
		जाओ init_failed;
	पूर्ण
	modeset_init(ddev);

#अगर_घोषित CONFIG_CPU_FREQ
	priv->freq_transition.notअगरier_call = cpufreq_transition;
	ret = cpufreq_रेजिस्टर_notअगरier(&priv->freq_transition,
			CPUFREQ_TRANSITION_NOTIFIER);
	अगर (ret) अणु
		dev_err(dev, "failed to register cpufreq notifier\n");
		priv->freq_transition.notअगरier_call = शून्य;
		जाओ init_failed;
	पूर्ण
#पूर्ण_अगर

	अगर (priv->is_componentized) अणु
		ret = component_bind_all(dev, ddev);
		अगर (ret < 0)
			जाओ init_failed;

		ret = tilcdc_add_component_encoder(ddev);
		अगर (ret < 0)
			जाओ init_failed;
	पूर्ण अन्यथा अणु
		ret = tilcdc_attach_बाह्यal_device(ddev);
		अगर (ret)
			जाओ init_failed;
	पूर्ण

	अगर (!priv->बाह्यal_connector &&
	    ((priv->num_encoders == 0) || (priv->num_connectors == 0))) अणु
		dev_err(dev, "no encoders/connectors found\n");
		ret = -EPROBE_DEFER;
		जाओ init_failed;
	पूर्ण

	ret = drm_vblank_init(ddev, 1);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to initialize vblank\n");
		जाओ init_failed;
	पूर्ण

	ret = drm_irq_install(ddev, platक्रमm_get_irq(pdev, 0));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to install IRQ handler\n");
		जाओ init_failed;
	पूर्ण

	drm_mode_config_reset(ddev);

	drm_kms_helper_poll_init(ddev);

	ret = drm_dev_रेजिस्टर(ddev, 0);
	अगर (ret)
		जाओ init_failed;
	priv->is_रेजिस्टरed = true;

	drm_fbdev_generic_setup(ddev, bpp);
	वापस 0;

init_failed:
	tilcdc_fini(ddev);

	वापस ret;
पूर्ण

अटल irqवापस_t tilcdc_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = arg;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	वापस tilcdc_crtc_irq(priv->crtc);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	uपूर्णांक8_t  rev;
	uपूर्णांक8_t  save;
	uपूर्णांक32_t reg;
पूर्ण रेजिस्टरs[] =		अणु
#घोषणा REG(rev, save, reg) अणु #reg, rev, save, reg पूर्ण
		/* exists in revision 1: */
		REG(1, false, LCDC_PID_REG),
		REG(1, true,  LCDC_CTRL_REG),
		REG(1, false, LCDC_STAT_REG),
		REG(1, true,  LCDC_RASTER_CTRL_REG),
		REG(1, true,  LCDC_RASTER_TIMING_0_REG),
		REG(1, true,  LCDC_RASTER_TIMING_1_REG),
		REG(1, true,  LCDC_RASTER_TIMING_2_REG),
		REG(1, true,  LCDC_DMA_CTRL_REG),
		REG(1, true,  LCDC_DMA_FB_BASE_ADDR_0_REG),
		REG(1, true,  LCDC_DMA_FB_CEILING_ADDR_0_REG),
		REG(1, true,  LCDC_DMA_FB_BASE_ADDR_1_REG),
		REG(1, true,  LCDC_DMA_FB_CEILING_ADDR_1_REG),
		/* new in revision 2: */
		REG(2, false, LCDC_RAW_STAT_REG),
		REG(2, false, LCDC_MASKED_STAT_REG),
		REG(2, true, LCDC_INT_ENABLE_SET_REG),
		REG(2, false, LCDC_INT_ENABLE_CLR_REG),
		REG(2, false, LCDC_END_OF_INT_IND_REG),
		REG(2, true,  LCDC_CLK_ENABLE_REG),
#अघोषित REG
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक tilcdc_regs_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित i;

	pm_runसमय_get_sync(dev->dev);

	seq_म_लिखो(m, "revision: %d\n", priv->rev);

	क्रम (i = 0; i < ARRAY_SIZE(रेजिस्टरs); i++)
		अगर (priv->rev >= रेजिस्टरs[i].rev)
			seq_म_लिखो(m, "%s:\t %08x\n", रेजिस्टरs[i].name,
					tilcdc_पढ़ो(dev, रेजिस्टरs[i].reg));

	pm_runसमय_put_sync(dev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tilcdc_mm_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);
	drm_mm_prपूर्णांक(&dev->vma_offset_manager->vm_addr_space_mm, &p);
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list tilcdc_debugfs_list[] = अणु
		अणु "regs", tilcdc_regs_show, 0, शून्य पूर्ण,
		अणु "mm",   tilcdc_mm_show,   0, शून्य पूर्ण,
पूर्ण;

अटल व्योम tilcdc_debugfs_init(काष्ठा drm_minor *minor)
अणु
	काष्ठा tilcdc_module *mod;

	drm_debugfs_create_files(tilcdc_debugfs_list,
				 ARRAY_SIZE(tilcdc_debugfs_list),
				 minor->debugfs_root, minor);

	list_क्रम_each_entry(mod, &module_list, list)
		अगर (mod->funcs->debugfs_init)
			mod->funcs->debugfs_init(mod, minor);
पूर्ण
#पूर्ण_अगर

DEFINE_DRM_GEM_CMA_FOPS(fops);

अटल स्थिर काष्ठा drm_driver tilcdc_driver = अणु
	.driver_features    = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.irq_handler        = tilcdc_irq,
	DRM_GEM_CMA_DRIVER_OPS,
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init       = tilcdc_debugfs_init,
#पूर्ण_अगर
	.fops               = &fops,
	.name               = "tilcdc",
	.desc               = "TI LCD Controller DRM",
	.date               = "20121205",
	.major              = 1,
	.minor              = 0,
पूर्ण;

/*
 * Power management:
 */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tilcdc_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = drm_mode_config_helper_suspend(ddev);

	/* Select sleep pin state */
	pinctrl_pm_select_sleep_state(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tilcdc_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);

	/* Select शेष pin state */
	pinctrl_pm_select_शेष_state(dev);
	वापस  drm_mode_config_helper_resume(ddev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops tilcdc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tilcdc_pm_suspend, tilcdc_pm_resume)
पूर्ण;

/*
 * Platक्रमm driver:
 */
अटल पूर्णांक tilcdc_bind(काष्ठा device *dev)
अणु
	वापस tilcdc_init(&tilcdc_driver, dev);
पूर्ण

अटल व्योम tilcdc_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);

	/* Check अगर a subcomponent has alपढ़ोy triggered the unloading. */
	अगर (!ddev->dev_निजी)
		वापस;

	tilcdc_fini(dev_get_drvdata(dev));
पूर्ण

अटल स्थिर काष्ठा component_master_ops tilcdc_comp_ops = अणु
	.bind = tilcdc_bind,
	.unbind = tilcdc_unbind,
पूर्ण;

अटल पूर्णांक tilcdc_pdev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा component_match *match = शून्य;
	पूर्णांक ret;

	/* bail out early अगर no DT data: */
	अगर (!pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "device-tree data is missing\n");
		वापस -ENXIO;
	पूर्ण

	ret = tilcdc_get_बाह्यal_components(&pdev->dev, &match);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret == 0)
		वापस tilcdc_init(&tilcdc_driver, &pdev->dev);
	अन्यथा
		वापस component_master_add_with_match(&pdev->dev,
						       &tilcdc_comp_ops,
						       match);
पूर्ण

अटल पूर्णांक tilcdc_pdev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = tilcdc_get_बाह्यal_components(&pdev->dev, शून्य);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret == 0)
		tilcdc_fini(platक्रमm_get_drvdata(pdev));
	अन्यथा
		component_master_del(&pdev->dev, &tilcdc_comp_ops);

	वापस 0;
पूर्ण

अटल काष्ठा of_device_id tilcdc_of_match[] = अणु
		अणु .compatible = "ti,am33xx-tilcdc", पूर्ण,
		अणु .compatible = "ti,da850-tilcdc", पूर्ण,
		अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tilcdc_of_match);

अटल काष्ठा platक्रमm_driver tilcdc_platक्रमm_driver = अणु
	.probe      = tilcdc_pdev_probe,
	.हटाओ     = tilcdc_pdev_हटाओ,
	.driver     = अणु
		.name   = "tilcdc",
		.pm     = &tilcdc_pm_ops,
		.of_match_table = tilcdc_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tilcdc_drm_init(व्योम)
अणु
	DBG("init");
	tilcdc_panel_init();
	वापस platक्रमm_driver_रेजिस्टर(&tilcdc_platक्रमm_driver);
पूर्ण

अटल व्योम __निकास tilcdc_drm_fini(व्योम)
अणु
	DBG("fini");
	platक्रमm_driver_unरेजिस्टर(&tilcdc_platक्रमm_driver);
	tilcdc_panel_fini();
पूर्ण

module_init(tilcdc_drm_init);
module_निकास(tilcdc_drm_fini);

MODULE_AUTHOR("Rob Clark <robdclark@gmail.com");
MODULE_DESCRIPTION("TI LCD Controller DRM Driver");
MODULE_LICENSE("GPL");
