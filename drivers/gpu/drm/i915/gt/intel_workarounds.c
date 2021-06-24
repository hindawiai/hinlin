<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014-2018 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_context.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt.h"
#समावेश "intel_ring.h"
#समावेश "intel_workarounds.h"

/**
 * DOC: Hardware workarounds
 *
 * This file is पूर्णांकended as a central place to implement most [1]_ of the
 * required workarounds क्रम hardware to work as originally पूर्णांकended. They fall
 * in five basic categories depending on how/when they are applied:
 *
 * - Workarounds that touch रेजिस्टरs that are saved/restored to/from the HW
 *   context image. The list is emitted (via Load Register Immediate commands)
 *   everyसमय a new context is created.
 * - GT workarounds. The list of these WAs is applied whenever these रेजिस्टरs
 *   revert to शेष values (on GPU reset, suspend/resume [2]_, etc..).
 * - Display workarounds. The list is applied during display घड़ी-gating
 *   initialization.
 * - Workarounds that whitelist a privileged रेजिस्टर, so that UMDs can manage
 *   them directly. This is just a special हाल of a MMMIO workaround (as we
 *   ग_लिखो the list of these to/be-whitelisted रेजिस्टरs to some special HW
 *   रेजिस्टरs).
 * - Workaround batchbuffers, that get executed स्वतःmatically by the hardware
 *   on every HW context restore.
 *
 * .. [1] Please notice that there are other WAs that, due to their nature,
 *    cannot be applied from a central place. Those are peppered around the rest
 *    of the code, as needed.
 *
 * .. [2] Technically, some रेजिस्टरs are घातercontext saved & restored, so they
 *    survive a suspend/resume. In practice, writing them again is not too
 *    costly and simplअगरies things. We can revisit this in the future.
 *
 * Layout
 * ~~~~~~
 *
 * Keep things in this file ordered by WA type, as per the above (context, GT,
 * display, रेजिस्टर whitelist, batchbuffer). Then, inside each type, keep the
 * following order:
 *
 * - Infraकाष्ठाure functions and macros
 * - WAs per platक्रमm in standard gen/chrono order
 * - Public functions to init or apply the given workaround type.
 */

अटल व्योम wa_init_start(काष्ठा i915_wa_list *wal, स्थिर अक्षर *name, स्थिर अक्षर *engine_name)
अणु
	wal->name = name;
	wal->engine_name = engine_name;
पूर्ण

#घोषणा WA_LIST_CHUNK (1 << 4)

अटल व्योम wa_init_finish(काष्ठा i915_wa_list *wal)
अणु
	/* Trim unused entries. */
	अगर (!IS_ALIGNED(wal->count, WA_LIST_CHUNK)) अणु
		काष्ठा i915_wa *list = kmemdup(wal->list,
					       wal->count * माप(*list),
					       GFP_KERNEL);

		अगर (list) अणु
			kमुक्त(wal->list);
			wal->list = list;
		पूर्ण
	पूर्ण

	अगर (!wal->count)
		वापस;

	DRM_DEBUG_DRIVER("Initialized %u %s workarounds on %s\n",
			 wal->wa_count, wal->name, wal->engine_name);
पूर्ण

अटल व्योम _wa_add(काष्ठा i915_wa_list *wal, स्थिर काष्ठा i915_wa *wa)
अणु
	अचिन्हित पूर्णांक addr = i915_mmio_reg_offset(wa->reg);
	अचिन्हित पूर्णांक start = 0, end = wal->count;
	स्थिर अचिन्हित पूर्णांक grow = WA_LIST_CHUNK;
	काष्ठा i915_wa *wa_;

	GEM_BUG_ON(!is_घातer_of_2(grow));

	अगर (IS_ALIGNED(wal->count, grow)) अणु /* Either uninitialized or full. */
		काष्ठा i915_wa *list;

		list = kदो_स्मृति_array(ALIGN(wal->count + 1, grow), माप(*wa),
				     GFP_KERNEL);
		अगर (!list) अणु
			DRM_ERROR("No space for workaround init!\n");
			वापस;
		पूर्ण

		अगर (wal->list) अणु
			स_नकल(list, wal->list, माप(*wa) * wal->count);
			kमुक्त(wal->list);
		पूर्ण

		wal->list = list;
	पूर्ण

	जबतक (start < end) अणु
		अचिन्हित पूर्णांक mid = start + (end - start) / 2;

		अगर (i915_mmio_reg_offset(wal->list[mid].reg) < addr) अणु
			start = mid + 1;
		पूर्ण अन्यथा अगर (i915_mmio_reg_offset(wal->list[mid].reg) > addr) अणु
			end = mid;
		पूर्ण अन्यथा अणु
			wa_ = &wal->list[mid];

			अगर ((wa->clr | wa_->clr) && !(wa->clr & ~wa_->clr)) अणु
				DRM_ERROR("Discarding overwritten w/a for reg %04x (clear: %08x, set: %08x)\n",
					  i915_mmio_reg_offset(wa_->reg),
					  wa_->clr, wa_->set);

				wa_->set &= ~wa->clr;
			पूर्ण

			wal->wa_count++;
			wa_->set |= wa->set;
			wa_->clr |= wa->clr;
			wa_->पढ़ो |= wa->पढ़ो;
			वापस;
		पूर्ण
	पूर्ण

	wal->wa_count++;
	wa_ = &wal->list[wal->count++];
	*wa_ = *wa;

	जबतक (wa_-- > wal->list) अणु
		GEM_BUG_ON(i915_mmio_reg_offset(wa_[0].reg) ==
			   i915_mmio_reg_offset(wa_[1].reg));
		अगर (i915_mmio_reg_offset(wa_[1].reg) >
		    i915_mmio_reg_offset(wa_[0].reg))
			अवरोध;

		swap(wa_[1], wa_[0]);
	पूर्ण
पूर्ण

अटल व्योम wa_add(काष्ठा i915_wa_list *wal, i915_reg_t reg,
		   u32 clear, u32 set, u32 पढ़ो_mask)
अणु
	काष्ठा i915_wa wa = अणु
		.reg  = reg,
		.clr  = clear,
		.set  = set,
		.पढ़ो = पढ़ो_mask,
	पूर्ण;

	_wa_add(wal, &wa);
पूर्ण

अटल व्योम
wa_ग_लिखो_clr_set(काष्ठा i915_wa_list *wal, i915_reg_t reg, u32 clear, u32 set)
अणु
	wa_add(wal, reg, clear, set, clear);
पूर्ण

अटल व्योम
wa_ग_लिखो(काष्ठा i915_wa_list *wal, i915_reg_t reg, u32 set)
अणु
	wa_ग_लिखो_clr_set(wal, reg, ~0, set);
पूर्ण

अटल व्योम
wa_ग_लिखो_or(काष्ठा i915_wa_list *wal, i915_reg_t reg, u32 set)
अणु
	wa_ग_लिखो_clr_set(wal, reg, set, set);
पूर्ण

अटल व्योम
wa_ग_लिखो_clr(काष्ठा i915_wa_list *wal, i915_reg_t reg, u32 clr)
अणु
	wa_ग_लिखो_clr_set(wal, reg, clr, 0);
पूर्ण

/*
 * WA operations on "masked register". A masked रेजिस्टर has the upper 16 bits
 * करोcumented as "masked" in b-spec. Its purpose is to allow writing to just a
 * portion of the रेजिस्टर without a rmw: you simply ग_लिखो in the upper 16 bits
 * the mask of bits you are going to modअगरy.
 *
 * The wa_masked_* family of functions alपढ़ोy करोes the necessary operations to
 * calculate the mask based on the parameters passed, so user only has to
 * provide the lower 16 bits of that रेजिस्टर.
 */

अटल व्योम
wa_masked_en(काष्ठा i915_wa_list *wal, i915_reg_t reg, u32 val)
अणु
	wa_add(wal, reg, 0, _MASKED_BIT_ENABLE(val), val);
पूर्ण

अटल व्योम
wa_masked_dis(काष्ठा i915_wa_list *wal, i915_reg_t reg, u32 val)
अणु
	wa_add(wal, reg, 0, _MASKED_BIT_DISABLE(val), val);
पूर्ण

अटल व्योम
wa_masked_field_set(काष्ठा i915_wa_list *wal, i915_reg_t reg,
		    u32 mask, u32 val)
अणु
	wa_add(wal, reg, 0, _MASKED_FIELD(mask, val), mask);
पूर्ण

अटल व्योम gen6_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				      काष्ठा i915_wa_list *wal)
अणु
	wa_masked_en(wal, INSTPM, INSTPM_FORCE_ORDERING);
पूर्ण

अटल व्योम gen7_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				      काष्ठा i915_wa_list *wal)
अणु
	wa_masked_en(wal, INSTPM, INSTPM_FORCE_ORDERING);
पूर्ण

अटल व्योम gen8_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				      काष्ठा i915_wa_list *wal)
अणु
	wa_masked_en(wal, INSTPM, INSTPM_FORCE_ORDERING);

	/* WaDisableAsyncFlipPerfMode:bdw,chv */
	wa_masked_en(wal, MI_MODE, ASYNC_FLIP_PERF_DISABLE);

	/* WaDisablePartialInstShootकरोwn:bdw,chv */
	wa_masked_en(wal, GEN8_ROW_CHICKEN,
		     PARTIAL_INSTRUCTION_SHOOTDOWN_DISABLE);

	/* Use Force Non-Coherent whenever executing a 3D context. This is a
	 * workaround क्रम a possible hang in the unlikely event a TLB
	 * invalidation occurs during a PSD flush.
	 */
	/* WaForceEnableNonCoherent:bdw,chv */
	/* WaHdcDisableFetchWhenMasked:bdw,chv */
	wa_masked_en(wal, HDC_CHICKEN0,
		     HDC_DONOT_FETCH_MEM_WHEN_MASKED |
		     HDC_FORCE_NON_COHERENT);

	/* From the Haswell PRM, Command Reference: Registers, CACHE_MODE_0:
	 * "The Hierarchical Z RAW Stall Optimization allows non-overlapping
	 *  polygons in the same 8x4 pixel/sample area to be processed without
	 *  stalling रुकोing क्रम the earlier ones to ग_लिखो to Hierarchical Z
	 *  buffer."
	 *
	 * This optimization is off by शेष क्रम BDW and CHV; turn it on.
	 */
	wa_masked_dis(wal, CACHE_MODE_0_GEN7, HIZ_RAW_STALL_OPT_DISABLE);

	/* Wa4x4STCOptimizationDisable:bdw,chv */
	wa_masked_en(wal, CACHE_MODE_1, GEN8_4x4_STC_OPTIMIZATION_DISABLE);

	/*
	 * BSpec recommends 8x4 when MSAA is used,
	 * however in practice 16x4 seems fastest.
	 *
	 * Note that PS/WM thपढ़ो counts depend on the WIZ hashing
	 * disable bit, which we करोn't touch here, but it's good
	 * to keep in mind (see 3DSTATE_PS and 3DSTATE_WM).
	 */
	wa_masked_field_set(wal, GEN7_GT_MODE,
			    GEN6_WIZ_HASHING_MASK,
			    GEN6_WIZ_HASHING_16x4);
पूर्ण

अटल व्योम bdw_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	gen8_ctx_workarounds_init(engine, wal);

	/* WaDisableThपढ़ोStallDopClockGating:bdw (pre-production) */
	wa_masked_en(wal, GEN8_ROW_CHICKEN, STALL_DOP_GATING_DISABLE);

	/* WaDisableDopClockGating:bdw
	 *
	 * Also see the related UCGTCL1 ग_लिखो in bdw_init_घड़ी_gating()
	 * to disable EUTC घड़ी gating.
	 */
	wa_masked_en(wal, GEN7_ROW_CHICKEN2,
		     DOP_CLOCK_GATING_DISABLE);

	wa_masked_en(wal, HALF_SLICE_CHICKEN3,
		     GEN8_SAMPLER_POWER_BYPASS_DIS);

	wa_masked_en(wal, HDC_CHICKEN0,
		     /* WaForceContextSaveRestoreNonCoherent:bdw */
		     HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT |
		     /* WaDisableFenceDestinationToSLM:bdw (pre-prod) */
		     (IS_BDW_GT3(i915) ? HDC_FENCE_DEST_SLM_DISABLE : 0));
पूर्ण

अटल व्योम chv_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	gen8_ctx_workarounds_init(engine, wal);

	/* WaDisableThपढ़ोStallDopClockGating:chv */
	wa_masked_en(wal, GEN8_ROW_CHICKEN, STALL_DOP_GATING_DISABLE);

	/* Improve HiZ throughput on CHV. */
	wa_masked_en(wal, HIZ_CHICKEN, CHV_HZ_8X8_MODE_IN_1X);
पूर्ण

अटल व्योम gen9_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				      काष्ठा i915_wa_list *wal)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	अगर (HAS_LLC(i915)) अणु
		/* WaCompressedResourceSamplerPbeMediaNewHashMode:skl,kbl
		 *
		 * Must match Display Engine. See
		 * WaCompressedResourceDisplayNewHashMode.
		 */
		wa_masked_en(wal, COMMON_SLICE_CHICKEN2,
			     GEN9_PBE_COMPRESSED_HASH_SELECTION);
		wa_masked_en(wal, GEN9_HALF_SLICE_CHICKEN7,
			     GEN9_SAMPLER_HASH_COMPRESSED_READ_ADDR);
	पूर्ण

	/* WaClearFlowControlGpgpuContextSave:skl,bxt,kbl,glk,cfl */
	/* WaDisablePartialInstShootकरोwn:skl,bxt,kbl,glk,cfl */
	wa_masked_en(wal, GEN8_ROW_CHICKEN,
		     FLOW_CONTROL_ENABLE |
		     PARTIAL_INSTRUCTION_SHOOTDOWN_DISABLE);

	/* WaEnableYV12BugFixInHalfSliceChicken7:skl,bxt,kbl,glk,cfl */
	/* WaEnableSamplerGPGPUPreemptionSupport:skl,bxt,kbl,cfl */
	wa_masked_en(wal, GEN9_HALF_SLICE_CHICKEN7,
		     GEN9_ENABLE_YV12_BUGFIX |
		     GEN9_ENABLE_GPGPU_PREEMPTION);

	/* Wa4x4STCOptimizationDisable:skl,bxt,kbl,glk,cfl */
	/* WaDisablePartialResolveInVc:skl,bxt,kbl,cfl */
	wa_masked_en(wal, CACHE_MODE_1,
		     GEN8_4x4_STC_OPTIMIZATION_DISABLE |
		     GEN9_PARTIAL_RESOLVE_IN_VC_DISABLE);

	/* WaCcsTlbPrefetchDisable:skl,bxt,kbl,glk,cfl */
	wa_masked_dis(wal, GEN9_HALF_SLICE_CHICKEN5,
		      GEN9_CCS_TLB_PREFETCH_ENABLE);

	/* WaForceContextSaveRestoreNonCoherent:skl,bxt,kbl,cfl */
	wa_masked_en(wal, HDC_CHICKEN0,
		     HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT |
		     HDC_FORCE_CSR_NON_COHERENT_OVR_DISABLE);

	/* WaForceEnableNonCoherent and WaDisableHDCInvalidation are
	 * both tied to WaForceContextSaveRestoreNonCoherent
	 * in some hsds क्रम skl. We keep the tie क्रम all gen9. The
	 * करोcumentation is a bit hazy and so we want to get common behaviour,
	 * even though there is no clear evidence we would need both on kbl/bxt.
	 * This area has been source of प्रणाली hangs so we play it safe
	 * and mimic the skl regardless of what bspec says.
	 *
	 * Use Force Non-Coherent whenever executing a 3D context. This
	 * is a workaround क्रम a possible hang in the unlikely event
	 * a TLB invalidation occurs during a PSD flush.
	 */

	/* WaForceEnableNonCoherent:skl,bxt,kbl,cfl */
	wa_masked_en(wal, HDC_CHICKEN0,
		     HDC_FORCE_NON_COHERENT);

	/* WaDisableSamplerPowerBypassForSOPingPong:skl,bxt,kbl,cfl */
	अगर (IS_SKYLAKE(i915) ||
	    IS_KABYLAKE(i915) ||
	    IS_COFFEELAKE(i915) ||
	    IS_COMETLAKE(i915))
		wa_masked_en(wal, HALF_SLICE_CHICKEN3,
			     GEN8_SAMPLER_POWER_BYPASS_DIS);

	/* WaDisableSTUnitPowerOptimization:skl,bxt,kbl,glk,cfl */
	wa_masked_en(wal, HALF_SLICE_CHICKEN2, GEN8_ST_PO_DISABLE);

	/*
	 * Supporting preemption with fine-granularity requires changes in the
	 * batch buffer programming. Since we can't अवरोध old userspace, we
	 * need to set our शेष preemption level to safe value. Userspace is
	 * still able to use more fine-grained preemption levels, since in
	 * WaEnablePreemptionGranularityControlByUMD we're whitelisting the
	 * per-ctx रेजिस्टर. As such, WaDisableअणु3D,GPGPUपूर्णMidCmdPreemption are
	 * not real HW workarounds, but merely a way to start using preemption
	 * जबतक मुख्यtaining old contract with userspace.
	 */

	/* WaDisable3DMidCmdPreemption:skl,bxt,glk,cfl,[cnl] */
	wa_masked_dis(wal, GEN8_CS_CHICKEN1, GEN9_PREEMPT_3D_OBJECT_LEVEL);

	/* WaDisableGPGPUMidCmdPreemption:skl,bxt,blk,cfl,[cnl] */
	wa_masked_field_set(wal, GEN8_CS_CHICKEN1,
			    GEN9_PREEMPT_GPGPU_LEVEL_MASK,
			    GEN9_PREEMPT_GPGPU_COMMAND_LEVEL);

	/* WaClearHIZ_WM_CHICKEN3:bxt,glk */
	अगर (IS_GEN9_LP(i915))
		wa_masked_en(wal, GEN9_WM_CHICKEN3, GEN9_FACTOR_IN_CLR_VAL_HIZ);
पूर्ण

अटल व्योम skl_tune_iz_hashing(काष्ठा पूर्णांकel_engine_cs *engine,
				काष्ठा i915_wa_list *wal)
अणु
	काष्ठा पूर्णांकel_gt *gt = engine->gt;
	u8 vals[3] = अणु 0, 0, 0 पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		u8 ss;

		/*
		 * Only consider slices where one, and only one, subslice has 7
		 * EUs
		 */
		अगर (!is_घातer_of_2(gt->info.sseu.subslice_7eu[i]))
			जारी;

		/*
		 * subslice_7eu[i] != 0 (because of the check above) and
		 * ss_max == 4 (maximum number of subslices possible per slice)
		 *
		 * ->    0 <= ss <= 3;
		 */
		ss = ffs(gt->info.sseu.subslice_7eu[i]) - 1;
		vals[i] = 3 - ss;
	पूर्ण

	अगर (vals[0] == 0 && vals[1] == 0 && vals[2] == 0)
		वापस;

	/* Tune IZ hashing. See पूर्णांकel_device_info_runसमय_init() */
	wa_masked_field_set(wal, GEN7_GT_MODE,
			    GEN9_IZ_HASHING_MASK(2) |
			    GEN9_IZ_HASHING_MASK(1) |
			    GEN9_IZ_HASHING_MASK(0),
			    GEN9_IZ_HASHING(2, vals[2]) |
			    GEN9_IZ_HASHING(1, vals[1]) |
			    GEN9_IZ_HASHING(0, vals[0]));
पूर्ण

अटल व्योम skl_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	gen9_ctx_workarounds_init(engine, wal);
	skl_tune_iz_hashing(engine, wal);
पूर्ण

अटल व्योम bxt_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	gen9_ctx_workarounds_init(engine, wal);

	/* WaDisableThपढ़ोStallDopClockGating:bxt */
	wa_masked_en(wal, GEN8_ROW_CHICKEN,
		     STALL_DOP_GATING_DISABLE);

	/* WaToEnableHwFixForPushConstHWBug:bxt */
	wa_masked_en(wal, COMMON_SLICE_CHICKEN2,
		     GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);
पूर्ण

अटल व्योम kbl_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	gen9_ctx_workarounds_init(engine, wal);

	/* WaToEnableHwFixForPushConstHWBug:kbl */
	अगर (IS_KBL_GT_STEP(i915, STEP_C0, STEP_FOREVER))
		wa_masked_en(wal, COMMON_SLICE_CHICKEN2,
			     GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	/* WaDisableSbeCacheDispatchPortSharing:kbl */
	wa_masked_en(wal, GEN7_HALF_SLICE_CHICKEN1,
		     GEN7_SBE_SS_CACHE_DISPATCH_PORT_SHARING_DISABLE);
पूर्ण

अटल व्योम glk_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	gen9_ctx_workarounds_init(engine, wal);

	/* WaToEnableHwFixForPushConstHWBug:glk */
	wa_masked_en(wal, COMMON_SLICE_CHICKEN2,
		     GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);
पूर्ण

अटल व्योम cfl_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	gen9_ctx_workarounds_init(engine, wal);

	/* WaToEnableHwFixForPushConstHWBug:cfl */
	wa_masked_en(wal, COMMON_SLICE_CHICKEN2,
		     GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	/* WaDisableSbeCacheDispatchPortSharing:cfl */
	wa_masked_en(wal, GEN7_HALF_SLICE_CHICKEN1,
		     GEN7_SBE_SS_CACHE_DISPATCH_PORT_SHARING_DISABLE);
पूर्ण

अटल व्योम cnl_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	/* WaForceContextSaveRestoreNonCoherent:cnl */
	wa_masked_en(wal, CNL_HDC_CHICKEN0,
		     HDC_FORCE_CONTEXT_SAVE_RESTORE_NON_COHERENT);

	/* WaDisableReplayBufferBankArbitrationOptimization:cnl */
	wa_masked_en(wal, COMMON_SLICE_CHICKEN2,
		     GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	/* WaPushConstantDereferenceHoldDisable:cnl */
	wa_masked_en(wal, GEN7_ROW_CHICKEN2, PUSH_CONSTANT_DEREF_DISABLE);

	/* FtrEnableFastAnisoL1BankingFix:cnl */
	wa_masked_en(wal, HALF_SLICE_CHICKEN3, CNL_FAST_ANISO_L1_BANKING_FIX);

	/* WaDisable3DMidCmdPreemption:cnl */
	wa_masked_dis(wal, GEN8_CS_CHICKEN1, GEN9_PREEMPT_3D_OBJECT_LEVEL);

	/* WaDisableGPGPUMidCmdPreemption:cnl */
	wa_masked_field_set(wal, GEN8_CS_CHICKEN1,
			    GEN9_PREEMPT_GPGPU_LEVEL_MASK,
			    GEN9_PREEMPT_GPGPU_COMMAND_LEVEL);

	/* WaDisableEarlyEOT:cnl */
	wa_masked_en(wal, GEN8_ROW_CHICKEN, DISABLE_EARLY_EOT);
पूर्ण

अटल व्योम icl_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	/* WaDisableBankHangMode:icl */
	wa_ग_लिखो(wal,
		 GEN8_L3CNTLREG,
		 पूर्णांकel_uncore_पढ़ो(engine->uncore, GEN8_L3CNTLREG) |
		 GEN8_ERRDETBCTRL);

	/* Wa_1604370585:icl (pre-prod)
	 * Formerly known as WaPushConstantDereferenceHoldDisable
	 */
	अगर (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_B0))
		wa_masked_en(wal, GEN7_ROW_CHICKEN2,
			     PUSH_CONSTANT_DEREF_DISABLE);

	/* WaForceEnableNonCoherent:icl
	 * This is not the same workaround as in early Gen9 platक्रमms, where
	 * lacking this could cause प्रणाली hangs, but coherency perक्रमmance
	 * overhead is high and only a few compute workloads really need it
	 * (the रेजिस्टर is whitelisted in hardware now, so UMDs can opt in
	 * क्रम coherency अगर they have a good reason).
	 */
	wa_masked_en(wal, ICL_HDC_MODE, HDC_FORCE_NON_COHERENT);

	/* Wa_2006611047:icl (pre-prod)
	 * Formerly known as WaDisableImprovedTdlClkGating
	 */
	अगर (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_A0))
		wa_masked_en(wal, GEN7_ROW_CHICKEN2,
			     GEN11_TDL_CLOCK_GATING_FIX_DISABLE);

	/* Wa_2006665173:icl (pre-prod) */
	अगर (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_A0))
		wa_masked_en(wal, GEN11_COMMON_SLICE_CHICKEN3,
			     GEN11_BLEND_EMB_FIX_DISABLE_IN_RCC);

	/* WaEnableFloatBlendOptimization:icl */
	wa_ग_लिखो_clr_set(wal,
			 GEN10_CACHE_MODE_SS,
			 0, /* ग_लिखो-only, so skip validation */
			 _MASKED_BIT_ENABLE(FLOAT_BLEND_OPTIMIZATION_ENABLE));

	/* WaDisableGPGPUMidThपढ़ोPreemption:icl */
	wa_masked_field_set(wal, GEN8_CS_CHICKEN1,
			    GEN9_PREEMPT_GPGPU_LEVEL_MASK,
			    GEN9_PREEMPT_GPGPU_THREAD_GROUP_LEVEL);

	/* allow headerless messages क्रम preemptible GPGPU context */
	wa_masked_en(wal, GEN10_SAMPLER_MODE,
		     GEN11_SAMPLER_ENABLE_HEADLESS_MSG);

	/* Wa_1604278689:icl,ehl */
	wa_ग_लिखो(wal, IVB_FBC_RT_BASE, 0xFFFFFFFF & ~ILK_FBC_RT_VALID);
	wa_ग_लिखो_clr_set(wal, IVB_FBC_RT_BASE_UPPER,
			 0, /* ग_लिखो-only रेजिस्टर; skip validation */
			 0xFFFFFFFF);

	/* Wa_1406306137:icl,ehl */
	wa_masked_en(wal, GEN9_ROW_CHICKEN4, GEN11_DIS_PICK_2ND_EU);
पूर्ण

अटल व्योम gen12_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				       काष्ठा i915_wa_list *wal)
अणु
	/*
	 * Wa_1409142259:tgl
	 * Wa_1409347922:tgl
	 * Wa_1409252684:tgl
	 * Wa_1409217633:tgl
	 * Wa_1409207793:tgl
	 * Wa_1409178076:tgl
	 * Wa_1408979724:tgl
	 * Wa_14010443199:rkl
	 * Wa_14010698770:rkl
	 */
	wa_masked_en(wal, GEN11_COMMON_SLICE_CHICKEN3,
		     GEN12_DISABLE_CPS_AWARE_COLOR_PIPE);

	/* WaDisableGPGPUMidThपढ़ोPreemption:gen12 */
	wa_masked_field_set(wal, GEN8_CS_CHICKEN1,
			    GEN9_PREEMPT_GPGPU_LEVEL_MASK,
			    GEN9_PREEMPT_GPGPU_THREAD_GROUP_LEVEL);
पूर्ण

अटल व्योम tgl_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	gen12_ctx_workarounds_init(engine, wal);

	/*
	 * Wa_1604555607:tgl,rkl
	 *
	 * Note that the implementation of this workaround is further modअगरied
	 * according to the FF_MODE2 guidance given by Wa_1608008084:gen12.
	 * FF_MODE2 रेजिस्टर will वापस the wrong value when पढ़ो. The शेष
	 * value क्रम this रेजिस्टर is zero क्रम all fields and there are no bit
	 * masks. So instead of करोing a RMW we should just ग_लिखो the GS Timer
	 * and TDS समयr values क्रम Wa_1604555607 and Wa_16011163337.
	 */
	wa_add(wal,
	       FF_MODE2,
	       FF_MODE2_GS_TIMER_MASK | FF_MODE2_TDS_TIMER_MASK,
	       FF_MODE2_GS_TIMER_224  | FF_MODE2_TDS_TIMER_128,
	       0);
पूर्ण

अटल व्योम dg1_ctx_workarounds_init(काष्ठा पूर्णांकel_engine_cs *engine,
				     काष्ठा i915_wa_list *wal)
अणु
	gen12_ctx_workarounds_init(engine, wal);

	/* Wa_1409044764 */
	wa_masked_dis(wal, GEN11_COMMON_SLICE_CHICKEN3,
		      DG1_FLOAT_POINT_BLEND_OPT_STRICT_MODE_EN);

	/* Wa_22010493298 */
	wa_masked_en(wal, HIZ_CHICKEN,
		     DG1_HZ_READ_SUPPRESSION_OPTIMIZATION_DISABLE);

	/*
	 * Wa_16011163337
	 *
	 * Like in tgl_ctx_workarounds_init(), पढ़ो verअगरication is ignored due
	 * to Wa_1608008084.
	 */
	wa_add(wal,
	       FF_MODE2,
	       FF_MODE2_GS_TIMER_MASK, FF_MODE2_GS_TIMER_224, 0);
पूर्ण

अटल व्योम
__पूर्णांकel_engine_init_ctx_wa(काष्ठा पूर्णांकel_engine_cs *engine,
			   काष्ठा i915_wa_list *wal,
			   स्थिर अक्षर *name)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	अगर (engine->class != RENDER_CLASS)
		वापस;

	wa_init_start(wal, name, engine->name);

	अगर (IS_DG1(i915))
		dg1_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_ALDERLAKE_S(i915) || IS_ROCKETLAKE(i915) ||
		 IS_TIGERLAKE(i915))
		tgl_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_GEN(i915, 12))
		gen12_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_GEN(i915, 11))
		icl_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_CANNONLAKE(i915))
		cnl_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_COFFEELAKE(i915) || IS_COMETLAKE(i915))
		cfl_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_GEMINILAKE(i915))
		glk_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_KABYLAKE(i915))
		kbl_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_BROXTON(i915))
		bxt_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_SKYLAKE(i915))
		skl_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_CHERRYVIEW(i915))
		chv_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_BROADWELL(i915))
		bdw_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_GEN(i915, 7))
		gen7_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (IS_GEN(i915, 6))
		gen6_ctx_workarounds_init(engine, wal);
	अन्यथा अगर (INTEL_GEN(i915) < 8)
		;
	अन्यथा
		MISSING_CASE(INTEL_GEN(i915));

	wa_init_finish(wal);
पूर्ण

व्योम पूर्णांकel_engine_init_ctx_wa(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	__पूर्णांकel_engine_init_ctx_wa(engine, &engine->ctx_wa_list, "context");
पूर्ण

पूर्णांक पूर्णांकel_engine_emit_ctx_wa(काष्ठा i915_request *rq)
अणु
	काष्ठा i915_wa_list *wal = &rq->engine->ctx_wa_list;
	काष्ठा i915_wa *wa;
	अचिन्हित पूर्णांक i;
	u32 *cs;
	पूर्णांक ret;

	अगर (wal->count == 0)
		वापस 0;

	ret = rq->engine->emit_flush(rq, EMIT_BARRIER);
	अगर (ret)
		वापस ret;

	cs = पूर्णांकel_ring_begin(rq, (wal->count * 2 + 2));
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(wal->count);
	क्रम (i = 0, wa = wal->list; i < wal->count; i++, wa++) अणु
		*cs++ = i915_mmio_reg_offset(wa->reg);
		*cs++ = wa->set;
	पूर्ण
	*cs++ = MI_NOOP;

	पूर्णांकel_ring_advance(rq, cs);

	ret = rq->engine->emit_flush(rq, EMIT_BARRIER);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम
gen4_gt_workarounds_init(काष्ठा drm_i915_निजी *i915,
			 काष्ठा i915_wa_list *wal)
अणु
	/* WaDisable_RenderCache_OperationalFlush:gen4,ilk */
	wa_masked_dis(wal, CACHE_MODE_0, RC_OP_FLUSH_ENABLE);
पूर्ण

अटल व्योम
g4x_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	gen4_gt_workarounds_init(i915, wal);

	/* WaDisableRenderCachePipelinedFlush:g4x,ilk */
	wa_masked_en(wal, CACHE_MODE_0, CM0_PIPELINED_RENDER_FLUSH_DISABLE);
पूर्ण

अटल व्योम
ilk_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	g4x_gt_workarounds_init(i915, wal);

	wa_masked_en(wal, _3D_CHICKEN2, _3D_CHICKEN2_WM_READ_PIPELINED);
पूर्ण

अटल व्योम
snb_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
पूर्ण

अटल व्योम
ivb_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	/* Apply the WaDisableRHWOOptimizationForRenderHang:ivb workaround. */
	wa_masked_dis(wal,
		      GEN7_COMMON_SLICE_CHICKEN1,
		      GEN7_CSC1_RHWO_OPT_DISABLE_IN_RCC);

	/* WaApplyL3ControlAndL3ChickenMode:ivb */
	wa_ग_लिखो(wal, GEN7_L3CNTLREG1, GEN7_WA_FOR_GEN7_L3_CONTROL);
	wa_ग_लिखो(wal, GEN7_L3_CHICKEN_MODE_REGISTER, GEN7_WA_L3_CHICKEN_MODE);

	/* WaForceL3Serialization:ivb */
	wa_ग_लिखो_clr(wal, GEN7_L3SQCREG4, L3SQ_URB_READ_CAM_MATCH_DISABLE);
पूर्ण

अटल व्योम
vlv_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	/* WaForceL3Serialization:vlv */
	wa_ग_लिखो_clr(wal, GEN7_L3SQCREG4, L3SQ_URB_READ_CAM_MATCH_DISABLE);

	/*
	 * WaIncreaseL3CreditsForVLVB0:vlv
	 * This is the hardware शेष actually.
	 */
	wa_ग_लिखो(wal, GEN7_L3SQCREG1, VLV_B0_WA_L3SQCREG1_VALUE);
पूर्ण

अटल व्योम
hsw_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	/* L3 caching of data atomics करोesn't work -- disable it. */
	wa_ग_लिखो(wal, HSW_SCRATCH1, HSW_SCRATCH1_L3_DATA_ATOMICS_DISABLE);

	wa_add(wal,
	       HSW_ROW_CHICKEN3, 0,
	       _MASKED_BIT_ENABLE(HSW_ROW_CHICKEN3_L3_GLOBAL_ATOMICS_DISABLE),
		0 /* XXX करोes this reg exist? */);

	/* WaVSRefCountFullक्रमceMissDisable:hsw */
	wa_ग_लिखो_clr(wal, GEN7_FF_THREAD_MODE, GEN7_FF_VS_REF_CNT_FFME);
पूर्ण

अटल व्योम
gen9_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	/* WaDisableKillLogic:bxt,skl,kbl */
	अगर (!IS_COFFEELAKE(i915) && !IS_COMETLAKE(i915))
		wa_ग_लिखो_or(wal,
			    GAM_ECOCHK,
			    ECOCHK_DIS_TLB);

	अगर (HAS_LLC(i915)) अणु
		/* WaCompressedResourceSamplerPbeMediaNewHashMode:skl,kbl
		 *
		 * Must match Display Engine. See
		 * WaCompressedResourceDisplayNewHashMode.
		 */
		wa_ग_लिखो_or(wal,
			    MMCD_MISC_CTRL,
			    MMCD_PCLA | MMCD_HOTSPOT_EN);
	पूर्ण

	/* WaDisableHDCInvalidation:skl,bxt,kbl,cfl */
	wa_ग_लिखो_or(wal,
		    GAM_ECOCHK,
		    BDW_DISABLE_HDC_INVALIDATION);
पूर्ण

अटल व्योम
skl_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	gen9_gt_workarounds_init(i915, wal);

	/* WaDisableGafsUnitClkGating:skl */
	wa_ग_लिखो_or(wal,
		    GEN7_UCGCTL4,
		    GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE);

	/* WaInPlaceDecompressionHang:skl */
	अगर (IS_SKL_REVID(i915, SKL_REVID_H0, REVID_FOREVER))
		wa_ग_लिखो_or(wal,
			    GEN9_GAMT_ECO_REG_RW_IA,
			    GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);
पूर्ण

अटल व्योम
bxt_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	gen9_gt_workarounds_init(i915, wal);

	/* WaInPlaceDecompressionHang:bxt */
	wa_ग_लिखो_or(wal,
		    GEN9_GAMT_ECO_REG_RW_IA,
		    GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);
पूर्ण

अटल व्योम
kbl_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	gen9_gt_workarounds_init(i915, wal);

	/* WaDisableDynamicCreditSharing:kbl */
	अगर (IS_KBL_GT_STEP(i915, 0, STEP_B0))
		wa_ग_लिखो_or(wal,
			    GAMT_CHKN_BIT_REG,
			    GAMT_CHKN_DISABLE_DYNAMIC_CREDIT_SHARING);

	/* WaDisableGafsUnitClkGating:kbl */
	wa_ग_लिखो_or(wal,
		    GEN7_UCGCTL4,
		    GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE);

	/* WaInPlaceDecompressionHang:kbl */
	wa_ग_लिखो_or(wal,
		    GEN9_GAMT_ECO_REG_RW_IA,
		    GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);
पूर्ण

अटल व्योम
glk_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	gen9_gt_workarounds_init(i915, wal);
पूर्ण

अटल व्योम
cfl_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	gen9_gt_workarounds_init(i915, wal);

	/* WaDisableGafsUnitClkGating:cfl */
	wa_ग_लिखो_or(wal,
		    GEN7_UCGCTL4,
		    GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE);

	/* WaInPlaceDecompressionHang:cfl */
	wa_ग_लिखो_or(wal,
		    GEN9_GAMT_ECO_REG_RW_IA,
		    GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);
पूर्ण

अटल व्योम
wa_init_mcr(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	स्थिर काष्ठा sseu_dev_info *sseu = &i915->gt.info.sseu;
	अचिन्हित पूर्णांक slice, subslice;
	u32 l3_en, mcr, mcr_mask;

	GEM_BUG_ON(INTEL_GEN(i915) < 10);

	/*
	 * WaProgramMgsrForL3BankSpecअगरicMmioReads: cnl,icl
	 * L3Banks could be fused off in single slice scenario. If that is
	 * the हाल, we might need to program MCR select to a valid L3Bank
	 * by शेष, to make sure we correctly पढ़ो certain रेजिस्टरs
	 * later on (in the range 0xB100 - 0xB3FF).
	 *
	 * WaProgramMgsrForCorrectSliceSpecअगरicMmioReads:cnl,icl
	 * Beक्रमe any MMIO पढ़ो पूर्णांकo slice/subslice specअगरic रेजिस्टरs, MCR
	 * packet control रेजिस्टर needs to be programmed to poपूर्णांक to any
	 * enabled s/ss pair. Otherwise, incorrect values will be वापसed.
	 * This means each subsequent MMIO पढ़ो will be क्रमwarded to an
	 * specअगरic s/ss combination, but this is OK since these रेजिस्टरs
	 * are consistent across s/ss in almost all हालs. In the rare
	 * occasions, such as INSTDONE, where this value is dependent
	 * on s/ss combo, the पढ़ो should be करोne with पढ़ो_subslice_reg.
	 *
	 * Since GEN8_MCR_SELECTOR contains dual-purpose bits which select both
	 * to which subslice, or to which L3 bank, the respective mmio पढ़ोs
	 * will go, we have to find a common index which works क्रम both
	 * accesses.
	 *
	 * Case where we cannot find a common index क्रमtunately should not
	 * happen in production hardware, so we only emit a warning instead of
	 * implementing something more complex that requires checking the range
	 * of every MMIO पढ़ो.
	 */

	अगर (INTEL_GEN(i915) >= 10 && is_घातer_of_2(sseu->slice_mask)) अणु
		u32 l3_fuse =
			पूर्णांकel_uncore_पढ़ो(&i915->uncore, GEN10_MIRROR_FUSE3) &
			GEN10_L3BANK_MASK;

		drm_dbg(&i915->drm, "L3 fuse = %x\n", l3_fuse);
		l3_en = ~(l3_fuse << GEN10_L3BANK_PAIR_COUNT | l3_fuse);
	पूर्ण अन्यथा अणु
		l3_en = ~0;
	पूर्ण

	slice = fls(sseu->slice_mask) - 1;
	subslice = fls(l3_en & पूर्णांकel_sseu_get_subslices(sseu, slice));
	अगर (!subslice) अणु
		drm_warn(&i915->drm,
			 "No common index found between subslice mask %x and L3 bank mask %x!\n",
			 पूर्णांकel_sseu_get_subslices(sseu, slice), l3_en);
		subslice = fls(l3_en);
		drm_WARN_ON(&i915->drm, !subslice);
	पूर्ण
	subslice--;

	अगर (INTEL_GEN(i915) >= 11) अणु
		mcr = GEN11_MCR_SLICE(slice) | GEN11_MCR_SUBSLICE(subslice);
		mcr_mask = GEN11_MCR_SLICE_MASK | GEN11_MCR_SUBSLICE_MASK;
	पूर्ण अन्यथा अणु
		mcr = GEN8_MCR_SLICE(slice) | GEN8_MCR_SUBSLICE(subslice);
		mcr_mask = GEN8_MCR_SLICE_MASK | GEN8_MCR_SUBSLICE_MASK;
	पूर्ण

	drm_dbg(&i915->drm, "MCR slice/subslice = %x\n", mcr);

	wa_ग_लिखो_clr_set(wal, GEN8_MCR_SELECTOR, mcr_mask, mcr);
पूर्ण

अटल व्योम
cnl_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	wa_init_mcr(i915, wal);

	/* WaInPlaceDecompressionHang:cnl */
	wa_ग_लिखो_or(wal,
		    GEN9_GAMT_ECO_REG_RW_IA,
		    GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);
पूर्ण

अटल व्योम
icl_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	wa_init_mcr(i915, wal);

	/* WaInPlaceDecompressionHang:icl */
	wa_ग_लिखो_or(wal,
		    GEN9_GAMT_ECO_REG_RW_IA,
		    GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);

	/* WaModअगरyGamTlbPartitioning:icl */
	wa_ग_लिखो_clr_set(wal,
			 GEN11_GACB_PERF_CTRL,
			 GEN11_HASH_CTRL_MASK,
			 GEN11_HASH_CTRL_BIT0 | GEN11_HASH_CTRL_BIT4);

	/* Wa_1405766107:icl
	 * Formerly known as WaCL2SFHalfMaxAlloc
	 */
	wa_ग_लिखो_or(wal,
		    GEN11_LSN_UNSLCVC,
		    GEN11_LSN_UNSLCVC_GAFS_HALF_SF_MAXALLOC |
		    GEN11_LSN_UNSLCVC_GAFS_HALF_CL2_MAXALLOC);

	/* Wa_220166154:icl
	 * Formerly known as WaDisCtxReload
	 */
	wa_ग_लिखो_or(wal,
		    GEN8_GAMW_ECO_DEV_RW_IA,
		    GAMW_ECO_DEV_CTX_RELOAD_DISABLE);

	/* Wa_1405779004:icl (pre-prod) */
	अगर (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_A0))
		wa_ग_लिखो_or(wal,
			    SLICE_UNIT_LEVEL_CLKGATE,
			    MSCUNIT_CLKGATE_DIS);

	/* Wa_1406838659:icl (pre-prod) */
	अगर (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_B0))
		wa_ग_लिखो_or(wal,
			    INF_UNIT_LEVEL_CLKGATE,
			    CGPSF_CLKGATE_DIS);

	/* Wa_1406463099:icl
	 * Formerly known as WaGamTlbPendError
	 */
	wa_ग_लिखो_or(wal,
		    GAMT_CHKN_BIT_REG,
		    GAMT_CHKN_DISABLE_L3_COH_PIPE);

	/* Wa_1607087056:icl,ehl,jsl */
	अगर (IS_ICELAKE(i915) ||
	    IS_JSL_EHL_REVID(i915, EHL_REVID_A0, EHL_REVID_A0))
		wa_ग_लिखो_or(wal,
			    SLICE_UNIT_LEVEL_CLKGATE,
			    L3_CLKGATE_DIS | L3_CR2X_CLKGATE_DIS);
पूर्ण

अटल व्योम
gen12_gt_workarounds_init(काष्ठा drm_i915_निजी *i915,
			  काष्ठा i915_wa_list *wal)
अणु
	wa_init_mcr(i915, wal);
पूर्ण

अटल व्योम
tgl_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	gen12_gt_workarounds_init(i915, wal);

	/* Wa_1409420604:tgl */
	अगर (IS_TGL_UY_GT_STEP(i915, STEP_A0, STEP_A0))
		wa_ग_लिखो_or(wal,
			    SUBSLICE_UNIT_LEVEL_CLKGATE2,
			    CPSSUNIT_CLKGATE_DIS);

	/* Wa_1607087056:tgl also know as BUG:1409180338 */
	अगर (IS_TGL_UY_GT_STEP(i915, STEP_A0, STEP_A0))
		wa_ग_लिखो_or(wal,
			    SLICE_UNIT_LEVEL_CLKGATE,
			    L3_CLKGATE_DIS | L3_CR2X_CLKGATE_DIS);

	/* Wa_1408615072:tgl[a0] */
	अगर (IS_TGL_UY_GT_STEP(i915, STEP_A0, STEP_A0))
		wa_ग_लिखो_or(wal, UNSLICE_UNIT_LEVEL_CLKGATE2,
			    VSUNIT_CLKGATE_DIS_TGL);
पूर्ण

अटल व्योम
dg1_gt_workarounds_init(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	gen12_gt_workarounds_init(i915, wal);

	/* Wa_1607087056:dg1 */
	अगर (IS_DG1_REVID(i915, DG1_REVID_A0, DG1_REVID_A0))
		wa_ग_लिखो_or(wal,
			    SLICE_UNIT_LEVEL_CLKGATE,
			    L3_CLKGATE_DIS | L3_CR2X_CLKGATE_DIS);

	/* Wa_1409420604:dg1 */
	अगर (IS_DG1(i915))
		wa_ग_लिखो_or(wal,
			    SUBSLICE_UNIT_LEVEL_CLKGATE2,
			    CPSSUNIT_CLKGATE_DIS);

	/* Wa_1408615072:dg1 */
	/* Empirical testing shows this रेजिस्टर is unaffected by engine reset. */
	अगर (IS_DG1(i915))
		wa_ग_लिखो_or(wal, UNSLICE_UNIT_LEVEL_CLKGATE2,
			    VSUNIT_CLKGATE_DIS_TGL);
पूर्ण

अटल व्योम
gt_init_workarounds(काष्ठा drm_i915_निजी *i915, काष्ठा i915_wa_list *wal)
अणु
	अगर (IS_DG1(i915))
		dg1_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_TIGERLAKE(i915))
		tgl_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_GEN(i915, 12))
		gen12_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_GEN(i915, 11))
		icl_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_CANNONLAKE(i915))
		cnl_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_COFFEELAKE(i915) || IS_COMETLAKE(i915))
		cfl_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_GEMINILAKE(i915))
		glk_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_KABYLAKE(i915))
		kbl_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_BROXTON(i915))
		bxt_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_SKYLAKE(i915))
		skl_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_HASWELL(i915))
		hsw_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_VALLEYVIEW(i915))
		vlv_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_IVYBRIDGE(i915))
		ivb_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_GEN(i915, 6))
		snb_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_GEN(i915, 5))
		ilk_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_G4X(i915))
		g4x_gt_workarounds_init(i915, wal);
	अन्यथा अगर (IS_GEN(i915, 4))
		gen4_gt_workarounds_init(i915, wal);
	अन्यथा अगर (INTEL_GEN(i915) <= 8)
		;
	अन्यथा
		MISSING_CASE(INTEL_GEN(i915));
पूर्ण

व्योम पूर्णांकel_gt_init_workarounds(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_wa_list *wal = &i915->gt_wa_list;

	wa_init_start(wal, "GT", "global");
	gt_init_workarounds(i915, wal);
	wa_init_finish(wal);
पूर्ण

अटल क्रमागत क्रमcewake_करोमुख्यs
wal_get_fw_क्रम_rmw(काष्ठा पूर्णांकel_uncore *uncore, स्थिर काष्ठा i915_wa_list *wal)
अणु
	क्रमागत क्रमcewake_करोमुख्यs fw = 0;
	काष्ठा i915_wa *wa;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0, wa = wal->list; i < wal->count; i++, wa++)
		fw |= पूर्णांकel_uncore_क्रमcewake_क्रम_reg(uncore,
						     wa->reg,
						     FW_REG_READ |
						     FW_REG_WRITE);

	वापस fw;
पूर्ण

अटल bool
wa_verअगरy(स्थिर काष्ठा i915_wa *wa, u32 cur, स्थिर अक्षर *name, स्थिर अक्षर *from)
अणु
	अगर ((cur ^ wa->set) & wa->पढ़ो) अणु
		DRM_ERROR("%s workaround lost on %s! (reg[%x]=0x%x, relevant bits were 0x%x vs expected 0x%x)\n",
			  name, from, i915_mmio_reg_offset(wa->reg),
			  cur, cur & wa->पढ़ो, wa->set & wa->पढ़ो);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
wa_list_apply(काष्ठा पूर्णांकel_uncore *uncore, स्थिर काष्ठा i915_wa_list *wal)
अणु
	क्रमागत क्रमcewake_करोमुख्यs fw;
	अचिन्हित दीर्घ flags;
	काष्ठा i915_wa *wa;
	अचिन्हित पूर्णांक i;

	अगर (!wal->count)
		वापस;

	fw = wal_get_fw_क्रम_rmw(uncore, wal);

	spin_lock_irqsave(&uncore->lock, flags);
	पूर्णांकel_uncore_क्रमcewake_get__locked(uncore, fw);

	क्रम (i = 0, wa = wal->list; i < wal->count; i++, wa++) अणु
		अगर (wa->clr)
			पूर्णांकel_uncore_rmw_fw(uncore, wa->reg, wa->clr, wa->set);
		अन्यथा
			पूर्णांकel_uncore_ग_लिखो_fw(uncore, wa->reg, wa->set);
		अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
			wa_verअगरy(wa,
				  पूर्णांकel_uncore_पढ़ो_fw(uncore, wa->reg),
				  wal->name, "application");
	पूर्ण

	पूर्णांकel_uncore_क्रमcewake_put__locked(uncore, fw);
	spin_unlock_irqrestore(&uncore->lock, flags);
पूर्ण

व्योम पूर्णांकel_gt_apply_workarounds(काष्ठा पूर्णांकel_gt *gt)
अणु
	wa_list_apply(gt->uncore, &gt->i915->gt_wa_list);
पूर्ण

अटल bool wa_list_verअगरy(काष्ठा पूर्णांकel_uncore *uncore,
			   स्थिर काष्ठा i915_wa_list *wal,
			   स्थिर अक्षर *from)
अणु
	काष्ठा i915_wa *wa;
	अचिन्हित पूर्णांक i;
	bool ok = true;

	क्रम (i = 0, wa = wal->list; i < wal->count; i++, wa++)
		ok &= wa_verअगरy(wa,
				पूर्णांकel_uncore_पढ़ो(uncore, wa->reg),
				wal->name, from);

	वापस ok;
पूर्ण

bool पूर्णांकel_gt_verअगरy_workarounds(काष्ठा पूर्णांकel_gt *gt, स्थिर अक्षर *from)
अणु
	वापस wa_list_verअगरy(gt->uncore, &gt->i915->gt_wa_list, from);
पूर्ण

__maybe_unused
अटल bool is_nonpriv_flags_valid(u32 flags)
अणु
	/* Check only valid flag bits are set */
	अगर (flags & ~RING_FORCE_TO_NONPRIV_MASK_VALID)
		वापस false;

	/* NB: Only 3 out of 4 क्रमागत values are valid क्रम access field */
	अगर ((flags & RING_FORCE_TO_NONPRIV_ACCESS_MASK) ==
	    RING_FORCE_TO_NONPRIV_ACCESS_INVALID)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम
whitelist_reg_ext(काष्ठा i915_wa_list *wal, i915_reg_t reg, u32 flags)
अणु
	काष्ठा i915_wa wa = अणु
		.reg = reg
	पूर्ण;

	अगर (GEM_DEBUG_WARN_ON(wal->count >= RING_MAX_NONPRIV_SLOTS))
		वापस;

	अगर (GEM_DEBUG_WARN_ON(!is_nonpriv_flags_valid(flags)))
		वापस;

	wa.reg.reg |= flags;
	_wa_add(wal, &wa);
पूर्ण

अटल व्योम
whitelist_reg(काष्ठा i915_wa_list *wal, i915_reg_t reg)
अणु
	whitelist_reg_ext(wal, reg, RING_FORCE_TO_NONPRIV_ACCESS_RW);
पूर्ण

अटल व्योम gen9_whitelist_build(काष्ठा i915_wa_list *w)
अणु
	/* WaVFEStateAfterPipeControlwithMediaStateClear:skl,bxt,glk,cfl */
	whitelist_reg(w, GEN9_CTX_PREEMPT_REG);

	/* WaEnablePreemptionGranularityControlByUMD:skl,bxt,kbl,cfl,[cnl] */
	whitelist_reg(w, GEN8_CS_CHICKEN1);

	/* WaAllowUMDToModअगरyHDCChicken1:skl,bxt,kbl,glk,cfl */
	whitelist_reg(w, GEN8_HDC_CHICKEN1);

	/* WaSendPushConstantsFromMMIO:skl,bxt */
	whitelist_reg(w, COMMON_SLICE_CHICKEN2);
पूर्ण

अटल व्योम skl_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	अगर (engine->class != RENDER_CLASS)
		वापस;

	gen9_whitelist_build(w);

	/* WaDisableLSQCROPERFक्रमOCL:skl */
	whitelist_reg(w, GEN8_L3SQCREG4);
पूर्ण

अटल व्योम bxt_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (engine->class != RENDER_CLASS)
		वापस;

	gen9_whitelist_build(&engine->whitelist);
पूर्ण

अटल व्योम kbl_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	अगर (engine->class != RENDER_CLASS)
		वापस;

	gen9_whitelist_build(w);

	/* WaDisableLSQCROPERFक्रमOCL:kbl */
	whitelist_reg(w, GEN8_L3SQCREG4);
पूर्ण

अटल व्योम glk_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	अगर (engine->class != RENDER_CLASS)
		वापस;

	gen9_whitelist_build(w);

	/* WA #0862: Userspace has to set "Barrier Mode" to aव्योम hangs. */
	whitelist_reg(w, GEN9_SLICE_COMMON_ECO_CHICKEN1);
पूर्ण

अटल व्योम cfl_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	अगर (engine->class != RENDER_CLASS)
		वापस;

	gen9_whitelist_build(w);

	/*
	 * WaAllowPMDepthAndInvocationCountAccessFromUMD:cfl,whl,cml,aml
	 *
	 * This covers 4 रेजिस्टर which are next to one another :
	 *   - PS_INVOCATION_COUNT
	 *   - PS_INVOCATION_COUNT_UDW
	 *   - PS_DEPTH_COUNT
	 *   - PS_DEPTH_COUNT_UDW
	 */
	whitelist_reg_ext(w, PS_INVOCATION_COUNT,
			  RING_FORCE_TO_NONPRIV_ACCESS_RD |
			  RING_FORCE_TO_NONPRIV_RANGE_4);
पूर्ण

अटल व्योम cml_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	अगर (engine->class != RENDER_CLASS)
		whitelist_reg_ext(w,
				  RING_CTX_TIMESTAMP(engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);

	cfl_whitelist_build(engine);
पूर्ण

अटल व्योम cnl_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	अगर (engine->class != RENDER_CLASS)
		वापस;

	/* WaEnablePreemptionGranularityControlByUMD:cnl */
	whitelist_reg(w, GEN8_CS_CHICKEN1);
पूर्ण

अटल व्योम icl_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	चयन (engine->class) अणु
	हाल RENDER_CLASS:
		/* WaAllowUMDToModअगरyHalfSliceChicken7:icl */
		whitelist_reg(w, GEN9_HALF_SLICE_CHICKEN7);

		/* WaAllowUMDToModअगरySamplerMode:icl */
		whitelist_reg(w, GEN10_SAMPLER_MODE);

		/* WaEnableStateCacheRedirectToCS:icl */
		whitelist_reg(w, GEN9_SLICE_COMMON_ECO_CHICKEN1);

		/*
		 * WaAllowPMDepthAndInvocationCountAccessFromUMD:icl
		 *
		 * This covers 4 रेजिस्टर which are next to one another :
		 *   - PS_INVOCATION_COUNT
		 *   - PS_INVOCATION_COUNT_UDW
		 *   - PS_DEPTH_COUNT
		 *   - PS_DEPTH_COUNT_UDW
		 */
		whitelist_reg_ext(w, PS_INVOCATION_COUNT,
				  RING_FORCE_TO_NONPRIV_ACCESS_RD |
				  RING_FORCE_TO_NONPRIV_RANGE_4);
		अवरोध;

	हाल VIDEO_DECODE_CLASS:
		/* hucStatusRegOffset */
		whitelist_reg_ext(w, _MMIO(0x2000 + engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		/* hucUKernelHdrInfoRegOffset */
		whitelist_reg_ext(w, _MMIO(0x2014 + engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		/* hucStatus2RegOffset */
		whitelist_reg_ext(w, _MMIO(0x23B0 + engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		whitelist_reg_ext(w,
				  RING_CTX_TIMESTAMP(engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		अवरोध;

	शेष:
		whitelist_reg_ext(w,
				  RING_CTX_TIMESTAMP(engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tgl_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	चयन (engine->class) अणु
	हाल RENDER_CLASS:
		/*
		 * WaAllowPMDepthAndInvocationCountAccessFromUMD:tgl
		 * Wa_1408556865:tgl
		 *
		 * This covers 4 रेजिस्टरs which are next to one another :
		 *   - PS_INVOCATION_COUNT
		 *   - PS_INVOCATION_COUNT_UDW
		 *   - PS_DEPTH_COUNT
		 *   - PS_DEPTH_COUNT_UDW
		 */
		whitelist_reg_ext(w, PS_INVOCATION_COUNT,
				  RING_FORCE_TO_NONPRIV_ACCESS_RD |
				  RING_FORCE_TO_NONPRIV_RANGE_4);

		/* Wa_1808121037:tgl */
		whitelist_reg(w, GEN7_COMMON_SLICE_CHICKEN1);

		/* Wa_1806527549:tgl */
		whitelist_reg(w, HIZ_CHICKEN);
		अवरोध;
	शेष:
		whitelist_reg_ext(w,
				  RING_CTX_TIMESTAMP(engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dg1_whitelist_build(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *w = &engine->whitelist;

	tgl_whitelist_build(engine);

	/* GEN:BUG:1409280441:dg1 */
	अगर (IS_DG1_REVID(engine->i915, DG1_REVID_A0, DG1_REVID_A0) &&
	    (engine->class == RENDER_CLASS ||
	     engine->class == COPY_ENGINE_CLASS))
		whitelist_reg_ext(w, RING_ID(engine->mmio_base),
				  RING_FORCE_TO_NONPRIV_ACCESS_RD);
पूर्ण

व्योम पूर्णांकel_engine_init_whitelist(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;
	काष्ठा i915_wa_list *w = &engine->whitelist;

	wa_init_start(w, "whitelist", engine->name);

	अगर (IS_DG1(i915))
		dg1_whitelist_build(engine);
	अन्यथा अगर (IS_GEN(i915, 12))
		tgl_whitelist_build(engine);
	अन्यथा अगर (IS_GEN(i915, 11))
		icl_whitelist_build(engine);
	अन्यथा अगर (IS_CANNONLAKE(i915))
		cnl_whitelist_build(engine);
	अन्यथा अगर (IS_COMETLAKE(i915))
		cml_whitelist_build(engine);
	अन्यथा अगर (IS_COFFEELAKE(i915))
		cfl_whitelist_build(engine);
	अन्यथा अगर (IS_GEMINILAKE(i915))
		glk_whitelist_build(engine);
	अन्यथा अगर (IS_KABYLAKE(i915))
		kbl_whitelist_build(engine);
	अन्यथा अगर (IS_BROXTON(i915))
		bxt_whitelist_build(engine);
	अन्यथा अगर (IS_SKYLAKE(i915))
		skl_whitelist_build(engine);
	अन्यथा अगर (INTEL_GEN(i915) <= 8)
		;
	अन्यथा
		MISSING_CASE(INTEL_GEN(i915));

	wa_init_finish(w);
पूर्ण

व्योम पूर्णांकel_engine_apply_whitelist(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर काष्ठा i915_wa_list *wal = &engine->whitelist;
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	स्थिर u32 base = engine->mmio_base;
	काष्ठा i915_wa *wa;
	अचिन्हित पूर्णांक i;

	अगर (!wal->count)
		वापस;

	क्रम (i = 0, wa = wal->list; i < wal->count; i++, wa++)
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   RING_FORCE_TO_NONPRIV(base, i),
				   i915_mmio_reg_offset(wa->reg));

	/* And clear the rest just in हाल of garbage */
	क्रम (; i < RING_MAX_NONPRIV_SLOTS; i++)
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   RING_FORCE_TO_NONPRIV(base, i),
				   i915_mmio_reg_offset(RING_NOPID(base)));
पूर्ण

अटल व्योम
rcs_engine_wa_init(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा i915_wa_list *wal)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	अगर (IS_DG1_REVID(i915, DG1_REVID_A0, DG1_REVID_A0) ||
	    IS_TGL_UY_GT_STEP(i915, STEP_A0, STEP_A0)) अणु
		/*
		 * Wa_1607138336:tgl[a0],dg1[a0]
		 * Wa_1607063988:tgl[a0],dg1[a0]
		 */
		wa_ग_लिखो_or(wal,
			    GEN9_CTX_PREEMPT_REG,
			    GEN12_DISABLE_POSH_BUSY_FF_DOP_CG);
	पूर्ण

	अगर (IS_TGL_UY_GT_STEP(i915, STEP_A0, STEP_A0)) अणु
		/*
		 * Wa_1606679103:tgl
		 * (see also Wa_1606682166:icl)
		 */
		wa_ग_लिखो_or(wal,
			    GEN7_SARCHKMD,
			    GEN7_DISABLE_SAMPLER_PREFETCH);
	पूर्ण

	अगर (IS_ALDERLAKE_S(i915) || IS_DG1(i915) ||
	    IS_ROCKETLAKE(i915) || IS_TIGERLAKE(i915)) अणु
		/* Wa_1606931601:tgl,rkl,dg1,adl-s */
		wa_masked_en(wal, GEN7_ROW_CHICKEN2, GEN12_DISABLE_EARLY_READ);

		/*
		 * Wa_1407928979:tgl A*
		 * Wa_18011464164:tgl[B0+],dg1[B0+]
		 * Wa_22010931296:tgl[B0+],dg1[B0+]
		 * Wa_14010919138:rkl,dg1,adl-s
		 */
		wa_ग_लिखो_or(wal, GEN7_FF_THREAD_MODE,
			    GEN12_FF_TESSELATION_DOP_GATE_DISABLE);

		/*
		 * Wa_1606700617:tgl,dg1
		 * Wa_22010271021:tgl,rkl,dg1, adl-s
		 */
		wa_masked_en(wal,
			     GEN9_CS_DEBUG_MODE1,
			     FF_DOP_CLOCK_GATE_DISABLE);
	पूर्ण

	अगर (IS_ALDERLAKE_S(i915) || IS_DG1_REVID(i915, DG1_REVID_A0, DG1_REVID_A0) ||
	    IS_ROCKETLAKE(i915) || IS_TIGERLAKE(i915)) अणु
		/* Wa_1409804808:tgl,rkl,dg1[a0],adl-s */
		wa_masked_en(wal, GEN7_ROW_CHICKEN2,
			     GEN12_PUSH_CONST_DEREF_HOLD_DIS);

		/*
		 * Wa_1409085225:tgl
		 * Wa_14010229206:tgl,rkl,dg1[a0],adl-s
		 */
		wa_masked_en(wal, GEN9_ROW_CHICKEN4, GEN12_DISABLE_TDL_PUSH);
	पूर्ण


	अगर (IS_DG1_REVID(i915, DG1_REVID_A0, DG1_REVID_A0) ||
	    IS_ROCKETLAKE(i915) || IS_TIGERLAKE(i915)) अणु
		/*
		 * Wa_1607030317:tgl
		 * Wa_1607186500:tgl
		 * Wa_1607297627:tgl,rkl,dg1[a0]
		 *
		 * On TGL and RKL there are multiple entries क्रम this WA in the
		 * BSpec; some indicate this is an A0-only WA, others indicate
		 * it applies to all steppings so we trust the "all steppings."
		 * For DG1 this only applies to A0.
		 */
		wa_masked_en(wal,
			     GEN6_RC_SLEEP_PSMI_CONTROL,
			     GEN12_WAIT_FOR_EVENT_POWER_DOWN_DISABLE |
			     GEN8_RC_SEMA_IDLE_MSG_DISABLE);
	पूर्ण

	अगर (IS_DG1(i915) || IS_ROCKETLAKE(i915) || IS_TIGERLAKE(i915)) अणु
		/* Wa_1406941453:tgl,rkl,dg1 */
		wa_masked_en(wal,
			     GEN10_SAMPLER_MODE,
			     ENABLE_SMALLPL);
	पूर्ण

	अगर (IS_GEN(i915, 11)) अणु
		/* This is not an Wa. Enable क्रम better image quality */
		wa_masked_en(wal,
			     _3D_CHICKEN3,
			     _3D_CHICKEN3_AA_LINE_QUALITY_FIX_ENABLE);

		/* WaPipelineFlushCoherentLines:icl */
		wa_ग_लिखो_or(wal,
			    GEN8_L3SQCREG4,
			    GEN8_LQSC_FLUSH_COHERENT_LINES);

		/*
		 * Wa_1405543622:icl
		 * Formerly known as WaGAPZPriorityScheme
		 */
		wa_ग_लिखो_or(wal,
			    GEN8_GARBCNTL,
			    GEN11_ARBITRATION_PRIO_ORDER_MASK);

		/*
		 * Wa_1604223664:icl
		 * Formerly known as WaL3BankAddressHashing
		 */
		wa_ग_लिखो_clr_set(wal,
				 GEN8_GARBCNTL,
				 GEN11_HASH_CTRL_EXCL_MASK,
				 GEN11_HASH_CTRL_EXCL_BIT0);
		wa_ग_लिखो_clr_set(wal,
				 GEN11_GLBLINVL,
				 GEN11_BANK_HASH_ADDR_EXCL_MASK,
				 GEN11_BANK_HASH_ADDR_EXCL_BIT0);

		/*
		 * Wa_1405733216:icl
		 * Formerly known as WaDisableCleanEvicts
		 */
		wa_ग_लिखो_or(wal,
			    GEN8_L3SQCREG4,
			    GEN11_LQSC_CLEAN_EVICT_DISABLE);

		/* WaForwardProgressSoftReset:icl */
		wa_ग_लिखो_or(wal,
			    GEN10_SCRATCH_LNCF2,
			    PMFLUSHDONE_LNICRSDROP |
			    PMFLUSH_GAPL3UNBLOCK |
			    PMFLUSHDONE_LNEBLK);

		/* Wa_1406609255:icl (pre-prod) */
		अगर (IS_ICL_REVID(i915, ICL_REVID_A0, ICL_REVID_B0))
			wa_ग_लिखो_or(wal,
				    GEN7_SARCHKMD,
				    GEN7_DISABLE_DEMAND_PREFETCH);

		/* Wa_1606682166:icl */
		wa_ग_लिखो_or(wal,
			    GEN7_SARCHKMD,
			    GEN7_DISABLE_SAMPLER_PREFETCH);

		/* Wa_1409178092:icl */
		wa_ग_लिखो_clr_set(wal,
				 GEN11_SCRATCH2,
				 GEN11_COHERENT_PARTIAL_WRITE_MERGE_ENABLE,
				 0);

		/* WaEnable32PlaneMode:icl */
		wa_masked_en(wal, GEN9_CSFE_CHICKEN1_RCS,
			     GEN11_ENABLE_32_PLANE_MODE);

		/*
		 * Wa_1408615072:icl,ehl  (vsunit)
		 * Wa_1407596294:icl,ehl  (hsunit)
		 */
		wa_ग_लिखो_or(wal, UNSLICE_UNIT_LEVEL_CLKGATE,
			    VSUNIT_CLKGATE_DIS | HSUNIT_CLKGATE_DIS);

		/* Wa_1407352427:icl,ehl */
		wa_ग_लिखो_or(wal, UNSLICE_UNIT_LEVEL_CLKGATE2,
			    PSDUNIT_CLKGATE_DIS);

		/* Wa_1406680159:icl,ehl */
		wa_ग_लिखो_or(wal,
			    SUBSLICE_UNIT_LEVEL_CLKGATE,
			    GWUNIT_CLKGATE_DIS);

		/*
		 * Wa_1408767742:icl[a2..क्रमever],ehl[all]
		 * Wa_1605460711:icl[a0..c0]
		 */
		wa_ग_लिखो_or(wal,
			    GEN7_FF_THREAD_MODE,
			    GEN12_FF_TESSELATION_DOP_GATE_DISABLE);

		/* Wa_22010271021:ehl */
		अगर (IS_JSL_EHL(i915))
			wa_masked_en(wal,
				     GEN9_CS_DEBUG_MODE1,
				     FF_DOP_CLOCK_GATE_DISABLE);
	पूर्ण

	अगर (IS_GEN_RANGE(i915, 9, 12)) अणु
		/* FtrPerCtxtPreemptionGranularityControl:skl,bxt,kbl,cfl,cnl,icl,tgl */
		wa_masked_en(wal,
			     GEN7_FF_SLICE_CS_CHICKEN1,
			     GEN9_FFSC_PERCTX_PREEMPT_CTRL);
	पूर्ण

	अगर (IS_SKYLAKE(i915) ||
	    IS_KABYLAKE(i915) ||
	    IS_COFFEELAKE(i915) ||
	    IS_COMETLAKE(i915)) अणु
		/* WaEnableGapsTsvCreditFix:skl,kbl,cfl */
		wa_ग_लिखो_or(wal,
			    GEN8_GARBCNTL,
			    GEN9_GAPS_TSV_CREDIT_DISABLE);
	पूर्ण

	अगर (IS_BROXTON(i915)) अणु
		/* WaDisablePooledEuLoadBalancingFix:bxt */
		wa_masked_en(wal,
			     FF_SLICE_CS_CHICKEN2,
			     GEN9_POOLED_EU_LOAD_BALANCING_FIX_DISABLE);
	पूर्ण

	अगर (IS_GEN(i915, 9)) अणु
		/* WaContextSwitchWithConcurrentTLBInvalidate:skl,bxt,kbl,glk,cfl */
		wa_masked_en(wal,
			     GEN9_CSFE_CHICKEN1_RCS,
			     GEN9_PREEMPT_GPGPU_SYNC_SWITCH_DISABLE);

		/* WaEnableLbsSlaRetryTimerDecrement:skl,bxt,kbl,glk,cfl */
		wa_ग_लिखो_or(wal,
			    BDW_SCRATCH1,
			    GEN9_LBS_SLA_RETRY_TIMER_DECREMENT_ENABLE);

		/* WaProgramL3SqcReg1DefaultForPerf:bxt,glk */
		अगर (IS_GEN9_LP(i915))
			wa_ग_लिखो_clr_set(wal,
					 GEN8_L3SQCREG1,
					 L3_PRIO_CREDITS_MASK,
					 L3_GENERAL_PRIO_CREDITS(62) |
					 L3_HIGH_PRIO_CREDITS(2));

		/* WaOCLCoherentLineFlush:skl,bxt,kbl,cfl */
		wa_ग_लिखो_or(wal,
			    GEN8_L3SQCREG4,
			    GEN8_LQSC_FLUSH_COHERENT_LINES);

		/* Disable atomics in L3 to prevent unrecoverable hangs */
		wa_ग_लिखो_clr_set(wal, GEN9_SCRATCH_LNCF1,
				 GEN9_LNCF_NONIA_COHERENT_ATOMICS_ENABLE, 0);
		wa_ग_लिखो_clr_set(wal, GEN8_L3SQCREG4,
				 GEN8_LQSQ_NONIA_COHERENT_ATOMICS_ENABLE, 0);
		wa_ग_लिखो_clr_set(wal, GEN9_SCRATCH1,
				 EVICTION_PERF_FIX_ENABLE, 0);
	पूर्ण

	अगर (IS_HASWELL(i915)) अणु
		/* WaSampleCChickenBitEnable:hsw */
		wa_masked_en(wal,
			     HALF_SLICE_CHICKEN3, HSW_SAMPLE_C_PERFORMANCE);

		wa_masked_dis(wal,
			      CACHE_MODE_0_GEN7,
			      /* enable HiZ Raw Stall Optimization */
			      HIZ_RAW_STALL_OPT_DISABLE);

		/* WaDisable4x2SubspanOptimization:hsw */
		wa_masked_en(wal, CACHE_MODE_1, PIXEL_SUBSPAN_COLLECT_OPT_DISABLE);
	पूर्ण

	अगर (IS_VALLEYVIEW(i915)) अणु
		/* WaDisableEarlyCull:vlv */
		wa_masked_en(wal,
			     _3D_CHICKEN3,
			     _3D_CHICKEN_SF_DISABLE_OBJEND_CULL);

		/*
		 * WaVSThपढ़ोDispatchOverride:ivb,vlv
		 *
		 * This actually overrides the dispatch
		 * mode क्रम all thपढ़ो types.
		 */
		wa_ग_लिखो_clr_set(wal,
				 GEN7_FF_THREAD_MODE,
				 GEN7_FF_SCHED_MASK,
				 GEN7_FF_TS_SCHED_HW |
				 GEN7_FF_VS_SCHED_HW |
				 GEN7_FF_DS_SCHED_HW);

		/* WaPsdDispatchEnable:vlv */
		/* WaDisablePSDDualDispatchEnable:vlv */
		wa_masked_en(wal,
			     GEN7_HALF_SLICE_CHICKEN1,
			     GEN7_MAX_PS_THREAD_DEP |
			     GEN7_PSD_SINGLE_PORT_DISPATCH_ENABLE);
	पूर्ण

	अगर (IS_IVYBRIDGE(i915)) अणु
		/* WaDisableEarlyCull:ivb */
		wa_masked_en(wal,
			     _3D_CHICKEN3,
			     _3D_CHICKEN_SF_DISABLE_OBJEND_CULL);

		अगर (0) अणु /* causes HiZ corruption on ivb:gt1 */
			/* enable HiZ Raw Stall Optimization */
			wa_masked_dis(wal,
				      CACHE_MODE_0_GEN7,
				      HIZ_RAW_STALL_OPT_DISABLE);
		पूर्ण

		/*
		 * WaVSThपढ़ोDispatchOverride:ivb,vlv
		 *
		 * This actually overrides the dispatch
		 * mode क्रम all thपढ़ो types.
		 */
		wa_ग_लिखो_clr_set(wal,
				 GEN7_FF_THREAD_MODE,
				 GEN7_FF_SCHED_MASK,
				 GEN7_FF_TS_SCHED_HW |
				 GEN7_FF_VS_SCHED_HW |
				 GEN7_FF_DS_SCHED_HW);

		/* WaDisablePSDDualDispatchEnable:ivb */
		अगर (IS_IVB_GT1(i915))
			wa_masked_en(wal,
				     GEN7_HALF_SLICE_CHICKEN1,
				     GEN7_PSD_SINGLE_PORT_DISPATCH_ENABLE);
	पूर्ण

	अगर (IS_GEN(i915, 7)) अणु
		/* WaBCSVCSTlbInvalidationMode:ivb,vlv,hsw */
		wa_masked_en(wal,
			     GFX_MODE_GEN7,
			     GFX_TLB_INVALIDATE_EXPLICIT | GFX_REPLAY_MODE);

		/* WaDisable_RenderCache_OperationalFlush:ivb,vlv,hsw */
		wa_masked_dis(wal, CACHE_MODE_0_GEN7, RC_OP_FLUSH_ENABLE);

		/*
		 * BSpec says this must be set, even though
		 * WaDisable4x2SubspanOptimization:ivb,hsw
		 * WaDisable4x2SubspanOptimization isn't listed क्रम VLV.
		 */
		wa_masked_en(wal,
			     CACHE_MODE_1,
			     PIXEL_SUBSPAN_COLLECT_OPT_DISABLE);

		/*
		 * BSpec recommends 8x4 when MSAA is used,
		 * however in practice 16x4 seems fastest.
		 *
		 * Note that PS/WM thपढ़ो counts depend on the WIZ hashing
		 * disable bit, which we करोn't touch here, but it's good
		 * to keep in mind (see 3DSTATE_PS and 3DSTATE_WM).
		 */
		wa_add(wal, GEN7_GT_MODE, 0,
		       _MASKED_FIELD(GEN6_WIZ_HASHING_MASK,
				     GEN6_WIZ_HASHING_16x4),
		       GEN6_WIZ_HASHING_16x4);
	पूर्ण

	अगर (IS_GEN_RANGE(i915, 6, 7))
		/*
		 * We need to disable the AsyncFlip perक्रमmance optimisations in
		 * order to use MI_WAIT_FOR_EVENT within the CS. It should
		 * alपढ़ोy be programmed to '1' on all products.
		 *
		 * WaDisableAsyncFlipPerfMode:snb,ivb,hsw,vlv
		 */
		wa_masked_en(wal,
			     MI_MODE,
			     ASYNC_FLIP_PERF_DISABLE);

	अगर (IS_GEN(i915, 6)) अणु
		/*
		 * Required क्रम the hardware to program scanline values क्रम
		 * रुकोing
		 * WaEnableFlushTlbInvalidationMode:snb
		 */
		wa_masked_en(wal,
			     GFX_MODE,
			     GFX_TLB_INVALIDATE_EXPLICIT);

		/* WaDisableHiZPlanesWhenMSAAEnabled:snb */
		wa_masked_en(wal,
			     _3D_CHICKEN,
			     _3D_CHICKEN_HIZ_PLANE_DISABLE_MSAA_4X_SNB);

		wa_masked_en(wal,
			     _3D_CHICKEN3,
			     /* WaStripsFansDisableFastClipPerक्रमmanceFix:snb */
			     _3D_CHICKEN3_SF_DISABLE_FASTCLIP_CULL |
			     /*
			      * Bspec says:
			      * "This bit must be set अगर 3DSTATE_CLIP clip mode is set
			      * to normal and 3DSTATE_SF number of SF output attributes
			      * is more than 16."
			      */
			     _3D_CHICKEN3_SF_DISABLE_PIPELINED_ATTR_FETCH);

		/*
		 * BSpec recommends 8x4 when MSAA is used,
		 * however in practice 16x4 seems fastest.
		 *
		 * Note that PS/WM thपढ़ो counts depend on the WIZ hashing
		 * disable bit, which we करोn't touch here, but it's good
		 * to keep in mind (see 3DSTATE_PS and 3DSTATE_WM).
		 */
		wa_add(wal,
		       GEN6_GT_MODE, 0,
		       _MASKED_FIELD(GEN6_WIZ_HASHING_MASK, GEN6_WIZ_HASHING_16x4),
		       GEN6_WIZ_HASHING_16x4);

		/* WaDisable_RenderCache_OperationalFlush:snb */
		wa_masked_dis(wal, CACHE_MODE_0, RC_OP_FLUSH_ENABLE);

		/*
		 * From the Sandybridge PRM, volume 1 part 3, page 24:
		 * "If this bit is set, STCunit will have LRA as replacement
		 *  policy. [...] This bit must be reset. LRA replacement
		 *  policy is not supported."
		 */
		wa_masked_dis(wal,
			      CACHE_MODE_0,
			      CM0_STC_EVICT_DISABLE_LRA_SNB);
	पूर्ण

	अगर (IS_GEN_RANGE(i915, 4, 6))
		/* WaTimedSingleVertexDispatch:cl,bw,ctg,elk,ilk,snb */
		wa_add(wal, MI_MODE,
		       0, _MASKED_BIT_ENABLE(VS_TIMER_DISPATCH),
		       /* XXX bit करोesn't stick on Broadwater */
		       IS_I965G(i915) ? 0 : VS_TIMER_DISPATCH);

	अगर (IS_GEN(i915, 4))
		/*
		 * Disable CONSTANT_BUFFER beक्रमe it is loaded from the context
		 * image. For as it is loaded, it is executed and the stored
		 * address may no दीर्घer be valid, leading to a GPU hang.
		 *
		 * This imposes the requirement that userspace reload their
		 * CONSTANT_BUFFER on every batch, क्रमtunately a requirement
		 * they are alपढ़ोy accustomed to from beक्रमe contexts were
		 * enabled.
		 */
		wa_add(wal, ECOSKPD,
		       0, _MASKED_BIT_ENABLE(ECO_CONSTANT_BUFFER_SR_DISABLE),
		       0 /* XXX bit करोesn't stick on Broadwater */);
पूर्ण

अटल व्योम
xcs_engine_wa_init(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा i915_wa_list *wal)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	/* WaKBLVECSSemaphoreWaitPoll:kbl */
	अगर (IS_KBL_GT_STEP(i915, STEP_A0, STEP_E0)) अणु
		wa_ग_लिखो(wal,
			 RING_SEMA_WAIT_POLL(engine->mmio_base),
			 1);
	पूर्ण
पूर्ण

अटल व्योम
engine_init_workarounds(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा i915_wa_list *wal)
अणु
	अगर (I915_SELFTEST_ONLY(INTEL_GEN(engine->i915) < 4))
		वापस;

	अगर (engine->class == RENDER_CLASS)
		rcs_engine_wa_init(engine, wal);
	अन्यथा
		xcs_engine_wa_init(engine, wal);
पूर्ण

व्योम पूर्णांकel_engine_init_workarounds(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_wa_list *wal = &engine->wa_list;

	अगर (INTEL_GEN(engine->i915) < 4)
		वापस;

	wa_init_start(wal, "engine", engine->name);
	engine_init_workarounds(engine, wal);
	wa_init_finish(wal);
पूर्ण

व्योम पूर्णांकel_engine_apply_workarounds(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	wa_list_apply(engine->uncore, &engine->wa_list);
पूर्ण

काष्ठा mcr_range अणु
	u32 start;
	u32 end;
पूर्ण;

अटल स्थिर काष्ठा mcr_range mcr_ranges_gen8[] = अणु
	अणु .start = 0x5500, .end = 0x55ff पूर्ण,
	अणु .start = 0x7000, .end = 0x7fff पूर्ण,
	अणु .start = 0x9400, .end = 0x97ff पूर्ण,
	अणु .start = 0xb000, .end = 0xb3ff पूर्ण,
	अणु .start = 0xe000, .end = 0xe7ff पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mcr_range mcr_ranges_gen12[] = अणु
	अणु .start =  0x8150, .end =  0x815f पूर्ण,
	अणु .start =  0x9520, .end =  0x955f पूर्ण,
	अणु .start =  0xb100, .end =  0xb3ff पूर्ण,
	अणु .start =  0xde80, .end =  0xe8ff पूर्ण,
	अणु .start = 0x24a00, .end = 0x24a7f पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल bool mcr_range(काष्ठा drm_i915_निजी *i915, u32 offset)
अणु
	स्थिर काष्ठा mcr_range *mcr_ranges;
	पूर्णांक i;

	अगर (INTEL_GEN(i915) >= 12)
		mcr_ranges = mcr_ranges_gen12;
	अन्यथा अगर (INTEL_GEN(i915) >= 8)
		mcr_ranges = mcr_ranges_gen8;
	अन्यथा
		वापस false;

	/*
	 * Registers in these ranges are affected by the MCR selector
	 * which only controls CPU initiated MMIO. Routing करोes not
	 * work क्रम CS access so we cannot verअगरy them on this path.
	 */
	क्रम (i = 0; mcr_ranges[i].start; i++)
		अगर (offset >= mcr_ranges[i].start &&
		    offset <= mcr_ranges[i].end)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक
wa_list_srm(काष्ठा i915_request *rq,
	    स्थिर काष्ठा i915_wa_list *wal,
	    काष्ठा i915_vma *vma)
अणु
	काष्ठा drm_i915_निजी *i915 = rq->engine->i915;
	अचिन्हित पूर्णांक i, count = 0;
	स्थिर काष्ठा i915_wa *wa;
	u32 srm, *cs;

	srm = MI_STORE_REGISTER_MEM | MI_SRM_LRM_GLOBAL_GTT;
	अगर (INTEL_GEN(i915) >= 8)
		srm++;

	क्रम (i = 0, wa = wal->list; i < wal->count; i++, wa++) अणु
		अगर (!mcr_range(i915, i915_mmio_reg_offset(wa->reg)))
			count++;
	पूर्ण

	cs = पूर्णांकel_ring_begin(rq, 4 * count);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	क्रम (i = 0, wa = wal->list; i < wal->count; i++, wa++) अणु
		u32 offset = i915_mmio_reg_offset(wa->reg);

		अगर (mcr_range(i915, offset))
			जारी;

		*cs++ = srm;
		*cs++ = offset;
		*cs++ = i915_ggtt_offset(vma) + माप(u32) * i;
		*cs++ = 0;
	पूर्ण
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक engine_wa_list_verअगरy(काष्ठा पूर्णांकel_context *ce,
				 स्थिर काष्ठा i915_wa_list * स्थिर wal,
				 स्थिर अक्षर *from)
अणु
	स्थिर काष्ठा i915_wa *wa;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma;
	काष्ठा i915_gem_ww_ctx ww;
	अचिन्हित पूर्णांक i;
	u32 *results;
	पूर्णांक err;

	अगर (!wal->count)
		वापस 0;

	vma = __vm_create_scratch_क्रम_पढ़ो(&ce->engine->gt->ggtt->vm,
					   wal->count * माप(u32));
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	पूर्णांकel_engine_pm_get(ce->engine);
	i915_gem_ww_ctx_init(&ww, false);
retry:
	err = i915_gem_object_lock(vma->obj, &ww);
	अगर (err == 0)
		err = पूर्णांकel_context_pin_ww(ce, &ww);
	अगर (err)
		जाओ err_pm;

	err = i915_vma_pin_ww(vma, &ww, 0, 0,
			   i915_vma_is_ggtt(vma) ? PIN_GLOBAL : PIN_USER);
	अगर (err)
		जाओ err_unpin;

	rq = i915_request_create(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_vma;
	पूर्ण

	err = i915_request_aरुको_object(rq, vma->obj, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	अगर (err == 0)
		err = wa_list_srm(rq, wal, vma);

	i915_request_get(rq);
	अगर (err)
		i915_request_set_error_once(rq, err);
	i915_request_add(rq);

	अगर (err)
		जाओ err_rq;

	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
		err = -ETIME;
		जाओ err_rq;
	पूर्ण

	results = i915_gem_object_pin_map(vma->obj, I915_MAP_WB);
	अगर (IS_ERR(results)) अणु
		err = PTR_ERR(results);
		जाओ err_rq;
	पूर्ण

	err = 0;
	क्रम (i = 0, wa = wal->list; i < wal->count; i++, wa++) अणु
		अगर (mcr_range(rq->engine->i915, i915_mmio_reg_offset(wa->reg)))
			जारी;

		अगर (!wa_verअगरy(wa, results[i], wal->name, from))
			err = -ENXIO;
	पूर्ण

	i915_gem_object_unpin_map(vma->obj);

err_rq:
	i915_request_put(rq);
err_vma:
	i915_vma_unpin(vma);
err_unpin:
	पूर्णांकel_context_unpin(ce);
err_pm:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	पूर्णांकel_engine_pm_put(ce->engine);
	i915_vma_put(vma);
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_engine_verअगरy_workarounds(काष्ठा पूर्णांकel_engine_cs *engine,
				    स्थिर अक्षर *from)
अणु
	वापस engine_wa_list_verअगरy(engine->kernel_context,
				     &engine->wa_list,
				     from);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_workarounds.c"
#पूर्ण_अगर
