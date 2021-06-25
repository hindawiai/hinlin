<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "debugfs_gt.h"

#समावेश "gem/i915_gem_lmem.h"
#समावेश "i915_drv.h"
#समावेश "intel_context.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_buffer_pool.h"
#समावेश "intel_gt_clock_utils.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_gt_requests.h"
#समावेश "intel_mocs.h"
#समावेश "intel_rc6.h"
#समावेश "intel_renderstate.h"
#समावेश "intel_rps.h"
#समावेश "intel_uncore.h"
#समावेश "intel_pm.h"
#समावेश "shmem_utils.h"

व्योम पूर्णांकel_gt_init_early(काष्ठा पूर्णांकel_gt *gt, काष्ठा drm_i915_निजी *i915)
अणु
	gt->i915 = i915;
	gt->uncore = &i915->uncore;

	spin_lock_init(&gt->irq_lock);

	INIT_LIST_HEAD(&gt->बंदd_vma);
	spin_lock_init(&gt->बंदd_lock);

	init_llist_head(&gt->watchकरोg.list);
	INIT_WORK(&gt->watchकरोg.work, पूर्णांकel_gt_watchकरोg_work);

	पूर्णांकel_gt_init_buffer_pool(gt);
	पूर्णांकel_gt_init_reset(gt);
	पूर्णांकel_gt_init_requests(gt);
	पूर्णांकel_gt_init_समयlines(gt);
	पूर्णांकel_gt_pm_init_early(gt);

	पूर्णांकel_rps_init_early(&gt->rps);
	पूर्णांकel_uc_init_early(&gt->uc);
पूर्ण

पूर्णांक पूर्णांकel_gt_probe_lmem(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_memory_region *mem;
	पूर्णांक id;
	पूर्णांक err;

	mem = पूर्णांकel_gt_setup_lmem(gt);
	अगर (mem == ERR_PTR(-ENODEV))
		mem = पूर्णांकel_gt_setup_fake_lmem(gt);
	अगर (IS_ERR(mem)) अणु
		err = PTR_ERR(mem);
		अगर (err == -ENODEV)
			वापस 0;

		drm_err(&i915->drm,
			"Failed to setup region(%d) type=%d\n",
			err, INTEL_MEMORY_LOCAL);
		वापस err;
	पूर्ण

	id = INTEL_REGION_LMEM;

	mem->id = id;
	mem->type = INTEL_MEMORY_LOCAL;
	mem->instance = 0;

	पूर्णांकel_memory_region_set_name(mem, "local%u", mem->instance);

	GEM_BUG_ON(!HAS_REGION(i915, id));
	GEM_BUG_ON(i915->mm.regions[id]);
	i915->mm.regions[id] = mem;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_gt_init_hw_early(काष्ठा पूर्णांकel_gt *gt, काष्ठा i915_ggtt *ggtt)
अणु
	gt->ggtt = ggtt;
पूर्ण

पूर्णांक पूर्णांकel_gt_init_mmio(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_gt_init_घड़ी_frequency(gt);

	पूर्णांकel_uc_init_mmio(&gt->uc);
	पूर्णांकel_sseu_info_init(gt);

	वापस पूर्णांकel_engines_init_mmio(gt);
पूर्ण

अटल व्योम init_unused_ring(काष्ठा पूर्णांकel_gt *gt, u32 base)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	पूर्णांकel_uncore_ग_लिखो(uncore, RING_CTL(base), 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, RING_HEAD(base), 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, RING_TAIL(base), 0);
	पूर्णांकel_uncore_ग_लिखो(uncore, RING_START(base), 0);
पूर्ण

अटल व्योम init_unused_rings(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	अगर (IS_I830(i915)) अणु
		init_unused_ring(gt, PRB1_BASE);
		init_unused_ring(gt, SRB0_BASE);
		init_unused_ring(gt, SRB1_BASE);
		init_unused_ring(gt, SRB2_BASE);
		init_unused_ring(gt, SRB3_BASE);
	पूर्ण अन्यथा अगर (IS_GEN(i915, 2)) अणु
		init_unused_ring(gt, SRB0_BASE);
		init_unused_ring(gt, SRB1_BASE);
	पूर्ण अन्यथा अगर (IS_GEN(i915, 3)) अणु
		init_unused_ring(gt, PRB1_BASE);
		init_unused_ring(gt, PRB2_BASE);
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_gt_init_hw(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	पूर्णांक ret;

	gt->last_init_समय = kसमय_get();

	/* Double layer security blanket, see i915_gem_init() */
	पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);

	अगर (HAS_EDRAM(i915) && INTEL_GEN(i915) < 9)
		पूर्णांकel_uncore_rmw(uncore, HSW_IDICR, 0, IDIHASHMSK(0xf));

	अगर (IS_HASWELL(i915))
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   MI_PREDICATE_RESULT_2,
				   IS_HSW_GT3(i915) ?
				   LOWER_SLICE_ENABLED : LOWER_SLICE_DISABLED);

	/* Apply the GT workarounds... */
	पूर्णांकel_gt_apply_workarounds(gt);
	/* ...and determine whether they are sticking. */
	पूर्णांकel_gt_verअगरy_workarounds(gt, "init");

	पूर्णांकel_gt_init_swizzling(gt);

	/*
	 * At least 830 can leave some of the unused rings
	 * "active" (ie. head != tail) after resume which
	 * will prevent c3 entry. Makes sure all unused rings
	 * are totally idle.
	 */
	init_unused_rings(gt);

	ret = i915_ppgtt_init_hw(gt);
	अगर (ret) अणु
		DRM_ERROR("Enabling PPGTT failed (%d)\n", ret);
		जाओ out;
	पूर्ण

	/* We can't enable contexts until all firmware is loaded */
	ret = पूर्णांकel_uc_init_hw(&gt->uc);
	अगर (ret) अणु
		i915_probe_error(i915, "Enabling uc failed (%d)\n", ret);
		जाओ out;
	पूर्ण

	पूर्णांकel_mocs_init(gt);

out:
	पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);
	वापस ret;
पूर्ण

अटल व्योम rmw_set(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u32 set)
अणु
	पूर्णांकel_uncore_rmw(uncore, reg, 0, set);
पूर्ण

अटल व्योम rmw_clear(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u32 clr)
अणु
	पूर्णांकel_uncore_rmw(uncore, reg, clr, 0);
पूर्ण

अटल व्योम clear_रेजिस्टर(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg)
अणु
	पूर्णांकel_uncore_rmw(uncore, reg, 0, 0);
पूर्ण

अटल व्योम gen8_clear_engine_error_रेजिस्टर(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	GEN6_RING_FAULT_REG_RMW(engine, RING_FAULT_VALID, 0);
	GEN6_RING_FAULT_REG_POSTING_READ(engine);
पूर्ण

व्योम
पूर्णांकel_gt_clear_error_रेजिस्टरs(काष्ठा पूर्णांकel_gt *gt,
			       पूर्णांकel_engine_mask_t engine_mask)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 eir;

	अगर (!IS_GEN(i915, 2))
		clear_रेजिस्टर(uncore, PGTBL_ER);

	अगर (INTEL_GEN(i915) < 4)
		clear_रेजिस्टर(uncore, IPEIR(RENDER_RING_BASE));
	अन्यथा
		clear_रेजिस्टर(uncore, IPEIR_I965);

	clear_रेजिस्टर(uncore, EIR);
	eir = पूर्णांकel_uncore_पढ़ो(uncore, EIR);
	अगर (eir) अणु
		/*
		 * some errors might have become stuck,
		 * mask them.
		 */
		DRM_DEBUG_DRIVER("EIR stuck: 0x%08x, masking\n", eir);
		rmw_set(uncore, EMR, eir);
		पूर्णांकel_uncore_ग_लिखो(uncore, GEN2_IIR,
				   I915_MASTER_ERROR_INTERRUPT);
	पूर्ण

	अगर (INTEL_GEN(i915) >= 12) अणु
		rmw_clear(uncore, GEN12_RING_FAULT_REG, RING_FAULT_VALID);
		पूर्णांकel_uncore_posting_पढ़ो(uncore, GEN12_RING_FAULT_REG);
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
		rmw_clear(uncore, GEN8_RING_FAULT_REG, RING_FAULT_VALID);
		पूर्णांकel_uncore_posting_पढ़ो(uncore, GEN8_RING_FAULT_REG);
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 6) अणु
		काष्ठा पूर्णांकel_engine_cs *engine;
		क्रमागत पूर्णांकel_engine_id id;

		क्रम_each_engine_masked(engine, gt, engine_mask, id)
			gen8_clear_engine_error_रेजिस्टर(engine);
	पूर्ण
पूर्ण

अटल व्योम gen6_check_faults(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	u32 fault;

	क्रम_each_engine(engine, gt, id) अणु
		fault = GEN6_RING_FAULT_REG_READ(engine);
		अगर (fault & RING_FAULT_VALID) अणु
			drm_dbg(&engine->i915->drm, "Unexpected fault\n"
				"\tAddr: 0x%08lx\n"
				"\tAddress space: %s\n"
				"\tSource ID: %d\n"
				"\tType: %d\n",
				fault & PAGE_MASK,
				fault & RING_FAULT_GTTSEL_MASK ?
				"GGTT" : "PPGTT",
				RING_FAULT_SRCID(fault),
				RING_FAULT_FAULT_TYPE(fault));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gen8_check_faults(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	i915_reg_t fault_reg, fault_data0_reg, fault_data1_reg;
	u32 fault;

	अगर (INTEL_GEN(gt->i915) >= 12) अणु
		fault_reg = GEN12_RING_FAULT_REG;
		fault_data0_reg = GEN12_FAULT_TLB_DATA0;
		fault_data1_reg = GEN12_FAULT_TLB_DATA1;
	पूर्ण अन्यथा अणु
		fault_reg = GEN8_RING_FAULT_REG;
		fault_data0_reg = GEN8_FAULT_TLB_DATA0;
		fault_data1_reg = GEN8_FAULT_TLB_DATA1;
	पूर्ण

	fault = पूर्णांकel_uncore_पढ़ो(uncore, fault_reg);
	अगर (fault & RING_FAULT_VALID) अणु
		u32 fault_data0, fault_data1;
		u64 fault_addr;

		fault_data0 = पूर्णांकel_uncore_पढ़ो(uncore, fault_data0_reg);
		fault_data1 = पूर्णांकel_uncore_पढ़ो(uncore, fault_data1_reg);

		fault_addr = ((u64)(fault_data1 & FAULT_VA_HIGH_BITS) << 44) |
			     ((u64)fault_data0 << 12);

		drm_dbg(&uncore->i915->drm, "Unexpected fault\n"
			"\tAddr: 0x%08x_%08x\n"
			"\tAddress space: %s\n"
			"\tEngine ID: %d\n"
			"\tSource ID: %d\n"
			"\tType: %d\n",
			upper_32_bits(fault_addr), lower_32_bits(fault_addr),
			fault_data1 & FAULT_GTT_SEL ? "GGTT" : "PPGTT",
			GEN8_RING_FAULT_ENGINE_ID(fault),
			RING_FAULT_SRCID(fault),
			RING_FAULT_FAULT_TYPE(fault));
	पूर्ण
पूर्ण

व्योम पूर्णांकel_gt_check_and_clear_faults(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	/* From GEN8 onwards we only have one 'All Engine Fault Register' */
	अगर (INTEL_GEN(i915) >= 8)
		gen8_check_faults(gt);
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		gen6_check_faults(gt);
	अन्यथा
		वापस;

	पूर्णांकel_gt_clear_error_रेजिस्टरs(gt, ALL_ENGINES);
पूर्ण

व्योम पूर्णांकel_gt_flush_ggtt_ग_लिखोs(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	पूर्णांकel_wakeref_t wakeref;

	/*
	 * No actual flushing is required क्रम the GTT ग_लिखो करोमुख्य क्रम पढ़ोs
	 * from the GTT करोमुख्य. Writes to it "immediately" go to मुख्य memory
	 * as far as we know, so there's no chipset flush. It also doesn't
	 * land in the GPU render cache.
	 *
	 * However, we करो have to enक्रमce the order so that all ग_लिखोs through
	 * the GTT land beक्रमe any ग_लिखोs to the device, such as updates to
	 * the GATT itself.
	 *
	 * We also have to रुको a bit क्रम the ग_लिखोs to land from the GTT.
	 * An uncached पढ़ो (i.e. mmio) seems to be ideal क्रम the round-trip
	 * timing. This issue has only been observed when चयनing quickly
	 * between GTT ग_लिखोs and CPU पढ़ोs from inside the kernel on recent hw,
	 * and it appears to only affect discrete GTT blocks (i.e. on LLC
	 * प्रणाली agents we cannot reproduce this behaviour, until Cannonlake
	 * that was!).
	 */

	wmb();

	अगर (INTEL_INFO(gt->i915)->has_coherent_ggtt)
		वापस;

	पूर्णांकel_gt_chipset_flush(gt);

	with_पूर्णांकel_runसमय_pm_अगर_in_use(uncore->rpm, wakeref) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&uncore->lock, flags);
		पूर्णांकel_uncore_posting_पढ़ो_fw(uncore,
					     RING_HEAD(RENDER_RING_BASE));
		spin_unlock_irqrestore(&uncore->lock, flags);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_gt_chipset_flush(काष्ठा पूर्णांकel_gt *gt)
अणु
	wmb();
	अगर (INTEL_GEN(gt->i915) < 6)
		पूर्णांकel_gtt_chipset_flush();
पूर्ण

व्योम पूर्णांकel_gt_driver_रेजिस्टर(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_rps_driver_रेजिस्टर(&gt->rps);

	debugfs_gt_रेजिस्टर(gt);
पूर्ण

अटल पूर्णांक पूर्णांकel_gt_init_scratch(काष्ठा पूर्णांकel_gt *gt, अचिन्हित पूर्णांक size)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक ret;

	obj = i915_gem_object_create_lmem(i915, size, I915_BO_ALLOC_VOLATILE);
	अगर (IS_ERR(obj))
		obj = i915_gem_object_create_stolen(i915, size);
	अगर (IS_ERR(obj))
		obj = i915_gem_object_create_पूर्णांकernal(i915, size);
	अगर (IS_ERR(obj)) अणु
		drm_err(&i915->drm, "Failed to allocate scratch page\n");
		वापस PTR_ERR(obj);
	पूर्ण

	vma = i915_vma_instance(obj, &gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ err_unref;
	पूर्ण

	ret = i915_ggtt_pin(vma, शून्य, 0, PIN_HIGH);
	अगर (ret)
		जाओ err_unref;

	gt->scratch = i915_vma_make_unshrinkable(vma);

	वापस 0;

err_unref:
	i915_gem_object_put(obj);
	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_gt_fini_scratch(काष्ठा पूर्णांकel_gt *gt)
अणु
	i915_vma_unpin_and_release(&gt->scratch, 0);
पूर्ण

अटल काष्ठा i915_address_space *kernel_vm(काष्ठा पूर्णांकel_gt *gt)
अणु
	अगर (INTEL_PPGTT(gt->i915) > INTEL_PPGTT_ALIASING)
		वापस &i915_ppgtt_create(gt)->vm;
	अन्यथा
		वापस i915_vm_get(&gt->ggtt->vm);
पूर्ण

अटल पूर्णांक __engines_record_शेषs(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा i915_request *requests[I915_NUM_ENGINES] = अणुपूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * As we reset the gpu during very early sanitisation, the current
	 * रेजिस्टर state on the GPU should reflect its शेषs values.
	 * We load a context onto the hw (with restore-inhibit), then चयन
	 * over to a second context to save that शेष रेजिस्टर state. We
	 * can then prime every new context with that state so they all start
	 * from the same शेष HW values.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_renderstate so;
		काष्ठा पूर्णांकel_context *ce;
		काष्ठा i915_request *rq;

		/* We must be able to चयन to something! */
		GEM_BUG_ON(!engine->kernel_context);

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			जाओ out;
		पूर्ण

		err = पूर्णांकel_renderstate_init(&so, ce);
		अगर (err)
			जाओ err;

		rq = i915_request_create(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_fini;
		पूर्ण

		err = पूर्णांकel_engine_emit_ctx_wa(rq);
		अगर (err)
			जाओ err_rq;

		err = पूर्णांकel_renderstate_emit(&so, rq);
		अगर (err)
			जाओ err_rq;

err_rq:
		requests[id] = i915_request_get(rq);
		i915_request_add(rq);
err_fini:
		पूर्णांकel_renderstate_fini(&so, ce);
err:
		अगर (err) अणु
			पूर्णांकel_context_put(ce);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Flush the शेष context image to memory, and enable घातersaving. */
	अगर (पूर्णांकel_gt_रुको_क्रम_idle(gt, I915_GEM_IDLE_TIMEOUT) == -ETIME) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	क्रम (id = 0; id < ARRAY_SIZE(requests); id++) अणु
		काष्ठा i915_request *rq;
		काष्ठा file *state;

		rq = requests[id];
		अगर (!rq)
			जारी;

		अगर (rq->fence.error) अणु
			err = -EIO;
			जाओ out;
		पूर्ण

		GEM_BUG_ON(!test_bit(CONTEXT_ALLOC_BIT, &rq->context->flags));
		अगर (!rq->context->state)
			जारी;

		/* Keep a copy of the state's backing pages; मुक्त the obj */
		state = shmem_create_from_object(rq->context->state->obj);
		अगर (IS_ERR(state)) अणु
			err = PTR_ERR(state);
			जाओ out;
		पूर्ण
		rq->engine->शेष_state = state;
	पूर्ण

out:
	/*
	 * If we have to abanकरोn now, we expect the engines to be idle
	 * and पढ़ोy to be torn-करोwn. The quickest way we can accomplish
	 * this is by declaring ourselves wedged.
	 */
	अगर (err)
		पूर्णांकel_gt_set_wedged(gt);

	क्रम (id = 0; id < ARRAY_SIZE(requests); id++) अणु
		काष्ठा पूर्णांकel_context *ce;
		काष्ठा i915_request *rq;

		rq = requests[id];
		अगर (!rq)
			जारी;

		ce = rq->context;
		i915_request_put(rq);
		पूर्णांकel_context_put(ce);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __engines_verअगरy_workarounds(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	अगर (!IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		अगर (पूर्णांकel_engine_verअगरy_workarounds(engine, "load"))
			err = -EIO;
	पूर्ण

	/* Flush and restore the kernel context क्रम safety */
	अगर (पूर्णांकel_gt_रुको_क्रम_idle(gt, I915_GEM_IDLE_TIMEOUT) == -ETIME)
		err = -EIO;

	वापस err;
पूर्ण

अटल व्योम __पूर्णांकel_gt_disable(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_gt_set_wedged_on_fini(gt);

	पूर्णांकel_gt_suspend_prepare(gt);
	पूर्णांकel_gt_suspend_late(gt);

	GEM_BUG_ON(पूर्णांकel_gt_pm_is_awake(gt));
पूर्ण

पूर्णांक पूर्णांकel_gt_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांक err;

	err = i915_inject_probe_error(gt->i915, -ENODEV);
	अगर (err)
		वापस err;

	/*
	 * This is just a security blanket to placate dragons.
	 * On some प्रणालीs, we very sporadically observe that the first TLBs
	 * used by the CS may be stale, despite us poking the TLB reset. If
	 * we hold the क्रमcewake during initialisation these problems
	 * just magically go away.
	 */
	पूर्णांकel_uncore_क्रमcewake_get(gt->uncore, FORCEWAKE_ALL);

	err = पूर्णांकel_gt_init_scratch(gt, IS_GEN(gt->i915, 2) ? SZ_256K : SZ_4K);
	अगर (err)
		जाओ out_fw;

	पूर्णांकel_gt_pm_init(gt);

	gt->vm = kernel_vm(gt);
	अगर (!gt->vm) अणु
		err = -ENOMEM;
		जाओ err_pm;
	पूर्ण

	err = पूर्णांकel_engines_init(gt);
	अगर (err)
		जाओ err_engines;

	err = पूर्णांकel_uc_init(&gt->uc);
	अगर (err)
		जाओ err_engines;

	err = पूर्णांकel_gt_resume(gt);
	अगर (err)
		जाओ err_uc_init;

	err = __engines_record_शेषs(gt);
	अगर (err)
		जाओ err_gt;

	err = __engines_verअगरy_workarounds(gt);
	अगर (err)
		जाओ err_gt;

	err = i915_inject_probe_error(gt->i915, -EIO);
	अगर (err)
		जाओ err_gt;

	जाओ out_fw;
err_gt:
	__पूर्णांकel_gt_disable(gt);
	पूर्णांकel_uc_fini_hw(&gt->uc);
err_uc_init:
	पूर्णांकel_uc_fini(&gt->uc);
err_engines:
	पूर्णांकel_engines_release(gt);
	i915_vm_put(fetch_and_zero(&gt->vm));
err_pm:
	पूर्णांकel_gt_pm_fini(gt);
	पूर्णांकel_gt_fini_scratch(gt);
out_fw:
	अगर (err)
		पूर्णांकel_gt_set_wedged_on_init(gt);
	पूर्णांकel_uncore_क्रमcewake_put(gt->uncore, FORCEWAKE_ALL);
	वापस err;
पूर्ण

व्योम पूर्णांकel_gt_driver_हटाओ(काष्ठा पूर्णांकel_gt *gt)
अणु
	__पूर्णांकel_gt_disable(gt);

	पूर्णांकel_uc_driver_हटाओ(&gt->uc);

	पूर्णांकel_engines_release(gt);
पूर्ण

व्योम पूर्णांकel_gt_driver_unरेजिस्टर(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_wakeref_t wakeref;

	पूर्णांकel_rps_driver_unरेजिस्टर(&gt->rps);

	/*
	 * Upon unरेजिस्टरing the device to prevent any new users, cancel
	 * all in-flight requests so that we can quickly unbind the active
	 * resources.
	 */
	पूर्णांकel_gt_set_wedged(gt);

	/* Scrub all HW state upon release */
	with_पूर्णांकel_runसमय_pm(gt->uncore->rpm, wakeref)
		__पूर्णांकel_gt_reset(gt, ALL_ENGINES);
पूर्ण

व्योम पूर्णांकel_gt_driver_release(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा i915_address_space *vm;

	vm = fetch_and_zero(&gt->vm);
	अगर (vm) /* FIXME being called twice on error paths :( */
		i915_vm_put(vm);

	पूर्णांकel_gt_pm_fini(gt);
	पूर्णांकel_gt_fini_scratch(gt);
	पूर्णांकel_gt_fini_buffer_pool(gt);
पूर्ण

व्योम पूर्णांकel_gt_driver_late_release(काष्ठा पूर्णांकel_gt *gt)
अणु
	/* We need to रुको क्रम inflight RCU मुक्तs to release their grip */
	rcu_barrier();

	पूर्णांकel_uc_driver_late_release(&gt->uc);
	पूर्णांकel_gt_fini_requests(gt);
	पूर्णांकel_gt_fini_reset(gt);
	पूर्णांकel_gt_fini_समयlines(gt);
	पूर्णांकel_engines_मुक्त(gt);
पूर्ण

व्योम पूर्णांकel_gt_info_prपूर्णांक(स्थिर काष्ठा पूर्णांकel_gt_info *info,
			 काष्ठा drm_prपूर्णांकer *p)
अणु
	drm_म_लिखो(p, "available engines: %x\n", info->engine_mask);

	पूर्णांकel_sseu_dump(&info->sseu, p);
पूर्ण
