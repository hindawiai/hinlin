<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002 Ralf Baechle (ralf@gnu.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#समावेश <linux/cpu_pm.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/linkage.h>
#समावेश <linux/preempt.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-map-ops.h> /* क्रम dma_शेष_coherent */

#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/war.h>
#समावेश <यंत्र/cacheflush.h> /* क्रम run_uncached() */
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/mips-cps.h>

/*
 * Bits describing what cache ops an SMP callback function may perक्रमm.
 *
 * R4K_HIT   -	Virtual user or kernel address based cache operations. The
 *		active_mm must be checked beक्रमe using user addresses, falling
 *		back to kmap.
 * R4K_INDEX -	Index based cache operations.
 */

#घोषणा R4K_HIT		BIT(0)
#घोषणा R4K_INDEX	BIT(1)

/**
 * r4k_op_needs_ipi() - Decide अगर a cache op needs to be करोne on every core.
 * @type:	Type of cache operations (R4K_HIT or R4K_INDEX).
 *
 * Decides whether a cache op needs to be perक्रमmed on every core in the प्रणाली.
 * This may change depending on the @type of cache operation, as well as the set
 * of online CPUs, so preemption should be disabled by the caller to prevent CPU
 * hotplug from changing the result.
 *
 * Returns:	1 अगर the cache operation @type should be करोne on every core in
 *		the प्रणाली.
 *		0 अगर the cache operation @type is globalized and only needs to
 *		be perक्रमmed on a simple CPU.
 */
अटल अंतरभूत bool r4k_op_needs_ipi(अचिन्हित पूर्णांक type)
अणु
	/* The MIPS Coherence Manager (CM) globalizes address-based cache ops */
	अगर (type == R4K_HIT && mips_cm_present())
		वापस false;

	/*
	 * Hardware करोesn't globalize the required cache ops, so SMP calls may
	 * be needed, but only अगर there are क्रमeign CPUs (non-siblings with
	 * separate caches).
	 */
	/* cpu_क्रमeign_map[] undeclared when !CONFIG_SMP */
#अगर_घोषित CONFIG_SMP
	वापस !cpumask_empty(&cpu_क्रमeign_map[0]);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/*
 * Special Variant of smp_call_function क्रम use by cache functions:
 *
 *  o No वापस value
 *  o collapses to normal function call on UP kernels
 *  o collapses to normal function call on प्रणालीs with a single shared
 *    primary cache.
 *  o करोesn't disable पूर्णांकerrupts on the local CPU
 */
अटल अंतरभूत व्योम r4k_on_each_cpu(अचिन्हित पूर्णांक type,
				   व्योम (*func)(व्योम *info), व्योम *info)
अणु
	preempt_disable();
	अगर (r4k_op_needs_ipi(type))
		smp_call_function_many(&cpu_क्रमeign_map[smp_processor_id()],
				       func, info, 1);
	func(info);
	preempt_enable();
पूर्ण

/*
 * Must die.
 */
अटल अचिन्हित दीर्घ icache_size __पढ़ो_mostly;
अटल अचिन्हित दीर्घ dcache_size __पढ़ो_mostly;
अटल अचिन्हित दीर्घ vcache_size __पढ़ो_mostly;
अटल अचिन्हित दीर्घ scache_size __पढ़ो_mostly;

/*
 * Dummy cache handling routines क्रम machines without boardcaches
 */
अटल व्योम cache_noop(व्योम) अणुपूर्ण

अटल काष्ठा bcache_ops no_sc_ops = अणु
	.bc_enable = (व्योम *)cache_noop,
	.bc_disable = (व्योम *)cache_noop,
	.bc_wback_inv = (व्योम *)cache_noop,
	.bc_inv = (व्योम *)cache_noop
पूर्ण;

काष्ठा bcache_ops *bcops = &no_sc_ops;

#घोषणा cpu_is_r4600_v1_x()	((पढ़ो_c0_prid() & 0xfffffff0) == 0x00002010)
#घोषणा cpu_is_r4600_v2_x()	((पढ़ो_c0_prid() & 0xfffffff0) == 0x00002020)

#घोषणा R4600_HIT_CACHEOP_WAR_IMPL					\
करो अणु									\
	अगर (IS_ENABLED(CONFIG_WAR_R4600_V2_HIT_CACHEOP) &&		\
	    cpu_is_r4600_v2_x())					\
		*(अस्थिर अचिन्हित दीर्घ *)CKSEG1;			\
	अगर (IS_ENABLED(CONFIG_WAR_R4600_V1_HIT_CACHEOP))					\
		__यंत्र__ __अस्थिर__("nop;nop;nop;nop");		\
पूर्ण जबतक (0)

अटल व्योम (*r4k_blast_dcache_page)(अचिन्हित दीर्घ addr);

अटल अंतरभूत व्योम r4k_blast_dcache_page_dc32(अचिन्हित दीर्घ addr)
अणु
	R4600_HIT_CACHEOP_WAR_IMPL;
	blast_dcache32_page(addr);
पूर्ण

अटल अंतरभूत व्योम r4k_blast_dcache_page_dc64(अचिन्हित दीर्घ addr)
अणु
	blast_dcache64_page(addr);
पूर्ण

अटल अंतरभूत व्योम r4k_blast_dcache_page_dc128(अचिन्हित दीर्घ addr)
अणु
	blast_dcache128_page(addr);
पूर्ण

अटल व्योम r4k_blast_dcache_page_setup(व्योम)
अणु
	अचिन्हित दीर्घ  dc_lsize = cpu_dcache_line_size();

	चयन (dc_lsize) अणु
	हाल 0:
		r4k_blast_dcache_page = (व्योम *)cache_noop;
		अवरोध;
	हाल 16:
		r4k_blast_dcache_page = blast_dcache16_page;
		अवरोध;
	हाल 32:
		r4k_blast_dcache_page = r4k_blast_dcache_page_dc32;
		अवरोध;
	हाल 64:
		r4k_blast_dcache_page = r4k_blast_dcache_page_dc64;
		अवरोध;
	हाल 128:
		r4k_blast_dcache_page = r4k_blast_dcache_page_dc128;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_EVA
#घोषणा r4k_blast_dcache_user_page  r4k_blast_dcache_page
#अन्यथा

अटल व्योम (*r4k_blast_dcache_user_page)(अचिन्हित दीर्घ addr);

अटल व्योम r4k_blast_dcache_user_page_setup(व्योम)
अणु
	अचिन्हित दीर्घ  dc_lsize = cpu_dcache_line_size();

	अगर (dc_lsize == 0)
		r4k_blast_dcache_user_page = (व्योम *)cache_noop;
	अन्यथा अगर (dc_lsize == 16)
		r4k_blast_dcache_user_page = blast_dcache16_user_page;
	अन्यथा अगर (dc_lsize == 32)
		r4k_blast_dcache_user_page = blast_dcache32_user_page;
	अन्यथा अगर (dc_lsize == 64)
		r4k_blast_dcache_user_page = blast_dcache64_user_page;
पूर्ण

#पूर्ण_अगर

अटल व्योम (* r4k_blast_dcache_page_indexed)(अचिन्हित दीर्घ addr);

अटल व्योम r4k_blast_dcache_page_indexed_setup(व्योम)
अणु
	अचिन्हित दीर्घ dc_lsize = cpu_dcache_line_size();

	अगर (dc_lsize == 0)
		r4k_blast_dcache_page_indexed = (व्योम *)cache_noop;
	अन्यथा अगर (dc_lsize == 16)
		r4k_blast_dcache_page_indexed = blast_dcache16_page_indexed;
	अन्यथा अगर (dc_lsize == 32)
		r4k_blast_dcache_page_indexed = blast_dcache32_page_indexed;
	अन्यथा अगर (dc_lsize == 64)
		r4k_blast_dcache_page_indexed = blast_dcache64_page_indexed;
	अन्यथा अगर (dc_lsize == 128)
		r4k_blast_dcache_page_indexed = blast_dcache128_page_indexed;
पूर्ण

व्योम (* r4k_blast_dcache)(व्योम);
EXPORT_SYMBOL(r4k_blast_dcache);

अटल व्योम r4k_blast_dcache_setup(व्योम)
अणु
	अचिन्हित दीर्घ dc_lsize = cpu_dcache_line_size();

	अगर (dc_lsize == 0)
		r4k_blast_dcache = (व्योम *)cache_noop;
	अन्यथा अगर (dc_lsize == 16)
		r4k_blast_dcache = blast_dcache16;
	अन्यथा अगर (dc_lsize == 32)
		r4k_blast_dcache = blast_dcache32;
	अन्यथा अगर (dc_lsize == 64)
		r4k_blast_dcache = blast_dcache64;
	अन्यथा अगर (dc_lsize == 128)
		r4k_blast_dcache = blast_dcache128;
पूर्ण

/* क्रमce code alignment (used क्रम CONFIG_WAR_TX49XX_ICACHE_INDEX_INV) */
#घोषणा JUMP_TO_ALIGN(order) \
	__यंत्र__ __अस्थिर__( \
		"b\t1f\n\t" \
		".align\t" #order "\n\t" \
		"1:\n\t" \
		)
#घोषणा CACHE32_UNROLL32_ALIGN	JUMP_TO_ALIGN(10) /* 32 * 32 = 1024 */
#घोषणा CACHE32_UNROLL32_ALIGN2 JUMP_TO_ALIGN(11)

अटल अंतरभूत व्योम blast_r4600_v1_icache32(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	blast_icache32();
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम tx49_blast_icache32(व्योम)
अणु
	अचिन्हित दीर्घ start = INDEX_BASE;
	अचिन्हित दीर्घ end = start + current_cpu_data.icache.waysize;
	अचिन्हित दीर्घ ws_inc = 1UL << current_cpu_data.icache.waybit;
	अचिन्हित दीर्घ ws_end = current_cpu_data.icache.ways <<
			       current_cpu_data.icache.waybit;
	अचिन्हित दीर्घ ws, addr;

	CACHE32_UNROLL32_ALIGN2;
	/* I'm in even chunk.  blast odd chunks */
	क्रम (ws = 0; ws < ws_end; ws += ws_inc)
		क्रम (addr = start + 0x400; addr < end; addr += 0x400 * 2)
			cache_unroll(32, kernel_cache, Index_Invalidate_I,
				     addr | ws, 32);
	CACHE32_UNROLL32_ALIGN;
	/* I'm in odd chunk.  blast even chunks */
	क्रम (ws = 0; ws < ws_end; ws += ws_inc)
		क्रम (addr = start; addr < end; addr += 0x400 * 2)
			cache_unroll(32, kernel_cache, Index_Invalidate_I,
				     addr | ws, 32);
पूर्ण

अटल अंतरभूत व्योम blast_icache32_r4600_v1_page_indexed(अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	blast_icache32_page_indexed(page);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम tx49_blast_icache32_page_indexed(अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ indexmask = current_cpu_data.icache.waysize - 1;
	अचिन्हित दीर्घ start = INDEX_BASE + (page & indexmask);
	अचिन्हित दीर्घ end = start + PAGE_SIZE;
	अचिन्हित दीर्घ ws_inc = 1UL << current_cpu_data.icache.waybit;
	अचिन्हित दीर्घ ws_end = current_cpu_data.icache.ways <<
			       current_cpu_data.icache.waybit;
	अचिन्हित दीर्घ ws, addr;

	CACHE32_UNROLL32_ALIGN2;
	/* I'm in even chunk.  blast odd chunks */
	क्रम (ws = 0; ws < ws_end; ws += ws_inc)
		क्रम (addr = start + 0x400; addr < end; addr += 0x400 * 2)
			cache_unroll(32, kernel_cache, Index_Invalidate_I,
				     addr | ws, 32);
	CACHE32_UNROLL32_ALIGN;
	/* I'm in odd chunk.  blast even chunks */
	क्रम (ws = 0; ws < ws_end; ws += ws_inc)
		क्रम (addr = start; addr < end; addr += 0x400 * 2)
			cache_unroll(32, kernel_cache, Index_Invalidate_I,
				     addr | ws, 32);
पूर्ण

अटल व्योम (* r4k_blast_icache_page)(अचिन्हित दीर्घ addr);

अटल व्योम r4k_blast_icache_page_setup(व्योम)
अणु
	अचिन्हित दीर्घ ic_lsize = cpu_icache_line_size();

	अगर (ic_lsize == 0)
		r4k_blast_icache_page = (व्योम *)cache_noop;
	अन्यथा अगर (ic_lsize == 16)
		r4k_blast_icache_page = blast_icache16_page;
	अन्यथा अगर (ic_lsize == 32 && current_cpu_type() == CPU_LOONGSON2EF)
		r4k_blast_icache_page = loongson2_blast_icache32_page;
	अन्यथा अगर (ic_lsize == 32)
		r4k_blast_icache_page = blast_icache32_page;
	अन्यथा अगर (ic_lsize == 64)
		r4k_blast_icache_page = blast_icache64_page;
	अन्यथा अगर (ic_lsize == 128)
		r4k_blast_icache_page = blast_icache128_page;
पूर्ण

#अगर_अघोषित CONFIG_EVA
#घोषणा r4k_blast_icache_user_page  r4k_blast_icache_page
#अन्यथा

अटल व्योम (*r4k_blast_icache_user_page)(अचिन्हित दीर्घ addr);

अटल व्योम r4k_blast_icache_user_page_setup(व्योम)
अणु
	अचिन्हित दीर्घ ic_lsize = cpu_icache_line_size();

	अगर (ic_lsize == 0)
		r4k_blast_icache_user_page = (व्योम *)cache_noop;
	अन्यथा अगर (ic_lsize == 16)
		r4k_blast_icache_user_page = blast_icache16_user_page;
	अन्यथा अगर (ic_lsize == 32)
		r4k_blast_icache_user_page = blast_icache32_user_page;
	अन्यथा अगर (ic_lsize == 64)
		r4k_blast_icache_user_page = blast_icache64_user_page;
पूर्ण

#पूर्ण_अगर

अटल व्योम (* r4k_blast_icache_page_indexed)(अचिन्हित दीर्घ addr);

अटल व्योम r4k_blast_icache_page_indexed_setup(व्योम)
अणु
	अचिन्हित दीर्घ ic_lsize = cpu_icache_line_size();

	अगर (ic_lsize == 0)
		r4k_blast_icache_page_indexed = (व्योम *)cache_noop;
	अन्यथा अगर (ic_lsize == 16)
		r4k_blast_icache_page_indexed = blast_icache16_page_indexed;
	अन्यथा अगर (ic_lsize == 32) अणु
		अगर (IS_ENABLED(CONFIG_WAR_R4600_V1_INDEX_ICACHEOP) &&
		    cpu_is_r4600_v1_x())
			r4k_blast_icache_page_indexed =
				blast_icache32_r4600_v1_page_indexed;
		अन्यथा अगर (IS_ENABLED(CONFIG_WAR_TX49XX_ICACHE_INDEX_INV))
			r4k_blast_icache_page_indexed =
				tx49_blast_icache32_page_indexed;
		अन्यथा अगर (current_cpu_type() == CPU_LOONGSON2EF)
			r4k_blast_icache_page_indexed =
				loongson2_blast_icache32_page_indexed;
		अन्यथा
			r4k_blast_icache_page_indexed =
				blast_icache32_page_indexed;
	पूर्ण अन्यथा अगर (ic_lsize == 64)
		r4k_blast_icache_page_indexed = blast_icache64_page_indexed;
पूर्ण

व्योम (* r4k_blast_icache)(व्योम);
EXPORT_SYMBOL(r4k_blast_icache);

अटल व्योम r4k_blast_icache_setup(व्योम)
अणु
	अचिन्हित दीर्घ ic_lsize = cpu_icache_line_size();

	अगर (ic_lsize == 0)
		r4k_blast_icache = (व्योम *)cache_noop;
	अन्यथा अगर (ic_lsize == 16)
		r4k_blast_icache = blast_icache16;
	अन्यथा अगर (ic_lsize == 32) अणु
		अगर (IS_ENABLED(CONFIG_WAR_R4600_V1_INDEX_ICACHEOP) &&
		    cpu_is_r4600_v1_x())
			r4k_blast_icache = blast_r4600_v1_icache32;
		अन्यथा अगर (IS_ENABLED(CONFIG_WAR_TX49XX_ICACHE_INDEX_INV))
			r4k_blast_icache = tx49_blast_icache32;
		अन्यथा अगर (current_cpu_type() == CPU_LOONGSON2EF)
			r4k_blast_icache = loongson2_blast_icache32;
		अन्यथा
			r4k_blast_icache = blast_icache32;
	पूर्ण अन्यथा अगर (ic_lsize == 64)
		r4k_blast_icache = blast_icache64;
	अन्यथा अगर (ic_lsize == 128)
		r4k_blast_icache = blast_icache128;
पूर्ण

अटल व्योम (* r4k_blast_scache_page)(अचिन्हित दीर्घ addr);

अटल व्योम r4k_blast_scache_page_setup(व्योम)
अणु
	अचिन्हित दीर्घ sc_lsize = cpu_scache_line_size();

	अगर (scache_size == 0)
		r4k_blast_scache_page = (व्योम *)cache_noop;
	अन्यथा अगर (sc_lsize == 16)
		r4k_blast_scache_page = blast_scache16_page;
	अन्यथा अगर (sc_lsize == 32)
		r4k_blast_scache_page = blast_scache32_page;
	अन्यथा अगर (sc_lsize == 64)
		r4k_blast_scache_page = blast_scache64_page;
	अन्यथा अगर (sc_lsize == 128)
		r4k_blast_scache_page = blast_scache128_page;
पूर्ण

अटल व्योम (* r4k_blast_scache_page_indexed)(अचिन्हित दीर्घ addr);

अटल व्योम r4k_blast_scache_page_indexed_setup(व्योम)
अणु
	अचिन्हित दीर्घ sc_lsize = cpu_scache_line_size();

	अगर (scache_size == 0)
		r4k_blast_scache_page_indexed = (व्योम *)cache_noop;
	अन्यथा अगर (sc_lsize == 16)
		r4k_blast_scache_page_indexed = blast_scache16_page_indexed;
	अन्यथा अगर (sc_lsize == 32)
		r4k_blast_scache_page_indexed = blast_scache32_page_indexed;
	अन्यथा अगर (sc_lsize == 64)
		r4k_blast_scache_page_indexed = blast_scache64_page_indexed;
	अन्यथा अगर (sc_lsize == 128)
		r4k_blast_scache_page_indexed = blast_scache128_page_indexed;
पूर्ण

अटल व्योम (* r4k_blast_scache)(व्योम);

अटल व्योम r4k_blast_scache_setup(व्योम)
अणु
	अचिन्हित दीर्घ sc_lsize = cpu_scache_line_size();

	अगर (scache_size == 0)
		r4k_blast_scache = (व्योम *)cache_noop;
	अन्यथा अगर (sc_lsize == 16)
		r4k_blast_scache = blast_scache16;
	अन्यथा अगर (sc_lsize == 32)
		r4k_blast_scache = blast_scache32;
	अन्यथा अगर (sc_lsize == 64)
		r4k_blast_scache = blast_scache64;
	अन्यथा अगर (sc_lsize == 128)
		r4k_blast_scache = blast_scache128;
पूर्ण

अटल व्योम (*r4k_blast_scache_node)(दीर्घ node);

अटल व्योम r4k_blast_scache_node_setup(व्योम)
अणु
	अचिन्हित दीर्घ sc_lsize = cpu_scache_line_size();

	अगर (current_cpu_type() != CPU_LOONGSON64)
		r4k_blast_scache_node = (व्योम *)cache_noop;
	अन्यथा अगर (sc_lsize == 16)
		r4k_blast_scache_node = blast_scache16_node;
	अन्यथा अगर (sc_lsize == 32)
		r4k_blast_scache_node = blast_scache32_node;
	अन्यथा अगर (sc_lsize == 64)
		r4k_blast_scache_node = blast_scache64_node;
	अन्यथा अगर (sc_lsize == 128)
		r4k_blast_scache_node = blast_scache128_node;
पूर्ण

अटल अंतरभूत व्योम local_r4k___flush_cache_all(व्योम * args)
अणु
	चयन (current_cpu_type()) अणु
	हाल CPU_LOONGSON2EF:
	हाल CPU_R4000SC:
	हाल CPU_R4000MC:
	हाल CPU_R4400SC:
	हाल CPU_R4400MC:
	हाल CPU_R10000:
	हाल CPU_R12000:
	हाल CPU_R14000:
	हाल CPU_R16000:
		/*
		 * These caches are inclusive caches, that is, अगर something
		 * is not cached in the S-cache, we know it also won't be
		 * in one of the primary caches.
		 */
		r4k_blast_scache();
		अवरोध;

	हाल CPU_LOONGSON64:
		/* Use get_ebase_cpunum() क्रम both NUMA=y/n */
		r4k_blast_scache_node(get_ebase_cpunum() >> 2);
		अवरोध;

	हाल CPU_BMIPS5000:
		r4k_blast_scache();
		__sync();
		अवरोध;

	शेष:
		r4k_blast_dcache();
		r4k_blast_icache();
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम r4k___flush_cache_all(व्योम)
अणु
	r4k_on_each_cpu(R4K_INDEX, local_r4k___flush_cache_all, शून्य);
पूर्ण

/**
 * has_valid_asid() - Determine अगर an mm alपढ़ोy has an ASID.
 * @mm:		Memory map.
 * @type:	R4K_HIT or R4K_INDEX, type of cache op.
 *
 * Determines whether @mm alपढ़ोy has an ASID on any of the CPUs which cache ops
 * of type @type within an r4k_on_each_cpu() call will affect. If
 * r4k_on_each_cpu() करोes an SMP call to a single VPE in each core, then the
 * scope of the operation is confined to sibling CPUs, otherwise all online CPUs
 * will need to be checked.
 *
 * Must be called in non-preemptive context.
 *
 * Returns:	1 अगर the CPUs affected by @type cache ops have an ASID क्रम @mm.
 *		0 otherwise.
 */
अटल अंतरभूत पूर्णांक has_valid_asid(स्थिर काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर cpumask_t *mask = cpu_present_mask;

	अगर (cpu_has_mmid)
		वापस cpu_context(0, mm) != 0;

	/* cpu_sibling_map[] undeclared when !CONFIG_SMP */
#अगर_घोषित CONFIG_SMP
	/*
	 * If r4k_on_each_cpu करोes SMP calls, it करोes them to a single VPE in
	 * each क्रमeign core, so we only need to worry about siblings.
	 * Otherwise we need to worry about all present CPUs.
	 */
	अगर (r4k_op_needs_ipi(type))
		mask = &cpu_sibling_map[smp_processor_id()];
#पूर्ण_अगर
	क्रम_each_cpu(i, mask)
		अगर (cpu_context(i, mm))
			वापस 1;
	वापस 0;
पूर्ण

अटल व्योम r4k__flush_cache_vmap(व्योम)
अणु
	r4k_blast_dcache();
पूर्ण

अटल व्योम r4k__flush_cache_vunmap(व्योम)
अणु
	r4k_blast_dcache();
पूर्ण

/*
 * Note: flush_tlb_range() assumes flush_cache_range() sufficiently flushes
 * whole caches when vma is executable.
 */
अटल अंतरभूत व्योम local_r4k_flush_cache_range(व्योम * args)
अणु
	काष्ठा vm_area_काष्ठा *vma = args;
	पूर्णांक exec = vma->vm_flags & VM_EXEC;

	अगर (!has_valid_asid(vma->vm_mm, R4K_INDEX))
		वापस;

	/*
	 * If dcache can alias, we must blast it since mapping is changing.
	 * If executable, we must ensure any dirty lines are written back far
	 * enough to be visible to icache.
	 */
	अगर (cpu_has_dc_aliases || (exec && !cpu_has_ic_fills_f_dc))
		r4k_blast_dcache();
	/* If executable, blast stale lines from icache */
	अगर (exec)
		r4k_blast_icache();
पूर्ण

अटल व्योम r4k_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक exec = vma->vm_flags & VM_EXEC;

	अगर (cpu_has_dc_aliases || exec)
		r4k_on_each_cpu(R4K_INDEX, local_r4k_flush_cache_range, vma);
पूर्ण

अटल अंतरभूत व्योम local_r4k_flush_cache_mm(व्योम * args)
अणु
	काष्ठा mm_काष्ठा *mm = args;

	अगर (!has_valid_asid(mm, R4K_INDEX))
		वापस;

	/*
	 * Kludge alert.  For obscure reasons R4000SC and R4400SC go nuts अगर we
	 * only flush the primary caches but R1x000 behave sane ...
	 * R4000SC and R4400SC indexed S-cache ops also invalidate primary
	 * caches, so we can bail out early.
	 */
	अगर (current_cpu_type() == CPU_R4000SC ||
	    current_cpu_type() == CPU_R4000MC ||
	    current_cpu_type() == CPU_R4400SC ||
	    current_cpu_type() == CPU_R4400MC) अणु
		r4k_blast_scache();
		वापस;
	पूर्ण

	r4k_blast_dcache();
पूर्ण

अटल व्योम r4k_flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (!cpu_has_dc_aliases)
		वापस;

	r4k_on_each_cpu(R4K_INDEX, local_r4k_flush_cache_mm, mm);
पूर्ण

काष्ठा flush_cache_page_args अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ pfn;
पूर्ण;

अटल अंतरभूत व्योम local_r4k_flush_cache_page(व्योम *args)
अणु
	काष्ठा flush_cache_page_args *fcp_args = args;
	काष्ठा vm_area_काष्ठा *vma = fcp_args->vma;
	अचिन्हित दीर्घ addr = fcp_args->addr;
	काष्ठा page *page = pfn_to_page(fcp_args->pfn);
	पूर्णांक exec = vma->vm_flags & VM_EXEC;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	पूर्णांक map_coherent = 0;
	pmd_t *pmdp;
	pte_t *ptep;
	व्योम *vaddr;

	/*
	 * If owns no valid ASID yet, cannot possibly have gotten
	 * this page पूर्णांकo the cache.
	 */
	अगर (!has_valid_asid(mm, R4K_HIT))
		वापस;

	addr &= PAGE_MASK;
	pmdp = pmd_off(mm, addr);
	ptep = pte_offset_kernel(pmdp, addr);

	/*
	 * If the page isn't marked valid, the page cannot possibly be
	 * in the cache.
	 */
	अगर (!(pte_present(*ptep)))
		वापस;

	अगर ((mm == current->active_mm) && (pte_val(*ptep) & _PAGE_VALID))
		vaddr = शून्य;
	अन्यथा अणु
		/*
		 * Use kmap_coherent or kmap_atomic to करो flushes क्रम
		 * another ASID than the current one.
		 */
		map_coherent = (cpu_has_dc_aliases &&
				page_mapcount(page) &&
				!Page_dcache_dirty(page));
		अगर (map_coherent)
			vaddr = kmap_coherent(page, addr);
		अन्यथा
			vaddr = kmap_atomic(page);
		addr = (अचिन्हित दीर्घ)vaddr;
	पूर्ण

	अगर (cpu_has_dc_aliases || (exec && !cpu_has_ic_fills_f_dc)) अणु
		vaddr ? r4k_blast_dcache_page(addr) :
			r4k_blast_dcache_user_page(addr);
		अगर (exec && !cpu_icache_snoops_remote_store)
			r4k_blast_scache_page(addr);
	पूर्ण
	अगर (exec) अणु
		अगर (vaddr && cpu_has_vtag_icache && mm == current->active_mm) अणु
			drop_mmu_context(mm);
		पूर्ण अन्यथा
			vaddr ? r4k_blast_icache_page(addr) :
				r4k_blast_icache_user_page(addr);
	पूर्ण

	अगर (vaddr) अणु
		अगर (map_coherent)
			kunmap_coherent();
		अन्यथा
			kunmap_atomic(vaddr);
	पूर्ण
पूर्ण

अटल व्योम r4k_flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा flush_cache_page_args args;

	args.vma = vma;
	args.addr = addr;
	args.pfn = pfn;

	r4k_on_each_cpu(R4K_HIT, local_r4k_flush_cache_page, &args);
पूर्ण

अटल अंतरभूत व्योम local_r4k_flush_data_cache_page(व्योम * addr)
अणु
	r4k_blast_dcache_page((अचिन्हित दीर्घ) addr);
पूर्ण

अटल व्योम r4k_flush_data_cache_page(अचिन्हित दीर्घ addr)
अणु
	अगर (in_atomic())
		local_r4k_flush_data_cache_page((व्योम *)addr);
	अन्यथा
		r4k_on_each_cpu(R4K_HIT, local_r4k_flush_data_cache_page,
				(व्योम *) addr);
पूर्ण

काष्ठा flush_icache_range_args अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	अचिन्हित पूर्णांक type;
	bool user;
पूर्ण;

अटल अंतरभूत व्योम __local_r4k_flush_icache_range(अचिन्हित दीर्घ start,
						  अचिन्हित दीर्घ end,
						  अचिन्हित पूर्णांक type,
						  bool user)
अणु
	अगर (!cpu_has_ic_fills_f_dc) अणु
		अगर (type == R4K_INDEX ||
		    (type & R4K_INDEX && end - start >= dcache_size)) अणु
			r4k_blast_dcache();
		पूर्ण अन्यथा अणु
			R4600_HIT_CACHEOP_WAR_IMPL;
			अगर (user)
				रक्षित_blast_dcache_range(start, end);
			अन्यथा
				blast_dcache_range(start, end);
		पूर्ण
	पूर्ण

	अगर (type == R4K_INDEX ||
	    (type & R4K_INDEX && end - start > icache_size))
		r4k_blast_icache();
	अन्यथा अणु
		चयन (boot_cpu_type()) अणु
		हाल CPU_LOONGSON2EF:
			रक्षित_loongson2_blast_icache_range(start, end);
			अवरोध;

		शेष:
			अगर (user)
				रक्षित_blast_icache_range(start, end);
			अन्यथा
				blast_icache_range(start, end);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम local_r4k_flush_icache_range(अचिन्हित दीर्घ start,
						अचिन्हित दीर्घ end)
अणु
	__local_r4k_flush_icache_range(start, end, R4K_HIT | R4K_INDEX, false);
पूर्ण

अटल अंतरभूत व्योम local_r4k_flush_icache_user_range(अचिन्हित दीर्घ start,
						     अचिन्हित दीर्घ end)
अणु
	__local_r4k_flush_icache_range(start, end, R4K_HIT | R4K_INDEX, true);
पूर्ण

अटल अंतरभूत व्योम local_r4k_flush_icache_range_ipi(व्योम *args)
अणु
	काष्ठा flush_icache_range_args *fir_args = args;
	अचिन्हित दीर्घ start = fir_args->start;
	अचिन्हित दीर्घ end = fir_args->end;
	अचिन्हित पूर्णांक type = fir_args->type;
	bool user = fir_args->user;

	__local_r4k_flush_icache_range(start, end, type, user);
पूर्ण

अटल व्योम __r4k_flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				     bool user)
अणु
	काष्ठा flush_icache_range_args args;
	अचिन्हित दीर्घ size, cache_size;

	args.start = start;
	args.end = end;
	args.type = R4K_HIT | R4K_INDEX;
	args.user = user;

	/*
	 * Indexed cache ops require an SMP call.
	 * Consider अगर that can or should be aव्योमed.
	 */
	preempt_disable();
	अगर (r4k_op_needs_ipi(R4K_INDEX) && !r4k_op_needs_ipi(R4K_HIT)) अणु
		/*
		 * If address-based cache ops करोn't require an SMP call, then
		 * use them exclusively क्रम small flushes.
		 */
		size = end - start;
		cache_size = icache_size;
		अगर (!cpu_has_ic_fills_f_dc) अणु
			size *= 2;
			cache_size += dcache_size;
		पूर्ण
		अगर (size <= cache_size)
			args.type &= ~R4K_INDEX;
	पूर्ण
	r4k_on_each_cpu(args.type, local_r4k_flush_icache_range_ipi, &args);
	preempt_enable();
	inकाष्ठाion_hazard();
पूर्ण

अटल व्योम r4k_flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस __r4k_flush_icache_range(start, end, false);
पूर्ण

अटल व्योम r4k_flush_icache_user_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस __r4k_flush_icache_range(start, end, true);
पूर्ण

#अगर_घोषित CONFIG_DMA_NONCOHERENT

अटल व्योम r4k_dma_cache_wback_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	/* Catch bad driver code */
	अगर (WARN_ON(size == 0))
		वापस;

	preempt_disable();
	अगर (cpu_has_inclusive_pcaches) अणु
		अगर (size >= scache_size) अणु
			अगर (current_cpu_type() != CPU_LOONGSON64)
				r4k_blast_scache();
			अन्यथा
				r4k_blast_scache_node(pa_to_nid(addr));
		पूर्ण अन्यथा अणु
			blast_scache_range(addr, addr + size);
		पूर्ण
		preempt_enable();
		__sync();
		वापस;
	पूर्ण

	/*
	 * Either no secondary cache or the available caches करोn't have the
	 * subset property so we have to flush the primary caches
	 * explicitly.
	 * If we would need IPI to perक्रमm an INDEX-type operation, then
	 * we have to use the HIT-type alternative as IPI cannot be used
	 * here due to पूर्णांकerrupts possibly being disabled.
	 */
	अगर (!r4k_op_needs_ipi(R4K_INDEX) && size >= dcache_size) अणु
		r4k_blast_dcache();
	पूर्ण अन्यथा अणु
		R4600_HIT_CACHEOP_WAR_IMPL;
		blast_dcache_range(addr, addr + size);
	पूर्ण
	preempt_enable();

	bc_wback_inv(addr, size);
	__sync();
पूर्ण

अटल व्योम prefetch_cache_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित पूर्णांक linesz = cpu_scache_line_size();
	अचिन्हित दीर्घ addr0 = addr, addr1;

	addr0 &= ~(linesz - 1);
	addr1 = (addr0 + size - 1) & ~(linesz - 1);

	रक्षित_ग_लिखोback_scache_line(addr0);
	अगर (likely(addr1 != addr0))
		रक्षित_ग_लिखोback_scache_line(addr1);
	अन्यथा
		वापस;

	addr0 += linesz;
	अगर (likely(addr1 != addr0))
		रक्षित_ग_लिखोback_scache_line(addr0);
	अन्यथा
		वापस;

	addr1 -= linesz;
	अगर (likely(addr1 > addr0))
		रक्षित_ग_लिखोback_scache_line(addr0);
पूर्ण

अटल व्योम r4k_dma_cache_inv(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	/* Catch bad driver code */
	अगर (WARN_ON(size == 0))
		वापस;

	preempt_disable();

	अगर (current_cpu_type() == CPU_BMIPS5000)
		prefetch_cache_inv(addr, size);

	अगर (cpu_has_inclusive_pcaches) अणु
		अगर (size >= scache_size) अणु
			अगर (current_cpu_type() != CPU_LOONGSON64)
				r4k_blast_scache();
			अन्यथा
				r4k_blast_scache_node(pa_to_nid(addr));
		पूर्ण अन्यथा अणु
			/*
			 * There is no clearly करोcumented alignment requirement
			 * क्रम the cache inकाष्ठाion on MIPS processors and
			 * some processors, among them the RM5200 and RM7000
			 * QED processors will throw an address error क्रम cache
			 * hit ops with insufficient alignment.	 Solved by
			 * aligning the address to cache line size.
			 */
			blast_inv_scache_range(addr, addr + size);
		पूर्ण
		preempt_enable();
		__sync();
		वापस;
	पूर्ण

	अगर (!r4k_op_needs_ipi(R4K_INDEX) && size >= dcache_size) अणु
		r4k_blast_dcache();
	पूर्ण अन्यथा अणु
		R4600_HIT_CACHEOP_WAR_IMPL;
		blast_inv_dcache_range(addr, addr + size);
	पूर्ण
	preempt_enable();

	bc_inv(addr, size);
	__sync();
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_NONCOHERENT */

अटल व्योम r4k_flush_icache_all(व्योम)
अणु
	अगर (cpu_has_vtag_icache)
		r4k_blast_icache();
पूर्ण

काष्ठा flush_kernel_vmap_range_args अणु
	अचिन्हित दीर्घ	vaddr;
	पूर्णांक		size;
पूर्ण;

अटल अंतरभूत व्योम local_r4k_flush_kernel_vmap_range_index(व्योम *args)
अणु
	/*
	 * Aliases only affect the primary caches so करोn't bother with
	 * S-caches or T-caches.
	 */
	r4k_blast_dcache();
पूर्ण

अटल अंतरभूत व्योम local_r4k_flush_kernel_vmap_range(व्योम *args)
अणु
	काष्ठा flush_kernel_vmap_range_args *vmra = args;
	अचिन्हित दीर्घ vaddr = vmra->vaddr;
	पूर्णांक size = vmra->size;

	/*
	 * Aliases only affect the primary caches so करोn't bother with
	 * S-caches or T-caches.
	 */
	R4600_HIT_CACHEOP_WAR_IMPL;
	blast_dcache_range(vaddr, vaddr + size);
पूर्ण

अटल व्योम r4k_flush_kernel_vmap_range(अचिन्हित दीर्घ vaddr, पूर्णांक size)
अणु
	काष्ठा flush_kernel_vmap_range_args args;

	args.vaddr = (अचिन्हित दीर्घ) vaddr;
	args.size = size;

	अगर (size >= dcache_size)
		r4k_on_each_cpu(R4K_INDEX,
				local_r4k_flush_kernel_vmap_range_index, शून्य);
	अन्यथा
		r4k_on_each_cpu(R4K_HIT, local_r4k_flush_kernel_vmap_range,
				&args);
पूर्ण

अटल अंतरभूत व्योम rm7k_erratum31(व्योम)
अणु
	स्थिर अचिन्हित दीर्घ ic_lsize = 32;
	अचिन्हित दीर्घ addr;

	/* RM7000 erratum #31. The icache is screwed at startup. */
	ग_लिखो_c0_taglo(0);
	ग_लिखो_c0_taghi(0);

	क्रम (addr = INDEX_BASE; addr <= INDEX_BASE + 4096; addr += ic_lsize) अणु
		__यंत्र__ __अस्थिर__ (
			".set push\n\t"
			".set noreorder\n\t"
			".set mips3\n\t"
			"cache\t%1, 0(%0)\n\t"
			"cache\t%1, 0x1000(%0)\n\t"
			"cache\t%1, 0x2000(%0)\n\t"
			"cache\t%1, 0x3000(%0)\n\t"
			"cache\t%2, 0(%0)\n\t"
			"cache\t%2, 0x1000(%0)\n\t"
			"cache\t%2, 0x2000(%0)\n\t"
			"cache\t%2, 0x3000(%0)\n\t"
			"cache\t%1, 0(%0)\n\t"
			"cache\t%1, 0x1000(%0)\n\t"
			"cache\t%1, 0x2000(%0)\n\t"
			"cache\t%1, 0x3000(%0)\n\t"
			".set pop\n"
			:
			: "r" (addr), "i" (Index_Store_Tag_I), "i" (Fill_I));
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक alias_74k_erratum(काष्ठा cpuinfo_mips *c)
अणु
	अचिन्हित पूर्णांक imp = c->processor_id & PRID_IMP_MASK;
	अचिन्हित पूर्णांक rev = c->processor_id & PRID_REV_MASK;
	पूर्णांक present = 0;

	/*
	 * Early versions of the 74K करो not update the cache tags on a
	 * vtag miss/ptag hit which can occur in the हाल of KSEG0/KUSEG
	 * aliases.  In this हाल it is better to treat the cache as always
	 * having aliases.  Also disable the synonym tag update feature
	 * where available.  In this हाल no opportunistic tag update will
	 * happen where a load causes a भव address miss but a physical
	 * address hit during a D-cache look-up.
	 */
	चयन (imp) अणु
	हाल PRID_IMP_74K:
		अगर (rev <= PRID_REV_ENCODE_332(2, 4, 0))
			present = 1;
		अगर (rev == PRID_REV_ENCODE_332(2, 4, 0))
			ग_लिखो_c0_config6(पढ़ो_c0_config6() | MTI_CONF6_SYND);
		अवरोध;
	हाल PRID_IMP_1074K:
		अगर (rev <= PRID_REV_ENCODE_332(1, 1, 0)) अणु
			present = 1;
			ग_लिखो_c0_config6(पढ़ो_c0_config6() | MTI_CONF6_SYND);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस present;
पूर्ण

अटल व्योम b5k_inकाष्ठाion_hazard(व्योम)
अणु
	__sync();
	__sync();
	__यंत्र__ __अस्थिर__(
	"       nop; nop; nop; nop; nop; nop; nop; nop\n"
	"       nop; nop; nop; nop; nop; nop; nop; nop\n"
	"       nop; nop; nop; nop; nop; nop; nop; nop\n"
	"       nop; nop; nop; nop; nop; nop; nop; nop\n"
	: : : "memory");
पूर्ण

अटल अक्षर *way_string[] = अणु शून्य, "direct mapped", "2-way",
	"3-way", "4-way", "5-way", "6-way", "7-way", "8-way",
	"9-way", "10-way", "11-way", "12-way",
	"13-way", "14-way", "15-way", "16-way",
पूर्ण;

अटल व्योम probe_pcache(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	अचिन्हित पूर्णांक config = पढ़ो_c0_config();
	अचिन्हित पूर्णांक prid = पढ़ो_c0_prid();
	पूर्णांक has_74k_erratum = 0;
	अचिन्हित दीर्घ config1;
	अचिन्हित पूर्णांक lsize;

	चयन (current_cpu_type()) अणु
	हाल CPU_R4600:			/* QED style two way caches? */
	हाल CPU_R4700:
	हाल CPU_R5000:
	हाल CPU_NEVADA:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 2;
		c->icache.waybit = __ffs(icache_size/2);

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 2;
		c->dcache.waybit= __ffs(dcache_size/2);

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		अवरोध;

	हाल CPU_R5500:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 2;
		c->icache.waybit= 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 2;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_CACHE_CDEX_P | MIPS_CPU_PREFETCH;
		अवरोध;

	हाल CPU_TX49XX:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 4;
		c->icache.waybit= 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 4;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		c->options |= MIPS_CPU_PREFETCH;
		अवरोध;

	हाल CPU_R4000PC:
	हाल CPU_R4000SC:
	हाल CPU_R4000MC:
	हाल CPU_R4400PC:
	हाल CPU_R4400SC:
	हाल CPU_R4400MC:
	हाल CPU_R4300:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 1;
		c->icache.waybit = 0;	/* करोesn't matter */

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 1;
		c->dcache.waybit = 0;	/* करोes not matter */

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		अवरोध;

	हाल CPU_R10000:
	हाल CPU_R12000:
	हाल CPU_R14000:
	हाल CPU_R16000:
		icache_size = 1 << (12 + ((config & R10K_CONF_IC) >> 29));
		c->icache.linesz = 64;
		c->icache.ways = 2;
		c->icache.waybit = 0;

		dcache_size = 1 << (12 + ((config & R10K_CONF_DC) >> 26));
		c->dcache.linesz = 32;
		c->dcache.ways = 2;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_PREFETCH;
		अवरोध;

	हाल CPU_VR4133:
		ग_लिखो_c0_config(config & ~VR41_CONF_P4K);
		fallthrough;
	हाल CPU_VR4131:
		/* Workaround क्रम cache inकाष्ठाion bug of VR4131 */
		अगर (c->processor_id == 0x0c80U || c->processor_id == 0x0c81U ||
		    c->processor_id == 0x0c82U) अणु
			config |= 0x00400000U;
			अगर (c->processor_id == 0x0c80U)
				config |= VR41_CONF_BP;
			ग_लिखो_c0_config(config);
		पूर्ण अन्यथा
			c->options |= MIPS_CPU_CACHE_CDEX_P;

		icache_size = 1 << (10 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 2;
		c->icache.waybit = __ffs(icache_size/2);

		dcache_size = 1 << (10 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 2;
		c->dcache.waybit = __ffs(dcache_size/2);
		अवरोध;

	हाल CPU_VR41XX:
	हाल CPU_VR4111:
	हाल CPU_VR4121:
	हाल CPU_VR4122:
	हाल CPU_VR4181:
	हाल CPU_VR4181A:
		icache_size = 1 << (10 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 1;
		c->icache.waybit = 0;	/* करोesn't matter */

		dcache_size = 1 << (10 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 1;
		c->dcache.waybit = 0;	/* करोes not matter */

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		अवरोध;

	हाल CPU_RM7000:
		rm7k_erratum31();

		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 4;
		c->icache.waybit = __ffs(icache_size / c->icache.ways);

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 4;
		c->dcache.waybit = __ffs(dcache_size / c->dcache.ways);

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		c->options |= MIPS_CPU_PREFETCH;
		अवरोध;

	हाल CPU_LOONGSON2EF:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.linesz = 16 << ((config & CONF_IB) >> 5);
		अगर (prid & 0x3)
			c->icache.ways = 4;
		अन्यथा
			c->icache.ways = 2;
		c->icache.waybit = 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.linesz = 16 << ((config & CONF_DB) >> 4);
		अगर (prid & 0x3)
			c->dcache.ways = 4;
		अन्यथा
			c->dcache.ways = 2;
		c->dcache.waybit = 0;
		अवरोध;

	हाल CPU_LOONGSON64:
		config1 = पढ़ो_c0_config1();
		lsize = (config1 >> 19) & 7;
		अगर (lsize)
			c->icache.linesz = 2 << lsize;
		अन्यथा
			c->icache.linesz = 0;
		c->icache.sets = 64 << ((config1 >> 22) & 7);
		c->icache.ways = 1 + ((config1 >> 16) & 7);
		icache_size = c->icache.sets *
					  c->icache.ways *
					  c->icache.linesz;
		c->icache.waybit = 0;

		lsize = (config1 >> 10) & 7;
		अगर (lsize)
			c->dcache.linesz = 2 << lsize;
		अन्यथा
			c->dcache.linesz = 0;
		c->dcache.sets = 64 << ((config1 >> 13) & 7);
		c->dcache.ways = 1 + ((config1 >> 7) & 7);
		dcache_size = c->dcache.sets *
					  c->dcache.ways *
					  c->dcache.linesz;
		c->dcache.waybit = 0;
		अगर ((c->processor_id & (PRID_IMP_MASK | PRID_REV_MASK)) >=
				(PRID_IMP_LOONGSON_64C | PRID_REV_LOONGSON3A_R2_0) ||
				(c->processor_id & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64R)
			c->options |= MIPS_CPU_PREFETCH;
		अवरोध;

	हाल CPU_CAVIUM_OCTEON3:
		/* For now lie about the number of ways. */
		c->icache.linesz = 128;
		c->icache.sets = 16;
		c->icache.ways = 8;
		c->icache.flags |= MIPS_CACHE_VTAG;
		icache_size = c->icache.sets * c->icache.ways * c->icache.linesz;

		c->dcache.linesz = 128;
		c->dcache.ways = 8;
		c->dcache.sets = 8;
		dcache_size = c->dcache.sets * c->dcache.ways * c->dcache.linesz;
		c->options |= MIPS_CPU_PREFETCH;
		अवरोध;

	शेष:
		अगर (!(config & MIPS_CONF_M))
			panic("Don't know how to probe P-caches on this cpu.");

		/*
		 * So we seem to be a MIPS32 or MIPS64 CPU
		 * So let's probe the I-cache ...
		 */
		config1 = पढ़ो_c0_config1();

		lsize = (config1 >> 19) & 7;

		/* IL == 7 is reserved */
		अगर (lsize == 7)
			panic("Invalid icache line size");

		c->icache.linesz = lsize ? 2 << lsize : 0;

		c->icache.sets = 32 << (((config1 >> 22) + 1) & 7);
		c->icache.ways = 1 + ((config1 >> 16) & 7);

		icache_size = c->icache.sets *
			      c->icache.ways *
			      c->icache.linesz;
		c->icache.waybit = __ffs(icache_size/c->icache.ways);

		अगर (config & MIPS_CONF_VI)
			c->icache.flags |= MIPS_CACHE_VTAG;

		/*
		 * Now probe the MIPS32 / MIPS64 data cache.
		 */
		c->dcache.flags = 0;

		lsize = (config1 >> 10) & 7;

		/* DL == 7 is reserved */
		अगर (lsize == 7)
			panic("Invalid dcache line size");

		c->dcache.linesz = lsize ? 2 << lsize : 0;

		c->dcache.sets = 32 << (((config1 >> 13) + 1) & 7);
		c->dcache.ways = 1 + ((config1 >> 7) & 7);

		dcache_size = c->dcache.sets *
			      c->dcache.ways *
			      c->dcache.linesz;
		c->dcache.waybit = __ffs(dcache_size/c->dcache.ways);

		c->options |= MIPS_CPU_PREFETCH;
		अवरोध;
	पूर्ण

	/*
	 * Processor configuration sanity check क्रम the R4000SC erratum
	 * #5.	With page sizes larger than 32kB there is no possibility
	 * to get a VCE exception anymore so we करोn't care about this
	 * misconfiguration.  The हाल is rather theoretical anyway;
	 * presumably no venकरोr is shipping his hardware in the "bad"
	 * configuration.
	 */
	अगर ((prid & PRID_IMP_MASK) == PRID_IMP_R4000 &&
	    (prid & PRID_REV_MASK) < PRID_REV_R4400 &&
	    !(config & CONF_SC) && c->icache.linesz != 16 &&
	    PAGE_SIZE <= 0x8000)
		panic("Improper R4000SC processor configuration detected");

	/* compute a couple of other cache variables */
	c->icache.waysize = icache_size / c->icache.ways;
	c->dcache.waysize = dcache_size / c->dcache.ways;

	c->icache.sets = c->icache.linesz ?
		icache_size / (c->icache.linesz * c->icache.ways) : 0;
	c->dcache.sets = c->dcache.linesz ?
		dcache_size / (c->dcache.linesz * c->dcache.ways) : 0;

	/*
	 * R1x000 P-caches are odd in a positive way.  They're 32kB 2-way
	 * भवly indexed so normally would suffer from aliases.  So
	 * normally they'd suffer from aliases but magic in the hardware deals
	 * with that क्रम us so we करोn't need to take care ourselves.
	 */
	चयन (current_cpu_type()) अणु
	हाल CPU_20KC:
	हाल CPU_25KF:
	हाल CPU_I6400:
	हाल CPU_I6500:
	हाल CPU_SB1:
	हाल CPU_SB1A:
	हाल CPU_XLR:
		c->dcache.flags |= MIPS_CACHE_PINDEX;
		अवरोध;

	हाल CPU_R10000:
	हाल CPU_R12000:
	हाल CPU_R14000:
	हाल CPU_R16000:
		अवरोध;

	हाल CPU_74K:
	हाल CPU_1074K:
		has_74k_erratum = alias_74k_erratum(c);
		fallthrough;
	हाल CPU_M14KC:
	हाल CPU_M14KEC:
	हाल CPU_24K:
	हाल CPU_34K:
	हाल CPU_1004K:
	हाल CPU_INTERAPTIV:
	हाल CPU_P5600:
	हाल CPU_PROAPTIV:
	हाल CPU_M5150:
	हाल CPU_QEMU_GENERIC:
	हाल CPU_P6600:
	हाल CPU_M6250:
		अगर (!(पढ़ो_c0_config7() & MIPS_CONF7_IAR) &&
		    (c->icache.waysize > PAGE_SIZE))
			c->icache.flags |= MIPS_CACHE_ALIASES;
		अगर (!has_74k_erratum && (पढ़ो_c0_config7() & MIPS_CONF7_AR)) अणु
			/*
			 * Effectively physically indexed dcache,
			 * thus no भव aliases.
			*/
			c->dcache.flags |= MIPS_CACHE_PINDEX;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		अगर (has_74k_erratum || c->dcache.waysize > PAGE_SIZE)
			c->dcache.flags |= MIPS_CACHE_ALIASES;
	पूर्ण

	/* Physically indexed caches करोn't suffer from भव aliasing */
	अगर (c->dcache.flags & MIPS_CACHE_PINDEX)
		c->dcache.flags &= ~MIPS_CACHE_ALIASES;

	/*
	 * In प्रणालीs with CM the icache fills from L2 or बंदr caches, and
	 * thus sees remote stores without needing to ग_लिखो them back any
	 * further than that.
	 */
	अगर (mips_cm_present())
		c->icache.flags |= MIPS_IC_SNOOPS_REMOTE;

	चयन (current_cpu_type()) अणु
	हाल CPU_20KC:
		/*
		 * Some older 20Kc chips करोesn't have the 'VI' bit in
		 * the config रेजिस्टर.
		 */
		c->icache.flags |= MIPS_CACHE_VTAG;
		अवरोध;

	हाल CPU_ALCHEMY:
	हाल CPU_I6400:
	हाल CPU_I6500:
		c->icache.flags |= MIPS_CACHE_IC_F_DC;
		अवरोध;

	हाल CPU_BMIPS5000:
		c->icache.flags |= MIPS_CACHE_IC_F_DC;
		/* Cache aliases are handled in hardware; allow HIGHMEM */
		c->dcache.flags &= ~MIPS_CACHE_ALIASES;
		अवरोध;

	हाल CPU_LOONGSON2EF:
		/*
		 * LOONGSON2 has 4 way icache, but when using indexed cache op,
		 * one op will act on all 4 ways
		 */
		c->icache.ways = 1;
	पूर्ण

	pr_info("Primary instruction cache %ldkB, %s, %s, linesize %d bytes.\n",
		icache_size >> 10,
		c->icache.flags & MIPS_CACHE_VTAG ? "VIVT" : "VIPT",
		way_string[c->icache.ways], c->icache.linesz);

	pr_info("Primary data cache %ldkB, %s, %s, %s, linesize %d bytes\n",
		dcache_size >> 10, way_string[c->dcache.ways],
		(c->dcache.flags & MIPS_CACHE_PINDEX) ? "PIPT" : "VIPT",
		(c->dcache.flags & MIPS_CACHE_ALIASES) ?
			"cache aliases" : "no aliases",
		c->dcache.linesz);
पूर्ण

अटल व्योम probe_vcache(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	अचिन्हित पूर्णांक config2, lsize;

	अगर (current_cpu_type() != CPU_LOONGSON64)
		वापस;

	config2 = पढ़ो_c0_config2();
	अगर ((lsize = ((config2 >> 20) & 15)))
		c->vcache.linesz = 2 << lsize;
	अन्यथा
		c->vcache.linesz = lsize;

	c->vcache.sets = 64 << ((config2 >> 24) & 15);
	c->vcache.ways = 1 + ((config2 >> 16) & 15);

	vcache_size = c->vcache.sets * c->vcache.ways * c->vcache.linesz;

	c->vcache.waybit = 0;
	c->vcache.waysize = vcache_size / c->vcache.ways;

	pr_info("Unified victim cache %ldkB %s, linesize %d bytes.\n",
		vcache_size >> 10, way_string[c->vcache.ways], c->vcache.linesz);
पूर्ण

/*
 * If you even _breathe_ on this function, look at the gcc output and make sure
 * it करोes not pop things on and off the stack क्रम the cache sizing loop that
 * executes in KSEG1 space or अन्यथा you will crash and burn badly.  You have
 * been warned.
 */
अटल पूर्णांक probe_scache(व्योम)
अणु
	अचिन्हित दीर्घ flags, addr, begin, end, घात2;
	अचिन्हित पूर्णांक config = पढ़ो_c0_config();
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	अगर (config & CONF_SC)
		वापस 0;

	begin = (अचिन्हित दीर्घ) &_stext;
	begin &= ~((4 * 1024 * 1024) - 1);
	end = begin + (4 * 1024 * 1024);

	/*
	 * This is such a bitch, you'd think they would make it easy to करो
	 * this.  Away you daemons of stupidity!
	 */
	local_irq_save(flags);

	/* Fill each size-multiple cache line with a valid tag. */
	घात2 = (64 * 1024);
	क्रम (addr = begin; addr < end; addr = (begin + घात2)) अणु
		अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *) addr;
		__यंत्र__ __अस्थिर__("nop" : : "r" (*p)); /* whee... */
		घात2 <<= 1;
	पूर्ण

	/* Load first line with zero (thereक्रमe invalid) tag. */
	ग_लिखो_c0_taglo(0);
	ग_लिखो_c0_taghi(0);
	__यंत्र__ __अस्थिर__("nop; nop; nop; nop;"); /* aव्योम the hazard */
	cache_op(Index_Store_Tag_I, begin);
	cache_op(Index_Store_Tag_D, begin);
	cache_op(Index_Store_Tag_SD, begin);

	/* Now search क्रम the wrap around poपूर्णांक. */
	घात2 = (128 * 1024);
	क्रम (addr = begin + (128 * 1024); addr < end; addr = begin + घात2) अणु
		cache_op(Index_Load_Tag_SD, addr);
		__यंत्र__ __अस्थिर__("nop; nop; nop; nop;"); /* hazard... */
		अगर (!पढ़ो_c0_taglo())
			अवरोध;
		घात2 <<= 1;
	पूर्ण
	local_irq_restore(flags);
	addr -= begin;

	scache_size = addr;
	c->scache.linesz = 16 << ((config & R4K_CONF_SB) >> 22);
	c->scache.ways = 1;
	c->scache.waybit = 0;		/* करोes not matter */

	वापस 1;
पूर्ण

अटल व्योम loongson2_sc_init(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	scache_size = 512*1024;
	c->scache.linesz = 32;
	c->scache.ways = 4;
	c->scache.waybit = 0;
	c->scache.waysize = scache_size / (c->scache.ways);
	c->scache.sets = scache_size / (c->scache.linesz * c->scache.ways);
	pr_info("Unified secondary cache %ldkB %s, linesize %d bytes.\n",
	       scache_size >> 10, way_string[c->scache.ways], c->scache.linesz);

	c->options |= MIPS_CPU_INCLUSIVE_CACHES;
पूर्ण

अटल व्योम loongson3_sc_init(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	अचिन्हित पूर्णांक config2, lsize;

	config2 = पढ़ो_c0_config2();
	lsize = (config2 >> 4) & 15;
	अगर (lsize)
		c->scache.linesz = 2 << lsize;
	अन्यथा
		c->scache.linesz = 0;
	c->scache.sets = 64 << ((config2 >> 8) & 15);
	c->scache.ways = 1 + (config2 & 15);

	/* Loongson-3 has 4-Scache banks, जबतक Loongson-2K have only 2 banks */
	अगर ((c->processor_id & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64R)
		c->scache.sets *= 2;
	अन्यथा
		c->scache.sets *= 4;

	scache_size = c->scache.sets * c->scache.ways * c->scache.linesz;

	c->scache.waybit = 0;
	c->scache.waysize = scache_size / c->scache.ways;
	pr_info("Unified secondary cache %ldkB %s, linesize %d bytes.\n",
	       scache_size >> 10, way_string[c->scache.ways], c->scache.linesz);
	अगर (scache_size)
		c->options |= MIPS_CPU_INCLUSIVE_CACHES;
	वापस;
पूर्ण

बाह्य पूर्णांक r5k_sc_init(व्योम);
बाह्य पूर्णांक rm7k_sc_init(व्योम);
बाह्य पूर्णांक mips_sc_init(व्योम);

अटल व्योम setup_scache(व्योम)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	अचिन्हित पूर्णांक config = पढ़ो_c0_config();
	पूर्णांक sc_present = 0;

	/*
	 * Do the probing thing on R4000SC and R4400SC processors.  Other
	 * processors करोn't have a S-cache that would be relevant to the
	 * Linux memory management.
	 */
	चयन (current_cpu_type()) अणु
	हाल CPU_R4000SC:
	हाल CPU_R4000MC:
	हाल CPU_R4400SC:
	हाल CPU_R4400MC:
		sc_present = run_uncached(probe_scache);
		अगर (sc_present)
			c->options |= MIPS_CPU_CACHE_CDEX_S;
		अवरोध;

	हाल CPU_R10000:
	हाल CPU_R12000:
	हाल CPU_R14000:
	हाल CPU_R16000:
		scache_size = 0x80000 << ((config & R10K_CONF_SS) >> 16);
		c->scache.linesz = 64 << ((config >> 13) & 1);
		c->scache.ways = 2;
		c->scache.waybit= 0;
		sc_present = 1;
		अवरोध;

	हाल CPU_R5000:
	हाल CPU_NEVADA:
#अगर_घोषित CONFIG_R5000_CPU_SCACHE
		r5k_sc_init();
#पूर्ण_अगर
		वापस;

	हाल CPU_RM7000:
#अगर_घोषित CONFIG_RM7000_CPU_SCACHE
		rm7k_sc_init();
#पूर्ण_अगर
		वापस;

	हाल CPU_LOONGSON2EF:
		loongson2_sc_init();
		वापस;

	हाल CPU_LOONGSON64:
		loongson3_sc_init();
		वापस;

	हाल CPU_CAVIUM_OCTEON3:
	हाल CPU_XLP:
		/* करोn't need to worry about L2, fully coherent */
		वापस;

	शेष:
		अगर (c->isa_level & (MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
				    MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
				    MIPS_CPU_ISA_M32R5 | MIPS_CPU_ISA_M64R5 |
				    MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)) अणु
#अगर_घोषित CONFIG_MIPS_CPU_SCACHE
			अगर (mips_sc_init ()) अणु
				scache_size = c->scache.ways * c->scache.sets * c->scache.linesz;
				prपूर्णांकk("MIPS secondary cache %ldkB, %s, linesize %d bytes.\n",
				       scache_size >> 10,
				       way_string[c->scache.ways], c->scache.linesz);

				अगर (current_cpu_type() == CPU_BMIPS5000)
					c->options |= MIPS_CPU_INCLUSIVE_CACHES;
			पूर्ण

#अन्यथा
			अगर (!(c->scache.flags & MIPS_CACHE_NOT_PRESENT))
				panic("Dunno how to handle MIPS32 / MIPS64 second level cache");
#पूर्ण_अगर
			वापस;
		पूर्ण
		sc_present = 0;
	पूर्ण

	अगर (!sc_present)
		वापस;

	/* compute a couple of other cache variables */
	c->scache.waysize = scache_size / c->scache.ways;

	c->scache.sets = scache_size / (c->scache.linesz * c->scache.ways);

	prपूर्णांकk("Unified secondary cache %ldkB %s, linesize %d bytes.\n",
	       scache_size >> 10, way_string[c->scache.ways], c->scache.linesz);

	c->options |= MIPS_CPU_INCLUSIVE_CACHES;
पूर्ण

व्योम au1x00_fixup_config_od(व्योम)
अणु
	/*
	 * c0_config.od (bit 19) was ग_लिखो only (and पढ़ो as 0)
	 * on the early revisions of Alchemy SOCs.  It disables the bus
	 * transaction overlapping and needs to be set to fix various errata.
	 */
	चयन (पढ़ो_c0_prid()) अणु
	हाल 0x00030100: /* Au1000 DA */
	हाल 0x00030201: /* Au1000 HA */
	हाल 0x00030202: /* Au1000 HB */
	हाल 0x01030200: /* Au1500 AB */
	/*
	 * Au1100 errata actually keeps silence about this bit, so we set it
	 * just in हाल क्रम those revisions that require it to be set according
	 * to the (now gone) cpu table.
	 */
	हाल 0x02030200: /* Au1100 AB */
	हाल 0x02030201: /* Au1100 BA */
	हाल 0x02030202: /* Au1100 BC */
		set_c0_config(1 << 19);
		अवरोध;
	पूर्ण
पूर्ण

/* CP0 hazard aव्योमance. */
#घोषणा NXP_BARRIER()							\
	 __यंत्र__ __अस्थिर__(						\
	".set noreorder\n\t"						\
	"nop; nop; nop; nop; nop; nop;\n\t"				\
	".set reorder\n\t")

अटल व्योम nxp_pr4450_fixup_config(व्योम)
अणु
	अचिन्हित दीर्घ config0;

	config0 = पढ़ो_c0_config();

	/* clear all three cache coherency fields */
	config0 &= ~(0x7 | (7 << 25) | (7 << 28));
	config0 |= (((_page_cachable_शेष >> _CACHE_SHIFT) <<  0) |
		    ((_page_cachable_शेष >> _CACHE_SHIFT) << 25) |
		    ((_page_cachable_शेष >> _CACHE_SHIFT) << 28));
	ग_लिखो_c0_config(config0);
	NXP_BARRIER();
पूर्ण

अटल पूर्णांक cca = -1;

अटल पूर्णांक __init cca_setup(अक्षर *str)
अणु
	get_option(&str, &cca);

	वापस 0;
पूर्ण

early_param("cca", cca_setup);

अटल व्योम coherency_setup(व्योम)
अणु
	अगर (cca < 0 || cca > 7)
		cca = पढ़ो_c0_config() & CONF_CM_CMASK;
	_page_cachable_शेष = cca << _CACHE_SHIFT;

	pr_debug("Using cache attribute %d\n", cca);
	change_c0_config(CONF_CM_CMASK, cca);

	/*
	 * c0_status.cu=0 specअगरies that updates by the sc inकाष्ठाion use
	 * the coherency mode specअगरied by the TLB; 1 means cachable
	 * coherent update on ग_लिखो will be used.  Not all processors have
	 * this bit and; some wire it to zero, others like Toshiba had the
	 * silly idea of putting something अन्यथा there ...
	 */
	चयन (current_cpu_type()) अणु
	हाल CPU_R4000PC:
	हाल CPU_R4000SC:
	हाल CPU_R4000MC:
	हाल CPU_R4400PC:
	हाल CPU_R4400SC:
	हाल CPU_R4400MC:
		clear_c0_config(CONF_CU);
		अवरोध;
	/*
	 * We need to catch the early Alchemy SOCs with
	 * the ग_लिखो-only co_config.od bit and set it back to one on:
	 * Au1000 rev DA, HA, HB;  Au1100 AB, BA, BC, Au1500 AB
	 */
	हाल CPU_ALCHEMY:
		au1x00_fixup_config_od();
		अवरोध;

	हाल PRID_IMP_PR4450:
		nxp_pr4450_fixup_config();
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम r4k_cache_error_setup(व्योम)
अणु
	बाह्य अक्षर __weak except_vec2_generic;
	बाह्य अक्षर __weak except_vec2_sb1;

	चयन (current_cpu_type()) अणु
	हाल CPU_SB1:
	हाल CPU_SB1A:
		set_uncached_handler(0x100, &except_vec2_sb1, 0x80);
		अवरोध;

	शेष:
		set_uncached_handler(0x100, &except_vec2_generic, 0x80);
		अवरोध;
	पूर्ण
पूर्ण

व्योम r4k_cache_init(व्योम)
अणु
	बाह्य व्योम build_clear_page(व्योम);
	बाह्य व्योम build_copy_page(व्योम);
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	probe_pcache();
	probe_vcache();
	setup_scache();

	r4k_blast_dcache_page_setup();
	r4k_blast_dcache_page_indexed_setup();
	r4k_blast_dcache_setup();
	r4k_blast_icache_page_setup();
	r4k_blast_icache_page_indexed_setup();
	r4k_blast_icache_setup();
	r4k_blast_scache_page_setup();
	r4k_blast_scache_page_indexed_setup();
	r4k_blast_scache_setup();
	r4k_blast_scache_node_setup();
#अगर_घोषित CONFIG_EVA
	r4k_blast_dcache_user_page_setup();
	r4k_blast_icache_user_page_setup();
#पूर्ण_अगर

	/*
	 * Some MIPS32 and MIPS64 processors have physically indexed caches.
	 * This code supports भवly indexed processors and will be
	 * unnecessarily inefficient on physically indexed processors.
	 */
	अगर (c->dcache.linesz && cpu_has_dc_aliases)
		shm_align_mask = max_t( अचिन्हित दीर्घ,
					c->dcache.sets * c->dcache.linesz - 1,
					PAGE_SIZE - 1);
	अन्यथा
		shm_align_mask = PAGE_SIZE-1;

	__flush_cache_vmap	= r4k__flush_cache_vmap;
	__flush_cache_vunmap	= r4k__flush_cache_vunmap;

	flush_cache_all		= cache_noop;
	__flush_cache_all	= r4k___flush_cache_all;
	flush_cache_mm		= r4k_flush_cache_mm;
	flush_cache_page	= r4k_flush_cache_page;
	flush_cache_range	= r4k_flush_cache_range;

	__flush_kernel_vmap_range = r4k_flush_kernel_vmap_range;

	flush_icache_all	= r4k_flush_icache_all;
	local_flush_data_cache_page	= local_r4k_flush_data_cache_page;
	flush_data_cache_page	= r4k_flush_data_cache_page;
	flush_icache_range	= r4k_flush_icache_range;
	local_flush_icache_range	= local_r4k_flush_icache_range;
	__flush_icache_user_range	= r4k_flush_icache_user_range;
	__local_flush_icache_user_range	= local_r4k_flush_icache_user_range;

#अगर_घोषित CONFIG_DMA_NONCOHERENT
	अगर (dma_शेष_coherent) अणु
		_dma_cache_wback_inv	= (व्योम *)cache_noop;
		_dma_cache_wback	= (व्योम *)cache_noop;
		_dma_cache_inv		= (व्योम *)cache_noop;
	पूर्ण अन्यथा अणु
		_dma_cache_wback_inv	= r4k_dma_cache_wback_inv;
		_dma_cache_wback	= r4k_dma_cache_wback_inv;
		_dma_cache_inv		= r4k_dma_cache_inv;
	पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_NONCOHERENT */

	build_clear_page();
	build_copy_page();

	/*
	 * We want to run CMP kernels on core with and without coherent
	 * caches. Thereक्रमe, करो not use CONFIG_MIPS_CMP to decide whether
	 * or not to flush caches.
	 */
	local_r4k___flush_cache_all(शून्य);

	coherency_setup();
	board_cache_error_setup = r4k_cache_error_setup;

	/*
	 * Per-CPU overrides
	 */
	चयन (current_cpu_type()) अणु
	हाल CPU_BMIPS4350:
	हाल CPU_BMIPS4380:
		/* No IPI is needed because all CPUs share the same D$ */
		flush_data_cache_page = r4k_blast_dcache_page;
		अवरोध;
	हाल CPU_BMIPS5000:
		/* We lose our superघातers अगर L2 is disabled */
		अगर (c->scache.flags & MIPS_CACHE_NOT_PRESENT)
			अवरोध;

		/* I$ fills from D$ just by emptying the ग_लिखो buffers */
		flush_cache_page = (व्योम *)b5k_inकाष्ठाion_hazard;
		flush_cache_range = (व्योम *)b5k_inकाष्ठाion_hazard;
		local_flush_data_cache_page = (व्योम *)b5k_inकाष्ठाion_hazard;
		flush_data_cache_page = (व्योम *)b5k_inकाष्ठाion_hazard;
		flush_icache_range = (व्योम *)b5k_inकाष्ठाion_hazard;
		local_flush_icache_range = (व्योम *)b5k_inकाष्ठाion_hazard;


		/* Optimization: an L2 flush implicitly flushes the L1 */
		current_cpu_data.options |= MIPS_CPU_INCLUSIVE_CACHES;
		अवरोध;
	हाल CPU_LOONGSON64:
		/* Loongson-3 मुख्यtains cache coherency by hardware */
		__flush_cache_all	= cache_noop;
		__flush_cache_vmap	= cache_noop;
		__flush_cache_vunmap	= cache_noop;
		__flush_kernel_vmap_range = (व्योम *)cache_noop;
		flush_cache_mm		= (व्योम *)cache_noop;
		flush_cache_page	= (व्योम *)cache_noop;
		flush_cache_range	= (व्योम *)cache_noop;
		flush_icache_all	= (व्योम *)cache_noop;
		flush_data_cache_page	= (व्योम *)cache_noop;
		local_flush_data_cache_page	= (व्योम *)cache_noop;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक r4k_cache_pm_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,
			       व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_PM_ENTER_FAILED:
	हाल CPU_PM_EXIT:
		coherency_setup();
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block r4k_cache_pm_notअगरier_block = अणु
	.notअगरier_call = r4k_cache_pm_notअगरier,
पूर्ण;

पूर्णांक __init r4k_cache_init_pm(व्योम)
अणु
	वापस cpu_pm_रेजिस्टर_notअगरier(&r4k_cache_pm_notअगरier_block);
पूर्ण
arch_initcall(r4k_cache_init_pm);
