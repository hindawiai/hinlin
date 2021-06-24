<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/pgtable-3level-hwdef.h
 *
 * Copyright (C) 2011 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 */
#अगर_अघोषित _ASM_PGTABLE_3LEVEL_HWDEF_H
#घोषणा _ASM_PGTABLE_3LEVEL_HWDEF_H

/*
 * Hardware page table definitions.
 *
 * + Level 1/2 descriptor
 *   - common
 */
#घोषणा PMD_TYPE_MASK		(_AT(pmdval_t, 3) << 0)
#घोषणा PMD_TYPE_FAULT		(_AT(pmdval_t, 0) << 0)
#घोषणा PMD_TYPE_TABLE		(_AT(pmdval_t, 3) << 0)
#घोषणा PMD_TYPE_SECT		(_AT(pmdval_t, 1) << 0)
#घोषणा PMD_TABLE_BIT		(_AT(pmdval_t, 1) << 1)
#घोषणा PMD_BIT4		(_AT(pmdval_t, 0))
#घोषणा PMD_DOMAIN(x)		(_AT(pmdval_t, 0))
#घोषणा PMD_APTABLE_SHIFT	(61)
#घोषणा PMD_APTABLE		(_AT(pgdval_t, 3) << PGD_APTABLE_SHIFT)
#घोषणा PMD_PXNTABLE		(_AT(pgdval_t, 1) << 59)

/*
 *   - section
 */
#घोषणा PMD_SECT_BUFFERABLE	(_AT(pmdval_t, 1) << 2)
#घोषणा PMD_SECT_CACHEABLE	(_AT(pmdval_t, 1) << 3)
#घोषणा PMD_SECT_USER		(_AT(pmdval_t, 1) << 6)		/* AP[1] */
#घोषणा PMD_SECT_AP2		(_AT(pmdval_t, 1) << 7)		/* पढ़ो only */
#घोषणा PMD_SECT_S		(_AT(pmdval_t, 3) << 8)
#घोषणा PMD_SECT_AF		(_AT(pmdval_t, 1) << 10)
#घोषणा PMD_SECT_nG		(_AT(pmdval_t, 1) << 11)
#घोषणा PMD_SECT_PXN		(_AT(pmdval_t, 1) << 53)
#घोषणा PMD_SECT_XN		(_AT(pmdval_t, 1) << 54)
#घोषणा PMD_SECT_AP_WRITE	(_AT(pmdval_t, 0))
#घोषणा PMD_SECT_AP_READ	(_AT(pmdval_t, 0))
#घोषणा PMD_SECT_AP1		(_AT(pmdval_t, 1) << 6)
#घोषणा PMD_SECT_TEX(x)		(_AT(pmdval_t, 0))

/*
 * AttrIndx[2:0] encoding (mapping attributes defined in the MAIR* रेजिस्टरs).
 */
#घोषणा PMD_SECT_UNCACHED	(_AT(pmdval_t, 0) << 2)	/* strongly ordered */
#घोषणा PMD_SECT_BUFFERED	(_AT(pmdval_t, 1) << 2)	/* normal non-cacheable */
#घोषणा PMD_SECT_WT		(_AT(pmdval_t, 2) << 2)	/* normal inner ग_लिखो-through */
#घोषणा PMD_SECT_WB		(_AT(pmdval_t, 3) << 2)	/* normal inner ग_लिखो-back */
#घोषणा PMD_SECT_WBWA		(_AT(pmdval_t, 7) << 2)	/* normal inner ग_लिखो-alloc */
#घोषणा PMD_SECT_CACHE_MASK	(_AT(pmdval_t, 7) << 2)

/*
 * + Level 3 descriptor (PTE)
 */
#घोषणा PTE_TYPE_MASK		(_AT(pteval_t, 3) << 0)
#घोषणा PTE_TYPE_FAULT		(_AT(pteval_t, 0) << 0)
#घोषणा PTE_TYPE_PAGE		(_AT(pteval_t, 3) << 0)
#घोषणा PTE_TABLE_BIT		(_AT(pteval_t, 1) << 1)
#घोषणा PTE_BUFFERABLE		(_AT(pteval_t, 1) << 2)		/* AttrIndx[0] */
#घोषणा PTE_CACHEABLE		(_AT(pteval_t, 1) << 3)		/* AttrIndx[1] */
#घोषणा PTE_AP2			(_AT(pteval_t, 1) << 7)		/* AP[2] */
#घोषणा PTE_EXT_SHARED		(_AT(pteval_t, 3) << 8)		/* SH[1:0], inner shareable */
#घोषणा PTE_EXT_AF		(_AT(pteval_t, 1) << 10)	/* Access Flag */
#घोषणा PTE_EXT_NG		(_AT(pteval_t, 1) << 11)	/* nG */
#घोषणा PTE_EXT_PXN		(_AT(pteval_t, 1) << 53)	/* PXN */
#घोषणा PTE_EXT_XN		(_AT(pteval_t, 1) << 54)	/* XN */

/*
 * 40-bit physical address supported.
 */
#घोषणा PHYS_MASK_SHIFT		(40)
#घोषणा PHYS_MASK		((1ULL << PHYS_MASK_SHIFT) - 1)

/*
 * TTBR0/TTBR1 split (PAGE_OFFSET):
 *   0x40000000: T0SZ = 2, T1SZ = 0 (not used)
 *   0x80000000: T0SZ = 0, T1SZ = 1
 *   0xc0000000: T0SZ = 0, T1SZ = 2
 *
 * Only use this feature अगर PHYS_OFFSET <= PAGE_OFFSET, otherwise
 * booting secondary CPUs would end up using TTBR1 क्रम the identity
 * mapping set up in TTBR0.
 */
#अगर defined CONFIG_VMSPLIT_2G
#घोषणा TTBR1_OFFSET	16			/* skip two L1 entries */
#या_अगर defined CONFIG_VMSPLIT_3G
#घोषणा TTBR1_OFFSET	(4096 * (1 + 3))	/* only L2, skip pgd + 3*pmd */
#अन्यथा
#घोषणा TTBR1_OFFSET	0
#पूर्ण_अगर

#घोषणा TTBR1_SIZE	(((PAGE_OFFSET >> 30) - 1) << 16)

#पूर्ण_अगर
