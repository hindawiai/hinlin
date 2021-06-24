<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 1995  Linus Torvalds
 *
 *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/swap.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/pci.h>
#समावेश <linux/pfn.h>
#समावेश <linux/poison.h>
#समावेश <linux/memblock.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/initrd.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/bios_ebda.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/olpc_ofw.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/page_types.h>
#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/init.h>
#समावेश <यंत्र/pgtable_areas.h>
#समावेश <यंत्र/numa.h>

#समावेश "mm_internal.h"

अचिन्हित दीर्घ highstart_pfn, highend_pfn;

bool __पढ़ो_mostly __vदो_स्मृति_start_set = false;

/*
 * Creates a middle page table and माला_दो a poपूर्णांकer to it in the
 * given global directory entry. This only वापसs the gd entry
 * in non-PAE compilation mode, since the middle layer is folded.
 */
अटल pmd_t * __init one_md_table_init(pgd_t *pgd)
अणु
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd_table;

#अगर_घोषित CONFIG_X86_PAE
	अगर (!(pgd_val(*pgd) & _PAGE_PRESENT)) अणु
		pmd_table = (pmd_t *)alloc_low_page();
		paravirt_alloc_pmd(&init_mm, __pa(pmd_table) >> PAGE_SHIFT);
		set_pgd(pgd, __pgd(__pa(pmd_table) | _PAGE_PRESENT));
		p4d = p4d_offset(pgd, 0);
		pud = pud_offset(p4d, 0);
		BUG_ON(pmd_table != pmd_offset(pud, 0));

		वापस pmd_table;
	पूर्ण
#पूर्ण_अगर
	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);
	pmd_table = pmd_offset(pud, 0);

	वापस pmd_table;
पूर्ण

/*
 * Create a page table and place a poपूर्णांकer to it in a middle page
 * directory entry:
 */
अटल pte_t * __init one_page_table_init(pmd_t *pmd)
अणु
	अगर (!(pmd_val(*pmd) & _PAGE_PRESENT)) अणु
		pte_t *page_table = (pte_t *)alloc_low_page();

		paravirt_alloc_pte(&init_mm, __pa(page_table) >> PAGE_SHIFT);
		set_pmd(pmd, __pmd(__pa(page_table) | _PAGE_TABLE));
		BUG_ON(page_table != pte_offset_kernel(pmd, 0));
	पूर्ण

	वापस pte_offset_kernel(pmd, 0);
पूर्ण

pmd_t * __init populate_extra_pmd(अचिन्हित दीर्घ vaddr)
अणु
	पूर्णांक pgd_idx = pgd_index(vaddr);
	पूर्णांक pmd_idx = pmd_index(vaddr);

	वापस one_md_table_init(swapper_pg_dir + pgd_idx) + pmd_idx;
पूर्ण

pte_t * __init populate_extra_pte(अचिन्हित दीर्घ vaddr)
अणु
	पूर्णांक pte_idx = pte_index(vaddr);
	pmd_t *pmd;

	pmd = populate_extra_pmd(vaddr);
	वापस one_page_table_init(pmd) + pte_idx;
पूर्ण

अटल अचिन्हित दीर्घ __init
page_table_range_init_count(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ count = 0;
#अगर_घोषित CONFIG_HIGHMEM
	पूर्णांक pmd_idx_kmap_begin = fix_to_virt(FIX_KMAP_END) >> PMD_SHIFT;
	पूर्णांक pmd_idx_kmap_end = fix_to_virt(FIX_KMAP_BEGIN) >> PMD_SHIFT;
	पूर्णांक pgd_idx, pmd_idx;
	अचिन्हित दीर्घ vaddr;

	अगर (pmd_idx_kmap_begin == pmd_idx_kmap_end)
		वापस 0;

	vaddr = start;
	pgd_idx = pgd_index(vaddr);
	pmd_idx = pmd_index(vaddr);

	क्रम ( ; (pgd_idx < PTRS_PER_PGD) && (vaddr != end); pgd_idx++) अणु
		क्रम (; (pmd_idx < PTRS_PER_PMD) && (vaddr != end);
							pmd_idx++) अणु
			अगर ((vaddr >> PMD_SHIFT) >= pmd_idx_kmap_begin &&
			    (vaddr >> PMD_SHIFT) <= pmd_idx_kmap_end)
				count++;
			vaddr += PMD_SIZE;
		पूर्ण
		pmd_idx = 0;
	पूर्ण
#पूर्ण_अगर
	वापस count;
पूर्ण

अटल pte_t *__init page_table_kmap_check(pte_t *pte, pmd_t *pmd,
					   अचिन्हित दीर्घ vaddr, pte_t *lastpte,
					   व्योम **adr)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	/*
	 * Something (early fixmap) may alपढ़ोy have put a pte
	 * page here, which causes the page table allocation
	 * to become nonlinear. Attempt to fix it, and अगर it
	 * is still nonlinear then we have to bug.
	 */
	पूर्णांक pmd_idx_kmap_begin = fix_to_virt(FIX_KMAP_END) >> PMD_SHIFT;
	पूर्णांक pmd_idx_kmap_end = fix_to_virt(FIX_KMAP_BEGIN) >> PMD_SHIFT;

	अगर (pmd_idx_kmap_begin != pmd_idx_kmap_end
	    && (vaddr >> PMD_SHIFT) >= pmd_idx_kmap_begin
	    && (vaddr >> PMD_SHIFT) <= pmd_idx_kmap_end) अणु
		pte_t *newpte;
		पूर्णांक i;

		BUG_ON(after_booपंचांगem);
		newpte = *adr;
		क्रम (i = 0; i < PTRS_PER_PTE; i++)
			set_pte(newpte + i, pte[i]);
		*adr = (व्योम *)(((अचिन्हित दीर्घ)(*adr)) + PAGE_SIZE);

		paravirt_alloc_pte(&init_mm, __pa(newpte) >> PAGE_SHIFT);
		set_pmd(pmd, __pmd(__pa(newpte)|_PAGE_TABLE));
		BUG_ON(newpte != pte_offset_kernel(pmd, 0));
		__flush_tlb_all();

		paravirt_release_pte(__pa(pte) >> PAGE_SHIFT);
		pte = newpte;
	पूर्ण
	BUG_ON(vaddr < fix_to_virt(FIX_KMAP_BEGIN - 1)
	       && vaddr > fix_to_virt(FIX_KMAP_END)
	       && lastpte && lastpte + PTRS_PER_PTE != pte);
#पूर्ण_अगर
	वापस pte;
पूर्ण

/*
 * This function initializes a certain range of kernel भव memory
 * with new booपंचांगem page tables, everywhere page tables are missing in
 * the given range.
 *
 * NOTE: The pagetables are allocated contiguous on the physical space
 * so we can cache the place of the first one and move around without
 * checking the pgd every समय.
 */
अटल व्योम __init
page_table_range_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, pgd_t *pgd_base)
अणु
	पूर्णांक pgd_idx, pmd_idx;
	अचिन्हित दीर्घ vaddr;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte = शून्य;
	अचिन्हित दीर्घ count = page_table_range_init_count(start, end);
	व्योम *adr = शून्य;

	अगर (count)
		adr = alloc_low_pages(count);

	vaddr = start;
	pgd_idx = pgd_index(vaddr);
	pmd_idx = pmd_index(vaddr);
	pgd = pgd_base + pgd_idx;

	क्रम ( ; (pgd_idx < PTRS_PER_PGD) && (vaddr != end); pgd++, pgd_idx++) अणु
		pmd = one_md_table_init(pgd);
		pmd = pmd + pmd_index(vaddr);
		क्रम (; (pmd_idx < PTRS_PER_PMD) && (vaddr != end);
							pmd++, pmd_idx++) अणु
			pte = page_table_kmap_check(one_page_table_init(pmd),
						    pmd, vaddr, pte, &adr);

			vaddr += PMD_SIZE;
		पूर्ण
		pmd_idx = 0;
	पूर्ण
पूर्ण

/*
 * The <linux/kallsyms.h> alपढ़ोy defines is_kernel_text,
 * using '__' prefix not to get in conflict.
 */
अटल अंतरभूत पूर्णांक __is_kernel_text(अचिन्हित दीर्घ addr)
अणु
	अगर (addr >= (अचिन्हित दीर्घ)_text && addr <= (अचिन्हित दीर्घ)__init_end)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * This maps the physical memory to kernel भव address space, a total
 * of max_low_pfn pages, by creating page tables starting from address
 * PAGE_OFFSET:
 */
अचिन्हित दीर्घ __init
kernel_physical_mapping_init(अचिन्हित दीर्घ start,
			     अचिन्हित दीर्घ end,
			     अचिन्हित दीर्घ page_size_mask,
			     pgprot_t prot)
अणु
	पूर्णांक use_pse = page_size_mask == (1<<PG_LEVEL_2M);
	अचिन्हित दीर्घ last_map_addr = end;
	अचिन्हित दीर्घ start_pfn, end_pfn;
	pgd_t *pgd_base = swapper_pg_dir;
	पूर्णांक pgd_idx, pmd_idx, pte_ofs;
	अचिन्हित दीर्घ pfn;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;
	अचिन्हित pages_2m, pages_4k;
	पूर्णांक mapping_iter;

	start_pfn = start >> PAGE_SHIFT;
	end_pfn = end >> PAGE_SHIFT;

	/*
	 * First iteration will setup identity mapping using large/small pages
	 * based on use_pse, with other attributes same as set by
	 * the early code in head_32.S
	 *
	 * Second iteration will setup the appropriate attributes (NX, GLOBAL..)
	 * as desired क्रम the kernel identity mapping.
	 *
	 * This two pass mechanism conक्रमms to the TLB app note which says:
	 *
	 *     "Software should not ग_लिखो to a paging-काष्ठाure entry in a way
	 *      that would change, क्रम any linear address, both the page size
	 *      and either the page frame or attributes."
	 */
	mapping_iter = 1;

	अगर (!boot_cpu_has(X86_FEATURE_PSE))
		use_pse = 0;

repeat:
	pages_2m = pages_4k = 0;
	pfn = start_pfn;
	pgd_idx = pgd_index((pfn<<PAGE_SHIFT) + PAGE_OFFSET);
	pgd = pgd_base + pgd_idx;
	क्रम (; pgd_idx < PTRS_PER_PGD; pgd++, pgd_idx++) अणु
		pmd = one_md_table_init(pgd);

		अगर (pfn >= end_pfn)
			जारी;
#अगर_घोषित CONFIG_X86_PAE
		pmd_idx = pmd_index((pfn<<PAGE_SHIFT) + PAGE_OFFSET);
		pmd += pmd_idx;
#अन्यथा
		pmd_idx = 0;
#पूर्ण_अगर
		क्रम (; pmd_idx < PTRS_PER_PMD && pfn < end_pfn;
		     pmd++, pmd_idx++) अणु
			अचिन्हित पूर्णांक addr = pfn * PAGE_SIZE + PAGE_OFFSET;

			/*
			 * Map with big pages अगर possible, otherwise
			 * create normal page tables:
			 */
			अगर (use_pse) अणु
				अचिन्हित पूर्णांक addr2;
				pgprot_t prot = PAGE_KERNEL_LARGE;
				/*
				 * first pass will use the same initial
				 * identity mapping attribute + _PAGE_PSE.
				 */
				pgprot_t init_prot =
					__pgprot(PTE_IDENT_ATTR |
						 _PAGE_PSE);

				pfn &= PMD_MASK >> PAGE_SHIFT;
				addr2 = (pfn + PTRS_PER_PTE-1) * PAGE_SIZE +
					PAGE_OFFSET + PAGE_SIZE-1;

				अगर (__is_kernel_text(addr) ||
				    __is_kernel_text(addr2))
					prot = PAGE_KERNEL_LARGE_EXEC;

				pages_2m++;
				अगर (mapping_iter == 1)
					set_pmd(pmd, pfn_pmd(pfn, init_prot));
				अन्यथा
					set_pmd(pmd, pfn_pmd(pfn, prot));

				pfn += PTRS_PER_PTE;
				जारी;
			पूर्ण
			pte = one_page_table_init(pmd);

			pte_ofs = pte_index((pfn<<PAGE_SHIFT) + PAGE_OFFSET);
			pte += pte_ofs;
			क्रम (; pte_ofs < PTRS_PER_PTE && pfn < end_pfn;
			     pte++, pfn++, pte_ofs++, addr += PAGE_SIZE) अणु
				pgprot_t prot = PAGE_KERNEL;
				/*
				 * first pass will use the same initial
				 * identity mapping attribute.
				 */
				pgprot_t init_prot = __pgprot(PTE_IDENT_ATTR);

				अगर (__is_kernel_text(addr))
					prot = PAGE_KERNEL_EXEC;

				pages_4k++;
				अगर (mapping_iter == 1) अणु
					set_pte(pte, pfn_pte(pfn, init_prot));
					last_map_addr = (pfn << PAGE_SHIFT) + PAGE_SIZE;
				पूर्ण अन्यथा
					set_pte(pte, pfn_pte(pfn, prot));
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (mapping_iter == 1) अणु
		/*
		 * update direct mapping page count only in the first
		 * iteration.
		 */
		update_page_count(PG_LEVEL_2M, pages_2m);
		update_page_count(PG_LEVEL_4K, pages_4k);

		/*
		 * local global flush tlb, which will flush the previous
		 * mappings present in both small and large page TLB's.
		 */
		__flush_tlb_all();

		/*
		 * Second iteration will set the actual desired PTE attributes.
		 */
		mapping_iter = 2;
		जाओ repeat;
	पूर्ण
	वापस last_map_addr;
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
अटल व्योम __init permanent_kmaps_init(pgd_t *pgd_base)
अणु
	अचिन्हित दीर्घ vaddr = PKMAP_BASE;

	page_table_range_init(vaddr, vaddr + PAGE_SIZE*LAST_PKMAP, pgd_base);

	pkmap_page_table = virt_to_kpte(vaddr);
पूर्ण

व्योम __init add_highpages_with_active_regions(पूर्णांक nid,
			 अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	phys_addr_t start, end;
	u64 i;

	क्रम_each_मुक्त_mem_range(i, nid, MEMBLOCK_NONE, &start, &end, शून्य) अणु
		अचिन्हित दीर्घ pfn = clamp_t(अचिन्हित दीर्घ, PFN_UP(start),
					    start_pfn, end_pfn);
		अचिन्हित दीर्घ e_pfn = clamp_t(अचिन्हित दीर्घ, PFN_DOWN(end),
					      start_pfn, end_pfn);
		क्रम ( ; pfn < e_pfn; pfn++)
			अगर (pfn_valid(pfn))
				मुक्त_highmem_page(pfn_to_page(pfn));
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम permanent_kmaps_init(pgd_t *pgd_base)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

व्योम __init sync_initial_page_table(व्योम)
अणु
	clone_pgd_range(initial_page_table + KERNEL_PGD_BOUNDARY,
			swapper_pg_dir     + KERNEL_PGD_BOUNDARY,
			KERNEL_PGD_PTRS);

	/*
	 * sync back low identity map too.  It is used क्रम example
	 * in the 32-bit EFI stub.
	 */
	clone_pgd_range(initial_page_table,
			swapper_pg_dir     + KERNEL_PGD_BOUNDARY,
			min(KERNEL_PGD_PTRS, KERNEL_PGD_BOUNDARY));
पूर्ण

व्योम __init native_pagetable_init(व्योम)
अणु
	अचिन्हित दीर्घ pfn, va;
	pgd_t *pgd, *base = swapper_pg_dir;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	/*
	 * Remove any mappings which extend past the end of physical
	 * memory from the boot समय page table.
	 * In भव address space, we should have at least two pages
	 * from VMALLOC_END to pkmap or fixmap according to VMALLOC_END
	 * definition. And max_low_pfn is set to VMALLOC_END physical
	 * address. If initial memory mapping is करोing right job, we
	 * should have pte used near max_low_pfn or one pmd is not present.
	 */
	क्रम (pfn = max_low_pfn; pfn < 1<<(32-PAGE_SHIFT); pfn++) अणु
		va = PAGE_OFFSET + (pfn<<PAGE_SHIFT);
		pgd = base + pgd_index(va);
		अगर (!pgd_present(*pgd))
			अवरोध;

		p4d = p4d_offset(pgd, va);
		pud = pud_offset(p4d, va);
		pmd = pmd_offset(pud, va);
		अगर (!pmd_present(*pmd))
			अवरोध;

		/* should not be large page here */
		अगर (pmd_large(*pmd)) अणु
			pr_warn("try to clear pte for ram above max_low_pfn: pfn: %lx pmd: %p pmd phys: %lx, but pmd is big page and is not using pte !\n",
				pfn, pmd, __pa(pmd));
			BUG_ON(1);
		पूर्ण

		pte = pte_offset_kernel(pmd, va);
		अगर (!pte_present(*pte))
			अवरोध;

		prपूर्णांकk(KERN_DEBUG "clearing pte for ram above max_low_pfn: pfn: %lx pmd: %p pmd phys: %lx pte: %p pte phys: %lx\n",
				pfn, pmd, __pa(pmd), pte, __pa(pte));
		pte_clear(शून्य, va, pte);
	पूर्ण
	paravirt_alloc_pmd(&init_mm, __pa(base) >> PAGE_SHIFT);
	paging_init();
पूर्ण

/*
 * Build a proper pagetable क्रम the kernel mappings.  Up until this
 * poपूर्णांक, we've been running on some set of pagetables स्थिरructed by
 * the boot process.
 *
 * If we're booting on native hardware, this will be a pagetable
 * स्थिरructed in arch/x86/kernel/head_32.S.  The root of the
 * pagetable will be swapper_pg_dir.
 *
 * If we're booting paraभवized under a hypervisor, then there are
 * more options: we may alपढ़ोy be running PAE, and the pagetable may
 * or may not be based in swapper_pg_dir.  In any हाल,
 * paravirt_pagetable_init() will set up swapper_pg_dir
 * appropriately क्रम the rest of the initialization to work.
 *
 * In general, pagetable_init() assumes that the pagetable may alपढ़ोy
 * be partially populated, and so it aव्योमs stomping on any existing
 * mappings.
 */
व्योम __init early_ioremap_page_table_range_init(व्योम)
अणु
	pgd_t *pgd_base = swapper_pg_dir;
	अचिन्हित दीर्घ vaddr, end;

	/*
	 * Fixed mappings, only the page table काष्ठाure has to be
	 * created - mappings will be set by set_fixmap():
	 */
	vaddr = __fix_to_virt(__end_of_fixed_addresses - 1) & PMD_MASK;
	end = (FIXADDR_TOP + PMD_SIZE - 1) & PMD_MASK;
	page_table_range_init(vaddr, end, pgd_base);
	early_ioremap_reset();
पूर्ण

अटल व्योम __init pagetable_init(व्योम)
अणु
	pgd_t *pgd_base = swapper_pg_dir;

	permanent_kmaps_init(pgd_base);
पूर्ण

#घोषणा DEFAULT_PTE_MASK ~(_PAGE_NX | _PAGE_GLOBAL)
/* Bits supported by the hardware: */
pteval_t __supported_pte_mask __पढ़ो_mostly = DEFAULT_PTE_MASK;
/* Bits allowed in normal kernel mappings: */
pteval_t __शेष_kernel_pte_mask __पढ़ो_mostly = DEFAULT_PTE_MASK;
EXPORT_SYMBOL_GPL(__supported_pte_mask);
/* Used in PAGE_KERNEL_* macros which are reasonably used out-of-tree: */
EXPORT_SYMBOL(__शेष_kernel_pte_mask);

/* user-defined highmem size */
अटल अचिन्हित पूर्णांक highmem_pages = -1;

/*
 * highmem=size क्रमces highmem to be exactly 'size' bytes.
 * This works even on boxes that have no highmem otherwise.
 * This also works to reduce highmem size on bigger boxes.
 */
अटल पूर्णांक __init parse_highmem(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	highmem_pages = memparse(arg, &arg) >> PAGE_SHIFT;
	वापस 0;
पूर्ण
early_param("highmem", parse_highmem);

#घोषणा MSG_HIGHMEM_TOO_BIG \
	"highmem size (%luMB) is bigger than pages available (%luMB)!\n"

#घोषणा MSG_LOWMEM_TOO_SMALL \
	"highmem size (%luMB) results in <64MB lowmem, ignoring it!\n"
/*
 * All of RAM fits पूर्णांकo lowmem - but अगर user wants highmem
 * artअगरicially via the highmem=x boot parameter then create
 * it:
 */
अटल व्योम __init lowmem_pfn_init(व्योम)
अणु
	/* max_low_pfn is 0, we alपढ़ोy have early_res support */
	max_low_pfn = max_pfn;

	अगर (highmem_pages == -1)
		highmem_pages = 0;
#अगर_घोषित CONFIG_HIGHMEM
	अगर (highmem_pages >= max_pfn) अणु
		prपूर्णांकk(KERN_ERR MSG_HIGHMEM_TOO_BIG,
			pages_to_mb(highmem_pages), pages_to_mb(max_pfn));
		highmem_pages = 0;
	पूर्ण
	अगर (highmem_pages) अणु
		अगर (max_low_pfn - highmem_pages < 64*1024*1024/PAGE_SIZE) अणु
			prपूर्णांकk(KERN_ERR MSG_LOWMEM_TOO_SMALL,
				pages_to_mb(highmem_pages));
			highmem_pages = 0;
		पूर्ण
		max_low_pfn -= highmem_pages;
	पूर्ण
#अन्यथा
	अगर (highmem_pages)
		prपूर्णांकk(KERN_ERR "ignoring highmem size on non-highmem kernel!\n");
#पूर्ण_अगर
पूर्ण

#घोषणा MSG_HIGHMEM_TOO_SMALL \
	"only %luMB highmem pages available, ignoring highmem size of %luMB!\n"

#घोषणा MSG_HIGHMEM_TRIMMED \
	"Warning: only 4GB will be used. Use a HIGHMEM64G enabled kernel!\n"
/*
 * We have more RAM than fits पूर्णांकo lowmem - we try to put it पूर्णांकo
 * highmem, also taking the highmem=x boot parameter पूर्णांकo account:
 */
अटल व्योम __init highmem_pfn_init(व्योम)
अणु
	max_low_pfn = MAXMEM_PFN;

	अगर (highmem_pages == -1)
		highmem_pages = max_pfn - MAXMEM_PFN;

	अगर (highmem_pages + MAXMEM_PFN < max_pfn)
		max_pfn = MAXMEM_PFN + highmem_pages;

	अगर (highmem_pages + MAXMEM_PFN > max_pfn) अणु
		prपूर्णांकk(KERN_WARNING MSG_HIGHMEM_TOO_SMALL,
			pages_to_mb(max_pfn - MAXMEM_PFN),
			pages_to_mb(highmem_pages));
		highmem_pages = 0;
	पूर्ण
#अगर_अघोषित CONFIG_HIGHMEM
	/* Maximum memory usable is what is directly addressable */
	prपूर्णांकk(KERN_WARNING "Warning only %ldMB will be used.\n", MAXMEM>>20);
	अगर (max_pfn > MAX_NONPAE_PFN)
		prपूर्णांकk(KERN_WARNING "Use a HIGHMEM64G enabled kernel.\n");
	अन्यथा
		prपूर्णांकk(KERN_WARNING "Use a HIGHMEM enabled kernel.\n");
	max_pfn = MAXMEM_PFN;
#अन्यथा /* !CONFIG_HIGHMEM */
#अगर_अघोषित CONFIG_HIGHMEM64G
	अगर (max_pfn > MAX_NONPAE_PFN) अणु
		max_pfn = MAX_NONPAE_PFN;
		prपूर्णांकk(KERN_WARNING MSG_HIGHMEM_TRIMMED);
	पूर्ण
#पूर्ण_अगर /* !CONFIG_HIGHMEM64G */
#पूर्ण_अगर /* !CONFIG_HIGHMEM */
पूर्ण

/*
 * Determine low and high memory ranges:
 */
व्योम __init find_low_pfn_range(व्योम)
अणु
	/* it could update max_pfn */

	अगर (max_pfn <= MAXMEM_PFN)
		lowmem_pfn_init();
	अन्यथा
		highmem_pfn_init();
पूर्ण

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
व्योम __init iniपंचांगem_init(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	highstart_pfn = highend_pfn = max_pfn;
	अगर (max_pfn > max_low_pfn)
		highstart_pfn = max_low_pfn;
	prपूर्णांकk(KERN_NOTICE "%ldMB HIGHMEM available.\n",
		pages_to_mb(highend_pfn - highstart_pfn));
	high_memory = (व्योम *) __va(highstart_pfn * PAGE_SIZE - 1) + 1;
#अन्यथा
	high_memory = (व्योम *) __va(max_low_pfn * PAGE_SIZE - 1) + 1;
#पूर्ण_अगर

	memblock_set_node(0, PHYS_ADDR_MAX, &memblock.memory, 0);

#अगर_घोषित CONFIG_FLATMEM
	max_mapnr = IS_ENABLED(CONFIG_HIGHMEM) ? highend_pfn : max_low_pfn;
#पूर्ण_अगर
	__vदो_स्मृति_start_set = true;

	prपूर्णांकk(KERN_NOTICE "%ldMB LOWMEM available.\n",
			pages_to_mb(max_low_pfn));

	setup_booपंचांगem_allocator();
पूर्ण
#पूर्ण_अगर /* !CONFIG_NEED_MULTIPLE_NODES */

व्योम __init setup_booपंचांगem_allocator(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "  mapped low ram: 0 - %08lx\n",
		 max_pfn_mapped<<PAGE_SHIFT);
	prपूर्णांकk(KERN_INFO "  low ram: 0 - %08lx\n", max_low_pfn<<PAGE_SHIFT);
पूर्ण

/*
 * paging_init() sets up the page tables - note that the first 8MB are
 * alपढ़ोy mapped by head.S.
 *
 * This routines also unmaps the page at भव kernel address 0, so
 * that we can trap those pesky शून्य-reference errors in the kernel.
 */
व्योम __init paging_init(व्योम)
अणु
	pagetable_init();

	__flush_tlb_all();

	/*
	 * NOTE: at this poपूर्णांक the booपंचांगem allocator is fully available.
	 */
	olpc_dt_build_devicetree();
	sparse_init();
	zone_sizes_init();
पूर्ण

/*
 * Test अगर the WP bit works in supervisor mode. It isn't supported on 386's
 * and also on some strange 486's. All 586+'s are OK. This used to involve
 * black magic jumps to work around some nasty CPU bugs, but क्रमtunately the
 * चयन to using exceptions got rid of all that.
 */
अटल व्योम __init test_wp_bit(व्योम)
अणु
	अक्षर z = 0;

	prपूर्णांकk(KERN_INFO "Checking if this processor honours the WP bit even in supervisor mode...");

	__set_fixmap(FIX_WP_TEST, __pa_symbol(empty_zero_page), PAGE_KERNEL_RO);

	अगर (copy_to_kernel_nofault((अक्षर *)fix_to_virt(FIX_WP_TEST), &z, 1)) अणु
		clear_fixmap(FIX_WP_TEST);
		prपूर्णांकk(KERN_CONT "Ok.\n");
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_CONT "No.\n");
	panic("Linux doesn't support CPUs with broken WP.");
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	pci_iommu_alloc();

#अगर_घोषित CONFIG_FLATMEM
	BUG_ON(!mem_map);
#पूर्ण_अगर
	/*
	 * With CONFIG_DEBUG_PAGEALLOC initialization of highmem pages has to
	 * be करोne beक्रमe memblock_मुक्त_all(). Memblock use मुक्त low memory क्रम
	 * temporary data (see find_range_array()) and क्रम this purpose can use
	 * pages that was alपढ़ोy passed to the buddy allocator, hence marked as
	 * not accessible in the page tables when compiled with
	 * CONFIG_DEBUG_PAGEALLOC. Otherwise order of initialization is not
	 * important here.
	 */
	set_highmem_pages_init();

	/* this will put all low memory onto the मुक्तlists */
	memblock_मुक्त_all();

	after_booपंचांगem = 1;
	x86_init.hyper.init_after_booपंचांगem();

	/*
	 * Check boundaries twice: Some fundamental inconsistencies can
	 * be detected at build समय alपढ़ोy.
	 */
#घोषणा __FIXADDR_TOP (-PAGE_SIZE)
#अगर_घोषित CONFIG_HIGHMEM
	BUILD_BUG_ON(PKMAP_BASE + LAST_PKMAP*PAGE_SIZE	> FIXADDR_START);
	BUILD_BUG_ON(VMALLOC_END			> PKMAP_BASE);
#पूर्ण_अगर
#घोषणा high_memory (-128UL << 20)
	BUILD_BUG_ON(VMALLOC_START			>= VMALLOC_END);
#अघोषित high_memory
#अघोषित __FIXADDR_TOP

#अगर_घोषित CONFIG_HIGHMEM
	BUG_ON(PKMAP_BASE + LAST_PKMAP*PAGE_SIZE	> FIXADDR_START);
	BUG_ON(VMALLOC_END				> PKMAP_BASE);
#पूर्ण_अगर
	BUG_ON(VMALLOC_START				>= VMALLOC_END);
	BUG_ON((अचिन्हित दीर्घ)high_memory		> VMALLOC_START);

	test_wp_bit();
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
पूर्णांक arch_add_memory(पूर्णांक nid, u64 start, u64 size,
		    काष्ठा mhp_params *params)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;
	पूर्णांक ret;

	/*
	 * The page tables were alपढ़ोy mapped at boot so अगर the caller
	 * requests a dअगरferent mapping type then we must change all the
	 * pages with __set_memory_prot().
	 */
	अगर (params->pgprot.pgprot != PAGE_KERNEL.pgprot) अणु
		ret = __set_memory_prot(start, nr_pages, params->pgprot);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस __add_pages(nid, start_pfn, nr_pages, params);
पूर्ण

व्योम arch_हटाओ_memory(पूर्णांक nid, u64 start, u64 size,
			काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;

	__हटाओ_pages(start_pfn, nr_pages, alपंचांगap);
पूर्ण
#पूर्ण_अगर

पूर्णांक kernel_set_to_पढ़ोonly __पढ़ो_mostly;

अटल व्योम mark_nxdata_nx(व्योम)
अणु
	/*
	 * When this called, init has alपढ़ोy been executed and released,
	 * so everything past _etext should be NX.
	 */
	अचिन्हित दीर्घ start = PFN_ALIGN(_etext);
	/*
	 * This comes from __is_kernel_text upper limit. Also HPAGE where used:
	 */
	अचिन्हित दीर्घ size = (((अचिन्हित दीर्घ)__init_end + HPAGE_SIZE) & HPAGE_MASK) - start;

	अगर (__supported_pte_mask & _PAGE_NX)
		prपूर्णांकk(KERN_INFO "NX-protecting the kernel data: %luk\n", size >> 10);
	set_memory_nx(start, size >> PAGE_SHIFT);
पूर्ण

व्योम mark_rodata_ro(व्योम)
अणु
	अचिन्हित दीर्घ start = PFN_ALIGN(_text);
	अचिन्हित दीर्घ size = (अचिन्हित दीर्घ)__end_rodata - start;

	set_pages_ro(virt_to_page(start), size >> PAGE_SHIFT);
	pr_info("Write protecting kernel text and read-only data: %luk\n",
		size >> 10);

	kernel_set_to_पढ़ोonly = 1;

#अगर_घोषित CONFIG_CPA_DEBUG
	pr_info("Testing CPA: Reverting %lx-%lx\n", start, start + size);
	set_pages_rw(virt_to_page(start), size >> PAGE_SHIFT);

	pr_info("Testing CPA: write protecting again\n");
	set_pages_ro(virt_to_page(start), size >> PAGE_SHIFT);
#पूर्ण_अगर
	mark_nxdata_nx();
	अगर (__supported_pte_mask & _PAGE_NX)
		debug_checkwx();
पूर्ण
