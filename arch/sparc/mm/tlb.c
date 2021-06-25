<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* arch/sparc64/mm/tlb.c
 *
 * Copyright (C) 2004 David S. Miller <davem@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/preempt.h>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlb.h>

/* Heavily inspired by the ppc64 code.  */

अटल DEFINE_PER_CPU(काष्ठा tlb_batch, tlb_batch);

व्योम flush_tlb_pending(व्योम)
अणु
	काष्ठा tlb_batch *tb = &get_cpu_var(tlb_batch);
	काष्ठा mm_काष्ठा *mm = tb->mm;

	अगर (!tb->tlb_nr)
		जाओ out;

	flush_tsb_user(tb);

	अगर (CTX_VALID(mm->context)) अणु
		अगर (tb->tlb_nr == 1) अणु
			global_flush_tlb_page(mm, tb->vaddrs[0]);
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_SMP
			smp_flush_tlb_pending(tb->mm, tb->tlb_nr,
					      &tb->vaddrs[0]);
#अन्यथा
			__flush_tlb_pending(CTX_HWBITS(tb->mm->context),
					    tb->tlb_nr, &tb->vaddrs[0]);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	tb->tlb_nr = 0;

out:
	put_cpu_var(tlb_batch);
पूर्ण

व्योम arch_enter_lazy_mmu_mode(व्योम)
अणु
	काष्ठा tlb_batch *tb = this_cpu_ptr(&tlb_batch);

	tb->active = 1;
पूर्ण

व्योम arch_leave_lazy_mmu_mode(व्योम)
अणु
	काष्ठा tlb_batch *tb = this_cpu_ptr(&tlb_batch);

	अगर (tb->tlb_nr)
		flush_tlb_pending();
	tb->active = 0;
पूर्ण

अटल व्योम tlb_batch_add_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
			      bool exec, अचिन्हित पूर्णांक hugepage_shअगरt)
अणु
	काष्ठा tlb_batch *tb = &get_cpu_var(tlb_batch);
	अचिन्हित दीर्घ nr;

	vaddr &= PAGE_MASK;
	अगर (exec)
		vaddr |= 0x1UL;

	nr = tb->tlb_nr;

	अगर (unlikely(nr != 0 && mm != tb->mm)) अणु
		flush_tlb_pending();
		nr = 0;
	पूर्ण

	अगर (!tb->active) अणु
		flush_tsb_user_page(mm, vaddr, hugepage_shअगरt);
		global_flush_tlb_page(mm, vaddr);
		जाओ out;
	पूर्ण

	अगर (nr == 0) अणु
		tb->mm = mm;
		tb->hugepage_shअगरt = hugepage_shअगरt;
	पूर्ण

	अगर (tb->hugepage_shअगरt != hugepage_shअगरt) अणु
		flush_tlb_pending();
		tb->hugepage_shअगरt = hugepage_shअगरt;
		nr = 0;
	पूर्ण

	tb->vaddrs[nr] = vaddr;
	tb->tlb_nr = ++nr;
	अगर (nr >= TLB_BATCH_NR)
		flush_tlb_pending();

out:
	put_cpu_var(tlb_batch);
पूर्ण

व्योम tlb_batch_add(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
		   pte_t *ptep, pte_t orig, पूर्णांक fullmm,
		   अचिन्हित पूर्णांक hugepage_shअगरt)
अणु
	अगर (tlb_type != hypervisor &&
	    pte_dirty(orig)) अणु
		अचिन्हित दीर्घ paddr, pfn = pte_pfn(orig);
		काष्ठा address_space *mapping;
		काष्ठा page *page;

		अगर (!pfn_valid(pfn))
			जाओ no_cache_flush;

		page = pfn_to_page(pfn);
		अगर (PageReserved(page))
			जाओ no_cache_flush;

		/* A real file page? */
		mapping = page_mapping_file(page);
		अगर (!mapping)
			जाओ no_cache_flush;

		paddr = (अचिन्हित दीर्घ) page_address(page);
		अगर ((paddr ^ vaddr) & (1 << 13))
			flush_dcache_page_all(mm, page);
	पूर्ण

no_cache_flush:
	अगर (!fullmm)
		tlb_batch_add_one(mm, vaddr, pte_exec(orig), hugepage_shअगरt);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम tlb_batch_pmd_scan(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
			       pmd_t pmd)
अणु
	अचिन्हित दीर्घ end;
	pte_t *pte;

	pte = pte_offset_map(&pmd, vaddr);
	end = vaddr + HPAGE_SIZE;
	जबतक (vaddr < end) अणु
		अगर (pte_val(*pte) & _PAGE_VALID) अणु
			bool exec = pte_exec(*pte);

			tlb_batch_add_one(mm, vaddr, exec, PAGE_SHIFT);
		पूर्ण
		pte++;
		vaddr += PAGE_SIZE;
	पूर्ण
	pte_unmap(pte);
पूर्ण


अटल व्योम __set_pmd_acct(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			   pmd_t orig, pmd_t pmd)
अणु
	अगर (mm == &init_mm)
		वापस;

	अगर ((pmd_val(pmd) ^ pmd_val(orig)) & _PAGE_PMD_HUGE) अणु
		/*
		 * Note that this routine only sets pmds क्रम THP pages.
		 * Hugetlb pages are handled अन्यथाwhere.  We need to check
		 * क्रम huge zero page.  Huge zero pages are like hugetlb
		 * pages in that there is no RSS, but there is the need
		 * क्रम TSB entries.  So, huge zero page counts go पूर्णांकo
		 * hugetlb_pte_count.
		 */
		अगर (pmd_val(pmd) & _PAGE_PMD_HUGE) अणु
			अगर (is_huge_zero_page(pmd_page(pmd)))
				mm->context.hugetlb_pte_count++;
			अन्यथा
				mm->context.thp_pte_count++;
		पूर्ण अन्यथा अणु
			अगर (is_huge_zero_page(pmd_page(orig)))
				mm->context.hugetlb_pte_count--;
			अन्यथा
				mm->context.thp_pte_count--;
		पूर्ण

		/* Do not try to allocate the TSB hash table अगर we
		 * करोn't have one alपढ़ोy.  We have various locks held
		 * and thus we'll end up करोing a GFP_KERNEL allocation
		 * in an atomic context.
		 *
		 * Instead, we let the first TLB miss on a hugepage
		 * take care of this.
		 */
	पूर्ण

	अगर (!pmd_none(orig)) अणु
		addr &= HPAGE_MASK;
		अगर (pmd_trans_huge(orig)) अणु
			pte_t orig_pte = __pte(pmd_val(orig));
			bool exec = pte_exec(orig_pte);

			tlb_batch_add_one(mm, addr, exec, REAL_HPAGE_SHIFT);
			tlb_batch_add_one(mm, addr + REAL_HPAGE_SIZE, exec,
					  REAL_HPAGE_SHIFT);
		पूर्ण अन्यथा अणु
			tlb_batch_pmd_scan(mm, addr, orig);
		पूर्ण
	पूर्ण
पूर्ण

व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		pmd_t *pmdp, pmd_t pmd)
अणु
	pmd_t orig = *pmdp;

	*pmdp = pmd;
	__set_pmd_acct(mm, addr, orig, pmd);
पूर्ण

अटल अंतरभूत pmd_t pmdp_establish(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, pmd_t *pmdp, pmd_t pmd)
अणु
	pmd_t old;

	करो अणु
		old = *pmdp;
	पूर्ण जबतक (cmpxchg64(&pmdp->pmd, old.pmd, pmd.pmd) != old.pmd);
	__set_pmd_acct(vma->vm_mm, address, old, pmd);

	वापस old;
पूर्ण

/*
 * This routine is only called when splitting a THP
 */
pmd_t pmdp_invalidate(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		     pmd_t *pmdp)
अणु
	pmd_t old, entry;

	entry = __pmd(pmd_val(*pmdp) & ~_PAGE_VALID);
	old = pmdp_establish(vma, address, pmdp, entry);
	flush_tlb_range(vma, address, address + HPAGE_PMD_SIZE);

	/*
	 * set_pmd_at() will not be called in a way to decrement
	 * thp_pte_count when splitting a THP, so करो it now.
	 * Sanity check pmd beक्रमe करोing the actual decrement.
	 */
	अगर ((pmd_val(entry) & _PAGE_PMD_HUGE) &&
	    !is_huge_zero_page(pmd_page(entry)))
		(vma->vm_mm)->context.thp_pte_count--;

	वापस old;
पूर्ण

व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				pgtable_t pgtable)
अणु
	काष्ठा list_head *lh = (काष्ठा list_head *) pgtable;

	निश्चित_spin_locked(&mm->page_table_lock);

	/* FIFO */
	अगर (!pmd_huge_pte(mm, pmdp))
		INIT_LIST_HEAD(lh);
	अन्यथा
		list_add(lh, (काष्ठा list_head *) pmd_huge_pte(mm, pmdp));
	pmd_huge_pte(mm, pmdp) = pgtable;
पूर्ण

pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp)
अणु
	काष्ठा list_head *lh;
	pgtable_t pgtable;

	निश्चित_spin_locked(&mm->page_table_lock);

	/* FIFO */
	pgtable = pmd_huge_pte(mm, pmdp);
	lh = (काष्ठा list_head *) pgtable;
	अगर (list_empty(lh))
		pmd_huge_pte(mm, pmdp) = शून्य;
	अन्यथा अणु
		pmd_huge_pte(mm, pmdp) = (pgtable_t) lh->next;
		list_del(lh);
	पूर्ण
	pte_val(pgtable[0]) = 0;
	pte_val(pgtable[1]) = 0;

	वापस pgtable;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
