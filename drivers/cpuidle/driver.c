<शैली गुरु>
/*
 * driver.c - driver support
 *
 * (C) 2006-2007 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *               Shaohua Li <shaohua.li@पूर्णांकel.com>
 *               Adam Belay <abelay@novell.com>
 *
 * This code is licenced under the GPL.
 */

#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/idle.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/tick.h>
#समावेश <linux/cpu.h>

#समावेश "cpuidle.h"

DEFINE_SPINLOCK(cpuidle_driver_lock);

#अगर_घोषित CONFIG_CPU_IDLE_MULTIPLE_DRIVERS

अटल DEFINE_PER_CPU(काष्ठा cpuidle_driver *, cpuidle_drivers);

/**
 * __cpuidle_get_cpu_driver - वापस the cpuidle driver tied to a CPU.
 * @cpu: the CPU handled by the driver
 *
 * Returns a poपूर्णांकer to काष्ठा cpuidle_driver or शून्य अगर no driver has been
 * रेजिस्टरed क्रम @cpu.
 */
अटल काष्ठा cpuidle_driver *__cpuidle_get_cpu_driver(पूर्णांक cpu)
अणु
	वापस per_cpu(cpuidle_drivers, cpu);
पूर्ण

/**
 * __cpuidle_unset_driver - unset per CPU driver variables.
 * @drv: a valid poपूर्णांकer to a काष्ठा cpuidle_driver
 *
 * For each CPU in the driver's CPU mask, unset the रेजिस्टरed driver per CPU
 * variable. If @drv is dअगरferent from the रेजिस्टरed driver, the corresponding
 * variable is not cleared.
 */
अटल अंतरभूत व्योम __cpuidle_unset_driver(काष्ठा cpuidle_driver *drv)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, drv->cpumask) अणु

		अगर (drv != __cpuidle_get_cpu_driver(cpu))
			जारी;

		per_cpu(cpuidle_drivers, cpu) = शून्य;
	पूर्ण
पूर्ण

/**
 * __cpuidle_set_driver - set per CPU driver variables क्रम the given driver.
 * @drv: a valid poपूर्णांकer to a काष्ठा cpuidle_driver
 *
 * Returns 0 on success, -EBUSY अगर any CPU in the cpumask have a driver
 * dअगरferent from drv alपढ़ोy.
 */
अटल अंतरभूत पूर्णांक __cpuidle_set_driver(काष्ठा cpuidle_driver *drv)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, drv->cpumask) अणु
		काष्ठा cpuidle_driver *old_drv;

		old_drv = __cpuidle_get_cpu_driver(cpu);
		अगर (old_drv && old_drv != drv)
			वापस -EBUSY;
	पूर्ण

	क्रम_each_cpu(cpu, drv->cpumask)
		per_cpu(cpuidle_drivers, cpu) = drv;

	वापस 0;
पूर्ण

#अन्यथा

अटल काष्ठा cpuidle_driver *cpuidle_curr_driver;

/**
 * __cpuidle_get_cpu_driver - वापस the global cpuidle driver poपूर्णांकer.
 * @cpu: ignored without the multiple driver support
 *
 * Return a poपूर्णांकer to a काष्ठा cpuidle_driver object or शून्य अगर no driver was
 * previously रेजिस्टरed.
 */
अटल अंतरभूत काष्ठा cpuidle_driver *__cpuidle_get_cpu_driver(पूर्णांक cpu)
अणु
	वापस cpuidle_curr_driver;
पूर्ण

/**
 * __cpuidle_set_driver - assign the global cpuidle driver variable.
 * @drv: poपूर्णांकer to a काष्ठा cpuidle_driver object
 *
 * Returns 0 on success, -EBUSY अगर the driver is alपढ़ोy रेजिस्टरed.
 */
अटल अंतरभूत पूर्णांक __cpuidle_set_driver(काष्ठा cpuidle_driver *drv)
अणु
	अगर (cpuidle_curr_driver)
		वापस -EBUSY;

	cpuidle_curr_driver = drv;

	वापस 0;
पूर्ण

/**
 * __cpuidle_unset_driver - unset the global cpuidle driver variable.
 * @drv: a poपूर्णांकer to a काष्ठा cpuidle_driver
 *
 * Reset the global cpuidle variable to शून्य.  If @drv करोes not match the
 * रेजिस्टरed driver, करो nothing.
 */
अटल अंतरभूत व्योम __cpuidle_unset_driver(काष्ठा cpuidle_driver *drv)
अणु
	अगर (drv == cpuidle_curr_driver)
		cpuidle_curr_driver = शून्य;
पूर्ण

#पूर्ण_अगर

/**
 * cpuidle_setup_broadcast_समयr - enable/disable the broadcast समयr on a cpu
 * @arg: a व्योम poपूर्णांकer used to match the SMP cross call API
 *
 * If @arg is शून्य broadcast is disabled otherwise enabled
 *
 * This function is executed per CPU by an SMP cross call.  It's not
 * supposed to be called directly.
 */
अटल व्योम cpuidle_setup_broadcast_समयr(व्योम *arg)
अणु
	अगर (arg)
		tick_broadcast_enable();
	अन्यथा
		tick_broadcast_disable();
पूर्ण

/**
 * __cpuidle_driver_init - initialize the driver's पूर्णांकernal data
 * @drv: a valid poपूर्णांकer to a काष्ठा cpuidle_driver
 */
अटल व्योम __cpuidle_driver_init(काष्ठा cpuidle_driver *drv)
अणु
	पूर्णांक i;

	/*
	 * Use all possible CPUs as the शेष, because अगर the kernel boots
	 * with some CPUs offline and then we online one of them, the CPU
	 * notअगरier has to know which driver to assign.
	 */
	अगर (!drv->cpumask)
		drv->cpumask = (काष्ठा cpumask *)cpu_possible_mask;

	क्रम (i = 0; i < drv->state_count; i++) अणु
		काष्ठा cpuidle_state *s = &drv->states[i];

		/*
		 * Look क्रम the समयr stop flag in the dअगरferent states and अगर
		 * it is found, indicate that the broadcast समयr has to be set
		 * up.
		 */
		अगर (s->flags & CPUIDLE_FLAG_TIMER_STOP)
			drv->bस_समयr = 1;

		/*
		 * The core will use the target residency and निकास latency
		 * values in nanoseconds, but allow drivers to provide them in
		 * microseconds too.
		 */
		अगर (s->target_residency > 0)
			s->target_residency_ns = s->target_residency * NSEC_PER_USEC;
		अन्यथा अगर (s->target_residency_ns < 0)
			s->target_residency_ns = 0;

		अगर (s->निकास_latency > 0)
			s->निकास_latency_ns = s->निकास_latency * NSEC_PER_USEC;
		अन्यथा अगर (s->निकास_latency_ns < 0)
			s->निकास_latency_ns =  0;
	पूर्ण
पूर्ण

/**
 * __cpuidle_रेजिस्टर_driver: रेजिस्टर the driver
 * @drv: a valid poपूर्णांकer to a काष्ठा cpuidle_driver
 *
 * Do some sanity checks, initialize the driver, assign the driver to the
 * global cpuidle driver variable(s) and set up the broadcast समयr अगर the
 * cpuidle driver has some states that shut करोwn the local समयr.
 *
 * Returns 0 on success, a negative error code otherwise:
 *  * -EINVAL अगर the driver poपूर्णांकer is शून्य or no idle states are available
 *  * -ENODEV अगर the cpuidle framework is disabled
 *  * -EBUSY अगर the driver is alपढ़ोy asचिन्हित to the global variable(s)
 */
अटल पूर्णांक __cpuidle_रेजिस्टर_driver(काष्ठा cpuidle_driver *drv)
अणु
	पूर्णांक ret;

	अगर (!drv || !drv->state_count)
		वापस -EINVAL;

	ret = cpuidle_coupled_state_verअगरy(drv);
	अगर (ret)
		वापस ret;

	अगर (cpuidle_disabled())
		वापस -ENODEV;

	__cpuidle_driver_init(drv);

	ret = __cpuidle_set_driver(drv);
	अगर (ret)
		वापस ret;

	अगर (drv->bस_समयr)
		on_each_cpu_mask(drv->cpumask, cpuidle_setup_broadcast_समयr,
				 (व्योम *)1, 1);

	वापस 0;
पूर्ण

/**
 * __cpuidle_unरेजिस्टर_driver - unरेजिस्टर the driver
 * @drv: a valid poपूर्णांकer to a काष्ठा cpuidle_driver
 *
 * Check अगर the driver is no दीर्घer in use, reset the global cpuidle driver
 * variable(s) and disable the समयr broadcast notअगरication mechanism अगर it was
 * in use.
 *
 */
अटल व्योम __cpuidle_unरेजिस्टर_driver(काष्ठा cpuidle_driver *drv)
अणु
	अगर (drv->bस_समयr) अणु
		drv->bस_समयr = 0;
		on_each_cpu_mask(drv->cpumask, cpuidle_setup_broadcast_समयr,
				 शून्य, 1);
	पूर्ण

	__cpuidle_unset_driver(drv);
पूर्ण

/**
 * cpuidle_रेजिस्टर_driver - रेजिस्टरs a driver
 * @drv: a poपूर्णांकer to a valid काष्ठा cpuidle_driver
 *
 * Register the driver under a lock to prevent concurrent attempts to
 * [un]रेजिस्टर the driver from occuring at the same समय.
 *
 * Returns 0 on success, a negative error code (वापसed by
 * __cpuidle_रेजिस्टर_driver()) otherwise.
 */
पूर्णांक cpuidle_रेजिस्टर_driver(काष्ठा cpuidle_driver *drv)
अणु
	काष्ठा cpuidle_governor *gov;
	पूर्णांक ret;

	spin_lock(&cpuidle_driver_lock);
	ret = __cpuidle_रेजिस्टर_driver(drv);
	spin_unlock(&cpuidle_driver_lock);

	अगर (!ret && !म_माप(param_governor) && drv->governor &&
	    (cpuidle_get_driver() == drv)) अणु
		mutex_lock(&cpuidle_lock);
		gov = cpuidle_find_governor(drv->governor);
		अगर (gov) अणु
			cpuidle_prev_governor = cpuidle_curr_governor;
			अगर (cpuidle_चयन_governor(gov) < 0)
				cpuidle_prev_governor = शून्य;
		पूर्ण
		mutex_unlock(&cpuidle_lock);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cpuidle_रेजिस्टर_driver);

/**
 * cpuidle_unरेजिस्टर_driver - unरेजिस्टरs a driver
 * @drv: a poपूर्णांकer to a valid काष्ठा cpuidle_driver
 *
 * Unरेजिस्टरs the cpuidle driver under a lock to prevent concurrent attempts
 * to [un]रेजिस्टर the driver from occuring at the same समय.  @drv has to
 * match the currently रेजिस्टरed driver.
 */
व्योम cpuidle_unरेजिस्टर_driver(काष्ठा cpuidle_driver *drv)
अणु
	bool enabled = (cpuidle_get_driver() == drv);

	spin_lock(&cpuidle_driver_lock);
	__cpuidle_unरेजिस्टर_driver(drv);
	spin_unlock(&cpuidle_driver_lock);

	अगर (!enabled)
		वापस;

	mutex_lock(&cpuidle_lock);
	अगर (cpuidle_prev_governor) अणु
		अगर (!cpuidle_चयन_governor(cpuidle_prev_governor))
			cpuidle_prev_governor = शून्य;
	पूर्ण
	mutex_unlock(&cpuidle_lock);
पूर्ण
EXPORT_SYMBOL_GPL(cpuidle_unरेजिस्टर_driver);

/**
 * cpuidle_get_driver - वापस the driver tied to the current CPU.
 *
 * Returns a काष्ठा cpuidle_driver poपूर्णांकer, or शून्य अगर no driver is रेजिस्टरed.
 */
काष्ठा cpuidle_driver *cpuidle_get_driver(व्योम)
अणु
	काष्ठा cpuidle_driver *drv;
	पूर्णांक cpu;

	cpu = get_cpu();
	drv = __cpuidle_get_cpu_driver(cpu);
	put_cpu();

	वापस drv;
पूर्ण
EXPORT_SYMBOL_GPL(cpuidle_get_driver);

/**
 * cpuidle_get_cpu_driver - वापस the driver रेजिस्टरed क्रम a CPU.
 * @dev: a valid poपूर्णांकer to a काष्ठा cpuidle_device
 *
 * Returns a काष्ठा cpuidle_driver poपूर्णांकer, or शून्य अगर no driver is रेजिस्टरed
 * क्रम the CPU associated with @dev.
 */
काष्ठा cpuidle_driver *cpuidle_get_cpu_driver(काष्ठा cpuidle_device *dev)
अणु
	अगर (!dev)
		वापस शून्य;

	वापस __cpuidle_get_cpu_driver(dev->cpu);
पूर्ण
EXPORT_SYMBOL_GPL(cpuidle_get_cpu_driver);

/**
 * cpuidle_driver_state_disabled - Disable or enable an idle state
 * @drv: cpuidle driver owning the state
 * @idx: State index
 * @disable: Whether or not to disable the state
 */
व्योम cpuidle_driver_state_disabled(काष्ठा cpuidle_driver *drv, पूर्णांक idx,
				 bool disable)
अणु
	अचिन्हित पूर्णांक cpu;

	mutex_lock(&cpuidle_lock);

	spin_lock(&cpuidle_driver_lock);

	अगर (!drv->cpumask) अणु
		drv->states[idx].flags |= CPUIDLE_FLAG_UNUSABLE;
		जाओ unlock;
	पूर्ण

	क्रम_each_cpu(cpu, drv->cpumask) अणु
		काष्ठा cpuidle_device *dev = per_cpu(cpuidle_devices, cpu);

		अगर (!dev)
			जारी;

		अगर (disable)
			dev->states_usage[idx].disable |= CPUIDLE_STATE_DISABLED_BY_DRIVER;
		अन्यथा
			dev->states_usage[idx].disable &= ~CPUIDLE_STATE_DISABLED_BY_DRIVER;
	पूर्ण

unlock:
	spin_unlock(&cpuidle_driver_lock);

	mutex_unlock(&cpuidle_lock);
पूर्ण
