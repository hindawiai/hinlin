<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_engine_user.h"
#समावेश "gt/intel_gt.h"
#समावेश "i915_selftest.h"
#समावेश "intel_reset.h"

#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/igt_reset.h"
#समावेश "selftests/igt_spinner.h"
#समावेश "selftests/mock_drm.h"

#समावेश "gem/selftests/igt_gem_utils.h"
#समावेश "gem/selftests/mock_context.h"

अटल स्थिर काष्ठा wo_रेजिस्टर अणु
	क्रमागत पूर्णांकel_platक्रमm platक्रमm;
	u32 reg;
पूर्ण wo_रेजिस्टरs[] = अणु
	अणु INTEL_GEMINILAKE, 0x731c पूर्ण
पूर्ण;

काष्ठा wa_lists अणु
	काष्ठा i915_wa_list gt_wa_list;
	काष्ठा अणु
		काष्ठा i915_wa_list wa_list;
		काष्ठा i915_wa_list ctx_wa_list;
	पूर्ण engine[I915_NUM_ENGINES];
पूर्ण;

अटल पूर्णांक request_add_sync(काष्ठा i915_request *rq, पूर्णांक err)
अणु
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
		err = -EIO;
	i915_request_put(rq);

	वापस err;
पूर्ण

अटल पूर्णांक request_add_spin(काष्ठा i915_request *rq, काष्ठा igt_spinner *spin)
अणु
	पूर्णांक err = 0;

	i915_request_get(rq);
	i915_request_add(rq);
	अगर (spin && !igt_रुको_क्रम_spinner(spin, rq))
		err = -ETIMEDOUT;
	i915_request_put(rq);

	वापस err;
पूर्ण

अटल व्योम
reference_lists_init(काष्ठा पूर्णांकel_gt *gt, काष्ठा wa_lists *lists)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	स_रखो(lists, 0, माप(*lists));

	wa_init_start(&lists->gt_wa_list, "GT_REF", "global");
	gt_init_workarounds(gt->i915, &lists->gt_wa_list);
	wa_init_finish(&lists->gt_wa_list);

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_wa_list *wal = &lists->engine[id].wa_list;

		wa_init_start(wal, "REF", engine->name);
		engine_init_workarounds(engine, wal);
		wa_init_finish(wal);

		__पूर्णांकel_engine_init_ctx_wa(engine,
					   &lists->engine[id].ctx_wa_list,
					   "CTX_REF");
	पूर्ण
पूर्ण

अटल व्योम
reference_lists_fini(काष्ठा पूर्णांकel_gt *gt, काष्ठा wa_lists *lists)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt, id)
		पूर्णांकel_wa_list_मुक्त(&lists->engine[id].wa_list);

	पूर्णांकel_wa_list_मुक्त(&lists->gt_wa_list);
पूर्ण

अटल काष्ठा drm_i915_gem_object *
पढ़ो_nonprivs(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	स्थिर u32 base = engine->mmio_base;
	काष्ठा drm_i915_gem_object *result;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma;
	u32 srm, *cs;
	पूर्णांक err;
	पूर्णांक i;

	result = i915_gem_object_create_पूर्णांकernal(engine->i915, PAGE_SIZE);
	अगर (IS_ERR(result))
		वापस result;

	i915_gem_object_set_cache_coherency(result, I915_CACHE_LLC);

	cs = i915_gem_object_pin_map_unlocked(result, I915_MAP_WB);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_obj;
	पूर्ण
	स_रखो(cs, 0xc5, PAGE_SIZE);
	i915_gem_object_flush_map(result);
	i915_gem_object_unpin_map(result);

	vma = i915_vma_instance(result, &engine->gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_obj;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_GLOBAL);
	अगर (err)
		जाओ err_obj;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_pin;
	पूर्ण

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	i915_vma_unlock(vma);
	अगर (err)
		जाओ err_req;

	srm = MI_STORE_REGISTER_MEM | MI_SRM_LRM_GLOBAL_GTT;
	अगर (INTEL_GEN(engine->i915) >= 8)
		srm++;

	cs = पूर्णांकel_ring_begin(rq, 4 * RING_MAX_NONPRIV_SLOTS);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_req;
	पूर्ण

	क्रम (i = 0; i < RING_MAX_NONPRIV_SLOTS; i++) अणु
		*cs++ = srm;
		*cs++ = i915_mmio_reg_offset(RING_FORCE_TO_NONPRIV(base, i));
		*cs++ = i915_ggtt_offset(vma) + माप(u32) * i;
		*cs++ = 0;
	पूर्ण
	पूर्णांकel_ring_advance(rq, cs);

	i915_request_add(rq);
	i915_vma_unpin(vma);

	वापस result;

err_req:
	i915_request_add(rq);
err_pin:
	i915_vma_unpin(vma);
err_obj:
	i915_gem_object_put(result);
	वापस ERR_PTR(err);
पूर्ण

अटल u32
get_whitelist_reg(स्थिर काष्ठा पूर्णांकel_engine_cs *engine, अचिन्हित पूर्णांक i)
अणु
	i915_reg_t reg = i < engine->whitelist.count ?
			 engine->whitelist.list[i].reg :
			 RING_NOPID(engine->mmio_base);

	वापस i915_mmio_reg_offset(reg);
पूर्ण

अटल व्योम
prपूर्णांक_results(स्थिर काष्ठा पूर्णांकel_engine_cs *engine, स्थिर u32 *results)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < RING_MAX_NONPRIV_SLOTS; i++) अणु
		u32 expected = get_whitelist_reg(engine, i);
		u32 actual = results[i];

		pr_info("RING_NONPRIV[%d]: expected 0x%08x, found 0x%08x\n",
			i, expected, actual);
	पूर्ण
पूर्ण

अटल पूर्णांक check_whitelist(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	काष्ठा drm_i915_gem_object *results;
	काष्ठा पूर्णांकel_wedge_me wedge;
	u32 *vaddr;
	पूर्णांक err;
	पूर्णांक i;

	results = पढ़ो_nonprivs(ce);
	अगर (IS_ERR(results))
		वापस PTR_ERR(results);

	err = 0;
	i915_gem_object_lock(results, शून्य);
	पूर्णांकel_wedge_on_समयout(&wedge, engine->gt, HZ / 5) /* safety net! */
		err = i915_gem_object_set_to_cpu_करोमुख्य(results, false);

	अगर (पूर्णांकel_gt_is_wedged(engine->gt))
		err = -EIO;
	अगर (err)
		जाओ out_put;

	vaddr = i915_gem_object_pin_map(results, I915_MAP_WB);
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		जाओ out_put;
	पूर्ण

	क्रम (i = 0; i < RING_MAX_NONPRIV_SLOTS; i++) अणु
		u32 expected = get_whitelist_reg(engine, i);
		u32 actual = vaddr[i];

		अगर (expected != actual) अणु
			prपूर्णांक_results(engine, vaddr);
			pr_err("Invalid RING_NONPRIV[%d], expected 0x%08x, found 0x%08x\n",
			       i, expected, actual);

			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	i915_gem_object_unpin_map(results);
out_put:
	i915_gem_object_unlock(results);
	i915_gem_object_put(results);
	वापस err;
पूर्ण

अटल पूर्णांक करो_device_reset(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_gt_reset(engine->gt, engine->mask, "live_workarounds");
	वापस 0;
पूर्ण

अटल पूर्णांक करो_engine_reset(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस पूर्णांकel_engine_reset(engine, "live_workarounds");
पूर्ण

अटल पूर्णांक
चयन_to_scratch_context(काष्ठा पूर्णांकel_engine_cs *engine,
			  काष्ठा igt_spinner *spin)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	पूर्णांक err = 0;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	rq = igt_spinner_create_request(spin, ce, MI_NOOP);
	पूर्णांकel_context_put(ce);

	अगर (IS_ERR(rq)) अणु
		spin = शून्य;
		err = PTR_ERR(rq);
		जाओ err;
	पूर्ण

	err = request_add_spin(rq, spin);
err:
	अगर (err && spin)
		igt_spinner_end(spin);

	वापस err;
पूर्ण

अटल पूर्णांक check_whitelist_across_reset(काष्ठा पूर्णांकel_engine_cs *engine,
					पूर्णांक (*reset)(काष्ठा पूर्णांकel_engine_cs *),
					स्थिर अक्षर *name)
अणु
	काष्ठा पूर्णांकel_context *ce, *पंचांगp;
	काष्ठा igt_spinner spin;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक err;

	pr_info("Checking %d whitelisted registers on %s (RING_NONPRIV) [%s]\n",
		engine->whitelist.count, engine->name, name);

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	err = igt_spinner_init(&spin, engine->gt);
	अगर (err)
		जाओ out_ctx;

	err = check_whitelist(ce);
	अगर (err) अणु
		pr_err("Invalid whitelist *before* %s reset!\n", name);
		जाओ out_spin;
	पूर्ण

	err = चयन_to_scratch_context(engine, &spin);
	अगर (err)
		जाओ out_spin;

	with_पूर्णांकel_runसमय_pm(engine->uncore->rpm, wakeref)
		err = reset(engine);

	igt_spinner_end(&spin);

	अगर (err) अणु
		pr_err("%s reset failed\n", name);
		जाओ out_spin;
	पूर्ण

	err = check_whitelist(ce);
	अगर (err) अणु
		pr_err("Whitelist not preserved in context across %s reset!\n",
		       name);
		जाओ out_spin;
	पूर्ण

	पंचांगp = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(पंचांगp)) अणु
		err = PTR_ERR(पंचांगp);
		जाओ out_spin;
	पूर्ण
	पूर्णांकel_context_put(ce);
	ce = पंचांगp;

	err = check_whitelist(ce);
	अगर (err) अणु
		pr_err("Invalid whitelist *after* %s reset in fresh context!\n",
		       name);
		जाओ out_spin;
	पूर्ण

out_spin:
	igt_spinner_fini(&spin);
out_ctx:
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल काष्ठा i915_vma *create_batch(काष्ठा i915_address_space *vm)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(vm->i915, 16 * PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_obj;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ err_obj;

	वापस vma;

err_obj:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल u32 reg_ग_लिखो(u32 old, u32 new, u32 rsvd)
अणु
	अगर (rsvd == 0x0000ffff) अणु
		old &= ~(new >> 16);
		old |= new & (new >> 16);
	पूर्ण अन्यथा अणु
		old &= ~rsvd;
		old |= new & rsvd;
	पूर्ण

	वापस old;
पूर्ण

अटल bool wo_रेजिस्टर(काष्ठा पूर्णांकel_engine_cs *engine, u32 reg)
अणु
	क्रमागत पूर्णांकel_platक्रमm platक्रमm = INTEL_INFO(engine->i915)->platक्रमm;
	पूर्णांक i;

	अगर ((reg & RING_FORCE_TO_NONPRIV_ACCESS_MASK) ==
	     RING_FORCE_TO_NONPRIV_ACCESS_WR)
		वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(wo_रेजिस्टरs); i++) अणु
		अगर (wo_रेजिस्टरs[i].platक्रमm == platक्रमm &&
		    wo_रेजिस्टरs[i].reg == reg)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool बारtamp(स्थिर काष्ठा पूर्णांकel_engine_cs *engine, u32 reg)
अणु
	reg = (reg - engine->mmio_base) & ~RING_FORCE_TO_NONPRIV_ACCESS_MASK;
	चयन (reg) अणु
	हाल 0x358:
	हाल 0x35c:
	हाल 0x3a8:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ro_रेजिस्टर(u32 reg)
अणु
	अगर ((reg & RING_FORCE_TO_NONPRIV_ACCESS_MASK) ==
	     RING_FORCE_TO_NONPRIV_ACCESS_RD)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक whitelist_writable_count(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांक count = engine->whitelist.count;
	पूर्णांक i;

	क्रम (i = 0; i < engine->whitelist.count; i++) अणु
		u32 reg = i915_mmio_reg_offset(engine->whitelist.list[i].reg);

		अगर (ro_रेजिस्टर(reg))
			count--;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक check_dirty_whitelist(काष्ठा पूर्णांकel_context *ce)
अणु
	स्थिर u32 values[] = अणु
		0x00000000,
		0x01010101,
		0x10100101,
		0x03030303,
		0x30300303,
		0x05050505,
		0x50500505,
		0x0f0f0f0f,
		0xf00ff00f,
		0x10101010,
		0xf0f01010,
		0x30303030,
		0xa0a03030,
		0x50505050,
		0xc0c05050,
		0xf0f0f0f0,
		0x11111111,
		0x33333333,
		0x55555555,
		0x0000ffff,
		0x00ff00ff,
		0xff0000ff,
		0xffff00ff,
		0xffffffff,
	पूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	काष्ठा i915_vma *scratch;
	काष्ठा i915_vma *batch;
	पूर्णांक err = 0, i, v, sz;
	u32 *cs, *results;

	sz = (2 * ARRAY_SIZE(values) + 1) * माप(u32);
	scratch = __vm_create_scratch_क्रम_पढ़ो_pinned(ce->vm, sz);
	अगर (IS_ERR(scratch))
		वापस PTR_ERR(scratch);

	batch = create_batch(ce->vm);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_scratch;
	पूर्ण

	क्रम (i = 0; i < engine->whitelist.count; i++) अणु
		u32 reg = i915_mmio_reg_offset(engine->whitelist.list[i].reg);
		काष्ठा i915_gem_ww_ctx ww;
		u64 addr = scratch->node.start;
		काष्ठा i915_request *rq;
		u32 srm, lrm, rsvd;
		u32 expect;
		पूर्णांक idx;
		bool ro_reg;

		अगर (wo_रेजिस्टर(engine, reg))
			जारी;

		अगर (बारtamp(engine, reg))
			जारी; /* बारtamps are expected to स्वतःincrement */

		ro_reg = ro_रेजिस्टर(reg);

		i915_gem_ww_ctx_init(&ww, false);
retry:
		cs = शून्य;
		err = i915_gem_object_lock(scratch->obj, &ww);
		अगर (!err)
			err = i915_gem_object_lock(batch->obj, &ww);
		अगर (!err)
			err = पूर्णांकel_context_pin_ww(ce, &ww);
		अगर (err)
			जाओ out;

		cs = i915_gem_object_pin_map(batch->obj, I915_MAP_WC);
		अगर (IS_ERR(cs)) अणु
			err = PTR_ERR(cs);
			जाओ out_ctx;
		पूर्ण

		results = i915_gem_object_pin_map(scratch->obj, I915_MAP_WB);
		अगर (IS_ERR(results)) अणु
			err = PTR_ERR(results);
			जाओ out_unmap_batch;
		पूर्ण

		/* Clear non priv flags */
		reg &= RING_FORCE_TO_NONPRIV_ADDRESS_MASK;

		srm = MI_STORE_REGISTER_MEM;
		lrm = MI_LOAD_REGISTER_MEM;
		अगर (INTEL_GEN(engine->i915) >= 8)
			lrm++, srm++;

		pr_debug("%s: Writing garbage to %x\n",
			 engine->name, reg);

		/* SRM original */
		*cs++ = srm;
		*cs++ = reg;
		*cs++ = lower_32_bits(addr);
		*cs++ = upper_32_bits(addr);

		idx = 1;
		क्रम (v = 0; v < ARRAY_SIZE(values); v++) अणु
			/* LRI garbage */
			*cs++ = MI_LOAD_REGISTER_IMM(1);
			*cs++ = reg;
			*cs++ = values[v];

			/* SRM result */
			*cs++ = srm;
			*cs++ = reg;
			*cs++ = lower_32_bits(addr + माप(u32) * idx);
			*cs++ = upper_32_bits(addr + माप(u32) * idx);
			idx++;
		पूर्ण
		क्रम (v = 0; v < ARRAY_SIZE(values); v++) अणु
			/* LRI garbage */
			*cs++ = MI_LOAD_REGISTER_IMM(1);
			*cs++ = reg;
			*cs++ = ~values[v];

			/* SRM result */
			*cs++ = srm;
			*cs++ = reg;
			*cs++ = lower_32_bits(addr + माप(u32) * idx);
			*cs++ = upper_32_bits(addr + माप(u32) * idx);
			idx++;
		पूर्ण
		GEM_BUG_ON(idx * माप(u32) > scratch->size);

		/* LRM original -- करोn't leave garbage in the context! */
		*cs++ = lrm;
		*cs++ = reg;
		*cs++ = lower_32_bits(addr);
		*cs++ = upper_32_bits(addr);

		*cs++ = MI_BATCH_BUFFER_END;

		i915_gem_object_flush_map(batch->obj);
		i915_gem_object_unpin_map(batch->obj);
		पूर्णांकel_gt_chipset_flush(engine->gt);
		cs = शून्य;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out_unmap_scratch;
		पूर्ण

		अगर (engine->emit_init_bपढ़ोcrumb) अणु /* Be nice अगर we hang */
			err = engine->emit_init_bपढ़ोcrumb(rq);
			अगर (err)
				जाओ err_request;
		पूर्ण

		err = i915_request_aरुको_object(rq, batch->obj, false);
		अगर (err == 0)
			err = i915_vma_move_to_active(batch, rq, 0);
		अगर (err)
			जाओ err_request;

		err = i915_request_aरुको_object(rq, scratch->obj, true);
		अगर (err == 0)
			err = i915_vma_move_to_active(scratch, rq,
						      EXEC_OBJECT_WRITE);
		अगर (err)
			जाओ err_request;

		err = engine->emit_bb_start(rq,
					    batch->node.start, PAGE_SIZE,
					    0);
		अगर (err)
			जाओ err_request;

err_request:
		err = request_add_sync(rq, err);
		अगर (err) अणु
			pr_err("%s: Futzing %x timedout; cancelling test\n",
			       engine->name, reg);
			पूर्णांकel_gt_set_wedged(engine->gt);
			जाओ out_unmap_scratch;
		पूर्ण

		GEM_BUG_ON(values[ARRAY_SIZE(values) - 1] != 0xffffffff);
		अगर (!ro_reg) अणु
			/* detect ग_लिखो masking */
			rsvd = results[ARRAY_SIZE(values)];
			अगर (!rsvd) अणु
				pr_err("%s: Unable to write to whitelisted register %x\n",
				       engine->name, reg);
				err = -EINVAL;
				जाओ out_unmap_scratch;
			पूर्ण
		पूर्ण अन्यथा अणु
			rsvd = 0;
		पूर्ण

		expect = results[0];
		idx = 1;
		क्रम (v = 0; v < ARRAY_SIZE(values); v++) अणु
			अगर (ro_reg)
				expect = results[0];
			अन्यथा
				expect = reg_ग_लिखो(expect, values[v], rsvd);

			अगर (results[idx] != expect)
				err++;
			idx++;
		पूर्ण
		क्रम (v = 0; v < ARRAY_SIZE(values); v++) अणु
			अगर (ro_reg)
				expect = results[0];
			अन्यथा
				expect = reg_ग_लिखो(expect, ~values[v], rsvd);

			अगर (results[idx] != expect)
				err++;
			idx++;
		पूर्ण
		अगर (err) अणु
			pr_err("%s: %d mismatch between values written to whitelisted register [%x], and values read back!\n",
			       engine->name, err, reg);

			अगर (ro_reg)
				pr_info("%s: Whitelisted read-only register: %x, original value %08x\n",
					engine->name, reg, results[0]);
			अन्यथा
				pr_info("%s: Whitelisted register: %x, original value %08x, rsvd %08x\n",
					engine->name, reg, results[0], rsvd);

			expect = results[0];
			idx = 1;
			क्रम (v = 0; v < ARRAY_SIZE(values); v++) अणु
				u32 w = values[v];

				अगर (ro_reg)
					expect = results[0];
				अन्यथा
					expect = reg_ग_लिखो(expect, w, rsvd);
				pr_info("Wrote %08x, read %08x, expect %08x\n",
					w, results[idx], expect);
				idx++;
			पूर्ण
			क्रम (v = 0; v < ARRAY_SIZE(values); v++) अणु
				u32 w = ~values[v];

				अगर (ro_reg)
					expect = results[0];
				अन्यथा
					expect = reg_ग_लिखो(expect, w, rsvd);
				pr_info("Wrote %08x, read %08x, expect %08x\n",
					w, results[idx], expect);
				idx++;
			पूर्ण

			err = -EINVAL;
		पूर्ण
out_unmap_scratch:
		i915_gem_object_unpin_map(scratch->obj);
out_unmap_batch:
		अगर (cs)
			i915_gem_object_unpin_map(batch->obj);
out_ctx:
		पूर्णांकel_context_unpin(ce);
out:
		अगर (err == -EDEADLK) अणु
			err = i915_gem_ww_ctx_backoff(&ww);
			अगर (!err)
				जाओ retry;
		पूर्ण
		i915_gem_ww_ctx_fini(&ww);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (igt_flush_test(engine->i915))
		err = -EIO;

	i915_vma_unpin_and_release(&batch, 0);
out_scratch:
	i915_vma_unpin_and_release(&scratch, 0);
	वापस err;
पूर्ण

अटल पूर्णांक live_dirty_whitelist(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/* Can the user ग_लिखो to the whitelisted रेजिस्टरs? */

	अगर (INTEL_GEN(gt->i915) < 7) /* minimum requirement क्रम LRI, SRM, LRM */
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;
		पूर्णांक err;

		अगर (engine->whitelist.count == 0)
			जारी;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce))
			वापस PTR_ERR(ce);

		err = check_dirty_whitelist(ce);
		पूर्णांकel_context_put(ce);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक live_reset_whitelist(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/* If we reset the gpu, we should not lose the RING_NONPRIV */
	igt_global_reset_lock(gt);

	क्रम_each_engine(engine, gt, id) अणु
		अगर (engine->whitelist.count == 0)
			जारी;

		अगर (पूर्णांकel_has_reset_engine(gt)) अणु
			err = check_whitelist_across_reset(engine,
							   करो_engine_reset,
							   "engine");
			अगर (err)
				जाओ out;
		पूर्ण

		अगर (पूर्णांकel_has_gpu_reset(gt)) अणु
			err = check_whitelist_across_reset(engine,
							   करो_device_reset,
							   "device");
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	igt_global_reset_unlock(gt);
	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_whitelisted_रेजिस्टरs(काष्ठा पूर्णांकel_context *ce,
				      काष्ठा i915_vma *results)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	काष्ठा i915_request *rq;
	पूर्णांक i, err = 0;
	u32 srm, *cs;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	i915_vma_lock(results);
	err = i915_request_aरुको_object(rq, results->obj, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(results, rq, EXEC_OBJECT_WRITE);
	i915_vma_unlock(results);
	अगर (err)
		जाओ err_req;

	srm = MI_STORE_REGISTER_MEM;
	अगर (INTEL_GEN(engine->i915) >= 8)
		srm++;

	cs = पूर्णांकel_ring_begin(rq, 4 * engine->whitelist.count);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_req;
	पूर्ण

	क्रम (i = 0; i < engine->whitelist.count; i++) अणु
		u64 offset = results->node.start + माप(u32) * i;
		u32 reg = i915_mmio_reg_offset(engine->whitelist.list[i].reg);

		/* Clear non priv flags */
		reg &= RING_FORCE_TO_NONPRIV_ADDRESS_MASK;

		*cs++ = srm;
		*cs++ = reg;
		*cs++ = lower_32_bits(offset);
		*cs++ = upper_32_bits(offset);
	पूर्ण
	पूर्णांकel_ring_advance(rq, cs);

err_req:
	वापस request_add_sync(rq, err);
पूर्ण

अटल पूर्णांक scrub_whitelisted_रेजिस्टरs(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *batch;
	पूर्णांक i, err = 0;
	u32 *cs;

	batch = create_batch(ce->vm);
	अगर (IS_ERR(batch))
		वापस PTR_ERR(batch);

	cs = i915_gem_object_pin_map_unlocked(batch->obj, I915_MAP_WC);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_batch;
	पूर्ण

	*cs++ = MI_LOAD_REGISTER_IMM(whitelist_writable_count(engine));
	क्रम (i = 0; i < engine->whitelist.count; i++) अणु
		u32 reg = i915_mmio_reg_offset(engine->whitelist.list[i].reg);

		अगर (ro_रेजिस्टर(reg))
			जारी;

		/* Clear non priv flags */
		reg &= RING_FORCE_TO_NONPRIV_ADDRESS_MASK;

		*cs++ = reg;
		*cs++ = 0xffffffff;
	पूर्ण
	*cs++ = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(batch->obj);
	पूर्णांकel_gt_chipset_flush(engine->gt);

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_unpin;
	पूर्ण

	अगर (engine->emit_init_bपढ़ोcrumb) अणु /* Be nice अगर we hang */
		err = engine->emit_init_bपढ़ोcrumb(rq);
		अगर (err)
			जाओ err_request;
	पूर्ण

	i915_vma_lock(batch);
	err = i915_request_aरुको_object(rq, batch->obj, false);
	अगर (err == 0)
		err = i915_vma_move_to_active(batch, rq, 0);
	i915_vma_unlock(batch);
	अगर (err)
		जाओ err_request;

	/* Perक्रमm the ग_लिखोs from an unprivileged "user" batch */
	err = engine->emit_bb_start(rq, batch->node.start, 0, 0);

err_request:
	err = request_add_sync(rq, err);

err_unpin:
	i915_gem_object_unpin_map(batch->obj);
err_batch:
	i915_vma_unpin_and_release(&batch, 0);
	वापस err;
पूर्ण

काष्ठा regmask अणु
	i915_reg_t reg;
	अचिन्हित दीर्घ gen_mask;
पूर्ण;

अटल bool find_reg(काष्ठा drm_i915_निजी *i915,
		     i915_reg_t reg,
		     स्थिर काष्ठा regmask *tbl,
		     अचिन्हित दीर्घ count)
अणु
	u32 offset = i915_mmio_reg_offset(reg);

	जबतक (count--) अणु
		अगर (INTEL_INFO(i915)->gen_mask & tbl->gen_mask &&
		    i915_mmio_reg_offset(tbl->reg) == offset)
			वापस true;
		tbl++;
	पूर्ण

	वापस false;
पूर्ण

अटल bool parकरोn_reg(काष्ठा drm_i915_निजी *i915, i915_reg_t reg)
अणु
	/* Alas, we must parकरोn some whitelists. Mistakes alपढ़ोy made */
	अटल स्थिर काष्ठा regmask parकरोn[] = अणु
		अणु GEN9_CTX_PREEMPT_REG, INTEL_GEN_MASK(9, 9) पूर्ण,
		अणु GEN8_L3SQCREG4, INTEL_GEN_MASK(9, 9) पूर्ण,
	पूर्ण;

	वापस find_reg(i915, reg, parकरोn, ARRAY_SIZE(parकरोn));
पूर्ण

अटल bool result_eq(काष्ठा पूर्णांकel_engine_cs *engine,
		      u32 a, u32 b, i915_reg_t reg)
अणु
	अगर (a != b && !parकरोn_reg(engine->i915, reg)) अणु
		pr_err("Whitelisted register 0x%4x not context saved: A=%08x, B=%08x\n",
		       i915_mmio_reg_offset(reg), a, b);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool ग_लिखोonly_reg(काष्ठा drm_i915_निजी *i915, i915_reg_t reg)
अणु
	/* Some रेजिस्टरs करो not seem to behave and our ग_लिखोs unपढ़ोable */
	अटल स्थिर काष्ठा regmask wo[] = अणु
		अणु GEN9_SLICE_COMMON_ECO_CHICKEN1, INTEL_GEN_MASK(9, 9) पूर्ण,
	पूर्ण;

	वापस find_reg(i915, reg, wo, ARRAY_SIZE(wo));
पूर्ण

अटल bool result_neq(काष्ठा पूर्णांकel_engine_cs *engine,
		       u32 a, u32 b, i915_reg_t reg)
अणु
	अगर (a == b && !ग_लिखोonly_reg(engine->i915, reg)) अणु
		pr_err("Whitelist register 0x%4x:%08x was unwritable\n",
		       i915_mmio_reg_offset(reg), a);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
check_whitelisted_रेजिस्टरs(काष्ठा पूर्णांकel_engine_cs *engine,
			    काष्ठा i915_vma *A,
			    काष्ठा i915_vma *B,
			    bool (*fn)(काष्ठा पूर्णांकel_engine_cs *engine,
				       u32 a, u32 b,
				       i915_reg_t reg))
अणु
	u32 *a, *b;
	पूर्णांक i, err;

	a = i915_gem_object_pin_map_unlocked(A->obj, I915_MAP_WB);
	अगर (IS_ERR(a))
		वापस PTR_ERR(a);

	b = i915_gem_object_pin_map_unlocked(B->obj, I915_MAP_WB);
	अगर (IS_ERR(b)) अणु
		err = PTR_ERR(b);
		जाओ err_a;
	पूर्ण

	err = 0;
	क्रम (i = 0; i < engine->whitelist.count; i++) अणु
		स्थिर काष्ठा i915_wa *wa = &engine->whitelist.list[i];

		अगर (i915_mmio_reg_offset(wa->reg) &
		    RING_FORCE_TO_NONPRIV_ACCESS_RD)
			जारी;

		अगर (!fn(engine, a[i], b[i], wa->reg))
			err = -EINVAL;
	पूर्ण

	i915_gem_object_unpin_map(B->obj);
err_a:
	i915_gem_object_unpin_map(A->obj);
	वापस err;
पूर्ण

अटल पूर्णांक live_isolated_whitelist(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा अणु
		काष्ठा i915_vma *scratch[2];
	पूर्ण client[2] = अणुपूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक i, err = 0;

	/*
	 * Check that a ग_लिखो पूर्णांकo a whitelist रेजिस्टर works, but
	 * invisible to a second context.
	 */

	अगर (!पूर्णांकel_engines_has_context_isolation(gt->i915))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(client); i++) अणु
		client[i].scratch[0] =
			__vm_create_scratch_क्रम_पढ़ो_pinned(gt->vm, 4096);
		अगर (IS_ERR(client[i].scratch[0])) अणु
			err = PTR_ERR(client[i].scratch[0]);
			जाओ err;
		पूर्ण

		client[i].scratch[1] =
			__vm_create_scratch_क्रम_पढ़ो_pinned(gt->vm, 4096);
		अगर (IS_ERR(client[i].scratch[1])) अणु
			err = PTR_ERR(client[i].scratch[1]);
			i915_vma_unpin_and_release(&client[i].scratch[0], 0);
			जाओ err;
		पूर्ण
	पूर्ण

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce[2];

		अगर (!engine->kernel_context->vm)
			जारी;

		अगर (!whitelist_writable_count(engine))
			जारी;

		ce[0] = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce[0])) अणु
			err = PTR_ERR(ce[0]);
			अवरोध;
		पूर्ण
		ce[1] = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce[1])) अणु
			err = PTR_ERR(ce[1]);
			पूर्णांकel_context_put(ce[0]);
			अवरोध;
		पूर्ण

		/* Read शेष values */
		err = पढ़ो_whitelisted_रेजिस्टरs(ce[0], client[0].scratch[0]);
		अगर (err)
			जाओ err_ce;

		/* Try to overग_लिखो रेजिस्टरs (should only affect ctx0) */
		err = scrub_whitelisted_रेजिस्टरs(ce[0]);
		अगर (err)
			जाओ err_ce;

		/* Read values from ctx1, we expect these to be शेषs */
		err = पढ़ो_whitelisted_रेजिस्टरs(ce[1], client[1].scratch[0]);
		अगर (err)
			जाओ err_ce;

		/* Verअगरy that both पढ़ोs वापस the same शेष values */
		err = check_whitelisted_रेजिस्टरs(engine,
						  client[0].scratch[0],
						  client[1].scratch[0],
						  result_eq);
		अगर (err)
			जाओ err_ce;

		/* Read back the updated values in ctx0 */
		err = पढ़ो_whitelisted_रेजिस्टरs(ce[0], client[0].scratch[1]);
		अगर (err)
			जाओ err_ce;

		/* User should be granted privilege to overwhite regs */
		err = check_whitelisted_रेजिस्टरs(engine,
						  client[0].scratch[0],
						  client[0].scratch[1],
						  result_neq);
err_ce:
		पूर्णांकel_context_put(ce[1]);
		पूर्णांकel_context_put(ce[0]);
		अगर (err)
			अवरोध;
	पूर्ण

err:
	क्रम (i = 0; i < ARRAY_SIZE(client); i++) अणु
		i915_vma_unpin_and_release(&client[i].scratch[1], 0);
		i915_vma_unpin_and_release(&client[i].scratch[0], 0);
	पूर्ण

	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	वापस err;
पूर्ण

अटल bool
verअगरy_wa_lists(काष्ठा पूर्णांकel_gt *gt, काष्ठा wa_lists *lists,
		स्थिर अक्षर *str)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	bool ok = true;

	ok &= wa_list_verअगरy(gt->uncore, &lists->gt_wa_list, str);

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce))
			वापस false;

		ok &= engine_wa_list_verअगरy(ce,
					    &lists->engine[id].wa_list,
					    str) == 0;

		ok &= engine_wa_list_verअगरy(ce,
					    &lists->engine[id].ctx_wa_list,
					    str) == 0;

		पूर्णांकel_context_put(ce);
	पूर्ण

	वापस ok;
पूर्ण

अटल पूर्णांक
live_gpu_reset_workarounds(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा wa_lists lists;
	bool ok;

	अगर (!पूर्णांकel_has_gpu_reset(gt))
		वापस 0;

	pr_info("Verifying after GPU reset...\n");

	igt_global_reset_lock(gt);
	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);

	reference_lists_init(gt, &lists);

	ok = verअगरy_wa_lists(gt, &lists, "before reset");
	अगर (!ok)
		जाओ out;

	पूर्णांकel_gt_reset(gt, ALL_ENGINES, "live_workarounds");

	ok = verअगरy_wa_lists(gt, &lists, "after reset");

out:
	reference_lists_fini(gt, &lists);
	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
	igt_global_reset_unlock(gt);

	वापस ok ? 0 : -ESRCH;
पूर्ण

अटल पूर्णांक
live_engine_reset_workarounds(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा igt_spinner spin;
	काष्ठा i915_request *rq;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा wa_lists lists;
	पूर्णांक ret = 0;

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	igt_global_reset_lock(gt);
	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);

	reference_lists_init(gt, &lists);

	क्रम_each_engine(engine, gt, id) अणु
		bool ok;

		pr_info("Verifying after %s reset...\n", engine->name);
		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			ret = PTR_ERR(ce);
			अवरोध;
		पूर्ण

		ok = verअगरy_wa_lists(gt, &lists, "before reset");
		अगर (!ok) अणु
			ret = -ESRCH;
			जाओ err;
		पूर्ण

		ret = पूर्णांकel_engine_reset(engine, "live_workarounds:idle");
		अगर (ret) अणु
			pr_err("%s: Reset failed while idle\n", engine->name);
			जाओ err;
		पूर्ण

		ok = verअगरy_wa_lists(gt, &lists, "after idle reset");
		अगर (!ok) अणु
			ret = -ESRCH;
			जाओ err;
		पूर्ण

		ret = igt_spinner_init(&spin, engine->gt);
		अगर (ret)
			जाओ err;

		rq = igt_spinner_create_request(&spin, ce, MI_NOOP);
		अगर (IS_ERR(rq)) अणु
			ret = PTR_ERR(rq);
			igt_spinner_fini(&spin);
			जाओ err;
		पूर्ण

		ret = request_add_spin(rq, &spin);
		अगर (ret) अणु
			pr_err("%s: Spinner failed to start\n", engine->name);
			igt_spinner_fini(&spin);
			जाओ err;
		पूर्ण

		ret = पूर्णांकel_engine_reset(engine, "live_workarounds:active");
		अगर (ret) अणु
			pr_err("%s: Reset failed on an active spinner\n",
			       engine->name);
			igt_spinner_fini(&spin);
			जाओ err;
		पूर्ण

		igt_spinner_end(&spin);
		igt_spinner_fini(&spin);

		ok = verअगरy_wa_lists(gt, &lists, "after busy reset");
		अगर (!ok) अणु
			ret = -ESRCH;
			जाओ err;
		पूर्ण

err:
		पूर्णांकel_context_put(ce);
		अगर (ret)
			अवरोध;
	पूर्ण

	reference_lists_fini(gt, &lists);
	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
	igt_global_reset_unlock(gt);

	igt_flush_test(gt->i915);

	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_workarounds_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_dirty_whitelist),
		SUBTEST(live_reset_whitelist),
		SUBTEST(live_isolated_whitelist),
		SUBTEST(live_gpu_reset_workarounds),
		SUBTEST(live_engine_reset_workarounds),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
