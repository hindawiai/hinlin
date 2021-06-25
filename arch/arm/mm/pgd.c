<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/pgd.c
 *
 *  Copyright (C) 1998-2005 Russell King
 */
#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "mm.h"

#अगर_घोषित CONFIG_ARM_LPAE
#घोषणा __pgd_alloc()	kदो_स्मृति_array(PTRS_PER_PGD, माप(pgd_t), GFP_KERNEL)
#घोषणा __pgd_मुक्त(pgd)	kमुक्त(pgd)
#अन्यथा
#घोषणा __pgd_alloc()	(pgd_t *)__get_मुक्त_pages(GFP_KERNEL, 2)
#घोषणा __pgd_मुक्त(pgd)	मुक्त_pages((अचिन्हित दीर्घ)pgd, 2)
#पूर्ण_अगर

/*
 * need to get a 16k page क्रम level 1
 */
pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *new_pgd, *init_pgd;
	p4d_t *new_p4d, *init_p4d;
	pud_t *new_pud, *init_pud;
	pmd_t *new_pmd, *init_pmd;
	pte_t *new_pte, *init_pte;

	new_pgd = __pgd_alloc();
	अगर (!new_pgd)
		जाओ no_pgd;

	स_रखो(new_pgd, 0, USER_PTRS_PER_PGD * माप(pgd_t));

	/*
	 * Copy over the kernel and IO PGD entries
	 */
	init_pgd = pgd_offset_k(0);
	स_नकल(new_pgd + USER_PTRS_PER_PGD, init_pgd + USER_PTRS_PER_PGD,
		       (PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));

	clean_dcache_area(new_pgd, PTRS_PER_PGD * माप(pgd_t));

#अगर_घोषित CONFIG_ARM_LPAE
	/*
	 * Allocate PMD table क्रम modules and pkmap mappings.
	 */
	new_p4d = p4d_alloc(mm, new_pgd + pgd_index(MODULES_VADDR),
			    MODULES_VADDR);
	अगर (!new_p4d)
		जाओ no_p4d;

	new_pud = pud_alloc(mm, new_p4d, MODULES_VADDR);
	अगर (!new_pud)
		जाओ no_pud;

	new_pmd = pmd_alloc(mm, new_pud, 0);
	अगर (!new_pmd)
		जाओ no_pmd;
#अगर_घोषित CONFIG_KASAN
	/*
	 * Copy PMD table क्रम KASAN shaकरोw mappings.
	 */
	init_pgd = pgd_offset_k(TASK_SIZE);
	init_p4d = p4d_offset(init_pgd, TASK_SIZE);
	init_pud = pud_offset(init_p4d, TASK_SIZE);
	init_pmd = pmd_offset(init_pud, TASK_SIZE);
	new_pmd = pmd_offset(new_pud, TASK_SIZE);
	स_नकल(new_pmd, init_pmd,
	       (pmd_index(MODULES_VADDR) - pmd_index(TASK_SIZE))
	       * माप(pmd_t));
	clean_dcache_area(new_pmd, PTRS_PER_PMD * माप(pmd_t));
#पूर्ण_अगर /* CONFIG_KASAN */
#पूर्ण_अगर /* CONFIG_LPAE */

	अगर (!vectors_high()) अणु
		/*
		 * On ARM, first page must always be allocated since it
		 * contains the machine vectors. The vectors are always high
		 * with LPAE.
		 */
		new_p4d = p4d_alloc(mm, new_pgd, 0);
		अगर (!new_p4d)
			जाओ no_p4d;

		new_pud = pud_alloc(mm, new_p4d, 0);
		अगर (!new_pud)
			जाओ no_pud;

		new_pmd = pmd_alloc(mm, new_pud, 0);
		अगर (!new_pmd)
			जाओ no_pmd;

		new_pte = pte_alloc_map(mm, new_pmd, 0);
		अगर (!new_pte)
			जाओ no_pte;

#अगर_अघोषित CONFIG_ARM_LPAE
		/*
		 * Modअगरy the PTE poपूर्णांकer to have the correct करोमुख्य.  This
		 * needs to be the vectors करोमुख्य to aव्योम the low vectors
		 * being unmapped.
		 */
		pmd_val(*new_pmd) &= ~PMD_DOMAIN_MASK;
		pmd_val(*new_pmd) |= PMD_DOMAIN(DOMAIN_VECTORS);
#पूर्ण_अगर

		init_p4d = p4d_offset(init_pgd, 0);
		init_pud = pud_offset(init_p4d, 0);
		init_pmd = pmd_offset(init_pud, 0);
		init_pte = pte_offset_map(init_pmd, 0);
		set_pte_ext(new_pte + 0, init_pte[0], 0);
		set_pte_ext(new_pte + 1, init_pte[1], 0);
		pte_unmap(init_pte);
		pte_unmap(new_pte);
	पूर्ण

	वापस new_pgd;

no_pte:
	pmd_मुक्त(mm, new_pmd);
	mm_dec_nr_pmds(mm);
no_pmd:
	pud_मुक्त(mm, new_pud);
no_pud:
	p4d_मुक्त(mm, new_p4d);
no_p4d:
	__pgd_मुक्त(new_pgd);
no_pgd:
	वापस शून्य;
पूर्ण

व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd_base)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pgtable_t pte;

	अगर (!pgd_base)
		वापस;

	pgd = pgd_base + pgd_index(0);
	अगर (pgd_none_or_clear_bad(pgd))
		जाओ no_pgd;

	p4d = p4d_offset(pgd, 0);
	अगर (p4d_none_or_clear_bad(p4d))
		जाओ no_p4d;

	pud = pud_offset(p4d, 0);
	अगर (pud_none_or_clear_bad(pud))
		जाओ no_pud;

	pmd = pmd_offset(pud, 0);
	अगर (pmd_none_or_clear_bad(pmd))
		जाओ no_pmd;

	pte = pmd_pgtable(*pmd);
	pmd_clear(pmd);
	pte_मुक्त(mm, pte);
	mm_dec_nr_ptes(mm);
no_pmd:
	pud_clear(pud);
	pmd_मुक्त(mm, pmd);
	mm_dec_nr_pmds(mm);
no_pud:
	p4d_clear(p4d);
	pud_मुक्त(mm, pud);
no_p4d:
	pgd_clear(pgd);
	p4d_मुक्त(mm, p4d);
no_pgd:
#अगर_घोषित CONFIG_ARM_LPAE
	/*
	 * Free modules/pkmap or identity pmd tables.
	 */
	क्रम (pgd = pgd_base; pgd < pgd_base + PTRS_PER_PGD; pgd++) अणु
		अगर (pgd_none_or_clear_bad(pgd))
			जारी;
		अगर (pgd_val(*pgd) & L_PGD_SWAPPER)
			जारी;
		p4d = p4d_offset(pgd, 0);
		अगर (p4d_none_or_clear_bad(p4d))
			जारी;
		pud = pud_offset(p4d, 0);
		अगर (pud_none_or_clear_bad(pud))
			जारी;
		pmd = pmd_offset(pud, 0);
		pud_clear(pud);
		pmd_मुक्त(mm, pmd);
		mm_dec_nr_pmds(mm);
		p4d_clear(p4d);
		pud_मुक्त(mm, pud);
		mm_dec_nr_puds(mm);
		pgd_clear(pgd);
		p4d_मुक्त(mm, p4d);
	पूर्ण
#पूर्ण_अगर
	__pgd_मुक्त(pgd_base);
पूर्ण
