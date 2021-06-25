<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter support क्रम POWER10 processors.
 *
 * Copyright 2020 Madhavan Srinivasan, IBM Corporation.
 * Copyright 2020 Athira Rajeev, IBM Corporation.
 */

#घोषणा pr_fmt(fmt)	"power10-pmu: " fmt

#समावेश "isa207-common.h"

/*
 * Raw event encoding क्रम Power10:
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   | | [ ]   [ src_match ] [  src_mask ]   | [ ] [ l2l3_sel ]  [  thresh_ctl   ]
 *   | |  |                                  |  |                         |
 *   | |  *- IFM (Linux)                     |  |        thresh start/stop -*
 *   | *- BHRB (Linux)                       |  src_sel
 *   *- EBB (Linux)                          *invert_bit
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   [   ] [  sample ]   [ ] [ ]   [ pmc ]   [unit ]   [ ] |  m   [    pmcxsel    ]
 *     |        |        |    |                        |   |  |
 *     |        |        |    |                        |   |  *- mark
 *     |        |        |    *- L1/L2/L3 cache_sel    |   |*-radix_scope_qual
 *     |        |        sdar_mode                     |
 *     |        *- sampling mode क्रम marked events     *- combine
 *     |
 *     *- thresh_sel
 *
 * Below uses IBM bit numbering.
 *
 * MMCR1[x:y] = unit    (PMCxUNIT)
 * MMCR1[24]   = pmc1combine[0]
 * MMCR1[25]   = pmc1combine[1]
 * MMCR1[26]   = pmc2combine[0]
 * MMCR1[27]   = pmc2combine[1]
 * MMCR1[28]   = pmc3combine[0]
 * MMCR1[29]   = pmc3combine[1]
 * MMCR1[30]   = pmc4combine[0]
 * MMCR1[31]   = pmc4combine[1]
 *
 * अगर pmc == 3 and unit == 0 and pmcxsel[0:6] == 0b0101011
 *	MMCR1[20:27] = thresh_ctl
 * अन्यथा अगर pmc == 4 and unit == 0xf and pmcxsel[0:6] == 0b0101001
 *	MMCR1[20:27] = thresh_ctl
 * अन्यथा
 *	MMCRA[48:55] = thresh_ctl   (THRESH START/END)
 *
 * अगर thresh_sel:
 *	MMCRA[45:47] = thresh_sel
 *
 * अगर l2l3_sel:
 * MMCR2[56:60] = l2l3_sel[0:4]
 *
 * MMCR1[16] = cache_sel[0]
 * MMCR1[17] = cache_sel[1]
 * MMCR1[18] = radix_scope_qual
 *
 * अगर mark:
 *	MMCRA[63]    = 1		(SAMPLE_ENABLE)
 *	MMCRA[57:59] = sample[0:2]	(RAND_SAMP_ELIG)
 *	MMCRA[61:62] = sample[3:4]	(RAND_SAMP_MODE)
 *
 * अगर EBB and BHRB:
 *	MMCRA[32:33] = IFM
 *
 * MMCRA[SDAR_MODE]  = sdar_mode[0:1]
 */

/*
 * Some घातer10 event codes.
 */
#घोषणा EVENT(_name, _code)     क्रमागतअणु_name = _codeपूर्ण

#समावेश "power10-events-list.h"

#अघोषित EVENT

/* MMCRA IFM bits - POWER10 */
#घोषणा POWER10_MMCRA_IFM1		0x0000000040000000UL
#घोषणा POWER10_MMCRA_IFM2		0x0000000080000000UL
#घोषणा POWER10_MMCRA_IFM3		0x00000000C0000000UL
#घोषणा POWER10_MMCRA_BHRB_MASK		0x00000000C0000000UL

बाह्य u64 PERF_REG_EXTENDED_MASK;

/* Table of alternatives, sorted by column 0 */
अटल स्थिर अचिन्हित पूर्णांक घातer10_event_alternatives[][MAX_ALT] = अणु
	अणु PM_RUN_CYC_ALT,		PM_RUN_CYC पूर्ण,
	अणु PM_RUN_INST_CMPL_ALT,		PM_RUN_INST_CMPL पूर्ण,
पूर्ण;

अटल पूर्णांक घातer10_get_alternatives(u64 event, अचिन्हित पूर्णांक flags, u64 alt[])
अणु
	पूर्णांक num_alt = 0;

	num_alt = isa207_get_alternatives(event, alt,
					  ARRAY_SIZE(घातer10_event_alternatives), flags,
					  घातer10_event_alternatives);

	वापस num_alt;
पूर्ण

अटल पूर्णांक घातer10_check_attr_config(काष्ठा perf_event *ev)
अणु
	u64 val;
	u64 event = ev->attr.config;

	val = (event >> EVENT_SAMPLE_SHIFT) & EVENT_SAMPLE_MASK;
	अगर (val == 0x10 || isa3XX_check_attr_config(ev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

GENERIC_EVENT_ATTR(cpu-cycles,			PM_RUN_CYC);
GENERIC_EVENT_ATTR(inकाष्ठाions,		PM_RUN_INST_CMPL);
GENERIC_EVENT_ATTR(branch-inकाष्ठाions,		PM_BR_CMPL);
GENERIC_EVENT_ATTR(branch-misses,		PM_BR_MPRED_CMPL);
GENERIC_EVENT_ATTR(cache-references,		PM_LD_REF_L1);
GENERIC_EVENT_ATTR(cache-misses,		PM_LD_MISS_L1);
GENERIC_EVENT_ATTR(mem-loads,			MEM_LOADS);
GENERIC_EVENT_ATTR(mem-stores,			MEM_STORES);
GENERIC_EVENT_ATTR(branch-inकाष्ठाions,		PM_BR_FIN);
GENERIC_EVENT_ATTR(branch-misses,		PM_MPRED_BR_FIN);
GENERIC_EVENT_ATTR(cache-misses,		PM_LD_DEMAND_MISS_L1_FIN);

CACHE_EVENT_ATTR(L1-dcache-load-misses,		PM_LD_MISS_L1);
CACHE_EVENT_ATTR(L1-dcache-loads,		PM_LD_REF_L1);
CACHE_EVENT_ATTR(L1-dcache-prefetches,		PM_LD_PREFETCH_CACHE_LINE_MISS);
CACHE_EVENT_ATTR(L1-dcache-store-misses,	PM_ST_MISS_L1);
CACHE_EVENT_ATTR(L1-icache-load-misses,		PM_L1_ICACHE_MISS);
CACHE_EVENT_ATTR(L1-icache-loads,		PM_INST_FROM_L1);
CACHE_EVENT_ATTR(L1-icache-prefetches,		PM_IC_PREF_REQ);
CACHE_EVENT_ATTR(LLC-load-misses,		PM_DATA_FROM_L3MISS);
CACHE_EVENT_ATTR(LLC-loads,			PM_DATA_FROM_L3);
CACHE_EVENT_ATTR(LLC-prefetches,		PM_L3_PF_MISS_L3);
CACHE_EVENT_ATTR(LLC-store-misses,		PM_L2_ST_MISS);
CACHE_EVENT_ATTR(LLC-stores,			PM_L2_ST);
CACHE_EVENT_ATTR(branch-load-misses,		PM_BR_MPRED_CMPL);
CACHE_EVENT_ATTR(branch-loads,			PM_BR_CMPL);
CACHE_EVENT_ATTR(dTLB-load-misses,		PM_DTLB_MISS);
CACHE_EVENT_ATTR(iTLB-load-misses,		PM_ITLB_MISS);

अटल काष्ठा attribute *घातer10_events_attr_dd1[] = अणु
	GENERIC_EVENT_PTR(PM_RUN_CYC),
	GENERIC_EVENT_PTR(PM_RUN_INST_CMPL),
	GENERIC_EVENT_PTR(PM_BR_CMPL),
	GENERIC_EVENT_PTR(PM_BR_MPRED_CMPL),
	GENERIC_EVENT_PTR(PM_LD_REF_L1),
	GENERIC_EVENT_PTR(PM_LD_MISS_L1),
	GENERIC_EVENT_PTR(MEM_LOADS),
	GENERIC_EVENT_PTR(MEM_STORES),
	CACHE_EVENT_PTR(PM_LD_MISS_L1),
	CACHE_EVENT_PTR(PM_LD_REF_L1),
	CACHE_EVENT_PTR(PM_LD_PREFETCH_CACHE_LINE_MISS),
	CACHE_EVENT_PTR(PM_ST_MISS_L1),
	CACHE_EVENT_PTR(PM_L1_ICACHE_MISS),
	CACHE_EVENT_PTR(PM_INST_FROM_L1),
	CACHE_EVENT_PTR(PM_IC_PREF_REQ),
	CACHE_EVENT_PTR(PM_DATA_FROM_L3MISS),
	CACHE_EVENT_PTR(PM_DATA_FROM_L3),
	CACHE_EVENT_PTR(PM_BR_MPRED_CMPL),
	CACHE_EVENT_PTR(PM_BR_CMPL),
	CACHE_EVENT_PTR(PM_DTLB_MISS),
	CACHE_EVENT_PTR(PM_ITLB_MISS),
	शून्य
पूर्ण;

अटल काष्ठा attribute *घातer10_events_attr[] = अणु
	GENERIC_EVENT_PTR(PM_RUN_CYC),
	GENERIC_EVENT_PTR(PM_RUN_INST_CMPL),
	GENERIC_EVENT_PTR(PM_BR_FIN),
	GENERIC_EVENT_PTR(PM_MPRED_BR_FIN),
	GENERIC_EVENT_PTR(PM_LD_REF_L1),
	GENERIC_EVENT_PTR(PM_LD_DEMAND_MISS_L1_FIN),
	GENERIC_EVENT_PTR(MEM_LOADS),
	GENERIC_EVENT_PTR(MEM_STORES),
	CACHE_EVENT_PTR(PM_LD_MISS_L1),
	CACHE_EVENT_PTR(PM_LD_REF_L1),
	CACHE_EVENT_PTR(PM_LD_PREFETCH_CACHE_LINE_MISS),
	CACHE_EVENT_PTR(PM_ST_MISS_L1),
	CACHE_EVENT_PTR(PM_L1_ICACHE_MISS),
	CACHE_EVENT_PTR(PM_INST_FROM_L1),
	CACHE_EVENT_PTR(PM_IC_PREF_REQ),
	CACHE_EVENT_PTR(PM_DATA_FROM_L3MISS),
	CACHE_EVENT_PTR(PM_DATA_FROM_L3),
	CACHE_EVENT_PTR(PM_L3_PF_MISS_L3),
	CACHE_EVENT_PTR(PM_L2_ST_MISS),
	CACHE_EVENT_PTR(PM_L2_ST),
	CACHE_EVENT_PTR(PM_BR_MPRED_CMPL),
	CACHE_EVENT_PTR(PM_BR_CMPL),
	CACHE_EVENT_PTR(PM_DTLB_MISS),
	CACHE_EVENT_PTR(PM_ITLB_MISS),
	शून्य
पूर्ण;

अटल काष्ठा attribute_group घातer10_pmu_events_group_dd1 = अणु
	.name = "events",
	.attrs = घातer10_events_attr_dd1,
पूर्ण;

अटल काष्ठा attribute_group घातer10_pmu_events_group = अणु
	.name = "events",
	.attrs = घातer10_events_attr,
पूर्ण;

PMU_FORMAT_ATTR(event,          "config:0-59");
PMU_FORMAT_ATTR(pmcxsel,        "config:0-7");
PMU_FORMAT_ATTR(mark,           "config:8");
PMU_FORMAT_ATTR(combine,        "config:10-11");
PMU_FORMAT_ATTR(unit,           "config:12-15");
PMU_FORMAT_ATTR(pmc,            "config:16-19");
PMU_FORMAT_ATTR(cache_sel,      "config:20-21");
PMU_FORMAT_ATTR(sdar_mode,      "config:22-23");
PMU_FORMAT_ATTR(sample_mode,    "config:24-28");
PMU_FORMAT_ATTR(thresh_sel,     "config:29-31");
PMU_FORMAT_ATTR(thresh_stop,    "config:32-35");
PMU_FORMAT_ATTR(thresh_start,   "config:36-39");
PMU_FORMAT_ATTR(l2l3_sel,       "config:40-44");
PMU_FORMAT_ATTR(src_sel,        "config:45-46");
PMU_FORMAT_ATTR(invert_bit,     "config:47");
PMU_FORMAT_ATTR(src_mask,       "config:48-53");
PMU_FORMAT_ATTR(src_match,      "config:54-59");
PMU_FORMAT_ATTR(radix_scope,	"config:9");
PMU_FORMAT_ATTR(thresh_cmp,     "config1:0-17");

अटल काष्ठा attribute *घातer10_pmu_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_pmcxsel.attr,
	&क्रमmat_attr_mark.attr,
	&क्रमmat_attr_combine.attr,
	&क्रमmat_attr_unit.attr,
	&क्रमmat_attr_pmc.attr,
	&क्रमmat_attr_cache_sel.attr,
	&क्रमmat_attr_sdar_mode.attr,
	&क्रमmat_attr_sample_mode.attr,
	&क्रमmat_attr_thresh_sel.attr,
	&क्रमmat_attr_thresh_stop.attr,
	&क्रमmat_attr_thresh_start.attr,
	&क्रमmat_attr_l2l3_sel.attr,
	&क्रमmat_attr_src_sel.attr,
	&क्रमmat_attr_invert_bit.attr,
	&क्रमmat_attr_src_mask.attr,
	&क्रमmat_attr_src_match.attr,
	&क्रमmat_attr_radix_scope.attr,
	&क्रमmat_attr_thresh_cmp.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group घातer10_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = घातer10_pmu_क्रमmat_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *घातer10_pmu_attr_groups_dd1[] = अणु
	&घातer10_pmu_क्रमmat_group,
	&घातer10_pmu_events_group_dd1,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *घातer10_pmu_attr_groups[] = अणु
	&घातer10_pmu_क्रमmat_group,
	&घातer10_pmu_events_group,
	शून्य,
पूर्ण;

अटल पूर्णांक घातer10_generic_events_dd1[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] =			PM_RUN_CYC,
	[PERF_COUNT_HW_INSTRUCTIONS] =			PM_RUN_INST_CMPL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] =		PM_BR_CMPL,
	[PERF_COUNT_HW_BRANCH_MISSES] =			PM_BR_MPRED_CMPL,
	[PERF_COUNT_HW_CACHE_REFERENCES] =		PM_LD_REF_L1,
	[PERF_COUNT_HW_CACHE_MISSES] =			PM_LD_MISS_L1,
पूर्ण;

अटल पूर्णांक घातer10_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] =			PM_RUN_CYC,
	[PERF_COUNT_HW_INSTRUCTIONS] =			PM_RUN_INST_CMPL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] =		PM_BR_FIN,
	[PERF_COUNT_HW_BRANCH_MISSES] =			PM_MPRED_BR_FIN,
	[PERF_COUNT_HW_CACHE_REFERENCES] =		PM_LD_REF_L1,
	[PERF_COUNT_HW_CACHE_MISSES] =			PM_LD_DEMAND_MISS_L1_FIN,
पूर्ण;

अटल u64 घातer10_bhrb_filter_map(u64 branch_sample_type)
अणु
	u64 pmu_bhrb_filter = 0;

	/* BHRB and regular PMU events share the same privilege state
	 * filter configuration. BHRB is always recorded aदीर्घ with a
	 * regular PMU event. As the privilege state filter is handled
	 * in the basic PMC configuration of the accompanying regular
	 * PMU event, we ignore any separate BHRB specअगरic request.
	 */

	/* No branch filter requested */
	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_ANY)
		वापस pmu_bhrb_filter;

	/* Invalid branch filter options - HW करोes not support */
	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_ANY_RETURN)
		वापस -1;

	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_IND_CALL) अणु
		pmu_bhrb_filter |= POWER10_MMCRA_IFM2;
		वापस pmu_bhrb_filter;
	पूर्ण

	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_COND) अणु
		pmu_bhrb_filter |= POWER10_MMCRA_IFM3;
		वापस pmu_bhrb_filter;
	पूर्ण

	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_CALL)
		वापस -1;

	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_ANY_CALL) अणु
		pmu_bhrb_filter |= POWER10_MMCRA_IFM1;
		वापस pmu_bhrb_filter;
	पूर्ण

	/* Every thing अन्यथा is unsupported */
	वापस -1;
पूर्ण

अटल व्योम घातer10_config_bhrb(u64 pmu_bhrb_filter)
अणु
	pmu_bhrb_filter &= POWER10_MMCRA_BHRB_MASK;

	/* Enable BHRB filter in PMU */
	mtspr(SPRN_MMCRA, (mfspr(SPRN_MMCRA) | pmu_bhrb_filter));
पूर्ण

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 */
अटल u64 घातer10_cache_events_dd1[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PM_LD_REF_L1,
			[C(RESULT_MISS)] = PM_LD_MISS_L1,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = 0,
			[C(RESULT_MISS)] = PM_ST_MISS_L1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = PM_LD_PREFETCH_CACHE_LINE_MISS,
			[C(RESULT_MISS)] = 0,
		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PM_INST_FROM_L1,
			[C(RESULT_MISS)] = PM_L1_ICACHE_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = PM_INST_FROM_L1MISS,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = PM_IC_PREF_REQ,
			[C(RESULT_MISS)] = 0,
		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PM_DATA_FROM_L3,
			[C(RESULT_MISS)] = PM_DATA_FROM_L3MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = 0,
		पूर्ण,
	पूर्ण,
	 [C(DTLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = 0,
			[C(RESULT_MISS)] = PM_DTLB_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = 0,
			[C(RESULT_MISS)] = PM_ITLB_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PM_BR_CMPL,
			[C(RESULT_MISS)] = PM_BR_MPRED_CMPL,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल u64 घातer10_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PM_LD_REF_L1,
			[C(RESULT_MISS)] = PM_LD_MISS_L1,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = 0,
			[C(RESULT_MISS)] = PM_ST_MISS_L1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = PM_LD_PREFETCH_CACHE_LINE_MISS,
			[C(RESULT_MISS)] = 0,
		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PM_INST_FROM_L1,
			[C(RESULT_MISS)] = PM_L1_ICACHE_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = PM_INST_FROM_L1MISS,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = PM_IC_PREF_REQ,
			[C(RESULT_MISS)] = 0,
		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PM_DATA_FROM_L3,
			[C(RESULT_MISS)] = PM_DATA_FROM_L3MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = PM_L2_ST,
			[C(RESULT_MISS)] = PM_L2_ST_MISS,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = PM_L3_PF_MISS_L3,
			[C(RESULT_MISS)] = 0,
		पूर्ण,
	पूर्ण,
	 [C(DTLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = 0,
			[C(RESULT_MISS)] = PM_DTLB_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = 0,
			[C(RESULT_MISS)] = PM_ITLB_MISS,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PM_BR_CMPL,
			[C(RESULT_MISS)] = PM_BR_MPRED_CMPL,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = -1,
			[C(RESULT_MISS)] = -1,
		पूर्ण,
	पूर्ण,
पूर्ण;

#अघोषित C

अटल काष्ठा घातer_pmu घातer10_pmu = अणु
	.name			= "POWER10",
	.n_counter		= MAX_PMU_COUNTERS,
	.add_fields		= ISA207_ADD_FIELDS,
	.test_adder		= ISA207_TEST_ADDER,
	.group_स्थिरraपूर्णांक_mask	= CNST_CACHE_PMC4_MASK,
	.group_स्थिरraपूर्णांक_val	= CNST_CACHE_PMC4_VAL,
	.compute_mmcr		= isa207_compute_mmcr,
	.config_bhrb		= घातer10_config_bhrb,
	.bhrb_filter_map	= घातer10_bhrb_filter_map,
	.get_स्थिरraपूर्णांक		= isa207_get_स्थिरraपूर्णांक,
	.get_alternatives	= घातer10_get_alternatives,
	.get_mem_data_src	= isa207_get_mem_data_src,
	.get_mem_weight		= isa207_get_mem_weight,
	.disable_pmc		= isa207_disable_pmc,
	.flags			= PPMU_HAS_SIER | PPMU_ARCH_207S |
				  PPMU_ARCH_31 | PPMU_HAS_ATTR_CONFIG1,
	.n_generic		= ARRAY_SIZE(घातer10_generic_events),
	.generic_events		= घातer10_generic_events,
	.cache_events		= &घातer10_cache_events,
	.attr_groups		= घातer10_pmu_attr_groups,
	.bhrb_nr		= 32,
	.capabilities           = PERF_PMU_CAP_EXTENDED_REGS,
	.check_attr_config	= घातer10_check_attr_config,
पूर्ण;

पूर्णांक init_घातer10_pmu(व्योम)
अणु
	अचिन्हित पूर्णांक pvr;
	पूर्णांक rc;

	/* Comes from cpu_specs[] */
	अगर (!cur_cpu_spec->oprofile_cpu_type ||
	    म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/power10"))
		वापस -ENODEV;

	pvr = mfspr(SPRN_PVR);
	/* Add the ppmu flag क्रम घातer10 DD1 */
	अगर ((PVR_CFG(pvr) == 1))
		घातer10_pmu.flags |= PPMU_P10_DD1;

	/* Set the PERF_REG_EXTENDED_MASK here */
	PERF_REG_EXTENDED_MASK = PERF_REG_PMU_MASK_31;

	अगर ((PVR_CFG(pvr) == 1)) अणु
		घातer10_pmu.generic_events = घातer10_generic_events_dd1;
		घातer10_pmu.attr_groups = घातer10_pmu_attr_groups_dd1;
		घातer10_pmu.cache_events = &घातer10_cache_events_dd1;
	पूर्ण

	rc = रेजिस्टर_घातer_pmu(&घातer10_pmu);
	अगर (rc)
		वापस rc;

	/* Tell userspace that EBB is supported */
	cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_EBB;

	वापस 0;
पूर्ण
