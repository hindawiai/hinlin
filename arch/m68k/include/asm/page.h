<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_PAGE_H
#घोषणा _M68K_PAGE_H

#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page_offset.h>

/* PAGE_SHIFT determines the page size */
#अगर defined(CONFIG_SUN3) || defined(CONFIG_COLDFIRE)
#घोषणा PAGE_SHIFT	13
#अन्यथा
#घोषणा PAGE_SHIFT	12
#पूर्ण_अगर
#घोषणा PAGE_SIZE	(_AC(1, UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))
#घोषणा PAGE_OFFSET	(PAGE_OFFSET_RAW)

#अगर_अघोषित __ASSEMBLY__

/*
 * These are used to make use of C type-checking..
 */
#अगर !defined(CONFIG_MMU) || CONFIG_PGTABLE_LEVELS == 3
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
#घोषणा pmd_val(x)	((&x)->pmd)
#घोषणा __pmd(x)	((pmd_t) अणु (x) पूर्ण )
#पूर्ण_अगर

प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;

#अगर defined(CONFIG_SUN3)
/*
 * Sun3 still uses the यंत्र-generic/pgभाग.स code and thus needs this
 * definition. It would be possible to unअगरy Sun3 and ColdFire pgalloc and have
 * all of m68k use the same type.
 */
प्रकार काष्ठा page *pgtable_t;
#अन्यथा
प्रकार pte_t *pgtable_t;
#पूर्ण_अगर

#घोषणा pte_val(x)	((x).pte)
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

बाह्य अचिन्हित दीर्घ _rambase;
बाह्य अचिन्हित दीर्घ _ramstart;
बाह्य अचिन्हित दीर्घ _ramend;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_MMU
#समावेश <यंत्र/page_mm.h>
#अन्यथा
#समावेश <यंत्र/page_no.h>
#पूर्ण_अगर

#अगर !defined(CONFIG_MMU) || defined(CONFIG_DISCONTIGMEM)
#घोषणा __phys_to_pfn(paddr)	((अचिन्हित दीर्घ)((paddr) >> PAGE_SHIFT))
#घोषणा __pfn_to_phys(pfn)	PFN_PHYS(pfn)
#पूर्ण_अगर

#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _M68K_PAGE_H */
