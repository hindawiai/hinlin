<शैली गुरु>
/*
 * fixmap.h: compile-समय भव memory allocation
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998 Ingo Molnar
 * Copyright (C) 2013 Mark Salter <msalter@redhat.com>
 *
 * Adapted from arch/x86 version.
 *
 */

#अगर_अघोषित _ASM_ARM64_FIXMAP_H
#घोषणा _ASM_ARM64_FIXMAP_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/boot.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable-prot.h>

/*
 * Here we define all the compile-समय 'special' भव
 * addresses. The poपूर्णांक is to have a स्थिरant address at
 * compile समय, but to set the physical address only
 * in the boot process.
 *
 * Each क्रमागत increment in these 'compile-time allocated'
 * memory buffers is page-sized. Use set_fixmap(idx,phys)
 * to associate physical memory with a fixmap index.
 */
क्रमागत fixed_addresses अणु
	FIX_HOLE,

	/*
	 * Reserve a भव winकरोw क्रम the FDT that is 2 MB larger than the
	 * maximum supported size, and put it at the top of the fixmap region.
	 * The additional space ensures that any FDT that करोes not exceed
	 * MAX_FDT_SIZE can be mapped regardless of whether it crosses any
	 * 2 MB alignment boundaries.
	 *
	 * Keep this at the top so it reमुख्यs 2 MB aligned.
	 */
#घोषणा FIX_FDT_SIZE		(MAX_FDT_SIZE + SZ_2M)
	FIX_FDT_END,
	FIX_FDT = FIX_FDT_END + FIX_FDT_SIZE / PAGE_SIZE - 1,

	FIX_EARLYCON_MEM_BASE,
	FIX_TEXT_POKE0,

#अगर_घोषित CONFIG_ACPI_APEI_GHES
	/* Used क्रम GHES mapping from assorted contexts */
	FIX_APEI_GHES_IRQ,
	FIX_APEI_GHES_SEA,
#अगर_घोषित CONFIG_ARM_SDE_INTERFACE
	FIX_APEI_GHES_SDEI_NORMAL,
	FIX_APEI_GHES_SDEI_CRITICAL,
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_ACPI_APEI_GHES */

#अगर_घोषित CONFIG_UNMAP_KERNEL_AT_EL0
	FIX_ENTRY_TRAMP_DATA,
	FIX_ENTRY_TRAMP_TEXT,
#घोषणा TRAMP_VALIAS		(__fix_to_virt(FIX_ENTRY_TRAMP_TEXT))
#पूर्ण_अगर /* CONFIG_UNMAP_KERNEL_AT_EL0 */
	__end_of_permanent_fixed_addresses,

	/*
	 * Temporary boot-समय mappings, used by early_ioremap(),
	 * beक्रमe ioremap() is functional.
	 */
#घोषणा NR_FIX_BTMAPS		(SZ_256K / PAGE_SIZE)
#घोषणा FIX_BTMAPS_SLOTS	7
#घोषणा TOTAL_FIX_BTMAPS	(NR_FIX_BTMAPS * FIX_BTMAPS_SLOTS)

	FIX_BTMAP_END = __end_of_permanent_fixed_addresses,
	FIX_BTMAP_BEGIN = FIX_BTMAP_END + TOTAL_FIX_BTMAPS - 1,

	/*
	 * Used क्रम kernel page table creation, so unmapped memory may be used
	 * क्रम tables.
	 */
	FIX_PTE,
	FIX_PMD,
	FIX_PUD,
	FIX_PGD,

	__end_of_fixed_addresses
पूर्ण;

#घोषणा FIXADDR_SIZE	(__end_of_permanent_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START	(FIXADDR_TOP - FIXADDR_SIZE)

#घोषणा FIXMAP_PAGE_IO     __pgprot(PROT_DEVICE_nGnRE)

व्योम __init early_fixmap_init(व्योम);

#घोषणा __early_set_fixmap __set_fixmap

#घोषणा __late_set_fixmap __set_fixmap
#घोषणा __late_clear_fixmap(idx) __set_fixmap((idx), 0, FIXMAP_PAGE_CLEAR)

बाह्य व्योम __set_fixmap(क्रमागत fixed_addresses idx, phys_addr_t phys, pgprot_t prot);

#समावेश <यंत्र-generic/fixmap.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_ARM64_FIXMAP_H */
