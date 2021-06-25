<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "intel_memory_region.h"
#समावेश "i915_gem_region.h"
#समावेश "i915_drv.h"
#समावेश "i915_trace.h"

व्योम
i915_gem_object_put_pages_buddy(काष्ठा drm_i915_gem_object *obj,
				काष्ठा sg_table *pages)
अणु
	__पूर्णांकel_memory_region_put_pages_buddy(obj->mm.region, &obj->mm.blocks);

	obj->mm.dirty = false;
	sg_मुक्त_table(pages);
	kमुक्त(pages);
पूर्ण

पूर्णांक
i915_gem_object_get_pages_buddy(काष्ठा drm_i915_gem_object *obj)
अणु
	स्थिर u64 max_segment = i915_sg_segment_size();
	काष्ठा पूर्णांकel_memory_region *mem = obj->mm.region;
	काष्ठा list_head *blocks = &obj->mm.blocks;
	resource_माप_प्रकार size = obj->base.size;
	resource_माप_प्रकार prev_end;
	काष्ठा i915_buddy_block *block;
	अचिन्हित पूर्णांक flags;
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक sg_page_sizes;
	पूर्णांक ret;

	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	अगर (sg_alloc_table(st, size >> PAGE_SHIFT, GFP_KERNEL)) अणु
		kमुक्त(st);
		वापस -ENOMEM;
	पूर्ण

	flags = I915_ALLOC_MIN_PAGE_SIZE;
	अगर (obj->flags & I915_BO_ALLOC_CONTIGUOUS)
		flags |= I915_ALLOC_CONTIGUOUS;

	ret = __पूर्णांकel_memory_region_get_pages_buddy(mem, size, flags, blocks);
	अगर (ret)
		जाओ err_मुक्त_sg;

	GEM_BUG_ON(list_empty(blocks));

	sg = st->sgl;
	st->nents = 0;
	sg_page_sizes = 0;
	prev_end = (resource_माप_प्रकार)-1;

	list_क्रम_each_entry(block, blocks, link) अणु
		u64 block_size, offset;

		block_size = min_t(u64, size,
				   i915_buddy_block_size(&mem->mm, block));
		offset = i915_buddy_block_offset(block);

		जबतक (block_size) अणु
			u64 len;

			अगर (offset != prev_end || sg->length >= max_segment) अणु
				अगर (st->nents) अणु
					sg_page_sizes |= sg->length;
					sg = __sg_next(sg);
				पूर्ण

				sg_dma_address(sg) = mem->region.start + offset;
				sg_dma_len(sg) = 0;
				sg->length = 0;
				st->nents++;
			पूर्ण

			len = min(block_size, max_segment - sg->length);
			sg->length += len;
			sg_dma_len(sg) += len;

			offset += len;
			block_size -= len;

			prev_end = offset;
		पूर्ण
	पूर्ण

	sg_page_sizes |= sg->length;
	sg_mark_end(sg);
	i915_sg_trim(st);

	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	वापस 0;

err_मुक्त_sg:
	sg_मुक्त_table(st);
	kमुक्त(st);
	वापस ret;
पूर्ण

व्योम i915_gem_object_init_memory_region(काष्ठा drm_i915_gem_object *obj,
					काष्ठा पूर्णांकel_memory_region *mem)
अणु
	INIT_LIST_HEAD(&obj->mm.blocks);
	obj->mm.region = पूर्णांकel_memory_region_get(mem);

	अगर (obj->base.size <= mem->min_page_size)
		obj->flags |= I915_BO_ALLOC_CONTIGUOUS;

	mutex_lock(&mem->objects.lock);

	अगर (obj->flags & I915_BO_ALLOC_VOLATILE)
		list_add(&obj->mm.region_link, &mem->objects.purgeable);
	अन्यथा
		list_add(&obj->mm.region_link, &mem->objects.list);

	mutex_unlock(&mem->objects.lock);
पूर्ण

व्योम i915_gem_object_release_memory_region(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा पूर्णांकel_memory_region *mem = obj->mm.region;

	mutex_lock(&mem->objects.lock);
	list_del(&obj->mm.region_link);
	mutex_unlock(&mem->objects.lock);

	पूर्णांकel_memory_region_put(mem);
पूर्ण

काष्ठा drm_i915_gem_object *
i915_gem_object_create_region(काष्ठा पूर्णांकel_memory_region *mem,
			      resource_माप_प्रकार size,
			      अचिन्हित पूर्णांक flags)
अणु
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err;

	/*
	 * NB: Our use of resource_माप_प्रकार क्रम the size stems from using काष्ठा
	 * resource क्रम the mem->region. We might need to revisit this in the
	 * future.
	 */

	GEM_BUG_ON(flags & ~I915_BO_ALLOC_FLAGS);

	अगर (!mem)
		वापस ERR_PTR(-ENODEV);

	size = round_up(size, mem->min_page_size);

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_MIN_ALIGNMENT));

	अगर (i915_gem_object_size_2big(size))
		वापस ERR_PTR(-E2BIG);

	obj = i915_gem_object_alloc();
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	err = mem->ops->init_object(mem, obj, size, flags);
	अगर (err)
		जाओ err_object_मुक्त;

	trace_i915_gem_object_create(obj);
	वापस obj;

err_object_मुक्त:
	i915_gem_object_मुक्त(obj);
	वापस ERR_PTR(err);
पूर्ण
