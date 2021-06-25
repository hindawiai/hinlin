<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/proc-fns.h
 *
 *  Copyright (C) 1997-1999 Russell King
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 */
#अगर_अघोषित __ASM_PROCFNS_H
#घोषणा __ASM_PROCFNS_H

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/glue-proc.h>
#समावेश <यंत्र/page.h>

#अगर_अघोषित __ASSEMBLY__

काष्ठा mm_काष्ठा;

/*
 * Don't change this काष्ठाure - ASM code relies on it.
 */
काष्ठा processor अणु
	/* MISC
	 * get data पात address/flags
	 */
	व्योम (*_data_पात)(अचिन्हित दीर्घ pc);
	/*
	 * Retrieve prefetch fault address
	 */
	अचिन्हित दीर्घ (*_prefetch_पात)(अचिन्हित दीर्घ lr);
	/*
	 * Set up any processor specअगरics
	 */
	व्योम (*_proc_init)(व्योम);
	/*
	 * Check क्रम processor bugs
	 */
	व्योम (*check_bugs)(व्योम);
	/*
	 * Disable any processor specअगरics
	 */
	व्योम (*_proc_fin)(व्योम);
	/*
	 * Special stuff क्रम a reset
	 */
	व्योम (*reset)(अचिन्हित दीर्घ addr, bool hvc) __attribute__((noवापस));
	/*
	 * Idle the processor
	 */
	पूर्णांक (*_करो_idle)(व्योम);
	/*
	 * Processor architecture specअगरic
	 */
	/*
	 * clean a भव address range from the
	 * D-cache without flushing the cache.
	 */
	व्योम (*dcache_clean_area)(व्योम *addr, पूर्णांक size);

	/*
	 * Set the page table
	 */
	व्योम (*चयन_mm)(phys_addr_t pgd_phys, काष्ठा mm_काष्ठा *mm);
	/*
	 * Set a possibly extended PTE.  Non-extended PTEs should
	 * ignore 'ext'.
	 */
#अगर_घोषित CONFIG_ARM_LPAE
	व्योम (*set_pte_ext)(pte_t *ptep, pte_t pte);
#अन्यथा
	व्योम (*set_pte_ext)(pte_t *ptep, pte_t pte, अचिन्हित पूर्णांक ext);
#पूर्ण_अगर

	/* Suspend/resume */
	अचिन्हित पूर्णांक suspend_size;
	व्योम (*करो_suspend)(व्योम *);
	व्योम (*करो_resume)(व्योम *);
पूर्ण;

#अगर_अघोषित MULTI_CPU
अटल अंतरभूत व्योम init_proc_vtable(स्थिर काष्ठा processor *p)
अणु
पूर्ण

बाह्य व्योम cpu_proc_init(व्योम);
बाह्य व्योम cpu_proc_fin(व्योम);
बाह्य पूर्णांक cpu_करो_idle(व्योम);
बाह्य व्योम cpu_dcache_clean_area(व्योम *, पूर्णांक);
बाह्य व्योम cpu_करो_चयन_mm(phys_addr_t pgd_phys, काष्ठा mm_काष्ठा *mm);
#अगर_घोषित CONFIG_ARM_LPAE
बाह्य व्योम cpu_set_pte_ext(pte_t *ptep, pte_t pte);
#अन्यथा
बाह्य व्योम cpu_set_pte_ext(pte_t *ptep, pte_t pte, अचिन्हित पूर्णांक ext);
#पूर्ण_अगर
बाह्य व्योम cpu_reset(अचिन्हित दीर्घ addr, bool hvc) __attribute__((noवापस));

/* These three are निजी to arch/arm/kernel/suspend.c */
बाह्य व्योम cpu_करो_suspend(व्योम *);
बाह्य व्योम cpu_करो_resume(व्योम *);
#अन्यथा

बाह्य काष्ठा processor processor;
#अगर defined(CONFIG_BIG_LITTLE) && defined(CONFIG_HARDEN_BRANCH_PREDICTOR)
#समावेश <linux/smp.h>
/*
 * This can't be a per-cpu variable because we need to access it beक्रमe
 * per-cpu has been initialised.  We have a couple of functions that are
 * called in a pre-emptible context, and so can't use smp_processor_id()
 * there, hence PROC_TABLE().  We insist in init_proc_vtable() that the
 * function poपूर्णांकers क्रम these are identical across all CPUs.
 */
बाह्य काष्ठा processor *cpu_vtable[];
#घोषणा PROC_VTABLE(f)			cpu_vtable[smp_processor_id()]->f
#घोषणा PROC_TABLE(f)			cpu_vtable[0]->f
अटल अंतरभूत व्योम init_proc_vtable(स्थिर काष्ठा processor *p)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	*cpu_vtable[cpu] = *p;
	WARN_ON_ONCE(cpu_vtable[cpu]->dcache_clean_area !=
		     cpu_vtable[0]->dcache_clean_area);
	WARN_ON_ONCE(cpu_vtable[cpu]->set_pte_ext !=
		     cpu_vtable[0]->set_pte_ext);
पूर्ण
#अन्यथा
#घोषणा PROC_VTABLE(f)			processor.f
#घोषणा PROC_TABLE(f)			processor.f
अटल अंतरभूत व्योम init_proc_vtable(स्थिर काष्ठा processor *p)
अणु
	processor = *p;
पूर्ण
#पूर्ण_अगर

#घोषणा cpu_proc_init			PROC_VTABLE(_proc_init)
#घोषणा cpu_check_bugs			PROC_VTABLE(check_bugs)
#घोषणा cpu_proc_fin			PROC_VTABLE(_proc_fin)
#घोषणा cpu_reset			PROC_VTABLE(reset)
#घोषणा cpu_करो_idle			PROC_VTABLE(_करो_idle)
#घोषणा cpu_dcache_clean_area		PROC_TABLE(dcache_clean_area)
#घोषणा cpu_set_pte_ext			PROC_TABLE(set_pte_ext)
#घोषणा cpu_करो_चयन_mm		PROC_VTABLE(चयन_mm)

/* These two are निजी to arch/arm/kernel/suspend.c */
#घोषणा cpu_करो_suspend			PROC_VTABLE(करो_suspend)
#घोषणा cpu_करो_resume			PROC_VTABLE(करो_resume)
#पूर्ण_अगर

बाह्य व्योम cpu_resume(व्योम);

#समावेश <यंत्र/memory.h>

#अगर_घोषित CONFIG_MMU

#घोषणा cpu_चयन_mm(pgd,mm) cpu_करो_चयन_mm(virt_to_phys(pgd),mm)

#अगर_घोषित CONFIG_ARM_LPAE

#घोषणा cpu_get_ttbr(nr)					\
	(अणु							\
		u64 ttbr;					\
		__यंत्र__("mrrc	p15, " #nr ", %Q0, %R0, c2"	\
			: "=r" (ttbr));				\
		ttbr;						\
	पूर्ण)

#घोषणा cpu_get_pgd()	\
	(अणु						\
		u64 pg = cpu_get_ttbr(0);		\
		pg &= ~(PTRS_PER_PGD*माप(pgd_t)-1);	\
		(pgd_t *)phys_to_virt(pg);		\
	पूर्ण)
#अन्यथा
#घोषणा cpu_get_pgd()	\
	(अणु						\
		अचिन्हित दीर्घ pg;			\
		__यंत्र__("mrc	p15, 0, %0, c2, c0, 0"	\
			 : "=r" (pg) : : "cc");		\
		pg &= ~0x3fff;				\
		(pgd_t *)phys_to_virt(pg);		\
	पूर्ण)
#पूर्ण_अगर

#अन्यथा	/*!CONFIG_MMU */

#घोषणा cpu_चयन_mm(pgd,mm)	अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_PROCFNS_H */
