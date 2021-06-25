<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 STRATO AG
 * written by Arne Jansen <sensille@gmx.net>
 */

#समावेश <linux/slab.h>
#समावेश "ulist.h"
#समावेश "ctree.h"

/*
 * ulist is a generic data काष्ठाure to hold a collection of unique u64
 * values. The only operations it supports is adding to the list and
 * क्रमागतerating it.
 * It is possible to store an auxiliary value aदीर्घ with the key.
 *
 * A sample usage क्रम ulists is the क्रमागतeration of directed graphs without
 * visiting a node twice. The pseuकरो-code could look like this:
 *
 * ulist = ulist_alloc();
 * ulist_add(ulist, root);
 * ULIST_ITER_INIT(&uiter);
 *
 * जबतक ((elem = ulist_next(ulist, &uiter)) अणु
 * 	क्रम (all child nodes n in elem)
 *		ulist_add(ulist, n);
 *	करो something useful with the node;
 * पूर्ण
 * ulist_मुक्त(ulist);
 *
 * This assumes the graph nodes are addressable by u64. This stems from the
 * usage क्रम tree क्रमागतeration in btrfs, where the logical addresses are
 * 64 bit.
 *
 * It is also useful क्रम tree क्रमागतeration which could be करोne elegantly
 * recursively, but is not possible due to kernel stack limitations. The
 * loop would be similar to the above.
 */

/**
 * ulist_init - freshly initialize a ulist
 * @ulist:	the ulist to initialize
 *
 * Note: करोn't use this function to init an alपढ़ोy used ulist, use
 * ulist_reinit instead.
 */
व्योम ulist_init(काष्ठा ulist *ulist)
अणु
	INIT_LIST_HEAD(&ulist->nodes);
	ulist->root = RB_ROOT;
	ulist->nnodes = 0;
पूर्ण

/**
 * ulist_release - मुक्त up additionally allocated memory क्रम the ulist
 * @ulist:	the ulist from which to मुक्त the additional memory
 *
 * This is useful in हालs where the base 'struct ulist' has been अटलally
 * allocated.
 */
व्योम ulist_release(काष्ठा ulist *ulist)
अणु
	काष्ठा ulist_node *node;
	काष्ठा ulist_node *next;

	list_क्रम_each_entry_safe(node, next, &ulist->nodes, list) अणु
		kमुक्त(node);
	पूर्ण
	ulist->root = RB_ROOT;
	INIT_LIST_HEAD(&ulist->nodes);
पूर्ण

/**
 * ulist_reinit - prepare a ulist क्रम reuse
 * @ulist:	ulist to be reused
 *
 * Free up all additional memory allocated क्रम the list elements and reinit
 * the ulist.
 */
व्योम ulist_reinit(काष्ठा ulist *ulist)
अणु
	ulist_release(ulist);
	ulist_init(ulist);
पूर्ण

/**
 * ulist_alloc - dynamically allocate a ulist
 * @gfp_mask:	allocation flags to क्रम base allocation
 *
 * The allocated ulist will be वापसed in an initialized state.
 */
काष्ठा ulist *ulist_alloc(gfp_t gfp_mask)
अणु
	काष्ठा ulist *ulist = kदो_स्मृति(माप(*ulist), gfp_mask);

	अगर (!ulist)
		वापस शून्य;

	ulist_init(ulist);

	वापस ulist;
पूर्ण

/**
 * ulist_मुक्त - मुक्त dynamically allocated ulist
 * @ulist:	ulist to मुक्त
 *
 * It is not necessary to call ulist_release beक्रमe.
 */
व्योम ulist_मुक्त(काष्ठा ulist *ulist)
अणु
	अगर (!ulist)
		वापस;
	ulist_release(ulist);
	kमुक्त(ulist);
पूर्ण

अटल काष्ठा ulist_node *ulist_rbtree_search(काष्ठा ulist *ulist, u64 val)
अणु
	काष्ठा rb_node *n = ulist->root.rb_node;
	काष्ठा ulist_node *u = शून्य;

	जबतक (n) अणु
		u = rb_entry(n, काष्ठा ulist_node, rb_node);
		अगर (u->val < val)
			n = n->rb_right;
		अन्यथा अगर (u->val > val)
			n = n->rb_left;
		अन्यथा
			वापस u;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम ulist_rbtree_erase(काष्ठा ulist *ulist, काष्ठा ulist_node *node)
अणु
	rb_erase(&node->rb_node, &ulist->root);
	list_del(&node->list);
	kमुक्त(node);
	BUG_ON(ulist->nnodes == 0);
	ulist->nnodes--;
पूर्ण

अटल पूर्णांक ulist_rbtree_insert(काष्ठा ulist *ulist, काष्ठा ulist_node *ins)
अणु
	काष्ठा rb_node **p = &ulist->root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा ulist_node *cur = शून्य;

	जबतक (*p) अणु
		parent = *p;
		cur = rb_entry(parent, काष्ठा ulist_node, rb_node);

		अगर (cur->val < ins->val)
			p = &(*p)->rb_right;
		अन्यथा अगर (cur->val > ins->val)
			p = &(*p)->rb_left;
		अन्यथा
			वापस -EEXIST;
	पूर्ण
	rb_link_node(&ins->rb_node, parent, p);
	rb_insert_color(&ins->rb_node, &ulist->root);
	वापस 0;
पूर्ण

/**
 * ulist_add - add an element to the ulist
 * @ulist:	ulist to add the element to
 * @val:	value to add to ulist
 * @aux:	auxiliary value to store aदीर्घ with val
 * @gfp_mask:	flags to use क्रम allocation
 *
 * Note: locking must be provided by the caller. In हाल of rwlocks ग_लिखो
 *       locking is needed
 *
 * Add an element to a ulist. The @val will only be added अगर it करोesn't
 * alपढ़ोy exist. If it is added, the auxiliary value @aux is stored aदीर्घ with
 * it. In हाल @val alपढ़ोy exists in the ulist, @aux is ignored, even अगर
 * it dअगरfers from the alपढ़ोy stored value.
 *
 * ulist_add वापसs 0 अगर @val alपढ़ोy exists in ulist and 1 अगर @val has been
 * inserted.
 * In हाल of allocation failure -ENOMEM is वापसed and the ulist stays
 * unaltered.
 */
पूर्णांक ulist_add(काष्ठा ulist *ulist, u64 val, u64 aux, gfp_t gfp_mask)
अणु
	वापस ulist_add_merge(ulist, val, aux, शून्य, gfp_mask);
पूर्ण

पूर्णांक ulist_add_merge(काष्ठा ulist *ulist, u64 val, u64 aux,
		    u64 *old_aux, gfp_t gfp_mask)
अणु
	पूर्णांक ret;
	काष्ठा ulist_node *node;

	node = ulist_rbtree_search(ulist, val);
	अगर (node) अणु
		अगर (old_aux)
			*old_aux = node->aux;
		वापस 0;
	पूर्ण
	node = kदो_स्मृति(माप(*node), gfp_mask);
	अगर (!node)
		वापस -ENOMEM;

	node->val = val;
	node->aux = aux;

	ret = ulist_rbtree_insert(ulist, node);
	ASSERT(!ret);
	list_add_tail(&node->list, &ulist->nodes);
	ulist->nnodes++;

	वापस 1;
पूर्ण

/*
 * ulist_del - delete one node from ulist
 * @ulist:	ulist to हटाओ node from
 * @val:	value to delete
 * @aux:	aux to delete
 *
 * The deletion will only be करोne when *BOTH* val and aux matches.
 * Return 0 क्रम successful delete.
 * Return > 0 क्रम not found.
 */
पूर्णांक ulist_del(काष्ठा ulist *ulist, u64 val, u64 aux)
अणु
	काष्ठा ulist_node *node;

	node = ulist_rbtree_search(ulist, val);
	/* Not found */
	अगर (!node)
		वापस 1;

	अगर (node->aux != aux)
		वापस 1;

	/* Found and delete */
	ulist_rbtree_erase(ulist, node);
	वापस 0;
पूर्ण

/**
 * ulist_next - iterate ulist
 * @ulist:	ulist to iterate
 * @uiter:	iterator variable, initialized with ULIST_ITER_INIT(&iterator)
 *
 * Note: locking must be provided by the caller. In हाल of rwlocks only पढ़ो
 *       locking is needed
 *
 * This function is used to iterate an ulist.
 * It वापसs the next element from the ulist or %शून्य when the
 * end is reached. No guarantee is made with respect to the order in which
 * the elements are वापसed. They might neither be वापसed in order of
 * addition nor in ascending order.
 * It is allowed to call ulist_add during an क्रमागतeration. Newly added items
 * are guaranteed to show up in the running क्रमागतeration.
 */
काष्ठा ulist_node *ulist_next(काष्ठा ulist *ulist, काष्ठा ulist_iterator *uiter)
अणु
	काष्ठा ulist_node *node;

	अगर (list_empty(&ulist->nodes))
		वापस शून्य;
	अगर (uiter->cur_list && uiter->cur_list->next == &ulist->nodes)
		वापस शून्य;
	अगर (uiter->cur_list) अणु
		uiter->cur_list = uiter->cur_list->next;
	पूर्ण अन्यथा अणु
		uiter->cur_list = ulist->nodes.next;
	पूर्ण
	node = list_entry(uiter->cur_list, काष्ठा ulist_node, list);
	वापस node;
पूर्ण
