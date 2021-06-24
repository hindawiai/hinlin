<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2017-2018 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>

#समावेश "intel_context.h"
#समावेश "intel_engine_heartbeat.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_requests.h"
#समावेश "intel_ring.h"
#समावेश "selftest_engine_heartbeat.h"

#समावेश "../selftests/i915_random.h"
#समावेश "../i915_selftest.h"

#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/lib_sw_fence.h"
#समावेश "selftests/mock_gem_device.h"
#समावेश "selftests/mock_timeline.h"

अटल काष्ठा page *hwsp_page(काष्ठा पूर्णांकel_समयline *tl)
अणु
	काष्ठा drm_i915_gem_object *obj = tl->hwsp_ggtt->obj;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
	वापस sg_page(obj->mm.pages->sgl);
पूर्ण

अटल अचिन्हित दीर्घ hwsp_cacheline(काष्ठा पूर्णांकel_समयline *tl)
अणु
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)page_address(hwsp_page(tl));

	वापस (address + offset_in_page(tl->hwsp_offset)) / TIMELINE_SEQNO_BYTES;
पूर्ण

अटल पूर्णांक selftest_tl_pin(काष्ठा पूर्णांकel_समयline *tl)
अणु
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err;

	i915_gem_ww_ctx_init(&ww, false);
retry:
	err = i915_gem_object_lock(tl->hwsp_ggtt->obj, &ww);
	अगर (!err)
		err = पूर्णांकel_समयline_pin(tl, &ww);

	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	वापस err;
पूर्ण

/* Only half of seqno's are usable, see __पूर्णांकel_समयline_get_seqno() */
#घोषणा CACHELINES_PER_PAGE (PAGE_SIZE / TIMELINE_SEQNO_BYTES / 2)

काष्ठा mock_hwsp_मुक्तlist अणु
	काष्ठा पूर्णांकel_gt *gt;
	काष्ठा radix_tree_root cachelines;
	काष्ठा पूर्णांकel_समयline **history;
	अचिन्हित दीर्घ count, max;
	काष्ठा rnd_state prng;
पूर्ण;

क्रमागत अणु
	SHUFFLE = BIT(0),
पूर्ण;

अटल व्योम __mock_hwsp_record(काष्ठा mock_hwsp_मुक्तlist *state,
			       अचिन्हित पूर्णांक idx,
			       काष्ठा पूर्णांकel_समयline *tl)
अणु
	tl = xchg(&state->history[idx], tl);
	अगर (tl) अणु
		radix_tree_delete(&state->cachelines, hwsp_cacheline(tl));
		पूर्णांकel_समयline_unpin(tl);
		पूर्णांकel_समयline_put(tl);
	पूर्ण
पूर्ण

अटल पूर्णांक __mock_hwsp_समयline(काष्ठा mock_hwsp_मुक्तlist *state,
				अचिन्हित पूर्णांक count,
				अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_समयline *tl;
	अचिन्हित पूर्णांक idx;

	जबतक (count--) अणु
		अचिन्हित दीर्घ cacheline;
		पूर्णांक err;

		tl = पूर्णांकel_समयline_create(state->gt);
		अगर (IS_ERR(tl))
			वापस PTR_ERR(tl);

		err = selftest_tl_pin(tl);
		अगर (err) अणु
			पूर्णांकel_समयline_put(tl);
			वापस err;
		पूर्ण

		cacheline = hwsp_cacheline(tl);
		err = radix_tree_insert(&state->cachelines, cacheline, tl);
		अगर (err) अणु
			अगर (err == -EEXIST) अणु
				pr_err("HWSP cacheline %lu already used; duplicate allocation!\n",
				       cacheline);
			पूर्ण
			पूर्णांकel_समयline_unpin(tl);
			पूर्णांकel_समयline_put(tl);
			वापस err;
		पूर्ण

		idx = state->count++ % state->max;
		__mock_hwsp_record(state, idx, tl);
	पूर्ण

	अगर (flags & SHUFFLE)
		i915_pअक्रमom_shuffle(state->history,
				     माप(*state->history),
				     min(state->count, state->max),
				     &state->prng);

	count = i915_pअक्रमom_u32_max_state(min(state->count, state->max),
					   &state->prng);
	जबतक (count--) अणु
		idx = --state->count % state->max;
		__mock_hwsp_record(state, idx, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mock_hwsp_मुक्तlist(व्योम *arg)
अणु
	काष्ठा mock_hwsp_मुक्तlist state;
	काष्ठा drm_i915_निजी *i915;
	स्थिर काष्ठा अणु
		स्थिर अक्षर *name;
		अचिन्हित पूर्णांक flags;
	पूर्ण phases[] = अणु
		अणु "linear", 0 पूर्ण,
		अणु "shuffled", SHUFFLE पूर्ण,
		अणु पूर्ण,
	पूर्ण, *p;
	अचिन्हित पूर्णांक na;
	पूर्णांक err = 0;

	i915 = mock_gem_device();
	अगर (!i915)
		वापस -ENOMEM;

	INIT_RADIX_TREE(&state.cachelines, GFP_KERNEL);
	state.prng = I915_RND_STATE_INITIALIZER(i915_selftest.अक्रमom_seed);

	state.gt = &i915->gt;

	/*
	 * Create a bunch of समयlines and check that their HWSP करो not overlap.
	 * Free some, and try again.
	 */

	state.max = PAGE_SIZE / माप(*state.history);
	state.count = 0;
	state.history = kसुस्मृति(state.max, माप(*state.history), GFP_KERNEL);
	अगर (!state.history) अणु
		err = -ENOMEM;
		जाओ err_put;
	पूर्ण

	क्रम (p = phases; p->name; p++) अणु
		pr_debug("%s(%s)\n", __func__, p->name);
		क्रम_each_prime_number_from(na, 1, 2 * CACHELINES_PER_PAGE) अणु
			err = __mock_hwsp_समयline(&state, na, p->flags);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	क्रम (na = 0; na < state.max; na++)
		__mock_hwsp_record(&state, na, शून्य);
	kमुक्त(state.history);
err_put:
	mock_destroy_device(i915);
	वापस err;
पूर्ण

काष्ठा __igt_sync अणु
	स्थिर अक्षर *name;
	u32 seqno;
	bool expected;
	bool set;
पूर्ण;

अटल पूर्णांक __igt_sync(काष्ठा पूर्णांकel_समयline *tl,
		      u64 ctx,
		      स्थिर काष्ठा __igt_sync *p,
		      स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	अगर (__पूर्णांकel_समयline_sync_is_later(tl, ctx, p->seqno) != p->expected) अणु
		pr_err("%s: %s(ctx=%llu, seqno=%u) expected passed %s but failed\n",
		       name, p->name, ctx, p->seqno, yesno(p->expected));
		वापस -EINVAL;
	पूर्ण

	अगर (p->set) अणु
		ret = __पूर्णांकel_समयline_sync_set(tl, ctx, p->seqno);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_sync(व्योम *arg)
अणु
	स्थिर काष्ठा __igt_sync pass[] = अणु
		अणु "unset", 0, false, false पूर्ण,
		अणु "new", 0, false, true पूर्ण,
		अणु "0a", 0, true, true पूर्ण,
		अणु "1a", 1, false, true पूर्ण,
		अणु "1b", 1, true, true पूर्ण,
		अणु "0b", 0, true, false पूर्ण,
		अणु "2a", 2, false, true पूर्ण,
		अणु "4", 4, false, true पूर्ण,
		अणु "INT_MAX", पूर्णांक_उच्च, false, true पूर्ण,
		अणु "INT_MAX-1", पूर्णांक_उच्च-1, true, false पूर्ण,
		अणु "INT_MAX+1", (u32)पूर्णांक_उच्च+1, false, true पूर्ण,
		अणु "INT_MAX", पूर्णांक_उच्च, true, false पूर्ण,
		अणु "UINT_MAX", अच_पूर्णांक_उच्च, false, true पूर्ण,
		अणु "wrap", 0, false, true पूर्ण,
		अणु "unwrap", अच_पूर्णांक_उच्च, true, false पूर्ण,
		अणुपूर्ण,
	पूर्ण, *p;
	काष्ठा पूर्णांकel_समयline tl;
	पूर्णांक order, offset;
	पूर्णांक ret = -ENODEV;

	mock_समयline_init(&tl, 0);
	क्रम (p = pass; p->name; p++) अणु
		क्रम (order = 1; order < 64; order++) अणु
			क्रम (offset = -1; offset <= (order > 1); offset++) अणु
				u64 ctx = BIT_ULL(order) + offset;

				ret = __igt_sync(&tl, ctx, p, "1");
				अगर (ret)
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	mock_समयline_fini(&tl);

	mock_समयline_init(&tl, 0);
	क्रम (order = 1; order < 64; order++) अणु
		क्रम (offset = -1; offset <= (order > 1); offset++) अणु
			u64 ctx = BIT_ULL(order) + offset;

			क्रम (p = pass; p->name; p++) अणु
				ret = __igt_sync(&tl, ctx, p, "2");
				अगर (ret)
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	mock_समयline_fini(&tl);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक अक्रमom_engine(काष्ठा rnd_state *rnd)
अणु
	वापस i915_pअक्रमom_u32_max_state(I915_NUM_ENGINES, rnd);
पूर्ण

अटल पूर्णांक bench_sync(व्योम *arg)
अणु
	काष्ठा rnd_state prng;
	काष्ठा पूर्णांकel_समयline tl;
	अचिन्हित दीर्घ end_समय, count;
	u64 prng32_1M;
	kसमय_प्रकार kt;
	पूर्णांक order, last_order;

	mock_समयline_init(&tl, 0);

	/* Lookups from cache are very fast and so the अक्रमom number generation
	 * and the loop itself becomes a signअगरicant factor in the per-iteration
	 * timings. We try to compensate the results by measuring the overhead
	 * of the prng and subtract it from the reported results.
	 */
	pअक्रमom_seed_state(&prng, i915_selftest.अक्रमom_seed);
	count = 0;
	kt = kसमय_get();
	end_समय = jअगरfies + HZ/10;
	करो अणु
		u32 x;

		/* Make sure the compiler करोesn't optimise away the prng call */
		WRITE_ONCE(x, pअक्रमom_u32_state(&prng));

		count++;
	पूर्ण जबतक (!समय_after(jअगरfies, end_समय));
	kt = kसमय_sub(kसमय_get(), kt);
	pr_debug("%s: %lu random evaluations, %lluns/prng\n",
		 __func__, count, (दीर्घ दीर्घ)भाग64_ul(kसमय_प्रकारo_ns(kt), count));
	prng32_1M = भाग64_ul(kसमय_प्रकारo_ns(kt) << 20, count);

	/* Benchmark (only) setting अक्रमom context ids */
	pअक्रमom_seed_state(&prng, i915_selftest.अक्रमom_seed);
	count = 0;
	kt = kसमय_get();
	end_समय = jअगरfies + HZ/10;
	करो अणु
		u64 id = i915_pअक्रमom_u64_state(&prng);

		__पूर्णांकel_समयline_sync_set(&tl, id, 0);
		count++;
	पूर्ण जबतक (!समय_after(jअगरfies, end_समय));
	kt = kसमय_sub(kसमय_get(), kt);
	kt = kसमय_sub_ns(kt, (count * prng32_1M * 2) >> 20);
	pr_info("%s: %lu random insertions, %lluns/insert\n",
		__func__, count, (दीर्घ दीर्घ)भाग64_ul(kसमय_प्रकारo_ns(kt), count));

	/* Benchmark looking up the exact same context ids as we just set */
	pअक्रमom_seed_state(&prng, i915_selftest.अक्रमom_seed);
	end_समय = count;
	kt = kसमय_get();
	जबतक (end_समय--) अणु
		u64 id = i915_pअक्रमom_u64_state(&prng);

		अगर (!__पूर्णांकel_समयline_sync_is_later(&tl, id, 0)) अणु
			mock_समयline_fini(&tl);
			pr_err("Lookup of %llu failed\n", id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	kt = kसमय_sub(kसमय_get(), kt);
	kt = kसमय_sub_ns(kt, (count * prng32_1M * 2) >> 20);
	pr_info("%s: %lu random lookups, %lluns/lookup\n",
		__func__, count, (दीर्घ दीर्घ)भाग64_ul(kसमय_प्रकारo_ns(kt), count));

	mock_समयline_fini(&tl);
	cond_resched();

	mock_समयline_init(&tl, 0);

	/* Benchmark setting the first N (in order) contexts */
	count = 0;
	kt = kसमय_get();
	end_समय = jअगरfies + HZ/10;
	करो अणु
		__पूर्णांकel_समयline_sync_set(&tl, count++, 0);
	पूर्ण जबतक (!समय_after(jअगरfies, end_समय));
	kt = kसमय_sub(kसमय_get(), kt);
	pr_info("%s: %lu in-order insertions, %lluns/insert\n",
		__func__, count, (दीर्घ दीर्घ)भाग64_ul(kसमय_प्रकारo_ns(kt), count));

	/* Benchmark looking up the exact same context ids as we just set */
	end_समय = count;
	kt = kसमय_get();
	जबतक (end_समय--) अणु
		अगर (!__पूर्णांकel_समयline_sync_is_later(&tl, end_समय, 0)) अणु
			pr_err("Lookup of %lu failed\n", end_समय);
			mock_समयline_fini(&tl);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	kt = kसमय_sub(kसमय_get(), kt);
	pr_info("%s: %lu in-order lookups, %lluns/lookup\n",
		__func__, count, (दीर्घ दीर्घ)भाग64_ul(kसमय_प्रकारo_ns(kt), count));

	mock_समयline_fini(&tl);
	cond_resched();

	mock_समयline_init(&tl, 0);

	/* Benchmark searching क्रम a अक्रमom context id and maybe changing it */
	pअक्रमom_seed_state(&prng, i915_selftest.अक्रमom_seed);
	count = 0;
	kt = kसमय_get();
	end_समय = jअगरfies + HZ/10;
	करो अणु
		u32 id = अक्रमom_engine(&prng);
		u32 seqno = pअक्रमom_u32_state(&prng);

		अगर (!__पूर्णांकel_समयline_sync_is_later(&tl, id, seqno))
			__पूर्णांकel_समयline_sync_set(&tl, id, seqno);

		count++;
	पूर्ण जबतक (!समय_after(jअगरfies, end_समय));
	kt = kसमय_sub(kसमय_get(), kt);
	kt = kसमय_sub_ns(kt, (count * prng32_1M * 2) >> 20);
	pr_info("%s: %lu repeated insert/lookups, %lluns/op\n",
		__func__, count, (दीर्घ दीर्घ)भाग64_ul(kसमय_प्रकारo_ns(kt), count));
	mock_समयline_fini(&tl);
	cond_resched();

	/* Benchmark searching क्रम a known context id and changing the seqno */
	क्रम (last_order = 1, order = 1; order < 32;
	     (अणु पूर्णांक पंचांगp = last_order; last_order = order; order += पंचांगp; पूर्ण)) अणु
		अचिन्हित पूर्णांक mask = BIT(order) - 1;

		mock_समयline_init(&tl, 0);

		count = 0;
		kt = kसमय_get();
		end_समय = jअगरfies + HZ/10;
		करो अणु
			/* Without assuming too many details of the underlying
			 * implementation, try to identअगरy its phase-changes
			 * (अगर any)!
			 */
			u64 id = (u64)(count & mask) << order;

			__पूर्णांकel_समयline_sync_is_later(&tl, id, 0);
			__पूर्णांकel_समयline_sync_set(&tl, id, 0);

			count++;
		पूर्ण जबतक (!समय_after(jअगरfies, end_समय));
		kt = kसमय_sub(kसमय_get(), kt);
		pr_info("%s: %lu cyclic/%d insert/lookups, %lluns/op\n",
			__func__, count, order,
			(दीर्घ दीर्घ)भाग64_ul(kसमय_प्रकारo_ns(kt), count));
		mock_समयline_fini(&tl);
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_समयline_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(mock_hwsp_मुक्तlist),
		SUBTEST(igt_sync),
		SUBTEST(bench_sync),
	पूर्ण;

	वापस i915_subtests(tests, शून्य);
पूर्ण

अटल पूर्णांक emit_ggtt_store_dw(काष्ठा i915_request *rq, u32 addr, u32 value)
अणु
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	अगर (INTEL_GEN(rq->engine->i915) >= 8) अणु
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = addr;
		*cs++ = 0;
		*cs++ = value;
	पूर्ण अन्यथा अगर (INTEL_GEN(rq->engine->i915) >= 4) अणु
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = 0;
		*cs++ = addr;
		*cs++ = value;
	पूर्ण अन्यथा अणु
		*cs++ = MI_STORE_DWORD_IMM | MI_MEM_VIRTUAL;
		*cs++ = addr;
		*cs++ = value;
		*cs++ = MI_NOOP;
	पूर्ण

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल काष्ठा i915_request *
checked_tl_ग_लिखो(काष्ठा पूर्णांकel_समयline *tl, काष्ठा पूर्णांकel_engine_cs *engine, u32 value)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	err = selftest_tl_pin(tl);
	अगर (err) अणु
		rq = ERR_PTR(err);
		जाओ out;
	पूर्ण

	अगर (READ_ONCE(*tl->hwsp_seqno) != tl->seqno) अणु
		pr_err("Timeline created with incorrect breadcrumb, found %x, expected %x\n",
		       *tl->hwsp_seqno, tl->seqno);
		पूर्णांकel_समयline_unpin(tl);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	rq = पूर्णांकel_engine_create_kernel_request(engine);
	अगर (IS_ERR(rq))
		जाओ out_unpin;

	i915_request_get(rq);

	err = emit_ggtt_store_dw(rq, tl->hwsp_offset, value);
	i915_request_add(rq);
	अगर (err) अणु
		i915_request_put(rq);
		rq = ERR_PTR(err);
	पूर्ण

out_unpin:
	पूर्णांकel_समयline_unpin(tl);
out:
	अगर (IS_ERR(rq))
		pr_err("Failed to write to timeline!\n");
	वापस rq;
पूर्ण

अटल पूर्णांक live_hwsp_engine(व्योम *arg)
अणु
#घोषणा NUM_TIMELINES 4096
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_समयline **समयlines;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	अचिन्हित दीर्घ count, n;
	पूर्णांक err = 0;

	/*
	 * Create a bunch of समयlines and check we can ग_लिखो
	 * independently to each of their bपढ़ोcrumb slots.
	 */

	समयlines = kvदो_स्मृति_array(NUM_TIMELINES * I915_NUM_ENGINES,
				   माप(*समयlines),
				   GFP_KERNEL);
	अगर (!समयlines)
		वापस -ENOMEM;

	count = 0;
	क्रम_each_engine(engine, gt, id) अणु
		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		पूर्णांकel_engine_pm_get(engine);

		क्रम (n = 0; n < NUM_TIMELINES; n++) अणु
			काष्ठा पूर्णांकel_समयline *tl;
			काष्ठा i915_request *rq;

			tl = पूर्णांकel_समयline_create(gt);
			अगर (IS_ERR(tl)) अणु
				err = PTR_ERR(tl);
				अवरोध;
			पूर्ण

			rq = checked_tl_ग_लिखो(tl, engine, count);
			अगर (IS_ERR(rq)) अणु
				पूर्णांकel_समयline_put(tl);
				err = PTR_ERR(rq);
				अवरोध;
			पूर्ण

			समयlines[count++] = tl;
			i915_request_put(rq);
		पूर्ण

		पूर्णांकel_engine_pm_put(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	क्रम (n = 0; n < count; n++) अणु
		काष्ठा पूर्णांकel_समयline *tl = समयlines[n];

		अगर (!err && READ_ONCE(*tl->hwsp_seqno) != n) अणु
			GEM_TRACE_ERR("Invalid seqno:%lu stored in timeline %llu @ %x, found 0x%x\n",
				      n, tl->fence_context, tl->hwsp_offset, *tl->hwsp_seqno);
			GEM_TRACE_DUMP();
			err = -EINVAL;
		पूर्ण
		पूर्णांकel_समयline_put(tl);
	पूर्ण

	kvमुक्त(समयlines);
	वापस err;
#अघोषित NUM_TIMELINES
पूर्ण

अटल पूर्णांक live_hwsp_alternate(व्योम *arg)
अणु
#घोषणा NUM_TIMELINES 4096
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_समयline **समयlines;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	अचिन्हित दीर्घ count, n;
	पूर्णांक err = 0;

	/*
	 * Create a bunch of समयlines and check we can ग_लिखो
	 * independently to each of their bपढ़ोcrumb slots with adjacent
	 * engines.
	 */

	समयlines = kvदो_स्मृति_array(NUM_TIMELINES * I915_NUM_ENGINES,
				   माप(*समयlines),
				   GFP_KERNEL);
	अगर (!समयlines)
		वापस -ENOMEM;

	count = 0;
	क्रम (n = 0; n < NUM_TIMELINES; n++) अणु
		क्रम_each_engine(engine, gt, id) अणु
			काष्ठा पूर्णांकel_समयline *tl;
			काष्ठा i915_request *rq;

			अगर (!पूर्णांकel_engine_can_store_dword(engine))
				जारी;

			tl = पूर्णांकel_समयline_create(gt);
			अगर (IS_ERR(tl)) अणु
				err = PTR_ERR(tl);
				जाओ out;
			पूर्ण

			पूर्णांकel_engine_pm_get(engine);
			rq = checked_tl_ग_लिखो(tl, engine, count);
			पूर्णांकel_engine_pm_put(engine);
			अगर (IS_ERR(rq)) अणु
				पूर्णांकel_समयline_put(tl);
				err = PTR_ERR(rq);
				जाओ out;
			पूर्ण

			समयlines[count++] = tl;
			i915_request_put(rq);
		पूर्ण
	पूर्ण

out:
	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	क्रम (n = 0; n < count; n++) अणु
		काष्ठा पूर्णांकel_समयline *tl = समयlines[n];

		अगर (!err && READ_ONCE(*tl->hwsp_seqno) != n) अणु
			GEM_TRACE_ERR("Invalid seqno:%lu stored in timeline %llu @ %x, found 0x%x\n",
				      n, tl->fence_context, tl->hwsp_offset, *tl->hwsp_seqno);
			GEM_TRACE_DUMP();
			err = -EINVAL;
		पूर्ण
		पूर्णांकel_समयline_put(tl);
	पूर्ण

	kvमुक्त(समयlines);
	वापस err;
#अघोषित NUM_TIMELINES
पूर्ण

अटल पूर्णांक live_hwsp_wrap(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा पूर्णांकel_समयline *tl;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Across a seqno wrap, we need to keep the old cacheline alive क्रम
	 * क्रमeign GPU references.
	 */

	tl = पूर्णांकel_समयline_create(gt);
	अगर (IS_ERR(tl))
		वापस PTR_ERR(tl);

	अगर (!tl->has_initial_bपढ़ोcrumb)
		जाओ out_मुक्त;

	err = selftest_tl_pin(tl);
	अगर (err)
		जाओ out_मुक्त;

	क्रम_each_engine(engine, gt, id) अणु
		स्थिर u32 *hwsp_seqno[2];
		काष्ठा i915_request *rq;
		u32 seqno[2];

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		rq = पूर्णांकel_engine_create_kernel_request(engine);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out;
		पूर्ण

		tl->seqno = -4u;

		mutex_lock_nested(&tl->mutex, SINGLE_DEPTH_NESTING);
		err = पूर्णांकel_समयline_get_seqno(tl, rq, &seqno[0]);
		mutex_unlock(&tl->mutex);
		अगर (err) अणु
			i915_request_add(rq);
			जाओ out;
		पूर्ण
		pr_debug("seqno[0]:%08x, hwsp_offset:%08x\n",
			 seqno[0], tl->hwsp_offset);

		err = emit_ggtt_store_dw(rq, tl->hwsp_offset, seqno[0]);
		अगर (err) अणु
			i915_request_add(rq);
			जाओ out;
		पूर्ण
		hwsp_seqno[0] = tl->hwsp_seqno;

		mutex_lock_nested(&tl->mutex, SINGLE_DEPTH_NESTING);
		err = पूर्णांकel_समयline_get_seqno(tl, rq, &seqno[1]);
		mutex_unlock(&tl->mutex);
		अगर (err) अणु
			i915_request_add(rq);
			जाओ out;
		पूर्ण
		pr_debug("seqno[1]:%08x, hwsp_offset:%08x\n",
			 seqno[1], tl->hwsp_offset);

		err = emit_ggtt_store_dw(rq, tl->hwsp_offset, seqno[1]);
		अगर (err) अणु
			i915_request_add(rq);
			जाओ out;
		पूर्ण
		hwsp_seqno[1] = tl->hwsp_seqno;

		/* With wrap should come a new hwsp */
		GEM_BUG_ON(seqno[1] >= seqno[0]);
		GEM_BUG_ON(hwsp_seqno[0] == hwsp_seqno[1]);

		i915_request_add(rq);

		अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
			pr_err("Wait for timeline writes timed out!\n");
			err = -EIO;
			जाओ out;
		पूर्ण

		अगर (READ_ONCE(*hwsp_seqno[0]) != seqno[0] ||
		    READ_ONCE(*hwsp_seqno[1]) != seqno[1]) अणु
			pr_err("Bad timeline values: found (%x, %x), expected (%x, %x)\n",
			       *hwsp_seqno[0], *hwsp_seqno[1],
			       seqno[0], seqno[1]);
			err = -EINVAL;
			जाओ out;
		पूर्ण

		पूर्णांकel_gt_retire_requests(gt); /* recycle HWSP */
	पूर्ण

out:
	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	पूर्णांकel_समयline_unpin(tl);
out_मुक्त:
	पूर्णांकel_समयline_put(tl);
	वापस err;
पूर्ण

अटल पूर्णांक emit_पढ़ो_hwsp(काष्ठा i915_request *rq,
			  u32 seqno, u32 hwsp,
			  u32 *addr)
अणु
	स्थिर u32 gpr = i915_mmio_reg_offset(GEN8_RING_CS_GPR(rq->engine->mmio_base, 0));
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 12);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = *addr;
	*cs++ = 0;
	*cs++ = seqno;
	*addr += 4;

	*cs++ = MI_LOAD_REGISTER_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = gpr;
	*cs++ = hwsp;
	*cs++ = 0;

	*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = gpr;
	*cs++ = *addr;
	*cs++ = 0;
	*addr += 4;

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

काष्ठा hwsp_watcher अणु
	काष्ठा i915_vma *vma;
	काष्ठा i915_request *rq;
	u32 addr;
	u32 *map;
पूर्ण;

अटल bool cmp_lt(u32 a, u32 b)
अणु
	वापस a < b;
पूर्ण

अटल bool cmp_gte(u32 a, u32 b)
अणु
	वापस a >= b;
पूर्ण

अटल पूर्णांक setup_watcher(काष्ठा hwsp_watcher *w, काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, SZ_2M);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	w->map = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(w->map)) अणु
		i915_gem_object_put(obj);
		वापस PTR_ERR(w->map);
	पूर्ण

	vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0, 0);
	अगर (IS_ERR(vma)) अणु
		i915_gem_object_put(obj);
		वापस PTR_ERR(vma);
	पूर्ण

	w->vma = vma;
	w->addr = i915_ggtt_offset(vma);
	वापस 0;
पूर्ण

अटल व्योम चयन_tl_lock(काष्ठा i915_request *from, काष्ठा i915_request *to)
अणु
	/* some light mutex juggling required; think co-routines */

	अगर (from) अणु
		lockdep_unpin_lock(&from->context->समयline->mutex, from->cookie);
		mutex_unlock(&from->context->समयline->mutex);
	पूर्ण

	अगर (to) अणु
		mutex_lock(&to->context->समयline->mutex);
		to->cookie = lockdep_pin_lock(&to->context->समयline->mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक create_watcher(काष्ठा hwsp_watcher *w,
			  काष्ठा पूर्णांकel_engine_cs *engine,
			  पूर्णांक ringsz)
अणु
	काष्ठा पूर्णांकel_context *ce;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	ce->ring = __पूर्णांकel_context_ring_size(ringsz);
	w->rq = पूर्णांकel_context_create_request(ce);
	पूर्णांकel_context_put(ce);
	अगर (IS_ERR(w->rq))
		वापस PTR_ERR(w->rq);

	w->addr = i915_ggtt_offset(w->vma);

	चयन_tl_lock(w->rq, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक check_watcher(काष्ठा hwsp_watcher *w, स्थिर अक्षर *name,
			 bool (*op)(u32 hwsp, u32 seqno))
अणु
	काष्ठा i915_request *rq = fetch_and_zero(&w->rq);
	u32 offset, end;
	पूर्णांक err;

	GEM_BUG_ON(w->addr - i915_ggtt_offset(w->vma) > w->vma->size);

	i915_request_get(rq);
	चयन_tl_lock(शून्य, rq);
	i915_request_add(rq);

	अगर (i915_request_रुको(rq, 0, HZ) < 0) अणु
		err = -ETIME;
		जाओ out;
	पूर्ण

	err = 0;
	offset = 0;
	end = (w->addr - i915_ggtt_offset(w->vma)) / माप(*w->map);
	जबतक (offset < end) अणु
		अगर (!op(w->map[offset + 1], w->map[offset])) अणु
			pr_err("Watcher '%s' found HWSP value %x for seqno %x\n",
			       name, w->map[offset + 1], w->map[offset]);
			err = -EINVAL;
		पूर्ण

		offset += 2;
	पूर्ण

out:
	i915_request_put(rq);
	वापस err;
पूर्ण

अटल व्योम cleanup_watcher(काष्ठा hwsp_watcher *w)
अणु
	अगर (w->rq) अणु
		चयन_tl_lock(शून्य, w->rq);

		i915_request_add(w->rq);
	पूर्ण

	i915_vma_unpin_and_release(&w->vma, I915_VMA_RELEASE_MAP);
पूर्ण

अटल bool retire_requests(काष्ठा पूर्णांकel_समयline *tl)
अणु
	काष्ठा i915_request *rq, *rn;

	mutex_lock(&tl->mutex);
	list_क्रम_each_entry_safe(rq, rn, &tl->requests, link)
		अगर (!i915_request_retire(rq))
			अवरोध;
	mutex_unlock(&tl->mutex);

	वापस !i915_active_fence_isset(&tl->last_request);
पूर्ण

अटल काष्ठा i915_request *wrap_समयline(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_context *ce = rq->context;
	काष्ठा पूर्णांकel_समयline *tl = ce->समयline;
	u32 seqno = rq->fence.seqno;

	जबतक (tl->seqno >= seqno) अणु /* Cause a wrap */
		i915_request_put(rq);
		rq = पूर्णांकel_context_create_request(ce);
		अगर (IS_ERR(rq))
			वापस rq;

		i915_request_get(rq);
		i915_request_add(rq);
	पूर्ण

	i915_request_put(rq);
	rq = i915_request_create(ce);
	अगर (IS_ERR(rq))
		वापस rq;

	i915_request_get(rq);
	i915_request_add(rq);

	वापस rq;
पूर्ण

अटल पूर्णांक live_hwsp_पढ़ो(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा hwsp_watcher watcher[2] = अणुपूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा पूर्णांकel_समयline *tl;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;
	पूर्णांक i;

	/*
	 * If we take a reference to the HWSP क्रम पढ़ोing on the GPU, that
	 * पढ़ो may be arbitrarily delayed (either by क्रमeign fence or
	 * priority saturation) and a wrap can happen within 30 minutes.
	 * When the GPU पढ़ो is finally submitted it should be correct,
	 * even across multiple wraps.
	 */

	अगर (INTEL_GEN(gt->i915) < 8) /* CS convenience [SRM/LRM] */
		वापस 0;

	tl = पूर्णांकel_समयline_create(gt);
	अगर (IS_ERR(tl))
		वापस PTR_ERR(tl);

	अगर (!tl->has_initial_bपढ़ोcrumb)
		जाओ out_मुक्त;

	क्रम (i = 0; i < ARRAY_SIZE(watcher); i++) अणु
		err = setup_watcher(&watcher[i], gt);
		अगर (err)
			जाओ out;
	पूर्ण

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;
		अचिन्हित दीर्घ count = 0;
		IGT_TIMEOUT(end_समय);

		/* Create a request we can use क्रम remote पढ़ोing of the HWSP */
		err = create_watcher(&watcher[1], engine, SZ_512K);
		अगर (err)
			जाओ out;

		करो अणु
			काष्ठा i915_sw_fence *submit;
			काष्ठा i915_request *rq;
			u32 hwsp, dummy;

			submit = heap_fence_create(GFP_KERNEL);
			अगर (!submit) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण

			err = create_watcher(&watcher[0], engine, SZ_4K);
			अगर (err)
				जाओ out;

			ce = पूर्णांकel_context_create(engine);
			अगर (IS_ERR(ce)) अणु
				err = PTR_ERR(ce);
				जाओ out;
			पूर्ण

			ce->समयline = पूर्णांकel_समयline_get(tl);

			/* Ensure समयline is mapped, करोne during first pin */
			err = पूर्णांकel_context_pin(ce);
			अगर (err) अणु
				पूर्णांकel_context_put(ce);
				जाओ out;
			पूर्ण

			/*
			 * Start at a new wrap, and set seqno right beक्रमe another wrap,
			 * saving 30 minutes of nops
			 */
			tl->seqno = -12u + 2 * (count & 3);
			__पूर्णांकel_समयline_get_seqno(tl, &dummy);

			rq = i915_request_create(ce);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				पूर्णांकel_context_unpin(ce);
				पूर्णांकel_context_put(ce);
				जाओ out;
			पूर्ण

			err = i915_sw_fence_aरुको_dma_fence(&rq->submit,
							    &watcher[0].rq->fence, 0,
							    GFP_KERNEL);
			अगर (err < 0) अणु
				i915_request_add(rq);
				पूर्णांकel_context_unpin(ce);
				पूर्णांकel_context_put(ce);
				जाओ out;
			पूर्ण

			चयन_tl_lock(rq, watcher[0].rq);
			err = पूर्णांकel_समयline_पढ़ो_hwsp(rq, watcher[0].rq, &hwsp);
			अगर (err == 0)
				err = emit_पढ़ो_hwsp(watcher[0].rq, /* beक्रमe */
						     rq->fence.seqno, hwsp,
						     &watcher[0].addr);
			चयन_tl_lock(watcher[0].rq, rq);
			अगर (err) अणु
				i915_request_add(rq);
				पूर्णांकel_context_unpin(ce);
				पूर्णांकel_context_put(ce);
				जाओ out;
			पूर्ण

			चयन_tl_lock(rq, watcher[1].rq);
			err = पूर्णांकel_समयline_पढ़ो_hwsp(rq, watcher[1].rq, &hwsp);
			अगर (err == 0)
				err = emit_पढ़ो_hwsp(watcher[1].rq, /* after */
						     rq->fence.seqno, hwsp,
						     &watcher[1].addr);
			चयन_tl_lock(watcher[1].rq, rq);
			अगर (err) अणु
				i915_request_add(rq);
				पूर्णांकel_context_unpin(ce);
				पूर्णांकel_context_put(ce);
				जाओ out;
			पूर्ण

			i915_request_get(rq);
			i915_request_add(rq);

			rq = wrap_समयline(rq);
			पूर्णांकel_context_unpin(ce);
			पूर्णांकel_context_put(ce);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				जाओ out;
			पूर्ण

			err = i915_sw_fence_aरुको_dma_fence(&watcher[1].rq->submit,
							    &rq->fence, 0,
							    GFP_KERNEL);
			अगर (err < 0) अणु
				i915_request_put(rq);
				जाओ out;
			पूर्ण

			err = check_watcher(&watcher[0], "before", cmp_lt);
			i915_sw_fence_commit(submit);
			heap_fence_put(submit);
			अगर (err) अणु
				i915_request_put(rq);
				जाओ out;
			पूर्ण
			count++;

			/* Flush the समयline beक्रमe manually wrapping again */
			अगर (i915_request_रुको(rq,
					      I915_WAIT_INTERRUPTIBLE,
					      HZ) < 0) अणु
				err = -ETIME;
				i915_request_put(rq);
				जाओ out;
			पूर्ण
			retire_requests(tl);
			i915_request_put(rq);

			/* Single requests are limited to half a ring at most */
			अगर (8 * watcher[1].rq->ring->emit >
			    3 * watcher[1].rq->ring->size)
				अवरोध;

		पूर्ण जबतक (!__igt_समयout(end_समय, शून्य) &&
			 count < (PAGE_SIZE / TIMELINE_SEQNO_BYTES - 1) / 2);

		pr_info("%s: simulated %lu wraps\n", engine->name, count);
		err = check_watcher(&watcher[1], "after", cmp_gte);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	क्रम (i = 0; i < ARRAY_SIZE(watcher); i++)
		cleanup_watcher(&watcher[i]);

	अगर (igt_flush_test(gt->i915))
		err = -EIO;

out_मुक्त:
	पूर्णांकel_समयline_put(tl);
	वापस err;
पूर्ण

अटल पूर्णांक live_hwsp_rollover_kernel(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Run the host क्रम दीर्घ enough, and even the kernel context will
	 * see a seqno rollover.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
		काष्ठा पूर्णांकel_समयline *tl = ce->समयline;
		काष्ठा i915_request *rq[3] = अणुपूर्ण;
		पूर्णांक i;

		st_engine_heartbeat_disable(engine);
		अगर (पूर्णांकel_gt_रुको_क्रम_idle(gt, HZ / 2)) अणु
			err = -EIO;
			जाओ out;
		पूर्ण

		GEM_BUG_ON(i915_active_fence_isset(&tl->last_request));
		tl->seqno = -2u;
		WRITE_ONCE(*(u32 *)tl->hwsp_seqno, tl->seqno);

		क्रम (i = 0; i < ARRAY_SIZE(rq); i++) अणु
			काष्ठा i915_request *this;

			this = i915_request_create(ce);
			अगर (IS_ERR(this)) अणु
				err = PTR_ERR(this);
				जाओ out;
			पूर्ण

			pr_debug("%s: create fence.seqnp:%d\n",
				 engine->name,
				 lower_32_bits(this->fence.seqno));

			GEM_BUG_ON(rcu_access_poपूर्णांकer(this->समयline) != tl);

			rq[i] = i915_request_get(this);
			i915_request_add(this);
		पूर्ण

		/* We expected a wrap! */
		GEM_BUG_ON(rq[2]->fence.seqno > rq[0]->fence.seqno);

		अगर (i915_request_रुको(rq[2], 0, HZ / 5) < 0) अणु
			pr_err("Wait for timeline wrap timed out!\n");
			err = -EIO;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(rq); i++) अणु
			अगर (!i915_request_completed(rq[i])) अणु
				pr_err("Pre-wrap request not completed!\n");
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण

out:
		क्रम (i = 0; i < ARRAY_SIZE(rq); i++)
			i915_request_put(rq[i]);
		st_engine_heartbeat_enable(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक live_hwsp_rollover_user(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Simulate a दीर्घ running user context, and क्रमce the seqno wrap
	 * on the user's समयline.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *rq[3] = अणुपूर्ण;
		काष्ठा पूर्णांकel_समयline *tl;
		काष्ठा पूर्णांकel_context *ce;
		पूर्णांक i;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce))
			वापस PTR_ERR(ce);

		err = पूर्णांकel_context_alloc_state(ce);
		अगर (err)
			जाओ out;

		tl = ce->समयline;
		अगर (!tl->has_initial_bपढ़ोcrumb)
			जाओ out;

		err = पूर्णांकel_context_pin(ce);
		अगर (err)
			जाओ out;

		tl->seqno = -4u;
		WRITE_ONCE(*(u32 *)tl->hwsp_seqno, tl->seqno);

		क्रम (i = 0; i < ARRAY_SIZE(rq); i++) अणु
			काष्ठा i915_request *this;

			this = पूर्णांकel_context_create_request(ce);
			अगर (IS_ERR(this)) अणु
				err = PTR_ERR(this);
				जाओ out_unpin;
			पूर्ण

			pr_debug("%s: create fence.seqnp:%d\n",
				 engine->name,
				 lower_32_bits(this->fence.seqno));

			GEM_BUG_ON(rcu_access_poपूर्णांकer(this->समयline) != tl);

			rq[i] = i915_request_get(this);
			i915_request_add(this);
		पूर्ण

		/* We expected a wrap! */
		GEM_BUG_ON(rq[2]->fence.seqno > rq[0]->fence.seqno);

		अगर (i915_request_रुको(rq[2], 0, HZ / 5) < 0) अणु
			pr_err("Wait for timeline wrap timed out!\n");
			err = -EIO;
			जाओ out_unpin;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(rq); i++) अणु
			अगर (!i915_request_completed(rq[i])) अणु
				pr_err("Pre-wrap request not completed!\n");
				err = -EINVAL;
				जाओ out_unpin;
			पूर्ण
		पूर्ण
out_unpin:
		पूर्णांकel_context_unpin(ce);
out:
		क्रम (i = 0; i < ARRAY_SIZE(rq); i++)
			i915_request_put(rq[i]);
		पूर्णांकel_context_put(ce);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक live_hwsp_recycle(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	अचिन्हित दीर्घ count;
	पूर्णांक err = 0;

	/*
	 * Check seqno ग_लिखोs पूर्णांकo one समयline at a समय. We expect to
	 * recycle the bपढ़ोcrumb slot between iterations and neither
	 * want to confuse ourselves or the GPU.
	 */

	count = 0;
	क्रम_each_engine(engine, gt, id) अणु
		IGT_TIMEOUT(end_समय);

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		पूर्णांकel_engine_pm_get(engine);

		करो अणु
			काष्ठा पूर्णांकel_समयline *tl;
			काष्ठा i915_request *rq;

			tl = पूर्णांकel_समयline_create(gt);
			अगर (IS_ERR(tl)) अणु
				err = PTR_ERR(tl);
				अवरोध;
			पूर्ण

			rq = checked_tl_ग_लिखो(tl, engine, count);
			अगर (IS_ERR(rq)) अणु
				पूर्णांकel_समयline_put(tl);
				err = PTR_ERR(rq);
				अवरोध;
			पूर्ण

			अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
				pr_err("Wait for timeline writes timed out!\n");
				i915_request_put(rq);
				पूर्णांकel_समयline_put(tl);
				err = -EIO;
				अवरोध;
			पूर्ण

			अगर (READ_ONCE(*tl->hwsp_seqno) != count) अणु
				GEM_TRACE_ERR("Invalid seqno:%lu stored in timeline %llu @ %x found 0x%x\n",
					      count, tl->fence_context,
					      tl->hwsp_offset, *tl->hwsp_seqno);
				GEM_TRACE_DUMP();
				err = -EINVAL;
			पूर्ण

			i915_request_put(rq);
			पूर्णांकel_समयline_put(tl);
			count++;

			अगर (err)
				अवरोध;
		पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));

		पूर्णांकel_engine_pm_put(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_समयline_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_hwsp_recycle),
		SUBTEST(live_hwsp_engine),
		SUBTEST(live_hwsp_alternate),
		SUBTEST(live_hwsp_wrap),
		SUBTEST(live_hwsp_पढ़ो),
		SUBTEST(live_hwsp_rollover_kernel),
		SUBTEST(live_hwsp_rollover_user),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
