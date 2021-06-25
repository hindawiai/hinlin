<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RCULIST_BL_H
#घोषणा _LINUX_RCULIST_BL_H

/*
 * RCU-रक्षित bl list version. See include/linux/list_bl.h.
 */
#समावेश <linux/list_bl.h>
#समावेश <linux/rcupdate.h>

अटल अंतरभूत व्योम hlist_bl_set_first_rcu(काष्ठा hlist_bl_head *h,
					काष्ठा hlist_bl_node *n)
अणु
	LIST_BL_BUG_ON((अचिन्हित दीर्घ)n & LIST_BL_LOCKMASK);
	LIST_BL_BUG_ON(((अचिन्हित दीर्घ)h->first & LIST_BL_LOCKMASK) !=
							LIST_BL_LOCKMASK);
	rcu_assign_poपूर्णांकer(h->first,
		(काष्ठा hlist_bl_node *)((अचिन्हित दीर्घ)n | LIST_BL_LOCKMASK));
पूर्ण

अटल अंतरभूत काष्ठा hlist_bl_node *hlist_bl_first_rcu(काष्ठा hlist_bl_head *h)
अणु
	वापस (काष्ठा hlist_bl_node *)
		((अचिन्हित दीर्घ)rcu_dereference_check(h->first, hlist_bl_is_locked(h)) & ~LIST_BL_LOCKMASK);
पूर्ण

/**
 * hlist_bl_del_rcu - deletes entry from hash list without re-initialization
 * @n: the element to delete from the hash list.
 *
 * Note: hlist_bl_unhashed() on entry करोes not वापस true after this,
 * the entry is in an undefined state. It is useful क्रम RCU based
 * lockमुक्त traversal.
 *
 * In particular, it means that we can not poison the क्रमward
 * poपूर्णांकers that may still be used क्रम walking the hash list.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_bl_add_head_rcu()
 * or hlist_bl_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_bl_क्रम_each_entry().
 */
अटल अंतरभूत व्योम hlist_bl_del_rcu(काष्ठा hlist_bl_node *n)
अणु
	__hlist_bl_del(n);
	n->pprev = LIST_POISON2;
पूर्ण

/**
 * hlist_bl_add_head_rcu
 * @n: the element to add to the hash list.
 * @h: the list to add to.
 *
 * Description:
 * Adds the specअगरied element to the specअगरied hlist_bl,
 * जबतक permitting racing traversals.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_bl_add_head_rcu()
 * or hlist_bl_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_bl_क्रम_each_entry_rcu(), used to prevent memory-consistency
 * problems on Alpha CPUs.  Regardless of the type of CPU, the
 * list-traversal primitive must be guarded by rcu_पढ़ो_lock().
 */
अटल अंतरभूत व्योम hlist_bl_add_head_rcu(काष्ठा hlist_bl_node *n,
					काष्ठा hlist_bl_head *h)
अणु
	काष्ठा hlist_bl_node *first;

	/* करोn't need hlist_bl_first_rcu because we're under lock */
	first = hlist_bl_first(h);

	n->next = first;
	अगर (first)
		first->pprev = &n->next;
	n->pprev = &h->first;

	/* need _rcu because we can have concurrent lock मुक्त पढ़ोers */
	hlist_bl_set_first_rcu(h, n);
पूर्ण
/**
 * hlist_bl_क्रम_each_entry_rcu - iterate over rcu list of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा hlist_bl_node to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_bl_node within the काष्ठा.
 *
 */
#घोषणा hlist_bl_क्रम_each_entry_rcu(tpos, pos, head, member)		\
	क्रम (pos = hlist_bl_first_rcu(head);				\
		pos &&							\
		(अणु tpos = hlist_bl_entry(pos, typeof(*tpos), member); 1; पूर्ण); \
		pos = rcu_dereference_raw(pos->next))

#पूर्ण_अगर
