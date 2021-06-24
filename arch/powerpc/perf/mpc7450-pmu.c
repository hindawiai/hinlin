<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter support क्रम MPC7450-family processors.
 *
 * Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 */
#समावेश <linux/माला.स>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>

#घोषणा N_COUNTER	6	/* Number of hardware counters */
#घोषणा MAX_ALT		3	/* Maximum number of event alternative codes */

/*
 * Bits in event code क्रम MPC7450 family
 */
#घोषणा PM_THRMULT_MSKS	0x40000
#घोषणा PM_THRESH_SH	12
#घोषणा PM_THRESH_MSK	0x3f
#घोषणा PM_PMC_SH	8
#घोषणा PM_PMC_MSK	7
#घोषणा PM_PMCSEL_MSK	0x7f

/*
 * Classअगरy events according to how specअगरic their PMC requirements are.
 * Result is:
 *	0: can go on any PMC
 *	1: can go on PMCs 1-4
 *	2: can go on PMCs 1,2,4
 *	3: can go on PMCs 1 or 2
 *	4: can only go on one PMC
 *	-1: event code is invalid
 */
#घोषणा N_CLASSES	5

अटल पूर्णांक mpc7450_classअगरy_event(u32 event)
अणु
	पूर्णांक pmc;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	अगर (pmc) अणु
		अगर (pmc > N_COUNTER)
			वापस -1;
		वापस 4;
	पूर्ण
	event &= PM_PMCSEL_MSK;
	अगर (event <= 1)
		वापस 0;
	अगर (event <= 7)
		वापस 1;
	अगर (event <= 13)
		वापस 2;
	अगर (event <= 22)
		वापस 3;
	वापस -1;
पूर्ण

/*
 * Events using threshold and possible threshold scale:
 *	code	scale?	name
 *	11e	N	PM_INSTQ_EXCEED_CYC
 *	11f	N	PM_ALTV_IQ_EXCEED_CYC
 *	128	Y	PM_DTLB_SEARCH_EXCEED_CYC
 *	12b	Y	PM_LD_MISS_EXCEED_L1_CYC
 *	220	N	PM_CQ_EXCEED_CYC
 *	30c	N	PM_GPR_RB_EXCEED_CYC
 *	30d	?	PM_FPR_IQ_EXCEED_CYC ?
 *	311	Y	PM_ITLB_SEARCH_EXCEED
 *	410	N	PM_GPR_IQ_EXCEED_CYC
 */

/*
 * Return use of threshold and threshold scale bits:
 * 0 = uses neither, 1 = uses threshold, 2 = uses both
 */
अटल पूर्णांक mpc7450_threshold_use(u32 event)
अणु
	पूर्णांक pmc, sel;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	sel = event & PM_PMCSEL_MSK;
	चयन (pmc) अणु
	हाल 1:
		अगर (sel == 0x1e || sel == 0x1f)
			वापस 1;
		अगर (sel == 0x28 || sel == 0x2b)
			वापस 2;
		अवरोध;
	हाल 2:
		अगर (sel == 0x20)
			वापस 1;
		अवरोध;
	हाल 3:
		अगर (sel == 0xc || sel == 0xd)
			वापस 1;
		अगर (sel == 0x11)
			वापस 2;
		अवरोध;
	हाल 4:
		अगर (sel == 0x10)
			वापस 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Layout of स्थिरraपूर्णांक bits:
 * 33222222222211111111110000000000
 * 10987654321098765432109876543210
 *  |<    ><  > < > < ><><><><><><>
 *  TS TV   G4   G3  G2P6P5P4P3P2P1
 *
 * P1 - P6
 *	0 - 11: Count of events needing PMC1 .. PMC6
 *
 * G2
 *	12 - 14: Count of events needing PMC1 or PMC2
 *
 * G3
 *	16 - 18: Count of events needing PMC1, PMC2 or PMC4
 *
 * G4
 *	20 - 23: Count of events needing PMC1, PMC2, PMC3 or PMC4
 *
 * TV
 *	24 - 29: Threshold value requested
 *
 * TS
 *	30: Threshold scale value requested
 */

अटल u32 pmcbits[N_COUNTER][2] = अणु
	अणु 0x00844002, 0x00111001 पूर्ण,	/* PMC1 mask, value: P1,G2,G3,G4 */
	अणु 0x00844008, 0x00111004 पूर्ण,	/* PMC2: P2,G2,G3,G4 */
	अणु 0x00800020, 0x00100010 पूर्ण,	/* PMC3: P3,G4 */
	अणु 0x00840080, 0x00110040 पूर्ण,	/* PMC4: P4,G3,G4 */
	अणु 0x00000200, 0x00000100 पूर्ण,	/* PMC5: P5 */
	अणु 0x00000800, 0x00000400 पूर्ण	/* PMC6: P6 */
पूर्ण;

अटल u32 classbits[N_CLASSES - 1][2] = अणु
	अणु 0x00000000, 0x00000000 पूर्ण,	/* class 0: no स्थिरraपूर्णांक */
	अणु 0x00800000, 0x00100000 पूर्ण,	/* class 1: G4 */
	अणु 0x00040000, 0x00010000 पूर्ण,	/* class 2: G3 */
	अणु 0x00004000, 0x00001000 पूर्ण,	/* class 3: G2 */
पूर्ण;

अटल पूर्णांक mpc7450_get_स्थिरraपूर्णांक(u64 event, अचिन्हित दीर्घ *maskp,
				  अचिन्हित दीर्घ *valp, u64 event_config1 __maybe_unused)
अणु
	पूर्णांक pmc, class;
	u32 mask, value;
	पूर्णांक thresh, tuse;

	class = mpc7450_classअगरy_event(event);
	अगर (class < 0)
		वापस -1;
	अगर (class == 4) अणु
		pmc = ((अचिन्हित पूर्णांक)event >> PM_PMC_SH) & PM_PMC_MSK;
		mask  = pmcbits[pmc - 1][0];
		value = pmcbits[pmc - 1][1];
	पूर्ण अन्यथा अणु
		mask  = classbits[class][0];
		value = classbits[class][1];
	पूर्ण

	tuse = mpc7450_threshold_use(event);
	अगर (tuse) अणु
		thresh = ((अचिन्हित पूर्णांक)event >> PM_THRESH_SH) & PM_THRESH_MSK;
		mask  |= 0x3f << 24;
		value |= thresh << 24;
		अगर (tuse == 2) अणु
			mask |= 0x40000000;
			अगर ((अचिन्हित पूर्णांक)event & PM_THRMULT_MSKS)
				value |= 0x40000000;
		पूर्ण
	पूर्ण

	*maskp = mask;
	*valp = value;
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक event_alternatives[][MAX_ALT] = अणु
	अणु 0x217, 0x317 पूर्ण,		/* PM_L1_DCACHE_MISS */
	अणु 0x418, 0x50f, 0x60f पूर्ण,	/* PM_SNOOP_RETRY */
	अणु 0x502, 0x602 पूर्ण,		/* PM_L2_HIT */
	अणु 0x503, 0x603 पूर्ण,		/* PM_L3_HIT */
	अणु 0x504, 0x604 पूर्ण,		/* PM_L2_ICACHE_MISS */
	अणु 0x505, 0x605 पूर्ण,		/* PM_L3_ICACHE_MISS */
	अणु 0x506, 0x606 पूर्ण,		/* PM_L2_DCACHE_MISS */
	अणु 0x507, 0x607 पूर्ण,		/* PM_L3_DCACHE_MISS */
	अणु 0x50a, 0x623 पूर्ण,		/* PM_LD_HIT_L3 */
	अणु 0x50b, 0x624 पूर्ण,		/* PM_ST_HIT_L3 */
	अणु 0x50d, 0x60d पूर्ण,		/* PM_L2_TOUCH_HIT */
	अणु 0x50e, 0x60e पूर्ण,		/* PM_L3_TOUCH_HIT */
	अणु 0x512, 0x612 पूर्ण,		/* PM_INT_LOCAL */
	अणु 0x513, 0x61d पूर्ण,		/* PM_L2_MISS */
	अणु 0x514, 0x61e पूर्ण,		/* PM_L3_MISS */
पूर्ण;

/*
 * Scan the alternatives table क्रम a match and वापस the
 * index पूर्णांकo the alternatives table अगर found, अन्यथा -1.
 */
अटल पूर्णांक find_alternative(u32 event)
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

अटल पूर्णांक mpc7450_get_alternatives(u64 event, अचिन्हित पूर्णांक flags, u64 alt[])
अणु
	पूर्णांक i, j, nalt = 1;
	u32 ae;

	alt[0] = event;
	nalt = 1;
	i = find_alternative((u32)event);
	अगर (i >= 0) अणु
		क्रम (j = 0; j < MAX_ALT; ++j) अणु
			ae = event_alternatives[i][j];
			अगर (ae && ae != (u32)event)
				alt[nalt++] = ae;
		पूर्ण
	पूर्ण
	वापस nalt;
पूर्ण

/*
 * Biपंचांगaps of which PMCs each class can use क्रम classes 0 - 3.
 * Bit i is set अगर PMC i+1 is usable.
 */
अटल स्थिर u8 classmap[N_CLASSES] = अणु
	0x3f, 0x0f, 0x0b, 0x03, 0
पूर्ण;

/* Bit position and width of each PMCSEL field */
अटल स्थिर पूर्णांक pmcsel_shअगरt[N_COUNTER] = अणु
	6,	0,	27,	22,	17,	11
पूर्ण;
अटल स्थिर u32 pmcsel_mask[N_COUNTER] = अणु
	0x7f,	0x3f,	0x1f,	0x1f,	0x1f,	0x3f
पूर्ण;

/*
 * Compute MMCR0/1/2 values क्रम a set of events.
 */
अटल पूर्णांक mpc7450_compute_mmcr(u64 event[], पूर्णांक n_ev, अचिन्हित पूर्णांक hwc[],
				काष्ठा mmcr_regs *mmcr,
				काष्ठा perf_event *pevents[],
				u32 flags __maybe_unused)
अणु
	u8 event_index[N_CLASSES][N_COUNTER];
	पूर्णांक n_classevent[N_CLASSES];
	पूर्णांक i, j, class, tuse;
	u32 pmc_inuse = 0, pmc_avail;
	u32 mmcr0 = 0, mmcr1 = 0, mmcr2 = 0;
	u32 ev, pmc, thresh;

	अगर (n_ev > N_COUNTER)
		वापस -1;

	/* First pass: count usage in each class */
	क्रम (i = 0; i < N_CLASSES; ++i)
		n_classevent[i] = 0;
	क्रम (i = 0; i < n_ev; ++i) अणु
		class = mpc7450_classअगरy_event(event[i]);
		अगर (class < 0)
			वापस -1;
		j = n_classevent[class]++;
		event_index[class][j] = i;
	पूर्ण

	/* Second pass: allocate PMCs from most specअगरic event to least */
	क्रम (class = N_CLASSES - 1; class >= 0; --class) अणु
		क्रम (i = 0; i < n_classevent[class]; ++i) अणु
			ev = event[event_index[class][i]];
			अगर (class == 4) अणु
				pmc = (ev >> PM_PMC_SH) & PM_PMC_MSK;
				अगर (pmc_inuse & (1 << (pmc - 1)))
					वापस -1;
			पूर्ण अन्यथा अणु
				/* Find a suitable PMC */
				pmc_avail = classmap[class] & ~pmc_inuse;
				अगर (!pmc_avail)
					वापस -1;
				pmc = ffs(pmc_avail);
			पूर्ण
			pmc_inuse |= 1 << (pmc - 1);

			tuse = mpc7450_threshold_use(ev);
			अगर (tuse) अणु
				thresh = (ev >> PM_THRESH_SH) & PM_THRESH_MSK;
				mmcr0 |= thresh << 16;
				अगर (tuse == 2 && (ev & PM_THRMULT_MSKS))
					mmcr2 = 0x80000000;
			पूर्ण
			ev &= pmcsel_mask[pmc - 1];
			ev <<= pmcsel_shअगरt[pmc - 1];
			अगर (pmc <= 2)
				mmcr0 |= ev;
			अन्यथा
				mmcr1 |= ev;
			hwc[event_index[class][i]] = pmc - 1;
		पूर्ण
	पूर्ण

	अगर (pmc_inuse & 1)
		mmcr0 |= MMCR0_PMC1CE;
	अगर (pmc_inuse & 0x3e)
		mmcr0 |= MMCR0_PMCnCE;

	/* Return MMCRx values */
	mmcr->mmcr0 = mmcr0;
	mmcr->mmcr1 = mmcr1;
	mmcr->mmcr2 = mmcr2;
	/*
	 * 32-bit करोesn't have an MMCRA and uses SPRN_MMCR2 to define
	 * SPRN_MMCRA. So assign mmcra of cpu_hw_events with `mmcr2`
	 * value to ensure that any ग_लिखो to this SPRN_MMCRA will
	 * use mmcr2 value.
	 */
	mmcr->mmcra = mmcr2;
	वापस 0;
पूर्ण

/*
 * Disable counting by a PMC.
 * Note that the pmc argument is 0-based here, not 1-based.
 */
अटल व्योम mpc7450_disable_pmc(अचिन्हित पूर्णांक pmc, काष्ठा mmcr_regs *mmcr)
अणु
	अगर (pmc <= 1)
		mmcr->mmcr0 &= ~(pmcsel_mask[pmc] << pmcsel_shअगरt[pmc]);
	अन्यथा
		mmcr->mmcr1 &= ~(pmcsel_mask[pmc] << pmcsel_shअगरt[pmc]);
पूर्ण

अटल पूर्णांक mpc7450_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 1,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 2,
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x217, /* PM_L1_DCACHE_MISS */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x122, /* PM_BR_CMPL */
	[PERF_COUNT_HW_BRANCH_MISSES] 		= 0x41c, /* PM_BR_MPRED */
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 */
अटल u64 mpc7450_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x225	पूर्ण,
		[C(OP_WRITE)] = अणु	0,		0x227	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0,		0	पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x129,		0x115	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0x634,		0	पूर्ण,
	पूर्ण,
	[C(LL)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0	पूर्ण,
		[C(OP_WRITE)] = अणु	0,		0	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0,		0	पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x312	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x223	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x122,		0x41c	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	-1,		-1	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा घातer_pmu mpc7450_pmu = अणु
	.name			= "MPC7450 family",
	.n_counter		= N_COUNTER,
	.max_alternatives	= MAX_ALT,
	.add_fields		= 0x00111555ul,
	.test_adder		= 0x00301000ul,
	.compute_mmcr		= mpc7450_compute_mmcr,
	.get_स्थिरraपूर्णांक		= mpc7450_get_स्थिरraपूर्णांक,
	.get_alternatives	= mpc7450_get_alternatives,
	.disable_pmc		= mpc7450_disable_pmc,
	.n_generic		= ARRAY_SIZE(mpc7450_generic_events),
	.generic_events		= mpc7450_generic_events,
	.cache_events		= &mpc7450_cache_events,
पूर्ण;

अटल पूर्णांक __init init_mpc7450_pmu(व्योम)
अणु
	अगर (!cur_cpu_spec->oprofile_cpu_type ||
	    म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc/7450"))
		वापस -ENODEV;

	वापस रेजिस्टर_घातer_pmu(&mpc7450_pmu);
पूर्ण

early_initcall(init_mpc7450_pmu);
