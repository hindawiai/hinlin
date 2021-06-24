<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "hardware.h"

u32 g_diag_reg;
अटल व्योम __iomem *scu_base;

अटल काष्ठा map_desc scu_io_desc __initdata = अणु
	/* .भव and .pfn are run-समय asचिन्हित */
	.length		= SZ_4K,
	.type		= MT_DEVICE,
पूर्ण;

व्योम __init imx_scu_map_io(व्योम)
अणु
	अचिन्हित दीर्घ base;

	/* Get SCU base */
	यंत्र("mrc p15, 4, %0, c15, c0, 0" : "=r" (base));

	scu_io_desc.भव = IMX_IO_P2V(base);
	scu_io_desc.pfn = __phys_to_pfn(base);
	iotable_init(&scu_io_desc, 1);

	scu_base = IMX_IO_ADDRESS(base);
पूर्ण

अटल पूर्णांक imx_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	imx_set_cpu_jump(cpu, v7_secondary_startup);
	imx_enable_cpu(cpu, true);
	वापस 0;
पूर्ण

/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the प्रणाली.
 */
अटल व्योम __init imx_smp_init_cpus(व्योम)
अणु
	पूर्णांक i, ncores;

	ncores = scu_get_core_count(scu_base);

	क्रम (i = ncores; i < NR_CPUS; i++)
		set_cpu_possible(i, false);
पूर्ण

व्योम imx_smp_prepare(व्योम)
अणु
	scu_enable(scu_base);
पूर्ण

अटल व्योम __init imx_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	imx_smp_prepare();

	/*
	 * The diagnostic रेजिस्टर holds the errata bits.  Mostly bootloader
	 * करोes not bring up secondary cores, so that when errata bits are set
	 * in bootloader, they are set only क्रम boot cpu.  But on a SMP
	 * configuration, it should be equally करोne on every single core.
	 * Read the रेजिस्टर from boot cpu here, and will replicate it पूर्णांकo
	 * secondary cores when booting them.
	 */
	यंत्र("mrc p15, 0, %0, c15, c0, 1" : "=r" (g_diag_reg) : : "cc");
	sync_cache_w(&g_diag_reg);
पूर्ण

स्थिर काष्ठा smp_operations imx_smp_ops __initस्थिर = अणु
	.smp_init_cpus		= imx_smp_init_cpus,
	.smp_prepare_cpus	= imx_smp_prepare_cpus,
	.smp_boot_secondary	= imx_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= imx_cpu_die,
	.cpu_समाप्त		= imx_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

#घोषणा DCFG_CCSR_SCRATCHRW1	0x200

अटल पूर्णांक ls1021a_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	वापस 0;
पूर्ण

अटल व्योम __init ls1021a_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *dcfg_base;
	अचिन्हित दीर्घ paddr;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,ls1021a-dcfg");
	dcfg_base = of_iomap(np, 0);
	of_node_put(np);
	BUG_ON(!dcfg_base);

	paddr = __pa_symbol(secondary_startup);
	ग_लिखोl_relaxed(cpu_to_be32(paddr), dcfg_base + DCFG_CCSR_SCRATCHRW1);

	iounmap(dcfg_base);
पूर्ण

स्थिर काष्ठा smp_operations ls1021a_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= ls1021a_smp_prepare_cpus,
	.smp_boot_secondary	= ls1021a_boot_secondary,
पूर्ण;
