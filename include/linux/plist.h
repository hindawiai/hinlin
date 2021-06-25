<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Descending-priority-sorted द्विगुन-linked list
 *
 * (C) 2002-2003 Intel Corp
 * Inaky Perez-Gonzalez <inaky.perez-gonzalez@पूर्णांकel.com>.
 *
 * 2001-2005 (c) MontaVista Software, Inc.
 * Daniel Walker <dwalker@mvista.com>
 *
 * (C) 2005 Thomas Gleixner <tglx@linutronix.de>
 *
 * Simplअगरications of the original code by
 * Oleg Nesterov <oleg@tv-sign.ru>
 *
 * Based on simple lists (include/linux/list.h).
 *
 * This is a priority-sorted list of nodes; each node has a
 * priority from पूर्णांक_न्यून (highest) to पूर्णांक_उच्च (lowest).
 *
 * Addition is O(K), removal is O(1), change of priority of a node is
 * O(K) and K is the number of RT priority levels used in the प्रणाली.
 * (1 <= K <= 99)
 *
 * This list is really a list of lists:
 *
 *  - The tier 1 list is the prio_list, dअगरferent priority nodes.
 *
 *  - The tier 2 list is the node_list, serialized nodes.
 *
 * Simple ASCII art explanation:
 *
 * pl:prio_list (only क्रम plist_node)
 * nl:node_list
 *   HEAD|             NODE(S)
 *       |
 *       ||------------------------------------|
 *       ||->|pl|<->|pl|<--------------->|pl|<-|
 *       |   |10|   |21|   |21|   |21|   |40|   (prio)
 *       |   |  |   |  |   |  |   |  |   |  |
 *       |   |  |   |  |   |  |   |  |   |  |
 * |->|nl|<->|nl|<->|nl|<->|nl|<->|nl|<->|nl|<-|
 * |-------------------------------------------|
 *
 * The nodes on the prio_list list are sorted by priority to simplअगरy
 * the insertion of new nodes. There are no nodes with duplicate
 * priorites on the list.
 *
 * The nodes on the node_list are ordered by priority and can contain
 * entries which have the same priority. Those entries are ordered
 * FIFO
 *
 * Addition means: look क्रम the prio_list node in the prio_list
 * क्रम the priority of the node and insert it beक्रमe the node_list
 * entry of the next prio_list node. If it is the first node of
 * that priority, add it to the prio_list in the right position and
 * insert it पूर्णांकo the serialized node_list list
 *
 * Removal means हटाओ it from the node_list and हटाओ it from
 * the prio_list अगर the node_list list_head is non empty. In हाल
 * of removal from the prio_list it must be checked whether other
 * entries of the same priority are on the list or not. If there
 * is another entry of the same priority then this entry has to
 * replace the हटाओd entry on the prio_list. If the entry which
 * is हटाओd is the only entry of this priority then a simple
 * हटाओ from both list is sufficient.
 *
 * पूर्णांक_न्यून is the highest priority, 0 is the medium highest, पूर्णांक_उच्च
 * is lowest priority.
 *
 * No locking is करोne, up to the caller.
 */
#अगर_अघोषित _LINUX_PLIST_H_
#घोषणा _LINUX_PLIST_H_

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>

काष्ठा plist_head अणु
	काष्ठा list_head node_list;
पूर्ण;

काष्ठा plist_node अणु
	पूर्णांक			prio;
	काष्ठा list_head	prio_list;
	काष्ठा list_head	node_list;
पूर्ण;

/**
 * PLIST_HEAD_INIT - अटल काष्ठा plist_head initializer
 * @head:	काष्ठा plist_head variable name
 */
#घोषणा PLIST_HEAD_INIT(head)				\
अणु							\
	.node_list = LIST_HEAD_INIT((head).node_list)	\
पूर्ण

/**
 * PLIST_HEAD - declare and init plist_head
 * @head:	name क्रम काष्ठा plist_head variable
 */
#घोषणा PLIST_HEAD(head) \
	काष्ठा plist_head head = PLIST_HEAD_INIT(head)

/**
 * PLIST_NODE_INIT - अटल काष्ठा plist_node initializer
 * @node:	काष्ठा plist_node variable name
 * @__prio:	initial node priority
 */
#घोषणा PLIST_NODE_INIT(node, __prio)			\
अणु							\
	.prio  = (__prio),				\
	.prio_list = LIST_HEAD_INIT((node).prio_list),	\
	.node_list = LIST_HEAD_INIT((node).node_list),	\
पूर्ण

/**
 * plist_head_init - dynamic काष्ठा plist_head initializer
 * @head:	&काष्ठा plist_head poपूर्णांकer
 */
अटल अंतरभूत व्योम
plist_head_init(काष्ठा plist_head *head)
अणु
	INIT_LIST_HEAD(&head->node_list);
पूर्ण

/**
 * plist_node_init - Dynamic काष्ठा plist_node initializer
 * @node:	&काष्ठा plist_node poपूर्णांकer
 * @prio:	initial node priority
 */
अटल अंतरभूत व्योम plist_node_init(काष्ठा plist_node *node, पूर्णांक prio)
अणु
	node->prio = prio;
	INIT_LIST_HEAD(&node->prio_list);
	INIT_LIST_HEAD(&node->node_list);
पूर्ण

बाह्य व्योम plist_add(काष्ठा plist_node *node, काष्ठा plist_head *head);
बाह्य व्योम plist_del(काष्ठा plist_node *node, काष्ठा plist_head *head);

बाह्य व्योम plist_requeue(काष्ठा plist_node *node, काष्ठा plist_head *head);

/**
 * plist_क्रम_each - iterate over the plist
 * @pos:	the type * to use as a loop counter
 * @head:	the head क्रम your list
 */
#घोषणा plist_क्रम_each(pos, head)	\
	 list_क्रम_each_entry(pos, &(head)->node_list, node_list)

/**
 * plist_क्रम_each_जारी - जारी iteration over the plist
 * @pos:	the type * to use as a loop cursor
 * @head:	the head क्रम your list
 *
 * Continue to iterate over plist, continuing after the current position.
 */
#घोषणा plist_क्रम_each_जारी(pos, head)	\
	 list_क्रम_each_entry_जारी(pos, &(head)->node_list, node_list)

/**
 * plist_क्रम_each_safe - iterate safely over a plist of given type
 * @pos:	the type * to use as a loop counter
 * @n:	another type * to use as temporary storage
 * @head:	the head क्रम your list
 *
 * Iterate over a plist of given type, safe against removal of list entry.
 */
#घोषणा plist_क्रम_each_safe(pos, n, head)	\
	 list_क्रम_each_entry_safe(pos, n, &(head)->node_list, node_list)

/**
 * plist_क्रम_each_entry	- iterate over list of given type
 * @pos:	the type * to use as a loop counter
 * @head:	the head क्रम your list
 * @mem:	the name of the list_head within the काष्ठा
 */
#घोषणा plist_क्रम_each_entry(pos, head, mem)	\
	 list_क्रम_each_entry(pos, &(head)->node_list, mem.node_list)

/**
 * plist_क्रम_each_entry_जारी - जारी iteration over list of given type
 * @pos:	the type * to use as a loop cursor
 * @head:	the head क्रम your list
 * @m:		the name of the list_head within the काष्ठा
 *
 * Continue to iterate over list of given type, continuing after
 * the current position.
 */
#घोषणा plist_क्रम_each_entry_जारी(pos, head, m)	\
	list_क्रम_each_entry_जारी(pos, &(head)->node_list, m.node_list)

/**
 * plist_क्रम_each_entry_safe - iterate safely over list of given type
 * @pos:	the type * to use as a loop counter
 * @n:		another type * to use as temporary storage
 * @head:	the head क्रम your list
 * @m:		the name of the list_head within the काष्ठा
 *
 * Iterate over list of given type, safe against removal of list entry.
 */
#घोषणा plist_क्रम_each_entry_safe(pos, n, head, m)	\
	list_क्रम_each_entry_safe(pos, n, &(head)->node_list, m.node_list)

/**
 * plist_head_empty - वापस !0 अगर a plist_head is empty
 * @head:	&काष्ठा plist_head poपूर्णांकer
 */
अटल अंतरभूत पूर्णांक plist_head_empty(स्थिर काष्ठा plist_head *head)
अणु
	वापस list_empty(&head->node_list);
पूर्ण

/**
 * plist_node_empty - वापस !0 अगर plist_node is not on a list
 * @node:	&काष्ठा plist_node poपूर्णांकer
 */
अटल अंतरभूत पूर्णांक plist_node_empty(स्थिर काष्ठा plist_node *node)
अणु
	वापस list_empty(&node->node_list);
पूर्ण

/* All functions below assume the plist_head is not empty. */

/**
 * plist_first_entry - get the काष्ठा क्रम the first entry
 * @head:	the &काष्ठा plist_head poपूर्णांकer
 * @type:	the type of the काष्ठा this is embedded in
 * @member:	the name of the list_head within the काष्ठा
 */
#अगर_घोषित CONFIG_DEBUG_PLIST
# define plist_first_entry(head, type, member)	\
(अणु \
	WARN_ON(plist_head_empty(head)); \
	container_of(plist_first(head), type, member); \
पूर्ण)
#अन्यथा
# define plist_first_entry(head, type, member)	\
	container_of(plist_first(head), type, member)
#पूर्ण_अगर

/**
 * plist_last_entry - get the काष्ठा क्रम the last entry
 * @head:	the &काष्ठा plist_head poपूर्णांकer
 * @type:	the type of the काष्ठा this is embedded in
 * @member:	the name of the list_head within the काष्ठा
 */
#अगर_घोषित CONFIG_DEBUG_PLIST
# define plist_last_entry(head, type, member)	\
(अणु \
	WARN_ON(plist_head_empty(head)); \
	container_of(plist_last(head), type, member); \
पूर्ण)
#अन्यथा
# define plist_last_entry(head, type, member)	\
	container_of(plist_last(head), type, member)
#पूर्ण_अगर

/**
 * plist_next - get the next entry in list
 * @pos:	the type * to cursor
 */
#घोषणा plist_next(pos) \
	list_next_entry(pos, node_list)

/**
 * plist_prev - get the prev entry in list
 * @pos:	the type * to cursor
 */
#घोषणा plist_prev(pos) \
	list_prev_entry(pos, node_list)

/**
 * plist_first - वापस the first node (and thus, highest priority)
 * @head:	the &काष्ठा plist_head poपूर्णांकer
 *
 * Assumes the plist is _not_ empty.
 */
अटल अंतरभूत काष्ठा plist_node *plist_first(स्थिर काष्ठा plist_head *head)
अणु
	वापस list_entry(head->node_list.next,
			  काष्ठा plist_node, node_list);
पूर्ण

/**
 * plist_last - वापस the last node (and thus, lowest priority)
 * @head:	the &काष्ठा plist_head poपूर्णांकer
 *
 * Assumes the plist is _not_ empty.
 */
अटल अंतरभूत काष्ठा plist_node *plist_last(स्थिर काष्ठा plist_head *head)
अणु
	वापस list_entry(head->node_list.prev,
			  काष्ठा plist_node, node_list);
पूर्ण

#पूर्ण_अगर
