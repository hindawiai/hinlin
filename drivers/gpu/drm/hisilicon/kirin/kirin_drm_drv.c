<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hisilicon Kirin SoCs drm master driver
 *
 * Copyright (c) 2016 Linaro Limited.
 * Copyright (c) 2014-2016 Hisilicon Limited.
 *
 * Author:
 *	Xinliang Liu <z.liuxinliang@hisilicon.com>
 *	Xinliang Liu <xinliang.liu@linaro.org>
 *	Xinwei Kong <kong.kongxinwei@hisilicon.com>
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "kirin_drm_drv.h"

#घोषणा KIRIN_MAX_PLANE	2

काष्ठा kirin_drm_निजी अणु
	काष्ठा kirin_crtc crtc;
	काष्ठा kirin_plane planes[KIRIN_MAX_PLANE];
	व्योम *hw_ctx;
पूर्ण;

अटल पूर्णांक kirin_drm_crtc_init(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc,
			       काष्ठा drm_plane *plane,
			       स्थिर काष्ठा kirin_drm_data *driver_data)
अणु
	काष्ठा device_node *port;
	पूर्णांक ret;

	/* set crtc port so that
	 * drm_of_find_possible_crtcs call works
	 */
	port = of_get_child_by_name(dev->dev->of_node, "port");
	अगर (!port) अणु
		DRM_ERROR("no port node found in %pOF\n", dev->dev->of_node);
		वापस -EINVAL;
	पूर्ण
	of_node_put(port);
	crtc->port = port;

	ret = drm_crtc_init_with_planes(dev, crtc, plane, शून्य,
					driver_data->crtc_funcs, शून्य);
	अगर (ret) अणु
		DRM_ERROR("failed to init crtc.\n");
		वापस ret;
	पूर्ण

	drm_crtc_helper_add(crtc, driver_data->crtc_helper_funcs);

	वापस 0;
पूर्ण

अटल पूर्णांक kirin_drm_plane_init(काष्ठा drm_device *dev, काष्ठा drm_plane *plane,
				क्रमागत drm_plane_type type,
				स्थिर काष्ठा kirin_drm_data *data)
अणु
	पूर्णांक ret = 0;

	ret = drm_universal_plane_init(dev, plane, 1, data->plane_funcs,
				       data->channel_क्रमmats,
				       data->channel_क्रमmats_cnt,
				       शून्य, type, शून्य);
	अगर (ret) अणु
		DRM_ERROR("fail to init plane, ch=%d\n", 0);
		वापस ret;
	पूर्ण

	drm_plane_helper_add(plane, data->plane_helper_funcs);

	वापस 0;
पूर्ण

अटल व्योम kirin_drm_निजी_cleanup(काष्ठा drm_device *dev)
अणु
	काष्ठा kirin_drm_निजी *kirin_priv = dev->dev_निजी;
	काष्ठा kirin_drm_data *data;

	data = (काष्ठा kirin_drm_data *)of_device_get_match_data(dev->dev);
	अगर (data->cleanup_hw_ctx)
		data->cleanup_hw_ctx(kirin_priv->hw_ctx);

	devm_kमुक्त(dev->dev, kirin_priv);
	dev->dev_निजी = शून्य;
पूर्ण

अटल पूर्णांक kirin_drm_निजी_init(काष्ठा drm_device *dev,
				  स्थिर काष्ठा kirin_drm_data *driver_data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	काष्ठा kirin_drm_निजी *kirin_priv;
	काष्ठा drm_plane *prim_plane;
	क्रमागत drm_plane_type type;
	व्योम *ctx;
	पूर्णांक ret;
	u32 ch;

	kirin_priv = devm_kzalloc(dev->dev, माप(*kirin_priv), GFP_KERNEL);
	अगर (!kirin_priv) अणु
		DRM_ERROR("failed to alloc kirin_drm_private\n");
		वापस -ENOMEM;
	पूर्ण

	ctx = driver_data->alloc_hw_ctx(pdev, &kirin_priv->crtc.base);
	अगर (IS_ERR(ctx)) अणु
		DRM_ERROR("failed to initialize kirin_priv hw ctx\n");
		वापस -EINVAL;
	पूर्ण
	kirin_priv->hw_ctx = ctx;

	/*
	 * plane init
	 * TODO: Now only support primary plane, overlay planes
	 * need to करो.
	 */
	क्रम (ch = 0; ch < driver_data->num_planes; ch++) अणु
		अगर (ch == driver_data->prim_plane)
			type = DRM_PLANE_TYPE_PRIMARY;
		अन्यथा
			type = DRM_PLANE_TYPE_OVERLAY;
		ret = kirin_drm_plane_init(dev, &kirin_priv->planes[ch].base,
					   type, driver_data);
		अगर (ret)
			वापस ret;
		kirin_priv->planes[ch].ch = ch;
		kirin_priv->planes[ch].hw_ctx = ctx;
	पूर्ण

	/* crtc init */
	prim_plane = &kirin_priv->planes[driver_data->prim_plane].base;
	ret = kirin_drm_crtc_init(dev, &kirin_priv->crtc.base,
				  prim_plane, driver_data);
	अगर (ret)
		वापस ret;
	kirin_priv->crtc.hw_ctx = ctx;
	dev->dev_निजी = kirin_priv;

	वापस 0;
पूर्ण

अटल पूर्णांक kirin_drm_kms_init(काष्ठा drm_device *dev,
			      स्थिर काष्ठा kirin_drm_data *driver_data)
अणु
	पूर्णांक ret;

	/* dev->mode_config initialization */
	drm_mode_config_init(dev);
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = driver_data->config_max_width;
	dev->mode_config.max_height = driver_data->config_max_width;
	dev->mode_config.funcs = driver_data->mode_config_funcs;

	/* display controller init */
	ret = kirin_drm_निजी_init(dev, driver_data);
	अगर (ret)
		जाओ err_mode_config_cleanup;

	/* bind and init sub drivers */
	ret = component_bind_all(dev->dev, dev);
	अगर (ret) अणु
		DRM_ERROR("failed to bind all component.\n");
		जाओ err_निजी_cleanup;
	पूर्ण

	/* vblank init */
	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	अगर (ret) अणु
		DRM_ERROR("failed to initialize vblank.\n");
		जाओ err_unbind_all;
	पूर्ण
	/* with irq_enabled = true, we can use the vblank feature. */
	dev->irq_enabled = true;

	/* reset all the states of crtc/plane/encoder/connector */
	drm_mode_config_reset(dev);

	/* init kms poll क्रम handling hpd */
	drm_kms_helper_poll_init(dev);

	वापस 0;

err_unbind_all:
	component_unbind_all(dev->dev, dev);
err_निजी_cleanup:
	kirin_drm_निजी_cleanup(dev);
err_mode_config_cleanup:
	drm_mode_config_cleanup(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

अटल पूर्णांक kirin_drm_kms_cleanup(काष्ठा drm_device *dev)
अणु
	drm_kms_helper_poll_fini(dev);
	kirin_drm_निजी_cleanup(dev);
	drm_mode_config_cleanup(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक kirin_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा kirin_drm_data *driver_data;
	काष्ठा drm_device *drm_dev;
	पूर्णांक ret;

	driver_data = (काष्ठा kirin_drm_data *)of_device_get_match_data(dev);
	अगर (!driver_data)
		वापस -EINVAL;

	drm_dev = drm_dev_alloc(driver_data->driver, dev);
	अगर (IS_ERR(drm_dev))
		वापस PTR_ERR(drm_dev);
	dev_set_drvdata(dev, drm_dev);

	/* display controller init */
	ret = kirin_drm_kms_init(drm_dev, driver_data);
	अगर (ret)
		जाओ err_drm_dev_put;

	ret = drm_dev_रेजिस्टर(drm_dev, 0);
	अगर (ret)
		जाओ err_kms_cleanup;

	drm_fbdev_generic_setup(drm_dev, 32);

	वापस 0;

err_kms_cleanup:
	kirin_drm_kms_cleanup(drm_dev);
err_drm_dev_put:
	drm_dev_put(drm_dev);

	वापस ret;
पूर्ण

अटल व्योम kirin_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(drm_dev);
	kirin_drm_kms_cleanup(drm_dev);
	drm_dev_put(drm_dev);
पूर्ण

अटल स्थिर काष्ठा component_master_ops kirin_drm_ops = अणु
	.bind = kirin_drm_bind,
	.unbind = kirin_drm_unbind,
पूर्ण;

अटल पूर्णांक kirin_drm_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा component_match *match = शून्य;
	काष्ठा device_node *remote;

	remote = of_graph_get_remote_node(np, 0, 0);
	अगर (!remote)
		वापस -ENODEV;

	drm_of_component_match_add(dev, &match, compare_of, remote);
	of_node_put(remote);

	वापस component_master_add_with_match(dev, &kirin_drm_ops, match);
पूर्ण

अटल पूर्णांक kirin_drm_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &kirin_drm_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id kirin_drm_dt_ids[] = अणु
	अणु .compatible = "hisilicon,hi6220-ade",
	  .data = &ade_driver_data,
	पूर्ण,
	अणु /* end node */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, kirin_drm_dt_ids);

अटल काष्ठा platक्रमm_driver kirin_drm_platक्रमm_driver = अणु
	.probe = kirin_drm_platक्रमm_probe,
	.हटाओ = kirin_drm_platक्रमm_हटाओ,
	.driver = अणु
		.name = "kirin-drm",
		.of_match_table = kirin_drm_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(kirin_drm_platक्रमm_driver);

MODULE_AUTHOR("Xinliang Liu <xinliang.liu@linaro.org>");
MODULE_AUTHOR("Xinliang Liu <z.liuxinliang@hisilicon.com>");
MODULE_AUTHOR("Xinwei Kong <kong.kongxinwei@hisilicon.com>");
MODULE_DESCRIPTION("hisilicon Kirin SoCs' DRM master driver");
MODULE_LICENSE("GPL v2");
