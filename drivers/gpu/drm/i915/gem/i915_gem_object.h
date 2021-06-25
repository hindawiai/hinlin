<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __I915_GEM_OBJECT_H__
#घोषणा __I915_GEM_OBJECT_H__

#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_device.h>

#समावेश "display/intel_frontbuffer.h"
#समावेश "i915_gem_object_types.h"
#समावेश "i915_gem_gtt.h"
#समावेश "i915_vma_types.h"

/*
 * XXX: There is a prevalence of the assumption that we fit the
 * object's page count inside a 32bit _signed_ variable. Let's करोcument
 * this and catch अगर we ever need to fix it. In the meanसमय, अगर you करो
 * spot such a local variable, please consider fixing!
 *
 * Aside from our own locals (क्रम which we have no excuse!):
 * - sg_table embeds अचिन्हित पूर्णांक क्रम num_pages
 * - get_user_pages*() mixed पूर्णांकs with दीर्घs
 */
#घोषणा GEM_CHECK_SIZE_OVERFLOW(sz) \
	GEM_WARN_ON((sz) >> PAGE_SHIFT > पूर्णांक_उच्च)

अटल अंतरभूत bool i915_gem_object_size_2big(u64 size)
अणु
	काष्ठा drm_i915_gem_object *obj;

	अगर (GEM_CHECK_SIZE_OVERFLOW(size))
		वापस true;

	अगर (overflows_type(size, obj->base.size))
		वापस true;

	वापस false;
पूर्ण

व्योम i915_gem_init__objects(काष्ठा drm_i915_निजी *i915);

काष्ठा drm_i915_gem_object *i915_gem_object_alloc(व्योम);
व्योम i915_gem_object_मुक्त(काष्ठा drm_i915_gem_object *obj);

व्योम i915_gem_object_init(काष्ठा drm_i915_gem_object *obj,
			  स्थिर काष्ठा drm_i915_gem_object_ops *ops,
			  काष्ठा lock_class_key *key,
			  अचिन्हित alloc_flags);
काष्ठा drm_i915_gem_object *
i915_gem_object_create_shmem(काष्ठा drm_i915_निजी *i915,
			     resource_माप_प्रकार size);
काष्ठा drm_i915_gem_object *
i915_gem_object_create_shmem_from_data(काष्ठा drm_i915_निजी *i915,
				       स्थिर व्योम *data, resource_माप_प्रकार size);

बाह्य स्थिर काष्ठा drm_i915_gem_object_ops i915_gem_shmem_ops;

व्योम __i915_gem_object_release_shmem(काष्ठा drm_i915_gem_object *obj,
				     काष्ठा sg_table *pages,
				     bool needs_clflush);

पूर्णांक i915_gem_object_pग_लिखो_phys(काष्ठा drm_i915_gem_object *obj,
				स्थिर काष्ठा drm_i915_gem_pग_लिखो *args);
पूर्णांक i915_gem_object_pपढ़ो_phys(काष्ठा drm_i915_gem_object *obj,
			       स्थिर काष्ठा drm_i915_gem_pपढ़ो *args);

पूर्णांक i915_gem_object_attach_phys(काष्ठा drm_i915_gem_object *obj, पूर्णांक align);
व्योम i915_gem_object_put_pages_shmem(काष्ठा drm_i915_gem_object *obj,
				     काष्ठा sg_table *pages);
व्योम i915_gem_object_put_pages_phys(काष्ठा drm_i915_gem_object *obj,
				    काष्ठा sg_table *pages);

व्योम i915_gem_flush_मुक्त_objects(काष्ठा drm_i915_निजी *i915);

काष्ठा sg_table *
__i915_gem_object_unset_pages(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_truncate(काष्ठा drm_i915_gem_object *obj);

/**
 * i915_gem_object_lookup_rcu - look up a temporary GEM object from its handle
 * @filp: DRM file निजी date
 * @handle: userspace handle
 *
 * Returns:
 *
 * A poपूर्णांकer to the object named by the handle अगर such exists on @filp, शून्य
 * otherwise. This object is only valid whilst under the RCU पढ़ो lock, and
 * note carefully the object may be in the process of being destroyed.
 */
अटल अंतरभूत काष्ठा drm_i915_gem_object *
i915_gem_object_lookup_rcu(काष्ठा drm_file *file, u32 handle)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	WARN_ON(debug_locks && !lock_is_held(&rcu_lock_map));
#पूर्ण_अगर
	वापस idr_find(&file->object_idr, handle);
पूर्ण

अटल अंतरभूत काष्ठा drm_i915_gem_object *
i915_gem_object_get_rcu(काष्ठा drm_i915_gem_object *obj)
अणु
	अगर (obj && !kref_get_unless_zero(&obj->base.refcount))
		obj = शून्य;

	वापस obj;
पूर्ण

अटल अंतरभूत काष्ठा drm_i915_gem_object *
i915_gem_object_lookup(काष्ठा drm_file *file, u32 handle)
अणु
	काष्ठा drm_i915_gem_object *obj;

	rcu_पढ़ो_lock();
	obj = i915_gem_object_lookup_rcu(file, handle);
	obj = i915_gem_object_get_rcu(obj);
	rcu_पढ़ो_unlock();

	वापस obj;
पूर्ण

__deprecated
काष्ठा drm_gem_object *
drm_gem_object_lookup(काष्ठा drm_file *file, u32 handle);

__attribute__((nonnull))
अटल अंतरभूत काष्ठा drm_i915_gem_object *
i915_gem_object_get(काष्ठा drm_i915_gem_object *obj)
अणु
	drm_gem_object_get(&obj->base);
	वापस obj;
पूर्ण

__attribute__((nonnull))
अटल अंतरभूत व्योम
i915_gem_object_put(काष्ठा drm_i915_gem_object *obj)
अणु
	__drm_gem_object_put(&obj->base);
पूर्ण

#घोषणा निश्चित_object_held(obj) dma_resv_निश्चित_held((obj)->base.resv)

/*
 * If more than one potential simultaneous locker, निश्चित held.
 */
अटल अंतरभूत व्योम निश्चित_object_held_shared(काष्ठा drm_i915_gem_object *obj)
अणु
	/*
	 * Note mm list lookup is रक्षित by
	 * kref_get_unless_zero().
	 */
	अगर (IS_ENABLED(CONFIG_LOCKDEP) &&
	    kref_पढ़ो(&obj->base.refcount) > 0)
		निश्चित_object_held(obj);
पूर्ण

अटल अंतरभूत पूर्णांक __i915_gem_object_lock(काष्ठा drm_i915_gem_object *obj,
					 काष्ठा i915_gem_ww_ctx *ww,
					 bool पूर्णांकr)
अणु
	पूर्णांक ret;

	अगर (पूर्णांकr)
		ret = dma_resv_lock_पूर्णांकerruptible(obj->base.resv, ww ? &ww->ctx : शून्य);
	अन्यथा
		ret = dma_resv_lock(obj->base.resv, ww ? &ww->ctx : शून्य);

	अगर (!ret && ww)
		list_add_tail(&obj->obj_link, &ww->obj_list);
	अगर (ret == -EALREADY)
		ret = 0;

	अगर (ret == -EDEADLK)
		ww->contended = obj;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक i915_gem_object_lock(काष्ठा drm_i915_gem_object *obj,
				       काष्ठा i915_gem_ww_ctx *ww)
अणु
	वापस __i915_gem_object_lock(obj, ww, ww && ww->पूर्णांकr);
पूर्ण

अटल अंतरभूत पूर्णांक i915_gem_object_lock_पूर्णांकerruptible(काष्ठा drm_i915_gem_object *obj,
						     काष्ठा i915_gem_ww_ctx *ww)
अणु
	WARN_ON(ww && !ww->पूर्णांकr);
	वापस __i915_gem_object_lock(obj, ww, true);
पूर्ण

अटल अंतरभूत bool i915_gem_object_trylock(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस dma_resv_trylock(obj->base.resv);
पूर्ण

अटल अंतरभूत व्योम i915_gem_object_unlock(काष्ठा drm_i915_gem_object *obj)
अणु
	dma_resv_unlock(obj->base.resv);
पूर्ण

अटल अंतरभूत व्योम
i915_gem_object_set_पढ़ोonly(काष्ठा drm_i915_gem_object *obj)
अणु
	obj->flags |= I915_BO_READONLY;
पूर्ण

अटल अंतरभूत bool
i915_gem_object_is_पढ़ोonly(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->flags & I915_BO_READONLY;
पूर्ण

अटल अंतरभूत bool
i915_gem_object_is_contiguous(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->flags & I915_BO_ALLOC_CONTIGUOUS;
पूर्ण

अटल अंतरभूत bool
i915_gem_object_is_अस्थिर(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->flags & I915_BO_ALLOC_VOLATILE;
पूर्ण

अटल अंतरभूत व्योम
i915_gem_object_set_अस्थिर(काष्ठा drm_i915_gem_object *obj)
अणु
	obj->flags |= I915_BO_ALLOC_VOLATILE;
पूर्ण

अटल अंतरभूत bool
i915_gem_object_has_tiling_quirk(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस test_bit(I915_TILING_QUIRK_BIT, &obj->flags);
पूर्ण

अटल अंतरभूत व्योम
i915_gem_object_set_tiling_quirk(काष्ठा drm_i915_gem_object *obj)
अणु
	set_bit(I915_TILING_QUIRK_BIT, &obj->flags);
पूर्ण

अटल अंतरभूत व्योम
i915_gem_object_clear_tiling_quirk(काष्ठा drm_i915_gem_object *obj)
अणु
	clear_bit(I915_TILING_QUIRK_BIT, &obj->flags);
पूर्ण

अटल अंतरभूत bool
i915_gem_object_type_has(स्थिर काष्ठा drm_i915_gem_object *obj,
			 अचिन्हित दीर्घ flags)
अणु
	वापस obj->ops->flags & flags;
पूर्ण

अटल अंतरभूत bool
i915_gem_object_has_काष्ठा_page(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->flags & I915_BO_ALLOC_STRUCT_PAGE;
पूर्ण

अटल अंतरभूत bool
i915_gem_object_has_iomem(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस i915_gem_object_type_has(obj, I915_GEM_OBJECT_HAS_IOMEM);
पूर्ण

अटल अंतरभूत bool
i915_gem_object_is_shrinkable(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस i915_gem_object_type_has(obj, I915_GEM_OBJECT_IS_SHRINKABLE);
पूर्ण

अटल अंतरभूत bool
i915_gem_object_is_proxy(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस i915_gem_object_type_has(obj, I915_GEM_OBJECT_IS_PROXY);
पूर्ण

अटल अंतरभूत bool
i915_gem_object_never_mmap(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस i915_gem_object_type_has(obj, I915_GEM_OBJECT_NO_MMAP);
पूर्ण

अटल अंतरभूत bool
i915_gem_object_is_framebuffer(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस READ_ONCE(obj->frontbuffer);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
i915_gem_object_get_tiling(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->tiling_and_stride & TILING_MASK;
पूर्ण

अटल अंतरभूत bool
i915_gem_object_is_tiled(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस i915_gem_object_get_tiling(obj) != I915_TILING_NONE;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
i915_gem_object_get_stride(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->tiling_and_stride & STRIDE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
i915_gem_tile_height(अचिन्हित पूर्णांक tiling)
अणु
	GEM_BUG_ON(!tiling);
	वापस tiling == I915_TILING_Y ? 32 : 8;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
i915_gem_object_get_tile_height(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस i915_gem_tile_height(i915_gem_object_get_tiling(obj));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
i915_gem_object_get_tile_row_size(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस (i915_gem_object_get_stride(obj) *
		i915_gem_object_get_tile_height(obj));
पूर्ण

पूर्णांक i915_gem_object_set_tiling(काष्ठा drm_i915_gem_object *obj,
			       अचिन्हित पूर्णांक tiling, अचिन्हित पूर्णांक stride);

काष्ठा scatterlist *
__i915_gem_object_get_sg(काष्ठा drm_i915_gem_object *obj,
			 काष्ठा i915_gem_object_page_iter *iter,
			 अचिन्हित पूर्णांक n,
			 अचिन्हित पूर्णांक *offset, bool allow_alloc);

अटल अंतरभूत काष्ठा scatterlist *
i915_gem_object_get_sg(काष्ठा drm_i915_gem_object *obj,
		       अचिन्हित पूर्णांक n,
		       अचिन्हित पूर्णांक *offset, bool allow_alloc)
अणु
	वापस __i915_gem_object_get_sg(obj, &obj->mm.get_page, n, offset, allow_alloc);
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *
i915_gem_object_get_sg_dma(काष्ठा drm_i915_gem_object *obj,
			   अचिन्हित पूर्णांक n,
			   अचिन्हित पूर्णांक *offset, bool allow_alloc)
अणु
	वापस __i915_gem_object_get_sg(obj, &obj->mm.get_dma_page, n, offset, allow_alloc);
पूर्ण

काष्ठा page *
i915_gem_object_get_page(काष्ठा drm_i915_gem_object *obj,
			 अचिन्हित पूर्णांक n);

काष्ठा page *
i915_gem_object_get_dirty_page(काष्ठा drm_i915_gem_object *obj,
			       अचिन्हित पूर्णांक n);

dma_addr_t
i915_gem_object_get_dma_address_len(काष्ठा drm_i915_gem_object *obj,
				    अचिन्हित दीर्घ n,
				    अचिन्हित पूर्णांक *len);

dma_addr_t
i915_gem_object_get_dma_address(काष्ठा drm_i915_gem_object *obj,
				अचिन्हित दीर्घ n);

व्योम __i915_gem_object_set_pages(काष्ठा drm_i915_gem_object *obj,
				 काष्ठा sg_table *pages,
				 अचिन्हित पूर्णांक sg_page_sizes);

पूर्णांक ____i915_gem_object_get_pages(काष्ठा drm_i915_gem_object *obj);
पूर्णांक __i915_gem_object_get_pages(काष्ठा drm_i915_gem_object *obj);

अटल अंतरभूत पूर्णांक __must_check
i915_gem_object_pin_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	निश्चित_object_held(obj);

	अगर (atomic_inc_not_zero(&obj->mm.pages_pin_count))
		वापस 0;

	वापस __i915_gem_object_get_pages(obj);
पूर्ण

पूर्णांक i915_gem_object_pin_pages_unlocked(काष्ठा drm_i915_gem_object *obj);

अटल अंतरभूत bool
i915_gem_object_has_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस !IS_ERR_OR_शून्य(READ_ONCE(obj->mm.pages));
पूर्ण

अटल अंतरभूत व्योम
__i915_gem_object_pin_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));

	atomic_inc(&obj->mm.pages_pin_count);
पूर्ण

अटल अंतरभूत bool
i915_gem_object_has_pinned_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस atomic_पढ़ो(&obj->mm.pages_pin_count);
पूर्ण

अटल अंतरभूत व्योम
__i915_gem_object_unpin_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));
	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));

	atomic_dec(&obj->mm.pages_pin_count);
पूर्ण

अटल अंतरभूत व्योम
i915_gem_object_unpin_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	__i915_gem_object_unpin_pages(obj);
पूर्ण

पूर्णांक __i915_gem_object_put_pages(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_truncate(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_ग_लिखोback(काष्ठा drm_i915_gem_object *obj);

/**
 * i915_gem_object_pin_map - वापस a contiguous mapping of the entire object
 * @obj: the object to map पूर्णांकo kernel address space
 * @type: the type of mapping, used to select pgprot_t
 *
 * Calls i915_gem_object_pin_pages() to prevent reaping of the object's
 * pages and then वापसs a contiguous mapping of the backing storage पूर्णांकo
 * the kernel address space. Based on the @type of mapping, the PTE will be
 * set to either WriteBack or WriteCombine (via pgprot_t).
 *
 * The caller is responsible क्रम calling i915_gem_object_unpin_map() when the
 * mapping is no दीर्घer required.
 *
 * Returns the poपूर्णांकer through which to access the mapped object, or an
 * ERR_PTR() on error.
 */
व्योम *__must_check i915_gem_object_pin_map(काष्ठा drm_i915_gem_object *obj,
					   क्रमागत i915_map_type type);

व्योम *__must_check i915_gem_object_pin_map_unlocked(काष्ठा drm_i915_gem_object *obj,
						    क्रमागत i915_map_type type);

व्योम __i915_gem_object_flush_map(काष्ठा drm_i915_gem_object *obj,
				 अचिन्हित दीर्घ offset,
				 अचिन्हित दीर्घ size);
अटल अंतरभूत व्योम i915_gem_object_flush_map(काष्ठा drm_i915_gem_object *obj)
अणु
	__i915_gem_object_flush_map(obj, 0, obj->base.size);
पूर्ण

/**
 * i915_gem_object_unpin_map - releases an earlier mapping
 * @obj: the object to unmap
 *
 * After pinning the object and mapping its pages, once you are finished
 * with your access, call i915_gem_object_unpin_map() to release the pin
 * upon the mapping. Once the pin count reaches zero, that mapping may be
 * हटाओd.
 */
अटल अंतरभूत व्योम i915_gem_object_unpin_map(काष्ठा drm_i915_gem_object *obj)
अणु
	i915_gem_object_unpin_pages(obj);
पूर्ण

व्योम __i915_gem_object_release_map(काष्ठा drm_i915_gem_object *obj);

पूर्णांक i915_gem_object_prepare_पढ़ो(काष्ठा drm_i915_gem_object *obj,
				 अचिन्हित पूर्णांक *needs_clflush);
पूर्णांक i915_gem_object_prepare_ग_लिखो(काष्ठा drm_i915_gem_object *obj,
				  अचिन्हित पूर्णांक *needs_clflush);
#घोषणा CLFLUSH_BEFORE	BIT(0)
#घोषणा CLFLUSH_AFTER	BIT(1)
#घोषणा CLFLUSH_FLAGS	(CLFLUSH_BEFORE | CLFLUSH_AFTER)

अटल अंतरभूत व्योम
i915_gem_object_finish_access(काष्ठा drm_i915_gem_object *obj)
अणु
	i915_gem_object_unpin_pages(obj);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_engine_cs *
i915_gem_object_last_ग_लिखो_engine(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = शून्य;
	काष्ठा dma_fence *fence;

	rcu_पढ़ो_lock();
	fence = dma_resv_get_excl_rcu(obj->base.resv);
	rcu_पढ़ो_unlock();

	अगर (fence && dma_fence_is_i915(fence) && !dma_fence_is_संकेतed(fence))
		engine = to_request(fence)->engine;
	dma_fence_put(fence);

	वापस engine;
पूर्ण

व्योम i915_gem_object_set_cache_coherency(काष्ठा drm_i915_gem_object *obj,
					 अचिन्हित पूर्णांक cache_level);
व्योम i915_gem_object_flush_अगर_display(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_flush_अगर_display_locked(काष्ठा drm_i915_gem_object *obj);

पूर्णांक __must_check
i915_gem_object_set_to_wc_करोमुख्य(काष्ठा drm_i915_gem_object *obj, bool ग_लिखो);
पूर्णांक __must_check
i915_gem_object_set_to_gtt_करोमुख्य(काष्ठा drm_i915_gem_object *obj, bool ग_लिखो);
पूर्णांक __must_check
i915_gem_object_set_to_cpu_करोमुख्य(काष्ठा drm_i915_gem_object *obj, bool ग_लिखो);
काष्ठा i915_vma * __must_check
i915_gem_object_pin_to_display_plane(काष्ठा drm_i915_gem_object *obj,
				     काष्ठा i915_gem_ww_ctx *ww,
				     u32 alignment,
				     स्थिर काष्ठा i915_ggtt_view *view,
				     अचिन्हित पूर्णांक flags);

व्योम i915_gem_object_make_unshrinkable(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_make_shrinkable(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_make_purgeable(काष्ठा drm_i915_gem_object *obj);

अटल अंतरभूत bool cpu_ग_लिखो_needs_clflush(काष्ठा drm_i915_gem_object *obj)
अणु
	अगर (obj->cache_dirty)
		वापस false;

	अगर (!(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_WRITE))
		वापस true;

	/* Currently in use by HW (display engine)? Keep flushed. */
	वापस i915_gem_object_is_framebuffer(obj);
पूर्ण

अटल अंतरभूत व्योम __start_cpu_ग_लिखो(काष्ठा drm_i915_gem_object *obj)
अणु
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU;
	obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_CPU;
	अगर (cpu_ग_लिखो_needs_clflush(obj))
		obj->cache_dirty = true;
पूर्ण

व्योम i915_gem_fence_रुको_priority(काष्ठा dma_fence *fence,
				  स्थिर काष्ठा i915_sched_attr *attr);

पूर्णांक i915_gem_object_रुको(काष्ठा drm_i915_gem_object *obj,
			 अचिन्हित पूर्णांक flags,
			 दीर्घ समयout);
पूर्णांक i915_gem_object_रुको_priority(काष्ठा drm_i915_gem_object *obj,
				  अचिन्हित पूर्णांक flags,
				  स्थिर काष्ठा i915_sched_attr *attr);

व्योम __i915_gem_object_flush_frontbuffer(काष्ठा drm_i915_gem_object *obj,
					 क्रमागत fb_op_origin origin);
व्योम __i915_gem_object_invalidate_frontbuffer(काष्ठा drm_i915_gem_object *obj,
					      क्रमागत fb_op_origin origin);

अटल अंतरभूत व्योम
i915_gem_object_flush_frontbuffer(काष्ठा drm_i915_gem_object *obj,
				  क्रमागत fb_op_origin origin)
अणु
	अगर (unlikely(rcu_access_poपूर्णांकer(obj->frontbuffer)))
		__i915_gem_object_flush_frontbuffer(obj, origin);
पूर्ण

अटल अंतरभूत व्योम
i915_gem_object_invalidate_frontbuffer(काष्ठा drm_i915_gem_object *obj,
				       क्रमागत fb_op_origin origin)
अणु
	अगर (unlikely(rcu_access_poपूर्णांकer(obj->frontbuffer)))
		__i915_gem_object_invalidate_frontbuffer(obj, origin);
पूर्ण

पूर्णांक i915_gem_object_पढ़ो_from_page(काष्ठा drm_i915_gem_object *obj, u64 offset, व्योम *dst, पूर्णांक size);

bool i915_gem_object_is_shmem(स्थिर काष्ठा drm_i915_gem_object *obj);

#अगर_घोषित CONFIG_MMU_NOTIFIER
अटल अंतरभूत bool
i915_gem_object_is_userptr(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->userptr.notअगरier.mm;
पूर्ण

पूर्णांक i915_gem_object_userptr_submit_init(काष्ठा drm_i915_gem_object *obj);
पूर्णांक i915_gem_object_userptr_submit_करोne(काष्ठा drm_i915_gem_object *obj);
व्योम i915_gem_object_userptr_submit_fini(काष्ठा drm_i915_gem_object *obj);
पूर्णांक i915_gem_object_userptr_validate(काष्ठा drm_i915_gem_object *obj);
#अन्यथा
अटल अंतरभूत bool i915_gem_object_is_userptr(काष्ठा drm_i915_gem_object *obj) अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक i915_gem_object_userptr_submit_init(काष्ठा drm_i915_gem_object *obj) अणु GEM_BUG_ON(1); वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक i915_gem_object_userptr_submit_करोne(काष्ठा drm_i915_gem_object *obj) अणु GEM_BUG_ON(1); वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम i915_gem_object_userptr_submit_fini(काष्ठा drm_i915_gem_object *obj) अणु GEM_BUG_ON(1); पूर्ण
अटल अंतरभूत पूर्णांक i915_gem_object_userptr_validate(काष्ठा drm_i915_gem_object *obj) अणु GEM_BUG_ON(1); वापस -ENODEV; पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
