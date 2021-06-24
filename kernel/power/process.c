<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/घातer/process.c - Functions क्रम starting/stopping processes on 
 *                           suspend transitions.
 *
 * Originally from swsusp.
 */


#अघोषित DEBUG

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/oom.h>
#समावेश <linux/suspend.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kmod.h>
#समावेश <trace/events/घातer.h>
#समावेश <linux/cpuset.h>

/*
 * Timeout क्रम stopping processes
 */
अचिन्हित पूर्णांक __पढ़ो_mostly मुक्तze_समयout_msecs = 20 * MSEC_PER_SEC;

अटल पूर्णांक try_to_मुक्तze_tasks(bool user_only)
अणु
	काष्ठा task_काष्ठा *g, *p;
	अचिन्हित दीर्घ end_समय;
	अचिन्हित पूर्णांक toकरो;
	bool wq_busy = false;
	kसमय_प्रकार start, end, elapsed;
	अचिन्हित पूर्णांक elapsed_msecs;
	bool wakeup = false;
	पूर्णांक sleep_usecs = USEC_PER_MSEC;

	start = kसमय_get_bootसमय();

	end_समय = jअगरfies + msecs_to_jअगरfies(मुक्तze_समयout_msecs);

	अगर (!user_only)
		मुक्तze_workqueues_begin();

	जबतक (true) अणु
		toकरो = 0;
		पढ़ो_lock(&tasklist_lock);
		क्रम_each_process_thपढ़ो(g, p) अणु
			अगर (p == current || !मुक्तze_task(p))
				जारी;

			अगर (!मुक्तzer_should_skip(p))
				toकरो++;
		पूर्ण
		पढ़ो_unlock(&tasklist_lock);

		अगर (!user_only) अणु
			wq_busy = मुक्तze_workqueues_busy();
			toकरो += wq_busy;
		पूर्ण

		अगर (!toकरो || समय_after(jअगरfies, end_समय))
			अवरोध;

		अगर (pm_wakeup_pending()) अणु
			wakeup = true;
			अवरोध;
		पूर्ण

		/*
		 * We need to retry, but first give the मुक्तzing tasks some
		 * समय to enter the refrigerator.  Start with an initial
		 * 1 ms sleep followed by exponential backoff until 8 ms.
		 */
		usleep_range(sleep_usecs / 2, sleep_usecs);
		अगर (sleep_usecs < 8 * USEC_PER_MSEC)
			sleep_usecs *= 2;
	पूर्ण

	end = kसमय_get_bootसमय();
	elapsed = kसमय_sub(end, start);
	elapsed_msecs = kसमय_प्रकारo_ms(elapsed);

	अगर (toकरो) अणु
		pr_cont("\n");
		pr_err("Freezing of tasks %s after %d.%03d seconds "
		       "(%d tasks refusing to freeze, wq_busy=%d):\n",
		       wakeup ? "aborted" : "failed",
		       elapsed_msecs / 1000, elapsed_msecs % 1000,
		       toकरो - wq_busy, wq_busy);

		अगर (wq_busy)
			show_workqueue_state();

		अगर (!wakeup || pm_debug_messages_on) अणु
			पढ़ो_lock(&tasklist_lock);
			क्रम_each_process_thपढ़ो(g, p) अणु
				अगर (p != current && !मुक्तzer_should_skip(p)
				    && मुक्तzing(p) && !frozen(p))
					sched_show_task(p);
			पूर्ण
			पढ़ो_unlock(&tasklist_lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_cont("(elapsed %d.%03d seconds) ", elapsed_msecs / 1000,
			elapsed_msecs % 1000);
	पूर्ण

	वापस toकरो ? -EBUSY : 0;
पूर्ण

/**
 * मुक्तze_processes - Signal user space processes to enter the refrigerator.
 * The current thपढ़ो will not be frozen.  The same process that calls
 * मुक्तze_processes must later call thaw_processes.
 *
 * On success, वापसs 0.  On failure, -त्रुटि_सं and प्रणाली is fully thawed.
 */
पूर्णांक मुक्तze_processes(व्योम)
अणु
	पूर्णांक error;

	error = __usermodehelper_disable(UMH_FREEZING);
	अगर (error)
		वापस error;

	/* Make sure this task करोesn't get frozen */
	current->flags |= PF_SUSPEND_TASK;

	अगर (!pm_मुक्तzing)
		atomic_inc(&प्रणाली_मुक्तzing_cnt);

	pm_wakeup_clear(true);
	pr_info("Freezing user space processes ... ");
	pm_मुक्तzing = true;
	error = try_to_मुक्तze_tasks(true);
	अगर (!error) अणु
		__usermodehelper_set_disable_depth(UMH_DISABLED);
		pr_cont("done.");
	पूर्ण
	pr_cont("\n");
	BUG_ON(in_atomic());

	/*
	 * Now that the whole userspace is frozen we need to disable
	 * the OOM समाप्तer to disallow any further पूर्णांकerference with
	 * समाप्तable tasks. There is no guarantee oom victims will
	 * ever reach a poपूर्णांक they go away we have to रुको with a समयout.
	 */
	अगर (!error && !oom_समाप्तer_disable(msecs_to_jअगरfies(मुक्तze_समयout_msecs)))
		error = -EBUSY;

	अगर (error)
		thaw_processes();
	वापस error;
पूर्ण

/**
 * मुक्तze_kernel_thपढ़ोs - Make मुक्तzable kernel thपढ़ोs go to the refrigerator.
 *
 * On success, वापसs 0.  On failure, -त्रुटि_सं and only the kernel thपढ़ोs are
 * thawed, so as to give a chance to the caller to करो additional cleanups
 * (अगर any) beक्रमe thawing the userspace tasks. So, it is the responsibility
 * of the caller to thaw the userspace tasks, when the समय is right.
 */
पूर्णांक मुक्तze_kernel_thपढ़ोs(व्योम)
अणु
	पूर्णांक error;

	pr_info("Freezing remaining freezable tasks ... ");

	pm_nosig_मुक्तzing = true;
	error = try_to_मुक्तze_tasks(false);
	अगर (!error)
		pr_cont("done.");

	pr_cont("\n");
	BUG_ON(in_atomic());

	अगर (error)
		thaw_kernel_thपढ़ोs();
	वापस error;
पूर्ण

व्योम thaw_processes(व्योम)
अणु
	काष्ठा task_काष्ठा *g, *p;
	काष्ठा task_काष्ठा *curr = current;

	trace_suspend_resume(TPS("thaw_processes"), 0, true);
	अगर (pm_मुक्तzing)
		atomic_dec(&प्रणाली_मुक्तzing_cnt);
	pm_मुक्तzing = false;
	pm_nosig_मुक्तzing = false;

	oom_समाप्तer_enable();

	pr_info("Restarting tasks ... ");

	__usermodehelper_set_disable_depth(UMH_FREEZING);
	thaw_workqueues();

	cpuset_रुको_क्रम_hotplug();

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, p) अणु
		/* No other thपढ़ोs should have PF_SUSPEND_TASK set */
		WARN_ON((p != curr) && (p->flags & PF_SUSPEND_TASK));
		__thaw_task(p);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

	WARN_ON(!(curr->flags & PF_SUSPEND_TASK));
	curr->flags &= ~PF_SUSPEND_TASK;

	usermodehelper_enable();

	schedule();
	pr_cont("done.\n");
	trace_suspend_resume(TPS("thaw_processes"), 0, false);
पूर्ण

व्योम thaw_kernel_thपढ़ोs(व्योम)
अणु
	काष्ठा task_काष्ठा *g, *p;

	pm_nosig_मुक्तzing = false;
	pr_info("Restarting kernel threads ... ");

	thaw_workqueues();

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, p) अणु
		अगर (p->flags & PF_KTHREAD)
			__thaw_task(p);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

	schedule();
	pr_cont("done.\n");
पूर्ण
