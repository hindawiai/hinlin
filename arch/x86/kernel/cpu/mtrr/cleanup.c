<शैली गुरु>
/*
 * MTRR (Memory Type Range Register) cleanup
 *
 *  Copyright (C) 2009 Yinghai Lu
 *
 * This library is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License aदीर्घ with this library; अगर not, ग_लिखो to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kvm_para.h>
#समावेश <linux/range.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/msr.h>

#समावेश "mtrr.h"

काष्ठा var_mtrr_range_state अणु
	अचिन्हित दीर्घ	base_pfn;
	अचिन्हित दीर्घ	size_pfn;
	mtrr_type	type;
पूर्ण;

काष्ठा var_mtrr_state अणु
	अचिन्हित दीर्घ	range_startk;
	अचिन्हित दीर्घ	range_sizek;
	अचिन्हित दीर्घ	chunk_sizek;
	अचिन्हित दीर्घ	gran_sizek;
	अचिन्हित पूर्णांक	reg;
पूर्ण;

/* Should be related to MTRR_VAR_RANGES nums */
#घोषणा RANGE_NUM				256

अटल काष्ठा range __initdata		range[RANGE_NUM];
अटल पूर्णांक __initdata				nr_range;

अटल काष्ठा var_mtrr_range_state __initdata	range_state[RANGE_NUM];

अटल पूर्णांक __initdata debug_prपूर्णांक;
#घोषणा Dprपूर्णांकk(x...) करो अणु अगर (debug_prपूर्णांक) pr_debug(x); पूर्ण जबतक (0)

#घोषणा BIOS_BUG_MSG \
	"WARNING: BIOS bug: VAR MTRR %d contains strange UC entry under 1M, check with your system vendor!\n"

अटल पूर्णांक __init
x86_get_mtrr_mem_range(काष्ठा range *range, पूर्णांक nr_range,
		       अचिन्हित दीर्घ extra_हटाओ_base,
		       अचिन्हित दीर्घ extra_हटाओ_size)
अणु
	अचिन्हित दीर्घ base, size;
	mtrr_type type;
	पूर्णांक i;

	क्रम (i = 0; i < num_var_ranges; i++) अणु
		type = range_state[i].type;
		अगर (type != MTRR_TYPE_WRBACK)
			जारी;
		base = range_state[i].base_pfn;
		size = range_state[i].size_pfn;
		nr_range = add_range_with_merge(range, RANGE_NUM, nr_range,
						base, base + size);
	पूर्ण
	अगर (debug_prपूर्णांक) अणु
		pr_debug("After WB checking\n");
		क्रम (i = 0; i < nr_range; i++)
			pr_debug("MTRR MAP PFN: %016llx - %016llx\n",
				 range[i].start, range[i].end);
	पूर्ण

	/* Take out UC ranges: */
	क्रम (i = 0; i < num_var_ranges; i++) अणु
		type = range_state[i].type;
		अगर (type != MTRR_TYPE_UNCACHABLE &&
		    type != MTRR_TYPE_WRPROT)
			जारी;
		size = range_state[i].size_pfn;
		अगर (!size)
			जारी;
		base = range_state[i].base_pfn;
		अगर (base < (1<<(20-PAGE_SHIFT)) && mtrr_state.have_fixed &&
		    (mtrr_state.enabled & MTRR_STATE_MTRR_ENABLED) &&
		    (mtrr_state.enabled & MTRR_STATE_MTRR_FIXED_ENABLED)) अणु
			/* Var MTRR contains UC entry below 1M? Skip it: */
			pr_warn(BIOS_BUG_MSG, i);
			अगर (base + size <= (1<<(20-PAGE_SHIFT)))
				जारी;
			size -= (1<<(20-PAGE_SHIFT)) - base;
			base = 1<<(20-PAGE_SHIFT);
		पूर्ण
		subtract_range(range, RANGE_NUM, base, base + size);
	पूर्ण
	अगर (extra_हटाओ_size)
		subtract_range(range, RANGE_NUM, extra_हटाओ_base,
				 extra_हटाओ_base + extra_हटाओ_size);

	अगर  (debug_prपूर्णांक) अणु
		pr_debug("After UC checking\n");
		क्रम (i = 0; i < RANGE_NUM; i++) अणु
			अगर (!range[i].end)
				जारी;
			pr_debug("MTRR MAP PFN: %016llx - %016llx\n",
				 range[i].start, range[i].end);
		पूर्ण
	पूर्ण

	/* sort the ranges */
	nr_range = clean_sort_range(range, RANGE_NUM);
	अगर  (debug_prपूर्णांक) अणु
		pr_debug("After sorting\n");
		क्रम (i = 0; i < nr_range; i++)
			pr_debug("MTRR MAP PFN: %016llx - %016llx\n",
				 range[i].start, range[i].end);
	पूर्ण

	वापस nr_range;
पूर्ण

#अगर_घोषित CONFIG_MTRR_SANITIZER

अटल अचिन्हित दीर्घ __init sum_ranges(काष्ठा range *range, पूर्णांक nr_range)
अणु
	अचिन्हित दीर्घ sum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < nr_range; i++)
		sum += range[i].end - range[i].start;

	वापस sum;
पूर्ण

अटल पूर्णांक enable_mtrr_cleanup __initdata =
	CONFIG_MTRR_SANITIZER_ENABLE_DEFAULT;

अटल पूर्णांक __init disable_mtrr_cleanup_setup(अक्षर *str)
अणु
	enable_mtrr_cleanup = 0;
	वापस 0;
पूर्ण
early_param("disable_mtrr_cleanup", disable_mtrr_cleanup_setup);

अटल पूर्णांक __init enable_mtrr_cleanup_setup(अक्षर *str)
अणु
	enable_mtrr_cleanup = 1;
	वापस 0;
पूर्ण
early_param("enable_mtrr_cleanup", enable_mtrr_cleanup_setup);

अटल पूर्णांक __init mtrr_cleanup_debug_setup(अक्षर *str)
अणु
	debug_prपूर्णांक = 1;
	वापस 0;
पूर्ण
early_param("mtrr_cleanup_debug", mtrr_cleanup_debug_setup);

अटल व्योम __init
set_var_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ basek, अचिन्हित दीर्घ sizek,
	     अचिन्हित अक्षर type, अचिन्हित पूर्णांक address_bits)
अणु
	u32 base_lo, base_hi, mask_lo, mask_hi;
	u64 base, mask;

	अगर (!sizek) अणु
		fill_mtrr_var_range(reg, 0, 0, 0, 0);
		वापस;
	पूर्ण

	mask = (1ULL << address_bits) - 1;
	mask &= ~((((u64)sizek) << 10) - 1);

	base = ((u64)basek) << 10;

	base |= type;
	mask |= 0x800;

	base_lo = base & ((1ULL<<32) - 1);
	base_hi = base >> 32;

	mask_lo = mask & ((1ULL<<32) - 1);
	mask_hi = mask >> 32;

	fill_mtrr_var_range(reg, base_lo, base_hi, mask_lo, mask_hi);
पूर्ण

अटल व्योम __init
save_var_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ basek, अचिन्हित दीर्घ sizek,
	      अचिन्हित अक्षर type)
अणु
	range_state[reg].base_pfn = basek >> (PAGE_SHIFT - 10);
	range_state[reg].size_pfn = sizek >> (PAGE_SHIFT - 10);
	range_state[reg].type = type;
पूर्ण

अटल व्योम __init set_var_mtrr_all(अचिन्हित पूर्णांक address_bits)
अणु
	अचिन्हित दीर्घ basek, sizek;
	अचिन्हित अक्षर type;
	अचिन्हित पूर्णांक reg;

	क्रम (reg = 0; reg < num_var_ranges; reg++) अणु
		basek = range_state[reg].base_pfn << (PAGE_SHIFT - 10);
		sizek = range_state[reg].size_pfn << (PAGE_SHIFT - 10);
		type = range_state[reg].type;

		set_var_mtrr(reg, basek, sizek, type, address_bits);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ to_size_factor(अचिन्हित दीर्घ sizek, अक्षर *factorp)
अणु
	अचिन्हित दीर्घ base = sizek;
	अक्षर factor;

	अगर (base & ((1<<10) - 1)) अणु
		/* Not MB-aligned: */
		factor = 'K';
	पूर्ण अन्यथा अगर (base & ((1<<20) - 1)) अणु
		factor = 'M';
		base >>= 10;
	पूर्ण अन्यथा अणु
		factor = 'G';
		base >>= 20;
	पूर्ण

	*factorp = factor;

	वापस base;
पूर्ण

अटल अचिन्हित पूर्णांक __init
range_to_mtrr(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ range_startk,
	      अचिन्हित दीर्घ range_sizek, अचिन्हित अक्षर type)
अणु
	अगर (!range_sizek || (reg >= num_var_ranges))
		वापस reg;

	जबतक (range_sizek) अणु
		अचिन्हित दीर्घ max_align, align;
		अचिन्हित दीर्घ sizek;

		/* Compute the maximum size with which we can make a range: */
		अगर (range_startk)
			max_align = __ffs(range_startk);
		अन्यथा
			max_align = BITS_PER_LONG - 1;

		align = __fls(range_sizek);
		अगर (align > max_align)
			align = max_align;

		sizek = 1UL << align;
		अगर (debug_prपूर्णांक) अणु
			अक्षर start_factor = 'K', size_factor = 'K';
			अचिन्हित दीर्घ start_base, size_base;

			start_base = to_size_factor(range_startk, &start_factor);
			size_base = to_size_factor(sizek, &size_factor);

			Dprपूर्णांकk("Setting variable MTRR %d, "
				"base: %ld%cB, range: %ld%cB, type %s\n",
				reg, start_base, start_factor,
				size_base, size_factor,
				(type == MTRR_TYPE_UNCACHABLE) ? "UC" :
				   ((type == MTRR_TYPE_WRBACK) ? "WB" : "Other")
				);
		पूर्ण
		save_var_mtrr(reg++, range_startk, sizek, type);
		range_startk += sizek;
		range_sizek -= sizek;
		अगर (reg >= num_var_ranges)
			अवरोध;
	पूर्ण
	वापस reg;
पूर्ण

अटल अचिन्हित __init
range_to_mtrr_with_hole(काष्ठा var_mtrr_state *state, अचिन्हित दीर्घ basek,
			अचिन्हित दीर्घ sizek)
अणु
	अचिन्हित दीर्घ hole_basek, hole_sizek;
	अचिन्हित दीर्घ second_sizek;
	अचिन्हित दीर्घ range0_basek, range0_sizek;
	अचिन्हित दीर्घ range_basek, range_sizek;
	अचिन्हित दीर्घ chunk_sizek;
	अचिन्हित दीर्घ gran_sizek;

	hole_basek = 0;
	hole_sizek = 0;
	second_sizek = 0;
	chunk_sizek = state->chunk_sizek;
	gran_sizek = state->gran_sizek;

	/* Align with gran size, prevent small block used up MTRRs: */
	range_basek = ALIGN(state->range_startk, gran_sizek);
	अगर ((range_basek > basek) && basek)
		वापस second_sizek;

	state->range_sizek -= (range_basek - state->range_startk);
	range_sizek = ALIGN(state->range_sizek, gran_sizek);

	जबतक (range_sizek > state->range_sizek) अणु
		range_sizek -= gran_sizek;
		अगर (!range_sizek)
			वापस 0;
	पूर्ण
	state->range_sizek = range_sizek;

	/* Try to append some small hole: */
	range0_basek = state->range_startk;
	range0_sizek = ALIGN(state->range_sizek, chunk_sizek);

	/* No increase: */
	अगर (range0_sizek == state->range_sizek) अणु
		Dprपूर्णांकk("rangeX: %016lx - %016lx\n",
			range0_basek<<10,
			(range0_basek + state->range_sizek)<<10);
		state->reg = range_to_mtrr(state->reg, range0_basek,
				state->range_sizek, MTRR_TYPE_WRBACK);
		वापस 0;
	पूर्ण

	/* Only cut back when it is not the last: */
	अगर (sizek) अणु
		जबतक (range0_basek + range0_sizek > (basek + sizek)) अणु
			अगर (range0_sizek >= chunk_sizek)
				range0_sizek -= chunk_sizek;
			अन्यथा
				range0_sizek = 0;

			अगर (!range0_sizek)
				अवरोध;
		पूर्ण
	पूर्ण

second_try:
	range_basek = range0_basek + range0_sizek;

	/* One hole in the middle: */
	अगर (range_basek > basek && range_basek <= (basek + sizek))
		second_sizek = range_basek - basek;

	अगर (range0_sizek > state->range_sizek) अणु

		/* One hole in middle or at the end: */
		hole_sizek = range0_sizek - state->range_sizek - second_sizek;

		/* Hole size should be less than half of range0 size: */
		अगर (hole_sizek >= (range0_sizek >> 1) &&
		    range0_sizek >= chunk_sizek) अणु
			range0_sizek -= chunk_sizek;
			second_sizek = 0;
			hole_sizek = 0;

			जाओ second_try;
		पूर्ण
	पूर्ण

	अगर (range0_sizek) अणु
		Dprपूर्णांकk("range0: %016lx - %016lx\n",
			range0_basek<<10,
			(range0_basek + range0_sizek)<<10);
		state->reg = range_to_mtrr(state->reg, range0_basek,
				range0_sizek, MTRR_TYPE_WRBACK);
	पूर्ण

	अगर (range0_sizek < state->range_sizek) अणु
		/* Need to handle left over range: */
		range_sizek = state->range_sizek - range0_sizek;

		Dprपूर्णांकk("range: %016lx - %016lx\n",
			 range_basek<<10,
			 (range_basek + range_sizek)<<10);

		state->reg = range_to_mtrr(state->reg, range_basek,
				 range_sizek, MTRR_TYPE_WRBACK);
	पूर्ण

	अगर (hole_sizek) अणु
		hole_basek = range_basek - hole_sizek - second_sizek;
		Dprपूर्णांकk("hole: %016lx - %016lx\n",
			 hole_basek<<10,
			 (hole_basek + hole_sizek)<<10);
		state->reg = range_to_mtrr(state->reg, hole_basek,
				 hole_sizek, MTRR_TYPE_UNCACHABLE);
	पूर्ण

	वापस second_sizek;
पूर्ण

अटल व्योम __init
set_var_mtrr_range(काष्ठा var_mtrr_state *state, अचिन्हित दीर्घ base_pfn,
		   अचिन्हित दीर्घ size_pfn)
अणु
	अचिन्हित दीर्घ basek, sizek;
	अचिन्हित दीर्घ second_sizek = 0;

	अगर (state->reg >= num_var_ranges)
		वापस;

	basek = base_pfn << (PAGE_SHIFT - 10);
	sizek = size_pfn << (PAGE_SHIFT - 10);

	/* See अगर I can merge with the last range: */
	अगर ((basek <= 1024) ||
	    (state->range_startk + state->range_sizek == basek)) अणु
		अचिन्हित दीर्घ endk = basek + sizek;
		state->range_sizek = endk - state->range_startk;
		वापस;
	पूर्ण
	/* Write the range mtrrs: */
	अगर (state->range_sizek != 0)
		second_sizek = range_to_mtrr_with_hole(state, basek, sizek);

	/* Allocate an msr: */
	state->range_startk = basek + second_sizek;
	state->range_sizek  = sizek - second_sizek;
पूर्ण

/* Minimum size of mtrr block that can take hole: */
अटल u64 mtrr_chunk_size __initdata = (256ULL<<20);

अटल पूर्णांक __init parse_mtrr_chunk_size_opt(अक्षर *p)
अणु
	अगर (!p)
		वापस -EINVAL;
	mtrr_chunk_size = memparse(p, &p);
	वापस 0;
पूर्ण
early_param("mtrr_chunk_size", parse_mtrr_chunk_size_opt);

/* Granularity of mtrr of block: */
अटल u64 mtrr_gran_size __initdata;

अटल पूर्णांक __init parse_mtrr_gran_size_opt(अक्षर *p)
अणु
	अगर (!p)
		वापस -EINVAL;
	mtrr_gran_size = memparse(p, &p);
	वापस 0;
पूर्ण
early_param("mtrr_gran_size", parse_mtrr_gran_size_opt);

अटल अचिन्हित दीर्घ nr_mtrr_spare_reg __initdata =
				 CONFIG_MTRR_SANITIZER_SPARE_REG_NR_DEFAULT;

अटल पूर्णांक __init parse_mtrr_spare_reg(अक्षर *arg)
अणु
	अगर (arg)
		nr_mtrr_spare_reg = simple_म_से_अदीर्घ(arg, शून्य, 0);
	वापस 0;
पूर्ण
early_param("mtrr_spare_reg_nr", parse_mtrr_spare_reg);

अटल पूर्णांक __init
x86_setup_var_mtrrs(काष्ठा range *range, पूर्णांक nr_range,
		    u64 chunk_size, u64 gran_size)
अणु
	काष्ठा var_mtrr_state var_state;
	पूर्णांक num_reg;
	पूर्णांक i;

	var_state.range_startk	= 0;
	var_state.range_sizek	= 0;
	var_state.reg		= 0;
	var_state.chunk_sizek	= chunk_size >> 10;
	var_state.gran_sizek	= gran_size >> 10;

	स_रखो(range_state, 0, माप(range_state));

	/* Write the range: */
	क्रम (i = 0; i < nr_range; i++) अणु
		set_var_mtrr_range(&var_state, range[i].start,
				   range[i].end - range[i].start);
	पूर्ण

	/* Write the last range: */
	अगर (var_state.range_sizek != 0)
		range_to_mtrr_with_hole(&var_state, 0, 0);

	num_reg = var_state.reg;
	/* Clear out the extra MTRR's: */
	जबतक (var_state.reg < num_var_ranges) अणु
		save_var_mtrr(var_state.reg, 0, 0, 0);
		var_state.reg++;
	पूर्ण

	वापस num_reg;
पूर्ण

काष्ठा mtrr_cleanup_result अणु
	अचिन्हित दीर्घ	gran_sizek;
	अचिन्हित दीर्घ	chunk_sizek;
	अचिन्हित दीर्घ	lose_cover_sizek;
	अचिन्हित पूर्णांक	num_reg;
	पूर्णांक		bad;
पूर्ण;

/*
 * gran_size: 64K, 128K, 256K, 512K, 1M, 2M, ..., 2G
 * chunk size: gran_size, ..., 2G
 * so we need (1+16)*8
 */
#घोषणा NUM_RESULT	136
#घोषणा PSHIFT		(PAGE_SHIFT - 10)

अटल काष्ठा mtrr_cleanup_result __initdata result[NUM_RESULT];
अटल अचिन्हित दीर्घ __initdata min_loss_pfn[RANGE_NUM];

अटल व्योम __init prपूर्णांक_out_mtrr_range_state(व्योम)
अणु
	अक्षर start_factor = 'K', size_factor = 'K';
	अचिन्हित दीर्घ start_base, size_base;
	mtrr_type type;
	पूर्णांक i;

	क्रम (i = 0; i < num_var_ranges; i++) अणु

		size_base = range_state[i].size_pfn << (PAGE_SHIFT - 10);
		अगर (!size_base)
			जारी;

		size_base = to_size_factor(size_base, &size_factor);
		start_base = range_state[i].base_pfn << (PAGE_SHIFT - 10);
		start_base = to_size_factor(start_base, &start_factor);
		type = range_state[i].type;

		pr_debug("reg %d, base: %ld%cB, range: %ld%cB, type %s\n",
			i, start_base, start_factor,
			size_base, size_factor,
			(type == MTRR_TYPE_UNCACHABLE) ? "UC" :
			    ((type == MTRR_TYPE_WRPROT) ? "WP" :
			     ((type == MTRR_TYPE_WRBACK) ? "WB" : "Other"))
			);
	पूर्ण
पूर्ण

अटल पूर्णांक __init mtrr_need_cleanup(व्योम)
अणु
	पूर्णांक i;
	mtrr_type type;
	अचिन्हित दीर्घ size;
	/* Extra one क्रम all 0: */
	पूर्णांक num[MTRR_NUM_TYPES + 1];

	/* Check entries number: */
	स_रखो(num, 0, माप(num));
	क्रम (i = 0; i < num_var_ranges; i++) अणु
		type = range_state[i].type;
		size = range_state[i].size_pfn;
		अगर (type >= MTRR_NUM_TYPES)
			जारी;
		अगर (!size)
			type = MTRR_NUM_TYPES;
		num[type]++;
	पूर्ण

	/* Check अगर we got UC entries: */
	अगर (!num[MTRR_TYPE_UNCACHABLE])
		वापस 0;

	/* Check अगर we only had WB and UC */
	अगर (num[MTRR_TYPE_WRBACK] + num[MTRR_TYPE_UNCACHABLE] !=
	    num_var_ranges - num[MTRR_NUM_TYPES])
		वापस 0;

	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ __initdata range_sums;

अटल व्योम __init
mtrr_calc_range_state(u64 chunk_size, u64 gran_size,
		      अचिन्हित दीर्घ x_हटाओ_base,
		      अचिन्हित दीर्घ x_हटाओ_size, पूर्णांक i)
अणु
	/*
	 * range_new should really be an स्वतःmatic variable, but
	 * putting 4096 bytes on the stack is frowned upon, to put it
	 * mildly. It is safe to make it a अटल __initdata variable,
	 * since mtrr_calc_range_state is only called during init and
	 * there's no way it will call itself recursively.
	 */
	अटल काष्ठा range range_new[RANGE_NUM] __initdata;
	अचिन्हित दीर्घ range_sums_new;
	पूर्णांक nr_range_new;
	पूर्णांक num_reg;

	/* Convert ranges to var ranges state: */
	num_reg = x86_setup_var_mtrrs(range, nr_range, chunk_size, gran_size);

	/* We got new setting in range_state, check it: */
	स_रखो(range_new, 0, माप(range_new));
	nr_range_new = x86_get_mtrr_mem_range(range_new, 0,
				x_हटाओ_base, x_हटाओ_size);
	range_sums_new = sum_ranges(range_new, nr_range_new);

	result[i].chunk_sizek = chunk_size >> 10;
	result[i].gran_sizek = gran_size >> 10;
	result[i].num_reg = num_reg;

	अगर (range_sums < range_sums_new) अणु
		result[i].lose_cover_sizek = (range_sums_new - range_sums) << PSHIFT;
		result[i].bad = 1;
	पूर्ण अन्यथा अणु
		result[i].lose_cover_sizek = (range_sums - range_sums_new) << PSHIFT;
	पूर्ण

	/* Double check it: */
	अगर (!result[i].bad && !result[i].lose_cover_sizek) अणु
		अगर (nr_range_new != nr_range || स_भेद(range, range_new, माप(range)))
			result[i].bad = 1;
	पूर्ण

	अगर (!result[i].bad && (range_sums - range_sums_new < min_loss_pfn[num_reg]))
		min_loss_pfn[num_reg] = range_sums - range_sums_new;
पूर्ण

अटल व्योम __init mtrr_prपूर्णांक_out_one_result(पूर्णांक i)
अणु
	अचिन्हित दीर्घ gran_base, chunk_base, lose_base;
	अक्षर gran_factor, chunk_factor, lose_factor;

	gran_base = to_size_factor(result[i].gran_sizek, &gran_factor);
	chunk_base = to_size_factor(result[i].chunk_sizek, &chunk_factor);
	lose_base = to_size_factor(result[i].lose_cover_sizek, &lose_factor);

	pr_info("%sgran_size: %ld%c \tchunk_size: %ld%c \t",
		result[i].bad ? "*BAD*" : " ",
		gran_base, gran_factor, chunk_base, chunk_factor);
	pr_cont("num_reg: %d  \tlose cover RAM: %s%ld%c\n",
		result[i].num_reg, result[i].bad ? "-" : "",
		lose_base, lose_factor);
पूर्ण

अटल पूर्णांक __init mtrr_search_optimal_index(व्योम)
अणु
	पूर्णांक num_reg_good;
	पूर्णांक index_good;
	पूर्णांक i;

	अगर (nr_mtrr_spare_reg >= num_var_ranges)
		nr_mtrr_spare_reg = num_var_ranges - 1;

	num_reg_good = -1;
	क्रम (i = num_var_ranges - nr_mtrr_spare_reg; i > 0; i--) अणु
		अगर (!min_loss_pfn[i])
			num_reg_good = i;
	पूर्ण

	index_good = -1;
	अगर (num_reg_good != -1) अणु
		क्रम (i = 0; i < NUM_RESULT; i++) अणु
			अगर (!result[i].bad &&
			    result[i].num_reg == num_reg_good &&
			    !result[i].lose_cover_sizek) अणु
				index_good = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस index_good;
पूर्ण

पूर्णांक __init mtrr_cleanup(अचिन्हित address_bits)
अणु
	अचिन्हित दीर्घ x_हटाओ_base, x_हटाओ_size;
	अचिन्हित दीर्घ base, size, def, dummy;
	u64 chunk_size, gran_size;
	mtrr_type type;
	पूर्णांक index_good;
	पूर्णांक i;

	अगर (!is_cpu(INTEL) || enable_mtrr_cleanup < 1)
		वापस 0;

	rdmsr(MSR_MTRRdefType, def, dummy);
	def &= 0xff;
	अगर (def != MTRR_TYPE_UNCACHABLE)
		वापस 0;

	/* Get it and store it aside: */
	स_रखो(range_state, 0, माप(range_state));
	क्रम (i = 0; i < num_var_ranges; i++) अणु
		mtrr_अगर->get(i, &base, &size, &type);
		range_state[i].base_pfn = base;
		range_state[i].size_pfn = size;
		range_state[i].type = type;
	पूर्ण

	/* Check अगर we need handle it and can handle it: */
	अगर (!mtrr_need_cleanup())
		वापस 0;

	/* Prपूर्णांक original var MTRRs at first, क्रम debugging: */
	pr_debug("original variable MTRRs\n");
	prपूर्णांक_out_mtrr_range_state();

	स_रखो(range, 0, माप(range));
	x_हटाओ_size = 0;
	x_हटाओ_base = 1 << (32 - PAGE_SHIFT);
	अगर (mtrr_tom2)
		x_हटाओ_size = (mtrr_tom2 >> PAGE_SHIFT) - x_हटाओ_base;

	/*
	 * [0, 1M) should always be covered by var mtrr with WB
	 * and fixed mtrrs should take effect beक्रमe var mtrr क्रम it:
	 */
	nr_range = add_range_with_merge(range, RANGE_NUM, 0, 0,
					1ULL<<(20 - PAGE_SHIFT));
	/* add from var mtrr at last */
	nr_range = x86_get_mtrr_mem_range(range, nr_range,
					  x_हटाओ_base, x_हटाओ_size);

	range_sums = sum_ranges(range, nr_range);
	pr_info("total RAM covered: %ldM\n",
	       range_sums >> (20 - PAGE_SHIFT));

	अगर (mtrr_chunk_size && mtrr_gran_size) अणु
		i = 0;
		mtrr_calc_range_state(mtrr_chunk_size, mtrr_gran_size,
				      x_हटाओ_base, x_हटाओ_size, i);

		mtrr_prपूर्णांक_out_one_result(i);

		अगर (!result[i].bad) अणु
			set_var_mtrr_all(address_bits);
			pr_debug("New variable MTRRs\n");
			prपूर्णांक_out_mtrr_range_state();
			वापस 1;
		पूर्ण
		pr_info("invalid mtrr_gran_size or mtrr_chunk_size, will find optimal one\n");
	पूर्ण

	i = 0;
	स_रखो(min_loss_pfn, 0xff, माप(min_loss_pfn));
	स_रखो(result, 0, माप(result));
	क्रम (gran_size = (1ULL<<16); gran_size < (1ULL<<32); gran_size <<= 1) अणु

		क्रम (chunk_size = gran_size; chunk_size < (1ULL<<32);
		     chunk_size <<= 1) अणु

			अगर (i >= NUM_RESULT)
				जारी;

			mtrr_calc_range_state(chunk_size, gran_size,
				      x_हटाओ_base, x_हटाओ_size, i);
			अगर (debug_prपूर्णांक) अणु
				mtrr_prपूर्णांक_out_one_result(i);
				pr_info("\n");
			पूर्ण

			i++;
		पूर्ण
	पूर्ण

	/* Try to find the optimal index: */
	index_good = mtrr_search_optimal_index();

	अगर (index_good != -1) अणु
		pr_info("Found optimal setting for mtrr clean up\n");
		i = index_good;
		mtrr_prपूर्णांक_out_one_result(i);

		/* Convert ranges to var ranges state: */
		chunk_size = result[i].chunk_sizek;
		chunk_size <<= 10;
		gran_size = result[i].gran_sizek;
		gran_size <<= 10;
		x86_setup_var_mtrrs(range, nr_range, chunk_size, gran_size);
		set_var_mtrr_all(address_bits);
		pr_debug("New variable MTRRs\n");
		prपूर्णांक_out_mtrr_range_state();
		वापस 1;
	पूर्ण अन्यथा अणु
		/* prपूर्णांक out all */
		क्रम (i = 0; i < NUM_RESULT; i++)
			mtrr_prपूर्णांक_out_one_result(i);
	पूर्ण

	pr_info("mtrr_cleanup: can not find optimal value\n");
	pr_info("please specify mtrr_gran_size/mtrr_chunk_size\n");

	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक __init mtrr_cleanup(अचिन्हित address_bits)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक disable_mtrr_trim;

अटल पूर्णांक __init disable_mtrr_trim_setup(अक्षर *str)
अणु
	disable_mtrr_trim = 1;
	वापस 0;
पूर्ण
early_param("disable_mtrr_trim", disable_mtrr_trim_setup);

/*
 * Newer AMD K8s and later CPUs have a special magic MSR way to क्रमce WB
 * क्रम memory >4GB. Check क्रम that here.
 * Note this won't check if the MTRRs < 4GB where the magic bit doesn't
 * apply to are wrong, but so far we करोn't know of any such हाल in the wild.
 */
#घोषणा Tom2Enabled		(1U << 21)
#घोषणा Tom2ForceMemTypeWB	(1U << 22)

पूर्णांक __init amd_special_शेष_mtrr(व्योम)
अणु
	u32 l, h;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_HYGON)
		वापस 0;
	अगर (boot_cpu_data.x86 < 0xf)
		वापस 0;
	/* In हाल some hypervisor करोesn't pass SYSCFG through: */
	अगर (rdmsr_safe(MSR_AMD64_SYSCFG, &l, &h) < 0)
		वापस 0;
	/*
	 * Memory between 4GB and top of mem is क्रमced WB by this magic bit.
	 * Reserved beक्रमe K8RevF, but should be zero there.
	 */
	अगर ((l & (Tom2Enabled | Tom2ForceMemTypeWB)) ==
		 (Tom2Enabled | Tom2ForceMemTypeWB))
		वापस 1;
	वापस 0;
पूर्ण

अटल u64 __init
real_trim_memory(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ limit_pfn)
अणु
	u64 trim_start, trim_size;

	trim_start = start_pfn;
	trim_start <<= PAGE_SHIFT;

	trim_size = limit_pfn;
	trim_size <<= PAGE_SHIFT;
	trim_size -= trim_start;

	वापस e820__range_update(trim_start, trim_size, E820_TYPE_RAM, E820_TYPE_RESERVED);
पूर्ण

/**
 * mtrr_trim_uncached_memory - trim RAM not covered by MTRRs
 * @end_pfn: ending page frame number
 *
 * Some buggy BIOSes करोn't setup the MTRRs properly क्रम प्रणालीs with certain
 * memory configurations.  This routine checks that the highest MTRR matches
 * the end of memory, to make sure the MTRRs having a ग_लिखो back type cover
 * all of the memory the kernel is पूर्णांकending to use.  If not, it'll trim any
 * memory off the end by adjusting end_pfn, removing it from the kernel's
 * allocation pools, warning the user with an obnoxious message.
 */
पूर्णांक __init mtrr_trim_uncached_memory(अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ i, base, size, highest_pfn = 0, def, dummy;
	mtrr_type type;
	u64 total_trim_size;
	/* extra one क्रम all 0 */
	पूर्णांक num[MTRR_NUM_TYPES + 1];

	/*
	 * Make sure we only trim uncachable memory on machines that
	 * support the Intel MTRR architecture:
	 */
	अगर (!is_cpu(INTEL) || disable_mtrr_trim)
		वापस 0;

	rdmsr(MSR_MTRRdefType, def, dummy);
	def &= 0xff;
	अगर (def != MTRR_TYPE_UNCACHABLE)
		वापस 0;

	/* Get it and store it aside: */
	स_रखो(range_state, 0, माप(range_state));
	क्रम (i = 0; i < num_var_ranges; i++) अणु
		mtrr_अगर->get(i, &base, &size, &type);
		range_state[i].base_pfn = base;
		range_state[i].size_pfn = size;
		range_state[i].type = type;
	पूर्ण

	/* Find highest cached pfn: */
	क्रम (i = 0; i < num_var_ranges; i++) अणु
		type = range_state[i].type;
		अगर (type != MTRR_TYPE_WRBACK)
			जारी;
		base = range_state[i].base_pfn;
		size = range_state[i].size_pfn;
		अगर (highest_pfn < base + size)
			highest_pfn = base + size;
	पूर्ण

	/* kvm/qemu करोesn't have mtrr set right, don't trim them all: */
	अगर (!highest_pfn) अणु
		pr_info("CPU MTRRs all blank - virtualized system.\n");
		वापस 0;
	पूर्ण

	/* Check entries number: */
	स_रखो(num, 0, माप(num));
	क्रम (i = 0; i < num_var_ranges; i++) अणु
		type = range_state[i].type;
		अगर (type >= MTRR_NUM_TYPES)
			जारी;
		size = range_state[i].size_pfn;
		अगर (!size)
			type = MTRR_NUM_TYPES;
		num[type]++;
	पूर्ण

	/* No entry क्रम WB? */
	अगर (!num[MTRR_TYPE_WRBACK])
		वापस 0;

	/* Check अगर we only had WB and UC: */
	अगर (num[MTRR_TYPE_WRBACK] + num[MTRR_TYPE_UNCACHABLE] !=
		num_var_ranges - num[MTRR_NUM_TYPES])
		वापस 0;

	स_रखो(range, 0, माप(range));
	nr_range = 0;
	अगर (mtrr_tom2) अणु
		range[nr_range].start = (1ULL<<(32 - PAGE_SHIFT));
		range[nr_range].end = mtrr_tom2 >> PAGE_SHIFT;
		अगर (highest_pfn < range[nr_range].end)
			highest_pfn = range[nr_range].end;
		nr_range++;
	पूर्ण
	nr_range = x86_get_mtrr_mem_range(range, nr_range, 0, 0);

	/* Check the head: */
	total_trim_size = 0;
	अगर (range[0].start)
		total_trim_size += real_trim_memory(0, range[0].start);

	/* Check the holes: */
	क्रम (i = 0; i < nr_range - 1; i++) अणु
		अगर (range[i].end < range[i+1].start)
			total_trim_size += real_trim_memory(range[i].end,
							    range[i+1].start);
	पूर्ण

	/* Check the top: */
	i = nr_range - 1;
	अगर (range[i].end < end_pfn)
		total_trim_size += real_trim_memory(range[i].end,
							 end_pfn);

	अगर (total_trim_size) अणु
		pr_warn("WARNING: BIOS bug: CPU MTRRs don't cover all of memory, losing %lluMB of RAM.\n",
			total_trim_size >> 20);

		अगर (!changed_by_mtrr_cleanup)
			WARN_ON(1);

		pr_info("update e820 for mtrr\n");
		e820__update_table_prपूर्णांक();

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
