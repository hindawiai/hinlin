<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PAGE_DEFS_H
#घोषणा _ASM_X86_PAGE_DEFS_H

#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>
#समावेश <linux/mem_encrypt.h>

/* PAGE_SHIFT determines the page size */
#घोषणा PAGE_SHIFT		12
#घोषणा PAGE_SIZE		(_AC(1,UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK		(~(PAGE_SIZE-1))

#घोषणा PMD_PAGE_SIZE		(_AC(1, UL) << PMD_SHIFT)
#घोषणा PMD_PAGE_MASK		(~(PMD_PAGE_SIZE-1))

#घोषणा PUD_PAGE_SIZE		(_AC(1, UL) << PUD_SHIFT)
#घोषणा PUD_PAGE_MASK		(~(PUD_PAGE_SIZE-1))

#घोषणा __VIRTUAL_MASK		((1UL << __VIRTUAL_MASK_SHIFT) - 1)

/* Cast *PAGE_MASK to a चिन्हित type so that it is sign-extended अगर
   भव addresses are 32-bits but physical addresses are larger
   (ie, 32-bit PAE). */
#घोषणा PHYSICAL_PAGE_MASK	(((चिन्हित दीर्घ)PAGE_MASK) & __PHYSICAL_MASK)
#घोषणा PHYSICAL_PMD_PAGE_MASK	(((चिन्हित दीर्घ)PMD_PAGE_MASK) & __PHYSICAL_MASK)
#घोषणा PHYSICAL_PUD_PAGE_MASK	(((चिन्हित दीर्घ)PUD_PAGE_MASK) & __PHYSICAL_MASK)

#घोषणा HPAGE_SHIFT		PMD_SHIFT
#घोषणा HPAGE_SIZE		(_AC(1,UL) << HPAGE_SHIFT)
#घोषणा HPAGE_MASK		(~(HPAGE_SIZE - 1))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)

#घोषणा HUGE_MAX_HSTATE 2

#घोषणा PAGE_OFFSET		((अचिन्हित दीर्घ)__PAGE_OFFSET)

#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_TSK_EXEC

#घोषणा __PHYSICAL_START	ALIGN(CONFIG_PHYSICAL_START, \
				      CONFIG_PHYSICAL_ALIGN)

#घोषणा __START_KERNEL		(__START_KERNEL_map + __PHYSICAL_START)

#अगर_घोषित CONFIG_X86_64
#समावेश <यंत्र/page_64_types.h>
#घोषणा IOREMAP_MAX_ORDER       (PUD_SHIFT)
#अन्यथा
#समावेश <यंत्र/page_32_types.h>
#घोषणा IOREMAP_MAX_ORDER       (PMD_SHIFT)
#पूर्ण_अगर	/* CONFIG_X86_64 */

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_DYNAMIC_PHYSICAL_MASK
बाह्य phys_addr_t physical_mask;
#घोषणा __PHYSICAL_MASK		physical_mask
#अन्यथा
#घोषणा __PHYSICAL_MASK		((phys_addr_t)((1ULL << __PHYSICAL_MASK_SHIFT) - 1))
#पूर्ण_अगर

बाह्य पूर्णांक devmem_is_allowed(अचिन्हित दीर्घ pagenr);

बाह्य अचिन्हित दीर्घ max_low_pfn_mapped;
बाह्य अचिन्हित दीर्घ max_pfn_mapped;

अटल अंतरभूत phys_addr_t get_max_mapped(व्योम)
अणु
	वापस (phys_addr_t)max_pfn_mapped << PAGE_SHIFT;
पूर्ण

bool pfn_range_is_mapped(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn);

बाह्य व्योम iniपंचांगem_init(व्योम);

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर	/* _ASM_X86_PAGE_DEFS_H */
