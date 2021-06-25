<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2008-2018 Intel Corporation
 */

#समावेश <linux/sched/mm.h>
#समावेश <linux/stop_machine.h>

#समावेश "display/intel_display_types.h"
#समावेश "display/intel_overlay.h"

#समावेश "gem/i915_gem_context.h"

#समावेश "i915_drv.h"
#समावेश "i915_gpu_error.h"
#समावेश "i915_irq.h"
#समावेश "intel_breadcrumbs.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_gt_requests.h"
#समावेश "intel_reset.h"

#समावेश "uc/intel_guc.h"
#समावेश "uc/intel_guc_submission.h"

#घोषणा RESET_MAX_RETRIES 3

/* XXX How to handle concurrent GGTT updates using tiling रेजिस्टरs? */
#घोषणा RESET_UNDER_STOP_MACHINE 0

अटल व्योम rmw_set_fw(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u32 set)
अणु
	पूर्णांकel_uncore_rmw_fw(uncore, reg, 0, set);
पूर्ण

अटल व्योम rmw_clear_fw(काष्ठा पूर्णांकel_uncore *uncore, i915_reg_t reg, u32 clr)
अणु
	पूर्णांकel_uncore_rmw_fw(uncore, reg, clr, 0);
पूर्ण

अटल व्योम skip_context(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_context *hung_ctx = rq->context;

	list_क्रम_each_entry_from_rcu(rq, &hung_ctx->समयline->requests, link) अणु
		अगर (!i915_request_is_active(rq))
			वापस;

		अगर (rq->context == hung_ctx) अणु
			i915_request_set_error_once(rq, -EIO);
			__i915_request_skip(rq);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम client_mark_guilty(काष्ठा i915_gem_context *ctx, bool banned)
अणु
	काष्ठा drm_i915_file_निजी *file_priv = ctx->file_priv;
	अचिन्हित दीर्घ prev_hang;
	अचिन्हित पूर्णांक score;

	अगर (IS_ERR_OR_शून्य(file_priv))
		वापस;

	score = 0;
	अगर (banned)
		score = I915_CLIENT_SCORE_CONTEXT_BAN;

	prev_hang = xchg(&file_priv->hang_बारtamp, jअगरfies);
	अगर (समय_beक्रमe(jअगरfies, prev_hang + I915_CLIENT_FAST_HANG_JIFFIES))
		score += I915_CLIENT_SCORE_HANG_FAST;

	अगर (score) अणु
		atomic_add(score, &file_priv->ban_score);

		drm_dbg(&ctx->i915->drm,
			"client %s: gained %u ban score, now %u\n",
			ctx->name, score,
			atomic_पढ़ो(&file_priv->ban_score));
	पूर्ण
पूर्ण

अटल bool mark_guilty(काष्ठा i915_request *rq)
अणु
	काष्ठा i915_gem_context *ctx;
	अचिन्हित दीर्घ prev_hang;
	bool banned;
	पूर्णांक i;

	अगर (पूर्णांकel_context_is_बंदd(rq->context)) अणु
		पूर्णांकel_context_set_banned(rq->context);
		वापस true;
	पूर्ण

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(rq->context->gem_context);
	अगर (ctx && !kref_get_unless_zero(&ctx->ref))
		ctx = शून्य;
	rcu_पढ़ो_unlock();
	अगर (!ctx)
		वापस पूर्णांकel_context_is_banned(rq->context);

	atomic_inc(&ctx->guilty_count);

	/* Cool contexts are too cool to be banned! (Used क्रम reset testing.) */
	अगर (!i915_gem_context_is_bannable(ctx)) अणु
		banned = false;
		जाओ out;
	पूर्ण

	drm_notice(&ctx->i915->drm,
		   "%s context reset due to GPU hang\n",
		   ctx->name);

	/* Record the बारtamp क्रम the last N hangs */
	prev_hang = ctx->hang_बारtamp[0];
	क्रम (i = 0; i < ARRAY_SIZE(ctx->hang_बारtamp) - 1; i++)
		ctx->hang_बारtamp[i] = ctx->hang_बारtamp[i + 1];
	ctx->hang_बारtamp[i] = jअगरfies;

	/* If we have hung N+1 बार in rapid succession, we ban the context! */
	banned = !i915_gem_context_is_recoverable(ctx);
	अगर (समय_beक्रमe(jअगरfies, prev_hang + CONTEXT_FAST_HANG_JIFFIES))
		banned = true;
	अगर (banned) अणु
		drm_dbg(&ctx->i915->drm, "context %s: guilty %d, banned\n",
			ctx->name, atomic_पढ़ो(&ctx->guilty_count));
		पूर्णांकel_context_set_banned(rq->context);
	पूर्ण

	client_mark_guilty(ctx, banned);

out:
	i915_gem_context_put(ctx);
	वापस banned;
पूर्ण

अटल व्योम mark_innocent(काष्ठा i915_request *rq)
अणु
	काष्ठा i915_gem_context *ctx;

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(rq->context->gem_context);
	अगर (ctx)
		atomic_inc(&ctx->active_count);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम __i915_request_reset(काष्ठा i915_request *rq, bool guilty)
अणु
	RQ_TRACE(rq, "guilty? %s\n", yesno(guilty));
	GEM_BUG_ON(__i915_request_is_complete(rq));

	rcu_पढ़ो_lock(); /* protect the GEM context */
	अगर (guilty) अणु
		i915_request_set_error_once(rq, -EIO);
		__i915_request_skip(rq);
		अगर (mark_guilty(rq))
			skip_context(rq);
	पूर्ण अन्यथा अणु
		i915_request_set_error_once(rq, -EAGAIN);
		mark_innocent(rq);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल bool i915_in_reset(काष्ठा pci_dev *pdev)
अणु
	u8 gdrst;

	pci_पढ़ो_config_byte(pdev, I915_GDRST, &gdrst);
	वापस gdrst & GRDOM_RESET_STATUS;
पूर्ण

अटल पूर्णांक i915_करो_reset(काष्ठा पूर्णांकel_gt *gt,
			 पूर्णांकel_engine_mask_t engine_mask,
			 अचिन्हित पूर्णांक retry)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(gt->i915->drm.dev);
	पूर्णांक err;

	/* Assert reset क्रम at least 20 usec, and रुको क्रम acknowledgement. */
	pci_ग_लिखो_config_byte(pdev, I915_GDRST, GRDOM_RESET_ENABLE);
	udelay(50);
	err = रुको_क्रम_atomic(i915_in_reset(pdev), 50);

	/* Clear the reset request. */
	pci_ग_लिखो_config_byte(pdev, I915_GDRST, 0);
	udelay(50);
	अगर (!err)
		err = रुको_क्रम_atomic(!i915_in_reset(pdev), 50);

	वापस err;
पूर्ण

अटल bool g4x_reset_complete(काष्ठा pci_dev *pdev)
अणु
	u8 gdrst;

	pci_पढ़ो_config_byte(pdev, I915_GDRST, &gdrst);
	वापस (gdrst & GRDOM_RESET_ENABLE) == 0;
पूर्ण

अटल पूर्णांक g33_करो_reset(काष्ठा पूर्णांकel_gt *gt,
			पूर्णांकel_engine_mask_t engine_mask,
			अचिन्हित पूर्णांक retry)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(gt->i915->drm.dev);

	pci_ग_लिखो_config_byte(pdev, I915_GDRST, GRDOM_RESET_ENABLE);
	वापस रुको_क्रम_atomic(g4x_reset_complete(pdev), 50);
पूर्ण

अटल पूर्णांक g4x_करो_reset(काष्ठा पूर्णांकel_gt *gt,
			पूर्णांकel_engine_mask_t engine_mask,
			अचिन्हित पूर्णांक retry)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(gt->i915->drm.dev);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	पूर्णांक ret;

	/* WaVcpClkGateDisableForMediaReset:ctg,elk */
	rmw_set_fw(uncore, VDECCLK_GATE_D, VCP_UNIT_CLOCK_GATE_DISABLE);
	पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, VDECCLK_GATE_D);

	pci_ग_लिखो_config_byte(pdev, I915_GDRST,
			      GRDOM_MEDIA | GRDOM_RESET_ENABLE);
	ret =  रुको_क्रम_atomic(g4x_reset_complete(pdev), 50);
	अगर (ret) अणु
		GT_TRACE(gt, "Wait for media reset failed\n");
		जाओ out;
	पूर्ण

	pci_ग_लिखो_config_byte(pdev, I915_GDRST,
			      GRDOM_RENDER | GRDOM_RESET_ENABLE);
	ret =  रुको_क्रम_atomic(g4x_reset_complete(pdev), 50);
	अगर (ret) अणु
		GT_TRACE(gt, "Wait for render reset failed\n");
		जाओ out;
	पूर्ण

out:
	pci_ग_लिखो_config_byte(pdev, I915_GDRST, 0);

	rmw_clear_fw(uncore, VDECCLK_GATE_D, VCP_UNIT_CLOCK_GATE_DISABLE);
	पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, VDECCLK_GATE_D);

	वापस ret;
पूर्ण

अटल पूर्णांक ilk_करो_reset(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t engine_mask,
			अचिन्हित पूर्णांक retry)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	पूर्णांक ret;

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, ILK_GDSR,
			      ILK_GRDOM_RENDER | ILK_GRDOM_RESET_ENABLE);
	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore, ILK_GDSR,
					   ILK_GRDOM_RESET_ENABLE, 0,
					   5000, 0,
					   शून्य);
	अगर (ret) अणु
		GT_TRACE(gt, "Wait for render reset failed\n");
		जाओ out;
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, ILK_GDSR,
			      ILK_GRDOM_MEDIA | ILK_GRDOM_RESET_ENABLE);
	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore, ILK_GDSR,
					   ILK_GRDOM_RESET_ENABLE, 0,
					   5000, 0,
					   शून्य);
	अगर (ret) अणु
		GT_TRACE(gt, "Wait for media reset failed\n");
		जाओ out;
	पूर्ण

out:
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, ILK_GDSR, 0);
	पूर्णांकel_uncore_posting_पढ़ो_fw(uncore, ILK_GDSR);
	वापस ret;
पूर्ण

/* Reset the hardware करोमुख्यs (GENX_GRDOM_*) specअगरied by mask */
अटल पूर्णांक gen6_hw_करोमुख्य_reset(काष्ठा पूर्णांकel_gt *gt, u32 hw_करोमुख्य_mask)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	पूर्णांक err;

	/*
	 * GEN6_GDRST is not in the gt घातer well, no need to check
	 * क्रम fअगरo space क्रम the ग_लिखो or क्रमcewake the chip क्रम
	 * the पढ़ो
	 */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN6_GDRST, hw_करोमुख्य_mask);

	/* Wait क्रम the device to ack the reset requests */
	err = __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
					   GEN6_GDRST, hw_करोमुख्य_mask, 0,
					   500, 0,
					   शून्य);
	अगर (err)
		GT_TRACE(gt,
			 "Wait for 0x%08x engines reset failed\n",
			 hw_करोमुख्य_mask);

	वापस err;
पूर्ण

अटल पूर्णांक gen6_reset_engines(काष्ठा पूर्णांकel_gt *gt,
			      पूर्णांकel_engine_mask_t engine_mask,
			      अचिन्हित पूर्णांक retry)
अणु
	अटल स्थिर u32 hw_engine_mask[] = अणु
		[RCS0]  = GEN6_GRDOM_RENDER,
		[BCS0]  = GEN6_GRDOM_BLT,
		[VCS0]  = GEN6_GRDOM_MEDIA,
		[VCS1]  = GEN8_GRDOM_MEDIA2,
		[VECS0] = GEN6_GRDOM_VECS,
	पूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine;
	u32 hw_mask;

	अगर (engine_mask == ALL_ENGINES) अणु
		hw_mask = GEN6_GRDOM_FULL;
	पूर्ण अन्यथा अणु
		पूर्णांकel_engine_mask_t पंचांगp;

		hw_mask = 0;
		क्रम_each_engine_masked(engine, gt, engine_mask, पंचांगp) अणु
			GEM_BUG_ON(engine->id >= ARRAY_SIZE(hw_engine_mask));
			hw_mask |= hw_engine_mask[engine->id];
		पूर्ण
	पूर्ण

	वापस gen6_hw_करोमुख्य_reset(gt, hw_mask);
पूर्ण

अटल पूर्णांक gen11_lock_sfc(काष्ठा पूर्णांकel_engine_cs *engine, u32 *hw_mask)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	u8 vdbox_sfc_access = engine->gt->info.vdbox_sfc_access;
	i915_reg_t sfc_क्रमced_lock, sfc_क्रमced_lock_ack;
	u32 sfc_क्रमced_lock_bit, sfc_क्रमced_lock_ack_bit;
	i915_reg_t sfc_usage;
	u32 sfc_usage_bit;
	u32 sfc_reset_bit;
	पूर्णांक ret;

	चयन (engine->class) अणु
	हाल VIDEO_DECODE_CLASS:
		अगर ((BIT(engine->instance) & vdbox_sfc_access) == 0)
			वापस 0;

		sfc_क्रमced_lock = GEN11_VCS_SFC_FORCED_LOCK(engine);
		sfc_क्रमced_lock_bit = GEN11_VCS_SFC_FORCED_LOCK_BIT;

		sfc_क्रमced_lock_ack = GEN11_VCS_SFC_LOCK_STATUS(engine);
		sfc_क्रमced_lock_ack_bit  = GEN11_VCS_SFC_LOCK_ACK_BIT;

		sfc_usage = GEN11_VCS_SFC_LOCK_STATUS(engine);
		sfc_usage_bit = GEN11_VCS_SFC_USAGE_BIT;
		sfc_reset_bit = GEN11_VCS_SFC_RESET_BIT(engine->instance);
		अवरोध;

	हाल VIDEO_ENHANCEMENT_CLASS:
		sfc_क्रमced_lock = GEN11_VECS_SFC_FORCED_LOCK(engine);
		sfc_क्रमced_lock_bit = GEN11_VECS_SFC_FORCED_LOCK_BIT;

		sfc_क्रमced_lock_ack = GEN11_VECS_SFC_LOCK_ACK(engine);
		sfc_क्रमced_lock_ack_bit  = GEN11_VECS_SFC_LOCK_ACK_BIT;

		sfc_usage = GEN11_VECS_SFC_USAGE(engine);
		sfc_usage_bit = GEN11_VECS_SFC_USAGE_BIT;
		sfc_reset_bit = GEN11_VECS_SFC_RESET_BIT(engine->instance);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	/*
	 * If the engine is using a SFC, tell the engine that a software reset
	 * is going to happen. The engine will then try to क्रमce lock the SFC.
	 * If SFC ends up being locked to the engine we want to reset, we have
	 * to reset it as well (we will unlock it once the reset sequence is
	 * completed).
	 */
	अगर (!(पूर्णांकel_uncore_पढ़ो_fw(uncore, sfc_usage) & sfc_usage_bit))
		वापस 0;

	rmw_set_fw(uncore, sfc_क्रमced_lock, sfc_क्रमced_lock_bit);

	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
					   sfc_क्रमced_lock_ack,
					   sfc_क्रमced_lock_ack_bit,
					   sfc_क्रमced_lock_ack_bit,
					   1000, 0, शून्य);

	/* Was the SFC released जबतक we were trying to lock it? */
	अगर (!(पूर्णांकel_uncore_पढ़ो_fw(uncore, sfc_usage) & sfc_usage_bit))
		वापस 0;

	अगर (ret) अणु
		ENGINE_TRACE(engine, "Wait for SFC forced lock ack failed\n");
		वापस ret;
	पूर्ण

	*hw_mask |= sfc_reset_bit;
	वापस 0;
पूर्ण

अटल व्योम gen11_unlock_sfc(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	u8 vdbox_sfc_access = engine->gt->info.vdbox_sfc_access;
	i915_reg_t sfc_क्रमced_lock;
	u32 sfc_क्रमced_lock_bit;

	चयन (engine->class) अणु
	हाल VIDEO_DECODE_CLASS:
		अगर ((BIT(engine->instance) & vdbox_sfc_access) == 0)
			वापस;

		sfc_क्रमced_lock = GEN11_VCS_SFC_FORCED_LOCK(engine);
		sfc_क्रमced_lock_bit = GEN11_VCS_SFC_FORCED_LOCK_BIT;
		अवरोध;

	हाल VIDEO_ENHANCEMENT_CLASS:
		sfc_क्रमced_lock = GEN11_VECS_SFC_FORCED_LOCK(engine);
		sfc_क्रमced_lock_bit = GEN11_VECS_SFC_FORCED_LOCK_BIT;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	rmw_clear_fw(uncore, sfc_क्रमced_lock, sfc_क्रमced_lock_bit);
पूर्ण

अटल पूर्णांक gen11_reset_engines(काष्ठा पूर्णांकel_gt *gt,
			       पूर्णांकel_engine_mask_t engine_mask,
			       अचिन्हित पूर्णांक retry)
अणु
	अटल स्थिर u32 hw_engine_mask[] = अणु
		[RCS0]  = GEN11_GRDOM_RENDER,
		[BCS0]  = GEN11_GRDOM_BLT,
		[VCS0]  = GEN11_GRDOM_MEDIA,
		[VCS1]  = GEN11_GRDOM_MEDIA2,
		[VCS2]  = GEN11_GRDOM_MEDIA3,
		[VCS3]  = GEN11_GRDOM_MEDIA4,
		[VECS0] = GEN11_GRDOM_VECS,
		[VECS1] = GEN11_GRDOM_VECS2,
	पूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांकel_engine_mask_t पंचांगp;
	u32 hw_mask;
	पूर्णांक ret;

	अगर (engine_mask == ALL_ENGINES) अणु
		hw_mask = GEN11_GRDOM_FULL;
	पूर्ण अन्यथा अणु
		hw_mask = 0;
		क्रम_each_engine_masked(engine, gt, engine_mask, पंचांगp) अणु
			GEM_BUG_ON(engine->id >= ARRAY_SIZE(hw_engine_mask));
			hw_mask |= hw_engine_mask[engine->id];
			ret = gen11_lock_sfc(engine, &hw_mask);
			अगर (ret)
				जाओ sfc_unlock;
		पूर्ण
	पूर्ण

	ret = gen6_hw_करोमुख्य_reset(gt, hw_mask);

sfc_unlock:
	/*
	 * We unlock the SFC based on the lock status and not the result of
	 * gen11_lock_sfc to make sure that we clean properly अगर something
	 * wrong happened during the lock (e.g. lock acquired after समयout
	 * expiration).
	 */
	अगर (engine_mask != ALL_ENGINES)
		क्रम_each_engine_masked(engine, gt, engine_mask, पंचांगp)
			gen11_unlock_sfc(engine);

	वापस ret;
पूर्ण

अटल पूर्णांक gen8_engine_reset_prepare(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	स्थिर i915_reg_t reg = RING_RESET_CTL(engine->mmio_base);
	u32 request, mask, ack;
	पूर्णांक ret;

	अगर (I915_SELFTEST_ONLY(should_fail(&engine->reset_समयout, 1)))
		वापस -ETIMEDOUT;

	ack = पूर्णांकel_uncore_पढ़ो_fw(uncore, reg);
	अगर (ack & RESET_CTL_CAT_ERROR) अणु
		/*
		 * For catastrophic errors, पढ़ोy-क्रम-reset sequence
		 * needs to be bypassed: HAS#396813
		 */
		request = RESET_CTL_CAT_ERROR;
		mask = RESET_CTL_CAT_ERROR;

		/* Catastrophic errors need to be cleared by HW */
		ack = 0;
	पूर्ण अन्यथा अगर (!(ack & RESET_CTL_READY_TO_RESET)) अणु
		request = RESET_CTL_REQUEST_RESET;
		mask = RESET_CTL_READY_TO_RESET;
		ack = RESET_CTL_READY_TO_RESET;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, reg, _MASKED_BIT_ENABLE(request));
	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore, reg, mask, ack,
					   700, 0, शून्य);
	अगर (ret)
		drm_err(&engine->i915->drm,
			"%s reset request timed out: {request: %08x, RESET_CTL: %08x}\n",
			engine->name, request,
			पूर्णांकel_uncore_पढ़ो_fw(uncore, reg));

	वापस ret;
पूर्ण

अटल व्योम gen8_engine_reset_cancel(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_uncore_ग_लिखो_fw(engine->uncore,
			      RING_RESET_CTL(engine->mmio_base),
			      _MASKED_BIT_DISABLE(RESET_CTL_REQUEST_RESET));
पूर्ण

अटल पूर्णांक gen8_reset_engines(काष्ठा पूर्णांकel_gt *gt,
			      पूर्णांकel_engine_mask_t engine_mask,
			      अचिन्हित पूर्णांक retry)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	स्थिर bool reset_non_पढ़ोy = retry >= 1;
	पूर्णांकel_engine_mask_t पंचांगp;
	पूर्णांक ret;

	क्रम_each_engine_masked(engine, gt, engine_mask, पंचांगp) अणु
		ret = gen8_engine_reset_prepare(engine);
		अगर (ret && !reset_non_पढ़ोy)
			जाओ skip_reset;

		/*
		 * If this is not the first failed attempt to prepare,
		 * we decide to proceed anyway.
		 *
		 * By करोing so we risk context corruption and with
		 * some gens (kbl), possible प्रणाली hang अगर reset
		 * happens during active bb execution.
		 *
		 * We rather take context corruption instead of
		 * failed reset with a wedged driver/gpu. And
		 * active bb execution हाल should be covered by
		 * stop_engines() we have beक्रमe the reset.
		 */
	पूर्ण

	अगर (INTEL_GEN(gt->i915) >= 11)
		ret = gen11_reset_engines(gt, engine_mask, retry);
	अन्यथा
		ret = gen6_reset_engines(gt, engine_mask, retry);

skip_reset:
	क्रम_each_engine_masked(engine, gt, engine_mask, पंचांगp)
		gen8_engine_reset_cancel(engine);

	वापस ret;
पूर्ण

अटल पूर्णांक mock_reset(काष्ठा पूर्णांकel_gt *gt,
		      पूर्णांकel_engine_mask_t mask,
		      अचिन्हित पूर्णांक retry)
अणु
	वापस 0;
पूर्ण

प्रकार पूर्णांक (*reset_func)(काष्ठा पूर्णांकel_gt *,
			  पूर्णांकel_engine_mask_t engine_mask,
			  अचिन्हित पूर्णांक retry);

अटल reset_func पूर्णांकel_get_gpu_reset(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	अगर (is_mock_gt(gt))
		वापस mock_reset;
	अन्यथा अगर (INTEL_GEN(i915) >= 8)
		वापस gen8_reset_engines;
	अन्यथा अगर (INTEL_GEN(i915) >= 6)
		वापस gen6_reset_engines;
	अन्यथा अगर (INTEL_GEN(i915) >= 5)
		वापस ilk_करो_reset;
	अन्यथा अगर (IS_G4X(i915))
		वापस g4x_करो_reset;
	अन्यथा अगर (IS_G33(i915) || IS_PINEVIEW(i915))
		वापस g33_करो_reset;
	अन्यथा अगर (INTEL_GEN(i915) >= 3)
		वापस i915_करो_reset;
	अन्यथा
		वापस शून्य;
पूर्ण

पूर्णांक __पूर्णांकel_gt_reset(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t engine_mask)
अणु
	स्थिर पूर्णांक retries = engine_mask == ALL_ENGINES ? RESET_MAX_RETRIES : 1;
	reset_func reset;
	पूर्णांक ret = -ETIMEDOUT;
	पूर्णांक retry;

	reset = पूर्णांकel_get_gpu_reset(gt);
	अगर (!reset)
		वापस -ENODEV;

	/*
	 * If the घातer well sleeps during the reset, the reset
	 * request may be dropped and never completes (causing -EIO).
	 */
	पूर्णांकel_uncore_क्रमcewake_get(gt->uncore, FORCEWAKE_ALL);
	क्रम (retry = 0; ret == -ETIMEDOUT && retry < retries; retry++) अणु
		GT_TRACE(gt, "engine_mask=%x\n", engine_mask);
		preempt_disable();
		ret = reset(gt, engine_mask, retry);
		preempt_enable();
	पूर्ण
	पूर्णांकel_uncore_क्रमcewake_put(gt->uncore, FORCEWAKE_ALL);

	वापस ret;
पूर्ण

bool पूर्णांकel_has_gpu_reset(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	अगर (!gt->i915->params.reset)
		वापस शून्य;

	वापस पूर्णांकel_get_gpu_reset(gt);
पूर्ण

bool पूर्णांकel_has_reset_engine(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	अगर (gt->i915->params.reset < 2)
		वापस false;

	वापस INTEL_INFO(gt->i915)->has_reset_engine;
पूर्ण

पूर्णांक पूर्णांकel_reset_guc(काष्ठा पूर्णांकel_gt *gt)
अणु
	u32 guc_करोमुख्य =
		INTEL_GEN(gt->i915) >= 11 ? GEN11_GRDOM_GUC : GEN9_GRDOM_GUC;
	पूर्णांक ret;

	GEM_BUG_ON(!HAS_GT_UC(gt->i915));

	पूर्णांकel_uncore_क्रमcewake_get(gt->uncore, FORCEWAKE_ALL);
	ret = gen6_hw_करोमुख्य_reset(gt, guc_करोमुख्य);
	पूर्णांकel_uncore_क्रमcewake_put(gt->uncore, FORCEWAKE_ALL);

	वापस ret;
पूर्ण

/*
 * Ensure irq handler finishes, and not run again.
 * Also वापस the active request so that we only search क्रम it once.
 */
अटल व्योम reset_prepare_engine(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/*
	 * During the reset sequence, we must prevent the engine from
	 * entering RC6. As the context state is undefined until we restart
	 * the engine, अगर it करोes enter RC6 during the reset, the state
	 * written to the घातercontext is undefined and so we may lose
	 * GPU state upon resume, i.e. fail to restart after a reset.
	 */
	पूर्णांकel_uncore_क्रमcewake_get(engine->uncore, FORCEWAKE_ALL);
	अगर (engine->reset.prepare)
		engine->reset.prepare(engine);
पूर्ण

अटल व्योम revoke_mmaps(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gt->ggtt->num_fences; i++) अणु
		काष्ठा drm_vma_offset_node *node;
		काष्ठा i915_vma *vma;
		u64 vma_offset;

		vma = READ_ONCE(gt->ggtt->fence_regs[i].vma);
		अगर (!vma)
			जारी;

		अगर (!i915_vma_has_userfault(vma))
			जारी;

		GEM_BUG_ON(vma->fence != &gt->ggtt->fence_regs[i]);

		अगर (!vma->mmo)
			जारी;

		node = &vma->mmo->vma_node;
		vma_offset = vma->ggtt_view.partial.offset << PAGE_SHIFT;

		unmap_mapping_range(gt->i915->drm.anon_inode->i_mapping,
				    drm_vma_node_offset_addr(node) + vma_offset,
				    vma->size,
				    1);
	पूर्ण
पूर्ण

अटल पूर्णांकel_engine_mask_t reset_prepare(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांकel_engine_mask_t awake = 0;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt, id) अणु
		अगर (पूर्णांकel_engine_pm_get_अगर_awake(engine))
			awake |= engine->mask;
		reset_prepare_engine(engine);
	पूर्ण

	पूर्णांकel_uc_reset_prepare(&gt->uc);

	वापस awake;
पूर्ण

अटल व्योम gt_revoke(काष्ठा पूर्णांकel_gt *gt)
अणु
	revoke_mmaps(gt);
पूर्ण

अटल पूर्णांक gt_reset(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t stalled_mask)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err;

	/*
	 * Everything depends on having the GTT running, so we need to start
	 * there.
	 */
	err = i915_ggtt_enable_hw(gt->i915);
	अगर (err)
		वापस err;

	local_bh_disable();
	क्रम_each_engine(engine, gt, id)
		__पूर्णांकel_engine_reset(engine, stalled_mask & engine->mask);
	local_bh_enable();

	पूर्णांकel_ggtt_restore_fences(gt->ggtt);

	वापस err;
पूर्ण

अटल व्योम reset_finish_engine(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (engine->reset.finish)
		engine->reset.finish(engine);
	पूर्णांकel_uncore_क्रमcewake_put(engine->uncore, FORCEWAKE_ALL);

	पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(engine);
पूर्ण

अटल व्योम reset_finish(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t awake)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt, id) अणु
		reset_finish_engine(engine);
		अगर (awake & engine->mask)
			पूर्णांकel_engine_pm_put(engine);
	पूर्ण
पूर्ण

अटल व्योम nop_submit_request(काष्ठा i915_request *request)
अणु
	RQ_TRACE(request, "-EIO\n");

	request = i915_request_mark_eio(request);
	अगर (request) अणु
		i915_request_submit(request);
		पूर्णांकel_engine_संकेत_bपढ़ोcrumbs(request->engine);

		i915_request_put(request);
	पूर्ण
पूर्ण

अटल व्योम __पूर्णांकel_gt_set_wedged(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांकel_engine_mask_t awake;
	क्रमागत पूर्णांकel_engine_id id;

	अगर (test_bit(I915_WEDGED, &gt->reset.flags))
		वापस;

	GT_TRACE(gt, "start\n");

	/*
	 * First, stop submission to hw, but करो not yet complete requests by
	 * rolling the global seqno क्रमward (since this would complete requests
	 * क्रम which we haven't set the fence error to EIO yet).
	 */
	awake = reset_prepare(gt);

	/* Even अगर the GPU reset fails, it should still stop the engines */
	अगर (!INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		__पूर्णांकel_gt_reset(gt, ALL_ENGINES);

	क्रम_each_engine(engine, gt, id)
		engine->submit_request = nop_submit_request;

	/*
	 * Make sure no request can slip through without getting completed by
	 * either this call here to पूर्णांकel_engine_ग_लिखो_global_seqno, or the one
	 * in nop_submit_request.
	 */
	synchronize_rcu_expedited();
	set_bit(I915_WEDGED, &gt->reset.flags);

	/* Mark all executing requests as skipped */
	local_bh_disable();
	क्रम_each_engine(engine, gt, id)
		अगर (engine->reset.cancel)
			engine->reset.cancel(engine);
	local_bh_enable();

	reset_finish(gt, awake);

	GT_TRACE(gt, "end\n");
पूर्ण

व्योम पूर्णांकel_gt_set_wedged(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_wakeref_t wakeref;

	अगर (test_bit(I915_WEDGED, &gt->reset.flags))
		वापस;

	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);
	mutex_lock(&gt->reset.mutex);

	अगर (GEM_SHOW_DEBUG()) अणु
		काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer(__func__);
		काष्ठा पूर्णांकel_engine_cs *engine;
		क्रमागत पूर्णांकel_engine_id id;

		drm_म_लिखो(&p, "called from %pS\n", (व्योम *)_RET_IP_);
		क्रम_each_engine(engine, gt, id) अणु
			अगर (पूर्णांकel_engine_is_idle(engine))
				जारी;

			पूर्णांकel_engine_dump(engine, &p, "%s\n", engine->name);
		पूर्ण
	पूर्ण

	__पूर्णांकel_gt_set_wedged(gt);

	mutex_unlock(&gt->reset.mutex);
	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
पूर्ण

अटल bool __पूर्णांकel_gt_unset_wedged(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_gt_समयlines *समयlines = &gt->समयlines;
	काष्ठा पूर्णांकel_समयline *tl;
	bool ok;

	अगर (!test_bit(I915_WEDGED, &gt->reset.flags))
		वापस true;

	/* Never fully initialised, recovery impossible */
	अगर (पूर्णांकel_gt_has_unrecoverable_error(gt))
		वापस false;

	GT_TRACE(gt, "start\n");

	/*
	 * Beक्रमe unwedging, make sure that all pending operations
	 * are flushed and errored out - we may have requests रुकोing upon
	 * third party fences. We marked all inflight requests as EIO, and
	 * every execbuf since वापसed EIO, क्रम consistency we want all
	 * the currently pending requests to also be marked as EIO, which
	 * is करोne inside our nop_submit_request - and so we must रुको.
	 *
	 * No more can be submitted until we reset the wedged bit.
	 */
	spin_lock(&समयlines->lock);
	list_क्रम_each_entry(tl, &समयlines->active_list, link) अणु
		काष्ठा dma_fence *fence;

		fence = i915_active_fence_get(&tl->last_request);
		अगर (!fence)
			जारी;

		spin_unlock(&समयlines->lock);

		/*
		 * All पूर्णांकernal dependencies (i915_requests) will have
		 * been flushed by the set-wedge, but we may be stuck रुकोing
		 * क्रम बाह्यal fences. These should all be capped to 10s
		 * (I915_FENCE_TIMEOUT) so this रुको should not be unbounded
		 * in the worst हाल.
		 */
		dma_fence_शेष_रुको(fence, false, MAX_SCHEDULE_TIMEOUT);
		dma_fence_put(fence);

		/* Restart iteration after droping lock */
		spin_lock(&समयlines->lock);
		tl = list_entry(&समयlines->active_list, typeof(*tl), link);
	पूर्ण
	spin_unlock(&समयlines->lock);

	/* We must reset pending GPU events beक्रमe restoring our submission */
	ok = !HAS_EXECLISTS(gt->i915); /* XXX better agnosticism desired */
	अगर (!INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		ok = __पूर्णांकel_gt_reset(gt, ALL_ENGINES) == 0;
	अगर (!ok) अणु
		/*
		 * Warn CI about the unrecoverable wedged condition.
		 * Time क्रम a reboot.
		 */
		add_taपूर्णांक_क्रम_CI(gt->i915, TAINT_WARN);
		वापस false;
	पूर्ण

	/*
	 * Unकरो nop_submit_request. We prevent all new i915 requests from
	 * being queued (by disallowing execbuf whilst wedged) so having
	 * रुकोed क्रम all active requests above, we know the प्रणाली is idle
	 * and करो not have to worry about a thपढ़ो being inside
	 * engine->submit_request() as we swap over. So unlike installing
	 * the nop_submit_request on reset, we can करो this from normal
	 * context and करो not require stop_machine().
	 */
	पूर्णांकel_engines_reset_शेष_submission(gt);

	GT_TRACE(gt, "end\n");

	smp_mb__beक्रमe_atomic(); /* complete takeover beक्रमe enabling execbuf */
	clear_bit(I915_WEDGED, &gt->reset.flags);

	वापस true;
पूर्ण

bool पूर्णांकel_gt_unset_wedged(काष्ठा पूर्णांकel_gt *gt)
अणु
	bool result;

	mutex_lock(&gt->reset.mutex);
	result = __पूर्णांकel_gt_unset_wedged(gt);
	mutex_unlock(&gt->reset.mutex);

	वापस result;
पूर्ण

अटल पूर्णांक करो_reset(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t stalled_mask)
अणु
	पूर्णांक err, i;

	err = __पूर्णांकel_gt_reset(gt, ALL_ENGINES);
	क्रम (i = 0; err && i < RESET_MAX_RETRIES; i++) अणु
		msleep(10 * (i + 1));
		err = __पूर्णांकel_gt_reset(gt, ALL_ENGINES);
	पूर्ण
	अगर (err)
		वापस err;

	वापस gt_reset(gt, stalled_mask);
पूर्ण

अटल पूर्णांक resume(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक ret;

	क्रम_each_engine(engine, gt, id) अणु
		ret = पूर्णांकel_engine_resume(engine);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gt_reset - reset chip after a hang
 * @gt: #पूर्णांकel_gt to reset
 * @stalled_mask: mask of the stalled engines with the guilty requests
 * @reason: user error message क्रम why we are resetting
 *
 * Reset the chip.  Useful अगर a hang is detected. Marks the device as wedged
 * on failure.
 *
 * Procedure is fairly simple:
 *   - reset the chip using the reset reg
 *   - re-init context state
 *   - re-init hardware status page
 *   - re-init ring buffer
 *   - re-init पूर्णांकerrupt state
 *   - re-init display
 */
व्योम पूर्णांकel_gt_reset(काष्ठा पूर्णांकel_gt *gt,
		    पूर्णांकel_engine_mask_t stalled_mask,
		    स्थिर अक्षर *reason)
अणु
	पूर्णांकel_engine_mask_t awake;
	पूर्णांक ret;

	GT_TRACE(gt, "flags=%lx\n", gt->reset.flags);

	might_sleep();
	GEM_BUG_ON(!test_bit(I915_RESET_BACKOFF, &gt->reset.flags));

	/*
	 * FIXME: Revoking cpu mmap ptes cannot be करोne from a dma_fence
	 * critical section like gpu reset.
	 */
	gt_revoke(gt);

	mutex_lock(&gt->reset.mutex);

	/* Clear any previous failed attempts at recovery. Time to try again. */
	अगर (!__पूर्णांकel_gt_unset_wedged(gt))
		जाओ unlock;

	अगर (reason)
		drm_notice(&gt->i915->drm,
			   "Resetting chip for %s\n", reason);
	atomic_inc(&gt->i915->gpu_error.reset_count);

	awake = reset_prepare(gt);

	अगर (!पूर्णांकel_has_gpu_reset(gt)) अणु
		अगर (gt->i915->params.reset)
			drm_err(&gt->i915->drm, "GPU reset not supported\n");
		अन्यथा
			drm_dbg(&gt->i915->drm, "GPU reset disabled\n");
		जाओ error;
	पूर्ण

	अगर (INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		पूर्णांकel_runसमय_pm_disable_पूर्णांकerrupts(gt->i915);

	अगर (करो_reset(gt, stalled_mask)) अणु
		drm_err(&gt->i915->drm, "Failed to reset chip\n");
		जाओ taपूर्णांक;
	पूर्ण

	अगर (INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		पूर्णांकel_runसमय_pm_enable_पूर्णांकerrupts(gt->i915);

	पूर्णांकel_overlay_reset(gt->i915);

	/*
	 * Next we need to restore the context, but we करोn't use those
	 * yet either...
	 *
	 * Ring buffer needs to be re-initialized in the KMS हाल, or अगर X
	 * was running at the समय of the reset (i.e. we weren't VT
	 * चयनed away).
	 */
	ret = पूर्णांकel_gt_init_hw(gt);
	अगर (ret) अणु
		drm_err(&gt->i915->drm,
			"Failed to initialise HW following reset (%d)\n",
			ret);
		जाओ taपूर्णांक;
	पूर्ण

	ret = resume(gt);
	अगर (ret)
		जाओ taपूर्णांक;

finish:
	reset_finish(gt, awake);
unlock:
	mutex_unlock(&gt->reset.mutex);
	वापस;

taपूर्णांक:
	/*
	 * History tells us that अगर we cannot reset the GPU now, we
	 * never will. This then impacts everything that is run
	 * subsequently. On failing the reset, we mark the driver
	 * as wedged, preventing further execution on the GPU.
	 * We also want to go one step further and add a taपूर्णांक to the
	 * kernel so that any subsequent faults can be traced back to
	 * this failure. This is important क्रम CI, where अगर the
	 * GPU/driver fails we would like to reboot and restart testing
	 * rather than जारी on पूर्णांकo oblivion. For everyone अन्यथा,
	 * the प्रणाली should still plod aदीर्घ, but they have been warned!
	 */
	add_taपूर्णांक_क्रम_CI(gt->i915, TAINT_WARN);
error:
	__पूर्णांकel_gt_set_wedged(gt);
	जाओ finish;
पूर्ण

अटल पूर्णांक पूर्णांकel_gt_reset_engine(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस __पूर्णांकel_gt_reset(engine->gt, engine->mask);
पूर्ण

पूर्णांक __पूर्णांकel_engine_reset_bh(काष्ठा पूर्णांकel_engine_cs *engine, स्थिर अक्षर *msg)
अणु
	काष्ठा पूर्णांकel_gt *gt = engine->gt;
	bool uses_guc = पूर्णांकel_engine_in_guc_submission_mode(engine);
	पूर्णांक ret;

	ENGINE_TRACE(engine, "flags=%lx\n", gt->reset.flags);
	GEM_BUG_ON(!test_bit(I915_RESET_ENGINE + engine->id, &gt->reset.flags));

	अगर (!पूर्णांकel_engine_pm_get_अगर_awake(engine))
		वापस 0;

	reset_prepare_engine(engine);

	अगर (msg)
		drm_notice(&engine->i915->drm,
			   "Resetting %s for %s\n", engine->name, msg);
	atomic_inc(&engine->i915->gpu_error.reset_engine_count[engine->uabi_class]);

	अगर (!uses_guc)
		ret = पूर्णांकel_gt_reset_engine(engine);
	अन्यथा
		ret = पूर्णांकel_guc_reset_engine(&engine->gt->uc.guc, engine);
	अगर (ret) अणु
		/* If we fail here, we expect to fallback to a global reset */
		ENGINE_TRACE(engine, "Failed to reset, err: %d\n", ret);
		जाओ out;
	पूर्ण

	/*
	 * The request that caused the hang is stuck on elsp, we know the
	 * active request and can drop it, adjust head to skip the offending
	 * request to resume executing reमुख्यing requests in the queue.
	 */
	__पूर्णांकel_engine_reset(engine, true);

	/*
	 * The engine and its रेजिस्टरs (and workarounds in हाल of render)
	 * have been reset to their शेष values. Follow the init_ring
	 * process to program RING_MODE, HWSP and re-enable submission.
	 */
	ret = पूर्णांकel_engine_resume(engine);

out:
	पूर्णांकel_engine_cancel_stop_cs(engine);
	reset_finish_engine(engine);
	पूर्णांकel_engine_pm_put_async(engine);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_engine_reset - reset GPU engine to recover from a hang
 * @engine: engine to reset
 * @msg: reason क्रम GPU reset; or शून्य क्रम no drm_notice()
 *
 * Reset a specअगरic GPU engine. Useful अगर a hang is detected.
 * Returns zero on successful reset or otherwise an error code.
 *
 * Procedure is:
 *  - identअगरies the request that caused the hang and it is dropped
 *  - reset engine (which will क्रमce the engine to idle)
 *  - re-init/configure engine
 */
पूर्णांक पूर्णांकel_engine_reset(काष्ठा पूर्णांकel_engine_cs *engine, स्थिर अक्षर *msg)
अणु
	पूर्णांक err;

	local_bh_disable();
	err = __पूर्णांकel_engine_reset_bh(engine, msg);
	local_bh_enable();

	वापस err;
पूर्ण

अटल व्योम पूर्णांकel_gt_reset_global(काष्ठा पूर्णांकel_gt *gt,
				  u32 engine_mask,
				  स्थिर अक्षर *reason)
अणु
	काष्ठा kobject *kobj = &gt->i915->drm.primary->kdev->kobj;
	अक्षर *error_event[] = अणु I915_ERROR_UEVENT "=1", शून्य पूर्ण;
	अक्षर *reset_event[] = अणु I915_RESET_UEVENT "=1", शून्य पूर्ण;
	अक्षर *reset_करोne_event[] = अणु I915_ERROR_UEVENT "=0", शून्य पूर्ण;
	काष्ठा पूर्णांकel_wedge_me w;

	kobject_uevent_env(kobj, KOBJ_CHANGE, error_event);

	GT_TRACE(gt, "resetting chip, engines=%x\n", engine_mask);
	kobject_uevent_env(kobj, KOBJ_CHANGE, reset_event);

	/* Use a watchकरोg to ensure that our reset completes */
	पूर्णांकel_wedge_on_समयout(&w, gt, 5 * HZ) अणु
		पूर्णांकel_display_prepare_reset(gt->i915);

		/* Flush everyone using a resource about to be clobbered */
		synchronize_srcu_expedited(&gt->reset.backoff_srcu);

		पूर्णांकel_gt_reset(gt, engine_mask, reason);

		पूर्णांकel_display_finish_reset(gt->i915);
	पूर्ण

	अगर (!test_bit(I915_WEDGED, &gt->reset.flags))
		kobject_uevent_env(kobj, KOBJ_CHANGE, reset_करोne_event);
पूर्ण

/**
 * पूर्णांकel_gt_handle_error - handle a gpu error
 * @gt: the पूर्णांकel_gt
 * @engine_mask: mask representing engines that are hung
 * @flags: control flags
 * @fmt: Error message क्रमmat string
 *
 * Do some basic checking of रेजिस्टर state at error समय and
 * dump it to the syslog.  Also call i915_capture_error_state() to make
 * sure we get a record and make it available in debugfs.  Fire a uevent
 * so userspace knows something bad happened (should trigger collection
 * of a ring dump etc.).
 */
व्योम पूर्णांकel_gt_handle_error(काष्ठा पूर्णांकel_gt *gt,
			   पूर्णांकel_engine_mask_t engine_mask,
			   अचिन्हित दीर्घ flags,
			   स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांकel_engine_mask_t पंचांगp;
	अक्षर error_msg[80];
	अक्षर *msg = शून्य;

	अगर (fmt) अणु
		बहु_सूची args;

		बहु_शुरू(args, fmt);
		vscnम_लिखो(error_msg, माप(error_msg), fmt, args);
		बहु_पूर्ण(args);

		msg = error_msg;
	पूर्ण

	/*
	 * In most हालs it's guaranteed that we get here with an RPM
	 * reference held, क्रम example because there is a pending GPU
	 * request that won't finish until the reset is करोne. This
	 * isn't the हाल at least when we get here by करोing a
	 * simulated reset via debugfs, so get an RPM reference.
	 */
	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);

	engine_mask &= gt->info.engine_mask;

	अगर (flags & I915_ERROR_CAPTURE) अणु
		i915_capture_error_state(gt, engine_mask);
		पूर्णांकel_gt_clear_error_रेजिस्टरs(gt, engine_mask);
	पूर्ण

	/*
	 * Try engine reset when available. We fall back to full reset अगर
	 * single reset fails.
	 */
	अगर (पूर्णांकel_has_reset_engine(gt) && !पूर्णांकel_gt_is_wedged(gt)) अणु
		local_bh_disable();
		क्रम_each_engine_masked(engine, gt, engine_mask, पंचांगp) अणु
			BUILD_BUG_ON(I915_RESET_MODESET >= I915_RESET_ENGINE);
			अगर (test_and_set_bit(I915_RESET_ENGINE + engine->id,
					     &gt->reset.flags))
				जारी;

			अगर (__पूर्णांकel_engine_reset_bh(engine, msg) == 0)
				engine_mask &= ~engine->mask;

			clear_and_wake_up_bit(I915_RESET_ENGINE + engine->id,
					      &gt->reset.flags);
		पूर्ण
		local_bh_enable();
	पूर्ण

	अगर (!engine_mask)
		जाओ out;

	/* Full reset needs the mutex, stop any other user trying to करो so. */
	अगर (test_and_set_bit(I915_RESET_BACKOFF, &gt->reset.flags)) अणु
		रुको_event(gt->reset.queue,
			   !test_bit(I915_RESET_BACKOFF, &gt->reset.flags));
		जाओ out; /* piggy-back on the other reset */
	पूर्ण

	/* Make sure i915_reset_trylock() sees the I915_RESET_BACKOFF */
	synchronize_rcu_expedited();

	/* Prevent any other reset-engine attempt. */
	क्रम_each_engine(engine, gt, पंचांगp) अणु
		जबतक (test_and_set_bit(I915_RESET_ENGINE + engine->id,
					&gt->reset.flags))
			रुको_on_bit(&gt->reset.flags,
				    I915_RESET_ENGINE + engine->id,
				    TASK_UNINTERRUPTIBLE);
	पूर्ण

	पूर्णांकel_gt_reset_global(gt, engine_mask, msg);

	क्रम_each_engine(engine, gt, पंचांगp)
		clear_bit_unlock(I915_RESET_ENGINE + engine->id,
				 &gt->reset.flags);
	clear_bit_unlock(I915_RESET_BACKOFF, &gt->reset.flags);
	smp_mb__after_atomic();
	wake_up_all(&gt->reset.queue);

out:
	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);
पूर्ण

पूर्णांक पूर्णांकel_gt_reset_trylock(काष्ठा पूर्णांकel_gt *gt, पूर्णांक *srcu)
अणु
	might_lock(&gt->reset.backoff_srcu);
	might_sleep();

	rcu_पढ़ो_lock();
	जबतक (test_bit(I915_RESET_BACKOFF, &gt->reset.flags)) अणु
		rcu_पढ़ो_unlock();

		अगर (रुको_event_पूर्णांकerruptible(gt->reset.queue,
					     !test_bit(I915_RESET_BACKOFF,
						       &gt->reset.flags)))
			वापस -EINTR;

		rcu_पढ़ो_lock();
	पूर्ण
	*srcu = srcu_पढ़ो_lock(&gt->reset.backoff_srcu);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

व्योम पूर्णांकel_gt_reset_unlock(काष्ठा पूर्णांकel_gt *gt, पूर्णांक tag)
__releases(&gt->reset.backoff_srcu)
अणु
	srcu_पढ़ो_unlock(&gt->reset.backoff_srcu, tag);
पूर्ण

पूर्णांक पूर्णांकel_gt_terminally_wedged(काष्ठा पूर्णांकel_gt *gt)
अणु
	might_sleep();

	अगर (!पूर्णांकel_gt_is_wedged(gt))
		वापस 0;

	अगर (पूर्णांकel_gt_has_unrecoverable_error(gt))
		वापस -EIO;

	/* Reset still in progress? Maybe we will recover? */
	अगर (रुको_event_पूर्णांकerruptible(gt->reset.queue,
				     !test_bit(I915_RESET_BACKOFF,
					       &gt->reset.flags)))
		वापस -EINTR;

	वापस पूर्णांकel_gt_is_wedged(gt) ? -EIO : 0;
पूर्ण

व्योम पूर्णांकel_gt_set_wedged_on_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	BUILD_BUG_ON(I915_RESET_ENGINE + I915_NUM_ENGINES >
		     I915_WEDGED_ON_INIT);
	पूर्णांकel_gt_set_wedged(gt);
	set_bit(I915_WEDGED_ON_INIT, &gt->reset.flags);

	/* Wedged on init is non-recoverable */
	add_taपूर्णांक_क्रम_CI(gt->i915, TAINT_WARN);
पूर्ण

व्योम पूर्णांकel_gt_set_wedged_on_fini(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_gt_set_wedged(gt);
	set_bit(I915_WEDGED_ON_FINI, &gt->reset.flags);
	पूर्णांकel_gt_retire_requests(gt); /* cleanup any wedged requests */
पूर्ण

व्योम पूर्णांकel_gt_init_reset(काष्ठा पूर्णांकel_gt *gt)
अणु
	init_रुकोqueue_head(&gt->reset.queue);
	mutex_init(&gt->reset.mutex);
	init_srcu_काष्ठा(&gt->reset.backoff_srcu);

	/*
	 * While undesirable to रुको inside the shrinker, complain anyway.
	 *
	 * If we have to रुको during shrinking, we guarantee क्रमward progress
	 * by क्रमcing the reset. Thereक्रमe during the reset we must not
	 * re-enter the shrinker. By declaring that we take the reset mutex
	 * within the shrinker, we क्रमbid ourselves from perक्रमming any
	 * fs-reclaim or taking related locks during reset.
	 */
	i915_gem_shrinker_taपूर्णांकs_mutex(gt->i915, &gt->reset.mutex);

	/* no GPU until we are पढ़ोy! */
	__set_bit(I915_WEDGED, &gt->reset.flags);
पूर्ण

व्योम पूर्णांकel_gt_fini_reset(काष्ठा पूर्णांकel_gt *gt)
अणु
	cleanup_srcu_काष्ठा(&gt->reset.backoff_srcu);
पूर्ण

अटल व्योम पूर्णांकel_wedge_me(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_wedge_me *w = container_of(work, typeof(*w), work.work);

	drm_err(&w->gt->i915->drm,
		"%s timed out, cancelling all in-flight rendering.\n",
		w->name);
	पूर्णांकel_gt_set_wedged(w->gt);
पूर्ण

व्योम __पूर्णांकel_init_wedge(काष्ठा पूर्णांकel_wedge_me *w,
			काष्ठा पूर्णांकel_gt *gt,
			दीर्घ समयout,
			स्थिर अक्षर *name)
अणु
	w->gt = gt;
	w->name = name;

	INIT_DELAYED_WORK_ONSTACK(&w->work, पूर्णांकel_wedge_me);
	schedule_delayed_work(&w->work, समयout);
पूर्ण

व्योम __पूर्णांकel_fini_wedge(काष्ठा पूर्णांकel_wedge_me *w)
अणु
	cancel_delayed_work_sync(&w->work);
	destroy_delayed_work_on_stack(&w->work);
	w->gt = शून्य;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_reset.c"
#समावेश "selftest_hangcheck.c"
#पूर्ण_अगर
