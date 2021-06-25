<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Andes Technology Corporation

#समावेश <linux/pfn.h>
#समावेश <linux/init_task.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/pgभाग.स>

बाह्य pgd_t early_pg_dir[PTRS_PER_PGD];
यंत्रlinkage व्योम __init kasan_early_init(व्योम)
अणु
	uपूर्णांकptr_t i;
	pgd_t *pgd = early_pg_dir + pgd_index(KASAN_SHADOW_START);

	क्रम (i = 0; i < PTRS_PER_PTE; ++i)
		set_pte(kasan_early_shaकरोw_pte + i,
			mk_pte(virt_to_page(kasan_early_shaकरोw_page),
			       PAGE_KERNEL));

	क्रम (i = 0; i < PTRS_PER_PMD; ++i)
		set_pmd(kasan_early_shaकरोw_pmd + i,
			pfn_pmd(PFN_DOWN
				(__pa((uपूर्णांकptr_t) kasan_early_shaकरोw_pte)),
				__pgprot(_PAGE_TABLE)));

	क्रम (i = KASAN_SHADOW_START; i < KASAN_SHADOW_END;
	     i += PGसूची_SIZE, ++pgd)
		set_pgd(pgd,
			pfn_pgd(PFN_DOWN
				(__pa(((uपूर्णांकptr_t) kasan_early_shaकरोw_pmd))),
				__pgprot(_PAGE_TABLE)));

	/* init क्रम swapper_pg_dir */
	pgd = pgd_offset_k(KASAN_SHADOW_START);

	क्रम (i = KASAN_SHADOW_START; i < KASAN_SHADOW_END;
	     i += PGसूची_SIZE, ++pgd)
		set_pgd(pgd,
			pfn_pgd(PFN_DOWN
				(__pa(((uपूर्णांकptr_t) kasan_early_shaकरोw_pmd))),
				__pgprot(_PAGE_TABLE)));

	local_flush_tlb_all();
पूर्ण

अटल व्योम __init kasan_populate_pte(pmd_t *pmd, अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ end)
अणु
	phys_addr_t phys_addr;
	pte_t *ptep, *base_pte;

	अगर (pmd_none(*pmd))
		base_pte = memblock_alloc(PTRS_PER_PTE * माप(pte_t), PAGE_SIZE);
	अन्यथा
		base_pte = (pte_t *)pmd_page_vaddr(*pmd);

	ptep = base_pte + pte_index(vaddr);

	करो अणु
		अगर (pte_none(*ptep)) अणु
			phys_addr = memblock_phys_alloc(PAGE_SIZE, PAGE_SIZE);
			set_pte(ptep, pfn_pte(PFN_DOWN(phys_addr), PAGE_KERNEL));
		पूर्ण
	पूर्ण जबतक (ptep++, vaddr += PAGE_SIZE, vaddr != end);

	set_pmd(pmd, pfn_pmd(PFN_DOWN(__pa(base_pte)), PAGE_TABLE));
पूर्ण

अटल व्योम __init kasan_populate_pmd(pgd_t *pgd, अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ end)
अणु
	phys_addr_t phys_addr;
	pmd_t *pmdp, *base_pmd;
	अचिन्हित दीर्घ next;

	base_pmd = (pmd_t *)pgd_page_vaddr(*pgd);
	अगर (base_pmd == lm_alias(kasan_early_shaकरोw_pmd))
		base_pmd = memblock_alloc(PTRS_PER_PMD * माप(pmd_t), PAGE_SIZE);

	pmdp = base_pmd + pmd_index(vaddr);

	करो अणु
		next = pmd_addr_end(vaddr, end);

		अगर (pmd_none(*pmdp) && IS_ALIGNED(vaddr, PMD_SIZE) && (next - vaddr) >= PMD_SIZE) अणु
			phys_addr = memblock_phys_alloc(PMD_SIZE, PMD_SIZE);
			अगर (phys_addr) अणु
				set_pmd(pmdp, pfn_pmd(PFN_DOWN(phys_addr), PAGE_KERNEL));
				जारी;
			पूर्ण
		पूर्ण

		kasan_populate_pte(pmdp, vaddr, next);
	पूर्ण जबतक (pmdp++, vaddr = next, vaddr != end);

	/*
	 * Wait क्रम the whole PGD to be populated beक्रमe setting the PGD in
	 * the page table, otherwise, अगर we did set the PGD beक्रमe populating
	 * it entirely, memblock could allocate a page at a physical address
	 * where KASAN is not populated yet and then we'd get a page fault.
	 */
	set_pgd(pgd, pfn_pgd(PFN_DOWN(__pa(base_pmd)), PAGE_TABLE));
पूर्ण

अटल व्योम __init kasan_populate_pgd(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ end)
अणु
	phys_addr_t phys_addr;
	pgd_t *pgdp = pgd_offset_k(vaddr);
	अचिन्हित दीर्घ next;

	करो अणु
		next = pgd_addr_end(vaddr, end);

		/*
		 * pgdp can't be none since kasan_early_init initialized all KASAN
		 * shaकरोw region with kasan_early_shaकरोw_pmd: अगर this is stillthe हाल,
		 * that means we can try to allocate a hugepage as a replacement.
		 */
		अगर (pgd_page_vaddr(*pgdp) == (अचिन्हित दीर्घ)lm_alias(kasan_early_shaकरोw_pmd) &&
		    IS_ALIGNED(vaddr, PGसूची_SIZE) && (next - vaddr) >= PGसूची_SIZE) अणु
			phys_addr = memblock_phys_alloc(PGसूची_SIZE, PGसूची_SIZE);
			अगर (phys_addr) अणु
				set_pgd(pgdp, pfn_pgd(PFN_DOWN(phys_addr), PAGE_KERNEL));
				जारी;
			पूर्ण
		पूर्ण

		kasan_populate_pmd(pgdp, vaddr, next);
	पूर्ण जबतक (pgdp++, vaddr = next, vaddr != end);
पूर्ण

अटल व्योम __init kasan_populate(व्योम *start, व्योम *end)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)start & PAGE_MASK;
	अचिन्हित दीर्घ vend = PAGE_ALIGN((अचिन्हित दीर्घ)end);

	kasan_populate_pgd(vaddr, vend);

	local_flush_tlb_all();
	स_रखो(start, KASAN_SHADOW_INIT, end - start);
पूर्ण

अटल व्योम __init kasan_shallow_populate_pgd(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	व्योम *p;
	pgd_t *pgd_k = pgd_offset_k(vaddr);

	करो अणु
		next = pgd_addr_end(vaddr, end);
		अगर (pgd_page_vaddr(*pgd_k) == (अचिन्हित दीर्घ)lm_alias(kasan_early_shaकरोw_pmd)) अणु
			p = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
			set_pgd(pgd_k, pfn_pgd(PFN_DOWN(__pa(p)), PAGE_TABLE));
		पूर्ण
	पूर्ण जबतक (pgd_k++, vaddr = next, vaddr != end);
पूर्ण

अटल व्योम __init kasan_shallow_populate(व्योम *start, व्योम *end)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)start & PAGE_MASK;
	अचिन्हित दीर्घ vend = PAGE_ALIGN((अचिन्हित दीर्घ)end);

	kasan_shallow_populate_pgd(vaddr, vend);
	local_flush_tlb_all();
पूर्ण

व्योम __init kasan_init(व्योम)
अणु
	phys_addr_t p_start, p_end;
	u64 i;

	/*
	 * Populate all kernel भव address space with kasan_early_shaकरोw_page
	 * except क्रम the linear mapping and the modules/kernel/BPF mapping.
	 */
	kasan_populate_early_shaकरोw((व्योम *)KASAN_SHADOW_START,
				    (व्योम *)kasan_mem_to_shaकरोw((व्योम *)
								VMEMMAP_END));
	अगर (IS_ENABLED(CONFIG_KASAN_VMALLOC))
		kasan_shallow_populate(
			(व्योम *)kasan_mem_to_shaकरोw((व्योम *)VMALLOC_START),
			(व्योम *)kasan_mem_to_shaकरोw((व्योम *)VMALLOC_END));
	अन्यथा
		kasan_populate_early_shaकरोw(
			(व्योम *)kasan_mem_to_shaकरोw((व्योम *)VMALLOC_START),
			(व्योम *)kasan_mem_to_shaकरोw((व्योम *)VMALLOC_END));

	/* Populate the linear mapping */
	क्रम_each_mem_range(i, &p_start, &p_end) अणु
		व्योम *start = (व्योम *)__va(p_start);
		व्योम *end = (व्योम *)__va(p_end);

		अगर (start >= end)
			अवरोध;

		kasan_populate(kasan_mem_to_shaकरोw(start), kasan_mem_to_shaकरोw(end));
	पूर्ण

	/* Populate kernel, BPF, modules mapping */
	kasan_populate(kasan_mem_to_shaकरोw((स्थिर व्योम *)MODULES_VADDR),
		       kasan_mem_to_shaकरोw((स्थिर व्योम *)MODULES_VADDR + SZ_2G));

	क्रम (i = 0; i < PTRS_PER_PTE; i++)
		set_pte(&kasan_early_shaकरोw_pte[i],
			mk_pte(virt_to_page(kasan_early_shaकरोw_page),
			       __pgprot(_PAGE_PRESENT | _PAGE_READ |
					_PAGE_ACCESSED)));

	स_रखो(kasan_early_shaकरोw_page, KASAN_SHADOW_INIT, PAGE_SIZE);
	init_task.kasan_depth = 0;
पूर्ण
