<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <linux/list_sort.h>
#समावेश <linux/prime_numbers.h>

#समावेश "gem/i915_gem_context.h"
#समावेश "gem/selftests/mock_context.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_gpu_commands.h"

#समावेश "i915_random.h"
#समावेश "i915_selftest.h"

#समावेश "mock_drm.h"
#समावेश "mock_gem_device.h"
#समावेश "mock_gtt.h"
#समावेश "igt_flush_test.h"

अटल व्योम cleanup_मुक्तd_objects(काष्ठा drm_i915_निजी *i915)
अणु
	i915_gem_drain_मुक्तd_objects(i915);
पूर्ण

अटल व्योम fake_मुक्त_pages(काष्ठा drm_i915_gem_object *obj,
			    काष्ठा sg_table *pages)
अणु
	sg_मुक्त_table(pages);
	kमुक्त(pages);
पूर्ण

अटल पूर्णांक fake_get_pages(काष्ठा drm_i915_gem_object *obj)
अणु
#घोषणा GFP (GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY)
#घोषणा PFN_BIAS 0x1000
	काष्ठा sg_table *pages;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक sg_page_sizes;
	typeof(obj->base.size) rem;

	pages = kदो_स्मृति(माप(*pages), GFP);
	अगर (!pages)
		वापस -ENOMEM;

	rem = round_up(obj->base.size, BIT(31)) >> 31;
	अगर (sg_alloc_table(pages, rem, GFP)) अणु
		kमुक्त(pages);
		वापस -ENOMEM;
	पूर्ण

	sg_page_sizes = 0;
	rem = obj->base.size;
	क्रम (sg = pages->sgl; sg; sg = sg_next(sg)) अणु
		अचिन्हित दीर्घ len = min_t(typeof(rem), rem, BIT(31));

		GEM_BUG_ON(!len);
		sg_set_page(sg, pfn_to_page(PFN_BIAS), len, 0);
		sg_dma_address(sg) = page_to_phys(sg_page(sg));
		sg_dma_len(sg) = len;
		sg_page_sizes |= len;

		rem -= len;
	पूर्ण
	GEM_BUG_ON(rem);

	__i915_gem_object_set_pages(obj, pages, sg_page_sizes);

	वापस 0;
#अघोषित GFP
पूर्ण

अटल व्योम fake_put_pages(काष्ठा drm_i915_gem_object *obj,
			   काष्ठा sg_table *pages)
अणु
	fake_मुक्त_pages(obj, pages);
	obj->mm.dirty = false;
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops fake_ops = अणु
	.name = "fake-gem",
	.flags = I915_GEM_OBJECT_IS_SHRINKABLE,
	.get_pages = fake_get_pages,
	.put_pages = fake_put_pages,
पूर्ण;

अटल काष्ठा drm_i915_gem_object *
fake_dma_object(काष्ठा drm_i915_निजी *i915, u64 size)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_gem_object *obj;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE));

	अगर (overflows_type(size, obj->base.size))
		वापस ERR_PTR(-E2BIG);

	obj = i915_gem_object_alloc();
	अगर (!obj)
		जाओ err;

	drm_gem_निजी_object_init(&i915->drm, &obj->base, size);
	i915_gem_object_init(obj, &fake_ops, &lock_class, 0);

	i915_gem_object_set_अस्थिर(obj);

	obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_CPU;
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU;
	obj->cache_level = I915_CACHE_NONE;

	/* Pपुनः_स्मृतिate the "backing storage" */
	अगर (i915_gem_object_pin_pages_unlocked(obj))
		जाओ err_obj;

	i915_gem_object_unpin_pages(obj);
	वापस obj;

err_obj:
	i915_gem_object_put(obj);
err:
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक igt_ppgtt_alloc(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *dev_priv = arg;
	काष्ठा i915_ppgtt *ppgtt;
	काष्ठा i915_gem_ww_ctx ww;
	u64 size, last, limit;
	पूर्णांक err = 0;

	/* Allocate a ppggt and try to fill the entire range */

	अगर (!HAS_PPGTT(dev_priv))
		वापस 0;

	ppgtt = i915_ppgtt_create(&dev_priv->gt);
	अगर (IS_ERR(ppgtt))
		वापस PTR_ERR(ppgtt);

	अगर (!ppgtt->vm.allocate_va_range)
		जाओ err_ppgtt_cleanup;

	/*
	 * While we only allocate the page tables here and so we could
	 * address a much larger GTT than we could actually fit पूर्णांकo
	 * RAM, a practical limit is the amount of physical pages in the प्रणाली.
	 * This should ensure that we करो not run पूर्णांकo the oomसमाप्तer during
	 * the test and take करोwn the machine wilfully.
	 */
	limit = totalram_pages() << PAGE_SHIFT;
	limit = min(ppgtt->vm.total, limit);

	i915_gem_ww_ctx_init(&ww, false);
retry:
	err = i915_vm_lock_objects(&ppgtt->vm, &ww);
	अगर (err)
		जाओ err_ppgtt_cleanup;

	/* Check we can allocate the entire range */
	क्रम (size = 4096; size <= limit; size <<= 2) अणु
		काष्ठा i915_vm_pt_stash stash = अणुपूर्ण;

		err = i915_vm_alloc_pt_stash(&ppgtt->vm, &stash, size);
		अगर (err)
			जाओ err_ppgtt_cleanup;

		err = i915_vm_pin_pt_stash(&ppgtt->vm, &stash);
		अगर (err) अणु
			i915_vm_मुक्त_pt_stash(&ppgtt->vm, &stash);
			जाओ err_ppgtt_cleanup;
		पूर्ण

		ppgtt->vm.allocate_va_range(&ppgtt->vm, &stash, 0, size);
		cond_resched();

		ppgtt->vm.clear_range(&ppgtt->vm, 0, size);

		i915_vm_मुक्त_pt_stash(&ppgtt->vm, &stash);
	पूर्ण

	/* Check we can incrementally allocate the entire range */
	क्रम (last = 0, size = 4096; size <= limit; last = size, size <<= 2) अणु
		काष्ठा i915_vm_pt_stash stash = अणुपूर्ण;

		err = i915_vm_alloc_pt_stash(&ppgtt->vm, &stash, size - last);
		अगर (err)
			जाओ err_ppgtt_cleanup;

		err = i915_vm_pin_pt_stash(&ppgtt->vm, &stash);
		अगर (err) अणु
			i915_vm_मुक्त_pt_stash(&ppgtt->vm, &stash);
			जाओ err_ppgtt_cleanup;
		पूर्ण

		ppgtt->vm.allocate_va_range(&ppgtt->vm, &stash,
					    last, size - last);
		cond_resched();

		i915_vm_मुक्त_pt_stash(&ppgtt->vm, &stash);
	पूर्ण

err_ppgtt_cleanup:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);

	i915_vm_put(&ppgtt->vm);
	वापस err;
पूर्ण

अटल पूर्णांक lowlevel_hole(काष्ठा i915_address_space *vm,
			 u64 hole_start, u64 hole_end,
			 अचिन्हित दीर्घ end_समय)
अणु
	I915_RND_STATE(seed_prng);
	काष्ठा i915_vma *mock_vma;
	अचिन्हित पूर्णांक size;

	mock_vma = kzalloc(माप(*mock_vma), GFP_KERNEL);
	अगर (!mock_vma)
		वापस -ENOMEM;

	/* Keep creating larger objects until one cannot fit पूर्णांकo the hole */
	क्रम (size = 12; (hole_end - hole_start) >> size; size++) अणु
		I915_RND_SUBSTATE(prng, seed_prng);
		काष्ठा drm_i915_gem_object *obj;
		अचिन्हित पूर्णांक *order, count, n;
		u64 hole_size;

		hole_size = (hole_end - hole_start) >> size;
		अगर (hole_size > KMALLOC_MAX_SIZE / माप(u32))
			hole_size = KMALLOC_MAX_SIZE / माप(u32);
		count = hole_size >> 1;
		अगर (!count) अणु
			pr_debug("%s: hole is too small [%llx - %llx] >> %d: %lld\n",
				 __func__, hole_start, hole_end, size, hole_size);
			अवरोध;
		पूर्ण

		करो अणु
			order = i915_अक्रमom_order(count, &prng);
			अगर (order)
				अवरोध;
		पूर्ण जबतक (count >>= 1);
		अगर (!count) अणु
			kमुक्त(mock_vma);
			वापस -ENOMEM;
		पूर्ण
		GEM_BUG_ON(!order);

		GEM_BUG_ON(count * BIT_ULL(size) > vm->total);
		GEM_BUG_ON(hole_start + count * BIT_ULL(size) > hole_end);

		/* Ignore allocation failures (i.e. करोn't report them as
		 * a test failure) as we are purposefully allocating very
		 * large objects without checking that we have sufficient
		 * memory. We expect to hit -ENOMEM.
		 */

		obj = fake_dma_object(vm->i915, BIT_ULL(size));
		अगर (IS_ERR(obj)) अणु
			kमुक्त(order);
			अवरोध;
		पूर्ण

		GEM_BUG_ON(obj->base.size != BIT_ULL(size));

		अगर (i915_gem_object_pin_pages_unlocked(obj)) अणु
			i915_gem_object_put(obj);
			kमुक्त(order);
			अवरोध;
		पूर्ण

		क्रम (n = 0; n < count; n++) अणु
			u64 addr = hole_start + order[n] * BIT_ULL(size);
			पूर्णांकel_wakeref_t wakeref;

			GEM_BUG_ON(addr + BIT_ULL(size) > vm->total);

			अगर (igt_समयout(end_समय,
					"%s timed out before %d/%d\n",
					__func__, n, count)) अणु
				hole_end = hole_start; /* quit */
				अवरोध;
			पूर्ण

			अगर (vm->allocate_va_range) अणु
				काष्ठा i915_vm_pt_stash stash = अणुपूर्ण;
				काष्ठा i915_gem_ww_ctx ww;
				पूर्णांक err;

				i915_gem_ww_ctx_init(&ww, false);
retry:
				err = i915_vm_lock_objects(vm, &ww);
				अगर (err)
					जाओ alloc_vm_end;

				err = -ENOMEM;
				अगर (i915_vm_alloc_pt_stash(vm, &stash,
							   BIT_ULL(size)))
					जाओ alloc_vm_end;

				err = i915_vm_pin_pt_stash(vm, &stash);
				अगर (!err)
					vm->allocate_va_range(vm, &stash,
							      addr, BIT_ULL(size));

				i915_vm_मुक्त_pt_stash(vm, &stash);
alloc_vm_end:
				अगर (err == -EDEADLK) अणु
					err = i915_gem_ww_ctx_backoff(&ww);
					अगर (!err)
						जाओ retry;
				पूर्ण
				i915_gem_ww_ctx_fini(&ww);

				अगर (err)
					अवरोध;
			पूर्ण

			mock_vma->pages = obj->mm.pages;
			mock_vma->node.size = BIT_ULL(size);
			mock_vma->node.start = addr;

			with_पूर्णांकel_runसमय_pm(vm->gt->uncore->rpm, wakeref)
				vm->insert_entries(vm, mock_vma,
						   I915_CACHE_NONE, 0);
		पूर्ण
		count = n;

		i915_अक्रमom_reorder(order, count, &prng);
		क्रम (n = 0; n < count; n++) अणु
			u64 addr = hole_start + order[n] * BIT_ULL(size);
			पूर्णांकel_wakeref_t wakeref;

			GEM_BUG_ON(addr + BIT_ULL(size) > vm->total);
			with_पूर्णांकel_runसमय_pm(vm->gt->uncore->rpm, wakeref)
				vm->clear_range(vm, addr, BIT_ULL(size));
		पूर्ण

		i915_gem_object_unpin_pages(obj);
		i915_gem_object_put(obj);

		kमुक्त(order);

		cleanup_मुक्तd_objects(vm->i915);
	पूर्ण

	kमुक्त(mock_vma);
	वापस 0;
पूर्ण

अटल व्योम बंद_object_list(काष्ठा list_head *objects,
			      काष्ठा i915_address_space *vm)
अणु
	काष्ठा drm_i915_gem_object *obj, *on;
	पूर्णांक ignored;

	list_क्रम_each_entry_safe(obj, on, objects, st_link) अणु
		काष्ठा i915_vma *vma;

		vma = i915_vma_instance(obj, vm, शून्य);
		अगर (!IS_ERR(vma))
			ignored = i915_vma_unbind(vma);

		list_del(&obj->st_link);
		i915_gem_object_put(obj);
	पूर्ण
पूर्ण

अटल पूर्णांक fill_hole(काष्ठा i915_address_space *vm,
		     u64 hole_start, u64 hole_end,
		     अचिन्हित दीर्घ end_समय)
अणु
	स्थिर u64 hole_size = hole_end - hole_start;
	काष्ठा drm_i915_gem_object *obj;
	स्थिर अचिन्हित दीर्घ max_pages =
		min_t(u64, अच_दीर्घ_उच्च - 1, hole_size/2 >> PAGE_SHIFT);
	स्थिर अचिन्हित दीर्घ max_step = max(पूर्णांक_वर्ग_मूल(max_pages), 2UL);
	अचिन्हित दीर्घ npages, prime, flags;
	काष्ठा i915_vma *vma;
	LIST_HEAD(objects);
	पूर्णांक err;

	/* Try binding many VMA working inwards from either edge */

	flags = PIN_OFFSET_FIXED | PIN_USER;
	अगर (i915_is_ggtt(vm))
		flags |= PIN_GLOBAL;

	क्रम_each_prime_number_from(prime, 2, max_step) अणु
		क्रम (npages = 1; npages <= max_pages; npages *= prime) अणु
			स्थिर u64 full_size = npages << PAGE_SHIFT;
			स्थिर काष्ठा अणु
				स्थिर अक्षर *name;
				u64 offset;
				पूर्णांक step;
			पूर्ण phases[] = अणु
				अणु "top-down", hole_end, -1, पूर्ण,
				अणु "bottom-up", hole_start, 1, पूर्ण,
				अणु पूर्ण
			पूर्ण, *p;

			obj = fake_dma_object(vm->i915, full_size);
			अगर (IS_ERR(obj))
				अवरोध;

			list_add(&obj->st_link, &objects);

			/* Align dअगरfering sized objects against the edges, and
			 * check we करोn't walk off पूर्णांकo the व्योम when binding
			 * them पूर्णांकo the GTT.
			 */
			क्रम (p = phases; p->name; p++) अणु
				u64 offset;

				offset = p->offset;
				list_क्रम_each_entry(obj, &objects, st_link) अणु
					vma = i915_vma_instance(obj, vm, शून्य);
					अगर (IS_ERR(vma))
						जारी;

					अगर (p->step < 0) अणु
						अगर (offset < hole_start + obj->base.size)
							अवरोध;
						offset -= obj->base.size;
					पूर्ण

					err = i915_vma_pin(vma, 0, 0, offset | flags);
					अगर (err) अणु
						pr_err("%s(%s) pin (forward) failed with err=%d on size=%lu pages (prime=%lu), offset=%llx\n",
						       __func__, p->name, err, npages, prime, offset);
						जाओ err;
					पूर्ण

					अगर (!drm_mm_node_allocated(&vma->node) ||
					    i915_vma_misplaced(vma, 0, 0, offset | flags)) अणु
						pr_err("%s(%s) (forward) insert failed: vma.node=%llx + %llx [allocated? %d], expected offset %llx\n",
						       __func__, p->name, vma->node.start, vma->node.size, drm_mm_node_allocated(&vma->node),
						       offset);
						err = -EINVAL;
						जाओ err;
					पूर्ण

					i915_vma_unpin(vma);

					अगर (p->step > 0) अणु
						अगर (offset + obj->base.size > hole_end)
							अवरोध;
						offset += obj->base.size;
					पूर्ण
				पूर्ण

				offset = p->offset;
				list_क्रम_each_entry(obj, &objects, st_link) अणु
					vma = i915_vma_instance(obj, vm, शून्य);
					अगर (IS_ERR(vma))
						जारी;

					अगर (p->step < 0) अणु
						अगर (offset < hole_start + obj->base.size)
							अवरोध;
						offset -= obj->base.size;
					पूर्ण

					अगर (!drm_mm_node_allocated(&vma->node) ||
					    i915_vma_misplaced(vma, 0, 0, offset | flags)) अणु
						pr_err("%s(%s) (forward) moved vma.node=%llx + %llx, expected offset %llx\n",
						       __func__, p->name, vma->node.start, vma->node.size,
						       offset);
						err = -EINVAL;
						जाओ err;
					पूर्ण

					err = i915_vma_unbind(vma);
					अगर (err) अणु
						pr_err("%s(%s) (forward) unbind of vma.node=%llx + %llx failed with err=%d\n",
						       __func__, p->name, vma->node.start, vma->node.size,
						       err);
						जाओ err;
					पूर्ण

					अगर (p->step > 0) अणु
						अगर (offset + obj->base.size > hole_end)
							अवरोध;
						offset += obj->base.size;
					पूर्ण
				पूर्ण

				offset = p->offset;
				list_क्रम_each_entry_reverse(obj, &objects, st_link) अणु
					vma = i915_vma_instance(obj, vm, शून्य);
					अगर (IS_ERR(vma))
						जारी;

					अगर (p->step < 0) अणु
						अगर (offset < hole_start + obj->base.size)
							अवरोध;
						offset -= obj->base.size;
					पूर्ण

					err = i915_vma_pin(vma, 0, 0, offset | flags);
					अगर (err) अणु
						pr_err("%s(%s) pin (backward) failed with err=%d on size=%lu pages (prime=%lu), offset=%llx\n",
						       __func__, p->name, err, npages, prime, offset);
						जाओ err;
					पूर्ण

					अगर (!drm_mm_node_allocated(&vma->node) ||
					    i915_vma_misplaced(vma, 0, 0, offset | flags)) अणु
						pr_err("%s(%s) (backward) insert failed: vma.node=%llx + %llx [allocated? %d], expected offset %llx\n",
						       __func__, p->name, vma->node.start, vma->node.size, drm_mm_node_allocated(&vma->node),
						       offset);
						err = -EINVAL;
						जाओ err;
					पूर्ण

					i915_vma_unpin(vma);

					अगर (p->step > 0) अणु
						अगर (offset + obj->base.size > hole_end)
							अवरोध;
						offset += obj->base.size;
					पूर्ण
				पूर्ण

				offset = p->offset;
				list_क्रम_each_entry_reverse(obj, &objects, st_link) अणु
					vma = i915_vma_instance(obj, vm, शून्य);
					अगर (IS_ERR(vma))
						जारी;

					अगर (p->step < 0) अणु
						अगर (offset < hole_start + obj->base.size)
							अवरोध;
						offset -= obj->base.size;
					पूर्ण

					अगर (!drm_mm_node_allocated(&vma->node) ||
					    i915_vma_misplaced(vma, 0, 0, offset | flags)) अणु
						pr_err("%s(%s) (backward) moved vma.node=%llx + %llx [allocated? %d], expected offset %llx\n",
						       __func__, p->name, vma->node.start, vma->node.size, drm_mm_node_allocated(&vma->node),
						       offset);
						err = -EINVAL;
						जाओ err;
					पूर्ण

					err = i915_vma_unbind(vma);
					अगर (err) अणु
						pr_err("%s(%s) (backward) unbind of vma.node=%llx + %llx failed with err=%d\n",
						       __func__, p->name, vma->node.start, vma->node.size,
						       err);
						जाओ err;
					पूर्ण

					अगर (p->step > 0) अणु
						अगर (offset + obj->base.size > hole_end)
							अवरोध;
						offset += obj->base.size;
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (igt_समयout(end_समय, "%s timed out (npages=%lu, prime=%lu)\n",
					__func__, npages, prime)) अणु
				err = -EINTR;
				जाओ err;
			पूर्ण
		पूर्ण

		बंद_object_list(&objects, vm);
		cleanup_मुक्तd_objects(vm->i915);
	पूर्ण

	वापस 0;

err:
	बंद_object_list(&objects, vm);
	वापस err;
पूर्ण

अटल पूर्णांक walk_hole(काष्ठा i915_address_space *vm,
		     u64 hole_start, u64 hole_end,
		     अचिन्हित दीर्घ end_समय)
अणु
	स्थिर u64 hole_size = hole_end - hole_start;
	स्थिर अचिन्हित दीर्घ max_pages =
		min_t(u64, अच_दीर्घ_उच्च - 1, hole_size >> PAGE_SHIFT);
	अचिन्हित दीर्घ flags;
	u64 size;

	/* Try binding a single VMA in dअगरferent positions within the hole */

	flags = PIN_OFFSET_FIXED | PIN_USER;
	अगर (i915_is_ggtt(vm))
		flags |= PIN_GLOBAL;

	क्रम_each_prime_number_from(size, 1, max_pages) अणु
		काष्ठा drm_i915_gem_object *obj;
		काष्ठा i915_vma *vma;
		u64 addr;
		पूर्णांक err = 0;

		obj = fake_dma_object(vm->i915, size << PAGE_SHIFT);
		अगर (IS_ERR(obj))
			अवरोध;

		vma = i915_vma_instance(obj, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ err_put;
		पूर्ण

		क्रम (addr = hole_start;
		     addr + obj->base.size < hole_end;
		     addr += obj->base.size) अणु
			err = i915_vma_pin(vma, 0, 0, addr | flags);
			अगर (err) अणु
				pr_err("%s bind failed at %llx + %llx [hole %llx- %llx] with err=%d\n",
				       __func__, addr, vma->size,
				       hole_start, hole_end, err);
				जाओ err_put;
			पूर्ण
			i915_vma_unpin(vma);

			अगर (!drm_mm_node_allocated(&vma->node) ||
			    i915_vma_misplaced(vma, 0, 0, addr | flags)) अणु
				pr_err("%s incorrect at %llx + %llx\n",
				       __func__, addr, vma->size);
				err = -EINVAL;
				जाओ err_put;
			पूर्ण

			err = i915_vma_unbind(vma);
			अगर (err) अणु
				pr_err("%s unbind failed at %llx + %llx  with err=%d\n",
				       __func__, addr, vma->size, err);
				जाओ err_put;
			पूर्ण

			GEM_BUG_ON(drm_mm_node_allocated(&vma->node));

			अगर (igt_समयout(end_समय,
					"%s timed out at %llx\n",
					__func__, addr)) अणु
				err = -EINTR;
				जाओ err_put;
			पूर्ण
		पूर्ण

err_put:
		i915_gem_object_put(obj);
		अगर (err)
			वापस err;

		cleanup_मुक्तd_objects(vm->i915);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pot_hole(काष्ठा i915_address_space *vm,
		    u64 hole_start, u64 hole_end,
		    अचिन्हित दीर्घ end_समय)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pot;
	पूर्णांक err = 0;

	flags = PIN_OFFSET_FIXED | PIN_USER;
	अगर (i915_is_ggtt(vm))
		flags |= PIN_GLOBAL;

	obj = i915_gem_object_create_पूर्णांकernal(vm->i915, 2 * I915_GTT_PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_obj;
	पूर्ण

	/* Insert a pair of pages across every pot boundary within the hole */
	क्रम (pot = fls64(hole_end - 1) - 1;
	     pot > ilog2(2 * I915_GTT_PAGE_SIZE);
	     pot--) अणु
		u64 step = BIT_ULL(pot);
		u64 addr;

		क्रम (addr = round_up(hole_start + I915_GTT_PAGE_SIZE, step) - I915_GTT_PAGE_SIZE;
		     addr <= round_करोwn(hole_end - 2*I915_GTT_PAGE_SIZE, step) - I915_GTT_PAGE_SIZE;
		     addr += step) अणु
			err = i915_vma_pin(vma, 0, 0, addr | flags);
			अगर (err) अणु
				pr_err("%s failed to pin object at %llx in hole [%llx - %llx], with err=%d\n",
				       __func__,
				       addr,
				       hole_start, hole_end,
				       err);
				जाओ err_obj;
			पूर्ण

			अगर (!drm_mm_node_allocated(&vma->node) ||
			    i915_vma_misplaced(vma, 0, 0, addr | flags)) अणु
				pr_err("%s incorrect at %llx + %llx\n",
				       __func__, addr, vma->size);
				i915_vma_unpin(vma);
				err = i915_vma_unbind(vma);
				err = -EINVAL;
				जाओ err_obj;
			पूर्ण

			i915_vma_unpin(vma);
			err = i915_vma_unbind(vma);
			GEM_BUG_ON(err);
		पूर्ण

		अगर (igt_समयout(end_समय,
				"%s timed out after %d/%d\n",
				__func__, pot, fls64(hole_end - 1) - 1)) अणु
			err = -EINTR;
			जाओ err_obj;
		पूर्ण
	पूर्ण

err_obj:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल पूर्णांक drunk_hole(काष्ठा i915_address_space *vm,
		      u64 hole_start, u64 hole_end,
		      अचिन्हित दीर्घ end_समय)
अणु
	I915_RND_STATE(prng);
	अचिन्हित पूर्णांक size;
	अचिन्हित दीर्घ flags;

	flags = PIN_OFFSET_FIXED | PIN_USER;
	अगर (i915_is_ggtt(vm))
		flags |= PIN_GLOBAL;

	/* Keep creating larger objects until one cannot fit पूर्णांकo the hole */
	क्रम (size = 12; (hole_end - hole_start) >> size; size++) अणु
		काष्ठा drm_i915_gem_object *obj;
		अचिन्हित पूर्णांक *order, count, n;
		काष्ठा i915_vma *vma;
		u64 hole_size;
		पूर्णांक err = -ENODEV;

		hole_size = (hole_end - hole_start) >> size;
		अगर (hole_size > KMALLOC_MAX_SIZE / माप(u32))
			hole_size = KMALLOC_MAX_SIZE / माप(u32);
		count = hole_size >> 1;
		अगर (!count) अणु
			pr_debug("%s: hole is too small [%llx - %llx] >> %d: %lld\n",
				 __func__, hole_start, hole_end, size, hole_size);
			अवरोध;
		पूर्ण

		करो अणु
			order = i915_अक्रमom_order(count, &prng);
			अगर (order)
				अवरोध;
		पूर्ण जबतक (count >>= 1);
		अगर (!count)
			वापस -ENOMEM;
		GEM_BUG_ON(!order);

		/* Ignore allocation failures (i.e. करोn't report them as
		 * a test failure) as we are purposefully allocating very
		 * large objects without checking that we have sufficient
		 * memory. We expect to hit -ENOMEM.
		 */

		obj = fake_dma_object(vm->i915, BIT_ULL(size));
		अगर (IS_ERR(obj)) अणु
			kमुक्त(order);
			अवरोध;
		पूर्ण

		vma = i915_vma_instance(obj, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ err_obj;
		पूर्ण

		GEM_BUG_ON(vma->size != BIT_ULL(size));

		क्रम (n = 0; n < count; n++) अणु
			u64 addr = hole_start + order[n] * BIT_ULL(size);

			err = i915_vma_pin(vma, 0, 0, addr | flags);
			अगर (err) अणु
				pr_err("%s failed to pin object at %llx + %llx in hole [%llx - %llx], with err=%d\n",
				       __func__,
				       addr, BIT_ULL(size),
				       hole_start, hole_end,
				       err);
				जाओ err_obj;
			पूर्ण

			अगर (!drm_mm_node_allocated(&vma->node) ||
			    i915_vma_misplaced(vma, 0, 0, addr | flags)) अणु
				pr_err("%s incorrect at %llx + %llx\n",
				       __func__, addr, BIT_ULL(size));
				i915_vma_unpin(vma);
				err = i915_vma_unbind(vma);
				err = -EINVAL;
				जाओ err_obj;
			पूर्ण

			i915_vma_unpin(vma);
			err = i915_vma_unbind(vma);
			GEM_BUG_ON(err);

			अगर (igt_समयout(end_समय,
					"%s timed out after %d/%d\n",
					__func__, n, count)) अणु
				err = -EINTR;
				जाओ err_obj;
			पूर्ण
		पूर्ण

err_obj:
		i915_gem_object_put(obj);
		kमुक्त(order);
		अगर (err)
			वापस err;

		cleanup_मुक्तd_objects(vm->i915);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __shrink_hole(काष्ठा i915_address_space *vm,
			 u64 hole_start, u64 hole_end,
			 अचिन्हित दीर्घ end_समय)
अणु
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित दीर्घ flags = PIN_OFFSET_FIXED | PIN_USER;
	अचिन्हित पूर्णांक order = 12;
	LIST_HEAD(objects);
	पूर्णांक err = 0;
	u64 addr;

	/* Keep creating larger objects until one cannot fit पूर्णांकo the hole */
	क्रम (addr = hole_start; addr < hole_end; ) अणु
		काष्ठा i915_vma *vma;
		u64 size = BIT_ULL(order++);

		size = min(size, hole_end - addr);
		obj = fake_dma_object(vm->i915, size);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			अवरोध;
		पूर्ण

		list_add(&obj->st_link, &objects);

		vma = i915_vma_instance(obj, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			अवरोध;
		पूर्ण

		GEM_BUG_ON(vma->size != size);

		err = i915_vma_pin(vma, 0, 0, addr | flags);
		अगर (err) अणु
			pr_err("%s failed to pin object at %llx + %llx in hole [%llx - %llx], with err=%d\n",
			       __func__, addr, size, hole_start, hole_end, err);
			अवरोध;
		पूर्ण

		अगर (!drm_mm_node_allocated(&vma->node) ||
		    i915_vma_misplaced(vma, 0, 0, addr | flags)) अणु
			pr_err("%s incorrect at %llx + %llx\n",
			       __func__, addr, size);
			i915_vma_unpin(vma);
			err = i915_vma_unbind(vma);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		i915_vma_unpin(vma);
		addr += size;

		/*
		 * Since we are injecting allocation faults at अक्रमom पूर्णांकervals,
		 * रुको क्रम this allocation to complete beक्रमe we change the
		 * faultinjection.
		 */
		err = i915_vma_sync(vma);
		अगर (err)
			अवरोध;

		अगर (igt_समयout(end_समय,
				"%s timed out at ofset %llx [%llx - %llx]\n",
				__func__, addr, hole_start, hole_end)) अणु
			err = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण

	बंद_object_list(&objects, vm);
	cleanup_मुक्तd_objects(vm->i915);
	वापस err;
पूर्ण

अटल पूर्णांक shrink_hole(काष्ठा i915_address_space *vm,
		       u64 hole_start, u64 hole_end,
		       अचिन्हित दीर्घ end_समय)
अणु
	अचिन्हित दीर्घ prime;
	पूर्णांक err;

	vm->fault_attr.probability = 999;
	atomic_set(&vm->fault_attr.बार, -1);

	क्रम_each_prime_number_from(prime, 0, अच_दीर्घ_उच्च - 1) अणु
		vm->fault_attr.पूर्णांकerval = prime;
		err = __shrink_hole(vm, hole_start, hole_end, end_समय);
		अगर (err)
			अवरोध;
	पूर्ण

	स_रखो(&vm->fault_attr, 0, माप(vm->fault_attr));

	वापस err;
पूर्ण

अटल पूर्णांक shrink_boom(काष्ठा i915_address_space *vm,
		       u64 hole_start, u64 hole_end,
		       अचिन्हित दीर्घ end_समय)
अणु
	अचिन्हित पूर्णांक sizes[] = अणु SZ_2M, SZ_1G पूर्ण;
	काष्ठा drm_i915_gem_object *purge;
	काष्ठा drm_i915_gem_object *explode;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * Catch the हाल which shrink_hole seems to miss. The setup here
	 * requires invoking the shrinker as we करो the alloc_pt/alloc_pd, जबतक
	 * ensuring that all vma assiocated with the respective pd/pdp are
	 * unpinned at the समय.
	 */

	क्रम (i = 0; i < ARRAY_SIZE(sizes); ++i) अणु
		अचिन्हित पूर्णांक flags = PIN_USER | PIN_OFFSET_FIXED;
		अचिन्हित पूर्णांक size = sizes[i];
		काष्ठा i915_vma *vma;

		purge = fake_dma_object(vm->i915, size);
		अगर (IS_ERR(purge))
			वापस PTR_ERR(purge);

		vma = i915_vma_instance(purge, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ err_purge;
		पूर्ण

		err = i915_vma_pin(vma, 0, 0, flags);
		अगर (err)
			जाओ err_purge;

		/* Should now be ripe क्रम purging */
		i915_vma_unpin(vma);

		explode = fake_dma_object(vm->i915, size);
		अगर (IS_ERR(explode)) अणु
			err = PTR_ERR(explode);
			जाओ err_purge;
		पूर्ण

		vm->fault_attr.probability = 100;
		vm->fault_attr.पूर्णांकerval = 1;
		atomic_set(&vm->fault_attr.बार, -1);

		vma = i915_vma_instance(explode, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ err_explode;
		पूर्ण

		err = i915_vma_pin(vma, 0, 0, flags | size);
		अगर (err)
			जाओ err_explode;

		i915_vma_unpin(vma);

		i915_gem_object_put(purge);
		i915_gem_object_put(explode);

		स_रखो(&vm->fault_attr, 0, माप(vm->fault_attr));
		cleanup_मुक्तd_objects(vm->i915);
	पूर्ण

	वापस 0;

err_explode:
	i915_gem_object_put(explode);
err_purge:
	i915_gem_object_put(purge);
	स_रखो(&vm->fault_attr, 0, माप(vm->fault_attr));
	वापस err;
पूर्ण

अटल पूर्णांक exercise_ppgtt(काष्ठा drm_i915_निजी *dev_priv,
			  पूर्णांक (*func)(काष्ठा i915_address_space *vm,
				      u64 hole_start, u64 hole_end,
				      अचिन्हित दीर्घ end_समय))
अणु
	काष्ठा i915_ppgtt *ppgtt;
	IGT_TIMEOUT(end_समय);
	काष्ठा file *file;
	पूर्णांक err;

	अगर (!HAS_FULL_PPGTT(dev_priv))
		वापस 0;

	file = mock_file(dev_priv);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ppgtt = i915_ppgtt_create(&dev_priv->gt);
	अगर (IS_ERR(ppgtt)) अणु
		err = PTR_ERR(ppgtt);
		जाओ out_मुक्त;
	पूर्ण
	GEM_BUG_ON(offset_in_page(ppgtt->vm.total));
	GEM_BUG_ON(!atomic_पढ़ो(&ppgtt->vm.खोलो));

	err = func(&ppgtt->vm, 0, ppgtt->vm.total, end_समय);

	i915_vm_put(&ppgtt->vm);

out_मुक्त:
	fput(file);
	वापस err;
पूर्ण

अटल पूर्णांक igt_ppgtt_fill(व्योम *arg)
अणु
	वापस exercise_ppgtt(arg, fill_hole);
पूर्ण

अटल पूर्णांक igt_ppgtt_walk(व्योम *arg)
अणु
	वापस exercise_ppgtt(arg, walk_hole);
पूर्ण

अटल पूर्णांक igt_ppgtt_pot(व्योम *arg)
अणु
	वापस exercise_ppgtt(arg, pot_hole);
पूर्ण

अटल पूर्णांक igt_ppgtt_drunk(व्योम *arg)
अणु
	वापस exercise_ppgtt(arg, drunk_hole);
पूर्ण

अटल पूर्णांक igt_ppgtt_lowlevel(व्योम *arg)
अणु
	वापस exercise_ppgtt(arg, lowlevel_hole);
पूर्ण

अटल पूर्णांक igt_ppgtt_shrink(व्योम *arg)
अणु
	वापस exercise_ppgtt(arg, shrink_hole);
पूर्ण

अटल पूर्णांक igt_ppgtt_shrink_boom(व्योम *arg)
अणु
	वापस exercise_ppgtt(arg, shrink_boom);
पूर्ण

अटल पूर्णांक sort_holes(व्योम *priv, स्थिर काष्ठा list_head *A,
		      स्थिर काष्ठा list_head *B)
अणु
	काष्ठा drm_mm_node *a = list_entry(A, typeof(*a), hole_stack);
	काष्ठा drm_mm_node *b = list_entry(B, typeof(*b), hole_stack);

	अगर (a->start < b->start)
		वापस -1;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक exercise_ggtt(काष्ठा drm_i915_निजी *i915,
			 पूर्णांक (*func)(काष्ठा i915_address_space *vm,
				     u64 hole_start, u64 hole_end,
				     अचिन्हित दीर्घ end_समय))
अणु
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	u64 hole_start, hole_end, last = 0;
	काष्ठा drm_mm_node *node;
	IGT_TIMEOUT(end_समय);
	पूर्णांक err = 0;

restart:
	list_sort(शून्य, &ggtt->vm.mm.hole_stack, sort_holes);
	drm_mm_क्रम_each_hole(node, &ggtt->vm.mm, hole_start, hole_end) अणु
		अगर (hole_start < last)
			जारी;

		अगर (ggtt->vm.mm.color_adjust)
			ggtt->vm.mm.color_adjust(node, 0,
						 &hole_start, &hole_end);
		अगर (hole_start >= hole_end)
			जारी;

		err = func(&ggtt->vm, hole_start, hole_end, end_समय);
		अगर (err)
			अवरोध;

		/* As we have manipulated the drm_mm, the list may be corrupt */
		last = hole_end;
		जाओ restart;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक igt_ggtt_fill(व्योम *arg)
अणु
	वापस exercise_ggtt(arg, fill_hole);
पूर्ण

अटल पूर्णांक igt_ggtt_walk(व्योम *arg)
अणु
	वापस exercise_ggtt(arg, walk_hole);
पूर्ण

अटल पूर्णांक igt_ggtt_pot(व्योम *arg)
अणु
	वापस exercise_ggtt(arg, pot_hole);
पूर्ण

अटल पूर्णांक igt_ggtt_drunk(व्योम *arg)
अणु
	वापस exercise_ggtt(arg, drunk_hole);
पूर्ण

अटल पूर्णांक igt_ggtt_lowlevel(व्योम *arg)
अणु
	वापस exercise_ggtt(arg, lowlevel_hole);
पूर्ण

अटल पूर्णांक igt_ggtt_page(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक count = PAGE_SIZE/माप(u32);
	I915_RND_STATE(prng);
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा drm_mm_node पंचांगp;
	अचिन्हित पूर्णांक *order, n;
	पूर्णांक err;

	अगर (!i915_ggtt_has_aperture(ggtt))
		वापस 0;

	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	err = i915_gem_object_pin_pages_unlocked(obj);
	अगर (err)
		जाओ out_मुक्त;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	mutex_lock(&ggtt->vm.mutex);
	err = drm_mm_insert_node_in_range(&ggtt->vm.mm, &पंचांगp,
					  count * PAGE_SIZE, 0,
					  I915_COLOR_UNEVICTABLE,
					  0, ggtt->mappable_end,
					  DRM_MM_INSERT_LOW);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (err)
		जाओ out_unpin;

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	क्रम (n = 0; n < count; n++) अणु
		u64 offset = पंचांगp.start + n * PAGE_SIZE;

		ggtt->vm.insert_page(&ggtt->vm,
				     i915_gem_object_get_dma_address(obj, 0),
				     offset, I915_CACHE_NONE, 0);
	पूर्ण

	order = i915_अक्रमom_order(count, &prng);
	अगर (!order) अणु
		err = -ENOMEM;
		जाओ out_हटाओ;
	पूर्ण

	क्रम (n = 0; n < count; n++) अणु
		u64 offset = पंचांगp.start + order[n] * PAGE_SIZE;
		u32 __iomem *vaddr;

		vaddr = io_mapping_map_atomic_wc(&ggtt->iomap, offset);
		ioग_लिखो32(n, vaddr + n);
		io_mapping_unmap_atomic(vaddr);
	पूर्ण
	पूर्णांकel_gt_flush_ggtt_ग_लिखोs(ggtt->vm.gt);

	i915_अक्रमom_reorder(order, count, &prng);
	क्रम (n = 0; n < count; n++) अणु
		u64 offset = पंचांगp.start + order[n] * PAGE_SIZE;
		u32 __iomem *vaddr;
		u32 val;

		vaddr = io_mapping_map_atomic_wc(&ggtt->iomap, offset);
		val = ioपढ़ो32(vaddr + n);
		io_mapping_unmap_atomic(vaddr);

		अगर (val != n) अणु
			pr_err("insert page failed: found %d, expected %d\n",
			       val, n);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(order);
out_हटाओ:
	ggtt->vm.clear_range(&ggtt->vm, पंचांगp.start, पंचांगp.size);
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
	mutex_lock(&ggtt->vm.mutex);
	drm_mm_हटाओ_node(&पंचांगp);
	mutex_unlock(&ggtt->vm.mutex);
out_unpin:
	i915_gem_object_unpin_pages(obj);
out_मुक्त:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल व्योम track_vma_bind(काष्ठा i915_vma *vma)
अणु
	काष्ठा drm_i915_gem_object *obj = vma->obj;

	__i915_gem_object_pin_pages(obj);

	GEM_BUG_ON(vma->pages);
	atomic_set(&vma->pages_count, I915_VMA_PAGES_ACTIVE);
	__i915_gem_object_pin_pages(obj);
	vma->pages = obj->mm.pages;

	mutex_lock(&vma->vm->mutex);
	list_add_tail(&vma->vm_link, &vma->vm->bound_list);
	mutex_unlock(&vma->vm->mutex);
पूर्ण

अटल पूर्णांक exercise_mock(काष्ठा drm_i915_निजी *i915,
			 पूर्णांक (*func)(काष्ठा i915_address_space *vm,
				     u64 hole_start, u64 hole_end,
				     अचिन्हित दीर्घ end_समय))
अणु
	स्थिर u64 limit = totalram_pages() << PAGE_SHIFT;
	काष्ठा i915_address_space *vm;
	काष्ठा i915_gem_context *ctx;
	IGT_TIMEOUT(end_समय);
	पूर्णांक err;

	ctx = mock_context(i915, "mock");
	अगर (!ctx)
		वापस -ENOMEM;

	vm = i915_gem_context_get_vm_rcu(ctx);
	err = func(vm, 0, min(vm->total, limit), end_समय);
	i915_vm_put(vm);

	mock_context_बंद(ctx);
	वापस err;
पूर्ण

अटल पूर्णांक igt_mock_fill(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;

	वापस exercise_mock(ggtt->vm.i915, fill_hole);
पूर्ण

अटल पूर्णांक igt_mock_walk(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;

	वापस exercise_mock(ggtt->vm.i915, walk_hole);
पूर्ण

अटल पूर्णांक igt_mock_pot(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;

	वापस exercise_mock(ggtt->vm.i915, pot_hole);
पूर्ण

अटल पूर्णांक igt_mock_drunk(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;

	वापस exercise_mock(ggtt->vm.i915, drunk_hole);
पूर्ण

अटल पूर्णांक igt_gtt_reserve(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;
	काष्ठा drm_i915_gem_object *obj, *on;
	I915_RND_STATE(prng);
	LIST_HEAD(objects);
	u64 total;
	पूर्णांक err = -ENODEV;

	/* i915_gem_gtt_reserve() tries to reserve the precise range
	 * क्रम the node, and evicts अगर it has to. So our test checks that
	 * it can give us the requsted space and prevent overlaps.
	 */

	/* Start by filling the GGTT */
	क्रम (total = 0;
	     total + 2 * I915_GTT_PAGE_SIZE <= ggtt->vm.total;
	     total += 2 * I915_GTT_PAGE_SIZE) अणु
		काष्ठा i915_vma *vma;

		obj = i915_gem_object_create_पूर्णांकernal(ggtt->vm.i915,
						      2 * PAGE_SIZE);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			जाओ out;
		पूर्ण

		err = i915_gem_object_pin_pages_unlocked(obj);
		अगर (err) अणु
			i915_gem_object_put(obj);
			जाओ out;
		पूर्ण

		list_add(&obj->st_link, &objects);

		vma = i915_vma_instance(obj, &ggtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out;
		पूर्ण

		mutex_lock(&ggtt->vm.mutex);
		err = i915_gem_gtt_reserve(&ggtt->vm, &vma->node,
					   obj->base.size,
					   total,
					   obj->cache_level,
					   0);
		mutex_unlock(&ggtt->vm.mutex);
		अगर (err) अणु
			pr_err("i915_gem_gtt_reserve (pass 1) failed at %llu/%llu with err=%d\n",
			       total, ggtt->vm.total, err);
			जाओ out;
		पूर्ण
		track_vma_bind(vma);

		GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
		अगर (vma->node.start != total ||
		    vma->node.size != 2*I915_GTT_PAGE_SIZE) अणु
			pr_err("i915_gem_gtt_reserve (pass 1) placement failed, found (%llx + %llx), expected (%llx + %llx)\n",
			       vma->node.start, vma->node.size,
			       total, 2*I915_GTT_PAGE_SIZE);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Now we start क्रमcing evictions */
	क्रम (total = I915_GTT_PAGE_SIZE;
	     total + 2 * I915_GTT_PAGE_SIZE <= ggtt->vm.total;
	     total += 2 * I915_GTT_PAGE_SIZE) अणु
		काष्ठा i915_vma *vma;

		obj = i915_gem_object_create_पूर्णांकernal(ggtt->vm.i915,
						      2 * PAGE_SIZE);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			जाओ out;
		पूर्ण

		err = i915_gem_object_pin_pages_unlocked(obj);
		अगर (err) अणु
			i915_gem_object_put(obj);
			जाओ out;
		पूर्ण

		list_add(&obj->st_link, &objects);

		vma = i915_vma_instance(obj, &ggtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out;
		पूर्ण

		mutex_lock(&ggtt->vm.mutex);
		err = i915_gem_gtt_reserve(&ggtt->vm, &vma->node,
					   obj->base.size,
					   total,
					   obj->cache_level,
					   0);
		mutex_unlock(&ggtt->vm.mutex);
		अगर (err) अणु
			pr_err("i915_gem_gtt_reserve (pass 2) failed at %llu/%llu with err=%d\n",
			       total, ggtt->vm.total, err);
			जाओ out;
		पूर्ण
		track_vma_bind(vma);

		GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
		अगर (vma->node.start != total ||
		    vma->node.size != 2*I915_GTT_PAGE_SIZE) अणु
			pr_err("i915_gem_gtt_reserve (pass 2) placement failed, found (%llx + %llx), expected (%llx + %llx)\n",
			       vma->node.start, vma->node.size,
			       total, 2*I915_GTT_PAGE_SIZE);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* And then try at अक्रमom */
	list_क्रम_each_entry_safe(obj, on, &objects, st_link) अणु
		काष्ठा i915_vma *vma;
		u64 offset;

		vma = i915_vma_instance(obj, &ggtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out;
		पूर्ण

		err = i915_vma_unbind(vma);
		अगर (err) अणु
			pr_err("i915_vma_unbind failed with err=%d!\n", err);
			जाओ out;
		पूर्ण

		offset = igt_अक्रमom_offset(&prng,
					   0, ggtt->vm.total,
					   2 * I915_GTT_PAGE_SIZE,
					   I915_GTT_MIN_ALIGNMENT);

		mutex_lock(&ggtt->vm.mutex);
		err = i915_gem_gtt_reserve(&ggtt->vm, &vma->node,
					   obj->base.size,
					   offset,
					   obj->cache_level,
					   0);
		mutex_unlock(&ggtt->vm.mutex);
		अगर (err) अणु
			pr_err("i915_gem_gtt_reserve (pass 3) failed at %llu/%llu with err=%d\n",
			       total, ggtt->vm.total, err);
			जाओ out;
		पूर्ण
		track_vma_bind(vma);

		GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
		अगर (vma->node.start != offset ||
		    vma->node.size != 2*I915_GTT_PAGE_SIZE) अणु
			pr_err("i915_gem_gtt_reserve (pass 3) placement failed, found (%llx + %llx), expected (%llx + %llx)\n",
			       vma->node.start, vma->node.size,
			       offset, 2*I915_GTT_PAGE_SIZE);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	list_क्रम_each_entry_safe(obj, on, &objects, st_link) अणु
		i915_gem_object_unpin_pages(obj);
		i915_gem_object_put(obj);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक igt_gtt_insert(व्योम *arg)
अणु
	काष्ठा i915_ggtt *ggtt = arg;
	काष्ठा drm_i915_gem_object *obj, *on;
	काष्ठा drm_mm_node पंचांगp = अणुपूर्ण;
	स्थिर काष्ठा invalid_insert अणु
		u64 size;
		u64 alignment;
		u64 start, end;
	पूर्ण invalid_insert[] = अणु
		अणु
			ggtt->vm.total + I915_GTT_PAGE_SIZE, 0,
			0, ggtt->vm.total,
		पूर्ण,
		अणु
			2*I915_GTT_PAGE_SIZE, 0,
			0, I915_GTT_PAGE_SIZE,
		पूर्ण,
		अणु
			-(u64)I915_GTT_PAGE_SIZE, 0,
			0, 4*I915_GTT_PAGE_SIZE,
		पूर्ण,
		अणु
			-(u64)2*I915_GTT_PAGE_SIZE, 2*I915_GTT_PAGE_SIZE,
			0, 4*I915_GTT_PAGE_SIZE,
		पूर्ण,
		अणु
			I915_GTT_PAGE_SIZE, I915_GTT_MIN_ALIGNMENT << 1,
			I915_GTT_MIN_ALIGNMENT, I915_GTT_MIN_ALIGNMENT << 1,
		पूर्ण,
		अणुपूर्ण
	पूर्ण, *ii;
	LIST_HEAD(objects);
	u64 total;
	पूर्णांक err = -ENODEV;

	/* i915_gem_gtt_insert() tries to allocate some मुक्त space in the GTT
	 * to the node, evicting अगर required.
	 */

	/* Check a couple of obviously invalid requests */
	क्रम (ii = invalid_insert; ii->size; ii++) अणु
		mutex_lock(&ggtt->vm.mutex);
		err = i915_gem_gtt_insert(&ggtt->vm, &पंचांगp,
					  ii->size, ii->alignment,
					  I915_COLOR_UNEVICTABLE,
					  ii->start, ii->end,
					  0);
		mutex_unlock(&ggtt->vm.mutex);
		अगर (err != -ENOSPC) अणु
			pr_err("Invalid i915_gem_gtt_insert(.size=%llx, .alignment=%llx, .start=%llx, .end=%llx) succeeded (err=%d)\n",
			       ii->size, ii->alignment, ii->start, ii->end,
			       err);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Start by filling the GGTT */
	क्रम (total = 0;
	     total + I915_GTT_PAGE_SIZE <= ggtt->vm.total;
	     total += I915_GTT_PAGE_SIZE) अणु
		काष्ठा i915_vma *vma;

		obj = i915_gem_object_create_पूर्णांकernal(ggtt->vm.i915,
						      I915_GTT_PAGE_SIZE);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			जाओ out;
		पूर्ण

		err = i915_gem_object_pin_pages_unlocked(obj);
		अगर (err) अणु
			i915_gem_object_put(obj);
			जाओ out;
		पूर्ण

		list_add(&obj->st_link, &objects);

		vma = i915_vma_instance(obj, &ggtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out;
		पूर्ण

		mutex_lock(&ggtt->vm.mutex);
		err = i915_gem_gtt_insert(&ggtt->vm, &vma->node,
					  obj->base.size, 0, obj->cache_level,
					  0, ggtt->vm.total,
					  0);
		mutex_unlock(&ggtt->vm.mutex);
		अगर (err == -ENOSPC) अणु
			/* maxed out the GGTT space */
			i915_gem_object_put(obj);
			अवरोध;
		पूर्ण
		अगर (err) अणु
			pr_err("i915_gem_gtt_insert (pass 1) failed at %llu/%llu with err=%d\n",
			       total, ggtt->vm.total, err);
			जाओ out;
		पूर्ण
		track_vma_bind(vma);
		__i915_vma_pin(vma);

		GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	पूर्ण

	list_क्रम_each_entry(obj, &objects, st_link) अणु
		काष्ठा i915_vma *vma;

		vma = i915_vma_instance(obj, &ggtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out;
		पूर्ण

		अगर (!drm_mm_node_allocated(&vma->node)) अणु
			pr_err("VMA was unexpectedly evicted!\n");
			err = -EINVAL;
			जाओ out;
		पूर्ण

		__i915_vma_unpin(vma);
	पूर्ण

	/* If we then reinsert, we should find the same hole */
	list_क्रम_each_entry_safe(obj, on, &objects, st_link) अणु
		काष्ठा i915_vma *vma;
		u64 offset;

		vma = i915_vma_instance(obj, &ggtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out;
		पूर्ण

		GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
		offset = vma->node.start;

		err = i915_vma_unbind(vma);
		अगर (err) अणु
			pr_err("i915_vma_unbind failed with err=%d!\n", err);
			जाओ out;
		पूर्ण

		mutex_lock(&ggtt->vm.mutex);
		err = i915_gem_gtt_insert(&ggtt->vm, &vma->node,
					  obj->base.size, 0, obj->cache_level,
					  0, ggtt->vm.total,
					  0);
		mutex_unlock(&ggtt->vm.mutex);
		अगर (err) अणु
			pr_err("i915_gem_gtt_insert (pass 2) failed at %llu/%llu with err=%d\n",
			       total, ggtt->vm.total, err);
			जाओ out;
		पूर्ण
		track_vma_bind(vma);

		GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
		अगर (vma->node.start != offset) अणु
			pr_err("i915_gem_gtt_insert did not return node to its previous location (the only hole), expected address %llx, found %llx\n",
			       offset, vma->node.start);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* And then क्रमce evictions */
	क्रम (total = 0;
	     total + 2 * I915_GTT_PAGE_SIZE <= ggtt->vm.total;
	     total += 2 * I915_GTT_PAGE_SIZE) अणु
		काष्ठा i915_vma *vma;

		obj = i915_gem_object_create_पूर्णांकernal(ggtt->vm.i915,
						      2 * I915_GTT_PAGE_SIZE);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			जाओ out;
		पूर्ण

		err = i915_gem_object_pin_pages_unlocked(obj);
		अगर (err) अणु
			i915_gem_object_put(obj);
			जाओ out;
		पूर्ण

		list_add(&obj->st_link, &objects);

		vma = i915_vma_instance(obj, &ggtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out;
		पूर्ण

		mutex_lock(&ggtt->vm.mutex);
		err = i915_gem_gtt_insert(&ggtt->vm, &vma->node,
					  obj->base.size, 0, obj->cache_level,
					  0, ggtt->vm.total,
					  0);
		mutex_unlock(&ggtt->vm.mutex);
		अगर (err) अणु
			pr_err("i915_gem_gtt_insert (pass 3) failed at %llu/%llu with err=%d\n",
			       total, ggtt->vm.total, err);
			जाओ out;
		पूर्ण
		track_vma_bind(vma);

		GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	पूर्ण

out:
	list_क्रम_each_entry_safe(obj, on, &objects, st_link) अणु
		i915_gem_object_unpin_pages(obj);
		i915_gem_object_put(obj);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक i915_gem_gtt_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_mock_drunk),
		SUBTEST(igt_mock_walk),
		SUBTEST(igt_mock_pot),
		SUBTEST(igt_mock_fill),
		SUBTEST(igt_gtt_reserve),
		SUBTEST(igt_gtt_insert),
	पूर्ण;
	काष्ठा drm_i915_निजी *i915;
	काष्ठा i915_ggtt *ggtt;
	पूर्णांक err;

	i915 = mock_gem_device();
	अगर (!i915)
		वापस -ENOMEM;

	ggtt = kदो_स्मृति(माप(*ggtt), GFP_KERNEL);
	अगर (!ggtt) अणु
		err = -ENOMEM;
		जाओ out_put;
	पूर्ण
	mock_init_ggtt(i915, ggtt);

	err = i915_subtests(tests, ggtt);

	mock_device_flush(i915);
	i915_gem_drain_मुक्तd_objects(i915);
	mock_fini_ggtt(ggtt);
	kमुक्त(ggtt);
out_put:
	mock_destroy_device(i915);
	वापस err;
पूर्ण

अटल पूर्णांक context_sync(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_request *rq;
	दीर्घ समयout;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	i915_request_get(rq);
	i915_request_add(rq);

	समयout = i915_request_रुको(rq, 0, HZ / 5);
	i915_request_put(rq);

	वापस समयout < 0 ? -EIO : 0;
पूर्ण

अटल काष्ठा i915_request *
submit_batch(काष्ठा पूर्णांकel_context *ce, u64 addr)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस rq;

	err = 0;
	अगर (rq->engine->emit_init_bपढ़ोcrumb) /* detect a hang */
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
	अगर (err == 0)
		err = rq->engine->emit_bb_start(rq, addr, 0, 0);

	अगर (err == 0)
		i915_request_get(rq);
	i915_request_add(rq);

	वापस err ? ERR_PTR(err) : rq;
पूर्ण

अटल u32 *spinner(u32 *batch, पूर्णांक i)
अणु
	वापस batch + i * 64 / माप(*batch) + 4;
पूर्ण

अटल व्योम end_spin(u32 *batch, पूर्णांक i)
अणु
	*spinner(batch, i) = MI_BATCH_BUFFER_END;
	wmb();
पूर्ण

अटल पूर्णांक igt_cs_tlb(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक count = PAGE_SIZE / 64;
	स्थिर अचिन्हित पूर्णांक chunk_size = count * PAGE_SIZE;
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *bbe, *act, *out;
	काष्ठा i915_gem_engines_iter it;
	काष्ठा i915_address_space *vm;
	काष्ठा i915_gem_context *ctx;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_vma *vma;
	I915_RND_STATE(prng);
	काष्ठा file *file;
	अचिन्हित पूर्णांक i;
	u32 *result;
	u32 *batch;
	पूर्णांक err = 0;

	/*
	 * Our mission here is to fool the hardware to execute something
	 * from scratch as it has not seen the batch move (due to missing
	 * the TLB invalidate).
	 */

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ctx = live_context(i915, file);
	अगर (IS_ERR(ctx)) अणु
		err = PTR_ERR(ctx);
		जाओ out_unlock;
	पूर्ण

	vm = i915_gem_context_get_vm_rcu(ctx);
	अगर (i915_is_ggtt(vm))
		जाओ out_vm;

	/* Create two pages; dummy we prefill the TLB, and पूर्णांकended */
	bbe = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(bbe)) अणु
		err = PTR_ERR(bbe);
		जाओ out_vm;
	पूर्ण

	batch = i915_gem_object_pin_map_unlocked(bbe, I915_MAP_WC);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_put_bbe;
	पूर्ण
	स_रखो32(batch, MI_BATCH_BUFFER_END, PAGE_SIZE / माप(u32));
	i915_gem_object_flush_map(bbe);
	i915_gem_object_unpin_map(bbe);

	act = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(act)) अणु
		err = PTR_ERR(act);
		जाओ out_put_bbe;
	पूर्ण

	/* Track the execution of each request by writing पूर्णांकo dअगरferent slot */
	batch = i915_gem_object_pin_map_unlocked(act, I915_MAP_WC);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_put_act;
	पूर्ण
	क्रम (i = 0; i < count; i++) अणु
		u32 *cs = batch + i * 64 / माप(*cs);
		u64 addr = (vm->total - PAGE_SIZE) + i * माप(u32);

		GEM_BUG_ON(INTEL_GEN(i915) < 6);
		cs[0] = MI_STORE_DWORD_IMM_GEN4;
		अगर (INTEL_GEN(i915) >= 8) अणु
			cs[1] = lower_32_bits(addr);
			cs[2] = upper_32_bits(addr);
			cs[3] = i;
			cs[4] = MI_NOOP;
			cs[5] = MI_BATCH_BUFFER_START_GEN8;
		पूर्ण अन्यथा अणु
			cs[1] = 0;
			cs[2] = lower_32_bits(addr);
			cs[3] = i;
			cs[4] = MI_NOOP;
			cs[5] = MI_BATCH_BUFFER_START;
		पूर्ण
	पूर्ण

	out = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(out)) अणु
		err = PTR_ERR(out);
		जाओ out_put_batch;
	पूर्ण
	i915_gem_object_set_cache_coherency(out, I915_CACHING_CACHED);

	vma = i915_vma_instance(out, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ out_put_out;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0,
			   PIN_USER |
			   PIN_OFFSET_FIXED |
			   (vm->total - PAGE_SIZE));
	अगर (err)
		जाओ out_put_out;
	GEM_BUG_ON(vma->node.start != vm->total - PAGE_SIZE);

	result = i915_gem_object_pin_map_unlocked(out, I915_MAP_WB);
	अगर (IS_ERR(result)) अणु
		err = PTR_ERR(result);
		जाओ out_put_out;
	पूर्ण

	क्रम_each_gem_engine(ce, i915_gem_context_lock_engines(ctx), it) अणु
		IGT_TIMEOUT(end_समय);
		अचिन्हित दीर्घ pass = 0;

		अगर (!पूर्णांकel_engine_can_store_dword(ce->engine))
			जारी;

		जबतक (!__igt_समयout(end_समय, शून्य)) अणु
			काष्ठा i915_vm_pt_stash stash = अणुपूर्ण;
			काष्ठा i915_request *rq;
			काष्ठा i915_gem_ww_ctx ww;
			u64 offset;

			offset = igt_अक्रमom_offset(&prng,
						   0, vm->total - PAGE_SIZE,
						   chunk_size, PAGE_SIZE);

			स_रखो32(result, STACK_MAGIC, PAGE_SIZE / माप(u32));

			vma = i915_vma_instance(bbe, vm, शून्य);
			अगर (IS_ERR(vma)) अणु
				err = PTR_ERR(vma);
				जाओ end;
			पूर्ण

			err = vma->ops->set_pages(vma);
			अगर (err)
				जाओ end;

			i915_gem_ww_ctx_init(&ww, false);
retry:
			err = i915_vm_lock_objects(vm, &ww);
			अगर (err)
				जाओ end_ww;

			err = i915_vm_alloc_pt_stash(vm, &stash, chunk_size);
			अगर (err)
				जाओ end_ww;

			err = i915_vm_pin_pt_stash(vm, &stash);
			अगर (!err)
				vm->allocate_va_range(vm, &stash, offset, chunk_size);

			i915_vm_मुक्त_pt_stash(vm, &stash);
end_ww:
			अगर (err == -EDEADLK) अणु
				err = i915_gem_ww_ctx_backoff(&ww);
				अगर (!err)
					जाओ retry;
			पूर्ण
			i915_gem_ww_ctx_fini(&ww);
			अगर (err)
				जाओ end;

			/* Prime the TLB with the dummy pages */
			क्रम (i = 0; i < count; i++) अणु
				vma->node.start = offset + i * PAGE_SIZE;
				vm->insert_entries(vm, vma, I915_CACHE_NONE, 0);

				rq = submit_batch(ce, vma->node.start);
				अगर (IS_ERR(rq)) अणु
					err = PTR_ERR(rq);
					जाओ end;
				पूर्ण
				i915_request_put(rq);
			पूर्ण

			vma->ops->clear_pages(vma);

			err = context_sync(ce);
			अगर (err) अणु
				pr_err("%s: dummy setup timed out\n",
				       ce->engine->name);
				जाओ end;
			पूर्ण

			vma = i915_vma_instance(act, vm, शून्य);
			अगर (IS_ERR(vma)) अणु
				err = PTR_ERR(vma);
				जाओ end;
			पूर्ण

			err = vma->ops->set_pages(vma);
			अगर (err)
				जाओ end;

			/* Replace the TLB with target batches */
			क्रम (i = 0; i < count; i++) अणु
				काष्ठा i915_request *rq;
				u32 *cs = batch + i * 64 / माप(*cs);
				u64 addr;

				vma->node.start = offset + i * PAGE_SIZE;
				vm->insert_entries(vm, vma, I915_CACHE_NONE, 0);

				addr = vma->node.start + i * 64;
				cs[4] = MI_NOOP;
				cs[6] = lower_32_bits(addr);
				cs[7] = upper_32_bits(addr);
				wmb();

				rq = submit_batch(ce, addr);
				अगर (IS_ERR(rq)) अणु
					err = PTR_ERR(rq);
					जाओ end;
				पूर्ण

				/* Wait until the context chain has started */
				अगर (i == 0) अणु
					जबतक (READ_ONCE(result[i]) &&
					       !i915_request_completed(rq))
						cond_resched();
				पूर्ण अन्यथा अणु
					end_spin(batch, i - 1);
				पूर्ण

				i915_request_put(rq);
			पूर्ण
			end_spin(batch, count - 1);

			vma->ops->clear_pages(vma);

			err = context_sync(ce);
			अगर (err) अणु
				pr_err("%s: writes timed out\n",
				       ce->engine->name);
				जाओ end;
			पूर्ण

			क्रम (i = 0; i < count; i++) अणु
				अगर (result[i] != i) अणु
					pr_err("%s: Write lost on pass %lu, at offset %llx, index %d, found %x, expected %x\n",
					       ce->engine->name, pass,
					       offset, i, result[i], i);
					err = -EINVAL;
					जाओ end;
				पूर्ण
			पूर्ण

			vm->clear_range(vm, offset, chunk_size);
			pass++;
		पूर्ण
	पूर्ण
end:
	अगर (igt_flush_test(i915))
		err = -EIO;
	i915_gem_context_unlock_engines(ctx);
	i915_gem_object_unpin_map(out);
out_put_out:
	i915_gem_object_put(out);
out_put_batch:
	i915_gem_object_unpin_map(act);
out_put_act:
	i915_gem_object_put(act);
out_put_bbe:
	i915_gem_object_put(bbe);
out_vm:
	i915_vm_put(vm);
out_unlock:
	fput(file);
	वापस err;
पूर्ण

पूर्णांक i915_gem_gtt_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_ppgtt_alloc),
		SUBTEST(igt_ppgtt_lowlevel),
		SUBTEST(igt_ppgtt_drunk),
		SUBTEST(igt_ppgtt_walk),
		SUBTEST(igt_ppgtt_pot),
		SUBTEST(igt_ppgtt_fill),
		SUBTEST(igt_ppgtt_shrink),
		SUBTEST(igt_ppgtt_shrink_boom),
		SUBTEST(igt_ggtt_lowlevel),
		SUBTEST(igt_ggtt_drunk),
		SUBTEST(igt_ggtt_walk),
		SUBTEST(igt_ggtt_pot),
		SUBTEST(igt_ggtt_fill),
		SUBTEST(igt_ggtt_page),
		SUBTEST(igt_cs_tlb),
	पूर्ण;

	GEM_BUG_ON(offset_in_page(i915->ggtt.vm.total));

	वापस i915_subtests(tests, i915);
पूर्ण
