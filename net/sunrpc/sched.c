<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/sched.c
 *
 * Scheduling क्रम synchronous and asynchronous RPC requests.
 *
 * Copyright (C) 1996 Olaf Kirch, <okir@monad.swb.de>
 *
 * TCP NFS related पढ़ो + ग_लिखो fixes
 * (C) 1999 Dave Airlie, University of Limerick, Ireland <airlied@linux.ie>
 */

#समावेश <linux/module.h>

#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/mempool.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/sched/mm.h>

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/metrics.h>

#समावेश "sunrpc.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/sunrpc.h>

/*
 * RPC sद_असल and memory pools
 */
#घोषणा RPC_BUFFER_MAXSIZE	(2048)
#घोषणा RPC_BUFFER_POOLSIZE	(8)
#घोषणा RPC_TASK_POOLSIZE	(8)
अटल काष्ठा kmem_cache	*rpc_task_slabp __पढ़ो_mostly;
अटल काष्ठा kmem_cache	*rpc_buffer_slabp __पढ़ो_mostly;
अटल mempool_t	*rpc_task_mempool __पढ़ो_mostly;
अटल mempool_t	*rpc_buffer_mempool __पढ़ो_mostly;

अटल व्योम			rpc_async_schedule(काष्ठा work_काष्ठा *);
अटल व्योम			 rpc_release_task(काष्ठा rpc_task *task);
अटल व्योम __rpc_queue_समयr_fn(काष्ठा work_काष्ठा *);

/*
 * RPC tasks sit here जबतक रुकोing क्रम conditions to improve.
 */
अटल काष्ठा rpc_रुको_queue delay_queue;

/*
 * rpciod-related stuff
 */
काष्ठा workqueue_काष्ठा *rpciod_workqueue __पढ़ो_mostly;
काष्ठा workqueue_काष्ठा *xprtiod_workqueue __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(xprtiod_workqueue);

अचिन्हित दीर्घ
rpc_task_समयout(स्थिर काष्ठा rpc_task *task)
अणु
	अचिन्हित दीर्घ समयout = READ_ONCE(task->tk_समयout);

	अगर (समयout != 0) अणु
		अचिन्हित दीर्घ now = jअगरfies;
		अगर (समय_beक्रमe(now, समयout))
			वापस समयout - now;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_task_समयout);

/*
 * Disable the समयr क्रम a given RPC task. Should be called with
 * queue->lock and bh_disabled in order to aव्योम races within
 * rpc_run_समयr().
 */
अटल व्योम
__rpc_disable_समयr(काष्ठा rpc_रुको_queue *queue, काष्ठा rpc_task *task)
अणु
	अगर (list_empty(&task->u.tk_रुको.समयr_list))
		वापस;
	task->tk_समयout = 0;
	list_del(&task->u.tk_रुको.समयr_list);
	अगर (list_empty(&queue->समयr_list.list))
		cancel_delayed_work(&queue->समयr_list.dwork);
पूर्ण

अटल व्योम
rpc_set_queue_समयr(काष्ठा rpc_रुको_queue *queue, अचिन्हित दीर्घ expires)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	queue->समयr_list.expires = expires;
	अगर (समय_beक्रमe_eq(expires, now))
		expires = 0;
	अन्यथा
		expires -= now;
	mod_delayed_work(rpciod_workqueue, &queue->समयr_list.dwork, expires);
पूर्ण

/*
 * Set up a समयr क्रम the current task.
 */
अटल व्योम
__rpc_add_समयr(काष्ठा rpc_रुको_queue *queue, काष्ठा rpc_task *task,
		अचिन्हित दीर्घ समयout)
अणु
	task->tk_समयout = समयout;
	अगर (list_empty(&queue->समयr_list.list) || समय_beक्रमe(समयout, queue->समयr_list.expires))
		rpc_set_queue_समयr(queue, समयout);
	list_add(&task->u.tk_रुको.समयr_list, &queue->समयr_list.list);
पूर्ण

अटल व्योम rpc_set_रुकोqueue_priority(काष्ठा rpc_रुको_queue *queue, पूर्णांक priority)
अणु
	अगर (queue->priority != priority) अणु
		queue->priority = priority;
		queue->nr = 1U << priority;
	पूर्ण
पूर्ण

अटल व्योम rpc_reset_रुकोqueue_priority(काष्ठा rpc_रुको_queue *queue)
अणु
	rpc_set_रुकोqueue_priority(queue, queue->maxpriority);
पूर्ण

/*
 * Add a request to a queue list
 */
अटल व्योम
__rpc_list_enqueue_task(काष्ठा list_head *q, काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_task *t;

	list_क्रम_each_entry(t, q, u.tk_रुको.list) अणु
		अगर (t->tk_owner == task->tk_owner) अणु
			list_add_tail(&task->u.tk_रुको.links,
					&t->u.tk_रुको.links);
			/* Cache the queue head in task->u.tk_रुको.list */
			task->u.tk_रुको.list.next = q;
			task->u.tk_रुको.list.prev = शून्य;
			वापस;
		पूर्ण
	पूर्ण
	INIT_LIST_HEAD(&task->u.tk_रुको.links);
	list_add_tail(&task->u.tk_रुको.list, q);
पूर्ण

/*
 * Remove request from a queue list
 */
अटल व्योम
__rpc_list_dequeue_task(काष्ठा rpc_task *task)
अणु
	काष्ठा list_head *q;
	काष्ठा rpc_task *t;

	अगर (task->u.tk_रुको.list.prev == शून्य) अणु
		list_del(&task->u.tk_रुको.links);
		वापस;
	पूर्ण
	अगर (!list_empty(&task->u.tk_रुको.links)) अणु
		t = list_first_entry(&task->u.tk_रुको.links,
				काष्ठा rpc_task,
				u.tk_रुको.links);
		/* Assume __rpc_list_enqueue_task() cached the queue head */
		q = t->u.tk_रुको.list.next;
		list_add_tail(&t->u.tk_रुको.list, q);
		list_del(&task->u.tk_रुको.links);
	पूर्ण
	list_del(&task->u.tk_रुको.list);
पूर्ण

/*
 * Add new request to a priority queue.
 */
अटल व्योम __rpc_add_रुको_queue_priority(काष्ठा rpc_रुको_queue *queue,
		काष्ठा rpc_task *task,
		अचिन्हित अक्षर queue_priority)
अणु
	अगर (unlikely(queue_priority > queue->maxpriority))
		queue_priority = queue->maxpriority;
	__rpc_list_enqueue_task(&queue->tasks[queue_priority], task);
पूर्ण

/*
 * Add new request to रुको queue.
 *
 * Swapper tasks always get inserted at the head of the queue.
 * This should aव्योम many nasty memory deadlocks and hopefully
 * improve overall perक्रमmance.
 * Everyone अन्यथा माला_लो appended to the queue to ensure proper FIFO behavior.
 */
अटल व्योम __rpc_add_रुको_queue(काष्ठा rpc_रुको_queue *queue,
		काष्ठा rpc_task *task,
		अचिन्हित अक्षर queue_priority)
अणु
	INIT_LIST_HEAD(&task->u.tk_रुको.समयr_list);
	अगर (RPC_IS_PRIORITY(queue))
		__rpc_add_रुको_queue_priority(queue, task, queue_priority);
	अन्यथा अगर (RPC_IS_SWAPPER(task))
		list_add(&task->u.tk_रुको.list, &queue->tasks[0]);
	अन्यथा
		list_add_tail(&task->u.tk_रुको.list, &queue->tasks[0]);
	task->tk_रुकोqueue = queue;
	queue->qlen++;
	/* barrier matches the पढ़ो in rpc_wake_up_task_queue_locked() */
	smp_wmb();
	rpc_set_queued(task);
पूर्ण

/*
 * Remove request from a priority queue.
 */
अटल व्योम __rpc_हटाओ_रुको_queue_priority(काष्ठा rpc_task *task)
अणु
	__rpc_list_dequeue_task(task);
पूर्ण

/*
 * Remove request from queue.
 * Note: must be called with spin lock held.
 */
अटल व्योम __rpc_हटाओ_रुको_queue(काष्ठा rpc_रुको_queue *queue, काष्ठा rpc_task *task)
अणु
	__rpc_disable_समयr(queue, task);
	अगर (RPC_IS_PRIORITY(queue))
		__rpc_हटाओ_रुको_queue_priority(task);
	अन्यथा
		list_del(&task->u.tk_रुको.list);
	queue->qlen--;
पूर्ण

अटल व्योम __rpc_init_priority_रुको_queue(काष्ठा rpc_रुको_queue *queue, स्थिर अक्षर *qname, अचिन्हित अक्षर nr_queues)
अणु
	पूर्णांक i;

	spin_lock_init(&queue->lock);
	क्रम (i = 0; i < ARRAY_SIZE(queue->tasks); i++)
		INIT_LIST_HEAD(&queue->tasks[i]);
	queue->maxpriority = nr_queues - 1;
	rpc_reset_रुकोqueue_priority(queue);
	queue->qlen = 0;
	queue->समयr_list.expires = 0;
	INIT_DELAYED_WORK(&queue->समयr_list.dwork, __rpc_queue_समयr_fn);
	INIT_LIST_HEAD(&queue->समयr_list.list);
	rpc_assign_रुकोqueue_name(queue, qname);
पूर्ण

व्योम rpc_init_priority_रुको_queue(काष्ठा rpc_रुको_queue *queue, स्थिर अक्षर *qname)
अणु
	__rpc_init_priority_रुको_queue(queue, qname, RPC_NR_PRIORITY);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_init_priority_रुको_queue);

व्योम rpc_init_रुको_queue(काष्ठा rpc_रुको_queue *queue, स्थिर अक्षर *qname)
अणु
	__rpc_init_priority_रुको_queue(queue, qname, 1);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_init_रुको_queue);

व्योम rpc_destroy_रुको_queue(काष्ठा rpc_रुको_queue *queue)
अणु
	cancel_delayed_work_sync(&queue->समयr_list.dwork);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_destroy_रुको_queue);

अटल पूर्णांक rpc_रुको_bit_समाप्तable(काष्ठा रुको_bit_key *key, पूर्णांक mode)
अणु
	मुक्तzable_schedule_unsafe();
	अगर (संकेत_pending_state(mode, current))
		वापस -ERESTARTSYS;
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG) || IS_ENABLED(CONFIG_TRACEPOINTS)
अटल व्योम rpc_task_set_debuginfo(काष्ठा rpc_task *task)
अणु
	अटल atomic_t rpc_pid;

	task->tk_pid = atomic_inc_वापस(&rpc_pid);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम rpc_task_set_debuginfo(काष्ठा rpc_task *task)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम rpc_set_active(काष्ठा rpc_task *task)
अणु
	rpc_task_set_debuginfo(task);
	set_bit(RPC_TASK_ACTIVE, &task->tk_runstate);
	trace_rpc_task_begin(task, शून्य);
पूर्ण

/*
 * Mark an RPC call as having completed by clearing the 'active' bit
 * and then waking up all tasks that were sleeping.
 */
अटल पूर्णांक rpc_complete_task(काष्ठा rpc_task *task)
अणु
	व्योम *m = &task->tk_runstate;
	रुको_queue_head_t *wq = bit_रुकोqueue(m, RPC_TASK_ACTIVE);
	काष्ठा रुको_bit_key k = __WAIT_BIT_KEY_INITIALIZER(m, RPC_TASK_ACTIVE);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	trace_rpc_task_complete(task, शून्य);

	spin_lock_irqsave(&wq->lock, flags);
	clear_bit(RPC_TASK_ACTIVE, &task->tk_runstate);
	ret = atomic_dec_and_test(&task->tk_count);
	अगर (रुकोqueue_active(wq))
		__wake_up_locked_key(wq, TASK_NORMAL, &k);
	spin_unlock_irqrestore(&wq->lock, flags);
	वापस ret;
पूर्ण

/*
 * Allow callers to रुको क्रम completion of an RPC call
 *
 * Note the use of out_of_line_रुको_on_bit() rather than रुको_on_bit()
 * to enक्रमce taking of the wq->lock and hence aव्योम races with
 * rpc_complete_task().
 */
पूर्णांक __rpc_रुको_क्रम_completion_task(काष्ठा rpc_task *task, रुको_bit_action_f *action)
अणु
	अगर (action == शून्य)
		action = rpc_रुको_bit_समाप्तable;
	वापस out_of_line_रुको_on_bit(&task->tk_runstate, RPC_TASK_ACTIVE,
			action, TASK_KILLABLE);
पूर्ण
EXPORT_SYMBOL_GPL(__rpc_रुको_क्रम_completion_task);

/*
 * Make an RPC task runnable.
 *
 * Note: If the task is ASYNC, and is being made runnable after sitting on an
 * rpc_रुको_queue, this must be called with the queue spinlock held to protect
 * the रुको queue operation.
 * Note the ordering of rpc_test_and_set_running() and rpc_clear_queued(),
 * which is needed to ensure that __rpc_execute() करोesn't loop (due to the
 * lockless RPC_IS_QUEUED() test) beक्रमe we've had a chance to test
 * the RPC_TASK_RUNNING flag.
 */
अटल व्योम rpc_make_runnable(काष्ठा workqueue_काष्ठा *wq,
		काष्ठा rpc_task *task)
अणु
	bool need_wakeup = !rpc_test_and_set_running(task);

	rpc_clear_queued(task);
	अगर (!need_wakeup)
		वापस;
	अगर (RPC_IS_ASYNC(task)) अणु
		INIT_WORK(&task->u.tk_work, rpc_async_schedule);
		queue_work(wq, &task->u.tk_work);
	पूर्ण अन्यथा
		wake_up_bit(&task->tk_runstate, RPC_TASK_QUEUED);
पूर्ण

/*
 * Prepare क्रम sleeping on a रुको queue.
 * By always appending tasks to the list we ensure FIFO behavior.
 * NB: An RPC task will only receive पूर्णांकerrupt-driven events as दीर्घ
 * as it's on a रुको queue.
 */
अटल व्योम __rpc_करो_sleep_on_priority(काष्ठा rpc_रुको_queue *q,
		काष्ठा rpc_task *task,
		अचिन्हित अक्षर queue_priority)
अणु
	trace_rpc_task_sleep(task, q);

	__rpc_add_रुको_queue(q, task, queue_priority);
पूर्ण

अटल व्योम __rpc_sleep_on_priority(काष्ठा rpc_रुको_queue *q,
		काष्ठा rpc_task *task,
		अचिन्हित अक्षर queue_priority)
अणु
	अगर (WARN_ON_ONCE(RPC_IS_QUEUED(task)))
		वापस;
	__rpc_करो_sleep_on_priority(q, task, queue_priority);
पूर्ण

अटल व्योम __rpc_sleep_on_priority_समयout(काष्ठा rpc_रुको_queue *q,
		काष्ठा rpc_task *task, अचिन्हित दीर्घ समयout,
		अचिन्हित अक्षर queue_priority)
अणु
	अगर (WARN_ON_ONCE(RPC_IS_QUEUED(task)))
		वापस;
	अगर (समय_is_after_jअगरfies(समयout)) अणु
		__rpc_करो_sleep_on_priority(q, task, queue_priority);
		__rpc_add_समयr(q, task, समयout);
	पूर्ण अन्यथा
		task->tk_status = -ETIMEDOUT;
पूर्ण

अटल व्योम rpc_set_tk_callback(काष्ठा rpc_task *task, rpc_action action)
अणु
	अगर (action && !WARN_ON_ONCE(task->tk_callback != शून्य))
		task->tk_callback = action;
पूर्ण

अटल bool rpc_sleep_check_activated(काष्ठा rpc_task *task)
अणु
	/* We shouldn't ever put an inactive task to sleep */
	अगर (WARN_ON_ONCE(!RPC_IS_ACTIVATED(task))) अणु
		task->tk_status = -EIO;
		rpc_put_task_async(task);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

व्योम rpc_sleep_on_समयout(काष्ठा rpc_रुको_queue *q, काष्ठा rpc_task *task,
				rpc_action action, अचिन्हित दीर्घ समयout)
अणु
	अगर (!rpc_sleep_check_activated(task))
		वापस;

	rpc_set_tk_callback(task, action);

	/*
	 * Protect the queue operations.
	 */
	spin_lock(&q->lock);
	__rpc_sleep_on_priority_समयout(q, task, समयout, task->tk_priority);
	spin_unlock(&q->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_sleep_on_समयout);

व्योम rpc_sleep_on(काष्ठा rpc_रुको_queue *q, काष्ठा rpc_task *task,
				rpc_action action)
अणु
	अगर (!rpc_sleep_check_activated(task))
		वापस;

	rpc_set_tk_callback(task, action);

	WARN_ON_ONCE(task->tk_समयout != 0);
	/*
	 * Protect the queue operations.
	 */
	spin_lock(&q->lock);
	__rpc_sleep_on_priority(q, task, task->tk_priority);
	spin_unlock(&q->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_sleep_on);

व्योम rpc_sleep_on_priority_समयout(काष्ठा rpc_रुको_queue *q,
		काष्ठा rpc_task *task, अचिन्हित दीर्घ समयout, पूर्णांक priority)
अणु
	अगर (!rpc_sleep_check_activated(task))
		वापस;

	priority -= RPC_PRIORITY_LOW;
	/*
	 * Protect the queue operations.
	 */
	spin_lock(&q->lock);
	__rpc_sleep_on_priority_समयout(q, task, समयout, priority);
	spin_unlock(&q->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_sleep_on_priority_समयout);

व्योम rpc_sleep_on_priority(काष्ठा rpc_रुको_queue *q, काष्ठा rpc_task *task,
		पूर्णांक priority)
अणु
	अगर (!rpc_sleep_check_activated(task))
		वापस;

	WARN_ON_ONCE(task->tk_समयout != 0);
	priority -= RPC_PRIORITY_LOW;
	/*
	 * Protect the queue operations.
	 */
	spin_lock(&q->lock);
	__rpc_sleep_on_priority(q, task, priority);
	spin_unlock(&q->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_sleep_on_priority);

/**
 * __rpc_करो_wake_up_task_on_wq - wake up a single rpc_task
 * @wq: workqueue on which to run task
 * @queue: रुको queue
 * @task: task to be woken up
 *
 * Caller must hold queue->lock, and have cleared the task queued flag.
 */
अटल व्योम __rpc_करो_wake_up_task_on_wq(काष्ठा workqueue_काष्ठा *wq,
		काष्ठा rpc_रुको_queue *queue,
		काष्ठा rpc_task *task)
अणु
	/* Has the task been executed yet? If not, we cannot wake it up! */
	अगर (!RPC_IS_ACTIVATED(task)) अणु
		prपूर्णांकk(KERN_ERR "RPC: Inactive task (%p) being woken up!\n", task);
		वापस;
	पूर्ण

	trace_rpc_task_wakeup(task, queue);

	__rpc_हटाओ_रुको_queue(queue, task);

	rpc_make_runnable(wq, task);
पूर्ण

/*
 * Wake up a queued task जबतक the queue lock is being held
 */
अटल काष्ठा rpc_task *
rpc_wake_up_task_on_wq_queue_action_locked(काष्ठा workqueue_काष्ठा *wq,
		काष्ठा rpc_रुको_queue *queue, काष्ठा rpc_task *task,
		bool (*action)(काष्ठा rpc_task *, व्योम *), व्योम *data)
अणु
	अगर (RPC_IS_QUEUED(task)) अणु
		smp_rmb();
		अगर (task->tk_रुकोqueue == queue) अणु
			अगर (action == शून्य || action(task, data)) अणु
				__rpc_करो_wake_up_task_on_wq(wq, queue, task);
				वापस task;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Wake up a queued task जबतक the queue lock is being held
 */
अटल व्योम rpc_wake_up_task_queue_locked(काष्ठा rpc_रुको_queue *queue,
					  काष्ठा rpc_task *task)
अणु
	rpc_wake_up_task_on_wq_queue_action_locked(rpciod_workqueue, queue,
						   task, शून्य, शून्य);
पूर्ण

/*
 * Wake up a task on a specअगरic queue
 */
व्योम rpc_wake_up_queued_task(काष्ठा rpc_रुको_queue *queue, काष्ठा rpc_task *task)
अणु
	अगर (!RPC_IS_QUEUED(task))
		वापस;
	spin_lock(&queue->lock);
	rpc_wake_up_task_queue_locked(queue, task);
	spin_unlock(&queue->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_wake_up_queued_task);

अटल bool rpc_task_action_set_status(काष्ठा rpc_task *task, व्योम *status)
अणु
	task->tk_status = *(पूर्णांक *)status;
	वापस true;
पूर्ण

अटल व्योम
rpc_wake_up_task_queue_set_status_locked(काष्ठा rpc_रुको_queue *queue,
		काष्ठा rpc_task *task, पूर्णांक status)
अणु
	rpc_wake_up_task_on_wq_queue_action_locked(rpciod_workqueue, queue,
			task, rpc_task_action_set_status, &status);
पूर्ण

/**
 * rpc_wake_up_queued_task_set_status - wake up a task and set task->tk_status
 * @queue: poपूर्णांकer to rpc_रुको_queue
 * @task: poपूर्णांकer to rpc_task
 * @status: पूर्णांकeger error value
 *
 * If @task is queued on @queue, then it is woken up, and @task->tk_status is
 * set to the value of @status.
 */
व्योम
rpc_wake_up_queued_task_set_status(काष्ठा rpc_रुको_queue *queue,
		काष्ठा rpc_task *task, पूर्णांक status)
अणु
	अगर (!RPC_IS_QUEUED(task))
		वापस;
	spin_lock(&queue->lock);
	rpc_wake_up_task_queue_set_status_locked(queue, task, status);
	spin_unlock(&queue->lock);
पूर्ण

/*
 * Wake up the next task on a priority queue.
 */
अटल काष्ठा rpc_task *__rpc_find_next_queued_priority(काष्ठा rpc_रुको_queue *queue)
अणु
	काष्ठा list_head *q;
	काष्ठा rpc_task *task;

	/*
	 * Service a batch of tasks from a single owner.
	 */
	q = &queue->tasks[queue->priority];
	अगर (!list_empty(q) && --queue->nr) अणु
		task = list_first_entry(q, काष्ठा rpc_task, u.tk_रुको.list);
		जाओ out;
	पूर्ण

	/*
	 * Service the next queue.
	 */
	करो अणु
		अगर (q == &queue->tasks[0])
			q = &queue->tasks[queue->maxpriority];
		अन्यथा
			q = q - 1;
		अगर (!list_empty(q)) अणु
			task = list_first_entry(q, काष्ठा rpc_task, u.tk_रुको.list);
			जाओ new_queue;
		पूर्ण
	पूर्ण जबतक (q != &queue->tasks[queue->priority]);

	rpc_reset_रुकोqueue_priority(queue);
	वापस शून्य;

new_queue:
	rpc_set_रुकोqueue_priority(queue, (अचिन्हित पूर्णांक)(q - &queue->tasks[0]));
out:
	वापस task;
पूर्ण

अटल काष्ठा rpc_task *__rpc_find_next_queued(काष्ठा rpc_रुको_queue *queue)
अणु
	अगर (RPC_IS_PRIORITY(queue))
		वापस __rpc_find_next_queued_priority(queue);
	अगर (!list_empty(&queue->tasks[0]))
		वापस list_first_entry(&queue->tasks[0], काष्ठा rpc_task, u.tk_रुको.list);
	वापस शून्य;
पूर्ण

/*
 * Wake up the first task on the रुको queue.
 */
काष्ठा rpc_task *rpc_wake_up_first_on_wq(काष्ठा workqueue_काष्ठा *wq,
		काष्ठा rpc_रुको_queue *queue,
		bool (*func)(काष्ठा rpc_task *, व्योम *), व्योम *data)
अणु
	काष्ठा rpc_task	*task = शून्य;

	spin_lock(&queue->lock);
	task = __rpc_find_next_queued(queue);
	अगर (task != शून्य)
		task = rpc_wake_up_task_on_wq_queue_action_locked(wq, queue,
				task, func, data);
	spin_unlock(&queue->lock);

	वापस task;
पूर्ण

/*
 * Wake up the first task on the रुको queue.
 */
काष्ठा rpc_task *rpc_wake_up_first(काष्ठा rpc_रुको_queue *queue,
		bool (*func)(काष्ठा rpc_task *, व्योम *), व्योम *data)
अणु
	वापस rpc_wake_up_first_on_wq(rpciod_workqueue, queue, func, data);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_wake_up_first);

अटल bool rpc_wake_up_next_func(काष्ठा rpc_task *task, व्योम *data)
अणु
	वापस true;
पूर्ण

/*
 * Wake up the next task on the रुको queue.
*/
काष्ठा rpc_task *rpc_wake_up_next(काष्ठा rpc_रुको_queue *queue)
अणु
	वापस rpc_wake_up_first(queue, rpc_wake_up_next_func, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_wake_up_next);

/**
 * rpc_wake_up_locked - wake up all rpc_tasks
 * @queue: rpc_रुको_queue on which the tasks are sleeping
 *
 */
अटल व्योम rpc_wake_up_locked(काष्ठा rpc_रुको_queue *queue)
अणु
	काष्ठा rpc_task *task;

	क्रम (;;) अणु
		task = __rpc_find_next_queued(queue);
		अगर (task == शून्य)
			अवरोध;
		rpc_wake_up_task_queue_locked(queue, task);
	पूर्ण
पूर्ण

/**
 * rpc_wake_up - wake up all rpc_tasks
 * @queue: rpc_रुको_queue on which the tasks are sleeping
 *
 * Grअसल queue->lock
 */
व्योम rpc_wake_up(काष्ठा rpc_रुको_queue *queue)
अणु
	spin_lock(&queue->lock);
	rpc_wake_up_locked(queue);
	spin_unlock(&queue->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_wake_up);

/**
 * rpc_wake_up_status_locked - wake up all rpc_tasks and set their status value.
 * @queue: rpc_रुको_queue on which the tasks are sleeping
 * @status: status value to set
 */
अटल व्योम rpc_wake_up_status_locked(काष्ठा rpc_रुको_queue *queue, पूर्णांक status)
अणु
	काष्ठा rpc_task *task;

	क्रम (;;) अणु
		task = __rpc_find_next_queued(queue);
		अगर (task == शून्य)
			अवरोध;
		rpc_wake_up_task_queue_set_status_locked(queue, task, status);
	पूर्ण
पूर्ण

/**
 * rpc_wake_up_status - wake up all rpc_tasks and set their status value.
 * @queue: rpc_रुको_queue on which the tasks are sleeping
 * @status: status value to set
 *
 * Grअसल queue->lock
 */
व्योम rpc_wake_up_status(काष्ठा rpc_रुको_queue *queue, पूर्णांक status)
अणु
	spin_lock(&queue->lock);
	rpc_wake_up_status_locked(queue, status);
	spin_unlock(&queue->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_wake_up_status);

अटल व्योम __rpc_queue_समयr_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpc_रुको_queue *queue = container_of(work,
			काष्ठा rpc_रुको_queue,
			समयr_list.dwork.work);
	काष्ठा rpc_task *task, *n;
	अचिन्हित दीर्घ expires, now, समयo;

	spin_lock(&queue->lock);
	expires = now = jअगरfies;
	list_क्रम_each_entry_safe(task, n, &queue->समयr_list.list, u.tk_रुको.समयr_list) अणु
		समयo = task->tk_समयout;
		अगर (समय_after_eq(now, समयo)) अणु
			trace_rpc_task_समयout(task, task->tk_action);
			task->tk_status = -ETIMEDOUT;
			rpc_wake_up_task_queue_locked(queue, task);
			जारी;
		पूर्ण
		अगर (expires == now || समय_after(expires, समयo))
			expires = समयo;
	पूर्ण
	अगर (!list_empty(&queue->समयr_list.list))
		rpc_set_queue_समयr(queue, expires);
	spin_unlock(&queue->lock);
पूर्ण

अटल व्योम __rpc_atrun(काष्ठा rpc_task *task)
अणु
	अगर (task->tk_status == -ETIMEDOUT)
		task->tk_status = 0;
पूर्ण

/*
 * Run a task at a later समय
 */
व्योम rpc_delay(काष्ठा rpc_task *task, अचिन्हित दीर्घ delay)
अणु
	rpc_sleep_on_समयout(&delay_queue, task, __rpc_atrun, jअगरfies + delay);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_delay);

/*
 * Helper to call task->tk_ops->rpc_call_prepare
 */
व्योम rpc_prepare_task(काष्ठा rpc_task *task)
अणु
	task->tk_ops->rpc_call_prepare(task, task->tk_calldata);
पूर्ण

अटल व्योम
rpc_init_task_statistics(काष्ठा rpc_task *task)
अणु
	/* Initialize retry counters */
	task->tk_garb_retry = 2;
	task->tk_cred_retry = 2;
	task->tk_rebind_retry = 2;

	/* starting बारtamp */
	task->tk_start = kसमय_get();
पूर्ण

अटल व्योम
rpc_reset_task_statistics(काष्ठा rpc_task *task)
अणु
	task->tk_समयouts = 0;
	task->tk_flags &= ~(RPC_CALL_MAJORSEEN|RPC_TASK_SENT);
	rpc_init_task_statistics(task);
पूर्ण

/*
 * Helper that calls task->tk_ops->rpc_call_करोne अगर it exists
 */
व्योम rpc_निकास_task(काष्ठा rpc_task *task)
अणु
	trace_rpc_task_end(task, task->tk_action);
	task->tk_action = शून्य;
	अगर (task->tk_ops->rpc_count_stats)
		task->tk_ops->rpc_count_stats(task, task->tk_calldata);
	अन्यथा अगर (task->tk_client)
		rpc_count_iostats(task, task->tk_client->cl_metrics);
	अगर (task->tk_ops->rpc_call_करोne != शून्य) अणु
		task->tk_ops->rpc_call_करोne(task, task->tk_calldata);
		अगर (task->tk_action != शून्य) अणु
			/* Always release the RPC slot and buffer memory */
			xprt_release(task);
			rpc_reset_task_statistics(task);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rpc_संकेत_task(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_रुको_queue *queue;

	अगर (!RPC_IS_ACTIVATED(task))
		वापस;

	trace_rpc_task_संकेतled(task, task->tk_action);
	set_bit(RPC_TASK_SIGNALLED, &task->tk_runstate);
	smp_mb__after_atomic();
	queue = READ_ONCE(task->tk_रुकोqueue);
	अगर (queue)
		rpc_wake_up_queued_task_set_status(queue, task, -ERESTARTSYS);
पूर्ण

व्योम rpc_निकास(काष्ठा rpc_task *task, पूर्णांक status)
अणु
	task->tk_status = status;
	task->tk_action = rpc_निकास_task;
	rpc_wake_up_queued_task(task->tk_रुकोqueue, task);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_निकास);

व्योम rpc_release_calldata(स्थिर काष्ठा rpc_call_ops *ops, व्योम *calldata)
अणु
	अगर (ops->rpc_release != शून्य)
		ops->rpc_release(calldata);
पूर्ण

/*
 * This is the RPC `scheduler' (or rather, the finite state machine).
 */
अटल व्योम __rpc_execute(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_रुको_queue *queue;
	पूर्णांक task_is_async = RPC_IS_ASYNC(task);
	पूर्णांक status = 0;

	WARN_ON_ONCE(RPC_IS_QUEUED(task));
	अगर (RPC_IS_QUEUED(task))
		वापस;

	क्रम (;;) अणु
		व्योम (*करो_action)(काष्ठा rpc_task *);

		/*
		 * Perक्रमm the next FSM step or a pending callback.
		 *
		 * tk_action may be शून्य अगर the task has been समाप्तed.
		 * In particular, note that rpc_समाप्तall_tasks may
		 * करो this at any समय, so beware when dereferencing.
		 */
		करो_action = task->tk_action;
		अगर (task->tk_callback) अणु
			करो_action = task->tk_callback;
			task->tk_callback = शून्य;
		पूर्ण
		अगर (!करो_action)
			अवरोध;
		trace_rpc_task_run_action(task, करो_action);
		करो_action(task);

		/*
		 * Lockless check क्रम whether task is sleeping or not.
		 */
		अगर (!RPC_IS_QUEUED(task))
			जारी;

		/*
		 * Signalled tasks should निकास rather than sleep.
		 */
		अगर (RPC_SIGNALLED(task)) अणु
			task->tk_rpc_status = -ERESTARTSYS;
			rpc_निकास(task, -ERESTARTSYS);
		पूर्ण

		/*
		 * The queue->lock protects against races with
		 * rpc_make_runnable().
		 *
		 * Note that once we clear RPC_TASK_RUNNING on an asynchronous
		 * rpc_task, rpc_make_runnable() can assign it to a
		 * dअगरferent workqueue. We thereक्रमe cannot assume that the
		 * rpc_task poपूर्णांकer may still be dereferenced.
		 */
		queue = task->tk_रुकोqueue;
		spin_lock(&queue->lock);
		अगर (!RPC_IS_QUEUED(task)) अणु
			spin_unlock(&queue->lock);
			जारी;
		पूर्ण
		rpc_clear_running(task);
		spin_unlock(&queue->lock);
		अगर (task_is_async)
			वापस;

		/* sync task: sleep here */
		trace_rpc_task_sync_sleep(task, task->tk_action);
		status = out_of_line_रुको_on_bit(&task->tk_runstate,
				RPC_TASK_QUEUED, rpc_रुको_bit_समाप्तable,
				TASK_KILLABLE);
		अगर (status < 0) अणु
			/*
			 * When a sync task receives a संकेत, it निकासs with
			 * -ERESTARTSYS. In order to catch any callbacks that
			 * clean up after sleeping on some queue, we करोn't
			 * अवरोध the loop here, but go around once more.
			 */
			trace_rpc_task_संकेतled(task, task->tk_action);
			set_bit(RPC_TASK_SIGNALLED, &task->tk_runstate);
			task->tk_rpc_status = -ERESTARTSYS;
			rpc_निकास(task, -ERESTARTSYS);
		पूर्ण
		trace_rpc_task_sync_wake(task, task->tk_action);
	पूर्ण

	/* Release all resources associated with the task */
	rpc_release_task(task);
पूर्ण

/*
 * User-visible entry poपूर्णांक to the scheduler.
 *
 * This may be called recursively अगर e.g. an async NFS task updates
 * the attributes and finds that dirty pages must be flushed.
 * NOTE: Upon निकास of this function the task is guaranteed to be
 *	 released. In particular note that tk_release() will have
 *	 been called, so your task memory may have been मुक्तd.
 */
व्योम rpc_execute(काष्ठा rpc_task *task)
अणु
	bool is_async = RPC_IS_ASYNC(task);

	rpc_set_active(task);
	rpc_make_runnable(rpciod_workqueue, task);
	अगर (!is_async) अणु
		अचिन्हित पूर्णांक pflags = meदो_स्मृति_nofs_save();
		__rpc_execute(task);
		meदो_स्मृति_nofs_restore(pflags);
	पूर्ण
पूर्ण

अटल व्योम rpc_async_schedule(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित पूर्णांक pflags = meदो_स्मृति_nofs_save();

	__rpc_execute(container_of(work, काष्ठा rpc_task, u.tk_work));
	meदो_स्मृति_nofs_restore(pflags);
पूर्ण

/**
 * rpc_दो_स्मृति - allocate RPC buffer resources
 * @task: RPC task
 *
 * A single memory region is allocated, which is split between the
 * RPC call and RPC reply that this task is being used क्रम. When
 * this RPC is retired, the memory is released by calling rpc_मुक्त.
 *
 * To prevent rpciod from hanging, this allocator never sleeps,
 * वापसing -ENOMEM and suppressing warning अगर the request cannot
 * be serviced immediately. The caller can arrange to sleep in a
 * way that is safe क्रम rpciod.
 *
 * Most requests are 'small' (under 2KiB) and can be serviced from a
 * mempool, ensuring that NFS पढ़ोs and ग_लिखोs can always proceed,
 * and that there is good locality of reference क्रम these buffers.
 */
पूर्णांक rpc_दो_स्मृति(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *rqst = task->tk_rqstp;
	माप_प्रकार size = rqst->rq_callsize + rqst->rq_rcvsize;
	काष्ठा rpc_buffer *buf;
	gfp_t gfp = GFP_NOFS;

	अगर (RPC_IS_SWAPPER(task))
		gfp = __GFP_MEMALLOC | GFP_NOWAIT | __GFP_NOWARN;

	size += माप(काष्ठा rpc_buffer);
	अगर (size <= RPC_BUFFER_MAXSIZE)
		buf = mempool_alloc(rpc_buffer_mempool, gfp);
	अन्यथा
		buf = kदो_स्मृति(size, gfp);

	अगर (!buf)
		वापस -ENOMEM;

	buf->len = size;
	rqst->rq_buffer = buf->data;
	rqst->rq_rbuffer = (अक्षर *)rqst->rq_buffer + rqst->rq_callsize;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_दो_स्मृति);

/**
 * rpc_मुक्त - मुक्त RPC buffer resources allocated via rpc_दो_स्मृति
 * @task: RPC task
 *
 */
व्योम rpc_मुक्त(काष्ठा rpc_task *task)
अणु
	व्योम *buffer = task->tk_rqstp->rq_buffer;
	माप_प्रकार size;
	काष्ठा rpc_buffer *buf;

	buf = container_of(buffer, काष्ठा rpc_buffer, data);
	size = buf->len;

	अगर (size <= RPC_BUFFER_MAXSIZE)
		mempool_मुक्त(buf, rpc_buffer_mempool);
	अन्यथा
		kमुक्त(buf);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_मुक्त);

/*
 * Creation and deletion of RPC task काष्ठाures
 */
अटल व्योम rpc_init_task(काष्ठा rpc_task *task, स्थिर काष्ठा rpc_task_setup *task_setup_data)
अणु
	स_रखो(task, 0, माप(*task));
	atomic_set(&task->tk_count, 1);
	task->tk_flags  = task_setup_data->flags;
	task->tk_ops = task_setup_data->callback_ops;
	task->tk_calldata = task_setup_data->callback_data;
	INIT_LIST_HEAD(&task->tk_task);

	task->tk_priority = task_setup_data->priority - RPC_PRIORITY_LOW;
	task->tk_owner = current->tgid;

	/* Initialize workqueue क्रम async tasks */
	task->tk_workqueue = task_setup_data->workqueue;

	task->tk_xprt = rpc_task_get_xprt(task_setup_data->rpc_client,
			xprt_get(task_setup_data->rpc_xprt));

	task->tk_op_cred = get_rpccred(task_setup_data->rpc_op_cred);

	अगर (task->tk_ops->rpc_call_prepare != शून्य)
		task->tk_action = rpc_prepare_task;

	rpc_init_task_statistics(task);
पूर्ण

अटल काष्ठा rpc_task *
rpc_alloc_task(व्योम)
अणु
	वापस (काष्ठा rpc_task *)mempool_alloc(rpc_task_mempool, GFP_NOFS);
पूर्ण

/*
 * Create a new task क्रम the specअगरied client.
 */
काष्ठा rpc_task *rpc_new_task(स्थिर काष्ठा rpc_task_setup *setup_data)
अणु
	काष्ठा rpc_task	*task = setup_data->task;
	अचिन्हित लघु flags = 0;

	अगर (task == शून्य) अणु
		task = rpc_alloc_task();
		flags = RPC_TASK_DYNAMIC;
	पूर्ण

	rpc_init_task(task, setup_data);
	task->tk_flags |= flags;
	वापस task;
पूर्ण

/*
 * rpc_मुक्त_task - release rpc task and perक्रमm cleanups
 *
 * Note that we मुक्त up the rpc_task _after_ rpc_release_calldata()
 * in order to work around a workqueue dependency issue.
 *
 * Tejun Heo states:
 * "Workqueue currently considers two work items to be the same अगर they're
 * on the same address and won't execute them concurrently - ie. it
 * makes a work item which is queued again जबतक being executed रुको
 * क्रम the previous execution to complete.
 *
 * If a work function मुक्तs the work item, and then रुकोs क्रम an event
 * which should be perक्रमmed by another work item and *that* work item
 * recycles the मुक्तd work item, it can create a false dependency loop.
 * There really is no reliable way to detect this लघु of verअगरying
 * every memory मुक्त."
 *
 */
अटल व्योम rpc_मुक्त_task(काष्ठा rpc_task *task)
अणु
	अचिन्हित लघु tk_flags = task->tk_flags;

	put_rpccred(task->tk_op_cred);
	rpc_release_calldata(task->tk_ops, task->tk_calldata);

	अगर (tk_flags & RPC_TASK_DYNAMIC)
		mempool_मुक्त(task, rpc_task_mempool);
पूर्ण

अटल व्योम rpc_async_release(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित पूर्णांक pflags = meदो_स्मृति_nofs_save();

	rpc_मुक्त_task(container_of(work, काष्ठा rpc_task, u.tk_work));
	meदो_स्मृति_nofs_restore(pflags);
पूर्ण

अटल व्योम rpc_release_resources_task(काष्ठा rpc_task *task)
अणु
	xprt_release(task);
	अगर (task->tk_msg.rpc_cred) अणु
		अगर (!(task->tk_flags & RPC_TASK_CRED_NOREF))
			put_cred(task->tk_msg.rpc_cred);
		task->tk_msg.rpc_cred = शून्य;
	पूर्ण
	rpc_task_release_client(task);
पूर्ण

अटल व्योम rpc_final_put_task(काष्ठा rpc_task *task,
		काष्ठा workqueue_काष्ठा *q)
अणु
	अगर (q != शून्य) अणु
		INIT_WORK(&task->u.tk_work, rpc_async_release);
		queue_work(q, &task->u.tk_work);
	पूर्ण अन्यथा
		rpc_मुक्त_task(task);
पूर्ण

अटल व्योम rpc_करो_put_task(काष्ठा rpc_task *task, काष्ठा workqueue_काष्ठा *q)
अणु
	अगर (atomic_dec_and_test(&task->tk_count)) अणु
		rpc_release_resources_task(task);
		rpc_final_put_task(task, q);
	पूर्ण
पूर्ण

व्योम rpc_put_task(काष्ठा rpc_task *task)
अणु
	rpc_करो_put_task(task, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_put_task);

व्योम rpc_put_task_async(काष्ठा rpc_task *task)
अणु
	rpc_करो_put_task(task, task->tk_workqueue);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_put_task_async);

अटल व्योम rpc_release_task(काष्ठा rpc_task *task)
अणु
	WARN_ON_ONCE(RPC_IS_QUEUED(task));

	rpc_release_resources_task(task);

	/*
	 * Note: at this poपूर्णांक we have been हटाओd from rpc_clnt->cl_tasks,
	 * so it should be safe to use task->tk_count as a test क्रम whether
	 * or not any other processes still hold references to our rpc_task.
	 */
	अगर (atomic_पढ़ो(&task->tk_count) != 1 + !RPC_IS_ASYNC(task)) अणु
		/* Wake up anyone who may be रुकोing क्रम task completion */
		अगर (!rpc_complete_task(task))
			वापस;
	पूर्ण अन्यथा अणु
		अगर (!atomic_dec_and_test(&task->tk_count))
			वापस;
	पूर्ण
	rpc_final_put_task(task, task->tk_workqueue);
पूर्ण

पूर्णांक rpciod_up(व्योम)
अणु
	वापस try_module_get(THIS_MODULE) ? 0 : -EINVAL;
पूर्ण

व्योम rpciod_करोwn(व्योम)
अणु
	module_put(THIS_MODULE);
पूर्ण

/*
 * Start up the rpciod workqueue.
 */
अटल पूर्णांक rpciod_start(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *wq;

	/*
	 * Create the rpciod thपढ़ो and रुको क्रम it to start.
	 */
	wq = alloc_workqueue("rpciod", WQ_MEM_RECLAIM | WQ_UNBOUND, 0);
	अगर (!wq)
		जाओ out_failed;
	rpciod_workqueue = wq;
	/* Note: highpri because network receive is latency sensitive */
	wq = alloc_workqueue("xprtiod", WQ_UNBOUND|WQ_MEM_RECLAIM|WQ_HIGHPRI, 0);
	अगर (!wq)
		जाओ मुक्त_rpciod;
	xprtiod_workqueue = wq;
	वापस 1;
मुक्त_rpciod:
	wq = rpciod_workqueue;
	rpciod_workqueue = शून्य;
	destroy_workqueue(wq);
out_failed:
	वापस 0;
पूर्ण

अटल व्योम rpciod_stop(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *wq = शून्य;

	अगर (rpciod_workqueue == शून्य)
		वापस;

	wq = rpciod_workqueue;
	rpciod_workqueue = शून्य;
	destroy_workqueue(wq);
	wq = xprtiod_workqueue;
	xprtiod_workqueue = शून्य;
	destroy_workqueue(wq);
पूर्ण

व्योम
rpc_destroy_mempool(व्योम)
अणु
	rpciod_stop();
	mempool_destroy(rpc_buffer_mempool);
	mempool_destroy(rpc_task_mempool);
	kmem_cache_destroy(rpc_task_slabp);
	kmem_cache_destroy(rpc_buffer_slabp);
	rpc_destroy_रुको_queue(&delay_queue);
पूर्ण

पूर्णांक
rpc_init_mempool(व्योम)
अणु
	/*
	 * The following is not strictly a mempool initialisation,
	 * but there is no harm in करोing it here
	 */
	rpc_init_रुको_queue(&delay_queue, "delayq");
	अगर (!rpciod_start())
		जाओ err_nomem;

	rpc_task_slabp = kmem_cache_create("rpc_tasks",
					     माप(काष्ठा rpc_task),
					     0, SLAB_HWCACHE_ALIGN,
					     शून्य);
	अगर (!rpc_task_slabp)
		जाओ err_nomem;
	rpc_buffer_slabp = kmem_cache_create("rpc_buffers",
					     RPC_BUFFER_MAXSIZE,
					     0, SLAB_HWCACHE_ALIGN,
					     शून्य);
	अगर (!rpc_buffer_slabp)
		जाओ err_nomem;
	rpc_task_mempool = mempool_create_slab_pool(RPC_TASK_POOLSIZE,
						    rpc_task_slabp);
	अगर (!rpc_task_mempool)
		जाओ err_nomem;
	rpc_buffer_mempool = mempool_create_slab_pool(RPC_BUFFER_POOLSIZE,
						      rpc_buffer_slabp);
	अगर (!rpc_buffer_mempool)
		जाओ err_nomem;
	वापस 0;
err_nomem:
	rpc_destroy_mempool();
	वापस -ENOMEM;
पूर्ण
