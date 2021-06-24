<शैली गुरु>
/*
 * cpuidle.c - core cpuidle infraकाष्ठाure
 *
 * (C) 2006-2007 Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 *               Shaohua Li <shaohua.li@पूर्णांकel.com>
 *               Adam Belay <abelay@novell.com>
 *
 * This code is licenced under the GPL.
 */

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/module.h>
#समावेश <linux/suspend.h>
#समावेश <linux/tick.h>
#समावेश <linux/mmu_context.h>
#समावेश <trace/events/घातer.h>

#समावेश "cpuidle.h"

DEFINE_PER_CPU(काष्ठा cpuidle_device *, cpuidle_devices);
DEFINE_PER_CPU(काष्ठा cpuidle_device, cpuidle_dev);

DEFINE_MUTEX(cpuidle_lock);
LIST_HEAD(cpuidle_detected_devices);

अटल पूर्णांक enabled_devices;
अटल पूर्णांक off __पढ़ो_mostly;
अटल पूर्णांक initialized __पढ़ो_mostly;

पूर्णांक cpuidle_disabled(व्योम)
अणु
	वापस off;
पूर्ण
व्योम disable_cpuidle(व्योम)
अणु
	off = 1;
पूर्ण

bool cpuidle_not_available(काष्ठा cpuidle_driver *drv,
			   काष्ठा cpuidle_device *dev)
अणु
	वापस off || !initialized || !drv || !dev || !dev->enabled;
पूर्ण

/**
 * cpuidle_play_dead - cpu off-lining
 *
 * Returns in हाल of an error or no driver
 */
पूर्णांक cpuidle_play_dead(व्योम)
अणु
	काष्ठा cpuidle_device *dev = __this_cpu_पढ़ो(cpuidle_devices);
	काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(dev);
	पूर्णांक i;

	अगर (!drv)
		वापस -ENODEV;

	/* Find lowest-घातer state that supports दीर्घ-term idle */
	क्रम (i = drv->state_count - 1; i >= 0; i--)
		अगर (drv->states[i].enter_dead)
			वापस drv->states[i].enter_dead(dev, i);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक find_deepest_state(काष्ठा cpuidle_driver *drv,
			      काष्ठा cpuidle_device *dev,
			      u64 max_latency_ns,
			      अचिन्हित पूर्णांक क्रमbidden_flags,
			      bool s2idle)
अणु
	u64 latency_req = 0;
	पूर्णांक i, ret = 0;

	क्रम (i = 1; i < drv->state_count; i++) अणु
		काष्ठा cpuidle_state *s = &drv->states[i];

		अगर (dev->states_usage[i].disable ||
		    s->निकास_latency_ns <= latency_req ||
		    s->निकास_latency_ns > max_latency_ns ||
		    (s->flags & क्रमbidden_flags) ||
		    (s2idle && !s->enter_s2idle))
			जारी;

		latency_req = s->निकास_latency_ns;
		ret = i;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * cpuidle_use_deepest_state - Set/unset governor override mode.
 * @latency_limit_ns: Idle state निकास latency limit (or no override अगर 0).
 *
 * If @latency_limit_ns is nonzero, set the current CPU to use the deepest idle
 * state with निकास latency within @latency_limit_ns (override governors going
 * क्रमward), or करो not override governors अगर it is zero.
 */
व्योम cpuidle_use_deepest_state(u64 latency_limit_ns)
अणु
	काष्ठा cpuidle_device *dev;

	preempt_disable();
	dev = cpuidle_get_device();
	अगर (dev)
		dev->क्रमced_idle_latency_limit_ns = latency_limit_ns;
	preempt_enable();
पूर्ण

/**
 * cpuidle_find_deepest_state - Find the deepest available idle state.
 * @drv: cpuidle driver क्रम the given CPU.
 * @dev: cpuidle device क्रम the given CPU.
 * @latency_limit_ns: Idle state निकास latency limit
 *
 * Return: the index of the deepest available idle state.
 */
पूर्णांक cpuidle_find_deepest_state(काष्ठा cpuidle_driver *drv,
			       काष्ठा cpuidle_device *dev,
			       u64 latency_limit_ns)
अणु
	वापस find_deepest_state(drv, dev, latency_limit_ns, 0, false);
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
अटल व्योम enter_s2idle_proper(काष्ठा cpuidle_driver *drv,
				काष्ठा cpuidle_device *dev, पूर्णांक index)
अणु
	kसमय_प्रकार समय_start, समय_end;
	काष्ठा cpuidle_state *target_state = &drv->states[index];

	समय_start = ns_to_kसमय(local_घड़ी());

	tick_मुक्तze();
	/*
	 * The state used here cannot be a "coupled" one, because the "coupled"
	 * cpuidle mechanism enables पूर्णांकerrupts and करोing that with समयkeeping
	 * suspended is generally unsafe.
	 */
	stop_critical_timings();
	अगर (!(target_state->flags & CPUIDLE_FLAG_RCU_IDLE))
		rcu_idle_enter();
	target_state->enter_s2idle(dev, drv, index);
	अगर (WARN_ON_ONCE(!irqs_disabled()))
		local_irq_disable();
	अगर (!(target_state->flags & CPUIDLE_FLAG_RCU_IDLE))
		rcu_idle_निकास();
	tick_unमुक्तze();
	start_critical_timings();

	समय_end = ns_to_kसमय(local_घड़ी());

	dev->states_usage[index].s2idle_समय += kसमय_us_delta(समय_end, समय_start);
	dev->states_usage[index].s2idle_usage++;
पूर्ण

/**
 * cpuidle_enter_s2idle - Enter an idle state suitable क्रम suspend-to-idle.
 * @drv: cpuidle driver क्रम the given CPU.
 * @dev: cpuidle device क्रम the given CPU.
 *
 * If there are states with the ->enter_s2idle callback, find the deepest of
 * them and enter it with frozen tick.
 */
पूर्णांक cpuidle_enter_s2idle(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev)
अणु
	पूर्णांक index;

	/*
	 * Find the deepest state with ->enter_s2idle present, which guarantees
	 * that पूर्णांकerrupts won't be enabled when it निकासs and allows the tick to
	 * be frozen safely.
	 */
	index = find_deepest_state(drv, dev, U64_MAX, 0, true);
	अगर (index > 0) अणु
		enter_s2idle_proper(drv, dev, index);
		local_irq_enable();
	पूर्ण
	वापस index;
पूर्ण
#पूर्ण_अगर /* CONFIG_SUSPEND */

/**
 * cpuidle_enter_state - enter the state and update stats
 * @dev: cpuidle device क्रम this cpu
 * @drv: cpuidle driver क्रम this cpu
 * @index: index पूर्णांकo the states table in @drv of the state to enter
 */
पूर्णांक cpuidle_enter_state(काष्ठा cpuidle_device *dev, काष्ठा cpuidle_driver *drv,
			पूर्णांक index)
अणु
	पूर्णांक entered_state;

	काष्ठा cpuidle_state *target_state = &drv->states[index];
	bool broadcast = !!(target_state->flags & CPUIDLE_FLAG_TIMER_STOP);
	kसमय_प्रकार समय_start, समय_end;

	/*
	 * Tell the समय framework to चयन to a broadcast समयr because our
	 * local समयr will be shut करोwn.  If a local समयr is used from another
	 * CPU as a broadcast समयr, this call may fail अगर it is not available.
	 */
	अगर (broadcast && tick_broadcast_enter()) अणु
		index = find_deepest_state(drv, dev, target_state->निकास_latency_ns,
					   CPUIDLE_FLAG_TIMER_STOP, false);
		अगर (index < 0) अणु
			शेष_idle_call();
			वापस -EBUSY;
		पूर्ण
		target_state = &drv->states[index];
		broadcast = false;
	पूर्ण

	अगर (target_state->flags & CPUIDLE_FLAG_TLB_FLUSHED)
		leave_mm(dev->cpu);

	/* Take note of the planned idle state. */
	sched_idle_set_state(target_state);

	trace_cpu_idle(index, dev->cpu);
	समय_start = ns_to_kसमय(local_घड़ी());

	stop_critical_timings();
	अगर (!(target_state->flags & CPUIDLE_FLAG_RCU_IDLE))
		rcu_idle_enter();
	entered_state = target_state->enter(dev, drv, index);
	अगर (!(target_state->flags & CPUIDLE_FLAG_RCU_IDLE))
		rcu_idle_निकास();
	start_critical_timings();

	sched_घड़ी_idle_wakeup_event();
	समय_end = ns_to_kसमय(local_घड़ी());
	trace_cpu_idle(PWR_EVENT_EXIT, dev->cpu);

	/* The cpu is no दीर्घer idle or about to enter idle. */
	sched_idle_set_state(शून्य);

	अगर (broadcast) अणु
		अगर (WARN_ON_ONCE(!irqs_disabled()))
			local_irq_disable();

		tick_broadcast_निकास();
	पूर्ण

	अगर (!cpuidle_state_is_coupled(drv, index))
		local_irq_enable();

	अगर (entered_state >= 0) अणु
		s64 dअगरf, delay = drv->states[entered_state].निकास_latency_ns;
		पूर्णांक i;

		/*
		 * Update cpuidle counters
		 * This can be moved to within driver enter routine,
		 * but that results in multiple copies of same code.
		 */
		dअगरf = kसमय_sub(समय_end, समय_start);

		dev->last_residency_ns = dअगरf;
		dev->states_usage[entered_state].समय_ns += dअगरf;
		dev->states_usage[entered_state].usage++;

		अगर (dअगरf < drv->states[entered_state].target_residency_ns) अणु
			क्रम (i = entered_state - 1; i >= 0; i--) अणु
				अगर (dev->states_usage[i].disable)
					जारी;

				/* Shallower states are enabled, so update. */
				dev->states_usage[entered_state].above++;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (dअगरf > delay) अणु
			क्रम (i = entered_state + 1; i < drv->state_count; i++) अणु
				अगर (dev->states_usage[i].disable)
					जारी;

				/*
				 * Update अगर a deeper state would have been a
				 * better match क्रम the observed idle duration.
				 */
				अगर (dअगरf - delay >= drv->states[i].target_residency_ns)
					dev->states_usage[entered_state].below++;

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev->last_residency_ns = 0;
		dev->states_usage[index].rejected++;
	पूर्ण

	वापस entered_state;
पूर्ण

/**
 * cpuidle_select - ask the cpuidle framework to choose an idle state
 *
 * @drv: the cpuidle driver
 * @dev: the cpuidle device
 * @stop_tick: indication on whether or not to stop the tick
 *
 * Returns the index of the idle state.  The वापस value must not be negative.
 *
 * The memory location poपूर्णांकed to by @stop_tick is expected to be written the
 * 'false' boolean value अगर the scheduler tick should not be stopped beक्रमe
 * entering the वापसed state.
 */
पूर्णांक cpuidle_select(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev,
		   bool *stop_tick)
अणु
	वापस cpuidle_curr_governor->select(drv, dev, stop_tick);
पूर्ण

/**
 * cpuidle_enter - enter पूर्णांकo the specअगरied idle state
 *
 * @drv:   the cpuidle driver tied with the cpu
 * @dev:   the cpuidle device
 * @index: the index in the idle state table
 *
 * Returns the index in the idle state, < 0 in हाल of error.
 * The error code depends on the backend driver
 */
पूर्णांक cpuidle_enter(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev,
		  पूर्णांक index)
अणु
	पूर्णांक ret = 0;

	/*
	 * Store the next hrसमयr, which becomes either next tick or the next
	 * समयr event, whatever expires first. Additionally, to make this data
	 * useful क्रम consumers outside cpuidle, we rely on that the governor's
	 * ->select() callback have decided, whether to stop the tick or not.
	 */
	WRITE_ONCE(dev->next_hrसमयr, tick_nohz_get_next_hrसमयr());

	अगर (cpuidle_state_is_coupled(drv, index))
		ret = cpuidle_enter_state_coupled(dev, drv, index);
	अन्यथा
		ret = cpuidle_enter_state(dev, drv, index);

	WRITE_ONCE(dev->next_hrसमयr, 0);
	वापस ret;
पूर्ण

/**
 * cpuidle_reflect - tell the underlying governor what was the state
 * we were in
 *
 * @dev  : the cpuidle device
 * @index: the index in the idle state table
 *
 */
व्योम cpuidle_reflect(काष्ठा cpuidle_device *dev, पूर्णांक index)
अणु
	अगर (cpuidle_curr_governor->reflect && index >= 0)
		cpuidle_curr_governor->reflect(dev, index);
पूर्ण

/*
 * Min polling पूर्णांकerval of 10usec is a guess. It is assuming that
 * क्रम most users, the समय क्रम a single ping-pong workload like
 * perf bench pipe would generally complete within 10usec but
 * this is hardware dependant. Actual समय can be estimated with
 *
 * perf bench sched pipe -l 10000
 *
 * Run multiple बार to aव्योम cpufreq effects.
 */
#घोषणा CPUIDLE_POLL_MIN 10000
#घोषणा CPUIDLE_POLL_MAX (TICK_NSEC / 16)

/**
 * cpuidle_poll_समय - वापस amount of समय to poll क्रम,
 * governors can override dev->poll_limit_ns अगर necessary
 *
 * @drv:   the cpuidle driver tied with the cpu
 * @dev:   the cpuidle device
 *
 */
u64 cpuidle_poll_समय(काष्ठा cpuidle_driver *drv,
		      काष्ठा cpuidle_device *dev)
अणु
	पूर्णांक i;
	u64 limit_ns;

	BUILD_BUG_ON(CPUIDLE_POLL_MIN > CPUIDLE_POLL_MAX);

	अगर (dev->poll_limit_ns)
		वापस dev->poll_limit_ns;

	limit_ns = CPUIDLE_POLL_MAX;
	क्रम (i = 1; i < drv->state_count; i++) अणु
		u64 state_limit;

		अगर (dev->states_usage[i].disable)
			जारी;

		state_limit = drv->states[i].target_residency_ns;
		अगर (state_limit < CPUIDLE_POLL_MIN)
			जारी;

		limit_ns = min_t(u64, state_limit, CPUIDLE_POLL_MAX);
		अवरोध;
	पूर्ण

	dev->poll_limit_ns = limit_ns;

	वापस dev->poll_limit_ns;
पूर्ण

/**
 * cpuidle_install_idle_handler - installs the cpuidle idle loop handler
 */
व्योम cpuidle_install_idle_handler(व्योम)
अणु
	अगर (enabled_devices) अणु
		/* Make sure all changes finished beक्रमe we चयन to new idle */
		smp_wmb();
		initialized = 1;
	पूर्ण
पूर्ण

/**
 * cpuidle_uninstall_idle_handler - uninstalls the cpuidle idle loop handler
 */
व्योम cpuidle_uninstall_idle_handler(व्योम)
अणु
	अगर (enabled_devices) अणु
		initialized = 0;
		wake_up_all_idle_cpus();
	पूर्ण

	/*
	 * Make sure बाह्यal observers (such as the scheduler)
	 * are करोne looking at poपूर्णांकed idle states.
	 */
	synchronize_rcu();
पूर्ण

/**
 * cpuidle_छोड़ो_and_lock - temporarily disables CPUIDLE
 */
व्योम cpuidle_छोड़ो_and_lock(व्योम)
अणु
	mutex_lock(&cpuidle_lock);
	cpuidle_uninstall_idle_handler();
पूर्ण

EXPORT_SYMBOL_GPL(cpuidle_छोड़ो_and_lock);

/**
 * cpuidle_resume_and_unlock - resumes CPUIDLE operation
 */
व्योम cpuidle_resume_and_unlock(व्योम)
अणु
	cpuidle_install_idle_handler();
	mutex_unlock(&cpuidle_lock);
पूर्ण

EXPORT_SYMBOL_GPL(cpuidle_resume_and_unlock);

/* Currently used in suspend/resume path to suspend cpuidle */
व्योम cpuidle_छोड़ो(व्योम)
अणु
	mutex_lock(&cpuidle_lock);
	cpuidle_uninstall_idle_handler();
	mutex_unlock(&cpuidle_lock);
पूर्ण

/* Currently used in suspend/resume path to resume cpuidle */
व्योम cpuidle_resume(व्योम)
अणु
	mutex_lock(&cpuidle_lock);
	cpuidle_install_idle_handler();
	mutex_unlock(&cpuidle_lock);
पूर्ण

/**
 * cpuidle_enable_device - enables idle PM क्रम a CPU
 * @dev: the CPU
 *
 * This function must be called between cpuidle_छोड़ो_and_lock and
 * cpuidle_resume_and_unlock when used बाह्यally.
 */
पूर्णांक cpuidle_enable_device(काष्ठा cpuidle_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा cpuidle_driver *drv;

	अगर (!dev)
		वापस -EINVAL;

	अगर (dev->enabled)
		वापस 0;

	अगर (!cpuidle_curr_governor)
		वापस -EIO;

	drv = cpuidle_get_cpu_driver(dev);

	अगर (!drv)
		वापस -EIO;

	अगर (!dev->रेजिस्टरed)
		वापस -EINVAL;

	ret = cpuidle_add_device_sysfs(dev);
	अगर (ret)
		वापस ret;

	अगर (cpuidle_curr_governor->enable) अणु
		ret = cpuidle_curr_governor->enable(drv, dev);
		अगर (ret)
			जाओ fail_sysfs;
	पूर्ण

	smp_wmb();

	dev->enabled = 1;

	enabled_devices++;
	वापस 0;

fail_sysfs:
	cpuidle_हटाओ_device_sysfs(dev);

	वापस ret;
पूर्ण

EXPORT_SYMBOL_GPL(cpuidle_enable_device);

/**
 * cpuidle_disable_device - disables idle PM क्रम a CPU
 * @dev: the CPU
 *
 * This function must be called between cpuidle_छोड़ो_and_lock and
 * cpuidle_resume_and_unlock when used बाह्यally.
 */
व्योम cpuidle_disable_device(काष्ठा cpuidle_device *dev)
अणु
	काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(dev);

	अगर (!dev || !dev->enabled)
		वापस;

	अगर (!drv || !cpuidle_curr_governor)
		वापस;

	dev->enabled = 0;

	अगर (cpuidle_curr_governor->disable)
		cpuidle_curr_governor->disable(drv, dev);

	cpuidle_हटाओ_device_sysfs(dev);
	enabled_devices--;
पूर्ण

EXPORT_SYMBOL_GPL(cpuidle_disable_device);

अटल व्योम __cpuidle_unरेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणु
	काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(dev);

	list_del(&dev->device_list);
	per_cpu(cpuidle_devices, dev->cpu) = शून्य;
	module_put(drv->owner);

	dev->रेजिस्टरed = 0;
पूर्ण

अटल व्योम __cpuidle_device_init(काष्ठा cpuidle_device *dev)
अणु
	स_रखो(dev->states_usage, 0, माप(dev->states_usage));
	dev->last_residency_ns = 0;
	dev->next_hrसमयr = 0;
पूर्ण

/**
 * __cpuidle_रेजिस्टर_device - पूर्णांकernal रेजिस्टर function called beक्रमe रेजिस्टर
 * and enable routines
 * @dev: the cpu
 *
 * cpuidle_lock mutex must be held beक्रमe this is called
 */
अटल पूर्णांक __cpuidle_रेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणु
	काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(dev);
	पूर्णांक i, ret;

	अगर (!try_module_get(drv->owner))
		वापस -EINVAL;

	क्रम (i = 0; i < drv->state_count; i++) अणु
		अगर (drv->states[i].flags & CPUIDLE_FLAG_UNUSABLE)
			dev->states_usage[i].disable |= CPUIDLE_STATE_DISABLED_BY_DRIVER;

		अगर (drv->states[i].flags & CPUIDLE_FLAG_OFF)
			dev->states_usage[i].disable |= CPUIDLE_STATE_DISABLED_BY_USER;
	पूर्ण

	per_cpu(cpuidle_devices, dev->cpu) = dev;
	list_add(&dev->device_list, &cpuidle_detected_devices);

	ret = cpuidle_coupled_रेजिस्टर_device(dev);
	अगर (ret)
		__cpuidle_unरेजिस्टर_device(dev);
	अन्यथा
		dev->रेजिस्टरed = 1;

	वापस ret;
पूर्ण

/**
 * cpuidle_रेजिस्टर_device - रेजिस्टरs a CPU's idle PM feature
 * @dev: the cpu
 */
पूर्णांक cpuidle_रेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणु
	पूर्णांक ret = -EBUSY;

	अगर (!dev)
		वापस -EINVAL;

	mutex_lock(&cpuidle_lock);

	अगर (dev->रेजिस्टरed)
		जाओ out_unlock;

	__cpuidle_device_init(dev);

	ret = __cpuidle_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ out_unlock;

	ret = cpuidle_add_sysfs(dev);
	अगर (ret)
		जाओ out_unरेजिस्टर;

	ret = cpuidle_enable_device(dev);
	अगर (ret)
		जाओ out_sysfs;

	cpuidle_install_idle_handler();

out_unlock:
	mutex_unlock(&cpuidle_lock);

	वापस ret;

out_sysfs:
	cpuidle_हटाओ_sysfs(dev);
out_unरेजिस्टर:
	__cpuidle_unरेजिस्टर_device(dev);
	जाओ out_unlock;
पूर्ण

EXPORT_SYMBOL_GPL(cpuidle_रेजिस्टर_device);

/**
 * cpuidle_unरेजिस्टर_device - unरेजिस्टरs a CPU's idle PM feature
 * @dev: the cpu
 */
व्योम cpuidle_unरेजिस्टर_device(काष्ठा cpuidle_device *dev)
अणु
	अगर (!dev || dev->रेजिस्टरed == 0)
		वापस;

	cpuidle_छोड़ो_and_lock();

	cpuidle_disable_device(dev);

	cpuidle_हटाओ_sysfs(dev);

	__cpuidle_unरेजिस्टर_device(dev);

	cpuidle_coupled_unरेजिस्टर_device(dev);

	cpuidle_resume_and_unlock();
पूर्ण

EXPORT_SYMBOL_GPL(cpuidle_unरेजिस्टर_device);

/**
 * cpuidle_unरेजिस्टर: unरेजिस्टर a driver and the devices. This function
 * can be used only अगर the driver has been previously रेजिस्टरed through
 * the cpuidle_रेजिस्टर function.
 *
 * @drv: a valid poपूर्णांकer to a काष्ठा cpuidle_driver
 */
व्योम cpuidle_unरेजिस्टर(काष्ठा cpuidle_driver *drv)
अणु
	पूर्णांक cpu;
	काष्ठा cpuidle_device *device;

	क्रम_each_cpu(cpu, drv->cpumask) अणु
		device = &per_cpu(cpuidle_dev, cpu);
		cpuidle_unरेजिस्टर_device(device);
	पूर्ण

	cpuidle_unरेजिस्टर_driver(drv);
पूर्ण
EXPORT_SYMBOL_GPL(cpuidle_unरेजिस्टर);

/**
 * cpuidle_रेजिस्टर: रेजिस्टरs the driver and the cpu devices with the
 * coupled_cpus passed as parameter. This function is used क्रम all common
 * initialization pattern there are in the arch specअगरic drivers. The
 * devices is globally defined in this file.
 *
 * @drv         : a valid poपूर्णांकer to a काष्ठा cpuidle_driver
 * @coupled_cpus: a cpumask क्रम the coupled states
 *
 * Returns 0 on success, < 0 otherwise
 */
पूर्णांक cpuidle_रेजिस्टर(काष्ठा cpuidle_driver *drv,
		     स्थिर काष्ठा cpumask *स्थिर coupled_cpus)
अणु
	पूर्णांक ret, cpu;
	काष्ठा cpuidle_device *device;

	ret = cpuidle_रेजिस्टर_driver(drv);
	अगर (ret) अणु
		pr_err("failed to register cpuidle driver\n");
		वापस ret;
	पूर्ण

	क्रम_each_cpu(cpu, drv->cpumask) अणु
		device = &per_cpu(cpuidle_dev, cpu);
		device->cpu = cpu;

#अगर_घोषित CONFIG_ARCH_NEEDS_CPU_IDLE_COUPLED
		/*
		 * On multiplatक्रमm क्रम ARM, the coupled idle states could be
		 * enabled in the kernel even अगर the cpuidle driver करोes not
		 * use it. Note, coupled_cpus is a काष्ठा copy.
		 */
		अगर (coupled_cpus)
			device->coupled_cpus = *coupled_cpus;
#पूर्ण_अगर
		ret = cpuidle_रेजिस्टर_device(device);
		अगर (!ret)
			जारी;

		pr_err("Failed to register cpuidle device for cpu%d\n", cpu);

		cpuidle_unरेजिस्टर(drv);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cpuidle_रेजिस्टर);

/**
 * cpuidle_init - core initializer
 */
अटल पूर्णांक __init cpuidle_init(व्योम)
अणु
	अगर (cpuidle_disabled())
		वापस -ENODEV;

	वापस cpuidle_add_पूर्णांकerface(cpu_subsys.dev_root);
पूर्ण

module_param(off, पूर्णांक, 0444);
module_param_string(governor, param_governor, CPUIDLE_NAME_LEN, 0444);
core_initcall(cpuidle_init);
