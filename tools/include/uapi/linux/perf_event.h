<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
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
#अगर_अघोषित _UAPI_LINUX_PERF_EVENT_H
#घोषणा _UAPI_LINUX_PERF_EVENT_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <यंत्र/byteorder.h>

/*
 * User-space ABI bits:
 */

/*
 * attr.type
 */
क्रमागत perf_type_id अणु
	PERF_TYPE_HARDWARE			= 0,
	PERF_TYPE_SOFTWARE			= 1,
	PERF_TYPE_TRACEPOINT			= 2,
	PERF_TYPE_HW_CACHE			= 3,
	PERF_TYPE_RAW				= 4,
	PERF_TYPE_BREAKPOINT			= 5,

	PERF_TYPE_MAX,				/* non-ABI */
पूर्ण;

/*
 * attr.config layout क्रम type PERF_TYPE_HARDWARE and PERF_TYPE_HW_CACHE
 * PERF_TYPE_HARDWARE:			0xEEEEEEEE000000AA
 *					AA: hardware event ID
 *					EEEEEEEE: PMU type ID
 * PERF_TYPE_HW_CACHE:			0xEEEEEEEE00DDCCBB
 *					BB: hardware cache ID
 *					CC: hardware cache op ID
 *					DD: hardware cache op result ID
 *					EEEEEEEE: PMU type ID
 * If the PMU type ID is 0, the PERF_TYPE_RAW will be applied.
 */
#घोषणा PERF_PMU_TYPE_SHIFT		32
#घोषणा PERF_HW_EVENT_MASK		0xffffffff

/*
 * Generalized perक्रमmance event event_id types, used by the
 * attr.event_id parameter of the sys_perf_event_खोलो()
 * syscall:
 */
क्रमागत perf_hw_id अणु
	/*
	 * Common hardware events, generalized by the kernel:
	 */
	PERF_COUNT_HW_CPU_CYCLES		= 0,
	PERF_COUNT_HW_INSTRUCTIONS		= 1,
	PERF_COUNT_HW_CACHE_REFERENCES		= 2,
	PERF_COUNT_HW_CACHE_MISSES		= 3,
	PERF_COUNT_HW_BRANCH_INSTRUCTIONS	= 4,
	PERF_COUNT_HW_BRANCH_MISSES		= 5,
	PERF_COUNT_HW_BUS_CYCLES		= 6,
	PERF_COUNT_HW_STALLED_CYCLES_FRONTEND	= 7,
	PERF_COUNT_HW_STALLED_CYCLES_BACKEND	= 8,
	PERF_COUNT_HW_REF_CPU_CYCLES		= 9,

	PERF_COUNT_HW_MAX,			/* non-ABI */
पूर्ण;

/*
 * Generalized hardware cache events:
 *
 *       अणु L1-D, L1-I, LLC, ITLB, DTLB, BPU, NODE पूर्ण x
 *       अणु पढ़ो, ग_लिखो, prefetch पूर्ण x
 *       अणु accesses, misses पूर्ण
 */
क्रमागत perf_hw_cache_id अणु
	PERF_COUNT_HW_CACHE_L1D			= 0,
	PERF_COUNT_HW_CACHE_L1I			= 1,
	PERF_COUNT_HW_CACHE_LL			= 2,
	PERF_COUNT_HW_CACHE_DTLB		= 3,
	PERF_COUNT_HW_CACHE_ITLB		= 4,
	PERF_COUNT_HW_CACHE_BPU			= 5,
	PERF_COUNT_HW_CACHE_NODE		= 6,

	PERF_COUNT_HW_CACHE_MAX,		/* non-ABI */
पूर्ण;

क्रमागत perf_hw_cache_op_id अणु
	PERF_COUNT_HW_CACHE_OP_READ		= 0,
	PERF_COUNT_HW_CACHE_OP_WRITE		= 1,
	PERF_COUNT_HW_CACHE_OP_PREFETCH		= 2,

	PERF_COUNT_HW_CACHE_OP_MAX,		/* non-ABI */
पूर्ण;

क्रमागत perf_hw_cache_op_result_id अणु
	PERF_COUNT_HW_CACHE_RESULT_ACCESS	= 0,
	PERF_COUNT_HW_CACHE_RESULT_MISS		= 1,

	PERF_COUNT_HW_CACHE_RESULT_MAX,		/* non-ABI */
पूर्ण;

/*
 * Special "software" events provided by the kernel, even अगर the hardware
 * करोes not support perक्रमmance events. These events measure various
 * physical and sw events of the kernel (and allow the profiling of them as
 * well):
 */
क्रमागत perf_sw_ids अणु
	PERF_COUNT_SW_CPU_CLOCK			= 0,
	PERF_COUNT_SW_TASK_CLOCK		= 1,
	PERF_COUNT_SW_PAGE_FAULTS		= 2,
	PERF_COUNT_SW_CONTEXT_SWITCHES		= 3,
	PERF_COUNT_SW_CPU_MIGRATIONS		= 4,
	PERF_COUNT_SW_PAGE_FAULTS_MIN		= 5,
	PERF_COUNT_SW_PAGE_FAULTS_MAJ		= 6,
	PERF_COUNT_SW_ALIGNMENT_FAULTS		= 7,
	PERF_COUNT_SW_EMULATION_FAULTS		= 8,
	PERF_COUNT_SW_DUMMY			= 9,
	PERF_COUNT_SW_BPF_OUTPUT		= 10,
	PERF_COUNT_SW_CGROUP_SWITCHES		= 11,

	PERF_COUNT_SW_MAX,			/* non-ABI */
पूर्ण;

/*
 * Bits that can be set in attr.sample_type to request inक्रमmation
 * in the overflow packets.
 */
क्रमागत perf_event_sample_क्रमmat अणु
	PERF_SAMPLE_IP				= 1U << 0,
	PERF_SAMPLE_TID				= 1U << 1,
	PERF_SAMPLE_TIME			= 1U << 2,
	PERF_SAMPLE_ADDR			= 1U << 3,
	PERF_SAMPLE_READ			= 1U << 4,
	PERF_SAMPLE_CALLCHAIN			= 1U << 5,
	PERF_SAMPLE_ID				= 1U << 6,
	PERF_SAMPLE_CPU				= 1U << 7,
	PERF_SAMPLE_PERIOD			= 1U << 8,
	PERF_SAMPLE_STREAM_ID			= 1U << 9,
	PERF_SAMPLE_RAW				= 1U << 10,
	PERF_SAMPLE_BRANCH_STACK		= 1U << 11,
	PERF_SAMPLE_REGS_USER			= 1U << 12,
	PERF_SAMPLE_STACK_USER			= 1U << 13,
	PERF_SAMPLE_WEIGHT			= 1U << 14,
	PERF_SAMPLE_DATA_SRC			= 1U << 15,
	PERF_SAMPLE_IDENTIFIER			= 1U << 16,
	PERF_SAMPLE_TRANSACTION			= 1U << 17,
	PERF_SAMPLE_REGS_INTR			= 1U << 18,
	PERF_SAMPLE_PHYS_ADDR			= 1U << 19,
	PERF_SAMPLE_AUX				= 1U << 20,
	PERF_SAMPLE_CGROUP			= 1U << 21,
	PERF_SAMPLE_DATA_PAGE_SIZE		= 1U << 22,
	PERF_SAMPLE_CODE_PAGE_SIZE		= 1U << 23,
	PERF_SAMPLE_WEIGHT_STRUCT		= 1U << 24,

	PERF_SAMPLE_MAX = 1U << 25,		/* non-ABI */

	__PERF_SAMPLE_CALLCHAIN_EARLY		= 1ULL << 63, /* non-ABI; पूर्णांकernal use */
पूर्ण;

#घोषणा PERF_SAMPLE_WEIGHT_TYPE	(PERF_SAMPLE_WEIGHT | PERF_SAMPLE_WEIGHT_STRUCT)
/*
 * values to program पूर्णांकo branch_sample_type when PERF_SAMPLE_BRANCH is set
 *
 * If the user करोes not pass priv level inक्रमmation via branch_sample_type,
 * the kernel uses the event's priv level. Branch and event priv levels करो
 * not have to match. Branch priv level is checked क्रम permissions.
 *
 * The branch types can be combined, however BRANCH_ANY covers all types
 * of branches and thereक्रमe it supersedes all the other types.
 */
क्रमागत perf_branch_sample_type_shअगरt अणु
	PERF_SAMPLE_BRANCH_USER_SHIFT		= 0, /* user branches */
	PERF_SAMPLE_BRANCH_KERNEL_SHIFT		= 1, /* kernel branches */
	PERF_SAMPLE_BRANCH_HV_SHIFT		= 2, /* hypervisor branches */

	PERF_SAMPLE_BRANCH_ANY_SHIFT		= 3, /* any branch types */
	PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT	= 4, /* any call branch */
	PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT	= 5, /* any वापस branch */
	PERF_SAMPLE_BRANCH_IND_CALL_SHIFT	= 6, /* indirect calls */
	PERF_SAMPLE_BRANCH_ABORT_TX_SHIFT	= 7, /* transaction पातs */
	PERF_SAMPLE_BRANCH_IN_TX_SHIFT		= 8, /* in transaction */
	PERF_SAMPLE_BRANCH_NO_TX_SHIFT		= 9, /* not in transaction */
	PERF_SAMPLE_BRANCH_COND_SHIFT		= 10, /* conditional branches */

	PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT	= 11, /* call/ret stack */
	PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT	= 12, /* indirect jumps */
	PERF_SAMPLE_BRANCH_CALL_SHIFT		= 13, /* direct call */

	PERF_SAMPLE_BRANCH_NO_FLAGS_SHIFT	= 14, /* no flags */
	PERF_SAMPLE_BRANCH_NO_CYCLES_SHIFT	= 15, /* no cycles */

	PERF_SAMPLE_BRANCH_TYPE_SAVE_SHIFT	= 16, /* save branch type */

	PERF_SAMPLE_BRANCH_HW_INDEX_SHIFT	= 17, /* save low level index of raw branch records */

	PERF_SAMPLE_BRANCH_MAX_SHIFT		/* non-ABI */
पूर्ण;

क्रमागत perf_branch_sample_type अणु
	PERF_SAMPLE_BRANCH_USER		= 1U << PERF_SAMPLE_BRANCH_USER_SHIFT,
	PERF_SAMPLE_BRANCH_KERNEL	= 1U << PERF_SAMPLE_BRANCH_KERNEL_SHIFT,
	PERF_SAMPLE_BRANCH_HV		= 1U << PERF_SAMPLE_BRANCH_HV_SHIFT,

	PERF_SAMPLE_BRANCH_ANY		= 1U << PERF_SAMPLE_BRANCH_ANY_SHIFT,
	PERF_SAMPLE_BRANCH_ANY_CALL	= 1U << PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT,
	PERF_SAMPLE_BRANCH_ANY_RETURN	= 1U << PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT,
	PERF_SAMPLE_BRANCH_IND_CALL	= 1U << PERF_SAMPLE_BRANCH_IND_CALL_SHIFT,
	PERF_SAMPLE_BRANCH_ABORT_TX	= 1U << PERF_SAMPLE_BRANCH_ABORT_TX_SHIFT,
	PERF_SAMPLE_BRANCH_IN_TX	= 1U << PERF_SAMPLE_BRANCH_IN_TX_SHIFT,
	PERF_SAMPLE_BRANCH_NO_TX	= 1U << PERF_SAMPLE_BRANCH_NO_TX_SHIFT,
	PERF_SAMPLE_BRANCH_COND		= 1U << PERF_SAMPLE_BRANCH_COND_SHIFT,

	PERF_SAMPLE_BRANCH_CALL_STACK	= 1U << PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT,
	PERF_SAMPLE_BRANCH_IND_JUMP	= 1U << PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT,
	PERF_SAMPLE_BRANCH_CALL		= 1U << PERF_SAMPLE_BRANCH_CALL_SHIFT,

	PERF_SAMPLE_BRANCH_NO_FLAGS	= 1U << PERF_SAMPLE_BRANCH_NO_FLAGS_SHIFT,
	PERF_SAMPLE_BRANCH_NO_CYCLES	= 1U << PERF_SAMPLE_BRANCH_NO_CYCLES_SHIFT,

	PERF_SAMPLE_BRANCH_TYPE_SAVE	=
		1U << PERF_SAMPLE_BRANCH_TYPE_SAVE_SHIFT,

	PERF_SAMPLE_BRANCH_HW_INDEX	= 1U << PERF_SAMPLE_BRANCH_HW_INDEX_SHIFT,

	PERF_SAMPLE_BRANCH_MAX		= 1U << PERF_SAMPLE_BRANCH_MAX_SHIFT,
पूर्ण;

/*
 * Common flow change classअगरication
 */
क्रमागत अणु
	PERF_BR_UNKNOWN		= 0,	/* unknown */
	PERF_BR_COND		= 1,	/* conditional */
	PERF_BR_UNCOND		= 2,	/* unconditional  */
	PERF_BR_IND		= 3,	/* indirect */
	PERF_BR_CALL		= 4,	/* function call */
	PERF_BR_IND_CALL	= 5,	/* indirect function call */
	PERF_BR_RET		= 6,	/* function वापस */
	PERF_BR_SYSCALL		= 7,	/* syscall */
	PERF_BR_SYSRET		= 8,	/* syscall वापस */
	PERF_BR_COND_CALL	= 9,	/* conditional function call */
	PERF_BR_COND_RET	= 10,	/* conditional function वापस */
	PERF_BR_MAX,
पूर्ण;

#घोषणा PERF_SAMPLE_BRANCH_PLM_ALL \
	(PERF_SAMPLE_BRANCH_USER|\
	 PERF_SAMPLE_BRANCH_KERNEL|\
	 PERF_SAMPLE_BRANCH_HV)

/*
 * Values to determine ABI of the रेजिस्टरs dump.
 */
क्रमागत perf_sample_regs_abi अणु
	PERF_SAMPLE_REGS_ABI_NONE	= 0,
	PERF_SAMPLE_REGS_ABI_32		= 1,
	PERF_SAMPLE_REGS_ABI_64		= 2,
पूर्ण;

/*
 * Values क्रम the memory transaction event qualअगरier, mostly क्रम
 * पात events. Multiple bits can be set.
 */
क्रमागत अणु
	PERF_TXN_ELISION        = (1 << 0), /* From elision */
	PERF_TXN_TRANSACTION    = (1 << 1), /* From transaction */
	PERF_TXN_SYNC           = (1 << 2), /* Inकाष्ठाion is related */
	PERF_TXN_ASYNC          = (1 << 3), /* Inकाष्ठाion not related */
	PERF_TXN_RETRY          = (1 << 4), /* Retry possible */
	PERF_TXN_CONFLICT       = (1 << 5), /* Conflict पात */
	PERF_TXN_CAPACITY_WRITE = (1 << 6), /* Capacity ग_लिखो पात */
	PERF_TXN_CAPACITY_READ  = (1 << 7), /* Capacity पढ़ो पात */

	PERF_TXN_MAX	        = (1 << 8), /* non-ABI */

	/* bits 32..63 are reserved क्रम the पात code */

	PERF_TXN_ABORT_MASK  = (0xffffffffULL << 32),
	PERF_TXN_ABORT_SHIFT = 32,
पूर्ण;

/*
 * The क्रमmat of the data वापसed by पढ़ो() on a perf event fd,
 * as specअगरied by attr.पढ़ो_क्रमmat:
 *
 * काष्ठा पढ़ो_क्रमmat अणु
 *	अणु u64		value;
 *	  अणु u64		समय_enabled; पूर्ण && PERF_FORMAT_TOTAL_TIME_ENABLED
 *	  अणु u64		समय_running; पूर्ण && PERF_FORMAT_TOTAL_TIME_RUNNING
 *	  अणु u64		id;           पूर्ण && PERF_FORMAT_ID
 *	पूर्ण && !PERF_FORMAT_GROUP
 *
 *	अणु u64		nr;
 *	  अणु u64		समय_enabled; पूर्ण && PERF_FORMAT_TOTAL_TIME_ENABLED
 *	  अणु u64		समय_running; पूर्ण && PERF_FORMAT_TOTAL_TIME_RUNNING
 *	  अणु u64		value;
 *	    अणु u64	id;           पूर्ण && PERF_FORMAT_ID
 *	  पूर्ण		cntr[nr];
 *	पूर्ण && PERF_FORMAT_GROUP
 * पूर्ण;
 */
क्रमागत perf_event_पढ़ो_क्रमmat अणु
	PERF_FORMAT_TOTAL_TIME_ENABLED		= 1U << 0,
	PERF_FORMAT_TOTAL_TIME_RUNNING		= 1U << 1,
	PERF_FORMAT_ID				= 1U << 2,
	PERF_FORMAT_GROUP			= 1U << 3,

	PERF_FORMAT_MAX = 1U << 4,		/* non-ABI */
पूर्ण;

#घोषणा PERF_ATTR_SIZE_VER0	64	/* माप first published काष्ठा */
#घोषणा PERF_ATTR_SIZE_VER1	72	/* add: config2 */
#घोषणा PERF_ATTR_SIZE_VER2	80	/* add: branch_sample_type */
#घोषणा PERF_ATTR_SIZE_VER3	96	/* add: sample_regs_user */
					/* add: sample_stack_user */
#घोषणा PERF_ATTR_SIZE_VER4	104	/* add: sample_regs_पूर्णांकr */
#घोषणा PERF_ATTR_SIZE_VER5	112	/* add: aux_watermark */
#घोषणा PERF_ATTR_SIZE_VER6	120	/* add: aux_sample_size */
#घोषणा PERF_ATTR_SIZE_VER7	128	/* add: sig_data */

/*
 * Hardware event_id to monitor via a perक्रमmance monitoring event:
 *
 * @sample_max_stack: Max number of frame poपूर्णांकers in a callchain,
 *		      should be < /proc/sys/kernel/perf_event_max_stack
 */
काष्ठा perf_event_attr अणु

	/*
	 * Major type: hardware/software/tracepoपूर्णांक/etc.
	 */
	__u32			type;

	/*
	 * Size of the attr काष्ठाure, क्रम fwd/bwd compat.
	 */
	__u32			size;

	/*
	 * Type specअगरic configuration inक्रमmation.
	 */
	__u64			config;

	जोड़ अणु
		__u64		sample_period;
		__u64		sample_freq;
	पूर्ण;

	__u64			sample_type;
	__u64			पढ़ो_क्रमmat;

	__u64			disabled       :  1, /* off by शेष        */
				inherit	       :  1, /* children inherit it   */
				pinned	       :  1, /* must always be on PMU */
				exclusive      :  1, /* only group on PMU     */
				exclude_user   :  1, /* करोn't count user      */
				exclude_kernel :  1, /* ditto kernel          */
				exclude_hv     :  1, /* ditto hypervisor      */
				exclude_idle   :  1, /* करोn't count when idle */
				mmap           :  1, /* include mmap data     */
				comm	       :  1, /* include comm data     */
				freq           :  1, /* use freq, not period  */
				inherit_stat   :  1, /* per task counts       */
				enable_on_exec :  1, /* next exec enables     */
				task           :  1, /* trace विभाजन/निकास       */
				watermark      :  1, /* wakeup_watermark      */
				/*
				 * precise_ip:
				 *
				 *  0 - SAMPLE_IP can have arbitrary skid
				 *  1 - SAMPLE_IP must have स्थिरant skid
				 *  2 - SAMPLE_IP requested to have 0 skid
				 *  3 - SAMPLE_IP must have 0 skid
				 *
				 *  See also PERF_RECORD_MISC_EXACT_IP
				 */
				precise_ip     :  2, /* skid स्थिरraपूर्णांक       */
				mmap_data      :  1, /* non-exec mmap data    */
				sample_id_all  :  1, /* sample_type all events */

				exclude_host   :  1, /* करोn't count in host   */
				exclude_guest  :  1, /* करोn't count in guest  */

				exclude_callchain_kernel : 1, /* exclude kernel callchains */
				exclude_callchain_user   : 1, /* exclude user callchains */
				mmap2          :  1, /* include mmap with inode data     */
				comm_exec      :  1, /* flag comm events that are due to an exec */
				use_घड़ीid    :  1, /* use @घड़ीid क्रम समय fields */
				context_चयन :  1, /* context चयन data */
				ग_लिखो_backward :  1, /* Write ring buffer from end to beginning */
				namespaces     :  1, /* include namespaces data */
				ksymbol        :  1, /* include ksymbol events */
				bpf_event      :  1, /* include bpf events */
				aux_output     :  1, /* generate AUX records instead of events */
				cgroup         :  1, /* include cgroup events */
				text_poke      :  1, /* include text poke events */
				build_id       :  1, /* use build id in mmap2 events */
				inherit_thपढ़ो :  1, /* children only inherit अगर cloned with CLONE_THREAD */
				हटाओ_on_exec :  1, /* event is हटाओd from task on exec */
				sigtrap        :  1, /* send synchronous SIGTRAP on event */
				__reserved_1   : 26;

	जोड़ अणु
		__u32		wakeup_events;	  /* wakeup every n events */
		__u32		wakeup_watermark; /* bytes beक्रमe wakeup   */
	पूर्ण;

	__u32			bp_type;
	जोड़ अणु
		__u64		bp_addr;
		__u64		kprobe_func; /* क्रम perf_kprobe */
		__u64		uprobe_path; /* क्रम perf_uprobe */
		__u64		config1; /* extension of config */
	पूर्ण;
	जोड़ अणु
		__u64		bp_len;
		__u64		kprobe_addr; /* when kprobe_func == शून्य */
		__u64		probe_offset; /* क्रम perf_[k,u]probe */
		__u64		config2; /* extension of config1 */
	पूर्ण;
	__u64	branch_sample_type; /* क्रमागत perf_branch_sample_type */

	/*
	 * Defines set of user regs to dump on samples.
	 * See यंत्र/perf_regs.h क्रम details.
	 */
	__u64	sample_regs_user;

	/*
	 * Defines size of the user stack to dump on samples.
	 */
	__u32	sample_stack_user;

	__s32	घड़ीid;
	/*
	 * Defines set of regs to dump क्रम each sample
	 * state captured on:
	 *  - precise = 0: PMU पूर्णांकerrupt
	 *  - precise > 0: sampled inकाष्ठाion
	 *
	 * See यंत्र/perf_regs.h क्रम details.
	 */
	__u64	sample_regs_पूर्णांकr;

	/*
	 * Wakeup watermark क्रम AUX area
	 */
	__u32	aux_watermark;
	__u16	sample_max_stack;
	__u16	__reserved_2;
	__u32	aux_sample_size;
	__u32	__reserved_3;

	/*
	 * User provided data अगर sigtrap=1, passed back to user via
	 * siginfo_t::si_perf_data, e.g. to permit user to identअगरy the event.
	 */
	__u64	sig_data;
पूर्ण;

/*
 * Structure used by below PERF_EVENT_IOC_QUERY_BPF command
 * to query bpf programs attached to the same perf tracepoपूर्णांक
 * as the given perf event.
 */
काष्ठा perf_event_query_bpf अणु
	/*
	 * The below ids array length
	 */
	__u32	ids_len;
	/*
	 * Set by the kernel to indicate the number of
	 * available programs
	 */
	__u32	prog_cnt;
	/*
	 * User provided buffer to store program ids
	 */
	__u32	ids[0];
पूर्ण;

/*
 * Ioctls that can be करोne on a perf event fd:
 */
#घोषणा PERF_EVENT_IOC_ENABLE			_IO ('$', 0)
#घोषणा PERF_EVENT_IOC_DISABLE			_IO ('$', 1)
#घोषणा PERF_EVENT_IOC_REFRESH			_IO ('$', 2)
#घोषणा PERF_EVENT_IOC_RESET			_IO ('$', 3)
#घोषणा PERF_EVENT_IOC_PERIOD			_IOW('$', 4, __u64)
#घोषणा PERF_EVENT_IOC_SET_OUTPUT		_IO ('$', 5)
#घोषणा PERF_EVENT_IOC_SET_FILTER		_IOW('$', 6, अक्षर *)
#घोषणा PERF_EVENT_IOC_ID			_IOR('$', 7, __u64 *)
#घोषणा PERF_EVENT_IOC_SET_BPF			_IOW('$', 8, __u32)
#घोषणा PERF_EVENT_IOC_PAUSE_OUTPUT		_IOW('$', 9, __u32)
#घोषणा PERF_EVENT_IOC_QUERY_BPF		_IOWR('$', 10, काष्ठा perf_event_query_bpf *)
#घोषणा PERF_EVENT_IOC_MODIFY_ATTRIBUTES	_IOW('$', 11, काष्ठा perf_event_attr *)

क्रमागत perf_event_ioc_flags अणु
	PERF_IOC_FLAG_GROUP		= 1U << 0,
पूर्ण;

/*
 * Structure of the page that can be mapped via mmap
 */
काष्ठा perf_event_mmap_page अणु
	__u32	version;		/* version number of this काष्ठाure */
	__u32	compat_version;		/* lowest version this is compat with */

	/*
	 * Bits needed to पढ़ो the hw events in user-space.
	 *
	 *   u32 seq, समय_mult, समय_shअगरt, index, width;
	 *   u64 count, enabled, running;
	 *   u64 cyc, समय_offset;
	 *   s64 pmc = 0;
	 *
	 *   करो अणु
	 *     seq = pc->lock;
	 *     barrier()
	 *
	 *     enabled = pc->समय_enabled;
	 *     running = pc->समय_running;
	 *
	 *     अगर (pc->cap_usr_समय && enabled != running) अणु
	 *       cyc = rdtsc();
	 *       समय_offset = pc->समय_offset;
	 *       समय_mult   = pc->समय_mult;
	 *       समय_shअगरt  = pc->समय_shअगरt;
	 *     पूर्ण
	 *
	 *     index = pc->index;
	 *     count = pc->offset;
	 *     अगर (pc->cap_user_rdpmc && index) अणु
	 *       width = pc->pmc_width;
	 *       pmc = rdpmc(index - 1);
	 *     पूर्ण
	 *
	 *     barrier();
	 *   पूर्ण जबतक (pc->lock != seq);
	 *
	 * NOTE: क्रम obvious reason this only works on self-monitoring
	 *       processes.
	 */
	__u32	lock;			/* seqlock क्रम synchronization */
	__u32	index;			/* hardware event identअगरier */
	__s64	offset;			/* add to hardware event value */
	__u64	समय_enabled;		/* समय event active */
	__u64	समय_running;		/* समय event on cpu */
	जोड़ अणु
		__u64	capabilities;
		काष्ठा अणु
			__u64	cap_bit0		: 1, /* Always 0, deprecated, see commit 860f085b74e9 */
				cap_bit0_is_deprecated	: 1, /* Always 1, संकेतs that bit 0 is zero */

				cap_user_rdpmc		: 1, /* The RDPMC inकाष्ठाion can be used to पढ़ो counts */
				cap_user_समय		: 1, /* The समय_अणुshअगरt,mult,offsetपूर्ण fields are used */
				cap_user_समय_zero	: 1, /* The समय_zero field is used */
				cap_user_समय_लघु	: 1, /* the समय_अणुcycle,maskपूर्ण fields are used */
				cap_____res		: 58;
		पूर्ण;
	पूर्ण;

	/*
	 * If cap_user_rdpmc this field provides the bit-width of the value
	 * पढ़ो using the rdpmc() or equivalent inकाष्ठाion. This can be used
	 * to sign extend the result like:
	 *
	 *   pmc <<= 64 - width;
	 *   pmc >>= 64 - width; // चिन्हित shअगरt right
	 *   count += pmc;
	 */
	__u16	pmc_width;

	/*
	 * If cap_usr_समय the below fields can be used to compute the समय
	 * delta since समय_enabled (in ns) using rdtsc or similar.
	 *
	 *   u64 quot, rem;
	 *   u64 delta;
	 *
	 *   quot = (cyc >> समय_shअगरt);
	 *   rem = cyc & (((u64)1 << समय_shअगरt) - 1);
	 *   delta = समय_offset + quot * समय_mult +
	 *              ((rem * समय_mult) >> समय_shअगरt);
	 *
	 * Where समय_offset,समय_mult,समय_shअगरt and cyc are पढ़ो in the
	 * seqcount loop described above. This delta can then be added to
	 * enabled and possible running (अगर index), improving the scaling:
	 *
	 *   enabled += delta;
	 *   अगर (index)
	 *     running += delta;
	 *
	 *   quot = count / running;
	 *   rem  = count % running;
	 *   count = quot * enabled + (rem * enabled) / running;
	 */
	__u16	समय_shअगरt;
	__u32	समय_mult;
	__u64	समय_offset;
	/*
	 * If cap_usr_समय_zero, the hardware घड़ी (e.g. TSC) can be calculated
	 * from sample बारtamps.
	 *
	 *   समय = बारtamp - समय_zero;
	 *   quot = समय / समय_mult;
	 *   rem  = समय % समय_mult;
	 *   cyc = (quot << समय_shअगरt) + (rem << समय_shअगरt) / समय_mult;
	 *
	 * And vice versa:
	 *
	 *   quot = cyc >> समय_shअगरt;
	 *   rem  = cyc & (((u64)1 << समय_shअगरt) - 1);
	 *   बारtamp = समय_zero + quot * समय_mult +
	 *               ((rem * समय_mult) >> समय_shअगरt);
	 */
	__u64	समय_zero;

	__u32	size;			/* Header size up to __reserved[] fields. */
	__u32	__reserved_1;

	/*
	 * If cap_usr_समय_लघु, the hardware घड़ी is less than 64bit wide
	 * and we must compute the 'cyc' value, as used by cap_usr_समय, as:
	 *
	 *   cyc = समय_cycles + ((cyc - समय_cycles) & समय_mask)
	 *
	 * NOTE: this क्रमm is explicitly chosen such that cap_usr_समय_लघु
	 *       is a correction on top of cap_usr_समय, and code that करोesn't
	 *       know about cap_usr_समय_लघु still works under the assumption
	 *       the counter करोesn't wrap.
	 */
	__u64	समय_cycles;
	__u64	समय_mask;

		/*
		 * Hole क्रम extension of the self monitor capabilities
		 */

	__u8	__reserved[116*8];	/* align to 1k. */

	/*
	 * Control data क्रम the mmap() data buffer.
	 *
	 * User-space पढ़ोing the @data_head value should issue an smp_rmb(),
	 * after पढ़ोing this value.
	 *
	 * When the mapping is PROT_WRITE the @data_tail value should be
	 * written by userspace to reflect the last पढ़ो data, after issueing
	 * an smp_mb() to separate the data पढ़ो from the ->data_tail store.
	 * In this हाल the kernel will not over-ग_लिखो unपढ़ो data.
	 *
	 * See perf_output_put_handle() क्रम the data ordering.
	 *
	 * data_अणुoffset,sizeपूर्ण indicate the location and size of the perf record
	 * buffer within the mmapped area.
	 */
	__u64   data_head;		/* head in the data section */
	__u64	data_tail;		/* user-space written tail */
	__u64	data_offset;		/* where the buffer starts */
	__u64	data_size;		/* data buffer size */

	/*
	 * AUX area is defined by aux_अणुoffset,sizeपूर्ण fields that should be set
	 * by the userspace, so that
	 *
	 *   aux_offset >= data_offset + data_size
	 *
	 * prior to mmap()ing it. Size of the mmap()ed area should be aux_size.
	 *
	 * Ring buffer poपूर्णांकers aux_अणुhead,tailपूर्ण have the same semantics as
	 * data_अणुhead,tailपूर्ण and same ordering rules apply.
	 */
	__u64	aux_head;
	__u64	aux_tail;
	__u64	aux_offset;
	__u64	aux_size;
पूर्ण;

/*
 * The current state of perf_event_header::misc bits usage:
 * ('|' used bit, '-' unused bit)
 *
 *  012         CDEF
 *  |||---------||||
 *
 *  Where:
 *    0-2     CPUMODE_MASK
 *
 *    C       PROC_MAP_PARSE_TIMEOUT
 *    D       MMAP_DATA / COMM_EXEC / FORK_EXEC / SWITCH_OUT
 *    E       MMAP_BUILD_ID / EXACT_IP / SCHED_OUT_PREEMPT
 *    F       (reserved)
 */

#घोषणा PERF_RECORD_MISC_CPUMODE_MASK		(7 << 0)
#घोषणा PERF_RECORD_MISC_CPUMODE_UNKNOWN	(0 << 0)
#घोषणा PERF_RECORD_MISC_KERNEL			(1 << 0)
#घोषणा PERF_RECORD_MISC_USER			(2 << 0)
#घोषणा PERF_RECORD_MISC_HYPERVISOR		(3 << 0)
#घोषणा PERF_RECORD_MISC_GUEST_KERNEL		(4 << 0)
#घोषणा PERF_RECORD_MISC_GUEST_USER		(5 << 0)

/*
 * Indicates that /proc/PID/maps parsing are truncated by समय out.
 */
#घोषणा PERF_RECORD_MISC_PROC_MAP_PARSE_TIMEOUT	(1 << 12)
/*
 * Following PERF_RECORD_MISC_* are used on dअगरferent
 * events, so can reuse the same bit position:
 *
 *   PERF_RECORD_MISC_MMAP_DATA  - PERF_RECORD_MMAP* events
 *   PERF_RECORD_MISC_COMM_EXEC  - PERF_RECORD_COMM event
 *   PERF_RECORD_MISC_FORK_EXEC  - PERF_RECORD_FORK event (perf पूर्णांकernal)
 *   PERF_RECORD_MISC_SWITCH_OUT - PERF_RECORD_SWITCH* events
 */
#घोषणा PERF_RECORD_MISC_MMAP_DATA		(1 << 13)
#घोषणा PERF_RECORD_MISC_COMM_EXEC		(1 << 13)
#घोषणा PERF_RECORD_MISC_FORK_EXEC		(1 << 13)
#घोषणा PERF_RECORD_MISC_SWITCH_OUT		(1 << 13)
/*
 * These PERF_RECORD_MISC_* flags below are safely reused
 * क्रम the following events:
 *
 *   PERF_RECORD_MISC_EXACT_IP           - PERF_RECORD_SAMPLE of precise events
 *   PERF_RECORD_MISC_SWITCH_OUT_PREEMPT - PERF_RECORD_SWITCH* events
 *   PERF_RECORD_MISC_MMAP_BUILD_ID      - PERF_RECORD_MMAP2 event
 *
 *
 * PERF_RECORD_MISC_EXACT_IP:
 *   Indicates that the content of PERF_SAMPLE_IP poपूर्णांकs to
 *   the actual inकाष्ठाion that triggered the event. See also
 *   perf_event_attr::precise_ip.
 *
 * PERF_RECORD_MISC_SWITCH_OUT_PREEMPT:
 *   Indicates that thपढ़ो was preempted in TASK_RUNNING state.
 *
 * PERF_RECORD_MISC_MMAP_BUILD_ID:
 *   Indicates that mmap2 event carries build id data.
 */
#घोषणा PERF_RECORD_MISC_EXACT_IP		(1 << 14)
#घोषणा PERF_RECORD_MISC_SWITCH_OUT_PREEMPT	(1 << 14)
#घोषणा PERF_RECORD_MISC_MMAP_BUILD_ID		(1 << 14)
/*
 * Reserve the last bit to indicate some extended misc field
 */
#घोषणा PERF_RECORD_MISC_EXT_RESERVED		(1 << 15)

काष्ठा perf_event_header अणु
	__u32	type;
	__u16	misc;
	__u16	size;
पूर्ण;

काष्ठा perf_ns_link_info अणु
	__u64	dev;
	__u64	ino;
पूर्ण;

क्रमागत अणु
	NET_NS_INDEX		= 0,
	UTS_NS_INDEX		= 1,
	IPC_NS_INDEX		= 2,
	PID_NS_INDEX		= 3,
	USER_NS_INDEX		= 4,
	MNT_NS_INDEX		= 5,
	CGROUP_NS_INDEX		= 6,

	NR_NAMESPACES,		/* number of available namespaces */
पूर्ण;

क्रमागत perf_event_type अणु

	/*
	 * If perf_event_attr.sample_id_all is set then all event types will
	 * have the sample_type selected fields related to where/when
	 * (identity) an event took place (TID, TIME, ID, STREAM_ID, CPU,
	 * IDENTIFIER) described in PERF_RECORD_SAMPLE below, it will be stashed
	 * just after the perf_event_header and the fields alपढ़ोy present क्रम
	 * the existing fields, i.e. at the end of the payload. That way a newer
	 * perf.data file will be supported by older perf tools, with these new
	 * optional fields being ignored.
	 *
	 * काष्ठा sample_id अणु
	 * 	अणु u32			pid, tid; पूर्ण && PERF_SAMPLE_TID
	 * 	अणु u64			समय;     पूर्ण && PERF_SAMPLE_TIME
	 * 	अणु u64			id;       पूर्ण && PERF_SAMPLE_ID
	 * 	अणु u64			stream_id;पूर्ण && PERF_SAMPLE_STREAM_ID
	 * 	अणु u32			cpu, res; पूर्ण && PERF_SAMPLE_CPU
	 *	अणु u64			id;	  पूर्ण && PERF_SAMPLE_IDENTIFIER
	 * पूर्ण && perf_event_attr::sample_id_all
	 *
	 * Note that PERF_SAMPLE_IDENTIFIER duplicates PERF_SAMPLE_ID.  The
	 * advantage of PERF_SAMPLE_IDENTIFIER is that its position is fixed
	 * relative to header.size.
	 */

	/*
	 * The MMAP events record the PROT_EXEC mappings so that we can
	 * correlate userspace IPs to code. They have the following काष्ठाure:
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *
	 *	u32				pid, tid;
	 *	u64				addr;
	 *	u64				len;
	 *	u64				pgoff;
	 *	अक्षर				filename[];
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_MMAP			= 1,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u64				id;
	 *	u64				lost;
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_LOST			= 2,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *
	 *	u32				pid, tid;
	 *	अक्षर				comm[];
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_COMM			= 3,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u32				pid, ppid;
	 *	u32				tid, ptid;
	 *	u64				समय;
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_EXIT			= 4,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u64				समय;
	 *	u64				id;
	 *	u64				stream_id;
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_THROTTLE			= 5,
	PERF_RECORD_UNTHROTTLE			= 6,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u32				pid, ppid;
	 *	u32				tid, ptid;
	 *	u64				समय;
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_FORK			= 7,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u32				pid, tid;
	 *
	 *	काष्ठा पढ़ो_क्रमmat		values;
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_READ			= 8,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *
	 *	#
	 *	# Note that PERF_SAMPLE_IDENTIFIER duplicates PERF_SAMPLE_ID.
	 *	# The advantage of PERF_SAMPLE_IDENTIFIER is that its position
	 *	# is fixed relative to header.
	 *	#
	 *
	 *	अणु u64			id;	  पूर्ण && PERF_SAMPLE_IDENTIFIER
	 *	अणु u64			ip;	  पूर्ण && PERF_SAMPLE_IP
	 *	अणु u32			pid, tid; पूर्ण && PERF_SAMPLE_TID
	 *	अणु u64			समय;     पूर्ण && PERF_SAMPLE_TIME
	 *	अणु u64			addr;     पूर्ण && PERF_SAMPLE_ADDR
	 *	अणु u64			id;	  पूर्ण && PERF_SAMPLE_ID
	 *	अणु u64			stream_id;पूर्ण && PERF_SAMPLE_STREAM_ID
	 *	अणु u32			cpu, res; पूर्ण && PERF_SAMPLE_CPU
	 *	अणु u64			period;   पूर्ण && PERF_SAMPLE_PERIOD
	 *
	 *	अणु काष्ठा पढ़ो_क्रमmat	values;	  पूर्ण && PERF_SAMPLE_READ
	 *
	 *	अणु u64			nr,
	 *	  u64			ips[nr];  पूर्ण && PERF_SAMPLE_CALLCHAIN
	 *
	 *	#
	 *	# The RAW record below is opaque data wrt the ABI
	 *	#
	 *	# That is, the ABI करोesn't make any promises wrt to
	 *	# the stability of its content, it may vary depending
	 *	# on event, hardware, kernel version and phase of
	 *	# the moon.
	 *	#
	 *	# In other words, PERF_SAMPLE_RAW contents are not an ABI.
	 *	#
	 *
	 *	अणु u32			size;
	 *	  अक्षर                  data[size];पूर्ण&& PERF_SAMPLE_RAW
	 *
	 *	अणु u64                   nr;
	 *	  अणु u64	hw_idx; पूर्ण && PERF_SAMPLE_BRANCH_HW_INDEX
	 *        अणु u64 from, to, flags पूर्ण lbr[nr];
	 *      पूर्ण && PERF_SAMPLE_BRANCH_STACK
	 *
	 * 	अणु u64			abi; # क्रमागत perf_sample_regs_abi
	 * 	  u64			regs[weight(mask)]; पूर्ण && PERF_SAMPLE_REGS_USER
	 *
	 * 	अणु u64			size;
	 * 	  अक्षर			data[size];
	 * 	  u64			dyn_size; पूर्ण && PERF_SAMPLE_STACK_USER
	 *
	 *	अणु जोड़ perf_sample_weight
	 *	 अणु
	 *		u64		full; && PERF_SAMPLE_WEIGHT
	 *	#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	 *		काष्ठा अणु
	 *			u32	var1_dw;
	 *			u16	var2_w;
	 *			u16	var3_w;
	 *		पूर्ण && PERF_SAMPLE_WEIGHT_STRUCT
	 *	#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	 *		काष्ठा अणु
	 *			u16	var3_w;
	 *			u16	var2_w;
	 *			u32	var1_dw;
	 *		पूर्ण && PERF_SAMPLE_WEIGHT_STRUCT
	 *	#पूर्ण_अगर
	 *	 पूर्ण
	 *	पूर्ण
	 *	अणु u64			data_src; पूर्ण && PERF_SAMPLE_DATA_SRC
	 *	अणु u64			transaction; पूर्ण && PERF_SAMPLE_TRANSACTION
	 *	अणु u64			abi; # क्रमागत perf_sample_regs_abi
	 *	  u64			regs[weight(mask)]; पूर्ण && PERF_SAMPLE_REGS_INTR
	 *	अणु u64			phys_addr;पूर्ण && PERF_SAMPLE_PHYS_ADDR
	 *	अणु u64			size;
	 *	  अक्षर			data[size]; पूर्ण && PERF_SAMPLE_AUX
	 *	अणु u64			data_page_size;पूर्ण && PERF_SAMPLE_DATA_PAGE_SIZE
	 *	अणु u64			code_page_size;पूर्ण && PERF_SAMPLE_CODE_PAGE_SIZE
	 * पूर्ण;
	 */
	PERF_RECORD_SAMPLE			= 9,

	/*
	 * The MMAP2 records are an augmented version of MMAP, they add
	 * maj, min, ino numbers to be used to uniquely identअगरy each mapping
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *
	 *	u32				pid, tid;
	 *	u64				addr;
	 *	u64				len;
	 *	u64				pgoff;
	 *	जोड़ अणु
	 *		काष्ठा अणु
	 *			u32		maj;
	 *			u32		min;
	 *			u64		ino;
	 *			u64		ino_generation;
	 *		पूर्ण;
	 *		काष्ठा अणु
	 *			u8		build_id_size;
	 *			u8		__reserved_1;
	 *			u16		__reserved_2;
	 *			u8		build_id[20];
	 *		पूर्ण;
	 *	पूर्ण;
	 *	u32				prot, flags;
	 *	अक्षर				filename[];
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_MMAP2			= 10,

	/*
	 * Records that new data landed in the AUX buffer part.
	 *
	 * काष्ठा अणु
	 * 	काष्ठा perf_event_header	header;
	 *
	 * 	u64				aux_offset;
	 * 	u64				aux_size;
	 *	u64				flags;
	 * 	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_AUX				= 11,

	/*
	 * Indicates that inकाष्ठाion trace has started
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u32				pid;
	 *	u32				tid;
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_ITRACE_START		= 12,

	/*
	 * Records the dropped/lost sample number.
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *
	 *	u64				lost;
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_LOST_SAMPLES		= 13,

	/*
	 * Records a context चयन in or out (flagged by
	 * PERF_RECORD_MISC_SWITCH_OUT). See also
	 * PERF_RECORD_SWITCH_CPU_WIDE.
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_SWITCH			= 14,

	/*
	 * CPU-wide version of PERF_RECORD_SWITCH with next_prev_pid and
	 * next_prev_tid that are the next (चयनing out) or previous
	 * (चयनing in) pid/tid.
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u32				next_prev_pid;
	 *	u32				next_prev_tid;
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_SWITCH_CPU_WIDE		= 15,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u32				pid;
	 *	u32				tid;
	 *	u64				nr_namespaces;
	 *	अणु u64				dev, inode; पूर्ण [nr_namespaces];
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_NAMESPACES			= 16,

	/*
	 * Record ksymbol रेजिस्टर/unरेजिस्टर events:
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u64				addr;
	 *	u32				len;
	 *	u16				ksym_type;
	 *	u16				flags;
	 *	अक्षर				name[];
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_KSYMBOL			= 17,

	/*
	 * Record bpf events:
	 *  क्रमागत perf_bpf_event_type अणु
	 *	PERF_BPF_EVENT_UNKNOWN		= 0,
	 *	PERF_BPF_EVENT_PROG_LOAD	= 1,
	 *	PERF_BPF_EVENT_PROG_UNLOAD	= 2,
	 *  पूर्ण;
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u16				type;
	 *	u16				flags;
	 *	u32				id;
	 *	u8				tag[BPF_TAG_SIZE];
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_BPF_EVENT			= 18,

	/*
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u64				id;
	 *	अक्षर				path[];
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_CGROUP			= 19,

	/*
	 * Records changes to kernel text i.e. self-modअगरied code. 'old_len' is
	 * the number of old bytes, 'new_len' is the number of new bytes. Either
	 * 'old_len' or 'new_len' may be zero to indicate, क्रम example, the
	 * addition or removal of a trampoline. 'bytes' contains the old bytes
	 * followed immediately by the new bytes.
	 *
	 * काष्ठा अणु
	 *	काष्ठा perf_event_header	header;
	 *	u64				addr;
	 *	u16				old_len;
	 *	u16				new_len;
	 *	u8				bytes[];
	 *	काष्ठा sample_id		sample_id;
	 * पूर्ण;
	 */
	PERF_RECORD_TEXT_POKE			= 20,

	PERF_RECORD_MAX,			/* non-ABI */
पूर्ण;

क्रमागत perf_record_ksymbol_type अणु
	PERF_RECORD_KSYMBOL_TYPE_UNKNOWN	= 0,
	PERF_RECORD_KSYMBOL_TYPE_BPF		= 1,
	/*
	 * Out of line code such as kprobe-replaced inकाष्ठाions or optimized
	 * kprobes or ftrace trampolines.
	 */
	PERF_RECORD_KSYMBOL_TYPE_OOL		= 2,
	PERF_RECORD_KSYMBOL_TYPE_MAX		/* non-ABI */
पूर्ण;

#घोषणा PERF_RECORD_KSYMBOL_FLAGS_UNREGISTER	(1 << 0)

क्रमागत perf_bpf_event_type अणु
	PERF_BPF_EVENT_UNKNOWN		= 0,
	PERF_BPF_EVENT_PROG_LOAD	= 1,
	PERF_BPF_EVENT_PROG_UNLOAD	= 2,
	PERF_BPF_EVENT_MAX,		/* non-ABI */
पूर्ण;

#घोषणा PERF_MAX_STACK_DEPTH		127
#घोषणा PERF_MAX_CONTEXTS_PER_STACK	  8

क्रमागत perf_callchain_context अणु
	PERF_CONTEXT_HV			= (__u64)-32,
	PERF_CONTEXT_KERNEL		= (__u64)-128,
	PERF_CONTEXT_USER		= (__u64)-512,

	PERF_CONTEXT_GUEST		= (__u64)-2048,
	PERF_CONTEXT_GUEST_KERNEL	= (__u64)-2176,
	PERF_CONTEXT_GUEST_USER		= (__u64)-2560,

	PERF_CONTEXT_MAX		= (__u64)-4095,
पूर्ण;

/**
 * PERF_RECORD_AUX::flags bits
 */
#घोषणा PERF_AUX_FLAG_TRUNCATED			0x01	/* record was truncated to fit */
#घोषणा PERF_AUX_FLAG_OVERWRITE			0x02	/* snapshot from overग_लिखो mode */
#घोषणा PERF_AUX_FLAG_PARTIAL			0x04	/* record contains gaps */
#घोषणा PERF_AUX_FLAG_COLLISION			0x08	/* sample collided with another */
#घोषणा PERF_AUX_FLAG_PMU_FORMAT_TYPE_MASK	0xff00	/* PMU specअगरic trace क्रमmat type */

/* CoreSight PMU AUX buffer क्रमmats */
#घोषणा PERF_AUX_FLAG_CORESIGHT_FORMAT_CORESIGHT	0x0000 /* Default क्रम backward compatibility */
#घोषणा PERF_AUX_FLAG_CORESIGHT_FORMAT_RAW		0x0100 /* Raw क्रमmat of the source */

#घोषणा PERF_FLAG_FD_NO_GROUP		(1UL << 0)
#घोषणा PERF_FLAG_FD_OUTPUT		(1UL << 1)
#घोषणा PERF_FLAG_PID_CGROUP		(1UL << 2) /* pid=cgroup id, per-cpu mode only */
#घोषणा PERF_FLAG_FD_CLOEXEC		(1UL << 3) /* O_CLOEXEC */

#अगर defined(__LITTLE_ENDIAN_BITFIELD)
जोड़ perf_mem_data_src अणु
	__u64 val;
	काष्ठा अणु
		__u64   mem_op:5,	/* type of opcode */
			mem_lvl:14,	/* memory hierarchy level */
			mem_snoop:5,	/* snoop mode */
			mem_lock:2,	/* lock instr */
			mem_dtlb:7,	/* tlb access */
			mem_lvl_num:4,	/* memory hierarchy level number */
			mem_remote:1,   /* remote */
			mem_snoopx:2,	/* snoop mode, ext */
			mem_blk:3,	/* access blocked */
			mem_rsvd:21;
	पूर्ण;
पूर्ण;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
जोड़ perf_mem_data_src अणु
	__u64 val;
	काष्ठा अणु
		__u64	mem_rsvd:21,
			mem_blk:3,	/* access blocked */
			mem_snoopx:2,	/* snoop mode, ext */
			mem_remote:1,   /* remote */
			mem_lvl_num:4,	/* memory hierarchy level number */
			mem_dtlb:7,	/* tlb access */
			mem_lock:2,	/* lock instr */
			mem_snoop:5,	/* snoop mode */
			mem_lvl:14,	/* memory hierarchy level */
			mem_op:5;	/* type of opcode */
	पूर्ण;
पूर्ण;
#अन्यथा
#त्रुटि "Unknown endianness"
#पूर्ण_अगर

/* type of opcode (load/store/prefetch,code) */
#घोषणा PERF_MEM_OP_NA		0x01 /* not available */
#घोषणा PERF_MEM_OP_LOAD	0x02 /* load inकाष्ठाion */
#घोषणा PERF_MEM_OP_STORE	0x04 /* store inकाष्ठाion */
#घोषणा PERF_MEM_OP_PFETCH	0x08 /* prefetch */
#घोषणा PERF_MEM_OP_EXEC	0x10 /* code (execution) */
#घोषणा PERF_MEM_OP_SHIFT	0

/* memory hierarchy (memory level, hit or miss) */
#घोषणा PERF_MEM_LVL_NA		0x01  /* not available */
#घोषणा PERF_MEM_LVL_HIT	0x02  /* hit level */
#घोषणा PERF_MEM_LVL_MISS	0x04  /* miss level  */
#घोषणा PERF_MEM_LVL_L1		0x08  /* L1 */
#घोषणा PERF_MEM_LVL_LFB	0x10  /* Line Fill Buffer */
#घोषणा PERF_MEM_LVL_L2		0x20  /* L2 */
#घोषणा PERF_MEM_LVL_L3		0x40  /* L3 */
#घोषणा PERF_MEM_LVL_LOC_RAM	0x80  /* Local DRAM */
#घोषणा PERF_MEM_LVL_REM_RAM1	0x100 /* Remote DRAM (1 hop) */
#घोषणा PERF_MEM_LVL_REM_RAM2	0x200 /* Remote DRAM (2 hops) */
#घोषणा PERF_MEM_LVL_REM_CCE1	0x400 /* Remote Cache (1 hop) */
#घोषणा PERF_MEM_LVL_REM_CCE2	0x800 /* Remote Cache (2 hops) */
#घोषणा PERF_MEM_LVL_IO		0x1000 /* I/O memory */
#घोषणा PERF_MEM_LVL_UNC	0x2000 /* Uncached memory */
#घोषणा PERF_MEM_LVL_SHIFT	5

#घोषणा PERF_MEM_REMOTE_REMOTE	0x01  /* Remote */
#घोषणा PERF_MEM_REMOTE_SHIFT	37

#घोषणा PERF_MEM_LVLNUM_L1	0x01 /* L1 */
#घोषणा PERF_MEM_LVLNUM_L2	0x02 /* L2 */
#घोषणा PERF_MEM_LVLNUM_L3	0x03 /* L3 */
#घोषणा PERF_MEM_LVLNUM_L4	0x04 /* L4 */
/* 5-0xa available */
#घोषणा PERF_MEM_LVLNUM_ANY_CACHE 0x0b /* Any cache */
#घोषणा PERF_MEM_LVLNUM_LFB	0x0c /* LFB */
#घोषणा PERF_MEM_LVLNUM_RAM	0x0d /* RAM */
#घोषणा PERF_MEM_LVLNUM_PMEM	0x0e /* PMEM */
#घोषणा PERF_MEM_LVLNUM_NA	0x0f /* N/A */

#घोषणा PERF_MEM_LVLNUM_SHIFT	33

/* snoop mode */
#घोषणा PERF_MEM_SNOOP_NA	0x01 /* not available */
#घोषणा PERF_MEM_SNOOP_NONE	0x02 /* no snoop */
#घोषणा PERF_MEM_SNOOP_HIT	0x04 /* snoop hit */
#घोषणा PERF_MEM_SNOOP_MISS	0x08 /* snoop miss */
#घोषणा PERF_MEM_SNOOP_HITM	0x10 /* snoop hit modअगरied */
#घोषणा PERF_MEM_SNOOP_SHIFT	19

#घोषणा PERF_MEM_SNOOPX_FWD	0x01 /* क्रमward */
/* 1 मुक्त */
#घोषणा PERF_MEM_SNOOPX_SHIFT  38

/* locked inकाष्ठाion */
#घोषणा PERF_MEM_LOCK_NA	0x01 /* not available */
#घोषणा PERF_MEM_LOCK_LOCKED	0x02 /* locked transaction */
#घोषणा PERF_MEM_LOCK_SHIFT	24

/* TLB access */
#घोषणा PERF_MEM_TLB_NA		0x01 /* not available */
#घोषणा PERF_MEM_TLB_HIT	0x02 /* hit level */
#घोषणा PERF_MEM_TLB_MISS	0x04 /* miss level */
#घोषणा PERF_MEM_TLB_L1		0x08 /* L1 */
#घोषणा PERF_MEM_TLB_L2		0x10 /* L2 */
#घोषणा PERF_MEM_TLB_WK		0x20 /* Hardware Walker*/
#घोषणा PERF_MEM_TLB_OS		0x40 /* OS fault handler */
#घोषणा PERF_MEM_TLB_SHIFT	26

/* Access blocked */
#घोषणा PERF_MEM_BLK_NA		0x01 /* not available */
#घोषणा PERF_MEM_BLK_DATA	0x02 /* data could not be क्रमwarded */
#घोषणा PERF_MEM_BLK_ADDR	0x04 /* address conflict */
#घोषणा PERF_MEM_BLK_SHIFT	40

#घोषणा PERF_MEM_S(a, s) \
	(((__u64)PERF_MEM_##a##_##s) << PERF_MEM_##a##_SHIFT)

/*
 * single taken branch record layout:
 *
 *      from: source inकाष्ठाion (may not always be a branch insn)
 *        to: branch target
 *   mispred: branch target was mispredicted
 * predicted: branch target was predicted
 *
 * support क्रम mispred, predicted is optional. In हाल it
 * is not supported mispred = predicted = 0.
 *
 *     in_tx: running in a hardware transaction
 *     पात: पातing a hardware transaction
 *    cycles: cycles from last branch (or 0 अगर not supported)
 *      type: branch type
 */
काष्ठा perf_branch_entry अणु
	__u64	from;
	__u64	to;
	__u64	mispred:1,  /* target mispredicted */
		predicted:1,/* target predicted */
		in_tx:1,    /* in transaction */
		पात:1,    /* transaction पात */
		cycles:16,  /* cycle count to last branch */
		type:4,     /* branch type */
		reserved:40;
पूर्ण;

जोड़ perf_sample_weight अणु
	__u64		full;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	काष्ठा अणु
		__u32	var1_dw;
		__u16	var2_w;
		__u16	var3_w;
	पूर्ण;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	काष्ठा अणु
		__u16	var3_w;
		__u16	var2_w;
		__u32	var1_dw;
	पूर्ण;
#अन्यथा
#त्रुटि "Unknown endianness"
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_PERF_EVENT_H */
