<शैली गुरु>
/*
 * governor.c - governor support
 *
 * (C) 2006-2007 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *               Shaohua Li <shaohua.li@पूर्णांकel.com>
 *               Adam Belay <abelay@novell.com>
 *
 * This code is licenced under the GPL.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_qos.h>

#समावेश "cpuidle.h"

अक्षर param_governor[CPUIDLE_NAME_LEN];

LIST_HEAD(cpuidle_governors);
काष्ठा cpuidle_governor *cpuidle_curr_governor;
काष्ठा cpuidle_governor *cpuidle_prev_governor;

/**
 * cpuidle_find_governor - finds a governor of the specअगरied name
 * @str: the name
 *
 * Must be called with cpuidle_lock acquired.
 */
काष्ठा cpuidle_governor *cpuidle_find_governor(स्थिर अक्षर *str)
अणु
	काष्ठा cpuidle_governor *gov;

	list_क्रम_each_entry(gov, &cpuidle_governors, governor_list)
		अगर (!strnहालcmp(str, gov->name, CPUIDLE_NAME_LEN))
			वापस gov;

	वापस शून्य;
पूर्ण

/**
 * cpuidle_चयन_governor - changes the governor
 * @gov: the new target governor
 * Must be called with cpuidle_lock acquired.
 */
पूर्णांक cpuidle_चयन_governor(काष्ठा cpuidle_governor *gov)
अणु
	काष्ठा cpuidle_device *dev;

	अगर (!gov)
		वापस -EINVAL;

	अगर (gov == cpuidle_curr_governor)
		वापस 0;

	cpuidle_uninstall_idle_handler();

	अगर (cpuidle_curr_governor) अणु
		list_क्रम_each_entry(dev, &cpuidle_detected_devices, device_list)
			cpuidle_disable_device(dev);
	पूर्ण

	cpuidle_curr_governor = gov;

	अगर (gov) अणु
		list_क्रम_each_entry(dev, &cpuidle_detected_devices, device_list)
			cpuidle_enable_device(dev);
		cpuidle_install_idle_handler();
		prपूर्णांकk(KERN_INFO "cpuidle: using governor %s\n", gov->name);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cpuidle_रेजिस्टर_governor - रेजिस्टरs a governor
 * @gov: the governor
 */
पूर्णांक cpuidle_रेजिस्टर_governor(काष्ठा cpuidle_governor *gov)
अणु
	पूर्णांक ret = -EEXIST;

	अगर (!gov || !gov->select)
		वापस -EINVAL;

	अगर (cpuidle_disabled())
		वापस -ENODEV;

	mutex_lock(&cpuidle_lock);
	अगर (cpuidle_find_governor(gov->name) == शून्य) अणु
		ret = 0;
		list_add_tail(&gov->governor_list, &cpuidle_governors);
		अगर (!cpuidle_curr_governor ||
		    !strnहालcmp(param_governor, gov->name, CPUIDLE_NAME_LEN) ||
		    (cpuidle_curr_governor->rating < gov->rating &&
		     strnहालcmp(param_governor, cpuidle_curr_governor->name,
				 CPUIDLE_NAME_LEN)))
			cpuidle_चयन_governor(gov);
	पूर्ण
	mutex_unlock(&cpuidle_lock);

	वापस ret;
पूर्ण

/**
 * cpuidle_governor_latency_req - Compute a latency स्थिरraपूर्णांक क्रम CPU
 * @cpu: Target CPU
 */
s64 cpuidle_governor_latency_req(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *device = get_cpu_device(cpu);
	पूर्णांक device_req = dev_pm_qos_raw_resume_latency(device);
	पूर्णांक global_req = cpu_latency_qos_limit();

	अगर (device_req > global_req)
		device_req = global_req;

	वापस (s64)device_req * NSEC_PER_USEC;
पूर्ण
