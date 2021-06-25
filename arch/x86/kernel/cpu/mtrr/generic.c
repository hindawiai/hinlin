<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This only handles 32bit MTRR on 32bit hosts. This is strictly wrong
 * because MTRRs can span up to 40 bits (36bits on most modern x86)
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/processor-flags.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/memtype.h>

#समावेश "mtrr.h"

काष्ठा fixed_range_block अणु
	पूर्णांक base_msr;		/* start address of an MTRR block */
	पूर्णांक ranges;		/* number of MTRRs in this block  */
पूर्ण;

अटल काष्ठा fixed_range_block fixed_range_blocks[] = अणु
	अणु MSR_MTRRfix64K_00000, 1 पूर्ण, /* one   64k MTRR  */
	अणु MSR_MTRRfix16K_80000, 2 पूर्ण, /* two   16k MTRRs */
	अणु MSR_MTRRfix4K_C0000,  8 पूर्ण, /* eight  4k MTRRs */
	अणुपूर्ण
पूर्ण;

अटल अचिन्हित दीर्घ smp_changes_mask;
अटल पूर्णांक mtrr_state_set;
u64 mtrr_tom2;

काष्ठा mtrr_state_type mtrr_state;
EXPORT_SYMBOL_GPL(mtrr_state);

/*
 * BIOS is expected to clear MtrrFixDramModEn bit, see क्रम example
 * "BIOS and Kernel Developer's Guide क्रम the AMD Athlon 64 and AMD
 * Opteron Processors" (26094 Rev. 3.30 February 2006), section
 * "13.2.1.2 SYSCFG Register": "The MtrrFixDramModEn bit should be set
 * to 1 during BIOS initialization of the fixed MTRRs, then cleared to
 * 0 क्रम operation."
 */
अटल अंतरभूत व्योम k8_check_syscfg_dram_mod_en(व्योम)
अणु
	u32 lo, hi;

	अगर (!((boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD) &&
	      (boot_cpu_data.x86 >= 0x0f)))
		वापस;

	rdmsr(MSR_AMD64_SYSCFG, lo, hi);
	अगर (lo & K8_MTRRFIXRANGE_DRAM_MODIFY) अणु
		pr_err(FW_WARN "MTRR: CPU %u: SYSCFG[MtrrFixDramModEn]"
		       " not cleared by BIOS, clearing this bit\n",
		       smp_processor_id());
		lo &= ~K8_MTRRFIXRANGE_DRAM_MODIFY;
		mtrr_wrmsr(MSR_AMD64_SYSCFG, lo, hi);
	पूर्ण
पूर्ण

/* Get the size of contiguous MTRR range */
अटल u64 get_mtrr_size(u64 mask)
अणु
	u64 size;

	mask >>= PAGE_SHIFT;
	mask |= size_or_mask;
	size = -mask;
	size <<= PAGE_SHIFT;
	वापस size;
पूर्ण

/*
 * Check and वापस the effective type क्रम MTRR-MTRR type overlap.
 * Returns 1 अगर the effective type is UNCACHEABLE, अन्यथा वापसs 0
 */
अटल पूर्णांक check_type_overlap(u8 *prev, u8 *curr)
अणु
	अगर (*prev == MTRR_TYPE_UNCACHABLE || *curr == MTRR_TYPE_UNCACHABLE) अणु
		*prev = MTRR_TYPE_UNCACHABLE;
		*curr = MTRR_TYPE_UNCACHABLE;
		वापस 1;
	पूर्ण

	अगर ((*prev == MTRR_TYPE_WRBACK && *curr == MTRR_TYPE_WRTHROUGH) ||
	    (*prev == MTRR_TYPE_WRTHROUGH && *curr == MTRR_TYPE_WRBACK)) अणु
		*prev = MTRR_TYPE_WRTHROUGH;
		*curr = MTRR_TYPE_WRTHROUGH;
	पूर्ण

	अगर (*prev != *curr) अणु
		*prev = MTRR_TYPE_UNCACHABLE;
		*curr = MTRR_TYPE_UNCACHABLE;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mtrr_type_lookup_fixed - look up memory type in MTRR fixed entries
 *
 * Return the MTRR fixed memory type of 'start'.
 *
 * MTRR fixed entries are भागided पूर्णांकo the following ways:
 *  0x00000 - 0x7FFFF : This range is भागided पूर्णांकo eight 64KB sub-ranges
 *  0x80000 - 0xBFFFF : This range is भागided पूर्णांकo sixteen 16KB sub-ranges
 *  0xC0000 - 0xFFFFF : This range is भागided पूर्णांकo sixty-four 4KB sub-ranges
 *
 * Return Values:
 * MTRR_TYPE_(type)  - Matched memory type
 * MTRR_TYPE_INVALID - Unmatched
 */
अटल u8 mtrr_type_lookup_fixed(u64 start, u64 end)
अणु
	पूर्णांक idx;

	अगर (start >= 0x100000)
		वापस MTRR_TYPE_INVALID;

	/* 0x0 - 0x7FFFF */
	अगर (start < 0x80000) अणु
		idx = 0;
		idx += (start >> 16);
		वापस mtrr_state.fixed_ranges[idx];
	/* 0x80000 - 0xBFFFF */
	पूर्ण अन्यथा अगर (start < 0xC0000) अणु
		idx = 1 * 8;
		idx += ((start - 0x80000) >> 14);
		वापस mtrr_state.fixed_ranges[idx];
	पूर्ण

	/* 0xC0000 - 0xFFFFF */
	idx = 3 * 8;
	idx += ((start - 0xC0000) >> 12);
	वापस mtrr_state.fixed_ranges[idx];
पूर्ण

/**
 * mtrr_type_lookup_variable - look up memory type in MTRR variable entries
 *
 * Return Value:
 * MTRR_TYPE_(type) - Matched memory type or शेष memory type (unmatched)
 *
 * Output Arguments:
 * repeat - Set to 1 when [start:end] spanned across MTRR range and type
 *	    वापसed corresponds only to [start:*partial_end].  Caller has
 *	    to lookup again क्रम [*partial_end:end].
 *
 * unअगरorm - Set to 1 when an MTRR covers the region unअगरormly, i.e. the
 *	     region is fully covered by a single MTRR entry or the शेष
 *	     type.
 */
अटल u8 mtrr_type_lookup_variable(u64 start, u64 end, u64 *partial_end,
				    पूर्णांक *repeat, u8 *unअगरorm)
अणु
	पूर्णांक i;
	u64 base, mask;
	u8 prev_match, curr_match;

	*repeat = 0;
	*unअगरorm = 1;

	prev_match = MTRR_TYPE_INVALID;
	क्रम (i = 0; i < num_var_ranges; ++i) अणु
		अचिन्हित लघु start_state, end_state, inclusive;

		अगर (!(mtrr_state.var_ranges[i].mask_lo & (1 << 11)))
			जारी;

		base = (((u64)mtrr_state.var_ranges[i].base_hi) << 32) +
		       (mtrr_state.var_ranges[i].base_lo & PAGE_MASK);
		mask = (((u64)mtrr_state.var_ranges[i].mask_hi) << 32) +
		       (mtrr_state.var_ranges[i].mask_lo & PAGE_MASK);

		start_state = ((start & mask) == (base & mask));
		end_state = ((end & mask) == (base & mask));
		inclusive = ((start < base) && (end > base));

		अगर ((start_state != end_state) || inclusive) अणु
			/*
			 * We have start:end spanning across an MTRR.
			 * We split the region पूर्णांकo either
			 *
			 * - start_state:1
			 * (start:mtrr_end)(mtrr_end:end)
			 * - end_state:1
			 * (start:mtrr_start)(mtrr_start:end)
			 * - inclusive:1
			 * (start:mtrr_start)(mtrr_start:mtrr_end)(mtrr_end:end)
			 *
			 * depending on kind of overlap.
			 *
			 * Return the type of the first region and a poपूर्णांकer
			 * to the start of next region so that caller will be
			 * advised to lookup again after having adjusted start
			 * and end.
			 *
			 * Note: This way we handle overlaps with multiple
			 * entries and the शेष type properly.
			 */
			अगर (start_state)
				*partial_end = base + get_mtrr_size(mask);
			अन्यथा
				*partial_end = base;

			अगर (unlikely(*partial_end <= start)) अणु
				WARN_ON(1);
				*partial_end = start + PAGE_SIZE;
			पूर्ण

			end = *partial_end - 1; /* end is inclusive */
			*repeat = 1;
			*unअगरorm = 0;
		पूर्ण

		अगर ((start & mask) != (base & mask))
			जारी;

		curr_match = mtrr_state.var_ranges[i].base_lo & 0xff;
		अगर (prev_match == MTRR_TYPE_INVALID) अणु
			prev_match = curr_match;
			जारी;
		पूर्ण

		*unअगरorm = 0;
		अगर (check_type_overlap(&prev_match, &curr_match))
			वापस curr_match;
	पूर्ण

	अगर (prev_match != MTRR_TYPE_INVALID)
		वापस prev_match;

	वापस mtrr_state.def_type;
पूर्ण

/**
 * mtrr_type_lookup - look up memory type in MTRR
 *
 * Return Values:
 * MTRR_TYPE_(type)  - The effective MTRR type क्रम the region
 * MTRR_TYPE_INVALID - MTRR is disabled
 *
 * Output Argument:
 * unअगरorm - Set to 1 when an MTRR covers the region unअगरormly, i.e. the
 *	     region is fully covered by a single MTRR entry or the शेष
 *	     type.
 */
u8 mtrr_type_lookup(u64 start, u64 end, u8 *unअगरorm)
अणु
	u8 type, prev_type, is_unअगरorm = 1, dummy;
	पूर्णांक repeat;
	u64 partial_end;

	/* Make end inclusive instead of exclusive */
	end--;

	अगर (!mtrr_state_set)
		वापस MTRR_TYPE_INVALID;

	अगर (!(mtrr_state.enabled & MTRR_STATE_MTRR_ENABLED))
		वापस MTRR_TYPE_INVALID;

	/*
	 * Look up the fixed ranges first, which take priority over
	 * the variable ranges.
	 */
	अगर ((start < 0x100000) &&
	    (mtrr_state.have_fixed) &&
	    (mtrr_state.enabled & MTRR_STATE_MTRR_FIXED_ENABLED)) अणु
		is_unअगरorm = 0;
		type = mtrr_type_lookup_fixed(start, end);
		जाओ out;
	पूर्ण

	/*
	 * Look up the variable ranges.  Look of multiple ranges matching
	 * this address and pick type as per MTRR precedence.
	 */
	type = mtrr_type_lookup_variable(start, end, &partial_end,
					 &repeat, &is_unअगरorm);

	/*
	 * Common path is with repeat = 0.
	 * However, we can have हालs where [start:end] spans across some
	 * MTRR ranges and/or the शेष type.  Do repeated lookups क्रम
	 * that हाल here.
	 */
	जबतक (repeat) अणु
		prev_type = type;
		start = partial_end;
		is_unअगरorm = 0;
		type = mtrr_type_lookup_variable(start, end, &partial_end,
						 &repeat, &dummy);

		अगर (check_type_overlap(&prev_type, &type))
			जाओ out;
	पूर्ण

	अगर (mtrr_tom2 && (start >= (1ULL<<32)) && (end < mtrr_tom2))
		type = MTRR_TYPE_WRBACK;

out:
	*unअगरorm = is_unअगरorm;
	वापस type;
पूर्ण

/* Get the MSR pair relating to a var range */
अटल व्योम
get_mtrr_var_range(अचिन्हित पूर्णांक index, काष्ठा mtrr_var_range *vr)
अणु
	rdmsr(MTRRphysBase_MSR(index), vr->base_lo, vr->base_hi);
	rdmsr(MTRRphysMask_MSR(index), vr->mask_lo, vr->mask_hi);
पूर्ण

/* Fill the MSR pair relating to a var range */
व्योम fill_mtrr_var_range(अचिन्हित पूर्णांक index,
		u32 base_lo, u32 base_hi, u32 mask_lo, u32 mask_hi)
अणु
	काष्ठा mtrr_var_range *vr;

	vr = mtrr_state.var_ranges;

	vr[index].base_lo = base_lo;
	vr[index].base_hi = base_hi;
	vr[index].mask_lo = mask_lo;
	vr[index].mask_hi = mask_hi;
पूर्ण

अटल व्योम get_fixed_ranges(mtrr_type *frs)
अणु
	अचिन्हित पूर्णांक *p = (अचिन्हित पूर्णांक *)frs;
	पूर्णांक i;

	k8_check_syscfg_dram_mod_en();

	rdmsr(MSR_MTRRfix64K_00000, p[0], p[1]);

	क्रम (i = 0; i < 2; i++)
		rdmsr(MSR_MTRRfix16K_80000 + i, p[2 + i * 2], p[3 + i * 2]);
	क्रम (i = 0; i < 8; i++)
		rdmsr(MSR_MTRRfix4K_C0000 + i, p[6 + i * 2], p[7 + i * 2]);
पूर्ण

व्योम mtrr_save_fixed_ranges(व्योम *info)
अणु
	अगर (boot_cpu_has(X86_FEATURE_MTRR))
		get_fixed_ranges(mtrr_state.fixed_ranges);
पूर्ण

अटल अचिन्हित __initdata last_fixed_start;
अटल अचिन्हित __initdata last_fixed_end;
अटल mtrr_type __initdata last_fixed_type;

अटल व्योम __init prपूर्णांक_fixed_last(व्योम)
अणु
	अगर (!last_fixed_end)
		वापस;

	pr_debug("  %05X-%05X %s\n", last_fixed_start,
		 last_fixed_end - 1, mtrr_attrib_to_str(last_fixed_type));

	last_fixed_end = 0;
पूर्ण

अटल व्योम __init update_fixed_last(अचिन्हित base, अचिन्हित end,
				     mtrr_type type)
अणु
	last_fixed_start = base;
	last_fixed_end = end;
	last_fixed_type = type;
पूर्ण

अटल व्योम __init
prपूर्णांक_fixed(अचिन्हित base, अचिन्हित step, स्थिर mtrr_type *types)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < 8; ++i, ++types, base += step) अणु
		अगर (last_fixed_end == 0) अणु
			update_fixed_last(base, base + step, *types);
			जारी;
		पूर्ण
		अगर (last_fixed_end == base && last_fixed_type == *types) अणु
			last_fixed_end = base + step;
			जारी;
		पूर्ण
		/* new segments: gap or dअगरferent type */
		prपूर्णांक_fixed_last();
		update_fixed_last(base, base + step, *types);
	पूर्ण
पूर्ण

अटल व्योम prepare_set(व्योम);
अटल व्योम post_set(व्योम);

अटल व्योम __init prपूर्णांक_mtrr_state(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक high_width;

	pr_debug("MTRR default type: %s\n",
		 mtrr_attrib_to_str(mtrr_state.def_type));
	अगर (mtrr_state.have_fixed) अणु
		pr_debug("MTRR fixed ranges %sabled:\n",
			((mtrr_state.enabled & MTRR_STATE_MTRR_ENABLED) &&
			 (mtrr_state.enabled & MTRR_STATE_MTRR_FIXED_ENABLED)) ?
			 "en" : "dis");
		prपूर्णांक_fixed(0x00000, 0x10000, mtrr_state.fixed_ranges + 0);
		क्रम (i = 0; i < 2; ++i)
			prपूर्णांक_fixed(0x80000 + i * 0x20000, 0x04000,
				    mtrr_state.fixed_ranges + (i + 1) * 8);
		क्रम (i = 0; i < 8; ++i)
			prपूर्णांक_fixed(0xC0000 + i * 0x08000, 0x01000,
				    mtrr_state.fixed_ranges + (i + 3) * 8);

		/* tail */
		prपूर्णांक_fixed_last();
	पूर्ण
	pr_debug("MTRR variable ranges %sabled:\n",
		 mtrr_state.enabled & MTRR_STATE_MTRR_ENABLED ? "en" : "dis");
	high_width = (__ffs64(size_or_mask) - (32 - PAGE_SHIFT) + 3) / 4;

	क्रम (i = 0; i < num_var_ranges; ++i) अणु
		अगर (mtrr_state.var_ranges[i].mask_lo & (1 << 11))
			pr_debug("  %u base %0*X%05X000 mask %0*X%05X000 %s\n",
				 i,
				 high_width,
				 mtrr_state.var_ranges[i].base_hi,
				 mtrr_state.var_ranges[i].base_lo >> 12,
				 high_width,
				 mtrr_state.var_ranges[i].mask_hi,
				 mtrr_state.var_ranges[i].mask_lo >> 12,
				 mtrr_attrib_to_str(mtrr_state.var_ranges[i].base_lo & 0xff));
		अन्यथा
			pr_debug("  %u disabled\n", i);
	पूर्ण
	अगर (mtrr_tom2)
		pr_debug("TOM2: %016llx aka %lldM\n", mtrr_tom2, mtrr_tom2>>20);
पूर्ण

/* PAT setup क्रम BP. We need to go through sync steps here */
व्योम __init mtrr_bp_pat_init(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	prepare_set();

	pat_init();

	post_set();
	local_irq_restore(flags);
पूर्ण

/* Grab all of the MTRR state क्रम this CPU पूर्णांकo *state */
bool __init get_mtrr_state(व्योम)
अणु
	काष्ठा mtrr_var_range *vrs;
	अचिन्हित lo, dummy;
	अचिन्हित पूर्णांक i;

	vrs = mtrr_state.var_ranges;

	rdmsr(MSR_MTRRcap, lo, dummy);
	mtrr_state.have_fixed = (lo >> 8) & 1;

	क्रम (i = 0; i < num_var_ranges; i++)
		get_mtrr_var_range(i, &vrs[i]);
	अगर (mtrr_state.have_fixed)
		get_fixed_ranges(mtrr_state.fixed_ranges);

	rdmsr(MSR_MTRRdefType, lo, dummy);
	mtrr_state.def_type = (lo & 0xff);
	mtrr_state.enabled = (lo & 0xc00) >> 10;

	अगर (amd_special_शेष_mtrr()) अणु
		अचिन्हित low, high;

		/* TOP_MEM2 */
		rdmsr(MSR_K8_TOP_MEM2, low, high);
		mtrr_tom2 = high;
		mtrr_tom2 <<= 32;
		mtrr_tom2 |= low;
		mtrr_tom2 &= 0xffffff800000ULL;
	पूर्ण

	prपूर्णांक_mtrr_state();

	mtrr_state_set = 1;

	वापस !!(mtrr_state.enabled & MTRR_STATE_MTRR_ENABLED);
पूर्ण

/* Some BIOS's are messed up and don't set all MTRRs the same! */
व्योम __init mtrr_state_warn(व्योम)
अणु
	अचिन्हित दीर्घ mask = smp_changes_mask;

	अगर (!mask)
		वापस;
	अगर (mask & MTRR_CHANGE_MASK_FIXED)
		pr_warn("mtrr: your CPUs had inconsistent fixed MTRR settings\n");
	अगर (mask & MTRR_CHANGE_MASK_VARIABLE)
		pr_warn("mtrr: your CPUs had inconsistent variable MTRR settings\n");
	अगर (mask & MTRR_CHANGE_MASK_DEFTYPE)
		pr_warn("mtrr: your CPUs had inconsistent MTRRdefType settings\n");

	pr_info("mtrr: probably your BIOS does not setup all CPUs.\n");
	pr_info("mtrr: corrected configuration.\n");
पूर्ण

/*
 * Doesn't attempt to pass an error out to MTRR users
 * because it's quite complicated in some हालs and probably not
 * worth it because the best error handling is to ignore it.
 */
व्योम mtrr_wrmsr(अचिन्हित msr, अचिन्हित a, अचिन्हित b)
अणु
	अगर (wrmsr_safe(msr, a, b) < 0) अणु
		pr_err("MTRR: CPU %u: Writing MSR %x to %x:%x failed\n",
			smp_processor_id(), msr, a, b);
	पूर्ण
पूर्ण

/**
 * set_fixed_range - checks & updates a fixed-range MTRR अगर it
 *		     dअगरfers from the value it should have
 * @msr: MSR address of the MTTR which should be checked and updated
 * @changed: poपूर्णांकer which indicates whether the MTRR needed to be changed
 * @msrwords: poपूर्णांकer to the MSR values which the MSR should have
 */
अटल व्योम set_fixed_range(पूर्णांक msr, bool *changed, अचिन्हित पूर्णांक *msrwords)
अणु
	अचिन्हित lo, hi;

	rdmsr(msr, lo, hi);

	अगर (lo != msrwords[0] || hi != msrwords[1]) अणु
		mtrr_wrmsr(msr, msrwords[0], msrwords[1]);
		*changed = true;
	पूर्ण
पूर्ण

/**
 * generic_get_मुक्त_region - Get a मुक्त MTRR.
 * @base: The starting (base) address of the region.
 * @size: The size (in bytes) of the region.
 * @replace_reg: mtrr index to be replaced; set to invalid value अगर none.
 *
 * Returns: The index of the region on success, अन्यथा negative on error.
 */
पूर्णांक
generic_get_मुक्त_region(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size, पूर्णांक replace_reg)
अणु
	अचिन्हित दीर्घ lbase, lsize;
	mtrr_type ltype;
	पूर्णांक i, max;

	max = num_var_ranges;
	अगर (replace_reg >= 0 && replace_reg < max)
		वापस replace_reg;

	क्रम (i = 0; i < max; ++i) अणु
		mtrr_अगर->get(i, &lbase, &lsize, &ltype);
		अगर (lsize == 0)
			वापस i;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल व्योम generic_get_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ *base,
			     अचिन्हित दीर्घ *size, mtrr_type *type)
अणु
	u32 mask_lo, mask_hi, base_lo, base_hi;
	अचिन्हित पूर्णांक hi;
	u64 पंचांगp, mask;

	/*
	 * get_mtrr करोesn't need to update mtrr_state, also it could be called
	 * from any cpu, so try to prपूर्णांक it out directly.
	 */
	get_cpu();

	rdmsr(MTRRphysMask_MSR(reg), mask_lo, mask_hi);

	अगर ((mask_lo & 0x800) == 0) अणु
		/*  Invalid (i.e. मुक्त) range */
		*base = 0;
		*size = 0;
		*type = 0;
		जाओ out_put_cpu;
	पूर्ण

	rdmsr(MTRRphysBase_MSR(reg), base_lo, base_hi);

	/* Work out the shअगरted address mask: */
	पंचांगp = (u64)mask_hi << (32 - PAGE_SHIFT) | mask_lo >> PAGE_SHIFT;
	mask = size_or_mask | पंचांगp;

	/* Expand पंचांगp with high bits to all 1s: */
	hi = fls64(पंचांगp);
	अगर (hi > 0) अणु
		पंचांगp |= ~((1ULL<<(hi - 1)) - 1);

		अगर (पंचांगp != mask) अणु
			pr_warn("mtrr: your BIOS has configured an incorrect mask, fixing it.\n");
			add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_STILL_OK);
			mask = पंचांगp;
		पूर्ण
	पूर्ण

	/*
	 * This works correctly अगर size is a घातer of two, i.e. a
	 * contiguous range:
	 */
	*size = -mask;
	*base = (u64)base_hi << (32 - PAGE_SHIFT) | base_lo >> PAGE_SHIFT;
	*type = base_lo & 0xff;

out_put_cpu:
	put_cpu();
पूर्ण

/**
 * set_fixed_ranges - checks & updates the fixed-range MTRRs अगर they
 *		      dअगरfer from the saved set
 * @frs: poपूर्णांकer to fixed-range MTRR values, saved by get_fixed_ranges()
 */
अटल पूर्णांक set_fixed_ranges(mtrr_type *frs)
अणु
	अचिन्हित दीर्घ दीर्घ *saved = (अचिन्हित दीर्घ दीर्घ *)frs;
	bool changed = false;
	पूर्णांक block = -1, range;

	k8_check_syscfg_dram_mod_en();

	जबतक (fixed_range_blocks[++block].ranges) अणु
		क्रम (range = 0; range < fixed_range_blocks[block].ranges; range++)
			set_fixed_range(fixed_range_blocks[block].base_msr + range,
					&changed, (अचिन्हित पूर्णांक *)saved++);
	पूर्ण

	वापस changed;
पूर्ण

/*
 * Set the MSR pair relating to a var range.
 * Returns true अगर changes are made.
 */
अटल bool set_mtrr_var_ranges(अचिन्हित पूर्णांक index, काष्ठा mtrr_var_range *vr)
अणु
	अचिन्हित पूर्णांक lo, hi;
	bool changed = false;

	rdmsr(MTRRphysBase_MSR(index), lo, hi);
	अगर ((vr->base_lo & 0xfffff0ffUL) != (lo & 0xfffff0ffUL)
	    || (vr->base_hi & (size_and_mask >> (32 - PAGE_SHIFT))) !=
		(hi & (size_and_mask >> (32 - PAGE_SHIFT)))) अणु

		mtrr_wrmsr(MTRRphysBase_MSR(index), vr->base_lo, vr->base_hi);
		changed = true;
	पूर्ण

	rdmsr(MTRRphysMask_MSR(index), lo, hi);

	अगर ((vr->mask_lo & 0xfffff800UL) != (lo & 0xfffff800UL)
	    || (vr->mask_hi & (size_and_mask >> (32 - PAGE_SHIFT))) !=
		(hi & (size_and_mask >> (32 - PAGE_SHIFT)))) अणु
		mtrr_wrmsr(MTRRphysMask_MSR(index), vr->mask_lo, vr->mask_hi);
		changed = true;
	पूर्ण
	वापस changed;
पूर्ण

अटल u32 deftype_lo, deftype_hi;

/**
 * set_mtrr_state - Set the MTRR state क्रम this CPU.
 *
 * NOTE: The CPU must alपढ़ोy be in a safe state क्रम MTRR changes.
 * RETURNS: 0 अगर no changes made, अन्यथा a mask indicating what was changed.
 */
अटल अचिन्हित दीर्घ set_mtrr_state(व्योम)
अणु
	अचिन्हित दीर्घ change_mask = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_var_ranges; i++) अणु
		अगर (set_mtrr_var_ranges(i, &mtrr_state.var_ranges[i]))
			change_mask |= MTRR_CHANGE_MASK_VARIABLE;
	पूर्ण

	अगर (mtrr_state.have_fixed && set_fixed_ranges(mtrr_state.fixed_ranges))
		change_mask |= MTRR_CHANGE_MASK_FIXED;

	/*
	 * Set_mtrr_restore restores the old value of MTRRdefType,
	 * so to set it we fiddle with the saved value:
	 */
	अगर ((deftype_lo & 0xff) != mtrr_state.def_type
	    || ((deftype_lo & 0xc00) >> 10) != mtrr_state.enabled) अणु

		deftype_lo = (deftype_lo & ~0xcff) | mtrr_state.def_type |
			     (mtrr_state.enabled << 10);
		change_mask |= MTRR_CHANGE_MASK_DEFTYPE;
	पूर्ण

	वापस change_mask;
पूर्ण


अटल अचिन्हित दीर्घ cr4;
अटल DEFINE_RAW_SPINLOCK(set_atomicity_lock);

/*
 * Since we are disabling the cache करोn't allow any पूर्णांकerrupts,
 * they would run extremely slow and would only increase the pain.
 *
 * The caller must ensure that local पूर्णांकerrupts are disabled and
 * are reenabled after post_set() has been called.
 */
अटल व्योम prepare_set(व्योम) __acquires(set_atomicity_lock)
अणु
	अचिन्हित दीर्घ cr0;

	/*
	 * Note that this is not ideal
	 * since the cache is only flushed/disabled क्रम this CPU जबतक the
	 * MTRRs are changed, but changing this requires more invasive
	 * changes to the way the kernel boots
	 */

	raw_spin_lock(&set_atomicity_lock);

	/* Enter the no-fill (CD=1, NW=0) cache mode and flush caches. */
	cr0 = पढ़ो_cr0() | X86_CR0_CD;
	ग_लिखो_cr0(cr0);

	/*
	 * Cache flushing is the most समय-consuming step when programming
	 * the MTRRs. Fortunately, as per the Intel Software Development
	 * Manual, we can skip it अगर the processor supports cache self-
	 * snooping.
	 */
	अगर (!अटल_cpu_has(X86_FEATURE_SELFSNOOP))
		wbinvd();

	/* Save value of CR4 and clear Page Global Enable (bit 7) */
	अगर (boot_cpu_has(X86_FEATURE_PGE)) अणु
		cr4 = __पढ़ो_cr4();
		__ग_लिखो_cr4(cr4 & ~X86_CR4_PGE);
	पूर्ण

	/* Flush all TLBs via a mov %cr3, %reg; mov %reg, %cr3 */
	count_vm_tlb_event(NR_TLB_LOCAL_FLUSH_ALL);
	flush_tlb_local();

	/* Save MTRR state */
	rdmsr(MSR_MTRRdefType, deftype_lo, deftype_hi);

	/* Disable MTRRs, and set the शेष type to uncached */
	mtrr_wrmsr(MSR_MTRRdefType, deftype_lo & ~0xcff, deftype_hi);

	/* Again, only flush caches अगर we have to. */
	अगर (!अटल_cpu_has(X86_FEATURE_SELFSNOOP))
		wbinvd();
पूर्ण

अटल व्योम post_set(व्योम) __releases(set_atomicity_lock)
अणु
	/* Flush TLBs (no need to flush caches - they are disabled) */
	count_vm_tlb_event(NR_TLB_LOCAL_FLUSH_ALL);
	flush_tlb_local();

	/* Intel (P6) standard MTRRs */
	mtrr_wrmsr(MSR_MTRRdefType, deftype_lo, deftype_hi);

	/* Enable caches */
	ग_लिखो_cr0(पढ़ो_cr0() & ~X86_CR0_CD);

	/* Restore value of CR4 */
	अगर (boot_cpu_has(X86_FEATURE_PGE))
		__ग_लिखो_cr4(cr4);
	raw_spin_unlock(&set_atomicity_lock);
पूर्ण

अटल व्योम generic_set_all(व्योम)
अणु
	अचिन्हित दीर्घ mask, count;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	prepare_set();

	/* Actually set the state */
	mask = set_mtrr_state();

	/* also set PAT */
	pat_init();

	post_set();
	local_irq_restore(flags);

	/* Use the atomic bitops to update the global mask */
	क्रम (count = 0; count < माप(mask) * 8; ++count) अणु
		अगर (mask & 0x01)
			set_bit(count, &smp_changes_mask);
		mask >>= 1;
	पूर्ण

पूर्ण

/**
 * generic_set_mtrr - set variable MTRR रेजिस्टर on the local CPU.
 *
 * @reg: The रेजिस्टर to set.
 * @base: The base address of the region.
 * @size: The size of the region. If this is 0 the region is disabled.
 * @type: The type of the region.
 *
 * Returns nothing.
 */
अटल व्योम generic_set_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base,
			     अचिन्हित दीर्घ size, mtrr_type type)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mtrr_var_range *vr;

	vr = &mtrr_state.var_ranges[reg];

	local_irq_save(flags);
	prepare_set();

	अगर (size == 0) अणु
		/*
		 * The invalid bit is kept in the mask, so we simply
		 * clear the relevant mask रेजिस्टर to disable a range.
		 */
		mtrr_wrmsr(MTRRphysMask_MSR(reg), 0, 0);
		स_रखो(vr, 0, माप(काष्ठा mtrr_var_range));
	पूर्ण अन्यथा अणु
		vr->base_lo = base << PAGE_SHIFT | type;
		vr->base_hi = (base & size_and_mask) >> (32 - PAGE_SHIFT);
		vr->mask_lo = -size << PAGE_SHIFT | 0x800;
		vr->mask_hi = (-size & size_and_mask) >> (32 - PAGE_SHIFT);

		mtrr_wrmsr(MTRRphysBase_MSR(reg), vr->base_lo, vr->base_hi);
		mtrr_wrmsr(MTRRphysMask_MSR(reg), vr->mask_lo, vr->mask_hi);
	पूर्ण

	post_set();
	local_irq_restore(flags);
पूर्ण

पूर्णांक generic_validate_add_page(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
			      अचिन्हित पूर्णांक type)
अणु
	अचिन्हित दीर्घ lbase, last;

	/*
	 * For Intel PPro stepping <= 7
	 * must be 4 MiB aligned and not touch 0x70000000 -> 0x7003FFFF
	 */
	अगर (is_cpu(INTEL) && boot_cpu_data.x86 == 6 &&
	    boot_cpu_data.x86_model == 1 &&
	    boot_cpu_data.x86_stepping <= 7) अणु
		अगर (base & ((1 << (22 - PAGE_SHIFT)) - 1)) अणु
			pr_warn("mtrr: base(0x%lx000) is not 4 MiB aligned\n", base);
			वापस -EINVAL;
		पूर्ण
		अगर (!(base + size < 0x70000 || base > 0x7003F) &&
		    (type == MTRR_TYPE_WRCOMB
		     || type == MTRR_TYPE_WRBACK)) अणु
			pr_warn("mtrr: writable mtrr between 0x70000000 and 0x7003FFFF may hang the CPU.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Check upper bits of base and last are equal and lower bits are 0
	 * क्रम base and 1 क्रम last
	 */
	last = base + size - 1;
	क्रम (lbase = base; !(lbase & 1) && (last & 1);
	     lbase = lbase >> 1, last = last >> 1)
		;
	अगर (lbase != last) अणु
		pr_warn("mtrr: base(0x%lx000) is not aligned on a size(0x%lx000) boundary\n", base, size);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक generic_have_wrcomb(व्योम)
अणु
	अचिन्हित दीर्घ config, dummy;
	rdmsr(MSR_MTRRcap, config, dummy);
	वापस config & (1 << 10);
पूर्ण

पूर्णांक positive_have_wrcomb(व्योम)
अणु
	वापस 1;
पूर्ण

/*
 * Generic काष्ठाure...
 */
स्थिर काष्ठा mtrr_ops generic_mtrr_ops = अणु
	.use_पूर्णांकel_अगर		= 1,
	.set_all		= generic_set_all,
	.get			= generic_get_mtrr,
	.get_मुक्त_region	= generic_get_मुक्त_region,
	.set			= generic_set_mtrr,
	.validate_add_page	= generic_validate_add_page,
	.have_wrcomb		= generic_have_wrcomb,
पूर्ण;
