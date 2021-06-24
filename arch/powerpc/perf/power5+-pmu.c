<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter support क्रम POWER5+/++ (not POWER5) processors.
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
 * Bits in event code क्रम POWER5+ (POWER5 GS) and POWER5++ (POWER5 GS DD3)
 */
#घोषणा PM_PMC_SH	20	/* PMC number (1-based) क्रम direct events */
#घोषणा PM_PMC_MSK	0xf
#घोषणा PM_PMC_MSKS	(PM_PMC_MSK << PM_PMC_SH)
#घोषणा PM_UNIT_SH	16	/* TTMMUX number and setting - unit select */
#घोषणा PM_UNIT_MSK	0xf
#घोषणा PM_BYTE_SH	12	/* Byte number of event bus to use */
#घोषणा PM_BYTE_MSK	7
#घोषणा PM_GRS_SH	8	/* Storage subप्रणाली mux select */
#घोषणा PM_GRS_MSK	7
#घोषणा PM_BUSEVENT_MSK	0x80	/* Set अगर event uses event bus */
#घोषणा PM_PMCSEL_MSK	0x7f

/* Values in PM_UNIT field */
#घोषणा PM_FPU		0
#घोषणा PM_ISU0		1
#घोषणा PM_IFU		2
#घोषणा PM_ISU1		3
#घोषणा PM_IDU		4
#घोषणा PM_ISU0_ALT	6
#घोषणा PM_GRS		7
#घोषणा PM_LSU0		8
#घोषणा PM_LSU1		0xc
#घोषणा PM_LASTUNIT	0xc

/*
 * Bits in MMCR1 क्रम POWER5+
 */
#घोषणा MMCR1_TTM0SEL_SH	62
#घोषणा MMCR1_TTM1SEL_SH	60
#घोषणा MMCR1_TTM2SEL_SH	58
#घोषणा MMCR1_TTM3SEL_SH	56
#घोषणा MMCR1_TTMSEL_MSK	3
#घोषणा MMCR1_TD_CP_DBG0SEL_SH	54
#घोषणा MMCR1_TD_CP_DBG1SEL_SH	52
#घोषणा MMCR1_TD_CP_DBG2SEL_SH	50
#घोषणा MMCR1_TD_CP_DBG3SEL_SH	48
#घोषणा MMCR1_GRS_L2SEL_SH	46
#घोषणा MMCR1_GRS_L2SEL_MSK	3
#घोषणा MMCR1_GRS_L3SEL_SH	44
#घोषणा MMCR1_GRS_L3SEL_MSK	3
#घोषणा MMCR1_GRS_MCSEL_SH	41
#घोषणा MMCR1_GRS_MCSEL_MSK	7
#घोषणा MMCR1_GRS_FABSEL_SH	39
#घोषणा MMCR1_GRS_FABSEL_MSK	3
#घोषणा MMCR1_PMC1_ADDER_SEL_SH	35
#घोषणा MMCR1_PMC2_ADDER_SEL_SH	34
#घोषणा MMCR1_PMC3_ADDER_SEL_SH	33
#घोषणा MMCR1_PMC4_ADDER_SEL_SH	32
#घोषणा MMCR1_PMC1SEL_SH	25
#घोषणा MMCR1_PMC2SEL_SH	17
#घोषणा MMCR1_PMC3SEL_SH	9
#घोषणा MMCR1_PMC4SEL_SH	1
#घोषणा MMCR1_PMCSEL_SH(n)	(MMCR1_PMC1SEL_SH - (n) * 8)
#घोषणा MMCR1_PMCSEL_MSK	0x7f

/*
 * Layout of स्थिरraपूर्णांक bits:
 * 6666555555555544444444443333333333222222222211111111110000000000
 * 3210987654321098765432109876543210987654321098765432109876543210
 *             [  ><><>< ><> <><>[  >  <  ><  ><  ><  ><><><><><><>
 *             NC  G0G1G2 G3 T0T1 UC    B0  B1  B2  B3 P6P5P4P3P2P1
 *
 * NC - number of counters
 *     51: NC error 0x0008_0000_0000_0000
 *     48-50: number of events needing PMC1-4 0x0007_0000_0000_0000
 *
 * G0..G3 - GRS mux स्थिरraपूर्णांकs
 *     46-47: GRS_L2SEL value
 *     44-45: GRS_L3SEL value
 *     41-44: GRS_MCSEL value
 *     39-40: GRS_FABSEL value
 *	Note that these match up with their bit positions in MMCR1
 *
 * T0 - TTM0 स्थिरraपूर्णांक
 *     36-37: TTM0SEL value (0=FPU, 2=IFU, 3=ISU1) 0x30_0000_0000
 *
 * T1 - TTM1 स्थिरraपूर्णांक
 *     34-35: TTM1SEL value (0=IDU, 3=GRS) 0x0c_0000_0000
 *
 * UC - unit स्थिरraपूर्णांक: can't have all three of FPU|IFU|ISU1, ISU0, IDU|GRS
 *     33: UC3 error 0x02_0000_0000
 *     32: FPU|IFU|ISU1 events needed 0x01_0000_0000
 *     31: ISU0 events needed 0x01_8000_0000
 *     30: IDU|GRS events needed 0x00_4000_0000
 *
 * B0
 *     24-27: Byte 0 event source 0x0f00_0000
 *	      Encoding as क्रम the event code
 *
 * B1, B2, B3
 *     20-23, 16-19, 12-15: Byte 1, 2, 3 event sources
 *
 * P6
 *     11: P6 error 0x800
 *     10-11: Count of events needing PMC6
 *
 * P1..P5
 *     0-9: Count of events needing PMC1..PMC5
 */

अटल स्थिर पूर्णांक grsel_shअगरt[8] = अणु
	MMCR1_GRS_L2SEL_SH, MMCR1_GRS_L2SEL_SH, MMCR1_GRS_L2SEL_SH,
	MMCR1_GRS_L3SEL_SH, MMCR1_GRS_L3SEL_SH, MMCR1_GRS_L3SEL_SH,
	MMCR1_GRS_MCSEL_SH, MMCR1_GRS_FABSEL_SH
पूर्ण;

/* Masks and values क्रम using events from the various units */
अटल अचिन्हित दीर्घ unit_cons[PM_LASTUNIT+1][2] = अणु
	[PM_FPU] =   अणु 0x3200000000ul, 0x0100000000ul पूर्ण,
	[PM_ISU0] =  अणु 0x0200000000ul, 0x0080000000ul पूर्ण,
	[PM_ISU1] =  अणु 0x3200000000ul, 0x3100000000ul पूर्ण,
	[PM_IFU] =   अणु 0x3200000000ul, 0x2100000000ul पूर्ण,
	[PM_IDU] =   अणु 0x0e00000000ul, 0x0040000000ul पूर्ण,
	[PM_GRS] =   अणु 0x0e00000000ul, 0x0c40000000ul पूर्ण,
पूर्ण;

अटल पूर्णांक घातer5p_get_स्थिरraपूर्णांक(u64 event, अचिन्हित दीर्घ *maskp,
				  अचिन्हित दीर्घ *valp, u64 event_config1 __maybe_unused)
अणु
	पूर्णांक pmc, byte, unit, sh;
	पूर्णांक bit, fmask;
	अचिन्हित दीर्घ mask = 0, value = 0;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	अगर (pmc) अणु
		अगर (pmc > 6)
			वापस -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		value |= 1 << sh;
		अगर (pmc >= 5 && !(event == 0x500009 || event == 0x600005))
			वापस -1;
	पूर्ण
	अगर (event & PM_BUSEVENT_MSK) अणु
		unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
		अगर (unit > PM_LASTUNIT)
			वापस -1;
		अगर (unit == PM_ISU0_ALT)
			unit = PM_ISU0;
		mask |= unit_cons[unit][0];
		value |= unit_cons[unit][1];
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		अगर (byte >= 4) अणु
			अगर (unit != PM_LSU1)
				वापस -1;
			/* Map LSU1 low word (bytes 4-7) to unit LSU1+1 */
			++unit;
			byte &= 3;
		पूर्ण
		अगर (unit == PM_GRS) अणु
			bit = event & 7;
			fmask = (bit == 6)? 7: 3;
			sh = grsel_shअगरt[bit];
			mask |= (अचिन्हित दीर्घ)fmask << sh;
			value |= (अचिन्हित दीर्घ)((event >> PM_GRS_SH) & fmask)
				<< sh;
		पूर्ण
		/* Set byte lane select field */
		mask  |= 0xfUL << (24 - 4 * byte);
		value |= (अचिन्हित दीर्घ)unit << (24 - 4 * byte);
	पूर्ण
	अगर (pmc < 5) अणु
		/* need a counter from PMC1-4 set */
		mask  |= 0x8000000000000ul;
		value |= 0x1000000000000ul;
	पूर्ण
	*maskp = mask;
	*valp = value;
	वापस 0;
पूर्ण

अटल पूर्णांक घातer5p_limited_pmc_event(u64 event)
अणु
	पूर्णांक pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;

	वापस pmc == 5 || pmc == 6;
पूर्ण

#घोषणा MAX_ALT	3	/* at most 3 alternatives क्रम any event */

अटल स्थिर अचिन्हित पूर्णांक event_alternatives[][MAX_ALT] = अणु
	अणु 0x100c0,  0x40001f पूर्ण,			/* PM_GCT_FULL_CYC */
	अणु 0x120e4,  0x400002 पूर्ण,			/* PM_GRP_DISP_REJECT */
	अणु 0x230e2,  0x323087 पूर्ण,			/* PM_BR_PRED_CR */
	अणु 0x230e3,  0x223087, 0x3230a0 पूर्ण,	/* PM_BR_PRED_TA */
	अणु 0x410c7,  0x441084 पूर्ण,			/* PM_THRD_L2MISS_BOTH_CYC */
	अणु 0x800c4,  0xc20e0 पूर्ण,			/* PM_DTLB_MISS */
	अणु 0xc50c6,  0xc60e0 पूर्ण,			/* PM_MRK_DTLB_MISS */
	अणु 0x100005, 0x600005 पूर्ण,			/* PM_RUN_CYC */
	अणु 0x100009, 0x200009 पूर्ण,			/* PM_INST_CMPL */
	अणु 0x200015, 0x300015 पूर्ण,			/* PM_LSU_LMQ_SRQ_EMPTY_CYC */
	अणु 0x300009, 0x400009 पूर्ण,			/* PM_INST_DISP */
पूर्ण;

/*
 * Scan the alternatives table क्रम a match and वापस the
 * index पूर्णांकo the alternatives table अगर found, अन्यथा -1.
 */
अटल पूर्णांक find_alternative(अचिन्हित पूर्णांक event)
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

अटल स्थिर अचिन्हित अक्षर bytedecode_alternatives[4][4] = अणु
	/* PMC 1 */	अणु 0x21, 0x23, 0x25, 0x27 पूर्ण,
	/* PMC 2 */	अणु 0x07, 0x17, 0x0e, 0x1e पूर्ण,
	/* PMC 3 */	अणु 0x20, 0x22, 0x24, 0x26 पूर्ण,
	/* PMC 4 */	अणु 0x07, 0x17, 0x0e, 0x1e पूर्ण
पूर्ण;

/*
 * Some direct events क्रम decodes of event bus byte 3 have alternative
 * PMCSEL values on other counters.  This वापसs the alternative
 * event code क्रम those that करो, or -1 otherwise.  This also handles
 * alternative PCMSEL values क्रम add events.
 */
अटल s64 find_alternative_bdecode(u64 event)
अणु
	पूर्णांक pmc, altpmc, pp, j;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	अगर (pmc == 0 || pmc > 4)
		वापस -1;
	altpmc = 5 - pmc;	/* 1 <-> 4, 2 <-> 3 */
	pp = event & PM_PMCSEL_MSK;
	क्रम (j = 0; j < 4; ++j) अणु
		अगर (bytedecode_alternatives[pmc - 1][j] == pp) अणु
			वापस (event & ~(PM_PMC_MSKS | PM_PMCSEL_MSK)) |
				(altpmc << PM_PMC_SH) |
				bytedecode_alternatives[altpmc - 1][j];
		पूर्ण
	पूर्ण

	/* new decode alternatives क्रम घातer5+ */
	अगर (pmc == 1 && (pp == 0x0d || pp == 0x0e))
		वापस event + (2 << PM_PMC_SH) + (0x2e - 0x0d);
	अगर (pmc == 3 && (pp == 0x2e || pp == 0x2f))
		वापस event - (2 << PM_PMC_SH) - (0x2e - 0x0d);

	/* alternative add event encodings */
	अगर (pp == 0x10 || pp == 0x28)
		वापस ((event ^ (0x10 ^ 0x28)) & ~PM_PMC_MSKS) |
			(altpmc << PM_PMC_SH);

	वापस -1;
पूर्ण

अटल पूर्णांक घातer5p_get_alternatives(u64 event, अचिन्हित पूर्णांक flags, u64 alt[])
अणु
	पूर्णांक i, j, nalt = 1;
	पूर्णांक nlim;
	s64 ae;

	alt[0] = event;
	nalt = 1;
	nlim = घातer5p_limited_pmc_event(event);
	i = find_alternative(event);
	अगर (i >= 0) अणु
		क्रम (j = 0; j < MAX_ALT; ++j) अणु
			ae = event_alternatives[i][j];
			अगर (ae && ae != event)
				alt[nalt++] = ae;
			nlim += घातer5p_limited_pmc_event(ae);
		पूर्ण
	पूर्ण अन्यथा अणु
		ae = find_alternative_bdecode(event);
		अगर (ae > 0)
			alt[nalt++] = ae;
	पूर्ण

	अगर (flags & PPMU_ONLY_COUNT_RUN) अणु
		/*
		 * We're only counting in RUN state,
		 * so PM_CYC is equivalent to PM_RUN_CYC
		 * and PM_INST_CMPL === PM_RUN_INST_CMPL.
		 * This करोesn't include alternatives that don't provide
		 * any extra flexibility in assigning PMCs (e.g.
		 * 0x100005 क्रम PM_RUN_CYC vs. 0xf क्रम PM_CYC).
		 * Note that even with these additional alternatives
		 * we never end up with more than 3 alternatives क्रम any event.
		 */
		j = nalt;
		क्रम (i = 0; i < nalt; ++i) अणु
			चयन (alt[i]) अणु
			हाल 0xf:	/* PM_CYC */
				alt[j++] = 0x600005;	/* PM_RUN_CYC */
				++nlim;
				अवरोध;
			हाल 0x600005:	/* PM_RUN_CYC */
				alt[j++] = 0xf;
				अवरोध;
			हाल 0x100009:	/* PM_INST_CMPL */
				alt[j++] = 0x500009;	/* PM_RUN_INST_CMPL */
				++nlim;
				अवरोध;
			हाल 0x500009:	/* PM_RUN_INST_CMPL */
				alt[j++] = 0x100009;	/* PM_INST_CMPL */
				alt[j++] = 0x200009;
				अवरोध;
			पूर्ण
		पूर्ण
		nalt = j;
	पूर्ण

	अगर (!(flags & PPMU_LIMITED_PMC_OK) && nlim) अणु
		/* हटाओ the limited PMC events */
		j = 0;
		क्रम (i = 0; i < nalt; ++i) अणु
			अगर (!घातer5p_limited_pmc_event(alt[i])) अणु
				alt[j] = alt[i];
				++j;
			पूर्ण
		पूर्ण
		nalt = j;
	पूर्ण अन्यथा अगर ((flags & PPMU_LIMITED_PMC_REQD) && nlim < nalt) अणु
		/* हटाओ all but the limited PMC events */
		j = 0;
		क्रम (i = 0; i < nalt; ++i) अणु
			अगर (घातer5p_limited_pmc_event(alt[i])) अणु
				alt[j] = alt[i];
				++j;
			पूर्ण
		पूर्ण
		nalt = j;
	पूर्ण

	वापस nalt;
पूर्ण

/*
 * Map of which direct events on which PMCs are marked inकाष्ठाion events.
 * Indexed by PMCSEL value, bit i (LE) set अगर PMC i is a marked event.
 * Bit 0 is set अगर it is marked क्रम all PMCs.
 * The 0x80 bit indicates a byte decode PMCSEL value.
 */
अटल अचिन्हित अक्षर direct_event_is_marked[0x28] = अणु
	0,	/* 00 */
	0x1f,	/* 01 PM_IOPS_CMPL */
	0x2,	/* 02 PM_MRK_GRP_DISP */
	0xe,	/* 03 PM_MRK_ST_CMPL, PM_MRK_ST_GPS, PM_MRK_ST_CMPL_INT */
	0,	/* 04 */
	0x1c,	/* 05 PM_MRK_BRU_FIN, PM_MRK_INST_FIN, PM_MRK_CRU_FIN */
	0x80,	/* 06 */
	0x80,	/* 07 */
	0, 0, 0,/* 08 - 0a */
	0x18,	/* 0b PM_THRESH_TIMEO, PM_MRK_GRP_TIMEO */
	0,	/* 0c */
	0x80,	/* 0d */
	0x80,	/* 0e */
	0,	/* 0f */
	0,	/* 10 */
	0x14,	/* 11 PM_MRK_GRP_BR_REसूची, PM_MRK_GRP_IC_MISS */
	0,	/* 12 */
	0x10,	/* 13 PM_MRK_GRP_CMPL */
	0x1f,	/* 14 PM_GRP_MRK, PM_MRK_अणुFXU,FPU,LSUपूर्ण_FIN */
	0x2,	/* 15 PM_MRK_GRP_ISSUED */
	0x80,	/* 16 */
	0x80,	/* 17 */
	0, 0, 0, 0, 0,
	0x80,	/* 1d */
	0x80,	/* 1e */
	0,	/* 1f */
	0x80,	/* 20 */
	0x80,	/* 21 */
	0x80,	/* 22 */
	0x80,	/* 23 */
	0x80,	/* 24 */
	0x80,	/* 25 */
	0x80,	/* 26 */
	0x80,	/* 27 */
पूर्ण;

/*
 * Returns 1 अगर event counts things relating to marked inकाष्ठाions
 * and thus needs the MMCRA_SAMPLE_ENABLE bit set, or 0 अगर not.
 */
अटल पूर्णांक घातer5p_marked_instr_event(u64 event)
अणु
	पूर्णांक pmc, psel;
	पूर्णांक bit, byte, unit;
	u32 mask;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psel = event & PM_PMCSEL_MSK;
	अगर (pmc >= 5)
		वापस 0;

	bit = -1;
	अगर (psel < माप(direct_event_is_marked)) अणु
		अगर (direct_event_is_marked[psel] & (1 << pmc))
			वापस 1;
		अगर (direct_event_is_marked[psel] & 0x80)
			bit = 4;
		अन्यथा अगर (psel == 0x08)
			bit = pmc - 1;
		अन्यथा अगर (psel == 0x10)
			bit = 4 - pmc;
		अन्यथा अगर (psel == 0x1b && (pmc == 1 || pmc == 3))
			bit = 4;
	पूर्ण अन्यथा अगर ((psel & 0x48) == 0x40) अणु
		bit = psel & 7;
	पूर्ण अन्यथा अगर (psel == 0x28) अणु
		bit = pmc - 1;
	पूर्ण अन्यथा अगर (pmc == 3 && (psel == 0x2e || psel == 0x2f)) अणु
		bit = 4;
	पूर्ण

	अगर (!(event & PM_BUSEVENT_MSK) || bit == -1)
		वापस 0;

	byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	अगर (unit == PM_LSU0) अणु
		/* byte 1 bits 0-7, byte 2 bits 0,2-4,6 */
		mask = 0x5dff00;
	पूर्ण अन्यथा अगर (unit == PM_LSU1 && byte >= 4) अणु
		byte -= 4;
		/* byte 5 bits 6-7, byte 6 bits 0,4, byte 7 bits 0-4,6 */
		mask = 0x5f11c000;
	पूर्ण अन्यथा
		वापस 0;

	वापस (mask >> (byte * 8 + bit)) & 1;
पूर्ण

अटल पूर्णांक घातer5p_compute_mmcr(u64 event[], पूर्णांक n_ev,
				अचिन्हित पूर्णांक hwc[], काष्ठा mmcr_regs *mmcr,
				काष्ठा perf_event *pevents[],
				u32 flags __maybe_unused)
अणु
	अचिन्हित दीर्घ mmcr1 = 0;
	अचिन्हित दीर्घ mmcra = 0;
	अचिन्हित पूर्णांक pmc, unit, byte, psel;
	अचिन्हित पूर्णांक tपंचांग;
	पूर्णांक i, isbus, bit, grsel;
	अचिन्हित पूर्णांक pmc_inuse = 0;
	अचिन्हित अक्षर busbyte[4];
	अचिन्हित अक्षर unituse[16];
	पूर्णांक tपंचांगuse;

	अगर (n_ev > 6)
		वापस -1;

	/* First pass to count resource use */
	स_रखो(busbyte, 0, माप(busbyte));
	स_रखो(unituse, 0, माप(unituse));
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		अगर (pmc) अणु
			अगर (pmc > 6)
				वापस -1;
			अगर (pmc_inuse & (1 << (pmc - 1)))
				वापस -1;
			pmc_inuse |= 1 << (pmc - 1);
		पूर्ण
		अगर (event[i] & PM_BUSEVENT_MSK) अणु
			unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
			byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
			अगर (unit > PM_LASTUNIT)
				वापस -1;
			अगर (unit == PM_ISU0_ALT)
				unit = PM_ISU0;
			अगर (byte >= 4) अणु
				अगर (unit != PM_LSU1)
					वापस -1;
				++unit;
				byte &= 3;
			पूर्ण
			अगर (busbyte[byte] && busbyte[byte] != unit)
				वापस -1;
			busbyte[byte] = unit;
			unituse[unit] = 1;
		पूर्ण
	पूर्ण

	/*
	 * Assign resources and set multiplexer selects.
	 *
	 * PM_ISU0 can go either on TTM0 or TTM1, but that's the only
	 * choice we have to deal with.
	 */
	अगर (unituse[PM_ISU0] &
	    (unituse[PM_FPU] | unituse[PM_IFU] | unituse[PM_ISU1])) अणु
		unituse[PM_ISU0_ALT] = 1;	/* move ISU to TTM1 */
		unituse[PM_ISU0] = 0;
	पूर्ण
	/* Set TTM[01]SEL fields. */
	tपंचांगuse = 0;
	क्रम (i = PM_FPU; i <= PM_ISU1; ++i) अणु
		अगर (!unituse[i])
			जारी;
		अगर (tपंचांगuse++)
			वापस -1;
		mmcr1 |= (अचिन्हित दीर्घ)i << MMCR1_TTM0SEL_SH;
	पूर्ण
	tपंचांगuse = 0;
	क्रम (; i <= PM_GRS; ++i) अणु
		अगर (!unituse[i])
			जारी;
		अगर (tपंचांगuse++)
			वापस -1;
		mmcr1 |= (अचिन्हित दीर्घ)(i & 3) << MMCR1_TTM1SEL_SH;
	पूर्ण
	अगर (tपंचांगuse > 1)
		वापस -1;

	/* Set byte lane select fields, TTM[23]SEL and GRS_*SEL. */
	क्रम (byte = 0; byte < 4; ++byte) अणु
		unit = busbyte[byte];
		अगर (!unit)
			जारी;
		अगर (unit == PM_ISU0 && unituse[PM_ISU0_ALT]) अणु
			/* get ISU0 through TTM1 rather than TTM0 */
			unit = PM_ISU0_ALT;
		पूर्ण अन्यथा अगर (unit == PM_LSU1 + 1) अणु
			/* select lower word of LSU1 क्रम this byte */
			mmcr1 |= 1ul << (MMCR1_TTM3SEL_SH + 3 - byte);
		पूर्ण
		tपंचांग = unit >> 2;
		mmcr1 |= (अचिन्हित दीर्घ)tपंचांग
			<< (MMCR1_TD_CP_DBG0SEL_SH - 2 * byte);
	पूर्ण

	/* Second pass: assign PMCs, set PMCxSEL and PMCx_ADDER_SEL fields */
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		byte = (event[i] >> PM_BYTE_SH) & PM_BYTE_MSK;
		psel = event[i] & PM_PMCSEL_MSK;
		isbus = event[i] & PM_BUSEVENT_MSK;
		अगर (!pmc) अणु
			/* Bus event or any-PMC direct event */
			क्रम (pmc = 0; pmc < 4; ++pmc) अणु
				अगर (!(pmc_inuse & (1 << pmc)))
					अवरोध;
			पूर्ण
			अगर (pmc >= 4)
				वापस -1;
			pmc_inuse |= 1 << pmc;
		पूर्ण अन्यथा अगर (pmc <= 4) अणु
			/* Direct event */
			--pmc;
			अगर (isbus && (byte & 2) &&
			    (psel == 8 || psel == 0x10 || psel == 0x28))
				/* add events on higher-numbered bus */
				mmcr1 |= 1ul << (MMCR1_PMC1_ADDER_SEL_SH - pmc);
		पूर्ण अन्यथा अणु
			/* Inकाष्ठाions or run cycles on PMC5/6 */
			--pmc;
		पूर्ण
		अगर (isbus && unit == PM_GRS) अणु
			bit = psel & 7;
			grsel = (event[i] >> PM_GRS_SH) & PM_GRS_MSK;
			mmcr1 |= (अचिन्हित दीर्घ)grsel << grsel_shअगरt[bit];
		पूर्ण
		अगर (घातer5p_marked_instr_event(event[i]))
			mmcra |= MMCRA_SAMPLE_ENABLE;
		अगर ((psel & 0x58) == 0x40 && (byte & 1) != ((pmc >> 1) & 1))
			/* select alternate byte lane */
			psel |= 0x10;
		अगर (pmc <= 3)
			mmcr1 |= psel << MMCR1_PMCSEL_SH(pmc);
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

अटल व्योम घातer5p_disable_pmc(अचिन्हित पूर्णांक pmc, काष्ठा mmcr_regs *mmcr)
अणु
	अगर (pmc <= 3)
		mmcr->mmcr1 &= ~(0x7fUL << MMCR1_PMCSEL_SH(pmc));
पूर्ण

अटल पूर्णांक घातer5p_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 0xf,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 0x100009,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= 0x1c10a8, /* LD_REF_L1 */
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x3c1088, /* LD_MISS_L1 */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x230e4,  /* BR_ISSUED */
	[PERF_COUNT_HW_BRANCH_MISSES]		= 0x230e5,  /* BR_MPRED_CR */
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 */
अटल u64 घातer5p_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x1c10a8,	0x3c1088	पूर्ण,
		[C(OP_WRITE)] = अणु	0x2c10a8,	0xc10c3		पूर्ण,
		[C(OP_PREFETCH)] = अणु	0xc70e7,	-1		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0		पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	0,		0		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0		पूर्ण,
		[C(OP_WRITE)] = अणु	0,		0		पूर्ण,
		[C(OP_PREFETCH)] = अणु	0xc50c3,	0		पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0xc20e4,	0x800c4		पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x800c0		पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x230e4,	0x230e5		पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1		पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	-1,		-1		पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा घातer_pmu घातer5p_pmu = अणु
	.name			= "POWER5+/++",
	.n_counter		= 6,
	.max_alternatives	= MAX_ALT,
	.add_fields		= 0x7000000000055ul,
	.test_adder		= 0x3000040000000ul,
	.compute_mmcr		= घातer5p_compute_mmcr,
	.get_स्थिरraपूर्णांक		= घातer5p_get_स्थिरraपूर्णांक,
	.get_alternatives	= घातer5p_get_alternatives,
	.disable_pmc		= घातer5p_disable_pmc,
	.limited_pmc_event	= घातer5p_limited_pmc_event,
	.flags			= PPMU_LIMITED_PMC5_6 | PPMU_HAS_SSLOT,
	.n_generic		= ARRAY_SIZE(घातer5p_generic_events),
	.generic_events		= घातer5p_generic_events,
	.cache_events		= &घातer5p_cache_events,
पूर्ण;

पूर्णांक init_घातer5p_pmu(व्योम)
अणु
	अगर (!cur_cpu_spec->oprofile_cpu_type ||
	    (म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/power5+")
	     && म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/power5++")))
		वापस -ENODEV;

	वापस रेजिस्टर_घातer_pmu(&घातer5p_pmu);
पूर्ण
