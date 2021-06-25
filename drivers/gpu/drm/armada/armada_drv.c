<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Russell King
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_vblank.h>

#समावेश "armada_crtc.h"
#समावेश "armada_drm.h"
#समावेश "armada_gem.h"
#समावेश "armada_fb.h"
#समावेश "armada_hw.h"
#समावेश <drm/armada_drm.h>
#समावेश "armada_ioctlP.h"

अटल स्थिर काष्ठा drm_ioctl_desc armada_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(ARMADA_GEM_CREATE, armada_gem_create_ioctl,0),
	DRM_IOCTL_DEF_DRV(ARMADA_GEM_MMAP, armada_gem_mmap_ioctl, 0),
	DRM_IOCTL_DEF_DRV(ARMADA_GEM_PWRITE, armada_gem_pग_लिखो_ioctl, 0),
पूर्ण;

DEFINE_DRM_GEM_FOPS(armada_drm_fops);

अटल स्थिर काष्ठा drm_driver armada_drm_driver = अणु
	.lastबंद		= drm_fb_helper_lastबंद,
	.prime_handle_to_fd	= drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle	= drm_gem_prime_fd_to_handle,
	.gem_prime_import	= armada_gem_prime_import,
	.dumb_create		= armada_gem_dumb_create,
	.major			= 1,
	.minor			= 0,
	.name			= "armada-drm",
	.desc			= "Armada SoC DRM",
	.date			= "20120730",
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.ioctls			= armada_ioctls,
	.num_ioctls = ARRAY_SIZE(armada_ioctls),
	.fops			= &armada_drm_fops,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs armada_drm_mode_config_funcs = अणु
	.fb_create		= armada_fb_create,
	.output_poll_changed	= drm_fb_helper_output_poll_changed,
	.atomic_check		= drm_atomic_helper_check,
	.atomic_commit		= drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक armada_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा armada_निजी *priv;
	काष्ठा resource *mem = शून्य;
	पूर्णांक ret, n;

	क्रम (n = 0; ; n++) अणु
		काष्ठा resource *r = platक्रमm_get_resource(to_platक्रमm_device(dev),
							   IORESOURCE_MEM, n);
		अगर (!r)
			अवरोध;

		/* Resources above 64K are graphics memory */
		अगर (resource_size(r) > SZ_64K)
			mem = r;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (!mem)
		वापस -ENXIO;

	अगर (!devm_request_mem_region(dev, mem->start, resource_size(mem),
				     "armada-drm"))
		वापस -EBUSY;

	priv = devm_drm_dev_alloc(dev, &armada_drm_driver,
				  काष्ठा armada_निजी, drm);
	अगर (IS_ERR(priv)) अणु
		dev_err(dev, "[" DRM_NAME ":%s] devm_drm_dev_alloc failed: %li\n",
			__func__, PTR_ERR(priv));
		वापस PTR_ERR(priv);
	पूर्ण

	/* Remove early framebuffers */
	ret = drm_fb_helper_हटाओ_conflicting_framebuffers(शून्य,
							    "armada-drm-fb",
							    false);
	अगर (ret) अणु
		dev_err(dev, "[" DRM_NAME ":%s] can't kick out simple-fb: %d\n",
			__func__, ret);
		kमुक्त(priv);
		वापस ret;
	पूर्ण

	dev_set_drvdata(dev, &priv->drm);

	/* Mode setting support */
	drm_mode_config_init(&priv->drm);
	priv->drm.mode_config.min_width = 320;
	priv->drm.mode_config.min_height = 200;

	/*
	 * With vscale enabled, the maximum width is 1920 due to the
	 * 1920 by 3 lines RAM
	 */
	priv->drm.mode_config.max_width = 1920;
	priv->drm.mode_config.max_height = 2048;

	priv->drm.mode_config.preferred_depth = 24;
	priv->drm.mode_config.funcs = &armada_drm_mode_config_funcs;
	drm_mm_init(&priv->linear, mem->start, resource_size(mem));
	mutex_init(&priv->linear_lock);

	ret = component_bind_all(dev, &priv->drm);
	अगर (ret)
		जाओ err_kms;

	ret = drm_vblank_init(&priv->drm, priv->drm.mode_config.num_crtc);
	अगर (ret)
		जाओ err_comp;

	priv->drm.irq_enabled = true;

	drm_mode_config_reset(&priv->drm);

	ret = armada_fbdev_init(&priv->drm);
	अगर (ret)
		जाओ err_comp;

	drm_kms_helper_poll_init(&priv->drm);

	ret = drm_dev_रेजिस्टर(&priv->drm, 0);
	अगर (ret)
		जाओ err_poll;

#अगर_घोषित CONFIG_DEBUG_FS
	armada_drm_debugfs_init(priv->drm.primary);
#पूर्ण_अगर

	वापस 0;

 err_poll:
	drm_kms_helper_poll_fini(&priv->drm);
	armada_fbdev_fini(&priv->drm);
 err_comp:
	component_unbind_all(dev, &priv->drm);
 err_kms:
	drm_mode_config_cleanup(&priv->drm);
	drm_mm_takeकरोwn(&priv->linear);
	वापस ret;
पूर्ण

अटल व्योम armada_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा armada_निजी *priv = drm_to_armada_dev(drm);

	drm_kms_helper_poll_fini(&priv->drm);
	armada_fbdev_fini(&priv->drm);

	drm_dev_unरेजिस्टर(&priv->drm);

	drm_atomic_helper_shutकरोwn(&priv->drm);

	component_unbind_all(dev, &priv->drm);

	drm_mode_config_cleanup(&priv->drm);
	drm_mm_takeकरोwn(&priv->linear);
पूर्ण

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल पूर्णांक compare_dev_name(काष्ठा device *dev, व्योम *data)
अणु
	स्थिर अक्षर *name = data;
	वापस !म_भेद(dev_name(dev), name);
पूर्ण

अटल व्योम armada_add_endpoपूर्णांकs(काष्ठा device *dev,
	काष्ठा component_match **match, काष्ठा device_node *dev_node)
अणु
	काष्ठा device_node *ep, *remote;

	क्रम_each_endpoपूर्णांक_of_node(dev_node, ep) अणु
		remote = of_graph_get_remote_port_parent(ep);
		अगर (remote && of_device_is_available(remote))
			drm_of_component_match_add(dev, match, compare_of,
						   remote);
		of_node_put(remote);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा component_master_ops armada_master_ops = अणु
	.bind = armada_drm_bind,
	.unbind = armada_drm_unbind,
पूर्ण;

अटल पूर्णांक armada_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा component_match *match = शून्य;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	ret = drm_of_component_probe(dev, compare_dev_name, &armada_master_ops);
	अगर (ret != -EINVAL)
		वापस ret;

	अगर (dev->platक्रमm_data) अणु
		अक्षर **devices = dev->platक्रमm_data;
		काष्ठा device *d;
		पूर्णांक i;

		क्रम (i = 0; devices[i]; i++)
			component_match_add(dev, &match, compare_dev_name,
					    devices[i]);

		अगर (i == 0) अणु
			dev_err(dev, "missing 'ports' property\n");
			वापस -ENODEV;
		पूर्ण

		क्रम (i = 0; devices[i]; i++) अणु
			d = bus_find_device_by_name(&platक्रमm_bus_type, शून्य,
						    devices[i]);
			अगर (d && d->of_node)
				armada_add_endpoपूर्णांकs(dev, &match, d->of_node);
			put_device(d);
		पूर्ण
	पूर्ण

	वापस component_master_add_with_match(&pdev->dev, &armada_master_ops,
					       match);
पूर्ण

अटल पूर्णांक armada_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &armada_master_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id armada_drm_platक्रमm_ids[] = अणु
	अणु
		.name		= "armada-drm",
	पूर्ण, अणु
		.name		= "armada-510-drm",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, armada_drm_platक्रमm_ids);

अटल काष्ठा platक्रमm_driver armada_drm_platक्रमm_driver = अणु
	.probe	= armada_drm_probe,
	.हटाओ	= armada_drm_हटाओ,
	.driver	= अणु
		.name	= "armada-drm",
	पूर्ण,
	.id_table = armada_drm_platक्रमm_ids,
पूर्ण;

अटल पूर्णांक __init armada_drm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&armada_lcd_platक्रमm_driver);
	अगर (ret)
		वापस ret;
	ret = platक्रमm_driver_रेजिस्टर(&armada_drm_platक्रमm_driver);
	अगर (ret)
		platक्रमm_driver_unरेजिस्टर(&armada_lcd_platक्रमm_driver);
	वापस ret;
पूर्ण
module_init(armada_drm_init);

अटल व्योम __निकास armada_drm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&armada_drm_platक्रमm_driver);
	platक्रमm_driver_unरेजिस्टर(&armada_lcd_platक्रमm_driver);
पूर्ण
module_निकास(armada_drm_निकास);

MODULE_AUTHOR("Russell King <rmk+kernel@armlinux.org.uk>");
MODULE_DESCRIPTION("Armada DRM Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:armada-drm");
