<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_GT_TYPES__
#घोषणा __INTEL_GT_TYPES__

#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/llist.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश "uc/intel_uc.h"

#समावेश "i915_vma.h"
#समावेश "intel_engine_types.h"
#समावेश "intel_gt_buffer_pool_types.h"
#समावेश "intel_llc_types.h"
#समावेश "intel_reset_types.h"
#समावेश "intel_rc6_types.h"
#समावेश "intel_rps_types.h"
#समावेश "intel_wakeref.h"

काष्ठा drm_i915_निजी;
काष्ठा i915_ggtt;
काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_uncore;

काष्ठा पूर्णांकel_gt अणु
	काष्ठा drm_i915_निजी *i915;
	काष्ठा पूर्णांकel_uncore *uncore;
	काष्ठा i915_ggtt *ggtt;

	काष्ठा पूर्णांकel_uc uc;

	काष्ठा पूर्णांकel_gt_समयlines अणु
		spinlock_t lock; /* protects active_list */
		काष्ठा list_head active_list;
	पूर्ण समयlines;

	काष्ठा पूर्णांकel_gt_requests अणु
		/**
		 * We leave the user IRQ off as much as possible,
		 * but this means that requests will finish and never
		 * be retired once the प्रणाली goes idle. Set a समयr to
		 * fire periodically जबतक the ring is running. When it
		 * fires, go retire requests.
		 */
		काष्ठा delayed_work retire_work;
	पूर्ण requests;

	काष्ठा अणु
		काष्ठा llist_head list;
		काष्ठा work_काष्ठा work;
	पूर्ण watchकरोg;

	काष्ठा पूर्णांकel_wakeref wakeref;
	atomic_t user_wakeref;

	काष्ठा list_head बंदd_vma;
	spinlock_t बंदd_lock; /* guards the list of बंदd_vma */

	kसमय_प्रकार last_init_समय;
	काष्ठा पूर्णांकel_reset reset;

	/**
	 * Is the GPU currently considered idle, or busy executing
	 * userspace requests? Whilst idle, we allow runसमय घातer
	 * management to घातer करोwn the hardware and display घड़ीs.
	 * In order to reduce the effect on perक्रमmance, there
	 * is a slight delay beक्रमe we करो so.
	 */
	पूर्णांकel_wakeref_t awake;

	u32 घड़ी_frequency;
	u32 घड़ी_period_ns;

	काष्ठा पूर्णांकel_llc llc;
	काष्ठा पूर्णांकel_rc6 rc6;
	काष्ठा पूर्णांकel_rps rps;

	spinlock_t irq_lock;
	u32 gt_imr;
	u32 pm_ier;
	u32 pm_imr;

	u32 pm_guc_events;

	काष्ठा अणु
		bool active;

		/**
		 * @lock: Lock protecting the below fields.
		 */
		seqcount_mutex_t lock;

		/**
		 * @total: Total समय this engine was busy.
		 *
		 * Accumulated समय not counting the most recent block in हालs
		 * where engine is currently busy (active > 0).
		 */
		kसमय_प्रकार total;

		/**
		 * @start: Timestamp of the last idle to active transition.
		 *
		 * Idle is defined as active == 0, active is active > 0.
		 */
		kसमय_प्रकार start;
	पूर्ण stats;

	काष्ठा पूर्णांकel_engine_cs *engine[I915_NUM_ENGINES];
	काष्ठा पूर्णांकel_engine_cs *engine_class[MAX_ENGINE_CLASS + 1]
					    [MAX_ENGINE_INSTANCE + 1];

	/*
	 * Default address space (either GGTT or ppGTT depending on arch).
	 *
	 * Reserved क्रम exclusive use by the kernel.
	 */
	काष्ठा i915_address_space *vm;

	/*
	 * A pool of objects to use as shaकरोw copies of client batch buffers
	 * when the command parser is enabled. Prevents the client from
	 * modअगरying the batch contents after software parsing.
	 *
	 * Buffers older than 1s are periodically reaped from the pool,
	 * or may be reclaimed by the shrinker beक्रमe then.
	 */
	काष्ठा पूर्णांकel_gt_buffer_pool buffer_pool;

	काष्ठा i915_vma *scratch;

	काष्ठा पूर्णांकel_gt_info अणु
		पूर्णांकel_engine_mask_t engine_mask;
		u8 num_engines;

		/* Media engine access to SFC per instance */
		u8 vdbox_sfc_access;

		/* Slice/subslice/EU info */
		काष्ठा sseu_dev_info sseu;
	पूर्ण info;
पूर्ण;

क्रमागत पूर्णांकel_gt_scratch_field अणु
	/* 8 bytes */
	INTEL_GT_SCRATCH_FIELD_DEFAULT = 0,

	/* 8 bytes */
	INTEL_GT_SCRATCH_FIELD_RENDER_FLUSH = 128,

	/* 8 bytes */
	INTEL_GT_SCRATCH_FIELD_COHERENTL3_WA = 256,

	/* 6 * 8 bytes */
	INTEL_GT_SCRATCH_FIELD_PERF_CS_GPR = 2048,

	/* 4 bytes */
	INTEL_GT_SCRATCH_FIELD_PERF_PREDICATE_RESULT_1 = 2096,
पूर्ण;

#पूर्ण_अगर /* __INTEL_GT_TYPES_H__ */
