<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Per core/cpu state
 *
 * Used to coordinate shared रेजिस्टरs between HT thपढ़ोs or
 * among events on a single PMU.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/nmi.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/पूर्णांकel_pt.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/cpu_device_id.h>

#समावेश "../perf_event.h"

/*
 * Intel PerfMon, used on Core and later.
 */
अटल u64 पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_MAX] __पढ़ो_mostly =
अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 0x003c,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 0x00c0,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= 0x4f2e,
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x412e,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x00c4,
	[PERF_COUNT_HW_BRANCH_MISSES]		= 0x00c5,
	[PERF_COUNT_HW_BUS_CYCLES]		= 0x013c,
	[PERF_COUNT_HW_REF_CPU_CYCLES]		= 0x0300, /* pseuकरो-encoding */
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_core_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	INTEL_EVENT_CONSTRAINT(0x11, 0x2), /* FP_ASSIST */
	INTEL_EVENT_CONSTRAINT(0x12, 0x2), /* MUL */
	INTEL_EVENT_CONSTRAINT(0x13, 0x2), /* DIV */
	INTEL_EVENT_CONSTRAINT(0x14, 0x1), /* CYCLES_DIV_BUSY */
	INTEL_EVENT_CONSTRAINT(0x19, 0x2), /* DELAYED_BYPASS */
	INTEL_EVENT_CONSTRAINT(0xc1, 0x1), /* FP_COMP_INSTR_RET */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_core2_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1), /* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2), /* CPU_CLK_UNHALTED.REF */
	INTEL_EVENT_CONSTRAINT(0x10, 0x1), /* FP_COMP_OPS_EXE */
	INTEL_EVENT_CONSTRAINT(0x11, 0x2), /* FP_ASSIST */
	INTEL_EVENT_CONSTRAINT(0x12, 0x2), /* MUL */
	INTEL_EVENT_CONSTRAINT(0x13, 0x2), /* DIV */
	INTEL_EVENT_CONSTRAINT(0x14, 0x1), /* CYCLES_DIV_BUSY */
	INTEL_EVENT_CONSTRAINT(0x18, 0x1), /* IDLE_DURING_DIV */
	INTEL_EVENT_CONSTRAINT(0x19, 0x2), /* DELAYED_BYPASS */
	INTEL_EVENT_CONSTRAINT(0xa1, 0x1), /* RS_UOPS_DISPATCH_CYCLES */
	INTEL_EVENT_CONSTRAINT(0xc9, 0x1), /* ITLB_MISS_RETIRED (T30-9) */
	INTEL_EVENT_CONSTRAINT(0xcb, 0x1), /* MEM_LOAD_RETIRED */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_nehalem_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1), /* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2), /* CPU_CLK_UNHALTED.REF */
	INTEL_EVENT_CONSTRAINT(0x40, 0x3), /* L1D_CACHE_LD */
	INTEL_EVENT_CONSTRAINT(0x41, 0x3), /* L1D_CACHE_ST */
	INTEL_EVENT_CONSTRAINT(0x42, 0x3), /* L1D_CACHE_LOCK */
	INTEL_EVENT_CONSTRAINT(0x43, 0x3), /* L1D_ALL_REF */
	INTEL_EVENT_CONSTRAINT(0x48, 0x3), /* L1D_PEND_MISS */
	INTEL_EVENT_CONSTRAINT(0x4e, 0x3), /* L1D_PREFETCH */
	INTEL_EVENT_CONSTRAINT(0x51, 0x3), /* L1D */
	INTEL_EVENT_CONSTRAINT(0x63, 0x3), /* CACHE_LOCK_CYCLES */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_nehalem_extra_regs[] __पढ़ो_mostly =
अणु
	/* must define OFFCORE_RSP_X first, see पूर्णांकel_fixup_er() */
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0xffff, RSP_0),
	INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(0x100b),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_wesपंचांगere_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1), /* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2), /* CPU_CLK_UNHALTED.REF */
	INTEL_EVENT_CONSTRAINT(0x51, 0x3), /* L1D */
	INTEL_EVENT_CONSTRAINT(0x60, 0x1), /* OFFCORE_REQUESTS_OUTSTANDING */
	INTEL_EVENT_CONSTRAINT(0x63, 0x3), /* CACHE_LOCK_CYCLES */
	INTEL_EVENT_CONSTRAINT(0xb3, 0x1), /* SNOOPQ_REQUEST_OUTSTANDING */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_snb_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1), /* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2), /* CPU_CLK_UNHALTED.REF */
	INTEL_UEVENT_CONSTRAINT(0x04a3, 0xf), /* CYCLE_ACTIVITY.CYCLES_NO_DISPATCH */
	INTEL_UEVENT_CONSTRAINT(0x05a3, 0xf), /* CYCLE_ACTIVITY.STALLS_L2_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x02a3, 0x4), /* CYCLE_ACTIVITY.CYCLES_L1D_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x06a3, 0x4), /* CYCLE_ACTIVITY.STALLS_L1D_PENDING */
	INTEL_EVENT_CONSTRAINT(0x48, 0x4), /* L1D_PEND_MISS.PENDING */
	INTEL_UEVENT_CONSTRAINT(0x01c0, 0x2), /* INST_RETIRED.PREC_DIST */
	INTEL_EVENT_CONSTRAINT(0xcd, 0x8), /* MEM_TRANS_RETIRED.LOAD_LATENCY */
	INTEL_UEVENT_CONSTRAINT(0x04a3, 0xf), /* CYCLE_ACTIVITY.CYCLES_NO_DISPATCH */
	INTEL_UEVENT_CONSTRAINT(0x02a3, 0x4), /* CYCLE_ACTIVITY.CYCLES_L1D_PENDING */

	/*
	 * When HT is off these events can only run on the bottom 4 counters
	 * When HT is on, they are impacted by the HT bug and require EXCL access
	 */
	INTEL_EXCLEVT_CONSTRAINT(0xd0, 0xf), /* MEM_UOPS_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd1, 0xf), /* MEM_LOAD_UOPS_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd2, 0xf), /* MEM_LOAD_UOPS_LLC_HIT_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd3, 0xf), /* MEM_LOAD_UOPS_LLC_MISS_RETIRED.* */

	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_ivb_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1), /* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2), /* CPU_CLK_UNHALTED.REF */
	INTEL_UEVENT_CONSTRAINT(0x0148, 0x4), /* L1D_PEND_MISS.PENDING */
	INTEL_UEVENT_CONSTRAINT(0x0279, 0xf), /* IDQ.EMPTY */
	INTEL_UEVENT_CONSTRAINT(0x019c, 0xf), /* IDQ_UOPS_NOT_DELIVERED.CORE */
	INTEL_UEVENT_CONSTRAINT(0x02a3, 0xf), /* CYCLE_ACTIVITY.CYCLES_LDM_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x04a3, 0xf), /* CYCLE_ACTIVITY.CYCLES_NO_EXECUTE */
	INTEL_UEVENT_CONSTRAINT(0x05a3, 0xf), /* CYCLE_ACTIVITY.STALLS_L2_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x06a3, 0xf), /* CYCLE_ACTIVITY.STALLS_LDM_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x08a3, 0x4), /* CYCLE_ACTIVITY.CYCLES_L1D_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x0ca3, 0x4), /* CYCLE_ACTIVITY.STALLS_L1D_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x01c0, 0x2), /* INST_RETIRED.PREC_DIST */

	/*
	 * When HT is off these events can only run on the bottom 4 counters
	 * When HT is on, they are impacted by the HT bug and require EXCL access
	 */
	INTEL_EXCLEVT_CONSTRAINT(0xd0, 0xf), /* MEM_UOPS_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd1, 0xf), /* MEM_LOAD_UOPS_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd2, 0xf), /* MEM_LOAD_UOPS_LLC_HIT_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd3, 0xf), /* MEM_LOAD_UOPS_LLC_MISS_RETIRED.* */

	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_wesपंचांगere_extra_regs[] __पढ़ो_mostly =
अणु
	/* must define OFFCORE_RSP_X first, see पूर्णांकel_fixup_er() */
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0xffff, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x01bb, MSR_OFFCORE_RSP_1, 0xffff, RSP_1),
	INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(0x100b),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_v1_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_gen_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1), /* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2), /* CPU_CLK_UNHALTED.REF */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_slm_event_स्थिरraपूर्णांकs[] __पढ़ो_mostly =
अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1), /* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2), /* pseuकरो CPU_CLK_UNHALTED.REF */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_skl_event_स्थिरraपूर्णांकs[] = अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0),	/* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1),	/* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2),	/* CPU_CLK_UNHALTED.REF */
	INTEL_UEVENT_CONSTRAINT(0x1c0, 0x2),	/* INST_RETIRED.PREC_DIST */

	/*
	 * when HT is off, these can only run on the bottom 4 counters
	 */
	INTEL_EVENT_CONSTRAINT(0xd0, 0xf),	/* MEM_INST_RETIRED.* */
	INTEL_EVENT_CONSTRAINT(0xd1, 0xf),	/* MEM_LOAD_RETIRED.* */
	INTEL_EVENT_CONSTRAINT(0xd2, 0xf),	/* MEM_LOAD_L3_HIT_RETIRED.* */
	INTEL_EVENT_CONSTRAINT(0xcd, 0xf),	/* MEM_TRANS_RETIRED.* */
	INTEL_EVENT_CONSTRAINT(0xc6, 0xf),	/* FRONTEND_RETIRED.* */

	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_knl_extra_regs[] __पढ़ो_mostly = अणु
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x799ffbb6e7ull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x02b7, MSR_OFFCORE_RSP_1, 0x399ffbffe7ull, RSP_1),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_snb_extra_regs[] __पढ़ो_mostly = अणु
	/* must define OFFCORE_RSP_X first, see पूर्णांकel_fixup_er() */
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x3f807f8fffull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x01bb, MSR_OFFCORE_RSP_1, 0x3f807f8fffull, RSP_1),
	INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(0x01cd),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_snbep_extra_regs[] __पढ़ो_mostly = अणु
	/* must define OFFCORE_RSP_X first, see पूर्णांकel_fixup_er() */
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x3fffff8fffull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x01bb, MSR_OFFCORE_RSP_1, 0x3fffff8fffull, RSP_1),
	INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(0x01cd),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_skl_extra_regs[] __पढ़ो_mostly = अणु
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x3fffff8fffull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x01bb, MSR_OFFCORE_RSP_1, 0x3fffff8fffull, RSP_1),
	INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(0x01cd),
	/*
	 * Note the low 8 bits eventsel code is not a continuous field, containing
	 * some #GPing bits. These are masked out.
	 */
	INTEL_UEVENT_EXTRA_REG(0x01c6, MSR_PEBS_FRONTEND, 0x7fff17, FE),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_icl_event_स्थिरraपूर्णांकs[] = अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0),	/* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x01c0, 0),	/* INST_RETIRED.PREC_DIST */
	FIXED_EVENT_CONSTRAINT(0x003c, 1),	/* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2),	/* CPU_CLK_UNHALTED.REF */
	FIXED_EVENT_CONSTRAINT(0x0400, 3),	/* SLOTS */
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_RETIRING, 0),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_BAD_SPEC, 1),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_FE_BOUND, 2),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_BE_BOUND, 3),
	INTEL_EVENT_CONSTRAINT_RANGE(0x03, 0x0a, 0xf),
	INTEL_EVENT_CONSTRAINT_RANGE(0x1f, 0x28, 0xf),
	INTEL_EVENT_CONSTRAINT(0x32, 0xf),	/* SW_PREFETCH_ACCESS.* */
	INTEL_EVENT_CONSTRAINT_RANGE(0x48, 0x54, 0xf),
	INTEL_EVENT_CONSTRAINT_RANGE(0x60, 0x8b, 0xf),
	INTEL_UEVENT_CONSTRAINT(0x04a3, 0xff),  /* CYCLE_ACTIVITY.STALLS_TOTAL */
	INTEL_UEVENT_CONSTRAINT(0x10a3, 0xff),  /* CYCLE_ACTIVITY.CYCLES_MEM_ANY */
	INTEL_UEVENT_CONSTRAINT(0x14a3, 0xff),  /* CYCLE_ACTIVITY.STALLS_MEM_ANY */
	INTEL_EVENT_CONSTRAINT(0xa3, 0xf),      /* CYCLE_ACTIVITY.* */
	INTEL_EVENT_CONSTRAINT_RANGE(0xa8, 0xb0, 0xf),
	INTEL_EVENT_CONSTRAINT_RANGE(0xb7, 0xbd, 0xf),
	INTEL_EVENT_CONSTRAINT_RANGE(0xd0, 0xe6, 0xf),
	INTEL_EVENT_CONSTRAINT_RANGE(0xf0, 0xf4, 0xf),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_icl_extra_regs[] __पढ़ो_mostly = अणु
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x3fffffbfffull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x01bb, MSR_OFFCORE_RSP_1, 0x3fffffbfffull, RSP_1),
	INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(0x01cd),
	INTEL_UEVENT_EXTRA_REG(0x01c6, MSR_PEBS_FRONTEND, 0x7fff17, FE),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_spr_extra_regs[] __पढ़ो_mostly = अणु
	INTEL_UEVENT_EXTRA_REG(0x012a, MSR_OFFCORE_RSP_0, 0x3fffffffffull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x012b, MSR_OFFCORE_RSP_1, 0x3fffffffffull, RSP_1),
	INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(0x01cd),
	INTEL_UEVENT_EXTRA_REG(0x01c6, MSR_PEBS_FRONTEND, 0x7fff17, FE),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_spr_event_स्थिरraपूर्णांकs[] = अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0),	/* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x01c0, 0),	/* INST_RETIRED.PREC_DIST */
	FIXED_EVENT_CONSTRAINT(0x003c, 1),	/* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2),	/* CPU_CLK_UNHALTED.REF */
	FIXED_EVENT_CONSTRAINT(0x0400, 3),	/* SLOTS */
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_RETIRING, 0),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_BAD_SPEC, 1),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_FE_BOUND, 2),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_BE_BOUND, 3),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_HEAVY_OPS, 4),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_BR_MISPREDICT, 5),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_FETCH_LAT, 6),
	METRIC_EVENT_CONSTRAINT(INTEL_TD_METRIC_MEM_BOUND, 7),

	INTEL_EVENT_CONSTRAINT(0x2e, 0xff),
	INTEL_EVENT_CONSTRAINT(0x3c, 0xff),
	/*
	 * Generally event codes < 0x90 are restricted to counters 0-3.
	 * The 0x2E and 0x3C are exception, which has no restriction.
	 */
	INTEL_EVENT_CONSTRAINT_RANGE(0x01, 0x8f, 0xf),

	INTEL_UEVENT_CONSTRAINT(0x01a3, 0xf),
	INTEL_UEVENT_CONSTRAINT(0x02a3, 0xf),
	INTEL_UEVENT_CONSTRAINT(0x08a3, 0xf),
	INTEL_UEVENT_CONSTRAINT(0x04a4, 0x1),
	INTEL_UEVENT_CONSTRAINT(0x08a4, 0x1),
	INTEL_UEVENT_CONSTRAINT(0x02cd, 0x1),
	INTEL_EVENT_CONSTRAINT(0xce, 0x1),
	INTEL_EVENT_CONSTRAINT_RANGE(0xd0, 0xdf, 0xf),
	/*
	 * Generally event codes >= 0x90 are likely to have no restrictions.
	 * The exception are defined as above.
	 */
	INTEL_EVENT_CONSTRAINT_RANGE(0x90, 0xfe, 0xff),

	EVENT_CONSTRAINT_END
पूर्ण;


EVENT_ATTR_STR(mem-loads,	mem_ld_nhm,	"event=0x0b,umask=0x10,ldlat=3");
EVENT_ATTR_STR(mem-loads,	mem_ld_snb,	"event=0xcd,umask=0x1,ldlat=3");
EVENT_ATTR_STR(mem-stores,	mem_st_snb,	"event=0xcd,umask=0x2");

अटल काष्ठा attribute *nhm_mem_events_attrs[] = अणु
	EVENT_PTR(mem_ld_nhm),
	शून्य,
पूर्ण;

/*
 * topकरोwn events क्रम Intel Core CPUs.
 *
 * The events are all in slots, which is a मुक्त slot in a 4 wide
 * pipeline. Some events are alपढ़ोy reported in slots, क्रम cycle
 * events we multiply by the pipeline width (4).
 *
 * With Hyper Thपढ़ोing on, topकरोwn metrics are either summed or averaged
 * between the thपढ़ोs of a core: (count_t0 + count_t1).
 *
 * For the average हाल the metric is always scaled to pipeline width,
 * so we use factor 2 ((count_t0 + count_t1) / 2 * 4)
 */

EVENT_ATTR_STR_HT(topकरोwn-total-slots, td_total_slots,
	"event=0x3c,umask=0x0",			/* cpu_clk_unhalted.thपढ़ो */
	"event=0x3c,umask=0x0,any=1");		/* cpu_clk_unhalted.thपढ़ो_any */
EVENT_ATTR_STR_HT(topकरोwn-total-slots.scale, td_total_slots_scale, "4", "2");
EVENT_ATTR_STR(topकरोwn-slots-issued, td_slots_issued,
	"event=0xe,umask=0x1");			/* uops_issued.any */
EVENT_ATTR_STR(topकरोwn-slots-retired, td_slots_retired,
	"event=0xc2,umask=0x2");		/* uops_retired.retire_slots */
EVENT_ATTR_STR(topकरोwn-fetch-bubbles, td_fetch_bubbles,
	"event=0x9c,umask=0x1");		/* idq_uops_not_delivered_core */
EVENT_ATTR_STR_HT(topकरोwn-recovery-bubbles, td_recovery_bubbles,
	"event=0xd,umask=0x3,cmask=1",		/* पूर्णांक_misc.recovery_cycles */
	"event=0xd,umask=0x3,cmask=1,any=1");	/* पूर्णांक_misc.recovery_cycles_any */
EVENT_ATTR_STR_HT(topकरोwn-recovery-bubbles.scale, td_recovery_bubbles_scale,
	"4", "2");

EVENT_ATTR_STR(slots,			slots,			"event=0x00,umask=0x4");
EVENT_ATTR_STR(topकरोwn-retiring,	td_retiring,		"event=0x00,umask=0x80");
EVENT_ATTR_STR(topकरोwn-bad-spec,	td_bad_spec,		"event=0x00,umask=0x81");
EVENT_ATTR_STR(topकरोwn-fe-bound,	td_fe_bound,		"event=0x00,umask=0x82");
EVENT_ATTR_STR(topकरोwn-be-bound,	td_be_bound,		"event=0x00,umask=0x83");
EVENT_ATTR_STR(topकरोwn-heavy-ops,	td_heavy_ops,		"event=0x00,umask=0x84");
EVENT_ATTR_STR(topकरोwn-br-mispredict,	td_br_mispredict,	"event=0x00,umask=0x85");
EVENT_ATTR_STR(topकरोwn-fetch-lat,	td_fetch_lat,		"event=0x00,umask=0x86");
EVENT_ATTR_STR(topकरोwn-mem-bound,	td_mem_bound,		"event=0x00,umask=0x87");

अटल काष्ठा attribute *snb_events_attrs[] = अणु
	EVENT_PTR(td_slots_issued),
	EVENT_PTR(td_slots_retired),
	EVENT_PTR(td_fetch_bubbles),
	EVENT_PTR(td_total_slots),
	EVENT_PTR(td_total_slots_scale),
	EVENT_PTR(td_recovery_bubbles),
	EVENT_PTR(td_recovery_bubbles_scale),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *snb_mem_events_attrs[] = अणु
	EVENT_PTR(mem_ld_snb),
	EVENT_PTR(mem_st_snb),
	शून्य,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_hsw_event_स्थिरraपूर्णांकs[] = अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0), /* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1), /* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2), /* CPU_CLK_UNHALTED.REF */
	INTEL_UEVENT_CONSTRAINT(0x148, 0x4),	/* L1D_PEND_MISS.PENDING */
	INTEL_UEVENT_CONSTRAINT(0x01c0, 0x2), /* INST_RETIRED.PREC_DIST */
	INTEL_EVENT_CONSTRAINT(0xcd, 0x8), /* MEM_TRANS_RETIRED.LOAD_LATENCY */
	/* CYCLE_ACTIVITY.CYCLES_L1D_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x08a3, 0x4),
	/* CYCLE_ACTIVITY.STALLS_L1D_PENDING */
	INTEL_UEVENT_CONSTRAINT(0x0ca3, 0x4),
	/* CYCLE_ACTIVITY.CYCLES_NO_EXECUTE */
	INTEL_UEVENT_CONSTRAINT(0x04a3, 0xf),

	/*
	 * When HT is off these events can only run on the bottom 4 counters
	 * When HT is on, they are impacted by the HT bug and require EXCL access
	 */
	INTEL_EXCLEVT_CONSTRAINT(0xd0, 0xf), /* MEM_UOPS_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd1, 0xf), /* MEM_LOAD_UOPS_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd2, 0xf), /* MEM_LOAD_UOPS_LLC_HIT_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd3, 0xf), /* MEM_LOAD_UOPS_LLC_MISS_RETIRED.* */

	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_bdw_event_स्थिरraपूर्णांकs[] = अणु
	FIXED_EVENT_CONSTRAINT(0x00c0, 0),	/* INST_RETIRED.ANY */
	FIXED_EVENT_CONSTRAINT(0x003c, 1),	/* CPU_CLK_UNHALTED.CORE */
	FIXED_EVENT_CONSTRAINT(0x0300, 2),	/* CPU_CLK_UNHALTED.REF */
	INTEL_UEVENT_CONSTRAINT(0x148, 0x4),	/* L1D_PEND_MISS.PENDING */
	INTEL_UBIT_EVENT_CONSTRAINT(0x8a3, 0x4),	/* CYCLE_ACTIVITY.CYCLES_L1D_MISS */
	/*
	 * when HT is off, these can only run on the bottom 4 counters
	 */
	INTEL_EVENT_CONSTRAINT(0xd0, 0xf),	/* MEM_INST_RETIRED.* */
	INTEL_EVENT_CONSTRAINT(0xd1, 0xf),	/* MEM_LOAD_RETIRED.* */
	INTEL_EVENT_CONSTRAINT(0xd2, 0xf),	/* MEM_LOAD_L3_HIT_RETIRED.* */
	INTEL_EVENT_CONSTRAINT(0xcd, 0xf),	/* MEM_TRANS_RETIRED.* */
	EVENT_CONSTRAINT_END
पूर्ण;

अटल u64 पूर्णांकel_pmu_event_map(पूर्णांक hw_event)
अणु
	वापस पूर्णांकel_perfmon_event_map[hw_event];
पूर्ण

अटल __initस्थिर स्थिर u64 spr_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x81d0,
		[ C(RESULT_MISS)   ] = 0xe124,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x82d0,
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_MISS)   ] = 0xe424,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x12a,
		[ C(RESULT_MISS)   ] = 0x12a,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x12a,
		[ C(RESULT_MISS)   ] = 0x12a,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x81d0,
		[ C(RESULT_MISS)   ] = 0xe12,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x82d0,
		[ C(RESULT_MISS)   ] = 0xe13,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = 0xe11,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x4c4,
		[ C(RESULT_MISS)   ] = 0x4c5,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x12a,
		[ C(RESULT_MISS)   ] = 0x12a,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 spr_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x10001,
		[ C(RESULT_MISS)   ] = 0x3fbfc00001,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x3f3ffc0002,
		[ C(RESULT_MISS)   ] = 0x3f3fc00002,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x10c000001,
		[ C(RESULT_MISS)   ] = 0x3fb3000001,
	पूर्ण,
 पूर्ण,
पूर्ण;

/*
 * Notes on the events:
 * - data पढ़ोs करो not include code पढ़ोs (comparable to earlier tables)
 * - data counts include speculative execution (except L1 ग_लिखो, dtlb, bpu)
 * - remote node access includes remote memory, remote cache, remote mmio.
 * - prefetches are not included in the counts.
 * - icache miss करोes not include decoded icache
 */

#घोषणा SKL_DEMAND_DATA_RD		BIT_ULL(0)
#घोषणा SKL_DEMAND_RFO			BIT_ULL(1)
#घोषणा SKL_ANY_RESPONSE		BIT_ULL(16)
#घोषणा SKL_SUPPLIER_NONE		BIT_ULL(17)
#घोषणा SKL_L3_MISS_LOCAL_DRAM		BIT_ULL(26)
#घोषणा SKL_L3_MISS_REMOTE_HOP0_DRAM	BIT_ULL(27)
#घोषणा SKL_L3_MISS_REMOTE_HOP1_DRAM	BIT_ULL(28)
#घोषणा SKL_L3_MISS_REMOTE_HOP2P_DRAM	BIT_ULL(29)
#घोषणा SKL_L3_MISS			(SKL_L3_MISS_LOCAL_DRAM| \
					 SKL_L3_MISS_REMOTE_HOP0_DRAM| \
					 SKL_L3_MISS_REMOTE_HOP1_DRAM| \
					 SKL_L3_MISS_REMOTE_HOP2P_DRAM)
#घोषणा SKL_SPL_HIT			BIT_ULL(30)
#घोषणा SKL_SNOOP_NONE			BIT_ULL(31)
#घोषणा SKL_SNOOP_NOT_NEEDED		BIT_ULL(32)
#घोषणा SKL_SNOOP_MISS			BIT_ULL(33)
#घोषणा SKL_SNOOP_HIT_NO_FWD		BIT_ULL(34)
#घोषणा SKL_SNOOP_HIT_WITH_FWD		BIT_ULL(35)
#घोषणा SKL_SNOOP_HITM			BIT_ULL(36)
#घोषणा SKL_SNOOP_NON_DRAM		BIT_ULL(37)
#घोषणा SKL_ANY_SNOOP			(SKL_SPL_HIT|SKL_SNOOP_NONE| \
					 SKL_SNOOP_NOT_NEEDED|SKL_SNOOP_MISS| \
					 SKL_SNOOP_HIT_NO_FWD|SKL_SNOOP_HIT_WITH_FWD| \
					 SKL_SNOOP_HITM|SKL_SNOOP_NON_DRAM)
#घोषणा SKL_DEMAND_READ			SKL_DEMAND_DATA_RD
#घोषणा SKL_SNOOP_DRAM			(SKL_SNOOP_NONE| \
					 SKL_SNOOP_NOT_NEEDED|SKL_SNOOP_MISS| \
					 SKL_SNOOP_HIT_NO_FWD|SKL_SNOOP_HIT_WITH_FWD| \
					 SKL_SNOOP_HITM|SKL_SPL_HIT)
#घोषणा SKL_DEMAND_WRITE		SKL_DEMAND_RFO
#घोषणा SKL_LLC_ACCESS			SKL_ANY_RESPONSE
#घोषणा SKL_L3_MISS_REMOTE		(SKL_L3_MISS_REMOTE_HOP0_DRAM| \
					 SKL_L3_MISS_REMOTE_HOP1_DRAM| \
					 SKL_L3_MISS_REMOTE_HOP2P_DRAM)

अटल __initस्थिर स्थिर u64 skl_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x81d0,	/* MEM_INST_RETIRED.ALL_LOADS */
		[ C(RESULT_MISS)   ] = 0x151,	/* L1D.REPLACEMENT */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x82d0,	/* MEM_INST_RETIRED.ALL_STORES */
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x283,	/* ICACHE_64B.MISS */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1b7,	/* OFFCORE_RESPONSE */
		[ C(RESULT_MISS)   ] = 0x1b7,	/* OFFCORE_RESPONSE */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1b7,	/* OFFCORE_RESPONSE */
		[ C(RESULT_MISS)   ] = 0x1b7,	/* OFFCORE_RESPONSE */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x81d0,	/* MEM_INST_RETIRED.ALL_LOADS */
		[ C(RESULT_MISS)   ] = 0xe08,	/* DTLB_LOAD_MISSES.WALK_COMPLETED */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x82d0,	/* MEM_INST_RETIRED.ALL_STORES */
		[ C(RESULT_MISS)   ] = 0xe49,	/* DTLB_STORE_MISSES.WALK_COMPLETED */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x2085,	/* ITLB_MISSES.STLB_HIT */
		[ C(RESULT_MISS)   ] = 0xe85,	/* ITLB_MISSES.WALK_COMPLETED */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0xc4,	/* BR_INST_RETIRED.ALL_BRANCHES */
		[ C(RESULT_MISS)   ] = 0xc5,	/* BR_MISP_RETIRED.ALL_BRANCHES */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1b7,	/* OFFCORE_RESPONSE */
		[ C(RESULT_MISS)   ] = 0x1b7,	/* OFFCORE_RESPONSE */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1b7,	/* OFFCORE_RESPONSE */
		[ C(RESULT_MISS)   ] = 0x1b7,	/* OFFCORE_RESPONSE */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 skl_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = SKL_DEMAND_READ|
				       SKL_LLC_ACCESS|SKL_ANY_SNOOP,
		[ C(RESULT_MISS)   ] = SKL_DEMAND_READ|
				       SKL_L3_MISS|SKL_ANY_SNOOP|
				       SKL_SUPPLIER_NONE,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = SKL_DEMAND_WRITE|
				       SKL_LLC_ACCESS|SKL_ANY_SNOOP,
		[ C(RESULT_MISS)   ] = SKL_DEMAND_WRITE|
				       SKL_L3_MISS|SKL_ANY_SNOOP|
				       SKL_SUPPLIER_NONE,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = SKL_DEMAND_READ|
				       SKL_L3_MISS_LOCAL_DRAM|SKL_SNOOP_DRAM,
		[ C(RESULT_MISS)   ] = SKL_DEMAND_READ|
				       SKL_L3_MISS_REMOTE|SKL_SNOOP_DRAM,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = SKL_DEMAND_WRITE|
				       SKL_L3_MISS_LOCAL_DRAM|SKL_SNOOP_DRAM,
		[ C(RESULT_MISS)   ] = SKL_DEMAND_WRITE|
				       SKL_L3_MISS_REMOTE|SKL_SNOOP_DRAM,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
पूर्ण;

#घोषणा SNB_DMND_DATA_RD	(1ULL << 0)
#घोषणा SNB_DMND_RFO		(1ULL << 1)
#घोषणा SNB_DMND_IFETCH		(1ULL << 2)
#घोषणा SNB_DMND_WB		(1ULL << 3)
#घोषणा SNB_PF_DATA_RD		(1ULL << 4)
#घोषणा SNB_PF_RFO		(1ULL << 5)
#घोषणा SNB_PF_IFETCH		(1ULL << 6)
#घोषणा SNB_LLC_DATA_RD		(1ULL << 7)
#घोषणा SNB_LLC_RFO		(1ULL << 8)
#घोषणा SNB_LLC_IFETCH		(1ULL << 9)
#घोषणा SNB_BUS_LOCKS		(1ULL << 10)
#घोषणा SNB_STRM_ST		(1ULL << 11)
#घोषणा SNB_OTHER		(1ULL << 15)
#घोषणा SNB_RESP_ANY		(1ULL << 16)
#घोषणा SNB_NO_SUPP		(1ULL << 17)
#घोषणा SNB_LLC_HITM		(1ULL << 18)
#घोषणा SNB_LLC_HITE		(1ULL << 19)
#घोषणा SNB_LLC_HITS		(1ULL << 20)
#घोषणा SNB_LLC_HITF		(1ULL << 21)
#घोषणा SNB_LOCAL		(1ULL << 22)
#घोषणा SNB_REMOTE		(0xffULL << 23)
#घोषणा SNB_SNP_NONE		(1ULL << 31)
#घोषणा SNB_SNP_NOT_NEEDED	(1ULL << 32)
#घोषणा SNB_SNP_MISS		(1ULL << 33)
#घोषणा SNB_NO_FWD		(1ULL << 34)
#घोषणा SNB_SNP_FWD		(1ULL << 35)
#घोषणा SNB_HITM		(1ULL << 36)
#घोषणा SNB_NON_DRAM		(1ULL << 37)

#घोषणा SNB_DMND_READ		(SNB_DMND_DATA_RD|SNB_LLC_DATA_RD)
#घोषणा SNB_DMND_WRITE		(SNB_DMND_RFO|SNB_LLC_RFO)
#घोषणा SNB_DMND_PREFETCH	(SNB_PF_DATA_RD|SNB_PF_RFO)

#घोषणा SNB_SNP_ANY		(SNB_SNP_NONE|SNB_SNP_NOT_NEEDED| \
				 SNB_SNP_MISS|SNB_NO_FWD|SNB_SNP_FWD| \
				 SNB_HITM)

#घोषणा SNB_DRAM_ANY		(SNB_LOCAL|SNB_REMOTE|SNB_SNP_ANY)
#घोषणा SNB_DRAM_REMOTE		(SNB_REMOTE|SNB_SNP_ANY)

#घोषणा SNB_L3_ACCESS		SNB_RESP_ANY
#घोषणा SNB_L3_MISS		(SNB_DRAM_ANY|SNB_NON_DRAM)

अटल __initस्थिर स्थिर u64 snb_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = SNB_DMND_READ|SNB_L3_ACCESS,
		[ C(RESULT_MISS)   ] = SNB_DMND_READ|SNB_L3_MISS,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = SNB_DMND_WRITE|SNB_L3_ACCESS,
		[ C(RESULT_MISS)   ] = SNB_DMND_WRITE|SNB_L3_MISS,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = SNB_DMND_PREFETCH|SNB_L3_ACCESS,
		[ C(RESULT_MISS)   ] = SNB_DMND_PREFETCH|SNB_L3_MISS,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = SNB_DMND_READ|SNB_DRAM_ANY,
		[ C(RESULT_MISS)   ] = SNB_DMND_READ|SNB_DRAM_REMOTE,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = SNB_DMND_WRITE|SNB_DRAM_ANY,
		[ C(RESULT_MISS)   ] = SNB_DMND_WRITE|SNB_DRAM_REMOTE,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = SNB_DMND_PREFETCH|SNB_DRAM_ANY,
		[ C(RESULT_MISS)   ] = SNB_DMND_PREFETCH|SNB_DRAM_REMOTE,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 snb_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0xf1d0, /* MEM_UOP_RETIRED.LOADS        */
		[ C(RESULT_MISS)   ] = 0x0151, /* L1D.REPLACEMENT              */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0xf2d0, /* MEM_UOP_RETIRED.STORES       */
		[ C(RESULT_MISS)   ] = 0x0851, /* L1D.ALL_M_REPLACEMENT        */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x024e, /* HW_PRE_REQ.DL1_MISS          */
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0280, /* ICACHE.MISSES */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		/* OFFCORE_RESPONSE.ANY_DATA.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.ANY_DATA.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		/* OFFCORE_RESPONSE.ANY_RFO.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.ANY_RFO.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		/* OFFCORE_RESPONSE.PREFETCH.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.PREFETCH.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x81d0, /* MEM_UOP_RETIRED.ALL_LOADS */
		[ C(RESULT_MISS)   ] = 0x0108, /* DTLB_LOAD_MISSES.CAUSES_A_WALK */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x82d0, /* MEM_UOP_RETIRED.ALL_STORES */
		[ C(RESULT_MISS)   ] = 0x0149, /* DTLB_STORE_MISSES.MISS_CAUSES_A_WALK */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1085, /* ITLB_MISSES.STLB_HIT         */
		[ C(RESULT_MISS)   ] = 0x0185, /* ITLB_MISSES.CAUSES_A_WALK    */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c4, /* BR_INST_RETIRED.ALL_BRANCHES */
		[ C(RESULT_MISS)   ] = 0x00c5, /* BR_MISP_RETIRED.ALL_BRANCHES */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
 पूर्ण,

पूर्ण;

/*
 * Notes on the events:
 * - data पढ़ोs करो not include code पढ़ोs (comparable to earlier tables)
 * - data counts include speculative execution (except L1 ग_लिखो, dtlb, bpu)
 * - remote node access includes remote memory, remote cache, remote mmio.
 * - prefetches are not included in the counts because they are not
 *   reliably counted.
 */

#घोषणा HSW_DEMAND_DATA_RD		BIT_ULL(0)
#घोषणा HSW_DEMAND_RFO			BIT_ULL(1)
#घोषणा HSW_ANY_RESPONSE		BIT_ULL(16)
#घोषणा HSW_SUPPLIER_NONE		BIT_ULL(17)
#घोषणा HSW_L3_MISS_LOCAL_DRAM		BIT_ULL(22)
#घोषणा HSW_L3_MISS_REMOTE_HOP0		BIT_ULL(27)
#घोषणा HSW_L3_MISS_REMOTE_HOP1		BIT_ULL(28)
#घोषणा HSW_L3_MISS_REMOTE_HOP2P	BIT_ULL(29)
#घोषणा HSW_L3_MISS			(HSW_L3_MISS_LOCAL_DRAM| \
					 HSW_L3_MISS_REMOTE_HOP0|HSW_L3_MISS_REMOTE_HOP1| \
					 HSW_L3_MISS_REMOTE_HOP2P)
#घोषणा HSW_SNOOP_NONE			BIT_ULL(31)
#घोषणा HSW_SNOOP_NOT_NEEDED		BIT_ULL(32)
#घोषणा HSW_SNOOP_MISS			BIT_ULL(33)
#घोषणा HSW_SNOOP_HIT_NO_FWD		BIT_ULL(34)
#घोषणा HSW_SNOOP_HIT_WITH_FWD		BIT_ULL(35)
#घोषणा HSW_SNOOP_HITM			BIT_ULL(36)
#घोषणा HSW_SNOOP_NON_DRAM		BIT_ULL(37)
#घोषणा HSW_ANY_SNOOP			(HSW_SNOOP_NONE| \
					 HSW_SNOOP_NOT_NEEDED|HSW_SNOOP_MISS| \
					 HSW_SNOOP_HIT_NO_FWD|HSW_SNOOP_HIT_WITH_FWD| \
					 HSW_SNOOP_HITM|HSW_SNOOP_NON_DRAM)
#घोषणा HSW_SNOOP_DRAM			(HSW_ANY_SNOOP & ~HSW_SNOOP_NON_DRAM)
#घोषणा HSW_DEMAND_READ			HSW_DEMAND_DATA_RD
#घोषणा HSW_DEMAND_WRITE		HSW_DEMAND_RFO
#घोषणा HSW_L3_MISS_REMOTE		(HSW_L3_MISS_REMOTE_HOP0|\
					 HSW_L3_MISS_REMOTE_HOP1|HSW_L3_MISS_REMOTE_HOP2P)
#घोषणा HSW_LLC_ACCESS			HSW_ANY_RESPONSE

#घोषणा BDW_L3_MISS_LOCAL		BIT(26)
#घोषणा BDW_L3_MISS			(BDW_L3_MISS_LOCAL| \
					 HSW_L3_MISS_REMOTE_HOP0|HSW_L3_MISS_REMOTE_HOP1| \
					 HSW_L3_MISS_REMOTE_HOP2P)


अटल __initस्थिर स्थिर u64 hsw_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x81d0,	/* MEM_UOPS_RETIRED.ALL_LOADS */
		[ C(RESULT_MISS)   ] = 0x151,	/* L1D.REPLACEMENT */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x82d0,	/* MEM_UOPS_RETIRED.ALL_STORES */
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x280,	/* ICACHE.MISSES */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1b7,	/* OFFCORE_RESPONSE */
		[ C(RESULT_MISS)   ] = 0x1b7,	/* OFFCORE_RESPONSE */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1b7,	/* OFFCORE_RESPONSE */
		[ C(RESULT_MISS)   ] = 0x1b7,	/* OFFCORE_RESPONSE */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x81d0,	/* MEM_UOPS_RETIRED.ALL_LOADS */
		[ C(RESULT_MISS)   ] = 0x108,	/* DTLB_LOAD_MISSES.MISS_CAUSES_A_WALK */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x82d0,	/* MEM_UOPS_RETIRED.ALL_STORES */
		[ C(RESULT_MISS)   ] = 0x149,	/* DTLB_STORE_MISSES.MISS_CAUSES_A_WALK */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x6085,	/* ITLB_MISSES.STLB_HIT */
		[ C(RESULT_MISS)   ] = 0x185,	/* ITLB_MISSES.MISS_CAUSES_A_WALK */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0xc4,	/* BR_INST_RETIRED.ALL_BRANCHES */
		[ C(RESULT_MISS)   ] = 0xc5,	/* BR_MISP_RETIRED.ALL_BRANCHES */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1b7,	/* OFFCORE_RESPONSE */
		[ C(RESULT_MISS)   ] = 0x1b7,	/* OFFCORE_RESPONSE */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x1b7,	/* OFFCORE_RESPONSE */
		[ C(RESULT_MISS)   ] = 0x1b7,	/* OFFCORE_RESPONSE */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 hsw_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = HSW_DEMAND_READ|
				       HSW_LLC_ACCESS,
		[ C(RESULT_MISS)   ] = HSW_DEMAND_READ|
				       HSW_L3_MISS|HSW_ANY_SNOOP,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = HSW_DEMAND_WRITE|
				       HSW_LLC_ACCESS,
		[ C(RESULT_MISS)   ] = HSW_DEMAND_WRITE|
				       HSW_L3_MISS|HSW_ANY_SNOOP,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = HSW_DEMAND_READ|
				       HSW_L3_MISS_LOCAL_DRAM|
				       HSW_SNOOP_DRAM,
		[ C(RESULT_MISS)   ] = HSW_DEMAND_READ|
				       HSW_L3_MISS_REMOTE|
				       HSW_SNOOP_DRAM,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = HSW_DEMAND_WRITE|
				       HSW_L3_MISS_LOCAL_DRAM|
				       HSW_SNOOP_DRAM,
		[ C(RESULT_MISS)   ] = HSW_DEMAND_WRITE|
				       HSW_L3_MISS_REMOTE|
				       HSW_SNOOP_DRAM,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 wesपंचांगere_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x010b, /* MEM_INST_RETIRED.LOADS       */
		[ C(RESULT_MISS)   ] = 0x0151, /* L1D.REPL                     */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x020b, /* MEM_INST_RETURED.STORES      */
		[ C(RESULT_MISS)   ] = 0x0251, /* L1D.M_REPL                   */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x014e, /* L1D_PREFETCH.REQUESTS        */
		[ C(RESULT_MISS)   ] = 0x024e, /* L1D_PREFETCH.MISS            */
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0380, /* L1I.READS                    */
		[ C(RESULT_MISS)   ] = 0x0280, /* L1I.MISSES                   */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		/* OFFCORE_RESPONSE.ANY_DATA.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.ANY_DATA.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	/*
	 * Use RFO, not WRITEBACK, because a ग_लिखो miss would typically occur
	 * on RFO.
	 */
	[ C(OP_WRITE) ] = अणु
		/* OFFCORE_RESPONSE.ANY_RFO.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.ANY_RFO.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		/* OFFCORE_RESPONSE.PREFETCH.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.PREFETCH.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x010b, /* MEM_INST_RETIRED.LOADS       */
		[ C(RESULT_MISS)   ] = 0x0108, /* DTLB_LOAD_MISSES.ANY         */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x020b, /* MEM_INST_RETURED.STORES      */
		[ C(RESULT_MISS)   ] = 0x010c, /* MEM_STORE_RETIRED.DTLB_MISS  */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01c0, /* INST_RETIRED.ANY_P           */
		[ C(RESULT_MISS)   ] = 0x0185, /* ITLB_MISSES.ANY              */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c4, /* BR_INST_RETIRED.ALL_BRANCHES */
		[ C(RESULT_MISS)   ] = 0x03e8, /* BPU_CLEARS.ANY               */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
 पूर्ण,
पूर्ण;

/*
 * Nehalem/Wesपंचांगere MSR_OFFCORE_RESPONSE bits;
 * See IA32 SDM Vol 3B 30.6.1.3
 */

#घोषणा NHM_DMND_DATA_RD	(1 << 0)
#घोषणा NHM_DMND_RFO		(1 << 1)
#घोषणा NHM_DMND_IFETCH		(1 << 2)
#घोषणा NHM_DMND_WB		(1 << 3)
#घोषणा NHM_PF_DATA_RD		(1 << 4)
#घोषणा NHM_PF_DATA_RFO		(1 << 5)
#घोषणा NHM_PF_IFETCH		(1 << 6)
#घोषणा NHM_OFFCORE_OTHER	(1 << 7)
#घोषणा NHM_UNCORE_HIT		(1 << 8)
#घोषणा NHM_OTHER_CORE_HIT_SNP	(1 << 9)
#घोषणा NHM_OTHER_CORE_HITM	(1 << 10)
        			/* reserved */
#घोषणा NHM_REMOTE_CACHE_FWD	(1 << 12)
#घोषणा NHM_REMOTE_DRAM		(1 << 13)
#घोषणा NHM_LOCAL_DRAM		(1 << 14)
#घोषणा NHM_NON_DRAM		(1 << 15)

#घोषणा NHM_LOCAL		(NHM_LOCAL_DRAM|NHM_REMOTE_CACHE_FWD)
#घोषणा NHM_REMOTE		(NHM_REMOTE_DRAM)

#घोषणा NHM_DMND_READ		(NHM_DMND_DATA_RD)
#घोषणा NHM_DMND_WRITE		(NHM_DMND_RFO|NHM_DMND_WB)
#घोषणा NHM_DMND_PREFETCH	(NHM_PF_DATA_RD|NHM_PF_DATA_RFO)

#घोषणा NHM_L3_HIT	(NHM_UNCORE_HIT|NHM_OTHER_CORE_HIT_SNP|NHM_OTHER_CORE_HITM)
#घोषणा NHM_L3_MISS	(NHM_NON_DRAM|NHM_LOCAL_DRAM|NHM_REMOTE_DRAM|NHM_REMOTE_CACHE_FWD)
#घोषणा NHM_L3_ACCESS	(NHM_L3_HIT|NHM_L3_MISS)

अटल __initस्थिर स्थिर u64 nehalem_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = NHM_DMND_READ|NHM_L3_ACCESS,
		[ C(RESULT_MISS)   ] = NHM_DMND_READ|NHM_L3_MISS,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = NHM_DMND_WRITE|NHM_L3_ACCESS,
		[ C(RESULT_MISS)   ] = NHM_DMND_WRITE|NHM_L3_MISS,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = NHM_DMND_PREFETCH|NHM_L3_ACCESS,
		[ C(RESULT_MISS)   ] = NHM_DMND_PREFETCH|NHM_L3_MISS,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = NHM_DMND_READ|NHM_LOCAL|NHM_REMOTE,
		[ C(RESULT_MISS)   ] = NHM_DMND_READ|NHM_REMOTE,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = NHM_DMND_WRITE|NHM_LOCAL|NHM_REMOTE,
		[ C(RESULT_MISS)   ] = NHM_DMND_WRITE|NHM_REMOTE,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = NHM_DMND_PREFETCH|NHM_LOCAL|NHM_REMOTE,
		[ C(RESULT_MISS)   ] = NHM_DMND_PREFETCH|NHM_REMOTE,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 nehalem_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x010b, /* MEM_INST_RETIRED.LOADS       */
		[ C(RESULT_MISS)   ] = 0x0151, /* L1D.REPL                     */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x020b, /* MEM_INST_RETURED.STORES      */
		[ C(RESULT_MISS)   ] = 0x0251, /* L1D.M_REPL                   */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x014e, /* L1D_PREFETCH.REQUESTS        */
		[ C(RESULT_MISS)   ] = 0x024e, /* L1D_PREFETCH.MISS            */
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0380, /* L1I.READS                    */
		[ C(RESULT_MISS)   ] = 0x0280, /* L1I.MISSES                   */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		/* OFFCORE_RESPONSE.ANY_DATA.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.ANY_DATA.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	/*
	 * Use RFO, not WRITEBACK, because a ग_लिखो miss would typically occur
	 * on RFO.
	 */
	[ C(OP_WRITE) ] = अणु
		/* OFFCORE_RESPONSE.ANY_RFO.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.ANY_RFO.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		/* OFFCORE_RESPONSE.PREFETCH.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.PREFETCH.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0f40, /* L1D_CACHE_LD.MESI   (alias)  */
		[ C(RESULT_MISS)   ] = 0x0108, /* DTLB_LOAD_MISSES.ANY         */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0f41, /* L1D_CACHE_ST.MESI   (alias)  */
		[ C(RESULT_MISS)   ] = 0x010c, /* MEM_STORE_RETIRED.DTLB_MISS  */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0x0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01c0, /* INST_RETIRED.ANY_P           */
		[ C(RESULT_MISS)   ] = 0x20c8, /* ITLB_MISS_RETIRED            */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c4, /* BR_INST_RETIRED.ALL_BRANCHES */
		[ C(RESULT_MISS)   ] = 0x03e8, /* BPU_CLEARS.ANY               */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(NODE) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 core2_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0f40, /* L1D_CACHE_LD.MESI          */
		[ C(RESULT_MISS)   ] = 0x0140, /* L1D_CACHE_LD.I_STATE       */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0f41, /* L1D_CACHE_ST.MESI          */
		[ C(RESULT_MISS)   ] = 0x0141, /* L1D_CACHE_ST.I_STATE       */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x104e, /* L1D_PREFETCH.REQUESTS      */
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0080, /* L1I.READS                  */
		[ C(RESULT_MISS)   ] = 0x0081, /* L1I.MISSES                 */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x4f29, /* L2_LD.MESI                 */
		[ C(RESULT_MISS)   ] = 0x4129, /* L2_LD.ISTATE               */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x4f2A, /* L2_ST.MESI                 */
		[ C(RESULT_MISS)   ] = 0x412A, /* L2_ST.ISTATE               */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0f40, /* L1D_CACHE_LD.MESI  (alias) */
		[ C(RESULT_MISS)   ] = 0x0208, /* DTLB_MISSES.MISS_LD        */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0f41, /* L1D_CACHE_ST.MESI  (alias) */
		[ C(RESULT_MISS)   ] = 0x0808, /* DTLB_MISSES.MISS_ST        */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c0, /* INST_RETIRED.ANY_P         */
		[ C(RESULT_MISS)   ] = 0x1282, /* ITLBMISSES                 */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c4, /* BR_INST_RETIRED.ANY        */
		[ C(RESULT_MISS)   ] = 0x00c5, /* BP_INST_RETIRED.MISPRED    */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 atom_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x2140, /* L1D_CACHE.LD               */
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x2240, /* L1D_CACHE.ST               */
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0380, /* L1I.READS                  */
		[ C(RESULT_MISS)   ] = 0x0280, /* L1I.MISSES                 */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x4f29, /* L2_LD.MESI                 */
		[ C(RESULT_MISS)   ] = 0x4129, /* L2_LD.ISTATE               */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x4f2A, /* L2_ST.MESI                 */
		[ C(RESULT_MISS)   ] = 0x412A, /* L2_ST.ISTATE               */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x2140, /* L1D_CACHE_LD.MESI  (alias) */
		[ C(RESULT_MISS)   ] = 0x0508, /* DTLB_MISSES.MISS_LD        */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x2240, /* L1D_CACHE_ST.MESI  (alias) */
		[ C(RESULT_MISS)   ] = 0x0608, /* DTLB_MISSES.MISS_ST        */
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c0, /* INST_RETIRED.ANY_P         */
		[ C(RESULT_MISS)   ] = 0x0282, /* ITLB.MISSES                */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c4, /* BR_INST_RETIRED.ANY        */
		[ C(RESULT_MISS)   ] = 0x00c5, /* BP_INST_RETIRED.MISPRED    */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
पूर्ण;

EVENT_ATTR_STR(topकरोwn-total-slots, td_total_slots_slm, "event=0x3c");
EVENT_ATTR_STR(topकरोwn-total-slots.scale, td_total_slots_scale_slm, "2");
/* no_alloc_cycles.not_delivered */
EVENT_ATTR_STR(topकरोwn-fetch-bubbles, td_fetch_bubbles_slm,
	       "event=0xca,umask=0x50");
EVENT_ATTR_STR(topकरोwn-fetch-bubbles.scale, td_fetch_bubbles_scale_slm, "2");
/* uops_retired.all */
EVENT_ATTR_STR(topकरोwn-slots-issued, td_slots_issued_slm,
	       "event=0xc2,umask=0x10");
/* uops_retired.all */
EVENT_ATTR_STR(topकरोwn-slots-retired, td_slots_retired_slm,
	       "event=0xc2,umask=0x10");

अटल काष्ठा attribute *slm_events_attrs[] = अणु
	EVENT_PTR(td_total_slots_slm),
	EVENT_PTR(td_total_slots_scale_slm),
	EVENT_PTR(td_fetch_bubbles_slm),
	EVENT_PTR(td_fetch_bubbles_scale_slm),
	EVENT_PTR(td_slots_issued_slm),
	EVENT_PTR(td_slots_retired_slm),
	शून्य
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_slm_extra_regs[] __पढ़ो_mostly =
अणु
	/* must define OFFCORE_RSP_X first, see पूर्णांकel_fixup_er() */
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x768005ffffull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x02b7, MSR_OFFCORE_RSP_1, 0x368005ffffull, RSP_1),
	EVENT_EXTRA_END
पूर्ण;

#घोषणा SLM_DMND_READ		SNB_DMND_DATA_RD
#घोषणा SLM_DMND_WRITE		SNB_DMND_RFO
#घोषणा SLM_DMND_PREFETCH	(SNB_PF_DATA_RD|SNB_PF_RFO)

#घोषणा SLM_SNP_ANY		(SNB_SNP_NONE|SNB_SNP_MISS|SNB_NO_FWD|SNB_HITM)
#घोषणा SLM_LLC_ACCESS		SNB_RESP_ANY
#घोषणा SLM_LLC_MISS		(SLM_SNP_ANY|SNB_NON_DRAM)

अटल __initस्थिर स्थिर u64 slm_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = SLM_DMND_READ|SLM_LLC_ACCESS,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = SLM_DMND_WRITE|SLM_LLC_ACCESS,
		[ C(RESULT_MISS)   ] = SLM_DMND_WRITE|SLM_LLC_MISS,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = SLM_DMND_PREFETCH|SLM_LLC_ACCESS,
		[ C(RESULT_MISS)   ] = SLM_DMND_PREFETCH|SLM_LLC_MISS,
	पूर्ण,
 पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 slm_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] =
अणु
 [ C(L1D) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0x0104, /* LD_DCU_MISS */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(L1I ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x0380, /* ICACHE.ACCESSES */
		[ C(RESULT_MISS)   ] = 0x0280, /* ICACGE.MISSES */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(LL  ) ] = अणु
	[ C(OP_READ) ] = अणु
		/* OFFCORE_RESPONSE.ANY_DATA.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		/* OFFCORE_RESPONSE.ANY_RFO.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.ANY_RFO.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		/* OFFCORE_RESPONSE.PREFETCH.LOCAL_CACHE */
		[ C(RESULT_ACCESS) ] = 0x01b7,
		/* OFFCORE_RESPONSE.PREFETCH.ANY_LLC_MISS */
		[ C(RESULT_MISS)   ] = 0x01b7,
	पूर्ण,
 पूर्ण,
 [ C(DTLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0x0804, /* LD_DTLB_MISS */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = 0,
		[ C(RESULT_MISS)   ] = 0,
	पूर्ण,
 पूर्ण,
 [ C(ITLB) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c0, /* INST_RETIRED.ANY_P */
		[ C(RESULT_MISS)   ] = 0x40205, /* PAGE_WALKS.I_SIDE_WALKS */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
 [ C(BPU ) ] = अणु
	[ C(OP_READ) ] = अणु
		[ C(RESULT_ACCESS) ] = 0x00c4, /* BR_INST_RETIRED.ANY */
		[ C(RESULT_MISS)   ] = 0x00c5, /* BP_INST_RETIRED.MISPRED */
	पूर्ण,
	[ C(OP_WRITE) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
	[ C(OP_PREFETCH) ] = अणु
		[ C(RESULT_ACCESS) ] = -1,
		[ C(RESULT_MISS)   ] = -1,
	पूर्ण,
 पूर्ण,
पूर्ण;

EVENT_ATTR_STR(topकरोwn-total-slots, td_total_slots_glm, "event=0x3c");
EVENT_ATTR_STR(topकरोwn-total-slots.scale, td_total_slots_scale_glm, "3");
/* UOPS_NOT_DELIVERED.ANY */
EVENT_ATTR_STR(topकरोwn-fetch-bubbles, td_fetch_bubbles_glm, "event=0x9c");
/* ISSUE_SLOTS_NOT_CONSUMED.RECOVERY */
EVENT_ATTR_STR(topकरोwn-recovery-bubbles, td_recovery_bubbles_glm, "event=0xca,umask=0x02");
/* UOPS_RETIRED.ANY */
EVENT_ATTR_STR(topकरोwn-slots-retired, td_slots_retired_glm, "event=0xc2");
/* UOPS_ISSUED.ANY */
EVENT_ATTR_STR(topकरोwn-slots-issued, td_slots_issued_glm, "event=0x0e");

अटल काष्ठा attribute *glm_events_attrs[] = अणु
	EVENT_PTR(td_total_slots_glm),
	EVENT_PTR(td_total_slots_scale_glm),
	EVENT_PTR(td_fetch_bubbles_glm),
	EVENT_PTR(td_recovery_bubbles_glm),
	EVENT_PTR(td_slots_issued_glm),
	EVENT_PTR(td_slots_retired_glm),
	शून्य
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_glm_extra_regs[] __पढ़ो_mostly = अणु
	/* must define OFFCORE_RSP_X first, see पूर्णांकel_fixup_er() */
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x760005ffbfull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x02b7, MSR_OFFCORE_RSP_1, 0x360005ffbfull, RSP_1),
	EVENT_EXTRA_END
पूर्ण;

#घोषणा GLM_DEMAND_DATA_RD		BIT_ULL(0)
#घोषणा GLM_DEMAND_RFO			BIT_ULL(1)
#घोषणा GLM_ANY_RESPONSE		BIT_ULL(16)
#घोषणा GLM_SNP_NONE_OR_MISS		BIT_ULL(33)
#घोषणा GLM_DEMAND_READ			GLM_DEMAND_DATA_RD
#घोषणा GLM_DEMAND_WRITE		GLM_DEMAND_RFO
#घोषणा GLM_DEMAND_PREFETCH		(SNB_PF_DATA_RD|SNB_PF_RFO)
#घोषणा GLM_LLC_ACCESS			GLM_ANY_RESPONSE
#घोषणा GLM_SNP_ANY			(GLM_SNP_NONE_OR_MISS|SNB_NO_FWD|SNB_HITM)
#घोषणा GLM_LLC_MISS			(GLM_SNP_ANY|SNB_NON_DRAM)

अटल __initस्थिर स्थिर u64 glm_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	[C(L1D)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x81d0,	/* MEM_UOPS_RETIRED.ALL_LOADS */
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x82d0,	/* MEM_UOPS_RETIRED.ALL_STORES */
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x0380,	/* ICACHE.ACCESSES */
			[C(RESULT_MISS)]	= 0x0280,	/* ICACHE.MISSES */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
			[C(RESULT_MISS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
			[C(RESULT_MISS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
			[C(RESULT_MISS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
		पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x81d0,	/* MEM_UOPS_RETIRED.ALL_LOADS */
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x82d0,	/* MEM_UOPS_RETIRED.ALL_STORES */
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x00c0,	/* INST_RETIRED.ANY_P */
			[C(RESULT_MISS)]	= 0x0481,	/* ITLB.MISS */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x00c4,	/* BR_INST_RETIRED.ALL_BRANCHES */
			[C(RESULT_MISS)]	= 0x00c5,	/* BR_MISP_RETIRED.ALL_BRANCHES */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 glm_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= GLM_DEMAND_READ|
						  GLM_LLC_ACCESS,
			[C(RESULT_MISS)]	= GLM_DEMAND_READ|
						  GLM_LLC_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= GLM_DEMAND_WRITE|
						  GLM_LLC_ACCESS,
			[C(RESULT_MISS)]	= GLM_DEMAND_WRITE|
						  GLM_LLC_MISS,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= GLM_DEMAND_PREFETCH|
						  GLM_LLC_ACCESS,
			[C(RESULT_MISS)]	= GLM_DEMAND_PREFETCH|
						  GLM_LLC_MISS,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 glp_hw_cache_event_ids
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	[C(L1D)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x81d0,	/* MEM_UOPS_RETIRED.ALL_LOADS */
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x82d0,	/* MEM_UOPS_RETIRED.ALL_STORES */
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x0380,	/* ICACHE.ACCESSES */
			[C(RESULT_MISS)]	= 0x0280,	/* ICACHE.MISSES */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
			[C(RESULT_MISS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
			[C(RESULT_MISS)]	= 0x1b7,	/* OFFCORE_RESPONSE */
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x81d0,	/* MEM_UOPS_RETIRED.ALL_LOADS */
			[C(RESULT_MISS)]	= 0xe08,	/* DTLB_LOAD_MISSES.WALK_COMPLETED */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x82d0,	/* MEM_UOPS_RETIRED.ALL_STORES */
			[C(RESULT_MISS)]	= 0xe49,	/* DTLB_STORE_MISSES.WALK_COMPLETED */
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x00c0,	/* INST_RETIRED.ANY_P */
			[C(RESULT_MISS)]	= 0x0481,	/* ITLB.MISS */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x00c4,	/* BR_INST_RETIRED.ALL_BRANCHES */
			[C(RESULT_MISS)]	= 0x00c5,	/* BR_MISP_RETIRED.ALL_BRANCHES */
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= -1,
			[C(RESULT_MISS)]	= -1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल __initस्थिर स्थिर u64 glp_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= GLM_DEMAND_READ|
						  GLM_LLC_ACCESS,
			[C(RESULT_MISS)]	= GLM_DEMAND_READ|
						  GLM_LLC_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= GLM_DEMAND_WRITE|
						  GLM_LLC_ACCESS,
			[C(RESULT_MISS)]	= GLM_DEMAND_WRITE|
						  GLM_LLC_MISS,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा TNT_LOCAL_DRAM			BIT_ULL(26)
#घोषणा TNT_DEMAND_READ			GLM_DEMAND_DATA_RD
#घोषणा TNT_DEMAND_WRITE		GLM_DEMAND_RFO
#घोषणा TNT_LLC_ACCESS			GLM_ANY_RESPONSE
#घोषणा TNT_SNP_ANY			(SNB_SNP_NOT_NEEDED|SNB_SNP_MISS| \
					 SNB_NO_FWD|SNB_SNP_FWD|SNB_HITM)
#घोषणा TNT_LLC_MISS			(TNT_SNP_ANY|SNB_NON_DRAM|TNT_LOCAL_DRAM)

अटल __initस्थिर स्थिर u64 tnt_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= TNT_DEMAND_READ|
						  TNT_LLC_ACCESS,
			[C(RESULT_MISS)]	= TNT_DEMAND_READ|
						  TNT_LLC_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= TNT_DEMAND_WRITE|
						  TNT_LLC_ACCESS,
			[C(RESULT_MISS)]	= TNT_DEMAND_WRITE|
						  TNT_LLC_MISS,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x0,
			[C(RESULT_MISS)]	= 0x0,
		पूर्ण,
	पूर्ण,
पूर्ण;

EVENT_ATTR_STR(topकरोwn-fe-bound,       td_fe_bound_tnt,        "event=0x71,umask=0x0");
EVENT_ATTR_STR(topकरोwn-retiring,       td_retiring_tnt,        "event=0xc2,umask=0x0");
EVENT_ATTR_STR(topकरोwn-bad-spec,       td_bad_spec_tnt,        "event=0x73,umask=0x6");
EVENT_ATTR_STR(topकरोwn-be-bound,       td_be_bound_tnt,        "event=0x74,umask=0x0");

अटल काष्ठा attribute *tnt_events_attrs[] = अणु
	EVENT_PTR(td_fe_bound_tnt),
	EVENT_PTR(td_retiring_tnt),
	EVENT_PTR(td_bad_spec_tnt),
	EVENT_PTR(td_be_bound_tnt),
	शून्य,
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_tnt_extra_regs[] __पढ़ो_mostly = अणु
	/* must define OFFCORE_RSP_X first, see पूर्णांकel_fixup_er() */
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x800ff0ffffff9fffull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x02b7, MSR_OFFCORE_RSP_1, 0xff0ffffff9fffull, RSP_1),
	EVENT_EXTRA_END
पूर्ण;

अटल काष्ठा extra_reg पूर्णांकel_grt_extra_regs[] __पढ़ो_mostly = अणु
	/* must define OFFCORE_RSP_X first, see पूर्णांकel_fixup_er() */
	INTEL_UEVENT_EXTRA_REG(0x01b7, MSR_OFFCORE_RSP_0, 0x3fffffffffull, RSP_0),
	INTEL_UEVENT_EXTRA_REG(0x02b7, MSR_OFFCORE_RSP_1, 0x3fffffffffull, RSP_1),
	INTEL_UEVENT_PEBS_LDLAT_EXTRA_REG(0x5d0),
	EVENT_EXTRA_END
पूर्ण;

#घोषणा KNL_OT_L2_HITE		BIT_ULL(19) /* Other Tile L2 Hit */
#घोषणा KNL_OT_L2_HITF		BIT_ULL(20) /* Other Tile L2 Hit */
#घोषणा KNL_MCDRAM_LOCAL	BIT_ULL(21)
#घोषणा KNL_MCDRAM_FAR		BIT_ULL(22)
#घोषणा KNL_DDR_LOCAL		BIT_ULL(23)
#घोषणा KNL_DDR_FAR		BIT_ULL(24)
#घोषणा KNL_DRAM_ANY		(KNL_MCDRAM_LOCAL | KNL_MCDRAM_FAR | \
				    KNL_DDR_LOCAL | KNL_DDR_FAR)
#घोषणा KNL_L2_READ		SLM_DMND_READ
#घोषणा KNL_L2_WRITE		SLM_DMND_WRITE
#घोषणा KNL_L2_PREFETCH		SLM_DMND_PREFETCH
#घोषणा KNL_L2_ACCESS		SLM_LLC_ACCESS
#घोषणा KNL_L2_MISS		(KNL_OT_L2_HITE | KNL_OT_L2_HITF | \
				   KNL_DRAM_ANY | SNB_SNP_ANY | \
						  SNB_NON_DRAM)

अटल __initस्थिर स्थिर u64 knl_hw_cache_extra_regs
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = KNL_L2_READ | KNL_L2_ACCESS,
			[C(RESULT_MISS)]   = 0,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = KNL_L2_WRITE | KNL_L2_ACCESS,
			[C(RESULT_MISS)]   = KNL_L2_WRITE | KNL_L2_MISS,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = KNL_L2_PREFETCH | KNL_L2_ACCESS,
			[C(RESULT_MISS)]   = KNL_L2_PREFETCH | KNL_L2_MISS,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * Used from PMIs where the LBRs are alपढ़ोy disabled.
 *
 * This function could be called consecutively. It is required to reमुख्य in
 * disabled state अगर called consecutively.
 *
 * During consecutive calls, the same disable value will be written to related
 * रेजिस्टरs, so the PMU state reमुख्यs unchanged.
 *
 * पूर्णांकel_bts events करोn't coexist with intel PMU's BTS events because of
 * x86_add_exclusive(x86_lbr_exclusive_lbr); there's no need to keep them
 * disabled around पूर्णांकel PMU's event batching etc, only inside the PMI handler.
 *
 * Aव्योम PEBS_ENABLE MSR access in PMIs.
 * The GLOBAL_CTRL has been disabled. All the counters करो not count anymore.
 * It करोesn't matter अगर the PEBS is enabled or not.
 * Usually, the PEBS status are not changed in PMIs. It's unnecessary to
 * access PEBS_ENABLE MSR in disable_all()/enable_all().
 * However, there are some हालs which may change PEBS status, e.g. PMI
 * throttle. The PEBS_ENABLE should be updated where the status changes.
 */
अटल व्योम __पूर्णांकel_pmu_disable_all(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL, 0);

	अगर (test_bit(INTEL_PMC_IDX_FIXED_BTS, cpuc->active_mask))
		पूर्णांकel_pmu_disable_bts();
पूर्ण

अटल व्योम पूर्णांकel_pmu_disable_all(व्योम)
अणु
	__पूर्णांकel_pmu_disable_all();
	पूर्णांकel_pmu_pebs_disable_all();
	पूर्णांकel_pmu_lbr_disable_all();
पूर्ण

अटल व्योम __पूर्णांकel_pmu_enable_all(पूर्णांक added, bool pmi)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	u64 पूर्णांकel_ctrl = hybrid(cpuc->pmu, पूर्णांकel_ctrl);

	पूर्णांकel_pmu_lbr_enable_all(pmi);
	wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL,
	       पूर्णांकel_ctrl & ~cpuc->पूर्णांकel_ctrl_guest_mask);

	अगर (test_bit(INTEL_PMC_IDX_FIXED_BTS, cpuc->active_mask)) अणु
		काष्ठा perf_event *event =
			cpuc->events[INTEL_PMC_IDX_FIXED_BTS];

		अगर (WARN_ON_ONCE(!event))
			वापस;

		पूर्णांकel_pmu_enable_bts(event->hw.config);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_enable_all(पूर्णांक added)
अणु
	पूर्णांकel_pmu_pebs_enable_all();
	__पूर्णांकel_pmu_enable_all(added, false);
पूर्ण

/*
 * Workaround क्रम:
 *   Intel Errata AAK100 (model 26)
 *   Intel Errata AAP53  (model 30)
 *   Intel Errata BD53   (model 44)
 *
 * The official story:
 *   These chips need to be 'reset' when adding counters by programming the
 *   magic three (non-counting) events 0x4300B5, 0x4300D2, and 0x4300B1 either
 *   in sequence on the same PMC or on dअगरferent PMCs.
 *
 * In practice it appears some of these events करो in fact count, and
 * we need to program all 4 events.
 */
अटल व्योम पूर्णांकel_pmu_nhm_workaround(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	अटल स्थिर अचिन्हित दीर्घ nhm_magic[4] = अणु
		0x4300B5,
		0x4300D2,
		0x4300B1,
		0x4300B1
	पूर्ण;
	काष्ठा perf_event *event;
	पूर्णांक i;

	/*
	 * The Errata requires below steps:
	 * 1) Clear MSR_IA32_PEBS_ENABLE and MSR_CORE_PERF_GLOBAL_CTRL;
	 * 2) Configure 4 PERFEVTSELx with the magic events and clear
	 *    the corresponding PMCx;
	 * 3) set bit0~bit3 of MSR_CORE_PERF_GLOBAL_CTRL;
	 * 4) Clear MSR_CORE_PERF_GLOBAL_CTRL;
	 * 5) Clear 4 pairs of ERFEVTSELx and PMCx;
	 */

	/*
	 * The real steps we choose are a little dअगरferent from above.
	 * A) To reduce MSR operations, we करोn't run step 1) as they
	 *    are alपढ़ोy cleared beक्रमe this function is called;
	 * B) Call x86_perf_event_update to save PMCx beक्रमe configuring
	 *    PERFEVTSELx with magic number;
	 * C) With step 5), we करो clear only when the PERFEVTSELx is
	 *    not used currently.
	 * D) Call x86_perf_event_set_period to restore PMCx;
	 */

	/* We always operate 4 pairs of PERF Counters */
	क्रम (i = 0; i < 4; i++) अणु
		event = cpuc->events[i];
		अगर (event)
			x86_perf_event_update(event);
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		wrmsrl(MSR_ARCH_PERFMON_EVENTSEL0 + i, nhm_magic[i]);
		wrmsrl(MSR_ARCH_PERFMON_PERFCTR0 + i, 0x0);
	पूर्ण

	wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL, 0xf);
	wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL, 0x0);

	क्रम (i = 0; i < 4; i++) अणु
		event = cpuc->events[i];

		अगर (event) अणु
			x86_perf_event_set_period(event);
			__x86_pmu_enable_event(&event->hw,
					ARCH_PERFMON_EVENTSEL_ENABLE);
		पूर्ण अन्यथा
			wrmsrl(MSR_ARCH_PERFMON_EVENTSEL0 + i, 0x0);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_nhm_enable_all(पूर्णांक added)
अणु
	अगर (added)
		पूर्णांकel_pmu_nhm_workaround();
	पूर्णांकel_pmu_enable_all(added);
पूर्ण

अटल व्योम पूर्णांकel_set_tfa(काष्ठा cpu_hw_events *cpuc, bool on)
अणु
	u64 val = on ? MSR_TFA_RTM_FORCE_ABORT : 0;

	अगर (cpuc->tfa_shaकरोw != val) अणु
		cpuc->tfa_shaकरोw = val;
		wrmsrl(MSR_TSX_FORCE_ABORT, val);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_tfa_commit_scheduling(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx, पूर्णांक cntr)
अणु
	/*
	 * We're going to use PMC3, make sure TFA is set beक्रमe we touch it.
	 */
	अगर (cntr == 3)
		पूर्णांकel_set_tfa(cpuc, true);
पूर्ण

अटल व्योम पूर्णांकel_tfa_pmu_enable_all(पूर्णांक added)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * If we find PMC3 is no दीर्घer used when we enable the PMU, we can
	 * clear TFA.
	 */
	अगर (!test_bit(3, cpuc->active_mask))
		पूर्णांकel_set_tfa(cpuc, false);

	पूर्णांकel_pmu_enable_all(added);
पूर्ण

अटल अंतरभूत u64 पूर्णांकel_pmu_get_status(व्योम)
अणु
	u64 status;

	rdmsrl(MSR_CORE_PERF_GLOBAL_STATUS, status);

	वापस status;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pmu_ack_status(u64 ack)
अणु
	wrmsrl(MSR_CORE_PERF_GLOBAL_OVF_CTRL, ack);
पूर्ण

अटल अंतरभूत bool event_is_checkpoपूर्णांकed(काष्ठा perf_event *event)
अणु
	वापस unlikely(event->hw.config & HSW_IN_TX_CHECKPOINTED) != 0;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_set_masks(काष्ठा perf_event *event, पूर्णांक idx)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (event->attr.exclude_host)
		__set_bit(idx, (अचिन्हित दीर्घ *)&cpuc->पूर्णांकel_ctrl_guest_mask);
	अगर (event->attr.exclude_guest)
		__set_bit(idx, (अचिन्हित दीर्घ *)&cpuc->पूर्णांकel_ctrl_host_mask);
	अगर (event_is_checkpoपूर्णांकed(event))
		__set_bit(idx, (अचिन्हित दीर्घ *)&cpuc->पूर्णांकel_cp_status);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_clear_masks(काष्ठा perf_event *event, पूर्णांक idx)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	__clear_bit(idx, (अचिन्हित दीर्घ *)&cpuc->पूर्णांकel_ctrl_guest_mask);
	__clear_bit(idx, (अचिन्हित दीर्घ *)&cpuc->पूर्णांकel_ctrl_host_mask);
	__clear_bit(idx, (अचिन्हित दीर्घ *)&cpuc->पूर्णांकel_cp_status);
पूर्ण

अटल व्योम पूर्णांकel_pmu_disable_fixed(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 ctrl_val, mask;
	पूर्णांक idx = hwc->idx;

	अगर (is_topकरोwn_idx(idx)) अणु
		काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

		/*
		 * When there are other active TopDown events,
		 * करोn't disable the fixed counter 3.
		 */
		अगर (*(u64 *)cpuc->active_mask & INTEL_PMC_OTHER_TOPDOWN_BITS(idx))
			वापस;
		idx = INTEL_PMC_IDX_FIXED_SLOTS;
	पूर्ण

	पूर्णांकel_clear_masks(event, idx);

	mask = 0xfULL << ((idx - INTEL_PMC_IDX_FIXED) * 4);
	rdmsrl(hwc->config_base, ctrl_val);
	ctrl_val &= ~mask;
	wrmsrl(hwc->config_base, ctrl_val);
पूर्ण

अटल व्योम पूर्णांकel_pmu_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	चयन (idx) अणु
	हाल 0 ... INTEL_PMC_IDX_FIXED - 1:
		पूर्णांकel_clear_masks(event, idx);
		x86_pmu_disable_event(event);
		अवरोध;
	हाल INTEL_PMC_IDX_FIXED ... INTEL_PMC_IDX_FIXED_BTS - 1:
	हाल INTEL_PMC_IDX_METRIC_BASE ... INTEL_PMC_IDX_METRIC_END:
		पूर्णांकel_pmu_disable_fixed(event);
		अवरोध;
	हाल INTEL_PMC_IDX_FIXED_BTS:
		पूर्णांकel_pmu_disable_bts();
		पूर्णांकel_pmu_drain_bts_buffer();
		वापस;
	हाल INTEL_PMC_IDX_FIXED_VLBR:
		पूर्णांकel_clear_masks(event, idx);
		अवरोध;
	शेष:
		पूर्णांकel_clear_masks(event, idx);
		pr_warn("Failed to disable the event with invalid index %d\n",
			idx);
		वापस;
	पूर्ण

	/*
	 * Needs to be called after x86_pmu_disable_event,
	 * so we करोn't trigger the event without PEBS bit set.
	 */
	अगर (unlikely(event->attr.precise_ip))
		पूर्णांकel_pmu_pebs_disable(event);
पूर्ण

अटल व्योम पूर्णांकel_pmu_del_event(काष्ठा perf_event *event)
अणु
	अगर (needs_branch_stack(event))
		पूर्णांकel_pmu_lbr_del(event);
	अगर (event->attr.precise_ip)
		पूर्णांकel_pmu_pebs_del(event);
पूर्ण

अटल पूर्णांक icl_set_topकरोwn_event_period(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	s64 left = local64_पढ़ो(&hwc->period_left);

	/*
	 * The values in PERF_METRICS MSR are derived from fixed counter 3.
	 * Software should start both रेजिस्टरs, PERF_METRICS and fixed
	 * counter 3, from zero.
	 * Clear PERF_METRICS and Fixed counter 3 in initialization.
	 * After that, both MSRs will be cleared क्रम each पढ़ो.
	 * Don't need to clear them again.
	 */
	अगर (left == x86_pmu.max_period) अणु
		wrmsrl(MSR_CORE_PERF_FIXED_CTR3, 0);
		wrmsrl(MSR_PERF_METRICS, 0);
		hwc->saved_slots = 0;
		hwc->saved_metric = 0;
	पूर्ण

	अगर ((hwc->saved_slots) && is_slots_event(event)) अणु
		wrmsrl(MSR_CORE_PERF_FIXED_CTR3, hwc->saved_slots);
		wrmsrl(MSR_PERF_METRICS, hwc->saved_metric);
	पूर्ण

	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल पूर्णांक adl_set_topकरोwn_event_period(काष्ठा perf_event *event)
अणु
	काष्ठा x86_hybrid_pmu *pmu = hybrid_pmu(event->pmu);

	अगर (pmu->cpu_type != hybrid_big)
		वापस 0;

	वापस icl_set_topकरोwn_event_period(event);
पूर्ण

अटल अंतरभूत u64 icl_get_metrics_event_value(u64 metric, u64 slots, पूर्णांक idx)
अणु
	u32 val;

	/*
	 * The metric is reported as an 8bit पूर्णांकeger fraction
	 * summing up to 0xff.
	 * slots-in-metric = (Metric / 0xff) * slots
	 */
	val = (metric >> ((idx - INTEL_PMC_IDX_METRIC_BASE) * 8)) & 0xff;
	वापस  mul_u64_u32_भाग(slots, val, 0xff);
पूर्ण

अटल u64 icl_get_topकरोwn_value(काष्ठा perf_event *event,
				       u64 slots, u64 metrics)
अणु
	पूर्णांक idx = event->hw.idx;
	u64 delta;

	अगर (is_metric_idx(idx))
		delta = icl_get_metrics_event_value(metrics, slots, idx);
	अन्यथा
		delta = slots;

	वापस delta;
पूर्ण

अटल व्योम __icl_update_topकरोwn_event(काष्ठा perf_event *event,
				       u64 slots, u64 metrics,
				       u64 last_slots, u64 last_metrics)
अणु
	u64 delta, last = 0;

	delta = icl_get_topकरोwn_value(event, slots, metrics);
	अगर (last_slots)
		last = icl_get_topकरोwn_value(event, last_slots, last_metrics);

	/*
	 * The 8bit पूर्णांकeger fraction of metric may be not accurate,
	 * especially when the changes is very small.
	 * For example, अगर only a few bad_spec happens, the fraction
	 * may be reduced from 1 to 0. If so, the bad_spec event value
	 * will be 0 which is definitely less than the last value.
	 * Aव्योम update event->count क्रम this हाल.
	 */
	अगर (delta > last) अणु
		delta -= last;
		local64_add(delta, &event->count);
	पूर्ण
पूर्ण

अटल व्योम update_saved_topकरोwn_regs(काष्ठा perf_event *event, u64 slots,
				      u64 metrics, पूर्णांक metric_end)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा perf_event *other;
	पूर्णांक idx;

	event->hw.saved_slots = slots;
	event->hw.saved_metric = metrics;

	क्रम_each_set_bit(idx, cpuc->active_mask, metric_end + 1) अणु
		अगर (!is_topकरोwn_idx(idx))
			जारी;
		other = cpuc->events[idx];
		other->hw.saved_slots = slots;
		other->hw.saved_metric = metrics;
	पूर्ण
पूर्ण

/*
 * Update all active Topकरोwn events.
 *
 * The PERF_METRICS and Fixed counter 3 are पढ़ो separately. The values may be
 * modअगरy by a NMI. PMU has to be disabled beक्रमe calling this function.
 */

अटल u64 पूर्णांकel_update_topकरोwn_event(काष्ठा perf_event *event, पूर्णांक metric_end)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा perf_event *other;
	u64 slots, metrics;
	bool reset = true;
	पूर्णांक idx;

	/* पढ़ो Fixed counter 3 */
	rdpmcl((3 | INTEL_PMC_FIXED_RDPMC_BASE), slots);
	अगर (!slots)
		वापस 0;

	/* पढ़ो PERF_METRICS */
	rdpmcl(INTEL_PMC_FIXED_RDPMC_METRICS, metrics);

	क्रम_each_set_bit(idx, cpuc->active_mask, metric_end + 1) अणु
		अगर (!is_topकरोwn_idx(idx))
			जारी;
		other = cpuc->events[idx];
		__icl_update_topकरोwn_event(other, slots, metrics,
					   event ? event->hw.saved_slots : 0,
					   event ? event->hw.saved_metric : 0);
	पूर्ण

	/*
	 * Check and update this event, which may have been cleared
	 * in active_mask e.g. x86_pmu_stop()
	 */
	अगर (event && !test_bit(event->hw.idx, cpuc->active_mask)) अणु
		__icl_update_topकरोwn_event(event, slots, metrics,
					   event->hw.saved_slots,
					   event->hw.saved_metric);

		/*
		 * In x86_pmu_stop(), the event is cleared in active_mask first,
		 * then drain the delta, which indicates context चयन क्रम
		 * counting.
		 * Save metric and slots क्रम context चयन.
		 * Don't need to reset the PERF_METRICS and Fixed counter 3.
		 * Because the values will be restored in next schedule in.
		 */
		update_saved_topकरोwn_regs(event, slots, metrics, metric_end);
		reset = false;
	पूर्ण

	अगर (reset) अणु
		/* The fixed counter 3 has to be written beक्रमe the PERF_METRICS. */
		wrmsrl(MSR_CORE_PERF_FIXED_CTR3, 0);
		wrmsrl(MSR_PERF_METRICS, 0);
		अगर (event)
			update_saved_topकरोwn_regs(event, 0, 0, metric_end);
	पूर्ण

	वापस slots;
पूर्ण

अटल u64 icl_update_topकरोwn_event(काष्ठा perf_event *event)
अणु
	वापस पूर्णांकel_update_topकरोwn_event(event, INTEL_PMC_IDX_METRIC_BASE +
						 x86_pmu.num_topकरोwn_events - 1);
पूर्ण

अटल u64 adl_update_topकरोwn_event(काष्ठा perf_event *event)
अणु
	काष्ठा x86_hybrid_pmu *pmu = hybrid_pmu(event->pmu);

	अगर (pmu->cpu_type != hybrid_big)
		वापस 0;

	वापस icl_update_topकरोwn_event(event);
पूर्ण


अटल व्योम पूर्णांकel_pmu_पढ़ो_topकरोwn_event(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/* Only need to call update_topकरोwn_event() once क्रम group पढ़ो. */
	अगर ((cpuc->txn_flags & PERF_PMU_TXN_READ) &&
	    !is_slots_event(event))
		वापस;

	perf_pmu_disable(event->pmu);
	x86_pmu.update_topकरोwn_event(event);
	perf_pmu_enable(event->pmu);
पूर्ण

अटल व्योम पूर्णांकel_pmu_पढ़ो_event(काष्ठा perf_event *event)
अणु
	अगर (event->hw.flags & PERF_X86_EVENT_AUTO_RELOAD)
		पूर्णांकel_pmu_स्वतः_reload_पढ़ो(event);
	अन्यथा अगर (is_topकरोwn_count(event) && x86_pmu.update_topकरोwn_event)
		पूर्णांकel_pmu_पढ़ो_topकरोwn_event(event);
	अन्यथा
		x86_perf_event_update(event);
पूर्ण

अटल व्योम पूर्णांकel_pmu_enable_fixed(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 ctrl_val, mask, bits = 0;
	पूर्णांक idx = hwc->idx;

	अगर (is_topकरोwn_idx(idx)) अणु
		काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
		/*
		 * When there are other active TopDown events,
		 * करोn't enable the fixed counter 3 again.
		 */
		अगर (*(u64 *)cpuc->active_mask & INTEL_PMC_OTHER_TOPDOWN_BITS(idx))
			वापस;

		idx = INTEL_PMC_IDX_FIXED_SLOTS;
	पूर्ण

	पूर्णांकel_set_masks(event, idx);

	/*
	 * Enable IRQ generation (0x8), अगर not PEBS,
	 * and enable ring-3 counting (0x2) and ring-0 counting (0x1)
	 * अगर requested:
	 */
	अगर (!event->attr.precise_ip)
		bits |= 0x8;
	अगर (hwc->config & ARCH_PERFMON_EVENTSEL_USR)
		bits |= 0x2;
	अगर (hwc->config & ARCH_PERFMON_EVENTSEL_OS)
		bits |= 0x1;

	/*
	 * ANY bit is supported in v3 and up
	 */
	अगर (x86_pmu.version > 2 && hwc->config & ARCH_PERFMON_EVENTSEL_ANY)
		bits |= 0x4;

	idx -= INTEL_PMC_IDX_FIXED;
	bits <<= (idx * 4);
	mask = 0xfULL << (idx * 4);

	अगर (x86_pmu.पूर्णांकel_cap.pebs_baseline && event->attr.precise_ip) अणु
		bits |= ICL_FIXED_0_ADAPTIVE << (idx * 4);
		mask |= ICL_FIXED_0_ADAPTIVE << (idx * 4);
	पूर्ण

	rdmsrl(hwc->config_base, ctrl_val);
	ctrl_val &= ~mask;
	ctrl_val |= bits;
	wrmsrl(hwc->config_base, ctrl_val);
पूर्ण

अटल व्योम पूर्णांकel_pmu_enable_event(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (unlikely(event->attr.precise_ip))
		पूर्णांकel_pmu_pebs_enable(event);

	चयन (idx) अणु
	हाल 0 ... INTEL_PMC_IDX_FIXED - 1:
		पूर्णांकel_set_masks(event, idx);
		__x86_pmu_enable_event(hwc, ARCH_PERFMON_EVENTSEL_ENABLE);
		अवरोध;
	हाल INTEL_PMC_IDX_FIXED ... INTEL_PMC_IDX_FIXED_BTS - 1:
	हाल INTEL_PMC_IDX_METRIC_BASE ... INTEL_PMC_IDX_METRIC_END:
		पूर्णांकel_pmu_enable_fixed(event);
		अवरोध;
	हाल INTEL_PMC_IDX_FIXED_BTS:
		अगर (!__this_cpu_पढ़ो(cpu_hw_events.enabled))
			वापस;
		पूर्णांकel_pmu_enable_bts(hwc->config);
		अवरोध;
	हाल INTEL_PMC_IDX_FIXED_VLBR:
		पूर्णांकel_set_masks(event, idx);
		अवरोध;
	शेष:
		pr_warn("Failed to enable the event with invalid index %d\n",
			idx);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_add_event(काष्ठा perf_event *event)
अणु
	अगर (event->attr.precise_ip)
		पूर्णांकel_pmu_pebs_add(event);
	अगर (needs_branch_stack(event))
		पूर्णांकel_pmu_lbr_add(event);
पूर्ण

/*
 * Save and restart an expired event. Called by NMI contexts,
 * so it has to be careful about preempting normal event ops:
 */
पूर्णांक पूर्णांकel_pmu_save_and_restart(काष्ठा perf_event *event)
अणु
	x86_perf_event_update(event);
	/*
	 * For a checkpoपूर्णांकed counter always reset back to 0.  This
	 * aव्योमs a situation where the counter overflows, पातs the
	 * transaction and is then set back to लघुly beक्रमe the
	 * overflow, and overflows and पातs again.
	 */
	अगर (unlikely(event_is_checkpoपूर्णांकed(event))) अणु
		/* No race with NMIs because the counter should not be armed */
		wrmsrl(event->hw.event_base, 0);
		local64_set(&event->hw.prev_count, 0);
	पूर्ण
	वापस x86_perf_event_set_period(event);
पूर्ण

अटल व्योम पूर्णांकel_pmu_reset(व्योम)
अणु
	काष्ठा debug_store *ds = __this_cpu_पढ़ो(cpu_hw_events.ds);
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक num_counters_fixed = hybrid(cpuc->pmu, num_counters_fixed);
	पूर्णांक num_counters = hybrid(cpuc->pmu, num_counters);
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	अगर (!num_counters)
		वापस;

	local_irq_save(flags);

	pr_info("clearing PMU state on CPU#%d\n", smp_processor_id());

	क्रम (idx = 0; idx < num_counters; idx++) अणु
		wrmsrl_safe(x86_pmu_config_addr(idx), 0ull);
		wrmsrl_safe(x86_pmu_event_addr(idx),  0ull);
	पूर्ण
	क्रम (idx = 0; idx < num_counters_fixed; idx++) अणु
		अगर (fixed_counter_disabled(idx, cpuc->pmu))
			जारी;
		wrmsrl_safe(MSR_ARCH_PERFMON_FIXED_CTR0 + idx, 0ull);
	पूर्ण

	अगर (ds)
		ds->bts_index = ds->bts_buffer_base;

	/* Ack all overflows and disable fixed counters */
	अगर (x86_pmu.version >= 2) अणु
		पूर्णांकel_pmu_ack_status(पूर्णांकel_pmu_get_status());
		wrmsrl(MSR_CORE_PERF_GLOBAL_CTRL, 0);
	पूर्ण

	/* Reset LBRs and LBR मुक्तzing */
	अगर (x86_pmu.lbr_nr) अणु
		update_debugctlmsr(get_debugctlmsr() &
			~(DEBUGCTLMSR_FREEZE_LBRS_ON_PMI|DEBUGCTLMSR_LBR));
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक handle_pmi_common(काष्ठा pt_regs *regs, u64 status)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक bit;
	पूर्णांक handled = 0;
	u64 पूर्णांकel_ctrl = hybrid(cpuc->pmu, पूर्णांकel_ctrl);

	inc_irq_stat(apic_perf_irqs);

	/*
	 * Ignore a range of extra bits in status that करो not indicate
	 * overflow by themselves.
	 */
	status &= ~(GLOBAL_STATUS_COND_CHG |
		    GLOBAL_STATUS_ASIF |
		    GLOBAL_STATUS_LBRS_FROZEN);
	अगर (!status)
		वापस 0;
	/*
	 * In हाल multiple PEBS events are sampled at the same समय,
	 * it is possible to have GLOBAL_STATUS bit 62 set indicating
	 * PEBS buffer overflow and also seeing at most 3 PEBS counters
	 * having their bits set in the status रेजिस्टर. This is a sign
	 * that there was at least one PEBS record pending at the समय
	 * of the PMU पूर्णांकerrupt. PEBS counters must only be processed
	 * via the drain_pebs() calls and not via the regular sample
	 * processing loop coming after that the function, otherwise
	 * phony regular samples may be generated in the sampling buffer
	 * not marked with the EXACT tag. Another possibility is to have
	 * one PEBS event and at least one non-PEBS event which overflows
	 * जबतक PEBS has armed. In this हाल, bit 62 of GLOBAL_STATUS will
	 * not be set, yet the overflow status bit क्रम the PEBS counter will
	 * be on Skylake.
	 *
	 * To aव्योम this problem, we प्रणालीatically ignore the PEBS-enabled
	 * counters from the GLOBAL_STATUS mask and we always process PEBS
	 * events via drain_pebs().
	 */
	अगर (x86_pmu.flags & PMU_FL_PEBS_ALL)
		status &= ~cpuc->pebs_enabled;
	अन्यथा
		status &= ~(cpuc->pebs_enabled & PEBS_COUNTER_MASK);

	/*
	 * PEBS overflow sets bit 62 in the global status रेजिस्टर
	 */
	अगर (__test_and_clear_bit(GLOBAL_STATUS_BUFFER_OVF_BIT, (अचिन्हित दीर्घ *)&status)) अणु
		u64 pebs_enabled = cpuc->pebs_enabled;

		handled++;
		x86_pmu.drain_pebs(regs, &data);
		status &= पूर्णांकel_ctrl | GLOBAL_STATUS_TRACE_TOPAPMI;

		/*
		 * PMI throttle may be triggered, which stops the PEBS event.
		 * Although cpuc->pebs_enabled is updated accordingly, the
		 * MSR_IA32_PEBS_ENABLE is not updated. Because the
		 * cpuc->enabled has been क्रमced to 0 in PMI.
		 * Update the MSR अगर pebs_enabled is changed.
		 */
		अगर (pebs_enabled != cpuc->pebs_enabled)
			wrmsrl(MSR_IA32_PEBS_ENABLE, cpuc->pebs_enabled);
	पूर्ण

	/*
	 * Intel PT
	 */
	अगर (__test_and_clear_bit(GLOBAL_STATUS_TRACE_TOPAPMI_BIT, (अचिन्हित दीर्घ *)&status)) अणु
		handled++;
		अगर (unlikely(perf_guest_cbs && perf_guest_cbs->is_in_guest() &&
			perf_guest_cbs->handle_पूर्णांकel_pt_पूर्णांकr))
			perf_guest_cbs->handle_पूर्णांकel_pt_पूर्णांकr();
		अन्यथा
			पूर्णांकel_pt_पूर्णांकerrupt();
	पूर्ण

	/*
	 * Intel Perf metrics
	 */
	अगर (__test_and_clear_bit(GLOBAL_STATUS_PERF_METRICS_OVF_BIT, (अचिन्हित दीर्घ *)&status)) अणु
		handled++;
		अगर (x86_pmu.update_topकरोwn_event)
			x86_pmu.update_topकरोwn_event(शून्य);
	पूर्ण

	/*
	 * Checkpoपूर्णांकed counters can lead to 'spurious' PMIs because the
	 * rollback caused by the PMI will have cleared the overflow status
	 * bit. Thereक्रमe always क्रमce probe these counters.
	 */
	status |= cpuc->पूर्णांकel_cp_status;

	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&status, X86_PMC_IDX_MAX) अणु
		काष्ठा perf_event *event = cpuc->events[bit];

		handled++;

		अगर (!test_bit(bit, cpuc->active_mask))
			जारी;

		अगर (!पूर्णांकel_pmu_save_and_restart(event))
			जारी;

		perf_sample_data_init(&data, 0, event->hw.last_period);

		अगर (has_branch_stack(event))
			data.br_stack = &cpuc->lbr_stack;

		अगर (perf_event_overflow(event, &data, regs))
			x86_pmu_stop(event, 0);
	पूर्ण

	वापस handled;
पूर्ण

/*
 * This handler is triggered by the local APIC, so the APIC IRQ handling
 * rules apply:
 */
अटल पूर्णांक पूर्णांकel_pmu_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा cpu_hw_events *cpuc;
	पूर्णांक loops;
	u64 status;
	पूर्णांक handled;
	पूर्णांक pmu_enabled;

	cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * Save the PMU state.
	 * It needs to be restored when leaving the handler.
	 */
	pmu_enabled = cpuc->enabled;
	/*
	 * No known reason to not always करो late ACK,
	 * but just in हाल करो it opt-in.
	 */
	अगर (!x86_pmu.late_ack)
		apic_ग_लिखो(APIC_LVTPC, APIC_DM_NMI);
	पूर्णांकel_bts_disable_local();
	cpuc->enabled = 0;
	__पूर्णांकel_pmu_disable_all();
	handled = पूर्णांकel_pmu_drain_bts_buffer();
	handled += पूर्णांकel_bts_पूर्णांकerrupt();
	status = पूर्णांकel_pmu_get_status();
	अगर (!status)
		जाओ करोne;

	loops = 0;
again:
	पूर्णांकel_pmu_lbr_पढ़ो();
	पूर्णांकel_pmu_ack_status(status);
	अगर (++loops > 100) अणु
		अटल bool warned;

		अगर (!warned) अणु
			WARN(1, "perfevents: irq loop stuck!\n");
			perf_event_prपूर्णांक_debug();
			warned = true;
		पूर्ण
		पूर्णांकel_pmu_reset();
		जाओ करोne;
	पूर्ण

	handled += handle_pmi_common(regs, status);

	/*
	 * Repeat अगर there is more work to be करोne:
	 */
	status = पूर्णांकel_pmu_get_status();
	अगर (status)
		जाओ again;

करोne:
	/* Only restore PMU state when it's active. See x86_pmu_disable(). */
	cpuc->enabled = pmu_enabled;
	अगर (pmu_enabled)
		__पूर्णांकel_pmu_enable_all(0, true);
	पूर्णांकel_bts_enable_local();

	/*
	 * Only unmask the NMI after the overflow counters
	 * have been reset. This aव्योमs spurious NMIs on
	 * Haswell CPUs.
	 */
	अगर (x86_pmu.late_ack)
		apic_ग_लिखो(APIC_LVTPC, APIC_DM_NMI);
	वापस handled;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
पूर्णांकel_bts_स्थिरraपूर्णांकs(काष्ठा perf_event *event)
अणु
	अगर (unlikely(पूर्णांकel_pmu_has_bts(event)))
		वापस &bts_स्थिरraपूर्णांक;

	वापस शून्य;
पूर्ण

/*
 * Note: matches a fake event, like Fixed2.
 */
अटल काष्ठा event_स्थिरraपूर्णांक *
पूर्णांकel_vlbr_स्थिरraपूर्णांकs(काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c = &vlbr_स्थिरraपूर्णांक;

	अगर (unlikely(स्थिरraपूर्णांक_match(c, event->hw.config)))
		वापस c;

	वापस शून्य;
पूर्ण

अटल पूर्णांक पूर्णांकel_alt_er(काष्ठा cpu_hw_events *cpuc,
			पूर्णांक idx, u64 config)
अणु
	काष्ठा extra_reg *extra_regs = hybrid(cpuc->pmu, extra_regs);
	पूर्णांक alt_idx = idx;

	अगर (!(x86_pmu.flags & PMU_FL_HAS_RSP_1))
		वापस idx;

	अगर (idx == EXTRA_REG_RSP_0)
		alt_idx = EXTRA_REG_RSP_1;

	अगर (idx == EXTRA_REG_RSP_1)
		alt_idx = EXTRA_REG_RSP_0;

	अगर (config & ~extra_regs[alt_idx].valid_mask)
		वापस idx;

	वापस alt_idx;
पूर्ण

अटल व्योम पूर्णांकel_fixup_er(काष्ठा perf_event *event, पूर्णांक idx)
अणु
	काष्ठा extra_reg *extra_regs = hybrid(event->pmu, extra_regs);
	event->hw.extra_reg.idx = idx;

	अगर (idx == EXTRA_REG_RSP_0) अणु
		event->hw.config &= ~INTEL_ARCH_EVENT_MASK;
		event->hw.config |= extra_regs[EXTRA_REG_RSP_0].event;
		event->hw.extra_reg.reg = MSR_OFFCORE_RSP_0;
	पूर्ण अन्यथा अगर (idx == EXTRA_REG_RSP_1) अणु
		event->hw.config &= ~INTEL_ARCH_EVENT_MASK;
		event->hw.config |= extra_regs[EXTRA_REG_RSP_1].event;
		event->hw.extra_reg.reg = MSR_OFFCORE_RSP_1;
	पूर्ण
पूर्ण

/*
 * manage allocation of shared extra msr क्रम certain events
 *
 * sharing can be:
 * per-cpu: to be shared between the various events on a single PMU
 * per-core: per-cpu + shared by HT thपढ़ोs
 */
अटल काष्ठा event_स्थिरraपूर्णांक *
__पूर्णांकel_shared_reg_get_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc,
				   काष्ठा perf_event *event,
				   काष्ठा hw_perf_event_extra *reg)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c = &emptyस्थिरraपूर्णांक;
	काष्ठा er_account *era;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx = reg->idx;

	/*
	 * reg->alloc can be set due to existing state, so क्रम fake cpuc we
	 * need to ignore this, otherwise we might fail to allocate proper fake
	 * state क्रम this extra reg स्थिरraपूर्णांक. Also see the comment below.
	 */
	अगर (reg->alloc && !cpuc->is_fake)
		वापस शून्य; /* call x86_get_event_स्थिरraपूर्णांक() */

again:
	era = &cpuc->shared_regs->regs[idx];
	/*
	 * we use spin_lock_irqsave() to aव्योम lockdep issues when
	 * passing a fake cpuc
	 */
	raw_spin_lock_irqsave(&era->lock, flags);

	अगर (!atomic_पढ़ो(&era->ref) || era->config == reg->config) अणु

		/*
		 * If its a fake cpuc -- as per validate_अणुgroup,eventपूर्ण() we
		 * shouldn't touch event state and we can aव्योम करोing so
		 * since both will only call get_event_स्थिरraपूर्णांकs() once
		 * on each event, this aव्योमs the need क्रम reg->alloc.
		 *
		 * Not करोing the ER fixup will only result in era->reg being
		 * wrong, but since we won't actually try and program hardware
		 * this isn't a problem either.
		 */
		अगर (!cpuc->is_fake) अणु
			अगर (idx != reg->idx)
				पूर्णांकel_fixup_er(event, idx);

			/*
			 * x86_schedule_events() can call get_event_स्थिरraपूर्णांकs()
			 * multiple बार on events in the हाल of incremental
			 * scheduling(). reg->alloc ensures we only करो the ER
			 * allocation once.
			 */
			reg->alloc = 1;
		पूर्ण

		/* lock in msr value */
		era->config = reg->config;
		era->reg = reg->reg;

		/* one more user */
		atomic_inc(&era->ref);

		/*
		 * need to call x86_get_event_स्थिरraपूर्णांक()
		 * to check अगर associated event has स्थिरraपूर्णांकs
		 */
		c = शून्य;
	पूर्ण अन्यथा अणु
		idx = पूर्णांकel_alt_er(cpuc, idx, reg->config);
		अगर (idx != reg->idx) अणु
			raw_spin_unlock_irqrestore(&era->lock, flags);
			जाओ again;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&era->lock, flags);

	वापस c;
पूर्ण

अटल व्योम
__पूर्णांकel_shared_reg_put_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc,
				   काष्ठा hw_perf_event_extra *reg)
अणु
	काष्ठा er_account *era;

	/*
	 * Only put स्थिरraपूर्णांक अगर extra reg was actually allocated. Also takes
	 * care of event which करो not use an extra shared reg.
	 *
	 * Also, अगर this is a fake cpuc we shouldn't touch any event state
	 * (reg->alloc) and we करोn't care about leaving inconsistent cpuc state
	 * either since it'll be thrown out.
	 */
	अगर (!reg->alloc || cpuc->is_fake)
		वापस;

	era = &cpuc->shared_regs->regs[reg->idx];

	/* one fewer user */
	atomic_dec(&era->ref);

	/* allocate again next समय */
	reg->alloc = 0;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
पूर्णांकel_shared_regs_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc,
			      काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c = शून्य, *d;
	काष्ठा hw_perf_event_extra *xreg, *breg;

	xreg = &event->hw.extra_reg;
	अगर (xreg->idx != EXTRA_REG_NONE) अणु
		c = __पूर्णांकel_shared_reg_get_स्थिरraपूर्णांकs(cpuc, event, xreg);
		अगर (c == &emptyस्थिरraपूर्णांक)
			वापस c;
	पूर्ण
	breg = &event->hw.branch_reg;
	अगर (breg->idx != EXTRA_REG_NONE) अणु
		d = __पूर्णांकel_shared_reg_get_स्थिरraपूर्णांकs(cpuc, event, breg);
		अगर (d == &emptyस्थिरraपूर्णांक) अणु
			__पूर्णांकel_shared_reg_put_स्थिरraपूर्णांकs(cpuc, xreg);
			c = d;
		पूर्ण
	पूर्ण
	वापस c;
पूर्ण

काष्ठा event_स्थिरraपूर्णांक *
x86_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *event_स्थिरraपूर्णांकs = hybrid(cpuc->pmu, event_स्थिरraपूर्णांकs);
	काष्ठा event_स्थिरraपूर्णांक *c;

	अगर (event_स्थिरraपूर्णांकs) अणु
		क्रम_each_event_स्थिरraपूर्णांक(c, event_स्थिरraपूर्णांकs) अणु
			अगर (स्थिरraपूर्णांक_match(c, event->hw.config)) अणु
				event->hw.flags |= c->flags;
				वापस c;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस &hybrid_var(cpuc->pmu, unस्थिरrained);
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
__पूर्णांकel_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			    काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;

	c = पूर्णांकel_vlbr_स्थिरraपूर्णांकs(event);
	अगर (c)
		वापस c;

	c = पूर्णांकel_bts_स्थिरraपूर्णांकs(event);
	अगर (c)
		वापस c;

	c = पूर्णांकel_shared_regs_स्थिरraपूर्णांकs(cpuc, event);
	अगर (c)
		वापस c;

	c = पूर्णांकel_pebs_स्थिरraपूर्णांकs(event);
	अगर (c)
		वापस c;

	वापस x86_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);
पूर्ण

अटल व्योम
पूर्णांकel_start_scheduling(काष्ठा cpu_hw_events *cpuc)
अणु
	काष्ठा पूर्णांकel_excl_cntrs *excl_cntrs = cpuc->excl_cntrs;
	काष्ठा पूर्णांकel_excl_states *xl;
	पूर्णांक tid = cpuc->excl_thपढ़ो_id;

	/*
	 * nothing needed अगर in group validation mode
	 */
	अगर (cpuc->is_fake || !is_ht_workaround_enabled())
		वापस;

	/*
	 * no exclusion needed
	 */
	अगर (WARN_ON_ONCE(!excl_cntrs))
		वापस;

	xl = &excl_cntrs->states[tid];

	xl->sched_started = true;
	/*
	 * lock shared state until we are करोne scheduling
	 * in stop_event_scheduling()
	 * makes scheduling appear as a transaction
	 */
	raw_spin_lock(&excl_cntrs->lock);
पूर्ण

अटल व्योम पूर्णांकel_commit_scheduling(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx, पूर्णांक cntr)
अणु
	काष्ठा पूर्णांकel_excl_cntrs *excl_cntrs = cpuc->excl_cntrs;
	काष्ठा event_स्थिरraपूर्णांक *c = cpuc->event_स्थिरraपूर्णांक[idx];
	काष्ठा पूर्णांकel_excl_states *xl;
	पूर्णांक tid = cpuc->excl_thपढ़ो_id;

	अगर (cpuc->is_fake || !is_ht_workaround_enabled())
		वापस;

	अगर (WARN_ON_ONCE(!excl_cntrs))
		वापस;

	अगर (!(c->flags & PERF_X86_EVENT_DYNAMIC))
		वापस;

	xl = &excl_cntrs->states[tid];

	lockdep_निश्चित_held(&excl_cntrs->lock);

	अगर (c->flags & PERF_X86_EVENT_EXCL)
		xl->state[cntr] = INTEL_EXCL_EXCLUSIVE;
	अन्यथा
		xl->state[cntr] = INTEL_EXCL_SHARED;
पूर्ण

अटल व्योम
पूर्णांकel_stop_scheduling(काष्ठा cpu_hw_events *cpuc)
अणु
	काष्ठा पूर्णांकel_excl_cntrs *excl_cntrs = cpuc->excl_cntrs;
	काष्ठा पूर्णांकel_excl_states *xl;
	पूर्णांक tid = cpuc->excl_thपढ़ो_id;

	/*
	 * nothing needed अगर in group validation mode
	 */
	अगर (cpuc->is_fake || !is_ht_workaround_enabled())
		वापस;
	/*
	 * no exclusion needed
	 */
	अगर (WARN_ON_ONCE(!excl_cntrs))
		वापस;

	xl = &excl_cntrs->states[tid];

	xl->sched_started = false;
	/*
	 * release shared state lock (acquired in पूर्णांकel_start_scheduling())
	 */
	raw_spin_unlock(&excl_cntrs->lock);
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
dyn_स्थिरraपूर्णांक(काष्ठा cpu_hw_events *cpuc, काष्ठा event_स्थिरraपूर्णांक *c, पूर्णांक idx)
अणु
	WARN_ON_ONCE(!cpuc->स्थिरraपूर्णांक_list);

	अगर (!(c->flags & PERF_X86_EVENT_DYNAMIC)) अणु
		काष्ठा event_स्थिरraपूर्णांक *cx;

		/*
		 * grab pre-allocated स्थिरraपूर्णांक entry
		 */
		cx = &cpuc->स्थिरraपूर्णांक_list[idx];

		/*
		 * initialize dynamic स्थिरraपूर्णांक
		 * with अटल स्थिरraपूर्णांक
		 */
		*cx = *c;

		/*
		 * mark स्थिरraपूर्णांक as dynamic
		 */
		cx->flags |= PERF_X86_EVENT_DYNAMIC;
		c = cx;
	पूर्ण

	वापस c;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
पूर्णांकel_get_excl_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, काष्ठा perf_event *event,
			   पूर्णांक idx, काष्ठा event_स्थिरraपूर्णांक *c)
अणु
	काष्ठा पूर्णांकel_excl_cntrs *excl_cntrs = cpuc->excl_cntrs;
	काष्ठा पूर्णांकel_excl_states *xlo;
	पूर्णांक tid = cpuc->excl_thपढ़ो_id;
	पूर्णांक is_excl, i, w;

	/*
	 * validating a group करोes not require
	 * enक्रमcing cross-thपढ़ो  exclusion
	 */
	अगर (cpuc->is_fake || !is_ht_workaround_enabled())
		वापस c;

	/*
	 * no exclusion needed
	 */
	अगर (WARN_ON_ONCE(!excl_cntrs))
		वापस c;

	/*
	 * because we modअगरy the स्थिरraपूर्णांक, we need
	 * to make a copy. Static स्थिरraपूर्णांकs come
	 * from अटल स्थिर tables.
	 *
	 * only needed when स्थिरraपूर्णांक has not yet
	 * been cloned (marked dynamic)
	 */
	c = dyn_स्थिरraपूर्णांक(cpuc, c, idx);

	/*
	 * From here on, the स्थिरraपूर्णांक is dynamic.
	 * Either it was just allocated above, or it
	 * was allocated during a earlier invocation
	 * of this function
	 */

	/*
	 * state of sibling HT
	 */
	xlo = &excl_cntrs->states[tid ^ 1];

	/*
	 * event requires exclusive counter access
	 * across HT thपढ़ोs
	 */
	is_excl = c->flags & PERF_X86_EVENT_EXCL;
	अगर (is_excl && !(event->hw.flags & PERF_X86_EVENT_EXCL_ACCT)) अणु
		event->hw.flags |= PERF_X86_EVENT_EXCL_ACCT;
		अगर (!cpuc->n_excl++)
			WRITE_ONCE(excl_cntrs->has_exclusive[tid], 1);
	पूर्ण

	/*
	 * Modअगरy अटल स्थिरraपूर्णांक with current dynamic
	 * state of thपढ़ो
	 *
	 * EXCLUSIVE: sibling counter measuring exclusive event
	 * SHARED   : sibling counter measuring non-exclusive event
	 * UNUSED   : sibling counter unused
	 */
	w = c->weight;
	क्रम_each_set_bit(i, c->idxmsk, X86_PMC_IDX_MAX) अणु
		/*
		 * exclusive event in sibling counter
		 * our corresponding counter cannot be used
		 * regardless of our event
		 */
		अगर (xlo->state[i] == INTEL_EXCL_EXCLUSIVE) अणु
			__clear_bit(i, c->idxmsk);
			w--;
			जारी;
		पूर्ण
		/*
		 * अगर measuring an exclusive event, sibling
		 * measuring non-exclusive, then counter cannot
		 * be used
		 */
		अगर (is_excl && xlo->state[i] == INTEL_EXCL_SHARED) अणु
			__clear_bit(i, c->idxmsk);
			w--;
			जारी;
		पूर्ण
	पूर्ण

	/*
	 * अगर we वापस an empty mask, then चयन
	 * back to अटल empty स्थिरraपूर्णांक to aव्योम
	 * the cost of मुक्तing later on
	 */
	अगर (!w)
		c = &emptyस्थिरraपूर्णांक;

	c->weight = w;

	वापस c;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
पूर्णांकel_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			    काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c1, *c2;

	c1 = cpuc->event_स्थिरraपूर्णांक[idx];

	/*
	 * first समय only
	 * - अटल स्थिरraपूर्णांक: no change across incremental scheduling calls
	 * - dynamic स्थिरraपूर्णांक: handled by पूर्णांकel_get_excl_स्थिरraपूर्णांकs()
	 */
	c2 = __पूर्णांकel_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);
	अगर (c1) अणु
	        WARN_ON_ONCE(!(c1->flags & PERF_X86_EVENT_DYNAMIC));
		biपंचांगap_copy(c1->idxmsk, c2->idxmsk, X86_PMC_IDX_MAX);
		c1->weight = c2->weight;
		c2 = c1;
	पूर्ण

	अगर (cpuc->excl_cntrs)
		वापस पूर्णांकel_get_excl_स्थिरraपूर्णांकs(cpuc, event, idx, c2);

	वापस c2;
पूर्ण

अटल व्योम पूर्णांकel_put_excl_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc,
		काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा पूर्णांकel_excl_cntrs *excl_cntrs = cpuc->excl_cntrs;
	पूर्णांक tid = cpuc->excl_thपढ़ो_id;
	काष्ठा पूर्णांकel_excl_states *xl;

	/*
	 * nothing needed अगर in group validation mode
	 */
	अगर (cpuc->is_fake)
		वापस;

	अगर (WARN_ON_ONCE(!excl_cntrs))
		वापस;

	अगर (hwc->flags & PERF_X86_EVENT_EXCL_ACCT) अणु
		hwc->flags &= ~PERF_X86_EVENT_EXCL_ACCT;
		अगर (!--cpuc->n_excl)
			WRITE_ONCE(excl_cntrs->has_exclusive[tid], 0);
	पूर्ण

	/*
	 * If event was actually asचिन्हित, then mark the counter state as
	 * unused now.
	 */
	अगर (hwc->idx >= 0) अणु
		xl = &excl_cntrs->states[tid];

		/*
		 * put_स्थिरraपूर्णांक may be called from x86_schedule_events()
		 * which alपढ़ोy has the lock held so here make locking
		 * conditional.
		 */
		अगर (!xl->sched_started)
			raw_spin_lock(&excl_cntrs->lock);

		xl->state[hwc->idx] = INTEL_EXCL_UNUSED;

		अगर (!xl->sched_started)
			raw_spin_unlock(&excl_cntrs->lock);
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_put_shared_regs_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc,
					काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg;

	reg = &event->hw.extra_reg;
	अगर (reg->idx != EXTRA_REG_NONE)
		__पूर्णांकel_shared_reg_put_स्थिरraपूर्णांकs(cpuc, reg);

	reg = &event->hw.branch_reg;
	अगर (reg->idx != EXTRA_REG_NONE)
		__पूर्णांकel_shared_reg_put_स्थिरraपूर्णांकs(cpuc, reg);
पूर्ण

अटल व्योम पूर्णांकel_put_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc,
					काष्ठा perf_event *event)
अणु
	पूर्णांकel_put_shared_regs_event_स्थिरraपूर्णांकs(cpuc, event);

	/*
	 * is PMU has exclusive counter restrictions, then
	 * all events are subject to and must call the
	 * put_excl_स्थिरraपूर्णांकs() routine
	 */
	अगर (cpuc->excl_cntrs)
		पूर्णांकel_put_excl_स्थिरraपूर्णांकs(cpuc, event);
पूर्ण

अटल व्योम पूर्णांकel_pebs_aliases_core2(काष्ठा perf_event *event)
अणु
	अगर ((event->hw.config & X86_RAW_EVENT_MASK) == 0x003c) अणु
		/*
		 * Use an alternative encoding क्रम CPU_CLK_UNHALTED.THREAD_P
		 * (0x003c) so that we can use it with PEBS.
		 *
		 * The regular CPU_CLK_UNHALTED.THREAD_P event (0x003c) isn't
		 * PEBS capable. However we can use INST_RETIRED.ANY_P
		 * (0x00c0), which is a PEBS capable event, to get the same
		 * count.
		 *
		 * INST_RETIRED.ANY_P counts the number of cycles that retires
		 * CNTMASK inकाष्ठाions. By setting CNTMASK to a value (16)
		 * larger than the maximum number of inकाष्ठाions that can be
		 * retired per cycle (4) and then inverting the condition, we
		 * count all cycles that retire 16 or less inकाष्ठाions, which
		 * is every cycle.
		 *
		 * Thereby we gain a PEBS capable cycle counter.
		 */
		u64 alt_config = X86_CONFIG(.event=0xc0, .inv=1, .cmask=16);

		alt_config |= (event->hw.config & ~X86_RAW_EVENT_MASK);
		event->hw.config = alt_config;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pebs_aliases_snb(काष्ठा perf_event *event)
अणु
	अगर ((event->hw.config & X86_RAW_EVENT_MASK) == 0x003c) अणु
		/*
		 * Use an alternative encoding क्रम CPU_CLK_UNHALTED.THREAD_P
		 * (0x003c) so that we can use it with PEBS.
		 *
		 * The regular CPU_CLK_UNHALTED.THREAD_P event (0x003c) isn't
		 * PEBS capable. However we can use UOPS_RETIRED.ALL
		 * (0x01c2), which is a PEBS capable event, to get the same
		 * count.
		 *
		 * UOPS_RETIRED.ALL counts the number of cycles that retires
		 * CNTMASK micro-ops. By setting CNTMASK to a value (16)
		 * larger than the maximum number of micro-ops that can be
		 * retired per cycle (4) and then inverting the condition, we
		 * count all cycles that retire 16 or less micro-ops, which
		 * is every cycle.
		 *
		 * Thereby we gain a PEBS capable cycle counter.
		 */
		u64 alt_config = X86_CONFIG(.event=0xc2, .umask=0x01, .inv=1, .cmask=16);

		alt_config |= (event->hw.config & ~X86_RAW_EVENT_MASK);
		event->hw.config = alt_config;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pebs_aliases_precdist(काष्ठा perf_event *event)
अणु
	अगर ((event->hw.config & X86_RAW_EVENT_MASK) == 0x003c) अणु
		/*
		 * Use an alternative encoding क्रम CPU_CLK_UNHALTED.THREAD_P
		 * (0x003c) so that we can use it with PEBS.
		 *
		 * The regular CPU_CLK_UNHALTED.THREAD_P event (0x003c) isn't
		 * PEBS capable. However we can use INST_RETIRED.PREC_DIST
		 * (0x01c0), which is a PEBS capable event, to get the same
		 * count.
		 *
		 * The PREC_DIST event has special support to minimize sample
		 * shaकरोwing effects. One drawback is that it can be
		 * only programmed on counter 1, but that seems like an
		 * acceptable trade off.
		 */
		u64 alt_config = X86_CONFIG(.event=0xc0, .umask=0x01, .inv=1, .cmask=16);

		alt_config |= (event->hw.config & ~X86_RAW_EVENT_MASK);
		event->hw.config = alt_config;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pebs_aliases_ivb(काष्ठा perf_event *event)
अणु
	अगर (event->attr.precise_ip < 3)
		वापस पूर्णांकel_pebs_aliases_snb(event);
	वापस पूर्णांकel_pebs_aliases_precdist(event);
पूर्ण

अटल व्योम पूर्णांकel_pebs_aliases_skl(काष्ठा perf_event *event)
अणु
	अगर (event->attr.precise_ip < 3)
		वापस पूर्णांकel_pebs_aliases_core2(event);
	वापस पूर्णांकel_pebs_aliases_precdist(event);
पूर्ण

अटल अचिन्हित दीर्घ पूर्णांकel_pmu_large_pebs_flags(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags = x86_pmu.large_pebs_flags;

	अगर (event->attr.use_घड़ीid)
		flags &= ~PERF_SAMPLE_TIME;
	अगर (!event->attr.exclude_kernel)
		flags &= ~PERF_SAMPLE_REGS_USER;
	अगर (event->attr.sample_regs_user & ~PEBS_GP_REGS)
		flags &= ~(PERF_SAMPLE_REGS_USER | PERF_SAMPLE_REGS_INTR);
	वापस flags;
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_bts_config(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;

	अगर (unlikely(पूर्णांकel_pmu_has_bts(event))) अणु
		/* BTS is not supported by this architecture. */
		अगर (!x86_pmu.bts_active)
			वापस -EOPNOTSUPP;

		/* BTS is currently only allowed क्रम user-mode. */
		अगर (!attr->exclude_kernel)
			वापस -EOPNOTSUPP;

		/* BTS is not allowed क्रम precise events. */
		अगर (attr->precise_ip)
			वापस -EOPNOTSUPP;

		/* disallow bts अगर conflicting events are present */
		अगर (x86_add_exclusive(x86_lbr_exclusive_lbr))
			वापस -EBUSY;

		event->destroy = hw_perf_lbr_event_destroy;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक core_pmu_hw_config(काष्ठा perf_event *event)
अणु
	पूर्णांक ret = x86_pmu_hw_config(event);

	अगर (ret)
		वापस ret;

	वापस पूर्णांकel_pmu_bts_config(event);
पूर्ण

#घोषणा INTEL_TD_METRIC_AVAILABLE_MAX	(INTEL_TD_METRIC_RETIRING + \
					 ((x86_pmu.num_topकरोwn_events - 1) << 8))

अटल bool is_available_metric_event(काष्ठा perf_event *event)
अणु
	वापस is_metric_event(event) &&
		event->attr.config <= INTEL_TD_METRIC_AVAILABLE_MAX;
पूर्ण

अटल अंतरभूत bool is_mem_loads_event(काष्ठा perf_event *event)
अणु
	वापस (event->attr.config & INTEL_ARCH_EVENT_MASK) == X86_CONFIG(.event=0xcd, .umask=0x01);
पूर्ण

अटल अंतरभूत bool is_mem_loads_aux_event(काष्ठा perf_event *event)
अणु
	वापस (event->attr.config & INTEL_ARCH_EVENT_MASK) == X86_CONFIG(.event=0x03, .umask=0x82);
पूर्ण

अटल अंतरभूत bool require_mem_loads_aux_event(काष्ठा perf_event *event)
अणु
	अगर (!(x86_pmu.flags & PMU_FL_MEM_LOADS_AUX))
		वापस false;

	अगर (is_hybrid())
		वापस hybrid_pmu(event->pmu)->cpu_type == hybrid_big;

	वापस true;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pmu_has_cap(काष्ठा perf_event *event, पूर्णांक idx)
अणु
	जोड़ perf_capabilities *पूर्णांकel_cap = &hybrid(event->pmu, पूर्णांकel_cap);

	वापस test_bit(idx, (अचिन्हित दीर्घ *)&पूर्णांकel_cap->capabilities);
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_hw_config(काष्ठा perf_event *event)
अणु
	पूर्णांक ret = x86_pmu_hw_config(event);

	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_pmu_bts_config(event);
	अगर (ret)
		वापस ret;

	अगर (event->attr.precise_ip) अणु
		अगर ((event->attr.config & INTEL_ARCH_EVENT_MASK) == INTEL_FIXED_VLBR_EVENT)
			वापस -EINVAL;

		अगर (!(event->attr.freq || (event->attr.wakeup_events && !event->attr.watermark))) अणु
			event->hw.flags |= PERF_X86_EVENT_AUTO_RELOAD;
			अगर (!(event->attr.sample_type &
			      ~पूर्णांकel_pmu_large_pebs_flags(event))) अणु
				event->hw.flags |= PERF_X86_EVENT_LARGE_PEBS;
				event->attach_state |= PERF_ATTACH_SCHED_CB;
			पूर्ण
		पूर्ण
		अगर (x86_pmu.pebs_aliases)
			x86_pmu.pebs_aliases(event);

		अगर (event->attr.sample_type & PERF_SAMPLE_CALLCHAIN)
			event->attr.sample_type |= __PERF_SAMPLE_CALLCHAIN_EARLY;
	पूर्ण

	अगर (needs_branch_stack(event)) अणु
		ret = पूर्णांकel_pmu_setup_lbr_filter(event);
		अगर (ret)
			वापस ret;
		event->attach_state |= PERF_ATTACH_SCHED_CB;

		/*
		 * BTS is set up earlier in this path, so करोn't account twice
		 */
		अगर (!unlikely(पूर्णांकel_pmu_has_bts(event))) अणु
			/* disallow lbr अगर conflicting events are present */
			अगर (x86_add_exclusive(x86_lbr_exclusive_lbr))
				वापस -EBUSY;

			event->destroy = hw_perf_lbr_event_destroy;
		पूर्ण
	पूर्ण

	अगर (event->attr.aux_output) अणु
		अगर (!event->attr.precise_ip)
			वापस -EINVAL;

		event->hw.flags |= PERF_X86_EVENT_PEBS_VIA_PT;
	पूर्ण

	अगर ((event->attr.type == PERF_TYPE_HARDWARE) ||
	    (event->attr.type == PERF_TYPE_HW_CACHE))
		वापस 0;

	/*
	 * Config Topकरोwn slots and metric events
	 *
	 * The slots event on Fixed Counter 3 can support sampling,
	 * which will be handled normally in x86_perf_event_update().
	 *
	 * Metric events करोn't support sampling and require being paired
	 * with a slots event as group leader. When the slots event
	 * is used in a metrics group, it too cannot support sampling.
	 */
	अगर (पूर्णांकel_pmu_has_cap(event, PERF_CAP_METRICS_IDX) && is_topकरोwn_event(event)) अणु
		अगर (event->attr.config1 || event->attr.config2)
			वापस -EINVAL;

		/*
		 * The TopDown metrics events and slots event करोn't
		 * support any filters.
		 */
		अगर (event->attr.config & X86_ALL_EVENT_FLAGS)
			वापस -EINVAL;

		अगर (is_available_metric_event(event)) अणु
			काष्ठा perf_event *leader = event->group_leader;

			/* The metric events करोn't support sampling. */
			अगर (is_sampling_event(event))
				वापस -EINVAL;

			/* The metric events require a slots group leader. */
			अगर (!is_slots_event(leader))
				वापस -EINVAL;

			/*
			 * The leader/SLOTS must not be a sampling event क्रम
			 * metric use; hardware requires it starts at 0 when used
			 * in conjunction with MSR_PERF_METRICS.
			 */
			अगर (is_sampling_event(leader))
				वापस -EINVAL;

			event->event_caps |= PERF_EV_CAP_SIBLING;
			/*
			 * Only once we have a METRICs sibling करो we
			 * need TopDown magic.
			 */
			leader->hw.flags |= PERF_X86_EVENT_TOPDOWN;
			event->hw.flags  |= PERF_X86_EVENT_TOPDOWN;
		पूर्ण
	पूर्ण

	/*
	 * The load latency event X86_CONFIG(.event=0xcd, .umask=0x01) on SPR
	 * करोesn't function quite right. As a work-around it needs to always be
	 * co-scheduled with a auxiliary event X86_CONFIG(.event=0x03, .umask=0x82).
	 * The actual count of this second event is irrelevant it just needs
	 * to be active to make the first event function correctly.
	 *
	 * In a group, the auxiliary event must be in front of the load latency
	 * event. The rule is to simplअगरy the implementation of the check.
	 * That's because perf cannot have a complete group at the moment.
	 */
	अगर (require_mem_loads_aux_event(event) &&
	    (event->attr.sample_type & PERF_SAMPLE_DATA_SRC) &&
	    is_mem_loads_event(event)) अणु
		काष्ठा perf_event *leader = event->group_leader;
		काष्ठा perf_event *sibling = शून्य;

		अगर (!is_mem_loads_aux_event(leader)) अणु
			क्रम_each_sibling_event(sibling, leader) अणु
				अगर (is_mem_loads_aux_event(sibling))
					अवरोध;
			पूर्ण
			अगर (list_entry_is_head(sibling, &leader->sibling_list, sibling_list))
				वापस -ENODATA;
		पूर्ण
	पूर्ण

	अगर (!(event->attr.config & ARCH_PERFMON_EVENTSEL_ANY))
		वापस 0;

	अगर (x86_pmu.version < 3)
		वापस -EINVAL;

	ret = perf_allow_cpu(&event->attr);
	अगर (ret)
		वापस ret;

	event->hw.config |= ARCH_PERFMON_EVENTSEL_ANY;

	वापस 0;
पूर्ण

अटल काष्ठा perf_guest_चयन_msr *पूर्णांकel_guest_get_msrs(पूर्णांक *nr)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा perf_guest_चयन_msr *arr = cpuc->guest_चयन_msrs;
	u64 पूर्णांकel_ctrl = hybrid(cpuc->pmu, पूर्णांकel_ctrl);

	arr[0].msr = MSR_CORE_PERF_GLOBAL_CTRL;
	arr[0].host = पूर्णांकel_ctrl & ~cpuc->पूर्णांकel_ctrl_guest_mask;
	arr[0].guest = पूर्णांकel_ctrl & ~cpuc->पूर्णांकel_ctrl_host_mask;
	अगर (x86_pmu.flags & PMU_FL_PEBS_ALL)
		arr[0].guest &= ~cpuc->pebs_enabled;
	अन्यथा
		arr[0].guest &= ~(cpuc->pebs_enabled & PEBS_COUNTER_MASK);
	*nr = 1;

	अगर (x86_pmu.pebs && x86_pmu.pebs_no_isolation) अणु
		/*
		 * If PMU counter has PEBS enabled it is not enough to
		 * disable counter on a guest entry since PEBS memory
		 * ग_लिखो can overshoot guest entry and corrupt guest
		 * memory. Disabling PEBS solves the problem.
		 *
		 * Don't करो this अगर the CPU alपढ़ोy enक्रमces it.
		 */
		arr[1].msr = MSR_IA32_PEBS_ENABLE;
		arr[1].host = cpuc->pebs_enabled;
		arr[1].guest = 0;
		*nr = 2;
	पूर्ण

	वापस arr;
पूर्ण

अटल काष्ठा perf_guest_चयन_msr *core_guest_get_msrs(पूर्णांक *nr)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा perf_guest_चयन_msr *arr = cpuc->guest_चयन_msrs;
	पूर्णांक idx;

	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++)  अणु
		काष्ठा perf_event *event = cpuc->events[idx];

		arr[idx].msr = x86_pmu_config_addr(idx);
		arr[idx].host = arr[idx].guest = 0;

		अगर (!test_bit(idx, cpuc->active_mask))
			जारी;

		arr[idx].host = arr[idx].guest =
			event->hw.config | ARCH_PERFMON_EVENTSEL_ENABLE;

		अगर (event->attr.exclude_host)
			arr[idx].host &= ~ARCH_PERFMON_EVENTSEL_ENABLE;
		अन्यथा अगर (event->attr.exclude_guest)
			arr[idx].guest &= ~ARCH_PERFMON_EVENTSEL_ENABLE;
	पूर्ण

	*nr = x86_pmu.num_counters;
	वापस arr;
पूर्ण

अटल व्योम core_pmu_enable_event(काष्ठा perf_event *event)
अणु
	अगर (!event->attr.exclude_host)
		x86_pmu_enable_event(event);
पूर्ण

अटल व्योम core_pmu_enable_all(पूर्णांक added)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक idx;

	क्रम (idx = 0; idx < x86_pmu.num_counters; idx++) अणु
		काष्ठा hw_perf_event *hwc = &cpuc->events[idx]->hw;

		अगर (!test_bit(idx, cpuc->active_mask) ||
				cpuc->events[idx]->attr.exclude_host)
			जारी;

		__x86_pmu_enable_event(hwc, ARCH_PERFMON_EVENTSEL_ENABLE);
	पूर्ण
पूर्ण

अटल पूर्णांक hsw_hw_config(काष्ठा perf_event *event)
अणु
	पूर्णांक ret = पूर्णांकel_pmu_hw_config(event);

	अगर (ret)
		वापस ret;
	अगर (!boot_cpu_has(X86_FEATURE_RTM) && !boot_cpu_has(X86_FEATURE_HLE))
		वापस 0;
	event->hw.config |= event->attr.config & (HSW_IN_TX|HSW_IN_TX_CHECKPOINTED);

	/*
	 * IN_TX/IN_TX-CP filters are not supported by the Haswell PMU with
	 * PEBS or in ANY thपढ़ो mode. Since the results are non-sensical क्रमbid
	 * this combination.
	 */
	अगर ((event->hw.config & (HSW_IN_TX|HSW_IN_TX_CHECKPOINTED)) &&
	     ((event->hw.config & ARCH_PERFMON_EVENTSEL_ANY) ||
	      event->attr.precise_ip > 0))
		वापस -EOPNOTSUPP;

	अगर (event_is_checkpoपूर्णांकed(event)) अणु
		/*
		 * Sampling of checkpoपूर्णांकed events can cause situations where
		 * the CPU स्थिरantly पातs because of a overflow, which is
		 * then checkpoपूर्णांकed back and ignored. Forbid checkpoपूर्णांकing
		 * क्रम sampling.
		 *
		 * But still allow a दीर्घ sampling period, so that perf stat
		 * from KVM works.
		 */
		अगर (event->attr.sample_period > 0 &&
		    event->attr.sample_period < 0x7fffffff)
			वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक counter0_स्थिरraपूर्णांक =
			INTEL_ALL_EVENT_CONSTRAINT(0, 0x1);

अटल काष्ठा event_स्थिरraपूर्णांक counter2_स्थिरraपूर्णांक =
			EVENT_CONSTRAINT(0, 0x4, 0);

अटल काष्ठा event_स्थिरraपूर्णांक fixed0_स्थिरraपूर्णांक =
			FIXED_EVENT_CONSTRAINT(0x00c0, 0);

अटल काष्ठा event_स्थिरraपूर्णांक fixed0_counter0_स्थिरraपूर्णांक =
			INTEL_ALL_EVENT_CONSTRAINT(0, 0x100000001ULL);

अटल काष्ठा event_स्थिरraपूर्णांक *
hsw_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;

	c = पूर्णांकel_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);

	/* Handle special quirk on in_tx_checkpoपूर्णांकed only in counter 2 */
	अगर (event->hw.config & HSW_IN_TX_CHECKPOINTED) अणु
		अगर (c->idxmsk64 & (1U << 2))
			वापस &counter2_स्थिरraपूर्णांक;
		वापस &emptyस्थिरraपूर्णांक;
	पूर्ण

	वापस c;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
icl_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	/*
	 * Fixed counter 0 has less skid.
	 * Force inकाष्ठाion:ppp in Fixed counter 0
	 */
	अगर ((event->attr.precise_ip == 3) &&
	    स्थिरraपूर्णांक_match(&fixed0_स्थिरraपूर्णांक, event->hw.config))
		वापस &fixed0_स्थिरraपूर्णांक;

	वापस hsw_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
spr_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;

	c = icl_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);

	/*
	 * The :ppp indicates the Precise Distribution (PDist) facility, which
	 * is only supported on the GP counter 0. If a :ppp event which is not
	 * available on the GP counter 0, error out.
	 */
	अगर (event->attr.precise_ip == 3) अणु
		अगर (c->idxmsk64 & BIT_ULL(0))
			वापस &counter0_स्थिरraपूर्णांक;

		वापस &emptyस्थिरraपूर्णांक;
	पूर्ण

	वापस c;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
glp_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;

	/* :ppp means to करो reduced skid PEBS which is PMC0 only. */
	अगर (event->attr.precise_ip == 3)
		वापस &counter0_स्थिरraपूर्णांक;

	c = पूर्णांकel_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);

	वापस c;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
tnt_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;

	/*
	 * :ppp means to करो reduced skid PEBS,
	 * which is available on PMC0 and fixed counter 0.
	 */
	अगर (event->attr.precise_ip == 3) अणु
		/* Force inकाष्ठाion:ppp on PMC0 and Fixed counter 0 */
		अगर (स्थिरraपूर्णांक_match(&fixed0_स्थिरraपूर्णांक, event->hw.config))
			वापस &fixed0_counter0_स्थिरraपूर्णांक;

		वापस &counter0_स्थिरraपूर्णांक;
	पूर्ण

	c = पूर्णांकel_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);

	वापस c;
पूर्ण

अटल bool allow_tsx_क्रमce_पात = true;

अटल काष्ठा event_स्थिरraपूर्णांक *
tfa_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c = hsw_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);

	/*
	 * Without TFA we must not use PMC3.
	 */
	अगर (!allow_tsx_क्रमce_पात && test_bit(3, c->idxmsk)) अणु
		c = dyn_स्थिरraपूर्णांक(cpuc, c, idx);
		c->idxmsk64 &= ~(1ULL << 3);
		c->weight--;
	पूर्ण

	वापस c;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
adl_get_event_स्थिरraपूर्णांकs(काष्ठा cpu_hw_events *cpuc, पूर्णांक idx,
			  काष्ठा perf_event *event)
अणु
	काष्ठा x86_hybrid_pmu *pmu = hybrid_pmu(event->pmu);

	अगर (pmu->cpu_type == hybrid_big)
		वापस spr_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);
	अन्यथा अगर (pmu->cpu_type == hybrid_small)
		वापस tnt_get_event_स्थिरraपूर्णांकs(cpuc, idx, event);

	WARN_ON(1);
	वापस &emptyस्थिरraपूर्णांक;
पूर्ण

अटल पूर्णांक adl_hw_config(काष्ठा perf_event *event)
अणु
	काष्ठा x86_hybrid_pmu *pmu = hybrid_pmu(event->pmu);

	अगर (pmu->cpu_type == hybrid_big)
		वापस hsw_hw_config(event);
	अन्यथा अगर (pmu->cpu_type == hybrid_small)
		वापस पूर्णांकel_pmu_hw_config(event);

	WARN_ON(1);
	वापस -EOPNOTSUPP;
पूर्ण

अटल u8 adl_get_hybrid_cpu_type(व्योम)
अणु
	वापस hybrid_big;
पूर्ण

/*
 * Broadwell:
 *
 * The INST_RETIRED.ALL period always needs to have lowest 6 bits cleared
 * (BDM55) and it must not use a period smaller than 100 (BDM11). We combine
 * the two to enक्रमce a minimum period of 128 (the smallest value that has bits
 * 0-5 cleared and >= 100).
 *
 * Because of how the code in x86_perf_event_set_period() works, the truncation
 * of the lower 6 bits is 'harmless' as we'll occasionally add a दीर्घer period
 * to make up क्रम the 'lost' events due to carrying the 'error' in period_left.
 *
 * Thereक्रमe the effective (average) period matches the requested period,
 * despite coarser hardware granularity.
 */
अटल u64 bdw_limit_period(काष्ठा perf_event *event, u64 left)
अणु
	अगर ((event->hw.config & INTEL_ARCH_EVENT_MASK) ==
			X86_CONFIG(.event=0xc0, .umask=0x01)) अणु
		अगर (left < 128)
			left = 128;
		left &= ~0x3fULL;
	पूर्ण
	वापस left;
पूर्ण

अटल u64 nhm_limit_period(काष्ठा perf_event *event, u64 left)
अणु
	वापस max(left, 32ULL);
पूर्ण

अटल u64 spr_limit_period(काष्ठा perf_event *event, u64 left)
अणु
	अगर (event->attr.precise_ip == 3)
		वापस max(left, 128ULL);

	वापस left;
पूर्ण

PMU_FORMAT_ATTR(event,	"config:0-7"	);
PMU_FORMAT_ATTR(umask,	"config:8-15"	);
PMU_FORMAT_ATTR(edge,	"config:18"	);
PMU_FORMAT_ATTR(pc,	"config:19"	);
PMU_FORMAT_ATTR(any,	"config:21"	); /* v3 + */
PMU_FORMAT_ATTR(inv,	"config:23"	);
PMU_FORMAT_ATTR(cmask,	"config:24-31"	);
PMU_FORMAT_ATTR(in_tx,  "config:32");
PMU_FORMAT_ATTR(in_tx_cp, "config:33");

अटल काष्ठा attribute *पूर्णांकel_arch_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_pc.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_cmask.attr,
	शून्य,
पूर्ण;

sमाप_प्रकार पूर्णांकel_event_sysfs_show(अक्षर *page, u64 config)
अणु
	u64 event = (config & ARCH_PERFMON_EVENTSEL_EVENT);

	वापस x86_event_sysfs_show(page, config, event);
पूर्ण

अटल काष्ठा पूर्णांकel_shared_regs *allocate_shared_regs(पूर्णांक cpu)
अणु
	काष्ठा पूर्णांकel_shared_regs *regs;
	पूर्णांक i;

	regs = kzalloc_node(माप(काष्ठा पूर्णांकel_shared_regs),
			    GFP_KERNEL, cpu_to_node(cpu));
	अगर (regs) अणु
		/*
		 * initialize the locks to keep lockdep happy
		 */
		क्रम (i = 0; i < EXTRA_REG_MAX; i++)
			raw_spin_lock_init(&regs->regs[i].lock);

		regs->core_id = -1;
	पूर्ण
	वापस regs;
पूर्ण

अटल काष्ठा पूर्णांकel_excl_cntrs *allocate_excl_cntrs(पूर्णांक cpu)
अणु
	काष्ठा पूर्णांकel_excl_cntrs *c;

	c = kzalloc_node(माप(काष्ठा पूर्णांकel_excl_cntrs),
			 GFP_KERNEL, cpu_to_node(cpu));
	अगर (c) अणु
		raw_spin_lock_init(&c->lock);
		c->core_id = -1;
	पूर्ण
	वापस c;
पूर्ण


पूर्णांक पूर्णांकel_cpuc_prepare(काष्ठा cpu_hw_events *cpuc, पूर्णांक cpu)
अणु
	cpuc->pebs_record_size = x86_pmu.pebs_record_size;

	अगर (is_hybrid() || x86_pmu.extra_regs || x86_pmu.lbr_sel_map) अणु
		cpuc->shared_regs = allocate_shared_regs(cpu);
		अगर (!cpuc->shared_regs)
			जाओ err;
	पूर्ण

	अगर (x86_pmu.flags & (PMU_FL_EXCL_CNTRS | PMU_FL_TFA)) अणु
		माप_प्रकार sz = X86_PMC_IDX_MAX * माप(काष्ठा event_स्थिरraपूर्णांक);

		cpuc->स्थिरraपूर्णांक_list = kzalloc_node(sz, GFP_KERNEL, cpu_to_node(cpu));
		अगर (!cpuc->स्थिरraपूर्णांक_list)
			जाओ err_shared_regs;
	पूर्ण

	अगर (x86_pmu.flags & PMU_FL_EXCL_CNTRS) अणु
		cpuc->excl_cntrs = allocate_excl_cntrs(cpu);
		अगर (!cpuc->excl_cntrs)
			जाओ err_स्थिरraपूर्णांक_list;

		cpuc->excl_thपढ़ो_id = 0;
	पूर्ण

	वापस 0;

err_स्थिरraपूर्णांक_list:
	kमुक्त(cpuc->स्थिरraपूर्णांक_list);
	cpuc->स्थिरraपूर्णांक_list = शून्य;

err_shared_regs:
	kमुक्त(cpuc->shared_regs);
	cpuc->shared_regs = शून्य;

err:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_cpu_prepare(पूर्णांक cpu)
अणु
	वापस पूर्णांकel_cpuc_prepare(&per_cpu(cpu_hw_events, cpu), cpu);
पूर्ण

अटल व्योम flip_smm_bit(व्योम *data)
अणु
	अचिन्हित दीर्घ set = *(अचिन्हित दीर्घ *)data;

	अगर (set > 0) अणु
		msr_set_bit(MSR_IA32_DEBUGCTLMSR,
			    DEBUGCTLMSR_FREEZE_IN_SMM_BIT);
	पूर्ण अन्यथा अणु
		msr_clear_bit(MSR_IA32_DEBUGCTLMSR,
			      DEBUGCTLMSR_FREEZE_IN_SMM_BIT);
	पूर्ण
पूर्ण

अटल bool init_hybrid_pmu(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);
	u8 cpu_type = get_this_hybrid_cpu_type();
	काष्ठा x86_hybrid_pmu *pmu = शून्य;
	पूर्णांक i;

	अगर (!cpu_type && x86_pmu.get_hybrid_cpu_type)
		cpu_type = x86_pmu.get_hybrid_cpu_type();

	क्रम (i = 0; i < x86_pmu.num_hybrid_pmus; i++) अणु
		अगर (x86_pmu.hybrid_pmu[i].cpu_type == cpu_type) अणु
			pmu = &x86_pmu.hybrid_pmu[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (WARN_ON_ONCE(!pmu || (pmu->pmu.type == -1))) अणु
		cpuc->pmu = शून्य;
		वापस false;
	पूर्ण

	/* Only check and dump the PMU inक्रमmation क्रम the first CPU */
	अगर (!cpumask_empty(&pmu->supported_cpus))
		जाओ end;

	अगर (!check_hw_exists(&pmu->pmu, pmu->num_counters, pmu->num_counters_fixed))
		वापस false;

	pr_info("%s PMU driver: ", pmu->name);

	अगर (pmu->पूर्णांकel_cap.pebs_output_pt_available)
		pr_cont("PEBS-via-PT ");

	pr_cont("\n");

	x86_pmu_show_pmu_cap(pmu->num_counters, pmu->num_counters_fixed,
			     pmu->पूर्णांकel_ctrl);

end:
	cpumask_set_cpu(cpu, &pmu->supported_cpus);
	cpuc->pmu = &pmu->pmu;

	x86_pmu_update_cpu_context(&pmu->pmu, cpu);

	वापस true;
पूर्ण

अटल व्योम पूर्णांकel_pmu_cpu_starting(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);
	पूर्णांक core_id = topology_core_id(cpu);
	पूर्णांक i;

	अगर (is_hybrid() && !init_hybrid_pmu(cpu))
		वापस;

	init_debug_store_on_cpu(cpu);
	/*
	 * Deal with CPUs that करोn't clear their LBRs on घातer-up.
	 */
	पूर्णांकel_pmu_lbr_reset();

	cpuc->lbr_sel = शून्य;

	अगर (x86_pmu.flags & PMU_FL_TFA) अणु
		WARN_ON_ONCE(cpuc->tfa_shaकरोw);
		cpuc->tfa_shaकरोw = ~0ULL;
		पूर्णांकel_set_tfa(cpuc, false);
	पूर्ण

	अगर (x86_pmu.version > 1)
		flip_smm_bit(&x86_pmu.attr_मुक्तze_on_smi);

	/*
	 * Disable perf metrics अगर any added CPU करोesn't support it.
	 *
	 * Turn off the check क्रम a hybrid architecture, because the
	 * architecture MSR, MSR_IA32_PERF_CAPABILITIES, only indicate
	 * the architecture features. The perf metrics is a model-specअगरic
	 * feature क्रम now. The corresponding bit should always be 0 on
	 * a hybrid platक्रमm, e.g., Alder Lake.
	 */
	अगर (!is_hybrid() && x86_pmu.पूर्णांकel_cap.perf_metrics) अणु
		जोड़ perf_capabilities perf_cap;

		rdmsrl(MSR_IA32_PERF_CAPABILITIES, perf_cap.capabilities);
		अगर (!perf_cap.perf_metrics) अणु
			x86_pmu.पूर्णांकel_cap.perf_metrics = 0;
			x86_pmu.पूर्णांकel_ctrl &= ~(1ULL << GLOBAL_CTRL_EN_PERF_METRICS);
		पूर्ण
	पूर्ण

	अगर (!cpuc->shared_regs)
		वापस;

	अगर (!(x86_pmu.flags & PMU_FL_NO_HT_SHARING)) अणु
		क्रम_each_cpu(i, topology_sibling_cpumask(cpu)) अणु
			काष्ठा पूर्णांकel_shared_regs *pc;

			pc = per_cpu(cpu_hw_events, i).shared_regs;
			अगर (pc && pc->core_id == core_id) अणु
				cpuc->kमुक्त_on_online[0] = cpuc->shared_regs;
				cpuc->shared_regs = pc;
				अवरोध;
			पूर्ण
		पूर्ण
		cpuc->shared_regs->core_id = core_id;
		cpuc->shared_regs->refcnt++;
	पूर्ण

	अगर (x86_pmu.lbr_sel_map)
		cpuc->lbr_sel = &cpuc->shared_regs->regs[EXTRA_REG_LBR];

	अगर (x86_pmu.flags & PMU_FL_EXCL_CNTRS) अणु
		क्रम_each_cpu(i, topology_sibling_cpumask(cpu)) अणु
			काष्ठा cpu_hw_events *sibling;
			काष्ठा पूर्णांकel_excl_cntrs *c;

			sibling = &per_cpu(cpu_hw_events, i);
			c = sibling->excl_cntrs;
			अगर (c && c->core_id == core_id) अणु
				cpuc->kमुक्त_on_online[1] = cpuc->excl_cntrs;
				cpuc->excl_cntrs = c;
				अगर (!sibling->excl_thपढ़ो_id)
					cpuc->excl_thपढ़ो_id = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		cpuc->excl_cntrs->core_id = core_id;
		cpuc->excl_cntrs->refcnt++;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_excl_cntrs(काष्ठा cpu_hw_events *cpuc)
अणु
	काष्ठा पूर्णांकel_excl_cntrs *c;

	c = cpuc->excl_cntrs;
	अगर (c) अणु
		अगर (c->core_id == -1 || --c->refcnt == 0)
			kमुक्त(c);
		cpuc->excl_cntrs = शून्य;
	पूर्ण

	kमुक्त(cpuc->स्थिरraपूर्णांक_list);
	cpuc->स्थिरraपूर्णांक_list = शून्य;
पूर्ण

अटल व्योम पूर्णांकel_pmu_cpu_dying(पूर्णांक cpu)
अणु
	fini_debug_store_on_cpu(cpu);
पूर्ण

व्योम पूर्णांकel_cpuc_finish(काष्ठा cpu_hw_events *cpuc)
अणु
	काष्ठा पूर्णांकel_shared_regs *pc;

	pc = cpuc->shared_regs;
	अगर (pc) अणु
		अगर (pc->core_id == -1 || --pc->refcnt == 0)
			kमुक्त(pc);
		cpuc->shared_regs = शून्य;
	पूर्ण

	मुक्त_excl_cntrs(cpuc);
पूर्ण

अटल व्योम पूर्णांकel_pmu_cpu_dead(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);

	पूर्णांकel_cpuc_finish(cpuc);

	अगर (is_hybrid() && cpuc->pmu)
		cpumask_clear_cpu(cpu, &hybrid_pmu(cpuc->pmu)->supported_cpus);
पूर्ण

अटल व्योम पूर्णांकel_pmu_sched_task(काष्ठा perf_event_context *ctx,
				 bool sched_in)
अणु
	पूर्णांकel_pmu_pebs_sched_task(ctx, sched_in);
	पूर्णांकel_pmu_lbr_sched_task(ctx, sched_in);
पूर्ण

अटल व्योम पूर्णांकel_pmu_swap_task_ctx(काष्ठा perf_event_context *prev,
				    काष्ठा perf_event_context *next)
अणु
	पूर्णांकel_pmu_lbr_swap_task_ctx(prev, next);
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_check_period(काष्ठा perf_event *event, u64 value)
अणु
	वापस पूर्णांकel_pmu_has_bts_period(event, value) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_aux_output_match(काष्ठा perf_event *event)
अणु
	अगर (!x86_pmu.पूर्णांकel_cap.pebs_output_pt_available)
		वापस 0;

	वापस is_पूर्णांकel_pt_event(event);
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_filter_match(काष्ठा perf_event *event)
अणु
	काष्ठा x86_hybrid_pmu *pmu = hybrid_pmu(event->pmu);
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	वापस cpumask_test_cpu(cpu, &pmu->supported_cpus);
पूर्ण

PMU_FORMAT_ATTR(offcore_rsp, "config1:0-63");

PMU_FORMAT_ATTR(ldlat, "config1:0-15");

PMU_FORMAT_ATTR(frontend, "config1:0-23");

अटल काष्ठा attribute *पूर्णांकel_arch3_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_pc.attr,
	&क्रमmat_attr_any.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_cmask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *hsw_क्रमmat_attr[] = अणु
	&क्रमmat_attr_in_tx.attr,
	&क्रमmat_attr_in_tx_cp.attr,
	&क्रमmat_attr_offcore_rsp.attr,
	&क्रमmat_attr_ldlat.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *nhm_क्रमmat_attr[] = अणु
	&क्रमmat_attr_offcore_rsp.attr,
	&क्रमmat_attr_ldlat.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *slm_क्रमmat_attr[] = अणु
	&क्रमmat_attr_offcore_rsp.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *skl_क्रमmat_attr[] = अणु
	&क्रमmat_attr_frontend.attr,
	शून्य,
पूर्ण;

अटल __initस्थिर स्थिर काष्ठा x86_pmu core_pmu = अणु
	.name			= "core",
	.handle_irq		= x86_pmu_handle_irq,
	.disable_all		= x86_pmu_disable_all,
	.enable_all		= core_pmu_enable_all,
	.enable			= core_pmu_enable_event,
	.disable		= x86_pmu_disable_event,
	.hw_config		= core_pmu_hw_config,
	.schedule_events	= x86_schedule_events,
	.eventsel		= MSR_ARCH_PERFMON_EVENTSEL0,
	.perfctr		= MSR_ARCH_PERFMON_PERFCTR0,
	.event_map		= पूर्णांकel_pmu_event_map,
	.max_events		= ARRAY_SIZE(पूर्णांकel_perfmon_event_map),
	.apic			= 1,
	.large_pebs_flags	= LARGE_PEBS_FLAGS,

	/*
	 * Intel PMCs cannot be accessed sanely above 32-bit width,
	 * so we install an artअगरicial 1<<31 period regardless of
	 * the generic event period:
	 */
	.max_period		= (1ULL<<31) - 1,
	.get_event_स्थिरraपूर्णांकs	= पूर्णांकel_get_event_स्थिरraपूर्णांकs,
	.put_event_स्थिरraपूर्णांकs	= पूर्णांकel_put_event_स्थिरraपूर्णांकs,
	.event_स्थिरraपूर्णांकs	= पूर्णांकel_core_event_स्थिरraपूर्णांकs,
	.guest_get_msrs		= core_guest_get_msrs,
	.क्रमmat_attrs		= पूर्णांकel_arch_क्रमmats_attr,
	.events_sysfs_show	= पूर्णांकel_event_sysfs_show,

	/*
	 * Virtual (or funny metal) CPU can define x86_pmu.extra_regs
	 * together with PMU version 1 and thus be using core_pmu with
	 * shared_regs. We need following callbacks here to allocate
	 * it properly.
	 */
	.cpu_prepare		= पूर्णांकel_pmu_cpu_prepare,
	.cpu_starting		= पूर्णांकel_pmu_cpu_starting,
	.cpu_dying		= पूर्णांकel_pmu_cpu_dying,
	.cpu_dead		= पूर्णांकel_pmu_cpu_dead,

	.check_period		= पूर्णांकel_pmu_check_period,

	.lbr_reset		= पूर्णांकel_pmu_lbr_reset_64,
	.lbr_पढ़ो		= पूर्णांकel_pmu_lbr_पढ़ो_64,
	.lbr_save		= पूर्णांकel_pmu_lbr_save,
	.lbr_restore		= पूर्णांकel_pmu_lbr_restore,
पूर्ण;

अटल __initस्थिर स्थिर काष्ठा x86_pmu पूर्णांकel_pmu = अणु
	.name			= "Intel",
	.handle_irq		= पूर्णांकel_pmu_handle_irq,
	.disable_all		= पूर्णांकel_pmu_disable_all,
	.enable_all		= पूर्णांकel_pmu_enable_all,
	.enable			= पूर्णांकel_pmu_enable_event,
	.disable		= पूर्णांकel_pmu_disable_event,
	.add			= पूर्णांकel_pmu_add_event,
	.del			= पूर्णांकel_pmu_del_event,
	.पढ़ो			= पूर्णांकel_pmu_पढ़ो_event,
	.hw_config		= पूर्णांकel_pmu_hw_config,
	.schedule_events	= x86_schedule_events,
	.eventsel		= MSR_ARCH_PERFMON_EVENTSEL0,
	.perfctr		= MSR_ARCH_PERFMON_PERFCTR0,
	.event_map		= पूर्णांकel_pmu_event_map,
	.max_events		= ARRAY_SIZE(पूर्णांकel_perfmon_event_map),
	.apic			= 1,
	.large_pebs_flags	= LARGE_PEBS_FLAGS,
	/*
	 * Intel PMCs cannot be accessed sanely above 32 bit width,
	 * so we install an artअगरicial 1<<31 period regardless of
	 * the generic event period:
	 */
	.max_period		= (1ULL << 31) - 1,
	.get_event_स्थिरraपूर्णांकs	= पूर्णांकel_get_event_स्थिरraपूर्णांकs,
	.put_event_स्थिरraपूर्णांकs	= पूर्णांकel_put_event_स्थिरraपूर्णांकs,
	.pebs_aliases		= पूर्णांकel_pebs_aliases_core2,

	.क्रमmat_attrs		= पूर्णांकel_arch3_क्रमmats_attr,
	.events_sysfs_show	= पूर्णांकel_event_sysfs_show,

	.cpu_prepare		= पूर्णांकel_pmu_cpu_prepare,
	.cpu_starting		= पूर्णांकel_pmu_cpu_starting,
	.cpu_dying		= पूर्णांकel_pmu_cpu_dying,
	.cpu_dead		= पूर्णांकel_pmu_cpu_dead,

	.guest_get_msrs		= पूर्णांकel_guest_get_msrs,
	.sched_task		= पूर्णांकel_pmu_sched_task,
	.swap_task_ctx		= पूर्णांकel_pmu_swap_task_ctx,

	.check_period		= पूर्णांकel_pmu_check_period,

	.aux_output_match	= पूर्णांकel_pmu_aux_output_match,

	.lbr_reset		= पूर्णांकel_pmu_lbr_reset_64,
	.lbr_पढ़ो		= पूर्णांकel_pmu_lbr_पढ़ो_64,
	.lbr_save		= पूर्णांकel_pmu_lbr_save,
	.lbr_restore		= पूर्णांकel_pmu_lbr_restore,
पूर्ण;

अटल __init व्योम पूर्णांकel_clovertown_quirk(व्योम)
अणु
	/*
	 * PEBS is unreliable due to:
	 *
	 *   AJ67  - PEBS may experience CPL leaks
	 *   AJ68  - PEBS PMI may be delayed by one event
	 *   AJ69  - GLOBAL_STATUS[62] will only be set when DEBUGCTL[12]
	 *   AJ106 - FREEZE_LBRS_ON_PMI करोesn't work in combination with PEBS
	 *
	 * AJ67 could be worked around by restricting the OS/USR flags.
	 * AJ69 could be worked around by setting PMU_FREEZE_ON_PMI.
	 *
	 * AJ106 could possibly be worked around by not allowing LBR
	 *       usage from PEBS, including the fixup.
	 * AJ68  could possibly be worked around by always programming
	 *	 a pebs_event_reset[0] value and coping with the lost events.
	 *
	 * But taken together it might just make sense to not enable PEBS on
	 * these chips.
	 */
	pr_warn("PEBS disabled due to CPU errata\n");
	x86_pmu.pebs = 0;
	x86_pmu.pebs_स्थिरraपूर्णांकs = शून्य;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_desc isolation_ucodes[] = अणु
	INTEL_CPU_DESC(INTEL_FAM6_HASWELL,		 3, 0x0000001f),
	INTEL_CPU_DESC(INTEL_FAM6_HASWELL_L,		 1, 0x0000001e),
	INTEL_CPU_DESC(INTEL_FAM6_HASWELL_G,		 1, 0x00000015),
	INTEL_CPU_DESC(INTEL_FAM6_HASWELL_X,		 2, 0x00000037),
	INTEL_CPU_DESC(INTEL_FAM6_HASWELL_X,		 4, 0x0000000a),
	INTEL_CPU_DESC(INTEL_FAM6_BROADWELL,		 4, 0x00000023),
	INTEL_CPU_DESC(INTEL_FAM6_BROADWELL_G,		 1, 0x00000014),
	INTEL_CPU_DESC(INTEL_FAM6_BROADWELL_D,		 2, 0x00000010),
	INTEL_CPU_DESC(INTEL_FAM6_BROADWELL_D,		 3, 0x07000009),
	INTEL_CPU_DESC(INTEL_FAM6_BROADWELL_D,		 4, 0x0f000009),
	INTEL_CPU_DESC(INTEL_FAM6_BROADWELL_D,		 5, 0x0e000002),
	INTEL_CPU_DESC(INTEL_FAM6_BROADWELL_X,		 1, 0x0b000014),
	INTEL_CPU_DESC(INTEL_FAM6_SKYLAKE_X,		 3, 0x00000021),
	INTEL_CPU_DESC(INTEL_FAM6_SKYLAKE_X,		 4, 0x00000000),
	INTEL_CPU_DESC(INTEL_FAM6_SKYLAKE_X,		 5, 0x00000000),
	INTEL_CPU_DESC(INTEL_FAM6_SKYLAKE_X,		 6, 0x00000000),
	INTEL_CPU_DESC(INTEL_FAM6_SKYLAKE_X,		 7, 0x00000000),
	INTEL_CPU_DESC(INTEL_FAM6_SKYLAKE_L,		 3, 0x0000007c),
	INTEL_CPU_DESC(INTEL_FAM6_SKYLAKE,		 3, 0x0000007c),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE,		 9, 0x0000004e),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE_L,		 9, 0x0000004e),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE_L,		10, 0x0000004e),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE_L,		11, 0x0000004e),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE_L,		12, 0x0000004e),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE,		10, 0x0000004e),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE,		11, 0x0000004e),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE,		12, 0x0000004e),
	INTEL_CPU_DESC(INTEL_FAM6_KABYLAKE,		13, 0x0000004e),
	अणुपूर्ण
पूर्ण;

अटल व्योम पूर्णांकel_check_pebs_isolation(व्योम)
अणु
	x86_pmu.pebs_no_isolation = !x86_cpu_has_min_microcode_rev(isolation_ucodes);
पूर्ण

अटल __init व्योम पूर्णांकel_pebs_isolation_quirk(व्योम)
अणु
	WARN_ON_ONCE(x86_pmu.check_microcode);
	x86_pmu.check_microcode = पूर्णांकel_check_pebs_isolation;
	पूर्णांकel_check_pebs_isolation();
पूर्ण

अटल स्थिर काष्ठा x86_cpu_desc pebs_ucodes[] = अणु
	INTEL_CPU_DESC(INTEL_FAM6_SANDYBRIDGE,		7, 0x00000028),
	INTEL_CPU_DESC(INTEL_FAM6_SANDYBRIDGE_X,	6, 0x00000618),
	INTEL_CPU_DESC(INTEL_FAM6_SANDYBRIDGE_X,	7, 0x0000070c),
	अणुपूर्ण
पूर्ण;

अटल bool पूर्णांकel_snb_pebs_broken(व्योम)
अणु
	वापस !x86_cpu_has_min_microcode_rev(pebs_ucodes);
पूर्ण

अटल व्योम पूर्णांकel_snb_check_microcode(व्योम)
अणु
	अगर (पूर्णांकel_snb_pebs_broken() == x86_pmu.pebs_broken)
		वापस;

	/*
	 * Serialized by the microcode lock..
	 */
	अगर (x86_pmu.pebs_broken) अणु
		pr_info("PEBS enabled due to microcode update\n");
		x86_pmu.pebs_broken = 0;
	पूर्ण अन्यथा अणु
		pr_info("PEBS disabled due to CPU errata, please upgrade microcode\n");
		x86_pmu.pebs_broken = 1;
	पूर्ण
पूर्ण

अटल bool is_lbr_from(अचिन्हित दीर्घ msr)
अणु
	अचिन्हित दीर्घ lbr_from_nr = x86_pmu.lbr_from + x86_pmu.lbr_nr;

	वापस x86_pmu.lbr_from <= msr && msr < lbr_from_nr;
पूर्ण

/*
 * Under certain circumstances, access certain MSR may cause #GP.
 * The function tests अगर the input MSR can be safely accessed.
 */
अटल bool check_msr(अचिन्हित दीर्घ msr, u64 mask)
अणु
	u64 val_old, val_new, val_पंचांगp;

	/*
	 * Disable the check क्रम real HW, so we करोn't
	 * mess with potentially enabled रेजिस्टरs:
	 */
	अगर (!boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस true;

	/*
	 * Read the current value, change it and पढ़ो it back to see अगर it
	 * matches, this is needed to detect certain hardware emulators
	 * (qemu/kvm) that करोn't trap on the MSR access and always वापस 0s.
	 */
	अगर (rdmsrl_safe(msr, &val_old))
		वापस false;

	/*
	 * Only change the bits which can be updated by wrmsrl.
	 */
	val_पंचांगp = val_old ^ mask;

	अगर (is_lbr_from(msr))
		val_पंचांगp = lbr_from_signext_quirk_wr(val_पंचांगp);

	अगर (wrmsrl_safe(msr, val_पंचांगp) ||
	    rdmsrl_safe(msr, &val_new))
		वापस false;

	/*
	 * Quirk only affects validation in wrmsr(), so wrmsrl()'s value
	 * should equal rdmsrl()'s even with the quirk.
	 */
	अगर (val_new != val_पंचांगp)
		वापस false;

	अगर (is_lbr_from(msr))
		val_old = lbr_from_signext_quirk_wr(val_old);

	/* Here it's sure that the MSR can be safely accessed.
	 * Restore the old value and वापस.
	 */
	wrmsrl(msr, val_old);

	वापस true;
पूर्ण

अटल __init व्योम पूर्णांकel_sandybridge_quirk(व्योम)
अणु
	x86_pmu.check_microcode = पूर्णांकel_snb_check_microcode;
	cpus_पढ़ो_lock();
	पूर्णांकel_snb_check_microcode();
	cpus_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा अणु पूर्णांक id; अक्षर *name; पूर्ण पूर्णांकel_arch_events_map[] __initस्थिर = अणु
	अणु PERF_COUNT_HW_CPU_CYCLES, "cpu cycles" पूर्ण,
	अणु PERF_COUNT_HW_INSTRUCTIONS, "instructions" पूर्ण,
	अणु PERF_COUNT_HW_BUS_CYCLES, "bus cycles" पूर्ण,
	अणु PERF_COUNT_HW_CACHE_REFERENCES, "cache references" पूर्ण,
	अणु PERF_COUNT_HW_CACHE_MISSES, "cache misses" पूर्ण,
	अणु PERF_COUNT_HW_BRANCH_INSTRUCTIONS, "branch instructions" पूर्ण,
	अणु PERF_COUNT_HW_BRANCH_MISSES, "branch misses" पूर्ण,
पूर्ण;

अटल __init व्योम पूर्णांकel_arch_events_quirk(व्योम)
अणु
	पूर्णांक bit;

	/* disable event that reported as not present by cpuid */
	क्रम_each_set_bit(bit, x86_pmu.events_mask, ARRAY_SIZE(पूर्णांकel_arch_events_map)) अणु
		पूर्णांकel_perfmon_event_map[पूर्णांकel_arch_events_map[bit].id] = 0;
		pr_warn("CPUID marked event: \'%s\' unavailable\n",
			पूर्णांकel_arch_events_map[bit].name);
	पूर्ण
पूर्ण

अटल __init व्योम पूर्णांकel_nehalem_quirk(व्योम)
अणु
	जोड़ cpuid10_ebx ebx;

	ebx.full = x86_pmu.events_maskl;
	अगर (ebx.split.no_branch_misses_retired) अणु
		/*
		 * Erratum AAJ80 detected, we work it around by using
		 * the BR_MISP_EXEC.ANY event. This will over-count
		 * branch-misses, but it's still much better than the
		 * architectural event which is often completely bogus:
		 */
		पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_BRANCH_MISSES] = 0x7f89;
		ebx.split.no_branch_misses_retired = 0;
		x86_pmu.events_maskl = ebx.full;
		pr_info("CPU erratum AAJ80 worked around\n");
	पूर्ण
पूर्ण

/*
 * enable software workaround क्रम errata:
 * SNB: BJ122
 * IVB: BV98
 * HSW: HSD29
 *
 * Only needed when HT is enabled. However detecting
 * अगर HT is enabled is dअगरficult (model specअगरic). So instead,
 * we enable the workaround in the early boot, and verअगरy अगर
 * it is needed in a later initcall phase once we have valid
 * topology inक्रमmation to check अगर HT is actually enabled
 */
अटल __init व्योम पूर्णांकel_ht_bug(व्योम)
अणु
	x86_pmu.flags |= PMU_FL_EXCL_CNTRS | PMU_FL_EXCL_ENABLED;

	x86_pmu.start_scheduling = पूर्णांकel_start_scheduling;
	x86_pmu.commit_scheduling = पूर्णांकel_commit_scheduling;
	x86_pmu.stop_scheduling = पूर्णांकel_stop_scheduling;
पूर्ण

EVENT_ATTR_STR(mem-loads,	mem_ld_hsw,	"event=0xcd,umask=0x1,ldlat=3");
EVENT_ATTR_STR(mem-stores,	mem_st_hsw,	"event=0xd0,umask=0x82")

/* Haswell special events */
EVENT_ATTR_STR(tx-start,	tx_start,	"event=0xc9,umask=0x1");
EVENT_ATTR_STR(tx-commit,	tx_commit,	"event=0xc9,umask=0x2");
EVENT_ATTR_STR(tx-पात,	tx_पात,	"event=0xc9,umask=0x4");
EVENT_ATTR_STR(tx-capacity,	tx_capacity,	"event=0x54,umask=0x2");
EVENT_ATTR_STR(tx-conflict,	tx_conflict,	"event=0x54,umask=0x1");
EVENT_ATTR_STR(el-start,	el_start,	"event=0xc8,umask=0x1");
EVENT_ATTR_STR(el-commit,	el_commit,	"event=0xc8,umask=0x2");
EVENT_ATTR_STR(el-पात,	el_पात,	"event=0xc8,umask=0x4");
EVENT_ATTR_STR(el-capacity,	el_capacity,	"event=0x54,umask=0x2");
EVENT_ATTR_STR(el-conflict,	el_conflict,	"event=0x54,umask=0x1");
EVENT_ATTR_STR(cycles-t,	cycles_t,	"event=0x3c,in_tx=1");
EVENT_ATTR_STR(cycles-ct,	cycles_ct,	"event=0x3c,in_tx=1,in_tx_cp=1");

अटल काष्ठा attribute *hsw_events_attrs[] = अणु
	EVENT_PTR(td_slots_issued),
	EVENT_PTR(td_slots_retired),
	EVENT_PTR(td_fetch_bubbles),
	EVENT_PTR(td_total_slots),
	EVENT_PTR(td_total_slots_scale),
	EVENT_PTR(td_recovery_bubbles),
	EVENT_PTR(td_recovery_bubbles_scale),
	शून्य
पूर्ण;

अटल काष्ठा attribute *hsw_mem_events_attrs[] = अणु
	EVENT_PTR(mem_ld_hsw),
	EVENT_PTR(mem_st_hsw),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *hsw_tsx_events_attrs[] = अणु
	EVENT_PTR(tx_start),
	EVENT_PTR(tx_commit),
	EVENT_PTR(tx_पात),
	EVENT_PTR(tx_capacity),
	EVENT_PTR(tx_conflict),
	EVENT_PTR(el_start),
	EVENT_PTR(el_commit),
	EVENT_PTR(el_पात),
	EVENT_PTR(el_capacity),
	EVENT_PTR(el_conflict),
	EVENT_PTR(cycles_t),
	EVENT_PTR(cycles_ct),
	शून्य
पूर्ण;

EVENT_ATTR_STR(tx-capacity-पढ़ो,  tx_capacity_पढ़ो,  "event=0x54,umask=0x80");
EVENT_ATTR_STR(tx-capacity-ग_लिखो, tx_capacity_ग_लिखो, "event=0x54,umask=0x2");
EVENT_ATTR_STR(el-capacity-पढ़ो,  el_capacity_पढ़ो,  "event=0x54,umask=0x80");
EVENT_ATTR_STR(el-capacity-ग_लिखो, el_capacity_ग_लिखो, "event=0x54,umask=0x2");

अटल काष्ठा attribute *icl_events_attrs[] = अणु
	EVENT_PTR(mem_ld_hsw),
	EVENT_PTR(mem_st_hsw),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *icl_td_events_attrs[] = अणु
	EVENT_PTR(slots),
	EVENT_PTR(td_retiring),
	EVENT_PTR(td_bad_spec),
	EVENT_PTR(td_fe_bound),
	EVENT_PTR(td_be_bound),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *icl_tsx_events_attrs[] = अणु
	EVENT_PTR(tx_start),
	EVENT_PTR(tx_पात),
	EVENT_PTR(tx_commit),
	EVENT_PTR(tx_capacity_पढ़ो),
	EVENT_PTR(tx_capacity_ग_लिखो),
	EVENT_PTR(tx_conflict),
	EVENT_PTR(el_start),
	EVENT_PTR(el_पात),
	EVENT_PTR(el_commit),
	EVENT_PTR(el_capacity_पढ़ो),
	EVENT_PTR(el_capacity_ग_लिखो),
	EVENT_PTR(el_conflict),
	EVENT_PTR(cycles_t),
	EVENT_PTR(cycles_ct),
	शून्य,
पूर्ण;


EVENT_ATTR_STR(mem-stores,	mem_st_spr,	"event=0xcd,umask=0x2");
EVENT_ATTR_STR(mem-loads-aux,	mem_ld_aux,	"event=0x03,umask=0x82");

अटल काष्ठा attribute *spr_events_attrs[] = अणु
	EVENT_PTR(mem_ld_hsw),
	EVENT_PTR(mem_st_spr),
	EVENT_PTR(mem_ld_aux),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *spr_td_events_attrs[] = अणु
	EVENT_PTR(slots),
	EVENT_PTR(td_retiring),
	EVENT_PTR(td_bad_spec),
	EVENT_PTR(td_fe_bound),
	EVENT_PTR(td_be_bound),
	EVENT_PTR(td_heavy_ops),
	EVENT_PTR(td_br_mispredict),
	EVENT_PTR(td_fetch_lat),
	EVENT_PTR(td_mem_bound),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *spr_tsx_events_attrs[] = अणु
	EVENT_PTR(tx_start),
	EVENT_PTR(tx_पात),
	EVENT_PTR(tx_commit),
	EVENT_PTR(tx_capacity_पढ़ो),
	EVENT_PTR(tx_capacity_ग_लिखो),
	EVENT_PTR(tx_conflict),
	EVENT_PTR(cycles_t),
	EVENT_PTR(cycles_ct),
	शून्य,
पूर्ण;

अटल sमाप_प्रकार मुक्तze_on_smi_show(काष्ठा device *cdev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", x86_pmu.attr_मुक्तze_on_smi);
पूर्ण

अटल DEFINE_MUTEX(मुक्तze_on_smi_mutex);

अटल sमाप_प्रकार मुक्तze_on_smi_store(काष्ठा device *cdev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&मुक्तze_on_smi_mutex);

	अगर (x86_pmu.attr_मुक्तze_on_smi == val)
		जाओ करोne;

	x86_pmu.attr_मुक्तze_on_smi = val;

	get_online_cpus();
	on_each_cpu(flip_smm_bit, &val, 1);
	put_online_cpus();
करोne:
	mutex_unlock(&मुक्तze_on_smi_mutex);

	वापस count;
पूर्ण

अटल व्योम update_tfa_sched(व्योम *ignored)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * check अगर PMC3 is used
	 * and अगर so क्रमce schedule out क्रम all event types all contexts
	 */
	अगर (test_bit(3, cpuc->active_mask))
		perf_pmu_resched(x86_get_pmu(smp_processor_id()));
पूर्ण

अटल sमाप_प्रकार show_sysctl_tfa(काष्ठा device *cdev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस snम_लिखो(buf, 40, "%d\n", allow_tsx_क्रमce_पात);
पूर्ण

अटल sमाप_प्रकार set_sysctl_tfa(काष्ठा device *cdev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bool val;
	sमाप_प्रकार ret;

	ret = kstrtobool(buf, &val);
	अगर (ret)
		वापस ret;

	/* no change */
	अगर (val == allow_tsx_क्रमce_पात)
		वापस count;

	allow_tsx_क्रमce_पात = val;

	get_online_cpus();
	on_each_cpu(update_tfa_sched, शून्य, 1);
	put_online_cpus();

	वापस count;
पूर्ण


अटल DEVICE_ATTR_RW(मुक्तze_on_smi);

अटल sमाप_प्रकार branches_show(काष्ठा device *cdev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", x86_pmu.lbr_nr);
पूर्ण

अटल DEVICE_ATTR_RO(branches);

अटल काष्ठा attribute *lbr_attrs[] = अणु
	&dev_attr_branches.attr,
	शून्य
पूर्ण;

अटल अक्षर pmu_name_str[30];

अटल sमाप_प्रकार pmu_name_show(काष्ठा device *cdev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", pmu_name_str);
पूर्ण

अटल DEVICE_ATTR_RO(pmu_name);

अटल काष्ठा attribute *पूर्णांकel_pmu_caps_attrs[] = अणु
       &dev_attr_pmu_name.attr,
       शून्य
पूर्ण;

अटल DEVICE_ATTR(allow_tsx_क्रमce_पात, 0644,
		   show_sysctl_tfa,
		   set_sysctl_tfa);

अटल काष्ठा attribute *पूर्णांकel_pmu_attrs[] = अणु
	&dev_attr_मुक्तze_on_smi.attr,
	&dev_attr_allow_tsx_क्रमce_पात.attr,
	शून्य,
पूर्ण;

अटल umode_t
tsx_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक i)
अणु
	वापस boot_cpu_has(X86_FEATURE_RTM) ? attr->mode : 0;
पूर्ण

अटल umode_t
pebs_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक i)
अणु
	वापस x86_pmu.pebs ? attr->mode : 0;
पूर्ण

अटल umode_t
lbr_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक i)
अणु
	वापस x86_pmu.lbr_nr ? attr->mode : 0;
पूर्ण

अटल umode_t
exra_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक i)
अणु
	वापस x86_pmu.version >= 2 ? attr->mode : 0;
पूर्ण

अटल umode_t
शेष_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक i)
अणु
	अगर (attr == &dev_attr_allow_tsx_क्रमce_पात.attr)
		वापस x86_pmu.flags & PMU_FL_TFA ? attr->mode : 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute_group group_events_td  = अणु
	.name = "events",
पूर्ण;

अटल काष्ठा attribute_group group_events_mem = अणु
	.name       = "events",
	.is_visible = pebs_is_visible,
पूर्ण;

अटल काष्ठा attribute_group group_events_tsx = अणु
	.name       = "events",
	.is_visible = tsx_is_visible,
पूर्ण;

अटल काष्ठा attribute_group group_caps_gen = अणु
	.name  = "caps",
	.attrs = पूर्णांकel_pmu_caps_attrs,
पूर्ण;

अटल काष्ठा attribute_group group_caps_lbr = अणु
	.name       = "caps",
	.attrs	    = lbr_attrs,
	.is_visible = lbr_is_visible,
पूर्ण;

अटल काष्ठा attribute_group group_क्रमmat_extra = अणु
	.name       = "format",
	.is_visible = exra_is_visible,
पूर्ण;

अटल काष्ठा attribute_group group_क्रमmat_extra_skl = अणु
	.name       = "format",
	.is_visible = exra_is_visible,
पूर्ण;

अटल काष्ठा attribute_group group_शेष = अणु
	.attrs      = पूर्णांकel_pmu_attrs,
	.is_visible = शेष_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_update[] = अणु
	&group_events_td,
	&group_events_mem,
	&group_events_tsx,
	&group_caps_gen,
	&group_caps_lbr,
	&group_क्रमmat_extra,
	&group_क्रमmat_extra_skl,
	&group_शेष,
	शून्य,
पूर्ण;

EVENT_ATTR_STR_HYBRID(slots,                 slots_adl,        "event=0x00,umask=0x4",                       hybrid_big);
EVENT_ATTR_STR_HYBRID(topकरोwn-retiring,      td_retiring_adl,  "event=0xc2,umask=0x0;event=0x00,umask=0x80", hybrid_big_small);
EVENT_ATTR_STR_HYBRID(topकरोwn-bad-spec,      td_bad_spec_adl,  "event=0x73,umask=0x0;event=0x00,umask=0x81", hybrid_big_small);
EVENT_ATTR_STR_HYBRID(topकरोwn-fe-bound,      td_fe_bound_adl,  "event=0x71,umask=0x0;event=0x00,umask=0x82", hybrid_big_small);
EVENT_ATTR_STR_HYBRID(topकरोwn-be-bound,      td_be_bound_adl,  "event=0x74,umask=0x0;event=0x00,umask=0x83", hybrid_big_small);
EVENT_ATTR_STR_HYBRID(topकरोwn-heavy-ops,     td_heavy_ops_adl, "event=0x00,umask=0x84",                      hybrid_big);
EVENT_ATTR_STR_HYBRID(topकरोwn-br-mispredict, td_br_mis_adl,    "event=0x00,umask=0x85",                      hybrid_big);
EVENT_ATTR_STR_HYBRID(topकरोwn-fetch-lat,     td_fetch_lat_adl, "event=0x00,umask=0x86",                      hybrid_big);
EVENT_ATTR_STR_HYBRID(topकरोwn-mem-bound,     td_mem_bound_adl, "event=0x00,umask=0x87",                      hybrid_big);

अटल काष्ठा attribute *adl_hybrid_events_attrs[] = अणु
	EVENT_PTR(slots_adl),
	EVENT_PTR(td_retiring_adl),
	EVENT_PTR(td_bad_spec_adl),
	EVENT_PTR(td_fe_bound_adl),
	EVENT_PTR(td_be_bound_adl),
	EVENT_PTR(td_heavy_ops_adl),
	EVENT_PTR(td_br_mis_adl),
	EVENT_PTR(td_fetch_lat_adl),
	EVENT_PTR(td_mem_bound_adl),
	शून्य,
पूर्ण;

/* Must be in IDX order */
EVENT_ATTR_STR_HYBRID(mem-loads,     mem_ld_adl,     "event=0xd0,umask=0x5,ldlat=3;event=0xcd,umask=0x1,ldlat=3", hybrid_big_small);
EVENT_ATTR_STR_HYBRID(mem-stores,    mem_st_adl,     "event=0xd0,umask=0x6;event=0xcd,umask=0x2",                 hybrid_big_small);
EVENT_ATTR_STR_HYBRID(mem-loads-aux, mem_ld_aux_adl, "event=0x03,umask=0x82",                                     hybrid_big);

अटल काष्ठा attribute *adl_hybrid_mem_attrs[] = अणु
	EVENT_PTR(mem_ld_adl),
	EVENT_PTR(mem_st_adl),
	EVENT_PTR(mem_ld_aux_adl),
	शून्य,
पूर्ण;

EVENT_ATTR_STR_HYBRID(tx-start,          tx_start_adl,          "event=0xc9,umask=0x1",          hybrid_big);
EVENT_ATTR_STR_HYBRID(tx-commit,         tx_commit_adl,         "event=0xc9,umask=0x2",          hybrid_big);
EVENT_ATTR_STR_HYBRID(tx-पात,          tx_पात_adl,          "event=0xc9,umask=0x4",          hybrid_big);
EVENT_ATTR_STR_HYBRID(tx-conflict,       tx_conflict_adl,       "event=0x54,umask=0x1",          hybrid_big);
EVENT_ATTR_STR_HYBRID(cycles-t,          cycles_t_adl,          "event=0x3c,in_tx=1",            hybrid_big);
EVENT_ATTR_STR_HYBRID(cycles-ct,         cycles_ct_adl,         "event=0x3c,in_tx=1,in_tx_cp=1", hybrid_big);
EVENT_ATTR_STR_HYBRID(tx-capacity-पढ़ो,  tx_capacity_पढ़ो_adl,  "event=0x54,umask=0x80",         hybrid_big);
EVENT_ATTR_STR_HYBRID(tx-capacity-ग_लिखो, tx_capacity_ग_लिखो_adl, "event=0x54,umask=0x2",          hybrid_big);

अटल काष्ठा attribute *adl_hybrid_tsx_attrs[] = अणु
	EVENT_PTR(tx_start_adl),
	EVENT_PTR(tx_पात_adl),
	EVENT_PTR(tx_commit_adl),
	EVENT_PTR(tx_capacity_पढ़ो_adl),
	EVENT_PTR(tx_capacity_ग_लिखो_adl),
	EVENT_PTR(tx_conflict_adl),
	EVENT_PTR(cycles_t_adl),
	EVENT_PTR(cycles_ct_adl),
	शून्य,
पूर्ण;

FORMAT_ATTR_HYBRID(in_tx,       hybrid_big);
FORMAT_ATTR_HYBRID(in_tx_cp,    hybrid_big);
FORMAT_ATTR_HYBRID(offcore_rsp, hybrid_big_small);
FORMAT_ATTR_HYBRID(ldlat,       hybrid_big_small);
FORMAT_ATTR_HYBRID(frontend,    hybrid_big);

अटल काष्ठा attribute *adl_hybrid_extra_attr_rपंचांग[] = अणु
	FORMAT_HYBRID_PTR(in_tx),
	FORMAT_HYBRID_PTR(in_tx_cp),
	FORMAT_HYBRID_PTR(offcore_rsp),
	FORMAT_HYBRID_PTR(ldlat),
	FORMAT_HYBRID_PTR(frontend),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *adl_hybrid_extra_attr[] = अणु
	FORMAT_HYBRID_PTR(offcore_rsp),
	FORMAT_HYBRID_PTR(ldlat),
	FORMAT_HYBRID_PTR(frontend),
	शून्य,
पूर्ण;

अटल bool is_attr_क्रम_this_pmu(काष्ठा kobject *kobj, काष्ठा attribute *attr)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा x86_hybrid_pmu *pmu =
		container_of(dev_get_drvdata(dev), काष्ठा x86_hybrid_pmu, pmu);
	काष्ठा perf_pmu_events_hybrid_attr *pmu_attr =
		container_of(attr, काष्ठा perf_pmu_events_hybrid_attr, attr.attr);

	वापस pmu->cpu_type & pmu_attr->pmu_type;
पूर्ण

अटल umode_t hybrid_events_is_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक i)
अणु
	वापस is_attr_क्रम_this_pmu(kobj, attr) ? attr->mode : 0;
पूर्ण

अटल अंतरभूत पूर्णांक hybrid_find_supported_cpu(काष्ठा x86_hybrid_pmu *pmu)
अणु
	पूर्णांक cpu = cpumask_first(&pmu->supported_cpus);

	वापस (cpu >= nr_cpu_ids) ? -1 : cpu;
पूर्ण

अटल umode_t hybrid_tsx_is_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा x86_hybrid_pmu *pmu =
		 container_of(dev_get_drvdata(dev), काष्ठा x86_hybrid_pmu, pmu);
	पूर्णांक cpu = hybrid_find_supported_cpu(pmu);

	वापस (cpu >= 0) && is_attr_क्रम_this_pmu(kobj, attr) && cpu_has(&cpu_data(cpu), X86_FEATURE_RTM) ? attr->mode : 0;
पूर्ण

अटल umode_t hybrid_क्रमmat_is_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक i)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा x86_hybrid_pmu *pmu =
		container_of(dev_get_drvdata(dev), काष्ठा x86_hybrid_pmu, pmu);
	काष्ठा perf_pmu_क्रमmat_hybrid_attr *pmu_attr =
		container_of(attr, काष्ठा perf_pmu_क्रमmat_hybrid_attr, attr.attr);
	पूर्णांक cpu = hybrid_find_supported_cpu(pmu);

	वापस (cpu >= 0) && (pmu->cpu_type & pmu_attr->pmu_type) ? attr->mode : 0;
पूर्ण

अटल काष्ठा attribute_group hybrid_group_events_td  = अणु
	.name		= "events",
	.is_visible	= hybrid_events_is_visible,
पूर्ण;

अटल काष्ठा attribute_group hybrid_group_events_mem = अणु
	.name		= "events",
	.is_visible	= hybrid_events_is_visible,
पूर्ण;

अटल काष्ठा attribute_group hybrid_group_events_tsx = अणु
	.name		= "events",
	.is_visible	= hybrid_tsx_is_visible,
पूर्ण;

अटल काष्ठा attribute_group hybrid_group_क्रमmat_extra = अणु
	.name		= "format",
	.is_visible	= hybrid_क्रमmat_is_visible,
पूर्ण;

अटल sमाप_प्रकार पूर्णांकel_hybrid_get_attr_cpus(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा x86_hybrid_pmu *pmu =
		container_of(dev_get_drvdata(dev), काष्ठा x86_hybrid_pmu, pmu);

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &pmu->supported_cpus);
पूर्ण

अटल DEVICE_ATTR(cpus, S_IRUGO, पूर्णांकel_hybrid_get_attr_cpus, शून्य);
अटल काष्ठा attribute *पूर्णांकel_hybrid_cpus_attrs[] = अणु
	&dev_attr_cpus.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group hybrid_group_cpus = अणु
	.attrs		= पूर्णांकel_hybrid_cpus_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hybrid_attr_update[] = अणु
	&hybrid_group_events_td,
	&hybrid_group_events_mem,
	&hybrid_group_events_tsx,
	&group_caps_gen,
	&group_caps_lbr,
	&hybrid_group_क्रमmat_extra,
	&group_शेष,
	&hybrid_group_cpus,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *empty_attrs;

अटल व्योम पूर्णांकel_pmu_check_num_counters(पूर्णांक *num_counters,
					 पूर्णांक *num_counters_fixed,
					 u64 *पूर्णांकel_ctrl, u64 fixed_mask)
अणु
	अगर (*num_counters > INTEL_PMC_MAX_GENERIC) अणु
		WARN(1, KERN_ERR "hw perf events %d > max(%d), clipping!",
		     *num_counters, INTEL_PMC_MAX_GENERIC);
		*num_counters = INTEL_PMC_MAX_GENERIC;
	पूर्ण
	*पूर्णांकel_ctrl = (1ULL << *num_counters) - 1;

	अगर (*num_counters_fixed > INTEL_PMC_MAX_FIXED) अणु
		WARN(1, KERN_ERR "hw perf events fixed %d > max(%d), clipping!",
		     *num_counters_fixed, INTEL_PMC_MAX_FIXED);
		*num_counters_fixed = INTEL_PMC_MAX_FIXED;
	पूर्ण

	*पूर्णांकel_ctrl |= fixed_mask << INTEL_PMC_IDX_FIXED;
पूर्ण

अटल व्योम पूर्णांकel_pmu_check_event_स्थिरraपूर्णांकs(काष्ठा event_स्थिरraपूर्णांक *event_स्थिरraपूर्णांकs,
					      पूर्णांक num_counters,
					      पूर्णांक num_counters_fixed,
					      u64 पूर्णांकel_ctrl)
अणु
	काष्ठा event_स्थिरraपूर्णांक *c;

	अगर (!event_स्थिरraपूर्णांकs)
		वापस;

	/*
	 * event on fixed counter2 (REF_CYCLES) only works on this
	 * counter, so करो not extend mask to generic counters
	 */
	क्रम_each_event_स्थिरraपूर्णांक(c, event_स्थिरraपूर्णांकs) अणु
		/*
		 * Don't extend the topकरोwn slots and metrics
		 * events to the generic counters.
		 */
		अगर (c->idxmsk64 & INTEL_PMC_MSK_TOPDOWN) अणु
			/*
			 * Disable topकरोwn slots and metrics events,
			 * अगर slots event is not in CPUID.
			 */
			अगर (!(INTEL_PMC_MSK_FIXED_SLOTS & पूर्णांकel_ctrl))
				c->idxmsk64 = 0;
			c->weight = hweight64(c->idxmsk64);
			जारी;
		पूर्ण

		अगर (c->cmask == FIXED_EVENT_FLAGS) अणु
			/* Disabled fixed counters which are not in CPUID */
			c->idxmsk64 &= पूर्णांकel_ctrl;

			अगर (c->idxmsk64 != INTEL_PMC_MSK_FIXED_REF_CYCLES)
				c->idxmsk64 |= (1ULL << num_counters) - 1;
		पूर्ण
		c->idxmsk64 &=
			~(~0ULL << (INTEL_PMC_IDX_FIXED + num_counters_fixed));
		c->weight = hweight64(c->idxmsk64);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_check_extra_regs(काष्ठा extra_reg *extra_regs)
अणु
	काष्ठा extra_reg *er;

	/*
	 * Access extra MSR may cause #GP under certain circumstances.
	 * E.g. KVM करोesn't support offcore event
	 * Check all extra_regs here.
	 */
	अगर (!extra_regs)
		वापस;

	क्रम (er = extra_regs; er->msr; er++) अणु
		er->extra_msr_access = check_msr(er->msr, 0x11UL);
		/* Disable LBR select mapping */
		अगर ((er->idx == EXTRA_REG_LBR) && !er->extra_msr_access)
			x86_pmu.lbr_sel_map = शून्य;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_check_hybrid_pmus(u64 fixed_mask)
अणु
	काष्ठा x86_hybrid_pmu *pmu;
	पूर्णांक i;

	क्रम (i = 0; i < x86_pmu.num_hybrid_pmus; i++) अणु
		pmu = &x86_pmu.hybrid_pmu[i];

		पूर्णांकel_pmu_check_num_counters(&pmu->num_counters,
					     &pmu->num_counters_fixed,
					     &pmu->पूर्णांकel_ctrl,
					     fixed_mask);

		अगर (pmu->पूर्णांकel_cap.perf_metrics) अणु
			pmu->पूर्णांकel_ctrl |= 1ULL << GLOBAL_CTRL_EN_PERF_METRICS;
			pmu->पूर्णांकel_ctrl |= INTEL_PMC_MSK_FIXED_SLOTS;
		पूर्ण

		अगर (pmu->पूर्णांकel_cap.pebs_output_pt_available)
			pmu->pmu.capabilities |= PERF_PMU_CAP_AUX_OUTPUT;

		पूर्णांकel_pmu_check_event_स्थिरraपूर्णांकs(pmu->event_स्थिरraपूर्णांकs,
						  pmu->num_counters,
						  pmu->num_counters_fixed,
						  pmu->पूर्णांकel_ctrl);

		पूर्णांकel_pmu_check_extra_regs(pmu->extra_regs);
	पूर्ण
पूर्ण

__init पूर्णांक पूर्णांकel_pmu_init(व्योम)
अणु
	काष्ठा attribute **extra_skl_attr = &empty_attrs;
	काष्ठा attribute **extra_attr = &empty_attrs;
	काष्ठा attribute **td_attr    = &empty_attrs;
	काष्ठा attribute **mem_attr   = &empty_attrs;
	काष्ठा attribute **tsx_attr   = &empty_attrs;
	जोड़ cpuid10_edx edx;
	जोड़ cpuid10_eax eax;
	जोड़ cpuid10_ebx ebx;
	अचिन्हित पूर्णांक fixed_mask;
	bool pmem = false;
	पूर्णांक version, i;
	अक्षर *name;
	काष्ठा x86_hybrid_pmu *pmu;

	अगर (!cpu_has(&boot_cpu_data, X86_FEATURE_ARCH_PERFMON)) अणु
		चयन (boot_cpu_data.x86) अणु
		हाल 0x6:
			वापस p6_pmu_init();
		हाल 0xb:
			वापस knc_pmu_init();
		हाल 0xf:
			वापस p4_pmu_init();
		पूर्ण
		वापस -ENODEV;
	पूर्ण

	/*
	 * Check whether the Architectural PerfMon supports
	 * Branch Misses Retired hw_event or not.
	 */
	cpuid(10, &eax.full, &ebx.full, &fixed_mask, &edx.full);
	अगर (eax.split.mask_length < ARCH_PERFMON_EVENTS_COUNT)
		वापस -ENODEV;

	version = eax.split.version_id;
	अगर (version < 2)
		x86_pmu = core_pmu;
	अन्यथा
		x86_pmu = पूर्णांकel_pmu;

	x86_pmu.version			= version;
	x86_pmu.num_counters		= eax.split.num_counters;
	x86_pmu.cntval_bits		= eax.split.bit_width;
	x86_pmu.cntval_mask		= (1ULL << eax.split.bit_width) - 1;

	x86_pmu.events_maskl		= ebx.full;
	x86_pmu.events_mask_len		= eax.split.mask_length;

	x86_pmu.max_pebs_events		= min_t(अचिन्हित, MAX_PEBS_EVENTS, x86_pmu.num_counters);

	/*
	 * Quirk: v2 perfmon करोes not report fixed-purpose events, so
	 * assume at least 3 events, when not running in a hypervisor:
	 */
	अगर (version > 1 && version < 5) अणु
		पूर्णांक assume = 3 * !boot_cpu_has(X86_FEATURE_HYPERVISOR);

		x86_pmu.num_counters_fixed =
			max((पूर्णांक)edx.split.num_counters_fixed, assume);

		fixed_mask = (1L << x86_pmu.num_counters_fixed) - 1;
	पूर्ण अन्यथा अगर (version >= 5)
		x86_pmu.num_counters_fixed = fls(fixed_mask);

	अगर (boot_cpu_has(X86_FEATURE_PDCM)) अणु
		u64 capabilities;

		rdmsrl(MSR_IA32_PERF_CAPABILITIES, capabilities);
		x86_pmu.पूर्णांकel_cap.capabilities = capabilities;
	पूर्ण

	अगर (x86_pmu.पूर्णांकel_cap.lbr_क्रमmat == LBR_FORMAT_32) अणु
		x86_pmu.lbr_reset = पूर्णांकel_pmu_lbr_reset_32;
		x86_pmu.lbr_पढ़ो = पूर्णांकel_pmu_lbr_पढ़ो_32;
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_ARCH_LBR))
		पूर्णांकel_pmu_arch_lbr_init();

	पूर्णांकel_ds_init();

	x86_add_quirk(पूर्णांकel_arch_events_quirk); /* Install first, so it runs last */

	अगर (version >= 5) अणु
		x86_pmu.पूर्णांकel_cap.anythपढ़ो_deprecated = edx.split.anythपढ़ो_deprecated;
		अगर (x86_pmu.पूर्णांकel_cap.anythपढ़ो_deprecated)
			pr_cont(" AnyThread deprecated, ");
	पूर्ण

	/*
	 * Install the hw-cache-events table:
	 */
	चयन (boot_cpu_data.x86_model) अणु
	हाल INTEL_FAM6_CORE_YONAH:
		pr_cont("Core events, ");
		name = "core";
		अवरोध;

	हाल INTEL_FAM6_CORE2_MEROM:
		x86_add_quirk(पूर्णांकel_clovertown_quirk);
		fallthrough;

	हाल INTEL_FAM6_CORE2_MEROM_L:
	हाल INTEL_FAM6_CORE2_PENRYN:
	हाल INTEL_FAM6_CORE2_DUNNINGTON:
		स_नकल(hw_cache_event_ids, core2_hw_cache_event_ids,
		       माप(hw_cache_event_ids));

		पूर्णांकel_pmu_lbr_init_core();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_core2_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_core2_pebs_event_स्थिरraपूर्णांकs;
		pr_cont("Core2 events, ");
		name = "core2";
		अवरोध;

	हाल INTEL_FAM6_NEHALEM:
	हाल INTEL_FAM6_NEHALEM_EP:
	हाल INTEL_FAM6_NEHALEM_EX:
		स_नकल(hw_cache_event_ids, nehalem_hw_cache_event_ids,
		       माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, nehalem_hw_cache_extra_regs,
		       माप(hw_cache_extra_regs));

		पूर्णांकel_pmu_lbr_init_nhm();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_nehalem_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_nehalem_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.enable_all = पूर्णांकel_pmu_nhm_enable_all;
		x86_pmu.extra_regs = पूर्णांकel_nehalem_extra_regs;
		x86_pmu.limit_period = nhm_limit_period;

		mem_attr = nhm_mem_events_attrs;

		/* UOPS_ISSUED.STALLED_CYCLES */
		पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] =
			X86_CONFIG(.event=0x0e, .umask=0x01, .inv=1, .cmask=1);
		/* UOPS_EXECUTED.CORE_ACTIVE_CYCLES,c=1,i=1 */
		पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] =
			X86_CONFIG(.event=0xb1, .umask=0x3f, .inv=1, .cmask=1);

		पूर्णांकel_pmu_pebs_data_source_nhm();
		x86_add_quirk(पूर्णांकel_nehalem_quirk);
		x86_pmu.pebs_no_tlb = 1;
		extra_attr = nhm_क्रमmat_attr;

		pr_cont("Nehalem events, ");
		name = "nehalem";
		अवरोध;

	हाल INTEL_FAM6_ATOM_BONNELL:
	हाल INTEL_FAM6_ATOM_BONNELL_MID:
	हाल INTEL_FAM6_ATOM_SALTWELL:
	हाल INTEL_FAM6_ATOM_SALTWELL_MID:
	हाल INTEL_FAM6_ATOM_SALTWELL_TABLET:
		स_नकल(hw_cache_event_ids, atom_hw_cache_event_ids,
		       माप(hw_cache_event_ids));

		पूर्णांकel_pmu_lbr_init_atom();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_gen_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_atom_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_aliases = पूर्णांकel_pebs_aliases_core2;
		pr_cont("Atom events, ");
		name = "bonnell";
		अवरोध;

	हाल INTEL_FAM6_ATOM_SILVERMONT:
	हाल INTEL_FAM6_ATOM_SILVERMONT_D:
	हाल INTEL_FAM6_ATOM_SILVERMONT_MID:
	हाल INTEL_FAM6_ATOM_AIRMONT:
	हाल INTEL_FAM6_ATOM_AIRMONT_MID:
		स_नकल(hw_cache_event_ids, slm_hw_cache_event_ids,
			माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, slm_hw_cache_extra_regs,
		       माप(hw_cache_extra_regs));

		पूर्णांकel_pmu_lbr_init_slm();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_slm_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_slm_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_slm_extra_regs;
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		td_attr = slm_events_attrs;
		extra_attr = slm_क्रमmat_attr;
		pr_cont("Silvermont events, ");
		name = "silvermont";
		अवरोध;

	हाल INTEL_FAM6_ATOM_GOLDMONT:
	हाल INTEL_FAM6_ATOM_GOLDMONT_D:
		स_नकल(hw_cache_event_ids, glm_hw_cache_event_ids,
		       माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, glm_hw_cache_extra_regs,
		       माप(hw_cache_extra_regs));

		पूर्णांकel_pmu_lbr_init_skl();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_slm_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_glm_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_glm_extra_regs;
		/*
		 * It's recommended to use CPU_CLK_UNHALTED.CORE_P + NPEBS
		 * क्रम precise cycles.
		 * :pp is identical to :ppp
		 */
		x86_pmu.pebs_aliases = शून्य;
		x86_pmu.pebs_prec_dist = true;
		x86_pmu.lbr_pt_coexist = true;
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		td_attr = glm_events_attrs;
		extra_attr = slm_क्रमmat_attr;
		pr_cont("Goldmont events, ");
		name = "goldmont";
		अवरोध;

	हाल INTEL_FAM6_ATOM_GOLDMONT_PLUS:
		स_नकल(hw_cache_event_ids, glp_hw_cache_event_ids,
		       माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, glp_hw_cache_extra_regs,
		       माप(hw_cache_extra_regs));

		पूर्णांकel_pmu_lbr_init_skl();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_slm_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_glm_extra_regs;
		/*
		 * It's recommended to use CPU_CLK_UNHALTED.CORE_P + NPEBS
		 * क्रम precise cycles.
		 */
		x86_pmu.pebs_aliases = शून्य;
		x86_pmu.pebs_prec_dist = true;
		x86_pmu.lbr_pt_coexist = true;
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_PEBS_ALL;
		x86_pmu.get_event_स्थिरraपूर्णांकs = glp_get_event_स्थिरraपूर्णांकs;
		td_attr = glm_events_attrs;
		/* Goldmont Plus has 4-wide pipeline */
		event_attr_td_total_slots_scale_glm.event_str = "4";
		extra_attr = slm_क्रमmat_attr;
		pr_cont("Goldmont plus events, ");
		name = "goldmont_plus";
		अवरोध;

	हाल INTEL_FAM6_ATOM_TREMONT_D:
	हाल INTEL_FAM6_ATOM_TREMONT:
	हाल INTEL_FAM6_ATOM_TREMONT_L:
		x86_pmu.late_ack = true;
		स_नकल(hw_cache_event_ids, glp_hw_cache_event_ids,
		       माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, tnt_hw_cache_extra_regs,
		       माप(hw_cache_extra_regs));
		hw_cache_event_ids[C(ITLB)][C(OP_READ)][C(RESULT_ACCESS)] = -1;

		पूर्णांकel_pmu_lbr_init_skl();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_slm_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_tnt_extra_regs;
		/*
		 * It's recommended to use CPU_CLK_UNHALTED.CORE_P + NPEBS
		 * क्रम precise cycles.
		 */
		x86_pmu.pebs_aliases = शून्य;
		x86_pmu.pebs_prec_dist = true;
		x86_pmu.lbr_pt_coexist = true;
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.get_event_स्थिरraपूर्णांकs = tnt_get_event_स्थिरraपूर्णांकs;
		td_attr = tnt_events_attrs;
		extra_attr = slm_क्रमmat_attr;
		pr_cont("Tremont events, ");
		name = "Tremont";
		अवरोध;

	हाल INTEL_FAM6_WESTMERE:
	हाल INTEL_FAM6_WESTMERE_EP:
	हाल INTEL_FAM6_WESTMERE_EX:
		स_नकल(hw_cache_event_ids, wesपंचांगere_hw_cache_event_ids,
		       माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, nehalem_hw_cache_extra_regs,
		       माप(hw_cache_extra_regs));

		पूर्णांकel_pmu_lbr_init_nhm();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_wesपंचांगere_event_स्थिरraपूर्णांकs;
		x86_pmu.enable_all = पूर्णांकel_pmu_nhm_enable_all;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_wesपंचांगere_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_wesपंचांगere_extra_regs;
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;

		mem_attr = nhm_mem_events_attrs;

		/* UOPS_ISSUED.STALLED_CYCLES */
		पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] =
			X86_CONFIG(.event=0x0e, .umask=0x01, .inv=1, .cmask=1);
		/* UOPS_EXECUTED.CORE_ACTIVE_CYCLES,c=1,i=1 */
		पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] =
			X86_CONFIG(.event=0xb1, .umask=0x3f, .inv=1, .cmask=1);

		पूर्णांकel_pmu_pebs_data_source_nhm();
		extra_attr = nhm_क्रमmat_attr;
		pr_cont("Westmere events, ");
		name = "westmere";
		अवरोध;

	हाल INTEL_FAM6_SANDYBRIDGE:
	हाल INTEL_FAM6_SANDYBRIDGE_X:
		x86_add_quirk(पूर्णांकel_sandybridge_quirk);
		x86_add_quirk(पूर्णांकel_ht_bug);
		स_नकल(hw_cache_event_ids, snb_hw_cache_event_ids,
		       माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, snb_hw_cache_extra_regs,
		       माप(hw_cache_extra_regs));

		पूर्णांकel_pmu_lbr_init_snb();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_snb_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_snb_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_aliases = पूर्णांकel_pebs_aliases_snb;
		अगर (boot_cpu_data.x86_model == INTEL_FAM6_SANDYBRIDGE_X)
			x86_pmu.extra_regs = पूर्णांकel_snbep_extra_regs;
		अन्यथा
			x86_pmu.extra_regs = पूर्णांकel_snb_extra_regs;


		/* all extra regs are per-cpu when HT is on */
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;

		td_attr  = snb_events_attrs;
		mem_attr = snb_mem_events_attrs;

		/* UOPS_ISSUED.ANY,c=1,i=1 to count stall cycles */
		पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] =
			X86_CONFIG(.event=0x0e, .umask=0x01, .inv=1, .cmask=1);
		/* UOPS_DISPATCHED.THREAD,c=1,i=1 to count stall cycles*/
		पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] =
			X86_CONFIG(.event=0xb1, .umask=0x01, .inv=1, .cmask=1);

		extra_attr = nhm_क्रमmat_attr;

		pr_cont("SandyBridge events, ");
		name = "sandybridge";
		अवरोध;

	हाल INTEL_FAM6_IVYBRIDGE:
	हाल INTEL_FAM6_IVYBRIDGE_X:
		x86_add_quirk(पूर्णांकel_ht_bug);
		स_नकल(hw_cache_event_ids, snb_hw_cache_event_ids,
		       माप(hw_cache_event_ids));
		/* dTLB-load-misses on IVB is dअगरferent than SNB */
		hw_cache_event_ids[C(DTLB)][C(OP_READ)][C(RESULT_MISS)] = 0x8108; /* DTLB_LOAD_MISSES.DEMAND_LD_MISS_CAUSES_A_WALK */

		स_नकल(hw_cache_extra_regs, snb_hw_cache_extra_regs,
		       माप(hw_cache_extra_regs));

		पूर्णांकel_pmu_lbr_init_snb();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_ivb_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_ivb_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_aliases = पूर्णांकel_pebs_aliases_ivb;
		x86_pmu.pebs_prec_dist = true;
		अगर (boot_cpu_data.x86_model == INTEL_FAM6_IVYBRIDGE_X)
			x86_pmu.extra_regs = पूर्णांकel_snbep_extra_regs;
		अन्यथा
			x86_pmu.extra_regs = पूर्णांकel_snb_extra_regs;
		/* all extra regs are per-cpu when HT is on */
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;

		td_attr  = snb_events_attrs;
		mem_attr = snb_mem_events_attrs;

		/* UOPS_ISSUED.ANY,c=1,i=1 to count stall cycles */
		पूर्णांकel_perfmon_event_map[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] =
			X86_CONFIG(.event=0x0e, .umask=0x01, .inv=1, .cmask=1);

		extra_attr = nhm_क्रमmat_attr;

		pr_cont("IvyBridge events, ");
		name = "ivybridge";
		अवरोध;


	हाल INTEL_FAM6_HASWELL:
	हाल INTEL_FAM6_HASWELL_X:
	हाल INTEL_FAM6_HASWELL_L:
	हाल INTEL_FAM6_HASWELL_G:
		x86_add_quirk(पूर्णांकel_ht_bug);
		x86_add_quirk(पूर्णांकel_pebs_isolation_quirk);
		x86_pmu.late_ack = true;
		स_नकल(hw_cache_event_ids, hsw_hw_cache_event_ids, माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, hsw_hw_cache_extra_regs, माप(hw_cache_extra_regs));

		पूर्णांकel_pmu_lbr_init_hsw();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_hsw_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_hsw_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_snbep_extra_regs;
		x86_pmu.pebs_aliases = पूर्णांकel_pebs_aliases_ivb;
		x86_pmu.pebs_prec_dist = true;
		/* all extra regs are per-cpu when HT is on */
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;

		x86_pmu.hw_config = hsw_hw_config;
		x86_pmu.get_event_स्थिरraपूर्णांकs = hsw_get_event_स्थिरraपूर्णांकs;
		x86_pmu.lbr_द्विगुन_पात = true;
		extra_attr = boot_cpu_has(X86_FEATURE_RTM) ?
			hsw_क्रमmat_attr : nhm_क्रमmat_attr;
		td_attr  = hsw_events_attrs;
		mem_attr = hsw_mem_events_attrs;
		tsx_attr = hsw_tsx_events_attrs;
		pr_cont("Haswell events, ");
		name = "haswell";
		अवरोध;

	हाल INTEL_FAM6_BROADWELL:
	हाल INTEL_FAM6_BROADWELL_D:
	हाल INTEL_FAM6_BROADWELL_G:
	हाल INTEL_FAM6_BROADWELL_X:
		x86_add_quirk(पूर्णांकel_pebs_isolation_quirk);
		x86_pmu.late_ack = true;
		स_नकल(hw_cache_event_ids, hsw_hw_cache_event_ids, माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, hsw_hw_cache_extra_regs, माप(hw_cache_extra_regs));

		/* L3_MISS_LOCAL_DRAM is BIT(26) in Broadwell */
		hw_cache_extra_regs[C(LL)][C(OP_READ)][C(RESULT_MISS)] = HSW_DEMAND_READ |
									 BDW_L3_MISS|HSW_SNOOP_DRAM;
		hw_cache_extra_regs[C(LL)][C(OP_WRITE)][C(RESULT_MISS)] = HSW_DEMAND_WRITE|BDW_L3_MISS|
									  HSW_SNOOP_DRAM;
		hw_cache_extra_regs[C(NODE)][C(OP_READ)][C(RESULT_ACCESS)] = HSW_DEMAND_READ|
									     BDW_L3_MISS_LOCAL|HSW_SNOOP_DRAM;
		hw_cache_extra_regs[C(NODE)][C(OP_WRITE)][C(RESULT_ACCESS)] = HSW_DEMAND_WRITE|
									      BDW_L3_MISS_LOCAL|HSW_SNOOP_DRAM;

		पूर्णांकel_pmu_lbr_init_hsw();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_bdw_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_bdw_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_snbep_extra_regs;
		x86_pmu.pebs_aliases = पूर्णांकel_pebs_aliases_ivb;
		x86_pmu.pebs_prec_dist = true;
		/* all extra regs are per-cpu when HT is on */
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;

		x86_pmu.hw_config = hsw_hw_config;
		x86_pmu.get_event_स्थिरraपूर्णांकs = hsw_get_event_स्थिरraपूर्णांकs;
		x86_pmu.limit_period = bdw_limit_period;
		extra_attr = boot_cpu_has(X86_FEATURE_RTM) ?
			hsw_क्रमmat_attr : nhm_क्रमmat_attr;
		td_attr  = hsw_events_attrs;
		mem_attr = hsw_mem_events_attrs;
		tsx_attr = hsw_tsx_events_attrs;
		pr_cont("Broadwell events, ");
		name = "broadwell";
		अवरोध;

	हाल INTEL_FAM6_XEON_PHI_KNL:
	हाल INTEL_FAM6_XEON_PHI_KNM:
		स_नकल(hw_cache_event_ids,
		       slm_hw_cache_event_ids, माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs,
		       knl_hw_cache_extra_regs, माप(hw_cache_extra_regs));
		पूर्णांकel_pmu_lbr_init_knl();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_slm_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_slm_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_knl_extra_regs;

		/* all extra regs are per-cpu when HT is on */
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;
		extra_attr = slm_क्रमmat_attr;
		pr_cont("Knights Landing/Mill events, ");
		name = "knights-landing";
		अवरोध;

	हाल INTEL_FAM6_SKYLAKE_X:
		pmem = true;
		fallthrough;
	हाल INTEL_FAM6_SKYLAKE_L:
	हाल INTEL_FAM6_SKYLAKE:
	हाल INTEL_FAM6_KABYLAKE_L:
	हाल INTEL_FAM6_KABYLAKE:
	हाल INTEL_FAM6_COMETLAKE_L:
	हाल INTEL_FAM6_COMETLAKE:
		x86_add_quirk(पूर्णांकel_pebs_isolation_quirk);
		x86_pmu.late_ack = true;
		स_नकल(hw_cache_event_ids, skl_hw_cache_event_ids, माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, skl_hw_cache_extra_regs, माप(hw_cache_extra_regs));
		पूर्णांकel_pmu_lbr_init_skl();

		/* INT_MISC.RECOVERY_CYCLES has umask 1 in Skylake */
		event_attr_td_recovery_bubbles.event_str_noht =
			"event=0xd,umask=0x1,cmask=1";
		event_attr_td_recovery_bubbles.event_str_ht =
			"event=0xd,umask=0x1,cmask=1,any=1";

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_skl_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_skl_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_skl_extra_regs;
		x86_pmu.pebs_aliases = पूर्णांकel_pebs_aliases_skl;
		x86_pmu.pebs_prec_dist = true;
		/* all extra regs are per-cpu when HT is on */
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;

		x86_pmu.hw_config = hsw_hw_config;
		x86_pmu.get_event_स्थिरraपूर्णांकs = hsw_get_event_स्थिरraपूर्णांकs;
		extra_attr = boot_cpu_has(X86_FEATURE_RTM) ?
			hsw_क्रमmat_attr : nhm_क्रमmat_attr;
		extra_skl_attr = skl_क्रमmat_attr;
		td_attr  = hsw_events_attrs;
		mem_attr = hsw_mem_events_attrs;
		tsx_attr = hsw_tsx_events_attrs;
		पूर्णांकel_pmu_pebs_data_source_skl(pmem);

		अगर (boot_cpu_has(X86_FEATURE_TSX_FORCE_ABORT)) अणु
			x86_pmu.flags |= PMU_FL_TFA;
			x86_pmu.get_event_स्थिरraपूर्णांकs = tfa_get_event_स्थिरraपूर्णांकs;
			x86_pmu.enable_all = पूर्णांकel_tfa_pmu_enable_all;
			x86_pmu.commit_scheduling = पूर्णांकel_tfa_commit_scheduling;
		पूर्ण

		pr_cont("Skylake events, ");
		name = "skylake";
		अवरोध;

	हाल INTEL_FAM6_ICELAKE_X:
	हाल INTEL_FAM6_ICELAKE_D:
		pmem = true;
		fallthrough;
	हाल INTEL_FAM6_ICELAKE_L:
	हाल INTEL_FAM6_ICELAKE:
	हाल INTEL_FAM6_TIGERLAKE_L:
	हाल INTEL_FAM6_TIGERLAKE:
	हाल INTEL_FAM6_ROCKETLAKE:
		x86_pmu.late_ack = true;
		स_नकल(hw_cache_event_ids, skl_hw_cache_event_ids, माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, skl_hw_cache_extra_regs, माप(hw_cache_extra_regs));
		hw_cache_event_ids[C(ITLB)][C(OP_READ)][C(RESULT_ACCESS)] = -1;
		पूर्णांकel_pmu_lbr_init_skl();

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_icl_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_icl_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_icl_extra_regs;
		x86_pmu.pebs_aliases = शून्य;
		x86_pmu.pebs_prec_dist = true;
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;

		x86_pmu.hw_config = hsw_hw_config;
		x86_pmu.get_event_स्थिरraपूर्णांकs = icl_get_event_स्थिरraपूर्णांकs;
		extra_attr = boot_cpu_has(X86_FEATURE_RTM) ?
			hsw_क्रमmat_attr : nhm_क्रमmat_attr;
		extra_skl_attr = skl_क्रमmat_attr;
		mem_attr = icl_events_attrs;
		td_attr = icl_td_events_attrs;
		tsx_attr = icl_tsx_events_attrs;
		x86_pmu.rपंचांग_पात_event = X86_CONFIG(.event=0xc9, .umask=0x04);
		x86_pmu.lbr_pt_coexist = true;
		पूर्णांकel_pmu_pebs_data_source_skl(pmem);
		x86_pmu.num_topकरोwn_events = 4;
		x86_pmu.update_topकरोwn_event = icl_update_topकरोwn_event;
		x86_pmu.set_topकरोwn_event_period = icl_set_topकरोwn_event_period;
		pr_cont("Icelake events, ");
		name = "icelake";
		अवरोध;

	हाल INTEL_FAM6_SAPPHIRERAPIDS_X:
		pmem = true;
		x86_pmu.late_ack = true;
		स_नकल(hw_cache_event_ids, spr_hw_cache_event_ids, माप(hw_cache_event_ids));
		स_नकल(hw_cache_extra_regs, spr_hw_cache_extra_regs, माप(hw_cache_extra_regs));

		x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_spr_event_स्थिरraपूर्णांकs;
		x86_pmu.pebs_स्थिरraपूर्णांकs = पूर्णांकel_spr_pebs_event_स्थिरraपूर्णांकs;
		x86_pmu.extra_regs = पूर्णांकel_spr_extra_regs;
		x86_pmu.limit_period = spr_limit_period;
		x86_pmu.pebs_aliases = शून्य;
		x86_pmu.pebs_prec_dist = true;
		x86_pmu.pebs_block = true;
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;
		x86_pmu.flags |= PMU_FL_PEBS_ALL;
		x86_pmu.flags |= PMU_FL_INSTR_LATENCY;
		x86_pmu.flags |= PMU_FL_MEM_LOADS_AUX;

		x86_pmu.hw_config = hsw_hw_config;
		x86_pmu.get_event_स्थिरraपूर्णांकs = spr_get_event_स्थिरraपूर्णांकs;
		extra_attr = boot_cpu_has(X86_FEATURE_RTM) ?
			hsw_क्रमmat_attr : nhm_क्रमmat_attr;
		extra_skl_attr = skl_क्रमmat_attr;
		mem_attr = spr_events_attrs;
		td_attr = spr_td_events_attrs;
		tsx_attr = spr_tsx_events_attrs;
		x86_pmu.rपंचांग_पात_event = X86_CONFIG(.event=0xc9, .umask=0x04);
		x86_pmu.lbr_pt_coexist = true;
		पूर्णांकel_pmu_pebs_data_source_skl(pmem);
		x86_pmu.num_topकरोwn_events = 8;
		x86_pmu.update_topकरोwn_event = icl_update_topकरोwn_event;
		x86_pmu.set_topकरोwn_event_period = icl_set_topकरोwn_event_period;
		pr_cont("Sapphire Rapids events, ");
		name = "sapphire_rapids";
		अवरोध;

	हाल INTEL_FAM6_ALDERLAKE:
	हाल INTEL_FAM6_ALDERLAKE_L:
		/*
		 * Alder Lake has 2 types of CPU, core and atom.
		 *
		 * Initialize the common PerfMon capabilities here.
		 */
		x86_pmu.hybrid_pmu = kसुस्मृति(X86_HYBRID_NUM_PMUS,
					     माप(काष्ठा x86_hybrid_pmu),
					     GFP_KERNEL);
		अगर (!x86_pmu.hybrid_pmu)
			वापस -ENOMEM;
		अटल_branch_enable(&perf_is_hybrid);
		x86_pmu.num_hybrid_pmus = X86_HYBRID_NUM_PMUS;

		x86_pmu.late_ack = true;
		x86_pmu.pebs_aliases = शून्य;
		x86_pmu.pebs_prec_dist = true;
		x86_pmu.pebs_block = true;
		x86_pmu.flags |= PMU_FL_HAS_RSP_1;
		x86_pmu.flags |= PMU_FL_NO_HT_SHARING;
		x86_pmu.flags |= PMU_FL_PEBS_ALL;
		x86_pmu.flags |= PMU_FL_INSTR_LATENCY;
		x86_pmu.flags |= PMU_FL_MEM_LOADS_AUX;
		x86_pmu.lbr_pt_coexist = true;
		पूर्णांकel_pmu_pebs_data_source_skl(false);
		x86_pmu.num_topकरोwn_events = 8;
		x86_pmu.update_topकरोwn_event = adl_update_topकरोwn_event;
		x86_pmu.set_topकरोwn_event_period = adl_set_topकरोwn_event_period;

		x86_pmu.filter_match = पूर्णांकel_pmu_filter_match;
		x86_pmu.get_event_स्थिरraपूर्णांकs = adl_get_event_स्थिरraपूर्णांकs;
		x86_pmu.hw_config = adl_hw_config;
		x86_pmu.limit_period = spr_limit_period;
		x86_pmu.get_hybrid_cpu_type = adl_get_hybrid_cpu_type;
		/*
		 * The rपंचांग_पात_event is used to check whether to enable GPRs
		 * क्रम the RTM पात event. Atom करोesn't have the RTM पात
		 * event. There is no harmful to set it in the common
		 * x86_pmu.rपंचांग_पात_event.
		 */
		x86_pmu.rपंचांग_पात_event = X86_CONFIG(.event=0xc9, .umask=0x04);

		td_attr = adl_hybrid_events_attrs;
		mem_attr = adl_hybrid_mem_attrs;
		tsx_attr = adl_hybrid_tsx_attrs;
		extra_attr = boot_cpu_has(X86_FEATURE_RTM) ?
			adl_hybrid_extra_attr_rपंचांग : adl_hybrid_extra_attr;

		/* Initialize big core specअगरic PerfMon capabilities.*/
		pmu = &x86_pmu.hybrid_pmu[X86_HYBRID_PMU_CORE_IDX];
		pmu->name = "cpu_core";
		pmu->cpu_type = hybrid_big;
		pmu->num_counters = x86_pmu.num_counters + 2;
		pmu->num_counters_fixed = x86_pmu.num_counters_fixed + 1;
		pmu->max_pebs_events = min_t(अचिन्हित, MAX_PEBS_EVENTS, pmu->num_counters);
		pmu->unस्थिरrained = (काष्ठा event_स्थिरraपूर्णांक)
					__EVENT_CONSTRAINT(0, (1ULL << pmu->num_counters) - 1,
							   0, pmu->num_counters, 0, 0);
		pmu->पूर्णांकel_cap.capabilities = x86_pmu.पूर्णांकel_cap.capabilities;
		pmu->पूर्णांकel_cap.perf_metrics = 1;
		pmu->पूर्णांकel_cap.pebs_output_pt_available = 0;

		स_नकल(pmu->hw_cache_event_ids, spr_hw_cache_event_ids, माप(pmu->hw_cache_event_ids));
		स_नकल(pmu->hw_cache_extra_regs, spr_hw_cache_extra_regs, माप(pmu->hw_cache_extra_regs));
		pmu->event_स्थिरraपूर्णांकs = पूर्णांकel_spr_event_स्थिरraपूर्णांकs;
		pmu->pebs_स्थिरraपूर्णांकs = पूर्णांकel_spr_pebs_event_स्थिरraपूर्णांकs;
		pmu->extra_regs = पूर्णांकel_spr_extra_regs;

		/* Initialize Atom core specअगरic PerfMon capabilities.*/
		pmu = &x86_pmu.hybrid_pmu[X86_HYBRID_PMU_ATOM_IDX];
		pmu->name = "cpu_atom";
		pmu->cpu_type = hybrid_small;
		pmu->num_counters = x86_pmu.num_counters;
		pmu->num_counters_fixed = x86_pmu.num_counters_fixed;
		pmu->max_pebs_events = x86_pmu.max_pebs_events;
		pmu->unस्थिरrained = (काष्ठा event_स्थिरraपूर्णांक)
					__EVENT_CONSTRAINT(0, (1ULL << pmu->num_counters) - 1,
							   0, pmu->num_counters, 0, 0);
		pmu->पूर्णांकel_cap.capabilities = x86_pmu.पूर्णांकel_cap.capabilities;
		pmu->पूर्णांकel_cap.perf_metrics = 0;
		pmu->पूर्णांकel_cap.pebs_output_pt_available = 1;

		स_नकल(pmu->hw_cache_event_ids, glp_hw_cache_event_ids, माप(pmu->hw_cache_event_ids));
		स_नकल(pmu->hw_cache_extra_regs, tnt_hw_cache_extra_regs, माप(pmu->hw_cache_extra_regs));
		pmu->hw_cache_event_ids[C(ITLB)][C(OP_READ)][C(RESULT_ACCESS)] = -1;
		pmu->event_स्थिरraपूर्णांकs = पूर्णांकel_slm_event_स्थिरraपूर्णांकs;
		pmu->pebs_स्थिरraपूर्णांकs = पूर्णांकel_grt_pebs_event_स्थिरraपूर्णांकs;
		pmu->extra_regs = पूर्णांकel_grt_extra_regs;
		pr_cont("Alderlake Hybrid events, ");
		name = "alderlake_hybrid";
		अवरोध;

	शेष:
		चयन (x86_pmu.version) अणु
		हाल 1:
			x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_v1_event_स्थिरraपूर्णांकs;
			pr_cont("generic architected perfmon v1, ");
			name = "generic_arch_v1";
			अवरोध;
		शेष:
			/*
			 * शेष स्थिरraपूर्णांकs क्रम v2 and up
			 */
			x86_pmu.event_स्थिरraपूर्णांकs = पूर्णांकel_gen_event_स्थिरraपूर्णांकs;
			pr_cont("generic architected perfmon, ");
			name = "generic_arch_v2+";
			अवरोध;
		पूर्ण
	पूर्ण

	snम_लिखो(pmu_name_str, माप(pmu_name_str), "%s", name);

	अगर (!is_hybrid()) अणु
		group_events_td.attrs  = td_attr;
		group_events_mem.attrs = mem_attr;
		group_events_tsx.attrs = tsx_attr;
		group_क्रमmat_extra.attrs = extra_attr;
		group_क्रमmat_extra_skl.attrs = extra_skl_attr;

		x86_pmu.attr_update = attr_update;
	पूर्ण अन्यथा अणु
		hybrid_group_events_td.attrs  = td_attr;
		hybrid_group_events_mem.attrs = mem_attr;
		hybrid_group_events_tsx.attrs = tsx_attr;
		hybrid_group_क्रमmat_extra.attrs = extra_attr;

		x86_pmu.attr_update = hybrid_attr_update;
	पूर्ण

	पूर्णांकel_pmu_check_num_counters(&x86_pmu.num_counters,
				     &x86_pmu.num_counters_fixed,
				     &x86_pmu.पूर्णांकel_ctrl,
				     (u64)fixed_mask);

	/* AnyThपढ़ो may be deprecated on arch perfmon v5 or later */
	अगर (x86_pmu.पूर्णांकel_cap.anythपढ़ो_deprecated)
		x86_pmu.क्रमmat_attrs = पूर्णांकel_arch_क्रमmats_attr;

	पूर्णांकel_pmu_check_event_स्थिरraपूर्णांकs(x86_pmu.event_स्थिरraपूर्णांकs,
					  x86_pmu.num_counters,
					  x86_pmu.num_counters_fixed,
					  x86_pmu.पूर्णांकel_ctrl);
	/*
	 * Access LBR MSR may cause #GP under certain circumstances.
	 * E.g. KVM करोesn't support LBR MSR
	 * Check all LBT MSR here.
	 * Disable LBR access अगर any LBR MSRs can not be accessed.
	 */
	अगर (x86_pmu.lbr_tos && !check_msr(x86_pmu.lbr_tos, 0x3UL))
		x86_pmu.lbr_nr = 0;
	क्रम (i = 0; i < x86_pmu.lbr_nr; i++) अणु
		अगर (!(check_msr(x86_pmu.lbr_from + i, 0xffffUL) &&
		      check_msr(x86_pmu.lbr_to + i, 0xffffUL)))
			x86_pmu.lbr_nr = 0;
	पूर्ण

	अगर (x86_pmu.lbr_nr)
		pr_cont("%d-deep LBR, ", x86_pmu.lbr_nr);

	पूर्णांकel_pmu_check_extra_regs(x86_pmu.extra_regs);

	/* Support full width counters using alternative MSR range */
	अगर (x86_pmu.पूर्णांकel_cap.full_width_ग_लिखो) अणु
		x86_pmu.max_period = x86_pmu.cntval_mask >> 1;
		x86_pmu.perfctr = MSR_IA32_PMC0;
		pr_cont("full-width counters, ");
	पूर्ण

	अगर (!is_hybrid() && x86_pmu.पूर्णांकel_cap.perf_metrics)
		x86_pmu.पूर्णांकel_ctrl |= 1ULL << GLOBAL_CTRL_EN_PERF_METRICS;

	अगर (is_hybrid())
		पूर्णांकel_pmu_check_hybrid_pmus((u64)fixed_mask);

	वापस 0;
पूर्ण

/*
 * HT bug: phase 2 init
 * Called once we have valid topology inक्रमmation to check
 * whether or not HT is enabled
 * If HT is off, then we disable the workaround
 */
अटल __init पूर्णांक fixup_ht_bug(व्योम)
अणु
	पूर्णांक c;
	/*
	 * problem not present on this CPU model, nothing to करो
	 */
	अगर (!(x86_pmu.flags & PMU_FL_EXCL_ENABLED))
		वापस 0;

	अगर (topology_max_smt_thपढ़ोs() > 1) अणु
		pr_info("PMU erratum BJ122, BV98, HSD29 worked around, HT is on\n");
		वापस 0;
	पूर्ण

	cpus_पढ़ो_lock();

	hardlockup_detector_perf_stop();

	x86_pmu.flags &= ~(PMU_FL_EXCL_CNTRS | PMU_FL_EXCL_ENABLED);

	x86_pmu.start_scheduling = शून्य;
	x86_pmu.commit_scheduling = शून्य;
	x86_pmu.stop_scheduling = शून्य;

	hardlockup_detector_perf_restart();

	क्रम_each_online_cpu(c)
		मुक्त_excl_cntrs(&per_cpu(cpu_hw_events, c));

	cpus_पढ़ो_unlock();
	pr_info("PMU erratum BJ122, BV98, HSD29 workaround disabled, HT off\n");
	वापस 0;
पूर्ण
subsys_initcall(fixup_ht_bug)
