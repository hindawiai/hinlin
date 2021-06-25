<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "i915_vma.h"
#समावेश "intel_context.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_lrc.h"
#समावेश "intel_ring.h"
#समावेश "intel_sseu.h"

अटल पूर्णांक gen8_emit_rpcs_config(काष्ठा i915_request *rq,
				 स्थिर काष्ठा पूर्णांकel_context *ce,
				 स्थिर काष्ठा पूर्णांकel_sseu sseu)
अणु
	u64 offset;
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	offset = i915_ggtt_offset(ce->state) +
		 LRC_STATE_OFFSET + CTX_R_PWR_CLK_STATE * 4;

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = lower_32_bits(offset);
	*cs++ = upper_32_bits(offset);
	*cs++ = पूर्णांकel_sseu_make_rpcs(rq->engine->gt, &sseu);

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक
gen8_modअगरy_rpcs(काष्ठा पूर्णांकel_context *ce, स्थिर काष्ठा पूर्णांकel_sseu sseu)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ce->pin_mutex);

	/*
	 * If the context is not idle, we have to submit an ordered request to
	 * modअगरy its context image via the kernel context (writing to our own
	 * image, or पूर्णांकo the रेजिस्टरs directory, करोes not stick). Pristine
	 * and idle contexts will be configured on pinning.
	 */
	अगर (!पूर्णांकel_context_pin_अगर_active(ce))
		वापस 0;

	rq = पूर्णांकel_engine_create_kernel_request(ce->engine);
	अगर (IS_ERR(rq)) अणु
		ret = PTR_ERR(rq);
		जाओ out_unpin;
	पूर्ण

	/* Serialise with the remote context */
	ret = पूर्णांकel_context_prepare_remote_request(ce, rq);
	अगर (ret == 0)
		ret = gen8_emit_rpcs_config(rq, ce, sseu);

	i915_request_add(rq);
out_unpin:
	पूर्णांकel_context_unpin(ce);
	वापस ret;
पूर्ण

पूर्णांक
पूर्णांकel_context_reconfigure_sseu(काष्ठा पूर्णांकel_context *ce,
			       स्थिर काष्ठा पूर्णांकel_sseu sseu)
अणु
	पूर्णांक ret;

	GEM_BUG_ON(INTEL_GEN(ce->engine->i915) < 8);

	ret = पूर्णांकel_context_lock_pinned(ce);
	अगर (ret)
		वापस ret;

	/* Nothing to करो अगर unmodअगरied. */
	अगर (!स_भेद(&ce->sseu, &sseu, माप(sseu)))
		जाओ unlock;

	ret = gen8_modअगरy_rpcs(ce, sseu);
	अगर (!ret)
		ce->sseu = sseu;

unlock:
	पूर्णांकel_context_unlock_pinned(ce);
	वापस ret;
पूर्ण
