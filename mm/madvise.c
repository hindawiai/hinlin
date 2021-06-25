<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/mm/madvise.c
 *
 * Copyright (C) 1999  Linus Torvalds
 * Copyright (C) 2002  Christoph Hellwig
 */

#समावेश <linux/mman.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/page-isolation.h>
#समावेश <linux/page_idle.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/fadvise.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/uपन.स>
#समावेश <linux/ksm.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/pagewalk.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/mmu_notअगरier.h>

#समावेश <यंत्र/tlb.h>

#समावेश "internal.h"

काष्ठा madvise_walk_निजी अणु
	काष्ठा mmu_gather *tlb;
	bool pageout;
पूर्ण;

/*
 * Any behaviour which results in changes to the vma->vm_flags needs to
 * take mmap_lock क्रम writing. Others, which simply traverse vmas, need
 * to only take it क्रम पढ़ोing.
 */
अटल पूर्णांक madvise_need_mmap_ग_लिखो(पूर्णांक behavior)
अणु
	चयन (behavior) अणु
	हाल MADV_REMOVE:
	हाल MADV_WILLNEED:
	हाल MADV_DONTNEED:
	हाल MADV_COLD:
	हाल MADV_PAGEOUT:
	हाल MADV_FREE:
		वापस 0;
	शेष:
		/* be safe, शेष to 1. list exceptions explicitly */
		वापस 1;
	पूर्ण
पूर्ण

/*
 * We can potentially split a vm area पूर्णांकo separate
 * areas, each area with its own behavior.
 */
अटल दीर्घ madvise_behavior(काष्ठा vm_area_काष्ठा *vma,
		     काष्ठा vm_area_काष्ठा **prev,
		     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक behavior)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	पूर्णांक error = 0;
	pgoff_t pgoff;
	अचिन्हित दीर्घ new_flags = vma->vm_flags;

	चयन (behavior) अणु
	हाल MADV_NORMAL:
		new_flags = new_flags & ~VM_RAND_READ & ~VM_SEQ_READ;
		अवरोध;
	हाल MADV_SEQUENTIAL:
		new_flags = (new_flags & ~VM_RAND_READ) | VM_SEQ_READ;
		अवरोध;
	हाल MADV_RANDOM:
		new_flags = (new_flags & ~VM_SEQ_READ) | VM_RAND_READ;
		अवरोध;
	हाल MADV_DONTFORK:
		new_flags |= VM_DONTCOPY;
		अवरोध;
	हाल MADV_DOFORK:
		अगर (vma->vm_flags & VM_IO) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
		new_flags &= ~VM_DONTCOPY;
		अवरोध;
	हाल MADV_WIPEONFORK:
		/* MADV_WIPEONFORK is only supported on anonymous memory. */
		अगर (vma->vm_file || vma->vm_flags & VM_SHARED) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
		new_flags |= VM_WIPEONFORK;
		अवरोध;
	हाल MADV_KEEPONFORK:
		new_flags &= ~VM_WIPEONFORK;
		अवरोध;
	हाल MADV_DONTDUMP:
		new_flags |= VM_DONTDUMP;
		अवरोध;
	हाल MADV_DODUMP:
		अगर (!is_vm_hugetlb_page(vma) && new_flags & VM_SPECIAL) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण
		new_flags &= ~VM_DONTDUMP;
		अवरोध;
	हाल MADV_MERGEABLE:
	हाल MADV_UNMERGEABLE:
		error = ksm_madvise(vma, start, end, behavior, &new_flags);
		अगर (error)
			जाओ out_convert_त्रुटि_सं;
		अवरोध;
	हाल MADV_HUGEPAGE:
	हाल MADV_NOHUGEPAGE:
		error = hugepage_madvise(vma, &new_flags, behavior);
		अगर (error)
			जाओ out_convert_त्रुटि_सं;
		अवरोध;
	पूर्ण

	अगर (new_flags == vma->vm_flags) अणु
		*prev = vma;
		जाओ out;
	पूर्ण

	pgoff = vma->vm_pgoff + ((start - vma->vm_start) >> PAGE_SHIFT);
	*prev = vma_merge(mm, *prev, start, end, new_flags, vma->anon_vma,
			  vma->vm_file, pgoff, vma_policy(vma),
			  vma->vm_userfaultfd_ctx);
	अगर (*prev) अणु
		vma = *prev;
		जाओ success;
	पूर्ण

	*prev = vma;

	अगर (start != vma->vm_start) अणु
		अगर (unlikely(mm->map_count >= sysctl_max_map_count)) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		error = __split_vma(mm, vma, start, 1);
		अगर (error)
			जाओ out_convert_त्रुटि_सं;
	पूर्ण

	अगर (end != vma->vm_end) अणु
		अगर (unlikely(mm->map_count >= sysctl_max_map_count)) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		error = __split_vma(mm, vma, end, 0);
		अगर (error)
			जाओ out_convert_त्रुटि_सं;
	पूर्ण

success:
	/*
	 * vm_flags is रक्षित by the mmap_lock held in ग_लिखो mode.
	 */
	vma->vm_flags = new_flags;

out_convert_त्रुटि_सं:
	/*
	 * madvise() वापसs EAGAIN अगर kernel resources, such as
	 * slab, are temporarily unavailable.
	 */
	अगर (error == -ENOMEM)
		error = -EAGAIN;
out:
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_SWAP
अटल पूर्णांक swapin_walk_pmd_entry(pmd_t *pmd, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	pte_t *orig_pte;
	काष्ठा vm_area_काष्ठा *vma = walk->निजी;
	अचिन्हित दीर्घ index;

	अगर (pmd_none_or_trans_huge_or_clear_bad(pmd))
		वापस 0;

	क्रम (index = start; index != end; index += PAGE_SIZE) अणु
		pte_t pte;
		swp_entry_t entry;
		काष्ठा page *page;
		spinlock_t *ptl;

		orig_pte = pte_offset_map_lock(vma->vm_mm, pmd, start, &ptl);
		pte = *(orig_pte + ((index - start) / PAGE_SIZE));
		pte_unmap_unlock(orig_pte, ptl);

		अगर (pte_present(pte) || pte_none(pte))
			जारी;
		entry = pte_to_swp_entry(pte);
		अगर (unlikely(non_swap_entry(entry)))
			जारी;

		page = पढ़ो_swap_cache_async(entry, GFP_HIGHUSER_MOVABLE,
							vma, index, false);
		अगर (page)
			put_page(page);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops swapin_walk_ops = अणु
	.pmd_entry		= swapin_walk_pmd_entry,
पूर्ण;

अटल व्योम क्रमce_shm_swapin_पढ़ोahead(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		काष्ठा address_space *mapping)
अणु
	XA_STATE(xas, &mapping->i_pages, linear_page_index(vma, start));
	pgoff_t end_index = linear_page_index(vma, end + PAGE_SIZE - 1);
	काष्ठा page *page;

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, end_index) अणु
		swp_entry_t swap;

		अगर (!xa_is_value(page))
			जारी;
		xas_छोड़ो(&xas);
		rcu_पढ़ो_unlock();

		swap = radix_to_swp_entry(page);
		page = पढ़ो_swap_cache_async(swap, GFP_HIGHUSER_MOVABLE,
							शून्य, 0, false);
		अगर (page)
			put_page(page);

		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();

	lru_add_drain();	/* Push any new pages onto the LRU now */
पूर्ण
#पूर्ण_अगर		/* CONFIG_SWAP */

/*
 * Schedule all required I/O operations.  Do not रुको क्रम completion.
 */
अटल दीर्घ madvise_willneed(काष्ठा vm_area_काष्ठा *vma,
			     काष्ठा vm_area_काष्ठा **prev,
			     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा file *file = vma->vm_file;
	loff_t offset;

	*prev = vma;
#अगर_घोषित CONFIG_SWAP
	अगर (!file) अणु
		walk_page_range(vma->vm_mm, start, end, &swapin_walk_ops, vma);
		lru_add_drain(); /* Push any new pages onto the LRU now */
		वापस 0;
	पूर्ण

	अगर (shmem_mapping(file->f_mapping)) अणु
		क्रमce_shm_swapin_पढ़ोahead(vma, start, end,
					file->f_mapping);
		वापस 0;
	पूर्ण
#अन्यथा
	अगर (!file)
		वापस -EBADF;
#पूर्ण_अगर

	अगर (IS_DAX(file_inode(file))) अणु
		/* no bad वापस value, but ignore advice */
		वापस 0;
	पूर्ण

	/*
	 * Fileप्रणाली's fadvise may need to take various locks.  We need to
	 * explicitly grab a reference because the vma (and hence the
	 * vma's reference to the file) can go away as soon as we drop
	 * mmap_lock.
	 */
	*prev = शून्य;	/* tell sys_madvise we drop mmap_lock */
	get_file(file);
	offset = (loff_t)(start - vma->vm_start)
			+ ((loff_t)vma->vm_pgoff << PAGE_SHIFT);
	mmap_पढ़ो_unlock(mm);
	vfs_fadvise(file, offset, end - start, POSIX_FADV_WILLNEED);
	fput(file);
	mmap_पढ़ो_lock(mm);
	वापस 0;
पूर्ण

अटल पूर्णांक madvise_cold_or_pageout_pte_range(pmd_t *pmd,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				काष्ठा mm_walk *walk)
अणु
	काष्ठा madvise_walk_निजी *निजी = walk->निजी;
	काष्ठा mmu_gather *tlb = निजी->tlb;
	bool pageout = निजी->pageout;
	काष्ठा mm_काष्ठा *mm = tlb->mm;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	pte_t *orig_pte, *pte, ptent;
	spinlock_t *ptl;
	काष्ठा page *page = शून्य;
	LIST_HEAD(page_list);

	अगर (fatal_संकेत_pending(current))
		वापस -EINTR;

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	अगर (pmd_trans_huge(*pmd)) अणु
		pmd_t orig_pmd;
		अचिन्हित दीर्घ next = pmd_addr_end(addr, end);

		tlb_change_page_size(tlb, HPAGE_PMD_SIZE);
		ptl = pmd_trans_huge_lock(pmd, vma);
		अगर (!ptl)
			वापस 0;

		orig_pmd = *pmd;
		अगर (is_huge_zero_pmd(orig_pmd))
			जाओ huge_unlock;

		अगर (unlikely(!pmd_present(orig_pmd))) अणु
			VM_BUG_ON(thp_migration_supported() &&
					!is_pmd_migration_entry(orig_pmd));
			जाओ huge_unlock;
		पूर्ण

		page = pmd_page(orig_pmd);

		/* Do not पूर्णांकerfere with other mappings of this page */
		अगर (page_mapcount(page) != 1)
			जाओ huge_unlock;

		अगर (next - addr != HPAGE_PMD_SIZE) अणु
			पूर्णांक err;

			get_page(page);
			spin_unlock(ptl);
			lock_page(page);
			err = split_huge_page(page);
			unlock_page(page);
			put_page(page);
			अगर (!err)
				जाओ regular_page;
			वापस 0;
		पूर्ण

		अगर (pmd_young(orig_pmd)) अणु
			pmdp_invalidate(vma, addr, pmd);
			orig_pmd = pmd_mkold(orig_pmd);

			set_pmd_at(mm, addr, pmd, orig_pmd);
			tlb_हटाओ_pmd_tlb_entry(tlb, pmd, addr);
		पूर्ण

		ClearPageReferenced(page);
		test_and_clear_page_young(page);
		अगर (pageout) अणु
			अगर (!isolate_lru_page(page)) अणु
				अगर (PageUnevictable(page))
					putback_lru_page(page);
				अन्यथा
					list_add(&page->lru, &page_list);
			पूर्ण
		पूर्ण अन्यथा
			deactivate_page(page);
huge_unlock:
		spin_unlock(ptl);
		अगर (pageout)
			reclaim_pages(&page_list);
		वापस 0;
	पूर्ण

regular_page:
	अगर (pmd_trans_unstable(pmd))
		वापस 0;
#पूर्ण_अगर
	tlb_change_page_size(tlb, PAGE_SIZE);
	orig_pte = pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	flush_tlb_batched_pending(mm);
	arch_enter_lazy_mmu_mode();
	क्रम (; addr < end; pte++, addr += PAGE_SIZE) अणु
		ptent = *pte;

		अगर (pte_none(ptent))
			जारी;

		अगर (!pte_present(ptent))
			जारी;

		page = vm_normal_page(vma, addr, ptent);
		अगर (!page)
			जारी;

		/*
		 * Creating a THP page is expensive so split it only अगर we
		 * are sure it's worth. Split it अगर we are only owner.
		 */
		अगर (PageTransCompound(page)) अणु
			अगर (page_mapcount(page) != 1)
				अवरोध;
			get_page(page);
			अगर (!trylock_page(page)) अणु
				put_page(page);
				अवरोध;
			पूर्ण
			pte_unmap_unlock(orig_pte, ptl);
			अगर (split_huge_page(page)) अणु
				unlock_page(page);
				put_page(page);
				pte_offset_map_lock(mm, pmd, addr, &ptl);
				अवरोध;
			पूर्ण
			unlock_page(page);
			put_page(page);
			pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
			pte--;
			addr -= PAGE_SIZE;
			जारी;
		पूर्ण

		/* Do not पूर्णांकerfere with other mappings of this page */
		अगर (page_mapcount(page) != 1)
			जारी;

		VM_BUG_ON_PAGE(PageTransCompound(page), page);

		अगर (pte_young(ptent)) अणु
			ptent = ptep_get_and_clear_full(mm, addr, pte,
							tlb->fullmm);
			ptent = pte_mkold(ptent);
			set_pte_at(mm, addr, pte, ptent);
			tlb_हटाओ_tlb_entry(tlb, pte, addr);
		पूर्ण

		/*
		 * We are deactivating a page क्रम accelerating reclaiming.
		 * VM couldn't reclaim the page unless we clear PG_young.
		 * As a side effect, it makes confuse idle-page tracking
		 * because they will miss recent referenced history.
		 */
		ClearPageReferenced(page);
		test_and_clear_page_young(page);
		अगर (pageout) अणु
			अगर (!isolate_lru_page(page)) अणु
				अगर (PageUnevictable(page))
					putback_lru_page(page);
				अन्यथा
					list_add(&page->lru, &page_list);
			पूर्ण
		पूर्ण अन्यथा
			deactivate_page(page);
	पूर्ण

	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(orig_pte, ptl);
	अगर (pageout)
		reclaim_pages(&page_list);
	cond_resched();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops cold_walk_ops = अणु
	.pmd_entry = madvise_cold_or_pageout_pte_range,
पूर्ण;

अटल व्योम madvise_cold_page_range(काष्ठा mmu_gather *tlb,
			     काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	काष्ठा madvise_walk_निजी walk_निजी = अणु
		.pageout = false,
		.tlb = tlb,
	पूर्ण;

	tlb_start_vma(tlb, vma);
	walk_page_range(vma->vm_mm, addr, end, &cold_walk_ops, &walk_निजी);
	tlb_end_vma(tlb, vma);
पूर्ण

अटल दीर्घ madvise_cold(काष्ठा vm_area_काष्ठा *vma,
			काष्ठा vm_area_काष्ठा **prev,
			अचिन्हित दीर्घ start_addr, अचिन्हित दीर्घ end_addr)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा mmu_gather tlb;

	*prev = vma;
	अगर (!can_madv_lru_vma(vma))
		वापस -EINVAL;

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm);
	madvise_cold_page_range(&tlb, vma, start_addr, end_addr);
	tlb_finish_mmu(&tlb);

	वापस 0;
पूर्ण

अटल व्योम madvise_pageout_page_range(काष्ठा mmu_gather *tlb,
			     काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	काष्ठा madvise_walk_निजी walk_निजी = अणु
		.pageout = true,
		.tlb = tlb,
	पूर्ण;

	tlb_start_vma(tlb, vma);
	walk_page_range(vma->vm_mm, addr, end, &cold_walk_ops, &walk_निजी);
	tlb_end_vma(tlb, vma);
पूर्ण

अटल अंतरभूत bool can_करो_pageout(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma_is_anonymous(vma))
		वापस true;
	अगर (!vma->vm_file)
		वापस false;
	/*
	 * paging out pagecache only क्रम non-anonymous mappings that correspond
	 * to the files the calling process could (अगर tried) खोलो क्रम writing;
	 * otherwise we'd be including shared non-exclusive mappings, which
	 * खोलोs a side channel.
	 */
	वापस inode_owner_or_capable(&init_user_ns,
				      file_inode(vma->vm_file)) ||
	       file_permission(vma->vm_file, MAY_WRITE) == 0;
पूर्ण

अटल दीर्घ madvise_pageout(काष्ठा vm_area_काष्ठा *vma,
			काष्ठा vm_area_काष्ठा **prev,
			अचिन्हित दीर्घ start_addr, अचिन्हित दीर्घ end_addr)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा mmu_gather tlb;

	*prev = vma;
	अगर (!can_madv_lru_vma(vma))
		वापस -EINVAL;

	अगर (!can_करो_pageout(vma))
		वापस 0;

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm);
	madvise_pageout_page_range(&tlb, vma, start_addr, end_addr);
	tlb_finish_mmu(&tlb);

	वापस 0;
पूर्ण

अटल पूर्णांक madvise_मुक्त_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)

अणु
	काष्ठा mmu_gather *tlb = walk->निजी;
	काष्ठा mm_काष्ठा *mm = tlb->mm;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	spinlock_t *ptl;
	pte_t *orig_pte, *pte, ptent;
	काष्ठा page *page;
	पूर्णांक nr_swap = 0;
	अचिन्हित दीर्घ next;

	next = pmd_addr_end(addr, end);
	अगर (pmd_trans_huge(*pmd))
		अगर (madvise_मुक्त_huge_pmd(tlb, vma, pmd, addr, next))
			जाओ next;

	अगर (pmd_trans_unstable(pmd))
		वापस 0;

	tlb_change_page_size(tlb, PAGE_SIZE);
	orig_pte = pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
	flush_tlb_batched_pending(mm);
	arch_enter_lazy_mmu_mode();
	क्रम (; addr != end; pte++, addr += PAGE_SIZE) अणु
		ptent = *pte;

		अगर (pte_none(ptent))
			जारी;
		/*
		 * If the pte has swp_entry, just clear page table to
		 * prevent swap-in which is more expensive rather than
		 * (page allocation + zeroing).
		 */
		अगर (!pte_present(ptent)) अणु
			swp_entry_t entry;

			entry = pte_to_swp_entry(ptent);
			अगर (non_swap_entry(entry))
				जारी;
			nr_swap--;
			मुक्त_swap_and_cache(entry);
			pte_clear_not_present_full(mm, addr, pte, tlb->fullmm);
			जारी;
		पूर्ण

		page = vm_normal_page(vma, addr, ptent);
		अगर (!page)
			जारी;

		/*
		 * If pmd isn't transhuge but the page is THP and
		 * is owned by only this process, split it and
		 * deactivate all pages.
		 */
		अगर (PageTransCompound(page)) अणु
			अगर (page_mapcount(page) != 1)
				जाओ out;
			get_page(page);
			अगर (!trylock_page(page)) अणु
				put_page(page);
				जाओ out;
			पूर्ण
			pte_unmap_unlock(orig_pte, ptl);
			अगर (split_huge_page(page)) अणु
				unlock_page(page);
				put_page(page);
				pte_offset_map_lock(mm, pmd, addr, &ptl);
				जाओ out;
			पूर्ण
			unlock_page(page);
			put_page(page);
			pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
			pte--;
			addr -= PAGE_SIZE;
			जारी;
		पूर्ण

		VM_BUG_ON_PAGE(PageTransCompound(page), page);

		अगर (PageSwapCache(page) || PageDirty(page)) अणु
			अगर (!trylock_page(page))
				जारी;
			/*
			 * If page is shared with others, we couldn't clear
			 * PG_dirty of the page.
			 */
			अगर (page_mapcount(page) != 1) अणु
				unlock_page(page);
				जारी;
			पूर्ण

			अगर (PageSwapCache(page) && !try_to_मुक्त_swap(page)) अणु
				unlock_page(page);
				जारी;
			पूर्ण

			ClearPageDirty(page);
			unlock_page(page);
		पूर्ण

		अगर (pte_young(ptent) || pte_dirty(ptent)) अणु
			/*
			 * Some of architecture(ex, PPC) करोn't update TLB
			 * with set_pte_at and tlb_हटाओ_tlb_entry so क्रम
			 * the portability, remap the pte with old|clean
			 * after pte clearing.
			 */
			ptent = ptep_get_and_clear_full(mm, addr, pte,
							tlb->fullmm);

			ptent = pte_mkold(ptent);
			ptent = pte_mkclean(ptent);
			set_pte_at(mm, addr, pte, ptent);
			tlb_हटाओ_tlb_entry(tlb, pte, addr);
		पूर्ण
		mark_page_lazyमुक्त(page);
	पूर्ण
out:
	अगर (nr_swap) अणु
		अगर (current->mm == mm)
			sync_mm_rss(mm);

		add_mm_counter(mm, MM_SWAPENTS, nr_swap);
	पूर्ण
	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(orig_pte, ptl);
	cond_resched();
next:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops madvise_मुक्त_walk_ops = अणु
	.pmd_entry		= madvise_मुक्त_pte_range,
पूर्ण;

अटल पूर्णांक madvise_मुक्त_single_vma(काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ start_addr, अचिन्हित दीर्घ end_addr)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा mmu_notअगरier_range range;
	काष्ठा mmu_gather tlb;

	/* MADV_FREE works क्रम only anon vma at the moment */
	अगर (!vma_is_anonymous(vma))
		वापस -EINVAL;

	range.start = max(vma->vm_start, start_addr);
	अगर (range.start >= vma->vm_end)
		वापस -EINVAL;
	range.end = min(vma->vm_end, end_addr);
	अगर (range.end <= vma->vm_start)
		वापस -EINVAL;
	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm,
				range.start, range.end);

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm);
	update_hiwater_rss(mm);

	mmu_notअगरier_invalidate_range_start(&range);
	tlb_start_vma(&tlb, vma);
	walk_page_range(vma->vm_mm, range.start, range.end,
			&madvise_मुक्त_walk_ops, &tlb);
	tlb_end_vma(&tlb, vma);
	mmu_notअगरier_invalidate_range_end(&range);
	tlb_finish_mmu(&tlb);

	वापस 0;
पूर्ण

/*
 * Application no दीर्घer needs these pages.  If the pages are dirty,
 * it's OK to just throw them away.  The app will be more careful about
 * data it wants to keep.  Be sure to मुक्त swap resources too.  The
 * zap_page_range call sets things up क्रम shrink_active_list to actually मुक्त
 * these pages later अगर no one अन्यथा has touched them in the meanसमय,
 * although we could add these pages to a global reuse list क्रम
 * shrink_active_list to pick up beक्रमe reclaiming other pages.
 *
 * NB: This पूर्णांकerface discards data rather than pushes it out to swap,
 * as some implementations करो.  This has perक्रमmance implications क्रम
 * applications like large transactional databases which want to discard
 * pages in anonymous maps after committing to backing store the data
 * that was kept in them.  There is no reason to ग_लिखो this data out to
 * the swap area अगर the application is discarding it.
 *
 * An पूर्णांकerface that causes the प्रणाली to मुक्त clean pages and flush
 * dirty pages is alपढ़ोy available as msync(MS_INVALIDATE).
 */
अटल दीर्घ madvise_करोntneed_single_vma(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	zap_page_range(vma, start, end - start);
	वापस 0;
पूर्ण

अटल दीर्घ madvise_करोntneed_मुक्त(काष्ठा vm_area_काष्ठा *vma,
				  काष्ठा vm_area_काष्ठा **prev,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  पूर्णांक behavior)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	*prev = vma;
	अगर (!can_madv_lru_vma(vma))
		वापस -EINVAL;

	अगर (!userfaultfd_हटाओ(vma, start, end)) अणु
		*prev = शून्य; /* mmap_lock has been dropped, prev is stale */

		mmap_पढ़ो_lock(mm);
		vma = find_vma(mm, start);
		अगर (!vma)
			वापस -ENOMEM;
		अगर (start < vma->vm_start) अणु
			/*
			 * This "vma" under revalidation is the one
			 * with the lowest vma->vm_start where start
			 * is also < vma->vm_end. If start <
			 * vma->vm_start it means an hole materialized
			 * in the user address space within the
			 * भव range passed to MADV_DONTNEED
			 * or MADV_FREE.
			 */
			वापस -ENOMEM;
		पूर्ण
		अगर (!can_madv_lru_vma(vma))
			वापस -EINVAL;
		अगर (end > vma->vm_end) अणु
			/*
			 * Don't fail अगर end > vma->vm_end. If the old
			 * vma was split जबतक the mmap_lock was
			 * released the effect of the concurrent
			 * operation may not cause madvise() to
			 * have an undefined result. There may be an
			 * adjacent next vma that we'll walk
			 * next. userfaultfd_हटाओ() will generate an
			 * UFFD_EVENT_REMOVE repetition on the
			 * end-vma->vm_end range, but the manager can
			 * handle a repetition fine.
			 */
			end = vma->vm_end;
		पूर्ण
		VM_WARN_ON(start >= end);
	पूर्ण

	अगर (behavior == MADV_DONTNEED)
		वापस madvise_करोntneed_single_vma(vma, start, end);
	अन्यथा अगर (behavior == MADV_FREE)
		वापस madvise_मुक्त_single_vma(vma, start, end);
	अन्यथा
		वापस -EINVAL;
पूर्ण

/*
 * Application wants to मुक्त up the pages and associated backing store.
 * This is effectively punching a hole पूर्णांकo the middle of a file.
 */
अटल दीर्घ madvise_हटाओ(काष्ठा vm_area_काष्ठा *vma,
				काष्ठा vm_area_काष्ठा **prev,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	loff_t offset;
	पूर्णांक error;
	काष्ठा file *f;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	*prev = शून्य;	/* tell sys_madvise we drop mmap_lock */

	अगर (vma->vm_flags & VM_LOCKED)
		वापस -EINVAL;

	f = vma->vm_file;

	अगर (!f || !f->f_mapping || !f->f_mapping->host) अणु
			वापस -EINVAL;
	पूर्ण

	अगर ((vma->vm_flags & (VM_SHARED|VM_WRITE)) != (VM_SHARED|VM_WRITE))
		वापस -EACCES;

	offset = (loff_t)(start - vma->vm_start)
			+ ((loff_t)vma->vm_pgoff << PAGE_SHIFT);

	/*
	 * Fileप्रणाली's fallocate may need to take i_mutex.  We need to
	 * explicitly grab a reference because the vma (and hence the
	 * vma's reference to the file) can go away as soon as we drop
	 * mmap_lock.
	 */
	get_file(f);
	अगर (userfaultfd_हटाओ(vma, start, end)) अणु
		/* mmap_lock was not released by userfaultfd_हटाओ() */
		mmap_पढ़ो_unlock(mm);
	पूर्ण
	error = vfs_fallocate(f,
				FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE,
				offset, end - start);
	fput(f);
	mmap_पढ़ो_lock(mm);
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_FAILURE
/*
 * Error injection support क्रम memory error handling.
 */
अटल पूर्णांक madvise_inject_error(पूर्णांक behavior,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ size;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;


	क्रम (; start < end; start += size) अणु
		अचिन्हित दीर्घ pfn;
		काष्ठा page *page;
		पूर्णांक ret;

		ret = get_user_pages_fast(start, 1, 0, &page);
		अगर (ret != 1)
			वापस ret;
		pfn = page_to_pfn(page);

		/*
		 * When soft offlining hugepages, after migrating the page
		 * we dissolve it, thereक्रमe in the second loop "page" will
		 * no दीर्घer be a compound page.
		 */
		size = page_size(compound_head(page));

		अगर (behavior == MADV_SOFT_OFFLINE) अणु
			pr_info("Soft offlining pfn %#lx at process virtual address %#lx\n",
				 pfn, start);
			ret = soft_offline_page(pfn, MF_COUNT_INCREASED);
		पूर्ण अन्यथा अणु
			pr_info("Injecting memory failure for pfn %#lx at process virtual address %#lx\n",
				 pfn, start);
			ret = memory_failure(pfn, MF_COUNT_INCREASED);
		पूर्ण

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल दीर्घ
madvise_vma(काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_area_काष्ठा **prev,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक behavior)
अणु
	चयन (behavior) अणु
	हाल MADV_REMOVE:
		वापस madvise_हटाओ(vma, prev, start, end);
	हाल MADV_WILLNEED:
		वापस madvise_willneed(vma, prev, start, end);
	हाल MADV_COLD:
		वापस madvise_cold(vma, prev, start, end);
	हाल MADV_PAGEOUT:
		वापस madvise_pageout(vma, prev, start, end);
	हाल MADV_FREE:
	हाल MADV_DONTNEED:
		वापस madvise_करोntneed_मुक्त(vma, prev, start, end, behavior);
	शेष:
		वापस madvise_behavior(vma, prev, start, end, behavior);
	पूर्ण
पूर्ण

अटल bool
madvise_behavior_valid(पूर्णांक behavior)
अणु
	चयन (behavior) अणु
	हाल MADV_DOFORK:
	हाल MADV_DONTFORK:
	हाल MADV_NORMAL:
	हाल MADV_SEQUENTIAL:
	हाल MADV_RANDOM:
	हाल MADV_REMOVE:
	हाल MADV_WILLNEED:
	हाल MADV_DONTNEED:
	हाल MADV_FREE:
	हाल MADV_COLD:
	हाल MADV_PAGEOUT:
#अगर_घोषित CONFIG_KSM
	हाल MADV_MERGEABLE:
	हाल MADV_UNMERGEABLE:
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	हाल MADV_HUGEPAGE:
	हाल MADV_NOHUGEPAGE:
#पूर्ण_अगर
	हाल MADV_DONTDUMP:
	हाल MADV_DODUMP:
	हाल MADV_WIPEONFORK:
	हाल MADV_KEEPONFORK:
#अगर_घोषित CONFIG_MEMORY_FAILURE
	हाल MADV_SOFT_OFFLINE:
	हाल MADV_HWPOISON:
#पूर्ण_अगर
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool
process_madvise_behavior_valid(पूर्णांक behavior)
अणु
	चयन (behavior) अणु
	हाल MADV_COLD:
	हाल MADV_PAGEOUT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * The madvise(2) प्रणाली call.
 *
 * Applications can use madvise() to advise the kernel how it should
 * handle paging I/O in this VM area.  The idea is to help the kernel
 * use appropriate पढ़ो-ahead and caching techniques.  The inक्रमmation
 * provided is advisory only, and can be safely disregarded by the
 * kernel without affecting the correct operation of the application.
 *
 * behavior values:
 *  MADV_NORMAL - the शेष behavior is to पढ़ो clusters.  This
 *		results in some पढ़ो-ahead and पढ़ो-behind.
 *  MADV_RANDOM - the प्रणाली should पढ़ो the minimum amount of data
 *		on any access, since it is unlikely that the appli-
 *		cation will need more than what it asks क्रम.
 *  MADV_SEQUENTIAL - pages in the given range will probably be accessed
 *		once, so they can be aggressively पढ़ो ahead, and
 *		can be मुक्तd soon after they are accessed.
 *  MADV_WILLNEED - the application is notअगरying the प्रणाली to पढ़ो
 *		some pages ahead.
 *  MADV_DONTNEED - the application is finished with the given range,
 *		so the kernel can मुक्त resources associated with it.
 *  MADV_FREE - the application marks pages in the given range as lazy मुक्त,
 *		where actual purges are postponed until memory pressure happens.
 *  MADV_REMOVE - the application wants to मुक्त up the given range of
 *		pages and associated backing store.
 *  MADV_DONTFORK - omit this area from child's address space when विभाजनing:
 *		typically, to aव्योम COWing pages pinned by get_user_pages().
 *  MADV_DOFORK - cancel MADV_DONTFORK: no दीर्घer omit this area when विभाजनing.
 *  MADV_WIPEONFORK - present the child process with zero-filled memory in this
 *              range after a विभाजन.
 *  MADV_KEEPONFORK - unकरो the effect of MADV_WIPEONFORK
 *  MADV_HWPOISON - trigger memory error handler as अगर the given memory range
 *		were corrupted by unrecoverable hardware memory failure.
 *  MADV_SOFT_OFFLINE - try to soft-offline the given range of memory.
 *  MADV_MERGEABLE - the application recommends that KSM try to merge pages in
 *		this area with pages of identical content from other such areas.
 *  MADV_UNMERGEABLE- cancel MADV_MERGEABLE: no दीर्घer merge pages with others.
 *  MADV_HUGEPAGE - the application wants to back the given range by transparent
 *		huge pages in the future. Existing pages might be coalesced and
 *		new pages might be allocated as THP.
 *  MADV_NOHUGEPAGE - mark the given range as not worth being backed by
 *		transparent huge pages so the existing pages will not be
 *		coalesced पूर्णांकo THP and new pages will not be allocated as THP.
 *  MADV_DONTDUMP - the application wants to prevent pages in the given range
 *		from being included in its core dump.
 *  MADV_DODUMP - cancel MADV_DONTDUMP: no दीर्घer exclude from core dump.
 *  MADV_COLD - the application is not expected to use this memory soon,
 *		deactivate pages in this range so that they can be reclaimed
 *		easily अगर memory pressure happens.
 *  MADV_PAGEOUT - the application is not expected to use this memory soon,
 *		page out the pages in this range immediately.
 *
 * वापस values:
 *  zero    - success
 *  -EINVAL - start + len < 0, start is not page-aligned,
 *		"behavior" is not a valid value, or application
 *		is attempting to release locked or shared pages,
 *		or the specअगरied address range includes file, Huge TLB,
 *		MAP_SHARED or VMPFNMAP range.
 *  -ENOMEM - addresses in the specअगरied range are not currently
 *		mapped, or are outside the AS of the process.
 *  -EIO    - an I/O error occurred जबतक paging in data.
 *  -EBADF  - map exists, but area maps something that isn't a file.
 *  -EAGAIN - a kernel resource was temporarily unavailable.
 */
पूर्णांक करो_madvise(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, माप_प्रकार len_in, पूर्णांक behavior)
अणु
	अचिन्हित दीर्घ end, पंचांगp;
	काष्ठा vm_area_काष्ठा *vma, *prev;
	पूर्णांक unmapped_error = 0;
	पूर्णांक error = -EINVAL;
	पूर्णांक ग_लिखो;
	माप_प्रकार len;
	काष्ठा blk_plug plug;

	start = untagged_addr(start);

	अगर (!madvise_behavior_valid(behavior))
		वापस error;

	अगर (!PAGE_ALIGNED(start))
		वापस error;
	len = PAGE_ALIGN(len_in);

	/* Check to see whether len was rounded up from small -ve to zero */
	अगर (len_in && !len)
		वापस error;

	end = start + len;
	अगर (end < start)
		वापस error;

	error = 0;
	अगर (end == start)
		वापस error;

#अगर_घोषित CONFIG_MEMORY_FAILURE
	अगर (behavior == MADV_HWPOISON || behavior == MADV_SOFT_OFFLINE)
		वापस madvise_inject_error(behavior, start, start + len_in);
#पूर्ण_अगर

	ग_लिखो = madvise_need_mmap_ग_लिखो(behavior);
	अगर (ग_लिखो) अणु
		अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
			वापस -EINTR;
	पूर्ण अन्यथा अणु
		mmap_पढ़ो_lock(mm);
	पूर्ण

	/*
	 * If the पूर्णांकerval [start,end) covers some unmapped address
	 * ranges, just ignore them, but वापस -ENOMEM at the end.
	 * - dअगरferent from the way of handling in mlock etc.
	 */
	vma = find_vma_prev(mm, start, &prev);
	अगर (vma && start > vma->vm_start)
		prev = vma;

	blk_start_plug(&plug);
	क्रम (;;) अणु
		/* Still start < end. */
		error = -ENOMEM;
		अगर (!vma)
			जाओ out;

		/* Here start < (end|vma->vm_end). */
		अगर (start < vma->vm_start) अणु
			unmapped_error = -ENOMEM;
			start = vma->vm_start;
			अगर (start >= end)
				जाओ out;
		पूर्ण

		/* Here vma->vm_start <= start < (end|vma->vm_end) */
		पंचांगp = vma->vm_end;
		अगर (end < पंचांगp)
			पंचांगp = end;

		/* Here vma->vm_start <= start < पंचांगp <= (end|vma->vm_end). */
		error = madvise_vma(vma, &prev, start, पंचांगp, behavior);
		अगर (error)
			जाओ out;
		start = पंचांगp;
		अगर (prev && start < prev->vm_end)
			start = prev->vm_end;
		error = unmapped_error;
		अगर (start >= end)
			जाओ out;
		अगर (prev)
			vma = prev->vm_next;
		अन्यथा	/* madvise_हटाओ dropped mmap_lock */
			vma = find_vma(mm, start);
	पूर्ण
out:
	blk_finish_plug(&plug);
	अगर (ग_लिखो)
		mmap_ग_लिखो_unlock(mm);
	अन्यथा
		mmap_पढ़ो_unlock(mm);

	वापस error;
पूर्ण

SYSCALL_DEFINE3(madvise, अचिन्हित दीर्घ, start, माप_प्रकार, len_in, पूर्णांक, behavior)
अणु
	वापस करो_madvise(current->mm, start, len_in, behavior);
पूर्ण

SYSCALL_DEFINE5(process_madvise, पूर्णांक, pidfd, स्थिर काष्ठा iovec __user *, vec,
		माप_प्रकार, vlen, पूर्णांक, behavior, अचिन्हित पूर्णांक, flags)
अणु
	sमाप_प्रकार ret;
	काष्ठा iovec iovstack[UIO_FASTIOV], iovec;
	काष्ठा iovec *iov = iovstack;
	काष्ठा iov_iter iter;
	काष्ठा pid *pid;
	काष्ठा task_काष्ठा *task;
	काष्ठा mm_काष्ठा *mm;
	माप_प्रकार total_len;
	अचिन्हित पूर्णांक f_flags;

	अगर (flags != 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = import_iovec(READ, vec, vlen, ARRAY_SIZE(iovstack), &iov, &iter);
	अगर (ret < 0)
		जाओ out;

	pid = pidfd_get_pid(pidfd, &f_flags);
	अगर (IS_ERR(pid)) अणु
		ret = PTR_ERR(pid);
		जाओ मुक्त_iov;
	पूर्ण

	task = get_pid_task(pid, PIDTYPE_PID);
	अगर (!task) अणु
		ret = -ESRCH;
		जाओ put_pid;
	पूर्ण

	अगर (!process_madvise_behavior_valid(behavior)) अणु
		ret = -EINVAL;
		जाओ release_task;
	पूर्ण

	/* Require PTRACE_MODE_READ to aव्योम leaking ASLR metadata. */
	mm = mm_access(task, PTRACE_MODE_READ_FSCREDS);
	अगर (IS_ERR_OR_शून्य(mm)) अणु
		ret = IS_ERR(mm) ? PTR_ERR(mm) : -ESRCH;
		जाओ release_task;
	पूर्ण

	/*
	 * Require CAP_SYS_NICE क्रम influencing process perक्रमmance. Note that
	 * only non-deकाष्ठाive hपूर्णांकs are currently supported.
	 */
	अगर (!capable(CAP_SYS_NICE)) अणु
		ret = -EPERM;
		जाओ release_mm;
	पूर्ण

	total_len = iov_iter_count(&iter);

	जबतक (iov_iter_count(&iter)) अणु
		iovec = iov_iter_iovec(&iter);
		ret = करो_madvise(mm, (अचिन्हित दीर्घ)iovec.iov_base,
					iovec.iov_len, behavior);
		अगर (ret < 0)
			अवरोध;
		iov_iter_advance(&iter, iovec.iov_len);
	पूर्ण

	अगर (ret == 0)
		ret = total_len - iov_iter_count(&iter);

release_mm:
	mmput(mm);
release_task:
	put_task_काष्ठा(task);
put_pid:
	put_pid(pid);
मुक्त_iov:
	kमुक्त(iov);
out:
	वापस ret;
पूर्ण
