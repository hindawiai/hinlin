<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Kernel page table mapping
 *
 * Copyright (C) 2015 ARM Ltd.
 */

#अगर_अघोषित __ASM_KERNEL_PGTABLE_H
#घोषणा __ASM_KERNEL_PGTABLE_H

#समावेश <यंत्र/pgtable-hwdef.h>
#समावेश <यंत्र/sparseस्मृति.स>

/*
 * The linear mapping and the start of memory are both 2M aligned (per
 * the arm64 booting.txt requirements). Hence we can use section mapping
 * with 4K (section size = 2M) but not with 16K (section size = 32M) or
 * 64K (section size = 512M).
 */
#अगर_घोषित CONFIG_ARM64_4K_PAGES
#घोषणा ARM64_SWAPPER_USES_SECTION_MAPS 1
#अन्यथा
#घोषणा ARM64_SWAPPER_USES_SECTION_MAPS 0
#पूर्ण_अगर

/*
 * The idmap and swapper page tables need some space reserved in the kernel
 * image. Both require pgd, pud (4 levels only) and pmd tables to (section)
 * map the kernel. With the 64K page configuration, swapper and idmap need to
 * map to pte level. The swapper also maps the FDT (see __create_page_tables
 * क्रम more inक्रमmation). Note that the number of ID map translation levels
 * could be increased on the fly अगर प्रणाली RAM is out of reach क्रम the शेष
 * VA range, so pages required to map highest possible PA are reserved in all
 * हालs.
 */
#अगर ARM64_SWAPPER_USES_SECTION_MAPS
#घोषणा SWAPPER_PGTABLE_LEVELS	(CONFIG_PGTABLE_LEVELS - 1)
#घोषणा IDMAP_PGTABLE_LEVELS	(ARM64_HW_PGTABLE_LEVELS(PHYS_MASK_SHIFT) - 1)
#अन्यथा
#घोषणा SWAPPER_PGTABLE_LEVELS	(CONFIG_PGTABLE_LEVELS)
#घोषणा IDMAP_PGTABLE_LEVELS	(ARM64_HW_PGTABLE_LEVELS(PHYS_MASK_SHIFT))
#पूर्ण_अगर


/*
 * If KASLR is enabled, then an offset K is added to the kernel address
 * space. The bottom 21 bits of this offset are zero to guarantee 2MB
 * alignment क्रम PA and VA.
 *
 * For each pagetable level of the swapper, we know that the shअगरt will
 * be larger than 21 (क्रम the 4KB granule हाल we use section maps thus
 * the smallest shअगरt is actually 30) thus there is the possibility that
 * KASLR can increase the number of pagetable entries by 1, so we make
 * room क्रम this extra entry.
 *
 * Note KASLR cannot increase the number of required entries क्रम a level
 * by more than one because it increments both the भव start and end
 * addresses equally (the extra entry comes from the हाल where the end
 * address is just pushed over a boundary and the start address isn't).
 */

#अगर_घोषित CONFIG_RANDOMIZE_BASE
#घोषणा EARLY_KASLR	(1)
#अन्यथा
#घोषणा EARLY_KASLR	(0)
#पूर्ण_अगर

#घोषणा EARLY_ENTRIES(vstart, vend, shअगरt) (((vend) >> (shअगरt)) \
					- ((vstart) >> (shअगरt)) + 1 + EARLY_KASLR)

#घोषणा EARLY_PGDS(vstart, vend) (EARLY_ENTRIES(vstart, vend, PGसूची_SHIFT))

#अगर SWAPPER_PGTABLE_LEVELS > 3
#घोषणा EARLY_PUDS(vstart, vend) (EARLY_ENTRIES(vstart, vend, PUD_SHIFT))
#अन्यथा
#घोषणा EARLY_PUDS(vstart, vend) (0)
#पूर्ण_अगर

#अगर SWAPPER_PGTABLE_LEVELS > 2
#घोषणा EARLY_PMDS(vstart, vend) (EARLY_ENTRIES(vstart, vend, SWAPPER_TABLE_SHIFT))
#अन्यथा
#घोषणा EARLY_PMDS(vstart, vend) (0)
#पूर्ण_अगर

#घोषणा EARLY_PAGES(vstart, vend) ( 1 			/* PGसूची page */				\
			+ EARLY_PGDS((vstart), (vend)) 	/* each PGसूची needs a next level page table */	\
			+ EARLY_PUDS((vstart), (vend))	/* each PUD needs a next level page table */	\
			+ EARLY_PMDS((vstart), (vend)))	/* each PMD needs a next level page table */
#घोषणा INIT_सूची_SIZE (PAGE_SIZE * EARLY_PAGES(KIMAGE_VADDR, _end))
#घोषणा IDMAP_सूची_SIZE		(IDMAP_PGTABLE_LEVELS * PAGE_SIZE)

/* Initial memory map size */
#अगर ARM64_SWAPPER_USES_SECTION_MAPS
#घोषणा SWAPPER_BLOCK_SHIFT	SECTION_SHIFT
#घोषणा SWAPPER_BLOCK_SIZE	SECTION_SIZE
#घोषणा SWAPPER_TABLE_SHIFT	PUD_SHIFT
#अन्यथा
#घोषणा SWAPPER_BLOCK_SHIFT	PAGE_SHIFT
#घोषणा SWAPPER_BLOCK_SIZE	PAGE_SIZE
#घोषणा SWAPPER_TABLE_SHIFT	PMD_SHIFT
#पूर्ण_अगर

/* The size of the initial kernel direct mapping */
#घोषणा SWAPPER_INIT_MAP_SIZE	(_AC(1, UL) << SWAPPER_TABLE_SHIFT)

/*
 * Initial memory map attributes.
 */
#घोषणा SWAPPER_PTE_FLAGS	(PTE_TYPE_PAGE | PTE_AF | PTE_SHARED)
#घोषणा SWAPPER_PMD_FLAGS	(PMD_TYPE_SECT | PMD_SECT_AF | PMD_SECT_S)

#अगर ARM64_SWAPPER_USES_SECTION_MAPS
#घोषणा SWAPPER_MM_MMUFLAGS	(PMD_ATTRINDX(MT_NORMAL) | SWAPPER_PMD_FLAGS)
#अन्यथा
#घोषणा SWAPPER_MM_MMUFLAGS	(PTE_ATTRINDX(MT_NORMAL) | SWAPPER_PTE_FLAGS)
#पूर्ण_अगर

/*
 * To make optimal use of block mappings when laying out the linear
 * mapping, round करोwn the base of physical memory to a size that can
 * be mapped efficiently, i.e., either PUD_SIZE (4k granule) or PMD_SIZE
 * (64k granule), or a multiple that can be mapped using contiguous bits
 * in the page tables: 32 * PMD_SIZE (16k granule)
 */
#अगर defined(CONFIG_ARM64_4K_PAGES)
#घोषणा ARM64_MEMSTART_SHIFT		PUD_SHIFT
#या_अगर defined(CONFIG_ARM64_16K_PAGES)
#घोषणा ARM64_MEMSTART_SHIFT		(PMD_SHIFT + 5)
#अन्यथा
#घोषणा ARM64_MEMSTART_SHIFT		PMD_SHIFT
#पूर्ण_अगर

/*
 * sparsemem vmemmap imposes an additional requirement on the alignment of
 * memstart_addr, due to the fact that the base of the vmemmap region
 * has a direct correspondence, and needs to appear sufficiently aligned
 * in the भव address space.
 */
#अगर ARM64_MEMSTART_SHIFT < SECTION_SIZE_BITS
#घोषणा ARM64_MEMSTART_ALIGN	(1UL << SECTION_SIZE_BITS)
#अन्यथा
#घोषणा ARM64_MEMSTART_ALIGN	(1UL << ARM64_MEMSTART_SHIFT)
#पूर्ण_अगर

#पूर्ण_अगर	/* __ASM_KERNEL_PGTABLE_H */
