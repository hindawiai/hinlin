<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम flushing entries from the
 * TLB and MMU hash table.
 *
 *  Derived from arch/ppc64/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Dave Engebretsen <engebret@us.ibm.com>
 *      Rework क्रम PPC64 port.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/pte-walk.h>


#समावेश <trace/events/thp.h>

DEFINE_PER_CPU(काष्ठा ppc64_tlb_batch, ppc64_tlb_batch);

/*
 * A linux PTE was changed and the corresponding hash table entry
 * neesd to be flushed. This function will either perक्रमm the flush
 * immediately or will batch it up अगर the current CPU has an active
 * batch on it.
 */
व्योम hpte_need_flush(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, अचिन्हित दीर्घ pte, पूर्णांक huge)
अणु
	अचिन्हित दीर्घ vpn;
	काष्ठा ppc64_tlb_batch *batch = &get_cpu_var(ppc64_tlb_batch);
	अचिन्हित दीर्घ vsid;
	अचिन्हित पूर्णांक psize;
	पूर्णांक ssize;
	real_pte_t rpte;
	पूर्णांक i, offset;

	i = batch->index;

	/*
	 * Get page size (maybe move back to caller).
	 *
	 * NOTE: when using special 64K mappings in 4K environment like
	 * क्रम SPEs, we obtain the page size from the slice, which thus
	 * must still exist (and thus the VMA not reused) at the समय
	 * of this call
	 */
	अगर (huge) अणु
#अगर_घोषित CONFIG_HUGETLB_PAGE
		psize = get_slice_psize(mm, addr);
		/* Mask the address क्रम the correct page size */
		addr &= ~((1UL << mmu_psize_defs[psize].shअगरt) - 1);
		अगर (unlikely(psize == MMU_PAGE_16G))
			offset = PTRS_PER_PUD;
		अन्यथा
			offset = PTRS_PER_PMD;
#अन्यथा
		BUG();
		psize = pte_pagesize_index(mm, addr, pte); /* shutup gcc */
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		psize = pte_pagesize_index(mm, addr, pte);
		/*
		 * Mask the address क्रम the standard page size.  If we
		 * have a 64k page kernel, but the hardware करोes not
		 * support 64k pages, this might be dअगरferent from the
		 * hardware page size encoded in the slice table.
		 */
		addr &= PAGE_MASK;
		offset = PTRS_PER_PTE;
	पूर्ण


	/* Build full vaddr */
	अगर (!is_kernel_addr(addr)) अणु
		ssize = user_segment_size(addr);
		vsid = get_user_vsid(&mm->context, addr, ssize);
	पूर्ण अन्यथा अणु
		vsid = get_kernel_vsid(addr, mmu_kernel_ssize);
		ssize = mmu_kernel_ssize;
	पूर्ण
	WARN_ON(vsid == 0);
	vpn = hpt_vpn(addr, vsid, ssize);
	rpte = __real_pte(__pte(pte), ptep, offset);

	/*
	 * Check अगर we have an active batch on this CPU. If not, just
	 * flush now and वापस.
	 */
	अगर (!batch->active) अणु
		flush_hash_page(vpn, rpte, psize, ssize, mm_is_thपढ़ो_local(mm));
		put_cpu_var(ppc64_tlb_batch);
		वापस;
	पूर्ण

	/*
	 * This can happen when we are in the middle of a TLB batch and
	 * we encounter memory pressure (eg copy_page_range when it tries
	 * to allocate a new pte). If we have to reclaim memory and end
	 * up scanning and resetting referenced bits then our batch context
	 * will change mid stream.
	 *
	 * We also need to ensure only one page size is present in a given
	 * batch
	 */
	अगर (i != 0 && (mm != batch->mm || batch->psize != psize ||
		       batch->ssize != ssize)) अणु
		__flush_tlb_pending(batch);
		i = 0;
	पूर्ण
	अगर (i == 0) अणु
		batch->mm = mm;
		batch->psize = psize;
		batch->ssize = ssize;
	पूर्ण
	batch->pte[i] = rpte;
	batch->vpn[i] = vpn;
	batch->index = ++i;
	अगर (i >= PPC64_TLB_BATCH_NR)
		__flush_tlb_pending(batch);
	put_cpu_var(ppc64_tlb_batch);
पूर्ण

/*
 * This function is called when terminating an mmu batch or when a batch
 * is full. It will perक्रमm the flush of all the entries currently stored
 * in a batch.
 *
 * Must be called from within some kind of spinlock/non-preempt region...
 */
व्योम __flush_tlb_pending(काष्ठा ppc64_tlb_batch *batch)
अणु
	पूर्णांक i, local;

	i = batch->index;
	local = mm_is_thपढ़ो_local(batch->mm);
	अगर (i == 1)
		flush_hash_page(batch->vpn[0], batch->pte[0],
				batch->psize, batch->ssize, local);
	अन्यथा
		flush_hash_range(i, local);
	batch->index = 0;
पूर्ण

व्योम hash__tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	काष्ठा ppc64_tlb_batch *tlbbatch = &get_cpu_var(ppc64_tlb_batch);

	/*
	 * If there's a TLB batch pending, then we must flush it because the
	 * pages are going to be मुक्तd and we really करोn't want to have a CPU
	 * access a मुक्तd page because it has a stale TLB
	 */
	अगर (tlbbatch->index)
		__flush_tlb_pending(tlbbatch);

	put_cpu_var(ppc64_tlb_batch);
पूर्ण

/**
 * __flush_hash_table_range - Flush all HPTEs क्रम a given address range
 *                            from the hash table (and the TLB). But keeps
 *                            the linux PTEs पूर्णांकact.
 *
 * @start	: starting address
 * @end         : ending address (not included in the flush)
 *
 * This function is mostly to be used by some IO hotplug code in order
 * to हटाओ all hash entries from a given address range used to map IO
 * space on a हटाओd PCI-PCI bidge without tearing करोwn the full mapping
 * since 64K pages may overlap with other bridges when using 64K pages
 * with 4K HW pages on IO space.
 *
 * Because of that usage pattern, it is implemented क्रम small size rather
 * than speed.
 */
व्योम __flush_hash_table_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक hugepage_shअगरt;
	अचिन्हित दीर्घ flags;

	start = ALIGN_DOWN(start, PAGE_SIZE);
	end = ALIGN(end, PAGE_SIZE);


	/*
	 * Note: Normally, we should only ever use a batch within a
	 * PTE locked section. This violates the rule, but will work
	 * since we करोn't actually modअगरy the PTEs, we just flush the
	 * hash जबतक leaving the PTEs पूर्णांकact (including their reference
	 * to being hashed). This is not the most perक्रमmance oriented
	 * way to करो things but is fine क्रम our needs here.
	 */
	local_irq_save(flags);
	arch_enter_lazy_mmu_mode();
	क्रम (; start < end; start += PAGE_SIZE) अणु
		pte_t *ptep = find_init_mm_pte(start, &hugepage_shअगरt);
		अचिन्हित दीर्घ pte;

		अगर (ptep == शून्य)
			जारी;
		pte = pte_val(*ptep);
		अगर (!(pte & H_PAGE_HASHPTE))
			जारी;
		hpte_need_flush(&init_mm, start, ptep, pte, hugepage_shअगरt);
	पूर्ण
	arch_leave_lazy_mmu_mode();
	local_irq_restore(flags);
पूर्ण

व्योम flush_tlb_pmd_range(काष्ठा mm_काष्ठा *mm, pmd_t *pmd, अचिन्हित दीर्घ addr)
अणु
	pte_t *pte;
	pte_t *start_pte;
	अचिन्हित दीर्घ flags;

	addr = ALIGN_DOWN(addr, PMD_SIZE);
	/*
	 * Note: Normally, we should only ever use a batch within a
	 * PTE locked section. This violates the rule, but will work
	 * since we करोn't actually modअगरy the PTEs, we just flush the
	 * hash जबतक leaving the PTEs पूर्णांकact (including their reference
	 * to being hashed). This is not the most perक्रमmance oriented
	 * way to करो things but is fine क्रम our needs here.
	 */
	local_irq_save(flags);
	arch_enter_lazy_mmu_mode();
	start_pte = pte_offset_map(pmd, addr);
	क्रम (pte = start_pte; pte < start_pte + PTRS_PER_PTE; pte++) अणु
		अचिन्हित दीर्घ pteval = pte_val(*pte);
		अगर (pteval & H_PAGE_HASHPTE)
			hpte_need_flush(mm, addr, pte, pteval, 0);
		addr += PAGE_SIZE;
	पूर्ण
	arch_leave_lazy_mmu_mode();
	local_irq_restore(flags);
पूर्ण
