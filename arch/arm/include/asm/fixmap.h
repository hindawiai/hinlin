<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_FIXMAP_H
#घोषणा _ASM_FIXMAP_H

#घोषणा FIXADDR_START		0xffc80000UL
#घोषणा FIXADDR_END		0xfff00000UL
#घोषणा FIXADDR_TOP		(FIXADDR_END - PAGE_SIZE)

#समावेश <linux/pgtable.h>
#समावेश <यंत्र/kmap_size.h>

क्रमागत fixed_addresses अणु
	FIX_EARLYCON_MEM_BASE,
	__end_of_permanent_fixed_addresses,

	FIX_KMAP_BEGIN = __end_of_permanent_fixed_addresses,
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * NR_CPUS) - 1,

	/* Support writing RO kernel text via kprobes, jump labels, etc. */
	FIX_TEXT_POKE0,
	FIX_TEXT_POKE1,

	__end_of_fixmap_region,

	/*
	 * Share the kmap() region with early_ioremap(): this is guaranteed
	 * not to clash since early_ioremap() is only available beक्रमe
	 * paging_init(), and kmap() only after.
	 */
#घोषणा NR_FIX_BTMAPS		32
#घोषणा FIX_BTMAPS_SLOTS	7
#घोषणा TOTAL_FIX_BTMAPS	(NR_FIX_BTMAPS * FIX_BTMAPS_SLOTS)

	FIX_BTMAP_END = __end_of_permanent_fixed_addresses,
	FIX_BTMAP_BEGIN = FIX_BTMAP_END + TOTAL_FIX_BTMAPS - 1,
	__end_of_early_ioremap_region
पूर्ण;

अटल स्थिर क्रमागत fixed_addresses __end_of_fixed_addresses =
	__end_of_fixmap_region > __end_of_early_ioremap_region ?
	__end_of_fixmap_region : __end_of_early_ioremap_region;

#घोषणा FIXMAP_PAGE_COMMON	(L_PTE_YOUNG | L_PTE_PRESENT | L_PTE_XN | L_PTE_सूचीTY)

#घोषणा FIXMAP_PAGE_NORMAL	(pgprot_kernel | L_PTE_XN)
#घोषणा FIXMAP_PAGE_RO		(FIXMAP_PAGE_NORMAL | L_PTE_RDONLY)

/* Used by set_fixmap_(io|nocache), both meant क्रम mapping a device */
#घोषणा FIXMAP_PAGE_IO		(FIXMAP_PAGE_COMMON | L_PTE_MT_DEV_SHARED | L_PTE_SHARED)
#घोषणा FIXMAP_PAGE_NOCACHE	FIXMAP_PAGE_IO

#घोषणा __early_set_fixmap	__set_fixmap

#अगर_घोषित CONFIG_MMU

व्योम __set_fixmap(क्रमागत fixed_addresses idx, phys_addr_t phys, pgprot_t prot);
व्योम __init early_fixmap_init(व्योम);

#समावेश <यंत्र-generic/fixmap.h>

#अन्यथा

अटल अंतरभूत व्योम early_fixmap_init(व्योम) अणु पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
