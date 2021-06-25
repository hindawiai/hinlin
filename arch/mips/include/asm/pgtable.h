<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 Ralf Baechle
 */
#अगर_अघोषित _ASM_PGTABLE_H
#घोषणा _ASM_PGTABLE_H

#समावेश <linux/mm_types.h>
#समावेश <linux/mmzone.h>
#अगर_घोषित CONFIG_32BIT
#समावेश <यंत्र/pgtable-32.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_64BIT
#समावेश <यंत्र/pgtable-64.h>
#पूर्ण_अगर

#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pgtable-bits.h>
#समावेश <यंत्र/cpu-features.h>

काष्ठा mm_काष्ठा;
काष्ठा vm_area_काष्ठा;

#घोषणा PAGE_SHARED	vm_get_page_prot(VM_READ|VM_WRITE|VM_SHARED)

#घोषणा PAGE_KERNEL	__pgprot(_PAGE_PRESENT | __READABLE | __WRITEABLE | \
				 _PAGE_GLOBAL | _page_cachable_शेष)
#घोषणा PAGE_KERNEL_NC	__pgprot(_PAGE_PRESENT | __READABLE | __WRITEABLE | \
				 _PAGE_GLOBAL | _CACHE_CACHABLE_NONCOHERENT)
#घोषणा PAGE_KERNEL_UNCACHED __pgprot(_PAGE_PRESENT | __READABLE | \
			__WRITEABLE | _PAGE_GLOBAL | _CACHE_UNCACHED)

/*
 * If _PAGE_NO_EXEC is not defined, we can't करो page protection क्रम
 * execute, and consider it to be the same as पढ़ो. Also, ग_लिखो
 * permissions imply पढ़ो permissions. This is the बंदst we can get
 * by reasonable means..
 */

/*
 * Dummy values to fill the table in mmap.c
 * The real values will be generated at runसमय
 */
#घोषणा __P000 __pgprot(0)
#घोषणा __P001 __pgprot(0)
#घोषणा __P010 __pgprot(0)
#घोषणा __P011 __pgprot(0)
#घोषणा __P100 __pgprot(0)
#घोषणा __P101 __pgprot(0)
#घोषणा __P110 __pgprot(0)
#घोषणा __P111 __pgprot(0)

#घोषणा __S000 __pgprot(0)
#घोषणा __S001 __pgprot(0)
#घोषणा __S010 __pgprot(0)
#घोषणा __S011 __pgprot(0)
#घोषणा __S100 __pgprot(0)
#घोषणा __S101 __pgprot(0)
#घोषणा __S110 __pgprot(0)
#घोषणा __S111 __pgprot(0)

बाह्य अचिन्हित दीर्घ _page_cachable_शेष;
बाह्य व्योम __update_cache(अचिन्हित दीर्घ address, pte_t pte);

/*
 * ZERO_PAGE is a global shared page that is always zero; used
 * क्रम zero-mapped memory areas etc..
 */

बाह्य अचिन्हित दीर्घ empty_zero_page;
बाह्य अचिन्हित दीर्घ zero_page_mask;

#घोषणा ZERO_PAGE(vaddr) \
	(virt_to_page((व्योम *)(empty_zero_page + (((अचिन्हित दीर्घ)(vaddr)) & zero_page_mask))))
#घोषणा __HAVE_COLOR_ZERO_PAGE

बाह्य व्योम paging_init(व्योम);

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा pmd_phys(pmd)		virt_to_phys((व्योम *)pmd_val(pmd))

#घोषणा __pmd_page(pmd)		(pfn_to_page(pmd_phys(pmd) >> PAGE_SHIFT))
#अगर_अघोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा pmd_page(pmd)		__pmd_page(pmd)
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE  */

#घोषणा pmd_page_vaddr(pmd)	pmd_val(pmd)

#घोषणा htw_stop()							\
करो अणु									\
	अचिन्हित दीर्घ __flags;						\
									\
	अगर (cpu_has_htw) अणु						\
		local_irq_save(__flags);				\
		अगर(!raw_current_cpu_data.htw_seq++) अणु			\
			ग_लिखो_c0_pwctl(पढ़ो_c0_pwctl() &		\
				       ~(1 << MIPS_PWCTL_PWEN_SHIFT));	\
			back_to_back_c0_hazard();			\
		पूर्ण							\
		local_irq_restore(__flags);				\
	पूर्ण								\
पूर्ण जबतक(0)

#घोषणा htw_start()							\
करो अणु									\
	अचिन्हित दीर्घ __flags;						\
									\
	अगर (cpu_has_htw) अणु						\
		local_irq_save(__flags);				\
		अगर (!--raw_current_cpu_data.htw_seq) अणु			\
			ग_लिखो_c0_pwctl(पढ़ो_c0_pwctl() |		\
				       (1 << MIPS_PWCTL_PWEN_SHIFT));	\
			back_to_back_c0_hazard();			\
		पूर्ण							\
		local_irq_restore(__flags);				\
	पूर्ण								\
पूर्ण जबतक(0)

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep, pte_t pteval);

#अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)

#अगर_घोषित CONFIG_XPA
# define pte_none(pte)		(!(((pte).pte_high) & ~_PAGE_GLOBAL))
#अन्यथा
# define pte_none(pte)		(!(((pte).pte_low | (pte).pte_high) & ~_PAGE_GLOBAL))
#पूर्ण_अगर

#घोषणा pte_present(pte)	((pte).pte_low & _PAGE_PRESENT)
#घोषणा pte_no_exec(pte)	((pte).pte_low & _PAGE_NO_EXEC)

अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pte)
अणु
	ptep->pte_high = pte.pte_high;
	smp_wmb();
	ptep->pte_low = pte.pte_low;

#अगर_घोषित CONFIG_XPA
	अगर (pte.pte_high & _PAGE_GLOBAL) अणु
#अन्यथा
	अगर (pte.pte_low & _PAGE_GLOBAL) अणु
#पूर्ण_अगर
		pte_t *buddy = ptep_buddy(ptep);
		/*
		 * Make sure the buddy is global too (अगर it's !none,
		 * it better alपढ़ोy be global)
		 */
		अगर (pte_none(*buddy)) अणु
			अगर (!IS_ENABLED(CONFIG_XPA))
				buddy->pte_low |= _PAGE_GLOBAL;
			buddy->pte_high |= _PAGE_GLOBAL;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t null = __pte(0);

	htw_stop();
	/* Preserve global status क्रम the pair */
	अगर (IS_ENABLED(CONFIG_XPA)) अणु
		अगर (ptep_buddy(ptep)->pte_high & _PAGE_GLOBAL)
			null.pte_high = _PAGE_GLOBAL;
	पूर्ण अन्यथा अणु
		अगर (ptep_buddy(ptep)->pte_low & _PAGE_GLOBAL)
			null.pte_low = null.pte_high = _PAGE_GLOBAL;
	पूर्ण

	set_pte_at(mm, addr, ptep, null);
	htw_start();
पूर्ण
#अन्यथा

#घोषणा pte_none(pte)		(!(pte_val(pte) & ~_PAGE_GLOBAL))
#घोषणा pte_present(pte)	(pte_val(pte) & _PAGE_PRESENT)
#घोषणा pte_no_exec(pte)	(pte_val(pte) & _PAGE_NO_EXEC)

/*
 * Certain architectures need to करो special things when pte's
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pteval)
अणु
	*ptep = pteval;
#अगर !defined(CONFIG_CPU_R3K_TLB)
	अगर (pte_val(pteval) & _PAGE_GLOBAL) अणु
		pte_t *buddy = ptep_buddy(ptep);
		/*
		 * Make sure the buddy is global too (अगर it's !none,
		 * it better alपढ़ोy be global)
		 */
# अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && !defined(CONFIG_CPU_MIPS32)
		cmpxchg64(&buddy->pte, 0, _PAGE_GLOBAL);
# अन्यथा
		cmpxchg(&buddy->pte, 0, _PAGE_GLOBAL);
# endअगर
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	htw_stop();
#अगर !defined(CONFIG_CPU_R3K_TLB)
	/* Preserve global status क्रम the pair */
	अगर (pte_val(*ptep_buddy(ptep)) & _PAGE_GLOBAL)
		set_pte_at(mm, addr, ptep, __pte(_PAGE_GLOBAL));
	अन्यथा
#पूर्ण_अगर
		set_pte_at(mm, addr, ptep, __pte(0));
	htw_start();
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep, pte_t pteval)
अणु

	अगर (!pte_present(pteval))
		जाओ cache_sync_करोne;

	अगर (pte_present(*ptep) && (pte_pfn(*ptep) == pte_pfn(pteval)))
		जाओ cache_sync_करोne;

	__update_cache(addr, pteval);
cache_sync_करोne:
	set_pte(ptep, pteval);
पूर्ण

/*
 * (pmds are folded पूर्णांकo puds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
#घोषणा set_pmd(pmdptr, pmdval) करो अणु *(pmdptr) = (pmdval); पूर्ण जबतक(0)

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
/*
 * (puds are folded पूर्णांकo pgds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
#घोषणा set_pud(pudptr, pudval) करो अणु *(pudptr) = (pudval); पूर्ण जबतक(0)
#पूर्ण_अगर

#घोषणा PGD_T_LOG2	(__builtin_ffs(माप(pgd_t)) - 1)
#घोषणा PMD_T_LOG2	(__builtin_ffs(माप(pmd_t)) - 1)
#घोषणा PTE_T_LOG2	(__builtin_ffs(माप(pte_t)) - 1)

/*
 * We used to declare this array with size but gcc 3.3 and older are not able
 * to find that this expression is a स्थिरant, so the size is dropped.
 */
बाह्य pgd_t swapper_pg_dir[];

/*
 * Platक्रमm specअगरic pte_special() and pte_mkspecial() definitions
 * are required only when ARCH_HAS_PTE_SPECIAL is enabled.
 */
#अगर defined(CONFIG_ARCH_HAS_PTE_SPECIAL)
#अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)
अटल अंतरभूत पूर्णांक pte_special(pte_t pte)
अणु
	वापस pte.pte_low & _PAGE_SPECIAL;
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	pte.pte_low |= _PAGE_SPECIAL;
	वापस pte;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pte_special(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_SPECIAL;
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_SPECIAL;
	वापस pte;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_ARCH_HAS_PTE_SPECIAL */

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
#अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)	अणु वापस pte.pte_low & _PAGE_WRITE; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)	अणु वापस pte.pte_low & _PAGE_MODIFIED; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte)	अणु वापस pte.pte_low & _PAGE_ACCESSED; पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte.pte_low  &= ~_PAGE_WRITE;
	अगर (!IS_ENABLED(CONFIG_XPA))
		pte.pte_low &= ~_PAGE_SILENT_WRITE;
	pte.pte_high &= ~_PAGE_SILENT_WRITE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte.pte_low  &= ~_PAGE_MODIFIED;
	अगर (!IS_ENABLED(CONFIG_XPA))
		pte.pte_low &= ~_PAGE_SILENT_WRITE;
	pte.pte_high &= ~_PAGE_SILENT_WRITE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte.pte_low  &= ~_PAGE_ACCESSED;
	अगर (!IS_ENABLED(CONFIG_XPA))
		pte.pte_low &= ~_PAGE_SILENT_READ;
	pte.pte_high &= ~_PAGE_SILENT_READ;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte.pte_low |= _PAGE_WRITE;
	अगर (pte.pte_low & _PAGE_MODIFIED) अणु
		अगर (!IS_ENABLED(CONFIG_XPA))
			pte.pte_low |= _PAGE_SILENT_WRITE;
		pte.pte_high |= _PAGE_SILENT_WRITE;
	पूर्ण
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte.pte_low |= _PAGE_MODIFIED;
	अगर (pte.pte_low & _PAGE_WRITE) अणु
		अगर (!IS_ENABLED(CONFIG_XPA))
			pte.pte_low |= _PAGE_SILENT_WRITE;
		pte.pte_high |= _PAGE_SILENT_WRITE;
	पूर्ण
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	pte.pte_low |= _PAGE_ACCESSED;
	अगर (!(pte.pte_low & _PAGE_NO_READ)) अणु
		अगर (!IS_ENABLED(CONFIG_XPA))
			pte.pte_low |= _PAGE_SILENT_READ;
		pte.pte_high |= _PAGE_SILENT_READ;
	पूर्ण
	वापस pte;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)	अणु वापस pte_val(pte) & _PAGE_WRITE; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)	अणु वापस pte_val(pte) & _PAGE_MODIFIED; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte)	अणु वापस pte_val(pte) & _PAGE_ACCESSED; पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_WRITE | _PAGE_SILENT_WRITE);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_MODIFIED | _PAGE_SILENT_WRITE);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_ACCESSED | _PAGE_SILENT_READ);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_WRITE;
	अगर (pte_val(pte) & _PAGE_MODIFIED)
		pte_val(pte) |= _PAGE_SILENT_WRITE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_MODIFIED | _PAGE_SOFT_सूचीTY;
	अगर (pte_val(pte) & _PAGE_WRITE)
		pte_val(pte) |= _PAGE_SILENT_WRITE;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_ACCESSED;
	अगर (!(pte_val(pte) & _PAGE_NO_READ))
		pte_val(pte) |= _PAGE_SILENT_READ;
	वापस pte;
पूर्ण

#घोषणा pte_sw_mkyoung	pte_mkyoung

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
अटल अंतरभूत पूर्णांक pte_huge(pte_t pte)	अणु वापस pte_val(pte) & _PAGE_HUGE; पूर्ण

अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_HUGE;
	वापस pte;
पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_HUGE_TLB_SUPPORT */

#अगर_घोषित CONFIG_HAVE_ARCH_SOFT_सूचीTY
अटल अंतरभूत bool pte_soft_dirty(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_SOFT_सूचीTY;
पूर्ण
#घोषणा pte_swp_soft_dirty pte_soft_dirty

अटल अंतरभूत pte_t pte_mksoft_dirty(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_SOFT_सूचीTY;
	वापस pte;
पूर्ण
#घोषणा pte_swp_mksoft_dirty pte_mksoft_dirty

अटल अंतरभूत pte_t pte_clear_soft_dirty(pte_t pte)
अणु
	pte_val(pte) &= ~(_PAGE_SOFT_सूचीTY);
	वापस pte;
पूर्ण
#घोषणा pte_swp_clear_soft_dirty pte_clear_soft_dirty

#पूर्ण_अगर /* CONFIG_HAVE_ARCH_SOFT_सूचीTY */

#पूर्ण_अगर

/*
 * Macro to make mark a page protection value as "uncacheable".	 Note
 * that "protection" is really a misnomer here as the protection value
 * contains the memory attribute bits, dirty bits, and various other
 * bits as well.
 */
#घोषणा pgprot_noncached pgprot_noncached

अटल अंतरभूत pgprot_t pgprot_noncached(pgprot_t _prot)
अणु
	अचिन्हित दीर्घ prot = pgprot_val(_prot);

	prot = (prot & ~_CACHE_MASK) | _CACHE_UNCACHED;

	वापस __pgprot(prot);
पूर्ण

#घोषणा pgprot_ग_लिखोcombine pgprot_ग_लिखोcombine

अटल अंतरभूत pgprot_t pgprot_ग_लिखोcombine(pgprot_t _prot)
अणु
	अचिन्हित दीर्घ prot = pgprot_val(_prot);

	/* cpu_data[0].ग_लिखोcombine is alपढ़ोy shअगरted by _CACHE_SHIFT */
	prot = (prot & ~_CACHE_MASK) | cpu_data[0].ग_लिखोcombine;

	वापस __pgprot(prot);
पूर्ण

अटल अंतरभूत व्योम flush_tlb_fix_spurious_fault(काष्ठा vm_area_काष्ठा *vma,
						अचिन्हित दीर्घ address)
अणु
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
अटल अंतरभूत पूर्णांक pte_same(pte_t pte_a, pte_t pte_b)
अणु
	वापस pte_val(pte_a) == pte_val(pte_b);
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
अटल अंतरभूत पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address, pte_t *ptep,
					pte_t entry, पूर्णांक dirty)
अणु
	अगर (!pte_same(*ptep, entry))
		set_pte_at(vma->vm_mm, address, ptep, entry);
	/*
	 * update_mmu_cache will unconditionally execute, handling both
	 * the हाल that the PTE changed and the spurious fault हाल.
	 */
	वापस true;
पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा mk_pte(page, pgprot)	pfn_pte(page_to_pfn(page), (pgprot))

#अगर defined(CONFIG_XPA)
अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte.pte_low  &= (_PAGE_MODIFIED | _PAGE_ACCESSED | _PFNX_MASK);
	pte.pte_high &= (_PFN_MASK | _CACHE_MASK);
	pte.pte_low  |= pgprot_val(newprot) & ~_PFNX_MASK;
	pte.pte_high |= pgprot_val(newprot) & ~(_PFN_MASK | _CACHE_MASK);
	वापस pte;
पूर्ण
#या_अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)
अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte.pte_low  &= _PAGE_CHG_MASK;
	pte.pte_high &= (_PFN_MASK | _CACHE_MASK);
	pte.pte_low  |= pgprot_val(newprot);
	pte.pte_high |= pgprot_val(newprot) & ~(_PFN_MASK | _CACHE_MASK);
	वापस pte;
पूर्ण
#अन्यथा
अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte_val(pte) &= _PAGE_CHG_MASK;
	pte_val(pte) |= pgprot_val(newprot) & ~_PAGE_CHG_MASK;
	अगर ((pte_val(pte) & _PAGE_ACCESSED) && !(pte_val(pte) & _PAGE_NO_READ))
		pte_val(pte) |= _PAGE_SILENT_READ;
	वापस pte;
पूर्ण
#पूर्ण_अगर


बाह्य व्योम __update_tlb(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
	pte_t pte);

अटल अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	pte_t pte = *ptep;
	__update_tlb(vma, address, pte);
पूर्ण

#घोषणा	__HAVE_ARCH_UPDATE_MMU_TLB
#घोषणा update_mmu_tlb	update_mmu_cache

अटल अंतरभूत व्योम update_mmu_cache_pmd(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	pte_t pte = *(pte_t *)pmdp;

	__update_tlb(vma, address, pte);
पूर्ण

#घोषणा kern_addr_valid(addr)	(1)

/*
 * Allow physical addresses to be fixed up to help 36-bit peripherals.
 */
#अगर_घोषित CONFIG_MIPS_FIXUP_BIGPHYS_ADDR
phys_addr_t fixup_bigphys_addr(phys_addr_t addr, phys_addr_t size);
पूर्णांक io_remap_pfn_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vaddr,
		अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot);
#घोषणा io_remap_pfn_range io_remap_pfn_range
#अन्यथा
#घोषणा fixup_bigphys_addr(addr, size)	(addr)
#पूर्ण_अगर /* CONFIG_MIPS_FIXUP_BIGPHYS_ADDR */

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

/* We करोn't have hardware dirty/accessed bits, generic_pmdp_establish is fine.*/
#घोषणा pmdp_establish generic_pmdp_establish

#घोषणा has_transparent_hugepage has_transparent_hugepage
बाह्य पूर्णांक has_transparent_hugepage(व्योम);

अटल अंतरभूत पूर्णांक pmd_trans_huge(pmd_t pmd)
अणु
	वापस !!(pmd_val(pmd) & _PAGE_HUGE);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkhuge(pmd_t pmd)
अणु
	pmd_val(pmd) |= _PAGE_HUGE;

	वापस pmd;
पूर्ण

बाह्य व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		       pmd_t *pmdp, pmd_t pmd);

#घोषणा pmd_ग_लिखो pmd_ग_लिखो
अटल अंतरभूत पूर्णांक pmd_ग_लिखो(pmd_t pmd)
अणु
	वापस !!(pmd_val(pmd) & _PAGE_WRITE);
पूर्ण

अटल अंतरभूत pmd_t pmd_wrprotect(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~(_PAGE_WRITE | _PAGE_SILENT_WRITE);
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkग_लिखो(pmd_t pmd)
अणु
	pmd_val(pmd) |= _PAGE_WRITE;
	अगर (pmd_val(pmd) & _PAGE_MODIFIED)
		pmd_val(pmd) |= _PAGE_SILENT_WRITE;

	वापस pmd;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_dirty(pmd_t pmd)
अणु
	वापस !!(pmd_val(pmd) & _PAGE_MODIFIED);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkclean(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~(_PAGE_MODIFIED | _PAGE_SILENT_WRITE);
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_सूची_गढ़ोty(pmd_t pmd)
अणु
	pmd_val(pmd) |= _PAGE_MODIFIED | _PAGE_SOFT_सूचीTY;
	अगर (pmd_val(pmd) & _PAGE_WRITE)
		pmd_val(pmd) |= _PAGE_SILENT_WRITE;

	वापस pmd;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_young(pmd_t pmd)
अणु
	वापस !!(pmd_val(pmd) & _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkold(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~(_PAGE_ACCESSED|_PAGE_SILENT_READ);

	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkyoung(pmd_t pmd)
अणु
	pmd_val(pmd) |= _PAGE_ACCESSED;

	अगर (!(pmd_val(pmd) & _PAGE_NO_READ))
		pmd_val(pmd) |= _PAGE_SILENT_READ;

	वापस pmd;
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_SOFT_सूचीTY
अटल अंतरभूत पूर्णांक pmd_soft_dirty(pmd_t pmd)
अणु
	वापस !!(pmd_val(pmd) & _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pmd_t pmd_mksoft_dirty(pmd_t pmd)
अणु
	pmd_val(pmd) |= _PAGE_SOFT_सूचीTY;
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_clear_soft_dirty(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~(_PAGE_SOFT_सूचीTY);
	वापस pmd;
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_ARCH_SOFT_सूचीTY */

/* Extern to aव्योम header file madness */
बाह्य pmd_t mk_pmd(काष्ठा page *page, pgprot_t prot);

अटल अंतरभूत अचिन्हित दीर्घ pmd_pfn(pmd_t pmd)
अणु
	वापस pmd_val(pmd) >> _PFN_SHIFT;
पूर्ण

अटल अंतरभूत काष्ठा page *pmd_page(pmd_t pmd)
अणु
	अगर (pmd_trans_huge(pmd))
		वापस pfn_to_page(pmd_pfn(pmd));

	वापस pfn_to_page(pmd_phys(pmd) >> PAGE_SHIFT);
पूर्ण

अटल अंतरभूत pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot)
अणु
	pmd_val(pmd) = (pmd_val(pmd) & (_PAGE_CHG_MASK | _PAGE_HUGE)) |
		       (pgprot_val(newprot) & ~_PAGE_CHG_MASK);
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkinvalid(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~(_PAGE_PRESENT | _PAGE_VALID | _PAGE_सूचीTY);

	वापस pmd;
पूर्ण

/*
 * The generic version pmdp_huge_get_and_clear uses a version of pmd_clear() with a
 * dअगरferent prototype.
 */
#घोषणा __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	pmd_t old = *pmdp;

	pmd_clear(pmdp);

	वापस old;
पूर्ण

#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अगर_घोषित _PAGE_HUGE
#घोषणा pmd_leaf(pmd)	((pmd_val(pmd) & _PAGE_HUGE) != 0)
#घोषणा pud_leaf(pud)	((pud_val(pud) & _PAGE_HUGE) != 0)
#पूर्ण_अगर

#घोषणा gup_fast_permitted(start, end)	(!cpu_has_dc_aliases)

/*
 * We provide our own get_unmapped area to cope with the भव aliasing
 * स्थिरraपूर्णांकs placed on us by the cache architecture.
 */
#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

#पूर्ण_अगर /* _ASM_PGTABLE_H */
