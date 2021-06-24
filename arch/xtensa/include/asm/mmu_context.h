<शैली गुरु>
/*
 * Switch an MMU context.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_MMU_CONTEXT_H
#घोषणा _XTENSA_MMU_CONTEXT_H

#अगर_अघोषित CONFIG_MMU
#समावेश <यंत्र/nommu_context.h>
#अन्यथा

#समावेश <linux/stringअगरy.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/vectors.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र-generic/mm_hooks.h>
#समावेश <यंत्र-generic/percpu.h>

#अगर (XCHAL_HAVE_TLBS != 1)
# error "Linux must have an MMU!"
#पूर्ण_अगर

DECLARE_PER_CPU(अचिन्हित दीर्घ, asid_cache);
#घोषणा cpu_asid_cache(cpu) per_cpu(asid_cache, cpu)

/*
 * NO_CONTEXT is the invalid ASID value that we करोn't ever assign to
 * any user or kernel context.  We use the reserved values in the
 * ASID_INSERT macro below.
 *
 * 0 invalid
 * 1 kernel
 * 2 reserved
 * 3 reserved
 * 4...255 available
 */

#घोषणा NO_CONTEXT	0
#घोषणा ASID_USER_FIRST	4
#घोषणा ASID_MASK	((1 << XCHAL_MMU_ASID_BITS) - 1)
#घोषणा ASID_INSERT(x)	(0x03020001 | (((x) & ASID_MASK) << 8))

व्योम init_mmu(व्योम);
व्योम init_kio(व्योम);

अटल अंतरभूत व्योम set_rasid_रेजिस्टर (अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__ (" wsr %0, rasid\n\t"
			      " isync\n" : : "a" (val));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_rasid_रेजिस्टर (व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__ (" rsr %0, rasid\n\t" : "=a" (पंचांगp));
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम get_new_mmu_context(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ asid = cpu_asid_cache(cpu);
	अगर ((++asid & ASID_MASK) == 0) अणु
		/*
		 * Start new asid cycle; जारी counting with next
		 * incarnation bits; skipping over 0, 1, 2, 3.
		 */
		local_flush_tlb_all();
		asid += ASID_USER_FIRST;
	पूर्ण
	cpu_asid_cache(cpu) = asid;
	mm->context.asid[cpu] = asid;
	mm->context.cpu = cpu;
पूर्ण

अटल अंतरभूत व्योम get_mmu_context(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Check अगर our ASID is of an older version and thus invalid.
	 */

	अगर (mm) अणु
		अचिन्हित दीर्घ asid = mm->context.asid[cpu];

		अगर (asid == NO_CONTEXT ||
				((asid ^ cpu_asid_cache(cpu)) & ~ASID_MASK))
			get_new_mmu_context(mm, cpu);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम activate_context(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	get_mmu_context(mm, cpu);
	set_rasid_रेजिस्टर(ASID_INSERT(mm->context.asid[cpu]));
	invalidate_page_directory();
पूर्ण

/*
 * Initialize the context related info क्रम a new mm_काष्ठा
 * instance.  Valid cpu values are 0..(NR_CPUS-1), so initializing
 * to -1 says the process has never run on any core.
 */

#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
		काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक cpu;
	क्रम_each_possible_cpu(cpu) अणु
		mm->context.asid[cpu] = NO_CONTEXT;
	पूर्ण
	mm->context.cpu = -1;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक migrated = next->context.cpu != cpu;
	/* Flush the icache अगर we migrated to a new core. */
	अगर (migrated) अणु
		__invalidate_icache_all();
		next->context.cpu = cpu;
	पूर्ण
	अगर (migrated || prev != next)
		activate_context(next, cpu);
पूर्ण

/*
 * Destroy context related info क्रम an mm_काष्ठा that is about
 * to be put to rest.
 */
#घोषणा destroy_context destroy_context
अटल अंतरभूत व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	invalidate_page_directory();
पूर्ण


#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर /* _XTENSA_MMU_CONTEXT_H */
