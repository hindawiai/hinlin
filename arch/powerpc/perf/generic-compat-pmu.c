<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2019 Madhavan Srinivasan, IBM Corporation.

#घोषणा pr_fmt(fmt)	"generic-compat-pmu: " fmt

#समावेश "isa207-common.h"

/*
 * Raw event encoding:
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *                                 [ pmc ]   [unit ]   [ ]   m   [    pmcxsel    ]
 *                                                     |     |
 *                                                     |     *- mark
 *                                                     |
 *                                                     |
 *                                                     *- combine
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
 */

/*
 * Some घातer9 event codes.
 */
#घोषणा EVENT(_name, _code)	_name = _code,

क्रमागत अणु
EVENT(PM_CYC,					0x0001e)
EVENT(PM_INST_CMPL,				0x00002)
पूर्ण;

#अघोषित EVENT

GENERIC_EVENT_ATTR(cpu-cycles,			PM_CYC);
GENERIC_EVENT_ATTR(inकाष्ठाions,		PM_INST_CMPL);

अटल काष्ठा attribute *generic_compat_events_attr[] = अणु
	GENERIC_EVENT_PTR(PM_CYC),
	GENERIC_EVENT_PTR(PM_INST_CMPL),
	शून्य
पूर्ण;

अटल काष्ठा attribute_group generic_compat_pmu_events_group = अणु
	.name = "events",
	.attrs = generic_compat_events_attr,
पूर्ण;

PMU_FORMAT_ATTR(event,		"config:0-19");
PMU_FORMAT_ATTR(pmcxsel,	"config:0-7");
PMU_FORMAT_ATTR(mark,		"config:8");
PMU_FORMAT_ATTR(combine,	"config:10-11");
PMU_FORMAT_ATTR(unit,		"config:12-15");
PMU_FORMAT_ATTR(pmc,		"config:16-19");

अटल काष्ठा attribute *generic_compat_pmu_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_pmcxsel.attr,
	&क्रमmat_attr_mark.attr,
	&क्रमmat_attr_combine.attr,
	&क्रमmat_attr_unit.attr,
	&क्रमmat_attr_pmc.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group generic_compat_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = generic_compat_pmu_क्रमmat_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *generic_compat_pmu_attr_groups[] = अणु
	&generic_compat_pmu_क्रमmat_group,
	&generic_compat_pmu_events_group,
	शून्य,
पूर्ण;

अटल पूर्णांक compat_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] =			PM_CYC,
	[PERF_COUNT_HW_INSTRUCTIONS] =			PM_INST_CMPL,
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 */
अटल u64 generic_compat_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[ C(L1D) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
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
	[ C(L1I) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
		[ C(OP_WRITE) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = -1,
		पूर्ण,
		[ C(OP_PREFETCH) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
		पूर्ण,
	पूर्ण,
	[ C(LL) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
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
	[ C(DTLB) ] = अणु
		[ C(OP_READ) ] = अणु
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
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
			[ C(RESULT_MISS)   ] = 0,
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
			[ C(RESULT_ACCESS) ] = 0,
			[ C(RESULT_MISS)   ] = 0,
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

अटल काष्ठा घातer_pmu generic_compat_pmu = अणु
	.name			= "GENERIC_COMPAT",
	.n_counter		= MAX_PMU_COUNTERS,
	.add_fields		= ISA207_ADD_FIELDS,
	.test_adder		= ISA207_TEST_ADDER,
	.compute_mmcr		= isa207_compute_mmcr,
	.get_स्थिरraपूर्णांक		= isa207_get_स्थिरraपूर्णांक,
	.disable_pmc		= isa207_disable_pmc,
	.flags			= PPMU_HAS_SIER | PPMU_ARCH_207S,
	.n_generic		= ARRAY_SIZE(compat_generic_events),
	.generic_events		= compat_generic_events,
	.cache_events		= &generic_compat_cache_events,
	.attr_groups		= generic_compat_pmu_attr_groups,
पूर्ण;

पूर्णांक init_generic_compat_pmu(व्योम)
अणु
	पूर्णांक rc = 0;

	rc = रेजिस्टर_घातer_pmu(&generic_compat_pmu);
	अगर (rc)
		वापस rc;

	/* Tell userspace that EBB is supported */
	cur_cpu_spec->cpu_user_features2 |= PPC_FEATURE2_EBB;

	वापस 0;
पूर्ण
