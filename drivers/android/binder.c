<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* binder.c
 *
 * Android IPC Subप्रणाली
 *
 * Copyright (C) 2007-2008 Google, Inc.
 */

/*
 * Locking overview
 *
 * There are 3 मुख्य spinlocks which must be acquired in the
 * order shown:
 *
 * 1) proc->outer_lock : protects binder_ref
 *    binder_proc_lock() and binder_proc_unlock() are
 *    used to acq/rel.
 * 2) node->lock : protects most fields of binder_node.
 *    binder_node_lock() and binder_node_unlock() are
 *    used to acq/rel
 * 3) proc->inner_lock : protects the thपढ़ो and node lists
 *    (proc->thपढ़ोs, proc->रुकोing_thपढ़ोs, proc->nodes)
 *    and all toकरो lists associated with the binder_proc
 *    (proc->toकरो, thपढ़ो->toकरो, proc->delivered_death and
 *    node->async_toकरो), as well as thपढ़ो->transaction_stack
 *    binder_inner_proc_lock() and binder_inner_proc_unlock()
 *    are used to acq/rel
 *
 * Any lock under procA must never be nested under any lock at the same
 * level or below on procB.
 *
 * Functions that require a lock held on entry indicate which lock
 * in the suffix of the function name:
 *
 * foo_olocked() : requires node->outer_lock
 * foo_nlocked() : requires node->lock
 * foo_ilocked() : requires proc->inner_lock
 * foo_oilocked(): requires proc->outer_lock and proc->inner_lock
 * foo_nilocked(): requires node->lock and proc->inner_lock
 * ...
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fdtable.h>
#समावेश <linux/file.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/poll.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/security.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/task_work.h>
#समावेश <linux/sizes.h>

#समावेश <uapi/linux/android/binder.h>

#समावेश <यंत्र/cacheflush.h>

#समावेश "binder_internal.h"
#समावेश "binder_trace.h"

अटल HLIST_HEAD(binder_deferred_list);
अटल DEFINE_MUTEX(binder_deferred_lock);

अटल HLIST_HEAD(binder_devices);
अटल HLIST_HEAD(binder_procs);
अटल DEFINE_MUTEX(binder_procs_lock);

अटल HLIST_HEAD(binder_dead_nodes);
अटल DEFINE_SPINLOCK(binder_dead_nodes_lock);

अटल काष्ठा dentry *binder_debugfs_dir_entry_root;
अटल काष्ठा dentry *binder_debugfs_dir_entry_proc;
अटल atomic_t binder_last_id;

अटल पूर्णांक proc_show(काष्ठा seq_file *m, व्योम *unused);
DEFINE_SHOW_ATTRIBUTE(proc);

#घोषणा FORBIDDEN_MMAP_FLAGS                (VM_WRITE)

क्रमागत अणु
	BINDER_DEBUG_USER_ERROR             = 1U << 0,
	BINDER_DEBUG_FAILED_TRANSACTION     = 1U << 1,
	BINDER_DEBUG_DEAD_TRANSACTION       = 1U << 2,
	BINDER_DEBUG_OPEN_CLOSE             = 1U << 3,
	BINDER_DEBUG_DEAD_BINDER            = 1U << 4,
	BINDER_DEBUG_DEATH_NOTIFICATION     = 1U << 5,
	BINDER_DEBUG_READ_WRITE             = 1U << 6,
	BINDER_DEBUG_USER_REFS              = 1U << 7,
	BINDER_DEBUG_THREADS                = 1U << 8,
	BINDER_DEBUG_TRANSACTION            = 1U << 9,
	BINDER_DEBUG_TRANSACTION_COMPLETE   = 1U << 10,
	BINDER_DEBUG_FREE_BUFFER            = 1U << 11,
	BINDER_DEBUG_INTERNAL_REFS          = 1U << 12,
	BINDER_DEBUG_PRIORITY_CAP           = 1U << 13,
	BINDER_DEBUG_SPINLOCKS              = 1U << 14,
पूर्ण;
अटल uपूर्णांक32_t binder_debug_mask = BINDER_DEBUG_USER_ERROR |
	BINDER_DEBUG_FAILED_TRANSACTION | BINDER_DEBUG_DEAD_TRANSACTION;
module_param_named(debug_mask, binder_debug_mask, uपूर्णांक, 0644);

अक्षर *binder_devices_param = CONFIG_ANDROID_BINDER_DEVICES;
module_param_named(devices, binder_devices_param, अक्षरp, 0444);

अटल DECLARE_WAIT_QUEUE_HEAD(binder_user_error_रुको);
अटल पूर्णांक binder_stop_on_user_error;

अटल पूर्णांक binder_set_stop_on_user_error(स्थिर अक्षर *val,
					 स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;

	ret = param_set_पूर्णांक(val, kp);
	अगर (binder_stop_on_user_error < 2)
		wake_up(&binder_user_error_रुको);
	वापस ret;
पूर्ण
module_param_call(stop_on_user_error, binder_set_stop_on_user_error,
	param_get_पूर्णांक, &binder_stop_on_user_error, 0644);

#घोषणा binder_debug(mask, x...) \
	करो अणु \
		अगर (binder_debug_mask & mask) \
			pr_info_ratelimited(x); \
	पूर्ण जबतक (0)

#घोषणा binder_user_error(x...) \
	करो अणु \
		अगर (binder_debug_mask & BINDER_DEBUG_USER_ERROR) \
			pr_info_ratelimited(x); \
		अगर (binder_stop_on_user_error) \
			binder_stop_on_user_error = 2; \
	पूर्ण जबतक (0)

#घोषणा to_flat_binder_object(hdr) \
	container_of(hdr, काष्ठा flat_binder_object, hdr)

#घोषणा to_binder_fd_object(hdr) container_of(hdr, काष्ठा binder_fd_object, hdr)

#घोषणा to_binder_buffer_object(hdr) \
	container_of(hdr, काष्ठा binder_buffer_object, hdr)

#घोषणा to_binder_fd_array_object(hdr) \
	container_of(hdr, काष्ठा binder_fd_array_object, hdr)

अटल काष्ठा binder_stats binder_stats;

अटल अंतरभूत व्योम binder_stats_deleted(क्रमागत binder_stat_types type)
अणु
	atomic_inc(&binder_stats.obj_deleted[type]);
पूर्ण

अटल अंतरभूत व्योम binder_stats_created(क्रमागत binder_stat_types type)
अणु
	atomic_inc(&binder_stats.obj_created[type]);
पूर्ण

काष्ठा binder_transaction_log binder_transaction_log;
काष्ठा binder_transaction_log binder_transaction_log_failed;

अटल काष्ठा binder_transaction_log_entry *binder_transaction_log_add(
	काष्ठा binder_transaction_log *log)
अणु
	काष्ठा binder_transaction_log_entry *e;
	अचिन्हित पूर्णांक cur = atomic_inc_वापस(&log->cur);

	अगर (cur >= ARRAY_SIZE(log->entry))
		log->full = true;
	e = &log->entry[cur % ARRAY_SIZE(log->entry)];
	WRITE_ONCE(e->debug_id_करोne, 0);
	/*
	 * ग_लिखो-barrier to synchronize access to e->debug_id_करोne.
	 * We make sure the initialized 0 value is seen beक्रमe
	 * स_रखो() other fields are zeroed by स_रखो.
	 */
	smp_wmb();
	स_रखो(e, 0, माप(*e));
	वापस e;
पूर्ण

क्रमागत binder_deferred_state अणु
	BINDER_DEFERRED_FLUSH        = 0x01,
	BINDER_DEFERRED_RELEASE      = 0x02,
पूर्ण;

क्रमागत अणु
	BINDER_LOOPER_STATE_REGISTERED  = 0x01,
	BINDER_LOOPER_STATE_ENTERED     = 0x02,
	BINDER_LOOPER_STATE_EXITED      = 0x04,
	BINDER_LOOPER_STATE_INVALID     = 0x08,
	BINDER_LOOPER_STATE_WAITING     = 0x10,
	BINDER_LOOPER_STATE_POLL        = 0x20,
पूर्ण;

/**
 * binder_proc_lock() - Acquire outer lock क्रम given binder_proc
 * @proc:         काष्ठा binder_proc to acquire
 *
 * Acquires proc->outer_lock. Used to protect binder_ref
 * काष्ठाures associated with the given proc.
 */
#घोषणा binder_proc_lock(proc) _binder_proc_lock(proc, __LINE__)
अटल व्योम
_binder_proc_lock(काष्ठा binder_proc *proc, पूर्णांक line)
	__acquires(&proc->outer_lock)
अणु
	binder_debug(BINDER_DEBUG_SPINLOCKS,
		     "%s: line=%d\n", __func__, line);
	spin_lock(&proc->outer_lock);
पूर्ण

/**
 * binder_proc_unlock() - Release spinlock क्रम given binder_proc
 * @proc:         काष्ठा binder_proc to acquire
 *
 * Release lock acquired via binder_proc_lock()
 */
#घोषणा binder_proc_unlock(_proc) _binder_proc_unlock(_proc, __LINE__)
अटल व्योम
_binder_proc_unlock(काष्ठा binder_proc *proc, पूर्णांक line)
	__releases(&proc->outer_lock)
अणु
	binder_debug(BINDER_DEBUG_SPINLOCKS,
		     "%s: line=%d\n", __func__, line);
	spin_unlock(&proc->outer_lock);
पूर्ण

/**
 * binder_inner_proc_lock() - Acquire inner lock क्रम given binder_proc
 * @proc:         काष्ठा binder_proc to acquire
 *
 * Acquires proc->inner_lock. Used to protect toकरो lists
 */
#घोषणा binder_inner_proc_lock(proc) _binder_inner_proc_lock(proc, __LINE__)
अटल व्योम
_binder_inner_proc_lock(काष्ठा binder_proc *proc, पूर्णांक line)
	__acquires(&proc->inner_lock)
अणु
	binder_debug(BINDER_DEBUG_SPINLOCKS,
		     "%s: line=%d\n", __func__, line);
	spin_lock(&proc->inner_lock);
पूर्ण

/**
 * binder_inner_proc_unlock() - Release inner lock क्रम given binder_proc
 * @proc:         काष्ठा binder_proc to acquire
 *
 * Release lock acquired via binder_inner_proc_lock()
 */
#घोषणा binder_inner_proc_unlock(proc) _binder_inner_proc_unlock(proc, __LINE__)
अटल व्योम
_binder_inner_proc_unlock(काष्ठा binder_proc *proc, पूर्णांक line)
	__releases(&proc->inner_lock)
अणु
	binder_debug(BINDER_DEBUG_SPINLOCKS,
		     "%s: line=%d\n", __func__, line);
	spin_unlock(&proc->inner_lock);
पूर्ण

/**
 * binder_node_lock() - Acquire spinlock क्रम given binder_node
 * @node:         काष्ठा binder_node to acquire
 *
 * Acquires node->lock. Used to protect binder_node fields
 */
#घोषणा binder_node_lock(node) _binder_node_lock(node, __LINE__)
अटल व्योम
_binder_node_lock(काष्ठा binder_node *node, पूर्णांक line)
	__acquires(&node->lock)
अणु
	binder_debug(BINDER_DEBUG_SPINLOCKS,
		     "%s: line=%d\n", __func__, line);
	spin_lock(&node->lock);
पूर्ण

/**
 * binder_node_unlock() - Release spinlock क्रम given binder_proc
 * @node:         काष्ठा binder_node to acquire
 *
 * Release lock acquired via binder_node_lock()
 */
#घोषणा binder_node_unlock(node) _binder_node_unlock(node, __LINE__)
अटल व्योम
_binder_node_unlock(काष्ठा binder_node *node, पूर्णांक line)
	__releases(&node->lock)
अणु
	binder_debug(BINDER_DEBUG_SPINLOCKS,
		     "%s: line=%d\n", __func__, line);
	spin_unlock(&node->lock);
पूर्ण

/**
 * binder_node_inner_lock() - Acquire node and inner locks
 * @node:         काष्ठा binder_node to acquire
 *
 * Acquires node->lock. If node->proc also acquires
 * proc->inner_lock. Used to protect binder_node fields
 */
#घोषणा binder_node_inner_lock(node) _binder_node_inner_lock(node, __LINE__)
अटल व्योम
_binder_node_inner_lock(काष्ठा binder_node *node, पूर्णांक line)
	__acquires(&node->lock) __acquires(&node->proc->inner_lock)
अणु
	binder_debug(BINDER_DEBUG_SPINLOCKS,
		     "%s: line=%d\n", __func__, line);
	spin_lock(&node->lock);
	अगर (node->proc)
		binder_inner_proc_lock(node->proc);
	अन्यथा
		/* annotation क्रम sparse */
		__acquire(&node->proc->inner_lock);
पूर्ण

/**
 * binder_node_unlock() - Release node and inner locks
 * @node:         काष्ठा binder_node to acquire
 *
 * Release lock acquired via binder_node_lock()
 */
#घोषणा binder_node_inner_unlock(node) _binder_node_inner_unlock(node, __LINE__)
अटल व्योम
_binder_node_inner_unlock(काष्ठा binder_node *node, पूर्णांक line)
	__releases(&node->lock) __releases(&node->proc->inner_lock)
अणु
	काष्ठा binder_proc *proc = node->proc;

	binder_debug(BINDER_DEBUG_SPINLOCKS,
		     "%s: line=%d\n", __func__, line);
	अगर (proc)
		binder_inner_proc_unlock(proc);
	अन्यथा
		/* annotation क्रम sparse */
		__release(&node->proc->inner_lock);
	spin_unlock(&node->lock);
पूर्ण

अटल bool binder_worklist_empty_ilocked(काष्ठा list_head *list)
अणु
	वापस list_empty(list);
पूर्ण

/**
 * binder_worklist_empty() - Check अगर no items on the work list
 * @proc:       binder_proc associated with list
 * @list:	list to check
 *
 * Return: true अगर there are no items on list, अन्यथा false
 */
अटल bool binder_worklist_empty(काष्ठा binder_proc *proc,
				  काष्ठा list_head *list)
अणु
	bool ret;

	binder_inner_proc_lock(proc);
	ret = binder_worklist_empty_ilocked(list);
	binder_inner_proc_unlock(proc);
	वापस ret;
पूर्ण

/**
 * binder_enqueue_work_ilocked() - Add an item to the work list
 * @work:         काष्ठा binder_work to add to list
 * @target_list:  list to add work to
 *
 * Adds the work to the specअगरied list. Asserts that work
 * is not alपढ़ोy on a list.
 *
 * Requires the proc->inner_lock to be held.
 */
अटल व्योम
binder_enqueue_work_ilocked(काष्ठा binder_work *work,
			   काष्ठा list_head *target_list)
अणु
	BUG_ON(target_list == शून्य);
	BUG_ON(work->entry.next && !list_empty(&work->entry));
	list_add_tail(&work->entry, target_list);
पूर्ण

/**
 * binder_enqueue_deferred_thपढ़ो_work_ilocked() - Add deferred thपढ़ो work
 * @thपढ़ो:       thपढ़ो to queue work to
 * @work:         काष्ठा binder_work to add to list
 *
 * Adds the work to the toकरो list of the thपढ़ो. Doesn't set the process_toकरो
 * flag, which means that (अगर it wasn't alपढ़ोy set) the thपढ़ो will go to
 * sleep without handling this work when it calls पढ़ो.
 *
 * Requires the proc->inner_lock to be held.
 */
अटल व्योम
binder_enqueue_deferred_thपढ़ो_work_ilocked(काष्ठा binder_thपढ़ो *thपढ़ो,
					    काष्ठा binder_work *work)
अणु
	WARN_ON(!list_empty(&thपढ़ो->रुकोing_thपढ़ो_node));
	binder_enqueue_work_ilocked(work, &thपढ़ो->toकरो);
पूर्ण

/**
 * binder_enqueue_thपढ़ो_work_ilocked() - Add an item to the thपढ़ो work list
 * @thपढ़ो:       thपढ़ो to queue work to
 * @work:         काष्ठा binder_work to add to list
 *
 * Adds the work to the toकरो list of the thपढ़ो, and enables processing
 * of the toकरो queue.
 *
 * Requires the proc->inner_lock to be held.
 */
अटल व्योम
binder_enqueue_thपढ़ो_work_ilocked(काष्ठा binder_thपढ़ो *thपढ़ो,
				   काष्ठा binder_work *work)
अणु
	WARN_ON(!list_empty(&thपढ़ो->रुकोing_thपढ़ो_node));
	binder_enqueue_work_ilocked(work, &thपढ़ो->toकरो);
	thपढ़ो->process_toकरो = true;
पूर्ण

/**
 * binder_enqueue_thपढ़ो_work() - Add an item to the thपढ़ो work list
 * @thपढ़ो:       thपढ़ो to queue work to
 * @work:         काष्ठा binder_work to add to list
 *
 * Adds the work to the toकरो list of the thपढ़ो, and enables processing
 * of the toकरो queue.
 */
अटल व्योम
binder_enqueue_thपढ़ो_work(काष्ठा binder_thपढ़ो *thपढ़ो,
			   काष्ठा binder_work *work)
अणु
	binder_inner_proc_lock(thपढ़ो->proc);
	binder_enqueue_thपढ़ो_work_ilocked(thपढ़ो, work);
	binder_inner_proc_unlock(thपढ़ो->proc);
पूर्ण

अटल व्योम
binder_dequeue_work_ilocked(काष्ठा binder_work *work)
अणु
	list_del_init(&work->entry);
पूर्ण

/**
 * binder_dequeue_work() - Removes an item from the work list
 * @proc:         binder_proc associated with list
 * @work:         काष्ठा binder_work to हटाओ from list
 *
 * Removes the specअगरied work item from whatever list it is on.
 * Can safely be called अगर work is not on any list.
 */
अटल व्योम
binder_dequeue_work(काष्ठा binder_proc *proc, काष्ठा binder_work *work)
अणु
	binder_inner_proc_lock(proc);
	binder_dequeue_work_ilocked(work);
	binder_inner_proc_unlock(proc);
पूर्ण

अटल काष्ठा binder_work *binder_dequeue_work_head_ilocked(
					काष्ठा list_head *list)
अणु
	काष्ठा binder_work *w;

	w = list_first_entry_or_null(list, काष्ठा binder_work, entry);
	अगर (w)
		list_del_init(&w->entry);
	वापस w;
पूर्ण

अटल व्योम
binder_defer_work(काष्ठा binder_proc *proc, क्रमागत binder_deferred_state defer);
अटल व्योम binder_मुक्त_thपढ़ो(काष्ठा binder_thपढ़ो *thपढ़ो);
अटल व्योम binder_मुक्त_proc(काष्ठा binder_proc *proc);
अटल व्योम binder_inc_node_पंचांगpref_ilocked(काष्ठा binder_node *node);

अटल bool binder_has_work_ilocked(काष्ठा binder_thपढ़ो *thपढ़ो,
				    bool करो_proc_work)
अणु
	वापस thपढ़ो->process_toकरो ||
		thपढ़ो->looper_need_वापस ||
		(करो_proc_work &&
		 !binder_worklist_empty_ilocked(&thपढ़ो->proc->toकरो));
पूर्ण

अटल bool binder_has_work(काष्ठा binder_thपढ़ो *thपढ़ो, bool करो_proc_work)
अणु
	bool has_work;

	binder_inner_proc_lock(thपढ़ो->proc);
	has_work = binder_has_work_ilocked(thपढ़ो, करो_proc_work);
	binder_inner_proc_unlock(thपढ़ो->proc);

	वापस has_work;
पूर्ण

अटल bool binder_available_क्रम_proc_work_ilocked(काष्ठा binder_thपढ़ो *thपढ़ो)
अणु
	वापस !thपढ़ो->transaction_stack &&
		binder_worklist_empty_ilocked(&thपढ़ो->toकरो) &&
		(thपढ़ो->looper & (BINDER_LOOPER_STATE_ENTERED |
				   BINDER_LOOPER_STATE_REGISTERED));
पूर्ण

अटल व्योम binder_wakeup_poll_thपढ़ोs_ilocked(काष्ठा binder_proc *proc,
					       bool sync)
अणु
	काष्ठा rb_node *n;
	काष्ठा binder_thपढ़ो *thपढ़ो;

	क्रम (n = rb_first(&proc->thपढ़ोs); n != शून्य; n = rb_next(n)) अणु
		thपढ़ो = rb_entry(n, काष्ठा binder_thपढ़ो, rb_node);
		अगर (thपढ़ो->looper & BINDER_LOOPER_STATE_POLL &&
		    binder_available_क्रम_proc_work_ilocked(thपढ़ो)) अणु
			अगर (sync)
				wake_up_पूर्णांकerruptible_sync(&thपढ़ो->रुको);
			अन्यथा
				wake_up_पूर्णांकerruptible(&thपढ़ो->रुको);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * binder_select_thपढ़ो_ilocked() - selects a thपढ़ो क्रम करोing proc work.
 * @proc:	process to select a thपढ़ो from
 *
 * Note that calling this function moves the thपढ़ो off the रुकोing_thपढ़ोs
 * list, so it can only be woken up by the caller of this function, or a
 * संकेत. Thereक्रमe, callers *should* always wake up the thपढ़ो this function
 * वापसs.
 *
 * Return:	If there's a thपढ़ो currently रुकोing क्रम process work,
 *		वापसs that thपढ़ो. Otherwise वापसs शून्य.
 */
अटल काष्ठा binder_thपढ़ो *
binder_select_thपढ़ो_ilocked(काष्ठा binder_proc *proc)
अणु
	काष्ठा binder_thपढ़ो *thपढ़ो;

	निश्चित_spin_locked(&proc->inner_lock);
	thपढ़ो = list_first_entry_or_null(&proc->रुकोing_thपढ़ोs,
					  काष्ठा binder_thपढ़ो,
					  रुकोing_thपढ़ो_node);

	अगर (thपढ़ो)
		list_del_init(&thपढ़ो->रुकोing_thपढ़ो_node);

	वापस thपढ़ो;
पूर्ण

/**
 * binder_wakeup_thपढ़ो_ilocked() - wakes up a thपढ़ो क्रम करोing proc work.
 * @proc:	process to wake up a thपढ़ो in
 * @thपढ़ो:	specअगरic thपढ़ो to wake-up (may be शून्य)
 * @sync:	whether to करो a synchronous wake-up
 *
 * This function wakes up a thपढ़ो in the @proc process.
 * The caller may provide a specअगरic thपढ़ो to wake-up in
 * the @thपढ़ो parameter. If @thपढ़ो is शून्य, this function
 * will wake up thपढ़ोs that have called poll().
 *
 * Note that क्रम this function to work as expected, callers
 * should first call binder_select_thपढ़ो() to find a thपढ़ो
 * to handle the work (अगर they करोn't have a thपढ़ो alपढ़ोy),
 * and pass the result पूर्णांकo the @thपढ़ो parameter.
 */
अटल व्योम binder_wakeup_thपढ़ो_ilocked(काष्ठा binder_proc *proc,
					 काष्ठा binder_thपढ़ो *thपढ़ो,
					 bool sync)
अणु
	निश्चित_spin_locked(&proc->inner_lock);

	अगर (thपढ़ो) अणु
		अगर (sync)
			wake_up_पूर्णांकerruptible_sync(&thपढ़ो->रुको);
		अन्यथा
			wake_up_पूर्णांकerruptible(&thपढ़ो->रुको);
		वापस;
	पूर्ण

	/* Didn't find a thपढ़ो रुकोing क्रम proc work; this can happen
	 * in two scenarios:
	 * 1. All thपढ़ोs are busy handling transactions
	 *    In that हाल, one of those thपढ़ोs should call back पूर्णांकo
	 *    the kernel driver soon and pick up this work.
	 * 2. Thपढ़ोs are using the (e)poll पूर्णांकerface, in which हाल
	 *    they may be blocked on the रुकोqueue without having been
	 *    added to रुकोing_thपढ़ोs. For this हाल, we just iterate
	 *    over all thपढ़ोs not handling transaction work, and
	 *    wake them all up. We wake all because we करोn't know whether
	 *    a thपढ़ो that called पूर्णांकo (e)poll is handling non-binder
	 *    work currently.
	 */
	binder_wakeup_poll_thपढ़ोs_ilocked(proc, sync);
पूर्ण

अटल व्योम binder_wakeup_proc_ilocked(काष्ठा binder_proc *proc)
अणु
	काष्ठा binder_thपढ़ो *thपढ़ो = binder_select_thपढ़ो_ilocked(proc);

	binder_wakeup_thपढ़ो_ilocked(proc, thपढ़ो, /* sync = */false);
पूर्ण

अटल व्योम binder_set_nice(दीर्घ nice)
अणु
	दीर्घ min_nice;

	अगर (can_nice(current, nice)) अणु
		set_user_nice(current, nice);
		वापस;
	पूर्ण
	min_nice = rlimit_to_nice(rlimit(RLIMIT_NICE));
	binder_debug(BINDER_DEBUG_PRIORITY_CAP,
		     "%d: nice value %ld not allowed use %ld instead\n",
		      current->pid, nice, min_nice);
	set_user_nice(current, min_nice);
	अगर (min_nice <= MAX_NICE)
		वापस;
	binder_user_error("%d RLIMIT_NICE not set\n", current->pid);
पूर्ण

अटल काष्ठा binder_node *binder_get_node_ilocked(काष्ठा binder_proc *proc,
						   binder_uपूर्णांकptr_t ptr)
अणु
	काष्ठा rb_node *n = proc->nodes.rb_node;
	काष्ठा binder_node *node;

	निश्चित_spin_locked(&proc->inner_lock);

	जबतक (n) अणु
		node = rb_entry(n, काष्ठा binder_node, rb_node);

		अगर (ptr < node->ptr)
			n = n->rb_left;
		अन्यथा अगर (ptr > node->ptr)
			n = n->rb_right;
		अन्यथा अणु
			/*
			 * take an implicit weak reference
			 * to ensure node stays alive until
			 * call to binder_put_node()
			 */
			binder_inc_node_पंचांगpref_ilocked(node);
			वापस node;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा binder_node *binder_get_node(काष्ठा binder_proc *proc,
					   binder_uपूर्णांकptr_t ptr)
अणु
	काष्ठा binder_node *node;

	binder_inner_proc_lock(proc);
	node = binder_get_node_ilocked(proc, ptr);
	binder_inner_proc_unlock(proc);
	वापस node;
पूर्ण

अटल काष्ठा binder_node *binder_init_node_ilocked(
						काष्ठा binder_proc *proc,
						काष्ठा binder_node *new_node,
						काष्ठा flat_binder_object *fp)
अणु
	काष्ठा rb_node **p = &proc->nodes.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा binder_node *node;
	binder_uपूर्णांकptr_t ptr = fp ? fp->binder : 0;
	binder_uपूर्णांकptr_t cookie = fp ? fp->cookie : 0;
	__u32 flags = fp ? fp->flags : 0;

	निश्चित_spin_locked(&proc->inner_lock);

	जबतक (*p) अणु

		parent = *p;
		node = rb_entry(parent, काष्ठा binder_node, rb_node);

		अगर (ptr < node->ptr)
			p = &(*p)->rb_left;
		अन्यथा अगर (ptr > node->ptr)
			p = &(*p)->rb_right;
		अन्यथा अणु
			/*
			 * A matching node is alपढ़ोy in
			 * the rb tree. Abanकरोn the init
			 * and वापस it.
			 */
			binder_inc_node_पंचांगpref_ilocked(node);
			वापस node;
		पूर्ण
	पूर्ण
	node = new_node;
	binder_stats_created(BINDER_STAT_NODE);
	node->पंचांगp_refs++;
	rb_link_node(&node->rb_node, parent, p);
	rb_insert_color(&node->rb_node, &proc->nodes);
	node->debug_id = atomic_inc_वापस(&binder_last_id);
	node->proc = proc;
	node->ptr = ptr;
	node->cookie = cookie;
	node->work.type = BINDER_WORK_NODE;
	node->min_priority = flags & FLAT_BINDER_FLAG_PRIORITY_MASK;
	node->accept_fds = !!(flags & FLAT_BINDER_FLAG_ACCEPTS_FDS);
	node->txn_security_ctx = !!(flags & FLAT_BINDER_FLAG_TXN_SECURITY_CTX);
	spin_lock_init(&node->lock);
	INIT_LIST_HEAD(&node->work.entry);
	INIT_LIST_HEAD(&node->async_toकरो);
	binder_debug(BINDER_DEBUG_INTERNAL_REFS,
		     "%d:%d node %d u%016llx c%016llx created\n",
		     proc->pid, current->pid, node->debug_id,
		     (u64)node->ptr, (u64)node->cookie);

	वापस node;
पूर्ण

अटल काष्ठा binder_node *binder_new_node(काष्ठा binder_proc *proc,
					   काष्ठा flat_binder_object *fp)
अणु
	काष्ठा binder_node *node;
	काष्ठा binder_node *new_node = kzalloc(माप(*node), GFP_KERNEL);

	अगर (!new_node)
		वापस शून्य;
	binder_inner_proc_lock(proc);
	node = binder_init_node_ilocked(proc, new_node, fp);
	binder_inner_proc_unlock(proc);
	अगर (node != new_node)
		/*
		 * The node was alपढ़ोy added by another thपढ़ो
		 */
		kमुक्त(new_node);

	वापस node;
पूर्ण

अटल व्योम binder_मुक्त_node(काष्ठा binder_node *node)
अणु
	kमुक्त(node);
	binder_stats_deleted(BINDER_STAT_NODE);
पूर्ण

अटल पूर्णांक binder_inc_node_nilocked(काष्ठा binder_node *node, पूर्णांक strong,
				    पूर्णांक पूर्णांकernal,
				    काष्ठा list_head *target_list)
अणु
	काष्ठा binder_proc *proc = node->proc;

	निश्चित_spin_locked(&node->lock);
	अगर (proc)
		निश्चित_spin_locked(&proc->inner_lock);
	अगर (strong) अणु
		अगर (पूर्णांकernal) अणु
			अगर (target_list == शून्य &&
			    node->पूर्णांकernal_strong_refs == 0 &&
			    !(node->proc &&
			      node == node->proc->context->binder_context_mgr_node &&
			      node->has_strong_ref)) अणु
				pr_err("invalid inc strong node for %d\n",
					node->debug_id);
				वापस -EINVAL;
			पूर्ण
			node->पूर्णांकernal_strong_refs++;
		पूर्ण अन्यथा
			node->local_strong_refs++;
		अगर (!node->has_strong_ref && target_list) अणु
			काष्ठा binder_thपढ़ो *thपढ़ो = container_of(target_list,
						    काष्ठा binder_thपढ़ो, toकरो);
			binder_dequeue_work_ilocked(&node->work);
			BUG_ON(&thपढ़ो->toकरो != target_list);
			binder_enqueue_deferred_thपढ़ो_work_ilocked(thपढ़ो,
								   &node->work);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!पूर्णांकernal)
			node->local_weak_refs++;
		अगर (!node->has_weak_ref && list_empty(&node->work.entry)) अणु
			अगर (target_list == शून्य) अणु
				pr_err("invalid inc weak node for %d\n",
					node->debug_id);
				वापस -EINVAL;
			पूर्ण
			/*
			 * See comment above
			 */
			binder_enqueue_work_ilocked(&node->work, target_list);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक binder_inc_node(काष्ठा binder_node *node, पूर्णांक strong, पूर्णांक पूर्णांकernal,
			   काष्ठा list_head *target_list)
अणु
	पूर्णांक ret;

	binder_node_inner_lock(node);
	ret = binder_inc_node_nilocked(node, strong, पूर्णांकernal, target_list);
	binder_node_inner_unlock(node);

	वापस ret;
पूर्ण

अटल bool binder_dec_node_nilocked(काष्ठा binder_node *node,
				     पूर्णांक strong, पूर्णांक पूर्णांकernal)
अणु
	काष्ठा binder_proc *proc = node->proc;

	निश्चित_spin_locked(&node->lock);
	अगर (proc)
		निश्चित_spin_locked(&proc->inner_lock);
	अगर (strong) अणु
		अगर (पूर्णांकernal)
			node->पूर्णांकernal_strong_refs--;
		अन्यथा
			node->local_strong_refs--;
		अगर (node->local_strong_refs || node->पूर्णांकernal_strong_refs)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (!पूर्णांकernal)
			node->local_weak_refs--;
		अगर (node->local_weak_refs || node->पंचांगp_refs ||
				!hlist_empty(&node->refs))
			वापस false;
	पूर्ण

	अगर (proc && (node->has_strong_ref || node->has_weak_ref)) अणु
		अगर (list_empty(&node->work.entry)) अणु
			binder_enqueue_work_ilocked(&node->work, &proc->toकरो);
			binder_wakeup_proc_ilocked(proc);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hlist_empty(&node->refs) && !node->local_strong_refs &&
		    !node->local_weak_refs && !node->पंचांगp_refs) अणु
			अगर (proc) अणु
				binder_dequeue_work_ilocked(&node->work);
				rb_erase(&node->rb_node, &proc->nodes);
				binder_debug(BINDER_DEBUG_INTERNAL_REFS,
					     "refless node %d deleted\n",
					     node->debug_id);
			पूर्ण अन्यथा अणु
				BUG_ON(!list_empty(&node->work.entry));
				spin_lock(&binder_dead_nodes_lock);
				/*
				 * पंचांगp_refs could have changed so
				 * check it again
				 */
				अगर (node->पंचांगp_refs) अणु
					spin_unlock(&binder_dead_nodes_lock);
					वापस false;
				पूर्ण
				hlist_del(&node->dead_node);
				spin_unlock(&binder_dead_nodes_lock);
				binder_debug(BINDER_DEBUG_INTERNAL_REFS,
					     "dead node %d deleted\n",
					     node->debug_id);
			पूर्ण
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम binder_dec_node(काष्ठा binder_node *node, पूर्णांक strong, पूर्णांक पूर्णांकernal)
अणु
	bool मुक्त_node;

	binder_node_inner_lock(node);
	मुक्त_node = binder_dec_node_nilocked(node, strong, पूर्णांकernal);
	binder_node_inner_unlock(node);
	अगर (मुक्त_node)
		binder_मुक्त_node(node);
पूर्ण

अटल व्योम binder_inc_node_पंचांगpref_ilocked(काष्ठा binder_node *node)
अणु
	/*
	 * No call to binder_inc_node() is needed since we
	 * करोn't need to inक्रमm userspace of any changes to
	 * पंचांगp_refs
	 */
	node->पंचांगp_refs++;
पूर्ण

/**
 * binder_inc_node_पंचांगpref() - take a temporary reference on node
 * @node:	node to reference
 *
 * Take reference on node to prevent the node from being मुक्तd
 * जबतक referenced only by a local variable. The inner lock is
 * needed to serialize with the node work on the queue (which
 * isn't needed after the node is dead). If the node is dead
 * (node->proc is शून्य), use binder_dead_nodes_lock to protect
 * node->पंचांगp_refs against dead-node-only हालs where the node
 * lock cannot be acquired (eg traversing the dead node list to
 * prपूर्णांक nodes)
 */
अटल व्योम binder_inc_node_पंचांगpref(काष्ठा binder_node *node)
अणु
	binder_node_lock(node);
	अगर (node->proc)
		binder_inner_proc_lock(node->proc);
	अन्यथा
		spin_lock(&binder_dead_nodes_lock);
	binder_inc_node_पंचांगpref_ilocked(node);
	अगर (node->proc)
		binder_inner_proc_unlock(node->proc);
	अन्यथा
		spin_unlock(&binder_dead_nodes_lock);
	binder_node_unlock(node);
पूर्ण

/**
 * binder_dec_node_पंचांगpref() - हटाओ a temporary reference on node
 * @node:	node to reference
 *
 * Release temporary reference on node taken via binder_inc_node_पंचांगpref()
 */
अटल व्योम binder_dec_node_पंचांगpref(काष्ठा binder_node *node)
अणु
	bool मुक्त_node;

	binder_node_inner_lock(node);
	अगर (!node->proc)
		spin_lock(&binder_dead_nodes_lock);
	अन्यथा
		__acquire(&binder_dead_nodes_lock);
	node->पंचांगp_refs--;
	BUG_ON(node->पंचांगp_refs < 0);
	अगर (!node->proc)
		spin_unlock(&binder_dead_nodes_lock);
	अन्यथा
		__release(&binder_dead_nodes_lock);
	/*
	 * Call binder_dec_node() to check अगर all refcounts are 0
	 * and cleanup is needed. Calling with strong=0 and पूर्णांकernal=1
	 * causes no actual reference to be released in binder_dec_node().
	 * If that changes, a change is needed here too.
	 */
	मुक्त_node = binder_dec_node_nilocked(node, 0, 1);
	binder_node_inner_unlock(node);
	अगर (मुक्त_node)
		binder_मुक्त_node(node);
पूर्ण

अटल व्योम binder_put_node(काष्ठा binder_node *node)
अणु
	binder_dec_node_पंचांगpref(node);
पूर्ण

अटल काष्ठा binder_ref *binder_get_ref_olocked(काष्ठा binder_proc *proc,
						 u32 desc, bool need_strong_ref)
अणु
	काष्ठा rb_node *n = proc->refs_by_desc.rb_node;
	काष्ठा binder_ref *ref;

	जबतक (n) अणु
		ref = rb_entry(n, काष्ठा binder_ref, rb_node_desc);

		अगर (desc < ref->data.desc) अणु
			n = n->rb_left;
		पूर्ण अन्यथा अगर (desc > ref->data.desc) अणु
			n = n->rb_right;
		पूर्ण अन्यथा अगर (need_strong_ref && !ref->data.strong) अणु
			binder_user_error("tried to use weak ref as strong ref\n");
			वापस शून्य;
		पूर्ण अन्यथा अणु
			वापस ref;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * binder_get_ref_क्रम_node_olocked() - get the ref associated with given node
 * @proc:	binder_proc that owns the ref
 * @node:	binder_node of target
 * @new_ref:	newly allocated binder_ref to be initialized or %शून्य
 *
 * Look up the ref क्रम the given node and वापस it अगर it exists
 *
 * If it करोesn't exist and the caller provides a newly allocated
 * ref, initialize the fields of the newly allocated ref and insert
 * पूर्णांकo the given proc rb_trees and node refs list.
 *
 * Return:	the ref क्रम node. It is possible that another thपढ़ो
 *		allocated/initialized the ref first in which हाल the
 *		वापसed ref would be dअगरferent than the passed-in
 *		new_ref. new_ref must be kमुक्त'd by the caller in
 *		this हाल.
 */
अटल काष्ठा binder_ref *binder_get_ref_क्रम_node_olocked(
					काष्ठा binder_proc *proc,
					काष्ठा binder_node *node,
					काष्ठा binder_ref *new_ref)
अणु
	काष्ठा binder_context *context = proc->context;
	काष्ठा rb_node **p = &proc->refs_by_node.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा binder_ref *ref;
	काष्ठा rb_node *n;

	जबतक (*p) अणु
		parent = *p;
		ref = rb_entry(parent, काष्ठा binder_ref, rb_node_node);

		अगर (node < ref->node)
			p = &(*p)->rb_left;
		अन्यथा अगर (node > ref->node)
			p = &(*p)->rb_right;
		अन्यथा
			वापस ref;
	पूर्ण
	अगर (!new_ref)
		वापस शून्य;

	binder_stats_created(BINDER_STAT_REF);
	new_ref->data.debug_id = atomic_inc_वापस(&binder_last_id);
	new_ref->proc = proc;
	new_ref->node = node;
	rb_link_node(&new_ref->rb_node_node, parent, p);
	rb_insert_color(&new_ref->rb_node_node, &proc->refs_by_node);

	new_ref->data.desc = (node == context->binder_context_mgr_node) ? 0 : 1;
	क्रम (n = rb_first(&proc->refs_by_desc); n != शून्य; n = rb_next(n)) अणु
		ref = rb_entry(n, काष्ठा binder_ref, rb_node_desc);
		अगर (ref->data.desc > new_ref->data.desc)
			अवरोध;
		new_ref->data.desc = ref->data.desc + 1;
	पूर्ण

	p = &proc->refs_by_desc.rb_node;
	जबतक (*p) अणु
		parent = *p;
		ref = rb_entry(parent, काष्ठा binder_ref, rb_node_desc);

		अगर (new_ref->data.desc < ref->data.desc)
			p = &(*p)->rb_left;
		अन्यथा अगर (new_ref->data.desc > ref->data.desc)
			p = &(*p)->rb_right;
		अन्यथा
			BUG();
	पूर्ण
	rb_link_node(&new_ref->rb_node_desc, parent, p);
	rb_insert_color(&new_ref->rb_node_desc, &proc->refs_by_desc);

	binder_node_lock(node);
	hlist_add_head(&new_ref->node_entry, &node->refs);

	binder_debug(BINDER_DEBUG_INTERNAL_REFS,
		     "%d new ref %d desc %d for node %d\n",
		      proc->pid, new_ref->data.debug_id, new_ref->data.desc,
		      node->debug_id);
	binder_node_unlock(node);
	वापस new_ref;
पूर्ण

अटल व्योम binder_cleanup_ref_olocked(काष्ठा binder_ref *ref)
अणु
	bool delete_node = false;

	binder_debug(BINDER_DEBUG_INTERNAL_REFS,
		     "%d delete ref %d desc %d for node %d\n",
		      ref->proc->pid, ref->data.debug_id, ref->data.desc,
		      ref->node->debug_id);

	rb_erase(&ref->rb_node_desc, &ref->proc->refs_by_desc);
	rb_erase(&ref->rb_node_node, &ref->proc->refs_by_node);

	binder_node_inner_lock(ref->node);
	अगर (ref->data.strong)
		binder_dec_node_nilocked(ref->node, 1, 1);

	hlist_del(&ref->node_entry);
	delete_node = binder_dec_node_nilocked(ref->node, 0, 1);
	binder_node_inner_unlock(ref->node);
	/*
	 * Clear ref->node unless we want the caller to मुक्त the node
	 */
	अगर (!delete_node) अणु
		/*
		 * The caller uses ref->node to determine
		 * whether the node needs to be मुक्तd. Clear
		 * it since the node is still alive.
		 */
		ref->node = शून्य;
	पूर्ण

	अगर (ref->death) अणु
		binder_debug(BINDER_DEBUG_DEAD_BINDER,
			     "%d delete ref %d desc %d has death notification\n",
			      ref->proc->pid, ref->data.debug_id,
			      ref->data.desc);
		binder_dequeue_work(ref->proc, &ref->death->work);
		binder_stats_deleted(BINDER_STAT_DEATH);
	पूर्ण
	binder_stats_deleted(BINDER_STAT_REF);
पूर्ण

/**
 * binder_inc_ref_olocked() - increment the ref क्रम given handle
 * @ref:         ref to be incremented
 * @strong:      अगर true, strong increment, अन्यथा weak
 * @target_list: list to queue node work on
 *
 * Increment the ref. @ref->proc->outer_lock must be held on entry
 *
 * Return: 0, अगर successful, अन्यथा त्रुटि_सं
 */
अटल पूर्णांक binder_inc_ref_olocked(काष्ठा binder_ref *ref, पूर्णांक strong,
				  काष्ठा list_head *target_list)
अणु
	पूर्णांक ret;

	अगर (strong) अणु
		अगर (ref->data.strong == 0) अणु
			ret = binder_inc_node(ref->node, 1, 1, target_list);
			अगर (ret)
				वापस ret;
		पूर्ण
		ref->data.strong++;
	पूर्ण अन्यथा अणु
		अगर (ref->data.weak == 0) अणु
			ret = binder_inc_node(ref->node, 0, 1, target_list);
			अगर (ret)
				वापस ret;
		पूर्ण
		ref->data.weak++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * binder_dec_ref() - dec the ref क्रम given handle
 * @ref:	ref to be decremented
 * @strong:	अगर true, strong decrement, अन्यथा weak
 *
 * Decrement the ref.
 *
 * Return: true अगर ref is cleaned up and पढ़ोy to be मुक्तd
 */
अटल bool binder_dec_ref_olocked(काष्ठा binder_ref *ref, पूर्णांक strong)
अणु
	अगर (strong) अणु
		अगर (ref->data.strong == 0) अणु
			binder_user_error("%d invalid dec strong, ref %d desc %d s %d w %d\n",
					  ref->proc->pid, ref->data.debug_id,
					  ref->data.desc, ref->data.strong,
					  ref->data.weak);
			वापस false;
		पूर्ण
		ref->data.strong--;
		अगर (ref->data.strong == 0)
			binder_dec_node(ref->node, strong, 1);
	पूर्ण अन्यथा अणु
		अगर (ref->data.weak == 0) अणु
			binder_user_error("%d invalid dec weak, ref %d desc %d s %d w %d\n",
					  ref->proc->pid, ref->data.debug_id,
					  ref->data.desc, ref->data.strong,
					  ref->data.weak);
			वापस false;
		पूर्ण
		ref->data.weak--;
	पूर्ण
	अगर (ref->data.strong == 0 && ref->data.weak == 0) अणु
		binder_cleanup_ref_olocked(ref);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * binder_get_node_from_ref() - get the node from the given proc/desc
 * @proc:	proc containing the ref
 * @desc:	the handle associated with the ref
 * @need_strong_ref: अगर true, only वापस node अगर ref is strong
 * @rdata:	the id/refcount data क्रम the ref
 *
 * Given a proc and ref handle, वापस the associated binder_node
 *
 * Return: a binder_node or शून्य अगर not found or not strong when strong required
 */
अटल काष्ठा binder_node *binder_get_node_from_ref(
		काष्ठा binder_proc *proc,
		u32 desc, bool need_strong_ref,
		काष्ठा binder_ref_data *rdata)
अणु
	काष्ठा binder_node *node;
	काष्ठा binder_ref *ref;

	binder_proc_lock(proc);
	ref = binder_get_ref_olocked(proc, desc, need_strong_ref);
	अगर (!ref)
		जाओ err_no_ref;
	node = ref->node;
	/*
	 * Take an implicit reference on the node to ensure
	 * it stays alive until the call to binder_put_node()
	 */
	binder_inc_node_पंचांगpref(node);
	अगर (rdata)
		*rdata = ref->data;
	binder_proc_unlock(proc);

	वापस node;

err_no_ref:
	binder_proc_unlock(proc);
	वापस शून्य;
पूर्ण

/**
 * binder_मुक्त_ref() - मुक्त the binder_ref
 * @ref:	ref to मुक्त
 *
 * Free the binder_ref. Free the binder_node indicated by ref->node
 * (अगर non-शून्य) and the binder_ref_death indicated by ref->death.
 */
अटल व्योम binder_मुक्त_ref(काष्ठा binder_ref *ref)
अणु
	अगर (ref->node)
		binder_मुक्त_node(ref->node);
	kमुक्त(ref->death);
	kमुक्त(ref);
पूर्ण

/**
 * binder_update_ref_क्रम_handle() - inc/dec the ref क्रम given handle
 * @proc:	proc containing the ref
 * @desc:	the handle associated with the ref
 * @increment:	true=inc reference, false=dec reference
 * @strong:	true=strong reference, false=weak reference
 * @rdata:	the id/refcount data क्रम the ref
 *
 * Given a proc and ref handle, increment or decrement the ref
 * according to "increment" arg.
 *
 * Return: 0 अगर successful, अन्यथा त्रुटि_सं
 */
अटल पूर्णांक binder_update_ref_क्रम_handle(काष्ठा binder_proc *proc,
		uपूर्णांक32_t desc, bool increment, bool strong,
		काष्ठा binder_ref_data *rdata)
अणु
	पूर्णांक ret = 0;
	काष्ठा binder_ref *ref;
	bool delete_ref = false;

	binder_proc_lock(proc);
	ref = binder_get_ref_olocked(proc, desc, strong);
	अगर (!ref) अणु
		ret = -EINVAL;
		जाओ err_no_ref;
	पूर्ण
	अगर (increment)
		ret = binder_inc_ref_olocked(ref, strong, शून्य);
	अन्यथा
		delete_ref = binder_dec_ref_olocked(ref, strong);

	अगर (rdata)
		*rdata = ref->data;
	binder_proc_unlock(proc);

	अगर (delete_ref)
		binder_मुक्त_ref(ref);
	वापस ret;

err_no_ref:
	binder_proc_unlock(proc);
	वापस ret;
पूर्ण

/**
 * binder_dec_ref_क्रम_handle() - dec the ref क्रम given handle
 * @proc:	proc containing the ref
 * @desc:	the handle associated with the ref
 * @strong:	true=strong reference, false=weak reference
 * @rdata:	the id/refcount data क्रम the ref
 *
 * Just calls binder_update_ref_क्रम_handle() to decrement the ref.
 *
 * Return: 0 अगर successful, अन्यथा त्रुटि_सं
 */
अटल पूर्णांक binder_dec_ref_क्रम_handle(काष्ठा binder_proc *proc,
		uपूर्णांक32_t desc, bool strong, काष्ठा binder_ref_data *rdata)
अणु
	वापस binder_update_ref_क्रम_handle(proc, desc, false, strong, rdata);
पूर्ण


/**
 * binder_inc_ref_क्रम_node() - increment the ref क्रम given proc/node
 * @proc:	 proc containing the ref
 * @node:	 target node
 * @strong:	 true=strong reference, false=weak reference
 * @target_list: worklist to use अगर node is incremented
 * @rdata:	 the id/refcount data क्रम the ref
 *
 * Given a proc and node, increment the ref. Create the ref अगर it
 * करोesn't alपढ़ोy exist
 *
 * Return: 0 अगर successful, अन्यथा त्रुटि_सं
 */
अटल पूर्णांक binder_inc_ref_क्रम_node(काष्ठा binder_proc *proc,
			काष्ठा binder_node *node,
			bool strong,
			काष्ठा list_head *target_list,
			काष्ठा binder_ref_data *rdata)
अणु
	काष्ठा binder_ref *ref;
	काष्ठा binder_ref *new_ref = शून्य;
	पूर्णांक ret = 0;

	binder_proc_lock(proc);
	ref = binder_get_ref_क्रम_node_olocked(proc, node, शून्य);
	अगर (!ref) अणु
		binder_proc_unlock(proc);
		new_ref = kzalloc(माप(*ref), GFP_KERNEL);
		अगर (!new_ref)
			वापस -ENOMEM;
		binder_proc_lock(proc);
		ref = binder_get_ref_क्रम_node_olocked(proc, node, new_ref);
	पूर्ण
	ret = binder_inc_ref_olocked(ref, strong, target_list);
	*rdata = ref->data;
	binder_proc_unlock(proc);
	अगर (new_ref && ref != new_ref)
		/*
		 * Another thपढ़ो created the ref first so
		 * मुक्त the one we allocated
		 */
		kमुक्त(new_ref);
	वापस ret;
पूर्ण

अटल व्योम binder_pop_transaction_ilocked(काष्ठा binder_thपढ़ो *target_thपढ़ो,
					   काष्ठा binder_transaction *t)
अणु
	BUG_ON(!target_thपढ़ो);
	निश्चित_spin_locked(&target_thपढ़ो->proc->inner_lock);
	BUG_ON(target_thपढ़ो->transaction_stack != t);
	BUG_ON(target_thपढ़ो->transaction_stack->from != target_thपढ़ो);
	target_thपढ़ो->transaction_stack =
		target_thपढ़ो->transaction_stack->from_parent;
	t->from = शून्य;
पूर्ण

/**
 * binder_thपढ़ो_dec_पंचांगpref() - decrement thपढ़ो->पंचांगp_ref
 * @thपढ़ो:	thपढ़ो to decrement
 *
 * A thपढ़ो needs to be kept alive जबतक being used to create or
 * handle a transaction. binder_get_txn_from() is used to safely
 * extract t->from from a binder_transaction and keep the thपढ़ो
 * indicated by t->from from being मुक्तd. When करोne with that
 * binder_thपढ़ो, this function is called to decrement the
 * पंचांगp_ref and मुक्त अगर appropriate (thपढ़ो has been released
 * and no transaction being processed by the driver)
 */
अटल व्योम binder_thपढ़ो_dec_पंचांगpref(काष्ठा binder_thपढ़ो *thपढ़ो)
अणु
	/*
	 * atomic is used to protect the counter value जबतक
	 * it cannot reach zero or thपढ़ो->is_dead is false
	 */
	binder_inner_proc_lock(thपढ़ो->proc);
	atomic_dec(&thपढ़ो->पंचांगp_ref);
	अगर (thपढ़ो->is_dead && !atomic_पढ़ो(&thपढ़ो->पंचांगp_ref)) अणु
		binder_inner_proc_unlock(thपढ़ो->proc);
		binder_मुक्त_thपढ़ो(thपढ़ो);
		वापस;
	पूर्ण
	binder_inner_proc_unlock(thपढ़ो->proc);
पूर्ण

/**
 * binder_proc_dec_पंचांगpref() - decrement proc->पंचांगp_ref
 * @proc:	proc to decrement
 *
 * A binder_proc needs to be kept alive जबतक being used to create or
 * handle a transaction. proc->पंचांगp_ref is incremented when
 * creating a new transaction or the binder_proc is currently in-use
 * by thपढ़ोs that are being released. When करोne with the binder_proc,
 * this function is called to decrement the counter and मुक्त the
 * proc अगर appropriate (proc has been released, all thपढ़ोs have
 * been released and not currenly in-use to process a transaction).
 */
अटल व्योम binder_proc_dec_पंचांगpref(काष्ठा binder_proc *proc)
अणु
	binder_inner_proc_lock(proc);
	proc->पंचांगp_ref--;
	अगर (proc->is_dead && RB_EMPTY_ROOT(&proc->thपढ़ोs) &&
			!proc->पंचांगp_ref) अणु
		binder_inner_proc_unlock(proc);
		binder_मुक्त_proc(proc);
		वापस;
	पूर्ण
	binder_inner_proc_unlock(proc);
पूर्ण

/**
 * binder_get_txn_from() - safely extract the "from" thपढ़ो in transaction
 * @t:	binder transaction क्रम t->from
 *
 * Atomically वापस the "from" thपढ़ो and increment the पंचांगp_ref
 * count क्रम the thपढ़ो to ensure it stays alive until
 * binder_thपढ़ो_dec_पंचांगpref() is called.
 *
 * Return: the value of t->from
 */
अटल काष्ठा binder_thपढ़ो *binder_get_txn_from(
		काष्ठा binder_transaction *t)
अणु
	काष्ठा binder_thपढ़ो *from;

	spin_lock(&t->lock);
	from = t->from;
	अगर (from)
		atomic_inc(&from->पंचांगp_ref);
	spin_unlock(&t->lock);
	वापस from;
पूर्ण

/**
 * binder_get_txn_from_and_acq_inner() - get t->from and acquire inner lock
 * @t:	binder transaction क्रम t->from
 *
 * Same as binder_get_txn_from() except it also acquires the proc->inner_lock
 * to guarantee that the thपढ़ो cannot be released जबतक operating on it.
 * The caller must call binder_inner_proc_unlock() to release the inner lock
 * as well as call binder_dec_thपढ़ो_txn() to release the reference.
 *
 * Return: the value of t->from
 */
अटल काष्ठा binder_thपढ़ो *binder_get_txn_from_and_acq_inner(
		काष्ठा binder_transaction *t)
	__acquires(&t->from->proc->inner_lock)
अणु
	काष्ठा binder_thपढ़ो *from;

	from = binder_get_txn_from(t);
	अगर (!from) अणु
		__acquire(&from->proc->inner_lock);
		वापस शून्य;
	पूर्ण
	binder_inner_proc_lock(from->proc);
	अगर (t->from) अणु
		BUG_ON(from != t->from);
		वापस from;
	पूर्ण
	binder_inner_proc_unlock(from->proc);
	__acquire(&from->proc->inner_lock);
	binder_thपढ़ो_dec_पंचांगpref(from);
	वापस शून्य;
पूर्ण

/**
 * binder_मुक्त_txn_fixups() - मुक्त unprocessed fd fixups
 * @t:	binder transaction क्रम t->from
 *
 * If the transaction is being torn करोwn prior to being
 * processed by the target process, मुक्त all of the
 * fd fixups and fput the file काष्ठाs. It is safe to
 * call this function after the fixups have been
 * processed -- in that हाल, the list will be empty.
 */
अटल व्योम binder_मुक्त_txn_fixups(काष्ठा binder_transaction *t)
अणु
	काष्ठा binder_txn_fd_fixup *fixup, *पंचांगp;

	list_क्रम_each_entry_safe(fixup, पंचांगp, &t->fd_fixups, fixup_entry) अणु
		fput(fixup->file);
		list_del(&fixup->fixup_entry);
		kमुक्त(fixup);
	पूर्ण
पूर्ण

अटल व्योम binder_txn_latency_मुक्त(काष्ठा binder_transaction *t)
अणु
	पूर्णांक from_proc, from_thपढ़ो, to_proc, to_thपढ़ो;

	spin_lock(&t->lock);
	from_proc = t->from ? t->from->proc->pid : 0;
	from_thपढ़ो = t->from ? t->from->pid : 0;
	to_proc = t->to_proc ? t->to_proc->pid : 0;
	to_thपढ़ो = t->to_thपढ़ो ? t->to_thपढ़ो->pid : 0;
	spin_unlock(&t->lock);

	trace_binder_txn_latency_मुक्त(t, from_proc, from_thपढ़ो, to_proc, to_thपढ़ो);
पूर्ण

अटल व्योम binder_मुक्त_transaction(काष्ठा binder_transaction *t)
अणु
	काष्ठा binder_proc *target_proc = t->to_proc;

	अगर (target_proc) अणु
		binder_inner_proc_lock(target_proc);
		target_proc->outstanding_txns--;
		अगर (target_proc->outstanding_txns < 0)
			pr_warn("%s: Unexpected outstanding_txns %d\n",
				__func__, target_proc->outstanding_txns);
		अगर (!target_proc->outstanding_txns && target_proc->is_frozen)
			wake_up_पूर्णांकerruptible_all(&target_proc->मुक्तze_रुको);
		अगर (t->buffer)
			t->buffer->transaction = शून्य;
		binder_inner_proc_unlock(target_proc);
	पूर्ण
	अगर (trace_binder_txn_latency_मुक्त_enabled())
		binder_txn_latency_मुक्त(t);
	/*
	 * If the transaction has no target_proc, then
	 * t->buffer->transaction has alपढ़ोy been cleared.
	 */
	binder_मुक्त_txn_fixups(t);
	kमुक्त(t);
	binder_stats_deleted(BINDER_STAT_TRANSACTION);
पूर्ण

अटल व्योम binder_send_failed_reply(काष्ठा binder_transaction *t,
				     uपूर्णांक32_t error_code)
अणु
	काष्ठा binder_thपढ़ो *target_thपढ़ो;
	काष्ठा binder_transaction *next;

	BUG_ON(t->flags & TF_ONE_WAY);
	जबतक (1) अणु
		target_thपढ़ो = binder_get_txn_from_and_acq_inner(t);
		अगर (target_thपढ़ो) अणु
			binder_debug(BINDER_DEBUG_FAILED_TRANSACTION,
				     "send failed reply for transaction %d to %d:%d\n",
				      t->debug_id,
				      target_thपढ़ो->proc->pid,
				      target_thपढ़ो->pid);

			binder_pop_transaction_ilocked(target_thपढ़ो, t);
			अगर (target_thपढ़ो->reply_error.cmd == BR_OK) अणु
				target_thपढ़ो->reply_error.cmd = error_code;
				binder_enqueue_thपढ़ो_work_ilocked(
					target_thपढ़ो,
					&target_thपढ़ो->reply_error.work);
				wake_up_पूर्णांकerruptible(&target_thपढ़ो->रुको);
			पूर्ण अन्यथा अणु
				/*
				 * Cannot get here क्रम normal operation, but
				 * we can अगर multiple synchronous transactions
				 * are sent without blocking क्रम responses.
				 * Just ignore the 2nd error in this हाल.
				 */
				pr_warn("Unexpected reply error: %u\n",
					target_thपढ़ो->reply_error.cmd);
			पूर्ण
			binder_inner_proc_unlock(target_thपढ़ो->proc);
			binder_thपढ़ो_dec_पंचांगpref(target_thपढ़ो);
			binder_मुक्त_transaction(t);
			वापस;
		पूर्ण
		__release(&target_thपढ़ो->proc->inner_lock);
		next = t->from_parent;

		binder_debug(BINDER_DEBUG_FAILED_TRANSACTION,
			     "send failed reply for transaction %d, target dead\n",
			     t->debug_id);

		binder_मुक्त_transaction(t);
		अगर (next == शून्य) अणु
			binder_debug(BINDER_DEBUG_DEAD_BINDER,
				     "reply failed, no target thread at root\n");
			वापस;
		पूर्ण
		t = next;
		binder_debug(BINDER_DEBUG_DEAD_BINDER,
			     "reply failed, no target thread -- retry %d\n",
			      t->debug_id);
	पूर्ण
पूर्ण

/**
 * binder_cleanup_transaction() - cleans up undelivered transaction
 * @t:		transaction that needs to be cleaned up
 * @reason:	reason the transaction wasn't delivered
 * @error_code:	error to वापस to caller (अगर synchronous call)
 */
अटल व्योम binder_cleanup_transaction(काष्ठा binder_transaction *t,
				       स्थिर अक्षर *reason,
				       uपूर्णांक32_t error_code)
अणु
	अगर (t->buffer->target_node && !(t->flags & TF_ONE_WAY)) अणु
		binder_send_failed_reply(t, error_code);
	पूर्ण अन्यथा अणु
		binder_debug(BINDER_DEBUG_DEAD_TRANSACTION,
			"undelivered transaction %d, %s\n",
			t->debug_id, reason);
		binder_मुक्त_transaction(t);
	पूर्ण
पूर्ण

/**
 * binder_get_object() - माला_लो object and checks क्रम valid metadata
 * @proc:	binder_proc owning the buffer
 * @buffer:	binder_buffer that we're parsing.
 * @offset:	offset in the @buffer at which to validate an object.
 * @object:	काष्ठा binder_object to पढ़ो पूर्णांकo
 *
 * Return:	If there's a valid metadata object at @offset in @buffer, the
 *		size of that object. Otherwise, it वापसs zero. The object
 *		is पढ़ो पूर्णांकo the काष्ठा binder_object poपूर्णांकed to by @object.
 */
अटल माप_प्रकार binder_get_object(काष्ठा binder_proc *proc,
				काष्ठा binder_buffer *buffer,
				अचिन्हित दीर्घ offset,
				काष्ठा binder_object *object)
अणु
	माप_प्रकार पढ़ो_size;
	काष्ठा binder_object_header *hdr;
	माप_प्रकार object_size = 0;

	पढ़ो_size = min_t(माप_प्रकार, माप(*object), buffer->data_size - offset);
	अगर (offset > buffer->data_size || पढ़ो_size < माप(*hdr) ||
	    binder_alloc_copy_from_buffer(&proc->alloc, object, buffer,
					  offset, पढ़ो_size))
		वापस 0;

	/* Ok, now see अगर we पढ़ो a complete object. */
	hdr = &object->hdr;
	चयन (hdr->type) अणु
	हाल BINDER_TYPE_BINDER:
	हाल BINDER_TYPE_WEAK_BINDER:
	हाल BINDER_TYPE_HANDLE:
	हाल BINDER_TYPE_WEAK_HANDLE:
		object_size = माप(काष्ठा flat_binder_object);
		अवरोध;
	हाल BINDER_TYPE_FD:
		object_size = माप(काष्ठा binder_fd_object);
		अवरोध;
	हाल BINDER_TYPE_PTR:
		object_size = माप(काष्ठा binder_buffer_object);
		अवरोध;
	हाल BINDER_TYPE_FDA:
		object_size = माप(काष्ठा binder_fd_array_object);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	अगर (offset <= buffer->data_size - object_size &&
	    buffer->data_size >= object_size)
		वापस object_size;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * binder_validate_ptr() - validates binder_buffer_object in a binder_buffer.
 * @proc:	binder_proc owning the buffer
 * @b:		binder_buffer containing the object
 * @object:	काष्ठा binder_object to पढ़ो पूर्णांकo
 * @index:	index in offset array at which the binder_buffer_object is
 *		located
 * @start_offset: poपूर्णांकs to the start of the offset array
 * @object_offsetp: offset of @object पढ़ो from @b
 * @num_valid:	the number of valid offsets in the offset array
 *
 * Return:	If @index is within the valid range of the offset array
 *		described by @start and @num_valid, and अगर there's a valid
 *		binder_buffer_object at the offset found in index @index
 *		of the offset array, that object is वापसed. Otherwise,
 *		%शून्य is वापसed.
 *		Note that the offset found in index @index itself is not
 *		verअगरied; this function assumes that @num_valid elements
 *		from @start were previously verअगरied to have valid offsets.
 *		If @object_offsetp is non-शून्य, then the offset within
 *		@b is written to it.
 */
अटल काष्ठा binder_buffer_object *binder_validate_ptr(
						काष्ठा binder_proc *proc,
						काष्ठा binder_buffer *b,
						काष्ठा binder_object *object,
						binder_माप_प्रकार index,
						binder_माप_प्रकार start_offset,
						binder_माप_प्रकार *object_offsetp,
						binder_माप_प्रकार num_valid)
अणु
	माप_प्रकार object_size;
	binder_माप_प्रकार object_offset;
	अचिन्हित दीर्घ buffer_offset;

	अगर (index >= num_valid)
		वापस शून्य;

	buffer_offset = start_offset + माप(binder_माप_प्रकार) * index;
	अगर (binder_alloc_copy_from_buffer(&proc->alloc, &object_offset,
					  b, buffer_offset,
					  माप(object_offset)))
		वापस शून्य;
	object_size = binder_get_object(proc, b, object_offset, object);
	अगर (!object_size || object->hdr.type != BINDER_TYPE_PTR)
		वापस शून्य;
	अगर (object_offsetp)
		*object_offsetp = object_offset;

	वापस &object->bbo;
पूर्ण

/**
 * binder_validate_fixup() - validates poपूर्णांकer/fd fixups happen in order.
 * @proc:		binder_proc owning the buffer
 * @b:			transaction buffer
 * @objects_start_offset: offset to start of objects buffer
 * @buffer_obj_offset:	offset to binder_buffer_object in which to fix up
 * @fixup_offset:	start offset in @buffer to fix up
 * @last_obj_offset:	offset to last binder_buffer_object that we fixed
 * @last_min_offset:	minimum fixup offset in object at @last_obj_offset
 *
 * Return:		%true अगर a fixup in buffer @buffer at offset @offset is
 *			allowed.
 *
 * For safety reasons, we only allow fixups inside a buffer to happen
 * at increasing offsets; additionally, we only allow fixup on the last
 * buffer object that was verअगरied, or one of its parents.
 *
 * Example of what is allowed:
 *
 * A
 *   B (parent = A, offset = 0)
 *   C (parent = A, offset = 16)
 *     D (parent = C, offset = 0)
 *   E (parent = A, offset = 32) // min_offset is 16 (C.parent_offset)
 *
 * Examples of what is not allowed:
 *
 * Decreasing offsets within the same parent:
 * A
 *   C (parent = A, offset = 16)
 *   B (parent = A, offset = 0) // decreasing offset within A
 *
 * Referring to a parent that wasn't the last object or any of its parents:
 * A
 *   B (parent = A, offset = 0)
 *   C (parent = A, offset = 0)
 *   C (parent = A, offset = 16)
 *     D (parent = B, offset = 0) // B is not A or any of A's parents
 */
अटल bool binder_validate_fixup(काष्ठा binder_proc *proc,
				  काष्ठा binder_buffer *b,
				  binder_माप_प्रकार objects_start_offset,
				  binder_माप_प्रकार buffer_obj_offset,
				  binder_माप_प्रकार fixup_offset,
				  binder_माप_प्रकार last_obj_offset,
				  binder_माप_प्रकार last_min_offset)
अणु
	अगर (!last_obj_offset) अणु
		/* Nothing to fix up in */
		वापस false;
	पूर्ण

	जबतक (last_obj_offset != buffer_obj_offset) अणु
		अचिन्हित दीर्घ buffer_offset;
		काष्ठा binder_object last_object;
		काष्ठा binder_buffer_object *last_bbo;
		माप_प्रकार object_size = binder_get_object(proc, b, last_obj_offset,
						       &last_object);
		अगर (object_size != माप(*last_bbo))
			वापस false;

		last_bbo = &last_object.bbo;
		/*
		 * Safe to retrieve the parent of last_obj, since it
		 * was alपढ़ोy previously verअगरied by the driver.
		 */
		अगर ((last_bbo->flags & BINDER_BUFFER_FLAG_HAS_PARENT) == 0)
			वापस false;
		last_min_offset = last_bbo->parent_offset + माप(uपूर्णांकptr_t);
		buffer_offset = objects_start_offset +
			माप(binder_माप_प्रकार) * last_bbo->parent;
		अगर (binder_alloc_copy_from_buffer(&proc->alloc,
						  &last_obj_offset,
						  b, buffer_offset,
						  माप(last_obj_offset)))
			वापस false;
	पूर्ण
	वापस (fixup_offset >= last_min_offset);
पूर्ण

/**
 * काष्ठा binder_task_work_cb - क्रम deferred बंद
 *
 * @twork:                callback_head क्रम task work
 * @fd:                   fd to बंद
 *
 * Structure to pass task work to be handled after
 * वापसing from binder_ioctl() via task_work_add().
 */
काष्ठा binder_task_work_cb अणु
	काष्ठा callback_head twork;
	काष्ठा file *file;
पूर्ण;

/**
 * binder_करो_fd_बंद() - बंद list of file descriptors
 * @twork:	callback head क्रम task work
 *
 * It is not safe to call ksys_बंद() during the binder_ioctl()
 * function अगर there is a chance that binder's own file descriptor
 * might be बंदd. This is to meet the requirements क्रम using
 * fdget() (see comments क्रम __fget_light()). Thereक्रमe use
 * task_work_add() to schedule the बंद operation once we have
 * वापसed from binder_ioctl(). This function is a callback
 * क्रम that mechanism and करोes the actual ksys_बंद() on the
 * given file descriptor.
 */
अटल व्योम binder_करो_fd_बंद(काष्ठा callback_head *twork)
अणु
	काष्ठा binder_task_work_cb *twcb = container_of(twork,
			काष्ठा binder_task_work_cb, twork);

	fput(twcb->file);
	kमुक्त(twcb);
पूर्ण

/**
 * binder_deferred_fd_बंद() - schedule a बंद क्रम the given file-descriptor
 * @fd:		file-descriptor to बंद
 *
 * See comments in binder_करो_fd_बंद(). This function is used to schedule
 * a file-descriptor to be बंदd after वापसing from binder_ioctl().
 */
अटल व्योम binder_deferred_fd_बंद(पूर्णांक fd)
अणु
	काष्ठा binder_task_work_cb *twcb;

	twcb = kzalloc(माप(*twcb), GFP_KERNEL);
	अगर (!twcb)
		वापस;
	init_task_work(&twcb->twork, binder_करो_fd_बंद);
	बंद_fd_get_file(fd, &twcb->file);
	अगर (twcb->file) अणु
		filp_बंद(twcb->file, current->files);
		task_work_add(current, &twcb->twork, TWA_RESUME);
	पूर्ण अन्यथा अणु
		kमुक्त(twcb);
	पूर्ण
पूर्ण

अटल व्योम binder_transaction_buffer_release(काष्ठा binder_proc *proc,
					      काष्ठा binder_buffer *buffer,
					      binder_माप_प्रकार failed_at,
					      bool is_failure)
अणु
	पूर्णांक debug_id = buffer->debug_id;
	binder_माप_प्रकार off_start_offset, buffer_offset, off_end_offset;

	binder_debug(BINDER_DEBUG_TRANSACTION,
		     "%d buffer release %d, size %zd-%zd, failed at %llx\n",
		     proc->pid, buffer->debug_id,
		     buffer->data_size, buffer->offsets_size,
		     (अचिन्हित दीर्घ दीर्घ)failed_at);

	अगर (buffer->target_node)
		binder_dec_node(buffer->target_node, 1, 0);

	off_start_offset = ALIGN(buffer->data_size, माप(व्योम *));
	off_end_offset = is_failure ? failed_at :
				off_start_offset + buffer->offsets_size;
	क्रम (buffer_offset = off_start_offset; buffer_offset < off_end_offset;
	     buffer_offset += माप(binder_माप_प्रकार)) अणु
		काष्ठा binder_object_header *hdr;
		माप_प्रकार object_size = 0;
		काष्ठा binder_object object;
		binder_माप_प्रकार object_offset;

		अगर (!binder_alloc_copy_from_buffer(&proc->alloc, &object_offset,
						   buffer, buffer_offset,
						   माप(object_offset)))
			object_size = binder_get_object(proc, buffer,
							object_offset, &object);
		अगर (object_size == 0) अणु
			pr_err("transaction release %d bad object at offset %lld, size %zd\n",
			       debug_id, (u64)object_offset, buffer->data_size);
			जारी;
		पूर्ण
		hdr = &object.hdr;
		चयन (hdr->type) अणु
		हाल BINDER_TYPE_BINDER:
		हाल BINDER_TYPE_WEAK_BINDER: अणु
			काष्ठा flat_binder_object *fp;
			काष्ठा binder_node *node;

			fp = to_flat_binder_object(hdr);
			node = binder_get_node(proc, fp->binder);
			अगर (node == शून्य) अणु
				pr_err("transaction release %d bad node %016llx\n",
				       debug_id, (u64)fp->binder);
				अवरोध;
			पूर्ण
			binder_debug(BINDER_DEBUG_TRANSACTION,
				     "        node %d u%016llx\n",
				     node->debug_id, (u64)node->ptr);
			binder_dec_node(node, hdr->type == BINDER_TYPE_BINDER,
					0);
			binder_put_node(node);
		पूर्ण अवरोध;
		हाल BINDER_TYPE_HANDLE:
		हाल BINDER_TYPE_WEAK_HANDLE: अणु
			काष्ठा flat_binder_object *fp;
			काष्ठा binder_ref_data rdata;
			पूर्णांक ret;

			fp = to_flat_binder_object(hdr);
			ret = binder_dec_ref_क्रम_handle(proc, fp->handle,
				hdr->type == BINDER_TYPE_HANDLE, &rdata);

			अगर (ret) अणु
				pr_err("transaction release %d bad handle %d, ret = %d\n",
				 debug_id, fp->handle, ret);
				अवरोध;
			पूर्ण
			binder_debug(BINDER_DEBUG_TRANSACTION,
				     "        ref %d desc %d\n",
				     rdata.debug_id, rdata.desc);
		पूर्ण अवरोध;

		हाल BINDER_TYPE_FD: अणु
			/*
			 * No need to बंद the file here since user-space
			 * बंदs it क्रम क्रम successfully delivered
			 * transactions. For transactions that weren't
			 * delivered, the new fd was never allocated so
			 * there is no need to बंद and the fput on the
			 * file is करोne when the transaction is torn
			 * करोwn.
			 */
		पूर्ण अवरोध;
		हाल BINDER_TYPE_PTR:
			/*
			 * Nothing to करो here, this will get cleaned up when the
			 * transaction buffer माला_लो मुक्तd
			 */
			अवरोध;
		हाल BINDER_TYPE_FDA: अणु
			काष्ठा binder_fd_array_object *fda;
			काष्ठा binder_buffer_object *parent;
			काष्ठा binder_object ptr_object;
			binder_माप_प्रकार fda_offset;
			माप_प्रकार fd_index;
			binder_माप_प्रकार fd_buf_size;
			binder_माप_प्रकार num_valid;

			अगर (proc->tsk != current->group_leader) अणु
				/*
				 * Nothing to करो अगर running in sender context
				 * The fd fixups have not been applied so no
				 * fds need to be बंदd.
				 */
				जारी;
			पूर्ण

			num_valid = (buffer_offset - off_start_offset) /
						माप(binder_माप_प्रकार);
			fda = to_binder_fd_array_object(hdr);
			parent = binder_validate_ptr(proc, buffer, &ptr_object,
						     fda->parent,
						     off_start_offset,
						     शून्य,
						     num_valid);
			अगर (!parent) अणु
				pr_err("transaction release %d bad parent offset\n",
				       debug_id);
				जारी;
			पूर्ण
			fd_buf_size = माप(u32) * fda->num_fds;
			अगर (fda->num_fds >= SIZE_MAX / माप(u32)) अणु
				pr_err("transaction release %d invalid number of fds (%lld)\n",
				       debug_id, (u64)fda->num_fds);
				जारी;
			पूर्ण
			अगर (fd_buf_size > parent->length ||
			    fda->parent_offset > parent->length - fd_buf_size) अणु
				/* No space क्रम all file descriptors here. */
				pr_err("transaction release %d not enough space for %lld fds in buffer\n",
				       debug_id, (u64)fda->num_fds);
				जारी;
			पूर्ण
			/*
			 * the source data क्रम binder_buffer_object is visible
			 * to user-space and the @buffer element is the user
			 * poपूर्णांकer to the buffer_object containing the fd_array.
			 * Convert the address to an offset relative to
			 * the base of the transaction buffer.
			 */
			fda_offset =
			    (parent->buffer - (uपूर्णांकptr_t)buffer->user_data) +
			    fda->parent_offset;
			क्रम (fd_index = 0; fd_index < fda->num_fds;
			     fd_index++) अणु
				u32 fd;
				पूर्णांक err;
				binder_माप_प्रकार offset = fda_offset +
					fd_index * माप(fd);

				err = binder_alloc_copy_from_buffer(
						&proc->alloc, &fd, buffer,
						offset, माप(fd));
				WARN_ON(err);
				अगर (!err)
					binder_deferred_fd_बंद(fd);
			पूर्ण
		पूर्ण अवरोध;
		शेष:
			pr_err("transaction release %d bad object type %x\n",
				debug_id, hdr->type);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक binder_translate_binder(काष्ठा flat_binder_object *fp,
				   काष्ठा binder_transaction *t,
				   काष्ठा binder_thपढ़ो *thपढ़ो)
अणु
	काष्ठा binder_node *node;
	काष्ठा binder_proc *proc = thपढ़ो->proc;
	काष्ठा binder_proc *target_proc = t->to_proc;
	काष्ठा binder_ref_data rdata;
	पूर्णांक ret = 0;

	node = binder_get_node(proc, fp->binder);
	अगर (!node) अणु
		node = binder_new_node(proc, fp);
		अगर (!node)
			वापस -ENOMEM;
	पूर्ण
	अगर (fp->cookie != node->cookie) अणु
		binder_user_error("%d:%d sending u%016llx node %d, cookie mismatch %016llx != %016llx\n",
				  proc->pid, thपढ़ो->pid, (u64)fp->binder,
				  node->debug_id, (u64)fp->cookie,
				  (u64)node->cookie);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	अगर (security_binder_transfer_binder(proc->tsk, target_proc->tsk)) अणु
		ret = -EPERM;
		जाओ करोne;
	पूर्ण

	ret = binder_inc_ref_क्रम_node(target_proc, node,
			fp->hdr.type == BINDER_TYPE_BINDER,
			&thपढ़ो->toकरो, &rdata);
	अगर (ret)
		जाओ करोne;

	अगर (fp->hdr.type == BINDER_TYPE_BINDER)
		fp->hdr.type = BINDER_TYPE_HANDLE;
	अन्यथा
		fp->hdr.type = BINDER_TYPE_WEAK_HANDLE;
	fp->binder = 0;
	fp->handle = rdata.desc;
	fp->cookie = 0;

	trace_binder_transaction_node_to_ref(t, node, &rdata);
	binder_debug(BINDER_DEBUG_TRANSACTION,
		     "        node %d u%016llx -> ref %d desc %d\n",
		     node->debug_id, (u64)node->ptr,
		     rdata.debug_id, rdata.desc);
करोne:
	binder_put_node(node);
	वापस ret;
पूर्ण

अटल पूर्णांक binder_translate_handle(काष्ठा flat_binder_object *fp,
				   काष्ठा binder_transaction *t,
				   काष्ठा binder_thपढ़ो *thपढ़ो)
अणु
	काष्ठा binder_proc *proc = thपढ़ो->proc;
	काष्ठा binder_proc *target_proc = t->to_proc;
	काष्ठा binder_node *node;
	काष्ठा binder_ref_data src_rdata;
	पूर्णांक ret = 0;

	node = binder_get_node_from_ref(proc, fp->handle,
			fp->hdr.type == BINDER_TYPE_HANDLE, &src_rdata);
	अगर (!node) अणु
		binder_user_error("%d:%d got transaction with invalid handle, %d\n",
				  proc->pid, thपढ़ो->pid, fp->handle);
		वापस -EINVAL;
	पूर्ण
	अगर (security_binder_transfer_binder(proc->tsk, target_proc->tsk)) अणु
		ret = -EPERM;
		जाओ करोne;
	पूर्ण

	binder_node_lock(node);
	अगर (node->proc == target_proc) अणु
		अगर (fp->hdr.type == BINDER_TYPE_HANDLE)
			fp->hdr.type = BINDER_TYPE_BINDER;
		अन्यथा
			fp->hdr.type = BINDER_TYPE_WEAK_BINDER;
		fp->binder = node->ptr;
		fp->cookie = node->cookie;
		अगर (node->proc)
			binder_inner_proc_lock(node->proc);
		अन्यथा
			__acquire(&node->proc->inner_lock);
		binder_inc_node_nilocked(node,
					 fp->hdr.type == BINDER_TYPE_BINDER,
					 0, शून्य);
		अगर (node->proc)
			binder_inner_proc_unlock(node->proc);
		अन्यथा
			__release(&node->proc->inner_lock);
		trace_binder_transaction_ref_to_node(t, node, &src_rdata);
		binder_debug(BINDER_DEBUG_TRANSACTION,
			     "        ref %d desc %d -> node %d u%016llx\n",
			     src_rdata.debug_id, src_rdata.desc, node->debug_id,
			     (u64)node->ptr);
		binder_node_unlock(node);
	पूर्ण अन्यथा अणु
		काष्ठा binder_ref_data dest_rdata;

		binder_node_unlock(node);
		ret = binder_inc_ref_क्रम_node(target_proc, node,
				fp->hdr.type == BINDER_TYPE_HANDLE,
				शून्य, &dest_rdata);
		अगर (ret)
			जाओ करोne;

		fp->binder = 0;
		fp->handle = dest_rdata.desc;
		fp->cookie = 0;
		trace_binder_transaction_ref_to_ref(t, node, &src_rdata,
						    &dest_rdata);
		binder_debug(BINDER_DEBUG_TRANSACTION,
			     "        ref %d desc %d -> ref %d desc %d (node %d)\n",
			     src_rdata.debug_id, src_rdata.desc,
			     dest_rdata.debug_id, dest_rdata.desc,
			     node->debug_id);
	पूर्ण
करोne:
	binder_put_node(node);
	वापस ret;
पूर्ण

अटल पूर्णांक binder_translate_fd(u32 fd, binder_माप_प्रकार fd_offset,
			       काष्ठा binder_transaction *t,
			       काष्ठा binder_thपढ़ो *thपढ़ो,
			       काष्ठा binder_transaction *in_reply_to)
अणु
	काष्ठा binder_proc *proc = thपढ़ो->proc;
	काष्ठा binder_proc *target_proc = t->to_proc;
	काष्ठा binder_txn_fd_fixup *fixup;
	काष्ठा file *file;
	पूर्णांक ret = 0;
	bool target_allows_fd;

	अगर (in_reply_to)
		target_allows_fd = !!(in_reply_to->flags & TF_ACCEPT_FDS);
	अन्यथा
		target_allows_fd = t->buffer->target_node->accept_fds;
	अगर (!target_allows_fd) अणु
		binder_user_error("%d:%d got %s with fd, %d, but target does not allow fds\n",
				  proc->pid, thपढ़ो->pid,
				  in_reply_to ? "reply" : "transaction",
				  fd);
		ret = -EPERM;
		जाओ err_fd_not_accepted;
	पूर्ण

	file = fget(fd);
	अगर (!file) अणु
		binder_user_error("%d:%d got transaction with invalid fd, %d\n",
				  proc->pid, thपढ़ो->pid, fd);
		ret = -EBADF;
		जाओ err_fget;
	पूर्ण
	ret = security_binder_transfer_file(proc->tsk, target_proc->tsk, file);
	अगर (ret < 0) अणु
		ret = -EPERM;
		जाओ err_security;
	पूर्ण

	/*
	 * Add fixup record क्रम this transaction. The allocation
	 * of the fd in the target needs to be करोne from a
	 * target thपढ़ो.
	 */
	fixup = kzalloc(माप(*fixup), GFP_KERNEL);
	अगर (!fixup) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण
	fixup->file = file;
	fixup->offset = fd_offset;
	trace_binder_transaction_fd_send(t, fd, fixup->offset);
	list_add_tail(&fixup->fixup_entry, &t->fd_fixups);

	वापस ret;

err_alloc:
err_security:
	fput(file);
err_fget:
err_fd_not_accepted:
	वापस ret;
पूर्ण

अटल पूर्णांक binder_translate_fd_array(काष्ठा binder_fd_array_object *fda,
				     काष्ठा binder_buffer_object *parent,
				     काष्ठा binder_transaction *t,
				     काष्ठा binder_thपढ़ो *thपढ़ो,
				     काष्ठा binder_transaction *in_reply_to)
अणु
	binder_माप_प्रकार fdi, fd_buf_size;
	binder_माप_प्रकार fda_offset;
	काष्ठा binder_proc *proc = thपढ़ो->proc;
	काष्ठा binder_proc *target_proc = t->to_proc;

	fd_buf_size = माप(u32) * fda->num_fds;
	अगर (fda->num_fds >= SIZE_MAX / माप(u32)) अणु
		binder_user_error("%d:%d got transaction with invalid number of fds (%lld)\n",
				  proc->pid, thपढ़ो->pid, (u64)fda->num_fds);
		वापस -EINVAL;
	पूर्ण
	अगर (fd_buf_size > parent->length ||
	    fda->parent_offset > parent->length - fd_buf_size) अणु
		/* No space क्रम all file descriptors here. */
		binder_user_error("%d:%d not enough space to store %lld fds in buffer\n",
				  proc->pid, thपढ़ो->pid, (u64)fda->num_fds);
		वापस -EINVAL;
	पूर्ण
	/*
	 * the source data क्रम binder_buffer_object is visible
	 * to user-space and the @buffer element is the user
	 * poपूर्णांकer to the buffer_object containing the fd_array.
	 * Convert the address to an offset relative to
	 * the base of the transaction buffer.
	 */
	fda_offset = (parent->buffer - (uपूर्णांकptr_t)t->buffer->user_data) +
		fda->parent_offset;
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)fda_offset, माप(u32))) अणु
		binder_user_error("%d:%d parent offset not aligned correctly.\n",
				  proc->pid, thपढ़ो->pid);
		वापस -EINVAL;
	पूर्ण
	क्रम (fdi = 0; fdi < fda->num_fds; fdi++) अणु
		u32 fd;
		पूर्णांक ret;
		binder_माप_प्रकार offset = fda_offset + fdi * माप(fd);

		ret = binder_alloc_copy_from_buffer(&target_proc->alloc,
						    &fd, t->buffer,
						    offset, माप(fd));
		अगर (!ret)
			ret = binder_translate_fd(fd, offset, t, thपढ़ो,
						  in_reply_to);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक binder_fixup_parent(काष्ठा binder_transaction *t,
			       काष्ठा binder_thपढ़ो *thपढ़ो,
			       काष्ठा binder_buffer_object *bp,
			       binder_माप_प्रकार off_start_offset,
			       binder_माप_प्रकार num_valid,
			       binder_माप_प्रकार last_fixup_obj_off,
			       binder_माप_प्रकार last_fixup_min_off)
अणु
	काष्ठा binder_buffer_object *parent;
	काष्ठा binder_buffer *b = t->buffer;
	काष्ठा binder_proc *proc = thपढ़ो->proc;
	काष्ठा binder_proc *target_proc = t->to_proc;
	काष्ठा binder_object object;
	binder_माप_प्रकार buffer_offset;
	binder_माप_प्रकार parent_offset;

	अगर (!(bp->flags & BINDER_BUFFER_FLAG_HAS_PARENT))
		वापस 0;

	parent = binder_validate_ptr(target_proc, b, &object, bp->parent,
				     off_start_offset, &parent_offset,
				     num_valid);
	अगर (!parent) अणु
		binder_user_error("%d:%d got transaction with invalid parent offset or type\n",
				  proc->pid, thपढ़ो->pid);
		वापस -EINVAL;
	पूर्ण

	अगर (!binder_validate_fixup(target_proc, b, off_start_offset,
				   parent_offset, bp->parent_offset,
				   last_fixup_obj_off,
				   last_fixup_min_off)) अणु
		binder_user_error("%d:%d got transaction with out-of-order buffer fixup\n",
				  proc->pid, thपढ़ो->pid);
		वापस -EINVAL;
	पूर्ण

	अगर (parent->length < माप(binder_uपूर्णांकptr_t) ||
	    bp->parent_offset > parent->length - माप(binder_uपूर्णांकptr_t)) अणु
		/* No space क्रम a poपूर्णांकer here! */
		binder_user_error("%d:%d got transaction with invalid parent offset\n",
				  proc->pid, thपढ़ो->pid);
		वापस -EINVAL;
	पूर्ण
	buffer_offset = bp->parent_offset +
			(uपूर्णांकptr_t)parent->buffer - (uपूर्णांकptr_t)b->user_data;
	अगर (binder_alloc_copy_to_buffer(&target_proc->alloc, b, buffer_offset,
					&bp->buffer, माप(bp->buffer))) अणु
		binder_user_error("%d:%d got transaction with invalid parent offset\n",
				  proc->pid, thपढ़ो->pid);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * binder_proc_transaction() - sends a transaction to a process and wakes it up
 * @t:		transaction to send
 * @proc:	process to send the transaction to
 * @thपढ़ो:	thपढ़ो in @proc to send the transaction to (may be शून्य)
 *
 * This function queues a transaction to the specअगरied process. It will try
 * to find a thपढ़ो in the target process to handle the transaction and
 * wake it up. If no thपढ़ो is found, the work is queued to the proc
 * रुकोqueue.
 *
 * If the @thपढ़ो parameter is not शून्य, the transaction is always queued
 * to the रुकोlist of that specअगरic thपढ़ो.
 *
 * Return:	0 अगर the transaction was successfully queued
 *		BR_DEAD_REPLY अगर the target process or thपढ़ो is dead
 *		BR_FROZEN_REPLY अगर the target process or thपढ़ो is frozen
 */
अटल पूर्णांक binder_proc_transaction(काष्ठा binder_transaction *t,
				    काष्ठा binder_proc *proc,
				    काष्ठा binder_thपढ़ो *thपढ़ो)
अणु
	काष्ठा binder_node *node = t->buffer->target_node;
	bool oneway = !!(t->flags & TF_ONE_WAY);
	bool pending_async = false;

	BUG_ON(!node);
	binder_node_lock(node);
	अगर (oneway) अणु
		BUG_ON(thपढ़ो);
		अगर (node->has_async_transaction)
			pending_async = true;
		अन्यथा
			node->has_async_transaction = true;
	पूर्ण

	binder_inner_proc_lock(proc);
	अगर (proc->is_frozen) अणु
		proc->sync_recv |= !oneway;
		proc->async_recv |= oneway;
	पूर्ण

	अगर ((proc->is_frozen && !oneway) || proc->is_dead ||
			(thपढ़ो && thपढ़ो->is_dead)) अणु
		binder_inner_proc_unlock(proc);
		binder_node_unlock(node);
		वापस proc->is_frozen ? BR_FROZEN_REPLY : BR_DEAD_REPLY;
	पूर्ण

	अगर (!thपढ़ो && !pending_async)
		thपढ़ो = binder_select_thपढ़ो_ilocked(proc);

	अगर (thपढ़ो)
		binder_enqueue_thपढ़ो_work_ilocked(thपढ़ो, &t->work);
	अन्यथा अगर (!pending_async)
		binder_enqueue_work_ilocked(&t->work, &proc->toकरो);
	अन्यथा
		binder_enqueue_work_ilocked(&t->work, &node->async_toकरो);

	अगर (!pending_async)
		binder_wakeup_thपढ़ो_ilocked(proc, thपढ़ो, !oneway /* sync */);

	proc->outstanding_txns++;
	binder_inner_proc_unlock(proc);
	binder_node_unlock(node);

	वापस 0;
पूर्ण

/**
 * binder_get_node_refs_क्रम_txn() - Get required refs on node क्रम txn
 * @node:         काष्ठा binder_node क्रम which to get refs
 * @proc:         वापसs @node->proc अगर valid
 * @error:        अगर no @proc then वापसs BR_DEAD_REPLY
 *
 * User-space normally keeps the node alive when creating a transaction
 * since it has a reference to the target. The local strong ref keeps it
 * alive अगर the sending process dies beक्रमe the target process processes
 * the transaction. If the source process is malicious or has a reference
 * counting bug, relying on the local strong ref can fail.
 *
 * Since user-space can cause the local strong ref to go away, we also take
 * a पंचांगpref on the node to ensure it survives जबतक we are स्थिरructing
 * the transaction. We also need a पंचांगpref on the proc जबतक we are
 * स्थिरructing the transaction, so we take that here as well.
 *
 * Return: The target_node with refs taken or शून्य अगर no @node->proc is शून्य.
 * Also sets @proc अगर valid. If the @node->proc is शून्य indicating that the
 * target proc has died, @error is set to BR_DEAD_REPLY
 */
अटल काष्ठा binder_node *binder_get_node_refs_क्रम_txn(
		काष्ठा binder_node *node,
		काष्ठा binder_proc **procp,
		uपूर्णांक32_t *error)
अणु
	काष्ठा binder_node *target_node = शून्य;

	binder_node_inner_lock(node);
	अगर (node->proc) अणु
		target_node = node;
		binder_inc_node_nilocked(node, 1, 0, शून्य);
		binder_inc_node_पंचांगpref_ilocked(node);
		node->proc->पंचांगp_ref++;
		*procp = node->proc;
	पूर्ण अन्यथा
		*error = BR_DEAD_REPLY;
	binder_node_inner_unlock(node);

	वापस target_node;
पूर्ण

अटल व्योम binder_transaction(काष्ठा binder_proc *proc,
			       काष्ठा binder_thपढ़ो *thपढ़ो,
			       काष्ठा binder_transaction_data *tr, पूर्णांक reply,
			       binder_माप_प्रकार extra_buffers_size)
अणु
	पूर्णांक ret;
	काष्ठा binder_transaction *t;
	काष्ठा binder_work *w;
	काष्ठा binder_work *tcomplete;
	binder_माप_प्रकार buffer_offset = 0;
	binder_माप_प्रकार off_start_offset, off_end_offset;
	binder_माप_प्रकार off_min;
	binder_माप_प्रकार sg_buf_offset, sg_buf_end_offset;
	काष्ठा binder_proc *target_proc = शून्य;
	काष्ठा binder_thपढ़ो *target_thपढ़ो = शून्य;
	काष्ठा binder_node *target_node = शून्य;
	काष्ठा binder_transaction *in_reply_to = शून्य;
	काष्ठा binder_transaction_log_entry *e;
	uपूर्णांक32_t वापस_error = 0;
	uपूर्णांक32_t वापस_error_param = 0;
	uपूर्णांक32_t वापस_error_line = 0;
	binder_माप_प्रकार last_fixup_obj_off = 0;
	binder_माप_प्रकार last_fixup_min_off = 0;
	काष्ठा binder_context *context = proc->context;
	पूर्णांक t_debug_id = atomic_inc_वापस(&binder_last_id);
	अक्षर *secctx = शून्य;
	u32 secctx_sz = 0;

	e = binder_transaction_log_add(&binder_transaction_log);
	e->debug_id = t_debug_id;
	e->call_type = reply ? 2 : !!(tr->flags & TF_ONE_WAY);
	e->from_proc = proc->pid;
	e->from_thपढ़ो = thपढ़ो->pid;
	e->target_handle = tr->target.handle;
	e->data_size = tr->data_size;
	e->offsets_size = tr->offsets_size;
	strscpy(e->context_name, proc->context->name, BINDERFS_MAX_NAME);

	अगर (reply) अणु
		binder_inner_proc_lock(proc);
		in_reply_to = thपढ़ो->transaction_stack;
		अगर (in_reply_to == शून्य) अणु
			binder_inner_proc_unlock(proc);
			binder_user_error("%d:%d got reply transaction with no transaction stack\n",
					  proc->pid, thपढ़ो->pid);
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EPROTO;
			वापस_error_line = __LINE__;
			जाओ err_empty_call_stack;
		पूर्ण
		अगर (in_reply_to->to_thपढ़ो != thपढ़ो) अणु
			spin_lock(&in_reply_to->lock);
			binder_user_error("%d:%d got reply transaction with bad transaction stack, transaction %d has target %d:%d\n",
				proc->pid, thपढ़ो->pid, in_reply_to->debug_id,
				in_reply_to->to_proc ?
				in_reply_to->to_proc->pid : 0,
				in_reply_to->to_thपढ़ो ?
				in_reply_to->to_thपढ़ो->pid : 0);
			spin_unlock(&in_reply_to->lock);
			binder_inner_proc_unlock(proc);
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EPROTO;
			वापस_error_line = __LINE__;
			in_reply_to = शून्य;
			जाओ err_bad_call_stack;
		पूर्ण
		thपढ़ो->transaction_stack = in_reply_to->to_parent;
		binder_inner_proc_unlock(proc);
		binder_set_nice(in_reply_to->saved_priority);
		target_thपढ़ो = binder_get_txn_from_and_acq_inner(in_reply_to);
		अगर (target_thपढ़ो == शून्य) अणु
			/* annotation क्रम sparse */
			__release(&target_thपढ़ो->proc->inner_lock);
			वापस_error = BR_DEAD_REPLY;
			वापस_error_line = __LINE__;
			जाओ err_dead_binder;
		पूर्ण
		अगर (target_thपढ़ो->transaction_stack != in_reply_to) अणु
			binder_user_error("%d:%d got reply transaction with bad target transaction stack %d, expected %d\n",
				proc->pid, thपढ़ो->pid,
				target_thपढ़ो->transaction_stack ?
				target_thपढ़ो->transaction_stack->debug_id : 0,
				in_reply_to->debug_id);
			binder_inner_proc_unlock(target_thपढ़ो->proc);
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EPROTO;
			वापस_error_line = __LINE__;
			in_reply_to = शून्य;
			target_thपढ़ो = शून्य;
			जाओ err_dead_binder;
		पूर्ण
		target_proc = target_thपढ़ो->proc;
		target_proc->पंचांगp_ref++;
		binder_inner_proc_unlock(target_thपढ़ो->proc);
	पूर्ण अन्यथा अणु
		अगर (tr->target.handle) अणु
			काष्ठा binder_ref *ref;

			/*
			 * There must alपढ़ोy be a strong ref
			 * on this node. If so, करो a strong
			 * increment on the node to ensure it
			 * stays alive until the transaction is
			 * करोne.
			 */
			binder_proc_lock(proc);
			ref = binder_get_ref_olocked(proc, tr->target.handle,
						     true);
			अगर (ref) अणु
				target_node = binder_get_node_refs_क्रम_txn(
						ref->node, &target_proc,
						&वापस_error);
			पूर्ण अन्यथा अणु
				binder_user_error("%d:%d got transaction to invalid handle\n",
						  proc->pid, thपढ़ो->pid);
				वापस_error = BR_FAILED_REPLY;
			पूर्ण
			binder_proc_unlock(proc);
		पूर्ण अन्यथा अणु
			mutex_lock(&context->context_mgr_node_lock);
			target_node = context->binder_context_mgr_node;
			अगर (target_node)
				target_node = binder_get_node_refs_क्रम_txn(
						target_node, &target_proc,
						&वापस_error);
			अन्यथा
				वापस_error = BR_DEAD_REPLY;
			mutex_unlock(&context->context_mgr_node_lock);
			अगर (target_node && target_proc->pid == proc->pid) अणु
				binder_user_error("%d:%d got transaction to context manager from process owning it\n",
						  proc->pid, thपढ़ो->pid);
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = -EINVAL;
				वापस_error_line = __LINE__;
				जाओ err_invalid_target_handle;
			पूर्ण
		पूर्ण
		अगर (!target_node) अणु
			/*
			 * वापस_error is set above
			 */
			वापस_error_param = -EINVAL;
			वापस_error_line = __LINE__;
			जाओ err_dead_binder;
		पूर्ण
		e->to_node = target_node->debug_id;
		अगर (WARN_ON(proc == target_proc)) अणु
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EINVAL;
			वापस_error_line = __LINE__;
			जाओ err_invalid_target_handle;
		पूर्ण
		अगर (security_binder_transaction(proc->tsk,
						target_proc->tsk) < 0) अणु
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EPERM;
			वापस_error_line = __LINE__;
			जाओ err_invalid_target_handle;
		पूर्ण
		binder_inner_proc_lock(proc);

		w = list_first_entry_or_null(&thपढ़ो->toकरो,
					     काष्ठा binder_work, entry);
		अगर (!(tr->flags & TF_ONE_WAY) && w &&
		    w->type == BINDER_WORK_TRANSACTION) अणु
			/*
			 * Do not allow new outgoing transaction from a
			 * thपढ़ो that has a transaction at the head of
			 * its toकरो list. Only need to check the head
			 * because binder_select_thपढ़ो_ilocked picks a
			 * thपढ़ो from proc->रुकोing_thपढ़ोs to enqueue
			 * the transaction, and nothing is queued to the
			 * toकरो list जबतक the thपढ़ो is on रुकोing_thपढ़ोs.
			 */
			binder_user_error("%d:%d new transaction not allowed when there is a transaction on thread todo\n",
					  proc->pid, thपढ़ो->pid);
			binder_inner_proc_unlock(proc);
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EPROTO;
			वापस_error_line = __LINE__;
			जाओ err_bad_toकरो_list;
		पूर्ण

		अगर (!(tr->flags & TF_ONE_WAY) && thपढ़ो->transaction_stack) अणु
			काष्ठा binder_transaction *पंचांगp;

			पंचांगp = thपढ़ो->transaction_stack;
			अगर (पंचांगp->to_thपढ़ो != thपढ़ो) अणु
				spin_lock(&पंचांगp->lock);
				binder_user_error("%d:%d got new transaction with bad transaction stack, transaction %d has target %d:%d\n",
					proc->pid, thपढ़ो->pid, पंचांगp->debug_id,
					पंचांगp->to_proc ? पंचांगp->to_proc->pid : 0,
					पंचांगp->to_thपढ़ो ?
					पंचांगp->to_thपढ़ो->pid : 0);
				spin_unlock(&पंचांगp->lock);
				binder_inner_proc_unlock(proc);
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = -EPROTO;
				वापस_error_line = __LINE__;
				जाओ err_bad_call_stack;
			पूर्ण
			जबतक (पंचांगp) अणु
				काष्ठा binder_thपढ़ो *from;

				spin_lock(&पंचांगp->lock);
				from = पंचांगp->from;
				अगर (from && from->proc == target_proc) अणु
					atomic_inc(&from->पंचांगp_ref);
					target_thपढ़ो = from;
					spin_unlock(&पंचांगp->lock);
					अवरोध;
				पूर्ण
				spin_unlock(&पंचांगp->lock);
				पंचांगp = पंचांगp->from_parent;
			पूर्ण
		पूर्ण
		binder_inner_proc_unlock(proc);
	पूर्ण
	अगर (target_thपढ़ो)
		e->to_thपढ़ो = target_thपढ़ो->pid;
	e->to_proc = target_proc->pid;

	/* TODO: reuse incoming transaction क्रम reply */
	t = kzalloc(माप(*t), GFP_KERNEL);
	अगर (t == शून्य) अणु
		वापस_error = BR_FAILED_REPLY;
		वापस_error_param = -ENOMEM;
		वापस_error_line = __LINE__;
		जाओ err_alloc_t_failed;
	पूर्ण
	INIT_LIST_HEAD(&t->fd_fixups);
	binder_stats_created(BINDER_STAT_TRANSACTION);
	spin_lock_init(&t->lock);

	tcomplete = kzalloc(माप(*tcomplete), GFP_KERNEL);
	अगर (tcomplete == शून्य) अणु
		वापस_error = BR_FAILED_REPLY;
		वापस_error_param = -ENOMEM;
		वापस_error_line = __LINE__;
		जाओ err_alloc_tcomplete_failed;
	पूर्ण
	binder_stats_created(BINDER_STAT_TRANSACTION_COMPLETE);

	t->debug_id = t_debug_id;

	अगर (reply)
		binder_debug(BINDER_DEBUG_TRANSACTION,
			     "%d:%d BC_REPLY %d -> %d:%d, data %016llx-%016llx size %lld-%lld-%lld\n",
			     proc->pid, thपढ़ो->pid, t->debug_id,
			     target_proc->pid, target_thपढ़ो->pid,
			     (u64)tr->data.ptr.buffer,
			     (u64)tr->data.ptr.offsets,
			     (u64)tr->data_size, (u64)tr->offsets_size,
			     (u64)extra_buffers_size);
	अन्यथा
		binder_debug(BINDER_DEBUG_TRANSACTION,
			     "%d:%d BC_TRANSACTION %d -> %d - node %d, data %016llx-%016llx size %lld-%lld-%lld\n",
			     proc->pid, thपढ़ो->pid, t->debug_id,
			     target_proc->pid, target_node->debug_id,
			     (u64)tr->data.ptr.buffer,
			     (u64)tr->data.ptr.offsets,
			     (u64)tr->data_size, (u64)tr->offsets_size,
			     (u64)extra_buffers_size);

	अगर (!reply && !(tr->flags & TF_ONE_WAY))
		t->from = thपढ़ो;
	अन्यथा
		t->from = शून्य;
	t->sender_euid = task_euid(proc->tsk);
	t->to_proc = target_proc;
	t->to_thपढ़ो = target_thपढ़ो;
	t->code = tr->code;
	t->flags = tr->flags;
	t->priority = task_nice(current);

	अगर (target_node && target_node->txn_security_ctx) अणु
		u32 secid;
		माप_प्रकार added_size;

		/*
		 * Arguably this should be the task's subjective LSM secid but
		 * we can't reliably access the subjective creds of a task
		 * other than our own so we must use the objective creds, which
		 * are safe to access.  The करोwnside is that अगर a task is
		 * temporarily overriding it's creds it will not be reflected
		 * here; however, it isn't clear that binder would handle that
		 * हाल well anyway.
		 */
		security_task_माला_लोecid_obj(proc->tsk, &secid);
		ret = security_secid_to_secctx(secid, &secctx, &secctx_sz);
		अगर (ret) अणु
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = ret;
			वापस_error_line = __LINE__;
			जाओ err_get_secctx_failed;
		पूर्ण
		added_size = ALIGN(secctx_sz, माप(u64));
		extra_buffers_size += added_size;
		अगर (extra_buffers_size < added_size) अणु
			/* पूर्णांकeger overflow of extra_buffers_size */
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EINVAL;
			वापस_error_line = __LINE__;
			जाओ err_bad_extra_size;
		पूर्ण
	पूर्ण

	trace_binder_transaction(reply, t, target_node);

	t->buffer = binder_alloc_new_buf(&target_proc->alloc, tr->data_size,
		tr->offsets_size, extra_buffers_size,
		!reply && (t->flags & TF_ONE_WAY), current->tgid);
	अगर (IS_ERR(t->buffer)) अणु
		/*
		 * -ESRCH indicates VMA cleared. The target is dying.
		 */
		वापस_error_param = PTR_ERR(t->buffer);
		वापस_error = वापस_error_param == -ESRCH ?
			BR_DEAD_REPLY : BR_FAILED_REPLY;
		वापस_error_line = __LINE__;
		t->buffer = शून्य;
		जाओ err_binder_alloc_buf_failed;
	पूर्ण
	अगर (secctx) अणु
		पूर्णांक err;
		माप_प्रकार buf_offset = ALIGN(tr->data_size, माप(व्योम *)) +
				    ALIGN(tr->offsets_size, माप(व्योम *)) +
				    ALIGN(extra_buffers_size, माप(व्योम *)) -
				    ALIGN(secctx_sz, माप(u64));

		t->security_ctx = (uपूर्णांकptr_t)t->buffer->user_data + buf_offset;
		err = binder_alloc_copy_to_buffer(&target_proc->alloc,
						  t->buffer, buf_offset,
						  secctx, secctx_sz);
		अगर (err) अणु
			t->security_ctx = 0;
			WARN_ON(1);
		पूर्ण
		security_release_secctx(secctx, secctx_sz);
		secctx = शून्य;
	पूर्ण
	t->buffer->debug_id = t->debug_id;
	t->buffer->transaction = t;
	t->buffer->target_node = target_node;
	t->buffer->clear_on_मुक्त = !!(t->flags & TF_CLEAR_BUF);
	trace_binder_transaction_alloc_buf(t->buffer);

	अगर (binder_alloc_copy_user_to_buffer(
				&target_proc->alloc,
				t->buffer, 0,
				(स्थिर व्योम __user *)
					(uपूर्णांकptr_t)tr->data.ptr.buffer,
				tr->data_size)) अणु
		binder_user_error("%d:%d got transaction with invalid data ptr\n",
				proc->pid, thपढ़ो->pid);
		वापस_error = BR_FAILED_REPLY;
		वापस_error_param = -EFAULT;
		वापस_error_line = __LINE__;
		जाओ err_copy_data_failed;
	पूर्ण
	अगर (binder_alloc_copy_user_to_buffer(
				&target_proc->alloc,
				t->buffer,
				ALIGN(tr->data_size, माप(व्योम *)),
				(स्थिर व्योम __user *)
					(uपूर्णांकptr_t)tr->data.ptr.offsets,
				tr->offsets_size)) अणु
		binder_user_error("%d:%d got transaction with invalid offsets ptr\n",
				proc->pid, thपढ़ो->pid);
		वापस_error = BR_FAILED_REPLY;
		वापस_error_param = -EFAULT;
		वापस_error_line = __LINE__;
		जाओ err_copy_data_failed;
	पूर्ण
	अगर (!IS_ALIGNED(tr->offsets_size, माप(binder_माप_प्रकार))) अणु
		binder_user_error("%d:%d got transaction with invalid offsets size, %lld\n",
				proc->pid, thपढ़ो->pid, (u64)tr->offsets_size);
		वापस_error = BR_FAILED_REPLY;
		वापस_error_param = -EINVAL;
		वापस_error_line = __LINE__;
		जाओ err_bad_offset;
	पूर्ण
	अगर (!IS_ALIGNED(extra_buffers_size, माप(u64))) अणु
		binder_user_error("%d:%d got transaction with unaligned buffers size, %lld\n",
				  proc->pid, thपढ़ो->pid,
				  (u64)extra_buffers_size);
		वापस_error = BR_FAILED_REPLY;
		वापस_error_param = -EINVAL;
		वापस_error_line = __LINE__;
		जाओ err_bad_offset;
	पूर्ण
	off_start_offset = ALIGN(tr->data_size, माप(व्योम *));
	buffer_offset = off_start_offset;
	off_end_offset = off_start_offset + tr->offsets_size;
	sg_buf_offset = ALIGN(off_end_offset, माप(व्योम *));
	sg_buf_end_offset = sg_buf_offset + extra_buffers_size -
		ALIGN(secctx_sz, माप(u64));
	off_min = 0;
	क्रम (buffer_offset = off_start_offset; buffer_offset < off_end_offset;
	     buffer_offset += माप(binder_माप_प्रकार)) अणु
		काष्ठा binder_object_header *hdr;
		माप_प्रकार object_size;
		काष्ठा binder_object object;
		binder_माप_प्रकार object_offset;

		अगर (binder_alloc_copy_from_buffer(&target_proc->alloc,
						  &object_offset,
						  t->buffer,
						  buffer_offset,
						  माप(object_offset))) अणु
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EINVAL;
			वापस_error_line = __LINE__;
			जाओ err_bad_offset;
		पूर्ण
		object_size = binder_get_object(target_proc, t->buffer,
						object_offset, &object);
		अगर (object_size == 0 || object_offset < off_min) अणु
			binder_user_error("%d:%d got transaction with invalid offset (%lld, min %lld max %lld) or object.\n",
					  proc->pid, thपढ़ो->pid,
					  (u64)object_offset,
					  (u64)off_min,
					  (u64)t->buffer->data_size);
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EINVAL;
			वापस_error_line = __LINE__;
			जाओ err_bad_offset;
		पूर्ण

		hdr = &object.hdr;
		off_min = object_offset + object_size;
		चयन (hdr->type) अणु
		हाल BINDER_TYPE_BINDER:
		हाल BINDER_TYPE_WEAK_BINDER: अणु
			काष्ठा flat_binder_object *fp;

			fp = to_flat_binder_object(hdr);
			ret = binder_translate_binder(fp, t, thपढ़ो);

			अगर (ret < 0 ||
			    binder_alloc_copy_to_buffer(&target_proc->alloc,
							t->buffer,
							object_offset,
							fp, माप(*fp))) अणु
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = ret;
				वापस_error_line = __LINE__;
				जाओ err_translate_failed;
			पूर्ण
		पूर्ण अवरोध;
		हाल BINDER_TYPE_HANDLE:
		हाल BINDER_TYPE_WEAK_HANDLE: अणु
			काष्ठा flat_binder_object *fp;

			fp = to_flat_binder_object(hdr);
			ret = binder_translate_handle(fp, t, thपढ़ो);
			अगर (ret < 0 ||
			    binder_alloc_copy_to_buffer(&target_proc->alloc,
							t->buffer,
							object_offset,
							fp, माप(*fp))) अणु
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = ret;
				वापस_error_line = __LINE__;
				जाओ err_translate_failed;
			पूर्ण
		पूर्ण अवरोध;

		हाल BINDER_TYPE_FD: अणु
			काष्ठा binder_fd_object *fp = to_binder_fd_object(hdr);
			binder_माप_प्रकार fd_offset = object_offset +
				(uपूर्णांकptr_t)&fp->fd - (uपूर्णांकptr_t)fp;
			पूर्णांक ret = binder_translate_fd(fp->fd, fd_offset, t,
						      thपढ़ो, in_reply_to);

			fp->pad_binder = 0;
			अगर (ret < 0 ||
			    binder_alloc_copy_to_buffer(&target_proc->alloc,
							t->buffer,
							object_offset,
							fp, माप(*fp))) अणु
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = ret;
				वापस_error_line = __LINE__;
				जाओ err_translate_failed;
			पूर्ण
		पूर्ण अवरोध;
		हाल BINDER_TYPE_FDA: अणु
			काष्ठा binder_object ptr_object;
			binder_माप_प्रकार parent_offset;
			काष्ठा binder_fd_array_object *fda =
				to_binder_fd_array_object(hdr);
			माप_प्रकार num_valid = (buffer_offset - off_start_offset) /
						माप(binder_माप_प्रकार);
			काष्ठा binder_buffer_object *parent =
				binder_validate_ptr(target_proc, t->buffer,
						    &ptr_object, fda->parent,
						    off_start_offset,
						    &parent_offset,
						    num_valid);
			अगर (!parent) अणु
				binder_user_error("%d:%d got transaction with invalid parent offset or type\n",
						  proc->pid, thपढ़ो->pid);
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = -EINVAL;
				वापस_error_line = __LINE__;
				जाओ err_bad_parent;
			पूर्ण
			अगर (!binder_validate_fixup(target_proc, t->buffer,
						   off_start_offset,
						   parent_offset,
						   fda->parent_offset,
						   last_fixup_obj_off,
						   last_fixup_min_off)) अणु
				binder_user_error("%d:%d got transaction with out-of-order buffer fixup\n",
						  proc->pid, thपढ़ो->pid);
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = -EINVAL;
				वापस_error_line = __LINE__;
				जाओ err_bad_parent;
			पूर्ण
			ret = binder_translate_fd_array(fda, parent, t, thपढ़ो,
							in_reply_to);
			अगर (ret < 0) अणु
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = ret;
				वापस_error_line = __LINE__;
				जाओ err_translate_failed;
			पूर्ण
			last_fixup_obj_off = parent_offset;
			last_fixup_min_off =
				fda->parent_offset + माप(u32) * fda->num_fds;
		पूर्ण अवरोध;
		हाल BINDER_TYPE_PTR: अणु
			काष्ठा binder_buffer_object *bp =
				to_binder_buffer_object(hdr);
			माप_प्रकार buf_left = sg_buf_end_offset - sg_buf_offset;
			माप_प्रकार num_valid;

			अगर (bp->length > buf_left) अणु
				binder_user_error("%d:%d got transaction with too large buffer\n",
						  proc->pid, thपढ़ो->pid);
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = -EINVAL;
				वापस_error_line = __LINE__;
				जाओ err_bad_offset;
			पूर्ण
			अगर (binder_alloc_copy_user_to_buffer(
						&target_proc->alloc,
						t->buffer,
						sg_buf_offset,
						(स्थिर व्योम __user *)
							(uपूर्णांकptr_t)bp->buffer,
						bp->length)) अणु
				binder_user_error("%d:%d got transaction with invalid offsets ptr\n",
						  proc->pid, thपढ़ो->pid);
				वापस_error_param = -EFAULT;
				वापस_error = BR_FAILED_REPLY;
				वापस_error_line = __LINE__;
				जाओ err_copy_data_failed;
			पूर्ण
			/* Fixup buffer poपूर्णांकer to target proc address space */
			bp->buffer = (uपूर्णांकptr_t)
				t->buffer->user_data + sg_buf_offset;
			sg_buf_offset += ALIGN(bp->length, माप(u64));

			num_valid = (buffer_offset - off_start_offset) /
					माप(binder_माप_प्रकार);
			ret = binder_fixup_parent(t, thपढ़ो, bp,
						  off_start_offset,
						  num_valid,
						  last_fixup_obj_off,
						  last_fixup_min_off);
			अगर (ret < 0 ||
			    binder_alloc_copy_to_buffer(&target_proc->alloc,
							t->buffer,
							object_offset,
							bp, माप(*bp))) अणु
				वापस_error = BR_FAILED_REPLY;
				वापस_error_param = ret;
				वापस_error_line = __LINE__;
				जाओ err_translate_failed;
			पूर्ण
			last_fixup_obj_off = object_offset;
			last_fixup_min_off = 0;
		पूर्ण अवरोध;
		शेष:
			binder_user_error("%d:%d got transaction with invalid object type, %x\n",
				proc->pid, thपढ़ो->pid, hdr->type);
			वापस_error = BR_FAILED_REPLY;
			वापस_error_param = -EINVAL;
			वापस_error_line = __LINE__;
			जाओ err_bad_object_type;
		पूर्ण
	पूर्ण
	अगर (t->buffer->oneway_spam_suspect)
		tcomplete->type = BINDER_WORK_TRANSACTION_ONEWAY_SPAM_SUSPECT;
	अन्यथा
		tcomplete->type = BINDER_WORK_TRANSACTION_COMPLETE;
	t->work.type = BINDER_WORK_TRANSACTION;

	अगर (reply) अणु
		binder_enqueue_thपढ़ो_work(thपढ़ो, tcomplete);
		binder_inner_proc_lock(target_proc);
		अगर (target_thपढ़ो->is_dead || target_proc->is_frozen) अणु
			वापस_error = target_thपढ़ो->is_dead ?
				BR_DEAD_REPLY : BR_FROZEN_REPLY;
			binder_inner_proc_unlock(target_proc);
			जाओ err_dead_proc_or_thपढ़ो;
		पूर्ण
		BUG_ON(t->buffer->async_transaction != 0);
		binder_pop_transaction_ilocked(target_thपढ़ो, in_reply_to);
		binder_enqueue_thपढ़ो_work_ilocked(target_thपढ़ो, &t->work);
		target_proc->outstanding_txns++;
		binder_inner_proc_unlock(target_proc);
		wake_up_पूर्णांकerruptible_sync(&target_thपढ़ो->रुको);
		binder_मुक्त_transaction(in_reply_to);
	पूर्ण अन्यथा अगर (!(t->flags & TF_ONE_WAY)) अणु
		BUG_ON(t->buffer->async_transaction != 0);
		binder_inner_proc_lock(proc);
		/*
		 * Defer the TRANSACTION_COMPLETE, so we करोn't वापस to
		 * userspace immediately; this allows the target process to
		 * immediately start processing this transaction, reducing
		 * latency. We will then वापस the TRANSACTION_COMPLETE when
		 * the target replies (or there is an error).
		 */
		binder_enqueue_deferred_thपढ़ो_work_ilocked(thपढ़ो, tcomplete);
		t->need_reply = 1;
		t->from_parent = thपढ़ो->transaction_stack;
		thपढ़ो->transaction_stack = t;
		binder_inner_proc_unlock(proc);
		वापस_error = binder_proc_transaction(t,
				target_proc, target_thपढ़ो);
		अगर (वापस_error) अणु
			binder_inner_proc_lock(proc);
			binder_pop_transaction_ilocked(thपढ़ो, t);
			binder_inner_proc_unlock(proc);
			जाओ err_dead_proc_or_thपढ़ो;
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG_ON(target_node == शून्य);
		BUG_ON(t->buffer->async_transaction != 1);
		binder_enqueue_thपढ़ो_work(thपढ़ो, tcomplete);
		वापस_error = binder_proc_transaction(t, target_proc, शून्य);
		अगर (वापस_error)
			जाओ err_dead_proc_or_thपढ़ो;
	पूर्ण
	अगर (target_thपढ़ो)
		binder_thपढ़ो_dec_पंचांगpref(target_thपढ़ो);
	binder_proc_dec_पंचांगpref(target_proc);
	अगर (target_node)
		binder_dec_node_पंचांगpref(target_node);
	/*
	 * ग_लिखो barrier to synchronize with initialization
	 * of log entry
	 */
	smp_wmb();
	WRITE_ONCE(e->debug_id_करोne, t_debug_id);
	वापस;

err_dead_proc_or_thपढ़ो:
	वापस_error_line = __LINE__;
	binder_dequeue_work(proc, tcomplete);
err_translate_failed:
err_bad_object_type:
err_bad_offset:
err_bad_parent:
err_copy_data_failed:
	binder_मुक्त_txn_fixups(t);
	trace_binder_transaction_failed_buffer_release(t->buffer);
	binder_transaction_buffer_release(target_proc, t->buffer,
					  buffer_offset, true);
	अगर (target_node)
		binder_dec_node_पंचांगpref(target_node);
	target_node = शून्य;
	t->buffer->transaction = शून्य;
	binder_alloc_मुक्त_buf(&target_proc->alloc, t->buffer);
err_binder_alloc_buf_failed:
err_bad_extra_size:
	अगर (secctx)
		security_release_secctx(secctx, secctx_sz);
err_get_secctx_failed:
	kमुक्त(tcomplete);
	binder_stats_deleted(BINDER_STAT_TRANSACTION_COMPLETE);
err_alloc_tcomplete_failed:
	अगर (trace_binder_txn_latency_मुक्त_enabled())
		binder_txn_latency_मुक्त(t);
	kमुक्त(t);
	binder_stats_deleted(BINDER_STAT_TRANSACTION);
err_alloc_t_failed:
err_bad_toकरो_list:
err_bad_call_stack:
err_empty_call_stack:
err_dead_binder:
err_invalid_target_handle:
	अगर (target_thपढ़ो)
		binder_thपढ़ो_dec_पंचांगpref(target_thपढ़ो);
	अगर (target_proc)
		binder_proc_dec_पंचांगpref(target_proc);
	अगर (target_node) अणु
		binder_dec_node(target_node, 1, 0);
		binder_dec_node_पंचांगpref(target_node);
	पूर्ण

	binder_debug(BINDER_DEBUG_FAILED_TRANSACTION,
		     "%d:%d transaction failed %d/%d, size %lld-%lld line %d\n",
		     proc->pid, thपढ़ो->pid, वापस_error, वापस_error_param,
		     (u64)tr->data_size, (u64)tr->offsets_size,
		     वापस_error_line);

	अणु
		काष्ठा binder_transaction_log_entry *fe;

		e->वापस_error = वापस_error;
		e->वापस_error_param = वापस_error_param;
		e->वापस_error_line = वापस_error_line;
		fe = binder_transaction_log_add(&binder_transaction_log_failed);
		*fe = *e;
		/*
		 * ग_लिखो barrier to synchronize with initialization
		 * of log entry
		 */
		smp_wmb();
		WRITE_ONCE(e->debug_id_करोne, t_debug_id);
		WRITE_ONCE(fe->debug_id_करोne, t_debug_id);
	पूर्ण

	BUG_ON(thपढ़ो->वापस_error.cmd != BR_OK);
	अगर (in_reply_to) अणु
		thपढ़ो->वापस_error.cmd = BR_TRANSACTION_COMPLETE;
		binder_enqueue_thपढ़ो_work(thपढ़ो, &thपढ़ो->वापस_error.work);
		binder_send_failed_reply(in_reply_to, वापस_error);
	पूर्ण अन्यथा अणु
		thपढ़ो->वापस_error.cmd = वापस_error;
		binder_enqueue_thपढ़ो_work(thपढ़ो, &thपढ़ो->वापस_error.work);
	पूर्ण
पूर्ण

/**
 * binder_मुक्त_buf() - मुक्त the specअगरied buffer
 * @proc:	binder proc that owns buffer
 * @buffer:	buffer to be मुक्तd
 *
 * If buffer क्रम an async transaction, enqueue the next async
 * transaction from the node.
 *
 * Cleanup buffer and मुक्त it.
 */
अटल व्योम
binder_मुक्त_buf(काष्ठा binder_proc *proc, काष्ठा binder_buffer *buffer)
अणु
	binder_inner_proc_lock(proc);
	अगर (buffer->transaction) अणु
		buffer->transaction->buffer = शून्य;
		buffer->transaction = शून्य;
	पूर्ण
	binder_inner_proc_unlock(proc);
	अगर (buffer->async_transaction && buffer->target_node) अणु
		काष्ठा binder_node *buf_node;
		काष्ठा binder_work *w;

		buf_node = buffer->target_node;
		binder_node_inner_lock(buf_node);
		BUG_ON(!buf_node->has_async_transaction);
		BUG_ON(buf_node->proc != proc);
		w = binder_dequeue_work_head_ilocked(
				&buf_node->async_toकरो);
		अगर (!w) अणु
			buf_node->has_async_transaction = false;
		पूर्ण अन्यथा अणु
			binder_enqueue_work_ilocked(
					w, &proc->toकरो);
			binder_wakeup_proc_ilocked(proc);
		पूर्ण
		binder_node_inner_unlock(buf_node);
	पूर्ण
	trace_binder_transaction_buffer_release(buffer);
	binder_transaction_buffer_release(proc, buffer, 0, false);
	binder_alloc_मुक्त_buf(&proc->alloc, buffer);
पूर्ण

अटल पूर्णांक binder_thपढ़ो_ग_लिखो(काष्ठा binder_proc *proc,
			काष्ठा binder_thपढ़ो *thपढ़ो,
			binder_uपूर्णांकptr_t binder_buffer, माप_प्रकार size,
			binder_माप_प्रकार *consumed)
अणु
	uपूर्णांक32_t cmd;
	काष्ठा binder_context *context = proc->context;
	व्योम __user *buffer = (व्योम __user *)(uपूर्णांकptr_t)binder_buffer;
	व्योम __user *ptr = buffer + *consumed;
	व्योम __user *end = buffer + size;

	जबतक (ptr < end && thपढ़ो->वापस_error.cmd == BR_OK) अणु
		पूर्णांक ret;

		अगर (get_user(cmd, (uपूर्णांक32_t __user *)ptr))
			वापस -EFAULT;
		ptr += माप(uपूर्णांक32_t);
		trace_binder_command(cmd);
		अगर (_IOC_NR(cmd) < ARRAY_SIZE(binder_stats.bc)) अणु
			atomic_inc(&binder_stats.bc[_IOC_NR(cmd)]);
			atomic_inc(&proc->stats.bc[_IOC_NR(cmd)]);
			atomic_inc(&thपढ़ो->stats.bc[_IOC_NR(cmd)]);
		पूर्ण
		चयन (cmd) अणु
		हाल BC_INCREFS:
		हाल BC_ACQUIRE:
		हाल BC_RELEASE:
		हाल BC_DECREFS: अणु
			uपूर्णांक32_t target;
			स्थिर अक्षर *debug_string;
			bool strong = cmd == BC_ACQUIRE || cmd == BC_RELEASE;
			bool increment = cmd == BC_INCREFS || cmd == BC_ACQUIRE;
			काष्ठा binder_ref_data rdata;

			अगर (get_user(target, (uपूर्णांक32_t __user *)ptr))
				वापस -EFAULT;

			ptr += माप(uपूर्णांक32_t);
			ret = -1;
			अगर (increment && !target) अणु
				काष्ठा binder_node *ctx_mgr_node;

				mutex_lock(&context->context_mgr_node_lock);
				ctx_mgr_node = context->binder_context_mgr_node;
				अगर (ctx_mgr_node) अणु
					अगर (ctx_mgr_node->proc == proc) अणु
						binder_user_error("%d:%d context manager tried to acquire desc 0\n",
								  proc->pid, thपढ़ो->pid);
						mutex_unlock(&context->context_mgr_node_lock);
						वापस -EINVAL;
					पूर्ण
					ret = binder_inc_ref_क्रम_node(
							proc, ctx_mgr_node,
							strong, शून्य, &rdata);
				पूर्ण
				mutex_unlock(&context->context_mgr_node_lock);
			पूर्ण
			अगर (ret)
				ret = binder_update_ref_क्रम_handle(
						proc, target, increment, strong,
						&rdata);
			अगर (!ret && rdata.desc != target) अणु
				binder_user_error("%d:%d tried to acquire reference to desc %d, got %d instead\n",
					proc->pid, thपढ़ो->pid,
					target, rdata.desc);
			पूर्ण
			चयन (cmd) अणु
			हाल BC_INCREFS:
				debug_string = "IncRefs";
				अवरोध;
			हाल BC_ACQUIRE:
				debug_string = "Acquire";
				अवरोध;
			हाल BC_RELEASE:
				debug_string = "Release";
				अवरोध;
			हाल BC_DECREFS:
			शेष:
				debug_string = "DecRefs";
				अवरोध;
			पूर्ण
			अगर (ret) अणु
				binder_user_error("%d:%d %s %d refcount change on invalid ref %d ret %d\n",
					proc->pid, thपढ़ो->pid, debug_string,
					strong, target, ret);
				अवरोध;
			पूर्ण
			binder_debug(BINDER_DEBUG_USER_REFS,
				     "%d:%d %s ref %d desc %d s %d w %d\n",
				     proc->pid, thपढ़ो->pid, debug_string,
				     rdata.debug_id, rdata.desc, rdata.strong,
				     rdata.weak);
			अवरोध;
		पूर्ण
		हाल BC_INCREFS_DONE:
		हाल BC_ACQUIRE_DONE: अणु
			binder_uपूर्णांकptr_t node_ptr;
			binder_uपूर्णांकptr_t cookie;
			काष्ठा binder_node *node;
			bool मुक्त_node;

			अगर (get_user(node_ptr, (binder_uपूर्णांकptr_t __user *)ptr))
				वापस -EFAULT;
			ptr += माप(binder_uपूर्णांकptr_t);
			अगर (get_user(cookie, (binder_uपूर्णांकptr_t __user *)ptr))
				वापस -EFAULT;
			ptr += माप(binder_uपूर्णांकptr_t);
			node = binder_get_node(proc, node_ptr);
			अगर (node == शून्य) अणु
				binder_user_error("%d:%d %s u%016llx no match\n",
					proc->pid, thपढ़ो->pid,
					cmd == BC_INCREFS_DONE ?
					"BC_INCREFS_DONE" :
					"BC_ACQUIRE_DONE",
					(u64)node_ptr);
				अवरोध;
			पूर्ण
			अगर (cookie != node->cookie) अणु
				binder_user_error("%d:%d %s u%016llx node %d cookie mismatch %016llx != %016llx\n",
					proc->pid, thपढ़ो->pid,
					cmd == BC_INCREFS_DONE ?
					"BC_INCREFS_DONE" : "BC_ACQUIRE_DONE",
					(u64)node_ptr, node->debug_id,
					(u64)cookie, (u64)node->cookie);
				binder_put_node(node);
				अवरोध;
			पूर्ण
			binder_node_inner_lock(node);
			अगर (cmd == BC_ACQUIRE_DONE) अणु
				अगर (node->pending_strong_ref == 0) अणु
					binder_user_error("%d:%d BC_ACQUIRE_DONE node %d has no pending acquire request\n",
						proc->pid, thपढ़ो->pid,
						node->debug_id);
					binder_node_inner_unlock(node);
					binder_put_node(node);
					अवरोध;
				पूर्ण
				node->pending_strong_ref = 0;
			पूर्ण अन्यथा अणु
				अगर (node->pending_weak_ref == 0) अणु
					binder_user_error("%d:%d BC_INCREFS_DONE node %d has no pending increfs request\n",
						proc->pid, thपढ़ो->pid,
						node->debug_id);
					binder_node_inner_unlock(node);
					binder_put_node(node);
					अवरोध;
				पूर्ण
				node->pending_weak_ref = 0;
			पूर्ण
			मुक्त_node = binder_dec_node_nilocked(node,
					cmd == BC_ACQUIRE_DONE, 0);
			WARN_ON(मुक्त_node);
			binder_debug(BINDER_DEBUG_USER_REFS,
				     "%d:%d %s node %d ls %d lw %d tr %d\n",
				     proc->pid, thपढ़ो->pid,
				     cmd == BC_INCREFS_DONE ? "BC_INCREFS_DONE" : "BC_ACQUIRE_DONE",
				     node->debug_id, node->local_strong_refs,
				     node->local_weak_refs, node->पंचांगp_refs);
			binder_node_inner_unlock(node);
			binder_put_node(node);
			अवरोध;
		पूर्ण
		हाल BC_ATTEMPT_ACQUIRE:
			pr_err("BC_ATTEMPT_ACQUIRE not supported\n");
			वापस -EINVAL;
		हाल BC_ACQUIRE_RESULT:
			pr_err("BC_ACQUIRE_RESULT not supported\n");
			वापस -EINVAL;

		हाल BC_FREE_BUFFER: अणु
			binder_uपूर्णांकptr_t data_ptr;
			काष्ठा binder_buffer *buffer;

			अगर (get_user(data_ptr, (binder_uपूर्णांकptr_t __user *)ptr))
				वापस -EFAULT;
			ptr += माप(binder_uपूर्णांकptr_t);

			buffer = binder_alloc_prepare_to_मुक्त(&proc->alloc,
							      data_ptr);
			अगर (IS_ERR_OR_शून्य(buffer)) अणु
				अगर (PTR_ERR(buffer) == -EPERM) अणु
					binder_user_error(
						"%d:%d BC_FREE_BUFFER u%016llx matched unreturned or currently freeing buffer\n",
						proc->pid, thपढ़ो->pid,
						(u64)data_ptr);
				पूर्ण अन्यथा अणु
					binder_user_error(
						"%d:%d BC_FREE_BUFFER u%016llx no match\n",
						proc->pid, thपढ़ो->pid,
						(u64)data_ptr);
				पूर्ण
				अवरोध;
			पूर्ण
			binder_debug(BINDER_DEBUG_FREE_BUFFER,
				     "%d:%d BC_FREE_BUFFER u%016llx found buffer %d for %s transaction\n",
				     proc->pid, thपढ़ो->pid, (u64)data_ptr,
				     buffer->debug_id,
				     buffer->transaction ? "active" : "finished");
			binder_मुक्त_buf(proc, buffer);
			अवरोध;
		पूर्ण

		हाल BC_TRANSACTION_SG:
		हाल BC_REPLY_SG: अणु
			काष्ठा binder_transaction_data_sg tr;

			अगर (copy_from_user(&tr, ptr, माप(tr)))
				वापस -EFAULT;
			ptr += माप(tr);
			binder_transaction(proc, thपढ़ो, &tr.transaction_data,
					   cmd == BC_REPLY_SG, tr.buffers_size);
			अवरोध;
		पूर्ण
		हाल BC_TRANSACTION:
		हाल BC_REPLY: अणु
			काष्ठा binder_transaction_data tr;

			अगर (copy_from_user(&tr, ptr, माप(tr)))
				वापस -EFAULT;
			ptr += माप(tr);
			binder_transaction(proc, thपढ़ो, &tr,
					   cmd == BC_REPLY, 0);
			अवरोध;
		पूर्ण

		हाल BC_REGISTER_LOOPER:
			binder_debug(BINDER_DEBUG_THREADS,
				     "%d:%d BC_REGISTER_LOOPER\n",
				     proc->pid, thपढ़ो->pid);
			binder_inner_proc_lock(proc);
			अगर (thपढ़ो->looper & BINDER_LOOPER_STATE_ENTERED) अणु
				thपढ़ो->looper |= BINDER_LOOPER_STATE_INVALID;
				binder_user_error("%d:%d ERROR: BC_REGISTER_LOOPER called after BC_ENTER_LOOPER\n",
					proc->pid, thपढ़ो->pid);
			पूर्ण अन्यथा अगर (proc->requested_thपढ़ोs == 0) अणु
				thपढ़ो->looper |= BINDER_LOOPER_STATE_INVALID;
				binder_user_error("%d:%d ERROR: BC_REGISTER_LOOPER called without request\n",
					proc->pid, thपढ़ो->pid);
			पूर्ण अन्यथा अणु
				proc->requested_thपढ़ोs--;
				proc->requested_thपढ़ोs_started++;
			पूर्ण
			thपढ़ो->looper |= BINDER_LOOPER_STATE_REGISTERED;
			binder_inner_proc_unlock(proc);
			अवरोध;
		हाल BC_ENTER_LOOPER:
			binder_debug(BINDER_DEBUG_THREADS,
				     "%d:%d BC_ENTER_LOOPER\n",
				     proc->pid, thपढ़ो->pid);
			अगर (thपढ़ो->looper & BINDER_LOOPER_STATE_REGISTERED) अणु
				thपढ़ो->looper |= BINDER_LOOPER_STATE_INVALID;
				binder_user_error("%d:%d ERROR: BC_ENTER_LOOPER called after BC_REGISTER_LOOPER\n",
					proc->pid, thपढ़ो->pid);
			पूर्ण
			thपढ़ो->looper |= BINDER_LOOPER_STATE_ENTERED;
			अवरोध;
		हाल BC_EXIT_LOOPER:
			binder_debug(BINDER_DEBUG_THREADS,
				     "%d:%d BC_EXIT_LOOPER\n",
				     proc->pid, thपढ़ो->pid);
			thपढ़ो->looper |= BINDER_LOOPER_STATE_EXITED;
			अवरोध;

		हाल BC_REQUEST_DEATH_NOTIFICATION:
		हाल BC_CLEAR_DEATH_NOTIFICATION: अणु
			uपूर्णांक32_t target;
			binder_uपूर्णांकptr_t cookie;
			काष्ठा binder_ref *ref;
			काष्ठा binder_ref_death *death = शून्य;

			अगर (get_user(target, (uपूर्णांक32_t __user *)ptr))
				वापस -EFAULT;
			ptr += माप(uपूर्णांक32_t);
			अगर (get_user(cookie, (binder_uपूर्णांकptr_t __user *)ptr))
				वापस -EFAULT;
			ptr += माप(binder_uपूर्णांकptr_t);
			अगर (cmd == BC_REQUEST_DEATH_NOTIFICATION) अणु
				/*
				 * Allocate memory क्रम death notअगरication
				 * beक्रमe taking lock
				 */
				death = kzalloc(माप(*death), GFP_KERNEL);
				अगर (death == शून्य) अणु
					WARN_ON(thपढ़ो->वापस_error.cmd !=
						BR_OK);
					thपढ़ो->वापस_error.cmd = BR_ERROR;
					binder_enqueue_thपढ़ो_work(
						thपढ़ो,
						&thपढ़ो->वापस_error.work);
					binder_debug(
						BINDER_DEBUG_FAILED_TRANSACTION,
						"%d:%d BC_REQUEST_DEATH_NOTIFICATION failed\n",
						proc->pid, thपढ़ो->pid);
					अवरोध;
				पूर्ण
			पूर्ण
			binder_proc_lock(proc);
			ref = binder_get_ref_olocked(proc, target, false);
			अगर (ref == शून्य) अणु
				binder_user_error("%d:%d %s invalid ref %d\n",
					proc->pid, thपढ़ो->pid,
					cmd == BC_REQUEST_DEATH_NOTIFICATION ?
					"BC_REQUEST_DEATH_NOTIFICATION" :
					"BC_CLEAR_DEATH_NOTIFICATION",
					target);
				binder_proc_unlock(proc);
				kमुक्त(death);
				अवरोध;
			पूर्ण

			binder_debug(BINDER_DEBUG_DEATH_NOTIFICATION,
				     "%d:%d %s %016llx ref %d desc %d s %d w %d for node %d\n",
				     proc->pid, thपढ़ो->pid,
				     cmd == BC_REQUEST_DEATH_NOTIFICATION ?
				     "BC_REQUEST_DEATH_NOTIFICATION" :
				     "BC_CLEAR_DEATH_NOTIFICATION",
				     (u64)cookie, ref->data.debug_id,
				     ref->data.desc, ref->data.strong,
				     ref->data.weak, ref->node->debug_id);

			binder_node_lock(ref->node);
			अगर (cmd == BC_REQUEST_DEATH_NOTIFICATION) अणु
				अगर (ref->death) अणु
					binder_user_error("%d:%d BC_REQUEST_DEATH_NOTIFICATION death notification already set\n",
						proc->pid, thपढ़ो->pid);
					binder_node_unlock(ref->node);
					binder_proc_unlock(proc);
					kमुक्त(death);
					अवरोध;
				पूर्ण
				binder_stats_created(BINDER_STAT_DEATH);
				INIT_LIST_HEAD(&death->work.entry);
				death->cookie = cookie;
				ref->death = death;
				अगर (ref->node->proc == शून्य) अणु
					ref->death->work.type = BINDER_WORK_DEAD_BINDER;

					binder_inner_proc_lock(proc);
					binder_enqueue_work_ilocked(
						&ref->death->work, &proc->toकरो);
					binder_wakeup_proc_ilocked(proc);
					binder_inner_proc_unlock(proc);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (ref->death == शून्य) अणु
					binder_user_error("%d:%d BC_CLEAR_DEATH_NOTIFICATION death notification not active\n",
						proc->pid, thपढ़ो->pid);
					binder_node_unlock(ref->node);
					binder_proc_unlock(proc);
					अवरोध;
				पूर्ण
				death = ref->death;
				अगर (death->cookie != cookie) अणु
					binder_user_error("%d:%d BC_CLEAR_DEATH_NOTIFICATION death notification cookie mismatch %016llx != %016llx\n",
						proc->pid, thपढ़ो->pid,
						(u64)death->cookie,
						(u64)cookie);
					binder_node_unlock(ref->node);
					binder_proc_unlock(proc);
					अवरोध;
				पूर्ण
				ref->death = शून्य;
				binder_inner_proc_lock(proc);
				अगर (list_empty(&death->work.entry)) अणु
					death->work.type = BINDER_WORK_CLEAR_DEATH_NOTIFICATION;
					अगर (thपढ़ो->looper &
					    (BINDER_LOOPER_STATE_REGISTERED |
					     BINDER_LOOPER_STATE_ENTERED))
						binder_enqueue_thपढ़ो_work_ilocked(
								thपढ़ो,
								&death->work);
					अन्यथा अणु
						binder_enqueue_work_ilocked(
								&death->work,
								&proc->toकरो);
						binder_wakeup_proc_ilocked(
								proc);
					पूर्ण
				पूर्ण अन्यथा अणु
					BUG_ON(death->work.type != BINDER_WORK_DEAD_BINDER);
					death->work.type = BINDER_WORK_DEAD_BINDER_AND_CLEAR;
				पूर्ण
				binder_inner_proc_unlock(proc);
			पूर्ण
			binder_node_unlock(ref->node);
			binder_proc_unlock(proc);
		पूर्ण अवरोध;
		हाल BC_DEAD_BINDER_DONE: अणु
			काष्ठा binder_work *w;
			binder_uपूर्णांकptr_t cookie;
			काष्ठा binder_ref_death *death = शून्य;

			अगर (get_user(cookie, (binder_uपूर्णांकptr_t __user *)ptr))
				वापस -EFAULT;

			ptr += माप(cookie);
			binder_inner_proc_lock(proc);
			list_क्रम_each_entry(w, &proc->delivered_death,
					    entry) अणु
				काष्ठा binder_ref_death *पंचांगp_death =
					container_of(w,
						     काष्ठा binder_ref_death,
						     work);

				अगर (पंचांगp_death->cookie == cookie) अणु
					death = पंचांगp_death;
					अवरोध;
				पूर्ण
			पूर्ण
			binder_debug(BINDER_DEBUG_DEAD_BINDER,
				     "%d:%d BC_DEAD_BINDER_DONE %016llx found %pK\n",
				     proc->pid, thपढ़ो->pid, (u64)cookie,
				     death);
			अगर (death == शून्य) अणु
				binder_user_error("%d:%d BC_DEAD_BINDER_DONE %016llx not found\n",
					proc->pid, thपढ़ो->pid, (u64)cookie);
				binder_inner_proc_unlock(proc);
				अवरोध;
			पूर्ण
			binder_dequeue_work_ilocked(&death->work);
			अगर (death->work.type == BINDER_WORK_DEAD_BINDER_AND_CLEAR) अणु
				death->work.type = BINDER_WORK_CLEAR_DEATH_NOTIFICATION;
				अगर (thपढ़ो->looper &
					(BINDER_LOOPER_STATE_REGISTERED |
					 BINDER_LOOPER_STATE_ENTERED))
					binder_enqueue_thपढ़ो_work_ilocked(
						thपढ़ो, &death->work);
				अन्यथा अणु
					binder_enqueue_work_ilocked(
							&death->work,
							&proc->toकरो);
					binder_wakeup_proc_ilocked(proc);
				पूर्ण
			पूर्ण
			binder_inner_proc_unlock(proc);
		पूर्ण अवरोध;

		शेष:
			pr_err("%d:%d unknown command %d\n",
			       proc->pid, thपढ़ो->pid, cmd);
			वापस -EINVAL;
		पूर्ण
		*consumed = ptr - buffer;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम binder_stat_br(काष्ठा binder_proc *proc,
			   काष्ठा binder_thपढ़ो *thपढ़ो, uपूर्णांक32_t cmd)
अणु
	trace_binder_वापस(cmd);
	अगर (_IOC_NR(cmd) < ARRAY_SIZE(binder_stats.br)) अणु
		atomic_inc(&binder_stats.br[_IOC_NR(cmd)]);
		atomic_inc(&proc->stats.br[_IOC_NR(cmd)]);
		atomic_inc(&thपढ़ो->stats.br[_IOC_NR(cmd)]);
	पूर्ण
पूर्ण

अटल पूर्णांक binder_put_node_cmd(काष्ठा binder_proc *proc,
			       काष्ठा binder_thपढ़ो *thपढ़ो,
			       व्योम __user **ptrp,
			       binder_uपूर्णांकptr_t node_ptr,
			       binder_uपूर्णांकptr_t node_cookie,
			       पूर्णांक node_debug_id,
			       uपूर्णांक32_t cmd, स्थिर अक्षर *cmd_name)
अणु
	व्योम __user *ptr = *ptrp;

	अगर (put_user(cmd, (uपूर्णांक32_t __user *)ptr))
		वापस -EFAULT;
	ptr += माप(uपूर्णांक32_t);

	अगर (put_user(node_ptr, (binder_uपूर्णांकptr_t __user *)ptr))
		वापस -EFAULT;
	ptr += माप(binder_uपूर्णांकptr_t);

	अगर (put_user(node_cookie, (binder_uपूर्णांकptr_t __user *)ptr))
		वापस -EFAULT;
	ptr += माप(binder_uपूर्णांकptr_t);

	binder_stat_br(proc, thपढ़ो, cmd);
	binder_debug(BINDER_DEBUG_USER_REFS, "%d:%d %s %d u%016llx c%016llx\n",
		     proc->pid, thपढ़ो->pid, cmd_name, node_debug_id,
		     (u64)node_ptr, (u64)node_cookie);

	*ptrp = ptr;
	वापस 0;
पूर्ण

अटल पूर्णांक binder_रुको_क्रम_work(काष्ठा binder_thपढ़ो *thपढ़ो,
				bool करो_proc_work)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा binder_proc *proc = thपढ़ो->proc;
	पूर्णांक ret = 0;

	मुक्तzer_करो_not_count();
	binder_inner_proc_lock(proc);
	क्रम (;;) अणु
		prepare_to_रुको(&thपढ़ो->रुको, &रुको, TASK_INTERRUPTIBLE);
		अगर (binder_has_work_ilocked(thपढ़ो, करो_proc_work))
			अवरोध;
		अगर (करो_proc_work)
			list_add(&thपढ़ो->रुकोing_thपढ़ो_node,
				 &proc->रुकोing_thपढ़ोs);
		binder_inner_proc_unlock(proc);
		schedule();
		binder_inner_proc_lock(proc);
		list_del_init(&thपढ़ो->रुकोing_thपढ़ो_node);
		अगर (संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण
	पूर्ण
	finish_रुको(&thपढ़ो->रुको, &रुको);
	binder_inner_proc_unlock(proc);
	मुक्तzer_count();

	वापस ret;
पूर्ण

/**
 * binder_apply_fd_fixups() - finish fd translation
 * @proc:         binder_proc associated @t->buffer
 * @t:	binder transaction with list of fd fixups
 *
 * Now that we are in the context of the transaction target
 * process, we can allocate and install fds. Process the
 * list of fds to translate and fixup the buffer with the
 * new fds.
 *
 * If we fail to allocate an fd, then मुक्त the resources by
 * fput'ing files that have not been processed and ksys_close'ing
 * any fds that have alपढ़ोy been allocated.
 */
अटल पूर्णांक binder_apply_fd_fixups(काष्ठा binder_proc *proc,
				  काष्ठा binder_transaction *t)
अणु
	काष्ठा binder_txn_fd_fixup *fixup, *पंचांगp;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(fixup, &t->fd_fixups, fixup_entry) अणु
		पूर्णांक fd = get_unused_fd_flags(O_CLOEXEC);

		अगर (fd < 0) अणु
			binder_debug(BINDER_DEBUG_TRANSACTION,
				     "failed fd fixup txn %d fd %d\n",
				     t->debug_id, fd);
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		binder_debug(BINDER_DEBUG_TRANSACTION,
			     "fd fixup txn %d fd %d\n",
			     t->debug_id, fd);
		trace_binder_transaction_fd_recv(t, fd, fixup->offset);
		fd_install(fd, fixup->file);
		fixup->file = शून्य;
		अगर (binder_alloc_copy_to_buffer(&proc->alloc, t->buffer,
						fixup->offset, &fd,
						माप(u32))) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(fixup, पंचांगp, &t->fd_fixups, fixup_entry) अणु
		अगर (fixup->file) अणु
			fput(fixup->file);
		पूर्ण अन्यथा अगर (ret) अणु
			u32 fd;
			पूर्णांक err;

			err = binder_alloc_copy_from_buffer(&proc->alloc, &fd,
							    t->buffer,
							    fixup->offset,
							    माप(fd));
			WARN_ON(err);
			अगर (!err)
				binder_deferred_fd_बंद(fd);
		पूर्ण
		list_del(&fixup->fixup_entry);
		kमुक्त(fixup);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक binder_thपढ़ो_पढ़ो(काष्ठा binder_proc *proc,
			      काष्ठा binder_thपढ़ो *thपढ़ो,
			      binder_uपूर्णांकptr_t binder_buffer, माप_प्रकार size,
			      binder_माप_प्रकार *consumed, पूर्णांक non_block)
अणु
	व्योम __user *buffer = (व्योम __user *)(uपूर्णांकptr_t)binder_buffer;
	व्योम __user *ptr = buffer + *consumed;
	व्योम __user *end = buffer + size;

	पूर्णांक ret = 0;
	पूर्णांक रुको_क्रम_proc_work;

	अगर (*consumed == 0) अणु
		अगर (put_user(BR_NOOP, (uपूर्णांक32_t __user *)ptr))
			वापस -EFAULT;
		ptr += माप(uपूर्णांक32_t);
	पूर्ण

retry:
	binder_inner_proc_lock(proc);
	रुको_क्रम_proc_work = binder_available_क्रम_proc_work_ilocked(thपढ़ो);
	binder_inner_proc_unlock(proc);

	thपढ़ो->looper |= BINDER_LOOPER_STATE_WAITING;

	trace_binder_रुको_क्रम_work(रुको_क्रम_proc_work,
				   !!thपढ़ो->transaction_stack,
				   !binder_worklist_empty(proc, &thपढ़ो->toकरो));
	अगर (रुको_क्रम_proc_work) अणु
		अगर (!(thपढ़ो->looper & (BINDER_LOOPER_STATE_REGISTERED |
					BINDER_LOOPER_STATE_ENTERED))) अणु
			binder_user_error("%d:%d ERROR: Thread waiting for process work before calling BC_REGISTER_LOOPER or BC_ENTER_LOOPER (state %x)\n",
				proc->pid, thपढ़ो->pid, thपढ़ो->looper);
			रुको_event_पूर्णांकerruptible(binder_user_error_रुको,
						 binder_stop_on_user_error < 2);
		पूर्ण
		binder_set_nice(proc->शेष_priority);
	पूर्ण

	अगर (non_block) अणु
		अगर (!binder_has_work(thपढ़ो, रुको_क्रम_proc_work))
			ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		ret = binder_रुको_क्रम_work(thपढ़ो, रुको_क्रम_proc_work);
	पूर्ण

	thपढ़ो->looper &= ~BINDER_LOOPER_STATE_WAITING;

	अगर (ret)
		वापस ret;

	जबतक (1) अणु
		uपूर्णांक32_t cmd;
		काष्ठा binder_transaction_data_secctx tr;
		काष्ठा binder_transaction_data *trd = &tr.transaction_data;
		काष्ठा binder_work *w = शून्य;
		काष्ठा list_head *list = शून्य;
		काष्ठा binder_transaction *t = शून्य;
		काष्ठा binder_thपढ़ो *t_from;
		माप_प्रकार trsize = माप(*trd);

		binder_inner_proc_lock(proc);
		अगर (!binder_worklist_empty_ilocked(&thपढ़ो->toकरो))
			list = &thपढ़ो->toकरो;
		अन्यथा अगर (!binder_worklist_empty_ilocked(&proc->toकरो) &&
			   रुको_क्रम_proc_work)
			list = &proc->toकरो;
		अन्यथा अणु
			binder_inner_proc_unlock(proc);

			/* no data added */
			अगर (ptr - buffer == 4 && !thपढ़ो->looper_need_वापस)
				जाओ retry;
			अवरोध;
		पूर्ण

		अगर (end - ptr < माप(tr) + 4) अणु
			binder_inner_proc_unlock(proc);
			अवरोध;
		पूर्ण
		w = binder_dequeue_work_head_ilocked(list);
		अगर (binder_worklist_empty_ilocked(&thपढ़ो->toकरो))
			thपढ़ो->process_toकरो = false;

		चयन (w->type) अणु
		हाल BINDER_WORK_TRANSACTION: अणु
			binder_inner_proc_unlock(proc);
			t = container_of(w, काष्ठा binder_transaction, work);
		पूर्ण अवरोध;
		हाल BINDER_WORK_RETURN_ERROR: अणु
			काष्ठा binder_error *e = container_of(
					w, काष्ठा binder_error, work);

			WARN_ON(e->cmd == BR_OK);
			binder_inner_proc_unlock(proc);
			अगर (put_user(e->cmd, (uपूर्णांक32_t __user *)ptr))
				वापस -EFAULT;
			cmd = e->cmd;
			e->cmd = BR_OK;
			ptr += माप(uपूर्णांक32_t);

			binder_stat_br(proc, thपढ़ो, cmd);
		पूर्ण अवरोध;
		हाल BINDER_WORK_TRANSACTION_COMPLETE:
		हाल BINDER_WORK_TRANSACTION_ONEWAY_SPAM_SUSPECT: अणु
			अगर (proc->oneway_spam_detection_enabled &&
				   w->type == BINDER_WORK_TRANSACTION_ONEWAY_SPAM_SUSPECT)
				cmd = BR_ONEWAY_SPAM_SUSPECT;
			अन्यथा
				cmd = BR_TRANSACTION_COMPLETE;
			binder_inner_proc_unlock(proc);
			kमुक्त(w);
			binder_stats_deleted(BINDER_STAT_TRANSACTION_COMPLETE);
			अगर (put_user(cmd, (uपूर्णांक32_t __user *)ptr))
				वापस -EFAULT;
			ptr += माप(uपूर्णांक32_t);

			binder_stat_br(proc, thपढ़ो, cmd);
			binder_debug(BINDER_DEBUG_TRANSACTION_COMPLETE,
				     "%d:%d BR_TRANSACTION_COMPLETE\n",
				     proc->pid, thपढ़ो->pid);
		पूर्ण अवरोध;
		हाल BINDER_WORK_NODE: अणु
			काष्ठा binder_node *node = container_of(w, काष्ठा binder_node, work);
			पूर्णांक strong, weak;
			binder_uपूर्णांकptr_t node_ptr = node->ptr;
			binder_uपूर्णांकptr_t node_cookie = node->cookie;
			पूर्णांक node_debug_id = node->debug_id;
			पूर्णांक has_weak_ref;
			पूर्णांक has_strong_ref;
			व्योम __user *orig_ptr = ptr;

			BUG_ON(proc != node->proc);
			strong = node->पूर्णांकernal_strong_refs ||
					node->local_strong_refs;
			weak = !hlist_empty(&node->refs) ||
					node->local_weak_refs ||
					node->पंचांगp_refs || strong;
			has_strong_ref = node->has_strong_ref;
			has_weak_ref = node->has_weak_ref;

			अगर (weak && !has_weak_ref) अणु
				node->has_weak_ref = 1;
				node->pending_weak_ref = 1;
				node->local_weak_refs++;
			पूर्ण
			अगर (strong && !has_strong_ref) अणु
				node->has_strong_ref = 1;
				node->pending_strong_ref = 1;
				node->local_strong_refs++;
			पूर्ण
			अगर (!strong && has_strong_ref)
				node->has_strong_ref = 0;
			अगर (!weak && has_weak_ref)
				node->has_weak_ref = 0;
			अगर (!weak && !strong) अणु
				binder_debug(BINDER_DEBUG_INTERNAL_REFS,
					     "%d:%d node %d u%016llx c%016llx deleted\n",
					     proc->pid, thपढ़ो->pid,
					     node_debug_id,
					     (u64)node_ptr,
					     (u64)node_cookie);
				rb_erase(&node->rb_node, &proc->nodes);
				binder_inner_proc_unlock(proc);
				binder_node_lock(node);
				/*
				 * Acquire the node lock beक्रमe मुक्तing the
				 * node to serialize with other thपढ़ोs that
				 * may have been holding the node lock जबतक
				 * decrementing this node (aव्योमs race where
				 * this thपढ़ो मुक्तs जबतक the other thपढ़ो
				 * is unlocking the node after the final
				 * decrement)
				 */
				binder_node_unlock(node);
				binder_मुक्त_node(node);
			पूर्ण अन्यथा
				binder_inner_proc_unlock(proc);

			अगर (weak && !has_weak_ref)
				ret = binder_put_node_cmd(
						proc, thपढ़ो, &ptr, node_ptr,
						node_cookie, node_debug_id,
						BR_INCREFS, "BR_INCREFS");
			अगर (!ret && strong && !has_strong_ref)
				ret = binder_put_node_cmd(
						proc, thपढ़ो, &ptr, node_ptr,
						node_cookie, node_debug_id,
						BR_ACQUIRE, "BR_ACQUIRE");
			अगर (!ret && !strong && has_strong_ref)
				ret = binder_put_node_cmd(
						proc, thपढ़ो, &ptr, node_ptr,
						node_cookie, node_debug_id,
						BR_RELEASE, "BR_RELEASE");
			अगर (!ret && !weak && has_weak_ref)
				ret = binder_put_node_cmd(
						proc, thपढ़ो, &ptr, node_ptr,
						node_cookie, node_debug_id,
						BR_DECREFS, "BR_DECREFS");
			अगर (orig_ptr == ptr)
				binder_debug(BINDER_DEBUG_INTERNAL_REFS,
					     "%d:%d node %d u%016llx c%016llx state unchanged\n",
					     proc->pid, thपढ़ो->pid,
					     node_debug_id,
					     (u64)node_ptr,
					     (u64)node_cookie);
			अगर (ret)
				वापस ret;
		पूर्ण अवरोध;
		हाल BINDER_WORK_DEAD_BINDER:
		हाल BINDER_WORK_DEAD_BINDER_AND_CLEAR:
		हाल BINDER_WORK_CLEAR_DEATH_NOTIFICATION: अणु
			काष्ठा binder_ref_death *death;
			uपूर्णांक32_t cmd;
			binder_uपूर्णांकptr_t cookie;

			death = container_of(w, काष्ठा binder_ref_death, work);
			अगर (w->type == BINDER_WORK_CLEAR_DEATH_NOTIFICATION)
				cmd = BR_CLEAR_DEATH_NOTIFICATION_DONE;
			अन्यथा
				cmd = BR_DEAD_BINDER;
			cookie = death->cookie;

			binder_debug(BINDER_DEBUG_DEATH_NOTIFICATION,
				     "%d:%d %s %016llx\n",
				      proc->pid, thपढ़ो->pid,
				      cmd == BR_DEAD_BINDER ?
				      "BR_DEAD_BINDER" :
				      "BR_CLEAR_DEATH_NOTIFICATION_DONE",
				      (u64)cookie);
			अगर (w->type == BINDER_WORK_CLEAR_DEATH_NOTIFICATION) अणु
				binder_inner_proc_unlock(proc);
				kमुक्त(death);
				binder_stats_deleted(BINDER_STAT_DEATH);
			पूर्ण अन्यथा अणु
				binder_enqueue_work_ilocked(
						w, &proc->delivered_death);
				binder_inner_proc_unlock(proc);
			पूर्ण
			अगर (put_user(cmd, (uपूर्णांक32_t __user *)ptr))
				वापस -EFAULT;
			ptr += माप(uपूर्णांक32_t);
			अगर (put_user(cookie,
				     (binder_uपूर्णांकptr_t __user *)ptr))
				वापस -EFAULT;
			ptr += माप(binder_uपूर्णांकptr_t);
			binder_stat_br(proc, thपढ़ो, cmd);
			अगर (cmd == BR_DEAD_BINDER)
				जाओ करोne; /* DEAD_BINDER notअगरications can cause transactions */
		पूर्ण अवरोध;
		शेष:
			binder_inner_proc_unlock(proc);
			pr_err("%d:%d: bad work type %d\n",
			       proc->pid, thपढ़ो->pid, w->type);
			अवरोध;
		पूर्ण

		अगर (!t)
			जारी;

		BUG_ON(t->buffer == शून्य);
		अगर (t->buffer->target_node) अणु
			काष्ठा binder_node *target_node = t->buffer->target_node;

			trd->target.ptr = target_node->ptr;
			trd->cookie =  target_node->cookie;
			t->saved_priority = task_nice(current);
			अगर (t->priority < target_node->min_priority &&
			    !(t->flags & TF_ONE_WAY))
				binder_set_nice(t->priority);
			अन्यथा अगर (!(t->flags & TF_ONE_WAY) ||
				 t->saved_priority > target_node->min_priority)
				binder_set_nice(target_node->min_priority);
			cmd = BR_TRANSACTION;
		पूर्ण अन्यथा अणु
			trd->target.ptr = 0;
			trd->cookie = 0;
			cmd = BR_REPLY;
		पूर्ण
		trd->code = t->code;
		trd->flags = t->flags;
		trd->sender_euid = from_kuid(current_user_ns(), t->sender_euid);

		t_from = binder_get_txn_from(t);
		अगर (t_from) अणु
			काष्ठा task_काष्ठा *sender = t_from->proc->tsk;

			trd->sender_pid =
				task_tgid_nr_ns(sender,
						task_active_pid_ns(current));
		पूर्ण अन्यथा अणु
			trd->sender_pid = 0;
		पूर्ण

		ret = binder_apply_fd_fixups(proc, t);
		अगर (ret) अणु
			काष्ठा binder_buffer *buffer = t->buffer;
			bool oneway = !!(t->flags & TF_ONE_WAY);
			पूर्णांक tid = t->debug_id;

			अगर (t_from)
				binder_thपढ़ो_dec_पंचांगpref(t_from);
			buffer->transaction = शून्य;
			binder_cleanup_transaction(t, "fd fixups failed",
						   BR_FAILED_REPLY);
			binder_मुक्त_buf(proc, buffer);
			binder_debug(BINDER_DEBUG_FAILED_TRANSACTION,
				     "%d:%d %stransaction %d fd fixups failed %d/%d, line %d\n",
				     proc->pid, thपढ़ो->pid,
				     oneway ? "async " :
					(cmd == BR_REPLY ? "reply " : ""),
				     tid, BR_FAILED_REPLY, ret, __LINE__);
			अगर (cmd == BR_REPLY) अणु
				cmd = BR_FAILED_REPLY;
				अगर (put_user(cmd, (uपूर्णांक32_t __user *)ptr))
					वापस -EFAULT;
				ptr += माप(uपूर्णांक32_t);
				binder_stat_br(proc, thपढ़ो, cmd);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण
		trd->data_size = t->buffer->data_size;
		trd->offsets_size = t->buffer->offsets_size;
		trd->data.ptr.buffer = (uपूर्णांकptr_t)t->buffer->user_data;
		trd->data.ptr.offsets = trd->data.ptr.buffer +
					ALIGN(t->buffer->data_size,
					    माप(व्योम *));

		tr.secctx = t->security_ctx;
		अगर (t->security_ctx) अणु
			cmd = BR_TRANSACTION_SEC_CTX;
			trsize = माप(tr);
		पूर्ण
		अगर (put_user(cmd, (uपूर्णांक32_t __user *)ptr)) अणु
			अगर (t_from)
				binder_thपढ़ो_dec_पंचांगpref(t_from);

			binder_cleanup_transaction(t, "put_user failed",
						   BR_FAILED_REPLY);

			वापस -EFAULT;
		पूर्ण
		ptr += माप(uपूर्णांक32_t);
		अगर (copy_to_user(ptr, &tr, trsize)) अणु
			अगर (t_from)
				binder_thपढ़ो_dec_पंचांगpref(t_from);

			binder_cleanup_transaction(t, "copy_to_user failed",
						   BR_FAILED_REPLY);

			वापस -EFAULT;
		पूर्ण
		ptr += trsize;

		trace_binder_transaction_received(t);
		binder_stat_br(proc, thपढ़ो, cmd);
		binder_debug(BINDER_DEBUG_TRANSACTION,
			     "%d:%d %s %d %d:%d, cmd %d size %zd-%zd ptr %016llx-%016llx\n",
			     proc->pid, thपढ़ो->pid,
			     (cmd == BR_TRANSACTION) ? "BR_TRANSACTION" :
				(cmd == BR_TRANSACTION_SEC_CTX) ?
				     "BR_TRANSACTION_SEC_CTX" : "BR_REPLY",
			     t->debug_id, t_from ? t_from->proc->pid : 0,
			     t_from ? t_from->pid : 0, cmd,
			     t->buffer->data_size, t->buffer->offsets_size,
			     (u64)trd->data.ptr.buffer,
			     (u64)trd->data.ptr.offsets);

		अगर (t_from)
			binder_thपढ़ो_dec_पंचांगpref(t_from);
		t->buffer->allow_user_मुक्त = 1;
		अगर (cmd != BR_REPLY && !(t->flags & TF_ONE_WAY)) अणु
			binder_inner_proc_lock(thपढ़ो->proc);
			t->to_parent = thपढ़ो->transaction_stack;
			t->to_thपढ़ो = thपढ़ो;
			thपढ़ो->transaction_stack = t;
			binder_inner_proc_unlock(thपढ़ो->proc);
		पूर्ण अन्यथा अणु
			binder_मुक्त_transaction(t);
		पूर्ण
		अवरोध;
	पूर्ण

करोne:

	*consumed = ptr - buffer;
	binder_inner_proc_lock(proc);
	अगर (proc->requested_thपढ़ोs == 0 &&
	    list_empty(&thपढ़ो->proc->रुकोing_thपढ़ोs) &&
	    proc->requested_thपढ़ोs_started < proc->max_thपढ़ोs &&
	    (thपढ़ो->looper & (BINDER_LOOPER_STATE_REGISTERED |
	     BINDER_LOOPER_STATE_ENTERED)) /* the user-space code fails to */
	     /*spawn a new thपढ़ो अगर we leave this out */) अणु
		proc->requested_thपढ़ोs++;
		binder_inner_proc_unlock(proc);
		binder_debug(BINDER_DEBUG_THREADS,
			     "%d:%d BR_SPAWN_LOOPER\n",
			     proc->pid, thपढ़ो->pid);
		अगर (put_user(BR_SPAWN_LOOPER, (uपूर्णांक32_t __user *)buffer))
			वापस -EFAULT;
		binder_stat_br(proc, thपढ़ो, BR_SPAWN_LOOPER);
	पूर्ण अन्यथा
		binder_inner_proc_unlock(proc);
	वापस 0;
पूर्ण

अटल व्योम binder_release_work(काष्ठा binder_proc *proc,
				काष्ठा list_head *list)
अणु
	काष्ठा binder_work *w;
	क्रमागत binder_work_type wtype;

	जबतक (1) अणु
		binder_inner_proc_lock(proc);
		w = binder_dequeue_work_head_ilocked(list);
		wtype = w ? w->type : 0;
		binder_inner_proc_unlock(proc);
		अगर (!w)
			वापस;

		चयन (wtype) अणु
		हाल BINDER_WORK_TRANSACTION: अणु
			काष्ठा binder_transaction *t;

			t = container_of(w, काष्ठा binder_transaction, work);

			binder_cleanup_transaction(t, "process died.",
						   BR_DEAD_REPLY);
		पूर्ण अवरोध;
		हाल BINDER_WORK_RETURN_ERROR: अणु
			काष्ठा binder_error *e = container_of(
					w, काष्ठा binder_error, work);

			binder_debug(BINDER_DEBUG_DEAD_TRANSACTION,
				"undelivered TRANSACTION_ERROR: %u\n",
				e->cmd);
		पूर्ण अवरोध;
		हाल BINDER_WORK_TRANSACTION_COMPLETE: अणु
			binder_debug(BINDER_DEBUG_DEAD_TRANSACTION,
				"undelivered TRANSACTION_COMPLETE\n");
			kमुक्त(w);
			binder_stats_deleted(BINDER_STAT_TRANSACTION_COMPLETE);
		पूर्ण अवरोध;
		हाल BINDER_WORK_DEAD_BINDER_AND_CLEAR:
		हाल BINDER_WORK_CLEAR_DEATH_NOTIFICATION: अणु
			काष्ठा binder_ref_death *death;

			death = container_of(w, काष्ठा binder_ref_death, work);
			binder_debug(BINDER_DEBUG_DEAD_TRANSACTION,
				"undelivered death notification, %016llx\n",
				(u64)death->cookie);
			kमुक्त(death);
			binder_stats_deleted(BINDER_STAT_DEATH);
		पूर्ण अवरोध;
		हाल BINDER_WORK_NODE:
			अवरोध;
		शेष:
			pr_err("unexpected work type, %d, not freed\n",
			       wtype);
			अवरोध;
		पूर्ण
	पूर्ण

पूर्ण

अटल काष्ठा binder_thपढ़ो *binder_get_thपढ़ो_ilocked(
		काष्ठा binder_proc *proc, काष्ठा binder_thपढ़ो *new_thपढ़ो)
अणु
	काष्ठा binder_thपढ़ो *thपढ़ो = शून्य;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rb_node **p = &proc->thपढ़ोs.rb_node;

	जबतक (*p) अणु
		parent = *p;
		thपढ़ो = rb_entry(parent, काष्ठा binder_thपढ़ो, rb_node);

		अगर (current->pid < thपढ़ो->pid)
			p = &(*p)->rb_left;
		अन्यथा अगर (current->pid > thपढ़ो->pid)
			p = &(*p)->rb_right;
		अन्यथा
			वापस thपढ़ो;
	पूर्ण
	अगर (!new_thपढ़ो)
		वापस शून्य;
	thपढ़ो = new_thपढ़ो;
	binder_stats_created(BINDER_STAT_THREAD);
	thपढ़ो->proc = proc;
	thपढ़ो->pid = current->pid;
	atomic_set(&thपढ़ो->पंचांगp_ref, 0);
	init_रुकोqueue_head(&thपढ़ो->रुको);
	INIT_LIST_HEAD(&thपढ़ो->toकरो);
	rb_link_node(&thपढ़ो->rb_node, parent, p);
	rb_insert_color(&thपढ़ो->rb_node, &proc->thपढ़ोs);
	thपढ़ो->looper_need_वापस = true;
	thपढ़ो->वापस_error.work.type = BINDER_WORK_RETURN_ERROR;
	thपढ़ो->वापस_error.cmd = BR_OK;
	thपढ़ो->reply_error.work.type = BINDER_WORK_RETURN_ERROR;
	thपढ़ो->reply_error.cmd = BR_OK;
	INIT_LIST_HEAD(&new_thपढ़ो->रुकोing_thपढ़ो_node);
	वापस thपढ़ो;
पूर्ण

अटल काष्ठा binder_thपढ़ो *binder_get_thपढ़ो(काष्ठा binder_proc *proc)
अणु
	काष्ठा binder_thपढ़ो *thपढ़ो;
	काष्ठा binder_thपढ़ो *new_thपढ़ो;

	binder_inner_proc_lock(proc);
	thपढ़ो = binder_get_thपढ़ो_ilocked(proc, शून्य);
	binder_inner_proc_unlock(proc);
	अगर (!thपढ़ो) अणु
		new_thपढ़ो = kzalloc(माप(*thपढ़ो), GFP_KERNEL);
		अगर (new_thपढ़ो == शून्य)
			वापस शून्य;
		binder_inner_proc_lock(proc);
		thपढ़ो = binder_get_thपढ़ो_ilocked(proc, new_thपढ़ो);
		binder_inner_proc_unlock(proc);
		अगर (thपढ़ो != new_thपढ़ो)
			kमुक्त(new_thपढ़ो);
	पूर्ण
	वापस thपढ़ो;
पूर्ण

अटल व्योम binder_मुक्त_proc(काष्ठा binder_proc *proc)
अणु
	काष्ठा binder_device *device;

	BUG_ON(!list_empty(&proc->toकरो));
	BUG_ON(!list_empty(&proc->delivered_death));
	अगर (proc->outstanding_txns)
		pr_warn("%s: Unexpected outstanding_txns %d\n",
			__func__, proc->outstanding_txns);
	device = container_of(proc->context, काष्ठा binder_device, context);
	अगर (refcount_dec_and_test(&device->ref)) अणु
		kमुक्त(proc->context->name);
		kमुक्त(device);
	पूर्ण
	binder_alloc_deferred_release(&proc->alloc);
	put_task_काष्ठा(proc->tsk);
	binder_stats_deleted(BINDER_STAT_PROC);
	kमुक्त(proc);
पूर्ण

अटल व्योम binder_मुक्त_thपढ़ो(काष्ठा binder_thपढ़ो *thपढ़ो)
अणु
	BUG_ON(!list_empty(&thपढ़ो->toकरो));
	binder_stats_deleted(BINDER_STAT_THREAD);
	binder_proc_dec_पंचांगpref(thपढ़ो->proc);
	kमुक्त(thपढ़ो);
पूर्ण

अटल पूर्णांक binder_thपढ़ो_release(काष्ठा binder_proc *proc,
				 काष्ठा binder_thपढ़ो *thपढ़ो)
अणु
	काष्ठा binder_transaction *t;
	काष्ठा binder_transaction *send_reply = शून्य;
	पूर्णांक active_transactions = 0;
	काष्ठा binder_transaction *last_t = शून्य;

	binder_inner_proc_lock(thपढ़ो->proc);
	/*
	 * take a ref on the proc so it survives
	 * after we हटाओ this thपढ़ो from proc->thपढ़ोs.
	 * The corresponding dec is when we actually
	 * मुक्त the thपढ़ो in binder_मुक्त_thपढ़ो()
	 */
	proc->पंचांगp_ref++;
	/*
	 * take a ref on this thपढ़ो to ensure it
	 * survives जबतक we are releasing it
	 */
	atomic_inc(&thपढ़ो->पंचांगp_ref);
	rb_erase(&thपढ़ो->rb_node, &proc->thपढ़ोs);
	t = thपढ़ो->transaction_stack;
	अगर (t) अणु
		spin_lock(&t->lock);
		अगर (t->to_thपढ़ो == thपढ़ो)
			send_reply = t;
	पूर्ण अन्यथा अणु
		__acquire(&t->lock);
	पूर्ण
	thपढ़ो->is_dead = true;

	जबतक (t) अणु
		last_t = t;
		active_transactions++;
		binder_debug(BINDER_DEBUG_DEAD_TRANSACTION,
			     "release %d:%d transaction %d %s, still active\n",
			      proc->pid, thपढ़ो->pid,
			     t->debug_id,
			     (t->to_thपढ़ो == thपढ़ो) ? "in" : "out");

		अगर (t->to_thपढ़ो == thपढ़ो) अणु
			thपढ़ो->proc->outstanding_txns--;
			t->to_proc = शून्य;
			t->to_thपढ़ो = शून्य;
			अगर (t->buffer) अणु
				t->buffer->transaction = शून्य;
				t->buffer = शून्य;
			पूर्ण
			t = t->to_parent;
		पूर्ण अन्यथा अगर (t->from == thपढ़ो) अणु
			t->from = शून्य;
			t = t->from_parent;
		पूर्ण अन्यथा
			BUG();
		spin_unlock(&last_t->lock);
		अगर (t)
			spin_lock(&t->lock);
		अन्यथा
			__acquire(&t->lock);
	पूर्ण
	/* annotation क्रम sparse, lock not acquired in last iteration above */
	__release(&t->lock);

	/*
	 * If this thपढ़ो used poll, make sure we हटाओ the रुकोqueue
	 * from any epoll data काष्ठाures holding it with POLLFREE.
	 * रुकोqueue_active() is safe to use here because we're holding
	 * the inner lock.
	 */
	अगर ((thपढ़ो->looper & BINDER_LOOPER_STATE_POLL) &&
	    रुकोqueue_active(&thपढ़ो->रुको)) अणु
		wake_up_poll(&thपढ़ो->रुको, EPOLLHUP | POLLFREE);
	पूर्ण

	binder_inner_proc_unlock(thपढ़ो->proc);

	/*
	 * This is needed to aव्योम races between wake_up_poll() above and
	 * and ep_हटाओ_रुकोqueue() called क्रम other reasons (eg the epoll file
	 * descriptor being बंदd); ep_हटाओ_रुकोqueue() holds an RCU पढ़ो
	 * lock, so we can be sure it's करोne after calling synchronize_rcu().
	 */
	अगर (thपढ़ो->looper & BINDER_LOOPER_STATE_POLL)
		synchronize_rcu();

	अगर (send_reply)
		binder_send_failed_reply(send_reply, BR_DEAD_REPLY);
	binder_release_work(proc, &thपढ़ो->toकरो);
	binder_thपढ़ो_dec_पंचांगpref(thपढ़ो);
	वापस active_transactions;
पूर्ण

अटल __poll_t binder_poll(काष्ठा file *filp,
				काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा binder_proc *proc = filp->निजी_data;
	काष्ठा binder_thपढ़ो *thपढ़ो = शून्य;
	bool रुको_क्रम_proc_work;

	thपढ़ो = binder_get_thपढ़ो(proc);
	अगर (!thपढ़ो)
		वापस POLLERR;

	binder_inner_proc_lock(thपढ़ो->proc);
	thपढ़ो->looper |= BINDER_LOOPER_STATE_POLL;
	रुको_क्रम_proc_work = binder_available_क्रम_proc_work_ilocked(thपढ़ो);

	binder_inner_proc_unlock(thपढ़ो->proc);

	poll_रुको(filp, &thपढ़ो->रुको, रुको);

	अगर (binder_has_work(thपढ़ो, रुको_क्रम_proc_work))
		वापस EPOLLIN;

	वापस 0;
पूर्ण

अटल पूर्णांक binder_ioctl_ग_लिखो_पढ़ो(काष्ठा file *filp,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
				काष्ठा binder_thपढ़ो *thपढ़ो)
अणु
	पूर्णांक ret = 0;
	काष्ठा binder_proc *proc = filp->निजी_data;
	अचिन्हित पूर्णांक size = _IOC_SIZE(cmd);
	व्योम __user *ubuf = (व्योम __user *)arg;
	काष्ठा binder_ग_लिखो_पढ़ो bwr;

	अगर (size != माप(काष्ठा binder_ग_लिखो_पढ़ो)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (copy_from_user(&bwr, ubuf, माप(bwr))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	binder_debug(BINDER_DEBUG_READ_WRITE,
		     "%d:%d write %lld at %016llx, read %lld at %016llx\n",
		     proc->pid, thपढ़ो->pid,
		     (u64)bwr.ग_लिखो_size, (u64)bwr.ग_लिखो_buffer,
		     (u64)bwr.पढ़ो_size, (u64)bwr.पढ़ो_buffer);

	अगर (bwr.ग_लिखो_size > 0) अणु
		ret = binder_thपढ़ो_ग_लिखो(proc, thपढ़ो,
					  bwr.ग_लिखो_buffer,
					  bwr.ग_लिखो_size,
					  &bwr.ग_लिखो_consumed);
		trace_binder_ग_लिखो_करोne(ret);
		अगर (ret < 0) अणु
			bwr.पढ़ो_consumed = 0;
			अगर (copy_to_user(ubuf, &bwr, माप(bwr)))
				ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (bwr.पढ़ो_size > 0) अणु
		ret = binder_thपढ़ो_पढ़ो(proc, thपढ़ो, bwr.पढ़ो_buffer,
					 bwr.पढ़ो_size,
					 &bwr.पढ़ो_consumed,
					 filp->f_flags & O_NONBLOCK);
		trace_binder_पढ़ो_करोne(ret);
		binder_inner_proc_lock(proc);
		अगर (!binder_worklist_empty_ilocked(&proc->toकरो))
			binder_wakeup_proc_ilocked(proc);
		binder_inner_proc_unlock(proc);
		अगर (ret < 0) अणु
			अगर (copy_to_user(ubuf, &bwr, माप(bwr)))
				ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
	binder_debug(BINDER_DEBUG_READ_WRITE,
		     "%d:%d wrote %lld of %lld, read return %lld of %lld\n",
		     proc->pid, thपढ़ो->pid,
		     (u64)bwr.ग_लिखो_consumed, (u64)bwr.ग_लिखो_size,
		     (u64)bwr.पढ़ो_consumed, (u64)bwr.पढ़ो_size);
	अगर (copy_to_user(ubuf, &bwr, माप(bwr))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक binder_ioctl_set_ctx_mgr(काष्ठा file *filp,
				    काष्ठा flat_binder_object *fbo)
अणु
	पूर्णांक ret = 0;
	काष्ठा binder_proc *proc = filp->निजी_data;
	काष्ठा binder_context *context = proc->context;
	काष्ठा binder_node *new_node;
	kuid_t curr_euid = current_euid();

	mutex_lock(&context->context_mgr_node_lock);
	अगर (context->binder_context_mgr_node) अणु
		pr_err("BINDER_SET_CONTEXT_MGR already set\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	ret = security_binder_set_context_mgr(proc->tsk);
	अगर (ret < 0)
		जाओ out;
	अगर (uid_valid(context->binder_context_mgr_uid)) अणु
		अगर (!uid_eq(context->binder_context_mgr_uid, curr_euid)) अणु
			pr_err("BINDER_SET_CONTEXT_MGR bad uid %d != %d\n",
			       from_kuid(&init_user_ns, curr_euid),
			       from_kuid(&init_user_ns,
					 context->binder_context_mgr_uid));
			ret = -EPERM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		context->binder_context_mgr_uid = curr_euid;
	पूर्ण
	new_node = binder_new_node(proc, fbo);
	अगर (!new_node) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	binder_node_lock(new_node);
	new_node->local_weak_refs++;
	new_node->local_strong_refs++;
	new_node->has_strong_ref = 1;
	new_node->has_weak_ref = 1;
	context->binder_context_mgr_node = new_node;
	binder_node_unlock(new_node);
	binder_put_node(new_node);
out:
	mutex_unlock(&context->context_mgr_node_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक binder_ioctl_get_node_info_क्रम_ref(काष्ठा binder_proc *proc,
		काष्ठा binder_node_info_क्रम_ref *info)
अणु
	काष्ठा binder_node *node;
	काष्ठा binder_context *context = proc->context;
	__u32 handle = info->handle;

	अगर (info->strong_count || info->weak_count || info->reserved1 ||
	    info->reserved2 || info->reserved3) अणु
		binder_user_error("%d BINDER_GET_NODE_INFO_FOR_REF: only handle may be non-zero.",
				  proc->pid);
		वापस -EINVAL;
	पूर्ण

	/* This ioctl may only be used by the context manager */
	mutex_lock(&context->context_mgr_node_lock);
	अगर (!context->binder_context_mgr_node ||
		context->binder_context_mgr_node->proc != proc) अणु
		mutex_unlock(&context->context_mgr_node_lock);
		वापस -EPERM;
	पूर्ण
	mutex_unlock(&context->context_mgr_node_lock);

	node = binder_get_node_from_ref(proc, handle, true, शून्य);
	अगर (!node)
		वापस -EINVAL;

	info->strong_count = node->local_strong_refs +
		node->पूर्णांकernal_strong_refs;
	info->weak_count = node->local_weak_refs;

	binder_put_node(node);

	वापस 0;
पूर्ण

अटल पूर्णांक binder_ioctl_get_node_debug_info(काष्ठा binder_proc *proc,
				काष्ठा binder_node_debug_info *info)
अणु
	काष्ठा rb_node *n;
	binder_uपूर्णांकptr_t ptr = info->ptr;

	स_रखो(info, 0, माप(*info));

	binder_inner_proc_lock(proc);
	क्रम (n = rb_first(&proc->nodes); n != शून्य; n = rb_next(n)) अणु
		काष्ठा binder_node *node = rb_entry(n, काष्ठा binder_node,
						    rb_node);
		अगर (node->ptr > ptr) अणु
			info->ptr = node->ptr;
			info->cookie = node->cookie;
			info->has_strong_ref = node->has_strong_ref;
			info->has_weak_ref = node->has_weak_ref;
			अवरोध;
		पूर्ण
	पूर्ण
	binder_inner_proc_unlock(proc);

	वापस 0;
पूर्ण

अटल पूर्णांक binder_ioctl_मुक्तze(काष्ठा binder_मुक्तze_info *info,
			       काष्ठा binder_proc *target_proc)
अणु
	पूर्णांक ret = 0;

	अगर (!info->enable) अणु
		binder_inner_proc_lock(target_proc);
		target_proc->sync_recv = false;
		target_proc->async_recv = false;
		target_proc->is_frozen = false;
		binder_inner_proc_unlock(target_proc);
		वापस 0;
	पूर्ण

	/*
	 * Freezing the target. Prevent new transactions by
	 * setting frozen state. If समयout specअगरied, रुको
	 * क्रम transactions to drain.
	 */
	binder_inner_proc_lock(target_proc);
	target_proc->sync_recv = false;
	target_proc->async_recv = false;
	target_proc->is_frozen = true;
	binder_inner_proc_unlock(target_proc);

	अगर (info->समयout_ms > 0)
		ret = रुको_event_पूर्णांकerruptible_समयout(
			target_proc->मुक्तze_रुको,
			(!target_proc->outstanding_txns),
			msecs_to_jअगरfies(info->समयout_ms));

	अगर (!ret && target_proc->outstanding_txns)
		ret = -EAGAIN;

	अगर (ret < 0) अणु
		binder_inner_proc_lock(target_proc);
		target_proc->is_frozen = false;
		binder_inner_proc_unlock(target_proc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक binder_ioctl_get_मुक्तzer_info(
				काष्ठा binder_frozen_status_info *info)
अणु
	काष्ठा binder_proc *target_proc;
	bool found = false;

	info->sync_recv = 0;
	info->async_recv = 0;

	mutex_lock(&binder_procs_lock);
	hlist_क्रम_each_entry(target_proc, &binder_procs, proc_node) अणु
		अगर (target_proc->pid == info->pid) अणु
			found = true;
			binder_inner_proc_lock(target_proc);
			info->sync_recv |= target_proc->sync_recv;
			info->async_recv |= target_proc->async_recv;
			binder_inner_proc_unlock(target_proc);
		पूर्ण
	पूर्ण
	mutex_unlock(&binder_procs_lock);

	अगर (!found)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल दीर्घ binder_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा binder_proc *proc = filp->निजी_data;
	काष्ठा binder_thपढ़ो *thपढ़ो;
	अचिन्हित पूर्णांक size = _IOC_SIZE(cmd);
	व्योम __user *ubuf = (व्योम __user *)arg;

	/*pr_info("binder_ioctl: %d:%d %x %lx\n",
			proc->pid, current->pid, cmd, arg);*/

	binder_selftest_alloc(&proc->alloc);

	trace_binder_ioctl(cmd, arg);

	ret = रुको_event_पूर्णांकerruptible(binder_user_error_रुको, binder_stop_on_user_error < 2);
	अगर (ret)
		जाओ err_unlocked;

	thपढ़ो = binder_get_thपढ़ो(proc);
	अगर (thपढ़ो == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	चयन (cmd) अणु
	हाल BINDER_WRITE_READ:
		ret = binder_ioctl_ग_लिखो_पढ़ो(filp, cmd, arg, thपढ़ो);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल BINDER_SET_MAX_THREADS: अणु
		पूर्णांक max_thपढ़ोs;

		अगर (copy_from_user(&max_thपढ़ोs, ubuf,
				   माप(max_thपढ़ोs))) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		binder_inner_proc_lock(proc);
		proc->max_thपढ़ोs = max_thपढ़ोs;
		binder_inner_proc_unlock(proc);
		अवरोध;
	पूर्ण
	हाल BINDER_SET_CONTEXT_MGR_EXT: अणु
		काष्ठा flat_binder_object fbo;

		अगर (copy_from_user(&fbo, ubuf, माप(fbo))) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		ret = binder_ioctl_set_ctx_mgr(filp, &fbo);
		अगर (ret)
			जाओ err;
		अवरोध;
	पूर्ण
	हाल BINDER_SET_CONTEXT_MGR:
		ret = binder_ioctl_set_ctx_mgr(filp, शून्य);
		अगर (ret)
			जाओ err;
		अवरोध;
	हाल BINDER_THREAD_EXIT:
		binder_debug(BINDER_DEBUG_THREADS, "%d:%d exit\n",
			     proc->pid, thपढ़ो->pid);
		binder_thपढ़ो_release(proc, thपढ़ो);
		thपढ़ो = शून्य;
		अवरोध;
	हाल BINDER_VERSION: अणु
		काष्ठा binder_version __user *ver = ubuf;

		अगर (size != माप(काष्ठा binder_version)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अगर (put_user(BINDER_CURRENT_PROTOCOL_VERSION,
			     &ver->protocol_version)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BINDER_GET_NODE_INFO_FOR_REF: अणु
		काष्ठा binder_node_info_क्रम_ref info;

		अगर (copy_from_user(&info, ubuf, माप(info))) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		ret = binder_ioctl_get_node_info_क्रम_ref(proc, &info);
		अगर (ret < 0)
			जाओ err;

		अगर (copy_to_user(ubuf, &info, माप(info))) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		अवरोध;
	पूर्ण
	हाल BINDER_GET_NODE_DEBUG_INFO: अणु
		काष्ठा binder_node_debug_info info;

		अगर (copy_from_user(&info, ubuf, माप(info))) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		ret = binder_ioctl_get_node_debug_info(proc, &info);
		अगर (ret < 0)
			जाओ err;

		अगर (copy_to_user(ubuf, &info, माप(info))) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BINDER_FREEZE: अणु
		काष्ठा binder_मुक्तze_info info;
		काष्ठा binder_proc **target_procs = शून्य, *target_proc;
		पूर्णांक target_procs_count = 0, i = 0;

		ret = 0;

		अगर (copy_from_user(&info, ubuf, माप(info))) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		mutex_lock(&binder_procs_lock);
		hlist_क्रम_each_entry(target_proc, &binder_procs, proc_node) अणु
			अगर (target_proc->pid == info.pid)
				target_procs_count++;
		पूर्ण

		अगर (target_procs_count == 0) अणु
			mutex_unlock(&binder_procs_lock);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		target_procs = kसुस्मृति(target_procs_count,
				       माप(काष्ठा binder_proc *),
				       GFP_KERNEL);

		अगर (!target_procs) अणु
			mutex_unlock(&binder_procs_lock);
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		hlist_क्रम_each_entry(target_proc, &binder_procs, proc_node) अणु
			अगर (target_proc->pid != info.pid)
				जारी;

			binder_inner_proc_lock(target_proc);
			target_proc->पंचांगp_ref++;
			binder_inner_proc_unlock(target_proc);

			target_procs[i++] = target_proc;
		पूर्ण
		mutex_unlock(&binder_procs_lock);

		क्रम (i = 0; i < target_procs_count; i++) अणु
			अगर (ret >= 0)
				ret = binder_ioctl_मुक्तze(&info,
							  target_procs[i]);

			binder_proc_dec_पंचांगpref(target_procs[i]);
		पूर्ण

		kमुक्त(target_procs);

		अगर (ret < 0)
			जाओ err;
		अवरोध;
	पूर्ण
	हाल BINDER_GET_FROZEN_INFO: अणु
		काष्ठा binder_frozen_status_info info;

		अगर (copy_from_user(&info, ubuf, माप(info))) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण

		ret = binder_ioctl_get_मुक्तzer_info(&info);
		अगर (ret < 0)
			जाओ err;

		अगर (copy_to_user(ubuf, &info, माप(info))) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BINDER_ENABLE_ONEWAY_SPAM_DETECTION: अणु
		uपूर्णांक32_t enable;

		अगर (copy_from_user(&enable, ubuf, माप(enable))) अणु
			ret = -EFAULT;
			जाओ err;
		पूर्ण
		binder_inner_proc_lock(proc);
		proc->oneway_spam_detection_enabled = (bool)enable;
		binder_inner_proc_unlock(proc);
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	ret = 0;
err:
	अगर (thपढ़ो)
		thपढ़ो->looper_need_वापस = false;
	रुको_event_पूर्णांकerruptible(binder_user_error_रुको, binder_stop_on_user_error < 2);
	अगर (ret && ret != -EINTR)
		pr_info("%d:%d ioctl %x %lx returned %d\n", proc->pid, current->pid, cmd, arg, ret);
err_unlocked:
	trace_binder_ioctl_करोne(ret);
	वापस ret;
पूर्ण

अटल व्योम binder_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा binder_proc *proc = vma->vm_निजी_data;

	binder_debug(BINDER_DEBUG_OPEN_CLOSE,
		     "%d open vm area %lx-%lx (%ld K) vma %lx pagep %lx\n",
		     proc->pid, vma->vm_start, vma->vm_end,
		     (vma->vm_end - vma->vm_start) / SZ_1K, vma->vm_flags,
		     (अचिन्हित दीर्घ)pgprot_val(vma->vm_page_prot));
पूर्ण

अटल व्योम binder_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा binder_proc *proc = vma->vm_निजी_data;

	binder_debug(BINDER_DEBUG_OPEN_CLOSE,
		     "%d close vm area %lx-%lx (%ld K) vma %lx pagep %lx\n",
		     proc->pid, vma->vm_start, vma->vm_end,
		     (vma->vm_end - vma->vm_start) / SZ_1K, vma->vm_flags,
		     (अचिन्हित दीर्घ)pgprot_val(vma->vm_page_prot));
	binder_alloc_vma_बंद(&proc->alloc);
पूर्ण

अटल vm_fault_t binder_vm_fault(काष्ठा vm_fault *vmf)
अणु
	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा binder_vm_ops = अणु
	.खोलो = binder_vma_खोलो,
	.बंद = binder_vma_बंद,
	.fault = binder_vm_fault,
पूर्ण;

अटल पूर्णांक binder_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा binder_proc *proc = filp->निजी_data;

	अगर (proc->tsk != current->group_leader)
		वापस -EINVAL;

	binder_debug(BINDER_DEBUG_OPEN_CLOSE,
		     "%s: %d %lx-%lx (%ld K) vma %lx pagep %lx\n",
		     __func__, proc->pid, vma->vm_start, vma->vm_end,
		     (vma->vm_end - vma->vm_start) / SZ_1K, vma->vm_flags,
		     (अचिन्हित दीर्घ)pgprot_val(vma->vm_page_prot));

	अगर (vma->vm_flags & FORBIDDEN_MMAP_FLAGS) अणु
		pr_err("%s: %d %lx-%lx %s failed %d\n", __func__,
		       proc->pid, vma->vm_start, vma->vm_end, "bad vm_flags", -EPERM);
		वापस -EPERM;
	पूर्ण
	vma->vm_flags |= VM_DONTCOPY | VM_MIXEDMAP;
	vma->vm_flags &= ~VM_MAYWRITE;

	vma->vm_ops = &binder_vm_ops;
	vma->vm_निजी_data = proc;

	वापस binder_alloc_mmap_handler(&proc->alloc, vma);
पूर्ण

अटल पूर्णांक binder_खोलो(काष्ठा inode *nodp, काष्ठा file *filp)
अणु
	काष्ठा binder_proc *proc, *itr;
	काष्ठा binder_device *binder_dev;
	काष्ठा binderfs_info *info;
	काष्ठा dentry *binder_binderfs_dir_entry_proc = शून्य;
	bool existing_pid = false;

	binder_debug(BINDER_DEBUG_OPEN_CLOSE, "%s: %d:%d\n", __func__,
		     current->group_leader->pid, current->pid);

	proc = kzalloc(माप(*proc), GFP_KERNEL);
	अगर (proc == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&proc->inner_lock);
	spin_lock_init(&proc->outer_lock);
	get_task_काष्ठा(current->group_leader);
	proc->tsk = current->group_leader;
	INIT_LIST_HEAD(&proc->toकरो);
	init_रुकोqueue_head(&proc->मुक्तze_रुको);
	proc->शेष_priority = task_nice(current);
	/* binderfs stashes devices in i_निजी */
	अगर (is_binderfs_device(nodp)) अणु
		binder_dev = nodp->i_निजी;
		info = nodp->i_sb->s_fs_info;
		binder_binderfs_dir_entry_proc = info->proc_log_dir;
	पूर्ण अन्यथा अणु
		binder_dev = container_of(filp->निजी_data,
					  काष्ठा binder_device, miscdev);
	पूर्ण
	refcount_inc(&binder_dev->ref);
	proc->context = &binder_dev->context;
	binder_alloc_init(&proc->alloc);

	binder_stats_created(BINDER_STAT_PROC);
	proc->pid = current->group_leader->pid;
	INIT_LIST_HEAD(&proc->delivered_death);
	INIT_LIST_HEAD(&proc->रुकोing_thपढ़ोs);
	filp->निजी_data = proc;

	mutex_lock(&binder_procs_lock);
	hlist_क्रम_each_entry(itr, &binder_procs, proc_node) अणु
		अगर (itr->pid == proc->pid) अणु
			existing_pid = true;
			अवरोध;
		पूर्ण
	पूर्ण
	hlist_add_head(&proc->proc_node, &binder_procs);
	mutex_unlock(&binder_procs_lock);

	अगर (binder_debugfs_dir_entry_proc && !existing_pid) अणु
		अक्षर strbuf[11];

		snम_लिखो(strbuf, माप(strbuf), "%u", proc->pid);
		/*
		 * proc debug entries are shared between contexts.
		 * Only create क्रम the first PID to aव्योम debugfs log spamming
		 * The prपूर्णांकing code will anyway prपूर्णांक all contexts क्रम a given
		 * PID so this is not a problem.
		 */
		proc->debugfs_entry = debugfs_create_file(strbuf, 0444,
			binder_debugfs_dir_entry_proc,
			(व्योम *)(अचिन्हित दीर्घ)proc->pid,
			&proc_fops);
	पूर्ण

	अगर (binder_binderfs_dir_entry_proc && !existing_pid) अणु
		अक्षर strbuf[11];
		काष्ठा dentry *binderfs_entry;

		snम_लिखो(strbuf, माप(strbuf), "%u", proc->pid);
		/*
		 * Similar to debugfs, the process specअगरic log file is shared
		 * between contexts. Only create क्रम the first PID.
		 * This is ok since same as debugfs, the log file will contain
		 * inक्रमmation on all contexts of a given PID.
		 */
		binderfs_entry = binderfs_create_file(binder_binderfs_dir_entry_proc,
			strbuf, &proc_fops, (व्योम *)(अचिन्हित दीर्घ)proc->pid);
		अगर (!IS_ERR(binderfs_entry)) अणु
			proc->binderfs_entry = binderfs_entry;
		पूर्ण अन्यथा अणु
			पूर्णांक error;

			error = PTR_ERR(binderfs_entry);
			pr_warn("Unable to create file %s in binderfs (error %d)\n",
				strbuf, error);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक binder_flush(काष्ठा file *filp, fl_owner_t id)
अणु
	काष्ठा binder_proc *proc = filp->निजी_data;

	binder_defer_work(proc, BINDER_DEFERRED_FLUSH);

	वापस 0;
पूर्ण

अटल व्योम binder_deferred_flush(काष्ठा binder_proc *proc)
अणु
	काष्ठा rb_node *n;
	पूर्णांक wake_count = 0;

	binder_inner_proc_lock(proc);
	क्रम (n = rb_first(&proc->thपढ़ोs); n != शून्य; n = rb_next(n)) अणु
		काष्ठा binder_thपढ़ो *thपढ़ो = rb_entry(n, काष्ठा binder_thपढ़ो, rb_node);

		thपढ़ो->looper_need_वापस = true;
		अगर (thपढ़ो->looper & BINDER_LOOPER_STATE_WAITING) अणु
			wake_up_पूर्णांकerruptible(&thपढ़ो->रुको);
			wake_count++;
		पूर्ण
	पूर्ण
	binder_inner_proc_unlock(proc);

	binder_debug(BINDER_DEBUG_OPEN_CLOSE,
		     "binder_flush: %d woke %d threads\n", proc->pid,
		     wake_count);
पूर्ण

अटल पूर्णांक binder_release(काष्ठा inode *nodp, काष्ठा file *filp)
अणु
	काष्ठा binder_proc *proc = filp->निजी_data;

	debugfs_हटाओ(proc->debugfs_entry);

	अगर (proc->binderfs_entry) अणु
		binderfs_हटाओ_file(proc->binderfs_entry);
		proc->binderfs_entry = शून्य;
	पूर्ण

	binder_defer_work(proc, BINDER_DEFERRED_RELEASE);

	वापस 0;
पूर्ण

अटल पूर्णांक binder_node_release(काष्ठा binder_node *node, पूर्णांक refs)
अणु
	काष्ठा binder_ref *ref;
	पूर्णांक death = 0;
	काष्ठा binder_proc *proc = node->proc;

	binder_release_work(proc, &node->async_toकरो);

	binder_node_lock(node);
	binder_inner_proc_lock(proc);
	binder_dequeue_work_ilocked(&node->work);
	/*
	 * The caller must have taken a temporary ref on the node,
	 */
	BUG_ON(!node->पंचांगp_refs);
	अगर (hlist_empty(&node->refs) && node->पंचांगp_refs == 1) अणु
		binder_inner_proc_unlock(proc);
		binder_node_unlock(node);
		binder_मुक्त_node(node);

		वापस refs;
	पूर्ण

	node->proc = शून्य;
	node->local_strong_refs = 0;
	node->local_weak_refs = 0;
	binder_inner_proc_unlock(proc);

	spin_lock(&binder_dead_nodes_lock);
	hlist_add_head(&node->dead_node, &binder_dead_nodes);
	spin_unlock(&binder_dead_nodes_lock);

	hlist_क्रम_each_entry(ref, &node->refs, node_entry) अणु
		refs++;
		/*
		 * Need the node lock to synchronize
		 * with new notअगरication requests and the
		 * inner lock to synchronize with queued
		 * death notअगरications.
		 */
		binder_inner_proc_lock(ref->proc);
		अगर (!ref->death) अणु
			binder_inner_proc_unlock(ref->proc);
			जारी;
		पूर्ण

		death++;

		BUG_ON(!list_empty(&ref->death->work.entry));
		ref->death->work.type = BINDER_WORK_DEAD_BINDER;
		binder_enqueue_work_ilocked(&ref->death->work,
					    &ref->proc->toकरो);
		binder_wakeup_proc_ilocked(ref->proc);
		binder_inner_proc_unlock(ref->proc);
	पूर्ण

	binder_debug(BINDER_DEBUG_DEAD_BINDER,
		     "node %d now dead, refs %d, death %d\n",
		     node->debug_id, refs, death);
	binder_node_unlock(node);
	binder_put_node(node);

	वापस refs;
पूर्ण

अटल व्योम binder_deferred_release(काष्ठा binder_proc *proc)
अणु
	काष्ठा binder_context *context = proc->context;
	काष्ठा rb_node *n;
	पूर्णांक thपढ़ोs, nodes, incoming_refs, outgoing_refs, active_transactions;

	mutex_lock(&binder_procs_lock);
	hlist_del(&proc->proc_node);
	mutex_unlock(&binder_procs_lock);

	mutex_lock(&context->context_mgr_node_lock);
	अगर (context->binder_context_mgr_node &&
	    context->binder_context_mgr_node->proc == proc) अणु
		binder_debug(BINDER_DEBUG_DEAD_BINDER,
			     "%s: %d context_mgr_node gone\n",
			     __func__, proc->pid);
		context->binder_context_mgr_node = शून्य;
	पूर्ण
	mutex_unlock(&context->context_mgr_node_lock);
	binder_inner_proc_lock(proc);
	/*
	 * Make sure proc stays alive after we
	 * हटाओ all the thपढ़ोs
	 */
	proc->पंचांगp_ref++;

	proc->is_dead = true;
	proc->is_frozen = false;
	proc->sync_recv = false;
	proc->async_recv = false;
	thपढ़ोs = 0;
	active_transactions = 0;
	जबतक ((n = rb_first(&proc->thपढ़ोs))) अणु
		काष्ठा binder_thपढ़ो *thपढ़ो;

		thपढ़ो = rb_entry(n, काष्ठा binder_thपढ़ो, rb_node);
		binder_inner_proc_unlock(proc);
		thपढ़ोs++;
		active_transactions += binder_thपढ़ो_release(proc, thपढ़ो);
		binder_inner_proc_lock(proc);
	पूर्ण

	nodes = 0;
	incoming_refs = 0;
	जबतक ((n = rb_first(&proc->nodes))) अणु
		काष्ठा binder_node *node;

		node = rb_entry(n, काष्ठा binder_node, rb_node);
		nodes++;
		/*
		 * take a temporary ref on the node beक्रमe
		 * calling binder_node_release() which will either
		 * kमुक्त() the node or call binder_put_node()
		 */
		binder_inc_node_पंचांगpref_ilocked(node);
		rb_erase(&node->rb_node, &proc->nodes);
		binder_inner_proc_unlock(proc);
		incoming_refs = binder_node_release(node, incoming_refs);
		binder_inner_proc_lock(proc);
	पूर्ण
	binder_inner_proc_unlock(proc);

	outgoing_refs = 0;
	binder_proc_lock(proc);
	जबतक ((n = rb_first(&proc->refs_by_desc))) अणु
		काष्ठा binder_ref *ref;

		ref = rb_entry(n, काष्ठा binder_ref, rb_node_desc);
		outgoing_refs++;
		binder_cleanup_ref_olocked(ref);
		binder_proc_unlock(proc);
		binder_मुक्त_ref(ref);
		binder_proc_lock(proc);
	पूर्ण
	binder_proc_unlock(proc);

	binder_release_work(proc, &proc->toकरो);
	binder_release_work(proc, &proc->delivered_death);

	binder_debug(BINDER_DEBUG_OPEN_CLOSE,
		     "%s: %d threads %d, nodes %d (ref %d), refs %d, active transactions %d\n",
		     __func__, proc->pid, thपढ़ोs, nodes, incoming_refs,
		     outgoing_refs, active_transactions);

	binder_proc_dec_पंचांगpref(proc);
पूर्ण

अटल व्योम binder_deferred_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा binder_proc *proc;

	पूर्णांक defer;

	करो अणु
		mutex_lock(&binder_deferred_lock);
		अगर (!hlist_empty(&binder_deferred_list)) अणु
			proc = hlist_entry(binder_deferred_list.first,
					काष्ठा binder_proc, deferred_work_node);
			hlist_del_init(&proc->deferred_work_node);
			defer = proc->deferred_work;
			proc->deferred_work = 0;
		पूर्ण अन्यथा अणु
			proc = शून्य;
			defer = 0;
		पूर्ण
		mutex_unlock(&binder_deferred_lock);

		अगर (defer & BINDER_DEFERRED_FLUSH)
			binder_deferred_flush(proc);

		अगर (defer & BINDER_DEFERRED_RELEASE)
			binder_deferred_release(proc); /* मुक्तs proc */
	पूर्ण जबतक (proc);
पूर्ण
अटल DECLARE_WORK(binder_deferred_work, binder_deferred_func);

अटल व्योम
binder_defer_work(काष्ठा binder_proc *proc, क्रमागत binder_deferred_state defer)
अणु
	mutex_lock(&binder_deferred_lock);
	proc->deferred_work |= defer;
	अगर (hlist_unhashed(&proc->deferred_work_node)) अणु
		hlist_add_head(&proc->deferred_work_node,
				&binder_deferred_list);
		schedule_work(&binder_deferred_work);
	पूर्ण
	mutex_unlock(&binder_deferred_lock);
पूर्ण

अटल व्योम prपूर्णांक_binder_transaction_ilocked(काष्ठा seq_file *m,
					     काष्ठा binder_proc *proc,
					     स्थिर अक्षर *prefix,
					     काष्ठा binder_transaction *t)
अणु
	काष्ठा binder_proc *to_proc;
	काष्ठा binder_buffer *buffer = t->buffer;

	spin_lock(&t->lock);
	to_proc = t->to_proc;
	seq_म_लिखो(m,
		   "%s %d: %pK from %d:%d to %d:%d code %x flags %x pri %ld r%d",
		   prefix, t->debug_id, t,
		   t->from ? t->from->proc->pid : 0,
		   t->from ? t->from->pid : 0,
		   to_proc ? to_proc->pid : 0,
		   t->to_thपढ़ो ? t->to_thपढ़ो->pid : 0,
		   t->code, t->flags, t->priority, t->need_reply);
	spin_unlock(&t->lock);

	अगर (proc != to_proc) अणु
		/*
		 * Can only safely deref buffer अगर we are holding the
		 * correct proc inner lock क्रम this node
		 */
		seq_माला_दो(m, "\n");
		वापस;
	पूर्ण

	अगर (buffer == शून्य) अणु
		seq_माला_दो(m, " buffer free\n");
		वापस;
	पूर्ण
	अगर (buffer->target_node)
		seq_म_लिखो(m, " node %d", buffer->target_node->debug_id);
	seq_म_लिखो(m, " size %zd:%zd data %pK\n",
		   buffer->data_size, buffer->offsets_size,
		   buffer->user_data);
पूर्ण

अटल व्योम prपूर्णांक_binder_work_ilocked(काष्ठा seq_file *m,
				     काष्ठा binder_proc *proc,
				     स्थिर अक्षर *prefix,
				     स्थिर अक्षर *transaction_prefix,
				     काष्ठा binder_work *w)
अणु
	काष्ठा binder_node *node;
	काष्ठा binder_transaction *t;

	चयन (w->type) अणु
	हाल BINDER_WORK_TRANSACTION:
		t = container_of(w, काष्ठा binder_transaction, work);
		prपूर्णांक_binder_transaction_ilocked(
				m, proc, transaction_prefix, t);
		अवरोध;
	हाल BINDER_WORK_RETURN_ERROR: अणु
		काष्ठा binder_error *e = container_of(
				w, काष्ठा binder_error, work);

		seq_म_लिखो(m, "%stransaction error: %u\n",
			   prefix, e->cmd);
	पूर्ण अवरोध;
	हाल BINDER_WORK_TRANSACTION_COMPLETE:
		seq_म_लिखो(m, "%stransaction complete\n", prefix);
		अवरोध;
	हाल BINDER_WORK_NODE:
		node = container_of(w, काष्ठा binder_node, work);
		seq_म_लिखो(m, "%snode work %d: u%016llx c%016llx\n",
			   prefix, node->debug_id,
			   (u64)node->ptr, (u64)node->cookie);
		अवरोध;
	हाल BINDER_WORK_DEAD_BINDER:
		seq_म_लिखो(m, "%shas dead binder\n", prefix);
		अवरोध;
	हाल BINDER_WORK_DEAD_BINDER_AND_CLEAR:
		seq_म_लिखो(m, "%shas cleared dead binder\n", prefix);
		अवरोध;
	हाल BINDER_WORK_CLEAR_DEATH_NOTIFICATION:
		seq_म_लिखो(m, "%shas cleared death notification\n", prefix);
		अवरोध;
	शेष:
		seq_म_लिखो(m, "%sunknown work: type %d\n", prefix, w->type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_binder_thपढ़ो_ilocked(काष्ठा seq_file *m,
					काष्ठा binder_thपढ़ो *thपढ़ो,
					पूर्णांक prपूर्णांक_always)
अणु
	काष्ठा binder_transaction *t;
	काष्ठा binder_work *w;
	माप_प्रकार start_pos = m->count;
	माप_प्रकार header_pos;

	seq_म_लिखो(m, "  thread %d: l %02x need_return %d tr %d\n",
			thपढ़ो->pid, thपढ़ो->looper,
			thपढ़ो->looper_need_वापस,
			atomic_पढ़ो(&thपढ़ो->पंचांगp_ref));
	header_pos = m->count;
	t = thपढ़ो->transaction_stack;
	जबतक (t) अणु
		अगर (t->from == thपढ़ो) अणु
			prपूर्णांक_binder_transaction_ilocked(m, thपढ़ो->proc,
					"    outgoing transaction", t);
			t = t->from_parent;
		पूर्ण अन्यथा अगर (t->to_thपढ़ो == thपढ़ो) अणु
			prपूर्णांक_binder_transaction_ilocked(m, thपढ़ो->proc,
						 "    incoming transaction", t);
			t = t->to_parent;
		पूर्ण अन्यथा अणु
			prपूर्णांक_binder_transaction_ilocked(m, thपढ़ो->proc,
					"    bad transaction", t);
			t = शून्य;
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(w, &thपढ़ो->toकरो, entry) अणु
		prपूर्णांक_binder_work_ilocked(m, thपढ़ो->proc, "    ",
					  "    pending transaction", w);
	पूर्ण
	अगर (!prपूर्णांक_always && m->count == header_pos)
		m->count = start_pos;
पूर्ण

अटल व्योम prपूर्णांक_binder_node_nilocked(काष्ठा seq_file *m,
				       काष्ठा binder_node *node)
अणु
	काष्ठा binder_ref *ref;
	काष्ठा binder_work *w;
	पूर्णांक count;

	count = 0;
	hlist_क्रम_each_entry(ref, &node->refs, node_entry)
		count++;

	seq_म_लिखो(m, "  node %d: u%016llx c%016llx hs %d hw %d ls %d lw %d is %d iw %d tr %d",
		   node->debug_id, (u64)node->ptr, (u64)node->cookie,
		   node->has_strong_ref, node->has_weak_ref,
		   node->local_strong_refs, node->local_weak_refs,
		   node->पूर्णांकernal_strong_refs, count, node->पंचांगp_refs);
	अगर (count) अणु
		seq_माला_दो(m, " proc");
		hlist_क्रम_each_entry(ref, &node->refs, node_entry)
			seq_म_लिखो(m, " %d", ref->proc->pid);
	पूर्ण
	seq_माला_दो(m, "\n");
	अगर (node->proc) अणु
		list_क्रम_each_entry(w, &node->async_toकरो, entry)
			prपूर्णांक_binder_work_ilocked(m, node->proc, "    ",
					  "    pending async transaction", w);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_binder_ref_olocked(काष्ठा seq_file *m,
				     काष्ठा binder_ref *ref)
अणु
	binder_node_lock(ref->node);
	seq_म_लिखो(m, "  ref %d: desc %d %snode %d s %d w %d d %pK\n",
		   ref->data.debug_id, ref->data.desc,
		   ref->node->proc ? "" : "dead ",
		   ref->node->debug_id, ref->data.strong,
		   ref->data.weak, ref->death);
	binder_node_unlock(ref->node);
पूर्ण

अटल व्योम prपूर्णांक_binder_proc(काष्ठा seq_file *m,
			      काष्ठा binder_proc *proc, पूर्णांक prपूर्णांक_all)
अणु
	काष्ठा binder_work *w;
	काष्ठा rb_node *n;
	माप_प्रकार start_pos = m->count;
	माप_प्रकार header_pos;
	काष्ठा binder_node *last_node = शून्य;

	seq_म_लिखो(m, "proc %d\n", proc->pid);
	seq_म_लिखो(m, "context %s\n", proc->context->name);
	header_pos = m->count;

	binder_inner_proc_lock(proc);
	क्रम (n = rb_first(&proc->thपढ़ोs); n != शून्य; n = rb_next(n))
		prपूर्णांक_binder_thपढ़ो_ilocked(m, rb_entry(n, काष्ठा binder_thपढ़ो,
						rb_node), prपूर्णांक_all);

	क्रम (n = rb_first(&proc->nodes); n != शून्य; n = rb_next(n)) अणु
		काष्ठा binder_node *node = rb_entry(n, काष्ठा binder_node,
						    rb_node);
		अगर (!prपूर्णांक_all && !node->has_async_transaction)
			जारी;

		/*
		 * take a temporary reference on the node so it
		 * survives and isn't हटाओd from the tree
		 * जबतक we prपूर्णांक it.
		 */
		binder_inc_node_पंचांगpref_ilocked(node);
		/* Need to drop inner lock to take node lock */
		binder_inner_proc_unlock(proc);
		अगर (last_node)
			binder_put_node(last_node);
		binder_node_inner_lock(node);
		prपूर्णांक_binder_node_nilocked(m, node);
		binder_node_inner_unlock(node);
		last_node = node;
		binder_inner_proc_lock(proc);
	पूर्ण
	binder_inner_proc_unlock(proc);
	अगर (last_node)
		binder_put_node(last_node);

	अगर (prपूर्णांक_all) अणु
		binder_proc_lock(proc);
		क्रम (n = rb_first(&proc->refs_by_desc);
		     n != शून्य;
		     n = rb_next(n))
			prपूर्णांक_binder_ref_olocked(m, rb_entry(n,
							    काष्ठा binder_ref,
							    rb_node_desc));
		binder_proc_unlock(proc);
	पूर्ण
	binder_alloc_prपूर्णांक_allocated(m, &proc->alloc);
	binder_inner_proc_lock(proc);
	list_क्रम_each_entry(w, &proc->toकरो, entry)
		prपूर्णांक_binder_work_ilocked(m, proc, "  ",
					  "  pending transaction", w);
	list_क्रम_each_entry(w, &proc->delivered_death, entry) अणु
		seq_माला_दो(m, "  has delivered dead binder\n");
		अवरोध;
	पूर्ण
	binder_inner_proc_unlock(proc);
	अगर (!prपूर्णांक_all && m->count == header_pos)
		m->count = start_pos;
पूर्ण

अटल स्थिर अक्षर * स्थिर binder_वापस_strings[] = अणु
	"BR_ERROR",
	"BR_OK",
	"BR_TRANSACTION",
	"BR_REPLY",
	"BR_ACQUIRE_RESULT",
	"BR_DEAD_REPLY",
	"BR_TRANSACTION_COMPLETE",
	"BR_INCREFS",
	"BR_ACQUIRE",
	"BR_RELEASE",
	"BR_DECREFS",
	"BR_ATTEMPT_ACQUIRE",
	"BR_NOOP",
	"BR_SPAWN_LOOPER",
	"BR_FINISHED",
	"BR_DEAD_BINDER",
	"BR_CLEAR_DEATH_NOTIFICATION_DONE",
	"BR_FAILED_REPLY",
	"BR_FROZEN_REPLY",
	"BR_ONEWAY_SPAM_SUSPECT",
पूर्ण;

अटल स्थिर अक्षर * स्थिर binder_command_strings[] = अणु
	"BC_TRANSACTION",
	"BC_REPLY",
	"BC_ACQUIRE_RESULT",
	"BC_FREE_BUFFER",
	"BC_INCREFS",
	"BC_ACQUIRE",
	"BC_RELEASE",
	"BC_DECREFS",
	"BC_INCREFS_DONE",
	"BC_ACQUIRE_DONE",
	"BC_ATTEMPT_ACQUIRE",
	"BC_REGISTER_LOOPER",
	"BC_ENTER_LOOPER",
	"BC_EXIT_LOOPER",
	"BC_REQUEST_DEATH_NOTIFICATION",
	"BC_CLEAR_DEATH_NOTIFICATION",
	"BC_DEAD_BINDER_DONE",
	"BC_TRANSACTION_SG",
	"BC_REPLY_SG",
पूर्ण;

अटल स्थिर अक्षर * स्थिर binder_objstat_strings[] = अणु
	"proc",
	"thread",
	"node",
	"ref",
	"death",
	"transaction",
	"transaction_complete"
पूर्ण;

अटल व्योम prपूर्णांक_binder_stats(काष्ठा seq_file *m, स्थिर अक्षर *prefix,
			       काष्ठा binder_stats *stats)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(stats->bc) !=
		     ARRAY_SIZE(binder_command_strings));
	क्रम (i = 0; i < ARRAY_SIZE(stats->bc); i++) अणु
		पूर्णांक temp = atomic_पढ़ो(&stats->bc[i]);

		अगर (temp)
			seq_म_लिखो(m, "%s%s: %d\n", prefix,
				   binder_command_strings[i], temp);
	पूर्ण

	BUILD_BUG_ON(ARRAY_SIZE(stats->br) !=
		     ARRAY_SIZE(binder_वापस_strings));
	क्रम (i = 0; i < ARRAY_SIZE(stats->br); i++) अणु
		पूर्णांक temp = atomic_पढ़ो(&stats->br[i]);

		अगर (temp)
			seq_म_लिखो(m, "%s%s: %d\n", prefix,
				   binder_वापस_strings[i], temp);
	पूर्ण

	BUILD_BUG_ON(ARRAY_SIZE(stats->obj_created) !=
		     ARRAY_SIZE(binder_objstat_strings));
	BUILD_BUG_ON(ARRAY_SIZE(stats->obj_created) !=
		     ARRAY_SIZE(stats->obj_deleted));
	क्रम (i = 0; i < ARRAY_SIZE(stats->obj_created); i++) अणु
		पूर्णांक created = atomic_पढ़ो(&stats->obj_created[i]);
		पूर्णांक deleted = atomic_पढ़ो(&stats->obj_deleted[i]);

		अगर (created || deleted)
			seq_म_लिखो(m, "%s%s: active %d total %d\n",
				prefix,
				binder_objstat_strings[i],
				created - deleted,
				created);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_binder_proc_stats(काष्ठा seq_file *m,
				    काष्ठा binder_proc *proc)
अणु
	काष्ठा binder_work *w;
	काष्ठा binder_thपढ़ो *thपढ़ो;
	काष्ठा rb_node *n;
	पूर्णांक count, strong, weak, पढ़ोy_thपढ़ोs;
	माप_प्रकार मुक्त_async_space =
		binder_alloc_get_मुक्त_async_space(&proc->alloc);

	seq_म_लिखो(m, "proc %d\n", proc->pid);
	seq_म_लिखो(m, "context %s\n", proc->context->name);
	count = 0;
	पढ़ोy_thपढ़ोs = 0;
	binder_inner_proc_lock(proc);
	क्रम (n = rb_first(&proc->thपढ़ोs); n != शून्य; n = rb_next(n))
		count++;

	list_क्रम_each_entry(thपढ़ो, &proc->रुकोing_thपढ़ोs, रुकोing_thपढ़ो_node)
		पढ़ोy_thपढ़ोs++;

	seq_म_लिखो(m, "  threads: %d\n", count);
	seq_म_लिखो(m, "  requested threads: %d+%d/%d\n"
			"  ready threads %d\n"
			"  free async space %zd\n", proc->requested_thपढ़ोs,
			proc->requested_thपढ़ोs_started, proc->max_thपढ़ोs,
			पढ़ोy_thपढ़ोs,
			मुक्त_async_space);
	count = 0;
	क्रम (n = rb_first(&proc->nodes); n != शून्य; n = rb_next(n))
		count++;
	binder_inner_proc_unlock(proc);
	seq_म_लिखो(m, "  nodes: %d\n", count);
	count = 0;
	strong = 0;
	weak = 0;
	binder_proc_lock(proc);
	क्रम (n = rb_first(&proc->refs_by_desc); n != शून्य; n = rb_next(n)) अणु
		काष्ठा binder_ref *ref = rb_entry(n, काष्ठा binder_ref,
						  rb_node_desc);
		count++;
		strong += ref->data.strong;
		weak += ref->data.weak;
	पूर्ण
	binder_proc_unlock(proc);
	seq_म_लिखो(m, "  refs: %d s %d w %d\n", count, strong, weak);

	count = binder_alloc_get_allocated_count(&proc->alloc);
	seq_म_लिखो(m, "  buffers: %d\n", count);

	binder_alloc_prपूर्णांक_pages(m, &proc->alloc);

	count = 0;
	binder_inner_proc_lock(proc);
	list_क्रम_each_entry(w, &proc->toकरो, entry) अणु
		अगर (w->type == BINDER_WORK_TRANSACTION)
			count++;
	पूर्ण
	binder_inner_proc_unlock(proc);
	seq_म_लिखो(m, "  pending transactions: %d\n", count);

	prपूर्णांक_binder_stats(m, "  ", &proc->stats);
पूर्ण


पूर्णांक binder_state_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा binder_proc *proc;
	काष्ठा binder_node *node;
	काष्ठा binder_node *last_node = शून्य;

	seq_माला_दो(m, "binder state:\n");

	spin_lock(&binder_dead_nodes_lock);
	अगर (!hlist_empty(&binder_dead_nodes))
		seq_माला_दो(m, "dead nodes:\n");
	hlist_क्रम_each_entry(node, &binder_dead_nodes, dead_node) अणु
		/*
		 * take a temporary reference on the node so it
		 * survives and isn't हटाओd from the list
		 * जबतक we prपूर्णांक it.
		 */
		node->पंचांगp_refs++;
		spin_unlock(&binder_dead_nodes_lock);
		अगर (last_node)
			binder_put_node(last_node);
		binder_node_lock(node);
		prपूर्णांक_binder_node_nilocked(m, node);
		binder_node_unlock(node);
		last_node = node;
		spin_lock(&binder_dead_nodes_lock);
	पूर्ण
	spin_unlock(&binder_dead_nodes_lock);
	अगर (last_node)
		binder_put_node(last_node);

	mutex_lock(&binder_procs_lock);
	hlist_क्रम_each_entry(proc, &binder_procs, proc_node)
		prपूर्णांक_binder_proc(m, proc, 1);
	mutex_unlock(&binder_procs_lock);

	वापस 0;
पूर्ण

पूर्णांक binder_stats_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा binder_proc *proc;

	seq_माला_दो(m, "binder stats:\n");

	prपूर्णांक_binder_stats(m, "", &binder_stats);

	mutex_lock(&binder_procs_lock);
	hlist_क्रम_each_entry(proc, &binder_procs, proc_node)
		prपूर्णांक_binder_proc_stats(m, proc);
	mutex_unlock(&binder_procs_lock);

	वापस 0;
पूर्ण

पूर्णांक binder_transactions_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा binder_proc *proc;

	seq_माला_दो(m, "binder transactions:\n");
	mutex_lock(&binder_procs_lock);
	hlist_क्रम_each_entry(proc, &binder_procs, proc_node)
		prपूर्णांक_binder_proc(m, proc, 0);
	mutex_unlock(&binder_procs_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक proc_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा binder_proc *itr;
	पूर्णांक pid = (अचिन्हित दीर्घ)m->निजी;

	mutex_lock(&binder_procs_lock);
	hlist_क्रम_each_entry(itr, &binder_procs, proc_node) अणु
		अगर (itr->pid == pid) अणु
			seq_माला_दो(m, "binder proc state:\n");
			prपूर्णांक_binder_proc(m, itr, 1);
		पूर्ण
	पूर्ण
	mutex_unlock(&binder_procs_lock);

	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_binder_transaction_log_entry(काष्ठा seq_file *m,
					काष्ठा binder_transaction_log_entry *e)
अणु
	पूर्णांक debug_id = READ_ONCE(e->debug_id_करोne);
	/*
	 * पढ़ो barrier to guarantee debug_id_करोne पढ़ो beक्रमe
	 * we prपूर्णांक the log values
	 */
	smp_rmb();
	seq_म_लिखो(m,
		   "%d: %s from %d:%d to %d:%d context %s node %d handle %d size %d:%d ret %d/%d l=%d",
		   e->debug_id, (e->call_type == 2) ? "reply" :
		   ((e->call_type == 1) ? "async" : "call "), e->from_proc,
		   e->from_thपढ़ो, e->to_proc, e->to_thपढ़ो, e->context_name,
		   e->to_node, e->target_handle, e->data_size, e->offsets_size,
		   e->वापस_error, e->वापस_error_param,
		   e->वापस_error_line);
	/*
	 * पढ़ो-barrier to guarantee पढ़ो of debug_id_करोne after
	 * करोne prपूर्णांकing the fields of the entry
	 */
	smp_rmb();
	seq_म_लिखो(m, debug_id && debug_id == READ_ONCE(e->debug_id_करोne) ?
			"\n" : " (incomplete)\n");
पूर्ण

पूर्णांक binder_transaction_log_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा binder_transaction_log *log = m->निजी;
	अचिन्हित पूर्णांक log_cur = atomic_पढ़ो(&log->cur);
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक cur;
	पूर्णांक i;

	count = log_cur + 1;
	cur = count < ARRAY_SIZE(log->entry) && !log->full ?
		0 : count % ARRAY_SIZE(log->entry);
	अगर (count > ARRAY_SIZE(log->entry) || log->full)
		count = ARRAY_SIZE(log->entry);
	क्रम (i = 0; i < count; i++) अणु
		अचिन्हित पूर्णांक index = cur++ % ARRAY_SIZE(log->entry);

		prपूर्णांक_binder_transaction_log_entry(m, &log->entry[index]);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations binder_fops = अणु
	.owner = THIS_MODULE,
	.poll = binder_poll,
	.unlocked_ioctl = binder_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.mmap = binder_mmap,
	.खोलो = binder_खोलो,
	.flush = binder_flush,
	.release = binder_release,
पूर्ण;

अटल पूर्णांक __init init_binder_device(स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	काष्ठा binder_device *binder_device;

	binder_device = kzalloc(माप(*binder_device), GFP_KERNEL);
	अगर (!binder_device)
		वापस -ENOMEM;

	binder_device->miscdev.fops = &binder_fops;
	binder_device->miscdev.minor = MISC_DYNAMIC_MINOR;
	binder_device->miscdev.name = name;

	refcount_set(&binder_device->ref, 1);
	binder_device->context.binder_context_mgr_uid = INVALID_UID;
	binder_device->context.name = name;
	mutex_init(&binder_device->context.context_mgr_node_lock);

	ret = misc_रेजिस्टर(&binder_device->miscdev);
	अगर (ret < 0) अणु
		kमुक्त(binder_device);
		वापस ret;
	पूर्ण

	hlist_add_head(&binder_device->hlist, &binder_devices);

	वापस ret;
पूर्ण

अटल पूर्णांक __init binder_init(व्योम)
अणु
	पूर्णांक ret;
	अक्षर *device_name, *device_पंचांगp;
	काष्ठा binder_device *device;
	काष्ठा hlist_node *पंचांगp;
	अक्षर *device_names = शून्य;

	ret = binder_alloc_shrinker_init();
	अगर (ret)
		वापस ret;

	atomic_set(&binder_transaction_log.cur, ~0U);
	atomic_set(&binder_transaction_log_failed.cur, ~0U);

	binder_debugfs_dir_entry_root = debugfs_create_dir("binder", शून्य);
	अगर (binder_debugfs_dir_entry_root)
		binder_debugfs_dir_entry_proc = debugfs_create_dir("proc",
						 binder_debugfs_dir_entry_root);

	अगर (binder_debugfs_dir_entry_root) अणु
		debugfs_create_file("state",
				    0444,
				    binder_debugfs_dir_entry_root,
				    शून्य,
				    &binder_state_fops);
		debugfs_create_file("stats",
				    0444,
				    binder_debugfs_dir_entry_root,
				    शून्य,
				    &binder_stats_fops);
		debugfs_create_file("transactions",
				    0444,
				    binder_debugfs_dir_entry_root,
				    शून्य,
				    &binder_transactions_fops);
		debugfs_create_file("transaction_log",
				    0444,
				    binder_debugfs_dir_entry_root,
				    &binder_transaction_log,
				    &binder_transaction_log_fops);
		debugfs_create_file("failed_transaction_log",
				    0444,
				    binder_debugfs_dir_entry_root,
				    &binder_transaction_log_failed,
				    &binder_transaction_log_fops);
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_ANDROID_BINDERFS) &&
	    म_भेद(binder_devices_param, "") != 0) अणु
		/*
		* Copy the module_parameter string, because we करोn't want to
		* tokenize it in-place.
		 */
		device_names = kstrdup(binder_devices_param, GFP_KERNEL);
		अगर (!device_names) अणु
			ret = -ENOMEM;
			जाओ err_alloc_device_names_failed;
		पूर्ण

		device_पंचांगp = device_names;
		जबतक ((device_name = strsep(&device_पंचांगp, ","))) अणु
			ret = init_binder_device(device_name);
			अगर (ret)
				जाओ err_init_binder_device_failed;
		पूर्ण
	पूर्ण

	ret = init_binderfs();
	अगर (ret)
		जाओ err_init_binder_device_failed;

	वापस ret;

err_init_binder_device_failed:
	hlist_क्रम_each_entry_safe(device, पंचांगp, &binder_devices, hlist) अणु
		misc_deरेजिस्टर(&device->miscdev);
		hlist_del(&device->hlist);
		kमुक्त(device);
	पूर्ण

	kमुक्त(device_names);

err_alloc_device_names_failed:
	debugfs_हटाओ_recursive(binder_debugfs_dir_entry_root);

	वापस ret;
पूर्ण

device_initcall(binder_init);

#घोषणा CREATE_TRACE_POINTS
#समावेश "binder_trace.h"

MODULE_LICENSE("GPL v2");
