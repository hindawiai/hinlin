<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/bug.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memblock.h>
#समावेश <linux/swap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pfn.h>
#समावेश <linux/initrd.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cacheflush.h>

#घोषणा PTRS_KERN_TABLE \
		((PTRS_PER_PGD - USER_PTRS_PER_PGD) * PTRS_PER_PTE)

pgd_t swapper_pg_dir[PTRS_PER_PGD] __page_aligned_bss;
pte_t invalid_pte_table[PTRS_PER_PTE] __page_aligned_bss;
pte_t kernel_pte_tables[PTRS_KERN_TABLE] __page_aligned_bss;

EXPORT_SYMBOL(invalid_pte_table);
अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)]
						__page_aligned_bss;
EXPORT_SYMBOL(empty_zero_page);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
अटल व्योम __init setup_initrd(व्योम)
अणु
	अचिन्हित दीर्घ size;

	अगर (initrd_start >= initrd_end) अणु
		pr_err("initrd not found or empty");
		जाओ disable;
	पूर्ण

	अगर (__pa(initrd_end) > PFN_PHYS(max_low_pfn)) अणु
		pr_err("initrd extends beyond end of memory");
		जाओ disable;
	पूर्ण

	size = initrd_end - initrd_start;

	अगर (memblock_is_region_reserved(__pa(initrd_start), size)) अणु
		pr_err("INITRD: 0x%08lx+0x%08lx overlaps in-use memory region",
		       __pa(initrd_start), size);
		जाओ disable;
	पूर्ण

	memblock_reserve(__pa(initrd_start), size);

	pr_info("Initial ramdisk at: 0x%p (%lu bytes)\n",
		(व्योम *)(initrd_start), size);

	initrd_below_start_ok = 1;

	वापस;

disable:
	initrd_start = initrd_end = 0;

	pr_err(" - disabling initrd\n");
पूर्ण
#पूर्ण_अगर

व्योम __init mem_init(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	अचिन्हित दीर्घ पंचांगp;

	set_max_mapnr(highend_pfn - ARCH_PFN_OFFSET);
#अन्यथा
	set_max_mapnr(max_low_pfn - ARCH_PFN_OFFSET);
#पूर्ण_अगर
	high_memory = (व्योम *) __va(max_low_pfn << PAGE_SHIFT);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	setup_initrd();
#पूर्ण_अगर

	memblock_मुक्त_all();

#अगर_घोषित CONFIG_HIGHMEM
	क्रम (पंचांगp = highstart_pfn; पंचांगp < highend_pfn; पंचांगp++) अणु
		काष्ठा page *page = pfn_to_page(पंचांगp);

		/* FIXME not sure about */
		अगर (!memblock_is_reserved(पंचांगp << PAGE_SHIFT))
			मुक्त_highmem_page(page);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
	मुक्त_iniपंचांगem_शेष(-1);
पूर्ण

व्योम pgd_init(अचिन्हित दीर्घ *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PGD; i++)
		p[i] = __pa(invalid_pte_table);

	flush_tlb_all();
	local_icache_inv_all(शून्य);
पूर्ण

व्योम __init mmu_init(अचिन्हित दीर्घ min_pfn, अचिन्हित दीर्घ max_pfn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < USER_PTRS_PER_PGD; i++)
		swapper_pg_dir[i].pgd = __pa(invalid_pte_table);

	क्रम (i = USER_PTRS_PER_PGD; i < PTRS_PER_PGD; i++)
		swapper_pg_dir[i].pgd =
			__pa(kernel_pte_tables + (PTRS_PER_PTE * (i - USER_PTRS_PER_PGD)));

	क्रम (i = 0; i < PTRS_KERN_TABLE; i++)
		set_pte(&kernel_pte_tables[i], __pte(_PAGE_GLOBAL));

	क्रम (i = min_pfn; i < max_pfn; i++)
		set_pte(&kernel_pte_tables[i - PFN_DOWN(va_pa_offset)], pfn_pte(i, PAGE_KERNEL));

	flush_tlb_all();
	local_icache_inv_all(शून्य);

	/* Setup page mask to 4k */
	ग_लिखो_mmu_pagemask(0);

	setup_pgd(swapper_pg_dir, 0);
पूर्ण

व्योम __init fixrange_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			pgd_t *pgd_base)
अणु
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	पूर्णांक i, j, k;
	अचिन्हित दीर्घ vaddr;

	vaddr = start;
	i = pgd_index(vaddr);
	j = pud_index(vaddr);
	k = pmd_index(vaddr);
	pgd = pgd_base + i;

	क्रम ( ; (i < PTRS_PER_PGD) && (vaddr != end); pgd++, i++) अणु
		pud = (pud_t *)pgd;
		क्रम ( ; (j < PTRS_PER_PUD) && (vaddr != end); pud++, j++) अणु
			pmd = (pmd_t *)pud;
			क्रम (; (k < PTRS_PER_PMD) && (vaddr != end); pmd++, k++) अणु
				अगर (pmd_none(*pmd)) अणु
					pte = (pte_t *) memblock_alloc_low(PAGE_SIZE, PAGE_SIZE);
					अगर (!pte)
						panic("%s: Failed to allocate %lu bytes align=%lx\n",
						      __func__, PAGE_SIZE,
						      PAGE_SIZE);

					set_pmd(pmd, __pmd(__pa(pte)));
					BUG_ON(pte != pte_offset_kernel(pmd, 0));
				पूर्ण
				vaddr += PMD_SIZE;
			पूर्ण
			k = 0;
		पूर्ण
		j = 0;
	पूर्ण
पूर्ण

व्योम __init fixaddr_init(व्योम)
अणु
	अचिन्हित दीर्घ vaddr;

	vaddr = __fix_to_virt(__end_of_fixed_addresses - 1) & PMD_MASK;
	fixrange_init(vaddr, vaddr + PMD_SIZE, swapper_pg_dir);
पूर्ण
