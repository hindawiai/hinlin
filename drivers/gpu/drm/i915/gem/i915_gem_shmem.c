<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2014-2016 Intel Corporation
 */

#समावेश <linux/pagevec.h>
#समावेश <linux/swap.h>

#समावेश "gem/i915_gem_region.h"
#समावेश "i915_drv.h"
#समावेश "i915_gemfs.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_scatterlist.h"
#समावेश "i915_trace.h"

/*
 * Move pages to appropriate lru and release the pagevec, decrementing the
 * ref count of those pages.
 */
अटल व्योम check_release_pagevec(काष्ठा pagevec *pvec)
अणु
	check_move_unevictable_pages(pvec);
	__pagevec_release(pvec);
	cond_resched();
पूर्ण

अटल पूर्णांक shmem_get_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा पूर्णांकel_memory_region *mem = obj->mm.region;
	स्थिर अचिन्हित दीर्घ page_count = obj->base.size / PAGE_SIZE;
	अचिन्हित दीर्घ i;
	काष्ठा address_space *mapping;
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	काष्ठा sgt_iter sgt_iter;
	काष्ठा page *page;
	अचिन्हित दीर्घ last_pfn = 0;	/* suppress gcc warning */
	अचिन्हित पूर्णांक max_segment = i915_sg_segment_size();
	अचिन्हित पूर्णांक sg_page_sizes;
	gfp_t noreclaim;
	पूर्णांक ret;

	/*
	 * Assert that the object is not currently in any GPU करोमुख्य. As it
	 * wasn't in the GTT, there shouldn't be any way it could have been in
	 * a GPU cache
	 */
	GEM_BUG_ON(obj->पढ़ो_करोमुख्यs & I915_GEM_GPU_DOMAINS);
	GEM_BUG_ON(obj->ग_लिखो_करोमुख्य & I915_GEM_GPU_DOMAINS);

	/*
	 * If there's no chance of allocating enough pages क्रम the whole
	 * object, bail early.
	 */
	अगर (obj->base.size > resource_size(&mem->region))
		वापस -ENOMEM;

	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

rebuild_st:
	अगर (sg_alloc_table(st, page_count, GFP_KERNEL)) अणु
		kमुक्त(st);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Get the list of pages out of our काष्ठा file.  They'll be pinned
	 * at this poपूर्णांक until we release them.
	 *
	 * Fail silently without starting the shrinker
	 */
	mapping = obj->base.filp->f_mapping;
	mapping_set_unevictable(mapping);
	noreclaim = mapping_gfp_स्थिरraपूर्णांक(mapping, ~__GFP_RECLAIM);
	noreclaim |= __GFP_NORETRY | __GFP_NOWARN;

	sg = st->sgl;
	st->nents = 0;
	sg_page_sizes = 0;
	क्रम (i = 0; i < page_count; i++) अणु
		स्थिर अचिन्हित पूर्णांक shrink[] = अणु
			I915_SHRINK_BOUND | I915_SHRINK_UNBOUND,
			0,
		पूर्ण, *s = shrink;
		gfp_t gfp = noreclaim;

		करो अणु
			cond_resched();
			page = shmem_पढ़ो_mapping_page_gfp(mapping, i, gfp);
			अगर (!IS_ERR(page))
				अवरोध;

			अगर (!*s) अणु
				ret = PTR_ERR(page);
				जाओ err_sg;
			पूर्ण

			i915_gem_shrink(शून्य, i915, 2 * page_count, शून्य, *s++);

			/*
			 * We've tried hard to allocate the memory by reaping
			 * our own buffer, now let the real VM करो its job and
			 * go करोwn in flames अगर truly OOM.
			 *
			 * However, since graphics tend to be disposable,
			 * defer the oom here by reporting the ENOMEM back
			 * to userspace.
			 */
			अगर (!*s) अणु
				/* reclaim and warn, but no oom */
				gfp = mapping_gfp_mask(mapping);

				/*
				 * Our bo are always dirty and so we require
				 * kswapd to reclaim our pages (direct reclaim
				 * करोes not effectively begin pageout of our
				 * buffers on its own). However, direct reclaim
				 * only रुकोs क्रम kswapd when under allocation
				 * congestion. So as a result __GFP_RECLAIM is
				 * unreliable and fails to actually reclaim our
				 * dirty pages -- unless you try over and over
				 * again with !__GFP_NORETRY. However, we still
				 * want to fail this allocation rather than
				 * trigger the out-of-memory समाप्तer and क्रम
				 * this we want __GFP_RETRY_MAYFAIL.
				 */
				gfp |= __GFP_RETRY_MAYFAIL;
			पूर्ण
		पूर्ण जबतक (1);

		अगर (!i ||
		    sg->length >= max_segment ||
		    page_to_pfn(page) != last_pfn + 1) अणु
			अगर (i) अणु
				sg_page_sizes |= sg->length;
				sg = sg_next(sg);
			पूर्ण
			st->nents++;
			sg_set_page(sg, page, PAGE_SIZE, 0);
		पूर्ण अन्यथा अणु
			sg->length += PAGE_SIZE;
		पूर्ण
		last_pfn = page_to_pfn(page);

		/* Check that the i965g/gm workaround works. */
		GEM_BUG_ON(gfp & __GFP_DMA32 && last_pfn >= 0x00100000UL);
	पूर्ण
	अगर (sg) अणु /* loop terminated early; लघु sg table */
		sg_page_sizes |= sg->length;
		sg_mark_end(sg);
	पूर्ण

	/* Trim unused sg entries to aव्योम wasting memory. */
	i915_sg_trim(st);

	ret = i915_gem_gtt_prepare_pages(obj, st);
	अगर (ret) अणु
		/*
		 * DMA remapping failed? One possible cause is that
		 * it could not reserve enough large entries, asking
		 * क्रम PAGE_SIZE chunks instead may be helpful.
		 */
		अगर (max_segment > PAGE_SIZE) अणु
			क्रम_each_sgt_page(page, sgt_iter, st)
				put_page(page);
			sg_मुक्त_table(st);

			max_segment = PAGE_SIZE;
			जाओ rebuild_st;
		पूर्ण अन्यथा अणु
			dev_warn(i915->drm.dev,
				 "Failed to DMA remap %lu pages\n",
				 page_count);
			जाओ err_pages;
		पूर्ण
	पूर्ण

	अगर (i915_gem_object_needs_bit17_swizzle(obj))
		i915_gem_object_करो_bit_17_swizzle(obj, st);

	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	वापस 0;

err_sg:
	sg_mark_end(sg);
err_pages:
	mapping_clear_unevictable(mapping);
	अगर (sg != st->sgl) अणु
		काष्ठा pagevec pvec;

		pagevec_init(&pvec);
		क्रम_each_sgt_page(page, sgt_iter, st) अणु
			अगर (!pagevec_add(&pvec, page))
				check_release_pagevec(&pvec);
		पूर्ण
		अगर (pagevec_count(&pvec))
			check_release_pagevec(&pvec);
	पूर्ण
	sg_मुक्त_table(st);
	kमुक्त(st);

	/*
	 * shmemfs first checks अगर there is enough memory to allocate the page
	 * and reports ENOSPC should there be insufficient, aदीर्घ with the usual
	 * ENOMEM क्रम a genuine allocation failure.
	 *
	 * We use ENOSPC in our driver to mean that we have run out of aperture
	 * space and so want to translate the error from shmemfs back to our
	 * usual understanding of ENOMEM.
	 */
	अगर (ret == -ENOSPC)
		ret = -ENOMEM;

	वापस ret;
पूर्ण

अटल व्योम
shmem_truncate(काष्ठा drm_i915_gem_object *obj)
अणु
	/*
	 * Our goal here is to वापस as much of the memory as
	 * is possible back to the प्रणाली as we are called from OOM.
	 * To करो this we must inकाष्ठा the shmfs to drop all of its
	 * backing pages, *now*.
	 */
	shmem_truncate_range(file_inode(obj->base.filp), 0, (loff_t)-1);
	obj->mm.madv = __I915_MADV_PURGED;
	obj->mm.pages = ERR_PTR(-EFAULT);
पूर्ण

अटल व्योम
shmem_ग_लिखोback(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा address_space *mapping;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_NONE,
		.nr_to_ग_लिखो = SWAP_CLUSTER_MAX,
		.range_start = 0,
		.range_end = Lदीर्घ_उच्च,
		.क्रम_reclaim = 1,
	पूर्ण;
	अचिन्हित दीर्घ i;

	/*
	 * Leave mmapings पूर्णांकact (GTT will have been revoked on unbinding,
	 * leaving only CPU mmapings around) and add those pages to the LRU
	 * instead of invoking ग_लिखोback so they are aged and paged out
	 * as normal.
	 */
	mapping = obj->base.filp->f_mapping;

	/* Begin ग_लिखोback on each dirty page */
	क्रम (i = 0; i < obj->base.size >> PAGE_SHIFT; i++) अणु
		काष्ठा page *page;

		page = find_lock_page(mapping, i);
		अगर (!page)
			जारी;

		अगर (!page_mapped(page) && clear_page_dirty_क्रम_io(page)) अणु
			पूर्णांक ret;

			SetPageReclaim(page);
			ret = mapping->a_ops->ग_लिखोpage(page, &wbc);
			अगर (!PageWriteback(page))
				ClearPageReclaim(page);
			अगर (!ret)
				जाओ put;
		पूर्ण
		unlock_page(page);
put:
		put_page(page);
	पूर्ण
पूर्ण

व्योम
__i915_gem_object_release_shmem(काष्ठा drm_i915_gem_object *obj,
				काष्ठा sg_table *pages,
				bool needs_clflush)
अणु
	GEM_BUG_ON(obj->mm.madv == __I915_MADV_PURGED);

	अगर (obj->mm.madv == I915_MADV_DONTNEED)
		obj->mm.dirty = false;

	अगर (needs_clflush &&
	    (obj->पढ़ो_करोमुख्यs & I915_GEM_DOMAIN_CPU) == 0 &&
	    !(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
		drm_clflush_sg(pages);

	__start_cpu_ग_लिखो(obj);
पूर्ण

व्योम i915_gem_object_put_pages_shmem(काष्ठा drm_i915_gem_object *obj, काष्ठा sg_table *pages)
अणु
	काष्ठा sgt_iter sgt_iter;
	काष्ठा pagevec pvec;
	काष्ठा page *page;

	__i915_gem_object_release_shmem(obj, pages, true);

	i915_gem_gtt_finish_pages(obj, pages);

	अगर (i915_gem_object_needs_bit17_swizzle(obj))
		i915_gem_object_save_bit_17_swizzle(obj, pages);

	mapping_clear_unevictable(file_inode(obj->base.filp)->i_mapping);

	pagevec_init(&pvec);
	क्रम_each_sgt_page(page, sgt_iter, pages) अणु
		अगर (obj->mm.dirty)
			set_page_dirty(page);

		अगर (obj->mm.madv == I915_MADV_WILLNEED)
			mark_page_accessed(page);

		अगर (!pagevec_add(&pvec, page))
			check_release_pagevec(&pvec);
	पूर्ण
	अगर (pagevec_count(&pvec))
		check_release_pagevec(&pvec);
	obj->mm.dirty = false;

	sg_मुक्त_table(pages);
	kमुक्त(pages);
पूर्ण

अटल व्योम
shmem_put_pages(काष्ठा drm_i915_gem_object *obj, काष्ठा sg_table *pages)
अणु
	अगर (likely(i915_gem_object_has_काष्ठा_page(obj)))
		i915_gem_object_put_pages_shmem(obj, pages);
	अन्यथा
		i915_gem_object_put_pages_phys(obj, pages);
पूर्ण

अटल पूर्णांक
shmem_pग_लिखो(काष्ठा drm_i915_gem_object *obj,
	     स्थिर काष्ठा drm_i915_gem_pग_लिखो *arg)
अणु
	काष्ठा address_space *mapping = obj->base.filp->f_mapping;
	अक्षर __user *user_data = u64_to_user_ptr(arg->data_ptr);
	u64 reमुख्य, offset;
	अचिन्हित पूर्णांक pg;

	/* Caller alपढ़ोy validated user args */
	GEM_BUG_ON(!access_ok(user_data, arg->size));

	अगर (!i915_gem_object_has_काष्ठा_page(obj))
		वापस i915_gem_object_pग_लिखो_phys(obj, arg);

	/*
	 * Beक्रमe we instantiate/pin the backing store क्रम our use, we
	 * can prepopulate the shmemfs filp efficiently using a ग_लिखो पूर्णांकo
	 * the pagecache. We aव्योम the penalty of instantiating all the
	 * pages, important अगर the user is just writing to a few and never
	 * uses the object on the GPU, and using a direct ग_लिखो पूर्णांकo shmemfs
	 * allows it to aव्योम the cost of retrieving a page (either swapin
	 * or clearing-beक्रमe-use) beक्रमe it is overwritten.
	 */
	अगर (i915_gem_object_has_pages(obj))
		वापस -ENODEV;

	अगर (obj->mm.madv != I915_MADV_WILLNEED)
		वापस -EFAULT;

	/*
	 * Beक्रमe the pages are instantiated the object is treated as being
	 * in the CPU करोमुख्य. The pages will be clflushed as required beक्रमe
	 * use, and we can मुक्तly ग_लिखो पूर्णांकo the pages directly. If userspace
	 * races pग_लिखो with any other operation; corruption will ensue -
	 * that is userspace's prerogative!
	 */

	reमुख्य = arg->size;
	offset = arg->offset;
	pg = offset_in_page(offset);

	करो अणु
		अचिन्हित पूर्णांक len, unwritten;
		काष्ठा page *page;
		व्योम *data, *vaddr;
		पूर्णांक err;
		अक्षर c;

		len = PAGE_SIZE - pg;
		अगर (len > reमुख्य)
			len = reमुख्य;

		/* Prefault the user page to reduce potential recursion */
		err = __get_user(c, user_data);
		अगर (err)
			वापस err;

		err = __get_user(c, user_data + len - 1);
		अगर (err)
			वापस err;

		err = pagecache_ग_लिखो_begin(obj->base.filp, mapping,
					    offset, len, 0,
					    &page, &data);
		अगर (err < 0)
			वापस err;

		vaddr = kmap_atomic(page);
		unwritten = __copy_from_user_inatomic(vaddr + pg,
						      user_data,
						      len);
		kunmap_atomic(vaddr);

		err = pagecache_ग_लिखो_end(obj->base.filp, mapping,
					  offset, len, len - unwritten,
					  page, data);
		अगर (err < 0)
			वापस err;

		/* We करोn't handle -EFAULT, leave it to the caller to check */
		अगर (unwritten)
			वापस -ENODEV;

		reमुख्य -= len;
		user_data += len;
		offset += len;
		pg = 0;
	पूर्ण जबतक (reमुख्य);

	वापस 0;
पूर्ण

अटल पूर्णांक
shmem_pपढ़ो(काष्ठा drm_i915_gem_object *obj,
	    स्थिर काष्ठा drm_i915_gem_pपढ़ो *arg)
अणु
	अगर (!i915_gem_object_has_काष्ठा_page(obj))
		वापस i915_gem_object_pपढ़ो_phys(obj, arg);

	वापस -ENODEV;
पूर्ण

अटल व्योम shmem_release(काष्ठा drm_i915_gem_object *obj)
अणु
	अगर (obj->flags & I915_BO_ALLOC_STRUCT_PAGE)
		i915_gem_object_release_memory_region(obj);

	fput(obj->base.filp);
पूर्ण

स्थिर काष्ठा drm_i915_gem_object_ops i915_gem_shmem_ops = अणु
	.name = "i915_gem_object_shmem",
	.flags = I915_GEM_OBJECT_IS_SHRINKABLE,

	.get_pages = shmem_get_pages,
	.put_pages = shmem_put_pages,
	.truncate = shmem_truncate,
	.ग_लिखोback = shmem_ग_लिखोback,

	.pग_लिखो = shmem_pग_लिखो,
	.pपढ़ो = shmem_pपढ़ो,

	.release = shmem_release,
पूर्ण;

अटल पूर्णांक __create_shmem(काष्ठा drm_i915_निजी *i915,
			  काष्ठा drm_gem_object *obj,
			  resource_माप_प्रकार size)
अणु
	अचिन्हित दीर्घ flags = VM_NORESERVE;
	काष्ठा file *filp;

	drm_gem_निजी_object_init(&i915->drm, obj, size);

	अगर (i915->mm.gemfs)
		filp = shmem_file_setup_with_mnt(i915->mm.gemfs, "i915", size,
						 flags);
	अन्यथा
		filp = shmem_file_setup("i915", size, flags);
	अगर (IS_ERR(filp))
		वापस PTR_ERR(filp);

	obj->filp = filp;
	वापस 0;
पूर्ण

अटल पूर्णांक shmem_object_init(काष्ठा पूर्णांकel_memory_region *mem,
			     काष्ठा drm_i915_gem_object *obj,
			     resource_माप_प्रकार size,
			     अचिन्हित पूर्णांक flags)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_निजी *i915 = mem->i915;
	काष्ठा address_space *mapping;
	अचिन्हित पूर्णांक cache_level;
	gfp_t mask;
	पूर्णांक ret;

	ret = __create_shmem(i915, &obj->base, size);
	अगर (ret)
		वापस ret;

	mask = GFP_HIGHUSER | __GFP_RECLAIMABLE;
	अगर (IS_I965GM(i915) || IS_I965G(i915)) अणु
		/* 965gm cannot relocate objects above 4GiB. */
		mask &= ~__GFP_HIGHMEM;
		mask |= __GFP_DMA32;
	पूर्ण

	mapping = obj->base.filp->f_mapping;
	mapping_set_gfp_mask(mapping, mask);
	GEM_BUG_ON(!(mapping_gfp_mask(mapping) & __GFP_RECLAIM));

	i915_gem_object_init(obj, &i915_gem_shmem_ops, &lock_class,
			     I915_BO_ALLOC_STRUCT_PAGE);

	obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_CPU;
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU;

	अगर (HAS_LLC(i915))
		/* On some devices, we can have the GPU use the LLC (the CPU
		 * cache) क्रम about a 10% perक्रमmance improvement
		 * compared to uncached.  Graphics requests other than
		 * display scanout are coherent with the CPU in
		 * accessing this cache.  This means in this mode we
		 * करोn't need to clflush on the CPU side, and on the
		 * GPU side we only need to flush पूर्णांकernal caches to
		 * get data visible to the CPU.
		 *
		 * However, we मुख्यtain the display planes as UC, and so
		 * need to rebind when first used as such.
		 */
		cache_level = I915_CACHE_LLC;
	अन्यथा
		cache_level = I915_CACHE_NONE;

	i915_gem_object_set_cache_coherency(obj, cache_level);

	i915_gem_object_init_memory_region(obj, mem);

	वापस 0;
पूर्ण

काष्ठा drm_i915_gem_object *
i915_gem_object_create_shmem(काष्ठा drm_i915_निजी *i915,
			     resource_माप_प्रकार size)
अणु
	वापस i915_gem_object_create_region(i915->mm.regions[INTEL_REGION_SMEM],
					     size, 0);
पूर्ण

/* Allocate a new GEM object and fill it with the supplied data */
काष्ठा drm_i915_gem_object *
i915_gem_object_create_shmem_from_data(काष्ठा drm_i915_निजी *dev_priv,
				       स्थिर व्योम *data, resource_माप_प्रकार size)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा file *file;
	resource_माप_प्रकार offset;
	पूर्णांक err;

	obj = i915_gem_object_create_shmem(dev_priv, round_up(size, PAGE_SIZE));
	अगर (IS_ERR(obj))
		वापस obj;

	GEM_BUG_ON(obj->ग_लिखो_करोमुख्य != I915_GEM_DOMAIN_CPU);

	file = obj->base.filp;
	offset = 0;
	करो अणु
		अचिन्हित पूर्णांक len = min_t(typeof(size), size, PAGE_SIZE);
		काष्ठा page *page;
		व्योम *pgdata, *vaddr;

		err = pagecache_ग_लिखो_begin(file, file->f_mapping,
					    offset, len, 0,
					    &page, &pgdata);
		अगर (err < 0)
			जाओ fail;

		vaddr = kmap(page);
		स_नकल(vaddr, data, len);
		kunmap(page);

		err = pagecache_ग_लिखो_end(file, file->f_mapping,
					  offset, len, len,
					  page, pgdata);
		अगर (err < 0)
			जाओ fail;

		size -= len;
		data += len;
		offset += len;
	पूर्ण जबतक (size);

	वापस obj;

fail:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक init_shmem(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	पूर्णांक err;

	err = i915_gemfs_init(mem->i915);
	अगर (err) अणु
		DRM_NOTE("Unable to create a private tmpfs mount, hugepage support will be disabled(%d).\n",
			 err);
	पूर्ण

	पूर्णांकel_memory_region_set_name(mem, "system");

	वापस 0; /* Don't error, we can simply fallback to the kernel mnt */
पूर्ण

अटल व्योम release_shmem(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	i915_gemfs_fini(mem->i915);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_memory_region_ops shmem_region_ops = अणु
	.init = init_shmem,
	.release = release_shmem,
	.init_object = shmem_object_init,
पूर्ण;

काष्ठा पूर्णांकel_memory_region *i915_gem_shmem_setup(काष्ठा drm_i915_निजी *i915)
अणु
	वापस पूर्णांकel_memory_region_create(i915, 0,
					  totalram_pages() << PAGE_SHIFT,
					  PAGE_SIZE, 0,
					  &shmem_region_ops);
पूर्ण

bool i915_gem_object_is_shmem(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस obj->ops == &i915_gem_shmem_ops;
पूर्ण
