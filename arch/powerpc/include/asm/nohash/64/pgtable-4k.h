<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_64_PGTABLE_4K_H
#घोषणा _ASM_POWERPC_NOHASH_64_PGTABLE_4K_H

#समावेश <यंत्र-generic/pgtable-nop4d.h>

/*
 * Entries per page directory level.  The PTE level must use a 64b record
 * क्रम each page table entry.  The PMD and PGD level use a 32b record क्रम
 * each entry by assuming that each entry is page aligned.
 */
#घोषणा PTE_INDEX_SIZE  9
#घोषणा PMD_INDEX_SIZE  7
#घोषणा PUD_INDEX_SIZE  9
#घोषणा PGD_INDEX_SIZE  9

#अगर_अघोषित __ASSEMBLY__
#घोषणा PTE_TABLE_SIZE	(माप(pte_t) << PTE_INDEX_SIZE)
#घोषणा PMD_TABLE_SIZE	(माप(pmd_t) << PMD_INDEX_SIZE)
#घोषणा PUD_TABLE_SIZE	(माप(pud_t) << PUD_INDEX_SIZE)
#घोषणा PGD_TABLE_SIZE	(माप(pgd_t) << PGD_INDEX_SIZE)
#पूर्ण_अगर	/* __ASSEMBLY__ */

#घोषणा PTRS_PER_PTE	(1 << PTE_INDEX_SIZE)
#घोषणा PTRS_PER_PMD	(1 << PMD_INDEX_SIZE)
#घोषणा PTRS_PER_PUD	(1 << PUD_INDEX_SIZE)
#घोषणा PTRS_PER_PGD	(1 << PGD_INDEX_SIZE)

/* PMD_SHIFT determines what a second-level page table entry can map */
#घोषणा PMD_SHIFT	(PAGE_SHIFT + PTE_INDEX_SIZE)
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))

/* PUD_SHIFT determines what a third-level page table entry can map */
#घोषणा PUD_SHIFT	(PMD_SHIFT + PMD_INDEX_SIZE)
#घोषणा PUD_SIZE	(1UL << PUD_SHIFT)
#घोषणा PUD_MASK	(~(PUD_SIZE-1))

/* PGसूची_SHIFT determines what a fourth-level page table entry can map */
#घोषणा PGसूची_SHIFT	(PUD_SHIFT + PUD_INDEX_SIZE)
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/* Bits to mask out from a PMD to get to the PTE page */
#घोषणा PMD_MASKED_BITS		0
/* Bits to mask out from a PUD to get to the PMD page */
#घोषणा PUD_MASKED_BITS		0
/* Bits to mask out from a P4D to get to the PUD page */
#घोषणा P4D_MASKED_BITS		0


/*
 * 4-level page tables related bits
 */

#घोषणा p4d_none(p4d)		(!p4d_val(p4d))
#घोषणा p4d_bad(p4d)		(p4d_val(p4d) == 0)
#घोषणा p4d_present(p4d)	(p4d_val(p4d) != 0)
#घोषणा p4d_page_vaddr(p4d)	(p4d_val(p4d) & ~P4D_MASKED_BITS)

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम p4d_clear(p4d_t *p4dp)
अणु
	*p4dp = __p4d(0);
पूर्ण

अटल अंतरभूत pte_t p4d_pte(p4d_t p4d)
अणु
	वापस __pte(p4d_val(p4d));
पूर्ण

अटल अंतरभूत p4d_t pte_p4d(pte_t pte)
अणु
	वापस __p4d(pte_val(pte));
पूर्ण
बाह्य काष्ठा page *p4d_page(p4d_t p4d);

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा pud_ERROR(e) \
	pr_err("%s:%d: bad pud %08lx.\n", __खाता__, __LINE__, pud_val(e))

/*
 * On all 4K setups, remap_4k_pfn() equates to remap_pfn_range() */
#घोषणा remap_4k_pfn(vma, addr, pfn, prot)	\
	remap_pfn_range((vma), (addr), (pfn), PAGE_SIZE, (prot))

#पूर्ण_अगर /* _ _ASM_POWERPC_NOHASH_64_PGTABLE_4K_H */
