<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_PGTABLE_64K_H
#घोषणा _ASM_POWERPC_BOOK3S_64_PGTABLE_64K_H

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_HUGETLB_PAGE
/*
 * We have PGD_INDEX_SIZ = 12 and PTE_INDEX_SIZE = 8, so that we can have
 * 16GB hugepage pte in PGD and 16MB hugepage pte at PMD;
 *
 * Defined in such a way that we can optimize away code block at build समय
 * अगर CONFIG_HUGETLB_PAGE=n.
 *
 * वापसs true क्रम pmd migration entries, THP, devmap, hugetlb
 * But compile समय dependent on CONFIG_HUGETLB_PAGE
 */
अटल अंतरभूत पूर्णांक pmd_huge(pmd_t pmd)
अणु
	/*
	 * leaf pte क्रम huge page
	 */
	वापस !!(pmd_raw(pmd) & cpu_to_be64(_PAGE_PTE));
पूर्ण

अटल अंतरभूत पूर्णांक pud_huge(pud_t pud)
अणु
	/*
	 * leaf pte क्रम huge page
	 */
	वापस !!(pud_raw(pud) & cpu_to_be64(_PAGE_PTE));
पूर्ण

अटल अंतरभूत पूर्णांक pgd_huge(pgd_t pgd)
अणु
	/*
	 * leaf pte क्रम huge page
	 */
	वापस !!(pgd_raw(pgd) & cpu_to_be64(_PAGE_PTE));
पूर्ण
#घोषणा pgd_huge pgd_huge

/*
 * With 64k page size, we have hugepage ptes in the pgd and pmd entries. We करोn't
 * need to setup hugepage directory क्रम them. Our pte and page directory क्रमmat
 * enable us to have this enabled.
 */
अटल अंतरभूत पूर्णांक hugepd_ok(hugepd_t hpd)
अणु
	वापस 0;
पूर्ण

#घोषणा is_hugepd(pdep)			0

/*
 * This should never get called
 */
अटल अंतरभूत पूर्णांक get_hugepd_cache_index(पूर्णांक index)
अणु
	BUG();
पूर्ण

#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

अटल अंतरभूत पूर्णांक remap_4k_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			       अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	अगर (radix_enabled())
		BUG();
	वापस hash__remap_4k_pfn(vma, addr, pfn, prot);
पूर्ण
#पूर्ण_अगर	/* __ASSEMBLY__ */
#पूर्ण_अगर /*_ASM_POWERPC_BOOK3S_64_PGTABLE_64K_H */
