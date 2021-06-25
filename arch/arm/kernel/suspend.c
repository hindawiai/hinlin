<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ftrace.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/tlbflush.h>

बाह्य पूर्णांक __cpu_suspend(अचिन्हित दीर्घ, पूर्णांक (*)(अचिन्हित दीर्घ), u32 cpuid);
बाह्य व्योम cpu_resume_mmu(व्योम);

#अगर_घोषित CONFIG_MMU
पूर्णांक cpu_suspend(अचिन्हित दीर्घ arg, पूर्णांक (*fn)(अचिन्हित दीर्घ))
अणु
	काष्ठा mm_काष्ठा *mm = current->active_mm;
	u32 __mpidr = cpu_logical_map(smp_processor_id());
	पूर्णांक ret;

	अगर (!idmap_pgd)
		वापस -EINVAL;

	/*
	 * Function graph tracer state माला_लो incosistent when the kernel
	 * calls functions that never वापस (aka suspend finishers) hence
	 * disable graph tracing during their execution.
	 */
	छोड़ो_graph_tracing();

	/*
	 * Provide a temporary page table with an identity mapping क्रम
	 * the MMU-enable code, required क्रम resuming.  On successful
	 * resume (indicated by a zero वापस code), we need to चयन
	 * back to the correct page tables.
	 */
	ret = __cpu_suspend(arg, fn, __mpidr);

	unछोड़ो_graph_tracing();

	अगर (ret == 0) अणु
		cpu_चयन_mm(mm->pgd, mm);
		local_flush_bp_all();
		local_flush_tlb_all();
		check_other_bugs();
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
पूर्णांक cpu_suspend(अचिन्हित दीर्घ arg, पूर्णांक (*fn)(अचिन्हित दीर्घ))
अणु
	u32 __mpidr = cpu_logical_map(smp_processor_id());
	पूर्णांक ret;

	छोड़ो_graph_tracing();
	ret = __cpu_suspend(arg, fn, __mpidr);
	unछोड़ो_graph_tracing();

	वापस ret;
पूर्ण
#घोषणा	idmap_pgd	शून्य
#पूर्ण_अगर

/*
 * This is called by __cpu_suspend() to save the state, and करो whatever
 * flushing is required to ensure that when the CPU goes to sleep we have
 * the necessary data available when the caches are not searched.
 */
व्योम __cpu_suspend_save(u32 *ptr, u32 ptrsz, u32 sp, u32 *save_ptr)
अणु
	u32 *ctx = ptr;

	*save_ptr = virt_to_phys(ptr);

	/* This must correspond to the LDM in cpu_resume() assembly */
	*ptr++ = virt_to_phys(idmap_pgd);
	*ptr++ = sp;
	*ptr++ = virt_to_phys(cpu_करो_resume);

	cpu_करो_suspend(ptr);

	flush_cache_louis();

	/*
	 * flush_cache_louis करोes not guarantee that
	 * save_ptr and ptr are cleaned to मुख्य memory,
	 * just up to the Level of Unअगरication Inner Shareable.
	 * Since the context poपूर्णांकer and context itself
	 * are to be retrieved with the MMU off that
	 * data must be cleaned from all cache levels
	 * to मुख्य memory using "area" cache primitives.
	*/
	__cpuc_flush_dcache_area(ctx, ptrsz);
	__cpuc_flush_dcache_area(save_ptr, माप(*save_ptr));

	outer_clean_range(*save_ptr, *save_ptr + ptrsz);
	outer_clean_range(virt_to_phys(save_ptr),
			  virt_to_phys(save_ptr) + माप(*save_ptr));
पूर्ण

बाह्य काष्ठा sleep_save_sp sleep_save_sp;

अटल पूर्णांक cpu_suspend_alloc_sp(व्योम)
अणु
	व्योम *ctx_ptr;
	/* ctx_ptr is an array of physical addresses */
	ctx_ptr = kसुस्मृति(mpidr_hash_size(), माप(u32), GFP_KERNEL);

	अगर (WARN_ON(!ctx_ptr))
		वापस -ENOMEM;
	sleep_save_sp.save_ptr_stash = ctx_ptr;
	sleep_save_sp.save_ptr_stash_phys = virt_to_phys(ctx_ptr);
	sync_cache_w(&sleep_save_sp);
	वापस 0;
पूर्ण
early_initcall(cpu_suspend_alloc_sp);
