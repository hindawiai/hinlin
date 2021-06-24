<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RCULIST_H
#घोषणा _LINUX_RCULIST_H

#अगर_घोषित __KERNEL__

/*
 * RCU-रक्षित list version
 */
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>

/*
 * Why is there no list_empty_rcu()?  Because list_empty() serves this
 * purpose.  The list_empty() function fetches the RCU-रक्षित poपूर्णांकer
 * and compares it to the address of the list head, but neither dereferences
 * this poपूर्णांकer itself nor provides this poपूर्णांकer to the caller.  Thereक्रमe,
 * it is not necessary to use rcu_dereference(), so that list_empty() can
 * be used anywhere you would want to use a list_empty_rcu().
 */

/*
 * INIT_LIST_HEAD_RCU - Initialize a list_head visible to RCU पढ़ोers
 * @list: list to be initialized
 *
 * You should instead use INIT_LIST_HEAD() क्रम normal initialization and
 * cleanup tasks, when पढ़ोers have no access to the list being initialized.
 * However, अगर the list being initialized is visible to पढ़ोers, you
 * need to keep the compiler from being too mischievous.
 */
अटल अंतरभूत व्योम INIT_LIST_HEAD_RCU(काष्ठा list_head *list)
अणु
	WRITE_ONCE(list->next, list);
	WRITE_ONCE(list->prev, list);
पूर्ण

/*
 * वापस the ->next poपूर्णांकer of a list_head in an rcu safe
 * way, we must not access it directly
 */
#घोषणा list_next_rcu(list)	(*((काष्ठा list_head __rcu **)(&(list)->next)))

/**
 * list_tail_rcu - वापसs the prev poपूर्णांकer of the head of the list
 * @head: the head of the list
 *
 * Note: This should only be used with the list header, and even then
 * only अगर list_del() and similar primitives are not also used on the
 * list header.
 */
#घोषणा list_tail_rcu(head)	(*((काष्ठा list_head __rcu **)(&(head)->prev)))

/*
 * Check during list traversal that we are within an RCU पढ़ोer
 */

#घोषणा check_arg_count_one(dummy)

#अगर_घोषित CONFIG_PROVE_RCU_LIST
#घोषणा __list_check_rcu(dummy, cond, extra...)				\
	(अणु								\
	check_arg_count_one(extra);					\
	RCU_LOCKDEP_WARN(!(cond) && !rcu_पढ़ो_lock_any_held(),		\
			 "RCU-list traversed in non-reader section!");	\
	पूर्ण)

#घोषणा __list_check_srcu(cond)					 \
	(अणु								 \
	RCU_LOCKDEP_WARN(!(cond),					 \
		"RCU-list traversed without holding the required lock!");\
	पूर्ण)
#अन्यथा
#घोषणा __list_check_rcu(dummy, cond, extra...)				\
	(अणु check_arg_count_one(extra); पूर्ण)

#घोषणा __list_check_srcu(cond) (अणु पूर्ण)
#पूर्ण_अगर

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only क्रम पूर्णांकernal list manipulation where we know
 * the prev/next entries alपढ़ोy!
 */
अटल अंतरभूत व्योम __list_add_rcu(काष्ठा list_head *new,
		काष्ठा list_head *prev, काष्ठा list_head *next)
अणु
	अगर (!__list_add_valid(new, prev, next))
		वापस;

	new->next = next;
	new->prev = prev;
	rcu_assign_poपूर्णांकer(list_next_rcu(prev), new);
	next->prev = new;
पूर्ण

/**
 * list_add_rcu - add a new entry to rcu-रक्षित list
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specअगरied head.
 * This is good क्रम implementing stacks.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as list_add_rcu()
 * or list_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * list_क्रम_each_entry_rcu().
 */
अटल अंतरभूत व्योम list_add_rcu(काष्ठा list_head *new, काष्ठा list_head *head)
अणु
	__list_add_rcu(new, head, head->next);
पूर्ण

/**
 * list_add_tail_rcu - add a new entry to rcu-रक्षित list
 * @new: new entry to be added
 * @head: list head to add it beक्रमe
 *
 * Insert a new entry beक्रमe the specअगरied head.
 * This is useful क्रम implementing queues.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as list_add_tail_rcu()
 * or list_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * list_क्रम_each_entry_rcu().
 */
अटल अंतरभूत व्योम list_add_tail_rcu(काष्ठा list_head *new,
					काष्ठा list_head *head)
अणु
	__list_add_rcu(new, head->prev, head);
पूर्ण

/**
 * list_del_rcu - deletes entry from list without re-initialization
 * @entry: the element to delete from the list.
 *
 * Note: list_empty() on entry करोes not वापस true after this,
 * the entry is in an undefined state. It is useful क्रम RCU based
 * lockमुक्त traversal.
 *
 * In particular, it means that we can not poison the क्रमward
 * poपूर्णांकers that may still be used क्रम walking the list.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as list_del_rcu()
 * or list_add_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * list_क्रम_each_entry_rcu().
 *
 * Note that the caller is not permitted to immediately मुक्त
 * the newly deleted entry.  Instead, either synchronize_rcu()
 * or call_rcu() must be used to defer मुक्तing until an RCU
 * grace period has elapsed.
 */
अटल अंतरभूत व्योम list_del_rcu(काष्ठा list_head *entry)
अणु
	__list_del_entry(entry);
	entry->prev = LIST_POISON2;
पूर्ण

/**
 * hlist_del_init_rcu - deletes entry from hash list with re-initialization
 * @n: the element to delete from the hash list.
 *
 * Note: list_unhashed() on the node वापस true after this. It is
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
 * list-mutation primitive, such as hlist_add_head_rcu() or
 * hlist_del_rcu(), running on this same list.  However, it is
 * perfectly legal to run concurrently with the _rcu list-traversal
 * primitives, such as hlist_क्रम_each_entry_rcu().
 */
अटल अंतरभूत व्योम hlist_del_init_rcu(काष्ठा hlist_node *n)
अणु
	अगर (!hlist_unhashed(n)) अणु
		__hlist_del(n);
		WRITE_ONCE(n->pprev, शून्य);
	पूर्ण
पूर्ण

/**
 * list_replace_rcu - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * The @old entry will be replaced with the @new entry atomically.
 * Note: @old should not be empty.
 */
अटल अंतरभूत व्योम list_replace_rcu(काष्ठा list_head *old,
				काष्ठा list_head *new)
अणु
	new->next = old->next;
	new->prev = old->prev;
	rcu_assign_poपूर्णांकer(list_next_rcu(new->prev), new);
	new->next->prev = new;
	old->prev = LIST_POISON2;
पूर्ण

/**
 * __list_splice_init_rcu - join an RCU-रक्षित list पूर्णांकo an existing list.
 * @list:	the RCU-रक्षित list to splice
 * @prev:	poपूर्णांकs to the last element of the existing list
 * @next:	poपूर्णांकs to the first element of the existing list
 * @sync:	synchronize_rcu, synchronize_rcu_expedited, ...
 *
 * The list poपूर्णांकed to by @prev and @next can be RCU-पढ़ो traversed
 * concurrently with this function.
 *
 * Note that this function blocks.
 *
 * Important note: the caller must take whatever action is necessary to prevent
 * any other updates to the existing list.  In principle, it is possible to
 * modअगरy the list as soon as sync() begins execution. If this sort of thing
 * becomes necessary, an alternative version based on call_rcu() could be
 * created.  But only अगर -really- needed -- there is no लघुage of RCU API
 * members.
 */
अटल अंतरभूत व्योम __list_splice_init_rcu(काष्ठा list_head *list,
					  काष्ठा list_head *prev,
					  काष्ठा list_head *next,
					  व्योम (*sync)(व्योम))
अणु
	काष्ठा list_head *first = list->next;
	काष्ठा list_head *last = list->prev;

	/*
	 * "first" and "last" tracking list, so initialize it.  RCU पढ़ोers
	 * have access to this list, so we must use INIT_LIST_HEAD_RCU()
	 * instead of INIT_LIST_HEAD().
	 */

	INIT_LIST_HEAD_RCU(list);

	/*
	 * At this poपूर्णांक, the list body still poपूर्णांकs to the source list.
	 * Wait क्रम any पढ़ोers to finish using the list beक्रमe splicing
	 * the list body पूर्णांकo the new list.  Any new पढ़ोers will see
	 * an empty list.
	 */

	sync();
	ASSERT_EXCLUSIVE_ACCESS(*first);
	ASSERT_EXCLUSIVE_ACCESS(*last);

	/*
	 * Readers are finished with the source list, so perक्रमm splice.
	 * The order is important अगर the new list is global and accessible
	 * to concurrent RCU पढ़ोers.  Note that RCU पढ़ोers are not
	 * permitted to traverse the prev poपूर्णांकers without excluding
	 * this function.
	 */

	last->next = next;
	rcu_assign_poपूर्णांकer(list_next_rcu(prev), first);
	first->prev = prev;
	next->prev = last;
पूर्ण

/**
 * list_splice_init_rcu - splice an RCU-रक्षित list पूर्णांकo an existing list,
 *                        deचिन्हित क्रम stacks.
 * @list:	the RCU-रक्षित list to splice
 * @head:	the place in the existing list to splice the first list पूर्णांकo
 * @sync:	synchronize_rcu, synchronize_rcu_expedited, ...
 */
अटल अंतरभूत व्योम list_splice_init_rcu(काष्ठा list_head *list,
					काष्ठा list_head *head,
					व्योम (*sync)(व्योम))
अणु
	अगर (!list_empty(list))
		__list_splice_init_rcu(list, head, head->next, sync);
पूर्ण

/**
 * list_splice_tail_init_rcu - splice an RCU-रक्षित list पूर्णांकo an existing
 *                             list, deचिन्हित क्रम queues.
 * @list:	the RCU-रक्षित list to splice
 * @head:	the place in the existing list to splice the first list पूर्णांकo
 * @sync:	synchronize_rcu, synchronize_rcu_expedited, ...
 */
अटल अंतरभूत व्योम list_splice_tail_init_rcu(काष्ठा list_head *list,
					     काष्ठा list_head *head,
					     व्योम (*sync)(व्योम))
अणु
	अगर (!list_empty(list))
		__list_splice_init_rcu(list, head->prev, head, sync);
पूर्ण

/**
 * list_entry_rcu - get the काष्ठा क्रम this entry
 * @ptr:        the &काष्ठा list_head poपूर्णांकer.
 * @type:       the type of the काष्ठा this is embedded in.
 * @member:     the name of the list_head within the काष्ठा.
 *
 * This primitive may safely run concurrently with the _rcu list-mutation
 * primitives such as list_add_rcu() as दीर्घ as it's guarded by rcu_पढ़ो_lock().
 */
#घोषणा list_entry_rcu(ptr, type, member) \
	container_of(READ_ONCE(ptr), type, member)

/*
 * Where are list_empty_rcu() and list_first_entry_rcu()?
 *
 * Implementing those functions following their counterparts list_empty() and
 * list_first_entry() is not advisable because they lead to subtle race
 * conditions as the following snippet shows:
 *
 * अगर (!list_empty_rcu(mylist)) अणु
 *	काष्ठा foo *bar = list_first_entry_rcu(mylist, काष्ठा foo, list_member);
 *	करो_something(bar);
 * पूर्ण
 *
 * The list may not be empty when list_empty_rcu checks it, but it may be when
 * list_first_entry_rcu reपढ़ोs the ->next poपूर्णांकer.
 *
 * Reपढ़ोing the ->next poपूर्णांकer is not a problem क्रम list_empty() and
 * list_first_entry() because they would be रक्षित by a lock that blocks
 * ग_लिखोrs.
 *
 * See list_first_or_null_rcu क्रम an alternative.
 */

/**
 * list_first_or_null_rcu - get the first element from a list
 * @ptr:        the list head to take the element from.
 * @type:       the type of the काष्ठा this is embedded in.
 * @member:     the name of the list_head within the काष्ठा.
 *
 * Note that अगर the list is empty, it वापसs शून्य.
 *
 * This primitive may safely run concurrently with the _rcu list-mutation
 * primitives such as list_add_rcu() as दीर्घ as it's guarded by rcu_पढ़ो_lock().
 */
#घोषणा list_first_or_null_rcu(ptr, type, member) \
(अणु \
	काष्ठा list_head *__ptr = (ptr); \
	काष्ठा list_head *__next = READ_ONCE(__ptr->next); \
	likely(__ptr != __next) ? list_entry_rcu(__next, type, member) : शून्य; \
पूर्ण)

/**
 * list_next_or_null_rcu - get the first element from a list
 * @head:	the head क्रम the list.
 * @ptr:        the list head to take the next element from.
 * @type:       the type of the काष्ठा this is embedded in.
 * @member:     the name of the list_head within the काष्ठा.
 *
 * Note that अगर the ptr is at the end of the list, शून्य is वापसed.
 *
 * This primitive may safely run concurrently with the _rcu list-mutation
 * primitives such as list_add_rcu() as दीर्घ as it's guarded by rcu_पढ़ो_lock().
 */
#घोषणा list_next_or_null_rcu(head, ptr, type, member) \
(अणु \
	काष्ठा list_head *__head = (head); \
	काष्ठा list_head *__ptr = (ptr); \
	काष्ठा list_head *__next = READ_ONCE(__ptr->next); \
	likely(__next != __head) ? list_entry_rcu(__next, type, \
						  member) : शून्य; \
पूर्ण)

/**
 * list_क्रम_each_entry_rcu	-	iterate over rcu list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 * @cond:	optional lockdep expression अगर called from non-RCU protection.
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as list_add_rcu()
 * as दीर्घ as the traversal is guarded by rcu_पढ़ो_lock().
 */
#घोषणा list_क्रम_each_entry_rcu(pos, head, member, cond...)		\
	क्रम (__list_check_rcu(dummy, ## cond, 0),			\
	     pos = list_entry_rcu((head)->next, typeof(*pos), member);	\
		&pos->member != (head);					\
		pos = list_entry_rcu(pos->member.next, typeof(*pos), member))

/**
 * list_क्रम_each_entry_srcu	-	iterate over rcu list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 * @cond:	lockdep expression क्रम the lock required to traverse the list.
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as list_add_rcu()
 * as दीर्घ as the traversal is guarded by srcu_पढ़ो_lock().
 * The lockdep expression srcu_पढ़ो_lock_held() can be passed as the
 * cond argument from पढ़ो side.
 */
#घोषणा list_क्रम_each_entry_srcu(pos, head, member, cond)		\
	क्रम (__list_check_srcu(cond),					\
	     pos = list_entry_rcu((head)->next, typeof(*pos), member);	\
		&pos->member != (head);					\
		pos = list_entry_rcu(pos->member.next, typeof(*pos), member))

/**
 * list_entry_lockless - get the काष्ठा क्रम this entry
 * @ptr:        the &काष्ठा list_head poपूर्णांकer.
 * @type:       the type of the काष्ठा this is embedded in.
 * @member:     the name of the list_head within the काष्ठा.
 *
 * This primitive may safely run concurrently with the _rcu
 * list-mutation primitives such as list_add_rcu(), but requires some
 * implicit RCU पढ़ो-side guarding.  One example is running within a special
 * exception-समय environment where preemption is disabled and where lockdep
 * cannot be invoked.  Another example is when items are added to the list,
 * but never deleted.
 */
#घोषणा list_entry_lockless(ptr, type, member) \
	container_of((typeof(ptr))READ_ONCE(ptr), type, member)

/**
 * list_क्रम_each_entry_lockless - iterate over rcu list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_काष्ठा within the काष्ठा.
 *
 * This primitive may safely run concurrently with the _rcu
 * list-mutation primitives such as list_add_rcu(), but requires some
 * implicit RCU पढ़ो-side guarding.  One example is running within a special
 * exception-समय environment where preemption is disabled and where lockdep
 * cannot be invoked.  Another example is when items are added to the list,
 * but never deleted.
 */
#घोषणा list_क्रम_each_entry_lockless(pos, head, member) \
	क्रम (pos = list_entry_lockless((head)->next, typeof(*pos), member); \
	     &pos->member != (head); \
	     pos = list_entry_lockless(pos->member.next, typeof(*pos), member))

/**
 * list_क्रम_each_entry_जारी_rcu - जारी iteration over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Continue to iterate over list of given type, continuing after
 * the current position which must have been in the list when the RCU पढ़ो
 * lock was taken.
 * This would typically require either that you obtained the node from a
 * previous walk of the list in the same RCU पढ़ो-side critical section, or
 * that you held some sort of non-RCU reference (such as a reference count)
 * to keep the node alive *and* in the list.
 *
 * This iterator is similar to list_क्रम_each_entry_from_rcu() except
 * this starts after the given position and that one starts at the given
 * position.
 */
#घोषणा list_क्रम_each_entry_जारी_rcu(pos, head, member) 		\
	क्रम (pos = list_entry_rcu(pos->member.next, typeof(*pos), member); \
	     &pos->member != (head);	\
	     pos = list_entry_rcu(pos->member.next, typeof(*pos), member))

/**
 * list_क्रम_each_entry_from_rcu - iterate over a list from current poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_node within the काष्ठा.
 *
 * Iterate over the tail of a list starting from a given position,
 * which must have been in the list when the RCU पढ़ो lock was taken.
 * This would typically require either that you obtained the node from a
 * previous walk of the list in the same RCU पढ़ो-side critical section, or
 * that you held some sort of non-RCU reference (such as a reference count)
 * to keep the node alive *and* in the list.
 *
 * This iterator is similar to list_क्रम_each_entry_जारी_rcu() except
 * this starts from the given position and that one starts from the position
 * after the given position.
 */
#घोषणा list_क्रम_each_entry_from_rcu(pos, head, member)			\
	क्रम (; &(pos)->member != (head);					\
		pos = list_entry_rcu(pos->member.next, typeof(*(pos)), member))

/**
 * hlist_del_rcu - deletes entry from hash list without re-initialization
 * @n: the element to delete from the hash list.
 *
 * Note: list_unhashed() on entry करोes not वापस true after this,
 * the entry is in an undefined state. It is useful क्रम RCU based
 * lockमुक्त traversal.
 *
 * In particular, it means that we can not poison the क्रमward
 * poपूर्णांकers that may still be used क्रम walking the hash list.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_add_head_rcu()
 * or hlist_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_क्रम_each_entry().
 */
अटल अंतरभूत व्योम hlist_del_rcu(काष्ठा hlist_node *n)
अणु
	__hlist_del(n);
	WRITE_ONCE(n->pprev, LIST_POISON2);
पूर्ण

/**
 * hlist_replace_rcu - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * The @old entry will be replaced with the @new entry atomically.
 */
अटल अंतरभूत व्योम hlist_replace_rcu(काष्ठा hlist_node *old,
					काष्ठा hlist_node *new)
अणु
	काष्ठा hlist_node *next = old->next;

	new->next = next;
	WRITE_ONCE(new->pprev, old->pprev);
	rcu_assign_poपूर्णांकer(*(काष्ठा hlist_node __rcu **)new->pprev, new);
	अगर (next)
		WRITE_ONCE(new->next->pprev, &new->next);
	WRITE_ONCE(old->pprev, LIST_POISON2);
पूर्ण

/**
 * hlists_swap_heads_rcu - swap the lists the hlist heads poपूर्णांक to
 * @left:  The hlist head on the left
 * @right: The hlist head on the right
 *
 * The lists start out as [@left  ][node1 ... ] and
 *                        [@right ][node2 ... ]
 * The lists end up as    [@left  ][node2 ... ]
 *                        [@right ][node1 ... ]
 */
अटल अंतरभूत व्योम hlists_swap_heads_rcu(काष्ठा hlist_head *left, काष्ठा hlist_head *right)
अणु
	काष्ठा hlist_node *node1 = left->first;
	काष्ठा hlist_node *node2 = right->first;

	rcu_assign_poपूर्णांकer(left->first, node2);
	rcu_assign_poपूर्णांकer(right->first, node1);
	WRITE_ONCE(node2->pprev, &left->first);
	WRITE_ONCE(node1->pprev, &right->first);
पूर्ण

/*
 * वापस the first or the next element in an RCU रक्षित hlist
 */
#घोषणा hlist_first_rcu(head)	(*((काष्ठा hlist_node __rcu **)(&(head)->first)))
#घोषणा hlist_next_rcu(node)	(*((काष्ठा hlist_node __rcu **)(&(node)->next)))
#घोषणा hlist_pprev_rcu(node)	(*((काष्ठा hlist_node __rcu **)((node)->pprev)))

/**
 * hlist_add_head_rcu
 * @n: the element to add to the hash list.
 * @h: the list to add to.
 *
 * Description:
 * Adds the specअगरied element to the specअगरied hlist,
 * जबतक permitting racing traversals.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_add_head_rcu()
 * or hlist_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_क्रम_each_entry_rcu(), used to prevent memory-consistency
 * problems on Alpha CPUs.  Regardless of the type of CPU, the
 * list-traversal primitive must be guarded by rcu_पढ़ो_lock().
 */
अटल अंतरभूत व्योम hlist_add_head_rcu(काष्ठा hlist_node *n,
					काष्ठा hlist_head *h)
अणु
	काष्ठा hlist_node *first = h->first;

	n->next = first;
	WRITE_ONCE(n->pprev, &h->first);
	rcu_assign_poपूर्णांकer(hlist_first_rcu(h), n);
	अगर (first)
		WRITE_ONCE(first->pprev, &n->next);
पूर्ण

/**
 * hlist_add_tail_rcu
 * @n: the element to add to the hash list.
 * @h: the list to add to.
 *
 * Description:
 * Adds the specअगरied element to the specअगरied hlist,
 * जबतक permitting racing traversals.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_add_head_rcu()
 * or hlist_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_क्रम_each_entry_rcu(), used to prevent memory-consistency
 * problems on Alpha CPUs.  Regardless of the type of CPU, the
 * list-traversal primitive must be guarded by rcu_पढ़ो_lock().
 */
अटल अंतरभूत व्योम hlist_add_tail_rcu(काष्ठा hlist_node *n,
				      काष्ठा hlist_head *h)
अणु
	काष्ठा hlist_node *i, *last = शून्य;

	/* Note: ग_लिखो side code, so rcu accessors are not needed. */
	क्रम (i = h->first; i; i = i->next)
		last = i;

	अगर (last) अणु
		n->next = last->next;
		WRITE_ONCE(n->pprev, &last->next);
		rcu_assign_poपूर्णांकer(hlist_next_rcu(last), n);
	पूर्ण अन्यथा अणु
		hlist_add_head_rcu(n, h);
	पूर्ण
पूर्ण

/**
 * hlist_add_beक्रमe_rcu
 * @n: the new element to add to the hash list.
 * @next: the existing element to add the new element beक्रमe.
 *
 * Description:
 * Adds the specअगरied element to the specअगरied hlist
 * beक्रमe the specअगरied node जबतक permitting racing traversals.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_add_head_rcu()
 * or hlist_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_क्रम_each_entry_rcu(), used to prevent memory-consistency
 * problems on Alpha CPUs.
 */
अटल अंतरभूत व्योम hlist_add_beक्रमe_rcu(काष्ठा hlist_node *n,
					काष्ठा hlist_node *next)
अणु
	WRITE_ONCE(n->pprev, next->pprev);
	n->next = next;
	rcu_assign_poपूर्णांकer(hlist_pprev_rcu(n), n);
	WRITE_ONCE(next->pprev, &n->next);
पूर्ण

/**
 * hlist_add_behind_rcu
 * @n: the new element to add to the hash list.
 * @prev: the existing element to add the new element after.
 *
 * Description:
 * Adds the specअगरied element to the specअगरied hlist
 * after the specअगरied node जबतक permitting racing traversals.
 *
 * The caller must take whatever precautions are necessary
 * (such as holding appropriate locks) to aव्योम racing
 * with another list-mutation primitive, such as hlist_add_head_rcu()
 * or hlist_del_rcu(), running on this same list.
 * However, it is perfectly legal to run concurrently with
 * the _rcu list-traversal primitives, such as
 * hlist_क्रम_each_entry_rcu(), used to prevent memory-consistency
 * problems on Alpha CPUs.
 */
अटल अंतरभूत व्योम hlist_add_behind_rcu(काष्ठा hlist_node *n,
					काष्ठा hlist_node *prev)
अणु
	n->next = prev->next;
	WRITE_ONCE(n->pprev, &prev->next);
	rcu_assign_poपूर्णांकer(hlist_next_rcu(prev), n);
	अगर (n->next)
		WRITE_ONCE(n->next->pprev, &n->next);
पूर्ण

#घोषणा __hlist_क्रम_each_rcu(pos, head)				\
	क्रम (pos = rcu_dereference(hlist_first_rcu(head));	\
	     pos;						\
	     pos = rcu_dereference(hlist_next_rcu(pos)))

/**
 * hlist_क्रम_each_entry_rcu - iterate over rcu list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 * @cond:	optional lockdep expression अगर called from non-RCU protection.
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as hlist_add_head_rcu()
 * as दीर्घ as the traversal is guarded by rcu_पढ़ो_lock().
 */
#घोषणा hlist_क्रम_each_entry_rcu(pos, head, member, cond...)		\
	क्रम (__list_check_rcu(dummy, ## cond, 0),			\
	     pos = hlist_entry_safe(rcu_dereference_raw(hlist_first_rcu(head)),\
			typeof(*(pos)), member);			\
		pos;							\
		pos = hlist_entry_safe(rcu_dereference_raw(hlist_next_rcu(\
			&(pos)->member)), typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_srcu - iterate over rcu list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 * @cond:	lockdep expression क्रम the lock required to traverse the list.
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as hlist_add_head_rcu()
 * as दीर्घ as the traversal is guarded by srcu_पढ़ो_lock().
 * The lockdep expression srcu_पढ़ो_lock_held() can be passed as the
 * cond argument from पढ़ो side.
 */
#घोषणा hlist_क्रम_each_entry_srcu(pos, head, member, cond)		\
	क्रम (__list_check_srcu(cond),					\
	     pos = hlist_entry_safe(rcu_dereference_raw(hlist_first_rcu(head)),\
			typeof(*(pos)), member);			\
		pos;							\
		pos = hlist_entry_safe(rcu_dereference_raw(hlist_next_rcu(\
			&(pos)->member)), typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_rcu_notrace - iterate over rcu list of given type (क्रम tracing)
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as hlist_add_head_rcu()
 * as दीर्घ as the traversal is guarded by rcu_पढ़ो_lock().
 *
 * This is the same as hlist_क्रम_each_entry_rcu() except that it करोes
 * not करो any RCU debugging or tracing.
 */
#घोषणा hlist_क्रम_each_entry_rcu_notrace(pos, head, member)			\
	क्रम (pos = hlist_entry_safe(rcu_dereference_raw_check(hlist_first_rcu(head)),\
			typeof(*(pos)), member);			\
		pos;							\
		pos = hlist_entry_safe(rcu_dereference_raw_check(hlist_next_rcu(\
			&(pos)->member)), typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_rcu_bh - iterate over rcu list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 *
 * This list-traversal primitive may safely run concurrently with
 * the _rcu list-mutation primitives such as hlist_add_head_rcu()
 * as दीर्घ as the traversal is guarded by rcu_पढ़ो_lock().
 */
#घोषणा hlist_क्रम_each_entry_rcu_bh(pos, head, member)			\
	क्रम (pos = hlist_entry_safe(rcu_dereference_bh(hlist_first_rcu(head)),\
			typeof(*(pos)), member);			\
		pos;							\
		pos = hlist_entry_safe(rcu_dereference_bh(hlist_next_rcu(\
			&(pos)->member)), typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_जारी_rcu - iterate over a hlist continuing after current poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @member:	the name of the hlist_node within the काष्ठा.
 */
#घोषणा hlist_क्रम_each_entry_जारी_rcu(pos, member)			\
	क्रम (pos = hlist_entry_safe(rcu_dereference_raw(hlist_next_rcu( \
			&(pos)->member)), typeof(*(pos)), member);	\
	     pos;							\
	     pos = hlist_entry_safe(rcu_dereference_raw(hlist_next_rcu(	\
			&(pos)->member)), typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_जारी_rcu_bh - iterate over a hlist continuing after current poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @member:	the name of the hlist_node within the काष्ठा.
 */
#घोषणा hlist_क्रम_each_entry_जारी_rcu_bh(pos, member)		\
	क्रम (pos = hlist_entry_safe(rcu_dereference_bh(hlist_next_rcu(  \
			&(pos)->member)), typeof(*(pos)), member);	\
	     pos;							\
	     pos = hlist_entry_safe(rcu_dereference_bh(hlist_next_rcu(	\
			&(pos)->member)), typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_from_rcu - iterate over a hlist continuing from current poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @member:	the name of the hlist_node within the काष्ठा.
 */
#घोषणा hlist_क्रम_each_entry_from_rcu(pos, member)			\
	क्रम (; pos;							\
	     pos = hlist_entry_safe(rcu_dereference_raw(hlist_next_rcu(	\
			&(pos)->member)), typeof(*(pos)), member))

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर
