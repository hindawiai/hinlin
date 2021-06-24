<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/smp.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>

अचिन्हित दीर्घ highstart_pfn, highend_pfn;

व्योम kmap_flush_tlb(अचिन्हित दीर्घ addr)
अणु
	flush_tlb_one(addr);
पूर्ण
EXPORT_SYMBOL(kmap_flush_tlb);

व्योम __init kmap_init(व्योम)
अणु
	अचिन्हित दीर्घ vaddr;
	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *pte;

	vaddr = PKMAP_BASE;
	fixrange_init(vaddr, vaddr + PAGE_SIZE*LAST_PKMAP, swapper_pg_dir);

	pgd = swapper_pg_dir + pgd_index(vaddr);
	pud = (pud_t *)pgd;
	pmd = pmd_offset(pud, vaddr);
	pte = pte_offset_kernel(pmd, vaddr);
	pkmap_page_table = pte;
पूर्ण
