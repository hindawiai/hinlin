<शैली गुरु>
/*
 * Perक्रमmance events x86 architecture header
 *
 *  Copyright (C) 2008 Thomas Gleixner <tglx@linutronix.de>
 *  Copyright (C) 2008-2009 Red Hat, Inc., Ingo Molnar
 *  Copyright (C) 2009 Jaswinder Singh Rajput
 *  Copyright (C) 2009 Advanced Micro Devices, Inc., Robert Richter
 *  Copyright (C) 2008-2009 Red Hat, Inc., Peter Zijlstra
 *  Copyright (C) 2009 Intel Corporation, <markus.t.metzger@पूर्णांकel.com>
 *  Copyright (C) 2009 Google, Inc., Stephane Eranian
 *
 *  For licencing details see kernel-base/COPYING
 */

#समावेश <linux/perf_event.h>

#समावेश <यंत्र/पूर्णांकel_ds.h>
#समावेश <यंत्र/cpu.h>

/* To enable MSR tracing please use the generic trace poपूर्णांकs. */

/*
 *          |   NHM/WSM    |      SNB     |
 * रेजिस्टर -------------------------------
 *          |  HT  | no HT |  HT  | no HT |
 *-----------------------------------------
 * offcore  | core | core  | cpu  | core  |
 * lbr_sel  | core | core  | cpu  | core  |
 * ld_lat   | cpu  | core  | cpu  | core  |
 *-----------------------------------------
 *
 * Given that there is a small number of shared regs,
 * we can pre-allocate their slot in the per-cpu
 * per-core reg tables.
 */
क्रमागत extra_reg_type अणु
	EXTRA_REG_NONE  = -1,	/* not used */

	EXTRA_REG_RSP_0 = 0,	/* offcore_response_0 */
	EXTRA_REG_RSP_1 = 1,	/* offcore_response_1 */
	EXTRA_REG_LBR   = 2,	/* lbr_select */
	EXTRA_REG_LDLAT = 3,	/* ld_lat_threshold */
	EXTRA_REG_FE    = 4,    /* fe_* */

	EXTRA_REG_MAX		/* number of entries needed */
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक अणु
	जोड़ अणु
		अचिन्हित दीर्घ	idxmsk[BITS_TO_LONGS(X86_PMC_IDX_MAX)];
		u64		idxmsk64;
	पूर्ण;
	u64		code;
	u64		cmask;
	पूर्णांक		weight;
	पूर्णांक		overlap;
	पूर्णांक		flags;
	अचिन्हित पूर्णांक	size;
पूर्ण;

अटल अंतरभूत bool स्थिरraपूर्णांक_match(काष्ठा event_स्थिरraपूर्णांक *c, u64 ecode)
अणु
	वापस ((ecode & c->cmask) - c->code) <= (u64)c->size;
पूर्ण

/*
 * काष्ठा hw_perf_event.flags flags
 */
#घोषणा PERF_X86_EVENT_PEBS_LDLAT	0x0001 /* ld+ldlat data address sampling */
#घोषणा PERF_X86_EVENT_PEBS_ST		0x0002 /* st data address sampling */
#घोषणा PERF_X86_EVENT_PEBS_ST_HSW	0x0004 /* haswell style datala, store */
#घोषणा PERF_X86_EVENT_PEBS_LD_HSW	0x0008 /* haswell style datala, load */
#घोषणा PERF_X86_EVENT_PEBS_NA_HSW	0x0010 /* haswell style datala, unknown */
#घोषणा PERF_X86_EVENT_EXCL		0x0020 /* HT exclusivity on counter */
#घोषणा PERF_X86_EVENT_DYNAMIC		0x0040 /* dynamic alloc'd स्थिरraपूर्णांक */
#घोषणा PERF_X86_EVENT_RDPMC_ALLOWED	0x0080 /* grant rdpmc permission */
#घोषणा PERF_X86_EVENT_EXCL_ACCT	0x0100 /* accounted EXCL event */
#घोषणा PERF_X86_EVENT_AUTO_RELOAD	0x0200 /* use PEBS स्वतः-reload */
#घोषणा PERF_X86_EVENT_LARGE_PEBS	0x0400 /* use large PEBS */
#घोषणा PERF_X86_EVENT_PEBS_VIA_PT	0x0800 /* use PT buffer क्रम PEBS */
#घोषणा PERF_X86_EVENT_PAIR		0x1000 /* Large Increment per Cycle */
#घोषणा PERF_X86_EVENT_LBR_SELECT	0x2000 /* Save/Restore MSR_LBR_SELECT */
#घोषणा PERF_X86_EVENT_TOPDOWN		0x4000 /* Count Topकरोwn slots/metrics events */
#घोषणा PERF_X86_EVENT_PEBS_STLAT	0x8000 /* st+stlat data address sampling */

अटल अंतरभूत bool is_topकरोwn_count(काष्ठा perf_event *event)
अणु
	वापस event->hw.flags & PERF_X86_EVENT_TOPDOWN;
पूर्ण

अटल अंतरभूत bool is_metric_event(काष्ठा perf_event *event)
अणु
	u64 config = event->attr.config;

	वापस ((config & ARCH_PERFMON_EVENTSEL_EVENT) == 0) &&
		((config & INTEL_ARCH_EVENT_MASK) >= INTEL_TD_METRIC_RETIRING)  &&
		((config & INTEL_ARCH_EVENT_MASK) <= INTEL_TD_METRIC_MAX);
पूर्ण

अटल अंतरभूत bool is_slots_event(काष्ठा perf_event *event)
अणु
	वापस (event->attr.config & INTEL_ARCH_EVENT_MASK) == INTEL_TD_SLOTS;
पूर्ण

अटल अंतरभूत bool is_topकरोwn_event(काष्ठा perf_event *event)
अणु
	वापस is_metric_event(event) || is_slots_event(event);
पूर्ण

काष्ठा amd_nb अणु
	पूर्णांक nb_id;  /* NorthBridge id */
	पूर्णांक refcnt; /* reference count */
	काष्ठा perf_event *owners[X86_PMC_IDX_MAX];
	काष्ठा event_स्थिरraपूर्णांक event_स्थिरraपूर्णांकs[X86_PMC_IDX_MAX];
पूर्ण;

#घोषणा PEBS_COUNTER_MASK	((1ULL << MAX_PEBS_EVENTS) - 1)
#घोषणा PEBS_PMI_AFTER_EACH_RECORD BIT_ULL(60)
#घोषणा PEBS_OUTPUT_OFFSET	61
#घोषणा PEBS_OUTPUT_MASK	(3ull << PEBS_OUTPUT_OFFSET)
#घोषणा PEBS_OUTPUT_PT		(1ull << PEBS_OUTPUT_OFFSET)
#घोषणा PEBS_VIA_PT_MASK	(PEBS_OUTPUT_PT | PEBS_PMI_AFTER_EACH_RECORD)

/*
 * Flags PEBS can handle without an PMI.
 *
 * TID can only be handled by flushing at context चयन.
 * REGS_USER can be handled क्रम events limited to ring 3.
 *
 */
#घोषणा LARGE_PEBS_FLAGS \
	(PERF_SAMPLE_IP | PERF_SAMPLE_TID | PERF_SAMPLE_ADDR | \
	PERF_SAMPLE_ID | PERF_SAMPLE_CPU | PERF_SAMPLE_STREAM_ID | \
	PERF_SAMPLE_DATA_SRC | PERF_SAMPLE_IDENTIFIER | \
	PERF_SAMPLE_TRANSACTION | PERF_SAMPLE_PHYS_ADDR | \
	PERF_SAMPLE_REGS_INTR | PERF_SAMPLE_REGS_USER | \
	PERF_SAMPLE_PERIOD | PERF_SAMPLE_CODE_PAGE_SIZE)

#घोषणा PEBS_GP_REGS			\
	((1ULL << PERF_REG_X86_AX)    | \
	 (1ULL << PERF_REG_X86_BX)    | \
	 (1ULL << PERF_REG_X86_CX)    | \
	 (1ULL << PERF_REG_X86_DX)    | \
	 (1ULL << PERF_REG_X86_DI)    | \
	 (1ULL << PERF_REG_X86_SI)    | \
	 (1ULL << PERF_REG_X86_SP)    | \
	 (1ULL << PERF_REG_X86_BP)    | \
	 (1ULL << PERF_REG_X86_IP)    | \
	 (1ULL << PERF_REG_X86_FLAGS) | \
	 (1ULL << PERF_REG_X86_R8)    | \
	 (1ULL << PERF_REG_X86_R9)    | \
	 (1ULL << PERF_REG_X86_R10)   | \
	 (1ULL << PERF_REG_X86_R11)   | \
	 (1ULL << PERF_REG_X86_R12)   | \
	 (1ULL << PERF_REG_X86_R13)   | \
	 (1ULL << PERF_REG_X86_R14)   | \
	 (1ULL << PERF_REG_X86_R15))

/*
 * Per रेजिस्टर state.
 */
काष्ठा er_account अणु
	raw_spinlock_t      lock;	/* per-core: protect काष्ठाure */
	u64                 config;	/* extra MSR config */
	u64                 reg;	/* extra MSR number */
	atomic_t            ref;	/* reference count */
पूर्ण;

/*
 * Per core/cpu state
 *
 * Used to coordinate shared रेजिस्टरs between HT thपढ़ोs or
 * among events on a single PMU.
 */
काष्ठा पूर्णांकel_shared_regs अणु
	काष्ठा er_account       regs[EXTRA_REG_MAX];
	पूर्णांक                     refcnt;		/* per-core: #HT thपढ़ोs */
	अचिन्हित                core_id;	/* per-core: core id */
पूर्ण;

क्रमागत पूर्णांकel_excl_state_type अणु
	INTEL_EXCL_UNUSED    = 0, /* counter is unused */
	INTEL_EXCL_SHARED    = 1, /* counter can be used by both thपढ़ोs */
	INTEL_EXCL_EXCLUSIVE = 2, /* counter can be used by one thपढ़ो only */
पूर्ण;

काष्ठा पूर्णांकel_excl_states अणु
	क्रमागत पूर्णांकel_excl_state_type state[X86_PMC_IDX_MAX];
	bool sched_started; /* true अगर scheduling has started */
पूर्ण;

काष्ठा पूर्णांकel_excl_cntrs अणु
	raw_spinlock_t	lock;

	काष्ठा पूर्णांकel_excl_states states[2];

	जोड़ अणु
		u16	has_exclusive[2];
		u32	exclusive_present;
	पूर्ण;

	पूर्णांक		refcnt;		/* per-core: #HT thपढ़ोs */
	अचिन्हित	core_id;	/* per-core: core id */
पूर्ण;

काष्ठा x86_perf_task_context;
#घोषणा MAX_LBR_ENTRIES		32

क्रमागत अणु
	LBR_FORMAT_32		= 0x00,
	LBR_FORMAT_LIP		= 0x01,
	LBR_FORMAT_EIP		= 0x02,
	LBR_FORMAT_EIP_FLAGS	= 0x03,
	LBR_FORMAT_EIP_FLAGS2	= 0x04,
	LBR_FORMAT_INFO		= 0x05,
	LBR_FORMAT_TIME		= 0x06,
	LBR_FORMAT_MAX_KNOWN    = LBR_FORMAT_TIME,
पूर्ण;

क्रमागत अणु
	X86_PERF_KFREE_SHARED = 0,
	X86_PERF_KFREE_EXCL   = 1,
	X86_PERF_KFREE_MAX
पूर्ण;

काष्ठा cpu_hw_events अणु
	/*
	 * Generic x86 PMC bits
	 */
	काष्ठा perf_event	*events[X86_PMC_IDX_MAX]; /* in counter order */
	अचिन्हित दीर्घ		active_mask[BITS_TO_LONGS(X86_PMC_IDX_MAX)];
	पूर्णांक			enabled;

	पूर्णांक			n_events; /* the # of events in the below arrays */
	पूर्णांक			n_added;  /* the # last events in the below arrays;
					     they've never been enabled yet */
	पूर्णांक			n_txn;    /* the # last events in the below arrays;
					     added in the current transaction */
	पूर्णांक			n_txn_pair;
	पूर्णांक			n_txn_metric;
	पूर्णांक			assign[X86_PMC_IDX_MAX]; /* event to counter assignment */
	u64			tags[X86_PMC_IDX_MAX];

	काष्ठा perf_event	*event_list[X86_PMC_IDX_MAX]; /* in enabled order */
	काष्ठा event_स्थिरraपूर्णांक	*event_स्थिरraपूर्णांक[X86_PMC_IDX_MAX];

	पूर्णांक			n_excl; /* the number of exclusive events */

	अचिन्हित पूर्णांक		txn_flags;
	पूर्णांक			is_fake;

	/*
	 * Intel DebugStore bits
	 */
	काष्ठा debug_store	*ds;
	व्योम			*ds_pebs_vaddr;
	व्योम			*ds_bts_vaddr;
	u64			pebs_enabled;
	पूर्णांक			n_pebs;
	पूर्णांक			n_large_pebs;
	पूर्णांक			n_pebs_via_pt;
	पूर्णांक			pebs_output;

	/* Current super set of events hardware configuration */
	u64			pebs_data_cfg;
	u64			active_pebs_data_cfg;
	पूर्णांक			pebs_record_size;

	/*
	 * Intel LBR bits
	 */
	पूर्णांक				lbr_users;
	पूर्णांक				lbr_pebs_users;
	काष्ठा perf_branch_stack	lbr_stack;
	काष्ठा perf_branch_entry	lbr_entries[MAX_LBR_ENTRIES];
	जोड़ अणु
		काष्ठा er_account		*lbr_sel;
		काष्ठा er_account		*lbr_ctl;
	पूर्ण;
	u64				br_sel;
	व्योम				*last_task_ctx;
	पूर्णांक				last_log_id;
	पूर्णांक				lbr_select;
	व्योम				*lbr_xsave;

	/*
	 * Intel host/guest exclude bits
	 */
	u64				पूर्णांकel_ctrl_guest_mask;
	u64				पूर्णांकel_ctrl_host_mask;
	काष्ठा perf_guest_चयन_msr	guest_चयन_msrs[X86_PMC_IDX_MAX];

	/*
	 * Intel checkpoपूर्णांक mask
	 */
	u64				पूर्णांकel_cp_status;

	/*
	 * manage shared (per-core, per-cpu) रेजिस्टरs
	 * used on Intel NHM/WSM/SNB
	 */
	काष्ठा पूर्णांकel_shared_regs	*shared_regs;
	/*
	 * manage exclusive counter access between hyperthपढ़ो
	 */
	काष्ठा event_स्थिरraपूर्णांक *स्थिरraपूर्णांक_list; /* in enable order */
	काष्ठा पूर्णांकel_excl_cntrs		*excl_cntrs;
	पूर्णांक excl_thपढ़ो_id; /* 0 or 1 */

	/*
	 * SKL TSX_FORCE_ABORT shaकरोw
	 */
	u64				tfa_shaकरोw;

	/*
	 * Perf Metrics
	 */
	/* number of accepted metrics events */
	पूर्णांक				n_metric;

	/*
	 * AMD specअगरic bits
	 */
	काष्ठा amd_nb			*amd_nb;
	/* Inverted mask of bits to clear in the perf_ctr ctrl रेजिस्टरs */
	u64				perf_ctr_virt_mask;
	पूर्णांक				n_pair; /* Large increment events */

	व्योम				*kमुक्त_on_online[X86_PERF_KFREE_MAX];

	काष्ठा pmu			*pmu;
पूर्ण;

#घोषणा __EVENT_CONSTRAINT_RANGE(c, e, n, m, w, o, f) अणु	\
	अणु .idxmsk64 = (n) पूर्ण,		\
	.code = (c),			\
	.size = (e) - (c),		\
	.cmask = (m),			\
	.weight = (w),			\
	.overlap = (o),			\
	.flags = f,			\
पूर्ण

#घोषणा __EVENT_CONSTRAINT(c, n, m, w, o, f) \
	__EVENT_CONSTRAINT_RANGE(c, c, n, m, w, o, f)

#घोषणा EVENT_CONSTRAINT(c, n, m)	\
	__EVENT_CONSTRAINT(c, n, m, HWEIGHT(n), 0, 0)

/*
 * The स्थिरraपूर्णांक_match() function only works क्रम 'simple' event codes
 * and not क्रम extended (AMD64_EVENTSEL_EVENT) events codes.
 */
#घोषणा EVENT_CONSTRAINT_RANGE(c, e, n, m) \
	__EVENT_CONSTRAINT_RANGE(c, e, n, m, HWEIGHT(n), 0, 0)

#घोषणा INTEL_EXCLEVT_CONSTRAINT(c, n)	\
	__EVENT_CONSTRAINT(c, n, ARCH_PERFMON_EVENTSEL_EVENT, HWEIGHT(n),\
			   0, PERF_X86_EVENT_EXCL)

/*
 * The overlap flag marks event स्थिरraपूर्णांकs with overlapping counter
 * masks. This is the हाल अगर the counter mask of such an event is not
 * a subset of any other counter mask of a स्थिरraपूर्णांक with an equal or
 * higher weight, e.g.:
 *
 *  c_overlaps = EVENT_CONSTRAINT_OVERLAP(0, 0x09, 0);
 *  c_another1 = EVENT_CONSTRAINT(0, 0x07, 0);
 *  c_another2 = EVENT_CONSTRAINT(0, 0x38, 0);
 *
 * The event scheduler may not select the correct counter in the first
 * cycle because it needs to know which subsequent events will be
 * scheduled. It may fail to schedule the events then. So we set the
 * overlap flag क्रम such स्थिरraपूर्णांकs to give the scheduler a hपूर्णांक which
 * events to select क्रम counter rescheduling.
 *
 * Care must be taken as the rescheduling algorithm is O(n!) which
 * will increase scheduling cycles क्रम an over-committed प्रणाली
 * dramatically.  The number of such EVENT_CONSTRAINT_OVERLAP() macros
 * and its counter masks must be kept at a minimum.
 */
#घोषणा EVENT_CONSTRAINT_OVERLAP(c, n, m)	\
	__EVENT_CONSTRAINT(c, n, m, HWEIGHT(n), 1, 0)

/*
 * Constraपूर्णांक on the Event code.
 */
#घोषणा INTEL_EVENT_CONSTRAINT(c, n)	\
	EVENT_CONSTRAINT(c, n, ARCH_PERFMON_EVENTSEL_EVENT)

/*
 * Constraपूर्णांक on a range of Event codes
 */
#घोषणा INTEL_EVENT_CONSTRAINT_RANGE(c, e, n)			\
	EVENT_CONSTRAINT_RANGE(c, e, n, ARCH_PERFMON_EVENTSEL_EVENT)

/*
 * Constraपूर्णांक on the Event code + UMask + fixed-mask
 *
 * filter mask to validate fixed counter events.
 * the following filters disqualअगरy क्रम fixed counters:
 *  - inv
 *  - edge
 *  - cnt-mask
 *  - in_tx
 *  - in_tx_checkpoपूर्णांकed
 *  The other filters are supported by fixed counters.
 *  The any-thपढ़ो option is supported starting with v3.
 */
#घोषणा FIXED_EVENT_FLAGS (X86_RAW_EVENT_MASK|HSW_IN_TX|HSW_IN_TX_CHECKPOINTED)
#घोषणा FIXED_EVENT_CONSTRAINT(c, n)	\
	EVENT_CONSTRAINT(c, (1ULL << (32+n)), FIXED_EVENT_FLAGS)

/*
 * The special metric counters करो not actually exist. They are calculated from
 * the combination of the FxCtr3 + MSR_PERF_METRICS.
 *
 * The special metric counters are mapped to a dummy offset क्रम the scheduler.
 * The sharing between multiple users of the same metric without multiplexing
 * is not allowed, even though the hardware supports that in principle.
 */

#घोषणा METRIC_EVENT_CONSTRAINT(c, n)					\
	EVENT_CONSTRAINT(c, (1ULL << (INTEL_PMC_IDX_METRIC_BASE + n)),	\
			 INTEL_ARCH_EVENT_MASK)

/*
 * Constraपूर्णांक on the Event code + UMask
 */
#घोषणा INTEL_UEVENT_CONSTRAINT(c, n)	\
	EVENT_CONSTRAINT(c, n, INTEL_ARCH_EVENT_MASK)

/* Constraपूर्णांक on specअगरic umask bit only + event */
#घोषणा INTEL_UBIT_EVENT_CONSTRAINT(c, n)	\
	EVENT_CONSTRAINT(c, n, ARCH_PERFMON_EVENTSEL_EVENT|(c))

/* Like UEVENT_CONSTRAINT, but match flags too */
#घोषणा INTEL_FLAGS_UEVENT_CONSTRAINT(c, n)	\
	EVENT_CONSTRAINT(c, n, INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS)

#घोषणा INTEL_EXCLUEVT_CONSTRAINT(c, n)	\
	__EVENT_CONSTRAINT(c, n, INTEL_ARCH_EVENT_MASK, \
			   HWEIGHT(n), 0, PERF_X86_EVENT_EXCL)

#घोषणा INTEL_PLD_CONSTRAINT(c, n)	\
	__EVENT_CONSTRAINT(c, n, INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS, \
			   HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_LDLAT)

#घोषणा INTEL_PSD_CONSTRAINT(c, n)	\
	__EVENT_CONSTRAINT(c, n, INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS, \
			   HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_STLAT)

#घोषणा INTEL_PST_CONSTRAINT(c, n)	\
	__EVENT_CONSTRAINT(c, n, INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_ST)

/* Event स्थिरraपूर्णांक, but match on all event flags too. */
#घोषणा INTEL_FLAGS_EVENT_CONSTRAINT(c, n) \
	EVENT_CONSTRAINT(c, n, ARCH_PERFMON_EVENTSEL_EVENT|X86_ALL_EVENT_FLAGS)

#घोषणा INTEL_FLAGS_EVENT_CONSTRAINT_RANGE(c, e, n)			\
	EVENT_CONSTRAINT_RANGE(c, e, n, ARCH_PERFMON_EVENTSEL_EVENT|X86_ALL_EVENT_FLAGS)

/* Check only flags, but allow all event/umask */
#घोषणा INTEL_ALL_EVENT_CONSTRAINT(code, n)	\
	EVENT_CONSTRAINT(code, n, X86_ALL_EVENT_FLAGS)

/* Check flags and event code, and set the HSW store flag */
#घोषणा INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_ST(code, n) \
	__EVENT_CONSTRAINT(code, n, 			\
			  ARCH_PERFMON_EVENTSEL_EVENT|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_ST_HSW)

/* Check flags and event code, and set the HSW load flag */
#घोषणा INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD(code, n) \
	__EVENT_CONSTRAINT(code, n,			\
			  ARCH_PERFMON_EVENTSEL_EVENT|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_LD_HSW)

#घोषणा INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD_RANGE(code, end, n) \
	__EVENT_CONSTRAINT_RANGE(code, end, n,				\
			  ARCH_PERFMON_EVENTSEL_EVENT|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_LD_HSW)

#घोषणा INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_XLD(code, n) \
	__EVENT_CONSTRAINT(code, n,			\
			  ARCH_PERFMON_EVENTSEL_EVENT|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, \
			  PERF_X86_EVENT_PEBS_LD_HSW|PERF_X86_EVENT_EXCL)

/* Check flags and event code/umask, and set the HSW store flag */
#घोषणा INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(code, n) \
	__EVENT_CONSTRAINT(code, n, 			\
			  INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_ST_HSW)

#घोषणा INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XST(code, n) \
	__EVENT_CONSTRAINT(code, n,			\
			  INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, \
			  PERF_X86_EVENT_PEBS_ST_HSW|PERF_X86_EVENT_EXCL)

/* Check flags and event code/umask, and set the HSW load flag */
#घोषणा INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(code, n) \
	__EVENT_CONSTRAINT(code, n, 			\
			  INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_LD_HSW)

#घोषणा INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XLD(code, n) \
	__EVENT_CONSTRAINT(code, n,			\
			  INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, \
			  PERF_X86_EVENT_PEBS_LD_HSW|PERF_X86_EVENT_EXCL)

/* Check flags and event code/umask, and set the HSW N/A flag */
#घोषणा INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_NA(code, n) \
	__EVENT_CONSTRAINT(code, n, 			\
			  INTEL_ARCH_EVENT_MASK|X86_ALL_EVENT_FLAGS, \
			  HWEIGHT(n), 0, PERF_X86_EVENT_PEBS_NA_HSW)


/*
 * We define the end marker as having a weight of -1
 * to enable blacklisting of events using a counter biपंचांगask
 * of zero and thus a weight of zero.
 * The end marker has a weight that cannot possibly be
 * obtained from counting the bits in the biपंचांगask.
 */
#घोषणा EVENT_CONSTRAINT_END अणु .weight = -1 पूर्ण

/*
 * Check क्रम end marker with weight == -1
 */
#घोषणा क्रम_each_event_स्थिरraपूर्णांक(e, c)	\
	क्रम ((e) = (c); (e)->weight != -1; (e)++)

/*
 * Extra रेजिस्टरs क्रम specअगरic events.
 *
 * Some events need large masks and require बाह्यal MSRs.
 * Those extra MSRs end up being shared क्रम all events on
 * a PMU and someबार between PMU of sibling HT thपढ़ोs.
 * In either हाल, the kernel needs to handle conflicting
 * accesses to those extra, shared, regs. The data काष्ठाure
 * to manage those रेजिस्टरs is stored in cpu_hw_event.
 */
काष्ठा extra_reg अणु
	अचिन्हित पूर्णांक		event;
	अचिन्हित पूर्णांक		msr;
	u64			config_mask;
	u64			valid_mask;
	पूर्णांक			idx;  /* per_xxx->regs[] reg index */
	bool			extra_msr_access;
पूर्ण;

#घोषणा EVENT_EXTRA_REG(e, ms, m, vm, i) अणु	\
	.event = (e),			\
	.msr = (ms),			\
	.config_mask = (m),		\
	.valid_mask = (vm),		\
	.idx = EXTRA_REG_##i,		\
	.extra_msr_access = true,	\
	पूर्ण

#घोषणा INTEL_EVENT_EXTRA_REG(event, msr, vm, idx)	\
	EVENT_EXTRA_REG(event, msr, ARCH_PERFMON_EVENTSEL_EVENT, vm, idx)

#घोषणा INTEL_UEVENT_EXTRA_REG(event, msr, vm, idx) \
	EVENT_EXTRA_REG(event, msr, ARCH_PERFMON_EVENTSEL_EVENT | \
			ARCH_PERFMON_EVENTSEL_UMASK, vm, idx)

#घोषणा INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(c) \
	INTEL_UEVENT_EXTRA_REG(c, \
			       MSR_PEBS_LD_LAT_THRESHOLD, \
			       0xffff, \
			       LDLAT)

#घोषणा EVENT_EXTRA_END EVENT_EXTRA_REG(0, 0, 0, 0, RSP_0)

जोड़ perf_capabilities अणु
	काष्ठा अणु
		u64	lbr_क्रमmat:6;
		u64	pebs_trap:1;
		u64	pebs_arch_reg:1;
		u64	pebs_क्रमmat:4;
		u64	smm_मुक्तze:1;
		/*
		 * PMU supports separate counter range क्रम writing
		 * values > 32bit.
		 */
		u64	full_width_ग_लिखो:1;
		u64     pebs_baseline:1;
		u64	perf_metrics:1;
		u64	pebs_output_pt_available:1;
		u64	anythपढ़ो_deprecated:1;
	पूर्ण;
	u64	capabilities;
पूर्ण;

काष्ठा x86_pmu_quirk अणु
	काष्ठा x86_pmu_quirk *next;
	व्योम (*func)(व्योम);
पूर्ण;

जोड़ x86_pmu_config अणु
	काष्ठा अणु
		u64 event:8,
		    umask:8,
		    usr:1,
		    os:1,
		    edge:1,
		    pc:1,
		    पूर्णांकerrupt:1,
		    __reserved1:1,
		    en:1,
		    inv:1,
		    cmask:8,
		    event2:4,
		    __reserved2:4,
		    go:1,
		    ho:1;
	पूर्ण bits;
	u64 value;
पूर्ण;

#घोषणा X86_CONFIG(args...) ((जोड़ x86_pmu_config)अणु.bits = अणुargsपूर्णपूर्ण).value

क्रमागत अणु
	x86_lbr_exclusive_lbr,
	x86_lbr_exclusive_bts,
	x86_lbr_exclusive_pt,
	x86_lbr_exclusive_max,
पूर्ण;

काष्ठा x86_hybrid_pmu अणु
	काष्ठा pmu			pmu;
	स्थिर अक्षर			*name;
	u8				cpu_type;
	cpumask_t			supported_cpus;
	जोड़ perf_capabilities		पूर्णांकel_cap;
	u64				पूर्णांकel_ctrl;
	पूर्णांक				max_pebs_events;
	पूर्णांक				num_counters;
	पूर्णांक				num_counters_fixed;
	काष्ठा event_स्थिरraपूर्णांक		unस्थिरrained;

	u64				hw_cache_event_ids
					[PERF_COUNT_HW_CACHE_MAX]
					[PERF_COUNT_HW_CACHE_OP_MAX]
					[PERF_COUNT_HW_CACHE_RESULT_MAX];
	u64				hw_cache_extra_regs
					[PERF_COUNT_HW_CACHE_MAX]
					[PERF_COUNT_HW_CACHE_OP_MAX]
					[PERF_COUNT_HW_CACHE_RESULT_MAX];
	काष्ठा event_स्थिरraपूर्णांक		*event_स्थिरraपूर्णांकs;
	काष्ठा event_स्थिरraपूर्णांक		*pebs_स्थिरraपूर्णांकs;
	काष्ठा extra_reg		*extra_regs;
पूर्ण;

अटल __always_अंतरभूत काष्ठा x86_hybrid_pmu *hybrid_pmu(काष्ठा pmu *pmu)
अणु
	वापस container_of(pmu, काष्ठा x86_hybrid_pmu, pmu);
पूर्ण

बाह्य काष्ठा अटल_key_false perf_is_hybrid;
#घोषणा is_hybrid()		अटल_branch_unlikely(&perf_is_hybrid)

#घोषणा hybrid(_pmu, _field)				\
(*(अणु							\
	typeof(&x86_pmu._field) __Fp = &x86_pmu._field;	\
							\
	अगर (is_hybrid() && (_pmu))			\
		__Fp = &hybrid_pmu(_pmu)->_field;	\
							\
	__Fp;						\
पूर्ण))

#घोषणा hybrid_var(_pmu, _var)				\
(*(अणु							\
	typeof(&_var) __Fp = &_var;			\
							\
	अगर (is_hybrid() && (_pmu))			\
		__Fp = &hybrid_pmu(_pmu)->_var;		\
							\
	__Fp;						\
पूर्ण))

क्रमागत hybrid_pmu_type अणु
	hybrid_big		= 0x40,
	hybrid_small		= 0x20,

	hybrid_big_small	= hybrid_big | hybrid_small,
पूर्ण;

#घोषणा X86_HYBRID_PMU_ATOM_IDX		0
#घोषणा X86_HYBRID_PMU_CORE_IDX		1

#घोषणा X86_HYBRID_NUM_PMUS		2

/*
 * काष्ठा x86_pmu - generic x86 pmu
 */
काष्ठा x86_pmu अणु
	/*
	 * Generic x86 PMC bits
	 */
	स्थिर अक्षर	*name;
	पूर्णांक		version;
	पूर्णांक		(*handle_irq)(काष्ठा pt_regs *);
	व्योम		(*disable_all)(व्योम);
	व्योम		(*enable_all)(पूर्णांक added);
	व्योम		(*enable)(काष्ठा perf_event *);
	व्योम		(*disable)(काष्ठा perf_event *);
	व्योम		(*add)(काष्ठा perf_event *);
	व्योम		(*del)(काष्ठा perf_event *);
	व्योम		(*पढ़ो)(काष्ठा perf_event *event);
	पूर्णांक		(*hw_config)(काष्ठा perf_event *event);
	पूर्णांक		(*schedule_events)(काष्ठा cpu_hw_events *cpuc, पूर्णांक n, पूर्णांक *assign);
	अचिन्हित	eventsel;
	अचिन्हित	perfctr;
	पूर्णांक		(*addr_offset)(पूर्णांक index, bool eventsel);
	पूर्णांक		(*rdpmc_index)(पूर्णांक index);
	u64		(*event_map)(पूर्णांक);
	पूर्णांक		max_events;
	पूर्णांक		num_counters;
	पूर्णांक		num_counters_fixed;
	पूर्णांक		cntval_bits;
	u64		cntval_mask;
	जोड़ अणु
			अचिन्हित दीर्घ events_maskl;
			अचिन्हित दीर्घ events_mask[BITS_TO_LONGS(ARCH_PERFMON_EVENTS_COUNT)];
	पूर्ण;
	पूर्णांक		events_mask_len;
	पूर्णांक		apic;
	u64		max_period;
	काष्ठा event_स्थिरraपूर्णांक *
			(*get_event_स्थिरraपूर्णांकs)(काष्ठा cpu_hw_events *cpuc,
						 पूर्णांक idx,
						 काष्ठा perf_event *event);

	व्योम		(*put_event_स्थिरraपूर्णांकs)(काष्ठा cpu_hw_events *cpuc,
						 काष्ठा perf_event *event);

	व्योम		(*start_scheduling)(काष्ठा cpu_hw_events *cpuc);

	व्योम		(*commit_scheduling)(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx, पूर्णांक cntr);

	व्योम		(*stop_scheduling)(काष्ठा cpu_hw_events *cpuc);

	काष्ठा event_स्थिरraपूर्णांक *event_स्थिरraपूर्णांकs;
	काष्ठा x86_pmu_quirk *quirks;
	पूर्णांक		perfctr_second_ग_लिखो;
	u64		(*limit_period)(काष्ठा perf_event *event, u64 l);

	/* PMI handler bits */
	अचिन्हित पूर्णांक	late_ack		:1,
			enabled_ack		:1;
	/*
	 * sysfs attrs
	 */
	पूर्णांक		attr_rdpmc_broken;
	पूर्णांक		attr_rdpmc;
	काष्ठा attribute **क्रमmat_attrs;

	sमाप_प्रकार		(*events_sysfs_show)(अक्षर *page, u64 config);
	स्थिर काष्ठा attribute_group **attr_update;

	अचिन्हित दीर्घ	attr_मुक्तze_on_smi;

	/*
	 * CPU Hotplug hooks
	 */
	पूर्णांक		(*cpu_prepare)(पूर्णांक cpu);
	व्योम		(*cpu_starting)(पूर्णांक cpu);
	व्योम		(*cpu_dying)(पूर्णांक cpu);
	व्योम		(*cpu_dead)(पूर्णांक cpu);

	व्योम		(*check_microcode)(व्योम);
	व्योम		(*sched_task)(काष्ठा perf_event_context *ctx,
				      bool sched_in);

	/*
	 * Intel Arch Perfmon v2+
	 */
	u64			पूर्णांकel_ctrl;
	जोड़ perf_capabilities पूर्णांकel_cap;

	/*
	 * Intel DebugStore bits
	 */
	अचिन्हित पूर्णांक	bts			:1,
			bts_active		:1,
			pebs			:1,
			pebs_active		:1,
			pebs_broken		:1,
			pebs_prec_dist		:1,
			pebs_no_tlb		:1,
			pebs_no_isolation	:1,
			pebs_block		:1;
	पूर्णांक		pebs_record_size;
	पूर्णांक		pebs_buffer_size;
	पूर्णांक		max_pebs_events;
	व्योम		(*drain_pebs)(काष्ठा pt_regs *regs, काष्ठा perf_sample_data *data);
	काष्ठा event_स्थिरraपूर्णांक *pebs_स्थिरraपूर्णांकs;
	व्योम		(*pebs_aliases)(काष्ठा perf_event *event);
	अचिन्हित दीर्घ	large_pebs_flags;
	u64		rपंचांग_पात_event;

	/*
	 * Intel LBR
	 */
	अचिन्हित पूर्णांक	lbr_tos, lbr_from, lbr_to,
			lbr_info, lbr_nr;	   /* LBR base regs and size */
	जोड़ अणु
		u64	lbr_sel_mask;		   /* LBR_SELECT valid bits */
		u64	lbr_ctl_mask;		   /* LBR_CTL valid bits */
	पूर्ण;
	जोड़ अणु
		स्थिर पूर्णांक	*lbr_sel_map;	   /* lbr_select mappings */
		पूर्णांक		*lbr_ctl_map;	   /* LBR_CTL mappings */
	पूर्ण;
	bool		lbr_द्विगुन_पात;	   /* duplicated lbr पातs */
	bool		lbr_pt_coexist;		   /* (LBR|BTS) may coexist with PT */

	/*
	 * Intel Architectural LBR CPUID Enumeration
	 */
	अचिन्हित पूर्णांक	lbr_depth_mask:8;
	अचिन्हित पूर्णांक	lbr_deep_c_reset:1;
	अचिन्हित पूर्णांक	lbr_lip:1;
	अचिन्हित पूर्णांक	lbr_cpl:1;
	अचिन्हित पूर्णांक	lbr_filter:1;
	अचिन्हित पूर्णांक	lbr_call_stack:1;
	अचिन्हित पूर्णांक	lbr_mispred:1;
	अचिन्हित पूर्णांक	lbr_समयd_lbr:1;
	अचिन्हित पूर्णांक	lbr_br_type:1;

	व्योम		(*lbr_reset)(व्योम);
	व्योम		(*lbr_पढ़ो)(काष्ठा cpu_hw_events *cpuc);
	व्योम		(*lbr_save)(व्योम *ctx);
	व्योम		(*lbr_restore)(व्योम *ctx);

	/*
	 * Intel PT/LBR/BTS are exclusive
	 */
	atomic_t	lbr_exclusive[x86_lbr_exclusive_max];

	/*
	 * Intel perf metrics
	 */
	पूर्णांक		num_topकरोwn_events;
	u64		(*update_topकरोwn_event)(काष्ठा perf_event *event);
	पूर्णांक		(*set_topकरोwn_event_period)(काष्ठा perf_event *event);

	/*
	 * perf task context (i.e. काष्ठा perf_event_context::task_ctx_data)
	 * चयन helper to bridge calls from perf/core to perf/x86.
	 * See काष्ठा pmu::swap_task_ctx() usage क्रम examples;
	 */
	व्योम		(*swap_task_ctx)(काष्ठा perf_event_context *prev,
					 काष्ठा perf_event_context *next);

	/*
	 * AMD bits
	 */
	अचिन्हित पूर्णांक	amd_nb_स्थिरraपूर्णांकs : 1;
	u64		perf_ctr_pair_en;

	/*
	 * Extra रेजिस्टरs क्रम events
	 */
	काष्ठा extra_reg *extra_regs;
	अचिन्हित पूर्णांक flags;

	/*
	 * Intel host/guest support (KVM)
	 */
	काष्ठा perf_guest_चयन_msr *(*guest_get_msrs)(पूर्णांक *nr);

	/*
	 * Check period value क्रम PERF_EVENT_IOC_PERIOD ioctl.
	 */
	पूर्णांक (*check_period) (काष्ठा perf_event *event, u64 period);

	पूर्णांक (*aux_output_match) (काष्ठा perf_event *event);

	पूर्णांक (*filter_match)(काष्ठा perf_event *event);
	/*
	 * Hybrid support
	 *
	 * Most PMU capabilities are the same among dअगरferent hybrid PMUs.
	 * The global x86_pmu saves the architecture capabilities, which
	 * are available क्रम all PMUs. The hybrid_pmu only includes the
	 * unique capabilities.
	 */
	पूर्णांक				num_hybrid_pmus;
	काष्ठा x86_hybrid_pmu		*hybrid_pmu;
	u8 (*get_hybrid_cpu_type)	(व्योम);
पूर्ण;

काष्ठा x86_perf_task_context_opt अणु
	पूर्णांक lbr_callstack_users;
	पूर्णांक lbr_stack_state;
	पूर्णांक log_id;
पूर्ण;

काष्ठा x86_perf_task_context अणु
	u64 lbr_sel;
	पूर्णांक tos;
	पूर्णांक valid_lbrs;
	काष्ठा x86_perf_task_context_opt opt;
	काष्ठा lbr_entry lbr[MAX_LBR_ENTRIES];
पूर्ण;

काष्ठा x86_perf_task_context_arch_lbr अणु
	काष्ठा x86_perf_task_context_opt opt;
	काष्ठा lbr_entry entries[];
पूर्ण;

/*
 * Add padding to guarantee the 64-byte alignment of the state buffer.
 *
 * The काष्ठाure is dynamically allocated. The size of the LBR state may vary
 * based on the number of LBR रेजिस्टरs.
 *
 * Do not put anything after the LBR state.
 */
काष्ठा x86_perf_task_context_arch_lbr_xsave अणु
	काष्ठा x86_perf_task_context_opt		opt;

	जोड़ अणु
		काष्ठा xregs_state			xsave;
		काष्ठा अणु
			काष्ठा fxregs_state		i387;
			काष्ठा xstate_header		header;
			काष्ठा arch_lbr_state		lbr;
		पूर्ण __attribute__ ((packed, aligned (XSAVE_ALIGNMENT)));
	पूर्ण;
पूर्ण;

#घोषणा x86_add_quirk(func_)						\
करो अणु									\
	अटल काष्ठा x86_pmu_quirk __quirk __initdata = अणु		\
		.func = func_,						\
	पूर्ण;								\
	__quirk.next = x86_pmu.quirks;					\
	x86_pmu.quirks = &__quirk;					\
पूर्ण जबतक (0)

/*
 * x86_pmu flags
 */
#घोषणा PMU_FL_NO_HT_SHARING	0x1 /* no hyper-thपढ़ोing resource sharing */
#घोषणा PMU_FL_HAS_RSP_1	0x2 /* has 2 equivalent offcore_rsp regs   */
#घोषणा PMU_FL_EXCL_CNTRS	0x4 /* has exclusive counter requirements  */
#घोषणा PMU_FL_EXCL_ENABLED	0x8 /* exclusive counter active */
#घोषणा PMU_FL_PEBS_ALL		0x10 /* all events are valid PEBS events */
#घोषणा PMU_FL_TFA		0x20 /* deal with TSX क्रमce पात */
#घोषणा PMU_FL_PAIR		0x40 /* merge counters क्रम large incr. events */
#घोषणा PMU_FL_INSTR_LATENCY	0x80 /* Support Inकाष्ठाion Latency in PEBS Memory Info Record */
#घोषणा PMU_FL_MEM_LOADS_AUX	0x100 /* Require an auxiliary event क्रम the complete memory info */

#घोषणा EVENT_VAR(_id)  event_attr_##_id
#घोषणा EVENT_PTR(_id) &event_attr_##_id.attr.attr

#घोषणा EVENT_ATTR(_name, _id)						\
अटल काष्ठा perf_pmu_events_attr EVENT_VAR(_id) = अणु			\
	.attr		= __ATTR(_name, 0444, events_sysfs_show, शून्य),	\
	.id		= PERF_COUNT_HW_##_id,				\
	.event_str	= शून्य,						\
पूर्ण;

#घोषणा EVENT_ATTR_STR(_name, v, str)					\
अटल काष्ठा perf_pmu_events_attr event_attr_##v = अणु			\
	.attr		= __ATTR(_name, 0444, events_sysfs_show, शून्य),	\
	.id		= 0,						\
	.event_str	= str,						\
पूर्ण;

#घोषणा EVENT_ATTR_STR_HT(_name, v, noht, ht)				\
अटल काष्ठा perf_pmu_events_ht_attr event_attr_##v = अणु		\
	.attr		= __ATTR(_name, 0444, events_ht_sysfs_show, शून्य),\
	.id		= 0,						\
	.event_str_noht	= noht,						\
	.event_str_ht	= ht,						\
पूर्ण

#घोषणा EVENT_ATTR_STR_HYBRID(_name, v, str, _pmu)			\
अटल काष्ठा perf_pmu_events_hybrid_attr event_attr_##v = अणु		\
	.attr		= __ATTR(_name, 0444, events_hybrid_sysfs_show, शून्य),\
	.id		= 0,						\
	.event_str	= str,						\
	.pmu_type	= _pmu,						\
पूर्ण

#घोषणा FORMAT_HYBRID_PTR(_id) (&क्रमmat_attr_hybrid_##_id.attr.attr)

#घोषणा FORMAT_ATTR_HYBRID(_name, _pmu)					\
अटल काष्ठा perf_pmu_क्रमmat_hybrid_attr क्रमmat_attr_hybrid_##_name = अणु\
	.attr		= __ATTR_RO(_name),				\
	.pmu_type	= _pmu,						\
पूर्ण

काष्ठा pmu *x86_get_pmu(अचिन्हित पूर्णांक cpu);
बाह्य काष्ठा x86_pmu x86_pmu __पढ़ो_mostly;

अटल __always_अंतरभूत काष्ठा x86_perf_task_context_opt *task_context_opt(व्योम *ctx)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR))
		वापस &((काष्ठा x86_perf_task_context_arch_lbr *)ctx)->opt;

	वापस &((काष्ठा x86_perf_task_context *)ctx)->opt;
पूर्ण

अटल अंतरभूत bool x86_pmu_has_lbr_callstack(व्योम)
अणु
	वापस  x86_pmu.lbr_sel_map &&
		x86_pmu.lbr_sel_map[PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT] > 0;
पूर्ण

DECLARE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events);

पूर्णांक x86_perf_event_set_period(काष्ठा perf_event *event);

/*
 * Generalized hw caching related hw_event table, filled
 * in on a per model basis. A value of 0 means
 * 'not supported', -1 means 'hw_event makes no sense on
 * this CPU', any other value means the raw hw_event
 * ID.
 */

#घोषणा C(x) PERF_COUNT_HW_CACHE_##x

बाह्य u64 __पढ़ो_mostly hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX];
बाह्य u64 __पढ़ो_mostly hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX];

u64 x86_perf_event_update(काष्ठा perf_event *event);

अटल अंतरभूत अचिन्हित पूर्णांक x86_pmu_config_addr(पूर्णांक index)
अणु
	वापस x86_pmu.eventsel + (x86_pmu.addr_offset ?
				   x86_pmu.addr_offset(index, true) : index);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक x86_pmu_event_addr(पूर्णांक index)
अणु
	वापस x86_pmu.perfctr + (x86_pmu.addr_offset ?
				  x86_pmu.addr_offset(index, false) : index);
पूर्ण

अटल अंतरभूत पूर्णांक x86_pmu_rdpmc_index(पूर्णांक index)
अणु
	वापस x86_pmu.rdpmc_index ? x86_pmu.rdpmc_index(index) : index;
पूर्ण

bool check_hw_exists(काष्ठा pmu *pmu, पूर्णांक num_counters,
		     पूर्णांक num_counters_fixed);

पूर्णांक x86_add_exclusive(अचिन्हित पूर्णांक what);

व्योम x86_del_exclusive(अचिन्हित पूर्णांक what);

पूर्णांक x86_reserve_hardware(व्योम);

व्योम x86_release_hardware(व्योम);

पूर्णांक x86_pmu_max_precise(व्योम);

व्योम hw_perf_lbr_event_destroy(काष्ठा perf_event *event);

पूर्णांक x86_setup_perfctr(काष्ठा perf_event *event);

पूर्णांक x86_pmu_hw_config(काष्ठा perf_event *event);

व्योम x86_pmu_disable_all(व्योम);

अटल अंतरभूत bool is_counter_pair(काष्ठा hw_perf_event *hwc)
अणु
	वापस hwc->flags & PERF_X86_EVENT_PAIR;
पूर्ण

अटल अंतरभूत व्योम __x86_pmu_enable_event(काष्ठा hw_perf_event *hwc,
					  u64 enable_mask)
अणु
	u64 disable_mask = __this_cpu_पढ़ो(cpu_hw_events.perf_ctr_virt_mask);

	अगर (hwc->extra_reg.reg)
		wrmsrl(hwc->extra_reg.reg, hwc->extra_reg.config);

	/*
	 * Add enabled Merge event on next counter
	 * अगर large increment event being enabled on this counter
	 */
	अगर (is_counter_pair(hwc))
		wrmsrl(x86_pmu_config_addr(hwc->idx + 1), x86_pmu.perf_ctr_pair_en);

	wrmsrl(hwc->config_base, (hwc->config | enable_mask) & ~disable_mask);
पूर्ण

व्योम x86_pmu_enable_all(पूर्णांक added);

पूर्णांक perf_assign_events(काष्ठा event_स्थिरraपूर्णांक **स्थिरraपूर्णांकs, पूर्णांक n,
			पूर्णांक wmin, पूर्णांक wmax, पूर्णांक gpmax, पूर्णांक *assign);
पूर्णांक x86_schedule_events(काष्ठा cpu_hw_events *cpuc, पूर्णांक n, पूर्णांक *assign);

व्योम x86_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags);

अटल अंतरभूत व्योम x86_pmu_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	wrmsrl(hwc->config_base, hwc->config);

	अगर (is_counter_pair(hwc))
		wrmsrl(x86_pmu_config_addr(hwc->idx + 1), 0);
पूर्ण

व्योम x86_pmu_enable_event(काष्ठा perf_event *event);

पूर्णांक x86_pmu_handle_irq(काष्ठा pt_regs *regs);

व्योम x86_pmu_show_pmu_cap(पूर्णांक num_counters, पूर्णांक num_counters_fixed,
			  u64 पूर्णांकel_ctrl);

व्योम x86_pmu_update_cpu_context(काष्ठा pmu *pmu, पूर्णांक cpu);

बाह्य काष्ठा event_स्थिरraपूर्णांक emptyस्थिरraपूर्णांक;

बाह्य काष्ठा event_स्थिरraपूर्णांक unस्थिरrained;

अटल अंतरभूत bool kernel_ip(अचिन्हित दीर्घ ip)
अणु
#अगर_घोषित CONFIG_X86_32
	वापस ip > PAGE_OFFSET;
#अन्यथा
	वापस (दीर्घ)ip < 0;
#पूर्ण_अगर
पूर्ण

/*
 * Not all PMUs provide the right context inक्रमmation to place the reported IP
 * पूर्णांकo full context. Specअगरically segment रेजिस्टरs are typically not
 * supplied.
 *
 * Assuming the address is a linear address (it is क्रम IBS), we fake the CS and
 * vm86 mode using the known zero-based code segment and 'fix up' the रेजिस्टरs
 * to reflect this.
 *
 * Intel PEBS/LBR appear to typically provide the effective address, nothing
 * much we can करो about that but pray and treat it like a linear address.
 */
अटल अंतरभूत व्योम set_linear_ip(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip)
अणु
	regs->cs = kernel_ip(ip) ? __KERNEL_CS : __USER_CS;
	अगर (regs->flags & X86_VM_MASK)
		regs->flags ^= (PERF_EFLAGS_VM | X86_VM_MASK);
	regs->ip = ip;
पूर्ण

sमाप_प्रकार x86_event_sysfs_show(अक्षर *page, u64 config, u64 event);
sमाप_प्रकार पूर्णांकel_event_sysfs_show(अक्षर *page, u64 config);

sमाप_प्रकार events_sysfs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *page);
sमाप_प्रकार events_ht_sysfs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *page);
sमाप_प्रकार events_hybrid_sysfs_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *page);

अटल अंतरभूत bool fixed_counter_disabled(पूर्णांक i, काष्ठा pmu *pmu)
अणु
	u64 पूर्णांकel_ctrl = hybrid(pmu, पूर्णांकel_ctrl);

	वापस !(पूर्णांकel_ctrl >> (i + INTEL_PMC_IDX_FIXED));
पूर्ण

#अगर_घोषित CONFIG_CPU_SUP_AMD

पूर्णांक amd_pmu_init(व्योम);

#अन्यथा /* CONFIG_CPU_SUP_AMD */

अटल अंतरभूत पूर्णांक amd_pmu_init(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_CPU_SUP_AMD */

अटल अंतरभूत पूर्णांक is_pebs_pt(काष्ठा perf_event *event)
अणु
	वापस !!(event->hw.flags & PERF_X86_EVENT_PEBS_VIA_PT);
पूर्ण

#अगर_घोषित CONFIG_CPU_SUP_INTEL

अटल अंतरभूत bool पूर्णांकel_pmu_has_bts_period(काष्ठा perf_event *event, u64 period)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	अचिन्हित पूर्णांक hw_event, bts_event;

	अगर (event->attr.freq)
		वापस false;

	hw_event = hwc->config & INTEL_ARCH_EVENT_MASK;
	bts_event = x86_pmu.event_map(PERF_COUNT_HW_BRANCH_INSTRUCTIONS);

	वापस hw_event == bts_event && period == 1;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pmu_has_bts(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	वापस पूर्णांकel_pmu_has_bts_period(event, hwc->sample_period);
पूर्ण

पूर्णांक पूर्णांकel_pmu_save_and_restart(काष्ठा perf_event *event);

काष्ठा event_स्थिरraपूर्णांक *
x86_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event);

बाह्य पूर्णांक पूर्णांकel_cpuc_prepare(काष्ठा cpu_hw_events *cpuc, पूर्णांक cpu);
बाह्य व्योम पूर्णांकel_cpuc_finish(काष्ठा cpu_hw_events *cpuc);

पूर्णांक पूर्णांकel_pmu_init(व्योम);

व्योम init_debug_store_on_cpu(पूर्णांक cpu);

व्योम fini_debug_store_on_cpu(पूर्णांक cpu);

व्योम release_ds_buffers(व्योम);

व्योम reserve_ds_buffers(व्योम);

व्योम release_lbr_buffers(व्योम);

व्योम reserve_lbr_buffers(व्योम);

बाह्य काष्ठा event_स्थिरraपूर्णांक bts_स्थिरraपूर्णांक;
बाह्य काष्ठा event_स्थिरraपूर्णांक vlbr_स्थिरraपूर्णांक;

व्योम पूर्णांकel_pmu_enable_bts(u64 config);

व्योम पूर्णांकel_pmu_disable_bts(व्योम);

पूर्णांक पूर्णांकel_pmu_drain_bts_buffer(व्योम);

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_core2_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_atom_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_slm_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_glm_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_glp_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_grt_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_nehalem_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_wesपंचांगere_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_snb_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_ivb_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_hsw_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_bdw_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_skl_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_icl_pebs_event_स्थिरraपूर्णांकs[];

बाह्य काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_spr_pebs_event_स्थिरraपूर्णांकs[];

काष्ठा event_स्थिरraपूर्णांक *पूर्णांकel_pebs_स्थिरraपूर्णांकs(काष्ठा perf_event *event);

व्योम पूर्णांकel_pmu_pebs_add(काष्ठा perf_event *event);

व्योम पूर्णांकel_pmu_pebs_del(काष्ठा perf_event *event);

व्योम पूर्णांकel_pmu_pebs_enable(काष्ठा perf_event *event);

व्योम पूर्णांकel_pmu_pebs_disable(काष्ठा perf_event *event);

व्योम पूर्णांकel_pmu_pebs_enable_all(व्योम);

व्योम पूर्णांकel_pmu_pebs_disable_all(व्योम);

व्योम पूर्णांकel_pmu_pebs_sched_task(काष्ठा perf_event_context *ctx, bool sched_in);

व्योम पूर्णांकel_pmu_स्वतः_reload_पढ़ो(काष्ठा perf_event *event);

व्योम पूर्णांकel_pmu_store_pebs_lbrs(काष्ठा lbr_entry *lbr);

व्योम पूर्णांकel_ds_init(व्योम);

व्योम पूर्णांकel_pmu_lbr_swap_task_ctx(काष्ठा perf_event_context *prev,
				 काष्ठा perf_event_context *next);

व्योम पूर्णांकel_pmu_lbr_sched_task(काष्ठा perf_event_context *ctx, bool sched_in);

u64 lbr_from_signext_quirk_wr(u64 val);

व्योम पूर्णांकel_pmu_lbr_reset(व्योम);

व्योम पूर्णांकel_pmu_lbr_reset_32(व्योम);

व्योम पूर्णांकel_pmu_lbr_reset_64(व्योम);

व्योम पूर्णांकel_pmu_lbr_add(काष्ठा perf_event *event);

व्योम पूर्णांकel_pmu_lbr_del(काष्ठा perf_event *event);

व्योम पूर्णांकel_pmu_lbr_enable_all(bool pmi);

व्योम पूर्णांकel_pmu_lbr_disable_all(व्योम);

व्योम पूर्णांकel_pmu_lbr_पढ़ो(व्योम);

व्योम पूर्णांकel_pmu_lbr_पढ़ो_32(काष्ठा cpu_hw_events *cpuc);

व्योम पूर्णांकel_pmu_lbr_पढ़ो_64(काष्ठा cpu_hw_events *cpuc);

व्योम पूर्णांकel_pmu_lbr_save(व्योम *ctx);

व्योम पूर्णांकel_pmu_lbr_restore(व्योम *ctx);

व्योम पूर्णांकel_pmu_lbr_init_core(व्योम);

व्योम पूर्णांकel_pmu_lbr_init_nhm(व्योम);

व्योम पूर्णांकel_pmu_lbr_init_atom(व्योम);

व्योम पूर्णांकel_pmu_lbr_init_slm(व्योम);

व्योम पूर्णांकel_pmu_lbr_init_snb(व्योम);

व्योम पूर्णांकel_pmu_lbr_init_hsw(व्योम);

व्योम पूर्णांकel_pmu_lbr_init_skl(व्योम);

व्योम पूर्णांकel_pmu_lbr_init_knl(व्योम);

व्योम पूर्णांकel_pmu_arch_lbr_init(व्योम);

व्योम पूर्णांकel_pmu_pebs_data_source_nhm(व्योम);

व्योम पूर्णांकel_pmu_pebs_data_source_skl(bool pmem);

पूर्णांक पूर्णांकel_pmu_setup_lbr_filter(काष्ठा perf_event *event);

व्योम पूर्णांकel_pt_पूर्णांकerrupt(व्योम);

पूर्णांक पूर्णांकel_bts_पूर्णांकerrupt(व्योम);

व्योम पूर्णांकel_bts_enable_local(व्योम);

व्योम पूर्णांकel_bts_disable_local(व्योम);

पूर्णांक p4_pmu_init(व्योम);

पूर्णांक p6_pmu_init(व्योम);

पूर्णांक knc_pmu_init(व्योम);

अटल अंतरभूत पूर्णांक is_ht_workaround_enabled(व्योम)
अणु
	वापस !!(x86_pmu.flags & PMU_FL_EXCL_ENABLED);
पूर्ण

#अन्यथा /* CONFIG_CPU_SUP_INTEL */

अटल अंतरभूत व्योम reserve_ds_buffers(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम release_ds_buffers(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम release_lbr_buffers(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम reserve_lbr_buffers(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_pmu_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_cpuc_prepare(काष्ठा cpu_hw_events *cpuc, पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_cpuc_finish(काष्ठा cpu_hw_events *cpuc)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक is_ht_workaround_enabled(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_SUP_INTEL */

#अगर ((defined CONFIG_CPU_SUP_CENTAUR) || (defined CONFIG_CPU_SUP_ZHAOXIN))
पूर्णांक zhaoxin_pmu_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक zhaoxin_pmu_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /*CONFIG_CPU_SUP_CENTAUR or CONFIG_CPU_SUP_ZHAOXIN*/
