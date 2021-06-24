<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RCULIST_शून्यS_H
#घोषणा _LINUX_RCULIST_शून्यS_H

#अगर_घोषित __KERNEL__

/*
 * RCU-रक्षित list version
 */
#समावेश <linux/list_nulls.h>
#समावेश <linux/rcupdate.h>

/**
 * hlist_nulls_del_init_rcu - deletes entry from hash list with re-initialization
 * @n: the element to delete from the hash list.
 *
 * Note: hlist_nulls_unhashed() on the node वापस true after this. It is
 * useful क्रम RCU based पढ़ो lockमुक्त traversal अगर the ग_लिखोr side
 * must know अगर the list entry is still hashed or alपढ़ोy unhashed.
 *
 * In particular, it means that we can not poison the क्रमward poपूर्णांकers
 * that may still be used क्रम walking the hash list and we can only
 * zero the pprev poपूर्णांकer so list_unhashed() will वापस true after
 * this.
 *
 * The caller must take whatever precautions are necessary (such as
 * holding appropriate locks) to aव्योम racing with another
 * list-mutation primitive, such as hlist_nulls_add_head_rcu() or
 * hlist_nulls_del_rcu(), running on this same list.  However, it is
 * perfectly legal to run concurrently with the _rcu list-traversal
 * primitives, such as hlist_nulls_क्रम_each_entry_rcu().
 */
अटल अंतरभूत व्योम hlist_nulls_del_init_rcu(काष्ठा hlist_nulls_node *n)
अणु
	अगर (!hlist_nulls_unhashed(n)) अणु
		__hlist_nulls_del(n);
		WRITE_ONCE(n->pprev, शून्य);
	पूर्ण
पूर्ण

/**
 * hlist_nulls_first_rcu - वापसs the first element of the hash list.
 * @head: the head of the list.
 */
#घोषणा hlist_nulls_first_rcu(head) \
	(*((काष्ठा hlist_nulls_node __rcu __क्रमce **)&(head)->first))

/**
 * hlist_nulls_next_rcu - वापसs the element of the list after @node.
 * @node: element of the list.
 */
#घोषणा hlist_nulls_next_rcu(node) \
	(*((काष्ठा hlist_nulls_node __rcu __क्रमce **)&(node)->next))

/**
 * hlist_nulls_del_rcu - deletes entry from hash list without re-initialization
 * @n: the element to delete from the hash list.
 *
 * Note: hlist_nulls_unhashed() on entry करोes not वापस true after this,
 * the entry is in an undefined state. It is useful क्रम RCU based
 * lockमुक्त traversal.
 *
 * In particular, it means that we can not poison the क्रमward
 * poपूर्णांकers that may still be used क्रम walking the hash list.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_nulls_add_head_rcu()
 * or hlist_nulls_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_nulls_क्रम_each_entry().
 */
अटल अंतरभूत व्योम hlist_nulls_del_rcu(काष्ठा hlist_nulls_node *n)
अणु
	__hlist_nulls_del(n);
	WRITE_ONCE(n->pprev, LIST_POISON2);
पूर्ण

/**
 * hlist_nulls_add_head_rcu
 * @n: the element to add to the hash list.
 * @h: the list to add to.
 *
 * Description:
 * Adds the specअगरied element to the specअगरied hlist_nulls,
 * जबतक permitting racing traversals.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_nulls_add_head_rcu()
 * or hlist_nulls_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_nulls_क्रम_each_entry_rcu(), used to prevent memory-consistency
 * problems on Alpha CPUs.  Regardless of the type of CPU, the
 * list-traversal primitive must be guarded by rcu_पढ़ो_lock().
 */
अटल अंतरभूत व्योम hlist_nulls_add_head_rcu(काष्ठा hlist_nulls_node *n,
					काष्ठा hlist_nulls_head *h)
अणु
	काष्ठा hlist_nulls_node *first = h->first;

	n->next = first;
	WRITE_ONCE(n->pprev, &h->first);
	rcu_assign_poपूर्णांकer(hlist_nulls_first_rcu(h), n);
	अगर (!is_a_nulls(first))
		WRITE_ONCE(first->pprev, &n->next);
पूर्ण

/**
 * hlist_nulls_add_tail_rcu
 * @n: the element to add to the hash list.
 * @h: the list to add to.
 *
 * Description:
 * Adds the specअगरied element to the specअगरied hlist_nulls,
 * जबतक permitting racing traversals.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_nulls_add_head_rcu()
 * or hlist_nulls_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_nulls_क्रम_each_entry_rcu(), used to prevent memory-consistency
 * problems on Alpha CPUs.  Regardless of the type of CPU, the
 * list-traversal primitive must be guarded by rcu_पढ़ो_lock().
 */
अटल अंतरभूत व्योम hlist_nulls_add_tail_rcu(काष्ठा hlist_nulls_node *n,
					    काष्ठा hlist_nulls_head *h)
अणु
	काष्ठा hlist_nulls_node *i, *last = शून्य;

	/* Note: ग_लिखो side code, so rcu accessors are not needed. */
	क्रम (i = h->first; !is_a_nulls(i); i = i->next)
		last = i;

	अगर (last) अणु
		n->next = last->next;
		n->pprev = &last->next;
		rcu_assign_poपूर्णांकer(hlist_next_rcu(last), n);
	पूर्ण अन्यथा अणु
		hlist_nulls_add_head_rcu(n, h);
	पूर्ण
पूर्ण

/* after that hlist_nulls_del will work */
अटल अंतरभूत व्योम hlist_nulls_add_fake(काष्ठा hlist_nulls_node *n)
अणु
	n->pprev = &n->next;
	n->next = (काष्ठा hlist_nulls_node *)शून्यS_MARKER(शून्य);
पूर्ण

/**
 * hlist_nulls_क्रम_each_entry_rcu - iterate over rcu list of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा hlist_nulls_node to use as a loop cursor.
 * @head:	the head of the list.
 * @member:	the name of the hlist_nulls_node within the काष्ठा.
 *
 * The barrier() is needed to make sure compiler करोesn't cache first element [1],
 * as this loop can be restarted [2]
 * [1] Documentation/memory-barriers.txt around line 1533
 * [2] Documentation/RCU/rculist_nulls.rst around line 146
 */
#घोषणा hlist_nulls_क्रम_each_entry_rcu(tpos, pos, head, member)			\
	क्रम ((अणुbarrier();पूर्ण),							\
	     pos = rcu_dereference_raw(hlist_nulls_first_rcu(head));		\
		(!is_a_nulls(pos)) &&						\
		(अणु tpos = hlist_nulls_entry(pos, typeof(*tpos), member); 1; पूर्ण); \
		pos = rcu_dereference_raw(hlist_nulls_next_rcu(pos)))

/**
 * hlist_nulls_क्रम_each_entry_safe -
 *   iterate over list of given type safe against removal of list entry
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा hlist_nulls_node to use as a loop cursor.
 * @head:	the head of the list.
 * @member:	the name of the hlist_nulls_node within the काष्ठा.
 */
#घोषणा hlist_nulls_क्रम_each_entry_safe(tpos, pos, head, member)		\
	क्रम ((अणुbarrier();पूर्ण),							\
	     pos = rcu_dereference_raw(hlist_nulls_first_rcu(head));		\
		(!is_a_nulls(pos)) &&						\
		(अणु tpos = hlist_nulls_entry(pos, typeof(*tpos), member);	\
		   pos = rcu_dereference_raw(hlist_nulls_next_rcu(pos)); 1; पूर्ण);)
#पूर्ण_अगर
#पूर्ण_अगर
