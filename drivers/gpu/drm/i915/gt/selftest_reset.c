<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/crc32.h>

#समावेश "gem/i915_gem_stolen.h"

#समावेश "i915_memcpy.h"
#समावेश "i915_selftest.h"
#समावेश "intel_gpu_commands.h"
#समावेश "selftests/igt_reset.h"
#समावेश "selftests/igt_atomic.h"
#समावेश "selftests/igt_spinner.h"

अटल पूर्णांक
__igt_reset_stolen(काष्ठा पूर्णांकel_gt *gt,
		   पूर्णांकel_engine_mask_t mask,
		   स्थिर अक्षर *msg)
अणु
	काष्ठा i915_ggtt *ggtt = &gt->i915->ggtt;
	स्थिर काष्ठा resource *dsm = &gt->i915->dsm;
	resource_माप_प्रकार num_pages, page;
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांकel_wakeref_t wakeref;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा igt_spinner spin;
	दीर्घ max, count;
	व्योम *पंचांगp;
	u32 *crc;
	पूर्णांक err;

	अगर (!drm_mm_node_allocated(&ggtt->error_capture))
		वापस 0;

	num_pages = resource_size(dsm) >> PAGE_SHIFT;
	अगर (!num_pages)
		वापस 0;

	crc = kदो_स्मृति_array(num_pages, माप(u32), GFP_KERNEL);
	अगर (!crc)
		वापस -ENOMEM;

	पंचांगp = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!पंचांगp) अणु
		err = -ENOMEM;
		जाओ err_crc;
	पूर्ण

	igt_global_reset_lock(gt);
	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);

	err = igt_spinner_init(&spin, gt);
	अगर (err)
		जाओ err_lock;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;
		काष्ठा i915_request *rq;

		अगर (!(mask & engine->mask))
			जारी;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ err_spin;
		पूर्ण
		rq = igt_spinner_create_request(&spin, ce, MI_ARB_CHECK);
		पूर्णांकel_context_put(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_spin;
		पूर्ण
		i915_request_add(rq);
	पूर्ण

	क्रम (page = 0; page < num_pages; page++) अणु
		dma_addr_t dma = (dma_addr_t)dsm->start + (page << PAGE_SHIFT);
		व्योम __iomem *s;
		व्योम *in;

		ggtt->vm.insert_page(&ggtt->vm, dma,
				     ggtt->error_capture.start,
				     I915_CACHE_NONE, 0);
		mb();

		s = io_mapping_map_wc(&ggtt->iomap,
				      ggtt->error_capture.start,
				      PAGE_SIZE);

		अगर (!__drm_mm_पूर्णांकerval_first(&gt->i915->mm.stolen,
					     page << PAGE_SHIFT,
					     ((page + 1) << PAGE_SHIFT) - 1))
			स_रखो_io(s, STACK_MAGIC, PAGE_SIZE);

		in = (व्योम __क्रमce *)s;
		अगर (i915_स_नकल_from_wc(पंचांगp, in, PAGE_SIZE))
			in = पंचांगp;
		crc[page] = crc32_le(0, in, PAGE_SIZE);

		io_mapping_unmap(s);
	पूर्ण
	mb();
	ggtt->vm.clear_range(&ggtt->vm, ggtt->error_capture.start, PAGE_SIZE);

	अगर (mask == ALL_ENGINES) अणु
		पूर्णांकel_gt_reset(gt, mask, शून्य);
	पूर्ण अन्यथा अणु
		क्रम_each_engine(engine, gt, id) अणु
			अगर (mask & engine->mask)
				पूर्णांकel_engine_reset(engine, शून्य);
		पूर्ण
	पूर्ण

	max = -1;
	count = 0;
	क्रम (page = 0; page < num_pages; page++) अणु
		dma_addr_t dma = (dma_addr_t)dsm->start + (page << PAGE_SHIFT);
		व्योम __iomem *s;
		व्योम *in;
		u32 x;

		ggtt->vm.insert_page(&ggtt->vm, dma,
				     ggtt->error_capture.start,
				     I915_CACHE_NONE, 0);
		mb();

		s = io_mapping_map_wc(&ggtt->iomap,
				      ggtt->error_capture.start,
				      PAGE_SIZE);

		in = (व्योम __क्रमce *)s;
		अगर (i915_स_नकल_from_wc(पंचांगp, in, PAGE_SIZE))
			in = पंचांगp;
		x = crc32_le(0, in, PAGE_SIZE);

		अगर (x != crc[page] &&
		    !__drm_mm_पूर्णांकerval_first(&gt->i915->mm.stolen,
					     page << PAGE_SHIFT,
					     ((page + 1) << PAGE_SHIFT) - 1)) अणु
			pr_debug("unused stolen page %pa modified by GPU reset\n",
				 &page);
			अगर (count++ == 0)
				igt_hexdump(in, PAGE_SIZE);
			max = page;
		पूर्ण

		io_mapping_unmap(s);
	पूर्ण
	mb();
	ggtt->vm.clear_range(&ggtt->vm, ggtt->error_capture.start, PAGE_SIZE);

	अगर (count > 0) अणु
		pr_info("%s reset clobbered %ld pages of stolen, last clobber at page %ld\n",
			msg, count, max);
	पूर्ण
	अगर (max >= I915_GEM_STOLEN_BIAS >> PAGE_SHIFT) अणु
		pr_err("%s reset clobbered unreserved area [above %x] of stolen; may cause severe faults\n",
		       msg, I915_GEM_STOLEN_BIAS);
		err = -EINVAL;
	पूर्ण

err_spin:
	igt_spinner_fini(&spin);

err_lock:
	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
	igt_global_reset_unlock(gt);

	kमुक्त(पंचांगp);
err_crc:
	kमुक्त(crc);
	वापस err;
पूर्ण

अटल पूर्णांक igt_reset_device_stolen(व्योम *arg)
अणु
	वापस __igt_reset_stolen(arg, ALL_ENGINES, "device");
पूर्ण

अटल पूर्णांक igt_reset_engines_stolen(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err;

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		err = __igt_reset_stolen(gt, engine->mask, engine->name);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_global_reset(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	अचिन्हित पूर्णांक reset_count;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक err = 0;

	/* Check that we can issue a global GPU reset */

	igt_global_reset_lock(gt);
	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);

	reset_count = i915_reset_count(&gt->i915->gpu_error);

	पूर्णांकel_gt_reset(gt, ALL_ENGINES, शून्य);

	अगर (i915_reset_count(&gt->i915->gpu_error) == reset_count) अणु
		pr_err("No GPU reset recorded!\n");
		err = -EINVAL;
	पूर्ण

	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
	igt_global_reset_unlock(gt);

	अगर (पूर्णांकel_gt_is_wedged(gt))
		err = -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक igt_wedged_reset(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	पूर्णांकel_wakeref_t wakeref;

	/* Check that we can recover a wedged device with a GPU reset */

	igt_global_reset_lock(gt);
	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);

	पूर्णांकel_gt_set_wedged(gt);

	GEM_BUG_ON(!पूर्णांकel_gt_is_wedged(gt));
	पूर्णांकel_gt_reset(gt, ALL_ENGINES, शून्य);

	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
	igt_global_reset_unlock(gt);

	वापस पूर्णांकel_gt_is_wedged(gt) ? -EIO : 0;
पूर्ण

अटल पूर्णांक igt_atomic_reset(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	स्थिर typeof(*igt_atomic_phases) *p;
	पूर्णांक err = 0;

	/* Check that the resets are usable from atomic context */

	पूर्णांकel_gt_pm_get(gt);
	igt_global_reset_lock(gt);

	/* Flush any requests beक्रमe we get started and check basics */
	अगर (!igt_क्रमce_reset(gt))
		जाओ unlock;

	क्रम (p = igt_atomic_phases; p->name; p++) अणु
		पूर्णांकel_engine_mask_t awake;

		GEM_TRACE("__intel_gt_reset under %s\n", p->name);

		awake = reset_prepare(gt);
		p->critical_section_begin();

		err = __पूर्णांकel_gt_reset(gt, ALL_ENGINES);

		p->critical_section_end();
		reset_finish(gt, awake);

		अगर (err) अणु
			pr_err("__intel_gt_reset failed under %s\n", p->name);
			अवरोध;
		पूर्ण
	पूर्ण

	/* As we poke around the guts, करो a full reset beक्रमe continuing. */
	igt_क्रमce_reset(gt);

unlock:
	igt_global_reset_unlock(gt);
	पूर्णांकel_gt_pm_put(gt);

	वापस err;
पूर्ण

अटल पूर्णांक igt_atomic_engine_reset(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	स्थिर typeof(*igt_atomic_phases) *p;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/* Check that the resets are usable from atomic context */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0;

	पूर्णांकel_gt_pm_get(gt);
	igt_global_reset_lock(gt);

	/* Flush any requests beक्रमe we get started and check basics */
	अगर (!igt_क्रमce_reset(gt))
		जाओ out_unlock;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा tasklet_काष्ठा *t = &engine->execlists.tasklet;

		अगर (t->func)
			tasklet_disable(t);
		पूर्णांकel_engine_pm_get(engine);

		क्रम (p = igt_atomic_phases; p->name; p++) अणु
			GEM_TRACE("intel_engine_reset(%s) under %s\n",
				  engine->name, p->name);
			अगर (म_भेद(p->name, "softirq"))
				local_bh_disable();

			p->critical_section_begin();
			err = __पूर्णांकel_engine_reset_bh(engine, शून्य);
			p->critical_section_end();

			अगर (म_भेद(p->name, "softirq"))
				local_bh_enable();

			अगर (err) अणु
				pr_err("intel_engine_reset(%s) failed under %s\n",
				       engine->name, p->name);
				अवरोध;
			पूर्ण
		पूर्ण

		पूर्णांकel_engine_pm_put(engine);
		अगर (t->func) अणु
			tasklet_enable(t);
			tasklet_hi_schedule(t);
		पूर्ण
		अगर (err)
			अवरोध;
	पूर्ण

	/* As we poke around the guts, करो a full reset beक्रमe continuing. */
	igt_क्रमce_reset(gt);

out_unlock:
	igt_global_reset_unlock(gt);
	पूर्णांकel_gt_pm_put(gt);

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_reset_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_global_reset), /* attempt to recover GPU first */
		SUBTEST(igt_reset_device_stolen),
		SUBTEST(igt_reset_engines_stolen),
		SUBTEST(igt_wedged_reset),
		SUBTEST(igt_atomic_reset),
		SUBTEST(igt_atomic_engine_reset),
	पूर्ण;
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;

	अगर (!पूर्णांकel_has_gpu_reset(gt))
		वापस 0;

	अगर (पूर्णांकel_gt_is_wedged(gt))
		वापस -EIO; /* we're दीर्घ past hope of a successful reset */

	वापस पूर्णांकel_gt_live_subtests(tests, gt);
पूर्ण
