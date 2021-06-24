<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/cache.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <यंत्र/cache.h>

व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		      pte_t *pte)
अणु
	अचिन्हित दीर्घ addr;
	काष्ठा page *page;

	अगर (!pfn_valid(pte_pfn(*pte)))
		वापस;

	page = pfn_to_page(pte_pfn(*pte));
	अगर (page == ZERO_PAGE(0))
		वापस;

	अगर (test_and_set_bit(PG_dcache_clean, &page->flags))
		वापस;

	addr = (अचिन्हित दीर्घ) kmap_atomic(page);

	dcache_wb_range(addr, addr + PAGE_SIZE);

	अगर (vma->vm_flags & VM_EXEC)
		icache_inv_range(addr, addr + PAGE_SIZE);

	kunmap_atomic((व्योम *) addr);
पूर्ण

व्योम flush_icache_deferred(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	cpumask_t *mask = &mm->context.icache_stale_mask;

	अगर (cpumask_test_cpu(cpu, mask)) अणु
		cpumask_clear_cpu(cpu, mask);
		/*
		 * Ensure the remote hart's ग_लिखोs are visible to this hart.
		 * This pairs with a barrier in flush_icache_mm.
		 */
		smp_mb();
		local_icache_inv_all(शून्य);
	पूर्ण
पूर्ण

व्योम flush_icache_mm_range(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित पूर्णांक cpu;
	cpumask_t others, *mask;

	preempt_disable();

#अगर_घोषित CONFIG_CPU_HAS_ICACHE_INS
	अगर (mm == current->mm) अणु
		icache_inv_range(start, end);
		preempt_enable();
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Mark every hart's icache as needing a flush क्रम this MM. */
	mask = &mm->context.icache_stale_mask;
	cpumask_setall(mask);

	/* Flush this hart's I$ now, and mark it as flushed. */
	cpu = smp_processor_id();
	cpumask_clear_cpu(cpu, mask);
	local_icache_inv_all(शून्य);

	/*
	 * Flush the I$ of other harts concurrently executing, and mark them as
	 * flushed.
	 */
	cpumask_andnot(&others, mm_cpumask(mm), cpumask_of(cpu));

	अगर (mm != current->active_mm || !cpumask_empty(&others)) अणु
		on_each_cpu_mask(&others, local_icache_inv_all, शून्य, 1);
		cpumask_clear(mask);
	पूर्ण

	preempt_enable();
पूर्ण
