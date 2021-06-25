<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "gem/i915_gem_context.h"

#समावेश "i915_drv.h"

#समावेश "intel_breadcrumbs.h"
#समावेश "intel_context.h"
#समावेश "intel_engine.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_engine_user.h"
#समावेश "intel_execlists_submission.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_requests.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_lrc_reg.h"
#समावेश "intel_reset.h"
#समावेश "intel_ring.h"
#समावेश "uc/intel_guc_submission.h"

/* Haswell करोes have the CXT_SIZE रेजिस्टर however it करोes not appear to be
 * valid. Now, करोcs explain in dwords what is in the context object. The full
 * size is 70720 bytes, however, the घातer context and execlist context will
 * never be saved (घातer context is stored अन्यथाwhere, and execlists करोn't work
 * on HSW) - so the final size, including the extra state required क्रम the
 * Resource Streamer, is 66944 bytes, which rounds to 17 pages.
 */
#घोषणा HSW_CXT_TOTAL_SIZE		(17 * PAGE_SIZE)

#घोषणा DEFAULT_LR_CONTEXT_RENDER_SIZE	(22 * PAGE_SIZE)
#घोषणा GEN8_LR_CONTEXT_RENDER_SIZE	(20 * PAGE_SIZE)
#घोषणा GEN9_LR_CONTEXT_RENDER_SIZE	(22 * PAGE_SIZE)
#घोषणा GEN10_LR_CONTEXT_RENDER_SIZE	(18 * PAGE_SIZE)
#घोषणा GEN11_LR_CONTEXT_RENDER_SIZE	(14 * PAGE_SIZE)

#घोषणा GEN8_LR_CONTEXT_OTHER_SIZE	( 2 * PAGE_SIZE)

#घोषणा MAX_MMIO_BASES 3
काष्ठा engine_info अणु
	अचिन्हित पूर्णांक hw_id;
	u8 class;
	u8 instance;
	/* mmio bases table *must* be sorted in reverse gen order */
	काष्ठा engine_mmio_base अणु
		u32 gen : 8;
		u32 base : 24;
	पूर्ण mmio_bases[MAX_MMIO_BASES];
पूर्ण;

अटल स्थिर काष्ठा engine_info पूर्णांकel_engines[] = अणु
	[RCS0] = अणु
		.hw_id = RCS0_HW,
		.class = RENDER_CLASS,
		.instance = 0,
		.mmio_bases = अणु
			अणु .gen = 1, .base = RENDER_RING_BASE पूर्ण
		पूर्ण,
	पूर्ण,
	[BCS0] = अणु
		.hw_id = BCS0_HW,
		.class = COPY_ENGINE_CLASS,
		.instance = 0,
		.mmio_bases = अणु
			अणु .gen = 6, .base = BLT_RING_BASE पूर्ण
		पूर्ण,
	पूर्ण,
	[VCS0] = अणु
		.hw_id = VCS0_HW,
		.class = VIDEO_DECODE_CLASS,
		.instance = 0,
		.mmio_bases = अणु
			अणु .gen = 11, .base = GEN11_BSD_RING_BASE पूर्ण,
			अणु .gen = 6, .base = GEN6_BSD_RING_BASE पूर्ण,
			अणु .gen = 4, .base = BSD_RING_BASE पूर्ण
		पूर्ण,
	पूर्ण,
	[VCS1] = अणु
		.hw_id = VCS1_HW,
		.class = VIDEO_DECODE_CLASS,
		.instance = 1,
		.mmio_bases = अणु
			अणु .gen = 11, .base = GEN11_BSD2_RING_BASE पूर्ण,
			अणु .gen = 8, .base = GEN8_BSD2_RING_BASE पूर्ण
		पूर्ण,
	पूर्ण,
	[VCS2] = अणु
		.hw_id = VCS2_HW,
		.class = VIDEO_DECODE_CLASS,
		.instance = 2,
		.mmio_bases = अणु
			अणु .gen = 11, .base = GEN11_BSD3_RING_BASE पूर्ण
		पूर्ण,
	पूर्ण,
	[VCS3] = अणु
		.hw_id = VCS3_HW,
		.class = VIDEO_DECODE_CLASS,
		.instance = 3,
		.mmio_bases = अणु
			अणु .gen = 11, .base = GEN11_BSD4_RING_BASE पूर्ण
		पूर्ण,
	पूर्ण,
	[VECS0] = अणु
		.hw_id = VECS0_HW,
		.class = VIDEO_ENHANCEMENT_CLASS,
		.instance = 0,
		.mmio_bases = अणु
			अणु .gen = 11, .base = GEN11_VEBOX_RING_BASE पूर्ण,
			अणु .gen = 7, .base = VEBOX_RING_BASE पूर्ण
		पूर्ण,
	पूर्ण,
	[VECS1] = अणु
		.hw_id = VECS1_HW,
		.class = VIDEO_ENHANCEMENT_CLASS,
		.instance = 1,
		.mmio_bases = अणु
			अणु .gen = 11, .base = GEN11_VEBOX2_RING_BASE पूर्ण
		पूर्ण,
	पूर्ण,
पूर्ण;

/**
 * पूर्णांकel_engine_context_size() - वापस the size of the context क्रम an engine
 * @gt: the gt
 * @class: engine class
 *
 * Each engine class may require a dअगरferent amount of space क्रम a context
 * image.
 *
 * Return: size (in bytes) of an engine class specअगरic context image
 *
 * Note: this size includes the HWSP, which is part of the context image
 * in LRC mode, but करोes not include the "shared data page" used with
 * GuC submission. The caller should account क्रम this अगर using the GuC.
 */
u32 पूर्णांकel_engine_context_size(काष्ठा पूर्णांकel_gt *gt, u8 class)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 cxt_size;

	BUILD_BUG_ON(I915_GTT_PAGE_SIZE != PAGE_SIZE);

	चयन (class) अणु
	हाल RENDER_CLASS:
		चयन (INTEL_GEN(gt->i915)) अणु
		शेष:
			MISSING_CASE(INTEL_GEN(gt->i915));
			वापस DEFAULT_LR_CONTEXT_RENDER_SIZE;
		हाल 12:
		हाल 11:
			वापस GEN11_LR_CONTEXT_RENDER_SIZE;
		हाल 10:
			वापस GEN10_LR_CONTEXT_RENDER_SIZE;
		हाल 9:
			वापस GEN9_LR_CONTEXT_RENDER_SIZE;
		हाल 8:
			वापस GEN8_LR_CONTEXT_RENDER_SIZE;
		हाल 7:
			अगर (IS_HASWELL(gt->i915))
				वापस HSW_CXT_TOTAL_SIZE;

			cxt_size = पूर्णांकel_uncore_पढ़ो(uncore, GEN7_CXT_SIZE);
			वापस round_up(GEN7_CXT_TOTAL_SIZE(cxt_size) * 64,
					PAGE_SIZE);
		हाल 6:
			cxt_size = पूर्णांकel_uncore_पढ़ो(uncore, CXT_SIZE);
			वापस round_up(GEN6_CXT_TOTAL_SIZE(cxt_size) * 64,
					PAGE_SIZE);
		हाल 5:
		हाल 4:
			/*
			 * There is a discrepancy here between the size reported
			 * by the रेजिस्टर and the size of the context layout
			 * in the करोcs. Both are described as authorative!
			 *
			 * The discrepancy is on the order of a few cachelines,
			 * but the total is under one page (4k), which is our
			 * minimum allocation anyway so it should all come
			 * out in the wash.
			 */
			cxt_size = पूर्णांकel_uncore_पढ़ो(uncore, CXT_SIZE) + 1;
			drm_dbg(&gt->i915->drm,
				"gen%d CXT_SIZE = %d bytes [0x%08x]\n",
				INTEL_GEN(gt->i915), cxt_size * 64,
				cxt_size - 1);
			वापस round_up(cxt_size * 64, PAGE_SIZE);
		हाल 3:
		हाल 2:
		/* For the special day when i810 माला_लो merged. */
		हाल 1:
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		MISSING_CASE(class);
		fallthrough;
	हाल VIDEO_DECODE_CLASS:
	हाल VIDEO_ENHANCEMENT_CLASS:
	हाल COPY_ENGINE_CLASS:
		अगर (INTEL_GEN(gt->i915) < 8)
			वापस 0;
		वापस GEN8_LR_CONTEXT_OTHER_SIZE;
	पूर्ण
पूर्ण

अटल u32 __engine_mmio_base(काष्ठा drm_i915_निजी *i915,
			      स्थिर काष्ठा engine_mmio_base *bases)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_MMIO_BASES; i++)
		अगर (INTEL_GEN(i915) >= bases[i].gen)
			अवरोध;

	GEM_BUG_ON(i == MAX_MMIO_BASES);
	GEM_BUG_ON(!bases[i].base);

	वापस bases[i].base;
पूर्ण

अटल व्योम __sprपूर्णांक_engine_name(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/*
	 * Beक्रमe we know what the uABI name क्रम this engine will be,
	 * we still would like to keep track of this engine in the debug logs.
	 * We throw in a ' here as a reminder that this isn't its final name.
	 */
	GEM_WARN_ON(snम_लिखो(engine->name, माप(engine->name), "%s'%u",
			     पूर्णांकel_engine_class_repr(engine->class),
			     engine->instance) >= माप(engine->name));
पूर्ण

व्योम पूर्णांकel_engine_set_hwsp_ग_लिखोmask(काष्ठा पूर्णांकel_engine_cs *engine, u32 mask)
अणु
	/*
	 * Though they added more rings on g4x/ilk, they did not add
	 * per-engine HWSTAM until gen6.
	 */
	अगर (INTEL_GEN(engine->i915) < 6 && engine->class != RENDER_CLASS)
		वापस;

	अगर (INTEL_GEN(engine->i915) >= 3)
		ENGINE_WRITE(engine, RING_HWSTAM, mask);
	अन्यथा
		ENGINE_WRITE16(engine, RING_HWSTAM, mask);
पूर्ण

अटल व्योम पूर्णांकel_engine_sanitize_mmio(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/* Mask off all ग_लिखोs पूर्णांकo the unknown HWSP */
	पूर्णांकel_engine_set_hwsp_ग_लिखोmask(engine, ~0u);
पूर्ण

अटल पूर्णांक पूर्णांकel_engine_setup(काष्ठा पूर्णांकel_gt *gt, क्रमागत पूर्णांकel_engine_id id)
अणु
	स्थिर काष्ठा engine_info *info = &पूर्णांकel_engines[id];
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_engine_cs *engine;

	BUILD_BUG_ON(MAX_ENGINE_CLASS >= BIT(GEN11_ENGINE_CLASS_WIDTH));
	BUILD_BUG_ON(MAX_ENGINE_INSTANCE >= BIT(GEN11_ENGINE_INSTANCE_WIDTH));

	अगर (GEM_DEBUG_WARN_ON(id >= ARRAY_SIZE(gt->engine)))
		वापस -EINVAL;

	अगर (GEM_DEBUG_WARN_ON(info->class > MAX_ENGINE_CLASS))
		वापस -EINVAL;

	अगर (GEM_DEBUG_WARN_ON(info->instance > MAX_ENGINE_INSTANCE))
		वापस -EINVAL;

	अगर (GEM_DEBUG_WARN_ON(gt->engine_class[info->class][info->instance]))
		वापस -EINVAL;

	engine = kzalloc(माप(*engine), GFP_KERNEL);
	अगर (!engine)
		वापस -ENOMEM;

	BUILD_BUG_ON(BITS_PER_TYPE(engine->mask) < I915_NUM_ENGINES);

	engine->id = id;
	engine->legacy_idx = INVALID_ENGINE;
	engine->mask = BIT(id);
	engine->i915 = i915;
	engine->gt = gt;
	engine->uncore = gt->uncore;
	engine->mmio_base = __engine_mmio_base(i915, info->mmio_bases);
	engine->hw_id = info->hw_id;
	engine->guc_id = MAKE_GUC_ID(info->class, info->instance);

	engine->class = info->class;
	engine->instance = info->instance;
	__sprपूर्णांक_engine_name(engine);

	engine->props.heartbeat_पूर्णांकerval_ms =
		CONFIG_DRM_I915_HEARTBEAT_INTERVAL;
	engine->props.max_busyरुको_duration_ns =
		CONFIG_DRM_I915_MAX_REQUEST_BUSYWAIT;
	engine->props.preempt_समयout_ms =
		CONFIG_DRM_I915_PREEMPT_TIMEOUT;
	engine->props.stop_समयout_ms =
		CONFIG_DRM_I915_STOP_TIMEOUT;
	engine->props.बारlice_duration_ms =
		CONFIG_DRM_I915_TIMESLICE_DURATION;

	/* Override to unपूर्णांकerruptible क्रम OpenCL workloads. */
	अगर (INTEL_GEN(i915) == 12 && engine->class == RENDER_CLASS)
		engine->props.preempt_समयout_ms = 0;

	engine->शेषs = engine->props; /* never to change again */

	engine->context_size = पूर्णांकel_engine_context_size(gt, engine->class);
	अगर (WARN_ON(engine->context_size > BIT(20)))
		engine->context_size = 0;
	अगर (engine->context_size)
		DRIVER_CAPS(i915)->has_logical_contexts = true;

	/* Nothing to करो here, execute in order of dependencies */
	engine->schedule = शून्य;

	ewma__engine_latency_init(&engine->latency);
	seqcount_init(&engine->stats.lock);

	ATOMIC_INIT_NOTIFIER_HEAD(&engine->context_status_notअगरier);

	/* Scrub mmio state on takeover */
	पूर्णांकel_engine_sanitize_mmio(engine);

	gt->engine_class[info->class][info->instance] = engine;
	gt->engine[id] = engine;

	वापस 0;
पूर्ण

अटल व्योम __setup_engine_capabilities(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	अगर (engine->class == VIDEO_DECODE_CLASS) अणु
		/*
		 * HEVC support is present on first engine instance
		 * beक्रमe Gen11 and on all instances afterwards.
		 */
		अगर (INTEL_GEN(i915) >= 11 ||
		    (INTEL_GEN(i915) >= 9 && engine->instance == 0))
			engine->uabi_capabilities |=
				I915_VIDEO_CLASS_CAPABILITY_HEVC;

		/*
		 * SFC block is present only on even logical engine
		 * instances.
		 */
		अगर ((INTEL_GEN(i915) >= 11 &&
		     (engine->gt->info.vdbox_sfc_access &
		      BIT(engine->instance))) ||
		    (INTEL_GEN(i915) >= 9 && engine->instance == 0))
			engine->uabi_capabilities |=
				I915_VIDEO_AND_ENHANCE_CLASS_CAPABILITY_SFC;
	पूर्ण अन्यथा अगर (engine->class == VIDEO_ENHANCEMENT_CLASS) अणु
		अगर (INTEL_GEN(i915) >= 9)
			engine->uabi_capabilities |=
				I915_VIDEO_AND_ENHANCE_CLASS_CAPABILITY_SFC;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_setup_engine_capabilities(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt, id)
		__setup_engine_capabilities(engine);
पूर्ण

/**
 * पूर्णांकel_engines_release() - मुक्त the resources allocated क्रम Command Streamers
 * @gt: poपूर्णांकer to काष्ठा पूर्णांकel_gt
 */
व्योम पूर्णांकel_engines_release(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * Beक्रमe we release the resources held by engine, we must be certain
	 * that the HW is no दीर्घer accessing them -- having the GPU scribble
	 * to or पढ़ो from a page being used क्रम something अन्यथा causes no end
	 * of fun.
	 *
	 * The GPU should be reset by this poपूर्णांक, but assume the worst just
	 * in हाल we पातed beक्रमe completely initialising the engines.
	 */
	GEM_BUG_ON(पूर्णांकel_gt_pm_is_awake(gt));
	अगर (!INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		__पूर्णांकel_gt_reset(gt, ALL_ENGINES);

	/* Decouple the backend; but keep the layout क्रम late GPU resets */
	क्रम_each_engine(engine, gt, id) अणु
		अगर (!engine->release)
			जारी;

		पूर्णांकel_wakeref_रुको_क्रम_idle(&engine->wakeref);
		GEM_BUG_ON(पूर्णांकel_engine_pm_is_awake(engine));

		engine->release(engine);
		engine->release = शून्य;

		स_रखो(&engine->reset, 0, माप(engine->reset));
	पूर्ण
पूर्ण

व्योम पूर्णांकel_engine_मुक्त_request_pool(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!engine->request_pool)
		वापस;

	kmem_cache_मुक्त(i915_request_slab_cache(), engine->request_pool);
पूर्ण

व्योम पूर्णांकel_engines_मुक्त(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/* Free the requests! dma-resv keeps fences around क्रम an eternity */
	rcu_barrier();

	क्रम_each_engine(engine, gt, id) अणु
		पूर्णांकel_engine_मुक्त_request_pool(engine);
		kमुक्त(engine);
		gt->engine[id] = शून्य;
	पूर्ण
पूर्ण

/*
 * Determine which engines are fused off in our particular hardware.
 * Note that we have a catch-22 situation where we need to be able to access
 * the blitter क्रमcewake करोमुख्य to पढ़ो the engine fuses, but at the same समय
 * we need to know which engines are available on the प्रणाली to know which
 * क्रमcewake करोमुख्यs are present. We solve this by पूर्णांकializing the क्रमcewake
 * करोमुख्यs based on the full engine mask in the platक्रमm capabilities beक्रमe
 * calling this function and pruning the करोमुख्यs क्रम fused-off engines
 * afterwards.
 */
अटल पूर्णांकel_engine_mask_t init_engine_mask(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_gt_info *info = &gt->info;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	अचिन्हित पूर्णांक logical_vdbox = 0;
	अचिन्हित पूर्णांक i;
	u32 media_fuse;
	u16 vdbox_mask;
	u16 vebox_mask;

	info->engine_mask = INTEL_INFO(i915)->platक्रमm_engine_mask;

	अगर (INTEL_GEN(i915) < 11)
		वापस info->engine_mask;

	media_fuse = ~पूर्णांकel_uncore_पढ़ो(uncore, GEN11_GT_VEBOX_VDBOX_DISABLE);

	vdbox_mask = media_fuse & GEN11_GT_VDBOX_DISABLE_MASK;
	vebox_mask = (media_fuse & GEN11_GT_VEBOX_DISABLE_MASK) >>
		      GEN11_GT_VEBOX_DISABLE_SHIFT;

	क्रम (i = 0; i < I915_MAX_VCS; i++) अणु
		अगर (!HAS_ENGINE(gt, _VCS(i))) अणु
			vdbox_mask &= ~BIT(i);
			जारी;
		पूर्ण

		अगर (!(BIT(i) & vdbox_mask)) अणु
			info->engine_mask &= ~BIT(_VCS(i));
			drm_dbg(&i915->drm, "vcs%u fused off\n", i);
			जारी;
		पूर्ण

		/*
		 * In Gen11, only even numbered logical VDBOXes are
		 * hooked up to an SFC (Scaler & Format Converter) unit.
		 * In TGL each VDBOX has access to an SFC.
		 */
		अगर (INTEL_GEN(i915) >= 12 || logical_vdbox++ % 2 == 0)
			gt->info.vdbox_sfc_access |= BIT(i);
	पूर्ण
	drm_dbg(&i915->drm, "vdbox enable: %04x, instances: %04lx\n",
		vdbox_mask, VDBOX_MASK(gt));
	GEM_BUG_ON(vdbox_mask != VDBOX_MASK(gt));

	क्रम (i = 0; i < I915_MAX_VECS; i++) अणु
		अगर (!HAS_ENGINE(gt, _VECS(i))) अणु
			vebox_mask &= ~BIT(i);
			जारी;
		पूर्ण

		अगर (!(BIT(i) & vebox_mask)) अणु
			info->engine_mask &= ~BIT(_VECS(i));
			drm_dbg(&i915->drm, "vecs%u fused off\n", i);
		पूर्ण
	पूर्ण
	drm_dbg(&i915->drm, "vebox enable: %04x, instances: %04lx\n",
		vebox_mask, VEBOX_MASK(gt));
	GEM_BUG_ON(vebox_mask != VEBOX_MASK(gt));

	वापस info->engine_mask;
पूर्ण

/**
 * पूर्णांकel_engines_init_mmio() - allocate and prepare the Engine Command Streamers
 * @gt: poपूर्णांकer to काष्ठा पूर्णांकel_gt
 *
 * Return: non-zero अगर the initialization failed.
 */
पूर्णांक पूर्णांकel_engines_init_mmio(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	स्थिर अचिन्हित पूर्णांक engine_mask = init_engine_mask(gt);
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	drm_WARN_ON(&i915->drm, engine_mask == 0);
	drm_WARN_ON(&i915->drm, engine_mask &
		    GENMASK(BITS_PER_TYPE(mask) - 1, I915_NUM_ENGINES));

	अगर (i915_inject_probe_failure(i915))
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकel_engines); i++) अणु
		अगर (!HAS_ENGINE(gt, i))
			जारी;

		err = पूर्णांकel_engine_setup(gt, i);
		अगर (err)
			जाओ cleanup;

		mask |= BIT(i);
	पूर्ण

	/*
	 * Catch failures to update पूर्णांकel_engines table when the new engines
	 * are added to the driver by a warning and disabling the क्रमgotten
	 * engines.
	 */
	अगर (drm_WARN_ON(&i915->drm, mask != engine_mask))
		gt->info.engine_mask = mask;

	gt->info.num_engines = hweight32(mask);

	पूर्णांकel_gt_check_and_clear_faults(gt);

	पूर्णांकel_setup_engine_capabilities(gt);

	पूर्णांकel_uncore_prune_engine_fw_करोमुख्यs(gt->uncore, gt);

	वापस 0;

cleanup:
	पूर्णांकel_engines_मुक्त(gt);
	वापस err;
पूर्ण

व्योम पूर्णांकel_engine_init_execlists(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;

	execlists->port_mask = 1;
	GEM_BUG_ON(!is_घातer_of_2(execlists_num_ports(execlists)));
	GEM_BUG_ON(execlists_num_ports(execlists) > EXECLIST_MAX_PORTS);

	स_रखो(execlists->pending, 0, माप(execlists->pending));
	execlists->active =
		स_रखो(execlists->inflight, 0, माप(execlists->inflight));

	execlists->queue_priority_hपूर्णांक = पूर्णांक_न्यून;
	execlists->queue = RB_ROOT_CACHED;
पूर्ण

अटल व्योम cleanup_status_page(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_vma *vma;

	/* Prevent ग_लिखोs पूर्णांकo HWSP after वापसing the page to the प्रणाली */
	पूर्णांकel_engine_set_hwsp_ग_लिखोmask(engine, ~0u);

	vma = fetch_and_zero(&engine->status_page.vma);
	अगर (!vma)
		वापस;

	अगर (!HWS_NEEDS_PHYSICAL(engine->i915))
		i915_vma_unpin(vma);

	i915_gem_object_unpin_map(vma->obj);
	i915_gem_object_put(vma->obj);
पूर्ण

अटल पूर्णांक pin_ggtt_status_page(काष्ठा पूर्णांकel_engine_cs *engine,
				काष्ठा i915_gem_ww_ctx *ww,
				काष्ठा i915_vma *vma)
अणु
	अचिन्हित पूर्णांक flags;

	अगर (!HAS_LLC(engine->i915) && i915_ggtt_has_aperture(engine->gt->ggtt))
		/*
		 * On g33, we cannot place HWS above 256MiB, so
		 * restrict its pinning to the low mappable arena.
		 * Though this restriction is not करोcumented क्रम
		 * gen4, gen5, or byt, they also behave similarly
		 * and hang अगर the HWS is placed at the top of the
		 * GTT. To generalise, it appears that all !llc
		 * platक्रमms have issues with us placing the HWS
		 * above the mappable region (even though we never
		 * actually map it).
		 */
		flags = PIN_MAPPABLE;
	अन्यथा
		flags = PIN_HIGH;

	वापस i915_ggtt_pin(vma, ww, 0, flags);
पूर्ण

अटल पूर्णांक init_status_page(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा i915_vma *vma;
	व्योम *vaddr;
	पूर्णांक ret;

	INIT_LIST_HEAD(&engine->status_page.समयlines);

	/*
	 * Though the HWS रेजिस्टर करोes support 36bit addresses, historically
	 * we have had hangs and corruption reported due to wild ग_लिखोs अगर
	 * the HWS is placed above 4G. We only allow objects to be allocated
	 * in GFP_DMA32 क्रम i965, and no earlier physical address users had
	 * access to more than 4G.
	 */
	obj = i915_gem_object_create_पूर्णांकernal(engine->i915, PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		drm_err(&engine->i915->drm,
			"Failed to allocate status page\n");
		वापस PTR_ERR(obj);
	पूर्ण

	i915_gem_object_set_cache_coherency(obj, I915_CACHE_LLC);

	vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ err_put;
	पूर्ण

	i915_gem_ww_ctx_init(&ww, true);
retry:
	ret = i915_gem_object_lock(obj, &ww);
	अगर (!ret && !HWS_NEEDS_PHYSICAL(engine->i915))
		ret = pin_ggtt_status_page(engine, &ww, vma);
	अगर (ret)
		जाओ err;

	vaddr = i915_gem_object_pin_map(obj, I915_MAP_WB);
	अगर (IS_ERR(vaddr)) अणु
		ret = PTR_ERR(vaddr);
		जाओ err_unpin;
	पूर्ण

	engine->status_page.addr = स_रखो(vaddr, 0, PAGE_SIZE);
	engine->status_page.vma = vma;

err_unpin:
	अगर (ret)
		i915_vma_unpin(vma);
err:
	अगर (ret == -EDEADLK) अणु
		ret = i915_gem_ww_ctx_backoff(&ww);
		अगर (!ret)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
err_put:
	अगर (ret)
		i915_gem_object_put(obj);
	वापस ret;
पूर्ण

अटल पूर्णांक engine_setup_common(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांक err;

	init_llist_head(&engine->barrier_tasks);

	err = init_status_page(engine);
	अगर (err)
		वापस err;

	engine->bपढ़ोcrumbs = पूर्णांकel_bपढ़ोcrumbs_create(engine);
	अगर (!engine->bपढ़ोcrumbs) अणु
		err = -ENOMEM;
		जाओ err_status;
	पूर्ण

	err = पूर्णांकel_engine_init_cmd_parser(engine);
	अगर (err)
		जाओ err_cmd_parser;

	पूर्णांकel_engine_init_active(engine, ENGINE_PHYSICAL);
	पूर्णांकel_engine_init_execlists(engine);
	पूर्णांकel_engine_init__pm(engine);
	पूर्णांकel_engine_init_retire(engine);

	/* Use the whole device by शेष */
	engine->sseu =
		पूर्णांकel_sseu_from_device_info(&engine->gt->info.sseu);

	पूर्णांकel_engine_init_workarounds(engine);
	पूर्णांकel_engine_init_whitelist(engine);
	पूर्णांकel_engine_init_ctx_wa(engine);

	अगर (INTEL_GEN(engine->i915) >= 12)
		engine->flags |= I915_ENGINE_HAS_RELATIVE_MMIO;

	वापस 0;

err_cmd_parser:
	पूर्णांकel_bपढ़ोcrumbs_मुक्त(engine->bपढ़ोcrumbs);
err_status:
	cleanup_status_page(engine);
	वापस err;
पूर्ण

काष्ठा measure_bपढ़ोcrumb अणु
	काष्ठा i915_request rq;
	काष्ठा पूर्णांकel_ring ring;
	u32 cs[2048];
पूर्ण;

अटल पूर्णांक measure_bपढ़ोcrumb_dw(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	काष्ठा measure_bपढ़ोcrumb *frame;
	पूर्णांक dw;

	GEM_BUG_ON(!engine->gt->scratch);

	frame = kzalloc(माप(*frame), GFP_KERNEL);
	अगर (!frame)
		वापस -ENOMEM;

	frame->rq.engine = engine;
	frame->rq.context = ce;
	rcu_assign_poपूर्णांकer(frame->rq.समयline, ce->समयline);
	frame->rq.hwsp_seqno = ce->समयline->hwsp_seqno;

	frame->ring.vaddr = frame->cs;
	frame->ring.size = माप(frame->cs);
	frame->ring.wrap =
		BITS_PER_TYPE(frame->ring.size) - ilog2(frame->ring.size);
	frame->ring.effective_size = frame->ring.size;
	पूर्णांकel_ring_update_space(&frame->ring);
	frame->rq.ring = &frame->ring;

	mutex_lock(&ce->समयline->mutex);
	spin_lock_irq(&engine->active.lock);

	dw = engine->emit_fini_bपढ़ोcrumb(&frame->rq, frame->cs) - frame->cs;

	spin_unlock_irq(&engine->active.lock);
	mutex_unlock(&ce->समयline->mutex);

	GEM_BUG_ON(dw & 1); /* RING_TAIL must be qword aligned */

	kमुक्त(frame);
	वापस dw;
पूर्ण

व्योम
पूर्णांकel_engine_init_active(काष्ठा पूर्णांकel_engine_cs *engine, अचिन्हित पूर्णांक subclass)
अणु
	INIT_LIST_HEAD(&engine->active.requests);
	INIT_LIST_HEAD(&engine->active.hold);

	spin_lock_init(&engine->active.lock);
	lockdep_set_subclass(&engine->active.lock, subclass);

	/*
	 * Due to an पूर्णांकeresting quirk in lockdep's पूर्णांकernal debug tracking,
	 * after setting a subclass we must ensure the lock is used. Otherwise,
	 * nr_unused_locks is incremented once too often.
	 */
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	local_irq_disable();
	lock_map_acquire(&engine->active.lock.dep_map);
	lock_map_release(&engine->active.lock.dep_map);
	local_irq_enable();
#पूर्ण_अगर
पूर्ण

अटल काष्ठा पूर्णांकel_context *
create_pinned_context(काष्ठा पूर्णांकel_engine_cs *engine,
		      अचिन्हित पूर्णांक hwsp,
		      काष्ठा lock_class_key *key,
		      स्थिर अक्षर *name)
अणु
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस ce;

	__set_bit(CONTEXT_BARRIER_BIT, &ce->flags);
	ce->समयline = page_pack_bits(शून्य, hwsp);

	err = पूर्णांकel_context_pin(ce); /* perma-pin so it is always available */
	अगर (err) अणु
		पूर्णांकel_context_put(ce);
		वापस ERR_PTR(err);
	पूर्ण

	/*
	 * Give our perma-pinned kernel समयlines a separate lockdep class,
	 * so that we can use them from within the normal user समयlines
	 * should we need to inject GPU operations during their request
	 * स्थिरruction.
	 */
	lockdep_set_class_and_name(&ce->समयline->mutex, key, name);

	वापस ce;
पूर्ण

अटल व्योम destroy_pinned_context(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	काष्ठा i915_vma *hwsp = engine->status_page.vma;

	GEM_BUG_ON(ce->समयline->hwsp_ggtt != hwsp);

	mutex_lock(&hwsp->vm->mutex);
	list_del(&ce->समयline->engine_link);
	mutex_unlock(&hwsp->vm->mutex);

	पूर्णांकel_context_unpin(ce);
	पूर्णांकel_context_put(ce);
पूर्ण

अटल काष्ठा पूर्णांकel_context *
create_kernel_context(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अटल काष्ठा lock_class_key kernel;

	वापस create_pinned_context(engine, I915_GEM_HWS_SEQNO_ADDR,
				     &kernel, "kernel_context");
पूर्ण

/**
 * पूर्णांकel_engines_init_common - initialize cengine state which might require hw access
 * @engine: Engine to initialize.
 *
 * Initializes @engine@ काष्ठाure members shared between legacy and execlists
 * submission modes which करो require hardware access.
 *
 * Typcally करोne at later stages of submission mode specअगरic engine setup.
 *
 * Returns zero on success or an error code on failure.
 */
अटल पूर्णांक engine_init_common(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक ret;

	engine->set_शेष_submission(engine);

	/*
	 * We may need to करो things with the shrinker which
	 * require us to immediately चयन back to the शेष
	 * context. This can cause a problem as pinning the
	 * शेष context also requires GTT space which may not
	 * be available. To aव्योम this we always pin the शेष
	 * context.
	 */
	ce = create_kernel_context(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	ret = measure_bपढ़ोcrumb_dw(ce);
	अगर (ret < 0)
		जाओ err_context;

	engine->emit_fini_bपढ़ोcrumb_dw = ret;
	engine->kernel_context = ce;

	वापस 0;

err_context:
	पूर्णांकel_context_put(ce);
	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_engines_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांक (*setup)(काष्ठा पूर्णांकel_engine_cs *engine);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err;

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		setup = पूर्णांकel_guc_submission_setup;
	अन्यथा अगर (HAS_EXECLISTS(gt->i915))
		setup = पूर्णांकel_execlists_submission_setup;
	अन्यथा
		setup = पूर्णांकel_ring_submission_setup;

	क्रम_each_engine(engine, gt, id) अणु
		err = engine_setup_common(engine);
		अगर (err)
			वापस err;

		err = setup(engine);
		अगर (err)
			वापस err;

		err = engine_init_common(engine);
		अगर (err)
			वापस err;

		पूर्णांकel_engine_add_user(engine);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_engines_cleanup_common - cleans up the engine state created by
 *                                the common initiailizers.
 * @engine: Engine to cleanup.
 *
 * This cleans up everything created by the common helpers.
 */
व्योम पूर्णांकel_engine_cleanup_common(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	GEM_BUG_ON(!list_empty(&engine->active.requests));
	tasklet_समाप्त(&engine->execlists.tasklet); /* flush the callback */

	पूर्णांकel_bपढ़ोcrumbs_मुक्त(engine->bपढ़ोcrumbs);

	पूर्णांकel_engine_fini_retire(engine);
	पूर्णांकel_engine_cleanup_cmd_parser(engine);

	अगर (engine->शेष_state)
		fput(engine->शेष_state);

	अगर (engine->kernel_context)
		destroy_pinned_context(engine->kernel_context);

	GEM_BUG_ON(!llist_empty(&engine->barrier_tasks));
	cleanup_status_page(engine);

	पूर्णांकel_wa_list_मुक्त(&engine->ctx_wa_list);
	पूर्णांकel_wa_list_मुक्त(&engine->wa_list);
	पूर्णांकel_wa_list_मुक्त(&engine->whitelist);
पूर्ण

/**
 * पूर्णांकel_engine_resume - re-initializes the HW state of the engine
 * @engine: Engine to resume.
 *
 * Returns zero on success or an error code on failure.
 */
पूर्णांक पूर्णांकel_engine_resume(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_engine_apply_workarounds(engine);
	पूर्णांकel_engine_apply_whitelist(engine);

	वापस engine->resume(engine);
पूर्ण

u64 पूर्णांकel_engine_get_active_head(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	u64 acthd;

	अगर (INTEL_GEN(i915) >= 8)
		acthd = ENGINE_READ64(engine, RING_ACTHD, RING_ACTHD_UDW);
	अन्यथा अगर (INTEL_GEN(i915) >= 4)
		acthd = ENGINE_READ(engine, RING_ACTHD);
	अन्यथा
		acthd = ENGINE_READ(engine, ACTHD);

	वापस acthd;
पूर्ण

u64 पूर्णांकel_engine_get_last_batch_head(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	u64 bbaddr;

	अगर (INTEL_GEN(engine->i915) >= 8)
		bbaddr = ENGINE_READ64(engine, RING_BBADDR, RING_BBADDR_UDW);
	अन्यथा
		bbaddr = ENGINE_READ(engine, RING_BBADDR);

	वापस bbaddr;
पूर्ण

अटल अचिन्हित दीर्घ stop_समयout(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (in_atomic() || irqs_disabled()) /* inside atomic preempt-reset? */
		वापस 0;

	/*
	 * If we are करोing a normal GPU reset, we can take our समय and allow
	 * the engine to quiesce. We've stopped submission to the engine, and
	 * अगर we रुको दीर्घ enough an innocent context should complete and
	 * leave the engine idle. So they should not be caught unaware by
	 * the क्रमthcoming GPU reset (which usually follows the stop_cs)!
	 */
	वापस READ_ONCE(engine->props.stop_समयout_ms);
पूर्ण

अटल पूर्णांक __पूर्णांकel_engine_stop_cs(काष्ठा पूर्णांकel_engine_cs *engine,
				  पूर्णांक fast_समयout_us,
				  पूर्णांक slow_समयout_ms)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	स्थिर i915_reg_t mode = RING_MI_MODE(engine->mmio_base);
	पूर्णांक err;

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, mode, _MASKED_BIT_ENABLE(STOP_RING));
	err = __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(engine->uncore, mode,
					   MODE_IDLE, MODE_IDLE,
					   fast_समयout_us,
					   slow_समयout_ms,
					   शून्य);

	/* A final mmio पढ़ो to let GPU ग_लिखोs be hopefully flushed to memory */
	पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, mode);
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_engine_stop_cs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांक err = 0;

	अगर (INTEL_GEN(engine->i915) < 3)
		वापस -ENODEV;

	ENGINE_TRACE(engine, "\n");
	अगर (__पूर्णांकel_engine_stop_cs(engine, 1000, stop_समयout(engine))) अणु
		ENGINE_TRACE(engine,
			     "timed out on STOP_RING -> IDLE; HEAD:%04x, TAIL:%04x\n",
			     ENGINE_READ_FW(engine, RING_HEAD) & HEAD_ADDR,
			     ENGINE_READ_FW(engine, RING_TAIL) & TAIL_ADDR);

		/*
		 * Someबार we observe that the idle flag is not
		 * set even though the ring is empty. So द्विगुन
		 * check beक्रमe giving up.
		 */
		अगर ((ENGINE_READ_FW(engine, RING_HEAD) & HEAD_ADDR) !=
		    (ENGINE_READ_FW(engine, RING_TAIL) & TAIL_ADDR))
			err = -ETIMEDOUT;
	पूर्ण

	वापस err;
पूर्ण

व्योम पूर्णांकel_engine_cancel_stop_cs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	ENGINE_TRACE(engine, "\n");

	ENGINE_WRITE_FW(engine, RING_MI_MODE, _MASKED_BIT_DISABLE(STOP_RING));
पूर्ण

स्थिर अक्षर *i915_cache_level_str(काष्ठा drm_i915_निजी *i915, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल I915_CACHE_NONE: वापस " uncached";
	हाल I915_CACHE_LLC: वापस HAS_LLC(i915) ? " LLC" : " snooped";
	हाल I915_CACHE_L3_LLC: वापस " L3+LLC";
	हाल I915_CACHE_WT: वापस " WT";
	शेष: वापस "";
	पूर्ण
पूर्ण

अटल u32
पढ़ो_subslice_reg(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		  पूर्णांक slice, पूर्णांक subslice, i915_reg_t reg)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	u32 mcr_mask, mcr_ss, mcr, old_mcr, val;
	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs;

	अगर (INTEL_GEN(i915) >= 11) अणु
		mcr_mask = GEN11_MCR_SLICE_MASK | GEN11_MCR_SUBSLICE_MASK;
		mcr_ss = GEN11_MCR_SLICE(slice) | GEN11_MCR_SUBSLICE(subslice);
	पूर्ण अन्यथा अणु
		mcr_mask = GEN8_MCR_SLICE_MASK | GEN8_MCR_SUBSLICE_MASK;
		mcr_ss = GEN8_MCR_SLICE(slice) | GEN8_MCR_SUBSLICE(subslice);
	पूर्ण

	fw_करोमुख्यs = पूर्णांकel_uncore_क्रमcewake_क्रम_reg(uncore, reg,
						    FW_REG_READ);
	fw_करोमुख्यs |= पूर्णांकel_uncore_क्रमcewake_क्रम_reg(uncore,
						     GEN8_MCR_SELECTOR,
						     FW_REG_READ | FW_REG_WRITE);

	spin_lock_irq(&uncore->lock);
	पूर्णांकel_uncore_क्रमcewake_get__locked(uncore, fw_करोमुख्यs);

	old_mcr = mcr = पूर्णांकel_uncore_पढ़ो_fw(uncore, GEN8_MCR_SELECTOR);

	mcr &= ~mcr_mask;
	mcr |= mcr_ss;
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN8_MCR_SELECTOR, mcr);

	val = पूर्णांकel_uncore_पढ़ो_fw(uncore, reg);

	mcr &= ~mcr_mask;
	mcr |= old_mcr & mcr_mask;

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN8_MCR_SELECTOR, mcr);

	पूर्णांकel_uncore_क्रमcewake_put__locked(uncore, fw_करोमुख्यs);
	spin_unlock_irq(&uncore->lock);

	वापस val;
पूर्ण

/* NB: please notice the स_रखो */
व्योम पूर्णांकel_engine_get_instकरोne(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			       काष्ठा पूर्णांकel_instकरोne *instकरोne)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;
	स्थिर काष्ठा sseu_dev_info *sseu = &engine->gt->info.sseu;
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	u32 mmio_base = engine->mmio_base;
	पूर्णांक slice;
	पूर्णांक subslice;

	स_रखो(instकरोne, 0, माप(*instकरोne));

	चयन (INTEL_GEN(i915)) अणु
	शेष:
		instकरोne->instकरोne =
			पूर्णांकel_uncore_पढ़ो(uncore, RING_INSTDONE(mmio_base));

		अगर (engine->id != RCS0)
			अवरोध;

		instकरोne->slice_common =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN7_SC_INSTDONE);
		अगर (INTEL_GEN(i915) >= 12) अणु
			instकरोne->slice_common_extra[0] =
				पूर्णांकel_uncore_पढ़ो(uncore, GEN12_SC_INSTDONE_EXTRA);
			instकरोne->slice_common_extra[1] =
				पूर्णांकel_uncore_पढ़ो(uncore, GEN12_SC_INSTDONE_EXTRA2);
		पूर्ण
		क्रम_each_instकरोne_slice_subslice(i915, sseu, slice, subslice) अणु
			instकरोne->sampler[slice][subslice] =
				पढ़ो_subslice_reg(engine, slice, subslice,
						  GEN7_SAMPLER_INSTDONE);
			instकरोne->row[slice][subslice] =
				पढ़ो_subslice_reg(engine, slice, subslice,
						  GEN7_ROW_INSTDONE);
		पूर्ण
		अवरोध;
	हाल 7:
		instकरोne->instकरोne =
			पूर्णांकel_uncore_पढ़ो(uncore, RING_INSTDONE(mmio_base));

		अगर (engine->id != RCS0)
			अवरोध;

		instकरोne->slice_common =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN7_SC_INSTDONE);
		instकरोne->sampler[0][0] =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN7_SAMPLER_INSTDONE);
		instकरोne->row[0][0] =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN7_ROW_INSTDONE);

		अवरोध;
	हाल 6:
	हाल 5:
	हाल 4:
		instकरोne->instकरोne =
			पूर्णांकel_uncore_पढ़ो(uncore, RING_INSTDONE(mmio_base));
		अगर (engine->id == RCS0)
			/* HACK: Using the wrong काष्ठा member */
			instकरोne->slice_common =
				पूर्णांकel_uncore_पढ़ो(uncore, GEN4_INSTDONE1);
		अवरोध;
	हाल 3:
	हाल 2:
		instकरोne->instकरोne = पूर्णांकel_uncore_पढ़ो(uncore, GEN2_INSTDONE);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool ring_is_idle(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	bool idle = true;

	अगर (I915_SELFTEST_ONLY(!engine->mmio_base))
		वापस true;

	अगर (!पूर्णांकel_engine_pm_get_अगर_awake(engine))
		वापस true;

	/* First check that no commands are left in the ring */
	अगर ((ENGINE_READ(engine, RING_HEAD) & HEAD_ADDR) !=
	    (ENGINE_READ(engine, RING_TAIL) & TAIL_ADDR))
		idle = false;

	/* No bit क्रम gen2, so assume the CS parser is idle */
	अगर (INTEL_GEN(engine->i915) > 2 &&
	    !(ENGINE_READ(engine, RING_MI_MODE) & MODE_IDLE))
		idle = false;

	पूर्णांकel_engine_pm_put(engine);

	वापस idle;
पूर्ण

व्योम __पूर्णांकel_engine_flush_submission(काष्ठा पूर्णांकel_engine_cs *engine, bool sync)
अणु
	काष्ठा tasklet_काष्ठा *t = &engine->execlists.tasklet;

	अगर (!t->callback)
		वापस;

	local_bh_disable();
	अगर (tasklet_trylock(t)) अणु
		/* Must रुको क्रम any GPU reset in progress. */
		अगर (__tasklet_is_enabled(t))
			t->callback(t);
		tasklet_unlock(t);
	पूर्ण
	local_bh_enable();

	/* Synchronise and रुको क्रम the tasklet on another CPU */
	अगर (sync)
		tasklet_unlock_रुको(t);
पूर्ण

/**
 * पूर्णांकel_engine_is_idle() - Report अगर the engine has finished process all work
 * @engine: the पूर्णांकel_engine_cs
 *
 * Return true अगर there are no requests pending, nothing left to be submitted
 * to hardware, and that the engine is idle.
 */
bool पूर्णांकel_engine_is_idle(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/* More white lies, अगर wedged, hw state is inconsistent */
	अगर (पूर्णांकel_gt_is_wedged(engine->gt))
		वापस true;

	अगर (!पूर्णांकel_engine_pm_is_awake(engine))
		वापस true;

	/* Waiting to drain ELSP? */
	synchronize_hardirq(to_pci_dev(engine->i915->drm.dev)->irq);
	पूर्णांकel_engine_flush_submission(engine);

	/* ELSP is empty, but there are पढ़ोy requests? E.g. after reset */
	अगर (!RB_EMPTY_ROOT(&engine->execlists.queue.rb_root))
		वापस false;

	/* Ring stopped? */
	वापस ring_is_idle(engine);
पूर्ण

bool पूर्णांकel_engines_are_idle(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * If the driver is wedged, HW state may be very inconsistent and
	 * report that it is still busy, even though we have stopped using it.
	 */
	अगर (पूर्णांकel_gt_is_wedged(gt))
		वापस true;

	/* Alपढ़ोy parked (and passed an idleness test); must still be idle */
	अगर (!READ_ONCE(gt->awake))
		वापस true;

	क्रम_each_engine(engine, gt, id) अणु
		अगर (!पूर्णांकel_engine_is_idle(engine))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम पूर्णांकel_engines_reset_शेष_submission(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt, id) अणु
		अगर (engine->sanitize)
			engine->sanitize(engine);

		engine->set_शेष_submission(engine);
	पूर्ण
पूर्ण

bool पूर्णांकel_engine_can_store_dword(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	चयन (INTEL_GEN(engine->i915)) अणु
	हाल 2:
		वापस false; /* uses physical not भव addresses */
	हाल 3:
		/* maybe only uses physical not भव addresses */
		वापस !(IS_I915G(engine->i915) || IS_I915GM(engine->i915));
	हाल 4:
		वापस !IS_I965G(engine->i915); /* who knows! */
	हाल 6:
		वापस engine->class != VIDEO_DECODE_CLASS; /* b0rked */
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल काष्ठा पूर्णांकel_समयline *get_समयline(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_समयline *tl;

	/*
	 * Even though we are holding the engine->active.lock here, there
	 * is no control over the submission queue per-se and we are
	 * inspecting the active state at a अक्रमom poपूर्णांक in समय, with an
	 * unknown queue. Play safe and make sure the समयline reमुख्यs valid.
	 * (Only being used क्रम pretty prपूर्णांकing, one extra kref shouldn't
	 * cause a camel stampede!)
	 */
	rcu_पढ़ो_lock();
	tl = rcu_dereference(rq->समयline);
	अगर (!kref_get_unless_zero(&tl->kref))
		tl = शून्य;
	rcu_पढ़ो_unlock();

	वापस tl;
पूर्ण

अटल पूर्णांक prपूर्णांक_ring(अक्षर *buf, पूर्णांक sz, काष्ठा i915_request *rq)
अणु
	पूर्णांक len = 0;

	अगर (!i915_request_संकेतed(rq)) अणु
		काष्ठा पूर्णांकel_समयline *tl = get_समयline(rq);

		len = scnम_लिखो(buf, sz,
				"ring:{start:%08x, hwsp:%08x, seqno:%08x, runtime:%llums}, ",
				i915_ggtt_offset(rq->ring->vma),
				tl ? tl->hwsp_offset : 0,
				hwsp_seqno(rq),
				DIV_ROUND_CLOSEST_ULL(पूर्णांकel_context_get_total_runसमय_ns(rq->context),
						      1000 * 1000));

		अगर (tl)
			पूर्णांकel_समयline_put(tl);
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम hexdump(काष्ठा drm_prपूर्णांकer *m, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	स्थिर माप_प्रकार rowsize = 8 * माप(u32);
	स्थिर व्योम *prev = शून्य;
	bool skip = false;
	माप_प्रकार pos;

	क्रम (pos = 0; pos < len; pos += rowsize) अणु
		अक्षर line[128];

		अगर (prev && !स_भेद(prev, buf + pos, rowsize)) अणु
			अगर (!skip) अणु
				drm_म_लिखो(m, "*\n");
				skip = true;
			पूर्ण
			जारी;
		पूर्ण

		WARN_ON_ONCE(hex_dump_to_buffer(buf + pos, len - pos,
						rowsize, माप(u32),
						line, माप(line),
						false) >= माप(line));
		drm_म_लिखो(m, "[%04zx] %s\n", pos, line);

		prev = buf + pos;
		skip = false;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *repr_समयr(स्थिर काष्ठा समयr_list *t)
अणु
	अगर (!READ_ONCE(t->expires))
		वापस "inactive";

	अगर (समयr_pending(t))
		वापस "active";

	वापस "expired";
पूर्ण

अटल व्योम पूर्णांकel_engine_prपूर्णांक_रेजिस्टरs(काष्ठा पूर्णांकel_engine_cs *engine,
					 काष्ठा drm_prपूर्णांकer *m)
अणु
	काष्ठा drm_i915_निजी *dev_priv = engine->i915;
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	u64 addr;

	अगर (engine->id == RENDER_CLASS && IS_GEN_RANGE(dev_priv, 4, 7))
		drm_म_लिखो(m, "\tCCID: 0x%08x\n", ENGINE_READ(engine, CCID));
	अगर (HAS_EXECLISTS(dev_priv)) अणु
		drm_म_लिखो(m, "\tEL_STAT_HI: 0x%08x\n",
			   ENGINE_READ(engine, RING_EXECLIST_STATUS_HI));
		drm_म_लिखो(m, "\tEL_STAT_LO: 0x%08x\n",
			   ENGINE_READ(engine, RING_EXECLIST_STATUS_LO));
	पूर्ण
	drm_म_लिखो(m, "\tRING_START: 0x%08x\n",
		   ENGINE_READ(engine, RING_START));
	drm_म_लिखो(m, "\tRING_HEAD:  0x%08x\n",
		   ENGINE_READ(engine, RING_HEAD) & HEAD_ADDR);
	drm_म_लिखो(m, "\tRING_TAIL:  0x%08x\n",
		   ENGINE_READ(engine, RING_TAIL) & TAIL_ADDR);
	drm_म_लिखो(m, "\tRING_CTL:   0x%08x%s\n",
		   ENGINE_READ(engine, RING_CTL),
		   ENGINE_READ(engine, RING_CTL) & (RING_WAIT | RING_WAIT_SEMAPHORE) ? " [waiting]" : "");
	अगर (INTEL_GEN(engine->i915) > 2) अणु
		drm_म_लिखो(m, "\tRING_MODE:  0x%08x%s\n",
			   ENGINE_READ(engine, RING_MI_MODE),
			   ENGINE_READ(engine, RING_MI_MODE) & (MODE_IDLE) ? " [idle]" : "");
	पूर्ण

	अगर (INTEL_GEN(dev_priv) >= 6) अणु
		drm_म_लिखो(m, "\tRING_IMR:   0x%08x\n",
			   ENGINE_READ(engine, RING_IMR));
		drm_म_लिखो(m, "\tRING_ESR:   0x%08x\n",
			   ENGINE_READ(engine, RING_ESR));
		drm_म_लिखो(m, "\tRING_EMR:   0x%08x\n",
			   ENGINE_READ(engine, RING_EMR));
		drm_म_लिखो(m, "\tRING_EIR:   0x%08x\n",
			   ENGINE_READ(engine, RING_EIR));
	पूर्ण

	addr = पूर्णांकel_engine_get_active_head(engine);
	drm_म_लिखो(m, "\tACTHD:  0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	addr = पूर्णांकel_engine_get_last_batch_head(engine);
	drm_म_लिखो(m, "\tBBADDR: 0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	अगर (INTEL_GEN(dev_priv) >= 8)
		addr = ENGINE_READ64(engine, RING_DMA_FADD, RING_DMA_FADD_UDW);
	अन्यथा अगर (INTEL_GEN(dev_priv) >= 4)
		addr = ENGINE_READ(engine, RING_DMA_FADD);
	अन्यथा
		addr = ENGINE_READ(engine, DMA_FADD_I8XX);
	drm_म_लिखो(m, "\tDMA_FADDR: 0x%08x_%08x\n",
		   upper_32_bits(addr), lower_32_bits(addr));
	अगर (INTEL_GEN(dev_priv) >= 4) अणु
		drm_म_लिखो(m, "\tIPEIR: 0x%08x\n",
			   ENGINE_READ(engine, RING_IPEIR));
		drm_म_लिखो(m, "\tIPEHR: 0x%08x\n",
			   ENGINE_READ(engine, RING_IPEHR));
	पूर्ण अन्यथा अणु
		drm_म_लिखो(m, "\tIPEIR: 0x%08x\n", ENGINE_READ(engine, IPEIR));
		drm_म_लिखो(m, "\tIPEHR: 0x%08x\n", ENGINE_READ(engine, IPEHR));
	पूर्ण

	अगर (पूर्णांकel_engine_in_guc_submission_mode(engine)) अणु
		/* nothing to prपूर्णांक yet */
	पूर्ण अन्यथा अगर (HAS_EXECLISTS(dev_priv)) अणु
		काष्ठा i915_request * स्थिर *port, *rq;
		स्थिर u32 *hws =
			&engine->status_page.addr[I915_HWS_CSB_BUF0_INDEX];
		स्थिर u8 num_entries = execlists->csb_size;
		अचिन्हित पूर्णांक idx;
		u8 पढ़ो, ग_लिखो;

		drm_म_लिखो(m, "\tExeclist tasklet queued? %s (%s), preempt? %s, timeslice? %s\n",
			   yesno(test_bit(TASKLET_STATE_SCHED,
					  &engine->execlists.tasklet.state)),
			   enableddisabled(!atomic_पढ़ो(&engine->execlists.tasklet.count)),
			   repr_समयr(&engine->execlists.preempt),
			   repr_समयr(&engine->execlists.समयr));

		पढ़ो = execlists->csb_head;
		ग_लिखो = READ_ONCE(*execlists->csb_ग_लिखो);

		drm_म_लिखो(m, "\tExeclist status: 0x%08x %08x; CSB read:%d, write:%d, entries:%d\n",
			   ENGINE_READ(engine, RING_EXECLIST_STATUS_LO),
			   ENGINE_READ(engine, RING_EXECLIST_STATUS_HI),
			   पढ़ो, ग_लिखो, num_entries);

		अगर (पढ़ो >= num_entries)
			पढ़ो = 0;
		अगर (ग_लिखो >= num_entries)
			ग_लिखो = 0;
		अगर (पढ़ो > ग_लिखो)
			ग_लिखो += num_entries;
		जबतक (पढ़ो < ग_लिखो) अणु
			idx = ++पढ़ो % num_entries;
			drm_म_लिखो(m, "\tExeclist CSB[%d]: 0x%08x, context: %d\n",
				   idx, hws[idx * 2], hws[idx * 2 + 1]);
		पूर्ण

		execlists_active_lock_bh(execlists);
		rcu_पढ़ो_lock();
		क्रम (port = execlists->active; (rq = *port); port++) अणु
			अक्षर hdr[160];
			पूर्णांक len;

			len = scnम_लिखो(hdr, माप(hdr),
					"\t\tActive[%d]:  ccid:%08x%s%s, ",
					(पूर्णांक)(port - execlists->active),
					rq->context->lrc.ccid,
					पूर्णांकel_context_is_बंदd(rq->context) ? "!" : "",
					पूर्णांकel_context_is_banned(rq->context) ? "*" : "");
			len += prपूर्णांक_ring(hdr + len, माप(hdr) - len, rq);
			scnम_लिखो(hdr + len, माप(hdr) - len, "rq: ");
			i915_request_show(m, rq, hdr, 0);
		पूर्ण
		क्रम (port = execlists->pending; (rq = *port); port++) अणु
			अक्षर hdr[160];
			पूर्णांक len;

			len = scnम_लिखो(hdr, माप(hdr),
					"\t\tPending[%d]: ccid:%08x%s%s, ",
					(पूर्णांक)(port - execlists->pending),
					rq->context->lrc.ccid,
					पूर्णांकel_context_is_बंदd(rq->context) ? "!" : "",
					पूर्णांकel_context_is_banned(rq->context) ? "*" : "");
			len += prपूर्णांक_ring(hdr + len, माप(hdr) - len, rq);
			scnम_लिखो(hdr + len, माप(hdr) - len, "rq: ");
			i915_request_show(m, rq, hdr, 0);
		पूर्ण
		rcu_पढ़ो_unlock();
		execlists_active_unlock_bh(execlists);
	पूर्ण अन्यथा अगर (INTEL_GEN(dev_priv) > 6) अणु
		drm_म_लिखो(m, "\tPP_DIR_BASE: 0x%08x\n",
			   ENGINE_READ(engine, RING_PP_सूची_BASE));
		drm_म_लिखो(m, "\tPP_DIR_BASE_READ: 0x%08x\n",
			   ENGINE_READ(engine, RING_PP_सूची_BASE_READ));
		drm_म_लिखो(m, "\tPP_DIR_DCLV: 0x%08x\n",
			   ENGINE_READ(engine, RING_PP_सूची_DCLV));
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_request_ring(काष्ठा drm_prपूर्णांकer *m, काष्ठा i915_request *rq)
अणु
	व्योम *ring;
	पूर्णांक size;

	drm_म_लिखो(m,
		   "[head %04x, postfix %04x, tail %04x, batch 0x%08x_%08x]:\n",
		   rq->head, rq->postfix, rq->tail,
		   rq->batch ? upper_32_bits(rq->batch->node.start) : ~0u,
		   rq->batch ? lower_32_bits(rq->batch->node.start) : ~0u);

	size = rq->tail - rq->head;
	अगर (rq->tail < rq->head)
		size += rq->ring->size;

	ring = kदो_स्मृति(size, GFP_ATOMIC);
	अगर (ring) अणु
		स्थिर व्योम *vaddr = rq->ring->vaddr;
		अचिन्हित पूर्णांक head = rq->head;
		अचिन्हित पूर्णांक len = 0;

		अगर (rq->tail < head) अणु
			len = rq->ring->size - head;
			स_नकल(ring, vaddr + head, len);
			head = 0;
		पूर्ण
		स_नकल(ring + len, vaddr + head, size - len);

		hexdump(m, ring, size);
		kमुक्त(ring);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ list_count(काष्ठा list_head *list)
अणु
	काष्ठा list_head *pos;
	अचिन्हित दीर्घ count = 0;

	list_क्रम_each(pos, list)
		count++;

	वापस count;
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_ul(व्योम *p, माप_प्रकार x)
अणु
	वापस *(अचिन्हित दीर्घ *)(p + x);
पूर्ण

अटल व्योम prपूर्णांक_properties(काष्ठा पूर्णांकel_engine_cs *engine,
			     काष्ठा drm_prपूर्णांकer *m)
अणु
	अटल स्थिर काष्ठा pmap अणु
		माप_प्रकार offset;
		स्थिर अक्षर *name;
	पूर्ण props[] = अणु
#घोषणा P(x) अणु \
	.offset = दुरत्व(typeof(engine->props), x), \
	.name = #x \
पूर्ण
		P(heartbeat_पूर्णांकerval_ms),
		P(max_busyरुको_duration_ns),
		P(preempt_समयout_ms),
		P(stop_समयout_ms),
		P(बारlice_duration_ms),

		अणुपूर्ण,
#अघोषित P
	पूर्ण;
	स्थिर काष्ठा pmap *p;

	drm_म_लिखो(m, "\tProperties:\n");
	क्रम (p = props; p->name; p++)
		drm_म_लिखो(m, "\t\t%s: %lu [default %lu]\n",
			   p->name,
			   पढ़ो_ul(&engine->props, p->offset),
			   पढ़ो_ul(&engine->शेषs, p->offset));
पूर्ण

व्योम पूर्णांकel_engine_dump(काष्ठा पूर्णांकel_engine_cs *engine,
		       काष्ठा drm_prपूर्णांकer *m,
		       स्थिर अक्षर *header, ...)
अणु
	काष्ठा i915_gpu_error * स्थिर error = &engine->i915->gpu_error;
	काष्ठा i915_request *rq;
	पूर्णांकel_wakeref_t wakeref;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार dummy;

	अगर (header) अणु
		बहु_सूची ap;

		बहु_शुरू(ap, header);
		drm_भ_लिखो(m, header, &ap);
		बहु_पूर्ण(ap);
	पूर्ण

	अगर (पूर्णांकel_gt_is_wedged(engine->gt))
		drm_म_लिखो(m, "*** WEDGED ***\n");

	drm_म_लिखो(m, "\tAwake? %d\n", atomic_पढ़ो(&engine->wakeref.count));
	drm_म_लिखो(m, "\tBarriers?: %s\n",
		   yesno(!llist_empty(&engine->barrier_tasks)));
	drm_म_लिखो(m, "\tLatency: %luus\n",
		   ewma__engine_latency_पढ़ो(&engine->latency));
	अगर (पूर्णांकel_engine_supports_stats(engine))
		drm_म_लिखो(m, "\tRuntime: %llums\n",
			   kसमय_प्रकारo_ms(पूर्णांकel_engine_get_busy_समय(engine,
								  &dummy)));
	drm_म_लिखो(m, "\tForcewake: %x domains, %d active\n",
		   engine->fw_करोमुख्य, READ_ONCE(engine->fw_active));

	rcu_पढ़ो_lock();
	rq = READ_ONCE(engine->heartbeat.systole);
	अगर (rq)
		drm_म_लिखो(m, "\tHeartbeat: %d ms ago\n",
			   jअगरfies_to_msecs(jअगरfies - rq->emitted_jअगरfies));
	rcu_पढ़ो_unlock();
	drm_म_लिखो(m, "\tReset count: %d (global %d)\n",
		   i915_reset_engine_count(error, engine),
		   i915_reset_count(error));
	prपूर्णांक_properties(engine, m);

	drm_म_लिखो(m, "\tRequests:\n");

	spin_lock_irqsave(&engine->active.lock, flags);
	rq = पूर्णांकel_engine_find_active_request(engine);
	अगर (rq) अणु
		काष्ठा पूर्णांकel_समयline *tl = get_समयline(rq);

		i915_request_show(m, rq, "\t\tactive ", 0);

		drm_म_लिखो(m, "\t\tring->start:  0x%08x\n",
			   i915_ggtt_offset(rq->ring->vma));
		drm_म_लिखो(m, "\t\tring->head:   0x%08x\n",
			   rq->ring->head);
		drm_म_लिखो(m, "\t\tring->tail:   0x%08x\n",
			   rq->ring->tail);
		drm_म_लिखो(m, "\t\tring->emit:   0x%08x\n",
			   rq->ring->emit);
		drm_म_लिखो(m, "\t\tring->space:  0x%08x\n",
			   rq->ring->space);

		अगर (tl) अणु
			drm_म_लिखो(m, "\t\tring->hwsp:   0x%08x\n",
				   tl->hwsp_offset);
			पूर्णांकel_समयline_put(tl);
		पूर्ण

		prपूर्णांक_request_ring(m, rq);

		अगर (rq->context->lrc_reg_state) अणु
			drm_म_लिखो(m, "Logical Ring Context:\n");
			hexdump(m, rq->context->lrc_reg_state, PAGE_SIZE);
		पूर्ण
	पूर्ण
	drm_म_लिखो(m, "\tOn hold?: %lu\n", list_count(&engine->active.hold));
	spin_unlock_irqrestore(&engine->active.lock, flags);

	drm_म_लिखो(m, "\tMMIO base:  0x%08x\n", engine->mmio_base);
	wakeref = पूर्णांकel_runसमय_pm_get_अगर_in_use(engine->uncore->rpm);
	अगर (wakeref) अणु
		पूर्णांकel_engine_prपूर्णांक_रेजिस्टरs(engine, m);
		पूर्णांकel_runसमय_pm_put(engine->uncore->rpm, wakeref);
	पूर्ण अन्यथा अणु
		drm_म_लिखो(m, "\tDevice is asleep; skipping register dump\n");
	पूर्ण

	पूर्णांकel_execlists_show_requests(engine, m, i915_request_show, 8);

	drm_म_लिखो(m, "HWSP:\n");
	hexdump(m, engine->status_page.addr, PAGE_SIZE);

	drm_म_लिखो(m, "Idle? %s\n", yesno(पूर्णांकel_engine_is_idle(engine)));

	पूर्णांकel_engine_prपूर्णांक_bपढ़ोcrumbs(engine, m);
पूर्ण

अटल kसमय_प्रकार __पूर्णांकel_engine_get_busy_समय(काष्ठा पूर्णांकel_engine_cs *engine,
					    kसमय_प्रकार *now)
अणु
	kसमय_प्रकार total = engine->stats.total;

	/*
	 * If the engine is executing something at the moment
	 * add it to the total.
	 */
	*now = kसमय_get();
	अगर (READ_ONCE(engine->stats.active))
		total = kसमय_add(total, kसमय_sub(*now, engine->stats.start));

	वापस total;
पूर्ण

/**
 * पूर्णांकel_engine_get_busy_समय() - Return current accumulated engine busyness
 * @engine: engine to report on
 * @now: monotonic बारtamp of sampling
 *
 * Returns accumulated समय @engine was busy since engine stats were enabled.
 */
kसमय_प्रकार पूर्णांकel_engine_get_busy_समय(काष्ठा पूर्णांकel_engine_cs *engine, kसमय_प्रकार *now)
अणु
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार total;

	करो अणु
		seq = पढ़ो_seqcount_begin(&engine->stats.lock);
		total = __पूर्णांकel_engine_get_busy_समय(engine, now);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&engine->stats.lock, seq));

	वापस total;
पूर्ण

अटल bool match_ring(काष्ठा i915_request *rq)
अणु
	u32 ring = ENGINE_READ(rq->engine, RING_START);

	वापस ring == i915_ggtt_offset(rq->ring->vma);
पूर्ण

काष्ठा i915_request *
पूर्णांकel_engine_find_active_request(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_request *request, *active = शून्य;

	/*
	 * We are called by the error capture, reset and to dump engine
	 * state at अक्रमom poपूर्णांकs in समय. In particular, note that neither is
	 * crucially ordered with an पूर्णांकerrupt. After a hang, the GPU is dead
	 * and we assume that no more ग_लिखोs can happen (we रुकोed दीर्घ enough
	 * क्रम all ग_लिखोs that were in transaction to be flushed) - adding an
	 * extra delay क्रम a recent पूर्णांकerrupt is poपूर्णांकless. Hence, we करो
	 * not need an engine->irq_seqno_barrier() beक्रमe the seqno पढ़ोs.
	 * At all other बार, we must assume the GPU is still running, but
	 * we only care about the snapshot of this moment.
	 */
	lockdep_निश्चित_held(&engine->active.lock);

	rcu_पढ़ो_lock();
	request = execlists_active(&engine->execlists);
	अगर (request) अणु
		काष्ठा पूर्णांकel_समयline *tl = request->context->समयline;

		list_क्रम_each_entry_from_reverse(request, &tl->requests, link) अणु
			अगर (__i915_request_is_complete(request))
				अवरोध;

			active = request;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (active)
		वापस active;

	list_क्रम_each_entry(request, &engine->active.requests, sched.link) अणु
		अगर (__i915_request_is_complete(request))
			जारी;

		अगर (!__i915_request_has_started(request))
			जारी;

		/* More than one preemptible request may match! */
		अगर (!match_ring(request))
			जारी;

		active = request;
		अवरोध;
	पूर्ण

	वापस active;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "mock_engine.c"
#समावेश "selftest_engine.c"
#समावेश "selftest_engine_cs.c"
#पूर्ण_अगर
