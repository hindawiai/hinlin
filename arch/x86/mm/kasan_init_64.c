<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा DISABLE_BRANCH_PROFILING
#घोषणा pr_fmt(fmt) "kasan: " fmt

/* cpu_feature_enabled() cannot be used this early */
#घोषणा USE_EARLY_PGTABLE_L5

#समावेश <linux/memblock.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/e820/types.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/cpu_entry_area.h>

बाह्य काष्ठा range pfn_mapped[E820_MAX_ENTRIES];

अटल p4d_t पंचांगp_p4d_table[MAX_PTRS_PER_P4D] __initdata __aligned(PAGE_SIZE);

अटल __init व्योम *early_alloc(माप_प्रकार size, पूर्णांक nid, bool should_panic)
अणु
	व्योम *ptr = memblock_alloc_try_nid(size, size,
			__pa(MAX_DMA_ADDRESS), MEMBLOCK_ALLOC_ACCESSIBLE, nid);

	अगर (!ptr && should_panic)
		panic("%pS: Failed to allocate page, nid=%d from=%lx\n",
		      (व्योम *)_RET_IP_, nid, __pa(MAX_DMA_ADDRESS));

	वापस ptr;
पूर्ण

अटल व्योम __init kasan_populate_pmd(pmd_t *pmd, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, पूर्णांक nid)
अणु
	pte_t *pte;

	अगर (pmd_none(*pmd)) अणु
		व्योम *p;

		अगर (boot_cpu_has(X86_FEATURE_PSE) &&
		    ((end - addr) == PMD_SIZE) &&
		    IS_ALIGNED(addr, PMD_SIZE)) अणु
			p = early_alloc(PMD_SIZE, nid, false);
			अगर (p && pmd_set_huge(pmd, __pa(p), PAGE_KERNEL))
				वापस;
			अन्यथा अगर (p)
				memblock_मुक्त(__pa(p), PMD_SIZE);
		पूर्ण

		p = early_alloc(PAGE_SIZE, nid, true);
		pmd_populate_kernel(&init_mm, pmd, p);
	पूर्ण

	pte = pte_offset_kernel(pmd, addr);
	करो अणु
		pte_t entry;
		व्योम *p;

		अगर (!pte_none(*pte))
			जारी;

		p = early_alloc(PAGE_SIZE, nid, true);
		entry = pfn_pte(PFN_DOWN(__pa(p)), PAGE_KERNEL);
		set_pte_at(&init_mm, addr, pte, entry);
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
पूर्ण

अटल व्योम __init kasan_populate_pud(pud_t *pud, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, पूर्णांक nid)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;

	अगर (pud_none(*pud)) अणु
		व्योम *p;

		अगर (boot_cpu_has(X86_FEATURE_GBPAGES) &&
		    ((end - addr) == PUD_SIZE) &&
		    IS_ALIGNED(addr, PUD_SIZE)) अणु
			p = early_alloc(PUD_SIZE, nid, false);
			अगर (p && pud_set_huge(pud, __pa(p), PAGE_KERNEL))
				वापस;
			अन्यथा अगर (p)
				memblock_मुक्त(__pa(p), PUD_SIZE);
		पूर्ण

		p = early_alloc(PAGE_SIZE, nid, true);
		pud_populate(&init_mm, pud, p);
	पूर्ण

	pmd = pmd_offset(pud, addr);
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (!pmd_large(*pmd))
			kasan_populate_pmd(pmd, addr, next, nid);
	पूर्ण जबतक (pmd++, addr = next, addr != end);
पूर्ण

अटल व्योम __init kasan_populate_p4d(p4d_t *p4d, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, पूर्णांक nid)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;

	अगर (p4d_none(*p4d)) अणु
		व्योम *p = early_alloc(PAGE_SIZE, nid, true);

		p4d_populate(&init_mm, p4d, p);
	पूर्ण

	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (!pud_large(*pud))
			kasan_populate_pud(pud, addr, next, nid);
	पूर्ण जबतक (pud++, addr = next, addr != end);
पूर्ण

अटल व्योम __init kasan_populate_pgd(pgd_t *pgd, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ end, पूर्णांक nid)
अणु
	व्योम *p;
	p4d_t *p4d;
	अचिन्हित दीर्घ next;

	अगर (pgd_none(*pgd)) अणु
		p = early_alloc(PAGE_SIZE, nid, true);
		pgd_populate(&init_mm, pgd, p);
	पूर्ण

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		kasan_populate_p4d(p4d, addr, next, nid);
	पूर्ण जबतक (p4d++, addr = next, addr != end);
पूर्ण

अटल व्योम __init kasan_populate_shaकरोw(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
					 पूर्णांक nid)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ next;

	addr = addr & PAGE_MASK;
	end = round_up(end, PAGE_SIZE);
	pgd = pgd_offset_k(addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		kasan_populate_pgd(pgd, addr, next, nid);
	पूर्ण जबतक (pgd++, addr = next, addr != end);
पूर्ण

अटल व्योम __init map_range(काष्ठा range *range)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;

	start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(pfn_to_kaddr(range->start));
	end = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(pfn_to_kaddr(range->end));

	kasan_populate_shaकरोw(start, end, early_pfn_to_nid(range->start));
पूर्ण

अटल व्योम __init clear_pgds(अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end)
अणु
	pgd_t *pgd;
	/* See comment in kasan_init() */
	अचिन्हित दीर्घ pgd_end = end & PGसूची_MASK;

	क्रम (; start < pgd_end; start += PGसूची_SIZE) अणु
		pgd = pgd_offset_k(start);
		/*
		 * With folded p4d, pgd_clear() is nop, use p4d_clear()
		 * instead.
		 */
		अगर (pgtable_l5_enabled())
			pgd_clear(pgd);
		अन्यथा
			p4d_clear(p4d_offset(pgd, start));
	पूर्ण

	pgd = pgd_offset_k(start);
	क्रम (; start < end; start += P4D_SIZE)
		p4d_clear(p4d_offset(pgd, start));
पूर्ण

अटल अंतरभूत p4d_t *early_p4d_offset(pgd_t *pgd, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ p4d;

	अगर (!pgtable_l5_enabled())
		वापस (p4d_t *)pgd;

	p4d = pgd_val(*pgd) & PTE_PFN_MASK;
	p4d += __START_KERNEL_map - phys_base;
	वापस (p4d_t *)p4d + p4d_index(addr);
पूर्ण

अटल व्योम __init kasan_early_p4d_populate(pgd_t *pgd,
		अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end)
अणु
	pgd_t pgd_entry;
	p4d_t *p4d, p4d_entry;
	अचिन्हित दीर्घ next;

	अगर (pgd_none(*pgd)) अणु
		pgd_entry = __pgd(_KERNPG_TABLE |
					__pa_nodebug(kasan_early_shaकरोw_p4d));
		set_pgd(pgd, pgd_entry);
	पूर्ण

	p4d = early_p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);

		अगर (!p4d_none(*p4d))
			जारी;

		p4d_entry = __p4d(_KERNPG_TABLE |
					__pa_nodebug(kasan_early_shaकरोw_pud));
		set_p4d(p4d, p4d_entry);
	पूर्ण जबतक (p4d++, addr = next, addr != end && p4d_none(*p4d));
पूर्ण

अटल व्योम __init kasan_map_early_shaकरोw(pgd_t *pgd)
अणु
	/* See comment in kasan_init() */
	अचिन्हित दीर्घ addr = KASAN_SHADOW_START & PGसूची_MASK;
	अचिन्हित दीर्घ end = KASAN_SHADOW_END;
	अचिन्हित दीर्घ next;

	pgd += pgd_index(addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		kasan_early_p4d_populate(pgd, addr, next);
	पूर्ण जबतक (pgd++, addr = next, addr != end);
पूर्ण

अटल व्योम __init kasan_shallow_populate_p4ds(pgd_t *pgd,
					       अचिन्हित दीर्घ addr,
					       अचिन्हित दीर्घ end)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	व्योम *p;

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);

		अगर (p4d_none(*p4d)) अणु
			p = early_alloc(PAGE_SIZE, NUMA_NO_NODE, true);
			p4d_populate(&init_mm, p4d, p);
		पूर्ण
	पूर्ण जबतक (p4d++, addr = next, addr != end);
पूर्ण

अटल व्योम __init kasan_shallow_populate_pgds(व्योम *start, व्योम *end)
अणु
	अचिन्हित दीर्घ addr, next;
	pgd_t *pgd;
	व्योम *p;

	addr = (अचिन्हित दीर्घ)start;
	pgd = pgd_offset_k(addr);
	करो अणु
		next = pgd_addr_end(addr, (अचिन्हित दीर्घ)end);

		अगर (pgd_none(*pgd)) अणु
			p = early_alloc(PAGE_SIZE, NUMA_NO_NODE, true);
			pgd_populate(&init_mm, pgd, p);
		पूर्ण

		/*
		 * we need to populate p4ds to be synced when running in
		 * four level mode - see sync_global_pgds_l4()
		 */
		kasan_shallow_populate_p4ds(pgd, addr, next);
	पूर्ण जबतक (pgd++, addr = next, addr != (अचिन्हित दीर्घ)end);
पूर्ण

व्योम __init kasan_early_init(व्योम)
अणु
	पूर्णांक i;
	pteval_t pte_val = __pa_nodebug(kasan_early_shaकरोw_page) |
				__PAGE_KERNEL | _PAGE_ENC;
	pmdval_t pmd_val = __pa_nodebug(kasan_early_shaकरोw_pte) | _KERNPG_TABLE;
	pudval_t pud_val = __pa_nodebug(kasan_early_shaकरोw_pmd) | _KERNPG_TABLE;
	p4dval_t p4d_val = __pa_nodebug(kasan_early_shaकरोw_pud) | _KERNPG_TABLE;

	/* Mask out unsupported __PAGE_KERNEL bits: */
	pte_val &= __शेष_kernel_pte_mask;
	pmd_val &= __शेष_kernel_pte_mask;
	pud_val &= __शेष_kernel_pte_mask;
	p4d_val &= __शेष_kernel_pte_mask;

	क्रम (i = 0; i < PTRS_PER_PTE; i++)
		kasan_early_shaकरोw_pte[i] = __pte(pte_val);

	क्रम (i = 0; i < PTRS_PER_PMD; i++)
		kasan_early_shaकरोw_pmd[i] = __pmd(pmd_val);

	क्रम (i = 0; i < PTRS_PER_PUD; i++)
		kasan_early_shaकरोw_pud[i] = __pud(pud_val);

	क्रम (i = 0; pgtable_l5_enabled() && i < PTRS_PER_P4D; i++)
		kasan_early_shaकरोw_p4d[i] = __p4d(p4d_val);

	kasan_map_early_shaकरोw(early_top_pgt);
	kasan_map_early_shaकरोw(init_top_pgt);
पूर्ण

व्योम __init kasan_init(व्योम)
अणु
	पूर्णांक i;
	व्योम *shaकरोw_cpu_entry_begin, *shaकरोw_cpu_entry_end;

	स_नकल(early_top_pgt, init_top_pgt, माप(early_top_pgt));

	/*
	 * We use the same shaकरोw offset क्रम 4- and 5-level paging to
	 * facilitate boot-समय चयनing between paging modes.
	 * As result in 5-level paging mode KASAN_SHADOW_START and
	 * KASAN_SHADOW_END are not aligned to PGD boundary.
	 *
	 * KASAN_SHADOW_START करोesn't share PGD with anything अन्यथा.
	 * We claim whole PGD entry to make things easier.
	 *
	 * KASAN_SHADOW_END lands in the last PGD entry and it collides with
	 * bunch of things like kernel code, modules, EFI mapping, etc.
	 * We need to take extra steps to not overग_लिखो them.
	 */
	अगर (pgtable_l5_enabled()) अणु
		व्योम *ptr;

		ptr = (व्योम *)pgd_page_vaddr(*pgd_offset_k(KASAN_SHADOW_END));
		स_नकल(पंचांगp_p4d_table, (व्योम *)ptr, माप(पंचांगp_p4d_table));
		set_pgd(&early_top_pgt[pgd_index(KASAN_SHADOW_END)],
				__pgd(__pa(पंचांगp_p4d_table) | _KERNPG_TABLE));
	पूर्ण

	load_cr3(early_top_pgt);
	__flush_tlb_all();

	clear_pgds(KASAN_SHADOW_START & PGसूची_MASK, KASAN_SHADOW_END);

	kasan_populate_early_shaकरोw((व्योम *)(KASAN_SHADOW_START & PGसूची_MASK),
			kasan_mem_to_shaकरोw((व्योम *)PAGE_OFFSET));

	क्रम (i = 0; i < E820_MAX_ENTRIES; i++) अणु
		अगर (pfn_mapped[i].end == 0)
			अवरोध;

		map_range(&pfn_mapped[i]);
	पूर्ण

	shaकरोw_cpu_entry_begin = (व्योम *)CPU_ENTRY_AREA_BASE;
	shaकरोw_cpu_entry_begin = kasan_mem_to_shaकरोw(shaकरोw_cpu_entry_begin);
	shaकरोw_cpu_entry_begin = (व्योम *)round_करोwn(
			(अचिन्हित दीर्घ)shaकरोw_cpu_entry_begin, PAGE_SIZE);

	shaकरोw_cpu_entry_end = (व्योम *)(CPU_ENTRY_AREA_BASE +
					CPU_ENTRY_AREA_MAP_SIZE);
	shaकरोw_cpu_entry_end = kasan_mem_to_shaकरोw(shaकरोw_cpu_entry_end);
	shaकरोw_cpu_entry_end = (व्योम *)round_up(
			(अचिन्हित दीर्घ)shaकरोw_cpu_entry_end, PAGE_SIZE);

	kasan_populate_early_shaकरोw(
		kasan_mem_to_shaकरोw((व्योम *)PAGE_OFFSET + MAXMEM),
		kasan_mem_to_shaकरोw((व्योम *)VMALLOC_START));

	/*
	 * If we're in full vmalloc mode, don't back vदो_स्मृति space with early
	 * shaकरोw pages. Instead, prepopulate pgds/p4ds so they are synced to
	 * the global table and we can populate the lower levels on demand.
	 */
	अगर (IS_ENABLED(CONFIG_KASAN_VMALLOC))
		kasan_shallow_populate_pgds(
			kasan_mem_to_shaकरोw((व्योम *)VMALLOC_START),
			kasan_mem_to_shaकरोw((व्योम *)VMALLOC_END));
	अन्यथा
		kasan_populate_early_shaकरोw(
			kasan_mem_to_shaकरोw((व्योम *)VMALLOC_START),
			kasan_mem_to_shaकरोw((व्योम *)VMALLOC_END));

	kasan_populate_early_shaकरोw(
		kasan_mem_to_shaकरोw((व्योम *)VMALLOC_END + 1),
		shaकरोw_cpu_entry_begin);

	kasan_populate_shaकरोw((अचिन्हित दीर्घ)shaकरोw_cpu_entry_begin,
			      (अचिन्हित दीर्घ)shaकरोw_cpu_entry_end, 0);

	kasan_populate_early_shaकरोw(shaकरोw_cpu_entry_end,
			kasan_mem_to_shaकरोw((व्योम *)__START_KERNEL_map));

	kasan_populate_shaकरोw((अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(_stext),
			      (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(_end),
			      early_pfn_to_nid(__pa(_stext)));

	kasan_populate_early_shaकरोw(kasan_mem_to_shaकरोw((व्योम *)MODULES_END),
					(व्योम *)KASAN_SHADOW_END);

	load_cr3(init_top_pgt);
	__flush_tlb_all();

	/*
	 * kasan_early_shaकरोw_page has been used as early shaकरोw memory, thus
	 * it may contain some garbage. Now we can clear and ग_लिखो protect it,
	 * since after the TLB flush no one should ग_लिखो to it.
	 */
	स_रखो(kasan_early_shaकरोw_page, 0, PAGE_SIZE);
	क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
		pte_t pte;
		pgprot_t prot;

		prot = __pgprot(__PAGE_KERNEL_RO | _PAGE_ENC);
		pgprot_val(prot) &= __शेष_kernel_pte_mask;

		pte = __pte(__pa(kasan_early_shaकरोw_page) | pgprot_val(prot));
		set_pte(&kasan_early_shaकरोw_pte[i], pte);
	पूर्ण
	/* Flush TLBs again to be sure that ग_लिखो protection applied. */
	__flush_tlb_all();

	init_task.kasan_depth = 0;
	pr_info("KernelAddressSanitizer initialized\n");
पूर्ण
