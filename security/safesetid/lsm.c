<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SafeSetID Linux Security Module
 *
 * Author: Micah Morton <mortonm@chromium.org>
 *
 * Copyright (C) 2018 The Chromium OS Authors.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 */

#घोषणा pr_fmt(fmt) "SafeSetID: " fmt

#समावेश <linux/lsm_hooks.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/security.h>
#समावेश "lsm.h"

/* Flag indicating whether initialization completed */
पूर्णांक safesetid_initialized;

काष्ठा setid_ruleset __rcu *safesetid_setuid_rules;
काष्ठा setid_ruleset __rcu *safesetid_setgid_rules;


/* Compute a decision क्रम a transition from @src to @dst under @policy. */
क्रमागत sid_policy_type _setid_policy_lookup(काष्ठा setid_ruleset *policy,
		kid_t src, kid_t dst)
अणु
	काष्ठा setid_rule *rule;
	क्रमागत sid_policy_type result = SIDPOL_DEFAULT;

	अगर (policy->type == UID) अणु
		hash_क्रम_each_possible(policy->rules, rule, next, __kuid_val(src.uid)) अणु
			अगर (!uid_eq(rule->src_id.uid, src.uid))
				जारी;
			अगर (uid_eq(rule->dst_id.uid, dst.uid))
				वापस SIDPOL_ALLOWED;
			result = SIDPOL_CONSTRAINED;
		पूर्ण
	पूर्ण अन्यथा अगर (policy->type == GID) अणु
		hash_क्रम_each_possible(policy->rules, rule, next, __kgid_val(src.gid)) अणु
			अगर (!gid_eq(rule->src_id.gid, src.gid))
				जारी;
			अगर (gid_eq(rule->dst_id.gid, dst.gid))अणु
				वापस SIDPOL_ALLOWED;
			पूर्ण
			result = SIDPOL_CONSTRAINED;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Should not reach here, report the ID as contrainsted */
		result = SIDPOL_CONSTRAINED;
	पूर्ण
	वापस result;
पूर्ण

/*
 * Compute a decision क्रम a transition from @src to @dst under the active
 * policy.
 */
अटल क्रमागत sid_policy_type setid_policy_lookup(kid_t src, kid_t dst, क्रमागत setid_type new_type)
अणु
	क्रमागत sid_policy_type result = SIDPOL_DEFAULT;
	काष्ठा setid_ruleset *pol;

	rcu_पढ़ो_lock();
	अगर (new_type == UID)
		pol = rcu_dereference(safesetid_setuid_rules);
	अन्यथा अगर (new_type == GID)
		pol = rcu_dereference(safesetid_setgid_rules);
	अन्यथा अणु /* Should not reach here */
		result = SIDPOL_CONSTRAINED;
		rcu_पढ़ो_unlock();
		वापस result;
	पूर्ण

	अगर (pol) अणु
		pol->type = new_type;
		result = _setid_policy_lookup(pol, src, dst);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस result;
पूर्ण

अटल पूर्णांक safesetid_security_capable(स्थिर काष्ठा cred *cred,
				      काष्ठा user_namespace *ns,
				      पूर्णांक cap,
				      अचिन्हित पूर्णांक opts)
अणु
	/* We're only पूर्णांकerested in CAP_SETUID and CAP_SETGID. */
	अगर (cap != CAP_SETUID && cap != CAP_SETGID)
		वापस 0;

	/*
	 * If CAP_SETअणुU/Gपूर्णID is currently used क्रम a setid() syscall, we want to
	 * let it go through here; the real security check happens later, in the
	 * task_fix_setअणुu/gपूर्णid hook.
         *
         * NOTE:
         * Until we add support क्रम restricting setgroups() calls, GID security
         * policies offer no meaningful security since we always वापस 0 here
         * when called from within the setgroups() syscall and there is no
         * additional hook later on to enक्रमce security policies क्रम setgroups().
	 */
	अगर ((opts & CAP_OPT_INSETID) != 0)
		वापस 0;

	चयन (cap) अणु
	हाल CAP_SETUID:
		/*
		* If no policy applies to this task, allow the use of CAP_SETUID क्रम
		* other purposes.
		*/
		अगर (setid_policy_lookup((kid_t)अणु.uid = cred->uidपूर्ण, INVALID_ID, UID) == SIDPOL_DEFAULT)
			वापस 0;
		/*
		 * Reject use of CAP_SETUID क्रम functionality other than calling
		 * set*uid() (e.g. setting up userns uid mappings).
		 */
		pr_warn("Operation requires CAP_SETUID, which is not available to UID %u for operations besides approved set*uid transitions\n",
			__kuid_val(cred->uid));
		वापस -EPERM;
	हाल CAP_SETGID:
		/*
		* If no policy applies to this task, allow the use of CAP_SETGID क्रम
		* other purposes.
		*/
		अगर (setid_policy_lookup((kid_t)अणु.gid = cred->gidपूर्ण, INVALID_ID, GID) == SIDPOL_DEFAULT)
			वापस 0;
		/*
		 * Reject use of CAP_SETUID क्रम functionality other than calling
		 * set*gid() (e.g. setting up userns gid mappings).
		 */
		pr_warn("Operation requires CAP_SETGID, which is not available to GID %u for operations besides approved set*gid transitions\n",
			__kuid_val(cred->uid));
		वापस -EPERM;
	शेष:
		/* Error, the only capabilities were checking क्रम is CAP_SETUID/GID */
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check whether a caller with old credentials @old is allowed to चयन to
 * credentials that contain @new_id.
 */
अटल bool id_permitted_क्रम_cred(स्थिर काष्ठा cred *old, kid_t new_id, क्रमागत setid_type new_type)
अणु
	bool permitted;

	/* If our old creds alपढ़ोy had this ID in it, it's fine. */
	अगर (new_type == UID) अणु
		अगर (uid_eq(new_id.uid, old->uid) || uid_eq(new_id.uid, old->euid) ||
			uid_eq(new_id.uid, old->suid))
			वापस true;
	पूर्ण अन्यथा अगर (new_type == GID)अणु
		अगर (gid_eq(new_id.gid, old->gid) || gid_eq(new_id.gid, old->egid) ||
			gid_eq(new_id.gid, old->sgid))
			वापस true;
	पूर्ण अन्यथा /* Error, new_type is an invalid type */
		वापस false;

	/*
	 * Transitions to new UIDs require a check against the policy of the old
	 * RUID.
	 */
	permitted =
	    setid_policy_lookup((kid_t)अणु.uid = old->uidपूर्ण, new_id, new_type) != SIDPOL_CONSTRAINED;

	अगर (!permitted) अणु
		अगर (new_type == UID) अणु
			pr_warn("UID transition ((%d,%d,%d) -> %d) blocked\n",
				__kuid_val(old->uid), __kuid_val(old->euid),
				__kuid_val(old->suid), __kuid_val(new_id.uid));
		पूर्ण अन्यथा अगर (new_type == GID) अणु
			pr_warn("GID transition ((%d,%d,%d) -> %d) blocked\n",
				__kgid_val(old->gid), __kgid_val(old->egid),
				__kgid_val(old->sgid), __kgid_val(new_id.gid));
		पूर्ण अन्यथा /* Error, new_type is an invalid type */
			वापस false;
	पूर्ण
	वापस permitted;
पूर्ण

/*
 * Check whether there is either an exception क्रम user under old cred काष्ठा to
 * set*uid to user under new cred काष्ठा, or the UID transition is allowed (by
 * Linux set*uid rules) even without CAP_SETUID.
 */
अटल पूर्णांक safesetid_task_fix_setuid(काष्ठा cred *new,
				     स्थिर काष्ठा cred *old,
				     पूर्णांक flags)
अणु

	/* Do nothing अगर there are no setuid restrictions क्रम our old RUID. */
	अगर (setid_policy_lookup((kid_t)अणु.uid = old->uidपूर्ण, INVALID_ID, UID) == SIDPOL_DEFAULT)
		वापस 0;

	अगर (id_permitted_क्रम_cred(old, (kid_t)अणु.uid = new->uidपूर्ण, UID) &&
	    id_permitted_क्रम_cred(old, (kid_t)अणु.uid = new->euidपूर्ण, UID) &&
	    id_permitted_क्रम_cred(old, (kid_t)अणु.uid = new->suidपूर्ण, UID) &&
	    id_permitted_क्रम_cred(old, (kid_t)अणु.uid = new->fsuidपूर्ण, UID))
		वापस 0;

	/*
	 * Kill this process to aव्योम potential security vulnerabilities
	 * that could arise from a missing allowlist entry preventing a
	 * privileged process from dropping to a lesser-privileged one.
	 */
	क्रमce_sig(SIGKILL);
	वापस -EACCES;
पूर्ण

अटल पूर्णांक safesetid_task_fix_setgid(काष्ठा cred *new,
				     स्थिर काष्ठा cred *old,
				     पूर्णांक flags)
अणु

	/* Do nothing अगर there are no setgid restrictions क्रम our old RGID. */
	अगर (setid_policy_lookup((kid_t)अणु.gid = old->gidपूर्ण, INVALID_ID, GID) == SIDPOL_DEFAULT)
		वापस 0;

	अगर (id_permitted_क्रम_cred(old, (kid_t)अणु.gid = new->gidपूर्ण, GID) &&
	    id_permitted_क्रम_cred(old, (kid_t)अणु.gid = new->egidपूर्ण, GID) &&
	    id_permitted_क्रम_cred(old, (kid_t)अणु.gid = new->sgidपूर्ण, GID) &&
	    id_permitted_क्रम_cred(old, (kid_t)अणु.gid = new->fsgidपूर्ण, GID))
		वापस 0;

	/*
	 * Kill this process to aव्योम potential security vulnerabilities
	 * that could arise from a missing allowlist entry preventing a
	 * privileged process from dropping to a lesser-privileged one.
	 */
	क्रमce_sig(SIGKILL);
	वापस -EACCES;
पूर्ण

अटल काष्ठा security_hook_list safesetid_security_hooks[] = अणु
	LSM_HOOK_INIT(task_fix_setuid, safesetid_task_fix_setuid),
	LSM_HOOK_INIT(task_fix_setgid, safesetid_task_fix_setgid),
	LSM_HOOK_INIT(capable, safesetid_security_capable)
पूर्ण;

अटल पूर्णांक __init safesetid_security_init(व्योम)
अणु
	security_add_hooks(safesetid_security_hooks,
			   ARRAY_SIZE(safesetid_security_hooks), "safesetid");

	/* Report that SafeSetID successfully initialized */
	safesetid_initialized = 1;

	वापस 0;
पूर्ण

DEFINE_LSM(safesetid_security_init) = अणु
	.init = safesetid_security_init,
	.name = "safesetid",
पूर्ण;
