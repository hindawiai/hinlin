<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// Based on arch/arm/mach-vexpress/dcscb.c

#समावेश <linux/arm-cci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/smp_plat.h>

#समावेश "common.h"

#घोषणा EXYNOS5420_CPUS_PER_CLUSTER	4
#घोषणा EXYNOS5420_NR_CLUSTERS		2

#घोषणा EXYNOS5420_ENABLE_AUTOMATIC_CORE_DOWN	BIT(9)
#घोषणा EXYNOS5420_USE_ARM_CORE_DOWN_STATE	BIT(29)
#घोषणा EXYNOS5420_USE_L2_COMMON_UP_STATE	BIT(30)

अटल व्योम __iomem *ns_sram_base_addr __ro_after_init;
अटल bool secure_firmware __ro_after_init;

/*
 * The common v7_निकास_coherency_flush API could not be used because of the
 * Erratum 799270 workaround. This macro is the same as the common one (in
 * arch/arm/include/यंत्र/cacheflush.h) except क्रम the erratum handling.
 */
#घोषणा exynos_v7_निकास_coherency_flush(level) \
	यंत्र अस्थिर( \
	"stmfd	sp!, {fp, ip}\n\t"\
	"mrc	p15, 0, r0, c1, c0, 0	@ get SCTLR\n\t" \
	"bic	r0, r0, #"__stringअगरy(CR_C)"\n\t" \
	"mcr	p15, 0, r0, c1, c0, 0	@ set SCTLR\n\t" \
	"isb\n\t"\
	"bl	v7_flush_dcache_"__stringअगरy(level)"\n\t" \
	"mrc	p15, 0, r0, c1, c0, 1	@ get ACTLR\n\t" \
	"bic	r0, r0, #(1 << 6)	@ disable local coherency\n\t" \
	/* Dummy Load of a device रेजिस्टर to aव्योम Erratum 799270 */ \
	"ldr	r4, [%0]\n\t" \
	"and	r4, r4, #0\n\t" \
	"orr	r0, r0, r4\n\t" \
	"mcr	p15, 0, r0, c1, c0, 1	@ set ACTLR\n\t" \
	"isb\n\t" \
	"dsb\n\t" \
	"ldmfd	sp!, {fp, ip}" \
	: \
	: "Ir" (pmu_base_addr + S5P_INFORM0) \
	: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", \
	  "r9", "r10", "lr", "memory")

अटल पूर्णांक exynos_cpu_घातerup(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक cpunr = cpu + (cluster * EXYNOS5420_CPUS_PER_CLUSTER);
	bool state;

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	अगर (cpu >= EXYNOS5420_CPUS_PER_CLUSTER ||
		cluster >= EXYNOS5420_NR_CLUSTERS)
		वापस -EINVAL;

	state = exynos_cpu_घातer_state(cpunr);
	exynos_cpu_घातer_up(cpunr);
	अगर (!state && secure_firmware) अणु
		/*
		 * This assumes the cluster number of the big cores(Cortex A15)
		 * is 0 and the Little cores(Cortex A7) is 1.
		 * When the प्रणाली was booted from the Little core,
		 * they should be reset during घातer up cpu.
		 */
		अगर (cluster &&
		    cluster == MPIDR_AFFINITY_LEVEL(cpu_logical_map(0), 1)) अणु
			अचिन्हित पूर्णांक समयout = 16;

			/*
			 * Beक्रमe we reset the Little cores, we should रुको
			 * the SPARE2 रेजिस्टर is set to 1 because the init
			 * codes of the iROM will set the रेजिस्टर after
			 * initialization.
			 */
			जबतक (समयout && !pmu_raw_पढ़ोl(S5P_PMU_SPARE2)) अणु
				समयout--;
				udelay(10);
			पूर्ण

			अगर (समयout == 0) अणु
				pr_err("cpu %u cluster %u powerup failed\n",
				       cpu, cluster);
				exynos_cpu_घातer_करोwn(cpunr);
				वापस -ETIMEDOUT;
			पूर्ण

			pmu_raw_ग_लिखोl(EXYNOS5420_KFC_CORE_RESET(cpu),
					EXYNOS_SWRESET);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_cluster_घातerup(अचिन्हित पूर्णांक cluster)
अणु
	pr_debug("%s: cluster %u\n", __func__, cluster);
	अगर (cluster >= EXYNOS5420_NR_CLUSTERS)
		वापस -EINVAL;

	exynos_cluster_घातer_up(cluster);
	वापस 0;
पूर्ण

अटल व्योम exynos_cpu_घातerकरोwn_prepare(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक cpunr = cpu + (cluster * EXYNOS5420_CPUS_PER_CLUSTER);

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	BUG_ON(cpu >= EXYNOS5420_CPUS_PER_CLUSTER ||
			cluster >= EXYNOS5420_NR_CLUSTERS);
	exynos_cpu_घातer_करोwn(cpunr);
पूर्ण

अटल व्योम exynos_cluster_घातerकरोwn_prepare(अचिन्हित पूर्णांक cluster)
अणु
	pr_debug("%s: cluster %u\n", __func__, cluster);
	BUG_ON(cluster >= EXYNOS5420_NR_CLUSTERS);
	exynos_cluster_घातer_करोwn(cluster);
पूर्ण

अटल व्योम exynos_cpu_cache_disable(व्योम)
अणु
	/* Disable and flush the local CPU cache. */
	exynos_v7_निकास_coherency_flush(louis);
पूर्ण

अटल व्योम exynos_cluster_cache_disable(व्योम)
अणु
	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A15) अणु
		/*
		 * On the Cortex-A15 we need to disable
		 * L2 prefetching beक्रमe flushing the cache.
		 */
		यंत्र अस्थिर(
		"mcr	p15, 1, %0, c15, c0, 3\n\t"
		"isb\n\t"
		"dsb"
		: : "r" (0x400));
	पूर्ण

	/* Flush all cache levels क्रम this cluster. */
	exynos_v7_निकास_coherency_flush(all);

	/*
	 * Disable cluster-level coherency by masking
	 * incoming snoops and DVM messages:
	 */
	cci_disable_port_by_cpu(पढ़ो_cpuid_mpidr());
पूर्ण

अटल पूर्णांक exynos_रुको_क्रम_घातerकरोwn(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक tries = 100;
	अचिन्हित पूर्णांक cpunr = cpu + (cluster * EXYNOS5420_CPUS_PER_CLUSTER);

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	BUG_ON(cpu >= EXYNOS5420_CPUS_PER_CLUSTER ||
			cluster >= EXYNOS5420_NR_CLUSTERS);

	/* Wait क्रम the core state to be OFF */
	जबतक (tries--) अणु
		अगर ((exynos_cpu_घातer_state(cpunr) == 0))
			वापस 0; /* success: the CPU is halted */

		/* Otherwise, रुको and retry: */
		msleep(1);
	पूर्ण

	वापस -ETIMEDOUT; /* समयout */
पूर्ण

अटल व्योम exynos_cpu_is_up(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	/* especially when resuming: make sure घातer control is set */
	exynos_cpu_घातerup(cpu, cluster);
पूर्ण

अटल स्थिर काष्ठा mcpm_platक्रमm_ops exynos_घातer_ops = अणु
	.cpu_घातerup		= exynos_cpu_घातerup,
	.cluster_घातerup	= exynos_cluster_घातerup,
	.cpu_घातerकरोwn_prepare	= exynos_cpu_घातerकरोwn_prepare,
	.cluster_घातerकरोwn_prepare = exynos_cluster_घातerकरोwn_prepare,
	.cpu_cache_disable	= exynos_cpu_cache_disable,
	.cluster_cache_disable	= exynos_cluster_cache_disable,
	.रुको_क्रम_घातerकरोwn	= exynos_रुको_क्रम_घातerकरोwn,
	.cpu_is_up		= exynos_cpu_is_up,
पूर्ण;

/*
 * Enable cluster-level coherency, in preparation क्रम turning on the MMU.
 */
अटल व्योम __naked exynos_pm_घातer_up_setup(अचिन्हित पूर्णांक affinity_level)
अणु
	यंत्र अस्थिर ("\n"
	"cmp	r0, #1\n"
	"bxne	lr\n"
	"b	cci_enable_port_for_self");
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos_dt_mcpm_match[] = अणु
	अणु .compatible = "samsung,exynos5420" पूर्ण,
	अणु .compatible = "samsung,exynos5800" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम exynos_mcpm_setup_entry_poपूर्णांक(व्योम)
अणु
	/*
	 * U-Boot SPL is hardcoded to jump to the start of ns_sram_base_addr
	 * as part of secondary_cpu_start().  Let's redirect it to the
	 * mcpm_entry_poपूर्णांक(). This is करोne during both secondary boot-up as
	 * well as प्रणाली resume.
	 */
	__raw_ग_लिखोl(0xe59f0000, ns_sram_base_addr);     /* ldr r0, [pc, #0] */
	__raw_ग_लिखोl(0xe12fff10, ns_sram_base_addr + 4); /* bx  r0 */
	__raw_ग_लिखोl(__pa_symbol(mcpm_entry_poपूर्णांक), ns_sram_base_addr + 8);
पूर्ण

अटल काष्ठा syscore_ops exynos_mcpm_syscore_ops = अणु
	.resume	= exynos_mcpm_setup_entry_poपूर्णांक,
पूर्ण;

अटल पूर्णांक __init exynos_mcpm_init(व्योम)
अणु
	काष्ठा device_node *node;
	अचिन्हित पूर्णांक value, i;
	पूर्णांक ret;

	node = of_find_matching_node(शून्य, exynos_dt_mcpm_match);
	अगर (!node)
		वापस -ENODEV;
	of_node_put(node);

	अगर (!cci_probed())
		वापस -ENODEV;

	node = of_find_compatible_node(शून्य, शून्य,
			"samsung,exynos4210-sysram-ns");
	अगर (!node)
		वापस -ENODEV;

	ns_sram_base_addr = of_iomap(node, 0);
	of_node_put(node);
	अगर (!ns_sram_base_addr) अणु
		pr_err("failed to map non-secure iRAM base address\n");
		वापस -ENOMEM;
	पूर्ण

	secure_firmware = exynos_secure_firmware_available();

	/*
	 * To increase the stability of KFC reset we need to program
	 * the PMU SPARE3 रेजिस्टर
	 */
	pmu_raw_ग_लिखोl(EXYNOS5420_SWRESET_KFC_SEL, S5P_PMU_SPARE3);

	ret = mcpm_platक्रमm_रेजिस्टर(&exynos_घातer_ops);
	अगर (!ret)
		ret = mcpm_sync_init(exynos_pm_घातer_up_setup);
	अगर (!ret)
		ret = mcpm_loopback(exynos_cluster_cache_disable); /* turn on the CCI */
	अगर (ret) अणु
		iounmap(ns_sram_base_addr);
		वापस ret;
	पूर्ण

	mcpm_smp_set_ops();

	pr_info("Exynos MCPM support installed\n");

	/*
	 * On Exynos5420/5800 क्रम the A15 and A7 clusters:
	 *
	 * EXYNOS5420_ENABLE_AUTOMATIC_CORE_DOWN ensures that all the cores
	 * in a cluster are turned off beक्रमe turning off the cluster L2.
	 *
	 * EXYNOS5420_USE_ARM_CORE_DOWN_STATE ensures that a cores is घातered
	 * off beक्रमe waking it up.
	 *
	 * EXYNOS5420_USE_L2_COMMON_UP_STATE ensures that cluster L2 will be
	 * turned on beक्रमe the first man is घातered up.
	 */
	क्रम (i = 0; i < EXYNOS5420_NR_CLUSTERS; i++) अणु
		value = pmu_raw_पढ़ोl(EXYNOS_COMMON_OPTION(i));
		value |= EXYNOS5420_ENABLE_AUTOMATIC_CORE_DOWN |
			 EXYNOS5420_USE_ARM_CORE_DOWN_STATE    |
			 EXYNOS5420_USE_L2_COMMON_UP_STATE;
		pmu_raw_ग_लिखोl(value, EXYNOS_COMMON_OPTION(i));
	पूर्ण

	exynos_mcpm_setup_entry_poपूर्णांक();

	रेजिस्टर_syscore_ops(&exynos_mcpm_syscore_ops);

	वापस ret;
पूर्ण

early_initcall(exynos_mcpm_init);
