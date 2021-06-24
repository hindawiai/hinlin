<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM64 CPU idle arch support
 *
 * Copyright (C) 2014 ARM Ltd.
 * Author: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/psci.h>

#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/cpu_ops.h>

पूर्णांक arm_cpuidle_init(अचिन्हित पूर्णांक cpu)
अणु
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(cpu);
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (ops && ops->cpu_suspend && ops->cpu_init_idle)
		ret = ops->cpu_init_idle(cpu);

	वापस ret;
पूर्ण

/**
 * arm_cpuidle_suspend() - function to enter a low-घातer idle state
 * @index: argument to pass to CPU suspend operations
 *
 * Return: 0 on success, -EOPNOTSUPP अगर CPU suspend hook not initialized, CPU
 * operations back-end error code otherwise.
 */
पूर्णांक arm_cpuidle_suspend(पूर्णांक index)
अणु
	पूर्णांक cpu = smp_processor_id();
	स्थिर काष्ठा cpu_operations *ops = get_cpu_ops(cpu);

	वापस ops->cpu_suspend(index);
पूर्ण

#अगर_घोषित CONFIG_ACPI

#समावेश <acpi/processor.h>

#घोषणा ARM64_LPI_IS_RETENTION_STATE(arch_flags) (!(arch_flags))

अटल पूर्णांक psci_acpi_cpu_init_idle(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i, count;
	काष्ठा acpi_lpi_state *lpi;
	काष्ठा acpi_processor *pr = per_cpu(processors, cpu);

	/*
	 * If the PSCI cpu_suspend function hook has not been initialized
	 * idle states must not be enabled, so bail out
	 */
	अगर (!psci_ops.cpu_suspend)
		वापस -EOPNOTSUPP;

	अगर (unlikely(!pr || !pr->flags.has_lpi))
		वापस -EINVAL;

	count = pr->घातer.count - 1;
	अगर (count <= 0)
		वापस -ENODEV;

	क्रम (i = 0; i < count; i++) अणु
		u32 state;

		lpi = &pr->घातer.lpi_states[i + 1];
		/*
		 * Only bits[31:0] represent a PSCI घातer_state जबतक
		 * bits[63:32] must be 0x0 as per ARM ACPI FFH Specअगरication
		 */
		state = lpi->address;
		अगर (!psci_घातer_state_is_valid(state)) अणु
			pr_warn("Invalid PSCI power state %#x\n", state);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक acpi_processor_ffh_lpi_probe(अचिन्हित पूर्णांक cpu)
अणु
	वापस psci_acpi_cpu_init_idle(cpu);
पूर्ण

पूर्णांक acpi_processor_ffh_lpi_enter(काष्ठा acpi_lpi_state *lpi)
अणु
	u32 state = lpi->address;

	अगर (ARM64_LPI_IS_RETENTION_STATE(lpi->arch_flags))
		वापस CPU_PM_CPU_IDLE_ENTER_RETENTION_PARAM(psci_cpu_suspend_enter,
						lpi->index, state);
	अन्यथा
		वापस CPU_PM_CPU_IDLE_ENTER_PARAM(psci_cpu_suspend_enter,
					     lpi->index, state);
पूर्ण
#पूर्ण_अगर
