<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Alternative live-patching क्रम parisc.
 *    Copyright (C) 2018 Helge Deller <deller@gmx.de>
 *
 */

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/alternative.h>

#समावेश <linux/module.h>

अटल पूर्णांक no_alternatives;
अटल पूर्णांक __init setup_no_alternatives(अक्षर *str)
अणु
	no_alternatives = 1;
	वापस 1;
पूर्ण
__setup("no-alternatives", setup_no_alternatives);

व्योम __init_or_module apply_alternatives(काष्ठा alt_instr *start,
		 काष्ठा alt_instr *end, स्थिर अक्षर *module_name)
अणु
	काष्ठा alt_instr *entry;
	पूर्णांक index = 0, applied = 0;
	पूर्णांक num_cpus = num_online_cpus();
	u32 cond_check;

	cond_check = ALT_COND_ALWAYS |
		((num_cpus == 1) ? ALT_COND_NO_SMP : 0) |
		((cache_info.dc_size == 0) ? ALT_COND_NO_DCACHE : 0) |
		((cache_info.ic_size == 0) ? ALT_COND_NO_ICACHE : 0) |
		(running_on_qemu ? ALT_COND_RUN_ON_QEMU : 0) |
		((split_tlb == 0) ? ALT_COND_NO_SPLIT_TLB : 0) |
		/*
		 * If the PDC_MODEL capabilities has Non-coherent IO-Pसूची bit
		 * set (bit #61, big endian), we have to flush and sync every
		 * समय IO-Pसूची is changed in Ike/Astro.
		 */
		(((boot_cpu_data.cpu_type > pcxw_) &&
		  ((boot_cpu_data.pdc.capabilities & PDC_MODEL_IOPसूची_FDC) == 0))
			? ALT_COND_NO_IOC_FDC : 0);

	क्रम (entry = start; entry < end; entry++, index++) अणु

		u32 *from, cond, replacement;
		s32 len;

		from = (u32 *)((uदीर्घ)&entry->orig_offset + entry->orig_offset);
		len = entry->len;
		cond = entry->cond;
		replacement = entry->replacement;

		WARN_ON(!cond);

		अगर ((cond & ALT_COND_ALWAYS) == 0 && no_alternatives)
			जारी;

		pr_debug("Check %d: Cond 0x%x, Replace %02d instructions @ 0x%px with 0x%08x\n",
			index, cond, len, from, replacement);

		/* Bounce out अगर none of the conditions are true. */
		अगर ((cond & cond_check) == 0)
			जारी;

		/* Want to replace pdtlb by a pdtlb,l inकाष्ठाion? */
		अगर (replacement == INSN_PxTLB) अणु
			replacement = *from;
			अगर (boot_cpu_data.cpu_type >= pcxu) /* >= pa2.0 ? */
				replacement |= (1 << 10); /* set el bit */
		पूर्ण

		/*
		 * Replace inकाष्ठाion with NOPs?
		 * For दीर्घ distance insert a branch inकाष्ठाion instead.
		 */
		अगर (replacement == INSN_NOP && len > 1)
			replacement = 0xe8000002 + (len-2)*8; /* "b,n .+8" */

		pr_debug("ALTERNATIVE %3d: Cond %2x, Replace %2d instructions to 0x%08x @ 0x%px (%pS)\n",
			index, cond, len, replacement, from, from);

		अगर (len < 0) अणु
			/* Replace multiple inकाष्ठाion by new code */
			u32 *source;
			len = -len;
			source = (u32 *)((uदीर्घ)&entry->replacement + entry->replacement);
			स_नकल(from, source, 4 * len);
		पूर्ण अन्यथा अणु
			/* Replace by one inकाष्ठाion */
			*from = replacement;
		पूर्ण
		applied++;
	पूर्ण

	pr_info("%s%salternatives: applied %d out of %d patches\n",
		module_name ? : "", module_name ? " " : "",
		applied, index);
पूर्ण


व्योम __init apply_alternatives_all(व्योम)
अणु
	set_kernel_text_rw(1);

	apply_alternatives((काष्ठा alt_instr *) &__alt_inकाष्ठाions,
		(काष्ठा alt_instr *) &__alt_inकाष्ठाions_end, शून्य);

	set_kernel_text_rw(0);
पूर्ण
