<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance counter support क्रम POWER6 processors.
 *
 * Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/cputable.h>

#समावेश "internal.h"

/*
 * Bits in event code क्रम POWER6
 */
#घोषणा PM_PMC_SH	20	/* PMC number (1-based) क्रम direct events */
#घोषणा PM_PMC_MSK	0x7
#घोषणा PM_PMC_MSKS	(PM_PMC_MSK << PM_PMC_SH)
#घोषणा PM_UNIT_SH	16	/* Unit event comes (TTMxSEL encoding) */
#घोषणा PM_UNIT_MSK	0xf
#घोषणा PM_UNIT_MSKS	(PM_UNIT_MSK << PM_UNIT_SH)
#घोषणा PM_LLAV		0x8000	/* Load lookahead match value */
#घोषणा PM_LLA		0x4000	/* Load lookahead match enable */
#घोषणा PM_BYTE_SH	12	/* Byte of event bus to use */
#घोषणा PM_BYTE_MSK	3
#घोषणा PM_SUBUNIT_SH	8	/* Subunit event comes from (NEST_SEL enc.) */
#घोषणा PM_SUBUNIT_MSK	7
#घोषणा PM_SUBUNIT_MSKS	(PM_SUBUNIT_MSK << PM_SUBUNIT_SH)
#घोषणा PM_PMCSEL_MSK	0xff	/* PMCxSEL value */
#घोषणा PM_BUSEVENT_MSK	0xf3700

/*
 * Bits in MMCR1 क्रम POWER6
 */
#घोषणा MMCR1_TTM0SEL_SH	60
#घोषणा MMCR1_TTMSEL_SH(n)	(MMCR1_TTM0SEL_SH - (n) * 4)
#घोषणा MMCR1_TTMSEL_MSK	0xf
#घोषणा MMCR1_TTMSEL(m, n)	(((m) >> MMCR1_TTMSEL_SH(n)) & MMCR1_TTMSEL_MSK)
#घोषणा MMCR1_NESTSEL_SH	45
#घोषणा MMCR1_NESTSEL_MSK	0x7
#घोषणा MMCR1_NESTSEL(m)	(((m) >> MMCR1_NESTSEL_SH) & MMCR1_NESTSEL_MSK)
#घोषणा MMCR1_PMC1_LLA		(1ul << 44)
#घोषणा MMCR1_PMC1_LLA_VALUE	(1ul << 39)
#घोषणा MMCR1_PMC1_ADDR_SEL	(1ul << 35)
#घोषणा MMCR1_PMC1SEL_SH	24
#घोषणा MMCR1_PMCSEL_SH(n)	(MMCR1_PMC1SEL_SH - (n) * 8)
#घोषणा MMCR1_PMCSEL_MSK	0xff

/*
 * Map of which direct events on which PMCs are marked inकाष्ठाion events.
 * Indexed by PMCSEL value >> 1.
 * Bottom 4 bits are a map of which PMCs are पूर्णांकeresting,
 * top 4 bits say what sort of event:
 *   0 = direct marked event,
 *   1 = byte decode event,
 *   4 = add/and event (PMC1 -> bits 0 & 4),
 *   5 = add/and event (PMC1 -> bits 1 & 5),
 *   6 = add/and event (PMC1 -> bits 2 & 6),
 *   7 = add/and event (PMC1 -> bits 3 & 7).
 */
अटल अचिन्हित अक्षर direct_event_is_marked[0x60 >> 1] = अणु
	0,	/* 00 */
	0,	/* 02 */
	0,	/* 04 */
	0x07,	/* 06 PM_MRK_ST_CMPL, PM_MRK_ST_GPS, PM_MRK_ST_CMPL_INT */
	0x04,	/* 08 PM_MRK_DFU_FIN */
	0x06,	/* 0a PM_MRK_IFU_FIN, PM_MRK_INST_FIN */
	0,	/* 0c */
	0,	/* 0e */
	0x02,	/* 10 PM_MRK_INST_DISP */
	0x08,	/* 12 PM_MRK_LSU_DERAT_MISS */
	0,	/* 14 */
	0,	/* 16 */
	0x0c,	/* 18 PM_THRESH_TIMEO, PM_MRK_INST_FIN */
	0x0f,	/* 1a PM_MRK_INST_DISP, PM_MRK_अणुFXU,FPU,LSUपूर्ण_FIN */
	0x01,	/* 1c PM_MRK_INST_ISSUED */
	0,	/* 1e */
	0,	/* 20 */
	0,	/* 22 */
	0,	/* 24 */
	0,	/* 26 */
	0x15,	/* 28 PM_MRK_DATA_FROM_L2MISS, PM_MRK_DATA_FROM_L3MISS */
	0,	/* 2a */
	0,	/* 2c */
	0,	/* 2e */
	0x4f,	/* 30 */
	0x7f,	/* 32 */
	0x4f,	/* 34 */
	0x5f,	/* 36 */
	0x6f,	/* 38 */
	0x4f,	/* 3a */
	0,	/* 3c */
	0x08,	/* 3e PM_MRK_INST_TIMEO */
	0x1f,	/* 40 */
	0x1f,	/* 42 */
	0x1f,	/* 44 */
	0x1f,	/* 46 */
	0x1f,	/* 48 */
	0x1f,	/* 4a */
	0x1f,	/* 4c */
	0x1f,	/* 4e */
	0,	/* 50 */
	0x05,	/* 52 PM_MRK_BR_TAKEN, PM_MRK_BR_MPRED */
	0x1c,	/* 54 PM_MRK_PTEG_FROM_L3MISS, PM_MRK_PTEG_FROM_L2MISS */
	0x02,	/* 56 PM_MRK_LD_MISS_L1 */
	0,	/* 58 */
	0,	/* 5a */
	0,	/* 5c */
	0,	/* 5e */
पूर्ण;

/*
 * Masks showing क्रम each unit which bits are marked events.
 * These masks are in LE order, i.e. 0x00000001 is byte 0, bit 0.
 */
अटल u32 marked_bus_events[16] = अणु
	0x01000000,	/* direct events set 1: byte 3 bit 0 */
	0x00010000,	/* direct events set 2: byte 2 bit 0 */
	0, 0, 0, 0,	/* IDU, IFU, nest: nothing */
	0x00000088,	/* VMX set 1: byte 0 bits 3, 7 */
	0x000000c0,	/* VMX set 2: byte 0 bits 4-7 */
	0x04010000,	/* LSU set 1: byte 2 bit 0, byte 3 bit 2 */
	0xff010000u,	/* LSU set 2: byte 2 bit 0, all of byte 3 */
	0,		/* LSU set 3 */
	0x00000010,	/* VMX set 3: byte 0 bit 4 */
	0,		/* BFP set 1 */
	0x00000022,	/* BFP set 2: byte 0 bits 1, 5 */
	0, 0
पूर्ण;

/*
 * Returns 1 अगर event counts things relating to marked inकाष्ठाions
 * and thus needs the MMCRA_SAMPLE_ENABLE bit set, or 0 अगर not.
 */
अटल पूर्णांक घातer6_marked_instr_event(u64 event)
अणु
	पूर्णांक pmc, psel, ptype;
	पूर्णांक bit, byte, unit;
	u32 mask;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psel = (event & PM_PMCSEL_MSK) >> 1;	/* drop edge/level bit */
	अगर (pmc >= 5)
		वापस 0;

	bit = -1;
	अगर (psel < माप(direct_event_is_marked)) अणु
		ptype = direct_event_is_marked[psel];
		अगर (pmc == 0 || !(ptype & (1 << (pmc - 1))))
			वापस 0;
		ptype >>= 4;
		अगर (ptype == 0)
			वापस 1;
		अगर (ptype == 1)
			bit = 0;
		अन्यथा
			bit = ptype ^ (pmc - 1);
	पूर्ण अन्यथा अगर ((psel & 0x48) == 0x40)
		bit = psel & 7;

	अगर (!(event & PM_BUSEVENT_MSK) || bit == -1)
		वापस 0;

	byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	mask = marked_bus_events[unit];
	वापस (mask >> (byte * 8 + bit)) & 1;
पूर्ण

/*
 * Assign PMC numbers and compute MMCR1 value क्रम a set of events
 */
अटल पूर्णांक p6_compute_mmcr(u64 event[], पूर्णांक n_ev,
			   अचिन्हित पूर्णांक hwc[], काष्ठा mmcr_regs *mmcr, काष्ठा perf_event *pevents[],
			   u32 flags __maybe_unused)
अणु
	अचिन्हित दीर्घ mmcr1 = 0;
	अचिन्हित दीर्घ mmcra = MMCRA_SDAR_DCACHE_MISS | MMCRA_SDAR_ERAT_MISS;
	पूर्णांक i;
	अचिन्हित पूर्णांक pmc, ev, b, u, s, psel;
	अचिन्हित पूर्णांक tपंचांगset = 0;
	अचिन्हित पूर्णांक pmc_inuse = 0;

	अगर (n_ev > 6)
		वापस -1;
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		अगर (pmc) अणु
			अगर (pmc_inuse & (1 << (pmc - 1)))
				वापस -1;	/* collision! */
			pmc_inuse |= 1 << (pmc - 1);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < n_ev; ++i) अणु
		ev = event[i];
		pmc = (ev >> PM_PMC_SH) & PM_PMC_MSK;
		अगर (pmc) अणु
			--pmc;
		पूर्ण अन्यथा अणु
			/* can go on any PMC; find a मुक्त one */
			क्रम (pmc = 0; pmc < 4; ++pmc)
				अगर (!(pmc_inuse & (1 << pmc)))
					अवरोध;
			अगर (pmc >= 4)
				वापस -1;
			pmc_inuse |= 1 << pmc;
		पूर्ण
		hwc[i] = pmc;
		psel = ev & PM_PMCSEL_MSK;
		अगर (ev & PM_BUSEVENT_MSK) अणु
			/* this event uses the event bus */
			b = (ev >> PM_BYTE_SH) & PM_BYTE_MSK;
			u = (ev >> PM_UNIT_SH) & PM_UNIT_MSK;
			/* check क्रम conflict on this byte of event bus */
			अगर ((tपंचांगset & (1 << b)) && MMCR1_TTMSEL(mmcr1, b) != u)
				वापस -1;
			mmcr1 |= (अचिन्हित दीर्घ)u << MMCR1_TTMSEL_SH(b);
			tपंचांगset |= 1 << b;
			अगर (u == 5) अणु
				/* Nest events have a further mux */
				s = (ev >> PM_SUBUNIT_SH) & PM_SUBUNIT_MSK;
				अगर ((tपंचांगset & 0x10) &&
				    MMCR1_NESTSEL(mmcr1) != s)
					वापस -1;
				tपंचांगset |= 0x10;
				mmcr1 |= (अचिन्हित दीर्घ)s << MMCR1_NESTSEL_SH;
			पूर्ण
			अगर (0x30 <= psel && psel <= 0x3d) अणु
				/* these need the PMCx_ADDR_SEL bits */
				अगर (b >= 2)
					mmcr1 |= MMCR1_PMC1_ADDR_SEL >> pmc;
			पूर्ण
			/* bus select values are dअगरferent क्रम PMC3/4 */
			अगर (pmc >= 2 && (psel & 0x90) == 0x80)
				psel ^= 0x20;
		पूर्ण
		अगर (ev & PM_LLA) अणु
			mmcr1 |= MMCR1_PMC1_LLA >> pmc;
			अगर (ev & PM_LLAV)
				mmcr1 |= MMCR1_PMC1_LLA_VALUE >> pmc;
		पूर्ण
		अगर (घातer6_marked_instr_event(event[i]))
			mmcra |= MMCRA_SAMPLE_ENABLE;
		अगर (pmc < 4)
			mmcr1 |= (अचिन्हित दीर्घ)psel << MMCR1_PMCSEL_SH(pmc);
	पूर्ण
	mmcr->mmcr0 = 0;
	अगर (pmc_inuse & 1)
		mmcr->mmcr0 = MMCR0_PMC1CE;
	अगर (pmc_inuse & 0xe)
		mmcr->mmcr0 |= MMCR0_PMCjCE;
	mmcr->mmcr1 = mmcr1;
	mmcr->mmcra = mmcra;
	वापस 0;
पूर्ण

/*
 * Layout of स्थिरraपूर्णांक bits:
 *
 *	0-1	add field: number of uses of PMC1 (max 1)
 *	2-3, 4-5, 6-7, 8-9, 10-11: ditto क्रम PMC2, 3, 4, 5, 6
 *	12-15	add field: number of uses of PMC1-4 (max 4)
 *	16-19	select field: unit on byte 0 of event bus
 *	20-23, 24-27, 28-31 ditto क्रम bytes 1, 2, 3
 *	32-34	select field: nest (subunit) event selector
 */
अटल पूर्णांक p6_get_स्थिरraपूर्णांक(u64 event, अचिन्हित दीर्घ *maskp,
			     अचिन्हित दीर्घ *valp, u64 event_config1 __maybe_unused)
अणु
	पूर्णांक pmc, byte, sh, subunit;
	अचिन्हित दीर्घ mask = 0, value = 0;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	अगर (pmc) अणु
		अगर (pmc > 4 && !(event == 0x500009 || event == 0x600005))
			वापस -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		value |= 1 << sh;
	पूर्ण
	अगर (event & PM_BUSEVENT_MSK) अणु
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		sh = byte * 4 + (16 - PM_UNIT_SH);
		mask |= PM_UNIT_MSKS << sh;
		value |= (अचिन्हित दीर्घ)(event & PM_UNIT_MSKS) << sh;
		अगर ((event & PM_UNIT_MSKS) == (5 << PM_UNIT_SH)) अणु
			subunit = (event >> PM_SUBUNIT_SH) & PM_SUBUNIT_MSK;
			mask  |= (अचिन्हित दीर्घ)PM_SUBUNIT_MSK << 32;
			value |= (अचिन्हित दीर्घ)subunit << 32;
		पूर्ण
	पूर्ण
	अगर (pmc <= 4) अणु
		mask  |= 0x8000;	/* add field क्रम count of PMC1-4 uses */
		value |= 0x1000;
	पूर्ण
	*maskp = mask;
	*valp = value;
	वापस 0;
पूर्ण

अटल पूर्णांक p6_limited_pmc_event(u64 event)
अणु
	पूर्णांक pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;

	वापस pmc == 5 || pmc == 6;
पूर्ण

#घोषणा MAX_ALT	4	/* at most 4 alternatives क्रम any event */

अटल स्थिर अचिन्हित पूर्णांक event_alternatives[][MAX_ALT] = अणु
	अणु 0x0130e8, 0x2000f6, 0x3000fc पूर्ण,	/* PM_PTEG_RELOAD_VALID */
	अणु 0x080080, 0x10000d, 0x30000c, 0x4000f0 पूर्ण, /* PM_LD_MISS_L1 */
	अणु 0x080088, 0x200054, 0x3000f0 पूर्ण,	/* PM_ST_MISS_L1 */
	अणु 0x10000a, 0x2000f4, 0x600005 पूर्ण,	/* PM_RUN_CYC */
	अणु 0x10000b, 0x2000f5 पूर्ण,			/* PM_RUN_COUNT */
	अणु 0x10000e, 0x400010 पूर्ण,			/* PM_PURR */
	अणु 0x100010, 0x4000f8 पूर्ण,			/* PM_FLUSH */
	अणु 0x10001a, 0x200010 पूर्ण,			/* PM_MRK_INST_DISP */
	अणु 0x100026, 0x3000f8 पूर्ण,			/* PM_TB_BIT_TRANS */
	अणु 0x100054, 0x2000f0 पूर्ण,			/* PM_ST_FIN */
	अणु 0x100056, 0x2000fc पूर्ण,			/* PM_L1_ICACHE_MISS */
	अणु 0x1000f0, 0x40000a पूर्ण,			/* PM_INST_IMC_MATCH_CMPL */
	अणु 0x1000f8, 0x200008 पूर्ण,			/* PM_GCT_EMPTY_CYC */
	अणु 0x1000fc, 0x400006 पूर्ण,			/* PM_LSU_DERAT_MISS_CYC */
	अणु 0x20000e, 0x400007 पूर्ण,			/* PM_LSU_DERAT_MISS */
	अणु 0x200012, 0x300012 पूर्ण,			/* PM_INST_DISP */
	अणु 0x2000f2, 0x3000f2 पूर्ण,			/* PM_INST_DISP */
	अणु 0x2000f8, 0x300010 पूर्ण,			/* PM_EXT_INT */
	अणु 0x2000fe, 0x300056 पूर्ण,			/* PM_DATA_FROM_L2MISS */
	अणु 0x2d0030, 0x30001a पूर्ण,			/* PM_MRK_FPU_FIN */
	अणु 0x30000a, 0x400018 पूर्ण,			/* PM_MRK_INST_FIN */
	अणु 0x3000f6, 0x40000e पूर्ण,			/* PM_L1_DCACHE_RELOAD_VALID */
	अणु 0x3000fe, 0x400056 पूर्ण,			/* PM_DATA_FROM_L3MISS */
पूर्ण;

/*
 * This could be made more efficient with a binary search on
 * a presorted list, अगर necessary
 */
अटल पूर्णांक find_alternatives_list(u64 event)
अणु
	पूर्णांक i, j;
	अचिन्हित पूर्णांक alt;

	क्रम (i = 0; i < ARRAY_SIZE(event_alternatives); ++i) अणु
		अगर (event < event_alternatives[i][0])
			वापस -1;
		क्रम (j = 0; j < MAX_ALT; ++j) अणु
			alt = event_alternatives[i][j];
			अगर (!alt || event < alt)
				अवरोध;
			अगर (event == alt)
				वापस i;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक p6_get_alternatives(u64 event, अचिन्हित पूर्णांक flags, u64 alt[])
अणु
	पूर्णांक i, j, nlim;
	अचिन्हित पूर्णांक psel, pmc;
	अचिन्हित पूर्णांक nalt = 1;
	u64 aevent;

	alt[0] = event;
	nlim = p6_limited_pmc_event(event);

	/* check the alternatives table */
	i = find_alternatives_list(event);
	अगर (i >= 0) अणु
		/* copy out alternatives from list */
		क्रम (j = 0; j < MAX_ALT; ++j) अणु
			aevent = event_alternatives[i][j];
			अगर (!aevent)
				अवरोध;
			अगर (aevent != event)
				alt[nalt++] = aevent;
			nlim += p6_limited_pmc_event(aevent);
		पूर्ण

	पूर्ण अन्यथा अणु
		/* Check क्रम alternative ways of computing sum events */
		/* PMCSEL 0x32 counter N == PMCSEL 0x34 counter 5-N */
		psel = event & (PM_PMCSEL_MSK & ~1);	/* ignore edge bit */
		pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
		अगर (pmc && (psel == 0x32 || psel == 0x34))
			alt[nalt++] = ((event ^ 0x6) & ~PM_PMC_MSKS) |
				((5 - pmc) << PM_PMC_SH);

		/* PMCSEL 0x38 counter N == PMCSEL 0x3a counter N+/-2 */
		अगर (pmc && (psel == 0x38 || psel == 0x3a))
			alt[nalt++] = ((event ^ 0x2) & ~PM_PMC_MSKS) |
				((pmc > 2? pmc - 2: pmc + 2) << PM_PMC_SH);
	पूर्ण

	अगर (flags & PPMU_ONLY_COUNT_RUN) अणु
		/*
		 * We're only counting in RUN state,
		 * so PM_CYC is equivalent to PM_RUN_CYC,
		 * PM_INST_CMPL === PM_RUN_INST_CMPL, PM_PURR === PM_RUN_PURR.
		 * This करोesn't include alternatives that don't provide
		 * any extra flexibility in assigning PMCs (e.g.
		 * 0x10000a क्रम PM_RUN_CYC vs. 0x1e क्रम PM_CYC).
		 * Note that even with these additional alternatives
		 * we never end up with more than 4 alternatives क्रम any event.
		 */
		j = nalt;
		क्रम (i = 0; i < nalt; ++i) अणु
			चयन (alt[i]) अणु
			हाल 0x1e:	/* PM_CYC */
				alt[j++] = 0x600005;	/* PM_RUN_CYC */
				++nlim;
				अवरोध;
			हाल 0x10000a:	/* PM_RUN_CYC */
				alt[j++] = 0x1e;	/* PM_CYC */
				अवरोध;
			हाल 2:		/* PM_INST_CMPL */
				alt[j++] = 0x500009;	/* PM_RUN_INST_CMPL */
				++nlim;
				अवरोध;
			हाल 0x500009:	/* PM_RUN_INST_CMPL */
				alt[j++] = 2;		/* PM_INST_CMPL */
				अवरोध;
			हाल 0x10000e:	/* PM_PURR */
				alt[j++] = 0x4000f4;	/* PM_RUN_PURR */
				अवरोध;
			हाल 0x4000f4:	/* PM_RUN_PURR */
				alt[j++] = 0x10000e;	/* PM_PURR */
				अवरोध;
			पूर्ण
		पूर्ण
		nalt = j;
	पूर्ण

	अगर (!(flags & PPMU_LIMITED_PMC_OK) && nlim) अणु
		/* हटाओ the limited PMC events */
		j = 0;
		क्रम (i = 0; i < nalt; ++i) अणु
			अगर (!p6_limited_pmc_event(alt[i])) अणु
				alt[j] = alt[i];
				++j;
			पूर्ण
		पूर्ण
		nalt = j;
	पूर्ण अन्यथा अगर ((flags & PPMU_LIMITED_PMC_REQD) && nlim < nalt) अणु
		/* हटाओ all but the limited PMC events */
		j = 0;
		क्रम (i = 0; i < nalt; ++i) अणु
			अगर (p6_limited_pmc_event(alt[i])) अणु
				alt[j] = alt[i];
				++j;
			पूर्ण
		पूर्ण
		nalt = j;
	पूर्ण

	वापस nalt;
पूर्ण

अटल व्योम p6_disable_pmc(अचिन्हित पूर्णांक pmc, काष्ठा mmcr_regs *mmcr)
अणु
	/* Set PMCxSEL to 0 to disable PMCx */
	अगर (pmc <= 3)
		mmcr->mmcr1 &= ~(0xffUL << MMCR1_PMCSEL_SH(pmc));
पूर्ण

अटल पूर्णांक घातer6_generic_events[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 0x1e,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 2,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= 0x280030, /* LD_REF_L1 */
	[PERF_COUNT_HW_CACHE_MISSES]		= 0x30000c, /* LD_MISS_L1 */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0x410a0,  /* BR_PRED */
	[PERF_COUNT_HW_BRANCH_MISSES]		= 0x400052, /* BR_MPRED */
पूर्ण;

#घोषणा C(x)	PERF_COUNT_HW_CACHE_##x

/*
 * Table of generalized cache-related events.
 * 0 means not supported, -1 means nonsensical, other values
 * are event codes.
 * The "DTLB" and "ITLB" events relate to the DERAT and IERAT.
 */
अटल u64 घातer6_cache_events[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x280030,	0x80080		पूर्ण,
		[C(OP_WRITE)] = अणु	0x180032,	0x80088		पूर्ण,
		[C(OP_PREFETCH)] = अणु	0x810a4,	0		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x100056 	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	0x4008c,	0		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x150730,	0x250532	पूर्ण,
		[C(OP_WRITE)] = अणु	0x250432,	0x150432	पूर्ण,
		[C(OP_PREFETCH)] = अणु	0x810a6,	0		पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x20000e	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0,		0x420ce		पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	0x430e6,	0x400052	पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1		पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु		/* 	RESULT_ACCESS	RESULT_MISS */
		[C(OP_READ)] = अणु	-1,		-1		पूर्ण,
		[C(OP_WRITE)] = अणु	-1,		-1		पूर्ण,
		[C(OP_PREFETCH)] = अणु	-1,		-1		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा घातer_pmu घातer6_pmu = अणु
	.name			= "POWER6",
	.n_counter		= 6,
	.max_alternatives	= MAX_ALT,
	.add_fields		= 0x1555,
	.test_adder		= 0x3000,
	.compute_mmcr		= p6_compute_mmcr,
	.get_स्थिरraपूर्णांक		= p6_get_स्थिरraपूर्णांक,
	.get_alternatives	= p6_get_alternatives,
	.disable_pmc		= p6_disable_pmc,
	.limited_pmc_event	= p6_limited_pmc_event,
	.flags			= PPMU_LIMITED_PMC5_6 | PPMU_ALT_SIPR,
	.n_generic		= ARRAY_SIZE(घातer6_generic_events),
	.generic_events		= घातer6_generic_events,
	.cache_events		= &घातer6_cache_events,
पूर्ण;

पूर्णांक init_घातer6_pmu(व्योम)
अणु
	अगर (!cur_cpu_spec->oprofile_cpu_type ||
	    म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/power6"))
		वापस -ENODEV;

	वापस रेजिस्टर_घातer_pmu(&घातer6_pmu);
पूर्ण
