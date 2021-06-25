<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Based upon linux/arch/m68k/mm/sun3mmu.c
 * Based upon linux/arch/ppc/mm/mmu_context.c
 *
 * Implementations of mm routines specअगरic to the Coldfire MMU.
 *
 * Copyright (c) 2008 Freescale Semiconductor, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mcf_pgभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/pgभाग.स>

#घोषणा KMAPAREA(x)	((x >= VMALLOC_START) && (x < KMAP_END))

mm_context_t next_mmu_context;
अचिन्हित दीर्घ context_map[LAST_CONTEXT / BITS_PER_LONG + 1];
atomic_t nr_मुक्त_contexts;
काष्ठा mm_काष्ठा *context_mm[LAST_CONTEXT+1];
अचिन्हित दीर्घ num_pages;

/*
 * ColdFire paging_init derived from sun3.
 */
व्योम __init paging_init(व्योम)
अणु
	pgd_t *pg_dir;
	pte_t *pg_table;
	अचिन्हित दीर्घ address, size;
	अचिन्हित दीर्घ next_pgtable, booपंचांगem_end;
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;
	पूर्णांक i;

	empty_zero_page = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!empty_zero_page)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	pg_dir = swapper_pg_dir;
	स_रखो(swapper_pg_dir, 0, माप(swapper_pg_dir));

	size = num_pages * माप(pte_t);
	size = (size + PAGE_SIZE) & ~(PAGE_SIZE-1);
	next_pgtable = (अचिन्हित दीर्घ) memblock_alloc(size, PAGE_SIZE);
	अगर (!next_pgtable)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, size, PAGE_SIZE);

	booपंचांगem_end = (next_pgtable + size + PAGE_SIZE) & PAGE_MASK;
	pg_dir += PAGE_OFFSET >> PGसूची_SHIFT;

	address = PAGE_OFFSET;
	जबतक (address < (अचिन्हित दीर्घ)high_memory) अणु
		pg_table = (pte_t *) next_pgtable;
		next_pgtable += PTRS_PER_PTE * माप(pte_t);
		pgd_val(*pg_dir) = (अचिन्हित दीर्घ) pg_table;
		pg_dir++;

		/* now change pg_table to kernel भव addresses */
		क्रम (i = 0; i < PTRS_PER_PTE; ++i, ++pg_table) अणु
			pte_t pte = pfn_pte(virt_to_pfn(address), PAGE_INIT);
			अगर (address >= (अचिन्हित दीर्घ) high_memory)
				pte_val(pte) = 0;

			set_pte(pg_table, pte);
			address += PAGE_SIZE;
		पूर्ण
	पूर्ण

	current->mm = शून्य;
	max_zone_pfn[ZONE_DMA] = PFN_DOWN(_ramend);
	मुक्त_area_init(max_zone_pfn);
पूर्ण

पूर्णांक cf_tlb_miss(काष्ठा pt_regs *regs, पूर्णांक ग_लिखो, पूर्णांक dtlb, पूर्णांक extension_word)
अणु
	अचिन्हित दीर्घ flags, mmuar, mmutr;
	काष्ठा mm_काष्ठा *mm;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	पूर्णांक asid;

	local_irq_save(flags);

	mmuar = (dtlb) ? mmu_पढ़ो(MMUAR) :
		regs->pc + (extension_word * माप(दीर्घ));

	mm = (!user_mode(regs) && KMAPAREA(mmuar)) ? &init_mm : current->mm;
	अगर (!mm) अणु
		local_irq_restore(flags);
		वापस -1;
	पूर्ण

	pgd = pgd_offset(mm, mmuar);
	अगर (pgd_none(*pgd))  अणु
		local_irq_restore(flags);
		वापस -1;
	पूर्ण

	p4d = p4d_offset(pgd, mmuar);
	अगर (p4d_none(*p4d)) अणु
		local_irq_restore(flags);
		वापस -1;
	पूर्ण

	pud = pud_offset(p4d, mmuar);
	अगर (pud_none(*pud)) अणु
		local_irq_restore(flags);
		वापस -1;
	पूर्ण

	pmd = pmd_offset(pud, mmuar);
	अगर (pmd_none(*pmd)) अणु
		local_irq_restore(flags);
		वापस -1;
	पूर्ण

	pte = (KMAPAREA(mmuar)) ? pte_offset_kernel(pmd, mmuar)
				: pte_offset_map(pmd, mmuar);
	अगर (pte_none(*pte) || !pte_present(*pte)) अणु
		local_irq_restore(flags);
		वापस -1;
	पूर्ण

	अगर (ग_लिखो) अणु
		अगर (!pte_ग_लिखो(*pte)) अणु
			local_irq_restore(flags);
			वापस -1;
		पूर्ण
		set_pte(pte, pte_सूची_गढ़ोty(*pte));
	पूर्ण

	set_pte(pte, pte_mkyoung(*pte));
	asid = mm->context & 0xff;
	अगर (!pte_dirty(*pte) && !KMAPAREA(mmuar))
		set_pte(pte, pte_wrprotect(*pte));

	mmutr = (mmuar & PAGE_MASK) | (asid << MMUTR_IDN) | MMUTR_V;
	अगर ((mmuar < TASK_UNMAPPED_BASE) || (mmuar >= TASK_SIZE))
		mmutr |= (pte->pte & CF_PAGE_MMUTR_MASK) >> CF_PAGE_MMUTR_SHIFT;
	mmu_ग_लिखो(MMUTR, mmutr);

	mmu_ग_लिखो(MMUDR, (pte_val(*pte) & PAGE_MASK) |
		((pte->pte) & CF_PAGE_MMUDR_MASK) | MMUDR_SZ_8KB | MMUDR_X);

	अगर (dtlb)
		mmu_ग_लिखो(MMUOR, MMUOR_ACC | MMUOR_UAA);
	अन्यथा
		mmu_ग_लिखो(MMUOR, MMUOR_ITLB | MMUOR_ACC | MMUOR_UAA);

	local_irq_restore(flags);
	वापस 0;
पूर्ण

व्योम __init cf_booपंचांगem_alloc(व्योम)
अणु
	अचिन्हित दीर्घ memstart;

	/* _rambase and _ramend will be naturally page aligned */
	m68k_memory[0].addr = _rambase;
	m68k_memory[0].size = _ramend - _rambase;

	memblock_add_node(m68k_memory[0].addr, m68k_memory[0].size, 0);

	/* compute total pages in प्रणाली */
	num_pages = PFN_DOWN(_ramend - _rambase);

	/* page numbers */
	memstart = PAGE_ALIGN(_ramstart);
	min_low_pfn = PFN_DOWN(_rambase);
	max_pfn = max_low_pfn = PFN_DOWN(_ramend);
	high_memory = (व्योम *)_ramend;

	/* Reserve kernel text/data/bss */
	memblock_reserve(_rambase, memstart - _rambase);

	m68k_virt_to_node_shअगरt = fls(_ramend - 1) - 6;
	module_fixup(शून्य, __start_fixup, __stop_fixup);

	/* setup node data */
	m68k_setup_node(0);
पूर्ण

/*
 * Initialize the context management stuff.
 * The following was taken from arch/ppc/mmu_context.c
 */
व्योम __init cf_mmu_context_init(व्योम)
अणु
	/*
	 * Some processors have too few contexts to reserve one क्रम
	 * init_mm, and require using context 0 क्रम a normal task.
	 * Other processors reserve the use of context zero क्रम the kernel.
	 * This code assumes FIRST_CONTEXT < 32.
	 */
	context_map[0] = (1 << FIRST_CONTEXT) - 1;
	next_mmu_context = FIRST_CONTEXT;
	atomic_set(&nr_मुक्त_contexts, LAST_CONTEXT - FIRST_CONTEXT + 1);
पूर्ण

/*
 * Steal a context from a task that has one at the moment.
 * This isn't an LRU प्रणाली, it just मुक्तs up each context in
 * turn (sort-of pseuकरो-अक्रमom replacement :).  This would be the
 * place to implement an LRU scheme अगर anyone was motivated to करो it.
 *  -- paulus
 */
व्योम steal_context(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm;
	/*
	 * मुक्त up context `next_mmu_context'
	 * अगर we shouldn't free context 0, don't...
	 */
	अगर (next_mmu_context < FIRST_CONTEXT)
		next_mmu_context = FIRST_CONTEXT;
	mm = context_mm[next_mmu_context];
	flush_tlb_mm(mm);
	destroy_context(mm);
पूर्ण

