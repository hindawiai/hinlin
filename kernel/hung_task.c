<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Detect Hung Task
 *
 * kernel/hung_task.c - kernel thपढ़ो क्रम detecting tasks stuck in D state
 *
 */

#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/nmi.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/export.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/suspend.h>
#समावेश <linux/utsname.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/sysctl.h>

#समावेश <trace/events/sched.h>

/*
 * The number of tasks checked:
 */
पूर्णांक __पढ़ो_mostly sysctl_hung_task_check_count = PID_MAX_LIMIT;

/*
 * Limit number of tasks checked in a batch.
 *
 * This value controls the preemptibility of khungtaskd since preemption
 * is disabled during the critical section. It also controls the size of
 * the RCU grace period. So it needs to be upper-bound.
 */
#घोषणा HUNG_TASK_LOCK_BREAK (HZ / 10)

/*
 * Zero means infinite समयout - no checking करोne:
 */
अचिन्हित दीर्घ __पढ़ो_mostly sysctl_hung_task_समयout_secs = CONFIG_DEFAULT_HUNG_TASK_TIMEOUT;

/*
 * Zero (शेष value) means use sysctl_hung_task_समयout_secs:
 */
अचिन्हित दीर्घ __पढ़ो_mostly sysctl_hung_task_check_पूर्णांकerval_secs;

पूर्णांक __पढ़ो_mostly sysctl_hung_task_warnings = 10;

अटल पूर्णांक __पढ़ो_mostly did_panic;
अटल bool hung_task_show_lock;
अटल bool hung_task_call_panic;
अटल bool hung_task_show_all_bt;

अटल काष्ठा task_काष्ठा *watchकरोg_task;

#अगर_घोषित CONFIG_SMP
/*
 * Should we dump all CPUs backtraces in a hung task event?
 * Defaults to 0, can be changed via sysctl.
 */
अचिन्हित पूर्णांक __पढ़ो_mostly sysctl_hung_task_all_cpu_backtrace;
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Should we panic (and reboot, अगर panic_समयout= is set) when a
 * hung task is detected:
 */
अचिन्हित पूर्णांक __पढ़ो_mostly sysctl_hung_task_panic =
				CONFIG_BOOTPARAM_HUNG_TASK_PANIC_VALUE;

अटल पूर्णांक
hung_task_panic(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	did_panic = 1;

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block panic_block = अणु
	.notअगरier_call = hung_task_panic,
पूर्ण;

अटल व्योम check_hung_task(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ चयन_count = t->nvcsw + t->nivcsw;

	/*
	 * Ensure the task is not frozen.
	 * Also, skip vविभाजन and any other user process that मुक्तzer should skip.
	 */
	अगर (unlikely(t->flags & (PF_FROZEN | PF_FREEZER_SKIP)))
	    वापस;

	/*
	 * When a freshly created task is scheduled once, changes its state to
	 * TASK_UNINTERRUPTIBLE without having ever been चयनed out once, it
	 * musn't be checked.
	 */
	अगर (unlikely(!चयन_count))
		वापस;

	अगर (चयन_count != t->last_चयन_count) अणु
		t->last_चयन_count = चयन_count;
		t->last_चयन_समय = jअगरfies;
		वापस;
	पूर्ण
	अगर (समय_is_after_jअगरfies(t->last_चयन_समय + समयout * HZ))
		वापस;

	trace_sched_process_hang(t);

	अगर (sysctl_hung_task_panic) अणु
		console_verbose();
		hung_task_show_lock = true;
		hung_task_call_panic = true;
	पूर्ण

	/*
	 * Ok, the task did not get scheduled क्रम more than 2 minutes,
	 * complain:
	 */
	अगर (sysctl_hung_task_warnings) अणु
		अगर (sysctl_hung_task_warnings > 0)
			sysctl_hung_task_warnings--;
		pr_err("INFO: task %s:%d blocked for more than %ld seconds.\n",
		       t->comm, t->pid, (jअगरfies - t->last_चयन_समय) / HZ);
		pr_err("      %s %s %.*s\n",
			prपूर्णांक_taपूर्णांकed(), init_utsname()->release,
			(पूर्णांक)म_खोज(init_utsname()->version, " "),
			init_utsname()->version);
		pr_err("\"echo 0 > /proc/sys/kernel/hung_task_timeout_secs\""
			" disables this message.\n");
		sched_show_task(t);
		hung_task_show_lock = true;

		अगर (sysctl_hung_task_all_cpu_backtrace)
			hung_task_show_all_bt = true;
	पूर्ण

	touch_nmi_watchकरोg();
पूर्ण

/*
 * To aव्योम extending the RCU grace period क्रम an unbounded amount of समय,
 * periodically निकास the critical section and enter a new one.
 *
 * For preemptible RCU it is sufficient to call rcu_पढ़ो_unlock in order
 * to निकास the grace period. For classic RCU, a reschedule is required.
 */
अटल bool rcu_lock_अवरोध(काष्ठा task_काष्ठा *g, काष्ठा task_काष्ठा *t)
अणु
	bool can_cont;

	get_task_काष्ठा(g);
	get_task_काष्ठा(t);
	rcu_पढ़ो_unlock();
	cond_resched();
	rcu_पढ़ो_lock();
	can_cont = pid_alive(g) && pid_alive(t);
	put_task_काष्ठा(t);
	put_task_काष्ठा(g);

	वापस can_cont;
पूर्ण

/*
 * Check whether a TASK_UNINTERRUPTIBLE करोes not get woken up क्रम
 * a really दीर्घ समय (120 seconds). If that happens, prपूर्णांक out
 * a warning.
 */
अटल व्योम check_hung_unपूर्णांकerruptible_tasks(अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक max_count = sysctl_hung_task_check_count;
	अचिन्हित दीर्घ last_अवरोध = jअगरfies;
	काष्ठा task_काष्ठा *g, *t;

	/*
	 * If the प्रणाली crashed alपढ़ोy then all bets are off,
	 * करो not report extra hung tasks:
	 */
	अगर (test_taपूर्णांक(TAINT_DIE) || did_panic)
		वापस;

	hung_task_show_lock = false;
	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(g, t) अणु
		अगर (!max_count--)
			जाओ unlock;
		अगर (समय_after(jअगरfies, last_अवरोध + HUNG_TASK_LOCK_BREAK)) अणु
			अगर (!rcu_lock_अवरोध(g, t))
				जाओ unlock;
			last_अवरोध = jअगरfies;
		पूर्ण
		/* use "==" to skip the TASK_KILLABLE tasks रुकोing on NFS */
		अगर (t->state == TASK_UNINTERRUPTIBLE)
			check_hung_task(t, समयout);
	पूर्ण
 unlock:
	rcu_पढ़ो_unlock();
	अगर (hung_task_show_lock)
		debug_show_all_locks();

	अगर (hung_task_show_all_bt) अणु
		hung_task_show_all_bt = false;
		trigger_all_cpu_backtrace();
	पूर्ण

	अगर (hung_task_call_panic)
		panic("hung_task: blocked tasks");
पूर्ण

अटल दीर्घ hung_समयout_jअगरfies(अचिन्हित दीर्घ last_checked,
				 अचिन्हित दीर्घ समयout)
अणु
	/* समयout of 0 will disable the watchकरोg */
	वापस समयout ? last_checked - jअगरfies + समयout * HZ :
		MAX_SCHEDULE_TIMEOUT;
पूर्ण

/*
 * Process updating of समयout sysctl
 */
पूर्णांक proc_करोhung_task_समयout_secs(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	अगर (ret || !ग_लिखो)
		जाओ out;

	wake_up_process(watchकरोg_task);

 out:
	वापस ret;
पूर्ण

अटल atomic_t reset_hung_task = ATOMIC_INIT(0);

व्योम reset_hung_task_detector(व्योम)
अणु
	atomic_set(&reset_hung_task, 1);
पूर्ण
EXPORT_SYMBOL_GPL(reset_hung_task_detector);

अटल bool hung_detector_suspended;

अटल पूर्णांक hungtask_pm_notअगरy(काष्ठा notअगरier_block *self,
			      अचिन्हित दीर्घ action, व्योम *hcpu)
अणु
	चयन (action) अणु
	हाल PM_SUSPEND_PREPARE:
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_RESTORE_PREPARE:
		hung_detector_suspended = true;
		अवरोध;
	हाल PM_POST_SUSPEND:
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
		hung_detector_suspended = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

/*
 * kthपढ़ो which checks क्रम tasks stuck in D state
 */
अटल पूर्णांक watchकरोg(व्योम *dummy)
अणु
	अचिन्हित दीर्घ hung_last_checked = jअगरfies;

	set_user_nice(current, 0);

	क्रम ( ; ; ) अणु
		अचिन्हित दीर्घ समयout = sysctl_hung_task_समयout_secs;
		अचिन्हित दीर्घ पूर्णांकerval = sysctl_hung_task_check_पूर्णांकerval_secs;
		दीर्घ t;

		अगर (पूर्णांकerval == 0)
			पूर्णांकerval = समयout;
		पूर्णांकerval = min_t(अचिन्हित दीर्घ, पूर्णांकerval, समयout);
		t = hung_समयout_jअगरfies(hung_last_checked, पूर्णांकerval);
		अगर (t <= 0) अणु
			अगर (!atomic_xchg(&reset_hung_task, 0) &&
			    !hung_detector_suspended)
				check_hung_unपूर्णांकerruptible_tasks(समयout);
			hung_last_checked = jअगरfies;
			जारी;
		पूर्ण
		schedule_समयout_पूर्णांकerruptible(t);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init hung_task_init(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &panic_block);

	/* Disable hung task detector on suspend */
	pm_notअगरier(hungtask_pm_notअगरy, 0);

	watchकरोg_task = kthपढ़ो_run(watchकरोg, शून्य, "khungtaskd");

	वापस 0;
पूर्ण
subsys_initcall(hung_task_init);
