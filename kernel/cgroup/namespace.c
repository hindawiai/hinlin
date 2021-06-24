<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "cgroup-internal.h"

#समावेश <linux/sched/task.h>
#समावेश <linux/slab.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/proc_ns.h>


/* cgroup namespaces */

अटल काष्ठा ucounts *inc_cgroup_namespaces(काष्ठा user_namespace *ns)
अणु
	वापस inc_ucount(ns, current_euid(), UCOUNT_CGROUP_NAMESPACES);
पूर्ण

अटल व्योम dec_cgroup_namespaces(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_CGROUP_NAMESPACES);
पूर्ण

अटल काष्ठा cgroup_namespace *alloc_cgroup_ns(व्योम)
अणु
	काष्ठा cgroup_namespace *new_ns;
	पूर्णांक ret;

	new_ns = kzalloc(माप(काष्ठा cgroup_namespace), GFP_KERNEL);
	अगर (!new_ns)
		वापस ERR_PTR(-ENOMEM);
	ret = ns_alloc_inum(&new_ns->ns);
	अगर (ret) अणु
		kमुक्त(new_ns);
		वापस ERR_PTR(ret);
	पूर्ण
	refcount_set(&new_ns->ns.count, 1);
	new_ns->ns.ops = &cgroupns_operations;
	वापस new_ns;
पूर्ण

व्योम मुक्त_cgroup_ns(काष्ठा cgroup_namespace *ns)
अणु
	put_css_set(ns->root_cset);
	dec_cgroup_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);
	ns_मुक्त_inum(&ns->ns);
	kमुक्त(ns);
पूर्ण
EXPORT_SYMBOL(मुक्त_cgroup_ns);

काष्ठा cgroup_namespace *copy_cgroup_ns(अचिन्हित दीर्घ flags,
					काष्ठा user_namespace *user_ns,
					काष्ठा cgroup_namespace *old_ns)
अणु
	काष्ठा cgroup_namespace *new_ns;
	काष्ठा ucounts *ucounts;
	काष्ठा css_set *cset;

	BUG_ON(!old_ns);

	अगर (!(flags & CLONE_NEWCGROUP)) अणु
		get_cgroup_ns(old_ns);
		वापस old_ns;
	पूर्ण

	/* Allow only sysadmin to create cgroup namespace. */
	अगर (!ns_capable(user_ns, CAP_SYS_ADMIN))
		वापस ERR_PTR(-EPERM);

	ucounts = inc_cgroup_namespaces(user_ns);
	अगर (!ucounts)
		वापस ERR_PTR(-ENOSPC);

	/* It is not safe to take cgroup_mutex here */
	spin_lock_irq(&css_set_lock);
	cset = task_css_set(current);
	get_css_set(cset);
	spin_unlock_irq(&css_set_lock);

	new_ns = alloc_cgroup_ns();
	अगर (IS_ERR(new_ns)) अणु
		put_css_set(cset);
		dec_cgroup_namespaces(ucounts);
		वापस new_ns;
	पूर्ण

	new_ns->user_ns = get_user_ns(user_ns);
	new_ns->ucounts = ucounts;
	new_ns->root_cset = cset;

	वापस new_ns;
पूर्ण

अटल अंतरभूत काष्ठा cgroup_namespace *to_cg_ns(काष्ठा ns_common *ns)
अणु
	वापस container_of(ns, काष्ठा cgroup_namespace, ns);
पूर्ण

अटल पूर्णांक cgroupns_install(काष्ठा nsset *nsset, काष्ठा ns_common *ns)
अणु
	काष्ठा nsproxy *nsproxy = nsset->nsproxy;
	काष्ठा cgroup_namespace *cgroup_ns = to_cg_ns(ns);

	अगर (!ns_capable(nsset->cred->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(cgroup_ns->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	/* Don't need to करो anything अगर we are attaching to our own cgroupns. */
	अगर (cgroup_ns == nsproxy->cgroup_ns)
		वापस 0;

	get_cgroup_ns(cgroup_ns);
	put_cgroup_ns(nsproxy->cgroup_ns);
	nsproxy->cgroup_ns = cgroup_ns;

	वापस 0;
पूर्ण

अटल काष्ठा ns_common *cgroupns_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cgroup_namespace *ns = शून्य;
	काष्ठा nsproxy *nsproxy;

	task_lock(task);
	nsproxy = task->nsproxy;
	अगर (nsproxy) अणु
		ns = nsproxy->cgroup_ns;
		get_cgroup_ns(ns);
	पूर्ण
	task_unlock(task);

	वापस ns ? &ns->ns : शून्य;
पूर्ण

अटल व्योम cgroupns_put(काष्ठा ns_common *ns)
अणु
	put_cgroup_ns(to_cg_ns(ns));
पूर्ण

अटल काष्ठा user_namespace *cgroupns_owner(काष्ठा ns_common *ns)
अणु
	वापस to_cg_ns(ns)->user_ns;
पूर्ण

स्थिर काष्ठा proc_ns_operations cgroupns_operations = अणु
	.name		= "cgroup",
	.type		= CLONE_NEWCGROUP,
	.get		= cgroupns_get,
	.put		= cgroupns_put,
	.install	= cgroupns_install,
	.owner		= cgroupns_owner,
पूर्ण;

अटल __init पूर्णांक cgroup_namespaces_init(व्योम)
अणु
	वापस 0;
पूर्ण
subsys_initcall(cgroup_namespaces_init);
