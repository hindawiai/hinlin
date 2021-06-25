<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PGTABLE_RADIX_64K_H
#घोषणा _ASM_POWERPC_PGTABLE_RADIX_64K_H

/*
 * For 64K page size supported index is 13/9/9/5
 */
#घोषणा RADIX_PTE_INDEX_SIZE   5  // size: 8B <<  5 = 256B, maps 2^5  x   64K =   2MB
#घोषणा RADIX_PMD_INDEX_SIZE   9  // size: 8B <<  9 =  4KB, maps 2^9  x   2MB =   1GB
#घोषणा RADIX_PUD_INDEX_SIZE   9  // size: 8B <<  9 =  4KB, maps 2^9  x   1GB = 512GB
#घोषणा RADIX_PGD_INDEX_SIZE  13  // size: 8B << 13 = 64KB, maps 2^13 x 512GB =   4PB

/*
 * We use a 256 byte PTE page fragment in radix
 * 8 bytes per each PTE entry.
 */
#घोषणा RADIX_PTE_FRAG_SIZE_SHIFT  (RADIX_PTE_INDEX_SIZE + 3)
#घोषणा RADIX_PTE_FRAG_NR	(PAGE_SIZE >> RADIX_PTE_FRAG_SIZE_SHIFT)

#घोषणा RADIX_PMD_FRAG_SIZE_SHIFT  (RADIX_PMD_INDEX_SIZE + 3)
#घोषणा RADIX_PMD_FRAG_NR	(PAGE_SIZE >> RADIX_PMD_FRAG_SIZE_SHIFT)

#पूर्ण_अगर /* _ASM_POWERPC_PGTABLE_RADIX_64K_H */
