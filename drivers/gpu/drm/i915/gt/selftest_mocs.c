<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "i915_selftest.h"

#समावेश "gem/selftests/mock_context.h"
#समावेश "selftests/igt_reset.h"
#समावेश "selftests/igt_spinner.h"

काष्ठा live_mocs अणु
	काष्ठा drm_i915_mocs_table table;
	काष्ठा drm_i915_mocs_table *mocs;
	काष्ठा drm_i915_mocs_table *l3cc;
	काष्ठा i915_vma *scratch;
	व्योम *vaddr;
पूर्ण;

अटल काष्ठा पूर्णांकel_context *mocs_context_create(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस ce;

	/* We build large requests to पढ़ो the रेजिस्टरs from the ring */
	ce->ring = __पूर्णांकel_context_ring_size(SZ_16K);

	वापस ce;
पूर्ण

अटल पूर्णांक request_add_sync(काष्ठा i915_request *rq, पूर्णांक err)
अणु
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
		err = -ETIME;
	i915_request_put(rq);

	वापस err;
पूर्ण

अटल पूर्णांक request_add_spin(काष्ठा i915_request *rq, काष्ठा igt_spinner *spin)
अणु
	पूर्णांक err = 0;

	i915_request_get(rq);
	i915_request_add(rq);
	अगर (spin && !igt_रुको_क्रम_spinner(spin, rq))
		err = -ETIME;
	i915_request_put(rq);

	वापस err;
पूर्ण

अटल पूर्णांक live_mocs_init(काष्ठा live_mocs *arg, काष्ठा पूर्णांकel_gt *gt)
अणु
	अचिन्हित पूर्णांक flags;
	पूर्णांक err;

	स_रखो(arg, 0, माप(*arg));

	flags = get_mocs_settings(gt->i915, &arg->table);
	अगर (!flags)
		वापस -EINVAL;

	अगर (flags & HAS_RENDER_L3CC)
		arg->l3cc = &arg->table;

	अगर (flags & (HAS_GLOBAL_MOCS | HAS_ENGINE_MOCS))
		arg->mocs = &arg->table;

	arg->scratch =
		__vm_create_scratch_क्रम_पढ़ो_pinned(&gt->ggtt->vm, PAGE_SIZE);
	अगर (IS_ERR(arg->scratch))
		वापस PTR_ERR(arg->scratch);

	arg->vaddr = i915_gem_object_pin_map_unlocked(arg->scratch->obj, I915_MAP_WB);
	अगर (IS_ERR(arg->vaddr)) अणु
		err = PTR_ERR(arg->vaddr);
		जाओ err_scratch;
	पूर्ण

	वापस 0;

err_scratch:
	i915_vma_unpin_and_release(&arg->scratch, 0);
	वापस err;
पूर्ण

अटल व्योम live_mocs_fini(काष्ठा live_mocs *arg)
अणु
	i915_vma_unpin_and_release(&arg->scratch, I915_VMA_RELEASE_MAP);
पूर्ण

अटल पूर्णांक पढ़ो_regs(काष्ठा i915_request *rq,
		     u32 addr, अचिन्हित पूर्णांक count,
		     u32 *offset)
अणु
	अचिन्हित पूर्णांक i;
	u32 *cs;

	GEM_BUG_ON(!IS_ALIGNED(*offset, माप(u32)));

	cs = पूर्णांकel_ring_begin(rq, 4 * count);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	क्रम (i = 0; i < count; i++) अणु
		*cs++ = MI_STORE_REGISTER_MEM_GEN8 | MI_USE_GGTT;
		*cs++ = addr;
		*cs++ = *offset;
		*cs++ = 0;

		addr += माप(u32);
		*offset += माप(u32);
	पूर्ण

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_mocs_table(काष्ठा i915_request *rq,
			   स्थिर काष्ठा drm_i915_mocs_table *table,
			   u32 *offset)
अणु
	u32 addr;

	अगर (!table)
		वापस 0;

	अगर (HAS_GLOBAL_MOCS_REGISTERS(rq->engine->i915))
		addr = global_mocs_offset();
	अन्यथा
		addr = mocs_offset(rq->engine);

	वापस पढ़ो_regs(rq, addr, table->n_entries, offset);
पूर्ण

अटल पूर्णांक पढ़ो_l3cc_table(काष्ठा i915_request *rq,
			   स्थिर काष्ठा drm_i915_mocs_table *table,
			   u32 *offset)
अणु
	u32 addr = i915_mmio_reg_offset(GEN9_LNCFCMOCS(0));

	अगर (!table)
		वापस 0;

	वापस पढ़ो_regs(rq, addr, (table->n_entries + 1) / 2, offset);
पूर्ण

अटल पूर्णांक check_mocs_table(काष्ठा पूर्णांकel_engine_cs *engine,
			    स्थिर काष्ठा drm_i915_mocs_table *table,
			    u32 **vaddr)
अणु
	अचिन्हित पूर्णांक i;
	u32 expect;

	अगर (!table)
		वापस 0;

	क्रम_each_mocs(expect, table, i) अणु
		अगर (**vaddr != expect) अणु
			pr_err("%s: Invalid MOCS[%d] entry, found %08x, expected %08x\n",
			       engine->name, i, **vaddr, expect);
			वापस -EINVAL;
		पूर्ण
		++*vaddr;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool mcr_range(काष्ठा drm_i915_निजी *i915, u32 offset)
अणु
	/*
	 * Registers in this range are affected by the MCR selector
	 * which only controls CPU initiated MMIO. Routing करोes not
	 * work क्रम CS access so we cannot verअगरy them on this path.
	 */
	वापस INTEL_GEN(i915) >= 8 && offset >= 0xb000 && offset <= 0xb4ff;
पूर्ण

अटल पूर्णांक check_l3cc_table(काष्ठा पूर्णांकel_engine_cs *engine,
			    स्थिर काष्ठा drm_i915_mocs_table *table,
			    u32 **vaddr)
अणु
	/* Can we पढ़ो the MCR range 0xb00 directly? See पूर्णांकel_workarounds! */
	u32 reg = i915_mmio_reg_offset(GEN9_LNCFCMOCS(0));
	अचिन्हित पूर्णांक i;
	u32 expect;

	अगर (!table)
		वापस 0;

	क्रम_each_l3cc(expect, table, i) अणु
		अगर (!mcr_range(engine->i915, reg) && **vaddr != expect) अणु
			pr_err("%s: Invalid L3CC[%d] entry, found %08x, expected %08x\n",
			       engine->name, i, **vaddr, expect);
			वापस -EINVAL;
		पूर्ण
		++*vaddr;
		reg += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_mocs_engine(काष्ठा live_mocs *arg,
			     काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_vma *vma = arg->scratch;
	काष्ठा i915_request *rq;
	u32 offset;
	u32 *vaddr;
	पूर्णांक err;

	स_रखो32(arg->vaddr, STACK_MAGIC, PAGE_SIZE / माप(u32));

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, true);
	अगर (!err)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	i915_vma_unlock(vma);

	/* Read the mocs tables back using SRM */
	offset = i915_ggtt_offset(vma);
	अगर (!err)
		err = पढ़ो_mocs_table(rq, arg->mocs, &offset);
	अगर (!err && ce->engine->class == RENDER_CLASS)
		err = पढ़ो_l3cc_table(rq, arg->l3cc, &offset);
	offset -= i915_ggtt_offset(vma);
	GEM_BUG_ON(offset > PAGE_SIZE);

	err = request_add_sync(rq, err);
	अगर (err)
		वापस err;

	/* Compare the results against the expected tables */
	vaddr = arg->vaddr;
	अगर (!err)
		err = check_mocs_table(ce->engine, arg->mocs, &vaddr);
	अगर (!err && ce->engine->class == RENDER_CLASS)
		err = check_l3cc_table(ce->engine, arg->l3cc, &vaddr);
	अगर (err)
		वापस err;

	GEM_BUG_ON(arg->vaddr + offset != vaddr);
	वापस 0;
पूर्ण

अटल पूर्णांक live_mocs_kernel(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा live_mocs mocs;
	पूर्णांक err;

	/* Basic check the प्रणाली is configured with the expected mocs table */

	err = live_mocs_init(&mocs, gt);
	अगर (err)
		वापस err;

	क्रम_each_engine(engine, gt, id) अणु
		पूर्णांकel_engine_pm_get(engine);
		err = check_mocs_engine(&mocs, engine->kernel_context);
		पूर्णांकel_engine_pm_put(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	live_mocs_fini(&mocs);
	वापस err;
पूर्ण

अटल पूर्णांक live_mocs_clean(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा live_mocs mocs;
	पूर्णांक err;

	/* Every new context should see the same mocs table */

	err = live_mocs_init(&mocs, gt);
	अगर (err)
		वापस err;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;

		ce = mocs_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			अवरोध;
		पूर्ण

		err = check_mocs_engine(&mocs, ce);
		पूर्णांकel_context_put(ce);
		अगर (err)
			अवरोध;
	पूर्ण

	live_mocs_fini(&mocs);
	वापस err;
पूर्ण

अटल पूर्णांक active_engine_reset(काष्ठा पूर्णांकel_context *ce,
			       स्थिर अक्षर *reason)
अणु
	काष्ठा igt_spinner spin;
	काष्ठा i915_request *rq;
	पूर्णांक err;

	err = igt_spinner_init(&spin, ce->engine->gt);
	अगर (err)
		वापस err;

	rq = igt_spinner_create_request(&spin, ce, MI_NOOP);
	अगर (IS_ERR(rq)) अणु
		igt_spinner_fini(&spin);
		वापस PTR_ERR(rq);
	पूर्ण

	err = request_add_spin(rq, &spin);
	अगर (err == 0)
		err = पूर्णांकel_engine_reset(ce->engine, reason);

	igt_spinner_end(&spin);
	igt_spinner_fini(&spin);

	वापस err;
पूर्ण

अटल पूर्णांक __live_mocs_reset(काष्ठा live_mocs *mocs,
			     काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_gt *gt = ce->engine->gt;
	पूर्णांक err;

	अगर (पूर्णांकel_has_reset_engine(gt)) अणु
		err = पूर्णांकel_engine_reset(ce->engine, "mocs");
		अगर (err)
			वापस err;

		err = check_mocs_engine(mocs, ce);
		अगर (err)
			वापस err;

		err = active_engine_reset(ce, "mocs");
		अगर (err)
			वापस err;

		err = check_mocs_engine(mocs, ce);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (पूर्णांकel_has_gpu_reset(gt)) अणु
		पूर्णांकel_gt_reset(gt, ce->engine->mask, "mocs");

		err = check_mocs_engine(mocs, ce);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक live_mocs_reset(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा live_mocs mocs;
	पूर्णांक err = 0;

	/* Check the mocs setup is retained over per-engine and global resets */

	err = live_mocs_init(&mocs, gt);
	अगर (err)
		वापस err;

	igt_global_reset_lock(gt);
	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce;

		ce = mocs_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			err = PTR_ERR(ce);
			अवरोध;
		पूर्ण

		पूर्णांकel_engine_pm_get(engine);
		err = __live_mocs_reset(&mocs, ce);
		पूर्णांकel_engine_pm_put(engine);

		पूर्णांकel_context_put(ce);
		अगर (err)
			अवरोध;
	पूर्ण
	igt_global_reset_unlock(gt);

	live_mocs_fini(&mocs);
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_mocs_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_mocs_kernel),
		SUBTEST(live_mocs_clean),
		SUBTEST(live_mocs_reset),
	पूर्ण;
	काष्ठा drm_i915_mocs_table table;

	अगर (!get_mocs_settings(i915, &table))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
