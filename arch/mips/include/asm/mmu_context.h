<शैली गुरु>
/*
 * Switch a MMU context.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 1998, 1999 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_MMU_CONTEXT_H
#घोषणा _ASM_MMU_CONTEXT_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/smp.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/dsemul.h>
#समावेश <यंत्र/ginvt.h>
#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र-generic/mm_hooks.h>

#घोषणा htw_set_pwbase(pgd)						\
करो अणु									\
	अगर (cpu_has_htw) अणु						\
		ग_लिखो_c0_pwbase(pgd);					\
		back_to_back_c0_hazard();				\
	पूर्ण								\
पूर्ण जबतक (0)

बाह्य व्योम tlbmiss_handler_setup_pgd(अचिन्हित दीर्घ);
बाह्य अक्षर tlbmiss_handler_setup_pgd_end[];

/* Note: This is also implemented with uयंत्र in arch/mips/kvm/entry.c */
#घोषणा TLBMISS_HANDLER_SETUP_PGD(pgd)					\
करो अणु									\
	tlbmiss_handler_setup_pgd((अचिन्हित दीर्घ)(pgd));		\
	htw_set_pwbase((अचिन्हित दीर्घ)pgd);				\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_MIPS_PGD_C0_CONTEXT

#घोषणा TLBMISS_HANDLER_RESTORE()					\
	ग_लिखो_c0_xcontext((अचिन्हित दीर्घ) smp_processor_id() <<		\
			  SMP_CPUID_REGSHIFT)

#घोषणा TLBMISS_HANDLER_SETUP()						\
	करो अणु								\
		TLBMISS_HANDLER_SETUP_PGD(swapper_pg_dir);		\
		TLBMISS_HANDLER_RESTORE();				\
	पूर्ण जबतक (0)

#अन्यथा /* !CONFIG_MIPS_PGD_C0_CONTEXT: using  pgd_current*/

/*
 * For the fast tlb miss handlers, we keep a per cpu array of poपूर्णांकers
 * to the current pgd क्रम each processor. Also, the proc. id is stuffed
 * पूर्णांकo the context रेजिस्टर.
 */
बाह्य अचिन्हित दीर्घ pgd_current[];

#घोषणा TLBMISS_HANDLER_RESTORE()					\
	ग_लिखो_c0_context((अचिन्हित दीर्घ) smp_processor_id() <<		\
			 SMP_CPUID_REGSHIFT)

#घोषणा TLBMISS_HANDLER_SETUP()						\
	TLBMISS_HANDLER_RESTORE();					\
	back_to_back_c0_hazard();					\
	TLBMISS_HANDLER_SETUP_PGD(swapper_pg_dir)
#पूर्ण_अगर /* CONFIG_MIPS_PGD_C0_CONTEXT*/

/*
 * The ginvt inकाष्ठाion will invalidate wired entries when its type field
 * tarमाला_लो anything other than the entire TLB. That means that अगर we were to
 * allow the kernel to create wired entries with the MMID of current->active_mm
 * then those wired entries could be invalidated when we later use ginvt to
 * invalidate TLB entries with that MMID.
 *
 * In order to prevent ginvt from trashing wired entries, we reserve one MMID
 * क्रम use by the kernel when creating wired entries. This MMID will never be
 * asचिन्हित to a काष्ठा mm, and we'll never target it with a ginvt inकाष्ठाion.
 */
#घोषणा MMID_KERNEL_WIRED	0

/*
 *  All unused by hardware upper bits will be considered
 *  as a software asid extension.
 */
अटल अंतरभूत u64 asid_version_mask(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ asid_mask = cpu_asid_mask(&cpu_data[cpu]);

	वापस ~(u64)(asid_mask | (asid_mask - 1));
पूर्ण

अटल अंतरभूत u64 asid_first_version(अचिन्हित पूर्णांक cpu)
अणु
	वापस ~asid_version_mask(cpu) + 1;
पूर्ण

अटल अंतरभूत u64 cpu_context(अचिन्हित पूर्णांक cpu, स्थिर काष्ठा mm_काष्ठा *mm)
अणु
	अगर (cpu_has_mmid)
		वापस atomic64_पढ़ो(&mm->context.mmid);

	वापस mm->context.asid[cpu];
पूर्ण

अटल अंतरभूत व्योम set_cpu_context(अचिन्हित पूर्णांक cpu,
				   काष्ठा mm_काष्ठा *mm, u64 ctx)
अणु
	अगर (cpu_has_mmid)
		atomic64_set(&mm->context.mmid, ctx);
	अन्यथा
		mm->context.asid[cpu] = ctx;
पूर्ण

#घोषणा asid_cache(cpu)		(cpu_data[cpu].asid_cache)
#घोषणा cpu_asid(cpu, mm) \
	(cpu_context((cpu), (mm)) & cpu_asid_mask(&cpu_data[cpu]))

बाह्य व्योम get_new_mmu_context(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम check_mmu_context(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम check_चयन_mmu_context(काष्ठा mm_काष्ठा *mm);

/*
 * Initialize the context related info क्रम a new mm_काष्ठा
 * instance.
 */
#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक
init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक i;

	अगर (cpu_has_mmid) अणु
		set_cpu_context(0, mm, 0);
	पूर्ण अन्यथा अणु
		क्रम_each_possible_cpu(i)
			set_cpu_context(i, mm, 0);
	पूर्ण

	mm->context.bd_emupage_allocmap = शून्य;
	spin_lock_init(&mm->context.bd_emupage_lock);
	init_रुकोqueue_head(&mm->context.bd_emupage_queue);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);

	htw_stop();
	check_चयन_mmu_context(next);

	/*
	 * Mark current->active_mm as not "active" anymore.
	 * We करोn't want to mislead possible IPI tlb flush routines.
	 */
	cpumask_clear_cpu(cpu, mm_cpumask(prev));
	cpumask_set_cpu(cpu, mm_cpumask(next));
	htw_start();

	local_irq_restore(flags);
पूर्ण

/*
 * Destroy context related info क्रम an mm_काष्ठा that is about
 * to be put to rest.
 */
#घोषणा destroy_context destroy_context
अटल अंतरभूत व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	dsemul_mm_cleanup(mm);
पूर्ण

अटल अंतरभूत व्योम
drop_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cpu;
	u32 old_mmid;
	u64 ctx;

	local_irq_save(flags);

	cpu = smp_processor_id();
	ctx = cpu_context(cpu, mm);

	अगर (!ctx) अणु
		/* no-op */
	पूर्ण अन्यथा अगर (cpu_has_mmid) अणु
		/*
		 * Globally invalidating TLB entries associated with the MMID
		 * is pretty cheap using the GINVT inकाष्ठाion, so we'll करो
		 * that rather than incur the overhead of allocating a new
		 * MMID. The latter would be especially dअगरficult since MMIDs
		 * are global & other CPUs may be actively using ctx.
		 */
		htw_stop();
		old_mmid = पढ़ो_c0_memorymapid();
		ग_लिखो_c0_memorymapid(ctx & cpu_asid_mask(&cpu_data[cpu]));
		mtc0_tlbw_hazard();
		ginvt_mmid();
		sync_ginv();
		ग_लिखो_c0_memorymapid(old_mmid);
		inकाष्ठाion_hazard();
		htw_start();
	पूर्ण अन्यथा अगर (cpumask_test_cpu(cpu, mm_cpumask(mm))) अणु
		/*
		 * mm is currently active, so we can't really drop it.
		 * Instead we bump the ASID.
		 */
		htw_stop();
		get_new_mmu_context(mm);
		ग_लिखो_c0_entryhi(cpu_asid(cpu, mm));
		htw_start();
	पूर्ण अन्यथा अणु
		/* will get a new context next समय */
		set_cpu_context(cpu, mm, 0);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* _ASM_MMU_CONTEXT_H */
