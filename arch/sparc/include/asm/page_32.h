<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * page.h:  Various defines and such क्रम MMU operations on the Sparc क्रम
 *          the Linux kernel.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _SPARC_PAGE_H
#घोषणा _SPARC_PAGE_H

#समावेश <linux/स्थिर.h>

#घोषणा PAGE_SHIFT   12
#घोषणा PAGE_SIZE    (_AC(1, UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK    (~(PAGE_SIZE-1))

#अगर_अघोषित __ASSEMBLY__

#घोषणा clear_page(page)	 स_रखो((व्योम *)(page), 0, PAGE_SIZE)
#घोषणा copy_page(to,from) 	स_नकल((व्योम *)(to), (व्योम *)(from), PAGE_SIZE)
#घोषणा clear_user_page(addr, vaddr, page)	\
	करो अणु 	clear_page(addr);		\
		sparc_flush_page_to_ram(page);	\
	पूर्ण जबतक (0)
#घोषणा copy_user_page(to, from, vaddr, page)	\
	करो अणु	copy_page(to, from);		\
		sparc_flush_page_to_ram(page);	\
	पूर्ण जबतक (0)

/* The following काष्ठाure is used to hold the physical
 * memory configuration of the machine.  This is filled in
 * prom_meminit() and is later used by mem_init() to set up
 * mem_map[].  We अटलally allocate SPARC_PHYS_BANKS+1 of
 * these काष्ठाs, this is arbitrary.  The entry after the
 * last valid one has num_bytes==0.
 */
काष्ठा sparc_phys_banks अणु
  अचिन्हित दीर्घ base_addr;
  अचिन्हित दीर्घ num_bytes;
पूर्ण;

#घोषणा SPARC_PHYS_BANKS 32

बाह्य काष्ठा sparc_phys_banks sp_banks[SPARC_PHYS_BANKS+1];

/* passing काष्ठाs on the Sparc slow us करोwn tremenकरोusly... */

/* #घोषणा STRICT_MM_TYPECHECKS */

#अगर_घोषित STRICT_MM_TYPECHECKS
/*
 * These are used to make use of C type-checking..
 */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ iopte; पूर्ण iopte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ ctxd; पूर्ण ctxd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ iopgprot; पूर्ण iopgprot_t;

#घोषणा pte_val(x)	((x).pte)
#घोषणा iopte_val(x)	((x).iopte)
#घोषणा pmd_val(x)      ((x).pmd)
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा ctxd_val(x)	((x).ctxd)
#घोषणा pgprot_val(x)	((x).pgprot)
#घोषणा iopgprot_val(x)	((x).iopgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#घोषणा __pmd(x)	((pmd_t) अणु अणु (x) पूर्ण, पूर्ण)
#घोषणा __iopte(x)	((iopte_t) अणु (x) पूर्ण )
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )
#घोषणा __ctxd(x)	((ctxd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )
#घोषणा __iopgprot(x)	((iopgprot_t) अणु (x) पूर्ण )

#अन्यथा
/*
 * .. जबतक these make it easier on the compiler
 */
प्रकार अचिन्हित दीर्घ pte_t;
प्रकार अचिन्हित दीर्घ iopte_t;
प्रकार अचिन्हित दीर्घ pmd_t;
प्रकार अचिन्हित दीर्घ pgd_t;
प्रकार अचिन्हित दीर्घ ctxd_t;
प्रकार अचिन्हित दीर्घ pgprot_t;
प्रकार अचिन्हित दीर्घ iopgprot_t;

#घोषणा pte_val(x)	(x)
#घोषणा iopte_val(x)	(x)
#घोषणा pmd_val(x)      (x)
#घोषणा pgd_val(x)	(x)
#घोषणा ctxd_val(x)	(x)
#घोषणा pgprot_val(x)	(x)
#घोषणा iopgprot_val(x)	(x)

#घोषणा __pte(x)	(x)
#घोषणा __pmd(x)	(x)
#घोषणा __iopte(x)	(x)
#घोषणा __pgd(x)	(x)
#घोषणा __ctxd(x)	(x)
#घोषणा __pgprot(x)	(x)
#घोषणा __iopgprot(x)	(x)

#पूर्ण_अगर

प्रकार pte_t *pgtable_t;

#घोषणा TASK_UNMAPPED_BASE	0x50000000

#अन्यथा /* !(__ASSEMBLY__) */

#घोषणा __pgprot(x)	(x)

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#घोषणा PAGE_OFFSET	0xf0000000
#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ phys_base;
बाह्य अचिन्हित दीर्घ pfn_base;
#पूर्ण_अगर
#घोषणा __pa(x)			((अचिन्हित दीर्घ)(x) - PAGE_OFFSET + phys_base)
#घोषणा __va(x)			((व्योम *)((अचिन्हित दीर्घ) (x) - phys_base + PAGE_OFFSET))

#घोषणा virt_to_phys		__pa
#घोषणा phys_to_virt		__va

#घोषणा ARCH_PFN_OFFSET		(pfn_base)
#घोषणा virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)

#घोषणा pfn_valid(pfn)		(((pfn) >= (pfn_base)) && (((pfn)-(pfn_base)) < max_mapnr))
#घोषणा virt_addr_valid(kaddr)	((((अचिन्हित दीर्घ)(kaddr)-PAGE_OFFSET)>>PAGE_SHIFT) < max_mapnr)

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _SPARC_PAGE_H */
