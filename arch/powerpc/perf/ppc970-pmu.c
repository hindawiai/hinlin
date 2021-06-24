<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter support क्रम PPC970-family processors.
 *
 * Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 */
#समावेश <linux/माला.स>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>

#समावेश "internal.h"

/*
 * Bits in event code क्रम PPC970
 */
#घोषणा PM_PMC_SH	12	/* PMC number (1-based) क्रम direct events */
#घोषणा PM_PMC_MSK	0xf
#घोषणा PM_UNIT_SH	8	/* TTMMUX number and setting - unit select */
#घोषणा PM_UNIT_MSK	0xf
#घोषणा PM_SPCSEL_SH	6
#घोषणा PM_SPCSEL_MSK	3
#घोषणा PM_BYTE_SH	4	/* Byte number of event bus to use */
#घोषणा PM_BYTE_MSK	3
#घोषणा PM_PMCSEL_MSK	0xf

/* Values in PM_UNIT field */
#घोषणा PM_NONE		0
#घोषणा PM_FPU		1
#घोषणा PM_VPU		2
#घोषणा PM_ISU		3
#घोषणा PM_IFU		4
#घोषणा PM_IDU		5
#घोषणा PM_STS		6
#घोषणा PM_LSU0		7
#घोषणा PM_LSU1U	8
#घोषणा PM_LSU1L	9
#घोषणा PM_LASTUNIT	9

/*
 * Bits in MMCR0 क्रम PPC970
 */
#घोषणा MMCR0_PMC1SEL_SH	8
#घोषणा MMCR0_PMC2SEL_SH	1
#घोषणा MMCR_PMCSEL_MSK		0x1f

/*
 * Bits in MMCR1 क्रम PPC970
 */
#घोषणा MMCR1_TTM0SEL_SH	62
#घोषणा MMCR1_TTM1SEL_SH	59
#घोषणा MMCR1_TTM3SEL_SH	53
#घोषणा MMCR1_TTMSEL_MSK	3
#घोषणा MMCR1_TD_CP_DBG0SEL_SH	50
#घोषणा MMCR1_TD_CP_DBG1SEL_SH	48
#घोषणा MMCR1_TD_CP_DBG2SEL_SH	46
#घोषणा MMCR1_TD_CP_DBG3SEL_SH	44
#घोषणा MMCR1_PMC1_ADDER_SEL_SH	39
#घोषणा MMCR1_PMC2_ADDER_SEL_SH	38
#घोषणा MMCR1_PMC6_ADDER_SEL_SH	37
#घोषणा MMCR1_PMC5_ADDER_SEL_SH	36
#घोषणा MMCR1_PMC8_ADDER_SEL_SH	35
#घोषणा MMCR1_PMC7_ADDER_SEL_SH	34
#घोषणा MMCR1_PMC3_ADDER_SEL_SH	33
#घोषणा MMCR1_PMC4_ADDER_SEL_SH	32
#घोषणा MMCR1_PMC3SEL_SH	27
#घोषणा MMCR1_PMC4SEL_SH	22
#घोषणा MMCR1_PMC5SEL_SH	17
#घोषणा MMCR1_PMC6SEL_SH	12
#घोषणा MMCR1_PMC7SEL_SH	7
#घोषणा MMCR1_PMC8SEL_SH	2

अटल लघु mmcr1_adder_bits[8] = अणु
	MMCR1_PMC1_ADDER_SEL_SH,
	MMCR1_PMC2_ADDER_SEL_SH,
	MMCR1_PMC3_ADDER_SEL_SH,
	MMCR1_PMC4_ADDER_SEL_SH,
	MMCR1_PMC5_ADDER_SEL_SH,
	MMCR1_PMC6_ADDER_SEL_SH,
	MMCR1_PMC7_ADDER_SEL_SH,
	MMCR1_PMC8_ADDER_SEL_SH
पूर्ण;

/*
 * Layout of स्थिरraपूर्णांक bits:
 * 6666555555555544444444443333333333222222222211111111110000000000
 * 3210987654321098765432109876543210987654321098765432109876543210
 *               <><><>[  >[  >[  ><  ><  ><  ><  ><><><><><><><><>
 *               SPT0T1 UC  PS1 PS2 B0  B1  B2  B3 P1P2P3P4P5P6P7P8
 *
 * SP - SPCSEL स्थिरraपूर्णांक
 *     48-49: SPCSEL value 0x3_0000_0000_0000
 *
 * T0 - TTM0 स्थिरraपूर्णांक
 *     46-47: TTM0SEL value (0=FPU, 2=IFU, 3=VPU) 0xC000_0000_0000
 *
 * T1 - TTM1 स्थिरraपूर्णांक
 *     44-45: TTM1SEL value (0=IDU, 3=STS) 0x3000_0000_0000
 *
 * UC - unit स्थिरraपूर्णांक: can't have all three of FPU|IFU|VPU, ISU, IDU|STS
 *     43: UC3 error 0x0800_0000_0000
 *     42: FPU|IFU|VPU events needed 0x0400_0000_0000
 *     41: ISU events needed 0x0200_0000_0000
 *     40: IDU|STS events needed 0x0100_0000_0000
 *
 * PS1
 *     39: PS1 error 0x0080_0000_0000
 *     36-38: count of events needing PMC1/2/5/6 0x0070_0000_0000
 *
 * PS2
 *     35: PS2 error 0x0008_0000_0000
 *     32-34: count of events needing PMC3/4/7/8 0x0007_0000_0000
 *
 * B0
 *     28-31: Byte 0 event source 0xf000_0000
 *	      Encoding as क्रम the event code
 *
 * B1, B2, B3
 *     24-27, 20-23, 16-19: Byte 1, 2, 3 event sources
 *
 * P1
 *     15: P1 error 0x8000
 *     14-15: Count of events needing PMC1
 *
 * P2..P8
 *     0-13: Count of events needing PMC2..PMC8
 */

अटल अचिन्हित अक्षर direct_marked_event[8] = अणु
	(1<<2) | (1<<3),	/* PMC1: PM_MRK_GRP_DISP, PM_MRK_ST_CMPL */
	(1<<3) | (1<<5),	/* PMC2: PM_THRESH_TIMEO, PM_MRK_BRU_FIN */
	(1<<3) | (1<<5),	/* PMC3: PM_MRK_ST_CMPL_INT, PM_MRK_VMX_FIN */
	(1<<4) | (1<<5),	/* PMC4: PM_MRK_GRP_CMPL, PM_MRK_CRU_FIN */
	(1<<4) | (1<<5),	/* PMC5: PM_GRP_MRK, PM_MRK_GRP_TIMEO */
	(1<<3) | (1<<4) | (1<<5),
		/* PMC6: PM_MRK_ST_STS, PM_MRK_FXU_FIN, PM_MRK_GRP_ISSUED */
	(1<<4) | (1<<5),	/* PMC7: PM_MRK_FPU_FIN, PM_MRK_INST_FIN */
	(1<<4)			/* PMC8: PM_MRK_LSU_FIN */
पूर्ण;

/*
 * Returns 1 अगर event counts things relating to marked inकाष्ठाions
 * and thus needs the MMCRA_SAMPLE_ENABLE bit set, or 0 अगर not.
 */
अटल पूर्णांक p970_marked_instr_event(u64 event)
अणु
	पूर्णांक pmc, psel, unit, byte, bit;
	अचिन्हित पूर्णांक mask;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psel = event & PM_PMCSEL_MSK;
	अगर (pmc) अणु
		अगर (direct_marked_event[pmc - 1] & (1 << psel))
			वापस 1;
		अगर (psel == 0)		/* add events */
			bit = (pmc <= 4)? pmc - 1: 8 - pmc;
		अन्यथा अगर (psel == 7 || psel == 13)	/* decode events */
			bit = 4;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा
		bit = psel;

	byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	mask = 0;
	चयन (unit) अणु
	हाल PM_VPU:
		mask = 0x4c;		/* byte 0 bits 2,3,6 */
		अवरोध;
	हाल PM_LSU0:
		/* byte 2 bits 0,2,3,4,6; all of byte 1 */
		mask = 0x085dff00;
		अवरोध;
	हाल PM_LSU1L:
		mask = 0x50 << 24;	/* byte 3 bits 4,6 */
		अवरोध;
	पूर्ण
	वापस (mask >> (byte * 8 + bit)) & 1;
पूर्ण

/* Masks and values क्रम using events from the various units */
अटल अचिन्हित दीर्घ unit_cons[PM_LASTUNIT+1][2] = अणु
	[PM_FPU] =   अणु 0xc80000000000ull, 0x040000000000ull पूर्ण,
	[PM_VPU] =   अणु 0xc80000000000ull, 0xc40000000000ull पूर्ण,
	[PM_ISU] =   अणु 0x080000000000ull, 0x020000000000ull पूर्ण,
	[PM_IFU] =   अणु 0xc80000000000ull, 0x840000000000ull पूर्ण,
	[PM_IDU] =   अणु 0x380000000000ull, 0x010000000000ull पूर्ण,
	[PM_STS] =   अणु 0x380000000000ull, 0x310000000000ull पूर्ण,
पूर्ण;

अटल पूर्णांक p970_get_स्थिरraपूर्णांक(u64 event, अचिन्हित दीर्घ *maskp,
			       अचिन्हित दीर्घ *valp, u64 event_config1 __maybe_unused)
अणु
	पूर्णांक pmc, byte, unit, sh, spcsel;
	अचिन्हित दीर्घ mask = 0, value = 0;
	पूर्णांक grp = -1;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	अगर (pmc) अणु
		अगर (pmc > 8)
			वापस -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		value |= 1 << sh;
		grp = ((pmc - 1) >> 1) & 1;
	पूर्ण
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	अगर (unit) अणु
		अगर (unit > PM_LASTUNIT)
			वापस -1;
		mask |= unit_cons[unit][0];
		value |= unit_cons[unit][1];
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		/*
		 * Bus events on bytes 0 and 2 can be counted
		 * on PMC1/2/5/6; bytes 1 and 3 on PMC3/4/7/8.
		 */
		अगर (!pmc)
			grp = byte & 1;
		/* Set byte lane select field */
		mask  |= 0xfULL << (28 - 4 * byte);
		value |= (अचिन्हित दीर्घ)unit << (28 - 4 * byte);
	पूर्ण
	अगर (grp == 0) अणु
		/* increment PMC1/2/5/6 field */
		mask  |= 0x8000000000ull;
		value |= 0x1000000000ull;
	पूर्ण अन्यथा अगर (grp == 1) अणु
		/* increment PMC3/4/7/8 field */
		mask  |= 0x800000000ull;
		value |= 0x100000000ull;
	पूर्ण
	spcsel = (event >> PM_SPCSEL_SH) & PM_SPCSEL_MSK;
	अगर (spcsel) अणु
		mask  |= 3ull << 48;
		value |= (अचिन्हित दीर्घ)spcsel << 48;
	पूर्ण
	*maskp = mask;
	*valp = value;
	वापस 0;
पूर्ण

अटल पूर्णांक p970_get_alternatives(u64 event, अचिन्हित पूर्णांक flags, u64 alt[])
अणु
	alt[0] = event;

	/* 2 alternatives क्रम LSU empty */
	अगर (event == 0x2002 || event == 0x3002) अणु
		alt[1] = event ^ 0x1000;
		वापस 2;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक p970_compute_mmcr(u64 event[], पूर्णांक n_ev,
			     अचिन्हित पूर्णांक hwc[], काष्ठा mmcr_regs *mmcr,
			     काष्ठा perf_event *pevents[],
			     u32 flags __maybe_unused)
अणु
	अचिन्हित दीर्घ mmcr0 = 0, mmcr1 = 0, mmcra = 0;
	अचिन्हित पूर्णांक pmc, unit, byte, psel;
	अचिन्हित पूर्णांक tपंचांग, grp;
	अचिन्हित पूर्णांक pmc_inuse = 0;
	अचिन्हित पूर्णांक pmc_grp_use[2];
	अचिन्हित अक्षर busbyte[4];
	अचिन्हित अक्षर unituse[16];
	अचिन्हित अक्षर uniपंचांगap[] = अणु 0, 0<<3, 3<<3, 1<<3, 2<<3, 0|4, 3|4 पूर्ण;
	अचिन्हित अक्षर tपंचांगuse[2];
	अचिन्हित अक्षर pmcsel[8];
	पूर्णांक i;
	पूर्णांक spcsel;

	अगर (n_ev > 8)
		वापस -1;

	/* First pass to count resource use */
	pmc_grp_use[0] = pmc_grp_use[1] = 0;
	स_रखो(busbyte, 0, माप(busbyte));
	स_रखो(unituse, 0, माप(unituse));
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		अगर (pmc) अणु
			अगर (pmc_inuse & (1 << (pmc - 1)))
				वापस -1;
			pmc_inuse |= 1 << (pmc - 1);
			/* count 1/2/5/6 vs 3/4/7/8 use */
			++pmc_grp_use[((pmc - 1) >> 1) & 1];
		पूर्ण
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
		अगर (unit) अणु
			अगर (unit > PM_LASTUNIT)
				वापस -1;
			अगर (!pmc)
				++pmc_grp_use[byte & 1];
			अगर (busbyte[byte] && busbyte[byte] != unit)
				वापस -1;
			busbyte[byte] = unit;
			unituse[unit] = 1;
		पूर्ण
	पूर्ण
	अगर (pmc_grp_use[0] > 4 || pmc_grp_use[1] > 4)
		वापस -1;

	/*
	 * Assign resources and set multiplexer selects.
	 *
	 * PM_ISU can go either on TTM0 or TTM1, but that's the only
	 * choice we have to deal with.
	 */
	अगर (unituse[PM_ISU] &
	    (unituse[PM_FPU] | unituse[PM_IFU] | unituse[PM_VPU]))
		uniपंचांगap[PM_ISU] = 2 | 4;	/* move ISU to TTM1 */
	/* Set TTM[01]SEL fields. */
	tपंचांगuse[0] = tपंचांगuse[1] = 0;
	क्रम (i = PM_FPU; i <= PM_STS; ++i) अणु
		अगर (!unituse[i])
			जारी;
		tपंचांग = uniपंचांगap[i];
		++tपंचांगuse[(tपंचांग >> 2) & 1];
		mmcr1 |= (अचिन्हित दीर्घ)(tपंचांग & ~4) << MMCR1_TTM1SEL_SH;
	पूर्ण
	/* Check only one unit per TTMx */
	अगर (tपंचांगuse[0] > 1 || tपंचांगuse[1] > 1)
		वापस -1;

	/* Set byte lane select fields and TTM3SEL. */
	क्रम (byte = 0; byte < 4; ++byte) अणु
		unit = busbyte[byte];
		अगर (!unit)
			जारी;
		अगर (unit <= PM_STS)
			tपंचांग = (uniपंचांगap[unit] >> 2) & 1;
		अन्यथा अगर (unit == PM_LSU0)
			tपंचांग = 2;
		अन्यथा अणु
			tपंचांग = 3;
			अगर (unit == PM_LSU1L && byte >= 2)
				mmcr1 |= 1ull << (MMCR1_TTM3SEL_SH + 3 - byte);
		पूर्ण
		mmcr1 |= (अचिन्हित दीर्घ)tपंचांग
			<< (MMCR1_TD_CP_DBG0SEL_SH - 2 * byte);
	पूर्ण

	/* Second pass: assign PMCs, set PMCxSEL and PMCx_ADDER_SEL fields */
	स_रखो(pmcsel, 0x8, माप(pmcsel));	/* 8 means करोn't count */
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
		psel = event[i] & PM_PMCSEL_MSK;
		अगर (!pmc) अणु
			/* Bus event or any-PMC direct event */
			अगर (unit)
				psel |= 0x10 | ((byte & 2) << 2);
			अन्यथा
				psel |= 8;
			क्रम (pmc = 0; pmc < 8; ++pmc) अणु
				अगर (pmc_inuse & (1 << pmc))
					जारी;
				grp = (pmc >> 1) & 1;
				अगर (unit) अणु
					अगर (grp == (byte & 1))
						अवरोध;
				पूर्ण अन्यथा अगर (pmc_grp_use[grp] < 4) अणु
					++pmc_grp_use[grp];
					अवरोध;
				पूर्ण
			पूर्ण
			pmc_inuse |= 1 << pmc;
		पूर्ण अन्यथा अणु
			/* Direct event */
			--pmc;
			अगर (psel == 0 && (byte & 2))
				/* add events on higher-numbered bus */
				mmcr1 |= 1ull << mmcr1_adder_bits[pmc];
		पूर्ण
		pmcsel[pmc] = psel;
		hwc[i] = pmc;
		spcsel = (event[i] >> PM_SPCSEL_SH) & PM_SPCSEL_MSK;
		mmcr1 |= spcsel;
		अगर (p970_marked_instr_event(event[i]))
			mmcra |= MMCRA_SAMPLE_ENABLE;
	पूर्ण
	क्रम (pmc = 0; pmc < 2; ++pmc)
		mmcr0 |= pmcsel[pmc] << (MMCR0_PMC1SEL_SH - 7 * pmc);
	क्रम (; pmc < 8; ++pmc)
		mmcr1 |= (अचिन्हित दीर्घ)pmcsel[pmc]
			<< (MMCR1_PMC3SEL_SH - 5 * (pmc - 2));
	अगर (pmc_inuse & 1)
		mmcr0 |= MMCR0_PMC1CE;
	अगर (pmc_inuse & 0xfe)
		mmcr0 |= MMCR0_PMCjCE;

	mmcra |= 0x2000;	/* mark only one IOP per PPC inकाष्ठाion */

	/* Return MMCRx values */
	mmcr->mmcr0 = mmcr0;
	mmcr->mmcr1 = mmcr1;
	mmcr->mmcra = mmcra;
	वापस 0;
पूर्ण

अटल व्योम p970_disable_pmc(अचिन्हित पूर्णांक pmc, काष्ठा mmcr_regs *mmcr)
अणु
	पूर्णांक shअगरt;

	/*
	 * Setting the PMCxSEL field to 0x08 disables PMC x.
	 */
	अगर (pmc <= 1) अणु
		shअगरt = MMCR0_PMC1SEL_SH - 7 * pmc;
		mmcr->mmcr0 = (mmcr->mmcr0 & ~(0x1fUL << shअगरt)) | (0x08UL << shअगरt);
	पूर्ण अन्यथा अणु
		shअगरt = MMCR1_PMC3SEL_SH - 5 * (pmc - 2);
		mmcr->mmcr1 = (mmcr->mmcr1 & ~(0x1fUL << shअगरt)) | (0x08UL << shअगरt);
	पूर्ण
पूर्ण

अटल पूर्णांक ppc970_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 7,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 1,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= 0x8810, /* PM_LD_REF_L1 */
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x3810, /* PM_LD_MISS_L1 */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x431,  /* PM_BR_ISSUED */
	[PERF_COUNT_HW_BRANCH_MISSES] 		= 0x327,  /* PM_GRP_BR_MPRED */
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 */
अटल u64 ppc970_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x8810,		0x3810	पूर्ण,
		[C(OP_WRITE)] = अणु	0x7810,		0x813	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0x731,		0	पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0,		0	पूर्ण,
	पूर्ण,
	[C(LL)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0	पूर्ण,
		[C(OP_WRITE)] = अणु	0,		0	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0x733,		0	पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x704	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x700	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x431,		0x327	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	-1,		-1	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1	पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1	पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा घातer_pmu ppc970_pmu = अणु
	.name			= "PPC970/FX/MP",
	.n_counter		= 8,
	.max_alternatives	= 2,
	.add_fields		= 0x001100005555ull,
	.test_adder		= 0x013300000000ull,
	.compute_mmcr		= p970_compute_mmcr,
	.get_स्थिरraपूर्णांक		= p970_get_स्थिरraपूर्णांक,
	.get_alternatives	= p970_get_alternatives,
	.disable_pmc		= p970_disable_pmc,
	.n_generic		= ARRAY_SIZE(ppc970_generic_events),
	.generic_events		= ppc970_generic_events,
	.cache_events		= &ppc970_cache_events,
	.flags			= PPMU_NO_SIPR | PPMU_NO_CONT_SAMPLING,
पूर्ण;

पूर्णांक init_ppc970_pmu(व्योम)
अणु
	अगर (!cur_cpu_spec->oprofile_cpu_type ||
	    (म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/970")
	     && म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/970MP")))
		वापस -ENODEV;

	वापस रेजिस्टर_घातer_pmu(&ppc970_pmu);
पूर्ण
