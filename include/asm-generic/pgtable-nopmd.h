<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PGTABLE_NOPMD_H
#घोषणा _PGTABLE_NOPMD_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र-generic/pgtable-nopud.h>

काष्ठा mm_काष्ठा;

#घोषणा __PAGETABLE_PMD_FOLDED 1

/*
 * Having the pmd type consist of a pud माला_लो the size right, and allows
 * us to conceptually access the pud entry that this pmd is folded पूर्णांकo
 * without casting.
 */
प्रकार काष्ठा अणु pud_t pud; पूर्ण pmd_t;

#घोषणा PMD_SHIFT	PUD_SHIFT
#घोषणा PTRS_PER_PMD	1
#घोषणा PMD_SIZE  	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK  	(~(PMD_SIZE-1))

/*
 * The "pud_xxx()" functions here are trivial क्रम a folded two-level
 * setup: the pmd is never bad, and a pmd always exists (as it's folded
 * पूर्णांकo the pud entry)
 */
अटल अंतरभूत पूर्णांक pud_none(pud_t pud)		अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pud_bad(pud_t pud)		अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pud_present(pud_t pud)	अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम pud_clear(pud_t *pud)	अणु पूर्ण
#घोषणा pmd_ERROR(pmd)				(pud_ERROR((pmd).pud))

#घोषणा pud_populate(mm, pmd, pte)		करो अणु पूर्ण जबतक (0)

/*
 * (pmds are folded पूर्णांकo puds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
#घोषणा set_pud(pudptr, pudval)			set_pmd((pmd_t *)(pudptr), (pmd_t) अणु pudval पूर्ण)

अटल अंतरभूत pmd_t * pmd_offset(pud_t * pud, अचिन्हित दीर्घ address)
अणु
	वापस (pmd_t *)pud;
पूर्ण
#घोषणा pmd_offset pmd_offset

#घोषणा pmd_val(x)				(pud_val((x).pud))
#घोषणा __pmd(x)				((pmd_t) अणु __pud(x) पूर्ण )

#घोषणा pud_page(pud)				(pmd_page((pmd_t)अणु pud पूर्ण))
#घोषणा pud_page_vaddr(pud)			(pmd_page_vaddr((pmd_t)अणु pud पूर्ण))

/*
 * allocating and मुक्तing a pmd is trivial: the 1-entry pmd is
 * inside the pud, so has no extra memory associated with it.
 */
#घोषणा pmd_alloc_one(mm, address)		शून्य
अटल अंतरभूत व्योम pmd_मुक्त(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
पूर्ण
#घोषणा pmd_मुक्त_tlb(tlb, x, a)		करो अणु पूर्ण जबतक (0)

#अघोषित  pmd_addr_end
#घोषणा pmd_addr_end(addr, end)			(end)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _PGTABLE_NOPMD_H */
