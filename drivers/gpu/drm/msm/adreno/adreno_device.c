<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2014 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 *
 * Copyright (c) 2014,2017 The Linux Foundation. All rights reserved.
 */

#समावेश "adreno_gpu.h"

#घोषणा ANY_ID 0xff

bool hang_debug = false;
MODULE_PARM_DESC(hang_debug, "Dump registers when hang is detected (can be slow!)");
module_param_named(hang_debug, hang_debug, bool, 0600);

bool snapshot_debugbus = false;
MODULE_PARM_DESC(snapshot_debugbus, "Include debugbus sections in GPU devcoredump (if not fused off)");
module_param_named(snapshot_debugbus, snapshot_debugbus, bool, 0600);

bool allow_vram_carveout = false;
MODULE_PARM_DESC(allow_vram_carveout, "Allow using VRAM Carveout, in place of IOMMU");
module_param_named(allow_vram_carveout, allow_vram_carveout, bool, 0600);

अटल स्थिर काष्ठा adreno_info gpulist[] = अणु
	अणु
		.rev   = ADRENO_REV(2, 0, 0, 0),
		.revn  = 200,
		.name  = "A200",
		.fw = अणु
			[ADRENO_FW_PM4] = "yamato_pm4.fw",
			[ADRENO_FW_PFP] = "yamato_pfp.fw",
		पूर्ण,
		.gmem  = SZ_256K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a2xx_gpu_init,
	पूर्ण, अणु /* a200 on i.mx51 has only 128kib gmem */
		.rev   = ADRENO_REV(2, 0, 0, 1),
		.revn  = 201,
		.name  = "A200",
		.fw = अणु
			[ADRENO_FW_PM4] = "yamato_pm4.fw",
			[ADRENO_FW_PFP] = "yamato_pfp.fw",
		पूर्ण,
		.gmem  = SZ_128K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a2xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(2, 2, 0, ANY_ID),
		.revn  = 220,
		.name  = "A220",
		.fw = अणु
			[ADRENO_FW_PM4] = "leia_pm4_470.fw",
			[ADRENO_FW_PFP] = "leia_pfp_470.fw",
		पूर्ण,
		.gmem  = SZ_512K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a2xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(3, 0, 5, ANY_ID),
		.revn  = 305,
		.name  = "A305",
		.fw = अणु
			[ADRENO_FW_PM4] = "a300_pm4.fw",
			[ADRENO_FW_PFP] = "a300_pfp.fw",
		पूर्ण,
		.gmem  = SZ_256K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a3xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(3, 0, 6, 0),
		.revn  = 307,        /* because a305c is revn==306 */
		.name  = "A306",
		.fw = अणु
			[ADRENO_FW_PM4] = "a300_pm4.fw",
			[ADRENO_FW_PFP] = "a300_pfp.fw",
		पूर्ण,
		.gmem  = SZ_128K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a3xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(3, 2, ANY_ID, ANY_ID),
		.revn  = 320,
		.name  = "A320",
		.fw = अणु
			[ADRENO_FW_PM4] = "a300_pm4.fw",
			[ADRENO_FW_PFP] = "a300_pfp.fw",
		पूर्ण,
		.gmem  = SZ_512K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a3xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(3, 3, 0, ANY_ID),
		.revn  = 330,
		.name  = "A330",
		.fw = अणु
			[ADRENO_FW_PM4] = "a330_pm4.fw",
			[ADRENO_FW_PFP] = "a330_pfp.fw",
		पूर्ण,
		.gmem  = SZ_1M,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a3xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(4, 0, 5, ANY_ID),
		.revn  = 405,
		.name  = "A405",
		.fw = अणु
			[ADRENO_FW_PM4] = "a420_pm4.fw",
			[ADRENO_FW_PFP] = "a420_pfp.fw",
		पूर्ण,
		.gmem  = SZ_256K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a4xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(4, 2, 0, ANY_ID),
		.revn  = 420,
		.name  = "A420",
		.fw = अणु
			[ADRENO_FW_PM4] = "a420_pm4.fw",
			[ADRENO_FW_PFP] = "a420_pfp.fw",
		पूर्ण,
		.gmem  = (SZ_1M + SZ_512K),
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a4xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(4, 3, 0, ANY_ID),
		.revn  = 430,
		.name  = "A430",
		.fw = अणु
			[ADRENO_FW_PM4] = "a420_pm4.fw",
			[ADRENO_FW_PFP] = "a420_pfp.fw",
		पूर्ण,
		.gmem  = (SZ_1M + SZ_512K),
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init  = a4xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(5, 0, 8, ANY_ID),
		.revn = 508,
		.name = "A508",
		.fw = अणु
			[ADRENO_FW_PM4] = "a530_pm4.fw",
			[ADRENO_FW_PFP] = "a530_pfp.fw",
		पूर्ण,
		.gmem = (SZ_128K + SZ_8K),
		/*
		 * Increase inactive period to 250 to aव्योम bouncing
		 * the GDSC which appears to make it grumpy
		 */
		.inactive_period = 250,
		.quirks = ADRENO_QUIRK_LMLOADKILL_DISABLE,
		.init = a5xx_gpu_init,
		.zapfw = "a508_zap.mdt",
	पूर्ण, अणु
		.rev   = ADRENO_REV(5, 0, 9, ANY_ID),
		.revn = 509,
		.name = "A509",
		.fw = अणु
			[ADRENO_FW_PM4] = "a530_pm4.fw",
			[ADRENO_FW_PFP] = "a530_pfp.fw",
		पूर्ण,
		.gmem = (SZ_256K + SZ_16K),
		/*
		 * Increase inactive period to 250 to aव्योम bouncing
		 * the GDSC which appears to make it grumpy
		 */
		.inactive_period = 250,
		.quirks = ADRENO_QUIRK_LMLOADKILL_DISABLE,
		.init = a5xx_gpu_init,
		/* Adreno 509 uses the same ZAP as 512 */
		.zapfw = "a512_zap.mdt",
	पूर्ण, अणु
		.rev   = ADRENO_REV(5, 1, 0, ANY_ID),
		.revn = 510,
		.name = "A510",
		.fw = अणु
			[ADRENO_FW_PM4] = "a530_pm4.fw",
			[ADRENO_FW_PFP] = "a530_pfp.fw",
		पूर्ण,
		.gmem = SZ_256K,
		/*
		 * Increase inactive period to 250 to aव्योम bouncing
		 * the GDSC which appears to make it grumpy
		 */
		.inactive_period = 250,
		.init = a5xx_gpu_init,
	पूर्ण, अणु
		.rev   = ADRENO_REV(5, 1, 2, ANY_ID),
		.revn = 512,
		.name = "A512",
		.fw = अणु
			[ADRENO_FW_PM4] = "a530_pm4.fw",
			[ADRENO_FW_PFP] = "a530_pfp.fw",
		पूर्ण,
		.gmem = (SZ_256K + SZ_16K),
		/*
		 * Increase inactive period to 250 to aव्योम bouncing
		 * the GDSC which appears to make it grumpy
		 */
		.inactive_period = 250,
		.quirks = ADRENO_QUIRK_LMLOADKILL_DISABLE,
		.init = a5xx_gpu_init,
		.zapfw = "a512_zap.mdt",
	पूर्ण, अणु
		.rev = ADRENO_REV(5, 3, 0, 2),
		.revn = 530,
		.name = "A530",
		.fw = अणु
			[ADRENO_FW_PM4] = "a530_pm4.fw",
			[ADRENO_FW_PFP] = "a530_pfp.fw",
			[ADRENO_FW_GPMU] = "a530v3_gpmu.fw2",
		पूर्ण,
		.gmem = SZ_1M,
		/*
		 * Increase inactive period to 250 to aव्योम bouncing
		 * the GDSC which appears to make it grumpy
		 */
		.inactive_period = 250,
		.quirks = ADRENO_QUIRK_TWO_PASS_USE_WFI |
			ADRENO_QUIRK_FAULT_DETECT_MASK,
		.init = a5xx_gpu_init,
		.zapfw = "a530_zap.mdt",
	पूर्ण, अणु
		.rev = ADRENO_REV(5, 4, 0, ANY_ID),
		.revn = 540,
		.name = "A540",
		.fw = अणु
			[ADRENO_FW_PM4] = "a530_pm4.fw",
			[ADRENO_FW_PFP] = "a530_pfp.fw",
			[ADRENO_FW_GPMU] = "a540_gpmu.fw2",
		पूर्ण,
		.gmem = SZ_1M,
		/*
		 * Increase inactive period to 250 to aव्योम bouncing
		 * the GDSC which appears to make it grumpy
		 */
		.inactive_period = 250,
		.quirks = ADRENO_QUIRK_LMLOADKILL_DISABLE,
		.init = a5xx_gpu_init,
		.zapfw = "a540_zap.mdt",
	पूर्ण, अणु
		.rev = ADRENO_REV(6, 1, 8, ANY_ID),
		.revn = 618,
		.name = "A618",
		.fw = अणु
			[ADRENO_FW_SQE] = "a630_sqe.fw",
			[ADRENO_FW_GMU] = "a630_gmu.bin",
		पूर्ण,
		.gmem = SZ_512K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init = a6xx_gpu_init,
	पूर्ण, अणु
		.rev = ADRENO_REV(6, 3, 0, ANY_ID),
		.revn = 630,
		.name = "A630",
		.fw = अणु
			[ADRENO_FW_SQE] = "a630_sqe.fw",
			[ADRENO_FW_GMU] = "a630_gmu.bin",
		पूर्ण,
		.gmem = SZ_1M,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init = a6xx_gpu_init,
		.zapfw = "a630_zap.mdt",
		.hwcg = a630_hwcg,
	पूर्ण, अणु
		.rev = ADRENO_REV(6, 4, 0, ANY_ID),
		.revn = 640,
		.name = "A640",
		.fw = अणु
			[ADRENO_FW_SQE] = "a630_sqe.fw",
			[ADRENO_FW_GMU] = "a640_gmu.bin",
		पूर्ण,
		.gmem = SZ_1M,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init = a6xx_gpu_init,
		.zapfw = "a640_zap.mdt",
		.hwcg = a640_hwcg,
	पूर्ण, अणु
		.rev = ADRENO_REV(6, 5, 0, ANY_ID),
		.revn = 650,
		.name = "A650",
		.fw = अणु
			[ADRENO_FW_SQE] = "a650_sqe.fw",
			[ADRENO_FW_GMU] = "a650_gmu.bin",
		पूर्ण,
		.gmem = SZ_1M + SZ_128K,
		.inactive_period = DRM_MSM_INACTIVE_PERIOD,
		.init = a6xx_gpu_init,
		.zapfw = "a650_zap.mdt",
		.hwcg = a650_hwcg,
	पूर्ण,
पूर्ण;

MODULE_FIRMWARE("qcom/a300_pm4.fw");
MODULE_FIRMWARE("qcom/a300_pfp.fw");
MODULE_FIRMWARE("qcom/a330_pm4.fw");
MODULE_FIRMWARE("qcom/a330_pfp.fw");
MODULE_FIRMWARE("qcom/a420_pm4.fw");
MODULE_FIRMWARE("qcom/a420_pfp.fw");
MODULE_FIRMWARE("qcom/a530_pm4.fw");
MODULE_FIRMWARE("qcom/a530_pfp.fw");
MODULE_FIRMWARE("qcom/a530v3_gpmu.fw2");
MODULE_FIRMWARE("qcom/a530_zap.mdt");
MODULE_FIRMWARE("qcom/a530_zap.b00");
MODULE_FIRMWARE("qcom/a530_zap.b01");
MODULE_FIRMWARE("qcom/a530_zap.b02");
MODULE_FIRMWARE("qcom/a630_sqe.fw");
MODULE_FIRMWARE("qcom/a630_gmu.bin");
MODULE_FIRMWARE("qcom/a630_zap.mbn");

अटल अंतरभूत bool _rev_match(uपूर्णांक8_t entry, uपूर्णांक8_t id)
अणु
	वापस (entry == ANY_ID) || (entry == id);
पूर्ण

स्थिर काष्ठा adreno_info *adreno_info(काष्ठा adreno_rev rev)
अणु
	पूर्णांक i;

	/* identअगरy gpu: */
	क्रम (i = 0; i < ARRAY_SIZE(gpulist); i++) अणु
		स्थिर काष्ठा adreno_info *info = &gpulist[i];
		अगर (_rev_match(info->rev.core, rev.core) &&
				_rev_match(info->rev.major, rev.major) &&
				_rev_match(info->rev.minor, rev.minor) &&
				_rev_match(info->rev.patchid, rev.patchid))
			वापस info;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा msm_gpu *adreno_load_gpu(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा platक्रमm_device *pdev = priv->gpu_pdev;
	काष्ठा msm_gpu *gpu = शून्य;
	काष्ठा adreno_gpu *adreno_gpu;
	पूर्णांक ret;

	अगर (pdev)
		gpu = dev_to_gpu(&pdev->dev);

	अगर (!gpu) अणु
		dev_err_once(dev->dev, "no GPU device was found\n");
		वापस शून्य;
	पूर्ण

	adreno_gpu = to_adreno_gpu(gpu);

	/*
	 * The number one reason क्रम HW init to fail is अगर the firmware isn't
	 * loaded yet. Try that first and करोn't bother continuing on
	 * otherwise
	 */

	ret = adreno_load_fw(adreno_gpu);
	अगर (ret)
		वापस शून्य;

	/* Make sure pm runसमय is active and reset any previous errors */
	pm_runसमय_set_active(&pdev->dev);

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_sync(&pdev->dev);
		DRM_DEV_ERROR(dev->dev, "Couldn't power up the GPU: %d\n", ret);
		वापस शून्य;
	पूर्ण

	mutex_lock(&dev->काष्ठा_mutex);
	ret = msm_gpu_hw_init(gpu);
	mutex_unlock(&dev->काष्ठा_mutex);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "gpu hw init failed: %d\n", ret);
		वापस शून्य;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	अगर (gpu->funcs->debugfs_init) अणु
		gpu->funcs->debugfs_init(gpu, dev->primary);
		gpu->funcs->debugfs_init(gpu, dev->render);
	पूर्ण
#पूर्ण_अगर

	वापस gpu;
पूर्ण

अटल व्योम set_gpu_pdev(काष्ठा drm_device *dev,
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	priv->gpu_pdev = pdev;
पूर्ण

अटल पूर्णांक find_chipid(काष्ठा device *dev, काष्ठा adreno_rev *rev)
अणु
	काष्ठा device_node *node = dev->of_node;
	स्थिर अक्षर *compat;
	पूर्णांक ret;
	u32 chipid;

	/* first search the compat strings क्रम qcom,adreno-XYZ.W: */
	ret = of_property_पढ़ो_string_index(node, "compatible", 0, &compat);
	अगर (ret == 0) अणु
		अचिन्हित पूर्णांक r, patch;

		अगर (माला_पूछो(compat, "qcom,adreno-%u.%u", &r, &patch) == 2 ||
		    माला_पूछो(compat, "amd,imageon-%u.%u", &r, &patch) == 2) अणु
			rev->core = r / 100;
			r %= 100;
			rev->major = r / 10;
			r %= 10;
			rev->minor = r;
			rev->patchid = patch;

			वापस 0;
		पूर्ण
	पूर्ण

	/* and अगर that fails, fall back to legacy "qcom,chipid" property: */
	ret = of_property_पढ़ो_u32(node, "qcom,chipid", &chipid);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "could not parse qcom,chipid: %d\n", ret);
		वापस ret;
	पूर्ण

	rev->core = (chipid >> 24) & 0xff;
	rev->major = (chipid >> 16) & 0xff;
	rev->minor = (chipid >> 8) & 0xff;
	rev->patchid = (chipid & 0xff);

	dev_warn(dev, "Using legacy qcom,chipid binding!\n");
	dev_warn(dev, "Use compatible qcom,adreno-%u%u%u.%u instead.\n",
		rev->core, rev->major, rev->minor, rev->patchid);

	वापस 0;
पूर्ण

अटल पूर्णांक adreno_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	अटल काष्ठा adreno_platक्रमm_config config = अणुपूर्ण;
	स्थिर काष्ठा adreno_info *info;
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;
	काष्ठा msm_gpu *gpu;
	पूर्णांक ret;

	ret = find_chipid(dev, &config.rev);
	अगर (ret)
		वापस ret;

	dev->platक्रमm_data = &config;
	set_gpu_pdev(drm, to_platक्रमm_device(dev));

	info = adreno_info(config.rev);

	अगर (!info) अणु
		dev_warn(drm->dev, "Unknown GPU revision: %u.%u.%u.%u\n",
			config.rev.core, config.rev.major,
			config.rev.minor, config.rev.patchid);
		वापस -ENXIO;
	पूर्ण

	DBG("Found GPU: %u.%u.%u.%u", config.rev.core, config.rev.major,
		config.rev.minor, config.rev.patchid);

	priv->is_a2xx = config.rev.core == 2;

	gpu = info->init(drm);
	अगर (IS_ERR(gpu)) अणु
		dev_warn(drm->dev, "failed to load adreno gpu\n");
		वापस PTR_ERR(gpu);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adreno_unbind(काष्ठा device *dev, काष्ठा device *master,
		व्योम *data)
अणु
	काष्ठा msm_gpu *gpu = dev_to_gpu(dev);

	pm_runसमय_क्रमce_suspend(dev);
	gpu->funcs->destroy(gpu);

	set_gpu_pdev(dev_get_drvdata(master), शून्य);
पूर्ण

अटल स्थिर काष्ठा component_ops a3xx_ops = अणु
		.bind   = adreno_bind,
		.unbind = adreno_unbind,
पूर्ण;

अटल व्योम adreno_device_रेजिस्टर_headless(व्योम)
अणु
	/* on imx5, we करोn't have a top-level mdp/dpu node
	 * this creates a dummy node क्रम the driver क्रम that हाल
	 */
	काष्ठा platक्रमm_device_info dummy_info = अणु
		.parent = शून्य,
		.name = "msm",
		.id = -1,
		.res = शून्य,
		.num_res = 0,
		.data = शून्य,
		.size_data = 0,
		.dma_mask = ~0,
	पूर्ण;
	platक्रमm_device_रेजिस्टर_full(&dummy_info);
पूर्ण

अटल पूर्णांक adreno_probe(काष्ठा platक्रमm_device *pdev)
अणु

	पूर्णांक ret;

	ret = component_add(&pdev->dev, &a3xx_ops);
	अगर (ret)
		वापस ret;

	अगर (of_device_is_compatible(pdev->dev.of_node, "amd,imageon"))
		adreno_device_रेजिस्टर_headless();

	वापस 0;
पूर्ण

अटल पूर्णांक adreno_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &a3xx_ops);
	वापस 0;
पूर्ण

अटल व्योम adreno_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_क्रमce_suspend(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id dt_match[] = अणु
	अणु .compatible = "qcom,adreno" पूर्ण,
	अणु .compatible = "qcom,adreno-3xx" पूर्ण,
	/* क्रम compatibility with imx5 gpu: */
	अणु .compatible = "amd,imageon" पूर्ण,
	/* क्रम backwards compat w/ करोwnstream kgsl DT files: */
	अणु .compatible = "qcom,kgsl-3d0" पूर्ण,
	अणुपूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक adreno_resume(काष्ठा device *dev)
अणु
	काष्ठा msm_gpu *gpu = dev_to_gpu(dev);

	वापस gpu->funcs->pm_resume(gpu);
पूर्ण

अटल पूर्णांक adreno_suspend(काष्ठा device *dev)
अणु
	काष्ठा msm_gpu *gpu = dev_to_gpu(dev);

	वापस gpu->funcs->pm_suspend(gpu);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops adreno_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(adreno_suspend, adreno_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver adreno_driver = अणु
	.probe = adreno_probe,
	.हटाओ = adreno_हटाओ,
	.shutकरोwn = adreno_shutकरोwn,
	.driver = अणु
		.name = "adreno",
		.of_match_table = dt_match,
		.pm = &adreno_pm_ops,
	पूर्ण,
पूर्ण;

व्योम __init adreno_रेजिस्टर(व्योम)
अणु
	platक्रमm_driver_रेजिस्टर(&adreno_driver);
पूर्ण

व्योम __निकास adreno_unरेजिस्टर(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&adreno_driver);
पूर्ण
