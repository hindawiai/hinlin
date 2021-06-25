<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy manipulation functions
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 *
 * AppArmor policy is based around profiles, which contain the rules a
 * task is confined by.  Every task in the प्रणाली has a profile attached
 * to it determined either by matching "unconfined" tasks against the
 * visible set of profiles or by following a profiles attachment rules.
 *
 * Each profile exists in a profile namespace which is a container of
 * visible profiles.  Each namespace contains a special "unconfined" profile,
 * which करोesn't enक्रमce any confinement on a task beyond DAC.
 *
 * Namespace and profile names can be written together in either
 * of two syntaxes.
 *	:namespace:profile - used by kernel पूर्णांकerfaces क्रम easy detection
 *	namespace://profile - used by policy
 *
 * Profile names can not start with : or @ or ^ and may not contain \0
 *
 * Reserved profile names
 *	unconfined - special स्वतःmatically generated unconfined profile
 *	inherit - special name to indicate profile inheritance
 *	null-XXXX-YYYY - special स्वतःmatically generated learning profiles
 *
 * Namespace names may not start with / or @ and may not contain \0 or :
 * Reserved namespace names
 *	user-XXXX - user defined profiles
 *
 * a // in a profile or namespace name indicates a hierarchical name with the
 * name beक्रमe the // being the parent and the name after the child.
 *
 * Profile and namespace hierarchies serve two dअगरferent but similar purposes.
 * The namespace contains the set of visible profiles that are considered
 * क्रम attachment.  The hierarchy of namespaces allows क्रम भवizing
 * the namespace so that क्रम example a chroot can have its own set of profiles
 * which may define some local user namespaces.
 * The profile hierarchy severs two distinct purposes,
 * -  it allows क्रम sub profiles or hats, which allows an application to run
 *    subprograms under its own profile with dअगरferent restriction than it
 *    self, and not have it use the प्रणाली profile.
 *    eg. अगर a mail program starts an editor, the policy might make the
 *        restrictions tighter on the editor tighter than the mail program,
 *        and definitely dअगरferent than general editor restrictions
 * - it allows क्रम binary hierarchy of profiles, so that execution history
 *   is preserved.  This feature isn't exploited by AppArmor reference policy
 *   but is allowed.  NOTE: this is currently suboptimal because profile
 *   aliasing is not currently implemented so that a profile क्रम each
 *   level must be defined.
 *   eg. /bin/bash///bin/ls as a name would indicate /bin/ls was started
 *       from /bin/bash
 *
 *   A profile or namespace name that can contain one or more // separators
 *   is referred to as an hname (hierarchical).
 *   eg.  /bin/bash//bin/ls
 *
 *   An fqname is a name that may contain both namespace and profile hnames.
 *   eg. :ns:/bin/bash//bin/ls
 *
 * NOTES:
 *   - locking of profile lists is currently fairly coarse.  All profile
 *     lists within a namespace use the namespace lock.
 * FIXME: move profile lists to using rcu_lists
 */

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/cred.h>
#समावेश <linux/rculist.h>
#समावेश <linux/user_namespace.h>

#समावेश "include/apparmor.h"
#समावेश "include/capability.h"
#समावेश "include/cred.h"
#समावेश "include/file.h"
#समावेश "include/ipc.h"
#समावेश "include/match.h"
#समावेश "include/path.h"
#समावेश "include/policy.h"
#समावेश "include/policy_ns.h"
#समावेश "include/policy_unpack.h"
#समावेश "include/resource.h"

पूर्णांक unprivileged_userns_apparmor_policy = 1;

स्थिर अक्षर *स्थिर aa_profile_mode_names[] = अणु
	"enforce",
	"complain",
	"kill",
	"unconfined",
पूर्ण;


/**
 * __add_profile - add a profiles to list and label tree
 * @list: list to add it to  (NOT शून्य)
 * @profile: the profile to add  (NOT शून्य)
 *
 * refcount @profile, should be put by __list_हटाओ_profile
 *
 * Requires: namespace lock be held, or list not be shared
 */
अटल व्योम __add_profile(काष्ठा list_head *list, काष्ठा aa_profile *profile)
अणु
	काष्ठा aa_label *l;

	AA_BUG(!list);
	AA_BUG(!profile);
	AA_BUG(!profile->ns);
	AA_BUG(!mutex_is_locked(&profile->ns->lock));

	list_add_rcu(&profile->base.list, list);
	/* get list reference */
	aa_get_profile(profile);
	l = aa_label_insert(&profile->ns->labels, &profile->label);
	AA_BUG(l != &profile->label);
	aa_put_label(l);
पूर्ण

/**
 * __list_हटाओ_profile - हटाओ a profile from the list it is on
 * @profile: the profile to हटाओ  (NOT शून्य)
 *
 * हटाओ a profile from the list, warning generally removal should
 * be करोne with __replace_profile as most profile removals are
 * replacements to the unconfined profile.
 *
 * put @profile list refcount
 *
 * Requires: namespace lock be held, or list not have been live
 */
अटल व्योम __list_हटाओ_profile(काष्ठा aa_profile *profile)
अणु
	AA_BUG(!profile);
	AA_BUG(!profile->ns);
	AA_BUG(!mutex_is_locked(&profile->ns->lock));

	list_del_rcu(&profile->base.list);
	aa_put_profile(profile);
पूर्ण

/**
 * __हटाओ_profile - हटाओ old profile, and children
 * @profile: profile to be replaced  (NOT शून्य)
 *
 * Requires: namespace list lock be held, or list not be shared
 */
अटल व्योम __हटाओ_profile(काष्ठा aa_profile *profile)
अणु
	AA_BUG(!profile);
	AA_BUG(!profile->ns);
	AA_BUG(!mutex_is_locked(&profile->ns->lock));

	/* release any children lists first */
	__aa_profile_list_release(&profile->base.profiles);
	/* released by मुक्त_profile */
	aa_label_हटाओ(&profile->label);
	__aafs_profile_सूची_हटाओ(profile);
	__list_हटाओ_profile(profile);
पूर्ण

/**
 * __aa_profile_list_release - हटाओ all profiles on the list and put refs
 * @head: list of profiles  (NOT शून्य)
 *
 * Requires: namespace lock be held
 */
व्योम __aa_profile_list_release(काष्ठा list_head *head)
अणु
	काष्ठा aa_profile *profile, *पंचांगp;
	list_क्रम_each_entry_safe(profile, पंचांगp, head, base.list)
		__हटाओ_profile(profile);
पूर्ण

/**
 * aa_मुक्त_data - मुक्त a data blob
 * @ptr: data to मुक्त
 * @arg: unused
 */
अटल व्योम aa_मुक्त_data(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा aa_data *data = ptr;

	kमुक्त_sensitive(data->data);
	kमुक्त_sensitive(data->key);
	kमुक्त_sensitive(data);
पूर्ण

/**
 * aa_मुक्त_profile - मुक्त a profile
 * @profile: the profile to मुक्त  (MAYBE शून्य)
 *
 * Free a profile, its hats and null_profile. All references to the profile,
 * its hats and null_profile must have been put.
 *
 * If the profile was referenced from a task context, मुक्त_profile() will
 * be called from an rcu callback routine, so we must not sleep here.
 */
व्योम aa_मुक्त_profile(काष्ठा aa_profile *profile)
अणु
	काष्ठा rhashtable *rht;
	पूर्णांक i;

	AA_DEBUG("%s(%p)\n", __func__, profile);

	अगर (!profile)
		वापस;

	/* मुक्त children profiles */
	aa_policy_destroy(&profile->base);
	aa_put_profile(rcu_access_poपूर्णांकer(profile->parent));

	aa_put_ns(profile->ns);
	kमुक्त_sensitive(profile->नाम);

	aa_मुक्त_file_rules(&profile->file);
	aa_मुक्त_cap_rules(&profile->caps);
	aa_मुक्त_rlimit_rules(&profile->rlimits);

	क्रम (i = 0; i < profile->xattr_count; i++)
		kमुक्त_sensitive(profile->xattrs[i]);
	kमुक्त_sensitive(profile->xattrs);
	क्रम (i = 0; i < profile->secmark_count; i++)
		kमुक्त_sensitive(profile->secmark[i].label);
	kमुक्त_sensitive(profile->secmark);
	kमुक्त_sensitive(profile->स_नाम);
	aa_put_dfa(profile->xmatch);
	aa_put_dfa(profile->policy.dfa);

	अगर (profile->data) अणु
		rht = profile->data;
		profile->data = शून्य;
		rhashtable_मुक्त_and_destroy(rht, aa_मुक्त_data, शून्य);
		kमुक्त_sensitive(rht);
	पूर्ण

	kमुक्त_sensitive(profile->hash);
	aa_put_loaddata(profile->rawdata);
	aa_label_destroy(&profile->label);

	kमुक्त_sensitive(profile);
पूर्ण

/**
 * aa_alloc_profile - allocate, initialize and वापस a new profile
 * @hname: name of the profile  (NOT शून्य)
 * @gfp: allocation type
 *
 * Returns: refcount profile or शून्य on failure
 */
काष्ठा aa_profile *aa_alloc_profile(स्थिर अक्षर *hname, काष्ठा aa_proxy *proxy,
				    gfp_t gfp)
अणु
	काष्ठा aa_profile *profile;

	/* मुक्तd by मुक्त_profile - usually through aa_put_profile */
	profile = kzalloc(माप(*profile) + माप(काष्ठा aa_profile *) * 2,
			  gfp);
	अगर (!profile)
		वापस शून्य;

	अगर (!aa_policy_init(&profile->base, शून्य, hname, gfp))
		जाओ fail;
	अगर (!aa_label_init(&profile->label, 1, gfp))
		जाओ fail;

	/* update being set needed by fs पूर्णांकerface */
	अगर (!proxy) अणु
		proxy = aa_alloc_proxy(&profile->label, gfp);
		अगर (!proxy)
			जाओ fail;
	पूर्ण अन्यथा
		aa_get_proxy(proxy);
	profile->label.proxy = proxy;

	profile->label.hname = profile->base.hname;
	profile->label.flags |= FLAG_PROखाता;
	profile->label.vec[0] = profile;

	/* refcount released by caller */
	वापस profile;

fail:
	aa_मुक्त_profile(profile);

	वापस शून्य;
पूर्ण

/* TODO: profile accounting - setup in हटाओ */

/**
 * __strn_find_child - find a profile on @head list using substring of @name
 * @head: list to search  (NOT शून्य)
 * @name: name of profile (NOT शून्य)
 * @len: length of @name substring to match
 *
 * Requires: rcu_पढ़ो_lock be held
 *
 * Returns: unrefcounted profile ptr, or शून्य अगर not found
 */
अटल काष्ठा aa_profile *__strn_find_child(काष्ठा list_head *head,
					    स्थिर अक्षर *name, पूर्णांक len)
अणु
	वापस (काष्ठा aa_profile *)__policy_strn_find(head, name, len);
पूर्ण

/**
 * __find_child - find a profile on @head list with a name matching @name
 * @head: list to search  (NOT शून्य)
 * @name: name of profile (NOT शून्य)
 *
 * Requires: rcu_पढ़ो_lock be held
 *
 * Returns: unrefcounted profile ptr, or शून्य अगर not found
 */
अटल काष्ठा aa_profile *__find_child(काष्ठा list_head *head, स्थिर अक्षर *name)
अणु
	वापस __strn_find_child(head, name, म_माप(name));
पूर्ण

/**
 * aa_find_child - find a profile by @name in @parent
 * @parent: profile to search  (NOT शून्य)
 * @name: profile name to search क्रम  (NOT शून्य)
 *
 * Returns: a refcounted profile or शून्य अगर not found
 */
काष्ठा aa_profile *aa_find_child(काष्ठा aa_profile *parent, स्थिर अक्षर *name)
अणु
	काष्ठा aa_profile *profile;

	rcu_पढ़ो_lock();
	करो अणु
		profile = __find_child(&parent->base.profiles, name);
	पूर्ण जबतक (profile && !aa_get_profile_not0(profile));
	rcu_पढ़ो_unlock();

	/* refcount released by caller */
	वापस profile;
पूर्ण

/**
 * __lookup_parent - lookup the parent of a profile of name @hname
 * @ns: namespace to lookup profile in  (NOT शून्य)
 * @hname: hierarchical profile name to find parent of  (NOT शून्य)
 *
 * Lookups up the parent of a fully qualअगरied profile name, the profile
 * that matches hname करोes not need to exist, in general this
 * is used to load a new profile.
 *
 * Requires: rcu_पढ़ो_lock be held
 *
 * Returns: unrefcounted policy or शून्य अगर not found
 */
अटल काष्ठा aa_policy *__lookup_parent(काष्ठा aa_ns *ns,
					 स्थिर अक्षर *hname)
अणु
	काष्ठा aa_policy *policy;
	काष्ठा aa_profile *profile = शून्य;
	अक्षर *split;

	policy = &ns->base;

	क्रम (split = म_माला(hname, "//"); split;) अणु
		profile = __strn_find_child(&policy->profiles, hname,
					    split - hname);
		अगर (!profile)
			वापस शून्य;
		policy = &profile->base;
		hname = split + 2;
		split = म_माला(hname, "//");
	पूर्ण
	अगर (!profile)
		वापस &ns->base;
	वापस &profile->base;
पूर्ण

/**
 * __lookupn_profile - lookup the profile matching @hname
 * @base: base list to start looking up profile name from  (NOT शून्य)
 * @hname: hierarchical profile name  (NOT शून्य)
 * @n: length of @hname
 *
 * Requires: rcu_पढ़ो_lock be held
 *
 * Returns: unrefcounted profile poपूर्णांकer or शून्य अगर not found
 *
 * Do a relative name lookup, recursing through profile tree.
 */
अटल काष्ठा aa_profile *__lookupn_profile(काष्ठा aa_policy *base,
					    स्थिर अक्षर *hname, माप_प्रकार n)
अणु
	काष्ठा aa_profile *profile = शून्य;
	स्थिर अक्षर *split;

	क्रम (split = strnstr(hname, "//", n); split;
	     split = strnstr(hname, "//", n)) अणु
		profile = __strn_find_child(&base->profiles, hname,
					    split - hname);
		अगर (!profile)
			वापस शून्य;

		base = &profile->base;
		n -= split + 2 - hname;
		hname = split + 2;
	पूर्ण

	अगर (n)
		वापस __strn_find_child(&base->profiles, hname, n);
	वापस शून्य;
पूर्ण

अटल काष्ठा aa_profile *__lookup_profile(काष्ठा aa_policy *base,
					   स्थिर अक्षर *hname)
अणु
	वापस __lookupn_profile(base, hname, म_माप(hname));
पूर्ण

/**
 * aa_lookup_profile - find a profile by its full or partial name
 * @ns: the namespace to start from (NOT शून्य)
 * @hname: name to करो lookup on.  Does not contain namespace prefix (NOT शून्य)
 * @n: size of @hname
 *
 * Returns: refcounted profile or शून्य अगर not found
 */
काष्ठा aa_profile *aa_lookupn_profile(काष्ठा aa_ns *ns, स्थिर अक्षर *hname,
				      माप_प्रकार n)
अणु
	काष्ठा aa_profile *profile;

	rcu_पढ़ो_lock();
	करो अणु
		profile = __lookupn_profile(&ns->base, hname, n);
	पूर्ण जबतक (profile && !aa_get_profile_not0(profile));
	rcu_पढ़ो_unlock();

	/* the unconfined profile is not in the regular profile list */
	अगर (!profile && म_भेदन(hname, "unconfined", n) == 0)
		profile = aa_get_newest_profile(ns->unconfined);

	/* refcount released by caller */
	वापस profile;
पूर्ण

काष्ठा aa_profile *aa_lookup_profile(काष्ठा aa_ns *ns, स्थिर अक्षर *hname)
अणु
	वापस aa_lookupn_profile(ns, hname, म_माप(hname));
पूर्ण

काष्ठा aa_profile *aa_fqlookupn_profile(काष्ठा aa_label *base,
					स्थिर अक्षर *fqname, माप_प्रकार n)
अणु
	काष्ठा aa_profile *profile;
	काष्ठा aa_ns *ns;
	स्थिर अक्षर *name, *ns_name;
	माप_प्रकार ns_len;

	name = aa_splitn_fqname(fqname, n, &ns_name, &ns_len);
	अगर (ns_name) अणु
		ns = aa_lookupn_ns(labels_ns(base), ns_name, ns_len);
		अगर (!ns)
			वापस शून्य;
	पूर्ण अन्यथा
		ns = aa_get_ns(labels_ns(base));

	अगर (name)
		profile = aa_lookupn_profile(ns, name, n - (name - fqname));
	अन्यथा अगर (ns)
		/* शेष profile क्रम ns, currently unconfined */
		profile = aa_get_newest_profile(ns->unconfined);
	अन्यथा
		profile = शून्य;
	aa_put_ns(ns);

	वापस profile;
पूर्ण

/**
 * aa_new_null_profile - create or find a null-X learning profile
 * @parent: profile that caused this profile to be created (NOT शून्य)
 * @hat: true अगर the null- learning profile is a hat
 * @base: name to base the null profile off of
 * @gfp: type of allocation
 *
 * Find/Create a null- complain mode profile used in learning mode.  The
 * name of the profile is unique and follows the क्रमmat of parent//null-XXX.
 * where XXX is based on the @name or अगर that fails or is not supplied
 * a unique number
 *
 * null profiles are added to the profile list but the list करोes not
 * hold a count on them so that they are स्वतःmatically released when
 * not in use.
 *
 * Returns: new refcounted profile अन्यथा शून्य on failure
 */
काष्ठा aa_profile *aa_new_null_profile(काष्ठा aa_profile *parent, bool hat,
				       स्थिर अक्षर *base, gfp_t gfp)
अणु
	काष्ठा aa_profile *p, *profile;
	स्थिर अक्षर *bname;
	अक्षर *name = शून्य;

	AA_BUG(!parent);

	अगर (base) अणु
		name = kदो_स्मृति(म_माप(parent->base.hname) + 8 + म_माप(base),
			       gfp);
		अगर (name) अणु
			प्र_लिखो(name, "%s//null-%s", parent->base.hname, base);
			जाओ name;
		पूर्ण
		/* fall through to try लघुer uniq */
	पूर्ण

	name = kदो_स्मृति(म_माप(parent->base.hname) + 2 + 7 + 8, gfp);
	अगर (!name)
		वापस शून्य;
	प्र_लिखो(name, "%s//null-%x", parent->base.hname,
		atomic_inc_वापस(&parent->ns->uniq_null));

name:
	/* lookup to see अगर this is a dup creation */
	bname = basename(name);
	profile = aa_find_child(parent, bname);
	अगर (profile)
		जाओ out;

	profile = aa_alloc_profile(name, शून्य, gfp);
	अगर (!profile)
		जाओ fail;

	profile->mode = APPARMOR_COMPLAIN;
	profile->label.flags |= FLAG_शून्य;
	अगर (hat)
		profile->label.flags |= FLAG_HAT;
	profile->path_flags = parent->path_flags;

	/* released on मुक्त_profile */
	rcu_assign_poपूर्णांकer(profile->parent, aa_get_profile(parent));
	profile->ns = aa_get_ns(parent->ns);
	profile->file.dfa = aa_get_dfa(nulldfa);
	profile->policy.dfa = aa_get_dfa(nulldfa);

	mutex_lock_nested(&profile->ns->lock, profile->ns->level);
	p = __find_child(&parent->base.profiles, bname);
	अगर (p) अणु
		aa_मुक्त_profile(profile);
		profile = aa_get_profile(p);
	पूर्ण अन्यथा अणु
		__add_profile(&parent->base.profiles, profile);
	पूर्ण
	mutex_unlock(&profile->ns->lock);

	/* refcount released by caller */
out:
	kमुक्त(name);

	वापस profile;

fail:
	kमुक्त(name);
	aa_मुक्त_profile(profile);
	वापस शून्य;
पूर्ण

/**
 * replacement_allowed - test to see अगर replacement is allowed
 * @profile: profile to test अगर it can be replaced  (MAYBE शून्य)
 * @noreplace: true अगर replacement shouldn't be allowed but addition is okay
 * @info: Returns - info about why replacement failed (NOT शून्य)
 *
 * Returns: %0 अगर replacement allowed अन्यथा error code
 */
अटल पूर्णांक replacement_allowed(काष्ठा aa_profile *profile, पूर्णांक noreplace,
			       स्थिर अक्षर **info)
अणु
	अगर (profile) अणु
		अगर (profile->label.flags & FLAG_IMMUTIBLE) अणु
			*info = "cannot replace immutable profile";
			वापस -EPERM;
		पूर्ण अन्यथा अगर (noreplace) अणु
			*info = "profile already exists";
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* audit callback क्रम net specअगरic fields */
अटल व्योम audit_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	अगर (aad(sa)->अगरace.ns) अणु
		audit_log_क्रमmat(ab, " ns=");
		audit_log_untrustedstring(ab, aad(sa)->अगरace.ns);
	पूर्ण
पूर्ण

/**
 * audit_policy - Do auditing of policy changes
 * @label: label to check अगर it can manage policy
 * @op: policy operation being perक्रमmed
 * @ns_name: name of namespace being manipulated
 * @name: name of profile being manipulated (NOT शून्य)
 * @info: any extra inक्रमmation to be audited (MAYBE शून्य)
 * @error: error code
 *
 * Returns: the error to be वापसed after audit is करोne
 */
अटल पूर्णांक audit_policy(काष्ठा aa_label *label, स्थिर अक्षर *op,
			स्थिर अक्षर *ns_name, स्थिर अक्षर *name,
			स्थिर अक्षर *info, पूर्णांक error)
अणु
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, op);

	aad(&sa)->अगरace.ns = ns_name;
	aad(&sa)->name = name;
	aad(&sa)->info = info;
	aad(&sa)->error = error;
	aad(&sa)->label = label;

	aa_audit_msg(AUDIT_APPARMOR_STATUS, &sa, audit_cb);

	वापस error;
पूर्ण

/**
 * policy_view_capable - check अगर viewing policy in at @ns is allowed
 * ns: namespace being viewed by current task (may be शून्य)
 * Returns: true अगर viewing policy is allowed
 *
 * If @ns is शून्य then the namespace being viewed is assumed to be the
 * tasks current namespace.
 */
bool policy_view_capable(काष्ठा aa_ns *ns)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	काष्ठा aa_ns *view_ns = aa_get_current_ns();
	bool root_in_user_ns = uid_eq(current_euid(), make_kuid(user_ns, 0)) ||
			       in_egroup_p(make_kgid(user_ns, 0));
	bool response = false;
	अगर (!ns)
		ns = view_ns;

	अगर (root_in_user_ns && aa_ns_visible(view_ns, ns, true) &&
	    (user_ns == &init_user_ns ||
	     (unprivileged_userns_apparmor_policy != 0 &&
	      user_ns->level == view_ns->level)))
		response = true;
	aa_put_ns(view_ns);

	वापस response;
पूर्ण

bool policy_admin_capable(काष्ठा aa_ns *ns)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	bool capable = ns_capable(user_ns, CAP_MAC_ADMIN);

	AA_DEBUG("cap_mac_admin? %d\n", capable);
	AA_DEBUG("policy locked? %d\n", aa_g_lock_policy);

	वापस policy_view_capable(ns) && capable && !aa_g_lock_policy;
पूर्ण

/**
 * aa_may_manage_policy - can the current task manage policy
 * @label: label to check अगर it can manage policy
 * @op: the policy manipulation operation being करोne
 *
 * Returns: 0 अगर the task is allowed to manipulate policy अन्यथा error
 */
पूर्णांक aa_may_manage_policy(काष्ठा aa_label *label, काष्ठा aa_ns *ns, u32 mask)
अणु
	स्थिर अक्षर *op;

	अगर (mask & AA_MAY_REMOVE_POLICY)
		op = OP_PROF_RM;
	अन्यथा अगर (mask & AA_MAY_REPLACE_POLICY)
		op = OP_PROF_REPL;
	अन्यथा
		op = OP_PROF_LOAD;

	/* check अगर loading policy is locked out */
	अगर (aa_g_lock_policy)
		वापस audit_policy(label, op, शून्य, शून्य, "policy_locked",
				    -EACCES);

	अगर (!policy_admin_capable(ns))
		वापस audit_policy(label, op, शून्य, शून्य, "not policy admin",
				    -EACCES);

	/* TODO: add fine grained mediation of policy loads */
	वापस 0;
पूर्ण

अटल काष्ठा aa_profile *__list_lookup_parent(काष्ठा list_head *lh,
					       काष्ठा aa_profile *profile)
अणु
	स्थिर अक्षर *base = basename(profile->base.hname);
	दीर्घ len = base - profile->base.hname;
	काष्ठा aa_load_ent *ent;

	/* parent won't have trailing // so हटाओ from len */
	अगर (len <= 2)
		वापस शून्य;
	len -= 2;

	list_क्रम_each_entry(ent, lh, list) अणु
		अगर (ent->new == profile)
			जारी;
		अगर (म_भेदन(ent->new->base.hname, profile->base.hname, len) ==
		    0 && ent->new->base.hname[len] == 0)
			वापस ent->new;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __replace_profile - replace @old with @new on a list
 * @old: profile to be replaced  (NOT शून्य)
 * @new: profile to replace @old with  (NOT शून्य)
 * @share_proxy: transfer @old->proxy to @new
 *
 * Will duplicate and refcount elements that @new inherits from @old
 * and will inherit @old children.
 *
 * refcount @new क्रम list, put @old list refcount
 *
 * Requires: namespace list lock be held, or list not be shared
 */
अटल व्योम __replace_profile(काष्ठा aa_profile *old, काष्ठा aa_profile *new)
अणु
	काष्ठा aa_profile *child, *पंचांगp;

	अगर (!list_empty(&old->base.profiles)) अणु
		LIST_HEAD(lh);
		list_splice_init_rcu(&old->base.profiles, &lh, synchronize_rcu);

		list_क्रम_each_entry_safe(child, पंचांगp, &lh, base.list) अणु
			काष्ठा aa_profile *p;

			list_del_init(&child->base.list);
			p = __find_child(&new->base.profiles, child->base.name);
			अगर (p) अणु
				/* @p replaces @child  */
				__replace_profile(child, p);
				जारी;
			पूर्ण

			/* inherit @child and its children */
			/* TODO: update hname of inherited children */
			/* list refcount transferred to @new */
			p = aa_deref_parent(child);
			rcu_assign_poपूर्णांकer(child->parent, aa_get_profile(new));
			list_add_rcu(&child->base.list, &new->base.profiles);
			aa_put_profile(p);
		पूर्ण
	पूर्ण

	अगर (!rcu_access_poपूर्णांकer(new->parent)) अणु
		काष्ठा aa_profile *parent = aa_deref_parent(old);
		rcu_assign_poपूर्णांकer(new->parent, aa_get_profile(parent));
	पूर्ण
	aa_label_replace(&old->label, &new->label);
	/* migrate dents must come after label replacement b/c update */
	__aafs_profile_migrate_dents(old, new);

	अगर (list_empty(&new->base.list)) अणु
		/* new is not on a list alपढ़ोy */
		list_replace_rcu(&old->base.list, &new->base.list);
		aa_get_profile(new);
		aa_put_profile(old);
	पूर्ण अन्यथा
		__list_हटाओ_profile(old);
पूर्ण

/**
 * __lookup_replace - lookup replacement inक्रमmation क्रम a profile
 * @ns - namespace the lookup occurs in
 * @hname - name of profile to lookup
 * @noreplace - true अगर not replacing an existing profile
 * @p - Returns: profile to be replaced
 * @info - Returns: info string on why lookup failed
 *
 * Returns: profile to replace (no ref) on success अन्यथा ptr error
 */
अटल पूर्णांक __lookup_replace(काष्ठा aa_ns *ns, स्थिर अक्षर *hname,
			    bool noreplace, काष्ठा aa_profile **p,
			    स्थिर अक्षर **info)
अणु
	*p = aa_get_profile(__lookup_profile(&ns->base, hname));
	अगर (*p) अणु
		पूर्णांक error = replacement_allowed(*p, noreplace, info);
		अगर (error) अणु
			*info = "profile can not be replaced";
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम share_name(काष्ठा aa_profile *old, काष्ठा aa_profile *new)
अणु
	aa_put_str(new->base.hname);
	aa_get_str(old->base.hname);
	new->base.hname = old->base.hname;
	new->base.name = old->base.name;
	new->label.hname = old->label.hname;
पूर्ण

/* Update to newest version of parent after previous replacements
 * Returns: unrefcount newest version of parent
 */
अटल काष्ठा aa_profile *update_to_newest_parent(काष्ठा aa_profile *new)
अणु
	काष्ठा aa_profile *parent, *newest;

	parent = rcu_dereference_रक्षित(new->parent,
					   mutex_is_locked(&new->ns->lock));
	newest = aa_get_newest_profile(parent);

	/* parent replaced in this atomic set? */
	अगर (newest != parent) अणु
		aa_put_profile(parent);
		rcu_assign_poपूर्णांकer(new->parent, newest);
	पूर्ण अन्यथा
		aa_put_profile(newest);

	वापस newest;
पूर्ण

/**
 * aa_replace_profiles - replace profile(s) on the profile list
 * @policy_ns: namespace load is occurring on
 * @label: label that is attempting to load/replace policy
 * @mask: permission mask
 * @udata: serialized data stream  (NOT शून्य)
 *
 * unpack and replace a profile on the profile list and uses of that profile
 * by any task creds via invalidating the old version of the profile, which
 * tasks will notice to update their own cred.  If the profile करोes not exist
 * on the profile list it is added.
 *
 * Returns: size of data consumed अन्यथा error code on failure.
 */
sमाप_प्रकार aa_replace_profiles(काष्ठा aa_ns *policy_ns, काष्ठा aa_label *label,
			    u32 mask, काष्ठा aa_loaddata *udata)
अणु
	स्थिर अक्षर *ns_name = शून्य, *info = शून्य;
	काष्ठा aa_ns *ns = शून्य;
	काष्ठा aa_load_ent *ent, *पंचांगp;
	काष्ठा aa_loaddata *rawdata_ent;
	स्थिर अक्षर *op;
	sमाप_प्रकार count, error;
	LIST_HEAD(lh);

	op = mask & AA_MAY_REPLACE_POLICY ? OP_PROF_REPL : OP_PROF_LOAD;
	aa_get_loaddata(udata);
	/* released below */
	error = aa_unpack(udata, &lh, &ns_name);
	अगर (error)
		जाओ out;

	/* ensure that profiles are all क्रम the same ns
	 * TODO: update locking to हटाओ this स्थिरaपूर्णांक. All profiles in
	 *       the load set must succeed as a set or the load will
	 *       fail. Sort ent list and take ns locks in hierarchy order
	 */
	count = 0;
	list_क्रम_each_entry(ent, &lh, list) अणु
		अगर (ns_name) अणु
			अगर (ent->ns_name &&
			    म_भेद(ent->ns_name, ns_name) != 0) अणु
				info = "policy load has mixed namespaces";
				error = -EACCES;
				जाओ fail;
			पूर्ण
		पूर्ण अन्यथा अगर (ent->ns_name) अणु
			अगर (count) अणु
				info = "policy load has mixed namespaces";
				error = -EACCES;
				जाओ fail;
			पूर्ण
			ns_name = ent->ns_name;
		पूर्ण अन्यथा
			count++;
	पूर्ण
	अगर (ns_name) अणु
		ns = aa_prepare_ns(policy_ns ? policy_ns : labels_ns(label),
				   ns_name);
		अगर (IS_ERR(ns)) अणु
			op = OP_PROF_LOAD;
			info = "failed to prepare namespace";
			error = PTR_ERR(ns);
			ns = शून्य;
			ent = शून्य;
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा
		ns = aa_get_ns(policy_ns ? policy_ns : labels_ns(label));

	mutex_lock_nested(&ns->lock, ns->level);
	/* check क्रम duplicate rawdata blobs: space and file dedup */
	list_क्रम_each_entry(rawdata_ent, &ns->rawdata_list, list) अणु
		अगर (aa_rawdata_eq(rawdata_ent, udata)) अणु
			काष्ठा aa_loaddata *पंचांगp;

			पंचांगp = __aa_get_loaddata(rawdata_ent);
			/* check we didn't fail the race */
			अगर (पंचांगp) अणु
				aa_put_loaddata(udata);
				udata = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/* setup parent and ns info */
	list_क्रम_each_entry(ent, &lh, list) अणु
		काष्ठा aa_policy *policy;

		ent->new->rawdata = aa_get_loaddata(udata);
		error = __lookup_replace(ns, ent->new->base.hname,
					 !(mask & AA_MAY_REPLACE_POLICY),
					 &ent->old, &info);
		अगर (error)
			जाओ fail_lock;

		अगर (ent->new->नाम) अणु
			error = __lookup_replace(ns, ent->new->नाम,
						!(mask & AA_MAY_REPLACE_POLICY),
						&ent->नाम, &info);
			अगर (error)
				जाओ fail_lock;
		पूर्ण

		/* released when @new is मुक्तd */
		ent->new->ns = aa_get_ns(ns);

		अगर (ent->old || ent->नाम)
			जारी;

		/* no ref on policy only use inside lock */
		policy = __lookup_parent(ns, ent->new->base.hname);
		अगर (!policy) अणु
			काष्ठा aa_profile *p;
			p = __list_lookup_parent(&lh, ent->new);
			अगर (!p) अणु
				error = -ENOENT;
				info = "parent does not exist";
				जाओ fail_lock;
			पूर्ण
			rcu_assign_poपूर्णांकer(ent->new->parent, aa_get_profile(p));
		पूर्ण अन्यथा अगर (policy != &ns->base) अणु
			/* released on profile replacement or मुक्त_profile */
			काष्ठा aa_profile *p = (काष्ठा aa_profile *) policy;
			rcu_assign_poपूर्णांकer(ent->new->parent, aa_get_profile(p));
		पूर्ण
	पूर्ण

	/* create new fs entries क्रम पूर्णांकrospection अगर needed */
	अगर (!udata->dents[AAFS_LOADDATA_सूची]) अणु
		error = __aa_fs_create_rawdata(ns, udata);
		अगर (error) अणु
			info = "failed to create raw_data dir and files";
			ent = शून्य;
			जाओ fail_lock;
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(ent, &lh, list) अणु
		अगर (!ent->old) अणु
			काष्ठा dentry *parent;
			अगर (rcu_access_poपूर्णांकer(ent->new->parent)) अणु
				काष्ठा aa_profile *p;
				p = aa_deref_parent(ent->new);
				parent = prof_child_dir(p);
			पूर्ण अन्यथा
				parent = ns_subprofs_dir(ent->new->ns);
			error = __aafs_profile_सूची_गढ़ो(ent->new, parent);
		पूर्ण

		अगर (error) अणु
			info = "failed to create";
			जाओ fail_lock;
		पूर्ण
	पूर्ण

	/* Done with checks that may fail - करो actual replacement */
	__aa_bump_ns_revision(ns);
	__aa_loaddata_update(udata, ns->revision);
	list_क्रम_each_entry_safe(ent, पंचांगp, &lh, list) अणु
		list_del_init(&ent->list);
		op = (!ent->old && !ent->नाम) ? OP_PROF_LOAD : OP_PROF_REPL;

		अगर (ent->old && ent->old->rawdata == ent->new->rawdata) अणु
			/* dedup actual profile replacement */
			audit_policy(label, op, ns_name, ent->new->base.hname,
				     "same as current profile, skipping",
				     error);
			/* अवरोध refcount cycle with proxy. */
			aa_put_proxy(ent->new->label.proxy);
			ent->new->label.proxy = शून्य;
			जाओ skip;
		पूर्ण

		/*
		 * TODO: finer dedup based on profile range in data. Load set
		 * can dअगरfer but profile may reमुख्य unchanged
		 */
		audit_policy(label, op, ns_name, ent->new->base.hname, शून्य,
			     error);

		अगर (ent->old) अणु
			share_name(ent->old, ent->new);
			__replace_profile(ent->old, ent->new);
		पूर्ण अन्यथा अणु
			काष्ठा list_head *lh;

			अगर (rcu_access_poपूर्णांकer(ent->new->parent)) अणु
				काष्ठा aa_profile *parent;

				parent = update_to_newest_parent(ent->new);
				lh = &parent->base.profiles;
			पूर्ण अन्यथा
				lh = &ns->base.profiles;
			__add_profile(lh, ent->new);
		पूर्ण
	skip:
		aa_load_ent_मुक्त(ent);
	पूर्ण
	__aa_labअन्यथाt_update_subtree(ns);
	mutex_unlock(&ns->lock);

out:
	aa_put_ns(ns);
	aa_put_loaddata(udata);
	kमुक्त(ns_name);

	अगर (error)
		वापस error;
	वापस udata->size;

fail_lock:
	mutex_unlock(&ns->lock);

	/* audit cause of failure */
	op = (ent && !ent->old) ? OP_PROF_LOAD : OP_PROF_REPL;
fail:
	  audit_policy(label, op, ns_name, ent ? ent->new->base.hname : शून्य,
		       info, error);
	/* audit status that rest of profiles in the atomic set failed too */
	info = "valid profile in failed atomic policy load";
	list_क्रम_each_entry(पंचांगp, &lh, list) अणु
		अगर (पंचांगp == ent) अणु
			info = "unchecked profile in failed atomic policy load";
			/* skip entry that caused failure */
			जारी;
		पूर्ण
		op = (!पंचांगp->old) ? OP_PROF_LOAD : OP_PROF_REPL;
		audit_policy(label, op, ns_name, पंचांगp->new->base.hname, info,
			     error);
	पूर्ण
	list_क्रम_each_entry_safe(ent, पंचांगp, &lh, list) अणु
		list_del_init(&ent->list);
		aa_load_ent_मुक्त(ent);
	पूर्ण

	जाओ out;
पूर्ण

/**
 * aa_हटाओ_profiles - हटाओ profile(s) from the प्रणाली
 * @policy_ns: namespace the हटाओ is being करोne from
 * @subj: label attempting to हटाओ policy
 * @fqname: name of the profile or namespace to हटाओ  (NOT शून्य)
 * @size: size of the name
 *
 * Remove a profile or sub namespace from the current namespace, so that
 * they can not be found anymore and mark them as replaced by unconfined
 *
 * NOTE: removing confinement करोes not restore rlimits to preconfinement values
 *
 * Returns: size of data consume अन्यथा error code अगर fails
 */
sमाप_प्रकार aa_हटाओ_profiles(काष्ठा aa_ns *policy_ns, काष्ठा aa_label *subj,
			   अक्षर *fqname, माप_प्रकार size)
अणु
	काष्ठा aa_ns *ns = शून्य;
	काष्ठा aa_profile *profile = शून्य;
	स्थिर अक्षर *name = fqname, *info = शून्य;
	स्थिर अक्षर *ns_name = शून्य;
	sमाप_प्रकार error = 0;

	अगर (*fqname == 0) अणु
		info = "no profile specified";
		error = -ENOENT;
		जाओ fail;
	पूर्ण

	अगर (fqname[0] == ':') अणु
		माप_प्रकार ns_len;

		name = aa_splitn_fqname(fqname, size, &ns_name, &ns_len);
		/* released below */
		ns = aa_lookupn_ns(policy_ns ? policy_ns : labels_ns(subj),
				   ns_name, ns_len);
		अगर (!ns) अणु
			info = "namespace does not exist";
			error = -ENOENT;
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा
		/* released below */
		ns = aa_get_ns(policy_ns ? policy_ns : labels_ns(subj));

	अगर (!name) अणु
		/* हटाओ namespace - can only happen अगर fqname[0] == ':' */
		mutex_lock_nested(&ns->parent->lock, ns->level);
		__aa_bump_ns_revision(ns);
		__aa_हटाओ_ns(ns);
		mutex_unlock(&ns->parent->lock);
	पूर्ण अन्यथा अणु
		/* हटाओ profile */
		mutex_lock_nested(&ns->lock, ns->level);
		profile = aa_get_profile(__lookup_profile(&ns->base, name));
		अगर (!profile) अणु
			error = -ENOENT;
			info = "profile does not exist";
			जाओ fail_ns_lock;
		पूर्ण
		name = profile->base.hname;
		__aa_bump_ns_revision(ns);
		__हटाओ_profile(profile);
		__aa_labअन्यथाt_update_subtree(ns);
		mutex_unlock(&ns->lock);
	पूर्ण

	/* करोn't fail removal अगर audit fails */
	(व्योम) audit_policy(subj, OP_PROF_RM, ns_name, name, info,
			    error);
	aa_put_ns(ns);
	aa_put_profile(profile);
	वापस size;

fail_ns_lock:
	mutex_unlock(&ns->lock);
	aa_put_ns(ns);

fail:
	(व्योम) audit_policy(subj, OP_PROF_RM, ns_name, name, info,
			    error);
	वापस error;
पूर्ण
