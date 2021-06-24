<शैली गुरु>
/*
 * Symmetric Multi Processing (SMP) support क्रम Armada XP
 *
 * Copyright (C) 2012 Marvell
 *
 * Lior Amsalem <alior@marvell.com>
 * Yehuda Yitschak <yehuday@marvell.com>
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * The Armada XP SoC has 4 ARMv7 PJ4B CPUs running in full HW coherency
 * This file implements the routines क्रम preparing the SMP infraकाष्ठाure
 * and waking up the secondary CPUs
 */

#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/mbus.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश "common.h"
#समावेश "armada-370-xp.h"
#समावेश "pmsu.h"
#समावेश "coherency.h"

#घोषणा ARMADA_XP_MAX_CPUS 4

#घोषणा AXP_BOOTROM_BASE 0xfff00000
#घोषणा AXP_BOOTROM_SIZE 0x100000

अटल काष्ठा clk *boot_cpu_clk;

अटल काष्ठा clk *get_cpu_clk(पूर्णांक cpu)
अणु
	काष्ठा clk *cpu_clk;
	काष्ठा device_node *np = of_get_cpu_node(cpu, शून्य);

	अगर (WARN(!np, "missing cpu node\n"))
		वापस शून्य;
	cpu_clk = of_clk_get(np, 0);
	अगर (WARN_ON(IS_ERR(cpu_clk)))
		वापस शून्य;
	वापस cpu_clk;
पूर्ण

अटल पूर्णांक armada_xp_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret, hw_cpu;

	pr_info("Booting CPU %d\n", cpu);

	hw_cpu = cpu_logical_map(cpu);
	mvebu_pmsu_set_cpu_boot_addr(hw_cpu, armada_xp_secondary_startup);

	/*
	 * This is needed to wake up CPUs in the offline state after
	 * using CPU hotplug.
	 */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	/*
	 * This is needed to take secondary CPUs out of reset on the
	 * initial boot.
	 */
	ret = mvebu_cpu_reset_deनिश्चित(hw_cpu);
	अगर (ret) अणु
		pr_warn("unable to boot CPU: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * When a CPU is brought back online, either through CPU hotplug, or
 * because of the boot of a kexec'ed kernel, the PMSU configuration
 * क्रम this CPU might be in the deep idle state, preventing this CPU
 * from receiving पूर्णांकerrupts. Here, we thereक्रमe take out the current
 * CPU from this state, which was entered by armada_xp_cpu_die()
 * below.
 */
अटल व्योम armada_xp_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	mvebu_v7_pmsu_idle_निकास();
पूर्ण

अटल व्योम __init armada_xp_smp_init_cpus(व्योम)
अणु
	अचिन्हित पूर्णांक ncores = num_possible_cpus();

	अगर (ncores == 0 || ncores > ARMADA_XP_MAX_CPUS)
		panic("Invalid number of CPUs in DT\n");
पूर्ण

अटल पूर्णांक armada_xp_sync_secondary_clk(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा clk *cpu_clk = get_cpu_clk(cpu);

	अगर (!cpu_clk || !boot_cpu_clk)
		वापस 0;

	clk_prepare_enable(cpu_clk);
	clk_set_rate(cpu_clk, clk_get_rate(boot_cpu_clk));

	वापस 0;
पूर्ण

अटल व्योम __init armada_xp_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *node;
	काष्ठा resource res;
	पूर्णांक err;

	flush_cache_all();
	set_cpu_coherent();

	boot_cpu_clk = get_cpu_clk(smp_processor_id());
	अगर (boot_cpu_clk) अणु
		clk_prepare_enable(boot_cpu_clk);
		cpuhp_setup_state_nocalls(CPUHP_AP_ARM_MVEBU_SYNC_CLOCKS,
					  "arm/mvebu/sync_clocks:online",
					  armada_xp_sync_secondary_clk, शून्य);
	पूर्ण

	/*
	 * In order to boot the secondary CPUs we need to ensure
	 * the bootROM is mapped at the correct address.
	 */
	node = of_find_compatible_node(शून्य, शून्य, "marvell,bootrom");
	अगर (!node)
		panic("Cannot find 'marvell,bootrom' compatible node");

	err = of_address_to_resource(node, 0, &res);
	of_node_put(node);
	अगर (err < 0)
		panic("Cannot get 'bootrom' node address");

	अगर (res.start != AXP_BOOTROM_BASE ||
	    resource_size(&res) != AXP_BOOTROM_SIZE)
		panic("The address for the BootROM is incorrect");
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम armada_xp_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * CPU hotplug is implemented by putting offline CPUs पूर्णांकo the
	 * deep idle sleep state.
	 */
	armada_370_xp_pmsu_idle_enter(true);
पूर्ण

/*
 * We need a dummy function, so that platक्रमm_can_cpu_hotplug() knows
 * we support CPU hotplug. However, the function करोes not need to करो
 * anything, because CPUs going offline can enter the deep idle state
 * by themselves, without any help from a still alive CPU.
 */
अटल पूर्णांक armada_xp_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा smp_operations armada_xp_smp_ops __initस्थिर = अणु
	.smp_init_cpus		= armada_xp_smp_init_cpus,
	.smp_prepare_cpus	= armada_xp_smp_prepare_cpus,
	.smp_boot_secondary	= armada_xp_boot_secondary,
	.smp_secondary_init     = armada_xp_secondary_init,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= armada_xp_cpu_die,
	.cpu_समाप्त               = armada_xp_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

CPU_METHOD_OF_DECLARE(armada_xp_smp, "marvell,armada-xp-smp",
		      &armada_xp_smp_ops);

#घोषणा MV98DX3236_CPU_RESUME_CTRL_REG 0x08
#घोषणा MV98DX3236_CPU_RESUME_ADDR_REG 0x04

अटल स्थिर काष्ठा of_device_id of_mv98dx3236_resume_table[] = अणु
	अणु
		.compatible = "marvell,98dx3336-resume-ctrl",
	पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

अटल पूर्णांक mv98dx3236_resume_set_cpu_boot_addr(पूर्णांक hw_cpu, व्योम *boot_addr)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *base;
	WARN_ON(hw_cpu != 1);

	np = of_find_matching_node(शून्य, of_mv98dx3236_resume_table);
	अगर (!np)
		वापस -ENODEV;

	base = of_io_request_and_map(np, 0, of_node_full_name(np));
	of_node_put(np);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	ग_लिखोl(0, base + MV98DX3236_CPU_RESUME_CTRL_REG);
	ग_लिखोl(__pa_symbol(boot_addr), base + MV98DX3236_CPU_RESUME_ADDR_REG);

	iounmap(base);

	वापस 0;
पूर्ण

अटल पूर्णांक mv98dx3236_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret, hw_cpu;

	hw_cpu = cpu_logical_map(cpu);
	mv98dx3236_resume_set_cpu_boot_addr(hw_cpu,
					    armada_xp_secondary_startup);

	/*
	 * This is needed to wake up CPUs in the offline state after
	 * using CPU hotplug.
	 */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	/*
	 * This is needed to take secondary CPUs out of reset on the
	 * initial boot.
	 */
	ret = mvebu_cpu_reset_deनिश्चित(hw_cpu);
	अगर (ret) अणु
		pr_warn("unable to boot CPU: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा smp_operations mv98dx3236_smp_ops __initस्थिर = अणु
	.smp_init_cpus		= armada_xp_smp_init_cpus,
	.smp_prepare_cpus	= armada_xp_smp_prepare_cpus,
	.smp_boot_secondary	= mv98dx3236_boot_secondary,
	.smp_secondary_init     = armada_xp_secondary_init,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= armada_xp_cpu_die,
	.cpu_समाप्त               = armada_xp_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

CPU_METHOD_OF_DECLARE(mv98dx3236_smp, "marvell,98dx3236-smp",
		      &mv98dx3236_smp_ops);
