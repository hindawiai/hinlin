<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 SiFive
 */

#समावेश <यंत्र/cacheflush.h>

#अगर_घोषित CONFIG_SMP

#समावेश <यंत्र/sbi.h>

अटल व्योम ipi_remote_fence_i(व्योम *info)
अणु
	वापस local_flush_icache_all();
पूर्ण

व्योम flush_icache_all(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_RISCV_SBI))
		sbi_remote_fence_i(शून्य);
	अन्यथा
		on_each_cpu(ipi_remote_fence_i, शून्य, 1);
पूर्ण
EXPORT_SYMBOL(flush_icache_all);

/*
 * Perक्रमms an icache flush क्रम the given MM context.  RISC-V has no direct
 * mechanism क्रम inकाष्ठाion cache shoot करोwns, so instead we send an IPI that
 * inक्रमms the remote harts they need to flush their local inकाष्ठाion caches.
 * To aव्योम pathologically slow behavior in a common हाल (a bunch of
 * single-hart processes on a many-hart machine, ie 'make -j') we aव्योम the
 * IPIs क्रम harts that are not currently executing a MM context and instead
 * schedule a deferred local inकाष्ठाion cache flush to be perक्रमmed beक्रमe
 * execution resumes on each hart.
 */
व्योम flush_icache_mm(काष्ठा mm_काष्ठा *mm, bool local)
अणु
	अचिन्हित पूर्णांक cpu;
	cpumask_t others, *mask;

	preempt_disable();

	/* Mark every hart's icache as needing a flush क्रम this MM. */
	mask = &mm->context.icache_stale_mask;
	cpumask_setall(mask);
	/* Flush this hart's I$ now, and mark it as flushed. */
	cpu = smp_processor_id();
	cpumask_clear_cpu(cpu, mask);
	local_flush_icache_all();

	/*
	 * Flush the I$ of other harts concurrently executing, and mark them as
	 * flushed.
	 */
	cpumask_andnot(&others, mm_cpumask(mm), cpumask_of(cpu));
	local |= cpumask_empty(&others);
	अगर (mm == current->active_mm && local) अणु
		/*
		 * It's assumed that at least one strongly ordered operation is
		 * perक्रमmed on this hart between setting a hart's cpumask bit
		 * and scheduling this MM context on that hart.  Sending an SBI
		 * remote message will करो this, but in the हाल where no
		 * messages are sent we still need to order this hart's ग_लिखोs
		 * with flush_icache_deferred().
		 */
		smp_mb();
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_RISCV_SBI)) अणु
		cpumask_t hartid_mask;

		riscv_cpuid_to_hartid_mask(&others, &hartid_mask);
		sbi_remote_fence_i(cpumask_bits(&hartid_mask));
	पूर्ण अन्यथा अणु
		on_each_cpu_mask(&others, ipi_remote_fence_i, शून्य, 1);
	पूर्ण

	preempt_enable();
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_MMU
व्योम flush_icache_pte(pte_t pte)
अणु
	काष्ठा page *page = pte_page(pte);

	अगर (!test_and_set_bit(PG_dcache_clean, &page->flags))
		flush_icache_all();
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */
