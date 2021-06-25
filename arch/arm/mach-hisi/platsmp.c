<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2013 HiSilicon Limited.
 * Based on arch/arm/mach-vexpress/platsmp.c, Copyright (C) 2002 ARM Ltd.
 */
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "core.h"

#घोषणा HIX5HD2_BOOT_ADDRESS		0xffff0000

अटल व्योम __iomem *ctrl_base;

व्योम hi3xxx_set_cpu_jump(पूर्णांक cpu, व्योम *jump_addr)
अणु
	cpu = cpu_logical_map(cpu);
	अगर (!cpu || !ctrl_base)
		वापस;
	ग_लिखोl_relaxed(__pa_symbol(jump_addr), ctrl_base + ((cpu - 1) << 2));
पूर्ण

पूर्णांक hi3xxx_get_cpu_jump(पूर्णांक cpu)
अणु
	cpu = cpu_logical_map(cpu);
	अगर (!cpu || !ctrl_base)
		वापस 0;
	वापस पढ़ोl_relaxed(ctrl_base + ((cpu - 1) << 2));
पूर्ण

अटल व्योम __init hisi_enable_scu_a9(व्योम)
अणु
	अचिन्हित दीर्घ base = 0;
	व्योम __iomem *scu_base = शून्य;

	अगर (scu_a9_has_base()) अणु
		base = scu_a9_get_base();
		scu_base = ioremap(base, SZ_4K);
		अगर (!scu_base) अणु
			pr_err("ioremap(scu_base) failed\n");
			वापस;
		पूर्ण
		scu_enable(scu_base);
		iounmap(scu_base);
	पूर्ण
पूर्ण

अटल व्योम __init hi3xxx_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np = शून्य;
	u32 offset = 0;

	hisi_enable_scu_a9();
	अगर (!ctrl_base) अणु
		np = of_find_compatible_node(शून्य, शून्य, "hisilicon,sysctrl");
		अगर (!np) अणु
			pr_err("failed to find hisilicon,sysctrl node\n");
			वापस;
		पूर्ण
		ctrl_base = of_iomap(np, 0);
		अगर (!ctrl_base) अणु
			pr_err("failed to map address\n");
			वापस;
		पूर्ण
		अगर (of_property_पढ़ो_u32(np, "smp-offset", &offset) < 0) अणु
			pr_err("failed to find smp-offset property\n");
			वापस;
		पूर्ण
		ctrl_base += offset;
	पूर्ण
पूर्ण

अटल पूर्णांक hi3xxx_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	hi3xxx_set_cpu(cpu, true);
	hi3xxx_set_cpu_jump(cpu, secondary_startup);
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा smp_operations hi3xxx_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= hi3xxx_smp_prepare_cpus,
	.smp_boot_secondary	= hi3xxx_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= hi3xxx_cpu_die,
	.cpu_समाप्त		= hi3xxx_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __init hisi_common_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	hisi_enable_scu_a9();
पूर्ण

अटल व्योम hix5hd2_set_scu_boot_addr(phys_addr_t start_addr, phys_addr_t jump_addr)
अणु
	व्योम __iomem *virt;

	virt = ioremap(start_addr, PAGE_SIZE);

	ग_लिखोl_relaxed(0xe51ff004, virt);	/* ldr pc, [pc, #-4] */
	ग_लिखोl_relaxed(jump_addr, virt + 4);	/* pc jump phy address */
	iounmap(virt);
पूर्ण

अटल पूर्णांक hix5hd2_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	phys_addr_t jumpaddr;

	jumpaddr = __pa_symbol(secondary_startup);
	hix5hd2_set_scu_boot_addr(HIX5HD2_BOOT_ADDRESS, jumpaddr);
	hix5hd2_set_cpu(cpu, true);
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा smp_operations hix5hd2_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= hisi_common_smp_prepare_cpus,
	.smp_boot_secondary	= hix5hd2_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= hix5hd2_cpu_die,
#पूर्ण_अगर
पूर्ण;


#घोषणा SC_SCTL_REMAP_CLR      0x00000100
#घोषणा HIP01_BOOT_ADDRESS     0x80000000
#घोषणा REG_SC_CTRL            0x000

अटल व्योम hip01_set_boot_addr(phys_addr_t start_addr, phys_addr_t jump_addr)
अणु
	व्योम __iomem *virt;

	virt = phys_to_virt(start_addr);

	ग_लिखोl_relaxed(0xe51ff004, virt);
	ग_लिखोl_relaxed(jump_addr, virt + 4);
पूर्ण

अटल पूर्णांक hip01_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	phys_addr_t jumpaddr;
	अचिन्हित पूर्णांक remap_reg_value = 0;
	काष्ठा device_node *node;


	jumpaddr = __pa_symbol(secondary_startup);
	hip01_set_boot_addr(HIP01_BOOT_ADDRESS, jumpaddr);

	node = of_find_compatible_node(शून्य, शून्य, "hisilicon,hip01-sysctrl");
	अगर (WARN_ON(!node))
		वापस -1;
	ctrl_base = of_iomap(node, 0);

	/* set the secondary core boot from DDR */
	remap_reg_value = पढ़ोl_relaxed(ctrl_base + REG_SC_CTRL);
	barrier();
	remap_reg_value |= SC_SCTL_REMAP_CLR;
	barrier();
	ग_लिखोl_relaxed(remap_reg_value, ctrl_base + REG_SC_CTRL);

	hip01_set_cpu(cpu, true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा smp_operations hip01_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus       = hisi_common_smp_prepare_cpus,
	.smp_boot_secondary     = hip01_boot_secondary,
पूर्ण;

CPU_METHOD_OF_DECLARE(hi3xxx_smp, "hisilicon,hi3620-smp", &hi3xxx_smp_ops);
CPU_METHOD_OF_DECLARE(hix5hd2_smp, "hisilicon,hix5hd2-smp", &hix5hd2_smp_ops);
CPU_METHOD_OF_DECLARE(hip01_smp, "hisilicon,hip01-smp", &hip01_smp_ops);
