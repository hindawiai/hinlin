<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PGTABLE_NOP4D_H
#घोषणा _PGTABLE_NOP4D_H

#अगर_अघोषित __ASSEMBLY__

#घोषणा __PAGETABLE_P4D_FOLDED 1

प्रकार काष्ठा अणु pgd_t pgd; पूर्ण p4d_t;

#घोषणा P4D_SHIFT		PGसूची_SHIFT
#घोषणा MAX_PTRS_PER_P4D	1
#घोषणा PTRS_PER_P4D		1
#घोषणा P4D_SIZE		(1UL << P4D_SHIFT)
#घोषणा P4D_MASK		(~(P4D_SIZE-1))

/*
 * The "pgd_xxx()" functions here are trivial क्रम a folded two-level
 * setup: the p4d is never bad, and a p4d always exists (as it's folded
 * पूर्णांकo the pgd entry)
 */
अटल अंतरभूत पूर्णांक pgd_none(pgd_t pgd)		अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pgd_bad(pgd_t pgd)		अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pgd_present(pgd_t pgd)	अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम pgd_clear(pgd_t *pgd)	अणु पूर्ण
#घोषणा p4d_ERROR(p4d)				(pgd_ERROR((p4d).pgd))

#घोषणा pgd_populate(mm, pgd, p4d)		करो अणु पूर्ण जबतक (0)
#घोषणा pgd_populate_safe(mm, pgd, p4d)		करो अणु पूर्ण जबतक (0)
/*
 * (p4ds are folded पूर्णांकo pgds so this करोesn't get actually called,
 * but the define is needed क्रम a generic अंतरभूत function.)
 */
#घोषणा set_pgd(pgdptr, pgdval)	set_p4d((p4d_t *)(pgdptr), (p4d_t) अणु pgdval पूर्ण)

अटल अंतरभूत p4d_t *p4d_offset(pgd_t *pgd, अचिन्हित दीर्घ address)
अणु
	वापस (p4d_t *)pgd;
पूर्ण

#घोषणा p4d_val(x)				(pgd_val((x).pgd))
#घोषणा __p4d(x)				((p4d_t) अणु __pgd(x) पूर्ण)

#घोषणा pgd_page(pgd)				(p4d_page((p4d_t)अणु pgd पूर्ण))
#घोषणा pgd_page_vaddr(pgd)			(p4d_page_vaddr((p4d_t)अणु pgd पूर्ण))

/*
 * allocating and मुक्तing a p4d is trivial: the 1-entry p4d is
 * inside the pgd, so has no extra memory associated with it.
 */
#घोषणा p4d_alloc_one(mm, address)		शून्य
#घोषणा p4d_मुक्त(mm, x)				करो अणु पूर्ण जबतक (0)
#घोषणा p4d_मुक्त_tlb(tlb, x, a)			करो अणु पूर्ण जबतक (0)

#अघोषित  p4d_addr_end
#घोषणा p4d_addr_end(addr, end)			(end)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _PGTABLE_NOP4D_H */
