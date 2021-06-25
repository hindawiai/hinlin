<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_PAGE_H
#घोषणा __ASM_GENERIC_PAGE_H
/*
 * Generic page.h implementation, क्रम NOMMU architectures.
 * This provides the dummy definitions क्रम the memory management.
 */

#अगर_घोषित CONFIG_MMU
#त्रुटि need to provide a real यंत्र/page.h
#पूर्ण_अगर


/* PAGE_SHIFT determines the page size */

#घोषणा PAGE_SHIFT	12
#अगर_घोषित __ASSEMBLY__
#घोषणा PAGE_SIZE	(1 << PAGE_SHIFT)
#अन्यथा
#घोषणा PAGE_SIZE	(1UL << PAGE_SHIFT)
#पूर्ण_अगर
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))

#समावेश <यंत्र/setup.h>

#अगर_अघोषित __ASSEMBLY__

#घोषणा clear_page(page)	स_रखो((page), 0, PAGE_SIZE)
#घोषणा copy_page(to,from)	स_नकल((to), (from), PAGE_SIZE)

#घोषणा clear_user_page(page, vaddr, pg)	clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

/*
 * These are used to make use of C type-checking..
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pte;
पूर्ण pte_t;
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pmd[16];
पूर्ण pmd_t;
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pgd;
पूर्ण pgd_t;
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pgprot;
पूर्ण pgprot_t;
प्रकार काष्ठा page *pgtable_t;

#घोषणा pte_val(x)	((x).pte)
#घोषणा pmd_val(x)	((&x)->pmd[0])
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#घोषणा __pmd(x)	((pmd_t) अणु (x) पूर्ण )
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

बाह्य अचिन्हित दीर्घ memory_start;
बाह्य अचिन्हित दीर्घ memory_end;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा PAGE_OFFSET		(0)

#अगर_अघोषित ARCH_PFN_OFFSET
#घोषणा ARCH_PFN_OFFSET		(PAGE_OFFSET >> PAGE_SHIFT)
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#घोषणा __va(x) ((व्योम *)((अचिन्हित दीर्घ) (x)))
#घोषणा __pa(x) ((अचिन्हित दीर्घ) (x))

#घोषणा virt_to_pfn(kaddr)	(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा pfn_to_virt(pfn)	__va((pfn) << PAGE_SHIFT)

#घोषणा virt_to_page(addr)	pfn_to_page(virt_to_pfn(addr))
#घोषणा page_to_virt(page)	pfn_to_virt(page_to_pfn(page))

#अगर_अघोषित page_to_phys
#घोषणा page_to_phys(page)      ((dma_addr_t)page_to_pfn(page) << PAGE_SHIFT)
#पूर्ण_अगर

#घोषणा pfn_valid(pfn)		((pfn) >= ARCH_PFN_OFFSET && ((pfn) - ARCH_PFN_OFFSET) < max_mapnr)

#घोषणा	virt_addr_valid(kaddr)	(((व्योम *)(kaddr) >= (व्योम *)PAGE_OFFSET) && \
				((व्योम *)(kaddr) < (व्योम *)memory_end))

#पूर्ण_अगर /* __ASSEMBLY__ */

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* __ASM_GENERIC_PAGE_H */
