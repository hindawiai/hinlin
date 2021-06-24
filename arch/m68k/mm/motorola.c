<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/m68k/mm/motorola.c
 *
 * Routines specअगरic to the Motorola MMU, originally from:
 * linux/arch/m68k/init.c
 * which are Copyright (C) 1995 Hamish Macकरोnald
 *
 * Moved 8/20/1999 Sam Creasey
 */

#समावेश <linux/module.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#अगर_घोषित CONFIG_ATARI
#समावेश <यंत्र/atari_stram.h>
#पूर्ण_अगर
#समावेश <यंत्र/sections.h>

#अघोषित DEBUG

#अगर_अघोषित mm_cachebits
/*
 * Bits to add to page descriptors क्रम "normal" caching mode.
 * For 68020/030 this is 0.
 * For 68040, this is _PAGE_CACHE040 (cachable, copyback)
 */
अचिन्हित दीर्घ mm_cachebits;
EXPORT_SYMBOL(mm_cachebits);
#पूर्ण_अगर

/* Prior to calling these routines, the page should have been flushed
 * from both the cache and ATC, or the CPU might not notice that the
 * cache setting क्रम the page has been changed. -jskov
 */
अटल अंतरभूत व्योम nocache_page(व्योम *vaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)vaddr;

	अगर (CPU_IS_040_OR_060) अणु
		pte_t *ptep = virt_to_kpte(addr);

		*ptep = pte_mknocache(*ptep);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cache_page(व्योम *vaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)vaddr;

	अगर (CPU_IS_040_OR_060) अणु
		pte_t *ptep = virt_to_kpte(addr);

		*ptep = pte_mkcache(*ptep);
	पूर्ण
पूर्ण

/*
 * Motorola 680x0 user's manual recommends using uncached memory क्रम address
 * translation tables.
 *
 * Seeing how the MMU can be बाह्यal on (some of) these chips, that seems like
 * a very important recommendation to follow. Provide some helpers to combat
 * 'variation' amongst the users of this.
 */

व्योम mmu_page_ctor(व्योम *page)
अणु
	__flush_page_to_ram(page);
	flush_tlb_kernel_page(page);
	nocache_page(page);
पूर्ण

व्योम mmu_page_dtor(व्योम *page)
अणु
	cache_page(page);
पूर्ण

/* ++andreas: अणुget,मुक्तपूर्ण_poपूर्णांकer_table rewritten to use unused fields from
   काष्ठा page instead of separately kदो_स्मृतिed काष्ठा.  Stolen from
   arch/sparc/mm/srmmu.c ... */

प्रकार काष्ठा list_head ptable_desc;

अटल काष्ठा list_head ptable_list[2] = अणु
	LIST_HEAD_INIT(ptable_list[0]),
	LIST_HEAD_INIT(ptable_list[1]),
पूर्ण;

#घोषणा PD_PTABLE(page) ((ptable_desc *)&(virt_to_page(page)->lru))
#घोषणा PD_PAGE(ptable) (list_entry(ptable, काष्ठा page, lru))
#घोषणा PD_MARKBITS(dp) (*(अचिन्हित पूर्णांक *)&PD_PAGE(dp)->index)

अटल स्थिर पूर्णांक ptable_shअगरt[2] = अणु
	7+2, /* PGD, PMD */
	6+2, /* PTE */
पूर्ण;

#घोषणा ptable_size(type) (1U << ptable_shअगरt[type])
#घोषणा ptable_mask(type) ((1U << (PAGE_SIZE / ptable_size(type))) - 1)

व्योम __init init_poपूर्णांकer_table(व्योम *table, पूर्णांक type)
अणु
	ptable_desc *dp;
	अचिन्हित दीर्घ ptable = (अचिन्हित दीर्घ)table;
	अचिन्हित दीर्घ page = ptable & PAGE_MASK;
	अचिन्हित पूर्णांक mask = 1U << ((ptable - page)/ptable_size(type));

	dp = PD_PTABLE(page);
	अगर (!(PD_MARKBITS(dp) & mask)) अणु
		PD_MARKBITS(dp) = ptable_mask(type);
		list_add(dp, &ptable_list[type]);
	पूर्ण

	PD_MARKBITS(dp) &= ~mask;
	pr_debug("init_pointer_table: %lx, %x\n", ptable, PD_MARKBITS(dp));

	/* unreserve the page so it's possible to मुक्त that page */
	__ClearPageReserved(PD_PAGE(dp));
	init_page_count(PD_PAGE(dp));

	वापस;
पूर्ण

व्योम *get_poपूर्णांकer_table(पूर्णांक type)
अणु
	ptable_desc *dp = ptable_list[type].next;
	अचिन्हित पूर्णांक mask = list_empty(&ptable_list[type]) ? 0 : PD_MARKBITS(dp);
	अचिन्हित पूर्णांक पंचांगp, off;

	/*
	 * For a poपूर्णांकer table क्रम a user process address space, a
	 * table is taken from a page allocated क्रम the purpose.  Each
	 * page can hold 8 poपूर्णांकer tables.  The page is remapped in
	 * भव address space to be noncacheable.
	 */
	अगर (mask == 0) अणु
		व्योम *page;
		ptable_desc *new;

		अगर (!(page = (व्योम *)get_zeroed_page(GFP_KERNEL)))
			वापस शून्य;

		अगर (type == TABLE_PTE) अणु
			/*
			 * m68k करोesn't have SPLIT_PTE_PTLOCKS क्रम not having
			 * SMP.
			 */
			pgtable_pte_page_ctor(virt_to_page(page));
		पूर्ण

		mmu_page_ctor(page);

		new = PD_PTABLE(page);
		PD_MARKBITS(new) = ptable_mask(type) - 1;
		list_add_tail(new, dp);

		वापस (pmd_t *)page;
	पूर्ण

	क्रम (पंचांगp = 1, off = 0; (mask & पंचांगp) == 0; पंचांगp <<= 1, off += ptable_size(type))
		;
	PD_MARKBITS(dp) = mask & ~पंचांगp;
	अगर (!PD_MARKBITS(dp)) अणु
		/* move to end of list */
		list_move_tail(dp, &ptable_list[type]);
	पूर्ण
	वापस page_address(PD_PAGE(dp)) + off;
पूर्ण

पूर्णांक मुक्त_poपूर्णांकer_table(व्योम *table, पूर्णांक type)
अणु
	ptable_desc *dp;
	अचिन्हित दीर्घ ptable = (अचिन्हित दीर्घ)table;
	अचिन्हित दीर्घ page = ptable & PAGE_MASK;
	अचिन्हित पूर्णांक mask = 1U << ((ptable - page)/ptable_size(type));

	dp = PD_PTABLE(page);
	अगर (PD_MARKBITS (dp) & mask)
		panic ("table already free!");

	PD_MARKBITS (dp) |= mask;

	अगर (PD_MARKBITS(dp) == ptable_mask(type)) अणु
		/* all tables in page are मुक्त, मुक्त page */
		list_del(dp);
		mmu_page_dtor((व्योम *)page);
		अगर (type == TABLE_PTE)
			pgtable_pte_page_dtor(virt_to_page(page));
		मुक्त_page (page);
		वापस 1;
	पूर्ण अन्यथा अगर (ptable_list[type].next != dp) अणु
		/*
		 * move this descriptor to the front of the list, since
		 * it has one or more मुक्त tables.
		 */
		list_move(dp, &ptable_list[type]);
	पूर्ण
	वापस 0;
पूर्ण

/* size of memory alपढ़ोy mapped in head.S */
बाह्य __initdata अचिन्हित दीर्घ m68k_init_mapped_size;

बाह्य अचिन्हित दीर्घ availmem;

अटल pte_t *last_pte_table __initdata = शून्य;

अटल pte_t * __init kernel_page_table(व्योम)
अणु
	pte_t *pte_table = last_pte_table;

	अगर (PAGE_ALIGNED(last_pte_table)) अणु
		pte_table = memblock_alloc_low(PAGE_SIZE, PAGE_SIZE);
		अगर (!pte_table) अणु
			panic("%s: Failed to allocate %lu bytes align=%lx\n",
					__func__, PAGE_SIZE, PAGE_SIZE);
		पूर्ण

		clear_page(pte_table);
		mmu_page_ctor(pte_table);

		last_pte_table = pte_table;
	पूर्ण

	last_pte_table += PTRS_PER_PTE;

	वापस pte_table;
पूर्ण

अटल pmd_t *last_pmd_table __initdata = शून्य;

अटल pmd_t * __init kernel_ptr_table(व्योम)
अणु
	अगर (!last_pmd_table) अणु
		अचिन्हित दीर्घ pmd, last;
		पूर्णांक i;

		/* Find the last ptr table that was used in head.S and
		 * reuse the reमुख्यing space in that page क्रम further
		 * ptr tables.
		 */
		last = (अचिन्हित दीर्घ)kernel_pg_dir;
		क्रम (i = 0; i < PTRS_PER_PGD; i++) अणु
			pud_t *pud = (pud_t *)(&kernel_pg_dir[i]);

			अगर (!pud_present(*pud))
				जारी;
			pmd = pgd_page_vaddr(kernel_pg_dir[i]);
			अगर (pmd > last)
				last = pmd;
		पूर्ण

		last_pmd_table = (pmd_t *)last;
#अगर_घोषित DEBUG
		prपूर्णांकk("kernel_ptr_init: %p\n", last_pmd_table);
#पूर्ण_अगर
	पूर्ण

	last_pmd_table += PTRS_PER_PMD;
	अगर (PAGE_ALIGNED(last_pmd_table)) अणु
		last_pmd_table = memblock_alloc_low(PAGE_SIZE, PAGE_SIZE);
		अगर (!last_pmd_table)
			panic("%s: Failed to allocate %lu bytes align=%lx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);

		clear_page(last_pmd_table);
		mmu_page_ctor(last_pmd_table);
	पूर्ण

	वापस last_pmd_table;
पूर्ण

अटल व्योम __init map_node(पूर्णांक node)
अणु
	अचिन्हित दीर्घ physaddr, virtaddr, size;
	pgd_t *pgd_dir;
	p4d_t *p4d_dir;
	pud_t *pud_dir;
	pmd_t *pmd_dir;
	pte_t *pte_dir;

	size = m68k_memory[node].size;
	physaddr = m68k_memory[node].addr;
	virtaddr = (अचिन्हित दीर्घ)phys_to_virt(physaddr);
	physaddr |= m68k_supervisor_cachemode |
		    _PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_सूचीTY;
	अगर (CPU_IS_040_OR_060)
		physaddr |= _PAGE_GLOBAL040;

	जबतक (size > 0) अणु
#अगर_घोषित DEBUG
		अगर (!(virtaddr & (PMD_SIZE-1)))
			prपूर्णांकk ("\npa=%#lx va=%#lx ", physaddr & PAGE_MASK,
				virtaddr);
#पूर्ण_अगर
		pgd_dir = pgd_offset_k(virtaddr);
		अगर (virtaddr && CPU_IS_020_OR_030) अणु
			अगर (!(virtaddr & (PGसूची_SIZE-1)) &&
			    size >= PGसूची_SIZE) अणु
#अगर_घोषित DEBUG
				prपूर्णांकk ("[very early term]");
#पूर्ण_अगर
				pgd_val(*pgd_dir) = physaddr;
				size -= PGसूची_SIZE;
				virtaddr += PGसूची_SIZE;
				physaddr += PGसूची_SIZE;
				जारी;
			पूर्ण
		पूर्ण
		p4d_dir = p4d_offset(pgd_dir, virtaddr);
		pud_dir = pud_offset(p4d_dir, virtaddr);
		अगर (!pud_present(*pud_dir)) अणु
			pmd_dir = kernel_ptr_table();
#अगर_घोषित DEBUG
			prपूर्णांकk ("[new pointer %p]", pmd_dir);
#पूर्ण_अगर
			pud_set(pud_dir, pmd_dir);
		पूर्ण अन्यथा
			pmd_dir = pmd_offset(pud_dir, virtaddr);

		अगर (CPU_IS_020_OR_030) अणु
			अगर (virtaddr) अणु
#अगर_घोषित DEBUG
				prपूर्णांकk ("[early term]");
#पूर्ण_अगर
				pmd_val(*pmd_dir) = physaddr;
				physaddr += PMD_SIZE;
			पूर्ण अन्यथा अणु
				पूर्णांक i;
#अगर_घोषित DEBUG
				prपूर्णांकk ("[zero map]");
#पूर्ण_अगर
				pte_dir = kernel_page_table();
				pmd_set(pmd_dir, pte_dir);

				pte_val(*pte_dir++) = 0;
				physaddr += PAGE_SIZE;
				क्रम (i = 1; i < PTRS_PER_PTE; physaddr += PAGE_SIZE, i++)
					pte_val(*pte_dir++) = physaddr;
			पूर्ण
			size -= PMD_SIZE;
			virtaddr += PMD_SIZE;
		पूर्ण अन्यथा अणु
			अगर (!pmd_present(*pmd_dir)) अणु
#अगर_घोषित DEBUG
				prपूर्णांकk ("[new table]");
#पूर्ण_अगर
				pte_dir = kernel_page_table();
				pmd_set(pmd_dir, pte_dir);
			पूर्ण
			pte_dir = pte_offset_kernel(pmd_dir, virtaddr);

			अगर (virtaddr) अणु
				अगर (!pte_present(*pte_dir))
					pte_val(*pte_dir) = physaddr;
			पूर्ण अन्यथा
				pte_val(*pte_dir) = 0;
			size -= PAGE_SIZE;
			virtaddr += PAGE_SIZE;
			physaddr += PAGE_SIZE;
		पूर्ण

	पूर्ण
#अगर_घोषित DEBUG
	prपूर्णांकk("\n");
#पूर्ण_अगर
पूर्ण

/*
 * paging_init() जारीs the भव memory environment setup which
 * was begun by the code in arch/head.S.
 */
व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0, पूर्ण;
	अचिन्हित दीर्घ min_addr, max_addr;
	अचिन्हित दीर्घ addr;
	पूर्णांक i;

#अगर_घोषित DEBUG
	prपूर्णांकk ("start of paging_init (%p, %lx)\n", kernel_pg_dir, availmem);
#पूर्ण_अगर

	/* Fix the cache mode in the page descriptors क्रम the 680[46]0.  */
	अगर (CPU_IS_040_OR_060) अणु
		पूर्णांक i;
#अगर_अघोषित mm_cachebits
		mm_cachebits = _PAGE_CACHE040;
#पूर्ण_अगर
		क्रम (i = 0; i < 16; i++)
			pgprot_val(protection_map[i]) |= _PAGE_CACHE040;
	पूर्ण

	min_addr = m68k_memory[0].addr;
	max_addr = min_addr + m68k_memory[0].size;
	memblock_add_node(m68k_memory[0].addr, m68k_memory[0].size, 0);
	क्रम (i = 1; i < m68k_num_memory;) अणु
		अगर (m68k_memory[i].addr < min_addr) अणु
			prपूर्णांकk("Ignoring memory chunk at 0x%lx:0x%lx before the first chunk\n",
				m68k_memory[i].addr, m68k_memory[i].size);
			prपूर्णांकk("Fix your bootloader or use a memfile to make use of this area!\n");
			m68k_num_memory--;
			स_हटाओ(m68k_memory + i, m68k_memory + i + 1,
				(m68k_num_memory - i) * माप(काष्ठा m68k_mem_info));
			जारी;
		पूर्ण
		memblock_add_node(m68k_memory[i].addr, m68k_memory[i].size, i);
		addr = m68k_memory[i].addr + m68k_memory[i].size;
		अगर (addr > max_addr)
			max_addr = addr;
		i++;
	पूर्ण
	m68k_memoffset = min_addr - PAGE_OFFSET;
	m68k_virt_to_node_shअगरt = fls(max_addr - min_addr - 1) - 6;

	module_fixup(शून्य, __start_fixup, __stop_fixup);
	flush_icache();

	high_memory = phys_to_virt(max_addr);

	min_low_pfn = availmem >> PAGE_SHIFT;
	max_pfn = max_low_pfn = max_addr >> PAGE_SHIFT;

	/* Reserve kernel text/data/bss and the memory allocated in head.S */
	memblock_reserve(m68k_memory[0].addr, availmem - m68k_memory[0].addr);

	/*
	 * Map the physical memory available पूर्णांकo the kernel भव
	 * address space. Make sure memblock will not try to allocate
	 * pages beyond the memory we alपढ़ोy mapped in head.S
	 */
	memblock_set_bottom_up(true);

	क्रम (i = 0; i < m68k_num_memory; i++) अणु
		m68k_setup_node(i);
		map_node(i);
	पूर्ण

	flush_tlb_all();

	/*
	 * initialize the bad page table and bad page to poपूर्णांक
	 * to a couple of allocated pages
	 */
	empty_zero_page = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!empty_zero_page)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	/*
	 * Set up SFC/DFC रेजिस्टरs
	 */
	set_fs(KERNEL_DS);

#अगर_घोषित DEBUG
	prपूर्णांकk ("before free_area_init\n");
#पूर्ण_अगर
	क्रम (i = 0; i < m68k_num_memory; i++)
		अगर (node_present_pages(i))
			node_set_state(i, N_NORMAL_MEMORY);

	max_zone_pfn[ZONE_DMA] = memblock_end_of_DRAM();
	मुक्त_area_init(max_zone_pfn);
पूर्ण
