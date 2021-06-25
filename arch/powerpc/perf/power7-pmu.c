<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter support क्रम POWER7 processors.
 *
 * Copyright 2009 Paul Mackerras, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>

#समावेश "internal.h"

/*
 * Bits in event code क्रम POWER7
 */
#घोषणा PM_PMC_SH	16	/* PMC number (1-based) क्रम direct events */
#घोषणा PM_PMC_MSK	0xf
#घोषणा PM_PMC_MSKS	(PM_PMC_MSK << PM_PMC_SH)
#घोषणा PM_UNIT_SH	12	/* TTMMUX number and setting - unit select */
#घोषणा PM_UNIT_MSK	0xf
#घोषणा PM_COMBINE_SH	11	/* Combined event bit */
#घोषणा PM_COMBINE_MSK	1
#घोषणा PM_COMBINE_MSKS	0x800
#घोषणा PM_L2SEL_SH	8	/* L2 event select */
#घोषणा PM_L2SEL_MSK	7
#घोषणा PM_PMCSEL_MSK	0xff

/*
 * Bits in MMCR1 क्रम POWER7
 */
#घोषणा MMCR1_TTM0SEL_SH	60
#घोषणा MMCR1_TTM1SEL_SH	56
#घोषणा MMCR1_TTM2SEL_SH	52
#घोषणा MMCR1_TTM3SEL_SH	48
#घोषणा MMCR1_TTMSEL_MSK	0xf
#घोषणा MMCR1_L2SEL_SH		45
#घोषणा MMCR1_L2SEL_MSK		7
#घोषणा MMCR1_PMC1_COMBINE_SH	35
#घोषणा MMCR1_PMC2_COMBINE_SH	34
#घोषणा MMCR1_PMC3_COMBINE_SH	33
#घोषणा MMCR1_PMC4_COMBINE_SH	32
#घोषणा MMCR1_PMC1SEL_SH	24
#घोषणा MMCR1_PMC2SEL_SH	16
#घोषणा MMCR1_PMC3SEL_SH	8
#घोषणा MMCR1_PMC4SEL_SH	0
#घोषणा MMCR1_PMCSEL_SH(n)	(MMCR1_PMC1SEL_SH - (n) * 8)
#घोषणा MMCR1_PMCSEL_MSK	0xff

/*
 * Power7 event codes.
 */
#घोषणा EVENT(_name, _code) \
	_name = _code,

क्रमागत अणु
#समावेश "power7-events-list.h"
पूर्ण;
#अघोषित EVENT

/*
 * Layout of स्थिरraपूर्णांक bits:
 * 6666555555555544444444443333333333222222222211111111110000000000
 * 3210987654321098765432109876543210987654321098765432109876543210
 *                                              < ><  ><><><><><><>
 *                                              L2  NC P6P5P4P3P2P1
 *
 * L2 - 16-18 - Required L2SEL value (select field)
 *
 * NC - number of counters
 *     15: NC error 0x8000
 *     12-14: number of events needing PMC1-4 0x7000
 *
 * P6
 *     11: P6 error 0x800
 *     10-11: Count of events needing PMC6
 *
 * P1..P5
 *     0-9: Count of events needing PMC1..PMC5
 */

अटल पूर्णांक घातer7_get_स्थिरraपूर्णांक(u64 event, अचिन्हित दीर्घ *maskp,
				 अचिन्हित दीर्घ *valp, u64 event_config1 __maybe_unused)
अणु
	पूर्णांक pmc, sh, unit;
	अचिन्हित दीर्घ mask = 0, value = 0;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	अगर (pmc) अणु
		अगर (pmc > 6)
			वापस -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		value |= 1 << sh;
		अगर (pmc >= 5 && !(event == 0x500fa || event == 0x600f4))
			वापस -1;
	पूर्ण
	अगर (pmc < 5) अणु
		/* need a counter from PMC1-4 set */
		mask  |= 0x8000;
		value |= 0x1000;
	पूर्ण

	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	अगर (unit == 6) अणु
		/* L2SEL must be identical across events */
		पूर्णांक l2sel = (event >> PM_L2SEL_SH) & PM_L2SEL_MSK;
		mask  |= 0x7 << 16;
		value |= l2sel << 16;
	पूर्ण

	*maskp = mask;
	*valp = value;
	वापस 0;
पूर्ण

#घोषणा MAX_ALT	2	/* at most 2 alternatives क्रम any event */

अटल स्थिर अचिन्हित पूर्णांक event_alternatives[][MAX_ALT] = अणु
	अणु 0x200f2, 0x300f2 पूर्ण,		/* PM_INST_DISP */
	अणु 0x200f4, 0x600f4 पूर्ण,		/* PM_RUN_CYC */
	अणु 0x400fa, 0x500fa पूर्ण,		/* PM_RUN_INST_CMPL */
पूर्ण;

/*
 * Scan the alternatives table क्रम a match and वापस the
 * index पूर्णांकo the alternatives table अगर found, अन्यथा -1.
 */
अटल पूर्णांक find_alternative(u64 event)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(event_alternatives); ++i) अणु
		अगर (event < event_alternatives[i][0])
			अवरोध;
		क्रम (j = 0; j < MAX_ALT && event_alternatives[i][j]; ++j)
			अगर (event == event_alternatives[i][j])
				वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल s64 find_alternative_decode(u64 event)
अणु
	पूर्णांक pmc, psel;

	/* this only handles the 4x decode events */
	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psel = event & PM_PMCSEL_MSK;
	अगर ((pmc == 2 || pmc == 4) && (psel & ~7) == 0x40)
		वापस event - (1 << PM_PMC_SH) + 8;
	अगर ((pmc == 1 || pmc == 3) && (psel & ~7) == 0x48)
		वापस event + (1 << PM_PMC_SH) - 8;
	वापस -1;
पूर्ण

अटल पूर्णांक घातer7_get_alternatives(u64 event, अचिन्हित पूर्णांक flags, u64 alt[])
अणु
	पूर्णांक i, j, nalt = 1;
	s64 ae;

	alt[0] = event;
	nalt = 1;
	i = find_alternative(event);
	अगर (i >= 0) अणु
		क्रम (j = 0; j < MAX_ALT; ++j) अणु
			ae = event_alternatives[i][j];
			अगर (ae && ae != event)
				alt[nalt++] = ae;
		पूर्ण
	पूर्ण अन्यथा अणु
		ae = find_alternative_decode(event);
		अगर (ae > 0)
			alt[nalt++] = ae;
	पूर्ण

	अगर (flags & PPMU_ONLY_COUNT_RUN) अणु
		/*
		 * We're only counting in RUN state,
		 * so PM_CYC is equivalent to PM_RUN_CYC
		 * and PM_INST_CMPL === PM_RUN_INST_CMPL.
		 * This करोesn't include alternatives that don't provide
		 * any extra flexibility in assigning PMCs.
		 */
		j = nalt;
		क्रम (i = 0; i < nalt; ++i) अणु
			चयन (alt[i]) अणु
			हाल 0x1e:	/* PM_CYC */
				alt[j++] = 0x600f4;	/* PM_RUN_CYC */
				अवरोध;
			हाल 0x600f4:	/* PM_RUN_CYC */
				alt[j++] = 0x1e;
				अवरोध;
			हाल 0x2:	/* PM_PPC_CMPL */
				alt[j++] = 0x500fa;	/* PM_RUN_INST_CMPL */
				अवरोध;
			हाल 0x500fa:	/* PM_RUN_INST_CMPL */
				alt[j++] = 0x2;	/* PM_PPC_CMPL */
				अवरोध;
			पूर्ण
		पूर्ण
		nalt = j;
	पूर्ण

	वापस nalt;
पूर्ण

/*
 * Returns 1 अगर event counts things relating to marked inकाष्ठाions
 * and thus needs the MMCRA_SAMPLE_ENABLE bit set, or 0 अगर not.
 */
अटल पूर्णांक घातer7_marked_instr_event(u64 event)
अणु
	पूर्णांक pmc, psel;
	पूर्णांक unit;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	psel = event & PM_PMCSEL_MSK & ~1;	/* trim off edge/level bit */
	अगर (pmc >= 5)
		वापस 0;

	चयन (psel >> 4) अणु
	हाल 2:
		वापस pmc == 2 || pmc == 4;
	हाल 3:
		अगर (psel == 0x3c)
			वापस pmc == 1;
		अगर (psel == 0x3e)
			वापस pmc != 2;
		वापस 1;
	हाल 4:
	हाल 5:
		वापस unit == 0xd;
	हाल 6:
		अगर (psel == 0x64)
			वापस pmc >= 3;
		अवरोध;
	हाल 8:
		वापस unit == 0xd;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक घातer7_compute_mmcr(u64 event[], पूर्णांक n_ev,
			       अचिन्हित पूर्णांक hwc[], काष्ठा mmcr_regs *mmcr,
			       काष्ठा perf_event *pevents[],
			       u32 flags __maybe_unused)
अणु
	अचिन्हित दीर्घ mmcr1 = 0;
	अचिन्हित दीर्घ mmcra = MMCRA_SDAR_DCACHE_MISS | MMCRA_SDAR_ERAT_MISS;
	अचिन्हित पूर्णांक pmc, unit, combine, l2sel, psel;
	अचिन्हित पूर्णांक pmc_inuse = 0;
	पूर्णांक i;

	/* First pass to count resource use */
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		अगर (pmc) अणु
			अगर (pmc > 6)
				वापस -1;
			अगर (pmc_inuse & (1 << (pmc - 1)))
				वापस -1;
			pmc_inuse |= 1 << (pmc - 1);
		पूर्ण
	पूर्ण

	/* Second pass: assign PMCs, set all MMCR1 fields */
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		combine = (event[i] >> PM_COMBINE_SH) & PM_COMBINE_MSK;
		l2sel = (event[i] >> PM_L2SEL_SH) & PM_L2SEL_MSK;
		psel = event[i] & PM_PMCSEL_MSK;
		अगर (!pmc) अणु
			/* Bus event or any-PMC direct event */
			क्रम (pmc = 0; pmc < 4; ++pmc) अणु
				अगर (!(pmc_inuse & (1 << pmc)))
					अवरोध;
			पूर्ण
			अगर (pmc >= 4)
				वापस -1;
			pmc_inuse |= 1 << pmc;
		पूर्ण अन्यथा अणु
			/* Direct or decoded event */
			--pmc;
		पूर्ण
		अगर (pmc <= 3) अणु
			mmcr1 |= (अचिन्हित दीर्घ) unit
				<< (MMCR1_TTM0SEL_SH - 4 * pmc);
			mmcr1 |= (अचिन्हित दीर्घ) combine
				<< (MMCR1_PMC1_COMBINE_SH - pmc);
			mmcr1 |= psel << MMCR1_PMCSEL_SH(pmc);
			अगर (unit == 6)	/* L2 events */
				mmcr1 |= (अचिन्हित दीर्घ) l2sel
					<< MMCR1_L2SEL_SH;
		पूर्ण
		अगर (घातer7_marked_instr_event(event[i]))
			mmcra |= MMCRA_SAMPLE_ENABLE;
		hwc[i] = pmc;
	पूर्ण

	/* Return MMCRx values */
	mmcr->mmcr0 = 0;
	अगर (pmc_inuse & 1)
		mmcr->mmcr0 = MMCR0_PMC1CE;
	अगर (pmc_inuse & 0x3e)
		mmcr->mmcr0 |= MMCR0_PMCjCE;
	mmcr->mmcr1 = mmcr1;
	mmcr->mmcra = mmcra;
	वापस 0;
पूर्ण

अटल व्योम घातer7_disable_pmc(अचिन्हित पूर्णांक pmc, काष्ठा mmcr_regs *mmcr)
अणु
	अगर (pmc <= 3)
		mmcr->mmcr1 &= ~(0xffUL << MMCR1_PMCSEL_SH(pmc));
पूर्ण

अटल पूर्णांक घातer7_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] =			PM_CYC,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] =	PM_GCT_NOSLOT_CYC,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] =	PM_CMPLU_STALL,
	[PERF_COUNT_HW_INSTRUCTIONS] =			PM_INST_CMPL,
	[PERF_COUNT_HW_CACHE_REFERENCES] =		PM_LD_REF_L1,
	[PERF_COUNT_HW_CACHE_MISSES] =			PM_LD_MISS_L1,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] =		PM_BRU_FIN,
	[PERF_COUNT_HW_BRANCH_MISSES] =			PM_BR_MPRED,
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 */
अटल u64 घातer7_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0xc880,		0x400f0	पूर्ण,
		[C(OP_WRITE)] = अणु	0,		0x300f0	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0xd8b8,		0	पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x200fc	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0x408a,		0	पूर्ण,
	पूर्ण,
	[C(LL)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x16080,	0x26080	पूर्ण,
		[C(OP_WRITE)] = अणु	0x16082,	0x26082	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0,		0	पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x300fc	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x400fc	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x10068,	0x400f6	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	-1,		-1	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
पूर्ण;


GENERIC_EVENT_ATTR(cpu-cycles,			PM_CYC);
GENERIC_EVENT_ATTR(stalled-cycles-frontend,	PM_GCT_NOSLOT_CYC);
GENERIC_EVENT_ATTR(stalled-cycles-backend,	PM_CMPLU_STALL);
GENERIC_EVENT_ATTR(inकाष्ठाions,		PM_INST_CMPL);
GENERIC_EVENT_ATTR(cache-references,		PM_LD_REF_L1);
GENERIC_EVENT_ATTR(cache-misses,		PM_LD_MISS_L1);
GENERIC_EVENT_ATTR(branch-inकाष्ठाions,		PM_BRU_FIN);
GENERIC_EVENT_ATTR(branch-misses,		PM_BR_MPRED);

#घोषणा EVENT(_name, _code)     POWER_EVENT_ATTR(_name, _name);
#समावेश "power7-events-list.h"
#अघोषित EVENT

#घोषणा EVENT(_name, _code)     POWER_EVENT_PTR(_name),

अटल काष्ठा attribute *घातer7_events_attr[] = अणु
	GENERIC_EVENT_PTR(PM_CYC),
	GENERIC_EVENT_PTR(PM_GCT_NOSLOT_CYC),
	GENERIC_EVENT_PTR(PM_CMPLU_STALL),
	GENERIC_EVENT_PTR(PM_INST_CMPL),
	GENERIC_EVENT_PTR(PM_LD_REF_L1),
	GENERIC_EVENT_PTR(PM_LD_MISS_L1),
	GENERIC_EVENT_PTR(PM_BRU_FIN),
	GENERIC_EVENT_PTR(PM_BR_MPRED),

	#समावेश "power7-events-list.h"
	#अघोषित EVENT
	शून्य
पूर्ण;

अटल काष्ठा attribute_group घातer7_pmu_events_group = अणु
	.name = "events",
	.attrs = घातer7_events_attr,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-19");

अटल काष्ठा attribute *घातer7_pmu_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group घातer7_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = घातer7_pmu_क्रमmat_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *घातer7_pmu_attr_groups[] = अणु
	&घातer7_pmu_क्रमmat_group,
	&घातer7_pmu_events_group,
	शून्य,
पूर्ण;

अटल काष्ठा घातer_pmu घातer7_pmu = अणु
	.name			= "POWER7",
	.n_counter		= 6,
	.max_alternatives	= MAX_ALT + 1,
	.add_fields		= 0x1555ul,
	.test_adder		= 0x3000ul,
	.compute_mmcr		= घातer7_compute_mmcr,
	.get_स्थिरraपूर्णांक		= घातer7_get_स्थिरraपूर्णांक,
	.get_alternatives	= घातer7_get_alternatives,
	.disable_pmc		= घातer7_disable_pmc,
	.flags			= PPMU_ALT_SIPR,
	.attr_groups		= घातer7_pmu_attr_groups,
	.n_generic		= ARRAY_SIZE(घातer7_generic_events),
	.generic_events		= घातer7_generic_events,
	.cache_events		= &घातer7_cache_events,
पूर्ण;

पूर्णांक init_घातer7_pmu(व्योम)
अणु
	अगर (!cur_cpu_spec->oprofile_cpu_type ||
	    म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/power7"))
		वापस -ENODEV;

	अगर (pvr_version_is(PVR_POWER7p))
		घातer7_pmu.flags |= PPMU_SIAR_VALID;

	वापस रेजिस्टर_घातer_pmu(&घातer7_pmu);
पूर्ण
