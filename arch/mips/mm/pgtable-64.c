<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999, 2000 by Silicon Graphics
 * Copyright (C) 2003 by Ralf Baechle
 */
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>

व्योम pgd_init(अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ *p, *end;
	अचिन्हित दीर्घ entry;

#अगर !defined(__PAGETABLE_PUD_FOLDED)
	entry = (अचिन्हित दीर्घ)invalid_pud_table;
#या_अगर !defined(__PAGETABLE_PMD_FOLDED)
	entry = (अचिन्हित दीर्घ)invalid_pmd_table;
#अन्यथा
	entry = (अचिन्हित दीर्घ)invalid_pte_table;
#पूर्ण_अगर

	p = (अचिन्हित दीर्घ *) page;
	end = p + PTRS_PER_PGD;

	करो अणु
		p[0] = entry;
		p[1] = entry;
		p[2] = entry;
		p[3] = entry;
		p[4] = entry;
		p += 8;
		p[-3] = entry;
		p[-2] = entry;
		p[-1] = entry;
	पूर्ण जबतक (p != end);
पूर्ण

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
व्योम pmd_init(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pagetable)
अणु
	अचिन्हित दीर्घ *p, *end;

	p = (अचिन्हित दीर्घ *) addr;
	end = p + PTRS_PER_PMD;

	करो अणु
		p[0] = pagetable;
		p[1] = pagetable;
		p[2] = pagetable;
		p[3] = pagetable;
		p[4] = pagetable;
		p += 8;
		p[-3] = pagetable;
		p[-2] = pagetable;
		p[-1] = pagetable;
	पूर्ण जबतक (p != end);
पूर्ण
EXPORT_SYMBOL_GPL(pmd_init);
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
व्योम pud_init(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pagetable)
अणु
	अचिन्हित दीर्घ *p, *end;

	p = (अचिन्हित दीर्घ *)addr;
	end = p + PTRS_PER_PUD;

	करो अणु
		p[0] = pagetable;
		p[1] = pagetable;
		p[2] = pagetable;
		p[3] = pagetable;
		p[4] = pagetable;
		p += 8;
		p[-3] = pagetable;
		p[-2] = pagetable;
		p[-1] = pagetable;
	पूर्ण जबतक (p != end);
पूर्ण
#पूर्ण_अगर

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

व्योम __init pagetable_init(व्योम)
अणु
	अचिन्हित दीर्घ vaddr;
	pgd_t *pgd_base;

	/* Initialize the entire pgd.  */
	pgd_init((अचिन्हित दीर्घ)swapper_pg_dir);
#अगर_अघोषित __PAGETABLE_PUD_FOLDED
	pud_init((अचिन्हित दीर्घ)invalid_pud_table, (अचिन्हित दीर्घ)invalid_pmd_table);
#पूर्ण_अगर
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pmd_init((अचिन्हित दीर्घ)invalid_pmd_table, (अचिन्हित दीर्घ)invalid_pte_table);
#पूर्ण_अगर
	pgd_base = swapper_pg_dir;
	/*
	 * Fixed mappings:
	 */
	vaddr = __fix_to_virt(__end_of_fixed_addresses - 1) & PMD_MASK;
	fixrange_init(vaddr, vaddr + FIXADDR_SIZE, pgd_base);
पूर्ण
