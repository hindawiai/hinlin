<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spinlock.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "zx_drm_drv.h"
#समावेश "zx_vou.h"

अटल स्थिर काष्ठा drm_mode_config_funcs zx_drm_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(zx_drm_fops);

अटल स्थिर काष्ठा drm_driver zx_drm_driver = अणु
	.driver_features = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	DRM_GEM_CMA_DRIVER_OPS,
	.fops = &zx_drm_fops,
	.name = "zx-vou",
	.desc = "ZTE VOU Controller DRM",
	.date = "20160811",
	.major = 1,
	.minor = 0,
पूर्ण;

अटल पूर्णांक zx_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm;
	पूर्णांक ret;

	drm = drm_dev_alloc(&zx_drm_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	dev_set_drvdata(dev, drm);

	drm_mode_config_init(drm);
	drm->mode_config.min_width = 16;
	drm->mode_config.min_height = 16;
	drm->mode_config.max_width = 4096;
	drm->mode_config.max_height = 4096;
	drm->mode_config.funcs = &zx_drm_mode_config_funcs;

	ret = component_bind_all(dev, drm);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to bind all components: %d\n", ret);
		जाओ out_unरेजिस्टर;
	पूर्ण

	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "failed to init vblank: %d\n", ret);
		जाओ out_unbind;
	पूर्ण

	/*
	 * We will manage irq handler on our own.  In this हाल, irq_enabled
	 * need to be true क्रम using vblank core support.
	 */
	drm->irq_enabled = true;

	drm_mode_config_reset(drm);
	drm_kms_helper_poll_init(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ out_poll_fini;

	drm_fbdev_generic_setup(drm, 32);

	वापस 0;

out_poll_fini:
	drm_kms_helper_poll_fini(drm);
	drm_mode_config_cleanup(drm);
out_unbind:
	component_unbind_all(dev, drm);
out_unरेजिस्टर:
	dev_set_drvdata(dev, शून्य);
	drm_dev_put(drm);
	वापस ret;
पूर्ण

अटल व्योम zx_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(drm);
	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutकरोwn(drm);
	drm_mode_config_cleanup(drm);
	component_unbind_all(dev, drm);
	dev_set_drvdata(dev, शून्य);
	drm_dev_put(drm);
पूर्ण

अटल स्थिर काष्ठा component_master_ops zx_drm_master_ops = अणु
	.bind = zx_drm_bind,
	.unbind = zx_drm_unbind,
पूर्ण;

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल पूर्णांक zx_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *parent = dev->of_node;
	काष्ठा device_node *child;
	काष्ठा component_match *match = शून्य;
	पूर्णांक ret;

	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret)
		वापस ret;

	क्रम_each_available_child_of_node(parent, child)
		component_match_add(dev, &match, compare_of, child);

	वापस component_master_add_with_match(dev, &zx_drm_master_ops, match);
पूर्ण

अटल पूर्णांक zx_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &zx_drm_master_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zx_drm_of_match[] = अणु
	अणु .compatible = "zte,zx296718-vou", पूर्ण,
	अणु /* end */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zx_drm_of_match);

अटल काष्ठा platक्रमm_driver zx_drm_platक्रमm_driver = अणु
	.probe = zx_drm_probe,
	.हटाओ = zx_drm_हटाओ,
	.driver	= अणु
		.name = "zx-drm",
		.of_match_table	= zx_drm_of_match,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver *drivers[] = अणु
	&zx_crtc_driver,
	&zx_hdmi_driver,
	&zx_tvenc_driver,
	&zx_vga_driver,
	&zx_drm_platक्रमm_driver,
पूर्ण;

अटल पूर्णांक zx_drm_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_init(zx_drm_init);

अटल व्योम zx_drm_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(zx_drm_निकास);

MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_DESCRIPTION("ZTE ZX VOU DRM driver");
MODULE_LICENSE("GPL v2");
