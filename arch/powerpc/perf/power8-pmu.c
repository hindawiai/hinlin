<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter support क्रम POWER8 processors.
 *
 * Copyright 2009 Paul Mackerras, IBM Corporation.
 * Copyright 2013 Michael Ellerman, IBM Corporation.
 */

#घोषणा pr_fmt(fmt)	"power8-pmu: " fmt

#समावेश "isa207-common.h"

/*
 * Some घातer8 event codes.
 */
#घोषणा EVENT(_name, _code)	_name = _code,

क्रमागत अणु
#समावेश "power8-events-list.h"
पूर्ण;

#अघोषित EVENT

/* MMCRA IFM bits - POWER8 */
#घोषणा	POWER8_MMCRA_IFM1		0x0000000040000000UL
#घोषणा	POWER8_MMCRA_IFM2		0x0000000080000000UL
#घोषणा	POWER8_MMCRA_IFM3		0x00000000C0000000UL
#घोषणा	POWER8_MMCRA_BHRB_MASK		0x00000000C0000000UL

/*
 * Raw event encoding क्रम PowerISA v2.07 (Power8):
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   | | [ ]                           [      thresh_cmp     ]   [  thresh_ctl   ]
 *   | |  |                                                              |
 *   | |  *- IFM (Linux)                 thresh start/stop OR FAB match -*
 *   | *- BHRB (Linux)
 *   *- EBB (Linux)
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   [   ] [  sample ]   [cache]   [ pmc ]   [unit ]   c     m   [    pmcxsel    ]
 *     |        |           |                          |     |
 *     |        |           |                          |     *- mark
 *     |        |           *- L1/L2/L3 cache_sel      |
 *     |        |                                      |
 *     |        *- sampling mode क्रम marked events     *- combine
 *     |
 *     *- thresh_sel
 *
 * Below uses IBM bit numbering.
 *
 * MMCR1[x:y] = unit    (PMCxUNIT)
 * MMCR1[x]   = combine (PMCxCOMB)
 *
 * अगर pmc == 3 and unit == 0 and pmcxsel[0:6] == 0b0101011
 *	# PM_MRK_FAB_RSP_MATCH
 *	MMCR1[20:27] = thresh_ctl   (FAB_CRESP_MATCH / FAB_TYPE_MATCH)
 * अन्यथा अगर pmc == 4 and unit == 0xf and pmcxsel[0:6] == 0b0101001
 *	# PM_MRK_FAB_RSP_MATCH_CYC
 *	MMCR1[20:27] = thresh_ctl   (FAB_CRESP_MATCH / FAB_TYPE_MATCH)
 * अन्यथा
 *	MMCRA[48:55] = thresh_ctl   (THRESH START/END)
 *
 * अगर thresh_sel:
 *	MMCRA[45:47] = thresh_sel
 *
 * अगर thresh_cmp:
 *	MMCRA[22:24] = thresh_cmp[0:2]
 *	MMCRA[25:31] = thresh_cmp[3:9]
 *
 * अगर unit == 6 or unit == 7
 *	MMCRC[53:55] = cache_sel[1:3]      (L2EVENT_SEL)
 * अन्यथा अगर unit == 8 or unit == 9:
 *	अगर cache_sel[0] == 0: # L3 bank
 *		MMCRC[47:49] = cache_sel[1:3]  (L3EVENT_SEL0)
 *	अन्यथा अगर cache_sel[0] == 1:
 *		MMCRC[50:51] = cache_sel[2:3]  (L3EVENT_SEL1)
 * अन्यथा अगर cache_sel[1]: # L1 event
 *	MMCR1[16] = cache_sel[2]
त *	MMCR1[17] = cache_sel[3]
 *
 * अगर mark:
 *	MMCRA[63]    = 1		(SAMPLE_ENABLE)
 *	MMCRA[57:59] = sample[0:2]	(RAND_SAMP_ELIG)
त *	MMCRA[61:62] = sample[3:4]	(RAND_SAMP_MODE)
 *
 * अगर EBB and BHRB:
 *	MMCRA[32:33] = IFM
 *
 */

/* PowerISA v2.07 क्रमmat attribute काष्ठाure*/
बाह्य काष्ठा attribute_group isa207_pmu_क्रमmat_group;

/* Table of alternatives, sorted by column 0 */
अटल स्थिर अचिन्हित पूर्णांक event_alternatives[][MAX_ALT] = अणु
	अणु PM_MRK_ST_CMPL,		PM_MRK_ST_CMPL_ALT पूर्ण,
	अणु PM_BR_MRK_2PATH,		PM_BR_MRK_2PATH_ALT पूर्ण,
	अणु PM_L3_CO_MEPF,		PM_L3_CO_MEPF_ALT पूर्ण,
	अणु PM_MRK_DATA_FROM_L2MISS,	PM_MRK_DATA_FROM_L2MISS_ALT पूर्ण,
	अणु PM_CMPLU_STALL_ALT,		PM_CMPLU_STALL पूर्ण,
	अणु PM_BR_2PATH,			PM_BR_2PATH_ALT पूर्ण,
	अणु PM_INST_DISP,			PM_INST_DISP_ALT पूर्ण,
	अणु PM_RUN_CYC_ALT,		PM_RUN_CYC पूर्ण,
	अणु PM_MRK_FILT_MATCH,		PM_MRK_FILT_MATCH_ALT पूर्ण,
	अणु PM_LD_MISS_L1,		PM_LD_MISS_L1_ALT पूर्ण,
	अणु PM_RUN_INST_CMPL_ALT,		PM_RUN_INST_CMPL पूर्ण,
पूर्ण;

अटल पूर्णांक घातer8_get_alternatives(u64 event, अचिन्हित पूर्णांक flags, u64 alt[])
अणु
	पूर्णांक num_alt = 0;

	num_alt = isa207_get_alternatives(event, alt,
					  ARRAY_SIZE(event_alternatives), flags,
					  event_alternatives);

	वापस num_alt;
पूर्ण

GENERIC_EVENT_ATTR(cpu-cycles,			PM_CYC);
GENERIC_EVENT_ATTR(stalled-cycles-frontend,	PM_GCT_NOSLOT_CYC);
GENERIC_EVENT_ATTR(stalled-cycles-backend,	PM_CMPLU_STALL);
GENERIC_EVENT_ATTR(inकाष्ठाions,		PM_INST_CMPL);
GENERIC_EVENT_ATTR(branch-inकाष्ठाions,		PM_BRU_FIN);
GENERIC_EVENT_ATTR(branch-misses,		PM_BR_MPRED_CMPL);
GENERIC_EVENT_ATTR(cache-references,		PM_LD_REF_L1);
GENERIC_EVENT_ATTR(cache-misses,		PM_LD_MISS_L1);
GENERIC_EVENT_ATTR(mem_access,			MEM_ACCESS);

CACHE_EVENT_ATTR(L1-dcache-load-misses,		PM_LD_MISS_L1);
CACHE_EVENT_ATTR(L1-dcache-loads,		PM_LD_REF_L1);

CACHE_EVENT_ATTR(L1-dcache-prefetches,		PM_L1_PREF);
CACHE_EVENT_ATTR(L1-dcache-store-misses,	PM_ST_MISS_L1);
CACHE_EVENT_ATTR(L1-icache-load-misses,		PM_L1_ICACHE_MISS);
CACHE_EVENT_ATTR(L1-icache-loads,		PM_INST_FROM_L1);
CACHE_EVENT_ATTR(L1-icache-prefetches,		PM_IC_PREF_WRITE);

CACHE_EVENT_ATTR(LLC-load-misses,		PM_DATA_FROM_L3MISS);
CACHE_EVENT_ATTR(LLC-loads,			PM_DATA_FROM_L3);
CACHE_EVENT_ATTR(LLC-prefetches,		PM_L3_PREF_ALL);
CACHE_EVENT_ATTR(LLC-store-misses,		PM_L2_ST_MISS);
CACHE_EVENT_ATTR(LLC-stores,			PM_L2_ST);

CACHE_EVENT_ATTR(branch-load-misses,		PM_BR_MPRED_CMPL);
CACHE_EVENT_ATTR(branch-loads,			PM_BRU_FIN);
CACHE_EVENT_ATTR(dTLB-load-misses,		PM_DTLB_MISS);
CACHE_EVENT_ATTR(iTLB-load-misses,		PM_ITLB_MISS);

अटल काष्ठा attribute *घातer8_events_attr[] = अणु
	GENERIC_EVENT_PTR(PM_CYC),
	GENERIC_EVENT_PTR(PM_GCT_NOSLOT_CYC),
	GENERIC_EVENT_PTR(PM_CMPLU_STALL),
	GENERIC_EVENT_PTR(PM_INST_CMPL),
	GENERIC_EVENT_PTR(PM_BRU_FIN),
	GENERIC_EVENT_PTR(PM_BR_MPRED_CMPL),
	GENERIC_EVENT_PTR(PM_LD_REF_L1),
	GENERIC_EVENT_PTR(PM_LD_MISS_L1),
	GENERIC_EVENT_PTR(MEM_ACCESS),

	CACHE_EVENT_PTR(PM_LD_MISS_L1),
	CACHE_EVENT_PTR(PM_LD_REF_L1),
	CACHE_EVENT_PTR(PM_L1_PREF),
	CACHE_EVENT_PTR(PM_ST_MISS_L1),
	CACHE_EVENT_PTR(PM_L1_ICACHE_MISS),
	CACHE_EVENT_PTR(PM_INST_FROM_L1),
	CACHE_EVENT_PTR(PM_IC_PREF_WRITE),
	CACHE_EVENT_PTR(PM_DATA_FROM_L3MISS),
	CACHE_EVENT_PTR(PM_DATA_FROM_L3),
	CACHE_EVENT_PTR(PM_L3_PREF_ALL),
	CACHE_EVENT_PTR(PM_L2_ST_MISS),
	CACHE_EVENT_PTR(PM_L2_ST),

	CACHE_EVENT_PTR(PM_BR_MPRED_CMPL),
	CACHE_EVENT_PTR(PM_BRU_FIN),

	CACHE_EVENT_PTR(PM_DTLB_MISS),
	CACHE_EVENT_PTR(PM_ITLB_MISS),
	शून्य
पूर्ण;

अटल काष्ठा attribute_group घातer8_pmu_events_group = अणु
	.name = "events",
	.attrs = घातer8_events_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *घातer8_pmu_attr_groups[] = अणु
	&isa207_pmu_क्रमmat_group,
	&घातer8_pmu_events_group,
	शून्य,
पूर्ण;

अटल पूर्णांक घातer8_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] =			PM_CYC,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] =	PM_GCT_NOSLOT_CYC,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] =	PM_CMPLU_STALL,
	[PERF_COUNT_HW_INSTRUCTIONS] =			PM_INST_CMPL,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] =		PM_BRU_FIN,
	[PERF_COUNT_HW_BRANCH_MISSES] =			PM_BR_MPRED_CMPL,
	[PERF_COUNT_HW_CACHE_REFERENCES] =		PM_LD_REF_L1,
	[PERF_COUNT_HW_CACHE_MISSES] =			PM_LD_MISS_L1,
पूर्ण;

अटल u64 घातer8_bhrb_filter_map(u64 branch_sample_type)
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

	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_IND_CALL)
		वापस -1;

	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_CALL)
		वापस -1;

	अगर (branch_sample_type & PERF_SAMPLE_BRANCH_ANY_CALL) अणु
		pmu_bhrb_filter |= POWER8_MMCRA_IFM1;
		वापस pmu_bhrb_filter;
	पूर्ण

	/* Every thing अन्यथा is unsupported */
	वापस -1;
पूर्ण

अटल व्योम घातer8_config_bhrb(u64 pmu_bhrb_filter)
अणु
	pmu_bhrb_filter &= POWER8_MMCRA_BHRB_MASK;

	/* Enable BHRB filter in PMU */
	mtspr(SPRN_MMCRA, (mfspr(SPRN_MMCRA) | pmu_bhrb_filter));
पूर्ण

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 */
अटल u64 घातer8_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[ C(L1D) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_LD_REF_L1,
			[ C(RESULT_MISS)   ] = PM_LD_MISS_L1,
		पूर्ण,
		[ C(OP_WRITE) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = PM_ST_MISS_L1,
		पूर्ण,
		[ C(OP_PREFETCH) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_L1_PREF,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
	पूर्ण,
	[ C(L1I) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_INST_FROM_L1,
			[ C(RESULT_MISS)   ] = PM_L1_ICACHE_MISS,
		पूर्ण,
		[ C(OP_WRITE) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_L1_DEMAND_WRITE,
			[ C(RESULT_MISS)   ] = -1,
		पूर्ण,
		[ C(OP_PREFETCH) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_IC_PREF_WRITE,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
	पूर्ण,
	[ C(LL) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_DATA_FROM_L3,
			[ C(RESULT_MISS)   ] = PM_DATA_FROM_L3MISS,
		पूर्ण,
		[ C(OP_WRITE) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_L2_ST,
			[ C(RESULT_MISS)   ] = PM_L2_ST_MISS,
		पूर्ण,
		[ C(OP_PREFETCH) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_L3_PREF_ALL,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
	पूर्ण,
	[ C(DTLB) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = PM_DTLB_MISS,
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
	[ C(ITLB) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = PM_ITLB_MISS,
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
	[ C(BPU) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = PM_BRU_FIN,
			[ C(RESULT_MISS)   ] = PM_BR_MPRED_CMPL,
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
			[ C(RESULT_ACCESS) ] = -1,
			[ C(RESULT_MISS)   ] = -1,
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

#अघोषित C

अटल काष्ठा घातer_pmu घातer8_pmu = अणु
	.name			= "POWER8",
	.n_counter		= MAX_PMU_COUNTERS,
	.max_alternatives	= MAX_ALT + 1,
	.add_fields		= ISA207_ADD_FIELDS,
	.test_adder		= ISA207_TEST_ADDER,
	.compute_mmcr		= isa207_compute_mmcr,
	.config_bhrb		= घातer8_config_bhrb,
	.bhrb_filter_map	= घातer8_bhrb_filter_map,
	.get_स्थिरraपूर्णांक		= isa207_get_स्थिरraपूर्णांक,
	.get_alternatives	= घातer8_get_alternatives,
	.get_mem_data_src	= isa207_get_mem_data_src,
	.get_mem_weight		= isa207_get_mem_weight,
	.disable_pmc		= isa207_disable_pmc,
	.flags			= PPMU_HAS_SIER | PPMU_ARCH_207S,
	.n_generic		= ARRAY_SIZE(घातer8_generic_events),
	.generic_events		= घातer8_generic_events,
	.cache_events		= &घातer8_cache_events,
	.attr_groups		= घातer8_pmu_attr_groups,
	.bhrb_nr		= 32,
पूर्ण;

पूर्णांक init_घातer8_pmu(व्योम)
अणु
	पूर्णांक rc;

	अगर (!cur_cpu_spec->oprofile_cpu_type ||
	    म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/power8"))
		वापस -ENODEV;

	rc = रेजिस्टर_घातer_pmu(&घातer8_pmu);
	अगर (rc)
		वापस rc;

	/* Tell userspace that EBB is supported */
	cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_EBB;

	अगर (cpu_has_feature(CPU_FTR_PMAO_BUG))
		pr_info("PMAO restore workaround active.\n");

	वापस 0;
पूर्ण
