<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * VM ops
 *
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 * Changes क्रम MMU support:
 *    Copyright (C) 2007 Xilinx, Inc.  All rights reserved.
 */

#अगर_अघोषित _ASM_MICROBLAZE_PAGE_H
#घोषणा _ASM_MICROBLAZE_PAGE_H

#समावेश <linux/pfn.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/यंत्र-compat.h>
#समावेश <linux/स्थिर.h>

#अगर_घोषित __KERNEL__

/* PAGE_SHIFT determines the page size */
#घोषणा PAGE_SHIFT		12
#घोषणा PAGE_SIZE	(ASM_CONST(1) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))

#घोषणा LOAD_OFFSET	ASM_CONST((CONFIG_KERNEL_START-CONFIG_KERNEL_BASE_ADDR))

#घोषणा PTE_SHIFT	(PAGE_SHIFT - 2)	/* 1024 ptes per page */

#अगर_अघोषित __ASSEMBLY__

/* MS be sure that SLAB allocates aligned objects */
#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES

#घोषणा ARCH_SLAB_MINALIGN	L1_CACHE_BYTES

#घोषणा PAGE_UP(addr)	(((addr)+((PAGE_SIZE)-1))&(~((PAGE_SIZE)-1)))
#घोषणा PAGE_DOWN(addr)	((addr)&(~((PAGE_SIZE)-1)))

/*
 * PAGE_OFFSET -- the first address of the first page of memory. With MMU
 * it is set to the kernel start address (aligned on a page boundary).
 *
 * CONFIG_KERNEL_START is defined in arch/microblaze/config.in and used
 * in arch/microblaze/Makefile.
 */
#घोषणा PAGE_OFFSET	CONFIG_KERNEL_START

/*
 * The basic type of a PTE - 32 bit physical addressing.
 */
प्रकार अचिन्हित दीर्घ pte_basic_t;
#घोषणा PTE_FMT		"%.8lx"

# define copy_page(to, from)			स_नकल((to), (from), PAGE_SIZE)
# define clear_page(pgaddr)			स_रखो((pgaddr), 0, PAGE_SIZE)

# define clear_user_page(pgaddr, vaddr, page)	स_रखो((pgaddr), 0, PAGE_SIZE)
# define copy_user_page(vto, vfrom, vaddr, topg) \
			स_नकल((vto), (vfrom), PAGE_SIZE)

/*
 * These are used to make use of C type-checking..
 */
प्रकार काष्ठा page *pgtable_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ	pte; पूर्ण		pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ	pgprot; पूर्ण	pgprot_t;
/* FIXME this can depend on linux kernel version */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;

# define pte_val(x)	((x).pte)
# define pgprot_val(x)	((x).pgprot)

#   define pgd_val(x)      ((x).pgd)

# define __pte(x)	((pte_t) अणु (x) पूर्ण)
# define __pgd(x)	((pgd_t) अणु (x) पूर्ण)
# define __pgprot(x)	((pgprot_t) अणु (x) पूर्ण)

/**
 * Conversions क्रम भव address, physical address, pfn, and काष्ठा
 * page are defined in the following files.
 *
 * virt -+
 *	 | यंत्र-microblaze/page.h
 * phys -+
 *	 | linux/pfn.h
 *  pfn -+
 *	 | यंत्र-generic/memory_model.h
 * page -+
 *
 */

बाह्य अचिन्हित दीर्घ max_low_pfn;
बाह्य अचिन्हित दीर्घ min_low_pfn;
बाह्य अचिन्हित दीर्घ max_pfn;

बाह्य अचिन्हित दीर्घ memory_start;
बाह्य अचिन्हित दीर्घ memory_size;
बाह्य अचिन्हित दीर्घ lowmem_size;

बाह्य अचिन्हित दीर्घ kernel_tlb;

बाह्य पूर्णांक page_is_ram(अचिन्हित दीर्घ pfn);

# define phys_to_pfn(phys)	(PFN_DOWN(phys))
# define pfn_to_phys(pfn)	(PFN_PHYS(pfn))

# define virt_to_pfn(vaddr)	(phys_to_pfn((__pa(vaddr))))
# define pfn_to_virt(pfn)	__va(pfn_to_phys((pfn)))

#  define virt_to_page(kaddr)	(pfn_to_page(__pa(kaddr) >> PAGE_SHIFT))
#  define page_to_virt(page)   __va(page_to_pfn(page) << PAGE_SHIFT)
#  define page_to_phys(page)     (page_to_pfn(page) << PAGE_SHIFT)

#  define ARCH_PFN_OFFSET	(memory_start >> PAGE_SHIFT)
#  define pfn_valid(pfn)	((pfn) < (max_mapnr + ARCH_PFN_OFFSET))

# endअगर /* __ASSEMBLY__ */

#घोषणा	virt_addr_valid(vaddr)	(pfn_valid(virt_to_pfn(vaddr)))

# define __pa(x)	__virt_to_phys((अचिन्हित दीर्घ)(x))
# define __va(x)	((व्योम *)__phys_to_virt((अचिन्हित दीर्घ)(x)))

/* Convert between भव and physical address क्रम MMU. */
/* Handle MicroBlaze processor with भव memory. */
#घोषणा __virt_to_phys(addr) \
	((addr) + CONFIG_KERNEL_BASE_ADDR - CONFIG_KERNEL_START)
#घोषणा __phys_to_virt(addr) \
	((addr) + CONFIG_KERNEL_START - CONFIG_KERNEL_BASE_ADDR)
#घोषणा tophys(rd, rs) \
	addik rd, rs, (CONFIG_KERNEL_BASE_ADDR - CONFIG_KERNEL_START)
#घोषणा tovirt(rd, rs) \
	addik rd, rs, (CONFIG_KERNEL_START - CONFIG_KERNEL_BASE_ADDR)

#घोषणा TOPHYS(addr)  __virt_to_phys(addr)

#पूर्ण_अगर /* __KERNEL__ */

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _ASM_MICROBLAZE_PAGE_H */
