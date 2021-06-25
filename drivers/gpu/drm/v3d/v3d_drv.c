<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2014-2018 Broadcom */

/**
 * DOC: Broadcom V3D Graphics Driver
 *
 * This driver supports the Broadcom V3D 3.3 and 4.1 OpenGL ES GPUs.
 * For V3D 2.x support, see the VC4 driver.
 *
 * The V3D GPU includes a tiled render (composed of a bin and render
 * pipelines), the TFU (texture क्रमmatting unit), and the CSD (compute
 * shader dispatch).
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <uapi/drm/v3d_drm.h>

#समावेश "v3d_drv.h"
#समावेश "v3d_regs.h"

#घोषणा DRIVER_NAME "v3d"
#घोषणा DRIVER_DESC "Broadcom V3D graphics"
#घोषणा DRIVER_DATE "20180419"
#घोषणा DRIVER_MAJOR 1
#घोषणा DRIVER_MINOR 0
#घोषणा DRIVER_PATCHLEVEL 0

अटल पूर्णांक v3d_get_param_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file_priv)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	काष्ठा drm_v3d_get_param *args = data;
	पूर्णांक ret;
	अटल स्थिर u32 reg_map[] = अणु
		[DRM_V3D_PARAM_V3D_UIFCFG] = V3D_HUB_UIFCFG,
		[DRM_V3D_PARAM_V3D_HUB_IDENT1] = V3D_HUB_IDENT1,
		[DRM_V3D_PARAM_V3D_HUB_IDENT2] = V3D_HUB_IDENT2,
		[DRM_V3D_PARAM_V3D_HUB_IDENT3] = V3D_HUB_IDENT3,
		[DRM_V3D_PARAM_V3D_CORE0_IDENT0] = V3D_CTL_IDENT0,
		[DRM_V3D_PARAM_V3D_CORE0_IDENT1] = V3D_CTL_IDENT1,
		[DRM_V3D_PARAM_V3D_CORE0_IDENT2] = V3D_CTL_IDENT2,
	पूर्ण;

	अगर (args->pad != 0)
		वापस -EINVAL;

	/* Note that DRM_V3D_PARAM_V3D_CORE0_IDENT0 is 0, so we need
	 * to explicitly allow it in the "the रेजिस्टर in our
	 * parameter map" check.
	 */
	अगर (args->param < ARRAY_SIZE(reg_map) &&
	    (reg_map[args->param] ||
	     args->param == DRM_V3D_PARAM_V3D_CORE0_IDENT0)) अणु
		u32 offset = reg_map[args->param];

		अगर (args->value != 0)
			वापस -EINVAL;

		ret = pm_runसमय_get_sync(v3d->drm.dev);
		अगर (ret < 0)
			वापस ret;
		अगर (args->param >= DRM_V3D_PARAM_V3D_CORE0_IDENT0 &&
		    args->param <= DRM_V3D_PARAM_V3D_CORE0_IDENT2) अणु
			args->value = V3D_CORE_READ(0, offset);
		पूर्ण अन्यथा अणु
			args->value = V3D_READ(offset);
		पूर्ण
		pm_runसमय_mark_last_busy(v3d->drm.dev);
		pm_runसमय_put_स्वतःsuspend(v3d->drm.dev);
		वापस 0;
	पूर्ण


	चयन (args->param) अणु
	हाल DRM_V3D_PARAM_SUPPORTS_TFU:
		args->value = 1;
		वापस 0;
	हाल DRM_V3D_PARAM_SUPPORTS_CSD:
		args->value = v3d_has_csd(v3d);
		वापस 0;
	हाल DRM_V3D_PARAM_SUPPORTS_CACHE_FLUSH:
		args->value = 1;
		वापस 0;
	शेष:
		DRM_DEBUG("Unknown parameter %d\n", args->param);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
v3d_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	काष्ठा v3d_file_priv *v3d_priv;
	काष्ठा drm_gpu_scheduler *sched;
	पूर्णांक i;

	v3d_priv = kzalloc(माप(*v3d_priv), GFP_KERNEL);
	अगर (!v3d_priv)
		वापस -ENOMEM;

	v3d_priv->v3d = v3d;

	क्रम (i = 0; i < V3D_MAX_QUEUES; i++) अणु
		sched = &v3d->queue[i].sched;
		drm_sched_entity_init(&v3d_priv->sched_entity[i],
				      DRM_SCHED_PRIORITY_NORMAL, &sched,
				      1, शून्य);
	पूर्ण

	file->driver_priv = v3d_priv;

	वापस 0;
पूर्ण

अटल व्योम
v3d_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा v3d_file_priv *v3d_priv = file->driver_priv;
	क्रमागत v3d_queue q;

	क्रम (q = 0; q < V3D_MAX_QUEUES; q++) अणु
		drm_sched_entity_destroy(&v3d_priv->sched_entity[q]);
	पूर्ण

	kमुक्त(v3d_priv);
पूर्ण

DEFINE_DRM_GEM_FOPS(v3d_drm_fops);

/* DRM_AUTH is required on SUBMIT_CL क्रम now, जबतक we करोn't have GMP
 * protection between clients.  Note that render nodes would be be
 * able to submit CLs that could access BOs from clients authenticated
 * with the master node.  The TFU करोesn't use the GMP, so it would
 * need to stay DRM_AUTH until we करो buffer size/offset validation.
 */
अटल स्थिर काष्ठा drm_ioctl_desc v3d_drm_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(V3D_SUBMIT_CL, v3d_submit_cl_ioctl, DRM_RENDER_ALLOW | DRM_AUTH),
	DRM_IOCTL_DEF_DRV(V3D_WAIT_BO, v3d_रुको_bo_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(V3D_CREATE_BO, v3d_create_bo_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(V3D_MMAP_BO, v3d_mmap_bo_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(V3D_GET_PARAM, v3d_get_param_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(V3D_GET_BO_OFFSET, v3d_get_bo_offset_ioctl, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(V3D_SUBMIT_TFU, v3d_submit_tfu_ioctl, DRM_RENDER_ALLOW | DRM_AUTH),
	DRM_IOCTL_DEF_DRV(V3D_SUBMIT_CSD, v3d_submit_csd_ioctl, DRM_RENDER_ALLOW | DRM_AUTH),
पूर्ण;

अटल स्थिर काष्ठा drm_driver v3d_drm_driver = अणु
	.driver_features = (DRIVER_GEM |
			    DRIVER_RENDER |
			    DRIVER_SYNCOBJ),

	.खोलो = v3d_खोलो,
	.postबंद = v3d_postबंद,

#अगर defined(CONFIG_DEBUG_FS)
	.debugfs_init = v3d_debugfs_init,
#पूर्ण_अगर

	.gem_create_object = v3d_create_object,
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = v3d_prime_import_sg_table,
	.gem_prime_mmap = drm_gem_prime_mmap,

	.ioctls = v3d_drm_ioctls,
	.num_ioctls = ARRAY_SIZE(v3d_drm_ioctls),
	.fops = &v3d_drm_fops,

	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल स्थिर काष्ठा of_device_id v3d_of_match[] = अणु
	अणु .compatible = "brcm,7268-v3d" पूर्ण,
	अणु .compatible = "brcm,7278-v3d" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, v3d_of_match);

अटल पूर्णांक
map_regs(काष्ठा v3d_dev *v3d, व्योम __iomem **regs, स्थिर अक्षर *name)
अणु
	काष्ठा resource *res =
		platक्रमm_get_resource_byname(v3d_to_pdev(v3d), IORESOURCE_MEM, name);

	*regs = devm_ioremap_resource(v3d->drm.dev, res);
	वापस PTR_ERR_OR_ZERO(*regs);
पूर्ण

अटल पूर्णांक v3d_platक्रमm_drm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा drm_device *drm;
	काष्ठा v3d_dev *v3d;
	पूर्णांक ret;
	u32 mmu_debug;
	u32 ident1;


	v3d = devm_drm_dev_alloc(dev, &v3d_drm_driver, काष्ठा v3d_dev, drm);
	अगर (IS_ERR(v3d))
		वापस PTR_ERR(v3d);

	drm = &v3d->drm;

	platक्रमm_set_drvdata(pdev, drm);

	ret = map_regs(v3d, &v3d->hub_regs, "hub");
	अगर (ret)
		वापस ret;

	ret = map_regs(v3d, &v3d->core_regs[0], "core0");
	अगर (ret)
		वापस ret;

	mmu_debug = V3D_READ(V3D_MMU_DEBUG_INFO);
	dma_set_mask_and_coherent(dev,
		DMA_BIT_MASK(30 + V3D_GET_FIELD(mmu_debug, V3D_MMU_PA_WIDTH)));
	v3d->va_width = 30 + V3D_GET_FIELD(mmu_debug, V3D_MMU_VA_WIDTH);

	ident1 = V3D_READ(V3D_HUB_IDENT1);
	v3d->ver = (V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_TVER) * 10 +
		    V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_REV));
	v3d->cores = V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_NCORES);
	WARN_ON(v3d->cores > 1); /* multicore not yet implemented */

	v3d->reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(v3d->reset)) अणु
		ret = PTR_ERR(v3d->reset);

		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		v3d->reset = शून्य;
		ret = map_regs(v3d, &v3d->bridge_regs, "bridge");
		अगर (ret) अणु
			dev_err(dev,
				"Failed to get reset control or bridge regs\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (v3d->ver < 41) अणु
		ret = map_regs(v3d, &v3d->gca_regs, "gca");
		अगर (ret)
			वापस ret;
	पूर्ण

	v3d->mmu_scratch = dma_alloc_wc(dev, 4096, &v3d->mmu_scratch_paddr,
					GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO);
	अगर (!v3d->mmu_scratch) अणु
		dev_err(dev, "Failed to allocate MMU scratch page\n");
		वापस -ENOMEM;
	पूर्ण

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 50);
	pm_runसमय_enable(dev);

	ret = v3d_gem_init(drm);
	अगर (ret)
		जाओ dma_मुक्त;

	ret = v3d_irq_init(v3d);
	अगर (ret)
		जाओ gem_destroy;

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ irq_disable;

	वापस 0;

irq_disable:
	v3d_irq_disable(v3d);
gem_destroy:
	v3d_gem_destroy(drm);
dma_मुक्त:
	dma_मुक्त_wc(dev, 4096, v3d->mmu_scratch, v3d->mmu_scratch_paddr);
	वापस ret;
पूर्ण

अटल पूर्णांक v3d_platक्रमm_drm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);
	काष्ठा v3d_dev *v3d = to_v3d_dev(drm);

	drm_dev_unरेजिस्टर(drm);

	v3d_gem_destroy(drm);

	dma_मुक्त_wc(v3d->drm.dev, 4096, v3d->mmu_scratch,
		    v3d->mmu_scratch_paddr);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver v3d_platक्रमm_driver = अणु
	.probe		= v3d_platक्रमm_drm_probe,
	.हटाओ		= v3d_platक्रमm_drm_हटाओ,
	.driver		= अणु
		.name	= "v3d",
		.of_match_table = v3d_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(v3d_platक्रमm_driver);

MODULE_ALIAS("platform:v3d-drm");
MODULE_DESCRIPTION("Broadcom V3D DRM Driver");
MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_LICENSE("GPL v2");
