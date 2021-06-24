<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  mm/mprotect.c
 *
 *  (C) Copyright 1994 Linus Torvalds
 *  (C) Copyright 2002 Christoph Hellwig
 *
 *  Address space accounting code	<alan@lxorguk.ukuu.org.uk>
 *  (C) Copyright 2002 Red Hat Inc, All Rights Reserved
 */

#समावेश <linux/pagewalk.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/shm.h>
#समावेश <linux/mman.h>
#समावेश <linux/fs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/security.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/personality.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/migrate.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/pkeys.h>
#समावेश <linux/ksm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "internal.h"

अटल अचिन्हित दीर्घ change_pte_range(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end, pgprot_t newprot,
		अचिन्हित दीर्घ cp_flags)
अणु
	pte_t *pte, oldpte;
	spinlock_t *ptl;
	अचिन्हित दीर्घ pages = 0;
	पूर्णांक target_node = NUMA_NO_NODE;
	bool dirty_accountable = cp_flags & MM_CP_सूचीTY_ACCT;
	bool prot_numa = cp_flags & MM_CP_PROT_NUMA;
	bool uffd_wp = cp_flags & MM_CP_UFFD_WP;
	bool uffd_wp_resolve = cp_flags & MM_CP_UFFD_WP_RESOLVE;

	/*
	 * Can be called with only the mmap_lock क्रम पढ़ोing by
	 * prot_numa so we must check the pmd isn't स्थिरantly
	 * changing from under us from pmd_none to pmd_trans_huge
	 * and/or the other way around.
	 */
	अगर (pmd_trans_unstable(pmd))
		वापस 0;

	/*
	 * The pmd poपूर्णांकs to a regular pte so the pmd can't change
	 * from under us even अगर the mmap_lock is only hold क्रम
	 * पढ़ोing.
	 */
	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);

	/* Get target node क्रम single thपढ़ोed निजी VMAs */
	अगर (prot_numa && !(vma->vm_flags & VM_SHARED) &&
	    atomic_पढ़ो(&vma->vm_mm->mm_users) == 1)
		target_node = numa_node_id();

	flush_tlb_batched_pending(vma->vm_mm);
	arch_enter_lazy_mmu_mode();
	करो अणु
		oldpte = *pte;
		अगर (pte_present(oldpte)) अणु
			pte_t ptent;
			bool preserve_ग_लिखो = prot_numa && pte_ग_लिखो(oldpte);

			/*
			 * Aव्योम trapping faults against the zero or KSM
			 * pages. See similar comment in change_huge_pmd.
			 */
			अगर (prot_numa) अणु
				काष्ठा page *page;

				/* Aव्योम TLB flush अगर possible */
				अगर (pte_protnone(oldpte))
					जारी;

				page = vm_normal_page(vma, addr, oldpte);
				अगर (!page || PageKsm(page))
					जारी;

				/* Also skip shared copy-on-ग_लिखो pages */
				अगर (is_cow_mapping(vma->vm_flags) &&
				    page_mapcount(page) != 1)
					जारी;

				/*
				 * While migration can move some dirty pages,
				 * it cannot move them all from MIGRATE_ASYNC
				 * context.
				 */
				अगर (page_is_file_lru(page) && PageDirty(page))
					जारी;

				/*
				 * Don't mess with PTEs अगर page is alपढ़ोy on the node
				 * a single-thपढ़ोed process is running on.
				 */
				अगर (target_node == page_to_nid(page))
					जारी;
			पूर्ण

			oldpte = ptep_modअगरy_prot_start(vma, addr, pte);
			ptent = pte_modअगरy(oldpte, newprot);
			अगर (preserve_ग_लिखो)
				ptent = pte_mk_savedग_लिखो(ptent);

			अगर (uffd_wp) अणु
				ptent = pte_wrprotect(ptent);
				ptent = pte_mkuffd_wp(ptent);
			पूर्ण अन्यथा अगर (uffd_wp_resolve) अणु
				/*
				 * Leave the ग_लिखो bit to be handled
				 * by PF पूर्णांकerrupt handler, then
				 * things like COW could be properly
				 * handled.
				 */
				ptent = pte_clear_uffd_wp(ptent);
			पूर्ण

			/* Aव्योम taking ग_लिखो faults क्रम known dirty pages */
			अगर (dirty_accountable && pte_dirty(ptent) &&
					(pte_soft_dirty(ptent) ||
					 !(vma->vm_flags & VM_SOFTसूचीTY))) अणु
				ptent = pte_mkग_लिखो(ptent);
			पूर्ण
			ptep_modअगरy_prot_commit(vma, addr, pte, oldpte, ptent);
			pages++;
		पूर्ण अन्यथा अगर (is_swap_pte(oldpte)) अणु
			swp_entry_t entry = pte_to_swp_entry(oldpte);
			pte_t newpte;

			अगर (is_ग_लिखो_migration_entry(entry)) अणु
				/*
				 * A protection check is dअगरficult so
				 * just be safe and disable ग_लिखो
				 */
				make_migration_entry_पढ़ो(&entry);
				newpte = swp_entry_to_pte(entry);
				अगर (pte_swp_soft_dirty(oldpte))
					newpte = pte_swp_mksoft_dirty(newpte);
				अगर (pte_swp_uffd_wp(oldpte))
					newpte = pte_swp_mkuffd_wp(newpte);
			पूर्ण अन्यथा अगर (is_ग_लिखो_device_निजी_entry(entry)) अणु
				/*
				 * We करो not preserve soft-dirtiness. See
				 * copy_one_pte() क्रम explanation.
				 */
				make_device_निजी_entry_पढ़ो(&entry);
				newpte = swp_entry_to_pte(entry);
				अगर (pte_swp_uffd_wp(oldpte))
					newpte = pte_swp_mkuffd_wp(newpte);
			पूर्ण अन्यथा अणु
				newpte = oldpte;
			पूर्ण

			अगर (uffd_wp)
				newpte = pte_swp_mkuffd_wp(newpte);
			अन्यथा अगर (uffd_wp_resolve)
				newpte = pte_swp_clear_uffd_wp(newpte);

			अगर (!pte_same(oldpte, newpte)) अणु
				set_pte_at(vma->vm_mm, addr, pte, newpte);
				pages++;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(pte - 1, ptl);

	वापस pages;
पूर्ण

/*
 * Used when setting स्वतःmatic NUMA hपूर्णांकing protection where it is
 * critical that a numa hपूर्णांकing PMD is not confused with a bad PMD.
 */
अटल अंतरभूत पूर्णांक pmd_none_or_clear_bad_unless_trans_huge(pmd_t *pmd)
अणु
	pmd_t pmdval = pmd_पढ़ो_atomic(pmd);

	/* See pmd_none_or_trans_huge_or_clear_bad क्रम info on barrier */
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	barrier();
#पूर्ण_अगर

	अगर (pmd_none(pmdval))
		वापस 1;
	अगर (pmd_trans_huge(pmdval))
		वापस 0;
	अगर (unlikely(pmd_bad(pmdval))) अणु
		pmd_clear_bad(pmd);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ change_pmd_range(काष्ठा vm_area_काष्ठा *vma,
		pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		pgprot_t newprot, अचिन्हित दीर्घ cp_flags)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ pages = 0;
	अचिन्हित दीर्घ nr_huge_updates = 0;
	काष्ठा mmu_notअगरier_range range;

	range.start = 0;

	pmd = pmd_offset(pud, addr);
	करो अणु
		अचिन्हित दीर्घ this_pages;

		next = pmd_addr_end(addr, end);

		/*
		 * Automatic NUMA balancing walks the tables with mmap_lock
		 * held क्रम पढ़ो. It's possible a parallel update to occur
		 * between pmd_trans_huge() and a pmd_none_or_clear_bad()
		 * check leading to a false positive and clearing.
		 * Hence, it's necessary to atomically पढ़ो the PMD value
		 * क्रम all the checks.
		 */
		अगर (!is_swap_pmd(*pmd) && !pmd_devmap(*pmd) &&
		     pmd_none_or_clear_bad_unless_trans_huge(pmd))
			जाओ next;

		/* invoke the mmu notअगरier अगर the pmd is populated */
		अगर (!range.start) अणु
			mmu_notअगरier_range_init(&range,
				MMU_NOTIFY_PROTECTION_VMA, 0,
				vma, vma->vm_mm, addr, end);
			mmu_notअगरier_invalidate_range_start(&range);
		पूर्ण

		अगर (is_swap_pmd(*pmd) || pmd_trans_huge(*pmd) || pmd_devmap(*pmd)) अणु
			अगर (next - addr != HPAGE_PMD_SIZE) अणु
				__split_huge_pmd(vma, pmd, addr, false, शून्य);
			पूर्ण अन्यथा अणु
				पूर्णांक nr_ptes = change_huge_pmd(vma, pmd, addr,
							      newprot, cp_flags);

				अगर (nr_ptes) अणु
					अगर (nr_ptes == HPAGE_PMD_NR) अणु
						pages += HPAGE_PMD_NR;
						nr_huge_updates++;
					पूर्ण

					/* huge pmd was handled */
					जाओ next;
				पूर्ण
			पूर्ण
			/* fall through, the trans huge pmd just split */
		पूर्ण
		this_pages = change_pte_range(vma, pmd, addr, next, newprot,
					      cp_flags);
		pages += this_pages;
next:
		cond_resched();
	पूर्ण जबतक (pmd++, addr = next, addr != end);

	अगर (range.start)
		mmu_notअगरier_invalidate_range_end(&range);

	अगर (nr_huge_updates)
		count_vm_numa_events(NUMA_HUGE_PTE_UPDATES, nr_huge_updates);
	वापस pages;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ change_pud_range(काष्ठा vm_area_काष्ठा *vma,
		p4d_t *p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		pgprot_t newprot, अचिन्हित दीर्घ cp_flags)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ pages = 0;

	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (pud_none_or_clear_bad(pud))
			जारी;
		pages += change_pmd_range(vma, pud, addr, next, newprot,
					  cp_flags);
	पूर्ण जबतक (pud++, addr = next, addr != end);

	वापस pages;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ change_p4d_range(काष्ठा vm_area_काष्ठा *vma,
		pgd_t *pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		pgprot_t newprot, अचिन्हित दीर्घ cp_flags)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ pages = 0;

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none_or_clear_bad(p4d))
			जारी;
		pages += change_pud_range(vma, p4d, addr, next, newprot,
					  cp_flags);
	पूर्ण जबतक (p4d++, addr = next, addr != end);

	वापस pages;
पूर्ण

अटल अचिन्हित दीर्घ change_protection_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end, pgprot_t newprot,
		अचिन्हित दीर्घ cp_flags)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pgd_t *pgd;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ start = addr;
	अचिन्हित दीर्घ pages = 0;

	BUG_ON(addr >= end);
	pgd = pgd_offset(mm, addr);
	flush_cache_range(vma, addr, end);
	inc_tlb_flush_pending(mm);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_none_or_clear_bad(pgd))
			जारी;
		pages += change_p4d_range(vma, pgd, addr, next, newprot,
					  cp_flags);
	पूर्ण जबतक (pgd++, addr = next, addr != end);

	/* Only flush the TLB अगर we actually modअगरied any entries: */
	अगर (pages)
		flush_tlb_range(vma, start, end);
	dec_tlb_flush_pending(mm);

	वापस pages;
पूर्ण

अचिन्हित दीर्घ change_protection(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		       अचिन्हित दीर्घ end, pgprot_t newprot,
		       अचिन्हित दीर्घ cp_flags)
अणु
	अचिन्हित दीर्घ pages;

	BUG_ON((cp_flags & MM_CP_UFFD_WP_ALL) == MM_CP_UFFD_WP_ALL);

	अगर (is_vm_hugetlb_page(vma))
		pages = hugetlb_change_protection(vma, start, end, newprot);
	अन्यथा
		pages = change_protection_range(vma, start, end, newprot,
						cp_flags);

	वापस pages;
पूर्ण

अटल पूर्णांक prot_none_pte_entry(pte_t *pte, अचिन्हित दीर्घ addr,
			       अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	वापस pfn_modअगरy_allowed(pte_pfn(*pte), *(pgprot_t *)(walk->निजी)) ?
		0 : -EACCES;
पूर्ण

अटल पूर्णांक prot_none_hugetlb_entry(pte_t *pte, अचिन्हित दीर्घ hmask,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next,
				   काष्ठा mm_walk *walk)
अणु
	वापस pfn_modअगरy_allowed(pte_pfn(*pte), *(pgprot_t *)(walk->निजी)) ?
		0 : -EACCES;
पूर्ण

अटल पूर्णांक prot_none_test(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next,
			  काष्ठा mm_walk *walk)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops prot_none_walk_ops = अणु
	.pte_entry		= prot_none_pte_entry,
	.hugetlb_entry		= prot_none_hugetlb_entry,
	.test_walk		= prot_none_test,
पूर्ण;

पूर्णांक
mprotect_fixup(काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_area_काष्ठा **pprev,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, अचिन्हित दीर्घ newflags)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ oldflags = vma->vm_flags;
	दीर्घ nrpages = (end - start) >> PAGE_SHIFT;
	अचिन्हित दीर्घ अक्षरged = 0;
	pgoff_t pgoff;
	पूर्णांक error;
	पूर्णांक dirty_accountable = 0;

	अगर (newflags == oldflags) अणु
		*pprev = vma;
		वापस 0;
	पूर्ण

	/*
	 * Do PROT_NONE PFN permission checks here when we can still
	 * bail out without unकरोing a lot of state. This is a rather
	 * uncommon हाल, so करोesn't need to be very optimized.
	 */
	अगर (arch_has_pfn_modअगरy_check() &&
	    (vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) &&
	    (newflags & VM_ACCESS_FLAGS) == 0) अणु
		pgprot_t new_pgprot = vm_get_page_prot(newflags);

		error = walk_page_range(current->mm, start, end,
				&prot_none_walk_ops, &new_pgprot);
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * If we make a निजी mapping writable we increase our commit;
	 * but (without finer accounting) cannot reduce our commit अगर we
	 * make it unwritable again. hugetlb mapping were accounted क्रम
	 * even अगर पढ़ो-only so there is no need to account क्रम them here
	 */
	अगर (newflags & VM_WRITE) अणु
		/* Check space limits when area turns पूर्णांकo data. */
		अगर (!may_expand_vm(mm, newflags, nrpages) &&
				may_expand_vm(mm, oldflags, nrpages))
			वापस -ENOMEM;
		अगर (!(oldflags & (VM_ACCOUNT|VM_WRITE|VM_HUGETLB|
						VM_SHARED|VM_NORESERVE))) अणु
			अक्षरged = nrpages;
			अगर (security_vm_enough_memory_mm(mm, अक्षरged))
				वापस -ENOMEM;
			newflags |= VM_ACCOUNT;
		पूर्ण
	पूर्ण

	/*
	 * First try to merge with previous and/or next vma.
	 */
	pgoff = vma->vm_pgoff + ((start - vma->vm_start) >> PAGE_SHIFT);
	*pprev = vma_merge(mm, *pprev, start, end, newflags,
			   vma->anon_vma, vma->vm_file, pgoff, vma_policy(vma),
			   vma->vm_userfaultfd_ctx);
	अगर (*pprev) अणु
		vma = *pprev;
		VM_WARN_ON((vma->vm_flags ^ newflags) & ~VM_SOFTसूचीTY);
		जाओ success;
	पूर्ण

	*pprev = vma;

	अगर (start != vma->vm_start) अणु
		error = split_vma(mm, vma, start, 1);
		अगर (error)
			जाओ fail;
	पूर्ण

	अगर (end != vma->vm_end) अणु
		error = split_vma(mm, vma, end, 0);
		अगर (error)
			जाओ fail;
	पूर्ण

success:
	/*
	 * vm_flags and vm_page_prot are रक्षित by the mmap_lock
	 * held in ग_लिखो mode.
	 */
	vma->vm_flags = newflags;
	dirty_accountable = vma_wants_ग_लिखोnotअगरy(vma, vma->vm_page_prot);
	vma_set_page_prot(vma);

	change_protection(vma, start, end, vma->vm_page_prot,
			  dirty_accountable ? MM_CP_सूचीTY_ACCT : 0);

	/*
	 * Private VM_LOCKED VMA becoming writable: trigger COW to aव्योम major
	 * fault on access.
	 */
	अगर ((oldflags & (VM_WRITE | VM_SHARED | VM_LOCKED)) == VM_LOCKED &&
			(newflags & VM_WRITE)) अणु
		populate_vma_page_range(vma, start, end, शून्य);
	पूर्ण

	vm_stat_account(mm, oldflags, -nrpages);
	vm_stat_account(mm, newflags, nrpages);
	perf_event_mmap(vma);
	वापस 0;

fail:
	vm_unacct_memory(अक्षरged);
	वापस error;
पूर्ण

/*
 * pkey==-1 when करोing a legacy mprotect()
 */
अटल पूर्णांक करो_mprotect_pkey(अचिन्हित दीर्घ start, माप_प्रकार len,
		अचिन्हित दीर्घ prot, पूर्णांक pkey)
अणु
	अचिन्हित दीर्घ nstart, end, पंचांगp, reqprot;
	काष्ठा vm_area_काष्ठा *vma, *prev;
	पूर्णांक error = -EINVAL;
	स्थिर पूर्णांक grows = prot & (PROT_GROWSDOWN|PROT_GROWSUP);
	स्थिर bool rier = (current->personality & READ_IMPLIES_EXEC) &&
				(prot & PROT_READ);

	start = untagged_addr(start);

	prot &= ~(PROT_GROWSDOWN|PROT_GROWSUP);
	अगर (grows == (PROT_GROWSDOWN|PROT_GROWSUP)) /* can't be both */
		वापस -EINVAL;

	अगर (start & ~PAGE_MASK)
		वापस -EINVAL;
	अगर (!len)
		वापस 0;
	len = PAGE_ALIGN(len);
	end = start + len;
	अगर (end <= start)
		वापस -ENOMEM;
	अगर (!arch_validate_prot(prot, start))
		वापस -EINVAL;

	reqprot = prot;

	अगर (mmap_ग_लिखो_lock_समाप्तable(current->mm))
		वापस -EINTR;

	/*
	 * If userspace did not allocate the pkey, करो not let
	 * them use it here.
	 */
	error = -EINVAL;
	अगर ((pkey != -1) && !mm_pkey_is_allocated(current->mm, pkey))
		जाओ out;

	vma = find_vma(current->mm, start);
	error = -ENOMEM;
	अगर (!vma)
		जाओ out;
	prev = vma->vm_prev;
	अगर (unlikely(grows & PROT_GROWSDOWN)) अणु
		अगर (vma->vm_start >= end)
			जाओ out;
		start = vma->vm_start;
		error = -EINVAL;
		अगर (!(vma->vm_flags & VM_GROWSDOWN))
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (vma->vm_start > start)
			जाओ out;
		अगर (unlikely(grows & PROT_GROWSUP)) अणु
			end = vma->vm_end;
			error = -EINVAL;
			अगर (!(vma->vm_flags & VM_GROWSUP))
				जाओ out;
		पूर्ण
	पूर्ण
	अगर (start > vma->vm_start)
		prev = vma;

	क्रम (nstart = start ; ; ) अणु
		अचिन्हित दीर्घ mask_off_old_flags;
		अचिन्हित दीर्घ newflags;
		पूर्णांक new_vma_pkey;

		/* Here we know that vma->vm_start <= nstart < vma->vm_end. */

		/* Does the application expect PROT_READ to imply PROT_EXEC */
		अगर (rier && (vma->vm_flags & VM_MAYEXEC))
			prot |= PROT_EXEC;

		/*
		 * Each mprotect() call explicitly passes r/w/x permissions.
		 * If a permission is not passed to mprotect(), it must be
		 * cleared from the VMA.
		 */
		mask_off_old_flags = VM_READ | VM_WRITE | VM_EXEC |
					VM_FLAGS_CLEAR;

		new_vma_pkey = arch_override_mprotect_pkey(vma, prot, pkey);
		newflags = calc_vm_prot_bits(prot, new_vma_pkey);
		newflags |= (vma->vm_flags & ~mask_off_old_flags);

		/* newflags >> 4 shअगरt VM_MAY% in place of VM_% */
		अगर ((newflags & ~(newflags >> 4)) & VM_ACCESS_FLAGS) अणु
			error = -EACCES;
			जाओ out;
		पूर्ण

		/* Allow architectures to sanity-check the new flags */
		अगर (!arch_validate_flags(newflags)) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण

		error = security_file_mprotect(vma, reqprot, prot);
		अगर (error)
			जाओ out;

		पंचांगp = vma->vm_end;
		अगर (पंचांगp > end)
			पंचांगp = end;

		अगर (vma->vm_ops && vma->vm_ops->mprotect) अणु
			error = vma->vm_ops->mprotect(vma, nstart, पंचांगp, newflags);
			अगर (error)
				जाओ out;
		पूर्ण

		error = mprotect_fixup(vma, &prev, nstart, पंचांगp, newflags);
		अगर (error)
			जाओ out;

		nstart = पंचांगp;

		अगर (nstart < prev->vm_end)
			nstart = prev->vm_end;
		अगर (nstart >= end)
			जाओ out;

		vma = prev->vm_next;
		अगर (!vma || vma->vm_start != nstart) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		prot = reqprot;
	पूर्ण
out:
	mmap_ग_लिखो_unlock(current->mm);
	वापस error;
पूर्ण

SYSCALL_DEFINE3(mprotect, अचिन्हित दीर्घ, start, माप_प्रकार, len,
		अचिन्हित दीर्घ, prot)
अणु
	वापस करो_mprotect_pkey(start, len, prot, -1);
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_PKEYS

SYSCALL_DEFINE4(pkey_mprotect, अचिन्हित दीर्घ, start, माप_प्रकार, len,
		अचिन्हित दीर्घ, prot, पूर्णांक, pkey)
अणु
	वापस करो_mprotect_pkey(start, len, prot, pkey);
पूर्ण

SYSCALL_DEFINE2(pkey_alloc, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ, init_val)
अणु
	पूर्णांक pkey;
	पूर्णांक ret;

	/* No flags supported yet. */
	अगर (flags)
		वापस -EINVAL;
	/* check क्रम unsupported init values */
	अगर (init_val & ~PKEY_ACCESS_MASK)
		वापस -EINVAL;

	mmap_ग_लिखो_lock(current->mm);
	pkey = mm_pkey_alloc(current->mm);

	ret = -ENOSPC;
	अगर (pkey == -1)
		जाओ out;

	ret = arch_set_user_pkey_access(current, pkey, init_val);
	अगर (ret) अणु
		mm_pkey_मुक्त(current->mm, pkey);
		जाओ out;
	पूर्ण
	ret = pkey;
out:
	mmap_ग_लिखो_unlock(current->mm);
	वापस ret;
पूर्ण

SYSCALL_DEFINE1(pkey_मुक्त, पूर्णांक, pkey)
अणु
	पूर्णांक ret;

	mmap_ग_लिखो_lock(current->mm);
	ret = mm_pkey_मुक्त(current->mm, pkey);
	mmap_ग_लिखो_unlock(current->mm);

	/*
	 * We could provide warnings or errors अगर any VMA still
	 * has the pkey set here.
	 */
	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_ARCH_HAS_PKEYS */
