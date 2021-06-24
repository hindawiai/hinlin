<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains functions which manage घड़ी event devices.
 *
 * Copyright(C) 2005-2006, Thomas Gleixner <tglx@linutronix.de>
 * Copyright(C) 2005-2007, Red Hat, Inc., Ingo Molnar
 * Copyright(C) 2006-2007, Timesys Corp., Thomas Gleixner
 */

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/smp.h>
#समावेश <linux/device.h>

#समावेश "tick-internal.h"

/* The रेजिस्टरed घड़ी event devices */
अटल LIST_HEAD(घड़ीevent_devices);
अटल LIST_HEAD(घड़ीevents_released);
/* Protection क्रम the above */
अटल DEFINE_RAW_SPINLOCK(घड़ीevents_lock);
/* Protection क्रम unbind operations */
अटल DEFINE_MUTEX(घड़ीevents_mutex);

काष्ठा ce_unbind अणु
	काष्ठा घड़ी_event_device *ce;
	पूर्णांक res;
पूर्ण;

अटल u64 cev_delta2ns(अचिन्हित दीर्घ latch, काष्ठा घड़ी_event_device *evt,
			bool ismax)
अणु
	u64 clc = (u64) latch << evt->shअगरt;
	u64 rnd;

	अगर (WARN_ON(!evt->mult))
		evt->mult = 1;
	rnd = (u64) evt->mult - 1;

	/*
	 * Upper bound sanity check. If the backwards conversion is
	 * not equal latch, we know that the above shअगरt overflowed.
	 */
	अगर ((clc >> evt->shअगरt) != (u64)latch)
		clc = ~0ULL;

	/*
	 * Scaled math oddities:
	 *
	 * For mult <= (1 << shअगरt) we can safely add mult - 1 to
	 * prevent पूर्णांकeger rounding loss. So the backwards conversion
	 * from nsec to device ticks will be correct.
	 *
	 * For mult > (1 << shअगरt), i.e. device frequency is > 1GHz we
	 * need to be careful. Adding mult - 1 will result in a value
	 * which when converted back to device ticks can be larger
	 * than latch by up to (mult - 1) >> shअगरt. For the min_delta
	 * calculation we still want to apply this in order to stay
	 * above the minimum device ticks limit. For the upper limit
	 * we would end up with a latch value larger than the upper
	 * limit of the device, so we omit the add to stay below the
	 * device upper boundary.
	 *
	 * Also omit the add अगर it would overflow the u64 boundary.
	 */
	अगर ((~0ULL - clc > rnd) &&
	    (!ismax || evt->mult <= (1ULL << evt->shअगरt)))
		clc += rnd;

	करो_भाग(clc, evt->mult);

	/* Deltas less than 1usec are poपूर्णांकless noise */
	वापस clc > 1000 ? clc : 1000;
पूर्ण

/**
 * घड़ीevents_delta2ns - Convert a latch value (device ticks) to nanoseconds
 * @latch:	value to convert
 * @evt:	poपूर्णांकer to घड़ी event device descriptor
 *
 * Math helper, वापसs latch value converted to nanoseconds (bound checked)
 */
u64 घड़ीevent_delta2ns(अचिन्हित दीर्घ latch, काष्ठा घड़ी_event_device *evt)
अणु
	वापस cev_delta2ns(latch, evt, false);
पूर्ण
EXPORT_SYMBOL_GPL(घड़ीevent_delta2ns);

अटल पूर्णांक __घड़ीevents_चयन_state(काष्ठा घड़ी_event_device *dev,
				      क्रमागत घड़ी_event_state state)
अणु
	अगर (dev->features & CLOCK_EVT_FEAT_DUMMY)
		वापस 0;

	/* Transition with new state-specअगरic callbacks */
	चयन (state) अणु
	हाल CLOCK_EVT_STATE_DETACHED:
		/* The घड़ीevent device is getting replaced. Shut it करोwn. */

	हाल CLOCK_EVT_STATE_SHUTDOWN:
		अगर (dev->set_state_shutकरोwn)
			वापस dev->set_state_shutकरोwn(dev);
		वापस 0;

	हाल CLOCK_EVT_STATE_PERIODIC:
		/* Core पूर्णांकernal bug */
		अगर (!(dev->features & CLOCK_EVT_FEAT_PERIODIC))
			वापस -ENOSYS;
		अगर (dev->set_state_periodic)
			वापस dev->set_state_periodic(dev);
		वापस 0;

	हाल CLOCK_EVT_STATE_ONESHOT:
		/* Core पूर्णांकernal bug */
		अगर (!(dev->features & CLOCK_EVT_FEAT_ONESHOT))
			वापस -ENOSYS;
		अगर (dev->set_state_oneshot)
			वापस dev->set_state_oneshot(dev);
		वापस 0;

	हाल CLOCK_EVT_STATE_ONESHOT_STOPPED:
		/* Core पूर्णांकernal bug */
		अगर (WARN_ONCE(!घड़ीevent_state_oneshot(dev),
			      "Current state: %d\n",
			      घड़ीevent_get_state(dev)))
			वापस -EINVAL;

		अगर (dev->set_state_oneshot_stopped)
			वापस dev->set_state_oneshot_stopped(dev);
		अन्यथा
			वापस -ENOSYS;

	शेष:
		वापस -ENOSYS;
	पूर्ण
पूर्ण

/**
 * घड़ीevents_चयन_state - set the operating state of a घड़ी event device
 * @dev:	device to modअगरy
 * @state:	new state
 *
 * Must be called with पूर्णांकerrupts disabled !
 */
व्योम घड़ीevents_चयन_state(काष्ठा घड़ी_event_device *dev,
			      क्रमागत घड़ी_event_state state)
अणु
	अगर (घड़ीevent_get_state(dev) != state) अणु
		अगर (__घड़ीevents_चयन_state(dev, state))
			वापस;

		घड़ीevent_set_state(dev, state);

		/*
		 * A nsec2cyc multiplicator of 0 is invalid and we'd crash
		 * on it, so fix it up and emit a warning:
		 */
		अगर (घड़ीevent_state_oneshot(dev)) अणु
			अगर (WARN_ON(!dev->mult))
				dev->mult = 1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * घड़ीevents_shutकरोwn - shutकरोwn the device and clear next_event
 * @dev:	device to shutकरोwn
 */
व्योम घड़ीevents_shutकरोwn(काष्ठा घड़ी_event_device *dev)
अणु
	घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_SHUTDOWN);
	dev->next_event = KTIME_MAX;
पूर्ण

/**
 * घड़ीevents_tick_resume -	Resume the tick device beक्रमe using it again
 * @dev:			device to resume
 */
पूर्णांक घड़ीevents_tick_resume(काष्ठा घड़ी_event_device *dev)
अणु
	पूर्णांक ret = 0;

	अगर (dev->tick_resume)
		ret = dev->tick_resume(dev);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_MIN_ADJUST

/* Limit min_delta to a jअगरfie */
#घोषणा MIN_DELTA_LIMIT		(NSEC_PER_SEC / HZ)

/**
 * घड़ीevents_increase_min_delta - उठाओ minimum delta of a घड़ी event device
 * @dev:       device to increase the minimum delta
 *
 * Returns 0 on success, -ETIME when the minimum delta reached the limit.
 */
अटल पूर्णांक घड़ीevents_increase_min_delta(काष्ठा घड़ी_event_device *dev)
अणु
	/* Nothing to करो अगर we alपढ़ोy reached the limit */
	अगर (dev->min_delta_ns >= MIN_DELTA_LIMIT) अणु
		prपूर्णांकk_deferred(KERN_WARNING
				"CE: Reprogramming failure. Giving up\n");
		dev->next_event = KTIME_MAX;
		वापस -ETIME;
	पूर्ण

	अगर (dev->min_delta_ns < 5000)
		dev->min_delta_ns = 5000;
	अन्यथा
		dev->min_delta_ns += dev->min_delta_ns >> 1;

	अगर (dev->min_delta_ns > MIN_DELTA_LIMIT)
		dev->min_delta_ns = MIN_DELTA_LIMIT;

	prपूर्णांकk_deferred(KERN_WARNING
			"CE: %s increased min_delta_ns to %llu nsec\n",
			dev->name ? dev->name : "?",
			(अचिन्हित दीर्घ दीर्घ) dev->min_delta_ns);
	वापस 0;
पूर्ण

/**
 * घड़ीevents_program_min_delta - Set घड़ी event device to the minimum delay.
 * @dev:	device to program
 *
 * Returns 0 on success, -ETIME when the retry loop failed.
 */
अटल पूर्णांक घड़ीevents_program_min_delta(काष्ठा घड़ी_event_device *dev)
अणु
	अचिन्हित दीर्घ दीर्घ clc;
	पूर्णांक64_t delta;
	पूर्णांक i;

	क्रम (i = 0;;) अणु
		delta = dev->min_delta_ns;
		dev->next_event = kसमय_add_ns(kसमय_get(), delta);

		अगर (घड़ीevent_state_shutकरोwn(dev))
			वापस 0;

		dev->retries++;
		clc = ((अचिन्हित दीर्घ दीर्घ) delta * dev->mult) >> dev->shअगरt;
		अगर (dev->set_next_event((अचिन्हित दीर्घ) clc, dev) == 0)
			वापस 0;

		अगर (++i > 2) अणु
			/*
			 * We tried 3 बार to program the device with the
			 * given min_delta_ns. Try to increase the minimum
			 * delta, अगर that fails as well get out of here.
			 */
			अगर (घड़ीevents_increase_min_delta(dev))
				वापस -ETIME;
			i = 0;
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा  /* CONFIG_GENERIC_CLOCKEVENTS_MIN_ADJUST */

/**
 * घड़ीevents_program_min_delta - Set घड़ी event device to the minimum delay.
 * @dev:	device to program
 *
 * Returns 0 on success, -ETIME when the retry loop failed.
 */
अटल पूर्णांक घड़ीevents_program_min_delta(काष्ठा घड़ी_event_device *dev)
अणु
	अचिन्हित दीर्घ दीर्घ clc;
	पूर्णांक64_t delta = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		delta += dev->min_delta_ns;
		dev->next_event = kसमय_add_ns(kसमय_get(), delta);

		अगर (घड़ीevent_state_shutकरोwn(dev))
			वापस 0;

		dev->retries++;
		clc = ((अचिन्हित दीर्घ दीर्घ) delta * dev->mult) >> dev->shअगरt;
		अगर (dev->set_next_event((अचिन्हित दीर्घ) clc, dev) == 0)
			वापस 0;
	पूर्ण
	वापस -ETIME;
पूर्ण

#पूर्ण_अगर /* CONFIG_GENERIC_CLOCKEVENTS_MIN_ADJUST */

/**
 * घड़ीevents_program_event - Reprogram the घड़ी event device.
 * @dev:	device to program
 * @expires:	असलolute expiry समय (monotonic घड़ी)
 * @क्रमce:	program minimum delay अगर expires can not be set
 *
 * Returns 0 on success, -ETIME when the event is in the past.
 */
पूर्णांक घड़ीevents_program_event(काष्ठा घड़ी_event_device *dev, kसमय_प्रकार expires,
			      bool क्रमce)
अणु
	अचिन्हित दीर्घ दीर्घ clc;
	पूर्णांक64_t delta;
	पूर्णांक rc;

	अगर (WARN_ON_ONCE(expires < 0))
		वापस -ETIME;

	dev->next_event = expires;

	अगर (घड़ीevent_state_shutकरोwn(dev))
		वापस 0;

	/* We must be in ONESHOT state here */
	WARN_ONCE(!घड़ीevent_state_oneshot(dev), "Current state: %d\n",
		  घड़ीevent_get_state(dev));

	/* Shortcut क्रम घड़ीevent devices that can deal with kसमय. */
	अगर (dev->features & CLOCK_EVT_FEAT_KTIME)
		वापस dev->set_next_kसमय(expires, dev);

	delta = kसमय_प्रकारo_ns(kसमय_sub(expires, kसमय_get()));
	अगर (delta <= 0)
		वापस क्रमce ? घड़ीevents_program_min_delta(dev) : -ETIME;

	delta = min(delta, (पूर्णांक64_t) dev->max_delta_ns);
	delta = max(delta, (पूर्णांक64_t) dev->min_delta_ns);

	clc = ((अचिन्हित दीर्घ दीर्घ) delta * dev->mult) >> dev->shअगरt;
	rc = dev->set_next_event((अचिन्हित दीर्घ) clc, dev);

	वापस (rc && क्रमce) ? घड़ीevents_program_min_delta(dev) : rc;
पूर्ण

/*
 * Called after a notअगरy add to make devices available which were
 * released from the notअगरier call.
 */
अटल व्योम घड़ीevents_notअगरy_released(व्योम)
अणु
	काष्ठा घड़ी_event_device *dev;

	जबतक (!list_empty(&घड़ीevents_released)) अणु
		dev = list_entry(घड़ीevents_released.next,
				 काष्ठा घड़ी_event_device, list);
		list_del(&dev->list);
		list_add(&dev->list, &घड़ीevent_devices);
		tick_check_new_device(dev);
	पूर्ण
पूर्ण

/*
 * Try to install a replacement घड़ी event device
 */
अटल पूर्णांक घड़ीevents_replace(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा घड़ी_event_device *dev, *newdev = शून्य;

	list_क्रम_each_entry(dev, &घड़ीevent_devices, list) अणु
		अगर (dev == ced || !घड़ीevent_state_detached(dev))
			जारी;

		अगर (!tick_check_replacement(newdev, dev))
			जारी;

		अगर (!try_module_get(dev->owner))
			जारी;

		अगर (newdev)
			module_put(newdev->owner);
		newdev = dev;
	पूर्ण
	अगर (newdev) अणु
		tick_install_replacement(newdev);
		list_del_init(&ced->list);
	पूर्ण
	वापस newdev ? 0 : -EBUSY;
पूर्ण

/*
 * Called with घड़ीevents_mutex and घड़ीevents_lock held
 */
अटल पूर्णांक __घड़ीevents_try_unbind(काष्ठा घड़ी_event_device *ced, पूर्णांक cpu)
अणु
	/* Fast track. Device is unused */
	अगर (घड़ीevent_state_detached(ced)) अणु
		list_del_init(&ced->list);
		वापस 0;
	पूर्ण

	वापस ced == per_cpu(tick_cpu_device, cpu).evtdev ? -EAGAIN : -EBUSY;
पूर्ण

/*
 * SMP function call to unbind a device
 */
अटल व्योम __घड़ीevents_unbind(व्योम *arg)
अणु
	काष्ठा ce_unbind *cu = arg;
	पूर्णांक res;

	raw_spin_lock(&घड़ीevents_lock);
	res = __घड़ीevents_try_unbind(cu->ce, smp_processor_id());
	अगर (res == -EAGAIN)
		res = घड़ीevents_replace(cu->ce);
	cu->res = res;
	raw_spin_unlock(&घड़ीevents_lock);
पूर्ण

/*
 * Issues smp function call to unbind a per cpu device. Called with
 * घड़ीevents_mutex held.
 */
अटल पूर्णांक घड़ीevents_unbind(काष्ठा घड़ी_event_device *ced, पूर्णांक cpu)
अणु
	काष्ठा ce_unbind cu = अणु .ce = ced, .res = -ENODEV पूर्ण;

	smp_call_function_single(cpu, __घड़ीevents_unbind, &cu, 1);
	वापस cu.res;
पूर्ण

/*
 * Unbind a घड़ीevents device.
 */
पूर्णांक घड़ीevents_unbind_device(काष्ठा घड़ी_event_device *ced, पूर्णांक cpu)
अणु
	पूर्णांक ret;

	mutex_lock(&घड़ीevents_mutex);
	ret = घड़ीevents_unbind(ced, cpu);
	mutex_unlock(&घड़ीevents_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(घड़ीevents_unbind_device);

/**
 * घड़ीevents_रेजिस्टर_device - रेजिस्टर a घड़ी event device
 * @dev:	device to रेजिस्टर
 */
व्योम घड़ीevents_रेजिस्टर_device(काष्ठा घड़ी_event_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	/* Initialize state to DETACHED */
	घड़ीevent_set_state(dev, CLOCK_EVT_STATE_DETACHED);

	अगर (!dev->cpumask) अणु
		WARN_ON(num_possible_cpus() > 1);
		dev->cpumask = cpumask_of(smp_processor_id());
	पूर्ण

	अगर (dev->cpumask == cpu_all_mask) अणु
		WARN(1, "%s cpumask == cpu_all_mask, using cpu_possible_mask instead\n",
		     dev->name);
		dev->cpumask = cpu_possible_mask;
	पूर्ण

	raw_spin_lock_irqsave(&घड़ीevents_lock, flags);

	list_add(&dev->list, &घड़ीevent_devices);
	tick_check_new_device(dev);
	घड़ीevents_notअगरy_released();

	raw_spin_unlock_irqrestore(&घड़ीevents_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(घड़ीevents_रेजिस्टर_device);

अटल व्योम घड़ीevents_config(काष्ठा घड़ी_event_device *dev, u32 freq)
अणु
	u64 sec;

	अगर (!(dev->features & CLOCK_EVT_FEAT_ONESHOT))
		वापस;

	/*
	 * Calculate the maximum number of seconds we can sleep. Limit
	 * to 10 minutes क्रम hardware which can program more than
	 * 32bit ticks so we still get reasonable conversion values.
	 */
	sec = dev->max_delta_ticks;
	करो_भाग(sec, freq);
	अगर (!sec)
		sec = 1;
	अन्यथा अगर (sec > 600 && dev->max_delta_ticks > अच_पूर्णांक_उच्च)
		sec = 600;

	घड़ीevents_calc_mult_shअगरt(dev, freq, sec);
	dev->min_delta_ns = cev_delta2ns(dev->min_delta_ticks, dev, false);
	dev->max_delta_ns = cev_delta2ns(dev->max_delta_ticks, dev, true);
पूर्ण

/**
 * घड़ीevents_config_and_रेजिस्टर - Configure and रेजिस्टर a घड़ी event device
 * @dev:	device to रेजिस्टर
 * @freq:	The घड़ी frequency
 * @min_delta:	The minimum घड़ी ticks to program in oneshot mode
 * @max_delta:	The maximum घड़ी ticks to program in oneshot mode
 *
 * min/max_delta can be 0 क्रम devices which करो not support oneshot mode.
 */
व्योम घड़ीevents_config_and_रेजिस्टर(काष्ठा घड़ी_event_device *dev,
				     u32 freq, अचिन्हित दीर्घ min_delta,
				     अचिन्हित दीर्घ max_delta)
अणु
	dev->min_delta_ticks = min_delta;
	dev->max_delta_ticks = max_delta;
	घड़ीevents_config(dev, freq);
	घड़ीevents_रेजिस्टर_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(घड़ीevents_config_and_रेजिस्टर);

पूर्णांक __घड़ीevents_update_freq(काष्ठा घड़ी_event_device *dev, u32 freq)
अणु
	घड़ीevents_config(dev, freq);

	अगर (घड़ीevent_state_oneshot(dev))
		वापस घड़ीevents_program_event(dev, dev->next_event, false);

	अगर (घड़ीevent_state_periodic(dev))
		वापस __घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_PERIODIC);

	वापस 0;
पूर्ण

/**
 * घड़ीevents_update_freq - Update frequency and reprogram a घड़ी event device.
 * @dev:	device to modअगरy
 * @freq:	new device frequency
 *
 * Reconfigure and reprogram a घड़ी event device in oneshot
 * mode. Must be called on the cpu क्रम which the device delivers per
 * cpu समयr events. If called क्रम the broadcast device the core takes
 * care of serialization.
 *
 * Returns 0 on success, -ETIME when the event is in the past.
 */
पूर्णांक घड़ीevents_update_freq(काष्ठा घड़ी_event_device *dev, u32 freq)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	local_irq_save(flags);
	ret = tick_broadcast_update_freq(dev, freq);
	अगर (ret == -ENODEV)
		ret = __घड़ीevents_update_freq(dev, freq);
	local_irq_restore(flags);
	वापस ret;
पूर्ण

/*
 * Noop handler when we shut करोwn an event device
 */
व्योम घड़ीevents_handle_noop(काष्ठा घड़ी_event_device *dev)
अणु
पूर्ण

/**
 * घड़ीevents_exchange_device - release and request घड़ी devices
 * @old:	device to release (can be शून्य)
 * @new:	device to request (can be शून्य)
 *
 * Called from various tick functions with घड़ीevents_lock held and
 * पूर्णांकerrupts disabled.
 */
व्योम घड़ीevents_exchange_device(काष्ठा घड़ी_event_device *old,
				 काष्ठा घड़ी_event_device *new)
अणु
	/*
	 * Caller releases a घड़ी event device. We queue it पूर्णांकo the
	 * released list and करो a notअगरy add later.
	 */
	अगर (old) अणु
		module_put(old->owner);
		घड़ीevents_चयन_state(old, CLOCK_EVT_STATE_DETACHED);
		list_del(&old->list);
		list_add(&old->list, &घड़ीevents_released);
	पूर्ण

	अगर (new) अणु
		BUG_ON(!घड़ीevent_state_detached(new));
		घड़ीevents_shutकरोwn(new);
	पूर्ण
पूर्ण

/**
 * घड़ीevents_suspend - suspend घड़ी devices
 */
व्योम घड़ीevents_suspend(व्योम)
अणु
	काष्ठा घड़ी_event_device *dev;

	list_क्रम_each_entry_reverse(dev, &घड़ीevent_devices, list)
		अगर (dev->suspend && !घड़ीevent_state_detached(dev))
			dev->suspend(dev);
पूर्ण

/**
 * घड़ीevents_resume - resume घड़ी devices
 */
व्योम घड़ीevents_resume(व्योम)
अणु
	काष्ठा घड़ी_event_device *dev;

	list_क्रम_each_entry(dev, &घड़ीevent_devices, list)
		अगर (dev->resume && !घड़ीevent_state_detached(dev))
			dev->resume(dev);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

# अगरdef CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
/**
 * tick_offline_cpu - Take CPU out of the broadcast mechanism
 * @cpu:	The outgoing CPU
 *
 * Called on the outgoing CPU after it took itself offline.
 */
व्योम tick_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	raw_spin_lock(&घड़ीevents_lock);
	tick_broadcast_offline(cpu);
	raw_spin_unlock(&घड़ीevents_lock);
पूर्ण
# endअगर

/**
 * tick_cleanup_dead_cpu - Cleanup the tick and घड़ीevents of a dead cpu
 */
व्योम tick_cleanup_dead_cpu(पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *dev, *पंचांगp;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&घड़ीevents_lock, flags);

	tick_shutकरोwn(cpu);
	/*
	 * Unरेजिस्टर the घड़ी event devices which were
	 * released from the users in the notअगरy chain.
	 */
	list_क्रम_each_entry_safe(dev, पंचांगp, &घड़ीevents_released, list)
		list_del(&dev->list);
	/*
	 * Now check whether the CPU has left unused per cpu devices
	 */
	list_क्रम_each_entry_safe(dev, पंचांगp, &घड़ीevent_devices, list) अणु
		अगर (cpumask_test_cpu(cpu, dev->cpumask) &&
		    cpumask_weight(dev->cpumask) == 1 &&
		    !tick_is_broadcast_device(dev)) अणु
			BUG_ON(!घड़ीevent_state_detached(dev));
			list_del(&dev->list);
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&घड़ीevents_lock, flags);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSFS
अटल काष्ठा bus_type घड़ीevents_subsys = अणु
	.name		= "clockevents",
	.dev_name       = "clockevent",
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा device, tick_percpu_dev);
अटल काष्ठा tick_device *tick_get_tick_dev(काष्ठा device *dev);

अटल sमाप_प्रकार sysfs_show_current_tick_dev(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा tick_device *td;
	sमाप_प्रकार count = 0;

	raw_spin_lock_irq(&घड़ीevents_lock);
	td = tick_get_tick_dev(dev);
	अगर (td && td->evtdev)
		count = snम_लिखो(buf, PAGE_SIZE, "%s\n", td->evtdev->name);
	raw_spin_unlock_irq(&घड़ीevents_lock);
	वापस count;
पूर्ण
अटल DEVICE_ATTR(current_device, 0444, sysfs_show_current_tick_dev, शून्य);

/* We करोn't support the abomination of removable broadcast devices */
अटल sमाप_प्रकार sysfs_unbind_tick_dev(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर name[CS_NAME_LEN];
	sमाप_प्रकार ret = sysfs_get_uname(buf, name, count);
	काष्ठा घड़ी_event_device *ce;

	अगर (ret < 0)
		वापस ret;

	ret = -ENODEV;
	mutex_lock(&घड़ीevents_mutex);
	raw_spin_lock_irq(&घड़ीevents_lock);
	list_क्रम_each_entry(ce, &घड़ीevent_devices, list) अणु
		अगर (!म_भेद(ce->name, name)) अणु
			ret = __घड़ीevents_try_unbind(ce, dev->id);
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irq(&घड़ीevents_lock);
	/*
	 * We hold घड़ीevents_mutex, so ce can't go away
	 */
	अगर (ret == -EAGAIN)
		ret = घड़ीevents_unbind(ce, dev->id);
	mutex_unlock(&घड़ीevents_mutex);
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR(unbind_device, 0200, शून्य, sysfs_unbind_tick_dev);

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
अटल काष्ठा device tick_bc_dev = अणु
	.init_name	= "broadcast",
	.id		= 0,
	.bus		= &घड़ीevents_subsys,
पूर्ण;

अटल काष्ठा tick_device *tick_get_tick_dev(काष्ठा device *dev)
अणु
	वापस dev == &tick_bc_dev ? tick_get_broadcast_device() :
		&per_cpu(tick_cpu_device, dev->id);
पूर्ण

अटल __init पूर्णांक tick_broadcast_init_sysfs(व्योम)
अणु
	पूर्णांक err = device_रेजिस्टर(&tick_bc_dev);

	अगर (!err)
		err = device_create_file(&tick_bc_dev, &dev_attr_current_device);
	वापस err;
पूर्ण
#अन्यथा
अटल काष्ठा tick_device *tick_get_tick_dev(काष्ठा device *dev)
अणु
	वापस &per_cpu(tick_cpu_device, dev->id);
पूर्ण
अटल अंतरभूत पूर्णांक tick_broadcast_init_sysfs(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init tick_init_sysfs(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा device *dev = &per_cpu(tick_percpu_dev, cpu);
		पूर्णांक err;

		dev->id = cpu;
		dev->bus = &घड़ीevents_subsys;
		err = device_रेजिस्टर(dev);
		अगर (!err)
			err = device_create_file(dev, &dev_attr_current_device);
		अगर (!err)
			err = device_create_file(dev, &dev_attr_unbind_device);
		अगर (err)
			वापस err;
	पूर्ण
	वापस tick_broadcast_init_sysfs();
पूर्ण

अटल पूर्णांक __init घड़ीevents_init_sysfs(व्योम)
अणु
	पूर्णांक err = subsys_प्रणाली_रेजिस्टर(&घड़ीevents_subsys, शून्य);

	अगर (!err)
		err = tick_init_sysfs();
	वापस err;
पूर्ण
device_initcall(घड़ीevents_init_sysfs);
#पूर्ण_अगर /* SYSFS */
