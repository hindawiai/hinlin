<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>

#समावेश "i915_selftest.h"
#समावेश "intel_engine_heartbeat.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_reset.h"
#समावेश "intel_ring.h"
#समावेश "selftest_engine_heartbeat.h"
#समावेश "selftests/i915_random.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/igt_live_test.h"
#समावेश "selftests/igt_spinner.h"
#समावेश "selftests/lib_sw_fence.h"
#समावेश "shmem_utils.h"

#समावेश "gem/selftests/igt_gem_utils.h"
#समावेश "gem/selftests/mock_context.h"

#घोषणा CS_GPR(engine, n) ((engine)->mmio_base + 0x600 + (n) * 4)
#घोषणा NUM_GPR 16
#घोषणा NUM_GPR_DW (NUM_GPR * 2) /* each GPR is 2 dwords */

अटल काष्ठा i915_vma *create_scratch(काष्ठा पूर्णांकel_gt *gt)
अणु
	वापस __vm_create_scratch_क्रम_पढ़ो_pinned(&gt->ggtt->vm, PAGE_SIZE);
पूर्ण

अटल bool is_active(काष्ठा i915_request *rq)
अणु
	अगर (i915_request_is_active(rq))
		वापस true;

	अगर (i915_request_on_hold(rq))
		वापस true;

	अगर (i915_request_has_initial_bपढ़ोcrumb(rq) && i915_request_started(rq))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक रुको_क्रम_submit(काष्ठा पूर्णांकel_engine_cs *engine,
			   काष्ठा i915_request *rq,
			   अचिन्हित दीर्घ समयout)
अणु
	/* Ignore our own attempts to suppress excess tasklets */
	tasklet_hi_schedule(&engine->execlists.tasklet);

	समयout += jअगरfies;
	करो अणु
		bool करोne = समय_after(jअगरfies, समयout);

		अगर (i915_request_completed(rq)) /* that was quick! */
			वापस 0;

		/* Wait until the HW has acknowleged the submission (or err) */
		पूर्णांकel_engine_flush_submission(engine);
		अगर (!READ_ONCE(engine->execlists.pending[0]) && is_active(rq))
			वापस 0;

		अगर (करोne)
			वापस -ETIME;

		cond_resched();
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक emit_semaphore_संकेत(काष्ठा पूर्णांकel_context *ce, व्योम *slot)
अणु
	स्थिर u32 offset =
		i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(slot);
	काष्ठा i915_request *rq;
	u32 *cs;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = 1;

	पूर्णांकel_ring_advance(rq, cs);

	rq->sched.attr.priority = I915_PRIORITY_BARRIER;
	i915_request_add(rq);
	वापस 0;
पूर्ण

अटल पूर्णांक context_flush(काष्ठा पूर्णांकel_context *ce, दीर्घ समयout)
अणु
	काष्ठा i915_request *rq;
	काष्ठा dma_fence *fence;
	पूर्णांक err = 0;

	rq = पूर्णांकel_engine_create_kernel_request(ce->engine);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	fence = i915_active_fence_get(&ce->समयline->last_request);
	अगर (fence) अणु
		i915_request_aरुको_dma_fence(rq, fence);
		dma_fence_put(fence);
	पूर्ण

	rq = i915_request_get(rq);
	i915_request_add(rq);
	अगर (i915_request_रुको(rq, 0, समयout) < 0)
		err = -ETIME;
	i915_request_put(rq);

	rmb(); /* We know the request is written, make sure all state is too! */
	वापस err;
पूर्ण

अटल पूर्णांक live_lrc_layout(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	u32 *lrc;
	पूर्णांक err;

	/*
	 * Check the रेजिस्टरs offsets we use to create the initial reg state
	 * match the layout saved by HW.
	 */

	lrc = (u32 *)__get_मुक्त_page(GFP_KERNEL); /* requires page alignment */
	अगर (!lrc)
		वापस -ENOMEM;
	GEM_BUG_ON(offset_in_page(lrc));

	err = 0;
	क्रम_each_engine(engine, gt, id) अणु
		u32 *hw;
		पूर्णांक dw;

		अगर (!engine->शेष_state)
			जारी;

		hw = shmem_pin_map(engine->शेष_state);
		अगर (IS_ERR(hw)) अणु
			err = PTR_ERR(hw);
			अवरोध;
		पूर्ण
		hw += LRC_STATE_OFFSET / माप(*hw);

		__lrc_init_regs(स_रखो(lrc, POISON_INUSE, PAGE_SIZE),
				engine->kernel_context, engine, true);

		dw = 0;
		करो अणु
			u32 lri = READ_ONCE(hw[dw]);

			अगर (lri == 0) अणु
				dw++;
				जारी;
			पूर्ण

			अगर (lrc[dw] == 0) अणु
				pr_debug("%s: skipped instruction %x at dword %d\n",
					 engine->name, lri, dw);
				dw++;
				जारी;
			पूर्ण

			अगर ((lri & GENMASK(31, 23)) != MI_INSTR(0x22, 0)) अणु
				pr_err("%s: Expected LRI command at dword %d, found %08x\n",
				       engine->name, dw, lri);
				err = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (lrc[dw] != lri) अणु
				pr_err("%s: LRI command mismatch at dword %d, expected %08x found %08x\n",
				       engine->name, dw, lri, lrc[dw]);
				err = -EINVAL;
				अवरोध;
			पूर्ण

			lri &= 0x7f;
			lri++;
			dw++;

			जबतक (lri) अणु
				u32 offset = READ_ONCE(hw[dw]);

				अगर (offset != lrc[dw]) अणु
					pr_err("%s: Different registers found at dword %d, expected %x, found %x\n",
					       engine->name, dw, offset, lrc[dw]);
					err = -EINVAL;
					अवरोध;
				पूर्ण

				/*
				 * Skip over the actual रेजिस्टर value as we
				 * expect that to dअगरfer.
				 */
				dw += 2;
				lri -= 2;
			पूर्ण
		पूर्ण जबतक (!err && (lrc[dw] & ~BIT(0)) != MI_BATCH_BUFFER_END);

		अगर (err) अणु
			pr_info("%s: HW register image:\n", engine->name);
			igt_hexdump(hw, PAGE_SIZE);

			pr_info("%s: SW register image:\n", engine->name);
			igt_hexdump(lrc, PAGE_SIZE);
		पूर्ण

		shmem_unpin_map(engine->शेष_state, hw);
		अगर (err)
			अवरोध;
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)lrc);
	वापस err;
पूर्ण

अटल पूर्णांक find_offset(स्थिर u32 *lri, u32 offset)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PAGE_SIZE / माप(u32); i++)
		अगर (lri[i] == offset)
			वापस i;

	वापस -1;
पूर्ण

अटल पूर्णांक live_lrc_fixed(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Check the assumed रेजिस्टर offsets match the actual locations in
	 * the context image.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		स्थिर काष्ठा अणु
			u32 reg;
			u32 offset;
			स्थिर अक्षर *name;
		पूर्ण tbl[] = अणु
			अणु
				i915_mmio_reg_offset(RING_START(engine->mmio_base)),
				CTX_RING_START - 1,
				"RING_START"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_CTL(engine->mmio_base)),
				CTX_RING_CTL - 1,
				"RING_CTL"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_HEAD(engine->mmio_base)),
				CTX_RING_HEAD - 1,
				"RING_HEAD"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_TAIL(engine->mmio_base)),
				CTX_RING_TAIL - 1,
				"RING_TAIL"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_MI_MODE(engine->mmio_base)),
				lrc_ring_mi_mode(engine),
				"RING_MI_MODE"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_BBSTATE(engine->mmio_base)),
				CTX_BB_STATE - 1,
				"BB_STATE"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_BB_PER_CTX_PTR(engine->mmio_base)),
				lrc_ring_wa_bb_per_ctx(engine),
				"RING_BB_PER_CTX_PTR"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_INसूचीECT_CTX(engine->mmio_base)),
				lrc_ring_indirect_ptr(engine),
				"RING_INDIRECT_CTX_PTR"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_INसूचीECT_CTX_OFFSET(engine->mmio_base)),
				lrc_ring_indirect_offset(engine),
				"RING_INDIRECT_CTX_OFFSET"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_CTX_TIMESTAMP(engine->mmio_base)),
				CTX_TIMESTAMP - 1,
				"RING_CTX_TIMESTAMP"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(GEN8_RING_CS_GPR(engine->mmio_base, 0)),
				lrc_ring_gpr0(engine),
				"RING_CS_GPR0"
			पूर्ण,
			अणु
				i915_mmio_reg_offset(RING_CMD_BUF_CCTL(engine->mmio_base)),
				lrc_ring_cmd_buf_cctl(engine),
				"RING_CMD_BUF_CCTL"
			पूर्ण,
			अणु पूर्ण,
		पूर्ण, *t;
		u32 *hw;

		अगर (!engine->शेष_state)
			जारी;

		hw = shmem_pin_map(engine->शेष_state);
		अगर (IS_ERR(hw)) अणु
			err = PTR_ERR(hw);
			अवरोध;
		पूर्ण
		hw += LRC_STATE_OFFSET / माप(*hw);

		क्रम (t = tbl; t->name; t++) अणु
			पूर्णांक dw = find_offset(hw, t->reg);

			अगर (dw != t->offset) अणु
				pr_err("%s: Offset for %s [0x%x] mismatch, found %x, expected %x\n",
				       engine->name,
				       t->name,
				       t->reg,
				       dw,
				       t->offset);
				err = -EINVAL;
			पूर्ण
		पूर्ण

		shmem_unpin_map(engine->शेष_state, hw);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __live_lrc_state(काष्ठा पूर्णांकel_engine_cs *engine,
			    काष्ठा i915_vma *scratch)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	काष्ठा i915_gem_ww_ctx ww;
	क्रमागत अणु
		RING_START_IDX = 0,
		RING_TAIL_IDX,
		MAX_IDX
	पूर्ण;
	u32 expected[MAX_IDX];
	u32 *cs;
	पूर्णांक err;
	पूर्णांक n;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	i915_gem_ww_ctx_init(&ww, false);
retry:
	err = i915_gem_object_lock(scratch->obj, &ww);
	अगर (!err)
		err = पूर्णांकel_context_pin_ww(ce, &ww);
	अगर (err)
		जाओ err_put;

	rq = i915_request_create(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_unpin;
	पूर्ण

	cs = पूर्णांकel_ring_begin(rq, 4 * MAX_IDX);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		i915_request_add(rq);
		जाओ err_unpin;
	पूर्ण

	*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_reg_offset(RING_START(engine->mmio_base));
	*cs++ = i915_ggtt_offset(scratch) + RING_START_IDX * माप(u32);
	*cs++ = 0;

	expected[RING_START_IDX] = i915_ggtt_offset(ce->ring->vma);

	*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_reg_offset(RING_TAIL(engine->mmio_base));
	*cs++ = i915_ggtt_offset(scratch) + RING_TAIL_IDX * माप(u32);
	*cs++ = 0;

	err = i915_request_aरुको_object(rq, scratch->obj, true);
	अगर (!err)
		err = i915_vma_move_to_active(scratch, rq, EXEC_OBJECT_WRITE);

	i915_request_get(rq);
	i915_request_add(rq);
	अगर (err)
		जाओ err_rq;

	पूर्णांकel_engine_flush_submission(engine);
	expected[RING_TAIL_IDX] = ce->ring->tail;

	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
		err = -ETIME;
		जाओ err_rq;
	पूर्ण

	cs = i915_gem_object_pin_map(scratch->obj, I915_MAP_WB);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_rq;
	पूर्ण

	क्रम (n = 0; n < MAX_IDX; n++) अणु
		अगर (cs[n] != expected[n]) अणु
			pr_err("%s: Stored register[%d] value[0x%x] did not match expected[0x%x]\n",
			       engine->name, n, cs[n], expected[n]);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	i915_gem_object_unpin_map(scratch->obj);

err_rq:
	i915_request_put(rq);
err_unpin:
	पूर्णांकel_context_unpin(ce);
err_put:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक live_lrc_state(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_vma *scratch;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Check the live रेजिस्टर state matches what we expect क्रम this
	 * पूर्णांकel_context.
	 */

	scratch = create_scratch(gt);
	अगर (IS_ERR(scratch))
		वापस PTR_ERR(scratch);

	क्रम_each_engine(engine, gt, id) अणु
		err = __live_lrc_state(engine, scratch);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	i915_vma_unpin_and_release(&scratch, 0);
	वापस err;
पूर्ण

अटल पूर्णांक gpr_make_dirty(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_request *rq;
	u32 *cs;
	पूर्णांक n;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	cs = पूर्णांकel_ring_begin(rq, 2 * NUM_GPR_DW + 2);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस PTR_ERR(cs);
	पूर्ण

	*cs++ = MI_LOAD_REGISTER_IMM(NUM_GPR_DW);
	क्रम (n = 0; n < NUM_GPR_DW; n++) अणु
		*cs++ = CS_GPR(ce->engine, n);
		*cs++ = STACK_MAGIC;
	पूर्ण
	*cs++ = MI_NOOP;

	पूर्णांकel_ring_advance(rq, cs);

	rq->sched.attr.priority = I915_PRIORITY_BARRIER;
	i915_request_add(rq);

	वापस 0;
पूर्ण

अटल काष्ठा i915_request *
__gpr_पढ़ो(काष्ठा पूर्णांकel_context *ce, काष्ठा i915_vma *scratch, u32 *slot)
अणु
	स्थिर u32 offset =
		i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(slot);
	काष्ठा i915_request *rq;
	u32 *cs;
	पूर्णांक err;
	पूर्णांक n;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस rq;

	cs = पूर्णांकel_ring_begin(rq, 6 + 4 * NUM_GPR_DW);
	अगर (IS_ERR(cs)) अणु
		i915_request_add(rq);
		वापस ERR_CAST(cs);
	पूर्ण

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	*cs++ = MI_NOOP;

	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_NEQ_SDD;
	*cs++ = 0;
	*cs++ = offset;
	*cs++ = 0;

	क्रम (n = 0; n < NUM_GPR_DW; n++) अणु
		*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
		*cs++ = CS_GPR(ce->engine, n);
		*cs++ = i915_ggtt_offset(scratch) + n * माप(u32);
		*cs++ = 0;
	पूर्ण

	i915_vma_lock(scratch);
	err = i915_request_aरुको_object(rq, scratch->obj, true);
	अगर (!err)
		err = i915_vma_move_to_active(scratch, rq, EXEC_OBJECT_WRITE);
	i915_vma_unlock(scratch);

	i915_request_get(rq);
	i915_request_add(rq);
	अगर (err) अणु
		i915_request_put(rq);
		rq = ERR_PTR(err);
	पूर्ण

	वापस rq;
पूर्ण

अटल पूर्णांक __live_lrc_gpr(काष्ठा पूर्णांकel_engine_cs *engine,
			  काष्ठा i915_vma *scratch,
			  bool preempt)
अणु
	u32 *slot = स_रखो32(engine->status_page.addr + 1000, 0, 4);
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	u32 *cs;
	पूर्णांक err;
	पूर्णांक n;

	अगर (INTEL_GEN(engine->i915) < 9 && engine->class != RENDER_CLASS)
		वापस 0; /* GPR only on rcs0 क्रम gen8 */

	err = gpr_make_dirty(engine->kernel_context);
	अगर (err)
		वापस err;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	rq = __gpr_पढ़ो(ce, scratch, slot);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_put;
	पूर्ण

	err = रुको_क्रम_submit(engine, rq, HZ / 2);
	अगर (err)
		जाओ err_rq;

	अगर (preempt) अणु
		err = gpr_make_dirty(engine->kernel_context);
		अगर (err)
			जाओ err_rq;

		err = emit_semaphore_संकेत(engine->kernel_context, slot);
		अगर (err)
			जाओ err_rq;

		err = रुको_क्रम_submit(engine, rq, HZ / 2);
		अगर (err)
			जाओ err_rq;
	पूर्ण अन्यथा अणु
		slot[0] = 1;
		wmb();
	पूर्ण

	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
		err = -ETIME;
		जाओ err_rq;
	पूर्ण

	cs = i915_gem_object_pin_map_unlocked(scratch->obj, I915_MAP_WB);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_rq;
	पूर्ण

	क्रम (n = 0; n < NUM_GPR_DW; n++) अणु
		अगर (cs[n]) अणु
			pr_err("%s: GPR[%d].%s was not zero, found 0x%08x!\n",
			       engine->name,
			       n / 2, n & 1 ? "udw" : "ldw",
			       cs[n]);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	i915_gem_object_unpin_map(scratch->obj);

err_rq:
	स_रखो32(&slot[0], -1, 4);
	wmb();
	i915_request_put(rq);
err_put:
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक live_lrc_gpr(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_vma *scratch;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Check that GPR रेजिस्टरs are cleared in new contexts as we need
	 * to aव्योम leaking any inक्रमmation from previous contexts.
	 */

	scratch = create_scratch(gt);
	अगर (IS_ERR(scratch))
		वापस PTR_ERR(scratch);

	क्रम_each_engine(engine, gt, id) अणु
		st_engine_heartbeat_disable(engine);

		err = __live_lrc_gpr(engine, scratch, false);
		अगर (err)
			जाओ err;

		err = __live_lrc_gpr(engine, scratch, true);
		अगर (err)
			जाओ err;

err:
		st_engine_heartbeat_enable(engine);
		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			अवरोध;
	पूर्ण

	i915_vma_unpin_and_release(&scratch, 0);
	वापस err;
पूर्ण

अटल काष्ठा i915_request *
create_बारtamp(काष्ठा पूर्णांकel_context *ce, व्योम *slot, पूर्णांक idx)
अणु
	स्थिर u32 offset =
		i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(slot);
	काष्ठा i915_request *rq;
	u32 *cs;
	पूर्णांक err;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस rq;

	cs = पूर्णांकel_ring_begin(rq, 10);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err;
	पूर्ण

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	*cs++ = MI_NOOP;

	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_NEQ_SDD;
	*cs++ = 0;
	*cs++ = offset;
	*cs++ = 0;

	*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_reg_offset(RING_CTX_TIMESTAMP(rq->engine->mmio_base));
	*cs++ = offset + idx * माप(u32);
	*cs++ = 0;

	पूर्णांकel_ring_advance(rq, cs);

	err = 0;
err:
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (err) अणु
		i915_request_put(rq);
		वापस ERR_PTR(err);
	पूर्ण

	वापस rq;
पूर्ण

काष्ठा lrc_बारtamp अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा पूर्णांकel_context *ce[2];
	u32 poison;
पूर्ण;

अटल bool बारtamp_advanced(u32 start, u32 end)
अणु
	वापस (s32)(end - start) > 0;
पूर्ण

अटल पूर्णांक __lrc_बारtamp(स्थिर काष्ठा lrc_बारtamp *arg, bool preempt)
अणु
	u32 *slot = स_रखो32(arg->engine->status_page.addr + 1000, 0, 4);
	काष्ठा i915_request *rq;
	u32 बारtamp;
	पूर्णांक err = 0;

	arg->ce[0]->lrc_reg_state[CTX_TIMESTAMP] = arg->poison;
	rq = create_बारtamp(arg->ce[0], slot, 1);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	err = रुको_क्रम_submit(rq->engine, rq, HZ / 2);
	अगर (err)
		जाओ err;

	अगर (preempt) अणु
		arg->ce[1]->lrc_reg_state[CTX_TIMESTAMP] = 0xdeadbeef;
		err = emit_semaphore_संकेत(arg->ce[1], slot);
		अगर (err)
			जाओ err;
	पूर्ण अन्यथा अणु
		slot[0] = 1;
		wmb();
	पूर्ण

	/* And रुको क्रम चयन to kernel (to save our context to memory) */
	err = context_flush(arg->ce[0], HZ / 2);
	अगर (err)
		जाओ err;

	अगर (!बारtamp_advanced(arg->poison, slot[1])) अणु
		pr_err("%s(%s): invalid timestamp on restore, context:%x, request:%x\n",
		       arg->engine->name, preempt ? "preempt" : "simple",
		       arg->poison, slot[1]);
		err = -EINVAL;
	पूर्ण

	बारtamp = READ_ONCE(arg->ce[0]->lrc_reg_state[CTX_TIMESTAMP]);
	अगर (!बारtamp_advanced(slot[1], बारtamp)) अणु
		pr_err("%s(%s): invalid timestamp on save, request:%x, context:%x\n",
		       arg->engine->name, preempt ? "preempt" : "simple",
		       slot[1], बारtamp);
		err = -EINVAL;
	पूर्ण

err:
	स_रखो32(slot, -1, 4);
	i915_request_put(rq);
	वापस err;
पूर्ण

अटल पूर्णांक live_lrc_बारtamp(व्योम *arg)
अणु
	काष्ठा lrc_बारtamp data = अणुपूर्ण;
	काष्ठा पूर्णांकel_gt *gt = arg;
	क्रमागत पूर्णांकel_engine_id id;
	स्थिर u32 poison[] = अणु
		0,
		S32_MAX,
		(u32)S32_MAX + 1,
		U32_MAX,
	पूर्ण;

	/*
	 * We want to verअगरy that the बारtamp is saved and restore across
	 * context चयनes and is monotonic.
	 *
	 * So we करो this with a little bit of LRC poisoning to check various
	 * boundary conditions, and see what happens अगर we preempt the context
	 * with a second request (carrying more poison पूर्णांकo the बारtamp).
	 */

	क्रम_each_engine(data.engine, gt, id) अणु
		पूर्णांक i, err = 0;

		st_engine_heartbeat_disable(data.engine);

		क्रम (i = 0; i < ARRAY_SIZE(data.ce); i++) अणु
			काष्ठा पूर्णांकel_context *पंचांगp;

			पंचांगp = पूर्णांकel_context_create(data.engine);
			अगर (IS_ERR(पंचांगp)) अणु
				err = PTR_ERR(पंचांगp);
				जाओ err;
			पूर्ण

			err = पूर्णांकel_context_pin(पंचांगp);
			अगर (err) अणु
				पूर्णांकel_context_put(पंचांगp);
				जाओ err;
			पूर्ण

			data.ce[i] = पंचांगp;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(poison); i++) अणु
			data.poison = poison[i];

			err = __lrc_बारtamp(&data, false);
			अगर (err)
				अवरोध;

			err = __lrc_बारtamp(&data, true);
			अगर (err)
				अवरोध;
		पूर्ण

err:
		st_engine_heartbeat_enable(data.engine);
		क्रम (i = 0; i < ARRAY_SIZE(data.ce); i++) अणु
			अगर (!data.ce[i])
				अवरोध;

			पूर्णांकel_context_unpin(data.ce[i]);
			पूर्णांकel_context_put(data.ce[i]);
		पूर्ण

		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i915_vma *
create_user_vma(काष्ठा i915_address_space *vm, अचिन्हित दीर्घ size)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(vm->i915, size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		i915_gem_object_put(obj);
		वापस vma;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err) अणु
		i915_gem_object_put(obj);
		वापस ERR_PTR(err);
	पूर्ण

	वापस vma;
पूर्ण

अटल काष्ठा i915_vma *
store_context(काष्ठा पूर्णांकel_context *ce, काष्ठा i915_vma *scratch)
अणु
	काष्ठा i915_vma *batch;
	u32 dw, x, *cs, *hw;
	u32 *शेषs;

	batch = create_user_vma(ce->vm, SZ_64K);
	अगर (IS_ERR(batch))
		वापस batch;

	cs = i915_gem_object_pin_map_unlocked(batch->obj, I915_MAP_WC);
	अगर (IS_ERR(cs)) अणु
		i915_vma_put(batch);
		वापस ERR_CAST(cs);
	पूर्ण

	शेषs = shmem_pin_map(ce->engine->शेष_state);
	अगर (!शेषs) अणु
		i915_gem_object_unpin_map(batch->obj);
		i915_vma_put(batch);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	x = 0;
	dw = 0;
	hw = शेषs;
	hw += LRC_STATE_OFFSET / माप(*hw);
	करो अणु
		u32 len = hw[dw] & 0x7f;

		अगर (hw[dw] == 0) अणु
			dw++;
			जारी;
		पूर्ण

		अगर ((hw[dw] & GENMASK(31, 23)) != MI_INSTR(0x22, 0)) अणु
			dw += len + 2;
			जारी;
		पूर्ण

		dw++;
		len = (len + 1) / 2;
		जबतक (len--) अणु
			*cs++ = MI_STORE_REGISTER_MEM_GEN8;
			*cs++ = hw[dw];
			*cs++ = lower_32_bits(scratch->node.start + x);
			*cs++ = upper_32_bits(scratch->node.start + x);

			dw += 2;
			x += 4;
		पूर्ण
	पूर्ण जबतक (dw < PAGE_SIZE / माप(u32) &&
		 (hw[dw] & ~BIT(0)) != MI_BATCH_BUFFER_END);

	*cs++ = MI_BATCH_BUFFER_END;

	shmem_unpin_map(ce->engine->शेष_state, शेषs);

	i915_gem_object_flush_map(batch->obj);
	i915_gem_object_unpin_map(batch->obj);

	वापस batch;
पूर्ण

अटल पूर्णांक move_to_active(काष्ठा i915_request *rq,
			  काष्ठा i915_vma *vma,
			  अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, flags);
	अगर (!err)
		err = i915_vma_move_to_active(vma, rq, flags);
	i915_vma_unlock(vma);

	वापस err;
पूर्ण

अटल काष्ठा i915_request *
record_रेजिस्टरs(काष्ठा पूर्णांकel_context *ce,
		 काष्ठा i915_vma *beक्रमe,
		 काष्ठा i915_vma *after,
		 u32 *sema)
अणु
	काष्ठा i915_vma *b_beक्रमe, *b_after;
	काष्ठा i915_request *rq;
	u32 *cs;
	पूर्णांक err;

	b_beक्रमe = store_context(ce, beक्रमe);
	अगर (IS_ERR(b_beक्रमe))
		वापस ERR_CAST(b_beक्रमe);

	b_after = store_context(ce, after);
	अगर (IS_ERR(b_after)) अणु
		rq = ERR_CAST(b_after);
		जाओ err_beक्रमe;
	पूर्ण

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		जाओ err_after;

	err = move_to_active(rq, beक्रमe, EXEC_OBJECT_WRITE);
	अगर (err)
		जाओ err_rq;

	err = move_to_active(rq, b_beक्रमe, 0);
	अगर (err)
		जाओ err_rq;

	err = move_to_active(rq, after, EXEC_OBJECT_WRITE);
	अगर (err)
		जाओ err_rq;

	err = move_to_active(rq, b_after, 0);
	अगर (err)
		जाओ err_rq;

	cs = पूर्णांकel_ring_begin(rq, 14);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_rq;
	पूर्ण

	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;
	*cs++ = MI_BATCH_BUFFER_START_GEN8 | BIT(8);
	*cs++ = lower_32_bits(b_beक्रमe->node.start);
	*cs++ = upper_32_bits(b_beक्रमe->node.start);

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_NEQ_SDD;
	*cs++ = 0;
	*cs++ = i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(sema);
	*cs++ = 0;
	*cs++ = MI_NOOP;

	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;
	*cs++ = MI_BATCH_BUFFER_START_GEN8 | BIT(8);
	*cs++ = lower_32_bits(b_after->node.start);
	*cs++ = upper_32_bits(b_after->node.start);

	पूर्णांकel_ring_advance(rq, cs);

	WRITE_ONCE(*sema, 0);
	i915_request_get(rq);
	i915_request_add(rq);
err_after:
	i915_vma_put(b_after);
err_beक्रमe:
	i915_vma_put(b_beक्रमe);
	वापस rq;

err_rq:
	i915_request_add(rq);
	rq = ERR_PTR(err);
	जाओ err_after;
पूर्ण

अटल काष्ठा i915_vma *load_context(काष्ठा पूर्णांकel_context *ce, u32 poison)
अणु
	काष्ठा i915_vma *batch;
	u32 dw, *cs, *hw;
	u32 *शेषs;

	batch = create_user_vma(ce->vm, SZ_64K);
	अगर (IS_ERR(batch))
		वापस batch;

	cs = i915_gem_object_pin_map_unlocked(batch->obj, I915_MAP_WC);
	अगर (IS_ERR(cs)) अणु
		i915_vma_put(batch);
		वापस ERR_CAST(cs);
	पूर्ण

	शेषs = shmem_pin_map(ce->engine->शेष_state);
	अगर (!शेषs) अणु
		i915_gem_object_unpin_map(batch->obj);
		i915_vma_put(batch);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dw = 0;
	hw = शेषs;
	hw += LRC_STATE_OFFSET / माप(*hw);
	करो अणु
		u32 len = hw[dw] & 0x7f;

		अगर (hw[dw] == 0) अणु
			dw++;
			जारी;
		पूर्ण

		अगर ((hw[dw] & GENMASK(31, 23)) != MI_INSTR(0x22, 0)) अणु
			dw += len + 2;
			जारी;
		पूर्ण

		dw++;
		len = (len + 1) / 2;
		*cs++ = MI_LOAD_REGISTER_IMM(len);
		जबतक (len--) अणु
			*cs++ = hw[dw];
			*cs++ = poison;
			dw += 2;
		पूर्ण
	पूर्ण जबतक (dw < PAGE_SIZE / माप(u32) &&
		 (hw[dw] & ~BIT(0)) != MI_BATCH_BUFFER_END);

	*cs++ = MI_BATCH_BUFFER_END;

	shmem_unpin_map(ce->engine->शेष_state, शेषs);

	i915_gem_object_flush_map(batch->obj);
	i915_gem_object_unpin_map(batch->obj);

	वापस batch;
पूर्ण

अटल पूर्णांक poison_रेजिस्टरs(काष्ठा पूर्णांकel_context *ce, u32 poison, u32 *sema)
अणु
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *batch;
	u32 *cs;
	पूर्णांक err;

	batch = load_context(ce, poison);
	अगर (IS_ERR(batch))
		वापस PTR_ERR(batch);

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_batch;
	पूर्ण

	err = move_to_active(rq, batch, 0);
	अगर (err)
		जाओ err_rq;

	cs = पूर्णांकel_ring_begin(rq, 8);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_rq;
	पूर्ण

	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;
	*cs++ = MI_BATCH_BUFFER_START_GEN8 | BIT(8);
	*cs++ = lower_32_bits(batch->node.start);
	*cs++ = upper_32_bits(batch->node.start);

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(sema);
	*cs++ = 0;
	*cs++ = 1;

	पूर्णांकel_ring_advance(rq, cs);

	rq->sched.attr.priority = I915_PRIORITY_BARRIER;
err_rq:
	i915_request_add(rq);
err_batch:
	i915_vma_put(batch);
	वापस err;
पूर्ण

अटल bool is_moving(u32 a, u32 b)
अणु
	वापस a != b;
पूर्ण

अटल पूर्णांक compare_isolation(काष्ठा पूर्णांकel_engine_cs *engine,
			     काष्ठा i915_vma *ref[2],
			     काष्ठा i915_vma *result[2],
			     काष्ठा पूर्णांकel_context *ce,
			     u32 poison)
अणु
	u32 x, dw, *hw, *lrc;
	u32 *A[2], *B[2];
	u32 *शेषs;
	पूर्णांक err = 0;

	A[0] = i915_gem_object_pin_map_unlocked(ref[0]->obj, I915_MAP_WC);
	अगर (IS_ERR(A[0]))
		वापस PTR_ERR(A[0]);

	A[1] = i915_gem_object_pin_map_unlocked(ref[1]->obj, I915_MAP_WC);
	अगर (IS_ERR(A[1])) अणु
		err = PTR_ERR(A[1]);
		जाओ err_A0;
	पूर्ण

	B[0] = i915_gem_object_pin_map_unlocked(result[0]->obj, I915_MAP_WC);
	अगर (IS_ERR(B[0])) अणु
		err = PTR_ERR(B[0]);
		जाओ err_A1;
	पूर्ण

	B[1] = i915_gem_object_pin_map_unlocked(result[1]->obj, I915_MAP_WC);
	अगर (IS_ERR(B[1])) अणु
		err = PTR_ERR(B[1]);
		जाओ err_B0;
	पूर्ण

	lrc = i915_gem_object_pin_map_unlocked(ce->state->obj,
				      i915_coherent_map_type(engine->i915));
	अगर (IS_ERR(lrc)) अणु
		err = PTR_ERR(lrc);
		जाओ err_B1;
	पूर्ण
	lrc += LRC_STATE_OFFSET / माप(*hw);

	शेषs = shmem_pin_map(ce->engine->शेष_state);
	अगर (!शेषs) अणु
		err = -ENOMEM;
		जाओ err_lrc;
	पूर्ण

	x = 0;
	dw = 0;
	hw = शेषs;
	hw += LRC_STATE_OFFSET / माप(*hw);
	करो अणु
		u32 len = hw[dw] & 0x7f;

		अगर (hw[dw] == 0) अणु
			dw++;
			जारी;
		पूर्ण

		अगर ((hw[dw] & GENMASK(31, 23)) != MI_INSTR(0x22, 0)) अणु
			dw += len + 2;
			जारी;
		पूर्ण

		dw++;
		len = (len + 1) / 2;
		जबतक (len--) अणु
			अगर (!is_moving(A[0][x], A[1][x]) &&
			    (A[0][x] != B[0][x] || A[1][x] != B[1][x])) अणु
				चयन (hw[dw] & 4095) अणु
				हाल 0x30: /* RING_HEAD */
				हाल 0x34: /* RING_TAIL */
					अवरोध;

				शेष:
					pr_err("%s[%d]: Mismatch for register %4x, default %08x, reference %08x, result (%08x, %08x), poison %08x, context %08x\n",
					       engine->name, dw,
					       hw[dw], hw[dw + 1],
					       A[0][x], B[0][x], B[1][x],
					       poison, lrc[dw + 1]);
					err = -EINVAL;
				पूर्ण
			पूर्ण
			dw += 2;
			x++;
		पूर्ण
	पूर्ण जबतक (dw < PAGE_SIZE / माप(u32) &&
		 (hw[dw] & ~BIT(0)) != MI_BATCH_BUFFER_END);

	shmem_unpin_map(ce->engine->शेष_state, शेषs);
err_lrc:
	i915_gem_object_unpin_map(ce->state->obj);
err_B1:
	i915_gem_object_unpin_map(result[1]->obj);
err_B0:
	i915_gem_object_unpin_map(result[0]->obj);
err_A1:
	i915_gem_object_unpin_map(ref[1]->obj);
err_A0:
	i915_gem_object_unpin_map(ref[0]->obj);
	वापस err;
पूर्ण

अटल पूर्णांक __lrc_isolation(काष्ठा पूर्णांकel_engine_cs *engine, u32 poison)
अणु
	u32 *sema = स_रखो32(engine->status_page.addr + 1000, 0, 1);
	काष्ठा i915_vma *ref[2], *result[2];
	काष्ठा पूर्णांकel_context *A, *B;
	काष्ठा i915_request *rq;
	पूर्णांक err;

	A = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(A))
		वापस PTR_ERR(A);

	B = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(B)) अणु
		err = PTR_ERR(B);
		जाओ err_A;
	पूर्ण

	ref[0] = create_user_vma(A->vm, SZ_64K);
	अगर (IS_ERR(ref[0])) अणु
		err = PTR_ERR(ref[0]);
		जाओ err_B;
	पूर्ण

	ref[1] = create_user_vma(A->vm, SZ_64K);
	अगर (IS_ERR(ref[1])) अणु
		err = PTR_ERR(ref[1]);
		जाओ err_ref0;
	पूर्ण

	rq = record_रेजिस्टरs(A, ref[0], ref[1], sema);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_ref1;
	पूर्ण

	WRITE_ONCE(*sema, 1);
	wmb();

	अगर (i915_request_रुको(rq, 0, HZ / 2) < 0) अणु
		i915_request_put(rq);
		err = -ETIME;
		जाओ err_ref1;
	पूर्ण
	i915_request_put(rq);

	result[0] = create_user_vma(A->vm, SZ_64K);
	अगर (IS_ERR(result[0])) अणु
		err = PTR_ERR(result[0]);
		जाओ err_ref1;
	पूर्ण

	result[1] = create_user_vma(A->vm, SZ_64K);
	अगर (IS_ERR(result[1])) अणु
		err = PTR_ERR(result[1]);
		जाओ err_result0;
	पूर्ण

	rq = record_रेजिस्टरs(A, result[0], result[1], sema);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_result1;
	पूर्ण

	err = poison_रेजिस्टरs(B, poison, sema);
	अगर (err) अणु
		WRITE_ONCE(*sema, -1);
		i915_request_put(rq);
		जाओ err_result1;
	पूर्ण

	अगर (i915_request_रुको(rq, 0, HZ / 2) < 0) अणु
		i915_request_put(rq);
		err = -ETIME;
		जाओ err_result1;
	पूर्ण
	i915_request_put(rq);

	err = compare_isolation(engine, ref, result, A, poison);

err_result1:
	i915_vma_put(result[1]);
err_result0:
	i915_vma_put(result[0]);
err_ref1:
	i915_vma_put(ref[1]);
err_ref0:
	i915_vma_put(ref[0]);
err_B:
	पूर्णांकel_context_put(B);
err_A:
	पूर्णांकel_context_put(A);
	वापस err;
पूर्ण

अटल bool skip_isolation(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (engine->class == COPY_ENGINE_CLASS && INTEL_GEN(engine->i915) == 9)
		वापस true;

	अगर (engine->class == RENDER_CLASS && INTEL_GEN(engine->i915) == 11)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक live_lrc_isolation(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	स्थिर u32 poison[] = अणु
		STACK_MAGIC,
		0x3a3a3a3a,
		0x5c5c5c5c,
		0xffffffff,
		0xffff0000,
	पूर्ण;
	पूर्णांक err = 0;

	/*
	 * Our goal is try and verअगरy that per-context state cannot be
	 * tampered with by another non-privileged client.
	 *
	 * We take the list of context रेजिस्टरs from the LRI in the शेष
	 * context image and attempt to modअगरy that list from a remote context.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		पूर्णांक i;

		/* Just करोn't even ask */
		अगर (!IS_ENABLED(CONFIG_DRM_I915_SELFTEST_BROKEN) &&
		    skip_isolation(engine))
			जारी;

		पूर्णांकel_engine_pm_get(engine);
		क्रम (i = 0; i < ARRAY_SIZE(poison); i++) अणु
			पूर्णांक result;

			result = __lrc_isolation(engine, poison[i]);
			अगर (result && !err)
				err = result;

			result = __lrc_isolation(engine, ~poison[i]);
			अगर (result && !err)
				err = result;
		पूर्ण
		पूर्णांकel_engine_pm_put(engine);
		अगर (igt_flush_test(gt->i915)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक indirect_ctx_submit_req(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err = 0;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	i915_request_get(rq);
	i915_request_add(rq);

	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
		err = -ETIME;

	i915_request_put(rq);

	वापस err;
पूर्ण

#घोषणा CTX_BB_CANARY_OFFSET (3 * 1024)
#घोषणा CTX_BB_CANARY_INDEX  (CTX_BB_CANARY_OFFSET / माप(u32))

अटल u32 *
emit_indirect_ctx_bb_canary(स्थिर काष्ठा पूर्णांकel_context *ce, u32 *cs)
अणु
	*cs++ = MI_STORE_REGISTER_MEM_GEN8 |
		MI_SRM_LRM_GLOBAL_GTT |
		MI_LRI_LRM_CS_MMIO;
	*cs++ = i915_mmio_reg_offset(RING_START(0));
	*cs++ = i915_ggtt_offset(ce->state) +
		context_wa_bb_offset(ce) +
		CTX_BB_CANARY_OFFSET;
	*cs++ = 0;

	वापस cs;
पूर्ण

अटल व्योम
indirect_ctx_bb_setup(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 *cs = context_indirect_bb(ce);

	cs[CTX_BB_CANARY_INDEX] = 0xdeadf00d;

	setup_indirect_ctx_bb(ce, ce->engine, emit_indirect_ctx_bb_canary);
पूर्ण

अटल bool check_ring_start(काष्ठा पूर्णांकel_context *ce)
अणु
	स्थिर u32 * स्थिर ctx_bb = (व्योम *)(ce->lrc_reg_state) -
		LRC_STATE_OFFSET + context_wa_bb_offset(ce);

	अगर (ctx_bb[CTX_BB_CANARY_INDEX] == ce->lrc_reg_state[CTX_RING_START])
		वापस true;

	pr_err("ring start mismatch: canary 0x%08x vs state 0x%08x\n",
	       ctx_bb[CTX_BB_CANARY_INDEX],
	       ce->lrc_reg_state[CTX_RING_START]);

	वापस false;
पूर्ण

अटल पूर्णांक indirect_ctx_bb_check(काष्ठा पूर्णांकel_context *ce)
अणु
	पूर्णांक err;

	err = indirect_ctx_submit_req(ce);
	अगर (err)
		वापस err;

	अगर (!check_ring_start(ce))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __live_lrc_indirect_ctx_bb(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *a, *b;
	पूर्णांक err;

	a = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(a))
		वापस PTR_ERR(a);
	err = पूर्णांकel_context_pin(a);
	अगर (err)
		जाओ put_a;

	b = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(b)) अणु
		err = PTR_ERR(b);
		जाओ unpin_a;
	पूर्ण
	err = पूर्णांकel_context_pin(b);
	अगर (err)
		जाओ put_b;

	/* We use the alपढ़ोy reserved extra page in context state */
	अगर (!a->wa_bb_page) अणु
		GEM_BUG_ON(b->wa_bb_page);
		GEM_BUG_ON(INTEL_GEN(engine->i915) == 12);
		जाओ unpin_b;
	पूर्ण

	/*
	 * In order to test that our per context bb is truly per context,
	 * and executes at the पूर्णांकended spot on context restoring process,
	 * make the batch store the ring start value to memory.
	 * As ring start is restored apriori of starting the indirect ctx bb and
	 * as it will be dअगरferent क्रम each context, it fits to this purpose.
	 */
	indirect_ctx_bb_setup(a);
	indirect_ctx_bb_setup(b);

	err = indirect_ctx_bb_check(a);
	अगर (err)
		जाओ unpin_b;

	err = indirect_ctx_bb_check(b);

unpin_b:
	पूर्णांकel_context_unpin(b);
put_b:
	पूर्णांकel_context_put(b);
unpin_a:
	पूर्णांकel_context_unpin(a);
put_a:
	पूर्णांकel_context_put(a);

	वापस err;
पूर्ण

अटल पूर्णांक live_lrc_indirect_ctx_bb(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	क्रम_each_engine(engine, gt, id) अणु
		पूर्णांकel_engine_pm_get(engine);
		err = __live_lrc_indirect_ctx_bb(engine);
		पूर्णांकel_engine_pm_put(engine);

		अगर (igt_flush_test(gt->i915))
			err = -EIO;

		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम garbage_reset(काष्ठा पूर्णांकel_engine_cs *engine,
			  काष्ठा i915_request *rq)
अणु
	स्थिर अचिन्हित पूर्णांक bit = I915_RESET_ENGINE + engine->id;
	अचिन्हित दीर्घ *lock = &engine->gt->reset.flags;

	local_bh_disable();
	अगर (!test_and_set_bit(bit, lock)) अणु
		tasklet_disable(&engine->execlists.tasklet);

		अगर (!rq->fence.error)
			__पूर्णांकel_engine_reset_bh(engine, शून्य);

		tasklet_enable(&engine->execlists.tasklet);
		clear_and_wake_up_bit(bit, lock);
	पूर्ण
	local_bh_enable();
पूर्ण

अटल काष्ठा i915_request *garbage(काष्ठा पूर्णांकel_context *ce,
				    काष्ठा rnd_state *prng)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	err = पूर्णांकel_context_pin(ce);
	अगर (err)
		वापस ERR_PTR(err);

	pअक्रमom_bytes_state(prng,
			    ce->lrc_reg_state,
			    ce->engine->context_size -
			    LRC_STATE_OFFSET);

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_unpin;
	पूर्ण

	i915_request_get(rq);
	i915_request_add(rq);
	वापस rq;

err_unpin:
	पूर्णांकel_context_unpin(ce);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक __lrc_garbage(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा rnd_state *prng)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *hang;
	पूर्णांक err = 0;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	hang = garbage(ce, prng);
	अगर (IS_ERR(hang)) अणु
		err = PTR_ERR(hang);
		जाओ err_ce;
	पूर्ण

	अगर (रुको_क्रम_submit(engine, hang, HZ / 2)) अणु
		i915_request_put(hang);
		err = -ETIME;
		जाओ err_ce;
	पूर्ण

	पूर्णांकel_context_set_banned(ce);
	garbage_reset(engine, hang);

	पूर्णांकel_engine_flush_submission(engine);
	अगर (!hang->fence.error) अणु
		i915_request_put(hang);
		pr_err("%s: corrupted context was not reset\n",
		       engine->name);
		err = -EINVAL;
		जाओ err_ce;
	पूर्ण

	अगर (i915_request_रुको(hang, 0, HZ / 2) < 0) अणु
		pr_err("%s: corrupted context did not recover\n",
		       engine->name);
		i915_request_put(hang);
		err = -EIO;
		जाओ err_ce;
	पूर्ण
	i915_request_put(hang);

err_ce:
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक live_lrc_garbage(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * Verअगरy that we can recover अगर one context state is completely
	 * corrupted.
	 */

	अगर (!IS_ENABLED(CONFIG_DRM_I915_SELFTEST_BROKEN))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		I915_RND_STATE(prng);
		पूर्णांक err = 0, i;

		अगर (!पूर्णांकel_has_reset_engine(engine->gt))
			जारी;

		पूर्णांकel_engine_pm_get(engine);
		क्रम (i = 0; i < 3; i++) अणु
			err = __lrc_garbage(engine, &prng);
			अगर (err)
				अवरोध;
		पूर्ण
		पूर्णांकel_engine_pm_put(engine);

		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __live_pphwsp_runसमय(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	IGT_TIMEOUT(end_समय);
	पूर्णांक err;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	ce->runसमय.num_underflow = 0;
	ce->runसमय.max_underflow = 0;

	करो अणु
		अचिन्हित पूर्णांक loop = 1024;

		जबतक (loop) अणु
			rq = पूर्णांकel_context_create_request(ce);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				जाओ err_rq;
			पूर्ण

			अगर (--loop == 0)
				i915_request_get(rq);

			i915_request_add(rq);
		पूर्ण

		अगर (__igt_समयout(end_समय, शून्य))
			अवरोध;

		i915_request_put(rq);
	पूर्ण जबतक (1);

	err = i915_request_रुको(rq, 0, HZ / 5);
	अगर (err < 0) अणु
		pr_err("%s: request not completed!\n", engine->name);
		जाओ err_रुको;
	पूर्ण

	igt_flush_test(engine->i915);

	pr_info("%s: pphwsp runtime %lluns, average %lluns\n",
		engine->name,
		पूर्णांकel_context_get_total_runसमय_ns(ce),
		पूर्णांकel_context_get_avg_runसमय_ns(ce));

	err = 0;
	अगर (ce->runसमय.num_underflow) अणु
		pr_err("%s: pphwsp underflow %u time(s), max %u cycles!\n",
		       engine->name,
		       ce->runसमय.num_underflow,
		       ce->runसमय.max_underflow);
		GEM_TRACE_DUMP();
		err = -EOVERFLOW;
	पूर्ण

err_रुको:
	i915_request_put(rq);
err_rq:
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक live_pphwsp_runसमय(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Check that cumulative context runसमय as stored in the pphwsp[16]
	 * is monotonic.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		err = __live_pphwsp_runसमय(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_lrc_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_lrc_layout),
		SUBTEST(live_lrc_fixed),
		SUBTEST(live_lrc_state),
		SUBTEST(live_lrc_gpr),
		SUBTEST(live_lrc_isolation),
		SUBTEST(live_lrc_बारtamp),
		SUBTEST(live_lrc_garbage),
		SUBTEST(live_pphwsp_runसमय),
		SUBTEST(live_lrc_indirect_ctx_bb),
	पूर्ण;

	अगर (!HAS_LOGICAL_RING_CONTEXTS(i915))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
