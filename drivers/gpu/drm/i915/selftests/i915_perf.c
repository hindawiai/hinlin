<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/kref.h>

#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_gt.h"

#समावेश "i915_selftest.h"

#समावेश "igt_flush_test.h"
#समावेश "lib_sw_fence.h"

#घोषणा TEST_OA_CONFIG_UUID "12345678-1234-1234-1234-1234567890ab"

अटल पूर्णांक
alloc_empty_config(काष्ठा i915_perf *perf)
अणु
	काष्ठा i915_oa_config *oa_config;

	oa_config = kzalloc(माप(*oa_config), GFP_KERNEL);
	अगर (!oa_config)
		वापस -ENOMEM;

	oa_config->perf = perf;
	kref_init(&oa_config->ref);

	strlcpy(oa_config->uuid, TEST_OA_CONFIG_UUID, माप(oa_config->uuid));

	mutex_lock(&perf->metrics_lock);

	oa_config->id = idr_alloc(&perf->metrics_idr, oa_config, 2, 0, GFP_KERNEL);
	अगर (oa_config->id < 0)  अणु
		mutex_unlock(&perf->metrics_lock);
		i915_oa_config_put(oa_config);
		वापस -ENOMEM;
	पूर्ण

	mutex_unlock(&perf->metrics_lock);

	वापस 0;
पूर्ण

अटल व्योम
destroy_empty_config(काष्ठा i915_perf *perf)
अणु
	काष्ठा i915_oa_config *oa_config = शून्य, *पंचांगp;
	पूर्णांक id;

	mutex_lock(&perf->metrics_lock);

	idr_क्रम_each_entry(&perf->metrics_idr, पंचांगp, id) अणु
		अगर (!म_भेद(पंचांगp->uuid, TEST_OA_CONFIG_UUID)) अणु
			oa_config = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (oa_config)
		idr_हटाओ(&perf->metrics_idr, oa_config->id);

	mutex_unlock(&perf->metrics_lock);

	अगर (oa_config)
		i915_oa_config_put(oa_config);
पूर्ण

अटल काष्ठा i915_oa_config *
get_empty_config(काष्ठा i915_perf *perf)
अणु
	काष्ठा i915_oa_config *oa_config = शून्य, *पंचांगp;
	पूर्णांक id;

	mutex_lock(&perf->metrics_lock);

	idr_क्रम_each_entry(&perf->metrics_idr, पंचांगp, id) अणु
		अगर (!म_भेद(पंचांगp->uuid, TEST_OA_CONFIG_UUID)) अणु
			oa_config = i915_oa_config_get(पंचांगp);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&perf->metrics_lock);

	वापस oa_config;
पूर्ण

अटल काष्ठा i915_perf_stream *
test_stream(काष्ठा i915_perf *perf)
अणु
	काष्ठा drm_i915_perf_खोलो_param param = अणुपूर्ण;
	काष्ठा i915_oa_config *oa_config = get_empty_config(perf);
	काष्ठा perf_खोलो_properties props = अणु
		.engine = पूर्णांकel_engine_lookup_user(perf->i915,
						   I915_ENGINE_CLASS_RENDER,
						   0),
		.sample_flags = SAMPLE_OA_REPORT,
		.oa_क्रमmat = IS_GEN(perf->i915, 12) ?
		I915_OA_FORMAT_A32u40_A4u32_B8_C8 : I915_OA_FORMAT_C4_B8,
	पूर्ण;
	काष्ठा i915_perf_stream *stream;

	अगर (!oa_config)
		वापस शून्य;

	props.metrics_set = oa_config->id;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream) अणु
		i915_oa_config_put(oa_config);
		वापस शून्य;
	पूर्ण

	stream->perf = perf;

	mutex_lock(&perf->lock);
	अगर (i915_oa_stream_init(stream, &param, &props)) अणु
		kमुक्त(stream);
		stream =  शून्य;
	पूर्ण
	mutex_unlock(&perf->lock);

	i915_oa_config_put(oa_config);

	वापस stream;
पूर्ण

अटल व्योम stream_destroy(काष्ठा i915_perf_stream *stream)
अणु
	काष्ठा i915_perf *perf = stream->perf;

	mutex_lock(&perf->lock);
	i915_perf_destroy_locked(stream);
	mutex_unlock(&perf->lock);
पूर्ण

अटल पूर्णांक live_sanitycheck(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_perf_stream *stream;

	/* Quick check we can create a perf stream */

	stream = test_stream(&i915->perf);
	अगर (!stream)
		वापस -EINVAL;

	stream_destroy(stream);
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_बारtamp(काष्ठा i915_request *rq, पूर्णांक slot)
अणु
	u32 *cs;
	पूर्णांक len;

	cs = पूर्णांकel_ring_begin(rq, 6);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	len = 5;
	अगर (INTEL_GEN(rq->engine->i915) >= 8)
		len++;

	*cs++ = GFX_OP_PIPE_CONTROL(len);
	*cs++ = PIPE_CONTROL_GLOBAL_GTT_IVB |
		PIPE_CONTROL_STORE_DATA_INDEX |
		PIPE_CONTROL_WRITE_TIMESTAMP;
	*cs++ = slot * माप(u32);
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल kसमय_प्रकार poll_status(काष्ठा i915_request *rq, पूर्णांक slot)
अणु
	जबतक (!पूर्णांकel_पढ़ो_status_page(rq->engine, slot) &&
	       !i915_request_completed(rq))
		cpu_relax();

	वापस kसमय_get();
पूर्ण

अटल पूर्णांक live_noa_delay(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_perf_stream *stream;
	काष्ठा i915_request *rq;
	kसमय_प्रकार t0, t1;
	u64 expected;
	u32 delay;
	पूर्णांक err;
	पूर्णांक i;

	/* Check that the GPU delays matches expectations */

	stream = test_stream(&i915->perf);
	अगर (!stream)
		वापस -ENOMEM;

	expected = atomic64_पढ़ो(&stream->perf->noa_programming_delay);

	अगर (stream->engine->class != RENDER_CLASS) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		पूर्णांकel_ग_लिखो_status_page(stream->engine, 0x100 + i, 0);

	rq = पूर्णांकel_engine_create_kernel_request(stream->engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out;
	पूर्ण

	अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
		अगर (err) अणु
			i915_request_add(rq);
			जाओ out;
		पूर्ण
	पूर्ण

	err = ग_लिखो_बारtamp(rq, 0x100);
	अगर (err) अणु
		i915_request_add(rq);
		जाओ out;
	पूर्ण

	err = rq->engine->emit_bb_start(rq,
					i915_ggtt_offset(stream->noa_रुको), 0,
					I915_DISPATCH_SECURE);
	अगर (err) अणु
		i915_request_add(rq);
		जाओ out;
	पूर्ण

	err = ग_लिखो_बारtamp(rq, 0x102);
	अगर (err) अणु
		i915_request_add(rq);
		जाओ out;
	पूर्ण

	i915_request_get(rq);
	i915_request_add(rq);

	preempt_disable();
	t0 = poll_status(rq, 0x100);
	t1 = poll_status(rq, 0x102);
	preempt_enable();

	pr_info("CPU delay: %lluns, expected %lluns\n",
		kसमय_sub(t1, t0), expected);

	delay = पूर्णांकel_पढ़ो_status_page(stream->engine, 0x102);
	delay -= पूर्णांकel_पढ़ो_status_page(stream->engine, 0x100);
	delay = पूर्णांकel_gt_घड़ी_पूर्णांकerval_to_ns(stream->engine->gt, delay);
	pr_info("GPU delay: %uns, expected %lluns\n",
		delay, expected);

	अगर (4 * delay < 3 * expected || 2 * delay > 3 * expected) अणु
		pr_err("GPU delay [%uus] outside of expected threshold! [%lluus, %lluus]\n",
		       delay / 1000,
		       भाग_u64(3 * expected, 4000),
		       भाग_u64(3 * expected, 2000));
		err = -EINVAL;
	पूर्ण

	i915_request_put(rq);
out:
	stream_destroy(stream);
	वापस err;
पूर्ण

अटल पूर्णांक live_noa_gpr(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा i915_perf_stream *stream;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	u32 *cs, *store;
	व्योम *scratch;
	u32 gpr0;
	पूर्णांक err;
	पूर्णांक i;

	/* Check that the delay करोes not clobber user context state (GPR) */

	stream = test_stream(&i915->perf);
	अगर (!stream)
		वापस -ENOMEM;

	gpr0 = i915_mmio_reg_offset(GEN8_RING_CS_GPR(stream->engine->mmio_base, 0));

	ce = पूर्णांकel_context_create(stream->engine);
	अगर (IS_ERR(ce)) अणु
		err = PTR_ERR(ce);
		जाओ out;
	पूर्ण

	/* Poison the ce->vm so we detect ग_लिखोs not to the GGTT gt->scratch */
	scratch = kmap(__px_page(ce->vm->scratch[0]));
	स_रखो(scratch, POISON_FREE, PAGE_SIZE);

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_ce;
	पूर्ण
	i915_request_get(rq);

	अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
		अगर (err) अणु
			i915_request_add(rq);
			जाओ out_rq;
		पूर्ण
	पूर्ण

	/* Fill the 16 qword [32 dword] GPR with a known unlikely value */
	cs = पूर्णांकel_ring_begin(rq, 2 * 32 + 2);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		i915_request_add(rq);
		जाओ out_rq;
	पूर्ण

	*cs++ = MI_LOAD_REGISTER_IMM(32);
	क्रम (i = 0; i < 32; i++) अणु
		*cs++ = gpr0 + i * माप(u32);
		*cs++ = STACK_MAGIC;
	पूर्ण
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	/* Execute the GPU delay */
	err = rq->engine->emit_bb_start(rq,
					i915_ggtt_offset(stream->noa_रुको), 0,
					I915_DISPATCH_SECURE);
	अगर (err) अणु
		i915_request_add(rq);
		जाओ out_rq;
	पूर्ण

	/* Read the GPR back, using the pinned global HWSP क्रम convenience */
	store = स_रखो32(rq->engine->status_page.addr + 512, 0, 32);
	क्रम (i = 0; i < 32; i++) अणु
		u32 cmd;

		cs = पूर्णांकel_ring_begin(rq, 4);
		अगर (IS_ERR(cs)) अणु
			err = PTR_ERR(cs);
			i915_request_add(rq);
			जाओ out_rq;
		पूर्ण

		cmd = MI_STORE_REGISTER_MEM;
		अगर (INTEL_GEN(i915) >= 8)
			cmd++;
		cmd |= MI_USE_GGTT;

		*cs++ = cmd;
		*cs++ = gpr0 + i * माप(u32);
		*cs++ = i915_ggtt_offset(rq->engine->status_page.vma) +
			offset_in_page(store) +
			i * माप(u32);
		*cs++ = 0;
		पूर्णांकel_ring_advance(rq, cs);
	पूर्ण

	i915_request_add(rq);

	अगर (i915_request_रुको(rq, I915_WAIT_INTERRUPTIBLE, HZ / 2) < 0) अणु
		pr_err("noa_wait timed out\n");
		पूर्णांकel_gt_set_wedged(stream->engine->gt);
		err = -EIO;
		जाओ out_rq;
	पूर्ण

	/* Verअगरy that the GPR contain our expected values */
	क्रम (i = 0; i < 32; i++) अणु
		अगर (store[i] == STACK_MAGIC)
			जारी;

		pr_err("GPR[%d] lost, found:%08x, expected:%08x!\n",
		       i, store[i], STACK_MAGIC);
		err = -EINVAL;
	पूर्ण

	/* Verअगरy that the user's scratch page was not used क्रम GPR storage */
	अगर (स_प्रथम_inv(scratch, POISON_FREE, PAGE_SIZE)) अणु
		pr_err("Scratch page overwritten!\n");
		igt_hexdump(scratch, 4096);
		err = -EINVAL;
	पूर्ण

out_rq:
	i915_request_put(rq);
out_ce:
	kunmap(__px_page(ce->vm->scratch[0]));
	पूर्णांकel_context_put(ce);
out:
	stream_destroy(stream);
	वापस err;
पूर्ण

पूर्णांक i915_perf_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_sanitycheck),
		SUBTEST(live_noa_delay),
		SUBTEST(live_noa_gpr),
	पूर्ण;
	काष्ठा i915_perf *perf = &i915->perf;
	पूर्णांक err;

	अगर (!perf->metrics_kobj || !perf->ops.enable_metric_set)
		वापस 0;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	err = alloc_empty_config(&i915->perf);
	अगर (err)
		वापस err;

	err = i915_subtests(tests, i915);

	destroy_empty_config(&i915->perf);

	वापस err;
पूर्ण
