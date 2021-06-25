<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_32_H
#घोषणा _ASM_X86_PGTABLE_32_H

#समावेश <यंत्र/pgtable_32_types.h>

/*
 * The Linux memory management assumes a three-level page table setup. On
 * the i386, we use that, but "fold" the mid level पूर्णांकo the top-level page
 * table, so that we physically have the same two-level page table as the
 * i386 mmu expects.
 *
 * This file contains the functions and defines necessary to modअगरy and use
 * the i386 page table tree.
 */
#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/processor.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/paravirt.h>

#समावेश <linux/bitops.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

काष्ठा mm_काष्ठा;
काष्ठा vm_area_काष्ठा;

बाह्य pgd_t swapper_pg_dir[1024];
बाह्य pgd_t initial_page_table[1024];
बाह्य pmd_t initial_pg_pmd[];

व्योम paging_init(व्योम);
व्योम sync_initial_page_table(व्योम);

#अगर_घोषित CONFIG_X86_PAE
# include <यंत्र/pgtable-3level.h>
#अन्यथा
# include <यंत्र/pgtable-2level.h>
#पूर्ण_अगर

/* Clear a kernel PTE and flush it from the TLB */
#घोषणा kpte_clear_flush(ptep, vaddr)		\
करो अणु						\
	pte_clear(&init_mm, (vaddr), (ptep));	\
	flush_tlb_one_kernel((vaddr));		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * kern_addr_valid() is (1) क्रम FLATMEM and (0) क्रम SPARSEMEM
 */
#अगर_घोषित CONFIG_FLATMEM
#घोषणा kern_addr_valid(addr)	(1)
#अन्यथा
#घोषणा kern_addr_valid(kaddr)	(0)
#पूर्ण_अगर

/*
 * This is used to calculate the .brk reservation क्रम initial pagetables.
 * Enough space is reserved to allocate pagetables sufficient to cover all
 * of LOWMEM_PAGES, which is an upper bound on the size of the direct map of
 * lowmem.
 *
 * With PAE paging (PTRS_PER_PMD > 1), we allocate PTRS_PER_PGD == 4 pages क्रम
 * the PMD's in addition to the pages required क्रम the last level pagetables.
 */
#अगर PTRS_PER_PMD > 1
#घोषणा PAGE_TABLE_SIZE(pages) (((pages) / PTRS_PER_PMD) + PTRS_PER_PGD)
#अन्यथा
#घोषणा PAGE_TABLE_SIZE(pages) ((pages) / PTRS_PER_PGD)
#पूर्ण_अगर

/*
 * Number of possible pages in the lowmem region.
 *
 * We shअगरt 2 by 31 instead of 1 by 32 to the left in order to aव्योम a
 * gas warning about overflowing shअगरt count when gas has been compiled
 * with only a host target support using a 32-bit type क्रम पूर्णांकernal
 * representation.
 */
#घोषणा LOWMEM_PAGES ((((_ULL(2)<<31) - __PAGE_OFFSET) >> PAGE_SHIFT))

#पूर्ण_अगर /* _ASM_X86_PGTABLE_32_H */
