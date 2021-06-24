<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  mm/pgtable-generic.c
 *
 *  Generic pgtable methods declared in linux/pgtable.h
 *
 *  Copyright (C) 2010  Linus Torvalds
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/tlb.h>

/*
 * If a p?d_bad entry is found जबतक walking page tables, report
 * the error, beक्रमe resetting entry to p?d_none.  Usually (but
 * very selकरोm) called out from the p?d_none_or_clear_bad macros.
 */

व्योम pgd_clear_bad(pgd_t *pgd)
अणु
	pgd_ERROR(*pgd);
	pgd_clear(pgd);
पूर्ण

#अगर_अघोषित __PAGETABLE_P4D_FOLDED
व्योम p4d_clear_bad(p4d_t *p4d)
अणु
	p4d_ERROR(*p4d);
	p4d_clear(p4d);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
व्योम pud_clear_bad(pud_t *pud)
अणु
	pud_ERROR(*pud);
	pud_clear(pud);
पूर्ण
#पूर्ण_अगर

/*
 * Note that the pmd variant below can't be stub'ed out just as क्रम p4d/pud
 * above. pmd folding is special and typically pmd_* macros refer to upper
 * level even when folded
 */
व्योम pmd_clear_bad(pmd_t *pmd)
अणु
	pmd_ERROR(*pmd);
	pmd_clear(pmd);
पूर्ण

#अगर_अघोषित __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
/*
 * Only sets the access flags (dirty, accessed), as well as ग_लिखो
 * permission. Furthermore, we know it always माला_लो set to a "more
 * permissive" setting, which allows most architectures to optimize
 * this. We वापस whether the PTE actually changed, which in turn
 * inकाष्ठाs the caller to करो things like update__mmu_cache.  This
 * used to be करोne in the caller, but sparc needs minor faults to
 * क्रमce that call on sun4c so we changed this macro slightly
 */
पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
			  अचिन्हित दीर्घ address, pte_t *ptep,
			  pte_t entry, पूर्णांक dirty)
अणु
	पूर्णांक changed = !pte_same(*ptep, entry);
	अगर (changed) अणु
		set_pte_at(vma->vm_mm, address, ptep, entry);
		flush_tlb_fix_spurious_fault(vma, address);
	पूर्ण
	वापस changed;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
पूर्णांक ptep_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	पूर्णांक young;
	young = ptep_test_and_clear_young(vma, address, ptep);
	अगर (young)
		flush_tlb_page(vma, address);
	वापस young;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PTEP_CLEAR_FLUSH
pte_t ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		       pte_t *ptep)
अणु
	काष्ठा mm_काष्ठा *mm = (vma)->vm_mm;
	pte_t pte;
	pte = ptep_get_and_clear(mm, address, ptep);
	अगर (pte_accessible(mm, pte))
		flush_tlb_page(vma, address);
	वापस pte;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

#अगर_अघोषित __HAVE_ARCH_PMDP_SET_ACCESS_FLAGS
पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
			  अचिन्हित दीर्घ address, pmd_t *pmdp,
			  pmd_t entry, पूर्णांक dirty)
अणु
	पूर्णांक changed = !pmd_same(*pmdp, entry);
	VM_BUG_ON(address & ~HPAGE_PMD_MASK);
	अगर (changed) अणु
		set_pmd_at(vma->vm_mm, address, pmdp, entry);
		flush_pmd_tlb_range(vma, address, address + HPAGE_PMD_SIZE);
	पूर्ण
	वापस changed;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_CLEAR_YOUNG_FLUSH
पूर्णांक pmdp_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	पूर्णांक young;
	VM_BUG_ON(address & ~HPAGE_PMD_MASK);
	young = pmdp_test_and_clear_young(vma, address, pmdp);
	अगर (young)
		flush_pmd_tlb_range(vma, address, address + HPAGE_PMD_SIZE);
	वापस young;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_HUGE_CLEAR_FLUSH
pmd_t pmdp_huge_clear_flush(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			    pmd_t *pmdp)
अणु
	pmd_t pmd;
	VM_BUG_ON(address & ~HPAGE_PMD_MASK);
	VM_BUG_ON(pmd_present(*pmdp) && !pmd_trans_huge(*pmdp) &&
			   !pmd_devmap(*pmdp));
	pmd = pmdp_huge_get_and_clear(vma->vm_mm, address, pmdp);
	flush_pmd_tlb_range(vma, address, address + HPAGE_PMD_SIZE);
	वापस pmd;
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
pud_t pudp_huge_clear_flush(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			    pud_t *pudp)
अणु
	pud_t pud;

	VM_BUG_ON(address & ~HPAGE_PUD_MASK);
	VM_BUG_ON(!pud_trans_huge(*pudp) && !pud_devmap(*pudp));
	pud = pudp_huge_get_and_clear(vma->vm_mm, address, pudp);
	flush_pud_tlb_range(vma, address, address + HPAGE_PUD_SIZE);
	वापस pud;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PGTABLE_DEPOSIT
व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				pgtable_t pgtable)
अणु
	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));

	/* FIFO */
	अगर (!pmd_huge_pte(mm, pmdp))
		INIT_LIST_HEAD(&pgtable->lru);
	अन्यथा
		list_add(&pgtable->lru, &pmd_huge_pte(mm, pmdp)->lru);
	pmd_huge_pte(mm, pmdp) = pgtable;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PGTABLE_WITHDRAW
/* no "address" argument so destroys page coloring of some arch */
pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp)
अणु
	pgtable_t pgtable;

	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));

	/* FIFO */
	pgtable = pmd_huge_pte(mm, pmdp);
	pmd_huge_pte(mm, pmdp) = list_first_entry_or_null(&pgtable->lru,
							  काष्ठा page, lru);
	अगर (pmd_huge_pte(mm, pmdp))
		list_del(&pgtable->lru);
	वापस pgtable;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PMDP_INVALIDATE
pmd_t pmdp_invalidate(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		     pmd_t *pmdp)
अणु
	pmd_t old = pmdp_establish(vma, address, pmdp, pmd_mkinvalid(*pmdp));
	flush_pmd_tlb_range(vma, address, address + HPAGE_PMD_SIZE);
	वापस old;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित pmdp_collapse_flush
pmd_t pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			  pmd_t *pmdp)
अणु
	/*
	 * pmd and hugepage pte क्रमmat are same. So we could
	 * use the same function.
	 */
	pmd_t pmd;

	VM_BUG_ON(address & ~HPAGE_PMD_MASK);
	VM_BUG_ON(pmd_trans_huge(*pmdp));
	pmd = pmdp_huge_get_and_clear(vma->vm_mm, address, pmdp);

	/* collapse entails shooting करोwn ptes not pmd */
	flush_tlb_range(vma, address, address + HPAGE_PMD_SIZE);
	वापस pmd;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
