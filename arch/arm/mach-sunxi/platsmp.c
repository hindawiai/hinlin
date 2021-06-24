<शैली गुरु>
/*
 * SMP support क्रम Allwinner SoCs
 *
 * Copyright (C) 2013 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * Based on code
 *  Copyright (C) 2012-2013 Allwinner Ltd.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/memory.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/smp.h>

#घोषणा CPUCFG_CPU_PWR_CLAMP_STATUS_REG(cpu)	((cpu) * 0x40 + 0x64)
#घोषणा CPUCFG_CPU_RST_CTRL_REG(cpu)		(((cpu) + 1) * 0x40)
#घोषणा CPUCFG_CPU_CTRL_REG(cpu)		(((cpu) + 1) * 0x40 + 0x04)
#घोषणा CPUCFG_CPU_STATUS_REG(cpu)		(((cpu) + 1) * 0x40 + 0x08)
#घोषणा CPUCFG_GEN_CTRL_REG			0x184
#घोषणा CPUCFG_PRIVATE0_REG			0x1a4
#घोषणा CPUCFG_PRIVATE1_REG			0x1a8
#घोषणा CPUCFG_DBG_CTL0_REG			0x1e0
#घोषणा CPUCFG_DBG_CTL1_REG			0x1e4

#घोषणा PRCM_CPU_PWROFF_REG			0x100
#घोषणा PRCM_CPU_PWR_CLAMP_REG(cpu)		(((cpu) * 4) + 0x140)

अटल व्योम __iomem *cpucfg_membase;
अटल व्योम __iomem *prcm_membase;

अटल DEFINE_SPINLOCK(cpu_lock);

अटल व्योम __init sun6i_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *node;

	node = of_find_compatible_node(शून्य, शून्य, "allwinner,sun6i-a31-prcm");
	अगर (!node) अणु
		pr_err("Missing A31 PRCM node in the device tree\n");
		वापस;
	पूर्ण

	prcm_membase = of_iomap(node, 0);
	of_node_put(node);
	अगर (!prcm_membase) अणु
		pr_err("Couldn't map A31 PRCM registers\n");
		वापस;
	पूर्ण

	node = of_find_compatible_node(शून्य, शून्य,
				       "allwinner,sun6i-a31-cpuconfig");
	अगर (!node) अणु
		pr_err("Missing A31 CPU config node in the device tree\n");
		वापस;
	पूर्ण

	cpucfg_membase = of_iomap(node, 0);
	of_node_put(node);
	अगर (!cpucfg_membase)
		pr_err("Couldn't map A31 CPU config registers\n");

पूर्ण

अटल पूर्णांक sun6i_smp_boot_secondary(अचिन्हित पूर्णांक cpu,
				    काष्ठा task_काष्ठा *idle)
अणु
	u32 reg;
	पूर्णांक i;

	अगर (!(prcm_membase && cpucfg_membase))
		वापस -EFAULT;

	spin_lock(&cpu_lock);

	/* Set CPU boot address */
	ग_लिखोl(__pa_symbol(secondary_startup),
	       cpucfg_membase + CPUCFG_PRIVATE0_REG);

	/* Assert the CPU core in reset */
	ग_लिखोl(0, cpucfg_membase + CPUCFG_CPU_RST_CTRL_REG(cpu));

	/* Assert the L1 cache in reset */
	reg = पढ़ोl(cpucfg_membase + CPUCFG_GEN_CTRL_REG);
	ग_लिखोl(reg & ~BIT(cpu), cpucfg_membase + CPUCFG_GEN_CTRL_REG);

	/* Disable बाह्यal debug access */
	reg = पढ़ोl(cpucfg_membase + CPUCFG_DBG_CTL1_REG);
	ग_लिखोl(reg & ~BIT(cpu), cpucfg_membase + CPUCFG_DBG_CTL1_REG);

	/* Power up the CPU */
	क्रम (i = 0; i <= 8; i++)
		ग_लिखोl(0xff >> i, prcm_membase + PRCM_CPU_PWR_CLAMP_REG(cpu));
	mdelay(10);

	/* Clear CPU घातer-off gating */
	reg = पढ़ोl(prcm_membase + PRCM_CPU_PWROFF_REG);
	ग_लिखोl(reg & ~BIT(cpu), prcm_membase + PRCM_CPU_PWROFF_REG);
	mdelay(1);

	/* Deनिश्चित the CPU core reset */
	ग_लिखोl(3, cpucfg_membase + CPUCFG_CPU_RST_CTRL_REG(cpu));

	/* Enable back the बाह्यal debug accesses */
	reg = पढ़ोl(cpucfg_membase + CPUCFG_DBG_CTL1_REG);
	ग_लिखोl(reg | BIT(cpu), cpucfg_membase + CPUCFG_DBG_CTL1_REG);

	spin_unlock(&cpu_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा smp_operations sun6i_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= sun6i_smp_prepare_cpus,
	.smp_boot_secondary	= sun6i_smp_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(sun6i_a31_smp, "allwinner,sun6i-a31", &sun6i_smp_ops);

अटल व्योम __init sun8i_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *node;

	node = of_find_compatible_node(शून्य, शून्य, "allwinner,sun8i-a23-prcm");
	अगर (!node) अणु
		pr_err("Missing A23 PRCM node in the device tree\n");
		वापस;
	पूर्ण

	prcm_membase = of_iomap(node, 0);
	of_node_put(node);
	अगर (!prcm_membase) अणु
		pr_err("Couldn't map A23 PRCM registers\n");
		वापस;
	पूर्ण

	node = of_find_compatible_node(शून्य, शून्य,
				       "allwinner,sun8i-a23-cpuconfig");
	अगर (!node) अणु
		pr_err("Missing A23 CPU config node in the device tree\n");
		वापस;
	पूर्ण

	cpucfg_membase = of_iomap(node, 0);
	of_node_put(node);
	अगर (!cpucfg_membase)
		pr_err("Couldn't map A23 CPU config registers\n");

पूर्ण

अटल पूर्णांक sun8i_smp_boot_secondary(अचिन्हित पूर्णांक cpu,
				    काष्ठा task_काष्ठा *idle)
अणु
	u32 reg;

	अगर (!(prcm_membase && cpucfg_membase))
		वापस -EFAULT;

	spin_lock(&cpu_lock);

	/* Set CPU boot address */
	ग_लिखोl(__pa_symbol(secondary_startup),
	       cpucfg_membase + CPUCFG_PRIVATE0_REG);

	/* Assert the CPU core in reset */
	ग_लिखोl(0, cpucfg_membase + CPUCFG_CPU_RST_CTRL_REG(cpu));

	/* Assert the L1 cache in reset */
	reg = पढ़ोl(cpucfg_membase + CPUCFG_GEN_CTRL_REG);
	ग_लिखोl(reg & ~BIT(cpu), cpucfg_membase + CPUCFG_GEN_CTRL_REG);

	/* Clear CPU घातer-off gating */
	reg = पढ़ोl(prcm_membase + PRCM_CPU_PWROFF_REG);
	ग_लिखोl(reg & ~BIT(cpu), prcm_membase + PRCM_CPU_PWROFF_REG);
	mdelay(1);

	/* Deनिश्चित the CPU core reset */
	ग_लिखोl(3, cpucfg_membase + CPUCFG_CPU_RST_CTRL_REG(cpu));

	spin_unlock(&cpu_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा smp_operations sun8i_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= sun8i_smp_prepare_cpus,
	.smp_boot_secondary	= sun8i_smp_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(sun8i_a23_smp, "allwinner,sun8i-a23", &sun8i_smp_ops);
