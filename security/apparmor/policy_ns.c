<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy manipulation functions
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2017 Canonical Ltd.
 *
 * AppArmor policy namespaces, allow क्रम dअगरferent sets of policies
 * to be loaded क्रम tasks within the namespace.
 */

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "include/apparmor.h"
#समावेश "include/cred.h"
#समावेश "include/policy_ns.h"
#समावेश "include/label.h"
#समावेश "include/policy.h"

/* root profile namespace */
काष्ठा aa_ns *root_ns;
स्थिर अक्षर *aa_hidden_ns_name = "---";

/**
 * aa_ns_visible - test अगर @view is visible from @curr
 * @curr: namespace to treat as the parent (NOT शून्य)
 * @view: namespace to test अगर visible from @curr (NOT शून्य)
 * @subns: whether view of a subns is allowed
 *
 * Returns: true अगर @view is visible from @curr अन्यथा false
 */
bool aa_ns_visible(काष्ठा aa_ns *curr, काष्ठा aa_ns *view, bool subns)
अणु
	अगर (curr == view)
		वापस true;

	अगर (!subns)
		वापस false;

	क्रम ( ; view; view = view->parent) अणु
		अगर (view->parent == curr)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * aa_na_name - Find the ns name to display क्रम @view from @curr
 * @curr - current namespace (NOT शून्य)
 * @view - namespace attempting to view (NOT शून्य)
 * @subns - are subns visible
 *
 * Returns: name of @view visible from @curr
 */
स्थिर अक्षर *aa_ns_name(काष्ठा aa_ns *curr, काष्ठा aa_ns *view, bool subns)
अणु
	/* अगर view == curr then the namespace name isn't displayed */
	अगर (curr == view)
		वापस "";

	अगर (aa_ns_visible(curr, view, subns)) अणु
		/* at this poपूर्णांक अगर a ns is visible it is in a view ns
		 * thus the curr ns.hname is a prefix of its name.
		 * Only output the भवized portion of the name
		 * Add + 2 to skip over // separating curr hname prefix
		 * from the visible tail of the views hname
		 */
		वापस view->base.hname + म_माप(curr->base.hname) + 2;
	पूर्ण

	वापस aa_hidden_ns_name;
पूर्ण

/**
 * alloc_ns - allocate, initialize and वापस a new namespace
 * @prefix: parent namespace name (MAYBE शून्य)
 * @name: a pपुनः_स्मृतिated name  (NOT शून्य)
 *
 * Returns: refcounted namespace or शून्य on failure.
 */
अटल काष्ठा aa_ns *alloc_ns(स्थिर अक्षर *prefix, स्थिर अक्षर *name)
अणु
	काष्ठा aa_ns *ns;

	ns = kzalloc(माप(*ns), GFP_KERNEL);
	AA_DEBUG("%s(%p)\n", __func__, ns);
	अगर (!ns)
		वापस शून्य;
	अगर (!aa_policy_init(&ns->base, prefix, name, GFP_KERNEL))
		जाओ fail_ns;

	INIT_LIST_HEAD(&ns->sub_ns);
	INIT_LIST_HEAD(&ns->rawdata_list);
	mutex_init(&ns->lock);
	init_रुकोqueue_head(&ns->रुको);

	/* released by aa_मुक्त_ns() */
	ns->unconfined = aa_alloc_profile("unconfined", शून्य, GFP_KERNEL);
	अगर (!ns->unconfined)
		जाओ fail_unconfined;

	ns->unconfined->label.flags |= FLAG_IX_ON_NAME_ERROR |
		FLAG_IMMUTIBLE | FLAG_NS_COUNT | FLAG_UNCONFINED;
	ns->unconfined->mode = APPARMOR_UNCONFINED;
	ns->unconfined->file.dfa = aa_get_dfa(nulldfa);
	ns->unconfined->policy.dfa = aa_get_dfa(nulldfa);

	/* ns and ns->unconfined share ns->unconfined refcount */
	ns->unconfined->ns = ns;

	atomic_set(&ns->uniq_null, 0);

	aa_labअन्यथाt_init(&ns->labels);

	वापस ns;

fail_unconfined:
	kमुक्त_sensitive(ns->base.hname);
fail_ns:
	kमुक्त_sensitive(ns);
	वापस शून्य;
पूर्ण

/**
 * aa_मुक्त_ns - मुक्त a profile namespace
 * @ns: the namespace to मुक्त  (MAYBE शून्य)
 *
 * Requires: All references to the namespace must have been put, अगर the
 *           namespace was referenced by a profile confining a task,
 */
व्योम aa_मुक्त_ns(काष्ठा aa_ns *ns)
अणु
	अगर (!ns)
		वापस;

	aa_policy_destroy(&ns->base);
	aa_labअन्यथाt_destroy(&ns->labels);
	aa_put_ns(ns->parent);

	ns->unconfined->ns = शून्य;
	aa_मुक्त_profile(ns->unconfined);
	kमुक्त_sensitive(ns);
पूर्ण

/**
 * aa_findn_ns  -  look up a profile namespace on the namespace list
 * @root: namespace to search in  (NOT शून्य)
 * @name: name of namespace to find  (NOT शून्य)
 * @n: length of @name
 *
 * Returns: a refcounted namespace on the list, or शून्य अगर no namespace
 *          called @name exists.
 *
 * refcount released by caller
 */
काष्ठा aa_ns *aa_findn_ns(काष्ठा aa_ns *root, स्थिर अक्षर *name, माप_प्रकार n)
अणु
	काष्ठा aa_ns *ns = शून्य;

	rcu_पढ़ो_lock();
	ns = aa_get_ns(__aa_findn_ns(&root->sub_ns, name, n));
	rcu_पढ़ो_unlock();

	वापस ns;
पूर्ण

/**
 * aa_find_ns  -  look up a profile namespace on the namespace list
 * @root: namespace to search in  (NOT शून्य)
 * @name: name of namespace to find  (NOT शून्य)
 *
 * Returns: a refcounted namespace on the list, or शून्य अगर no namespace
 *          called @name exists.
 *
 * refcount released by caller
 */
काष्ठा aa_ns *aa_find_ns(काष्ठा aa_ns *root, स्थिर अक्षर *name)
अणु
	वापस aa_findn_ns(root, name, म_माप(name));
पूर्ण

/**
 * __aa_lookupn_ns - lookup the namespace matching @hname
 * @base: base list to start looking up profile name from  (NOT शून्य)
 * @hname: hierarchical ns name  (NOT शून्य)
 * @n: length of @hname
 *
 * Requires: rcu_पढ़ो_lock be held
 *
 * Returns: unrefcounted ns poपूर्णांकer or शून्य अगर not found
 *
 * Do a relative name lookup, recursing through profile tree.
 */
काष्ठा aa_ns *__aa_lookupn_ns(काष्ठा aa_ns *view, स्थिर अक्षर *hname, माप_प्रकार n)
अणु
	काष्ठा aa_ns *ns = view;
	स्थिर अक्षर *split;

	क्रम (split = strnstr(hname, "//", n); split;
	     split = strnstr(hname, "//", n)) अणु
		ns = __aa_findn_ns(&ns->sub_ns, hname, split - hname);
		अगर (!ns)
			वापस शून्य;

		n -= split + 2 - hname;
		hname = split + 2;
	पूर्ण

	अगर (n)
		वापस __aa_findn_ns(&ns->sub_ns, hname, n);
	वापस शून्य;
पूर्ण

/**
 * aa_lookupn_ns  -  look up a policy namespace relative to @view
 * @view: namespace to search in  (NOT शून्य)
 * @name: name of namespace to find  (NOT शून्य)
 * @n: length of @name
 *
 * Returns: a refcounted namespace on the list, or शून्य अगर no namespace
 *          called @name exists.
 *
 * refcount released by caller
 */
काष्ठा aa_ns *aa_lookupn_ns(काष्ठा aa_ns *view, स्थिर अक्षर *name, माप_प्रकार n)
अणु
	काष्ठा aa_ns *ns = शून्य;

	rcu_पढ़ो_lock();
	ns = aa_get_ns(__aa_lookupn_ns(view, name, n));
	rcu_पढ़ो_unlock();

	वापस ns;
पूर्ण

अटल काष्ठा aa_ns *__aa_create_ns(काष्ठा aa_ns *parent, स्थिर अक्षर *name,
				    काष्ठा dentry *dir)
अणु
	काष्ठा aa_ns *ns;
	पूर्णांक error;

	AA_BUG(!parent);
	AA_BUG(!name);
	AA_BUG(!mutex_is_locked(&parent->lock));

	ns = alloc_ns(parent->base.hname, name);
	अगर (!ns)
		वापस ERR_PTR(-ENOMEM);
	ns->level = parent->level + 1;
	mutex_lock_nested(&ns->lock, ns->level);
	error = __aafs_ns_सूची_गढ़ो(ns, ns_subns_dir(parent), name, dir);
	अगर (error) अणु
		AA_ERROR("Failed to create interface for ns %s\n",
			 ns->base.name);
		mutex_unlock(&ns->lock);
		aa_मुक्त_ns(ns);
		वापस ERR_PTR(error);
	पूर्ण
	ns->parent = aa_get_ns(parent);
	list_add_rcu(&ns->base.list, &parent->sub_ns);
	/* add list ref */
	aa_get_ns(ns);
	mutex_unlock(&ns->lock);

	वापस ns;
पूर्ण

/**
 * aa_create_ns - create an ns, fail अगर it alपढ़ोy exists
 * @parent: the parent of the namespace being created
 * @name: the name of the namespace
 * @dir: अगर not null the dir to put the ns entries in
 *
 * Returns: the a refcounted ns that has been add or an ERR_PTR
 */
काष्ठा aa_ns *__aa_find_or_create_ns(काष्ठा aa_ns *parent, स्थिर अक्षर *name,
				     काष्ठा dentry *dir)
अणु
	काष्ठा aa_ns *ns;

	AA_BUG(!mutex_is_locked(&parent->lock));

	/* try and find the specअगरied ns */
	/* released by caller */
	ns = aa_get_ns(__aa_find_ns(&parent->sub_ns, name));
	अगर (!ns)
		ns = __aa_create_ns(parent, name, dir);
	अन्यथा
		ns = ERR_PTR(-EEXIST);

	/* वापस ref */
	वापस ns;
पूर्ण

/**
 * aa_prepare_ns - find an existing or create a new namespace of @name
 * @parent: ns to treat as parent
 * @name: the namespace to find or add  (NOT शून्य)
 *
 * Returns: refcounted namespace or PTR_ERR अगर failed to create one
 */
काष्ठा aa_ns *aa_prepare_ns(काष्ठा aa_ns *parent, स्थिर अक्षर *name)
अणु
	काष्ठा aa_ns *ns;

	mutex_lock_nested(&parent->lock, parent->level);
	/* try and find the specअगरied ns and अगर it करोesn't exist create it */
	/* released by caller */
	ns = aa_get_ns(__aa_find_ns(&parent->sub_ns, name));
	अगर (!ns)
		ns = __aa_create_ns(parent, name, शून्य);
	mutex_unlock(&parent->lock);

	/* वापस ref */
	वापस ns;
पूर्ण

अटल व्योम __ns_list_release(काष्ठा list_head *head);

/**
 * destroy_ns - हटाओ everything contained by @ns
 * @ns: namespace to have it contents हटाओd  (NOT शून्य)
 */
अटल व्योम destroy_ns(काष्ठा aa_ns *ns)
अणु
	अगर (!ns)
		वापस;

	mutex_lock_nested(&ns->lock, ns->level);
	/* release all profiles in this namespace */
	__aa_profile_list_release(&ns->base.profiles);

	/* release all sub namespaces */
	__ns_list_release(&ns->sub_ns);

	अगर (ns->parent) अणु
		अचिन्हित दीर्घ flags;

		ग_लिखो_lock_irqsave(&ns->labels.lock, flags);
		__aa_proxy_redirect(ns_unconfined(ns),
				    ns_unconfined(ns->parent));
		ग_लिखो_unlock_irqrestore(&ns->labels.lock, flags);
	पूर्ण
	__aafs_ns_सूची_हटाओ(ns);
	mutex_unlock(&ns->lock);
पूर्ण

/**
 * __aa_हटाओ_ns - हटाओ a namespace and all its children
 * @ns: namespace to be हटाओd  (NOT शून्य)
 *
 * Requires: ns->parent->lock be held and ns हटाओd from parent.
 */
व्योम __aa_हटाओ_ns(काष्ठा aa_ns *ns)
अणु
	/* हटाओ ns from namespace list */
	list_del_rcu(&ns->base.list);
	destroy_ns(ns);
	aa_put_ns(ns);
पूर्ण

/**
 * __ns_list_release - हटाओ all profile namespaces on the list put refs
 * @head: list of profile namespaces  (NOT शून्य)
 *
 * Requires: namespace lock be held
 */
अटल व्योम __ns_list_release(काष्ठा list_head *head)
अणु
	काष्ठा aa_ns *ns, *पंचांगp;

	list_क्रम_each_entry_safe(ns, पंचांगp, head, base.list)
		__aa_हटाओ_ns(ns);

पूर्ण

/**
 * aa_alloc_root_ns - allocate the root profile namespace
 *
 * Returns: %0 on success अन्यथा error
 *
 */
पूर्णांक __init aa_alloc_root_ns(व्योम)
अणु
	/* released by aa_मुक्त_root_ns - used as list ref*/
	root_ns = alloc_ns(शून्य, "root");
	अगर (!root_ns)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

 /**
  * aa_मुक्त_root_ns - मुक्त the root profile namespace
  */
व्योम __init aa_मुक्त_root_ns(व्योम)
अणु
	 काष्ठा aa_ns *ns = root_ns;

	 root_ns = शून्य;

	 destroy_ns(ns);
	 aa_put_ns(ns);
पूर्ण
