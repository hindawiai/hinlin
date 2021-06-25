<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/मुक्तzer.c - Function to मुक्तze a process
 *
 * Originally from kernel/घातer/process.c
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/suspend.h>
#समावेश <linux/export.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>

/* total number of मुक्तzing conditions in effect */
atomic_t प्रणाली_मुक्तzing_cnt = ATOMIC_INIT(0);
EXPORT_SYMBOL(प्रणाली_मुक्तzing_cnt);

/* indicate whether PM मुक्तzing is in effect, रक्षित by
 * प्रणाली_transition_mutex
 */
bool pm_मुक्तzing;
bool pm_nosig_मुक्तzing;

/* protects मुक्तzing and frozen transitions */
अटल DEFINE_SPINLOCK(मुक्तzer_lock);

/**
 * मुक्तzing_slow_path - slow path क्रम testing whether a task needs to be frozen
 * @p: task to be tested
 *
 * This function is called by मुक्तzing() अगर प्रणाली_मुक्तzing_cnt isn't zero
 * and tests whether @p needs to enter and stay in frozen state.  Can be
 * called under any context.  The मुक्तzers are responsible क्रम ensuring the
 * target tasks see the updated state.
 */
bool मुक्तzing_slow_path(काष्ठा task_काष्ठा *p)
अणु
	अगर (p->flags & (PF_NOFREEZE | PF_SUSPEND_TASK))
		वापस false;

	अगर (test_tsk_thपढ़ो_flag(p, TIF_MEMDIE))
		वापस false;

	अगर (pm_nosig_मुक्तzing || cgroup_मुक्तzing(p))
		वापस true;

	अगर (pm_मुक्तzing && !(p->flags & PF_KTHREAD))
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(मुक्तzing_slow_path);

/* Refrigerator is place where frozen processes are stored :-). */
bool __refrigerator(bool check_kthr_stop)
अणु
	/* Hmm, should we be allowed to suspend when there are realसमय
	   processes around? */
	bool was_frozen = false;
	दीर्घ save = current->state;

	pr_debug("%s entered refrigerator\n", current->comm);

	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);

		spin_lock_irq(&मुक्तzer_lock);
		current->flags |= PF_FROZEN;
		अगर (!मुक्तzing(current) ||
		    (check_kthr_stop && kthपढ़ो_should_stop()))
			current->flags &= ~PF_FROZEN;
		spin_unlock_irq(&मुक्तzer_lock);

		अगर (!(current->flags & PF_FROZEN))
			अवरोध;
		was_frozen = true;
		schedule();
	पूर्ण

	pr_debug("%s left refrigerator\n", current->comm);

	/*
	 * Restore saved task state beक्रमe वापसing.  The mb'd version
	 * needs to be used; otherwise, it might silently अवरोध
	 * synchronization which depends on ordered task state change.
	 */
	set_current_state(save);

	वापस was_frozen;
पूर्ण
EXPORT_SYMBOL(__refrigerator);

अटल व्योम fake_संकेत_wake_up(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ flags;

	अगर (lock_task_sighand(p, &flags)) अणु
		संकेत_wake_up(p, 0);
		unlock_task_sighand(p, &flags);
	पूर्ण
पूर्ण

/**
 * मुक्तze_task - send a मुक्तze request to given task
 * @p: task to send the request to
 *
 * If @p is मुक्तzing, the मुक्तze request is sent either by sending a fake
 * संकेत (अगर it's not a kernel thread) or waking it up (if it's a kernel
 * thपढ़ो).
 *
 * RETURNS:
 * %false, अगर @p is not मुक्तzing or alपढ़ोy frozen; %true, otherwise
 */
bool मुक्तze_task(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * This check can race with मुक्तzer_करो_not_count, but worst हाल that
	 * will result in an extra wakeup being sent to the task.  It करोes not
	 * race with मुक्तzer_count(), the barriers in मुक्तzer_count() and
	 * मुक्तzer_should_skip() ensure that either मुक्तzer_count() sees
	 * मुक्तzing == true in try_to_मुक्तze() and मुक्तzes, or
	 * मुक्तzer_should_skip() sees !PF_FREEZE_SKIP and मुक्तzes the task
	 * normally.
	 */
	अगर (मुक्तzer_should_skip(p))
		वापस false;

	spin_lock_irqsave(&मुक्तzer_lock, flags);
	अगर (!मुक्तzing(p) || frozen(p)) अणु
		spin_unlock_irqrestore(&मुक्तzer_lock, flags);
		वापस false;
	पूर्ण

	अगर (!(p->flags & PF_KTHREAD))
		fake_संकेत_wake_up(p);
	अन्यथा
		wake_up_state(p, TASK_INTERRUPTIBLE);

	spin_unlock_irqrestore(&मुक्तzer_lock, flags);
	वापस true;
पूर्ण

व्योम __thaw_task(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&मुक्तzer_lock, flags);
	अगर (frozen(p))
		wake_up_process(p);
	spin_unlock_irqrestore(&मुक्तzer_lock, flags);
पूर्ण

/**
 * set_मुक्तzable - make %current मुक्तzable
 *
 * Mark %current मुक्तzable and enter refrigerator अगर necessary.
 */
bool set_मुक्तzable(व्योम)
अणु
	might_sleep();

	/*
	 * Modअगरy flags जबतक holding मुक्तzer_lock.  This ensures the
	 * मुक्तzer notices that we aren't frozen yet or the मुक्तzing
	 * condition is visible to try_to_मुक्तze() below.
	 */
	spin_lock_irq(&मुक्तzer_lock);
	current->flags &= ~PF_NOFREEZE;
	spin_unlock_irq(&मुक्तzer_lock);

	वापस try_to_मुक्तze();
पूर्ण
EXPORT_SYMBOL(set_मुक्तzable);
