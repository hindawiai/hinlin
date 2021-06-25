<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-vexpress/mcpm_platsmp.c
 *
 * Created by:  Nicolas Pitre, November 2012
 * Copyright:   (C) 2012-2013  Linaro Limited
 *
 * Code to handle secondary CPU bringup and hotplug क्रम the cluster घातer API.
 */

#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/smp_plat.h>

अटल व्योम cpu_to_pcpu(अचिन्हित पूर्णांक cpu,
			अचिन्हित पूर्णांक *pcpu, अचिन्हित पूर्णांक *pcluster)
अणु
	अचिन्हित पूर्णांक mpidr;

	mpidr = cpu_logical_map(cpu);
	*pcpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	*pcluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
पूर्ण

अटल पूर्णांक mcpm_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अचिन्हित पूर्णांक pcpu, pcluster, ret;
	बाह्य व्योम secondary_startup(व्योम);

	cpu_to_pcpu(cpu, &pcpu, &pcluster);

	pr_debug("%s: logical CPU %d is physical CPU %d cluster %d\n",
		 __func__, cpu, pcpu, pcluster);

	mcpm_set_entry_vector(pcpu, pcluster, शून्य);
	ret = mcpm_cpu_घातer_up(pcpu, pcluster);
	अगर (ret)
		वापस ret;
	mcpm_set_entry_vector(pcpu, pcluster, secondary_startup);
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));
	dsb_sev();
	वापस 0;
पूर्ण

अटल व्योम mcpm_secondary_init(अचिन्हित पूर्णांक cpu)
अणु
	mcpm_cpu_घातered_up();
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल पूर्णांक mcpm_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक pcpu, pcluster;

	cpu_to_pcpu(cpu, &pcpu, &pcluster);

	वापस !mcpm_रुको_क्रम_cpu_घातerकरोwn(pcpu, pcluster);
पूर्ण

अटल bool mcpm_cpu_can_disable(अचिन्हित पूर्णांक cpu)
अणु
	/* We assume all CPUs may be shut करोwn. */
	वापस true;
पूर्ण

अटल व्योम mcpm_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक mpidr, pcpu, pcluster;
	mpidr = पढ़ो_cpuid_mpidr();
	pcpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	pcluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	mcpm_set_entry_vector(pcpu, pcluster, शून्य);
	mcpm_cpu_घातer_करोwn();
पूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा smp_operations mcpm_smp_ops __initस्थिर = अणु
	.smp_boot_secondary	= mcpm_boot_secondary,
	.smp_secondary_init	= mcpm_secondary_init,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_समाप्त		= mcpm_cpu_समाप्त,
	.cpu_can_disable	= mcpm_cpu_can_disable,
	.cpu_die		= mcpm_cpu_die,
#पूर्ण_अगर
पूर्ण;

व्योम __init mcpm_smp_set_ops(व्योम)
अणु
	smp_set_ops(&mcpm_smp_ops);
पूर्ण
