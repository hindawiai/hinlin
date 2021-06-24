<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Marvell Technology Group Ltd.
 *
 * Antoine Tथऊnart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

/*
 * There are two reset रेजिस्टरs, one with self-clearing (SC)
 * reset and one with non-self-clearing reset (NON_SC).
 */
#घोषणा CPU_RESET_SC		0x00
#घोषणा CPU_RESET_NON_SC	0x20

#घोषणा RESET_VECT		0x00
#घोषणा SW_RESET_ADDR		0x94

बाह्य u32 boot_inst;

अटल व्योम __iomem *cpu_ctrl;

अटल अंतरभूत व्योम berlin_perक्रमm_reset_cpu(अचिन्हित पूर्णांक cpu)
अणु
	u32 val;

	val = पढ़ोl(cpu_ctrl + CPU_RESET_NON_SC);
	val &= ~BIT(cpu_logical_map(cpu));
	ग_लिखोl(val, cpu_ctrl + CPU_RESET_NON_SC);
	val |= BIT(cpu_logical_map(cpu));
	ग_लिखोl(val, cpu_ctrl + CPU_RESET_NON_SC);
पूर्ण

अटल पूर्णांक berlin_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अगर (!cpu_ctrl)
		वापस -EFAULT;

	/*
	 * Reset the CPU, making it to execute the inकाष्ठाion in the reset
	 * exception vector.
	 */
	berlin_perक्रमm_reset_cpu(cpu);

	वापस 0;
पूर्ण

अटल व्योम __init berlin_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *scu_base;
	व्योम __iomem *vectors_base;

	np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");
	scu_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!scu_base)
		वापस;

	np = of_find_compatible_node(शून्य, शून्य, "marvell,berlin-cpu-ctrl");
	cpu_ctrl = of_iomap(np, 0);
	of_node_put(np);
	अगर (!cpu_ctrl)
		जाओ unmap_scu;

	vectors_base = ioremap(VECTORS_BASE, SZ_32K);
	अगर (!vectors_base)
		जाओ unmap_scu;

	scu_enable(scu_base);

	/*
	 * Write the first inकाष्ठाion the CPU will execute after being reset
	 * in the reset exception vector.
	 */
	ग_लिखोl(boot_inst, vectors_base + RESET_VECT);

	/*
	 * Write the secondary startup address पूर्णांकo the SW reset address
	 * vector. This is used by boot_inst.
	 */
	ग_लिखोl(__pa_symbol(secondary_startup), vectors_base + SW_RESET_ADDR);

	iounmap(vectors_base);
unmap_scu:
	iounmap(scu_base);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम berlin_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	v7_निकास_coherency_flush(louis);
	जबतक (1)
		cpu_करो_idle();
पूर्ण

अटल पूर्णांक berlin_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	u32 val;

	val = पढ़ोl(cpu_ctrl + CPU_RESET_NON_SC);
	val &= ~BIT(cpu_logical_map(cpu));
	ग_लिखोl(val, cpu_ctrl + CPU_RESET_NON_SC);

	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations berlin_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= berlin_smp_prepare_cpus,
	.smp_boot_secondary	= berlin_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= berlin_cpu_die,
	.cpu_समाप्त		= berlin_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;
CPU_METHOD_OF_DECLARE(berlin_smp, "marvell,berlin-smp", &berlin_smp_ops);
