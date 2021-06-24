<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file contains Xilinx specअगरic SMP code, used to start up
 * the second processor.
 *
 * Copyright (C) 2011-2013 Xilinx
 *
 * based on linux/arch/arm/mach-realview/platsmp.c
 *
 * Copyright (C) 2002 ARM Ltd.
 */

#समावेश <linux/export.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश "common.h"

/*
 * Store number of cores in the प्रणाली
 * Because of scu_get_core_count() must be in __init section and can't
 * be called from zynq_cpun_start() because it is not in __init section.
 */
अटल पूर्णांक ncores;

पूर्णांक zynq_cpun_start(u32 address, पूर्णांक cpu)
अणु
	u32 trampoline_code_size = &zynq_secondary_trampoline_end -
						&zynq_secondary_trampoline;
	u32 phy_cpuid = cpu_logical_map(cpu);

	/* MS: Expectation that SLCR are directly map and accessible */
	/* Not possible to jump to non aligned address */
	अगर (!(address & 3) && (!address || (address >= trampoline_code_size))) अणु
		/* Store poपूर्णांकer to ioremap area which poपूर्णांकs to address 0x0 */
		अटल u8 __iomem *zero;
		u32 trampoline_size = &zynq_secondary_trampoline_jump -
						&zynq_secondary_trampoline;

		zynq_slcr_cpu_stop(phy_cpuid);
		अगर (address) अणु
			अगर (__pa(PAGE_OFFSET)) अणु
				zero = ioremap(0, trampoline_code_size);
				अगर (!zero) अणु
					pr_warn("BOOTUP jump vectors not accessible\n");
					वापस -1;
				पूर्ण
			पूर्ण अन्यथा अणु
				zero = (__क्रमce u8 __iomem *)PAGE_OFFSET;
			पूर्ण

			/*
			* This is elegant way how to jump to any address
			* 0x0: Load address at 0x8 to r0
			* 0x4: Jump by mov inकाष्ठाion
			* 0x8: Jumping address
			*/
			स_नकल_toio(zero, &zynq_secondary_trampoline,
							trampoline_size);
			ग_लिखोl(address, zero + trampoline_size);

			flush_cache_all();
			outer_flush_range(0, trampoline_code_size);
			smp_wmb();

			अगर (__pa(PAGE_OFFSET))
				iounmap(zero);
		पूर्ण
		zynq_slcr_cpu_start(phy_cpuid);

		वापस 0;
	पूर्ण

	pr_warn("Can't start CPU%d: Wrong starting address %x\n", cpu, address);

	वापस -1;
पूर्ण
EXPORT_SYMBOL(zynq_cpun_start);

अटल पूर्णांक zynq_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	वापस zynq_cpun_start(__pa_symbol(secondary_startup_arm), cpu);
पूर्ण

/*
 * Initialise the CPU possible map early - this describes the CPUs
 * which may be present or become present in the प्रणाली.
 */
अटल व्योम __init zynq_smp_init_cpus(व्योम)
अणु
	पूर्णांक i;

	ncores = scu_get_core_count(zynq_scu_base);

	क्रम (i = 0; i < ncores && i < CONFIG_NR_CPUS; i++)
		set_cpu_possible(i, true);
पूर्ण

अटल व्योम __init zynq_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	scu_enable(zynq_scu_base);
पूर्ण

/**
 * zynq_secondary_init - Initialize secondary CPU cores
 * @cpu:	CPU that is initialized
 *
 * This function is in the hotplug path. Don't move it पूर्णांकo the
 * init section!!
 */
अटल व्योम zynq_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	zynq_core_pm_init();
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक zynq_cpu_समाप्त(अचिन्हित cpu)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(50);

	जबतक (zynq_slcr_cpu_state_पढ़ो(cpu))
		अगर (समय_after(jअगरfies, समयout))
			वापस 0;

	zynq_slcr_cpu_stop(cpu);
	वापस 1;
पूर्ण

/**
 * zynq_cpu_die - Let a CPU core die
 * @cpu:	Dying CPU
 *
 * Platक्रमm-specअगरic code to shutकरोwn a CPU.
 * Called with IRQs disabled on the dying CPU.
 */
अटल व्योम zynq_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	zynq_slcr_cpu_state_ग_लिखो(cpu, true);

	/*
	 * there is no घातer-control hardware on this platक्रमm, so all
	 * we can करो is put the core पूर्णांकo WFI; this is safe as the calling
	 * code will have alपढ़ोy disabled पूर्णांकerrupts
	 */
	क्रम (;;)
		cpu_करो_idle();
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा smp_operations zynq_smp_ops __initस्थिर = अणु
	.smp_init_cpus		= zynq_smp_init_cpus,
	.smp_prepare_cpus	= zynq_smp_prepare_cpus,
	.smp_boot_secondary	= zynq_boot_secondary,
	.smp_secondary_init	= zynq_secondary_init,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_die		= zynq_cpu_die,
	.cpu_समाप्त		= zynq_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;
