<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>
#समावेश <linux/sort.h>

#समावेश "../i915_selftest.h"

#समावेश "mock_drm.h"
#समावेश "mock_gem_device.h"
#समावेश "mock_region.h"

#समावेश "gem/i915_gem_context.h"
#समावेश "gem/i915_gem_lmem.h"
#समावेश "gem/i915_gem_region.h"
#समावेश "gem/i915_gem_object_blt.h"
#समावेश "gem/selftests/igt_gem_utils.h"
#समावेश "gem/selftests/mock_context.h"
#समावेश "gt/intel_engine_user.h"
#समावेश "gt/intel_gt.h"
#समावेश "i915_memcpy.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/i915_random.h"

अटल व्योम बंद_objects(काष्ठा पूर्णांकel_memory_region *mem,
			  काष्ठा list_head *objects)
अणु
	काष्ठा drm_i915_निजी *i915 = mem->i915;
	काष्ठा drm_i915_gem_object *obj, *on;

	list_क्रम_each_entry_safe(obj, on, objects, st_link) अणु
		i915_gem_object_lock(obj, शून्य);
		अगर (i915_gem_object_has_pinned_pages(obj))
			i915_gem_object_unpin_pages(obj);
		/* No polluting the memory region between tests */
		__i915_gem_object_put_pages(obj);
		i915_gem_object_unlock(obj);
		list_del(&obj->st_link);
		i915_gem_object_put(obj);
	पूर्ण

	cond_resched();

	i915_gem_drain_मुक्तd_objects(i915);
पूर्ण

अटल पूर्णांक igt_mock_fill(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_memory_region *mem = arg;
	resource_माप_प्रकार total = resource_size(&mem->region);
	resource_माप_प्रकार page_size;
	resource_माप_प्रकार rem;
	अचिन्हित दीर्घ max_pages;
	अचिन्हित दीर्घ page_num;
	LIST_HEAD(objects);
	पूर्णांक err = 0;

	page_size = mem->mm.chunk_size;
	max_pages = भाग64_u64(total, page_size);
	rem = total;

	क्रम_each_prime_number_from(page_num, 1, max_pages) अणु
		resource_माप_प्रकार size = page_num * page_size;
		काष्ठा drm_i915_gem_object *obj;

		obj = i915_gem_object_create_region(mem, size, 0);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			अवरोध;
		पूर्ण

		err = i915_gem_object_pin_pages_unlocked(obj);
		अगर (err) अणु
			i915_gem_object_put(obj);
			अवरोध;
		पूर्ण

		list_add(&obj->st_link, &objects);
		rem -= size;
	पूर्ण

	अगर (err == -ENOMEM)
		err = 0;
	अगर (err == -ENXIO) अणु
		अगर (page_num * page_size <= rem) अणु
			pr_err("%s failed, space still left in region\n",
			       __func__);
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			err = 0;
		पूर्ण
	पूर्ण

	बंद_objects(mem, &objects);

	वापस err;
पूर्ण

अटल काष्ठा drm_i915_gem_object *
igt_object_create(काष्ठा पूर्णांकel_memory_region *mem,
		  काष्ठा list_head *objects,
		  u64 size,
		  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err;

	obj = i915_gem_object_create_region(mem, size, flags);
	अगर (IS_ERR(obj))
		वापस obj;

	err = i915_gem_object_pin_pages_unlocked(obj);
	अगर (err)
		जाओ put;

	list_add(&obj->st_link, objects);
	वापस obj;

put:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम igt_object_release(काष्ठा drm_i915_gem_object *obj)
अणु
	i915_gem_object_lock(obj, शून्य);
	i915_gem_object_unpin_pages(obj);
	__i915_gem_object_put_pages(obj);
	i915_gem_object_unlock(obj);
	list_del(&obj->st_link);
	i915_gem_object_put(obj);
पूर्ण

अटल bool is_contiguous(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा scatterlist *sg;
	dma_addr_t addr = -1;

	क्रम (sg = obj->mm.pages->sgl; sg; sg = sg_next(sg)) अणु
		अगर (addr != -1 && sg_dma_address(sg) != addr)
			वापस false;

		addr = sg_dma_address(sg) + sg_dma_len(sg);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक igt_mock_reserve(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_memory_region *mem = arg;
	resource_माप_प्रकार avail = resource_size(&mem->region);
	काष्ठा drm_i915_gem_object *obj;
	स्थिर u32 chunk_size = SZ_32M;
	u32 i, offset, count, *order;
	u64 allocated, cur_avail;
	I915_RND_STATE(prng);
	LIST_HEAD(objects);
	पूर्णांक err = 0;

	अगर (!list_empty(&mem->reserved)) अणु
		pr_err("%s region reserved list is not empty\n", __func__);
		वापस -EINVAL;
	पूर्ण

	count = avail / chunk_size;
	order = i915_अक्रमom_order(count, &prng);
	अगर (!order)
		वापस 0;

	/* Reserve a bunch of ranges within the region */
	क्रम (i = 0; i < count; ++i) अणु
		u64 start = order[i] * chunk_size;
		u64 size = i915_pअक्रमom_u32_max_state(chunk_size, &prng);

		/* Allow क्रम some really big holes */
		अगर (!size)
			जारी;

		size = round_up(size, PAGE_SIZE);
		offset = igt_अक्रमom_offset(&prng, 0, chunk_size, size,
					   PAGE_SIZE);

		err = पूर्णांकel_memory_region_reserve(mem, start + offset, size);
		अगर (err) अणु
			pr_err("%s failed to reserve range", __func__);
			जाओ out_बंद;
		पूर्ण

		/* XXX: maybe sanity check the block range here? */
		avail -= size;
	पूर्ण

	/* Try to see अगर we can allocate from the reमुख्यing space */
	allocated = 0;
	cur_avail = avail;
	करो अणु
		u32 size = i915_pअक्रमom_u32_max_state(cur_avail, &prng);

		size = max_t(u32, round_up(size, PAGE_SIZE), PAGE_SIZE);
		obj = igt_object_create(mem, &objects, size, 0);
		अगर (IS_ERR(obj)) अणु
			अगर (PTR_ERR(obj) == -ENXIO)
				अवरोध;

			err = PTR_ERR(obj);
			जाओ out_बंद;
		पूर्ण
		cur_avail -= size;
		allocated += size;
	पूर्ण जबतक (1);

	अगर (allocated != avail) अणु
		pr_err("%s mismatch between allocation and free space", __func__);
		err = -EINVAL;
	पूर्ण

out_बंद:
	kमुक्त(order);
	बंद_objects(mem, &objects);
	i915_buddy_मुक्त_list(&mem->mm, &mem->reserved);
	वापस err;
पूर्ण

अटल पूर्णांक igt_mock_contiguous(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_memory_region *mem = arg;
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित दीर्घ n_objects;
	LIST_HEAD(objects);
	LIST_HEAD(holes);
	I915_RND_STATE(prng);
	resource_माप_प्रकार total;
	resource_माप_प्रकार min;
	u64 target;
	पूर्णांक err = 0;

	total = resource_size(&mem->region);

	/* Min size */
	obj = igt_object_create(mem, &objects, mem->mm.chunk_size,
				I915_BO_ALLOC_CONTIGUOUS);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	अगर (!is_contiguous(obj)) अणु
		pr_err("%s min object spans disjoint sg entries\n", __func__);
		err = -EINVAL;
		जाओ err_बंद_objects;
	पूर्ण

	igt_object_release(obj);

	/* Max size */
	obj = igt_object_create(mem, &objects, total, I915_BO_ALLOC_CONTIGUOUS);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	अगर (!is_contiguous(obj)) अणु
		pr_err("%s max object spans disjoint sg entries\n", __func__);
		err = -EINVAL;
		जाओ err_बंद_objects;
	पूर्ण

	igt_object_release(obj);

	/* Internal fragmentation should not bleed पूर्णांकo the object size */
	target = i915_pअक्रमom_u64_state(&prng);
	भाग64_u64_rem(target, total, &target);
	target = round_up(target, PAGE_SIZE);
	target = max_t(u64, PAGE_SIZE, target);

	obj = igt_object_create(mem, &objects, target,
				I915_BO_ALLOC_CONTIGUOUS);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	अगर (obj->base.size != target) अणु
		pr_err("%s obj->base.size(%zx) != target(%llx)\n", __func__,
		       obj->base.size, target);
		err = -EINVAL;
		जाओ err_बंद_objects;
	पूर्ण

	अगर (!is_contiguous(obj)) अणु
		pr_err("%s object spans disjoint sg entries\n", __func__);
		err = -EINVAL;
		जाओ err_बंद_objects;
	पूर्ण

	igt_object_release(obj);

	/*
	 * Try to fragment the address space, such that half of it is मुक्त, but
	 * the max contiguous block size is SZ_64K.
	 */

	target = SZ_64K;
	n_objects = भाग64_u64(total, target);

	जबतक (n_objects--) अणु
		काष्ठा list_head *list;

		अगर (n_objects % 2)
			list = &holes;
		अन्यथा
			list = &objects;

		obj = igt_object_create(mem, list, target,
					I915_BO_ALLOC_CONTIGUOUS);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			जाओ err_बंद_objects;
		पूर्ण
	पूर्ण

	बंद_objects(mem, &holes);

	min = target;
	target = total >> 1;

	/* Make sure we can still allocate all the fragmented space */
	obj = igt_object_create(mem, &objects, target, 0);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ err_बंद_objects;
	पूर्ण

	igt_object_release(obj);

	/*
	 * Even though we have enough मुक्त space, we करोn't have a big enough
	 * contiguous block. Make sure that holds true.
	 */

	करो अणु
		bool should_fail = target > min;

		obj = igt_object_create(mem, &objects, target,
					I915_BO_ALLOC_CONTIGUOUS);
		अगर (should_fail != IS_ERR(obj)) अणु
			pr_err("%s target allocation(%llx) mismatch\n",
			       __func__, target);
			err = -EINVAL;
			जाओ err_बंद_objects;
		पूर्ण

		target >>= 1;
	पूर्ण जबतक (target >= mem->mm.chunk_size);

err_बंद_objects:
	list_splice_tail(&holes, &objects);
	बंद_objects(mem, &objects);
	वापस err;
पूर्ण

अटल पूर्णांक igt_mock_splपूर्णांकered_region(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_memory_region *mem = arg;
	काष्ठा drm_i915_निजी *i915 = mem->i915;
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित पूर्णांक expected_order;
	LIST_HEAD(objects);
	u64 size;
	पूर्णांक err = 0;

	/*
	 * Sanity check we can still allocate everything even अगर the
	 * mm.max_order != mm.size. i.e our starting address space size is not a
	 * घातer-of-two.
	 */

	size = (SZ_4G - 1) & PAGE_MASK;
	mem = mock_region_create(i915, 0, size, PAGE_SIZE, 0);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	अगर (mem->mm.size != size) अणु
		pr_err("%s size mismatch(%llu != %llu)\n",
		       __func__, mem->mm.size, size);
		err = -EINVAL;
		जाओ out_put;
	पूर्ण

	expected_order = get_order(roundकरोwn_घात_of_two(size));
	अगर (mem->mm.max_order != expected_order) अणु
		pr_err("%s order mismatch(%u != %u)\n",
		       __func__, mem->mm.max_order, expected_order);
		err = -EINVAL;
		जाओ out_put;
	पूर्ण

	obj = igt_object_create(mem, &objects, size, 0);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ out_बंद;
	पूर्ण

	बंद_objects(mem, &objects);

	/*
	 * While we should be able allocate everything without any flag
	 * restrictions, अगर we consider I915_BO_ALLOC_CONTIGUOUS then we are
	 * actually limited to the largest घातer-of-two क्रम the region size i.e
	 * max_order, due to the inner workings of the buddy allocator. So make
	 * sure that करोes indeed hold true.
	 */

	obj = igt_object_create(mem, &objects, size, I915_BO_ALLOC_CONTIGUOUS);
	अगर (!IS_ERR(obj)) अणु
		pr_err("%s too large contiguous allocation was not rejected\n",
		       __func__);
		err = -EINVAL;
		जाओ out_बंद;
	पूर्ण

	obj = igt_object_create(mem, &objects, roundकरोwn_घात_of_two(size),
				I915_BO_ALLOC_CONTIGUOUS);
	अगर (IS_ERR(obj)) अणु
		pr_err("%s largest possible contiguous allocation failed\n",
		       __func__);
		err = PTR_ERR(obj);
		जाओ out_बंद;
	पूर्ण

out_बंद:
	बंद_objects(mem, &objects);
out_put:
	पूर्णांकel_memory_region_put(mem);
	वापस err;
पूर्ण

#अगर_अघोषित SZ_8G
#घोषणा SZ_8G BIT_ULL(33)
#पूर्ण_अगर

अटल पूर्णांक igt_mock_max_segment(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक max_segment = i915_sg_segment_size();
	काष्ठा पूर्णांकel_memory_region *mem = arg;
	काष्ठा drm_i915_निजी *i915 = mem->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_buddy_block *block;
	काष्ठा scatterlist *sg;
	LIST_HEAD(objects);
	u64 size;
	पूर्णांक err = 0;

	/*
	 * While we may create very large contiguous blocks, we may need
	 * to अवरोध those करोwn क्रम consumption अन्यथाwhere. In particular,
	 * dma-mapping with scatterlist elements have an implicit limit of
	 * अच_पूर्णांक_उच्च on each element.
	 */

	size = SZ_8G;
	mem = mock_region_create(i915, 0, size, PAGE_SIZE, 0);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	obj = igt_object_create(mem, &objects, size, 0);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ out_put;
	पूर्ण

	size = 0;
	list_क्रम_each_entry(block, &obj->mm.blocks, link) अणु
		अगर (i915_buddy_block_size(&mem->mm, block) > size)
			size = i915_buddy_block_size(&mem->mm, block);
	पूर्ण
	अगर (size < max_segment) अणु
		pr_err("%s: Failed to create a huge contiguous block [> %u], largest block %lld\n",
		       __func__, max_segment, size);
		err = -EINVAL;
		जाओ out_बंद;
	पूर्ण

	क्रम (sg = obj->mm.pages->sgl; sg; sg = sg_next(sg)) अणु
		अगर (sg->length > max_segment) अणु
			pr_err("%s: Created an oversized scatterlist entry, %u > %u\n",
			       __func__, sg->length, max_segment);
			err = -EINVAL;
			जाओ out_बंद;
		पूर्ण
	पूर्ण

out_बंद:
	बंद_objects(mem, &objects);
out_put:
	पूर्णांकel_memory_region_put(mem);
	वापस err;
पूर्ण

अटल पूर्णांक igt_gpu_ग_लिखो_dw(काष्ठा पूर्णांकel_context *ce,
			    काष्ठा i915_vma *vma,
			    u32 dword,
			    u32 value)
अणु
	वापस igt_gpu_fill_dw(ce, vma, dword * माप(u32),
			       vma->size >> PAGE_SHIFT, value);
पूर्ण

अटल पूर्णांक igt_cpu_check(काष्ठा drm_i915_gem_object *obj, u32 dword, u32 val)
अणु
	अचिन्हित दीर्घ n = obj->base.size >> PAGE_SHIFT;
	u32 *ptr;
	पूर्णांक err;

	err = i915_gem_object_रुको(obj, 0, MAX_SCHEDULE_TIMEOUT);
	अगर (err)
		वापस err;

	ptr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);

	ptr += dword;
	जबतक (n--) अणु
		अगर (*ptr != val) अणु
			pr_err("base[%u]=%08x, val=%08x\n",
			       dword, *ptr, val);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		ptr += PAGE_SIZE / माप(*ptr);
	पूर्ण

	i915_gem_object_unpin_map(obj);
	वापस err;
पूर्ण

अटल पूर्णांक igt_gpu_ग_लिखो(काष्ठा i915_gem_context *ctx,
			 काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा i915_gem_engines *engines;
	काष्ठा i915_gem_engines_iter it;
	काष्ठा i915_address_space *vm;
	काष्ठा पूर्णांकel_context *ce;
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end_समय);
	अचिन्हित पूर्णांक count;
	काष्ठा i915_vma *vma;
	पूर्णांक *order;
	पूर्णांक i, n;
	पूर्णांक err = 0;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));

	n = 0;
	count = 0;
	क्रम_each_gem_engine(ce, i915_gem_context_lock_engines(ctx), it) अणु
		count++;
		अगर (!पूर्णांकel_engine_can_store_dword(ce->engine))
			जारी;

		vm = ce->vm;
		n++;
	पूर्ण
	i915_gem_context_unlock_engines(ctx);
	अगर (!n)
		वापस 0;

	order = i915_अक्रमom_order(count * count, &prng);
	अगर (!order)
		वापस -ENOMEM;

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ out_मुक्त;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ out_मुक्त;

	i = 0;
	engines = i915_gem_context_lock_engines(ctx);
	करो अणु
		u32 rng = pअक्रमom_u32_state(&prng);
		u32 dword = offset_in_page(rng) / 4;

		ce = engines->engines[order[i] % engines->num_engines];
		i = (i + 1) % (count * count);
		अगर (!ce || !पूर्णांकel_engine_can_store_dword(ce->engine))
			जारी;

		err = igt_gpu_ग_लिखो_dw(ce, vma, dword, rng);
		अगर (err)
			अवरोध;

		err = igt_cpu_check(obj, dword, rng);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
	i915_gem_context_unlock_engines(ctx);

out_मुक्त:
	kमुक्त(order);

	अगर (err == -ENOMEM)
		err = 0;

	वापस err;
पूर्ण

अटल पूर्णांक igt_lmem_create(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err = 0;

	obj = i915_gem_object_create_lmem(i915, PAGE_SIZE, 0);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	err = i915_gem_object_pin_pages_unlocked(obj);
	अगर (err)
		जाओ out_put;

	i915_gem_object_unpin_pages(obj);
out_put:
	i915_gem_object_put(obj);

	वापस err;
पूर्ण

अटल पूर्णांक igt_lmem_ग_लिखो_gpu(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_gem_context *ctx;
	काष्ठा file *file;
	I915_RND_STATE(prng);
	u32 sz;
	पूर्णांक err;

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ctx = live_context(i915, file);
	अगर (IS_ERR(ctx)) अणु
		err = PTR_ERR(ctx);
		जाओ out_file;
	पूर्ण

	sz = round_up(pअक्रमom_u32_state(&prng) % SZ_32M, PAGE_SIZE);

	obj = i915_gem_object_create_lmem(i915, sz, 0);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ out_file;
	पूर्ण

	err = i915_gem_object_pin_pages_unlocked(obj);
	अगर (err)
		जाओ out_put;

	err = igt_gpu_ग_लिखो(ctx, obj);
	अगर (err)
		pr_err("igt_gpu_write failed(%d)\n", err);

	i915_gem_object_unpin_pages(obj);
out_put:
	i915_gem_object_put(obj);
out_file:
	fput(file);
	वापस err;
पूर्ण

अटल काष्ठा पूर्णांकel_engine_cs *
अक्रमom_engine_class(काष्ठा drm_i915_निजी *i915,
		    अचिन्हित पूर्णांक class,
		    काष्ठा rnd_state *prng)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	अचिन्हित पूर्णांक count;

	count = 0;
	क्रम (engine = पूर्णांकel_engine_lookup_user(i915, class, 0);
	     engine && engine->uabi_class == class;
	     engine = rb_entry_safe(rb_next(&engine->uabi_node),
				    typeof(*engine), uabi_node))
		count++;

	count = i915_pअक्रमom_u32_max_state(count, prng);
	वापस पूर्णांकel_engine_lookup_user(i915, class, count);
पूर्ण

अटल पूर्णांक igt_lmem_ग_लिखो_cpu(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end_समय);
	u32 bytes[] = अणु
		0, /* rng placeholder */
		माप(u32),
		माप(u64),
		64, /* cl */
		PAGE_SIZE,
		PAGE_SIZE - माप(u32),
		PAGE_SIZE - माप(u64),
		PAGE_SIZE - 64,
	पूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine;
	u32 *vaddr;
	u32 sz;
	u32 i;
	पूर्णांक *order;
	पूर्णांक count;
	पूर्णांक err;

	engine = अक्रमom_engine_class(i915, I915_ENGINE_CLASS_COPY, &prng);
	अगर (!engine)
		वापस 0;

	pr_info("%s: using %s\n", __func__, engine->name);

	sz = round_up(pअक्रमom_u32_state(&prng) % SZ_32M, PAGE_SIZE);
	sz = max_t(u32, 2 * PAGE_SIZE, sz);

	obj = i915_gem_object_create_lmem(i915, sz, I915_BO_ALLOC_CONTIGUOUS);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	vaddr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		जाओ out_put;
	पूर्ण

	/* Put the pages पूर्णांकo a known state -- from the gpu क्रम added fun */
	पूर्णांकel_engine_pm_get(engine);
	err = i915_gem_object_fill_blt(obj, engine->kernel_context, 0xdeadbeaf);
	पूर्णांकel_engine_pm_put(engine);
	अगर (err)
		जाओ out_unpin;

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_set_to_wc_करोमुख्य(obj, true);
	i915_gem_object_unlock(obj);
	अगर (err)
		जाओ out_unpin;

	count = ARRAY_SIZE(bytes);
	order = i915_अक्रमom_order(count * count, &prng);
	अगर (!order) अणु
		err = -ENOMEM;
		जाओ out_unpin;
	पूर्ण

	/* A अक्रमom multiple of u32, picked between [64, PAGE_SIZE - 64] */
	bytes[0] = igt_अक्रमom_offset(&prng, 64, PAGE_SIZE - 64, 0, माप(u32));
	GEM_BUG_ON(!IS_ALIGNED(bytes[0], माप(u32)));

	i = 0;
	करो अणु
		u32 offset;
		u32 align;
		u32 dword;
		u32 size;
		u32 val;

		size = bytes[order[i] % count];
		i = (i + 1) % (count * count);

		align = bytes[order[i] % count];
		i = (i + 1) % (count * count);

		align = max_t(u32, माप(u32), roundकरोwn_घात_of_two(align));

		offset = igt_अक्रमom_offset(&prng, 0, obj->base.size,
					   size, align);

		val = pअक्रमom_u32_state(&prng);
		स_रखो32(vaddr + offset / माप(u32), val ^ 0xdeadbeaf,
			 size / माप(u32));

		/*
		 * Sample अक्रमom dw -- करोn't waste precious समय पढ़ोing every
		 * single dw.
		 */
		dword = igt_अक्रमom_offset(&prng, offset,
					  offset + size,
					  माप(u32), माप(u32));
		dword /= माप(u32);
		अगर (vaddr[dword] != (val ^ 0xdeadbeaf)) अणु
			pr_err("%s vaddr[%u]=%u, val=%u, size=%u, align=%u, offset=%u\n",
			       __func__, dword, vaddr[dword], val ^ 0xdeadbeaf,
			       size, align, offset);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));

out_unpin:
	i915_gem_object_unpin_map(obj);
out_put:
	i915_gem_object_put(obj);

	वापस err;
पूर्ण

अटल स्थिर अक्षर *repr_type(u32 type)
अणु
	चयन (type) अणु
	हाल I915_MAP_WB:
		वापस "WB";
	हाल I915_MAP_WC:
		वापस "WC";
	पूर्ण

	वापस "";
पूर्ण

अटल काष्ठा drm_i915_gem_object *
create_region_क्रम_mapping(काष्ठा पूर्णांकel_memory_region *mr, u64 size, u32 type,
			  व्योम **out_addr)
अणु
	काष्ठा drm_i915_gem_object *obj;
	व्योम *addr;

	obj = i915_gem_object_create_region(mr, size, 0);
	अगर (IS_ERR(obj)) अणु
		अगर (PTR_ERR(obj) == -ENOSPC) /* Stolen memory */
			वापस ERR_PTR(-ENODEV);
		वापस obj;
	पूर्ण

	addr = i915_gem_object_pin_map_unlocked(obj, type);
	अगर (IS_ERR(addr)) अणु
		i915_gem_object_put(obj);
		अगर (PTR_ERR(addr) == -ENXIO)
			वापस ERR_PTR(-ENODEV);
		वापस addr;
	पूर्ण

	*out_addr = addr;
	वापस obj;
पूर्ण

अटल पूर्णांक wrap_kसमय_compare(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर kसमय_प्रकार *a = A, *b = B;

	वापस kसमय_compare(*a, *b);
पूर्ण

अटल व्योम igt_स_नकल_दीर्घ(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ *पंचांगp = dst;
	स्थिर अचिन्हित दीर्घ *s = src;

	size = size / माप(अचिन्हित दीर्घ);
	जबतक (size--)
		*पंचांगp++ = *s++;
पूर्ण

अटल अंतरभूत व्योम igt_स_नकल(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	स_नकल(dst, src, size);
पूर्ण

अटल अंतरभूत व्योम igt_स_नकल_from_wc(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	i915_स_नकल_from_wc(dst, src, size);
पूर्ण

अटल पूर्णांक _perf_स_नकल(काष्ठा पूर्णांकel_memory_region *src_mr,
			काष्ठा पूर्णांकel_memory_region *dst_mr,
			u64 size, u32 src_type, u32 dst_type)
अणु
	काष्ठा drm_i915_निजी *i915 = src_mr->i915;
	स्थिर काष्ठा अणु
		स्थिर अक्षर *name;
		व्योम (*copy)(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size);
		bool skip;
	पूर्ण tests[] = अणु
		अणु
			"memcpy",
			igt_स_नकल,
		पूर्ण,
		अणु
			"memcpy_long",
			igt_स_नकल_दीर्घ,
		पूर्ण,
		अणु
			"memcpy_from_wc",
			igt_स_नकल_from_wc,
			!i915_has_स_नकल_from_wc(),
		पूर्ण,
	पूर्ण;
	काष्ठा drm_i915_gem_object *src, *dst;
	व्योम *src_addr, *dst_addr;
	पूर्णांक ret = 0;
	पूर्णांक i;

	src = create_region_क्रम_mapping(src_mr, size, src_type, &src_addr);
	अगर (IS_ERR(src)) अणु
		ret = PTR_ERR(src);
		जाओ out;
	पूर्ण

	dst = create_region_क्रम_mapping(dst_mr, size, dst_type, &dst_addr);
	अगर (IS_ERR(dst)) अणु
		ret = PTR_ERR(dst);
		जाओ out_unpin_src;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tests); ++i) अणु
		kसमय_प्रकार t[5];
		पूर्णांक pass;

		अगर (tests[i].skip)
			जारी;

		क्रम (pass = 0; pass < ARRAY_SIZE(t); pass++) अणु
			kसमय_प्रकार t0, t1;

			t0 = kसमय_get();

			tests[i].copy(dst_addr, src_addr, size);

			t1 = kसमय_get();
			t[pass] = kसमय_sub(t1, t0);
		पूर्ण

		sort(t, ARRAY_SIZE(t), माप(*t), wrap_kसमय_compare, शून्य);
		अगर (t[0] <= 0) अणु
			/* ignore the impossible to protect our sanity */
			pr_debug("Skipping %s src(%s, %s) -> dst(%s, %s) %14s %4lluKiB copy, unstable measurement [%lld, %lld]\n",
				 __func__,
				 src_mr->name, repr_type(src_type),
				 dst_mr->name, repr_type(dst_type),
				 tests[i].name, size >> 10,
				 t[0], t[4]);
			जारी;
		पूर्ण

		pr_info("%s src(%s, %s) -> dst(%s, %s) %14s %4llu KiB copy: %5lld MiB/s\n",
			__func__,
			src_mr->name, repr_type(src_type),
			dst_mr->name, repr_type(dst_type),
			tests[i].name, size >> 10,
			भाग64_u64(mul_u32_u32(4 * size,
					      1000 * 1000 * 1000),
				  t[1] + 2 * t[2] + t[3]) >> 20);

		cond_resched();
	पूर्ण

	i915_gem_object_unpin_map(dst);
	i915_gem_object_put(dst);
out_unpin_src:
	i915_gem_object_unpin_map(src);
	i915_gem_object_put(src);

	i915_gem_drain_मुक्तd_objects(i915);
out:
	अगर (ret == -ENODEV)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक perf_स_नकल(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	अटल स्थिर u32 types[] = अणु
		I915_MAP_WB,
		I915_MAP_WC,
	पूर्ण;
	अटल स्थिर u32 sizes[] = अणु
		SZ_4K,
		SZ_64K,
		SZ_4M,
	पूर्ण;
	काष्ठा पूर्णांकel_memory_region *src_mr, *dst_mr;
	पूर्णांक src_id, dst_id;
	पूर्णांक i, j, k;
	पूर्णांक ret;

	क्रम_each_memory_region(src_mr, i915, src_id) अणु
		क्रम_each_memory_region(dst_mr, i915, dst_id) अणु
			क्रम (i = 0; i < ARRAY_SIZE(sizes); ++i) अणु
				क्रम (j = 0; j < ARRAY_SIZE(types); ++j) अणु
					क्रम (k = 0; k < ARRAY_SIZE(types); ++k) अणु
						ret = _perf_स_नकल(src_mr,
								   dst_mr,
								   sizes[i],
								   types[j],
								   types[k]);
						अगर (ret)
							वापस ret;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_memory_region_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_mock_reserve),
		SUBTEST(igt_mock_fill),
		SUBTEST(igt_mock_contiguous),
		SUBTEST(igt_mock_splपूर्णांकered_region),
		SUBTEST(igt_mock_max_segment),
	पूर्ण;
	काष्ठा पूर्णांकel_memory_region *mem;
	काष्ठा drm_i915_निजी *i915;
	पूर्णांक err;

	i915 = mock_gem_device();
	अगर (!i915)
		वापस -ENOMEM;

	mem = mock_region_create(i915, 0, SZ_2G, I915_GTT_PAGE_SIZE_4K, 0);
	अगर (IS_ERR(mem)) अणु
		pr_err("failed to create memory region\n");
		err = PTR_ERR(mem);
		जाओ out_unref;
	पूर्ण

	err = i915_subtests(tests, mem);

	पूर्णांकel_memory_region_put(mem);
out_unref:
	mock_destroy_device(i915);
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_memory_region_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_lmem_create),
		SUBTEST(igt_lmem_ग_लिखो_cpu),
		SUBTEST(igt_lmem_ग_लिखो_gpu),
	पूर्ण;

	अगर (!HAS_LMEM(i915)) अणु
		pr_info("device lacks LMEM support, skipping\n");
		वापस 0;
	पूर्ण

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_live_subtests(tests, i915);
पूर्ण

पूर्णांक पूर्णांकel_memory_region_perf_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(perf_स_नकल),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_live_subtests(tests, i915);
पूर्ण
