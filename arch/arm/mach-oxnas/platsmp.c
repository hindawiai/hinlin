<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2013 Ma Haijun <mahaijuns@gmail.com>
 * Copyright (C) 2002 ARM Ltd.
 * All Rights Reserved
 */
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

बाह्य व्योम ox820_secondary_startup(व्योम);

अटल व्योम __iomem *cpu_ctrl;
अटल व्योम __iomem *gic_cpu_ctrl;

#घोषणा HOLDINGPEN_CPU_OFFSET		0xc8
#घोषणा HOLDINGPEN_LOCATION_OFFSET	0xc4

#घोषणा GIC_NCPU_OFFSET(cpu)		(0x100 + (cpu)*0x100)
#घोषणा GIC_CPU_CTRL			0x00
#घोषणा GIC_CPU_CTRL_ENABLE		1

अटल पूर्णांक __init ox820_boot_secondary(अचिन्हित पूर्णांक cpu,
		काष्ठा task_काष्ठा *idle)
अणु
	/*
	 * Write the address of secondary startup पूर्णांकo the
	 * प्रणाली-wide flags रेजिस्टर. The BootMonitor रुकोs
	 * until it receives a soft पूर्णांकerrupt, and then the
	 * secondary CPU branches to this address.
	 */
	ग_लिखोl(virt_to_phys(ox820_secondary_startup),
			cpu_ctrl + HOLDINGPEN_LOCATION_OFFSET);

	ग_लिखोl(cpu, cpu_ctrl + HOLDINGPEN_CPU_OFFSET);

	/*
	 * Enable GIC cpu पूर्णांकerface in CPU Interface Control Register
	 */
	ग_लिखोl(GIC_CPU_CTRL_ENABLE,
		gic_cpu_ctrl + GIC_NCPU_OFFSET(cpu) + GIC_CPU_CTRL);

	/*
	 * Send the secondary CPU a soft पूर्णांकerrupt, thereby causing
	 * the boot monitor to पढ़ो the प्रणाली wide flags रेजिस्टर,
	 * and branch to the address found there.
	 */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	वापस 0;
पूर्ण

अटल व्योम __init ox820_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *scu_base;

	np = of_find_compatible_node(शून्य, शून्य, "arm,arm11mp-scu");
	scu_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!scu_base)
		वापस;

	/* Remap CPU Interrupt Interface Registers */
	np = of_find_compatible_node(शून्य, शून्य, "arm,arm11mp-gic");
	gic_cpu_ctrl = of_iomap(np, 1);
	of_node_put(np);
	अगर (!gic_cpu_ctrl)
		जाओ unmap_scu;

	np = of_find_compatible_node(शून्य, शून्य, "oxsemi,ox820-sys-ctrl");
	cpu_ctrl = of_iomap(np, 0);
	of_node_put(np);
	अगर (!cpu_ctrl)
		जाओ unmap_scu;

	scu_enable(scu_base);
	flush_cache_all();

unmap_scu:
	iounmap(scu_base);
पूर्ण

अटल स्थिर काष्ठा smp_operations ox820_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= ox820_smp_prepare_cpus,
	.smp_boot_secondary	= ox820_boot_secondary,
पूर्ण;

CPU_METHOD_OF_DECLARE(ox820_smp, "oxsemi,ox820-smp", &ox820_smp_ops);
