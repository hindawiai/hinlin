<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMP support क्रम SoCs with SCU covered by mach-shmobile
 *
 * Copyright (C) 2013  Magnus Damm
 */
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/smp.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश "common.h"


अटल phys_addr_t shmobile_scu_base_phys;
अटल व्योम __iomem *shmobile_scu_base;

अटल पूर्णांक shmobile_scu_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	/* For this particular CPU रेजिस्टर SCU SMP boot vector */
	shmobile_smp_hook(cpu, __pa_symbol(shmobile_boot_scu),
			  shmobile_scu_base_phys);
	वापस 0;
पूर्ण

व्योम __init shmobile_smp_scu_prepare_cpus(phys_addr_t scu_base_phys,
					  अचिन्हित पूर्णांक max_cpus)
अणु
	/* install boot code shared by all CPUs */
	shmobile_boot_fn = __pa_symbol(shmobile_smp_boot);

	/* enable SCU and cache coherency on booting CPU */
	shmobile_scu_base_phys = scu_base_phys;
	shmobile_scu_base = ioremap(scu_base_phys, PAGE_SIZE);
	scu_enable(shmobile_scu_base);
	scu_घातer_mode(shmobile_scu_base, SCU_PM_NORMAL);

	/* Use CPU notअगरier क्रम reset vector control */
	cpuhp_setup_state_nocalls(CPUHP_ARM_SHMOBILE_SCU_PREPARE,
				  "arm/shmobile-scu:prepare",
				  shmobile_scu_cpu_prepare, शून्य);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम shmobile_smp_scu_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	/* For this particular CPU deरेजिस्टर boot vector */
	shmobile_smp_hook(cpu, 0, 0);

	dsb();
	flush_cache_all();

	/* disable cache coherency */
	scu_घातer_mode(shmobile_scu_base, SCU_PM_POWEROFF);

	/* jump to shared mach-shmobile sleep / reset code */
	shmobile_smp_sleep();
पूर्ण

अटल पूर्णांक shmobile_smp_scu_psr_core_disabled(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ mask = SCU_PM_POWEROFF << (cpu * 8);

	अगर ((पढ़ोl(shmobile_scu_base + 8) & mask) == mask)
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक shmobile_smp_scu_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक k;

	/* this function is running on another CPU than the offline target,
	 * here we need रुको क्रम shutकरोwn code in platक्रमm_cpu_die() to
	 * finish beक्रमe asking SoC-specअगरic code to घातer off the CPU core.
	 */
	क्रम (k = 0; k < 1000; k++) अणु
		अगर (shmobile_smp_scu_psr_core_disabled(cpu))
			वापस 1;

		mdelay(1);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर
