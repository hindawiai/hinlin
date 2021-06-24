<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common Perक्रमmance counter support functions क्रम PowerISA v2.07 processors.
 *
 * Copyright 2009 Paul Mackerras, IBM Corporation.
 * Copyright 2013 Michael Ellerman, IBM Corporation.
 * Copyright 2016 Madhavan Srinivasan, IBM Corporation.
 */
#समावेश "isa207-common.h"

PMU_FORMAT_ATTR(event,		"config:0-49");
PMU_FORMAT_ATTR(pmcxsel,	"config:0-7");
PMU_FORMAT_ATTR(mark,		"config:8");
PMU_FORMAT_ATTR(combine,	"config:11");
PMU_FORMAT_ATTR(unit,		"config:12-15");
PMU_FORMAT_ATTR(pmc,		"config:16-19");
PMU_FORMAT_ATTR(cache_sel,	"config:20-23");
PMU_FORMAT_ATTR(sample_mode,	"config:24-28");
PMU_FORMAT_ATTR(thresh_sel,	"config:29-31");
PMU_FORMAT_ATTR(thresh_stop,	"config:32-35");
PMU_FORMAT_ATTR(thresh_start,	"config:36-39");
PMU_FORMAT_ATTR(thresh_cmp,	"config:40-49");

अटल काष्ठा attribute *isa207_pmu_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_pmcxsel.attr,
	&क्रमmat_attr_mark.attr,
	&क्रमmat_attr_combine.attr,
	&क्रमmat_attr_unit.attr,
	&क्रमmat_attr_pmc.attr,
	&क्रमmat_attr_cache_sel.attr,
	&क्रमmat_attr_sample_mode.attr,
	&क्रमmat_attr_thresh_sel.attr,
	&क्रमmat_attr_thresh_stop.attr,
	&क्रमmat_attr_thresh_start.attr,
	&क्रमmat_attr_thresh_cmp.attr,
	शून्य,
पूर्ण;

काष्ठा attribute_group isa207_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = isa207_pmu_क्रमmat_attr,
पूर्ण;

अटल अंतरभूत bool event_is_fab_match(u64 event)
अणु
	/* Only check pmc, unit and pmcxsel, ignore the edge bit (0) */
	event &= 0xff0fe;

	/* PM_MRK_FAB_RSP_MATCH & PM_MRK_FAB_RSP_MATCH_CYC */
	वापस (event == 0x30056 || event == 0x4f052);
पूर्ण

अटल bool is_event_valid(u64 event)
अणु
	u64 valid_mask = EVENT_VALID_MASK;

	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		valid_mask = p10_EVENT_VALID_MASK;
	अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		valid_mask = p9_EVENT_VALID_MASK;

	वापस !(event & ~valid_mask);
पूर्ण

अटल अंतरभूत bool is_event_marked(u64 event)
अणु
	अगर (event & EVENT_IS_MARKED)
		वापस true;

	वापस false;
पूर्ण

अटल अचिन्हित दीर्घ sdar_mod_val(u64 event)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		वापस p10_SDAR_MODE(event);

	वापस p9_SDAR_MODE(event);
पूर्ण

अटल व्योम mmcra_sdar_mode(u64 event, अचिन्हित दीर्घ *mmcra)
अणु
	/*
	 * MMCRA[SDAR_MODE] specअगरices how the SDAR should be updated in
	 * continous sampling mode.
	 *
	 * Inहाल of Power8:
	 * MMCRA[SDAR_MODE] will be programmed as "0b01" क्रम continous sampling
	 * mode and will be un-changed when setting MMCRA[63] (Marked events).
	 *
	 * Inहाल of Power9/घातer10:
	 * Marked event: MMCRA[SDAR_MODE] will be set to 0b00 ('No Updates'),
	 *               or अगर group alपढ़ोy have any marked events.
	 * For rest
	 *	MMCRA[SDAR_MODE] will be set from event code.
	 *      If sdar_mode from event is zero, शेष to 0b01. Hardware
	 *      requires that we set a non-zero value.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अगर (is_event_marked(event) || (*mmcra & MMCRA_SAMPLE_ENABLE))
			*mmcra &= MMCRA_SDAR_MODE_NO_UPDATES;
		अन्यथा अगर (sdar_mod_val(event))
			*mmcra |= sdar_mod_val(event) << MMCRA_SDAR_MODE_SHIFT;
		अन्यथा
			*mmcra |= MMCRA_SDAR_MODE_DCACHE;
	पूर्ण अन्यथा
		*mmcra |= MMCRA_SDAR_MODE_TLB;
पूर्ण

अटल u64 p10_thresh_cmp_val(u64 value)
अणु
	पूर्णांक exp = 0;
	u64 result = value;

	अगर (!value)
		वापस value;

	/*
	 * Inहाल of P10, thresh_cmp value is not part of raw event code
	 * and provided via attr.config1 parameter. To program threshold in MMCRA,
	 * take a 18 bit number N and shअगरt right 2 places and increment
	 * the exponent E by 1 until the upper 10 bits of N are zero.
	 * Write E to the threshold exponent and ग_लिखो the lower 8 bits of N
	 * to the threshold mantissa.
	 * The max threshold that can be written is 261120.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		अगर (value > 261120)
			value = 261120;
		जबतक ((64 - __builtin_clzl(value)) > 8) अणु
			exp++;
			value >>= 2;
		पूर्ण

		/*
		 * Note that it is invalid to ग_लिखो a mantissa with the
		 * upper 2 bits of mantissa being zero, unless the
		 * exponent is also zero.
		 */
		अगर (!(value & 0xC0) && exp)
			result = 0;
		अन्यथा
			result = (exp << 8) | value;
	पूर्ण
	वापस result;
पूर्ण

अटल u64 thresh_cmp_val(u64 value)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		value = p10_thresh_cmp_val(value);

	/*
	 * Since location of threshold compare bits in MMCRA
	 * is dअगरferent क्रम p8, using dअगरferent shअगरt value.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		वापस value << p9_MMCRA_THR_CMP_SHIFT;
	अन्यथा
		वापस value << MMCRA_THR_CMP_SHIFT;
पूर्ण

अटल अचिन्हित दीर्घ combine_from_event(u64 event)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		वापस p9_EVENT_COMBINE(event);

	वापस EVENT_COMBINE(event);
पूर्ण

अटल अचिन्हित दीर्घ combine_shअगरt(अचिन्हित दीर्घ pmc)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		वापस p9_MMCR1_COMBINE_SHIFT(pmc);

	वापस MMCR1_COMBINE_SHIFT(pmc);
पूर्ण

अटल अंतरभूत bool event_is_threshold(u64 event)
अणु
	वापस (event >> EVENT_THR_SEL_SHIFT) & EVENT_THR_SEL_MASK;
पूर्ण

अटल bool is_thresh_cmp_valid(u64 event)
अणु
	अचिन्हित पूर्णांक cmp, exp;

	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		वापस p10_thresh_cmp_val(event) != 0;

	/*
	 * Check the mantissa upper two bits are not zero, unless the
	 * exponent is also zero. See the THRESH_CMP_MANTISSA करोc.
	 */

	cmp = (event >> EVENT_THR_CMP_SHIFT) & EVENT_THR_CMP_MASK;
	exp = cmp >> 7;

	अगर (exp && (cmp & 0x60) == 0)
		वापस false;

	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक dc_ic_rld_quad_l1_sel(u64 event)
अणु
	अचिन्हित पूर्णांक cache;

	cache = (event >> EVENT_CACHE_SEL_SHIFT) & MMCR1_DC_IC_QUAL_MASK;
	वापस cache;
पूर्ण

अटल अंतरभूत u64 isa207_find_source(u64 idx, u32 sub_idx)
अणु
	u64 ret = PERF_MEM_NA;

	चयन(idx) अणु
	हाल 0:
		/* Nothing to करो */
		अवरोध;
	हाल 1:
		ret = PH(LVL, L1);
		अवरोध;
	हाल 2:
		ret = PH(LVL, L2);
		अवरोध;
	हाल 3:
		ret = PH(LVL, L3);
		अवरोध;
	हाल 4:
		अगर (sub_idx <= 1)
			ret = PH(LVL, LOC_RAM);
		अन्यथा अगर (sub_idx > 1 && sub_idx <= 2)
			ret = PH(LVL, REM_RAM1);
		अन्यथा
			ret = PH(LVL, REM_RAM2);
		ret |= P(SNOOP, HIT);
		अवरोध;
	हाल 5:
		ret = PH(LVL, REM_CCE1);
		अगर ((sub_idx == 0) || (sub_idx == 2) || (sub_idx == 4))
			ret |= P(SNOOP, HIT);
		अन्यथा अगर ((sub_idx == 1) || (sub_idx == 3) || (sub_idx == 5))
			ret |= P(SNOOP, HITM);
		अवरोध;
	हाल 6:
		ret = PH(LVL, REM_CCE2);
		अगर ((sub_idx == 0) || (sub_idx == 2))
			ret |= P(SNOOP, HIT);
		अन्यथा अगर ((sub_idx == 1) || (sub_idx == 3))
			ret |= P(SNOOP, HITM);
		अवरोध;
	हाल 7:
		ret = PM(LVL, L1);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम isa207_get_mem_data_src(जोड़ perf_mem_data_src *dsrc, u32 flags,
							काष्ठा pt_regs *regs)
अणु
	u64 idx;
	u32 sub_idx;
	u64 sier;
	u64 val;

	/* Skip अगर no SIER support */
	अगर (!(flags & PPMU_HAS_SIER)) अणु
		dsrc->val = 0;
		वापस;
	पूर्ण

	sier = mfspr(SPRN_SIER);
	val = (sier & ISA207_SIER_TYPE_MASK) >> ISA207_SIER_TYPE_SHIFT;
	अगर (val != 1 && val != 2 && !(val == 7 && cpu_has_feature(CPU_FTR_ARCH_31)))
		वापस;

	idx = (sier & ISA207_SIER_LDST_MASK) >> ISA207_SIER_LDST_SHIFT;
	sub_idx = (sier & ISA207_SIER_DATA_SRC_MASK) >> ISA207_SIER_DATA_SRC_SHIFT;

	dsrc->val = isa207_find_source(idx, sub_idx);
	अगर (val == 7) अणु
		u64 mmcra;
		u32 op_type;

		/*
		 * Type 0b111 denotes either larx or stcx inकाष्ठाion. Use the
		 * MMCRA sampling bits [57:59] aदीर्घ with the type value
		 * to determine the exact inकाष्ठाion type. If the sampling
		 * criteria is neither load or store, set the type as शेष
		 * to NA.
		 */
		mmcra = mfspr(SPRN_MMCRA);

		op_type = (mmcra >> MMCRA_SAMP_ELIG_SHIFT) & MMCRA_SAMP_ELIG_MASK;
		चयन (op_type) अणु
		हाल 5:
			dsrc->val |= P(OP, LOAD);
			अवरोध;
		हाल 7:
			dsrc->val |= P(OP, STORE);
			अवरोध;
		शेष:
			dsrc->val |= P(OP, NA);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		dsrc->val |= (val == 1) ? P(OP, LOAD) : P(OP, STORE);
	पूर्ण
पूर्ण

व्योम isa207_get_mem_weight(u64 *weight, u64 type)
अणु
	जोड़ perf_sample_weight *weight_fields;
	u64 weight_lat;
	u64 mmcra = mfspr(SPRN_MMCRA);
	u64 exp = MMCRA_THR_CTR_EXP(mmcra);
	u64 mantissa = MMCRA_THR_CTR_MANT(mmcra);
	u64 sier = mfspr(SPRN_SIER);
	u64 val = (sier & ISA207_SIER_TYPE_MASK) >> ISA207_SIER_TYPE_SHIFT;

	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		mantissa = P10_MMCRA_THR_CTR_MANT(mmcra);

	अगर (val == 0 || (val == 7 && !cpu_has_feature(CPU_FTR_ARCH_31)))
		weight_lat = 0;
	अन्यथा
		weight_lat = mantissa << (2 * exp);

	/*
	 * Use 64 bit weight field (full) अगर sample type is
	 * WEIGHT.
	 *
	 * अगर sample type is WEIGHT_STRUCT:
	 * - store memory latency in the lower 32 bits.
	 * - For ISA v3.1, use reमुख्यing two 16 bit fields of
	 *   perf_sample_weight to store cycle counter values
	 *   from sier2.
	 */
	weight_fields = (जोड़ perf_sample_weight *)weight;
	अगर (type & PERF_SAMPLE_WEIGHT)
		weight_fields->full = weight_lat;
	अन्यथा अणु
		weight_fields->var1_dw = (u32)weight_lat;
		अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
			weight_fields->var2_w = P10_SIER2_FINISH_CYC(mfspr(SPRN_SIER2));
			weight_fields->var3_w = P10_SIER2_DISPATCH_CYC(mfspr(SPRN_SIER2));
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक isa207_get_स्थिरraपूर्णांक(u64 event, अचिन्हित दीर्घ *maskp, अचिन्हित दीर्घ *valp, u64 event_config1)
अणु
	अचिन्हित पूर्णांक unit, pmc, cache, ebb;
	अचिन्हित दीर्घ mask, value;

	mask = value = 0;

	अगर (!is_event_valid(event))
		वापस -1;

	pmc   = (event >> EVENT_PMC_SHIFT)        & EVENT_PMC_MASK;
	unit  = (event >> EVENT_UNIT_SHIFT)       & EVENT_UNIT_MASK;
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		cache = (event >> EVENT_CACHE_SEL_SHIFT) &
			p10_EVENT_CACHE_SEL_MASK;
	अन्यथा
		cache = (event >> EVENT_CACHE_SEL_SHIFT) &
			EVENT_CACHE_SEL_MASK;
	ebb   = (event >> EVENT_EBB_SHIFT)        & EVENT_EBB_MASK;

	अगर (pmc) अणु
		u64 base_event;

		अगर (pmc > 6)
			वापस -1;

		/* Ignore Linux defined bits when checking event below */
		base_event = event & ~EVENT_LINUX_MASK;

		अगर (pmc >= 5 && base_event != 0x500fa &&
				base_event != 0x600f4)
			वापस -1;

		mask  |= CNST_PMC_MASK(pmc);
		value |= CNST_PMC_VAL(pmc);

		/*
		 * PMC5 and PMC6 are used to count cycles and inकाष्ठाions and
		 * they करो not support most of the स्थिरraपूर्णांक bits. Add a check
		 * to exclude PMC5/6 from most of the स्थिरraपूर्णांकs except क्रम
		 * EBB/BHRB.
		 */
		अगर (pmc >= 5)
			जाओ ebb_bhrb;
	पूर्ण

	अगर (pmc <= 4) अणु
		/*
		 * Add to number of counters in use. Note this includes events with
		 * a PMC of 0 - they still need a PMC, it's just asचिन्हित later.
		 * Don't count events on PMC 5 & 6, there is only one valid event
		 * on each of those counters, and they are handled above.
		 */
		mask  |= CNST_NC_MASK;
		value |= CNST_NC_VAL;
	पूर्ण

	अगर (unit >= 6 && unit <= 9) अणु
		अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
			अगर (unit == 6) अणु
				mask |= CNST_L2L3_GROUP_MASK;
				value |= CNST_L2L3_GROUP_VAL(event >> p10_L2L3_EVENT_SHIFT);
			पूर्ण
		पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			mask  |= CNST_CACHE_GROUP_MASK;
			value |= CNST_CACHE_GROUP_VAL(event & 0xff);

			mask |= CNST_CACHE_PMC4_MASK;
			अगर (pmc == 4)
				value |= CNST_CACHE_PMC4_VAL;
		पूर्ण अन्यथा अगर (cache & 0x7) अणु
			/*
			 * L2/L3 events contain a cache selector field, which is
			 * supposed to be programmed पूर्णांकo MMCRC. However MMCRC is only
			 * HV writable, and there is no API क्रम guest kernels to modअगरy
			 * it. The solution is क्रम the hypervisor to initialise the
			 * field to zeroes, and क्रम us to only ever allow events that
			 * have a cache selector of zero. The bank selector (bit 3) is
			 * irrelevant, as दीर्घ as the rest of the value is 0.
			 */
			वापस -1;
		पूर्ण

	पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_300) || (event & EVENT_IS_L1)) अणु
		mask  |= CNST_L1_QUAL_MASK;
		value |= CNST_L1_QUAL_VAL(cache);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		mask |= CNST_RADIX_SCOPE_GROUP_MASK;
		value |= CNST_RADIX_SCOPE_GROUP_VAL(event >> p10_EVENT_RADIX_SCOPE_QUAL_SHIFT);
	पूर्ण

	अगर (is_event_marked(event)) अणु
		mask  |= CNST_SAMPLE_MASK;
		value |= CNST_SAMPLE_VAL(event >> EVENT_SAMPLE_SHIFT);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		अगर (event_is_threshold(event) && is_thresh_cmp_valid(event_config1)) अणु
			mask  |= CNST_THRESH_CTL_SEL_MASK;
			value |= CNST_THRESH_CTL_SEL_VAL(event >> EVENT_THRESH_SHIFT);
			mask  |= p10_CNST_THRESH_CMP_MASK;
			value |= p10_CNST_THRESH_CMP_VAL(p10_thresh_cmp_val(event_config1));
		पूर्ण
	पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_300))  अणु
		अगर (event_is_threshold(event) && is_thresh_cmp_valid(event)) अणु
			mask  |= CNST_THRESH_MASK;
			value |= CNST_THRESH_VAL(event >> EVENT_THRESH_SHIFT);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Special हाल क्रम PM_MRK_FAB_RSP_MATCH and PM_MRK_FAB_RSP_MATCH_CYC,
		 * the threshold control bits are used क्रम the match value.
		 */
		अगर (event_is_fab_match(event)) अणु
			mask  |= CNST_FAB_MATCH_MASK;
			value |= CNST_FAB_MATCH_VAL(event >> EVENT_THR_CTL_SHIFT);
		पूर्ण अन्यथा अणु
			अगर (!is_thresh_cmp_valid(event))
				वापस -1;

			mask  |= CNST_THRESH_MASK;
			value |= CNST_THRESH_VAL(event >> EVENT_THRESH_SHIFT);
		पूर्ण
	पूर्ण

ebb_bhrb:
	अगर (!pmc && ebb)
		/* EBB events must specअगरy the PMC */
		वापस -1;

	अगर (event & EVENT_WANTS_BHRB) अणु
		अगर (!ebb)
			/* Only EBB events can request BHRB */
			वापस -1;

		mask  |= CNST_IFM_MASK;
		value |= CNST_IFM_VAL(event >> EVENT_IFM_SHIFT);
	पूर्ण

	/*
	 * All events must agree on EBB, either all request it or none.
	 * EBB events are pinned & exclusive, so this should never actually
	 * hit, but we leave it as a fallback in हाल.
	 */
	mask  |= CNST_EBB_MASK;
	value |= CNST_EBB_VAL(ebb);

	*maskp = mask;
	*valp = value;

	वापस 0;
पूर्ण

पूर्णांक isa207_compute_mmcr(u64 event[], पूर्णांक n_ev,
			       अचिन्हित पूर्णांक hwc[], काष्ठा mmcr_regs *mmcr,
			       काष्ठा perf_event *pevents[], u32 flags)
अणु
	अचिन्हित दीर्घ mmcra, mmcr1, mmcr2, unit, combine, psel, cache, val;
	अचिन्हित दीर्घ mmcr3;
	अचिन्हित पूर्णांक pmc, pmc_inuse;
	पूर्णांक i;

	pmc_inuse = 0;

	/* First pass to count resource use */
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc = (event[i] >> EVENT_PMC_SHIFT) & EVENT_PMC_MASK;
		अगर (pmc)
			pmc_inuse |= 1 << pmc;
	पूर्ण

	mmcra = mmcr1 = mmcr2 = mmcr3 = 0;

	/*
	 * Disable bhrb unless explicitly requested
	 * by setting MMCRA (BHRBRD) bit.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		mmcra |= MMCRA_BHRB_DISABLE;

	/* Second pass: assign PMCs, set all MMCR1 fields */
	क्रम (i = 0; i < n_ev; ++i) अणु
		pmc     = (event[i] >> EVENT_PMC_SHIFT) & EVENT_PMC_MASK;
		unit    = (event[i] >> EVENT_UNIT_SHIFT) & EVENT_UNIT_MASK;
		combine = combine_from_event(event[i]);
		psel    =  event[i] & EVENT_PSEL_MASK;

		अगर (!pmc) अणु
			क्रम (pmc = 1; pmc <= 4; ++pmc) अणु
				अगर (!(pmc_inuse & (1 << pmc)))
					अवरोध;
			पूर्ण

			pmc_inuse |= 1 << pmc;
		पूर्ण

		अगर (pmc <= 4) अणु
			mmcr1 |= unit << MMCR1_UNIT_SHIFT(pmc);
			mmcr1 |= combine << combine_shअगरt(pmc);
			mmcr1 |= psel << MMCR1_PMCSEL_SHIFT(pmc);
		पूर्ण

		/* In continuous sampling mode, update SDAR on TLB miss */
		mmcra_sdar_mode(event[i], &mmcra);

		अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			cache = dc_ic_rld_quad_l1_sel(event[i]);
			mmcr1 |= (cache) << MMCR1_DC_IC_QUAL_SHIFT;
		पूर्ण अन्यथा अणु
			अगर (event[i] & EVENT_IS_L1) अणु
				cache = dc_ic_rld_quad_l1_sel(event[i]);
				mmcr1 |= (cache) << MMCR1_DC_IC_QUAL_SHIFT;
			पूर्ण
		पूर्ण

		/* Set RADIX_SCOPE_QUAL bit */
		अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
			val = (event[i] >> p10_EVENT_RADIX_SCOPE_QUAL_SHIFT) &
				p10_EVENT_RADIX_SCOPE_QUAL_MASK;
			mmcr1 |= val << p10_MMCR1_RADIX_SCOPE_QUAL_SHIFT;
		पूर्ण

		अगर (is_event_marked(event[i])) अणु
			mmcra |= MMCRA_SAMPLE_ENABLE;

			val = (event[i] >> EVENT_SAMPLE_SHIFT) & EVENT_SAMPLE_MASK;
			अगर (val) अणु
				mmcra |= (val &  3) << MMCRA_SAMP_MODE_SHIFT;
				mmcra |= (val >> 2) << MMCRA_SAMP_ELIG_SHIFT;
			पूर्ण
		पूर्ण

		/*
		 * PM_MRK_FAB_RSP_MATCH and PM_MRK_FAB_RSP_MATCH_CYC,
		 * the threshold bits are used क्रम the match value.
		 */
		अगर (!cpu_has_feature(CPU_FTR_ARCH_300) && event_is_fab_match(event[i])) अणु
			mmcr1 |= ((event[i] >> EVENT_THR_CTL_SHIFT) &
				  EVENT_THR_CTL_MASK) << MMCR1_FAB_SHIFT;
		पूर्ण अन्यथा अणु
			val = (event[i] >> EVENT_THR_CTL_SHIFT) & EVENT_THR_CTL_MASK;
			mmcra |= val << MMCRA_THR_CTL_SHIFT;
			val = (event[i] >> EVENT_THR_SEL_SHIFT) & EVENT_THR_SEL_MASK;
			mmcra |= val << MMCRA_THR_SEL_SHIFT;
			अगर (!cpu_has_feature(CPU_FTR_ARCH_31)) अणु
				val = (event[i] >> EVENT_THR_CMP_SHIFT) &
					EVENT_THR_CMP_MASK;
				mmcra |= thresh_cmp_val(val);
			पूर्ण अन्यथा अगर (flags & PPMU_HAS_ATTR_CONFIG1) अणु
				val = (pevents[i]->attr.config1 >> p10_EVENT_THR_CMP_SHIFT) &
					p10_EVENT_THR_CMP_MASK;
				mmcra |= thresh_cmp_val(val);
			पूर्ण
		पूर्ण

		अगर (cpu_has_feature(CPU_FTR_ARCH_31) && (unit == 6)) अणु
			val = (event[i] >> p10_L2L3_EVENT_SHIFT) &
				p10_EVENT_L2L3_SEL_MASK;
			mmcr2 |= val << p10_L2L3_SEL_SHIFT;
		पूर्ण

		अगर (event[i] & EVENT_WANTS_BHRB) अणु
			val = (event[i] >> EVENT_IFM_SHIFT) & EVENT_IFM_MASK;
			mmcra |= val << MMCRA_IFM_SHIFT;
		पूर्ण

		/* set MMCRA (BHRBRD) to 0 अगर there is user request क्रम BHRB */
		अगर (cpu_has_feature(CPU_FTR_ARCH_31) &&
				(has_branch_stack(pevents[i]) || (event[i] & EVENT_WANTS_BHRB)))
			mmcra &= ~MMCRA_BHRB_DISABLE;

		अगर (pevents[i]->attr.exclude_user)
			mmcr2 |= MMCR2_FCP(pmc);

		अगर (pevents[i]->attr.exclude_hv)
			mmcr2 |= MMCR2_FCH(pmc);

		अगर (pevents[i]->attr.exclude_kernel) अणु
			अगर (cpu_has_feature(CPU_FTR_HVMODE))
				mmcr2 |= MMCR2_FCH(pmc);
			अन्यथा
				mmcr2 |= MMCR2_FCS(pmc);
		पूर्ण

		अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
			अगर (pmc <= 4) अणु
				val = (event[i] >> p10_EVENT_MMCR3_SHIFT) &
					p10_EVENT_MMCR3_MASK;
				mmcr3 |= val << MMCR3_SHIFT(pmc);
			पूर्ण
		पूर्ण

		hwc[i] = pmc - 1;
	पूर्ण

	/* Return MMCRx values */
	mmcr->mmcr0 = 0;

	/* pmc_inuse is 1-based */
	अगर (pmc_inuse & 2)
		mmcr->mmcr0 = MMCR0_PMC1CE;

	अगर (pmc_inuse & 0x7c)
		mmcr->mmcr0 |= MMCR0_PMCjCE;

	/* If we're not using PMC 5 or 6, मुक्तze them */
	अगर (!(pmc_inuse & 0x60))
		mmcr->mmcr0 |= MMCR0_FC56;

	/*
	 * Set mmcr0 (PMCCEXT) क्रम p10 which
	 * will restrict access to group B रेजिस्टरs
	 * when MMCR0 PMCC=0b00.
	 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_31))
		mmcr->mmcr0 |= MMCR0_PMCCEXT;

	mmcr->mmcr1 = mmcr1;
	mmcr->mmcra = mmcra;
	mmcr->mmcr2 = mmcr2;
	mmcr->mmcr3 = mmcr3;

	वापस 0;
पूर्ण

व्योम isa207_disable_pmc(अचिन्हित पूर्णांक pmc, काष्ठा mmcr_regs *mmcr)
अणु
	अगर (pmc <= 3)
		mmcr->mmcr1 &= ~(0xffUL << MMCR1_PMCSEL_SHIFT(pmc + 1));
पूर्ण

अटल पूर्णांक find_alternative(u64 event, स्थिर अचिन्हित पूर्णांक ev_alt[][MAX_ALT], पूर्णांक size)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < size; ++i) अणु
		अगर (event < ev_alt[i][0])
			अवरोध;

		क्रम (j = 0; j < MAX_ALT && ev_alt[i][j]; ++j)
			अगर (event == ev_alt[i][j])
				वापस i;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक isa207_get_alternatives(u64 event, u64 alt[], पूर्णांक size, अचिन्हित पूर्णांक flags,
					स्थिर अचिन्हित पूर्णांक ev_alt[][MAX_ALT])
अणु
	पूर्णांक i, j, num_alt = 0;
	u64 alt_event;

	alt[num_alt++] = event;
	i = find_alternative(event, ev_alt, size);
	अगर (i >= 0) अणु
		/* Filter out the original event, it's alपढ़ोy in alt[0] */
		क्रम (j = 0; j < MAX_ALT; ++j) अणु
			alt_event = ev_alt[i][j];
			अगर (alt_event && alt_event != event)
				alt[num_alt++] = alt_event;
		पूर्ण
	पूर्ण

	अगर (flags & PPMU_ONLY_COUNT_RUN) अणु
		/*
		 * We're only counting in RUN state, so PM_CYC is equivalent to
		 * PM_RUN_CYC and PM_INST_CMPL === PM_RUN_INST_CMPL.
		 */
		j = num_alt;
		क्रम (i = 0; i < num_alt; ++i) अणु
			चयन (alt[i]) अणु
			हाल 0x1e:			/* PMC_CYC */
				alt[j++] = 0x600f4;	/* PM_RUN_CYC */
				अवरोध;
			हाल 0x600f4:
				alt[j++] = 0x1e;
				अवरोध;
			हाल 0x2:			/* PM_INST_CMPL */
				alt[j++] = 0x500fa;	/* PM_RUN_INST_CMPL */
				अवरोध;
			हाल 0x500fa:
				alt[j++] = 0x2;
				अवरोध;
			पूर्ण
		पूर्ण
		num_alt = j;
	पूर्ण

	वापस num_alt;
पूर्ण

पूर्णांक isa3XX_check_attr_config(काष्ठा perf_event *ev)
अणु
	u64 val, sample_mode;
	u64 event = ev->attr.config;

	val = (event >> EVENT_SAMPLE_SHIFT) & EVENT_SAMPLE_MASK;
	sample_mode = val & 0x3;

	/*
	 * MMCRA[61:62] is Ranकरोm Sampling Mode (SM).
	 * value of 0b11 is reserved.
	 */
	अगर (sample_mode == 0x3)
		वापस -EINVAL;

	/*
	 * Check क्रम all reserved value
	 * Source: Perक्रमmance Monitoring Unit User Guide
	 */
	चयन (val) अणु
	हाल 0x5:
	हाल 0x9:
	हाल 0xD:
	हाल 0x19:
	हाल 0x1D:
	हाल 0x1A:
	हाल 0x1E:
		वापस -EINVAL;
	पूर्ण

	/*
	 * MMCRA[48:51]/[52:55]) Threshold Start/Stop
	 * Events Selection.
	 * 0b11110000/0b00001111 is reserved.
	 */
	val = (event >> EVENT_THR_CTL_SHIFT) & EVENT_THR_CTL_MASK;
	अगर (((val & 0xF0) == 0xF0) || ((val & 0xF) == 0xF))
		वापस -EINVAL;

	वापस 0;
पूर्ण
