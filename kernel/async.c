<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * async.c: Asynchronous function calls क्रम boot perक्रमmance
 *
 * (C) Copyright 2009 Intel Corporation
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */


/*

Goals and Theory of Operation

The primary goal of this feature is to reduce the kernel boot समय,
by करोing various independent hardware delays and discovery operations
decoupled and not strictly serialized.

More specअगरically, the asynchronous function call concept allows
certain operations (primarily during प्रणाली boot) to happen
asynchronously, out of order, जबतक these operations still
have their बाह्यally visible parts happen sequentially and in-order.
(not unlike how out-of-order CPUs retire their inकाष्ठाions in order)

Key to the asynchronous function call implementation is the concept of
a "sequence cookie" (which, although it has an असलtracted type, can be
thought of as a monotonically incrementing number).

The async core will assign each scheduled event such a sequence cookie and
pass this to the called functions.

The asynchronously called function should beक्रमe करोing a globally visible
operation, such as रेजिस्टरing device numbers, call the
async_synchronize_cookie() function and pass in its own cookie. The
async_synchronize_cookie() function will make sure that all asynchronous
operations that were scheduled prior to the operation corresponding with the
cookie have completed.

Subप्रणाली/driver initialization code that scheduled asynchronous probe
functions, but which shares global resources with other drivers/subप्रणालीs
that करो not use the asynchronous call feature, need to करो a full
synchronization with the async_synchronize_full() function, beक्रमe वापसing
from their init function. This is to मुख्यtain strict ordering between the
asynchronous and synchronous parts of the kernel.

*/

#समावेश <linux/async.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/export.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "workqueue_internal.h"

अटल async_cookie_t next_cookie = 1;

#घोषणा MAX_WORK		32768
#घोषणा ASYNC_COOKIE_MAX	ULदीर्घ_उच्च	/* infinity cookie */

अटल LIST_HEAD(async_global_pending);	/* pending from all रेजिस्टरed करोms */
अटल ASYNC_DOMAIN(async_dfl_करोमुख्य);
अटल DEFINE_SPINLOCK(async_lock);

काष्ठा async_entry अणु
	काष्ठा list_head	करोमुख्य_list;
	काष्ठा list_head	global_list;
	काष्ठा work_काष्ठा	work;
	async_cookie_t		cookie;
	async_func_t		func;
	व्योम			*data;
	काष्ठा async_करोमुख्य	*करोमुख्य;
पूर्ण;

अटल DECLARE_WAIT_QUEUE_HEAD(async_करोne);

अटल atomic_t entry_count;

अटल दीर्घ दीर्घ microseconds_since(kसमय_प्रकार start)
अणु
	kसमय_प्रकार now = kसमय_get();
	वापस kसमय_प्रकारo_ns(kसमय_sub(now, start)) >> 10;
पूर्ण

अटल async_cookie_t lowest_in_progress(काष्ठा async_करोमुख्य *करोमुख्य)
अणु
	काष्ठा async_entry *first = शून्य;
	async_cookie_t ret = ASYNC_COOKIE_MAX;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&async_lock, flags);

	अगर (करोमुख्य) अणु
		अगर (!list_empty(&करोमुख्य->pending))
			first = list_first_entry(&करोमुख्य->pending,
					काष्ठा async_entry, करोमुख्य_list);
	पूर्ण अन्यथा अणु
		अगर (!list_empty(&async_global_pending))
			first = list_first_entry(&async_global_pending,
					काष्ठा async_entry, global_list);
	पूर्ण

	अगर (first)
		ret = first->cookie;

	spin_unlock_irqrestore(&async_lock, flags);
	वापस ret;
पूर्ण

/*
 * pick the first pending entry and run it
 */
अटल व्योम async_run_entry_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा async_entry *entry =
		container_of(work, काष्ठा async_entry, work);
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार callसमय;

	/* 1) run (and prपूर्णांक duration) */
	pr_debug("calling  %lli_%pS @ %i\n", (दीर्घ दीर्घ)entry->cookie,
		 entry->func, task_pid_nr(current));
	callसमय = kसमय_get();

	entry->func(entry->data, entry->cookie);

	pr_debug("initcall %lli_%pS returned after %lld usecs\n",
		 (दीर्घ दीर्घ)entry->cookie, entry->func,
		 microseconds_since(callसमय));

	/* 2) हटाओ self from the pending queues */
	spin_lock_irqsave(&async_lock, flags);
	list_del_init(&entry->करोमुख्य_list);
	list_del_init(&entry->global_list);

	/* 3) मुक्त the entry */
	kमुक्त(entry);
	atomic_dec(&entry_count);

	spin_unlock_irqrestore(&async_lock, flags);

	/* 4) wake up any रुकोers */
	wake_up(&async_करोne);
पूर्ण

/**
 * async_schedule_node_करोमुख्य - NUMA specअगरic version of async_schedule_करोमुख्य
 * @func: function to execute asynchronously
 * @data: data poपूर्णांकer to pass to the function
 * @node: NUMA node that we want to schedule this on or बंद to
 * @करोमुख्य: the करोमुख्य
 *
 * Returns an async_cookie_t that may be used क्रम checkpoपूर्णांकing later.
 * @करोमुख्य may be used in the async_synchronize_*_करोमुख्य() functions to
 * रुको within a certain synchronization करोमुख्य rather than globally.
 *
 * Note: This function may be called from atomic or non-atomic contexts.
 *
 * The node requested will be honored on a best efक्रमt basis. If the node
 * has no CPUs associated with it then the work is distributed among all
 * available CPUs.
 */
async_cookie_t async_schedule_node_करोमुख्य(async_func_t func, व्योम *data,
					  पूर्णांक node, काष्ठा async_करोमुख्य *करोमुख्य)
अणु
	काष्ठा async_entry *entry;
	अचिन्हित दीर्घ flags;
	async_cookie_t newcookie;

	/* allow irq-off callers */
	entry = kzalloc(माप(काष्ठा async_entry), GFP_ATOMIC);

	/*
	 * If we're out of memory or if there's too much work
	 * pending alपढ़ोy, we execute synchronously.
	 */
	अगर (!entry || atomic_पढ़ो(&entry_count) > MAX_WORK) अणु
		kमुक्त(entry);
		spin_lock_irqsave(&async_lock, flags);
		newcookie = next_cookie++;
		spin_unlock_irqrestore(&async_lock, flags);

		/* low on memory.. run synchronously */
		func(data, newcookie);
		वापस newcookie;
	पूर्ण
	INIT_LIST_HEAD(&entry->करोमुख्य_list);
	INIT_LIST_HEAD(&entry->global_list);
	INIT_WORK(&entry->work, async_run_entry_fn);
	entry->func = func;
	entry->data = data;
	entry->करोमुख्य = करोमुख्य;

	spin_lock_irqsave(&async_lock, flags);

	/* allocate cookie and queue */
	newcookie = entry->cookie = next_cookie++;

	list_add_tail(&entry->करोमुख्य_list, &करोमुख्य->pending);
	अगर (करोमुख्य->रेजिस्टरed)
		list_add_tail(&entry->global_list, &async_global_pending);

	atomic_inc(&entry_count);
	spin_unlock_irqrestore(&async_lock, flags);

	/* mark that this task has queued an async job, used by module init */
	current->flags |= PF_USED_ASYNC;

	/* schedule क्रम execution */
	queue_work_node(node, प्रणाली_unbound_wq, &entry->work);

	वापस newcookie;
पूर्ण
EXPORT_SYMBOL_GPL(async_schedule_node_करोमुख्य);

/**
 * async_schedule_node - NUMA specअगरic version of async_schedule
 * @func: function to execute asynchronously
 * @data: data poपूर्णांकer to pass to the function
 * @node: NUMA node that we want to schedule this on or बंद to
 *
 * Returns an async_cookie_t that may be used क्रम checkpoपूर्णांकing later.
 * Note: This function may be called from atomic or non-atomic contexts.
 *
 * The node requested will be honored on a best efक्रमt basis. If the node
 * has no CPUs associated with it then the work is distributed among all
 * available CPUs.
 */
async_cookie_t async_schedule_node(async_func_t func, व्योम *data, पूर्णांक node)
अणु
	वापस async_schedule_node_करोमुख्य(func, data, node, &async_dfl_करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(async_schedule_node);

/**
 * async_synchronize_full - synchronize all asynchronous function calls
 *
 * This function रुकोs until all asynchronous function calls have been करोne.
 */
व्योम async_synchronize_full(व्योम)
अणु
	async_synchronize_full_करोमुख्य(शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(async_synchronize_full);

/**
 * async_synchronize_full_करोमुख्य - synchronize all asynchronous function within a certain करोमुख्य
 * @करोमुख्य: the करोमुख्य to synchronize
 *
 * This function रुकोs until all asynchronous function calls क्रम the
 * synchronization करोमुख्य specअगरied by @करोमुख्य have been करोne.
 */
व्योम async_synchronize_full_करोमुख्य(काष्ठा async_करोमुख्य *करोमुख्य)
अणु
	async_synchronize_cookie_करोमुख्य(ASYNC_COOKIE_MAX, करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(async_synchronize_full_करोमुख्य);

/**
 * async_synchronize_cookie_करोमुख्य - synchronize asynchronous function calls within a certain करोमुख्य with cookie checkpoपूर्णांकing
 * @cookie: async_cookie_t to use as checkpoपूर्णांक
 * @करोमुख्य: the करोमुख्य to synchronize (%शून्य क्रम all रेजिस्टरed करोमुख्यs)
 *
 * This function रुकोs until all asynchronous function calls क्रम the
 * synchronization करोमुख्य specअगरied by @करोमुख्य submitted prior to @cookie
 * have been करोne.
 */
व्योम async_synchronize_cookie_करोमुख्य(async_cookie_t cookie, काष्ठा async_करोमुख्य *करोमुख्य)
अणु
	kसमय_प्रकार startसमय;

	pr_debug("async_waiting @ %i\n", task_pid_nr(current));
	startसमय = kसमय_get();

	रुको_event(async_करोne, lowest_in_progress(करोमुख्य) >= cookie);

	pr_debug("async_continuing @ %i after %lli usec\n", task_pid_nr(current),
		 microseconds_since(startसमय));
पूर्ण
EXPORT_SYMBOL_GPL(async_synchronize_cookie_करोमुख्य);

/**
 * async_synchronize_cookie - synchronize asynchronous function calls with cookie checkpoपूर्णांकing
 * @cookie: async_cookie_t to use as checkpoपूर्णांक
 *
 * This function रुकोs until all asynchronous function calls prior to @cookie
 * have been करोne.
 */
व्योम async_synchronize_cookie(async_cookie_t cookie)
अणु
	async_synchronize_cookie_करोमुख्य(cookie, &async_dfl_करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(async_synchronize_cookie);

/**
 * current_is_async - is %current an async worker task?
 *
 * Returns %true अगर %current is an async worker task.
 */
bool current_is_async(व्योम)
अणु
	काष्ठा worker *worker = current_wq_worker();

	वापस worker && worker->current_func == async_run_entry_fn;
पूर्ण
EXPORT_SYMBOL_GPL(current_is_async);
