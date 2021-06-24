<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/m68k/mm/sun3mmu.c
 *
 * Implementations of mm routines specअगरic to the sun3 MMU.
 *
 * Moved here 8/20/1999 Sam Creasey
 *
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>

बाह्य व्योम mmu_emu_init (अचिन्हित दीर्घ booपंचांगem_end);

स्थिर अक्षर bad_pmd_string[] = "Bad pmd in pte_alloc: %08lx\n";

बाह्य अचिन्हित दीर्घ num_pages;

/* For the sun3 we try to follow the i386 paging_init() more बंदly */
/* start_mem and end_mem have PAGE_OFFSET added alपढ़ोy */
/* now sets up tables using sun3 PTEs rather than i386 as beक्रमe. --m */
व्योम __init paging_init(व्योम)
अणु
	pgd_t * pg_dir;
	pte_t * pg_table;
	पूर्णांक i;
	अचिन्हित दीर्घ address;
	अचिन्हित दीर्घ next_pgtable;
	अचिन्हित दीर्घ booपंचांगem_end;
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0, पूर्ण;
	अचिन्हित दीर्घ size;

	empty_zero_page = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!empty_zero_page)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	address = PAGE_OFFSET;
	pg_dir = swapper_pg_dir;
	स_रखो (swapper_pg_dir, 0, माप (swapper_pg_dir));
	स_रखो (kernel_pg_dir,  0, माप (kernel_pg_dir));

	size = num_pages * माप(pte_t);
	size = (size + PAGE_SIZE) & ~(PAGE_SIZE-1);

	next_pgtable = (अचिन्हित दीर्घ)memblock_alloc(size, PAGE_SIZE);
	अगर (!next_pgtable)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, size, PAGE_SIZE);
	booपंचांगem_end = (next_pgtable + size + PAGE_SIZE) & PAGE_MASK;

	/* Map whole memory from PAGE_OFFSET (0x0E000000) */
	pg_dir += PAGE_OFFSET >> PGसूची_SHIFT;

	जबतक (address < (अचिन्हित दीर्घ)high_memory) अणु
		pg_table = (pte_t *) __pa (next_pgtable);
		next_pgtable += PTRS_PER_PTE * माप (pte_t);
		pgd_val(*pg_dir) = (अचिन्हित दीर्घ) pg_table;
		pg_dir++;

		/* now change pg_table to kernel भव addresses */
		pg_table = (pte_t *) __va ((अचिन्हित दीर्घ) pg_table);
		क्रम (i=0; i<PTRS_PER_PTE; ++i, ++pg_table) अणु
			pte_t pte = pfn_pte(virt_to_pfn(address), PAGE_INIT);
			अगर (address >= (अचिन्हित दीर्घ)high_memory)
				pte_val (pte) = 0;
			set_pte (pg_table, pte);
			address += PAGE_SIZE;
		पूर्ण
	पूर्ण

	mmu_emu_init(booपंचांगem_end);

	current->mm = शून्य;

	/* memory sizing is a hack stolen from motorola.c..  hope it works क्रम us */
	max_zone_pfn[ZONE_DMA] = ((अचिन्हित दीर्घ)high_memory) >> PAGE_SHIFT;

	/* I really wish I knew why the following change made things better...  -- Sam */
	मुक्त_area_init(max_zone_pfn);


पूर्ण
