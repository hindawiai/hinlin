<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/init_task.h>

#घोषणा __HAVE_ARCH_PGD_FREE
#समावेश <यंत्र/pgभाग.स>

#घोषणा FIRST_KERNEL_PGD_NR	(USER_PTRS_PER_PGD)

/*
 * need to get a page क्रम level 1
 */

pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *new_pgd, *init_pgd;
	पूर्णांक i;

	new_pgd = (pgd_t *) __get_मुक्त_pages(GFP_KERNEL, 0);
	अगर (!new_pgd)
		वापस शून्य;
	क्रम (i = 0; i < PTRS_PER_PGD; i++) अणु
		(*new_pgd) = 1;
		new_pgd++;
	पूर्ण
	new_pgd -= PTRS_PER_PGD;

	init_pgd = pgd_offset_k(0);

	स_नकल(new_pgd + FIRST_KERNEL_PGD_NR, init_pgd + FIRST_KERNEL_PGD_NR,
	       (PTRS_PER_PGD - FIRST_KERNEL_PGD_NR) * माप(pgd_t));

	cpu_dcache_wb_range((अचिन्हित दीर्घ)new_pgd,
			    (अचिन्हित दीर्घ)new_pgd +
			    PTRS_PER_PGD * माप(pgd_t));
	inc_lruvec_page_state(virt_to_page((अचिन्हित दीर्घ *)new_pgd),
			      NR_PAGETABLE);

	वापस new_pgd;
पूर्ण

व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t * pgd)
अणु
	pmd_t *pmd;
	काष्ठा page *pte;

	अगर (!pgd)
		वापस;

	pmd = (pmd_t *) pgd;
	अगर (pmd_none(*pmd))
		जाओ मुक्त;
	अगर (pmd_bad(*pmd)) अणु
		pmd_ERROR(*pmd);
		pmd_clear(pmd);
		जाओ मुक्त;
	पूर्ण

	pte = pmd_page(*pmd);
	pmd_clear(pmd);
	dec_lruvec_page_state(virt_to_page((अचिन्हित दीर्घ *)pgd), NR_PAGETABLE);
	pte_मुक्त(mm, pte);
	mm_dec_nr_ptes(mm);
	pmd_मुक्त(mm, pmd);
मुक्त:
	मुक्त_pages((अचिन्हित दीर्घ)pgd, 0);
पूर्ण

/*
 * In order to soft-boot, we need to insert a 1:1 mapping in place of
 * the user-mode pages.  This will then ensure that we have predictable
 * results when turning the mmu off
 */
व्योम setup_mm_क्रम_reboot(अक्षर mode)
अणु
	अचिन्हित दीर्घ pmdval;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	पूर्णांक i;

	अगर (current->mm && current->mm->pgd)
		pgd = current->mm->pgd;
	अन्यथा
		pgd = init_mm.pgd;

	क्रम (i = 0; i < USER_PTRS_PER_PGD; i++) अणु
		pmdval = (i << PGसूची_SHIFT);
		p4d = p4d_offset(pgd, i << PGसूची_SHIFT);
		pud = pud_offset(p4d, i << PGसूची_SHIFT);
		pmd = pmd_offset(pud + i, i << PGसूची_SHIFT);
		set_pmd(pmd, __pmd(pmdval));
	पूर्ण
पूर्ण
