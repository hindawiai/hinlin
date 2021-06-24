<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-vexpress/tc2_pm.c - TC2 घातer management support
 *
 * Created by:	Nicolas Pitre, October 2012
 * Copyright:	(C) 2012-2013  Linaro Limited
 *
 * Some portions of this file were originally written by Achin Gupta
 * Copyright:   (C) 2012  ARM Limited
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/irqchip/arm-gic.h>

#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cp15.h>

#समावेश <linux/arm-cci.h>

#समावेश "spc.h"

/* SCC conf रेजिस्टरs */
#घोषणा RESET_CTRL		0x018
#घोषणा RESET_A15_NCORERESET(cpu)	(1 << (2 + (cpu)))
#घोषणा RESET_A7_NCORERESET(cpu)	(1 << (16 + (cpu)))

#घोषणा A15_CONF		0x400
#घोषणा A7_CONF			0x500
#घोषणा SYS_INFO		0x700
#घोषणा SPC_BASE		0xb00

अटल व्योम __iomem *scc;

#घोषणा TC2_CLUSTERS			2
#घोषणा TC2_MAX_CPUS_PER_CLUSTER	3

अटल अचिन्हित पूर्णांक tc2_nr_cpus[TC2_CLUSTERS];

अटल पूर्णांक tc2_pm_cpu_घातerup(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	अगर (cluster >= TC2_CLUSTERS || cpu >= tc2_nr_cpus[cluster])
		वापस -EINVAL;
	ve_spc_set_resume_addr(cluster, cpu,
			       __pa_symbol(mcpm_entry_poपूर्णांक));
	ve_spc_cpu_wakeup_irq(cluster, cpu, true);
	वापस 0;
पूर्ण

अटल पूर्णांक tc2_pm_cluster_घातerup(अचिन्हित पूर्णांक cluster)
अणु
	pr_debug("%s: cluster %u\n", __func__, cluster);
	अगर (cluster >= TC2_CLUSTERS)
		वापस -EINVAL;
	ve_spc_घातerकरोwn(cluster, false);
	वापस 0;
पूर्ण

अटल व्योम tc2_pm_cpu_घातerकरोwn_prepare(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	BUG_ON(cluster >= TC2_CLUSTERS || cpu >= TC2_MAX_CPUS_PER_CLUSTER);
	ve_spc_cpu_wakeup_irq(cluster, cpu, true);
	/*
	 * If the CPU is committed to घातer करोwn, make sure
	 * the घातer controller will be in अक्षरge of waking it
	 * up upon IRQ, ie IRQ lines are cut from GIC CPU IF
	 * to the CPU by disabling the GIC CPU IF to prevent wfi
	 * from completing execution behind घातer controller back
	 */
	gic_cpu_अगर_करोwn(0);
पूर्ण

अटल व्योम tc2_pm_cluster_घातerकरोwn_prepare(अचिन्हित पूर्णांक cluster)
अणु
	pr_debug("%s: cluster %u\n", __func__, cluster);
	BUG_ON(cluster >= TC2_CLUSTERS);
	ve_spc_घातerकरोwn(cluster, true);
	ve_spc_global_wakeup_irq(true);
पूर्ण

अटल व्योम tc2_pm_cpu_cache_disable(व्योम)
अणु
	v7_निकास_coherency_flush(louis);
पूर्ण

अटल व्योम tc2_pm_cluster_cache_disable(व्योम)
अणु
	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A15) अणु
		/*
		 * On the Cortex-A15 we need to disable
		 * L2 prefetching beक्रमe flushing the cache.
		 */
		यंत्र अस्थिर(
		"mcr	p15, 1, %0, c15, c0, 3 \n\t"
		"isb	\n\t"
		"dsb	"
		: : "r" (0x400) );
	पूर्ण

	v7_निकास_coherency_flush(all);
	cci_disable_port_by_cpu(पढ़ो_cpuid_mpidr());
पूर्ण

अटल पूर्णांक tc2_core_in_reset(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	u32 mask = cluster ?
		  RESET_A7_NCORERESET(cpu)
		: RESET_A15_NCORERESET(cpu);

	वापस !(पढ़ोl_relaxed(scc + RESET_CTRL) & mask);
पूर्ण

#घोषणा POLL_MSEC 10
#घोषणा TIMEOUT_MSEC 1000

अटल पूर्णांक tc2_pm_रुको_क्रम_घातerकरोwn(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित tries;

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	BUG_ON(cluster >= TC2_CLUSTERS || cpu >= TC2_MAX_CPUS_PER_CLUSTER);

	क्रम (tries = 0; tries < TIMEOUT_MSEC / POLL_MSEC; ++tries) अणु
		pr_debug("%s(cpu=%u, cluster=%u): RESET_CTRL = 0x%08X\n",
			 __func__, cpu, cluster,
			 पढ़ोl_relaxed(scc + RESET_CTRL));

		/*
		 * We need the CPU to reach WFI, but the घातer
		 * controller may put the cluster in reset and
		 * घातer it off as soon as that happens, beक्रमe
		 * we have a chance to see STANDBYWFI.
		 *
		 * So we need to check क्रम both conditions:
		 */
		अगर (tc2_core_in_reset(cpu, cluster) ||
		    ve_spc_cpu_in_wfi(cpu, cluster))
			वापस 0; /* success: the CPU is halted */

		/* Otherwise, रुको and retry: */
		msleep(POLL_MSEC);
	पूर्ण

	वापस -ETIMEDOUT; /* समयout */
पूर्ण

अटल व्योम tc2_pm_cpu_suspend_prepare(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	ve_spc_set_resume_addr(cluster, cpu, __pa_symbol(mcpm_entry_poपूर्णांक));
पूर्ण

अटल व्योम tc2_pm_cpu_is_up(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	BUG_ON(cluster >= TC2_CLUSTERS || cpu >= TC2_MAX_CPUS_PER_CLUSTER);
	ve_spc_cpu_wakeup_irq(cluster, cpu, false);
	ve_spc_set_resume_addr(cluster, cpu, 0);
पूर्ण

अटल व्योम tc2_pm_cluster_is_up(अचिन्हित पूर्णांक cluster)
अणु
	pr_debug("%s: cluster %u\n", __func__, cluster);
	BUG_ON(cluster >= TC2_CLUSTERS);
	ve_spc_घातerकरोwn(cluster, false);
	ve_spc_global_wakeup_irq(false);
पूर्ण

अटल स्थिर काष्ठा mcpm_platक्रमm_ops tc2_pm_घातer_ops = अणु
	.cpu_घातerup		= tc2_pm_cpu_घातerup,
	.cluster_घातerup	= tc2_pm_cluster_घातerup,
	.cpu_suspend_prepare	= tc2_pm_cpu_suspend_prepare,
	.cpu_घातerकरोwn_prepare	= tc2_pm_cpu_घातerकरोwn_prepare,
	.cluster_घातerकरोwn_prepare = tc2_pm_cluster_घातerकरोwn_prepare,
	.cpu_cache_disable	= tc2_pm_cpu_cache_disable,
	.cluster_cache_disable	= tc2_pm_cluster_cache_disable,
	.रुको_क्रम_घातerकरोwn	= tc2_pm_रुको_क्रम_घातerकरोwn,
	.cpu_is_up		= tc2_pm_cpu_is_up,
	.cluster_is_up		= tc2_pm_cluster_is_up,
पूर्ण;

/*
 * Enable cluster-level coherency, in preparation क्रम turning on the MMU.
 */
अटल व्योम __naked tc2_pm_घातer_up_setup(अचिन्हित पूर्णांक affinity_level)
अणु
	यंत्र अस्थिर (" \n"
"	cmp	r0, #1 \n"
"	bxne	lr \n"
"	b	cci_enable_port_for_self ");
पूर्ण

अटल पूर्णांक __init tc2_pm_init(व्योम)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	पूर्णांक ret, irq;
	u32 a15_cluster_id, a7_cluster_id, sys_info;
	काष्ठा device_node *np;

	/*
	 * The घातer management-related features are hidden behind
	 * SCC रेजिस्टरs. We need to extract runसमय inक्रमmation like
	 * cluster ids and number of CPUs really available in clusters.
	 */
	np = of_find_compatible_node(शून्य, शून्य,
			"arm,vexpress-scc,v2p-ca15_a7");
	scc = of_iomap(np, 0);
	अगर (!scc)
		वापस -ENODEV;

	a15_cluster_id = पढ़ोl_relaxed(scc + A15_CONF) & 0xf;
	a7_cluster_id = पढ़ोl_relaxed(scc + A7_CONF) & 0xf;
	अगर (a15_cluster_id >= TC2_CLUSTERS || a7_cluster_id >= TC2_CLUSTERS)
		वापस -EINVAL;

	sys_info = पढ़ोl_relaxed(scc + SYS_INFO);
	tc2_nr_cpus[a15_cluster_id] = (sys_info >> 16) & 0xf;
	tc2_nr_cpus[a7_cluster_id] = (sys_info >> 20) & 0xf;

	irq = irq_of_parse_and_map(np, 0);

	/*
	 * A subset of the SCC रेजिस्टरs is also used to communicate
	 * with the SPC (घातer controller). We need to be able to
	 * drive it very early in the boot process to घातer up
	 * processors, so we initialize the SPC driver here.
	 */
	ret = ve_spc_init(scc + SPC_BASE, a15_cluster_id, irq);
	अगर (ret)
		वापस ret;

	अगर (!cci_probed())
		वापस -ENODEV;

	mpidr = पढ़ो_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	अगर (cluster >= TC2_CLUSTERS || cpu >= tc2_nr_cpus[cluster]) अणु
		pr_err("%s: boot CPU is out of bound!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ret = mcpm_platक्रमm_रेजिस्टर(&tc2_pm_घातer_ops);
	अगर (!ret) अणु
		mcpm_sync_init(tc2_pm_घातer_up_setup);
		/* test अगर we can (re)enable the CCI on our own */
		BUG_ON(mcpm_loopback(tc2_pm_cluster_cache_disable) != 0);
		pr_info("TC2 power management initialized\n");
	पूर्ण
	वापस ret;
पूर्ण

early_initcall(tc2_pm_init);
