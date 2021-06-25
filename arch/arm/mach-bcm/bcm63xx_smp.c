<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom BCM63138 DSL SoCs SMP support code
 *
 * Copyright (C) 2015, Broadcom Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/vfp.h>

#समावेश "bcm63xx_smp.h"

/* Size of mapped Cortex A9 SCU address space */
#घोषणा CORTEX_A9_SCU_SIZE	0x58

/*
 * Enable the Cortex A9 Snoop Control Unit
 *
 * By the समय this is called we alपढ़ोy know there are multiple
 * cores present.  We assume we're running on a Cortex A9 processor,
 * so any trouble getting the base address रेजिस्टर or getting the
 * SCU base is a problem.
 *
 * Return 0 अगर successful or an error code otherwise.
 */
अटल पूर्णांक __init scu_a9_enable(व्योम)
अणु
	अचिन्हित दीर्घ config_base;
	व्योम __iomem *scu_base;
	अचिन्हित पूर्णांक i, ncores;

	अगर (!scu_a9_has_base()) अणु
		pr_err("no configuration base address register!\n");
		वापस -ENXIO;
	पूर्ण

	/* Config base address रेजिस्टर value is zero क्रम uniprocessor */
	config_base = scu_a9_get_base();
	अगर (!config_base) अणु
		pr_err("hardware reports only one core\n");
		वापस -ENOENT;
	पूर्ण

	scu_base = ioremap((phys_addr_t)config_base, CORTEX_A9_SCU_SIZE);
	अगर (!scu_base) अणु
		pr_err("failed to remap config base (%lu/%u) for SCU\n",
			config_base, CORTEX_A9_SCU_SIZE);
		वापस -ENOMEM;
	पूर्ण

	scu_enable(scu_base);

	ncores = scu_base ? scu_get_core_count(scu_base) : 1;

	अगर (ncores > nr_cpu_ids) अणु
		pr_warn("SMP: %u cores greater than maximum (%u), clipping\n",
				ncores, nr_cpu_ids);
		ncores = nr_cpu_ids;
	पूर्ण

	/* The BCM63138 SoC has two Cortex-A9 CPUs, CPU0 features a complete
	 * and fully functional VFP unit that can be used, but CPU1 करोes not.
	 * Since we will not be able to trap kernel-mode NEON to क्रमce
	 * migration to CPU0, just करो not advertise VFP support at all.
	 *
	 * This will make vfp_init bail out and करो not attempt to use VFP at
	 * all, क्रम kernel-mode NEON, we करो not want to पूर्णांकroduce any
	 * conditionals in hot-paths, so we just restrict the प्रणाली to UP.
	 */
#अगर_घोषित CONFIG_VFP
	अगर (ncores > 1) अणु
		pr_warn("SMP: secondary CPUs lack VFP unit, disabling VFP\n");
		vfp_disable();

#अगर_घोषित CONFIG_KERNEL_MODE_NEON
		WARN(1, "SMP: kernel-mode NEON enabled, restricting to UP\n");
		ncores = 1;
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

	क्रम (i = 0; i < ncores; i++)
		set_cpu_possible(i, true);

	iounmap(scu_base);	/* That's the last we'll need of this */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm63138_bootlut_ids[] = अणु
	अणु .compatible = "brcm,bcm63138-bootlut", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

#घोषणा BOOTLUT_RESET_VECT	0x20

अटल पूर्णांक bcm63138_smp_boot_secondary(अचिन्हित पूर्णांक cpu,
				       काष्ठा task_काष्ठा *idle)
अणु
	व्योम __iomem *bootlut_base;
	काष्ठा device_node *dn;
	पूर्णांक ret = 0;
	u32 val;

	dn = of_find_matching_node(शून्य, bcm63138_bootlut_ids);
	अगर (!dn) अणु
		pr_err("SMP: unable to find bcm63138 boot LUT node\n");
		वापस -ENODEV;
	पूर्ण

	bootlut_base = of_iomap(dn, 0);
	of_node_put(dn);

	अगर (!bootlut_base) अणु
		pr_err("SMP: unable to remap boot LUT base register\n");
		वापस -ENOMEM;
	पूर्ण

	/* Locate the secondary CPU node */
	dn = of_get_cpu_node(cpu, शून्य);
	अगर (!dn) अणु
		pr_err("SMP: failed to locate secondary CPU%d node\n", cpu);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* Write the secondary init routine to the BootLUT reset vector */
	val = __pa_symbol(secondary_startup);
	ग_लिखोl_relaxed(val, bootlut_base + BOOTLUT_RESET_VECT);

	/* Power up the core, will jump straight to its reset vector when we
	 * वापस
	 */
	ret = bcm63xx_pmb_घातer_on_cpu(dn);
	of_node_put(dn);
	अगर (ret)
		जाओ out;
out:
	iounmap(bootlut_base);

	वापस ret;
पूर्ण

अटल व्योम __init bcm63138_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक ret;

	ret = scu_a9_enable();
	अगर (ret) अणु
		pr_warn("SMP: Cortex-A9 SCU setup failed\n");
		वापस;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा smp_operations bcm63138_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= bcm63138_smp_prepare_cpus,
	.smp_boot_secondary	= bcm63138_smp_boot_secondary,
पूर्ण;

CPU_METHOD_OF_DECLARE(bcm63138_smp, "brcm,bcm63138", &bcm63138_smp_ops);
