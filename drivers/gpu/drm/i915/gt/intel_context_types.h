<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_CONTEXT_TYPES__
#घोषणा __INTEL_CONTEXT_TYPES__

#समावेश <linux/average.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

#समावेश "i915_active_types.h"
#समावेश "i915_utils.h"
#समावेश "intel_engine_types.h"
#समावेश "intel_sseu.h"

#घोषणा CONTEXT_REDZONE POISON_INUSE

DECLARE_EWMA(runसमय, 3, 8);

काष्ठा i915_gem_context;
काष्ठा i915_gem_ww_ctx;
काष्ठा i915_vma;
काष्ठा पूर्णांकel_bपढ़ोcrumbs;
काष्ठा पूर्णांकel_context;
काष्ठा पूर्णांकel_ring;

काष्ठा पूर्णांकel_context_ops अणु
	अचिन्हित दीर्घ flags;
#घोषणा COPS_HAS_INFLIGHT_BIT 0
#घोषणा COPS_HAS_INFLIGHT BIT(COPS_HAS_INFLIGHT_BIT)

	पूर्णांक (*alloc)(काष्ठा पूर्णांकel_context *ce);

	पूर्णांक (*pre_pin)(काष्ठा पूर्णांकel_context *ce, काष्ठा i915_gem_ww_ctx *ww, व्योम **vaddr);
	पूर्णांक (*pin)(काष्ठा पूर्णांकel_context *ce, व्योम *vaddr);
	व्योम (*unpin)(काष्ठा पूर्णांकel_context *ce);
	व्योम (*post_unpin)(काष्ठा पूर्णांकel_context *ce);

	व्योम (*enter)(काष्ठा पूर्णांकel_context *ce);
	व्योम (*निकास)(काष्ठा पूर्णांकel_context *ce);

	व्योम (*reset)(काष्ठा पूर्णांकel_context *ce);
	व्योम (*destroy)(काष्ठा kref *kref);
पूर्ण;

काष्ठा पूर्णांकel_context अणु
	/*
	 * Note: Some fields may be accessed under RCU.
	 *
	 * Unless otherwise noted a field can safely be assumed to be रक्षित
	 * by strong reference counting.
	 */
	जोड़ अणु
		काष्ठा kref ref; /* no kref_get_unless_zero()! */
		काष्ठा rcu_head rcu;
	पूर्ण;

	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा पूर्णांकel_engine_cs *inflight;
#घोषणा __पूर्णांकel_context_inflight(engine) ptr_mask_bits(engine, 3)
#घोषणा __पूर्णांकel_context_inflight_count(engine) ptr_unmask_bits(engine, 3)
#घोषणा पूर्णांकel_context_inflight(ce) \
	__पूर्णांकel_context_inflight(READ_ONCE((ce)->inflight))
#घोषणा पूर्णांकel_context_inflight_count(ce) \
	__पूर्णांकel_context_inflight_count(READ_ONCE((ce)->inflight))

	काष्ठा i915_address_space *vm;
	काष्ठा i915_gem_context __rcu *gem_context;

	/*
	 * @संकेत_lock protects the list of requests that need संकेतing,
	 * @संकेतs. While there are any requests that need संकेतing,
	 * we add the context to the bपढ़ोcrumbs worker, and हटाओ it
	 * upon completion/cancellation of the last request.
	 */
	काष्ठा list_head संकेत_link; /* Accessed under RCU */
	काष्ठा list_head संकेतs; /* Guarded by संकेत_lock */
	spinlock_t संकेत_lock; /* protects संकेतs, the list of requests */

	काष्ठा i915_vma *state;
	काष्ठा पूर्णांकel_ring *ring;
	काष्ठा पूर्णांकel_समयline *समयline;

	अचिन्हित दीर्घ flags;
#घोषणा CONTEXT_BARRIER_BIT		0
#घोषणा CONTEXT_ALLOC_BIT		1
#घोषणा CONTEXT_INIT_BIT		2
#घोषणा CONTEXT_VALID_BIT		3
#घोषणा CONTEXT_CLOSED_BIT		4
#घोषणा CONTEXT_USE_SEMAPHORES		5
#घोषणा CONTEXT_BANNED			6
#घोषणा CONTEXT_FORCE_SINGLE_SUBMISSION	7
#घोषणा CONTEXT_NOPREEMPT		8

	काष्ठा अणु
		u64 समयout_us;
	पूर्ण watchकरोg;

	u32 *lrc_reg_state;
	जोड़ अणु
		काष्ठा अणु
			u32 lrca;
			u32 ccid;
		पूर्ण;
		u64 desc;
	पूर्ण lrc;
	u32 tag; /* cookie passed to HW to track this context on submission */

	/* Time on GPU as tracked by the hw. */
	काष्ठा अणु
		काष्ठा ewma_runसमय avg;
		u64 total;
		u32 last;
		I915_SELFTEST_DECLARE(u32 num_underflow);
		I915_SELFTEST_DECLARE(u32 max_underflow);
	पूर्ण runसमय;

	अचिन्हित पूर्णांक active_count; /* रक्षित by समयline->mutex */

	atomic_t pin_count;
	काष्ठा mutex pin_mutex; /* guards pinning and associated on-gpuing */

	/**
	 * active: Active tracker क्रम the rq activity (inc. बाह्यal) on this
	 * पूर्णांकel_context object.
	 */
	काष्ठा i915_active active;

	स्थिर काष्ठा पूर्णांकel_context_ops *ops;

	/** sseu: Control eu/slice partitioning */
	काष्ठा पूर्णांकel_sseu sseu;

	u8 wa_bb_page; /* अगर set, page num reserved क्रम context workarounds */
पूर्ण;

#पूर्ण_अगर /* __INTEL_CONTEXT_TYPES__ */
