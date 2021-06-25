<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014 Intel Corporation
 */

#समावेश "gem/i915_gem_lmem.h"

#समावेश "gen8_engine_cs.h"
#समावेश "i915_drv.h"
#समावेश "i915_perf.h"
#समावेश "intel_engine.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt.h"
#समावेश "intel_lrc.h"
#समावेश "intel_lrc_reg.h"
#समावेश "intel_ring.h"
#समावेश "shmem_utils.h"

अटल व्योम set_offsets(u32 *regs,
			स्थिर u8 *data,
			स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			bool बंद)
#घोषणा NOP(x) (BIT(7) | (x))
#घोषणा LRI(count, flags) ((flags) << 6 | (count) | BUILD_BUG_ON_ZERO(count >= BIT(6)))
#घोषणा POSTED BIT(0)
#घोषणा REG(x) (((x) >> 2) | BUILD_BUG_ON_ZERO(x >= 0x200))
#घोषणा REG16(x) \
	(((x) >> 9) | BIT(7) | BUILD_BUG_ON_ZERO(x >= 0x10000)), \
	(((x) >> 2) & 0x7f)
#घोषणा END 0
अणु
	स्थिर u32 base = engine->mmio_base;

	जबतक (*data) अणु
		u8 count, flags;

		अगर (*data & BIT(7)) अणु /* skip */
			count = *data++ & ~BIT(7);
			regs += count;
			जारी;
		पूर्ण

		count = *data & 0x3f;
		flags = *data >> 6;
		data++;

		*regs = MI_LOAD_REGISTER_IMM(count);
		अगर (flags & POSTED)
			*regs |= MI_LRI_FORCE_POSTED;
		अगर (INTEL_GEN(engine->i915) >= 11)
			*regs |= MI_LRI_LRM_CS_MMIO;
		regs++;

		GEM_BUG_ON(!count);
		करो अणु
			u32 offset = 0;
			u8 v;

			करो अणु
				v = *data++;
				offset <<= 7;
				offset |= v & ~BIT(7);
			पूर्ण जबतक (v & BIT(7));

			regs[0] = base + (offset << 2);
			regs += 2;
		पूर्ण जबतक (--count);
	पूर्ण

	अगर (बंद) अणु
		/* Close the batch; used मुख्यly by live_lrc_layout() */
		*regs = MI_BATCH_BUFFER_END;
		अगर (INTEL_GEN(engine->i915) >= 10)
			*regs |= BIT(0);
	पूर्ण
पूर्ण

अटल स्थिर u8 gen8_xcs_offsets[] = अणु
	NOP(1),
	LRI(11, 0),
	REG16(0x244),
	REG(0x034),
	REG(0x030),
	REG(0x038),
	REG(0x03c),
	REG(0x168),
	REG(0x140),
	REG(0x110),
	REG(0x11c),
	REG(0x114),
	REG(0x118),

	NOP(9),
	LRI(9, 0),
	REG16(0x3a8),
	REG16(0x28c),
	REG16(0x288),
	REG16(0x284),
	REG16(0x280),
	REG16(0x27c),
	REG16(0x278),
	REG16(0x274),
	REG16(0x270),

	NOP(13),
	LRI(2, 0),
	REG16(0x200),
	REG(0x028),

	END
पूर्ण;

अटल स्थिर u8 gen9_xcs_offsets[] = अणु
	NOP(1),
	LRI(14, POSTED),
	REG16(0x244),
	REG(0x034),
	REG(0x030),
	REG(0x038),
	REG(0x03c),
	REG(0x168),
	REG(0x140),
	REG(0x110),
	REG(0x11c),
	REG(0x114),
	REG(0x118),
	REG(0x1c0),
	REG(0x1c4),
	REG(0x1c8),

	NOP(3),
	LRI(9, POSTED),
	REG16(0x3a8),
	REG16(0x28c),
	REG16(0x288),
	REG16(0x284),
	REG16(0x280),
	REG16(0x27c),
	REG16(0x278),
	REG16(0x274),
	REG16(0x270),

	NOP(13),
	LRI(1, POSTED),
	REG16(0x200),

	NOP(13),
	LRI(44, POSTED),
	REG(0x028),
	REG(0x09c),
	REG(0x0c0),
	REG(0x178),
	REG(0x17c),
	REG16(0x358),
	REG(0x170),
	REG(0x150),
	REG(0x154),
	REG(0x158),
	REG16(0x41c),
	REG16(0x600),
	REG16(0x604),
	REG16(0x608),
	REG16(0x60c),
	REG16(0x610),
	REG16(0x614),
	REG16(0x618),
	REG16(0x61c),
	REG16(0x620),
	REG16(0x624),
	REG16(0x628),
	REG16(0x62c),
	REG16(0x630),
	REG16(0x634),
	REG16(0x638),
	REG16(0x63c),
	REG16(0x640),
	REG16(0x644),
	REG16(0x648),
	REG16(0x64c),
	REG16(0x650),
	REG16(0x654),
	REG16(0x658),
	REG16(0x65c),
	REG16(0x660),
	REG16(0x664),
	REG16(0x668),
	REG16(0x66c),
	REG16(0x670),
	REG16(0x674),
	REG16(0x678),
	REG16(0x67c),
	REG(0x068),

	END
पूर्ण;

अटल स्थिर u8 gen12_xcs_offsets[] = अणु
	NOP(1),
	LRI(13, POSTED),
	REG16(0x244),
	REG(0x034),
	REG(0x030),
	REG(0x038),
	REG(0x03c),
	REG(0x168),
	REG(0x140),
	REG(0x110),
	REG(0x1c0),
	REG(0x1c4),
	REG(0x1c8),
	REG(0x180),
	REG16(0x2b4),

	NOP(5),
	LRI(9, POSTED),
	REG16(0x3a8),
	REG16(0x28c),
	REG16(0x288),
	REG16(0x284),
	REG16(0x280),
	REG16(0x27c),
	REG16(0x278),
	REG16(0x274),
	REG16(0x270),

	END
पूर्ण;

अटल स्थिर u8 gen8_rcs_offsets[] = अणु
	NOP(1),
	LRI(14, POSTED),
	REG16(0x244),
	REG(0x034),
	REG(0x030),
	REG(0x038),
	REG(0x03c),
	REG(0x168),
	REG(0x140),
	REG(0x110),
	REG(0x11c),
	REG(0x114),
	REG(0x118),
	REG(0x1c0),
	REG(0x1c4),
	REG(0x1c8),

	NOP(3),
	LRI(9, POSTED),
	REG16(0x3a8),
	REG16(0x28c),
	REG16(0x288),
	REG16(0x284),
	REG16(0x280),
	REG16(0x27c),
	REG16(0x278),
	REG16(0x274),
	REG16(0x270),

	NOP(13),
	LRI(1, 0),
	REG(0x0c8),

	END
पूर्ण;

अटल स्थिर u8 gen9_rcs_offsets[] = अणु
	NOP(1),
	LRI(14, POSTED),
	REG16(0x244),
	REG(0x34),
	REG(0x30),
	REG(0x38),
	REG(0x3c),
	REG(0x168),
	REG(0x140),
	REG(0x110),
	REG(0x11c),
	REG(0x114),
	REG(0x118),
	REG(0x1c0),
	REG(0x1c4),
	REG(0x1c8),

	NOP(3),
	LRI(9, POSTED),
	REG16(0x3a8),
	REG16(0x28c),
	REG16(0x288),
	REG16(0x284),
	REG16(0x280),
	REG16(0x27c),
	REG16(0x278),
	REG16(0x274),
	REG16(0x270),

	NOP(13),
	LRI(1, 0),
	REG(0xc8),

	NOP(13),
	LRI(44, POSTED),
	REG(0x28),
	REG(0x9c),
	REG(0xc0),
	REG(0x178),
	REG(0x17c),
	REG16(0x358),
	REG(0x170),
	REG(0x150),
	REG(0x154),
	REG(0x158),
	REG16(0x41c),
	REG16(0x600),
	REG16(0x604),
	REG16(0x608),
	REG16(0x60c),
	REG16(0x610),
	REG16(0x614),
	REG16(0x618),
	REG16(0x61c),
	REG16(0x620),
	REG16(0x624),
	REG16(0x628),
	REG16(0x62c),
	REG16(0x630),
	REG16(0x634),
	REG16(0x638),
	REG16(0x63c),
	REG16(0x640),
	REG16(0x644),
	REG16(0x648),
	REG16(0x64c),
	REG16(0x650),
	REG16(0x654),
	REG16(0x658),
	REG16(0x65c),
	REG16(0x660),
	REG16(0x664),
	REG16(0x668),
	REG16(0x66c),
	REG16(0x670),
	REG16(0x674),
	REG16(0x678),
	REG16(0x67c),
	REG(0x68),

	END
पूर्ण;

अटल स्थिर u8 gen11_rcs_offsets[] = अणु
	NOP(1),
	LRI(15, POSTED),
	REG16(0x244),
	REG(0x034),
	REG(0x030),
	REG(0x038),
	REG(0x03c),
	REG(0x168),
	REG(0x140),
	REG(0x110),
	REG(0x11c),
	REG(0x114),
	REG(0x118),
	REG(0x1c0),
	REG(0x1c4),
	REG(0x1c8),
	REG(0x180),

	NOP(1),
	LRI(9, POSTED),
	REG16(0x3a8),
	REG16(0x28c),
	REG16(0x288),
	REG16(0x284),
	REG16(0x280),
	REG16(0x27c),
	REG16(0x278),
	REG16(0x274),
	REG16(0x270),

	LRI(1, POSTED),
	REG(0x1b0),

	NOP(10),
	LRI(1, 0),
	REG(0x0c8),

	END
पूर्ण;

अटल स्थिर u8 gen12_rcs_offsets[] = अणु
	NOP(1),
	LRI(13, POSTED),
	REG16(0x244),
	REG(0x034),
	REG(0x030),
	REG(0x038),
	REG(0x03c),
	REG(0x168),
	REG(0x140),
	REG(0x110),
	REG(0x1c0),
	REG(0x1c4),
	REG(0x1c8),
	REG(0x180),
	REG16(0x2b4),

	NOP(5),
	LRI(9, POSTED),
	REG16(0x3a8),
	REG16(0x28c),
	REG16(0x288),
	REG16(0x284),
	REG16(0x280),
	REG16(0x27c),
	REG16(0x278),
	REG16(0x274),
	REG16(0x270),

	LRI(3, POSTED),
	REG(0x1b0),
	REG16(0x5a8),
	REG16(0x5ac),

	NOP(6),
	LRI(1, 0),
	REG(0x0c8),
	NOP(3 + 9 + 1),

	LRI(51, POSTED),
	REG16(0x588),
	REG16(0x588),
	REG16(0x588),
	REG16(0x588),
	REG16(0x588),
	REG16(0x588),
	REG(0x028),
	REG(0x09c),
	REG(0x0c0),
	REG(0x178),
	REG(0x17c),
	REG16(0x358),
	REG(0x170),
	REG(0x150),
	REG(0x154),
	REG(0x158),
	REG16(0x41c),
	REG16(0x600),
	REG16(0x604),
	REG16(0x608),
	REG16(0x60c),
	REG16(0x610),
	REG16(0x614),
	REG16(0x618),
	REG16(0x61c),
	REG16(0x620),
	REG16(0x624),
	REG16(0x628),
	REG16(0x62c),
	REG16(0x630),
	REG16(0x634),
	REG16(0x638),
	REG16(0x63c),
	REG16(0x640),
	REG16(0x644),
	REG16(0x648),
	REG16(0x64c),
	REG16(0x650),
	REG16(0x654),
	REG16(0x658),
	REG16(0x65c),
	REG16(0x660),
	REG16(0x664),
	REG16(0x668),
	REG16(0x66c),
	REG16(0x670),
	REG16(0x674),
	REG16(0x678),
	REG16(0x67c),
	REG(0x068),
	REG(0x084),
	NOP(1),

	END
पूर्ण;

#अघोषित END
#अघोषित REG16
#अघोषित REG
#अघोषित LRI
#अघोषित NOP

अटल स्थिर u8 *reg_offsets(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/*
	 * The gen12+ lists only have the रेजिस्टरs we program in the basic
	 * शेष state. We rely on the context image using relative
	 * addressing to स्वतःmatic fixup the रेजिस्टर state between the
	 * physical engines क्रम भव engine.
	 */
	GEM_BUG_ON(INTEL_GEN(engine->i915) >= 12 &&
		   !पूर्णांकel_engine_has_relative_mmio(engine));

	अगर (engine->class == RENDER_CLASS) अणु
		अगर (INTEL_GEN(engine->i915) >= 12)
			वापस gen12_rcs_offsets;
		अन्यथा अगर (INTEL_GEN(engine->i915) >= 11)
			वापस gen11_rcs_offsets;
		अन्यथा अगर (INTEL_GEN(engine->i915) >= 9)
			वापस gen9_rcs_offsets;
		अन्यथा
			वापस gen8_rcs_offsets;
	पूर्ण अन्यथा अणु
		अगर (INTEL_GEN(engine->i915) >= 12)
			वापस gen12_xcs_offsets;
		अन्यथा अगर (INTEL_GEN(engine->i915) >= 9)
			वापस gen9_xcs_offsets;
		अन्यथा
			वापस gen8_xcs_offsets;
	पूर्ण
पूर्ण

अटल पूर्णांक lrc_ring_mi_mode(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (INTEL_GEN(engine->i915) >= 12)
		वापस 0x60;
	अन्यथा अगर (INTEL_GEN(engine->i915) >= 9)
		वापस 0x54;
	अन्यथा अगर (engine->class == RENDER_CLASS)
		वापस 0x58;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक lrc_ring_gpr0(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (INTEL_GEN(engine->i915) >= 12)
		वापस 0x74;
	अन्यथा अगर (INTEL_GEN(engine->i915) >= 9)
		वापस 0x68;
	अन्यथा अगर (engine->class == RENDER_CLASS)
		वापस 0xd8;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक lrc_ring_wa_bb_per_ctx(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (INTEL_GEN(engine->i915) >= 12)
		वापस 0x12;
	अन्यथा अगर (INTEL_GEN(engine->i915) >= 9 || engine->class == RENDER_CLASS)
		वापस 0x18;
	अन्यथा
		वापस -1;
पूर्ण

अटल पूर्णांक lrc_ring_indirect_ptr(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांक x;

	x = lrc_ring_wa_bb_per_ctx(engine);
	अगर (x < 0)
		वापस x;

	वापस x + 2;
पूर्ण

अटल पूर्णांक lrc_ring_indirect_offset(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांक x;

	x = lrc_ring_indirect_ptr(engine);
	अगर (x < 0)
		वापस x;

	वापस x + 2;
पूर्ण

अटल पूर्णांक lrc_ring_cmd_buf_cctl(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (engine->class != RENDER_CLASS)
		वापस -1;

	अगर (INTEL_GEN(engine->i915) >= 12)
		वापस 0xb6;
	अन्यथा अगर (INTEL_GEN(engine->i915) >= 11)
		वापस 0xaa;
	अन्यथा
		वापस -1;
पूर्ण

अटल u32
lrc_ring_indirect_offset_शेष(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	चयन (INTEL_GEN(engine->i915)) अणु
	शेष:
		MISSING_CASE(INTEL_GEN(engine->i915));
		fallthrough;
	हाल 12:
		वापस GEN12_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT;
	हाल 11:
		वापस GEN11_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT;
	हाल 10:
		वापस GEN10_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT;
	हाल 9:
		वापस GEN9_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT;
	हाल 8:
		वापस GEN8_CTX_RCS_INसूचीECT_CTX_OFFSET_DEFAULT;
	पूर्ण
पूर्ण

अटल व्योम
lrc_setup_indirect_ctx(u32 *regs,
		       स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		       u32 ctx_bb_ggtt_addr,
		       u32 size)
अणु
	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, CACHELINE_BYTES));
	GEM_BUG_ON(lrc_ring_indirect_ptr(engine) == -1);
	regs[lrc_ring_indirect_ptr(engine) + 1] =
		ctx_bb_ggtt_addr | (size / CACHELINE_BYTES);

	GEM_BUG_ON(lrc_ring_indirect_offset(engine) == -1);
	regs[lrc_ring_indirect_offset(engine) + 1] =
		lrc_ring_indirect_offset_शेष(engine) << 6;
पूर्ण

अटल व्योम init_common_regs(u32 * स्थिर regs,
			     स्थिर काष्ठा पूर्णांकel_context *ce,
			     स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			     bool inhibit)
अणु
	u32 ctl;

	ctl = _MASKED_BIT_ENABLE(CTX_CTRL_INHIBIT_SYN_CTX_SWITCH);
	ctl |= _MASKED_BIT_DISABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT);
	अगर (inhibit)
		ctl |= CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT;
	अगर (INTEL_GEN(engine->i915) < 11)
		ctl |= _MASKED_BIT_DISABLE(CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT |
					   CTX_CTRL_RS_CTX_ENABLE);
	regs[CTX_CONTEXT_CONTROL] = ctl;

	regs[CTX_TIMESTAMP] = ce->runसमय.last;
पूर्ण

अटल व्योम init_wa_bb_regs(u32 * स्थिर regs,
			    स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर काष्ठा i915_ctx_workarounds * स्थिर wa_ctx = &engine->wa_ctx;

	अगर (wa_ctx->per_ctx.size) अणु
		स्थिर u32 ggtt_offset = i915_ggtt_offset(wa_ctx->vma);

		GEM_BUG_ON(lrc_ring_wa_bb_per_ctx(engine) == -1);
		regs[lrc_ring_wa_bb_per_ctx(engine) + 1] =
			(ggtt_offset + wa_ctx->per_ctx.offset) | 0x01;
	पूर्ण

	अगर (wa_ctx->indirect_ctx.size) अणु
		lrc_setup_indirect_ctx(regs, engine,
				       i915_ggtt_offset(wa_ctx->vma) +
				       wa_ctx->indirect_ctx.offset,
				       wa_ctx->indirect_ctx.size);
	पूर्ण
पूर्ण

अटल व्योम init_ppgtt_regs(u32 *regs, स्थिर काष्ठा i915_ppgtt *ppgtt)
अणु
	अगर (i915_vm_is_4lvl(&ppgtt->vm)) अणु
		/* 64b PPGTT (48bit canonical)
		 * PDP0_DESCRIPTOR contains the base address to PML4 and
		 * other PDP Descriptors are ignored.
		 */
		ASSIGN_CTX_PML4(ppgtt, regs);
	पूर्ण अन्यथा अणु
		ASSIGN_CTX_PDP(ppgtt, regs, 3);
		ASSIGN_CTX_PDP(ppgtt, regs, 2);
		ASSIGN_CTX_PDP(ppgtt, regs, 1);
		ASSIGN_CTX_PDP(ppgtt, regs, 0);
	पूर्ण
पूर्ण

अटल काष्ठा i915_ppgtt *vm_alias(काष्ठा i915_address_space *vm)
अणु
	अगर (i915_is_ggtt(vm))
		वापस i915_vm_to_ggtt(vm)->alias;
	अन्यथा
		वापस i915_vm_to_ppgtt(vm);
पूर्ण

अटल व्योम __reset_stop_ring(u32 *regs, स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांक x;

	x = lrc_ring_mi_mode(engine);
	अगर (x != -1) अणु
		regs[x + 1] &= ~STOP_RING;
		regs[x + 1] |= STOP_RING << 16;
	पूर्ण
पूर्ण

अटल व्योम __lrc_init_regs(u32 *regs,
			    स्थिर काष्ठा पूर्णांकel_context *ce,
			    स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			    bool inhibit)
अणु
	/*
	 * A context is actually a big batch buffer with several
	 * MI_LOAD_REGISTER_IMM commands followed by (reg, value) pairs. The
	 * values we are setting here are only क्रम the first context restore:
	 * on a subsequent save, the GPU will recreate this batchbuffer with new
	 * values (including all the missing MI_LOAD_REGISTER_IMM commands that
	 * we are not initializing here).
	 *
	 * Must keep consistent with भव_update_रेजिस्टर_offsets().
	 */

	अगर (inhibit)
		स_रखो(regs, 0, PAGE_SIZE);

	set_offsets(regs, reg_offsets(engine), engine, inhibit);

	init_common_regs(regs, ce, engine, inhibit);
	init_ppgtt_regs(regs, vm_alias(ce->vm));

	init_wa_bb_regs(regs, engine);

	__reset_stop_ring(regs, engine);
पूर्ण

व्योम lrc_init_regs(स्थिर काष्ठा पूर्णांकel_context *ce,
		   स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		   bool inhibit)
अणु
	__lrc_init_regs(ce->lrc_reg_state, ce, engine, inhibit);
पूर्ण

व्योम lrc_reset_regs(स्थिर काष्ठा पूर्णांकel_context *ce,
		    स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	__reset_stop_ring(ce->lrc_reg_state, engine);
पूर्ण

अटल व्योम
set_redzone(व्योम *vaddr, स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		वापस;

	vaddr += engine->context_size;

	स_रखो(vaddr, CONTEXT_REDZONE, I915_GTT_PAGE_SIZE);
पूर्ण

अटल व्योम
check_redzone(स्थिर व्योम *vaddr, स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		वापस;

	vaddr += engine->context_size;

	अगर (स_प्रथम_inv(vaddr, CONTEXT_REDZONE, I915_GTT_PAGE_SIZE))
		drm_err_once(&engine->i915->drm,
			     "%s context redzone overwritten!\n",
			     engine->name);
पूर्ण

व्योम lrc_init_state(काष्ठा पूर्णांकel_context *ce,
		    काष्ठा पूर्णांकel_engine_cs *engine,
		    व्योम *state)
अणु
	bool inhibit = true;

	set_redzone(state, engine);

	अगर (engine->शेष_state) अणु
		shmem_पढ़ो(engine->शेष_state, 0,
			   state, engine->context_size);
		__set_bit(CONTEXT_VALID_BIT, &ce->flags);
		inhibit = false;
	पूर्ण

	/* Clear the ppHWSP (inc. per-context counters) */
	स_रखो(state, 0, PAGE_SIZE);

	/*
	 * The second page of the context object contains some रेजिस्टरs which
	 * must be set up prior to the first execution.
	 */
	__lrc_init_regs(state + LRC_STATE_OFFSET, ce, engine, inhibit);
पूर्ण

अटल काष्ठा i915_vma *
__lrc_alloc_state(काष्ठा पूर्णांकel_context *ce, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 context_size;

	context_size = round_up(engine->context_size, I915_GTT_PAGE_SIZE);

	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		context_size += I915_GTT_PAGE_SIZE; /* क्रम redzone */

	अगर (INTEL_GEN(engine->i915) == 12) अणु
		ce->wa_bb_page = context_size / PAGE_SIZE;
		context_size += PAGE_SIZE;
	पूर्ण

	obj = i915_gem_object_create_lmem(engine->i915, context_size, 0);
	अगर (IS_ERR(obj))
		obj = i915_gem_object_create_shmem(engine->i915, context_size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		i915_gem_object_put(obj);
		वापस vma;
	पूर्ण

	वापस vma;
पूर्ण

अटल काष्ठा पूर्णांकel_समयline *
pinned_समयline(काष्ठा पूर्णांकel_context *ce, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_समयline *tl = fetch_and_zero(&ce->समयline);

	वापस पूर्णांकel_समयline_create_from_engine(engine, page_unmask_bits(tl));
पूर्ण

पूर्णांक lrc_alloc(काष्ठा पूर्णांकel_context *ce, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_ring *ring;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	GEM_BUG_ON(ce->state);

	vma = __lrc_alloc_state(ce, engine);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	ring = पूर्णांकel_engine_create_ring(engine, (अचिन्हित दीर्घ)ce->ring);
	अगर (IS_ERR(ring)) अणु
		err = PTR_ERR(ring);
		जाओ err_vma;
	पूर्ण

	अगर (!page_mask_bits(ce->समयline)) अणु
		काष्ठा पूर्णांकel_समयline *tl;

		/*
		 * Use the अटल global HWSP क्रम the kernel context, and
		 * a dynamically allocated cacheline क्रम everyone अन्यथा.
		 */
		अगर (unlikely(ce->समयline))
			tl = pinned_समयline(ce, engine);
		अन्यथा
			tl = पूर्णांकel_समयline_create(engine->gt);
		अगर (IS_ERR(tl)) अणु
			err = PTR_ERR(tl);
			जाओ err_ring;
		पूर्ण

		ce->समयline = tl;
	पूर्ण

	ce->ring = ring;
	ce->state = vma;

	वापस 0;

err_ring:
	पूर्णांकel_ring_put(ring);
err_vma:
	i915_vma_put(vma);
	वापस err;
पूर्ण

व्योम lrc_reset(काष्ठा पूर्णांकel_context *ce)
अणु
	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(ce));

	पूर्णांकel_ring_reset(ce->ring, ce->ring->emit);

	/* Scrub away the garbage */
	lrc_init_regs(ce, ce->engine, true);
	ce->lrc.lrca = lrc_update_regs(ce, ce->engine, ce->ring->tail);
पूर्ण

पूर्णांक
lrc_pre_pin(काष्ठा पूर्णांकel_context *ce,
	    काष्ठा पूर्णांकel_engine_cs *engine,
	    काष्ठा i915_gem_ww_ctx *ww,
	    व्योम **vaddr)
अणु
	GEM_BUG_ON(!ce->state);
	GEM_BUG_ON(!i915_vma_is_pinned(ce->state));

	*vaddr = i915_gem_object_pin_map(ce->state->obj,
					 i915_coherent_map_type(ce->engine->i915) |
					 I915_MAP_OVERRIDE);

	वापस PTR_ERR_OR_ZERO(*vaddr);
पूर्ण

पूर्णांक
lrc_pin(काष्ठा पूर्णांकel_context *ce,
	काष्ठा पूर्णांकel_engine_cs *engine,
	व्योम *vaddr)
अणु
	ce->lrc_reg_state = vaddr + LRC_STATE_OFFSET;

	अगर (!__test_and_set_bit(CONTEXT_INIT_BIT, &ce->flags))
		lrc_init_state(ce, engine, vaddr);

	ce->lrc.lrca = lrc_update_regs(ce, engine, ce->ring->tail);
	वापस 0;
पूर्ण

व्योम lrc_unpin(काष्ठा पूर्णांकel_context *ce)
अणु
	check_redzone((व्योम *)ce->lrc_reg_state - LRC_STATE_OFFSET,
		      ce->engine);
पूर्ण

व्योम lrc_post_unpin(काष्ठा पूर्णांकel_context *ce)
अणु
	i915_gem_object_unpin_map(ce->state->obj);
पूर्ण

व्योम lrc_fini(काष्ठा पूर्णांकel_context *ce)
अणु
	अगर (!ce->state)
		वापस;

	पूर्णांकel_ring_put(fetch_and_zero(&ce->ring));
	i915_vma_put(fetch_and_zero(&ce->state));
पूर्ण

व्योम lrc_destroy(काष्ठा kref *kref)
अणु
	काष्ठा पूर्णांकel_context *ce = container_of(kref, typeof(*ce), ref);

	GEM_BUG_ON(!i915_active_is_idle(&ce->active));
	GEM_BUG_ON(पूर्णांकel_context_is_pinned(ce));

	lrc_fini(ce);

	पूर्णांकel_context_fini(ce);
	पूर्णांकel_context_मुक्त(ce);
पूर्ण

अटल u32 *
gen12_emit_बारtamp_wa(स्थिर काष्ठा पूर्णांकel_context *ce, u32 *cs)
अणु
	*cs++ = MI_LOAD_REGISTER_MEM_GEN8 |
		MI_SRM_LRM_GLOBAL_GTT |
		MI_LRI_LRM_CS_MMIO;
	*cs++ = i915_mmio_reg_offset(GEN8_RING_CS_GPR(0, 0));
	*cs++ = i915_ggtt_offset(ce->state) + LRC_STATE_OFFSET +
		CTX_TIMESTAMP * माप(u32);
	*cs++ = 0;

	*cs++ = MI_LOAD_REGISTER_REG |
		MI_LRR_SOURCE_CS_MMIO |
		MI_LRI_LRM_CS_MMIO;
	*cs++ = i915_mmio_reg_offset(GEN8_RING_CS_GPR(0, 0));
	*cs++ = i915_mmio_reg_offset(RING_CTX_TIMESTAMP(0));

	*cs++ = MI_LOAD_REGISTER_REG |
		MI_LRR_SOURCE_CS_MMIO |
		MI_LRI_LRM_CS_MMIO;
	*cs++ = i915_mmio_reg_offset(GEN8_RING_CS_GPR(0, 0));
	*cs++ = i915_mmio_reg_offset(RING_CTX_TIMESTAMP(0));

	वापस cs;
पूर्ण

अटल u32 *
gen12_emit_restore_scratch(स्थिर काष्ठा पूर्णांकel_context *ce, u32 *cs)
अणु
	GEM_BUG_ON(lrc_ring_gpr0(ce->engine) == -1);

	*cs++ = MI_LOAD_REGISTER_MEM_GEN8 |
		MI_SRM_LRM_GLOBAL_GTT |
		MI_LRI_LRM_CS_MMIO;
	*cs++ = i915_mmio_reg_offset(GEN8_RING_CS_GPR(0, 0));
	*cs++ = i915_ggtt_offset(ce->state) + LRC_STATE_OFFSET +
		(lrc_ring_gpr0(ce->engine) + 1) * माप(u32);
	*cs++ = 0;

	वापस cs;
पूर्ण

अटल u32 *
gen12_emit_cmd_buf_wa(स्थिर काष्ठा पूर्णांकel_context *ce, u32 *cs)
अणु
	GEM_BUG_ON(lrc_ring_cmd_buf_cctl(ce->engine) == -1);

	*cs++ = MI_LOAD_REGISTER_MEM_GEN8 |
		MI_SRM_LRM_GLOBAL_GTT |
		MI_LRI_LRM_CS_MMIO;
	*cs++ = i915_mmio_reg_offset(GEN8_RING_CS_GPR(0, 0));
	*cs++ = i915_ggtt_offset(ce->state) + LRC_STATE_OFFSET +
		(lrc_ring_cmd_buf_cctl(ce->engine) + 1) * माप(u32);
	*cs++ = 0;

	*cs++ = MI_LOAD_REGISTER_REG |
		MI_LRR_SOURCE_CS_MMIO |
		MI_LRI_LRM_CS_MMIO;
	*cs++ = i915_mmio_reg_offset(GEN8_RING_CS_GPR(0, 0));
	*cs++ = i915_mmio_reg_offset(RING_CMD_BUF_CCTL(0));

	वापस cs;
पूर्ण

अटल u32 *
gen12_emit_indirect_ctx_rcs(स्थिर काष्ठा पूर्णांकel_context *ce, u32 *cs)
अणु
	cs = gen12_emit_बारtamp_wa(ce, cs);
	cs = gen12_emit_cmd_buf_wa(ce, cs);
	cs = gen12_emit_restore_scratch(ce, cs);

	वापस cs;
पूर्ण

अटल u32 *
gen12_emit_indirect_ctx_xcs(स्थिर काष्ठा पूर्णांकel_context *ce, u32 *cs)
अणु
	cs = gen12_emit_बारtamp_wa(ce, cs);
	cs = gen12_emit_restore_scratch(ce, cs);

	वापस cs;
पूर्ण

अटल u32 context_wa_bb_offset(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस PAGE_SIZE * ce->wa_bb_page;
पूर्ण

अटल u32 *context_indirect_bb(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	व्योम *ptr;

	GEM_BUG_ON(!ce->wa_bb_page);

	ptr = ce->lrc_reg_state;
	ptr -= LRC_STATE_OFFSET; /* back to start of context image */
	ptr += context_wa_bb_offset(ce);

	वापस ptr;
पूर्ण

अटल व्योम
setup_indirect_ctx_bb(स्थिर काष्ठा पूर्णांकel_context *ce,
		      स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		      u32 *(*emit)(स्थिर काष्ठा पूर्णांकel_context *, u32 *))
अणु
	u32 * स्थिर start = context_indirect_bb(ce);
	u32 *cs;

	cs = emit(ce, start);
	GEM_BUG_ON(cs - start > I915_GTT_PAGE_SIZE / माप(*cs));
	जबतक ((अचिन्हित दीर्घ)cs % CACHELINE_BYTES)
		*cs++ = MI_NOOP;

	lrc_setup_indirect_ctx(ce->lrc_reg_state, engine,
			       i915_ggtt_offset(ce->state) +
			       context_wa_bb_offset(ce),
			       (cs - start) * माप(*cs));
पूर्ण

/*
 * The context descriptor encodes various attributes of a context,
 * including its GTT address and some flags. Because it's fairly
 * expensive to calculate, we'll just करो it once and cache the result,
 * which reमुख्यs valid until the context is unpinned.
 *
 * This is what a descriptor looks like, from LSB to MSB::
 *
 *      bits  0-11:    flags, GEN8_CTX_* (cached in ctx->desc_ढाँचा)
 *      bits 12-31:    LRCA, GTT address of (the HWSP of) this context
 *      bits 32-52:    ctx ID, a globally unique tag (highest bit used by GuC)
 *      bits 53-54:    mbz, reserved क्रम use by hardware
 *      bits 55-63:    group ID, currently unused and set to 0
 *
 * Starting from Gen11, the upper dword of the descriptor has a new क्रमmat:
 *
 *      bits 32-36:    reserved
 *      bits 37-47:    SW context ID
 *      bits 48:53:    engine instance
 *      bit 54:        mbz, reserved क्रम use by hardware
 *      bits 55-60:    SW counter
 *      bits 61-63:    engine class
 *
 * engine info, SW context ID and SW counter need to क्रमm a unique number
 * (Context ID) per lrc.
 */
अटल u32 lrc_descriptor(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	u32 desc;

	desc = INTEL_LEGACY_32B_CONTEXT;
	अगर (i915_vm_is_4lvl(ce->vm))
		desc = INTEL_LEGACY_64B_CONTEXT;
	desc <<= GEN8_CTX_ADDRESSING_MODE_SHIFT;

	desc |= GEN8_CTX_VALID | GEN8_CTX_PRIVILEGE;
	अगर (IS_GEN(ce->vm->i915, 8))
		desc |= GEN8_CTX_L3LLC_COHERENT;

	वापस i915_ggtt_offset(ce->state) | desc;
पूर्ण

u32 lrc_update_regs(स्थिर काष्ठा पूर्णांकel_context *ce,
		    स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		    u32 head)
अणु
	काष्ठा पूर्णांकel_ring *ring = ce->ring;
	u32 *regs = ce->lrc_reg_state;

	GEM_BUG_ON(!पूर्णांकel_ring_offset_valid(ring, head));
	GEM_BUG_ON(!पूर्णांकel_ring_offset_valid(ring, ring->tail));

	regs[CTX_RING_START] = i915_ggtt_offset(ring->vma);
	regs[CTX_RING_HEAD] = head;
	regs[CTX_RING_TAIL] = ring->tail;
	regs[CTX_RING_CTL] = RING_CTL_SIZE(ring->size) | RING_VALID;

	/* RPCS */
	अगर (engine->class == RENDER_CLASS) अणु
		regs[CTX_R_PWR_CLK_STATE] =
			पूर्णांकel_sseu_make_rpcs(engine->gt, &ce->sseu);

		i915_oa_init_reg_state(ce, engine);
	पूर्ण

	अगर (ce->wa_bb_page) अणु
		u32 *(*fn)(स्थिर काष्ठा पूर्णांकel_context *ce, u32 *cs);

		fn = gen12_emit_indirect_ctx_xcs;
		अगर (ce->engine->class == RENDER_CLASS)
			fn = gen12_emit_indirect_ctx_rcs;

		/* Mutually exclusive wrt to global indirect bb */
		GEM_BUG_ON(engine->wa_ctx.indirect_ctx.size);
		setup_indirect_ctx_bb(ce, engine, fn);
	पूर्ण

	वापस lrc_descriptor(ce) | CTX_DESC_FORCE_RESTORE;
पूर्ण

व्योम lrc_update_offsets(काष्ठा पूर्णांकel_context *ce,
			काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	set_offsets(ce->lrc_reg_state, reg_offsets(engine), engine, false);
पूर्ण

व्योम lrc_check_regs(स्थिर काष्ठा पूर्णांकel_context *ce,
		    स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		    स्थिर अक्षर *when)
अणु
	स्थिर काष्ठा पूर्णांकel_ring *ring = ce->ring;
	u32 *regs = ce->lrc_reg_state;
	bool valid = true;
	पूर्णांक x;

	अगर (regs[CTX_RING_START] != i915_ggtt_offset(ring->vma)) अणु
		pr_err("%s: context submitted with incorrect RING_START [%08x], expected %08x\n",
		       engine->name,
		       regs[CTX_RING_START],
		       i915_ggtt_offset(ring->vma));
		regs[CTX_RING_START] = i915_ggtt_offset(ring->vma);
		valid = false;
	पूर्ण

	अगर ((regs[CTX_RING_CTL] & ~(RING_WAIT | RING_WAIT_SEMAPHORE)) !=
	    (RING_CTL_SIZE(ring->size) | RING_VALID)) अणु
		pr_err("%s: context submitted with incorrect RING_CTL [%08x], expected %08x\n",
		       engine->name,
		       regs[CTX_RING_CTL],
		       (u32)(RING_CTL_SIZE(ring->size) | RING_VALID));
		regs[CTX_RING_CTL] = RING_CTL_SIZE(ring->size) | RING_VALID;
		valid = false;
	पूर्ण

	x = lrc_ring_mi_mode(engine);
	अगर (x != -1 && regs[x + 1] & (regs[x + 1] >> 16) & STOP_RING) अणु
		pr_err("%s: context submitted with STOP_RING [%08x] in RING_MI_MODE\n",
		       engine->name, regs[x + 1]);
		regs[x + 1] &= ~STOP_RING;
		regs[x + 1] |= STOP_RING << 16;
		valid = false;
	पूर्ण

	WARN_ONCE(!valid, "Invalid lrc state found %s submission\n", when);
पूर्ण

/*
 * In this WA we need to set GEN8_L3SQCREG4[21:21] and reset it after
 * PIPE_CONTROL inकाष्ठाion. This is required क्रम the flush to happen correctly
 * but there is a slight complication as this is applied in WA batch where the
 * values are only initialized once so we cannot take रेजिस्टर value at the
 * beginning and reuse it further; hence we save its value to memory, upload a
 * स्थिरant value with bit21 set and then we restore it back with the saved value.
 * To simplअगरy the WA, a स्थिरant value is क्रमmed by using the शेष value
 * of this रेजिस्टर. This shouldn't be a problem because we are only modअगरying
 * it क्रम a लघु period and this batch in non-premptible. We can ofcourse
 * use additional inकाष्ठाions that पढ़ो the actual value of the रेजिस्टर
 * at that समय and set our bit of पूर्णांकerest but it makes the WA complicated.
 *
 * This WA is also required क्रम Gen9 so extracting as a function aव्योमs
 * code duplication.
 */
अटल u32 *
gen8_emit_flush_coherentl3_wa(काष्ठा पूर्णांकel_engine_cs *engine, u32 *batch)
अणु
	/* NB no one अन्यथा is allowed to scribble over scratch + 256! */
	*batch++ = MI_STORE_REGISTER_MEM_GEN8 | MI_SRM_LRM_GLOBAL_GTT;
	*batch++ = i915_mmio_reg_offset(GEN8_L3SQCREG4);
	*batch++ = पूर्णांकel_gt_scratch_offset(engine->gt,
					   INTEL_GT_SCRATCH_FIELD_COHERENTL3_WA);
	*batch++ = 0;

	*batch++ = MI_LOAD_REGISTER_IMM(1);
	*batch++ = i915_mmio_reg_offset(GEN8_L3SQCREG4);
	*batch++ = 0x40400000 | GEN8_LQSC_FLUSH_COHERENT_LINES;

	batch = gen8_emit_pipe_control(batch,
				       PIPE_CONTROL_CS_STALL |
				       PIPE_CONTROL_DC_FLUSH_ENABLE,
				       0);

	*batch++ = MI_LOAD_REGISTER_MEM_GEN8 | MI_SRM_LRM_GLOBAL_GTT;
	*batch++ = i915_mmio_reg_offset(GEN8_L3SQCREG4);
	*batch++ = पूर्णांकel_gt_scratch_offset(engine->gt,
					   INTEL_GT_SCRATCH_FIELD_COHERENTL3_WA);
	*batch++ = 0;

	वापस batch;
पूर्ण

/*
 * Typically we only have one indirect_ctx and per_ctx batch buffer which are
 * initialized at the beginning and shared across all contexts but this field
 * helps us to have multiple batches at dअगरferent offsets and select them based
 * on a criteria. At the moment this batch always start at the beginning of the page
 * and at this poपूर्णांक we करोn't have multiple wa_ctx batch buffers.
 *
 * The number of WA applied are not known at the beginning; we use this field
 * to वापस the no of DWORDS written.
 *
 * It is to be noted that this batch करोes not contain MI_BATCH_BUFFER_END
 * so it adds NOOPs as padding to make it cacheline aligned.
 * MI_BATCH_BUFFER_END will be added to perctx batch and both of them together
 * makes a complete batch buffer.
 */
अटल u32 *gen8_init_indirectctx_bb(काष्ठा पूर्णांकel_engine_cs *engine, u32 *batch)
अणु
	/* WaDisableCtxRestoreArbitration:bdw,chv */
	*batch++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;

	/* WaFlushCoherentL3CacheLinesAtContextSwitch:bdw */
	अगर (IS_BROADWELL(engine->i915))
		batch = gen8_emit_flush_coherentl3_wa(engine, batch);

	/* WaClearSlmSpaceAtContextSwitch:bdw,chv */
	/* Actual scratch location is at 128 bytes offset */
	batch = gen8_emit_pipe_control(batch,
				       PIPE_CONTROL_FLUSH_L3 |
				       PIPE_CONTROL_STORE_DATA_INDEX |
				       PIPE_CONTROL_CS_STALL |
				       PIPE_CONTROL_QW_WRITE,
				       LRC_PPHWSP_SCRATCH_ADDR);

	*batch++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;

	/* Pad to end of cacheline */
	जबतक ((अचिन्हित दीर्घ)batch % CACHELINE_BYTES)
		*batch++ = MI_NOOP;

	/*
	 * MI_BATCH_BUFFER_END is not required in Indirect ctx BB because
	 * execution depends on the length specअगरied in terms of cache lines
	 * in the रेजिस्टर CTX_RCS_INसूचीECT_CTX
	 */

	वापस batch;
पूर्ण

काष्ठा lri अणु
	i915_reg_t reg;
	u32 value;
पूर्ण;

अटल u32 *emit_lri(u32 *batch, स्थिर काष्ठा lri *lri, अचिन्हित पूर्णांक count)
अणु
	GEM_BUG_ON(!count || count > 63);

	*batch++ = MI_LOAD_REGISTER_IMM(count);
	करो अणु
		*batch++ = i915_mmio_reg_offset(lri->reg);
		*batch++ = lri->value;
	पूर्ण जबतक (lri++, --count);
	*batch++ = MI_NOOP;

	वापस batch;
पूर्ण

अटल u32 *gen9_init_indirectctx_bb(काष्ठा पूर्णांकel_engine_cs *engine, u32 *batch)
अणु
	अटल स्थिर काष्ठा lri lri[] = अणु
		/* WaDisableGatherAtSetShaderCommonSlice:skl,bxt,kbl,glk */
		अणु
			COMMON_SLICE_CHICKEN2,
			__MASKED_FIELD(GEN9_DISABLE_GATHER_AT_SET_SHADER_COMMON_SLICE,
				       0),
		पूर्ण,

		/* BSpec: 11391 */
		अणु
			FF_SLICE_CHICKEN,
			__MASKED_FIELD(FF_SLICE_CHICKEN_CL_PROVOKING_VERTEX_FIX,
				       FF_SLICE_CHICKEN_CL_PROVOKING_VERTEX_FIX),
		पूर्ण,

		/* BSpec: 11299 */
		अणु
			_3D_CHICKEN3,
			__MASKED_FIELD(_3D_CHICKEN_SF_PROVOKING_VERTEX_FIX,
				       _3D_CHICKEN_SF_PROVOKING_VERTEX_FIX),
		पूर्ण
	पूर्ण;

	*batch++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;

	/* WaFlushCoherentL3CacheLinesAtContextSwitch:skl,bxt,glk */
	batch = gen8_emit_flush_coherentl3_wa(engine, batch);

	/* WaClearSlmSpaceAtContextSwitch:skl,bxt,kbl,glk,cfl */
	batch = gen8_emit_pipe_control(batch,
				       PIPE_CONTROL_FLUSH_L3 |
				       PIPE_CONTROL_STORE_DATA_INDEX |
				       PIPE_CONTROL_CS_STALL |
				       PIPE_CONTROL_QW_WRITE,
				       LRC_PPHWSP_SCRATCH_ADDR);

	batch = emit_lri(batch, lri, ARRAY_SIZE(lri));

	/* WaMediaPoolStateCmdInWABB:bxt,glk */
	अगर (HAS_POOLED_EU(engine->i915)) अणु
		/*
		 * EU pool configuration is setup aदीर्घ with golden context
		 * during context initialization. This value depends on
		 * device type (2x6 or 3x6) and needs to be updated based
		 * on which subslice is disabled especially क्रम 2x6
		 * devices, however it is safe to load शेष
		 * configuration of 3x6 device instead of masking off
		 * corresponding bits because HW ignores bits of a disabled
		 * subslice and drops करोwn to appropriate config. Please
		 * see render_state_setup() in i915_gem_render_state.c क्रम
		 * possible configurations, to aव्योम duplication they are
		 * not shown here again.
		 */
		*batch++ = GEN9_MEDIA_POOL_STATE;
		*batch++ = GEN9_MEDIA_POOL_ENABLE;
		*batch++ = 0x00777000;
		*batch++ = 0;
		*batch++ = 0;
		*batch++ = 0;
	पूर्ण

	*batch++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;

	/* Pad to end of cacheline */
	जबतक ((अचिन्हित दीर्घ)batch % CACHELINE_BYTES)
		*batch++ = MI_NOOP;

	वापस batch;
पूर्ण

अटल u32 *
gen10_init_indirectctx_bb(काष्ठा पूर्णांकel_engine_cs *engine, u32 *batch)
अणु
	पूर्णांक i;

	/*
	 * WaPipeControlBeक्रमe3DStateSamplePattern: cnl
	 *
	 * Ensure the engine is idle prior to programming a
	 * 3DSTATE_SAMPLE_PATTERN during a context restore.
	 */
	batch = gen8_emit_pipe_control(batch,
				       PIPE_CONTROL_CS_STALL,
				       0);
	/*
	 * WaPipeControlBeक्रमe3DStateSamplePattern says we need 4 dwords क्रम
	 * the PIPE_CONTROL followed by 12 dwords of 0x0, so 16 dwords in
	 * total. However, a PIPE_CONTROL is 6 dwords दीर्घ, not 4, which is
	 * confusing. Since gen8_emit_pipe_control() alपढ़ोy advances the
	 * batch by 6 dwords, we advance the other 10 here, completing a
	 * cacheline. It's not clear अगर the workaround requires this padding
	 * beक्रमe other commands, or अगर it's just the regular padding we would
	 * alपढ़ोy have क्रम the workaround bb, so leave it here क्रम now.
	 */
	क्रम (i = 0; i < 10; i++)
		*batch++ = MI_NOOP;

	/* Pad to end of cacheline */
	जबतक ((अचिन्हित दीर्घ)batch % CACHELINE_BYTES)
		*batch++ = MI_NOOP;

	वापस batch;
पूर्ण

#घोषणा CTX_WA_BB_SIZE (PAGE_SIZE)

अटल पूर्णांक lrc_create_wa_ctx(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	obj = i915_gem_object_create_shmem(engine->i915, CTX_WA_BB_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err;
	पूर्ण

	engine->wa_ctx.vma = vma;
	वापस 0;

err:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

व्योम lrc_fini_wa_ctx(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	i915_vma_unpin_and_release(&engine->wa_ctx.vma, 0);
पूर्ण

प्रकार u32 *(*wa_bb_func_t)(काष्ठा पूर्णांकel_engine_cs *engine, u32 *batch);

व्योम lrc_init_wa_ctx(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_ctx_workarounds *wa_ctx = &engine->wa_ctx;
	काष्ठा i915_wa_ctx_bb *wa_bb[] = अणु
		&wa_ctx->indirect_ctx, &wa_ctx->per_ctx
	पूर्ण;
	wa_bb_func_t wa_bb_fn[ARRAY_SIZE(wa_bb)];
	काष्ठा i915_gem_ww_ctx ww;
	व्योम *batch, *batch_ptr;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (engine->class != RENDER_CLASS)
		वापस;

	चयन (INTEL_GEN(engine->i915)) अणु
	हाल 12:
	हाल 11:
		वापस;
	हाल 10:
		wa_bb_fn[0] = gen10_init_indirectctx_bb;
		wa_bb_fn[1] = शून्य;
		अवरोध;
	हाल 9:
		wa_bb_fn[0] = gen9_init_indirectctx_bb;
		wa_bb_fn[1] = शून्य;
		अवरोध;
	हाल 8:
		wa_bb_fn[0] = gen8_init_indirectctx_bb;
		wa_bb_fn[1] = शून्य;
		अवरोध;
	शेष:
		MISSING_CASE(INTEL_GEN(engine->i915));
		वापस;
	पूर्ण

	err = lrc_create_wa_ctx(engine);
	अगर (err) अणु
		/*
		 * We जारी even अगर we fail to initialize WA batch
		 * because we only expect rare glitches but nothing
		 * critical to prevent us from using GPU
		 */
		drm_err(&engine->i915->drm,
			"Ignoring context switch w/a allocation error:%d\n",
			err);
		वापस;
	पूर्ण

	अगर (!engine->wa_ctx.vma)
		वापस;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = i915_gem_object_lock(wa_ctx->vma->obj, &ww);
	अगर (!err)
		err = i915_ggtt_pin(wa_ctx->vma, &ww, 0, PIN_HIGH);
	अगर (err)
		जाओ err;

	batch = i915_gem_object_pin_map(wa_ctx->vma->obj, I915_MAP_WB);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ err_unpin;
	पूर्ण

	/*
	 * Emit the two workaround batch buffers, recording the offset from the
	 * start of the workaround batch buffer object क्रम each and their
	 * respective sizes.
	 */
	batch_ptr = batch;
	क्रम (i = 0; i < ARRAY_SIZE(wa_bb_fn); i++) अणु
		wa_bb[i]->offset = batch_ptr - batch;
		अगर (GEM_DEBUG_WARN_ON(!IS_ALIGNED(wa_bb[i]->offset,
						  CACHELINE_BYTES))) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (wa_bb_fn[i])
			batch_ptr = wa_bb_fn[i](engine, batch_ptr);
		wa_bb[i]->size = batch_ptr - (batch + wa_bb[i]->offset);
	पूर्ण
	GEM_BUG_ON(batch_ptr - batch > CTX_WA_BB_SIZE);

	__i915_gem_object_flush_map(wa_ctx->vma->obj, 0, batch_ptr - batch);
	__i915_gem_object_release_map(wa_ctx->vma->obj);

	/* Verअगरy that we can handle failure to setup the wa_ctx */
	अगर (!err)
		err = i915_inject_probe_error(engine->i915, -ENODEV);

err_unpin:
	अगर (err)
		i915_vma_unpin(wa_ctx->vma);
err:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);

	अगर (err) अणु
		i915_vma_put(engine->wa_ctx.vma);

		/* Clear all flags to prevent further use */
		स_रखो(wa_ctx, 0, माप(*wa_ctx));
	पूर्ण
पूर्ण

अटल व्योम st_update_runसमय_underflow(काष्ठा पूर्णांकel_context *ce, s32 dt)
अणु
#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
	ce->runसमय.num_underflow++;
	ce->runसमय.max_underflow = max_t(u32, ce->runसमय.max_underflow, -dt);
#पूर्ण_अगर
पूर्ण

व्योम lrc_update_runसमय(काष्ठा पूर्णांकel_context *ce)
अणु
	u32 old;
	s32 dt;

	अगर (पूर्णांकel_context_is_barrier(ce))
		वापस;

	old = ce->runसमय.last;
	ce->runसमय.last = lrc_get_runसमय(ce);
	dt = ce->runसमय.last - old;

	अगर (unlikely(dt < 0)) अणु
		CE_TRACE(ce, "runtime underflow: last=%u, new=%u, delta=%d\n",
			 old, ce->runसमय.last, dt);
		st_update_runसमय_underflow(ce, dt);
		वापस;
	पूर्ण

	ewma_runसमय_add(&ce->runसमय.avg, dt);
	ce->runसमय.total += dt;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_lrc.c"
#पूर्ण_अगर
