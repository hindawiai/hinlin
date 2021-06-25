<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2018 Marty E. Plummer <hanetzer@starपंचांगail.com> */
/* Copyright 2019 Linaro, Ltd., Rob Herring <robh@kernel.org> */
/* Copyright 2019 Collabora ltd. */

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <drm/panfrost_drm.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_syncobj.h>
#समावेश <drm/drm_utils.h>

#समावेश "panfrost_device.h"
#समावेश "panfrost_gem.h"
#समावेश "panfrost_mmu.h"
#समावेश "panfrost_job.h"
#समावेश "panfrost_gpu.h"
#समावेश "panfrost_perfcnt.h"

अटल bool unstable_ioctls;
module_param_unsafe(unstable_ioctls, bool, 0600);

अटल पूर्णांक panfrost_ioctl_get_param(काष्ठा drm_device *ddev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_panfrost_get_param *param = data;
	काष्ठा panfrost_device *pfdev = ddev->dev_निजी;

	अगर (param->pad != 0)
		वापस -EINVAL;

#घोषणा PANFROST_FEATURE(name, member)			\
	हाल DRM_PANFROST_PARAM_ ## name:		\
		param->value = pfdev->features.member;	\
		अवरोध
#घोषणा PANFROST_FEATURE_ARRAY(name, member, max)			\
	हाल DRM_PANFROST_PARAM_ ## name ## 0 ...			\
		DRM_PANFROST_PARAM_ ## name ## max:			\
		param->value = pfdev->features.member[param->param -	\
			DRM_PANFROST_PARAM_ ## name ## 0];		\
		अवरोध

	चयन (param->param) अणु
		PANFROST_FEATURE(GPU_PROD_ID, id);
		PANFROST_FEATURE(GPU_REVISION, revision);
		PANFROST_FEATURE(SHADER_PRESENT, shader_present);
		PANFROST_FEATURE(TILER_PRESENT, tiler_present);
		PANFROST_FEATURE(L2_PRESENT, l2_present);
		PANFROST_FEATURE(STACK_PRESENT, stack_present);
		PANFROST_FEATURE(AS_PRESENT, as_present);
		PANFROST_FEATURE(JS_PRESENT, js_present);
		PANFROST_FEATURE(L2_FEATURES, l2_features);
		PANFROST_FEATURE(CORE_FEATURES, core_features);
		PANFROST_FEATURE(TILER_FEATURES, tiler_features);
		PANFROST_FEATURE(MEM_FEATURES, mem_features);
		PANFROST_FEATURE(MMU_FEATURES, mmu_features);
		PANFROST_FEATURE(THREAD_FEATURES, thपढ़ो_features);
		PANFROST_FEATURE(MAX_THREADS, max_thपढ़ोs);
		PANFROST_FEATURE(THREAD_MAX_WORKGROUP_SZ,
				thपढ़ो_max_workgroup_sz);
		PANFROST_FEATURE(THREAD_MAX_BARRIER_SZ,
				thपढ़ो_max_barrier_sz);
		PANFROST_FEATURE(COHERENCY_FEATURES, coherency_features);
		PANFROST_FEATURE_ARRAY(TEXTURE_FEATURES, texture_features, 3);
		PANFROST_FEATURE_ARRAY(JS_FEATURES, js_features, 15);
		PANFROST_FEATURE(NR_CORE_GROUPS, nr_core_groups);
		PANFROST_FEATURE(THREAD_TLS_ALLOC, thपढ़ो_tls_alloc);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक panfrost_ioctl_create_bo(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा panfrost_file_priv *priv = file->driver_priv;
	काष्ठा panfrost_gem_object *bo;
	काष्ठा drm_panfrost_create_bo *args = data;
	काष्ठा panfrost_gem_mapping *mapping;

	अगर (!args->size || args->pad ||
	    (args->flags & ~(PANFROST_BO_NOEXEC | PANFROST_BO_HEAP)))
		वापस -EINVAL;

	/* Heaps should never be executable */
	अगर ((args->flags & PANFROST_BO_HEAP) &&
	    !(args->flags & PANFROST_BO_NOEXEC))
		वापस -EINVAL;

	bo = panfrost_gem_create_with_handle(file, dev, args->size, args->flags,
					     &args->handle);
	अगर (IS_ERR(bo))
		वापस PTR_ERR(bo);

	mapping = panfrost_gem_mapping_get(bo, priv);
	अगर (!mapping) अणु
		drm_gem_object_put(&bo->base.base);
		वापस -EINVAL;
	पूर्ण

	args->offset = mapping->mmnode.start << PAGE_SHIFT;
	panfrost_gem_mapping_put(mapping);

	वापस 0;
पूर्ण

/**
 * panfrost_lookup_bos() - Sets up job->bo[] with the GEM objects
 * referenced by the job.
 * @dev: DRM device
 * @file_priv: DRM file क्रम this fd
 * @args: IOCTL args
 * @job: job being set up
 *
 * Resolve handles from userspace to BOs and attach them to job.
 *
 * Note that this function करोesn't need to unreference the BOs on
 * failure, because that will happen at panfrost_job_cleanup() समय.
 */
अटल पूर्णांक
panfrost_lookup_bos(काष्ठा drm_device *dev,
		  काष्ठा drm_file *file_priv,
		  काष्ठा drm_panfrost_submit *args,
		  काष्ठा panfrost_job *job)
अणु
	काष्ठा panfrost_file_priv *priv = file_priv->driver_priv;
	काष्ठा panfrost_gem_object *bo;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	job->bo_count = args->bo_handle_count;

	अगर (!job->bo_count)
		वापस 0;

	job->implicit_fences = kvदो_स्मृति_array(job->bo_count,
				  माप(काष्ठा dma_fence *),
				  GFP_KERNEL | __GFP_ZERO);
	अगर (!job->implicit_fences)
		वापस -ENOMEM;

	ret = drm_gem_objects_lookup(file_priv,
				     (व्योम __user *)(uपूर्णांकptr_t)args->bo_handles,
				     job->bo_count, &job->bos);
	अगर (ret)
		वापस ret;

	job->mappings = kvदो_स्मृति_array(job->bo_count,
				       माप(काष्ठा panfrost_gem_mapping *),
				       GFP_KERNEL | __GFP_ZERO);
	अगर (!job->mappings)
		वापस -ENOMEM;

	क्रम (i = 0; i < job->bo_count; i++) अणु
		काष्ठा panfrost_gem_mapping *mapping;

		bo = to_panfrost_bo(job->bos[i]);
		mapping = panfrost_gem_mapping_get(bo, priv);
		अगर (!mapping) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		atomic_inc(&bo->gpu_usecount);
		job->mappings[i] = mapping;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * panfrost_copy_in_sync() - Sets up job->in_fences[] with the sync objects
 * referenced by the job.
 * @dev: DRM device
 * @file_priv: DRM file क्रम this fd
 * @args: IOCTL args
 * @job: job being set up
 *
 * Resolve syncobjs from userspace to fences and attach them to job.
 *
 * Note that this function करोesn't need to unreference the fences on
 * failure, because that will happen at panfrost_job_cleanup() समय.
 */
अटल पूर्णांक
panfrost_copy_in_sync(काष्ठा drm_device *dev,
		  काष्ठा drm_file *file_priv,
		  काष्ठा drm_panfrost_submit *args,
		  काष्ठा panfrost_job *job)
अणु
	u32 *handles;
	पूर्णांक ret = 0;
	पूर्णांक i;

	job->in_fence_count = args->in_sync_count;

	अगर (!job->in_fence_count)
		वापस 0;

	job->in_fences = kvदो_स्मृति_array(job->in_fence_count,
					माप(काष्ठा dma_fence *),
					GFP_KERNEL | __GFP_ZERO);
	अगर (!job->in_fences) अणु
		DRM_DEBUG("Failed to allocate job in fences\n");
		वापस -ENOMEM;
	पूर्ण

	handles = kvदो_स्मृति_array(job->in_fence_count, माप(u32), GFP_KERNEL);
	अगर (!handles) अणु
		ret = -ENOMEM;
		DRM_DEBUG("Failed to allocate incoming syncobj handles\n");
		जाओ fail;
	पूर्ण

	अगर (copy_from_user(handles,
			   (व्योम __user *)(uपूर्णांकptr_t)args->in_syncs,
			   job->in_fence_count * माप(u32))) अणु
		ret = -EFAULT;
		DRM_DEBUG("Failed to copy in syncobj handles\n");
		जाओ fail;
	पूर्ण

	क्रम (i = 0; i < job->in_fence_count; i++) अणु
		ret = drm_syncobj_find_fence(file_priv, handles[i], 0, 0,
					     &job->in_fences[i]);
		अगर (ret == -EINVAL)
			जाओ fail;
	पूर्ण

fail:
	kvमुक्त(handles);
	वापस ret;
पूर्ण

अटल पूर्णांक panfrost_ioctl_submit(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा panfrost_device *pfdev = dev->dev_निजी;
	काष्ठा drm_panfrost_submit *args = data;
	काष्ठा drm_syncobj *sync_out = शून्य;
	काष्ठा panfrost_job *job;
	पूर्णांक ret = 0;

	अगर (!args->jc)
		वापस -EINVAL;

	अगर (args->requirements && args->requirements != PANFROST_JD_REQ_FS)
		वापस -EINVAL;

	अगर (args->out_sync > 0) अणु
		sync_out = drm_syncobj_find(file, args->out_sync);
		अगर (!sync_out)
			वापस -ENODEV;
	पूर्ण

	job = kzalloc(माप(*job), GFP_KERNEL);
	अगर (!job) अणु
		ret = -ENOMEM;
		जाओ fail_out_sync;
	पूर्ण

	kref_init(&job->refcount);

	job->pfdev = pfdev;
	job->jc = args->jc;
	job->requirements = args->requirements;
	job->flush_id = panfrost_gpu_get_latest_flush_id(pfdev);
	job->file_priv = file->driver_priv;

	ret = panfrost_copy_in_sync(dev, file, args, job);
	अगर (ret)
		जाओ fail_job;

	ret = panfrost_lookup_bos(dev, file, args, job);
	अगर (ret)
		जाओ fail_job;

	ret = panfrost_job_push(job);
	अगर (ret)
		जाओ fail_job;

	/* Update the वापस sync object क्रम the job */
	अगर (sync_out)
		drm_syncobj_replace_fence(sync_out, job->render_करोne_fence);

fail_job:
	panfrost_job_put(job);
fail_out_sync:
	अगर (sync_out)
		drm_syncobj_put(sync_out);

	वापस ret;
पूर्ण

अटल पूर्णांक
panfrost_ioctl_रुको_bo(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	दीर्घ ret;
	काष्ठा drm_panfrost_रुको_bo *args = data;
	काष्ठा drm_gem_object *gem_obj;
	अचिन्हित दीर्घ समयout = drm_समयout_असल_to_jअगरfies(args->समयout_ns);

	अगर (args->pad)
		वापस -EINVAL;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj)
		वापस -ENOENT;

	ret = dma_resv_रुको_समयout_rcu(gem_obj->resv, true,
						  true, समयout);
	अगर (!ret)
		ret = समयout ? -ETIMEDOUT : -EBUSY;

	drm_gem_object_put(gem_obj);

	वापस ret;
पूर्ण

अटल पूर्णांक panfrost_ioctl_mmap_bo(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_panfrost_mmap_bo *args = data;
	काष्ठा drm_gem_object *gem_obj;
	पूर्णांक ret;

	अगर (args->flags != 0) अणु
		DRM_INFO("unknown mmap_bo flags: %d\n", args->flags);
		वापस -EINVAL;
	पूर्ण

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -ENOENT;
	पूर्ण

	/* Don't allow mmapping of heap objects as pages are not pinned. */
	अगर (to_panfrost_bo(gem_obj)->is_heap) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = drm_gem_create_mmap_offset(gem_obj);
	अगर (ret == 0)
		args->offset = drm_vma_node_offset_addr(&gem_obj->vma_node);

out:
	drm_gem_object_put(gem_obj);
	वापस ret;
पूर्ण

अटल पूर्णांक panfrost_ioctl_get_bo_offset(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv)
अणु
	काष्ठा panfrost_file_priv *priv = file_priv->driver_priv;
	काष्ठा drm_panfrost_get_bo_offset *args = data;
	काष्ठा panfrost_gem_mapping *mapping;
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा panfrost_gem_object *bo;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -ENOENT;
	पूर्ण
	bo = to_panfrost_bo(gem_obj);

	mapping = panfrost_gem_mapping_get(bo, priv);
	drm_gem_object_put(gem_obj);

	अगर (!mapping)
		वापस -EINVAL;

	args->offset = mapping->mmnode.start << PAGE_SHIFT;
	panfrost_gem_mapping_put(mapping);
	वापस 0;
पूर्ण

अटल पूर्णांक panfrost_ioctl_madvise(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा panfrost_file_priv *priv = file_priv->driver_priv;
	काष्ठा drm_panfrost_madvise *args = data;
	काष्ठा panfrost_device *pfdev = dev->dev_निजी;
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा panfrost_gem_object *bo;
	पूर्णांक ret = 0;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -ENOENT;
	पूर्ण

	bo = to_panfrost_bo(gem_obj);

	mutex_lock(&pfdev->shrinker_lock);
	mutex_lock(&bo->mappings.lock);
	अगर (args->madv == PANFROST_MADV_DONTNEED) अणु
		काष्ठा panfrost_gem_mapping *first;

		first = list_first_entry(&bo->mappings.list,
					 काष्ठा panfrost_gem_mapping,
					 node);

		/*
		 * If we want to mark the BO purgeable, there must be only one
		 * user: the caller FD.
		 * We could करो something smarter and mark the BO purgeable only
		 * when all its users have marked it purgeable, but globally
		 * visible/shared BOs are likely to never be marked purgeable
		 * anyway, so let's not bother.
		 */
		अगर (!list_is_singular(&bo->mappings.list) ||
		    WARN_ON_ONCE(first->mmu != &priv->mmu)) अणु
			ret = -EINVAL;
			जाओ out_unlock_mappings;
		पूर्ण
	पूर्ण

	args->retained = drm_gem_shmem_madvise(gem_obj, args->madv);

	अगर (args->retained) अणु
		अगर (args->madv == PANFROST_MADV_DONTNEED)
			list_add_tail(&bo->base.madv_list,
				      &pfdev->shrinker_list);
		अन्यथा अगर (args->madv == PANFROST_MADV_WILLNEED)
			list_del_init(&bo->base.madv_list);
	पूर्ण

out_unlock_mappings:
	mutex_unlock(&bo->mappings.lock);
	mutex_unlock(&pfdev->shrinker_lock);

	drm_gem_object_put(gem_obj);
	वापस ret;
पूर्ण

पूर्णांक panfrost_unstable_ioctl_check(व्योम)
अणु
	अगर (!unstable_ioctls)
		वापस -ENOSYS;

	वापस 0;
पूर्ण

#घोषणा PFN_4G		(SZ_4G >> PAGE_SHIFT)
#घोषणा PFN_4G_MASK	(PFN_4G - 1)
#घोषणा PFN_16M		(SZ_16M >> PAGE_SHIFT)

अटल व्योम panfrost_drm_mm_color_adjust(स्थिर काष्ठा drm_mm_node *node,
					 अचिन्हित दीर्घ color,
					 u64 *start, u64 *end)
अणु
	/* Executable buffers can't start or end on a 4GB boundary */
	अगर (!(color & PANFROST_BO_NOEXEC)) अणु
		u64 next_seg;

		अगर ((*start & PFN_4G_MASK) == 0)
			(*start)++;

		अगर ((*end & PFN_4G_MASK) == 0)
			(*end)--;

		next_seg = ALIGN(*start, PFN_4G);
		अगर (next_seg - *start <= PFN_16M)
			*start = next_seg + 1;

		*end = min(*end, ALIGN(*start, PFN_4G) - 1);
	पूर्ण
पूर्ण

अटल पूर्णांक
panfrost_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	पूर्णांक ret;
	काष्ठा panfrost_device *pfdev = dev->dev_निजी;
	काष्ठा panfrost_file_priv *panfrost_priv;

	panfrost_priv = kzalloc(माप(*panfrost_priv), GFP_KERNEL);
	अगर (!panfrost_priv)
		वापस -ENOMEM;

	panfrost_priv->pfdev = pfdev;
	file->driver_priv = panfrost_priv;

	spin_lock_init(&panfrost_priv->mm_lock);

	/* 4G enough क्रम now. can be 48-bit */
	drm_mm_init(&panfrost_priv->mm, SZ_32M >> PAGE_SHIFT, (SZ_4G - SZ_32M) >> PAGE_SHIFT);
	panfrost_priv->mm.color_adjust = panfrost_drm_mm_color_adjust;

	ret = panfrost_mmu_pgtable_alloc(panfrost_priv);
	अगर (ret)
		जाओ err_pgtable;

	ret = panfrost_job_खोलो(panfrost_priv);
	अगर (ret)
		जाओ err_job;

	वापस 0;

err_job:
	panfrost_mmu_pgtable_मुक्त(panfrost_priv);
err_pgtable:
	drm_mm_takeकरोwn(&panfrost_priv->mm);
	kमुक्त(panfrost_priv);
	वापस ret;
पूर्ण

अटल व्योम
panfrost_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा panfrost_file_priv *panfrost_priv = file->driver_priv;

	panfrost_perfcnt_बंद(file);
	panfrost_job_बंद(panfrost_priv);

	panfrost_mmu_pgtable_मुक्त(panfrost_priv);
	drm_mm_takeकरोwn(&panfrost_priv->mm);
	kमुक्त(panfrost_priv);
पूर्ण

अटल स्थिर काष्ठा drm_ioctl_desc panfrost_drm_driver_ioctls[] = अणु
#घोषणा PANFROST_IOCTL(n, func, flags) \
	DRM_IOCTL_DEF_DRV(PANFROST_##n, panfrost_ioctl_##func, flags)

	PANFROST_IOCTL(SUBMIT,		submit,		DRM_RENDER_ALLOW),
	PANFROST_IOCTL(WAIT_BO,		रुको_bo,	DRM_RENDER_ALLOW),
	PANFROST_IOCTL(CREATE_BO,	create_bo,	DRM_RENDER_ALLOW),
	PANFROST_IOCTL(MMAP_BO,		mmap_bo,	DRM_RENDER_ALLOW),
	PANFROST_IOCTL(GET_PARAM,	get_param,	DRM_RENDER_ALLOW),
	PANFROST_IOCTL(GET_BO_OFFSET,	get_bo_offset,	DRM_RENDER_ALLOW),
	PANFROST_IOCTL(PERFCNT_ENABLE,	perfcnt_enable,	DRM_RENDER_ALLOW),
	PANFROST_IOCTL(PERFCNT_DUMP,	perfcnt_dump,	DRM_RENDER_ALLOW),
	PANFROST_IOCTL(MADVISE,		madvise,	DRM_RENDER_ALLOW),
पूर्ण;

DEFINE_DRM_GEM_FOPS(panfrost_drm_driver_fops);

/*
 * Panfrost driver version:
 * - 1.0 - initial पूर्णांकerface
 * - 1.1 - adds HEAP and NOEXEC flags क्रम CREATE_BO
 */
अटल स्थिर काष्ठा drm_driver panfrost_drm_driver = अणु
	.driver_features	= DRIVER_RENDER | DRIVER_GEM | DRIVER_SYNCOBJ,
	.खोलो			= panfrost_खोलो,
	.postबंद		= panfrost_postबंद,
	.ioctls			= panfrost_drm_driver_ioctls,
	.num_ioctls		= ARRAY_SIZE(panfrost_drm_driver_ioctls),
	.fops			= &panfrost_drm_driver_fops,
	.name			= "panfrost",
	.desc			= "panfrost DRM",
	.date			= "20180908",
	.major			= 1,
	.minor			= 1,

	.gem_create_object	= panfrost_gem_create_object,
	.prime_handle_to_fd	= drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle	= drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = panfrost_gem_prime_import_sg_table,
	.gem_prime_mmap		= drm_gem_prime_mmap,
पूर्ण;

अटल पूर्णांक panfrost_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panfrost_device *pfdev;
	काष्ठा drm_device *ddev;
	पूर्णांक err;

	pfdev = devm_kzalloc(&pdev->dev, माप(*pfdev), GFP_KERNEL);
	अगर (!pfdev)
		वापस -ENOMEM;

	pfdev->pdev = pdev;
	pfdev->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, pfdev);

	pfdev->comp = of_device_get_match_data(&pdev->dev);
	अगर (!pfdev->comp)
		वापस -ENODEV;

	pfdev->coherent = device_get_dma_attr(&pdev->dev) == DEV_DMA_COHERENT;

	/* Allocate and initialze the DRM device. */
	ddev = drm_dev_alloc(&panfrost_drm_driver, &pdev->dev);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	ddev->dev_निजी = pfdev;
	pfdev->ddev = ddev;

	mutex_init(&pfdev->shrinker_lock);
	INIT_LIST_HEAD(&pfdev->shrinker_list);

	err = panfrost_device_init(pfdev);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Fatal error during GPU init\n");
		जाओ err_out0;
	पूर्ण

	pm_runसमय_set_active(pfdev->dev);
	pm_runसमय_mark_last_busy(pfdev->dev);
	pm_runसमय_enable(pfdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(pfdev->dev, 50); /* ~3 frames */
	pm_runसमय_use_स्वतःsuspend(pfdev->dev);

	/*
	 * Register the DRM device with the core and the connectors with
	 * sysfs
	 */
	err = drm_dev_रेजिस्टर(ddev, 0);
	अगर (err < 0)
		जाओ err_out1;

	panfrost_gem_shrinker_init(ddev);

	वापस 0;

err_out1:
	pm_runसमय_disable(pfdev->dev);
	panfrost_device_fini(pfdev);
	pm_runसमय_set_suspended(pfdev->dev);
err_out0:
	drm_dev_put(ddev);
	वापस err;
पूर्ण

अटल पूर्णांक panfrost_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panfrost_device *pfdev = platक्रमm_get_drvdata(pdev);
	काष्ठा drm_device *ddev = pfdev->ddev;

	drm_dev_unरेजिस्टर(ddev);
	panfrost_gem_shrinker_cleanup(ddev);

	pm_runसमय_get_sync(pfdev->dev);
	pm_runसमय_disable(pfdev->dev);
	panfrost_device_fini(pfdev);
	pm_runसमय_set_suspended(pfdev->dev);

	drm_dev_put(ddev);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर शेष_supplies[] = अणु "mali" पूर्ण;
अटल स्थिर काष्ठा panfrost_compatible शेष_data = अणु
	.num_supplies = ARRAY_SIZE(शेष_supplies),
	.supply_names = शेष_supplies,
	.num_pm_करोमुख्यs = 1, /* optional */
	.pm_करोमुख्य_names = शून्य,
पूर्ण;

अटल स्थिर काष्ठा panfrost_compatible amlogic_data = अणु
	.num_supplies = ARRAY_SIZE(शेष_supplies),
	.supply_names = शेष_supplies,
	.venकरोr_quirk = panfrost_gpu_amlogic_quirk,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dt_match[] = अणु
	/* Set first to probe beक्रमe the generic compatibles */
	अणु .compatible = "amlogic,meson-gxm-mali",
	  .data = &amlogic_data, पूर्ण,
	अणु .compatible = "amlogic,meson-g12a-mali",
	  .data = &amlogic_data, पूर्ण,
	अणु .compatible = "arm,mali-t604", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-t624", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-t628", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-t720", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-t760", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-t820", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-t830", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-t860", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-t880", .data = &शेष_data, पूर्ण,
	अणु .compatible = "arm,mali-bifrost", .data = &शेष_data, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dt_match);

अटल स्थिर काष्ठा dev_pm_ops panfrost_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(panfrost_device_suspend, panfrost_device_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver panfrost_driver = अणु
	.probe		= panfrost_probe,
	.हटाओ		= panfrost_हटाओ,
	.driver		= अणु
		.name	= "panfrost",
		.pm	= &panfrost_pm_ops,
		.of_match_table = dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(panfrost_driver);

MODULE_AUTHOR("Panfrost Project Developers");
MODULE_DESCRIPTION("Panfrost DRM Driver");
MODULE_LICENSE("GPL v2");
