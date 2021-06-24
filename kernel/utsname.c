<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2004 IBM Corporation
 *
 *  Author: Serge Hallyn <serue@us.ibm.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/uts.h>
#समावेश <linux/utsname.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/sched/task.h>

अटल काष्ठा kmem_cache *uts_ns_cache __ro_after_init;

अटल काष्ठा ucounts *inc_uts_namespaces(काष्ठा user_namespace *ns)
अणु
	वापस inc_ucount(ns, current_euid(), UCOUNT_UTS_NAMESPACES);
पूर्ण

अटल व्योम dec_uts_namespaces(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_UTS_NAMESPACES);
पूर्ण

अटल काष्ठा uts_namespace *create_uts_ns(व्योम)
अणु
	काष्ठा uts_namespace *uts_ns;

	uts_ns = kmem_cache_alloc(uts_ns_cache, GFP_KERNEL);
	अगर (uts_ns)
		refcount_set(&uts_ns->ns.count, 1);
	वापस uts_ns;
पूर्ण

/*
 * Clone a new ns copying an original utsname, setting refcount to 1
 * @old_ns: namespace to clone
 * Return ERR_PTR(-ENOMEM) on error (failure to allocate), new ns otherwise
 */
अटल काष्ठा uts_namespace *clone_uts_ns(काष्ठा user_namespace *user_ns,
					  काष्ठा uts_namespace *old_ns)
अणु
	काष्ठा uts_namespace *ns;
	काष्ठा ucounts *ucounts;
	पूर्णांक err;

	err = -ENOSPC;
	ucounts = inc_uts_namespaces(user_ns);
	अगर (!ucounts)
		जाओ fail;

	err = -ENOMEM;
	ns = create_uts_ns();
	अगर (!ns)
		जाओ fail_dec;

	err = ns_alloc_inum(&ns->ns);
	अगर (err)
		जाओ fail_मुक्त;

	ns->ucounts = ucounts;
	ns->ns.ops = &utsns_operations;

	करोwn_पढ़ो(&uts_sem);
	स_नकल(&ns->name, &old_ns->name, माप(ns->name));
	ns->user_ns = get_user_ns(user_ns);
	up_पढ़ो(&uts_sem);
	वापस ns;

fail_मुक्त:
	kmem_cache_मुक्त(uts_ns_cache, ns);
fail_dec:
	dec_uts_namespaces(ucounts);
fail:
	वापस ERR_PTR(err);
पूर्ण

/*
 * Copy task tsk's utsname namespace, or clone it अगर flags
 * specअगरies CLONE_NEWUTS.  In latter हाल, changes to the
 * utsname of this process won't be seen by parent, and vice
 * versa.
 */
काष्ठा uts_namespace *copy_utsname(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा uts_namespace *old_ns)
अणु
	काष्ठा uts_namespace *new_ns;

	BUG_ON(!old_ns);
	get_uts_ns(old_ns);

	अगर (!(flags & CLONE_NEWUTS))
		वापस old_ns;

	new_ns = clone_uts_ns(user_ns, old_ns);

	put_uts_ns(old_ns);
	वापस new_ns;
पूर्ण

व्योम मुक्त_uts_ns(काष्ठा uts_namespace *ns)
अणु
	dec_uts_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);
	ns_मुक्त_inum(&ns->ns);
	kmem_cache_मुक्त(uts_ns_cache, ns);
पूर्ण

अटल अंतरभूत काष्ठा uts_namespace *to_uts_ns(काष्ठा ns_common *ns)
अणु
	वापस container_of(ns, काष्ठा uts_namespace, ns);
पूर्ण

अटल काष्ठा ns_common *utsns_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा uts_namespace *ns = शून्य;
	काष्ठा nsproxy *nsproxy;

	task_lock(task);
	nsproxy = task->nsproxy;
	अगर (nsproxy) अणु
		ns = nsproxy->uts_ns;
		get_uts_ns(ns);
	पूर्ण
	task_unlock(task);

	वापस ns ? &ns->ns : शून्य;
पूर्ण

अटल व्योम utsns_put(काष्ठा ns_common *ns)
अणु
	put_uts_ns(to_uts_ns(ns));
पूर्ण

अटल पूर्णांक utsns_install(काष्ठा nsset *nsset, काष्ठा ns_common *new)
अणु
	काष्ठा nsproxy *nsproxy = nsset->nsproxy;
	काष्ठा uts_namespace *ns = to_uts_ns(new);

	अगर (!ns_capable(ns->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(nsset->cred->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	get_uts_ns(ns);
	put_uts_ns(nsproxy->uts_ns);
	nsproxy->uts_ns = ns;
	वापस 0;
पूर्ण

अटल काष्ठा user_namespace *utsns_owner(काष्ठा ns_common *ns)
अणु
	वापस to_uts_ns(ns)->user_ns;
पूर्ण

स्थिर काष्ठा proc_ns_operations utsns_operations = अणु
	.name		= "uts",
	.type		= CLONE_NEWUTS,
	.get		= utsns_get,
	.put		= utsns_put,
	.install	= utsns_install,
	.owner		= utsns_owner,
पूर्ण;

व्योम __init uts_ns_init(व्योम)
अणु
	uts_ns_cache = kmem_cache_create_usercopy(
			"uts_namespace", माप(काष्ठा uts_namespace), 0,
			SLAB_PANIC|SLAB_ACCOUNT,
			दुरत्व(काष्ठा uts_namespace, name),
			माप_field(काष्ठा uts_namespace, name),
			शून्य);
पूर्ण
