<शैली गुरु>
/*
 * Perक्रमmance events:
 *
 *    Copyright (C) 2008-2009, Thomas Gleixner <tglx@linutronix.de>
 *    Copyright (C) 2008-2011, Red Hat, Inc., Ingo Molnar
 *    Copyright (C) 2008-2011, Red Hat, Inc., Peter Zijlstra
 *
 * Data type definitions, declarations, prototypes.
 *
 *    Started by: Thomas Gleixner and Ingo Molnar
 *
 * For licencing details see kernel-base/COPYING
 */
#अगर_अघोषित _LINUX_PERF_EVENT_H
#घोषणा _LINUX_PERF_EVENT_H

#समावेश <uapi/linux/perf_event.h>
#समावेश <uapi/linux/bpf_perf_event.h>

/*
 * Kernel-पूर्णांकernal data types and definitions:
 */

#अगर_घोषित CONFIG_PERF_EVENTS
# include <यंत्र/perf_event.h>
# include <यंत्र/local64.h>
#पूर्ण_अगर

काष्ठा perf_guest_info_callbacks अणु
	पूर्णांक				(*is_in_guest)(व्योम);
	पूर्णांक				(*is_user_mode)(व्योम);
	अचिन्हित दीर्घ			(*get_guest_ip)(व्योम);
	व्योम				(*handle_पूर्णांकel_pt_पूर्णांकr)(व्योम);
पूर्ण;

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#पूर्ण_अगर

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/fs.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/jump_label_ratelimit.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/perf_regs.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/refcount.h>
#समावेश <linux/security.h>
#समावेश <यंत्र/local.h>

काष्ठा perf_callchain_entry अणु
	__u64				nr;
	__u64				ip[]; /* /proc/sys/kernel/perf_event_max_stack */
पूर्ण;

काष्ठा perf_callchain_entry_ctx अणु
	काष्ठा perf_callchain_entry *entry;
	u32			    max_stack;
	u32			    nr;
	लघु			    contexts;
	bool			    contexts_maxed;
पूर्ण;

प्रकार अचिन्हित दीर्घ (*perf_copy_f)(व्योम *dst, स्थिर व्योम *src,
				     अचिन्हित दीर्घ off, अचिन्हित दीर्घ len);

काष्ठा perf_raw_frag अणु
	जोड़ अणु
		काष्ठा perf_raw_frag	*next;
		अचिन्हित दीर्घ		pad;
	पूर्ण;
	perf_copy_f			copy;
	व्योम				*data;
	u32				size;
पूर्ण __packed;

काष्ठा perf_raw_record अणु
	काष्ठा perf_raw_frag		frag;
	u32				size;
पूर्ण;

/*
 * branch stack layout:
 *  nr: number of taken branches stored in entries[]
 *  hw_idx: The low level index of raw branch records
 *          क्रम the most recent branch.
 *          -1ULL means invalid/unknown.
 *
 * Note that nr can vary from sample to sample
 * branches (to, from) are stored from most recent
 * to least recent, i.e., entries[0] contains the most
 * recent branch.
 * The entries[] is an असलtraction of raw branch records,
 * which may not be stored in age order in HW, e.g. Intel LBR.
 * The hw_idx is to expose the low level index of raw
 * branch record क्रम the most recent branch aka entries[0].
 * The hw_idx index is between -1 (unknown) and max depth,
 * which can be retrieved in /sys/devices/cpu/caps/branches.
 * For the architectures whose raw branch records are
 * alपढ़ोy stored in age order, the hw_idx should be 0.
 */
काष्ठा perf_branch_stack अणु
	__u64				nr;
	__u64				hw_idx;
	काष्ठा perf_branch_entry	entries[];
पूर्ण;

काष्ठा task_काष्ठा;

/*
 * extra PMU रेजिस्टर associated with an event
 */
काष्ठा hw_perf_event_extra अणु
	u64		config;	/* रेजिस्टर value */
	अचिन्हित पूर्णांक	reg;	/* रेजिस्टर address or index */
	पूर्णांक		alloc;	/* extra रेजिस्टर alपढ़ोy allocated */
	पूर्णांक		idx;	/* index in shared_regs->regs[] */
पूर्ण;

/**
 * काष्ठा hw_perf_event - perक्रमmance event hardware details:
 */
काष्ठा hw_perf_event अणु
#अगर_घोषित CONFIG_PERF_EVENTS
	जोड़ अणु
		काष्ठा अणु /* hardware */
			u64		config;
			u64		last_tag;
			अचिन्हित दीर्घ	config_base;
			अचिन्हित दीर्घ	event_base;
			पूर्णांक		event_base_rdpmc;
			पूर्णांक		idx;
			पूर्णांक		last_cpu;
			पूर्णांक		flags;

			काष्ठा hw_perf_event_extra extra_reg;
			काष्ठा hw_perf_event_extra branch_reg;
		पूर्ण;
		काष्ठा अणु /* software */
			काष्ठा hrसमयr	hrसमयr;
		पूर्ण;
		काष्ठा अणु /* tracepoपूर्णांक */
			/* क्रम tp_event->class */
			काष्ठा list_head	tp_list;
		पूर्ण;
		काष्ठा अणु /* amd_घातer */
			u64	pwr_acc;
			u64	ptsc;
		पूर्ण;
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
		काष्ठा अणु /* अवरोधpoपूर्णांक */
			/*
			 * Crufty hack to aव्योम the chicken and egg
			 * problem hw_अवरोधpoपूर्णांक has with context
			 * creation and event initalization.
			 */
			काष्ठा arch_hw_अवरोधpoपूर्णांक	info;
			काष्ठा list_head		bp_list;
		पूर्ण;
#पूर्ण_अगर
		काष्ठा अणु /* amd_iommu */
			u8	iommu_bank;
			u8	iommu_cntr;
			u16	padding;
			u64	conf;
			u64	conf1;
		पूर्ण;
	पूर्ण;
	/*
	 * If the event is a per task event, this will poपूर्णांक to the task in
	 * question. See the comment in perf_event_alloc().
	 */
	काष्ठा task_काष्ठा		*target;

	/*
	 * PMU would store hardware filter configuration
	 * here.
	 */
	व्योम				*addr_filters;

	/* Last sync'ed generation of filters */
	अचिन्हित दीर्घ			addr_filters_gen;

/*
 * hw_perf_event::state flags; used to track the PERF_EF_* state.
 */
#घोषणा PERF_HES_STOPPED	0x01 /* the counter is stopped */
#घोषणा PERF_HES_UPTODATE	0x02 /* event->count up-to-date */
#घोषणा PERF_HES_ARCH		0x04

	पूर्णांक				state;

	/*
	 * The last observed hardware counter value, updated with a
	 * local64_cmpxchg() such that pmu::पढ़ो() can be called nested.
	 */
	local64_t			prev_count;

	/*
	 * The period to start the next sample with.
	 */
	u64				sample_period;

	जोड़ अणु
		काष्ठा अणु /* Sampling */
			/*
			 * The period we started this sample with.
			 */
			u64				last_period;

			/*
			 * However much is left of the current period;
			 * note that this is a full 64bit value and
			 * allows क्रम generation of periods दीर्घer
			 * than hardware might allow.
			 */
			local64_t			period_left;
		पूर्ण;
		काष्ठा अणु /* Topकरोwn events counting क्रम context चयन */
			u64				saved_metric;
			u64				saved_slots;
		पूर्ण;
	पूर्ण;

	/*
	 * State क्रम throttling the event, see __perf_event_overflow() and
	 * perf_adjust_freq_unthr_context().
	 */
	u64                             पूर्णांकerrupts_seq;
	u64				पूर्णांकerrupts;

	/*
	 * State क्रम freq target events, see __perf_event_overflow() and
	 * perf_adjust_freq_unthr_context().
	 */
	u64				freq_समय_stamp;
	u64				freq_count_stamp;
#पूर्ण_अगर
पूर्ण;

काष्ठा perf_event;

/*
 * Common implementation detail of pmu::अणुstart,commit,cancelपूर्ण_txn
 */
#घोषणा PERF_PMU_TXN_ADD  0x1		/* txn to add/schedule event on PMU */
#घोषणा PERF_PMU_TXN_READ 0x2		/* txn to पढ़ो event group from PMU */

/**
 * pmu::capabilities flags
 */
#घोषणा PERF_PMU_CAP_NO_INTERRUPT		0x0001
#घोषणा PERF_PMU_CAP_NO_NMI			0x0002
#घोषणा PERF_PMU_CAP_AUX_NO_SG			0x0004
#घोषणा PERF_PMU_CAP_EXTENDED_REGS		0x0008
#घोषणा PERF_PMU_CAP_EXCLUSIVE			0x0010
#घोषणा PERF_PMU_CAP_ITRACE			0x0020
#घोषणा PERF_PMU_CAP_HETEROGENEOUS_CPUS		0x0040
#घोषणा PERF_PMU_CAP_NO_EXCLUDE			0x0080
#घोषणा PERF_PMU_CAP_AUX_OUTPUT			0x0100
#घोषणा PERF_PMU_CAP_EXTENDED_HW_TYPE		0x0200

काष्ठा perf_output_handle;

/**
 * काष्ठा pmu - generic perक्रमmance monitoring unit
 */
काष्ठा pmu अणु
	काष्ठा list_head		entry;

	काष्ठा module			*module;
	काष्ठा device			*dev;
	स्थिर काष्ठा attribute_group	**attr_groups;
	स्थिर काष्ठा attribute_group	**attr_update;
	स्थिर अक्षर			*name;
	पूर्णांक				type;

	/*
	 * various common per-pmu feature flags
	 */
	पूर्णांक				capabilities;

	पूर्णांक __percpu			*pmu_disable_count;
	काष्ठा perf_cpu_context __percpu *pmu_cpu_context;
	atomic_t			exclusive_cnt; /* < 0: cpu; > 0: tsk */
	पूर्णांक				task_ctx_nr;
	पूर्णांक				hrसमयr_पूर्णांकerval_ms;

	/* number of address filters this PMU can करो */
	अचिन्हित पूर्णांक			nr_addr_filters;

	/*
	 * Fully disable/enable this PMU, can be used to protect from the PMI
	 * as well as क्रम lazy/batch writing of the MSRs.
	 */
	व्योम (*pmu_enable)		(काष्ठा pmu *pmu); /* optional */
	व्योम (*pmu_disable)		(काष्ठा pmu *pmu); /* optional */

	/*
	 * Try and initialize the event क्रम this PMU.
	 *
	 * Returns:
	 *  -ENOENT	-- @event is not क्रम this PMU
	 *
	 *  -ENODEV	-- @event is क्रम this PMU but PMU not present
	 *  -EBUSY	-- @event is क्रम this PMU but PMU temporarily unavailable
	 *  -EINVAL	-- @event is क्रम this PMU but @event is not valid
	 *  -EOPNOTSUPP -- @event is क्रम this PMU, @event is valid, but not supported
	 *  -EACCES	-- @event is क्रम this PMU, @event is valid, but no privileges
	 *
	 *  0		-- @event is क्रम this PMU and valid
	 *
	 * Other error वापस values are allowed.
	 */
	पूर्णांक (*event_init)		(काष्ठा perf_event *event);

	/*
	 * Notअगरication that the event was mapped or unmapped.  Called
	 * in the context of the mapping task.
	 */
	व्योम (*event_mapped)		(काष्ठा perf_event *event, काष्ठा mm_काष्ठा *mm); /* optional */
	व्योम (*event_unmapped)		(काष्ठा perf_event *event, काष्ठा mm_काष्ठा *mm); /* optional */

	/*
	 * Flags क्रम ->add()/->del()/ ->start()/->stop(). There are
	 * matching hw_perf_event::state flags.
	 */
#घोषणा PERF_EF_START	0x01		/* start the counter when adding    */
#घोषणा PERF_EF_RELOAD	0x02		/* reload the counter when starting */
#घोषणा PERF_EF_UPDATE	0x04		/* update the counter when stopping */

	/*
	 * Adds/Removes a counter to/from the PMU, can be करोne inside a
	 * transaction, see the ->*_txn() methods.
	 *
	 * The add/del callbacks will reserve all hardware resources required
	 * to service the event, this includes any counter स्थिरraपूर्णांक
	 * scheduling etc.
	 *
	 * Called with IRQs disabled and the PMU disabled on the CPU the event
	 * is on.
	 *
	 * ->add() called without PERF_EF_START should result in the same state
	 *  as ->add() followed by ->stop().
	 *
	 * ->del() must always PERF_EF_UPDATE stop an event. If it calls
	 *  ->stop() that must deal with alपढ़ोy being stopped without
	 *  PERF_EF_UPDATE.
	 */
	पूर्णांक  (*add)			(काष्ठा perf_event *event, पूर्णांक flags);
	व्योम (*del)			(काष्ठा perf_event *event, पूर्णांक flags);

	/*
	 * Starts/Stops a counter present on the PMU.
	 *
	 * The PMI handler should stop the counter when perf_event_overflow()
	 * वापसs !0. ->start() will be used to जारी.
	 *
	 * Also used to change the sample period.
	 *
	 * Called with IRQs disabled and the PMU disabled on the CPU the event
	 * is on -- will be called from NMI context with the PMU generates
	 * NMIs.
	 *
	 * ->stop() with PERF_EF_UPDATE will पढ़ो the counter and update
	 *  period/count values like ->पढ़ो() would.
	 *
	 * ->start() with PERF_EF_RELOAD will reprogram the counter
	 *  value, must be preceded by a ->stop() with PERF_EF_UPDATE.
	 */
	व्योम (*start)			(काष्ठा perf_event *event, पूर्णांक flags);
	व्योम (*stop)			(काष्ठा perf_event *event, पूर्णांक flags);

	/*
	 * Updates the counter value of the event.
	 *
	 * For sampling capable PMUs this will also update the software period
	 * hw_perf_event::period_left field.
	 */
	व्योम (*पढ़ो)			(काष्ठा perf_event *event);

	/*
	 * Group events scheduling is treated as a transaction, add
	 * group events as a whole and perक्रमm one schedulability test.
	 * If the test fails, roll back the whole group
	 *
	 * Start the transaction, after this ->add() करोesn't need to
	 * करो schedulability tests.
	 *
	 * Optional.
	 */
	व्योम (*start_txn)		(काष्ठा pmu *pmu, अचिन्हित पूर्णांक txn_flags);
	/*
	 * If ->start_txn() disabled the ->add() schedulability test
	 * then ->commit_txn() is required to perक्रमm one. On success
	 * the transaction is बंदd. On error the transaction is kept
	 * खोलो until ->cancel_txn() is called.
	 *
	 * Optional.
	 */
	पूर्णांक  (*commit_txn)		(काष्ठा pmu *pmu);
	/*
	 * Will cancel the transaction, assumes ->del() is called
	 * क्रम each successful ->add() during the transaction.
	 *
	 * Optional.
	 */
	व्योम (*cancel_txn)		(काष्ठा pmu *pmu);

	/*
	 * Will वापस the value क्रम perf_event_mmap_page::index क्रम this event,
	 * अगर no implementation is provided it will शेष to: event->hw.idx + 1.
	 */
	पूर्णांक (*event_idx)		(काष्ठा perf_event *event); /*optional */

	/*
	 * context-चयनes callback
	 */
	व्योम (*sched_task)		(काष्ठा perf_event_context *ctx,
					bool sched_in);

	/*
	 * Kmem cache of PMU specअगरic data
	 */
	काष्ठा kmem_cache		*task_ctx_cache;

	/*
	 * PMU specअगरic parts of task perf event context (i.e. ctx->task_ctx_data)
	 * can be synchronized using this function. See Intel LBR callstack support
	 * implementation and Perf core context चयन handling callbacks क्रम usage
	 * examples.
	 */
	व्योम (*swap_task_ctx)		(काष्ठा perf_event_context *prev,
					 काष्ठा perf_event_context *next);
					/* optional */

	/*
	 * Set up pmu-निजी data काष्ठाures क्रम an AUX area
	 */
	व्योम *(*setup_aux)		(काष्ठा perf_event *event, व्योम **pages,
					 पूर्णांक nr_pages, bool overग_लिखो);
					/* optional */

	/*
	 * Free pmu-निजी AUX data काष्ठाures
	 */
	व्योम (*मुक्त_aux)		(व्योम *aux); /* optional */

	/*
	 * Take a snapshot of the AUX buffer without touching the event
	 * state, so that preempting ->start()/->stop() callbacks करोes
	 * not पूर्णांकerfere with their logic. Called in PMI context.
	 *
	 * Returns the size of AUX data copied to the output handle.
	 *
	 * Optional.
	 */
	दीर्घ (*snapshot_aux)		(काष्ठा perf_event *event,
					 काष्ठा perf_output_handle *handle,
					 अचिन्हित दीर्घ size);

	/*
	 * Validate address range filters: make sure the HW supports the
	 * requested configuration and number of filters; वापस 0 अगर the
	 * supplied filters are valid, -त्रुटि_सं otherwise.
	 *
	 * Runs in the context of the ioctl()ing process and is not serialized
	 * with the rest of the PMU callbacks.
	 */
	पूर्णांक (*addr_filters_validate)	(काष्ठा list_head *filters);
					/* optional */

	/*
	 * Synchronize address range filter configuration:
	 * translate hw-agnostic filters पूर्णांकo hardware configuration in
	 * event::hw::addr_filters.
	 *
	 * Runs as a part of filter sync sequence that is करोne in ->start()
	 * callback by calling perf_event_addr_filters_sync().
	 *
	 * May (and should) traverse event::addr_filters::list, क्रम which its
	 * caller provides necessary serialization.
	 */
	व्योम (*addr_filters_sync)	(काष्ठा perf_event *event);
					/* optional */

	/*
	 * Check अगर event can be used क्रम aux_output purposes क्रम
	 * events of this PMU.
	 *
	 * Runs from perf_event_खोलो(). Should वापस 0 क्रम "no match"
	 * or non-zero क्रम "match".
	 */
	पूर्णांक (*aux_output_match)		(काष्ठा perf_event *event);
					/* optional */

	/*
	 * Filter events क्रम PMU-specअगरic reasons.
	 */
	पूर्णांक (*filter_match)		(काष्ठा perf_event *event); /* optional */

	/*
	 * Check period value क्रम PERF_EVENT_IOC_PERIOD ioctl.
	 */
	पूर्णांक (*check_period)		(काष्ठा perf_event *event, u64 value); /* optional */
पूर्ण;

क्रमागत perf_addr_filter_action_t अणु
	PERF_ADDR_FILTER_ACTION_STOP = 0,
	PERF_ADDR_FILTER_ACTION_START,
	PERF_ADDR_FILTER_ACTION_FILTER,
पूर्ण;

/**
 * काष्ठा perf_addr_filter - address range filter definition
 * @entry:	event's filter list linkage
 * @path:	object file's path क्रम file-based filters
 * @offset:	filter range offset
 * @size:	filter range size (size==0 means single address trigger)
 * @action:	filter/start/stop
 *
 * This is a hardware-agnostic filter configuration as specअगरied by the user.
 */
काष्ठा perf_addr_filter अणु
	काष्ठा list_head	entry;
	काष्ठा path		path;
	अचिन्हित दीर्घ		offset;
	अचिन्हित दीर्घ		size;
	क्रमागत perf_addr_filter_action_t	action;
पूर्ण;

/**
 * काष्ठा perf_addr_filters_head - container क्रम address range filters
 * @list:	list of filters क्रम this event
 * @lock:	spinlock that serializes accesses to the @list and event's
 *		(and its children's) filter generations.
 * @nr_file_filters:	number of file-based filters
 *
 * A child event will use parent's @list (and thereक्रमe @lock), so they are
 * bundled together; see perf_event_addr_filters().
 */
काष्ठा perf_addr_filters_head अणु
	काष्ठा list_head	list;
	raw_spinlock_t		lock;
	अचिन्हित पूर्णांक		nr_file_filters;
पूर्ण;

काष्ठा perf_addr_filter_range अणु
	अचिन्हित दीर्घ		start;
	अचिन्हित दीर्घ		size;
पूर्ण;

/**
 * क्रमागत perf_event_state - the states of an event:
 */
क्रमागत perf_event_state अणु
	PERF_EVENT_STATE_DEAD		= -4,
	PERF_EVENT_STATE_EXIT		= -3,
	PERF_EVENT_STATE_ERROR		= -2,
	PERF_EVENT_STATE_OFF		= -1,
	PERF_EVENT_STATE_INACTIVE	=  0,
	PERF_EVENT_STATE_ACTIVE		=  1,
पूर्ण;

काष्ठा file;
काष्ठा perf_sample_data;

प्रकार व्योम (*perf_overflow_handler_t)(काष्ठा perf_event *,
					काष्ठा perf_sample_data *,
					काष्ठा pt_regs *regs);

/*
 * Event capabilities. For event_caps and groups caps.
 *
 * PERF_EV_CAP_SOFTWARE: Is a software event.
 * PERF_EV_CAP_READ_ACTIVE_PKG: A CPU event (or cgroup event) that can be पढ़ो
 * from any CPU in the package where it is active.
 * PERF_EV_CAP_SIBLING: An event with this flag must be a group sibling and
 * cannot be a group leader. If an event with this flag is detached from the
 * group it is scheduled out and moved पूर्णांकo an unrecoverable ERROR state.
 */
#घोषणा PERF_EV_CAP_SOFTWARE		BIT(0)
#घोषणा PERF_EV_CAP_READ_ACTIVE_PKG	BIT(1)
#घोषणा PERF_EV_CAP_SIBLING		BIT(2)

#घोषणा SWEVENT_HLIST_BITS		8
#घोषणा SWEVENT_HLIST_SIZE		(1 << SWEVENT_HLIST_BITS)

काष्ठा swevent_hlist अणु
	काष्ठा hlist_head		heads[SWEVENT_HLIST_SIZE];
	काष्ठा rcu_head			rcu_head;
पूर्ण;

#घोषणा PERF_ATTACH_CONTEXT	0x01
#घोषणा PERF_ATTACH_GROUP	0x02
#घोषणा PERF_ATTACH_TASK	0x04
#घोषणा PERF_ATTACH_TASK_DATA	0x08
#घोषणा PERF_ATTACH_ITRACE	0x10
#घोषणा PERF_ATTACH_SCHED_CB	0x20
#घोषणा PERF_ATTACH_CHILD	0x40

काष्ठा perf_cgroup;
काष्ठा perf_buffer;

काष्ठा pmu_event_list अणु
	raw_spinlock_t		lock;
	काष्ठा list_head	list;
पूर्ण;

#घोषणा क्रम_each_sibling_event(sibling, event)			\
	अगर ((event)->group_leader == (event))			\
		list_क्रम_each_entry((sibling), &(event)->sibling_list, sibling_list)

/**
 * काष्ठा perf_event - perक्रमmance event kernel representation:
 */
काष्ठा perf_event अणु
#अगर_घोषित CONFIG_PERF_EVENTS
	/*
	 * entry onto perf_event_context::event_list;
	 *   modअगरications require ctx->lock
	 *   RCU safe iterations.
	 */
	काष्ठा list_head		event_entry;

	/*
	 * Locked क्रम modअगरication by both ctx->mutex and ctx->lock; holding
	 * either sufficies क्रम पढ़ो.
	 */
	काष्ठा list_head		sibling_list;
	काष्ठा list_head		active_list;
	/*
	 * Node on the pinned or flexible tree located at the event context;
	 */
	काष्ठा rb_node			group_node;
	u64				group_index;
	/*
	 * We need storage to track the entries in perf_pmu_migrate_context; we
	 * cannot use the event_entry because of RCU and we want to keep the
	 * group in tact which aव्योमs us using the other two entries.
	 */
	काष्ठा list_head		migrate_entry;

	काष्ठा hlist_node		hlist_entry;
	काष्ठा list_head		active_entry;
	पूर्णांक				nr_siblings;

	/* Not serialized. Only written during event initialization. */
	पूर्णांक				event_caps;
	/* The cumulative AND of all event_caps क्रम events in this group. */
	पूर्णांक				group_caps;

	काष्ठा perf_event		*group_leader;
	काष्ठा pmu			*pmu;
	व्योम				*pmu_निजी;

	क्रमागत perf_event_state		state;
	अचिन्हित पूर्णांक			attach_state;
	local64_t			count;
	atomic64_t			child_count;

	/*
	 * These are the total समय in nanoseconds that the event
	 * has been enabled (i.e. eligible to run, and the task has
	 * been scheduled in, अगर this is a per-task event)
	 * and running (scheduled onto the CPU), respectively.
	 */
	u64				total_समय_enabled;
	u64				total_समय_running;
	u64				tstamp;

	/*
	 * बारtamp shaकरोws the actual context timing but it can
	 * be safely used in NMI पूर्णांकerrupt context. It reflects the
	 * context समय as it was when the event was last scheduled in.
	 *
	 * ctx_समय alपढ़ोy accounts क्रम ctx->बारtamp. Thereक्रमe to
	 * compute ctx_समय क्रम a sample, simply add perf_घड़ी().
	 */
	u64				shaकरोw_ctx_समय;

	काष्ठा perf_event_attr		attr;
	u16				header_size;
	u16				id_header_size;
	u16				पढ़ो_size;
	काष्ठा hw_perf_event		hw;

	काष्ठा perf_event_context	*ctx;
	atomic_दीर्घ_t			refcount;

	/*
	 * These accumulate total समय (in nanoseconds) that children
	 * events have been enabled and running, respectively.
	 */
	atomic64_t			child_total_समय_enabled;
	atomic64_t			child_total_समय_running;

	/*
	 * Protect attach/detach and child_list:
	 */
	काष्ठा mutex			child_mutex;
	काष्ठा list_head		child_list;
	काष्ठा perf_event		*parent;

	पूर्णांक				oncpu;
	पूर्णांक				cpu;

	काष्ठा list_head		owner_entry;
	काष्ठा task_काष्ठा		*owner;

	/* mmap bits */
	काष्ठा mutex			mmap_mutex;
	atomic_t			mmap_count;

	काष्ठा perf_buffer		*rb;
	काष्ठा list_head		rb_entry;
	अचिन्हित दीर्घ			rcu_batches;
	पूर्णांक				rcu_pending;

	/* poll related */
	रुको_queue_head_t		रुकोq;
	काष्ठा fasync_काष्ठा		*fasync;

	/* delayed work क्रम NMIs and such */
	पूर्णांक				pending_wakeup;
	पूर्णांक				pending_समाप्त;
	पूर्णांक				pending_disable;
	अचिन्हित दीर्घ			pending_addr;	/* SIGTRAP */
	काष्ठा irq_work			pending;

	atomic_t			event_limit;

	/* address range filters */
	काष्ठा perf_addr_filters_head	addr_filters;
	/* vma address array क्रम file-based filders */
	काष्ठा perf_addr_filter_range	*addr_filter_ranges;
	अचिन्हित दीर्घ			addr_filters_gen;

	/* क्रम aux_output events */
	काष्ठा perf_event		*aux_event;

	व्योम (*destroy)(काष्ठा perf_event *);
	काष्ठा rcu_head			rcu_head;

	काष्ठा pid_namespace		*ns;
	u64				id;

	u64				(*घड़ी)(व्योम);
	perf_overflow_handler_t		overflow_handler;
	व्योम				*overflow_handler_context;
#अगर_घोषित CONFIG_BPF_SYSCALL
	perf_overflow_handler_t		orig_overflow_handler;
	काष्ठा bpf_prog			*prog;
#पूर्ण_अगर

#अगर_घोषित CONFIG_EVENT_TRACING
	काष्ठा trace_event_call		*tp_event;
	काष्ठा event_filter		*filter;
#अगर_घोषित CONFIG_FUNCTION_TRACER
	काष्ठा ftrace_ops               ftrace_ops;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CGROUP_PERF
	काष्ठा perf_cgroup		*cgrp; /* cgroup event is attach to */
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY
	व्योम *security;
#पूर्ण_अगर
	काष्ठा list_head		sb_list;
#पूर्ण_अगर /* CONFIG_PERF_EVENTS */
पूर्ण;


काष्ठा perf_event_groups अणु
	काष्ठा rb_root	tree;
	u64		index;
पूर्ण;

/**
 * काष्ठा perf_event_context - event context काष्ठाure
 *
 * Used as a container क्रम task events and CPU events as well:
 */
काष्ठा perf_event_context अणु
	काष्ठा pmu			*pmu;
	/*
	 * Protect the states of the events in the list,
	 * nr_active, and the list:
	 */
	raw_spinlock_t			lock;
	/*
	 * Protect the list of events.  Locking either mutex or lock
	 * is sufficient to ensure the list करोesn't change; to change
	 * the list you need to lock both the mutex and the spinlock.
	 */
	काष्ठा mutex			mutex;

	काष्ठा list_head		active_ctx_list;
	काष्ठा perf_event_groups	pinned_groups;
	काष्ठा perf_event_groups	flexible_groups;
	काष्ठा list_head		event_list;

	काष्ठा list_head		pinned_active;
	काष्ठा list_head		flexible_active;

	पूर्णांक				nr_events;
	पूर्णांक				nr_active;
	पूर्णांक				is_active;
	पूर्णांक				nr_stat;
	पूर्णांक				nr_freq;
	पूर्णांक				rotate_disable;
	/*
	 * Set when nr_events != nr_active, except tolerant to events not
	 * necessary to be active due to scheduling स्थिरraपूर्णांकs, such as cgroups.
	 */
	पूर्णांक				rotate_necessary;
	refcount_t			refcount;
	काष्ठा task_काष्ठा		*task;

	/*
	 * Context घड़ी, runs when context enabled.
	 */
	u64				समय;
	u64				बारtamp;

	/*
	 * These fields let us detect when two contexts have both
	 * been cloned (inherited) from a common ancestor.
	 */
	काष्ठा perf_event_context	*parent_ctx;
	u64				parent_gen;
	u64				generation;
	पूर्णांक				pin_count;
#अगर_घोषित CONFIG_CGROUP_PERF
	पूर्णांक				nr_cgroups;	 /* cgroup evts */
#पूर्ण_अगर
	व्योम				*task_ctx_data; /* pmu specअगरic data */
	काष्ठा rcu_head			rcu_head;
पूर्ण;

/*
 * Number of contexts where an event can trigger:
 *	task, softirq, hardirq, nmi.
 */
#घोषणा PERF_NR_CONTEXTS	4

/**
 * काष्ठा perf_event_cpu_context - per cpu event context काष्ठाure
 */
काष्ठा perf_cpu_context अणु
	काष्ठा perf_event_context	ctx;
	काष्ठा perf_event_context	*task_ctx;
	पूर्णांक				active_oncpu;
	पूर्णांक				exclusive;

	raw_spinlock_t			hrसमयr_lock;
	काष्ठा hrसमयr			hrसमयr;
	kसमय_प्रकार				hrसमयr_पूर्णांकerval;
	अचिन्हित पूर्णांक			hrसमयr_active;

#अगर_घोषित CONFIG_CGROUP_PERF
	काष्ठा perf_cgroup		*cgrp;
	काष्ठा list_head		cgrp_cpuctx_entry;
#पूर्ण_अगर

	काष्ठा list_head		sched_cb_entry;
	पूर्णांक				sched_cb_usage;

	पूर्णांक				online;
	/*
	 * Per-CPU storage क्रम iterators used in visit_groups_merge. The शेष
	 * storage is of size 2 to hold the CPU and any CPU event iterators.
	 */
	पूर्णांक				heap_size;
	काष्ठा perf_event		**heap;
	काष्ठा perf_event		*heap_शेष[2];
पूर्ण;

काष्ठा perf_output_handle अणु
	काष्ठा perf_event		*event;
	काष्ठा perf_buffer		*rb;
	अचिन्हित दीर्घ			wakeup;
	अचिन्हित दीर्घ			size;
	u64				aux_flags;
	जोड़ अणु
		व्योम			*addr;
		अचिन्हित दीर्घ		head;
	पूर्ण;
	पूर्णांक				page;
पूर्ण;

काष्ठा bpf_perf_event_data_kern अणु
	bpf_user_pt_regs_t *regs;
	काष्ठा perf_sample_data *data;
	काष्ठा perf_event *event;
पूर्ण;

#अगर_घोषित CONFIG_CGROUP_PERF

/*
 * perf_cgroup_info keeps track of समय_enabled क्रम a cgroup.
 * This is a per-cpu dynamically allocated data काष्ठाure.
 */
काष्ठा perf_cgroup_info अणु
	u64				समय;
	u64				बारtamp;
पूर्ण;

काष्ठा perf_cgroup अणु
	काष्ठा cgroup_subsys_state	css;
	काष्ठा perf_cgroup_info	__percpu *info;
पूर्ण;

/*
 * Must ensure cgroup is pinned (css_get) beक्रमe calling
 * this function. In other words, we cannot call this function
 * अगर there is no cgroup event क्रम the current CPU context.
 */
अटल अंतरभूत काष्ठा perf_cgroup *
perf_cgroup_from_task(काष्ठा task_काष्ठा *task, काष्ठा perf_event_context *ctx)
अणु
	वापस container_of(task_css_check(task, perf_event_cgrp_id,
					   ctx ? lockdep_is_held(&ctx->lock)
					       : true),
			    काष्ठा perf_cgroup, css);
पूर्ण
#पूर्ण_अगर /* CONFIG_CGROUP_PERF */

#अगर_घोषित CONFIG_PERF_EVENTS

बाह्य व्योम *perf_aux_output_begin(काष्ठा perf_output_handle *handle,
				   काष्ठा perf_event *event);
बाह्य व्योम perf_aux_output_end(काष्ठा perf_output_handle *handle,
				अचिन्हित दीर्घ size);
बाह्य पूर्णांक perf_aux_output_skip(काष्ठा perf_output_handle *handle,
				अचिन्हित दीर्घ size);
बाह्य व्योम *perf_get_aux(काष्ठा perf_output_handle *handle);
बाह्य व्योम perf_aux_output_flag(काष्ठा perf_output_handle *handle, u64 flags);
बाह्य व्योम perf_event_itrace_started(काष्ठा perf_event *event);

बाह्य पूर्णांक perf_pmu_रेजिस्टर(काष्ठा pmu *pmu, स्थिर अक्षर *name, पूर्णांक type);
बाह्य व्योम perf_pmu_unरेजिस्टर(काष्ठा pmu *pmu);

बाह्य व्योम __perf_event_task_sched_in(काष्ठा task_काष्ठा *prev,
				       काष्ठा task_काष्ठा *task);
बाह्य व्योम __perf_event_task_sched_out(काष्ठा task_काष्ठा *prev,
					काष्ठा task_काष्ठा *next);
बाह्य पूर्णांक perf_event_init_task(काष्ठा task_काष्ठा *child, u64 clone_flags);
बाह्य व्योम perf_event_निकास_task(काष्ठा task_काष्ठा *child);
बाह्य व्योम perf_event_मुक्त_task(काष्ठा task_काष्ठा *task);
बाह्य व्योम perf_event_delayed_put(काष्ठा task_काष्ठा *task);
बाह्य काष्ठा file *perf_event_get(अचिन्हित पूर्णांक fd);
बाह्य स्थिर काष्ठा perf_event *perf_get_event(काष्ठा file *file);
बाह्य स्थिर काष्ठा perf_event_attr *perf_event_attrs(काष्ठा perf_event *event);
बाह्य व्योम perf_event_prपूर्णांक_debug(व्योम);
बाह्य व्योम perf_pmu_disable(काष्ठा pmu *pmu);
बाह्य व्योम perf_pmu_enable(काष्ठा pmu *pmu);
बाह्य व्योम perf_sched_cb_dec(काष्ठा pmu *pmu);
बाह्य व्योम perf_sched_cb_inc(काष्ठा pmu *pmu);
बाह्य पूर्णांक perf_event_task_disable(व्योम);
बाह्य पूर्णांक perf_event_task_enable(व्योम);

बाह्य व्योम perf_pmu_resched(काष्ठा pmu *pmu);

बाह्य पूर्णांक perf_event_refresh(काष्ठा perf_event *event, पूर्णांक refresh);
बाह्य व्योम perf_event_update_userpage(काष्ठा perf_event *event);
बाह्य पूर्णांक perf_event_release_kernel(काष्ठा perf_event *event);
बाह्य काष्ठा perf_event *
perf_event_create_kernel_counter(काष्ठा perf_event_attr *attr,
				पूर्णांक cpu,
				काष्ठा task_काष्ठा *task,
				perf_overflow_handler_t callback,
				व्योम *context);
बाह्य व्योम perf_pmu_migrate_context(काष्ठा pmu *pmu,
				पूर्णांक src_cpu, पूर्णांक dst_cpu);
पूर्णांक perf_event_पढ़ो_local(काष्ठा perf_event *event, u64 *value,
			  u64 *enabled, u64 *running);
बाह्य u64 perf_event_पढ़ो_value(काष्ठा perf_event *event,
				 u64 *enabled, u64 *running);


काष्ठा perf_sample_data अणु
	/*
	 * Fields set by perf_sample_data_init(), group so as to
	 * minimize the cachelines touched.
	 */
	u64				addr;
	काष्ठा perf_raw_record		*raw;
	काष्ठा perf_branch_stack	*br_stack;
	u64				period;
	जोड़ perf_sample_weight	weight;
	u64				txn;
	जोड़  perf_mem_data_src	data_src;

	/*
	 * The other fields, optionally अणुset,usedपूर्ण by
	 * perf_अणुprepare,outputपूर्ण_sample().
	 */
	u64				type;
	u64				ip;
	काष्ठा अणु
		u32	pid;
		u32	tid;
	पूर्ण				tid_entry;
	u64				समय;
	u64				id;
	u64				stream_id;
	काष्ठा अणु
		u32	cpu;
		u32	reserved;
	पूर्ण				cpu_entry;
	काष्ठा perf_callchain_entry	*callchain;
	u64				aux_size;

	काष्ठा perf_regs		regs_user;
	काष्ठा perf_regs		regs_पूर्णांकr;
	u64				stack_user_size;

	u64				phys_addr;
	u64				cgroup;
	u64				data_page_size;
	u64				code_page_size;
पूर्ण ____cacheline_aligned;

/* शेष value क्रम data source */
#घोषणा PERF_MEM_NA (PERF_MEM_S(OP, NA)   |\
		    PERF_MEM_S(LVL, NA)   |\
		    PERF_MEM_S(SNOOP, NA) |\
		    PERF_MEM_S(LOCK, NA)  |\
		    PERF_MEM_S(TLB, NA))

अटल अंतरभूत व्योम perf_sample_data_init(काष्ठा perf_sample_data *data,
					 u64 addr, u64 period)
अणु
	/* reमुख्यing काष्ठा members initialized in perf_prepare_sample() */
	data->addr = addr;
	data->raw  = शून्य;
	data->br_stack = शून्य;
	data->period = period;
	data->weight.full = 0;
	data->data_src.val = PERF_MEM_NA;
	data->txn = 0;
पूर्ण

बाह्य व्योम perf_output_sample(काष्ठा perf_output_handle *handle,
			       काष्ठा perf_event_header *header,
			       काष्ठा perf_sample_data *data,
			       काष्ठा perf_event *event);
बाह्य व्योम perf_prepare_sample(काष्ठा perf_event_header *header,
				काष्ठा perf_sample_data *data,
				काष्ठा perf_event *event,
				काष्ठा pt_regs *regs);

बाह्य पूर्णांक perf_event_overflow(काष्ठा perf_event *event,
				 काष्ठा perf_sample_data *data,
				 काष्ठा pt_regs *regs);

बाह्य व्योम perf_event_output_क्रमward(काष्ठा perf_event *event,
				     काष्ठा perf_sample_data *data,
				     काष्ठा pt_regs *regs);
बाह्य व्योम perf_event_output_backward(काष्ठा perf_event *event,
				       काष्ठा perf_sample_data *data,
				       काष्ठा pt_regs *regs);
बाह्य पूर्णांक perf_event_output(काष्ठा perf_event *event,
			     काष्ठा perf_sample_data *data,
			     काष्ठा pt_regs *regs);

अटल अंतरभूत bool
is_शेष_overflow_handler(काष्ठा perf_event *event)
अणु
	अगर (likely(event->overflow_handler == perf_event_output_क्रमward))
		वापस true;
	अगर (unlikely(event->overflow_handler == perf_event_output_backward))
		वापस true;
	वापस false;
पूर्ण

बाह्य व्योम
perf_event_header__init_id(काष्ठा perf_event_header *header,
			   काष्ठा perf_sample_data *data,
			   काष्ठा perf_event *event);
बाह्य व्योम
perf_event__output_id_sample(काष्ठा perf_event *event,
			     काष्ठा perf_output_handle *handle,
			     काष्ठा perf_sample_data *sample);

बाह्य व्योम
perf_log_lost_samples(काष्ठा perf_event *event, u64 lost);

अटल अंतरभूत bool event_has_any_exclude_flag(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;

	वापस attr->exclude_idle || attr->exclude_user ||
	       attr->exclude_kernel || attr->exclude_hv ||
	       attr->exclude_guest || attr->exclude_host;
पूर्ण

अटल अंतरभूत bool is_sampling_event(काष्ठा perf_event *event)
अणु
	वापस event->attr.sample_period != 0;
पूर्ण

/*
 * Return 1 क्रम a software event, 0 क्रम a hardware event
 */
अटल अंतरभूत पूर्णांक is_software_event(काष्ठा perf_event *event)
अणु
	वापस event->event_caps & PERF_EV_CAP_SOFTWARE;
पूर्ण

/*
 * Return 1 क्रम event in sw context, 0 क्रम event in hw context
 */
अटल अंतरभूत पूर्णांक in_software_context(काष्ठा perf_event *event)
अणु
	वापस event->ctx->pmu->task_ctx_nr == perf_sw_context;
पूर्ण

अटल अंतरभूत पूर्णांक is_exclusive_pmu(काष्ठा pmu *pmu)
अणु
	वापस pmu->capabilities & PERF_PMU_CAP_EXCLUSIVE;
पूर्ण

बाह्य काष्ठा अटल_key perf_swevent_enabled[PERF_COUNT_SW_MAX];

बाह्य व्योम ___perf_sw_event(u32, u64, काष्ठा pt_regs *, u64);
बाह्य व्योम __perf_sw_event(u32, u64, काष्ठा pt_regs *, u64);

#अगर_अघोषित perf_arch_fetch_caller_regs
अटल अंतरभूत व्योम perf_arch_fetch_caller_regs(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip) अणु पूर्ण
#पूर्ण_अगर

/*
 * When generating a perf sample in-line, instead of from an पूर्णांकerrupt /
 * exception, we lack a pt_regs. This is typically used from software events
 * like: SW_CONTEXT_SWITCHES, SW_MIGRATIONS and the tie-in with tracepoपूर्णांकs.
 *
 * We typically करोn't need a full set, but (क्रम x86) करो require:
 * - ip क्रम PERF_SAMPLE_IP
 * - cs क्रम user_mode() tests
 * - sp क्रम PERF_SAMPLE_CALLCHAIN
 * - eflags क्रम MISC bits and CALLCHAIN (see: perf_hw_regs())
 *
 * NOTE: assumes @regs is otherwise alपढ़ोy 0 filled; this is important क्रम
 * things like PERF_SAMPLE_REGS_INTR.
 */
अटल अंतरभूत व्योम perf_fetch_caller_regs(काष्ठा pt_regs *regs)
अणु
	perf_arch_fetch_caller_regs(regs, CALLER_ADDR0);
पूर्ण

अटल __always_अंतरभूत व्योम
perf_sw_event(u32 event_id, u64 nr, काष्ठा pt_regs *regs, u64 addr)
अणु
	अगर (अटल_key_false(&perf_swevent_enabled[event_id]))
		__perf_sw_event(event_id, nr, regs, addr);
पूर्ण

DECLARE_PER_CPU(काष्ठा pt_regs, __perf_regs[4]);

/*
 * 'Special' version क्रम the scheduler, it hard assumes no recursion,
 * which is guaranteed by us not actually scheduling inside other swevents
 * because those disable preemption.
 */
अटल __always_अंतरभूत व्योम __perf_sw_event_sched(u32 event_id, u64 nr, u64 addr)
अणु
	काष्ठा pt_regs *regs = this_cpu_ptr(&__perf_regs[0]);

	perf_fetch_caller_regs(regs);
	___perf_sw_event(event_id, nr, regs, addr);
पूर्ण

बाह्य काष्ठा अटल_key_false perf_sched_events;

अटल __always_अंतरभूत bool __perf_sw_enabled(पूर्णांक swevt)
अणु
	वापस अटल_key_false(&perf_swevent_enabled[swevt]);
पूर्ण

अटल अंतरभूत व्योम perf_event_task_migrate(काष्ठा task_काष्ठा *task)
अणु
	अगर (__perf_sw_enabled(PERF_COUNT_SW_CPU_MIGRATIONS))
		task->sched_migrated = 1;
पूर्ण

अटल अंतरभूत व्योम perf_event_task_sched_in(काष्ठा task_काष्ठा *prev,
					    काष्ठा task_काष्ठा *task)
अणु
	अगर (अटल_branch_unlikely(&perf_sched_events))
		__perf_event_task_sched_in(prev, task);

	अगर (__perf_sw_enabled(PERF_COUNT_SW_CPU_MIGRATIONS) &&
	    task->sched_migrated) अणु
		__perf_sw_event_sched(PERF_COUNT_SW_CPU_MIGRATIONS, 1, 0);
		task->sched_migrated = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम perf_event_task_sched_out(काष्ठा task_काष्ठा *prev,
					     काष्ठा task_काष्ठा *next)
अणु
	अगर (__perf_sw_enabled(PERF_COUNT_SW_CONTEXT_SWITCHES))
		__perf_sw_event_sched(PERF_COUNT_SW_CONTEXT_SWITCHES, 1, 0);

#अगर_घोषित CONFIG_CGROUP_PERF
	अगर (__perf_sw_enabled(PERF_COUNT_SW_CGROUP_SWITCHES) &&
	    perf_cgroup_from_task(prev, शून्य) !=
	    perf_cgroup_from_task(next, शून्य))
		__perf_sw_event_sched(PERF_COUNT_SW_CGROUP_SWITCHES, 1, 0);
#पूर्ण_अगर

	अगर (अटल_branch_unlikely(&perf_sched_events))
		__perf_event_task_sched_out(prev, next);
पूर्ण

बाह्य व्योम perf_event_mmap(काष्ठा vm_area_काष्ठा *vma);

बाह्य व्योम perf_event_ksymbol(u16 ksym_type, u64 addr, u32 len,
			       bool unरेजिस्टर, स्थिर अक्षर *sym);
बाह्य व्योम perf_event_bpf_event(काष्ठा bpf_prog *prog,
				 क्रमागत perf_bpf_event_type type,
				 u16 flags);

बाह्य काष्ठा perf_guest_info_callbacks *perf_guest_cbs;
बाह्य पूर्णांक perf_रेजिस्टर_guest_info_callbacks(काष्ठा perf_guest_info_callbacks *callbacks);
बाह्य पूर्णांक perf_unरेजिस्टर_guest_info_callbacks(काष्ठा perf_guest_info_callbacks *callbacks);

बाह्य व्योम perf_event_exec(व्योम);
बाह्य व्योम perf_event_comm(काष्ठा task_काष्ठा *tsk, bool exec);
बाह्य व्योम perf_event_namespaces(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम perf_event_विभाजन(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम perf_event_text_poke(स्थिर व्योम *addr,
				 स्थिर व्योम *old_bytes, माप_प्रकार old_len,
				 स्थिर व्योम *new_bytes, माप_प्रकार new_len);

/* Callchains */
DECLARE_PER_CPU(काष्ठा perf_callchain_entry, perf_callchain_entry);

बाह्य व्योम perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs);
बाह्य व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry, काष्ठा pt_regs *regs);
बाह्य काष्ठा perf_callchain_entry *
get_perf_callchain(काष्ठा pt_regs *regs, u32 init_nr, bool kernel, bool user,
		   u32 max_stack, bool crosstask, bool add_mark);
बाह्य काष्ठा perf_callchain_entry *perf_callchain(काष्ठा perf_event *event, काष्ठा pt_regs *regs);
बाह्य पूर्णांक get_callchain_buffers(पूर्णांक max_stack);
बाह्य व्योम put_callchain_buffers(व्योम);
बाह्य काष्ठा perf_callchain_entry *get_callchain_entry(पूर्णांक *rctx);
बाह्य व्योम put_callchain_entry(पूर्णांक rctx);

बाह्य पूर्णांक sysctl_perf_event_max_stack;
बाह्य पूर्णांक sysctl_perf_event_max_contexts_per_stack;

अटल अंतरभूत पूर्णांक perf_callchain_store_context(काष्ठा perf_callchain_entry_ctx *ctx, u64 ip)
अणु
	अगर (ctx->contexts < sysctl_perf_event_max_contexts_per_stack) अणु
		काष्ठा perf_callchain_entry *entry = ctx->entry;
		entry->ip[entry->nr++] = ip;
		++ctx->contexts;
		वापस 0;
	पूर्ण अन्यथा अणु
		ctx->contexts_maxed = true;
		वापस -1; /* no more room, stop walking the stack */
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक perf_callchain_store(काष्ठा perf_callchain_entry_ctx *ctx, u64 ip)
अणु
	अगर (ctx->nr < ctx->max_stack && !ctx->contexts_maxed) अणु
		काष्ठा perf_callchain_entry *entry = ctx->entry;
		entry->ip[entry->nr++] = ip;
		++ctx->nr;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -1; /* no more room, stop walking the stack */
	पूर्ण
पूर्ण

बाह्य पूर्णांक sysctl_perf_event_paranoid;
बाह्य पूर्णांक sysctl_perf_event_mlock;
बाह्य पूर्णांक sysctl_perf_event_sample_rate;
बाह्य पूर्णांक sysctl_perf_cpu_समय_max_percent;

बाह्य व्योम perf_sample_event_took(u64 sample_len_ns);

पूर्णांक perf_proc_update_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक perf_cpu_समय_max_percent_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक perf_event_max_stack_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);

/* Access to perf_event_खोलो(2) syscall. */
#घोषणा PERF_SECURITY_OPEN		0

/* Finer grained perf_event_खोलो(2) access control. */
#घोषणा PERF_SECURITY_CPU		1
#घोषणा PERF_SECURITY_KERNEL		2
#घोषणा PERF_SECURITY_TRACEPOINT	3

अटल अंतरभूत पूर्णांक perf_is_paranoid(व्योम)
अणु
	वापस sysctl_perf_event_paranoid > -1;
पूर्ण

अटल अंतरभूत पूर्णांक perf_allow_kernel(काष्ठा perf_event_attr *attr)
अणु
	अगर (sysctl_perf_event_paranoid > 1 && !perfmon_capable())
		वापस -EACCES;

	वापस security_perf_event_खोलो(attr, PERF_SECURITY_KERNEL);
पूर्ण

अटल अंतरभूत पूर्णांक perf_allow_cpu(काष्ठा perf_event_attr *attr)
अणु
	अगर (sysctl_perf_event_paranoid > 0 && !perfmon_capable())
		वापस -EACCES;

	वापस security_perf_event_खोलो(attr, PERF_SECURITY_CPU);
पूर्ण

अटल अंतरभूत पूर्णांक perf_allow_tracepoपूर्णांक(काष्ठा perf_event_attr *attr)
अणु
	अगर (sysctl_perf_event_paranoid > -1 && !perfmon_capable())
		वापस -EPERM;

	वापस security_perf_event_खोलो(attr, PERF_SECURITY_TRACEPOINT);
पूर्ण

बाह्य व्योम perf_event_init(व्योम);
बाह्य व्योम perf_tp_event(u16 event_type, u64 count, व्योम *record,
			  पूर्णांक entry_size, काष्ठा pt_regs *regs,
			  काष्ठा hlist_head *head, पूर्णांक rctx,
			  काष्ठा task_काष्ठा *task);
बाह्य व्योम perf_bp_event(काष्ठा perf_event *event, व्योम *data);

#अगर_अघोषित perf_misc_flags
# define perf_misc_flags(regs) \
		(user_mode(regs) ? PERF_RECORD_MISC_USER : PERF_RECORD_MISC_KERNEL)
# define perf_inकाष्ठाion_poपूर्णांकer(regs)	inकाष्ठाion_poपूर्णांकer(regs)
#पूर्ण_अगर
#अगर_अघोषित perf_arch_bpf_user_pt_regs
# define perf_arch_bpf_user_pt_regs(regs) regs
#पूर्ण_अगर

अटल अंतरभूत bool has_branch_stack(काष्ठा perf_event *event)
अणु
	वापस event->attr.sample_type & PERF_SAMPLE_BRANCH_STACK;
पूर्ण

अटल अंतरभूत bool needs_branch_stack(काष्ठा perf_event *event)
अणु
	वापस event->attr.branch_sample_type != 0;
पूर्ण

अटल अंतरभूत bool has_aux(काष्ठा perf_event *event)
अणु
	वापस event->pmu->setup_aux;
पूर्ण

अटल अंतरभूत bool is_ग_लिखो_backward(काष्ठा perf_event *event)
अणु
	वापस !!event->attr.ग_लिखो_backward;
पूर्ण

अटल अंतरभूत bool has_addr_filter(काष्ठा perf_event *event)
अणु
	वापस event->pmu->nr_addr_filters;
पूर्ण

/*
 * An inherited event uses parent's filters
 */
अटल अंतरभूत काष्ठा perf_addr_filters_head *
perf_event_addr_filters(काष्ठा perf_event *event)
अणु
	काष्ठा perf_addr_filters_head *अगरh = &event->addr_filters;

	अगर (event->parent)
		अगरh = &event->parent->addr_filters;

	वापस अगरh;
पूर्ण

बाह्य व्योम perf_event_addr_filters_sync(काष्ठा perf_event *event);

बाह्य पूर्णांक perf_output_begin(काष्ठा perf_output_handle *handle,
			     काष्ठा perf_sample_data *data,
			     काष्ठा perf_event *event, अचिन्हित पूर्णांक size);
बाह्य पूर्णांक perf_output_begin_क्रमward(काष्ठा perf_output_handle *handle,
				     काष्ठा perf_sample_data *data,
				     काष्ठा perf_event *event,
				     अचिन्हित पूर्णांक size);
बाह्य पूर्णांक perf_output_begin_backward(काष्ठा perf_output_handle *handle,
				      काष्ठा perf_sample_data *data,
				      काष्ठा perf_event *event,
				      अचिन्हित पूर्णांक size);

बाह्य व्योम perf_output_end(काष्ठा perf_output_handle *handle);
बाह्य अचिन्हित पूर्णांक perf_output_copy(काष्ठा perf_output_handle *handle,
			     स्थिर व्योम *buf, अचिन्हित पूर्णांक len);
बाह्य अचिन्हित पूर्णांक perf_output_skip(काष्ठा perf_output_handle *handle,
				     अचिन्हित पूर्णांक len);
बाह्य दीर्घ perf_output_copy_aux(काष्ठा perf_output_handle *aux_handle,
				 काष्ठा perf_output_handle *handle,
				 अचिन्हित दीर्घ from, अचिन्हित दीर्घ to);
बाह्य पूर्णांक perf_swevent_get_recursion_context(व्योम);
बाह्य व्योम perf_swevent_put_recursion_context(पूर्णांक rctx);
बाह्य u64 perf_swevent_set_period(काष्ठा perf_event *event);
बाह्य व्योम perf_event_enable(काष्ठा perf_event *event);
बाह्य व्योम perf_event_disable(काष्ठा perf_event *event);
बाह्य व्योम perf_event_disable_local(काष्ठा perf_event *event);
बाह्य व्योम perf_event_disable_inatomic(काष्ठा perf_event *event);
बाह्य व्योम perf_event_task_tick(व्योम);
बाह्य पूर्णांक perf_event_account_पूर्णांकerrupt(काष्ठा perf_event *event);
बाह्य पूर्णांक perf_event_period(काष्ठा perf_event *event, u64 value);
बाह्य u64 perf_event_छोड़ो(काष्ठा perf_event *event, bool reset);
#अन्यथा /* !CONFIG_PERF_EVENTS: */
अटल अंतरभूत व्योम *
perf_aux_output_begin(काष्ठा perf_output_handle *handle,
		      काष्ठा perf_event *event)				अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम
perf_aux_output_end(काष्ठा perf_output_handle *handle, अचिन्हित दीर्घ size)
									अणु पूर्ण
अटल अंतरभूत पूर्णांक
perf_aux_output_skip(काष्ठा perf_output_handle *handle,
		     अचिन्हित दीर्घ size)				अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत व्योम *
perf_get_aux(काष्ठा perf_output_handle *handle)				अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम
perf_event_task_migrate(काष्ठा task_काष्ठा *task)			अणु पूर्ण
अटल अंतरभूत व्योम
perf_event_task_sched_in(काष्ठा task_काष्ठा *prev,
			 काष्ठा task_काष्ठा *task)			अणु पूर्ण
अटल अंतरभूत व्योम
perf_event_task_sched_out(काष्ठा task_काष्ठा *prev,
			  काष्ठा task_काष्ठा *next)			अणु पूर्ण
अटल अंतरभूत पूर्णांक perf_event_init_task(काष्ठा task_काष्ठा *child,
				       u64 clone_flags)			अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम perf_event_निकास_task(काष्ठा task_काष्ठा *child)	अणु पूर्ण
अटल अंतरभूत व्योम perf_event_मुक्त_task(काष्ठा task_काष्ठा *task)	अणु पूर्ण
अटल अंतरभूत व्योम perf_event_delayed_put(काष्ठा task_काष्ठा *task)	अणु पूर्ण
अटल अंतरभूत काष्ठा file *perf_event_get(अचिन्हित पूर्णांक fd)	अणु वापस ERR_PTR(-EINVAL); पूर्ण
अटल अंतरभूत स्थिर काष्ठा perf_event *perf_get_event(काष्ठा file *file)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत स्थिर काष्ठा perf_event_attr *perf_event_attrs(काष्ठा perf_event *event)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत पूर्णांक perf_event_पढ़ो_local(काष्ठा perf_event *event, u64 *value,
					u64 *enabled, u64 *running)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम perf_event_prपूर्णांक_debug(व्योम)				अणु पूर्ण
अटल अंतरभूत पूर्णांक perf_event_task_disable(व्योम)				अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत पूर्णांक perf_event_task_enable(व्योम)				अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत पूर्णांक perf_event_refresh(काष्ठा perf_event *event, पूर्णांक refresh)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम
perf_sw_event(u32 event_id, u64 nr, काष्ठा pt_regs *regs, u64 addr)	अणु पूर्ण
अटल अंतरभूत व्योम
perf_bp_event(काष्ठा perf_event *event, व्योम *data)			अणु पूर्ण

अटल अंतरभूत पूर्णांक perf_रेजिस्टर_guest_info_callbacks
(काष्ठा perf_guest_info_callbacks *callbacks)				अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक perf_unरेजिस्टर_guest_info_callbacks
(काष्ठा perf_guest_info_callbacks *callbacks)				अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम perf_event_mmap(काष्ठा vm_area_काष्ठा *vma)		अणु पूर्ण

प्रकार पूर्णांक (perf_ksymbol_get_name_f)(अक्षर *name, पूर्णांक name_len, व्योम *data);
अटल अंतरभूत व्योम perf_event_ksymbol(u16 ksym_type, u64 addr, u32 len,
				      bool unरेजिस्टर, स्थिर अक्षर *sym)	अणु पूर्ण
अटल अंतरभूत व्योम perf_event_bpf_event(काष्ठा bpf_prog *prog,
					क्रमागत perf_bpf_event_type type,
					u16 flags)			अणु पूर्ण
अटल अंतरभूत व्योम perf_event_exec(व्योम)				अणु पूर्ण
अटल अंतरभूत व्योम perf_event_comm(काष्ठा task_काष्ठा *tsk, bool exec)	अणु पूर्ण
अटल अंतरभूत व्योम perf_event_namespaces(काष्ठा task_काष्ठा *tsk)	अणु पूर्ण
अटल अंतरभूत व्योम perf_event_विभाजन(काष्ठा task_काष्ठा *tsk)		अणु पूर्ण
अटल अंतरभूत व्योम perf_event_text_poke(स्थिर व्योम *addr,
					स्थिर व्योम *old_bytes,
					माप_प्रकार old_len,
					स्थिर व्योम *new_bytes,
					माप_प्रकार new_len)			अणु पूर्ण
अटल अंतरभूत व्योम perf_event_init(व्योम)				अणु पूर्ण
अटल अंतरभूत पूर्णांक  perf_swevent_get_recursion_context(व्योम)		अणु वापस -1; पूर्ण
अटल अंतरभूत व्योम perf_swevent_put_recursion_context(पूर्णांक rctx)		अणु पूर्ण
अटल अंतरभूत u64 perf_swevent_set_period(काष्ठा perf_event *event)	अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम perf_event_enable(काष्ठा perf_event *event)		अणु पूर्ण
अटल अंतरभूत व्योम perf_event_disable(काष्ठा perf_event *event)		अणु पूर्ण
अटल अंतरभूत पूर्णांक __perf_event_disable(व्योम *info)			अणु वापस -1; पूर्ण
अटल अंतरभूत व्योम perf_event_task_tick(व्योम)				अणु पूर्ण
अटल अंतरभूत पूर्णांक perf_event_release_kernel(काष्ठा perf_event *event)	अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक perf_event_period(काष्ठा perf_event *event, u64 value)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत u64 perf_event_छोड़ो(काष्ठा perf_event *event, bool reset)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PERF_EVENTS) && defined(CONFIG_CPU_SUP_INTEL)
बाह्य व्योम perf_restore_debug_store(व्योम);
#अन्यथा
अटल अंतरभूत व्योम perf_restore_debug_store(व्योम)			अणु पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत bool perf_raw_frag_last(स्थिर काष्ठा perf_raw_frag *frag)
अणु
	वापस frag->pad < माप(u64);
पूर्ण

#घोषणा perf_output_put(handle, x) perf_output_copy((handle), &(x), माप(x))

काष्ठा perf_pmu_events_attr अणु
	काष्ठा device_attribute attr;
	u64 id;
	स्थिर अक्षर *event_str;
पूर्ण;

काष्ठा perf_pmu_events_ht_attr अणु
	काष्ठा device_attribute			attr;
	u64					id;
	स्थिर अक्षर				*event_str_ht;
	स्थिर अक्षर				*event_str_noht;
पूर्ण;

काष्ठा perf_pmu_events_hybrid_attr अणु
	काष्ठा device_attribute			attr;
	u64					id;
	स्थिर अक्षर				*event_str;
	u64					pmu_type;
पूर्ण;

काष्ठा perf_pmu_क्रमmat_hybrid_attr अणु
	काष्ठा device_attribute			attr;
	u64					pmu_type;
पूर्ण;

sमाप_प्रकार perf_event_sysfs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *page);

#घोषणा PMU_EVENT_ATTR(_name, _var, _id, _show)				\
अटल काष्ठा perf_pmu_events_attr _var = अणु				\
	.attr = __ATTR(_name, 0444, _show, शून्य),			\
	.id   =  _id,							\
पूर्ण;

#घोषणा PMU_EVENT_ATTR_STRING(_name, _var, _str)			    \
अटल काष्ठा perf_pmu_events_attr _var = अणु				    \
	.attr		= __ATTR(_name, 0444, perf_event_sysfs_show, शून्य), \
	.id		= 0,						    \
	.event_str	= _str,						    \
पूर्ण;

#घोषणा PMU_FORMAT_ATTR(_name, _क्रमmat)					\
अटल sमाप_प्रकार								\
_name##_show(काष्ठा device *dev,					\
			       काष्ठा device_attribute *attr,		\
			       अक्षर *page)				\
अणु									\
	BUILD_BUG_ON(माप(_क्रमmat) >= PAGE_SIZE);			\
	वापस प्र_लिखो(page, _क्रमmat "\n");				\
पूर्ण									\
									\
अटल काष्ठा device_attribute क्रमmat_attr_##_name = __ATTR_RO(_name)

/* Perक्रमmance counter hotplug functions */
#अगर_घोषित CONFIG_PERF_EVENTS
पूर्णांक perf_event_init_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक perf_event_निकास_cpu(अचिन्हित पूर्णांक cpu);
#अन्यथा
#घोषणा perf_event_init_cpu	शून्य
#घोषणा perf_event_निकास_cpu	शून्य
#पूर्ण_अगर

बाह्य व्योम __weak arch_perf_update_userpage(काष्ठा perf_event *event,
					     काष्ठा perf_event_mmap_page *userpg,
					     u64 now);

#अगर_घोषित CONFIG_MMU
बाह्य __weak u64 arch_perf_get_page_size(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_PERF_EVENT_H */
