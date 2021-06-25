<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित LLIST_H
#घोषणा LLIST_H
/*
 * Lock-less शून्य terminated single linked list
 *
 * Cases where locking is not needed:
 * If there are multiple producers and multiple consumers, llist_add can be
 * used in producers and llist_del_all can be used in consumers simultaneously
 * without locking. Also a single consumer can use llist_del_first जबतक
 * multiple producers simultaneously use llist_add, without any locking.
 *
 * Cases where locking is needed:
 * If we have multiple consumers with llist_del_first used in one consumer, and
 * llist_del_first or llist_del_all used in other consumers, then a lock is
 * needed.  This is because llist_del_first depends on list->first->next not
 * changing, but without lock protection, there's no way to be sure about that
 * अगर a preemption happens in the middle of the delete operation and on being
 * preempted back, the list->first is the same as beक्रमe causing the cmpxchg in
 * llist_del_first to succeed. For example, जबतक a llist_del_first operation
 * is in progress in one consumer, then a llist_del_first, llist_add,
 * llist_add (or llist_del_all, llist_add, llist_add) sequence in another
 * consumer may cause violations.
 *
 * This can be summarized as follows:
 *
 *           |   add    | del_first |  del_all
 * add       |    -     |     -     |     -
 * del_first |          |     L     |     L
 * del_all   |          |           |     -
 *
 * Where, a particular row's operation can happen concurrently with a column's
 * operation, with "-" being no lock needed, जबतक "L" being lock is needed.
 *
 * The list entries deleted via llist_del_all can be traversed with
 * traversing function such as llist_क्रम_each etc.  But the list
 * entries can not be traversed safely beक्रमe deleted from the list.
 * The order of deleted entries is from the newest to the oldest added
 * one.  If you want to traverse from the oldest to the newest, you
 * must reverse the order by yourself beक्रमe traversing.
 *
 * The basic atomic operation of this list is cmpxchg on दीर्घ.  On
 * architectures that करोn't have NMI-safe cmpxchg implementation, the
 * list can NOT be used in NMI handlers.  So code that uses the list in
 * an NMI handler should depend on CONFIG_ARCH_HAVE_NMI_SAFE_CMPXCHG.
 *
 * Copyright 2010,2011 Intel Corp.
 *   Author: Huang Ying <ying.huang@पूर्णांकel.com>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>

काष्ठा llist_head अणु
	काष्ठा llist_node *first;
पूर्ण;

काष्ठा llist_node अणु
	काष्ठा llist_node *next;
पूर्ण;

#घोषणा LLIST_HEAD_INIT(name)	अणु शून्य पूर्ण
#घोषणा LLIST_HEAD(name)	काष्ठा llist_head name = LLIST_HEAD_INIT(name)

/**
 * init_llist_head - initialize lock-less list head
 * @head:	the head क्रम your lock-less list
 */
अटल अंतरभूत व्योम init_llist_head(काष्ठा llist_head *list)
अणु
	list->first = शून्य;
पूर्ण

/**
 * llist_entry - get the काष्ठा of this entry
 * @ptr:	the &काष्ठा llist_node poपूर्णांकer.
 * @type:	the type of the काष्ठा this is embedded in.
 * @member:	the name of the llist_node within the काष्ठा.
 */
#घोषणा llist_entry(ptr, type, member)		\
	container_of(ptr, type, member)

/**
 * member_address_is_nonnull - check whether the member address is not शून्य
 * @ptr:	the object poपूर्णांकer (काष्ठा type * that contains the llist_node)
 * @member:	the name of the llist_node within the काष्ठा.
 *
 * This macro is conceptually the same as
 *	&ptr->member != शून्य
 * but it works around the fact that compilers can decide that taking a member
 * address is never a शून्य poपूर्णांकer.
 *
 * Real objects that start at a high address and have a member at शून्य are
 * unlikely to exist, but such poपूर्णांकers may be वापसed e.g. by the
 * container_of() macro.
 */
#घोषणा member_address_is_nonnull(ptr, member)	\
	((uपूर्णांकptr_t)(ptr) + दुरत्व(typeof(*(ptr)), member) != 0)

/**
 * llist_क्रम_each - iterate over some deleted entries of a lock-less list
 * @pos:	the &काष्ठा llist_node to use as a loop cursor
 * @node:	the first entry of deleted list entries
 *
 * In general, some entries of the lock-less list can be traversed
 * safely only after being deleted from list, so start with an entry
 * instead of list head.
 *
 * If being used on entries deleted from lock-less list directly, the
 * traverse order is from the newest to the oldest added entry.  If
 * you want to traverse from the oldest to the newest, you must
 * reverse the order by yourself beक्रमe traversing.
 */
#घोषणा llist_क्रम_each(pos, node)			\
	क्रम ((pos) = (node); pos; (pos) = (pos)->next)

/**
 * llist_क्रम_each_safe - iterate over some deleted entries of a lock-less list
 *			 safe against removal of list entry
 * @pos:	the &काष्ठा llist_node to use as a loop cursor
 * @n:		another &काष्ठा llist_node to use as temporary storage
 * @node:	the first entry of deleted list entries
 *
 * In general, some entries of the lock-less list can be traversed
 * safely only after being deleted from list, so start with an entry
 * instead of list head.
 *
 * If being used on entries deleted from lock-less list directly, the
 * traverse order is from the newest to the oldest added entry.  If
 * you want to traverse from the oldest to the newest, you must
 * reverse the order by yourself beक्रमe traversing.
 */
#घोषणा llist_क्रम_each_safe(pos, n, node)			\
	क्रम ((pos) = (node); (pos) && ((n) = (pos)->next, true); (pos) = (n))

/**
 * llist_क्रम_each_entry - iterate over some deleted entries of lock-less list of given type
 * @pos:	the type * to use as a loop cursor.
 * @node:	the fist entry of deleted list entries.
 * @member:	the name of the llist_node with the काष्ठा.
 *
 * In general, some entries of the lock-less list can be traversed
 * safely only after being हटाओd from list, so start with an entry
 * instead of list head.
 *
 * If being used on entries deleted from lock-less list directly, the
 * traverse order is from the newest to the oldest added entry.  If
 * you want to traverse from the oldest to the newest, you must
 * reverse the order by yourself beक्रमe traversing.
 */
#घोषणा llist_क्रम_each_entry(pos, node, member)				\
	क्रम ((pos) = llist_entry((node), typeof(*(pos)), member);	\
	     member_address_is_nonnull(pos, member);			\
	     (pos) = llist_entry((pos)->member.next, typeof(*(pos)), member))

/**
 * llist_क्रम_each_entry_safe - iterate over some deleted entries of lock-less list of given type
 *			       safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @node:	the first entry of deleted list entries.
 * @member:	the name of the llist_node with the काष्ठा.
 *
 * In general, some entries of the lock-less list can be traversed
 * safely only after being हटाओd from list, so start with an entry
 * instead of list head.
 *
 * If being used on entries deleted from lock-less list directly, the
 * traverse order is from the newest to the oldest added entry.  If
 * you want to traverse from the oldest to the newest, you must
 * reverse the order by yourself beक्रमe traversing.
 */
#घोषणा llist_क्रम_each_entry_safe(pos, n, node, member)			       \
	क्रम (pos = llist_entry((node), typeof(*pos), member);		       \
	     member_address_is_nonnull(pos, member) &&			       \
	        (n = llist_entry(pos->member.next, typeof(*n), member), true); \
	     pos = n)

/**
 * llist_empty - tests whether a lock-less list is empty
 * @head:	the list to test
 *
 * Not guaranteed to be accurate or up to date.  Just a quick way to
 * test whether the list is empty without deleting something from the
 * list.
 */
अटल अंतरभूत bool llist_empty(स्थिर काष्ठा llist_head *head)
अणु
	वापस READ_ONCE(head->first) == शून्य;
पूर्ण

अटल अंतरभूत काष्ठा llist_node *llist_next(काष्ठा llist_node *node)
अणु
	वापस node->next;
पूर्ण

बाह्य bool llist_add_batch(काष्ठा llist_node *new_first,
			    काष्ठा llist_node *new_last,
			    काष्ठा llist_head *head);

अटल अंतरभूत bool __llist_add_batch(काष्ठा llist_node *new_first,
				     काष्ठा llist_node *new_last,
				     काष्ठा llist_head *head)
अणु
	new_last->next = head->first;
	head->first = new_first;
	वापस new_last->next == शून्य;
पूर्ण

/**
 * llist_add - add a new entry
 * @new:	new entry to be added
 * @head:	the head क्रम your lock-less list
 *
 * Returns true अगर the list was empty prior to adding this entry.
 */
अटल अंतरभूत bool llist_add(काष्ठा llist_node *new, काष्ठा llist_head *head)
अणु
	वापस llist_add_batch(new, new, head);
पूर्ण

अटल अंतरभूत bool __llist_add(काष्ठा llist_node *new, काष्ठा llist_head *head)
अणु
	वापस __llist_add_batch(new, new, head);
पूर्ण

/**
 * llist_del_all - delete all entries from lock-less list
 * @head:	the head of lock-less list to delete all entries
 *
 * If list is empty, वापस शून्य, otherwise, delete all entries and
 * वापस the poपूर्णांकer to the first entry.  The order of entries
 * deleted is from the newest to the oldest added one.
 */
अटल अंतरभूत काष्ठा llist_node *llist_del_all(काष्ठा llist_head *head)
अणु
	वापस xchg(&head->first, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा llist_node *__llist_del_all(काष्ठा llist_head *head)
अणु
	काष्ठा llist_node *first = head->first;

	head->first = शून्य;
	वापस first;
पूर्ण

बाह्य काष्ठा llist_node *llist_del_first(काष्ठा llist_head *head);

काष्ठा llist_node *llist_reverse_order(काष्ठा llist_node *head);

#पूर्ण_अगर /* LLIST_H */
