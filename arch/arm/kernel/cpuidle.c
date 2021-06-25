<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Linaro Ltd.
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/cpuidle.h>

बाह्य काष्ठा of_cpuidle_method __cpuidle_method_of_table[];

अटल स्थिर काष्ठा of_cpuidle_method __cpuidle_method_of_table_sentinel
	__used __section("__cpuidle_method_of_table_end");

अटल काष्ठा cpuidle_ops cpuidle_ops[NR_CPUS] __ro_after_init;

/**
 * arm_cpuidle_simple_enter() - a wrapper to cpu_करो_idle()
 * @dev: not used
 * @drv: not used
 * @index: not used
 *
 * A trivial wrapper to allow the cpu_करो_idle function to be asचिन्हित as a
 * cpuidle callback by matching the function signature.
 *
 * Returns the index passed as parameter
 */
पूर्णांक arm_cpuidle_simple_enter(काष्ठा cpuidle_device *dev,
		काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	cpu_करो_idle();

	वापस index;
पूर्ण

/**
 * arm_cpuidle_suspend() - function to enter low घातer idle states
 * @index: an पूर्णांकeger used as an identअगरier क्रम the low level PM callbacks
 *
 * This function calls the underlying arch specअगरic low level PM code as
 * रेजिस्टरed at the init समय.
 *
 * Returns the result of the suspend callback.
 */
पूर्णांक arm_cpuidle_suspend(पूर्णांक index)
अणु
	पूर्णांक cpu = smp_processor_id();

	वापस cpuidle_ops[cpu].suspend(index);
पूर्ण

/**
 * arm_cpuidle_get_ops() - find a रेजिस्टरed cpuidle_ops by name
 * @method: the method name
 *
 * Search in the __cpuidle_method_of_table array the cpuidle ops matching the
 * method name.
 *
 * Returns a काष्ठा cpuidle_ops poपूर्णांकer, शून्य अगर not found.
 */
अटल स्थिर काष्ठा cpuidle_ops *__init arm_cpuidle_get_ops(स्थिर अक्षर *method)
अणु
	काष्ठा of_cpuidle_method *m = __cpuidle_method_of_table;

	क्रम (; m->method; m++)
		अगर (!म_भेद(m->method, method))
			वापस m->ops;

	वापस शून्य;
पूर्ण

/**
 * arm_cpuidle_पढ़ो_ops() - Initialize the cpuidle ops with the device tree
 * @dn: a poपूर्णांकer to a काष्ठा device node corresponding to a cpu node
 * @cpu: the cpu identअगरier
 *
 * Get the method name defined in the 'enable-method' property, retrieve the
 * associated cpuidle_ops and करो a काष्ठा copy. This copy is needed because all
 * cpuidle_ops are tagged __initस्थिर and will be unloaded after the init
 * process.
 *
 * Return 0 on sucess, -ENOENT अगर no 'enable-method' is defined, -EOPNOTSUPP अगर
 * no cpuidle_ops is रेजिस्टरed क्रम the 'enable-method', or अगर either init or
 * suspend callback isn't defined.
 */
अटल पूर्णांक __init arm_cpuidle_पढ़ो_ops(काष्ठा device_node *dn, पूर्णांक cpu)
अणु
	स्थिर अक्षर *enable_method;
	स्थिर काष्ठा cpuidle_ops *ops;

	enable_method = of_get_property(dn, "enable-method", शून्य);
	अगर (!enable_method)
		वापस -ENOENT;

	ops = arm_cpuidle_get_ops(enable_method);
	अगर (!ops) अणु
		pr_warn("%pOF: unsupported enable-method property: %s\n",
			dn, enable_method);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!ops->init || !ops->suspend) अणु
		pr_warn("cpuidle_ops '%s': no init or suspend callback\n",
			enable_method);
		वापस -EOPNOTSUPP;
	पूर्ण

	cpuidle_ops[cpu] = *ops; /* काष्ठाure copy */

	pr_notice("cpuidle: enable-method property '%s'"
		  " found operations\n", enable_method);

	वापस 0;
पूर्ण

/**
 * arm_cpuidle_init() - Initialize cpuidle_ops क्रम a specअगरic cpu
 * @cpu: the cpu to be initialized
 *
 * Initialize the cpuidle ops with the device क्रम the cpu and then call
 * the cpu's idle initialization callback. This may fail अगर the underlying HW
 * is not operational.
 *
 * Returns:
 *  0 on success,
 *  -ENODEV अगर it fails to find the cpu node in the device tree,
 *  -EOPNOTSUPP अगर it करोes not find a रेजिस्टरed and valid cpuidle_ops क्रम
 *  this cpu,
 *  -ENOENT अगर it fails to find an 'enable-method' property,
 *  -ENXIO अगर the HW reports a failure or a misconfiguration,
 *  -ENOMEM अगर the HW report an memory allocation failure 
 */
पूर्णांक __init arm_cpuidle_init(पूर्णांक cpu)
अणु
	काष्ठा device_node *cpu_node = of_cpu_device_node_get(cpu);
	पूर्णांक ret;

	अगर (!cpu_node)
		वापस -ENODEV;

	ret = arm_cpuidle_पढ़ो_ops(cpu_node, cpu);
	अगर (!ret)
		ret = cpuidle_ops[cpu].init(cpu_node, cpu);

	of_node_put(cpu_node);

	वापस ret;
पूर्ण
