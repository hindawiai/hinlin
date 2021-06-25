<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ZynqMP DisplayPort Subप्रणाली Driver
 *
 * Copyright (C) 2017 - 2020 Xilinx, Inc.
 *
 * Authors:
 * - Hyun Woo Kwon <hyun.kwon@xilinx.com>
 * - Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mode_config.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "zynqmp_disp.h"
#समावेश "zynqmp_dp.h"
#समावेश "zynqmp_dpsub.h"

/* -----------------------------------------------------------------------------
 * Dumb Buffer & Framebuffer Allocation
 */

अटल पूर्णांक zynqmp_dpsub_dumb_create(काष्ठा drm_file *file_priv,
				    काष्ठा drm_device *drm,
				    काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा zynqmp_dpsub *dpsub = to_zynqmp_dpsub(drm);
	अचिन्हित पूर्णांक pitch = DIV_ROUND_UP(args->width * args->bpp, 8);

	/* Enक्रमce the alignment स्थिरraपूर्णांकs of the DMA engine. */
	args->pitch = ALIGN(pitch, dpsub->dma_align);

	वापस drm_gem_cma_dumb_create_पूर्णांकernal(file_priv, drm, args);
पूर्ण

अटल काष्ठा drm_framebuffer *
zynqmp_dpsub_fb_create(काष्ठा drm_device *drm, काष्ठा drm_file *file_priv,
		       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा zynqmp_dpsub *dpsub = to_zynqmp_dpsub(drm);
	काष्ठा drm_mode_fb_cmd2 cmd = *mode_cmd;
	अचिन्हित पूर्णांक i;

	/* Enक्रमce the alignment स्थिरraपूर्णांकs of the DMA engine. */
	क्रम (i = 0; i < ARRAY_SIZE(cmd.pitches); ++i)
		cmd.pitches[i] = ALIGN(cmd.pitches[i], dpsub->dma_align);

	वापस drm_gem_fb_create(drm, file_priv, &cmd);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs zynqmp_dpsub_mode_config_funcs = अणु
	.fb_create		= zynqmp_dpsub_fb_create,
	.atomic_check		= drm_atomic_helper_check,
	.atomic_commit		= drm_atomic_helper_commit,
पूर्ण;

/* -----------------------------------------------------------------------------
 * DRM/KMS Driver
 */

DEFINE_DRM_GEM_CMA_FOPS(zynqmp_dpsub_drm_fops);

अटल स्थिर काष्ठा drm_driver zynqmp_dpsub_drm_driver = अणु
	.driver_features		= DRIVER_MODESET | DRIVER_GEM |
					  DRIVER_ATOMIC,

	DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(zynqmp_dpsub_dumb_create),

	.fops				= &zynqmp_dpsub_drm_fops,

	.name				= "zynqmp-dpsub",
	.desc				= "Xilinx DisplayPort Subsystem Driver",
	.date				= "20130509",
	.major				= 1,
	.minor				= 0,
पूर्ण;

अटल पूर्णांक zynqmp_dpsub_drm_init(काष्ठा zynqmp_dpsub *dpsub)
अणु
	काष्ठा drm_device *drm = &dpsub->drm;
	पूर्णांक ret;

	/* Initialize mode config, vblank and the KMS poll helper. */
	ret = drmm_mode_config_init(drm);
	अगर (ret < 0)
		वापस ret;

	drm->mode_config.funcs = &zynqmp_dpsub_mode_config_funcs;
	drm->mode_config.min_width = 0;
	drm->mode_config.min_height = 0;
	drm->mode_config.max_width = ZYNQMP_DISP_MAX_WIDTH;
	drm->mode_config.max_height = ZYNQMP_DISP_MAX_HEIGHT;

	ret = drm_vblank_init(drm, 1);
	अगर (ret)
		वापस ret;

	drm->irq_enabled = 1;

	drm_kms_helper_poll_init(drm);

	/*
	 * Initialize the DISP and DP components. This will creates planes,
	 * CRTC, encoder and connector. The DISP should be initialized first as
	 * the DP encoder needs the CRTC.
	 */
	ret = zynqmp_disp_drm_init(dpsub);
	अगर (ret)
		जाओ err_poll_fini;

	ret = zynqmp_dp_drm_init(dpsub);
	अगर (ret)
		जाओ err_poll_fini;

	/* Reset all components and रेजिस्टर the DRM device. */
	drm_mode_config_reset(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret < 0)
		जाओ err_poll_fini;

	/* Initialize fbdev generic emulation. */
	drm_fbdev_generic_setup(drm, 24);

	वापस 0;

err_poll_fini:
	drm_kms_helper_poll_fini(drm);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Power Management
 */

अटल पूर्णांक __maybe_unused zynqmp_dpsub_suspend(काष्ठा device *dev)
अणु
	काष्ठा zynqmp_dpsub *dpsub = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_suspend(&dpsub->drm);
पूर्ण

अटल पूर्णांक __maybe_unused zynqmp_dpsub_resume(काष्ठा device *dev)
अणु
	काष्ठा zynqmp_dpsub *dpsub = dev_get_drvdata(dev);

	वापस drm_mode_config_helper_resume(&dpsub->drm);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops zynqmp_dpsub_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(zynqmp_dpsub_suspend, zynqmp_dpsub_resume)
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe & Remove
 */

अटल पूर्णांक zynqmp_dpsub_init_घड़ीs(काष्ठा zynqmp_dpsub *dpsub)
अणु
	पूर्णांक ret;

	dpsub->apb_clk = devm_clk_get(dpsub->dev, "dp_apb_clk");
	अगर (IS_ERR(dpsub->apb_clk))
		वापस PTR_ERR(dpsub->apb_clk);

	ret = clk_prepare_enable(dpsub->apb_clk);
	अगर (ret) अणु
		dev_err(dpsub->dev, "failed to enable the APB clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_dpsub_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_dpsub *dpsub;
	पूर्णांक ret;

	/* Allocate निजी data. */
	dpsub = devm_drm_dev_alloc(&pdev->dev, &zynqmp_dpsub_drm_driver,
				   काष्ठा zynqmp_dpsub, drm);
	अगर (IS_ERR(dpsub))
		वापस PTR_ERR(dpsub);

	dpsub->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dpsub);

	dma_set_mask(dpsub->dev, DMA_BIT_MASK(ZYNQMP_DISP_MAX_DMA_BIT));

	/* Try the reserved memory. Proceed अगर there's none. */
	of_reserved_mem_device_init(&pdev->dev);

	ret = zynqmp_dpsub_init_घड़ीs(dpsub);
	अगर (ret < 0)
		जाओ err_mem;

	pm_runसमय_enable(&pdev->dev);

	/*
	 * DP should be probed first so that the zynqmp_disp can set the output
	 * क्रमmat accordingly.
	 */
	ret = zynqmp_dp_probe(dpsub, &dpsub->drm);
	अगर (ret)
		जाओ err_pm;

	ret = zynqmp_disp_probe(dpsub, &dpsub->drm);
	अगर (ret)
		जाओ err_dp;

	ret = zynqmp_dpsub_drm_init(dpsub);
	अगर (ret)
		जाओ err_disp;

	dev_info(&pdev->dev, "ZynqMP DisplayPort Subsystem driver probed");

	वापस 0;

err_disp:
	zynqmp_disp_हटाओ(dpsub);
err_dp:
	zynqmp_dp_हटाओ(dpsub);
err_pm:
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(dpsub->apb_clk);
err_mem:
	of_reserved_mem_device_release(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक zynqmp_dpsub_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_dpsub *dpsub = platक्रमm_get_drvdata(pdev);
	काष्ठा drm_device *drm = &dpsub->drm;

	drm_dev_unरेजिस्टर(drm);
	drm_atomic_helper_shutकरोwn(drm);
	drm_kms_helper_poll_fini(drm);

	zynqmp_disp_हटाओ(dpsub);
	zynqmp_dp_हटाओ(dpsub);

	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(dpsub->apb_clk);
	of_reserved_mem_device_release(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम zynqmp_dpsub_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_dpsub *dpsub = platक्रमm_get_drvdata(pdev);

	drm_atomic_helper_shutकरोwn(&dpsub->drm);
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_dpsub_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-dpsub-1.7", पूर्ण,
	अणु /* end of table */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zynqmp_dpsub_of_match);

अटल काष्ठा platक्रमm_driver zynqmp_dpsub_driver = अणु
	.probe			= zynqmp_dpsub_probe,
	.हटाओ			= zynqmp_dpsub_हटाओ,
	.shutकरोwn		= zynqmp_dpsub_shutकरोwn,
	.driver			= अणु
		.name		= "zynqmp-dpsub",
		.pm		= &zynqmp_dpsub_pm_ops,
		.of_match_table	= zynqmp_dpsub_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(zynqmp_dpsub_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("ZynqMP DP Subsystem Driver");
MODULE_LICENSE("GPL v2");
