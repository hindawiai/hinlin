<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999 Niibe Yutaka
 * Copyright (C) 2003 - 2007 Paul Mundt
 *
 * ASID handling idea taken from MIPS implementation.
 */
#अगर_अघोषित __ASM_SH_MMU_CONTEXT_H
#घोषणा __ASM_SH_MMU_CONTEXT_H

#समावेश <cpu/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm_types.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र-generic/mm_hooks.h>

/*
 * The MMU "context" consists of two things:
 *    (a) TLB cache version (or round, cycle whatever expression you like)
 *    (b) ASID (Address Space IDentअगरier)
 */
#अगर_घोषित CONFIG_CPU_HAS_PTEAEX
#घोषणा MMU_CONTEXT_ASID_MASK		0x0000ffff
#अन्यथा
#घोषणा MMU_CONTEXT_ASID_MASK		0x000000ff
#पूर्ण_अगर

#घोषणा MMU_CONTEXT_VERSION_MASK	(~0UL & ~MMU_CONTEXT_ASID_MASK)
#घोषणा MMU_CONTEXT_FIRST_VERSION	(MMU_CONTEXT_ASID_MASK + 1)

/* Impossible ASID value, to dअगरferentiate from NO_CONTEXT. */
#घोषणा MMU_NO_ASID			MMU_CONTEXT_FIRST_VERSION
#घोषणा NO_CONTEXT			0UL

#घोषणा asid_cache(cpu)		(cpu_data[cpu].asid_cache)

#अगर_घोषित CONFIG_MMU
#घोषणा cpu_context(cpu, mm)	((mm)->context.id[cpu])

#घोषणा cpu_asid(cpu, mm)	\
	(cpu_context((cpu), (mm)) & MMU_CONTEXT_ASID_MASK)

/*
 * Virtual Page Number mask
 */
#घोषणा MMU_VPN_MASK	0xfffff000

#समावेश <यंत्र/mmu_context_32.h>

/*
 * Get MMU context अगर needed.
 */
अटल अंतरभूत व्योम get_mmu_context(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ asid = asid_cache(cpu);

	/* Check अगर we have old version of context. */
	अगर (((cpu_context(cpu, mm) ^ asid) & MMU_CONTEXT_VERSION_MASK) == 0)
		/* It's up to date, करो nothing */
		वापस;

	/* It's old, we need to get new context with new version. */
	अगर (!(++asid & MMU_CONTEXT_ASID_MASK)) अणु
		/*
		 * We exhaust ASID of this version.
		 * Flush all TLB and start new cycle.
		 */
		local_flush_tlb_all();

		/*
		 * Fix version; Note that we aव्योम version #0
		 * to distinguish NO_CONTEXT.
		 */
		अगर (!asid)
			asid = MMU_CONTEXT_FIRST_VERSION;
	पूर्ण

	cpu_context(cpu, mm) = asid_cache(cpu) = asid;
पूर्ण

/*
 * Initialize the context related info क्रम a new mm_काष्ठा
 * instance.
 */
#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
				   काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक i;

	क्रम_each_online_cpu(i)
		cpu_context(i, mm) = NO_CONTEXT;

	वापस 0;
पूर्ण

/*
 * After we have set current->mm to a new value, this activates
 * the context क्रम the new mm so we see the new mappings.
 */
अटल अंतरभूत व्योम activate_context(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	get_mmu_context(mm, cpu);
	set_asid(cpu_asid(cpu, mm));
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev,
			     काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (likely(prev != next)) अणु
		cpumask_set_cpu(cpu, mm_cpumask(next));
		set_TTB(next->pgd);
		activate_context(next, cpu);
	पूर्ण अन्यथा
		अगर (!cpumask_test_and_set_cpu(cpu, mm_cpumask(next)))
			activate_context(next, cpu);
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#अन्यथा

#घोषणा set_asid(asid)			करो अणु पूर्ण जबतक (0)
#घोषणा get_asid()			(0)
#घोषणा cpu_asid(cpu, mm)		(अणु (व्योम)cpu; NO_CONTEXT; पूर्ण)
#घोषणा चयन_and_save_asid(asid)	(0)
#घोषणा set_TTB(pgd)			करो अणु पूर्ण जबतक (0)
#घोषणा get_TTB()			(0)

#समावेश <यंत्र-generic/nommu_context.h>

#पूर्ण_अगर /* CONFIG_MMU */

#अगर defined(CONFIG_CPU_SH3) || defined(CONFIG_CPU_SH4)
/*
 * If this processor has an MMU, we need methods to turn it off/on ..
 * paging_init() will also have to be updated क्रम the processor in
 * question.
 */
अटल अंतरभूत व्योम enable_mmu(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* Enable MMU */
	__raw_ग_लिखोl(MMU_CONTROL_INIT, MMUCR);
	ctrl_barrier();

	अगर (asid_cache(cpu) == NO_CONTEXT)
		asid_cache(cpu) = MMU_CONTEXT_FIRST_VERSION;

	set_asid(asid_cache(cpu) & MMU_CONTEXT_ASID_MASK);
पूर्ण

अटल अंतरभूत व्योम disable_mmu(व्योम)
अणु
	अचिन्हित दीर्घ cr;

	cr = __raw_पढ़ोl(MMUCR);
	cr &= ~MMU_CONTROL_INIT;
	__raw_ग_लिखोl(cr, MMUCR);

	ctrl_barrier();
पूर्ण
#अन्यथा
/*
 * MMU control handlers क्रम processors lacking memory
 * management hardware.
 */
#घोषणा enable_mmu()	करो अणु पूर्ण जबतक (0)
#घोषणा disable_mmu()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_MMU_CONTEXT_H */
