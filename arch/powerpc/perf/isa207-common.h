<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2009 Paul Mackerras, IBM Corporation.
 * Copyright 2013 Michael Ellerman, IBM Corporation.
 * Copyright 2016 Madhavan Srinivasan, IBM Corporation.
 */

#अगर_अघोषित _LINUX_POWERPC_PERF_ISA207_COMMON_H_
#घोषणा _LINUX_POWERPC_PERF_ISA207_COMMON_H_

#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/cputable.h>

#समावेश "internal.h"

#घोषणा EVENT_EBB_MASK		1ull
#घोषणा EVENT_EBB_SHIFT		PERF_EVENT_CONFIG_EBB_SHIFT
#घोषणा EVENT_BHRB_MASK		1ull
#घोषणा EVENT_BHRB_SHIFT	62
#घोषणा EVENT_WANTS_BHRB	(EVENT_BHRB_MASK << EVENT_BHRB_SHIFT)
#घोषणा EVENT_IFM_MASK		3ull
#घोषणा EVENT_IFM_SHIFT		60
#घोषणा EVENT_THR_CMP_SHIFT	40	/* Threshold CMP value */
#घोषणा EVENT_THR_CMP_MASK	0x3ff
#घोषणा EVENT_THR_CTL_SHIFT	32	/* Threshold control value (start/stop) */
#घोषणा EVENT_THR_CTL_MASK	0xffull
#घोषणा EVENT_THR_SEL_SHIFT	29	/* Threshold select value */
#घोषणा EVENT_THR_SEL_MASK	0x7
#घोषणा EVENT_THRESH_SHIFT	29	/* All threshold bits */
#घोषणा EVENT_THRESH_MASK	0x1fffffull
#घोषणा EVENT_SAMPLE_SHIFT	24	/* Sampling mode & eligibility */
#घोषणा EVENT_SAMPLE_MASK	0x1f
#घोषणा EVENT_CACHE_SEL_SHIFT	20	/* L2/L3 cache select */
#घोषणा EVENT_CACHE_SEL_MASK	0xf
#घोषणा EVENT_IS_L1		(4 << EVENT_CACHE_SEL_SHIFT)
#घोषणा EVENT_PMC_SHIFT		16	/* PMC number (1-based) */
#घोषणा EVENT_PMC_MASK		0xf
#घोषणा EVENT_UNIT_SHIFT	12	/* Unit */
#घोषणा EVENT_UNIT_MASK		0xf
#घोषणा EVENT_COMBINE_SHIFT	11	/* Combine bit */
#घोषणा EVENT_COMBINE_MASK	0x1
#घोषणा EVENT_COMBINE(v)	(((v) >> EVENT_COMBINE_SHIFT) & EVENT_COMBINE_MASK)
#घोषणा EVENT_MARKED_SHIFT	8	/* Marked bit */
#घोषणा EVENT_MARKED_MASK	0x1
#घोषणा EVENT_IS_MARKED		(EVENT_MARKED_MASK << EVENT_MARKED_SHIFT)
#घोषणा EVENT_PSEL_MASK		0xff	/* PMCxSEL value */

/* Bits defined by Linux */
#घोषणा EVENT_LINUX_MASK	\
	((EVENT_EBB_MASK  << EVENT_EBB_SHIFT)			|	\
	 (EVENT_BHRB_MASK << EVENT_BHRB_SHIFT)			|	\
	 (EVENT_IFM_MASK  << EVENT_IFM_SHIFT))

#घोषणा EVENT_VALID_MASK	\
	((EVENT_THRESH_MASK    << EVENT_THRESH_SHIFT)		|	\
	 (EVENT_SAMPLE_MASK    << EVENT_SAMPLE_SHIFT)		|	\
	 (EVENT_CACHE_SEL_MASK << EVENT_CACHE_SEL_SHIFT)	|	\
	 (EVENT_PMC_MASK       << EVENT_PMC_SHIFT)		|	\
	 (EVENT_UNIT_MASK      << EVENT_UNIT_SHIFT)		|	\
	 (EVENT_COMBINE_MASK   << EVENT_COMBINE_SHIFT)		|	\
	 (EVENT_MARKED_MASK    << EVENT_MARKED_SHIFT)		|	\
	  EVENT_LINUX_MASK					|	\
	  EVENT_PSEL_MASK)

#घोषणा ONLY_PLM \
	(PERF_SAMPLE_BRANCH_USER        |\
	 PERF_SAMPLE_BRANCH_KERNEL      |\
	 PERF_SAMPLE_BRANCH_HV)

/* Contants to support घातer9 raw encoding क्रमmat */
#घोषणा p9_EVENT_COMBINE_SHIFT	10	/* Combine bit */
#घोषणा p9_EVENT_COMBINE_MASK	0x3ull
#घोषणा p9_EVENT_COMBINE(v)	(((v) >> p9_EVENT_COMBINE_SHIFT) & p9_EVENT_COMBINE_MASK)
#घोषणा p9_SDAR_MODE_SHIFT	50
#घोषणा p9_SDAR_MODE_MASK	0x3ull
#घोषणा p9_SDAR_MODE(v)		(((v) >> p9_SDAR_MODE_SHIFT) & p9_SDAR_MODE_MASK)

#घोषणा p9_EVENT_VALID_MASK		\
	((p9_SDAR_MODE_MASK   << p9_SDAR_MODE_SHIFT		|	\
	(EVENT_THRESH_MASK    << EVENT_THRESH_SHIFT)		|	\
	(EVENT_SAMPLE_MASK    << EVENT_SAMPLE_SHIFT)		|	\
	(EVENT_CACHE_SEL_MASK << EVENT_CACHE_SEL_SHIFT)		|	\
	(EVENT_PMC_MASK       << EVENT_PMC_SHIFT)		|	\
	(EVENT_UNIT_MASK      << EVENT_UNIT_SHIFT)		|	\
	(p9_EVENT_COMBINE_MASK << p9_EVENT_COMBINE_SHIFT)	|	\
	(EVENT_MARKED_MASK    << EVENT_MARKED_SHIFT)		|	\
	 EVENT_LINUX_MASK					|	\
	 EVENT_PSEL_MASK))

/* Contants to support घातer10 raw encoding क्रमmat */
#घोषणा p10_SDAR_MODE_SHIFT		22
#घोषणा p10_SDAR_MODE_MASK		0x3ull
#घोषणा p10_SDAR_MODE(v)		(((v) >> p10_SDAR_MODE_SHIFT) & \
					p10_SDAR_MODE_MASK)
#घोषणा p10_EVENT_L2L3_SEL_MASK		0x1f
#घोषणा p10_L2L3_SEL_SHIFT		3
#घोषणा p10_L2L3_EVENT_SHIFT		40
#घोषणा p10_EVENT_THRESH_MASK		0xffffull
#घोषणा p10_EVENT_CACHE_SEL_MASK	0x3ull
#घोषणा p10_EVENT_MMCR3_MASK		0x7fffull
#घोषणा p10_EVENT_MMCR3_SHIFT		45
#घोषणा p10_EVENT_RADIX_SCOPE_QUAL_SHIFT	9
#घोषणा p10_EVENT_RADIX_SCOPE_QUAL_MASK	0x1
#घोषणा p10_MMCR1_RADIX_SCOPE_QUAL_SHIFT	45

/* Event Threshold Compare bit स्थिरant क्रम घातer10 in config1 attribute */
#घोषणा p10_EVENT_THR_CMP_SHIFT        0
#घोषणा p10_EVENT_THR_CMP_MASK 0x3FFFFull

#घोषणा p10_EVENT_VALID_MASK		\
	((p10_SDAR_MODE_MASK   << p10_SDAR_MODE_SHIFT		|	\
	(p10_EVENT_THRESH_MASK  << EVENT_THRESH_SHIFT)		|	\
	(EVENT_SAMPLE_MASK     << EVENT_SAMPLE_SHIFT)		|	\
	(p10_EVENT_CACHE_SEL_MASK  << EVENT_CACHE_SEL_SHIFT)	|	\
	(EVENT_PMC_MASK        << EVENT_PMC_SHIFT)		|	\
	(EVENT_UNIT_MASK       << EVENT_UNIT_SHIFT)		|	\
	(p9_EVENT_COMBINE_MASK << p9_EVENT_COMBINE_SHIFT)	|	\
	(p10_EVENT_MMCR3_MASK  << p10_EVENT_MMCR3_SHIFT)	|	\
	(EVENT_MARKED_MASK     << EVENT_MARKED_SHIFT)		|	\
	(p10_EVENT_RADIX_SCOPE_QUAL_MASK << p10_EVENT_RADIX_SCOPE_QUAL_SHIFT)	|	\
	 EVENT_LINUX_MASK					|	\
	EVENT_PSEL_MASK))
/*
 * Layout of स्थिरraपूर्णांक bits:
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   [   fab_match   ]         [       thresh_cmp      ] [   thresh_ctl    ] [   ]
 *                                          |                                  |
 *                           [  thresh_cmp bits क्रम p10]           thresh_sel -*
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *               [ ] |   [ ] |  [  sample ]   [     ]   [6] [5]   [4] [3]   [2] [1]
 *                |  |    |  |                  |
 *      BHRB IFM -*  |    |  |*radix_scope      |      Count of events क्रम each PMC.
 *              EBB -*    |                     |        p1, p2, p3, p4, p5, p6.
 *      L1 I/D qualअगरier -*                     |
 *                     nc - number of counters -*
 *
 * The PMC fields P1..P6, and NC, are adder fields. As we accumulate स्थिरraपूर्णांकs
 * we want the low bit of each field to be added to any existing value.
 *
 * Everything अन्यथा is a value field.
 */

#घोषणा CNST_FAB_MATCH_VAL(v)	(((v) & EVENT_THR_CTL_MASK) << 56)
#घोषणा CNST_FAB_MATCH_MASK	CNST_FAB_MATCH_VAL(EVENT_THR_CTL_MASK)

/* We just throw all the threshold bits पूर्णांकo the स्थिरraपूर्णांक */
#घोषणा CNST_THRESH_VAL(v)	(((v) & EVENT_THRESH_MASK) << 32)
#घोषणा CNST_THRESH_MASK	CNST_THRESH_VAL(EVENT_THRESH_MASK)

#घोषणा CNST_THRESH_CTL_SEL_VAL(v)	(((v) & 0x7ffull) << 32)
#घोषणा CNST_THRESH_CTL_SEL_MASK	CNST_THRESH_CTL_SEL_VAL(0x7ff)

#घोषणा p10_CNST_THRESH_CMP_VAL(v) (((v) & 0x7ffull) << 43)
#घोषणा p10_CNST_THRESH_CMP_MASK   p10_CNST_THRESH_CMP_VAL(0x7ff)

#घोषणा CNST_EBB_VAL(v)		(((v) & EVENT_EBB_MASK) << 24)
#घोषणा CNST_EBB_MASK		CNST_EBB_VAL(EVENT_EBB_MASK)

#घोषणा CNST_IFM_VAL(v)		(((v) & EVENT_IFM_MASK) << 25)
#घोषणा CNST_IFM_MASK		CNST_IFM_VAL(EVENT_IFM_MASK)

#घोषणा CNST_L1_QUAL_VAL(v)	(((v) & 3) << 22)
#घोषणा CNST_L1_QUAL_MASK	CNST_L1_QUAL_VAL(3)

#घोषणा CNST_SAMPLE_VAL(v)	(((v) & EVENT_SAMPLE_MASK) << 16)
#घोषणा CNST_SAMPLE_MASK	CNST_SAMPLE_VAL(EVENT_SAMPLE_MASK)

#घोषणा CNST_CACHE_GROUP_VAL(v)	(((v) & 0xffull) << 55)
#घोषणा CNST_CACHE_GROUP_MASK	CNST_CACHE_GROUP_VAL(0xff)
#घोषणा CNST_CACHE_PMC4_VAL	(1ull << 54)
#घोषणा CNST_CACHE_PMC4_MASK	CNST_CACHE_PMC4_VAL

#घोषणा CNST_L2L3_GROUP_VAL(v)	(((v) & 0x1full) << 55)
#घोषणा CNST_L2L3_GROUP_MASK	CNST_L2L3_GROUP_VAL(0x1f)

#घोषणा CNST_RADIX_SCOPE_GROUP_VAL(v)	(((v) & 0x1ull) << 21)
#घोषणा CNST_RADIX_SCOPE_GROUP_MASK	CNST_RADIX_SCOPE_GROUP_VAL(1)

/*
 * For NC we are counting up to 4 events. This requires three bits, and we need
 * the fअगरth event to overflow and set the 4th bit. To achieve that we bias the
 * fields by 3 in test_adder.
 */
#घोषणा CNST_NC_SHIFT		12
#घोषणा CNST_NC_VAL		(1 << CNST_NC_SHIFT)
#घोषणा CNST_NC_MASK		(8 << CNST_NC_SHIFT)
#घोषणा ISA207_TEST_ADDER	(3 << CNST_NC_SHIFT)

/*
 * For the per-PMC fields we have two bits. The low bit is added, so अगर two
 * events ask क्रम the same PMC the sum will overflow, setting the high bit,
 * indicating an error. So our mask sets the high bit.
 */
#घोषणा CNST_PMC_SHIFT(pmc)	((pmc - 1) * 2)
#घोषणा CNST_PMC_VAL(pmc)	(1 << CNST_PMC_SHIFT(pmc))
#घोषणा CNST_PMC_MASK(pmc)	(2 << CNST_PMC_SHIFT(pmc))

/* Our add_fields is defined as: */
#घोषणा ISA207_ADD_FIELDS	\
	CNST_PMC_VAL(1) | CNST_PMC_VAL(2) | CNST_PMC_VAL(3) | \
	CNST_PMC_VAL(4) | CNST_PMC_VAL(5) | CNST_PMC_VAL(6) | CNST_NC_VAL

/* Bits in MMCR1 क्रम PowerISA v2.07 */
#घोषणा MMCR1_UNIT_SHIFT(pmc)		(60 - (4 * ((pmc) - 1)))
#घोषणा MMCR1_COMBINE_SHIFT(pmc)	(35 - ((pmc) - 1))
#घोषणा MMCR1_PMCSEL_SHIFT(pmc)		(24 - (((pmc) - 1)) * 8)
#घोषणा MMCR1_FAB_SHIFT			36
#घोषणा MMCR1_DC_IC_QUAL_MASK		0x3
#घोषणा MMCR1_DC_IC_QUAL_SHIFT		46

/* MMCR1 Combine bits macro क्रम घातer9 */
#घोषणा p9_MMCR1_COMBINE_SHIFT(pmc)	(38 - ((pmc - 1) * 2))

/* Bits in MMCRA क्रम PowerISA v2.07 */
#घोषणा MMCRA_SAMP_MODE_SHIFT		1
#घोषणा MMCRA_SAMP_ELIG_SHIFT		4
#घोषणा MMCRA_SAMP_ELIG_MASK		7
#घोषणा MMCRA_THR_CTL_SHIFT		8
#घोषणा MMCRA_THR_SEL_SHIFT		16
#घोषणा MMCRA_THR_CMP_SHIFT		32
#घोषणा MMCRA_SDAR_MODE_SHIFT		42
#घोषणा MMCRA_SDAR_MODE_TLB		(1ull << MMCRA_SDAR_MODE_SHIFT)
#घोषणा MMCRA_SDAR_MODE_NO_UPDATES	~(0x3ull << MMCRA_SDAR_MODE_SHIFT)
#घोषणा MMCRA_SDAR_MODE_DCACHE		(2ull << MMCRA_SDAR_MODE_SHIFT)
#घोषणा MMCRA_IFM_SHIFT			30
#घोषणा MMCRA_THR_CTR_MANT_SHIFT	19
#घोषणा MMCRA_THR_CTR_MANT_MASK		0x7Ful
#घोषणा MMCRA_THR_CTR_MANT(v)		(((v) >> MMCRA_THR_CTR_MANT_SHIFT) &\
						MMCRA_THR_CTR_MANT_MASK)

#घोषणा MMCRA_THR_CTR_EXP_SHIFT		27
#घोषणा MMCRA_THR_CTR_EXP_MASK		0x7ul
#घोषणा MMCRA_THR_CTR_EXP(v)		(((v) >> MMCRA_THR_CTR_EXP_SHIFT) &\
						MMCRA_THR_CTR_EXP_MASK)

#घोषणा P10_MMCRA_THR_CTR_MANT_MASK	0xFFul
#घोषणा P10_MMCRA_THR_CTR_MANT(v)	(((v) >> MMCRA_THR_CTR_MANT_SHIFT) &\
						P10_MMCRA_THR_CTR_MANT_MASK)

/* MMCRA Threshold Compare bit स्थिरant क्रम घातer9 */
#घोषणा p9_MMCRA_THR_CMP_SHIFT	45

/* Bits in MMCR2 क्रम PowerISA v2.07 */
#घोषणा MMCR2_FCS(pmc)			(1ull << (63 - (((pmc) - 1) * 9)))
#घोषणा MMCR2_FCP(pmc)			(1ull << (62 - (((pmc) - 1) * 9)))
#घोषणा MMCR2_FCH(pmc)			(1ull << (57 - (((pmc) - 1) * 9)))

#घोषणा MAX_ALT				2
#घोषणा MAX_PMU_COUNTERS		6

/* Bits in MMCR3 क्रम PowerISA v3.10 */
#घोषणा MMCR3_SHIFT(pmc)		(49 - (15 * ((pmc) - 1)))

#घोषणा ISA207_SIER_TYPE_SHIFT		15
#घोषणा ISA207_SIER_TYPE_MASK		(0x7ull << ISA207_SIER_TYPE_SHIFT)

#घोषणा ISA207_SIER_LDST_SHIFT		1
#घोषणा ISA207_SIER_LDST_MASK		(0x7ull << ISA207_SIER_LDST_SHIFT)

#घोषणा ISA207_SIER_DATA_SRC_SHIFT	53
#घोषणा ISA207_SIER_DATA_SRC_MASK	(0x7ull << ISA207_SIER_DATA_SRC_SHIFT)

/* Bits in SIER2/SIER3 क्रम Power10 */
#घोषणा P10_SIER2_FINISH_CYC(sier2)	(((sier2) >> (63 - 37)) & 0x7fful)
#घोषणा P10_SIER2_DISPATCH_CYC(sier2)	(((sier2) >> (63 - 13)) & 0x7fful)

#घोषणा P(a, b)				PERF_MEM_S(a, b)
#घोषणा PH(a, b)			(P(LVL, HIT) | P(a, b))
#घोषणा PM(a, b)			(P(LVL, MISS) | P(a, b))

पूर्णांक isa207_get_स्थिरraपूर्णांक(u64 event, अचिन्हित दीर्घ *maskp, अचिन्हित दीर्घ *valp, u64 event_config1);
पूर्णांक isa207_compute_mmcr(u64 event[], पूर्णांक n_ev,
				अचिन्हित पूर्णांक hwc[], काष्ठा mmcr_regs *mmcr,
				काष्ठा perf_event *pevents[], u32 flags);
व्योम isa207_disable_pmc(अचिन्हित पूर्णांक pmc, काष्ठा mmcr_regs *mmcr);
पूर्णांक isa207_get_alternatives(u64 event, u64 alt[], पूर्णांक size, अचिन्हित पूर्णांक flags,
					स्थिर अचिन्हित पूर्णांक ev_alt[][MAX_ALT]);
व्योम isa207_get_mem_data_src(जोड़ perf_mem_data_src *dsrc, u32 flags,
							काष्ठा pt_regs *regs);
व्योम isa207_get_mem_weight(u64 *weight, u64 type);

पूर्णांक isa3XX_check_attr_config(काष्ठा perf_event *ev);

#पूर्ण_अगर
