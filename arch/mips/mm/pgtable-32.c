<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 by Ralf Baechle
 */
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>

व्योम pgd_init(अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *) page;
	पूर्णांक i;

	क्रम (i = 0; i < USER_PTRS_PER_PGD; i+=8) अणु
		p[i + 0] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 1] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 2] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 3] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 4] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 5] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 6] = (अचिन्हित दीर्घ) invalid_pte_table;
		p[i + 7] = (अचिन्हित दीर्घ) invalid_pte_table;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE)
pmd_t mk_pmd(काष्ठा page *page, pgprot_t prot)
अणु
	pmd_t pmd;

	pmd_val(pmd) = (page_to_pfn(page) << _PFN_SHIFT) | pgprot_val(prot);

	वापस pmd;
पूर्ण


व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		pmd_t *pmdp, pmd_t pmd)
अणु
	*pmdp = pmd;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_TRANSPARENT_HUGEPAGE) */

व्योम __init pagetable_init(व्योम)
अणु
	अचिन्हित दीर्घ vaddr;
	pgd_t *pgd_base;
#अगर_घोषित CONFIG_HIGHMEM
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
#पूर्ण_अगर

	/* Initialize the entire pgd.  */
	pgd_init((अचिन्हित दीर्घ)swapper_pg_dir);
	pgd_init((अचिन्हित दीर्घ)swapper_pg_dir
		 + माप(pgd_t) * USER_PTRS_PER_PGD);

	pgd_base = swapper_pg_dir;

	/*
	 * Fixed mappings:
	 */
	vaddr = __fix_to_virt(__end_of_fixed_addresses - 1);
	fixrange_init(vaddr & PMD_MASK, vaddr + FIXADDR_SIZE, pgd_base);

#अगर_घोषित CONFIG_HIGHMEM
	/*
	 * Permanent kmaps:
	 */
	vaddr = PKMAP_BASE;
	fixrange_init(vaddr & PMD_MASK, vaddr + PAGE_SIZE*LAST_PKMAP, pgd_base);

	pgd = swapper_pg_dir + pgd_index(vaddr);
	p4d = p4d_offset(pgd, vaddr);
	pud = pud_offset(p4d, vaddr);
	pmd = pmd_offset(pud, vaddr);
	pte = pte_offset_kernel(pmd, vaddr);
	pkmap_page_table = pte;
#पूर्ण_अगर
पूर्ण
