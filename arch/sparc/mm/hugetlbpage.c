<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SPARC64 Huge TLB page support.
 *
 * Copyright (C) 2002, 2003, 2006 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sysctl.h>

#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mmu_context.h>

/* Slightly simplअगरied from the non-hugepage variant because by
 * definition we करोn't have to worry about any page coloring stuff
 */

अटल अचिन्हित दीर्घ hugetlb_get_unmapped_area_bottomup(काष्ठा file *filp,
							अचिन्हित दीर्घ addr,
							अचिन्हित दीर्घ len,
							अचिन्हित दीर्घ pgoff,
							अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(filp);
	अचिन्हित दीर्घ task_size = TASK_SIZE;
	काष्ठा vm_unmapped_area_info info;

	अगर (test_thपढ़ो_flag(TIF_32BIT))
		task_size = STACK_TOP32;

	info.flags = 0;
	info.length = len;
	info.low_limit = TASK_UNMAPPED_BASE;
	info.high_limit = min(task_size, VA_EXCLUDE_START);
	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;
	addr = vm_unmapped_area(&info);

	अगर ((addr & ~PAGE_MASK) && task_size > VA_EXCLUDE_END) अणु
		VM_BUG_ON(addr != -ENOMEM);
		info.low_limit = VA_EXCLUDE_END;
		info.high_limit = task_size;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण

अटल अचिन्हित दीर्घ
hugetlb_get_unmapped_area_topकरोwn(काष्ठा file *filp, स्थिर अचिन्हित दीर्घ addr0,
				  स्थिर अचिन्हित दीर्घ len,
				  स्थिर अचिन्हित दीर्घ pgoff,
				  स्थिर अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(filp);
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ addr = addr0;
	काष्ठा vm_unmapped_area_info info;

	/* This should only ever run क्रम 32-bit processes.  */
	BUG_ON(!test_thपढ़ो_flag(TIF_32BIT));

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = PAGE_SIZE;
	info.high_limit = mm->mmap_base;
	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;
	addr = vm_unmapped_area(&info);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	अगर (addr & ~PAGE_MASK) अणु
		VM_BUG_ON(addr != -ENOMEM);
		info.flags = 0;
		info.low_limit = TASK_UNMAPPED_BASE;
		info.high_limit = STACK_TOP32;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण

अचिन्हित दीर्घ
hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ task_size = TASK_SIZE;

	अगर (test_thपढ़ो_flag(TIF_32BIT))
		task_size = STACK_TOP32;

	अगर (len & ~huge_page_mask(h))
		वापस -EINVAL;
	अगर (len > task_size)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED) अणु
		अगर (prepare_hugepage_range(file, addr, len))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (addr) अणु
		addr = ALIGN(addr, huge_page_size(h));
		vma = find_vma(mm, addr);
		अगर (task_size - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण
	अगर (mm->get_unmapped_area == arch_get_unmapped_area)
		वापस hugetlb_get_unmapped_area_bottomup(file, addr, len,
				pgoff, flags);
	अन्यथा
		वापस hugetlb_get_unmapped_area_topकरोwn(file, addr, len,
				pgoff, flags);
पूर्ण

अटल pte_t sun4u_hugepage_shअगरt_to_tte(pte_t entry, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस entry;
पूर्ण

अटल pte_t sun4v_hugepage_shअगरt_to_tte(pte_t entry, अचिन्हित पूर्णांक shअगरt)
अणु
	अचिन्हित दीर्घ hugepage_size = _PAGE_SZ4MB_4V;

	pte_val(entry) = pte_val(entry) & ~_PAGE_SZALL_4V;

	चयन (shअगरt) अणु
	हाल HPAGE_16GB_SHIFT:
		hugepage_size = _PAGE_SZ16GB_4V;
		pte_val(entry) |= _PAGE_PUD_HUGE;
		अवरोध;
	हाल HPAGE_2GB_SHIFT:
		hugepage_size = _PAGE_SZ2GB_4V;
		pte_val(entry) |= _PAGE_PMD_HUGE;
		अवरोध;
	हाल HPAGE_256MB_SHIFT:
		hugepage_size = _PAGE_SZ256MB_4V;
		pte_val(entry) |= _PAGE_PMD_HUGE;
		अवरोध;
	हाल HPAGE_SHIFT:
		pte_val(entry) |= _PAGE_PMD_HUGE;
		अवरोध;
	हाल HPAGE_64K_SHIFT:
		hugepage_size = _PAGE_SZ64K_4V;
		अवरोध;
	शेष:
		WARN_ONCE(1, "unsupported hugepage shift=%u\n", shअगरt);
	पूर्ण

	pte_val(entry) = pte_val(entry) | hugepage_size;
	वापस entry;
पूर्ण

अटल pte_t hugepage_shअगरt_to_tte(pte_t entry, अचिन्हित पूर्णांक shअगरt)
अणु
	अगर (tlb_type == hypervisor)
		वापस sun4v_hugepage_shअगरt_to_tte(entry, shअगरt);
	अन्यथा
		वापस sun4u_hugepage_shअगरt_to_tte(entry, shअगरt);
पूर्ण

pte_t arch_make_huge_pte(pte_t entry, काष्ठा vm_area_काष्ठा *vma,
			 काष्ठा page *page, पूर्णांक ग_लिखोable)
अणु
	अचिन्हित पूर्णांक shअगरt = huge_page_shअगरt(hstate_vma(vma));
	pte_t pte;

	pte = hugepage_shअगरt_to_tte(entry, shअगरt);

#अगर_घोषित CONFIG_SPARC64
	/* If this vma has ADI enabled on it, turn on TTE.mcd
	 */
	अगर (vma->vm_flags & VM_SPARC_ADI)
		वापस pte_mkmcd(pte);
	अन्यथा
		वापस pte_mknoपंचांगcd(pte);
#अन्यथा
	वापस pte;
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित पूर्णांक sun4v_huge_tte_to_shअगरt(pte_t entry)
अणु
	अचिन्हित दीर्घ tte_szbits = pte_val(entry) & _PAGE_SZALL_4V;
	अचिन्हित पूर्णांक shअगरt;

	चयन (tte_szbits) अणु
	हाल _PAGE_SZ16GB_4V:
		shअगरt = HPAGE_16GB_SHIFT;
		अवरोध;
	हाल _PAGE_SZ2GB_4V:
		shअगरt = HPAGE_2GB_SHIFT;
		अवरोध;
	हाल _PAGE_SZ256MB_4V:
		shअगरt = HPAGE_256MB_SHIFT;
		अवरोध;
	हाल _PAGE_SZ4MB_4V:
		shअगरt = REAL_HPAGE_SHIFT;
		अवरोध;
	हाल _PAGE_SZ64K_4V:
		shअगरt = HPAGE_64K_SHIFT;
		अवरोध;
	शेष:
		shअगरt = PAGE_SHIFT;
		अवरोध;
	पूर्ण
	वापस shअगरt;
पूर्ण

अटल अचिन्हित पूर्णांक sun4u_huge_tte_to_shअगरt(pte_t entry)
अणु
	अचिन्हित दीर्घ tte_szbits = pte_val(entry) & _PAGE_SZALL_4U;
	अचिन्हित पूर्णांक shअगरt;

	चयन (tte_szbits) अणु
	हाल _PAGE_SZ256MB_4U:
		shअगरt = HPAGE_256MB_SHIFT;
		अवरोध;
	हाल _PAGE_SZ4MB_4U:
		shअगरt = REAL_HPAGE_SHIFT;
		अवरोध;
	हाल _PAGE_SZ64K_4U:
		shअगरt = HPAGE_64K_SHIFT;
		अवरोध;
	शेष:
		shअगरt = PAGE_SHIFT;
		अवरोध;
	पूर्ण
	वापस shअगरt;
पूर्ण

अटल अचिन्हित दीर्घ tte_to_shअगरt(pte_t entry)
अणु
	अगर (tlb_type == hypervisor)
		वापस sun4v_huge_tte_to_shअगरt(entry);

	वापस sun4u_huge_tte_to_shअगरt(entry);
पूर्ण

अटल अचिन्हित पूर्णांक huge_tte_to_shअगरt(pte_t entry)
अणु
	अचिन्हित दीर्घ shअगरt = tte_to_shअगरt(entry);

	अगर (shअगरt == PAGE_SHIFT)
		WARN_ONCE(1, "tto_to_shift: invalid hugepage tte=0x%lx\n",
			  pte_val(entry));

	वापस shअगरt;
पूर्ण

अटल अचिन्हित दीर्घ huge_tte_to_size(pte_t pte)
अणु
	अचिन्हित दीर्घ size = 1UL << huge_tte_to_shअगरt(pte);

	अगर (size == REAL_HPAGE_SIZE)
		size = HPAGE_SIZE;
	वापस size;
पूर्ण

अचिन्हित दीर्घ pud_leaf_size(pud_t pud) अणु वापस 1UL << tte_to_shअगरt(*(pte_t *)&pud); पूर्ण
अचिन्हित दीर्घ pmd_leaf_size(pmd_t pmd) अणु वापस 1UL << tte_to_shअगरt(*(pte_t *)&pmd); पूर्ण
अचिन्हित दीर्घ pte_leaf_size(pte_t pte) अणु वापस 1UL << tte_to_shअगरt(pte); पूर्ण

pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addr);
	p4d = p4d_offset(pgd, addr);
	pud = pud_alloc(mm, p4d, addr);
	अगर (!pud)
		वापस शून्य;
	अगर (sz >= PUD_SIZE)
		वापस (pte_t *)pud;
	pmd = pmd_alloc(mm, pud, addr);
	अगर (!pmd)
		वापस शून्य;
	अगर (sz >= PMD_SIZE)
		वापस (pte_t *)pmd;
	वापस pte_alloc_map(mm, pmd, addr);
पूर्ण

pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm,
		       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addr);
	अगर (pgd_none(*pgd))
		वापस शून्य;
	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d))
		वापस शून्य;
	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud))
		वापस शून्य;
	अगर (is_hugetlb_pud(*pud))
		वापस (pte_t *)pud;
	pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd))
		वापस शून्य;
	अगर (is_hugetlb_pmd(*pmd))
		वापस (pte_t *)pmd;
	वापस pte_offset_map(pmd, addr);
पूर्ण

व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t entry)
अणु
	अचिन्हित पूर्णांक nptes, orig_shअगरt, shअगरt;
	अचिन्हित दीर्घ i, size;
	pte_t orig;

	size = huge_tte_to_size(entry);

	shअगरt = PAGE_SHIFT;
	अगर (size >= PUD_SIZE)
		shअगरt = PUD_SHIFT;
	अन्यथा अगर (size >= PMD_SIZE)
		shअगरt = PMD_SHIFT;
	अन्यथा
		shअगरt = PAGE_SHIFT;

	nptes = size >> shअगरt;

	अगर (!pte_present(*ptep) && pte_present(entry))
		mm->context.hugetlb_pte_count += nptes;

	addr &= ~(size - 1);
	orig = *ptep;
	orig_shअगरt = pte_none(orig) ? PAGE_SHIFT : huge_tte_to_shअगरt(orig);

	क्रम (i = 0; i < nptes; i++)
		ptep[i] = __pte(pte_val(entry) + (i << shअगरt));

	maybe_tlb_batch_add(mm, addr, ptep, orig, 0, orig_shअगरt);
	/* An HPAGE_SIZE'ed page is composed of two REAL_HPAGE_SIZE'ed pages */
	अगर (size == HPAGE_SIZE)
		maybe_tlb_batch_add(mm, addr + REAL_HPAGE_SIZE, ptep, orig, 0,
				    orig_shअगरt);
पूर्ण

pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep)
अणु
	अचिन्हित पूर्णांक i, nptes, orig_shअगरt, shअगरt;
	अचिन्हित दीर्घ size;
	pte_t entry;

	entry = *ptep;
	size = huge_tte_to_size(entry);

	shअगरt = PAGE_SHIFT;
	अगर (size >= PUD_SIZE)
		shअगरt = PUD_SHIFT;
	अन्यथा अगर (size >= PMD_SIZE)
		shअगरt = PMD_SHIFT;
	अन्यथा
		shअगरt = PAGE_SHIFT;

	nptes = size >> shअगरt;
	orig_shअगरt = pte_none(entry) ? PAGE_SHIFT : huge_tte_to_shअगरt(entry);

	अगर (pte_present(entry))
		mm->context.hugetlb_pte_count -= nptes;

	addr &= ~(size - 1);
	क्रम (i = 0; i < nptes; i++)
		ptep[i] = __pte(0UL);

	maybe_tlb_batch_add(mm, addr, ptep, entry, 0, orig_shअगरt);
	/* An HPAGE_SIZE'ed page is composed of two REAL_HPAGE_SIZE'ed pages */
	अगर (size == HPAGE_SIZE)
		maybe_tlb_batch_add(mm, addr + REAL_HPAGE_SIZE, ptep, entry, 0,
				    orig_shअगरt);

	वापस entry;
पूर्ण

पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस !pmd_none(pmd) &&
		(pmd_val(pmd) & (_PAGE_VALID|_PAGE_PMD_HUGE)) != _PAGE_VALID;
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस !pud_none(pud) &&
		(pud_val(pud) & (_PAGE_VALID|_PAGE_PUD_HUGE)) != _PAGE_VALID;
पूर्ण

अटल व्योम hugetlb_मुक्त_pte_range(काष्ठा mmu_gather *tlb, pmd_t *pmd,
			   अचिन्हित दीर्घ addr)
अणु
	pgtable_t token = pmd_pgtable(*pmd);

	pmd_clear(pmd);
	pte_मुक्त_tlb(tlb, token, addr);
	mm_dec_nr_ptes(tlb->mm);
पूर्ण

अटल व्योम hugetlb_मुक्त_pmd_range(काष्ठा mmu_gather *tlb, pud_t *pud,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				   अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ start;

	start = addr;
	pmd = pmd_offset(pud, addr);
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (pmd_none(*pmd))
			जारी;
		अगर (is_hugetlb_pmd(*pmd))
			pmd_clear(pmd);
		अन्यथा
			hugetlb_मुक्त_pte_range(tlb, pmd, addr);
	पूर्ण जबतक (pmd++, addr = next, addr != end);

	start &= PUD_MASK;
	अगर (start < न्यूनमान)
		वापस;
	अगर (उच्चमानing) अणु
		उच्चमानing &= PUD_MASK;
		अगर (!उच्चमानing)
			वापस;
	पूर्ण
	अगर (end - 1 > उच्चमानing - 1)
		वापस;

	pmd = pmd_offset(pud, start);
	pud_clear(pud);
	pmd_मुक्त_tlb(tlb, pmd, start);
	mm_dec_nr_pmds(tlb->mm);
पूर्ण

अटल व्योम hugetlb_मुक्त_pud_range(काष्ठा mmu_gather *tlb, p4d_t *p4d,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				   अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ start;

	start = addr;
	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (pud_none_or_clear_bad(pud))
			जारी;
		अगर (is_hugetlb_pud(*pud))
			pud_clear(pud);
		अन्यथा
			hugetlb_मुक्त_pmd_range(tlb, pud, addr, next, न्यूनमान,
					       उच्चमानing);
	पूर्ण जबतक (pud++, addr = next, addr != end);

	start &= PGसूची_MASK;
	अगर (start < न्यूनमान)
		वापस;
	अगर (उच्चमानing) अणु
		उच्चमानing &= PGसूची_MASK;
		अगर (!उच्चमानing)
			वापस;
	पूर्ण
	अगर (end - 1 > उच्चमानing - 1)
		वापस;

	pud = pud_offset(p4d, start);
	p4d_clear(p4d);
	pud_मुक्त_tlb(tlb, pud, start);
	mm_dec_nr_puds(tlb->mm);
पूर्ण

व्योम hugetlb_मुक्त_pgd_range(काष्ठा mmu_gather *tlb,
			    अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			    अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	अचिन्हित दीर्घ next;

	addr &= PMD_MASK;
	अगर (addr < न्यूनमान) अणु
		addr += PMD_SIZE;
		अगर (!addr)
			वापस;
	पूर्ण
	अगर (उच्चमानing) अणु
		उच्चमानing &= PMD_MASK;
		अगर (!उच्चमानing)
			वापस;
	पूर्ण
	अगर (end - 1 > उच्चमानing - 1)
		end -= PMD_SIZE;
	अगर (addr > end - 1)
		वापस;

	pgd = pgd_offset(tlb->mm, addr);
	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none_or_clear_bad(p4d))
			जारी;
		hugetlb_मुक्त_pud_range(tlb, p4d, addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (p4d++, addr = next, addr != end);
पूर्ण
