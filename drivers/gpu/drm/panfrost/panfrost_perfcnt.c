<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2019 Collabora Ltd */

#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/panfrost_drm.h>
#समावेश <linux/completion.h>
#समावेश <linux/dma-buf-map.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "panfrost_device.h"
#समावेश "panfrost_features.h"
#समावेश "panfrost_gem.h"
#समावेश "panfrost_issues.h"
#समावेश "panfrost_job.h"
#समावेश "panfrost_mmu.h"
#समावेश "panfrost_perfcnt.h"
#समावेश "panfrost_regs.h"

#घोषणा COUNTERS_PER_BLOCK		64
#घोषणा BYTES_PER_COUNTER		4
#घोषणा BLOCKS_PER_COREGROUP		8
#घोषणा V4_SHADERS_PER_COREGROUP	4

काष्ठा panfrost_perfcnt अणु
	काष्ठा panfrost_gem_mapping *mapping;
	माप_प्रकार bosize;
	व्योम *buf;
	काष्ठा panfrost_file_priv *user;
	काष्ठा mutex lock;
	काष्ठा completion dump_comp;
पूर्ण;

व्योम panfrost_perfcnt_clean_cache_करोne(काष्ठा panfrost_device *pfdev)
अणु
	complete(&pfdev->perfcnt->dump_comp);
पूर्ण

व्योम panfrost_perfcnt_sample_करोne(काष्ठा panfrost_device *pfdev)
अणु
	gpu_ग_लिखो(pfdev, GPU_CMD, GPU_CMD_CLEAN_CACHES);
पूर्ण

अटल पूर्णांक panfrost_perfcnt_dump_locked(काष्ठा panfrost_device *pfdev)
अणु
	u64 gpuva;
	पूर्णांक ret;

	reinit_completion(&pfdev->perfcnt->dump_comp);
	gpuva = pfdev->perfcnt->mapping->mmnode.start << PAGE_SHIFT;
	gpu_ग_लिखो(pfdev, GPU_PERFCNT_BASE_LO, gpuva);
	gpu_ग_लिखो(pfdev, GPU_PERFCNT_BASE_HI, gpuva >> 32);
	gpu_ग_लिखो(pfdev, GPU_INT_CLEAR,
		  GPU_IRQ_CLEAN_CACHES_COMPLETED |
		  GPU_IRQ_PERFCNT_SAMPLE_COMPLETED);
	gpu_ग_लिखो(pfdev, GPU_CMD, GPU_CMD_PERFCNT_SAMPLE);
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&pfdev->perfcnt->dump_comp,
							msecs_to_jअगरfies(1000));
	अगर (!ret)
		ret = -ETIMEDOUT;
	अन्यथा अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक panfrost_perfcnt_enable_locked(काष्ठा panfrost_device *pfdev,
					  काष्ठा drm_file *file_priv,
					  अचिन्हित पूर्णांक counterset)
अणु
	काष्ठा panfrost_file_priv *user = file_priv->driver_priv;
	काष्ठा panfrost_perfcnt *perfcnt = pfdev->perfcnt;
	काष्ठा dma_buf_map map;
	काष्ठा drm_gem_shmem_object *bo;
	u32 cfg, as;
	पूर्णांक ret;

	अगर (user == perfcnt->user)
		वापस 0;
	अन्यथा अगर (perfcnt->user)
		वापस -EBUSY;

	ret = pm_runसमय_get_sync(pfdev->dev);
	अगर (ret < 0)
		जाओ err_put_pm;

	bo = drm_gem_shmem_create(pfdev->ddev, perfcnt->bosize);
	अगर (IS_ERR(bo)) अणु
		ret = PTR_ERR(bo);
		जाओ err_put_pm;
	पूर्ण

	/* Map the perfcnt buf in the address space attached to file_priv. */
	ret = panfrost_gem_खोलो(&bo->base, file_priv);
	अगर (ret)
		जाओ err_put_bo;

	perfcnt->mapping = panfrost_gem_mapping_get(to_panfrost_bo(&bo->base),
						    user);
	अगर (!perfcnt->mapping) अणु
		ret = -EINVAL;
		जाओ err_बंद_bo;
	पूर्ण

	ret = drm_gem_shmem_vmap(&bo->base, &map);
	अगर (ret)
		जाओ err_put_mapping;
	perfcnt->buf = map.vaddr;

	/*
	 * Invalidate the cache and clear the counters to start from a fresh
	 * state.
	 */
	reinit_completion(&pfdev->perfcnt->dump_comp);
	gpu_ग_लिखो(pfdev, GPU_INT_CLEAR,
		  GPU_IRQ_CLEAN_CACHES_COMPLETED |
		  GPU_IRQ_PERFCNT_SAMPLE_COMPLETED);
	gpu_ग_लिखो(pfdev, GPU_CMD, GPU_CMD_PERFCNT_CLEAR);
	gpu_ग_लिखो(pfdev, GPU_CMD, GPU_CMD_CLEAN_INV_CACHES);
	ret = रुको_क्रम_completion_समयout(&pfdev->perfcnt->dump_comp,
					  msecs_to_jअगरfies(1000));
	अगर (!ret) अणु
		ret = -ETIMEDOUT;
		जाओ err_vunmap;
	पूर्ण

	perfcnt->user = user;

	as = panfrost_mmu_as_get(pfdev, perfcnt->mapping->mmu);
	cfg = GPU_PERFCNT_CFG_AS(as) |
	      GPU_PERFCNT_CFG_MODE(GPU_PERFCNT_CFG_MODE_MANUAL);

	/*
	 * Bअगरrost GPUs have 2 set of counters, but we're only पूर्णांकerested by
	 * the first one क्रम now.
	 */
	अगर (panfrost_model_is_bअगरrost(pfdev))
		cfg |= GPU_PERFCNT_CFG_SETSEL(counterset);

	gpu_ग_लिखो(pfdev, GPU_PRFCNT_JM_EN, 0xffffffff);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_SHADER_EN, 0xffffffff);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_MMU_L2_EN, 0xffffffff);

	/*
	 * Due to PRLAM-8186 we need to disable the Tiler beक्रमe we enable HW
	 * counters.
	 */
	अगर (panfrost_has_hw_issue(pfdev, HW_ISSUE_8186))
		gpu_ग_लिखो(pfdev, GPU_PRFCNT_TILER_EN, 0);
	अन्यथा
		gpu_ग_लिखो(pfdev, GPU_PRFCNT_TILER_EN, 0xffffffff);

	gpu_ग_लिखो(pfdev, GPU_PERFCNT_CFG, cfg);

	अगर (panfrost_has_hw_issue(pfdev, HW_ISSUE_8186))
		gpu_ग_लिखो(pfdev, GPU_PRFCNT_TILER_EN, 0xffffffff);

	/* The BO ref is retained by the mapping. */
	drm_gem_object_put(&bo->base);

	वापस 0;

err_vunmap:
	drm_gem_shmem_vunmap(&bo->base, &map);
err_put_mapping:
	panfrost_gem_mapping_put(perfcnt->mapping);
err_बंद_bo:
	panfrost_gem_बंद(&bo->base, file_priv);
err_put_bo:
	drm_gem_object_put(&bo->base);
err_put_pm:
	pm_runसमय_put(pfdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक panfrost_perfcnt_disable_locked(काष्ठा panfrost_device *pfdev,
					   काष्ठा drm_file *file_priv)
अणु
	काष्ठा panfrost_file_priv *user = file_priv->driver_priv;
	काष्ठा panfrost_perfcnt *perfcnt = pfdev->perfcnt;
	काष्ठा dma_buf_map map = DMA_BUF_MAP_INIT_VADDR(perfcnt->buf);

	अगर (user != perfcnt->user)
		वापस -EINVAL;

	gpu_ग_लिखो(pfdev, GPU_PRFCNT_JM_EN, 0x0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_SHADER_EN, 0x0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_MMU_L2_EN, 0x0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_TILER_EN, 0);
	gpu_ग_लिखो(pfdev, GPU_PERFCNT_CFG,
		  GPU_PERFCNT_CFG_MODE(GPU_PERFCNT_CFG_MODE_OFF));

	perfcnt->user = शून्य;
	drm_gem_shmem_vunmap(&perfcnt->mapping->obj->base.base, &map);
	perfcnt->buf = शून्य;
	panfrost_gem_बंद(&perfcnt->mapping->obj->base.base, file_priv);
	panfrost_mmu_as_put(pfdev, perfcnt->mapping->mmu);
	panfrost_gem_mapping_put(perfcnt->mapping);
	perfcnt->mapping = शून्य;
	pm_runसमय_mark_last_busy(pfdev->dev);
	pm_runसमय_put_स्वतःsuspend(pfdev->dev);

	वापस 0;
पूर्ण

पूर्णांक panfrost_ioctl_perfcnt_enable(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा panfrost_device *pfdev = dev->dev_निजी;
	काष्ठा panfrost_perfcnt *perfcnt = pfdev->perfcnt;
	काष्ठा drm_panfrost_perfcnt_enable *req = data;
	पूर्णांक ret;

	ret = panfrost_unstable_ioctl_check();
	अगर (ret)
		वापस ret;

	/* Only Bअगरrost GPUs have 2 set of counters. */
	अगर (req->counterset > (panfrost_model_is_bअगरrost(pfdev) ? 1 : 0))
		वापस -EINVAL;

	mutex_lock(&perfcnt->lock);
	अगर (req->enable)
		ret = panfrost_perfcnt_enable_locked(pfdev, file_priv,
						     req->counterset);
	अन्यथा
		ret = panfrost_perfcnt_disable_locked(pfdev, file_priv);
	mutex_unlock(&perfcnt->lock);

	वापस ret;
पूर्ण

पूर्णांक panfrost_ioctl_perfcnt_dump(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा panfrost_device *pfdev = dev->dev_निजी;
	काष्ठा panfrost_perfcnt *perfcnt = pfdev->perfcnt;
	काष्ठा drm_panfrost_perfcnt_dump *req = data;
	व्योम __user *user_ptr = (व्योम __user *)(uपूर्णांकptr_t)req->buf_ptr;
	पूर्णांक ret;

	ret = panfrost_unstable_ioctl_check();
	अगर (ret)
		वापस ret;

	mutex_lock(&perfcnt->lock);
	अगर (perfcnt->user != file_priv->driver_priv) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = panfrost_perfcnt_dump_locked(pfdev);
	अगर (ret)
		जाओ out;

	अगर (copy_to_user(user_ptr, perfcnt->buf, perfcnt->bosize))
		ret = -EFAULT;

out:
	mutex_unlock(&perfcnt->lock);

	वापस ret;
पूर्ण

व्योम panfrost_perfcnt_बंद(काष्ठा drm_file *file_priv)
अणु
	काष्ठा panfrost_file_priv *pfile = file_priv->driver_priv;
	काष्ठा panfrost_device *pfdev = pfile->pfdev;
	काष्ठा panfrost_perfcnt *perfcnt = pfdev->perfcnt;

	pm_runसमय_get_sync(pfdev->dev);
	mutex_lock(&perfcnt->lock);
	अगर (perfcnt->user == pfile)
		panfrost_perfcnt_disable_locked(pfdev, file_priv);
	mutex_unlock(&perfcnt->lock);
	pm_runसमय_mark_last_busy(pfdev->dev);
	pm_runसमय_put_स्वतःsuspend(pfdev->dev);
पूर्ण

पूर्णांक panfrost_perfcnt_init(काष्ठा panfrost_device *pfdev)
अणु
	काष्ठा panfrost_perfcnt *perfcnt;
	माप_प्रकार size;

	अगर (panfrost_has_hw_feature(pfdev, HW_FEATURE_V4)) अणु
		अचिन्हित पूर्णांक ncoregroups;

		ncoregroups = hweight64(pfdev->features.l2_present);
		size = ncoregroups * BLOCKS_PER_COREGROUP *
		       COUNTERS_PER_BLOCK * BYTES_PER_COUNTER;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक nl2c, ncores;

		/*
		 * TODO: define a macro to extract the number of l2 caches from
		 * mem_features.
		 */
		nl2c = ((pfdev->features.mem_features >> 8) & GENMASK(3, 0)) + 1;

		/*
		 * shader_present might be sparse, but the counters layout
		 * क्रमces to dump unused regions too, hence the fls64() call
		 * instead of hweight64().
		 */
		ncores = fls64(pfdev->features.shader_present);

		/*
		 * There's always one JM and one Tiler block, hence the '+ 2'
		 * here.
		 */
		size = (nl2c + ncores + 2) *
		       COUNTERS_PER_BLOCK * BYTES_PER_COUNTER;
	पूर्ण

	perfcnt = devm_kzalloc(pfdev->dev, माप(*perfcnt), GFP_KERNEL);
	अगर (!perfcnt)
		वापस -ENOMEM;

	perfcnt->bosize = size;

	/* Start with everything disabled. */
	gpu_ग_लिखो(pfdev, GPU_PERFCNT_CFG,
		  GPU_PERFCNT_CFG_MODE(GPU_PERFCNT_CFG_MODE_OFF));
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_JM_EN, 0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_SHADER_EN, 0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_MMU_L2_EN, 0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_TILER_EN, 0);

	init_completion(&perfcnt->dump_comp);
	mutex_init(&perfcnt->lock);
	pfdev->perfcnt = perfcnt;

	वापस 0;
पूर्ण

व्योम panfrost_perfcnt_fini(काष्ठा panfrost_device *pfdev)
अणु
	/* Disable everything beक्रमe leaving. */
	gpu_ग_लिखो(pfdev, GPU_PERFCNT_CFG,
		  GPU_PERFCNT_CFG_MODE(GPU_PERFCNT_CFG_MODE_OFF));
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_JM_EN, 0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_SHADER_EN, 0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_MMU_L2_EN, 0);
	gpu_ग_लिखो(pfdev, GPU_PRFCNT_TILER_EN, 0);
पूर्ण
