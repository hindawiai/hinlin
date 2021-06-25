<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pid namespaces
 *
 * Authors:
 *    (C) 2007 Pavel Emelyanov <xemul@खोलोvz.org>, OpenVZ, SWsoft Inc.
 *    (C) 2007 Sukadev Bhattiprolu <sukadev@us.ibm.com>, IBM
 *     Many thanks to Oleg Nesterov क्रम comments and help
 *
 */

#समावेश <linux/pid.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/acct.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/reboot.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/idr.h>

अटल DEFINE_MUTEX(pid_caches_mutex);
अटल काष्ठा kmem_cache *pid_ns_cachep;
/* Write once array, filled from the beginning. */
अटल काष्ठा kmem_cache *pid_cache[MAX_PID_NS_LEVEL];

/*
 * creates the kmem cache to allocate pids from.
 * @level: pid namespace level
 */

अटल काष्ठा kmem_cache *create_pid_cachep(अचिन्हित पूर्णांक level)
अणु
	/* Level 0 is init_pid_ns.pid_cachep */
	काष्ठा kmem_cache **pkc = &pid_cache[level - 1];
	काष्ठा kmem_cache *kc;
	अक्षर name[4 + 10 + 1];
	अचिन्हित पूर्णांक len;

	kc = READ_ONCE(*pkc);
	अगर (kc)
		वापस kc;

	snम_लिखो(name, माप(name), "pid_%u", level + 1);
	len = माप(काष्ठा pid) + level * माप(काष्ठा upid);
	mutex_lock(&pid_caches_mutex);
	/* Name collision क्रमces to करो allocation under mutex. */
	अगर (!*pkc)
		*pkc = kmem_cache_create(name, len, 0, SLAB_HWCACHE_ALIGN, 0);
	mutex_unlock(&pid_caches_mutex);
	/* current can fail, but someone अन्यथा can succeed. */
	वापस READ_ONCE(*pkc);
पूर्ण

अटल काष्ठा ucounts *inc_pid_namespaces(काष्ठा user_namespace *ns)
अणु
	वापस inc_ucount(ns, current_euid(), UCOUNT_PID_NAMESPACES);
पूर्ण

अटल व्योम dec_pid_namespaces(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_PID_NAMESPACES);
पूर्ण

अटल काष्ठा pid_namespace *create_pid_namespace(काष्ठा user_namespace *user_ns,
	काष्ठा pid_namespace *parent_pid_ns)
अणु
	काष्ठा pid_namespace *ns;
	अचिन्हित पूर्णांक level = parent_pid_ns->level + 1;
	काष्ठा ucounts *ucounts;
	पूर्णांक err;

	err = -EINVAL;
	अगर (!in_userns(parent_pid_ns->user_ns, user_ns))
		जाओ out;

	err = -ENOSPC;
	अगर (level > MAX_PID_NS_LEVEL)
		जाओ out;
	ucounts = inc_pid_namespaces(user_ns);
	अगर (!ucounts)
		जाओ out;

	err = -ENOMEM;
	ns = kmem_cache_zalloc(pid_ns_cachep, GFP_KERNEL);
	अगर (ns == शून्य)
		जाओ out_dec;

	idr_init(&ns->idr);

	ns->pid_cachep = create_pid_cachep(level);
	अगर (ns->pid_cachep == शून्य)
		जाओ out_मुक्त_idr;

	err = ns_alloc_inum(&ns->ns);
	अगर (err)
		जाओ out_मुक्त_idr;
	ns->ns.ops = &pidns_operations;

	refcount_set(&ns->ns.count, 1);
	ns->level = level;
	ns->parent = get_pid_ns(parent_pid_ns);
	ns->user_ns = get_user_ns(user_ns);
	ns->ucounts = ucounts;
	ns->pid_allocated = PIDNS_ADDING;

	वापस ns;

out_मुक्त_idr:
	idr_destroy(&ns->idr);
	kmem_cache_मुक्त(pid_ns_cachep, ns);
out_dec:
	dec_pid_namespaces(ucounts);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम delayed_मुक्त_pidns(काष्ठा rcu_head *p)
अणु
	काष्ठा pid_namespace *ns = container_of(p, काष्ठा pid_namespace, rcu);

	dec_pid_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);

	kmem_cache_मुक्त(pid_ns_cachep, ns);
पूर्ण

अटल व्योम destroy_pid_namespace(काष्ठा pid_namespace *ns)
अणु
	ns_मुक्त_inum(&ns->ns);

	idr_destroy(&ns->idr);
	call_rcu(&ns->rcu, delayed_मुक्त_pidns);
पूर्ण

काष्ठा pid_namespace *copy_pid_ns(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा pid_namespace *old_ns)
अणु
	अगर (!(flags & CLONE_NEWPID))
		वापस get_pid_ns(old_ns);
	अगर (task_active_pid_ns(current) != old_ns)
		वापस ERR_PTR(-EINVAL);
	वापस create_pid_namespace(user_ns, old_ns);
पूर्ण

व्योम put_pid_ns(काष्ठा pid_namespace *ns)
अणु
	काष्ठा pid_namespace *parent;

	जबतक (ns != &init_pid_ns) अणु
		parent = ns->parent;
		अगर (!refcount_dec_and_test(&ns->ns.count))
			अवरोध;
		destroy_pid_namespace(ns);
		ns = parent;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(put_pid_ns);

व्योम zap_pid_ns_processes(काष्ठा pid_namespace *pid_ns)
अणु
	पूर्णांक nr;
	पूर्णांक rc;
	काष्ठा task_काष्ठा *task, *me = current;
	पूर्णांक init_pids = thपढ़ो_group_leader(me) ? 1 : 2;
	काष्ठा pid *pid;

	/* Don't allow any more processes पूर्णांकo the pid namespace */
	disable_pid_allocation(pid_ns);

	/*
	 * Ignore SIGCHLD causing any terminated children to स्वतःreap.
	 * This speeds up the namespace shutकरोwn, plus see the comment
	 * below.
	 */
	spin_lock_irq(&me->sighand->siglock);
	me->sighand->action[SIGCHLD - 1].sa.sa_handler = संक_छोड़ो;
	spin_unlock_irq(&me->sighand->siglock);

	/*
	 * The last thपढ़ो in the cgroup-init thपढ़ो group is terminating.
	 * Find reमुख्यing pid_ts in the namespace, संकेत and रुको क्रम them
	 * to निकास.
	 *
	 * Note:  This संकेतs each thपढ़ोs in the namespace - even those that
	 * 	  beदीर्घ to the same thपढ़ो group, To aव्योम this, we would have
	 * 	  to walk the entire tasklist looking a processes in this
	 * 	  namespace, but that could be unnecessarily expensive अगर the
	 * 	  pid namespace has just a few processes. Or we need to
	 * 	  मुख्यtain a tasklist क्रम each pid namespace.
	 *
	 */
	rcu_पढ़ो_lock();
	पढ़ो_lock(&tasklist_lock);
	nr = 2;
	idr_क्रम_each_entry_जारी(&pid_ns->idr, pid, nr) अणु
		task = pid_task(pid, PIDTYPE_PID);
		अगर (task && !__fatal_संकेत_pending(task))
			group_send_sig_info(SIGKILL, SEND_SIG_PRIV, task, PIDTYPE_MAX);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
	rcu_पढ़ो_unlock();

	/*
	 * Reap the EXIT_ZOMBIE children we had beक्रमe we ignored SIGCHLD.
	 * kernel_रुको4() will also block until our children traced from the
	 * parent namespace are detached and become EXIT_DEAD.
	 */
	करो अणु
		clear_thपढ़ो_flag(TIF_SIGPENDING);
		rc = kernel_रुको4(-1, शून्य, __WALL, शून्य);
	पूर्ण जबतक (rc != -ECHILD);

	/*
	 * kernel_रुको4() misses EXIT_DEAD children, and EXIT_ZOMBIE
	 * process whose parents processes are outside of the pid
	 * namespace.  Such processes are created with setns()+विभाजन().
	 *
	 * If those EXIT_ZOMBIE processes are not reaped by their
	 * parents beक्रमe their parents निकास, they will be reparented
	 * to pid_ns->child_reaper.  Thus pidns->child_reaper needs to
	 * stay valid until they all go away.
	 *
	 * The code relies on the pid_ns->child_reaper ignoring
	 * SIGCHILD to cause those EXIT_ZOMBIE processes to be
	 * स्वतःreaped अगर reparented.
	 *
	 * Semantically it is also desirable to रुको क्रम EXIT_ZOMBIE
	 * processes beक्रमe allowing the child_reaper to be reaped, as
	 * that gives the invariant that when the init process of a
	 * pid namespace is reaped all of the processes in the pid
	 * namespace are gone.
	 *
	 * Once all of the other tasks are gone from the pid_namespace
	 * मुक्त_pid() will awaken this task.
	 */
	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (pid_ns->pid_allocated == init_pids)
			अवरोध;
		schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);

	अगर (pid_ns->reboot)
		current->संकेत->group_निकास_code = pid_ns->reboot;

	acct_निकास_ns(pid_ns);
	वापस;
पूर्ण

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
अटल पूर्णांक pid_ns_ctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा pid_namespace *pid_ns = task_active_pid_ns(current);
	काष्ठा ctl_table पंचांगp = *table;
	पूर्णांक ret, next;

	अगर (ग_लिखो && !checkpoपूर्णांक_restore_ns_capable(pid_ns->user_ns))
		वापस -EPERM;

	/*
	 * Writing directly to ns' last_pid field is OK, since this field
	 * is अस्थिर in a living namespace anyway and a code writing to
	 * it should synchronize its usage with बाह्यal means.
	 */

	next = idr_get_cursor(&pid_ns->idr) - 1;

	पंचांगp.data = &next;
	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (!ret && ग_लिखो)
		idr_set_cursor(&pid_ns->idr, next + 1);

	वापस ret;
पूर्ण

बाह्य पूर्णांक pid_max;
अटल काष्ठा ctl_table pid_ns_ctl_table[] = अणु
	अणु
		.procname = "ns_last_pid",
		.maxlen = माप(पूर्णांक),
		.mode = 0666, /* permissions are checked in the handler */
		.proc_handler = pid_ns_ctl_handler,
		.extra1 = SYSCTL_ZERO,
		.extra2 = &pid_max,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
अटल काष्ठा ctl_path kern_path[] = अणु अणु .procname = "kernel", पूर्ण, अणु पूर्ण पूर्ण;
#पूर्ण_अगर	/* CONFIG_CHECKPOINT_RESTORE */

पूर्णांक reboot_pid_ns(काष्ठा pid_namespace *pid_ns, पूर्णांक cmd)
अणु
	अगर (pid_ns == &init_pid_ns)
		वापस 0;

	चयन (cmd) अणु
	हाल LINUX_REBOOT_CMD_RESTART2:
	हाल LINUX_REBOOT_CMD_RESTART:
		pid_ns->reboot = SIGHUP;
		अवरोध;

	हाल LINUX_REBOOT_CMD_POWER_OFF:
	हाल LINUX_REBOOT_CMD_HALT:
		pid_ns->reboot = संक_विघ्न;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	पढ़ो_lock(&tasklist_lock);
	send_sig(SIGKILL, pid_ns->child_reaper, 1);
	पढ़ो_unlock(&tasklist_lock);

	करो_निकास(0);

	/* Not reached */
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा pid_namespace *to_pid_ns(काष्ठा ns_common *ns)
अणु
	वापस container_of(ns, काष्ठा pid_namespace, ns);
पूर्ण

अटल काष्ठा ns_common *pidns_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pid_namespace *ns;

	rcu_पढ़ो_lock();
	ns = task_active_pid_ns(task);
	अगर (ns)
		get_pid_ns(ns);
	rcu_पढ़ो_unlock();

	वापस ns ? &ns->ns : शून्य;
पूर्ण

अटल काष्ठा ns_common *pidns_क्रम_children_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pid_namespace *ns = शून्य;

	task_lock(task);
	अगर (task->nsproxy) अणु
		ns = task->nsproxy->pid_ns_क्रम_children;
		get_pid_ns(ns);
	पूर्ण
	task_unlock(task);

	अगर (ns) अणु
		पढ़ो_lock(&tasklist_lock);
		अगर (!ns->child_reaper) अणु
			put_pid_ns(ns);
			ns = शून्य;
		पूर्ण
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण

	वापस ns ? &ns->ns : शून्य;
पूर्ण

अटल व्योम pidns_put(काष्ठा ns_common *ns)
अणु
	put_pid_ns(to_pid_ns(ns));
पूर्ण

अटल पूर्णांक pidns_install(काष्ठा nsset *nsset, काष्ठा ns_common *ns)
अणु
	काष्ठा nsproxy *nsproxy = nsset->nsproxy;
	काष्ठा pid_namespace *active = task_active_pid_ns(current);
	काष्ठा pid_namespace *ancestor, *new = to_pid_ns(ns);

	अगर (!ns_capable(new->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(nsset->cred->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	/*
	 * Only allow entering the current active pid namespace
	 * or a child of the current active pid namespace.
	 *
	 * This is required क्रम विभाजन to वापस a usable pid value and
	 * this मुख्यtains the property that processes and their
	 * children can not escape their current pid namespace.
	 */
	अगर (new->level < active->level)
		वापस -EINVAL;

	ancestor = new;
	जबतक (ancestor->level > active->level)
		ancestor = ancestor->parent;
	अगर (ancestor != active)
		वापस -EINVAL;

	put_pid_ns(nsproxy->pid_ns_क्रम_children);
	nsproxy->pid_ns_क्रम_children = get_pid_ns(new);
	वापस 0;
पूर्ण

अटल काष्ठा ns_common *pidns_get_parent(काष्ठा ns_common *ns)
अणु
	काष्ठा pid_namespace *active = task_active_pid_ns(current);
	काष्ठा pid_namespace *pid_ns, *p;

	/* See अगर the parent is in the current namespace */
	pid_ns = p = to_pid_ns(ns)->parent;
	क्रम (;;) अणु
		अगर (!p)
			वापस ERR_PTR(-EPERM);
		अगर (p == active)
			अवरोध;
		p = p->parent;
	पूर्ण

	वापस &get_pid_ns(pid_ns)->ns;
पूर्ण

अटल काष्ठा user_namespace *pidns_owner(काष्ठा ns_common *ns)
अणु
	वापस to_pid_ns(ns)->user_ns;
पूर्ण

स्थिर काष्ठा proc_ns_operations pidns_operations = अणु
	.name		= "pid",
	.type		= CLONE_NEWPID,
	.get		= pidns_get,
	.put		= pidns_put,
	.install	= pidns_install,
	.owner		= pidns_owner,
	.get_parent	= pidns_get_parent,
पूर्ण;

स्थिर काष्ठा proc_ns_operations pidns_क्रम_children_operations = अणु
	.name		= "pid_for_children",
	.real_ns_name	= "pid",
	.type		= CLONE_NEWPID,
	.get		= pidns_क्रम_children_get,
	.put		= pidns_put,
	.install	= pidns_install,
	.owner		= pidns_owner,
	.get_parent	= pidns_get_parent,
पूर्ण;

अटल __init पूर्णांक pid_namespaces_init(व्योम)
अणु
	pid_ns_cachep = KMEM_CACHE(pid_namespace, SLAB_PANIC);

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	रेजिस्टर_sysctl_paths(kern_path, pid_ns_ctl_table);
#पूर्ण_अगर
	वापस 0;
पूर्ण

__initcall(pid_namespaces_init);
