<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PERF_EVENT_H
#घोषणा _ASM_X86_PERF_EVENT_H

/*
 * Perक्रमmance event hw details:
 */

#घोषणा INTEL_PMC_MAX_GENERIC				       32
#घोषणा INTEL_PMC_MAX_FIXED					4
#घोषणा INTEL_PMC_IDX_FIXED				       32

#घोषणा X86_PMC_IDX_MAX					       64

#घोषणा MSR_ARCH_PERFMON_PERFCTR0			      0xc1
#घोषणा MSR_ARCH_PERFMON_PERFCTR1			      0xc2

#घोषणा MSR_ARCH_PERFMON_EVENTSEL0			     0x186
#घोषणा MSR_ARCH_PERFMON_EVENTSEL1			     0x187

#घोषणा ARCH_PERFMON_EVENTSEL_EVENT			0x000000FFULL
#घोषणा ARCH_PERFMON_EVENTSEL_UMASK			0x0000FF00ULL
#घोषणा ARCH_PERFMON_EVENTSEL_USR			(1ULL << 16)
#घोषणा ARCH_PERFMON_EVENTSEL_OS			(1ULL << 17)
#घोषणा ARCH_PERFMON_EVENTSEL_EDGE			(1ULL << 18)
#घोषणा ARCH_PERFMON_EVENTSEL_PIN_CONTROL		(1ULL << 19)
#घोषणा ARCH_PERFMON_EVENTSEL_INT			(1ULL << 20)
#घोषणा ARCH_PERFMON_EVENTSEL_ANY			(1ULL << 21)
#घोषणा ARCH_PERFMON_EVENTSEL_ENABLE			(1ULL << 22)
#घोषणा ARCH_PERFMON_EVENTSEL_INV			(1ULL << 23)
#घोषणा ARCH_PERFMON_EVENTSEL_CMASK			0xFF000000ULL

#घोषणा HSW_IN_TX					(1ULL << 32)
#घोषणा HSW_IN_TX_CHECKPOINTED				(1ULL << 33)
#घोषणा ICL_EVENTSEL_ADAPTIVE				(1ULL << 34)
#घोषणा ICL_FIXED_0_ADAPTIVE				(1ULL << 32)

#घोषणा AMD64_EVENTSEL_INT_CORE_ENABLE			(1ULL << 36)
#घोषणा AMD64_EVENTSEL_GUESTONLY			(1ULL << 40)
#घोषणा AMD64_EVENTSEL_HOSTONLY				(1ULL << 41)

#घोषणा AMD64_EVENTSEL_INT_CORE_SEL_SHIFT		37
#घोषणा AMD64_EVENTSEL_INT_CORE_SEL_MASK		\
	(0xFULL << AMD64_EVENTSEL_INT_CORE_SEL_SHIFT)

#घोषणा AMD64_EVENTSEL_EVENT	\
	(ARCH_PERFMON_EVENTSEL_EVENT | (0x0FULL << 32))
#घोषणा INTEL_ARCH_EVENT_MASK	\
	(ARCH_PERFMON_EVENTSEL_UMASK | ARCH_PERFMON_EVENTSEL_EVENT)

#घोषणा AMD64_L3_SLICE_SHIFT				48
#घोषणा AMD64_L3_SLICE_MASK				\
	(0xFULL << AMD64_L3_SLICE_SHIFT)
#घोषणा AMD64_L3_SLICEID_MASK				\
	(0x7ULL << AMD64_L3_SLICE_SHIFT)

#घोषणा AMD64_L3_THREAD_SHIFT				56
#घोषणा AMD64_L3_THREAD_MASK				\
	(0xFFULL << AMD64_L3_THREAD_SHIFT)
#घोषणा AMD64_L3_F19H_THREAD_MASK			\
	(0x3ULL << AMD64_L3_THREAD_SHIFT)

#घोषणा AMD64_L3_EN_ALL_CORES				BIT_ULL(47)
#घोषणा AMD64_L3_EN_ALL_SLICES				BIT_ULL(46)

#घोषणा AMD64_L3_COREID_SHIFT				42
#घोषणा AMD64_L3_COREID_MASK				\
	(0x7ULL << AMD64_L3_COREID_SHIFT)

#घोषणा X86_RAW_EVENT_MASK		\
	(ARCH_PERFMON_EVENTSEL_EVENT |	\
	 ARCH_PERFMON_EVENTSEL_UMASK |	\
	 ARCH_PERFMON_EVENTSEL_EDGE  |	\
	 ARCH_PERFMON_EVENTSEL_INV   |	\
	 ARCH_PERFMON_EVENTSEL_CMASK)
#घोषणा X86_ALL_EVENT_FLAGS  			\
	(ARCH_PERFMON_EVENTSEL_EDGE |  		\
	 ARCH_PERFMON_EVENTSEL_INV | 		\
	 ARCH_PERFMON_EVENTSEL_CMASK | 		\
	 ARCH_PERFMON_EVENTSEL_ANY | 		\
	 ARCH_PERFMON_EVENTSEL_PIN_CONTROL | 	\
	 HSW_IN_TX | 				\
	 HSW_IN_TX_CHECKPOINTED)
#घोषणा AMD64_RAW_EVENT_MASK		\
	(X86_RAW_EVENT_MASK          |  \
	 AMD64_EVENTSEL_EVENT)
#घोषणा AMD64_RAW_EVENT_MASK_NB		\
	(AMD64_EVENTSEL_EVENT        |  \
	 ARCH_PERFMON_EVENTSEL_UMASK)
#घोषणा AMD64_NUM_COUNTERS				4
#घोषणा AMD64_NUM_COUNTERS_CORE				6
#घोषणा AMD64_NUM_COUNTERS_NB				4

#घोषणा ARCH_PERFMON_UNHALTED_CORE_CYCLES_SEL		0x3c
#घोषणा ARCH_PERFMON_UNHALTED_CORE_CYCLES_UMASK		(0x00 << 8)
#घोषणा ARCH_PERFMON_UNHALTED_CORE_CYCLES_INDEX		0
#घोषणा ARCH_PERFMON_UNHALTED_CORE_CYCLES_PRESENT \
		(1 << (ARCH_PERFMON_UNHALTED_CORE_CYCLES_INDEX))

#घोषणा ARCH_PERFMON_BRANCH_MISSES_RETIRED		6
#घोषणा ARCH_PERFMON_EVENTS_COUNT			7

#घोषणा PEBS_DATACFG_MEMINFO	BIT_ULL(0)
#घोषणा PEBS_DATACFG_GP	BIT_ULL(1)
#घोषणा PEBS_DATACFG_XMMS	BIT_ULL(2)
#घोषणा PEBS_DATACFG_LBRS	BIT_ULL(3)
#घोषणा PEBS_DATACFG_LBR_SHIFT	24

/*
 * Intel "Architectural Performance Monitoring" CPUID
 * detection/क्रमागतeration details:
 */
जोड़ cpuid10_eax अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक version_id:8;
		अचिन्हित पूर्णांक num_counters:8;
		अचिन्हित पूर्णांक bit_width:8;
		अचिन्हित पूर्णांक mask_length:8;
	पूर्ण split;
	अचिन्हित पूर्णांक full;
पूर्ण;

जोड़ cpuid10_ebx अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक no_unhalted_core_cycles:1;
		अचिन्हित पूर्णांक no_inकाष्ठाions_retired:1;
		अचिन्हित पूर्णांक no_unhalted_reference_cycles:1;
		अचिन्हित पूर्णांक no_llc_reference:1;
		अचिन्हित पूर्णांक no_llc_misses:1;
		अचिन्हित पूर्णांक no_branch_inकाष्ठाion_retired:1;
		अचिन्हित पूर्णांक no_branch_misses_retired:1;
	पूर्ण split;
	अचिन्हित पूर्णांक full;
पूर्ण;

जोड़ cpuid10_edx अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक num_counters_fixed:5;
		अचिन्हित पूर्णांक bit_width_fixed:8;
		अचिन्हित पूर्णांक reserved1:2;
		अचिन्हित पूर्णांक anythपढ़ो_deprecated:1;
		अचिन्हित पूर्णांक reserved2:16;
	पूर्ण split;
	अचिन्हित पूर्णांक full;
पूर्ण;

/*
 * Intel Architectural LBR CPUID detection/क्रमागतeration details:
 */
जोड़ cpuid28_eax अणु
	काष्ठा अणु
		/* Supported LBR depth values */
		अचिन्हित पूर्णांक	lbr_depth_mask:8;
		अचिन्हित पूर्णांक	reserved:22;
		/* Deep C-state Reset */
		अचिन्हित पूर्णांक	lbr_deep_c_reset:1;
		/* IP values contain LIP */
		अचिन्हित पूर्णांक	lbr_lip:1;
	पूर्ण split;
	अचिन्हित पूर्णांक		full;
पूर्ण;

जोड़ cpuid28_ebx अणु
	काष्ठा अणु
		/* CPL Filtering Supported */
		अचिन्हित पूर्णांक    lbr_cpl:1;
		/* Branch Filtering Supported */
		अचिन्हित पूर्णांक    lbr_filter:1;
		/* Call-stack Mode Supported */
		अचिन्हित पूर्णांक    lbr_call_stack:1;
	पूर्ण split;
	अचिन्हित पूर्णांक            full;
पूर्ण;

जोड़ cpuid28_ecx अणु
	काष्ठा अणु
		/* Mispredict Bit Supported */
		अचिन्हित पूर्णांक    lbr_mispred:1;
		/* Timed LBRs Supported */
		अचिन्हित पूर्णांक    lbr_समयd_lbr:1;
		/* Branch Type Field Supported */
		अचिन्हित पूर्णांक    lbr_br_type:1;
	पूर्ण split;
	अचिन्हित पूर्णांक            full;
पूर्ण;

काष्ठा x86_pmu_capability अणु
	पूर्णांक		version;
	पूर्णांक		num_counters_gp;
	पूर्णांक		num_counters_fixed;
	पूर्णांक		bit_width_gp;
	पूर्णांक		bit_width_fixed;
	अचिन्हित पूर्णांक	events_mask;
	पूर्णांक		events_mask_len;
पूर्ण;

/*
 * Fixed-purpose perक्रमmance events:
 */

/* RDPMC offset क्रम Fixed PMCs */
#घोषणा INTEL_PMC_FIXED_RDPMC_BASE		(1 << 30)
#घोषणा INTEL_PMC_FIXED_RDPMC_METRICS		(1 << 29)

/*
 * All the fixed-mode PMCs are configured via this single MSR:
 */
#घोषणा MSR_ARCH_PERFMON_FIXED_CTR_CTRL	0x38d

/*
 * There is no event-code asचिन्हित to the fixed-mode PMCs.
 *
 * For a fixed-mode PMC, which has an equivalent event on a general-purpose
 * PMC, the event-code of the equivalent event is used क्रम the fixed-mode PMC,
 * e.g., Instr_Retired.Any and CPU_CLK_Unhalted.Core.
 *
 * For a fixed-mode PMC, which करोesn't have an equivalent event, a
 * pseuकरो-encoding is used, e.g., CPU_CLK_Unhalted.Ref and TOPDOWN.SLOTS.
 * The pseuकरो event-code क्रम a fixed-mode PMC must be 0x00.
 * The pseuकरो umask-code is 0xX. The X equals the index of the fixed
 * counter + 1, e.g., the fixed counter 2 has the pseuकरो-encoding 0x0300.
 *
 * The counts are available in separate MSRs:
 */

/* Instr_Retired.Any: */
#घोषणा MSR_ARCH_PERFMON_FIXED_CTR0	0x309
#घोषणा INTEL_PMC_IDX_FIXED_INSTRUCTIONS	(INTEL_PMC_IDX_FIXED + 0)

/* CPU_CLK_Unhalted.Core: */
#घोषणा MSR_ARCH_PERFMON_FIXED_CTR1	0x30a
#घोषणा INTEL_PMC_IDX_FIXED_CPU_CYCLES	(INTEL_PMC_IDX_FIXED + 1)

/* CPU_CLK_Unhalted.Ref: event=0x00,umask=0x3 (pseuकरो-encoding) */
#घोषणा MSR_ARCH_PERFMON_FIXED_CTR2	0x30b
#घोषणा INTEL_PMC_IDX_FIXED_REF_CYCLES	(INTEL_PMC_IDX_FIXED + 2)
#घोषणा INTEL_PMC_MSK_FIXED_REF_CYCLES	(1ULL << INTEL_PMC_IDX_FIXED_REF_CYCLES)

/* TOPDOWN.SLOTS: event=0x00,umask=0x4 (pseuकरो-encoding) */
#घोषणा MSR_ARCH_PERFMON_FIXED_CTR3	0x30c
#घोषणा INTEL_PMC_IDX_FIXED_SLOTS	(INTEL_PMC_IDX_FIXED + 3)
#घोषणा INTEL_PMC_MSK_FIXED_SLOTS	(1ULL << INTEL_PMC_IDX_FIXED_SLOTS)

/*
 * We model BTS tracing as another fixed-mode PMC.
 *
 * We choose the value 47 क्रम the fixed index of BTS, since lower
 * values are used by actual fixed events and higher values are used
 * to indicate other overflow conditions in the PERF_GLOBAL_STATUS msr.
 */
#घोषणा INTEL_PMC_IDX_FIXED_BTS			(INTEL_PMC_IDX_FIXED + 15)

/*
 * The PERF_METRICS MSR is modeled as several magic fixed-mode PMCs, one क्रम
 * each TopDown metric event.
 *
 * Internally the TopDown metric events are mapped to the FxCtr 3 (SLOTS).
 */
#घोषणा INTEL_PMC_IDX_METRIC_BASE		(INTEL_PMC_IDX_FIXED + 16)
#घोषणा INTEL_PMC_IDX_TD_RETIRING		(INTEL_PMC_IDX_METRIC_BASE + 0)
#घोषणा INTEL_PMC_IDX_TD_BAD_SPEC		(INTEL_PMC_IDX_METRIC_BASE + 1)
#घोषणा INTEL_PMC_IDX_TD_FE_BOUND		(INTEL_PMC_IDX_METRIC_BASE + 2)
#घोषणा INTEL_PMC_IDX_TD_BE_BOUND		(INTEL_PMC_IDX_METRIC_BASE + 3)
#घोषणा INTEL_PMC_IDX_TD_HEAVY_OPS		(INTEL_PMC_IDX_METRIC_BASE + 4)
#घोषणा INTEL_PMC_IDX_TD_BR_MISPREDICT		(INTEL_PMC_IDX_METRIC_BASE + 5)
#घोषणा INTEL_PMC_IDX_TD_FETCH_LAT		(INTEL_PMC_IDX_METRIC_BASE + 6)
#घोषणा INTEL_PMC_IDX_TD_MEM_BOUND		(INTEL_PMC_IDX_METRIC_BASE + 7)
#घोषणा INTEL_PMC_IDX_METRIC_END		INTEL_PMC_IDX_TD_MEM_BOUND
#घोषणा INTEL_PMC_MSK_TOPDOWN			((0xffull << INTEL_PMC_IDX_METRIC_BASE) | \
						INTEL_PMC_MSK_FIXED_SLOTS)

/*
 * There is no event-code asचिन्हित to the TopDown events.
 *
 * For the slots event, use the pseuकरो code of the fixed counter 3.
 *
 * For the metric events, the pseuकरो event-code is 0x00.
 * The pseuकरो umask-code starts from the middle of the pseuकरो event
 * space, 0x80.
 */
#घोषणा INTEL_TD_SLOTS				0x0400	/* TOPDOWN.SLOTS */
/* Level 1 metrics */
#घोषणा INTEL_TD_METRIC_RETIRING		0x8000	/* Retiring metric */
#घोषणा INTEL_TD_METRIC_BAD_SPEC		0x8100	/* Bad speculation metric */
#घोषणा INTEL_TD_METRIC_FE_BOUND		0x8200	/* FE bound metric */
#घोषणा INTEL_TD_METRIC_BE_BOUND		0x8300	/* BE bound metric */
/* Level 2 metrics */
#घोषणा INTEL_TD_METRIC_HEAVY_OPS		0x8400  /* Heavy Operations metric */
#घोषणा INTEL_TD_METRIC_BR_MISPREDICT		0x8500  /* Branch Mispredict metric */
#घोषणा INTEL_TD_METRIC_FETCH_LAT		0x8600  /* Fetch Latency metric */
#घोषणा INTEL_TD_METRIC_MEM_BOUND		0x8700  /* Memory bound metric */

#घोषणा INTEL_TD_METRIC_MAX			INTEL_TD_METRIC_MEM_BOUND
#घोषणा INTEL_TD_METRIC_NUM			8

अटल अंतरभूत bool is_metric_idx(पूर्णांक idx)
अणु
	वापस (अचिन्हित)(idx - INTEL_PMC_IDX_METRIC_BASE) < INTEL_TD_METRIC_NUM;
पूर्ण

अटल अंतरभूत bool is_topकरोwn_idx(पूर्णांक idx)
अणु
	वापस is_metric_idx(idx) || idx == INTEL_PMC_IDX_FIXED_SLOTS;
पूर्ण

#घोषणा INTEL_PMC_OTHER_TOPDOWN_BITS(bit)	\
			(~(0x1ull << bit) & INTEL_PMC_MSK_TOPDOWN)

#घोषणा GLOBAL_STATUS_COND_CHG			BIT_ULL(63)
#घोषणा GLOBAL_STATUS_BUFFER_OVF_BIT		62
#घोषणा GLOBAL_STATUS_BUFFER_OVF		BIT_ULL(GLOBAL_STATUS_BUFFER_OVF_BIT)
#घोषणा GLOBAL_STATUS_UNC_OVF			BIT_ULL(61)
#घोषणा GLOBAL_STATUS_ASIF			BIT_ULL(60)
#घोषणा GLOBAL_STATUS_COUNTERS_FROZEN		BIT_ULL(59)
#घोषणा GLOBAL_STATUS_LBRS_FROZEN_BIT		58
#घोषणा GLOBAL_STATUS_LBRS_FROZEN		BIT_ULL(GLOBAL_STATUS_LBRS_FROZEN_BIT)
#घोषणा GLOBAL_STATUS_TRACE_TOPAPMI_BIT		55
#घोषणा GLOBAL_STATUS_TRACE_TOPAPMI		BIT_ULL(GLOBAL_STATUS_TRACE_TOPAPMI_BIT)
#घोषणा GLOBAL_STATUS_PERF_METRICS_OVF_BIT	48

#घोषणा GLOBAL_CTRL_EN_PERF_METRICS		48
/*
 * We model guest LBR event tracing as another fixed-mode PMC like BTS.
 *
 * We choose bit 58 because it's used to indicate LBR stack frozen state
 * क्रम architectural perfmon v4, also we unconditionally mask that bit in
 * the handle_pmi_common(), so it'll never be set in the overflow handling.
 *
 * With this fake counter asचिन्हित, the guest LBR event user (such as KVM),
 * can program the LBR रेजिस्टरs on its own, and we करोn't actually करो anything
 * with then in the host context.
 */
#घोषणा INTEL_PMC_IDX_FIXED_VLBR	(GLOBAL_STATUS_LBRS_FROZEN_BIT)

/*
 * Pseuकरो-encoding the guest LBR event as event=0x00,umask=0x1b,
 * since it would claim bit 58 which is effectively Fixed26.
 */
#घोषणा INTEL_FIXED_VLBR_EVENT	0x1b00

/*
 * Adaptive PEBS v4
 */

काष्ठा pebs_basic अणु
	u64 क्रमmat_size;
	u64 ip;
	u64 applicable_counters;
	u64 tsc;
पूर्ण;

काष्ठा pebs_meminfo अणु
	u64 address;
	u64 aux;
	u64 latency;
	u64 tsx_tuning;
पूर्ण;

काष्ठा pebs_gprs अणु
	u64 flags, ip, ax, cx, dx, bx, sp, bp, si, di;
	u64 r8, r9, r10, r11, r12, r13, r14, r15;
पूर्ण;

काष्ठा pebs_xmm अणु
	u64 xmm[16*2];	/* two entries क्रम each रेजिस्टर */
पूर्ण;

/*
 * IBS cpuid feature detection
 */

#घोषणा IBS_CPUID_FEATURES		0x8000001b

/*
 * Same bit mask as क्रम IBS cpuid feature flags (Fn8000_001B_EAX), but
 * bit 0 is used to indicate the existence of IBS.
 */
#घोषणा IBS_CAPS_AVAIL			(1U<<0)
#घोषणा IBS_CAPS_FETCHSAM		(1U<<1)
#घोषणा IBS_CAPS_OPSAM			(1U<<2)
#घोषणा IBS_CAPS_RDWROPCNT		(1U<<3)
#घोषणा IBS_CAPS_OPCNT			(1U<<4)
#घोषणा IBS_CAPS_BRNTRGT		(1U<<5)
#घोषणा IBS_CAPS_OPCNTEXT		(1U<<6)
#घोषणा IBS_CAPS_RIPINVALIDCHK		(1U<<7)
#घोषणा IBS_CAPS_OPBRNFUSE		(1U<<8)
#घोषणा IBS_CAPS_FETCHCTLEXTD		(1U<<9)
#घोषणा IBS_CAPS_OPDATA4		(1U<<10)

#घोषणा IBS_CAPS_DEFAULT		(IBS_CAPS_AVAIL		\
					 | IBS_CAPS_FETCHSAM	\
					 | IBS_CAPS_OPSAM)

/*
 * IBS APIC setup
 */
#घोषणा IBSCTL				0x1cc
#घोषणा IBSCTL_LVT_OFFSET_VALID		(1ULL<<8)
#घोषणा IBSCTL_LVT_OFFSET_MASK		0x0F

/* IBS fetch bits/masks */
#घोषणा IBS_FETCH_RAND_EN	(1ULL<<57)
#घोषणा IBS_FETCH_VAL		(1ULL<<49)
#घोषणा IBS_FETCH_ENABLE	(1ULL<<48)
#घोषणा IBS_FETCH_CNT		0xFFFF0000ULL
#घोषणा IBS_FETCH_MAX_CNT	0x0000FFFFULL

/*
 * IBS op bits/masks
 * The lower 7 bits of the current count are अक्रमom bits
 * preloaded by hardware and ignored in software
 */
#घोषणा IBS_OP_CUR_CNT		(0xFFF80ULL<<32)
#घोषणा IBS_OP_CUR_CNT_RAND	(0x0007FULL<<32)
#घोषणा IBS_OP_CNT_CTL		(1ULL<<19)
#घोषणा IBS_OP_VAL		(1ULL<<18)
#घोषणा IBS_OP_ENABLE		(1ULL<<17)
#घोषणा IBS_OP_MAX_CNT		0x0000FFFFULL
#घोषणा IBS_OP_MAX_CNT_EXT	0x007FFFFFULL	/* not a रेजिस्टर bit mask */
#घोषणा IBS_OP_MAX_CNT_EXT_MASK	(0x7FULL<<20)	/* separate upper 7 bits */
#घोषणा IBS_RIP_INVALID		(1ULL<<38)

#अगर_घोषित CONFIG_X86_LOCAL_APIC
बाह्य u32 get_ibs_caps(व्योम);
#अन्यथा
अटल अंतरभूत u32 get_ibs_caps(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PERF_EVENTS
बाह्य व्योम perf_events_lapic_init(व्योम);

/*
 * Abuse bits अणु3,5पूर्ण of the cpu eflags रेजिस्टर. These flags are otherwise
 * unused and ABI specअगरied to be 0, so nobody should care what we करो with
 * them.
 *
 * EXACT - the IP poपूर्णांकs to the exact inकाष्ठाion that triggered the
 *         event (HW bugs exempt).
 * VM    - original X86_VM_MASK; see set_linear_ip().
 */
#घोषणा PERF_EFLAGS_EXACT	(1UL << 3)
#घोषणा PERF_EFLAGS_VM		(1UL << 5)

काष्ठा pt_regs;
काष्ठा x86_perf_regs अणु
	काष्ठा pt_regs	regs;
	u64		*xmm_regs;
पूर्ण;

बाह्य अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs);
बाह्य अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs);
#घोषणा perf_misc_flags(regs)	perf_misc_flags(regs)

#समावेश <यंत्र/stacktrace.h>

/*
 * We abuse bit 3 from flags to pass exact inक्रमmation, see perf_misc_flags
 * and the comment with PERF_EFLAGS_EXACT.
 */
#घोषणा perf_arch_fetch_caller_regs(regs, __ip)		अणु	\
	(regs)->ip = (__ip);					\
	(regs)->sp = (अचिन्हित दीर्घ)__builtin_frame_address(0);	\
	(regs)->cs = __KERNEL_CS;				\
	regs->flags = 0;					\
पूर्ण

काष्ठा perf_guest_चयन_msr अणु
	अचिन्हित msr;
	u64 host, guest;
पूर्ण;

काष्ठा x86_pmu_lbr अणु
	अचिन्हित पूर्णांक	nr;
	अचिन्हित पूर्णांक	from;
	अचिन्हित पूर्णांक	to;
	अचिन्हित पूर्णांक	info;
पूर्ण;

बाह्य व्योम perf_get_x86_pmu_capability(काष्ठा x86_pmu_capability *cap);
बाह्य व्योम perf_check_microcode(व्योम);
बाह्य पूर्णांक x86_perf_rdpmc_index(काष्ठा perf_event *event);
#अन्यथा
अटल अंतरभूत व्योम perf_get_x86_pmu_capability(काष्ठा x86_pmu_capability *cap)
अणु
	स_रखो(cap, 0, माप(*cap));
पूर्ण

अटल अंतरभूत व्योम perf_events_lapic_init(व्योम)	अणु पूर्ण
अटल अंतरभूत व्योम perf_check_microcode(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PERF_EVENTS) && defined(CONFIG_CPU_SUP_INTEL)
बाह्य काष्ठा perf_guest_चयन_msr *perf_guest_get_msrs(पूर्णांक *nr);
बाह्य पूर्णांक x86_perf_get_lbr(काष्ठा x86_pmu_lbr *lbr);
#अन्यथा
काष्ठा perf_guest_चयन_msr *perf_guest_get_msrs(पूर्णांक *nr);
अटल अंतरभूत पूर्णांक x86_perf_get_lbr(काष्ठा x86_pmu_lbr *lbr)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_SUP_INTEL
 बाह्य व्योम पूर्णांकel_pt_handle_vmx(पूर्णांक on);
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_pt_handle_vmx(पूर्णांक on)
अणु

पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PERF_EVENTS) && defined(CONFIG_CPU_SUP_AMD)
 बाह्य व्योम amd_pmu_enable_virt(व्योम);
 बाह्य व्योम amd_pmu_disable_virt(व्योम);
#अन्यथा
 अटल अंतरभूत व्योम amd_pmu_enable_virt(व्योम) अणु पूर्ण
 अटल अंतरभूत व्योम amd_pmu_disable_virt(व्योम) अणु पूर्ण
#पूर्ण_अगर

#घोषणा arch_perf_out_copy_user copy_from_user_nmi

#पूर्ण_अगर /* _ASM_X86_PERF_EVENT_H */
