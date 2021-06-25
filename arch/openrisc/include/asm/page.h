<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_PAGE_H
#घोषणा __ASM_OPENRISC_PAGE_H


/* PAGE_SHIFT determines the page size */

#घोषणा PAGE_SHIFT      13
#अगर_घोषित __ASSEMBLY__
#घोषणा PAGE_SIZE       (1 << PAGE_SHIFT)
#अन्यथा
#घोषणा PAGE_SIZE       (1UL << PAGE_SHIFT)
#पूर्ण_अगर
#घोषणा PAGE_MASK       (~(PAGE_SIZE-1))

#घोषणा PAGE_OFFSET	0xc0000000
#घोषणा KERNELBASE	PAGE_OFFSET

/* This is not necessarily the right place क्रम this, but it's needed by
 * drivers/of/fdt.c
 */
#समावेश <यंत्र/setup.h>

#अगर_अघोषित __ASSEMBLY__

#घोषणा clear_page(page)	स_रखो((page), 0, PAGE_SIZE)
#घोषणा copy_page(to, from)	स_नकल((to), (from), PAGE_SIZE)

#घोषणा clear_user_page(page, vaddr, pg)        clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)     copy_page(to, from)

/*
 * These are used to make use of C type-checking..
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pte;
पूर्ण pte_t;
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pgd;
पूर्ण pgd_t;
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pgprot;
पूर्ण pgprot_t;
प्रकार काष्ठा page *pgtable_t;

#घोषणा pte_val(x)	((x).pte)
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण)
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण)
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण)

#पूर्ण_अगर /* !__ASSEMBLY__ */


#अगर_अघोषित __ASSEMBLY__

#घोषणा __va(x) ((व्योम *)((अचिन्हित दीर्घ)(x) + PAGE_OFFSET))
#घोषणा __pa(x) ((अचिन्हित दीर्घ) (x) - PAGE_OFFSET)

#घोषणा virt_to_pfn(kaddr)      (__pa(kaddr) >> PAGE_SHIFT)
#घोषणा pfn_to_virt(pfn)        __va((pfn) << PAGE_SHIFT)

#घोषणा virt_to_page(addr) \
	(mem_map + (((अचिन्हित दीर्घ)(addr)-PAGE_OFFSET) >> PAGE_SHIFT))

#घोषणा page_to_phys(page)      ((dma_addr_t)page_to_pfn(page) << PAGE_SHIFT)

#घोषणा pfn_valid(pfn)          ((pfn) < max_mapnr)

#घोषणा virt_addr_valid(kaddr)	(pfn_valid(virt_to_pfn(kaddr)))

#पूर्ण_अगर /* __ASSEMBLY__ */

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* __ASM_OPENRISC_PAGE_H */
