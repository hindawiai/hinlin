<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014-2015 Broadcom Corporation
 * Copyright 2014 Linaro Limited
 */

#समावेश <linux/cpumask.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/irq-bcm2836.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#समावेश "platsmp.h"

/* Size of mapped Cortex A9 SCU address space */
#घोषणा CORTEX_A9_SCU_SIZE	0x58

#घोषणा SECONDARY_TIMEOUT_NS	NSEC_PER_MSEC	/* 1 msec (in nanoseconds) */
#घोषणा BOOT_ADDR_CPUID_MASK	0x3

/* Name of device node property defining secondary boot रेजिस्टर location */
#घोषणा OF_SECONDARY_BOOT	"secondary-boot-reg"
#घोषणा MPIDR_CPUID_BITMASK	0x3

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

	iounmap(scu_base);	/* That's the last we'll need of this */

	वापस 0;
पूर्ण

अटल u32 secondary_boot_addr_क्रम(अचिन्हित पूर्णांक cpu)
अणु
	u32 secondary_boot_addr = 0;
	काष्ठा device_node *cpu_node = of_get_cpu_node(cpu, शून्य);

        अगर (!cpu_node) अणु
		pr_err("Failed to find device tree node for CPU%u\n", cpu);
		वापस 0;
	पूर्ण

	अगर (of_property_पढ़ो_u32(cpu_node,
				 OF_SECONDARY_BOOT,
				 &secondary_boot_addr))
		pr_err("required secondary boot register not specified for CPU%u\n",
			cpu);

	of_node_put(cpu_node);

	वापस secondary_boot_addr;
पूर्ण

अटल पूर्णांक nsp_ग_लिखो_lut(अचिन्हित पूर्णांक cpu)
अणु
	व्योम __iomem *sku_rom_lut;
	phys_addr_t secondary_startup_phy;
	स्थिर u32 secondary_boot_addr = secondary_boot_addr_क्रम(cpu);

	अगर (!secondary_boot_addr)
		वापस -EINVAL;

	sku_rom_lut = ioremap((phys_addr_t)secondary_boot_addr,
				      माप(phys_addr_t));
	अगर (!sku_rom_lut) अणु
		pr_warn("unable to ioremap SKU-ROM LUT register for cpu %u\n", cpu);
		वापस -ENOMEM;
	पूर्ण

	secondary_startup_phy = __pa_symbol(secondary_startup);
	BUG_ON(secondary_startup_phy > (phys_addr_t)U32_MAX);

	ग_लिखोl_relaxed(secondary_startup_phy, sku_rom_lut);

	/* Ensure the ग_लिखो is visible to the secondary core */
	smp_wmb();

	iounmap(sku_rom_lut);

	वापस 0;
पूर्ण

अटल व्योम __init bcm_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	स्थिर cpumask_t only_cpu_0 = अणु CPU_BITS_CPU0 पूर्ण;

	/* Enable the SCU on Cortex A9 based SoCs */
	अगर (scu_a9_enable()) अणु
		/* Update the CPU present map to reflect uniprocessor mode */
		pr_warn("failed to enable A9 SCU - disabling SMP\n");
		init_cpu_present(&only_cpu_0);
	पूर्ण
पूर्ण

/*
 * The ROM code has the secondary cores looping, रुकोing क्रम an event.
 * When an event occurs each core examines the bottom two bits of the
 * secondary boot रेजिस्टर.  When a core finds those bits contain its
 * own core id, it perक्रमms initialization, including computing its boot
 * address by clearing the boot रेजिस्टर value's bottom two bits.  The
 * core संकेतs that it is beginning its execution by writing its boot
 * address back to the secondary boot रेजिस्टर, and finally jumps to
 * that address.
 *
 * So to start a core executing we need to:
 * - Encode the (hardware) CPU id with the bottom bits of the secondary
 *   start address.
 * - Write that value पूर्णांकo the secondary boot रेजिस्टर.
 * - Generate an event to wake up the secondary CPU(s).
 * - Wait क्रम the secondary boot रेजिस्टर to be re-written, which
 *   indicates the secondary core has started.
 */
अटल पूर्णांक kona_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	व्योम __iomem *boot_reg;
	phys_addr_t boot_func;
	u64 start_घड़ी;
	u32 cpu_id;
	u32 boot_val;
	bool समयout = false;
	स्थिर u32 secondary_boot_addr = secondary_boot_addr_क्रम(cpu);

	cpu_id = cpu_logical_map(cpu);
	अगर (cpu_id & ~BOOT_ADDR_CPUID_MASK) अणु
		pr_err("bad cpu id (%u > %u)\n", cpu_id, BOOT_ADDR_CPUID_MASK);
		वापस -EINVAL;
	पूर्ण

	अगर (!secondary_boot_addr)
		वापस -EINVAL;

	boot_reg = ioremap((phys_addr_t)secondary_boot_addr,
				   माप(phys_addr_t));
	अगर (!boot_reg) अणु
		pr_err("unable to map boot register for cpu %u\n", cpu_id);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Secondary cores will start in secondary_startup(),
	 * defined in "arch/arm/kernel/head.S"
	 */
	boot_func = __pa_symbol(secondary_startup);
	BUG_ON(boot_func & BOOT_ADDR_CPUID_MASK);
	BUG_ON(boot_func > (phys_addr_t)U32_MAX);

	/* The core to start is encoded in the low bits */
	boot_val = (u32)boot_func | cpu_id;
	ग_लिखोl_relaxed(boot_val, boot_reg);

	sev();

	/* The low bits will be cleared once the core has started */
	start_घड़ी = local_घड़ी();
	जबतक (!समयout && पढ़ोl_relaxed(boot_reg) == boot_val)
		समयout = local_घड़ी() - start_घड़ी > SECONDARY_TIMEOUT_NS;

	iounmap(boot_reg);

	अगर (!समयout)
		वापस 0;

	pr_err("timeout waiting for cpu %u to start\n", cpu_id);

	वापस -ENXIO;
पूर्ण

/* Cluster Dormant Control command to bring CPU पूर्णांकo a running state */
#घोषणा CDC_CMD			6
#घोषणा CDC_CMD_OFFSET		0
#घोषणा CDC_CMD_REG(cpu)	(CDC_CMD_OFFSET + 4*(cpu))

/*
 * BCM23550 has a Cluster Dormant Control block that keeps the core in
 * idle state. A command needs to be sent to the block to bring the CPU
 * पूर्णांकo running state.
 */
अटल पूर्णांक bcm23550_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	व्योम __iomem *cdc_base;
	काष्ठा device_node *dn;
	अक्षर *name;
	पूर्णांक ret;

	/* Make sure a CDC node exists beक्रमe booting the
	 * secondary core.
	 */
	name = "brcm,bcm23550-cdc";
	dn = of_find_compatible_node(शून्य, शून्य, name);
	अगर (!dn) अणु
		pr_err("unable to find cdc node\n");
		वापस -ENODEV;
	पूर्ण

	cdc_base = of_iomap(dn, 0);
	of_node_put(dn);

	अगर (!cdc_base) अणु
		pr_err("unable to remap cdc base register\n");
		वापस -ENOMEM;
	पूर्ण

	/* Boot the secondary core */
	ret = kona_boot_secondary(cpu, idle);
	अगर (ret)
		जाओ out;

	/* Bring this CPU to RUN state so that nIRQ nFIQ
	 * संकेतs are unblocked.
	 */
	ग_लिखोl_relaxed(CDC_CMD, cdc_base + CDC_CMD_REG(cpu));

out:
	iounmap(cdc_base);

	वापस ret;
पूर्ण

अटल पूर्णांक nsp_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret;

	/*
	 * After wake up, secondary core branches to the startup
	 * address programmed at SKU ROM LUT location.
	 */
	ret = nsp_ग_लिखो_lut(cpu);
	अगर (ret) अणु
		pr_err("unable to write startup addr to SKU ROM LUT\n");
		जाओ out;
	पूर्ण

	/* Send a CPU wakeup पूर्णांकerrupt to the secondary core */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

out:
	वापस ret;
पूर्ण

अटल पूर्णांक bcm2836_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	व्योम __iomem *पूर्णांकc_base;
	काष्ठा device_node *dn;
	अक्षर *name;

	name = "brcm,bcm2836-l1-intc";
	dn = of_find_compatible_node(शून्य, शून्य, name);
	अगर (!dn) अणु
		pr_err("unable to find intc node\n");
		वापस -ENODEV;
	पूर्ण

	पूर्णांकc_base = of_iomap(dn, 0);
	of_node_put(dn);

	अगर (!पूर्णांकc_base) अणु
		pr_err("unable to remap intc base register\n");
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(virt_to_phys(secondary_startup),
	       पूर्णांकc_base + LOCAL_MAILBOX3_SET0 + 16 * cpu);

	dsb(sy);
	sev();

	iounmap(पूर्णांकc_base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा smp_operations kona_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= bcm_smp_prepare_cpus,
	.smp_boot_secondary	= kona_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(bcm_smp_bcm281xx, "brcm,bcm11351-cpu-method",
			&kona_smp_ops);

अटल स्थिर काष्ठा smp_operations bcm23550_smp_ops __initस्थिर = अणु
	.smp_boot_secondary	= bcm23550_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(bcm_smp_bcm23550, "brcm,bcm23550",
			&bcm23550_smp_ops);

अटल स्थिर काष्ठा smp_operations nsp_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= bcm_smp_prepare_cpus,
	.smp_boot_secondary	= nsp_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(bcm_smp_nsp, "brcm,bcm-nsp-smp", &nsp_smp_ops);

स्थिर काष्ठा smp_operations bcm2836_smp_ops __initस्थिर = अणु
	.smp_boot_secondary	= bcm2836_boot_secondary,
पूर्ण;
CPU_METHOD_OF_DECLARE(bcm_smp_bcm2836, "brcm,bcm2836-smp", &bcm2836_smp_ops);
