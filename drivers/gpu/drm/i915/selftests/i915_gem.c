<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/अक्रमom.h>

#समावेश "gem/selftests/igt_gem_utils.h"
#समावेश "gem/selftests/mock_context.h"
#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"

#समावेश "i915_selftest.h"

#समावेश "igt_flush_test.h"
#समावेश "mock_drm.h"

अटल पूर्णांक चयन_to_context(काष्ठा i915_gem_context *ctx)
अणु
	काष्ठा i915_gem_engines_iter it;
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err = 0;

	क्रम_each_gem_engine(ce, i915_gem_context_lock_engines(ctx), it) अणु
		काष्ठा i915_request *rq;

		rq = पूर्णांकel_context_create_request(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		i915_request_add(rq);
	पूर्ण
	i915_gem_context_unlock_engines(ctx);

	वापस err;
पूर्ण

अटल व्योम trash_stolen(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	स्थिर u64 slot = ggtt->error_capture.start;
	स्थिर resource_माप_प्रकार size = resource_size(&i915->dsm);
	अचिन्हित दीर्घ page;
	u32 prng = 0x12345678;

	/* XXX: fsck. needs some more thought... */
	अगर (!i915_ggtt_has_aperture(ggtt))
		वापस;

	क्रम (page = 0; page < size; page += PAGE_SIZE) अणु
		स्थिर dma_addr_t dma = i915->dsm.start + page;
		u32 __iomem *s;
		पूर्णांक x;

		ggtt->vm.insert_page(&ggtt->vm, dma, slot, I915_CACHE_NONE, 0);

		s = io_mapping_map_atomic_wc(&ggtt->iomap, slot);
		क्रम (x = 0; x < PAGE_SIZE / माप(u32); x++) अणु
			prng = next_pseuकरो_अक्रमom32(prng);
			ioग_लिखो32(prng, &s[x]);
		पूर्ण
		io_mapping_unmap_atomic(s);
	पूर्ण

	ggtt->vm.clear_range(&ggtt->vm, slot, PAGE_SIZE);
पूर्ण

अटल व्योम simulate_hibernate(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_wakeref_t wakeref;

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	/*
	 * As a final sting in the tail, invalidate stolen. Under a real S4,
	 * stolen is lost and needs to be refilled on resume. However, under
	 * CI we merely करो S4-device testing (as full S4 is too unreliable
	 * क्रम स्वतःmated testing across a cluster), so to simulate the effect
	 * of stolen being trashed across S4, we trash it ourselves.
	 */
	trash_stolen(i915);

	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
पूर्ण

अटल पूर्णांक pm_prepare(काष्ठा drm_i915_निजी *i915)
अणु
	i915_gem_suspend(i915);

	वापस 0;
पूर्ण

अटल व्योम pm_suspend(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_wakeref_t wakeref;

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref) अणु
		i915_ggtt_suspend(&i915->ggtt);
		i915_gem_suspend_late(i915);
	पूर्ण
पूर्ण

अटल व्योम pm_hibernate(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_wakeref_t wakeref;

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref) अणु
		i915_ggtt_suspend(&i915->ggtt);

		i915_gem_मुक्तze(i915);
		i915_gem_मुक्तze_late(i915);
	पूर्ण
पूर्ण

अटल व्योम pm_resume(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_wakeref_t wakeref;

	/*
	 * Both suspend and hibernate follow the same wakeup path and assume
	 * that runसमय-pm just works.
	 */
	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref) अणु
		i915_ggtt_resume(&i915->ggtt);
		i915_gem_resume(i915);
	पूर्ण
पूर्ण

अटल पूर्णांक igt_gem_suspend(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_gem_context *ctx;
	काष्ठा file *file;
	पूर्णांक err;

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	err = -ENOMEM;
	ctx = live_context(i915, file);
	अगर (!IS_ERR(ctx))
		err = चयन_to_context(ctx);
	अगर (err)
		जाओ out;

	err = pm_prepare(i915);
	अगर (err)
		जाओ out;

	pm_suspend(i915);

	/* Here be dragons! Note that with S3RST any S3 may become S4! */
	simulate_hibernate(i915);

	pm_resume(i915);

	err = चयन_to_context(ctx);
out:
	fput(file);
	वापस err;
पूर्ण

अटल पूर्णांक igt_gem_hibernate(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_gem_context *ctx;
	काष्ठा file *file;
	पूर्णांक err;

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	err = -ENOMEM;
	ctx = live_context(i915, file);
	अगर (!IS_ERR(ctx))
		err = चयन_to_context(ctx);
	अगर (err)
		जाओ out;

	err = pm_prepare(i915);
	अगर (err)
		जाओ out;

	pm_hibernate(i915);

	/* Here be dragons! */
	simulate_hibernate(i915);

	pm_resume(i915);

	err = चयन_to_context(ctx);
out:
	fput(file);
	वापस err;
पूर्ण

अटल पूर्णांक igt_gem_ww_ctx(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj, *obj2;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err = 0;

	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	obj2 = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj2)) अणु
		err = PTR_ERR(obj2);
		जाओ put1;
	पूर्ण

	i915_gem_ww_ctx_init(&ww, true);
retry:
	/* Lock the objects, twice क्रम good measure (-EALREADY handling) */
	err = i915_gem_object_lock(obj, &ww);
	अगर (!err)
		err = i915_gem_object_lock_पूर्णांकerruptible(obj, &ww);
	अगर (!err)
		err = i915_gem_object_lock_पूर्णांकerruptible(obj2, &ww);
	अगर (!err)
		err = i915_gem_object_lock(obj2, &ww);

	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	i915_gem_object_put(obj2);
put1:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

पूर्णांक i915_gem_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_gem_suspend),
		SUBTEST(igt_gem_hibernate),
		SUBTEST(igt_gem_ww_ctx),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_live_subtests(tests, i915);
पूर्ण
