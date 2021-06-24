<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  arch/arm/mach-sti/platsmp.c
 *
 * Copyright (C) 2013 STMicroelectronics (R&D) Limited.
 *		http://www.st.com
 *
 * Cloned from linux/arch/arm/mach-vexpress/platsmp.c
 *
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 */
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#समावेश "smp.h"

अटल u32 __iomem *cpu_strt_ptr;

अटल पूर्णांक sti_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित दीर्घ entry_pa = __pa_symbol(secondary_startup);

	/*
	 * Secondary CPU is initialised and started by a U-BOOTROM firmware.
	 * Secondary CPU is spinning and रुकोing क्रम a ग_लिखो at cpu_strt_ptr.
	 * Writing secondary_startup address at cpu_strt_ptr makes it to
	 * jump directly to secondary_startup().
	 */
	__raw_ग_लिखोl(entry_pa, cpu_strt_ptr);

	/* wmb so that data is actually written beक्रमe cache flush is करोne */
	smp_wmb();
	sync_cache_w(cpu_strt_ptr);

	वापस 0;
पूर्ण

अटल व्योम __init sti_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *scu_base;
	u32 release_phys;
	पूर्णांक cpu;

	np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");

	अगर (np) अणु
		scu_base = of_iomap(np, 0);
		scu_enable(scu_base);
		of_node_put(np);
	पूर्ण

	अगर (max_cpus <= 1)
		वापस;

	क्रम_each_possible_cpu(cpu) अणु

		np = of_get_cpu_node(cpu, शून्य);

		अगर (!np)
			जारी;

		अगर (of_property_पढ़ो_u32(np, "cpu-release-addr",
						&release_phys)) अणु
			pr_err("CPU %d: missing or invalid cpu-release-addr "
				"property\n", cpu);
			जारी;
		पूर्ण

		/*
		 * cpu-release-addr is usually configured in SBC DMEM but can
		 * also be in RAM.
		 */

		अगर (!memblock_is_memory(release_phys))
			cpu_strt_ptr =
				ioremap(release_phys, माप(release_phys));
		अन्यथा
			cpu_strt_ptr =
				(u32 __iomem *)phys_to_virt(release_phys);

		set_cpu_possible(cpu, true);
	पूर्ण
पूर्ण

स्थिर काष्ठा smp_operations sti_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= sti_smp_prepare_cpus,
	.smp_boot_secondary	= sti_boot_secondary,
पूर्ण;
