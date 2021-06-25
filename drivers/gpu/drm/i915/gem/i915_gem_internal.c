<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2014-2016 Intel Corporation
 */

#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/swiotlb.h>

#समावेश "i915_drv.h"
#समावेश "i915_gem.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_scatterlist.h"
#समावेश "i915_utils.h"

#घोषणा QUIET (__GFP_NORETRY | __GFP_NOWARN)
#घोषणा MAYFAIL (__GFP_RETRY_MAYFAIL | __GFP_NOWARN)

अटल व्योम पूर्णांकernal_मुक्त_pages(काष्ठा sg_table *st)
अणु
	काष्ठा scatterlist *sg;

	क्रम (sg = st->sgl; sg; sg = __sg_next(sg)) अणु
		अगर (sg_page(sg))
			__मुक्त_pages(sg_page(sg), get_order(sg->length));
	पूर्ण

	sg_मुक्त_table(st);
	kमुक्त(st);
पूर्ण

अटल पूर्णांक i915_gem_object_get_pages_पूर्णांकernal(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक sg_page_sizes;
	अचिन्हित पूर्णांक npages;
	पूर्णांक max_order;
	gfp_t gfp;

	max_order = MAX_ORDER;
#अगर_घोषित CONFIG_SWIOTLB
	अगर (is_swiotlb_active()) अणु
		अचिन्हित पूर्णांक max_segment;

		max_segment = swiotlb_max_segment();
		अगर (max_segment) अणु
			max_segment = max_t(अचिन्हित पूर्णांक, max_segment,
					    PAGE_SIZE) >> PAGE_SHIFT;
			max_order = min(max_order, ilog2(max_segment));
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	gfp = GFP_KERNEL | __GFP_HIGHMEM | __GFP_RECLAIMABLE;
	अगर (IS_I965GM(i915) || IS_I965G(i915)) अणु
		/* 965gm cannot relocate objects above 4GiB. */
		gfp &= ~__GFP_HIGHMEM;
		gfp |= __GFP_DMA32;
	पूर्ण

create_st:
	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	npages = obj->base.size / PAGE_SIZE;
	अगर (sg_alloc_table(st, npages, GFP_KERNEL)) अणु
		kमुक्त(st);
		वापस -ENOMEM;
	पूर्ण

	sg = st->sgl;
	st->nents = 0;
	sg_page_sizes = 0;

	करो अणु
		पूर्णांक order = min(fls(npages) - 1, max_order);
		काष्ठा page *page;

		करो अणु
			page = alloc_pages(gfp | (order ? QUIET : MAYFAIL),
					   order);
			अगर (page)
				अवरोध;
			अगर (!order--)
				जाओ err;

			/* Limit subsequent allocations as well */
			max_order = order;
		पूर्ण जबतक (1);

		sg_set_page(sg, page, PAGE_SIZE << order, 0);
		sg_page_sizes |= PAGE_SIZE << order;
		st->nents++;

		npages -= 1 << order;
		अगर (!npages) अणु
			sg_mark_end(sg);
			अवरोध;
		पूर्ण

		sg = __sg_next(sg);
	पूर्ण जबतक (1);

	अगर (i915_gem_gtt_prepare_pages(obj, st)) अणु
		/* Failed to dma-map try again with single page sg segments */
		अगर (get_order(st->sgl->length)) अणु
			पूर्णांकernal_मुक्त_pages(st);
			max_order = 0;
			जाओ create_st;
		पूर्ण
		जाओ err;
	पूर्ण

	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	वापस 0;

err:
	sg_set_page(sg, शून्य, 0, 0);
	sg_mark_end(sg);
	पूर्णांकernal_मुक्त_pages(st);

	वापस -ENOMEM;
पूर्ण

अटल व्योम i915_gem_object_put_pages_पूर्णांकernal(काष्ठा drm_i915_gem_object *obj,
					       काष्ठा sg_table *pages)
अणु
	i915_gem_gtt_finish_pages(obj, pages);
	पूर्णांकernal_मुक्त_pages(pages);

	obj->mm.dirty = false;
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops i915_gem_object_पूर्णांकernal_ops = अणु
	.name = "i915_gem_object_internal",
	.flags = I915_GEM_OBJECT_IS_SHRINKABLE,
	.get_pages = i915_gem_object_get_pages_पूर्णांकernal,
	.put_pages = i915_gem_object_put_pages_पूर्णांकernal,
पूर्ण;

/**
 * i915_gem_object_create_पूर्णांकernal: create an object with अस्थिर pages
 * @i915: the i915 device
 * @size: the size in bytes of backing storage to allocate क्रम the object
 *
 * Creates a new object that wraps some पूर्णांकernal memory क्रम निजी use.
 * This object is not backed by swappable storage, and as such its contents
 * are अस्थिर and only valid whilst pinned. If the object is reaped by the
 * shrinker, its pages and data will be discarded. Equally, it is not a full
 * GEM object and so not valid क्रम access from userspace. This makes it useful
 * क्रम hardware पूर्णांकerfaces like ringbuffers (which are pinned from the समय
 * the request is written to the समय the hardware stops accessing it), but
 * not क्रम contexts (which need to be preserved when not active क्रम later
 * reuse). Note that it is not cleared upon allocation.
 */
काष्ठा drm_i915_gem_object *
i915_gem_object_create_पूर्णांकernal(काष्ठा drm_i915_निजी *i915,
				phys_addr_t size)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित पूर्णांक cache_level;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, PAGE_SIZE));

	अगर (overflows_type(size, obj->base.size))
		वापस ERR_PTR(-E2BIG);

	obj = i915_gem_object_alloc();
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	drm_gem_निजी_object_init(&i915->drm, &obj->base, size);
	i915_gem_object_init(obj, &i915_gem_object_पूर्णांकernal_ops, &lock_class,
			     I915_BO_ALLOC_STRUCT_PAGE);

	/*
	 * Mark the object as अस्थिर, such that the pages are marked as
	 * करोntneed whilst they are still pinned. As soon as they are unpinned
	 * they are allowed to be reaped by the shrinker, and the caller is
	 * expected to repopulate - the contents of this object are only valid
	 * whilst active and pinned.
	 */
	i915_gem_object_set_अस्थिर(obj);

	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU;
	obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_CPU;

	cache_level = HAS_LLC(i915) ? I915_CACHE_LLC : I915_CACHE_NONE;
	i915_gem_object_set_cache_coherency(obj, cache_level);

	वापस obj;
पूर्ण
