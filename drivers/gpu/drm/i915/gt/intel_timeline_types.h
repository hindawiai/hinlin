<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __I915_TIMELINE_TYPES_H__
#घोषणा __I915_TIMELINE_TYPES_H__

#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/types.h>

#समावेश "i915_active_types.h"

काष्ठा i915_vma;
काष्ठा i915_syncmap;
काष्ठा पूर्णांकel_gt;

काष्ठा पूर्णांकel_समयline अणु
	u64 fence_context;
	u32 seqno;

	काष्ठा mutex mutex; /* protects the flow of requests */

	/*
	 * pin_count and active_count track essentially the same thing:
	 * How many requests are in flight or may be under स्थिरruction.
	 *
	 * We need two distinct counters so that we can assign dअगरferent
	 * lअगरeबार to the events क्रम dअगरferent use-हालs. For example,
	 * we want to permanently keep the समयline pinned क्रम the kernel
	 * context so that we can issue requests at any समय without having
	 * to acquire space in the GGTT. However, we want to keep tracking
	 * the activity (to be able to detect when we become idle) aदीर्घ that
	 * permanently pinned समयline and so end up requiring two counters.
	 *
	 * Note that the active_count is रक्षित by the पूर्णांकel_समयline.mutex,
	 * but the pin_count is रक्षित by a combination of serialisation
	 * from the पूर्णांकel_context caller plus पूर्णांकernal atomicity.
	 */
	atomic_t pin_count;
	atomic_t active_count;

	व्योम *hwsp_map;
	स्थिर u32 *hwsp_seqno;
	काष्ठा i915_vma *hwsp_ggtt;
	u32 hwsp_offset;

	bool has_initial_bपढ़ोcrumb;

	/**
	 * List of bपढ़ोcrumbs associated with GPU requests currently
	 * outstanding.
	 */
	काष्ठा list_head requests;

	/*
	 * Contains an RCU guarded poपूर्णांकer to the last request. No reference is
	 * held to the request, users must carefully acquire a reference to
	 * the request using i915_active_fence_get(), or manage the RCU
	 * protection themselves (cf the i915_active_fence API).
	 */
	काष्ठा i915_active_fence last_request;

	काष्ठा i915_active active;

	/** A chain of completed समयlines पढ़ोy क्रम early retirement. */
	काष्ठा पूर्णांकel_समयline *retire;

	/**
	 * We track the most recent seqno that we रुको on in every context so
	 * that we only have to emit a new aरुको and dependency on a more
	 * recent sync poपूर्णांक. As the contexts may be executed out-of-order, we
	 * have to track each inभागidually and can not rely on an असलolute
	 * global_seqno. When we know that all tracked fences are completed
	 * (i.e. when the driver is idle), we know that the syncmap is
	 * redundant and we can discard it without loss of generality.
	 */
	काष्ठा i915_syncmap *sync;

	काष्ठा list_head link;
	काष्ठा पूर्णांकel_gt *gt;

	काष्ठा list_head engine_link;

	काष्ठा kref kref;
	काष्ठा rcu_head rcu;
पूर्ण;

#पूर्ण_अगर /* __I915_TIMELINE_TYPES_H__ */
