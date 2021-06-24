<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/spinlock.h>
#समावेश <linux/task_work.h>
#समावेश <linux/tracehook.h>

अटल काष्ठा callback_head work_निकासed; /* all we need is ->next == शून्य */

/**
 * task_work_add - ask the @task to execute @work->func()
 * @task: the task which should run the callback
 * @work: the callback to run
 * @notअगरy: how to notअगरy the targeted task
 *
 * Queue @work क्रम task_work_run() below and notअगरy the @task अगर @notअगरy
 * is @TWA_RESUME or @TWA_SIGNAL. @TWA_SIGNAL works like संकेतs, in that the
 * it will पूर्णांकerrupt the targeted task and run the task_work. @TWA_RESUME
 * work is run only when the task निकासs the kernel and वापसs to user mode,
 * or beक्रमe entering guest mode. Fails अगर the @task is निकासing/निकासed and thus
 * it can't process this @work. Otherwise @work->func() will be called when the
 * @task goes through one of the aक्रमementioned transitions, or निकासs.
 *
 * If the targeted task is निकासing, then an error is वापसed and the work item
 * is not queued. It's up to the caller to arrange क्रम an alternative mechanism
 * in that हाल.
 *
 * Note: there is no ordering guarantee on works queued here. The task_work
 * list is LIFO.
 *
 * RETURNS:
 * 0 अगर succeeds or -ESRCH.
 */
पूर्णांक task_work_add(काष्ठा task_काष्ठा *task, काष्ठा callback_head *work,
		  क्रमागत task_work_notअगरy_mode notअगरy)
अणु
	काष्ठा callback_head *head;

	/* record the work call stack in order to prपूर्णांक it in KASAN reports */
	kasan_record_aux_stack(work);

	करो अणु
		head = READ_ONCE(task->task_works);
		अगर (unlikely(head == &work_निकासed))
			वापस -ESRCH;
		work->next = head;
	पूर्ण जबतक (cmpxchg(&task->task_works, head, work) != head);

	चयन (notअगरy) अणु
	हाल TWA_NONE:
		अवरोध;
	हाल TWA_RESUME:
		set_notअगरy_resume(task);
		अवरोध;
	हाल TWA_SIGNAL:
		set_notअगरy_संकेत(task);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * task_work_cancel_match - cancel a pending work added by task_work_add()
 * @task: the task which should execute the work
 * @match: match function to call
 *
 * RETURNS:
 * The found work or शून्य अगर not found.
 */
काष्ठा callback_head *
task_work_cancel_match(काष्ठा task_काष्ठा *task,
		       bool (*match)(काष्ठा callback_head *, व्योम *data),
		       व्योम *data)
अणु
	काष्ठा callback_head **pprev = &task->task_works;
	काष्ठा callback_head *work;
	अचिन्हित दीर्घ flags;

	अगर (likely(!task->task_works))
		वापस शून्य;
	/*
	 * If cmpxchg() fails we जारी without updating pprev.
	 * Either we raced with task_work_add() which added the
	 * new entry beक्रमe this work, we will find it again. Or
	 * we raced with task_work_run(), *pprev == शून्य/निकासed.
	 */
	raw_spin_lock_irqsave(&task->pi_lock, flags);
	जबतक ((work = READ_ONCE(*pprev))) अणु
		अगर (!match(work, data))
			pprev = &work->next;
		अन्यथा अगर (cmpxchg(pprev, work, work->next) == work)
			अवरोध;
	पूर्ण
	raw_spin_unlock_irqrestore(&task->pi_lock, flags);

	वापस work;
पूर्ण

अटल bool task_work_func_match(काष्ठा callback_head *cb, व्योम *data)
अणु
	वापस cb->func == data;
पूर्ण

/**
 * task_work_cancel - cancel a pending work added by task_work_add()
 * @task: the task which should execute the work
 * @func: identअगरies the work to हटाओ
 *
 * Find the last queued pending work with ->func == @func and हटाओ
 * it from queue.
 *
 * RETURNS:
 * The found work or शून्य अगर not found.
 */
काष्ठा callback_head *
task_work_cancel(काष्ठा task_काष्ठा *task, task_work_func_t func)
अणु
	वापस task_work_cancel_match(task, task_work_func_match, func);
पूर्ण

/**
 * task_work_run - execute the works added by task_work_add()
 *
 * Flush the pending works. Should be used by the core kernel code.
 * Called beक्रमe the task वापसs to the user-mode or stops, or when
 * it निकासs. In the latter हाल task_work_add() can no दीर्घer add the
 * new work after task_work_run() वापसs.
 */
व्योम task_work_run(व्योम)
अणु
	काष्ठा task_काष्ठा *task = current;
	काष्ठा callback_head *work, *head, *next;

	क्रम (;;) अणु
		/*
		 * work->func() can करो task_work_add(), करो not set
		 * work_निकासed unless the list is empty.
		 */
		करो अणु
			head = शून्य;
			work = READ_ONCE(task->task_works);
			अगर (!work) अणु
				अगर (task->flags & PF_EXITING)
					head = &work_निकासed;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण जबतक (cmpxchg(&task->task_works, work, head) != work);

		अगर (!work)
			अवरोध;
		/*
		 * Synchronize with task_work_cancel(). It can not हटाओ
		 * the first entry == work, cmpxchg(task_works) must fail.
		 * But it can हटाओ another entry from the ->next list.
		 */
		raw_spin_lock_irq(&task->pi_lock);
		raw_spin_unlock_irq(&task->pi_lock);

		करो अणु
			next = work->next;
			work->func(work);
			work = next;
			cond_resched();
		पूर्ण जबतक (work);
	पूर्ण
पूर्ण
