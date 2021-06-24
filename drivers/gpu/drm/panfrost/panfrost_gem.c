<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-mapping.h>

#समावेश <drm/panfrost_drm.h>
#समावेश "panfrost_device.h"
#समावेश "panfrost_gem.h"
#समावेश "panfrost_mmu.h"

/* Called DRM core on the last userspace/kernel unreference of the
 * BO.
 */
अटल व्योम panfrost_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा panfrost_gem_object *bo = to_panfrost_bo(obj);
	काष्ठा panfrost_device *pfdev = obj->dev->dev_निजी;

	/*
	 * Make sure the BO is no दीर्घer inserted in the shrinker list beक्रमe
	 * taking care of the deकाष्ठाion itself. If we करोn't करो that we have a
	 * race condition between this function and what's करोne in
	 * panfrost_gem_shrinker_scan().
	 */
	mutex_lock(&pfdev->shrinker_lock);
	list_del_init(&bo->base.madv_list);
	mutex_unlock(&pfdev->shrinker_lock);

	/*
	 * If we still have mappings attached to the BO, there's a problem in
	 * our refcounting.
	 */
	WARN_ON_ONCE(!list_empty(&bo->mappings.list));

	अगर (bo->sgts) अणु
		पूर्णांक i;
		पूर्णांक n_sgt = bo->base.base.size / SZ_2M;

		क्रम (i = 0; i < n_sgt; i++) अणु
			अगर (bo->sgts[i].sgl) अणु
				dma_unmap_sgtable(pfdev->dev, &bo->sgts[i],
						  DMA_BIसूचीECTIONAL, 0);
				sg_मुक्त_table(&bo->sgts[i]);
			पूर्ण
		पूर्ण
		kvमुक्त(bo->sgts);
	पूर्ण

	drm_gem_shmem_मुक्त_object(obj);
पूर्ण

काष्ठा panfrost_gem_mapping *
panfrost_gem_mapping_get(काष्ठा panfrost_gem_object *bo,
			 काष्ठा panfrost_file_priv *priv)
अणु
	काष्ठा panfrost_gem_mapping *iter, *mapping = शून्य;

	mutex_lock(&bo->mappings.lock);
	list_क्रम_each_entry(iter, &bo->mappings.list, node) अणु
		अगर (iter->mmu == &priv->mmu) अणु
			kref_get(&iter->refcount);
			mapping = iter;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&bo->mappings.lock);

	वापस mapping;
पूर्ण

अटल व्योम
panfrost_gem_tearकरोwn_mapping(काष्ठा panfrost_gem_mapping *mapping)
अणु
	काष्ठा panfrost_file_priv *priv;

	अगर (mapping->active)
		panfrost_mmu_unmap(mapping);

	priv = container_of(mapping->mmu, काष्ठा panfrost_file_priv, mmu);
	spin_lock(&priv->mm_lock);
	अगर (drm_mm_node_allocated(&mapping->mmnode))
		drm_mm_हटाओ_node(&mapping->mmnode);
	spin_unlock(&priv->mm_lock);
पूर्ण

अटल व्योम panfrost_gem_mapping_release(काष्ठा kref *kref)
अणु
	काष्ठा panfrost_gem_mapping *mapping;

	mapping = container_of(kref, काष्ठा panfrost_gem_mapping, refcount);

	panfrost_gem_tearकरोwn_mapping(mapping);
	drm_gem_object_put(&mapping->obj->base.base);
	kमुक्त(mapping);
पूर्ण

व्योम panfrost_gem_mapping_put(काष्ठा panfrost_gem_mapping *mapping)
अणु
	अगर (!mapping)
		वापस;

	kref_put(&mapping->refcount, panfrost_gem_mapping_release);
पूर्ण

व्योम panfrost_gem_tearकरोwn_mappings_locked(काष्ठा panfrost_gem_object *bo)
अणु
	काष्ठा panfrost_gem_mapping *mapping;

	list_क्रम_each_entry(mapping, &bo->mappings.list, node)
		panfrost_gem_tearकरोwn_mapping(mapping);
पूर्ण

पूर्णांक panfrost_gem_खोलो(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file_priv)
अणु
	पूर्णांक ret;
	माप_प्रकार size = obj->size;
	u64 align;
	काष्ठा panfrost_gem_object *bo = to_panfrost_bo(obj);
	अचिन्हित दीर्घ color = bo->noexec ? PANFROST_BO_NOEXEC : 0;
	काष्ठा panfrost_file_priv *priv = file_priv->driver_priv;
	काष्ठा panfrost_gem_mapping *mapping;

	mapping = kzalloc(माप(*mapping), GFP_KERNEL);
	अगर (!mapping)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&mapping->node);
	kref_init(&mapping->refcount);
	drm_gem_object_get(obj);
	mapping->obj = bo;

	/*
	 * Executable buffers cannot cross a 16MB boundary as the program
	 * counter is 24-bits. We assume executable buffers will be less than
	 * 16MB and aligning executable buffers to their size will aव्योम
	 * crossing a 16MB boundary.
	 */
	अगर (!bo->noexec)
		align = size >> PAGE_SHIFT;
	अन्यथा
		align = size >= SZ_2M ? SZ_2M >> PAGE_SHIFT : 0;

	mapping->mmu = &priv->mmu;
	spin_lock(&priv->mm_lock);
	ret = drm_mm_insert_node_generic(&priv->mm, &mapping->mmnode,
					 size >> PAGE_SHIFT, align, color, 0);
	spin_unlock(&priv->mm_lock);
	अगर (ret)
		जाओ err;

	अगर (!bo->is_heap) अणु
		ret = panfrost_mmu_map(mapping);
		अगर (ret)
			जाओ err;
	पूर्ण

	mutex_lock(&bo->mappings.lock);
	WARN_ON(bo->base.madv != PANFROST_MADV_WILLNEED);
	list_add_tail(&mapping->node, &bo->mappings.list);
	mutex_unlock(&bo->mappings.lock);

err:
	अगर (ret)
		panfrost_gem_mapping_put(mapping);
	वापस ret;
पूर्ण

व्योम panfrost_gem_बंद(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file_priv)
अणु
	काष्ठा panfrost_file_priv *priv = file_priv->driver_priv;
	काष्ठा panfrost_gem_object *bo = to_panfrost_bo(obj);
	काष्ठा panfrost_gem_mapping *mapping = शून्य, *iter;

	mutex_lock(&bo->mappings.lock);
	list_क्रम_each_entry(iter, &bo->mappings.list, node) अणु
		अगर (iter->mmu == &priv->mmu) अणु
			mapping = iter;
			list_del(&iter->node);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&bo->mappings.lock);

	panfrost_gem_mapping_put(mapping);
पूर्ण

अटल पूर्णांक panfrost_gem_pin(काष्ठा drm_gem_object *obj)
अणु
	अगर (to_panfrost_bo(obj)->is_heap)
		वापस -EINVAL;

	वापस drm_gem_shmem_pin(obj);
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs panfrost_gem_funcs = अणु
	.मुक्त = panfrost_gem_मुक्त_object,
	.खोलो = panfrost_gem_खोलो,
	.बंद = panfrost_gem_बंद,
	.prपूर्णांक_info = drm_gem_shmem_prपूर्णांक_info,
	.pin = panfrost_gem_pin,
	.unpin = drm_gem_shmem_unpin,
	.get_sg_table = drm_gem_shmem_get_sg_table,
	.vmap = drm_gem_shmem_vmap,
	.vunmap = drm_gem_shmem_vunmap,
	.mmap = drm_gem_shmem_mmap,
पूर्ण;

/**
 * panfrost_gem_create_object - Implementation of driver->gem_create_object.
 * @dev: DRM device
 * @size: Size in bytes of the memory the object will reference
 *
 * This lets the GEM helpers allocate object काष्ठाs क्रम us, and keep
 * our BO stats correct.
 */
काष्ठा drm_gem_object *panfrost_gem_create_object(काष्ठा drm_device *dev, माप_प्रकार size)
अणु
	काष्ठा panfrost_device *pfdev = dev->dev_निजी;
	काष्ठा panfrost_gem_object *obj;

	obj = kzalloc(माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस शून्य;

	INIT_LIST_HEAD(&obj->mappings.list);
	mutex_init(&obj->mappings.lock);
	obj->base.base.funcs = &panfrost_gem_funcs;
	obj->base.map_wc = !pfdev->coherent;

	वापस &obj->base.base;
पूर्ण

काष्ठा panfrost_gem_object *
panfrost_gem_create_with_handle(काष्ठा drm_file *file_priv,
				काष्ठा drm_device *dev, माप_प्रकार size,
				u32 flags,
				uपूर्णांक32_t *handle)
अणु
	पूर्णांक ret;
	काष्ठा drm_gem_shmem_object *shmem;
	काष्ठा panfrost_gem_object *bo;

	/* Round up heap allocations to 2MB to keep fault handling simple */
	अगर (flags & PANFROST_BO_HEAP)
		size = roundup(size, SZ_2M);

	shmem = drm_gem_shmem_create(dev, size);
	अगर (IS_ERR(shmem))
		वापस ERR_CAST(shmem);

	bo = to_panfrost_bo(&shmem->base);
	bo->noexec = !!(flags & PANFROST_BO_NOEXEC);
	bo->is_heap = !!(flags & PANFROST_BO_HEAP);

	/*
	 * Allocate an id of idr table where the obj is रेजिस्टरed
	 * and handle has the id what user can see.
	 */
	ret = drm_gem_handle_create(file_priv, &shmem->base, handle);
	/* drop reference from allocate - handle holds it now. */
	drm_gem_object_put(&shmem->base);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस bo;
पूर्ण

काष्ठा drm_gem_object *
panfrost_gem_prime_import_sg_table(काष्ठा drm_device *dev,
				   काष्ठा dma_buf_attachment *attach,
				   काष्ठा sg_table *sgt)
अणु
	काष्ठा drm_gem_object *obj;
	काष्ठा panfrost_gem_object *bo;

	obj = drm_gem_shmem_prime_import_sg_table(dev, attach, sgt);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	bo = to_panfrost_bo(obj);
	bo->noexec = true;

	वापस obj;
पूर्ण
