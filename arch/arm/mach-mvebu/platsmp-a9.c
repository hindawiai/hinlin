<शैली गुरु>
/*
 * Symmetric Multi Processing (SMP) support क्रम Marvell EBU Cortex-A9
 * based SOCs (Armada 375/38x).
 *
 * Copyright (C) 2014 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/smp.h>
#समावेश <linux/mbus.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश "common.h"
#समावेश "pmsu.h"

बाह्य व्योम mvebu_cortex_a9_secondary_startup(व्योम);

अटल पूर्णांक mvebu_cortex_a9_boot_secondary(अचिन्हित पूर्णांक cpu,
						    काष्ठा task_काष्ठा *idle)
अणु
	पूर्णांक ret, hw_cpu;

	pr_info("Booting CPU %d\n", cpu);

	/*
	 * Write the address of secondary startup पूर्णांकo the प्रणाली-wide
	 * flags रेजिस्टर. The boot monitor रुकोs until it receives a
	 * soft पूर्णांकerrupt, and then the secondary CPU branches to this
	 * address.
	 */
	hw_cpu = cpu_logical_map(cpu);
	अगर (of_machine_is_compatible("marvell,armada375"))
		mvebu_प्रणाली_controller_set_cpu_boot_addr(mvebu_cortex_a9_secondary_startup);
	अन्यथा
		mvebu_pmsu_set_cpu_boot_addr(hw_cpu, mvebu_cortex_a9_secondary_startup);
	smp_wmb();

	/*
	 * Doing this beक्रमe deनिश्चितing the CPUs is needed to wake up CPUs
	 * in the offline state after using CPU hotplug.
	 */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	ret = mvebu_cpu_reset_deनिश्चित(hw_cpu);
	अगर (ret) अणु
		pr_err("Could not start the secondary CPU: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
/*
 * When a CPU is brought back online, either through CPU hotplug, or
 * because of the boot of a kexec'ed kernel, the PMSU configuration
 * क्रम this CPU might be in the deep idle state, preventing this CPU
 * from receiving पूर्णांकerrupts. Here, we thereक्रमe take out the current
 * CPU from this state, which was entered by armada_38x_cpu_die()
 * below.
 */
अटल व्योम armada_38x_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	mvebu_v7_pmsu_idle_निकास();
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम armada_38x_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * CPU hotplug is implemented by putting offline CPUs पूर्णांकo the
	 * deep idle sleep state.
	 */
	armada_38x_करो_cpu_suspend(true);
पूर्ण

/*
 * We need a dummy function, so that platक्रमm_can_cpu_hotplug() knows
 * we support CPU hotplug. However, the function करोes not need to करो
 * anything, because CPUs going offline can enter the deep idle state
 * by themselves, without any help from a still alive CPU.
 */
अटल पूर्णांक armada_38x_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations mvebu_cortex_a9_smp_ops __initस्थिर = अणु
	.smp_boot_secondary	= mvebu_cortex_a9_boot_secondary,
पूर्ण;

अटल स्थिर काष्ठा smp_operations armada_38x_smp_ops __initस्थिर = अणु
	.smp_boot_secondary	= mvebu_cortex_a9_boot_secondary,
	.smp_secondary_init     = armada_38x_secondary_init,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= armada_38x_cpu_die,
	.cpu_समाप्त               = armada_38x_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

CPU_METHOD_OF_DECLARE(mvebu_armada_375_smp, "marvell,armada-375-smp",
		      &mvebu_cortex_a9_smp_ops);
CPU_METHOD_OF_DECLARE(mvebu_armada_380_smp, "marvell,armada-380-smp",
		      &armada_38x_smp_ops);
CPU_METHOD_OF_DECLARE(mvebu_armada_390_smp, "marvell,armada-390-smp",
		      &armada_38x_smp_ops);
