<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r2300.c: R2000 and R3000 specअगरic mmu/cache code.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 *
 * with a lot of changes to make this thing work क्रम R3000s
 * Tx39XX R4k style caches added. HK
 * Copyright (C) 1998, 1999, 2000 Harald Koerfgen
 * Copyright (C) 1998 Gleb Raiko & Vladimir Roganov
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/isadep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>

/* For R3000 cores with R4000 style caches */
अटल अचिन्हित दीर्घ icache_size, dcache_size;		/* Size in bytes */

#समावेश <यंत्र/r4kcache.h>

/* This sequence is required to ensure icache is disabled immediately */
#घोषणा TX39_STOP_STREAMING() \
__यंत्र__ __अस्थिर__( \
	".set	 push\n\t" \
	".set	 noreorder\n\t" \
	"b	 1f\n\t" \
	"nop\n\t" \
	"1:\n\t" \
	".set pop" \
	)

/* TX39H-style cache flush routines. */
अटल व्योम tx39h_flush_icache_all(व्योम)
अणु
	अचिन्हित दीर्घ flags, config;

	/* disable icache (set ICE#) */
	local_irq_save(flags);
	config = पढ़ो_c0_conf();
	ग_लिखो_c0_conf(config & ~TX39_CONF_ICE);
	TX39_STOP_STREAMING();
	blast_icache16();
	ग_लिखो_c0_conf(config);
	local_irq_restore(flags);
पूर्ण

अटल व्योम tx39h_dma_cache_wback_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	/* Catch bad driver code */
	BUG_ON(size == 0);

	iob();
	blast_inv_dcache_range(addr, addr + size);
पूर्ण


/* TX39H2,TX39H3 */
अटल अंतरभूत व्योम tx39_blast_dcache_page(अचिन्हित दीर्घ addr)
अणु
	अगर (current_cpu_type() != CPU_TX3912)
		blast_dcache16_page(addr);
पूर्ण

अटल अंतरभूत व्योम tx39_blast_dcache_page_indexed(अचिन्हित दीर्घ addr)
अणु
	blast_dcache16_page_indexed(addr);
पूर्ण

अटल अंतरभूत व्योम tx39_blast_dcache(व्योम)
अणु
	blast_dcache16();
पूर्ण

अटल अंतरभूत व्योम tx39_blast_icache_page(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ flags, config;
	/* disable icache (set ICE#) */
	local_irq_save(flags);
	config = पढ़ो_c0_conf();
	ग_लिखो_c0_conf(config & ~TX39_CONF_ICE);
	TX39_STOP_STREAMING();
	blast_icache16_page(addr);
	ग_लिखो_c0_conf(config);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम tx39_blast_icache_page_indexed(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ flags, config;
	/* disable icache (set ICE#) */
	local_irq_save(flags);
	config = पढ़ो_c0_conf();
	ग_लिखो_c0_conf(config & ~TX39_CONF_ICE);
	TX39_STOP_STREAMING();
	blast_icache16_page_indexed(addr);
	ग_लिखो_c0_conf(config);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम tx39_blast_icache(व्योम)
अणु
	अचिन्हित दीर्घ flags, config;
	/* disable icache (set ICE#) */
	local_irq_save(flags);
	config = पढ़ो_c0_conf();
	ग_लिखो_c0_conf(config & ~TX39_CONF_ICE);
	TX39_STOP_STREAMING();
	blast_icache16();
	ग_लिखो_c0_conf(config);
	local_irq_restore(flags);
पूर्ण

अटल व्योम tx39__flush_cache_vmap(व्योम)
अणु
	tx39_blast_dcache();
पूर्ण

अटल व्योम tx39__flush_cache_vunmap(व्योम)
अणु
	tx39_blast_dcache();
पूर्ण

अटल अंतरभूत व्योम tx39_flush_cache_all(व्योम)
अणु
	अगर (!cpu_has_dc_aliases)
		वापस;

	tx39_blast_dcache();
पूर्ण

अटल अंतरभूत व्योम tx39___flush_cache_all(व्योम)
अणु
	tx39_blast_dcache();
	tx39_blast_icache();
पूर्ण

अटल व्योम tx39_flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (!cpu_has_dc_aliases)
		वापस;

	अगर (cpu_context(smp_processor_id(), mm) != 0)
		tx39_blast_dcache();
पूर्ण

अटल व्योम tx39_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (!cpu_has_dc_aliases)
		वापस;
	अगर (!(cpu_context(smp_processor_id(), vma->vm_mm)))
		वापस;

	tx39_blast_dcache();
पूर्ण

अटल व्योम tx39_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page, अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक exec = vma->vm_flags & VM_EXEC;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pmd_t *pmdp;
	pte_t *ptep;

	/*
	 * If ownes no valid ASID yet, cannot possibly have gotten
	 * this page पूर्णांकo the cache.
	 */
	अगर (cpu_context(smp_processor_id(), mm) == 0)
		वापस;

	page &= PAGE_MASK;
	pmdp = pmd_off(mm, page);
	ptep = pte_offset_kernel(pmdp, page);

	/*
	 * If the page isn't marked valid, the page cannot possibly be
	 * in the cache.
	 */
	अगर (!(pte_val(*ptep) & _PAGE_PRESENT))
		वापस;

	/*
	 * Doing flushes क्रम another ASID than the current one is
	 * too dअगरficult since stupid R4k caches करो a TLB translation
	 * क्रम every cache flush operation.  So we करो indexed flushes
	 * in that हाल, which करोesn't overly flush the cache too much.
	 */
	अगर ((mm == current->active_mm) && (pte_val(*ptep) & _PAGE_VALID)) अणु
		अगर (cpu_has_dc_aliases || exec)
			tx39_blast_dcache_page(page);
		अगर (exec)
			tx39_blast_icache_page(page);

		वापस;
	पूर्ण

	/*
	 * Do indexed flush, too much work to get the (possible) TLB refills
	 * to work correctly.
	 */
	अगर (cpu_has_dc_aliases || exec)
		tx39_blast_dcache_page_indexed(page);
	अगर (exec)
		tx39_blast_icache_page_indexed(page);
पूर्ण

अटल व्योम local_tx39_flush_data_cache_page(व्योम * addr)
अणु
	tx39_blast_dcache_page((अचिन्हित दीर्घ)addr);
पूर्ण

अटल व्योम tx39_flush_data_cache_page(अचिन्हित दीर्घ addr)
अणु
	tx39_blast_dcache_page(addr);
पूर्ण

अटल व्योम tx39_flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (end - start > dcache_size)
		tx39_blast_dcache();
	अन्यथा
		रक्षित_blast_dcache_range(start, end);

	अगर (end - start > icache_size)
		tx39_blast_icache();
	अन्यथा अणु
		अचिन्हित दीर्घ flags, config;
		/* disable icache (set ICE#) */
		local_irq_save(flags);
		config = पढ़ो_c0_conf();
		ग_लिखो_c0_conf(config & ~TX39_CONF_ICE);
		TX39_STOP_STREAMING();
		रक्षित_blast_icache_range(start, end);
		ग_लिखो_c0_conf(config);
		local_irq_restore(flags);
	पूर्ण
पूर्ण

अटल व्योम tx39_flush_kernel_vmap_range(अचिन्हित दीर्घ vaddr, पूर्णांक size)
अणु
	BUG();
पूर्ण

अटल व्योम tx39_dma_cache_wback_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ end;

	अगर (((size | addr) & (PAGE_SIZE - 1)) == 0) अणु
		end = addr + size;
		करो अणु
			tx39_blast_dcache_page(addr);
			addr += PAGE_SIZE;
		पूर्ण जबतक(addr != end);
	पूर्ण अन्यथा अगर (size > dcache_size) अणु
		tx39_blast_dcache();
	पूर्ण अन्यथा अणु
		blast_dcache_range(addr, addr + size);
	पूर्ण
पूर्ण

अटल व्योम tx39_dma_cache_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ end;

	अगर (((size | addr) & (PAGE_SIZE - 1)) == 0) अणु
		end = addr + size;
		करो अणु
			tx39_blast_dcache_page(addr);
			addr += PAGE_SIZE;
		पूर्ण जबतक(addr != end);
	पूर्ण अन्यथा अगर (size > dcache_size) अणु
		tx39_blast_dcache();
	पूर्ण अन्यथा अणु
		blast_inv_dcache_range(addr, addr + size);
	पूर्ण
पूर्ण

अटल __init व्योम tx39_probe_cache(व्योम)
अणु
	अचिन्हित दीर्घ config;

	config = पढ़ो_c0_conf();

	icache_size = 1 << (10 + ((config & TX39_CONF_ICS_MASK) >>
				  TX39_CONF_ICS_SHIFT));
	dcache_size = 1 << (10 + ((config & TX39_CONF_DCS_MASK) >>
				  TX39_CONF_DCS_SHIFT));

	current_cpu_data.icache.linesz = 16;
	चयन (current_cpu_type()) अणु
	हाल CPU_TX3912:
		current_cpu_data.icache.ways = 1;
		current_cpu_data.dcache.ways = 1;
		current_cpu_data.dcache.linesz = 4;
		अवरोध;

	हाल CPU_TX3927:
		current_cpu_data.icache.ways = 2;
		current_cpu_data.dcache.ways = 2;
		current_cpu_data.dcache.linesz = 16;
		अवरोध;

	हाल CPU_TX3922:
	शेष:
		current_cpu_data.icache.ways = 1;
		current_cpu_data.dcache.ways = 1;
		current_cpu_data.dcache.linesz = 16;
		अवरोध;
	पूर्ण
पूर्ण

व्योम tx39_cache_init(व्योम)
अणु
	बाह्य व्योम build_clear_page(व्योम);
	बाह्य व्योम build_copy_page(व्योम);
	अचिन्हित दीर्घ config;

	config = पढ़ो_c0_conf();
	config &= ~TX39_CONF_WBON;
	ग_लिखो_c0_conf(config);

	tx39_probe_cache();

	चयन (current_cpu_type()) अणु
	हाल CPU_TX3912:
		/* TX39/H core (ग_लिखोthru direct-map cache) */
		__flush_cache_vmap	= tx39__flush_cache_vmap;
		__flush_cache_vunmap	= tx39__flush_cache_vunmap;
		flush_cache_all = tx39h_flush_icache_all;
		__flush_cache_all	= tx39h_flush_icache_all;
		flush_cache_mm		= (व्योम *) tx39h_flush_icache_all;
		flush_cache_range	= (व्योम *) tx39h_flush_icache_all;
		flush_cache_page	= (व्योम *) tx39h_flush_icache_all;
		flush_icache_range	= (व्योम *) tx39h_flush_icache_all;
		local_flush_icache_range = (व्योम *) tx39h_flush_icache_all;

		local_flush_data_cache_page	= (व्योम *) tx39h_flush_icache_all;
		flush_data_cache_page	= (व्योम *) tx39h_flush_icache_all;

		_dma_cache_wback_inv	= tx39h_dma_cache_wback_inv;

		shm_align_mask		= PAGE_SIZE - 1;

		अवरोध;

	हाल CPU_TX3922:
	हाल CPU_TX3927:
	शेष:
		/* TX39/H2,H3 core (ग_लिखोback 2way-set-associative cache) */
		/* board-dependent init code may set WBON */

		__flush_cache_vmap	= tx39__flush_cache_vmap;
		__flush_cache_vunmap	= tx39__flush_cache_vunmap;

		flush_cache_all = tx39_flush_cache_all;
		__flush_cache_all = tx39___flush_cache_all;
		flush_cache_mm = tx39_flush_cache_mm;
		flush_cache_range = tx39_flush_cache_range;
		flush_cache_page = tx39_flush_cache_page;
		flush_icache_range = tx39_flush_icache_range;
		local_flush_icache_range = tx39_flush_icache_range;

		__flush_kernel_vmap_range = tx39_flush_kernel_vmap_range;

		local_flush_data_cache_page = local_tx39_flush_data_cache_page;
		flush_data_cache_page = tx39_flush_data_cache_page;

		_dma_cache_wback_inv = tx39_dma_cache_wback_inv;
		_dma_cache_wback = tx39_dma_cache_wback_inv;
		_dma_cache_inv = tx39_dma_cache_inv;

		shm_align_mask = max_t(अचिन्हित दीर्घ,
				       (dcache_size / current_cpu_data.dcache.ways) - 1,
				       PAGE_SIZE - 1);

		अवरोध;
	पूर्ण

	__flush_icache_user_range = flush_icache_range;
	__local_flush_icache_user_range = local_flush_icache_range;

	current_cpu_data.icache.waysize = icache_size / current_cpu_data.icache.ways;
	current_cpu_data.dcache.waysize = dcache_size / current_cpu_data.dcache.ways;

	current_cpu_data.icache.sets =
		current_cpu_data.icache.waysize / current_cpu_data.icache.linesz;
	current_cpu_data.dcache.sets =
		current_cpu_data.dcache.waysize / current_cpu_data.dcache.linesz;

	अगर (current_cpu_data.dcache.waysize > PAGE_SIZE)
		current_cpu_data.dcache.flags |= MIPS_CACHE_ALIASES;

	current_cpu_data.icache.waybit = 0;
	current_cpu_data.dcache.waybit = 0;

	pr_info("Primary instruction cache %ldkB, linesize %d bytes\n",
		icache_size >> 10, current_cpu_data.icache.linesz);
	pr_info("Primary data cache %ldkB, linesize %d bytes\n",
		dcache_size >> 10, current_cpu_data.dcache.linesz);

	build_clear_page();
	build_copy_page();
	tx39h_flush_icache_all();
पूर्ण
