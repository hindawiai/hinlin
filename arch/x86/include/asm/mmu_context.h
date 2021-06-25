<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MMU_CONTEXT_H
#घोषणा _ASM_X86_MMU_CONTEXT_H

#समावेश <यंत्र/desc.h>
#समावेश <linux/atomic.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pkeys.h>

#समावेश <trace/events/tlb.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/debugreg.h>

बाह्य atomic64_t last_mm_ctx_id;

#अगर_अघोषित CONFIG_PARAVIRT_XXL
अटल अंतरभूत व्योम paravirt_activate_mm(काष्ठा mm_काष्ठा *prev,
					काष्ठा mm_काष्ठा *next)
अणु
पूर्ण
#पूर्ण_अगर	/* !CONFIG_PARAVIRT_XXL */

#अगर_घोषित CONFIG_PERF_EVENTS
DECLARE_STATIC_KEY_FALSE(rdpmc_never_available_key);
DECLARE_STATIC_KEY_FALSE(rdpmc_always_available_key);
व्योम cr4_update_pce(व्योम *ignored);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
/*
 * ldt_काष्ठाs can be allocated, used, and मुक्तd, but they are never
 * modअगरied जबतक live.
 */
काष्ठा ldt_काष्ठा अणु
	/*
	 * Xen requires page-aligned LDTs with special permissions.  This is
	 * needed to prevent us from installing evil descriptors such as
	 * call gates.  On native, we could merge the ldt_काष्ठा and LDT
	 * allocations, but it's not worth trying to optimize.
	 */
	काष्ठा desc_काष्ठा	*entries;
	अचिन्हित पूर्णांक		nr_entries;

	/*
	 * If PTI is in use, then the entries array is not mapped जबतक we're
	 * in user mode.  The whole array will be aliased at the addressed
	 * given by ldt_slot_va(slot).  We use two slots so that we can allocate
	 * and map, and enable a new LDT without invalidating the mapping
	 * of an older, still-in-use LDT.
	 *
	 * slot will be -1 अगर this LDT करोesn't have an alias mapping.
	 */
	पूर्णांक			slot;
पूर्ण;

/*
 * Used क्रम LDT copy/deकाष्ठाion.
 */
अटल अंतरभूत व्योम init_new_context_ldt(काष्ठा mm_काष्ठा *mm)
अणु
	mm->context.ldt = शून्य;
	init_rwsem(&mm->context.ldt_usr_sem);
पूर्ण
पूर्णांक ldt_dup_context(काष्ठा mm_काष्ठा *oldmm, काष्ठा mm_काष्ठा *mm);
व्योम destroy_context_ldt(काष्ठा mm_काष्ठा *mm);
व्योम ldt_arch_निकास_mmap(काष्ठा mm_काष्ठा *mm);
#अन्यथा	/* CONFIG_MODIFY_LDT_SYSCALL */
अटल अंतरभूत व्योम init_new_context_ldt(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
अटल अंतरभूत पूर्णांक ldt_dup_context(काष्ठा mm_काष्ठा *oldmm,
				  काष्ठा mm_काष्ठा *mm)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम destroy_context_ldt(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
अटल अंतरभूत व्योम ldt_arch_निकास_mmap(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
बाह्य व्योम load_mm_ldt(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम चयन_ldt(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next);
#अन्यथा
अटल अंतरभूत व्योम load_mm_ldt(काष्ठा mm_काष्ठा *mm)
अणु
	clear_LDT();
पूर्ण
अटल अंतरभूत व्योम चयन_ldt(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	DEBUG_LOCKS_WARN_ON(preemptible());
पूर्ण
#पूर्ण_अगर

#घोषणा enter_lazy_tlb enter_lazy_tlb
बाह्य व्योम enter_lazy_tlb(काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *tsk);

/*
 * Init a new mm.  Used on mm copies, like at विभाजन()
 * and on mm's that are bअक्रम-new, like at execve().
 */
#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
				   काष्ठा mm_काष्ठा *mm)
अणु
	mutex_init(&mm->context.lock);

	mm->context.ctx_id = atomic64_inc_वापस(&last_mm_ctx_id);
	atomic64_set(&mm->context.tlb_gen, 0);

#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
	अगर (cpu_feature_enabled(X86_FEATURE_OSPKE)) अणु
		/* pkey 0 is the शेष and allocated implicitly */
		mm->context.pkey_allocation_map = 0x1;
		/* -1 means unallocated or invalid */
		mm->context.execute_only_pkey = -1;
	पूर्ण
#पूर्ण_अगर
	init_new_context_ldt(mm);
	वापस 0;
पूर्ण

#घोषणा destroy_context destroy_context
अटल अंतरभूत व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	destroy_context_ldt(mm);
पूर्ण

बाह्य व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
		      काष्ठा task_काष्ठा *tsk);

बाह्य व्योम चयन_mm_irqs_off(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			       काष्ठा task_काष्ठा *tsk);
#घोषणा चयन_mm_irqs_off चयन_mm_irqs_off

#घोषणा activate_mm(prev, next)			\
करो अणु						\
	paravirt_activate_mm((prev), (next));	\
	चयन_mm((prev), (next), शून्य);	\
पूर्ण जबतक (0);

#अगर_घोषित CONFIG_X86_32
#घोषणा deactivate_mm(tsk, mm)			\
करो अणु						\
	lazy_load_gs(0);			\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा deactivate_mm(tsk, mm)			\
करो अणु						\
	load_gs_index(0);			\
	loadsegment(fs, 0);			\
पूर्ण जबतक (0)
#पूर्ण_अगर

अटल अंतरभूत व्योम arch_dup_pkeys(काष्ठा mm_काष्ठा *oldmm,
				  काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
	अगर (!cpu_feature_enabled(X86_FEATURE_OSPKE))
		वापस;

	/* Duplicate the oldmm pkey state in mm: */
	mm->context.pkey_allocation_map = oldmm->context.pkey_allocation_map;
	mm->context.execute_only_pkey   = oldmm->context.execute_only_pkey;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक arch_dup_mmap(काष्ठा mm_काष्ठा *oldmm, काष्ठा mm_काष्ठा *mm)
अणु
	arch_dup_pkeys(oldmm, mm);
	paravirt_arch_dup_mmap(oldmm, mm);
	वापस ldt_dup_context(oldmm, mm);
पूर्ण

अटल अंतरभूत व्योम arch_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	paravirt_arch_निकास_mmap(mm);
	ldt_arch_निकास_mmap(mm);
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल अंतरभूत bool is_64bit_mm(काष्ठा mm_काष्ठा *mm)
अणु
	वापस	!IS_ENABLED(CONFIG_IA32_EMULATION) ||
		!(mm->context.flags & MM_CONTEXT_UPROBE_IA32);
पूर्ण
#अन्यथा
अटल अंतरभूत bool is_64bit_mm(काष्ठा mm_काष्ठा *mm)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम arch_unmap(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ end)
अणु
पूर्ण

/*
 * We only want to enक्रमce protection keys on the current process
 * because we effectively have no access to PKRU क्रम other
 * processes or any way to tell *which * PKRU in a thपढ़ोed
 * process we could use.
 *
 * So करो not enक्रमce things अगर the VMA is not from the current
 * mm, or अगर we are in a kernel thपढ़ो.
 */
अटल अंतरभूत bool arch_vma_access_permitted(काष्ठा vm_area_काष्ठा *vma,
		bool ग_लिखो, bool execute, bool क्रमeign)
अणु
	/* pkeys never affect inकाष्ठाion fetches */
	अगर (execute)
		वापस true;
	/* allow access अगर the VMA is not one from this process */
	अगर (क्रमeign || vma_is_क्रमeign(vma))
		वापस true;
	वापस __pkru_allows_pkey(vma_pkey(vma), ग_लिखो);
पूर्ण

अचिन्हित दीर्घ __get_current_cr3_fast(व्योम);

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* _ASM_X86_MMU_CONTEXT_H */
