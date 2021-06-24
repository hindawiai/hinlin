<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_PGTABLE_64_H
#घोषणा _ASM_RISCV_PGTABLE_64_H

#समावेश <linux/स्थिर.h>

#घोषणा PGसूची_SHIFT     30
/* Size of region mapped by a page global directory */
#घोषणा PGसूची_SIZE      (_AC(1, UL) << PGसूची_SHIFT)
#घोषणा PGसूची_MASK      (~(PGसूची_SIZE - 1))

#घोषणा PMD_SHIFT       21
/* Size of region mapped by a page middle directory */
#घोषणा PMD_SIZE        (_AC(1, UL) << PMD_SHIFT)
#घोषणा PMD_MASK        (~(PMD_SIZE - 1))

/* Page Middle Directory entry */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pmd;
पूर्ण pmd_t;

#घोषणा pmd_val(x)      ((x).pmd)
#घोषणा __pmd(x)        ((pmd_t) अणु (x) पूर्ण)

#घोषणा PTRS_PER_PMD    (PAGE_SIZE / माप(pmd_t))

अटल अंतरभूत पूर्णांक pud_present(pud_t pud)
अणु
	वापस (pud_val(pud) & _PAGE_PRESENT);
पूर्ण

अटल अंतरभूत पूर्णांक pud_none(pud_t pud)
अणु
	वापस (pud_val(pud) == 0);
पूर्ण

अटल अंतरभूत पूर्णांक pud_bad(pud_t pud)
अणु
	वापस !pud_present(pud);
पूर्ण

#घोषणा pud_leaf	pud_leaf
अटल अंतरभूत पूर्णांक pud_leaf(pud_t pud)
अणु
	वापस pud_present(pud) &&
	       (pud_val(pud) & (_PAGE_READ | _PAGE_WRITE | _PAGE_EXEC));
पूर्ण

अटल अंतरभूत व्योम set_pud(pud_t *pudp, pud_t pud)
अणु
	*pudp = pud;
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
	set_pud(pudp, __pud(0));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_page_vaddr(pud_t pud)
अणु
	वापस (अचिन्हित दीर्घ)pfn_to_virt(pud_val(pud) >> _PAGE_PFN_SHIFT);
पूर्ण

अटल अंतरभूत काष्ठा page *pud_page(pud_t pud)
अणु
	वापस pfn_to_page(pud_val(pud) >> _PAGE_PFN_SHIFT);
पूर्ण

अटल अंतरभूत pmd_t pfn_pmd(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	वापस __pmd((pfn << _PAGE_PFN_SHIFT) | pgprot_val(prot));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ _pmd_pfn(pmd_t pmd)
अणु
	वापस pmd_val(pmd) >> _PAGE_PFN_SHIFT;
पूर्ण

#घोषणा pmd_ERROR(e) \
	pr_err("%s:%d: bad pmd %016lx.\n", __खाता__, __LINE__, pmd_val(e))

#पूर्ण_अगर /* _ASM_RISCV_PGTABLE_64_H */
