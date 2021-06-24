<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 Western Digital Corporation or its affiliates.
 */

#अगर_अघोषित _ASM_RISCV_FIXMAP_H
#घोषणा _ASM_RISCV_FIXMAP_H

#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_MMU
/*
 * Here we define all the compile-समय 'special' भव addresses.
 * The poपूर्णांक is to have a स्थिरant address at compile समय, but to
 * set the physical address only in the boot process.
 *
 * These 'compile-time allocated' memory buffers are page-sized. Use
 * set_fixmap(idx,phys) to associate physical memory with fixmap indices.
 */
क्रमागत fixed_addresses अणु
	FIX_HOLE,
	FIX_PTE,
	FIX_PMD,
	FIX_TEXT_POKE1,
	FIX_TEXT_POKE0,
	FIX_EARLYCON_MEM_BASE,

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

	__end_of_fixed_addresses
पूर्ण;

#घोषणा FIXMAP_PAGE_IO		PAGE_KERNEL

#घोषणा __early_set_fixmap	__set_fixmap

#घोषणा __late_set_fixmap	__set_fixmap
#घोषणा __late_clear_fixmap(idx) __set_fixmap((idx), 0, FIXMAP_PAGE_CLEAR)

बाह्य व्योम __set_fixmap(क्रमागत fixed_addresses idx,
			 phys_addr_t phys, pgprot_t prot);

#समावेश <यंत्र-generic/fixmap.h>

#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर /* _ASM_RISCV_FIXMAP_H */
