<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#समावेश <linux/component.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_prime.h>

#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_drv.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_mmu.h"
#समावेश "etnaviv_perfmon.h"

/*
 * DRM operations:
 */


अटल व्योम load_gpu(काष्ठा drm_device *dev)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ETNA_MAX_PIPES; i++) अणु
		काष्ठा etnaviv_gpu *g = priv->gpu[i];

		अगर (g) अणु
			पूर्णांक ret;

			ret = etnaviv_gpu_init(g);
			अगर (ret)
				priv->gpu[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक etnaviv_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा etnaviv_file_निजी *ctx;
	पूर्णांक ret, i;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->mmu = etnaviv_iommu_context_init(priv->mmu_global,
					      priv->cmdbuf_suballoc);
	अगर (!ctx->mmu) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < ETNA_MAX_PIPES; i++) अणु
		काष्ठा etnaviv_gpu *gpu = priv->gpu[i];
		काष्ठा drm_gpu_scheduler *sched;

		अगर (gpu) अणु
			sched = &gpu->sched;
			drm_sched_entity_init(&ctx->sched_entity[i],
					      DRM_SCHED_PRIORITY_NORMAL, &sched,
					      1, शून्य);
			पूर्ण
	पूर्ण

	file->driver_priv = ctx;

	वापस 0;

out_मुक्त:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल व्योम etnaviv_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा etnaviv_file_निजी *ctx = file->driver_priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ETNA_MAX_PIPES; i++) अणु
		काष्ठा etnaviv_gpu *gpu = priv->gpu[i];

		अगर (gpu)
			drm_sched_entity_destroy(&ctx->sched_entity[i]);
	पूर्ण

	etnaviv_iommu_context_put(ctx->mmu);

	kमुक्त(ctx);
पूर्ण

/*
 * DRM debugfs:
 */

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक etnaviv_gem_show(काष्ठा drm_device *dev, काष्ठा seq_file *m)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;

	etnaviv_gem_describe_objects(priv, m);

	वापस 0;
पूर्ण

अटल पूर्णांक etnaviv_mm_show(काष्ठा drm_device *dev, काष्ठा seq_file *m)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	पढ़ो_lock(&dev->vma_offset_manager->vm_lock);
	drm_mm_prपूर्णांक(&dev->vma_offset_manager->vm_addr_space_mm, &p);
	पढ़ो_unlock(&dev->vma_offset_manager->vm_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक etnaviv_mmu_show(काष्ठा etnaviv_gpu *gpu, काष्ठा seq_file *m)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);
	काष्ठा etnaviv_iommu_context *mmu_context;

	seq_म_लिखो(m, "Active Objects (%s):\n", dev_name(gpu->dev));

	/*
	 * Lock the GPU to aव्योम a MMU context चयन just now and elevate
	 * the refcount of the current context to aव्योम it disappearing from
	 * under our feet.
	 */
	mutex_lock(&gpu->lock);
	mmu_context = gpu->mmu_context;
	अगर (mmu_context)
		etnaviv_iommu_context_get(mmu_context);
	mutex_unlock(&gpu->lock);

	अगर (!mmu_context)
		वापस 0;

	mutex_lock(&mmu_context->lock);
	drm_mm_prपूर्णांक(&mmu_context->mm, &p);
	mutex_unlock(&mmu_context->lock);

	etnaviv_iommu_context_put(mmu_context);

	वापस 0;
पूर्ण

अटल व्योम etnaviv_buffer_dump(काष्ठा etnaviv_gpu *gpu, काष्ठा seq_file *m)
अणु
	काष्ठा etnaviv_cmdbuf *buf = &gpu->buffer;
	u32 size = buf->size;
	u32 *ptr = buf->vaddr;
	u32 i;

	seq_म_लिखो(m, "virt %p - phys 0x%llx - free 0x%08x\n",
			buf->vaddr, (u64)etnaviv_cmdbuf_get_pa(buf),
			size - buf->user_size);

	क्रम (i = 0; i < size / 4; i++) अणु
		अगर (i && !(i % 4))
			seq_माला_दो(m, "\n");
		अगर (i % 4 == 0)
			seq_म_लिखो(m, "\t0x%p: ", ptr + i);
		seq_म_लिखो(m, "%08x ", *(ptr + i));
	पूर्ण
	seq_माला_दो(m, "\n");
पूर्ण

अटल पूर्णांक etnaviv_ring_show(काष्ठा etnaviv_gpu *gpu, काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "Ring Buffer (%s): ", dev_name(gpu->dev));

	mutex_lock(&gpu->lock);
	etnaviv_buffer_dump(gpu, m);
	mutex_unlock(&gpu->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक show_unlocked(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	पूर्णांक (*show)(काष्ठा drm_device *dev, काष्ठा seq_file *m) =
			node->info_ent->data;

	वापस show(dev, m);
पूर्ण

अटल पूर्णांक show_each_gpu(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा etnaviv_gpu *gpu;
	पूर्णांक (*show)(काष्ठा etnaviv_gpu *gpu, काष्ठा seq_file *m) =
			node->info_ent->data;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < ETNA_MAX_PIPES; i++) अणु
		gpu = priv->gpu[i];
		अगर (!gpu)
			जारी;

		ret = show(gpu, m);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा drm_info_list etnaviv_debugfs_list[] = अणु
		अणु"gpu", show_each_gpu, 0, etnaviv_gpu_debugfsपूर्ण,
		अणु"gem", show_unlocked, 0, etnaviv_gem_showपूर्ण,
		अणु "mm", show_unlocked, 0, etnaviv_mm_show पूर्ण,
		अणु"mmu", show_each_gpu, 0, etnaviv_mmu_showपूर्ण,
		अणु"ring", show_each_gpu, 0, etnaviv_ring_showपूर्ण,
पूर्ण;

अटल व्योम etnaviv_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(etnaviv_debugfs_list,
				 ARRAY_SIZE(etnaviv_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
#पूर्ण_अगर

/*
 * DRM ioctls:
 */

अटल पूर्णांक etnaviv_ioctl_get_param(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_etnaviv_param *args = data;
	काष्ठा etnaviv_gpu *gpu;

	अगर (args->pipe >= ETNA_MAX_PIPES)
		वापस -EINVAL;

	gpu = priv->gpu[args->pipe];
	अगर (!gpu)
		वापस -ENXIO;

	वापस etnaviv_gpu_get_param(gpu, args->param, &args->value);
पूर्ण

अटल पूर्णांक etnaviv_ioctl_gem_new(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_etnaviv_gem_new *args = data;

	अगर (args->flags & ~(ETNA_BO_CACHED | ETNA_BO_WC | ETNA_BO_UNCACHED |
			    ETNA_BO_FORCE_MMU))
		वापस -EINVAL;

	वापस etnaviv_gem_new_handle(dev, file, args->size,
			args->flags, &args->handle);
पूर्ण

अटल पूर्णांक etnaviv_ioctl_gem_cpu_prep(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_etnaviv_gem_cpu_prep *args = data;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	अगर (args->op & ~(ETNA_PREP_READ | ETNA_PREP_WRITE | ETNA_PREP_NOSYNC))
		वापस -EINVAL;

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	ret = etnaviv_gem_cpu_prep(obj, args->op, &args->समयout);

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल पूर्णांक etnaviv_ioctl_gem_cpu_fini(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_etnaviv_gem_cpu_fini *args = data;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	अगर (args->flags)
		वापस -EINVAL;

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	ret = etnaviv_gem_cpu_fini(obj);

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल पूर्णांक etnaviv_ioctl_gem_info(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_etnaviv_gem_info *args = data;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	अगर (args->pad)
		वापस -EINVAL;

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	ret = etnaviv_gem_mmap_offset(obj, &args->offset);
	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल पूर्णांक etnaviv_ioctl_रुको_fence(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा drm_etnaviv_रुको_fence *args = data;
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_etnaviv_बारpec *समयout = &args->समयout;
	काष्ठा etnaviv_gpu *gpu;

	अगर (args->flags & ~(ETNA_WAIT_NONBLOCK))
		वापस -EINVAL;

	अगर (args->pipe >= ETNA_MAX_PIPES)
		वापस -EINVAL;

	gpu = priv->gpu[args->pipe];
	अगर (!gpu)
		वापस -ENXIO;

	अगर (args->flags & ETNA_WAIT_NONBLOCK)
		समयout = शून्य;

	वापस etnaviv_gpu_रुको_fence_पूर्णांकerruptible(gpu, args->fence,
						    समयout);
पूर्ण

अटल पूर्णांक etnaviv_ioctl_gem_userptr(काष्ठा drm_device *dev, व्योम *data,
	काष्ठा drm_file *file)
अणु
	काष्ठा drm_etnaviv_gem_userptr *args = data;

	अगर (args->flags & ~(ETNA_USERPTR_READ|ETNA_USERPTR_WRITE) ||
	    args->flags == 0)
		वापस -EINVAL;

	अगर (offset_in_page(args->user_ptr | args->user_size) ||
	    (uपूर्णांकptr_t)args->user_ptr != args->user_ptr ||
	    (u32)args->user_size != args->user_size ||
	    args->user_ptr & ~PAGE_MASK)
		वापस -EINVAL;

	अगर (!access_ok((व्योम __user *)(अचिन्हित दीर्घ)args->user_ptr,
		       args->user_size))
		वापस -EFAULT;

	वापस etnaviv_gem_new_userptr(dev, file, args->user_ptr,
				       args->user_size, args->flags,
				       &args->handle);
पूर्ण

अटल पूर्णांक etnaviv_ioctl_gem_रुको(काष्ठा drm_device *dev, व्योम *data,
	काष्ठा drm_file *file)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_etnaviv_gem_रुको *args = data;
	काष्ठा drm_etnaviv_बारpec *समयout = &args->समयout;
	काष्ठा drm_gem_object *obj;
	काष्ठा etnaviv_gpu *gpu;
	पूर्णांक ret;

	अगर (args->flags & ~(ETNA_WAIT_NONBLOCK))
		वापस -EINVAL;

	अगर (args->pipe >= ETNA_MAX_PIPES)
		वापस -EINVAL;

	gpu = priv->gpu[args->pipe];
	अगर (!gpu)
		वापस -ENXIO;

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	अगर (args->flags & ETNA_WAIT_NONBLOCK)
		समयout = शून्य;

	ret = etnaviv_gem_रुको_bo(gpu, obj, समयout);

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण

अटल पूर्णांक etnaviv_ioctl_pm_query_करोm(काष्ठा drm_device *dev, व्योम *data,
	काष्ठा drm_file *file)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_etnaviv_pm_करोमुख्य *args = data;
	काष्ठा etnaviv_gpu *gpu;

	अगर (args->pipe >= ETNA_MAX_PIPES)
		वापस -EINVAL;

	gpu = priv->gpu[args->pipe];
	अगर (!gpu)
		वापस -ENXIO;

	वापस etnaviv_pm_query_करोm(gpu, args);
पूर्ण

अटल पूर्णांक etnaviv_ioctl_pm_query_sig(काष्ठा drm_device *dev, व्योम *data,
	काष्ठा drm_file *file)
अणु
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_etnaviv_pm_संकेत *args = data;
	काष्ठा etnaviv_gpu *gpu;

	अगर (args->pipe >= ETNA_MAX_PIPES)
		वापस -EINVAL;

	gpu = priv->gpu[args->pipe];
	अगर (!gpu)
		वापस -ENXIO;

	वापस etnaviv_pm_query_sig(gpu, args);
पूर्ण

अटल स्थिर काष्ठा drm_ioctl_desc etnaviv_ioctls[] = अणु
#घोषणा ETNA_IOCTL(n, func, flags) \
	DRM_IOCTL_DEF_DRV(ETNAVIV_##n, etnaviv_ioctl_##func, flags)
	ETNA_IOCTL(GET_PARAM,    get_param,    DRM_RENDER_ALLOW),
	ETNA_IOCTL(GEM_NEW,      gem_new,      DRM_RENDER_ALLOW),
	ETNA_IOCTL(GEM_INFO,     gem_info,     DRM_RENDER_ALLOW),
	ETNA_IOCTL(GEM_CPU_PREP, gem_cpu_prep, DRM_RENDER_ALLOW),
	ETNA_IOCTL(GEM_CPU_FINI, gem_cpu_fini, DRM_RENDER_ALLOW),
	ETNA_IOCTL(GEM_SUBMIT,   gem_submit,   DRM_RENDER_ALLOW),
	ETNA_IOCTL(WAIT_FENCE,   रुको_fence,   DRM_RENDER_ALLOW),
	ETNA_IOCTL(GEM_USERPTR,  gem_userptr,  DRM_RENDER_ALLOW),
	ETNA_IOCTL(GEM_WAIT,     gem_रुको,     DRM_RENDER_ALLOW),
	ETNA_IOCTL(PM_QUERY_DOM, pm_query_करोm, DRM_RENDER_ALLOW),
	ETNA_IOCTL(PM_QUERY_SIG, pm_query_sig, DRM_RENDER_ALLOW),
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
	.mmap               = etnaviv_gem_mmap,
पूर्ण;

अटल स्थिर काष्ठा drm_driver etnaviv_drm_driver = अणु
	.driver_features    = DRIVER_GEM | DRIVER_RENDER,
	.खोलो               = etnaviv_खोलो,
	.postबंद           = etnaviv_postबंद,
	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = etnaviv_gem_prime_import_sg_table,
	.gem_prime_mmap     = etnaviv_gem_prime_mmap,
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init       = etnaviv_debugfs_init,
#पूर्ण_अगर
	.ioctls             = etnaviv_ioctls,
	.num_ioctls         = DRM_ETNAVIV_NUM_IOCTLS,
	.fops               = &fops,
	.name               = "etnaviv",
	.desc               = "etnaviv DRM",
	.date               = "20151214",
	.major              = 1,
	.minor              = 3,
पूर्ण;

/*
 * Platक्रमm driver:
 */
अटल पूर्णांक etnaviv_bind(काष्ठा device *dev)
अणु
	काष्ठा etnaviv_drm_निजी *priv;
	काष्ठा drm_device *drm;
	पूर्णांक ret;

	drm = drm_dev_alloc(&etnaviv_drm_driver, dev);
	अगर (IS_ERR(drm))
		वापस PTR_ERR(drm);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		dev_err(dev, "failed to allocate private data\n");
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण
	drm->dev_निजी = priv;

	dma_set_max_seg_size(dev, SZ_2G);

	mutex_init(&priv->gem_lock);
	INIT_LIST_HEAD(&priv->gem_list);
	priv->num_gpus = 0;
	priv->shm_gfp_mask = GFP_HIGHUSER | __GFP_RETRY_MAYFAIL | __GFP_NOWARN;

	priv->cmdbuf_suballoc = etnaviv_cmdbuf_suballoc_new(drm->dev);
	अगर (IS_ERR(priv->cmdbuf_suballoc)) अणु
		dev_err(drm->dev, "Failed to create cmdbuf suballocator\n");
		ret = PTR_ERR(priv->cmdbuf_suballoc);
		जाओ out_मुक्त_priv;
	पूर्ण

	dev_set_drvdata(dev, drm);

	ret = component_bind_all(dev, drm);
	अगर (ret < 0)
		जाओ out_destroy_suballoc;

	load_gpu(drm);

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret)
		जाओ out_unbind;

	वापस 0;

out_unbind:
	component_unbind_all(dev, drm);
out_destroy_suballoc:
	etnaviv_cmdbuf_suballoc_destroy(priv->cmdbuf_suballoc);
out_मुक्त_priv:
	kमुक्त(priv);
out_put:
	drm_dev_put(drm);

	वापस ret;
पूर्ण

अटल व्योम etnaviv_unbind(काष्ठा device *dev)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(dev);
	काष्ठा etnaviv_drm_निजी *priv = drm->dev_निजी;

	drm_dev_unरेजिस्टर(drm);

	component_unbind_all(dev, drm);

	etnaviv_cmdbuf_suballoc_destroy(priv->cmdbuf_suballoc);

	drm->dev_निजी = शून्य;
	kमुक्त(priv);

	drm_dev_put(drm);
पूर्ण

अटल स्थिर काष्ठा component_master_ops etnaviv_master_ops = अणु
	.bind = etnaviv_bind,
	.unbind = etnaviv_unbind,
पूर्ण;

अटल पूर्णांक compare_of(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device_node *np = data;

	वापस dev->of_node == np;
पूर्ण

अटल पूर्णांक compare_str(काष्ठा device *dev, व्योम *data)
अणु
	वापस !म_भेद(dev_name(dev), data);
पूर्ण

अटल पूर्णांक etnaviv_pdev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा component_match *match = शून्य;

	अगर (!dev->platक्रमm_data) अणु
		काष्ठा device_node *core_node;

		क्रम_each_compatible_node(core_node, शून्य, "vivante,gc") अणु
			अगर (!of_device_is_available(core_node))
				जारी;

			drm_of_component_match_add(&pdev->dev, &match,
						   compare_of, core_node);
		पूर्ण
	पूर्ण अन्यथा अणु
		अक्षर **names = dev->platक्रमm_data;
		अचिन्हित i;

		क्रम (i = 0; names[i]; i++)
			component_match_add(dev, &match, compare_str, names[i]);
	पूर्ण

	वापस component_master_add_with_match(dev, &etnaviv_master_ops, match);
पूर्ण

अटल पूर्णांक etnaviv_pdev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_master_del(&pdev->dev, &etnaviv_master_ops);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver etnaviv_platक्रमm_driver = अणु
	.probe      = etnaviv_pdev_probe,
	.हटाओ     = etnaviv_pdev_हटाओ,
	.driver     = अणु
		.name   = "etnaviv",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *etnaviv_drm;

अटल पूर्णांक __init etnaviv_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;
	काष्ठा device_node *np;

	etnaviv_validate_init();

	ret = platक्रमm_driver_रेजिस्टर(&etnaviv_gpu_driver);
	अगर (ret != 0)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&etnaviv_platक्रमm_driver);
	अगर (ret != 0)
		जाओ unरेजिस्टर_gpu_driver;

	/*
	 * If the DT contains at least one available GPU device, instantiate
	 * the DRM platक्रमm device.
	 */
	क्रम_each_compatible_node(np, शून्य, "vivante,gc") अणु
		अगर (!of_device_is_available(np))
			जारी;

		pdev = platक्रमm_device_alloc("etnaviv", -1);
		अगर (!pdev) अणु
			ret = -ENOMEM;
			of_node_put(np);
			जाओ unरेजिस्टर_platक्रमm_driver;
		पूर्ण
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(40);
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;

		/*
		 * Apply the same DMA configuration to the भव etnaviv
		 * device as the GPU we found. This assumes that all Vivante
		 * GPUs in the प्रणाली share the same DMA स्थिरraपूर्णांकs.
		 */
		of_dma_configure(&pdev->dev, np, true);

		ret = platक्रमm_device_add(pdev);
		अगर (ret) अणु
			platक्रमm_device_put(pdev);
			of_node_put(np);
			जाओ unरेजिस्टर_platक्रमm_driver;
		पूर्ण

		etnaviv_drm = pdev;
		of_node_put(np);
		अवरोध;
	पूर्ण

	वापस 0;

unरेजिस्टर_platक्रमm_driver:
	platक्रमm_driver_unरेजिस्टर(&etnaviv_platक्रमm_driver);
unरेजिस्टर_gpu_driver:
	platक्रमm_driver_unरेजिस्टर(&etnaviv_gpu_driver);
	वापस ret;
पूर्ण
module_init(etnaviv_init);

अटल व्योम __निकास etnaviv_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(etnaviv_drm);
	platक्रमm_driver_unरेजिस्टर(&etnaviv_platक्रमm_driver);
	platक्रमm_driver_unरेजिस्टर(&etnaviv_gpu_driver);
पूर्ण
module_निकास(etnaviv_निकास);

MODULE_AUTHOR("Christian Gmeiner <christian.gmeiner@gmail.com>");
MODULE_AUTHOR("Russell King <rmk+kernel@armlinux.org.uk>");
MODULE_AUTHOR("Lucas Stach <l.stach@pengutronix.de>");
MODULE_DESCRIPTION("etnaviv DRM Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:etnaviv");
