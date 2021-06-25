<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor label definitions
 *
 * Copyright 2017 Canonical Ltd.
 */

#समावेश <linux/audit.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sort.h>

#समावेश "include/apparmor.h"
#समावेश "include/cred.h"
#समावेश "include/label.h"
#समावेश "include/policy.h"
#समावेश "include/secid.h"


/*
 * the aa_label represents the set of profiles confining an object
 *
 * Labels मुख्यtain a reference count to the set of poपूर्णांकers they reference
 * Labels are ref counted by
 *   tasks and object via the security field/security context off the field
 *   code - will take a ref count on a label अगर it needs the label
 *          beyond what is possible with an rcu_पढ़ो_lock.
 *   profiles - each profile is a label
 *   secids - a pinned secid will keep a refcount of the label it is
 *          referencing
 *   objects - inode, files, sockets, ...
 *
 * Labels are not ref counted by the label set, so they maybe हटाओd and
 * मुक्तd when no दीर्घer in use.
 *
 */

#घोषणा PROXY_POISON 97
#घोषणा LABEL_POISON 100

अटल व्योम मुक्त_proxy(काष्ठा aa_proxy *proxy)
अणु
	अगर (proxy) अणु
		/* p->label will not updated any more as p is dead */
		aa_put_label(rcu_dereference_रक्षित(proxy->label, true));
		स_रखो(proxy, 0, माप(*proxy));
		RCU_INIT_POINTER(proxy->label, (काष्ठा aa_label *)PROXY_POISON);
		kमुक्त(proxy);
	पूर्ण
पूर्ण

व्योम aa_proxy_kref(काष्ठा kref *kref)
अणु
	काष्ठा aa_proxy *proxy = container_of(kref, काष्ठा aa_proxy, count);

	मुक्त_proxy(proxy);
पूर्ण

काष्ठा aa_proxy *aa_alloc_proxy(काष्ठा aa_label *label, gfp_t gfp)
अणु
	काष्ठा aa_proxy *new;

	new = kzalloc(माप(काष्ठा aa_proxy), gfp);
	अगर (new) अणु
		kref_init(&new->count);
		rcu_assign_poपूर्णांकer(new->label, aa_get_label(label));
	पूर्ण
	वापस new;
पूर्ण

/* requires profile list ग_लिखो lock held */
व्योम __aa_proxy_redirect(काष्ठा aa_label *orig, काष्ठा aa_label *new)
अणु
	काष्ठा aa_label *पंचांगp;

	AA_BUG(!orig);
	AA_BUG(!new);
	lockdep_निश्चित_held_ग_लिखो(&labels_set(orig)->lock);

	पंचांगp = rcu_dereference_रक्षित(orig->proxy->label,
					&labels_ns(orig)->lock);
	rcu_assign_poपूर्णांकer(orig->proxy->label, aa_get_label(new));
	orig->flags |= FLAG_STALE;
	aa_put_label(पंचांगp);
पूर्ण

अटल व्योम __proxy_share(काष्ठा aa_label *old, काष्ठा aa_label *new)
अणु
	काष्ठा aa_proxy *proxy = new->proxy;

	new->proxy = aa_get_proxy(old->proxy);
	__aa_proxy_redirect(old, new);
	aa_put_proxy(proxy);
पूर्ण


/**
 * ns_cmp - compare ns क्रम label set ordering
 * @a: ns to compare (NOT शून्य)
 * @b: ns to compare (NOT शून्य)
 *
 * Returns: <0 अगर a < b
 *          ==0 अगर a == b
 *          >0  अगर a > b
 */
अटल पूर्णांक ns_cmp(काष्ठा aa_ns *a, काष्ठा aa_ns *b)
अणु
	पूर्णांक res;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!a->base.hname);
	AA_BUG(!b->base.hname);

	अगर (a == b)
		वापस 0;

	res = a->level - b->level;
	अगर (res)
		वापस res;

	वापस म_भेद(a->base.hname, b->base.hname);
पूर्ण

/**
 * profile_cmp - profile comparison क्रम set ordering
 * @a: profile to compare (NOT शून्य)
 * @b: profile to compare (NOT शून्य)
 *
 * Returns: <0  अगर a < b
 *          ==0 अगर a == b
 *          >0  अगर a > b
 */
अटल पूर्णांक profile_cmp(काष्ठा aa_profile *a, काष्ठा aa_profile *b)
अणु
	पूर्णांक res;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!a->ns);
	AA_BUG(!b->ns);
	AA_BUG(!a->base.hname);
	AA_BUG(!b->base.hname);

	अगर (a == b || a->base.hname == b->base.hname)
		वापस 0;
	res = ns_cmp(a->ns, b->ns);
	अगर (res)
		वापस res;

	वापस म_भेद(a->base.hname, b->base.hname);
पूर्ण

/**
 * vec_cmp - label comparison क्रम set ordering
 * @a: label to compare (NOT शून्य)
 * @vec: vector of profiles to compare (NOT शून्य)
 * @n: length of @vec
 *
 * Returns: <0  अगर a < vec
 *          ==0 अगर a == vec
 *          >0  अगर a > vec
 */
अटल पूर्णांक vec_cmp(काष्ठा aa_profile **a, पूर्णांक an, काष्ठा aa_profile **b, पूर्णांक bn)
अणु
	पूर्णांक i;

	AA_BUG(!a);
	AA_BUG(!*a);
	AA_BUG(!b);
	AA_BUG(!*b);
	AA_BUG(an <= 0);
	AA_BUG(bn <= 0);

	क्रम (i = 0; i < an && i < bn; i++) अणु
		पूर्णांक res = profile_cmp(a[i], b[i]);

		अगर (res != 0)
			वापस res;
	पूर्ण

	वापस an - bn;
पूर्ण

अटल bool vec_is_stale(काष्ठा aa_profile **vec, पूर्णांक n)
अणु
	पूर्णांक i;

	AA_BUG(!vec);

	क्रम (i = 0; i < n; i++) अणु
		अगर (profile_is_stale(vec[i]))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool vec_unconfined(काष्ठा aa_profile **vec, पूर्णांक n)
अणु
	पूर्णांक i;

	AA_BUG(!vec);

	क्रम (i = 0; i < n; i++) अणु
		अगर (!profile_unconfined(vec[i]))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक sort_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस profile_cmp(*(काष्ठा aa_profile **)a, *(काष्ठा aa_profile **)b);
पूर्ण

/*
 * assumes vec is sorted
 * Assumes @vec has null terminator at vec[n], and will null terminate
 * vec[n - dups]
 */
अटल अंतरभूत पूर्णांक unique(काष्ठा aa_profile **vec, पूर्णांक n)
अणु
	पूर्णांक i, pos, dups = 0;

	AA_BUG(n < 1);
	AA_BUG(!vec);

	pos = 0;
	क्रम (i = 1; i < n; i++) अणु
		पूर्णांक res = profile_cmp(vec[pos], vec[i]);

		AA_BUG(res > 0, "vec not sorted");
		अगर (res == 0) अणु
			/* drop duplicate */
			aa_put_profile(vec[i]);
			dups++;
			जारी;
		पूर्ण
		pos++;
		अगर (dups)
			vec[pos] = vec[i];
	पूर्ण

	AA_BUG(dups < 0);

	वापस dups;
पूर्ण

/**
 * aa_vec_unique - canonical sort and unique a list of profiles
 * @n: number of refcounted profiles in the list (@n > 0)
 * @vec: list of profiles to sort and merge
 *
 * Returns: the number of duplicates eliminated == references put
 *
 * If @flags & VEC_FLAG_TERMINATE @vec has null terminator at vec[n], and will
 * null terminate vec[n - dups]
 */
पूर्णांक aa_vec_unique(काष्ठा aa_profile **vec, पूर्णांक n, पूर्णांक flags)
अणु
	पूर्णांक i, dups = 0;

	AA_BUG(n < 1);
	AA_BUG(!vec);

	/* vecs are usually small and inorder, have a fallback क्रम larger */
	अगर (n > 8) अणु
		sort(vec, n, माप(काष्ठा aa_profile *), sort_cmp, शून्य);
		dups = unique(vec, n);
		जाओ out;
	पूर्ण

	/* insertion sort + unique in one */
	क्रम (i = 1; i < n; i++) अणु
		काष्ठा aa_profile *पंचांगp = vec[i];
		पूर्णांक pos, j;

		क्रम (pos = i - 1 - dups; pos >= 0; pos--) अणु
			पूर्णांक res = profile_cmp(vec[pos], पंचांगp);

			अगर (res == 0) अणु
				/* drop duplicate entry */
				aa_put_profile(पंचांगp);
				dups++;
				जाओ जारी_outer;
			पूर्ण अन्यथा अगर (res < 0)
				अवरोध;
		पूर्ण
		/* pos is at entry < पंचांगp, or index -1. Set to insert pos */
		pos++;

		क्रम (j = i - dups; j > pos; j--)
			vec[j] = vec[j - 1];
		vec[pos] = पंचांगp;
जारी_outer:
		;
	पूर्ण

	AA_BUG(dups < 0);

out:
	अगर (flags & VEC_FLAG_TERMINATE)
		vec[n - dups] = शून्य;

	वापस dups;
पूर्ण


व्योम aa_label_destroy(काष्ठा aa_label *label)
अणु
	AA_BUG(!label);

	अगर (!label_isprofile(label)) अणु
		काष्ठा aa_profile *profile;
		काष्ठा label_it i;

		aa_put_str(label->hname);

		label_क्रम_each(i, label, profile) अणु
			aa_put_profile(profile);
			label->vec[i.i] = (काष्ठा aa_profile *)
					   (LABEL_POISON + (दीर्घ) i.i);
		पूर्ण
	पूर्ण

	अगर (label->proxy) अणु
		अगर (rcu_dereference_रक्षित(label->proxy->label, true) == label)
			rcu_assign_poपूर्णांकer(label->proxy->label, शून्य);
		aa_put_proxy(label->proxy);
	पूर्ण
	aa_मुक्त_secid(label->secid);

	label->proxy = (काष्ठा aa_proxy *) PROXY_POISON + 1;
पूर्ण

व्योम aa_label_मुक्त(काष्ठा aa_label *label)
अणु
	अगर (!label)
		वापस;

	aa_label_destroy(label);
	kमुक्त(label);
पूर्ण

अटल व्योम label_मुक्त_चयन(काष्ठा aa_label *label)
अणु
	अगर (label->flags & FLAG_NS_COUNT)
		aa_मुक्त_ns(labels_ns(label));
	अन्यथा अगर (label_isprofile(label))
		aa_मुक्त_profile(labels_profile(label));
	अन्यथा
		aa_label_मुक्त(label);
पूर्ण

अटल व्योम label_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा aa_label *label = container_of(head, काष्ठा aa_label, rcu);

	अगर (label->flags & FLAG_IN_TREE)
		(व्योम) aa_label_हटाओ(label);
	label_मुक्त_चयन(label);
पूर्ण

व्योम aa_label_kref(काष्ठा kref *kref)
अणु
	काष्ठा aa_label *label = container_of(kref, काष्ठा aa_label, count);
	काष्ठा aa_ns *ns = labels_ns(label);

	अगर (!ns) अणु
		/* never live, no rcu callback needed, just using the fn */
		label_मुक्त_चयन(label);
		वापस;
	पूर्ण
	/* TODO: update labels_profile macro so it works here */
	AA_BUG(label_isprofile(label) &&
	       on_list_rcu(&label->vec[0]->base.profiles));
	AA_BUG(label_isprofile(label) &&
	       on_list_rcu(&label->vec[0]->base.list));

	/* TODO: अगर compound label and not stale add to reclaim cache */
	call_rcu(&label->rcu, label_मुक्त_rcu);
पूर्ण

अटल व्योम label_मुक्त_or_put_new(काष्ठा aa_label *label, काष्ठा aa_label *new)
अणु
	अगर (label != new)
		/* need to मुक्त directly to अवरोध circular ref with proxy */
		aa_label_मुक्त(new);
	अन्यथा
		aa_put_label(new);
पूर्ण

bool aa_label_init(काष्ठा aa_label *label, पूर्णांक size, gfp_t gfp)
अणु
	AA_BUG(!label);
	AA_BUG(size < 1);

	अगर (aa_alloc_secid(label, gfp) < 0)
		वापस false;

	label->size = size;			/* करोesn't include null */
	label->vec[size] = शून्य;		/* null terminate */
	kref_init(&label->count);
	RB_CLEAR_NODE(&label->node);

	वापस true;
पूर्ण

/**
 * aa_label_alloc - allocate a label with a profile vector of @size length
 * @size: size of profile vector in the label
 * @proxy: proxy to use OR null अगर to allocate a new one
 * @gfp: memory allocation type
 *
 * Returns: new label
 *     अन्यथा शून्य अगर failed
 */
काष्ठा aa_label *aa_label_alloc(पूर्णांक size, काष्ठा aa_proxy *proxy, gfp_t gfp)
अणु
	काष्ठा aa_label *new;

	AA_BUG(size < 1);

	/*  + 1 क्रम null terminator entry on vec */
	new = kzalloc(माप(*new) + माप(काष्ठा aa_profile *) * (size + 1),
			gfp);
	AA_DEBUG("%s (%p)\n", __func__, new);
	अगर (!new)
		जाओ fail;

	अगर (!aa_label_init(new, size, gfp))
		जाओ fail;

	अगर (!proxy) अणु
		proxy = aa_alloc_proxy(new, gfp);
		अगर (!proxy)
			जाओ fail;
	पूर्ण अन्यथा
		aa_get_proxy(proxy);
	/* just set new's proxy, don't redirect proxy here अगर it was passed in*/
	new->proxy = proxy;

	वापस new;

fail:
	kमुक्त(new);

	वापस शून्य;
पूर्ण


/**
 * label_cmp - label comparison क्रम set ordering
 * @a: label to compare (NOT शून्य)
 * @b: label to compare (NOT शून्य)
 *
 * Returns: <0  अगर a < b
 *          ==0 अगर a == b
 *          >0  अगर a > b
 */
अटल पूर्णांक label_cmp(काष्ठा aa_label *a, काष्ठा aa_label *b)
अणु
	AA_BUG(!b);

	अगर (a == b)
		वापस 0;

	वापस vec_cmp(a->vec, a->size, b->vec, b->size);
पूर्ण

/* helper fn क्रम label_क्रम_each_confined */
पूर्णांक aa_label_next_confined(काष्ठा aa_label *label, पूर्णांक i)
अणु
	AA_BUG(!label);
	AA_BUG(i < 0);

	क्रम (; i < label->size; i++) अणु
		अगर (!profile_unconfined(label->vec[i]))
			वापस i;
	पूर्ण

	वापस i;
पूर्ण

/**
 * aa_label_next_not_in_set - वापस the next profile of @sub not in @set
 * @I: label iterator
 * @set: label to test against
 * @sub: label to अगर is subset of @set
 *
 * Returns: profile in @sub that is not in @set, with iterator set pos after
 *     अन्यथा शून्य अगर @sub is a subset of @set
 */
काष्ठा aa_profile *__aa_label_next_not_in_set(काष्ठा label_it *I,
					      काष्ठा aa_label *set,
					      काष्ठा aa_label *sub)
अणु
	AA_BUG(!set);
	AA_BUG(!I);
	AA_BUG(I->i < 0);
	AA_BUG(I->i > set->size);
	AA_BUG(!sub);
	AA_BUG(I->j < 0);
	AA_BUG(I->j > sub->size);

	जबतक (I->j < sub->size && I->i < set->size) अणु
		पूर्णांक res = profile_cmp(sub->vec[I->j], set->vec[I->i]);

		अगर (res == 0) अणु
			(I->j)++;
			(I->i)++;
		पूर्ण अन्यथा अगर (res > 0)
			(I->i)++;
		अन्यथा
			वापस sub->vec[(I->j)++];
	पूर्ण

	अगर (I->j < sub->size)
		वापस sub->vec[(I->j)++];

	वापस शून्य;
पूर्ण

/**
 * aa_label_is_subset - test अगर @sub is a subset of @set
 * @set: label to test against
 * @sub: label to test अगर is subset of @set
 *
 * Returns: true अगर @sub is subset of @set
 *     अन्यथा false
 */
bool aa_label_is_subset(काष्ठा aa_label *set, काष्ठा aa_label *sub)
अणु
	काष्ठा label_it i = अणु पूर्ण;

	AA_BUG(!set);
	AA_BUG(!sub);

	अगर (sub == set)
		वापस true;

	वापस __aa_label_next_not_in_set(&i, set, sub) == शून्य;
पूर्ण

/**
 * aa_label_is_unconfined_subset - test अगर @sub is a subset of @set
 * @set: label to test against
 * @sub: label to test अगर is subset of @set
 *
 * This checks क्रम subset but taking पूर्णांकo account unconfined. IF
 * @sub contains an unconfined profile that करोes not have a matching
 * unconfined in @set then this will not cause the test to fail.
 * Conversely we करोn't care about an unconfined in @set that is not in
 * @sub
 *
 * Returns: true अगर @sub is special_subset of @set
 *     अन्यथा false
 */
bool aa_label_is_unconfined_subset(काष्ठा aa_label *set, काष्ठा aa_label *sub)
अणु
	काष्ठा label_it i = अणु पूर्ण;
	काष्ठा aa_profile *p;

	AA_BUG(!set);
	AA_BUG(!sub);

	अगर (sub == set)
		वापस true;

	करो अणु
		p = __aa_label_next_not_in_set(&i, set, sub);
		अगर (p && !profile_unconfined(p))
			अवरोध;
	पूर्ण जबतक (p);

	वापस p == शून्य;
पूर्ण


/**
 * __label_हटाओ - हटाओ @label from the label set
 * @l: label to हटाओ
 * @new: label to redirect to
 *
 * Requires: labels_set(@label)->lock ग_लिखो_lock
 * Returns:  true अगर the label was in the tree and हटाओd
 */
अटल bool __label_हटाओ(काष्ठा aa_label *label, काष्ठा aa_label *new)
अणु
	काष्ठा aa_labअन्यथाt *ls = labels_set(label);

	AA_BUG(!ls);
	AA_BUG(!label);
	lockdep_निश्चित_held_ग_लिखो(&ls->lock);

	अगर (new)
		__aa_proxy_redirect(label, new);

	अगर (!label_is_stale(label))
		__label_make_stale(label);

	अगर (label->flags & FLAG_IN_TREE) अणु
		rb_erase(&label->node, &ls->root);
		label->flags &= ~FLAG_IN_TREE;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * __label_replace - replace @old with @new in label set
 * @old: label to हटाओ from label set
 * @new: label to replace @old with
 *
 * Requires: labels_set(@old)->lock ग_लिखो_lock
 *           valid ref count be held on @new
 * Returns: true अगर @old was in set and replaced by @new
 *
 * Note: current implementation requires label set be order in such a way
 *       that @new directly replaces @old position in the set (ie.
 *       using poपूर्णांकer comparison of the label address would not work)
 */
अटल bool __label_replace(काष्ठा aa_label *old, काष्ठा aa_label *new)
अणु
	काष्ठा aa_labअन्यथाt *ls = labels_set(old);

	AA_BUG(!ls);
	AA_BUG(!old);
	AA_BUG(!new);
	lockdep_निश्चित_held_ग_लिखो(&ls->lock);
	AA_BUG(new->flags & FLAG_IN_TREE);

	अगर (!label_is_stale(old))
		__label_make_stale(old);

	अगर (old->flags & FLAG_IN_TREE) अणु
		rb_replace_node(&old->node, &new->node, &ls->root);
		old->flags &= ~FLAG_IN_TREE;
		new->flags |= FLAG_IN_TREE;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * __label_insert - attempt to insert @l पूर्णांकo a label set
 * @ls: set of labels to insert @l पूर्णांकo (NOT शून्य)
 * @label: new label to insert (NOT शून्य)
 * @replace: whether insertion should replace existing entry that is not stale
 *
 * Requires: @ls->lock
 *           caller to hold a valid ref on l
 *           अगर @replace is true l has a pपुनः_स्मृतिated proxy associated
 * Returns: @l अगर successful in inserting @l - with additional refcount
 *          अन्यथा ref counted equivalent label that is alपढ़ोy in the set,
 *          the अन्यथा condition only happens अगर @replace is false
 */
अटल काष्ठा aa_label *__label_insert(काष्ठा aa_labअन्यथाt *ls,
				       काष्ठा aa_label *label, bool replace)
अणु
	काष्ठा rb_node **new, *parent = शून्य;

	AA_BUG(!ls);
	AA_BUG(!label);
	AA_BUG(labels_set(label) != ls);
	lockdep_निश्चित_held_ग_लिखो(&ls->lock);
	AA_BUG(label->flags & FLAG_IN_TREE);

	/* Figure out where to put new node */
	new = &ls->root.rb_node;
	जबतक (*new) अणु
		काष्ठा aa_label *this = rb_entry(*new, काष्ठा aa_label, node);
		पूर्णांक result = label_cmp(label, this);

		parent = *new;
		अगर (result == 0) अणु
			/* !__aa_get_label means queued क्रम deकाष्ठाion,
			 * so replace in place, however the label has
			 * died beक्रमe the replacement so करो not share
			 * the proxy
			 */
			अगर (!replace && !label_is_stale(this)) अणु
				अगर (__aa_get_label(this))
					वापस this;
			पूर्ण अन्यथा
				__proxy_share(this, label);
			AA_BUG(!__label_replace(this, label));
			वापस aa_get_label(label);
		पूर्ण अन्यथा अगर (result < 0)
			new = &((*new)->rb_left);
		अन्यथा /* (result > 0) */
			new = &((*new)->rb_right);
	पूर्ण

	/* Add new node and rebalance tree. */
	rb_link_node(&label->node, parent, new);
	rb_insert_color(&label->node, &ls->root);
	label->flags |= FLAG_IN_TREE;

	वापस aa_get_label(label);
पूर्ण

/**
 * __vec_find - find label that matches @vec in label set
 * @vec: vec of profiles to find matching label क्रम (NOT शून्य)
 * @n: length of @vec
 *
 * Requires: @vec_labअन्यथाt(vec) lock held
 *           caller to hold a valid ref on l
 *
 * Returns: ref counted @label अगर matching label is in tree
 *          ref counted label that is equiv to @l in tree
 *     अन्यथा शून्य अगर @vec equiv is not in tree
 */
अटल काष्ठा aa_label *__vec_find(काष्ठा aa_profile **vec, पूर्णांक n)
अणु
	काष्ठा rb_node *node;

	AA_BUG(!vec);
	AA_BUG(!*vec);
	AA_BUG(n <= 0);

	node = vec_labअन्यथाt(vec, n)->root.rb_node;
	जबतक (node) अणु
		काष्ठा aa_label *this = rb_entry(node, काष्ठा aa_label, node);
		पूर्णांक result = vec_cmp(this->vec, this->size, vec, n);

		अगर (result > 0)
			node = node->rb_left;
		अन्यथा अगर (result < 0)
			node = node->rb_right;
		अन्यथा
			वापस __aa_get_label(this);
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __label_find - find label @label in label set
 * @label: label to find (NOT शून्य)
 *
 * Requires: labels_set(@label)->lock held
 *           caller to hold a valid ref on l
 *
 * Returns: ref counted @label अगर @label is in tree OR
 *          ref counted label that is equiv to @label in tree
 *     अन्यथा शून्य अगर @label or equiv is not in tree
 */
अटल काष्ठा aa_label *__label_find(काष्ठा aa_label *label)
अणु
	AA_BUG(!label);

	वापस __vec_find(label->vec, label->size);
पूर्ण


/**
 * aa_label_हटाओ - हटाओ a label from the labअन्यथाt
 * @label: label to हटाओ
 *
 * Returns: true अगर @label was हटाओd from the tree
 *     अन्यथा @label was not in tree so it could not be हटाओd
 */
bool aa_label_हटाओ(काष्ठा aa_label *label)
अणु
	काष्ठा aa_labअन्यथाt *ls = labels_set(label);
	अचिन्हित दीर्घ flags;
	bool res;

	AA_BUG(!ls);

	ग_लिखो_lock_irqsave(&ls->lock, flags);
	res = __label_हटाओ(label, ns_unconfined(labels_ns(label)));
	ग_लिखो_unlock_irqrestore(&ls->lock, flags);

	वापस res;
पूर्ण

/**
 * aa_label_replace - replace a label @old with a new version @new
 * @old: label to replace
 * @new: label replacing @old
 *
 * Returns: true अगर @old was in tree and replaced
 *     अन्यथा @old was not in tree, and @new was not inserted
 */
bool aa_label_replace(काष्ठा aa_label *old, काष्ठा aa_label *new)
अणु
	अचिन्हित दीर्घ flags;
	bool res;

	अगर (name_is_shared(old, new) && labels_ns(old) == labels_ns(new)) अणु
		ग_लिखो_lock_irqsave(&labels_set(old)->lock, flags);
		अगर (old->proxy != new->proxy)
			__proxy_share(old, new);
		अन्यथा
			__aa_proxy_redirect(old, new);
		res = __label_replace(old, new);
		ग_लिखो_unlock_irqrestore(&labels_set(old)->lock, flags);
	पूर्ण अन्यथा अणु
		काष्ठा aa_label *l;
		काष्ठा aa_labअन्यथाt *ls = labels_set(old);

		ग_लिखो_lock_irqsave(&ls->lock, flags);
		res = __label_हटाओ(old, new);
		अगर (labels_ns(old) != labels_ns(new)) अणु
			ग_लिखो_unlock_irqrestore(&ls->lock, flags);
			ls = labels_set(new);
			ग_लिखो_lock_irqsave(&ls->lock, flags);
		पूर्ण
		l = __label_insert(ls, new, true);
		res = (l == new);
		ग_लिखो_unlock_irqrestore(&ls->lock, flags);
		aa_put_label(l);
	पूर्ण

	वापस res;
पूर्ण

/**
 * vec_find - find label @l in label set
 * @vec: array of profiles to find equiv label क्रम (NOT शून्य)
 * @n: length of @vec
 *
 * Returns: refcounted label अगर @vec equiv is in tree
 *     अन्यथा शून्य अगर @vec equiv is not in tree
 */
अटल काष्ठा aa_label *vec_find(काष्ठा aa_profile **vec, पूर्णांक n)
अणु
	काष्ठा aa_labअन्यथाt *ls;
	काष्ठा aa_label *label;
	अचिन्हित दीर्घ flags;

	AA_BUG(!vec);
	AA_BUG(!*vec);
	AA_BUG(n <= 0);

	ls = vec_labअन्यथाt(vec, n);
	पढ़ो_lock_irqsave(&ls->lock, flags);
	label = __vec_find(vec, n);
	पढ़ो_unlock_irqrestore(&ls->lock, flags);

	वापस label;
पूर्ण

/* requires sort and merge करोne first */
अटल काष्ठा aa_label *vec_create_and_insert_label(काष्ठा aa_profile **vec,
						    पूर्णांक len, gfp_t gfp)
अणु
	काष्ठा aa_label *label = शून्य;
	काष्ठा aa_labअन्यथाt *ls;
	अचिन्हित दीर्घ flags;
	काष्ठा aa_label *new;
	पूर्णांक i;

	AA_BUG(!vec);

	अगर (len == 1)
		वापस aa_get_label(&vec[0]->label);

	ls = labels_set(&vec[len - 1]->label);

	/* TODO: enable when पढ़ो side is lockless
	 * check अगर label exists beक्रमe taking locks
	 */
	new = aa_label_alloc(len, शून्य, gfp);
	अगर (!new)
		वापस शून्य;

	क्रम (i = 0; i < len; i++)
		new->vec[i] = aa_get_profile(vec[i]);

	ग_लिखो_lock_irqsave(&ls->lock, flags);
	label = __label_insert(ls, new, false);
	ग_लिखो_unlock_irqrestore(&ls->lock, flags);
	label_मुक्त_or_put_new(label, new);

	वापस label;
पूर्ण

काष्ठा aa_label *aa_vec_find_or_create_label(काष्ठा aa_profile **vec, पूर्णांक len,
					     gfp_t gfp)
अणु
	काष्ठा aa_label *label = vec_find(vec, len);

	अगर (label)
		वापस label;

	वापस vec_create_and_insert_label(vec, len, gfp);
पूर्ण

/**
 * aa_label_find - find label @label in label set
 * @label: label to find (NOT शून्य)
 *
 * Requires: caller to hold a valid ref on l
 *
 * Returns: refcounted @label अगर @label is in tree
 *          refcounted label that is equiv to @label in tree
 *     अन्यथा शून्य अगर @label or equiv is not in tree
 */
काष्ठा aa_label *aa_label_find(काष्ठा aa_label *label)
अणु
	AA_BUG(!label);

	वापस vec_find(label->vec, label->size);
पूर्ण


/**
 * aa_label_insert - insert label @label पूर्णांकo @ls or वापस existing label
 * @ls - labअन्यथाt to insert @label पूर्णांकo
 * @label - label to insert
 *
 * Requires: caller to hold a valid ref on @label
 *
 * Returns: ref counted @label अगर successful in inserting @label
 *     अन्यथा ref counted equivalent label that is alपढ़ोy in the set
 */
काष्ठा aa_label *aa_label_insert(काष्ठा aa_labअन्यथाt *ls, काष्ठा aa_label *label)
अणु
	काष्ठा aa_label *l;
	अचिन्हित दीर्घ flags;

	AA_BUG(!ls);
	AA_BUG(!label);

	/* check अगर label exists beक्रमe taking lock */
	अगर (!label_is_stale(label)) अणु
		पढ़ो_lock_irqsave(&ls->lock, flags);
		l = __label_find(label);
		पढ़ो_unlock_irqrestore(&ls->lock, flags);
		अगर (l)
			वापस l;
	पूर्ण

	ग_लिखो_lock_irqsave(&ls->lock, flags);
	l = __label_insert(ls, label, false);
	ग_लिखो_unlock_irqrestore(&ls->lock, flags);

	वापस l;
पूर्ण


/**
 * aa_label_next_in_merge - find the next profile when merging @a and @b
 * @I: label iterator
 * @a: label to merge
 * @b: label to merge
 *
 * Returns: next profile
 *     अन्यथा null अगर no more profiles
 */
काष्ठा aa_profile *aa_label_next_in_merge(काष्ठा label_it *I,
					  काष्ठा aa_label *a,
					  काष्ठा aa_label *b)
अणु
	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!I);
	AA_BUG(I->i < 0);
	AA_BUG(I->i > a->size);
	AA_BUG(I->j < 0);
	AA_BUG(I->j > b->size);

	अगर (I->i < a->size) अणु
		अगर (I->j < b->size) अणु
			पूर्णांक res = profile_cmp(a->vec[I->i], b->vec[I->j]);

			अगर (res > 0)
				वापस b->vec[(I->j)++];
			अगर (res == 0)
				(I->j)++;
		पूर्ण

		वापस a->vec[(I->i)++];
	पूर्ण

	अगर (I->j < b->size)
		वापस b->vec[(I->j)++];

	वापस शून्य;
पूर्ण

/**
 * label_merge_cmp - cmp of @a merging with @b against @z क्रम set ordering
 * @a: label to merge then compare (NOT शून्य)
 * @b: label to merge then compare (NOT शून्य)
 * @z: label to compare merge against (NOT शून्य)
 *
 * Assumes: using the most recent versions of @a, @b, and @z
 *
 * Returns: <0  अगर a < b
 *          ==0 अगर a == b
 *          >0  अगर a > b
 */
अटल पूर्णांक label_merge_cmp(काष्ठा aa_label *a, काष्ठा aa_label *b,
			   काष्ठा aa_label *z)
अणु
	काष्ठा aa_profile *p = शून्य;
	काष्ठा label_it i = अणु पूर्ण;
	पूर्णांक k;

	AA_BUG(!a);
	AA_BUG(!b);
	AA_BUG(!z);

	क्रम (k = 0;
	     k < z->size && (p = aa_label_next_in_merge(&i, a, b));
	     k++) अणु
		पूर्णांक res = profile_cmp(p, z->vec[k]);

		अगर (res != 0)
			वापस res;
	पूर्ण

	अगर (p)
		वापस 1;
	अन्यथा अगर (k < z->size)
		वापस -1;
	वापस 0;
पूर्ण

/**
 * label_merge_insert - create a new label by merging @a and @b
 * @new: pपुनः_स्मृतिated label to merge पूर्णांकo (NOT शून्य)
 * @a: label to merge with @b  (NOT शून्य)
 * @b: label to merge with @a  (NOT शून्य)
 *
 * Requires: pपुनः_स्मृतिated proxy
 *
 * Returns: ref counted label either @new अगर merge is unique
 *          @a अगर @b is a subset of @a
 *          @b अगर @a is a subset of @b
 *
 * NOTE: will not use @new अगर the merge results in @new == @a or @b
 *
 *       Must be used within labअन्यथाt ग_लिखो lock to aव्योम racing with
 *       setting labels stale.
 */
अटल काष्ठा aa_label *label_merge_insert(काष्ठा aa_label *new,
					   काष्ठा aa_label *a,
					   काष्ठा aa_label *b)
अणु
	काष्ठा aa_label *label;
	काष्ठा aa_labअन्यथाt *ls;
	काष्ठा aa_profile *next;
	काष्ठा label_it i;
	अचिन्हित दीर्घ flags;
	पूर्णांक k = 0, invcount = 0;
	bool stale = false;

	AA_BUG(!a);
	AA_BUG(a->size < 0);
	AA_BUG(!b);
	AA_BUG(b->size < 0);
	AA_BUG(!new);
	AA_BUG(new->size < a->size + b->size);

	label_क्रम_each_in_merge(i, a, b, next) अणु
		AA_BUG(!next);
		अगर (profile_is_stale(next)) अणु
			new->vec[k] = aa_get_newest_profile(next);
			AA_BUG(!new->vec[k]->label.proxy);
			AA_BUG(!new->vec[k]->label.proxy->label);
			अगर (next->label.proxy != new->vec[k]->label.proxy)
				invcount++;
			k++;
			stale = true;
		पूर्ण अन्यथा
			new->vec[k++] = aa_get_profile(next);
	पूर्ण
	/* set to actual size which is <= allocated len */
	new->size = k;
	new->vec[k] = शून्य;

	अगर (invcount) अणु
		new->size -= aa_vec_unique(&new->vec[0], new->size,
					   VEC_FLAG_TERMINATE);
		/* TODO: deal with reference labels */
		अगर (new->size == 1) अणु
			label = aa_get_label(&new->vec[0]->label);
			वापस label;
		पूर्ण
	पूर्ण अन्यथा अगर (!stale) अणु
		/*
		 * merge could be same as a || b, note: it is not possible
		 * क्रम new->size == a->size == b->size unless a == b
		 */
		अगर (k == a->size)
			वापस aa_get_label(a);
		अन्यथा अगर (k == b->size)
			वापस aa_get_label(b);
	पूर्ण
	अगर (vec_unconfined(new->vec, new->size))
		new->flags |= FLAG_UNCONFINED;
	ls = labels_set(new);
	ग_लिखो_lock_irqsave(&ls->lock, flags);
	label = __label_insert(labels_set(new), new, false);
	ग_लिखो_unlock_irqrestore(&ls->lock, flags);

	वापस label;
पूर्ण

/**
 * labअन्यथाt_of_merge - find which labअन्यथाt a merged label should be inserted
 * @a: label to merge and insert
 * @b: label to merge and insert
 *
 * Returns: labअन्यथाt that the merged label should be inserted पूर्णांकo
 */
अटल काष्ठा aa_labअन्यथाt *labअन्यथाt_of_merge(काष्ठा aa_label *a,
					     काष्ठा aa_label *b)
अणु
	काष्ठा aa_ns *nsa = labels_ns(a);
	काष्ठा aa_ns *nsb = labels_ns(b);

	अगर (ns_cmp(nsa, nsb) <= 0)
		वापस &nsa->labels;
	वापस &nsb->labels;
पूर्ण

/**
 * __label_find_merge - find label that is equiv to merge of @a and @b
 * @ls: set of labels to search (NOT शून्य)
 * @a: label to merge with @b  (NOT शून्य)
 * @b: label to merge with @a  (NOT शून्य)
 *
 * Requires: ls->lock पढ़ो_lock held
 *
 * Returns: ref counted label that is equiv to merge of @a and @b
 *     अन्यथा शून्य अगर merge of @a and @b is not in set
 */
अटल काष्ठा aa_label *__label_find_merge(काष्ठा aa_labअन्यथाt *ls,
					   काष्ठा aa_label *a,
					   काष्ठा aa_label *b)
अणु
	काष्ठा rb_node *node;

	AA_BUG(!ls);
	AA_BUG(!a);
	AA_BUG(!b);

	अगर (a == b)
		वापस __label_find(a);

	node  = ls->root.rb_node;
	जबतक (node) अणु
		काष्ठा aa_label *this = container_of(node, काष्ठा aa_label,
						     node);
		पूर्णांक result = label_merge_cmp(a, b, this);

		अगर (result < 0)
			node = node->rb_left;
		अन्यथा अगर (result > 0)
			node = node->rb_right;
		अन्यथा
			वापस __aa_get_label(this);
	पूर्ण

	वापस शून्य;
पूर्ण


/**
 * aa_label_find_merge - find label that is equiv to merge of @a and @b
 * @a: label to merge with @b  (NOT शून्य)
 * @b: label to merge with @a  (NOT शून्य)
 *
 * Requires: labels be fully स्थिरructed with a valid ns
 *
 * Returns: ref counted label that is equiv to merge of @a and @b
 *     अन्यथा शून्य अगर merge of @a and @b is not in set
 */
काष्ठा aa_label *aa_label_find_merge(काष्ठा aa_label *a, काष्ठा aa_label *b)
अणु
	काष्ठा aa_labअन्यथाt *ls;
	काष्ठा aa_label *label, *ar = शून्य, *br = शून्य;
	अचिन्हित दीर्घ flags;

	AA_BUG(!a);
	AA_BUG(!b);

	अगर (label_is_stale(a))
		a = ar = aa_get_newest_label(a);
	अगर (label_is_stale(b))
		b = br = aa_get_newest_label(b);
	ls = labअन्यथाt_of_merge(a, b);
	पढ़ो_lock_irqsave(&ls->lock, flags);
	label = __label_find_merge(ls, a, b);
	पढ़ो_unlock_irqrestore(&ls->lock, flags);
	aa_put_label(ar);
	aa_put_label(br);

	वापस label;
पूर्ण

/**
 * aa_label_merge - attempt to insert new merged label of @a and @b
 * @ls: set of labels to insert label पूर्णांकo (NOT शून्य)
 * @a: label to merge with @b  (NOT शून्य)
 * @b: label to merge with @a  (NOT शून्य)
 * @gfp: memory allocation type
 *
 * Requires: caller to hold valid refs on @a and @b
 *           labels be fully स्थिरructed with a valid ns
 *
 * Returns: ref counted new label अगर successful in inserting merge of a & b
 *     अन्यथा ref counted equivalent label that is alपढ़ोy in the set.
 *     अन्यथा शून्य अगर could not create label (-ENOMEM)
 */
काष्ठा aa_label *aa_label_merge(काष्ठा aa_label *a, काष्ठा aa_label *b,
				gfp_t gfp)
अणु
	काष्ठा aa_label *label = शून्य;

	AA_BUG(!a);
	AA_BUG(!b);

	अगर (a == b)
		वापस aa_get_newest_label(a);

	/* TODO: enable when पढ़ो side is lockless
	 * check अगर label exists beक्रमe taking locks
	अगर (!label_is_stale(a) && !label_is_stale(b))
		label = aa_label_find_merge(a, b);
	*/

	अगर (!label) अणु
		काष्ठा aa_label *new;

		a = aa_get_newest_label(a);
		b = aa_get_newest_label(b);

		/* could use label_merge_len(a, b), but requires द्विगुन
		 * comparison क्रम small savings
		 */
		new = aa_label_alloc(a->size + b->size, शून्य, gfp);
		अगर (!new)
			जाओ out;

		label = label_merge_insert(new, a, b);
		label_मुक्त_or_put_new(label, new);
out:
		aa_put_label(a);
		aa_put_label(b);
	पूर्ण

	वापस label;
पूर्ण

अटल अंतरभूत bool label_is_visible(काष्ठा aa_profile *profile,
				    काष्ठा aa_label *label)
अणु
	वापस aa_ns_visible(profile->ns, labels_ns(label), true);
पूर्ण

/* match a profile and its associated ns component अगर needed
 * Assumes visibility test has alपढ़ोy been करोne.
 * If a subns profile is not to be matched should be prescreened with
 * visibility test.
 */
अटल अंतरभूत अचिन्हित पूर्णांक match_component(काष्ठा aa_profile *profile,
					   काष्ठा aa_profile *tp,
					   अचिन्हित पूर्णांक state)
अणु
	स्थिर अक्षर *ns_name;

	अगर (profile->ns == tp->ns)
		वापस aa_dfa_match(profile->policy.dfa, state, tp->base.hname);

	/* try matching with namespace name and then profile */
	ns_name = aa_ns_name(profile->ns, tp->ns, true);
	state = aa_dfa_match_len(profile->policy.dfa, state, ":", 1);
	state = aa_dfa_match(profile->policy.dfa, state, ns_name);
	state = aa_dfa_match_len(profile->policy.dfa, state, ":", 1);
	वापस aa_dfa_match(profile->policy.dfa, state, tp->base.hname);
पूर्ण

/**
 * label_compound_match - find perms क्रम full compound label
 * @profile: profile to find perms क्रम
 * @label: label to check access permissions क्रम
 * @start: state to start match in
 * @subns: whether to करो permission checks on components in a subns
 * @request: permissions to request
 * @perms: perms काष्ठा to set
 *
 * Returns: 0 on success अन्यथा ERROR
 *
 * For the label A//&B//&C this करोes the perm match क्रम A//&B//&C
 * @perms should be preinitialized with allperms OR a previous permission
 *        check to be stacked.
 */
अटल पूर्णांक label_compound_match(काष्ठा aa_profile *profile,
				काष्ठा aa_label *label,
				अचिन्हित पूर्णांक state, bool subns, u32 request,
				काष्ठा aa_perms *perms)
अणु
	काष्ठा aa_profile *tp;
	काष्ठा label_it i;

	/* find first subcomponent that is visible */
	label_क्रम_each(i, label, tp) अणु
		अगर (!aa_ns_visible(profile->ns, tp->ns, subns))
			जारी;
		state = match_component(profile, tp, state);
		अगर (!state)
			जाओ fail;
		जाओ next;
	पूर्ण

	/* no component visible */
	*perms = allperms;
	वापस 0;

next:
	label_क्रम_each_cont(i, label, tp) अणु
		अगर (!aa_ns_visible(profile->ns, tp->ns, subns))
			जारी;
		state = aa_dfa_match(profile->policy.dfa, state, "//&");
		state = match_component(profile, tp, state);
		अगर (!state)
			जाओ fail;
	पूर्ण
	aa_compute_perms(profile->policy.dfa, state, perms);
	aa_apply_modes_to_perms(profile, perms);
	अगर ((perms->allow & request) != request)
		वापस -EACCES;

	वापस 0;

fail:
	*perms = nullperms;
	वापस state;
पूर्ण

/**
 * label_components_match - find perms क्रम all subcomponents of a label
 * @profile: profile to find perms क्रम
 * @label: label to check access permissions क्रम
 * @start: state to start match in
 * @subns: whether to करो permission checks on components in a subns
 * @request: permissions to request
 * @perms: an initialized perms काष्ठा to add accumulation to
 *
 * Returns: 0 on success अन्यथा ERROR
 *
 * For the label A//&B//&C this करोes the perm match क्रम each of A and B and C
 * @perms should be preinitialized with allperms OR a previous permission
 *        check to be stacked.
 */
अटल पूर्णांक label_components_match(काष्ठा aa_profile *profile,
				  काष्ठा aa_label *label, अचिन्हित पूर्णांक start,
				  bool subns, u32 request,
				  काष्ठा aa_perms *perms)
अणु
	काष्ठा aa_profile *tp;
	काष्ठा label_it i;
	काष्ठा aa_perms पंचांगp;
	अचिन्हित पूर्णांक state = 0;

	/* find first subcomponent to test */
	label_क्रम_each(i, label, tp) अणु
		अगर (!aa_ns_visible(profile->ns, tp->ns, subns))
			जारी;
		state = match_component(profile, tp, start);
		अगर (!state)
			जाओ fail;
		जाओ next;
	पूर्ण

	/* no subcomponents visible - no change in perms */
	वापस 0;

next:
	aa_compute_perms(profile->policy.dfa, state, &पंचांगp);
	aa_apply_modes_to_perms(profile, &पंचांगp);
	aa_perms_accum(perms, &पंचांगp);
	label_क्रम_each_cont(i, label, tp) अणु
		अगर (!aa_ns_visible(profile->ns, tp->ns, subns))
			जारी;
		state = match_component(profile, tp, start);
		अगर (!state)
			जाओ fail;
		aa_compute_perms(profile->policy.dfa, state, &पंचांगp);
		aa_apply_modes_to_perms(profile, &पंचांगp);
		aa_perms_accum(perms, &पंचांगp);
	पूर्ण

	अगर ((perms->allow & request) != request)
		वापस -EACCES;

	वापस 0;

fail:
	*perms = nullperms;
	वापस -EACCES;
पूर्ण

/**
 * aa_label_match - करो a multi-component label match
 * @profile: profile to match against (NOT शून्य)
 * @label: label to match (NOT शून्य)
 * @state: state to start in
 * @subns: whether to match subns components
 * @request: permission request
 * @perms: Returns computed perms (NOT शून्य)
 *
 * Returns: the state the match finished in, may be the none matching state
 */
पूर्णांक aa_label_match(काष्ठा aa_profile *profile, काष्ठा aa_label *label,
		   अचिन्हित पूर्णांक state, bool subns, u32 request,
		   काष्ठा aa_perms *perms)
अणु
	पूर्णांक error = label_compound_match(profile, label, state, subns, request,
					 perms);
	अगर (!error)
		वापस error;

	*perms = allperms;
	वापस label_components_match(profile, label, state, subns, request,
				      perms);
पूर्ण


/**
 * aa_update_label_name - update a label to have a stored name
 * @ns: ns being viewed from (NOT शून्य)
 * @label: label to update (NOT शून्य)
 * @gfp: type of memory allocation
 *
 * Requires: labels_set(label) not locked in caller
 *
 * note: only updates the label name अगर it करोes not have a name alपढ़ोy
 *       and अगर it is in the labअन्यथाt
 */
bool aa_update_label_name(काष्ठा aa_ns *ns, काष्ठा aa_label *label, gfp_t gfp)
अणु
	काष्ठा aa_labअन्यथाt *ls;
	अचिन्हित दीर्घ flags;
	अक्षर __counted *name;
	bool res = false;

	AA_BUG(!ns);
	AA_BUG(!label);

	अगर (label->hname || labels_ns(label) != ns)
		वापस res;

	अगर (aa_label_acntsxprपूर्णांक(&name, ns, label, FLAGS_NONE, gfp) == -1)
		वापस res;

	ls = labels_set(label);
	ग_लिखो_lock_irqsave(&ls->lock, flags);
	अगर (!label->hname && label->flags & FLAG_IN_TREE) अणु
		label->hname = name;
		res = true;
	पूर्ण अन्यथा
		aa_put_str(name);
	ग_लिखो_unlock_irqrestore(&ls->lock, flags);

	वापस res;
पूर्ण

/*
 * cached label name is present and visible
 * @label->hname only exists अगर label is namespace hierachical
 */
अटल अंतरभूत bool use_label_hname(काष्ठा aa_ns *ns, काष्ठा aa_label *label,
				   पूर्णांक flags)
अणु
	अगर (label->hname && (!ns || labels_ns(label) == ns) &&
	    !(flags & ~FLAG_SHOW_MODE))
		वापस true;

	वापस false;
पूर्ण

/* helper macro क्रम snprपूर्णांक routines */
#घोषणा update_क्रम_len(total, len, size, str)	\
करो अणु					\
	माप_प्रकार ulen = len;		\
					\
	AA_BUG(len < 0);		\
	total += ulen;			\
	ulen = min(ulen, size);		\
	size -= ulen;			\
	str += ulen;			\
पूर्ण जबतक (0)

/**
 * aa_profile_snxprपूर्णांक - prपूर्णांक a profile name to a buffer
 * @str: buffer to ग_लिखो to. (MAY BE शून्य अगर @size == 0)
 * @size: size of buffer
 * @view: namespace profile is being viewed from
 * @profile: profile to view (NOT शून्य)
 * @flags: whether to include the mode string
 * @prev_ns: last ns prपूर्णांकed when used in compound prपूर्णांक
 *
 * Returns: size of name written or would be written अगर larger than
 *          available buffer
 *
 * Note: will not prपूर्णांक anything अगर the profile is not visible
 */
अटल पूर्णांक aa_profile_snxprपूर्णांक(अक्षर *str, माप_प्रकार size, काष्ठा aa_ns *view,
			       काष्ठा aa_profile *profile, पूर्णांक flags,
			       काष्ठा aa_ns **prev_ns)
अणु
	स्थिर अक्षर *ns_name = शून्य;

	AA_BUG(!str && size != 0);
	AA_BUG(!profile);

	अगर (!view)
		view = profiles_ns(profile);

	अगर (view != profile->ns &&
	    (!prev_ns || (*prev_ns != profile->ns))) अणु
		अगर (prev_ns)
			*prev_ns = profile->ns;
		ns_name = aa_ns_name(view, profile->ns,
				     flags & FLAG_VIEW_SUBNS);
		अगर (ns_name == aa_hidden_ns_name) अणु
			अगर (flags & FLAG_HIDDEN_UNCONFINED)
				वापस snम_लिखो(str, size, "%s", "unconfined");
			वापस snम_लिखो(str, size, "%s", ns_name);
		पूर्ण
	पूर्ण

	अगर ((flags & FLAG_SHOW_MODE) && profile != profile->ns->unconfined) अणु
		स्थिर अक्षर *modestr = aa_profile_mode_names[profile->mode];

		अगर (ns_name)
			वापस snम_लिखो(str, size, ":%s:%s (%s)", ns_name,
					profile->base.hname, modestr);
		वापस snम_लिखो(str, size, "%s (%s)", profile->base.hname,
				modestr);
	पूर्ण

	अगर (ns_name)
		वापस snम_लिखो(str, size, ":%s:%s", ns_name,
				profile->base.hname);
	वापस snम_लिखो(str, size, "%s", profile->base.hname);
पूर्ण

अटल स्थिर अक्षर *label_modename(काष्ठा aa_ns *ns, काष्ठा aa_label *label,
				  पूर्णांक flags)
अणु
	काष्ठा aa_profile *profile;
	काष्ठा label_it i;
	पूर्णांक mode = -1, count = 0;

	label_क्रम_each(i, label, profile) अणु
		अगर (aa_ns_visible(ns, profile->ns, flags & FLAG_VIEW_SUBNS)) अणु
			count++;
			अगर (profile == profile->ns->unconfined)
				/* special हाल unconfined so stacks with
				 * unconfined करोn't report as mixed. ie.
				 * profile_foo//&:ns1:unconfined (mixed)
				 */
				जारी;
			अगर (mode == -1)
				mode = profile->mode;
			अन्यथा अगर (mode != profile->mode)
				वापस "mixed";
		पूर्ण
	पूर्ण

	अगर (count == 0)
		वापस "-";
	अगर (mode == -1)
		/* everything was unconfined */
		mode = APPARMOR_UNCONFINED;

	वापस aa_profile_mode_names[mode];
पूर्ण

/* अगर any visible label is not unconfined the display_mode वापसs true */
अटल अंतरभूत bool display_mode(काष्ठा aa_ns *ns, काष्ठा aa_label *label,
				पूर्णांक flags)
अणु
	अगर ((flags & FLAG_SHOW_MODE)) अणु
		काष्ठा aa_profile *profile;
		काष्ठा label_it i;

		label_क्रम_each(i, label, profile) अणु
			अगर (aa_ns_visible(ns, profile->ns,
					  flags & FLAG_VIEW_SUBNS) &&
			    profile != profile->ns->unconfined)
				वापस true;
		पूर्ण
		/* only ns->unconfined in set of profiles in ns */
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

/**
 * aa_label_snxprपूर्णांक - prपूर्णांक a label name to a string buffer
 * @str: buffer to ग_लिखो to. (MAY BE शून्य अगर @size == 0)
 * @size: size of buffer
 * @ns: namespace profile is being viewed from
 * @label: label to view (NOT शून्य)
 * @flags: whether to include the mode string
 *
 * Returns: size of name written or would be written अगर larger than
 *          available buffer
 *
 * Note: labels करो not have to be strictly hierarchical to the ns as
 *       objects may be shared across dअगरferent namespaces and thus
 *       pickup labeling from each ns.  If a particular part of the
 *       label is not visible it will just be excluded.  And अगर none
 *       of the label is visible "---" will be used.
 */
पूर्णांक aa_label_snxprपूर्णांक(अक्षर *str, माप_प्रकार size, काष्ठा aa_ns *ns,
		      काष्ठा aa_label *label, पूर्णांक flags)
अणु
	काष्ठा aa_profile *profile;
	काष्ठा aa_ns *prev_ns = शून्य;
	काष्ठा label_it i;
	पूर्णांक count = 0, total = 0;
	sमाप_प्रकार len;

	AA_BUG(!str && size != 0);
	AA_BUG(!label);

	अगर (flags & FLAG_ABS_ROOT) अणु
		ns = root_ns;
		len = snम_लिखो(str, size, "=");
		update_क्रम_len(total, len, size, str);
	पूर्ण अन्यथा अगर (!ns) अणु
		ns = labels_ns(label);
	पूर्ण

	label_क्रम_each(i, label, profile) अणु
		अगर (aa_ns_visible(ns, profile->ns, flags & FLAG_VIEW_SUBNS)) अणु
			अगर (count > 0) अणु
				len = snम_लिखो(str, size, "//&");
				update_क्रम_len(total, len, size, str);
			पूर्ण
			len = aa_profile_snxprपूर्णांक(str, size, ns, profile,
						  flags & FLAG_VIEW_SUBNS,
						  &prev_ns);
			update_क्रम_len(total, len, size, str);
			count++;
		पूर्ण
	पूर्ण

	अगर (count == 0) अणु
		अगर (flags & FLAG_HIDDEN_UNCONFINED)
			वापस snम_लिखो(str, size, "%s", "unconfined");
		वापस snम_लिखो(str, size, "%s", aa_hidden_ns_name);
	पूर्ण

	/* count == 1 && ... is क्रम backwards compat where the mode
	 * is not displayed क्रम 'unconfined' in the current ns
	 */
	अगर (display_mode(ns, label, flags)) अणु
		len = snम_लिखो(str, size, " (%s)",
			       label_modename(ns, label, flags));
		update_क्रम_len(total, len, size, str);
	पूर्ण

	वापस total;
पूर्ण
#अघोषित update_क्रम_len

/**
 * aa_label_asxprपूर्णांक - allocate a string buffer and prपूर्णांक label पूर्णांकo it
 * @strp: Returns - the allocated buffer with the label name. (NOT शून्य)
 * @ns: namespace profile is being viewed from
 * @label: label to view (NOT शून्य)
 * @flags: flags controlling what label info is prपूर्णांकed
 * @gfp: kernel memory allocation type
 *
 * Returns: size of name written or would be written अगर larger than
 *          available buffer
 */
पूर्णांक aa_label_asxprपूर्णांक(अक्षर **strp, काष्ठा aa_ns *ns, काष्ठा aa_label *label,
		      पूर्णांक flags, gfp_t gfp)
अणु
	पूर्णांक size;

	AA_BUG(!strp);
	AA_BUG(!label);

	size = aa_label_snxprपूर्णांक(शून्य, 0, ns, label, flags);
	अगर (size < 0)
		वापस size;

	*strp = kदो_स्मृति(size + 1, gfp);
	अगर (!*strp)
		वापस -ENOMEM;
	वापस aa_label_snxprपूर्णांक(*strp, size + 1, ns, label, flags);
पूर्ण

/**
 * aa_label_acntsxprपूर्णांक - allocate a __counted string buffer and prपूर्णांक label
 * @strp: buffer to ग_लिखो to. (MAY BE शून्य अगर @size == 0)
 * @ns: namespace profile is being viewed from
 * @label: label to view (NOT शून्य)
 * @flags: flags controlling what label info is prपूर्णांकed
 * @gfp: kernel memory allocation type
 *
 * Returns: size of name written or would be written अगर larger than
 *          available buffer
 */
पूर्णांक aa_label_acntsxprपूर्णांक(अक्षर __counted **strp, काष्ठा aa_ns *ns,
			 काष्ठा aa_label *label, पूर्णांक flags, gfp_t gfp)
अणु
	पूर्णांक size;

	AA_BUG(!strp);
	AA_BUG(!label);

	size = aa_label_snxprपूर्णांक(शून्य, 0, ns, label, flags);
	अगर (size < 0)
		वापस size;

	*strp = aa_str_alloc(size + 1, gfp);
	अगर (!*strp)
		वापस -ENOMEM;
	वापस aa_label_snxprपूर्णांक(*strp, size + 1, ns, label, flags);
पूर्ण


व्योम aa_label_xaudit(काष्ठा audit_buffer *ab, काष्ठा aa_ns *ns,
		     काष्ठा aa_label *label, पूर्णांक flags, gfp_t gfp)
अणु
	स्थिर अक्षर *str;
	अक्षर *name = शून्य;
	पूर्णांक len;

	AA_BUG(!ab);
	AA_BUG(!label);

	अगर (!use_label_hname(ns, label, flags) ||
	    display_mode(ns, label, flags)) अणु
		len  = aa_label_asxprपूर्णांक(&name, ns, label, flags, gfp);
		अगर (len == -1) अणु
			AA_DEBUG("label print error");
			वापस;
		पूर्ण
		str = name;
	पूर्ण अन्यथा अणु
		str = (अक्षर *) label->hname;
		len = म_माप(str);
	पूर्ण
	अगर (audit_string_contains_control(str, len))
		audit_log_n_hex(ab, str, len);
	अन्यथा
		audit_log_n_string(ab, str, len);

	kमुक्त(name);
पूर्ण

व्योम aa_label_seq_xprपूर्णांक(काष्ठा seq_file *f, काष्ठा aa_ns *ns,
			 काष्ठा aa_label *label, पूर्णांक flags, gfp_t gfp)
अणु
	AA_BUG(!f);
	AA_BUG(!label);

	अगर (!use_label_hname(ns, label, flags)) अणु
		अक्षर *str;
		पूर्णांक len;

		len = aa_label_asxprपूर्णांक(&str, ns, label, flags, gfp);
		अगर (len == -1) अणु
			AA_DEBUG("label print error");
			वापस;
		पूर्ण
		seq_माला_दो(f, str);
		kमुक्त(str);
	पूर्ण अन्यथा अगर (display_mode(ns, label, flags))
		seq_म_लिखो(f, "%s (%s)", label->hname,
			   label_modename(ns, label, flags));
	अन्यथा
		seq_माला_दो(f, label->hname);
पूर्ण

व्योम aa_label_xprपूर्णांकk(काष्ठा aa_ns *ns, काष्ठा aa_label *label, पूर्णांक flags,
		      gfp_t gfp)
अणु
	AA_BUG(!label);

	अगर (!use_label_hname(ns, label, flags)) अणु
		अक्षर *str;
		पूर्णांक len;

		len = aa_label_asxprपूर्णांक(&str, ns, label, flags, gfp);
		अगर (len == -1) अणु
			AA_DEBUG("label print error");
			वापस;
		पूर्ण
		pr_info("%s", str);
		kमुक्त(str);
	पूर्ण अन्यथा अगर (display_mode(ns, label, flags))
		pr_info("%s (%s)", label->hname,
		       label_modename(ns, label, flags));
	अन्यथा
		pr_info("%s", label->hname);
पूर्ण

व्योम aa_label_audit(काष्ठा audit_buffer *ab, काष्ठा aa_label *label, gfp_t gfp)
अणु
	काष्ठा aa_ns *ns = aa_get_current_ns();

	aa_label_xaudit(ab, ns, label, FLAG_VIEW_SUBNS, gfp);
	aa_put_ns(ns);
पूर्ण

व्योम aa_label_seq_prपूर्णांक(काष्ठा seq_file *f, काष्ठा aa_label *label, gfp_t gfp)
अणु
	काष्ठा aa_ns *ns = aa_get_current_ns();

	aa_label_seq_xprपूर्णांक(f, ns, label, FLAG_VIEW_SUBNS, gfp);
	aa_put_ns(ns);
पूर्ण

व्योम aa_label_prपूर्णांकk(काष्ठा aa_label *label, gfp_t gfp)
अणु
	काष्ठा aa_ns *ns = aa_get_current_ns();

	aa_label_xprपूर्णांकk(ns, label, FLAG_VIEW_SUBNS, gfp);
	aa_put_ns(ns);
पूर्ण

अटल पूर्णांक label_count_strn_entries(स्थिर अक्षर *str, माप_प्रकार n)
अणु
	स्थिर अक्षर *end = str + n;
	स्थिर अक्षर *split;
	पूर्णांक count = 1;

	AA_BUG(!str);

	क्रम (split = aa_label_strn_split(str, end - str);
	     split;
	     split = aa_label_strn_split(str, end - str)) अणु
		count++;
		str = split + 3;
	पूर्ण

	वापस count;
पूर्ण

/*
 * ensure stacks with components like
 *   :ns:A//&B
 * have :ns: applied to both 'A' and 'B' by making the lookup relative
 * to the base अगर the lookup specअगरies an ns, अन्यथा making the stacked lookup
 * relative to the last embedded ns in the string.
 */
अटल काष्ठा aa_profile *fqlookupn_profile(काष्ठा aa_label *base,
					    काष्ठा aa_label *currentbase,
					    स्थिर अक्षर *str, माप_प्रकार n)
अणु
	स्थिर अक्षर *first = skipn_spaces(str, n);

	अगर (first && *first == ':')
		वापस aa_fqlookupn_profile(base, str, n);

	वापस aa_fqlookupn_profile(currentbase, str, n);
पूर्ण

/**
 * aa_label_strn_parse - parse, validate and convert a text string to a label
 * @base: base label to use क्रम lookups (NOT शून्य)
 * @str: null terminated text string (NOT शून्य)
 * @n: length of str to parse, will stop at \0 अगर encountered beक्रमe n
 * @gfp: allocation type
 * @create: true अगर should create compound labels अगर they करोn't exist
 * @क्रमce_stack: true अगर should stack even अगर no leading &
 *
 * Returns: the matching refcounted label अगर present
 *     अन्यथा ERRPTR
 */
काष्ठा aa_label *aa_label_strn_parse(काष्ठा aa_label *base, स्थिर अक्षर *str,
				     माप_प्रकार n, gfp_t gfp, bool create,
				     bool क्रमce_stack)
अणु
	DEFINE_VEC(profile, vec);
	काष्ठा aa_label *label, *currbase = base;
	पूर्णांक i, len, stack = 0, error;
	स्थिर अक्षर *end = str + n;
	स्थिर अक्षर *split;

	AA_BUG(!base);
	AA_BUG(!str);

	str = skipn_spaces(str, n);
	अगर (str == शून्य || (*str == '=' && base != &root_ns->unconfined->label))
		वापस ERR_PTR(-EINVAL);

	len = label_count_strn_entries(str, end - str);
	अगर (*str == '&' || क्रमce_stack) अणु
		/* stack on top of base */
		stack = base->size;
		len += stack;
		अगर (*str == '&')
			str++;
	पूर्ण

	error = vec_setup(profile, vec, len, gfp);
	अगर (error)
		वापस ERR_PTR(error);

	क्रम (i = 0; i < stack; i++)
		vec[i] = aa_get_profile(base->vec[i]);

	क्रम (split = aa_label_strn_split(str, end - str), i = stack;
	     split && i < len; i++) अणु
		vec[i] = fqlookupn_profile(base, currbase, str, split - str);
		अगर (!vec[i])
			जाओ fail;
		/*
		 * अगर component specअगरied a new ns it becomes the new base
		 * so that subsequent lookups are relative to it
		 */
		अगर (vec[i]->ns != labels_ns(currbase))
			currbase = &vec[i]->label;
		str = split + 3;
		split = aa_label_strn_split(str, end - str);
	पूर्ण
	/* last element करोesn't have a split */
	अगर (i < len) अणु
		vec[i] = fqlookupn_profile(base, currbase, str, end - str);
		अगर (!vec[i])
			जाओ fail;
	पूर्ण
	अगर (len == 1)
		/* no need to मुक्त vec as len < LOCAL_VEC_ENTRIES */
		वापस &vec[0]->label;

	len -= aa_vec_unique(vec, len, VEC_FLAG_TERMINATE);
	/* TODO: deal with reference labels */
	अगर (len == 1) अणु
		label = aa_get_label(&vec[0]->label);
		जाओ out;
	पूर्ण

	अगर (create)
		label = aa_vec_find_or_create_label(vec, len, gfp);
	अन्यथा
		label = vec_find(vec, len);
	अगर (!label)
		जाओ fail;

out:
	/* use adjusted len from after vec_unique, not original */
	vec_cleanup(profile, vec, len);
	वापस label;

fail:
	label = ERR_PTR(-ENOENT);
	जाओ out;
पूर्ण

काष्ठा aa_label *aa_label_parse(काष्ठा aa_label *base, स्थिर अक्षर *str,
				gfp_t gfp, bool create, bool क्रमce_stack)
अणु
	वापस aa_label_strn_parse(base, str, म_माप(str), gfp, create,
				   क्रमce_stack);
पूर्ण

/**
 * aa_labअन्यथाt_destroy - हटाओ all labels from the label set
 * @ls: label set to cleanup (NOT शून्य)
 *
 * Labels that are हटाओd from the set may still exist beyond the set
 * being destroyed depending on their reference counting
 */
व्योम aa_labअन्यथाt_destroy(काष्ठा aa_labअन्यथाt *ls)
अणु
	काष्ठा rb_node *node;
	अचिन्हित दीर्घ flags;

	AA_BUG(!ls);

	ग_लिखो_lock_irqsave(&ls->lock, flags);
	क्रम (node = rb_first(&ls->root); node; node = rb_first(&ls->root)) अणु
		काष्ठा aa_label *this = rb_entry(node, काष्ठा aa_label, node);

		अगर (labels_ns(this) != root_ns)
			__label_हटाओ(this,
				       ns_unconfined(labels_ns(this)->parent));
		अन्यथा
			__label_हटाओ(this, शून्य);
	पूर्ण
	ग_लिखो_unlock_irqrestore(&ls->lock, flags);
पूर्ण

/*
 * @ls: labअन्यथाt to init (NOT शून्य)
 */
व्योम aa_labअन्यथाt_init(काष्ठा aa_labअन्यथाt *ls)
अणु
	AA_BUG(!ls);

	rwlock_init(&ls->lock);
	ls->root = RB_ROOT;
पूर्ण

अटल काष्ठा aa_label *labअन्यथाt_next_stale(काष्ठा aa_labअन्यथाt *ls)
अणु
	काष्ठा aa_label *label;
	काष्ठा rb_node *node;
	अचिन्हित दीर्घ flags;

	AA_BUG(!ls);

	पढ़ो_lock_irqsave(&ls->lock, flags);

	__labअन्यथाt_क्रम_each(ls, node) अणु
		label = rb_entry(node, काष्ठा aa_label, node);
		अगर ((label_is_stale(label) ||
		     vec_is_stale(label->vec, label->size)) &&
		    __aa_get_label(label))
			जाओ out;

	पूर्ण
	label = शून्य;

out:
	पढ़ो_unlock_irqrestore(&ls->lock, flags);

	वापस label;
पूर्ण

/**
 * __label_update - insert updated version of @label पूर्णांकo labअन्यथाt
 * @label - the label to update/replace
 *
 * Returns: new label that is up to date
 *     अन्यथा शून्य on failure
 *
 * Requires: @ns lock be held
 *
 * Note: worst हाल is the stale @label करोes not get updated and has
 *       to be updated at a later समय.
 */
अटल काष्ठा aa_label *__label_update(काष्ठा aa_label *label)
अणु
	काष्ठा aa_label *new, *पंचांगp;
	काष्ठा aa_labअन्यथाt *ls;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, invcount = 0;

	AA_BUG(!label);
	AA_BUG(!mutex_is_locked(&labels_ns(label)->lock));

	new = aa_label_alloc(label->size, label->proxy, GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	/*
	 * जबतक holding the ns_lock will stop profile replacement, removal,
	 * and label updates, label merging and removal can be occurring
	 */
	ls = labels_set(label);
	ग_लिखो_lock_irqsave(&ls->lock, flags);
	क्रम (i = 0; i < label->size; i++) अणु
		AA_BUG(!label->vec[i]);
		new->vec[i] = aa_get_newest_profile(label->vec[i]);
		AA_BUG(!new->vec[i]);
		AA_BUG(!new->vec[i]->label.proxy);
		AA_BUG(!new->vec[i]->label.proxy->label);
		अगर (new->vec[i]->label.proxy != label->vec[i]->label.proxy)
			invcount++;
	पूर्ण

	/* updated stale label by being हटाओd/नामd from labअन्यथाt */
	अगर (invcount) अणु
		new->size -= aa_vec_unique(&new->vec[0], new->size,
					   VEC_FLAG_TERMINATE);
		/* TODO: deal with reference labels */
		अगर (new->size == 1) अणु
			पंचांगp = aa_get_label(&new->vec[0]->label);
			AA_BUG(पंचांगp == label);
			जाओ हटाओ;
		पूर्ण
		अगर (labels_set(label) != labels_set(new)) अणु
			ग_लिखो_unlock_irqrestore(&ls->lock, flags);
			पंचांगp = aa_label_insert(labels_set(new), new);
			ग_लिखो_lock_irqsave(&ls->lock, flags);
			जाओ हटाओ;
		पूर्ण
	पूर्ण अन्यथा
		AA_BUG(labels_ns(label) != labels_ns(new));

	पंचांगp = __label_insert(labels_set(label), new, true);
हटाओ:
	/* ensure label is हटाओd, and redirected correctly */
	__label_हटाओ(label, पंचांगp);
	ग_लिखो_unlock_irqrestore(&ls->lock, flags);
	label_मुक्त_or_put_new(पंचांगp, new);

	वापस पंचांगp;
पूर्ण

/**
 * __labअन्यथाt_update - update labels in @ns
 * @ns: namespace to update labels in  (NOT शून्य)
 *
 * Requires: @ns lock be held
 *
 * Walk the labअन्यथाt ensuring that all labels are up to date and valid
 * Any label that has a stale component is marked stale and replaced and
 * by an updated version.
 *
 * If failures happen due to memory pressures then stale labels will
 * be left in place until the next pass.
 */
अटल व्योम __labअन्यथाt_update(काष्ठा aa_ns *ns)
अणु
	काष्ठा aa_label *label;

	AA_BUG(!ns);
	AA_BUG(!mutex_is_locked(&ns->lock));

	करो अणु
		label = labअन्यथाt_next_stale(&ns->labels);
		अगर (label) अणु
			काष्ठा aa_label *l = __label_update(label);

			aa_put_label(l);
			aa_put_label(label);
		पूर्ण
	पूर्ण जबतक (label);
पूर्ण

/**
 * __aa_labअन्यथाt_udate_subtree - update all labels with a stale component
 * @ns: ns to start update at (NOT शून्य)
 *
 * Requires: @ns lock be held
 *
 * Invalidates labels based on @p in @ns and any children namespaces.
 */
व्योम __aa_labअन्यथाt_update_subtree(काष्ठा aa_ns *ns)
अणु
	काष्ठा aa_ns *child;

	AA_BUG(!ns);
	AA_BUG(!mutex_is_locked(&ns->lock));

	__labअन्यथाt_update(ns);

	list_क्रम_each_entry(child, &ns->sub_ns, base.list) अणु
		mutex_lock_nested(&child->lock, child->level);
		__aa_labअन्यथाt_update_subtree(child);
		mutex_unlock(&child->lock);
	पूर्ण
पूर्ण
