<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PGTABLE_H
#घोषणा _LINUX_PGTABLE_H

#समावेश <linux/pfn.h>
#समावेश <यंत्र/pgtable.h>

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_MMU

#समावेश <linux/mm_types.h>
#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र-generic/pgtable_uffd.h>

#अगर 5 - defined(__PAGETABLE_P4D_FOLDED) - defined(__PAGETABLE_PUD_FOLDED) - \
	defined(__PAGETABLE_PMD_FOLDED) != CONFIG_PGTABLE_LEVELS
#त्रुटि CONFIG_PGTABLE_LEVELS is not consistent with __PAGETABLE_अणुP4D,PUD,PMDपूर्ण_FOLDED
#पूर्ण_अगर

/*
 * On almost all architectures and configurations, 0 can be used as the
 * upper उच्चमानing to मुक्त_pgtables(): on many architectures it has the same
 * effect as using TASK_SIZE.  However, there is one configuration which
 * must impose a more careful limit, to aव्योम मुक्तing kernel pgtables.
 */
#अगर_अघोषित USER_PGTABLES_CEILING
#घोषणा USER_PGTABLES_CEILING	0UL
#पूर्ण_अगर

/*
 * A page table page can be thought of an array like this: pXd_t[PTRS_PER_PxD]
 *
 * The pXx_index() functions वापस the index of the entry in the page
 * table page which would control the given भव address
 *
 * As these functions may be used by the same code क्रम dअगरferent levels of
 * the page table folding, they are always available, regardless of
 * CONFIG_PGTABLE_LEVELS value. For the folded levels they simply वापस 0
 * because in such हालs PTRS_PER_PxD equals 1.
 */

अटल अंतरभूत अचिन्हित दीर्घ pte_index(अचिन्हित दीर्घ address)
अणु
	वापस (address >> PAGE_SHIFT) & (PTRS_PER_PTE - 1);
पूर्ण

#अगर_अघोषित pmd_index
अटल अंतरभूत अचिन्हित दीर्घ pmd_index(अचिन्हित दीर्घ address)
अणु
	वापस (address >> PMD_SHIFT) & (PTRS_PER_PMD - 1);
पूर्ण
#घोषणा pmd_index pmd_index
#पूर्ण_अगर

#अगर_अघोषित pud_index
अटल अंतरभूत अचिन्हित दीर्घ pud_index(अचिन्हित दीर्घ address)
अणु
	वापस (address >> PUD_SHIFT) & (PTRS_PER_PUD - 1);
पूर्ण
#घोषणा pud_index pud_index
#पूर्ण_अगर

#अगर_अघोषित pgd_index
/* Must be a compile-समय स्थिरant, so implement it as a macro */
#घोषणा pgd_index(a)  (((a) >> PGसूची_SHIFT) & (PTRS_PER_PGD - 1))
#पूर्ण_अगर

#अगर_अघोषित pte_offset_kernel
अटल अंतरभूत pte_t *pte_offset_kernel(pmd_t *pmd, अचिन्हित दीर्घ address)
अणु
	वापस (pte_t *)pmd_page_vaddr(*pmd) + pte_index(address);
पूर्ण
#घोषणा pte_offset_kernel pte_offset_kernel
#पूर्ण_अगर

#अगर defined(CONFIG_HIGHPTE)
#घोषणा pte_offset_map(dir, address)				\
	((pte_t *)kmap_atomic(pmd_page(*(dir))) +		\
	 pte_index((address)))
#घोषणा pte_unmap(pte) kunmap_atomic((pte))
#अन्यथा
#घोषणा pte_offset_map(dir, address)	pte_offset_kernel((dir), (address))
#घोषणा pte_unmap(pte) ((व्योम)(pte))	/* NOP */
#पूर्ण_अगर

/* Find an entry in the second-level page table.. */
#अगर_अघोषित pmd_offset
अटल अंतरभूत pmd_t *pmd_offset(pud_t *pud, अचिन्हित दीर्घ address)
अणु
	वापस (pmd_t *)pud_page_vaddr(*pud) + pmd_index(address);
पूर्ण
#घोषणा pmd_offset pmd_offset
#पूर्ण_अगर

#अगर_अघोषित pud_offset
अटल अंतरभूत pud_t *pud_offset(p4d_t *p4d, अचिन्हित दीर्घ address)
अणु
	वापस (pud_t *)p4d_page_vaddr(*p4d) + pud_index(address);
पूर्ण
#घोषणा pud_offset pud_offset
#पूर्ण_अगर

अटल अंतरभूत pgd_t *pgd_offset_pgd(pgd_t *pgd, अचिन्हित दीर्घ address)
अणु
	वापस (pgd + pgd_index(address));
पूर्ण;

/*
 * a लघुcut to get a pgd_t in a given mm
 */
#अगर_अघोषित pgd_offset
#घोषणा pgd_offset(mm, address)		pgd_offset_pgd((mm)->pgd, (address))
#पूर्ण_अगर

/*
 * a लघुcut which implies the use of the kernel's pgd, instead
 * of a process's
 */
#अगर_अघोषित pgd_offset_k
#घोषणा pgd_offset_k(address)		pgd_offset(&init_mm, (address))
#पूर्ण_अगर

/*
 * In many हालs it is known that a भव address is mapped at PMD or PTE
 * level, so instead of traversing all the page table levels, we can get a
 * poपूर्णांकer to the PMD entry in user or kernel page table or translate a भव
 * address to the poपूर्णांकer in the PTE in the kernel page tables with simple
 * helpers.
 */
अटल अंतरभूत pmd_t *pmd_off(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ va)
अणु
	वापस pmd_offset(pud_offset(p4d_offset(pgd_offset(mm, va), va), va), va);
पूर्ण

अटल अंतरभूत pmd_t *pmd_off_k(अचिन्हित दीर्घ va)
अणु
	वापस pmd_offset(pud_offset(p4d_offset(pgd_offset_k(va), va), va), va);
पूर्ण

अटल अंतरभूत pte_t *virt_to_kpte(अचिन्हित दीर्घ vaddr)
अणु
	pmd_t *pmd = pmd_off_k(vaddr);

	वापस pmd_none(*pmd) ? शून्य : pte_offset_kernel(pmd, vaddr);
पूर्ण

#अगर_अघोषित __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
बाह्य पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pte_t *ptep,
				 pte_t entry, पूर्णांक dirty);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_SET_ACCESS_FLAGS
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pmd_t *pmdp,
				 pmd_t entry, पूर्णांक dirty);
बाह्य पूर्णांक pudp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pud_t *pudp,
				 pud_t entry, पूर्णांक dirty);
#अन्यथा
अटल अंतरभूत पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address, pmd_t *pmdp,
					pmd_t entry, पूर्णांक dirty)
अणु
	BUILD_BUG();
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pudp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address, pud_t *pudp,
					pud_t entry, पूर्णांक dirty)
अणु
	BUILD_BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ address,
					    pte_t *ptep)
अणु
	pte_t pte = *ptep;
	पूर्णांक r = 1;
	अगर (!pte_young(pte))
		r = 0;
	अन्यथा
		set_pte_at(vma->vm_mm, address, ptep, pte_mkold(pte));
	वापस r;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_TEST_AND_CLEAR_YOUNG
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत पूर्णांक pmdp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ address,
					    pmd_t *pmdp)
अणु
	pmd_t pmd = *pmdp;
	पूर्णांक r = 1;
	अगर (!pmd_young(pmd))
		r = 0;
	अन्यथा
		set_pmd_at(vma->vm_mm, address, pmdp, pmd_mkold(pmd));
	वापस r;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pmdp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ address,
					    pmd_t *pmdp)
अणु
	BUILD_BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
पूर्णांक ptep_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ address, pte_t *ptep);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_CLEAR_YOUNG_FLUSH
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य पूर्णांक pmdp_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ address, pmd_t *pmdp);
#अन्यथा
/*
 * Despite relevant to THP only, this API is called from generic rmap code
 * under PageTransHuge(), hence needs a dummy implementation क्रम !THP
 */
अटल अंतरभूत पूर्णांक pmdp_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	BUILD_BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ address,
				       pte_t *ptep)
अणु
	pte_t pte = *ptep;
	pte_clear(mm, address, ptep);
	वापस pte;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTEP_GET
अटल अंतरभूत pte_t ptep_get(pte_t *ptep)
अणु
	वापस READ_ONCE(*ptep);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_GUP_GET_PTE_LOW_HIGH
/*
 * WARNING: only to be used in the get_user_pages_fast() implementation.
 *
 * With get_user_pages_fast(), we walk करोwn the pagetables without taking any
 * locks.  For this we would like to load the poपूर्णांकers atomically, but someबार
 * that is not possible (e.g. without expensive cmpxchg8b on x86_32 PAE).  What
 * we करो have is the guarantee that a PTE will only either go from not present
 * to present, or present to not present or both -- it will not चयन to a
 * completely dअगरferent present page without a TLB flush in between; something
 * that we are blocking by holding पूर्णांकerrupts off.
 *
 * Setting ptes from not present to present goes:
 *
 *   ptep->pte_high = h;
 *   smp_wmb();
 *   ptep->pte_low = l;
 *
 * And present to not present goes:
 *
 *   ptep->pte_low = 0;
 *   smp_wmb();
 *   ptep->pte_high = 0;
 *
 * We must ensure here that the load of pte_low sees 'l' IFF pte_high sees 'h'.
 * We load pte_high *after* loading pte_low, which ensures we करोn't see an older
 * value of pte_high.  *Then* we recheck pte_low, which ensures that we haven't
 * picked up a changed pte high. We might have gotten rubbish values from
 * pte_low and pte_high, but we are guaranteed that pte_low will not have the
 * present bit set *unless* it is 'l'. Because get_user_pages_fast() only
 * operates on present ptes we're safe.
 */
अटल अंतरभूत pte_t ptep_get_lockless(pte_t *ptep)
अणु
	pte_t pte;

	करो अणु
		pte.pte_low = ptep->pte_low;
		smp_rmb();
		pte.pte_high = ptep->pte_high;
		smp_rmb();
	पूर्ण जबतक (unlikely(pte.pte_low != ptep->pte_low));

	वापस pte;
पूर्ण
#अन्यथा /* CONFIG_GUP_GET_PTE_LOW_HIGH */
/*
 * We require that the PTE can be पढ़ो atomically.
 */
अटल अंतरभूत pte_t ptep_get_lockless(pte_t *ptep)
अणु
	वापस ptep_get(ptep);
पूर्ण
#पूर्ण_अगर /* CONFIG_GUP_GET_PTE_LOW_HIGH */

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#अगर_अघोषित __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ address,
					    pmd_t *pmdp)
अणु
	pmd_t pmd = *pmdp;
	pmd_clear(pmdp);
	वापस pmd;
पूर्ण
#पूर्ण_अगर /* __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR */
#अगर_अघोषित __HAVE_ARCH_PUDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pud_t pudp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ address,
					    pud_t *pudp)
अणु
	pud_t pud = *pudp;

	pud_clear(pudp);
	वापस pud;
पूर्ण
#पूर्ण_अगर /* __HAVE_ARCH_PUDP_HUGE_GET_AND_CLEAR */
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#अगर_अघोषित __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR_FULL
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear_full(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ address, pmd_t *pmdp,
					    पूर्णांक full)
अणु
	वापस pmdp_huge_get_and_clear(vma->vm_mm, address, pmdp);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PUDP_HUGE_GET_AND_CLEAR_FULL
अटल अंतरभूत pud_t pudp_huge_get_and_clear_full(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ address, pud_t *pudp,
					    पूर्णांक full)
अणु
	वापस pudp_huge_get_and_clear(mm, address, pudp);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अगर_अघोषित __HAVE_ARCH_PTEP_GET_AND_CLEAR_FULL
अटल अंतरभूत pte_t ptep_get_and_clear_full(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ address, pte_t *ptep,
					    पूर्णांक full)
अणु
	pte_t pte;
	pte = ptep_get_and_clear(mm, address, ptep);
	वापस pte;
पूर्ण
#पूर्ण_अगर


/*
 * If two thपढ़ोs concurrently fault at the same page, the thपढ़ो that
 * won the race updates the PTE and its local TLB/Cache. The other thपढ़ो
 * gives up, simply करोes nothing, and जारीs; on architectures where
 * software can update TLB,  local TLB can be updated here to aव्योम next page
 * fault. This function updates TLB only, करो nothing with cache or others.
 * It is the dअगरference with function update_mmu_cache.
 */
#अगर_अघोषित __HAVE_ARCH_UPDATE_MMU_TLB
अटल अंतरभूत व्योम update_mmu_tlb(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ address, pte_t *ptep)
अणु
पूर्ण
#घोषणा __HAVE_ARCH_UPDATE_MMU_TLB
#पूर्ण_अगर

/*
 * Some architectures may be able to aव्योम expensive synchronization
 * primitives when modअगरications are made to PTE's which are alपढ़ोy
 * not present, or in the process of an address space deकाष्ठाion.
 */
#अगर_अघोषित __HAVE_ARCH_PTE_CLEAR_NOT_PRESENT_FULL
अटल अंतरभूत व्योम pte_clear_not_present_full(काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ address,
					      pte_t *ptep,
					      पूर्णांक full)
अणु
	pte_clear(mm, address, ptep);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTEP_CLEAR_FLUSH
बाह्य pte_t ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ address,
			      pte_t *ptep);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_HUGE_CLEAR_FLUSH
बाह्य pmd_t pmdp_huge_clear_flush(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ address,
			      pmd_t *pmdp);
बाह्य pud_t pudp_huge_clear_flush(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ address,
			      pud_t *pudp);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTEP_SET_WRPROTECT
काष्ठा mm_काष्ठा;
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	pte_t old_pte = *ptep;
	set_pte_at(mm, address, ptep, pte_wrprotect(old_pte));
पूर्ण
#पूर्ण_अगर

/*
 * On some architectures hardware करोes not set page access bit when accessing
 * memory page, it is responsibility of software setting this bit. It brings
 * out extra page fault penalty to track page access bit. For optimization page
 * access bit can be set during all page fault flow on these arches.
 * To be dअगरferentiate with macro pte_mkyoung, this macro is used on platक्रमms
 * where software मुख्यtains page access bit.
 */
#अगर_अघोषित pte_sw_mkyoung
अटल अंतरभूत pte_t pte_sw_mkyoung(pte_t pte)
अणु
	वापस pte;
पूर्ण
#घोषणा pte_sw_mkyoung	pte_sw_mkyoung
#पूर्ण_अगर

#अगर_अघोषित pte_savedग_लिखो
#घोषणा pte_savedग_लिखो pte_ग_लिखो
#पूर्ण_अगर

#अगर_अघोषित pte_mk_savedग_लिखो
#घोषणा pte_mk_savedग_लिखो pte_mkग_लिखो
#पूर्ण_अगर

#अगर_अघोषित pte_clear_savedग_लिखो
#घोषणा pte_clear_savedग_लिखो pte_wrprotect
#पूर्ण_अगर

#अगर_अघोषित pmd_savedग_लिखो
#घोषणा pmd_savedग_लिखो pmd_ग_लिखो
#पूर्ण_अगर

#अगर_अघोषित pmd_mk_savedग_लिखो
#घोषणा pmd_mk_savedग_लिखो pmd_mkग_लिखो
#पूर्ण_अगर

#अगर_अघोषित pmd_clear_savedग_लिखो
#घोषणा pmd_clear_savedग_लिखो pmd_wrprotect
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_SET_WRPROTECT
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत व्योम pmdp_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	pmd_t old_pmd = *pmdp;
	set_pmd_at(mm, address, pmdp, pmd_wrprotect(old_pmd));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pmdp_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	BUILD_BUG();
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
#पूर्ण_अगर
#अगर_अघोषित __HAVE_ARCH_PUDP_SET_WRPROTECT
#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल अंतरभूत व्योम pudp_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ address, pud_t *pudp)
अणु
	pud_t old_pud = *pudp;

	set_pud_at(mm, address, pudp, pud_wrprotect(old_pud));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pudp_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ address, pud_t *pudp)
अणु
	BUILD_BUG();
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */
#पूर्ण_अगर

#अगर_अघोषित pmdp_collapse_flush
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य pmd_t pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pmd_t *pmdp);
#अन्यथा
अटल अंतरभूत pmd_t pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address,
					pmd_t *pmdp)
अणु
	BUILD_BUG();
	वापस *pmdp;
पूर्ण
#घोषणा pmdp_collapse_flush pmdp_collapse_flush
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PGTABLE_DEPOSIT
बाह्य व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				       pgtable_t pgtable);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PGTABLE_WITHDRAW
बाह्य pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/*
 * This is an implementation of pmdp_establish() that is only suitable क्रम an
 * architecture that करोesn't have hardware dirty/accessed bits. In this हाल we
 * can't race with CPU which sets these bits and non-atomic approach is fine.
 */
अटल अंतरभूत pmd_t generic_pmdp_establish(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, pmd_t *pmdp, pmd_t pmd)
अणु
	pmd_t old_pmd = *pmdp;
	set_pmd_at(vma->vm_mm, address, pmdp, pmd);
	वापस old_pmd;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_INVALIDATE
बाह्य pmd_t pmdp_invalidate(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			    pmd_t *pmdp);
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTE_SAME
अटल अंतरभूत पूर्णांक pte_same(pte_t pte_a, pte_t pte_b)
अणु
	वापस pte_val(pte_a) == pte_val(pte_b);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTE_UNUSED
/*
 * Some architectures provide facilities to भवization guests
 * so that they can flag allocated pages as unused. This allows the
 * host to transparently reclaim unused pages. This function वापसs
 * whether the pte's page is unused.
 */
अटल अंतरभूत पूर्णांक pte_unused(pte_t pte)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित pte_access_permitted
#घोषणा pte_access_permitted(pte, ग_लिखो) \
	(pte_present(pte) && (!(ग_लिखो) || pte_ग_लिखो(pte)))
#पूर्ण_अगर

#अगर_अघोषित pmd_access_permitted
#घोषणा pmd_access_permitted(pmd, ग_लिखो) \
	(pmd_present(pmd) && (!(ग_लिखो) || pmd_ग_लिखो(pmd)))
#पूर्ण_अगर

#अगर_अघोषित pud_access_permitted
#घोषणा pud_access_permitted(pud, ग_लिखो) \
	(pud_present(pud) && (!(ग_लिखो) || pud_ग_लिखो(pud)))
#पूर्ण_अगर

#अगर_अघोषित p4d_access_permitted
#घोषणा p4d_access_permitted(p4d, ग_लिखो) \
	(p4d_present(p4d) && (!(ग_लिखो) || p4d_ग_लिखो(p4d)))
#पूर्ण_अगर

#अगर_अघोषित pgd_access_permitted
#घोषणा pgd_access_permitted(pgd, ग_लिखो) \
	(pgd_present(pgd) && (!(ग_लिखो) || pgd_ग_लिखो(pgd)))
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMD_SAME
अटल अंतरभूत पूर्णांक pmd_same(pmd_t pmd_a, pmd_t pmd_b)
अणु
	वापस pmd_val(pmd_a) == pmd_val(pmd_b);
पूर्ण

अटल अंतरभूत पूर्णांक pud_same(pud_t pud_a, pud_t pud_b)
अणु
	वापस pud_val(pud_a) == pud_val(pud_b);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_P4D_SAME
अटल अंतरभूत पूर्णांक p4d_same(p4d_t p4d_a, p4d_t p4d_b)
अणु
	वापस p4d_val(p4d_a) == p4d_val(p4d_b);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PGD_SAME
अटल अंतरभूत पूर्णांक pgd_same(pgd_t pgd_a, pgd_t pgd_b)
अणु
	वापस pgd_val(pgd_a) == pgd_val(pgd_b);
पूर्ण
#पूर्ण_अगर

/*
 * Use set_p*_safe(), and elide TLB flushing, when confident that *no*
 * TLB flush will be required as a result of the "set". For example, use
 * in scenarios where it is known ahead of समय that the routine is
 * setting non-present entries, or re-setting an existing entry to the
 * same value. Otherwise, use the typical "set" helpers and flush the
 * TLB.
 */
#घोषणा set_pte_safe(ptep, pte) \
(अणु \
	WARN_ON_ONCE(pte_present(*ptep) && !pte_same(*ptep, pte)); \
	set_pte(ptep, pte); \
पूर्ण)

#घोषणा set_pmd_safe(pmdp, pmd) \
(अणु \
	WARN_ON_ONCE(pmd_present(*pmdp) && !pmd_same(*pmdp, pmd)); \
	set_pmd(pmdp, pmd); \
पूर्ण)

#घोषणा set_pud_safe(pudp, pud) \
(अणु \
	WARN_ON_ONCE(pud_present(*pudp) && !pud_same(*pudp, pud)); \
	set_pud(pudp, pud); \
पूर्ण)

#घोषणा set_p4d_safe(p4dp, p4d) \
(अणु \
	WARN_ON_ONCE(p4d_present(*p4dp) && !p4d_same(*p4dp, p4d)); \
	set_p4d(p4dp, p4d); \
पूर्ण)

#घोषणा set_pgd_safe(pgdp, pgd) \
(अणु \
	WARN_ON_ONCE(pgd_present(*pgdp) && !pgd_same(*pgdp, pgd)); \
	set_pgd(pgdp, pgd); \
पूर्ण)

#अगर_अघोषित __HAVE_ARCH_DO_SWAP_PAGE
/*
 * Some architectures support metadata associated with a page. When a
 * page is being swapped out, this metadata must be saved so it can be
 * restored when the page is swapped back in. SPARC M7 and newer
 * processors support an ADI (Application Data Integrity) tag क्रम the
 * page as metadata क्रम the page. arch_करो_swap_page() can restore this
 * metadata when a page is swapped back in.
 */
अटल अंतरभूत व्योम arch_करो_swap_page(काष्ठा mm_काष्ठा *mm,
				     काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ addr,
				     pte_t pte, pte_t oldpte)
अणु

पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_UNMAP_ONE
/*
 * Some architectures support metadata associated with a page. When a
 * page is being swapped out, this metadata must be saved so it can be
 * restored when the page is swapped back in. SPARC M7 and newer
 * processors support an ADI (Application Data Integrity) tag क्रम the
 * page as metadata क्रम the page. arch_unmap_one() can save this
 * metadata on a swap-out of a page.
 */
अटल अंतरभूत पूर्णांक arch_unmap_one(काष्ठा mm_काष्ठा *mm,
				  काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ addr,
				  pte_t orig_pte)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Allow architectures to preserve additional metadata associated with
 * swapped-out pages. The corresponding __HAVE_ARCH_SWAP_* macros and function
 * prototypes must be defined in the arch-specअगरic यंत्र/pgtable.h file.
 */
#अगर_अघोषित __HAVE_ARCH_PREPARE_TO_SWAP
अटल अंतरभूत पूर्णांक arch_prepare_to_swap(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_SWAP_INVALIDATE
अटल अंतरभूत व्योम arch_swap_invalidate_page(पूर्णांक type, pgoff_t offset)
अणु
पूर्ण

अटल अंतरभूत व्योम arch_swap_invalidate_area(पूर्णांक type)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_SWAP_RESTORE
अटल अंतरभूत व्योम arch_swap_restore(swp_entry_t entry, काष्ठा page *page)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PGD_OFFSET_GATE
#घोषणा pgd_offset_gate(mm, addr)	pgd_offset(mm, addr)
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_MOVE_PTE
#घोषणा move_pte(pte, prot, old_addr, new_addr)	(pte)
#पूर्ण_अगर

#अगर_अघोषित pte_accessible
# define pte_accessible(mm, pte)	((व्योम)(pte), 1)
#पूर्ण_अगर

#अगर_अघोषित flush_tlb_fix_spurious_fault
#घोषणा flush_tlb_fix_spurious_fault(vma, address) flush_tlb_page(vma, address)
#पूर्ण_अगर

/*
 * When walking page tables, get the address of the next boundary,
 * or the end address of the range अगर that comes earlier.  Although no
 * vma end wraps to 0, rounded up __boundary may wrap to 0 throughout.
 */

#घोषणा pgd_addr_end(addr, end)						\
(अणु	अचिन्हित दीर्घ __boundary = ((addr) + PGसूची_SIZE) & PGसूची_MASK;	\
	(__boundary - 1 < (end) - 1)? __boundary: (end);		\
पूर्ण)

#अगर_अघोषित p4d_addr_end
#घोषणा p4d_addr_end(addr, end)						\
(अणु	अचिन्हित दीर्घ __boundary = ((addr) + P4D_SIZE) & P4D_MASK;	\
	(__boundary - 1 < (end) - 1)? __boundary: (end);		\
पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित pud_addr_end
#घोषणा pud_addr_end(addr, end)						\
(अणु	अचिन्हित दीर्घ __boundary = ((addr) + PUD_SIZE) & PUD_MASK;	\
	(__boundary - 1 < (end) - 1)? __boundary: (end);		\
पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित pmd_addr_end
#घोषणा pmd_addr_end(addr, end)						\
(अणु	अचिन्हित दीर्घ __boundary = ((addr) + PMD_SIZE) & PMD_MASK;	\
	(__boundary - 1 < (end) - 1)? __boundary: (end);		\
पूर्ण)
#पूर्ण_अगर

/*
 * When walking page tables, we usually want to skip any p?d_none entries;
 * and any p?d_bad entries - reporting the error beक्रमe resetting to none.
 * Do the tests अंतरभूत, but report and clear the bad entry in mm/memory.c.
 */
व्योम pgd_clear_bad(pgd_t *);

#अगर_अघोषित __PAGETABLE_P4D_FOLDED
व्योम p4d_clear_bad(p4d_t *);
#अन्यथा
#घोषणा p4d_clear_bad(p4d)        करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
व्योम pud_clear_bad(pud_t *);
#अन्यथा
#घोषणा pud_clear_bad(p4d)        करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

व्योम pmd_clear_bad(pmd_t *);

अटल अंतरभूत पूर्णांक pgd_none_or_clear_bad(pgd_t *pgd)
अणु
	अगर (pgd_none(*pgd))
		वापस 1;
	अगर (unlikely(pgd_bad(*pgd))) अणु
		pgd_clear_bad(pgd);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक p4d_none_or_clear_bad(p4d_t *p4d)
अणु
	अगर (p4d_none(*p4d))
		वापस 1;
	अगर (unlikely(p4d_bad(*p4d))) अणु
		p4d_clear_bad(p4d);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pud_none_or_clear_bad(pud_t *pud)
अणु
	अगर (pud_none(*pud))
		वापस 1;
	अगर (unlikely(pud_bad(*pud))) अणु
		pud_clear_bad(pud);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_none_or_clear_bad(pmd_t *pmd)
अणु
	अगर (pmd_none(*pmd))
		वापस 1;
	अगर (unlikely(pmd_bad(*pmd))) अणु
		pmd_clear_bad(pmd);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत pte_t __ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr,
					     pte_t *ptep)
अणु
	/*
	 * Get the current pte state, but zero it out to make it
	 * non-present, preventing the hardware from asynchronously
	 * updating it.
	 */
	वापस ptep_get_and_clear(vma->vm_mm, addr, ptep);
पूर्ण

अटल अंतरभूत व्योम __ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr,
					     pte_t *ptep, pte_t pte)
अणु
	/*
	 * The pte is non-present, so there's no hardware state to
	 * preserve.
	 */
	set_pte_at(vma->vm_mm, addr, ptep, pte);
पूर्ण

#अगर_अघोषित __HAVE_ARCH_PTEP_MODIFY_PROT_TRANSACTION
/*
 * Start a pte protection पढ़ो-modअगरy-ग_लिखो transaction, which
 * protects against asynchronous hardware modअगरications to the pte.
 * The पूर्णांकention is not to prevent the hardware from making pte
 * updates, but to prevent any updates it may make from being lost.
 *
 * This करोes not protect against other software modअगरications of the
 * pte; the appropriate pte lock must be held over the transaction.
 *
 * Note that this पूर्णांकerface is पूर्णांकended to be batchable, meaning that
 * ptep_modअगरy_prot_commit may not actually update the pte, but merely
 * queue the update to be करोne at some later समय.  The update must be
 * actually committed beक्रमe the pte lock is released, however.
 */
अटल अंतरभूत pte_t ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma,
					   अचिन्हित दीर्घ addr,
					   pte_t *ptep)
अणु
	वापस __ptep_modअगरy_prot_start(vma, addr, ptep);
पूर्ण

/*
 * Commit an update to a pte, leaving any hardware-controlled bits in
 * the PTE unmodअगरied.
 */
अटल अंतरभूत व्योम ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma,
					   अचिन्हित दीर्घ addr,
					   pte_t *ptep, pte_t old_pte, pte_t pte)
अणु
	__ptep_modअगरy_prot_commit(vma, addr, ptep, pte);
पूर्ण
#पूर्ण_अगर /* __HAVE_ARCH_PTEP_MODIFY_PROT_TRANSACTION */
#पूर्ण_अगर /* CONFIG_MMU */

/*
 * No-op macros that just वापस the current protection value. Defined here
 * because these macros can be used even अगर CONFIG_MMU is not defined.
 */

#अगर_अघोषित pgprot_nx
#घोषणा pgprot_nx(prot)	(prot)
#पूर्ण_अगर

#अगर_अघोषित pgprot_noncached
#घोषणा pgprot_noncached(prot)	(prot)
#पूर्ण_अगर

#अगर_अघोषित pgprot_ग_लिखोcombine
#घोषणा pgprot_ग_लिखोcombine pgprot_noncached
#पूर्ण_अगर

#अगर_अघोषित pgprot_ग_लिखोthrough
#घोषणा pgprot_ग_लिखोthrough pgprot_noncached
#पूर्ण_अगर

#अगर_अघोषित pgprot_device
#घोषणा pgprot_device pgprot_noncached
#पूर्ण_अगर

#अगर_अघोषित pgprot_mhp
#घोषणा pgprot_mhp(prot)	(prot)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
#अगर_अघोषित pgprot_modअगरy
#घोषणा pgprot_modअगरy pgprot_modअगरy
अटल अंतरभूत pgprot_t pgprot_modअगरy(pgprot_t oldprot, pgprot_t newprot)
अणु
	अगर (pgprot_val(oldprot) == pgprot_val(pgprot_noncached(oldprot)))
		newprot = pgprot_noncached(newprot);
	अगर (pgprot_val(oldprot) == pgprot_val(pgprot_ग_लिखोcombine(oldprot)))
		newprot = pgprot_ग_लिखोcombine(newprot);
	अगर (pgprot_val(oldprot) == pgprot_val(pgprot_device(oldprot)))
		newprot = pgprot_device(newprot);
	वापस newprot;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_MMU */

#अगर_अघोषित pgprot_encrypted
#घोषणा pgprot_encrypted(prot)	(prot)
#पूर्ण_अगर

#अगर_अघोषित pgprot_decrypted
#घोषणा pgprot_decrypted(prot)	(prot)
#पूर्ण_अगर

/*
 * A facility to provide lazy MMU batching.  This allows PTE updates and
 * page invalidations to be delayed until a call to leave lazy MMU mode
 * is issued.  Some architectures may benefit from करोing this, and it is
 * beneficial क्रम both shaकरोw and direct mode hypervisors, which may batch
 * the PTE updates which happen during this winकरोw.  Note that using this
 * पूर्णांकerface requires that पढ़ो hazards be हटाओd from the code.  A पढ़ो
 * hazard could result in the direct mode hypervisor हाल, since the actual
 * ग_लिखो to the page tables may not yet have taken place, so पढ़ोs though
 * a raw PTE poपूर्णांकer after it has been modअगरied are not guaranteed to be
 * up to date.  This mode can only be entered and left under the protection of
 * the page table locks क्रम all page tables which may be modअगरied.  In the UP
 * हाल, this is required so that preemption is disabled, and in the SMP हाल,
 * it must synchronize the delayed page table ग_लिखोs properly on other CPUs.
 */
#अगर_अघोषित __HAVE_ARCH_ENTER_LAZY_MMU_MODE
#घोषणा arch_enter_lazy_mmu_mode()	करो अणुपूर्ण जबतक (0)
#घोषणा arch_leave_lazy_mmu_mode()	करो अणुपूर्ण जबतक (0)
#घोषणा arch_flush_lazy_mmu_mode()	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * A facility to provide batching of the reload of page tables and
 * other process state with the actual context चयन code क्रम
 * paraभवized guests.  By convention, only one of the batched
 * update (lazy) modes (CPU, MMU) should be active at any given समय,
 * entry should never be nested, and entry and निकासs should always be
 * paired.  This is क्रम sanity of मुख्यtaining and reasoning about the
 * kernel code.  In this हाल, the निकास (end of the context चयन) is
 * in architecture-specअगरic code, and so करोesn't need a generic
 * definition.
 */
#अगर_अघोषित __HAVE_ARCH_START_CONTEXT_SWITCH
#घोषणा arch_start_context_चयन(prev)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_SOFT_सूचीTY
#अगर_अघोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
अटल अंतरभूत pmd_t pmd_swp_mksoft_dirty(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_swp_soft_dirty(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत pmd_t pmd_swp_clear_soft_dirty(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण
#पूर्ण_अगर
#अन्यथा /* !CONFIG_HAVE_ARCH_SOFT_सूचीTY */
अटल अंतरभूत पूर्णांक pte_soft_dirty(pte_t pte)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_soft_dirty(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत pte_t pte_mksoft_dirty(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल अंतरभूत pmd_t pmd_mksoft_dirty(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण

अटल अंतरभूत pte_t pte_clear_soft_dirty(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल अंतरभूत pmd_t pmd_clear_soft_dirty(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण

अटल अंतरभूत pte_t pte_swp_mksoft_dirty(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल अंतरभूत पूर्णांक pte_swp_soft_dirty(pte_t pte)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत pte_t pte_swp_clear_soft_dirty(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल अंतरभूत pmd_t pmd_swp_mksoft_dirty(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_swp_soft_dirty(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत pmd_t pmd_swp_clear_soft_dirty(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_PFNMAP_TRACKING
/*
 * Interfaces that can be used by architecture code to keep track of
 * memory type of pfn mappings specअगरied by the remap_pfn_range,
 * vmf_insert_pfn.
 */

/*
 * track_pfn_remap is called when a _new_ pfn mapping is being established
 * by remap_pfn_range() क्रम physical range indicated by pfn and size.
 */
अटल अंतरभूत पूर्णांक track_pfn_remap(काष्ठा vm_area_काष्ठा *vma, pgprot_t *prot,
				  अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ size)
अणु
	वापस 0;
पूर्ण

/*
 * track_pfn_insert is called when a _new_ single pfn is established
 * by vmf_insert_pfn().
 */
अटल अंतरभूत व्योम track_pfn_insert(काष्ठा vm_area_काष्ठा *vma, pgprot_t *prot,
				    pfn_t pfn)
अणु
पूर्ण

/*
 * track_pfn_copy is called when vma that is covering the pfnmap माला_लो
 * copied through copy_page_range().
 */
अटल अंतरभूत पूर्णांक track_pfn_copy(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस 0;
पूर्ण

/*
 * untrack_pfn is called जबतक unmapping a pfnmap क्रम a region.
 * untrack can be called क्रम a specअगरic region indicated by pfn and size or
 * can be क्रम the entire vma (in which हाल pfn, size are zero).
 */
अटल अंतरभूत व्योम untrack_pfn(काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size)
अणु
पूर्ण

/*
 * untrack_pfn_moved is called जबतक mremapping a pfnmap क्रम a new region.
 */
अटल अंतरभूत व्योम untrack_pfn_moved(काष्ठा vm_area_काष्ठा *vma)
अणु
पूर्ण
#अन्यथा
बाह्य पूर्णांक track_pfn_remap(काष्ठा vm_area_काष्ठा *vma, pgprot_t *prot,
			   अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ size);
बाह्य व्योम track_pfn_insert(काष्ठा vm_area_काष्ठा *vma, pgprot_t *prot,
			     pfn_t pfn);
बाह्य पूर्णांक track_pfn_copy(काष्ठा vm_area_काष्ठा *vma);
बाह्य व्योम untrack_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ pfn,
			अचिन्हित दीर्घ size);
बाह्य व्योम untrack_pfn_moved(काष्ठा vm_area_काष्ठा *vma);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
#अगर_घोषित __HAVE_COLOR_ZERO_PAGE
अटल अंतरभूत पूर्णांक is_zero_pfn(अचिन्हित दीर्घ pfn)
अणु
	बाह्य अचिन्हित दीर्घ zero_pfn;
	अचिन्हित दीर्घ offset_from_zero_pfn = pfn - zero_pfn;
	वापस offset_from_zero_pfn <= (zero_page_mask >> PAGE_SHIFT);
पूर्ण

#घोषणा my_zero_pfn(addr)	page_to_pfn(ZERO_PAGE(addr))

#अन्यथा
अटल अंतरभूत पूर्णांक is_zero_pfn(अचिन्हित दीर्घ pfn)
अणु
	बाह्य अचिन्हित दीर्घ zero_pfn;
	वापस pfn == zero_pfn;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ my_zero_pfn(अचिन्हित दीर्घ addr)
अणु
	बाह्य अचिन्हित दीर्घ zero_pfn;
	वापस zero_pfn;
पूर्ण
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत पूर्णांक is_zero_pfn(अचिन्हित दीर्घ pfn)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ my_zero_pfn(अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

#अगर_घोषित CONFIG_MMU

#अगर_अघोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत पूर्णांक pmd_trans_huge(pmd_t pmd)
अणु
	वापस 0;
पूर्ण
#अगर_अघोषित pmd_ग_लिखो
अटल अंतरभूत पूर्णांक pmd_ग_लिखो(pmd_t pmd)
अणु
	BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* pmd_ग_लिखो */
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अगर_अघोषित pud_ग_लिखो
अटल अंतरभूत पूर्णांक pud_ग_लिखो(pud_t pud)
अणु
	BUG();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* pud_ग_लिखो */

#अगर !defined(CONFIG_ARCH_HAS_PTE_DEVMAP) || !defined(CONFIG_TRANSPARENT_HUGEPAGE)
अटल अंतरभूत पूर्णांक pmd_devmap(pmd_t pmd)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pud_devmap(pud_t pud)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pgd_devmap(pgd_t pgd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर !defined(CONFIG_TRANSPARENT_HUGEPAGE) || \
	(defined(CONFIG_TRANSPARENT_HUGEPAGE) && \
	 !defined(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD))
अटल अंतरभूत पूर्णांक pud_trans_huge(pud_t pud)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* See pmd_none_or_trans_huge_or_clear_bad क्रम discussion. */
अटल अंतरभूत पूर्णांक pud_none_or_trans_huge_or_dev_or_clear_bad(pud_t *pud)
अणु
	pud_t pudval = READ_ONCE(*pud);

	अगर (pud_none(pudval) || pud_trans_huge(pudval) || pud_devmap(pudval))
		वापस 1;
	अगर (unlikely(pud_bad(pudval))) अणु
		pud_clear_bad(pud);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* See pmd_trans_unstable क्रम discussion. */
अटल अंतरभूत पूर्णांक pud_trans_unstable(pud_t *pud)
अणु
#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) &&			\
	defined(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD)
	वापस pud_none_or_trans_huge_or_dev_or_clear_bad(pud);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर_अघोषित pmd_पढ़ो_atomic
अटल अंतरभूत pmd_t pmd_पढ़ो_atomic(pmd_t *pmdp)
अणु
	/*
	 * Depend on compiler क्रम an atomic pmd पढ़ो. NOTE: this is
	 * only going to work, अगर the pmdval_t isn't larger than
	 * an अचिन्हित दीर्घ.
	 */
	वापस *pmdp;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_needs_pgtable_deposit
#घोषणा arch_needs_pgtable_deposit() (false)
#पूर्ण_अगर
/*
 * This function is meant to be used by sites walking pagetables with
 * the mmap_lock held in पढ़ो mode to protect against MADV_DONTNEED and
 * transhuge page faults. MADV_DONTNEED can convert a transhuge pmd
 * पूर्णांकo a null pmd and the transhuge page fault can convert a null pmd
 * पूर्णांकo an hugepmd or पूर्णांकo a regular pmd (अगर the hugepage allocation
 * fails). While holding the mmap_lock in पढ़ो mode the pmd becomes
 * stable and stops changing under us only अगर it's not null and not a
 * transhuge pmd. When those races occurs and this function makes a
 * dअगरference vs the standard pmd_none_or_clear_bad, the result is
 * undefined so behaving like अगर the pmd was none is safe (because it
 * can वापस none anyway). The compiler level barrier() is critically
 * important to compute the two checks atomically on the same pmdval.
 *
 * For 32bit kernels with a 64bit large pmd_t this स्वतःmatically takes
 * care of पढ़ोing the pmd atomically to aव्योम SMP race conditions
 * against pmd_populate() when the mmap_lock is hold क्रम पढ़ोing by the
 * caller (a special atomic पढ़ो not करोne by "gcc" as in the generic
 * version above, is also needed when THP is disabled because the page
 * fault can populate the pmd from under us).
 */
अटल अंतरभूत पूर्णांक pmd_none_or_trans_huge_or_clear_bad(pmd_t *pmd)
अणु
	pmd_t pmdval = pmd_पढ़ो_atomic(pmd);
	/*
	 * The barrier will stabilize the pmdval in a रेजिस्टर or on
	 * the stack so that it will stop changing under the code.
	 *
	 * When CONFIG_TRANSPARENT_HUGEPAGE=y on x86 32bit PAE,
	 * pmd_पढ़ो_atomic is allowed to वापस a not atomic pmdval
	 * (क्रम example poपूर्णांकing to an hugepage that has never been
	 * mapped in the pmd). The below checks will only care about
	 * the low part of the pmd with 32bit PAE x86 anyway, with the
	 * exception of pmd_none(). So the important thing is that अगर
	 * the low part of the pmd is found null, the high part will
	 * be also null or the pmd_none() check below would be
	 * confused.
	 */
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	barrier();
#पूर्ण_अगर
	/*
	 * !pmd_present() checks क्रम pmd migration entries
	 *
	 * The complete check uses is_pmd_migration_entry() in linux/swapops.h
	 * But using that requires moving current function and pmd_trans_unstable()
	 * to linux/swapops.h to resolve dependency, which is too much code move.
	 *
	 * !pmd_present() is equivalent to is_pmd_migration_entry() currently,
	 * because !pmd_present() pages can only be under migration not swapped
	 * out.
	 *
	 * pmd_none() is preserved क्रम future condition checks on pmd migration
	 * entries and not confusing with this function name, although it is
	 * redundant with !pmd_present().
	 */
	अगर (pmd_none(pmdval) || pmd_trans_huge(pmdval) ||
		(IS_ENABLED(CONFIG_ARCH_ENABLE_THP_MIGRATION) && !pmd_present(pmdval)))
		वापस 1;
	अगर (unlikely(pmd_bad(pmdval))) अणु
		pmd_clear_bad(pmd);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This is a noop अगर Transparent Hugepage Support is not built पूर्णांकo
 * the kernel. Otherwise it is equivalent to
 * pmd_none_or_trans_huge_or_clear_bad(), and shall only be called in
 * places that alपढ़ोy verअगरied the pmd is not none and they want to
 * walk ptes जबतक holding the mmap sem in पढ़ो mode (ग_लिखो mode करोn't
 * need this). If THP is not enabled, the pmd can't go away under the
 * code even अगर MADV_DONTNEED runs, but अगर THP is enabled we need to
 * run a pmd_trans_unstable beक्रमe walking the ptes after
 * split_huge_pmd वापसs (because it may have run when the pmd become
 * null, but then a page fault can map in a THP and not a regular page).
 */
अटल अंतरभूत पूर्णांक pmd_trans_unstable(pmd_t *pmd)
अणु
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	वापस pmd_none_or_trans_huge_or_clear_bad(pmd);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * the ordering of these checks is important क्रम pmds with _page_devmap set.
 * अगर we check pmd_trans_unstable() first we will trip the bad_pmd() check
 * inside of pmd_none_or_trans_huge_or_clear_bad(). this will end up correctly
 * वापसing 1 but not beक्रमe it spams dmesg with the pmd_clear_bad() output.
 */
अटल अंतरभूत पूर्णांक pmd_devmap_trans_unstable(pmd_t *pmd)
अणु
	वापस pmd_devmap(*pmd) || pmd_trans_unstable(pmd);
पूर्ण

#अगर_अघोषित CONFIG_NUMA_BALANCING
/*
 * Technically a PTE can be PROTNONE even when not करोing NUMA balancing but
 * the only हाल the kernel cares is क्रम NUMA balancing and is only ever set
 * when the VMA is accessible. For PROT_NONE VMAs, the PTEs are not marked
 * _PAGE_PROTNONE so by शेष, implement the helper as "always no". It
 * is the responsibility of the caller to distinguish between PROT_NONE
 * protections and NUMA hपूर्णांकing fault protections.
 */
अटल अंतरभूत पूर्णांक pte_protnone(pte_t pte)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_protnone(pmd_t pmd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#पूर्ण_अगर /* CONFIG_MMU */

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMAP

#अगर_अघोषित __PAGETABLE_P4D_FOLDED
पूर्णांक p4d_set_huge(p4d_t *p4d, phys_addr_t addr, pgprot_t prot);
पूर्णांक p4d_clear_huge(p4d_t *p4d);
#अन्यथा
अटल अंतरभूत पूर्णांक p4d_set_huge(p4d_t *p4d, phys_addr_t addr, pgprot_t prot)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक p4d_clear_huge(p4d_t *p4d)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !__PAGETABLE_P4D_FOLDED */

पूर्णांक pud_set_huge(pud_t *pud, phys_addr_t addr, pgprot_t prot);
पूर्णांक pmd_set_huge(pmd_t *pmd, phys_addr_t addr, pgprot_t prot);
पूर्णांक pud_clear_huge(pud_t *pud);
पूर्णांक pmd_clear_huge(pmd_t *pmd);
पूर्णांक p4d_मुक्त_pud_page(p4d_t *p4d, अचिन्हित दीर्घ addr);
पूर्णांक pud_मुक्त_pmd_page(pud_t *pud, अचिन्हित दीर्घ addr);
पूर्णांक pmd_मुक्त_pte_page(pmd_t *pmd, अचिन्हित दीर्घ addr);
#अन्यथा	/* !CONFIG_HAVE_ARCH_HUGE_VMAP */
अटल अंतरभूत पूर्णांक p4d_set_huge(p4d_t *p4d, phys_addr_t addr, pgprot_t prot)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pud_set_huge(pud_t *pud, phys_addr_t addr, pgprot_t prot)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pmd_set_huge(pmd_t *pmd, phys_addr_t addr, pgprot_t prot)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक p4d_clear_huge(p4d_t *p4d)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pud_clear_huge(pud_t *pud)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pmd_clear_huge(pmd_t *pmd)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक p4d_मुक्त_pud_page(p4d_t *p4d, अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pud_मुक्त_pmd_page(pud_t *pud, अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक pmd_मुक्त_pte_page(pmd_t *pmd, अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_HAVE_ARCH_HUGE_VMAP */

#अगर_अघोषित __HAVE_ARCH_FLUSH_PMD_TLB_RANGE
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/*
 * ARCHes with special requirements क्रम evicting THP backing TLB entries can
 * implement this. Otherwise also, it can help optimize normal TLB flush in
 * THP regime. Stock flush_tlb_range() typically has optimization to nuke the
 * entire TLB अगर flush span is greater than a threshold, which will
 * likely be true क्रम a single huge page. Thus a single THP flush will
 * invalidate the entire TLB which is not desirable.
 * e.g. see arch/arc: flush_pmd_tlb_range
 */
#घोषणा flush_pmd_tlb_range(vma, addr, end)	flush_tlb_range(vma, addr, end)
#घोषणा flush_pud_tlb_range(vma, addr, end)	flush_tlb_range(vma, addr, end)
#अन्यथा
#घोषणा flush_pmd_tlb_range(vma, addr, end)	BUILD_BUG()
#घोषणा flush_pud_tlb_range(vma, addr, end)	BUILD_BUG()
#पूर्ण_अगर
#पूर्ण_अगर

काष्ठा file;
पूर्णांक phys_mem_access_prot_allowed(काष्ठा file *file, अचिन्हित दीर्घ pfn,
			अचिन्हित दीर्घ size, pgprot_t *vma_prot);

#अगर_अघोषित CONFIG_X86_ESPFIX64
अटल अंतरभूत व्योम init_espfix_bsp(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम __init pgtable_cache_init(व्योम);

#अगर_अघोषित __HAVE_ARCH_PFN_MODIFY_ALLOWED
अटल अंतरभूत bool pfn_modअगरy_allowed(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool arch_has_pfn_modअगरy_check(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* !_HAVE_ARCH_PFN_MODIFY_ALLOWED */

/*
 * Architecture PAGE_KERNEL_* fallbacks
 *
 * Some architectures करोn't define certain PAGE_KERNEL_* flags. This is either
 * because they really करोn't support them, or the port needs to be updated to
 * reflect the required functionality. Below are a set of relatively safe
 * fallbacks, as best efक्रमt, which we can count on in lieu of the architectures
 * not defining them on their own yet.
 */

#अगर_अघोषित PAGE_KERNEL_RO
# define PAGE_KERNEL_RO PAGE_KERNEL
#पूर्ण_अगर

#अगर_अघोषित PAGE_KERNEL_EXEC
# define PAGE_KERNEL_EXEC PAGE_KERNEL
#पूर्ण_अगर

/*
 * Page Table Modअगरication bits क्रम pgtbl_mod_mask.
 *
 * These are used by the p?d_alloc_track*() set of functions an in the generic
 * vदो_स्मृति/ioremap code to track at which page-table levels entries have been
 * modअगरied. Based on that the code can better decide when vदो_स्मृति and ioremap
 * mapping changes need to be synchronized to other page-tables in the प्रणाली.
 */
#घोषणा		__PGTBL_PGD_MODIFIED	0
#घोषणा		__PGTBL_P4D_MODIFIED	1
#घोषणा		__PGTBL_PUD_MODIFIED	2
#घोषणा		__PGTBL_PMD_MODIFIED	3
#घोषणा		__PGTBL_PTE_MODIFIED	4

#घोषणा		PGTBL_PGD_MODIFIED	BIT(__PGTBL_PGD_MODIFIED)
#घोषणा		PGTBL_P4D_MODIFIED	BIT(__PGTBL_P4D_MODIFIED)
#घोषणा		PGTBL_PUD_MODIFIED	BIT(__PGTBL_PUD_MODIFIED)
#घोषणा		PGTBL_PMD_MODIFIED	BIT(__PGTBL_PMD_MODIFIED)
#घोषणा		PGTBL_PTE_MODIFIED	BIT(__PGTBL_PTE_MODIFIED)

/* Page-Table Modअगरication Mask */
प्रकार अचिन्हित पूर्णांक pgtbl_mod_mask;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर !defined(MAX_POSSIBLE_PHYSMEM_BITS) && !defined(CONFIG_64BIT)
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
/*
 * ZSMALLOC needs to know the highest PFN on 32-bit architectures
 * with physical address space extension, but falls back to
 * BITS_PER_LONG otherwise.
 */
#त्रुटि Missing MAX_POSSIBLE_PHYSMEM_BITS definition
#अन्यथा
#घोषणा MAX_POSSIBLE_PHYSMEM_BITS 32
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित has_transparent_hugepage
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा has_transparent_hugepage() 1
#अन्यथा
#घोषणा has_transparent_hugepage() 0
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * On some architectures it depends on the mm अगर the p4d/pud or pmd
 * layer of the page table hierarchy is folded or not.
 */
#अगर_अघोषित mm_p4d_folded
#घोषणा mm_p4d_folded(mm)	__is_defined(__PAGETABLE_P4D_FOLDED)
#पूर्ण_अगर

#अगर_अघोषित mm_pud_folded
#घोषणा mm_pud_folded(mm)	__is_defined(__PAGETABLE_PUD_FOLDED)
#पूर्ण_अगर

#अगर_अघोषित mm_pmd_folded
#घोषणा mm_pmd_folded(mm)	__is_defined(__PAGETABLE_PMD_FOLDED)
#पूर्ण_अगर

#अगर_अघोषित p4d_offset_lockless
#घोषणा p4d_offset_lockless(pgdp, pgd, address) p4d_offset(&(pgd), address)
#पूर्ण_अगर
#अगर_अघोषित pud_offset_lockless
#घोषणा pud_offset_lockless(p4dp, p4d, address) pud_offset(&(p4d), address)
#पूर्ण_अगर
#अगर_अघोषित pmd_offset_lockless
#घोषणा pmd_offset_lockless(pudp, pud, address) pmd_offset(&(pud), address)
#पूर्ण_अगर

/*
 * p?d_leaf() - true अगर this entry is a final mapping to a physical address.
 * This dअगरfers from p?d_huge() by the fact that they are always available (अगर
 * the architecture supports large pages at the appropriate level) even
 * अगर CONFIG_HUGETLB_PAGE is not defined.
 * Only meaningful when called on a valid entry.
 */
#अगर_अघोषित pgd_leaf
#घोषणा pgd_leaf(x)	0
#पूर्ण_अगर
#अगर_अघोषित p4d_leaf
#घोषणा p4d_leaf(x)	0
#पूर्ण_अगर
#अगर_अघोषित pud_leaf
#घोषणा pud_leaf(x)	0
#पूर्ण_अगर
#अगर_अघोषित pmd_leaf
#घोषणा pmd_leaf(x)	0
#पूर्ण_अगर

#अगर_अघोषित pgd_leaf_size
#घोषणा pgd_leaf_size(x) (1ULL << PGसूची_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित p4d_leaf_size
#घोषणा p4d_leaf_size(x) P4D_SIZE
#पूर्ण_अगर
#अगर_अघोषित pud_leaf_size
#घोषणा pud_leaf_size(x) PUD_SIZE
#पूर्ण_अगर
#अगर_अघोषित pmd_leaf_size
#घोषणा pmd_leaf_size(x) PMD_SIZE
#पूर्ण_अगर
#अगर_अघोषित pte_leaf_size
#घोषणा pte_leaf_size(x) PAGE_SIZE
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_PGTABLE_H */
