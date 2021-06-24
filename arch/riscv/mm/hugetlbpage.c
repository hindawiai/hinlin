<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/hugetlb.h>
#समावेश <linux/err.h>

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस pud_leaf(pud);
पूर्ण

पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस pmd_leaf(pmd);
पूर्ण

bool __init arch_hugetlb_valid_size(अचिन्हित दीर्घ size)
अणु
	अगर (size == HPAGE_SIZE)
		वापस true;
	अन्यथा अगर (IS_ENABLED(CONFIG_64BIT) && size == PUD_SIZE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

#अगर_घोषित CONFIG_CONTIG_ALLOC
अटल __init पूर्णांक gigantic_pages_init(व्योम)
अणु
	/* With CONTIG_ALLOC, we can allocate gigantic pages at runसमय */
	अगर (IS_ENABLED(CONFIG_64BIT))
		hugetlb_add_hstate(PUD_SHIFT - PAGE_SHIFT);
	वापस 0;
पूर्ण
arch_initcall(gigantic_pages_init);
#पूर्ण_अगर
