<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains functions which emulate a local घड़ी-event
 * device via a broadcast event source.
 *
 * Copyright(C) 2005-2006, Thomas Gleixner <tglx@linutronix.de>
 * Copyright(C) 2005-2007, Red Hat, Inc., Ingo Molnar
 * Copyright(C) 2006-2007, Timesys Corp., Thomas Gleixner
 */
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/profile.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/module.h>

#समावेश "tick-internal.h"

/*
 * Broadcast support क्रम broken x86 hardware, where the local apic
 * समयr stops in C3 state.
 */

अटल काष्ठा tick_device tick_broadcast_device;
अटल cpumask_var_t tick_broadcast_mask __cpumask_var_पढ़ो_mostly;
अटल cpumask_var_t tick_broadcast_on __cpumask_var_पढ़ो_mostly;
अटल cpumask_var_t पंचांगpmask __cpumask_var_पढ़ो_mostly;
अटल पूर्णांक tick_broadcast_क्रमced;

अटल __cacheline_aligned_in_smp DEFINE_RAW_SPINLOCK(tick_broadcast_lock);

#अगर_घोषित CONFIG_TICK_ONESHOT
अटल व्योम tick_broadcast_setup_oneshot(काष्ठा घड़ी_event_device *bc);
अटल व्योम tick_broadcast_clear_oneshot(पूर्णांक cpu);
अटल व्योम tick_resume_broadcast_oneshot(काष्ठा घड़ी_event_device *bc);
# अगरdef CONFIG_HOTPLUG_CPU
अटल व्योम tick_broadcast_oneshot_offline(अचिन्हित पूर्णांक cpu);
# endअगर
#अन्यथा
अटल अंतरभूत व्योम tick_broadcast_setup_oneshot(काष्ठा घड़ी_event_device *bc) अणु BUG(); पूर्ण
अटल अंतरभूत व्योम tick_broadcast_clear_oneshot(पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम tick_resume_broadcast_oneshot(काष्ठा घड़ी_event_device *bc) अणु पूर्ण
# अगरdef CONFIG_HOTPLUG_CPU
अटल अंतरभूत व्योम tick_broadcast_oneshot_offline(अचिन्हित पूर्णांक cpu) अणु पूर्ण
# endअगर
#पूर्ण_अगर

/*
 * Debugging: see समयr_list.c
 */
काष्ठा tick_device *tick_get_broadcast_device(व्योम)
अणु
	वापस &tick_broadcast_device;
पूर्ण

काष्ठा cpumask *tick_get_broadcast_mask(व्योम)
अणु
	वापस tick_broadcast_mask;
पूर्ण

/*
 * Start the device in periodic mode
 */
अटल व्योम tick_broadcast_start_periodic(काष्ठा घड़ी_event_device *bc)
अणु
	अगर (bc)
		tick_setup_periodic(bc, 1);
पूर्ण

/*
 * Check, अगर the device can be utilized as broadcast device:
 */
अटल bool tick_check_broadcast_device(काष्ठा घड़ी_event_device *curdev,
					काष्ठा घड़ी_event_device *newdev)
अणु
	अगर ((newdev->features & CLOCK_EVT_FEAT_DUMMY) ||
	    (newdev->features & CLOCK_EVT_FEAT_PERCPU) ||
	    (newdev->features & CLOCK_EVT_FEAT_C3STOP))
		वापस false;

	अगर (tick_broadcast_device.mode == TICKDEV_MODE_ONESHOT &&
	    !(newdev->features & CLOCK_EVT_FEAT_ONESHOT))
		वापस false;

	वापस !curdev || newdev->rating > curdev->rating;
पूर्ण

/*
 * Conditionally install/replace broadcast device
 */
व्योम tick_install_broadcast_device(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा घड़ी_event_device *cur = tick_broadcast_device.evtdev;

	अगर (!tick_check_broadcast_device(cur, dev))
		वापस;

	अगर (!try_module_get(dev->owner))
		वापस;

	घड़ीevents_exchange_device(cur, dev);
	अगर (cur)
		cur->event_handler = घड़ीevents_handle_noop;
	tick_broadcast_device.evtdev = dev;
	अगर (!cpumask_empty(tick_broadcast_mask))
		tick_broadcast_start_periodic(dev);

	अगर (!(dev->features & CLOCK_EVT_FEAT_ONESHOT))
		वापस;

	/*
	 * If the प्रणाली alपढ़ोy runs in oneshot mode, चयन the newly
	 * रेजिस्टरed broadcast device to oneshot mode explicitly.
	 */
	अगर (tick_broadcast_oneshot_active()) अणु
		tick_broadcast_चयन_to_oneshot();
		वापस;
	पूर्ण

	/*
	 * Inक्रमm all cpus about this. We might be in a situation
	 * where we did not चयन to oneshot mode because the per cpu
	 * devices are affected by CLOCK_EVT_FEAT_C3STOP and the lack
	 * of a oneshot capable broadcast device. Without that
	 * notअगरication the प्रणालीs stays stuck in periodic mode
	 * क्रमever.
	 */
	tick_घड़ी_notअगरy();
पूर्ण

/*
 * Check, अगर the device is the broadcast device
 */
पूर्णांक tick_is_broadcast_device(काष्ठा घड़ी_event_device *dev)
अणु
	वापस (dev && tick_broadcast_device.evtdev == dev);
पूर्ण

पूर्णांक tick_broadcast_update_freq(काष्ठा घड़ी_event_device *dev, u32 freq)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (tick_is_broadcast_device(dev)) अणु
		raw_spin_lock(&tick_broadcast_lock);
		ret = __घड़ीevents_update_freq(dev, freq);
		raw_spin_unlock(&tick_broadcast_lock);
	पूर्ण
	वापस ret;
पूर्ण


अटल व्योम err_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
	pr_crit_once("Failed to broadcast timer tick. Some CPUs may be unresponsive.\n");
पूर्ण

अटल व्योम tick_device_setup_broadcast_func(काष्ठा घड़ी_event_device *dev)
अणु
	अगर (!dev->broadcast)
		dev->broadcast = tick_broadcast;
	अगर (!dev->broadcast) अणु
		pr_warn_once("%s depends on broadcast, but no broadcast function available\n",
			     dev->name);
		dev->broadcast = err_broadcast;
	पूर्ण
पूर्ण

/*
 * Check, अगर the device is dysfunctional and a placeholder, which
 * needs to be handled by the broadcast device.
 */
पूर्णांक tick_device_uses_broadcast(काष्ठा घड़ी_event_device *dev, पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *bc = tick_broadcast_device.evtdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	raw_spin_lock_irqsave(&tick_broadcast_lock, flags);

	/*
	 * Devices might be रेजिस्टरed with both periodic and oneshot
	 * mode disabled. This संकेतs, that the device needs to be
	 * operated from the broadcast device and is a placeholder क्रम
	 * the cpu local device.
	 */
	अगर (!tick_device_is_functional(dev)) अणु
		dev->event_handler = tick_handle_periodic;
		tick_device_setup_broadcast_func(dev);
		cpumask_set_cpu(cpu, tick_broadcast_mask);
		अगर (tick_broadcast_device.mode == TICKDEV_MODE_PERIODIC)
			tick_broadcast_start_periodic(bc);
		अन्यथा
			tick_broadcast_setup_oneshot(bc);
		ret = 1;
	पूर्ण अन्यथा अणु
		/*
		 * Clear the broadcast bit क्रम this cpu अगर the
		 * device is not घातer state affected.
		 */
		अगर (!(dev->features & CLOCK_EVT_FEAT_C3STOP))
			cpumask_clear_cpu(cpu, tick_broadcast_mask);
		अन्यथा
			tick_device_setup_broadcast_func(dev);

		/*
		 * Clear the broadcast bit अगर the CPU is not in
		 * periodic broadcast on state.
		 */
		अगर (!cpumask_test_cpu(cpu, tick_broadcast_on))
			cpumask_clear_cpu(cpu, tick_broadcast_mask);

		चयन (tick_broadcast_device.mode) अणु
		हाल TICKDEV_MODE_ONESHOT:
			/*
			 * If the प्रणाली is in oneshot mode we can
			 * unconditionally clear the oneshot mask bit,
			 * because the CPU is running and thereक्रमe
			 * not in an idle state which causes the घातer
			 * state affected device to stop. Let the
			 * caller initialize the device.
			 */
			tick_broadcast_clear_oneshot(cpu);
			ret = 0;
			अवरोध;

		हाल TICKDEV_MODE_PERIODIC:
			/*
			 * If the प्रणाली is in periodic mode, check
			 * whether the broadcast device can be
			 * चयनed off now.
			 */
			अगर (cpumask_empty(tick_broadcast_mask) && bc)
				घड़ीevents_shutकरोwn(bc);
			/*
			 * If we kept the cpu in the broadcast mask,
			 * tell the caller to leave the per cpu device
			 * in shutकरोwn state. The periodic पूर्णांकerrupt
			 * is delivered by the broadcast device, अगर
			 * the broadcast device exists and is not
			 * hrसमयr based.
			 */
			अगर (bc && !(bc->features & CLOCK_EVT_FEAT_HRTIMER))
				ret = cpumask_test_cpu(cpu, tick_broadcast_mask);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&tick_broadcast_lock, flags);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
पूर्णांक tick_receive_broadcast(व्योम)
अणु
	काष्ठा tick_device *td = this_cpu_ptr(&tick_cpu_device);
	काष्ठा घड़ी_event_device *evt = td->evtdev;

	अगर (!evt)
		वापस -ENODEV;

	अगर (!evt->event_handler)
		वापस -EINVAL;

	evt->event_handler(evt);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Broadcast the event to the cpus, which are set in the mask (mangled).
 */
अटल bool tick_करो_broadcast(काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा tick_device *td;
	bool local = false;

	/*
	 * Check, अगर the current cpu is in the mask
	 */
	अगर (cpumask_test_cpu(cpu, mask)) अणु
		काष्ठा घड़ी_event_device *bc = tick_broadcast_device.evtdev;

		cpumask_clear_cpu(cpu, mask);
		/*
		 * We only run the local handler, अगर the broadcast
		 * device is not hrसमयr based. Otherwise we run पूर्णांकo
		 * a hrसमयr recursion.
		 *
		 * local समयr_पूर्णांकerrupt()
		 *   local_handler()
		 *     expire_hrसमयrs()
		 *       bc_handler()
		 *         local_handler()
		 *	     expire_hrसमयrs()
		 */
		local = !(bc->features & CLOCK_EVT_FEAT_HRTIMER);
	पूर्ण

	अगर (!cpumask_empty(mask)) अणु
		/*
		 * It might be necessary to actually check whether the devices
		 * have dअगरferent broadcast functions. For now, just use the
		 * one of the first device. This works as दीर्घ as we have this
		 * misfeature only on x86 (lapic)
		 */
		td = &per_cpu(tick_cpu_device, cpumask_first(mask));
		td->evtdev->broadcast(mask);
	पूर्ण
	वापस local;
पूर्ण

/*
 * Periodic broadcast:
 * - invoke the broadcast handlers
 */
अटल bool tick_करो_periodic_broadcast(व्योम)
अणु
	cpumask_and(पंचांगpmask, cpu_online_mask, tick_broadcast_mask);
	वापस tick_करो_broadcast(पंचांगpmask);
पूर्ण

/*
 * Event handler क्रम periodic broadcast ticks
 */
अटल व्योम tick_handle_periodic_broadcast(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा tick_device *td = this_cpu_ptr(&tick_cpu_device);
	bool bc_local;

	raw_spin_lock(&tick_broadcast_lock);

	/* Handle spurious पूर्णांकerrupts gracefully */
	अगर (घड़ीevent_state_shutकरोwn(tick_broadcast_device.evtdev)) अणु
		raw_spin_unlock(&tick_broadcast_lock);
		वापस;
	पूर्ण

	bc_local = tick_करो_periodic_broadcast();

	अगर (घड़ीevent_state_oneshot(dev)) अणु
		kसमय_प्रकार next = kसमय_add_ns(dev->next_event, TICK_NSEC);

		घड़ीevents_program_event(dev, next, true);
	पूर्ण
	raw_spin_unlock(&tick_broadcast_lock);

	/*
	 * We run the handler of the local cpu after dropping
	 * tick_broadcast_lock because the handler might deadlock when
	 * trying to चयन to oneshot mode.
	 */
	अगर (bc_local)
		td->evtdev->event_handler(td->evtdev);
पूर्ण

/**
 * tick_broadcast_control - Enable/disable or क्रमce broadcast mode
 * @mode:	The selected broadcast mode
 *
 * Called when the प्रणाली enters a state where affected tick devices
 * might stop. Note: TICK_BROADCAST_FORCE cannot be unकरोne.
 */
व्योम tick_broadcast_control(क्रमागत tick_broadcast_mode mode)
अणु
	काष्ठा घड़ी_event_device *bc, *dev;
	काष्ठा tick_device *td;
	पूर्णांक cpu, bc_stopped;
	अचिन्हित दीर्घ flags;

	/* Protects also the local घड़ीevent device. */
	raw_spin_lock_irqsave(&tick_broadcast_lock, flags);
	td = this_cpu_ptr(&tick_cpu_device);
	dev = td->evtdev;

	/*
	 * Is the device not affected by the घातerstate ?
	 */
	अगर (!dev || !(dev->features & CLOCK_EVT_FEAT_C3STOP))
		जाओ out;

	अगर (!tick_device_is_functional(dev))
		जाओ out;

	cpu = smp_processor_id();
	bc = tick_broadcast_device.evtdev;
	bc_stopped = cpumask_empty(tick_broadcast_mask);

	चयन (mode) अणु
	हाल TICK_BROADCAST_FORCE:
		tick_broadcast_क्रमced = 1;
		fallthrough;
	हाल TICK_BROADCAST_ON:
		cpumask_set_cpu(cpu, tick_broadcast_on);
		अगर (!cpumask_test_and_set_cpu(cpu, tick_broadcast_mask)) अणु
			/*
			 * Only shutकरोwn the cpu local device, अगर:
			 *
			 * - the broadcast device exists
			 * - the broadcast device is not a hrसमयr based one
			 * - the broadcast device is in periodic mode to
			 *   aव्योम a hiccup during चयन to oneshot mode
			 */
			अगर (bc && !(bc->features & CLOCK_EVT_FEAT_HRTIMER) &&
			    tick_broadcast_device.mode == TICKDEV_MODE_PERIODIC)
				घड़ीevents_shutकरोwn(dev);
		पूर्ण
		अवरोध;

	हाल TICK_BROADCAST_OFF:
		अगर (tick_broadcast_क्रमced)
			अवरोध;
		cpumask_clear_cpu(cpu, tick_broadcast_on);
		अगर (cpumask_test_and_clear_cpu(cpu, tick_broadcast_mask)) अणु
			अगर (tick_broadcast_device.mode ==
			    TICKDEV_MODE_PERIODIC)
				tick_setup_periodic(dev, 0);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (bc) अणु
		अगर (cpumask_empty(tick_broadcast_mask)) अणु
			अगर (!bc_stopped)
				घड़ीevents_shutकरोwn(bc);
		पूर्ण अन्यथा अगर (bc_stopped) अणु
			अगर (tick_broadcast_device.mode == TICKDEV_MODE_PERIODIC)
				tick_broadcast_start_periodic(bc);
			अन्यथा
				tick_broadcast_setup_oneshot(bc);
		पूर्ण
	पूर्ण
out:
	raw_spin_unlock_irqrestore(&tick_broadcast_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(tick_broadcast_control);

/*
 * Set the periodic handler depending on broadcast on/off
 */
व्योम tick_set_periodic_handler(काष्ठा घड़ी_event_device *dev, पूर्णांक broadcast)
अणु
	अगर (!broadcast)
		dev->event_handler = tick_handle_periodic;
	अन्यथा
		dev->event_handler = tick_handle_periodic_broadcast;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम tick_shutकरोwn_broadcast(व्योम)
अणु
	काष्ठा घड़ी_event_device *bc = tick_broadcast_device.evtdev;

	अगर (tick_broadcast_device.mode == TICKDEV_MODE_PERIODIC) अणु
		अगर (bc && cpumask_empty(tick_broadcast_mask))
			घड़ीevents_shutकरोwn(bc);
	पूर्ण
पूर्ण

/*
 * Remove a CPU from broadcasting
 */
व्योम tick_broadcast_offline(अचिन्हित पूर्णांक cpu)
अणु
	raw_spin_lock(&tick_broadcast_lock);
	cpumask_clear_cpu(cpu, tick_broadcast_mask);
	cpumask_clear_cpu(cpu, tick_broadcast_on);
	tick_broadcast_oneshot_offline(cpu);
	tick_shutकरोwn_broadcast();
	raw_spin_unlock(&tick_broadcast_lock);
पूर्ण

#पूर्ण_अगर

व्योम tick_suspend_broadcast(व्योम)
अणु
	काष्ठा घड़ी_event_device *bc;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tick_broadcast_lock, flags);

	bc = tick_broadcast_device.evtdev;
	अगर (bc)
		घड़ीevents_shutकरोwn(bc);

	raw_spin_unlock_irqrestore(&tick_broadcast_lock, flags);
पूर्ण

/*
 * This is called from tick_resume_local() on a resuming CPU. That's
 * called from the core resume function, tick_unमुक्तze() and the magic XEN
 * resume hackery.
 *
 * In none of these हालs the broadcast device mode can change and the
 * bit of the resuming CPU in the broadcast mask is safe as well.
 */
bool tick_resume_check_broadcast(व्योम)
अणु
	अगर (tick_broadcast_device.mode == TICKDEV_MODE_ONESHOT)
		वापस false;
	अन्यथा
		वापस cpumask_test_cpu(smp_processor_id(), tick_broadcast_mask);
पूर्ण

व्योम tick_resume_broadcast(व्योम)
अणु
	काष्ठा घड़ी_event_device *bc;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tick_broadcast_lock, flags);

	bc = tick_broadcast_device.evtdev;

	अगर (bc) अणु
		घड़ीevents_tick_resume(bc);

		चयन (tick_broadcast_device.mode) अणु
		हाल TICKDEV_MODE_PERIODIC:
			अगर (!cpumask_empty(tick_broadcast_mask))
				tick_broadcast_start_periodic(bc);
			अवरोध;
		हाल TICKDEV_MODE_ONESHOT:
			अगर (!cpumask_empty(tick_broadcast_mask))
				tick_resume_broadcast_oneshot(bc);
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&tick_broadcast_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_TICK_ONESHOT

अटल cpumask_var_t tick_broadcast_oneshot_mask __cpumask_var_पढ़ो_mostly;
अटल cpumask_var_t tick_broadcast_pending_mask __cpumask_var_पढ़ो_mostly;
अटल cpumask_var_t tick_broadcast_क्रमce_mask __cpumask_var_पढ़ो_mostly;

/*
 * Exposed क्रम debugging: see समयr_list.c
 */
काष्ठा cpumask *tick_get_broadcast_oneshot_mask(व्योम)
अणु
	वापस tick_broadcast_oneshot_mask;
पूर्ण

/*
 * Called beक्रमe going idle with पूर्णांकerrupts disabled. Checks whether a
 * broadcast event from the other core is about to happen. We detected
 * that in tick_broadcast_oneshot_control(). The callsite can use this
 * to aव्योम a deep idle transition as we are about to get the
 * broadcast IPI right away.
 */
पूर्णांक tick_check_broadcast_expired(व्योम)
अणु
	वापस cpumask_test_cpu(smp_processor_id(), tick_broadcast_क्रमce_mask);
पूर्ण

/*
 * Set broadcast पूर्णांकerrupt affinity
 */
अटल व्योम tick_broadcast_set_affinity(काष्ठा घड़ी_event_device *bc,
					स्थिर काष्ठा cpumask *cpumask)
अणु
	अगर (!(bc->features & CLOCK_EVT_FEAT_DYNIRQ))
		वापस;

	अगर (cpumask_equal(bc->cpumask, cpumask))
		वापस;

	bc->cpumask = cpumask;
	irq_set_affinity(bc->irq, bc->cpumask);
पूर्ण

अटल व्योम tick_broadcast_set_event(काष्ठा घड़ी_event_device *bc, पूर्णांक cpu,
				     kसमय_प्रकार expires)
अणु
	अगर (!घड़ीevent_state_oneshot(bc))
		घड़ीevents_चयन_state(bc, CLOCK_EVT_STATE_ONESHOT);

	घड़ीevents_program_event(bc, expires, 1);
	tick_broadcast_set_affinity(bc, cpumask_of(cpu));
पूर्ण

अटल व्योम tick_resume_broadcast_oneshot(काष्ठा घड़ी_event_device *bc)
अणु
	घड़ीevents_चयन_state(bc, CLOCK_EVT_STATE_ONESHOT);
पूर्ण

/*
 * Called from irq_enter() when idle was पूर्णांकerrupted to reenable the
 * per cpu device.
 */
व्योम tick_check_oneshot_broadcast_this_cpu(व्योम)
अणु
	अगर (cpumask_test_cpu(smp_processor_id(), tick_broadcast_oneshot_mask)) अणु
		काष्ठा tick_device *td = this_cpu_ptr(&tick_cpu_device);

		/*
		 * We might be in the middle of चयनing over from
		 * periodic to oneshot. If the CPU has not yet
		 * चयनed over, leave the device alone.
		 */
		अगर (td->mode == TICKDEV_MODE_ONESHOT) अणु
			घड़ीevents_चयन_state(td->evtdev,
					      CLOCK_EVT_STATE_ONESHOT);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Handle oneshot mode broadcasting
 */
अटल व्योम tick_handle_oneshot_broadcast(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा tick_device *td;
	kसमय_प्रकार now, next_event;
	पूर्णांक cpu, next_cpu = 0;
	bool bc_local;

	raw_spin_lock(&tick_broadcast_lock);
	dev->next_event = KTIME_MAX;
	next_event = KTIME_MAX;
	cpumask_clear(पंचांगpmask);
	now = kसमय_get();
	/* Find all expired events */
	क्रम_each_cpu(cpu, tick_broadcast_oneshot_mask) अणु
		/*
		 * Required क्रम !SMP because क्रम_each_cpu() reports
		 * unconditionally CPU0 as set on UP kernels.
		 */
		अगर (!IS_ENABLED(CONFIG_SMP) &&
		    cpumask_empty(tick_broadcast_oneshot_mask))
			अवरोध;

		td = &per_cpu(tick_cpu_device, cpu);
		अगर (td->evtdev->next_event <= now) अणु
			cpumask_set_cpu(cpu, पंचांगpmask);
			/*
			 * Mark the remote cpu in the pending mask, so
			 * it can aव्योम reprogramming the cpu local
			 * समयr in tick_broadcast_oneshot_control().
			 */
			cpumask_set_cpu(cpu, tick_broadcast_pending_mask);
		पूर्ण अन्यथा अगर (td->evtdev->next_event < next_event) अणु
			next_event = td->evtdev->next_event;
			next_cpu = cpu;
		पूर्ण
	पूर्ण

	/*
	 * Remove the current cpu from the pending mask. The event is
	 * delivered immediately in tick_करो_broadcast() !
	 */
	cpumask_clear_cpu(smp_processor_id(), tick_broadcast_pending_mask);

	/* Take care of enक्रमced broadcast requests */
	cpumask_or(पंचांगpmask, पंचांगpmask, tick_broadcast_क्रमce_mask);
	cpumask_clear(tick_broadcast_क्रमce_mask);

	/*
	 * Sanity check. Catch the हाल where we try to broadcast to
	 * offline cpus.
	 */
	अगर (WARN_ON_ONCE(!cpumask_subset(पंचांगpmask, cpu_online_mask)))
		cpumask_and(पंचांगpmask, पंचांगpmask, cpu_online_mask);

	/*
	 * Wakeup the cpus which have an expired event.
	 */
	bc_local = tick_करो_broadcast(पंचांगpmask);

	/*
	 * Two reasons क्रम reprogram:
	 *
	 * - The global event did not expire any CPU local
	 * events. This happens in dyntick mode, as the maximum PIT
	 * delta is quite small.
	 *
	 * - There are pending events on sleeping CPUs which were not
	 * in the event mask
	 */
	अगर (next_event != KTIME_MAX)
		tick_broadcast_set_event(dev, next_cpu, next_event);

	raw_spin_unlock(&tick_broadcast_lock);

	अगर (bc_local) अणु
		td = this_cpu_ptr(&tick_cpu_device);
		td->evtdev->event_handler(td->evtdev);
	पूर्ण
पूर्ण

अटल पूर्णांक broadcast_needs_cpu(काष्ठा घड़ी_event_device *bc, पूर्णांक cpu)
अणु
	अगर (!(bc->features & CLOCK_EVT_FEAT_HRTIMER))
		वापस 0;
	अगर (bc->next_event == KTIME_MAX)
		वापस 0;
	वापस bc->bound_on == cpu ? -EBUSY : 0;
पूर्ण

अटल व्योम broadcast_shutकरोwn_local(काष्ठा घड़ी_event_device *bc,
				     काष्ठा घड़ी_event_device *dev)
अणु
	/*
	 * For hrसमयr based broadcasting we cannot shutकरोwn the cpu
	 * local device अगर our own event is the first one to expire or
	 * अगर we own the broadcast समयr.
	 */
	अगर (bc->features & CLOCK_EVT_FEAT_HRTIMER) अणु
		अगर (broadcast_needs_cpu(bc, smp_processor_id()))
			वापस;
		अगर (dev->next_event < bc->next_event)
			वापस;
	पूर्ण
	घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_SHUTDOWN);
पूर्ण

पूर्णांक __tick_broadcast_oneshot_control(क्रमागत tick_broadcast_state state)
अणु
	काष्ठा घड़ी_event_device *bc, *dev;
	पूर्णांक cpu, ret = 0;
	kसमय_प्रकार now;

	/*
	 * If there is no broadcast device, tell the caller not to go
	 * पूर्णांकo deep idle.
	 */
	अगर (!tick_broadcast_device.evtdev)
		वापस -EBUSY;

	dev = this_cpu_ptr(&tick_cpu_device)->evtdev;

	raw_spin_lock(&tick_broadcast_lock);
	bc = tick_broadcast_device.evtdev;
	cpu = smp_processor_id();

	अगर (state == TICK_BROADCAST_ENTER) अणु
		/*
		 * If the current CPU owns the hrसमयr broadcast
		 * mechanism, it cannot go deep idle and we करो not add
		 * the CPU to the broadcast mask. We करोn't have to go
		 * through the EXIT path as the local समयr is not
		 * shutकरोwn.
		 */
		ret = broadcast_needs_cpu(bc, cpu);
		अगर (ret)
			जाओ out;

		/*
		 * If the broadcast device is in periodic mode, we
		 * वापस.
		 */
		अगर (tick_broadcast_device.mode == TICKDEV_MODE_PERIODIC) अणु
			/* If it is a hrसमयr based broadcast, वापस busy */
			अगर (bc->features & CLOCK_EVT_FEAT_HRTIMER)
				ret = -EBUSY;
			जाओ out;
		पूर्ण

		अगर (!cpumask_test_and_set_cpu(cpu, tick_broadcast_oneshot_mask)) अणु
			WARN_ON_ONCE(cpumask_test_cpu(cpu, tick_broadcast_pending_mask));

			/* Conditionally shut करोwn the local समयr. */
			broadcast_shutकरोwn_local(bc, dev);

			/*
			 * We only reprogram the broadcast समयr अगर we
			 * did not mark ourself in the क्रमce mask and
			 * अगर the cpu local event is earlier than the
			 * broadcast event. If the current CPU is in
			 * the क्रमce mask, then we are going to be
			 * woken by the IPI right away; we वापस
			 * busy, so the CPU करोes not try to go deep
			 * idle.
			 */
			अगर (cpumask_test_cpu(cpu, tick_broadcast_क्रमce_mask)) अणु
				ret = -EBUSY;
			पूर्ण अन्यथा अगर (dev->next_event < bc->next_event) अणु
				tick_broadcast_set_event(bc, cpu, dev->next_event);
				/*
				 * In हाल of hrसमयr broadcasts the
				 * programming might have moved the
				 * समयr to this cpu. If yes, हटाओ
				 * us from the broadcast mask and
				 * वापस busy.
				 */
				ret = broadcast_needs_cpu(bc, cpu);
				अगर (ret) अणु
					cpumask_clear_cpu(cpu,
						tick_broadcast_oneshot_mask);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cpumask_test_and_clear_cpu(cpu, tick_broadcast_oneshot_mask)) अणु
			घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_ONESHOT);
			/*
			 * The cpu which was handling the broadcast
			 * समयr marked this cpu in the broadcast
			 * pending mask and fired the broadcast
			 * IPI. So we are going to handle the expired
			 * event anyway via the broadcast IPI
			 * handler. No need to reprogram the समयr
			 * with an alपढ़ोy expired event.
			 */
			अगर (cpumask_test_and_clear_cpu(cpu,
				       tick_broadcast_pending_mask))
				जाओ out;

			/*
			 * Bail out अगर there is no next event.
			 */
			अगर (dev->next_event == KTIME_MAX)
				जाओ out;
			/*
			 * If the pending bit is not set, then we are
			 * either the CPU handling the broadcast
			 * पूर्णांकerrupt or we got woken by something अन्यथा.
			 *
			 * We are no दीर्घer in the broadcast mask, so
			 * अगर the cpu local expiry समय is alपढ़ोy
			 * reached, we would reprogram the cpu local
			 * समयr with an alपढ़ोy expired event.
			 *
			 * This can lead to a ping-pong when we वापस
			 * to idle and thereक्रमe rearm the broadcast
			 * समयr beक्रमe the cpu local समयr was able
			 * to fire. This happens because the क्रमced
			 * reprogramming makes sure that the event
			 * will happen in the future and depending on
			 * the min_delta setting this might be far
			 * enough out that the ping-pong starts.
			 *
			 * If the cpu local next_event has expired
			 * then we know that the broadcast समयr
			 * next_event has expired as well and
			 * broadcast is about to be handled. So we
			 * aव्योम reprogramming and enक्रमce that the
			 * broadcast handler, which did not run yet,
			 * will invoke the cpu local handler.
			 *
			 * We cannot call the handler directly from
			 * here, because we might be in a NOHZ phase
			 * and we did not go through the irq_enter()
			 * nohz fixups.
			 */
			now = kसमय_get();
			अगर (dev->next_event <= now) अणु
				cpumask_set_cpu(cpu, tick_broadcast_क्रमce_mask);
				जाओ out;
			पूर्ण
			/*
			 * We got woken by something अन्यथा. Reprogram
			 * the cpu local समयr device.
			 */
			tick_program_event(dev->next_event, 1);
		पूर्ण
	पूर्ण
out:
	raw_spin_unlock(&tick_broadcast_lock);
	वापस ret;
पूर्ण

/*
 * Reset the one shot broadcast क्रम a cpu
 *
 * Called with tick_broadcast_lock held
 */
अटल व्योम tick_broadcast_clear_oneshot(पूर्णांक cpu)
अणु
	cpumask_clear_cpu(cpu, tick_broadcast_oneshot_mask);
	cpumask_clear_cpu(cpu, tick_broadcast_pending_mask);
पूर्ण

अटल व्योम tick_broadcast_init_next_event(काष्ठा cpumask *mask,
					   kसमय_प्रकार expires)
अणु
	काष्ठा tick_device *td;
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
		td = &per_cpu(tick_cpu_device, cpu);
		अगर (td->evtdev)
			td->evtdev->next_event = expires;
	पूर्ण
पूर्ण

अटल अंतरभूत kसमय_प्रकार tick_get_next_period(व्योम)
अणु
	kसमय_प्रकार next;

	/*
	 * Protect against concurrent updates (store /load tearing on
	 * 32bit). It करोes not matter अगर the समय is alपढ़ोy in the
	 * past. The broadcast device which is about to be programmed will
	 * fire in any हाल.
	 */
	raw_spin_lock(&jअगरfies_lock);
	next = tick_next_period;
	raw_spin_unlock(&jअगरfies_lock);
	वापस next;
पूर्ण

/**
 * tick_broadcast_setup_oneshot - setup the broadcast device
 */
अटल व्योम tick_broadcast_setup_oneshot(काष्ठा घड़ी_event_device *bc)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (!bc)
		वापस;

	/* Set it up only once ! */
	अगर (bc->event_handler != tick_handle_oneshot_broadcast) अणु
		पूर्णांक was_periodic = घड़ीevent_state_periodic(bc);

		bc->event_handler = tick_handle_oneshot_broadcast;

		/*
		 * We must be careful here. There might be other CPUs
		 * रुकोing क्रम periodic broadcast. We need to set the
		 * oneshot_mask bits क्रम those and program the
		 * broadcast device to fire.
		 */
		cpumask_copy(पंचांगpmask, tick_broadcast_mask);
		cpumask_clear_cpu(cpu, पंचांगpmask);
		cpumask_or(tick_broadcast_oneshot_mask,
			   tick_broadcast_oneshot_mask, पंचांगpmask);

		अगर (was_periodic && !cpumask_empty(पंचांगpmask)) अणु
			kसमय_प्रकार nextevt = tick_get_next_period();

			घड़ीevents_चयन_state(bc, CLOCK_EVT_STATE_ONESHOT);
			tick_broadcast_init_next_event(पंचांगpmask, nextevt);
			tick_broadcast_set_event(bc, cpu, nextevt);
		पूर्ण अन्यथा
			bc->next_event = KTIME_MAX;
	पूर्ण अन्यथा अणु
		/*
		 * The first cpu which चयनes to oneshot mode sets
		 * the bit क्रम all other cpus which are in the general
		 * (periodic) broadcast mask. So the bit is set and
		 * would prevent the first broadcast enter after this
		 * to program the bc device.
		 */
		tick_broadcast_clear_oneshot(cpu);
	पूर्ण
पूर्ण

/*
 * Select oneshot operating mode क्रम the broadcast device
 */
व्योम tick_broadcast_चयन_to_oneshot(व्योम)
अणु
	काष्ठा घड़ी_event_device *bc;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tick_broadcast_lock, flags);

	tick_broadcast_device.mode = TICKDEV_MODE_ONESHOT;
	bc = tick_broadcast_device.evtdev;
	अगर (bc)
		tick_broadcast_setup_oneshot(bc);

	raw_spin_unlock_irqrestore(&tick_broadcast_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम hotplug_cpu__broadcast_tick_pull(पूर्णांक deadcpu)
अणु
	काष्ठा घड़ी_event_device *bc;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&tick_broadcast_lock, flags);
	bc = tick_broadcast_device.evtdev;

	अगर (bc && broadcast_needs_cpu(bc, deadcpu)) अणु
		/* This moves the broadcast assignment to this CPU: */
		घड़ीevents_program_event(bc, bc->next_event, 1);
	पूर्ण
	raw_spin_unlock_irqrestore(&tick_broadcast_lock, flags);
पूर्ण

/*
 * Remove a dying CPU from broadcasting
 */
अटल व्योम tick_broadcast_oneshot_offline(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Clear the broadcast masks क्रम the dead cpu, but करो not stop
	 * the broadcast device!
	 */
	cpumask_clear_cpu(cpu, tick_broadcast_oneshot_mask);
	cpumask_clear_cpu(cpu, tick_broadcast_pending_mask);
	cpumask_clear_cpu(cpu, tick_broadcast_क्रमce_mask);
पूर्ण
#पूर्ण_अगर

/*
 * Check, whether the broadcast device is in one shot mode
 */
पूर्णांक tick_broadcast_oneshot_active(व्योम)
अणु
	वापस tick_broadcast_device.mode == TICKDEV_MODE_ONESHOT;
पूर्ण

/*
 * Check whether the broadcast device supports oneshot.
 */
bool tick_broadcast_oneshot_available(व्योम)
अणु
	काष्ठा घड़ी_event_device *bc = tick_broadcast_device.evtdev;

	वापस bc ? bc->features & CLOCK_EVT_FEAT_ONESHOT : false;
पूर्ण

#अन्यथा
पूर्णांक __tick_broadcast_oneshot_control(क्रमागत tick_broadcast_state state)
अणु
	काष्ठा घड़ी_event_device *bc = tick_broadcast_device.evtdev;

	अगर (!bc || (bc->features & CLOCK_EVT_FEAT_HRTIMER))
		वापस -EBUSY;

	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __init tick_broadcast_init(व्योम)
अणु
	zalloc_cpumask_var(&tick_broadcast_mask, GFP_NOWAIT);
	zalloc_cpumask_var(&tick_broadcast_on, GFP_NOWAIT);
	zalloc_cpumask_var(&पंचांगpmask, GFP_NOWAIT);
#अगर_घोषित CONFIG_TICK_ONESHOT
	zalloc_cpumask_var(&tick_broadcast_oneshot_mask, GFP_NOWAIT);
	zalloc_cpumask_var(&tick_broadcast_pending_mask, GFP_NOWAIT);
	zalloc_cpumask_var(&tick_broadcast_क्रमce_mask, GFP_NOWAIT);
#पूर्ण_अगर
पूर्ण
