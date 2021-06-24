<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_fbdev.h"
#समावेश "exynos_drm_g2d.h"
#समावेश "exynos_drm_gem.h"
#समावेश "exynos_drm_ipp.h"
#समावेश "exynos_drm_plane.h"
#समावेश "exynos_drm_vidi.h"

#घोषणा DRIVER_NAME	"exynos"
#घोषणा DRIVER_DESC	"Samsung SoC DRM"
#घोषणा DRIVER_DATE	"20180330"

/*
 * Interface history:
 *
 * 1.0 - Original version
 * 1.1 - Upgrade IPP driver to version 2.0
 */
#घोषणा DRIVER_MAJOR	1
#घोषणा DRIVER_MINOR	1

अटल पूर्णांक exynos_drm_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा drm_exynos_file_निजी *file_priv;
	पूर्णांक ret;

	file_priv = kzalloc(माप(*file_priv), GFP_KERNEL);
	अगर (!file_priv)
		वापस -ENOMEM;

	file->driver_priv = file_priv;
	ret = g2d_खोलो(dev, file);
	अगर (ret)
		जाओ err_file_priv_मुक्त;

	वापस ret;

err_file_priv_मुक्त:
	kमुक्त(file_priv);
	file->driver_priv = शून्य;
	वापस ret;
पूर्ण

अटल व्योम exynos_drm_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	g2d_बंद(dev, file);
	kमुक्त(file->driver_priv);
	file->driver_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_ioctl_desc exynos_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(EXYNOS_GEM_CREATE, exynos_drm_gem_create_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_GEM_MAP, exynos_drm_gem_map_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_GEM_GET, exynos_drm_gem_get_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_VIDI_CONNECTION, vidi_connection_ioctl,
			DRM_AUTH),
	DRM_IOCTL_DEF_DRV(EXYNOS_G2D_GET_VER, exynos_g2d_get_ver_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_G2D_SET_CMDLIST, exynos_g2d_set_cmdlist_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_G2D_EXEC, exynos_g2d_exec_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_IPP_GET_RESOURCES,
			exynos_drm_ipp_get_res_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_IPP_GET_CAPS, exynos_drm_ipp_get_caps_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_IPP_GET_LIMITS,
			exynos_drm_ipp_get_limits_ioctl,
			DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(EXYNOS_IPP_COMMIT, exynos_drm_ipp_commit_ioctl,
			DRM_RENDER_ALLOW),
पूर्ण;

अटल स्थिर काष्ठा file_operations exynos_drm_driver_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= drm_खोलो,
	.mmap		= exynos_drm_gem_mmap,
	.poll		= drm_poll,
	.पढ़ो		= drm_पढ़ो,
	.unlocked_ioctl	= drm_ioctl,
	.compat_ioctl = drm_compat_ioctl,
	.release	= drm_release,
पूर्ण;

अटल स्थिर काष्ठा drm_driver exynos_drm_driver = अणु
	.driver_features	= DRIVER_MODESET | DRIVER_GEM
				  | DRIVER_ATOMIC | DRIVER_RENDER,
	.खोलो			= exynos_drm_खोलो,
	.lastबंद		= drm_fb_helper_lastबंद,
	.postबंद		= exynos_drm_postबंद,
	.dumb_create		= exynos_drm_gem_dumb_create,
	.prime_handle_to_fd	= drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle	= drm_gem_prime_fd_to_handle,
	.gem_prime_import	= exynos_drm_gem_prime_import,
	.gem_prime_import_sg_table	= exynos_drm_gem_prime_import_sg_table,
	.gem_prime_mmap		= exynos_drm_gem_prime_mmap,
	.ioctls			= exynos_ioctls,
	.num_ioctls		= ARRAY_SIZE(exynos_ioctls),
	.fops			= &exynos_drm_driver_fops,
	.name	= DRIVER_NAME,
	.desc	= DRIVER_DESC,
	.date	= DRIVER_DATE,
	.major	= DRIVER_MAJOR,
	.minor	= DRIVER_MINOR,
पूर्ण;

अटल पूर्णांक exynos_drm_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	वापस  drm_mode_config_helper_suspend(drm_dev);
पूर्ण

अटल व्योम exynos_drm_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(dev);

	drm_mode_config_helper_resume(drm_dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops exynos_drm_pm_ops = अणु
	.prepare = exynos_drm_suspend,
	.complete = exynos_drm_resume,
पूर्ण;

/* क्रमward declaration */
अटल काष्ठा platक्रमm_driver exynos_drm_platक्रमm_driver;

काष्ठा exynos_drm_driver_info अणु
	काष्ठा platक्रमm_driver *driver;
	अचिन्हित पूर्णांक flags;
पूर्ण;

#घोषणा DRM_COMPONENT_DRIVER	BIT(0)	/* supports component framework */
#घोषणा DRM_VIRTUAL_DEVICE	BIT(1)	/* create भव platक्रमm device */
#घोषणा DRM_FIMC_DEVICE		BIT(2)	/* devices shared with V4L2 subप्रणाली */

#घोषणा DRV_PTR(drv, cond) (IS_ENABLED(cond) ? &drv : शून्य)

/*
 * Connector drivers should not be placed beक्रमe associated crtc drivers,
 * because connector requires pipe number of its crtc during initialization.
 */
अटल काष्ठा exynos_drm_driver_info exynos_drm_drivers[] = अणु
	अणु
		DRV_PTR(fimd_driver, CONFIG_DRM_EXYNOS_FIMD),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(exynos5433_decon_driver, CONFIG_DRM_EXYNOS5433_DECON),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(decon_driver, CONFIG_DRM_EXYNOS7_DECON),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(mixer_driver, CONFIG_DRM_EXYNOS_MIXER),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(mic_driver, CONFIG_DRM_EXYNOS_MIC),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(dp_driver, CONFIG_DRM_EXYNOS_DP),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(dsi_driver, CONFIG_DRM_EXYNOS_DSI),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(hdmi_driver, CONFIG_DRM_EXYNOS_HDMI),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(vidi_driver, CONFIG_DRM_EXYNOS_VIDI),
		DRM_COMPONENT_DRIVER | DRM_VIRTUAL_DEVICE
	पूर्ण, अणु
		DRV_PTR(g2d_driver, CONFIG_DRM_EXYNOS_G2D),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(fimc_driver, CONFIG_DRM_EXYNOS_FIMC),
		DRM_COMPONENT_DRIVER | DRM_FIMC_DEVICE,
	पूर्ण, अणु
		DRV_PTR(rotator_driver, CONFIG_DRM_EXYNOS_ROTATOR),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(scaler_driver, CONFIG_DRM_EXYNOS_SCALER),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		DRV_PTR(gsc_driver, CONFIG_DRM_EXYNOS_GSC),
		DRM_COMPONENT_DRIVER
	पूर्ण, अणु
		&exynos_drm_platक्रमm_driver,
		DRM_VIRTUAL_DEVICE
	पूर्ण
पूर्ण;

अटल पूर्णांक compare_dev(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev == (काष्ठा device *)data;
पूर्ण

अटल काष्ठा component_match *exynos_drm_match_add(काष्ठा device *dev)
अणु
	काष्ठा component_match *match = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(exynos_drm_drivers); ++i) अणु
		काष्ठा exynos_drm_driver_info *info = &exynos_drm_drivers[i];
		काष्ठा device *p = शून्य, *d;

		अगर (!info->driver || !(info->flags & DRM_COMPONENT_DRIVER))
			जारी;

		जबतक ((d = platक्रमm_find_device_by_driver(p, &info->driver->driver))) अणु
			put_device(p);

			अगर (!(info->flags & DRM_FIMC_DEVICE) ||
			    exynos_drm_check_fimc_device(d) == 0)
				component_match_add(dev, &match,
						    compare_dev, d);
			p = d;
		पूर्ण
		put_device(p);
	पूर्ण

	वापस match ?: ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक exynos_drm_bind(काष्ठा device *dev)
अणु
	काष्ठा exynos_drm_निजी *निजी;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_device *drm;
	अचिन्हित पूर्णांक clone_mask;
	पूर्णांक ret;

	drm = drm_dev_alloc(&exynos_drm_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	निजी = kzalloc(माप(काष्ठा exynos_drm_निजी), GFP_KERNEL);
	अगर (!निजी) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_drm;
	पूर्ण

	init_रुकोqueue_head(&निजी->रुको);
	spin_lock_init(&निजी->lock);

	dev_set_drvdata(dev, drm);
	drm->dev_निजी = (व्योम *)निजी;

	drm_mode_config_init(drm);

	exynos_drm_mode_config_init(drm);

	/* setup possible_clones. */
	clone_mask = 0;
	list_क्रम_each_entry(encoder, &drm->mode_config.encoder_list, head)
		clone_mask |= drm_encoder_mask(encoder);

	list_क्रम_each_entry(encoder, &drm->mode_config.encoder_list, head)
		encoder->possible_clones = clone_mask;

	/* Try to bind all sub drivers. */
	ret = component_bind_all(drm->dev, drm);
	अगर (ret)
		जाओ err_mode_config_cleanup;

	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	अगर (ret)
		जाओ err_unbind_all;

	drm_mode_config_reset(drm);

	/*
	 * enable drm irq mode.
	 * - with irq_enabled = true, we can use the vblank feature.
	 *
	 * P.S. note that we wouldn't use drm irq handler but
	 *	just specअगरic driver own one instead because
	 *	drm framework supports only one irq handler.
	 */
	drm->irq_enabled = true;

	/* init kms poll क्रम handling hpd */
	drm_kms_helper_poll_init(drm);

	ret = exynos_drm_fbdev_init(drm);
	अगर (ret)
		जाओ err_cleanup_poll;

	/* रेजिस्टर the DRM device */
	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0)
		जाओ err_cleanup_fbdev;

	वापस 0;

err_cleanup_fbdev:
	exynos_drm_fbdev_fini(drm);
err_cleanup_poll:
	drm_kms_helper_poll_fini(drm);
err_unbind_all:
	component_unbind_all(drm->dev, drm);
err_mode_config_cleanup:
	drm_mode_config_cleanup(drm);
	exynos_drm_cleanup_dma(drm);
	kमुक्त(निजी);
err_मुक्त_drm:
	drm_dev_put(drm);

	वापस ret;
पूर्ण

अटल व्योम exynos_drm_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);

	drm_dev_unरेजिस्टर(drm);

	exynos_drm_fbdev_fini(drm);
	drm_kms_helper_poll_fini(drm);

	component_unbind_all(drm->dev, drm);
	drm_mode_config_cleanup(drm);
	exynos_drm_cleanup_dma(drm);

	kमुक्त(drm->dev_निजी);
	drm->dev_निजी = शून्य;
	dev_set_drvdata(dev, शून्य);

	drm_dev_put(drm);
पूर्ण

अटल स्थिर काष्ठा component_master_ops exynos_drm_ops = अणु
	.bind		= exynos_drm_bind,
	.unbind		= exynos_drm_unbind,
पूर्ण;

अटल पूर्णांक exynos_drm_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा component_match *match;

	pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	match = exynos_drm_match_add(&pdev->dev);
	अगर (IS_ERR(match))
		वापस PTR_ERR(match);

	वापस component_master_add_with_match(&pdev->dev, &exynos_drm_ops,
					       match);
पूर्ण

अटल पूर्णांक exynos_drm_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &exynos_drm_ops);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_drm_platक्रमm_driver = अणु
	.probe	= exynos_drm_platक्रमm_probe,
	.हटाओ	= exynos_drm_platक्रमm_हटाओ,
	.driver	= अणु
		.name	= "exynos-drm",
		.pm	= &exynos_drm_pm_ops,
	पूर्ण,
पूर्ण;

अटल व्योम exynos_drm_unरेजिस्टर_devices(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(exynos_drm_drivers) - 1; i >= 0; --i) अणु
		काष्ठा exynos_drm_driver_info *info = &exynos_drm_drivers[i];
		काष्ठा device *dev;

		अगर (!info->driver || !(info->flags & DRM_VIRTUAL_DEVICE))
			जारी;

		जबतक ((dev = platक्रमm_find_device_by_driver(शून्य,
						&info->driver->driver))) अणु
			put_device(dev);
			platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक exynos_drm_रेजिस्टर_devices(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(exynos_drm_drivers); ++i) अणु
		काष्ठा exynos_drm_driver_info *info = &exynos_drm_drivers[i];

		अगर (!info->driver || !(info->flags & DRM_VIRTUAL_DEVICE))
			जारी;

		pdev = platक्रमm_device_रेजिस्टर_simple(
					info->driver->driver.name, -1, शून्य, 0);
		अगर (IS_ERR(pdev))
			जाओ fail;
	पूर्ण

	वापस 0;
fail:
	exynos_drm_unरेजिस्टर_devices();
	वापस PTR_ERR(pdev);
पूर्ण

अटल व्योम exynos_drm_unरेजिस्टर_drivers(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(exynos_drm_drivers) - 1; i >= 0; --i) अणु
		काष्ठा exynos_drm_driver_info *info = &exynos_drm_drivers[i];

		अगर (!info->driver)
			जारी;

		platक्रमm_driver_unरेजिस्टर(info->driver);
	पूर्ण
पूर्ण

अटल पूर्णांक exynos_drm_रेजिस्टर_drivers(व्योम)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(exynos_drm_drivers); ++i) अणु
		काष्ठा exynos_drm_driver_info *info = &exynos_drm_drivers[i];

		अगर (!info->driver)
			जारी;

		ret = platक्रमm_driver_रेजिस्टर(info->driver);
		अगर (ret)
			जाओ fail;
	पूर्ण
	वापस 0;
fail:
	exynos_drm_unरेजिस्टर_drivers();
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_drm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = exynos_drm_रेजिस्टर_devices();
	अगर (ret)
		वापस ret;

	ret = exynos_drm_रेजिस्टर_drivers();
	अगर (ret)
		जाओ err_unरेजिस्टर_pdevs;

	वापस 0;

err_unरेजिस्टर_pdevs:
	exynos_drm_unरेजिस्टर_devices();

	वापस ret;
पूर्ण

अटल व्योम exynos_drm_निकास(व्योम)
अणु
	exynos_drm_unरेजिस्टर_drivers();
	exynos_drm_unरेजिस्टर_devices();
पूर्ण

module_init(exynos_drm_init);
module_निकास(exynos_drm_निकास);

MODULE_AUTHOR("Inki Dae <inki.dae@samsung.com>");
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_AUTHOR("Seung-Woo Kim <sw0312.kim@samsung.com>");
MODULE_DESCRIPTION("Samsung SoC DRM Driver");
MODULE_LICENSE("GPL");
