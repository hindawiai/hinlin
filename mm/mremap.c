<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	mm/mremap.c
 *
 *	(C) Copyright 1996 Linus Torvalds
 *
 *	Address space accounting code	<alan@lxorguk.ukuu.org.uk>
 *	(C) Copyright 2002 Red Hat Inc, All Rights Reserved
 */

#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/shm.h>
#समावेश <linux/ksm.h>
#समावेश <linux/mman.h>
#समावेश <linux/swap.h>
#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/swapops.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/userfaultfd_k.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "internal.h"

अटल pud_t *get_old_pud(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset(mm, addr);
	अगर (pgd_none_or_clear_bad(pgd))
		वापस शून्य;

	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none_or_clear_bad(p4d))
		वापस शून्य;

	pud = pud_offset(p4d, addr);
	अगर (pud_none_or_clear_bad(pud))
		वापस शून्य;

	वापस pud;
पूर्ण

अटल pmd_t *get_old_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pud_t *pud;
	pmd_t *pmd;

	pud = get_old_pud(mm, addr);
	अगर (!pud)
		वापस शून्य;

	pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd))
		वापस शून्य;

	वापस pmd;
पूर्ण

अटल pud_t *alloc_new_pud(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			    अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;

	pgd = pgd_offset(mm, addr);
	p4d = p4d_alloc(mm, pgd, addr);
	अगर (!p4d)
		वापस शून्य;

	वापस pud_alloc(mm, p4d, addr);
पूर्ण

अटल pmd_t *alloc_new_pmd(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			    अचिन्हित दीर्घ addr)
अणु
	pud_t *pud;
	pmd_t *pmd;

	pud = alloc_new_pud(mm, vma, addr);
	अगर (!pud)
		वापस शून्य;

	pmd = pmd_alloc(mm, pud, addr);
	अगर (!pmd)
		वापस शून्य;

	VM_BUG_ON(pmd_trans_huge(*pmd));

	वापस pmd;
पूर्ण

अटल व्योम take_rmap_locks(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_file)
		i_mmap_lock_ग_लिखो(vma->vm_file->f_mapping);
	अगर (vma->anon_vma)
		anon_vma_lock_ग_लिखो(vma->anon_vma);
पूर्ण

अटल व्योम drop_rmap_locks(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->anon_vma)
		anon_vma_unlock_ग_लिखो(vma->anon_vma);
	अगर (vma->vm_file)
		i_mmap_unlock_ग_लिखो(vma->vm_file->f_mapping);
पूर्ण

अटल pte_t move_soft_dirty_pte(pte_t pte)
अणु
	/*
	 * Set soft dirty bit so we can notice
	 * in userspace the ptes were moved.
	 */
#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
	अगर (pte_present(pte))
		pte = pte_mksoft_dirty(pte);
	अन्यथा अगर (is_swap_pte(pte))
		pte = pte_swp_mksoft_dirty(pte);
#पूर्ण_अगर
	वापस pte;
पूर्ण

अटल व्योम move_ptes(काष्ठा vm_area_काष्ठा *vma, pmd_t *old_pmd,
		अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ old_end,
		काष्ठा vm_area_काष्ठा *new_vma, pmd_t *new_pmd,
		अचिन्हित दीर्घ new_addr, bool need_rmap_locks)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pte_t *old_pte, *new_pte, pte;
	spinlock_t *old_ptl, *new_ptl;
	bool क्रमce_flush = false;
	अचिन्हित दीर्घ len = old_end - old_addr;

	/*
	 * When need_rmap_locks is true, we take the i_mmap_rwsem and anon_vma
	 * locks to ensure that rmap will always observe either the old or the
	 * new ptes. This is the easiest way to aव्योम races with
	 * truncate_pagecache(), page migration, etc...
	 *
	 * When need_rmap_locks is false, we use other ways to aव्योम
	 * such races:
	 *
	 * - During exec() shअगरt_arg_pages(), we use a specially tagged vma
	 *   which rmap call sites look क्रम using vma_is_temporary_stack().
	 *
	 * - During mremap(), new_vma is often known to be placed after vma
	 *   in rmap traversal order. This ensures rmap will always observe
	 *   either the old pte, or the new pte, or both (the page table locks
	 *   serialize access to inभागidual ptes, but only rmap traversal
	 *   order guarantees that we won't miss both the old and new ptes).
	 */
	अगर (need_rmap_locks)
		take_rmap_locks(vma);

	/*
	 * We करोn't have to worry about the ordering of src and dst
	 * pte locks because exclusive mmap_lock prevents deadlock.
	 */
	old_pte = pte_offset_map_lock(mm, old_pmd, old_addr, &old_ptl);
	new_pte = pte_offset_map(new_pmd, new_addr);
	new_ptl = pte_lockptr(mm, new_pmd);
	अगर (new_ptl != old_ptl)
		spin_lock_nested(new_ptl, SINGLE_DEPTH_NESTING);
	flush_tlb_batched_pending(vma->vm_mm);
	arch_enter_lazy_mmu_mode();

	क्रम (; old_addr < old_end; old_pte++, old_addr += PAGE_SIZE,
				   new_pte++, new_addr += PAGE_SIZE) अणु
		अगर (pte_none(*old_pte))
			जारी;

		pte = ptep_get_and_clear(mm, old_addr, old_pte);
		/*
		 * If we are remapping a valid PTE, make sure
		 * to flush TLB beक्रमe we drop the PTL क्रम the
		 * PTE.
		 *
		 * NOTE! Both old and new PTL matter: the old one
		 * क्रम racing with page_mkclean(), the new one to
		 * make sure the physical page stays valid until
		 * the TLB entry क्रम the old mapping has been
		 * flushed.
		 */
		अगर (pte_present(pte))
			क्रमce_flush = true;
		pte = move_pte(pte, new_vma->vm_page_prot, old_addr, new_addr);
		pte = move_soft_dirty_pte(pte);
		set_pte_at(mm, new_addr, new_pte, pte);
	पूर्ण

	arch_leave_lazy_mmu_mode();
	अगर (क्रमce_flush)
		flush_tlb_range(vma, old_end - len, old_end);
	अगर (new_ptl != old_ptl)
		spin_unlock(new_ptl);
	pte_unmap(new_pte - 1);
	pte_unmap_unlock(old_pte - 1, old_ptl);
	अगर (need_rmap_locks)
		drop_rmap_locks(vma);
पूर्ण

#अगर_घोषित CONFIG_HAVE_MOVE_PMD
अटल bool move_normal_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ old_addr,
		  अचिन्हित दीर्घ new_addr, pmd_t *old_pmd, pmd_t *new_pmd)
अणु
	spinlock_t *old_ptl, *new_ptl;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pmd_t pmd;

	/*
	 * The destination pmd shouldn't be established, मुक्त_pgtables()
	 * should have released it.
	 *
	 * However, there's a हाल during execve() where we use mremap
	 * to move the initial stack, and in that हाल the target area
	 * may overlap the source area (always moving करोwn).
	 *
	 * If everything is PMD-aligned, that works fine, as moving
	 * each pmd करोwn will clear the source pmd. But अगर we first
	 * have a few 4kB-only pages that get moved करोwn, and then
	 * hit the "now the rest is PMD-aligned, let's करो everything
	 * one pmd at a समय", we will still have the old (now empty
	 * of any 4kB pages, but still there) PMD in the page table
	 * tree.
	 *
	 * Warn on it once - because we really should try to figure
	 * out how to करो this better - but then say "I won't move
	 * this pmd".
	 *
	 * One alternative might be to just unmap the target pmd at
	 * this poपूर्णांक, and verअगरy that it really is empty. We'll see.
	 */
	अगर (WARN_ON_ONCE(!pmd_none(*new_pmd)))
		वापस false;

	/*
	 * We करोn't have to worry about the ordering of src and dst
	 * ptlocks because exclusive mmap_lock prevents deadlock.
	 */
	old_ptl = pmd_lock(vma->vm_mm, old_pmd);
	new_ptl = pmd_lockptr(mm, new_pmd);
	अगर (new_ptl != old_ptl)
		spin_lock_nested(new_ptl, SINGLE_DEPTH_NESTING);

	/* Clear the pmd */
	pmd = *old_pmd;
	pmd_clear(old_pmd);

	VM_BUG_ON(!pmd_none(*new_pmd));

	/* Set the new pmd */
	set_pmd_at(mm, new_addr, new_pmd, pmd);
	flush_tlb_range(vma, old_addr, old_addr + PMD_SIZE);
	अगर (new_ptl != old_ptl)
		spin_unlock(new_ptl);
	spin_unlock(old_ptl);

	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool move_normal_pmd(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ new_addr, pmd_t *old_pmd,
		pmd_t *new_pmd)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_MOVE_PUD
अटल bool move_normal_pud(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ old_addr,
		  अचिन्हित दीर्घ new_addr, pud_t *old_pud, pud_t *new_pud)
अणु
	spinlock_t *old_ptl, *new_ptl;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pud_t pud;

	/*
	 * The destination pud shouldn't be established, मुक्त_pgtables()
	 * should have released it.
	 */
	अगर (WARN_ON_ONCE(!pud_none(*new_pud)))
		वापस false;

	/*
	 * We करोn't have to worry about the ordering of src and dst
	 * ptlocks because exclusive mmap_lock prevents deadlock.
	 */
	old_ptl = pud_lock(vma->vm_mm, old_pud);
	new_ptl = pud_lockptr(mm, new_pud);
	अगर (new_ptl != old_ptl)
		spin_lock_nested(new_ptl, SINGLE_DEPTH_NESTING);

	/* Clear the pud */
	pud = *old_pud;
	pud_clear(old_pud);

	VM_BUG_ON(!pud_none(*new_pud));

	/* Set the new pud */
	set_pud_at(mm, new_addr, new_pud, pud);
	flush_tlb_range(vma, old_addr, old_addr + PUD_SIZE);
	अगर (new_ptl != old_ptl)
		spin_unlock(new_ptl);
	spin_unlock(old_ptl);

	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool move_normal_pud(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ new_addr, pud_t *old_pud,
		pud_t *new_pud)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

क्रमागत pgt_entry अणु
	NORMAL_PMD,
	HPAGE_PMD,
	NORMAL_PUD,
पूर्ण;

/*
 * Returns an extent of the corresponding size क्रम the pgt_entry specअगरied अगर
 * valid. Else वापसs a smaller extent bounded by the end of the source and
 * destination pgt_entry.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ get_extent(क्रमागत pgt_entry entry,
			अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ old_end,
			अचिन्हित दीर्घ new_addr)
अणु
	अचिन्हित दीर्घ next, extent, mask, size;

	चयन (entry) अणु
	हाल HPAGE_PMD:
	हाल NORMAL_PMD:
		mask = PMD_MASK;
		size = PMD_SIZE;
		अवरोध;
	हाल NORMAL_PUD:
		mask = PUD_MASK;
		size = PUD_SIZE;
		अवरोध;
	शेष:
		BUILD_BUG();
		अवरोध;
	पूर्ण

	next = (old_addr + size) & mask;
	/* even अगर next overflowed, extent below will be ok */
	extent = next - old_addr;
	अगर (extent > old_end - old_addr)
		extent = old_end - old_addr;
	next = (new_addr + size) & mask;
	अगर (extent > next - new_addr)
		extent = next - new_addr;
	वापस extent;
पूर्ण

/*
 * Attempts to speedup the move by moving entry at the level corresponding to
 * pgt_entry. Returns true अगर the move was successful, अन्यथा false.
 */
अटल bool move_pgt_entry(क्रमागत pgt_entry entry, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ new_addr,
			व्योम *old_entry, व्योम *new_entry, bool need_rmap_locks)
अणु
	bool moved = false;

	/* See comment in move_ptes() */
	अगर (need_rmap_locks)
		take_rmap_locks(vma);

	चयन (entry) अणु
	हाल NORMAL_PMD:
		moved = move_normal_pmd(vma, old_addr, new_addr, old_entry,
					new_entry);
		अवरोध;
	हाल NORMAL_PUD:
		moved = move_normal_pud(vma, old_addr, new_addr, old_entry,
					new_entry);
		अवरोध;
	हाल HPAGE_PMD:
		moved = IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) &&
			move_huge_pmd(vma, old_addr, new_addr, old_entry,
				      new_entry);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	अगर (need_rmap_locks)
		drop_rmap_locks(vma);

	वापस moved;
पूर्ण

अचिन्हित दीर्घ move_page_tables(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ old_addr, काष्ठा vm_area_काष्ठा *new_vma,
		अचिन्हित दीर्घ new_addr, अचिन्हित दीर्घ len,
		bool need_rmap_locks)
अणु
	अचिन्हित दीर्घ extent, old_end;
	काष्ठा mmu_notअगरier_range range;
	pmd_t *old_pmd, *new_pmd;

	old_end = old_addr + len;
	flush_cache_range(vma, old_addr, old_end);

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_UNMAP, 0, vma, vma->vm_mm,
				old_addr, old_end);
	mmu_notअगरier_invalidate_range_start(&range);

	क्रम (; old_addr < old_end; old_addr += extent, new_addr += extent) अणु
		cond_resched();
		/*
		 * If extent is PUD-sized try to speed up the move by moving at the
		 * PUD level अगर possible.
		 */
		extent = get_extent(NORMAL_PUD, old_addr, old_end, new_addr);
		अगर (IS_ENABLED(CONFIG_HAVE_MOVE_PUD) && extent == PUD_SIZE) अणु
			pud_t *old_pud, *new_pud;

			old_pud = get_old_pud(vma->vm_mm, old_addr);
			अगर (!old_pud)
				जारी;
			new_pud = alloc_new_pud(vma->vm_mm, vma, new_addr);
			अगर (!new_pud)
				अवरोध;
			अगर (move_pgt_entry(NORMAL_PUD, vma, old_addr, new_addr,
					   old_pud, new_pud, need_rmap_locks))
				जारी;
		पूर्ण

		extent = get_extent(NORMAL_PMD, old_addr, old_end, new_addr);
		old_pmd = get_old_pmd(vma->vm_mm, old_addr);
		अगर (!old_pmd)
			जारी;
		new_pmd = alloc_new_pmd(vma->vm_mm, vma, new_addr);
		अगर (!new_pmd)
			अवरोध;
		अगर (is_swap_pmd(*old_pmd) || pmd_trans_huge(*old_pmd) ||
		    pmd_devmap(*old_pmd)) अणु
			अगर (extent == HPAGE_PMD_SIZE &&
			    move_pgt_entry(HPAGE_PMD, vma, old_addr, new_addr,
					   old_pmd, new_pmd, need_rmap_locks))
				जारी;
			split_huge_pmd(vma, old_pmd, old_addr);
			अगर (pmd_trans_unstable(old_pmd))
				जारी;
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_HAVE_MOVE_PMD) &&
			   extent == PMD_SIZE) अणु
			/*
			 * If the extent is PMD-sized, try to speed the move by
			 * moving at the PMD level अगर possible.
			 */
			अगर (move_pgt_entry(NORMAL_PMD, vma, old_addr, new_addr,
					   old_pmd, new_pmd, need_rmap_locks))
				जारी;
		पूर्ण

		अगर (pte_alloc(new_vma->vm_mm, new_pmd))
			अवरोध;
		move_ptes(vma, old_pmd, old_addr, old_addr + extent, new_vma,
			  new_pmd, new_addr, need_rmap_locks);
	पूर्ण

	mmu_notअगरier_invalidate_range_end(&range);

	वापस len + old_addr - old_end;	/* how much करोne */
पूर्ण

अटल अचिन्हित दीर्घ move_vma(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ old_addr, अचिन्हित दीर्घ old_len,
		अचिन्हित दीर्घ new_len, अचिन्हित दीर्घ new_addr,
		bool *locked, अचिन्हित दीर्घ flags,
		काष्ठा vm_userfaultfd_ctx *uf, काष्ठा list_head *uf_unmap)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा vm_area_काष्ठा *new_vma;
	अचिन्हित दीर्घ vm_flags = vma->vm_flags;
	अचिन्हित दीर्घ new_pgoff;
	अचिन्हित दीर्घ moved_len;
	अचिन्हित दीर्घ excess = 0;
	अचिन्हित दीर्घ hiwater_vm;
	पूर्णांक split = 0;
	पूर्णांक err = 0;
	bool need_rmap_locks;

	/*
	 * We'd prefer to aव्योम failure later on in करो_munmap:
	 * which may split one vma पूर्णांकo three beक्रमe unmapping.
	 */
	अगर (mm->map_count >= sysctl_max_map_count - 3)
		वापस -ENOMEM;

	अगर (vma->vm_ops && vma->vm_ops->may_split) अणु
		अगर (vma->vm_start != old_addr)
			err = vma->vm_ops->may_split(vma, old_addr);
		अगर (!err && vma->vm_end != old_addr + old_len)
			err = vma->vm_ops->may_split(vma, old_addr + old_len);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Advise KSM to अवरोध any KSM pages in the area to be moved:
	 * it would be confusing अगर they were to turn up at the new
	 * location, where they happen to coincide with dअगरferent KSM
	 * pages recently unmapped.  But leave vma->vm_flags as it was,
	 * so KSM can come around to merge on vma and new_vma afterwards.
	 */
	err = ksm_madvise(vma, old_addr, old_addr + old_len,
						MADV_UNMERGEABLE, &vm_flags);
	अगर (err)
		वापस err;

	अगर (unlikely(flags & MREMAP_DONTUNMAP && vm_flags & VM_ACCOUNT)) अणु
		अगर (security_vm_enough_memory_mm(mm, new_len >> PAGE_SHIFT))
			वापस -ENOMEM;
	पूर्ण

	new_pgoff = vma->vm_pgoff + ((old_addr - vma->vm_start) >> PAGE_SHIFT);
	new_vma = copy_vma(&vma, new_addr, new_len, new_pgoff,
			   &need_rmap_locks);
	अगर (!new_vma) अणु
		अगर (unlikely(flags & MREMAP_DONTUNMAP && vm_flags & VM_ACCOUNT))
			vm_unacct_memory(new_len >> PAGE_SHIFT);
		वापस -ENOMEM;
	पूर्ण

	moved_len = move_page_tables(vma, old_addr, new_vma, new_addr, old_len,
				     need_rmap_locks);
	अगर (moved_len < old_len) अणु
		err = -ENOMEM;
	पूर्ण अन्यथा अगर (vma->vm_ops && vma->vm_ops->mremap) अणु
		err = vma->vm_ops->mremap(new_vma);
	पूर्ण

	अगर (unlikely(err)) अणु
		/*
		 * On error, move entries back from new area to old,
		 * which will succeed since page tables still there,
		 * and then proceed to unmap new area instead of old.
		 */
		move_page_tables(new_vma, new_addr, vma, old_addr, moved_len,
				 true);
		vma = new_vma;
		old_len = new_len;
		old_addr = new_addr;
		new_addr = err;
	पूर्ण अन्यथा अणु
		mremap_userfaultfd_prep(new_vma, uf);
	पूर्ण

	/* Conceal VM_ACCOUNT so old reservation is not unकरोne */
	अगर (vm_flags & VM_ACCOUNT && !(flags & MREMAP_DONTUNMAP)) अणु
		vma->vm_flags &= ~VM_ACCOUNT;
		excess = vma->vm_end - vma->vm_start - old_len;
		अगर (old_addr > vma->vm_start &&
		    old_addr + old_len < vma->vm_end)
			split = 1;
	पूर्ण

	/*
	 * If we failed to move page tables we still करो total_vm increment
	 * since करो_munmap() will decrement it by old_len == new_len.
	 *
	 * Since total_vm is about to be उठाओd artअगरicially high क्रम a
	 * moment, we need to restore high watermark afterwards: अगर stats
	 * are taken meanजबतक, total_vm and hiwater_vm appear too high.
	 * If this were a serious issue, we'd add a flag to करो_munmap().
	 */
	hiwater_vm = mm->hiwater_vm;
	vm_stat_account(mm, vma->vm_flags, new_len >> PAGE_SHIFT);

	/* Tell pfnmap has moved from this vma */
	अगर (unlikely(vma->vm_flags & VM_PFNMAP))
		untrack_pfn_moved(vma);

	अगर (unlikely(!err && (flags & MREMAP_DONTUNMAP))) अणु
		/* We always clear VM_LOCKED[ONFAULT] on the old vma */
		vma->vm_flags &= VM_LOCKED_CLEAR_MASK;

		/*
		 * anon_vma links of the old vma is no दीर्घer needed after its page
		 * table has been moved.
		 */
		अगर (new_vma != vma && vma->vm_start == old_addr &&
			vma->vm_end == (old_addr + old_len))
			unlink_anon_vmas(vma);

		/* Because we won't unmap we don't need to touch locked_vm */
		वापस new_addr;
	पूर्ण

	अगर (करो_munmap(mm, old_addr, old_len, uf_unmap) < 0) अणु
		/* OOM: unable to split vma, just get accounts right */
		अगर (vm_flags & VM_ACCOUNT && !(flags & MREMAP_DONTUNMAP))
			vm_acct_memory(new_len >> PAGE_SHIFT);
		excess = 0;
	पूर्ण

	अगर (vm_flags & VM_LOCKED) अणु
		mm->locked_vm += new_len >> PAGE_SHIFT;
		*locked = true;
	पूर्ण

	mm->hiwater_vm = hiwater_vm;

	/* Restore VM_ACCOUNT अगर one or two pieces of vma left */
	अगर (excess) अणु
		vma->vm_flags |= VM_ACCOUNT;
		अगर (split)
			vma->vm_next->vm_flags |= VM_ACCOUNT;
	पूर्ण

	वापस new_addr;
पूर्ण

अटल काष्ठा vm_area_काष्ठा *vma_to_resize(अचिन्हित दीर्घ addr,
	अचिन्हित दीर्घ old_len, अचिन्हित दीर्घ new_len, अचिन्हित दीर्घ flags,
	अचिन्हित दीर्घ *p)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma = find_vma(mm, addr);
	अचिन्हित दीर्घ pgoff;

	अगर (!vma || vma->vm_start > addr)
		वापस ERR_PTR(-EFAULT);

	/*
	 * !old_len is a special हाल where an attempt is made to 'duplicate'
	 * a mapping.  This makes no sense क्रम निजी mappings as it will
	 * instead create a fresh/new mapping unrelated to the original.  This
	 * is contrary to the basic idea of mremap which creates new mappings
	 * based on the original.  There are no known use हालs क्रम this
	 * behavior.  As a result, fail such attempts.
	 */
	अगर (!old_len && !(vma->vm_flags & (VM_SHARED | VM_MAYSHARE))) अणु
		pr_warn_once("%s (%d): attempted to duplicate a private mapping with mremap.  This is not supported.\n", current->comm, current->pid);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर ((flags & MREMAP_DONTUNMAP) &&
			(vma->vm_flags & (VM_DONTEXPAND | VM_PFNMAP)))
		वापस ERR_PTR(-EINVAL);

	अगर (is_vm_hugetlb_page(vma))
		वापस ERR_PTR(-EINVAL);

	/* We can't remap across vm area boundaries */
	अगर (old_len > vma->vm_end - addr)
		वापस ERR_PTR(-EFAULT);

	अगर (new_len == old_len)
		वापस vma;

	/* Need to be careful about a growing mapping */
	pgoff = (addr - vma->vm_start) >> PAGE_SHIFT;
	pgoff += vma->vm_pgoff;
	अगर (pgoff + (new_len >> PAGE_SHIFT) < pgoff)
		वापस ERR_PTR(-EINVAL);

	अगर (vma->vm_flags & (VM_DONTEXPAND | VM_PFNMAP))
		वापस ERR_PTR(-EFAULT);

	अगर (vma->vm_flags & VM_LOCKED) अणु
		अचिन्हित दीर्घ locked, lock_limit;
		locked = mm->locked_vm << PAGE_SHIFT;
		lock_limit = rlimit(RLIMIT_MEMLOCK);
		locked += new_len - old_len;
		अगर (locked > lock_limit && !capable(CAP_IPC_LOCK))
			वापस ERR_PTR(-EAGAIN);
	पूर्ण

	अगर (!may_expand_vm(mm, vma->vm_flags,
				(new_len - old_len) >> PAGE_SHIFT))
		वापस ERR_PTR(-ENOMEM);

	अगर (vma->vm_flags & VM_ACCOUNT) अणु
		अचिन्हित दीर्घ अक्षरged = (new_len - old_len) >> PAGE_SHIFT;
		अगर (security_vm_enough_memory_mm(mm, अक्षरged))
			वापस ERR_PTR(-ENOMEM);
		*p = अक्षरged;
	पूर्ण

	वापस vma;
पूर्ण

अटल अचिन्हित दीर्घ mremap_to(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ old_len,
		अचिन्हित दीर्घ new_addr, अचिन्हित दीर्घ new_len, bool *locked,
		अचिन्हित दीर्घ flags, काष्ठा vm_userfaultfd_ctx *uf,
		काष्ठा list_head *uf_unmap_early,
		काष्ठा list_head *uf_unmap)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ ret = -EINVAL;
	अचिन्हित दीर्घ अक्षरged = 0;
	अचिन्हित दीर्घ map_flags = 0;

	अगर (offset_in_page(new_addr))
		जाओ out;

	अगर (new_len > TASK_SIZE || new_addr > TASK_SIZE - new_len)
		जाओ out;

	/* Ensure the old/new locations करो not overlap */
	अगर (addr + old_len > new_addr && new_addr + new_len > addr)
		जाओ out;

	/*
	 * move_vma() need us to stay 4 maps below the threshold, otherwise
	 * it will bail out at the very beginning.
	 * That is a problem अगर we have alपढ़ोy unmaped the regions here
	 * (new_addr, and old_addr), because userspace will not know the
	 * state of the vma's after it माला_लो -ENOMEM.
	 * So, to aव्योम such scenario we can pre-compute अगर the whole
	 * operation has high chances to success map-wise.
	 * Worst-scenario हाल is when both vma's (new_addr and old_addr) get
	 * split in 3 beक्रमe unmapping it.
	 * That means 2 more maps (1 क्रम each) to the ones we alपढ़ोy hold.
	 * Check whether current map count plus 2 still leads us to 4 maps below
	 * the threshold, otherwise वापस -ENOMEM here to be more safe.
	 */
	अगर ((mm->map_count + 2) >= sysctl_max_map_count - 3)
		वापस -ENOMEM;

	अगर (flags & MREMAP_FIXED) अणु
		ret = करो_munmap(mm, new_addr, new_len, uf_unmap_early);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (old_len >= new_len) अणु
		ret = करो_munmap(mm, addr+new_len, old_len - new_len, uf_unmap);
		अगर (ret && old_len != new_len)
			जाओ out;
		old_len = new_len;
	पूर्ण

	vma = vma_to_resize(addr, old_len, new_len, flags, &अक्षरged);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out;
	पूर्ण

	/* MREMAP_DONTUNMAP expands by old_len since old_len == new_len */
	अगर (flags & MREMAP_DONTUNMAP &&
		!may_expand_vm(mm, vma->vm_flags, old_len >> PAGE_SHIFT)) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (flags & MREMAP_FIXED)
		map_flags |= MAP_FIXED;

	अगर (vma->vm_flags & VM_MAYSHARE)
		map_flags |= MAP_SHARED;

	ret = get_unmapped_area(vma->vm_file, new_addr, new_len, vma->vm_pgoff +
				((addr - vma->vm_start) >> PAGE_SHIFT),
				map_flags);
	अगर (IS_ERR_VALUE(ret))
		जाओ out1;

	/* We got a new mapping */
	अगर (!(flags & MREMAP_FIXED))
		new_addr = ret;

	ret = move_vma(vma, addr, old_len, new_len, new_addr, locked, flags, uf,
		       uf_unmap);

	अगर (!(offset_in_page(ret)))
		जाओ out;

out1:
	vm_unacct_memory(अक्षरged);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक vma_expandable(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ delta)
अणु
	अचिन्हित दीर्घ end = vma->vm_end + delta;
	अगर (end < vma->vm_end) /* overflow */
		वापस 0;
	अगर (vma->vm_next && vma->vm_next->vm_start < end) /* पूर्णांकersection */
		वापस 0;
	अगर (get_unmapped_area(शून्य, vma->vm_start, end - vma->vm_start,
			      0, MAP_FIXED) & ~PAGE_MASK)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Expand (or shrink) an existing mapping, potentially moving it at the
 * same समय (controlled by the MREMAP_MAYMOVE flag and available VM space)
 *
 * MREMAP_FIXED option added 5-Dec-1999 by Benjamin LaHaise
 * This option implies MREMAP_MAYMOVE.
 */
SYSCALL_DEFINE5(mremap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, old_len,
		अचिन्हित दीर्घ, new_len, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, new_addr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ ret = -EINVAL;
	अचिन्हित दीर्घ अक्षरged = 0;
	bool locked = false;
	bool करोwngraded = false;
	काष्ठा vm_userfaultfd_ctx uf = शून्य_VM_UFFD_CTX;
	LIST_HEAD(uf_unmap_early);
	LIST_HEAD(uf_unmap);

	/*
	 * There is a deliberate asymmetry here: we strip the poपूर्णांकer tag
	 * from the old address but leave the new address alone. This is
	 * क्रम consistency with mmap(), where we prevent the creation of
	 * aliasing mappings in userspace by leaving the tag bits of the
	 * mapping address पूर्णांकact. A non-zero tag will cause the subsequent
	 * range checks to reject the address as invalid.
	 *
	 * See Documentation/arm64/tagged-address-abi.rst क्रम more inक्रमmation.
	 */
	addr = untagged_addr(addr);

	अगर (flags & ~(MREMAP_FIXED | MREMAP_MAYMOVE | MREMAP_DONTUNMAP))
		वापस ret;

	अगर (flags & MREMAP_FIXED && !(flags & MREMAP_MAYMOVE))
		वापस ret;

	/*
	 * MREMAP_DONTUNMAP is always a move and it करोes not allow resizing
	 * in the process.
	 */
	अगर (flags & MREMAP_DONTUNMAP &&
			(!(flags & MREMAP_MAYMOVE) || old_len != new_len))
		वापस ret;


	अगर (offset_in_page(addr))
		वापस ret;

	old_len = PAGE_ALIGN(old_len);
	new_len = PAGE_ALIGN(new_len);

	/*
	 * We allow a zero old-len as a special हाल
	 * क्रम DOS-emu "duplicate shm area" thing. But
	 * a zero new-len is nonsensical.
	 */
	अगर (!new_len)
		वापस ret;

	अगर (mmap_ग_लिखो_lock_समाप्तable(current->mm))
		वापस -EINTR;

	अगर (flags & (MREMAP_FIXED | MREMAP_DONTUNMAP)) अणु
		ret = mremap_to(addr, old_len, new_addr, new_len,
				&locked, flags, &uf, &uf_unmap_early,
				&uf_unmap);
		जाओ out;
	पूर्ण

	/*
	 * Always allow a shrinking remap: that just unmaps
	 * the unnecessary pages..
	 * __करो_munmap करोes all the needed commit accounting, and
	 * करोwngrades mmap_lock to पढ़ो अगर so directed.
	 */
	अगर (old_len >= new_len) अणु
		पूर्णांक retval;

		retval = __करो_munmap(mm, addr+new_len, old_len - new_len,
				  &uf_unmap, true);
		अगर (retval < 0 && old_len != new_len) अणु
			ret = retval;
			जाओ out;
		/* Returning 1 indicates mmap_lock is करोwngraded to पढ़ो. */
		पूर्ण अन्यथा अगर (retval == 1)
			करोwngraded = true;
		ret = addr;
		जाओ out;
	पूर्ण

	/*
	 * Ok, we need to grow..
	 */
	vma = vma_to_resize(addr, old_len, new_len, flags, &अक्षरged);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out;
	पूर्ण

	/* old_len exactly to the end of the area..
	 */
	अगर (old_len == vma->vm_end - addr) अणु
		/* can we just expand the current mapping? */
		अगर (vma_expandable(vma, new_len - old_len)) अणु
			पूर्णांक pages = (new_len - old_len) >> PAGE_SHIFT;

			अगर (vma_adjust(vma, vma->vm_start, addr + new_len,
				       vma->vm_pgoff, शून्य)) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			vm_stat_account(mm, vma->vm_flags, pages);
			अगर (vma->vm_flags & VM_LOCKED) अणु
				mm->locked_vm += pages;
				locked = true;
				new_addr = addr;
			पूर्ण
			ret = addr;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We weren't able to just expand or shrink the area,
	 * we need to create a new one and move it..
	 */
	ret = -ENOMEM;
	अगर (flags & MREMAP_MAYMOVE) अणु
		अचिन्हित दीर्घ map_flags = 0;
		अगर (vma->vm_flags & VM_MAYSHARE)
			map_flags |= MAP_SHARED;

		new_addr = get_unmapped_area(vma->vm_file, 0, new_len,
					vma->vm_pgoff +
					((addr - vma->vm_start) >> PAGE_SHIFT),
					map_flags);
		अगर (IS_ERR_VALUE(new_addr)) अणु
			ret = new_addr;
			जाओ out;
		पूर्ण

		ret = move_vma(vma, addr, old_len, new_len, new_addr,
			       &locked, flags, &uf, &uf_unmap);
	पूर्ण
out:
	अगर (offset_in_page(ret)) अणु
		vm_unacct_memory(अक्षरged);
		locked = false;
	पूर्ण
	अगर (करोwngraded)
		mmap_पढ़ो_unlock(current->mm);
	अन्यथा
		mmap_ग_लिखो_unlock(current->mm);
	अगर (locked && new_len > old_len)
		mm_populate(new_addr + old_len, new_len - old_len);
	userfaultfd_unmap_complete(mm, &uf_unmap_early);
	mremap_userfaultfd_complete(&uf, addr, ret, old_len);
	userfaultfd_unmap_complete(mm, &uf_unmap);
	वापस ret;
पूर्ण
