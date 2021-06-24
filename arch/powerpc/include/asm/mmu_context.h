<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_POWERPC_MMU_CONTEXT_H
#घोषणा __ASM_POWERPC_MMU_CONTEXT_H
#अगर_घोषित __KERNEL__

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/mmu.h>	
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cputhपढ़ोs.h>

/*
 * Most अगर the context management is out of line
 */
#घोषणा init_new_context init_new_context
बाह्य पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm);
#घोषणा destroy_context destroy_context
बाह्य व्योम destroy_context(काष्ठा mm_काष्ठा *mm);
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
काष्ठा mm_iommu_table_group_mem_t;

बाह्य पूर्णांक isolate_lru_page(काष्ठा page *page);	/* from पूर्णांकernal.h */
बाह्य bool mm_iommu_preरेजिस्टरed(काष्ठा mm_काष्ठा *mm);
बाह्य दीर्घ mm_iommu_new(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ ua, अचिन्हित दीर्घ entries,
		काष्ठा mm_iommu_table_group_mem_t **pmem);
बाह्य दीर्घ mm_iommu_newdev(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ua,
		अचिन्हित दीर्घ entries, अचिन्हित दीर्घ dev_hpa,
		काष्ठा mm_iommu_table_group_mem_t **pmem);
बाह्य दीर्घ mm_iommu_put(काष्ठा mm_काष्ठा *mm,
		काष्ठा mm_iommu_table_group_mem_t *mem);
बाह्य व्योम mm_iommu_init(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम mm_iommu_cleanup(काष्ठा mm_काष्ठा *mm);
बाह्य काष्ठा mm_iommu_table_group_mem_t *mm_iommu_lookup(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ ua, अचिन्हित दीर्घ size);
बाह्य काष्ठा mm_iommu_table_group_mem_t *mm_iommu_lookup_rm(
		काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ua, अचिन्हित दीर्घ size);
बाह्य काष्ठा mm_iommu_table_group_mem_t *mm_iommu_get(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ ua, अचिन्हित दीर्घ entries);
बाह्य दीर्घ mm_iommu_ua_to_hpa(काष्ठा mm_iommu_table_group_mem_t *mem,
		अचिन्हित दीर्घ ua, अचिन्हित पूर्णांक pageshअगरt, अचिन्हित दीर्घ *hpa);
बाह्य दीर्घ mm_iommu_ua_to_hpa_rm(काष्ठा mm_iommu_table_group_mem_t *mem,
		अचिन्हित दीर्घ ua, अचिन्हित पूर्णांक pageshअगरt, अचिन्हित दीर्घ *hpa);
बाह्य व्योम mm_iommu_ua_mark_dirty_rm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ua);
बाह्य bool mm_iommu_is_devmem(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hpa,
		अचिन्हित पूर्णांक pageshअगरt, अचिन्हित दीर्घ *size);
बाह्य दीर्घ mm_iommu_mapped_inc(काष्ठा mm_iommu_table_group_mem_t *mem);
बाह्य व्योम mm_iommu_mapped_dec(काष्ठा mm_iommu_table_group_mem_t *mem);
#अन्यथा
अटल अंतरभूत bool mm_iommu_is_devmem(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hpa,
		अचिन्हित पूर्णांक pageshअगरt, अचिन्हित दीर्घ *size)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम mm_iommu_init(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
#पूर्ण_अगर
बाह्य व्योम चयन_slb(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm);
बाह्य व्योम set_context(अचिन्हित दीर्घ id, pgd_t *pgd);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
बाह्य व्योम radix__चयन_mmu_context(काष्ठा mm_काष्ठा *prev,
				      काष्ठा mm_काष्ठा *next);
अटल अंतरभूत व्योम चयन_mmu_context(काष्ठा mm_काष्ठा *prev,
				      काष्ठा mm_काष्ठा *next,
				      काष्ठा task_काष्ठा *tsk)
अणु
	अगर (radix_enabled())
		वापस radix__चयन_mmu_context(prev, next);
	वापस चयन_slb(tsk, next);
पूर्ण

बाह्य पूर्णांक hash__alloc_context_id(व्योम);
बाह्य व्योम hash__reserve_context_id(पूर्णांक id);
बाह्य व्योम __destroy_context(पूर्णांक context_id);
अटल अंतरभूत व्योम mmu_context_init(व्योम) अणु पूर्ण

अटल अंतरभूत पूर्णांक alloc_extended_context(काष्ठा mm_काष्ठा *mm,
					 अचिन्हित दीर्घ ea)
अणु
	पूर्णांक context_id;

	पूर्णांक index = ea >> MAX_EA_BITS_PER_CONTEXT;

	context_id = hash__alloc_context_id();
	अगर (context_id < 0)
		वापस context_id;

	VM_WARN_ON(mm->context.extended_id[index]);
	mm->context.extended_id[index] = context_id;
	वापस context_id;
पूर्ण

अटल अंतरभूत bool need_extra_context(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea)
अणु
	पूर्णांक context_id;

	context_id = get_user_context(&mm->context, ea);
	अगर (!context_id)
		वापस true;
	वापस false;
पूर्ण

#अन्यथा
बाह्य व्योम चयन_mmu_context(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			       काष्ठा task_काष्ठा *tsk);
बाह्य अचिन्हित दीर्घ __init_new_context(व्योम);
बाह्य व्योम __destroy_context(अचिन्हित दीर्घ context_id);
बाह्य व्योम mmu_context_init(व्योम);
अटल अंतरभूत पूर्णांक alloc_extended_context(काष्ठा mm_काष्ठा *mm,
					 अचिन्हित दीर्घ ea)
अणु
	/* non book3s_64 should never find this called */
	WARN_ON(1);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत bool need_extra_context(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_KVM_BOOK3S_HV_POSSIBLE) && defined(CONFIG_PPC_RADIX_MMU)
बाह्य व्योम radix_kvm_prefetch_workaround(काष्ठा mm_काष्ठा *mm);
#अन्यथा
अटल अंतरभूत व्योम radix_kvm_prefetch_workaround(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम चयन_cop(काष्ठा mm_काष्ठा *next);
बाह्य पूर्णांक use_cop(अचिन्हित दीर्घ acop, काष्ठा mm_काष्ठा *mm);
बाह्य व्योम drop_cop(अचिन्हित दीर्घ acop, काष्ठा mm_काष्ठा *mm);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल अंतरभूत व्योम inc_mm_active_cpus(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_inc(&mm->context.active_cpus);
पूर्ण

अटल अंतरभूत व्योम dec_mm_active_cpus(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_dec(&mm->context.active_cpus);
पूर्ण

अटल अंतरभूत व्योम mm_context_add_copro(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * If any copro is in use, increment the active CPU count
	 * in order to क्रमce TLB invalidations to be global as to
	 * propagate to the Nest MMU.
	 */
	अगर (atomic_inc_वापस(&mm->context.copros) == 1)
		inc_mm_active_cpus(mm);
पूर्ण

अटल अंतरभूत व्योम mm_context_हटाओ_copro(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक c;

	/*
	 * When removing the last copro, we need to broadcast a global
	 * flush of the full mm, as the next TLBI may be local and the
	 * nMMU and/or PSL need to be cleaned up.
	 *
	 * Both the 'copros' and 'active_cpus' counts are looked at in
	 * flush_all_mm() to determine the scope (local/global) of the
	 * TLBIs, so we need to flush first beक्रमe decrementing
	 * 'copros'. If this API is used by several callers क्रम the
	 * same context, it can lead to over-flushing. It's hopefully
	 * not common enough to be a problem.
	 *
	 * Skip on hash, as we करोn't know how to करो the proper flush
	 * क्रम the समय being. Invalidations will reमुख्य global अगर
	 * used on hash. Note that we can't drop 'copros' either, as
	 * it could make some invalidations local with no flush
	 * in-between.
	 */
	अगर (radix_enabled()) अणु
		flush_all_mm(mm);

		c = atomic_dec_अगर_positive(&mm->context.copros);
		/* Detect imbalance between add and हटाओ */
		WARN_ON(c < 0);

		अगर (c == 0)
			dec_mm_active_cpus(mm);
	पूर्ण
पूर्ण

/*
 * vas_winकरोws counter shows number of खोलो winकरोws in the mm
 * context. During context चयन, use this counter to clear the
 * क्रमeign real address mapping (CP_ABORT) क्रम the thपढ़ो / process
 * that पूर्णांकend to use COPY/PASTE. When a process बंदs all winकरोws,
 * disable CP_ABORT which is expensive to run.
 *
 * For user context, रेजिस्टर a copro so that TLBIs are seen by the
 * nest MMU. mm_context_add/हटाओ_vas_winकरोw() are used only क्रम user
 * space winकरोws.
 */
अटल अंतरभूत व्योम mm_context_add_vas_winकरोw(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_inc(&mm->context.vas_winकरोws);
	mm_context_add_copro(mm);
पूर्ण

अटल अंतरभूत व्योम mm_context_हटाओ_vas_winकरोw(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक v;

	mm_context_हटाओ_copro(mm);
	v = atomic_dec_अगर_positive(&mm->context.vas_winकरोws);

	/* Detect imbalance between add and हटाओ */
	WARN_ON(v < 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम inc_mm_active_cpus(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
अटल अंतरभूत व्योम dec_mm_active_cpus(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
अटल अंतरभूत व्योम mm_context_add_copro(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
अटल अंतरभूत व्योम mm_context_हटाओ_copro(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
#पूर्ण_अगर


बाह्य व्योम चयन_mm_irqs_off(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			       काष्ठा task_काष्ठा *tsk);

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	चयन_mm_irqs_off(prev, next, tsk);
	local_irq_restore(flags);
पूर्ण
#घोषणा चयन_mm_irqs_off चयन_mm_irqs_off

/*
 * After we have set current->mm to a new value, this activates
 * the context क्रम the new mm so we see the new mappings.
 */
#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	चयन_mm_irqs_off(prev, next, current);
पूर्ण

/* We करोn't currently use enter_lazy_tlb() क्रम anything */
#अगर_घोषित CONFIG_PPC_BOOK3E_64
#घोषणा enter_lazy_tlb enter_lazy_tlb
अटल अंतरभूत व्योम enter_lazy_tlb(काष्ठा mm_काष्ठा *mm,
				  काष्ठा task_काष्ठा *tsk)
अणु
	/* 64-bit Book3E keeps track of current PGD in the PACA */
	get_paca()->pgd = शून्य;
पूर्ण
#पूर्ण_अगर

बाह्य व्योम arch_निकास_mmap(काष्ठा mm_काष्ठा *mm);

अटल अंतरभूत व्योम arch_unmap(काष्ठा mm_काष्ठा *mm,
			      अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ vdso_base = (अचिन्हित दीर्घ)mm->context.vdso;

	अगर (start <= vdso_base && vdso_base < end)
		mm->context.vdso = शून्य;
पूर्ण

#अगर_घोषित CONFIG_PPC_MEM_KEYS
bool arch_vma_access_permitted(काष्ठा vm_area_काष्ठा *vma, bool ग_लिखो,
			       bool execute, bool क्रमeign);
व्योम arch_dup_pkeys(काष्ठा mm_काष्ठा *oldmm, काष्ठा mm_काष्ठा *mm);
#अन्यथा /* CONFIG_PPC_MEM_KEYS */
अटल अंतरभूत bool arch_vma_access_permitted(काष्ठा vm_area_काष्ठा *vma,
		bool ग_लिखो, bool execute, bool क्रमeign)
अणु
	/* by शेष, allow everything */
	वापस true;
पूर्ण

#घोषणा pkey_mm_init(mm)
#घोषणा arch_dup_pkeys(oldmm, mm)

अटल अंतरभूत u64 pte_to_hpte_pkey_bits(u64 pteflags, अचिन्हित दीर्घ flags)
अणु
	वापस 0x0UL;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_MEM_KEYS */

अटल अंतरभूत पूर्णांक arch_dup_mmap(काष्ठा mm_काष्ठा *oldmm,
				काष्ठा mm_काष्ठा *mm)
अणु
	arch_dup_pkeys(oldmm, mm);
	वापस 0;
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_POWERPC_MMU_CONTEXT_H */
