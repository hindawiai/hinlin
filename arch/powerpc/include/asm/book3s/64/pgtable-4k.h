<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_PGTABLE_4K_H
#घोषणा _ASM_POWERPC_BOOK3S_64_PGTABLE_4K_H
/*
 * hash 4k can't share hugetlb and also doesn't support THP
 */
#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल अंतरभूत पूर्णांक pmd_huge(pmd_t pmd)
अणु
	/*
	 * leaf pte क्रम huge page
	 */
	अगर (radix_enabled())
		वापस !!(pmd_raw(pmd) & cpu_to_be64(_PAGE_PTE));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pud_huge(pud_t pud)
अणु
	/*
	 * leaf pte क्रम huge page
	 */
	अगर (radix_enabled())
		वापस !!(pud_raw(pud) & cpu_to_be64(_PAGE_PTE));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pgd_huge(pgd_t pgd)
अणु
	/*
	 * leaf pte क्रम huge page
	 */
	अगर (radix_enabled())
		वापस !!(pgd_raw(pgd) & cpu_to_be64(_PAGE_PTE));
	वापस 0;
पूर्ण
#घोषणा pgd_huge pgd_huge
/*
 * With radix , we have hugepage ptes in the pud and pmd entries. We करोn't
 * need to setup hugepage directory क्रम them. Our pte and page directory क्रमmat
 * enable us to have this enabled.
 */
अटल अंतरभूत पूर्णांक hugepd_ok(hugepd_t hpd)
अणु
	अगर (radix_enabled())
		वापस 0;
	वापस hash__hugepd_ok(hpd);
पूर्ण
#घोषणा is_hugepd(hpd)		(hugepd_ok(hpd))

/*
 * 16M and 16G huge page directory tables are allocated from slab cache
 *
 */
#घोषणा H_16M_CACHE_INDEX (PAGE_SHIFT + H_PTE_INDEX_SIZE + H_PMD_INDEX_SIZE - 24)
#घोषणा H_16G_CACHE_INDEX                                                      \
	(PAGE_SHIFT + H_PTE_INDEX_SIZE + H_PMD_INDEX_SIZE + H_PUD_INDEX_SIZE - 34)

अटल अंतरभूत पूर्णांक get_hugepd_cache_index(पूर्णांक index)
अणु
	चयन (index) अणु
	हाल H_16M_CACHE_INDEX:
		वापस HTLB_16M_INDEX;
	हाल H_16G_CACHE_INDEX:
		वापस HTLB_16G_INDEX;
	शेष:
		BUG();
	पूर्ण
	/* should not reach */
पूर्ण

#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /*_ASM_POWERPC_BOOK3S_64_PGTABLE_4K_H */
