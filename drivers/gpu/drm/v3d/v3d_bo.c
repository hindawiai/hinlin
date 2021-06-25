<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2015-2018 Broadcom */

/**
 * DOC: V3D GEM BO management support
 *
 * Compared to VC4 (V3D 2.x), V3D 3.3 पूर्णांकroduces an MMU between the
 * GPU and the bus, allowing us to use shmem objects क्रम our storage
 * instead of CMA.
 *
 * Physically contiguous objects may still be imported to V3D, but the
 * driver करोesn't allocate physically contiguous objects on its own.
 * Display engines requiring physically contiguous allocations should
 * look पूर्णांकo Mesa's "renderonly" support (as used by the Mesa pl111
 * driver) क्रम an example of how to पूर्णांकegrate with V3D.
 *
 * Long term, we should support evicting pages from the MMU when under
 * memory pressure (thus the v3d_bo_get_pages() refcounting), but
 * that's not a high priority since our प्रणालीs tend to not have swap.
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/pfn_t.h>

#समावेश "v3d_drv.h"
#समावेश "uapi/drm/v3d_drm.h"

/* Called DRM core on the last userspace/kernel unreference of the
 * BO.
 */
व्योम v3d_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(obj->dev);
	काष्ठा v3d_bo *bo = to_v3d_bo(obj);

	v3d_mmu_हटाओ_ptes(bo);

	mutex_lock(&v3d->bo_lock);
	v3d->bo_stats.num_allocated--;
	v3d->bo_stats.pages_allocated -= obj->size >> PAGE_SHIFT;
	mutex_unlock(&v3d->bo_lock);

	spin_lock(&v3d->mm_lock);
	drm_mm_हटाओ_node(&bo->node);
	spin_unlock(&v3d->mm_lock);

	/* GPU execution may have dirtied any pages in the BO. */
	bo->base.pages_mark_dirty_on_put = true;

	drm_gem_shmem_मुक्त_object(obj);
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs v3d_gem_funcs = अणु
	.मुक्त = v3d_मुक्त_object,
	.prपूर्णांक_info = drm_gem_shmem_prपूर्णांक_info,
	.pin = drm_gem_shmem_pin,
	.unpin = drm_gem_shmem_unpin,
	.get_sg_table = drm_gem_shmem_get_sg_table,
	.vmap = drm_gem_shmem_vmap,
	.vunmap = drm_gem_shmem_vunmap,
	.mmap = drm_gem_shmem_mmap,
पूर्ण;

/* gem_create_object function क्रम allocating a BO काष्ठा and करोing
 * early setup.
 */
काष्ठा drm_gem_object *v3d_create_object(काष्ठा drm_device *dev, माप_प्रकार size)
अणु
	काष्ठा v3d_bo *bo;
	काष्ठा drm_gem_object *obj;

	अगर (size == 0)
		वापस शून्य;

	bo = kzalloc(माप(*bo), GFP_KERNEL);
	अगर (!bo)
		वापस शून्य;
	obj = &bo->base.base;

	obj->funcs = &v3d_gem_funcs;
	bo->base.map_wc = true;
	INIT_LIST_HEAD(&bo->unref_head);

	वापस &bo->base.base;
पूर्ण

अटल पूर्णांक
v3d_bo_create_finish(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(obj->dev);
	काष्ठा v3d_bo *bo = to_v3d_bo(obj);
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	/* So far we pin the BO in the MMU क्रम its lअगरeसमय, so use
	 * shmem's helper क्रम getting a lअगरeसमय sgt.
	 */
	sgt = drm_gem_shmem_get_pages_sgt(&bo->base.base);
	अगर (IS_ERR(sgt))
		वापस PTR_ERR(sgt);

	spin_lock(&v3d->mm_lock);
	/* Allocate the object's space in the GPU's page tables.
	 * Inserting PTEs will happen later, but the offset is क्रम the
	 * lअगरeसमय of the BO.
	 */
	ret = drm_mm_insert_node_generic(&v3d->mm, &bo->node,
					 obj->size >> PAGE_SHIFT,
					 GMP_GRANULARITY >> PAGE_SHIFT, 0, 0);
	spin_unlock(&v3d->mm_lock);
	अगर (ret)
		वापस ret;

	/* Track stats क्रम /debug/dri/n/bo_stats. */
	mutex_lock(&v3d->bo_lock);
	v3d->bo_stats.num_allocated++;
	v3d->bo_stats.pages_allocated += obj->size >> PAGE_SHIFT;
	mutex_unlock(&v3d->bo_lock);

	v3d_mmu_insert_ptes(bo);

	वापस 0;
पूर्ण

काष्ठा v3d_bo *v3d_bo_create(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
			     माप_प्रकार unaligned_size)
अणु
	काष्ठा drm_gem_shmem_object *shmem_obj;
	काष्ठा v3d_bo *bo;
	पूर्णांक ret;

	shmem_obj = drm_gem_shmem_create(dev, unaligned_size);
	अगर (IS_ERR(shmem_obj))
		वापस ERR_CAST(shmem_obj);
	bo = to_v3d_bo(&shmem_obj->base);

	ret = v3d_bo_create_finish(&shmem_obj->base);
	अगर (ret)
		जाओ मुक्त_obj;

	वापस bo;

मुक्त_obj:
	drm_gem_shmem_मुक्त_object(&shmem_obj->base);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा drm_gem_object *
v3d_prime_import_sg_table(काष्ठा drm_device *dev,
			  काष्ठा dma_buf_attachment *attach,
			  काष्ठा sg_table *sgt)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	obj = drm_gem_shmem_prime_import_sg_table(dev, attach, sgt);
	अगर (IS_ERR(obj))
		वापस obj;

	ret = v3d_bo_create_finish(obj);
	अगर (ret) अणु
		drm_gem_shmem_मुक्त_object(obj);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस obj;
पूर्ण

पूर्णांक v3d_create_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_v3d_create_bo *args = data;
	काष्ठा v3d_bo *bo = शून्य;
	पूर्णांक ret;

	अगर (args->flags != 0) अणु
		DRM_INFO("unknown create_bo flags: %d\n", args->flags);
		वापस -EINVAL;
	पूर्ण

	bo = v3d_bo_create(dev, file_priv, PAGE_ALIGN(args->size));
	अगर (IS_ERR(bo))
		वापस PTR_ERR(bo);

	args->offset = bo->node.start << PAGE_SHIFT;

	ret = drm_gem_handle_create(file_priv, &bo->base.base, &args->handle);
	drm_gem_object_put(&bo->base.base);

	वापस ret;
पूर्ण

पूर्णांक v3d_mmap_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_v3d_mmap_bo *args = data;
	काष्ठा drm_gem_object *gem_obj;

	अगर (args->flags != 0) अणु
		DRM_INFO("unknown mmap_bo flags: %d\n", args->flags);
		वापस -EINVAL;
	पूर्ण

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -ENOENT;
	पूर्ण

	args->offset = drm_vma_node_offset_addr(&gem_obj->vma_node);
	drm_gem_object_put(gem_obj);

	वापस 0;
पूर्ण

पूर्णांक v3d_get_bo_offset_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_v3d_get_bo_offset *args = data;
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा v3d_bo *bo;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -ENOENT;
	पूर्ण
	bo = to_v3d_bo(gem_obj);

	args->offset = bo->node.start << PAGE_SHIFT;

	drm_gem_object_put(gem_obj);
	वापस 0;
पूर्ण
