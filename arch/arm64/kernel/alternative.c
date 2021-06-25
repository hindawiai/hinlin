<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * alternative runसमय patching
 * inspired by the x86 version
 *
 * Copyright (C) 2014 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) "alternatives: " fmt

#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/sections.h>
#समावेश <linux/stop_machine.h>

#घोषणा __ALT_PTR(a, f)		((व्योम *)&(a)->f + (a)->f)
#घोषणा ALT_ORIG_PTR(a)		__ALT_PTR(a, orig_offset)
#घोषणा ALT_REPL_PTR(a)		__ALT_PTR(a, alt_offset)

/* Volatile, as we may be patching the guts of READ_ONCE() */
अटल अस्थिर पूर्णांक all_alternatives_applied;

अटल DECLARE_BITMAP(applied_alternatives, ARM64_NCAPS);

काष्ठा alt_region अणु
	काष्ठा alt_instr *begin;
	काष्ठा alt_instr *end;
पूर्ण;

bool alternative_is_applied(u16 cpufeature)
अणु
	अगर (WARN_ON(cpufeature >= ARM64_NCAPS))
		वापस false;

	वापस test_bit(cpufeature, applied_alternatives);
पूर्ण

/*
 * Check अगर the target PC is within an alternative block.
 */
अटल bool branch_insn_requires_update(काष्ठा alt_instr *alt, अचिन्हित दीर्घ pc)
अणु
	अचिन्हित दीर्घ replptr = (अचिन्हित दीर्घ)ALT_REPL_PTR(alt);
	वापस !(pc >= replptr && pc <= (replptr + alt->alt_len));
पूर्ण

#घोषणा align_करोwn(x, a)	((अचिन्हित दीर्घ)(x) & ~(((अचिन्हित दीर्घ)(a)) - 1))

अटल u32 get_alt_insn(काष्ठा alt_instr *alt, __le32 *insnptr, __le32 *altinsnptr)
अणु
	u32 insn;

	insn = le32_to_cpu(*altinsnptr);

	अगर (aarch64_insn_is_branch_imm(insn)) अणु
		s32 offset = aarch64_get_branch_offset(insn);
		अचिन्हित दीर्घ target;

		target = (अचिन्हित दीर्घ)altinsnptr + offset;

		/*
		 * If we're branching inside the alternate sequence,
		 * करो not reग_लिखो the inकाष्ठाion, as it is alपढ़ोy
		 * correct. Otherwise, generate the new inकाष्ठाion.
		 */
		अगर (branch_insn_requires_update(alt, target)) अणु
			offset = target - (अचिन्हित दीर्घ)insnptr;
			insn = aarch64_set_branch_offset(insn, offset);
		पूर्ण
	पूर्ण अन्यथा अगर (aarch64_insn_is_adrp(insn)) अणु
		s32 orig_offset, new_offset;
		अचिन्हित दीर्घ target;

		/*
		 * If we're replacing an adrp inकाष्ठाion, which uses PC-relative
		 * immediate addressing, adjust the offset to reflect the new
		 * PC. adrp operates on 4K aligned addresses.
		 */
		orig_offset  = aarch64_insn_adrp_get_offset(insn);
		target = align_करोwn(altinsnptr, SZ_4K) + orig_offset;
		new_offset = target - align_करोwn(insnptr, SZ_4K);
		insn = aarch64_insn_adrp_set_offset(insn, new_offset);
	पूर्ण अन्यथा अगर (aarch64_insn_uses_literal(insn)) अणु
		/*
		 * Disallow patching unhandled inकाष्ठाions using PC relative
		 * literal addresses
		 */
		BUG();
	पूर्ण

	वापस insn;
पूर्ण

अटल व्योम patch_alternative(काष्ठा alt_instr *alt,
			      __le32 *origptr, __le32 *updptr, पूर्णांक nr_inst)
अणु
	__le32 *replptr;
	पूर्णांक i;

	replptr = ALT_REPL_PTR(alt);
	क्रम (i = 0; i < nr_inst; i++) अणु
		u32 insn;

		insn = get_alt_insn(alt, origptr + i, replptr + i);
		updptr[i] = cpu_to_le32(insn);
	पूर्ण
पूर्ण

/*
 * We provide our own, निजी D-cache cleaning function so that we करोn't
 * accidentally call पूर्णांकo the cache.S code, which is patched by us at
 * runसमय.
 */
अटल व्योम clean_dcache_range_nopatch(u64 start, u64 end)
अणु
	u64 cur, d_size, ctr_el0;

	ctr_el0 = पढ़ो_sanitised_ftr_reg(SYS_CTR_EL0);
	d_size = 4 << cpuid_feature_extract_अचिन्हित_field(ctr_el0,
							   CTR_DMINLINE_SHIFT);
	cur = start & ~(d_size - 1);
	करो अणु
		/*
		 * We must clean+invalidate to the PoC in order to aव्योम
		 * Cortex-A53 errata 826319, 827319, 824069 and 819472
		 * (this corresponds to ARM64_WORKAROUND_CLEAN_CACHE)
		 */
		यंत्र अस्थिर("dc civac, %0" : : "r" (cur) : "memory");
	पूर्ण जबतक (cur += d_size, cur < end);
पूर्ण

अटल व्योम __nocfi __apply_alternatives(काष्ठा alt_region *region, bool is_module,
				 अचिन्हित दीर्घ *feature_mask)
अणु
	काष्ठा alt_instr *alt;
	__le32 *origptr, *updptr;
	alternative_cb_t alt_cb;

	क्रम (alt = region->begin; alt < region->end; alt++) अणु
		पूर्णांक nr_inst;

		अगर (!test_bit(alt->cpufeature, feature_mask))
			जारी;

		/* Use ARM64_CB_PATCH as an unconditional patch */
		अगर (alt->cpufeature < ARM64_CB_PATCH &&
		    !cpus_have_cap(alt->cpufeature))
			जारी;

		अगर (alt->cpufeature == ARM64_CB_PATCH)
			BUG_ON(alt->alt_len != 0);
		अन्यथा
			BUG_ON(alt->alt_len != alt->orig_len);

		pr_info_once("patching kernel code\n");

		origptr = ALT_ORIG_PTR(alt);
		updptr = is_module ? origptr : lm_alias(origptr);
		nr_inst = alt->orig_len / AARCH64_INSN_SIZE;

		अगर (alt->cpufeature < ARM64_CB_PATCH)
			alt_cb = patch_alternative;
		अन्यथा
			alt_cb  = ALT_REPL_PTR(alt);

		alt_cb(alt, origptr, updptr, nr_inst);

		अगर (!is_module) अणु
			clean_dcache_range_nopatch((u64)origptr,
						   (u64)(origptr + nr_inst));
		पूर्ण
	पूर्ण

	/*
	 * The core module code takes care of cache मुख्यtenance in
	 * flush_module_icache().
	 */
	अगर (!is_module) अणु
		dsb(ish);
		__flush_icache_all();
		isb();

		/* Ignore ARM64_CB bit from feature mask */
		biपंचांगap_or(applied_alternatives, applied_alternatives,
			  feature_mask, ARM64_NCAPS);
		biपंचांगap_and(applied_alternatives, applied_alternatives,
			   cpu_hwcaps, ARM64_NCAPS);
	पूर्ण
पूर्ण

/*
 * We might be patching the stop_machine state machine, so implement a
 * really simple polling protocol here.
 */
अटल पूर्णांक __apply_alternatives_multi_stop(व्योम *unused)
अणु
	काष्ठा alt_region region = अणु
		.begin	= (काष्ठा alt_instr *)__alt_inकाष्ठाions,
		.end	= (काष्ठा alt_instr *)__alt_inकाष्ठाions_end,
	पूर्ण;

	/* We always have a CPU 0 at this poपूर्णांक (__init) */
	अगर (smp_processor_id()) अणु
		जबतक (!all_alternatives_applied)
			cpu_relax();
		isb();
	पूर्ण अन्यथा अणु
		DECLARE_BITMAP(reमुख्यing_capabilities, ARM64_NPATCHABLE);

		biपंचांगap_complement(reमुख्यing_capabilities, boot_capabilities,
				  ARM64_NPATCHABLE);

		BUG_ON(all_alternatives_applied);
		__apply_alternatives(&region, false, reमुख्यing_capabilities);
		/* Barriers provided by the cache flushing */
		all_alternatives_applied = 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __init apply_alternatives_all(व्योम)
अणु
	/* better not try code patching on a live SMP प्रणाली */
	stop_machine(__apply_alternatives_multi_stop, शून्य, cpu_online_mask);
पूर्ण

/*
 * This is called very early in the boot process (directly after we run
 * a feature detect on the boot CPU). No need to worry about other CPUs
 * here.
 */
व्योम __init apply_boot_alternatives(व्योम)
अणु
	काष्ठा alt_region region = अणु
		.begin	= (काष्ठा alt_instr *)__alt_inकाष्ठाions,
		.end	= (काष्ठा alt_instr *)__alt_inकाष्ठाions_end,
	पूर्ण;

	/* If called on non-boot cpu things could go wrong */
	WARN_ON(smp_processor_id() != 0);

	__apply_alternatives(&region, false, &boot_capabilities[0]);
पूर्ण

#अगर_घोषित CONFIG_MODULES
व्योम apply_alternatives_module(व्योम *start, माप_प्रकार length)
अणु
	काष्ठा alt_region region = अणु
		.begin	= start,
		.end	= start + length,
	पूर्ण;
	DECLARE_BITMAP(all_capabilities, ARM64_NPATCHABLE);

	biपंचांगap_fill(all_capabilities, ARM64_NPATCHABLE);

	__apply_alternatives(&region, true, &all_capabilities[0]);
पूर्ण
#पूर्ण_अगर
