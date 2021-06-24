<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh2/probe.c
 *
 * CPU Subtype Probing क्रम SH-2.
 *
 * Copyright (C) 2002 Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cache.h>

#अगर defined(CONFIG_CPU_J2)
बाह्य u32 __iomem *j2_ccr_base;
अटल पूर्णांक __init scan_cache(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
			     पूर्णांक depth, व्योम *data)
अणु
	अगर (!of_flat_dt_is_compatible(node, "jcore,cache"))
		वापस 0;

	j2_ccr_base = (u32 __iomem *)of_flat_dt_translate_address(node);

	वापस 1;
पूर्ण
#पूर्ण_अगर

व्योम __ref cpu_probe(व्योम)
अणु
#अगर defined(CONFIG_CPU_SUBTYPE_SH7619)
	boot_cpu_data.type			= CPU_SH7619;
	boot_cpu_data.dcache.ways		= 4;
	boot_cpu_data.dcache.way_incr	= (1<<12);
	boot_cpu_data.dcache.sets		= 256;
	boot_cpu_data.dcache.entry_shअगरt	= 4;
	boot_cpu_data.dcache.linesz		= L1_CACHE_BYTES;
	boot_cpu_data.dcache.flags		= 0;
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_J2)
#अगर defined(CONFIG_SMP)
	अचिन्हित cpu = hard_smp_processor_id();
#अन्यथा
	अचिन्हित cpu = 0;
#पूर्ण_अगर
	अगर (cpu == 0) of_scan_flat_dt(scan_cache, शून्य);
	अगर (j2_ccr_base) __raw_ग_लिखोl(0x80000303, j2_ccr_base + 4*cpu);
	अगर (cpu != 0) वापस;
	boot_cpu_data.type			= CPU_J2;

	/* These शेषs are appropriate क्रम the original/current
	 * J2 cache. Once there is a proper framework क्रम getting cache
	 * info from device tree, we should चयन to that. */
	boot_cpu_data.dcache.ways		= 1;
	boot_cpu_data.dcache.sets		= 256;
	boot_cpu_data.dcache.entry_shअगरt	= 5;
	boot_cpu_data.dcache.linesz		= 32;
	boot_cpu_data.dcache.flags		= 0;

	boot_cpu_data.flags |= CPU_HAS_CAS_L;
#अन्यथा
	/*
	 * SH-2 करोesn't have separate caches
	 */
	boot_cpu_data.dcache.flags |= SH_CACHE_COMBINED;
#पूर्ण_अगर
	boot_cpu_data.icache = boot_cpu_data.dcache;
	boot_cpu_data.family = CPU_FAMILY_SH2;
पूर्ण
