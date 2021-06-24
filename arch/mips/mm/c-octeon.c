<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005-2007 Cavium Networks
 */
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpu.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/war.h>

#समावेश <यंत्र/octeon/octeon.h>

अचिन्हित दीर्घ दीर्घ cache_err_dcache[NR_CPUS];
EXPORT_SYMBOL_GPL(cache_err_dcache);

/**
 * Octeon स्वतःmatically flushes the dcache on tlb changes, so
 * from Linux's viewpoपूर्णांक it acts much like a physically
 * tagged cache. No flushing is needed
 *
 */
अटल व्योम octeon_flush_data_cache_page(अचिन्हित दीर्घ addr)
अणु
    /* Nothing to करो */
पूर्ण

अटल अंतरभूत व्योम octeon_local_flush_icache(व्योम)
अणु
	यंत्र अस्थिर ("synci 0($0)");
पूर्ण

/*
 * Flush local I-cache क्रम the specअगरied range.
 */
अटल व्योम local_octeon_flush_icache_range(अचिन्हित दीर्घ start,
					    अचिन्हित दीर्घ end)
अणु
	octeon_local_flush_icache();
पूर्ण

/**
 * Flush caches as necessary क्रम all cores affected by a
 * vma. If no vma is supplied, all cores are flushed.
 *
 * @vma:    VMA to flush or शून्य to flush all icaches.
 */
अटल व्योम octeon_flush_icache_all_cores(काष्ठा vm_area_काष्ठा *vma)
अणु
	बाह्य व्योम octeon_send_ipi_single(पूर्णांक cpu, अचिन्हित पूर्णांक action);
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu;
	cpumask_t mask;
#पूर्ण_अगर

	mb();
	octeon_local_flush_icache();
#अगर_घोषित CONFIG_SMP
	preempt_disable();
	cpu = smp_processor_id();

	/*
	 * If we have a vma काष्ठाure, we only need to worry about
	 * cores it has been used on
	 */
	अगर (vma)
		mask = *mm_cpumask(vma->vm_mm);
	अन्यथा
		mask = *cpu_online_mask;
	cpumask_clear_cpu(cpu, &mask);
	क्रम_each_cpu(cpu, &mask)
		octeon_send_ipi_single(cpu, SMP_ICACHE_FLUSH);

	preempt_enable();
#पूर्ण_अगर
पूर्ण


/**
 * Called to flush the icache on all cores
 */
अटल व्योम octeon_flush_icache_all(व्योम)
अणु
	octeon_flush_icache_all_cores(शून्य);
पूर्ण


/**
 * Called to flush all memory associated with a memory
 * context.
 *
 * @mm:	    Memory context to flush
 */
अटल व्योम octeon_flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * According to the R4K version of this file, CPUs without
	 * dcache aliases करोn't need to करो anything here
	 */
पूर्ण


/**
 * Flush a range of kernel addresses out of the icache
 *
 */
अटल व्योम octeon_flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	octeon_flush_icache_all_cores(शून्य);
पूर्ण


/**
 * Flush a range out of a vma
 *
 * @vma:    VMA to flush
 * @start:
 * @end:
 */
अटल व्योम octeon_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (vma->vm_flags & VM_EXEC)
		octeon_flush_icache_all_cores(vma);
पूर्ण


/**
 * Flush a specअगरic page of a vma
 *
 * @vma:    VMA to flush page क्रम
 * @page:   Page to flush
 * @pfn:
 */
अटल व्योम octeon_flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ page, अचिन्हित दीर्घ pfn)
अणु
	अगर (vma->vm_flags & VM_EXEC)
		octeon_flush_icache_all_cores(vma);
पूर्ण

अटल व्योम octeon_flush_kernel_vmap_range(अचिन्हित दीर्घ vaddr, पूर्णांक size)
अणु
	BUG();
पूर्ण

/**
 * Probe Octeon's caches
 *
 */
अटल व्योम probe_octeon(व्योम)
अणु
	अचिन्हित दीर्घ icache_size;
	अचिन्हित दीर्घ dcache_size;
	अचिन्हित पूर्णांक config1;
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	पूर्णांक cputype = current_cpu_type();

	config1 = पढ़ो_c0_config1();
	चयन (cputype) अणु
	हाल CPU_CAVIUM_OCTEON:
	हाल CPU_CAVIUM_OCTEON_PLUS:
		c->icache.linesz = 2 << ((config1 >> 19) & 7);
		c->icache.sets = 64 << ((config1 >> 22) & 7);
		c->icache.ways = 1 + ((config1 >> 16) & 7);
		c->icache.flags |= MIPS_CACHE_VTAG;
		icache_size =
			c->icache.sets * c->icache.ways * c->icache.linesz;
		c->icache.waybit = ffs(icache_size / c->icache.ways) - 1;
		c->dcache.linesz = 128;
		अगर (cputype == CPU_CAVIUM_OCTEON_PLUS)
			c->dcache.sets = 2; /* CN5XXX has two Dcache sets */
		अन्यथा
			c->dcache.sets = 1; /* CN3XXX has one Dcache set */
		c->dcache.ways = 64;
		dcache_size =
			c->dcache.sets * c->dcache.ways * c->dcache.linesz;
		c->dcache.waybit = ffs(dcache_size / c->dcache.ways) - 1;
		c->options |= MIPS_CPU_PREFETCH;
		अवरोध;

	हाल CPU_CAVIUM_OCTEON2:
		c->icache.linesz = 2 << ((config1 >> 19) & 7);
		c->icache.sets = 8;
		c->icache.ways = 37;
		c->icache.flags |= MIPS_CACHE_VTAG;
		icache_size = c->icache.sets * c->icache.ways * c->icache.linesz;

		c->dcache.linesz = 128;
		c->dcache.ways = 32;
		c->dcache.sets = 8;
		dcache_size = c->dcache.sets * c->dcache.ways * c->dcache.linesz;
		c->options |= MIPS_CPU_PREFETCH;
		अवरोध;

	हाल CPU_CAVIUM_OCTEON3:
		c->icache.linesz = 128;
		c->icache.sets = 16;
		c->icache.ways = 39;
		c->icache.flags |= MIPS_CACHE_VTAG;
		icache_size = c->icache.sets * c->icache.ways * c->icache.linesz;

		c->dcache.linesz = 128;
		c->dcache.ways = 32;
		c->dcache.sets = 8;
		dcache_size = c->dcache.sets * c->dcache.ways * c->dcache.linesz;
		c->options |= MIPS_CPU_PREFETCH;
		अवरोध;

	शेष:
		panic("Unsupported Cavium Networks CPU type");
		अवरोध;
	पूर्ण

	/* compute a couple of other cache variables */
	c->icache.waysize = icache_size / c->icache.ways;
	c->dcache.waysize = dcache_size / c->dcache.ways;

	c->icache.sets = icache_size / (c->icache.linesz * c->icache.ways);
	c->dcache.sets = dcache_size / (c->dcache.linesz * c->dcache.ways);

	अगर (smp_processor_id() == 0) अणु
		pr_info("Primary instruction cache %ldkB, %s, %d way, "
			"%d sets, linesize %d bytes.\n",
			icache_size >> 10,
			cpu_has_vtag_icache ?
				"virtually tagged" : "physically tagged",
			c->icache.ways, c->icache.sets, c->icache.linesz);

		pr_info("Primary data cache %ldkB, %d-way, %d sets, "
			"linesize %d bytes.\n",
			dcache_size >> 10, c->dcache.ways,
			c->dcache.sets, c->dcache.linesz);
	पूर्ण
पूर्ण

अटल व्योम  octeon_cache_error_setup(व्योम)
अणु
	बाह्य अक्षर except_vec2_octeon;
	set_handler(0x100, &except_vec2_octeon, 0x80);
पूर्ण

/**
 * Setup the Octeon cache flush routines
 *
 */
व्योम octeon_cache_init(व्योम)
अणु
	probe_octeon();

	shm_align_mask = PAGE_SIZE - 1;

	flush_cache_all			= octeon_flush_icache_all;
	__flush_cache_all		= octeon_flush_icache_all;
	flush_cache_mm			= octeon_flush_cache_mm;
	flush_cache_page		= octeon_flush_cache_page;
	flush_cache_range		= octeon_flush_cache_range;
	flush_icache_all		= octeon_flush_icache_all;
	flush_data_cache_page		= octeon_flush_data_cache_page;
	flush_icache_range		= octeon_flush_icache_range;
	local_flush_icache_range	= local_octeon_flush_icache_range;
	__flush_icache_user_range	= octeon_flush_icache_range;
	__local_flush_icache_user_range	= local_octeon_flush_icache_range;

	__flush_kernel_vmap_range	= octeon_flush_kernel_vmap_range;

	build_clear_page();
	build_copy_page();

	board_cache_error_setup = octeon_cache_error_setup;
पूर्ण

/*
 * Handle a cache error exception
 */
अटल RAW_NOTIFIER_HEAD(co_cache_error_chain);

पूर्णांक रेजिस्टर_co_cache_error_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस raw_notअगरier_chain_रेजिस्टर(&co_cache_error_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_co_cache_error_notअगरier);

पूर्णांक unरेजिस्टर_co_cache_error_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस raw_notअगरier_chain_unरेजिस्टर(&co_cache_error_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_co_cache_error_notअगरier);

अटल व्योम co_cache_error_call_notअगरiers(अचिन्हित दीर्घ val)
अणु
	पूर्णांक rv = raw_notअगरier_call_chain(&co_cache_error_chain, val, शून्य);
	अगर ((rv & ~NOTIFY_STOP_MASK) != NOTIFY_OK) अणु
		u64 dcache_err;
		अचिन्हित दीर्घ coreid = cvmx_get_core_num();
		u64 icache_err = पढ़ो_octeon_c0_icacheerr();

		अगर (val) अणु
			dcache_err = cache_err_dcache[coreid];
			cache_err_dcache[coreid] = 0;
		पूर्ण अन्यथा अणु
			dcache_err = पढ़ो_octeon_c0_dcacheerr();
		पूर्ण

		pr_err("Core%lu: Cache error exception:\n", coreid);
		pr_err("cp0_errorepc == %lx\n", पढ़ो_c0_errorepc());
		अगर (icache_err & 1) अणु
			pr_err("CacheErr (Icache) == %llx\n",
			       (अचिन्हित दीर्घ दीर्घ)icache_err);
			ग_लिखो_octeon_c0_icacheerr(0);
		पूर्ण
		अगर (dcache_err & 1) अणु
			pr_err("CacheErr (Dcache) == %llx\n",
			       (अचिन्हित दीर्घ दीर्घ)dcache_err);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Called when the the exception is recoverable
 */

यंत्रlinkage व्योम cache_parity_error_octeon_recoverable(व्योम)
अणु
	co_cache_error_call_notअगरiers(0);
पूर्ण

/**
 * Called when the the exception is not recoverable
 */

यंत्रlinkage व्योम cache_parity_error_octeon_non_recoverable(व्योम)
अणु
	co_cache_error_call_notअगरiers(1);
	panic("Can't handle cache error: nested exception");
पूर्ण
