<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NSPROXY_H
#घोषणा _LINUX_NSPROXY_H

#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>

काष्ठा mnt_namespace;
काष्ठा uts_namespace;
काष्ठा ipc_namespace;
काष्ठा pid_namespace;
काष्ठा cgroup_namespace;
काष्ठा fs_काष्ठा;

/*
 * A काष्ठाure to contain poपूर्णांकers to all per-process
 * namespaces - fs (mount), uts, network, sysvipc, etc.
 *
 * The pid namespace is an exception -- it's accessed using
 * task_active_pid_ns.  The pid namespace here is the
 * namespace that children will use.
 *
 * 'count' is the number of tasks holding a reference.
 * The count क्रम each namespace, then, will be the number
 * of nsproxies poपूर्णांकing to it, not the number of tasks.
 *
 * The nsproxy is shared by tasks which share all namespaces.
 * As soon as a single namespace is cloned or unshared, the
 * nsproxy is copied.
 */
काष्ठा nsproxy अणु
	atomic_t count;
	काष्ठा uts_namespace *uts_ns;
	काष्ठा ipc_namespace *ipc_ns;
	काष्ठा mnt_namespace *mnt_ns;
	काष्ठा pid_namespace *pid_ns_क्रम_children;
	काष्ठा net 	     *net_ns;
	काष्ठा समय_namespace *समय_ns;
	काष्ठा समय_namespace *समय_ns_क्रम_children;
	काष्ठा cgroup_namespace *cgroup_ns;
पूर्ण;
बाह्य काष्ठा nsproxy init_nsproxy;

/*
 * A काष्ठाure to encompass all bits needed to install
 * a partial or complete new set of namespaces.
 *
 * If a new user namespace is requested cred will
 * poपूर्णांक to a modअगरiable set of credentials. If a poपूर्णांकer
 * to a modअगरiable set is needed nsset_cred() must be
 * used and tested.
 */
काष्ठा nsset अणु
	अचिन्हित flags;
	काष्ठा nsproxy *nsproxy;
	काष्ठा fs_काष्ठा *fs;
	स्थिर काष्ठा cred *cred;
पूर्ण;

अटल अंतरभूत काष्ठा cred *nsset_cred(काष्ठा nsset *set)
अणु
	अगर (set->flags & CLONE_NEWUSER)
		वापस (काष्ठा cred *)set->cred;

	वापस शून्य;
पूर्ण

/*
 * the namespaces access rules are:
 *
 *  1. only current task is allowed to change tsk->nsproxy poपूर्णांकer or
 *     any poपूर्णांकer on the nsproxy itself.  Current must hold the task_lock
 *     when changing tsk->nsproxy.
 *
 *  2. when accessing (i.e. पढ़ोing) current task's namespaces - no
 *     precautions should be taken - just dereference the poपूर्णांकers
 *
 *  3. the access to other task namespaces is perक्रमmed like this
 *     task_lock(task);
 *     nsproxy = task->nsproxy;
 *     अगर (nsproxy != शून्य) अणु
 *             / *
 *               * work with the namespaces here
 *               * e.g. get the reference on one of them
 *               * /
 *     पूर्ण / *
 *         * शून्य task->nsproxy means that this task is
 *         * almost dead (zombie)
 *         * /
 *     task_unlock(task);
 *
 */

पूर्णांक copy_namespaces(अचिन्हित दीर्घ flags, काष्ठा task_काष्ठा *tsk);
व्योम निकास_task_namespaces(काष्ठा task_काष्ठा *tsk);
व्योम चयन_task_namespaces(काष्ठा task_काष्ठा *tsk, काष्ठा nsproxy *new);
व्योम मुक्त_nsproxy(काष्ठा nsproxy *ns);
पूर्णांक unshare_nsproxy_namespaces(अचिन्हित दीर्घ, काष्ठा nsproxy **,
	काष्ठा cred *, काष्ठा fs_काष्ठा *);
पूर्णांक __init nsproxy_cache_init(व्योम);

अटल अंतरभूत व्योम put_nsproxy(काष्ठा nsproxy *ns)
अणु
	अगर (atomic_dec_and_test(&ns->count)) अणु
		मुक्त_nsproxy(ns);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम get_nsproxy(काष्ठा nsproxy *ns)
अणु
	atomic_inc(&ns->count);
पूर्ण

#पूर्ण_अगर
