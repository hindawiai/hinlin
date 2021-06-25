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

#समावेश <linux/security.h>
#समावेश <linux/cred.h>

#समावेश "lsm.h"

अटल DEFINE_MUTEX(uid_policy_update_lock);
अटल DEFINE_MUTEX(gid_policy_update_lock);

/*
 * In the हाल the input buffer contains one or more invalid IDs, the kid_t
 * variables poपूर्णांकed to by @parent and @child will get updated but this
 * function will वापस an error.
 * Contents of @buf may be modअगरied.
 */
अटल पूर्णांक parse_policy_line(काष्ठा file *file, अक्षर *buf,
	काष्ठा setid_rule *rule)
अणु
	अक्षर *child_str;
	पूर्णांक ret;
	u32 parsed_parent, parsed_child;

	/* Format of |buf| string should be <UID>:<UID> or <GID>:<GID> */
	child_str = म_अक्षर(buf, ':');
	अगर (child_str == शून्य)
		वापस -EINVAL;
	*child_str = '\0';
	child_str++;

	ret = kstrtou32(buf, 0, &parsed_parent);
	अगर (ret)
		वापस ret;

	ret = kstrtou32(child_str, 0, &parsed_child);
	अगर (ret)
		वापस ret;

	अगर (rule->type == UID)अणु
		rule->src_id.uid = make_kuid(file->f_cred->user_ns, parsed_parent);
		rule->dst_id.uid = make_kuid(file->f_cred->user_ns, parsed_child);
		अगर (!uid_valid(rule->src_id.uid) || !uid_valid(rule->dst_id.uid))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (rule->type == GID)अणु
		rule->src_id.gid = make_kgid(file->f_cred->user_ns, parsed_parent);
		rule->dst_id.gid = make_kgid(file->f_cred->user_ns, parsed_child);
		अगर (!gid_valid(rule->src_id.gid) || !gid_valid(rule->dst_id.gid))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Error, rule->type is an invalid type */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __release_ruleset(काष्ठा rcu_head *rcu)
अणु
	काष्ठा setid_ruleset *pol =
		container_of(rcu, काष्ठा setid_ruleset, rcu);
	पूर्णांक bucket;
	काष्ठा setid_rule *rule;
	काष्ठा hlist_node *पंचांगp;

	hash_क्रम_each_safe(pol->rules, bucket, पंचांगp, rule, next)
		kमुक्त(rule);
	kमुक्त(pol->policy_str);
	kमुक्त(pol);
पूर्ण

अटल व्योम release_ruleset(काष्ठा setid_ruleset *pol)अणु
	call_rcu(&pol->rcu, __release_ruleset);
पूर्ण

अटल व्योम insert_rule(काष्ठा setid_ruleset *pol, काष्ठा setid_rule *rule)
अणु
	अगर (pol->type == UID)
		hash_add(pol->rules, &rule->next, __kuid_val(rule->src_id.uid));
	अन्यथा अगर (pol->type == GID)
		hash_add(pol->rules, &rule->next, __kgid_val(rule->src_id.gid));
	अन्यथा /* Error, pol->type is neither UID or GID */
		वापस;
पूर्ण

अटल पूर्णांक verअगरy_ruleset(काष्ठा setid_ruleset *pol)
अणु
	पूर्णांक bucket;
	काष्ठा setid_rule *rule, *nrule;
	पूर्णांक res = 0;

	hash_क्रम_each(pol->rules, bucket, rule, next) अणु
		अगर (_setid_policy_lookup(pol, rule->dst_id, INVALID_ID) == SIDPOL_DEFAULT) अणु
			अगर (pol->type == UID) अणु
				pr_warn("insecure policy detected: uid %d is constrained but transitively unconstrained through uid %d\n",
					__kuid_val(rule->src_id.uid),
					__kuid_val(rule->dst_id.uid));
			पूर्ण अन्यथा अगर (pol->type == GID) अणु
				pr_warn("insecure policy detected: gid %d is constrained but transitively unconstrained through gid %d\n",
					__kgid_val(rule->src_id.gid),
					__kgid_val(rule->dst_id.gid));
			पूर्ण अन्यथा अणु /* pol->type is an invalid type */
				res = -EINVAL;
				वापस res;
			पूर्ण
			res = -EINVAL;

			/* fix it up */
			nrule = kदो_स्मृति(माप(काष्ठा setid_rule), GFP_KERNEL);
			अगर (!nrule)
				वापस -ENOMEM;
			अगर (pol->type == UID)अणु
				nrule->src_id.uid = rule->dst_id.uid;
				nrule->dst_id.uid = rule->dst_id.uid;
				nrule->type = UID;
			पूर्ण अन्यथा अणु /* pol->type must be GID अगर we've made it to here */
				nrule->src_id.gid = rule->dst_id.gid;
				nrule->dst_id.gid = rule->dst_id.gid;
				nrule->type = GID;
			पूर्ण
			insert_rule(pol, nrule);
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल sमाप_प्रकार handle_policy_update(काष्ठा file *file,
				    स्थिर अक्षर __user *ubuf, माप_प्रकार len, क्रमागत setid_type policy_type)
अणु
	काष्ठा setid_ruleset *pol;
	अक्षर *buf, *p, *end;
	पूर्णांक err;

	pol = kदो_स्मृति(माप(काष्ठा setid_ruleset), GFP_KERNEL);
	अगर (!pol)
		वापस -ENOMEM;
	pol->policy_str = शून्य;
	pol->type = policy_type;
	hash_init(pol->rules);

	p = buf = memdup_user_nul(ubuf, len);
	अगर (IS_ERR(buf)) अणु
		err = PTR_ERR(buf);
		जाओ out_मुक्त_pol;
	पूर्ण
	pol->policy_str = kstrdup(buf, GFP_KERNEL);
	अगर (pol->policy_str == शून्य) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_buf;
	पूर्ण

	/* policy lines, including the last one, end with \न */
	जबतक (*p != '\0') अणु
		काष्ठा setid_rule *rule;

		end = म_अक्षर(p, '\n');
		अगर (end == शून्य) अणु
			err = -EINVAL;
			जाओ out_मुक्त_buf;
		पूर्ण
		*end = '\0';

		rule = kदो_स्मृति(माप(काष्ठा setid_rule), GFP_KERNEL);
		अगर (!rule) अणु
			err = -ENOMEM;
			जाओ out_मुक्त_buf;
		पूर्ण

		rule->type = policy_type;
		err = parse_policy_line(file, p, rule);
		अगर (err)
			जाओ out_मुक्त_rule;

		अगर (_setid_policy_lookup(pol, rule->src_id, rule->dst_id) == SIDPOL_ALLOWED) अणु
			pr_warn("bad policy: duplicate entry\n");
			err = -EEXIST;
			जाओ out_मुक्त_rule;
		पूर्ण

		insert_rule(pol, rule);
		p = end + 1;
		जारी;

out_मुक्त_rule:
		kमुक्त(rule);
		जाओ out_मुक्त_buf;
	पूर्ण

	err = verअगरy_ruleset(pol);
	/* bogus policy falls through after fixing it up */
	अगर (err && err != -EINVAL)
		जाओ out_मुक्त_buf;

	/*
	 * Everything looks good, apply the policy and release the old one.
	 * What we really want here is an xchg() wrapper क्रम RCU, but since that
	 * करोesn't currently exist, just use a spinlock क्रम now.
	 */
	अगर (policy_type == UID) अणु
		mutex_lock(&uid_policy_update_lock);
		pol = rcu_replace_poपूर्णांकer(safesetid_setuid_rules, pol,
					  lockdep_is_held(&uid_policy_update_lock));
		mutex_unlock(&uid_policy_update_lock);
	पूर्ण अन्यथा अगर (policy_type == GID) अणु
		mutex_lock(&gid_policy_update_lock);
		pol = rcu_replace_poपूर्णांकer(safesetid_setgid_rules, pol,
					  lockdep_is_held(&gid_policy_update_lock));
		mutex_unlock(&gid_policy_update_lock);
	पूर्ण अन्यथा अणु
		/* Error, policy type is neither UID or GID */
		pr_warn("error: bad policy type");
	पूर्ण
	err = len;

out_मुक्त_buf:
	kमुक्त(buf);
out_मुक्त_pol:
	अगर (pol)
		release_ruleset(pol);
	वापस err;
पूर्ण

अटल sमाप_प्रकार safesetid_uid_file_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *buf,
				    माप_प्रकार len,
				    loff_t *ppos)
अणु
	अगर (!file_ns_capable(file, &init_user_ns, CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (*ppos != 0)
		वापस -EINVAL;

	वापस handle_policy_update(file, buf, len, UID);
पूर्ण

अटल sमाप_प्रकार safesetid_gid_file_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *buf,
				    माप_प्रकार len,
				    loff_t *ppos)
अणु
	अगर (!file_ns_capable(file, &init_user_ns, CAP_MAC_ADMIN))
		वापस -EPERM;

	अगर (*ppos != 0)
		वापस -EINVAL;

	वापस handle_policy_update(file, buf, len, GID);
पूर्ण

अटल sमाप_प्रकार safesetid_file_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार len, loff_t *ppos, काष्ठा mutex *policy_update_lock, काष्ठा __rcu setid_ruleset* ruleset)
अणु
	sमाप_प्रकार res = 0;
	काष्ठा setid_ruleset *pol;
	स्थिर अक्षर *kbuf;

	mutex_lock(policy_update_lock);
	pol = rcu_dereference_रक्षित(ruleset, lockdep_is_held(policy_update_lock));
	अगर (pol) अणु
		kbuf = pol->policy_str;
		res = simple_पढ़ो_from_buffer(buf, len, ppos,
					      kbuf, म_माप(kbuf));
	पूर्ण
	mutex_unlock(policy_update_lock);

	वापस res;
पूर्ण

अटल sमाप_प्रकार safesetid_uid_file_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार len, loff_t *ppos)
अणु
	वापस safesetid_file_पढ़ो(file, buf, len, ppos,
				   &uid_policy_update_lock, safesetid_setuid_rules);
पूर्ण

अटल sमाप_प्रकार safesetid_gid_file_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार len, loff_t *ppos)
अणु
	वापस safesetid_file_पढ़ो(file, buf, len, ppos,
				   &gid_policy_update_lock, safesetid_setgid_rules);
पूर्ण



अटल स्थिर काष्ठा file_operations safesetid_uid_file_fops = अणु
	.पढ़ो = safesetid_uid_file_पढ़ो,
	.ग_लिखो = safesetid_uid_file_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations safesetid_gid_file_fops = अणु
	.पढ़ो = safesetid_gid_file_पढ़ो,
	.ग_लिखो = safesetid_gid_file_ग_लिखो,
पूर्ण;

अटल पूर्णांक __init safesetid_init_securityfs(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा dentry *policy_dir;
	काष्ठा dentry *uid_policy_file;
	काष्ठा dentry *gid_policy_file;

	अगर (!safesetid_initialized)
		वापस 0;

	policy_dir = securityfs_create_dir("safesetid", शून्य);
	अगर (IS_ERR(policy_dir)) अणु
		ret = PTR_ERR(policy_dir);
		जाओ error;
	पूर्ण

	uid_policy_file = securityfs_create_file("uid_allowlist_policy", 0600,
			policy_dir, शून्य, &safesetid_uid_file_fops);
	अगर (IS_ERR(uid_policy_file)) अणु
		ret = PTR_ERR(uid_policy_file);
		जाओ error;
	पूर्ण

	gid_policy_file = securityfs_create_file("gid_allowlist_policy", 0600,
			policy_dir, शून्य, &safesetid_gid_file_fops);
	अगर (IS_ERR(gid_policy_file)) अणु
		ret = PTR_ERR(gid_policy_file);
		जाओ error;
	पूर्ण


	वापस 0;

error:
	securityfs_हटाओ(policy_dir);
	वापस ret;
पूर्ण
fs_initcall(safesetid_init_securityfs);
