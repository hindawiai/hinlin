<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm64/mm/hugetlbpage.c
 *
 * Copyright (C) 2013 Linaro Ltd.
 *
 * Based on arch/x86/mm/hugetlbpage.c.
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/err.h>
#समावेश <linux/sysctl.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>

/*
 * HugeTLB Support Matrix
 *
 * ---------------------------------------------------
 * | Page Size | CONT PTE |  PMD  | CONT PMD |  PUD  |
 * ---------------------------------------------------
 * |     4K    |   64K    |   2M  |    32M   |   1G  |
 * |    16K    |    2M    |  32M  |     1G   |       |
 * |    64K    |    2M    | 512M  |    16G   |       |
 * ---------------------------------------------------
 */

/*
 * Reserve CMA areas क्रम the largest supported gigantic
 * huge page when requested. Any other smaller gigantic
 * huge pages could still be served from those areas.
 */
#अगर_घोषित CONFIG_CMA
व्योम __init arm64_hugetlb_cma_reserve(व्योम)
अणु
	पूर्णांक order;

#अगर_घोषित CONFIG_ARM64_4K_PAGES
	order = PUD_SHIFT - PAGE_SHIFT;
#अन्यथा
	order = CONT_PMD_SHIFT + PMD_SHIFT - PAGE_SHIFT;
#पूर्ण_अगर
	/*
	 * HugeTLB CMA reservation is required क्रम gigantic
	 * huge pages which could not be allocated via the
	 * page allocator. Just warn अगर there is any change
	 * अवरोधing this assumption.
	 */
	WARN_ON(order <= MAX_ORDER);
	hugetlb_cma_reserve(order);
पूर्ण
#पूर्ण_अगर /* CONFIG_CMA */

#अगर_घोषित CONFIG_ARCH_ENABLE_HUGEPAGE_MIGRATION
bool arch_hugetlb_migration_supported(काष्ठा hstate *h)
अणु
	माप_प्रकार pagesize = huge_page_size(h);

	चयन (pagesize) अणु
#अगर_घोषित CONFIG_ARM64_4K_PAGES
	हाल PUD_SIZE:
#पूर्ण_अगर
	हाल PMD_SIZE:
	हाल CONT_PMD_SIZE:
	हाल CONT_PTE_SIZE:
		वापस true;
	पूर्ण
	pr_warn("%s: unrecognized huge page size 0x%lx\n",
			__func__, pagesize);
	वापस false;
पूर्ण
#पूर्ण_अगर

पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस pmd_val(pmd) && !(pmd_val(pmd) & PMD_TABLE_BIT);
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	वापस pud_val(pud) && !(pud_val(pud) & PUD_TABLE_BIT);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * Select all bits except the pfn
 */
अटल अंतरभूत pgprot_t pte_pgprot(pte_t pte)
अणु
	अचिन्हित दीर्घ pfn = pte_pfn(pte);

	वापस __pgprot(pte_val(pfn_pte(pfn, __pgprot(0))) ^ pte_val(pte));
पूर्ण

अटल पूर्णांक find_num_contig(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			   pte_t *ptep, माप_प्रकार *pgsize)
अणु
	pgd_t *pgdp = pgd_offset(mm, addr);
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;

	*pgsize = PAGE_SIZE;
	p4dp = p4d_offset(pgdp, addr);
	pudp = pud_offset(p4dp, addr);
	pmdp = pmd_offset(pudp, addr);
	अगर ((pte_t *)pmdp == ptep) अणु
		*pgsize = PMD_SIZE;
		वापस CONT_PMDS;
	पूर्ण
	वापस CONT_PTES;
पूर्ण

अटल अंतरभूत पूर्णांक num_contig_ptes(अचिन्हित दीर्घ size, माप_प्रकार *pgsize)
अणु
	पूर्णांक contig_ptes = 0;

	*pgsize = size;

	चयन (size) अणु
#अगर_घोषित CONFIG_ARM64_4K_PAGES
	हाल PUD_SIZE:
#पूर्ण_अगर
	हाल PMD_SIZE:
		contig_ptes = 1;
		अवरोध;
	हाल CONT_PMD_SIZE:
		*pgsize = PMD_SIZE;
		contig_ptes = CONT_PMDS;
		अवरोध;
	हाल CONT_PTE_SIZE:
		*pgsize = PAGE_SIZE;
		contig_ptes = CONT_PTES;
		अवरोध;
	पूर्ण

	वापस contig_ptes;
पूर्ण

/*
 * Changing some bits of contiguous entries requires us to follow a
 * Break-Beक्रमe-Make approach, अवरोधing the whole contiguous set
 * beक्रमe we can change any entries. See ARM DDI 0487A.k_iss10775,
 * "Misprogramming of the Contiguous bit", page D4-1762.
 *
 * This helper perक्रमms the अवरोध step.
 */
अटल pte_t get_clear_flush(काष्ठा mm_काष्ठा *mm,
			     अचिन्हित दीर्घ addr,
			     pte_t *ptep,
			     अचिन्हित दीर्घ pgsize,
			     अचिन्हित दीर्घ ncontig)
अणु
	pte_t orig_pte = huge_ptep_get(ptep);
	bool valid = pte_valid(orig_pte);
	अचिन्हित दीर्घ i, saddr = addr;

	क्रम (i = 0; i < ncontig; i++, addr += pgsize, ptep++) अणु
		pte_t pte = ptep_get_and_clear(mm, addr, ptep);

		/*
		 * If HW_AFDBM is enabled, then the HW could turn on
		 * the dirty or accessed bit क्रम any page in the set,
		 * so check them all.
		 */
		अगर (pte_dirty(pte))
			orig_pte = pte_सूची_गढ़ोty(orig_pte);

		अगर (pte_young(pte))
			orig_pte = pte_mkyoung(orig_pte);
	पूर्ण

	अगर (valid) अणु
		काष्ठा vm_area_काष्ठा vma = TLB_FLUSH_VMA(mm, 0);
		flush_tlb_range(&vma, saddr, addr);
	पूर्ण
	वापस orig_pte;
पूर्ण

/*
 * Changing some bits of contiguous entries requires us to follow a
 * Break-Beक्रमe-Make approach, अवरोधing the whole contiguous set
 * beक्रमe we can change any entries. See ARM DDI 0487A.k_iss10775,
 * "Misprogramming of the Contiguous bit", page D4-1762.
 *
 * This helper perक्रमms the अवरोध step क्रम use हालs where the
 * original pte is not needed.
 */
अटल व्योम clear_flush(काष्ठा mm_काष्ठा *mm,
			     अचिन्हित दीर्घ addr,
			     pte_t *ptep,
			     अचिन्हित दीर्घ pgsize,
			     अचिन्हित दीर्घ ncontig)
अणु
	काष्ठा vm_area_काष्ठा vma = TLB_FLUSH_VMA(mm, 0);
	अचिन्हित दीर्घ i, saddr = addr;

	क्रम (i = 0; i < ncontig; i++, addr += pgsize, ptep++)
		pte_clear(mm, addr, ptep);

	flush_tlb_range(&vma, saddr, addr);
पूर्ण

व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			    pte_t *ptep, pte_t pte)
अणु
	माप_प्रकार pgsize;
	पूर्णांक i;
	पूर्णांक ncontig;
	अचिन्हित दीर्घ pfn, dpfn;
	pgprot_t hugeprot;

	/*
	 * Code needs to be expanded to handle huge swap and migration
	 * entries. Needed क्रम HUGETLB and MEMORY_FAILURE.
	 */
	WARN_ON(!pte_present(pte));

	अगर (!pte_cont(pte)) अणु
		set_pte_at(mm, addr, ptep, pte);
		वापस;
	पूर्ण

	ncontig = find_num_contig(mm, addr, ptep, &pgsize);
	pfn = pte_pfn(pte);
	dpfn = pgsize >> PAGE_SHIFT;
	hugeprot = pte_pgprot(pte);

	clear_flush(mm, addr, ptep, pgsize, ncontig);

	क्रम (i = 0; i < ncontig; i++, ptep++, addr += pgsize, pfn += dpfn)
		set_pte_at(mm, addr, ptep, pfn_pte(pfn, hugeprot));
पूर्ण

व्योम set_huge_swap_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			  pte_t *ptep, pte_t pte, अचिन्हित दीर्घ sz)
अणु
	पूर्णांक i, ncontig;
	माप_प्रकार pgsize;

	ncontig = num_contig_ptes(sz, &pgsize);

	क्रम (i = 0; i < ncontig; i++, ptep++)
		set_pte(ptep, pte);
पूर्ण

pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep = शून्य;

	pgdp = pgd_offset(mm, addr);
	p4dp = p4d_offset(pgdp, addr);
	pudp = pud_alloc(mm, p4dp, addr);
	अगर (!pudp)
		वापस शून्य;

	अगर (sz == PUD_SIZE) अणु
		ptep = (pte_t *)pudp;
	पूर्ण अन्यथा अगर (sz == (CONT_PTE_SIZE)) अणु
		pmdp = pmd_alloc(mm, pudp, addr);
		अगर (!pmdp)
			वापस शून्य;

		WARN_ON(addr & (sz - 1));
		/*
		 * Note that अगर this code were ever ported to the
		 * 32-bit arm platक्रमm then it will cause trouble in
		 * the हाल where CONFIG_HIGHPTE is set, since there
		 * will be no pte_unmap() to correspond with this
		 * pte_alloc_map().
		 */
		ptep = pte_alloc_map(mm, pmdp, addr);
	पूर्ण अन्यथा अगर (sz == PMD_SIZE) अणु
		अगर (want_pmd_share(vma, addr) && pud_none(READ_ONCE(*pudp)))
			ptep = huge_pmd_share(mm, vma, addr, pudp);
		अन्यथा
			ptep = (pte_t *)pmd_alloc(mm, pudp, addr);
	पूर्ण अन्यथा अगर (sz == (CONT_PMD_SIZE)) अणु
		pmdp = pmd_alloc(mm, pudp, addr);
		WARN_ON(addr & (sz - 1));
		वापस (pte_t *)pmdp;
	पूर्ण

	वापस ptep;
पूर्ण

pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm,
		       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp, pud;
	pmd_t *pmdp, pmd;

	pgdp = pgd_offset(mm, addr);
	अगर (!pgd_present(READ_ONCE(*pgdp)))
		वापस शून्य;

	p4dp = p4d_offset(pgdp, addr);
	अगर (!p4d_present(READ_ONCE(*p4dp)))
		वापस शून्य;

	pudp = pud_offset(p4dp, addr);
	pud = READ_ONCE(*pudp);
	अगर (sz != PUD_SIZE && pud_none(pud))
		वापस शून्य;
	/* hugepage or swap? */
	अगर (pud_huge(pud) || !pud_present(pud))
		वापस (pte_t *)pudp;
	/* table; check the next level */

	अगर (sz == CONT_PMD_SIZE)
		addr &= CONT_PMD_MASK;

	pmdp = pmd_offset(pudp, addr);
	pmd = READ_ONCE(*pmdp);
	अगर (!(sz == PMD_SIZE || sz == CONT_PMD_SIZE) &&
	    pmd_none(pmd))
		वापस शून्य;
	अगर (pmd_huge(pmd) || !pmd_present(pmd))
		वापस (pte_t *)pmdp;

	अगर (sz == CONT_PTE_SIZE)
		वापस pte_offset_kernel(pmdp, (addr & CONT_PTE_MASK));

	वापस शून्य;
पूर्ण

pte_t arch_make_huge_pte(pte_t entry, काष्ठा vm_area_काष्ठा *vma,
			 काष्ठा page *page, पूर्णांक writable)
अणु
	माप_प्रकार pagesize = huge_page_size(hstate_vma(vma));

	अगर (pagesize == CONT_PTE_SIZE) अणु
		entry = pte_mkcont(entry);
	पूर्ण अन्यथा अगर (pagesize == CONT_PMD_SIZE) अणु
		entry = pmd_pte(pmd_mkcont(pte_pmd(entry)));
	पूर्ण अन्यथा अगर (pagesize != PUD_SIZE && pagesize != PMD_SIZE) अणु
		pr_warn("%s: unrecognized huge page size 0x%lx\n",
			__func__, pagesize);
	पूर्ण
	वापस entry;
पूर्ण

व्योम huge_pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		    pte_t *ptep, अचिन्हित दीर्घ sz)
अणु
	पूर्णांक i, ncontig;
	माप_प्रकार pgsize;

	ncontig = num_contig_ptes(sz, &pgsize);

	क्रम (i = 0; i < ncontig; i++, addr += pgsize, ptep++)
		pte_clear(mm, addr, ptep);
पूर्ण

pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
			      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	पूर्णांक ncontig;
	माप_प्रकार pgsize;
	pte_t orig_pte = huge_ptep_get(ptep);

	अगर (!pte_cont(orig_pte))
		वापस ptep_get_and_clear(mm, addr, ptep);

	ncontig = find_num_contig(mm, addr, ptep, &pgsize);

	वापस get_clear_flush(mm, addr, ptep, pgsize, ncontig);
पूर्ण

/*
 * huge_ptep_set_access_flags will update access flags (dirty, accesssed)
 * and ग_लिखो permission.
 *
 * For a contiguous huge pte range we need to check whether or not ग_लिखो
 * permission has to change only on the first pte in the set. Then क्रम
 * all the contiguous ptes we need to check whether or not there is a
 * discrepancy between dirty or young.
 */
अटल पूर्णांक __cont_access_flags_changed(pte_t *ptep, pte_t pte, पूर्णांक ncontig)
अणु
	पूर्णांक i;

	अगर (pte_ग_लिखो(pte) != pte_ग_लिखो(huge_ptep_get(ptep)))
		वापस 1;

	क्रम (i = 0; i < ncontig; i++) अणु
		pte_t orig_pte = huge_ptep_get(ptep + i);

		अगर (pte_dirty(pte) != pte_dirty(orig_pte))
			वापस 1;

		अगर (pte_young(pte) != pte_young(orig_pte))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ addr, pte_t *ptep,
			       pte_t pte, पूर्णांक dirty)
अणु
	पूर्णांक ncontig, i;
	माप_प्रकार pgsize = 0;
	अचिन्हित दीर्घ pfn = pte_pfn(pte), dpfn;
	pgprot_t hugeprot;
	pte_t orig_pte;

	अगर (!pte_cont(pte))
		वापस ptep_set_access_flags(vma, addr, ptep, pte, dirty);

	ncontig = find_num_contig(vma->vm_mm, addr, ptep, &pgsize);
	dpfn = pgsize >> PAGE_SHIFT;

	अगर (!__cont_access_flags_changed(ptep, pte, ncontig))
		वापस 0;

	orig_pte = get_clear_flush(vma->vm_mm, addr, ptep, pgsize, ncontig);

	/* Make sure we करोn't lose the dirty or young state */
	अगर (pte_dirty(orig_pte))
		pte = pte_सूची_गढ़ोty(pte);

	अगर (pte_young(orig_pte))
		pte = pte_mkyoung(pte);

	hugeprot = pte_pgprot(pte);
	क्रम (i = 0; i < ncontig; i++, ptep++, addr += pgsize, pfn += dpfn)
		set_pte_at(vma->vm_mm, addr, ptep, pfn_pte(pfn, hugeprot));

	वापस 1;
पूर्ण

व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
			     अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ pfn, dpfn;
	pgprot_t hugeprot;
	पूर्णांक ncontig, i;
	माप_प्रकार pgsize;
	pte_t pte;

	अगर (!pte_cont(READ_ONCE(*ptep))) अणु
		ptep_set_wrprotect(mm, addr, ptep);
		वापस;
	पूर्ण

	ncontig = find_num_contig(mm, addr, ptep, &pgsize);
	dpfn = pgsize >> PAGE_SHIFT;

	pte = get_clear_flush(mm, addr, ptep, pgsize, ncontig);
	pte = pte_wrprotect(pte);

	hugeprot = pte_pgprot(pte);
	pfn = pte_pfn(pte);

	क्रम (i = 0; i < ncontig; i++, ptep++, addr += pgsize, pfn += dpfn)
		set_pte_at(mm, addr, ptep, pfn_pte(pfn, hugeprot));
पूर्ण

व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	माप_प्रकार pgsize;
	पूर्णांक ncontig;

	अगर (!pte_cont(READ_ONCE(*ptep))) अणु
		ptep_clear_flush(vma, addr, ptep);
		वापस;
	पूर्ण

	ncontig = find_num_contig(vma->vm_mm, addr, ptep, &pgsize);
	clear_flush(vma->vm_mm, addr, ptep, pgsize, ncontig);
पूर्ण

अटल पूर्णांक __init hugetlbpage_init(व्योम)
अणु
#अगर_घोषित CONFIG_ARM64_4K_PAGES
	hugetlb_add_hstate(PUD_SHIFT - PAGE_SHIFT);
#पूर्ण_अगर
	hugetlb_add_hstate(CONT_PMD_SHIFT - PAGE_SHIFT);
	hugetlb_add_hstate(PMD_SHIFT - PAGE_SHIFT);
	hugetlb_add_hstate(CONT_PTE_SHIFT - PAGE_SHIFT);

	वापस 0;
पूर्ण
arch_initcall(hugetlbpage_init);

bool __init arch_hugetlb_valid_size(अचिन्हित दीर्घ size)
अणु
	चयन (size) अणु
#अगर_घोषित CONFIG_ARM64_4K_PAGES
	हाल PUD_SIZE:
#पूर्ण_अगर
	हाल CONT_PMD_SIZE:
	हाल PMD_SIZE:
	हाल CONT_PTE_SIZE:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
