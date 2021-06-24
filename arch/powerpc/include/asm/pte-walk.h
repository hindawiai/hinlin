<शैली गुरु>
#अगर_अघोषित _ASM_POWERPC_PTE_WALK_H
#घोषणा _ASM_POWERPC_PTE_WALK_H

#समावेश <linux/sched.h>

/* Don't use this directly */
बाह्य pte_t *__find_linux_pte(pgd_t *pgdir, अचिन्हित दीर्घ ea,
			       bool *is_thp, अचिन्हित *hshअगरt);

अटल अंतरभूत pte_t *find_linux_pte(pgd_t *pgdir, अचिन्हित दीर्घ ea,
				    bool *is_thp, अचिन्हित *hshअगरt)
अणु
	pte_t *pte;

	VM_WARN(!arch_irqs_disabled(), "%s called with irq enabled\n", __func__);
	pte = __find_linux_pte(pgdir, ea, is_thp, hshअगरt);

#अगर defined(CONFIG_DEBUG_VM) &&						\
	!(defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE))
	/*
	 * We should not find huge page अगर these configs are not enabled.
	 */
	अगर (hshअगरt)
		WARN_ON(*hshअगरt);
#पूर्ण_अगर
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t *find_init_mm_pte(अचिन्हित दीर्घ ea, अचिन्हित *hshअगरt)
अणु
	pgd_t *pgdir = init_mm.pgd;
	वापस __find_linux_pte(pgdir, ea, शून्य, hshअगरt);
पूर्ण

/*
 * Convert a kernel vmap भव address (vदो_स्मृति or ioremap space) to a
 * physical address, without taking locks. This can be used in real-mode.
 */
अटल अंतरभूत phys_addr_t ppc_find_vmap_phys(अचिन्हित दीर्घ addr)
अणु
	pte_t *ptep;
	phys_addr_t pa;
	पूर्णांक hugepage_shअगरt;

	/*
	 * init_mm करोes not मुक्त page tables, and करोes not करो THP. It may
	 * have huge pages from huge vदो_स्मृति / ioremap etc.
	 */
	ptep = find_init_mm_pte(addr, &hugepage_shअगरt);
	अगर (WARN_ON(!ptep))
		वापस 0;

	pa = PFN_PHYS(pte_pfn(*ptep));

	अगर (!hugepage_shअगरt)
		hugepage_shअगरt = PAGE_SHIFT;

	pa |= addr & ((1ul << hugepage_shअगरt) - 1);

	वापस pa;
पूर्ण

/*
 * This is what we should always use. Any other lockless page table lookup needs
 * careful audit against THP split.
 */
अटल अंतरभूत pte_t *find_current_mm_pte(pgd_t *pgdir, अचिन्हित दीर्घ ea,
					 bool *is_thp, अचिन्हित *hshअगरt)
अणु
	pte_t *pte;

	VM_WARN(!arch_irqs_disabled(), "%s called with irq enabled\n", __func__);
	VM_WARN(pgdir != current->mm->pgd,
		"%s lock less page table lookup called on wrong mm\n", __func__);
	pte = __find_linux_pte(pgdir, ea, is_thp, hshअगरt);

#अगर defined(CONFIG_DEBUG_VM) &&						\
	!(defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE))
	/*
	 * We should not find huge page अगर these configs are not enabled.
	 */
	अगर (hshअगरt)
		WARN_ON(*hshअगरt);
#पूर्ण_अगर
	वापस pte;
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_PTE_WALK_H */
