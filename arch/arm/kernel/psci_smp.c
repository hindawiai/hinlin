<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2012 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/psci.h>

#समावेश <uapi/linux/psci.h>

#समावेश <यंत्र/psci.h>
#समावेश <यंत्र/smp_plat.h>

/*
 * psci_smp assumes that the following is true about PSCI:
 *
 * cpu_suspend   Suspend the execution on a CPU
 * @state        we करोn't currently describe affinity levels, so just pass 0.
 * @entry_poपूर्णांक  the first inकाष्ठाion to be executed on वापस
 * वापसs 0  success, < 0 on failure
 *
 * cpu_off       Power करोwn a CPU
 * @state        we करोn't currently describe affinity levels, so just pass 0.
 * no वापस on successful call
 *
 * cpu_on        Power up a CPU
 * @cpuid        cpuid of target CPU, as from MPIDR
 * @entry_poपूर्णांक  the first inकाष्ठाion to be executed on वापस
 * वापसs 0  success, < 0 on failure
 *
 * migrate       Migrate the context to a dअगरferent CPU
 * @cpuid        cpuid of target CPU, as from MPIDR
 * वापसs 0  success, < 0 on failure
 *
 */

बाह्य व्योम secondary_startup(व्योम);

अटल पूर्णांक psci_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	अगर (psci_ops.cpu_on)
		वापस psci_ops.cpu_on(cpu_logical_map(cpu),
					virt_to_idmap(&secondary_startup));
	वापस -ENODEV;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक psci_cpu_disable(अचिन्हित पूर्णांक cpu)
अणु
	/* Fail early अगर we करोn't have CPU_OFF support */
	अगर (!psci_ops.cpu_off)
		वापस -EOPNOTSUPP;

	/* Trusted OS will deny CPU_OFF */
	अगर (psci_tos_resident_on(cpu))
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल व्योम psci_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	u32 state = PSCI_POWER_STATE_TYPE_POWER_DOWN <<
		    PSCI_0_2_POWER_STATE_TYPE_SHIFT;

	अगर (psci_ops.cpu_off)
		psci_ops.cpu_off(state);

	/* We should never वापस */
	panic("psci: cpu %d failed to shutdown\n", cpu);
पूर्ण

अटल पूर्णांक psci_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err, i;

	अगर (!psci_ops.affinity_info)
		वापस 1;
	/*
	 * cpu_समाप्त could race with cpu_die and we can
	 * potentially end up declaring this cpu undead
	 * जबतक it is dying. So, try again a few बार.
	 */

	क्रम (i = 0; i < 10; i++) अणु
		err = psci_ops.affinity_info(cpu_logical_map(cpu), 0);
		अगर (err == PSCI_0_2_AFFINITY_LEVEL_OFF) अणु
			pr_info("CPU%d killed.\n", cpu);
			वापस 1;
		पूर्ण

		msleep(10);
		pr_info("Retrying again to check for CPU kill\n");
	पूर्ण

	pr_warn("CPU%d may not have shut down cleanly (AFFINITY_INFO reports %d)\n",
			cpu, err);
	/* Make platक्रमm_cpu_समाप्त() fail. */
	वापस 0;
पूर्ण

#पूर्ण_अगर

bool __init psci_smp_available(व्योम)
अणु
	/* is cpu_on available at least? */
	वापस (psci_ops.cpu_on != शून्य);
पूर्ण

स्थिर काष्ठा smp_operations psci_smp_ops __initस्थिर = अणु
	.smp_boot_secondary	= psci_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_disable		= psci_cpu_disable,
	.cpu_die		= psci_cpu_die,
	.cpu_समाप्त		= psci_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;
