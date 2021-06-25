<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/sched/types.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_vblank.h>

#समावेश "msm_drv.h"
#समावेश "msm_debugfs.h"
#समावेश "msm_fence.h"
#समावेश "msm_gem.h"
#समावेश "msm_gpu.h"
#समावेश "msm_kms.h"
#समावेश "adreno/adreno_gpu.h"

/*
 * MSM driver version:
 * - 1.0.0 - initial पूर्णांकerface
 * - 1.1.0 - adds madvise, and support क्रम submits with > 4 cmd buffers
 * - 1.2.0 - adds explicit fence support क्रम submit ioctl
 * - 1.3.0 - adds GMEM_BASE + NR_RINGS params, SUBMITQUEUE_NEW +
 *           SUBMITQUEUE_CLOSE ioctls, and MSM_INFO_IOVA flag क्रम
 *           MSM_GEM_INFO ioctl.
 * - 1.4.0 - softpin, MSM_RELOC_BO_DUMP, and GEM_INFO support to set/get
 *           GEM object's debug name
 * - 1.5.0 - Add SUBMITQUERY_QUERY ioctl
 * - 1.6.0 - Syncobj support
 * - 1.7.0 - Add MSM_PARAM_SUSPENDS to access suspend count
 */
#घोषणा MSM_VERSION_MAJOR	1
#घोषणा MSM_VERSION_MINOR	7
#घोषणा MSM_VERSION_PATCHLEVEL	0

अटल स्थिर काष्ठा drm_mode_config_funcs mode_config_funcs = अणु
	.fb_create = msm_framebuffer_create,
	.output_poll_changed = drm_fb_helper_output_poll_changed,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_helper_funcs mode_config_helper_funcs = अणु
	.atomic_commit_tail = msm_atomic_commit_tail,
पूर्ण;

#अगर_घोषित CONFIG_DRM_MSM_REGISTER_LOGGING
अटल bool reglog = false;
MODULE_PARM_DESC(reglog, "Enable register read/write logging");
module_param(reglog, bool, 0600);
#अन्यथा
#घोषणा reglog 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
अटल bool fbdev = true;
MODULE_PARM_DESC(fbdev, "Enable fbdev compat layer");
module_param(fbdev, bool, 0600);
#पूर्ण_अगर

अटल अक्षर *vram = "16m";
MODULE_PARM_DESC(vram, "Configure VRAM size (for devices without IOMMU/GPUMMU)");
module_param(vram, अक्षरp, 0);

bool dumpstate = false;
MODULE_PARM_DESC(dumpstate, "Dump KMS state on errors");
module_param(dumpstate, bool, 0600);

अटल bool modeset = true;
MODULE_PARM_DESC(modeset, "Use kernel modesetting [KMS] (1=on (default), 0=disable)");
module_param(modeset, bool, 0600);

/*
 * Util/helpers:
 */

काष्ठा clk *msm_clk_bulk_get_घड़ी(काष्ठा clk_bulk_data *bulk, पूर्णांक count,
		स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	अक्षर n[32];

	snम_लिखो(n, माप(n), "%s_clk", name);

	क्रम (i = 0; bulk && i < count; i++) अणु
		अगर (!म_भेद(bulk[i].id, name) || !म_भेद(bulk[i].id, n))
			वापस bulk[i].clk;
	पूर्ण


	वापस शून्य;
पूर्ण

काष्ठा clk *msm_clk_get(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name)
अणु
	काष्ठा clk *clk;
	अक्षर name2[32];

	clk = devm_clk_get(&pdev->dev, name);
	अगर (!IS_ERR(clk) || PTR_ERR(clk) == -EPROBE_DEFER)
		वापस clk;

	snम_लिखो(name2, माप(name2), "%s_clk", name);

	clk = devm_clk_get(&pdev->dev, name2);
	अगर (!IS_ERR(clk))
		dev_warn(&pdev->dev, "Using legacy clk name binding.  Use "
				"\"%s\" instead of \"%s\"\n", name, name2);

	वापस clk;
पूर्ण

अटल व्योम __iomem *_msm_ioremap(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
				  स्थिर अक्षर *dbgname, bool quiet)
अणु
	काष्ठा resource *res;
	अचिन्हित दीर्घ size;
	व्योम __iomem *ptr;

	अगर (name)
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, name);
	अन्यथा
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	अगर (!res) अणु
		अगर (!quiet)
			DRM_DEV_ERROR(&pdev->dev, "failed to get memory resource: %s\n", name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	size = resource_size(res);

	ptr = devm_ioremap(&pdev->dev, res->start, size);
	अगर (!ptr) अणु
		अगर (!quiet)
			DRM_DEV_ERROR(&pdev->dev, "failed to ioremap: %s\n", name);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (reglog)
		prपूर्णांकk(KERN_DEBUG "IO:region %s %p %08lx\n", dbgname, ptr, size);

	वापस ptr;
पूर्ण

व्योम __iomem *msm_ioremap(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
			  स्थिर अक्षर *dbgname)
अणु
	वापस _msm_ioremap(pdev, name, dbgname, false);
पूर्ण

व्योम __iomem *msm_ioremap_quiet(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
				स्थिर अक्षर *dbgname)
अणु
	वापस _msm_ioremap(pdev, name, dbgname, true);
पूर्ण

व्योम msm_ग_लिखोl(u32 data, व्योम __iomem *addr)
अणु
	अगर (reglog)
		prपूर्णांकk(KERN_DEBUG "IO:W %p %08x\n", addr, data);
	ग_लिखोl(data, addr);
पूर्ण

u32 msm_पढ़ोl(स्थिर व्योम __iomem *addr)
अणु
	u32 val = पढ़ोl(addr);
	अगर (reglog)
		pr_err("IO:R %p %08x\n", addr, val);
	वापस val;
पूर्ण

व्योम msm_rmw(व्योम __iomem *addr, u32 mask, u32 or)
अणु
	u32 val = msm_पढ़ोl(addr);

	val &= ~mask;
	msm_ग_लिखोl(val | or, addr);
पूर्ण

काष्ठा msm_vblank_work अणु
	काष्ठा work_काष्ठा work;
	पूर्णांक crtc_id;
	bool enable;
	काष्ठा msm_drm_निजी *priv;
पूर्ण;

अटल व्योम vblank_ctrl_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा msm_vblank_work *vbl_work = container_of(work,
						काष्ठा msm_vblank_work, work);
	काष्ठा msm_drm_निजी *priv = vbl_work->priv;
	काष्ठा msm_kms *kms = priv->kms;

	अगर (vbl_work->enable)
		kms->funcs->enable_vblank(kms, priv->crtcs[vbl_work->crtc_id]);
	अन्यथा
		kms->funcs->disable_vblank(kms,	priv->crtcs[vbl_work->crtc_id]);

	kमुक्त(vbl_work);
पूर्ण

अटल पूर्णांक vblank_ctrl_queue_work(काष्ठा msm_drm_निजी *priv,
					पूर्णांक crtc_id, bool enable)
अणु
	काष्ठा msm_vblank_work *vbl_work;

	vbl_work = kzalloc(माप(*vbl_work), GFP_ATOMIC);
	अगर (!vbl_work)
		वापस -ENOMEM;

	INIT_WORK(&vbl_work->work, vblank_ctrl_worker);

	vbl_work->crtc_id = crtc_id;
	vbl_work->enable = enable;
	vbl_work->priv = priv;

	queue_work(priv->wq, &vbl_work->work);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_drm_uninit(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *ddev = platक्रमm_get_drvdata(pdev);
	काष्ठा msm_drm_निजी *priv = ddev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	काष्ठा msm_mdss *mdss = priv->mdss;
	पूर्णांक i;

	/*
	 * Shutकरोwn the hw अगर we're far enough aदीर्घ where things might be on.
	 * If we run this too early, we'll end up panicking in any variety of
	 * places. Since we करोn't रेजिस्टर the drm device until late in
	 * msm_drm_init, drm_dev->रेजिस्टरed is used as an indicator that the
	 * shutकरोwn will be successful.
	 */
	अगर (ddev->रेजिस्टरed) अणु
		drm_dev_unरेजिस्टर(ddev);
		drm_atomic_helper_shutकरोwn(ddev);
	पूर्ण

	/* We must cancel and cleanup any pending vblank enable/disable
	 * work beक्रमe drm_irq_uninstall() to aव्योम work re-enabling an
	 * irq after uninstall has disabled it.
	 */

	flush_workqueue(priv->wq);

	/* clean up event worker thपढ़ोs */
	क्रम (i = 0; i < priv->num_crtcs; i++) अणु
		अगर (priv->event_thपढ़ो[i].worker)
			kthपढ़ो_destroy_worker(priv->event_thपढ़ो[i].worker);
	पूर्ण

	msm_gem_shrinker_cleanup(ddev);

	drm_kms_helper_poll_fini(ddev);

	msm_perf_debugfs_cleanup(priv);
	msm_rd_debugfs_cleanup(priv);

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	अगर (fbdev && priv->fbdev)
		msm_fbdev_मुक्त(ddev);
#पूर्ण_अगर

	drm_mode_config_cleanup(ddev);

	pm_runसमय_get_sync(dev);
	drm_irq_uninstall(ddev);
	pm_runसमय_put_sync(dev);

	अगर (kms && kms->funcs)
		kms->funcs->destroy(kms);

	अगर (priv->vram.paddr) अणु
		अचिन्हित दीर्घ attrs = DMA_ATTR_NO_KERNEL_MAPPING;
		drm_mm_takeकरोwn(&priv->vram.mm);
		dma_मुक्त_attrs(dev, priv->vram.size, शून्य,
			       priv->vram.paddr, attrs);
	पूर्ण

	component_unbind_all(dev, ddev);

	अगर (mdss && mdss->funcs)
		mdss->funcs->destroy(ddev);

	ddev->dev_निजी = शून्य;
	drm_dev_put(ddev);

	destroy_workqueue(priv->wq);
	kमुक्त(priv);

	वापस 0;
पूर्ण

#घोषणा KMS_MDP4 4
#घोषणा KMS_MDP5 5
#घोषणा KMS_DPU  3

अटल पूर्णांक get_mdp_ver(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	वापस (पूर्णांक) (अचिन्हित दीर्घ) of_device_get_match_data(dev);
पूर्ण

#समावेश <linux/of_address.h>

bool msm_use_mmu(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;

	/* a2xx comes with its own MMU */
	वापस priv->is_a2xx || iommu_present(&platक्रमm_bus_type);
पूर्ण

अटल पूर्णांक msm_init_vram(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा device_node *node;
	अचिन्हित दीर्घ size = 0;
	पूर्णांक ret = 0;

	/* In the device-tree world, we could have a 'memory-region'
	 * phandle, which gives us a link to our "vram".  Allocating
	 * is all nicely असलtracted behind the dma api, but we need
	 * to know the entire size to allocate it all in one go. There
	 * are two हालs:
	 *  1) device with no IOMMU, in which हाल we need exclusive
	 *     access to a VRAM carveout big enough क्रम all gpu
	 *     buffers
	 *  2) device with IOMMU, but where the bootloader माला_दो up
	 *     a splash screen.  In this हाल, the VRAM carveout
	 *     need only be large enough क्रम fbdev fb.  But we need
	 *     exclusive access to the buffer to aव्योम the kernel
	 *     using those pages क्रम other purposes (which appears
	 *     as corruption on screen beक्रमe we have a chance to
	 *     load and करो initial modeset)
	 */

	node = of_parse_phandle(dev->dev->of_node, "memory-region", 0);
	अगर (node) अणु
		काष्ठा resource r;
		ret = of_address_to_resource(node, 0, &r);
		of_node_put(node);
		अगर (ret)
			वापस ret;
		size = r.end - r.start;
		DRM_INFO("using VRAM carveout: %lx@%pa\n", size, &r.start);

		/* अगर we have no IOMMU, then we need to use carveout allocator.
		 * Grab the entire CMA chunk carved out in early startup in
		 * mach-msm:
		 */
	पूर्ण अन्यथा अगर (!msm_use_mmu(dev)) अणु
		DRM_INFO("using %s VRAM carveout\n", vram);
		size = memparse(vram, शून्य);
	पूर्ण

	अगर (size) अणु
		अचिन्हित दीर्घ attrs = 0;
		व्योम *p;

		priv->vram.size = size;

		drm_mm_init(&priv->vram.mm, 0, (size >> PAGE_SHIFT) - 1);
		spin_lock_init(&priv->vram.lock);

		attrs |= DMA_ATTR_NO_KERNEL_MAPPING;
		attrs |= DMA_ATTR_WRITE_COMBINE;

		/* note that क्रम no-kernel-mapping, the vaddr वापसed
		 * is bogus, but non-null अगर allocation succeeded:
		 */
		p = dma_alloc_attrs(dev->dev, size,
				&priv->vram.paddr, GFP_KERNEL, attrs);
		अगर (!p) अणु
			DRM_DEV_ERROR(dev->dev, "failed to allocate VRAM\n");
			priv->vram.paddr = 0;
			वापस -ENOMEM;
		पूर्ण

		DRM_DEV_INFO(dev->dev, "VRAM: %08x->%08x\n",
				(uपूर्णांक32_t)priv->vram.paddr,
				(uपूर्णांक32_t)(priv->vram.paddr + size));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक msm_drm_init(काष्ठा device *dev, स्थिर काष्ठा drm_driver *drv)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *ddev;
	काष्ठा msm_drm_निजी *priv;
	काष्ठा msm_kms *kms;
	काष्ठा msm_mdss *mdss;
	पूर्णांक ret, i;

	ddev = drm_dev_alloc(drv, dev);
	अगर (IS_ERR(ddev)) अणु
		DRM_DEV_ERROR(dev, "failed to allocate drm_device\n");
		वापस PTR_ERR(ddev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, ddev);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ err_put_drm_dev;
	पूर्ण

	ddev->dev_निजी = priv;
	priv->dev = ddev;

	चयन (get_mdp_ver(pdev)) अणु
	हाल KMS_MDP5:
		ret = mdp5_mdss_init(ddev);
		अवरोध;
	हाल KMS_DPU:
		ret = dpu_mdss_init(ddev);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण
	अगर (ret)
		जाओ err_मुक्त_priv;

	mdss = priv->mdss;

	priv->wq = alloc_ordered_workqueue("msm", 0);

	INIT_LIST_HEAD(&priv->objects);
	mutex_init(&priv->obj_lock);

	INIT_LIST_HEAD(&priv->inactive_willneed);
	INIT_LIST_HEAD(&priv->inactive_करोntneed);
	INIT_LIST_HEAD(&priv->inactive_unpinned);
	mutex_init(&priv->mm_lock);

	/* Teach lockdep about lock ordering wrt. shrinker: */
	fs_reclaim_acquire(GFP_KERNEL);
	might_lock(&priv->mm_lock);
	fs_reclaim_release(GFP_KERNEL);

	drm_mode_config_init(ddev);

	ret = msm_init_vram(ddev);
	अगर (ret)
		जाओ err_destroy_mdss;

	/* Bind all our sub-components: */
	ret = component_bind_all(dev, ddev);
	अगर (ret)
		जाओ err_destroy_mdss;

	dma_set_max_seg_size(dev, अच_पूर्णांक_उच्च);

	msm_gem_shrinker_init(ddev);

	चयन (get_mdp_ver(pdev)) अणु
	हाल KMS_MDP4:
		kms = mdp4_kms_init(ddev);
		priv->kms = kms;
		अवरोध;
	हाल KMS_MDP5:
		kms = mdp5_kms_init(ddev);
		अवरोध;
	हाल KMS_DPU:
		kms = dpu_kms_init(ddev);
		priv->kms = kms;
		अवरोध;
	शेष:
		/* valid only क्रम the dummy headless हाल, where of_node=शून्य */
		WARN_ON(dev->of_node);
		kms = शून्य;
		अवरोध;
	पूर्ण

	अगर (IS_ERR(kms)) अणु
		DRM_DEV_ERROR(dev, "failed to load kms\n");
		ret = PTR_ERR(kms);
		priv->kms = शून्य;
		जाओ err_msm_uninit;
	पूर्ण

	/* Enable normalization of plane zpos */
	ddev->mode_config.normalize_zpos = true;

	अगर (kms) अणु
		kms->dev = ddev;
		ret = kms->funcs->hw_init(kms);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev, "kms hw init failed: %d\n", ret);
			जाओ err_msm_uninit;
		पूर्ण
	पूर्ण

	ddev->mode_config.funcs = &mode_config_funcs;
	ddev->mode_config.helper_निजी = &mode_config_helper_funcs;

	क्रम (i = 0; i < priv->num_crtcs; i++) अणु
		/* initialize event thपढ़ो */
		priv->event_thपढ़ो[i].crtc_id = priv->crtcs[i]->base.id;
		priv->event_thपढ़ो[i].dev = ddev;
		priv->event_thपढ़ो[i].worker = kthपढ़ो_create_worker(0,
			"crtc_event:%d", priv->event_thपढ़ो[i].crtc_id);
		अगर (IS_ERR(priv->event_thपढ़ो[i].worker)) अणु
			DRM_DEV_ERROR(dev, "failed to create crtc_event kthread\n");
			जाओ err_msm_uninit;
		पूर्ण

		sched_set_fअगरo(priv->event_thपढ़ो[i].worker->task);
	पूर्ण

	ret = drm_vblank_init(ddev, priv->num_crtcs);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "failed to initialize vblank\n");
		जाओ err_msm_uninit;
	पूर्ण

	अगर (kms) अणु
		pm_runसमय_get_sync(dev);
		ret = drm_irq_install(ddev, kms->irq);
		pm_runसमय_put_sync(dev);
		अगर (ret < 0) अणु
			DRM_DEV_ERROR(dev, "failed to install IRQ handler\n");
			जाओ err_msm_uninit;
		पूर्ण
	पूर्ण

	ret = drm_dev_रेजिस्टर(ddev, 0);
	अगर (ret)
		जाओ err_msm_uninit;

	drm_mode_config_reset(ddev);

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	अगर (kms && fbdev)
		priv->fbdev = msm_fbdev_init(ddev);
#पूर्ण_अगर

	ret = msm_debugfs_late_init(ddev);
	अगर (ret)
		जाओ err_msm_uninit;

	drm_kms_helper_poll_init(ddev);

	वापस 0;

err_msm_uninit:
	msm_drm_uninit(dev);
	वापस ret;
err_destroy_mdss:
	अगर (mdss && mdss->funcs)
		mdss->funcs->destroy(ddev);
err_मुक्त_priv:
	kमुक्त(priv);
err_put_drm_dev:
	drm_dev_put(ddev);
	platक्रमm_set_drvdata(pdev, शून्य);
	वापस ret;
पूर्ण

/*
 * DRM operations:
 */

अटल व्योम load_gpu(काष्ठा drm_device *dev)
अणु
	अटल DEFINE_MUTEX(init_lock);
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;

	mutex_lock(&init_lock);

	अगर (!priv->gpu)
		priv->gpu = adreno_load_gpu(dev);

	mutex_unlock(&init_lock);
पूर्ण

अटल पूर्णांक context_init(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_file_निजी *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	kref_init(&ctx->ref);
	msm_submitqueue_init(dev, ctx);

	ctx->aspace = msm_gpu_create_निजी_address_space(priv->gpu, current);
	file->driver_priv = ctx;

	वापस 0;
पूर्ण

अटल पूर्णांक msm_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	/* For now, load gpu on खोलो.. to aव्योम the requirement of having
	 * firmware in the initrd.
	 */
	load_gpu(dev);

	वापस context_init(dev, file);
पूर्ण

अटल व्योम context_बंद(काष्ठा msm_file_निजी *ctx)
अणु
	msm_submitqueue_बंद(ctx);
	msm_file_निजी_put(ctx);
पूर्ण

अटल व्योम msm_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_file_निजी *ctx = file->driver_priv;

	mutex_lock(&dev->काष्ठा_mutex);
	अगर (ctx == priv->lastctx)
		priv->lastctx = शून्य;
	mutex_unlock(&dev->काष्ठा_mutex);

	context_बंद(ctx);
पूर्ण

अटल irqवापस_t msm_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = arg;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	BUG_ON(!kms);
	वापस kms->funcs->irq(kms);
पूर्ण

अटल व्योम msm_irq_preinstall(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	BUG_ON(!kms);
	kms->funcs->irq_preinstall(kms);
पूर्ण

अटल पूर्णांक msm_irq_postinstall(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	BUG_ON(!kms);

	अगर (kms->funcs->irq_postinstall)
		वापस kms->funcs->irq_postinstall(kms);

	वापस 0;
पूर्ण

अटल व्योम msm_irq_uninstall(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	BUG_ON(!kms);
	kms->funcs->irq_uninstall(kms);
पूर्ण

पूर्णांक msm_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	अगर (!kms)
		वापस -ENXIO;
	DBG("dev=%p, crtc=%u", dev, pipe);
	वापस vblank_ctrl_queue_work(priv, pipe, true);
पूर्ण

व्योम msm_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	अगर (!kms)
		वापस;
	DBG("dev=%p, crtc=%u", dev, pipe);
	vblank_ctrl_queue_work(priv, pipe, false);
पूर्ण

/*
 * DRM ioctls:
 */

अटल पूर्णांक msm_ioctl_get_param(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_msm_param *args = data;
	काष्ठा msm_gpu *gpu;

	/* क्रम now, we just have 3d pipe.. eventually this would need to
	 * be more clever to dispatch to appropriate gpu module:
	 */
	अगर (args->pipe != MSM_PIPE_3D0)
		वापस -EINVAL;

	gpu = priv->gpu;

	अगर (!gpu)
		वापस -ENXIO;

	वापस gpu->funcs->get_param(gpu, args->param, &args->value);
पूर्ण

अटल पूर्णांक msm_ioctl_gem_new(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_msm_gem_new *args = data;

	अगर (args->flags & ~MSM_BO_FLAGS) अणु
		DRM_ERROR("invalid flags: %08x\n", args->flags);
		वापस -EINVAL;
	पूर्ण

	वापस msm_gem_new_handle(dev, file, args->size,
			args->flags, &args->handle, शून्य);
पूर्ण

अटल अंतरभूत kसमय_प्रकार to_kसमय(काष्ठा drm_msm_बारpec समयout)
अणु
	वापस kसमय_set(समयout.tv_sec, समयout.tv_nsec);
पूर्ण

अटल पूर्णांक msm_ioctl_gem_cpu_prep(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_msm_gem_cpu_prep *args = data;
	काष्ठा drm_gem_object *obj;
	kसमय_प्रकार समयout = to_kसमय(args->समयout);
	पूर्णांक ret;

	अगर (args->op & ~MSM_PREP_FLAGS) अणु
		DRM_ERROR("invalid op: %08x\n", args->op);
		वापस -EINVAL;
	पूर्ण

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	ret = msm_gem_cpu_prep(obj, args->op, &समयout);

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल पूर्णांक msm_ioctl_gem_cpu_fini(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_msm_gem_cpu_fini *args = data;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	ret = msm_gem_cpu_fini(obj);

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल पूर्णांक msm_ioctl_gem_info_iova(काष्ठा drm_device *dev,
		काष्ठा drm_file *file, काष्ठा drm_gem_object *obj,
		uपूर्णांक64_t *iova)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_file_निजी *ctx = file->driver_priv;

	अगर (!priv->gpu)
		वापस -EINVAL;

	/*
	 * Don't pin the memory here - just get an address so that userspace can
	 * be productive
	 */
	वापस msm_gem_get_iova(obj, ctx->aspace, iova);
पूर्ण

अटल पूर्णांक msm_ioctl_gem_info(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_msm_gem_info *args = data;
	काष्ठा drm_gem_object *obj;
	काष्ठा msm_gem_object *msm_obj;
	पूर्णांक i, ret = 0;

	अगर (args->pad)
		वापस -EINVAL;

	चयन (args->info) अणु
	हाल MSM_INFO_GET_OFFSET:
	हाल MSM_INFO_GET_IOVA:
		/* value वापसed as immediate, not poपूर्णांकer, so len==0: */
		अगर (args->len)
			वापस -EINVAL;
		अवरोध;
	हाल MSM_INFO_SET_NAME:
	हाल MSM_INFO_GET_NAME:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	msm_obj = to_msm_bo(obj);

	चयन (args->info) अणु
	हाल MSM_INFO_GET_OFFSET:
		args->value = msm_gem_mmap_offset(obj);
		अवरोध;
	हाल MSM_INFO_GET_IOVA:
		ret = msm_ioctl_gem_info_iova(dev, file, obj, &args->value);
		अवरोध;
	हाल MSM_INFO_SET_NAME:
		/* length check should leave room क्रम terminating null: */
		अगर (args->len >= माप(msm_obj->name)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(msm_obj->name, u64_to_user_ptr(args->value),
				   args->len)) अणु
			msm_obj->name[0] = '\0';
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		msm_obj->name[args->len] = '\0';
		क्रम (i = 0; i < args->len; i++) अणु
			अगर (!है_छाप(msm_obj->name[i])) अणु
				msm_obj->name[i] = '\0';
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल MSM_INFO_GET_NAME:
		अगर (args->value && (args->len < म_माप(msm_obj->name))) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		args->len = म_माप(msm_obj->name);
		अगर (args->value) अणु
			अगर (copy_to_user(u64_to_user_ptr(args->value),
					 msm_obj->name, args->len))
				ret = -EFAULT;
		पूर्ण
		अवरोध;
	पूर्ण

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल पूर्णांक msm_ioctl_रुको_fence(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_msm_रुको_fence *args = data;
	kसमय_प्रकार समयout = to_kसमय(args->समयout);
	काष्ठा msm_gpu_submitqueue *queue;
	काष्ठा msm_gpu *gpu = priv->gpu;
	पूर्णांक ret;

	अगर (args->pad) अणु
		DRM_ERROR("invalid pad: %08x\n", args->pad);
		वापस -EINVAL;
	पूर्ण

	अगर (!gpu)
		वापस 0;

	queue = msm_submitqueue_get(file->driver_priv, args->queueid);
	अगर (!queue)
		वापस -ENOENT;

	ret = msm_रुको_fence(gpu->rb[queue->prio]->fctx, args->fence, &समयout,
		true);

	msm_submitqueue_put(queue);
	वापस ret;
पूर्ण

अटल पूर्णांक msm_ioctl_gem_madvise(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_msm_gem_madvise *args = data;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	चयन (args->madv) अणु
	हाल MSM_MADV_DONTNEED:
	हाल MSM_MADV_WILLNEED:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (!obj) अणु
		वापस -ENOENT;
	पूर्ण

	ret = msm_gem_madvise(obj, args->madv);
	अगर (ret >= 0) अणु
		args->retained = ret;
		ret = 0;
	पूर्ण

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण


अटल पूर्णांक msm_ioctl_submitqueue_new(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_msm_submitqueue *args = data;

	अगर (args->flags & ~MSM_SUBMITQUEUE_FLAGS)
		वापस -EINVAL;

	वापस msm_submitqueue_create(dev, file->driver_priv, args->prio,
		args->flags, &args->id);
पूर्ण

अटल पूर्णांक msm_ioctl_submitqueue_query(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	वापस msm_submitqueue_query(dev, file->driver_priv, data);
पूर्ण

अटल पूर्णांक msm_ioctl_submitqueue_बंद(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	u32 id = *(u32 *) data;

	वापस msm_submitqueue_हटाओ(file->driver_priv, id);
पूर्ण

अटल स्थिर काष्ठा drm_ioctl_desc msm_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(MSM_GET_PARAM,    msm_ioctl_get_param,    DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_GEM_NEW,      msm_ioctl_gem_new,      DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_GEM_INFO,     msm_ioctl_gem_info,     DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_GEM_CPU_PREP, msm_ioctl_gem_cpu_prep, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_GEM_CPU_FINI, msm_ioctl_gem_cpu_fini, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_GEM_SUBMIT,   msm_ioctl_gem_submit,   DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_WAIT_FENCE,   msm_ioctl_रुको_fence,   DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_GEM_MADVISE,  msm_ioctl_gem_madvise,  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_SUBMITQUEUE_NEW,   msm_ioctl_submitqueue_new,   DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_SUBMITQUEUE_CLOSE, msm_ioctl_submitqueue_बंद, DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(MSM_SUBMITQUEUE_QUERY, msm_ioctl_submitqueue_query, DRM_RENDER_ALLOW),
पूर्ण;

अटल स्थिर काष्ठा file_operations fops = अणु
	.owner              = THIS_MODULE,
	.खोलो               = drm_खोलो,
	.release            = drm_release,
	.unlocked_ioctl     = drm_ioctl,
	.compat_ioctl       = drm_compat_ioctl,
	.poll               = drm_poll,
	.पढ़ो               = drm_पढ़ो,
	.llseek             = no_llseek,
	.mmap               = msm_gem_mmap,
पूर्ण;

अटल स्थिर काष्ठा drm_driver msm_driver = अणु
	.driver_features    = DRIVER_GEM |
				DRIVER_RENDER |
				DRIVER_ATOMIC |
				DRIVER_MODESET |
				DRIVER_SYNCOBJ,
	.खोलो               = msm_खोलो,
	.postबंद           = msm_postबंद,
	.lastबंद          = drm_fb_helper_lastबंद,
	.irq_handler        = msm_irq,
	.irq_preinstall     = msm_irq_preinstall,
	.irq_postinstall    = msm_irq_postinstall,
	.irq_uninstall      = msm_irq_uninstall,
	.dumb_create        = msm_gem_dumb_create,
	.dumb_map_offset    = msm_gem_dumb_map_offset,
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = msm_gem_prime_import_sg_table,
	.gem_prime_mmap     = msm_gem_prime_mmap,
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init       = msm_debugfs_init,
#पूर्ण_अगर
	.ioctls             = msm_ioctls,
	.num_ioctls         = ARRAY_SIZE(msm_ioctls),
	.fops               = &fops,
	.name               = "msm",
	.desc               = "MSM Snapdragon DRM",
	.date               = "20130625",
	.major              = MSM_VERSION_MAJOR,
	.minor              = MSM_VERSION_MINOR,
	.patchlevel         = MSM_VERSION_PATCHLEVEL,
पूर्ण;

अटल पूर्णांक __maybe_unused msm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा msm_drm_निजी *priv = ddev->dev_निजी;
	काष्ठा msm_mdss *mdss = priv->mdss;

	DBG("");

	अगर (mdss && mdss->funcs)
		वापस mdss->funcs->disable(mdss);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused msm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा msm_drm_निजी *priv = ddev->dev_निजी;
	काष्ठा msm_mdss *mdss = priv->mdss;

	DBG("");

	अगर (mdss && mdss->funcs)
		वापस mdss->funcs->enable(mdss);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused msm_pm_suspend(काष्ठा device *dev)
अणु

	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	वापस msm_runसमय_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused msm_pm_resume(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	वापस msm_runसमय_resume(dev);
पूर्ण

अटल पूर्णांक __maybe_unused msm_pm_prepare(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा msm_drm_निजी *priv = ddev ? ddev->dev_निजी : शून्य;

	अगर (!priv || !priv->kms)
		वापस 0;

	वापस drm_mode_config_helper_suspend(ddev);
पूर्ण

अटल व्योम __maybe_unused msm_pm_complete(काष्ठा device *dev)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा msm_drm_निजी *priv = ddev ? ddev->dev_निजी : शून्य;

	अगर (!priv || !priv->kms)
		वापस;

	drm_mode_config_helper_resume(ddev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops msm_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(msm_pm_suspend, msm_pm_resume)
	SET_RUNTIME_PM_OPS(msm_runसमय_suspend, msm_runसमय_resume, शून्य)
	.prepare = msm_pm_prepare,
	.complete = msm_pm_complete,
पूर्ण;

/*
 * Componentized driver support:
 */

/*
 * NOTE: duplication of the same code as exynos or imx (or probably any other).
 * so probably some room क्रम some helpers
 */
अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->of_node == data;
पूर्ण

/*
 * Identअगरy what components need to be added by parsing what remote-endpoपूर्णांकs
 * our MDP output ports are connected to. In the हाल of LVDS on MDP4, there
 * is no बाह्यal component that we need to add since LVDS is within MDP4
 * itself.
 */
अटल पूर्णांक add_components_mdp(काष्ठा device *mdp_dev,
			      काष्ठा component_match **matchptr)
अणु
	काष्ठा device_node *np = mdp_dev->of_node;
	काष्ठा device_node *ep_node;
	काष्ठा device *master_dev;

	/*
	 * on MDP4 based platक्रमms, the MDP platक्रमm device is the component
	 * master that adds other display पूर्णांकerface components to itself.
	 *
	 * on MDP5 based platक्रमms, the MDSS platक्रमm device is the component
	 * master that adds MDP5 and other display पूर्णांकerface components to
	 * itself.
	 */
	अगर (of_device_is_compatible(np, "qcom,mdp4"))
		master_dev = mdp_dev;
	अन्यथा
		master_dev = mdp_dev->parent;

	क्रम_each_endpoपूर्णांक_of_node(np, ep_node) अणु
		काष्ठा device_node *पूर्णांकf;
		काष्ठा of_endpoपूर्णांक ep;
		पूर्णांक ret;

		ret = of_graph_parse_endpoपूर्णांक(ep_node, &ep);
		अगर (ret) अणु
			DRM_DEV_ERROR(mdp_dev, "unable to parse port endpoint\n");
			of_node_put(ep_node);
			वापस ret;
		पूर्ण

		/*
		 * The LCDC/LVDS port on MDP4 is a speacial हाल where the
		 * remote-endpoपूर्णांक isn't a component that we need to add
		 */
		अगर (of_device_is_compatible(np, "qcom,mdp4") &&
		    ep.port == 0)
			जारी;

		/*
		 * It's okay if some of the ports don't have a remote endpoपूर्णांक
		 * specअगरied. It just means that the port isn't connected to
		 * any बाह्यal पूर्णांकerface.
		 */
		पूर्णांकf = of_graph_get_remote_port_parent(ep_node);
		अगर (!पूर्णांकf)
			जारी;

		अगर (of_device_is_available(पूर्णांकf))
			drm_of_component_match_add(master_dev, matchptr,
						   compare_of, पूर्णांकf);

		of_node_put(पूर्णांकf);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक compare_name_mdp(काष्ठा device *dev, व्योम *data)
अणु
	वापस (म_माला(dev_name(dev), "mdp") != शून्य);
पूर्ण

अटल पूर्णांक add_display_components(काष्ठा platक्रमm_device *pdev,
				  काष्ठा component_match **matchptr)
अणु
	काष्ठा device *mdp_dev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	/*
	 * MDP5/DPU based devices करोn't have a flat hierarchy. There is a top
	 * level parent: MDSS, and children: MDP5/DPU, DSI, HDMI, eDP etc.
	 * Populate the children devices, find the MDP5/DPU node, and then add
	 * the पूर्णांकerfaces to our components list.
	 */
	चयन (get_mdp_ver(pdev)) अणु
	हाल KMS_MDP5:
	हाल KMS_DPU:
		ret = of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev, "failed to populate children devices\n");
			वापस ret;
		पूर्ण

		mdp_dev = device_find_child(dev, शून्य, compare_name_mdp);
		अगर (!mdp_dev) अणु
			DRM_DEV_ERROR(dev, "failed to find MDSS MDP node\n");
			of_platक्रमm_depopulate(dev);
			वापस -ENODEV;
		पूर्ण

		put_device(mdp_dev);

		/* add the MDP component itself */
		drm_of_component_match_add(dev, matchptr, compare_of,
					   mdp_dev->of_node);
		अवरोध;
	हाल KMS_MDP4:
		/* MDP4 */
		mdp_dev = dev;
		अवरोध;
	पूर्ण

	ret = add_components_mdp(mdp_dev, matchptr);
	अगर (ret)
		of_platक्रमm_depopulate(dev);

	वापस ret;
पूर्ण

/*
 * We करोn't know what's the best binding to link the gpu with the drm device.
 * Fow now, we just hunt क्रम all the possible gpus that we support, and add them
 * as components.
 */
अटल स्थिर काष्ठा of_device_id msm_gpu_match[] = अणु
	अणु .compatible = "qcom,adreno" पूर्ण,
	अणु .compatible = "qcom,adreno-3xx" पूर्ण,
	अणु .compatible = "amd,imageon" पूर्ण,
	अणु .compatible = "qcom,kgsl-3d0" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक add_gpu_components(काष्ठा device *dev,
			      काष्ठा component_match **matchptr)
अणु
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, msm_gpu_match);
	अगर (!np)
		वापस 0;

	अगर (of_device_is_available(np))
		drm_of_component_match_add(dev, matchptr, compare_of, np);

	of_node_put(np);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_drm_bind(काष्ठा device *dev)
अणु
	वापस msm_drm_init(dev, &msm_driver);
पूर्ण

अटल व्योम msm_drm_unbind(काष्ठा device *dev)
अणु
	msm_drm_uninit(dev);
पूर्ण

अटल स्थिर काष्ठा component_master_ops msm_drm_ops = अणु
	.bind = msm_drm_bind,
	.unbind = msm_drm_unbind,
पूर्ण;

/*
 * Platक्रमm driver:
 */

अटल पूर्णांक msm_pdev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा component_match *match = शून्य;
	पूर्णांक ret;

	अगर (get_mdp_ver(pdev)) अणु
		ret = add_display_components(pdev, &match);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = add_gpu_components(&pdev->dev, &match);
	अगर (ret)
		जाओ fail;

	/* on all devices that I am aware of, iommu's which can map
	 * any address the cpu can see are used:
	 */
	ret = dma_set_mask_and_coherent(&pdev->dev, ~0);
	अगर (ret)
		जाओ fail;

	ret = component_master_add_with_match(&pdev->dev, &msm_drm_ops, match);
	अगर (ret)
		जाओ fail;

	वापस 0;

fail:
	of_platक्रमm_depopulate(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक msm_pdev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &msm_drm_ops);
	of_platक्रमm_depopulate(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम msm_pdev_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा drm_device *drm = platक्रमm_get_drvdata(pdev);
	काष्ठा msm_drm_निजी *priv = drm ? drm->dev_निजी : शून्य;

	अगर (!priv || !priv->kms)
		वापस;

	drm_atomic_helper_shutकरोwn(drm);
पूर्ण

अटल स्थिर काष्ठा of_device_id dt_match[] = अणु
	अणु .compatible = "qcom,mdp4", .data = (व्योम *)KMS_MDP4 पूर्ण,
	अणु .compatible = "qcom,mdss", .data = (व्योम *)KMS_MDP5 पूर्ण,
	अणु .compatible = "qcom,sdm845-mdss", .data = (व्योम *)KMS_DPU पूर्ण,
	अणु .compatible = "qcom,sc7180-mdss", .data = (व्योम *)KMS_DPU पूर्ण,
	अणु .compatible = "qcom,sc7280-mdss", .data = (व्योम *)KMS_DPU पूर्ण,
	अणु .compatible = "qcom,sm8150-mdss", .data = (व्योम *)KMS_DPU पूर्ण,
	अणु .compatible = "qcom,sm8250-mdss", .data = (व्योम *)KMS_DPU पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dt_match);

अटल काष्ठा platक्रमm_driver msm_platक्रमm_driver = अणु
	.probe      = msm_pdev_probe,
	.हटाओ     = msm_pdev_हटाओ,
	.shutकरोwn   = msm_pdev_shutकरोwn,
	.driver     = अणु
		.name   = "msm",
		.of_match_table = dt_match,
		.pm     = &msm_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init msm_drm_रेजिस्टर(व्योम)
अणु
	अगर (!modeset)
		वापस -EINVAL;

	DBG("init");
	msm_mdp_रेजिस्टर();
	msm_dpu_रेजिस्टर();
	msm_dsi_रेजिस्टर();
	msm_edp_रेजिस्टर();
	msm_hdmi_रेजिस्टर();
	msm_dp_रेजिस्टर();
	adreno_रेजिस्टर();
	वापस platक्रमm_driver_रेजिस्टर(&msm_platक्रमm_driver);
पूर्ण

अटल व्योम __निकास msm_drm_unरेजिस्टर(व्योम)
अणु
	DBG("fini");
	platक्रमm_driver_unरेजिस्टर(&msm_platक्रमm_driver);
	msm_dp_unरेजिस्टर();
	msm_hdmi_unरेजिस्टर();
	adreno_unरेजिस्टर();
	msm_edp_unरेजिस्टर();
	msm_dsi_unरेजिस्टर();
	msm_mdp_unरेजिस्टर();
	msm_dpu_unरेजिस्टर();
पूर्ण

module_init(msm_drm_रेजिस्टर);
module_निकास(msm_drm_unरेजिस्टर);

MODULE_AUTHOR("Rob Clark <robdclark@gmail.com");
MODULE_DESCRIPTION("MSM DRM Driver");
MODULE_LICENSE("GPL");
