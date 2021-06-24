<शैली गुरु>
/*
 * MIPS Huge TLB Page Support क्रम Kernel.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2002, Rohit Seth <rohit.seth@पूर्णांकel.com>
 * Copyright 2005, Embedded Alley Solutions, Inc.
 * Matt Porter <mporter@embeddedalley.com>
 * Copyright (C) 2008, 2009 Cavium Networks, Inc.
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/err.h>
#समावेश <linux/sysctl.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>

pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pte_t *pte = शून्य;

	pgd = pgd_offset(mm, addr);
	p4d = p4d_alloc(mm, pgd, addr);
	pud = pud_alloc(mm, p4d, addr);
	अगर (pud)
		pte = (pte_t *)pmd_alloc(mm, pud, addr);

	वापस pte;
पूर्ण

pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		       अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd = शून्य;

	pgd = pgd_offset(mm, addr);
	अगर (pgd_present(*pgd)) अणु
		p4d = p4d_offset(pgd, addr);
		अगर (p4d_present(*p4d)) अणु
			pud = pud_offset(p4d, addr);
			अगर (pud_present(*pud))
				pmd = pmd_offset(pud, addr);
		पूर्ण
	पूर्ण
	वापस (pte_t *) pmd;
पूर्ण

पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & _PAGE_HUGE) != 0;
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस (pud_val(pud) & _PAGE_HUGE) != 0;
पूर्ण
