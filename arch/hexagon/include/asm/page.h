<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Page management definitions क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_PAGE_H
#घोषणा _ASM_PAGE_H

#समावेश <linux/स्थिर.h>

/*  This is probably not the most graceful way to handle this.  */

#अगर_घोषित CONFIG_PAGE_SIZE_4KB
#घोषणा PAGE_SHIFT 12
#घोषणा HEXAGON_L1_PTE_SIZE __HVM_PDE_S_4KB
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_SIZE_16KB
#घोषणा PAGE_SHIFT 14
#घोषणा HEXAGON_L1_PTE_SIZE __HVM_PDE_S_16KB
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_SIZE_64KB
#घोषणा PAGE_SHIFT 16
#घोषणा HEXAGON_L1_PTE_SIZE __HVM_PDE_S_64KB
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_SIZE_256KB
#घोषणा PAGE_SHIFT 18
#घोषणा HEXAGON_L1_PTE_SIZE __HVM_PDE_S_256KB
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_SIZE_1MB
#घोषणा PAGE_SHIFT 20
#घोषणा HEXAGON_L1_PTE_SIZE __HVM_PDE_S_1MB
#पूर्ण_अगर

/*
 *  These should be defined in hugetlb.h, but apparently not.
 *  "Huge" क्रम us should be 4MB or 16MB, which are both represented
 *  in L1 PTE's.  Right now, it's set up क्रम 4MB.
 */
#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा HPAGE_SHIFT 22
#घोषणा HPAGE_SIZE (1UL << HPAGE_SHIFT)
#घोषणा HPAGE_MASK (~(HPAGE_SIZE-1))
#घोषणा HUGETLB_PAGE_ORDER (HPAGE_SHIFT-PAGE_SHIFT)
#घोषणा HVM_HUGEPAGE_SIZE 0x5
#पूर्ण_अगर

#घोषणा PAGE_SIZE  (1UL << PAGE_SHIFT)
#घोषणा PAGE_MASK  (~((1 << PAGE_SHIFT) - 1))

#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASSEMBLY__

/*
 * This is क्रम PFN_DOWN, which mm.h needs.  Seems the right place to pull it in.
 */
#समावेश <linux/pfn.h>

/*
 * We implement a two-level architecture-specअगरic page table काष्ठाure.
 * Null पूर्णांकermediate page table level (pmd, pud) definitions will come from
 * यंत्र-generic/pagetable-nopmd.h and यंत्र-generic/pagetable-nopud.h
 */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
प्रकार काष्ठा page *pgtable_t;

#घोषणा pte_val(x)     ((x).pte)
#घोषणा pgd_val(x)     ((x).pgd)
#घोषणा pgprot_val(x)  ((x).pgprot)
#घोषणा __pte(x)       ((pte_t) अणु (x) पूर्ण)
#घोषणा __pgd(x)       ((pgd_t) अणु (x) पूर्ण)
#घोषणा __pgprot(x)    ((pgprot_t) अणु (x) पूर्ण)

/*
 * We need a __pa and a __va routine क्रम kernel space.
 * MIPS says they're only used during mem_init.
 * also, check अगर we need a PHYS_OFFSET.
 */
#घोषणा __pa(x) ((अचिन्हित दीर्घ)(x) - PAGE_OFFSET + PHYS_OFFSET)
#घोषणा __va(x) ((व्योम *)((अचिन्हित दीर्घ)(x) - PHYS_OFFSET + PAGE_OFFSET))

/* The "page frame" descriptor is defined in linux/mm.h */
काष्ठा page;

/* Returns page frame descriptor क्रम भव address. */
#घोषणा virt_to_page(kaddr) pfn_to_page(PFN_DOWN(__pa(kaddr)))

/* Default vm area behavior is non-executable.  */
#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_NON_EXEC

#घोषणा pfn_valid(pfn) ((pfn) < max_mapnr)
#घोषणा virt_addr_valid(kaddr) pfn_valid(__pa(kaddr) >> PAGE_SHIFT)

/*  Need to not use a define क्रम linesize; may move this to another file.  */
अटल अंतरभूत व्योम clear_page(व्योम *page)
अणु
	/*  This can only be करोne on pages with L1 WB cache */
	यंत्र अस्थिर(
		"	loop0(1f,%1);\n"
		"1:	{ dczeroa(%0);\n"
		"	  %0 = add(%0,#32); }:endloop0\n"
		: "+r" (page)
		: "r" (PAGE_SIZE/32)
		: "lc0", "sa0", "memory"
	);
पूर्ण

#घोषणा copy_page(to, from)	स_नकल((to), (from), PAGE_SIZE)

/*
 * Under assumption that kernel always "sees" user map...
 */
#घोषणा clear_user_page(page, vaddr, pg)	clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

/*
 * page_to_phys - convert page to physical address
 * @page - poपूर्णांकer to page entry in mem_map
 */
#घोषणा page_to_phys(page)      (page_to_pfn(page) << PAGE_SHIFT)

#घोषणा virt_to_pfn(kaddr)      (__pa(kaddr) >> PAGE_SHIFT)
#घोषणा pfn_to_virt(pfn)        __va((pfn) << PAGE_SHIFT)

#घोषणा page_to_virt(page)	__va(page_to_phys(page))

/*
 * For port to Hexagon Virtual Machine, MAYBE we check क्रम attempts
 * to reference reserved HVM space, but in any हाल, the VM will be
 * रक्षित.
 */
#घोषणा kern_addr_valid(addr)   (1)

#समावेश <यंत्र/mem-layout.h>
#समावेश <यंत्र-generic/memory_model.h>
/* XXX Toकरो: implement assembly-optimized version of getorder. */
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* अगरdef __ASSEMBLY__ */
#पूर्ण_अगर /* अगरdef __KERNEL__ */

#पूर्ण_अगर
