<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains the base functions to manage periodic tick
 * related events.
 *
 * Copyright(C) 2005-2006, Thomas Gleixner <tglx@linutronix.de>
 * Copyright(C) 2005-2007, Red Hat, Inc., Ingo Molnar
 * Copyright(C) 2006-2007, Timesys Corp., Thomas Gleixner
 */
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/nmi.h>
#समावेश <linux/percpu.h>
#समावेश <linux/profile.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <trace/events/घातer.h>

#समावेश <यंत्र/irq_regs.h>

#समावेश "tick-internal.h"

/*
 * Tick devices
 */
DEFINE_PER_CPU(काष्ठा tick_device, tick_cpu_device);
/*
 * Tick next event: keeps track of the tick समय. It's updated by the
 * CPU which handles the tick and रक्षित by jअगरfies_lock. There is
 * no requirement to ग_लिखो hold the jअगरfies seqcount क्रम it.
 */
kसमय_प्रकार tick_next_period;

/*
 * tick_करो_समयr_cpu is a समयr core पूर्णांकernal variable which holds the CPU NR
 * which is responsible क्रम calling करो_समयr(), i.e. the समयkeeping stuff. This
 * variable has two functions:
 *
 * 1) Prevent a thundering herd issue of a gazillion of CPUs trying to grab the
 *    समयkeeping lock all at once. Only the CPU which is asचिन्हित to करो the
 *    update is handling it.
 *
 * 2) Hand off the duty in the NOHZ idle हाल by setting the value to
 *    TICK_DO_TIMER_NONE, i.e. a non existing CPU. So the next cpu which looks
 *    at it will take over and keep the समय keeping alive.  The hanकरोver
 *    procedure also covers cpu hotplug.
 */
पूर्णांक tick_करो_समयr_cpu __पढ़ो_mostly = TICK_DO_TIMER_BOOT;
#अगर_घोषित CONFIG_NO_HZ_FULL
/*
 * tick_करो_समयr_boot_cpu indicates the boot CPU temporarily owns
 * tick_करो_समयr_cpu and it should be taken over by an eligible secondary
 * when one comes online.
 */
अटल पूर्णांक tick_करो_समयr_boot_cpu __पढ़ो_mostly = -1;
#पूर्ण_अगर

/*
 * Debugging: see समयr_list.c
 */
काष्ठा tick_device *tick_get_device(पूर्णांक cpu)
अणु
	वापस &per_cpu(tick_cpu_device, cpu);
पूर्ण

/**
 * tick_is_oneshot_available - check क्रम a oneshot capable event device
 */
पूर्णांक tick_is_oneshot_available(व्योम)
अणु
	काष्ठा घड़ी_event_device *dev = __this_cpu_पढ़ो(tick_cpu_device.evtdev);

	अगर (!dev || !(dev->features & CLOCK_EVT_FEAT_ONESHOT))
		वापस 0;
	अगर (!(dev->features & CLOCK_EVT_FEAT_C3STOP))
		वापस 1;
	वापस tick_broadcast_oneshot_available();
पूर्ण

/*
 * Periodic tick
 */
अटल व्योम tick_periodic(पूर्णांक cpu)
अणु
	अगर (tick_करो_समयr_cpu == cpu) अणु
		raw_spin_lock(&jअगरfies_lock);
		ग_लिखो_seqcount_begin(&jअगरfies_seq);

		/* Keep track of the next tick event */
		tick_next_period = kसमय_add_ns(tick_next_period, TICK_NSEC);

		करो_समयr(1);
		ग_लिखो_seqcount_end(&jअगरfies_seq);
		raw_spin_unlock(&jअगरfies_lock);
		update_wall_समय();
	पूर्ण

	update_process_बार(user_mode(get_irq_regs()));
	profile_tick(CPU_PROFILING);
पूर्ण

/*
 * Event handler क्रम periodic ticks
 */
व्योम tick_handle_periodic(काष्ठा घड़ी_event_device *dev)
अणु
	पूर्णांक cpu = smp_processor_id();
	kसमय_प्रकार next = dev->next_event;

	tick_periodic(cpu);

#अगर defined(CONFIG_HIGH_RES_TIMERS) || defined(CONFIG_NO_HZ_COMMON)
	/*
	 * The cpu might have transitioned to HIGHRES or NOHZ mode via
	 * update_process_बार() -> run_local_समयrs() ->
	 * hrसमयr_run_queues().
	 */
	अगर (dev->event_handler != tick_handle_periodic)
		वापस;
#पूर्ण_अगर

	अगर (!घड़ीevent_state_oneshot(dev))
		वापस;
	क्रम (;;) अणु
		/*
		 * Setup the next period क्रम devices, which करो not have
		 * periodic mode:
		 */
		next = kसमय_add_ns(next, TICK_NSEC);

		अगर (!घड़ीevents_program_event(dev, next, false))
			वापस;
		/*
		 * Have to be careful here. If we're in oneshot mode,
		 * beक्रमe we call tick_periodic() in a loop, we need
		 * to be sure we're using a real hardware घड़ीsource.
		 * Otherwise we could get trapped in an infinite
		 * loop, as the tick_periodic() increments jअगरfies,
		 * which then will increment समय, possibly causing
		 * the loop to trigger again and again.
		 */
		अगर (समयkeeping_valid_क्रम_hres())
			tick_periodic(cpu);
	पूर्ण
पूर्ण

/*
 * Setup the device क्रम a periodic tick
 */
व्योम tick_setup_periodic(काष्ठा घड़ी_event_device *dev, पूर्णांक broadcast)
अणु
	tick_set_periodic_handler(dev, broadcast);

	/* Broadcast setup ? */
	अगर (!tick_device_is_functional(dev))
		वापस;

	अगर ((dev->features & CLOCK_EVT_FEAT_PERIODIC) &&
	    !tick_broadcast_oneshot_active()) अणु
		घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_PERIODIC);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक seq;
		kसमय_प्रकार next;

		करो अणु
			seq = पढ़ो_seqcount_begin(&jअगरfies_seq);
			next = tick_next_period;
		पूर्ण जबतक (पढ़ो_seqcount_retry(&jअगरfies_seq, seq));

		घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_ONESHOT);

		क्रम (;;) अणु
			अगर (!घड़ीevents_program_event(dev, next, false))
				वापस;
			next = kसमय_add_ns(next, TICK_NSEC);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_FULL
अटल व्योम giveup_करो_समयr(व्योम *info)
अणु
	पूर्णांक cpu = *(अचिन्हित पूर्णांक *)info;

	WARN_ON(tick_करो_समयr_cpu != smp_processor_id());

	tick_करो_समयr_cpu = cpu;
पूर्ण

अटल व्योम tick_take_करो_समयr_from_boot(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक from = tick_करो_समयr_boot_cpu;

	अगर (from >= 0 && from != cpu)
		smp_call_function_single(from, giveup_करो_समयr, &cpu, 1);
पूर्ण
#पूर्ण_अगर

/*
 * Setup the tick device
 */
अटल व्योम tick_setup_device(काष्ठा tick_device *td,
			      काष्ठा घड़ी_event_device *newdev, पूर्णांक cpu,
			      स्थिर काष्ठा cpumask *cpumask)
अणु
	व्योम (*handler)(काष्ठा घड़ी_event_device *) = शून्य;
	kसमय_प्रकार next_event = 0;

	/*
	 * First device setup ?
	 */
	अगर (!td->evtdev) अणु
		/*
		 * If no cpu took the करो_समयr update, assign it to
		 * this cpu:
		 */
		अगर (tick_करो_समयr_cpu == TICK_DO_TIMER_BOOT) अणु
			tick_करो_समयr_cpu = cpu;

			tick_next_period = kसमय_get();
#अगर_घोषित CONFIG_NO_HZ_FULL
			/*
			 * The boot CPU may be nohz_full, in which हाल set
			 * tick_करो_समयr_boot_cpu so the first housekeeping
			 * secondary that comes up will take करो_समयr from
			 * us.
			 */
			अगर (tick_nohz_full_cpu(cpu))
				tick_करो_समयr_boot_cpu = cpu;

		पूर्ण अन्यथा अगर (tick_करो_समयr_boot_cpu != -1 &&
						!tick_nohz_full_cpu(cpu)) अणु
			tick_take_करो_समयr_from_boot();
			tick_करो_समयr_boot_cpu = -1;
			WARN_ON(tick_करो_समयr_cpu != cpu);
#पूर्ण_अगर
		पूर्ण

		/*
		 * Startup in periodic mode first.
		 */
		td->mode = TICKDEV_MODE_PERIODIC;
	पूर्ण अन्यथा अणु
		handler = td->evtdev->event_handler;
		next_event = td->evtdev->next_event;
		td->evtdev->event_handler = घड़ीevents_handle_noop;
	पूर्ण

	td->evtdev = newdev;

	/*
	 * When the device is not per cpu, pin the पूर्णांकerrupt to the
	 * current cpu:
	 */
	अगर (!cpumask_equal(newdev->cpumask, cpumask))
		irq_set_affinity(newdev->irq, cpumask);

	/*
	 * When global broadcasting is active, check अगर the current
	 * device is रेजिस्टरed as a placeholder क्रम broadcast mode.
	 * This allows us to handle this x86 misfeature in a generic
	 * way. This function also वापसs !=0 when we keep the
	 * current active broadcast state क्रम this CPU.
	 */
	अगर (tick_device_uses_broadcast(newdev, cpu))
		वापस;

	अगर (td->mode == TICKDEV_MODE_PERIODIC)
		tick_setup_periodic(newdev, 0);
	अन्यथा
		tick_setup_oneshot(newdev, handler, next_event);
पूर्ण

व्योम tick_install_replacement(काष्ठा घड़ी_event_device *newdev)
अणु
	काष्ठा tick_device *td = this_cpu_ptr(&tick_cpu_device);
	पूर्णांक cpu = smp_processor_id();

	घड़ीevents_exchange_device(td->evtdev, newdev);
	tick_setup_device(td, newdev, cpu, cpumask_of(cpu));
	अगर (newdev->features & CLOCK_EVT_FEAT_ONESHOT)
		tick_oneshot_notअगरy();
पूर्ण

अटल bool tick_check_percpu(काष्ठा घड़ी_event_device *curdev,
			      काष्ठा घड़ी_event_device *newdev, पूर्णांक cpu)
अणु
	अगर (!cpumask_test_cpu(cpu, newdev->cpumask))
		वापस false;
	अगर (cpumask_equal(newdev->cpumask, cpumask_of(cpu)))
		वापस true;
	/* Check अगर irq affinity can be set */
	अगर (newdev->irq >= 0 && !irq_can_set_affinity(newdev->irq))
		वापस false;
	/* Prefer an existing cpu local device */
	अगर (curdev && cpumask_equal(curdev->cpumask, cpumask_of(cpu)))
		वापस false;
	वापस true;
पूर्ण

अटल bool tick_check_preferred(काष्ठा घड़ी_event_device *curdev,
				 काष्ठा घड़ी_event_device *newdev)
अणु
	/* Prefer oneshot capable device */
	अगर (!(newdev->features & CLOCK_EVT_FEAT_ONESHOT)) अणु
		अगर (curdev && (curdev->features & CLOCK_EVT_FEAT_ONESHOT))
			वापस false;
		अगर (tick_oneshot_mode_active())
			वापस false;
	पूर्ण

	/*
	 * Use the higher rated one, but prefer a CPU local device with a lower
	 * rating than a non-CPU local device
	 */
	वापस !curdev ||
		newdev->rating > curdev->rating ||
	       !cpumask_equal(curdev->cpumask, newdev->cpumask);
पूर्ण

/*
 * Check whether the new device is a better fit than curdev. curdev
 * can be शून्य !
 */
bool tick_check_replacement(काष्ठा घड़ी_event_device *curdev,
			    काष्ठा घड़ी_event_device *newdev)
अणु
	अगर (!tick_check_percpu(curdev, newdev, smp_processor_id()))
		वापस false;

	वापस tick_check_preferred(curdev, newdev);
पूर्ण

/*
 * Check, अगर the new रेजिस्टरed device should be used. Called with
 * घड़ीevents_lock held and पूर्णांकerrupts disabled.
 */
व्योम tick_check_new_device(काष्ठा घड़ी_event_device *newdev)
अणु
	काष्ठा घड़ी_event_device *curdev;
	काष्ठा tick_device *td;
	पूर्णांक cpu;

	cpu = smp_processor_id();
	td = &per_cpu(tick_cpu_device, cpu);
	curdev = td->evtdev;

	अगर (!tick_check_replacement(curdev, newdev))
		जाओ out_bc;

	अगर (!try_module_get(newdev->owner))
		वापस;

	/*
	 * Replace the eventually existing device by the new
	 * device. If the current device is the broadcast device, करो
	 * not give it back to the घड़ीevents layer !
	 */
	अगर (tick_is_broadcast_device(curdev)) अणु
		घड़ीevents_shutकरोwn(curdev);
		curdev = शून्य;
	पूर्ण
	घड़ीevents_exchange_device(curdev, newdev);
	tick_setup_device(td, newdev, cpu, cpumask_of(cpu));
	अगर (newdev->features & CLOCK_EVT_FEAT_ONESHOT)
		tick_oneshot_notअगरy();
	वापस;

out_bc:
	/*
	 * Can the new device be used as a broadcast device ?
	 */
	tick_install_broadcast_device(newdev);
पूर्ण

/**
 * tick_broadcast_oneshot_control - Enter/निकास broadcast oneshot mode
 * @state:	The target state (enter/निकास)
 *
 * The प्रणाली enters/leaves a state, where affected devices might stop
 * Returns 0 on success, -EBUSY अगर the cpu is used to broadcast wakeups.
 *
 * Called with पूर्णांकerrupts disabled, so घड़ीevents_lock is not
 * required here because the local घड़ी event device cannot go away
 * under us.
 */
पूर्णांक tick_broadcast_oneshot_control(क्रमागत tick_broadcast_state state)
अणु
	काष्ठा tick_device *td = this_cpu_ptr(&tick_cpu_device);

	अगर (!(td->evtdev->features & CLOCK_EVT_FEAT_C3STOP))
		वापस 0;

	वापस __tick_broadcast_oneshot_control(state);
पूर्ण
EXPORT_SYMBOL_GPL(tick_broadcast_oneshot_control);

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * Transfer the करो_समयr job away from a dying cpu.
 *
 * Called with पूर्णांकerrupts disabled. No locking required. If
 * tick_करो_समयr_cpu is owned by this cpu, nothing can change it.
 */
व्योम tick_hanकरोver_करो_समयr(व्योम)
अणु
	अगर (tick_करो_समयr_cpu == smp_processor_id())
		tick_करो_समयr_cpu = cpumask_first(cpu_online_mask);
पूर्ण

/*
 * Shutकरोwn an event device on a given cpu:
 *
 * This is called on a lअगरe CPU, when a CPU is dead. So we cannot
 * access the hardware device itself.
 * We just set the mode and हटाओ it from the lists.
 */
व्योम tick_shutकरोwn(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा tick_device *td = &per_cpu(tick_cpu_device, cpu);
	काष्ठा घड़ी_event_device *dev = td->evtdev;

	td->mode = TICKDEV_MODE_PERIODIC;
	अगर (dev) अणु
		/*
		 * Prevent that the घड़ी events layer tries to call
		 * the set mode function!
		 */
		घड़ीevent_set_state(dev, CLOCK_EVT_STATE_DETACHED);
		घड़ीevents_exchange_device(dev, शून्य);
		dev->event_handler = घड़ीevents_handle_noop;
		td->evtdev = शून्य;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * tick_suspend_local - Suspend the local tick device
 *
 * Called from the local cpu क्रम मुक्तze with पूर्णांकerrupts disabled.
 *
 * No locks required. Nothing can change the per cpu device.
 */
व्योम tick_suspend_local(व्योम)
अणु
	काष्ठा tick_device *td = this_cpu_ptr(&tick_cpu_device);

	घड़ीevents_shutकरोwn(td->evtdev);
पूर्ण

/**
 * tick_resume_local - Resume the local tick device
 *
 * Called from the local CPU क्रम unमुक्तze or XEN resume magic.
 *
 * No locks required. Nothing can change the per cpu device.
 */
व्योम tick_resume_local(व्योम)
अणु
	काष्ठा tick_device *td = this_cpu_ptr(&tick_cpu_device);
	bool broadcast = tick_resume_check_broadcast();

	घड़ीevents_tick_resume(td->evtdev);
	अगर (!broadcast) अणु
		अगर (td->mode == TICKDEV_MODE_PERIODIC)
			tick_setup_periodic(td->evtdev, 0);
		अन्यथा
			tick_resume_oneshot();
	पूर्ण
पूर्ण

/**
 * tick_suspend - Suspend the tick and the broadcast device
 *
 * Called from syscore_suspend() via समयkeeping_suspend with only one
 * CPU online and पूर्णांकerrupts disabled or from tick_unमुक्तze() under
 * tick_मुक्तze_lock.
 *
 * No locks required. Nothing can change the per cpu device.
 */
व्योम tick_suspend(व्योम)
अणु
	tick_suspend_local();
	tick_suspend_broadcast();
पूर्ण

/**
 * tick_resume - Resume the tick and the broadcast device
 *
 * Called from syscore_resume() via समयkeeping_resume with only one
 * CPU online and पूर्णांकerrupts disabled.
 *
 * No locks required. Nothing can change the per cpu device.
 */
व्योम tick_resume(व्योम)
अणु
	tick_resume_broadcast();
	tick_resume_local();
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
अटल DEFINE_RAW_SPINLOCK(tick_मुक्तze_lock);
अटल अचिन्हित पूर्णांक tick_मुक्तze_depth;

/**
 * tick_मुक्तze - Suspend the local tick and (possibly) समयkeeping.
 *
 * Check अगर this is the last online CPU executing the function and अगर so,
 * suspend समयkeeping.  Otherwise suspend the local tick.
 *
 * Call with पूर्णांकerrupts disabled.  Must be balanced with %tick_unमुक्तze().
 * Interrupts must not be enabled beक्रमe the subsequent %tick_unमुक्तze().
 */
व्योम tick_मुक्तze(व्योम)
अणु
	raw_spin_lock(&tick_मुक्तze_lock);

	tick_मुक्तze_depth++;
	अगर (tick_मुक्तze_depth == num_online_cpus()) अणु
		trace_suspend_resume(TPS("timekeeping_freeze"),
				     smp_processor_id(), true);
		प्रणाली_state = SYSTEM_SUSPEND;
		sched_घड़ी_suspend();
		समयkeeping_suspend();
	पूर्ण अन्यथा अणु
		tick_suspend_local();
	पूर्ण

	raw_spin_unlock(&tick_मुक्तze_lock);
पूर्ण

/**
 * tick_unमुक्तze - Resume the local tick and (possibly) समयkeeping.
 *
 * Check अगर this is the first CPU executing the function and अगर so, resume
 * समयkeeping.  Otherwise resume the local tick.
 *
 * Call with पूर्णांकerrupts disabled.  Must be balanced with %tick_मुक्तze().
 * Interrupts must not be enabled after the preceding %tick_मुक्तze().
 */
व्योम tick_unमुक्तze(व्योम)
अणु
	raw_spin_lock(&tick_मुक्तze_lock);

	अगर (tick_मुक्तze_depth == num_online_cpus()) अणु
		समयkeeping_resume();
		sched_घड़ी_resume();
		प्रणाली_state = SYSTEM_RUNNING;
		trace_suspend_resume(TPS("timekeeping_freeze"),
				     smp_processor_id(), false);
	पूर्ण अन्यथा अणु
		touch_softlockup_watchकरोg();
		tick_resume_local();
	पूर्ण

	tick_मुक्तze_depth--;

	raw_spin_unlock(&tick_मुक्तze_lock);
पूर्ण
#पूर्ण_अगर /* CONFIG_SUSPEND */

/**
 * tick_init - initialize the tick control
 */
व्योम __init tick_init(व्योम)
अणु
	tick_broadcast_init();
	tick_nohz_init();
पूर्ण
