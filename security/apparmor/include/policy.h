<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#अगर_अघोषित __AA_POLICY_H
#घोषणा __AA_POLICY_H

#समावेश <linux/capability.h>
#समावेश <linux/cred.h>
#समावेश <linux/kref.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>

#समावेश "apparmor.h"
#समावेश "audit.h"
#समावेश "capability.h"
#समावेश "domain.h"
#समावेश "file.h"
#समावेश "lib.h"
#समावेश "label.h"
#समावेश "net.h"
#समावेश "perms.h"
#समावेश "resource.h"


काष्ठा aa_ns;

बाह्य पूर्णांक unprivileged_userns_apparmor_policy;

बाह्य स्थिर अक्षर *स्थिर aa_profile_mode_names[];
#घोषणा APPARMOR_MODE_NAMES_MAX_INDEX 4

#घोषणा PROखाता_MODE(_profile, _mode)		\
	((aa_g_profile_mode == (_mode)) ||	\
	 ((_profile)->mode == (_mode)))

#घोषणा COMPLAIN_MODE(_profile)	PROखाता_MODE((_profile), APPARMOR_COMPLAIN)

#घोषणा KILL_MODE(_profile) PROखाता_MODE((_profile), APPARMOR_KILL)

#घोषणा PROखाता_IS_HAT(_profile) ((_profile)->label.flags & FLAG_HAT)

#घोषणा profile_is_stale(_profile) (label_is_stale(&(_profile)->label))

#घोषणा on_list_rcu(X) (!list_empty(X) && (X)->prev != LIST_POISON2)

/*
 * FIXME: currently need a clean way to replace and हटाओ profiles as a
 * set.  It should be करोne at the namespace level.
 * Either, with a set of profiles loaded at the namespace level or via
 * a mark and हटाओ marked पूर्णांकerface.
 */
क्रमागत profile_mode अणु
	APPARMOR_ENFORCE,	/* enक्रमce access rules */
	APPARMOR_COMPLAIN,	/* allow and log access violations */
	APPARMOR_KILL,		/* समाप्त task on access violation */
	APPARMOR_UNCONFINED,	/* profile set to unconfined */
पूर्ण;


/* काष्ठा aa_policydb - match engine क्रम a policy
 * dfa: dfa pattern match
 * start: set of start states क्रम the dअगरferent classes of data
 */
काष्ठा aa_policydb अणु
	/* Generic policy DFA specअगरic rule types will be subsections of it */
	काष्ठा aa_dfa *dfa;
	अचिन्हित पूर्णांक start[AA_CLASS_LAST + 1];

पूर्ण;

/* काष्ठा aa_data - generic data काष्ठाure
 * key: name क्रम retrieving this data
 * size: size of data in bytes
 * data: binary data
 * head: reserved क्रम rhashtable
 */
काष्ठा aa_data अणु
	अक्षर *key;
	u32 size;
	अक्षर *data;
	काष्ठा rhash_head head;
पूर्ण;


/* काष्ठा aa_profile - basic confinement data
 * @base - base components of the profile (name, refcount, lists, lock ...)
 * @label - label this profile is an extension of
 * @parent: parent of profile
 * @ns: namespace the profile is in
 * @नाम: optional profile name that this profile नामd
 * @attach: human पढ़ोable attachment string
 * @xmatch: optional extended matching क्रम unconfined executables names
 * @xmatch_len: xmatch prefix len, used to determine xmatch priority
 * @audit: the auditing mode of the profile
 * @mode: the enक्रमcement mode of the profile
 * @path_flags: flags controlling path generation behavior
 * @disconnected: what to prepend अगर attach_disconnected is specअगरied
 * @size: the memory consumed by this profiles rules
 * @policy: general match rules governing policy
 * @file: The set of rules governing basic file access and करोमुख्य transitions
 * @caps: capabilities क्रम the profile
 * @rlimits: rlimits क्रम the profile
 *
 * @dents: dentries क्रम the profiles file entries in apparmorfs
 * @स_नाम: name of the profile dir in apparmorfs
 * @data: hashtable क्रम मुक्त-क्रमm policy aa_data
 *
 * The AppArmor profile contains the basic confinement data.  Each profile
 * has a name, and exists in a namespace.  The @name and @exec_match are
 * used to determine profile attachment against unconfined tasks.  All other
 * attachments are determined by profile X transition rules.
 *
 * Profiles have a hierarchy where hats and children profiles keep
 * a reference to their parent.
 *
 * Profile names can not begin with a : and can not contain the \0
 * अक्षरacter.  If a profile name begins with / it will be considered when
 * determining profile attachment on "unconfined" tasks.
 */
काष्ठा aa_profile अणु
	काष्ठा aa_policy base;
	काष्ठा aa_profile __rcu *parent;

	काष्ठा aa_ns *ns;
	स्थिर अक्षर *नाम;

	स्थिर अक्षर *attach;
	काष्ठा aa_dfa *xmatch;
	पूर्णांक xmatch_len;
	क्रमागत audit_mode audit;
	दीर्घ mode;
	u32 path_flags;
	स्थिर अक्षर *disconnected;
	पूर्णांक size;

	काष्ठा aa_policydb policy;
	काष्ठा aa_file_rules file;
	काष्ठा aa_caps caps;

	पूर्णांक xattr_count;
	अक्षर **xattrs;

	काष्ठा aa_rlimit rlimits;

	पूर्णांक secmark_count;
	काष्ठा aa_secmark *secmark;

	काष्ठा aa_loaddata *rawdata;
	अचिन्हित अक्षर *hash;
	अक्षर *स_नाम;
	काष्ठा dentry *dents[AAFS_PROF_SIZखातापूर्ण];
	काष्ठा rhashtable *data;
	काष्ठा aa_label label;
पूर्ण;

बाह्य क्रमागत profile_mode aa_g_profile_mode;

#घोषणा AA_MAY_LOAD_POLICY	AA_MAY_APPEND
#घोषणा AA_MAY_REPLACE_POLICY	AA_MAY_WRITE
#घोषणा AA_MAY_REMOVE_POLICY	AA_MAY_DELETE

#घोषणा profiles_ns(P) ((P)->ns)
#घोषणा name_is_shared(A, B) ((A)->hname && (A)->hname == (B)->hname)

व्योम aa_add_profile(काष्ठा aa_policy *common, काष्ठा aa_profile *profile);


व्योम aa_मुक्त_proxy_kref(काष्ठा kref *kref);
काष्ठा aa_profile *aa_alloc_profile(स्थिर अक्षर *name, काष्ठा aa_proxy *proxy,
				    gfp_t gfp);
काष्ठा aa_profile *aa_new_null_profile(काष्ठा aa_profile *parent, bool hat,
				       स्थिर अक्षर *base, gfp_t gfp);
व्योम aa_मुक्त_profile(काष्ठा aa_profile *profile);
व्योम aa_मुक्त_profile_kref(काष्ठा kref *kref);
काष्ठा aa_profile *aa_find_child(काष्ठा aa_profile *parent, स्थिर अक्षर *name);
काष्ठा aa_profile *aa_lookupn_profile(काष्ठा aa_ns *ns, स्थिर अक्षर *hname,
				      माप_प्रकार n);
काष्ठा aa_profile *aa_lookup_profile(काष्ठा aa_ns *ns, स्थिर अक्षर *name);
काष्ठा aa_profile *aa_fqlookupn_profile(काष्ठा aa_label *base,
					स्थिर अक्षर *fqname, माप_प्रकार n);
काष्ठा aa_profile *aa_match_profile(काष्ठा aa_ns *ns, स्थिर अक्षर *name);

sमाप_प्रकार aa_replace_profiles(काष्ठा aa_ns *view, काष्ठा aa_label *label,
			    u32 mask, काष्ठा aa_loaddata *udata);
sमाप_प्रकार aa_हटाओ_profiles(काष्ठा aa_ns *view, काष्ठा aa_label *label,
			   अक्षर *name, माप_प्रकार size);
व्योम __aa_profile_list_release(काष्ठा list_head *head);

#घोषणा PROF_ADD 1
#घोषणा PROF_REPLACE 0

#घोषणा profile_unconfined(X) ((X)->mode == APPARMOR_UNCONFINED)

/**
 * aa_get_newest_profile - simple wrapper fn to wrap the label version
 * @p: profile (NOT शून्य)
 *
 * Returns refcount to newest version of the profile (maybe @p)
 *
 * Requires: @p must be held with a valid refcount
 */
अटल अंतरभूत काष्ठा aa_profile *aa_get_newest_profile(काष्ठा aa_profile *p)
अणु
	वापस labels_profile(aa_get_newest_label(&p->label));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक PROखाता_MEDIATES(काष्ठा aa_profile *profile,
					    अचिन्हित अक्षर class)
अणु
	अगर (class <= AA_CLASS_LAST)
		वापस profile->policy.start[class];
	अन्यथा
		वापस aa_dfa_match_len(profile->policy.dfa,
					profile->policy.start[0], &class, 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक PROखाता_MEDIATES_AF(काष्ठा aa_profile *profile,
					       u16 AF) अणु
	अचिन्हित पूर्णांक state = PROखाता_MEDIATES(profile, AA_CLASS_NET);
	__be16 be_af = cpu_to_be16(AF);

	अगर (!state)
		वापस 0;
	वापस aa_dfa_match_len(profile->policy.dfa, state, (अक्षर *) &be_af, 2);
पूर्ण

/**
 * aa_get_profile - increment refcount on profile @p
 * @p: profile  (MAYBE शून्य)
 *
 * Returns: poपूर्णांकer to @p अगर @p is शून्य will वापस शून्य
 * Requires: @p must be held with valid refcount when called
 */
अटल अंतरभूत काष्ठा aa_profile *aa_get_profile(काष्ठा aa_profile *p)
अणु
	अगर (p)
		kref_get(&(p->label.count));

	वापस p;
पूर्ण

/**
 * aa_get_profile_not0 - increment refcount on profile @p found via lookup
 * @p: profile  (MAYBE शून्य)
 *
 * Returns: poपूर्णांकer to @p अगर @p is शून्य will वापस शून्य
 * Requires: @p must be held with valid refcount when called
 */
अटल अंतरभूत काष्ठा aa_profile *aa_get_profile_not0(काष्ठा aa_profile *p)
अणु
	अगर (p && kref_get_unless_zero(&p->label.count))
		वापस p;

	वापस शून्य;
पूर्ण

/**
 * aa_get_profile_rcu - increment a refcount profile that can be replaced
 * @p: poपूर्णांकer to profile that can be replaced (NOT शून्य)
 *
 * Returns: poपूर्णांकer to a refcounted profile.
 *     अन्यथा शून्य अगर no profile
 */
अटल अंतरभूत काष्ठा aa_profile *aa_get_profile_rcu(काष्ठा aa_profile __rcu **p)
अणु
	काष्ठा aa_profile *c;

	rcu_पढ़ो_lock();
	करो अणु
		c = rcu_dereference(*p);
	पूर्ण जबतक (c && !kref_get_unless_zero(&c->label.count));
	rcu_पढ़ो_unlock();

	वापस c;
पूर्ण

/**
 * aa_put_profile - decrement refcount on profile @p
 * @p: profile  (MAYBE शून्य)
 */
अटल अंतरभूत व्योम aa_put_profile(काष्ठा aa_profile *p)
अणु
	अगर (p)
		kref_put(&p->label.count, aa_label_kref);
पूर्ण

अटल अंतरभूत पूर्णांक AUDIT_MODE(काष्ठा aa_profile *profile)
अणु
	अगर (aa_g_audit != AUDIT_NORMAL)
		वापस aa_g_audit;

	वापस profile->audit;
पूर्ण

bool policy_view_capable(काष्ठा aa_ns *ns);
bool policy_admin_capable(काष्ठा aa_ns *ns);
पूर्णांक aa_may_manage_policy(काष्ठा aa_label *label, काष्ठा aa_ns *ns,
			 u32 mask);

#पूर्ण_अगर /* __AA_POLICY_H */
