<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2013 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <linux/reset.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "core.h"

अटल व्योम __iomem *scu_base_addr;
अटल व्योम __iomem *sram_base_addr;
अटल पूर्णांक ncores;

#घोषणा PMU_PWRDN_CON		0x08
#घोषणा PMU_PWRDN_ST		0x0c

#घोषणा PMU_PWRDN_SCU		4

अटल काष्ठा regmap *pmu;
अटल पूर्णांक has_pmu = true;

अटल पूर्णांक pmu_घातer_करोमुख्य_is_on(पूर्णांक pd)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pmu, PMU_PWRDN_ST, &val);
	अगर (ret < 0)
		वापस ret;

	वापस !(val & BIT(pd));
पूर्ण

अटल काष्ठा reset_control *rockchip_get_core_reset(पूर्णांक cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);
	काष्ठा device_node *np;

	/* The cpu device is only available after the initial core bringup */
	अगर (dev)
		np = dev->of_node;
	अन्यथा
		np = of_get_cpu_node(cpu, शून्य);

	वापस of_reset_control_get_exclusive(np, शून्य);
पूर्ण

अटल पूर्णांक pmu_set_घातer_करोमुख्य(पूर्णांक pd, bool on)
अणु
	u32 val = (on) ? 0 : BIT(pd);
	काष्ठा reset_control *rstc = rockchip_get_core_reset(pd);
	पूर्णांक ret;

	अगर (IS_ERR(rstc) && पढ़ो_cpuid_part() != ARM_CPU_PART_CORTEX_A9) अणु
		pr_err("%s: could not get reset control for core %d\n",
		       __func__, pd);
		वापस PTR_ERR(rstc);
	पूर्ण

	/*
	 * We need to soft reset the cpu when we turn off the cpu घातer करोमुख्य,
	 * or अन्यथा the active processors might be stalled when the inभागidual
	 * processor is घातered करोwn.
	 */
	अगर (!IS_ERR(rstc) && !on)
		reset_control_निश्चित(rstc);

	अगर (has_pmu) अणु
		ret = regmap_update_bits(pmu, PMU_PWRDN_CON, BIT(pd), val);
		अगर (ret < 0) अणु
			pr_err("%s: could not update power domain\n",
			       __func__);
			वापस ret;
		पूर्ण

		ret = -1;
		जबतक (ret != on) अणु
			ret = pmu_घातer_करोमुख्य_is_on(pd);
			अगर (ret < 0) अणु
				pr_err("%s: could not read power domain state\n",
				       __func__);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(rstc)) अणु
		अगर (on)
			reset_control_deनिश्चित(rstc);
		reset_control_put(rstc);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Handling of CPU cores
 */

अटल पूर्णांक rockchip_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret;

	अगर (!sram_base_addr || (has_pmu && !pmu)) अणु
		pr_err("%s: sram or pmu missing for cpu boot\n", __func__);
		वापस -ENXIO;
	पूर्ण

	अगर (cpu >= ncores) अणु
		pr_err("%s: cpu %d outside maximum number of cpus %d\n",
		       __func__, cpu, ncores);
		वापस -ENXIO;
	पूर्ण

	/* start the core */
	ret = pmu_set_घातer_करोमुख्य(0 + cpu, true);
	अगर (ret < 0)
		वापस ret;

	अगर (पढ़ो_cpuid_part() != ARM_CPU_PART_CORTEX_A9) अणु
		/*
		 * We communicate with the bootrom to active the cpus other
		 * than cpu0, after a blob of initialize code, they will
		 * stay at wfe state, once they are actived, they will check
		 * the mailbox:
		 * sram_base_addr + 4: 0xdeadbeaf
		 * sram_base_addr + 8: start address क्रम pc
		 * The cpu0 need to रुको the other cpus other than cpu0 entering
		 * the wfe state.The रुको समय is affected by many aspects.
		 * (e.g: cpu frequency, bootrom frequency, sram frequency, ...)
		 */
		mdelay(1); /* ensure the cpus other than cpu0 to startup */

		ग_लिखोl(__pa_symbol(secondary_startup), sram_base_addr + 8);
		ग_लिखोl(0xDEADBEAF, sram_base_addr + 4);
		dsb_sev();
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rockchip_smp_prepare_sram - populate necessary sram block
 * Starting cores execute the code residing at the start of the on-chip sram
 * after घातer-on. Thereक्रमe make sure, this sram region is reserved and
 * big enough. After this check, copy the trampoline code that directs the
 * core to the real startup code in ram पूर्णांकo the sram-region.
 * @node: mmio-sram device node
 */
अटल पूर्णांक __init rockchip_smp_prepare_sram(काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक trampoline_sz = &rockchip_secondary_trampoline_end -
					    &rockchip_secondary_trampoline;
	काष्ठा resource res;
	अचिन्हित पूर्णांक rsize;
	पूर्णांक ret;

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret < 0) अणु
		pr_err("%s: could not get address for node %pOF\n",
		       __func__, node);
		वापस ret;
	पूर्ण

	rsize = resource_size(&res);
	अगर (rsize < trampoline_sz) अणु
		pr_err("%s: reserved block with size 0x%x is too small for trampoline size 0x%x\n",
		       __func__, rsize, trampoline_sz);
		वापस -EINVAL;
	पूर्ण

	/* set the boot function क्रम the sram code */
	rockchip_boot_fn = __pa_symbol(secondary_startup);

	/* copy the trampoline to sram, that runs during startup of the core */
	स_नकल(sram_base_addr, &rockchip_secondary_trampoline, trampoline_sz);
	flush_cache_all();
	outer_clean_range(0, trampoline_sz);

	dsb_sev();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config rockchip_pmu_regmap_config = अणु
	.name = "rockchip-pmu",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल पूर्णांक __init rockchip_smp_prepare_pmu(व्योम)
अणु
	काष्ठा device_node *node;
	व्योम __iomem *pmu_base;

	/*
	 * This function is only called via smp_ops->smp_prepare_cpu().
	 * That only happens अगर a "/cpus" device tree node exists
	 * and has an "enable-method" property that selects the SMP
	 * operations defined herein.
	 */
	node = of_find_node_by_path("/cpus");

	pmu = syscon_regmap_lookup_by_phandle(node, "rockchip,pmu");
	of_node_put(node);
	अगर (!IS_ERR(pmu))
		वापस 0;

	pmu = syscon_regmap_lookup_by_compatible("rockchip,rk3066-pmu");
	अगर (!IS_ERR(pmu))
		वापस 0;

	/* fallback, create our own regmap क्रम the pmu area */
	pmu = शून्य;
	node = of_find_compatible_node(शून्य, शून्य, "rockchip,rk3066-pmu");
	अगर (!node) अणु
		pr_err("%s: could not find pmu dt node\n", __func__);
		वापस -ENODEV;
	पूर्ण

	pmu_base = of_iomap(node, 0);
	of_node_put(node);
	अगर (!pmu_base) अणु
		pr_err("%s: could not map pmu registers\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	pmu = regmap_init_mmio(शून्य, pmu_base, &rockchip_pmu_regmap_config);
	अगर (IS_ERR(pmu)) अणु
		पूर्णांक ret = PTR_ERR(pmu);

		iounmap(pmu_base);
		pmu = शून्य;
		pr_err("%s: regmap init failed\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init rockchip_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *node;
	अचिन्हित पूर्णांक i;

	node = of_find_compatible_node(शून्य, शून्य, "rockchip,rk3066-smp-sram");
	अगर (!node) अणु
		pr_err("%s: could not find sram dt node\n", __func__);
		वापस;
	पूर्ण

	sram_base_addr = of_iomap(node, 0);
	अगर (!sram_base_addr) अणु
		pr_err("%s: could not map sram registers\n", __func__);
		of_node_put(node);
		वापस;
	पूर्ण

	अगर (has_pmu && rockchip_smp_prepare_pmu()) अणु
		of_node_put(node);
		वापस;
	पूर्ण

	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9) अणु
		अगर (rockchip_smp_prepare_sram(node)) अणु
			of_node_put(node);
			वापस;
		पूर्ण

		/* enable the SCU घातer करोमुख्य */
		pmu_set_घातer_करोमुख्य(PMU_PWRDN_SCU, true);

		of_node_put(node);
		node = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");
		अगर (!node) अणु
			pr_err("%s: missing scu\n", __func__);
			वापस;
		पूर्ण

		scu_base_addr = of_iomap(node, 0);
		अगर (!scu_base_addr) अणु
			pr_err("%s: could not map scu registers\n", __func__);
			of_node_put(node);
			वापस;
		पूर्ण

		/*
		 * While the number of cpus is gathered from dt, also get the
		 * number of cores from the scu to verअगरy this value when
		 * booting the cores.
		 */
		ncores = scu_get_core_count(scu_base_addr);
		pr_err("%s: ncores %d\n", __func__, ncores);

		scu_enable(scu_base_addr);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक l2ctlr;

		यंत्र ("mrc p15, 1, %0, c9, c0, 2\n" : "=r" (l2ctlr));
		ncores = ((l2ctlr >> 24) & 0x3) + 1;
	पूर्ण
	of_node_put(node);

	/* Make sure that all cores except the first are really off */
	क्रम (i = 1; i < ncores; i++)
		pmu_set_घातer_करोमुख्य(0 + i, false);
पूर्ण

अटल व्योम __init rk3036_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	has_pmu = false;

	rockchip_smp_prepare_cpus(max_cpus);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक rockchip_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * We need a delay here to ensure that the dying CPU can finish
	 * executing v7_coherency_निकास() and reach the WFI/WFE state
	 * prior to having the घातer करोमुख्य disabled.
	 */
	mdelay(1);

	pmu_set_घातer_करोमुख्य(0 + cpu, false);
	वापस 1;
पूर्ण

अटल व्योम rockchip_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	v7_निकास_coherency_flush(louis);
	जबतक (1)
		cpu_करो_idle();
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations rk3036_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= rk3036_smp_prepare_cpus,
	.smp_boot_secondary	= rockchip_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_समाप्त		= rockchip_cpu_समाप्त,
	.cpu_die		= rockchip_cpu_die,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा smp_operations rockchip_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= rockchip_smp_prepare_cpus,
	.smp_boot_secondary	= rockchip_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_समाप्त		= rockchip_cpu_समाप्त,
	.cpu_die		= rockchip_cpu_die,
#पूर्ण_अगर
पूर्ण;

CPU_METHOD_OF_DECLARE(rk3036_smp, "rockchip,rk3036-smp", &rk3036_smp_ops);
CPU_METHOD_OF_DECLARE(rk3066_smp, "rockchip,rk3066-smp", &rockchip_smp_ops);
