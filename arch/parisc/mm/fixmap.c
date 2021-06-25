<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fixmaps क्रम parisc
 *
 * Copyright (c) 2019 Sven Schnelle <svens@stackframe.org>
 */

#समावेश <linux/kprobes.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fixmap.h>

व्योम notrace set_fixmap(क्रमागत fixed_addresses idx, phys_addr_t phys)
अणु
	अचिन्हित दीर्घ vaddr = __fix_to_virt(idx);
	pgd_t *pgd = pgd_offset_k(vaddr);
	p4d_t *p4d = p4d_offset(pgd, vaddr);
	pud_t *pud = pud_offset(p4d, vaddr);
	pmd_t *pmd = pmd_offset(pud, vaddr);
	pte_t *pte;

	अगर (pmd_none(*pmd))
		pmd = pmd_alloc(शून्य, pud, vaddr);

	pte = pte_offset_kernel(pmd, vaddr);
	अगर (pte_none(*pte))
		pte = pte_alloc_kernel(pmd, vaddr);

	set_pte_at(&init_mm, vaddr, pte, __mk_pte(phys, PAGE_KERNEL_RWX));
	flush_tlb_kernel_range(vaddr, vaddr + PAGE_SIZE);
पूर्ण

व्योम notrace clear_fixmap(क्रमागत fixed_addresses idx)
अणु
	अचिन्हित दीर्घ vaddr = __fix_to_virt(idx);
	pte_t *pte = virt_to_kpte(vaddr);

	अगर (WARN_ON(pte_none(*pte)))
		वापस;

	pte_clear(&init_mm, vaddr, pte);

	flush_tlb_kernel_range(vaddr, vaddr + PAGE_SIZE);
पूर्ण
