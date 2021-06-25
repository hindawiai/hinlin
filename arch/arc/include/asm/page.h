<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */
#अगर_अघोषित __ASM_ARC_PAGE_H
#घोषणा __ASM_ARC_PAGE_H

#समावेश <uapi/यंत्र/page.h>

#अगर_घोषित CONFIG_ARC_HAS_PAE40

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS	40
#घोषणा PAGE_MASK_PHYS			(0xff00000000ull | PAGE_MASK)

#अन्यथा /* CONFIG_ARC_HAS_PAE40 */

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS	32
#घोषणा PAGE_MASK_PHYS			PAGE_MASK

#पूर्ण_अगर /* CONFIG_ARC_HAS_PAE40 */

#अगर_अघोषित __ASSEMBLY__

#घोषणा clear_page(paddr)		स_रखो((paddr), 0, PAGE_SIZE)
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)
#घोषणा copy_page(to, from)		स_नकल((to), (from), PAGE_SIZE)

काष्ठा vm_area_काष्ठा;
काष्ठा page;

#घोषणा __HAVE_ARCH_COPY_USER_HIGHPAGE

व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ u_vaddr, काष्ठा vm_area_काष्ठा *vma);
व्योम clear_user_page(व्योम *to, अचिन्हित दीर्घ u_vaddr, काष्ठा page *page);

#अघोषित STRICT_MM_TYPECHECKS

#अगर_घोषित STRICT_MM_TYPECHECKS
/*
 * These are used to make use of C type-checking..
 */
प्रकार काष्ठा अणु
#अगर_घोषित CONFIG_ARC_HAS_PAE40
	अचिन्हित दीर्घ दीर्घ pte;
#अन्यथा
	अचिन्हित दीर्घ pte;
#पूर्ण_अगर
पूर्ण pte_t;
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pgd;
पूर्ण pgd_t;
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pgprot;
पूर्ण pgprot_t;

#घोषणा pte_val(x)      ((x).pte)
#घोषणा pgd_val(x)      ((x).pgd)
#घोषणा pgprot_val(x)   ((x).pgprot)

#घोषणा __pte(x)        ((pte_t) अणु (x) पूर्ण)
#घोषणा __pgd(x)        ((pgd_t) अणु (x) पूर्ण)
#घोषणा __pgprot(x)     ((pgprot_t) अणु (x) पूर्ण)

#घोषणा pte_pgprot(x) __pgprot(pte_val(x))

#अन्यथा /* !STRICT_MM_TYPECHECKS */

#अगर_घोषित CONFIG_ARC_HAS_PAE40
प्रकार अचिन्हित दीर्घ दीर्घ pte_t;
#अन्यथा
प्रकार अचिन्हित दीर्घ pte_t;
#पूर्ण_अगर
प्रकार अचिन्हित दीर्घ pgd_t;
प्रकार अचिन्हित दीर्घ pgprot_t;

#घोषणा pte_val(x)	(x)
#घोषणा pgd_val(x)	(x)
#घोषणा pgprot_val(x)	(x)
#घोषणा __pte(x)	(x)
#घोषणा __pgd(x)	(x)
#घोषणा __pgprot(x)	(x)
#घोषणा pte_pgprot(x)	(x)

#पूर्ण_अगर

प्रकार pte_t * pgtable_t;

/*
 * Use virt_to_pfn with caution:
 * If used in pte or paddr related macros, it could cause truncation
 * in PAE40 builds
 * As a rule of thumb, only use it in helpers starting with virt_
 * You have been warned !
 */
#घोषणा virt_to_pfn(kaddr)	(__pa(kaddr) >> PAGE_SHIFT)

/*
 * When HIGHMEM is enabled we have holes in the memory map so we need
 * pfn_valid() that takes पूर्णांकo account the actual extents of the physical
 * memory
 */
#अगर_घोषित CONFIG_HIGHMEM

बाह्य अचिन्हित दीर्घ arch_pfn_offset;
#घोषणा ARCH_PFN_OFFSET		arch_pfn_offset

बाह्य पूर्णांक pfn_valid(अचिन्हित दीर्घ pfn);
#घोषणा pfn_valid		pfn_valid

#अन्यथा /* CONFIG_HIGHMEM */

#घोषणा ARCH_PFN_OFFSET		virt_to_pfn(CONFIG_LINUX_RAM_BASE)
#घोषणा pfn_valid(pfn)		(((pfn) - ARCH_PFN_OFFSET) < max_mapnr)

#पूर्ण_अगर /* CONFIG_HIGHMEM */

/*
 * __pa, __va, virt_to_page (ALERT: deprecated, करोn't use them)
 *
 * These macros have historically been misnamed
 * virt here means link-address/program-address as embedded in object code.
 * And क्रम ARC, link-addr = physical address
 */
#घोषणा __pa(vaddr)  ((अचिन्हित दीर्घ)(vaddr))
#घोषणा __va(paddr)  ((व्योम *)((अचिन्हित दीर्घ)(paddr)))

#घोषणा virt_to_page(kaddr)	pfn_to_page(virt_to_pfn(kaddr))
#घोषणा virt_addr_valid(kaddr)  pfn_valid(virt_to_pfn(kaddr))

/* Default Permissions क्रम stack/heaps pages (Non Executable) */
#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_NON_EXEC

#घोषणा WANT_PAGE_VIRTUAL   1

#समावेश <यंत्र-generic/memory_model.h>   /* page_to_pfn, pfn_to_page */
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर
