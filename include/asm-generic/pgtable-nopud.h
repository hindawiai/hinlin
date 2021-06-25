<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PGTABLE_NOPUD_H
#घोषणा _PGTABLE_NOPUD_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र-generic/pgtable-nop4d.h>

#घोषणा __PAGETABLE_PUD_FOLDED 1

/*
 * Having the pud type consist of a p4d माला_लो the size right, and allows
 * us to conceptually access the p4d entry that this pud is folded पूर्णांकo
 * without casting.
 */
प्रकार काष्ठा अणु p4d_t p4d; पूर्ण pud_t;

#घोषणा PUD_SHIFT	P4D_SHIFT
#घोषणा PTRS_PER_PUD	1
#घोषणा PUD_SIZE  	(1UL << PUD_SHIFT)
#घोषणा PUD_MASK  	(~(PUD_SIZE-1))

/*
 * The "p4d_xxx()" functions here are trivial क्रम a folded two-level
 * setup: the pud is never bad, and a pud always exists (as it's folded
 * पूर्णांकo the p4d entry)
 */
अटल अंतरभूत पूर्णांक p4d_none(p4d_t p4d)		अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक p4d_bad(p4d_t p4d)		अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक p4d_present(p4d_t p4d)	अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम p4d_clear(p4d_t *p4d)	अणु पूर्ण
#घोषणा pud_ERROR(pud)				(p4d_ERROR((pud).p4d))

#घोषणा p4d_populate(mm, p4d, pud)		करो अणु पूर्ण जबतक (0)
#घोषणा p4d_populate_safe(mm, p4d, pud)		करो अणु पूर्ण जबतक (0)
/*
 * (puds are folded पूर्णांकo p4ds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
#घोषणा set_p4d(p4dptr, p4dval)	set_pud((pud_t *)(p4dptr), (pud_t) अणु p4dval पूर्ण)

अटल अंतरभूत pud_t *pud_offset(p4d_t *p4d, अचिन्हित दीर्घ address)
अणु
	वापस (pud_t *)p4d;
पूर्ण
#घोषणा pud_offset pud_offset

#घोषणा pud_val(x)				(p4d_val((x).p4d))
#घोषणा __pud(x)				((pud_t) अणु __p4d(x) पूर्ण)

#घोषणा p4d_page(p4d)				(pud_page((pud_t)अणु p4d पूर्ण))
#घोषणा p4d_page_vaddr(p4d)			(pud_page_vaddr((pud_t)अणु p4d पूर्ण))

/*
 * allocating and मुक्तing a pud is trivial: the 1-entry pud is
 * inside the p4d, so has no extra memory associated with it.
 */
#घोषणा pud_alloc_one(mm, address)		शून्य
#घोषणा pud_मुक्त(mm, x)				करो अणु पूर्ण जबतक (0)
#घोषणा pud_मुक्त_tlb(tlb, x, a)		        करो अणु पूर्ण जबतक (0)

#अघोषित  pud_addr_end
#घोषणा pud_addr_end(addr, end)			(end)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _PGTABLE_NOPUD_H */
