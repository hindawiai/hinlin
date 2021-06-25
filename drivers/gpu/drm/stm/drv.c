<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Authors: Philippe Cornu <philippe.cornu@st.com>
 *          Yannick Fertre <yannick.fertre@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          Mickael Reulier <mickael.reulier@st.com>
 */

#समावेश <linux/component.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "ltdc.h"

#घोषणा STM_MAX_FB_WIDTH	2048
#घोषणा STM_MAX_FB_HEIGHT	2048 /* same as width to handle orientation */

अटल स्थिर काष्ठा drm_mode_config_funcs drv_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक sपंचांग_gem_cma_dumb_create(काष्ठा drm_file *file,
				   काष्ठा drm_device *dev,
				   काष्ठा drm_mode_create_dumb *args)
अणु
	अचिन्हित पूर्णांक min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);

	/*
	 * in order to optimize data transfer, pitch is aligned on
	 * 128 bytes, height is aligned on 4 bytes
	 */
	args->pitch = roundup(min_pitch, 128);
	args->height = roundup(args->height, 4);

	वापस drm_gem_cma_dumb_create_पूर्णांकernal(file, dev, args);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(drv_driver_fops);

अटल स्थिर काष्ठा drm_driver drv_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.name = "stm",
	.desc = "STMicroelectronics SoC DRM",
	.date = "20170330",
	.major = 1,
	.minor = 0,
	.patchlevel = 0,
	.fops = &drv_driver_fops,
	DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(sपंचांग_gem_cma_dumb_create),
पूर्ण;

अटल पूर्णांक drv_load(काष्ठा drm_device *ddev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ddev->dev);
	काष्ठा ltdc_device *ldev;
	पूर्णांक ret;

	DRM_DEBUG("%s\n", __func__);

	ldev = devm_kzalloc(ddev->dev, माप(*ldev), GFP_KERNEL);
	अगर (!ldev)
		वापस -ENOMEM;

	ddev->dev_निजी = (व्योम *)ldev;

	ret = drmm_mode_config_init(ddev);
	अगर (ret)
		वापस ret;

	/*
	 * set max width and height as शेष value.
	 * this value would be used to check framebuffer size limitation
	 * at drm_mode_addfb().
	 */
	ddev->mode_config.min_width = 0;
	ddev->mode_config.min_height = 0;
	ddev->mode_config.max_width = STM_MAX_FB_WIDTH;
	ddev->mode_config.max_height = STM_MAX_FB_HEIGHT;
	ddev->mode_config.funcs = &drv_mode_config_funcs;

	ret = ltdc_load(ddev);
	अगर (ret)
		वापस ret;

	drm_mode_config_reset(ddev);
	drm_kms_helper_poll_init(ddev);

	platक्रमm_set_drvdata(pdev, ddev);

	वापस 0;
पूर्ण

अटल व्योम drv_unload(काष्ठा drm_device *ddev)
अणु
	DRM_DEBUG("%s\n", __func__);

	drm_kms_helper_poll_fini(ddev);
	ltdc_unload(ddev);
पूर्ण

अटल __maybe_unused पूर्णांक drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	काष्ठा drm_atomic_state *state;

	WARN_ON(ldev->suspend_state);

	state = drm_atomic_helper_suspend(ddev);
	अगर (IS_ERR(state))
		वापस PTR_ERR(state);

	ldev->suspend_state = state;
	pm_runसमय_क्रमce_suspend(dev);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक drv_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा ltdc_device *ldev = ddev->dev_निजी;
	पूर्णांक ret;

	अगर (WARN_ON(!ldev->suspend_state))
		वापस -ENOENT;

	pm_runसमय_क्रमce_resume(dev);
	ret = drm_atomic_helper_resume(ddev, ldev->suspend_state);
	अगर (ret)
		pm_runसमय_क्रमce_suspend(dev);

	ldev->suspend_state = शून्य;

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक drv_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);

	DRM_DEBUG_DRIVER("\n");
	ltdc_suspend(ddev);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक drv_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);

	DRM_DEBUG_DRIVER("\n");
	वापस ltdc_resume(ddev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops drv_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(drv_suspend, drv_resume)
	SET_RUNTIME_PM_OPS(drv_runसमय_suspend,
			   drv_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक sपंचांग_drm_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा drm_device *ddev;
	पूर्णांक ret;

	DRM_DEBUG("%s\n", __func__);

	dma_set_coherent_mask(dev, DMA_BIT_MASK(32));

	ddev = drm_dev_alloc(&drv_driver, dev);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	ret = drv_load(ddev);
	अगर (ret)
		जाओ err_put;

	ret = drm_dev_रेजिस्टर(ddev, 0);
	अगर (ret)
		जाओ err_put;

	drm_fbdev_generic_setup(ddev, 16);

	वापस 0;

err_put:
	drm_dev_put(ddev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग_drm_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *ddev = platक्रमm_get_drvdata(pdev);

	DRM_DEBUG("%s\n", __func__);

	drm_dev_unरेजिस्टर(ddev);
	drv_unload(ddev);
	drm_dev_put(ddev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id drv_dt_ids[] = अणु
	अणु .compatible = "st,stm32-ltdc"पूर्ण,
	अणु /* end node */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, drv_dt_ids);

अटल काष्ठा platक्रमm_driver sपंचांग_drm_platक्रमm_driver = अणु
	.probe = sपंचांग_drm_platक्रमm_probe,
	.हटाओ = sपंचांग_drm_platक्रमm_हटाओ,
	.driver = अणु
		.name = "stm32-display",
		.of_match_table = drv_dt_ids,
		.pm = &drv_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांग_drm_platक्रमm_driver);

MODULE_AUTHOR("Philippe Cornu <philippe.cornu@st.com>");
MODULE_AUTHOR("Yannick Fertre <yannick.fertre@st.com>");
MODULE_AUTHOR("Fabien Dessenne <fabien.dessenne@st.com>");
MODULE_AUTHOR("Mickael Reulier <mickael.reulier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics ST DRM LTDC driver");
MODULE_LICENSE("GPL v2");
