<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/mm/hugetlbpage.c
 *
 * SuperH HugeTLB page support.
 *
 * Cloned from sparc64 by Paul Mundt.
 *
 * Copyright (C) 2002, 2003 David S. Miller (davem@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sysctl.h>

#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>

pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = शून्य;

	pgd = pgd_offset(mm, addr);
	अगर (pgd) अणु
		p4d = p4d_alloc(mm, pgd, addr);
		अगर (p4d) अणु
			pud = pud_alloc(mm, p4d, addr);
			अगर (pud) अणु
				pmd = pmd_alloc(mm, pud, addr);
				अगर (pmd)
					pte = pte_alloc_map(mm, pmd, addr);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस pte;
पूर्ण

pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm,
		       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = शून्य;

	pgd = pgd_offset(mm, addr);
	अगर (pgd) अणु
		p4d = p4d_offset(pgd, addr);
		अगर (p4d) अणु
			pud = pud_offset(p4d, addr);
			अगर (pud) अणु
				pmd = pmd_offset(pud, addr);
				अगर (pmd)
					pte = pte_offset_map(pmd, addr);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस pte;
पूर्ण

पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस 0;
पूर्ण
