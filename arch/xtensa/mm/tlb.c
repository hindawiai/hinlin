<शैली गुरु>
/*
 * arch/xtensa/mm/tlb.c
 *
 * Logic that manipulates the Xtensa MMU.  Derived from MIPS.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2003 Tensilica Inc.
 *
 * Joe Taylor
 * Chris Zankel	<chris@zankel.net>
 * Marc Gauthier
 */

#समावेश <linux/mm.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>


अटल अंतरभूत व्योम __flush_itlb_all (व्योम)
अणु
	पूर्णांक w, i;

	क्रम (w = 0; w < ITLB_ARF_WAYS; w++) अणु
		क्रम (i = 0; i < (1 << XCHAL_ITLB_ARF_ENTRIES_LOG2); i++) अणु
			पूर्णांक e = w + (i << PAGE_SHIFT);
			invalidate_itlb_entry_no_isync(e);
		पूर्ण
	पूर्ण
	यंत्र अस्थिर ("isync\n");
पूर्ण

अटल अंतरभूत व्योम __flush_dtlb_all (व्योम)
अणु
	पूर्णांक w, i;

	क्रम (w = 0; w < DTLB_ARF_WAYS; w++) अणु
		क्रम (i = 0; i < (1 << XCHAL_DTLB_ARF_ENTRIES_LOG2); i++) अणु
			पूर्णांक e = w + (i << PAGE_SHIFT);
			invalidate_dtlb_entry_no_isync(e);
		पूर्ण
	पूर्ण
	यंत्र अस्थिर ("isync\n");
पूर्ण


व्योम local_flush_tlb_all(व्योम)
अणु
	__flush_itlb_all();
	__flush_dtlb_all();
पूर्ण

/* If mm is current, we simply assign the current task a new ASID, thus,
 * invalidating all previous tlb entries. If mm is someone अन्यथा's user mapping,
 * wie invalidate the context, thus, when that user mapping is swapped in,
 * a new context will be asचिन्हित to it.
 */

व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (mm == current->active_mm) अणु
		अचिन्हित दीर्घ flags;
		local_irq_save(flags);
		mm->context.asid[cpu] = NO_CONTEXT;
		activate_context(mm, cpu);
		local_irq_restore(flags);
	पूर्ण अन्यथा अणु
		mm->context.asid[cpu] = NO_CONTEXT;
		mm->context.cpu = -1;
	पूर्ण
पूर्ण


#घोषणा _ITLB_ENTRIES (ITLB_ARF_WAYS << XCHAL_ITLB_ARF_ENTRIES_LOG2)
#घोषणा _DTLB_ENTRIES (DTLB_ARF_WAYS << XCHAL_DTLB_ARF_ENTRIES_LOG2)
#अगर _ITLB_ENTRIES > _DTLB_ENTRIES
# define _TLB_ENTRIES _ITLB_ENTRIES
#अन्यथा
# define _TLB_ENTRIES _DTLB_ENTRIES
#पूर्ण_अगर

व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ flags;

	अगर (mm->context.asid[cpu] == NO_CONTEXT)
		वापस;

	pr_debug("[tlbrange<%02lx,%08lx,%08lx>]\n",
		 (अचिन्हित दीर्घ)mm->context.asid[cpu], start, end);
	local_irq_save(flags);

	अगर (end-start + (PAGE_SIZE-1) <= _TLB_ENTRIES << PAGE_SHIFT) अणु
		पूर्णांक oldpid = get_rasid_रेजिस्टर();

		set_rasid_रेजिस्टर(ASID_INSERT(mm->context.asid[cpu]));
		start &= PAGE_MASK;
		अगर (vma->vm_flags & VM_EXEC)
			जबतक(start < end) अणु
				invalidate_itlb_mapping(start);
				invalidate_dtlb_mapping(start);
				start += PAGE_SIZE;
			पूर्ण
		अन्यथा
			जबतक(start < end) अणु
				invalidate_dtlb_mapping(start);
				start += PAGE_SIZE;
			पूर्ण

		set_rasid_रेजिस्टर(oldpid);
	पूर्ण अन्यथा अणु
		local_flush_tlb_mm(mm);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा mm_काष्ठा* mm = vma->vm_mm;
	अचिन्हित दीर्घ flags;
	पूर्णांक oldpid;

	अगर (mm->context.asid[cpu] == NO_CONTEXT)
		वापस;

	local_irq_save(flags);

	oldpid = get_rasid_रेजिस्टर();
	set_rasid_रेजिस्टर(ASID_INSERT(mm->context.asid[cpu]));

	अगर (vma->vm_flags & VM_EXEC)
		invalidate_itlb_mapping(page);
	invalidate_dtlb_mapping(page);

	set_rasid_रेजिस्टर(oldpid);

	local_irq_restore(flags);
पूर्ण

व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (end > start && start >= TASK_SIZE && end <= PAGE_OFFSET &&
	    end - start < _TLB_ENTRIES << PAGE_SHIFT) अणु
		start &= PAGE_MASK;
		जबतक (start < end) अणु
			invalidate_itlb_mapping(start);
			invalidate_dtlb_mapping(start);
			start += PAGE_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		local_flush_tlb_all();
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_TLB_SANITY

अटल अचिन्हित get_pte_क्रम_vaddr(अचिन्हित vaddr)
अणु
	काष्ठा task_काष्ठा *task = get_current();
	काष्ठा mm_काष्ठा *mm = task->mm;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	अगर (!mm)
		mm = task->active_mm;
	pgd = pgd_offset(mm, vaddr);
	अगर (pgd_none_or_clear_bad(pgd))
		वापस 0;
	p4d = p4d_offset(pgd, vaddr);
	अगर (p4d_none_or_clear_bad(p4d))
		वापस 0;
	pud = pud_offset(p4d, vaddr);
	अगर (pud_none_or_clear_bad(pud))
		वापस 0;
	pmd = pmd_offset(pud, vaddr);
	अगर (pmd_none_or_clear_bad(pmd))
		वापस 0;
	pte = pte_offset_map(pmd, vaddr);
	अगर (!pte)
		वापस 0;
	वापस pte_val(*pte);
पूर्ण

क्रमागत अणु
	TLB_SUSPICIOUS	= 1,
	TLB_INSANE	= 2,
पूर्ण;

अटल व्योम tlb_insane(व्योम)
अणु
	BUG_ON(1);
पूर्ण

अटल व्योम tlb_suspicious(व्योम)
अणु
	WARN_ON(1);
पूर्ण

/*
 * Check that TLB entries with kernel ASID (1) have kernel VMA (>= TASK_SIZE),
 * and TLB entries with user ASID (>=4) have VMA < TASK_SIZE.
 *
 * Check that valid TLB entries either have the same PA as the PTE, or PTE is
 * marked as non-present. Non-present PTE and the page with non-zero refcount
 * and zero mapcount is normal क्रम batched TLB flush operation. Zero refcount
 * means that the page was मुक्तd prematurely. Non-zero mapcount is unusual,
 * but करोes not necessary means an error, thus marked as suspicious.
 */
अटल पूर्णांक check_tlb_entry(अचिन्हित w, अचिन्हित e, bool dtlb)
अणु
	अचिन्हित tlbidx = w | (e << PAGE_SHIFT);
	अचिन्हित r0 = dtlb ?
		पढ़ो_dtlb_भव(tlbidx) : पढ़ो_itlb_भव(tlbidx);
	अचिन्हित r1 = dtlb ?
		पढ़ो_dtlb_translation(tlbidx) : पढ़ो_itlb_translation(tlbidx);
	अचिन्हित vpn = (r0 & PAGE_MASK) | (e << PAGE_SHIFT);
	अचिन्हित pte = get_pte_क्रम_vaddr(vpn);
	अचिन्हित mm_asid = (get_rasid_रेजिस्टर() >> 8) & ASID_MASK;
	अचिन्हित tlb_asid = r0 & ASID_MASK;
	bool kernel = tlb_asid == 1;
	पूर्णांक rc = 0;

	अगर (tlb_asid > 0 && ((vpn < TASK_SIZE) == kernel)) अणु
		pr_err("%cTLB: way: %u, entry: %u, VPN %08x in %s PTE\n",
				dtlb ? 'D' : 'I', w, e, vpn,
				kernel ? "kernel" : "user");
		rc |= TLB_INSANE;
	पूर्ण

	अगर (tlb_asid == mm_asid) अणु
		अगर ((pte ^ r1) & PAGE_MASK) अणु
			pr_err("%cTLB: way: %u, entry: %u, mapping: %08x->%08x, PTE: %08x\n",
					dtlb ? 'D' : 'I', w, e, r0, r1, pte);
			अगर (pte == 0 || !pte_present(__pte(pte))) अणु
				काष्ठा page *p = pfn_to_page(r1 >> PAGE_SHIFT);
				pr_err("page refcount: %d, mapcount: %d\n",
						page_count(p),
						page_mapcount(p));
				अगर (!page_count(p))
					rc |= TLB_INSANE;
				अन्यथा अगर (page_mapcount(p))
					rc |= TLB_SUSPICIOUS;
			पूर्ण अन्यथा अणु
				rc |= TLB_INSANE;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

व्योम check_tlb_sanity(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित w, e;
	पूर्णांक bug = 0;

	local_irq_save(flags);
	क्रम (w = 0; w < DTLB_ARF_WAYS; ++w)
		क्रम (e = 0; e < (1 << XCHAL_DTLB_ARF_ENTRIES_LOG2); ++e)
			bug |= check_tlb_entry(w, e, true);
	क्रम (w = 0; w < ITLB_ARF_WAYS; ++w)
		क्रम (e = 0; e < (1 << XCHAL_ITLB_ARF_ENTRIES_LOG2); ++e)
			bug |= check_tlb_entry(w, e, false);
	अगर (bug & TLB_INSANE)
		tlb_insane();
	अगर (bug & TLB_SUSPICIOUS)
		tlb_suspicious();
	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_TLB_SANITY */
