<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2017 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>

#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_requests.h"
#समावेश "gt/intel_reset.h"
#समावेश "i915_selftest.h"

#समावेश "gem/selftests/igt_gem_utils.h"
#समावेश "selftests/i915_random.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/igt_live_test.h"
#समावेश "selftests/igt_reset.h"
#समावेश "selftests/igt_spinner.h"
#समावेश "selftests/mock_drm.h"
#समावेश "selftests/mock_gem_device.h"

#समावेश "huge_gem_object.h"
#समावेश "igt_gem_utils.h"

#घोषणा DW_PER_PAGE (PAGE_SIZE / माप(u32))

अटल अंतरभूत काष्ठा i915_address_space *ctx_vm(काष्ठा i915_gem_context *ctx)
अणु
	/* single thपढ़ोed, निजी ctx */
	वापस rcu_dereference_रक्षित(ctx->vm, true);
पूर्ण

अटल पूर्णांक live_nop_चयन(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक nctx = 1024;
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_gem_context **ctx;
	काष्ठा igt_live_test t;
	काष्ठा file *file;
	अचिन्हित दीर्घ n;
	पूर्णांक err = -ENODEV;

	/*
	 * Create as many contexts as we can feasibly get away with
	 * and check we can चयन between them rapidly.
	 *
	 * Serves as very simple stress test क्रम submission and HW चयनing
	 * between contexts.
	 */

	अगर (!DRIVER_CAPS(i915)->has_logical_contexts)
		वापस 0;

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ctx = kसुस्मृति(nctx, माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		err = -ENOMEM;
		जाओ out_file;
	पूर्ण

	क्रम (n = 0; n < nctx; n++) अणु
		ctx[n] = live_context(i915, file);
		अगर (IS_ERR(ctx[n])) अणु
			err = PTR_ERR(ctx[n]);
			जाओ out_file;
		पूर्ण
	पूर्ण

	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा i915_request *rq = शून्य;
		अचिन्हित दीर्घ end_समय, prime;
		kसमय_प्रकार बार[2] = अणुपूर्ण;

		बार[0] = kसमय_get_raw();
		क्रम (n = 0; n < nctx; n++) अणु
			काष्ठा i915_request *this;

			this = igt_request_alloc(ctx[n], engine);
			अगर (IS_ERR(this)) अणु
				err = PTR_ERR(this);
				जाओ out_file;
			पूर्ण
			अगर (rq) अणु
				i915_request_aरुको_dma_fence(this, &rq->fence);
				i915_request_put(rq);
			पूर्ण
			rq = i915_request_get(this);
			i915_request_add(this);
		पूर्ण
		अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
			pr_err("Failed to populated %d contexts\n", nctx);
			पूर्णांकel_gt_set_wedged(&i915->gt);
			i915_request_put(rq);
			err = -EIO;
			जाओ out_file;
		पूर्ण
		i915_request_put(rq);

		बार[1] = kसमय_get_raw();

		pr_info("Populated %d contexts on %s in %lluns\n",
			nctx, engine->name, kसमय_प्रकारo_ns(बार[1] - बार[0]));

		err = igt_live_test_begin(&t, i915, __func__, engine->name);
		अगर (err)
			जाओ out_file;

		end_समय = jअगरfies + i915_selftest.समयout_jअगरfies;
		क्रम_each_prime_number_from(prime, 2, 8192) अणु
			बार[1] = kसमय_get_raw();

			rq = शून्य;
			क्रम (n = 0; n < prime; n++) अणु
				काष्ठा i915_request *this;

				this = igt_request_alloc(ctx[n % nctx], engine);
				अगर (IS_ERR(this)) अणु
					err = PTR_ERR(this);
					जाओ out_file;
				पूर्ण

				अगर (rq) अणु /* Force submission order */
					i915_request_aरुको_dma_fence(this, &rq->fence);
					i915_request_put(rq);
				पूर्ण

				/*
				 * This space is left पूर्णांकentionally blank.
				 *
				 * We करो not actually want to perक्रमm any
				 * action with this request, we just want
				 * to measure the latency in allocation
				 * and submission of our bपढ़ोcrumbs -
				 * ensuring that the bare request is sufficient
				 * क्रम the प्रणाली to work (i.e. proper HEAD
				 * tracking of the rings, पूर्णांकerrupt handling,
				 * etc). It also gives us the lowest bounds
				 * क्रम latency.
				 */

				rq = i915_request_get(this);
				i915_request_add(this);
			पूर्ण
			GEM_BUG_ON(!rq);
			अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
				pr_err("Switching between %ld contexts timed out\n",
				       prime);
				पूर्णांकel_gt_set_wedged(&i915->gt);
				i915_request_put(rq);
				अवरोध;
			पूर्ण
			i915_request_put(rq);

			बार[1] = kसमय_sub(kसमय_get_raw(), बार[1]);
			अगर (prime == 2)
				बार[0] = बार[1];

			अगर (__igt_समयout(end_समय, शून्य))
				अवरोध;
		पूर्ण

		err = igt_live_test_end(&t);
		अगर (err)
			जाओ out_file;

		pr_info("Switch latencies on %s: 1 = %lluns, %lu = %lluns\n",
			engine->name,
			kसमय_प्रकारo_ns(बार[0]),
			prime - 1, भाग64_u64(kसमय_प्रकारo_ns(बार[1]), prime - 1));
	पूर्ण

out_file:
	fput(file);
	वापस err;
पूर्ण

काष्ठा parallel_चयन अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा पूर्णांकel_context *ce[2];
पूर्ण;

अटल पूर्णांक __live_parallel_चयन1(व्योम *data)
अणु
	काष्ठा parallel_चयन *arg = data;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;

	count = 0;
	करो अणु
		काष्ठा i915_request *rq = शून्य;
		पूर्णांक err, n;

		err = 0;
		क्रम (n = 0; !err && n < ARRAY_SIZE(arg->ce); n++) अणु
			काष्ठा i915_request *prev = rq;

			rq = i915_request_create(arg->ce[n]);
			अगर (IS_ERR(rq)) अणु
				i915_request_put(prev);
				वापस PTR_ERR(rq);
			पूर्ण

			i915_request_get(rq);
			अगर (prev) अणु
				err = i915_request_aरुको_dma_fence(rq, &prev->fence);
				i915_request_put(prev);
			पूर्ण

			i915_request_add(rq);
		पूर्ण
		अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
			err = -ETIME;
		i915_request_put(rq);
		अगर (err)
			वापस err;

		count++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));

	pr_info("%s: %lu switches (sync)\n", arg->ce[0]->engine->name, count);
	वापस 0;
पूर्ण

अटल पूर्णांक __live_parallel_चयनN(व्योम *data)
अणु
	काष्ठा parallel_चयन *arg = data;
	काष्ठा i915_request *rq = शून्य;
	IGT_TIMEOUT(end_समय);
	अचिन्हित दीर्घ count;
	पूर्णांक n;

	count = 0;
	करो अणु
		क्रम (n = 0; n < ARRAY_SIZE(arg->ce); n++) अणु
			काष्ठा i915_request *prev = rq;
			पूर्णांक err = 0;

			rq = i915_request_create(arg->ce[n]);
			अगर (IS_ERR(rq)) अणु
				i915_request_put(prev);
				वापस PTR_ERR(rq);
			पूर्ण

			i915_request_get(rq);
			अगर (prev) अणु
				err = i915_request_aरुको_dma_fence(rq, &prev->fence);
				i915_request_put(prev);
			पूर्ण

			i915_request_add(rq);
			अगर (err) अणु
				i915_request_put(rq);
				वापस err;
			पूर्ण
		पूर्ण

		count++;
	पूर्ण जबतक (!__igt_समयout(end_समय, शून्य));
	i915_request_put(rq);

	pr_info("%s: %lu switches (many)\n", arg->ce[0]->engine->name, count);
	वापस 0;
पूर्ण

अटल पूर्णांक live_parallel_चयन(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	अटल पूर्णांक (* स्थिर func[])(व्योम *arg) = अणु
		__live_parallel_चयन1,
		__live_parallel_चयनN,
		शून्य,
	पूर्ण;
	काष्ठा parallel_चयन *data = शून्य;
	काष्ठा i915_gem_engines *engines;
	काष्ठा i915_gem_engines_iter it;
	पूर्णांक (* स्थिर *fn)(व्योम *arg);
	काष्ठा i915_gem_context *ctx;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा file *file;
	पूर्णांक n, m, count;
	पूर्णांक err = 0;

	/*
	 * Check we can process चयनes on all engines simultaneously.
	 */

	अगर (!DRIVER_CAPS(i915)->has_logical_contexts)
		वापस 0;

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ctx = live_context(i915, file);
	अगर (IS_ERR(ctx)) अणु
		err = PTR_ERR(ctx);
		जाओ out_file;
	पूर्ण

	engines = i915_gem_context_lock_engines(ctx);
	count = engines->num_engines;

	data = kसुस्मृति(count, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		i915_gem_context_unlock_engines(ctx);
		err = -ENOMEM;
		जाओ out_file;
	पूर्ण

	m = 0; /* Use the first context as our ढाँचा क्रम the engines */
	क्रम_each_gem_engine(ce, engines, it) अणु
		err = पूर्णांकel_context_pin(ce);
		अगर (err) अणु
			i915_gem_context_unlock_engines(ctx);
			जाओ out;
		पूर्ण
		data[m++].ce[0] = पूर्णांकel_context_get(ce);
	पूर्ण
	i915_gem_context_unlock_engines(ctx);

	/* Clone the same set of engines पूर्णांकo the other contexts */
	क्रम (n = 1; n < ARRAY_SIZE(data->ce); n++) अणु
		ctx = live_context(i915, file);
		अगर (IS_ERR(ctx)) अणु
			err = PTR_ERR(ctx);
			जाओ out;
		पूर्ण

		क्रम (m = 0; m < count; m++) अणु
			अगर (!data[m].ce[0])
				जारी;

			ce = पूर्णांकel_context_create(data[m].ce[0]->engine);
			अगर (IS_ERR(ce))
				जाओ out;

			err = पूर्णांकel_context_pin(ce);
			अगर (err) अणु
				पूर्णांकel_context_put(ce);
				जाओ out;
			पूर्ण

			data[m].ce[n] = ce;
		पूर्ण
	पूर्ण

	क्रम (fn = func; !err && *fn; fn++) अणु
		काष्ठा igt_live_test t;
		पूर्णांक n;

		err = igt_live_test_begin(&t, i915, __func__, "");
		अगर (err)
			अवरोध;

		क्रम (n = 0; n < count; n++) अणु
			अगर (!data[n].ce[0])
				जारी;

			data[n].tsk = kthपढ़ो_run(*fn, &data[n],
						  "igt/parallel:%s",
						  data[n].ce[0]->engine->name);
			अगर (IS_ERR(data[n].tsk)) अणु
				err = PTR_ERR(data[n].tsk);
				अवरोध;
			पूर्ण
			get_task_काष्ठा(data[n].tsk);
		पूर्ण

		yield(); /* start all thपढ़ोs beक्रमe we kthपढ़ो_stop() */

		क्रम (n = 0; n < count; n++) अणु
			पूर्णांक status;

			अगर (IS_ERR_OR_शून्य(data[n].tsk))
				जारी;

			status = kthपढ़ो_stop(data[n].tsk);
			अगर (status && !err)
				err = status;

			put_task_काष्ठा(data[n].tsk);
			data[n].tsk = शून्य;
		पूर्ण

		अगर (igt_live_test_end(&t))
			err = -EIO;
	पूर्ण

out:
	क्रम (n = 0; n < count; n++) अणु
		क्रम (m = 0; m < ARRAY_SIZE(data->ce); m++) अणु
			अगर (!data[n].ce[m])
				जारी;

			पूर्णांकel_context_unpin(data[n].ce[m]);
			पूर्णांकel_context_put(data[n].ce[m]);
		पूर्ण
	पूर्ण
	kमुक्त(data);
out_file:
	fput(file);
	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ real_page_count(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस huge_gem_object_phys_size(obj) >> PAGE_SHIFT;
पूर्ण

अटल अचिन्हित दीर्घ fake_page_count(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस huge_gem_object_dma_size(obj) >> PAGE_SHIFT;
पूर्ण

अटल पूर्णांक gpu_fill(काष्ठा पूर्णांकel_context *ce,
		    काष्ठा drm_i915_gem_object *obj,
		    अचिन्हित पूर्णांक dw)
अणु
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	GEM_BUG_ON(obj->base.size > ce->vm->total);
	GEM_BUG_ON(!पूर्णांकel_engine_can_store_dword(ce->engine));

	vma = i915_vma_instance(obj, ce->vm, शून्य);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	err = i915_vma_pin(vma, 0, 0, PIN_HIGH | PIN_USER);
	अगर (err)
		वापस err;

	/*
	 * Within the GTT the huge objects maps every page onto
	 * its 1024 real pages (using phys_pfn = dma_pfn % 1024).
	 * We set the nth dword within the page using the nth
	 * mapping via the GTT - this should exercise the GTT mapping
	 * whilst checking that each context provides a unique view
	 * पूर्णांकo the object.
	 */
	err = igt_gpu_fill_dw(ce, vma,
			      (dw * real_page_count(obj)) << PAGE_SHIFT |
			      (dw * माप(u32)),
			      real_page_count(obj),
			      dw);
	i915_vma_unpin(vma);

	वापस err;
पूर्ण

अटल पूर्णांक cpu_fill(काष्ठा drm_i915_gem_object *obj, u32 value)
अणु
	स्थिर bool has_llc = HAS_LLC(to_i915(obj->base.dev));
	अचिन्हित पूर्णांक n, m, need_flush;
	पूर्णांक err;

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_prepare_ग_लिखो(obj, &need_flush);
	अगर (err)
		जाओ out;

	क्रम (n = 0; n < real_page_count(obj); n++) अणु
		u32 *map;

		map = kmap_atomic(i915_gem_object_get_page(obj, n));
		क्रम (m = 0; m < DW_PER_PAGE; m++)
			map[m] = value;
		अगर (!has_llc)
			drm_clflush_virt_range(map, PAGE_SIZE);
		kunmap_atomic(map);
	पूर्ण

	i915_gem_object_finish_access(obj);
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_GTT | I915_GEM_DOMAIN_CPU;
	obj->ग_लिखो_करोमुख्य = 0;
out:
	i915_gem_object_unlock(obj);
	वापस err;
पूर्ण

अटल noअंतरभूत पूर्णांक cpu_check(काष्ठा drm_i915_gem_object *obj,
			      अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक n, m, needs_flush;
	पूर्णांक err;

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_prepare_पढ़ो(obj, &needs_flush);
	अगर (err)
		जाओ out_unlock;

	क्रम (n = 0; n < real_page_count(obj); n++) अणु
		u32 *map;

		map = kmap_atomic(i915_gem_object_get_page(obj, n));
		अगर (needs_flush & CLFLUSH_BEFORE)
			drm_clflush_virt_range(map, PAGE_SIZE);

		क्रम (m = 0; m < max; m++) अणु
			अगर (map[m] != m) अणु
				pr_err("%pS: Invalid value at object %d page %d/%ld, offset %d/%d: found %x expected %x\n",
				       __builtin_वापस_address(0), idx,
				       n, real_page_count(obj), m, max,
				       map[m], m);
				err = -EINVAL;
				जाओ out_unmap;
			पूर्ण
		पूर्ण

		क्रम (; m < DW_PER_PAGE; m++) अणु
			अगर (map[m] != STACK_MAGIC) अणु
				pr_err("%pS: Invalid value at object %d page %d, offset %d: found %x expected %x (uninitialised)\n",
				       __builtin_वापस_address(0), idx, n, m,
				       map[m], STACK_MAGIC);
				err = -EINVAL;
				जाओ out_unmap;
			पूर्ण
		पूर्ण

out_unmap:
		kunmap_atomic(map);
		अगर (err)
			अवरोध;
	पूर्ण

	i915_gem_object_finish_access(obj);
out_unlock:
	i915_gem_object_unlock(obj);
	वापस err;
पूर्ण

अटल पूर्णांक file_add_object(काष्ठा file *file, काष्ठा drm_i915_gem_object *obj)
अणु
	पूर्णांक err;

	GEM_BUG_ON(obj->base.handle_count);

	/* tie the object to the drm_file क्रम easy reaping */
	err = idr_alloc(&to_drm_file(file)->object_idr,
			&obj->base, 1, 0, GFP_KERNEL);
	अगर (err < 0)
		वापस err;

	i915_gem_object_get(obj);
	obj->base.handle_count++;
	वापस 0;
पूर्ण

अटल काष्ठा drm_i915_gem_object *
create_test_object(काष्ठा i915_address_space *vm,
		   काष्ठा file *file,
		   काष्ठा list_head *objects)
अणु
	काष्ठा drm_i915_gem_object *obj;
	u64 size;
	पूर्णांक err;

	/* Keep in GEM's good graces */
	पूर्णांकel_gt_retire_requests(vm->gt);

	size = min(vm->total / 2, 1024ull * DW_PER_PAGE * PAGE_SIZE);
	size = round_करोwn(size, DW_PER_PAGE * PAGE_SIZE);

	obj = huge_gem_object(vm->i915, DW_PER_PAGE * PAGE_SIZE, size);
	अगर (IS_ERR(obj))
		वापस obj;

	err = file_add_object(file, obj);
	i915_gem_object_put(obj);
	अगर (err)
		वापस ERR_PTR(err);

	err = cpu_fill(obj, STACK_MAGIC);
	अगर (err) अणु
		pr_err("Failed to fill object with cpu, err=%d\n",
		       err);
		वापस ERR_PTR(err);
	पूर्ण

	list_add_tail(&obj->st_link, objects);
	वापस obj;
पूर्ण

अटल अचिन्हित दीर्घ max_dwords(काष्ठा drm_i915_gem_object *obj)
अणु
	अचिन्हित दीर्घ npages = fake_page_count(obj);

	GEM_BUG_ON(!IS_ALIGNED(npages, DW_PER_PAGE));
	वापस npages / DW_PER_PAGE;
पूर्ण

अटल व्योम throttle_release(काष्ठा i915_request **q, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (IS_ERR_OR_शून्य(q[i]))
			जारी;

		i915_request_put(fetch_and_zero(&q[i]));
	पूर्ण
पूर्ण

अटल पूर्णांक throttle(काष्ठा पूर्णांकel_context *ce,
		    काष्ठा i915_request **q, पूर्णांक count)
अणु
	पूर्णांक i;

	अगर (!IS_ERR_OR_शून्य(q[0])) अणु
		अगर (i915_request_रुको(q[0],
				      I915_WAIT_INTERRUPTIBLE,
				      MAX_SCHEDULE_TIMEOUT) < 0)
			वापस -EINTR;

		i915_request_put(q[0]);
	पूर्ण

	क्रम (i = 0; i < count - 1; i++)
		q[i] = q[i + 1];

	q[i] = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(q[i]))
		वापस PTR_ERR(q[i]);

	i915_request_get(q[i]);
	i915_request_add(q[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक igt_ctx_exec(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांक err = -ENODEV;

	/*
	 * Create a few dअगरferent contexts (with dअगरferent mm) and ग_लिखो
	 * through each ctx/mm using the GPU making sure those ग_लिखोs end
	 * up in the expected pages of our obj.
	 */

	अगर (!DRIVER_CAPS(i915)->has_logical_contexts)
		वापस 0;

	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा drm_i915_gem_object *obj = शून्य;
		अचिन्हित दीर्घ ncontexts, ndwords, dw;
		काष्ठा i915_request *tq[5] = अणुपूर्ण;
		काष्ठा igt_live_test t;
		IGT_TIMEOUT(end_समय);
		LIST_HEAD(objects);
		काष्ठा file *file;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		अगर (!engine->context_size)
			जारी; /* No logical context support in HW */

		file = mock_file(i915);
		अगर (IS_ERR(file))
			वापस PTR_ERR(file);

		err = igt_live_test_begin(&t, i915, __func__, engine->name);
		अगर (err)
			जाओ out_file;

		ncontexts = 0;
		ndwords = 0;
		dw = 0;
		जबतक (!समय_after(jअगरfies, end_समय)) अणु
			काष्ठा i915_gem_context *ctx;
			काष्ठा पूर्णांकel_context *ce;

			ctx = kernel_context(i915);
			अगर (IS_ERR(ctx)) अणु
				err = PTR_ERR(ctx);
				जाओ out_file;
			पूर्ण

			ce = i915_gem_context_get_engine(ctx, engine->legacy_idx);
			GEM_BUG_ON(IS_ERR(ce));

			अगर (!obj) अणु
				obj = create_test_object(ce->vm, file, &objects);
				अगर (IS_ERR(obj)) अणु
					err = PTR_ERR(obj);
					पूर्णांकel_context_put(ce);
					kernel_context_बंद(ctx);
					जाओ out_file;
				पूर्ण
			पूर्ण

			err = gpu_fill(ce, obj, dw);
			अगर (err) अणु
				pr_err("Failed to fill dword %lu [%lu/%lu] with gpu (%s) [full-ppgtt? %s], err=%d\n",
				       ndwords, dw, max_dwords(obj),
				       engine->name,
				       yesno(!!rcu_access_poपूर्णांकer(ctx->vm)),
				       err);
				पूर्णांकel_context_put(ce);
				kernel_context_बंद(ctx);
				जाओ out_file;
			पूर्ण

			err = throttle(ce, tq, ARRAY_SIZE(tq));
			अगर (err) अणु
				पूर्णांकel_context_put(ce);
				kernel_context_बंद(ctx);
				जाओ out_file;
			पूर्ण

			अगर (++dw == max_dwords(obj)) अणु
				obj = शून्य;
				dw = 0;
			पूर्ण

			ndwords++;
			ncontexts++;

			पूर्णांकel_context_put(ce);
			kernel_context_बंद(ctx);
		पूर्ण

		pr_info("Submitted %lu contexts to %s, filling %lu dwords\n",
			ncontexts, engine->name, ndwords);

		ncontexts = dw = 0;
		list_क्रम_each_entry(obj, &objects, st_link) अणु
			अचिन्हित पूर्णांक rem =
				min_t(अचिन्हित पूर्णांक, ndwords - dw, max_dwords(obj));

			err = cpu_check(obj, ncontexts++, rem);
			अगर (err)
				अवरोध;

			dw += rem;
		पूर्ण

out_file:
		throttle_release(tq, ARRAY_SIZE(tq));
		अगर (igt_live_test_end(&t))
			err = -EIO;

		fput(file);
		अगर (err)
			वापस err;

		i915_gem_drain_मुक्तd_objects(i915);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_shared_ctx_exec(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_request *tq[5] = अणुपूर्ण;
	काष्ठा i915_gem_context *parent;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा igt_live_test t;
	काष्ठा file *file;
	पूर्णांक err = 0;

	/*
	 * Create a few dअगरferent contexts with the same mm and ग_लिखो
	 * through each ctx using the GPU making sure those ग_लिखोs end
	 * up in the expected pages of our obj.
	 */
	अगर (!DRIVER_CAPS(i915)->has_logical_contexts)
		वापस 0;

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	parent = live_context(i915, file);
	अगर (IS_ERR(parent)) अणु
		err = PTR_ERR(parent);
		जाओ out_file;
	पूर्ण

	अगर (!parent->vm) अणु /* not full-ppgtt; nothing to share */
		err = 0;
		जाओ out_file;
	पूर्ण

	err = igt_live_test_begin(&t, i915, __func__, "");
	अगर (err)
		जाओ out_file;

	क्रम_each_uabi_engine(engine, i915) अणु
		अचिन्हित दीर्घ ncontexts, ndwords, dw;
		काष्ठा drm_i915_gem_object *obj = शून्य;
		IGT_TIMEOUT(end_समय);
		LIST_HEAD(objects);

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		dw = 0;
		ndwords = 0;
		ncontexts = 0;
		जबतक (!समय_after(jअगरfies, end_समय)) अणु
			काष्ठा i915_gem_context *ctx;
			काष्ठा पूर्णांकel_context *ce;

			ctx = kernel_context(i915);
			अगर (IS_ERR(ctx)) अणु
				err = PTR_ERR(ctx);
				जाओ out_test;
			पूर्ण

			mutex_lock(&ctx->mutex);
			__assign_ppgtt(ctx, ctx_vm(parent));
			mutex_unlock(&ctx->mutex);

			ce = i915_gem_context_get_engine(ctx, engine->legacy_idx);
			GEM_BUG_ON(IS_ERR(ce));

			अगर (!obj) अणु
				obj = create_test_object(ctx_vm(parent),
							 file, &objects);
				अगर (IS_ERR(obj)) अणु
					err = PTR_ERR(obj);
					पूर्णांकel_context_put(ce);
					kernel_context_बंद(ctx);
					जाओ out_test;
				पूर्ण
			पूर्ण

			err = gpu_fill(ce, obj, dw);
			अगर (err) अणु
				pr_err("Failed to fill dword %lu [%lu/%lu] with gpu (%s) [full-ppgtt? %s], err=%d\n",
				       ndwords, dw, max_dwords(obj),
				       engine->name,
				       yesno(!!rcu_access_poपूर्णांकer(ctx->vm)),
				       err);
				पूर्णांकel_context_put(ce);
				kernel_context_बंद(ctx);
				जाओ out_test;
			पूर्ण

			err = throttle(ce, tq, ARRAY_SIZE(tq));
			अगर (err) अणु
				पूर्णांकel_context_put(ce);
				kernel_context_बंद(ctx);
				जाओ out_test;
			पूर्ण

			अगर (++dw == max_dwords(obj)) अणु
				obj = शून्य;
				dw = 0;
			पूर्ण

			ndwords++;
			ncontexts++;

			पूर्णांकel_context_put(ce);
			kernel_context_बंद(ctx);
		पूर्ण
		pr_info("Submitted %lu contexts to %s, filling %lu dwords\n",
			ncontexts, engine->name, ndwords);

		ncontexts = dw = 0;
		list_क्रम_each_entry(obj, &objects, st_link) अणु
			अचिन्हित पूर्णांक rem =
				min_t(अचिन्हित पूर्णांक, ndwords - dw, max_dwords(obj));

			err = cpu_check(obj, ncontexts++, rem);
			अगर (err)
				जाओ out_test;

			dw += rem;
		पूर्ण

		i915_gem_drain_मुक्तd_objects(i915);
	पूर्ण
out_test:
	throttle_release(tq, ARRAY_SIZE(tq));
	अगर (igt_live_test_end(&t))
		err = -EIO;
out_file:
	fput(file);
	वापस err;
पूर्ण

अटल पूर्णांक rpcs_query_batch(काष्ठा drm_i915_gem_object *rpcs, काष्ठा i915_vma *vma)
अणु
	u32 *cmd;

	GEM_BUG_ON(INTEL_GEN(vma->vm->i915) < 8);

	cmd = i915_gem_object_pin_map(rpcs, I915_MAP_WB);
	अगर (IS_ERR(cmd))
		वापस PTR_ERR(cmd);

	*cmd++ = MI_STORE_REGISTER_MEM_GEN8;
	*cmd++ = i915_mmio_reg_offset(GEN8_R_PWR_CLK_STATE);
	*cmd++ = lower_32_bits(vma->node.start);
	*cmd++ = upper_32_bits(vma->node.start);
	*cmd = MI_BATCH_BUFFER_END;

	__i915_gem_object_flush_map(rpcs, 0, 64);
	i915_gem_object_unpin_map(rpcs);

	पूर्णांकel_gt_chipset_flush(vma->vm->gt);

	वापस 0;
पूर्ण

अटल पूर्णांक
emit_rpcs_query(काष्ठा drm_i915_gem_object *obj,
		काष्ठा पूर्णांकel_context *ce,
		काष्ठा i915_request **rq_out)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_request *rq;
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा i915_vma *batch;
	काष्ठा i915_vma *vma;
	काष्ठा drm_i915_gem_object *rpcs;
	पूर्णांक err;

	GEM_BUG_ON(!पूर्णांकel_engine_can_store_dword(ce->engine));

	अगर (INTEL_GEN(i915) < 8)
		वापस -EINVAL;

	vma = i915_vma_instance(obj, ce->vm, शून्य);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	rpcs = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(rpcs))
		वापस PTR_ERR(rpcs);

	batch = i915_vma_instance(rpcs, ce->vm, शून्य);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ err_put;
	पूर्ण

	i915_gem_ww_ctx_init(&ww, false);
retry:
	err = i915_gem_object_lock(obj, &ww);
	अगर (!err)
		err = i915_gem_object_lock(rpcs, &ww);
	अगर (!err)
		err = i915_gem_object_set_to_gtt_करोमुख्य(obj, false);
	अगर (!err)
		err = i915_vma_pin_ww(vma, &ww, 0, 0, PIN_USER);
	अगर (err)
		जाओ err_put;

	err = i915_vma_pin_ww(batch, &ww, 0, 0, PIN_USER);
	अगर (err)
		जाओ err_vma;

	err = rpcs_query_batch(rpcs, vma);
	अगर (err)
		जाओ err_batch;

	rq = i915_request_create(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_batch;
	पूर्ण

	err = i915_request_aरुको_object(rq, batch->obj, false);
	अगर (err == 0)
		err = i915_vma_move_to_active(batch, rq, 0);
	अगर (err)
		जाओ skip_request;

	err = i915_request_aरुको_object(rq, vma->obj, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	अगर (err)
		जाओ skip_request;

	अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
		अगर (err)
			जाओ skip_request;
	पूर्ण

	err = rq->engine->emit_bb_start(rq,
					batch->node.start, batch->node.size,
					0);
	अगर (err)
		जाओ skip_request;

	*rq_out = i915_request_get(rq);

skip_request:
	अगर (err)
		i915_request_set_error_once(rq, err);
	i915_request_add(rq);
err_batch:
	i915_vma_unpin(batch);
err_vma:
	i915_vma_unpin(vma);
err_put:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	i915_gem_object_put(rpcs);
	वापस err;
पूर्ण

#घोषणा TEST_IDLE	BIT(0)
#घोषणा TEST_BUSY	BIT(1)
#घोषणा TEST_RESET	BIT(2)

अटल पूर्णांक
__sseu_prepare(स्थिर अक्षर *name,
	       अचिन्हित पूर्णांक flags,
	       काष्ठा पूर्णांकel_context *ce,
	       काष्ठा igt_spinner **spin)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक ret;

	*spin = शून्य;
	अगर (!(flags & (TEST_BUSY | TEST_RESET)))
		वापस 0;

	*spin = kzalloc(माप(**spin), GFP_KERNEL);
	अगर (!*spin)
		वापस -ENOMEM;

	ret = igt_spinner_init(*spin, ce->engine->gt);
	अगर (ret)
		जाओ err_मुक्त;

	rq = igt_spinner_create_request(*spin, ce, MI_NOOP);
	अगर (IS_ERR(rq)) अणु
		ret = PTR_ERR(rq);
		जाओ err_fini;
	पूर्ण

	i915_request_add(rq);

	अगर (!igt_रुको_क्रम_spinner(*spin, rq)) अणु
		pr_err("%s: Spinner failed to start!\n", name);
		ret = -ETIMEDOUT;
		जाओ err_end;
	पूर्ण

	वापस 0;

err_end:
	igt_spinner_end(*spin);
err_fini:
	igt_spinner_fini(*spin);
err_मुक्त:
	kमुक्त(fetch_and_zero(spin));
	वापस ret;
पूर्ण

अटल पूर्णांक
__पढ़ो_slice_count(काष्ठा पूर्णांकel_context *ce,
		   काष्ठा drm_i915_gem_object *obj,
		   काष्ठा igt_spinner *spin,
		   u32 *rpcs)
अणु
	काष्ठा i915_request *rq = शून्य;
	u32 s_mask, s_shअगरt;
	अचिन्हित पूर्णांक cnt;
	u32 *buf, val;
	दीर्घ ret;

	ret = emit_rpcs_query(obj, ce, &rq);
	अगर (ret)
		वापस ret;

	अगर (spin)
		igt_spinner_end(spin);

	ret = i915_request_रुको(rq, 0, MAX_SCHEDULE_TIMEOUT);
	i915_request_put(rq);
	अगर (ret < 0)
		वापस ret;

	buf = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(buf)) अणु
		ret = PTR_ERR(buf);
		वापस ret;
	पूर्ण

	अगर (INTEL_GEN(ce->engine->i915) >= 11) अणु
		s_mask = GEN11_RPCS_S_CNT_MASK;
		s_shअगरt = GEN11_RPCS_S_CNT_SHIFT;
	पूर्ण अन्यथा अणु
		s_mask = GEN8_RPCS_S_CNT_MASK;
		s_shअगरt = GEN8_RPCS_S_CNT_SHIFT;
	पूर्ण

	val = *buf;
	cnt = (val & s_mask) >> s_shअगरt;
	*rpcs = val;

	i915_gem_object_unpin_map(obj);

	वापस cnt;
पूर्ण

अटल पूर्णांक
__check_rpcs(स्थिर अक्षर *name, u32 rpcs, पूर्णांक slices, अचिन्हित पूर्णांक expected,
	     स्थिर अक्षर *prefix, स्थिर अक्षर *suffix)
अणु
	अगर (slices == expected)
		वापस 0;

	अगर (slices < 0) अणु
		pr_err("%s: %s read slice count failed with %d%s\n",
		       name, prefix, slices, suffix);
		वापस slices;
	पूर्ण

	pr_err("%s: %s slice count %d is not %u%s\n",
	       name, prefix, slices, expected, suffix);

	pr_info("RPCS=0x%x; %u%sx%u%s\n",
		rpcs, slices,
		(rpcs & GEN8_RPCS_S_CNT_ENABLE) ? "*" : "",
		(rpcs & GEN8_RPCS_SS_CNT_MASK) >> GEN8_RPCS_SS_CNT_SHIFT,
		(rpcs & GEN8_RPCS_SS_CNT_ENABLE) ? "*" : "");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
__sseu_finish(स्थिर अक्षर *name,
	      अचिन्हित पूर्णांक flags,
	      काष्ठा पूर्णांकel_context *ce,
	      काष्ठा drm_i915_gem_object *obj,
	      अचिन्हित पूर्णांक expected,
	      काष्ठा igt_spinner *spin)
अणु
	अचिन्हित पूर्णांक slices = hweight32(ce->engine->sseu.slice_mask);
	u32 rpcs = 0;
	पूर्णांक ret = 0;

	अगर (flags & TEST_RESET) अणु
		ret = पूर्णांकel_engine_reset(ce->engine, "sseu");
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = __पढ़ो_slice_count(ce, obj,
				 flags & TEST_RESET ? शून्य : spin, &rpcs);
	ret = __check_rpcs(name, rpcs, ret, expected, "Context", "!");
	अगर (ret)
		जाओ out;

	ret = __पढ़ो_slice_count(ce->engine->kernel_context, obj, शून्य, &rpcs);
	ret = __check_rpcs(name, rpcs, ret, slices, "Kernel context", "!");

out:
	अगर (spin)
		igt_spinner_end(spin);

	अगर ((flags & TEST_IDLE) && ret == 0) अणु
		ret = igt_flush_test(ce->engine->i915);
		अगर (ret)
			वापस ret;

		ret = __पढ़ो_slice_count(ce, obj, शून्य, &rpcs);
		ret = __check_rpcs(name, rpcs, ret, expected,
				   "Context", " after idle!");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
__sseu_test(स्थिर अक्षर *name,
	    अचिन्हित पूर्णांक flags,
	    काष्ठा पूर्णांकel_context *ce,
	    काष्ठा drm_i915_gem_object *obj,
	    काष्ठा पूर्णांकel_sseu sseu)
अणु
	काष्ठा igt_spinner *spin = शून्य;
	पूर्णांक ret;

	पूर्णांकel_engine_pm_get(ce->engine);

	ret = __sseu_prepare(name, flags, ce, &spin);
	अगर (ret)
		जाओ out_pm;

	ret = पूर्णांकel_context_reconfigure_sseu(ce, sseu);
	अगर (ret)
		जाओ out_spin;

	ret = __sseu_finish(name, flags, ce, obj,
			    hweight32(sseu.slice_mask), spin);

out_spin:
	अगर (spin) अणु
		igt_spinner_end(spin);
		igt_spinner_fini(spin);
		kमुक्त(spin);
	पूर्ण
out_pm:
	पूर्णांकel_engine_pm_put(ce->engine);
	वापस ret;
पूर्ण

अटल पूर्णांक
__igt_ctx_sseu(काष्ठा drm_i915_निजी *i915,
	       स्थिर अक्षर *name,
	       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक inst = 0;
	पूर्णांक ret = 0;

	अगर (INTEL_GEN(i915) < 9)
		वापस 0;

	अगर (flags & TEST_RESET)
		igt_global_reset_lock(&i915->gt);

	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		ret = PTR_ERR(obj);
		जाओ out_unlock;
	पूर्ण

	करो अणु
		काष्ठा पूर्णांकel_engine_cs *engine;
		काष्ठा पूर्णांकel_context *ce;
		काष्ठा पूर्णांकel_sseu pg_sseu;

		engine = पूर्णांकel_engine_lookup_user(i915,
						  I915_ENGINE_CLASS_RENDER,
						  inst++);
		अगर (!engine)
			अवरोध;

		अगर (hweight32(engine->sseu.slice_mask) < 2)
			जारी;

		अगर (!engine->gt->info.sseu.has_slice_pg)
			जारी;

		/*
		 * Gen11 VME मित्रly घातer-gated configuration with
		 * half enabled sub-slices.
		 */
		pg_sseu = engine->sseu;
		pg_sseu.slice_mask = 1;
		pg_sseu.subslice_mask =
			~(~0 << (hweight32(engine->sseu.subslice_mask) / 2));

		pr_info("%s: SSEU subtest '%s', flags=%x, def_slices=%u, pg_slices=%u\n",
			engine->name, name, flags,
			hweight32(engine->sseu.slice_mask),
			hweight32(pg_sseu.slice_mask));

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			ret = PTR_ERR(ce);
			जाओ out_put;
		पूर्ण

		ret = पूर्णांकel_context_pin(ce);
		अगर (ret)
			जाओ out_ce;

		/* First set the शेष mask. */
		ret = __sseu_test(name, flags, ce, obj, engine->sseu);
		अगर (ret)
			जाओ out_unpin;

		/* Then set a घातer-gated configuration. */
		ret = __sseu_test(name, flags, ce, obj, pg_sseu);
		अगर (ret)
			जाओ out_unpin;

		/* Back to शेषs. */
		ret = __sseu_test(name, flags, ce, obj, engine->sseu);
		अगर (ret)
			जाओ out_unpin;

		/* One last घातer-gated configuration क्रम the road. */
		ret = __sseu_test(name, flags, ce, obj, pg_sseu);
		अगर (ret)
			जाओ out_unpin;

out_unpin:
		पूर्णांकel_context_unpin(ce);
out_ce:
		पूर्णांकel_context_put(ce);
	पूर्ण जबतक (!ret);

	अगर (igt_flush_test(i915))
		ret = -EIO;

out_put:
	i915_gem_object_put(obj);

out_unlock:
	अगर (flags & TEST_RESET)
		igt_global_reset_unlock(&i915->gt);

	अगर (ret)
		pr_err("%s: Failed with %d!\n", name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक igt_ctx_sseu(व्योम *arg)
अणु
	काष्ठा अणु
		स्थिर अक्षर *name;
		अचिन्हित पूर्णांक flags;
	पूर्ण *phase, phases[] = अणु
		अणु .name = "basic", .flags = 0 पूर्ण,
		अणु .name = "idle", .flags = TEST_IDLE पूर्ण,
		अणु .name = "busy", .flags = TEST_BUSY पूर्ण,
		अणु .name = "busy-reset", .flags = TEST_BUSY | TEST_RESET पूर्ण,
		अणु .name = "busy-idle", .flags = TEST_BUSY | TEST_IDLE पूर्ण,
		अणु .name = "reset-idle", .flags = TEST_RESET | TEST_IDLE पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0, phase = phases; ret == 0 && i < ARRAY_SIZE(phases);
	     i++, phase++)
		ret = __igt_ctx_sseu(arg, phase->name, phase->flags);

	वापस ret;
पूर्ण

अटल पूर्णांक igt_ctx_पढ़ोonly(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	अचिन्हित दीर्घ idx, ndwords, dw, num_engines;
	काष्ठा drm_i915_gem_object *obj = शून्य;
	काष्ठा i915_request *tq[5] = अणुपूर्ण;
	काष्ठा i915_gem_engines_iter it;
	काष्ठा i915_address_space *vm;
	काष्ठा i915_gem_context *ctx;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा igt_live_test t;
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end_समय);
	LIST_HEAD(objects);
	काष्ठा file *file;
	पूर्णांक err = -ENODEV;

	/*
	 * Create a few पढ़ो-only objects (with the occasional writable object)
	 * and try to ग_लिखो पूर्णांकo these object checking that the GPU discards
	 * any ग_लिखो to a पढ़ो-only object.
	 */

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	err = igt_live_test_begin(&t, i915, __func__, "");
	अगर (err)
		जाओ out_file;

	ctx = live_context(i915, file);
	अगर (IS_ERR(ctx)) अणु
		err = PTR_ERR(ctx);
		जाओ out_file;
	पूर्ण

	vm = ctx_vm(ctx) ?: &i915->ggtt.alias->vm;
	अगर (!vm || !vm->has_पढ़ो_only) अणु
		err = 0;
		जाओ out_file;
	पूर्ण

	num_engines = 0;
	क्रम_each_gem_engine(ce, i915_gem_context_lock_engines(ctx), it)
		अगर (पूर्णांकel_engine_can_store_dword(ce->engine))
			num_engines++;
	i915_gem_context_unlock_engines(ctx);

	ndwords = 0;
	dw = 0;
	जबतक (!समय_after(jअगरfies, end_समय)) अणु
		क्रम_each_gem_engine(ce,
				    i915_gem_context_lock_engines(ctx), it) अणु
			अगर (!पूर्णांकel_engine_can_store_dword(ce->engine))
				जारी;

			अगर (!obj) अणु
				obj = create_test_object(ce->vm, file, &objects);
				अगर (IS_ERR(obj)) अणु
					err = PTR_ERR(obj);
					i915_gem_context_unlock_engines(ctx);
					जाओ out_file;
				पूर्ण

				अगर (pअक्रमom_u32_state(&prng) & 1)
					i915_gem_object_set_पढ़ोonly(obj);
			पूर्ण

			err = gpu_fill(ce, obj, dw);
			अगर (err) अणु
				pr_err("Failed to fill dword %lu [%lu/%lu] with gpu (%s) [full-ppgtt? %s], err=%d\n",
				       ndwords, dw, max_dwords(obj),
				       ce->engine->name,
				       yesno(!!ctx_vm(ctx)),
				       err);
				i915_gem_context_unlock_engines(ctx);
				जाओ out_file;
			पूर्ण

			err = throttle(ce, tq, ARRAY_SIZE(tq));
			अगर (err) अणु
				i915_gem_context_unlock_engines(ctx);
				जाओ out_file;
			पूर्ण

			अगर (++dw == max_dwords(obj)) अणु
				obj = शून्य;
				dw = 0;
			पूर्ण
			ndwords++;
		पूर्ण
		i915_gem_context_unlock_engines(ctx);
	पूर्ण
	pr_info("Submitted %lu dwords (across %lu engines)\n",
		ndwords, num_engines);

	dw = 0;
	idx = 0;
	list_क्रम_each_entry(obj, &objects, st_link) अणु
		अचिन्हित पूर्णांक rem =
			min_t(अचिन्हित पूर्णांक, ndwords - dw, max_dwords(obj));
		अचिन्हित पूर्णांक num_ग_लिखोs;

		num_ग_लिखोs = rem;
		अगर (i915_gem_object_is_पढ़ोonly(obj))
			num_ग_लिखोs = 0;

		err = cpu_check(obj, idx++, num_ग_लिखोs);
		अगर (err)
			अवरोध;

		dw += rem;
	पूर्ण

out_file:
	throttle_release(tq, ARRAY_SIZE(tq));
	अगर (igt_live_test_end(&t))
		err = -EIO;

	fput(file);
	वापस err;
पूर्ण

अटल पूर्णांक check_scratch(काष्ठा i915_address_space *vm, u64 offset)
अणु
	काष्ठा drm_mm_node *node;

	mutex_lock(&vm->mutex);
	node = __drm_mm_पूर्णांकerval_first(&vm->mm,
				       offset, offset + माप(u32) - 1);
	mutex_unlock(&vm->mutex);
	अगर (!node || node->start > offset)
		वापस 0;

	GEM_BUG_ON(offset >= node->start + node->size);

	pr_err("Target offset 0x%08x_%08x overlaps with a node in the mm!\n",
	       upper_32_bits(offset), lower_32_bits(offset));
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ग_लिखो_to_scratch(काष्ठा i915_gem_context *ctx,
			    काष्ठा पूर्णांकel_engine_cs *engine,
			    u64 offset, u32 value)
अणु
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_address_space *vm;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma;
	u32 *cmd;
	पूर्णांक err;

	GEM_BUG_ON(offset < I915_GTT_PAGE_SIZE);

	err = check_scratch(ctx_vm(ctx), offset);
	अगर (err)
		वापस err;

	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	cmd = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ out;
	पूर्ण

	*cmd++ = MI_STORE_DWORD_IMM_GEN4;
	अगर (INTEL_GEN(i915) >= 8) अणु
		*cmd++ = lower_32_bits(offset);
		*cmd++ = upper_32_bits(offset);
	पूर्ण अन्यथा अणु
		*cmd++ = 0;
		*cmd++ = offset;
	पूर्ण
	*cmd++ = value;
	*cmd = MI_BATCH_BUFFER_END;
	__i915_gem_object_flush_map(obj, 0, 64);
	i915_gem_object_unpin_map(obj);

	पूर्णांकel_gt_chipset_flush(engine->gt);

	vm = i915_gem_context_get_vm_rcu(ctx);
	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ out_vm;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER | PIN_OFFSET_FIXED);
	अगर (err)
		जाओ out_vm;

	rq = igt_request_alloc(ctx, engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_unpin;
	पूर्ण

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, false);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, 0);
	i915_vma_unlock(vma);
	अगर (err)
		जाओ skip_request;

	अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
		अगर (err)
			जाओ skip_request;
	पूर्ण

	err = engine->emit_bb_start(rq, vma->node.start, vma->node.size, 0);
	अगर (err)
		जाओ skip_request;

	i915_vma_unpin(vma);

	i915_request_add(rq);

	जाओ out_vm;
skip_request:
	i915_request_set_error_once(rq, err);
	i915_request_add(rq);
err_unpin:
	i915_vma_unpin(vma);
out_vm:
	i915_vm_put(vm);
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_from_scratch(काष्ठा i915_gem_context *ctx,
			     काष्ठा पूर्णांकel_engine_cs *engine,
			     u64 offset, u32 *value)
अणु
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_address_space *vm;
	स्थिर u32 result = 0x100;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma;
	अचिन्हित पूर्णांक flags;
	u32 *cmd;
	पूर्णांक err;

	GEM_BUG_ON(offset < I915_GTT_PAGE_SIZE);

	err = check_scratch(ctx_vm(ctx), offset);
	अगर (err)
		वापस err;

	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	अगर (INTEL_GEN(i915) >= 8) अणु
		स्थिर u32 GPR0 = engine->mmio_base + 0x600;

		vm = i915_gem_context_get_vm_rcu(ctx);
		vma = i915_vma_instance(obj, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out_vm;
		पूर्ण

		err = i915_vma_pin(vma, 0, 0, PIN_USER | PIN_OFFSET_FIXED);
		अगर (err)
			जाओ out_vm;

		cmd = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
		अगर (IS_ERR(cmd)) अणु
			err = PTR_ERR(cmd);
			जाओ out;
		पूर्ण

		स_रखो(cmd, POISON_INUSE, PAGE_SIZE);
		*cmd++ = MI_LOAD_REGISTER_MEM_GEN8;
		*cmd++ = GPR0;
		*cmd++ = lower_32_bits(offset);
		*cmd++ = upper_32_bits(offset);
		*cmd++ = MI_STORE_REGISTER_MEM_GEN8;
		*cmd++ = GPR0;
		*cmd++ = result;
		*cmd++ = 0;
		*cmd = MI_BATCH_BUFFER_END;

		i915_gem_object_flush_map(obj);
		i915_gem_object_unpin_map(obj);

		flags = 0;
	पूर्ण अन्यथा अणु
		स्थिर u32 reg = engine->mmio_base + 0x420;

		/* hsw: रेजिस्टर access even to 3DPRIM! is रक्षित */
		vm = i915_vm_get(&engine->gt->ggtt->vm);
		vma = i915_vma_instance(obj, vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out_vm;
		पूर्ण

		err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
		अगर (err)
			जाओ out_vm;

		cmd = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
		अगर (IS_ERR(cmd)) अणु
			err = PTR_ERR(cmd);
			जाओ out;
		पूर्ण

		स_रखो(cmd, POISON_INUSE, PAGE_SIZE);
		*cmd++ = MI_LOAD_REGISTER_MEM;
		*cmd++ = reg;
		*cmd++ = offset;
		*cmd++ = MI_STORE_REGISTER_MEM | MI_USE_GGTT;
		*cmd++ = reg;
		*cmd++ = vma->node.start + result;
		*cmd = MI_BATCH_BUFFER_END;

		i915_gem_object_flush_map(obj);
		i915_gem_object_unpin_map(obj);

		flags = I915_DISPATCH_SECURE;
	पूर्ण

	पूर्णांकel_gt_chipset_flush(engine->gt);

	rq = igt_request_alloc(ctx, engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_unpin;
	पूर्ण

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	i915_vma_unlock(vma);
	अगर (err)
		जाओ skip_request;

	अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
		अगर (err)
			जाओ skip_request;
	पूर्ण

	err = engine->emit_bb_start(rq, vma->node.start, vma->node.size, flags);
	अगर (err)
		जाओ skip_request;

	i915_vma_unpin(vma);

	i915_request_add(rq);

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_set_to_cpu_करोमुख्य(obj, false);
	i915_gem_object_unlock(obj);
	अगर (err)
		जाओ out_vm;

	cmd = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ out_vm;
	पूर्ण

	*value = cmd[result / माप(*cmd)];
	i915_gem_object_unpin_map(obj);

	जाओ out_vm;
skip_request:
	i915_request_set_error_once(rq, err);
	i915_request_add(rq);
err_unpin:
	i915_vma_unpin(vma);
out_vm:
	i915_vm_put(vm);
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल पूर्णांक check_scratch_page(काष्ठा i915_gem_context *ctx, u32 *out)
अणु
	काष्ठा i915_address_space *vm;
	काष्ठा page *page;
	u32 *vaddr;
	पूर्णांक err = 0;

	vm = ctx_vm(ctx);
	अगर (!vm)
		वापस -ENODEV;

	page = __px_page(vm->scratch[0]);
	अगर (!page) अणु
		pr_err("No scratch page!\n");
		वापस -EINVAL;
	पूर्ण

	vaddr = kmap(page);
	अगर (!vaddr) अणु
		pr_err("No (mappable) scratch page!\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(out, vaddr, माप(*out));
	अगर (स_प्रथम_inv(vaddr, *out, PAGE_SIZE)) अणु
		pr_err("Inconsistent initial state of scratch page!\n");
		err = -EINVAL;
	पूर्ण
	kunmap(page);

	वापस err;
पूर्ण

अटल पूर्णांक igt_vm_isolation(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_gem_context *ctx_a, *ctx_b;
	अचिन्हित दीर्घ num_engines, count;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा igt_live_test t;
	I915_RND_STATE(prng);
	काष्ठा file *file;
	u64 vm_total;
	u32 expected;
	पूर्णांक err;

	अगर (INTEL_GEN(i915) < 7)
		वापस 0;

	/*
	 * The simple goal here is that a ग_लिखो पूर्णांकo one context is not
	 * observed in a second (separate page tables and scratch).
	 */

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	err = igt_live_test_begin(&t, i915, __func__, "");
	अगर (err)
		जाओ out_file;

	ctx_a = live_context(i915, file);
	अगर (IS_ERR(ctx_a)) अणु
		err = PTR_ERR(ctx_a);
		जाओ out_file;
	पूर्ण

	ctx_b = live_context(i915, file);
	अगर (IS_ERR(ctx_b)) अणु
		err = PTR_ERR(ctx_b);
		जाओ out_file;
	पूर्ण

	/* We can only test vm isolation, अगर the vm are distinct */
	अगर (ctx_vm(ctx_a) == ctx_vm(ctx_b))
		जाओ out_file;

	/* Read the initial state of the scratch page */
	err = check_scratch_page(ctx_a, &expected);
	अगर (err)
		जाओ out_file;

	err = check_scratch_page(ctx_b, &expected);
	अगर (err)
		जाओ out_file;

	vm_total = ctx_vm(ctx_a)->total;
	GEM_BUG_ON(ctx_vm(ctx_b)->total != vm_total);

	count = 0;
	num_engines = 0;
	क्रम_each_uabi_engine(engine, i915) अणु
		IGT_TIMEOUT(end_समय);
		अचिन्हित दीर्घ this = 0;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		/* Not all engines have their own GPR! */
		अगर (INTEL_GEN(i915) < 8 && engine->class != RENDER_CLASS)
			जारी;

		जबतक (!__igt_समयout(end_समय, शून्य)) अणु
			u32 value = 0xc5c5c5c5;
			u64 offset;

			/* Leave enough space at offset 0 क्रम the batch */
			offset = igt_अक्रमom_offset(&prng,
						   I915_GTT_PAGE_SIZE, vm_total,
						   माप(u32), alignof_dword);

			err = ग_लिखो_to_scratch(ctx_a, engine,
					       offset, 0xdeadbeef);
			अगर (err == 0)
				err = पढ़ो_from_scratch(ctx_b, engine,
							offset, &value);
			अगर (err)
				जाओ out_file;

			अगर (value != expected) अणु
				pr_err("%s: Read %08x from scratch (offset 0x%08x_%08x), after %lu reads!\n",
				       engine->name, value,
				       upper_32_bits(offset),
				       lower_32_bits(offset),
				       this);
				err = -EINVAL;
				जाओ out_file;
			पूर्ण

			this++;
		पूर्ण
		count += this;
		num_engines++;
	पूर्ण
	pr_info("Checked %lu scratch offsets across %lu engines\n",
		count, num_engines);

out_file:
	अगर (igt_live_test_end(&t))
		err = -EIO;
	fput(file);
	वापस err;
पूर्ण

अटल bool skip_unused_engines(काष्ठा पूर्णांकel_context *ce, व्योम *data)
अणु
	वापस !ce->state;
पूर्ण

अटल व्योम mock_barrier_task(व्योम *data)
अणु
	अचिन्हित पूर्णांक *counter = data;

	++*counter;
पूर्ण

अटल पूर्णांक mock_context_barrier(व्योम *arg)
अणु
#अघोषित pr_fmt
#घोषणा pr_fmt(x) "context_barrier_task():" # x
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_gem_context *ctx;
	काष्ठा i915_request *rq;
	अचिन्हित पूर्णांक counter;
	पूर्णांक err;

	/*
	 * The context barrier provides us with a callback after it emits
	 * a request; useful क्रम retiring old state after loading new.
	 */

	ctx = mock_context(i915, "mock");
	अगर (!ctx)
		वापस -ENOMEM;

	counter = 0;
	err = context_barrier_task(ctx, 0, शून्य, शून्य, शून्य,
				   mock_barrier_task, &counter);
	अगर (err) अणु
		pr_err("Failed at line %d, err=%d\n", __LINE__, err);
		जाओ out;
	पूर्ण
	अगर (counter == 0) अणु
		pr_err("Did not retire immediately with 0 engines\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	counter = 0;
	err = context_barrier_task(ctx, ALL_ENGINES, skip_unused_engines,
				   शून्य, शून्य, mock_barrier_task, &counter);
	अगर (err) अणु
		pr_err("Failed at line %d, err=%d\n", __LINE__, err);
		जाओ out;
	पूर्ण
	अगर (counter == 0) अणु
		pr_err("Did not retire immediately for all unused engines\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	rq = igt_request_alloc(ctx, i915->gt.engine[RCS0]);
	अगर (IS_ERR(rq)) अणु
		pr_err("Request allocation failed!\n");
		जाओ out;
	पूर्ण
	i915_request_add(rq);

	counter = 0;
	context_barrier_inject_fault = BIT(RCS0);
	err = context_barrier_task(ctx, ALL_ENGINES, शून्य, शून्य, शून्य,
				   mock_barrier_task, &counter);
	context_barrier_inject_fault = 0;
	अगर (err == -ENXIO)
		err = 0;
	अन्यथा
		pr_err("Did not hit fault injection!\n");
	अगर (counter != 0) अणु
		pr_err("Invoked callback on error!\n");
		err = -EIO;
	पूर्ण
	अगर (err)
		जाओ out;

	counter = 0;
	err = context_barrier_task(ctx, ALL_ENGINES, skip_unused_engines,
				   शून्य, शून्य, mock_barrier_task, &counter);
	अगर (err) अणु
		pr_err("Failed at line %d, err=%d\n", __LINE__, err);
		जाओ out;
	पूर्ण
	mock_device_flush(i915);
	अगर (counter == 0) अणु
		pr_err("Did not retire on each active engines\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

out:
	mock_context_बंद(ctx);
	वापस err;
#अघोषित pr_fmt
#घोषणा pr_fmt(x) x
पूर्ण

पूर्णांक i915_gem_context_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(mock_context_barrier),
	पूर्ण;
	काष्ठा drm_i915_निजी *i915;
	पूर्णांक err;

	i915 = mock_gem_device();
	अगर (!i915)
		वापस -ENOMEM;

	err = i915_subtests(tests, i915);

	mock_destroy_device(i915);
	वापस err;
पूर्ण

पूर्णांक i915_gem_context_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_nop_चयन),
		SUBTEST(live_parallel_चयन),
		SUBTEST(igt_ctx_exec),
		SUBTEST(igt_ctx_पढ़ोonly),
		SUBTEST(igt_ctx_sseu),
		SUBTEST(igt_shared_ctx_exec),
		SUBTEST(igt_vm_isolation),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_live_subtests(tests, i915);
पूर्ण
