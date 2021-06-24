<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/ipc/namespace.c
 * Copyright (C) 2006 Pavel Emelyanov <xemul@खोलोvz.org> OpenVZ, SWsoft Inc.
 */

#समावेश <linux/ipc.h>
#समावेश <linux/msg.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/sched/task.h>

#समावेश "util.h"

अटल काष्ठा ucounts *inc_ipc_namespaces(काष्ठा user_namespace *ns)
अणु
	वापस inc_ucount(ns, current_euid(), UCOUNT_IPC_NAMESPACES);
पूर्ण

अटल व्योम dec_ipc_namespaces(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_IPC_NAMESPACES);
पूर्ण

अटल काष्ठा ipc_namespace *create_ipc_ns(काष्ठा user_namespace *user_ns,
					   काष्ठा ipc_namespace *old_ns)
अणु
	काष्ठा ipc_namespace *ns;
	काष्ठा ucounts *ucounts;
	पूर्णांक err;

	err = -ENOSPC;
	ucounts = inc_ipc_namespaces(user_ns);
	अगर (!ucounts)
		जाओ fail;

	err = -ENOMEM;
	ns = kzalloc(माप(काष्ठा ipc_namespace), GFP_KERNEL);
	अगर (ns == शून्य)
		जाओ fail_dec;

	err = ns_alloc_inum(&ns->ns);
	अगर (err)
		जाओ fail_मुक्त;
	ns->ns.ops = &ipcns_operations;

	refcount_set(&ns->ns.count, 1);
	ns->user_ns = get_user_ns(user_ns);
	ns->ucounts = ucounts;

	err = mq_init_ns(ns);
	अगर (err)
		जाओ fail_put;

	sem_init_ns(ns);
	msg_init_ns(ns);
	shm_init_ns(ns);

	वापस ns;

fail_put:
	put_user_ns(ns->user_ns);
	ns_मुक्त_inum(&ns->ns);
fail_मुक्त:
	kमुक्त(ns);
fail_dec:
	dec_ipc_namespaces(ucounts);
fail:
	वापस ERR_PTR(err);
पूर्ण

काष्ठा ipc_namespace *copy_ipcs(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा ipc_namespace *ns)
अणु
	अगर (!(flags & CLONE_NEWIPC))
		वापस get_ipc_ns(ns);
	वापस create_ipc_ns(user_ns, ns);
पूर्ण

/*
 * मुक्त_ipcs - मुक्त all ipcs of one type
 * @ns:   the namespace to हटाओ the ipcs from
 * @ids:  the table of ipcs to मुक्त
 * @मुक्त: the function called to मुक्त each inभागidual ipc
 *
 * Called क्रम each kind of ipc when an ipc_namespace निकासs.
 */
व्योम मुक्त_ipcs(काष्ठा ipc_namespace *ns, काष्ठा ipc_ids *ids,
	       व्योम (*मुक्त)(काष्ठा ipc_namespace *, काष्ठा kern_ipc_perm *))
अणु
	काष्ठा kern_ipc_perm *perm;
	पूर्णांक next_id;
	पूर्णांक total, in_use;

	करोwn_ग_लिखो(&ids->rwsem);

	in_use = ids->in_use;

	क्रम (total = 0, next_id = 0; total < in_use; next_id++) अणु
		perm = idr_find(&ids->ipcs_idr, next_id);
		अगर (perm == शून्य)
			जारी;
		rcu_पढ़ो_lock();
		ipc_lock_object(perm);
		मुक्त(ns, perm);
		total++;
	पूर्ण
	up_ग_लिखो(&ids->rwsem);
पूर्ण

अटल व्योम मुक्त_ipc_ns(काष्ठा ipc_namespace *ns)
अणु
	/* mq_put_mnt() रुकोs क्रम a grace period as kern_unmount()
	 * uses synchronize_rcu().
	 */
	mq_put_mnt(ns);
	sem_निकास_ns(ns);
	msg_निकास_ns(ns);
	shm_निकास_ns(ns);

	dec_ipc_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);
	ns_मुक्त_inum(&ns->ns);
	kमुक्त(ns);
पूर्ण

अटल LLIST_HEAD(मुक्त_ipc_list);
अटल व्योम मुक्त_ipc(काष्ठा work_काष्ठा *unused)
अणु
	काष्ठा llist_node *node = llist_del_all(&मुक्त_ipc_list);
	काष्ठा ipc_namespace *n, *t;

	llist_क्रम_each_entry_safe(n, t, node, mnt_llist)
		मुक्त_ipc_ns(n);
पूर्ण

/*
 * The work queue is used to aव्योम the cost of synchronize_rcu in kern_unmount.
 */
अटल DECLARE_WORK(मुक्त_ipc_work, मुक्त_ipc);

/*
 * put_ipc_ns - drop a reference to an ipc namespace.
 * @ns: the namespace to put
 *
 * If this is the last task in the namespace निकासing, and
 * it is dropping the refcount to 0, then it can race with
 * a task in another ipc namespace but in a mounts namespace
 * which has this ipcns's mqueuefs mounted, करोing some action
 * with one of the mqueuefs files.  That can उठाओ the refcount.
 * So dropping the refcount, and raising the refcount when
 * accessing it through the VFS, are रक्षित with mq_lock.
 *
 * (Clearly, a task raising the refcount on its own ipc_ns
 * needn't take mq_lock since it can't race with the last task
 * in the ipcns निकासing).
 */
व्योम put_ipc_ns(काष्ठा ipc_namespace *ns)
अणु
	अगर (refcount_dec_and_lock(&ns->ns.count, &mq_lock)) अणु
		mq_clear_sbinfo(ns);
		spin_unlock(&mq_lock);

		अगर (llist_add(&ns->mnt_llist, &मुक्त_ipc_list))
			schedule_work(&मुक्त_ipc_work);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा ipc_namespace *to_ipc_ns(काष्ठा ns_common *ns)
अणु
	वापस container_of(ns, काष्ठा ipc_namespace, ns);
पूर्ण

अटल काष्ठा ns_common *ipcns_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा ipc_namespace *ns = शून्य;
	काष्ठा nsproxy *nsproxy;

	task_lock(task);
	nsproxy = task->nsproxy;
	अगर (nsproxy)
		ns = get_ipc_ns(nsproxy->ipc_ns);
	task_unlock(task);

	वापस ns ? &ns->ns : शून्य;
पूर्ण

अटल व्योम ipcns_put(काष्ठा ns_common *ns)
अणु
	वापस put_ipc_ns(to_ipc_ns(ns));
पूर्ण

अटल पूर्णांक ipcns_install(काष्ठा nsset *nsset, काष्ठा ns_common *new)
अणु
	काष्ठा nsproxy *nsproxy = nsset->nsproxy;
	काष्ठा ipc_namespace *ns = to_ipc_ns(new);
	अगर (!ns_capable(ns->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(nsset->cred->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	put_ipc_ns(nsproxy->ipc_ns);
	nsproxy->ipc_ns = get_ipc_ns(ns);
	वापस 0;
पूर्ण

अटल काष्ठा user_namespace *ipcns_owner(काष्ठा ns_common *ns)
अणु
	वापस to_ipc_ns(ns)->user_ns;
पूर्ण

स्थिर काष्ठा proc_ns_operations ipcns_operations = अणु
	.name		= "ipc",
	.type		= CLONE_NEWIPC,
	.get		= ipcns_get,
	.put		= ipcns_put,
	.install	= ipcns_install,
	.owner		= ipcns_owner,
पूर्ण;
