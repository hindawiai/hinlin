<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2017 Canonical Ltd.
 */

#अगर_अघोषित __AA_NAMESPACE_H
#घोषणा __AA_NAMESPACE_H

#समावेश <linux/kref.h>

#समावेश "apparmor.h"
#समावेश "apparmorfs.h"
#समावेश "label.h"
#समावेश "policy.h"


/* काष्ठा aa_ns_acct - accounting of profiles in namespace
 * @max_size: maximum space allowed क्रम all profiles in namespace
 * @max_count: maximum number of profiles that can be in this namespace
 * @size: current size of profiles
 * @count: current count of profiles (includes null profiles)
 */
काष्ठा aa_ns_acct अणु
	पूर्णांक max_size;
	पूर्णांक max_count;
	पूर्णांक size;
	पूर्णांक count;
पूर्ण;

/* काष्ठा aa_ns - namespace क्रम a set of profiles
 * @base: common policy
 * @parent: parent of namespace
 * @lock: lock क्रम modअगरying the object
 * @acct: accounting क्रम the namespace
 * @unconfined: special unconfined profile क्रम the namespace
 * @sub_ns: list of namespaces under the current namespace.
 * @uniq_null: uniq value used क्रम null learning profiles
 * @uniq_id: a unique id count क्रम the profiles in the namespace
 * @level: level of ns within the tree hierarchy
 * @dents: dentries क्रम the namespaces file entries in apparmorfs
 *
 * An aa_ns defines the set profiles that are searched to determine which
 * profile to attach to a task.  Profiles can not be shared between aa_ns
 * and profile names within a namespace are guaranteed to be unique.  When
 * profiles in separate namespaces have the same name they are NOT considered
 * to be equivalent.
 *
 * Namespaces are hierarchical and only namespaces and profiles below the
 * current namespace are visible.
 *
 * Namespace names must be unique and can not contain the अक्षरacters :/\0
 */
काष्ठा aa_ns अणु
	काष्ठा aa_policy base;
	काष्ठा aa_ns *parent;
	काष्ठा mutex lock;
	काष्ठा aa_ns_acct acct;
	काष्ठा aa_profile *unconfined;
	काष्ठा list_head sub_ns;
	atomic_t uniq_null;
	दीर्घ uniq_id;
	पूर्णांक level;
	दीर्घ revision;
	रुको_queue_head_t रुको;

	काष्ठा aa_labअन्यथाt labels;
	काष्ठा list_head rawdata_list;

	काष्ठा dentry *dents[AAFS_NS_SIZखातापूर्ण];
पूर्ण;

बाह्य काष्ठा aa_ns *root_ns;

बाह्य स्थिर अक्षर *aa_hidden_ns_name;

#घोषणा ns_unconfined(NS) (&(NS)->unconfined->label)

bool aa_ns_visible(काष्ठा aa_ns *curr, काष्ठा aa_ns *view, bool subns);
स्थिर अक्षर *aa_ns_name(काष्ठा aa_ns *parent, काष्ठा aa_ns *child, bool subns);
व्योम aa_मुक्त_ns(काष्ठा aa_ns *ns);
पूर्णांक aa_alloc_root_ns(व्योम);
व्योम aa_मुक्त_root_ns(व्योम);
व्योम aa_मुक्त_ns_kref(काष्ठा kref *kref);

काष्ठा aa_ns *aa_find_ns(काष्ठा aa_ns *root, स्थिर अक्षर *name);
काष्ठा aa_ns *aa_findn_ns(काष्ठा aa_ns *root, स्थिर अक्षर *name, माप_प्रकार n);
काष्ठा aa_ns *__aa_lookupn_ns(काष्ठा aa_ns *view, स्थिर अक्षर *hname, माप_प्रकार n);
काष्ठा aa_ns *aa_lookupn_ns(काष्ठा aa_ns *view, स्थिर अक्षर *name, माप_प्रकार n);
काष्ठा aa_ns *__aa_find_or_create_ns(काष्ठा aa_ns *parent, स्थिर अक्षर *name,
				     काष्ठा dentry *dir);
काष्ठा aa_ns *aa_prepare_ns(काष्ठा aa_ns *root, स्थिर अक्षर *name);
व्योम __aa_हटाओ_ns(काष्ठा aa_ns *ns);

अटल अंतरभूत काष्ठा aa_profile *aa_deref_parent(काष्ठा aa_profile *p)
अणु
	वापस rcu_dereference_रक्षित(p->parent,
					 mutex_is_locked(&p->ns->lock));
पूर्ण

/**
 * aa_get_ns - increment references count on @ns
 * @ns: namespace to increment reference count of (MAYBE शून्य)
 *
 * Returns: poपूर्णांकer to @ns, अगर @ns is शून्य वापसs शून्य
 * Requires: @ns must be held with valid refcount when called
 */
अटल अंतरभूत काष्ठा aa_ns *aa_get_ns(काष्ठा aa_ns *ns)
अणु
	अगर (ns)
		aa_get_profile(ns->unconfined);

	वापस ns;
पूर्ण

/**
 * aa_put_ns - decrement refcount on @ns
 * @ns: namespace to put reference of
 *
 * Decrement reference count of @ns and अगर no दीर्घer in use मुक्त it
 */
अटल अंतरभूत व्योम aa_put_ns(काष्ठा aa_ns *ns)
अणु
	अगर (ns)
		aa_put_profile(ns->unconfined);
पूर्ण

/**
 * __aa_findn_ns - find a namespace on a list by @name
 * @head: list to search क्रम namespace on  (NOT शून्य)
 * @name: name of namespace to look क्रम  (NOT शून्य)
 * @n: length of @name
 * Returns: unrefcounted namespace
 *
 * Requires: rcu_पढ़ो_lock be held
 */
अटल अंतरभूत काष्ठा aa_ns *__aa_findn_ns(काष्ठा list_head *head,
					  स्थिर अक्षर *name, माप_प्रकार n)
अणु
	वापस (काष्ठा aa_ns *)__policy_strn_find(head, name, n);
पूर्ण

अटल अंतरभूत काष्ठा aa_ns *__aa_find_ns(काष्ठा list_head *head,
					 स्थिर अक्षर *name)
अणु
	वापस __aa_findn_ns(head, name, म_माप(name));
पूर्ण

अटल अंतरभूत काष्ठा aa_ns *__aa_lookup_ns(काष्ठा aa_ns *base,
					   स्थिर अक्षर *hname)
अणु
	वापस __aa_lookupn_ns(base, hname, म_माप(hname));
पूर्ण

अटल अंतरभूत काष्ठा aa_ns *aa_lookup_ns(काष्ठा aa_ns *view, स्थिर अक्षर *name)
अणु
	वापस aa_lookupn_ns(view, name, म_माप(name));
पूर्ण

#पूर्ण_अगर /* AA_NAMESPACE_H */
