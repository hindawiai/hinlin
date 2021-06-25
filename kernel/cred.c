<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Task credentials management - see Documentation/security/credentials.rst
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#समावेश <linux/export.h>
#समावेश <linux/cred.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/key.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/init_task.h>
#समावेश <linux/security.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/cn_proc.h>
#समावेश <linux/uidgid.h>

#अगर 0
#घोषणा kdebug(FMT, ...)						\
	prपूर्णांकk("[%-5.5s%5u] " FMT "\n",					\
	       current->comm, current->pid, ##__VA_ARGS__)
#अन्यथा
#घोषणा kdebug(FMT, ...)						\
करो अणु									\
	अगर (0)								\
		no_prपूर्णांकk("[%-5.5s%5u] " FMT "\n",			\
			  current->comm, current->pid, ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#पूर्ण_अगर

अटल काष्ठा kmem_cache *cred_jar;

/* init to 2 - one क्रम init_task, one to ensure it is never मुक्तd */
अटल काष्ठा group_info init_groups = अणु .usage = ATOMIC_INIT(2) पूर्ण;

/*
 * The initial credentials क्रम the initial task
 */
काष्ठा cred init_cred = अणु
	.usage			= ATOMIC_INIT(4),
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	.subscribers		= ATOMIC_INIT(2),
	.magic			= CRED_MAGIC,
#पूर्ण_अगर
	.uid			= GLOBAL_ROOT_UID,
	.gid			= GLOBAL_ROOT_GID,
	.suid			= GLOBAL_ROOT_UID,
	.sgid			= GLOBAL_ROOT_GID,
	.euid			= GLOBAL_ROOT_UID,
	.egid			= GLOBAL_ROOT_GID,
	.fsuid			= GLOBAL_ROOT_UID,
	.fsgid			= GLOBAL_ROOT_GID,
	.securebits		= SECUREBITS_DEFAULT,
	.cap_inheritable	= CAP_EMPTY_SET,
	.cap_permitted		= CAP_FULL_SET,
	.cap_effective		= CAP_FULL_SET,
	.cap_bset		= CAP_FULL_SET,
	.user			= INIT_USER,
	.user_ns		= &init_user_ns,
	.group_info		= &init_groups,
पूर्ण;

अटल अंतरभूत व्योम set_cred_subscribers(काष्ठा cred *cred, पूर्णांक n)
अणु
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	atomic_set(&cred->subscribers, n);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_cred_subscribers(स्थिर काष्ठा cred *cred)
अणु
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	वापस atomic_पढ़ो(&cred->subscribers);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम alter_cred_subscribers(स्थिर काष्ठा cred *_cred, पूर्णांक n)
अणु
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	काष्ठा cred *cred = (काष्ठा cred *) _cred;

	atomic_add(n, &cred->subscribers);
#पूर्ण_अगर
पूर्ण

/*
 * The RCU callback to actually dispose of a set of credentials
 */
अटल व्योम put_cred_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा cred *cred = container_of(rcu, काष्ठा cred, rcu);

	kdebug("put_cred_rcu(%p)", cred);

#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	अगर (cred->magic != CRED_MAGIC_DEAD ||
	    atomic_पढ़ो(&cred->usage) != 0 ||
	    पढ़ो_cred_subscribers(cred) != 0)
		panic("CRED: put_cred_rcu() sees %p with"
		      " mag %x, put %p, usage %d, subscr %d\n",
		      cred, cred->magic, cred->put_addr,
		      atomic_पढ़ो(&cred->usage),
		      पढ़ो_cred_subscribers(cred));
#अन्यथा
	अगर (atomic_पढ़ो(&cred->usage) != 0)
		panic("CRED: put_cred_rcu() sees %p with usage %d\n",
		      cred, atomic_पढ़ो(&cred->usage));
#पूर्ण_अगर

	security_cred_मुक्त(cred);
	key_put(cred->session_keyring);
	key_put(cred->process_keyring);
	key_put(cred->thपढ़ो_keyring);
	key_put(cred->request_key_auth);
	अगर (cred->group_info)
		put_group_info(cred->group_info);
	मुक्त_uid(cred->user);
	put_user_ns(cred->user_ns);
	kmem_cache_मुक्त(cred_jar, cred);
पूर्ण

/**
 * __put_cred - Destroy a set of credentials
 * @cred: The record to release
 *
 * Destroy a set of credentials on which no references reमुख्य.
 */
व्योम __put_cred(काष्ठा cred *cred)
अणु
	kdebug("__put_cred(%p{%d,%d})", cred,
	       atomic_पढ़ो(&cred->usage),
	       पढ़ो_cred_subscribers(cred));

	BUG_ON(atomic_पढ़ो(&cred->usage) != 0);
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	BUG_ON(पढ़ो_cred_subscribers(cred) != 0);
	cred->magic = CRED_MAGIC_DEAD;
	cred->put_addr = __builtin_वापस_address(0);
#पूर्ण_अगर
	BUG_ON(cred == current->cred);
	BUG_ON(cred == current->real_cred);

	अगर (cred->non_rcu)
		put_cred_rcu(&cred->rcu);
	अन्यथा
		call_rcu(&cred->rcu, put_cred_rcu);
पूर्ण
EXPORT_SYMBOL(__put_cred);

/*
 * Clean up a task's credentials when it निकासs
 */
व्योम निकास_creds(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा cred *cred;

	kdebug("exit_creds(%u,%p,%p,{%d,%d})", tsk->pid, tsk->real_cred, tsk->cred,
	       atomic_पढ़ो(&tsk->cred->usage),
	       पढ़ो_cred_subscribers(tsk->cred));

	cred = (काष्ठा cred *) tsk->real_cred;
	tsk->real_cred = शून्य;
	validate_creds(cred);
	alter_cred_subscribers(cred, -1);
	put_cred(cred);

	cred = (काष्ठा cred *) tsk->cred;
	tsk->cred = शून्य;
	validate_creds(cred);
	alter_cred_subscribers(cred, -1);
	put_cred(cred);

#अगर_घोषित CONFIG_KEYS_REQUEST_CACHE
	key_put(tsk->cached_requested_key);
	tsk->cached_requested_key = शून्य;
#पूर्ण_अगर
पूर्ण

/**
 * get_task_cred - Get another task's objective credentials
 * @task: The task to query
 *
 * Get the objective credentials of a task, pinning them so that they can't go
 * away.  Accessing a task's credentials directly is not permitted.
 *
 * The caller must also make sure task करोesn't get deleted, either by holding a
 * ref on task or by holding tasklist_lock to prevent it from being unlinked.
 */
स्थिर काष्ठा cred *get_task_cred(काष्ठा task_काष्ठा *task)
अणु
	स्थिर काष्ठा cred *cred;

	rcu_पढ़ो_lock();

	करो अणु
		cred = __task_cred((task));
		BUG_ON(!cred);
	पूर्ण जबतक (!get_cred_rcu(cred));

	rcu_पढ़ो_unlock();
	वापस cred;
पूर्ण
EXPORT_SYMBOL(get_task_cred);

/*
 * Allocate blank credentials, such that the credentials can be filled in at a
 * later date without risk of ENOMEM.
 */
काष्ठा cred *cred_alloc_blank(व्योम)
अणु
	काष्ठा cred *new;

	new = kmem_cache_zalloc(cred_jar, GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	atomic_set(&new->usage, 1);
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	new->magic = CRED_MAGIC;
#पूर्ण_अगर

	अगर (security_cred_alloc_blank(new, GFP_KERNEL_ACCOUNT) < 0)
		जाओ error;

	वापस new;

error:
	पात_creds(new);
	वापस शून्य;
पूर्ण

/**
 * prepare_creds - Prepare a new set of credentials क्रम modअगरication
 *
 * Prepare a new set of task credentials क्रम modअगरication.  A task's creds
 * shouldn't generally be modअगरied directly, thereक्रमe this function is used to
 * prepare a new copy, which the caller then modअगरies and then commits by
 * calling commit_creds().
 *
 * Preparation involves making a copy of the objective creds क्रम modअगरication.
 *
 * Returns a poपूर्णांकer to the new creds-to-be अगर successful, शून्य otherwise.
 *
 * Call commit_creds() or पात_creds() to clean up.
 */
काष्ठा cred *prepare_creds(व्योम)
अणु
	काष्ठा task_काष्ठा *task = current;
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;

	validate_process_creds();

	new = kmem_cache_alloc(cred_jar, GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	kdebug("prepare_creds() alloc %p", new);

	old = task->cred;
	स_नकल(new, old, माप(काष्ठा cred));

	new->non_rcu = 0;
	atomic_set(&new->usage, 1);
	set_cred_subscribers(new, 0);
	get_group_info(new->group_info);
	get_uid(new->user);
	get_user_ns(new->user_ns);

#अगर_घोषित CONFIG_KEYS
	key_get(new->session_keyring);
	key_get(new->process_keyring);
	key_get(new->thपढ़ो_keyring);
	key_get(new->request_key_auth);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY
	new->security = शून्य;
#पूर्ण_अगर

	अगर (security_prepare_creds(new, old, GFP_KERNEL_ACCOUNT) < 0)
		जाओ error;
	validate_creds(new);
	वापस new;

error:
	पात_creds(new);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(prepare_creds);

/*
 * Prepare credentials क्रम current to perक्रमm an execve()
 * - The caller must hold ->cred_guard_mutex
 */
काष्ठा cred *prepare_exec_creds(व्योम)
अणु
	काष्ठा cred *new;

	new = prepare_creds();
	अगर (!new)
		वापस new;

#अगर_घोषित CONFIG_KEYS
	/* newly exec'd tasks don't get a thपढ़ो keyring */
	key_put(new->thपढ़ो_keyring);
	new->thपढ़ो_keyring = शून्य;

	/* inherit the session keyring; new process keyring */
	key_put(new->process_keyring);
	new->process_keyring = शून्य;
#पूर्ण_अगर

	new->suid = new->fsuid = new->euid;
	new->sgid = new->fsgid = new->egid;

	वापस new;
पूर्ण

/*
 * Copy credentials क्रम the new process created by विभाजन()
 *
 * We share अगर we can, but under some circumstances we have to generate a new
 * set.
 *
 * The new process माला_लो the current process's subjective credentials as its
 * objective and subjective credentials
 */
पूर्णांक copy_creds(काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ clone_flags)
अणु
	काष्ठा cred *new;
	पूर्णांक ret;

#अगर_घोषित CONFIG_KEYS_REQUEST_CACHE
	p->cached_requested_key = शून्य;
#पूर्ण_अगर

	अगर (
#अगर_घोषित CONFIG_KEYS
		!p->cred->thपढ़ो_keyring &&
#पूर्ण_अगर
		clone_flags & CLONE_THREAD
	    ) अणु
		p->real_cred = get_cred(p->cred);
		get_cred(p->cred);
		alter_cred_subscribers(p->cred, 2);
		kdebug("share_creds(%p{%d,%d})",
		       p->cred, atomic_पढ़ो(&p->cred->usage),
		       पढ़ो_cred_subscribers(p->cred));
		atomic_inc(&p->cred->user->processes);
		वापस 0;
	पूर्ण

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	अगर (clone_flags & CLONE_NEWUSER) अणु
		ret = create_user_ns(new);
		अगर (ret < 0)
			जाओ error_put;
	पूर्ण

#अगर_घोषित CONFIG_KEYS
	/* new thपढ़ोs get their own thपढ़ो keyrings अगर their parent alपढ़ोy
	 * had one */
	अगर (new->thपढ़ो_keyring) अणु
		key_put(new->thपढ़ो_keyring);
		new->thपढ़ो_keyring = शून्य;
		अगर (clone_flags & CLONE_THREAD)
			install_thपढ़ो_keyring_to_cred(new);
	पूर्ण

	/* The process keyring is only shared between the thपढ़ोs in a process;
	 * anything outside of those thपढ़ोs करोesn't inherit.
	 */
	अगर (!(clone_flags & CLONE_THREAD)) अणु
		key_put(new->process_keyring);
		new->process_keyring = शून्य;
	पूर्ण
#पूर्ण_अगर

	atomic_inc(&new->user->processes);
	p->cred = p->real_cred = get_cred(new);
	alter_cred_subscribers(new, 2);
	validate_creds(new);
	वापस 0;

error_put:
	put_cred(new);
	वापस ret;
पूर्ण

अटल bool cred_cap_issubset(स्थिर काष्ठा cred *set, स्थिर काष्ठा cred *subset)
अणु
	स्थिर काष्ठा user_namespace *set_ns = set->user_ns;
	स्थिर काष्ठा user_namespace *subset_ns = subset->user_ns;

	/* If the two credentials are in the same user namespace see अगर
	 * the capabilities of subset are a subset of set.
	 */
	अगर (set_ns == subset_ns)
		वापस cap_issubset(subset->cap_permitted, set->cap_permitted);

	/* The credentials are in a dअगरferent user namespaces
	 * thereक्रमe one is a subset of the other only अगर a set is an
	 * ancestor of subset and set->euid is owner of subset or one
	 * of subsets ancestors.
	 */
	क्रम (;subset_ns != &init_user_ns; subset_ns = subset_ns->parent) अणु
		अगर ((set_ns == subset_ns->parent)  &&
		    uid_eq(subset_ns->owner, set->euid))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * commit_creds - Install new credentials upon the current task
 * @new: The credentials to be asचिन्हित
 *
 * Install a new set of credentials to the current task, using RCU to replace
 * the old set.  Both the objective and the subjective credentials poपूर्णांकers are
 * updated.  This function may not be called अगर the subjective credentials are
 * in an overridden state.
 *
 * This function eats the caller's reference to the new credentials.
 *
 * Always वापसs 0 thus allowing this function to be tail-called at the end
 * of, say, sys_setgid().
 */
पूर्णांक commit_creds(काष्ठा cred *new)
अणु
	काष्ठा task_काष्ठा *task = current;
	स्थिर काष्ठा cred *old = task->real_cred;

	kdebug("commit_creds(%p{%d,%d})", new,
	       atomic_पढ़ो(&new->usage),
	       पढ़ो_cred_subscribers(new));

	BUG_ON(task->cred != old);
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	BUG_ON(पढ़ो_cred_subscribers(old) < 2);
	validate_creds(old);
	validate_creds(new);
#पूर्ण_अगर
	BUG_ON(atomic_पढ़ो(&new->usage) < 1);

	get_cred(new); /* we will require a ref क्रम the subj creds too */

	/* dumpability changes */
	अगर (!uid_eq(old->euid, new->euid) ||
	    !gid_eq(old->egid, new->egid) ||
	    !uid_eq(old->fsuid, new->fsuid) ||
	    !gid_eq(old->fsgid, new->fsgid) ||
	    !cred_cap_issubset(old, new)) अणु
		अगर (task->mm)
			set_dumpable(task->mm, suid_dumpable);
		task->pdeath_संकेत = 0;
		/*
		 * If a task drops privileges and becomes nondumpable,
		 * the dumpability change must become visible beक्रमe
		 * the credential change; otherwise, a __ptrace_may_access()
		 * racing with this change may be able to attach to a task it
		 * shouldn't be able to attach to (as अगर the task had dropped
		 * privileges without becoming nondumpable).
		 * Pairs with a पढ़ो barrier in __ptrace_may_access().
		 */
		smp_wmb();
	पूर्ण

	/* alter the thपढ़ो keyring */
	अगर (!uid_eq(new->fsuid, old->fsuid))
		key_fsuid_changed(new);
	अगर (!gid_eq(new->fsgid, old->fsgid))
		key_fsgid_changed(new);

	/* करो it
	 * RLIMIT_NPROC limits on user->processes have alपढ़ोy been checked
	 * in set_user().
	 */
	alter_cred_subscribers(new, 2);
	अगर (new->user != old->user)
		atomic_inc(&new->user->processes);
	rcu_assign_poपूर्णांकer(task->real_cred, new);
	rcu_assign_poपूर्णांकer(task->cred, new);
	अगर (new->user != old->user)
		atomic_dec(&old->user->processes);
	alter_cred_subscribers(old, -2);

	/* send notअगरications */
	अगर (!uid_eq(new->uid,   old->uid)  ||
	    !uid_eq(new->euid,  old->euid) ||
	    !uid_eq(new->suid,  old->suid) ||
	    !uid_eq(new->fsuid, old->fsuid))
		proc_id_connector(task, PROC_EVENT_UID);

	अगर (!gid_eq(new->gid,   old->gid)  ||
	    !gid_eq(new->egid,  old->egid) ||
	    !gid_eq(new->sgid,  old->sgid) ||
	    !gid_eq(new->fsgid, old->fsgid))
		proc_id_connector(task, PROC_EVENT_GID);

	/* release the old obj and subj refs both */
	put_cred(old);
	put_cred(old);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(commit_creds);

/**
 * पात_creds - Discard a set of credentials and unlock the current task
 * @new: The credentials that were going to be applied
 *
 * Discard a set of credentials that were under स्थिरruction and unlock the
 * current task.
 */
व्योम पात_creds(काष्ठा cred *new)
अणु
	kdebug("abort_creds(%p{%d,%d})", new,
	       atomic_पढ़ो(&new->usage),
	       पढ़ो_cred_subscribers(new));

#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	BUG_ON(पढ़ो_cred_subscribers(new) != 0);
#पूर्ण_अगर
	BUG_ON(atomic_पढ़ो(&new->usage) < 1);
	put_cred(new);
पूर्ण
EXPORT_SYMBOL(पात_creds);

/**
 * override_creds - Override the current process's subjective credentials
 * @new: The credentials to be asचिन्हित
 *
 * Install a set of temporary override subjective credentials on the current
 * process, वापसing the old set क्रम later reversion.
 */
स्थिर काष्ठा cred *override_creds(स्थिर काष्ठा cred *new)
अणु
	स्थिर काष्ठा cred *old = current->cred;

	kdebug("override_creds(%p{%d,%d})", new,
	       atomic_पढ़ो(&new->usage),
	       पढ़ो_cred_subscribers(new));

	validate_creds(old);
	validate_creds(new);

	/*
	 * NOTE! This uses 'get_new_cred()' rather than 'get_cred()'.
	 *
	 * That means that we करो not clear the 'non_rcu' flag, since
	 * we are only installing the cred पूर्णांकo the thपढ़ो-synchronous
	 * '->cred' pointer, not the '->real_cred' poपूर्णांकer that is
	 * visible to other thपढ़ोs under RCU.
	 *
	 * Also note that we did validate_creds() manually, not depending
	 * on the validation in 'get_cred()'.
	 */
	get_new_cred((काष्ठा cred *)new);
	alter_cred_subscribers(new, 1);
	rcu_assign_poपूर्णांकer(current->cred, new);
	alter_cred_subscribers(old, -1);

	kdebug("override_creds() = %p{%d,%d}", old,
	       atomic_पढ़ो(&old->usage),
	       पढ़ो_cred_subscribers(old));
	वापस old;
पूर्ण
EXPORT_SYMBOL(override_creds);

/**
 * revert_creds - Revert a temporary subjective credentials override
 * @old: The credentials to be restored
 *
 * Revert a temporary set of override subjective credentials to an old set,
 * discarding the override set.
 */
व्योम revert_creds(स्थिर काष्ठा cred *old)
अणु
	स्थिर काष्ठा cred *override = current->cred;

	kdebug("revert_creds(%p{%d,%d})", old,
	       atomic_पढ़ो(&old->usage),
	       पढ़ो_cred_subscribers(old));

	validate_creds(old);
	validate_creds(override);
	alter_cred_subscribers(old, 1);
	rcu_assign_poपूर्णांकer(current->cred, old);
	alter_cred_subscribers(override, -1);
	put_cred(override);
पूर्ण
EXPORT_SYMBOL(revert_creds);

/**
 * cred_fscmp - Compare two credentials with respect to fileप्रणाली access.
 * @a: The first credential
 * @b: The second credential
 *
 * cred_cmp() will वापस zero अगर both credentials have the same
 * fsuid, fsgid, and supplementary groups.  That is, अगर they will both
 * provide the same access to files based on mode/uid/gid.
 * If the credentials are dअगरferent, then either -1 or 1 will
 * be वापसed depending on whether @a comes beक्रमe or after @b
 * respectively in an arbitrary, but stable, ordering of credentials.
 *
 * Return: -1, 0, or 1 depending on comparison
 */
पूर्णांक cred_fscmp(स्थिर काष्ठा cred *a, स्थिर काष्ठा cred *b)
अणु
	काष्ठा group_info *ga, *gb;
	पूर्णांक g;

	अगर (a == b)
		वापस 0;
	अगर (uid_lt(a->fsuid, b->fsuid))
		वापस -1;
	अगर (uid_gt(a->fsuid, b->fsuid))
		वापस 1;

	अगर (gid_lt(a->fsgid, b->fsgid))
		वापस -1;
	अगर (gid_gt(a->fsgid, b->fsgid))
		वापस 1;

	ga = a->group_info;
	gb = b->group_info;
	अगर (ga == gb)
		वापस 0;
	अगर (ga == शून्य)
		वापस -1;
	अगर (gb == शून्य)
		वापस 1;
	अगर (ga->ngroups < gb->ngroups)
		वापस -1;
	अगर (ga->ngroups > gb->ngroups)
		वापस 1;

	क्रम (g = 0; g < ga->ngroups; g++) अणु
		अगर (gid_lt(ga->gid[g], gb->gid[g]))
			वापस -1;
		अगर (gid_gt(ga->gid[g], gb->gid[g]))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cred_fscmp);

/*
 * initialise the credentials stuff
 */
व्योम __init cred_init(व्योम)
अणु
	/* allocate a slab in which we can store credentials */
	cred_jar = kmem_cache_create("cred_jar", माप(काष्ठा cred), 0,
			SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_ACCOUNT, शून्य);
पूर्ण

/**
 * prepare_kernel_cred - Prepare a set of credentials क्रम a kernel service
 * @daemon: A userspace daemon to be used as a reference
 *
 * Prepare a set of credentials क्रम a kernel service.  This can then be used to
 * override a task's own credentials so that work can be करोne on behalf of that
 * task that requires a dअगरferent subjective context.
 *
 * @daemon is used to provide a base क्रम the security record, but can be शून्य.
 * If @daemon is supplied, then the security data will be derived from that;
 * otherwise they'll be set to 0 and no groups, full capabilities and no keys.
 *
 * The caller may change these controls afterwards अगर desired.
 *
 * Returns the new credentials or शून्य अगर out of memory.
 */
काष्ठा cred *prepare_kernel_cred(काष्ठा task_काष्ठा *daemon)
अणु
	स्थिर काष्ठा cred *old;
	काष्ठा cred *new;

	new = kmem_cache_alloc(cred_jar, GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	kdebug("prepare_kernel_cred() alloc %p", new);

	अगर (daemon)
		old = get_task_cred(daemon);
	अन्यथा
		old = get_cred(&init_cred);

	validate_creds(old);

	*new = *old;
	new->non_rcu = 0;
	atomic_set(&new->usage, 1);
	set_cred_subscribers(new, 0);
	get_uid(new->user);
	get_user_ns(new->user_ns);
	get_group_info(new->group_info);

#अगर_घोषित CONFIG_KEYS
	new->session_keyring = शून्य;
	new->process_keyring = शून्य;
	new->thपढ़ो_keyring = शून्य;
	new->request_key_auth = शून्य;
	new->jit_keyring = KEY_REQKEY_DEFL_THREAD_KEYRING;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY
	new->security = शून्य;
#पूर्ण_अगर
	अगर (security_prepare_creds(new, old, GFP_KERNEL_ACCOUNT) < 0)
		जाओ error;

	put_cred(old);
	validate_creds(new);
	वापस new;

error:
	put_cred(new);
	put_cred(old);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(prepare_kernel_cred);

/**
 * set_security_override - Set the security ID in a set of credentials
 * @new: The credentials to alter
 * @secid: The LSM security ID to set
 *
 * Set the LSM security ID in a set of credentials so that the subjective
 * security is overridden when an alternative set of credentials is used.
 */
पूर्णांक set_security_override(काष्ठा cred *new, u32 secid)
अणु
	वापस security_kernel_act_as(new, secid);
पूर्ण
EXPORT_SYMBOL(set_security_override);

/**
 * set_security_override_from_ctx - Set the security ID in a set of credentials
 * @new: The credentials to alter
 * @secctx: The LSM security context to generate the security ID from.
 *
 * Set the LSM security ID in a set of credentials so that the subjective
 * security is overridden when an alternative set of credentials is used.  The
 * security ID is specअगरied in string क्रमm as a security context to be
 * पूर्णांकerpreted by the LSM.
 */
पूर्णांक set_security_override_from_ctx(काष्ठा cred *new, स्थिर अक्षर *secctx)
अणु
	u32 secid;
	पूर्णांक ret;

	ret = security_secctx_to_secid(secctx, म_माप(secctx), &secid);
	अगर (ret < 0)
		वापस ret;

	वापस set_security_override(new, secid);
पूर्ण
EXPORT_SYMBOL(set_security_override_from_ctx);

/**
 * set_create_files_as - Set the LSM file create context in a set of credentials
 * @new: The credentials to alter
 * @inode: The inode to take the context from
 *
 * Change the LSM file creation context in a set of credentials to be the same
 * as the object context of the specअगरied inode, so that the new inodes have
 * the same MAC context as that inode.
 */
पूर्णांक set_create_files_as(काष्ठा cred *new, काष्ठा inode *inode)
अणु
	अगर (!uid_valid(inode->i_uid) || !gid_valid(inode->i_gid))
		वापस -EINVAL;
	new->fsuid = inode->i_uid;
	new->fsgid = inode->i_gid;
	वापस security_kernel_create_files_as(new, inode);
पूर्ण
EXPORT_SYMBOL(set_create_files_as);

#अगर_घोषित CONFIG_DEBUG_CREDENTIALS

bool creds_are_invalid(स्थिर काष्ठा cred *cred)
अणु
	अगर (cred->magic != CRED_MAGIC)
		वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL(creds_are_invalid);

/*
 * dump invalid credentials
 */
अटल व्योम dump_invalid_creds(स्थिर काष्ठा cred *cred, स्थिर अक्षर *label,
			       स्थिर काष्ठा task_काष्ठा *tsk)
अणु
	prपूर्णांकk(KERN_ERR "CRED: %s credentials: %p %s%s%s\n",
	       label, cred,
	       cred == &init_cred ? "[init]" : "",
	       cred == tsk->real_cred ? "[real]" : "",
	       cred == tsk->cred ? "[eff]" : "");
	prपूर्णांकk(KERN_ERR "CRED: ->magic=%x, put_addr=%p\n",
	       cred->magic, cred->put_addr);
	prपूर्णांकk(KERN_ERR "CRED: ->usage=%d, subscr=%d\n",
	       atomic_पढ़ो(&cred->usage),
	       पढ़ो_cred_subscribers(cred));
	prपूर्णांकk(KERN_ERR "CRED: ->*uid = { %d,%d,%d,%d }\n",
		from_kuid_munged(&init_user_ns, cred->uid),
		from_kuid_munged(&init_user_ns, cred->euid),
		from_kuid_munged(&init_user_ns, cred->suid),
		from_kuid_munged(&init_user_ns, cred->fsuid));
	prपूर्णांकk(KERN_ERR "CRED: ->*gid = { %d,%d,%d,%d }\n",
		from_kgid_munged(&init_user_ns, cred->gid),
		from_kgid_munged(&init_user_ns, cred->egid),
		from_kgid_munged(&init_user_ns, cred->sgid),
		from_kgid_munged(&init_user_ns, cred->fsgid));
#अगर_घोषित CONFIG_SECURITY
	prपूर्णांकk(KERN_ERR "CRED: ->security is %p\n", cred->security);
	अगर ((अचिन्हित दीर्घ) cred->security >= PAGE_SIZE &&
	    (((अचिन्हित दीर्घ) cred->security & 0xffffff00) !=
	     (POISON_FREE << 24 | POISON_FREE << 16 | POISON_FREE << 8)))
		prपूर्णांकk(KERN_ERR "CRED: ->security {%x, %x}\n",
		       ((u32*)cred->security)[0],
		       ((u32*)cred->security)[1]);
#पूर्ण_अगर
पूर्ण

/*
 * report use of invalid credentials
 */
व्योम __invalid_creds(स्थिर काष्ठा cred *cred, स्थिर अक्षर *file, अचिन्हित line)
अणु
	prपूर्णांकk(KERN_ERR "CRED: Invalid credentials\n");
	prपूर्णांकk(KERN_ERR "CRED: At %s:%u\n", file, line);
	dump_invalid_creds(cred, "Specified", current);
	BUG();
पूर्ण
EXPORT_SYMBOL(__invalid_creds);

/*
 * check the credentials on a process
 */
व्योम __validate_process_creds(काष्ठा task_काष्ठा *tsk,
			      स्थिर अक्षर *file, अचिन्हित line)
अणु
	अगर (tsk->cred == tsk->real_cred) अणु
		अगर (unlikely(पढ़ो_cred_subscribers(tsk->cred) < 2 ||
			     creds_are_invalid(tsk->cred)))
			जाओ invalid_creds;
	पूर्ण अन्यथा अणु
		अगर (unlikely(पढ़ो_cred_subscribers(tsk->real_cred) < 1 ||
			     पढ़ो_cred_subscribers(tsk->cred) < 1 ||
			     creds_are_invalid(tsk->real_cred) ||
			     creds_are_invalid(tsk->cred)))
			जाओ invalid_creds;
	पूर्ण
	वापस;

invalid_creds:
	prपूर्णांकk(KERN_ERR "CRED: Invalid process credentials\n");
	prपूर्णांकk(KERN_ERR "CRED: At %s:%u\n", file, line);

	dump_invalid_creds(tsk->real_cred, "Real", tsk);
	अगर (tsk->cred != tsk->real_cred)
		dump_invalid_creds(tsk->cred, "Effective", tsk);
	अन्यथा
		prपूर्णांकk(KERN_ERR "CRED: Effective creds == Real creds\n");
	BUG();
पूर्ण
EXPORT_SYMBOL(__validate_process_creds);

/*
 * check creds क्रम करो_निकास()
 */
व्योम validate_creds_क्रम_करो_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	kdebug("validate_creds_for_do_exit(%p,%p{%d,%d})",
	       tsk->real_cred, tsk->cred,
	       atomic_पढ़ो(&tsk->cred->usage),
	       पढ़ो_cred_subscribers(tsk->cred));

	__validate_process_creds(tsk, __खाता__, __LINE__);
पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_CREDENTIALS */
