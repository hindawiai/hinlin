<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPU kernel entry/निकास control
 *
 * Copyright (C) 2013 ARM Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cache.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/smp_plat.h>

बाह्य स्थिर काष्ठा cpu_operations smp_spin_table_ops;
#अगर_घोषित CONFIG_ARM64_ACPI_PARKING_PROTOCOL
बाह्य स्थिर काष्ठा cpu_operations acpi_parking_protocol_ops;
#पूर्ण_अगर
बाह्य स्थिर काष्ठा cpu_operations cpu_psci_ops;

अटल स्थिर काष्ठा cpu_operations *cpu_ops[NR_CPUS] __ro_after_init;

अटल स्थिर काष्ठा cpu_operations *स्थिर dt_supported_cpu_ops[] __initस्थिर = अणु
	&smp_spin_table_ops,
	&cpu_psci_ops,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा cpu_operations *स्थिर acpi_supported_cpu_ops[] __initस्थिर = अणु
#अगर_घोषित CONFIG_ARM64_ACPI_PARKING_PROTOCOL
	&acpi_parking_protocol_ops,
#पूर्ण_अगर
	&cpu_psci_ops,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा cpu_operations * __init cpu_get_ops(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा cpu_operations *स्थिर *ops;

	ops = acpi_disabled ? dt_supported_cpu_ops : acpi_supported_cpu_ops;

	जबतक (*ops) अणु
		अगर (!म_भेद(name, (*ops)->name))
			वापस *ops;

		ops++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *__init cpu_पढ़ो_enable_method(पूर्णांक cpu)
अणु
	स्थिर अक्षर *enable_method;

	अगर (acpi_disabled) अणु
		काष्ठा device_node *dn = of_get_cpu_node(cpu, शून्य);

		अगर (!dn) अणु
			अगर (!cpu)
				pr_err("Failed to find device node for boot cpu\n");
			वापस शून्य;
		पूर्ण

		enable_method = of_get_property(dn, "enable-method", शून्य);
		अगर (!enable_method) अणु
			/*
			 * The boot CPU may not have an enable method (e.g.
			 * when spin-table is used क्रम secondaries).
			 * Don't warn spuriously.
			 */
			अगर (cpu != 0)
				pr_err("%pOF: missing enable-method property\n",
					dn);
		पूर्ण
		of_node_put(dn);
	पूर्ण अन्यथा अणु
		enable_method = acpi_get_enable_method(cpu);
		अगर (!enable_method) अणु
			/*
			 * In ACPI प्रणालीs the boot CPU करोes not require
			 * checking the enable method since क्रम some
			 * boot protocol (ie parking protocol) it need not
			 * be initialized. Don't warn spuriously.
			 */
			अगर (cpu != 0)
				pr_err("Unsupported ACPI enable-method\n");
		पूर्ण
	पूर्ण

	वापस enable_method;
पूर्ण
/*
 * Read a cpu's enable method and record it in cpu_ops.
 */
पूर्णांक __init init_cpu_ops(पूर्णांक cpu)
अणु
	स्थिर अक्षर *enable_method = cpu_पढ़ो_enable_method(cpu);

	अगर (!enable_method)
		वापस -ENODEV;

	cpu_ops[cpu] = cpu_get_ops(enable_method);
	अगर (!cpu_ops[cpu]) अणु
		pr_warn("Unsupported enable-method: %s\n", enable_method);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा cpu_operations *get_cpu_ops(पूर्णांक cpu)
अणु
	वापस cpu_ops[cpu];
पूर्ण
