<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PFN_T_H_
#घोषणा _LINUX_PFN_T_H_
#समावेश <linux/mm.h>

/*
 * PFN_FLAGS_MASK - mask of all the possible valid pfn_t flags
 * PFN_SG_CHAIN - pfn is a poपूर्णांकer to the next scatterlist entry
 * PFN_SG_LAST - pfn references a page and is the last scatterlist entry
 * PFN_DEV - pfn is not covered by प्रणाली memmap by शेष
 * PFN_MAP - pfn has a dynamic page mapping established by a device driver
 * PFN_SPECIAL - क्रम CONFIG_FS_DAX_LIMITED builds to allow XIP, but not
 *		 get_user_pages
 */
#घोषणा PFN_FLAGS_MASK (((u64) (~PAGE_MASK)) << (BITS_PER_LONG_LONG - PAGE_SHIFT))
#घोषणा PFN_SG_CHAIN (1ULL << (BITS_PER_LONG_LONG - 1))
#घोषणा PFN_SG_LAST (1ULL << (BITS_PER_LONG_LONG - 2))
#घोषणा PFN_DEV (1ULL << (BITS_PER_LONG_LONG - 3))
#घोषणा PFN_MAP (1ULL << (BITS_PER_LONG_LONG - 4))
#घोषणा PFN_SPECIAL (1ULL << (BITS_PER_LONG_LONG - 5))

#घोषणा PFN_FLAGS_TRACE \
	अणु PFN_SPECIAL,	"SPECIAL" पूर्ण, \
	अणु PFN_SG_CHAIN,	"SG_CHAIN" पूर्ण, \
	अणु PFN_SG_LAST,	"SG_LAST" पूर्ण, \
	अणु PFN_DEV,	"DEV" पूर्ण, \
	अणु PFN_MAP,	"MAP" पूर्ण

अटल अंतरभूत pfn_t __pfn_to_pfn_t(अचिन्हित दीर्घ pfn, u64 flags)
अणु
	pfn_t pfn_t = अणु .val = pfn | (flags & PFN_FLAGS_MASK), पूर्ण;

	वापस pfn_t;
पूर्ण

/* a शेष pfn to pfn_t conversion assumes that @pfn is pfn_valid() */
अटल अंतरभूत pfn_t pfn_to_pfn_t(अचिन्हित दीर्घ pfn)
अणु
	वापस __pfn_to_pfn_t(pfn, 0);
पूर्ण

अटल अंतरभूत pfn_t phys_to_pfn_t(phys_addr_t addr, u64 flags)
अणु
	वापस __pfn_to_pfn_t(addr >> PAGE_SHIFT, flags);
पूर्ण

अटल अंतरभूत bool pfn_t_has_page(pfn_t pfn)
अणु
	वापस (pfn.val & PFN_MAP) == PFN_MAP || (pfn.val & PFN_DEV) == 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pfn_t_to_pfn(pfn_t pfn)
अणु
	वापस pfn.val & ~PFN_FLAGS_MASK;
पूर्ण

अटल अंतरभूत काष्ठा page *pfn_t_to_page(pfn_t pfn)
अणु
	अगर (pfn_t_has_page(pfn))
		वापस pfn_to_page(pfn_t_to_pfn(pfn));
	वापस शून्य;
पूर्ण

अटल अंतरभूत phys_addr_t pfn_t_to_phys(pfn_t pfn)
अणु
	वापस PFN_PHYS(pfn_t_to_pfn(pfn));
पूर्ण

अटल अंतरभूत pfn_t page_to_pfn_t(काष्ठा page *page)
अणु
	वापस pfn_to_pfn_t(page_to_pfn(page));
पूर्ण

अटल अंतरभूत पूर्णांक pfn_t_valid(pfn_t pfn)
अणु
	वापस pfn_valid(pfn_t_to_pfn(pfn));
पूर्ण

#अगर_घोषित CONFIG_MMU
अटल अंतरभूत pte_t pfn_t_pte(pfn_t pfn, pgprot_t pgprot)
अणु
	वापस pfn_pte(pfn_t_to_pfn(pfn), pgprot);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत pmd_t pfn_t_pmd(pfn_t pfn, pgprot_t pgprot)
अणु
	वापस pfn_pmd(pfn_t_to_pfn(pfn), pgprot);
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल अंतरभूत pud_t pfn_t_pud(pfn_t pfn, pgprot_t pgprot)
अणु
	वापस pfn_pud(pfn_t_to_pfn(pfn), pgprot);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_HAS_PTE_DEVMAP
अटल अंतरभूत bool pfn_t_devmap(pfn_t pfn)
अणु
	स्थिर u64 flags = PFN_DEV|PFN_MAP;

	वापस (pfn.val & flags) == flags;
पूर्ण
#अन्यथा
अटल अंतरभूत bool pfn_t_devmap(pfn_t pfn)
अणु
	वापस false;
पूर्ण
pte_t pte_mkdevmap(pte_t pte);
pmd_t pmd_mkdevmap(pmd_t pmd);
#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) && \
	defined(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD)
pud_t pud_mkdevmap(pud_t pud);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_ARCH_HAS_PTE_DEVMAP */

#अगर_घोषित CONFIG_ARCH_HAS_PTE_SPECIAL
अटल अंतरभूत bool pfn_t_special(pfn_t pfn)
अणु
	वापस (pfn.val & PFN_SPECIAL) == PFN_SPECIAL;
पूर्ण
#अन्यथा
अटल अंतरभूत bool pfn_t_special(pfn_t pfn)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_PTE_SPECIAL */
#पूर्ण_अगर /* _LINUX_PFN_T_H_ */
