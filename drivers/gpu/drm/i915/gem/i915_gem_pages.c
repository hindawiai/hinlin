<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2014-2016 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_scatterlist.h"
#समावेश "i915_gem_lmem.h"
#समावेश "i915_gem_mman.h"

व्योम __i915_gem_object_set_pages(काष्ठा drm_i915_gem_object *obj,
				 काष्ठा sg_table *pages,
				 अचिन्हित पूर्णांक sg_page_sizes)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	अचिन्हित दीर्घ supported = INTEL_INFO(i915)->page_sizes;
	bool shrinkable;
	पूर्णांक i;

	निश्चित_object_held_shared(obj);

	अगर (i915_gem_object_is_अस्थिर(obj))
		obj->mm.madv = I915_MADV_DONTNEED;

	/* Make the pages coherent with the GPU (flushing any swapin). */
	अगर (obj->cache_dirty) अणु
		obj->ग_लिखो_करोमुख्य = 0;
		अगर (i915_gem_object_has_काष्ठा_page(obj))
			drm_clflush_sg(pages);
		obj->cache_dirty = false;
	पूर्ण

	obj->mm.get_page.sg_pos = pages->sgl;
	obj->mm.get_page.sg_idx = 0;
	obj->mm.get_dma_page.sg_pos = pages->sgl;
	obj->mm.get_dma_page.sg_idx = 0;

	obj->mm.pages = pages;

	GEM_BUG_ON(!sg_page_sizes);
	obj->mm.page_sizes.phys = sg_page_sizes;

	/*
	 * Calculate the supported page-sizes which fit पूर्णांकo the given
	 * sg_page_sizes. This will give us the page-sizes which we may be able
	 * to use opportunistically when later inserting पूर्णांकo the GTT. For
	 * example अगर phys=2G, then in theory we should be able to use 1G, 2M,
	 * 64K or 4K pages, although in practice this will depend on a number of
	 * other factors.
	 */
	obj->mm.page_sizes.sg = 0;
	क्रम_each_set_bit(i, &supported, ilog2(I915_GTT_MAX_PAGE_SIZE) + 1) अणु
		अगर (obj->mm.page_sizes.phys & ~0u << i)
			obj->mm.page_sizes.sg |= BIT(i);
	पूर्ण
	GEM_BUG_ON(!HAS_PAGE_SIZES(i915, obj->mm.page_sizes.sg));

	shrinkable = i915_gem_object_is_shrinkable(obj);

	अगर (i915_gem_object_is_tiled(obj) &&
	    i915->quirks & QUIRK_PIN_SWIZZLED_PAGES) अणु
		GEM_BUG_ON(i915_gem_object_has_tiling_quirk(obj));
		i915_gem_object_set_tiling_quirk(obj);
		GEM_BUG_ON(!list_empty(&obj->mm.link));
		atomic_inc(&obj->mm.shrink_pin);
		shrinkable = false;
	पूर्ण

	अगर (shrinkable) अणु
		काष्ठा list_head *list;
		अचिन्हित दीर्घ flags;

		निश्चित_object_held(obj);
		spin_lock_irqsave(&i915->mm.obj_lock, flags);

		i915->mm.shrink_count++;
		i915->mm.shrink_memory += obj->base.size;

		अगर (obj->mm.madv != I915_MADV_WILLNEED)
			list = &i915->mm.purge_list;
		अन्यथा
			list = &i915->mm.shrink_list;
		list_add_tail(&obj->mm.link, list);

		atomic_set(&obj->mm.shrink_pin, 0);
		spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
	पूर्ण
पूर्ण

पूर्णांक ____i915_gem_object_get_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	पूर्णांक err;

	निश्चित_object_held_shared(obj);

	अगर (unlikely(obj->mm.madv != I915_MADV_WILLNEED)) अणु
		drm_dbg(&i915->drm,
			"Attempting to obtain a purgeable object\n");
		वापस -EFAULT;
	पूर्ण

	err = obj->ops->get_pages(obj);
	GEM_BUG_ON(!err && !i915_gem_object_has_pages(obj));

	वापस err;
पूर्ण

/* Ensure that the associated pages are gathered from the backing storage
 * and pinned पूर्णांकo our object. i915_gem_object_pin_pages() may be called
 * multiple बार beक्रमe they are released by a single call to
 * i915_gem_object_unpin_pages() - once the pages are no दीर्घer referenced
 * either as a result of memory pressure (reaping pages under the shrinker)
 * or as the object is itself released.
 */
पूर्णांक __i915_gem_object_get_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	पूर्णांक err;

	निश्चित_object_held(obj);

	निश्चित_object_held_shared(obj);

	अगर (unlikely(!i915_gem_object_has_pages(obj))) अणु
		GEM_BUG_ON(i915_gem_object_has_pinned_pages(obj));

		err = ____i915_gem_object_get_pages(obj);
		अगर (err)
			वापस err;

		smp_mb__beक्रमe_atomic();
	पूर्ण
	atomic_inc(&obj->mm.pages_pin_count);

	वापस 0;
पूर्ण

पूर्णांक i915_gem_object_pin_pages_unlocked(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = i915_gem_object_lock(obj, &ww);
	अगर (!err)
		err = i915_gem_object_pin_pages(obj);

	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	वापस err;
पूर्ण

/* Immediately discard the backing storage */
व्योम i915_gem_object_truncate(काष्ठा drm_i915_gem_object *obj)
अणु
	drm_gem_मुक्त_mmap_offset(&obj->base);
	अगर (obj->ops->truncate)
		obj->ops->truncate(obj);
पूर्ण

/* Try to discard unwanted pages */
व्योम i915_gem_object_ग_लिखोback(काष्ठा drm_i915_gem_object *obj)
अणु
	निश्चित_object_held_shared(obj);
	GEM_BUG_ON(i915_gem_object_has_pages(obj));

	अगर (obj->ops->ग_लिखोback)
		obj->ops->ग_लिखोback(obj);
पूर्ण

अटल व्योम __i915_gem_object_reset_page_iter(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;

	rcu_पढ़ो_lock();
	radix_tree_क्रम_each_slot(slot, &obj->mm.get_page.radix, &iter, 0)
		radix_tree_delete(&obj->mm.get_page.radix, iter.index);
	radix_tree_क्रम_each_slot(slot, &obj->mm.get_dma_page.radix, &iter, 0)
		radix_tree_delete(&obj->mm.get_dma_page.radix, iter.index);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम unmap_object(काष्ठा drm_i915_gem_object *obj, व्योम *ptr)
अणु
	अगर (is_vदो_स्मृति_addr(ptr))
		vunmap(ptr);
पूर्ण

काष्ठा sg_table *
__i915_gem_object_unset_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा sg_table *pages;

	निश्चित_object_held_shared(obj);

	pages = fetch_and_zero(&obj->mm.pages);
	अगर (IS_ERR_OR_शून्य(pages))
		वापस pages;

	अगर (i915_gem_object_is_अस्थिर(obj))
		obj->mm.madv = I915_MADV_WILLNEED;

	i915_gem_object_make_unshrinkable(obj);

	अगर (obj->mm.mapping) अणु
		unmap_object(obj, page_mask_bits(obj->mm.mapping));
		obj->mm.mapping = शून्य;
	पूर्ण

	__i915_gem_object_reset_page_iter(obj);
	obj->mm.page_sizes.phys = obj->mm.page_sizes.sg = 0;

	वापस pages;
पूर्ण

पूर्णांक __i915_gem_object_put_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा sg_table *pages;

	अगर (i915_gem_object_has_pinned_pages(obj))
		वापस -EBUSY;

	/* May be called by shrinker from within get_pages() (on another bo) */
	निश्चित_object_held_shared(obj);

	i915_gem_object_release_mmap_offset(obj);

	/*
	 * ->put_pages might need to allocate memory क्रम the bit17 swizzle
	 * array, hence protect them from being reaped by removing them from gtt
	 * lists early.
	 */
	pages = __i915_gem_object_unset_pages(obj);

	/*
	 * XXX Temporary hijinx to aव्योम updating all backends to handle
	 * शून्य pages. In the future, when we have more asynchronous
	 * get_pages backends we should be better able to handle the
	 * cancellation of the async task in a more unअगरorm manner.
	 */
	अगर (!IS_ERR_OR_शून्य(pages))
		obj->ops->put_pages(obj, pages);

	वापस 0;
पूर्ण

/* The 'mapping' part of i915_gem_object_pin_map() below */
अटल व्योम *i915_gem_object_map_page(काष्ठा drm_i915_gem_object *obj,
				      क्रमागत i915_map_type type)
अणु
	अचिन्हित दीर्घ n_pages = obj->base.size >> PAGE_SHIFT, i;
	काष्ठा page *stack[32], **pages = stack, *page;
	काष्ठा sgt_iter iter;
	pgprot_t pgprot;
	व्योम *vaddr;

	चयन (type) अणु
	शेष:
		MISSING_CASE(type);
		fallthrough;	/* to use PAGE_KERNEL anyway */
	हाल I915_MAP_WB:
		/*
		 * On 32b, highmem using a finite set of indirect PTE (i.e.
		 * vmap) to provide भव mappings of the high pages.
		 * As these are finite, map_new_भव() must रुको क्रम some
		 * other kmap() to finish when it runs out. If we map a large
		 * number of objects, there is no method क्रम it to tell us
		 * to release the mappings, and we deadlock.
		 *
		 * However, अगर we make an explicit vmap of the page, that
		 * uses a larger vदो_स्मृति arena, and also has the ability
		 * to tell us to release unwanted mappings. Most importantly,
		 * it will fail and propagate an error instead of रुकोing
		 * क्रमever.
		 *
		 * So अगर the page is beyond the 32b boundary, make an explicit
		 * vmap.
		 */
		अगर (n_pages == 1 && !PageHighMem(sg_page(obj->mm.pages->sgl)))
			वापस page_address(sg_page(obj->mm.pages->sgl));
		pgprot = PAGE_KERNEL;
		अवरोध;
	हाल I915_MAP_WC:
		pgprot = pgprot_ग_लिखोcombine(PAGE_KERNEL_IO);
		अवरोध;
	पूर्ण

	अगर (n_pages > ARRAY_SIZE(stack)) अणु
		/* Too big क्रम stack -- allocate temporary array instead */
		pages = kvदो_स्मृति_array(n_pages, माप(*pages), GFP_KERNEL);
		अगर (!pages)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	i = 0;
	क्रम_each_sgt_page(page, iter, obj->mm.pages)
		pages[i++] = page;
	vaddr = vmap(pages, n_pages, 0, pgprot);
	अगर (pages != stack)
		kvमुक्त(pages);

	वापस vaddr ?: ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम *i915_gem_object_map_pfn(काष्ठा drm_i915_gem_object *obj,
				     क्रमागत i915_map_type type)
अणु
	resource_माप_प्रकार iomap = obj->mm.region->iomap.base -
		obj->mm.region->region.start;
	अचिन्हित दीर्घ n_pfn = obj->base.size >> PAGE_SHIFT;
	अचिन्हित दीर्घ stack[32], *pfns = stack, i;
	काष्ठा sgt_iter iter;
	dma_addr_t addr;
	व्योम *vaddr;

	अगर (type != I915_MAP_WC)
		वापस ERR_PTR(-ENODEV);

	अगर (n_pfn > ARRAY_SIZE(stack)) अणु
		/* Too big क्रम stack -- allocate temporary array instead */
		pfns = kvदो_स्मृति_array(n_pfn, माप(*pfns), GFP_KERNEL);
		अगर (!pfns)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	i = 0;
	क्रम_each_sgt_daddr(addr, iter, obj->mm.pages)
		pfns[i++] = (iomap + addr) >> PAGE_SHIFT;
	vaddr = vmap_pfn(pfns, n_pfn, pgprot_ग_लिखोcombine(PAGE_KERNEL_IO));
	अगर (pfns != stack)
		kvमुक्त(pfns);

	वापस vaddr ?: ERR_PTR(-ENOMEM);
पूर्ण

/* get, pin, and map the pages of the object पूर्णांकo kernel space */
व्योम *i915_gem_object_pin_map(काष्ठा drm_i915_gem_object *obj,
			      क्रमागत i915_map_type type)
अणु
	क्रमागत i915_map_type has_type;
	bool pinned;
	व्योम *ptr;
	पूर्णांक err;

	अगर (!i915_gem_object_has_काष्ठा_page(obj) &&
	    !i915_gem_object_type_has(obj, I915_GEM_OBJECT_HAS_IOMEM))
		वापस ERR_PTR(-ENXIO);

	निश्चित_object_held(obj);

	pinned = !(type & I915_MAP_OVERRIDE);
	type &= ~I915_MAP_OVERRIDE;

	अगर (!atomic_inc_not_zero(&obj->mm.pages_pin_count)) अणु
		अगर (unlikely(!i915_gem_object_has_pages(obj))) अणु
			GEM_BUG_ON(i915_gem_object_has_pinned_pages(obj));

			err = ____i915_gem_object_get_pages(obj);
			अगर (err)
				वापस ERR_PTR(err);

			smp_mb__beक्रमe_atomic();
		पूर्ण
		atomic_inc(&obj->mm.pages_pin_count);
		pinned = false;
	पूर्ण
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));

	ptr = page_unpack_bits(obj->mm.mapping, &has_type);
	अगर (ptr && has_type != type) अणु
		अगर (pinned) अणु
			ptr = ERR_PTR(-EBUSY);
			जाओ err_unpin;
		पूर्ण

		unmap_object(obj, ptr);

		ptr = obj->mm.mapping = शून्य;
	पूर्ण

	अगर (!ptr) अणु
		अगर (GEM_WARN_ON(type == I915_MAP_WC &&
				!अटल_cpu_has(X86_FEATURE_PAT)))
			ptr = ERR_PTR(-ENODEV);
		अन्यथा अगर (i915_gem_object_has_काष्ठा_page(obj))
			ptr = i915_gem_object_map_page(obj, type);
		अन्यथा
			ptr = i915_gem_object_map_pfn(obj, type);
		अगर (IS_ERR(ptr))
			जाओ err_unpin;

		obj->mm.mapping = page_pack_bits(ptr, type);
	पूर्ण

	वापस ptr;

err_unpin:
	atomic_dec(&obj->mm.pages_pin_count);
	वापस ptr;
पूर्ण

व्योम *i915_gem_object_pin_map_unlocked(काष्ठा drm_i915_gem_object *obj,
				       क्रमागत i915_map_type type)
अणु
	व्योम *ret;

	i915_gem_object_lock(obj, शून्य);
	ret = i915_gem_object_pin_map(obj, type);
	i915_gem_object_unlock(obj);

	वापस ret;
पूर्ण

व्योम __i915_gem_object_flush_map(काष्ठा drm_i915_gem_object *obj,
				 अचिन्हित दीर्घ offset,
				 अचिन्हित दीर्घ size)
अणु
	क्रमागत i915_map_type has_type;
	व्योम *ptr;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
	GEM_BUG_ON(range_overflows_t(typeof(obj->base.size),
				     offset, size, obj->base.size));

	wmb(); /* let all previous ग_लिखोs be visible to coherent partners */
	obj->mm.dirty = true;

	अगर (obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_WRITE)
		वापस;

	ptr = page_unpack_bits(obj->mm.mapping, &has_type);
	अगर (has_type == I915_MAP_WC)
		वापस;

	drm_clflush_virt_range(ptr + offset, size);
	अगर (size == obj->base.size) अणु
		obj->ग_लिखो_करोमुख्य &= ~I915_GEM_DOMAIN_CPU;
		obj->cache_dirty = false;
	पूर्ण
पूर्ण

व्योम __i915_gem_object_release_map(काष्ठा drm_i915_gem_object *obj)
अणु
	GEM_BUG_ON(!obj->mm.mapping);

	/*
	 * We allow removing the mapping from underneath pinned pages!
	 *
	 * Furthermore, since this is an unsafe operation reserved only
	 * क्रम स्थिरruction समय manipulation, we ignore locking prudence.
	 */
	unmap_object(obj, page_mask_bits(fetch_and_zero(&obj->mm.mapping)));

	i915_gem_object_unpin_map(obj);
पूर्ण

काष्ठा scatterlist *
__i915_gem_object_get_sg(काष्ठा drm_i915_gem_object *obj,
			 काष्ठा i915_gem_object_page_iter *iter,
			 अचिन्हित पूर्णांक n,
			 अचिन्हित पूर्णांक *offset,
			 bool allow_alloc)
अणु
	स्थिर bool dma = iter == &obj->mm.get_dma_page;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक idx, count;

	might_sleep();
	GEM_BUG_ON(n >= obj->base.size >> PAGE_SHIFT);
	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));

	/* As we iterate क्रमward through the sg, we record each entry in a
	 * radixtree क्रम quick repeated (backwards) lookups. If we have seen
	 * this index previously, we will have an entry क्रम it.
	 *
	 * Initial lookup is O(N), but this is amortized to O(1) क्रम
	 * sequential page access (where each new request is consecutive
	 * to the previous one). Repeated lookups are O(lg(obj->base.size)),
	 * i.e. O(1) with a large स्थिरant!
	 */
	अगर (n < READ_ONCE(iter->sg_idx))
		जाओ lookup;

	अगर (!allow_alloc)
		जाओ manual_lookup;

	mutex_lock(&iter->lock);

	/* We prefer to reuse the last sg so that repeated lookup of this
	 * (or the subsequent) sg are fast - comparing against the last
	 * sg is faster than going through the radixtree.
	 */

	sg = iter->sg_pos;
	idx = iter->sg_idx;
	count = dma ? __sg_dma_page_count(sg) : __sg_page_count(sg);

	जबतक (idx + count <= n) अणु
		व्योम *entry;
		अचिन्हित दीर्घ i;
		पूर्णांक ret;

		/* If we cannot allocate and insert this entry, or the
		 * inभागidual pages from this range, cancel updating the
		 * sg_idx so that on this lookup we are क्रमced to linearly
		 * scan onwards, but on future lookups we will try the
		 * insertion again (in which हाल we need to be careful of
		 * the error वापस reporting that we have alपढ़ोy inserted
		 * this index).
		 */
		ret = radix_tree_insert(&iter->radix, idx, sg);
		अगर (ret && ret != -EEXIST)
			जाओ scan;

		entry = xa_mk_value(idx);
		क्रम (i = 1; i < count; i++) अणु
			ret = radix_tree_insert(&iter->radix, idx + i, entry);
			अगर (ret && ret != -EEXIST)
				जाओ scan;
		पूर्ण

		idx += count;
		sg = ____sg_next(sg);
		count = dma ? __sg_dma_page_count(sg) : __sg_page_count(sg);
	पूर्ण

scan:
	iter->sg_pos = sg;
	iter->sg_idx = idx;

	mutex_unlock(&iter->lock);

	अगर (unlikely(n < idx)) /* insertion completed by another thपढ़ो */
		जाओ lookup;

	जाओ manual_walk;

manual_lookup:
	idx = 0;
	sg = obj->mm.pages->sgl;
	count = __sg_page_count(sg);

manual_walk:
	/*
	 * In हाल we failed to insert the entry पूर्णांकo the radixtree, we need
	 * to look beyond the current sg.
	 */
	जबतक (idx + count <= n) अणु
		idx += count;
		sg = ____sg_next(sg);
		count = dma ? __sg_dma_page_count(sg) : __sg_page_count(sg);
	पूर्ण

	*offset = n - idx;
	वापस sg;

lookup:
	rcu_पढ़ो_lock();

	sg = radix_tree_lookup(&iter->radix, n);
	GEM_BUG_ON(!sg);

	/* If this index is in the middle of multi-page sg entry,
	 * the radix tree will contain a value entry that poपूर्णांकs
	 * to the start of that range. We will वापस the poपूर्णांकer to
	 * the base page and the offset of this page within the
	 * sg entry's range.
	 */
	*offset = 0;
	अगर (unlikely(xa_is_value(sg))) अणु
		अचिन्हित दीर्घ base = xa_to_value(sg);

		sg = radix_tree_lookup(&iter->radix, base);
		GEM_BUG_ON(!sg);

		*offset = n - base;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस sg;
पूर्ण

काष्ठा page *
i915_gem_object_get_page(काष्ठा drm_i915_gem_object *obj, अचिन्हित पूर्णांक n)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक offset;

	GEM_BUG_ON(!i915_gem_object_has_काष्ठा_page(obj));

	sg = i915_gem_object_get_sg(obj, n, &offset, true);
	वापस nth_page(sg_page(sg), offset);
पूर्ण

/* Like i915_gem_object_get_page(), but mark the वापसed page dirty */
काष्ठा page *
i915_gem_object_get_dirty_page(काष्ठा drm_i915_gem_object *obj,
			       अचिन्हित पूर्णांक n)
अणु
	काष्ठा page *page;

	page = i915_gem_object_get_page(obj, n);
	अगर (!obj->mm.dirty)
		set_page_dirty(page);

	वापस page;
पूर्ण

dma_addr_t
i915_gem_object_get_dma_address_len(काष्ठा drm_i915_gem_object *obj,
				    अचिन्हित दीर्घ n,
				    अचिन्हित पूर्णांक *len)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक offset;

	sg = i915_gem_object_get_sg_dma(obj, n, &offset, true);

	अगर (len)
		*len = sg_dma_len(sg) - (offset << PAGE_SHIFT);

	वापस sg_dma_address(sg) + (offset << PAGE_SHIFT);
पूर्ण

dma_addr_t
i915_gem_object_get_dma_address(काष्ठा drm_i915_gem_object *obj,
				अचिन्हित दीर्घ n)
अणु
	वापस i915_gem_object_get_dma_address_len(obj, n, शून्य);
पूर्ण
