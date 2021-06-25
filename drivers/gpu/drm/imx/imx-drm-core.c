<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Freescale i.MX drm driver
 *
 * Copyright (C) 2011 Sascha Hauer, Pengutronix
 */

#समावेश <linux/component.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/imx-ipu-v3.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "imx-drm.h"
#समावेश "ipuv3-plane.h"

#घोषणा MAX_CRTC	4

अटल पूर्णांक legacyfb_depth = 16;
module_param(legacyfb_depth, पूर्णांक, 0444);

DEFINE_DRM_GEM_CMA_FOPS(imx_drm_driver_fops);

व्योम imx_drm_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण
EXPORT_SYMBOL_GPL(imx_drm_connector_destroy);

अटल पूर्णांक imx_drm_atomic_check(काष्ठा drm_device *dev,
				काष्ठा drm_atomic_state *state)
अणु
	पूर्णांक ret;

	ret = drm_atomic_helper_check(dev, state);
	अगर (ret)
		वापस ret;

	/*
	 * Check modeset again in हाल crtc_state->mode_changed is
	 * updated in plane's ->atomic_check callback.
	 */
	ret = drm_atomic_helper_check_modeset(dev, state);
	अगर (ret)
		वापस ret;

	/* Assign PRG/PRE channels and check अगर all स्थिरrains are satisfied. */
	ret = ipu_planes_assign_pre(dev, state);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs imx_drm_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = imx_drm_atomic_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल व्योम imx_drm_atomic_commit_tail(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	bool plane_disabling = false;
	पूर्णांक i;

	drm_atomic_helper_commit_modeset_disables(dev, state);

	drm_atomic_helper_commit_planes(dev, state,
				DRM_PLANE_COMMIT_ACTIVE_ONLY |
				DRM_PLANE_COMMIT_NO_DISABLE_AFTER_MODESET);

	drm_atomic_helper_commit_modeset_enables(dev, state);

	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i) अणु
		अगर (drm_atomic_plane_disabling(old_plane_state, new_plane_state))
			plane_disabling = true;
	पूर्ण

	/*
	 * The flip करोne रुको is only strictly required by imx-drm अगर a deferred
	 * plane disable is in-flight. As the core requires blocking commits
	 * to रुको क्रम the flip it is करोne here unconditionally. This keeps the
	 * workitem around a bit दीर्घer than required क्रम the majority of
	 * non-blocking commits, but we accept that क्रम the sake of simplicity.
	 */
	drm_atomic_helper_रुको_क्रम_flip_करोne(dev, state);

	अगर (plane_disabling) अणु
		क्रम_each_old_plane_in_state(state, plane, old_plane_state, i)
			ipu_plane_disable_deferred(plane);

	पूर्ण

	drm_atomic_helper_commit_hw_करोne(state);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_helper_funcs imx_drm_mode_config_helpers = अणु
	.atomic_commit_tail = imx_drm_atomic_commit_tail,
पूर्ण;


पूर्णांक imx_drm_encoder_parse_of(काष्ठा drm_device *drm,
	काष्ठा drm_encoder *encoder, काष्ठा device_node *np)
अणु
	uपूर्णांक32_t crtc_mask = drm_of_find_possible_crtcs(drm, np);

	/*
	 * If we failed to find the CRTC(s) which this encoder is
	 * supposed to be connected to, it's because the CRTC has
	 * not been रेजिस्टरed yet.  Defer probing, and hope that
	 * the required CRTC is added later.
	 */
	अगर (crtc_mask == 0)
		वापस -EPROBE_DEFER;

	encoder->possible_crtcs = crtc_mask;

	/* FIXME: cloning support not clear, disable it all क्रम now */
	encoder->possible_clones = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(imx_drm_encoder_parse_of);

अटल स्थिर काष्ठा drm_ioctl_desc imx_drm_ioctls[] = अणु
	/* none so far */
पूर्ण;

अटल स्थिर काष्ठा drm_driver imx_drm_driver = अणु
	.driver_features	= DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	DRM_GEM_CMA_DRIVER_OPS,
	.ioctls			= imx_drm_ioctls,
	.num_ioctls		= ARRAY_SIZE(imx_drm_ioctls),
	.fops			= &imx_drm_driver_fops,
	.name			= "imx-drm",
	.desc			= "i.MX DRM graphics",
	.date			= "20120507",
	.major			= 1,
	.minor			= 0,
	.patchlevel		= 0,
पूर्ण;

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device_node *np = data;

	/* Special हाल क्रम DI, dev->of_node may not be set yet */
	अगर (म_भेद(dev->driver->name, "imx-ipuv3-crtc") == 0) अणु
		काष्ठा ipu_client_platक्रमmdata *pdata = dev->platक्रमm_data;

		वापस pdata->of_node == np;
	पूर्ण

	/* Special हाल क्रम LDB, one device क्रम two channels */
	अगर (of_node_name_eq(np, "lvds-channel")) अणु
		np = of_get_parent(np);
		of_node_put(np);
	पूर्ण

	वापस dev->of_node == np;
पूर्ण

अटल पूर्णांक imx_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm;
	पूर्णांक ret;

	drm = drm_dev_alloc(&imx_drm_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	/*
	 * enable drm irq mode.
	 * - with irq_enabled = true, we can use the vblank feature.
	 *
	 * P.S. note that we wouldn't use drm irq handler but
	 *      just specअगरic driver own one instead because
	 *      drm framework supports only one irq handler and
	 *      drivers can well take care of their पूर्णांकerrupts
	 */
	drm->irq_enabled = true;

	/*
	 * set max width and height as शेष value(4096x4096).
	 * this value would be used to check framebuffer size limitation
	 * at drm_mode_addfb().
	 */
	drm->mode_config.min_width = 1;
	drm->mode_config.min_height = 1;
	drm->mode_config.max_width = 4096;
	drm->mode_config.max_height = 4096;
	drm->mode_config.funcs = &imx_drm_mode_config_funcs;
	drm->mode_config.helper_निजी = &imx_drm_mode_config_helpers;
	drm->mode_config.allow_fb_modअगरiers = true;
	drm->mode_config.normalize_zpos = true;

	ret = drmm_mode_config_init(drm);
	अगर (ret)
		जाओ err_kms;

	ret = drm_vblank_init(drm, MAX_CRTC);
	अगर (ret)
		जाओ err_kms;

	dev_set_drvdata(dev, drm);

	/* Now try and bind all our sub-components */
	ret = component_bind_all(dev, drm);
	अगर (ret)
		जाओ err_kms;

	drm_mode_config_reset(drm);

	/*
	 * All components are now initialised, so setup the fb helper.
	 * The fb helper takes copies of key hardware inक्रमmation, so the
	 * crtcs/connectors/encoders must not change after this poपूर्णांक.
	 */
	अगर (legacyfb_depth != 16 && legacyfb_depth != 32) अणु
		dev_warn(dev, "Invalid legacyfb_depth.  Defaulting to 16bpp\n");
		legacyfb_depth = 16;
	पूर्ण

	drm_kms_helper_poll_init(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ err_poll_fini;

	drm_fbdev_generic_setup(drm, legacyfb_depth);

	वापस 0;

err_poll_fini:
	drm_kms_helper_poll_fini(drm);
	component_unbind_all(drm->dev, drm);
err_kms:
	drm_dev_put(drm);

	वापस ret;
पूर्ण

अटल व्योम imx_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(drm);

	drm_kms_helper_poll_fini(drm);

	component_unbind_all(drm->dev, drm);

	drm_dev_put(drm);

	dev_set_drvdata(dev, शून्य);
पूर्ण

अटल स्थिर काष्ठा component_master_ops imx_drm_ops = अणु
	.bind = imx_drm_bind,
	.unbind = imx_drm_unbind,
पूर्ण;

अटल पूर्णांक imx_drm_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = drm_of_component_probe(&pdev->dev, compare_of, &imx_drm_ops);

	अगर (!ret)
		ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

	वापस ret;
पूर्ण

अटल पूर्णांक imx_drm_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &imx_drm_ops);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक imx_drm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(drm_dev);
पूर्ण

अटल पूर्णांक imx_drm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(drm_dev);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(imx_drm_pm_ops, imx_drm_suspend, imx_drm_resume);

अटल स्थिर काष्ठा of_device_id imx_drm_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-display-subsystem", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_drm_dt_ids);

अटल काष्ठा platक्रमm_driver imx_drm_pdrv = अणु
	.probe		= imx_drm_platक्रमm_probe,
	.हटाओ		= imx_drm_platक्रमm_हटाओ,
	.driver		= अणु
		.name	= "imx-drm",
		.pm	= &imx_drm_pm_ops,
		.of_match_table = imx_drm_dt_ids,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&imx_drm_pdrv,
	&ipu_drm_driver,
पूर्ण;

अटल पूर्णांक __init imx_drm_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_init(imx_drm_init);

अटल व्योम __निकास imx_drm_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(imx_drm_निकास);

MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_DESCRIPTION("i.MX drm driver core");
MODULE_LICENSE("GPL");
