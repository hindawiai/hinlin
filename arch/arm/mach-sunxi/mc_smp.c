<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 *
 * arch/arm/mach-sunxi/mc_smp.c
 *
 * Based on Allwinner code, arch/arm/mach-exynos/mcpm-exynos.c, and
 * arch/arm/mach-hisi/plaपंचांगcpm.c
 * Cluster cache enable trampoline code adapted from MCPM framework
 */

#समावेश <linux/arm-cci.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/suspend.h>

#घोषणा SUNXI_CPUS_PER_CLUSTER		4
#घोषणा SUNXI_NR_CLUSTERS		2

#घोषणा POLL_USEC	100
#घोषणा TIMEOUT_USEC	100000

#घोषणा CPUCFG_CX_CTRL_REG0(c)		(0x10 * (c))
#घोषणा CPUCFG_CX_CTRL_REG0_L1_RST_DISABLE(n)	BIT(n)
#घोषणा CPUCFG_CX_CTRL_REG0_L1_RST_DISABLE_ALL	0xf
#घोषणा CPUCFG_CX_CTRL_REG0_L2_RST_DISABLE_A7	BIT(4)
#घोषणा CPUCFG_CX_CTRL_REG0_L2_RST_DISABLE_A15	BIT(0)
#घोषणा CPUCFG_CX_CTRL_REG1(c)		(0x10 * (c) + 0x4)
#घोषणा CPUCFG_CX_CTRL_REG1_ACINACTM	BIT(0)
#घोषणा CPUCFG_CX_STATUS(c)		(0x30 + 0x4 * (c))
#घोषणा CPUCFG_CX_STATUS_STANDBYWFI(n)	BIT(16 + (n))
#घोषणा CPUCFG_CX_STATUS_STANDBYWFIL2	BIT(0)
#घोषणा CPUCFG_CX_RST_CTRL(c)		(0x80 + 0x4 * (c))
#घोषणा CPUCFG_CX_RST_CTRL_DBG_SOC_RST	BIT(24)
#घोषणा CPUCFG_CX_RST_CTRL_ETM_RST(n)	BIT(20 + (n))
#घोषणा CPUCFG_CX_RST_CTRL_ETM_RST_ALL	(0xf << 20)
#घोषणा CPUCFG_CX_RST_CTRL_DBG_RST(n)	BIT(16 + (n))
#घोषणा CPUCFG_CX_RST_CTRL_DBG_RST_ALL	(0xf << 16)
#घोषणा CPUCFG_CX_RST_CTRL_H_RST	BIT(12)
#घोषणा CPUCFG_CX_RST_CTRL_L2_RST	BIT(8)
#घोषणा CPUCFG_CX_RST_CTRL_CX_RST(n)	BIT(4 + (n))
#घोषणा CPUCFG_CX_RST_CTRL_CORE_RST(n)	BIT(n)
#घोषणा CPUCFG_CX_RST_CTRL_CORE_RST_ALL	(0xf << 0)

#घोषणा PRCM_CPU_PO_RST_CTRL(c)		(0x4 + 0x4 * (c))
#घोषणा PRCM_CPU_PO_RST_CTRL_CORE(n)	BIT(n)
#घोषणा PRCM_CPU_PO_RST_CTRL_CORE_ALL	0xf
#घोषणा PRCM_PWROFF_GATING_REG(c)	(0x100 + 0x4 * (c))
/* The घातer off रेजिस्टर क्रम clusters are dअगरferent from a80 and a83t */
#घोषणा PRCM_PWROFF_GATING_REG_CLUSTER_SUN8I	BIT(0)
#घोषणा PRCM_PWROFF_GATING_REG_CLUSTER_SUN9I	BIT(4)
#घोषणा PRCM_PWROFF_GATING_REG_CORE(n)	BIT(n)
#घोषणा PRCM_PWR_SWITCH_REG(c, cpu)	(0x140 + 0x10 * (c) + 0x4 * (cpu))
#घोषणा PRCM_CPU_SOFT_ENTRY_REG		0x164

/* R_CPUCFG रेजिस्टरs, specअगरic to sun8i-a83t */
#घोषणा R_CPUCFG_CLUSTER_PO_RST_CTRL(c)	(0x30 + (c) * 0x4)
#घोषणा R_CPUCFG_CLUSTER_PO_RST_CTRL_CORE(n)	BIT(n)
#घोषणा R_CPUCFG_CPU_SOFT_ENTRY_REG		0x01a4

#घोषणा CPU0_SUPPORT_HOTPLUG_MAGIC0	0xFA50392F
#घोषणा CPU0_SUPPORT_HOTPLUG_MAGIC1	0x790DCA3A

अटल व्योम __iomem *cpucfg_base;
अटल व्योम __iomem *prcm_base;
अटल व्योम __iomem *sram_b_smp_base;
अटल व्योम __iomem *r_cpucfg_base;

बाह्य व्योम sunxi_mc_smp_secondary_startup(व्योम);
बाह्य व्योम sunxi_mc_smp_resume(व्योम);
अटल bool is_a83t;

अटल bool sunxi_core_is_cortex_a15(अचिन्हित पूर्णांक core, अचिन्हित पूर्णांक cluster)
अणु
	काष्ठा device_node *node;
	पूर्णांक cpu = cluster * SUNXI_CPUS_PER_CLUSTER + core;
	bool is_compatible;

	node = of_cpu_device_node_get(cpu);

	/* In हाल of_cpu_device_node_get fails */
	अगर (!node)
		node = of_get_cpu_node(cpu, शून्य);

	अगर (!node) अणु
		/*
		 * There's no poपूर्णांक in वापसing an error, since we
		 * would be mid way in a core or cluster घातer sequence.
		 */
		pr_err("%s: Couldn't get CPU cluster %u core %u device node\n",
		       __func__, cluster, core);

		वापस false;
	पूर्ण

	is_compatible = of_device_is_compatible(node, "arm,cortex-a15");
	of_node_put(node);
	वापस is_compatible;
पूर्ण

अटल पूर्णांक sunxi_cpu_घातer_चयन_set(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster,
				      bool enable)
अणु
	u32 reg;

	/* control sequence from Allwinner A80 user manual v1.2 PRCM section */
	reg = पढ़ोl(prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
	अगर (enable) अणु
		अगर (reg == 0x00) अणु
			pr_debug("power clamp for cluster %u cpu %u already open\n",
				 cluster, cpu);
			वापस 0;
		पूर्ण

		ग_लिखोl(0xff, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
		ग_लिखोl(0xfe, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
		ग_लिखोl(0xf8, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
		ग_लिखोl(0xf0, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
		ग_लिखोl(0x00, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0xff, prcm_base + PRCM_PWR_SWITCH_REG(cluster, cpu));
		udelay(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sunxi_cpu0_hotplug_support_set(bool enable)
अणु
	अगर (enable) अणु
		ग_लिखोl(CPU0_SUPPORT_HOTPLUG_MAGIC0, sram_b_smp_base);
		ग_लिखोl(CPU0_SUPPORT_HOTPLUG_MAGIC1, sram_b_smp_base + 0x4);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x0, sram_b_smp_base);
		ग_लिखोl(0x0, sram_b_smp_base + 0x4);
	पूर्ण
पूर्ण

अटल पूर्णांक sunxi_cpu_घातerup(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	u32 reg;

	pr_debug("%s: cluster %u cpu %u\n", __func__, cluster, cpu);
	अगर (cpu >= SUNXI_CPUS_PER_CLUSTER || cluster >= SUNXI_NR_CLUSTERS)
		वापस -EINVAL;

	/* Set hotplug support magic flags क्रम cpu0 */
	अगर (cluster == 0 && cpu == 0)
		sunxi_cpu0_hotplug_support_set(true);

	/* निश्चित processor घातer-on reset */
	reg = पढ़ोl(prcm_base + PRCM_CPU_PO_RST_CTRL(cluster));
	reg &= ~PRCM_CPU_PO_RST_CTRL_CORE(cpu);
	ग_लिखोl(reg, prcm_base + PRCM_CPU_PO_RST_CTRL(cluster));

	अगर (is_a83t) अणु
		/* निश्चित cpu घातer-on reset */
		reg  = पढ़ोl(r_cpucfg_base +
			     R_CPUCFG_CLUSTER_PO_RST_CTRL(cluster));
		reg &= ~(R_CPUCFG_CLUSTER_PO_RST_CTRL_CORE(cpu));
		ग_लिखोl(reg, r_cpucfg_base +
		       R_CPUCFG_CLUSTER_PO_RST_CTRL(cluster));
		udelay(10);
	पूर्ण

	/* Cortex-A7: hold L1 reset disable संकेत low */
	अगर (!sunxi_core_is_cortex_a15(cpu, cluster)) अणु
		reg = पढ़ोl(cpucfg_base + CPUCFG_CX_CTRL_REG0(cluster));
		reg &= ~CPUCFG_CX_CTRL_REG0_L1_RST_DISABLE(cpu);
		ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_CTRL_REG0(cluster));
	पूर्ण

	/* निश्चित processor related resets */
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));
	reg &= ~CPUCFG_CX_RST_CTRL_DBG_RST(cpu);

	/*
	 * Allwinner code also निश्चितs resets क्रम NEON on A15. According
	 * to ARM manuals, निश्चितing घातer-on reset is sufficient.
	 */
	अगर (!sunxi_core_is_cortex_a15(cpu, cluster))
		reg &= ~CPUCFG_CX_RST_CTRL_ETM_RST(cpu);

	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));

	/* खोलो घातer चयन */
	sunxi_cpu_घातer_चयन_set(cpu, cluster, true);

	/* Handle A83T bit swap */
	अगर (is_a83t) अणु
		अगर (cpu == 0)
			cpu = 4;
	पूर्ण

	/* clear processor घातer gate */
	reg = पढ़ोl(prcm_base + PRCM_PWROFF_GATING_REG(cluster));
	reg &= ~PRCM_PWROFF_GATING_REG_CORE(cpu);
	ग_लिखोl(reg, prcm_base + PRCM_PWROFF_GATING_REG(cluster));
	udelay(20);

	/* Handle A83T bit swap */
	अगर (is_a83t) अणु
		अगर (cpu == 4)
			cpu = 0;
	पूर्ण

	/* de-निश्चित processor घातer-on reset */
	reg = पढ़ोl(prcm_base + PRCM_CPU_PO_RST_CTRL(cluster));
	reg |= PRCM_CPU_PO_RST_CTRL_CORE(cpu);
	ग_लिखोl(reg, prcm_base + PRCM_CPU_PO_RST_CTRL(cluster));

	अगर (is_a83t) अणु
		reg  = पढ़ोl(r_cpucfg_base +
			     R_CPUCFG_CLUSTER_PO_RST_CTRL(cluster));
		reg |= R_CPUCFG_CLUSTER_PO_RST_CTRL_CORE(cpu);
		ग_लिखोl(reg, r_cpucfg_base +
		       R_CPUCFG_CLUSTER_PO_RST_CTRL(cluster));
		udelay(10);
	पूर्ण

	/* de-निश्चित all processor resets */
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));
	reg |= CPUCFG_CX_RST_CTRL_DBG_RST(cpu);
	reg |= CPUCFG_CX_RST_CTRL_CORE_RST(cpu);
	अगर (!sunxi_core_is_cortex_a15(cpu, cluster))
		reg |= CPUCFG_CX_RST_CTRL_ETM_RST(cpu);
	अन्यथा
		reg |= CPUCFG_CX_RST_CTRL_CX_RST(cpu); /* NEON */
	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_cluster_घातerup(अचिन्हित पूर्णांक cluster)
अणु
	u32 reg;

	pr_debug("%s: cluster %u\n", __func__, cluster);
	अगर (cluster >= SUNXI_NR_CLUSTERS)
		वापस -EINVAL;

	/* For A83T, निश्चित cluster cores resets */
	अगर (is_a83t) अणु
		reg = पढ़ोl(cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));
		reg &= ~CPUCFG_CX_RST_CTRL_CORE_RST_ALL;   /* Core Reset    */
		ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));
		udelay(10);
	पूर्ण

	/* निश्चित ACINACTM */
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_CTRL_REG1(cluster));
	reg |= CPUCFG_CX_CTRL_REG1_ACINACTM;
	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_CTRL_REG1(cluster));

	/* निश्चित cluster processor घातer-on resets */
	reg = पढ़ोl(prcm_base + PRCM_CPU_PO_RST_CTRL(cluster));
	reg &= ~PRCM_CPU_PO_RST_CTRL_CORE_ALL;
	ग_लिखोl(reg, prcm_base + PRCM_CPU_PO_RST_CTRL(cluster));

	/* निश्चित cluster cores resets */
	अगर (is_a83t) अणु
		reg  = पढ़ोl(r_cpucfg_base +
			     R_CPUCFG_CLUSTER_PO_RST_CTRL(cluster));
		reg &= ~CPUCFG_CX_RST_CTRL_CORE_RST_ALL;
		ग_लिखोl(reg, r_cpucfg_base +
		       R_CPUCFG_CLUSTER_PO_RST_CTRL(cluster));
		udelay(10);
	पूर्ण

	/* निश्चित cluster resets */
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));
	reg &= ~CPUCFG_CX_RST_CTRL_DBG_SOC_RST;
	reg &= ~CPUCFG_CX_RST_CTRL_DBG_RST_ALL;
	reg &= ~CPUCFG_CX_RST_CTRL_H_RST;
	reg &= ~CPUCFG_CX_RST_CTRL_L2_RST;

	/*
	 * Allwinner code also निश्चितs resets क्रम NEON on A15. According
	 * to ARM manuals, निश्चितing घातer-on reset is sufficient.
	 */
	अगर (!sunxi_core_is_cortex_a15(0, cluster))
		reg &= ~CPUCFG_CX_RST_CTRL_ETM_RST_ALL;

	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));

	/* hold L1/L2 reset disable संकेतs low */
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_CTRL_REG0(cluster));
	अगर (sunxi_core_is_cortex_a15(0, cluster)) अणु
		/* Cortex-A15: hold L2RSTDISABLE low */
		reg &= ~CPUCFG_CX_CTRL_REG0_L2_RST_DISABLE_A15;
	पूर्ण अन्यथा अणु
		/* Cortex-A7: hold L1RSTDISABLE and L2RSTDISABLE low */
		reg &= ~CPUCFG_CX_CTRL_REG0_L1_RST_DISABLE_ALL;
		reg &= ~CPUCFG_CX_CTRL_REG0_L2_RST_DISABLE_A7;
	पूर्ण
	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_CTRL_REG0(cluster));

	/* clear cluster घातer gate */
	reg = पढ़ोl(prcm_base + PRCM_PWROFF_GATING_REG(cluster));
	अगर (is_a83t)
		reg &= ~PRCM_PWROFF_GATING_REG_CLUSTER_SUN8I;
	अन्यथा
		reg &= ~PRCM_PWROFF_GATING_REG_CLUSTER_SUN9I;
	ग_लिखोl(reg, prcm_base + PRCM_PWROFF_GATING_REG(cluster));
	udelay(20);

	/* de-निश्चित cluster resets */
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));
	reg |= CPUCFG_CX_RST_CTRL_DBG_SOC_RST;
	reg |= CPUCFG_CX_RST_CTRL_H_RST;
	reg |= CPUCFG_CX_RST_CTRL_L2_RST;
	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));

	/* de-निश्चित ACINACTM */
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_CTRL_REG1(cluster));
	reg &= ~CPUCFG_CX_CTRL_REG1_ACINACTM;
	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_CTRL_REG1(cluster));

	वापस 0;
पूर्ण

/*
 * This bit is shared between the initial nocache_trampoline call to
 * enable CCI-400 and proper cluster cache disable beक्रमe घातer करोwn.
 */
अटल व्योम sunxi_cluster_cache_disable_without_axi(व्योम)
अणु
	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A15) अणु
		/*
		 * On the Cortex-A15 we need to disable
		 * L2 prefetching beक्रमe flushing the cache.
		 */
		यंत्र अस्थिर(
		"mcr	p15, 1, %0, c15, c0, 3\n"
		"isb\n"
		"dsb"
		: : "r" (0x400));
	पूर्ण

	/* Flush all cache levels क्रम this cluster. */
	v7_निकास_coherency_flush(all);

	/*
	 * Disable cluster-level coherency by masking
	 * incoming snoops and DVM messages:
	 */
	cci_disable_port_by_cpu(पढ़ो_cpuid_mpidr());
पूर्ण

अटल पूर्णांक sunxi_mc_smp_cpu_table[SUNXI_NR_CLUSTERS][SUNXI_CPUS_PER_CLUSTER];
पूर्णांक sunxi_mc_smp_first_comer;

अटल DEFINE_SPINLOCK(boot_lock);

अटल bool sunxi_mc_smp_cluster_is_करोwn(अचिन्हित पूर्णांक cluster)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SUNXI_CPUS_PER_CLUSTER; i++)
		अगर (sunxi_mc_smp_cpu_table[cluster][i])
			वापस false;
	वापस true;
पूर्ण

अटल व्योम sunxi_mc_smp_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	/* Clear hotplug support magic flags क्रम cpu0 */
	अगर (cpu == 0)
		sunxi_cpu0_hotplug_support_set(false);
पूर्ण

अटल पूर्णांक sunxi_mc_smp_boot_secondary(अचिन्हित पूर्णांक l_cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;

	mpidr = cpu_logical_map(l_cpu);
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	अगर (!cpucfg_base)
		वापस -ENODEV;
	अगर (cluster >= SUNXI_NR_CLUSTERS || cpu >= SUNXI_CPUS_PER_CLUSTER)
		वापस -EINVAL;

	spin_lock_irq(&boot_lock);

	अगर (sunxi_mc_smp_cpu_table[cluster][cpu])
		जाओ out;

	अगर (sunxi_mc_smp_cluster_is_करोwn(cluster)) अणु
		sunxi_mc_smp_first_comer = true;
		sunxi_cluster_घातerup(cluster);
	पूर्ण अन्यथा अणु
		sunxi_mc_smp_first_comer = false;
	पूर्ण

	/* This is पढ़ो by incoming CPUs with their cache and MMU disabled */
	sync_cache_w(&sunxi_mc_smp_first_comer);
	sunxi_cpu_घातerup(cpu, cluster);

out:
	sunxi_mc_smp_cpu_table[cluster][cpu]++;
	spin_unlock_irq(&boot_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम sunxi_cluster_cache_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cluster = MPIDR_AFFINITY_LEVEL(पढ़ो_cpuid_mpidr(), 1);
	u32 reg;

	pr_debug("%s: cluster %u\n", __func__, cluster);

	sunxi_cluster_cache_disable_without_axi();

	/* last man standing, निश्चित ACINACTM */
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_CTRL_REG1(cluster));
	reg |= CPUCFG_CX_CTRL_REG1_ACINACTM;
	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_CTRL_REG1(cluster));
पूर्ण

अटल व्योम sunxi_mc_smp_cpu_die(अचिन्हित पूर्णांक l_cpu)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	bool last_man;

	mpidr = cpu_logical_map(l_cpu);
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	pr_debug("%s: cluster %u cpu %u\n", __func__, cluster, cpu);

	spin_lock(&boot_lock);
	sunxi_mc_smp_cpu_table[cluster][cpu]--;
	अगर (sunxi_mc_smp_cpu_table[cluster][cpu] == 1) अणु
		/* A घातer_up request went ahead of us. */
		pr_debug("%s: aborting due to a power up request\n",
			 __func__);
		spin_unlock(&boot_lock);
		वापस;
	पूर्ण अन्यथा अगर (sunxi_mc_smp_cpu_table[cluster][cpu] > 1) अणु
		pr_err("Cluster %d CPU%d boots multiple times\n",
		       cluster, cpu);
		BUG();
	पूर्ण

	last_man = sunxi_mc_smp_cluster_is_करोwn(cluster);
	spin_unlock(&boot_lock);

	gic_cpu_अगर_करोwn(0);
	अगर (last_man)
		sunxi_cluster_cache_disable();
	अन्यथा
		v7_निकास_coherency_flush(louis);

	क्रम (;;)
		wfi();
पूर्ण

अटल पूर्णांक sunxi_cpu_घातerकरोwn(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	u32 reg;
	पूर्णांक gating_bit = cpu;

	pr_debug("%s: cluster %u cpu %u\n", __func__, cluster, cpu);
	अगर (cpu >= SUNXI_CPUS_PER_CLUSTER || cluster >= SUNXI_NR_CLUSTERS)
		वापस -EINVAL;

	अगर (is_a83t && cpu == 0)
		gating_bit = 4;

	/* gate processor घातer */
	reg = पढ़ोl(prcm_base + PRCM_PWROFF_GATING_REG(cluster));
	reg |= PRCM_PWROFF_GATING_REG_CORE(gating_bit);
	ग_लिखोl(reg, prcm_base + PRCM_PWROFF_GATING_REG(cluster));
	udelay(20);

	/* बंद घातer चयन */
	sunxi_cpu_घातer_चयन_set(cpu, cluster, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_cluster_घातerकरोwn(अचिन्हित पूर्णांक cluster)
अणु
	u32 reg;

	pr_debug("%s: cluster %u\n", __func__, cluster);
	अगर (cluster >= SUNXI_NR_CLUSTERS)
		वापस -EINVAL;

	/* निश्चित cluster resets or प्रणाली will hang */
	pr_debug("%s: assert cluster reset\n", __func__);
	reg = पढ़ोl(cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));
	reg &= ~CPUCFG_CX_RST_CTRL_DBG_SOC_RST;
	reg &= ~CPUCFG_CX_RST_CTRL_H_RST;
	reg &= ~CPUCFG_CX_RST_CTRL_L2_RST;
	ग_लिखोl(reg, cpucfg_base + CPUCFG_CX_RST_CTRL(cluster));

	/* gate cluster घातer */
	pr_debug("%s: gate cluster power\n", __func__);
	reg = पढ़ोl(prcm_base + PRCM_PWROFF_GATING_REG(cluster));
	अगर (is_a83t)
		reg |= PRCM_PWROFF_GATING_REG_CLUSTER_SUN8I;
	अन्यथा
		reg |= PRCM_PWROFF_GATING_REG_CLUSTER_SUN9I;
	ग_लिखोl(reg, prcm_base + PRCM_PWROFF_GATING_REG(cluster));
	udelay(20);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_mc_smp_cpu_समाप्त(अचिन्हित पूर्णांक l_cpu)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	अचिन्हित पूर्णांक tries, count;
	पूर्णांक ret = 0;
	u32 reg;

	mpidr = cpu_logical_map(l_cpu);
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	/* This should never happen */
	अगर (WARN_ON(cluster >= SUNXI_NR_CLUSTERS ||
		    cpu >= SUNXI_CPUS_PER_CLUSTER))
		वापस 0;

	/* रुको क्रम CPU core to die and enter WFI */
	count = TIMEOUT_USEC / POLL_USEC;
	spin_lock_irq(&boot_lock);
	क्रम (tries = 0; tries < count; tries++) अणु
		spin_unlock_irq(&boot_lock);
		usleep_range(POLL_USEC / 2, POLL_USEC);
		spin_lock_irq(&boot_lock);

		/*
		 * If the user turns off a bunch of cores at the same
		 * समय, the kernel might call cpu_समाप्त beक्रमe some of
		 * them are पढ़ोy. This is because boot_lock serializes
		 * both cpu_die and cpu_समाप्त callbacks. Either one could
		 * run first. We should रुको क्रम cpu_die to complete.
		 */
		अगर (sunxi_mc_smp_cpu_table[cluster][cpu])
			जारी;

		reg = पढ़ोl(cpucfg_base + CPUCFG_CX_STATUS(cluster));
		अगर (reg & CPUCFG_CX_STATUS_STANDBYWFI(cpu))
			अवरोध;
	पूर्ण

	अगर (tries >= count) अणु
		ret = ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* घातer करोwn CPU core */
	sunxi_cpu_घातerकरोwn(cpu, cluster);

	अगर (!sunxi_mc_smp_cluster_is_करोwn(cluster))
		जाओ out;

	/* रुको क्रम cluster L2 WFI */
	ret = पढ़ोl_poll_समयout(cpucfg_base + CPUCFG_CX_STATUS(cluster), reg,
				 reg & CPUCFG_CX_STATUS_STANDBYWFIL2,
				 POLL_USEC, TIMEOUT_USEC);
	अगर (ret) अणु
		/*
		 * Ignore समयout on the cluster. Leaving the cluster on
		 * will not affect प्रणाली execution, just use a bit more
		 * घातer. But वापसing an error here will only confuse
		 * the user as the CPU has alपढ़ोy been shutकरोwn.
		 */
		ret = 0;
		जाओ out;
	पूर्ण

	/* Power करोwn cluster */
	sunxi_cluster_घातerकरोwn(cluster);

out:
	spin_unlock_irq(&boot_lock);
	pr_debug("%s: cluster %u cpu %u powerdown: %d\n",
		 __func__, cluster, cpu, ret);
	वापस !ret;
पूर्ण

अटल bool sunxi_mc_smp_cpu_can_disable(अचिन्हित पूर्णांक cpu)
अणु
	/* CPU0 hotplug not handled क्रम sun8i-a83t */
	अगर (is_a83t)
		अगर (cpu == 0)
			वापस false;
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations sunxi_mc_smp_smp_ops __initस्थिर = अणु
	.smp_secondary_init	= sunxi_mc_smp_secondary_init,
	.smp_boot_secondary	= sunxi_mc_smp_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= sunxi_mc_smp_cpu_die,
	.cpu_समाप्त		= sunxi_mc_smp_cpu_समाप्त,
	.cpu_can_disable	= sunxi_mc_smp_cpu_can_disable,
#पूर्ण_अगर
पूर्ण;

अटल bool __init sunxi_mc_smp_cpu_table_init(व्योम)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;

	mpidr = पढ़ो_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	अगर (cluster >= SUNXI_NR_CLUSTERS || cpu >= SUNXI_CPUS_PER_CLUSTER) अणु
		pr_err("%s: boot CPU is out of bounds!\n", __func__);
		वापस false;
	पूर्ण
	sunxi_mc_smp_cpu_table[cluster][cpu] = 1;
	वापस true;
पूर्ण

/*
 * Adapted from arch/arm/common/mc_smp_entry.c
 *
 * We need the trampoline code to enable CCI-400 on the first cluster
 */
प्रकार typeof(cpu_reset) phys_reset_t;

अटल पूर्णांक __init nocache_trampoline(अचिन्हित दीर्घ __unused)
अणु
	phys_reset_t phys_reset;

	setup_mm_क्रम_reboot();
	sunxi_cluster_cache_disable_without_axi();

	phys_reset = (phys_reset_t)(अचिन्हित दीर्घ)__pa_symbol(cpu_reset);
	phys_reset(__pa_symbol(sunxi_mc_smp_resume), false);
	BUG();
पूर्ण

अटल पूर्णांक __init sunxi_mc_smp_loopback(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * We're going to soft-restart the current CPU through the
	 * low-level MCPM code by leveraging the suspend/resume
	 * infraकाष्ठाure. Let's play it safe by using cpu_pm_enter()
	 * in हाल the CPU init code path resets the VFP or similar.
	 */
	sunxi_mc_smp_first_comer = true;
	local_irq_disable();
	local_fiq_disable();
	ret = cpu_pm_enter();
	अगर (!ret) अणु
		ret = cpu_suspend(0, nocache_trampoline);
		cpu_pm_निकास();
	पूर्ण
	local_fiq_enable();
	local_irq_enable();
	sunxi_mc_smp_first_comer = false;

	वापस ret;
पूर्ण

/*
 * This holds any device nodes that we requested resources क्रम,
 * so that we may easily release resources in the error path.
 */
काष्ठा sunxi_mc_smp_nodes अणु
	काष्ठा device_node *prcm_node;
	काष्ठा device_node *cpucfg_node;
	काष्ठा device_node *sram_node;
	काष्ठा device_node *r_cpucfg_node;
पूर्ण;

/* This काष्ठाure holds SoC-specअगरic bits tied to an enable-method string. */
काष्ठा sunxi_mc_smp_data अणु
	स्थिर अक्षर *enable_method;
	पूर्णांक (*get_smp_nodes)(काष्ठा sunxi_mc_smp_nodes *nodes);
	bool is_a83t;
पूर्ण;

अटल व्योम __init sunxi_mc_smp_put_nodes(काष्ठा sunxi_mc_smp_nodes *nodes)
अणु
	of_node_put(nodes->prcm_node);
	of_node_put(nodes->cpucfg_node);
	of_node_put(nodes->sram_node);
	of_node_put(nodes->r_cpucfg_node);
	स_रखो(nodes, 0, माप(*nodes));
पूर्ण

अटल पूर्णांक __init sun9i_a80_get_smp_nodes(काष्ठा sunxi_mc_smp_nodes *nodes)
अणु
	nodes->prcm_node = of_find_compatible_node(शून्य, शून्य,
						   "allwinner,sun9i-a80-prcm");
	अगर (!nodes->prcm_node) अणु
		pr_err("%s: PRCM not available\n", __func__);
		वापस -ENODEV;
	पूर्ण

	nodes->cpucfg_node = of_find_compatible_node(शून्य, शून्य,
						     "allwinner,sun9i-a80-cpucfg");
	अगर (!nodes->cpucfg_node) अणु
		pr_err("%s: CPUCFG not available\n", __func__);
		वापस -ENODEV;
	पूर्ण

	nodes->sram_node = of_find_compatible_node(शून्य, शून्य,
						   "allwinner,sun9i-a80-smp-sram");
	अगर (!nodes->sram_node) अणु
		pr_err("%s: Secure SRAM not available\n", __func__);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init sun8i_a83t_get_smp_nodes(काष्ठा sunxi_mc_smp_nodes *nodes)
अणु
	nodes->prcm_node = of_find_compatible_node(शून्य, शून्य,
						   "allwinner,sun8i-a83t-r-ccu");
	अगर (!nodes->prcm_node) अणु
		pr_err("%s: PRCM not available\n", __func__);
		वापस -ENODEV;
	पूर्ण

	nodes->cpucfg_node = of_find_compatible_node(शून्य, शून्य,
						     "allwinner,sun8i-a83t-cpucfg");
	अगर (!nodes->cpucfg_node) अणु
		pr_err("%s: CPUCFG not available\n", __func__);
		वापस -ENODEV;
	पूर्ण

	nodes->r_cpucfg_node = of_find_compatible_node(शून्य, शून्य,
						       "allwinner,sun8i-a83t-r-cpucfg");
	अगर (!nodes->r_cpucfg_node) अणु
		pr_err("%s: RCPUCFG not available\n", __func__);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sunxi_mc_smp_data sunxi_mc_smp_data[] __initस्थिर = अणु
	अणु
		.enable_method	= "allwinner,sun9i-a80-smp",
		.get_smp_nodes	= sun9i_a80_get_smp_nodes,
	पूर्ण,
	अणु
		.enable_method	= "allwinner,sun8i-a83t-smp",
		.get_smp_nodes	= sun8i_a83t_get_smp_nodes,
		.is_a83t	= true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sunxi_mc_smp_init(व्योम)
अणु
	काष्ठा sunxi_mc_smp_nodes nodes = अणु 0 पूर्ण;
	काष्ठा device_node *node;
	काष्ठा resource res;
	व्योम __iomem *addr;
	पूर्णांक i, ret;

	/*
	 * Don't bother checking the "cpus" node, as an enable-method
	 * property in that node is unकरोcumented.
	 */
	node = of_cpu_device_node_get(0);
	अगर (!node)
		वापस -ENODEV;

	/*
	 * We can't actually use the enable-method magic in the kernel.
	 * Our loopback / trampoline code uses the CPU suspend framework,
	 * which requires the identity mapping be available. It would not
	 * yet be available अगर we used the .init_cpus or .prepare_cpus
	 * callbacks in smp_operations, which we would use अगर we were to
	 * use CPU_METHOD_OF_DECLARE
	 */
	क्रम (i = 0; i < ARRAY_SIZE(sunxi_mc_smp_data); i++) अणु
		ret = of_property_match_string(node, "enable-method",
					       sunxi_mc_smp_data[i].enable_method);
		अगर (!ret)
			अवरोध;
	पूर्ण

	is_a83t = sunxi_mc_smp_data[i].is_a83t;

	of_node_put(node);
	अगर (ret)
		वापस -ENODEV;

	अगर (!sunxi_mc_smp_cpu_table_init())
		वापस -EINVAL;

	अगर (!cci_probed()) अणु
		pr_err("%s: CCI-400 not available\n", __func__);
		वापस -ENODEV;
	पूर्ण

	/* Get needed device tree nodes */
	ret = sunxi_mc_smp_data[i].get_smp_nodes(&nodes);
	अगर (ret)
		जाओ err_put_nodes;

	/*
	 * Unक्रमtunately we can not request the I/O region क्रम the PRCM.
	 * It is shared with the PRCM घड़ी.
	 */
	prcm_base = of_iomap(nodes.prcm_node, 0);
	अगर (!prcm_base) अणु
		pr_err("%s: failed to map PRCM registers\n", __func__);
		ret = -ENOMEM;
		जाओ err_put_nodes;
	पूर्ण

	cpucfg_base = of_io_request_and_map(nodes.cpucfg_node, 0,
					    "sunxi-mc-smp");
	अगर (IS_ERR(cpucfg_base)) अणु
		ret = PTR_ERR(cpucfg_base);
		pr_err("%s: failed to map CPUCFG registers: %d\n",
		       __func__, ret);
		जाओ err_unmap_prcm;
	पूर्ण

	अगर (is_a83t) अणु
		r_cpucfg_base = of_io_request_and_map(nodes.r_cpucfg_node,
						      0, "sunxi-mc-smp");
		अगर (IS_ERR(r_cpucfg_base)) अणु
			ret = PTR_ERR(r_cpucfg_base);
			pr_err("%s: failed to map R-CPUCFG registers\n",
			       __func__);
			जाओ err_unmap_release_cpucfg;
		पूर्ण
	पूर्ण अन्यथा अणु
		sram_b_smp_base = of_io_request_and_map(nodes.sram_node, 0,
							"sunxi-mc-smp");
		अगर (IS_ERR(sram_b_smp_base)) अणु
			ret = PTR_ERR(sram_b_smp_base);
			pr_err("%s: failed to map secure SRAM\n", __func__);
			जाओ err_unmap_release_cpucfg;
		पूर्ण
	पूर्ण

	/* Configure CCI-400 क्रम boot cluster */
	ret = sunxi_mc_smp_loopback();
	अगर (ret) अणु
		pr_err("%s: failed to configure boot cluster: %d\n",
		       __func__, ret);
		जाओ err_unmap_release_sram_rcpucfg;
	पूर्ण

	/* We करोn't need the device nodes anymore */
	sunxi_mc_smp_put_nodes(&nodes);

	/* Set the hardware entry poपूर्णांक address */
	अगर (is_a83t)
		addr = r_cpucfg_base + R_CPUCFG_CPU_SOFT_ENTRY_REG;
	अन्यथा
		addr = prcm_base + PRCM_CPU_SOFT_ENTRY_REG;
	ग_लिखोl(__pa_symbol(sunxi_mc_smp_secondary_startup), addr);

	/* Actually enable multi cluster SMP */
	smp_set_ops(&sunxi_mc_smp_smp_ops);

	pr_info("sunxi multi cluster SMP support installed\n");

	वापस 0;

err_unmap_release_sram_rcpucfg:
	अगर (is_a83t) अणु
		iounmap(r_cpucfg_base);
		of_address_to_resource(nodes.r_cpucfg_node, 0, &res);
	पूर्ण अन्यथा अणु
		iounmap(sram_b_smp_base);
		of_address_to_resource(nodes.sram_node, 0, &res);
	पूर्ण
	release_mem_region(res.start, resource_size(&res));
err_unmap_release_cpucfg:
	iounmap(cpucfg_base);
	of_address_to_resource(nodes.cpucfg_node, 0, &res);
	release_mem_region(res.start, resource_size(&res));
err_unmap_prcm:
	iounmap(prcm_base);
err_put_nodes:
	sunxi_mc_smp_put_nodes(&nodes);
	वापस ret;
पूर्ण

early_initcall(sunxi_mc_smp_init);
