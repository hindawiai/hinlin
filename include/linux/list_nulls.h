<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LIST_शून्यS_H
#घोषणा _LINUX_LIST_शून्यS_H

#समावेश <linux/poison.h>
#समावेश <linux/स्थिर.h>

/*
 * Special version of lists, where end of list is not a शून्य poपूर्णांकer,
 * but a 'nulls' marker, which can have many dअगरferent values.
 * (up to 2^31 dअगरferent values guaranteed on all platक्रमms)
 *
 * In the standard hlist, termination of a list is the शून्य poपूर्णांकer.
 * In this special 'nulls' variant, we use the fact that objects stored in
 * a list are aligned on a word (4 or 8 bytes alignment).
 * We thereक्रमe use the last signअगरicant bit of 'ptr' :
 * Set to 1 : This is a 'nulls' end-of-list marker (ptr >> 1)
 * Set to 0 : This is a poपूर्णांकer to some object (ptr)
 */

काष्ठा hlist_nulls_head अणु
	काष्ठा hlist_nulls_node *first;
पूर्ण;

काष्ठा hlist_nulls_node अणु
	काष्ठा hlist_nulls_node *next, **pprev;
पूर्ण;
#घोषणा शून्यS_MARKER(value) (1UL | (((दीर्घ)value) << 1))
#घोषणा INIT_HLIST_शून्यS_HEAD(ptr, nulls) \
	((ptr)->first = (काष्ठा hlist_nulls_node *) शून्यS_MARKER(nulls))

#घोषणा hlist_nulls_entry(ptr, type, member) container_of(ptr,type,member)

#घोषणा hlist_nulls_entry_safe(ptr, type, member) \
	(अणु typeof(ptr) ____ptr = (ptr); \
	   !is_a_nulls(____ptr) ? hlist_nulls_entry(____ptr, type, member) : शून्य; \
	पूर्ण)
/**
 * ptr_is_a_nulls - Test अगर a ptr is a nulls
 * @ptr: ptr to be tested
 *
 */
अटल अंतरभूत पूर्णांक is_a_nulls(स्थिर काष्ठा hlist_nulls_node *ptr)
अणु
	वापस ((अचिन्हित दीर्घ)ptr & 1);
पूर्ण

/**
 * get_nulls_value - Get the 'nulls' value of the end of chain
 * @ptr: end of chain
 *
 * Should be called only अगर is_a_nulls(ptr);
 */
अटल अंतरभूत अचिन्हित दीर्घ get_nulls_value(स्थिर काष्ठा hlist_nulls_node *ptr)
अणु
	वापस ((अचिन्हित दीर्घ)ptr) >> 1;
पूर्ण

/**
 * hlist_nulls_unhashed - Has node been हटाओd and reinitialized?
 * @h: Node to be checked
 *
 * Not that not all removal functions will leave a node in unhashed state.
 * For example, hlist_del_init_rcu() leaves the node in unhashed state,
 * but hlist_nulls_del() करोes not.
 */
अटल अंतरभूत पूर्णांक hlist_nulls_unhashed(स्थिर काष्ठा hlist_nulls_node *h)
अणु
	वापस !h->pprev;
पूर्ण

/**
 * hlist_nulls_unhashed_lockless - Has node been हटाओd and reinitialized?
 * @h: Node to be checked
 *
 * Not that not all removal functions will leave a node in unhashed state.
 * For example, hlist_del_init_rcu() leaves the node in unhashed state,
 * but hlist_nulls_del() करोes not.  Unlike hlist_nulls_unhashed(), this
 * function may be used locklessly.
 */
अटल अंतरभूत पूर्णांक hlist_nulls_unhashed_lockless(स्थिर काष्ठा hlist_nulls_node *h)
अणु
	वापस !READ_ONCE(h->pprev);
पूर्ण

अटल अंतरभूत पूर्णांक hlist_nulls_empty(स्थिर काष्ठा hlist_nulls_head *h)
अणु
	वापस is_a_nulls(READ_ONCE(h->first));
पूर्ण

अटल अंतरभूत व्योम hlist_nulls_add_head(काष्ठा hlist_nulls_node *n,
					काष्ठा hlist_nulls_head *h)
अणु
	काष्ठा hlist_nulls_node *first = h->first;

	n->next = first;
	WRITE_ONCE(n->pprev, &h->first);
	h->first = n;
	अगर (!is_a_nulls(first))
		WRITE_ONCE(first->pprev, &n->next);
पूर्ण

अटल अंतरभूत व्योम __hlist_nulls_del(काष्ठा hlist_nulls_node *n)
अणु
	काष्ठा hlist_nulls_node *next = n->next;
	काष्ठा hlist_nulls_node **pprev = n->pprev;

	WRITE_ONCE(*pprev, next);
	अगर (!is_a_nulls(next))
		WRITE_ONCE(next->pprev, pprev);
पूर्ण

अटल अंतरभूत व्योम hlist_nulls_del(काष्ठा hlist_nulls_node *n)
अणु
	__hlist_nulls_del(n);
	WRITE_ONCE(n->pprev, LIST_POISON2);
पूर्ण

/**
 * hlist_nulls_क्रम_each_entry	- iterate over list of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा hlist_node to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 *
 */
#घोषणा hlist_nulls_क्रम_each_entry(tpos, pos, head, member)		       \
	क्रम (pos = (head)->first;					       \
	     (!is_a_nulls(pos)) &&					       \
		(अणु tpos = hlist_nulls_entry(pos, typeof(*tpos), member); 1;पूर्ण); \
	     pos = pos->next)

/**
 * hlist_nulls_क्रम_each_entry_from - iterate over a hlist continuing from current poपूर्णांक
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा hlist_node to use as a loop cursor.
 * @member:	the name of the hlist_node within the काष्ठा.
 *
 */
#घोषणा hlist_nulls_क्रम_each_entry_from(tpos, pos, member)	\
	क्रम (; (!is_a_nulls(pos)) && 				\
		(अणु tpos = hlist_nulls_entry(pos, typeof(*tpos), member); 1;पूर्ण); \
	     pos = pos->next)

#पूर्ण_अगर
