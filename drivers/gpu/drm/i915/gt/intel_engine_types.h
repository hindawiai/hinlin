<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_ENGINE_TYPES__
#घोषणा __INTEL_ENGINE_TYPES__

#समावेश <linux/average.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/llist.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश "i915_gem.h"
#समावेश "i915_pmu.h"
#समावेश "i915_priolist_types.h"
#समावेश "i915_selftest.h"
#समावेश "intel_breadcrumbs_types.h"
#समावेश "intel_sseu.h"
#समावेश "intel_timeline_types.h"
#समावेश "intel_uncore.h"
#समावेश "intel_wakeref.h"
#समावेश "intel_workarounds_types.h"

/* Legacy HW Engine ID */

#घोषणा RCS0_HW		0
#घोषणा VCS0_HW		1
#घोषणा BCS0_HW		2
#घोषणा VECS0_HW	3
#घोषणा VCS1_HW		4
#घोषणा VCS2_HW		6
#घोषणा VCS3_HW		7
#घोषणा VECS1_HW	12

/* Gen11+ HW Engine class + instance */
#घोषणा RENDER_CLASS		0
#घोषणा VIDEO_DECODE_CLASS	1
#घोषणा VIDEO_ENHANCEMENT_CLASS	2
#घोषणा COPY_ENGINE_CLASS	3
#घोषणा OTHER_CLASS		4
#घोषणा MAX_ENGINE_CLASS	4
#घोषणा MAX_ENGINE_INSTANCE	3

#घोषणा I915_MAX_SLICES	3
#घोषणा I915_MAX_SUBSLICES 8

#घोषणा I915_CMD_HASH_ORDER 9

काष्ठा dma_fence;
काष्ठा drm_i915_gem_object;
काष्ठा drm_i915_reg_table;
काष्ठा i915_gem_context;
काष्ठा i915_request;
काष्ठा i915_sched_attr;
काष्ठा पूर्णांकel_gt;
काष्ठा पूर्णांकel_ring;
काष्ठा पूर्णांकel_uncore;

प्रकार u8 पूर्णांकel_engine_mask_t;
#घोषणा ALL_ENGINES ((पूर्णांकel_engine_mask_t)~0ul)

काष्ठा पूर्णांकel_hw_status_page अणु
	काष्ठा list_head समयlines;
	काष्ठा i915_vma *vma;
	u32 *addr;
पूर्ण;

काष्ठा पूर्णांकel_instकरोne अणु
	u32 instकरोne;
	/* The following exist only in the RCS engine */
	u32 slice_common;
	u32 slice_common_extra[2];
	u32 sampler[I915_MAX_SLICES][I915_MAX_SUBSLICES];
	u32 row[I915_MAX_SLICES][I915_MAX_SUBSLICES];
पूर्ण;

/*
 * we use a single page to load ctx workarounds so all of these
 * values are referred in terms of dwords
 *
 * काष्ठा i915_wa_ctx_bb:
 *  offset: specअगरies batch starting position, also helpful in हाल
 *    अगर we want to have multiple batches at dअगरferent offsets based on
 *    some criteria. It is not a requirement at the moment but provides
 *    an option क्रम future use.
 *  size: size of the batch in DWORDS
 */
काष्ठा i915_ctx_workarounds अणु
	काष्ठा i915_wa_ctx_bb अणु
		u32 offset;
		u32 size;
	पूर्ण indirect_ctx, per_ctx;
	काष्ठा i915_vma *vma;
पूर्ण;

#घोषणा I915_MAX_VCS	4
#घोषणा I915_MAX_VECS	2

/*
 * Engine IDs definitions.
 * Keep instances of the same type engine together.
 */
क्रमागत पूर्णांकel_engine_id अणु
	RCS0 = 0,
	BCS0,
	VCS0,
	VCS1,
	VCS2,
	VCS3,
#घोषणा _VCS(n) (VCS0 + (n))
	VECS0,
	VECS1,
#घोषणा _VECS(n) (VECS0 + (n))
	I915_NUM_ENGINES
#घोषणा INVALID_ENGINE ((क्रमागत पूर्णांकel_engine_id)-1)
पूर्ण;

/* A simple estimator क्रम the round-trip latency of an engine */
DECLARE_EWMA(_engine_latency, 6, 4)

काष्ठा st_preempt_hang अणु
	काष्ठा completion completion;
	अचिन्हित पूर्णांक count;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_engine_execlists - execlist submission queue and port state
 *
 * The काष्ठा पूर्णांकel_engine_execlists represents the combined logical state of
 * driver and the hardware state क्रम execlist mode of submission.
 */
काष्ठा पूर्णांकel_engine_execlists अणु
	/**
	 * @tasklet: softirq tasklet क्रम bottom handler
	 */
	काष्ठा tasklet_काष्ठा tasklet;

	/**
	 * @समयr: kick the current context अगर its बारlice expires
	 */
	काष्ठा समयr_list समयr;

	/**
	 * @preempt: reset the current context अगर it fails to give way
	 */
	काष्ठा समयr_list preempt;

	/**
	 * @शेष_priolist: priority list क्रम I915_PRIORITY_NORMAL
	 */
	काष्ठा i915_priolist शेष_priolist;

	/**
	 * @ccid: identअगरier क्रम contexts submitted to this engine
	 */
	u32 ccid;

	/**
	 * @yield: CCID at the समय of the last semaphore-रुको पूर्णांकerrupt.
	 *
	 * Instead of leaving a semaphore busy-spinning on an engine, we would
	 * like to चयन to another पढ़ोy context, i.e. yielding the semaphore
	 * बारlice.
	 */
	u32 yield;

	/**
	 * @error_पूर्णांकerrupt: CS Master EIR
	 *
	 * The CS generates an पूर्णांकerrupt when it detects an error. We capture
	 * the first error पूर्णांकerrupt, record the EIR and schedule the tasklet.
	 * In the tasklet, we process the pending CS events to ensure we have
	 * the guilty request, and then reset the engine.
	 *
	 * Low 16b are used by HW, with the upper 16b used as the enabling mask.
	 * Reserve the upper 16b क्रम tracking पूर्णांकernal errors.
	 */
	u32 error_पूर्णांकerrupt;
#घोषणा ERROR_CSB	BIT(31)
#घोषणा ERROR_PREEMPT	BIT(30)

	/**
	 * @reset_ccid: Active CCID [EXECLISTS_STATUS_HI] at the समय of reset
	 */
	u32 reset_ccid;

	/**
	 * @no_priolist: priority lists disabled
	 */
	bool no_priolist;

	/**
	 * @submit_reg: gen-specअगरic execlist submission रेजिस्टर
	 * set to the ExecList Submission Port (elsp) रेजिस्टर pre-Gen11 and to
	 * the ExecList Submission Queue Contents रेजिस्टर array क्रम Gen11+
	 */
	u32 __iomem *submit_reg;

	/**
	 * @ctrl_reg: the enhanced execlists control रेजिस्टर, used to load the
	 * submit queue on the HW and to request preemptions to idle
	 */
	u32 __iomem *ctrl_reg;

#घोषणा EXECLIST_MAX_PORTS 2
	/**
	 * @active: the currently known context executing on HW
	 */
	काष्ठा i915_request * स्थिर *active;
	/**
	 * @inflight: the set of contexts submitted and acknowleged by HW
	 *
	 * The set of inflight contexts is managed by पढ़ोing CS events
	 * from the HW. On a context-चयन event (not preemption), we
	 * know the HW has transitioned from port0 to port1, and we
	 * advance our inflight/active tracking accordingly.
	 */
	काष्ठा i915_request *inflight[EXECLIST_MAX_PORTS + 1 /* sentinel */];
	/**
	 * @pending: the next set of contexts submitted to ELSP
	 *
	 * We store the array of contexts that we submit to HW (via ELSP) and
	 * promote them to the inflight array once HW has संकेतed the
	 * preemption or idle-to-active event.
	 */
	काष्ठा i915_request *pending[EXECLIST_MAX_PORTS + 1];

	/**
	 * @port_mask: number of execlist ports - 1
	 */
	अचिन्हित पूर्णांक port_mask;

	/**
	 * @queue_priority_hपूर्णांक: Highest pending priority.
	 *
	 * When we add requests पूर्णांकo the queue, or adjust the priority of
	 * executing requests, we compute the maximum priority of those
	 * pending requests. We can then use this value to determine अगर
	 * we need to preempt the executing requests to service the queue.
	 * However, since the we may have recorded the priority of an inflight
	 * request we wanted to preempt but since completed, at the समय of
	 * dequeuing the priority hपूर्णांक may no दीर्घer may match the highest
	 * available request priority.
	 */
	पूर्णांक queue_priority_hपूर्णांक;

	/**
	 * @queue: queue of requests, in priority lists
	 */
	काष्ठा rb_root_cached queue;
	काष्ठा rb_root_cached भव;

	/**
	 * @csb_ग_लिखो: control रेजिस्टर क्रम Context Switch buffer
	 *
	 * Note this रेजिस्टर may be either mmio or HWSP shaकरोw.
	 */
	u32 *csb_ग_लिखो;

	/**
	 * @csb_status: status array क्रम Context Switch buffer
	 *
	 * Note these रेजिस्टर may be either mmio or HWSP shaकरोw.
	 */
	u64 *csb_status;

	/**
	 * @csb_size: context status buffer FIFO size
	 */
	u8 csb_size;

	/**
	 * @csb_head: context status buffer head
	 */
	u8 csb_head;

	I915_SELFTEST_DECLARE(काष्ठा st_preempt_hang preempt_hang;)
पूर्ण;

#घोषणा INTEL_ENGINE_CS_MAX_NAME 8

काष्ठा पूर्णांकel_engine_cs अणु
	काष्ठा drm_i915_निजी *i915;
	काष्ठा पूर्णांकel_gt *gt;
	काष्ठा पूर्णांकel_uncore *uncore;
	अक्षर name[INTEL_ENGINE_CS_MAX_NAME];

	क्रमागत पूर्णांकel_engine_id id;
	क्रमागत पूर्णांकel_engine_id legacy_idx;

	अचिन्हित पूर्णांक hw_id;
	अचिन्हित पूर्णांक guc_id;

	पूर्णांकel_engine_mask_t mask;

	u8 class;
	u8 instance;

	u16 uabi_class;
	u16 uabi_instance;

	u32 uabi_capabilities;
	u32 context_size;
	u32 mmio_base;

	/*
	 * Some w/a require क्रमcewake to be held (which prevents RC6) जबतक
	 * a particular engine is active. If so, we set fw_करोमुख्य to which
	 * करोमुख्यs need to be held क्रम the duration of request activity,
	 * and 0 अगर none. We try to limit the duration of the hold as much
	 * as possible.
	 */
	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्य;
	अचिन्हित पूर्णांक fw_active;

	अचिन्हित दीर्घ context_tag;

	काष्ठा rb_node uabi_node;

	काष्ठा पूर्णांकel_sseu sseu;

	काष्ठा अणु
		spinlock_t lock;
		काष्ठा list_head requests;
		काष्ठा list_head hold; /* पढ़ोy requests, but on hold */
	पूर्ण active;

	/* keep a request in reserve क्रम a [pm] barrier under oom */
	काष्ठा i915_request *request_pool;

	काष्ठा llist_head barrier_tasks;

	काष्ठा पूर्णांकel_context *kernel_context; /* pinned */

	पूर्णांकel_engine_mask_t saturated; /* submitting semaphores too late? */

	काष्ठा अणु
		काष्ठा delayed_work work;
		काष्ठा i915_request *systole;
		अचिन्हित दीर्घ blocked;
	पूर्ण heartbeat;

	अचिन्हित दीर्घ serial;

	अचिन्हित दीर्घ wakeref_serial;
	काष्ठा पूर्णांकel_wakeref wakeref;
	काष्ठा file *शेष_state;

	काष्ठा अणु
		काष्ठा पूर्णांकel_ring *ring;
		काष्ठा पूर्णांकel_समयline *समयline;
	पूर्ण legacy;

	/*
	 * We track the average duration of the idle pulse on parking the
	 * engine to keep an estimate of the how the fast the engine is
	 * under ideal conditions.
	 */
	काष्ठा ewma__engine_latency latency;

	/* Keep track of all the seqno used, a trail of bपढ़ोcrumbs */
	काष्ठा पूर्णांकel_bपढ़ोcrumbs *bपढ़ोcrumbs;

	काष्ठा पूर्णांकel_engine_pmu अणु
		/**
		 * @enable: Biपंचांगask of enable sample events on this engine.
		 *
		 * Bits correspond to sample event types, क्रम instance
		 * I915_SAMPLE_QUEUED is bit 0 etc.
		 */
		u32 enable;
		/**
		 * @enable_count: Reference count क्रम the enabled samplers.
		 *
		 * Index number corresponds to @क्रमागत drm_i915_pmu_engine_sample.
		 */
		अचिन्हित पूर्णांक enable_count[I915_ENGINE_SAMPLE_COUNT];
		/**
		 * @sample: Counter values क्रम sampling events.
		 *
		 * Our पूर्णांकernal समयr stores the current counters in this field.
		 *
		 * Index number corresponds to @क्रमागत drm_i915_pmu_engine_sample.
		 */
		काष्ठा i915_pmu_sample sample[I915_ENGINE_SAMPLE_COUNT];
	पूर्ण pmu;

	काष्ठा पूर्णांकel_hw_status_page status_page;
	काष्ठा i915_ctx_workarounds wa_ctx;
	काष्ठा i915_wa_list ctx_wa_list;
	काष्ठा i915_wa_list wa_list;
	काष्ठा i915_wa_list whitelist;

	u32             irq_keep_mask; /* always keep these पूर्णांकerrupts */
	u32		irq_enable_mask; /* biपंचांगask to enable ring पूर्णांकerrupt */
	व्योम		(*irq_enable)(काष्ठा पूर्णांकel_engine_cs *engine);
	व्योम		(*irq_disable)(काष्ठा पूर्णांकel_engine_cs *engine);

	व्योम		(*sanitize)(काष्ठा पूर्णांकel_engine_cs *engine);
	पूर्णांक		(*resume)(काष्ठा पूर्णांकel_engine_cs *engine);

	काष्ठा अणु
		व्योम (*prepare)(काष्ठा पूर्णांकel_engine_cs *engine);

		व्योम (*शुरुआत)(काष्ठा पूर्णांकel_engine_cs *engine, bool stalled);
		व्योम (*cancel)(काष्ठा पूर्णांकel_engine_cs *engine);

		व्योम (*finish)(काष्ठा पूर्णांकel_engine_cs *engine);
	पूर्ण reset;

	व्योम		(*park)(काष्ठा पूर्णांकel_engine_cs *engine);
	व्योम		(*unpark)(काष्ठा पूर्णांकel_engine_cs *engine);

	व्योम		(*set_शेष_submission)(काष्ठा पूर्णांकel_engine_cs *engine);

	स्थिर काष्ठा पूर्णांकel_context_ops *cops;

	पूर्णांक		(*request_alloc)(काष्ठा i915_request *rq);

	पूर्णांक		(*emit_flush)(काष्ठा i915_request *request, u32 mode);
#घोषणा EMIT_INVALIDATE	BIT(0)
#घोषणा EMIT_FLUSH	BIT(1)
#घोषणा EMIT_BARRIER	(EMIT_INVALIDATE | EMIT_FLUSH)
	पूर्णांक		(*emit_bb_start)(काष्ठा i915_request *rq,
					 u64 offset, u32 length,
					 अचिन्हित पूर्णांक dispatch_flags);
#घोषणा I915_DISPATCH_SECURE BIT(0)
#घोषणा I915_DISPATCH_PINNED BIT(1)
	पूर्णांक		 (*emit_init_bपढ़ोcrumb)(काष्ठा i915_request *rq);
	u32		*(*emit_fini_bपढ़ोcrumb)(काष्ठा i915_request *rq,
						 u32 *cs);
	अचिन्हित पूर्णांक	emit_fini_bपढ़ोcrumb_dw;

	/* Pass the request to the hardware queue (e.g. directly पूर्णांकo
	 * the legacy ringbuffer or to the end of an execlist).
	 *
	 * This is called from an atomic context with irqs disabled; must
	 * be irq safe.
	 */
	व्योम		(*submit_request)(काष्ठा i915_request *rq);

	/*
	 * Called on संकेतing of a SUBMIT_FENCE, passing aदीर्घ the संकेतing
	 * request करोwn to the bonded pairs.
	 */
	व्योम            (*bond_execute)(काष्ठा i915_request *rq,
					काष्ठा dma_fence *संकेत);

	/*
	 * Call when the priority on a request has changed and it and its
	 * dependencies may need rescheduling. Note the request itself may
	 * not be पढ़ोy to run!
	 */
	व्योम		(*schedule)(काष्ठा i915_request *request,
				    स्थिर काष्ठा i915_sched_attr *attr);

	व्योम		(*release)(काष्ठा पूर्णांकel_engine_cs *engine);

	काष्ठा पूर्णांकel_engine_execlists execlists;

	/*
	 * Keep track of completed समयlines on this engine क्रम early
	 * retirement with the goal of quickly enabling घातersaving as
	 * soon as the engine is idle.
	 */
	काष्ठा पूर्णांकel_समयline *retire;
	काष्ठा work_काष्ठा retire_work;

	/* status_notअगरier: list of callbacks क्रम context-चयन changes */
	काष्ठा atomic_notअगरier_head context_status_notअगरier;

#घोषणा I915_ENGINE_USING_CMD_PARSER BIT(0)
#घोषणा I915_ENGINE_SUPPORTS_STATS   BIT(1)
#घोषणा I915_ENGINE_HAS_PREEMPTION   BIT(2)
#घोषणा I915_ENGINE_HAS_SEMAPHORES   BIT(3)
#घोषणा I915_ENGINE_HAS_TIMESLICES   BIT(4)
#घोषणा I915_ENGINE_NEEDS_BREADCRUMB_TASKLET BIT(5)
#घोषणा I915_ENGINE_IS_VIRTUAL       BIT(6)
#घोषणा I915_ENGINE_HAS_RELATIVE_MMIO BIT(7)
#घोषणा I915_ENGINE_REQUIRES_CMD_PARSER BIT(8)
	अचिन्हित पूर्णांक flags;

	/*
	 * Table of commands the command parser needs to know about
	 * क्रम this engine.
	 */
	DECLARE_HASHTABLE(cmd_hash, I915_CMD_HASH_ORDER);

	/*
	 * Table of रेजिस्टरs allowed in commands that पढ़ो/ग_लिखो रेजिस्टरs.
	 */
	स्थिर काष्ठा drm_i915_reg_table *reg_tables;
	पूर्णांक reg_table_count;

	/*
	 * Returns the biपंचांगask क्रम the length field of the specअगरied command.
	 * Return 0 क्रम an unrecognized/invalid command.
	 *
	 * If the command parser finds an entry क्रम a command in the engine's
	 * cmd_tables, it माला_लो the command's length based on the table entry.
	 * If not, it calls this function to determine the per-engine length
	 * field encoding क्रम the command (i.e. dअगरferent opcode ranges use
	 * certain bits to encode the command length in the header).
	 */
	u32 (*get_cmd_length_mask)(u32 cmd_header);

	काष्ठा अणु
		/**
		 * @active: Number of contexts currently scheduled in.
		 */
		अचिन्हित पूर्णांक active;

		/**
		 * @lock: Lock protecting the below fields.
		 */
		seqcount_t lock;

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

		/**
		 * @rps: Utilisation at last RPS sampling.
		 */
		kसमय_प्रकार rps;
	पूर्ण stats;

	काष्ठा अणु
		अचिन्हित दीर्घ heartbeat_पूर्णांकerval_ms;
		अचिन्हित दीर्घ max_busyरुको_duration_ns;
		अचिन्हित दीर्घ preempt_समयout_ms;
		अचिन्हित दीर्घ stop_समयout_ms;
		अचिन्हित दीर्घ बारlice_duration_ms;
	पूर्ण props, शेषs;

	I915_SELFTEST_DECLARE(काष्ठा fault_attr reset_समयout);
पूर्ण;

अटल अंतरभूत bool
पूर्णांकel_engine_using_cmd_parser(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->flags & I915_ENGINE_USING_CMD_PARSER;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_requires_cmd_parser(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->flags & I915_ENGINE_REQUIRES_CMD_PARSER;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_supports_stats(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->flags & I915_ENGINE_SUPPORTS_STATS;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_has_preemption(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->flags & I915_ENGINE_HAS_PREEMPTION;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_has_semaphores(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->flags & I915_ENGINE_HAS_SEMAPHORES;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_has_बारlices(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_TIMESLICE_DURATION))
		वापस false;

	वापस engine->flags & I915_ENGINE_HAS_TIMESLICES;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_needs_bपढ़ोcrumb_tasklet(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->flags & I915_ENGINE_NEEDS_BREADCRUMB_TASKLET;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_is_भव(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस engine->flags & I915_ENGINE_IS_VIRTUAL;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_engine_has_relative_mmio(स्थिर काष्ठा पूर्णांकel_engine_cs * स्थिर engine)
अणु
	वापस engine->flags & I915_ENGINE_HAS_RELATIVE_MMIO;
पूर्ण

#घोषणा instकरोne_has_slice(dev_priv___, sseu___, slice___) \
	((IS_GEN(dev_priv___, 7) ? 1 : ((sseu___)->slice_mask)) & BIT(slice___))

#घोषणा instकरोne_has_subslice(dev_priv__, sseu__, slice__, subslice__) \
	(IS_GEN(dev_priv__, 7) ? (1 & BIT(subslice__)) : \
	 पूर्णांकel_sseu_has_subslice(sseu__, 0, subslice__))

#घोषणा क्रम_each_instकरोne_slice_subslice(dev_priv_, sseu_, slice_, subslice_) \
	क्रम ((slice_) = 0, (subslice_) = 0; (slice_) < I915_MAX_SLICES; \
	     (subslice_) = ((subslice_) + 1) % I915_MAX_SUBSLICES, \
	     (slice_) += ((subslice_) == 0)) \
		क्रम_each_अगर((instकरोne_has_slice(dev_priv_, sseu_, slice_)) && \
			    (instकरोne_has_subslice(dev_priv_, sseu_, slice_, \
						    subslice_)))
#पूर्ण_अगर /* __INTEL_ENGINE_TYPES_H__ */
