<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* include/यंत्र-generic/tlb.h
 *
 *	Generic TLB shootकरोwn code
 *
 * Copyright 2001 Red Hat, Inc.
 * Based on code from mm/memory.c Copyright Linus Torvalds and others.
 *
 * Copyright 2011 Red Hat, Inc., Peter Zijlstra
 */
#अगर_अघोषित _ASM_GENERIC__TLB_H
#घोषणा _ASM_GENERIC__TLB_H

#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/swap.h>
#समावेश <linux/hugetlb_अंतरभूत.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * Blindly accessing user memory from NMI context can be dangerous
 * अगर we're in the middle of चयनing the current user task or चयनing
 * the loaded mm.
 */
#अगर_अघोषित nmi_uaccess_okay
# define nmi_uaccess_okay() true
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU

/*
 * Generic MMU-gather implementation.
 *
 * The mmu_gather data काष्ठाure is used by the mm code to implement the
 * correct and efficient ordering of मुक्तing pages and TLB invalidations.
 *
 * This correct ordering is:
 *
 *  1) unhook page
 *  2) TLB invalidate page
 *  3) मुक्त page
 *
 * That is, we must never मुक्त a page beक्रमe we have ensured there are no live
 * translations left to it. Otherwise it might be possible to observe (or
 * worse, change) the page content after it has been reused.
 *
 * The mmu_gather API consists of:
 *
 *  - tlb_gather_mmu() / tlb_gather_mmu_fullmm() / tlb_finish_mmu()
 *
 *    start and finish a mmu_gather
 *
 *    Finish in particular will issue a (final) TLB invalidate and मुक्त
 *    all (reमुख्यing) queued pages.
 *
 *  - tlb_start_vma() / tlb_end_vma(); marks the start / end of a VMA
 *
 *    Defaults to flushing at tlb_end_vma() to reset the range; helps when
 *    there's large holes between the VMAs.
 *
 *  - tlb_हटाओ_table()
 *
 *    tlb_हटाओ_table() is the basic primitive to मुक्त page-table directories
 *    (__p*_मुक्त_tlb()).  In it's most primitive क्रमm it is an alias क्रम
 *    tlb_हटाओ_page() below, क्रम when page directories are pages and have no
 *    additional स्थिरraपूर्णांकs.
 *
 *    See also MMU_GATHER_TABLE_FREE and MMU_GATHER_RCU_TABLE_FREE.
 *
 *  - tlb_हटाओ_page() / __tlb_हटाओ_page()
 *  - tlb_हटाओ_page_size() / __tlb_हटाओ_page_size()
 *
 *    __tlb_हटाओ_page_size() is the basic primitive that queues a page क्रम
 *    मुक्तing. __tlb_हटाओ_page() assumes PAGE_SIZE. Both will वापस a
 *    boolean indicating अगर the queue is (now) full and a call to
 *    tlb_flush_mmu() is required.
 *
 *    tlb_हटाओ_page() and tlb_हटाओ_page_size() imply the call to
 *    tlb_flush_mmu() when required and has no वापस value.
 *
 *  - tlb_change_page_size()
 *
 *    call beक्रमe __tlb_हटाओ_page*() to set the current page-size; implies a
 *    possible tlb_flush_mmu() call.
 *
 *  - tlb_flush_mmu() / tlb_flush_mmu_tlbonly()
 *
 *    tlb_flush_mmu_tlbonly() - करोes the TLB invalidate (and resets
 *                              related state, like the range)
 *
 *    tlb_flush_mmu() - in addition to the above TLB invalidate, also मुक्तs
 *			whatever pages are still batched.
 *
 *  - mmu_gather::fullmm
 *
 *    A flag set by tlb_gather_mmu_fullmm() to indicate we're going to मुक्त
 *    the entire mm; this allows a number of optimizations.
 *
 *    - We can ignore tlb_अणुstart,endपूर्ण_vma(); because we करोn't
 *      care about ranges. Everything will be shot करोwn.
 *
 *    - (RISC) architectures that use ASIDs can cycle to a new ASID
 *      and delay the invalidation until ASID space runs out.
 *
 *  - mmu_gather::need_flush_all
 *
 *    A flag that can be set by the arch code अगर it wants to क्रमce
 *    flush the entire TLB irrespective of the range. For instance
 *    x86-PAE needs this when changing top-level entries.
 *
 * And allows the architecture to provide and implement tlb_flush():
 *
 * tlb_flush() may, in addition to the above mentioned mmu_gather fields, make
 * use of:
 *
 *  - mmu_gather::start / mmu_gather::end
 *
 *    which provides the range that needs to be flushed to cover the pages to
 *    be मुक्तd.
 *
 *  - mmu_gather::मुक्तd_tables
 *
 *    set when we मुक्तd page table pages
 *
 *  - tlb_get_unmap_shअगरt() / tlb_get_unmap_size()
 *
 *    वापसs the smallest TLB entry size unmapped in this range.
 *
 * If an architecture करोes not provide tlb_flush() a शेष implementation
 * based on flush_tlb_range() will be used, unless MMU_GATHER_NO_RANGE is
 * specअगरied, in which हाल we'll शेष to flush_tlb_mm().
 *
 * Additionally there are a few opt-in features:
 *
 *  MMU_GATHER_PAGE_SIZE
 *
 *  This ensures we call tlb_flush() every समय tlb_change_page_size() actually
 *  changes the size and provides mmu_gather::page_size to tlb_flush().
 *
 *  This might be useful अगर your architecture has size specअगरic TLB
 *  invalidation inकाष्ठाions.
 *
 *  MMU_GATHER_TABLE_FREE
 *
 *  This provides tlb_हटाओ_table(), to be used instead of tlb_हटाओ_page()
 *  क्रम page directores (__p*_मुक्त_tlb()).
 *
 *  Useful अगर your architecture has non-page page directories.
 *
 *  When used, an architecture is expected to provide __tlb_हटाओ_table()
 *  which करोes the actual मुक्तing of these pages.
 *
 *  MMU_GATHER_RCU_TABLE_FREE
 *
 *  Like MMU_GATHER_TABLE_FREE, and adds semi-RCU semantics to the मुक्त (see
 *  comment below).
 *
 *  Useful अगर your architecture करोesn't use IPIs क्रम remote TLB invalidates
 *  and thereक्रमe करोesn't naturally serialize with software page-table walkers.
 *
 *  MMU_GATHER_NO_RANGE
 *
 *  Use this अगर your architecture lacks an efficient flush_tlb_range().
 *
 *  MMU_GATHER_NO_GATHER
 *
 *  If the option is set the mmu_gather will not track inभागidual pages क्रम
 *  delayed page मुक्त anymore. A platक्रमm that enables the option needs to
 *  provide its own implementation of the __tlb_हटाओ_page_size() function to
 *  मुक्त pages.
 *
 *  This is useful अगर your architecture alपढ़ोy flushes TLB entries in the
 *  various ptep_get_and_clear() functions.
 */

#अगर_घोषित CONFIG_MMU_GATHER_TABLE_FREE

काष्ठा mmu_table_batch अणु
#अगर_घोषित CONFIG_MMU_GATHER_RCU_TABLE_FREE
	काष्ठा rcu_head		rcu;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		nr;
	व्योम			*tables[0];
पूर्ण;

#घोषणा MAX_TABLE_BATCH		\
	((PAGE_SIZE - माप(काष्ठा mmu_table_batch)) / माप(व्योम *))

बाह्य व्योम tlb_हटाओ_table(काष्ठा mmu_gather *tlb, व्योम *table);

#अन्यथा /* !CONFIG_MMU_GATHER_HAVE_TABLE_FREE */

/*
 * Without MMU_GATHER_TABLE_FREE the architecture is assumed to have page based
 * page directories and we can use the normal page batching to मुक्त them.
 */
#घोषणा tlb_हटाओ_table(tlb, page) tlb_हटाओ_page((tlb), (page))

#पूर्ण_अगर /* CONFIG_MMU_GATHER_TABLE_FREE */

#अगर_घोषित CONFIG_MMU_GATHER_RCU_TABLE_FREE
/*
 * This allows an architecture that करोes not use the linux page-tables क्रम
 * hardware to skip the TLBI when मुक्तing page tables.
 */
#अगर_अघोषित tlb_needs_table_invalidate
#घोषणा tlb_needs_table_invalidate() (true)
#पूर्ण_अगर

#अन्यथा

#अगर_घोषित tlb_needs_table_invalidate
#त्रुटि tlb_needs_table_invalidate() requires MMU_GATHER_RCU_TABLE_FREE
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MMU_GATHER_RCU_TABLE_FREE */


#अगर_अघोषित CONFIG_MMU_GATHER_NO_GATHER
/*
 * If we can't allocate a page to make a big batch of page poपूर्णांकers
 * to work on, then just handle a few from the on-stack काष्ठाure.
 */
#घोषणा MMU_GATHER_BUNDLE	8

काष्ठा mmu_gather_batch अणु
	काष्ठा mmu_gather_batch	*next;
	अचिन्हित पूर्णांक		nr;
	अचिन्हित पूर्णांक		max;
	काष्ठा page		*pages[0];
पूर्ण;

#घोषणा MAX_GATHER_BATCH	\
	((PAGE_SIZE - माप(काष्ठा mmu_gather_batch)) / माप(व्योम *))

/*
 * Limit the maximum number of mmu_gather batches to reduce a risk of soft
 * lockups क्रम non-preemptible kernels on huge machines when a lot of memory
 * is zapped during unmapping.
 * 10K pages मुक्तd at once should be safe even without a preemption poपूर्णांक.
 */
#घोषणा MAX_GATHER_BATCH_COUNT	(10000UL/MAX_GATHER_BATCH)

बाह्य bool __tlb_हटाओ_page_size(काष्ठा mmu_gather *tlb, काष्ठा page *page,
				   पूर्णांक page_size);
#पूर्ण_अगर

/*
 * काष्ठा mmu_gather is an opaque type used by the mm code क्रम passing around
 * any data needed by arch specअगरic code क्रम tlb_हटाओ_page.
 */
काष्ठा mmu_gather अणु
	काष्ठा mm_काष्ठा	*mm;

#अगर_घोषित CONFIG_MMU_GATHER_TABLE_FREE
	काष्ठा mmu_table_batch	*batch;
#पूर्ण_अगर

	अचिन्हित दीर्घ		start;
	अचिन्हित दीर्घ		end;
	/*
	 * we are in the middle of an operation to clear
	 * a full mm and can make some optimizations
	 */
	अचिन्हित पूर्णांक		fullmm : 1;

	/*
	 * we have perक्रमmed an operation which
	 * requires a complete flush of the tlb
	 */
	अचिन्हित पूर्णांक		need_flush_all : 1;

	/*
	 * we have हटाओd page directories
	 */
	अचिन्हित पूर्णांक		मुक्तd_tables : 1;

	/*
	 * at which levels have we cleared entries?
	 */
	अचिन्हित पूर्णांक		cleared_ptes : 1;
	अचिन्हित पूर्णांक		cleared_pmds : 1;
	अचिन्हित पूर्णांक		cleared_puds : 1;
	अचिन्हित पूर्णांक		cleared_p4ds : 1;

	/*
	 * tracks VM_EXEC | VM_HUGETLB in tlb_start_vma
	 */
	अचिन्हित पूर्णांक		vma_exec : 1;
	अचिन्हित पूर्णांक		vma_huge : 1;

	अचिन्हित पूर्णांक		batch_count;

#अगर_अघोषित CONFIG_MMU_GATHER_NO_GATHER
	काष्ठा mmu_gather_batch *active;
	काष्ठा mmu_gather_batch	local;
	काष्ठा page		*__pages[MMU_GATHER_BUNDLE];

#अगर_घोषित CONFIG_MMU_GATHER_PAGE_SIZE
	अचिन्हित पूर्णांक page_size;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

व्योम tlb_flush_mmu(काष्ठा mmu_gather *tlb);

अटल अंतरभूत व्योम __tlb_adjust_range(काष्ठा mmu_gather *tlb,
				      अचिन्हित दीर्घ address,
				      अचिन्हित पूर्णांक range_size)
अणु
	tlb->start = min(tlb->start, address);
	tlb->end = max(tlb->end, address + range_size);
पूर्ण

अटल अंतरभूत व्योम __tlb_reset_range(काष्ठा mmu_gather *tlb)
अणु
	अगर (tlb->fullmm) अणु
		tlb->start = tlb->end = ~0;
	पूर्ण अन्यथा अणु
		tlb->start = TASK_SIZE;
		tlb->end = 0;
	पूर्ण
	tlb->मुक्तd_tables = 0;
	tlb->cleared_ptes = 0;
	tlb->cleared_pmds = 0;
	tlb->cleared_puds = 0;
	tlb->cleared_p4ds = 0;
	/*
	 * Do not reset mmu_gather::vma_* fields here, we करो not
	 * call पूर्णांकo tlb_start_vma() again to set them अगर there is an
	 * पूर्णांकermediate flush.
	 */
पूर्ण

#अगर_घोषित CONFIG_MMU_GATHER_NO_RANGE

#अगर defined(tlb_flush) || defined(tlb_start_vma) || defined(tlb_end_vma)
#त्रुटि MMU_GATHER_NO_RANGE relies on शेष tlb_flush(), tlb_start_vma() and tlb_end_vma()
#पूर्ण_अगर

/*
 * When an architecture करोes not have efficient means of range flushing TLBs
 * there is no poपूर्णांक in करोing पूर्णांकermediate flushes on tlb_end_vma() to keep the
 * range small. We equally करोn't have to worry about page granularity or other
 * things.
 *
 * All we need to करो is issue a full flush क्रम any !0 range.
 */
अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	अगर (tlb->end)
		flush_tlb_mm(tlb->mm);
पूर्ण

अटल अंतरभूत व्योम
tlb_update_vma_flags(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma) अणु पूर्ण

#घोषणा tlb_end_vma tlb_end_vma
अटल अंतरभूत व्योम tlb_end_vma(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma) अणु पूर्ण

#अन्यथा /* CONFIG_MMU_GATHER_NO_RANGE */

#अगर_अघोषित tlb_flush

#अगर defined(tlb_start_vma) || defined(tlb_end_vma)
#त्रुटि Default tlb_flush() relies on शेष tlb_start_vma() and tlb_end_vma()
#पूर्ण_अगर

/*
 * When an architecture करोes not provide its own tlb_flush() implementation
 * but करोes have a reasonably efficient flush_vma_range() implementation
 * use that.
 */
अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	अगर (tlb->fullmm || tlb->need_flush_all) अणु
		flush_tlb_mm(tlb->mm);
	पूर्ण अन्यथा अगर (tlb->end) अणु
		काष्ठा vm_area_काष्ठा vma = अणु
			.vm_mm = tlb->mm,
			.vm_flags = (tlb->vma_exec ? VM_EXEC    : 0) |
				    (tlb->vma_huge ? VM_HUGETLB : 0),
		पूर्ण;

		flush_tlb_range(&vma, tlb->start, tlb->end);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
tlb_update_vma_flags(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * flush_tlb_range() implementations that look at VM_HUGETLB (tile,
	 * mips-4k) flush only large pages.
	 *
	 * flush_tlb_range() implementations that flush I-TLB also flush D-TLB
	 * (tile, xtensa, arm), so it's ok to just add VM_EXEC to an existing
	 * range.
	 *
	 * We rely on tlb_end_vma() to issue a flush, such that when we reset
	 * these values the batch is empty.
	 */
	tlb->vma_huge = is_vm_hugetlb_page(vma);
	tlb->vma_exec = !!(vma->vm_flags & VM_EXEC);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम
tlb_update_vma_flags(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MMU_GATHER_NO_RANGE */

अटल अंतरभूत व्योम tlb_flush_mmu_tlbonly(काष्ठा mmu_gather *tlb)
अणु
	/*
	 * Anything calling __tlb_adjust_range() also sets at least one of
	 * these bits.
	 */
	अगर (!(tlb->मुक्तd_tables || tlb->cleared_ptes || tlb->cleared_pmds ||
	      tlb->cleared_puds || tlb->cleared_p4ds))
		वापस;

	tlb_flush(tlb);
	mmu_notअगरier_invalidate_range(tlb->mm, tlb->start, tlb->end);
	__tlb_reset_range(tlb);
पूर्ण

अटल अंतरभूत व्योम tlb_हटाओ_page_size(काष्ठा mmu_gather *tlb,
					काष्ठा page *page, पूर्णांक page_size)
अणु
	अगर (__tlb_हटाओ_page_size(tlb, page, page_size))
		tlb_flush_mmu(tlb);
पूर्ण

अटल अंतरभूत bool __tlb_हटाओ_page(काष्ठा mmu_gather *tlb, काष्ठा page *page)
अणु
	वापस __tlb_हटाओ_page_size(tlb, page, PAGE_SIZE);
पूर्ण

/* tlb_हटाओ_page
 *	Similar to __tlb_हटाओ_page but will call tlb_flush_mmu() itself when
 *	required.
 */
अटल अंतरभूत व्योम tlb_हटाओ_page(काष्ठा mmu_gather *tlb, काष्ठा page *page)
अणु
	वापस tlb_हटाओ_page_size(tlb, page, PAGE_SIZE);
पूर्ण

अटल अंतरभूत व्योम tlb_change_page_size(काष्ठा mmu_gather *tlb,
						     अचिन्हित पूर्णांक page_size)
अणु
#अगर_घोषित CONFIG_MMU_GATHER_PAGE_SIZE
	अगर (tlb->page_size && tlb->page_size != page_size) अणु
		अगर (!tlb->fullmm && !tlb->need_flush_all)
			tlb_flush_mmu(tlb);
	पूर्ण

	tlb->page_size = page_size;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tlb_get_unmap_shअगरt(काष्ठा mmu_gather *tlb)
अणु
	अगर (tlb->cleared_ptes)
		वापस PAGE_SHIFT;
	अगर (tlb->cleared_pmds)
		वापस PMD_SHIFT;
	अगर (tlb->cleared_puds)
		वापस PUD_SHIFT;
	अगर (tlb->cleared_p4ds)
		वापस P4D_SHIFT;

	वापस PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tlb_get_unmap_size(काष्ठा mmu_gather *tlb)
अणु
	वापस 1UL << tlb_get_unmap_shअगरt(tlb);
पूर्ण

/*
 * In the हाल of tlb vma handling, we can optimise these away in the
 * हाल where we're doing a full MM flush.  When we're करोing a munmap,
 * the vmas are adjusted to only cover the region to be torn करोwn.
 */
#अगर_अघोषित tlb_start_vma
अटल अंतरभूत व्योम tlb_start_vma(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (tlb->fullmm)
		वापस;

	tlb_update_vma_flags(tlb, vma);
	flush_cache_range(vma, vma->vm_start, vma->vm_end);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित tlb_end_vma
अटल अंतरभूत व्योम tlb_end_vma(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (tlb->fullmm)
		वापस;

	/*
	 * Do a TLB flush and reset the range at VMA boundaries; this aव्योमs
	 * the ranges growing with the unused space between consecutive VMAs,
	 * but also the mmu_gather::vma_* flags from tlb_start_vma() rely on
	 * this.
	 */
	tlb_flush_mmu_tlbonly(tlb);
पूर्ण
#पूर्ण_अगर

/*
 * tlb_flush_अणुpte|pmd|pud|p4dपूर्ण_range() adjust the tlb->start and tlb->end,
 * and set corresponding cleared_*.
 */
अटल अंतरभूत व्योम tlb_flush_pte_range(काष्ठा mmu_gather *tlb,
				     अचिन्हित दीर्घ address, अचिन्हित दीर्घ size)
अणु
	__tlb_adjust_range(tlb, address, size);
	tlb->cleared_ptes = 1;
पूर्ण

अटल अंतरभूत व्योम tlb_flush_pmd_range(काष्ठा mmu_gather *tlb,
				     अचिन्हित दीर्घ address, अचिन्हित दीर्घ size)
अणु
	__tlb_adjust_range(tlb, address, size);
	tlb->cleared_pmds = 1;
पूर्ण

अटल अंतरभूत व्योम tlb_flush_pud_range(काष्ठा mmu_gather *tlb,
				     अचिन्हित दीर्घ address, अचिन्हित दीर्घ size)
अणु
	__tlb_adjust_range(tlb, address, size);
	tlb->cleared_puds = 1;
पूर्ण

अटल अंतरभूत व्योम tlb_flush_p4d_range(काष्ठा mmu_gather *tlb,
				     अचिन्हित दीर्घ address, अचिन्हित दीर्घ size)
अणु
	__tlb_adjust_range(tlb, address, size);
	tlb->cleared_p4ds = 1;
पूर्ण

#अगर_अघोषित __tlb_हटाओ_tlb_entry
#घोषणा __tlb_हटाओ_tlb_entry(tlb, ptep, address) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * tlb_हटाओ_tlb_entry - remember a pte unmapping क्रम later tlb invalidation.
 *
 * Record the fact that pte's were really unmapped by updating the range,
 * so we can later optimise away the tlb invalidate.   This helps when
 * userspace is unmapping alपढ़ोy-unmapped pages, which happens quite a lot.
 */
#घोषणा tlb_हटाओ_tlb_entry(tlb, ptep, address)		\
	करो अणु							\
		tlb_flush_pte_range(tlb, address, PAGE_SIZE);	\
		__tlb_हटाओ_tlb_entry(tlb, ptep, address);	\
	पूर्ण जबतक (0)

#घोषणा tlb_हटाओ_huge_tlb_entry(h, tlb, ptep, address)	\
	करो अणु							\
		अचिन्हित दीर्घ _sz = huge_page_size(h);		\
		अगर (_sz == PMD_SIZE)				\
			tlb_flush_pmd_range(tlb, address, _sz);	\
		अन्यथा अगर (_sz == PUD_SIZE)			\
			tlb_flush_pud_range(tlb, address, _sz);	\
		__tlb_हटाओ_tlb_entry(tlb, ptep, address);	\
	पूर्ण जबतक (0)

/**
 * tlb_हटाओ_pmd_tlb_entry - remember a pmd mapping क्रम later tlb invalidation
 * This is a nop so far, because only x86 needs it.
 */
#अगर_अघोषित __tlb_हटाओ_pmd_tlb_entry
#घोषणा __tlb_हटाओ_pmd_tlb_entry(tlb, pmdp, address) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा tlb_हटाओ_pmd_tlb_entry(tlb, pmdp, address)			\
	करो अणु								\
		tlb_flush_pmd_range(tlb, address, HPAGE_PMD_SIZE);	\
		__tlb_हटाओ_pmd_tlb_entry(tlb, pmdp, address);		\
	पूर्ण जबतक (0)

/**
 * tlb_हटाओ_pud_tlb_entry - remember a pud mapping क्रम later tlb
 * invalidation. This is a nop so far, because only x86 needs it.
 */
#अगर_अघोषित __tlb_हटाओ_pud_tlb_entry
#घोषणा __tlb_हटाओ_pud_tlb_entry(tlb, pudp, address) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा tlb_हटाओ_pud_tlb_entry(tlb, pudp, address)			\
	करो अणु								\
		tlb_flush_pud_range(tlb, address, HPAGE_PUD_SIZE);	\
		__tlb_हटाओ_pud_tlb_entry(tlb, pudp, address);		\
	पूर्ण जबतक (0)

/*
 * For things like page tables caches (ie caching addresses "inside" the
 * page tables, like x86 करोes), क्रम legacy reasons, flushing an
 * inभागidual page had better flush the page table caches behind it. This
 * is definitely how x86 works, क्रम example. And अगर you have an
 * architected non-legacy page table cache (which I'm not aware of
 * anybody actually करोing), you're going to have some architecturally
 * explicit flushing क्रम that, likely *separate* from a regular TLB entry
 * flush, and thus you'd need more than just some range expansion..
 *
 * So अगर we ever find an architecture
 * that would want something that odd, I think it is up to that
 * architecture to करो its own odd thing, not cause pain क्रम others
 * http://lkml.kernel.org/r/CA+55aFzBggoXtNXQeng5d_mRoDnaMBE5Y+URs+PHR67nUpMtaw@mail.gmail.com
 *
 * For now w.r.t page table cache, mark the range_size as PAGE_SIZE
 */

#अगर_अघोषित pte_मुक्त_tlb
#घोषणा pte_मुक्त_tlb(tlb, ptep, address)			\
	करो अणु							\
		tlb_flush_pmd_range(tlb, address, PAGE_SIZE);	\
		tlb->मुक्तd_tables = 1;				\
		__pte_मुक्त_tlb(tlb, ptep, address);		\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित pmd_मुक्त_tlb
#घोषणा pmd_मुक्त_tlb(tlb, pmdp, address)			\
	करो अणु							\
		tlb_flush_pud_range(tlb, address, PAGE_SIZE);	\
		tlb->मुक्तd_tables = 1;				\
		__pmd_मुक्त_tlb(tlb, pmdp, address);		\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित pud_मुक्त_tlb
#घोषणा pud_मुक्त_tlb(tlb, pudp, address)			\
	करो अणु							\
		tlb_flush_p4d_range(tlb, address, PAGE_SIZE);	\
		tlb->मुक्तd_tables = 1;				\
		__pud_मुक्त_tlb(tlb, pudp, address);		\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित p4d_मुक्त_tlb
#घोषणा p4d_मुक्त_tlb(tlb, pudp, address)			\
	करो अणु							\
		__tlb_adjust_range(tlb, address, PAGE_SIZE);	\
		tlb->मुक्तd_tables = 1;				\
		__p4d_मुक्त_tlb(tlb, pudp, address);		\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MMU */

#पूर्ण_अगर /* _ASM_GENERIC__TLB_H */
