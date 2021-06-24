<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2019 Linaro Limited.
 *
 *  Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 *
 */
#घोषणा pr_fmt(fmt) "cpuidle cooling: " fmt

#समावेश <linux/cpu_cooling.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/idle_inject.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

/**
 * काष्ठा cpuidle_cooling_device - data क्रम the idle cooling device
 * @ii_dev: an atomic to keep track of the last task निकासing the idle cycle
 * @state: a normalized पूर्णांकeger giving the state of the cooling device
 */
काष्ठा cpuidle_cooling_device अणु
	काष्ठा idle_inject_device *ii_dev;
	अचिन्हित दीर्घ state;
पूर्ण;

/**
 * cpuidle_cooling_runसमय - Running समय computation
 * @idle_duration_us: CPU idle समय to inject in microseconds
 * @state: a percentile based number
 *
 * The running duration is computed from the idle injection duration
 * which is fixed. If we reach 100% of idle injection ratio, that
 * means the running duration is zero. If we have a 50% ratio
 * injection, that means we have equal duration क्रम idle and क्रम
 * running duration.
 *
 * The क्रमmula is deduced as follows:
 *
 *  running = idle x ((100 / ratio) - 1)
 *
 * For precision purpose क्रम पूर्णांकeger math, we use the following:
 *
 *  running = (idle x 100) / ratio - idle
 *
 * For example, अगर we have an injected duration of 50%, then we end up
 * with 10ms of idle injection and 10ms of running duration.
 *
 * Return: An अचिन्हित पूर्णांक क्रम a usec based runसमय duration.
 */
अटल अचिन्हित पूर्णांक cpuidle_cooling_runसमय(अचिन्हित पूर्णांक idle_duration_us,
					    अचिन्हित दीर्घ state)
अणु
	अगर (!state)
		वापस 0;

	वापस ((idle_duration_us * 100) / state) - idle_duration_us;
पूर्ण

/**
 * cpuidle_cooling_get_max_state - Get the maximum state
 * @cdev  : the thermal cooling device
 * @state : a poपूर्णांकer to the state variable to be filled
 *
 * The function always वापसs 100 as the injection ratio. It is
 * percentile based क्रम consistency accross dअगरferent platक्रमms.
 *
 * Return: The function can not fail, it is always zero
 */
अटल पूर्णांक cpuidle_cooling_get_max_state(काष्ठा thermal_cooling_device *cdev,
					 अचिन्हित दीर्घ *state)
अणु
	/*
	 * Depending on the configuration or the hardware, the running
	 * cycle and the idle cycle could be dअगरferent. We want to
	 * unअगरy that to an 0..100 पूर्णांकerval, so the set state
	 * पूर्णांकerface will be the same whatever the platक्रमm is.
	 *
	 * The state 100% will make the cluster 100% ... idle. A 0%
	 * injection ratio means no idle injection at all and 50%
	 * means क्रम 10ms of idle injection, we have 10ms of running
	 * समय.
	 */
	*state = 100;

	वापस 0;
पूर्ण

/**
 * cpuidle_cooling_get_cur_state - Get the current cooling state
 * @cdev: the thermal cooling device
 * @state: a poपूर्णांकer to the state
 *
 * The function just copies  the state value from the निजी thermal
 * cooling device काष्ठाure, the mapping is 1 <-> 1.
 *
 * Return: The function can not fail, it is always zero
 */
अटल पूर्णांक cpuidle_cooling_get_cur_state(काष्ठा thermal_cooling_device *cdev,
					 अचिन्हित दीर्घ *state)
अणु
	काष्ठा cpuidle_cooling_device *idle_cdev = cdev->devdata;

	*state = idle_cdev->state;

	वापस 0;
पूर्ण

/**
 * cpuidle_cooling_set_cur_state - Set the current cooling state
 * @cdev: the thermal cooling device
 * @state: the target state
 *
 * The function checks first अगर we are initiating the mitigation which
 * in turn wakes up all the idle injection tasks beदीर्घing to the idle
 * cooling device. In any हाल, it updates the पूर्णांकernal state क्रम the
 * cooling device.
 *
 * Return: The function can not fail, it is always zero
 */
अटल पूर्णांक cpuidle_cooling_set_cur_state(काष्ठा thermal_cooling_device *cdev,
					 अचिन्हित दीर्घ state)
अणु
	काष्ठा cpuidle_cooling_device *idle_cdev = cdev->devdata;
	काष्ठा idle_inject_device *ii_dev = idle_cdev->ii_dev;
	अचिन्हित दीर्घ current_state = idle_cdev->state;
	अचिन्हित पूर्णांक runसमय_us, idle_duration_us;

	idle_cdev->state = state;

	idle_inject_get_duration(ii_dev, &runसमय_us, &idle_duration_us);

	runसमय_us = cpuidle_cooling_runसमय(idle_duration_us, state);

	idle_inject_set_duration(ii_dev, runसमय_us, idle_duration_us);

	अगर (current_state == 0 && state > 0) अणु
		idle_inject_start(ii_dev);
	पूर्ण अन्यथा अगर (current_state > 0 && !state)  अणु
		idle_inject_stop(ii_dev);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cpuidle_cooling_ops - thermal cooling device ops
 */
अटल काष्ठा thermal_cooling_device_ops cpuidle_cooling_ops = अणु
	.get_max_state = cpuidle_cooling_get_max_state,
	.get_cur_state = cpuidle_cooling_get_cur_state,
	.set_cur_state = cpuidle_cooling_set_cur_state,
पूर्ण;

/**
 * __cpuidle_cooling_रेजिस्टर: रेजिस्टर the cooling device
 * @drv: a cpuidle driver काष्ठाure poपूर्णांकer
 * @np: a device node काष्ठाure poपूर्णांकer used क्रम the thermal binding
 *
 * This function is in अक्षरge of allocating the cpuidle cooling device
 * काष्ठाure, the idle injection, initialize them and रेजिस्टर the
 * cooling device to the thermal framework.
 *
 * Return: zero on success, a negative value वापसed by one of the
 * underlying subप्रणाली in हाल of error
 */
अटल पूर्णांक __cpuidle_cooling_रेजिस्टर(काष्ठा device_node *np,
				      काष्ठा cpuidle_driver *drv)
अणु
	काष्ठा idle_inject_device *ii_dev;
	काष्ठा cpuidle_cooling_device *idle_cdev;
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक idle_duration_us = TICK_USEC;
	अचिन्हित पूर्णांक latency_us = अच_पूर्णांक_उच्च;
	अक्षर *name;
	पूर्णांक ret;

	idle_cdev = kzalloc(माप(*idle_cdev), GFP_KERNEL);
	अगर (!idle_cdev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ii_dev = idle_inject_रेजिस्टर(drv->cpumask);
	अगर (!ii_dev) अणु
		ret = -EINVAL;
		जाओ out_kमुक्त;
	पूर्ण

	of_property_पढ़ो_u32(np, "duration-us", &idle_duration_us);
	of_property_पढ़ो_u32(np, "exit-latency-us", &latency_us);

	idle_inject_set_duration(ii_dev, TICK_USEC, idle_duration_us);
	idle_inject_set_latency(ii_dev, latency_us);

	idle_cdev->ii_dev = ii_dev;

	dev = get_cpu_device(cpumask_first(drv->cpumask));

	name = kaप्र_लिखो(GFP_KERNEL, "idle-%s", dev_name(dev));
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ out_unरेजिस्टर;
	पूर्ण

	cdev = thermal_of_cooling_device_रेजिस्टर(np, name, idle_cdev,
						  &cpuidle_cooling_ops);
	अगर (IS_ERR(cdev)) अणु
		ret = PTR_ERR(cdev);
		जाओ out_kमुक्त_name;
	पूर्ण

	pr_debug("%s: Idle injection set with idle duration=%u, latency=%u\n",
		 name, idle_duration_us, latency_us);

	kमुक्त(name);

	वापस 0;

out_kमुक्त_name:
	kमुक्त(name);
out_unरेजिस्टर:
	idle_inject_unरेजिस्टर(ii_dev);
out_kमुक्त:
	kमुक्त(idle_cdev);
out:
	वापस ret;
पूर्ण

/**
 * cpuidle_cooling_रेजिस्टर - Idle cooling device initialization function
 * @drv: a cpuidle driver काष्ठाure poपूर्णांकer
 *
 * This function is in अक्षरge of creating a cooling device per cpuidle
 * driver and रेजिस्टर it to the thermal framework.
 *
 * Return: zero on success, or negative value corresponding to the
 * error detected in the underlying subप्रणालीs.
 */
व्योम cpuidle_cooling_रेजिस्टर(काष्ठा cpuidle_driver *drv)
अणु
	काष्ठा device_node *cooling_node;
	काष्ठा device_node *cpu_node;
	पूर्णांक cpu, ret;

	क्रम_each_cpu(cpu, drv->cpumask) अणु

		cpu_node = of_cpu_device_node_get(cpu);

		cooling_node = of_get_child_by_name(cpu_node, "thermal-idle");

		of_node_put(cpu_node);

		अगर (!cooling_node) अणु
			pr_debug("'thermal-idle' node not found for cpu%d\n", cpu);
			जारी;
		पूर्ण

		ret = __cpuidle_cooling_रेजिस्टर(cooling_node, drv);

		of_node_put(cooling_node);

		अगर (ret) अणु
			pr_err("Failed to register the cpuidle cooling device" \
			       "for cpu%d: %d\n", cpu, ret);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
