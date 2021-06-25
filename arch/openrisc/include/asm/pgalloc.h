<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_PGALLOC_H
#घोषणा __ASM_OPENRISC_PGALLOC_H

#समावेश <यंत्र/page.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>

#घोषणा __HAVE_ARCH_PTE_ALLOC_ONE_KERNEL
#समावेश <यंत्र-generic/pgभाग.स>

बाह्य पूर्णांक mem_init_करोne;

#घोषणा pmd_populate_kernel(mm, pmd, pte) \
	set_pmd(pmd, __pmd(_KERNPG_TABLE + __pa(pte)))

अटल अंतरभूत व्योम pmd_populate(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				काष्ठा page *pte)
अणु
	set_pmd(pmd, __pmd(_KERNPG_TABLE +
		     ((अचिन्हित दीर्घ)page_to_pfn(pte) <<
		     (अचिन्हित दीर्घ) PAGE_SHIFT)));
पूर्ण

/*
 * Allocate and मुक्त page tables.
 */
अटल अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *ret = (pgd_t *)__get_मुक्त_page(GFP_KERNEL);

	अगर (ret) अणु
		स_रखो(ret, 0, USER_PTRS_PER_PGD * माप(pgd_t));
		स_नकल(ret + USER_PTRS_PER_PGD,
		       swapper_pg_dir + USER_PTRS_PER_PGD,
		       (PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));

	पूर्ण
	वापस ret;
पूर्ण

#अगर 0
/* FIXME: This seems to be the preferred style, but we are using
 * current_pgd (from mm->pgd) to load kernel pages so we need it
 * initialized.  This needs to be looked पूर्णांकo.
 */
बाह्य अंतरभूत pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस (pgd_t *)get_zeroed_page(GFP_KERNEL);
पूर्ण
#पूर्ण_अगर

बाह्य pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm);

#घोषणा __pte_मुक्त_tlb(tlb, pte, addr)	\
करो अणु					\
	pgtable_pte_page_dtor(pte);	\
	tlb_हटाओ_page((tlb), (pte));	\
पूर्ण जबतक (0)

#घोषणा pmd_pgtable(pmd) pmd_page(pmd)

#पूर्ण_अगर
