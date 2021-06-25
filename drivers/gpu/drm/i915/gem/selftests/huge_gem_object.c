<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "i915_scatterlist.h"

#समावेश "huge_gem_object.h"

अटल व्योम huge_मुक्त_pages(काष्ठा drm_i915_gem_object *obj,
			    काष्ठा sg_table *pages)
अणु
	अचिन्हित दीर्घ nreal = obj->scratch / PAGE_SIZE;
	काष्ठा sgt_iter sgt_iter;
	काष्ठा page *page;

	क्रम_each_sgt_page(page, sgt_iter, pages) अणु
		__मुक्त_page(page);
		अगर (!--nreal)
			अवरोध;
	पूर्ण

	sg_मुक्त_table(pages);
	kमुक्त(pages);
पूर्ण

अटल पूर्णांक huge_get_pages(काष्ठा drm_i915_gem_object *obj)
अणु
#घोषणा GFP (GFP_KERNEL | __GFP_NOWARN | __GFP_RETRY_MAYFAIL)
	स्थिर अचिन्हित दीर्घ nreal = obj->scratch / PAGE_SIZE;
	स्थिर अचिन्हित दीर्घ npages = obj->base.size / PAGE_SIZE;
	काष्ठा scatterlist *sg, *src, *end;
	काष्ठा sg_table *pages;
	अचिन्हित दीर्घ n;

	pages = kदो_स्मृति(माप(*pages), GFP);
	अगर (!pages)
		वापस -ENOMEM;

	अगर (sg_alloc_table(pages, npages, GFP)) अणु
		kमुक्त(pages);
		वापस -ENOMEM;
	पूर्ण

	sg = pages->sgl;
	क्रम (n = 0; n < nreal; n++) अणु
		काष्ठा page *page;

		page = alloc_page(GFP | __GFP_HIGHMEM);
		अगर (!page) अणु
			sg_mark_end(sg);
			जाओ err;
		पूर्ण

		sg_set_page(sg, page, PAGE_SIZE, 0);
		sg = __sg_next(sg);
	पूर्ण
	अगर (nreal < npages) अणु
		क्रम (end = sg, src = pages->sgl; sg; sg = __sg_next(sg)) अणु
			sg_set_page(sg, sg_page(src), PAGE_SIZE, 0);
			src = __sg_next(src);
			अगर (src == end)
				src = pages->sgl;
		पूर्ण
	पूर्ण

	अगर (i915_gem_gtt_prepare_pages(obj, pages))
		जाओ err;

	__i915_gem_object_set_pages(obj, pages, PAGE_SIZE);

	वापस 0;

err:
	huge_मुक्त_pages(obj, pages);
	वापस -ENOMEM;
#अघोषित GFP
पूर्ण

अटल व्योम huge_put_pages(काष्ठा drm_i915_gem_object *obj,
			   काष्ठा sg_table *pages)
अणु
	i915_gem_gtt_finish_pages(obj, pages);
	huge_मुक्त_pages(obj, pages);

	obj->mm.dirty = false;
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops huge_ops = अणु
	.name = "huge-gem",
	.get_pages = huge_get_pages,
	.put_pages = huge_put_pages,
पूर्ण;

काष्ठा drm_i915_gem_object *
huge_gem_object(काष्ठा drm_i915_निजी *i915,
		phys_addr_t phys_size,
		dma_addr_t dma_size)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित पूर्णांक cache_level;

	GEM_BUG_ON(!phys_size || phys_size > dma_size);
	GEM_BUG_ON(!IS_ALIGNED(phys_size, PAGE_SIZE));
	GEM_BUG_ON(!IS_ALIGNED(dma_size, I915_GTT_PAGE_SIZE));

	अगर (overflows_type(dma_size, obj->base.size))
		वापस ERR_PTR(-E2BIG);

	obj = i915_gem_object_alloc();
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	drm_gem_निजी_object_init(&i915->drm, &obj->base, dma_size);
	i915_gem_object_init(obj, &huge_ops, &lock_class,
			     I915_BO_ALLOC_STRUCT_PAGE);

	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU;
	obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_CPU;
	cache_level = HAS_LLC(i915) ? I915_CACHE_LLC : I915_CACHE_NONE;
	i915_gem_object_set_cache_coherency(obj, cache_level);
	obj->scratch = phys_size;

	वापस obj;
पूर्ण
