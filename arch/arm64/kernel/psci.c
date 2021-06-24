<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2013 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#घोषणा pr_fmt(fmt) "psci: " fmt

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/smp.h>
#समावेश <linux/delay.h>
#समावेश <linux/psci.h>
#समावेश <linux/mm.h>

#समावेश <uapi/linux/psci.h>

#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/smp_plat.h>

अटल पूर्णांक __init cpu_psci_cpu_init(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __init cpu_psci_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!psci_ops.cpu_on) अणु
		pr_err("no cpu_on method, not booting CPU%d\n", cpu);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpu_psci_cpu_boot(अचिन्हित पूर्णांक cpu)
अणु
	phys_addr_t pa_secondary_entry = __pa_symbol(function_nocfi(secondary_entry));
	पूर्णांक err = psci_ops.cpu_on(cpu_logical_map(cpu), pa_secondary_entry);
	अगर (err)
		pr_err("failed to boot CPU%d (%d)\n", cpu, err);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल bool cpu_psci_cpu_can_disable(अचिन्हित पूर्णांक cpu)
अणु
	वापस !psci_tos_resident_on(cpu);
पूर्ण

अटल पूर्णांक cpu_psci_cpu_disable(अचिन्हित पूर्णांक cpu)
अणु
	/* Fail early अगर we करोn't have CPU_OFF support */
	अगर (!psci_ops.cpu_off)
		वापस -EOPNOTSUPP;

	/* Trusted OS will deny CPU_OFF */
	अगर (psci_tos_resident_on(cpu))
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल व्योम cpu_psci_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * There are no known implementations of PSCI actually using the
	 * घातer state field, pass a sensible शेष क्रम now.
	 */
	u32 state = PSCI_POWER_STATE_TYPE_POWER_DOWN <<
		    PSCI_0_2_POWER_STATE_TYPE_SHIFT;

	psci_ops.cpu_off(state);
पूर्ण

अटल पूर्णांक cpu_psci_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ start, end;

	अगर (!psci_ops.affinity_info)
		वापस 0;
	/*
	 * cpu_समाप्त could race with cpu_die and we can
	 * potentially end up declaring this cpu undead
	 * जबतक it is dying. So, try again a few बार.
	 */

	start = jअगरfies;
	end = start + msecs_to_jअगरfies(100);
	करो अणु
		err = psci_ops.affinity_info(cpu_logical_map(cpu), 0);
		अगर (err == PSCI_0_2_AFFINITY_LEVEL_OFF) अणु
			pr_info("CPU%d killed (polled %d ms)\n", cpu,
				jअगरfies_to_msecs(jअगरfies - start));
			वापस 0;
		पूर्ण

		usleep_range(100, 1000);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	pr_warn("CPU%d may not have shut down cleanly (AFFINITY_INFO reports %d)\n",
			cpu, err);
	वापस -ETIMEDOUT;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा cpu_operations cpu_psci_ops = अणु
	.name		= "psci",
	.cpu_init	= cpu_psci_cpu_init,
	.cpu_prepare	= cpu_psci_cpu_prepare,
	.cpu_boot	= cpu_psci_cpu_boot,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_can_disable = cpu_psci_cpu_can_disable,
	.cpu_disable	= cpu_psci_cpu_disable,
	.cpu_die	= cpu_psci_cpu_die,
	.cpu_समाप्त	= cpu_psci_cpu_समाप्त,
#पूर्ण_अगर
पूर्ण;

