<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PARISC64 Huge TLB page support.
 *
 * This parisc implementation is heavily based on the SPARC and x86 code.
 *
 * Copyright (C) 2015 Helge Deller <deller@gmx.de>
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sysctl.h>

#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mmu_context.h>


अचिन्हित दीर्घ
hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);

	अगर (len & ~huge_page_mask(h))
		वापस -EINVAL;
	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED)
		अगर (prepare_hugepage_range(file, addr, len))
			वापस -EINVAL;

	अगर (addr)
		addr = ALIGN(addr, huge_page_size(h));

	/* we need to make sure the colouring is OK */
	वापस arch_get_unmapped_area(file, addr, len, pgoff, flags);
पूर्ण


pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = शून्य;

	/* We must align the address, because our caller will run
	 * set_huge_pte_at() on whatever we वापस, which ग_लिखोs out
	 * all of the sub-ptes क्रम the hugepage range.  So we have
	 * to give it the first such sub-pte.
	 */
	addr &= HPAGE_MASK;

	pgd = pgd_offset(mm, addr);
	p4d = p4d_offset(pgd, addr);
	pud = pud_alloc(mm, p4d, addr);
	अगर (pud) अणु
		pmd = pmd_alloc(mm, pud, addr);
		अगर (pmd)
			pte = pte_alloc_map(mm, pmd, addr);
	पूर्ण
	वापस pte;
पूर्ण

pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm,
		       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = शून्य;

	addr &= HPAGE_MASK;

	pgd = pgd_offset(mm, addr);
	अगर (!pgd_none(*pgd)) अणु
		p4d = p4d_offset(pgd, addr);
		अगर (!p4d_none(*p4d)) अणु
			pud = pud_offset(p4d, addr);
			अगर (!pud_none(*pud)) अणु
				pmd = pmd_offset(pud, addr);
				अगर (!pmd_none(*pmd))
					pte = pte_offset_map(pmd, addr);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस pte;
पूर्ण

/* Purge data and inकाष्ठाion TLB entries.  Must be called holding
 * the pa_tlb_lock.  The TLB purge inकाष्ठाions are slow on SMP
 * machines since the purge must be broadcast to all CPUs.
 */
अटल अंतरभूत व्योम purge_tlb_entries_huge(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक i;

	/* We may use multiple physical huge pages (e.g. 2x1 MB) to emulate
	 * Linux standard huge pages (e.g. 2 MB) */
	BUILD_BUG_ON(REAL_HPAGE_SHIFT > HPAGE_SHIFT);

	addr &= HPAGE_MASK;
	addr |= _HUGE_PAGE_SIZE_ENCODING_DEFAULT;

	क्रम (i = 0; i < (1 << (HPAGE_SHIFT-REAL_HPAGE_SHIFT)); i++) अणु
		purge_tlb_entries(mm, addr);
		addr += (1UL << REAL_HPAGE_SHIFT);
	पूर्ण
पूर्ण

/* __set_huge_pte_at() must be called holding the pa_tlb_lock. */
अटल व्योम __set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t entry)
अणु
	अचिन्हित दीर्घ addr_start;
	पूर्णांक i;

	addr &= HPAGE_MASK;
	addr_start = addr;

	क्रम (i = 0; i < (1 << HUGETLB_PAGE_ORDER); i++) अणु
		set_pte(ptep, entry);
		ptep++;

		addr += PAGE_SIZE;
		pte_val(entry) += PAGE_SIZE;
	पूर्ण

	purge_tlb_entries_huge(mm, addr_start);
पूर्ण

व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t entry)
अणु
	__set_huge_pte_at(mm, addr, ptep, entry);
पूर्ण


pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep)
अणु
	pte_t entry;

	entry = *ptep;
	__set_huge_pte_at(mm, addr, ptep, __pte(0));

	वापस entry;
पूर्ण


व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t old_pte;

	old_pte = *ptep;
	__set_huge_pte_at(mm, addr, ptep, pte_wrprotect(old_pte));
पूर्ण

पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ addr, pte_t *ptep,
				pte_t pte, पूर्णांक dirty)
अणु
	पूर्णांक changed;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	changed = !pte_same(*ptep, pte);
	अगर (changed) अणु
		__set_huge_pte_at(mm, addr, ptep, pte);
	पूर्ण
	वापस changed;
पूर्ण


पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस 0;
पूर्ण
