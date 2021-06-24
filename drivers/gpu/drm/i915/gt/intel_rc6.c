<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/pm_runसमय.स>

#समावेश "i915_drv.h"
#समावेश "i915_vgpu.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_rc6.h"
#समावेश "intel_sideband.h"

/**
 * DOC: RC6
 *
 * RC6 is a special घातer stage which allows the GPU to enter an very
 * low-voltage mode when idle, using करोwn to 0V जबतक at this stage.  This
 * stage is entered स्वतःmatically when the GPU is idle when RC6 support is
 * enabled, and as soon as new workload arises GPU wakes up स्वतःmatically as
 * well.
 *
 * There are dअगरferent RC6 modes available in Intel GPU, which dअगरferentiate
 * among each other with the latency required to enter and leave RC6 and
 * voltage consumed by the GPU in dअगरferent states.
 *
 * The combination of the following flags define which states GPU is allowed
 * to enter, जबतक RC6 is the normal RC6 state, RC6p is the deep RC6, and
 * RC6pp is deepest RC6. Their support by hardware varies according to the
 * GPU, BIOS, chipset and platक्रमm. RC6 is usually the safest one and the one
 * which brings the most घातer savings; deeper states save more घातer, but
 * require higher latency to चयन to and wake up.
 */

अटल काष्ठा पूर्णांकel_gt *rc6_to_gt(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	वापस container_of(rc6, काष्ठा पूर्णांकel_gt, rc6);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore *rc6_to_uncore(काष्ठा पूर्णांकel_rc6 *rc)
अणु
	वापस rc6_to_gt(rc)->uncore;
पूर्ण

अटल काष्ठा drm_i915_निजी *rc6_to_i915(काष्ठा पूर्णांकel_rc6 *rc)
अणु
	वापस rc6_to_gt(rc)->i915;
पूर्ण

अटल व्योम set(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u32 val)
अणु
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, reg, val);
पूर्ण

अटल व्योम gen11_rc6_enable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_gt *gt = rc6_to_gt(rc6);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	u32 pg_enable;
	पूर्णांक i;

	/* 2b: Program RC6 thresholds.*/
	set(uncore, GEN6_RC6_WAKE_RATE_LIMIT, 54 << 16 | 85);
	set(uncore, GEN10_MEDIA_WAKE_RATE_LIMIT, 150);

	set(uncore, GEN6_RC_EVALUATION_INTERVAL, 125000); /* 12500 * 1280ns */
	set(uncore, GEN6_RC_IDLE_HYSTERSIS, 25); /* 25 * 1280ns */
	क्रम_each_engine(engine, rc6_to_gt(rc6), id)
		set(uncore, RING_MAX_IDLE(engine->mmio_base), 10);

	set(uncore, GUC_MAX_IDLE_COUNT, 0xA);

	set(uncore, GEN6_RC_SLEEP, 0);

	set(uncore, GEN6_RC6_THRESHOLD, 50000); /* 50/125ms per EI */

	/*
	 * 2c: Program Coarse Power Gating Policies.
	 *
	 * Bspec's guidance is to use 25us (really 25 * 1280ns) here. What we
	 * use instead is a more conservative estimate क्रम the maximum समय
	 * it takes us to service a CS पूर्णांकerrupt and submit a new ELSP - that
	 * is the समय which the GPU is idle रुकोing क्रम the CPU to select the
	 * next request to execute. If the idle hysteresis is less than that
	 * पूर्णांकerrupt service latency, the hardware will स्वतःmatically gate
	 * the घातer well and we will then incur the wake up cost on top of
	 * the service latency. A similar guide from plane_state is that we
	 * करो not want the enable hysteresis to less than the wakeup latency.
	 *
	 * igt/gem_exec_nop/sequential provides a rough estimate क्रम the
	 * service latency, and माला_दो it under 10us क्रम Icelake, similar to
	 * Broadwell+, To be conservative, we want to factor in a context
	 * चयन on top (due to ksoftirqd).
	 */
	set(uncore, GEN9_MEDIA_PG_IDLE_HYSTERESIS, 60);
	set(uncore, GEN9_RENDER_PG_IDLE_HYSTERESIS, 60);

	/* 3a: Enable RC6 */
	rc6->ctl_enable =
		GEN6_RC_CTL_HW_ENABLE |
		GEN6_RC_CTL_RC6_ENABLE |
		GEN6_RC_CTL_EI_MODE(1);

	pg_enable =
		GEN9_RENDER_PG_ENABLE |
		GEN9_MEDIA_PG_ENABLE |
		GEN11_MEDIA_SAMPLER_PG_ENABLE;

	अगर (INTEL_GEN(gt->i915) >= 12) अणु
		क्रम (i = 0; i < I915_MAX_VCS; i++)
			अगर (HAS_ENGINE(gt, _VCS(i)))
				pg_enable |= (VDN_HCP_POWERGATE_ENABLE(i) |
					      VDN_MFX_POWERGATE_ENABLE(i));
	पूर्ण

	set(uncore, GEN9_PG_ENABLE, pg_enable);
पूर्ण

अटल व्योम gen9_rc6_enable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/* 2b: Program RC6 thresholds.*/
	अगर (INTEL_GEN(rc6_to_i915(rc6)) >= 10) अणु
		set(uncore, GEN6_RC6_WAKE_RATE_LIMIT, 54 << 16 | 85);
		set(uncore, GEN10_MEDIA_WAKE_RATE_LIMIT, 150);
	पूर्ण अन्यथा अगर (IS_SKYLAKE(rc6_to_i915(rc6))) अणु
		/*
		 * WaRsDoubleRc6WrlWithCoarsePowerGating:skl Doubling WRL only
		 * when CPG is enabled
		 */
		set(uncore, GEN6_RC6_WAKE_RATE_LIMIT, 108 << 16);
	पूर्ण अन्यथा अणु
		set(uncore, GEN6_RC6_WAKE_RATE_LIMIT, 54 << 16);
	पूर्ण

	set(uncore, GEN6_RC_EVALUATION_INTERVAL, 125000); /* 12500 * 1280ns */
	set(uncore, GEN6_RC_IDLE_HYSTERSIS, 25); /* 25 * 1280ns */
	क्रम_each_engine(engine, rc6_to_gt(rc6), id)
		set(uncore, RING_MAX_IDLE(engine->mmio_base), 10);

	set(uncore, GUC_MAX_IDLE_COUNT, 0xA);

	set(uncore, GEN6_RC_SLEEP, 0);

	/*
	 * 2c: Program Coarse Power Gating Policies.
	 *
	 * Bspec's guidance is to use 25us (really 25 * 1280ns) here. What we
	 * use instead is a more conservative estimate क्रम the maximum समय
	 * it takes us to service a CS पूर्णांकerrupt and submit a new ELSP - that
	 * is the समय which the GPU is idle रुकोing क्रम the CPU to select the
	 * next request to execute. If the idle hysteresis is less than that
	 * पूर्णांकerrupt service latency, the hardware will स्वतःmatically gate
	 * the घातer well and we will then incur the wake up cost on top of
	 * the service latency. A similar guide from plane_state is that we
	 * करो not want the enable hysteresis to less than the wakeup latency.
	 *
	 * igt/gem_exec_nop/sequential provides a rough estimate क्रम the
	 * service latency, and माला_दो it around 10us क्रम Broadwell (and other
	 * big core) and around 40us क्रम Broxton (and other low घातer cores).
	 * [Note that क्रम legacy ringbuffer submission, this is less than 1us!]
	 * However, the wakeup latency on Broxton is बंदr to 100us. To be
	 * conservative, we have to factor in a context चयन on top (due
	 * to ksoftirqd).
	 */
	set(uncore, GEN9_MEDIA_PG_IDLE_HYSTERESIS, 250);
	set(uncore, GEN9_RENDER_PG_IDLE_HYSTERESIS, 250);

	/* 3a: Enable RC6 */
	set(uncore, GEN6_RC6_THRESHOLD, 37500); /* 37.5/125ms per EI */

	rc6->ctl_enable =
		GEN6_RC_CTL_HW_ENABLE |
		GEN6_RC_CTL_RC6_ENABLE |
		GEN6_RC_CTL_EI_MODE(1);

	/*
	 * WaRsDisableCoarsePowerGating:skl,cnl
	 *   - Render/Media PG need to be disabled with RC6.
	 */
	अगर (!NEEDS_WaRsDisableCoarsePowerGating(rc6_to_i915(rc6)))
		set(uncore, GEN9_PG_ENABLE,
		    GEN9_RENDER_PG_ENABLE | GEN9_MEDIA_PG_ENABLE);
पूर्ण

अटल व्योम gen8_rc6_enable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/* 2b: Program RC6 thresholds.*/
	set(uncore, GEN6_RC6_WAKE_RATE_LIMIT, 40 << 16);
	set(uncore, GEN6_RC_EVALUATION_INTERVAL, 125000); /* 12500 * 1280ns */
	set(uncore, GEN6_RC_IDLE_HYSTERSIS, 25); /* 25 * 1280ns */
	क्रम_each_engine(engine, rc6_to_gt(rc6), id)
		set(uncore, RING_MAX_IDLE(engine->mmio_base), 10);
	set(uncore, GEN6_RC_SLEEP, 0);
	set(uncore, GEN6_RC6_THRESHOLD, 625); /* 800us/1.28 क्रम TO */

	/* 3: Enable RC6 */
	rc6->ctl_enable =
	    GEN6_RC_CTL_HW_ENABLE |
	    GEN7_RC_CTL_TO_MODE |
	    GEN6_RC_CTL_RC6_ENABLE;
पूर्ण

अटल व्योम gen6_rc6_enable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	u32 rc6vids, rc6_mask;
	पूर्णांक ret;

	set(uncore, GEN6_RC1_WAKE_RATE_LIMIT, 1000 << 16);
	set(uncore, GEN6_RC6_WAKE_RATE_LIMIT, 40 << 16 | 30);
	set(uncore, GEN6_RC6pp_WAKE_RATE_LIMIT, 30);
	set(uncore, GEN6_RC_EVALUATION_INTERVAL, 125000);
	set(uncore, GEN6_RC_IDLE_HYSTERSIS, 25);

	क्रम_each_engine(engine, rc6_to_gt(rc6), id)
		set(uncore, RING_MAX_IDLE(engine->mmio_base), 10);

	set(uncore, GEN6_RC_SLEEP, 0);
	set(uncore, GEN6_RC1e_THRESHOLD, 1000);
	set(uncore, GEN6_RC6_THRESHOLD, 50000);
	set(uncore, GEN6_RC6p_THRESHOLD, 150000);
	set(uncore, GEN6_RC6pp_THRESHOLD, 64000); /* unused */

	/* We करोn't use those on Haswell */
	rc6_mask = GEN6_RC_CTL_RC6_ENABLE;
	अगर (HAS_RC6p(i915))
		rc6_mask |= GEN6_RC_CTL_RC6p_ENABLE;
	अगर (HAS_RC6pp(i915))
		rc6_mask |= GEN6_RC_CTL_RC6pp_ENABLE;
	rc6->ctl_enable =
	    rc6_mask |
	    GEN6_RC_CTL_EI_MODE(1) |
	    GEN6_RC_CTL_HW_ENABLE;

	rc6vids = 0;
	ret = sandybridge_pcode_पढ़ो(i915, GEN6_PCODE_READ_RC6VIDS,
				     &rc6vids, शून्य);
	अगर (IS_GEN(i915, 6) && ret) अणु
		drm_dbg(&i915->drm, "Couldn't check for BIOS workaround\n");
	पूर्ण अन्यथा अगर (IS_GEN(i915, 6) &&
		   (GEN6_DECODE_RC6_VID(rc6vids & 0xff) < 450)) अणु
		drm_dbg(&i915->drm,
			"You should update your BIOS. Correcting minimum rc6 voltage (%dmV->%dmV)\n",
			GEN6_DECODE_RC6_VID(rc6vids & 0xff), 450);
		rc6vids &= 0xffff00;
		rc6vids |= GEN6_ENCODE_RC6_VID(450);
		ret = sandybridge_pcode_ग_लिखो(i915, GEN6_PCODE_WRITE_RC6VIDS, rc6vids);
		अगर (ret)
			drm_err(&i915->drm,
				"Couldn't fix incorrect rc6 voltage\n");
	पूर्ण
पूर्ण

/* Check that the pcbr address is not empty. */
अटल पूर्णांक chv_rc6_init(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);
	resource_माप_प्रकार pctx_paddr, paddr;
	resource_माप_प्रकार pctx_size = 32 * SZ_1K;
	u32 pcbr;

	pcbr = पूर्णांकel_uncore_पढ़ो(uncore, VLV_PCBR);
	अगर ((pcbr >> VLV_PCBR_ADDR_SHIFT) == 0) अणु
		drm_dbg(&i915->drm, "BIOS didn't set up PCBR, fixing up\n");
		paddr = i915->dsm.end + 1 - pctx_size;
		GEM_BUG_ON(paddr > U32_MAX);

		pctx_paddr = (paddr & ~4095);
		पूर्णांकel_uncore_ग_लिखो(uncore, VLV_PCBR, pctx_paddr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vlv_rc6_init(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	काष्ठा drm_i915_gem_object *pctx;
	resource_माप_प्रकार pctx_paddr;
	resource_माप_प्रकार pctx_size = 24 * SZ_1K;
	u32 pcbr;

	pcbr = पूर्णांकel_uncore_पढ़ो(uncore, VLV_PCBR);
	अगर (pcbr) अणु
		/* BIOS set it up alपढ़ोy, grab the pre-alloc'd space */
		resource_माप_प्रकार pcbr_offset;

		pcbr_offset = (pcbr & ~4095) - i915->dsm.start;
		pctx = i915_gem_object_create_stolen_क्रम_pपुनः_स्मृतिated(i915,
								      pcbr_offset,
								      pctx_size);
		अगर (IS_ERR(pctx))
			वापस PTR_ERR(pctx);

		जाओ out;
	पूर्ण

	drm_dbg(&i915->drm, "BIOS didn't set up PCBR, fixing up\n");

	/*
	 * From the Gunit रेजिस्टर HAS:
	 * The Gfx driver is expected to program this रेजिस्टर and ensure
	 * proper allocation within Gfx stolen memory.  For example, this
	 * रेजिस्टर should be programmed such than the PCBR range करोes not
	 * overlap with other ranges, such as the frame buffer, रक्षित
	 * memory, or any other relevant ranges.
	 */
	pctx = i915_gem_object_create_stolen(i915, pctx_size);
	अगर (IS_ERR(pctx)) अणु
		drm_dbg(&i915->drm,
			"not enough stolen space for PCTX, disabling\n");
		वापस PTR_ERR(pctx);
	पूर्ण

	GEM_BUG_ON(range_overflows_end_t(u64,
					 i915->dsm.start,
					 pctx->stolen->start,
					 U32_MAX));
	pctx_paddr = i915->dsm.start + pctx->stolen->start;
	पूर्णांकel_uncore_ग_लिखो(uncore, VLV_PCBR, pctx_paddr);

out:
	rc6->pctx = pctx;
	वापस 0;
पूर्ण

अटल व्योम chv_rc6_enable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/* 2a: Program RC6 thresholds.*/
	set(uncore, GEN6_RC6_WAKE_RATE_LIMIT, 40 << 16);
	set(uncore, GEN6_RC_EVALUATION_INTERVAL, 125000); /* 12500 * 1280ns */
	set(uncore, GEN6_RC_IDLE_HYSTERSIS, 25); /* 25 * 1280ns */

	क्रम_each_engine(engine, rc6_to_gt(rc6), id)
		set(uncore, RING_MAX_IDLE(engine->mmio_base), 10);
	set(uncore, GEN6_RC_SLEEP, 0);

	/* TO threshold set to 500 us (0x186 * 1.28 us) */
	set(uncore, GEN6_RC6_THRESHOLD, 0x186);

	/* Allows RC6 residency counter to work */
	set(uncore, VLV_COUNTER_CONTROL,
	    _MASKED_BIT_ENABLE(VLV_COUNT_RANGE_HIGH |
			       VLV_MEDIA_RC6_COUNT_EN |
			       VLV_RENDER_RC6_COUNT_EN));

	/* 3: Enable RC6 */
	rc6->ctl_enable = GEN7_RC_CTL_TO_MODE;
पूर्ण

अटल व्योम vlv_rc6_enable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	set(uncore, GEN6_RC6_WAKE_RATE_LIMIT, 0x00280000);
	set(uncore, GEN6_RC_EVALUATION_INTERVAL, 125000);
	set(uncore, GEN6_RC_IDLE_HYSTERSIS, 25);

	क्रम_each_engine(engine, rc6_to_gt(rc6), id)
		set(uncore, RING_MAX_IDLE(engine->mmio_base), 10);

	set(uncore, GEN6_RC6_THRESHOLD, 0x557);

	/* Allows RC6 residency counter to work */
	set(uncore, VLV_COUNTER_CONTROL,
	    _MASKED_BIT_ENABLE(VLV_COUNT_RANGE_HIGH |
			       VLV_MEDIA_RC0_COUNT_EN |
			       VLV_RENDER_RC0_COUNT_EN |
			       VLV_MEDIA_RC6_COUNT_EN |
			       VLV_RENDER_RC6_COUNT_EN));

	rc6->ctl_enable =
	    GEN7_RC_CTL_TO_MODE | VLV_RC_CTL_CTX_RST_PARALLEL;
पूर्ण

अटल bool bxt_check_bios_rc6_setup(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);
	u32 rc6_ctx_base, rc_ctl, rc_sw_target;
	bool enable_rc6 = true;

	rc_ctl = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RC_CONTROL);
	rc_sw_target = पूर्णांकel_uncore_पढ़ो(uncore, GEN6_RC_STATE);
	rc_sw_target &= RC_SW_TARGET_STATE_MASK;
	rc_sw_target >>= RC_SW_TARGET_STATE_SHIFT;
	drm_dbg(&i915->drm, "BIOS enabled RC states: "
			 "HW_CTRL %s HW_RC6 %s SW_TARGET_STATE %x\n",
			 onoff(rc_ctl & GEN6_RC_CTL_HW_ENABLE),
			 onoff(rc_ctl & GEN6_RC_CTL_RC6_ENABLE),
			 rc_sw_target);

	अगर (!(पूर्णांकel_uncore_पढ़ो(uncore, RC6_LOCATION) & RC6_CTX_IN_DRAM)) अणु
		drm_dbg(&i915->drm, "RC6 Base location not set properly.\n");
		enable_rc6 = false;
	पूर्ण

	/*
	 * The exact context size is not known क्रम BXT, so assume a page size
	 * क्रम this check.
	 */
	rc6_ctx_base =
		पूर्णांकel_uncore_पढ़ो(uncore, RC6_CTX_BASE) & RC6_CTX_BASE_MASK;
	अगर (!(rc6_ctx_base >= i915->dsm_reserved.start &&
	      rc6_ctx_base + PAGE_SIZE < i915->dsm_reserved.end)) अणु
		drm_dbg(&i915->drm, "RC6 Base address not as expected.\n");
		enable_rc6 = false;
	पूर्ण

	अगर (!((पूर्णांकel_uncore_पढ़ो(uncore, PWRCTX_MAXCNT_RCSUNIT) & IDLE_TIME_MASK) > 1 &&
	      (पूर्णांकel_uncore_पढ़ो(uncore, PWRCTX_MAXCNT_VCSUNIT0) & IDLE_TIME_MASK) > 1 &&
	      (पूर्णांकel_uncore_पढ़ो(uncore, PWRCTX_MAXCNT_BCSUNIT) & IDLE_TIME_MASK) > 1 &&
	      (पूर्णांकel_uncore_पढ़ो(uncore, PWRCTX_MAXCNT_VECSUNIT) & IDLE_TIME_MASK) > 1)) अणु
		drm_dbg(&i915->drm,
			"Engine Idle wait time not set properly.\n");
		enable_rc6 = false;
	पूर्ण

	अगर (!पूर्णांकel_uncore_पढ़ो(uncore, GEN8_PUSHBUS_CONTROL) ||
	    !पूर्णांकel_uncore_पढ़ो(uncore, GEN8_PUSHBUS_ENABLE) ||
	    !पूर्णांकel_uncore_पढ़ो(uncore, GEN8_PUSHBUS_SHIFT)) अणु
		drm_dbg(&i915->drm, "Pushbus not setup properly.\n");
		enable_rc6 = false;
	पूर्ण

	अगर (!पूर्णांकel_uncore_पढ़ो(uncore, GEN6_GFXPAUSE)) अणु
		drm_dbg(&i915->drm, "GFX pause not setup properly.\n");
		enable_rc6 = false;
	पूर्ण

	अगर (!पूर्णांकel_uncore_पढ़ो(uncore, GEN8_MISC_CTRL0)) अणु
		drm_dbg(&i915->drm, "GPM control not setup properly.\n");
		enable_rc6 = false;
	पूर्ण

	वापस enable_rc6;
पूर्ण

अटल bool rc6_supported(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);

	अगर (!HAS_RC6(i915))
		वापस false;

	अगर (पूर्णांकel_vgpu_active(i915))
		वापस false;

	अगर (is_mock_gt(rc6_to_gt(rc6)))
		वापस false;

	अगर (IS_GEN9_LP(i915) && !bxt_check_bios_rc6_setup(rc6)) अणु
		drm_notice(&i915->drm,
			   "RC6 and powersaving disabled by BIOS\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम rpm_get(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	GEM_BUG_ON(rc6->wakeref);
	pm_runसमय_get_sync(rc6_to_i915(rc6)->drm.dev);
	rc6->wakeref = true;
पूर्ण

अटल व्योम rpm_put(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	GEM_BUG_ON(!rc6->wakeref);
	pm_runसमय_put(rc6_to_i915(rc6)->drm.dev);
	rc6->wakeref = false;
पूर्ण

अटल bool pctx_corrupted(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);

	अगर (!NEEDS_RC6_CTX_CORRUPTION_WA(i915))
		वापस false;

	अगर (पूर्णांकel_uncore_पढ़ो(rc6_to_uncore(rc6), GEN8_RC6_CTX_INFO))
		वापस false;

	drm_notice(&i915->drm,
		   "RC6 context corruption, disabling runtime power management\n");
	वापस true;
पूर्ण

अटल व्योम __पूर्णांकel_rc6_disable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);

	पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);
	अगर (INTEL_GEN(i915) >= 9)
		set(uncore, GEN9_PG_ENABLE, 0);
	set(uncore, GEN6_RC_CONTROL, 0);
	set(uncore, GEN6_RC_STATE, 0);
	पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);
पूर्ण

व्योम पूर्णांकel_rc6_init(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);
	पूर्णांक err;

	/* Disable runसमय-pm until we can save the GPU state with rc6 pctx */
	rpm_get(rc6);

	अगर (!rc6_supported(rc6))
		वापस;

	अगर (IS_CHERRYVIEW(i915))
		err = chv_rc6_init(rc6);
	अन्यथा अगर (IS_VALLEYVIEW(i915))
		err = vlv_rc6_init(rc6);
	अन्यथा
		err = 0;

	/* Sanitize rc6, ensure it is disabled beक्रमe we are पढ़ोy. */
	__पूर्णांकel_rc6_disable(rc6);

	rc6->supported = err == 0;
पूर्ण

व्योम पूर्णांकel_rc6_sanitize(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	स_रखो(rc6->prev_hw_residency, 0, माप(rc6->prev_hw_residency));

	अगर (rc6->enabled) अणु /* unbalanced suspend/resume */
		rpm_get(rc6);
		rc6->enabled = false;
	पूर्ण

	अगर (rc6->supported)
		__पूर्णांकel_rc6_disable(rc6);
पूर्ण

व्योम पूर्णांकel_rc6_enable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);

	अगर (!rc6->supported)
		वापस;

	GEM_BUG_ON(rc6->enabled);

	पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);

	अगर (IS_CHERRYVIEW(i915))
		chv_rc6_enable(rc6);
	अन्यथा अगर (IS_VALLEYVIEW(i915))
		vlv_rc6_enable(rc6);
	अन्यथा अगर (INTEL_GEN(i915) >= 11)
		gen11_rc6_enable(rc6);
	अन्यथा अगर (INTEL_GEN(i915) >= 9)
		gen9_rc6_enable(rc6);
	अन्यथा अगर (IS_BROADWELL(i915))
		gen8_rc6_enable(rc6);
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		gen6_rc6_enable(rc6);

	rc6->manual = rc6->ctl_enable & GEN6_RC_CTL_RC6_ENABLE;
	अगर (NEEDS_RC6_CTX_CORRUPTION_WA(i915))
		rc6->ctl_enable = 0;

	पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);

	अगर (unlikely(pctx_corrupted(rc6)))
		वापस;

	/* rc6 is पढ़ोy, runसमय-pm is go! */
	rpm_put(rc6);
	rc6->enabled = true;
पूर्ण

व्योम पूर्णांकel_rc6_unpark(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);

	अगर (!rc6->enabled)
		वापस;

	/* Restore HW समयrs क्रम स्वतःmatic RC6 entry जबतक busy */
	set(uncore, GEN6_RC_CONTROL, rc6->ctl_enable);
पूर्ण

व्योम पूर्णांकel_rc6_park(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	अचिन्हित पूर्णांक target;

	अगर (!rc6->enabled)
		वापस;

	अगर (unlikely(pctx_corrupted(rc6))) अणु
		पूर्णांकel_rc6_disable(rc6);
		वापस;
	पूर्ण

	अगर (!rc6->manual)
		वापस;

	/* Turn off the HW समयrs and go directly to rc6 */
	set(uncore, GEN6_RC_CONTROL, GEN6_RC_CTL_RC6_ENABLE);

	अगर (HAS_RC6pp(rc6_to_i915(rc6)))
		target = 0x6; /* deepest rc6 */
	अन्यथा अगर (HAS_RC6p(rc6_to_i915(rc6)))
		target = 0x5; /* deep rc6 */
	अन्यथा
		target = 0x4; /* normal rc6 */
	set(uncore, GEN6_RC_STATE, target << RC_SW_TARGET_STATE_SHIFT);
पूर्ण

व्योम पूर्णांकel_rc6_disable(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	अगर (!rc6->enabled)
		वापस;

	rpm_get(rc6);
	rc6->enabled = false;

	__पूर्णांकel_rc6_disable(rc6);
पूर्ण

व्योम पूर्णांकel_rc6_fini(काष्ठा पूर्णांकel_rc6 *rc6)
अणु
	काष्ठा drm_i915_gem_object *pctx;

	पूर्णांकel_rc6_disable(rc6);

	pctx = fetch_and_zero(&rc6->pctx);
	अगर (pctx)
		i915_gem_object_put(pctx);

	अगर (rc6->wakeref)
		rpm_put(rc6);
पूर्ण

अटल u64 vlv_residency_raw(काष्ठा पूर्णांकel_uncore *uncore, स्थिर i915_reg_t reg)
अणु
	u32 lower, upper, पंचांगp;
	पूर्णांक loop = 2;

	/*
	 * The रेजिस्टर accessed करो not need क्रमcewake. We borrow
	 * uncore lock to prevent concurrent access to range reg.
	 */
	lockdep_निश्चित_held(&uncore->lock);

	/*
	 * vlv and chv residency counters are 40 bits in width.
	 * With a control bit, we can choose between upper or lower
	 * 32bit winकरोw पूर्णांकo this counter.
	 *
	 * Although we always use the counter in high-range mode अन्यथाwhere,
	 * userspace may attempt to पढ़ो the value beक्रमe rc6 is initialised,
	 * beक्रमe we have set the शेष VLV_COUNTER_CONTROL value. So always
	 * set the high bit to be safe.
	 */
	set(uncore, VLV_COUNTER_CONTROL,
	    _MASKED_BIT_ENABLE(VLV_COUNT_RANGE_HIGH));
	upper = पूर्णांकel_uncore_पढ़ो_fw(uncore, reg);
	करो अणु
		पंचांगp = upper;

		set(uncore, VLV_COUNTER_CONTROL,
		    _MASKED_BIT_DISABLE(VLV_COUNT_RANGE_HIGH));
		lower = पूर्णांकel_uncore_पढ़ो_fw(uncore, reg);

		set(uncore, VLV_COUNTER_CONTROL,
		    _MASKED_BIT_ENABLE(VLV_COUNT_RANGE_HIGH));
		upper = पूर्णांकel_uncore_पढ़ो_fw(uncore, reg);
	पूर्ण जबतक (upper != पंचांगp && --loop);

	/*
	 * Everywhere अन्यथा we always use VLV_COUNTER_CONTROL with the
	 * VLV_COUNT_RANGE_HIGH bit set - so it is safe to leave it set
	 * now.
	 */

	वापस lower | (u64)upper << 8;
पूर्ण

u64 पूर्णांकel_rc6_residency_ns(काष्ठा पूर्णांकel_rc6 *rc6, स्थिर i915_reg_t reg)
अणु
	काष्ठा drm_i915_निजी *i915 = rc6_to_i915(rc6);
	काष्ठा पूर्णांकel_uncore *uncore = rc6_to_uncore(rc6);
	u64 समय_hw, prev_hw, overflow_hw;
	अचिन्हित पूर्णांक fw_करोमुख्यs;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	u32 mul, भाग;

	अगर (!rc6->supported)
		वापस 0;

	/*
	 * Store previous hw counter values क्रम counter wrap-around handling.
	 *
	 * There are only four पूर्णांकeresting रेजिस्टरs and they live next to each
	 * other so we can use the relative address, compared to the smallest
	 * one as the index पूर्णांकo driver storage.
	 */
	i = (i915_mmio_reg_offset(reg) -
	     i915_mmio_reg_offset(GEN6_GT_GFX_RC6_LOCKED)) / माप(u32);
	अगर (drm_WARN_ON_ONCE(&i915->drm, i >= ARRAY_SIZE(rc6->cur_residency)))
		वापस 0;

	fw_करोमुख्यs = पूर्णांकel_uncore_क्रमcewake_क्रम_reg(uncore, reg, FW_REG_READ);

	spin_lock_irqsave(&uncore->lock, flags);
	पूर्णांकel_uncore_क्रमcewake_get__locked(uncore, fw_करोमुख्यs);

	/* On VLV and CHV, residency समय is in CZ units rather than 1.28us */
	अगर (IS_VALLEYVIEW(i915) || IS_CHERRYVIEW(i915)) अणु
		mul = 1000000;
		भाग = i915->czclk_freq;
		overflow_hw = BIT_ULL(40);
		समय_hw = vlv_residency_raw(uncore, reg);
	पूर्ण अन्यथा अणु
		/* 833.33ns units on Gen9LP, 1.28us अन्यथाwhere. */
		अगर (IS_GEN9_LP(i915)) अणु
			mul = 10000;
			भाग = 12;
		पूर्ण अन्यथा अणु
			mul = 1280;
			भाग = 1;
		पूर्ण

		overflow_hw = BIT_ULL(32);
		समय_hw = पूर्णांकel_uncore_पढ़ो_fw(uncore, reg);
	पूर्ण

	/*
	 * Counter wrap handling.
	 *
	 * But relying on a sufficient frequency of queries otherwise counters
	 * can still wrap.
	 */
	prev_hw = rc6->prev_hw_residency[i];
	rc6->prev_hw_residency[i] = समय_hw;

	/* RC6 delta from last sample. */
	अगर (समय_hw >= prev_hw)
		समय_hw -= prev_hw;
	अन्यथा
		समय_hw += overflow_hw - prev_hw;

	/* Add delta to RC6 extended raw driver copy. */
	समय_hw += rc6->cur_residency[i];
	rc6->cur_residency[i] = समय_hw;

	पूर्णांकel_uncore_क्रमcewake_put__locked(uncore, fw_करोमुख्यs);
	spin_unlock_irqrestore(&uncore->lock, flags);

	वापस mul_u64_u32_भाग(समय_hw, mul, भाग);
पूर्ण

u64 पूर्णांकel_rc6_residency_us(काष्ठा पूर्णांकel_rc6 *rc6, i915_reg_t reg)
अणु
	वापस DIV_ROUND_UP_ULL(पूर्णांकel_rc6_residency_ns(rc6, reg), 1000);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_rc6.c"
#पूर्ण_अगर
