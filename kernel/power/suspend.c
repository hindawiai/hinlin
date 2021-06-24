<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/घातer/suspend.c - Suspend to RAM and standby functionality.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 * Copyright (c) 2009 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 */

#घोषणा pr_fmt(fmt) "PM: " fmt

#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/sरुको.h>
#समावेश <linux/ftrace.h>
#समावेश <trace/events/घातer.h>
#समावेश <linux/compiler.h>
#समावेश <linux/moduleparam.h>

#समावेश "power.h"

स्थिर अक्षर * स्थिर pm_labels[] = अणु
	[PM_SUSPEND_TO_IDLE] = "freeze",
	[PM_SUSPEND_STANDBY] = "standby",
	[PM_SUSPEND_MEM] = "mem",
पूर्ण;
स्थिर अक्षर *pm_states[PM_SUSPEND_MAX];
अटल स्थिर अक्षर * स्थिर mem_sleep_labels[] = अणु
	[PM_SUSPEND_TO_IDLE] = "s2idle",
	[PM_SUSPEND_STANDBY] = "shallow",
	[PM_SUSPEND_MEM] = "deep",
पूर्ण;
स्थिर अक्षर *mem_sleep_states[PM_SUSPEND_MAX];

suspend_state_t mem_sleep_current = PM_SUSPEND_TO_IDLE;
suspend_state_t mem_sleep_शेष = PM_SUSPEND_MAX;
suspend_state_t pm_suspend_target_state;
EXPORT_SYMBOL_GPL(pm_suspend_target_state);

अचिन्हित पूर्णांक pm_suspend_global_flags;
EXPORT_SYMBOL_GPL(pm_suspend_global_flags);

अटल स्थिर काष्ठा platक्रमm_suspend_ops *suspend_ops;
अटल स्थिर काष्ठा platक्रमm_s2idle_ops *s2idle_ops;
अटल DECLARE_SWAIT_QUEUE_HEAD(s2idle_रुको_head);

क्रमागत s2idle_states __पढ़ो_mostly s2idle_state;
अटल DEFINE_RAW_SPINLOCK(s2idle_lock);

/**
 * pm_suspend_शेष_s2idle - Check अगर suspend-to-idle is the शेष suspend.
 *
 * Return 'true' अगर suspend-to-idle has been selected as the शेष प्रणाली
 * suspend method.
 */
bool pm_suspend_शेष_s2idle(व्योम)
अणु
	वापस mem_sleep_current == PM_SUSPEND_TO_IDLE;
पूर्ण
EXPORT_SYMBOL_GPL(pm_suspend_शेष_s2idle);

व्योम s2idle_set_ops(स्थिर काष्ठा platक्रमm_s2idle_ops *ops)
अणु
	lock_प्रणाली_sleep();
	s2idle_ops = ops;
	unlock_प्रणाली_sleep();
पूर्ण

अटल व्योम s2idle_begin(व्योम)
अणु
	s2idle_state = S2IDLE_STATE_NONE;
पूर्ण

अटल व्योम s2idle_enter(व्योम)
अणु
	trace_suspend_resume(TPS("machine_suspend"), PM_SUSPEND_TO_IDLE, true);

	raw_spin_lock_irq(&s2idle_lock);
	अगर (pm_wakeup_pending())
		जाओ out;

	s2idle_state = S2IDLE_STATE_ENTER;
	raw_spin_unlock_irq(&s2idle_lock);

	get_online_cpus();
	cpuidle_resume();

	/* Push all the CPUs पूर्णांकo the idle loop. */
	wake_up_all_idle_cpus();
	/* Make the current CPU रुको so it can enter the idle loop too. */
	sरुको_event_exclusive(s2idle_रुको_head,
		    s2idle_state == S2IDLE_STATE_WAKE);

	cpuidle_छोड़ो();
	put_online_cpus();

	raw_spin_lock_irq(&s2idle_lock);

 out:
	s2idle_state = S2IDLE_STATE_NONE;
	raw_spin_unlock_irq(&s2idle_lock);

	trace_suspend_resume(TPS("machine_suspend"), PM_SUSPEND_TO_IDLE, false);
पूर्ण

अटल व्योम s2idle_loop(व्योम)
अणु
	pm_pr_dbg("suspend-to-idle\n");

	/*
	 * Suspend-to-idle equals:
	 * frozen processes + suspended devices + idle processors.
	 * Thus s2idle_enter() should be called right after all devices have
	 * been suspended.
	 *
	 * Wakeups during the noirq suspend of devices may be spurious, so try
	 * to aव्योम them upfront.
	 */
	क्रम (;;) अणु
		अगर (s2idle_ops && s2idle_ops->wake) अणु
			अगर (s2idle_ops->wake())
				अवरोध;
		पूर्ण अन्यथा अगर (pm_wakeup_pending()) अणु
			अवरोध;
		पूर्ण

		pm_wakeup_clear(false);

		s2idle_enter();
	पूर्ण

	pm_pr_dbg("resume from suspend-to-idle\n");
पूर्ण

व्योम s2idle_wake(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&s2idle_lock, flags);
	अगर (s2idle_state > S2IDLE_STATE_NONE) अणु
		s2idle_state = S2IDLE_STATE_WAKE;
		swake_up_one(&s2idle_रुको_head);
	पूर्ण
	raw_spin_unlock_irqrestore(&s2idle_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(s2idle_wake);

अटल bool valid_state(suspend_state_t state)
अणु
	/*
	 * PM_SUSPEND_STANDBY and PM_SUSPEND_MEM states need low level
	 * support and need to be valid to the low level
	 * implementation, no valid callback implies that none are valid.
	 */
	वापस suspend_ops && suspend_ops->valid && suspend_ops->valid(state);
पूर्ण

व्योम __init pm_states_init(व्योम)
अणु
	/* "mem" and "freeze" are always present in /sys/घातer/state. */
	pm_states[PM_SUSPEND_MEM] = pm_labels[PM_SUSPEND_MEM];
	pm_states[PM_SUSPEND_TO_IDLE] = pm_labels[PM_SUSPEND_TO_IDLE];
	/*
	 * Suspend-to-idle should be supported even without any suspend_ops,
	 * initialize mem_sleep_states[] accordingly here.
	 */
	mem_sleep_states[PM_SUSPEND_TO_IDLE] = mem_sleep_labels[PM_SUSPEND_TO_IDLE];
पूर्ण

अटल पूर्णांक __init mem_sleep_शेष_setup(अक्षर *str)
अणु
	suspend_state_t state;

	क्रम (state = PM_SUSPEND_TO_IDLE; state <= PM_SUSPEND_MEM; state++)
		अगर (mem_sleep_labels[state] &&
		    !म_भेद(str, mem_sleep_labels[state])) अणु
			mem_sleep_शेष = state;
			अवरोध;
		पूर्ण

	वापस 1;
पूर्ण
__setup("mem_sleep_default=", mem_sleep_शेष_setup);

/**
 * suspend_set_ops - Set the global suspend method table.
 * @ops: Suspend operations to use.
 */
व्योम suspend_set_ops(स्थिर काष्ठा platक्रमm_suspend_ops *ops)
अणु
	lock_प्रणाली_sleep();

	suspend_ops = ops;

	अगर (valid_state(PM_SUSPEND_STANDBY)) अणु
		mem_sleep_states[PM_SUSPEND_STANDBY] = mem_sleep_labels[PM_SUSPEND_STANDBY];
		pm_states[PM_SUSPEND_STANDBY] = pm_labels[PM_SUSPEND_STANDBY];
		अगर (mem_sleep_शेष == PM_SUSPEND_STANDBY)
			mem_sleep_current = PM_SUSPEND_STANDBY;
	पूर्ण
	अगर (valid_state(PM_SUSPEND_MEM)) अणु
		mem_sleep_states[PM_SUSPEND_MEM] = mem_sleep_labels[PM_SUSPEND_MEM];
		अगर (mem_sleep_शेष >= PM_SUSPEND_MEM)
			mem_sleep_current = PM_SUSPEND_MEM;
	पूर्ण

	unlock_प्रणाली_sleep();
पूर्ण
EXPORT_SYMBOL_GPL(suspend_set_ops);

/**
 * suspend_valid_only_mem - Generic memory-only valid callback.
 * @state: Target प्रणाली sleep state.
 *
 * Platक्रमm drivers that implement mem suspend only and only need to check क्रम
 * that in their .valid() callback can use this instead of rolling their own
 * .valid() callback.
 */
पूर्णांक suspend_valid_only_mem(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_MEM;
पूर्ण
EXPORT_SYMBOL_GPL(suspend_valid_only_mem);

अटल bool sleep_state_supported(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_TO_IDLE || (suspend_ops && suspend_ops->enter);
पूर्ण

अटल पूर्णांक platक्रमm_suspend_prepare(suspend_state_t state)
अणु
	वापस state != PM_SUSPEND_TO_IDLE && suspend_ops->prepare ?
		suspend_ops->prepare() : 0;
पूर्ण

अटल पूर्णांक platक्रमm_suspend_prepare_late(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_TO_IDLE && s2idle_ops && s2idle_ops->prepare ?
		s2idle_ops->prepare() : 0;
पूर्ण

अटल पूर्णांक platक्रमm_suspend_prepare_noirq(suspend_state_t state)
अणु
	अगर (state == PM_SUSPEND_TO_IDLE)
		वापस s2idle_ops && s2idle_ops->prepare_late ?
			s2idle_ops->prepare_late() : 0;

	वापस suspend_ops->prepare_late ? suspend_ops->prepare_late() : 0;
पूर्ण

अटल व्योम platक्रमm_resume_noirq(suspend_state_t state)
अणु
	अगर (state == PM_SUSPEND_TO_IDLE) अणु
		अगर (s2idle_ops && s2idle_ops->restore_early)
			s2idle_ops->restore_early();
	पूर्ण अन्यथा अगर (suspend_ops->wake) अणु
		suspend_ops->wake();
	पूर्ण
पूर्ण

अटल व्योम platक्रमm_resume_early(suspend_state_t state)
अणु
	अगर (state == PM_SUSPEND_TO_IDLE && s2idle_ops && s2idle_ops->restore)
		s2idle_ops->restore();
पूर्ण

अटल व्योम platक्रमm_resume_finish(suspend_state_t state)
अणु
	अगर (state != PM_SUSPEND_TO_IDLE && suspend_ops->finish)
		suspend_ops->finish();
पूर्ण

अटल पूर्णांक platक्रमm_suspend_begin(suspend_state_t state)
अणु
	अगर (state == PM_SUSPEND_TO_IDLE && s2idle_ops && s2idle_ops->begin)
		वापस s2idle_ops->begin();
	अन्यथा अगर (suspend_ops && suspend_ops->begin)
		वापस suspend_ops->begin(state);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम platक्रमm_resume_end(suspend_state_t state)
अणु
	अगर (state == PM_SUSPEND_TO_IDLE && s2idle_ops && s2idle_ops->end)
		s2idle_ops->end();
	अन्यथा अगर (suspend_ops && suspend_ops->end)
		suspend_ops->end();
पूर्ण

अटल व्योम platक्रमm_recover(suspend_state_t state)
अणु
	अगर (state != PM_SUSPEND_TO_IDLE && suspend_ops->recover)
		suspend_ops->recover();
पूर्ण

अटल bool platक्रमm_suspend_again(suspend_state_t state)
अणु
	वापस state != PM_SUSPEND_TO_IDLE && suspend_ops->suspend_again ?
		suspend_ops->suspend_again() : false;
पूर्ण

#अगर_घोषित CONFIG_PM_DEBUG
अटल अचिन्हित पूर्णांक pm_test_delay = 5;
module_param(pm_test_delay, uपूर्णांक, 0644);
MODULE_PARM_DESC(pm_test_delay,
		 "Number of seconds to wait before resuming from suspend test");
#पूर्ण_अगर

अटल पूर्णांक suspend_test(पूर्णांक level)
अणु
#अगर_घोषित CONFIG_PM_DEBUG
	अगर (pm_test_level == level) अणु
		pr_info("suspend debug: Waiting for %d second(s).\n",
				pm_test_delay);
		mdelay(pm_test_delay * 1000);
		वापस 1;
	पूर्ण
#पूर्ण_अगर /* !CONFIG_PM_DEBUG */
	वापस 0;
पूर्ण

/**
 * suspend_prepare - Prepare क्रम entering प्रणाली sleep state.
 * @state: Target प्रणाली sleep state.
 *
 * Common code run क्रम every प्रणाली sleep state that can be entered (except क्रम
 * hibernation).  Run suspend notअगरiers, allocate the "suspend" console and
 * मुक्तze processes.
 */
अटल पूर्णांक suspend_prepare(suspend_state_t state)
अणु
	पूर्णांक error;

	अगर (!sleep_state_supported(state))
		वापस -EPERM;

	pm_prepare_console();

	error = pm_notअगरier_call_chain_robust(PM_SUSPEND_PREPARE, PM_POST_SUSPEND);
	अगर (error)
		जाओ Restore;

	trace_suspend_resume(TPS("freeze_processes"), 0, true);
	error = suspend_मुक्तze_processes();
	trace_suspend_resume(TPS("freeze_processes"), 0, false);
	अगर (!error)
		वापस 0;

	suspend_stats.failed_मुक्तze++;
	dpm_save_failed_step(SUSPEND_FREEZE);
	pm_notअगरier_call_chain(PM_POST_SUSPEND);
 Restore:
	pm_restore_console();
	वापस error;
पूर्ण

/* शेष implementation */
व्योम __weak arch_suspend_disable_irqs(व्योम)
अणु
	local_irq_disable();
पूर्ण

/* शेष implementation */
व्योम __weak arch_suspend_enable_irqs(व्योम)
अणु
	local_irq_enable();
पूर्ण

/**
 * suspend_enter - Make the प्रणाली enter the given sleep state.
 * @state: System sleep state to enter.
 * @wakeup: Returns inक्रमmation that the sleep state should not be re-entered.
 *
 * This function should be called after devices have been suspended.
 */
अटल पूर्णांक suspend_enter(suspend_state_t state, bool *wakeup)
अणु
	पूर्णांक error;

	error = platक्रमm_suspend_prepare(state);
	अगर (error)
		जाओ Platक्रमm_finish;

	error = dpm_suspend_late(PMSG_SUSPEND);
	अगर (error) अणु
		pr_err("late suspend of devices failed\n");
		जाओ Platक्रमm_finish;
	पूर्ण
	error = platक्रमm_suspend_prepare_late(state);
	अगर (error)
		जाओ Devices_early_resume;

	error = dpm_suspend_noirq(PMSG_SUSPEND);
	अगर (error) अणु
		pr_err("noirq suspend of devices failed\n");
		जाओ Platक्रमm_early_resume;
	पूर्ण
	error = platक्रमm_suspend_prepare_noirq(state);
	अगर (error)
		जाओ Platक्रमm_wake;

	अगर (suspend_test(TEST_PLATFORM))
		जाओ Platक्रमm_wake;

	अगर (state == PM_SUSPEND_TO_IDLE) अणु
		s2idle_loop();
		जाओ Platक्रमm_wake;
	पूर्ण

	error = suspend_disable_secondary_cpus();
	अगर (error || suspend_test(TEST_CPUS))
		जाओ Enable_cpus;

	arch_suspend_disable_irqs();
	BUG_ON(!irqs_disabled());

	प्रणाली_state = SYSTEM_SUSPEND;

	error = syscore_suspend();
	अगर (!error) अणु
		*wakeup = pm_wakeup_pending();
		अगर (!(suspend_test(TEST_CORE) || *wakeup)) अणु
			trace_suspend_resume(TPS("machine_suspend"),
				state, true);
			error = suspend_ops->enter(state);
			trace_suspend_resume(TPS("machine_suspend"),
				state, false);
		पूर्ण अन्यथा अगर (*wakeup) अणु
			error = -EBUSY;
		पूर्ण
		syscore_resume();
	पूर्ण

	प्रणाली_state = SYSTEM_RUNNING;

	arch_suspend_enable_irqs();
	BUG_ON(irqs_disabled());

 Enable_cpus:
	suspend_enable_secondary_cpus();

 Platक्रमm_wake:
	platक्रमm_resume_noirq(state);
	dpm_resume_noirq(PMSG_RESUME);

 Platक्रमm_early_resume:
	platक्रमm_resume_early(state);

 Devices_early_resume:
	dpm_resume_early(PMSG_RESUME);

 Platक्रमm_finish:
	platक्रमm_resume_finish(state);
	वापस error;
पूर्ण

/**
 * suspend_devices_and_enter - Suspend devices and enter प्रणाली sleep state.
 * @state: System sleep state to enter.
 */
पूर्णांक suspend_devices_and_enter(suspend_state_t state)
अणु
	पूर्णांक error;
	bool wakeup = false;

	अगर (!sleep_state_supported(state))
		वापस -ENOSYS;

	pm_suspend_target_state = state;

	अगर (state == PM_SUSPEND_TO_IDLE)
		pm_set_suspend_no_platक्रमm();

	error = platक्रमm_suspend_begin(state);
	अगर (error)
		जाओ Close;

	suspend_console();
	suspend_test_start();
	error = dpm_suspend_start(PMSG_SUSPEND);
	अगर (error) अणु
		pr_err("Some devices failed to suspend, or early wake event detected\n");
		जाओ Recover_platक्रमm;
	पूर्ण
	suspend_test_finish("suspend devices");
	अगर (suspend_test(TEST_DEVICES))
		जाओ Recover_platक्रमm;

	करो अणु
		error = suspend_enter(state, &wakeup);
	पूर्ण जबतक (!error && !wakeup && platक्रमm_suspend_again(state));

 Resume_devices:
	suspend_test_start();
	dpm_resume_end(PMSG_RESUME);
	suspend_test_finish("resume devices");
	trace_suspend_resume(TPS("resume_console"), state, true);
	resume_console();
	trace_suspend_resume(TPS("resume_console"), state, false);

 Close:
	platक्रमm_resume_end(state);
	pm_suspend_target_state = PM_SUSPEND_ON;
	वापस error;

 Recover_platक्रमm:
	platक्रमm_recover(state);
	जाओ Resume_devices;
पूर्ण

/**
 * suspend_finish - Clean up beक्रमe finishing the suspend sequence.
 *
 * Call platक्रमm code to clean up, restart processes, and मुक्त the console that
 * we've allocated. This routine is not called क्रम hibernation.
 */
अटल व्योम suspend_finish(व्योम)
अणु
	suspend_thaw_processes();
	pm_notअगरier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
पूर्ण

/**
 * enter_state - Do common work needed to enter प्रणाली sleep state.
 * @state: System sleep state to enter.
 *
 * Make sure that no one अन्यथा is trying to put the प्रणाली पूर्णांकo a sleep state.
 * Fail अगर that's not the हाल.  Otherwise, prepare क्रम प्रणाली suspend, make the
 * प्रणाली enter the given sleep state and clean up after wakeup.
 */
अटल पूर्णांक enter_state(suspend_state_t state)
अणु
	पूर्णांक error;

	trace_suspend_resume(TPS("suspend_enter"), state, true);
	अगर (state == PM_SUSPEND_TO_IDLE) अणु
#अगर_घोषित CONFIG_PM_DEBUG
		अगर (pm_test_level != TEST_NONE && pm_test_level <= TEST_CPUS) अणु
			pr_warn("Unsupported test mode for suspend to idle, please choose none/freezer/devices/platform.\n");
			वापस -EAGAIN;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (!valid_state(state)) अणु
		वापस -EINVAL;
	पूर्ण
	अगर (!mutex_trylock(&प्रणाली_transition_mutex))
		वापस -EBUSY;

	अगर (state == PM_SUSPEND_TO_IDLE)
		s2idle_begin();

	अगर (sync_on_suspend_enabled) अणु
		trace_suspend_resume(TPS("sync_filesystems"), 0, true);
		ksys_sync_helper();
		trace_suspend_resume(TPS("sync_filesystems"), 0, false);
	पूर्ण

	pm_pr_dbg("Preparing system for sleep (%s)\n", mem_sleep_labels[state]);
	pm_suspend_clear_flags();
	error = suspend_prepare(state);
	अगर (error)
		जाओ Unlock;

	अगर (suspend_test(TEST_FREEZER))
		जाओ Finish;

	trace_suspend_resume(TPS("suspend_enter"), state, false);
	pm_pr_dbg("Suspending system (%s)\n", mem_sleep_labels[state]);
	pm_restrict_gfp_mask();
	error = suspend_devices_and_enter(state);
	pm_restore_gfp_mask();

 Finish:
	events_check_enabled = false;
	pm_pr_dbg("Finishing wakeup.\n");
	suspend_finish();
 Unlock:
	mutex_unlock(&प्रणाली_transition_mutex);
	वापस error;
पूर्ण

/**
 * pm_suspend - Externally visible function क्रम suspending the प्रणाली.
 * @state: System sleep state to enter.
 *
 * Check अगर the value of @state represents one of the supported states,
 * execute enter_state() and update प्रणाली suspend statistics.
 */
पूर्णांक pm_suspend(suspend_state_t state)
अणु
	पूर्णांक error;

	अगर (state <= PM_SUSPEND_ON || state >= PM_SUSPEND_MAX)
		वापस -EINVAL;

	pr_info("suspend entry (%s)\n", mem_sleep_labels[state]);
	error = enter_state(state);
	अगर (error) अणु
		suspend_stats.fail++;
		dpm_save_failed_त्रुटि_सं(error);
	पूर्ण अन्यथा अणु
		suspend_stats.success++;
	पूर्ण
	pr_info("suspend exit\n");
	वापस error;
पूर्ण
EXPORT_SYMBOL(pm_suspend);
