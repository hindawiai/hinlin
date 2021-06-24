<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_CONTEXT_H__
#घोषणा __INTEL_CONTEXT_H__

#समावेश <linux/bitops.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/types.h>

#समावेश "i915_active.h"
#समावेश "i915_drv.h"
#समावेश "intel_context_types.h"
#समावेश "intel_engine_types.h"
#समावेश "intel_ring_types.h"
#समावेश "intel_timeline_types.h"

#घोषणा CE_TRACE(ce, fmt, ...) करो अणु					\
	स्थिर काष्ठा पूर्णांकel_context *ce__ = (ce);			\
	ENGINE_TRACE(ce__->engine, "context:%llx " fmt,			\
		     ce__->समयline->fence_context,			\
		     ##__VA_ARGS__);					\
पूर्ण जबतक (0)

काष्ठा i915_gem_ww_ctx;

व्योम पूर्णांकel_context_init(काष्ठा पूर्णांकel_context *ce,
			काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_context_fini(काष्ठा पूर्णांकel_context *ce);

काष्ठा पूर्णांकel_context *
पूर्णांकel_context_create(काष्ठा पूर्णांकel_engine_cs *engine);

पूर्णांक पूर्णांकel_context_alloc_state(काष्ठा पूर्णांकel_context *ce);

व्योम पूर्णांकel_context_मुक्त(काष्ठा पूर्णांकel_context *ce);

पूर्णांक पूर्णांकel_context_reconfigure_sseu(काष्ठा पूर्णांकel_context *ce,
				   स्थिर काष्ठा पूर्णांकel_sseu sseu);

/**
 * पूर्णांकel_context_lock_pinned - Stablises the 'pinned' status of the HW context
 * @ce - the context
 *
 * Acquire a lock on the pinned status of the HW context, such that the context
 * can neither be bound to the GPU or unbound whilst the lock is held, i.e.
 * पूर्णांकel_context_is_pinned() reमुख्यs stable.
 */
अटल अंतरभूत पूर्णांक पूर्णांकel_context_lock_pinned(काष्ठा पूर्णांकel_context *ce)
	__acquires(ce->pin_mutex)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&ce->pin_mutex);
पूर्ण

/**
 * पूर्णांकel_context_is_pinned - Reports the 'pinned' status
 * @ce - the context
 *
 * While in use by the GPU, the context, aदीर्घ with its ring and page
 * tables is pinned पूर्णांकo memory and the GTT.
 *
 * Returns: true अगर the context is currently pinned क्रम use by the GPU.
 */
अटल अंतरभूत bool
पूर्णांकel_context_is_pinned(काष्ठा पूर्णांकel_context *ce)
अणु
	वापस atomic_पढ़ो(&ce->pin_count);
पूर्ण

/**
 * पूर्णांकel_context_unlock_pinned - Releases the earlier locking of 'pinned' status
 * @ce - the context
 *
 * Releases the lock earlier acquired by पूर्णांकel_context_unlock_pinned().
 */
अटल अंतरभूत व्योम पूर्णांकel_context_unlock_pinned(काष्ठा पूर्णांकel_context *ce)
	__releases(ce->pin_mutex)
अणु
	mutex_unlock(&ce->pin_mutex);
पूर्ण

पूर्णांक __पूर्णांकel_context_करो_pin(काष्ठा पूर्णांकel_context *ce);
पूर्णांक __पूर्णांकel_context_करो_pin_ww(काष्ठा पूर्णांकel_context *ce,
			      काष्ठा i915_gem_ww_ctx *ww);

अटल अंतरभूत bool पूर्णांकel_context_pin_अगर_active(काष्ठा पूर्णांकel_context *ce)
अणु
	वापस atomic_inc_not_zero(&ce->pin_count);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_context_pin(काष्ठा पूर्णांकel_context *ce)
अणु
	अगर (likely(पूर्णांकel_context_pin_अगर_active(ce)))
		वापस 0;

	वापस __पूर्णांकel_context_करो_pin(ce);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_context_pin_ww(काष्ठा पूर्णांकel_context *ce,
				       काष्ठा i915_gem_ww_ctx *ww)
अणु
	अगर (likely(पूर्णांकel_context_pin_अगर_active(ce)))
		वापस 0;

	वापस __पूर्णांकel_context_करो_pin_ww(ce, ww);
पूर्ण

अटल अंतरभूत व्योम __पूर्णांकel_context_pin(काष्ठा पूर्णांकel_context *ce)
अणु
	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(ce));
	atomic_inc(&ce->pin_count);
पूर्ण

व्योम पूर्णांकel_context_unpin(काष्ठा पूर्णांकel_context *ce);

व्योम पूर्णांकel_context_enter_engine(काष्ठा पूर्णांकel_context *ce);
व्योम पूर्णांकel_context_निकास_engine(काष्ठा पूर्णांकel_context *ce);

अटल अंतरभूत व्योम पूर्णांकel_context_enter(काष्ठा पूर्णांकel_context *ce)
अणु
	lockdep_निश्चित_held(&ce->समयline->mutex);
	अगर (!ce->active_count++)
		ce->ops->enter(ce);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_context_mark_active(काष्ठा पूर्णांकel_context *ce)
अणु
	lockdep_निश्चित_held(&ce->समयline->mutex);
	++ce->active_count;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_context_निकास(काष्ठा पूर्णांकel_context *ce)
अणु
	lockdep_निश्चित_held(&ce->समयline->mutex);
	GEM_BUG_ON(!ce->active_count);
	अगर (!--ce->active_count)
		ce->ops->निकास(ce);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_context *पूर्णांकel_context_get(काष्ठा पूर्णांकel_context *ce)
अणु
	kref_get(&ce->ref);
	वापस ce;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_context_put(काष्ठा पूर्णांकel_context *ce)
अणु
	kref_put(&ce->ref, ce->ops->destroy);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_समयline *__must_check
पूर्णांकel_context_समयline_lock(काष्ठा पूर्णांकel_context *ce)
	__acquires(&ce->समयline->mutex)
अणु
	काष्ठा पूर्णांकel_समयline *tl = ce->समयline;
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&tl->mutex);
	अगर (err)
		वापस ERR_PTR(err);

	वापस tl;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_context_समयline_unlock(काष्ठा पूर्णांकel_समयline *tl)
	__releases(&tl->mutex)
अणु
	mutex_unlock(&tl->mutex);
पूर्ण

पूर्णांक पूर्णांकel_context_prepare_remote_request(काष्ठा पूर्णांकel_context *ce,
					 काष्ठा i915_request *rq);

काष्ठा i915_request *पूर्णांकel_context_create_request(काष्ठा पूर्णांकel_context *ce);

अटल अंतरभूत काष्ठा पूर्णांकel_ring *__पूर्णांकel_context_ring_size(u64 sz)
अणु
	वापस u64_to_ptr(काष्ठा पूर्णांकel_ring, sz);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_context_is_barrier(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस test_bit(CONTEXT_BARRIER_BIT, &ce->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_context_is_बंदd(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस test_bit(CONTEXT_CLOSED_BIT, &ce->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_context_has_inflight(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस test_bit(COPS_HAS_INFLIGHT_BIT, &ce->ops->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_context_use_semaphores(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस test_bit(CONTEXT_USE_SEMAPHORES, &ce->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_context_set_use_semaphores(काष्ठा पूर्णांकel_context *ce)
अणु
	set_bit(CONTEXT_USE_SEMAPHORES, &ce->flags);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_context_clear_use_semaphores(काष्ठा पूर्णांकel_context *ce)
अणु
	clear_bit(CONTEXT_USE_SEMAPHORES, &ce->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_context_is_banned(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस test_bit(CONTEXT_BANNED, &ce->flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_context_set_banned(काष्ठा पूर्णांकel_context *ce)
अणु
	वापस test_and_set_bit(CONTEXT_BANNED, &ce->flags);
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_context_क्रमce_single_submission(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस test_bit(CONTEXT_FORCE_SINGLE_SUBMISSION, &ce->flags);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_context_set_single_submission(काष्ठा पूर्णांकel_context *ce)
अणु
	__set_bit(CONTEXT_FORCE_SINGLE_SUBMISSION, &ce->flags);
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_context_nopreempt(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	वापस test_bit(CONTEXT_NOPREEMPT, &ce->flags);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_context_set_nopreempt(काष्ठा पूर्णांकel_context *ce)
अणु
	set_bit(CONTEXT_NOPREEMPT, &ce->flags);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_context_clear_nopreempt(काष्ठा पूर्णांकel_context *ce)
अणु
	clear_bit(CONTEXT_NOPREEMPT, &ce->flags);
पूर्ण

अटल अंतरभूत u64 पूर्णांकel_context_get_total_runसमय_ns(काष्ठा पूर्णांकel_context *ce)
अणु
	स्थिर u32 period = ce->engine->gt->घड़ी_period_ns;

	वापस READ_ONCE(ce->runसमय.total) * period;
पूर्ण

अटल अंतरभूत u64 पूर्णांकel_context_get_avg_runसमय_ns(काष्ठा पूर्णांकel_context *ce)
अणु
	स्थिर u32 period = ce->engine->gt->घड़ी_period_ns;

	वापस mul_u32_u32(ewma_runसमय_पढ़ो(&ce->runसमय.avg), period);
पूर्ण

#पूर्ण_अगर /* __INTEL_CONTEXT_H__ */
