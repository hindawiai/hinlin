<शैली गुरु>
/*
 * fixmap.h: compile-समय भव memory allocation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998 Ingo Molnar
 *
 * Copyright 2008 Freescale Semiconductor Inc.
 *   Port to घातerpc added by Kumar Gala
 */

#अगर_अघोषित _ASM_FIXMAP_H
#घोषणा _ASM_FIXMAP_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/sizes.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>
#अगर_घोषित CONFIG_HIGHMEM
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/kmap_size.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
#घोषणा FIXADDR_TOP	(IOREMAP_END + FIXADDR_SIZE)
#अन्यथा
#घोषणा FIXADDR_SIZE	0
#अगर_घोषित CONFIG_KASAN
#समावेश <यंत्र/kasan.h>
#घोषणा FIXADDR_TOP	(KASAN_SHADOW_START - PAGE_SIZE)
#अन्यथा
#घोषणा FIXADDR_TOP	((अचिन्हित दीर्घ)(-PAGE_SIZE))
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Here we define all the compile-समय 'special' भव
 * addresses. The poपूर्णांक is to have a स्थिरant address at
 * compile समय, but to set the physical address only
 * in the boot process. We allocate these special addresses
 * from the end of भव memory (0xfffff000) backwards.
 * Also this lets us करो fail-safe vदो_स्मृति(), we
 * can guarantee that these special addresses and
 * vदो_स्मृति()-ed addresses never overlap.
 *
 * these 'compile-time allocated' memory buffers are
 * fixed-size 4k pages. (or larger अगर used with an increment
 * highger than 1) use fixmap_set(idx,phys) to associate
 * physical memory with fixmap indices.
 *
 * TLB entries of such buffers will not be flushed across
 * task चयनes.
 */
क्रमागत fixed_addresses अणु
	FIX_HOLE,
#अगर_घोषित CONFIG_PPC32
	/* reserve the top 128K क्रम early debugging purposes */
	FIX_EARLY_DEBUG_TOP = FIX_HOLE,
	FIX_EARLY_DEBUG_BASE = FIX_EARLY_DEBUG_TOP+(ALIGN(SZ_128K, PAGE_SIZE)/PAGE_SIZE)-1,
#अगर_घोषित CONFIG_HIGHMEM
	FIX_KMAP_BEGIN,	/* reserved pte's क्रम temporary kernel mappings */
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * NR_CPUS) - 1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_8xx
	/* For IMMR we need an aligned 512K area */
#घोषणा FIX_IMMR_SIZE	(512 * 1024 / PAGE_SIZE)
	FIX_IMMR_START,
	FIX_IMMR_BASE = __ALIGN_MASK(FIX_IMMR_START, FIX_IMMR_SIZE - 1) - 1 +
		       FIX_IMMR_SIZE,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_83xx
	/* For IMMR we need an aligned 2M area */
#घोषणा FIX_IMMR_SIZE	(SZ_2M / PAGE_SIZE)
	FIX_IMMR_START,
	FIX_IMMR_BASE = __ALIGN_MASK(FIX_IMMR_START, FIX_IMMR_SIZE - 1) - 1 +
		       FIX_IMMR_SIZE,
#पूर्ण_अगर
	/* FIX_PCIE_MCFG, */
#पूर्ण_अगर /* CONFIG_PPC32 */
	__end_of_permanent_fixed_addresses,

#घोषणा NR_FIX_BTMAPS		(SZ_256K / PAGE_SIZE)
#घोषणा FIX_BTMAPS_SLOTS	16
#घोषणा TOTAL_FIX_BTMAPS	(NR_FIX_BTMAPS * FIX_BTMAPS_SLOTS)

	FIX_BTMAP_END = __end_of_permanent_fixed_addresses,
	FIX_BTMAP_BEGIN = FIX_BTMAP_END + TOTAL_FIX_BTMAPS - 1,
	__end_of_fixed_addresses
पूर्ण;

#घोषणा __FIXADDR_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START		(FIXADDR_TOP - __FIXADDR_SIZE)

#घोषणा FIXMAP_ALIGNED_SIZE	(ALIGN(FIXADDR_TOP, PGसूची_SIZE) - \
				 ALIGN_DOWN(FIXADDR_START, PGसूची_SIZE))
#घोषणा FIXMAP_PTE_SIZE	(FIXMAP_ALIGNED_SIZE / PGसूची_SIZE * PTE_TABLE_SIZE)

#घोषणा FIXMAP_PAGE_NOCACHE PAGE_KERNEL_NCG
#घोषणा FIXMAP_PAGE_IO	PAGE_KERNEL_NCG

#समावेश <यंत्र-generic/fixmap.h>

अटल अंतरभूत व्योम __set_fixmap(क्रमागत fixed_addresses idx,
				phys_addr_t phys, pgprot_t flags)
अणु
	BUILD_BUG_ON(IS_ENABLED(CONFIG_PPC64) && __FIXADDR_SIZE > FIXADDR_SIZE);

	अगर (__builtin_स्थिरant_p(idx))
		BUILD_BUG_ON(idx >= __end_of_fixed_addresses);
	अन्यथा अगर (WARN_ON(idx >= __end_of_fixed_addresses))
		वापस;

	map_kernel_page(__fix_to_virt(idx), phys, flags);
पूर्ण

#घोषणा __early_set_fixmap	__set_fixmap

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर
