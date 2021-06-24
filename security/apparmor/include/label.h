<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor label definitions
 *
 * Copyright 2017 Canonical Ltd.
 */

#अगर_अघोषित __AA_LABEL_H
#घोषणा __AA_LABEL_H

#समावेश <linux/atomic.h>
#समावेश <linux/audit.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rcupdate.h>

#समावेश "apparmor.h"
#समावेश "lib.h"

काष्ठा aa_ns;

#घोषणा LOCAL_VEC_ENTRIES 8
#घोषणा DEFINE_VEC(T, V)						\
	काष्ठा aa_ ## T *(_ ## V ## _localपंचांगp)[LOCAL_VEC_ENTRIES];	\
	काष्ठा aa_ ## T **(V)

#घोषणा vec_setup(T, V, N, GFP)						\
(अणु									\
	अगर ((N) <= LOCAL_VEC_ENTRIES) अणु					\
		typeof(N) i;						\
		(V) = (_ ## V ## _localपंचांगp);				\
		क्रम (i = 0; i < (N); i++)				\
			(V)[i] = शून्य;					\
	पूर्ण अन्यथा								\
		(V) = kzalloc(माप(काष्ठा aa_ ## T *) * (N), (GFP));	\
	(V) ? 0 : -ENOMEM;						\
पूर्ण)

#घोषणा vec_cleanup(T, V, N)						\
करो अणु									\
	पूर्णांक i;								\
	क्रम (i = 0; i < (N); i++) अणु					\
		अगर (!IS_ERR_OR_शून्य((V)[i]))				\
			aa_put_ ## T((V)[i]);				\
	पूर्ण								\
	अगर ((V) != _ ## V ## _localपंचांगp)					\
		kमुक्त(V);						\
पूर्ण जबतक (0)

#घोषणा vec_last(VEC, SIZE) ((VEC)[(SIZE) - 1])
#घोषणा vec_ns(VEC, SIZE) (vec_last((VEC), (SIZE))->ns)
#घोषणा vec_labअन्यथाt(VEC, SIZE) (&vec_ns((VEC), (SIZE))->labels)
#घोषणा cleanup_करोमुख्य_vec(V, L) cleanup_label_vec((V), (L)->size)

काष्ठा aa_profile;
#घोषणा VEC_FLAG_TERMINATE 1
पूर्णांक aa_vec_unique(काष्ठा aa_profile **vec, पूर्णांक n, पूर्णांक flags);
काष्ठा aa_label *aa_vec_find_or_create_label(काष्ठा aa_profile **vec, पूर्णांक len,
					     gfp_t gfp);
#घोषणा aa_sort_and_merge_vec(N, V) \
	aa_sort_and_merge_profiles((N), (काष्ठा aa_profile **)(V))


/* काष्ठा aa_labअन्यथाt - set of labels क्रम a namespace
 *
 * Labels are reference counted; aa_labअन्यथाt करोes not contribute to label
 * reference counts. Once a label's last refcount is put it is हटाओd from
 * the set.
 */
काष्ठा aa_labअन्यथाt अणु
	rwlock_t lock;

	काष्ठा rb_root root;
पूर्ण;

#घोषणा __labअन्यथाt_क्रम_each(LS, N) \
	क्रम ((N) = rb_first(&(LS)->root); (N); (N) = rb_next(N))

व्योम aa_labअन्यथाt_destroy(काष्ठा aa_labअन्यथाt *ls);
व्योम aa_labअन्यथाt_init(काष्ठा aa_labअन्यथाt *ls);


क्रमागत label_flags अणु
	FLAG_HAT = 1,			/* profile is a hat */
	FLAG_UNCONFINED = 2,		/* label unconfined only अगर all */
	FLAG_शून्य = 4,			/* profile is null learning profile */
	FLAG_IX_ON_NAME_ERROR = 8,	/* fallback to ix on name lookup fail */
	FLAG_IMMUTIBLE = 0x10,		/* करोn't allow changes/replacement */
	FLAG_USER_DEFINED = 0x20,	/* user based profile - lower privs */
	FLAG_NO_LIST_REF = 0x40,	/* list करोesn't keep profile ref */
	FLAG_NS_COUNT = 0x80,		/* carries NS ref count */
	FLAG_IN_TREE = 0x100,		/* label is in tree */
	FLAG_PROखाता = 0x200,		/* label is a profile */
	FLAG_EXPLICIT = 0x400,		/* explicit अटल label */
	FLAG_STALE = 0x800,		/* replaced/हटाओd */
	FLAG_RENAMED = 0x1000,		/* label has renaming in it */
	FLAG_REVOKED = 0x2000,		/* label has revocation in it */

	/* These flags must correspond with PATH_flags */
	/* TODO: add new path flags */
पूर्ण;

काष्ठा aa_label;
काष्ठा aa_proxy अणु
	काष्ठा kref count;
	काष्ठा aa_label __rcu *label;
पूर्ण;

काष्ठा label_it अणु
	पूर्णांक i, j;
पूर्ण;

/* काष्ठा aa_label - lazy labeling काष्ठा
 * @count: ref count of active users
 * @node: rbtree position
 * @rcu: rcu callback काष्ठा
 * @proxy: is set to the label that replaced this label
 * @hname: text representation of the label (MAYBE_शून्य)
 * @flags: stale and other flags - values may change under label set lock
 * @secid: secid that references this label
 * @size: number of entries in @ent[]
 * @ent: set of profiles क्रम label, actual size determined by @size
 */
काष्ठा aa_label अणु
	काष्ठा kref count;
	काष्ठा rb_node node;
	काष्ठा rcu_head rcu;
	काष्ठा aa_proxy *proxy;
	__counted अक्षर *hname;
	दीर्घ flags;
	u32 secid;
	पूर्णांक size;
	काष्ठा aa_profile *vec[];
पूर्ण;

#घोषणा last_error(E, FN)				\
करो अणु							\
	पूर्णांक __subE = (FN);				\
	अगर (__subE)					\
		(E) = __subE;				\
पूर्ण जबतक (0)

#घोषणा label_isprofile(X) ((X)->flags & FLAG_PROखाता)
#घोषणा label_unconfined(X) ((X)->flags & FLAG_UNCONFINED)
#घोषणा unconfined(X) label_unconfined(X)
#घोषणा label_is_stale(X) ((X)->flags & FLAG_STALE)
#घोषणा __label_make_stale(X) ((X)->flags |= FLAG_STALE)
#घोषणा labels_ns(X) (vec_ns(&((X)->vec[0]), (X)->size))
#घोषणा labels_set(X) (&labels_ns(X)->labels)
#घोषणा labels_profile(X) ((X)->vec[(X)->size - 1])


पूर्णांक aa_label_next_confined(काष्ठा aa_label *l, पूर्णांक i);

/* क्रम each profile in a label */
#घोषणा label_क्रम_each(I, L, P)						\
	क्रम ((I).i = 0; ((P) = (L)->vec[(I).i]); ++((I).i))

/* assumes अवरोध/जाओ ended label_क्रम_each */
#घोषणा label_क्रम_each_cont(I, L, P)					\
	क्रम (++((I).i); ((P) = (L)->vec[(I).i]); ++((I).i))

#घोषणा next_comb(I, L1, L2)						\
करो अणु									\
	(I).j++;							\
	अगर ((I).j >= (L2)->size) अणु					\
		(I).i++;						\
		(I).j = 0;						\
	पूर्ण								\
पूर्ण जबतक (0)


/* क्रम each combination of P1 in L1, and P2 in L2 */
#घोषणा label_क्रम_each_comb(I, L1, L2, P1, P2)				\
क्रम ((I).i = (I).j = 0;							\
	((P1) = (L1)->vec[(I).i]) && ((P2) = (L2)->vec[(I).j]);		\
	(I) = next_comb(I, L1, L2))

#घोषणा fn_क्रम_each_comb(L1, L2, P1, P2, FN)				\
(अणु									\
	काष्ठा label_it i;						\
	पूर्णांक __E = 0;							\
	label_क्रम_each_comb(i, (L1), (L2), (P1), (P2)) अणु		\
		last_error(__E, (FN));					\
	पूर्ण								\
	__E;								\
पूर्ण)

/* क्रम each profile that is enक्रमcing confinement in a label */
#घोषणा label_क्रम_each_confined(I, L, P)				\
	क्रम ((I).i = aa_label_next_confined((L), 0);			\
	     ((P) = (L)->vec[(I).i]);					\
	     (I).i = aa_label_next_confined((L), (I).i + 1))

#घोषणा label_क्रम_each_in_merge(I, A, B, P)				\
	क्रम ((I).i = (I).j = 0;						\
	     ((P) = aa_label_next_in_merge(&(I), (A), (B)));		\
	     )

#घोषणा label_क्रम_each_not_in_set(I, SET, SUB, P)			\
	क्रम ((I).i = (I).j = 0;						\
	     ((P) = __aa_label_next_not_in_set(&(I), (SET), (SUB)));	\
	     )

#घोषणा next_in_ns(i, NS, L)						\
(अणु									\
	typeof(i) ___i = (i);						\
	जबतक ((L)->vec[___i] && (L)->vec[___i]->ns != (NS))		\
		(___i)++;						\
	(___i);								\
पूर्ण)

#घोषणा label_क्रम_each_in_ns(I, NS, L, P)				\
	क्रम ((I).i = next_in_ns(0, (NS), (L));				\
	     ((P) = (L)->vec[(I).i]);					\
	     (I).i = next_in_ns((I).i + 1, (NS), (L)))

#घोषणा fn_क्रम_each_in_ns(L, P, FN)					\
(अणु									\
	काष्ठा label_it __i;						\
	काष्ठा aa_ns *__ns = labels_ns(L);				\
	पूर्णांक __E = 0;							\
	label_क्रम_each_in_ns(__i, __ns, (L), (P)) अणु			\
		last_error(__E, (FN));					\
	पूर्ण								\
	__E;								\
पूर्ण)


#घोषणा fn_क्रम_each_XXX(L, P, FN, ...)					\
(अणु									\
	काष्ठा label_it i;						\
	पूर्णांक __E = 0;							\
	label_क्रम_each ## __VA_ARGS__(i, (L), (P)) अणु			\
		last_error(__E, (FN));					\
	पूर्ण								\
	__E;								\
पूर्ण)

#घोषणा fn_क्रम_each(L, P, FN) fn_क्रम_each_XXX(L, P, FN)
#घोषणा fn_क्रम_each_confined(L, P, FN) fn_क्रम_each_XXX(L, P, FN, _confined)

#घोषणा fn_क्रम_each2_XXX(L1, L2, P, FN, ...)				\
(अणु									\
	काष्ठा label_it i;						\
	पूर्णांक __E = 0;							\
	label_क्रम_each ## __VA_ARGS__(i, (L1), (L2), (P)) अणु		\
		last_error(__E, (FN));					\
	पूर्ण								\
	__E;								\
पूर्ण)

#घोषणा fn_क्रम_each_in_merge(L1, L2, P, FN)				\
	fn_क्रम_each2_XXX((L1), (L2), P, FN, _in_merge)
#घोषणा fn_क्रम_each_not_in_set(L1, L2, P, FN)				\
	fn_क्रम_each2_XXX((L1), (L2), P, FN, _not_in_set)

#घोषणा LABEL_MEDIATES(L, C)						\
(अणु									\
	काष्ठा aa_profile *profile;					\
	काष्ठा label_it i;						\
	पूर्णांक ret = 0;							\
	label_क्रम_each(i, (L), profile) अणु				\
		अगर (PROखाता_MEDIATES(profile, (C))) अणु			\
			ret = 1;					\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	ret;								\
पूर्ण)


व्योम aa_labअन्यथाt_destroy(काष्ठा aa_labअन्यथाt *ls);
व्योम aa_labअन्यथाt_init(काष्ठा aa_labअन्यथाt *ls);
व्योम __aa_labअन्यथाt_update_subtree(काष्ठा aa_ns *ns);

व्योम aa_label_destroy(काष्ठा aa_label *label);
व्योम aa_label_मुक्त(काष्ठा aa_label *label);
व्योम aa_label_kref(काष्ठा kref *kref);
bool aa_label_init(काष्ठा aa_label *label, पूर्णांक size, gfp_t gfp);
काष्ठा aa_label *aa_label_alloc(पूर्णांक size, काष्ठा aa_proxy *proxy, gfp_t gfp);

bool aa_label_is_subset(काष्ठा aa_label *set, काष्ठा aa_label *sub);
bool aa_label_is_unconfined_subset(काष्ठा aa_label *set, काष्ठा aa_label *sub);
काष्ठा aa_profile *__aa_label_next_not_in_set(काष्ठा label_it *I,
					     काष्ठा aa_label *set,
					     काष्ठा aa_label *sub);
bool aa_label_हटाओ(काष्ठा aa_label *label);
काष्ठा aa_label *aa_label_insert(काष्ठा aa_labअन्यथाt *ls, काष्ठा aa_label *l);
bool aa_label_replace(काष्ठा aa_label *old, काष्ठा aa_label *new);
bool aa_label_make_newest(काष्ठा aa_labअन्यथाt *ls, काष्ठा aa_label *old,
			  काष्ठा aa_label *new);

काष्ठा aa_label *aa_label_find(काष्ठा aa_label *l);

काष्ठा aa_profile *aa_label_next_in_merge(काष्ठा label_it *I,
					  काष्ठा aa_label *a,
					  काष्ठा aa_label *b);
काष्ठा aa_label *aa_label_find_merge(काष्ठा aa_label *a, काष्ठा aa_label *b);
काष्ठा aa_label *aa_label_merge(काष्ठा aa_label *a, काष्ठा aa_label *b,
				gfp_t gfp);


bool aa_update_label_name(काष्ठा aa_ns *ns, काष्ठा aa_label *label, gfp_t gfp);

#घोषणा FLAGS_NONE 0
#घोषणा FLAG_SHOW_MODE 1
#घोषणा FLAG_VIEW_SUBNS 2
#घोषणा FLAG_HIDDEN_UNCONFINED 4
#घोषणा FLAG_ABS_ROOT 8
पूर्णांक aa_label_snxprपूर्णांक(अक्षर *str, माप_प्रकार size, काष्ठा aa_ns *view,
		      काष्ठा aa_label *label, पूर्णांक flags);
पूर्णांक aa_label_asxprपूर्णांक(अक्षर **strp, काष्ठा aa_ns *ns, काष्ठा aa_label *label,
		      पूर्णांक flags, gfp_t gfp);
पूर्णांक aa_label_acntsxprपूर्णांक(अक्षर __counted **strp, काष्ठा aa_ns *ns,
			 काष्ठा aa_label *label, पूर्णांक flags, gfp_t gfp);
व्योम aa_label_xaudit(काष्ठा audit_buffer *ab, काष्ठा aa_ns *ns,
		     काष्ठा aa_label *label, पूर्णांक flags, gfp_t gfp);
व्योम aa_label_seq_xprपूर्णांक(काष्ठा seq_file *f, काष्ठा aa_ns *ns,
			 काष्ठा aa_label *label, पूर्णांक flags, gfp_t gfp);
व्योम aa_label_xprपूर्णांकk(काष्ठा aa_ns *ns, काष्ठा aa_label *label, पूर्णांक flags,
		      gfp_t gfp);
व्योम aa_label_audit(काष्ठा audit_buffer *ab, काष्ठा aa_label *label, gfp_t gfp);
व्योम aa_label_seq_prपूर्णांक(काष्ठा seq_file *f, काष्ठा aa_label *label, gfp_t gfp);
व्योम aa_label_prपूर्णांकk(काष्ठा aa_label *label, gfp_t gfp);

काष्ठा aa_label *aa_label_strn_parse(काष्ठा aa_label *base, स्थिर अक्षर *str,
				     माप_प्रकार n, gfp_t gfp, bool create,
				     bool क्रमce_stack);
काष्ठा aa_label *aa_label_parse(काष्ठा aa_label *base, स्थिर अक्षर *str,
				gfp_t gfp, bool create, bool क्रमce_stack);

अटल अंतरभूत स्थिर अक्षर *aa_label_strn_split(स्थिर अक्षर *str, पूर्णांक n)
अणु
	स्थिर अक्षर *pos;
	अचिन्हित पूर्णांक state;

	state = aa_dfa_matchn_until(stacksplitdfa, DFA_START, str, n, &pos);
	अगर (!ACCEPT_TABLE(stacksplitdfa)[state])
		वापस शून्य;

	वापस pos - 3;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *aa_label_str_split(स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *pos;
	अचिन्हित पूर्णांक state;

	state = aa_dfa_match_until(stacksplitdfa, DFA_START, str, &pos);
	अगर (!ACCEPT_TABLE(stacksplitdfa)[state])
		वापस शून्य;

	वापस pos - 3;
पूर्ण



काष्ठा aa_perms;
पूर्णांक aa_label_match(काष्ठा aa_profile *profile, काष्ठा aa_label *label,
		   अचिन्हित पूर्णांक state, bool subns, u32 request,
		   काष्ठा aa_perms *perms);


/**
 * __aa_get_label - get a reference count to uncounted label reference
 * @l: reference to get a count on
 *
 * Returns: poपूर्णांकer to reference OR शून्य अगर race is lost and reference is
 *          being repeated.
 * Requires: lock held, and the वापस code MUST be checked
 */
अटल अंतरभूत काष्ठा aa_label *__aa_get_label(काष्ठा aa_label *l)
अणु
	अगर (l && kref_get_unless_zero(&l->count))
		वापस l;

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा aa_label *aa_get_label(काष्ठा aa_label *l)
अणु
	अगर (l)
		kref_get(&(l->count));

	वापस l;
पूर्ण


/**
 * aa_get_label_rcu - increment refcount on a label that can be replaced
 * @l: poपूर्णांकer to label that can be replaced (NOT शून्य)
 *
 * Returns: poपूर्णांकer to a refcounted label.
 *     अन्यथा शून्य अगर no label
 */
अटल अंतरभूत काष्ठा aa_label *aa_get_label_rcu(काष्ठा aa_label __rcu **l)
अणु
	काष्ठा aa_label *c;

	rcu_पढ़ो_lock();
	करो अणु
		c = rcu_dereference(*l);
	पूर्ण जबतक (c && !kref_get_unless_zero(&c->count));
	rcu_पढ़ो_unlock();

	वापस c;
पूर्ण

/**
 * aa_get_newest_label - find the newest version of @l
 * @l: the label to check क्रम newer versions of
 *
 * Returns: refcounted newest version of @l taking पूर्णांकo account
 *          replacement, नामs and removals
 *          वापस @l.
 */
अटल अंतरभूत काष्ठा aa_label *aa_get_newest_label(काष्ठा aa_label *l)
अणु
	अगर (!l)
		वापस शून्य;

	अगर (label_is_stale(l)) अणु
		काष्ठा aa_label *पंचांगp;

		AA_BUG(!l->proxy);
		AA_BUG(!l->proxy->label);
		/* BUG: only way this can happen is @l ref count and its
		 * replacement count have gone to 0 and are on their way
		 * to deकाष्ठाion. ie. we have a refcounting error
		 */
		पंचांगp = aa_get_label_rcu(&l->proxy->label);
		AA_BUG(!पंचांगp);

		वापस पंचांगp;
	पूर्ण

	वापस aa_get_label(l);
पूर्ण

अटल अंतरभूत व्योम aa_put_label(काष्ठा aa_label *l)
अणु
	अगर (l)
		kref_put(&l->count, aa_label_kref);
पूर्ण


काष्ठा aa_proxy *aa_alloc_proxy(काष्ठा aa_label *l, gfp_t gfp);
व्योम aa_proxy_kref(काष्ठा kref *kref);

अटल अंतरभूत काष्ठा aa_proxy *aa_get_proxy(काष्ठा aa_proxy *proxy)
अणु
	अगर (proxy)
		kref_get(&(proxy->count));

	वापस proxy;
पूर्ण

अटल अंतरभूत व्योम aa_put_proxy(काष्ठा aa_proxy *proxy)
अणु
	अगर (proxy)
		kref_put(&proxy->count, aa_proxy_kref);
पूर्ण

व्योम __aa_proxy_redirect(काष्ठा aa_label *orig, काष्ठा aa_label *new);

#पूर्ण_अगर /* __AA_LABEL_H */
