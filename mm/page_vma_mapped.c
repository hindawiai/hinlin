<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <linux/rmap.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>

#समावेश "internal.h"

अटल अंतरभूत bool not_found(काष्ठा page_vma_mapped_walk *pvmw)
अणु
	page_vma_mapped_walk_करोne(pvmw);
	वापस false;
पूर्ण

अटल bool map_pte(काष्ठा page_vma_mapped_walk *pvmw)
अणु
	pvmw->pte = pte_offset_map(pvmw->pmd, pvmw->address);
	अगर (!(pvmw->flags & PVMW_SYNC)) अणु
		अगर (pvmw->flags & PVMW_MIGRATION) अणु
			अगर (!is_swap_pte(*pvmw->pte))
				वापस false;
		पूर्ण अन्यथा अणु
			/*
			 * We get here when we are trying to unmap a निजी
			 * device page from the process address space. Such
			 * page is not CPU accessible and thus is mapped as
			 * a special swap entry, nonetheless it still करोes
			 * count as a valid regular mapping क्रम the page (and
			 * is accounted as such in page maps count).
			 *
			 * So handle this special हाल as अगर it was a normal
			 * page mapping ie lock CPU page table and वापसs
			 * true.
			 *
			 * For more details on device निजी memory see HMM
			 * (include/linux/hmm.h or mm/hmm.c).
			 */
			अगर (is_swap_pte(*pvmw->pte)) अणु
				swp_entry_t entry;

				/* Handle un-addressable ZONE_DEVICE memory */
				entry = pte_to_swp_entry(*pvmw->pte);
				अगर (!is_device_निजी_entry(entry))
					वापस false;
			पूर्ण अन्यथा अगर (!pte_present(*pvmw->pte))
				वापस false;
		पूर्ण
	पूर्ण
	pvmw->ptl = pte_lockptr(pvmw->vma->vm_mm, pvmw->pmd);
	spin_lock(pvmw->ptl);
	वापस true;
पूर्ण

अटल अंतरभूत bool pfn_is_match(काष्ठा page *page, अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ page_pfn = page_to_pfn(page);

	/* normal page and hugetlbfs page */
	अगर (!PageTransCompound(page) || PageHuge(page))
		वापस page_pfn == pfn;

	/* THP can be referenced by any subpage */
	वापस pfn >= page_pfn && pfn - page_pfn < thp_nr_pages(page);
पूर्ण

/**
 * check_pte - check अगर @pvmw->page is mapped at the @pvmw->pte
 * @pvmw: page_vma_mapped_walk काष्ठा, includes a pair pte and page क्रम checking
 *
 * page_vma_mapped_walk() found a place where @pvmw->page is *potentially*
 * mapped. check_pte() has to validate this.
 *
 * pvmw->pte may poपूर्णांक to empty PTE, swap PTE or PTE poपूर्णांकing to
 * arbitrary page.
 *
 * If PVMW_MIGRATION flag is set, वापसs true अगर @pvmw->pte contains migration
 * entry that poपूर्णांकs to @pvmw->page or any subpage in हाल of THP.
 *
 * If PVMW_MIGRATION flag is not set, वापसs true अगर pvmw->pte poपूर्णांकs to
 * pvmw->page or any subpage in हाल of THP.
 *
 * Otherwise, वापस false.
 *
 */
अटल bool check_pte(काष्ठा page_vma_mapped_walk *pvmw)
अणु
	अचिन्हित दीर्घ pfn;

	अगर (pvmw->flags & PVMW_MIGRATION) अणु
		swp_entry_t entry;
		अगर (!is_swap_pte(*pvmw->pte))
			वापस false;
		entry = pte_to_swp_entry(*pvmw->pte);

		अगर (!is_migration_entry(entry))
			वापस false;

		pfn = migration_entry_to_pfn(entry);
	पूर्ण अन्यथा अगर (is_swap_pte(*pvmw->pte)) अणु
		swp_entry_t entry;

		/* Handle un-addressable ZONE_DEVICE memory */
		entry = pte_to_swp_entry(*pvmw->pte);
		अगर (!is_device_निजी_entry(entry))
			वापस false;

		pfn = device_निजी_entry_to_pfn(entry);
	पूर्ण अन्यथा अणु
		अगर (!pte_present(*pvmw->pte))
			वापस false;

		pfn = pte_pfn(*pvmw->pte);
	पूर्ण

	वापस pfn_is_match(pvmw->page, pfn);
पूर्ण

/**
 * page_vma_mapped_walk - check अगर @pvmw->page is mapped in @pvmw->vma at
 * @pvmw->address
 * @pvmw: poपूर्णांकer to काष्ठा page_vma_mapped_walk. page, vma, address and flags
 * must be set. pmd, pte and ptl must be शून्य.
 *
 * Returns true अगर the page is mapped in the vma. @pvmw->pmd and @pvmw->pte poपूर्णांक
 * to relevant page table entries. @pvmw->ptl is locked. @pvmw->address is
 * adjusted अगर needed (क्रम PTE-mapped THPs).
 *
 * If @pvmw->pmd is set but @pvmw->pte is not, you have found PMD-mapped page
 * (usually THP). For PTE-mapped THP, you should run page_vma_mapped_walk() in
 * a loop to find all PTEs that map the THP.
 *
 * For HugeTLB pages, @pvmw->pte is set to the relevant page table entry
 * regardless of which page table level the page is mapped at. @pvmw->pmd is
 * शून्य.
 *
 * Returns false अगर there are no more page table entries क्रम the page in
 * the vma. @pvmw->ptl is unlocked and @pvmw->pte is unmapped.
 *
 * If you need to stop the walk beक्रमe page_vma_mapped_walk() वापसed false,
 * use page_vma_mapped_walk_करोne(). It will करो the housekeeping.
 */
bool page_vma_mapped_walk(काष्ठा page_vma_mapped_walk *pvmw)
अणु
	काष्ठा mm_काष्ठा *mm = pvmw->vma->vm_mm;
	काष्ठा page *page = pvmw->page;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t pmde;

	/* The only possible pmd mapping has been handled on last iteration */
	अगर (pvmw->pmd && !pvmw->pte)
		वापस not_found(pvmw);

	अगर (pvmw->pte)
		जाओ next_pte;

	अगर (unlikely(PageHuge(pvmw->page))) अणु
		/* when pud is not present, pte will be शून्य */
		pvmw->pte = huge_pte_offset(mm, pvmw->address, page_size(page));
		अगर (!pvmw->pte)
			वापस false;

		pvmw->ptl = huge_pte_lockptr(page_hstate(page), mm, pvmw->pte);
		spin_lock(pvmw->ptl);
		अगर (!check_pte(pvmw))
			वापस not_found(pvmw);
		वापस true;
	पूर्ण
restart:
	pgd = pgd_offset(mm, pvmw->address);
	अगर (!pgd_present(*pgd))
		वापस false;
	p4d = p4d_offset(pgd, pvmw->address);
	अगर (!p4d_present(*p4d))
		वापस false;
	pud = pud_offset(p4d, pvmw->address);
	अगर (!pud_present(*pud))
		वापस false;
	pvmw->pmd = pmd_offset(pud, pvmw->address);
	/*
	 * Make sure the pmd value isn't cached in a रेजिस्टर by the
	 * compiler and used as a stale value after we've observed a
	 * subsequent update.
	 */
	pmde = READ_ONCE(*pvmw->pmd);
	अगर (pmd_trans_huge(pmde) || is_pmd_migration_entry(pmde)) अणु
		pvmw->ptl = pmd_lock(mm, pvmw->pmd);
		अगर (likely(pmd_trans_huge(*pvmw->pmd))) अणु
			अगर (pvmw->flags & PVMW_MIGRATION)
				वापस not_found(pvmw);
			अगर (pmd_page(*pvmw->pmd) != page)
				वापस not_found(pvmw);
			वापस true;
		पूर्ण अन्यथा अगर (!pmd_present(*pvmw->pmd)) अणु
			अगर (thp_migration_supported()) अणु
				अगर (!(pvmw->flags & PVMW_MIGRATION))
					वापस not_found(pvmw);
				अगर (is_migration_entry(pmd_to_swp_entry(*pvmw->pmd))) अणु
					swp_entry_t entry = pmd_to_swp_entry(*pvmw->pmd);

					अगर (migration_entry_to_page(entry) != page)
						वापस not_found(pvmw);
					वापस true;
				पूर्ण
			पूर्ण
			वापस not_found(pvmw);
		पूर्ण अन्यथा अणु
			/* THP pmd was split under us: handle on pte level */
			spin_unlock(pvmw->ptl);
			pvmw->ptl = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (!pmd_present(pmde)) अणु
		/*
		 * If PVMW_SYNC, take and drop THP pmd lock so that we
		 * cannot वापस prematurely, जबतक zap_huge_pmd() has
		 * cleared *pmd but not decremented compound_mapcount().
		 */
		अगर ((pvmw->flags & PVMW_SYNC) &&
		    PageTransCompound(pvmw->page)) अणु
			spinlock_t *ptl = pmd_lock(mm, pvmw->pmd);

			spin_unlock(ptl);
		पूर्ण
		वापस false;
	पूर्ण
	अगर (!map_pte(pvmw))
		जाओ next_pte;
	जबतक (1) अणु
		अचिन्हित दीर्घ end;

		अगर (check_pte(pvmw))
			वापस true;
next_pte:
		/* Seek to next pte only makes sense क्रम THP */
		अगर (!PageTransHuge(pvmw->page) || PageHuge(pvmw->page))
			वापस not_found(pvmw);
		end = vma_address_end(pvmw->page, pvmw->vma);
		करो अणु
			pvmw->address += PAGE_SIZE;
			अगर (pvmw->address >= end)
				वापस not_found(pvmw);
			/* Did we cross page table boundary? */
			अगर (pvmw->address % PMD_SIZE == 0) अणु
				pte_unmap(pvmw->pte);
				अगर (pvmw->ptl) अणु
					spin_unlock(pvmw->ptl);
					pvmw->ptl = शून्य;
				पूर्ण
				जाओ restart;
			पूर्ण अन्यथा अणु
				pvmw->pte++;
			पूर्ण
		पूर्ण जबतक (pte_none(*pvmw->pte));

		अगर (!pvmw->ptl) अणु
			pvmw->ptl = pte_lockptr(mm, pvmw->pmd);
			spin_lock(pvmw->ptl);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * page_mapped_in_vma - check whether a page is really mapped in a VMA
 * @page: the page to test
 * @vma: the VMA to test
 *
 * Returns 1 अगर the page is mapped पूर्णांकo the page tables of the VMA, 0
 * अगर the page is not mapped पूर्णांकo the page tables of this VMA.  Only
 * valid क्रम normal file or anonymous VMAs.
 */
पूर्णांक page_mapped_in_vma(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा page_vma_mapped_walk pvmw = अणु
		.page = page,
		.vma = vma,
		.flags = PVMW_SYNC,
	पूर्ण;

	pvmw.address = vma_address(page, vma);
	अगर (pvmw.address == -EFAULT)
		वापस 0;
	अगर (!page_vma_mapped_walk(&pvmw))
		वापस 0;
	page_vma_mapped_walk_करोne(&pvmw);
	वापस 1;
पूर्ण
