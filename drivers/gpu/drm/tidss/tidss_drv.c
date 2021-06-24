<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/console.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "tidss_dispc.h"
#समावेश "tidss_drv.h"
#समावेश "tidss_kms.h"
#समावेश "tidss_irq.h"

/* Power management */

पूर्णांक tidss_runसमय_get(काष्ठा tidss_device *tidss)
अणु
	पूर्णांक r;

	dev_dbg(tidss->dev, "%s\n", __func__);

	r = pm_runसमय_get_sync(tidss->dev);
	WARN_ON(r < 0);
	वापस r < 0 ? r : 0;
पूर्ण

व्योम tidss_runसमय_put(काष्ठा tidss_device *tidss)
अणु
	पूर्णांक r;

	dev_dbg(tidss->dev, "%s\n", __func__);

	r = pm_runसमय_put_sync(tidss->dev);
	WARN_ON(r < 0);
पूर्ण

अटल पूर्णांक __maybe_unused tidss_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tidss_device *tidss = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	वापस dispc_runसमय_suspend(tidss->dispc);
पूर्ण

अटल पूर्णांक __maybe_unused tidss_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tidss_device *tidss = dev_get_drvdata(dev);
	पूर्णांक r;

	dev_dbg(dev, "%s\n", __func__);

	r = dispc_runसमय_resume(tidss->dispc);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tidss_suspend(काष्ठा device *dev)
अणु
	काष्ठा tidss_device *tidss = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	वापस drm_mode_config_helper_suspend(&tidss->ddev);
पूर्ण

अटल पूर्णांक __maybe_unused tidss_resume(काष्ठा device *dev)
अणु
	काष्ठा tidss_device *tidss = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	वापस drm_mode_config_helper_resume(&tidss->ddev);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल स्थिर काष्ठा dev_pm_ops tidss_pm_ops = अणु
	.runसमय_suspend = tidss_pm_runसमय_suspend,
	.runसमय_resume = tidss_pm_runसमय_resume,
	SET_SYSTEM_SLEEP_PM_OPS(tidss_suspend, tidss_resume)
पूर्ण;

#पूर्ण_अगर /* CONFIG_PM */

/* DRM device Inक्रमmation */

अटल व्योम tidss_release(काष्ठा drm_device *ddev)
अणु
	drm_kms_helper_poll_fini(ddev);
पूर्ण

DEFINE_DRM_GEM_CMA_FOPS(tidss_fops);

अटल स्थिर काष्ठा drm_driver tidss_driver = अणु
	.driver_features	= DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops			= &tidss_fops,
	.release		= tidss_release,
	DRM_GEM_CMA_DRIVER_OPS_VMAP,
	.name			= "tidss",
	.desc			= "TI Keystone DSS",
	.date			= "20180215",
	.major			= 1,
	.minor			= 0,

	.irq_preinstall		= tidss_irq_preinstall,
	.irq_postinstall	= tidss_irq_postinstall,
	.irq_handler		= tidss_irq_handler,
	.irq_uninstall		= tidss_irq_uninstall,
पूर्ण;

अटल पूर्णांक tidss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tidss_device *tidss;
	काष्ठा drm_device *ddev;
	पूर्णांक ret;
	पूर्णांक irq;

	dev_dbg(dev, "%s\n", __func__);

	tidss = devm_drm_dev_alloc(&pdev->dev, &tidss_driver,
				   काष्ठा tidss_device, ddev);
	अगर (IS_ERR(tidss))
		वापस PTR_ERR(tidss);

	ddev = &tidss->ddev;

	tidss->dev = dev;
	tidss->feat = of_device_get_match_data(dev);

	platक्रमm_set_drvdata(pdev, tidss);

	ret = dispc_init(tidss);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize dispc: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev);

#अगर_अघोषित CONFIG_PM
	/* If we करोn't have PM, we need to call resume manually */
	dispc_runसमय_resume(tidss->dispc);
#पूर्ण_अगर

	ret = tidss_modeset_init(tidss);
	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to init DRM/KMS (%d)\n", ret);
		जाओ err_runसमय_suspend;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_runसमय_suspend;
	पूर्ण

	ret = drm_irq_install(ddev, irq);
	अगर (ret) अणु
		dev_err(dev, "drm_irq_install failed: %d\n", ret);
		जाओ err_runसमय_suspend;
	पूर्ण

	drm_kms_helper_poll_init(ddev);

	drm_mode_config_reset(ddev);

	ret = drm_dev_रेजिस्टर(ddev, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to register DRM device\n");
		जाओ err_irq_uninstall;
	पूर्ण

	drm_fbdev_generic_setup(ddev, 32);

	dev_dbg(dev, "%s done\n", __func__);

	वापस 0;

err_irq_uninstall:
	drm_irq_uninstall(ddev);

err_runसमय_suspend:
#अगर_अघोषित CONFIG_PM
	dispc_runसमय_suspend(tidss->dispc);
#पूर्ण_अगर
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tidss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tidss_device *tidss = platक्रमm_get_drvdata(pdev);
	काष्ठा drm_device *ddev = &tidss->ddev;

	dev_dbg(dev, "%s\n", __func__);

	drm_dev_unरेजिस्टर(ddev);

	drm_atomic_helper_shutकरोwn(ddev);

	drm_irq_uninstall(ddev);

#अगर_अघोषित CONFIG_PM
	/* If we करोn't have PM, we need to call suspend manually */
	dispc_runसमय_suspend(tidss->dispc);
#पूर्ण_अगर
	pm_runसमय_disable(dev);

	/* devm allocated dispc goes away with the dev so mark it शून्य */
	dispc_हटाओ(tidss);

	dev_dbg(dev, "%s done\n", __func__);

	वापस 0;
पूर्ण

अटल व्योम tidss_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	drm_atomic_helper_shutकरोwn(platक्रमm_get_drvdata(pdev));
पूर्ण

अटल स्थिर काष्ठा of_device_id tidss_of_table[] = अणु
	अणु .compatible = "ti,k2g-dss", .data = &dispc_k2g_feats, पूर्ण,
	अणु .compatible = "ti,am65x-dss", .data = &dispc_am65x_feats, पूर्ण,
	अणु .compatible = "ti,j721e-dss", .data = &dispc_j721e_feats, पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, tidss_of_table);

अटल काष्ठा platक्रमm_driver tidss_platक्रमm_driver = अणु
	.probe		= tidss_probe,
	.हटाओ		= tidss_हटाओ,
	.shutकरोwn	= tidss_shutकरोwn,
	.driver		= अणु
		.name	= "tidss",
#अगर_घोषित CONFIG_PM
		.pm	= &tidss_pm_ops,
#पूर्ण_अगर
		.of_match_table = tidss_of_table,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(tidss_platक्रमm_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("TI Keystone DSS Driver");
MODULE_LICENSE("GPL v2");
