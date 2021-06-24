<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2006 IBM Corporation
 *
 *  Author: Serge Hallyn <serue@us.ibm.com>
 *
 *  Jun 2006 - namespaces support
 *             OpenVZ, SWsoft Inc.
 *             Pavel Emelianov <xemul@खोलोvz.org>
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/init_task.h>
#समावेश <linux/mnt_namespace.h>
#समावेश <linux/utsname.h>
#समावेश <linux/pid_namespace.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/समय_namespace.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/file.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/perf_event.h>

अटल काष्ठा kmem_cache *nsproxy_cachep;

काष्ठा nsproxy init_nsproxy = अणु
	.count			= ATOMIC_INIT(1),
	.uts_ns			= &init_uts_ns,
#अगर defined(CONFIG_POSIX_MQUEUE) || defined(CONFIG_SYSVIPC)
	.ipc_ns			= &init_ipc_ns,
#पूर्ण_अगर
	.mnt_ns			= शून्य,
	.pid_ns_क्रम_children	= &init_pid_ns,
#अगर_घोषित CONFIG_NET
	.net_ns			= &init_net,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUPS
	.cgroup_ns		= &init_cgroup_ns,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TIME_NS
	.समय_ns		= &init_समय_ns,
	.समय_ns_क्रम_children	= &init_समय_ns,
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा nsproxy *create_nsproxy(व्योम)
अणु
	काष्ठा nsproxy *nsproxy;

	nsproxy = kmem_cache_alloc(nsproxy_cachep, GFP_KERNEL);
	अगर (nsproxy)
		atomic_set(&nsproxy->count, 1);
	वापस nsproxy;
पूर्ण

/*
 * Create new nsproxy and all of its the associated namespaces.
 * Return the newly created nsproxy.  Do not attach this to the task,
 * leave it to the caller to करो proper locking and attach it to task.
 */
अटल काष्ठा nsproxy *create_new_namespaces(अचिन्हित दीर्घ flags,
	काष्ठा task_काष्ठा *tsk, काष्ठा user_namespace *user_ns,
	काष्ठा fs_काष्ठा *new_fs)
अणु
	काष्ठा nsproxy *new_nsp;
	पूर्णांक err;

	new_nsp = create_nsproxy();
	अगर (!new_nsp)
		वापस ERR_PTR(-ENOMEM);

	new_nsp->mnt_ns = copy_mnt_ns(flags, tsk->nsproxy->mnt_ns, user_ns, new_fs);
	अगर (IS_ERR(new_nsp->mnt_ns)) अणु
		err = PTR_ERR(new_nsp->mnt_ns);
		जाओ out_ns;
	पूर्ण

	new_nsp->uts_ns = copy_utsname(flags, user_ns, tsk->nsproxy->uts_ns);
	अगर (IS_ERR(new_nsp->uts_ns)) अणु
		err = PTR_ERR(new_nsp->uts_ns);
		जाओ out_uts;
	पूर्ण

	new_nsp->ipc_ns = copy_ipcs(flags, user_ns, tsk->nsproxy->ipc_ns);
	अगर (IS_ERR(new_nsp->ipc_ns)) अणु
		err = PTR_ERR(new_nsp->ipc_ns);
		जाओ out_ipc;
	पूर्ण

	new_nsp->pid_ns_क्रम_children =
		copy_pid_ns(flags, user_ns, tsk->nsproxy->pid_ns_क्रम_children);
	अगर (IS_ERR(new_nsp->pid_ns_क्रम_children)) अणु
		err = PTR_ERR(new_nsp->pid_ns_क्रम_children);
		जाओ out_pid;
	पूर्ण

	new_nsp->cgroup_ns = copy_cgroup_ns(flags, user_ns,
					    tsk->nsproxy->cgroup_ns);
	अगर (IS_ERR(new_nsp->cgroup_ns)) अणु
		err = PTR_ERR(new_nsp->cgroup_ns);
		जाओ out_cgroup;
	पूर्ण

	new_nsp->net_ns = copy_net_ns(flags, user_ns, tsk->nsproxy->net_ns);
	अगर (IS_ERR(new_nsp->net_ns)) अणु
		err = PTR_ERR(new_nsp->net_ns);
		जाओ out_net;
	पूर्ण

	new_nsp->समय_ns_क्रम_children = copy_समय_ns(flags, user_ns,
					tsk->nsproxy->समय_ns_क्रम_children);
	अगर (IS_ERR(new_nsp->समय_ns_क्रम_children)) अणु
		err = PTR_ERR(new_nsp->समय_ns_क्रम_children);
		जाओ out_समय;
	पूर्ण
	new_nsp->समय_ns = get_समय_ns(tsk->nsproxy->समय_ns);

	वापस new_nsp;

out_समय:
	put_net(new_nsp->net_ns);
out_net:
	put_cgroup_ns(new_nsp->cgroup_ns);
out_cgroup:
	अगर (new_nsp->pid_ns_क्रम_children)
		put_pid_ns(new_nsp->pid_ns_क्रम_children);
out_pid:
	अगर (new_nsp->ipc_ns)
		put_ipc_ns(new_nsp->ipc_ns);
out_ipc:
	अगर (new_nsp->uts_ns)
		put_uts_ns(new_nsp->uts_ns);
out_uts:
	अगर (new_nsp->mnt_ns)
		put_mnt_ns(new_nsp->mnt_ns);
out_ns:
	kmem_cache_मुक्त(nsproxy_cachep, new_nsp);
	वापस ERR_PTR(err);
पूर्ण

/*
 * called from clone.  This now handles copy क्रम nsproxy and all
 * namespaces therein.
 */
पूर्णांक copy_namespaces(अचिन्हित दीर्घ flags, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा nsproxy *old_ns = tsk->nsproxy;
	काष्ठा user_namespace *user_ns = task_cred_xxx(tsk, user_ns);
	काष्ठा nsproxy *new_ns;

	अगर (likely(!(flags & (CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWIPC |
			      CLONE_NEWPID | CLONE_NEWNET |
			      CLONE_NEWCGROUP | CLONE_NEWTIME)))) अणु
		अगर (likely(old_ns->समय_ns_क्रम_children == old_ns->समय_ns)) अणु
			get_nsproxy(old_ns);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!ns_capable(user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	/*
	 * CLONE_NEWIPC must detach from the unकरोlist: after चयनing
	 * to a new ipc namespace, the semaphore arrays from the old
	 * namespace are unreachable.  In clone parlance, CLONE_SYSVSEM
	 * means share unकरोlist with parent, so we must क्रमbid using
	 * it aदीर्घ with CLONE_NEWIPC.
	 */
	अगर ((flags & (CLONE_NEWIPC | CLONE_SYSVSEM)) ==
		(CLONE_NEWIPC | CLONE_SYSVSEM))
		वापस -EINVAL;

	new_ns = create_new_namespaces(flags, tsk, user_ns, tsk->fs);
	अगर (IS_ERR(new_ns))
		वापस  PTR_ERR(new_ns);

	समयns_on_विभाजन(new_ns, tsk);

	tsk->nsproxy = new_ns;
	वापस 0;
पूर्ण

व्योम मुक्त_nsproxy(काष्ठा nsproxy *ns)
अणु
	अगर (ns->mnt_ns)
		put_mnt_ns(ns->mnt_ns);
	अगर (ns->uts_ns)
		put_uts_ns(ns->uts_ns);
	अगर (ns->ipc_ns)
		put_ipc_ns(ns->ipc_ns);
	अगर (ns->pid_ns_क्रम_children)
		put_pid_ns(ns->pid_ns_क्रम_children);
	अगर (ns->समय_ns)
		put_समय_ns(ns->समय_ns);
	अगर (ns->समय_ns_क्रम_children)
		put_समय_ns(ns->समय_ns_क्रम_children);
	put_cgroup_ns(ns->cgroup_ns);
	put_net(ns->net_ns);
	kmem_cache_मुक्त(nsproxy_cachep, ns);
पूर्ण

/*
 * Called from unshare. Unshare all the namespaces part of nsproxy.
 * On success, वापसs the new nsproxy.
 */
पूर्णांक unshare_nsproxy_namespaces(अचिन्हित दीर्घ unshare_flags,
	काष्ठा nsproxy **new_nsp, काष्ठा cred *new_cred, काष्ठा fs_काष्ठा *new_fs)
अणु
	काष्ठा user_namespace *user_ns;
	पूर्णांक err = 0;

	अगर (!(unshare_flags & (CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWIPC |
			       CLONE_NEWNET | CLONE_NEWPID | CLONE_NEWCGROUP |
			       CLONE_NEWTIME)))
		वापस 0;

	user_ns = new_cred ? new_cred->user_ns : current_user_ns();
	अगर (!ns_capable(user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	*new_nsp = create_new_namespaces(unshare_flags, current, user_ns,
					 new_fs ? new_fs : current->fs);
	अगर (IS_ERR(*new_nsp)) अणु
		err = PTR_ERR(*new_nsp);
		जाओ out;
	पूर्ण

out:
	वापस err;
पूर्ण

व्योम चयन_task_namespaces(काष्ठा task_काष्ठा *p, काष्ठा nsproxy *new)
अणु
	काष्ठा nsproxy *ns;

	might_sleep();

	task_lock(p);
	ns = p->nsproxy;
	p->nsproxy = new;
	task_unlock(p);

	अगर (ns)
		put_nsproxy(ns);
पूर्ण

व्योम निकास_task_namespaces(काष्ठा task_काष्ठा *p)
अणु
	चयन_task_namespaces(p, शून्य);
पूर्ण

अटल पूर्णांक check_setns_flags(अचिन्हित दीर्घ flags)
अणु
	अगर (!flags || (flags & ~(CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWIPC |
				 CLONE_NEWNET | CLONE_NEWTIME | CLONE_NEWUSER |
				 CLONE_NEWPID | CLONE_NEWCGROUP)))
		वापस -EINVAL;

#अगर_अघोषित CONFIG_USER_NS
	अगर (flags & CLONE_NEWUSER)
		वापस -EINVAL;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_PID_NS
	अगर (flags & CLONE_NEWPID)
		वापस -EINVAL;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_UTS_NS
	अगर (flags & CLONE_NEWUTS)
		वापस -EINVAL;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_IPC_NS
	अगर (flags & CLONE_NEWIPC)
		वापस -EINVAL;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_CGROUPS
	अगर (flags & CLONE_NEWCGROUP)
		वापस -EINVAL;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_NET_NS
	अगर (flags & CLONE_NEWNET)
		वापस -EINVAL;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_TIME_NS
	अगर (flags & CLONE_NEWTIME)
		वापस -EINVAL;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम put_nsset(काष्ठा nsset *nsset)
अणु
	अचिन्हित flags = nsset->flags;

	अगर (flags & CLONE_NEWUSER)
		put_cred(nsset_cred(nsset));
	/*
	 * We only created a temporary copy अगर we attached to more than just
	 * the mount namespace.
	 */
	अगर (nsset->fs && (flags & CLONE_NEWNS) && (flags & ~CLONE_NEWNS))
		मुक्त_fs_काष्ठा(nsset->fs);
	अगर (nsset->nsproxy)
		मुक्त_nsproxy(nsset->nsproxy);
पूर्ण

अटल पूर्णांक prepare_nsset(अचिन्हित flags, काष्ठा nsset *nsset)
अणु
	काष्ठा task_काष्ठा *me = current;

	nsset->nsproxy = create_new_namespaces(0, me, current_user_ns(), me->fs);
	अगर (IS_ERR(nsset->nsproxy))
		वापस PTR_ERR(nsset->nsproxy);

	अगर (flags & CLONE_NEWUSER)
		nsset->cred = prepare_creds();
	अन्यथा
		nsset->cred = current_cred();
	अगर (!nsset->cred)
		जाओ out;

	/* Only create a temporary copy of fs_काष्ठा अगर we really need to. */
	अगर (flags == CLONE_NEWNS) अणु
		nsset->fs = me->fs;
	पूर्ण अन्यथा अगर (flags & CLONE_NEWNS) अणु
		nsset->fs = copy_fs_काष्ठा(me->fs);
		अगर (!nsset->fs)
			जाओ out;
	पूर्ण

	nsset->flags = flags;
	वापस 0;

out:
	put_nsset(nsset);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत पूर्णांक validate_ns(काष्ठा nsset *nsset, काष्ठा ns_common *ns)
अणु
	वापस ns->ops->install(nsset, ns);
पूर्ण

/*
 * This is the inverse operation to unshare().
 * Ordering is equivalent to the standard ordering used everywhere अन्यथा
 * during unshare and process creation. The चयन to the new set of
 * namespaces occurs at the poपूर्णांक of no वापस after installation of
 * all requested namespaces was successful in commit_nsset().
 */
अटल पूर्णांक validate_nsset(काष्ठा nsset *nsset, काष्ठा pid *pid)
अणु
	पूर्णांक ret = 0;
	अचिन्हित flags = nsset->flags;
	काष्ठा user_namespace *user_ns = शून्य;
	काष्ठा pid_namespace *pid_ns = शून्य;
	काष्ठा nsproxy *nsp;
	काष्ठा task_काष्ठा *tsk;

	/* Take a "snapshot" of the target task's namespaces. */
	rcu_पढ़ो_lock();
	tsk = pid_task(pid, PIDTYPE_PID);
	अगर (!tsk) अणु
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण

	अगर (!ptrace_may_access(tsk, PTRACE_MODE_READ_REALCREDS)) अणु
		rcu_पढ़ो_unlock();
		वापस -EPERM;
	पूर्ण

	task_lock(tsk);
	nsp = tsk->nsproxy;
	अगर (nsp)
		get_nsproxy(nsp);
	task_unlock(tsk);
	अगर (!nsp) अणु
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण

#अगर_घोषित CONFIG_PID_NS
	अगर (flags & CLONE_NEWPID) अणु
		pid_ns = task_active_pid_ns(tsk);
		अगर (unlikely(!pid_ns)) अणु
			rcu_पढ़ो_unlock();
			ret = -ESRCH;
			जाओ out;
		पूर्ण
		get_pid_ns(pid_ns);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_USER_NS
	अगर (flags & CLONE_NEWUSER)
		user_ns = get_user_ns(__task_cred(tsk)->user_ns);
#पूर्ण_अगर
	rcu_पढ़ो_unlock();

	/*
	 * Install requested namespaces. The caller will have
	 * verअगरied earlier that the requested namespaces are
	 * supported on this kernel. We करोn't report errors here
	 * अगर a namespace is requested that isn't supported.
	 */
#अगर_घोषित CONFIG_USER_NS
	अगर (flags & CLONE_NEWUSER) अणु
		ret = validate_ns(nsset, &user_ns->ns);
		अगर (ret)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

	अगर (flags & CLONE_NEWNS) अणु
		ret = validate_ns(nsset, from_mnt_ns(nsp->mnt_ns));
		अगर (ret)
			जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_UTS_NS
	अगर (flags & CLONE_NEWUTS) अणु
		ret = validate_ns(nsset, &nsp->uts_ns->ns);
		अगर (ret)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPC_NS
	अगर (flags & CLONE_NEWIPC) अणु
		ret = validate_ns(nsset, &nsp->ipc_ns->ns);
		अगर (ret)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PID_NS
	अगर (flags & CLONE_NEWPID) अणु
		ret = validate_ns(nsset, &pid_ns->ns);
		अगर (ret)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CGROUPS
	अगर (flags & CLONE_NEWCGROUP) अणु
		ret = validate_ns(nsset, &nsp->cgroup_ns->ns);
		अगर (ret)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_NS
	अगर (flags & CLONE_NEWNET) अणु
		ret = validate_ns(nsset, &nsp->net_ns->ns);
		अगर (ret)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TIME_NS
	अगर (flags & CLONE_NEWTIME) अणु
		ret = validate_ns(nsset, &nsp->समय_ns->ns);
		अगर (ret)
			जाओ out;
	पूर्ण
#पूर्ण_अगर

out:
	अगर (pid_ns)
		put_pid_ns(pid_ns);
	अगर (nsp)
		put_nsproxy(nsp);
	put_user_ns(user_ns);

	वापस ret;
पूर्ण

/*
 * This is the poपूर्णांक of no वापस. There are just a few namespaces
 * that करो some actual work here and it's sufficiently minimal that
 * a separate ns_common operation seems unnecessary क्रम now.
 * Unshare is करोing the same thing. If we'll end up needing to करो
 * more in a given namespace or a helper here is ultimately not
 * exported anymore a simple commit handler क्रम each namespace
 * should be added to ns_common.
 */
अटल व्योम commit_nsset(काष्ठा nsset *nsset)
अणु
	अचिन्हित flags = nsset->flags;
	काष्ठा task_काष्ठा *me = current;

#अगर_घोषित CONFIG_USER_NS
	अगर (flags & CLONE_NEWUSER) अणु
		/* transfer ownership */
		commit_creds(nsset_cred(nsset));
		nsset->cred = शून्य;
	पूर्ण
#पूर्ण_अगर

	/* We only need to commit अगर we have used a temporary fs_काष्ठा. */
	अगर ((flags & CLONE_NEWNS) && (flags & ~CLONE_NEWNS)) अणु
		set_fs_root(me->fs, &nsset->fs->root);
		set_fs_pwd(me->fs, &nsset->fs->pwd);
	पूर्ण

#अगर_घोषित CONFIG_IPC_NS
	अगर (flags & CLONE_NEWIPC)
		निकास_sem(me);
#पूर्ण_अगर

#अगर_घोषित CONFIG_TIME_NS
	अगर (flags & CLONE_NEWTIME)
		समयns_commit(me, nsset->nsproxy->समय_ns);
#पूर्ण_अगर

	/* transfer ownership */
	चयन_task_namespaces(me, nsset->nsproxy);
	nsset->nsproxy = शून्य;
पूर्ण

SYSCALL_DEFINE2(setns, पूर्णांक, fd, पूर्णांक, flags)
अणु
	काष्ठा file *file;
	काष्ठा ns_common *ns = शून्य;
	काष्ठा nsset nsset = अणुपूर्ण;
	पूर्णांक err = 0;

	file = fget(fd);
	अगर (!file)
		वापस -EBADF;

	अगर (proc_ns_file(file)) अणु
		ns = get_proc_ns(file_inode(file));
		अगर (flags && (ns->ops->type != flags))
			err = -EINVAL;
		flags = ns->ops->type;
	पूर्ण अन्यथा अगर (!IS_ERR(pidfd_pid(file))) अणु
		err = check_setns_flags(flags);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण
	अगर (err)
		जाओ out;

	err = prepare_nsset(flags, &nsset);
	अगर (err)
		जाओ out;

	अगर (proc_ns_file(file))
		err = validate_ns(&nsset, ns);
	अन्यथा
		err = validate_nsset(&nsset, file->निजी_data);
	अगर (!err) अणु
		commit_nsset(&nsset);
		perf_event_namespaces(current);
	पूर्ण
	put_nsset(&nsset);
out:
	fput(file);
	वापस err;
पूर्ण

पूर्णांक __init nsproxy_cache_init(व्योम)
अणु
	nsproxy_cachep = KMEM_CACHE(nsproxy, SLAB_PANIC);
	वापस 0;
पूर्ण
