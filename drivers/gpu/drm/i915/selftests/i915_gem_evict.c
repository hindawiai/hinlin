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

#समावेश "gem/i915_gem_pm.h"
#समावेश "gem/selftests/igt_gem_utils.h"
#समावेश "gem/selftests/mock_context.h"
#समावेश "gt/intel_gt.h"

#समावेश "i915_selftest.h"

#समावेश "igt_flush_test.h"
#समावेश "lib_sw_fence.h"
#समावेश "mock_drm.h"
#समावेश "mock_gem_device.h"

अटल व्योम quirk_add(काष्ठा drm_i915_gem_object *obj,
		      काष्ठा list_head *objects)
अणु
	/* quirk is only क्रम live tiled objects, use it to declare ownership */
	GEM_BUG_ON(i915_gem_object_has_tiling_quirk(obj));
	i915_gem_object_set_tiling_quirk(obj);
	list_add(&obj->st_link, objects);
पूर्ण

अटल पूर्णांक populate_ggtt(काष्ठा i915_ggtt *ggtt, काष्ठा list_head *objects)
अणु
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित दीर्घ count;

	count = 0;
	करो अणु
		काष्ठा i915_vma *vma;

		obj = i915_gem_object_create_पूर्णांकernal(ggtt->vm.i915,
						      I915_GTT_PAGE_SIZE);
		अगर (IS_ERR(obj))
			वापस PTR_ERR(obj);

		vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0, 0);
		अगर (IS_ERR(vma)) अणु
			i915_gem_object_put(obj);
			अगर (vma == ERR_PTR(-ENOSPC))
				अवरोध;

			वापस PTR_ERR(vma);
		पूर्ण

		quirk_add(obj, objects);
		count++;
	पूर्ण जबतक (1);
	pr_debug("Filled GGTT with %lu pages [%llu total]\n",
		 count, ggtt->vm.total / PAGE_SIZE);

	अगर (list_empty(&ggtt->vm.bound_list)) अणु
		pr_err("No objects on the GGTT inactive list!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम unpin_ggtt(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा i915_vma *vma;

	list_क्रम_each_entry(vma, &ggtt->vm.bound_list, vm_link)
		अगर (i915_gem_object_has_tiling_quirk(vma->obj))
			i915_vma_unpin(vma);
पूर्ण

अटल व्योम cleanup_objects(काष्ठा i915_ggtt *ggtt, काष्ठा list_head *list)
अणु
	काष्ठा drm_i915_gem_object *obj, *on;

	list_क्रम_each_entry_safe(obj, on, list, st_link) अणु
		GEM_BUG_ON(!i915_gem_object_has_tiling_quirk(obj));
		i915_gem_object_set_tiling_quirk(obj);
		i915_gem_object_put(obj);
	पूर्ण

	i915_gem_drain_मुक्तd_objects(ggtt->vm.i915);
पूर्ण

अटल पूर्णांक igt_evict_something(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_ggtt *ggtt = gt->ggtt;
	LIST_HEAD(objects);
	पूर्णांक err;

	/* Fill the GGTT with pinned objects and try to evict one. */

	err = populate_ggtt(ggtt, &objects);
	अगर (err)
		जाओ cleanup;

	/* Everything is pinned, nothing should happen */
	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_evict_something(&ggtt->vm,
				       I915_GTT_PAGE_SIZE, 0, 0,
				       0, U64_MAX,
				       0);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (err != -ENOSPC) अणु
		pr_err("i915_gem_evict_something failed on a full GGTT with err=%d\n",
		       err);
		जाओ cleanup;
	पूर्ण

	unpin_ggtt(ggtt);

	/* Everything is unpinned, we should be able to evict something */
	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_evict_something(&ggtt->vm,
				       I915_GTT_PAGE_SIZE, 0, 0,
				       0, U64_MAX,
				       0);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (err) अणु
		pr_err("i915_gem_evict_something failed on a full GGTT with err=%d\n",
		       err);
		जाओ cleanup;
	पूर्ण

cleanup:
	cleanup_objects(ggtt, &objects);
	वापस err;
पूर्ण

अटल पूर्णांक igt_overcommit(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_ggtt *ggtt = gt->ggtt;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	LIST_HEAD(objects);
	पूर्णांक err;

	/* Fill the GGTT with pinned objects and then try to pin one more.
	 * We expect it to fail.
	 */

	err = populate_ggtt(ggtt, &objects);
	अगर (err)
		जाओ cleanup;

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, I915_GTT_PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ cleanup;
	पूर्ण

	quirk_add(obj, &objects);

	vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0, 0);
	अगर (vma != ERR_PTR(-ENOSPC)) अणु
		pr_err("Failed to evict+insert, i915_gem_object_ggtt_pin returned err=%d\n", (पूर्णांक)PTR_ERR_OR_ZERO(vma));
		err = -EINVAL;
		जाओ cleanup;
	पूर्ण

cleanup:
	cleanup_objects(ggtt, &objects);
	वापस err;
पूर्ण

अटल पूर्णांक igt_evict_क्रम_vma(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_ggtt *ggtt = gt->ggtt;
	काष्ठा drm_mm_node target = अणु
		.start = 0,
		.size = 4096,
	पूर्ण;
	LIST_HEAD(objects);
	पूर्णांक err;

	/* Fill the GGTT with pinned objects and try to evict a range. */

	err = populate_ggtt(ggtt, &objects);
	अगर (err)
		जाओ cleanup;

	/* Everything is pinned, nothing should happen */
	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_evict_क्रम_node(&ggtt->vm, &target, 0);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (err != -ENOSPC) अणु
		pr_err("i915_gem_evict_for_node on a full GGTT returned err=%d\n",
		       err);
		जाओ cleanup;
	पूर्ण

	unpin_ggtt(ggtt);

	/* Everything is unpinned, we should be able to evict the node */
	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_evict_क्रम_node(&ggtt->vm, &target, 0);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (err) अणु
		pr_err("i915_gem_evict_for_node returned err=%d\n",
		       err);
		जाओ cleanup;
	पूर्ण

cleanup:
	cleanup_objects(ggtt, &objects);
	वापस err;
पूर्ण

अटल व्योम mock_color_adjust(स्थिर काष्ठा drm_mm_node *node,
			      अचिन्हित दीर्घ color,
			      u64 *start,
			      u64 *end)
अणु
पूर्ण

अटल पूर्णांक igt_evict_क्रम_cache_color(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_ggtt *ggtt = gt->ggtt;
	स्थिर अचिन्हित दीर्घ flags = PIN_OFFSET_FIXED;
	काष्ठा drm_mm_node target = अणु
		.start = I915_GTT_PAGE_SIZE * 2,
		.size = I915_GTT_PAGE_SIZE,
		.color = I915_CACHE_LLC,
	पूर्ण;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	LIST_HEAD(objects);
	पूर्णांक err;

	/*
	 * Currently the use of color_adjust क्रम the GGTT is limited to cache
	 * coloring and guard pages, and so the presence of mm.color_adjust क्रम
	 * the GGTT is assumed to be i915_ggtt_color_adjust, hence using a mock
	 * color adjust will work just fine क्रम our purposes.
	 */
	ggtt->vm.mm.color_adjust = mock_color_adjust;
	GEM_BUG_ON(!i915_vm_has_cache_coloring(&ggtt->vm));

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, I915_GTT_PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ cleanup;
	पूर्ण
	i915_gem_object_set_cache_coherency(obj, I915_CACHE_LLC);
	quirk_add(obj, &objects);

	vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0,
				       I915_GTT_PAGE_SIZE | flags);
	अगर (IS_ERR(vma)) अणु
		pr_err("[0]i915_gem_object_ggtt_pin failed\n");
		err = PTR_ERR(vma);
		जाओ cleanup;
	पूर्ण

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, I915_GTT_PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ cleanup;
	पूर्ण
	i915_gem_object_set_cache_coherency(obj, I915_CACHE_LLC);
	quirk_add(obj, &objects);

	/* Neighbouring; same colour - should fit */
	vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0,
				       (I915_GTT_PAGE_SIZE * 2) | flags);
	अगर (IS_ERR(vma)) अणु
		pr_err("[1]i915_gem_object_ggtt_pin failed\n");
		err = PTR_ERR(vma);
		जाओ cleanup;
	पूर्ण

	i915_vma_unpin(vma);

	/* Remove just the second vma */
	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_evict_क्रम_node(&ggtt->vm, &target, 0);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (err) अणु
		pr_err("[0]i915_gem_evict_for_node returned err=%d\n", err);
		जाओ cleanup;
	पूर्ण

	/* Attempt to हटाओ the first *pinned* vma, by removing the (empty)
	 * neighbour -- this should fail.
	 */
	target.color = I915_CACHE_L3_LLC;

	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_evict_क्रम_node(&ggtt->vm, &target, 0);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (!err) अणु
		pr_err("[1]i915_gem_evict_for_node returned err=%d\n", err);
		err = -EINVAL;
		जाओ cleanup;
	पूर्ण

	err = 0;

cleanup:
	unpin_ggtt(ggtt);
	cleanup_objects(ggtt, &objects);
	ggtt->vm.mm.color_adjust = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक igt_evict_vm(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_ggtt *ggtt = gt->ggtt;
	LIST_HEAD(objects);
	पूर्णांक err;

	/* Fill the GGTT with pinned objects and try to evict everything. */

	err = populate_ggtt(ggtt, &objects);
	अगर (err)
		जाओ cleanup;

	/* Everything is pinned, nothing should happen */
	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_evict_vm(&ggtt->vm);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (err) अणु
		pr_err("i915_gem_evict_vm on a full GGTT returned err=%d]\n",
		       err);
		जाओ cleanup;
	पूर्ण

	unpin_ggtt(ggtt);

	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_evict_vm(&ggtt->vm);
	mutex_unlock(&ggtt->vm.mutex);
	अगर (err) अणु
		pr_err("i915_gem_evict_vm on a full GGTT returned err=%d]\n",
		       err);
		जाओ cleanup;
	पूर्ण

cleanup:
	cleanup_objects(ggtt, &objects);
	वापस err;
पूर्ण

अटल पूर्णांक igt_evict_contexts(व्योम *arg)
अणु
	स्थिर u64 PRETEND_GGTT_SIZE = 16ull << 20;
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_ggtt *ggtt = gt->ggtt;
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा reserved अणु
		काष्ठा drm_mm_node node;
		काष्ठा reserved *next;
	पूर्ण *reserved = शून्य;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा drm_mm_node hole;
	अचिन्हित दीर्घ count;
	पूर्णांक err;

	/*
	 * The purpose of this test is to verअगरy that we will trigger an
	 * eviction in the GGTT when स्थिरructing a request that requires
	 * additional space in the GGTT क्रम pinning the context. This space
	 * is not directly tied to the request so reclaiming it requires
	 * extra work.
	 *
	 * As such this test is only meaningful क्रम full-ppgtt environments
	 * where the GTT space of the request is separate from the GGTT
	 * allocation required to build the request.
	 */
	अगर (!HAS_FULL_PPGTT(i915))
		वापस 0;

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	/* Reserve a block so that we know we have enough to fit a few rq */
	स_रखो(&hole, 0, माप(hole));
	mutex_lock(&ggtt->vm.mutex);
	err = i915_gem_gtt_insert(&ggtt->vm, &hole,
				  PRETEND_GGTT_SIZE, 0, I915_COLOR_UNEVICTABLE,
				  0, ggtt->vm.total,
				  PIN_NOEVICT);
	अगर (err)
		जाओ out_locked;

	/* Make the GGTT appear small by filling it with unevictable nodes */
	count = 0;
	करो अणु
		काष्ठा reserved *r;

		mutex_unlock(&ggtt->vm.mutex);
		r = kसुस्मृति(1, माप(*r), GFP_KERNEL);
		mutex_lock(&ggtt->vm.mutex);
		अगर (!r) अणु
			err = -ENOMEM;
			जाओ out_locked;
		पूर्ण

		अगर (i915_gem_gtt_insert(&ggtt->vm, &r->node,
					1ul << 20, 0, I915_COLOR_UNEVICTABLE,
					0, ggtt->vm.total,
					PIN_NOEVICT)) अणु
			kमुक्त(r);
			अवरोध;
		पूर्ण

		r->next = reserved;
		reserved = r;

		count++;
	पूर्ण जबतक (1);
	drm_mm_हटाओ_node(&hole);
	mutex_unlock(&ggtt->vm.mutex);
	pr_info("Filled GGTT with %lu 1MiB nodes\n", count);

	/* Overfill the GGTT with context objects and so try to evict one. */
	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_sw_fence fence;

		count = 0;
		onstack_fence_init(&fence);
		करो अणु
			काष्ठा पूर्णांकel_context *ce;
			काष्ठा i915_request *rq;

			ce = पूर्णांकel_context_create(engine);
			अगर (IS_ERR(ce))
				अवरोध;

			/* We will need some GGTT space क्रम the rq's context */
			igt_evict_ctl.fail_अगर_busy = true;
			rq = पूर्णांकel_context_create_request(ce);
			igt_evict_ctl.fail_अगर_busy = false;
			पूर्णांकel_context_put(ce);

			अगर (IS_ERR(rq)) अणु
				/* When full, fail_अगर_busy will trigger EBUSY */
				अगर (PTR_ERR(rq) != -EBUSY) अणु
					pr_err("Unexpected error from request alloc (on %s): %d\n",
					       engine->name,
					       (पूर्णांक)PTR_ERR(rq));
					err = PTR_ERR(rq);
				पूर्ण
				अवरोध;
			पूर्ण

			/* Keep every request/ctx pinned until we are full */
			err = i915_sw_fence_aरुको_sw_fence_gfp(&rq->submit,
							       &fence,
							       GFP_KERNEL);
			अगर (err < 0)
				अवरोध;

			i915_request_add(rq);
			count++;
			err = 0;
		पूर्ण जबतक(1);
		onstack_fence_fini(&fence);
		pr_info("Submitted %lu contexts/requests on %s\n",
			count, engine->name);
		अगर (err)
			अवरोध;
	पूर्ण

	mutex_lock(&ggtt->vm.mutex);
out_locked:
	अगर (igt_flush_test(i915))
		err = -EIO;
	जबतक (reserved) अणु
		काष्ठा reserved *next = reserved->next;

		drm_mm_हटाओ_node(&reserved->node);
		kमुक्त(reserved);

		reserved = next;
	पूर्ण
	अगर (drm_mm_node_allocated(&hole))
		drm_mm_हटाओ_node(&hole);
	mutex_unlock(&ggtt->vm.mutex);
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);

	वापस err;
पूर्ण

पूर्णांक i915_gem_evict_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_evict_something),
		SUBTEST(igt_evict_क्रम_vma),
		SUBTEST(igt_evict_क्रम_cache_color),
		SUBTEST(igt_evict_vm),
		SUBTEST(igt_overcommit),
	पूर्ण;
	काष्ठा drm_i915_निजी *i915;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक err = 0;

	i915 = mock_gem_device();
	अगर (!i915)
		वापस -ENOMEM;

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref)
		err = i915_subtests(tests, &i915->gt);

	mock_destroy_device(i915);
	वापस err;
पूर्ण

पूर्णांक i915_gem_evict_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_evict_contexts),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
