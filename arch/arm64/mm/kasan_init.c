<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains kasan initialization code क्रम ARM64.
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 */

#घोषणा pr_fmt(fmt) "kasan: " fmt
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/memblock.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/kernel-pgtable.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlbflush.h>

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)

अटल pgd_t पंचांगp_pg_dir[PTRS_PER_PGD] __initdata __aligned(PGD_SIZE);

/*
 * The p*d_populate functions call virt_to_phys implicitly so they can't be used
 * directly on kernel symbols (bm_p*d). All the early functions are called too
 * early to use lm_alias so __p*d_populate functions must be used to populate
 * with the physical address from __pa_symbol.
 */

अटल phys_addr_t __init kasan_alloc_zeroed_page(पूर्णांक node)
अणु
	व्योम *p = memblock_alloc_try_nid(PAGE_SIZE, PAGE_SIZE,
					      __pa(MAX_DMA_ADDRESS),
					      MEMBLOCK_ALLOC_KASAN, node);
	अगर (!p)
		panic("%s: Failed to allocate %lu bytes align=0x%lx nid=%d from=%llx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE, node,
		      __pa(MAX_DMA_ADDRESS));

	वापस __pa(p);
पूर्ण

अटल phys_addr_t __init kasan_alloc_raw_page(पूर्णांक node)
अणु
	व्योम *p = memblock_alloc_try_nid_raw(PAGE_SIZE, PAGE_SIZE,
						__pa(MAX_DMA_ADDRESS),
						MEMBLOCK_ALLOC_KASAN, node);
	अगर (!p)
		panic("%s: Failed to allocate %lu bytes align=0x%lx nid=%d from=%llx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE, node,
		      __pa(MAX_DMA_ADDRESS));

	वापस __pa(p);
पूर्ण

अटल pte_t *__init kasan_pte_offset(pmd_t *pmdp, अचिन्हित दीर्घ addr, पूर्णांक node,
				      bool early)
अणु
	अगर (pmd_none(READ_ONCE(*pmdp))) अणु
		phys_addr_t pte_phys = early ?
				__pa_symbol(kasan_early_shaकरोw_pte)
					: kasan_alloc_zeroed_page(node);
		__pmd_populate(pmdp, pte_phys, PMD_TYPE_TABLE);
	पूर्ण

	वापस early ? pte_offset_kimg(pmdp, addr)
		     : pte_offset_kernel(pmdp, addr);
पूर्ण

अटल pmd_t *__init kasan_pmd_offset(pud_t *pudp, अचिन्हित दीर्घ addr, पूर्णांक node,
				      bool early)
अणु
	अगर (pud_none(READ_ONCE(*pudp))) अणु
		phys_addr_t pmd_phys = early ?
				__pa_symbol(kasan_early_shaकरोw_pmd)
					: kasan_alloc_zeroed_page(node);
		__pud_populate(pudp, pmd_phys, PUD_TYPE_TABLE);
	पूर्ण

	वापस early ? pmd_offset_kimg(pudp, addr) : pmd_offset(pudp, addr);
पूर्ण

अटल pud_t *__init kasan_pud_offset(p4d_t *p4dp, अचिन्हित दीर्घ addr, पूर्णांक node,
				      bool early)
अणु
	अगर (p4d_none(READ_ONCE(*p4dp))) अणु
		phys_addr_t pud_phys = early ?
				__pa_symbol(kasan_early_shaकरोw_pud)
					: kasan_alloc_zeroed_page(node);
		__p4d_populate(p4dp, pud_phys, P4D_TYPE_TABLE);
	पूर्ण

	वापस early ? pud_offset_kimg(p4dp, addr) : pud_offset(p4dp, addr);
पूर्ण

अटल व्योम __init kasan_pte_populate(pmd_t *pmdp, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, पूर्णांक node, bool early)
अणु
	अचिन्हित दीर्घ next;
	pte_t *ptep = kasan_pte_offset(pmdp, addr, node, early);

	करो अणु
		phys_addr_t page_phys = early ?
				__pa_symbol(kasan_early_shaकरोw_page)
					: kasan_alloc_raw_page(node);
		अगर (!early)
			स_रखो(__va(page_phys), KASAN_SHADOW_INIT, PAGE_SIZE);
		next = addr + PAGE_SIZE;
		set_pte(ptep, pfn_pte(__phys_to_pfn(page_phys), PAGE_KERNEL));
	पूर्ण जबतक (ptep++, addr = next, addr != end && pte_none(READ_ONCE(*ptep)));
पूर्ण

अटल व्योम __init kasan_pmd_populate(pud_t *pudp, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, पूर्णांक node, bool early)
अणु
	अचिन्हित दीर्घ next;
	pmd_t *pmdp = kasan_pmd_offset(pudp, addr, node, early);

	करो अणु
		next = pmd_addr_end(addr, end);
		kasan_pte_populate(pmdp, addr, next, node, early);
	पूर्ण जबतक (pmdp++, addr = next, addr != end && pmd_none(READ_ONCE(*pmdp)));
पूर्ण

अटल व्योम __init kasan_pud_populate(p4d_t *p4dp, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, पूर्णांक node, bool early)
अणु
	अचिन्हित दीर्घ next;
	pud_t *pudp = kasan_pud_offset(p4dp, addr, node, early);

	करो अणु
		next = pud_addr_end(addr, end);
		kasan_pmd_populate(pudp, addr, next, node, early);
	पूर्ण जबतक (pudp++, addr = next, addr != end && pud_none(READ_ONCE(*pudp)));
पूर्ण

अटल व्योम __init kasan_p4d_populate(pgd_t *pgdp, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, पूर्णांक node, bool early)
अणु
	अचिन्हित दीर्घ next;
	p4d_t *p4dp = p4d_offset(pgdp, addr);

	करो अणु
		next = p4d_addr_end(addr, end);
		kasan_pud_populate(p4dp, addr, next, node, early);
	पूर्ण जबतक (p4dp++, addr = next, addr != end);
पूर्ण

अटल व्योम __init kasan_pgd_populate(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				      पूर्णांक node, bool early)
अणु
	अचिन्हित दीर्घ next;
	pgd_t *pgdp;

	pgdp = pgd_offset_k(addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		kasan_p4d_populate(pgdp, addr, next, node, early);
	पूर्ण जबतक (pgdp++, addr = next, addr != end);
पूर्ण

/* The early shaकरोw maps everything to a single page of zeroes */
यंत्रlinkage व्योम __init kasan_early_init(व्योम)
अणु
	BUILD_BUG_ON(KASAN_SHADOW_OFFSET !=
		KASAN_SHADOW_END - (1UL << (64 - KASAN_SHADOW_SCALE_SHIFT)));
	BUILD_BUG_ON(!IS_ALIGNED(_KASAN_SHADOW_START(VA_BITS), PGसूची_SIZE));
	BUILD_BUG_ON(!IS_ALIGNED(_KASAN_SHADOW_START(VA_BITS_MIN), PGसूची_SIZE));
	BUILD_BUG_ON(!IS_ALIGNED(KASAN_SHADOW_END, PGसूची_SIZE));
	kasan_pgd_populate(KASAN_SHADOW_START, KASAN_SHADOW_END, NUMA_NO_NODE,
			   true);
पूर्ण

/* Set up full kasan mappings, ensuring that the mapped pages are zeroed */
अटल व्योम __init kasan_map_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				      पूर्णांक node)
अणु
	kasan_pgd_populate(start & PAGE_MASK, PAGE_ALIGN(end), node, false);
पूर्ण

/*
 * Copy the current shaकरोw region पूर्णांकo a new pgdir.
 */
व्योम __init kasan_copy_shaकरोw(pgd_t *pgdir)
अणु
	pgd_t *pgdp, *pgdp_new, *pgdp_end;

	pgdp = pgd_offset_k(KASAN_SHADOW_START);
	pgdp_end = pgd_offset_k(KASAN_SHADOW_END);
	pgdp_new = pgd_offset_pgd(pgdir, KASAN_SHADOW_START);
	करो अणु
		set_pgd(pgdp_new, READ_ONCE(*pgdp));
	पूर्ण जबतक (pgdp++, pgdp_new++, pgdp != pgdp_end);
पूर्ण

अटल व्योम __init clear_pgds(अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end)
अणु
	/*
	 * Remove references to kasan page tables from
	 * swapper_pg_dir. pgd_clear() can't be used
	 * here because it's nop on 2,3-level pagetable setups
	 */
	क्रम (; start < end; start += PGसूची_SIZE)
		set_pgd(pgd_offset_k(start), __pgd(0));
पूर्ण

अटल व्योम __init kasan_init_shaकरोw(व्योम)
अणु
	u64 kimg_shaकरोw_start, kimg_shaकरोw_end;
	u64 mod_shaकरोw_start, mod_shaकरोw_end;
	u64 vदो_स्मृति_shaकरोw_end;
	phys_addr_t pa_start, pa_end;
	u64 i;

	kimg_shaकरोw_start = (u64)kasan_mem_to_shaकरोw(KERNEL_START) & PAGE_MASK;
	kimg_shaकरोw_end = PAGE_ALIGN((u64)kasan_mem_to_shaकरोw(KERNEL_END));

	mod_shaकरोw_start = (u64)kasan_mem_to_shaकरोw((व्योम *)MODULES_VADDR);
	mod_shaकरोw_end = (u64)kasan_mem_to_shaकरोw((व्योम *)MODULES_END);

	vदो_स्मृति_shaकरोw_end = (u64)kasan_mem_to_shaकरोw((व्योम *)VMALLOC_END);

	/*
	 * We are going to perक्रमm proper setup of shaकरोw memory.
	 * At first we should unmap early shaकरोw (clear_pgds() call below).
	 * However, instrumented code couldn't execute without shaकरोw memory.
	 * पंचांगp_pg_dir used to keep early shaकरोw mapped until full shaकरोw
	 * setup will be finished.
	 */
	स_नकल(पंचांगp_pg_dir, swapper_pg_dir, माप(पंचांगp_pg_dir));
	dsb(ishst);
	cpu_replace_ttbr1(lm_alias(पंचांगp_pg_dir));

	clear_pgds(KASAN_SHADOW_START, KASAN_SHADOW_END);

	kasan_map_populate(kimg_shaकरोw_start, kimg_shaकरोw_end,
			   early_pfn_to_nid(virt_to_pfn(lm_alias(KERNEL_START))));

	kasan_populate_early_shaकरोw(kasan_mem_to_shaकरोw((व्योम *)PAGE_END),
				   (व्योम *)mod_shaकरोw_start);

	अगर (IS_ENABLED(CONFIG_KASAN_VMALLOC)) अणु
		BUILD_BUG_ON(VMALLOC_START != MODULES_END);
		kasan_populate_early_shaकरोw((व्योम *)vदो_स्मृति_shaकरोw_end,
					    (व्योम *)KASAN_SHADOW_END);
	पूर्ण अन्यथा अणु
		kasan_populate_early_shaकरोw((व्योम *)kimg_shaकरोw_end,
					    (व्योम *)KASAN_SHADOW_END);
		अगर (kimg_shaकरोw_start > mod_shaकरोw_end)
			kasan_populate_early_shaकरोw((व्योम *)mod_shaकरोw_end,
						    (व्योम *)kimg_shaकरोw_start);
	पूर्ण

	क्रम_each_mem_range(i, &pa_start, &pa_end) अणु
		व्योम *start = (व्योम *)__phys_to_virt(pa_start);
		व्योम *end = (व्योम *)__phys_to_virt(pa_end);

		अगर (start >= end)
			अवरोध;

		kasan_map_populate((अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(start),
				   (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(end),
				   early_pfn_to_nid(virt_to_pfn(start)));
	पूर्ण

	/*
	 * KAsan may reuse the contents of kasan_early_shaकरोw_pte directly,
	 * so we should make sure that it maps the zero page पढ़ो-only.
	 */
	क्रम (i = 0; i < PTRS_PER_PTE; i++)
		set_pte(&kasan_early_shaकरोw_pte[i],
			pfn_pte(sym_to_pfn(kasan_early_shaकरोw_page),
				PAGE_KERNEL_RO));

	स_रखो(kasan_early_shaकरोw_page, KASAN_SHADOW_INIT, PAGE_SIZE);
	cpu_replace_ttbr1(lm_alias(swapper_pg_dir));
पूर्ण

अटल व्योम __init kasan_init_depth(व्योम)
अणु
	init_task.kasan_depth = 0;
पूर्ण

व्योम __init kasan_init(व्योम)
अणु
	kasan_init_shaकरोw();
	kasan_init_depth();
#अगर defined(CONFIG_KASAN_GENERIC)
	/* CONFIG_KASAN_SW_TAGS also requires kasan_init_sw_tags(). */
	pr_info("KernelAddressSanitizer initialized\n");
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS */
