<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PGTABLE_3LEVEL_H
#घोषणा __ASM_SH_PGTABLE_3LEVEL_H

#समावेश <यंत्र-generic/pgtable-nopud.h>

/*
 * Some cores need a 3-level page table layout, क्रम example when using
 * 64-bit PTEs and 4K pages.
 */
#घोषणा PAGETABLE_LEVELS	3

#घोषणा PTE_MAGNITUDE		3	/* 64-bit PTEs on SH-X2 TLB */

/* PGD bits */
#घोषणा PGसूची_SHIFT		30

#घोषणा PTRS_PER_PGD		4
#घोषणा USER_PTRS_PER_PGD	2

/* PMD bits */
#घोषणा PMD_SHIFT	(PAGE_SHIFT + (PAGE_SHIFT - PTE_MAGNITUDE))
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))

#घोषणा PTRS_PER_PMD	((1 << PGसूची_SHIFT) / PMD_SIZE)

#घोषणा pmd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pmd %016llx.\n", __खाता__, __LINE__, pmd_val(e))

प्रकार काष्ठा अणु अचिन्हित दीर्घ दीर्घ pmd; पूर्ण pmd_t;
#घोषणा pmd_val(x)	((x).pmd)
#घोषणा __pmd(x)	((pmd_t) अणु (x) पूर्ण )

अटल अंतरभूत अचिन्हित दीर्घ pud_page_vaddr(pud_t pud)
अणु
	वापस pud_val(pud);
पूर्ण

/* only used by the stubbed out hugetlb gup code, should never be called */
#घोषणा pud_page(pud)		शून्य
#घोषणा pud_none(x)	(!pud_val(x))
#घोषणा pud_present(x)	(pud_val(x))
#घोषणा pud_clear(xp)	करो अणु set_pud(xp, __pud(0)); पूर्ण जबतक (0)
#घोषणा	pud_bad(x)	(pud_val(x) & ~PAGE_MASK)

/*
 * (puds are folded पूर्णांकo pgds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
#घोषणा set_pud(pudptr, pudval) करो अणु *(pudptr) = (pudval); पूर्ण जबतक(0)

#पूर्ण_अगर /* __ASM_SH_PGTABLE_3LEVEL_H */
