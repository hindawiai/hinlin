<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hibernation support specअगरic क्रम i386 - temporary page tables
 *
 * Copyright (c) 2006 Rafael J. Wysocki <rjw@sisk.pl>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/suspend.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/suspend.h>

/* Poपूर्णांकer to the temporary resume page tables */
pgd_t *resume_pg_dir;

/* The following three functions are based on the analogous code in
 * arch/x86/mm/init_32.c
 */

/*
 * Create a middle page table on a resume-safe page and put a poपूर्णांकer to it in
 * the given global directory entry.  This only वापसs the gd entry
 * in non-PAE compilation mode, since the middle layer is folded.
 */
अटल pmd_t *resume_one_md_table_init(pgd_t *pgd)
अणु
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd_table;

#अगर_घोषित CONFIG_X86_PAE
	pmd_table = (pmd_t *)get_safe_page(GFP_ATOMIC);
	अगर (!pmd_table)
		वापस शून्य;

	set_pgd(pgd, __pgd(__pa(pmd_table) | _PAGE_PRESENT));
	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);

	BUG_ON(pmd_table != pmd_offset(pud, 0));
#अन्यथा
	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);
	pmd_table = pmd_offset(pud, 0);
#पूर्ण_अगर

	वापस pmd_table;
पूर्ण

/*
 * Create a page table on a resume-safe page and place a poपूर्णांकer to it in
 * a middle page directory entry.
 */
अटल pte_t *resume_one_page_table_init(pmd_t *pmd)
अणु
	अगर (pmd_none(*pmd)) अणु
		pte_t *page_table = (pte_t *)get_safe_page(GFP_ATOMIC);
		अगर (!page_table)
			वापस शून्य;

		set_pmd(pmd, __pmd(__pa(page_table) | _PAGE_TABLE));

		BUG_ON(page_table != pte_offset_kernel(pmd, 0));

		वापस page_table;
	पूर्ण

	वापस pte_offset_kernel(pmd, 0);
पूर्ण

/*
 * This maps the physical memory to kernel भव address space, a total
 * of max_low_pfn pages, by creating page tables starting from address
 * PAGE_OFFSET.  The page tables are allocated out of resume-safe pages.
 */
अटल पूर्णांक resume_physical_mapping_init(pgd_t *pgd_base)
अणु
	अचिन्हित दीर्घ pfn;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;
	पूर्णांक pgd_idx, pmd_idx;

	pgd_idx = pgd_index(PAGE_OFFSET);
	pgd = pgd_base + pgd_idx;
	pfn = 0;

	क्रम (; pgd_idx < PTRS_PER_PGD; pgd++, pgd_idx++) अणु
		pmd = resume_one_md_table_init(pgd);
		अगर (!pmd)
			वापस -ENOMEM;

		अगर (pfn >= max_low_pfn)
			जारी;

		क्रम (pmd_idx = 0; pmd_idx < PTRS_PER_PMD; pmd++, pmd_idx++) अणु
			अगर (pfn >= max_low_pfn)
				अवरोध;

			/* Map with big pages अगर possible, otherwise create
			 * normal page tables.
			 * NOTE: We can mark everything as executable here
			 */
			अगर (boot_cpu_has(X86_FEATURE_PSE)) अणु
				set_pmd(pmd, pfn_pmd(pfn, PAGE_KERNEL_LARGE_EXEC));
				pfn += PTRS_PER_PTE;
			पूर्ण अन्यथा अणु
				pte_t *max_pte;

				pte = resume_one_page_table_init(pmd);
				अगर (!pte)
					वापस -ENOMEM;

				max_pte = pte + PTRS_PER_PTE;
				क्रम (; pte < max_pte; pte++, pfn++) अणु
					अगर (pfn >= max_low_pfn)
						अवरोध;

					set_pte(pte, pfn_pte(pfn, PAGE_KERNEL_EXEC));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम resume_init_first_level_page_table(pgd_t *pg_dir)
अणु
#अगर_घोषित CONFIG_X86_PAE
	पूर्णांक i;

	/* Init entries of the first-level page table to the zero page */
	क्रम (i = 0; i < PTRS_PER_PGD; i++)
		set_pgd(pg_dir + i,
			__pgd(__pa(empty_zero_page) | _PAGE_PRESENT));
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक set_up_temporary_text_mapping(pgd_t *pgd_base)
अणु
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_base + pgd_index(restore_jump_address);

	pmd = resume_one_md_table_init(pgd);
	अगर (!pmd)
		वापस -ENOMEM;

	अगर (boot_cpu_has(X86_FEATURE_PSE)) अणु
		set_pmd(pmd + pmd_index(restore_jump_address),
		__pmd((jump_address_phys & PMD_MASK) | pgprot_val(PAGE_KERNEL_LARGE_EXEC)));
	पूर्ण अन्यथा अणु
		pte = resume_one_page_table_init(pmd);
		अगर (!pte)
			वापस -ENOMEM;
		set_pte(pte + pte_index(restore_jump_address),
		__pte((jump_address_phys & PAGE_MASK) | pgprot_val(PAGE_KERNEL_EXEC)));
	पूर्ण

	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक swsusp_arch_resume(व्योम)
अणु
	पूर्णांक error;

	resume_pg_dir = (pgd_t *)get_safe_page(GFP_ATOMIC);
	अगर (!resume_pg_dir)
		वापस -ENOMEM;

	resume_init_first_level_page_table(resume_pg_dir);

	error = set_up_temporary_text_mapping(resume_pg_dir);
	अगर (error)
		वापस error;

	error = resume_physical_mapping_init(resume_pg_dir);
	अगर (error)
		वापस error;

	temp_pgt = __pa(resume_pg_dir);

	error = relocate_restore_code();
	अगर (error)
		वापस error;

	/* We have got enough memory and from now on we cannot recover */
	restore_image();
	वापस 0;
पूर्ण
