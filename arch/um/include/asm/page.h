<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2000 - 2003 Jeff Dike (jdike@addtoit.com)
 * Copyright 2003 PathScale, Inc.
 */

#अगर_अघोषित __UM_PAGE_H
#घोषणा __UM_PAGE_H

#समावेश <linux/स्थिर.h>

/* PAGE_SHIFT determines the page size */
#घोषणा PAGE_SHIFT	12
#घोषणा PAGE_SIZE	(_AC(1, UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))

#अगर_अघोषित __ASSEMBLY__

काष्ठा page;

#समावेश <linux/pfn.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/vm-flags.h>

/*
 * These are used to make use of C type-checking..
 */

#घोषणा clear_page(page)	स_रखो((व्योम *)(page), 0, PAGE_SIZE)
#घोषणा copy_page(to,from)	स_नकल((व्योम *)(to), (व्योम *)(from), PAGE_SIZE)

#घोषणा clear_user_page(page, vaddr, pg)	clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

#अगर defined(CONFIG_3_LEVEL_PGTABLES) && !defined(CONFIG_64BIT)

प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
#घोषणा pte_val(p) ((p).pte)

#घोषणा pte_get_bits(p, bits) ((p).pte & (bits))
#घोषणा pte_set_bits(p, bits) ((p).pte |= (bits))
#घोषणा pte_clear_bits(p, bits) ((p).pte &= ~(bits))
#घोषणा pte_copy(to, from) (अणु (to).pte = (from).pte; पूर्ण)
#घोषणा pte_is_zero(p) (!((p).pte & ~_PAGE_NEWPAGE))
#घोषणा pte_set_val(p, phys, prot) \
	(अणु (p).pte = (phys) | pgprot_val(prot); पूर्ण)

#घोषणा pmd_val(x)	((x).pmd)
#घोषणा __pmd(x) ((pmd_t) अणु (x) पूर्ण )

प्रकार अचिन्हित दीर्घ दीर्घ phys_t;

#अन्यथा

प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;

#अगर_घोषित CONFIG_3_LEVEL_PGTABLES
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
#घोषणा pmd_val(x)	((x).pmd)
#घोषणा __pmd(x) ((pmd_t) अणु (x) पूर्ण )
#पूर्ण_अगर

#घोषणा pte_val(x)	((x).pte)


#घोषणा pte_get_bits(p, bits) ((p).pte & (bits))
#घोषणा pte_set_bits(p, bits) ((p).pte |= (bits))
#घोषणा pte_clear_bits(p, bits) ((p).pte &= ~(bits))
#घोषणा pte_copy(to, from) ((to).pte = (from).pte)
#घोषणा pte_is_zero(p) (!((p).pte & ~_PAGE_NEWPAGE))
#घोषणा pte_set_val(p, phys, prot) (p).pte = (phys | pgprot_val(prot))

प्रकार अचिन्हित दीर्घ phys_t;

#पूर्ण_अगर

प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;

प्रकार काष्ठा page *pgtable_t;

#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x) ((pte_t) अणु (x) पूर्ण )
#घोषणा __pgd(x) ((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

बाह्य अचिन्हित दीर्घ uml_physmem;

#घोषणा PAGE_OFFSET (uml_physmem)
#घोषणा KERNELBASE PAGE_OFFSET

#घोषणा __va_space (8*1024*1024)

#समावेश <स्मृति.स>

/* Cast to अचिन्हित दीर्घ beक्रमe casting to व्योम * to aव्योम a warning from
 * mmap_kmem about cutting a दीर्घ दीर्घ करोwn to a व्योम *.  Not sure that
 * casting is the right thing, but 32-bit UML can't have 64-bit भव
 * addresses
 */
#घोषणा __pa(virt) to_phys((व्योम *) (अचिन्हित दीर्घ) (virt))
#घोषणा __va(phys) to_virt((अचिन्हित दीर्घ) (phys))

#घोषणा phys_to_pfn(p) ((p) >> PAGE_SHIFT)
#घोषणा pfn_to_phys(pfn) PFN_PHYS(pfn)

#घोषणा pfn_valid(pfn) ((pfn) < max_mapnr)
#घोषणा virt_addr_valid(v) pfn_valid(phys_to_pfn(__pa(v)))

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर	/* __ASSEMBLY__ */

#अगर_घोषित CONFIG_X86_32
#घोषणा __HAVE_ARCH_GATE_AREA 1
#पूर्ण_अगर

#पूर्ण_अगर	/* __UM_PAGE_H */
