<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux perक्रमmance counter support क्रम ARC
 *
 * Copyright (C) 2014-2015 Synopsys, Inc. (www.synopsys.com)
 * Copyright (C) 2011-2013 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_PERF_EVENT_H
#घोषणा __ASM_PERF_EVENT_H

/* Max number of counters that PCT block may ever have */
#घोषणा ARC_PERF_MAX_COUNTERS	32

#घोषणा ARC_REG_CC_BUILD	0xF6
#घोषणा ARC_REG_CC_INDEX	0x240
#घोषणा ARC_REG_CC_NAME0	0x241
#घोषणा ARC_REG_CC_NAME1	0x242

#घोषणा ARC_REG_PCT_BUILD	0xF5
#घोषणा ARC_REG_PCT_COUNTL	0x250
#घोषणा ARC_REG_PCT_COUNTH	0x251
#घोषणा ARC_REG_PCT_SNAPL	0x252
#घोषणा ARC_REG_PCT_SNAPH	0x253
#घोषणा ARC_REG_PCT_CONFIG	0x254
#घोषणा ARC_REG_PCT_CONTROL	0x255
#घोषणा ARC_REG_PCT_INDEX	0x256
#घोषणा ARC_REG_PCT_INT_CNTL	0x25C
#घोषणा ARC_REG_PCT_INT_CNTH	0x25D
#घोषणा ARC_REG_PCT_INT_CTRL	0x25E
#घोषणा ARC_REG_PCT_INT_ACT	0x25F

#घोषणा ARC_REG_PCT_CONFIG_USER	(1 << 18)	/* count in user mode */
#घोषणा ARC_REG_PCT_CONFIG_KERN	(1 << 19)	/* count in kernel mode */

#घोषणा ARC_REG_PCT_CONTROL_CC	(1 << 16)	/* clear counts */
#घोषणा ARC_REG_PCT_CONTROL_SN	(1 << 17)	/* snapshot */

काष्ठा arc_reg_pct_build अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक m:8, c:8, r:5, i:1, s:2, v:8;
#अन्यथा
	अचिन्हित पूर्णांक v:8, s:2, i:1, r:5, c:8, m:8;
#पूर्ण_अगर
पूर्ण;

काष्ठा arc_reg_cc_build अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक c:16, r:8, v:8;
#अन्यथा
	अचिन्हित पूर्णांक v:8, r:8, c:16;
#पूर्ण_अगर
पूर्ण;

#घोषणा PERF_COUNT_ARC_DCLM	(PERF_COUNT_HW_MAX + 0)
#घोषणा PERF_COUNT_ARC_DCSM	(PERF_COUNT_HW_MAX + 1)
#घोषणा PERF_COUNT_ARC_ICM	(PERF_COUNT_HW_MAX + 2)
#घोषणा PERF_COUNT_ARC_BPOK	(PERF_COUNT_HW_MAX + 3)
#घोषणा PERF_COUNT_ARC_EDTLB	(PERF_COUNT_HW_MAX + 4)
#घोषणा PERF_COUNT_ARC_EITLB	(PERF_COUNT_HW_MAX + 5)
#घोषणा PERF_COUNT_ARC_LDC	(PERF_COUNT_HW_MAX + 6)
#घोषणा PERF_COUNT_ARC_STC	(PERF_COUNT_HW_MAX + 7)

#घोषणा PERF_COUNT_ARC_HW_MAX	(PERF_COUNT_HW_MAX + 8)

/*
 * Some ARC pct quirks:
 *
 * PERF_COUNT_HW_STALLED_CYCLES_BACKEND
 * PERF_COUNT_HW_STALLED_CYCLES_FRONTEND
 *	The ARC 700 can either measure stalls per pipeline stage, or all stalls
 *	combined; क्रम now we assign all stalls to STALLED_CYCLES_BACKEND
 *	and all pipeline flushes (e.g. caused by mispredicts, etc.) to
 *	STALLED_CYCLES_FRONTEND.
 *
 *	We could start multiple perक्रमmance counters and combine everything
 *	afterwards, but that makes it complicated.
 *
 *	Note that I$ cache misses aren't counted by either of the two!
 */

/*
 * ARC PCT has hardware conditions with fixed "names" but variable "indexes"
 * (based on a specअगरic RTL build)
 * Below is the अटल map between perf generic/arc specअगरic event_id and
 * h/w condition names.
 * At the समय of probe, we loop thru each index and find it's name to
 * complete the mapping of perf event_id to h/w index as latter is needed
 * to program the counter really
 */
अटल स्थिर अक्षर * स्थिर arc_pmu_ev_hw_map[] = अणु
	/* count cycles */
	[PERF_COUNT_HW_CPU_CYCLES] = "crun",
	[PERF_COUNT_HW_REF_CPU_CYCLES] = "crun",
	[PERF_COUNT_HW_BUS_CYCLES] = "crun",

	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND] = "bflush",
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND] = "bstall",

	/* counts condition */
	[PERF_COUNT_HW_INSTRUCTIONS] = "iall",
	/* All jump inकाष्ठाions that are taken */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = "ijmptak",
#अगर_घोषित CONFIG_ISA_ARCV2
	[PERF_COUNT_HW_BRANCH_MISSES] = "bpmp",
#अन्यथा
	[PERF_COUNT_ARC_BPOK]         = "bpok",	  /* NP-NT, PT-T, PNT-NT */
	[PERF_COUNT_HW_BRANCH_MISSES] = "bpfail", /* NP-T, PT-NT, PNT-T */
#पूर्ण_अगर
	[PERF_COUNT_ARC_LDC] = "imemrdc",	/* Instr: mem पढ़ो cached */
	[PERF_COUNT_ARC_STC] = "imemwrc",	/* Instr: mem ग_लिखो cached */

	[PERF_COUNT_ARC_DCLM] = "dclm",		/* D-cache Load Miss */
	[PERF_COUNT_ARC_DCSM] = "dcsm",		/* D-cache Store Miss */
	[PERF_COUNT_ARC_ICM] = "icm",		/* I-cache Miss */
	[PERF_COUNT_ARC_EDTLB] = "edtlb",	/* D-TLB Miss */
	[PERF_COUNT_ARC_EITLB] = "eitlb",	/* I-TLB Miss */

	[PERF_COUNT_HW_CACHE_REFERENCES] = "imemrdc",	/* Instr: mem पढ़ो cached */
	[PERF_COUNT_HW_CACHE_MISSES] = "dclm",		/* D-cache Load Miss */
पूर्ण;

#घोषणा C(_x)			PERF_COUNT_HW_CACHE_##_x
#घोषणा CACHE_OP_UNSUPPORTED	0xffff

अटल स्थिर अचिन्हित arc_pmu_cache_map[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= PERF_COUNT_ARC_LDC,
			[C(RESULT_MISS)]	= PERF_COUNT_ARC_DCLM,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= PERF_COUNT_ARC_STC,
			[C(RESULT_MISS)]	= PERF_COUNT_ARC_DCSM,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= PERF_COUNT_HW_INSTRUCTIONS,
			[C(RESULT_MISS)]	= PERF_COUNT_ARC_ICM,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= PERF_COUNT_ARC_LDC,
			[C(RESULT_MISS)]	= PERF_COUNT_ARC_EDTLB,
		पूर्ण,
			/* DTLB LD/ST Miss not segregated by h/w*/
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= PERF_COUNT_ARC_EITLB,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = PERF_COUNT_HW_BRANCH_INSTRUCTIONS,
			[C(RESULT_MISS)]	= PERF_COUNT_HW_BRANCH_MISSES,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
पूर्ण;

#पूर्ण_अगर /* __ASM_PERF_EVENT_H */
