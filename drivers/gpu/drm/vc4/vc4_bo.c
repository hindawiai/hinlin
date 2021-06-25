<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright तऊ 2015 Broadcom
 */

/**
 * DOC: VC4 GEM BO management support
 *
 * The VC4 GPU architecture (both scanout and rendering) has direct
 * access to प्रणाली memory with no MMU in between.  To support it, we
 * use the GEM CMA helper functions to allocate contiguous ranges of
 * physical memory क्रम our BOs.
 *
 * Since the CMA allocator is very slow, we keep a cache of recently
 * मुक्तd BOs around so that the kernel's allocation of objects क्रम 3D
 * rendering can वापस quickly.
 */

#समावेश <linux/dma-buf.h>

#समावेश "vc4_drv.h"
#समावेश "uapi/drm/vc4_drm.h"

अटल स्थिर काष्ठा drm_gem_object_funcs vc4_gem_object_funcs;

अटल स्थिर अक्षर * स्थिर bo_type_names[] = अणु
	"kernel",
	"V3D",
	"V3D shader",
	"dumb",
	"binner",
	"RCL",
	"BCL",
	"kernel BO cache",
पूर्ण;

अटल bool is_user_label(पूर्णांक label)
अणु
	वापस label >= VC4_BO_TYPE_COUNT;
पूर्ण

अटल व्योम vc4_bo_stats_prपूर्णांक(काष्ठा drm_prपूर्णांकer *p, काष्ठा vc4_dev *vc4)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vc4->num_labels; i++) अणु
		अगर (!vc4->bo_labels[i].num_allocated)
			जारी;

		drm_म_लिखो(p, "%30s: %6dkb BOs (%d)\n",
			   vc4->bo_labels[i].name,
			   vc4->bo_labels[i].size_allocated / 1024,
			   vc4->bo_labels[i].num_allocated);
	पूर्ण

	mutex_lock(&vc4->purgeable.lock);
	अगर (vc4->purgeable.num)
		drm_म_लिखो(p, "%30s: %6zdkb BOs (%d)\n", "userspace BO cache",
			   vc4->purgeable.size / 1024, vc4->purgeable.num);

	अगर (vc4->purgeable.purged_num)
		drm_म_लिखो(p, "%30s: %6zdkb BOs (%d)\n", "total purged BO",
			   vc4->purgeable.purged_size / 1024,
			   vc4->purgeable.purged_num);
	mutex_unlock(&vc4->purgeable.lock);
पूर्ण

अटल पूर्णांक vc4_bo_stats_debugfs(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	vc4_bo_stats_prपूर्णांक(&p, vc4);

	वापस 0;
पूर्ण

/* Takes ownership of *name and वापसs the appropriate slot क्रम it in
 * the bo_labels[] array, extending it as necessary.
 *
 * This is inefficient and could use a hash table instead of walking
 * an array and म_भेद()ing.  However, the assumption is that user
 * labeling will be infrequent (scanout buffers and other दीर्घ-lived
 * objects, or debug driver builds), so we can live with it क्रम now.
 */
अटल पूर्णांक vc4_get_user_label(काष्ठा vc4_dev *vc4, स्थिर अक्षर *name)
अणु
	पूर्णांक i;
	पूर्णांक मुक्त_slot = -1;

	क्रम (i = 0; i < vc4->num_labels; i++) अणु
		अगर (!vc4->bo_labels[i].name) अणु
			मुक्त_slot = i;
		पूर्ण अन्यथा अगर (म_भेद(vc4->bo_labels[i].name, name) == 0) अणु
			kमुक्त(name);
			वापस i;
		पूर्ण
	पूर्ण

	अगर (मुक्त_slot != -1) अणु
		WARN_ON(vc4->bo_labels[मुक्त_slot].num_allocated != 0);
		vc4->bo_labels[मुक्त_slot].name = name;
		वापस मुक्त_slot;
	पूर्ण अन्यथा अणु
		u32 new_label_count = vc4->num_labels + 1;
		काष्ठा vc4_label *new_labels =
			kपुनः_स्मृति(vc4->bo_labels,
				 new_label_count * माप(*new_labels),
				 GFP_KERNEL);

		अगर (!new_labels) अणु
			kमुक्त(name);
			वापस -1;
		पूर्ण

		मुक्त_slot = vc4->num_labels;
		vc4->bo_labels = new_labels;
		vc4->num_labels = new_label_count;

		vc4->bo_labels[मुक्त_slot].name = name;
		vc4->bo_labels[मुक्त_slot].num_allocated = 0;
		vc4->bo_labels[मुक्त_slot].size_allocated = 0;

		वापस मुक्त_slot;
	पूर्ण
पूर्ण

अटल व्योम vc4_bo_set_label(काष्ठा drm_gem_object *gem_obj, पूर्णांक label)
अणु
	काष्ठा vc4_bo *bo = to_vc4_bo(gem_obj);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(gem_obj->dev);

	lockdep_निश्चित_held(&vc4->bo_lock);

	अगर (label != -1) अणु
		vc4->bo_labels[label].num_allocated++;
		vc4->bo_labels[label].size_allocated += gem_obj->size;
	पूर्ण

	vc4->bo_labels[bo->label].num_allocated--;
	vc4->bo_labels[bo->label].size_allocated -= gem_obj->size;

	अगर (vc4->bo_labels[bo->label].num_allocated == 0 &&
	    is_user_label(bo->label)) अणु
		/* Free user BO label slots on last unreference.
		 * Slots are just where we track the stats क्रम a given
		 * name, and once a name is unused we can reuse that
		 * slot.
		 */
		kमुक्त(vc4->bo_labels[bo->label].name);
		vc4->bo_labels[bo->label].name = शून्य;
	पूर्ण

	bo->label = label;
पूर्ण

अटल uपूर्णांक32_t bo_page_index(माप_प्रकार size)
अणु
	वापस (size / PAGE_SIZE) - 1;
पूर्ण

अटल व्योम vc4_bo_destroy(काष्ठा vc4_bo *bo)
अणु
	काष्ठा drm_gem_object *obj = &bo->base.base;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(obj->dev);

	lockdep_निश्चित_held(&vc4->bo_lock);

	vc4_bo_set_label(obj, -1);

	अगर (bo->validated_shader) अणु
		kमुक्त(bo->validated_shader->unअगरorm_addr_offsets);
		kमुक्त(bo->validated_shader->texture_samples);
		kमुक्त(bo->validated_shader);
		bo->validated_shader = शून्य;
	पूर्ण

	drm_gem_cma_मुक्त_object(obj);
पूर्ण

अटल व्योम vc4_bo_हटाओ_from_cache(काष्ठा vc4_bo *bo)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	lockdep_निश्चित_held(&vc4->bo_lock);
	list_del(&bo->unref_head);
	list_del(&bo->size_head);
पूर्ण

अटल काष्ठा list_head *vc4_get_cache_list_क्रम_size(काष्ठा drm_device *dev,
						     माप_प्रकार size)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	uपूर्णांक32_t page_index = bo_page_index(size);

	अगर (vc4->bo_cache.size_list_size <= page_index) अणु
		uपूर्णांक32_t new_size = max(vc4->bo_cache.size_list_size * 2,
					page_index + 1);
		काष्ठा list_head *new_list;
		uपूर्णांक32_t i;

		new_list = kदो_स्मृति_array(new_size, माप(काष्ठा list_head),
					 GFP_KERNEL);
		अगर (!new_list)
			वापस शून्य;

		/* Rebase the old cached BO lists to their new list
		 * head locations.
		 */
		क्रम (i = 0; i < vc4->bo_cache.size_list_size; i++) अणु
			काष्ठा list_head *old_list =
				&vc4->bo_cache.size_list[i];

			अगर (list_empty(old_list))
				INIT_LIST_HEAD(&new_list[i]);
			अन्यथा
				list_replace(old_list, &new_list[i]);
		पूर्ण
		/* And initialize the bअक्रम new BO list heads. */
		क्रम (i = vc4->bo_cache.size_list_size; i < new_size; i++)
			INIT_LIST_HEAD(&new_list[i]);

		kमुक्त(vc4->bo_cache.size_list);
		vc4->bo_cache.size_list = new_list;
		vc4->bo_cache.size_list_size = new_size;
	पूर्ण

	वापस &vc4->bo_cache.size_list[page_index];
पूर्ण

अटल व्योम vc4_bo_cache_purge(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	mutex_lock(&vc4->bo_lock);
	जबतक (!list_empty(&vc4->bo_cache.समय_list)) अणु
		काष्ठा vc4_bo *bo = list_last_entry(&vc4->bo_cache.समय_list,
						    काष्ठा vc4_bo, unref_head);
		vc4_bo_हटाओ_from_cache(bo);
		vc4_bo_destroy(bo);
	पूर्ण
	mutex_unlock(&vc4->bo_lock);
पूर्ण

व्योम vc4_bo_add_to_purgeable_pool(काष्ठा vc4_bo *bo)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	mutex_lock(&vc4->purgeable.lock);
	list_add_tail(&bo->size_head, &vc4->purgeable.list);
	vc4->purgeable.num++;
	vc4->purgeable.size += bo->base.base.size;
	mutex_unlock(&vc4->purgeable.lock);
पूर्ण

अटल व्योम vc4_bo_हटाओ_from_purgeable_pool_locked(काष्ठा vc4_bo *bo)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	/* list_del_init() is used here because the caller might release
	 * the purgeable lock in order to acquire the madv one and update the
	 * madv status.
	 * During this लघु period of समय a user might decide to mark
	 * the BO as unpurgeable, and अगर bo->madv is set to
	 * VC4_MADV_DONTNEED it will try to हटाओ the BO from the
	 * purgeable list which will fail अगर the ->next/prev fields
	 * are set to LIST_POISON1/LIST_POISON2 (which is what
	 * list_del() करोes).
	 * Re-initializing the list element guarantees that list_del()
	 * will work correctly even अगर it's a NOP.
	 */
	list_del_init(&bo->size_head);
	vc4->purgeable.num--;
	vc4->purgeable.size -= bo->base.base.size;
पूर्ण

व्योम vc4_bo_हटाओ_from_purgeable_pool(काष्ठा vc4_bo *bo)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	mutex_lock(&vc4->purgeable.lock);
	vc4_bo_हटाओ_from_purgeable_pool_locked(bo);
	mutex_unlock(&vc4->purgeable.lock);
पूर्ण

अटल व्योम vc4_bo_purge(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा vc4_bo *bo = to_vc4_bo(obj);
	काष्ठा drm_device *dev = obj->dev;

	WARN_ON(!mutex_is_locked(&bo->madv_lock));
	WARN_ON(bo->madv != VC4_MADV_DONTNEED);

	drm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);

	dma_मुक्त_wc(dev->dev, obj->size, bo->base.vaddr, bo->base.paddr);
	bo->base.vaddr = शून्य;
	bo->madv = __VC4_MADV_PURGED;
पूर्ण

अटल व्योम vc4_bo_userspace_cache_purge(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	mutex_lock(&vc4->purgeable.lock);
	जबतक (!list_empty(&vc4->purgeable.list)) अणु
		काष्ठा vc4_bo *bo = list_first_entry(&vc4->purgeable.list,
						     काष्ठा vc4_bo, size_head);
		काष्ठा drm_gem_object *obj = &bo->base.base;
		माप_प्रकार purged_size = 0;

		vc4_bo_हटाओ_from_purgeable_pool_locked(bo);

		/* Release the purgeable lock जबतक we're purging the BO so
		 * that other people can जारी inserting things in the
		 * purgeable pool without having to रुको क्रम all BOs to be
		 * purged.
		 */
		mutex_unlock(&vc4->purgeable.lock);
		mutex_lock(&bo->madv_lock);

		/* Since we released the purgeable pool lock beक्रमe acquiring
		 * the BO madv one, the user may have marked the BO as WILLNEED
		 * and re-used it in the meanसमय.
		 * Beक्रमe purging the BO we need to make sure
		 * - it is still marked as DONTNEED
		 * - it has not been re-inserted in the purgeable list
		 * - it is not used by HW blocks
		 * If one of these conditions is not met, just skip the entry.
		 */
		अगर (bo->madv == VC4_MADV_DONTNEED &&
		    list_empty(&bo->size_head) &&
		    !refcount_पढ़ो(&bo->usecnt)) अणु
			purged_size = bo->base.base.size;
			vc4_bo_purge(obj);
		पूर्ण
		mutex_unlock(&bo->madv_lock);
		mutex_lock(&vc4->purgeable.lock);

		अगर (purged_size) अणु
			vc4->purgeable.purged_size += purged_size;
			vc4->purgeable.purged_num++;
		पूर्ण
	पूर्ण
	mutex_unlock(&vc4->purgeable.lock);
पूर्ण

अटल काष्ठा vc4_bo *vc4_bo_get_from_cache(काष्ठा drm_device *dev,
					    uपूर्णांक32_t size,
					    क्रमागत vc4_kernel_bo_type type)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	uपूर्णांक32_t page_index = bo_page_index(size);
	काष्ठा vc4_bo *bo = शून्य;

	size = roundup(size, PAGE_SIZE);

	mutex_lock(&vc4->bo_lock);
	अगर (page_index >= vc4->bo_cache.size_list_size)
		जाओ out;

	अगर (list_empty(&vc4->bo_cache.size_list[page_index]))
		जाओ out;

	bo = list_first_entry(&vc4->bo_cache.size_list[page_index],
			      काष्ठा vc4_bo, size_head);
	vc4_bo_हटाओ_from_cache(bo);
	kref_init(&bo->base.base.refcount);

out:
	अगर (bo)
		vc4_bo_set_label(&bo->base.base, type);
	mutex_unlock(&vc4->bo_lock);
	वापस bo;
पूर्ण

/**
 * vc4_create_object - Implementation of driver->gem_create_object.
 * @dev: DRM device
 * @size: Size in bytes of the memory the object will reference
 *
 * This lets the CMA helpers allocate object काष्ठाs क्रम us, and keep
 * our BO stats correct.
 */
काष्ठा drm_gem_object *vc4_create_object(काष्ठा drm_device *dev, माप_प्रकार size)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_bo *bo;

	bo = kzalloc(माप(*bo), GFP_KERNEL);
	अगर (!bo)
		वापस ERR_PTR(-ENOMEM);

	bo->madv = VC4_MADV_WILLNEED;
	refcount_set(&bo->usecnt, 0);
	mutex_init(&bo->madv_lock);
	mutex_lock(&vc4->bo_lock);
	bo->label = VC4_BO_TYPE_KERNEL;
	vc4->bo_labels[VC4_BO_TYPE_KERNEL].num_allocated++;
	vc4->bo_labels[VC4_BO_TYPE_KERNEL].size_allocated += size;
	mutex_unlock(&vc4->bo_lock);

	bo->base.base.funcs = &vc4_gem_object_funcs;

	वापस &bo->base.base;
पूर्ण

काष्ठा vc4_bo *vc4_bo_create(काष्ठा drm_device *dev, माप_प्रकार unaligned_size,
			     bool allow_unzeroed, क्रमागत vc4_kernel_bo_type type)
अणु
	माप_प्रकार size = roundup(unaligned_size, PAGE_SIZE);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_gem_cma_object *cma_obj;
	काष्ठा vc4_bo *bo;

	अगर (size == 0)
		वापस ERR_PTR(-EINVAL);

	/* First, try to get a vc4_bo from the kernel BO cache. */
	bo = vc4_bo_get_from_cache(dev, size, type);
	अगर (bo) अणु
		अगर (!allow_unzeroed)
			स_रखो(bo->base.vaddr, 0, bo->base.base.size);
		वापस bo;
	पूर्ण

	cma_obj = drm_gem_cma_create(dev, size);
	अगर (IS_ERR(cma_obj)) अणु
		/*
		 * If we've run out of CMA memory, समाप्त the cache of
		 * CMA allocations we've got laying around and try again.
		 */
		vc4_bo_cache_purge(dev);
		cma_obj = drm_gem_cma_create(dev, size);
	पूर्ण

	अगर (IS_ERR(cma_obj)) अणु
		/*
		 * Still not enough CMA memory, purge the userspace BO
		 * cache and retry.
		 * This is sub-optimal since we purge the whole userspace
		 * BO cache which क्रमces user that want to re-use the BO to
		 * restore its initial content.
		 * Ideally, we should purge entries one by one and retry
		 * after each to see अगर CMA allocation succeeds. Or even
		 * better, try to find an entry with at least the same
		 * size.
		 */
		vc4_bo_userspace_cache_purge(dev);
		cma_obj = drm_gem_cma_create(dev, size);
	पूर्ण

	अगर (IS_ERR(cma_obj)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(vc4->base.dev);
		DRM_ERROR("Failed to allocate from CMA:\n");
		vc4_bo_stats_prपूर्णांक(&p, vc4);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	bo = to_vc4_bo(&cma_obj->base);

	/* By शेष, BOs करो not support the MADV ioctl. This will be enabled
	 * only on BOs that are exposed to userspace (V3D, V3D_SHADER and DUMB
	 * BOs).
	 */
	bo->madv = __VC4_MADV_NOTSUPP;

	mutex_lock(&vc4->bo_lock);
	vc4_bo_set_label(&cma_obj->base, type);
	mutex_unlock(&vc4->bo_lock);

	वापस bo;
पूर्ण

पूर्णांक vc4_dumb_create(काष्ठा drm_file *file_priv,
		    काष्ठा drm_device *dev,
		    काष्ठा drm_mode_create_dumb *args)
अणु
	पूर्णांक min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	काष्ठा vc4_bo *bo = शून्य;
	पूर्णांक ret;

	अगर (args->pitch < min_pitch)
		args->pitch = min_pitch;

	अगर (args->size < args->pitch * args->height)
		args->size = args->pitch * args->height;

	bo = vc4_bo_create(dev, args->size, false, VC4_BO_TYPE_DUMB);
	अगर (IS_ERR(bo))
		वापस PTR_ERR(bo);

	bo->madv = VC4_MADV_WILLNEED;

	ret = drm_gem_handle_create(file_priv, &bo->base.base, &args->handle);
	drm_gem_object_put(&bo->base.base);

	वापस ret;
पूर्ण

अटल व्योम vc4_bo_cache_मुक्त_old(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	अचिन्हित दीर्घ expire_समय = jअगरfies - msecs_to_jअगरfies(1000);

	lockdep_निश्चित_held(&vc4->bo_lock);

	जबतक (!list_empty(&vc4->bo_cache.समय_list)) अणु
		काष्ठा vc4_bo *bo = list_last_entry(&vc4->bo_cache.समय_list,
						    काष्ठा vc4_bo, unref_head);
		अगर (समय_beक्रमe(expire_समय, bo->मुक्त_समय)) अणु
			mod_समयr(&vc4->bo_cache.समय_प्रकारimer,
				  round_jअगरfies_up(jअगरfies +
						   msecs_to_jअगरfies(1000)));
			वापस;
		पूर्ण

		vc4_bo_हटाओ_from_cache(bo);
		vc4_bo_destroy(bo);
	पूर्ण
पूर्ण

/* Called on the last userspace/kernel unreference of the BO.  Returns
 * it to the BO cache अगर possible, otherwise मुक्तs it.
 */
अटल व्योम vc4_मुक्त_object(काष्ठा drm_gem_object *gem_bo)
अणु
	काष्ठा drm_device *dev = gem_bo->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_bo *bo = to_vc4_bo(gem_bo);
	काष्ठा list_head *cache_list;

	/* Remove the BO from the purgeable list. */
	mutex_lock(&bo->madv_lock);
	अगर (bo->madv == VC4_MADV_DONTNEED && !refcount_पढ़ो(&bo->usecnt))
		vc4_bo_हटाओ_from_purgeable_pool(bo);
	mutex_unlock(&bo->madv_lock);

	mutex_lock(&vc4->bo_lock);
	/* If the object references someone अन्यथा's memory, we can't cache it.
	 */
	अगर (gem_bo->import_attach) अणु
		vc4_bo_destroy(bo);
		जाओ out;
	पूर्ण

	/* Don't cache अगर it was खुलाly named. */
	अगर (gem_bo->name) अणु
		vc4_bo_destroy(bo);
		जाओ out;
	पूर्ण

	/* If this object was partially स्थिरructed but CMA allocation
	 * had failed, just मुक्त it. Can also happen when the BO has been
	 * purged.
	 */
	अगर (!bo->base.vaddr) अणु
		vc4_bo_destroy(bo);
		जाओ out;
	पूर्ण

	cache_list = vc4_get_cache_list_क्रम_size(dev, gem_bo->size);
	अगर (!cache_list) अणु
		vc4_bo_destroy(bo);
		जाओ out;
	पूर्ण

	अगर (bo->validated_shader) अणु
		kमुक्त(bo->validated_shader->unअगरorm_addr_offsets);
		kमुक्त(bo->validated_shader->texture_samples);
		kमुक्त(bo->validated_shader);
		bo->validated_shader = शून्य;
	पूर्ण

	/* Reset madv and usecnt beक्रमe adding the BO to the cache. */
	bo->madv = __VC4_MADV_NOTSUPP;
	refcount_set(&bo->usecnt, 0);

	bo->t_क्रमmat = false;
	bo->मुक्त_समय = jअगरfies;
	list_add(&bo->size_head, cache_list);
	list_add(&bo->unref_head, &vc4->bo_cache.समय_list);

	vc4_bo_set_label(&bo->base.base, VC4_BO_TYPE_KERNEL_CACHE);

	vc4_bo_cache_मुक्त_old(dev);

out:
	mutex_unlock(&vc4->bo_lock);
पूर्ण

अटल व्योम vc4_bo_cache_समय_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vc4_dev *vc4 =
		container_of(work, काष्ठा vc4_dev, bo_cache.समय_work);
	काष्ठा drm_device *dev = &vc4->base;

	mutex_lock(&vc4->bo_lock);
	vc4_bo_cache_मुक्त_old(dev);
	mutex_unlock(&vc4->bo_lock);
पूर्ण

पूर्णांक vc4_bo_inc_usecnt(काष्ठा vc4_bo *bo)
अणु
	पूर्णांक ret;

	/* Fast path: अगर the BO is alपढ़ोy retained by someone, no need to
	 * check the madv status.
	 */
	अगर (refcount_inc_not_zero(&bo->usecnt))
		वापस 0;

	mutex_lock(&bo->madv_lock);
	चयन (bo->madv) अणु
	हाल VC4_MADV_WILLNEED:
		अगर (!refcount_inc_not_zero(&bo->usecnt))
			refcount_set(&bo->usecnt, 1);
		ret = 0;
		अवरोध;
	हाल VC4_MADV_DONTNEED:
		/* We shouldn't use a BO marked as purgeable अगर at least
		 * someone अन्यथा retained its content by incrementing usecnt.
		 * Luckily the BO hasn't been purged yet, but something wrong
		 * is happening here. Just throw an error instead of
		 * authorizing this use हाल.
		 */
	हाल __VC4_MADV_PURGED:
		/* We can't use a purged BO. */
	शेष:
		/* Invalid madv value. */
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	mutex_unlock(&bo->madv_lock);

	वापस ret;
पूर्ण

व्योम vc4_bo_dec_usecnt(काष्ठा vc4_bo *bo)
अणु
	/* Fast path: अगर the BO is still retained by someone, no need to test
	 * the madv value.
	 */
	अगर (refcount_dec_not_one(&bo->usecnt))
		वापस;

	mutex_lock(&bo->madv_lock);
	अगर (refcount_dec_and_test(&bo->usecnt) &&
	    bo->madv == VC4_MADV_DONTNEED)
		vc4_bo_add_to_purgeable_pool(bo);
	mutex_unlock(&bo->madv_lock);
पूर्ण

अटल व्योम vc4_bo_cache_समय_प्रकारimer(काष्ठा समयr_list *t)
अणु
	काष्ठा vc4_dev *vc4 = from_समयr(vc4, t, bo_cache.समय_प्रकारimer);

	schedule_work(&vc4->bo_cache.समय_work);
पूर्ण

अटल काष्ठा dma_buf *vc4_prime_export(काष्ठा drm_gem_object *obj, पूर्णांक flags)
अणु
	काष्ठा vc4_bo *bo = to_vc4_bo(obj);
	काष्ठा dma_buf *dmabuf;
	पूर्णांक ret;

	अगर (bo->validated_shader) अणु
		DRM_DEBUG("Attempting to export shader BO\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Note: as soon as the BO is exported it becomes unpurgeable, because
	 * noone ever decrements the usecnt even अगर the reference held by the
	 * exported BO is released. This shouldn't be a problem since we don't
	 * expect exported BOs to be marked as purgeable.
	 */
	ret = vc4_bo_inc_usecnt(bo);
	अगर (ret) अणु
		DRM_ERROR("Failed to increment BO usecnt\n");
		वापस ERR_PTR(ret);
	पूर्ण

	dmabuf = drm_gem_prime_export(obj, flags);
	अगर (IS_ERR(dmabuf))
		vc4_bo_dec_usecnt(bo);

	वापस dmabuf;
पूर्ण

अटल vm_fault_t vc4_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;
	काष्ठा vc4_bo *bo = to_vc4_bo(obj);

	/* The only reason we would end up here is when user-space accesses
	 * BO's memory after it's been purged.
	 */
	mutex_lock(&bo->madv_lock);
	WARN_ON(bo->madv != __VC4_MADV_PURGED);
	mutex_unlock(&bo->madv_lock);

	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल पूर्णांक vc4_gem_object_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vc4_bo *bo = to_vc4_bo(obj);

	अगर (bo->validated_shader && (vma->vm_flags & VM_WRITE)) अणु
		DRM_DEBUG("mmaping of shader BOs for writing not allowed.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (bo->madv != VC4_MADV_WILLNEED) अणु
		DRM_DEBUG("mmaping of %s BO not allowed\n",
			  bo->madv == VC4_MADV_DONTNEED ?
			  "purgeable" : "purged");
		वापस -EINVAL;
	पूर्ण

	वापस drm_gem_cma_mmap(obj, vma);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vc4_vm_ops = अणु
	.fault = vc4_fault,
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

अटल स्थिर काष्ठा drm_gem_object_funcs vc4_gem_object_funcs = अणु
	.मुक्त = vc4_मुक्त_object,
	.export = vc4_prime_export,
	.get_sg_table = drm_gem_cma_get_sg_table,
	.vmap = drm_gem_cma_vmap,
	.mmap = vc4_gem_object_mmap,
	.vm_ops = &vc4_vm_ops,
पूर्ण;

अटल पूर्णांक vc4_grab_bin_bo(काष्ठा vc4_dev *vc4, काष्ठा vc4_file *vc4file)
अणु
	पूर्णांक ret;

	अगर (!vc4->v3d)
		वापस -ENODEV;

	अगर (vc4file->bin_bo_used)
		वापस 0;

	ret = vc4_v3d_bin_bo_get(vc4, &vc4file->bin_bo_used);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक vc4_create_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vc4_create_bo *args = data;
	काष्ठा vc4_file *vc4file = file_priv->driver_priv;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_bo *bo = शून्य;
	पूर्णांक ret;

	ret = vc4_grab_bin_bo(vc4, vc4file);
	अगर (ret)
		वापस ret;

	/*
	 * We can't allocate from the BO cache, because the BOs don't
	 * get zeroed, and that might leak data between users.
	 */
	bo = vc4_bo_create(dev, args->size, false, VC4_BO_TYPE_V3D);
	अगर (IS_ERR(bo))
		वापस PTR_ERR(bo);

	bo->madv = VC4_MADV_WILLNEED;

	ret = drm_gem_handle_create(file_priv, &bo->base.base, &args->handle);
	drm_gem_object_put(&bo->base.base);

	वापस ret;
पूर्ण

पूर्णांक vc4_mmap_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vc4_mmap_bo *args = data;
	काष्ठा drm_gem_object *gem_obj;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -EINVAL;
	पूर्ण

	/* The mmap offset was set up at BO allocation समय. */
	args->offset = drm_vma_node_offset_addr(&gem_obj->vma_node);

	drm_gem_object_put(gem_obj);
	वापस 0;
पूर्ण

पूर्णांक
vc4_create_shader_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vc4_create_shader_bo *args = data;
	काष्ठा vc4_file *vc4file = file_priv->driver_priv;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_bo *bo = शून्य;
	पूर्णांक ret;

	अगर (args->size == 0)
		वापस -EINVAL;

	अगर (args->size % माप(u64) != 0)
		वापस -EINVAL;

	अगर (args->flags != 0) अणु
		DRM_INFO("Unknown flags set: 0x%08x\n", args->flags);
		वापस -EINVAL;
	पूर्ण

	अगर (args->pad != 0) अणु
		DRM_INFO("Pad set: 0x%08x\n", args->pad);
		वापस -EINVAL;
	पूर्ण

	ret = vc4_grab_bin_bo(vc4, vc4file);
	अगर (ret)
		वापस ret;

	bo = vc4_bo_create(dev, args->size, true, VC4_BO_TYPE_V3D_SHADER);
	अगर (IS_ERR(bo))
		वापस PTR_ERR(bo);

	bo->madv = VC4_MADV_WILLNEED;

	अगर (copy_from_user(bo->base.vaddr,
			     (व्योम __user *)(uपूर्णांकptr_t)args->data,
			     args->size)) अणु
		ret = -EFAULT;
		जाओ fail;
	पूर्ण
	/* Clear the rest of the memory from allocating from the BO
	 * cache.
	 */
	स_रखो(bo->base.vaddr + args->size, 0,
	       bo->base.base.size - args->size);

	bo->validated_shader = vc4_validate_shader(&bo->base);
	अगर (!bo->validated_shader) अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	/* We have to create the handle after validation, to aव्योम
	 * races क्रम users to करो करोing things like mmap the shader BO.
	 */
	ret = drm_gem_handle_create(file_priv, &bo->base.base, &args->handle);

fail:
	drm_gem_object_put(&bo->base.base);

	वापस ret;
पूर्ण

/**
 * vc4_set_tiling_ioctl() - Sets the tiling modअगरier क्रम a BO.
 * @dev: DRM device
 * @data: ioctl argument
 * @file_priv: DRM file क्रम this fd
 *
 * The tiling state of the BO decides the शेष modअगरier of an fb अगर
 * no specअगरic modअगरier was set by userspace, and the वापस value of
 * vc4_get_tiling_ioctl() (so that userspace can treat a BO it
 * received from dmabuf as the same tiling क्रमmat as the producer
 * used).
 */
पूर्णांक vc4_set_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vc4_set_tiling *args = data;
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा vc4_bo *bo;
	bool t_क्रमmat;

	अगर (args->flags != 0)
		वापस -EINVAL;

	चयन (args->modअगरier) अणु
	हाल DRM_FORMAT_MOD_NONE:
		t_क्रमmat = false;
		अवरोध;
	हाल DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED:
		t_क्रमmat = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -ENOENT;
	पूर्ण
	bo = to_vc4_bo(gem_obj);
	bo->t_क्रमmat = t_क्रमmat;

	drm_gem_object_put(gem_obj);

	वापस 0;
पूर्ण

/**
 * vc4_get_tiling_ioctl() - Gets the tiling modअगरier क्रम a BO.
 * @dev: DRM device
 * @data: ioctl argument
 * @file_priv: DRM file क्रम this fd
 *
 * Returns the tiling modअगरier क्रम a BO as set by vc4_set_tiling_ioctl().
 */
पूर्णांक vc4_get_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vc4_get_tiling *args = data;
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा vc4_bo *bo;

	अगर (args->flags != 0 || args->modअगरier != 0)
		वापस -EINVAL;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -ENOENT;
	पूर्ण
	bo = to_vc4_bo(gem_obj);

	अगर (bo->t_क्रमmat)
		args->modअगरier = DRM_FORMAT_MOD_BROADCOM_VC4_T_TILED;
	अन्यथा
		args->modअगरier = DRM_FORMAT_MOD_NONE;

	drm_gem_object_put(gem_obj);

	वापस 0;
पूर्ण

अटल व्योम vc4_bo_cache_destroy(काष्ठा drm_device *dev, व्योम *unused);
पूर्णांक vc4_bo_cache_init(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	पूर्णांक i;

	/* Create the initial set of BO labels that the kernel will
	 * use.  This lets us aव्योम a bunch of string पुनः_स्मृतिation in
	 * the kernel's draw and BO allocation paths.
	 */
	vc4->bo_labels = kसुस्मृति(VC4_BO_TYPE_COUNT, माप(*vc4->bo_labels),
				 GFP_KERNEL);
	अगर (!vc4->bo_labels)
		वापस -ENOMEM;
	vc4->num_labels = VC4_BO_TYPE_COUNT;

	BUILD_BUG_ON(ARRAY_SIZE(bo_type_names) != VC4_BO_TYPE_COUNT);
	क्रम (i = 0; i < VC4_BO_TYPE_COUNT; i++)
		vc4->bo_labels[i].name = bo_type_names[i];

	mutex_init(&vc4->bo_lock);

	vc4_debugfs_add_file(dev, "bo_stats", vc4_bo_stats_debugfs, शून्य);

	INIT_LIST_HEAD(&vc4->bo_cache.समय_list);

	INIT_WORK(&vc4->bo_cache.समय_work, vc4_bo_cache_समय_work);
	समयr_setup(&vc4->bo_cache.समय_प्रकारimer, vc4_bo_cache_समय_प्रकारimer, 0);

	वापस drmm_add_action_or_reset(dev, vc4_bo_cache_destroy, शून्य);
पूर्ण

अटल व्योम vc4_bo_cache_destroy(काष्ठा drm_device *dev, व्योम *unused)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	पूर्णांक i;

	del_समयr(&vc4->bo_cache.समय_प्रकारimer);
	cancel_work_sync(&vc4->bo_cache.समय_work);

	vc4_bo_cache_purge(dev);

	क्रम (i = 0; i < vc4->num_labels; i++) अणु
		अगर (vc4->bo_labels[i].num_allocated) अणु
			DRM_ERROR("Destroying BO cache with %d %s "
				  "BOs still allocated\n",
				  vc4->bo_labels[i].num_allocated,
				  vc4->bo_labels[i].name);
		पूर्ण

		अगर (is_user_label(i))
			kमुक्त(vc4->bo_labels[i].name);
	पूर्ण
	kमुक्त(vc4->bo_labels);
पूर्ण

पूर्णांक vc4_label_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_vc4_label_bo *args = data;
	अक्षर *name;
	काष्ठा drm_gem_object *gem_obj;
	पूर्णांक ret = 0, label;

	अगर (!args->len)
		वापस -EINVAL;

	name = strndup_user(u64_to_user_ptr(args->name), args->len + 1);
	अगर (IS_ERR(name))
		वापस PTR_ERR(name);

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_ERROR("Failed to look up GEM BO %d\n", args->handle);
		kमुक्त(name);
		वापस -ENOENT;
	पूर्ण

	mutex_lock(&vc4->bo_lock);
	label = vc4_get_user_label(vc4, name);
	अगर (label != -1)
		vc4_bo_set_label(gem_obj, label);
	अन्यथा
		ret = -ENOMEM;
	mutex_unlock(&vc4->bo_lock);

	drm_gem_object_put(gem_obj);

	वापस ret;
पूर्ण
