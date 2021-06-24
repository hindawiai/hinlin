<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_PGALLOC_H
#घोषणा _ASM_POWERPC_BOOK3S_64_PGALLOC_H
/*
 */

#समावेश <linux/slab.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/percpu.h>

काष्ठा vmemmap_backing अणु
	काष्ठा vmemmap_backing *list;
	अचिन्हित दीर्घ phys;
	अचिन्हित दीर्घ virt_addr;
पूर्ण;
बाह्य काष्ठा vmemmap_backing *vmemmap_list;

बाह्य pmd_t *pmd_fragment_alloc(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ);
बाह्य व्योम pmd_fragment_मुक्त(अचिन्हित दीर्घ *);
बाह्य व्योम pgtable_मुक्त_tlb(काष्ठा mmu_gather *tlb, व्योम *table, पूर्णांक shअगरt);
बाह्य व्योम __tlb_हटाओ_table(व्योम *_table);
व्योम pte_frag_destroy(व्योम *pte_frag);

अटल अंतरभूत pgd_t *radix__pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PPC_64K_PAGES
	वापस (pgd_t *)__get_मुक्त_page(pgtable_gfp_flags(mm, PGALLOC_GFP));
#अन्यथा
	काष्ठा page *page;
	page = alloc_pages(pgtable_gfp_flags(mm, PGALLOC_GFP | __GFP_RETRY_MAYFAIL),
				4);
	अगर (!page)
		वापस शून्य;
	वापस (pgd_t *) page_address(page);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम radix__pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
#अगर_घोषित CONFIG_PPC_64K_PAGES
	मुक्त_page((अचिन्हित दीर्घ)pgd);
#अन्यथा
	मुक्त_pages((अचिन्हित दीर्घ)pgd, 4);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd;

	अगर (radix_enabled())
		वापस radix__pgd_alloc(mm);

	pgd = kmem_cache_alloc(PGT_CACHE(PGD_INDEX_SIZE),
			       pgtable_gfp_flags(mm, GFP_KERNEL));
	अगर (unlikely(!pgd))
		वापस pgd;

	/*
	 * Don't scan the PGD क्रम poपूर्णांकers, it contains references to PUDs but
	 * those references are not full poपूर्णांकers and so can't be recognised by
	 * kmemleak.
	 */
	kmemleak_no_scan(pgd);

	/*
	 * With hugetlb, we करोn't clear the second half of the page table.
	 * If we share the same slab cache with the pmd or pud level table,
	 * we need to make sure we zero out the full table on alloc.
	 * With 4K we करोn't store slot in the second half. Hence we don't
	 * need to करो this क्रम 4k.
	 */
#अगर defined(CONFIG_HUGETLB_PAGE) && defined(CONFIG_PPC_64K_PAGES) && \
	(H_PGD_INDEX_SIZE == H_PUD_CACHE_INDEX)
	स_रखो(pgd, 0, PGD_TABLE_SIZE);
#पूर्ण_अगर
	वापस pgd;
पूर्ण

अटल अंतरभूत व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	अगर (radix_enabled())
		वापस radix__pgd_मुक्त(mm, pgd);
	kmem_cache_मुक्त(PGT_CACHE(PGD_INDEX_SIZE), pgd);
पूर्ण

अटल अंतरभूत व्योम p4d_populate(काष्ठा mm_काष्ठा *mm, p4d_t *pgd, pud_t *pud)
अणु
	*pgd =  __p4d(__pgtable_ptr_val(pud) | PGD_VAL_BITS);
पूर्ण

अटल अंतरभूत pud_t *pud_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pud_t *pud;

	pud = kmem_cache_alloc(PGT_CACHE(PUD_CACHE_INDEX),
			       pgtable_gfp_flags(mm, GFP_KERNEL));
	/*
	 * Tell kmemleak to ignore the PUD, that means करोn't scan it क्रम
	 * poपूर्णांकers and करोn't consider it a leak. PUDs are typically only
	 * referred to by their PGD, but kmemleak is not able to recognise those
	 * as poपूर्णांकers, leading to false leak reports.
	 */
	kmemleak_ignore(pud);

	वापस pud;
पूर्ण

अटल अंतरभूत व्योम __pud_मुक्त(pud_t *pud)
अणु
	काष्ठा page *page = virt_to_page(pud);

	/*
	 * Early pud pages allocated via memblock allocator
	 * can't be directly मुक्तd to slab
	 */
	अगर (PageReserved(page))
		मुक्त_reserved_page(page);
	अन्यथा
		kmem_cache_मुक्त(PGT_CACHE(PUD_CACHE_INDEX), pud);
पूर्ण

अटल अंतरभूत व्योम pud_मुक्त(काष्ठा mm_काष्ठा *mm, pud_t *pud)
अणु
	वापस __pud_मुक्त(pud);
पूर्ण

अटल अंतरभूत व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pud, pmd_t *pmd)
अणु
	*pud = __pud(__pgtable_ptr_val(pmd) | PUD_VAL_BITS);
पूर्ण

अटल अंतरभूत व्योम __pud_मुक्त_tlb(काष्ठा mmu_gather *tlb, pud_t *pud,
				  अचिन्हित दीर्घ address)
अणु
	pgtable_मुक्त_tlb(tlb, pud, PUD_INDEX);
पूर्ण

अटल अंतरभूत pmd_t *pmd_alloc_one(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस pmd_fragment_alloc(mm, addr);
पूर्ण

अटल अंतरभूत व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	pmd_fragment_मुक्त((अचिन्हित दीर्घ *)pmd);
पूर्ण

अटल अंतरभूत व्योम __pmd_मुक्त_tlb(काष्ठा mmu_gather *tlb, pmd_t *pmd,
				  अचिन्हित दीर्घ address)
अणु
	वापस pgtable_मुक्त_tlb(tlb, pmd, PMD_INDEX);
पूर्ण

अटल अंतरभूत व्योम pmd_populate_kernel(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				       pte_t *pte)
अणु
	*pmd = __pmd(__pgtable_ptr_val(pte) | PMD_VAL_BITS);
पूर्ण

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				pgtable_t pte_page)
अणु
	*pmd = __pmd(__pgtable_ptr_val(pte_page) | PMD_VAL_BITS);
पूर्ण

अटल अंतरभूत व्योम __pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, pgtable_t table,
				  अचिन्हित दीर्घ address)
अणु
	pgtable_मुक्त_tlb(tlb, table, PTE_INDEX);
पूर्ण

बाह्य atomic_दीर्घ_t direct_pages_count[MMU_PAGE_COUNT];
अटल अंतरभूत व्योम update_page_count(पूर्णांक psize, दीर्घ count)
अणु
	अगर (IS_ENABLED(CONFIG_PROC_FS))
		atomic_दीर्घ_add(count, &direct_pages_count[psize]);
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_64_PGALLOC_H */
