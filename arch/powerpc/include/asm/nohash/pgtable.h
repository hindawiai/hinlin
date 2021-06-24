<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_PGTABLE_H
#घोषणा _ASM_POWERPC_NOHASH_PGTABLE_H

#अगर defined(CONFIG_PPC64)
#समावेश <यंत्र/nohash/64/pgtable.h>
#अन्यथा
#समावेश <यंत्र/nohash/32/pgtable.h>
#पूर्ण_अगर

/* Permission masks used क्रम kernel mappings */
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RW)
#घोषणा PAGE_KERNEL_NC	__pgprot(_PAGE_BASE_NC | _PAGE_KERNEL_RW | _PAGE_NO_CACHE)
#घोषणा PAGE_KERNEL_NCG	__pgprot(_PAGE_BASE_NC | _PAGE_KERNEL_RW | \
				 _PAGE_NO_CACHE | _PAGE_GUARDED)
#घोषणा PAGE_KERNEL_X	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RWX)
#घोषणा PAGE_KERNEL_RO	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RO)
#घोषणा PAGE_KERNEL_ROX	__pgprot(_PAGE_BASE | _PAGE_KERNEL_ROX)

/*
 * Protection used क्रम kernel text. We want the debuggers to be able to
 * set अवरोधpoपूर्णांकs anywhere, so करोn't ग_लिखो protect the kernel text
 * on platक्रमms where such control is possible.
 */
#अगर defined(CONFIG_KGDB) || defined(CONFIG_XMON) || defined(CONFIG_BDI_SWITCH) ||\
	defined(CONFIG_KPROBES) || defined(CONFIG_DYNAMIC_FTRACE)
#घोषणा PAGE_KERNEL_TEXT	PAGE_KERNEL_X
#अन्यथा
#घोषणा PAGE_KERNEL_TEXT	PAGE_KERNEL_ROX
#पूर्ण_अगर

/* Make modules code happy. We करोn't set RO yet */
#घोषणा PAGE_KERNEL_EXEC	PAGE_KERNEL_X

/* Advertise special mapping type क्रम AGP */
#घोषणा PAGE_AGP		(PAGE_KERNEL_NC)
#घोषणा HAVE_PAGE_AGP

#अगर_अघोषित __ASSEMBLY__

/* Generic accessors to PTE bits */
#अगर_अघोषित pte_ग_लिखो
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_RW;
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)		अणु वापस 1; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_सूचीTY; पूर्ण
अटल अंतरभूत पूर्णांक pte_special(pte_t pte)	अणु वापस pte_val(pte) & _PAGE_SPECIAL; पूर्ण
अटल अंतरभूत पूर्णांक pte_none(pte_t pte)		अणु वापस (pte_val(pte) & ~_PTE_NONE_MASK) == 0; पूर्ण
अटल अंतरभूत bool pte_hashpte(pte_t pte)	अणु वापस false; पूर्ण
अटल अंतरभूत bool pte_ci(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_NO_CACHE; पूर्ण
अटल अंतरभूत bool pte_exec(pte_t pte)		अणु वापस pte_val(pte) & _PAGE_EXEC; पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
/*
 * These work without NUMA balancing but the kernel करोes not care. See the
 * comment in include/linux/pgtable.h . On घातerpc, this will only
 * work क्रम user pages and always वापस true क्रम kernel pages.
 */
अटल अंतरभूत पूर्णांक pte_protnone(pte_t pte)
अणु
	वापस pte_present(pte) && !pte_user(pte);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_protnone(pmd_t pmd)
अणु
	वापस pte_protnone(pmd_pte(pmd));
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

अटल अंतरभूत पूर्णांक pte_present(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_PRESENT;
पूर्ण

अटल अंतरभूत bool pte_hw_valid(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_PRESENT;
पूर्ण

/*
 * Don't just check क्रम any non zero bits in __PAGE_USER, since क्रम book3e
 * and PTE_64BIT, PAGE_KERNEL_X contains _PAGE_BAP_SR which is also in
 * _PAGE_USER.  Need to explicitly match _PAGE_BAP_UR bit in that हाल too.
 */
#अगर_अघोषित pte_user
अटल अंतरभूत bool pte_user(pte_t pte)
अणु
	वापस (pte_val(pte) & _PAGE_USER) == _PAGE_USER;
पूर्ण
#पूर्ण_अगर

/*
 * We only find page table entry in the last level
 * Hence no need क्रम other accessors
 */
#घोषणा pte_access_permitted pte_access_permitted
अटल अंतरभूत bool pte_access_permitted(pte_t pte, bool ग_लिखो)
अणु
	/*
	 * A पढ़ो-only access is controlled by _PAGE_USER bit.
	 * We have _PAGE_READ set क्रम WRITE and EXECUTE
	 */
	अगर (!pte_present(pte) || !pte_user(pte) || !pte_पढ़ो(pte))
		वापस false;

	अगर (ग_लिखो && !pte_ग_लिखो(pte))
		वापस false;

	वापस true;
पूर्ण

/* Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 *
 * Even अगर PTEs can be अचिन्हित दीर्घ दीर्घ, a PFN is always an अचिन्हित
 * दीर्घ क्रम now.
 */
अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ pfn, pgprot_t pgprot) अणु
	वापस __pte(((pte_basic_t)(pfn) << PTE_RPN_SHIFT) |
		     pgprot_val(pgprot)); पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ pte_pfn(pte_t pte)	अणु
	वापस pte_val(pte) >> PTE_RPN_SHIFT; पूर्ण

/* Generic modअगरiers क्रम PTE bits */
अटल अंतरभूत pte_t pte_exprotect(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_EXEC);
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_SPECIAL);
पूर्ण

#अगर_अघोषित pte_mkhuge
अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	वापस __pte(pte_val(pte));
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित pte_mkprivileged
अटल अंतरभूत pte_t pte_mkprivileged(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_USER);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित pte_mkuser
अटल अंतरभूत pte_t pte_mkuser(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_USER);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस __pte((pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot));
पूर्ण

/* Insert a PTE, top-level function is out of line. It uses an अंतरभूत
 * low level function in the respective pgtable-* files
 */
बाह्य व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep,
		       pte_t pte);

/* This low level function perक्रमms the actual PTE insertion
 * Setting the PTE depends on the MMU type and other factors. It's
 * an horrible mess that I'm not going to try to clean up now but
 * I'm keeping it in one place rather than spपढ़ो around
 */
अटल अंतरभूत व्योम __set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				pte_t *ptep, pte_t pte, पूर्णांक percpu)
अणु
	/* Second हाल is 32-bit with 64-bit PTE.  In this हाल, we
	 * can just store as दीर्घ as we करो the two halves in the right order
	 * with a barrier in between.
	 * In the percpu हाल, we also fallback to the simple update
	 */
	अगर (IS_ENABLED(CONFIG_PPC32) && IS_ENABLED(CONFIG_PTE_64BIT) && !percpu) अणु
		__यंत्र__ __अस्थिर__("\
			stw%X0 %2,%0\न\
			eieio\न\
			stw%X1 %L2,%1"
		: "=m" (*ptep), "=m" (*((अचिन्हित अक्षर *)ptep+4))
		: "r" (pte) : "memory");
		वापस;
	पूर्ण
	/* Anything अन्यथा just stores the PTE normally. That covers all 64-bit
	 * हालs, and 32-bit non-hash with 32-bit PTEs.
	 */
#अगर defined(CONFIG_PPC_8xx) && defined(CONFIG_PPC_16K_PAGES)
	ptep->pte = ptep->pte1 = ptep->pte2 = ptep->pte3 = pte_val(pte);
#अन्यथा
	*ptep = pte;
#पूर्ण_अगर

	/*
	 * With hardware tablewalk, a sync is needed to ensure that
	 * subsequent accesses see the PTE we just wrote.  Unlike userspace
	 * mappings, we can't tolerate spurious faults, so make sure
	 * the new PTE will be seen the first समय.
	 */
	अगर (IS_ENABLED(CONFIG_PPC_BOOK3E_64) && is_kernel_addr(addr))
		mb();
पूर्ण


#घोषणा __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
बाह्य पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
				 pte_t *ptep, pte_t entry, पूर्णांक dirty);

/*
 * Macro to mark a page protection value as "uncacheable".
 */

#घोषणा _PAGE_CACHE_CTL	(_PAGE_COHERENT | _PAGE_GUARDED | _PAGE_NO_CACHE | \
			 _PAGE_WRITETHRU)

#घोषणा pgprot_noncached(prot)	  (__pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) | \
				            _PAGE_NO_CACHE | _PAGE_GUARDED))

#घोषणा pgprot_noncached_wc(prot) (__pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) | \
				            _PAGE_NO_CACHE))

#घोषणा pgprot_cached(prot)       (__pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) | \
				            _PAGE_COHERENT))

#अगर _PAGE_WRITETHRU != 0
#घोषणा pgprot_cached_wthru(prot) (__pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) | \
				            _PAGE_COHERENT | _PAGE_WRITETHRU))
#अन्यथा
#घोषणा pgprot_cached_wthru(prot)	pgprot_noncached(prot)
#पूर्ण_अगर

#घोषणा pgprot_cached_noncoherent(prot) \
		(__pgprot(pgprot_val(prot) & ~_PAGE_CACHE_CTL))

#घोषणा pgprot_ग_लिखोcombine pgprot_noncached_wc

काष्ठा file;
बाह्य pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t vma_prot);
#घोषणा __HAVE_PHYS_MEM_ACCESS_PROT

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल अंतरभूत पूर्णांक hugepd_ok(hugepd_t hpd)
अणु
#अगर_घोषित CONFIG_PPC_8xx
	वापस ((hpd_val(hpd) & _PMD_PAGE_MASK) == _PMD_PAGE_8M);
#अन्यथा
	/* We clear the top bit to indicate hugepd */
	वापस (hpd_val(hpd) && (hpd_val(hpd) & PD_HUGE) == 0);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pud_huge(pud_t pud)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pgd_huge(pgd_t pgd)
अणु
	वापस 0;
पूर्ण
#घोषणा pgd_huge		pgd_huge

#घोषणा is_hugepd(hpd)		(hugepd_ok(hpd))
#पूर्ण_अगर

/*
 * This माला_लो called at the end of handling a page fault, when
 * the kernel has put a new PTE पूर्णांकo the page table क्रम the process.
 * We use it to ensure coherency between the i-cache and d-cache
 * क्रम the page which has just been mapped in.
 */
#अगर defined(CONFIG_PPC_FSL_BOOK3E) && defined(CONFIG_HUGETLB_PAGE)
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t *ptep);
#अन्यथा
अटल अंतरभूत
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t *ptep) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर
