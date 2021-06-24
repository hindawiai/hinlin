<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains common routines क्रम dealing with मुक्त of page tables
 * Aदीर्घ with common page table handling code
 *
 *  Derived from arch/घातerpc/mm/tlb_64.c:
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
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/hugetlb.h>
#समावेश <यंत्र/pte-walk.h>

अटल अंतरभूत पूर्णांक is_exec_fault(व्योम)
अणु
	वापस current->thपढ़ो.regs && TRAP(current->thपढ़ो.regs) == 0x400;
पूर्ण

/* We only try to करो i/d cache coherency on stuff that looks like
 * reasonably "normal" PTEs. We currently require a PTE to be present
 * and we aव्योम _PAGE_SPECIAL and cache inhibited pte. We also only करो that
 * on userspace PTEs
 */
अटल अंतरभूत पूर्णांक pte_looks_normal(pte_t pte)
अणु

	अगर (pte_present(pte) && !pte_special(pte)) अणु
		अगर (pte_ci(pte))
			वापस 0;
		अगर (pte_user(pte))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा page *maybe_pte_to_page(pte_t pte)
अणु
	अचिन्हित दीर्घ pfn = pte_pfn(pte);
	काष्ठा page *page;

	अगर (unlikely(!pfn_valid(pfn)))
		वापस शून्य;
	page = pfn_to_page(pfn);
	अगर (PageReserved(page))
		वापस शून्य;
	वापस page;
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S

/* Server-style MMU handles coherency when hashing अगर HW exec permission
 * is supposed per page (currently 64-bit only). If not, then, we always
 * flush the cache क्रम valid PTEs in set_pte. Embedded CPU without HW exec
 * support falls पूर्णांकo the same category.
 */

अटल pte_t set_pte_filter_hash(pte_t pte)
अणु
	अगर (radix_enabled())
		वापस pte;

	pte = __pte(pte_val(pte) & ~_PAGE_HPTEFLAGS);
	अगर (pte_looks_normal(pte) && !(cpu_has_feature(CPU_FTR_COHERENT_ICACHE) ||
				       cpu_has_feature(CPU_FTR_NOEXECUTE))) अणु
		काष्ठा page *pg = maybe_pte_to_page(pte);
		अगर (!pg)
			वापस pte;
		अगर (!test_bit(PG_dcache_clean, &pg->flags)) अणु
			flush_dcache_icache_page(pg);
			set_bit(PG_dcache_clean, &pg->flags);
		पूर्ण
	पूर्ण
	वापस pte;
पूर्ण

#अन्यथा /* CONFIG_PPC_BOOK3S */

अटल pte_t set_pte_filter_hash(pte_t pte) अणु वापस pte; पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_BOOK3S */

/* Embedded type MMU with HW exec support. This is a bit more complicated
 * as we करोn't have two bits to spare क्रम _PAGE_EXEC and _PAGE_HWEXEC so
 * instead we "filter out" the exec permission क्रम non clean pages.
 */
अटल अंतरभूत pte_t set_pte_filter(pte_t pte)
अणु
	काष्ठा page *pg;

	अगर (mmu_has_feature(MMU_FTR_HPTE_TABLE))
		वापस set_pte_filter_hash(pte);

	/* No exec permission in the first place, move on */
	अगर (!pte_exec(pte) || !pte_looks_normal(pte))
		वापस pte;

	/* If you set _PAGE_EXEC on weird pages you're on your own */
	pg = maybe_pte_to_page(pte);
	अगर (unlikely(!pg))
		वापस pte;

	/* If the page clean, we move on */
	अगर (test_bit(PG_dcache_clean, &pg->flags))
		वापस pte;

	/* If it's an exec fault, we flush the cache and make it clean */
	अगर (is_exec_fault()) अणु
		flush_dcache_icache_page(pg);
		set_bit(PG_dcache_clean, &pg->flags);
		वापस pte;
	पूर्ण

	/* Else, we filter out _PAGE_EXEC */
	वापस pte_exprotect(pte);
पूर्ण

अटल pte_t set_access_flags_filter(pte_t pte, काष्ठा vm_area_काष्ठा *vma,
				     पूर्णांक dirty)
अणु
	काष्ठा page *pg;

	अगर (mmu_has_feature(MMU_FTR_HPTE_TABLE))
		वापस pte;

	/* So here, we only care about exec faults, as we use them
	 * to recover lost _PAGE_EXEC and perक्रमm I$/D$ coherency
	 * अगर necessary. Also अगर _PAGE_EXEC is alपढ़ोy set, same deal,
	 * we just bail out
	 */
	अगर (dirty || pte_exec(pte) || !is_exec_fault())
		वापस pte;

#अगर_घोषित CONFIG_DEBUG_VM
	/* So this is an exec fault, _PAGE_EXEC is not set. If it was
	 * an error we would have bailed out earlier in करो_page_fault()
	 * but let's make sure of it
	 */
	अगर (WARN_ON(!(vma->vm_flags & VM_EXEC)))
		वापस pte;
#पूर्ण_अगर /* CONFIG_DEBUG_VM */

	/* If you set _PAGE_EXEC on weird pages you're on your own */
	pg = maybe_pte_to_page(pte);
	अगर (unlikely(!pg))
		जाओ bail;

	/* If the page is alपढ़ोy clean, we move on */
	अगर (test_bit(PG_dcache_clean, &pg->flags))
		जाओ bail;

	/* Clean the page and set PG_dcache_clean */
	flush_dcache_icache_page(pg);
	set_bit(PG_dcache_clean, &pg->flags);

 bail:
	वापस pte_mkexec(pte);
पूर्ण

/*
 * set_pte stores a linux PTE पूर्णांकo the linux page table.
 */
व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep,
		pte_t pte)
अणु
	/*
	 * Make sure hardware valid bit is not set. We करोn't करो
	 * tlb flush क्रम this update.
	 */
	VM_WARN_ON(pte_hw_valid(*ptep) && !pte_protnone(*ptep));

	/* Note: mm->context.id might not yet have been asचिन्हित as
	 * this context might not have been activated yet when this
	 * is called.
	 */
	pte = set_pte_filter(pte);

	/* Perक्रमm the setting of the PTE */
	__set_pte_at(mm, addr, ptep, pte, 0);
पूर्ण

/*
 * This is called when relaxing access to a PTE. It's also called in the page
 * fault path when we करोn't hit any of the major fault हालs, ie, a minor
 * update of _PAGE_ACCESSED, _PAGE_सूचीTY, etc... The generic code will have
 * handled those two क्रम us, we additionally deal with missing execute
 * permission here on some processors
 */
पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			  pte_t *ptep, pte_t entry, पूर्णांक dirty)
अणु
	पूर्णांक changed;
	entry = set_access_flags_filter(entry, vma, dirty);
	changed = !pte_same(*(ptep), entry);
	अगर (changed) अणु
		निश्चित_pte_locked(vma->vm_mm, address);
		__ptep_set_access_flags(vma, ptep, entry,
					address, mmu_भव_psize);
	पूर्ण
	वापस changed;
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ addr, pte_t *ptep,
			       pte_t pte, पूर्णांक dirty)
अणु
#अगर_घोषित HUGETLB_NEED_PRELOAD
	/*
	 * The "return 1" क्रमces a call of update_mmu_cache, which will ग_लिखो a
	 * TLB entry.  Without this, platक्रमms that करोn't करो a ग_लिखो of the TLB
	 * entry in the TLB miss handler यंत्र will fault ad infinitum.
	 */
	ptep_set_access_flags(vma, addr, ptep, pte, dirty);
	वापस 1;
#अन्यथा
	पूर्णांक changed, psize;

	pte = set_access_flags_filter(pte, vma, dirty);
	changed = !pte_same(*(ptep), pte);
	अगर (changed) अणु

#अगर_घोषित CONFIG_PPC_BOOK3S_64
		काष्ठा hstate *h = hstate_vma(vma);

		psize = hstate_get_psize(h);
#अगर_घोषित CONFIG_DEBUG_VM
		निश्चित_spin_locked(huge_pte_lockptr(h, vma->vm_mm, ptep));
#पूर्ण_अगर

#अन्यथा
		/*
		 * Not used on non book3s64 platक्रमms.
		 * 8xx compares it with mmu_भव_psize to
		 * know अगर it is a huge page or not.
		 */
		psize = MMU_PAGE_COUNT;
#पूर्ण_अगर
		__ptep_set_access_flags(vma, ptep, pte, addr, psize);
	पूर्ण
	वापस changed;
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_PPC_8xx)
व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep, pte_t pte)
अणु
	pmd_t *pmd = pmd_off(mm, addr);
	pte_basic_t val;
	pte_basic_t *entry = &ptep->pte;
	पूर्णांक num, i;

	/*
	 * Make sure hardware valid bit is not set. We करोn't करो
	 * tlb flush क्रम this update.
	 */
	VM_WARN_ON(pte_hw_valid(*ptep) && !pte_protnone(*ptep));

	pte = set_pte_filter(pte);

	val = pte_val(pte);

	num = number_of_cells_per_pte(pmd, val, 1);

	क्रम (i = 0; i < num; i++, entry++, val += SZ_4K)
		*entry = val;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#अगर_घोषित CONFIG_DEBUG_VM
व्योम निश्चित_pte_locked(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	अगर (mm == &init_mm)
		वापस;
	pgd = mm->pgd + pgd_index(addr);
	BUG_ON(pgd_none(*pgd));
	p4d = p4d_offset(pgd, addr);
	BUG_ON(p4d_none(*p4d));
	pud = pud_offset(p4d, addr);
	BUG_ON(pud_none(*pud));
	pmd = pmd_offset(pud, addr);
	/*
	 * khugepaged to collapse normal pages to hugepage, first set
	 * pmd to none to क्रमce page fault/gup to take mmap_lock. After
	 * pmd is set to none, we करो a pte_clear which करोes this निश्चितion
	 * so अगर we find pmd none, वापस.
	 */
	अगर (pmd_none(*pmd))
		वापस;
	BUG_ON(!pmd_present(*pmd));
	निश्चित_spin_locked(pte_lockptr(mm, pmd));
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_VM */

अचिन्हित दीर्घ vदो_स्मृति_to_phys(व्योम *va)
अणु
	अचिन्हित दीर्घ pfn = vदो_स्मृति_to_pfn(va);

	BUG_ON(!pfn);
	वापस __pa(pfn_to_kaddr(pfn)) + offset_in_page(va);
पूर्ण
EXPORT_SYMBOL_GPL(vदो_स्मृति_to_phys);

/*
 * We have 4 हालs क्रम pgds and pmds:
 * (1) invalid (all zeroes)
 * (2) poपूर्णांकer to next table, as normal; bottom 6 bits == 0
 * (3) leaf pte क्रम huge page _PAGE_PTE set
 * (4) hugepd poपूर्णांकer, _PAGE_PTE = 0 and bits [2..6] indicate size of table
 *
 * So दीर्घ as we atomically load page table poपूर्णांकers we are safe against tearकरोwn,
 * we can follow the address करोwn to the the page and take a ref on it.
 * This function need to be called with पूर्णांकerrupts disabled. We use this variant
 * when we have MSR[EE] = 0 but the paca->irq_soft_mask = IRQS_ENABLED
 */
pte_t *__find_linux_pte(pgd_t *pgdir, अचिन्हित दीर्घ ea,
			bool *is_thp, अचिन्हित *hpage_shअगरt)
अणु
	pgd_t *pgdp;
	p4d_t p4d, *p4dp;
	pud_t pud, *pudp;
	pmd_t pmd, *pmdp;
	pte_t *ret_pte;
	hugepd_t *hpdp = शून्य;
	अचिन्हित pdshअगरt;

	अगर (hpage_shअगरt)
		*hpage_shअगरt = 0;

	अगर (is_thp)
		*is_thp = false;

	/*
	 * Always operate on the local stack value. This make sure the
	 * value करोn't get updated by a parallel THP split/collapse,
	 * page fault or a page unmap. The वापस pte_t * is still not
	 * stable. So should be checked there क्रम above conditions.
	 * Top level is an exception because it is folded पूर्णांकo p4d.
	 */
	pgdp = pgdir + pgd_index(ea);
	p4dp = p4d_offset(pgdp, ea);
	p4d  = READ_ONCE(*p4dp);
	pdshअगरt = P4D_SHIFT;

	अगर (p4d_none(p4d))
		वापस शून्य;

	अगर (p4d_is_leaf(p4d)) अणु
		ret_pte = (pte_t *)p4dp;
		जाओ out;
	पूर्ण

	अगर (is_hugepd(__hugepd(p4d_val(p4d)))) अणु
		hpdp = (hugepd_t *)&p4d;
		जाओ out_huge;
	पूर्ण

	/*
	 * Even अगर we end up with an unmap, the pgtable will not
	 * be मुक्तd, because we करो an rcu मुक्त and here we are
	 * irq disabled
	 */
	pdshअगरt = PUD_SHIFT;
	pudp = pud_offset(&p4d, ea);
	pud  = READ_ONCE(*pudp);

	अगर (pud_none(pud))
		वापस शून्य;

	अगर (pud_is_leaf(pud)) अणु
		ret_pte = (pte_t *)pudp;
		जाओ out;
	पूर्ण

	अगर (is_hugepd(__hugepd(pud_val(pud)))) अणु
		hpdp = (hugepd_t *)&pud;
		जाओ out_huge;
	पूर्ण

	pdshअगरt = PMD_SHIFT;
	pmdp = pmd_offset(&pud, ea);
	pmd  = READ_ONCE(*pmdp);

	/*
	 * A hugepage collapse is captured by this condition, see
	 * pmdp_collapse_flush.
	 */
	अगर (pmd_none(pmd))
		वापस शून्य;

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/*
	 * A hugepage split is captured by this condition, see
	 * pmdp_invalidate.
	 *
	 * Huge page modअगरication can be caught here too.
	 */
	अगर (pmd_is_serializing(pmd))
		वापस शून्य;
#पूर्ण_अगर

	अगर (pmd_trans_huge(pmd) || pmd_devmap(pmd)) अणु
		अगर (is_thp)
			*is_thp = true;
		ret_pte = (pte_t *)pmdp;
		जाओ out;
	पूर्ण

	अगर (pmd_is_leaf(pmd)) अणु
		ret_pte = (pte_t *)pmdp;
		जाओ out;
	पूर्ण

	अगर (is_hugepd(__hugepd(pmd_val(pmd)))) अणु
		hpdp = (hugepd_t *)&pmd;
		जाओ out_huge;
	पूर्ण

	वापस pte_offset_kernel(&pmd, ea);

out_huge:
	अगर (!hpdp)
		वापस शून्य;

	ret_pte = hugepte_offset(*hpdp, ea, pdshअगरt);
	pdshअगरt = hugepd_shअगरt(*hpdp);
out:
	अगर (hpage_shअगरt)
		*hpage_shअगरt = pdshअगरt;
	वापस ret_pte;
पूर्ण
EXPORT_SYMBOL_GPL(__find_linux_pte);
