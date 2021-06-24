<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_PGTABLE_HWDEF_H
#घोषणा __ASM_PGTABLE_HWDEF_H

#समावेश <यंत्र/memory.h>

/*
 * Number of page-table levels required to address 'va_bits' wide
 * address, without section mapping. We resolve the top (va_bits - PAGE_SHIFT)
 * bits with (PAGE_SHIFT - 3) bits at each page table level. Hence:
 *
 *  levels = DIV_ROUND_UP((va_bits - PAGE_SHIFT), (PAGE_SHIFT - 3))
 *
 * where DIV_ROUND_UP(n, d) => (((n) + (d) - 1) / (d))
 *
 * We cannot include linux/kernel.h which defines DIV_ROUND_UP here
 * due to build issues. So we खोलो code DIV_ROUND_UP here:
 *
 *	((((va_bits) - PAGE_SHIFT) + (PAGE_SHIFT - 3) - 1) / (PAGE_SHIFT - 3))
 *
 * which माला_लो simplअगरied as :
 */
#घोषणा ARM64_HW_PGTABLE_LEVELS(va_bits) (((va_bits) - 4) / (PAGE_SHIFT - 3))

/*
 * Size mapped by an entry at level n ( 0 <= n <= 3)
 * We map (PAGE_SHIFT - 3) at all translation levels and PAGE_SHIFT bits
 * in the final page. The maximum number of translation levels supported by
 * the architecture is 4. Hence, starting at level n, we have further
 * ((4 - n) - 1) levels of translation excluding the offset within the page.
 * So, the total number of bits mapped by an entry at level n is :
 *
 *  ((4 - n) - 1) * (PAGE_SHIFT - 3) + PAGE_SHIFT
 *
 * Rearranging it a bit we get :
 *   (4 - n) * (PAGE_SHIFT - 3) + 3
 */
#घोषणा ARM64_HW_PGTABLE_LEVEL_SHIFT(n)	((PAGE_SHIFT - 3) * (4 - (n)) + 3)

#घोषणा PTRS_PER_PTE		(1 << (PAGE_SHIFT - 3))

/*
 * PMD_SHIFT determines the size a level 2 page table entry can map.
 */
#अगर CONFIG_PGTABLE_LEVELS > 2
#घोषणा PMD_SHIFT		ARM64_HW_PGTABLE_LEVEL_SHIFT(2)
#घोषणा PMD_SIZE		(_AC(1, UL) << PMD_SHIFT)
#घोषणा PMD_MASK		(~(PMD_SIZE-1))
#घोषणा PTRS_PER_PMD		PTRS_PER_PTE
#पूर्ण_अगर

/*
 * PUD_SHIFT determines the size a level 1 page table entry can map.
 */
#अगर CONFIG_PGTABLE_LEVELS > 3
#घोषणा PUD_SHIFT		ARM64_HW_PGTABLE_LEVEL_SHIFT(1)
#घोषणा PUD_SIZE		(_AC(1, UL) << PUD_SHIFT)
#घोषणा PUD_MASK		(~(PUD_SIZE-1))
#घोषणा PTRS_PER_PUD		PTRS_PER_PTE
#पूर्ण_अगर

/*
 * PGसूची_SHIFT determines the size a top-level page table entry can map
 * (depending on the configuration, this level can be 0, 1 or 2).
 */
#घोषणा PGसूची_SHIFT		ARM64_HW_PGTABLE_LEVEL_SHIFT(4 - CONFIG_PGTABLE_LEVELS)
#घोषणा PGसूची_SIZE		(_AC(1, UL) << PGसूची_SHIFT)
#घोषणा PGसूची_MASK		(~(PGसूची_SIZE-1))
#घोषणा PTRS_PER_PGD		(1 << (VA_BITS - PGसूची_SHIFT))

/*
 * Section address mask and size definitions.
 */
#घोषणा SECTION_SHIFT		PMD_SHIFT
#घोषणा SECTION_SIZE		(_AC(1, UL) << SECTION_SHIFT)
#घोषणा SECTION_MASK		(~(SECTION_SIZE-1))

/*
 * Contiguous page definitions.
 */
#घोषणा CONT_PTE_SHIFT		(CONFIG_ARM64_CONT_PTE_SHIFT + PAGE_SHIFT)
#घोषणा CONT_PTES		(1 << (CONT_PTE_SHIFT - PAGE_SHIFT))
#घोषणा CONT_PTE_SIZE		(CONT_PTES * PAGE_SIZE)
#घोषणा CONT_PTE_MASK		(~(CONT_PTE_SIZE - 1))

#घोषणा CONT_PMD_SHIFT		(CONFIG_ARM64_CONT_PMD_SHIFT + PMD_SHIFT)
#घोषणा CONT_PMDS		(1 << (CONT_PMD_SHIFT - PMD_SHIFT))
#घोषणा CONT_PMD_SIZE		(CONT_PMDS * PMD_SIZE)
#घोषणा CONT_PMD_MASK		(~(CONT_PMD_SIZE - 1))

/*
 * Hardware page table definitions.
 *
 * Level 0 descriptor (P4D).
 */
#घोषणा P4D_TYPE_TABLE		(_AT(p4dval_t, 3) << 0)
#घोषणा P4D_TABLE_BIT		(_AT(p4dval_t, 1) << 1)
#घोषणा P4D_TYPE_MASK		(_AT(p4dval_t, 3) << 0)
#घोषणा P4D_TYPE_SECT		(_AT(p4dval_t, 1) << 0)
#घोषणा P4D_SECT_RDONLY		(_AT(p4dval_t, 1) << 7)		/* AP[2] */
#घोषणा P4D_TABLE_PXN		(_AT(p4dval_t, 1) << 59)
#घोषणा P4D_TABLE_UXN		(_AT(p4dval_t, 1) << 60)

/*
 * Level 1 descriptor (PUD).
 */
#घोषणा PUD_TYPE_TABLE		(_AT(pudval_t, 3) << 0)
#घोषणा PUD_TABLE_BIT		(_AT(pudval_t, 1) << 1)
#घोषणा PUD_TYPE_MASK		(_AT(pudval_t, 3) << 0)
#घोषणा PUD_TYPE_SECT		(_AT(pudval_t, 1) << 0)
#घोषणा PUD_SECT_RDONLY		(_AT(pudval_t, 1) << 7)		/* AP[2] */
#घोषणा PUD_TABLE_PXN		(_AT(pudval_t, 1) << 59)
#घोषणा PUD_TABLE_UXN		(_AT(pudval_t, 1) << 60)

/*
 * Level 2 descriptor (PMD).
 */
#घोषणा PMD_TYPE_MASK		(_AT(pmdval_t, 3) << 0)
#घोषणा PMD_TYPE_TABLE		(_AT(pmdval_t, 3) << 0)
#घोषणा PMD_TYPE_SECT		(_AT(pmdval_t, 1) << 0)
#घोषणा PMD_TABLE_BIT		(_AT(pmdval_t, 1) << 1)

/*
 * Section
 */
#घोषणा PMD_SECT_VALID		(_AT(pmdval_t, 1) << 0)
#घोषणा PMD_SECT_USER		(_AT(pmdval_t, 1) << 6)		/* AP[1] */
#घोषणा PMD_SECT_RDONLY		(_AT(pmdval_t, 1) << 7)		/* AP[2] */
#घोषणा PMD_SECT_S		(_AT(pmdval_t, 3) << 8)
#घोषणा PMD_SECT_AF		(_AT(pmdval_t, 1) << 10)
#घोषणा PMD_SECT_NG		(_AT(pmdval_t, 1) << 11)
#घोषणा PMD_SECT_CONT		(_AT(pmdval_t, 1) << 52)
#घोषणा PMD_SECT_PXN		(_AT(pmdval_t, 1) << 53)
#घोषणा PMD_SECT_UXN		(_AT(pmdval_t, 1) << 54)
#घोषणा PMD_TABLE_PXN		(_AT(pmdval_t, 1) << 59)
#घोषणा PMD_TABLE_UXN		(_AT(pmdval_t, 1) << 60)

/*
 * AttrIndx[2:0] encoding (mapping attributes defined in the MAIR* रेजिस्टरs).
 */
#घोषणा PMD_ATTRINDX(t)		(_AT(pmdval_t, (t)) << 2)
#घोषणा PMD_ATTRINDX_MASK	(_AT(pmdval_t, 7) << 2)

/*
 * Level 3 descriptor (PTE).
 */
#घोषणा PTE_VALID		(_AT(pteval_t, 1) << 0)
#घोषणा PTE_TYPE_MASK		(_AT(pteval_t, 3) << 0)
#घोषणा PTE_TYPE_PAGE		(_AT(pteval_t, 3) << 0)
#घोषणा PTE_TABLE_BIT		(_AT(pteval_t, 1) << 1)
#घोषणा PTE_USER		(_AT(pteval_t, 1) << 6)		/* AP[1] */
#घोषणा PTE_RDONLY		(_AT(pteval_t, 1) << 7)		/* AP[2] */
#घोषणा PTE_SHARED		(_AT(pteval_t, 3) << 8)		/* SH[1:0], inner shareable */
#घोषणा PTE_AF			(_AT(pteval_t, 1) << 10)	/* Access Flag */
#घोषणा PTE_NG			(_AT(pteval_t, 1) << 11)	/* nG */
#घोषणा PTE_GP			(_AT(pteval_t, 1) << 50)	/* BTI guarded */
#घोषणा PTE_DBM			(_AT(pteval_t, 1) << 51)	/* Dirty Bit Management */
#घोषणा PTE_CONT		(_AT(pteval_t, 1) << 52)	/* Contiguous range */
#घोषणा PTE_PXN			(_AT(pteval_t, 1) << 53)	/* Privileged XN */
#घोषणा PTE_UXN			(_AT(pteval_t, 1) << 54)	/* User XN */

#घोषणा PTE_ADDR_LOW		(((_AT(pteval_t, 1) << (48 - PAGE_SHIFT)) - 1) << PAGE_SHIFT)
#अगर_घोषित CONFIG_ARM64_PA_BITS_52
#घोषणा PTE_ADDR_HIGH		(_AT(pteval_t, 0xf) << 12)
#घोषणा PTE_ADDR_MASK		(PTE_ADDR_LOW | PTE_ADDR_HIGH)
#अन्यथा
#घोषणा PTE_ADDR_MASK		PTE_ADDR_LOW
#पूर्ण_अगर

/*
 * AttrIndx[2:0] encoding (mapping attributes defined in the MAIR* रेजिस्टरs).
 */
#घोषणा PTE_ATTRINDX(t)		(_AT(pteval_t, (t)) << 2)
#घोषणा PTE_ATTRINDX_MASK	(_AT(pteval_t, 7) << 2)

/*
 * Memory Attribute override क्रम Stage-2 (MemAttr[3:0])
 */
#घोषणा PTE_S2_MEMATTR(t)	(_AT(pteval_t, (t)) << 2)

/*
 * Highest possible physical address supported.
 */
#घोषणा PHYS_MASK_SHIFT		(CONFIG_ARM64_PA_BITS)
#घोषणा PHYS_MASK		((UL(1) << PHYS_MASK_SHIFT) - 1)

#घोषणा TTBR_CNP_BIT		(UL(1) << 0)

/*
 * TCR flags.
 */
#घोषणा TCR_T0SZ_OFFSET		0
#घोषणा TCR_T1SZ_OFFSET		16
#घोषणा TCR_T0SZ(x)		((UL(64) - (x)) << TCR_T0SZ_OFFSET)
#घोषणा TCR_T1SZ(x)		((UL(64) - (x)) << TCR_T1SZ_OFFSET)
#घोषणा TCR_TxSZ(x)		(TCR_T0SZ(x) | TCR_T1SZ(x))
#घोषणा TCR_TxSZ_WIDTH		6
#घोषणा TCR_T0SZ_MASK		(((UL(1) << TCR_TxSZ_WIDTH) - 1) << TCR_T0SZ_OFFSET)
#घोषणा TCR_T1SZ_MASK		(((UL(1) << TCR_TxSZ_WIDTH) - 1) << TCR_T1SZ_OFFSET)

#घोषणा TCR_EPD0_SHIFT		7
#घोषणा TCR_EPD0_MASK		(UL(1) << TCR_EPD0_SHIFT)
#घोषणा TCR_IRGN0_SHIFT		8
#घोषणा TCR_IRGN0_MASK		(UL(3) << TCR_IRGN0_SHIFT)
#घोषणा TCR_IRGN0_NC		(UL(0) << TCR_IRGN0_SHIFT)
#घोषणा TCR_IRGN0_WBWA		(UL(1) << TCR_IRGN0_SHIFT)
#घोषणा TCR_IRGN0_WT		(UL(2) << TCR_IRGN0_SHIFT)
#घोषणा TCR_IRGN0_WBnWA		(UL(3) << TCR_IRGN0_SHIFT)

#घोषणा TCR_EPD1_SHIFT		23
#घोषणा TCR_EPD1_MASK		(UL(1) << TCR_EPD1_SHIFT)
#घोषणा TCR_IRGN1_SHIFT		24
#घोषणा TCR_IRGN1_MASK		(UL(3) << TCR_IRGN1_SHIFT)
#घोषणा TCR_IRGN1_NC		(UL(0) << TCR_IRGN1_SHIFT)
#घोषणा TCR_IRGN1_WBWA		(UL(1) << TCR_IRGN1_SHIFT)
#घोषणा TCR_IRGN1_WT		(UL(2) << TCR_IRGN1_SHIFT)
#घोषणा TCR_IRGN1_WBnWA		(UL(3) << TCR_IRGN1_SHIFT)

#घोषणा TCR_IRGN_NC		(TCR_IRGN0_NC | TCR_IRGN1_NC)
#घोषणा TCR_IRGN_WBWA		(TCR_IRGN0_WBWA | TCR_IRGN1_WBWA)
#घोषणा TCR_IRGN_WT		(TCR_IRGN0_WT | TCR_IRGN1_WT)
#घोषणा TCR_IRGN_WBnWA		(TCR_IRGN0_WBnWA | TCR_IRGN1_WBnWA)
#घोषणा TCR_IRGN_MASK		(TCR_IRGN0_MASK | TCR_IRGN1_MASK)


#घोषणा TCR_ORGN0_SHIFT		10
#घोषणा TCR_ORGN0_MASK		(UL(3) << TCR_ORGN0_SHIFT)
#घोषणा TCR_ORGN0_NC		(UL(0) << TCR_ORGN0_SHIFT)
#घोषणा TCR_ORGN0_WBWA		(UL(1) << TCR_ORGN0_SHIFT)
#घोषणा TCR_ORGN0_WT		(UL(2) << TCR_ORGN0_SHIFT)
#घोषणा TCR_ORGN0_WBnWA		(UL(3) << TCR_ORGN0_SHIFT)

#घोषणा TCR_ORGN1_SHIFT		26
#घोषणा TCR_ORGN1_MASK		(UL(3) << TCR_ORGN1_SHIFT)
#घोषणा TCR_ORGN1_NC		(UL(0) << TCR_ORGN1_SHIFT)
#घोषणा TCR_ORGN1_WBWA		(UL(1) << TCR_ORGN1_SHIFT)
#घोषणा TCR_ORGN1_WT		(UL(2) << TCR_ORGN1_SHIFT)
#घोषणा TCR_ORGN1_WBnWA		(UL(3) << TCR_ORGN1_SHIFT)

#घोषणा TCR_ORGN_NC		(TCR_ORGN0_NC | TCR_ORGN1_NC)
#घोषणा TCR_ORGN_WBWA		(TCR_ORGN0_WBWA | TCR_ORGN1_WBWA)
#घोषणा TCR_ORGN_WT		(TCR_ORGN0_WT | TCR_ORGN1_WT)
#घोषणा TCR_ORGN_WBnWA		(TCR_ORGN0_WBnWA | TCR_ORGN1_WBnWA)
#घोषणा TCR_ORGN_MASK		(TCR_ORGN0_MASK | TCR_ORGN1_MASK)

#घोषणा TCR_SH0_SHIFT		12
#घोषणा TCR_SH0_MASK		(UL(3) << TCR_SH0_SHIFT)
#घोषणा TCR_SH0_INNER		(UL(3) << TCR_SH0_SHIFT)

#घोषणा TCR_SH1_SHIFT		28
#घोषणा TCR_SH1_MASK		(UL(3) << TCR_SH1_SHIFT)
#घोषणा TCR_SH1_INNER		(UL(3) << TCR_SH1_SHIFT)
#घोषणा TCR_SHARED		(TCR_SH0_INNER | TCR_SH1_INNER)

#घोषणा TCR_TG0_SHIFT		14
#घोषणा TCR_TG0_MASK		(UL(3) << TCR_TG0_SHIFT)
#घोषणा TCR_TG0_4K		(UL(0) << TCR_TG0_SHIFT)
#घोषणा TCR_TG0_64K		(UL(1) << TCR_TG0_SHIFT)
#घोषणा TCR_TG0_16K		(UL(2) << TCR_TG0_SHIFT)

#घोषणा TCR_TG1_SHIFT		30
#घोषणा TCR_TG1_MASK		(UL(3) << TCR_TG1_SHIFT)
#घोषणा TCR_TG1_16K		(UL(1) << TCR_TG1_SHIFT)
#घोषणा TCR_TG1_4K		(UL(2) << TCR_TG1_SHIFT)
#घोषणा TCR_TG1_64K		(UL(3) << TCR_TG1_SHIFT)

#घोषणा TCR_IPS_SHIFT		32
#घोषणा TCR_IPS_MASK		(UL(7) << TCR_IPS_SHIFT)
#घोषणा TCR_A1			(UL(1) << 22)
#घोषणा TCR_ASID16		(UL(1) << 36)
#घोषणा TCR_TBI0		(UL(1) << 37)
#घोषणा TCR_TBI1		(UL(1) << 38)
#घोषणा TCR_HA			(UL(1) << 39)
#घोषणा TCR_HD			(UL(1) << 40)
#घोषणा TCR_TBID1		(UL(1) << 52)
#घोषणा TCR_NFD0		(UL(1) << 53)
#घोषणा TCR_NFD1		(UL(1) << 54)
#घोषणा TCR_E0PD0		(UL(1) << 55)
#घोषणा TCR_E0PD1		(UL(1) << 56)

/*
 * TTBR.
 */
#अगर_घोषित CONFIG_ARM64_PA_BITS_52
/*
 * This should be GENMASK_ULL(47, 2).
 * TTBR_ELx[1] is RES0 in this configuration.
 */
#घोषणा TTBR_BADDR_MASK_52	(((UL(1) << 46) - 1) << 2)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM64_VA_BITS_52
/* Must be at least 64-byte aligned to prevent corruption of the TTBR */
#घोषणा TTBR1_BADDR_4852_OFFSET	(((UL(1) << (52 - PGसूची_SHIFT)) - \
				 (UL(1) << (48 - PGसूची_SHIFT))) * 8)
#पूर्ण_अगर

#पूर्ण_अगर
