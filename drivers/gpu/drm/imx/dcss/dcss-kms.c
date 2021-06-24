<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge_connector.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "dcss-dev.h"
#समावेश "dcss-kms.h"

DEFINE_DRM_GEM_CMA_FOPS(dcss_cma_fops);

अटल स्थिर काष्ठा drm_mode_config_funcs dcss_drm_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_driver dcss_kms_driver = अणु
	.driver_features	= DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	DRM_GEM_CMA_DRIVER_OPS,
	.fops			= &dcss_cma_fops,
	.name			= "imx-dcss",
	.desc			= "i.MX8MQ Display Subsystem",
	.date			= "20190917",
	.major			= 1,
	.minor			= 0,
	.patchlevel		= 0,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_helper_funcs dcss_mode_config_helpers = अणु
	.atomic_commit_tail = drm_atomic_helper_commit_tail_rpm,
पूर्ण;

अटल व्योम dcss_kms_mode_config_init(काष्ठा dcss_kms_dev *kms)
अणु
	काष्ठा drm_mode_config *config = &kms->base.mode_config;

	drm_mode_config_init(&kms->base);

	config->min_width = 1;
	config->min_height = 1;
	config->max_width = 4096;
	config->max_height = 4096;
	config->allow_fb_modअगरiers = true;
	config->normalize_zpos = true;

	config->funcs = &dcss_drm_mode_config_funcs;
	config->helper_निजी = &dcss_mode_config_helpers;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs dcss_kms_simple_encoder_funcs = अणु
	.destroy = drm_encoder_cleanup,
पूर्ण;

अटल पूर्णांक dcss_kms_bridge_connector_init(काष्ठा dcss_kms_dev *kms)
अणु
	काष्ठा drm_device *ddev = &kms->base;
	काष्ठा drm_encoder *encoder = &kms->encoder;
	काष्ठा drm_crtc *crtc = (काष्ठा drm_crtc *)&kms->crtc;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	पूर्णांक ret;

	ret = drm_of_find_panel_or_bridge(ddev->dev->of_node, 0, 0,
					  &panel, &bridge);
	अगर (ret)
		वापस ret;

	अगर (!bridge) अणु
		dev_err(ddev->dev, "No bridge found %d.\n", ret);
		वापस -ENODEV;
	पूर्ण

	encoder->possible_crtcs = drm_crtc_mask(crtc);

	ret = drm_encoder_init(&kms->base, encoder,
			       &dcss_kms_simple_encoder_funcs,
			       DRM_MODE_ENCODER_NONE, शून्य);
	अगर (ret) अणु
		dev_err(ddev->dev, "Failed initializing encoder %d.\n", ret);
		वापस ret;
	पूर्ण

	ret = drm_bridge_attach(encoder, bridge, शून्य,
				DRM_BRIDGE_ATTACH_NO_CONNECTOR);
	अगर (ret < 0) अणु
		dev_err(ddev->dev, "Unable to attach bridge %pOF\n",
			bridge->of_node);
		वापस ret;
	पूर्ण

	kms->connector = drm_bridge_connector_init(ddev, encoder);
	अगर (IS_ERR(kms->connector)) अणु
		dev_err(ddev->dev, "Unable to create bridge connector.\n");
		वापस PTR_ERR(kms->connector);
	पूर्ण

	drm_connector_attach_encoder(kms->connector, encoder);

	वापस 0;
पूर्ण

काष्ठा dcss_kms_dev *dcss_kms_attach(काष्ठा dcss_dev *dcss)
अणु
	काष्ठा dcss_kms_dev *kms;
	काष्ठा drm_device *drm;
	काष्ठा dcss_crtc *crtc;
	पूर्णांक ret;

	kms = devm_drm_dev_alloc(dcss->dev, &dcss_kms_driver,
				 काष्ठा dcss_kms_dev, base);
	अगर (IS_ERR(kms))
		वापस kms;

	drm = &kms->base;
	crtc = &kms->crtc;

	drm->dev_निजी = dcss;

	dcss_kms_mode_config_init(kms);

	ret = drm_vblank_init(drm, 1);
	अगर (ret)
		जाओ cleanup_mode_config;

	drm->irq_enabled = true;

	ret = dcss_kms_bridge_connector_init(kms);
	अगर (ret)
		जाओ cleanup_mode_config;

	ret = dcss_crtc_init(crtc, drm);
	अगर (ret)
		जाओ cleanup_mode_config;

	drm_mode_config_reset(drm);

	drm_kms_helper_poll_init(drm);

	drm_bridge_connector_enable_hpd(kms->connector);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ cleanup_crtc;

	drm_fbdev_generic_setup(drm, 32);

	वापस kms;

cleanup_crtc:
	drm_bridge_connector_disable_hpd(kms->connector);
	drm_kms_helper_poll_fini(drm);
	dcss_crtc_deinit(crtc, drm);

cleanup_mode_config:
	drm_mode_config_cleanup(drm);
	drm->dev_निजी = शून्य;

	वापस ERR_PTR(ret);
पूर्ण

व्योम dcss_kms_detach(काष्ठा dcss_kms_dev *kms)
अणु
	काष्ठा drm_device *drm = &kms->base;

	drm_dev_unरेजिस्टर(drm);
	drm_bridge_connector_disable_hpd(kms->connector);
	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutकरोwn(drm);
	drm_crtc_vblank_off(&kms->crtc.base);
	drm->irq_enabled = false;
	drm_mode_config_cleanup(drm);
	dcss_crtc_deinit(&kms->crtc, drm);
	drm->dev_निजी = शून्य;
पूर्ण
