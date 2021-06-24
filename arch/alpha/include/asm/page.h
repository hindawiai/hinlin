<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_PAGE_H
#घोषणा _ALPHA_PAGE_H

#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/pal.h>

/* PAGE_SHIFT determines the page size */
#घोषणा PAGE_SHIFT	13
#घोषणा PAGE_SIZE	(_AC(1,UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))

#अगर_अघोषित __ASSEMBLY__

#घोषणा STRICT_MM_TYPECHECKS

बाह्य व्योम clear_page(व्योम *page);
#घोषणा clear_user_page(page, vaddr, pg)	clear_page(page)

#घोषणा __alloc_zeroed_user_highpage(movableflags, vma, vaddr) \
	alloc_page_vma(GFP_HIGHUSER | __GFP_ZERO | movableflags, vma, vmaddr)
#घोषणा __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE

बाह्य व्योम copy_page(व्योम * _to, व्योम * _from);
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

#अगर_घोषित STRICT_MM_TYPECHECKS
/*
 * These are used to make use of C type-checking..
 */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;

#घोषणा pte_val(x)	((x).pte)
#घोषणा pmd_val(x)	((x).pmd)
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#घोषणा __pmd(x)	((pmd_t) अणु (x) पूर्ण )
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

#अन्यथा
/*
 * .. जबतक these make it easier on the compiler
 */
प्रकार अचिन्हित दीर्घ pte_t;
प्रकार अचिन्हित दीर्घ pmd_t;
प्रकार अचिन्हित दीर्घ pgd_t;
प्रकार अचिन्हित दीर्घ pgprot_t;

#घोषणा pte_val(x)	(x)
#घोषणा pmd_val(x)	(x)
#घोषणा pgd_val(x)	(x)
#घोषणा pgprot_val(x)	(x)

#घोषणा __pte(x)	(x)
#घोषणा __pgd(x)	(x)
#घोषणा __pgprot(x)	(x)

#पूर्ण_अगर /* STRICT_MM_TYPECHECKS */

प्रकार काष्ठा page *pgtable_t;

#अगर_घोषित USE_48_BIT_KSEG
#घोषणा PAGE_OFFSET		0xffff800000000000UL
#अन्यथा
#घोषणा PAGE_OFFSET		0xfffffc0000000000UL
#पूर्ण_अगर

#अन्यथा

#अगर_घोषित USE_48_BIT_KSEG
#घोषणा PAGE_OFFSET		0xffff800000000000
#अन्यथा
#घोषणा PAGE_OFFSET		0xfffffc0000000000
#पूर्ण_अगर

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा __pa(x)			((अचिन्हित दीर्घ) (x) - PAGE_OFFSET)
#घोषणा __va(x)			((व्योम *)((अचिन्हित दीर्घ) (x) + PAGE_OFFSET))

#घोषणा virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा virt_addr_valid(kaddr)	pfn_valid((__pa(kaddr) >> PAGE_SHIFT))

#अगर_घोषित CONFIG_FLATMEM
#घोषणा pfn_valid(pfn)		((pfn) < max_mapnr)
#पूर्ण_अगर /* CONFIG_FLATMEM */

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _ALPHA_PAGE_H */
