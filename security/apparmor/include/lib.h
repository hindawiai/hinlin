<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor lib definitions
 *
 * 2017 Canonical Ltd.
 */

#अगर_अघोषित __AA_LIB_H
#घोषणा __AA_LIB_H

#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/lsm_hooks.h>

#समावेश "match.h"

/*
 * DEBUG reमुख्यs global (no per profile flag) since it is mostly used in sysctl
 * which is not related to profile accesses.
 */

#घोषणा DEBUG_ON (aa_g_debug)
#घोषणा dbg_prपूर्णांकk(__fmt, __args...) pr_debug(__fmt, ##__args)
#घोषणा AA_DEBUG(fmt, args...)						\
	करो अणु								\
		अगर (DEBUG_ON)						\
			pr_debug_ratelimited("AppArmor: " fmt, ##args);	\
	पूर्ण जबतक (0)

#घोषणा AA_WARN(X) WARN((X), "APPARMOR WARN %s: %s\n", __func__, #X)

#घोषणा AA_BUG(X, args...) AA_BUG_FMT((X), "" args)
#अगर_घोषित CONFIG_SECURITY_APPARMOR_DEBUG_ASSERTS
#घोषणा AA_BUG_FMT(X, fmt, args...)					\
	WARN((X), "AppArmor WARN %s: (" #X "): " fmt, __func__, ##args)
#अन्यथा
#घोषणा AA_BUG_FMT(X, fmt, args...)
#पूर्ण_अगर

#घोषणा AA_ERROR(fmt, args...)						\
	pr_err_ratelimited("AppArmor: " fmt, ##args)

/* Flag indicating whether initialization completed */
बाह्य पूर्णांक apparmor_initialized;

/* fn's in lib */
स्थिर अक्षर *skipn_spaces(स्थिर अक्षर *str, माप_प्रकार n);
अक्षर *aa_split_fqname(अक्षर *args, अक्षर **ns_name);
स्थिर अक्षर *aa_splitn_fqname(स्थिर अक्षर *fqname, माप_प्रकार n, स्थिर अक्षर **ns_name,
			     माप_प्रकार *ns_len);
व्योम aa_info_message(स्थिर अक्षर *str);

/* Security blob offsets */
बाह्य काष्ठा lsm_blob_sizes apparmor_blob_sizes;

/**
 * aa_strneq - compare null terminated @str to a non null terminated substring
 * @str: a null terminated string
 * @sub: a substring, not necessarily null terminated
 * @len: length of @sub to compare
 *
 * The @str string must be full consumed क्रम this to be considered a match
 */
अटल अंतरभूत bool aa_strneq(स्थिर अक्षर *str, स्थिर अक्षर *sub, पूर्णांक len)
अणु
	वापस !म_भेदन(str, sub, len) && !str[len];
पूर्ण

/**
 * aa_dfa_null_transition - step to next state after null अक्षरacter
 * @dfa: the dfa to match against
 * @start: the state of the dfa to start matching in
 *
 * aa_dfa_null_transition transitions to the next state after a null
 * अक्षरacter which is not used in standard matching and is only
 * used to separate pairs.
 */
अटल अंतरभूत अचिन्हित पूर्णांक aa_dfa_null_transition(काष्ठा aa_dfa *dfa,
						  अचिन्हित पूर्णांक start)
अणु
	/* the null transition only needs the string's null terminator byte */
	वापस aa_dfa_next(dfa, start, 0);
पूर्ण

अटल अंतरभूत bool path_mediated_fs(काष्ठा dentry *dentry)
अणु
	वापस !(dentry->d_sb->s_flags & SB_NOUSER);
पूर्ण


काष्ठा counted_str अणु
	काष्ठा kref count;
	अक्षर name[];
पूर्ण;

#घोषणा str_to_counted(str) \
	((काष्ठा counted_str *)(str - दुरत्व(काष्ठा counted_str, name)))

#घोषणा __counted	/* aपंचांग just a notation */

व्योम aa_str_kref(काष्ठा kref *kref);
अक्षर *aa_str_alloc(पूर्णांक size, gfp_t gfp);


अटल अंतरभूत __counted अक्षर *aa_get_str(__counted अक्षर *str)
अणु
	अगर (str)
		kref_get(&(str_to_counted(str)->count));

	वापस str;
पूर्ण

अटल अंतरभूत व्योम aa_put_str(__counted अक्षर *str)
अणु
	अगर (str)
		kref_put(&str_to_counted(str)->count, aa_str_kref);
पूर्ण


/* काष्ठा aa_policy - common part of both namespaces and profiles
 * @name: name of the object
 * @hname - The hierarchical name
 * @list: list policy object is on
 * @profiles: head of the profiles list contained in the object
 */
काष्ठा aa_policy अणु
	स्थिर अक्षर *name;
	__counted अक्षर *hname;
	काष्ठा list_head list;
	काष्ठा list_head profiles;
पूर्ण;

/**
 * basename - find the last component of an hname
 * @name: hname to find the base profile name component of  (NOT शून्य)
 *
 * Returns: the tail (base profile name) name component of an hname
 */
अटल अंतरभूत स्थिर अक्षर *basename(स्थिर अक्षर *hname)
अणु
	अक्षर *split;

	hname = strim((अक्षर *)hname);
	क्रम (split = म_माला(hname, "//"); split; split = म_माला(hname, "//"))
		hname = split + 2;

	वापस hname;
पूर्ण

/**
 * __policy_find - find a policy by @name on a policy list
 * @head: list to search  (NOT शून्य)
 * @name: name to search क्रम  (NOT शून्य)
 *
 * Requires: rcu_पढ़ो_lock be held
 *
 * Returns: unrefcounted policy that match @name or शून्य अगर not found
 */
अटल अंतरभूत काष्ठा aa_policy *__policy_find(काष्ठा list_head *head,
					      स्थिर अक्षर *name)
अणु
	काष्ठा aa_policy *policy;

	list_क्रम_each_entry_rcu(policy, head, list) अणु
		अगर (!म_भेद(policy->name, name))
			वापस policy;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * __policy_strn_find - find a policy that's name matches @len अक्षरs of @str
 * @head: list to search  (NOT शून्य)
 * @str: string to search क्रम  (NOT शून्य)
 * @len: length of match required
 *
 * Requires: rcu_पढ़ो_lock be held
 *
 * Returns: unrefcounted policy that match @str or शून्य अगर not found
 *
 * अगर @len == म_माप(@म_माप) then this is equiv to __policy_find
 * other wise it allows searching क्रम policy by a partial match of name
 */
अटल अंतरभूत काष्ठा aa_policy *__policy_strn_find(काष्ठा list_head *head,
					    स्थिर अक्षर *str, पूर्णांक len)
अणु
	काष्ठा aa_policy *policy;

	list_क्रम_each_entry_rcu(policy, head, list) अणु
		अगर (aa_strneq(policy->name, str, len))
			वापस policy;
	पूर्ण

	वापस शून्य;
पूर्ण

bool aa_policy_init(काष्ठा aa_policy *policy, स्थिर अक्षर *prefix,
		    स्थिर अक्षर *name, gfp_t gfp);
व्योम aa_policy_destroy(काष्ठा aa_policy *policy);


/*
 * fn_label_build - असलtract out the build of a label transition
 * @L: label the transition is being computed क्रम
 * @P: profile parameter derived from L by this macro, can be passed to FN
 * @GFP: memory allocation type to use
 * @FN: fn to call क्रम each profile transition. @P is set to the profile
 *
 * Returns: new label on success
 *          ERR_PTR अगर build @FN fails
 *          शून्य अगर label_build fails due to low memory conditions
 *
 * @FN must वापस a label or ERR_PTR on failure. शून्य is not allowed
 */
#घोषणा fn_label_build(L, P, GFP, FN)					\
(अणु									\
	__label__ __cleanup, __करोne;					\
	काष्ठा aa_label *__new_;					\
									\
	अगर ((L)->size > 1) अणु						\
		/* TODO: add cache of transitions alपढ़ोy करोne */	\
		काष्ठा label_it __i;					\
		पूर्णांक __j, __k, __count;					\
		DEFINE_VEC(label, __lvec);				\
		DEFINE_VEC(profile, __pvec);				\
		अगर (vec_setup(label, __lvec, (L)->size, (GFP)))	अणु	\
			__new_ = शून्य;					\
			जाओ __करोne;					\
		पूर्ण							\
		__j = 0;						\
		label_क्रम_each(__i, (L), (P)) अणु				\
			__new_ = (FN);					\
			AA_BUG(!__new_);				\
			अगर (IS_ERR(__new_))				\
				जाओ __cleanup;				\
			__lvec[__j++] = __new_;				\
		पूर्ण							\
		क्रम (__j = __count = 0; __j < (L)->size; __j++)		\
			__count += __lvec[__j]->size;			\
		अगर (!vec_setup(profile, __pvec, __count, (GFP))) अणु	\
			क्रम (__j = __k = 0; __j < (L)->size; __j++) अणु	\
				label_क्रम_each(__i, __lvec[__j], (P))	\
					__pvec[__k++] = aa_get_profile(P); \
			पूर्ण						\
			__count -= aa_vec_unique(__pvec, __count, 0);	\
			अगर (__count > 1) अणु				\
				__new_ = aa_vec_find_or_create_label(__pvec,\
						     __count, (GFP));	\
				/* only fails अगर out of Mem */		\
				अगर (!__new_)				\
					__new_ = शून्य;			\
			पूर्ण अन्यथा						\
				__new_ = aa_get_label(&__pvec[0]->label); \
			vec_cleanup(profile, __pvec, __count);		\
		पूर्ण अन्यथा							\
			__new_ = शून्य;					\
__cleanup:								\
		vec_cleanup(label, __lvec, (L)->size);			\
	पूर्ण अन्यथा अणु							\
		(P) = labels_profile(L);				\
		__new_ = (FN);						\
	पूर्ण								\
__करोne:									\
	अगर (!__new_)							\
		AA_DEBUG("label build failed\n");			\
	(__new_);							\
पूर्ण)


#घोषणा __fn_build_in_ns(NS, P, NS_FN, OTHER_FN)			\
(अणु									\
	काष्ठा aa_label *__new;						\
	अगर ((P)->ns != (NS))						\
		__new = (OTHER_FN);					\
	अन्यथा								\
		__new = (NS_FN);					\
	(__new);							\
पूर्ण)

#घोषणा fn_label_build_in_ns(L, P, GFP, NS_FN, OTHER_FN)		\
(अणु									\
	fn_label_build((L), (P), (GFP),					\
		__fn_build_in_ns(labels_ns(L), (P), (NS_FN), (OTHER_FN))); \
पूर्ण)

#पूर्ण_अगर /* __AA_LIB_H */
