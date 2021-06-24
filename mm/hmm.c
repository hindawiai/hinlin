<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Authors: Jथऊrथखme Glisse <jglisse@redhat.com>
 */
/*
 * Refer to include/linux/hmm.h क्रम inक्रमmation about heterogeneous memory
 * management or HMM क्रम लघु.
 */
#समावेश <linux/pagewalk.h>
#समावेश <linux/hmm.h>
#समावेश <linux/init.h>
#समावेश <linux/rmap.h>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/memremap.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/memory_hotplug.h>

काष्ठा hmm_vma_walk अणु
	काष्ठा hmm_range	*range;
	अचिन्हित दीर्घ		last;
पूर्ण;

क्रमागत अणु
	HMM_NEED_FAULT = 1 << 0,
	HMM_NEED_WRITE_FAULT = 1 << 1,
	HMM_NEED_ALL_BITS = HMM_NEED_FAULT | HMM_NEED_WRITE_FAULT,
पूर्ण;

अटल पूर्णांक hmm_pfns_fill(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			 काष्ठा hmm_range *range, अचिन्हित दीर्घ cpu_flags)
अणु
	अचिन्हित दीर्घ i = (addr - range->start) >> PAGE_SHIFT;

	क्रम (; addr < end; addr += PAGE_SIZE, i++)
		range->hmm_pfns[i] = cpu_flags;
	वापस 0;
पूर्ण

/*
 * hmm_vma_fault() - fault in a range lacking valid pmd or pte(s)
 * @addr: range भव start address (inclusive)
 * @end: range भव end address (exclusive)
 * @required_fault: HMM_NEED_* flags
 * @walk: mm_walk काष्ठाure
 * Return: -EBUSY after page fault, or page fault error
 *
 * This function will be called whenever pmd_none() or pte_none() वापसs true,
 * or whenever there is no page directory covering the भव address range.
 */
अटल पूर्णांक hmm_vma_fault(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			 अचिन्हित पूर्णांक required_fault, काष्ठा mm_walk *walk)
अणु
	काष्ठा hmm_vma_walk *hmm_vma_walk = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	अचिन्हित पूर्णांक fault_flags = FAULT_FLAG_REMOTE;

	WARN_ON_ONCE(!required_fault);
	hmm_vma_walk->last = addr;

	अगर (required_fault & HMM_NEED_WRITE_FAULT) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			वापस -EPERM;
		fault_flags |= FAULT_FLAG_WRITE;
	पूर्ण

	क्रम (; addr < end; addr += PAGE_SIZE)
		अगर (handle_mm_fault(vma, addr, fault_flags, शून्य) &
		    VM_FAULT_ERROR)
			वापस -EFAULT;
	वापस -EBUSY;
पूर्ण

अटल अचिन्हित पूर्णांक hmm_pte_need_fault(स्थिर काष्ठा hmm_vma_walk *hmm_vma_walk,
				       अचिन्हित दीर्घ pfn_req_flags,
				       अचिन्हित दीर्घ cpu_flags)
अणु
	काष्ठा hmm_range *range = hmm_vma_walk->range;

	/*
	 * So we not only consider the inभागidual per page request we also
	 * consider the शेष flags requested क्रम the range. The API can
	 * be used 2 ways. The first one where the HMM user coalesces
	 * multiple page faults पूर्णांकo one request and sets flags per pfn क्रम
	 * those faults. The second one where the HMM user wants to pre-
	 * fault a range with specअगरic flags. For the latter one it is a
	 * waste to have the user pre-fill the pfn arrays with a शेष
	 * flags value.
	 */
	pfn_req_flags &= range->pfn_flags_mask;
	pfn_req_flags |= range->शेष_flags;

	/* We aren't ask to करो anything ... */
	अगर (!(pfn_req_flags & HMM_PFN_REQ_FAULT))
		वापस 0;

	/* Need to ग_लिखो fault ? */
	अगर ((pfn_req_flags & HMM_PFN_REQ_WRITE) &&
	    !(cpu_flags & HMM_PFN_WRITE))
		वापस HMM_NEED_FAULT | HMM_NEED_WRITE_FAULT;

	/* If CPU page table is not valid then we need to fault */
	अगर (!(cpu_flags & HMM_PFN_VALID))
		वापस HMM_NEED_FAULT;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
hmm_range_need_fault(स्थिर काष्ठा hmm_vma_walk *hmm_vma_walk,
		     स्थिर अचिन्हित दीर्घ hmm_pfns[], अचिन्हित दीर्घ npages,
		     अचिन्हित दीर्घ cpu_flags)
अणु
	काष्ठा hmm_range *range = hmm_vma_walk->range;
	अचिन्हित पूर्णांक required_fault = 0;
	अचिन्हित दीर्घ i;

	/*
	 * If the शेष flags करो not request to fault pages, and the mask करोes
	 * not allow क्रम inभागidual pages to be faulted, then
	 * hmm_pte_need_fault() will always वापस 0.
	 */
	अगर (!((range->शेष_flags | range->pfn_flags_mask) &
	      HMM_PFN_REQ_FAULT))
		वापस 0;

	क्रम (i = 0; i < npages; ++i) अणु
		required_fault |= hmm_pte_need_fault(hmm_vma_walk, hmm_pfns[i],
						     cpu_flags);
		अगर (required_fault == HMM_NEED_ALL_BITS)
			वापस required_fault;
	पूर्ण
	वापस required_fault;
पूर्ण

अटल पूर्णांक hmm_vma_walk_hole(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			     __always_unused पूर्णांक depth, काष्ठा mm_walk *walk)
अणु
	काष्ठा hmm_vma_walk *hmm_vma_walk = walk->निजी;
	काष्ठा hmm_range *range = hmm_vma_walk->range;
	अचिन्हित पूर्णांक required_fault;
	अचिन्हित दीर्घ i, npages;
	अचिन्हित दीर्घ *hmm_pfns;

	i = (addr - range->start) >> PAGE_SHIFT;
	npages = (end - addr) >> PAGE_SHIFT;
	hmm_pfns = &range->hmm_pfns[i];
	required_fault =
		hmm_range_need_fault(hmm_vma_walk, hmm_pfns, npages, 0);
	अगर (!walk->vma) अणु
		अगर (required_fault)
			वापस -EFAULT;
		वापस hmm_pfns_fill(addr, end, range, HMM_PFN_ERROR);
	पूर्ण
	अगर (required_fault)
		वापस hmm_vma_fault(addr, end, required_fault, walk);
	वापस hmm_pfns_fill(addr, end, range, 0);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hmm_pfn_flags_order(अचिन्हित दीर्घ order)
अणु
	वापस order << HMM_PFN_ORDER_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_to_hmm_pfn_flags(काष्ठा hmm_range *range,
						 pmd_t pmd)
अणु
	अगर (pmd_protnone(pmd))
		वापस 0;
	वापस (pmd_ग_लिखो(pmd) ? (HMM_PFN_VALID | HMM_PFN_WRITE) :
				 HMM_PFN_VALID) |
	       hmm_pfn_flags_order(PMD_SHIFT - PAGE_SHIFT);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल पूर्णांक hmm_vma_handle_pmd(काष्ठा mm_walk *walk, अचिन्हित दीर्घ addr,
			      अचिन्हित दीर्घ end, अचिन्हित दीर्घ hmm_pfns[],
			      pmd_t pmd)
अणु
	काष्ठा hmm_vma_walk *hmm_vma_walk = walk->निजी;
	काष्ठा hmm_range *range = hmm_vma_walk->range;
	अचिन्हित दीर्घ pfn, npages, i;
	अचिन्हित पूर्णांक required_fault;
	अचिन्हित दीर्घ cpu_flags;

	npages = (end - addr) >> PAGE_SHIFT;
	cpu_flags = pmd_to_hmm_pfn_flags(range, pmd);
	required_fault =
		hmm_range_need_fault(hmm_vma_walk, hmm_pfns, npages, cpu_flags);
	अगर (required_fault)
		वापस hmm_vma_fault(addr, end, required_fault, walk);

	pfn = pmd_pfn(pmd) + ((addr & ~PMD_MASK) >> PAGE_SHIFT);
	क्रम (i = 0; addr < end; addr += PAGE_SIZE, i++, pfn++)
		hmm_pfns[i] = pfn | cpu_flags;
	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_TRANSPARENT_HUGEPAGE */
/* stub to allow the code below to compile */
पूर्णांक hmm_vma_handle_pmd(काष्ठा mm_walk *walk, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end, अचिन्हित दीर्घ hmm_pfns[], pmd_t pmd);
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

अटल अंतरभूत bool hmm_is_device_निजी_entry(काष्ठा hmm_range *range,
		swp_entry_t entry)
अणु
	वापस is_device_निजी_entry(entry) &&
		device_निजी_entry_to_page(entry)->pgmap->owner ==
		range->dev_निजी_owner;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_to_hmm_pfn_flags(काष्ठा hmm_range *range,
						 pte_t pte)
अणु
	अगर (pte_none(pte) || !pte_present(pte) || pte_protnone(pte))
		वापस 0;
	वापस pte_ग_लिखो(pte) ? (HMM_PFN_VALID | HMM_PFN_WRITE) : HMM_PFN_VALID;
पूर्ण

अटल पूर्णांक hmm_vma_handle_pte(काष्ठा mm_walk *walk, अचिन्हित दीर्घ addr,
			      अचिन्हित दीर्घ end, pmd_t *pmdp, pte_t *ptep,
			      अचिन्हित दीर्घ *hmm_pfn)
अणु
	काष्ठा hmm_vma_walk *hmm_vma_walk = walk->निजी;
	काष्ठा hmm_range *range = hmm_vma_walk->range;
	अचिन्हित पूर्णांक required_fault;
	अचिन्हित दीर्घ cpu_flags;
	pte_t pte = *ptep;
	uपूर्णांक64_t pfn_req_flags = *hmm_pfn;

	अगर (pte_none(pte)) अणु
		required_fault =
			hmm_pte_need_fault(hmm_vma_walk, pfn_req_flags, 0);
		अगर (required_fault)
			जाओ fault;
		*hmm_pfn = 0;
		वापस 0;
	पूर्ण

	अगर (!pte_present(pte)) अणु
		swp_entry_t entry = pte_to_swp_entry(pte);

		/*
		 * Never fault in device निजी pages, but just report
		 * the PFN even अगर not present.
		 */
		अगर (hmm_is_device_निजी_entry(range, entry)) अणु
			cpu_flags = HMM_PFN_VALID;
			अगर (is_ग_लिखो_device_निजी_entry(entry))
				cpu_flags |= HMM_PFN_WRITE;
			*hmm_pfn = device_निजी_entry_to_pfn(entry) |
					cpu_flags;
			वापस 0;
		पूर्ण

		required_fault =
			hmm_pte_need_fault(hmm_vma_walk, pfn_req_flags, 0);
		अगर (!required_fault) अणु
			*hmm_pfn = 0;
			वापस 0;
		पूर्ण

		अगर (!non_swap_entry(entry))
			जाओ fault;

		अगर (is_migration_entry(entry)) अणु
			pte_unmap(ptep);
			hmm_vma_walk->last = addr;
			migration_entry_रुको(walk->mm, pmdp, addr);
			वापस -EBUSY;
		पूर्ण

		/* Report error क्रम everything अन्यथा */
		pte_unmap(ptep);
		वापस -EFAULT;
	पूर्ण

	cpu_flags = pte_to_hmm_pfn_flags(range, pte);
	required_fault =
		hmm_pte_need_fault(hmm_vma_walk, pfn_req_flags, cpu_flags);
	अगर (required_fault)
		जाओ fault;

	/*
	 * Since each architecture defines a काष्ठा page क्रम the zero page, just
	 * fall through and treat it like a normal page.
	 */
	अगर (pte_special(pte) && !is_zero_pfn(pte_pfn(pte))) अणु
		अगर (hmm_pte_need_fault(hmm_vma_walk, pfn_req_flags, 0)) अणु
			pte_unmap(ptep);
			वापस -EFAULT;
		पूर्ण
		*hmm_pfn = HMM_PFN_ERROR;
		वापस 0;
	पूर्ण

	*hmm_pfn = pte_pfn(pte) | cpu_flags;
	वापस 0;

fault:
	pte_unmap(ptep);
	/* Fault any भव address we were asked to fault */
	वापस hmm_vma_fault(addr, end, required_fault, walk);
पूर्ण

अटल पूर्णांक hmm_vma_walk_pmd(pmd_t *pmdp,
			    अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end,
			    काष्ठा mm_walk *walk)
अणु
	काष्ठा hmm_vma_walk *hmm_vma_walk = walk->निजी;
	काष्ठा hmm_range *range = hmm_vma_walk->range;
	अचिन्हित दीर्घ *hmm_pfns =
		&range->hmm_pfns[(start - range->start) >> PAGE_SHIFT];
	अचिन्हित दीर्घ npages = (end - start) >> PAGE_SHIFT;
	अचिन्हित दीर्घ addr = start;
	pte_t *ptep;
	pmd_t pmd;

again:
	pmd = READ_ONCE(*pmdp);
	अगर (pmd_none(pmd))
		वापस hmm_vma_walk_hole(start, end, -1, walk);

	अगर (thp_migration_supported() && is_pmd_migration_entry(pmd)) अणु
		अगर (hmm_range_need_fault(hmm_vma_walk, hmm_pfns, npages, 0)) अणु
			hmm_vma_walk->last = addr;
			pmd_migration_entry_रुको(walk->mm, pmdp);
			वापस -EBUSY;
		पूर्ण
		वापस hmm_pfns_fill(start, end, range, 0);
	पूर्ण

	अगर (!pmd_present(pmd)) अणु
		अगर (hmm_range_need_fault(hmm_vma_walk, hmm_pfns, npages, 0))
			वापस -EFAULT;
		वापस hmm_pfns_fill(start, end, range, HMM_PFN_ERROR);
	पूर्ण

	अगर (pmd_devmap(pmd) || pmd_trans_huge(pmd)) अणु
		/*
		 * No need to take pmd_lock here, even अगर some other thपढ़ो
		 * is splitting the huge pmd we will get that event through
		 * mmu_notअगरier callback.
		 *
		 * So just पढ़ो pmd value and check again it's a transparent
		 * huge or device mapping one and compute corresponding pfn
		 * values.
		 */
		pmd = pmd_पढ़ो_atomic(pmdp);
		barrier();
		अगर (!pmd_devmap(pmd) && !pmd_trans_huge(pmd))
			जाओ again;

		वापस hmm_vma_handle_pmd(walk, addr, end, hmm_pfns, pmd);
	पूर्ण

	/*
	 * We have handled all the valid हालs above ie either none, migration,
	 * huge or transparent huge. At this poपूर्णांक either it is a valid pmd
	 * entry poपूर्णांकing to pte directory or it is a bad pmd that will not
	 * recover.
	 */
	अगर (pmd_bad(pmd)) अणु
		अगर (hmm_range_need_fault(hmm_vma_walk, hmm_pfns, npages, 0))
			वापस -EFAULT;
		वापस hmm_pfns_fill(start, end, range, HMM_PFN_ERROR);
	पूर्ण

	ptep = pte_offset_map(pmdp, addr);
	क्रम (; addr < end; addr += PAGE_SIZE, ptep++, hmm_pfns++) अणु
		पूर्णांक r;

		r = hmm_vma_handle_pte(walk, addr, end, pmdp, ptep, hmm_pfns);
		अगर (r) अणु
			/* hmm_vma_handle_pte() did pte_unmap() */
			वापस r;
		पूर्ण
	पूर्ण
	pte_unmap(ptep - 1);
	वापस 0;
पूर्ण

#अगर defined(CONFIG_ARCH_HAS_PTE_DEVMAP) && \
    defined(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD)
अटल अंतरभूत अचिन्हित दीर्घ pud_to_hmm_pfn_flags(काष्ठा hmm_range *range,
						 pud_t pud)
अणु
	अगर (!pud_present(pud))
		वापस 0;
	वापस (pud_ग_लिखो(pud) ? (HMM_PFN_VALID | HMM_PFN_WRITE) :
				 HMM_PFN_VALID) |
	       hmm_pfn_flags_order(PUD_SHIFT - PAGE_SHIFT);
पूर्ण

अटल पूर्णांक hmm_vma_walk_pud(pud_t *pudp, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		काष्ठा mm_walk *walk)
अणु
	काष्ठा hmm_vma_walk *hmm_vma_walk = walk->निजी;
	काष्ठा hmm_range *range = hmm_vma_walk->range;
	अचिन्हित दीर्घ addr = start;
	pud_t pud;
	पूर्णांक ret = 0;
	spinlock_t *ptl = pud_trans_huge_lock(pudp, walk->vma);

	अगर (!ptl)
		वापस 0;

	/* Normally we करोn't want to split the huge page */
	walk->action = ACTION_CONTINUE;

	pud = READ_ONCE(*pudp);
	अगर (pud_none(pud)) अणु
		spin_unlock(ptl);
		वापस hmm_vma_walk_hole(start, end, -1, walk);
	पूर्ण

	अगर (pud_huge(pud) && pud_devmap(pud)) अणु
		अचिन्हित दीर्घ i, npages, pfn;
		अचिन्हित पूर्णांक required_fault;
		अचिन्हित दीर्घ *hmm_pfns;
		अचिन्हित दीर्घ cpu_flags;

		अगर (!pud_present(pud)) अणु
			spin_unlock(ptl);
			वापस hmm_vma_walk_hole(start, end, -1, walk);
		पूर्ण

		i = (addr - range->start) >> PAGE_SHIFT;
		npages = (end - addr) >> PAGE_SHIFT;
		hmm_pfns = &range->hmm_pfns[i];

		cpu_flags = pud_to_hmm_pfn_flags(range, pud);
		required_fault = hmm_range_need_fault(hmm_vma_walk, hmm_pfns,
						      npages, cpu_flags);
		अगर (required_fault) अणु
			spin_unlock(ptl);
			वापस hmm_vma_fault(addr, end, required_fault, walk);
		पूर्ण

		pfn = pud_pfn(pud) + ((addr & ~PUD_MASK) >> PAGE_SHIFT);
		क्रम (i = 0; i < npages; ++i, ++pfn)
			hmm_pfns[i] = pfn | cpu_flags;
		जाओ out_unlock;
	पूर्ण

	/* Ask क्रम the PUD to be split */
	walk->action = ACTION_SUBTREE;

out_unlock:
	spin_unlock(ptl);
	वापस ret;
पूर्ण
#अन्यथा
#घोषणा hmm_vma_walk_pud	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल पूर्णांक hmm_vma_walk_hugetlb_entry(pte_t *pte, अचिन्हित दीर्घ hmask,
				      अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				      काष्ठा mm_walk *walk)
अणु
	अचिन्हित दीर्घ addr = start, i, pfn;
	काष्ठा hmm_vma_walk *hmm_vma_walk = walk->निजी;
	काष्ठा hmm_range *range = hmm_vma_walk->range;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	अचिन्हित पूर्णांक required_fault;
	अचिन्हित दीर्घ pfn_req_flags;
	अचिन्हित दीर्घ cpu_flags;
	spinlock_t *ptl;
	pte_t entry;

	ptl = huge_pte_lock(hstate_vma(vma), walk->mm, pte);
	entry = huge_ptep_get(pte);

	i = (start - range->start) >> PAGE_SHIFT;
	pfn_req_flags = range->hmm_pfns[i];
	cpu_flags = pte_to_hmm_pfn_flags(range, entry) |
		    hmm_pfn_flags_order(huge_page_order(hstate_vma(vma)));
	required_fault =
		hmm_pte_need_fault(hmm_vma_walk, pfn_req_flags, cpu_flags);
	अगर (required_fault) अणु
		spin_unlock(ptl);
		वापस hmm_vma_fault(addr, end, required_fault, walk);
	पूर्ण

	pfn = pte_pfn(entry) + ((start & ~hmask) >> PAGE_SHIFT);
	क्रम (; addr < end; addr += PAGE_SIZE, i++, pfn++)
		range->hmm_pfns[i] = pfn | cpu_flags;

	spin_unlock(ptl);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा hmm_vma_walk_hugetlb_entry शून्य
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

अटल पूर्णांक hmm_vma_walk_test(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			     काष्ठा mm_walk *walk)
अणु
	काष्ठा hmm_vma_walk *hmm_vma_walk = walk->निजी;
	काष्ठा hmm_range *range = hmm_vma_walk->range;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;

	अगर (!(vma->vm_flags & (VM_IO | VM_PFNMAP | VM_MIXEDMAP)) &&
	    vma->vm_flags & VM_READ)
		वापस 0;

	/*
	 * vma ranges that करोn't have काष्ठा page backing them or map I/O
	 * devices directly cannot be handled by hmm_range_fault().
	 *
	 * If the vma करोes not allow पढ़ो access, then assume that it करोes not
	 * allow ग_लिखो access either. HMM करोes not support architectures that
	 * allow ग_लिखो without पढ़ो.
	 *
	 * If a fault is requested क्रम an unsupported range then it is a hard
	 * failure.
	 */
	अगर (hmm_range_need_fault(hmm_vma_walk,
				 range->hmm_pfns +
					 ((start - range->start) >> PAGE_SHIFT),
				 (end - start) >> PAGE_SHIFT, 0))
		वापस -EFAULT;

	hmm_pfns_fill(start, end, range, HMM_PFN_ERROR);

	/* Skip this vma and जारी processing the next vma. */
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops hmm_walk_ops = अणु
	.pud_entry	= hmm_vma_walk_pud,
	.pmd_entry	= hmm_vma_walk_pmd,
	.pte_hole	= hmm_vma_walk_hole,
	.hugetlb_entry	= hmm_vma_walk_hugetlb_entry,
	.test_walk	= hmm_vma_walk_test,
पूर्ण;

/**
 * hmm_range_fault - try to fault some address in a भव address range
 * @range:	argument काष्ठाure
 *
 * Returns 0 on success or one of the following error codes:
 *
 * -EINVAL:	Invalid arguments or mm or भव address is in an invalid vma
 *		(e.g., device file vma).
 * -ENOMEM:	Out of memory.
 * -EPERM:	Invalid permission (e.g., asking क्रम ग_लिखो and range is पढ़ो
 *		only).
 * -EBUSY:	The range has been invalidated and the caller needs to रुको क्रम
 *		the invalidation to finish.
 * -EFAULT:     A page was requested to be valid and could not be made valid
 *              ie it has no backing VMA or it is illegal to access
 *
 * This is similar to get_user_pages(), except that it can पढ़ो the page tables
 * without mutating them (ie causing faults).
 */
पूर्णांक hmm_range_fault(काष्ठा hmm_range *range)
अणु
	काष्ठा hmm_vma_walk hmm_vma_walk = अणु
		.range = range,
		.last = range->start,
	पूर्ण;
	काष्ठा mm_काष्ठा *mm = range->notअगरier->mm;
	पूर्णांक ret;

	mmap_निश्चित_locked(mm);

	करो अणु
		/* If range is no दीर्घer valid क्रमce retry. */
		अगर (mmu_पूर्णांकerval_check_retry(range->notअगरier,
					     range->notअगरier_seq))
			वापस -EBUSY;
		ret = walk_page_range(mm, hmm_vma_walk.last, range->end,
				      &hmm_walk_ops, &hmm_vma_walk);
		/*
		 * When -EBUSY is वापसed the loop restarts with
		 * hmm_vma_walk.last set to an address that has not been stored
		 * in pfns. All entries < last in the pfn array are set to their
		 * output, and all >= are still at their input values.
		 */
	पूर्ण जबतक (ret == -EBUSY);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(hmm_range_fault);
