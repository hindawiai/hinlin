<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic pidhash and scalable, समय-bounded PID allocator
 *
 * (C) 2002-2003 Nadia Yvette Chambers, IBM
 * (C) 2004 Nadia Yvette Chambers, Oracle
 * (C) 2002-2004 Ingo Molnar, Red Hat
 *
 * pid-काष्ठाures are backing objects क्रम tasks sharing a given ID to chain
 * against. There is very little to them aside from hashing them and
 * parking tasks using given ID's on a list.
 *
 * The hash is always changed with the tasklist_lock ग_लिखो-acquired,
 * and the hash is only accessed with the tasklist_lock at least
 * पढ़ो-acquired, so there's no additional SMP locking needed here.
 *
 * We have a list of biपंचांगap pages, which biपंचांगaps represent the PID space.
 * Allocating and मुक्तing PIDs is completely lockless. The worst-हाल
 * allocation scenario when all but one out of 1 million PIDs possible are
 * allocated alपढ़ोy: the scanning of 32 list entries and at most PAGE_SIZE
 * bytes. The typical fastpath is a single successful setbit. Freeing is O(1).
 *
 * Pid namespaces:
 *    (C) 2007 Pavel Emelyanov <xemul@खोलोvz.org>, OpenVZ, SWsoft Inc.
 *    (C) 2007 Sukadev Bhattiprolu <sukadev@us.ibm.com>, IBM
 *     Many thanks to Oleg Nesterov क्रम comments and help
 *
 */

#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/rculist.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/init_task.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/refcount.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/idr.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/pidfd.h>

काष्ठा pid init_काष्ठा_pid = अणु
	.count		= REFCOUNT_INIT(1),
	.tasks		= अणु
		अणु .first = शून्य पूर्ण,
		अणु .first = शून्य पूर्ण,
		अणु .first = शून्य पूर्ण,
	पूर्ण,
	.level		= 0,
	.numbers	= अणु अणु
		.nr		= 0,
		.ns		= &init_pid_ns,
	पूर्ण, पूर्ण
पूर्ण;

पूर्णांक pid_max = PID_MAX_DEFAULT;

#घोषणा RESERVED_PIDS		300

पूर्णांक pid_max_min = RESERVED_PIDS + 1;
पूर्णांक pid_max_max = PID_MAX_LIMIT;

/*
 * PID-map pages start out as शून्य, they get allocated upon
 * first use and are never deallocated. This way a low pid_max
 * value करोes not cause lots of biपंचांगaps to be allocated, but
 * the scheme scales to up to 4 million PIDs, runसमय.
 */
काष्ठा pid_namespace init_pid_ns = अणु
	.ns.count = REFCOUNT_INIT(2),
	.idr = IDR_INIT(init_pid_ns.idr),
	.pid_allocated = PIDNS_ADDING,
	.level = 0,
	.child_reaper = &init_task,
	.user_ns = &init_user_ns,
	.ns.inum = PROC_PID_INIT_INO,
#अगर_घोषित CONFIG_PID_NS
	.ns.ops = &pidns_operations,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL_GPL(init_pid_ns);

/*
 * Note: disable पूर्णांकerrupts जबतक the pidmap_lock is held as an
 * पूर्णांकerrupt might come in and करो पढ़ो_lock(&tasklist_lock).
 *
 * If we करोn't disable पूर्णांकerrupts there is a nasty deadlock between
 * detach_pid()->मुक्त_pid() and another cpu that करोes
 * spin_lock(&pidmap_lock) followed by an पूर्णांकerrupt routine that करोes
 * पढ़ो_lock(&tasklist_lock);
 *
 * After we clean up the tasklist_lock and know there are no
 * irq handlers that take it we can leave the पूर्णांकerrupts enabled.
 * For now it is easier to be safe than to prove it can't happen.
 */

अटल  __cacheline_aligned_in_smp DEFINE_SPINLOCK(pidmap_lock);

व्योम put_pid(काष्ठा pid *pid)
अणु
	काष्ठा pid_namespace *ns;

	अगर (!pid)
		वापस;

	ns = pid->numbers[pid->level].ns;
	अगर (refcount_dec_and_test(&pid->count)) अणु
		kmem_cache_मुक्त(ns->pid_cachep, pid);
		put_pid_ns(ns);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(put_pid);

अटल व्योम delayed_put_pid(काष्ठा rcu_head *rhp)
अणु
	काष्ठा pid *pid = container_of(rhp, काष्ठा pid, rcu);
	put_pid(pid);
पूर्ण

व्योम मुक्त_pid(काष्ठा pid *pid)
अणु
	/* We can be called with ग_लिखो_lock_irq(&tasklist_lock) held */
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pidmap_lock, flags);
	क्रम (i = 0; i <= pid->level; i++) अणु
		काष्ठा upid *upid = pid->numbers + i;
		काष्ठा pid_namespace *ns = upid->ns;
		चयन (--ns->pid_allocated) अणु
		हाल 2:
		हाल 1:
			/* When all that is left in the pid namespace
			 * is the reaper wake up the reaper.  The reaper
			 * may be sleeping in zap_pid_ns_processes().
			 */
			wake_up_process(ns->child_reaper);
			अवरोध;
		हाल PIDNS_ADDING:
			/* Handle a विभाजन failure of the first process */
			WARN_ON(ns->child_reaper);
			ns->pid_allocated = 0;
			अवरोध;
		पूर्ण

		idr_हटाओ(&ns->idr, upid->nr);
	पूर्ण
	spin_unlock_irqrestore(&pidmap_lock, flags);

	call_rcu(&pid->rcu, delayed_put_pid);
पूर्ण

काष्ठा pid *alloc_pid(काष्ठा pid_namespace *ns, pid_t *set_tid,
		      माप_प्रकार set_tid_size)
अणु
	काष्ठा pid *pid;
	क्रमागत pid_type type;
	पूर्णांक i, nr;
	काष्ठा pid_namespace *पंचांगp;
	काष्ठा upid *upid;
	पूर्णांक retval = -ENOMEM;

	/*
	 * set_tid_size contains the size of the set_tid array. Starting at
	 * the most nested currently active PID namespace it tells alloc_pid()
	 * which PID to set क्रम a process in that most nested PID namespace
	 * up to set_tid_size PID namespaces. It करोes not have to set the PID
	 * क्रम a process in all nested PID namespaces but set_tid_size must
	 * never be greater than the current ns->level + 1.
	 */
	अगर (set_tid_size > ns->level + 1)
		वापस ERR_PTR(-EINVAL);

	pid = kmem_cache_alloc(ns->pid_cachep, GFP_KERNEL);
	अगर (!pid)
		वापस ERR_PTR(retval);

	पंचांगp = ns;
	pid->level = ns->level;

	क्रम (i = ns->level; i >= 0; i--) अणु
		पूर्णांक tid = 0;

		अगर (set_tid_size) अणु
			tid = set_tid[ns->level - i];

			retval = -EINVAL;
			अगर (tid < 1 || tid >= pid_max)
				जाओ out_मुक्त;
			/*
			 * Also fail अगर a PID != 1 is requested and
			 * no PID 1 exists.
			 */
			अगर (tid != 1 && !पंचांगp->child_reaper)
				जाओ out_मुक्त;
			retval = -EPERM;
			अगर (!checkpoपूर्णांक_restore_ns_capable(पंचांगp->user_ns))
				जाओ out_मुक्त;
			set_tid_size--;
		पूर्ण

		idr_preload(GFP_KERNEL);
		spin_lock_irq(&pidmap_lock);

		अगर (tid) अणु
			nr = idr_alloc(&पंचांगp->idr, शून्य, tid,
				       tid + 1, GFP_ATOMIC);
			/*
			 * If ENOSPC is वापसed it means that the PID is
			 * alreay in use. Return EEXIST in that हाल.
			 */
			अगर (nr == -ENOSPC)
				nr = -EEXIST;
		पूर्ण अन्यथा अणु
			पूर्णांक pid_min = 1;
			/*
			 * init really needs pid 1, but after reaching the
			 * maximum wrap back to RESERVED_PIDS
			 */
			अगर (idr_get_cursor(&पंचांगp->idr) > RESERVED_PIDS)
				pid_min = RESERVED_PIDS;

			/*
			 * Store a null poपूर्णांकer so find_pid_ns करोes not find
			 * a partially initialized PID (see below).
			 */
			nr = idr_alloc_cyclic(&पंचांगp->idr, शून्य, pid_min,
					      pid_max, GFP_ATOMIC);
		पूर्ण
		spin_unlock_irq(&pidmap_lock);
		idr_preload_end();

		अगर (nr < 0) अणु
			retval = (nr == -ENOSPC) ? -EAGAIN : nr;
			जाओ out_मुक्त;
		पूर्ण

		pid->numbers[i].nr = nr;
		pid->numbers[i].ns = पंचांगp;
		पंचांगp = पंचांगp->parent;
	पूर्ण

	/*
	 * ENOMEM is not the most obvious choice especially क्रम the हाल
	 * where the child subreaper has alपढ़ोy निकासed and the pid
	 * namespace denies the creation of any new processes. But ENOMEM
	 * is what we have exposed to userspace क्रम a दीर्घ समय and it is
	 * करोcumented behavior क्रम pid namespaces. So we can't easily
	 * change it even अगर there were an error code better suited.
	 */
	retval = -ENOMEM;

	get_pid_ns(ns);
	refcount_set(&pid->count, 1);
	spin_lock_init(&pid->lock);
	क्रम (type = 0; type < PIDTYPE_MAX; ++type)
		INIT_HLIST_HEAD(&pid->tasks[type]);

	init_रुकोqueue_head(&pid->रुको_pidfd);
	INIT_HLIST_HEAD(&pid->inodes);

	upid = pid->numbers + ns->level;
	spin_lock_irq(&pidmap_lock);
	अगर (!(ns->pid_allocated & PIDNS_ADDING))
		जाओ out_unlock;
	क्रम ( ; upid >= pid->numbers; --upid) अणु
		/* Make the PID visible to find_pid_ns. */
		idr_replace(&upid->ns->idr, pid, upid->nr);
		upid->ns->pid_allocated++;
	पूर्ण
	spin_unlock_irq(&pidmap_lock);

	वापस pid;

out_unlock:
	spin_unlock_irq(&pidmap_lock);
	put_pid_ns(ns);

out_मुक्त:
	spin_lock_irq(&pidmap_lock);
	जबतक (++i <= ns->level) अणु
		upid = pid->numbers + i;
		idr_हटाओ(&upid->ns->idr, upid->nr);
	पूर्ण

	/* On failure to allocate the first pid, reset the state */
	अगर (ns->pid_allocated == PIDNS_ADDING)
		idr_set_cursor(&ns->idr, 0);

	spin_unlock_irq(&pidmap_lock);

	kmem_cache_मुक्त(ns->pid_cachep, pid);
	वापस ERR_PTR(retval);
पूर्ण

व्योम disable_pid_allocation(काष्ठा pid_namespace *ns)
अणु
	spin_lock_irq(&pidmap_lock);
	ns->pid_allocated &= ~PIDNS_ADDING;
	spin_unlock_irq(&pidmap_lock);
पूर्ण

काष्ठा pid *find_pid_ns(पूर्णांक nr, काष्ठा pid_namespace *ns)
अणु
	वापस idr_find(&ns->idr, nr);
पूर्ण
EXPORT_SYMBOL_GPL(find_pid_ns);

काष्ठा pid *find_vpid(पूर्णांक nr)
अणु
	वापस find_pid_ns(nr, task_active_pid_ns(current));
पूर्ण
EXPORT_SYMBOL_GPL(find_vpid);

अटल काष्ठा pid **task_pid_ptr(काष्ठा task_काष्ठा *task, क्रमागत pid_type type)
अणु
	वापस (type == PIDTYPE_PID) ?
		&task->thपढ़ो_pid :
		&task->संकेत->pids[type];
पूर्ण

/*
 * attach_pid() must be called with the tasklist_lock ग_लिखो-held.
 */
व्योम attach_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type type)
अणु
	काष्ठा pid *pid = *task_pid_ptr(task, type);
	hlist_add_head_rcu(&task->pid_links[type], &pid->tasks[type]);
पूर्ण

अटल व्योम __change_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type type,
			काष्ठा pid *new)
अणु
	काष्ठा pid **pid_ptr = task_pid_ptr(task, type);
	काष्ठा pid *pid;
	पूर्णांक पंचांगp;

	pid = *pid_ptr;

	hlist_del_rcu(&task->pid_links[type]);
	*pid_ptr = new;

	क्रम (पंचांगp = PIDTYPE_MAX; --पंचांगp >= 0; )
		अगर (pid_has_task(pid, पंचांगp))
			वापस;

	मुक्त_pid(pid);
पूर्ण

व्योम detach_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type type)
अणु
	__change_pid(task, type, शून्य);
पूर्ण

व्योम change_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type type,
		काष्ठा pid *pid)
अणु
	__change_pid(task, type, pid);
	attach_pid(task, type);
पूर्ण

व्योम exchange_tids(काष्ठा task_काष्ठा *left, काष्ठा task_काष्ठा *right)
अणु
	काष्ठा pid *pid1 = left->thपढ़ो_pid;
	काष्ठा pid *pid2 = right->thपढ़ो_pid;
	काष्ठा hlist_head *head1 = &pid1->tasks[PIDTYPE_PID];
	काष्ठा hlist_head *head2 = &pid2->tasks[PIDTYPE_PID];

	/* Swap the single entry tid lists */
	hlists_swap_heads_rcu(head1, head2);

	/* Swap the per task_काष्ठा pid */
	rcu_assign_poपूर्णांकer(left->thपढ़ो_pid, pid2);
	rcu_assign_poपूर्णांकer(right->thपढ़ो_pid, pid1);

	/* Swap the cached value */
	WRITE_ONCE(left->pid, pid_nr(pid2));
	WRITE_ONCE(right->pid, pid_nr(pid1));
पूर्ण

/* transfer_pid is an optimization of attach_pid(new), detach_pid(old) */
व्योम transfer_pid(काष्ठा task_काष्ठा *old, काष्ठा task_काष्ठा *new,
			   क्रमागत pid_type type)
अणु
	अगर (type == PIDTYPE_PID)
		new->thपढ़ो_pid = old->thपढ़ो_pid;
	hlist_replace_rcu(&old->pid_links[type], &new->pid_links[type]);
पूर्ण

काष्ठा task_काष्ठा *pid_task(काष्ठा pid *pid, क्रमागत pid_type type)
अणु
	काष्ठा task_काष्ठा *result = शून्य;
	अगर (pid) अणु
		काष्ठा hlist_node *first;
		first = rcu_dereference_check(hlist_first_rcu(&pid->tasks[type]),
					      lockdep_tasklist_lock_is_held());
		अगर (first)
			result = hlist_entry(first, काष्ठा task_काष्ठा, pid_links[(type)]);
	पूर्ण
	वापस result;
पूर्ण
EXPORT_SYMBOL(pid_task);

/*
 * Must be called under rcu_पढ़ो_lock().
 */
काष्ठा task_काष्ठा *find_task_by_pid_ns(pid_t nr, काष्ठा pid_namespace *ns)
अणु
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_held(),
			 "find_task_by_pid_ns() needs rcu_read_lock() protection");
	वापस pid_task(find_pid_ns(nr, ns), PIDTYPE_PID);
पूर्ण

काष्ठा task_काष्ठा *find_task_by_vpid(pid_t vnr)
अणु
	वापस find_task_by_pid_ns(vnr, task_active_pid_ns(current));
पूर्ण

काष्ठा task_काष्ठा *find_get_task_by_vpid(pid_t nr)
अणु
	काष्ठा task_काष्ठा *task;

	rcu_पढ़ो_lock();
	task = find_task_by_vpid(nr);
	अगर (task)
		get_task_काष्ठा(task);
	rcu_पढ़ो_unlock();

	वापस task;
पूर्ण

काष्ठा pid *get_task_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type type)
अणु
	काष्ठा pid *pid;
	rcu_पढ़ो_lock();
	pid = get_pid(rcu_dereference(*task_pid_ptr(task, type)));
	rcu_पढ़ो_unlock();
	वापस pid;
पूर्ण
EXPORT_SYMBOL_GPL(get_task_pid);

काष्ठा task_काष्ठा *get_pid_task(काष्ठा pid *pid, क्रमागत pid_type type)
अणु
	काष्ठा task_काष्ठा *result;
	rcu_पढ़ो_lock();
	result = pid_task(pid, type);
	अगर (result)
		get_task_काष्ठा(result);
	rcu_पढ़ो_unlock();
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(get_pid_task);

काष्ठा pid *find_get_pid(pid_t nr)
अणु
	काष्ठा pid *pid;

	rcu_पढ़ो_lock();
	pid = get_pid(find_vpid(nr));
	rcu_पढ़ो_unlock();

	वापस pid;
पूर्ण
EXPORT_SYMBOL_GPL(find_get_pid);

pid_t pid_nr_ns(काष्ठा pid *pid, काष्ठा pid_namespace *ns)
अणु
	काष्ठा upid *upid;
	pid_t nr = 0;

	अगर (pid && ns->level <= pid->level) अणु
		upid = &pid->numbers[ns->level];
		अगर (upid->ns == ns)
			nr = upid->nr;
	पूर्ण
	वापस nr;
पूर्ण
EXPORT_SYMBOL_GPL(pid_nr_ns);

pid_t pid_vnr(काष्ठा pid *pid)
अणु
	वापस pid_nr_ns(pid, task_active_pid_ns(current));
पूर्ण
EXPORT_SYMBOL_GPL(pid_vnr);

pid_t __task_pid_nr_ns(काष्ठा task_काष्ठा *task, क्रमागत pid_type type,
			काष्ठा pid_namespace *ns)
अणु
	pid_t nr = 0;

	rcu_पढ़ो_lock();
	अगर (!ns)
		ns = task_active_pid_ns(current);
	nr = pid_nr_ns(rcu_dereference(*task_pid_ptr(task, type)), ns);
	rcu_पढ़ो_unlock();

	वापस nr;
पूर्ण
EXPORT_SYMBOL(__task_pid_nr_ns);

काष्ठा pid_namespace *task_active_pid_ns(काष्ठा task_काष्ठा *tsk)
अणु
	वापस ns_of_pid(task_pid(tsk));
पूर्ण
EXPORT_SYMBOL_GPL(task_active_pid_ns);

/*
 * Used by proc to find the first pid that is greater than or equal to nr.
 *
 * If there is a pid at nr this function is exactly the same as find_pid_ns.
 */
काष्ठा pid *find_ge_pid(पूर्णांक nr, काष्ठा pid_namespace *ns)
अणु
	वापस idr_get_next(&ns->idr, &nr);
पूर्ण

काष्ठा pid *pidfd_get_pid(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक *flags)
अणु
	काष्ठा fd f;
	काष्ठा pid *pid;

	f = fdget(fd);
	अगर (!f.file)
		वापस ERR_PTR(-EBADF);

	pid = pidfd_pid(f.file);
	अगर (!IS_ERR(pid)) अणु
		get_pid(pid);
		*flags = f.file->f_flags;
	पूर्ण

	fdput(f);
	वापस pid;
पूर्ण

/**
 * pidfd_create() - Create a new pid file descriptor.
 *
 * @pid:   काष्ठा pid that the pidfd will reference
 * @flags: flags to pass
 *
 * This creates a new pid file descriptor with the O_CLOEXEC flag set.
 *
 * Note, that this function can only be called after the fd table has
 * been unshared to aव्योम leaking the pidfd to the new process.
 *
 * Return: On success, a cloexec pidfd is वापसed.
 *         On error, a negative त्रुटि_सं number will be वापसed.
 */
अटल पूर्णांक pidfd_create(काष्ठा pid *pid, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक fd;

	fd = anon_inode_getfd("[pidfd]", &pidfd_fops, get_pid(pid),
			      flags | O_RDWR | O_CLOEXEC);
	अगर (fd < 0)
		put_pid(pid);

	वापस fd;
पूर्ण

/**
 * pidfd_खोलो() - Open new pid file descriptor.
 *
 * @pid:   pid क्रम which to retrieve a pidfd
 * @flags: flags to pass
 *
 * This creates a new pid file descriptor with the O_CLOEXEC flag set क्रम
 * the process identअगरied by @pid. Currently, the process identअगरied by
 * @pid must be a thपढ़ो-group leader. This restriction currently exists
 * क्रम all aspects of pidfds including pidfd creation (CLONE_PIDFD cannot
 * be used with CLONE_THREAD) and pidfd polling (only supports thपढ़ो group
 * leaders).
 *
 * Return: On success, a cloexec pidfd is वापसed.
 *         On error, a negative त्रुटि_सं number will be वापसed.
 */
SYSCALL_DEFINE2(pidfd_खोलो, pid_t, pid, अचिन्हित पूर्णांक, flags)
अणु
	पूर्णांक fd;
	काष्ठा pid *p;

	अगर (flags & ~PIDFD_NONBLOCK)
		वापस -EINVAL;

	अगर (pid <= 0)
		वापस -EINVAL;

	p = find_get_pid(pid);
	अगर (!p)
		वापस -ESRCH;

	अगर (pid_has_task(p, PIDTYPE_TGID))
		fd = pidfd_create(p, flags);
	अन्यथा
		fd = -EINVAL;

	put_pid(p);
	वापस fd;
पूर्ण

व्योम __init pid_idr_init(व्योम)
अणु
	/* Verअगरy no one has करोne anything silly: */
	BUILD_BUG_ON(PID_MAX_LIMIT >= PIDNS_ADDING);

	/* bump शेष and minimum pid_max based on number of cpus */
	pid_max = min(pid_max_max, max_t(पूर्णांक, pid_max,
				PIDS_PER_CPU_DEFAULT * num_possible_cpus()));
	pid_max_min = max_t(पूर्णांक, pid_max_min,
				PIDS_PER_CPU_MIN * num_possible_cpus());
	pr_info("pid_max: default: %u minimum: %u\n", pid_max, pid_max_min);

	idr_init(&init_pid_ns.idr);

	init_pid_ns.pid_cachep = KMEM_CACHE(pid,
			SLAB_HWCACHE_ALIGN | SLAB_PANIC | SLAB_ACCOUNT);
पूर्ण

अटल काष्ठा file *__pidfd_fget(काष्ठा task_काष्ठा *task, पूर्णांक fd)
अणु
	काष्ठा file *file;
	पूर्णांक ret;

	ret = करोwn_पढ़ो_समाप्तable(&task->संकेत->exec_update_lock);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (ptrace_may_access(task, PTRACE_MODE_ATTACH_REALCREDS))
		file = fget_task(task, fd);
	अन्यथा
		file = ERR_PTR(-EPERM);

	up_पढ़ो(&task->संकेत->exec_update_lock);

	वापस file ?: ERR_PTR(-EBADF);
पूर्ण

अटल पूर्णांक pidfd_getfd(काष्ठा pid *pid, पूर्णांक fd)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा file *file;
	पूर्णांक ret;

	task = get_pid_task(pid, PIDTYPE_PID);
	अगर (!task)
		वापस -ESRCH;

	file = __pidfd_fget(task, fd);
	put_task_काष्ठा(task);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ret = receive_fd(file, O_CLOEXEC);
	fput(file);

	वापस ret;
पूर्ण

/**
 * sys_pidfd_getfd() - Get a file descriptor from another process
 *
 * @pidfd:	the pidfd file descriptor of the process
 * @fd:		the file descriptor number to get
 * @flags:	flags on how to get the fd (reserved)
 *
 * This syscall माला_लो a copy of a file descriptor from another process
 * based on the pidfd, and file descriptor number. It requires that
 * the calling process has the ability to ptrace the process represented
 * by the pidfd. The process which is having its file descriptor copied
 * is otherwise unaffected.
 *
 * Return: On success, a cloexec file descriptor is वापसed.
 *         On error, a negative त्रुटि_सं number will be वापसed.
 */
SYSCALL_DEFINE3(pidfd_getfd, पूर्णांक, pidfd, पूर्णांक, fd,
		अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा pid *pid;
	काष्ठा fd f;
	पूर्णांक ret;

	/* flags is currently unused - make sure it's unset */
	अगर (flags)
		वापस -EINVAL;

	f = fdget(pidfd);
	अगर (!f.file)
		वापस -EBADF;

	pid = pidfd_pid(f.file);
	अगर (IS_ERR(pid))
		ret = PTR_ERR(pid);
	अन्यथा
		ret = pidfd_getfd(pid, fd);

	fdput(f);
	वापस ret;
पूर्ण
