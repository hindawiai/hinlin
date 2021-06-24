<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LIST_H
#घोषणा _LINUX_LIST_H

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/poison.h>
#समावेश <linux/स्थिर.h>
#समावेश <linux/kernel.h>

/*
 * Circular करोubly linked list implementation.
 *
 * Some of the पूर्णांकernal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * someबार we alपढ़ोy know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

#घोषणा LIST_HEAD_INIT(name) अणु &(name), &(name) पूर्ण

#घोषणा LIST_HEAD(name) \
	काष्ठा list_head name = LIST_HEAD_INIT(name)

/**
 * INIT_LIST_HEAD - Initialize a list_head काष्ठाure
 * @list: list_head काष्ठाure to be initialized.
 *
 * Initializes the list_head to poपूर्णांक to itself.  If it is a list header,
 * the result is an empty list.
 */
अटल अंतरभूत व्योम INIT_LIST_HEAD(काष्ठा list_head *list)
अणु
	WRITE_ONCE(list->next, list);
	list->prev = list;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LIST
बाह्य bool __list_add_valid(काष्ठा list_head *new,
			      काष्ठा list_head *prev,
			      काष्ठा list_head *next);
बाह्य bool __list_del_entry_valid(काष्ठा list_head *entry);
#अन्यथा
अटल अंतरभूत bool __list_add_valid(काष्ठा list_head *new,
				काष्ठा list_head *prev,
				काष्ठा list_head *next)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool __list_del_entry_valid(काष्ठा list_head *entry)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only क्रम पूर्णांकernal list manipulation where we know
 * the prev/next entries alपढ़ोy!
 */
अटल अंतरभूत व्योम __list_add(काष्ठा list_head *new,
			      काष्ठा list_head *prev,
			      काष्ठा list_head *next)
अणु
	अगर (!__list_add_valid(new, prev, next))
		वापस;

	next->prev = new;
	new->next = next;
	new->prev = prev;
	WRITE_ONCE(prev->next, new);
पूर्ण

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specअगरied head.
 * This is good क्रम implementing stacks.
 */
अटल अंतरभूत व्योम list_add(काष्ठा list_head *new, काष्ठा list_head *head)
अणु
	__list_add(new, head, head->next);
पूर्ण


/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it beक्रमe
 *
 * Insert a new entry beक्रमe the specअगरied head.
 * This is useful क्रम implementing queues.
 */
अटल अंतरभूत व्योम list_add_tail(काष्ठा list_head *new, काष्ठा list_head *head)
अणु
	__list_add(new, head->prev, head);
पूर्ण

/*
 * Delete a list entry by making the prev/next entries
 * poपूर्णांक to each other.
 *
 * This is only क्रम पूर्णांकernal list manipulation where we know
 * the prev/next entries alपढ़ोy!
 */
अटल अंतरभूत व्योम __list_del(काष्ठा list_head * prev, काष्ठा list_head * next)
अणु
	next->prev = prev;
	WRITE_ONCE(prev->next, next);
पूर्ण

/*
 * Delete a list entry and clear the 'prev' poपूर्णांकer.
 *
 * This is a special-purpose list clearing method used in the networking code
 * क्रम lists allocated as per-cpu, where we करोn't want to incur the extra
 * WRITE_ONCE() overhead of a regular list_del_init(). The code that uses this
 * needs to check the node 'prev' poपूर्णांकer instead of calling list_empty().
 */
अटल अंतरभूत व्योम __list_del_clearprev(काष्ठा list_head *entry)
अणु
	__list_del(entry->prev, entry->next);
	entry->prev = शून्य;
पूर्ण

अटल अंतरभूत व्योम __list_del_entry(काष्ठा list_head *entry)
अणु
	अगर (!__list_del_entry_valid(entry))
		वापस;

	__list_del(entry->prev, entry->next);
पूर्ण

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry करोes not वापस true after this, the entry is
 * in an undefined state.
 */
अटल अंतरभूत व्योम list_del(काष्ठा list_head *entry)
अणु
	__list_del_entry(entry);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
पूर्ण

/**
 * list_replace - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
अटल अंतरभूत व्योम list_replace(काष्ठा list_head *old,
				काष्ठा list_head *new)
अणु
	new->next = old->next;
	new->next->prev = new;
	new->prev = old->prev;
	new->prev->next = new;
पूर्ण

/**
 * list_replace_init - replace old entry by new one and initialize the old one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
अटल अंतरभूत व्योम list_replace_init(काष्ठा list_head *old,
				     काष्ठा list_head *new)
अणु
	list_replace(old, new);
	INIT_LIST_HEAD(old);
पूर्ण

/**
 * list_swap - replace entry1 with entry2 and re-add entry1 at entry2's position
 * @entry1: the location to place entry2
 * @entry2: the location to place entry1
 */
अटल अंतरभूत व्योम list_swap(काष्ठा list_head *entry1,
			     काष्ठा list_head *entry2)
अणु
	काष्ठा list_head *pos = entry2->prev;

	list_del(entry2);
	list_replace(entry1, entry2);
	अगर (pos == entry1)
		pos = entry2;
	list_add(entry1, pos);
पूर्ण

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
अटल अंतरभूत व्योम list_del_init(काष्ठा list_head *entry)
अणु
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
पूर्ण

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
अटल अंतरभूत व्योम list_move(काष्ठा list_head *list, काष्ठा list_head *head)
अणु
	__list_del_entry(list);
	list_add(list, head);
पूर्ण

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
अटल अंतरभूत व्योम list_move_tail(काष्ठा list_head *list,
				  काष्ठा list_head *head)
अणु
	__list_del_entry(list);
	list_add_tail(list, head);
पूर्ण

/**
 * list_bulk_move_tail - move a subsection of a list to its tail
 * @head: the head that will follow our entry
 * @first: first entry to move
 * @last: last entry to move, can be the same as first
 *
 * Move all entries between @first and including @last beक्रमe @head.
 * All three entries must beदीर्घ to the same linked list.
 */
अटल अंतरभूत व्योम list_bulk_move_tail(काष्ठा list_head *head,
				       काष्ठा list_head *first,
				       काष्ठा list_head *last)
अणु
	first->prev->next = last->next;
	last->next->prev = first->prev;

	head->prev->next = first;
	first->prev = head->prev;

	last->next = head;
	head->prev = last;
पूर्ण

/**
 * list_is_first -- tests whether @list is the first entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
अटल अंतरभूत पूर्णांक list_is_first(स्थिर काष्ठा list_head *list,
					स्थिर काष्ठा list_head *head)
अणु
	वापस list->prev == head;
पूर्ण

/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
अटल अंतरभूत पूर्णांक list_is_last(स्थिर काष्ठा list_head *list,
				स्थिर काष्ठा list_head *head)
अणु
	वापस list->next == head;
पूर्ण

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
अटल अंतरभूत पूर्णांक list_empty(स्थिर काष्ठा list_head *head)
अणु
	वापस READ_ONCE(head->next) == head;
पूर्ण

/**
 * list_del_init_careful - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 *
 * This is the same as list_del_init(), except deचिन्हित to be used
 * together with list_empty_careful() in a way to guarantee ordering
 * of other memory operations.
 *
 * Any memory operations करोne beक्रमe a list_del_init_careful() are
 * guaranteed to be visible after a list_empty_careful() test.
 */
अटल अंतरभूत व्योम list_del_init_careful(काष्ठा list_head *entry)
अणु
	__list_del_entry(entry);
	entry->prev = entry;
	smp_store_release(&entry->next, entry);
पूर्ण

/**
 * list_empty_careful - tests whether a list is empty and not being modअगरied
 * @head: the list to test
 *
 * Description:
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modअगरying either member (next or prev)
 *
 * NOTE: using list_empty_careful() without synchronization
 * can only be safe अगर the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * अगर another CPU could re-list_add() it.
 */
अटल अंतरभूत पूर्णांक list_empty_careful(स्थिर काष्ठा list_head *head)
अणु
	काष्ठा list_head *next = smp_load_acquire(&head->next);
	वापस (next == head) && (next == head->prev);
पूर्ण

/**
 * list_rotate_left - rotate the list to the left
 * @head: the head of the list
 */
अटल अंतरभूत व्योम list_rotate_left(काष्ठा list_head *head)
अणु
	काष्ठा list_head *first;

	अगर (!list_empty(head)) अणु
		first = head->next;
		list_move_tail(first, head);
	पूर्ण
पूर्ण

/**
 * list_rotate_to_front() - Rotate list to specअगरic item.
 * @list: The desired new front of the list.
 * @head: The head of the list.
 *
 * Rotates list so that @list becomes the new front of the list.
 */
अटल अंतरभूत व्योम list_rotate_to_front(काष्ठा list_head *list,
					काष्ठा list_head *head)
अणु
	/*
	 * Deletes the list head from the list denoted by @head and
	 * places it as the tail of @list, this effectively rotates the
	 * list so that @list is at the front.
	 */
	list_move_tail(head, list);
पूर्ण

/**
 * list_is_singular - tests whether a list has just one entry.
 * @head: the list to test.
 */
अटल अंतरभूत पूर्णांक list_is_singular(स्थिर काष्ठा list_head *head)
अणु
	वापस !list_empty(head) && (head->next == head->prev);
पूर्ण

अटल अंतरभूत व्योम __list_cut_position(काष्ठा list_head *list,
		काष्ठा list_head *head, काष्ठा list_head *entry)
अणु
	काष्ठा list_head *new_first = entry->next;
	list->next = head->next;
	list->next->prev = list;
	list->prev = entry;
	entry->next = list;
	head->next = new_first;
	new_first->prev = head;
पूर्ण

/**
 * list_cut_position - cut a list पूर्णांकo two
 * @list: a new list to add all हटाओd entries
 * @head: a list with entries
 * @entry: an entry within head, could be the head itself
 *	and अगर so we won't cut the list
 *
 * This helper moves the initial part of @head, up to and
 * including @entry, from @head to @list. You should
 * pass on @entry an element you know is on @head. @list
 * should be an empty list or a list you करो not care about
 * losing its data.
 *
 */
अटल अंतरभूत व्योम list_cut_position(काष्ठा list_head *list,
		काष्ठा list_head *head, काष्ठा list_head *entry)
अणु
	अगर (list_empty(head))
		वापस;
	अगर (list_is_singular(head) &&
		(head->next != entry && head != entry))
		वापस;
	अगर (entry == head)
		INIT_LIST_HEAD(list);
	अन्यथा
		__list_cut_position(list, head, entry);
पूर्ण

/**
 * list_cut_beक्रमe - cut a list पूर्णांकo two, beक्रमe given entry
 * @list: a new list to add all हटाओd entries
 * @head: a list with entries
 * @entry: an entry within head, could be the head itself
 *
 * This helper moves the initial part of @head, up to but
 * excluding @entry, from @head to @list.  You should pass
 * in @entry an element you know is on @head.  @list should
 * be an empty list or a list you करो not care about losing
 * its data.
 * If @entry == @head, all entries on @head are moved to
 * @list.
 */
अटल अंतरभूत व्योम list_cut_beक्रमe(काष्ठा list_head *list,
				   काष्ठा list_head *head,
				   काष्ठा list_head *entry)
अणु
	अगर (head->next == entry) अणु
		INIT_LIST_HEAD(list);
		वापस;
	पूर्ण
	list->next = head->next;
	list->next->prev = list;
	list->prev = entry->prev;
	list->prev->next = list;
	head->next = entry;
	entry->prev = head;
पूर्ण

अटल अंतरभूत व्योम __list_splice(स्थिर काष्ठा list_head *list,
				 काष्ठा list_head *prev,
				 काष्ठा list_head *next)
अणु
	काष्ठा list_head *first = list->next;
	काष्ठा list_head *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
पूर्ण

/**
 * list_splice - join two lists, this is deचिन्हित क्रम stacks
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
अटल अंतरभूत व्योम list_splice(स्थिर काष्ठा list_head *list,
				काष्ठा list_head *head)
अणु
	अगर (!list_empty(list))
		__list_splice(list, head, head->next);
पूर्ण

/**
 * list_splice_tail - join two lists, each list being a queue
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
अटल अंतरभूत व्योम list_splice_tail(काष्ठा list_head *list,
				काष्ठा list_head *head)
अणु
	अगर (!list_empty(list))
		__list_splice(list, head->prev, head);
पूर्ण

/**
 * list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
अटल अंतरभूत व्योम list_splice_init(काष्ठा list_head *list,
				    काष्ठा list_head *head)
अणु
	अगर (!list_empty(list)) अणु
		__list_splice(list, head, head->next);
		INIT_LIST_HEAD(list);
	पूर्ण
पूर्ण

/**
 * list_splice_tail_init - join two lists and reinitialise the emptied list
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * Each of the lists is a queue.
 * The list at @list is reinitialised
 */
अटल अंतरभूत व्योम list_splice_tail_init(काष्ठा list_head *list,
					 काष्ठा list_head *head)
अणु
	अगर (!list_empty(list)) अणु
		__list_splice(list, head->prev, head);
		INIT_LIST_HEAD(list);
	पूर्ण
पूर्ण

/**
 * list_entry - get the काष्ठा क्रम this entry
 * @ptr:	the &काष्ठा list_head poपूर्णांकer.
 * @type:	the type of the काष्ठा this is embedded in.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the काष्ठा this is embedded in.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Note, that list is expected to be not empty.
 */
#घोषणा list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

/**
 * list_last_entry - get the last element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the काष्ठा this is embedded in.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Note, that list is expected to be not empty.
 */
#घोषणा list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

/**
 * list_first_entry_or_null - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the काष्ठा this is embedded in.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Note that अगर the list is empty, it वापसs शून्य.
 */
#घोषणा list_first_entry_or_null(ptr, type, member) (अणु \
	काष्ठा list_head *head__ = (ptr); \
	काष्ठा list_head *pos__ = READ_ONCE(head__->next); \
	pos__ != head__ ? list_entry(pos__, type, member) : शून्य; \
पूर्ण)

/**
 * list_next_entry - get the next element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * list_prev_entry - get the prev element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

/**
 * list_क्रम_each	-	iterate over a list
 * @pos:	the &काष्ठा list_head to use as a loop cursor.
 * @head:	the head क्रम your list.
 */
#घोषणा list_क्रम_each(pos, head) \
	क्रम (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_क्रम_each_जारी - जारी iteration over a list
 * @pos:	the &काष्ठा list_head to use as a loop cursor.
 * @head:	the head क्रम your list.
 *
 * Continue to iterate over a list, continuing after the current position.
 */
#घोषणा list_क्रम_each_जारी(pos, head) \
	क्रम (pos = pos->next; pos != (head); pos = pos->next)

/**
 * list_क्रम_each_prev	-	iterate over a list backwards
 * @pos:	the &काष्ठा list_head to use as a loop cursor.
 * @head:	the head क्रम your list.
 */
#घोषणा list_क्रम_each_prev(pos, head) \
	क्रम (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
 * list_क्रम_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &काष्ठा list_head to use as a loop cursor.
 * @n:		another &काष्ठा list_head to use as temporary storage
 * @head:	the head क्रम your list.
 */
#घोषणा list_क्रम_each_safe(pos, n, head) \
	क्रम (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

/**
 * list_क्रम_each_prev_safe - iterate over a list backwards safe against removal of list entry
 * @pos:	the &काष्ठा list_head to use as a loop cursor.
 * @n:		another &काष्ठा list_head to use as temporary storage
 * @head:	the head क्रम your list.
 */
#घोषणा list_क्रम_each_prev_safe(pos, n, head) \
	क्रम (pos = (head)->prev, n = pos->prev; \
	     pos != (head); \
	     pos = n, n = pos->prev)

/**
 * list_entry_is_head - test अगर the entry poपूर्णांकs to the head of the list
 * @pos:	the type * to cursor
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_entry_is_head(pos, head, member)				\
	(&pos->member == (head))

/**
 * list_क्रम_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_क्रम_each_entry(pos, head, member)				\
	क्रम (pos = list_first_entry(head, typeof(*pos), member);	\
	     !list_entry_is_head(pos, head, member);			\
	     pos = list_next_entry(pos, member))

/**
 * list_क्रम_each_entry_reverse - iterate backwards over list of given type.
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_क्रम_each_entry_reverse(pos, head, member)			\
	क्रम (pos = list_last_entry(head, typeof(*pos), member);		\
	     !list_entry_is_head(pos, head, member); 			\
	     pos = list_prev_entry(pos, member))

/**
 * list_prepare_entry - prepare a pos entry क्रम use in list_क्रम_each_entry_जारी()
 * @pos:	the type * to use as a start poपूर्णांक
 * @head:	the head of the list
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Prepares a pos entry क्रम use as a start poपूर्णांक in list_क्रम_each_entry_जारी().
 */
#घोषणा list_prepare_entry(pos, head, member) \
	((pos) ? : list_entry(head, typeof(*pos), member))

/**
 * list_क्रम_each_entry_जारी - जारी iteration over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Continue to iterate over list of given type, continuing after
 * the current position.
 */
#घोषणा list_क्रम_each_entry_जारी(pos, head, member) 		\
	क्रम (pos = list_next_entry(pos, member);			\
	     !list_entry_is_head(pos, head, member);			\
	     pos = list_next_entry(pos, member))

/**
 * list_क्रम_each_entry_जारी_reverse - iterate backwards from the given poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Start to iterate over list of given type backwards, continuing after
 * the current position.
 */
#घोषणा list_क्रम_each_entry_जारी_reverse(pos, head, member)		\
	क्रम (pos = list_prev_entry(pos, member);			\
	     !list_entry_is_head(pos, head, member);			\
	     pos = list_prev_entry(pos, member))

/**
 * list_क्रम_each_entry_from - iterate over list of given type from the current poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Iterate over list of given type, continuing from current position.
 */
#घोषणा list_क्रम_each_entry_from(pos, head, member) 			\
	क्रम (; !list_entry_is_head(pos, head, member);			\
	     pos = list_next_entry(pos, member))

/**
 * list_क्रम_each_entry_from_reverse - iterate backwards over list of given type
 *                                    from the current poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Iterate backwards over list of given type, continuing from current position.
 */
#घोषणा list_क्रम_each_entry_from_reverse(pos, head, member)		\
	क्रम (; !list_entry_is_head(pos, head, member);			\
	     pos = list_prev_entry(pos, member))

/**
 * list_क्रम_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_क्रम_each_entry_safe(pos, n, head, member)			\
	क्रम (pos = list_first_entry(head, typeof(*pos), member),	\
		n = list_next_entry(pos, member);			\
	     !list_entry_is_head(pos, head, member); 			\
	     pos = n, n = list_next_entry(n, member))

/**
 * list_क्रम_each_entry_safe_जारी - जारी list iteration safe against removal
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Iterate over list of given type, continuing after current poपूर्णांक,
 * safe against removal of list entry.
 */
#घोषणा list_क्रम_each_entry_safe_जारी(pos, n, head, member) 		\
	क्रम (pos = list_next_entry(pos, member), 				\
		n = list_next_entry(pos, member);				\
	     !list_entry_is_head(pos, head, member);				\
	     pos = n, n = list_next_entry(n, member))

/**
 * list_क्रम_each_entry_safe_from - iterate over list from current poपूर्णांक safe against removal
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Iterate over list of given type from current poपूर्णांक, safe against
 * removal of list entry.
 */
#घोषणा list_क्रम_each_entry_safe_from(pos, n, head, member) 			\
	क्रम (n = list_next_entry(pos, member);					\
	     !list_entry_is_head(pos, head, member);				\
	     pos = n, n = list_next_entry(n, member))

/**
 * list_क्रम_each_entry_safe_reverse - iterate backwards over list safe against removal
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 *
 * Iterate backwards over list of given type, safe against removal
 * of list entry.
 */
#घोषणा list_क्रम_each_entry_safe_reverse(pos, n, head, member)		\
	क्रम (pos = list_last_entry(head, typeof(*pos), member),		\
		n = list_prev_entry(pos, member);			\
	     !list_entry_is_head(pos, head, member); 			\
	     pos = n, n = list_prev_entry(n, member))

/**
 * list_safe_reset_next - reset a stale list_क्रम_each_entry_safe loop
 * @pos:	the loop cursor used in the list_क्रम_each_entry_safe loop
 * @n:		temporary storage used in list_क्रम_each_entry_safe
 * @member:	the name of the list_head within the काष्ठा.
 *
 * list_safe_reset_next is not safe to use in general अगर the list may be
 * modअगरied concurrently (eg. the lock is dropped in the loop body). An
 * exception to this is अगर the cursor element (pos) is pinned in the list,
 * and list_safe_reset_next is called after re-taking the lock and beक्रमe
 * completing the current iteration of the loop body.
 */
#घोषणा list_safe_reset_next(pos, n, member)				\
	n = list_next_entry(pos, member)

/*
 * Double linked lists with a single poपूर्णांकer list head.
 * Mostly useful क्रम hash tables where the two poपूर्णांकer list head is
 * too wasteful.
 * You lose the ability to access the tail in O(1).
 */

#घोषणा HLIST_HEAD_INIT अणु .first = शून्य पूर्ण
#घोषणा HLIST_HEAD(name) काष्ठा hlist_head name = अणु  .first = शून्य पूर्ण
#घोषणा INIT_HLIST_HEAD(ptr) ((ptr)->first = शून्य)
अटल अंतरभूत व्योम INIT_HLIST_NODE(काष्ठा hlist_node *h)
अणु
	h->next = शून्य;
	h->pprev = शून्य;
पूर्ण

/**
 * hlist_unhashed - Has node been हटाओd from list and reinitialized?
 * @h: Node to be checked
 *
 * Not that not all removal functions will leave a node in unhashed
 * state.  For example, hlist_nulls_del_init_rcu() करोes leave the
 * node in unhashed state, but hlist_nulls_del() करोes not.
 */
अटल अंतरभूत पूर्णांक hlist_unhashed(स्थिर काष्ठा hlist_node *h)
अणु
	वापस !h->pprev;
पूर्ण

/**
 * hlist_unhashed_lockless - Version of hlist_unhashed क्रम lockless use
 * @h: Node to be checked
 *
 * This variant of hlist_unhashed() must be used in lockless contexts
 * to aव्योम potential load-tearing.  The READ_ONCE() is paired with the
 * various WRITE_ONCE() in hlist helpers that are defined below.
 */
अटल अंतरभूत पूर्णांक hlist_unhashed_lockless(स्थिर काष्ठा hlist_node *h)
अणु
	वापस !READ_ONCE(h->pprev);
पूर्ण

/**
 * hlist_empty - Is the specअगरied hlist_head काष्ठाure an empty hlist?
 * @h: Structure to check.
 */
अटल अंतरभूत पूर्णांक hlist_empty(स्थिर काष्ठा hlist_head *h)
अणु
	वापस !READ_ONCE(h->first);
पूर्ण

अटल अंतरभूत व्योम __hlist_del(काष्ठा hlist_node *n)
अणु
	काष्ठा hlist_node *next = n->next;
	काष्ठा hlist_node **pprev = n->pprev;

	WRITE_ONCE(*pprev, next);
	अगर (next)
		WRITE_ONCE(next->pprev, pprev);
पूर्ण

/**
 * hlist_del - Delete the specअगरied hlist_node from its list
 * @n: Node to delete.
 *
 * Note that this function leaves the node in hashed state.  Use
 * hlist_del_init() or similar instead to unhash @n.
 */
अटल अंतरभूत व्योम hlist_del(काष्ठा hlist_node *n)
अणु
	__hlist_del(n);
	n->next = LIST_POISON1;
	n->pprev = LIST_POISON2;
पूर्ण

/**
 * hlist_del_init - Delete the specअगरied hlist_node from its list and initialize
 * @n: Node to delete.
 *
 * Note that this function leaves the node in unhashed state.
 */
अटल अंतरभूत व्योम hlist_del_init(काष्ठा hlist_node *n)
अणु
	अगर (!hlist_unhashed(n)) अणु
		__hlist_del(n);
		INIT_HLIST_NODE(n);
	पूर्ण
पूर्ण

/**
 * hlist_add_head - add a new entry at the beginning of the hlist
 * @n: new entry to be added
 * @h: hlist head to add it after
 *
 * Insert a new entry after the specअगरied head.
 * This is good क्रम implementing stacks.
 */
अटल अंतरभूत व्योम hlist_add_head(काष्ठा hlist_node *n, काष्ठा hlist_head *h)
अणु
	काष्ठा hlist_node *first = h->first;
	WRITE_ONCE(n->next, first);
	अगर (first)
		WRITE_ONCE(first->pprev, &n->next);
	WRITE_ONCE(h->first, n);
	WRITE_ONCE(n->pprev, &h->first);
पूर्ण

/**
 * hlist_add_beक्रमe - add a new entry beक्रमe the one specअगरied
 * @n: new entry to be added
 * @next: hlist node to add it beक्रमe, which must be non-शून्य
 */
अटल अंतरभूत व्योम hlist_add_beक्रमe(काष्ठा hlist_node *n,
				    काष्ठा hlist_node *next)
अणु
	WRITE_ONCE(n->pprev, next->pprev);
	WRITE_ONCE(n->next, next);
	WRITE_ONCE(next->pprev, &n->next);
	WRITE_ONCE(*(n->pprev), n);
पूर्ण

/**
 * hlist_add_behind - add a new entry after the one specअगरied
 * @n: new entry to be added
 * @prev: hlist node to add it after, which must be non-शून्य
 */
अटल अंतरभूत व्योम hlist_add_behind(काष्ठा hlist_node *n,
				    काष्ठा hlist_node *prev)
अणु
	WRITE_ONCE(n->next, prev->next);
	WRITE_ONCE(prev->next, n);
	WRITE_ONCE(n->pprev, &prev->next);

	अगर (n->next)
		WRITE_ONCE(n->next->pprev, &n->next);
पूर्ण

/**
 * hlist_add_fake - create a fake hlist consisting of a single headless node
 * @n: Node to make a fake list out of
 *
 * This makes @n appear to be its own predecessor on a headless hlist.
 * The poपूर्णांक of this is to allow things like hlist_del() to work correctly
 * in हालs where there is no list.
 */
अटल अंतरभूत व्योम hlist_add_fake(काष्ठा hlist_node *n)
अणु
	n->pprev = &n->next;
पूर्ण

/**
 * hlist_fake: Is this node a fake hlist?
 * @h: Node to check क्रम being a self-referential fake hlist.
 */
अटल अंतरभूत bool hlist_fake(काष्ठा hlist_node *h)
अणु
	वापस h->pprev == &h->next;
पूर्ण

/**
 * hlist_is_singular_node - is node the only element of the specअगरied hlist?
 * @n: Node to check क्रम singularity.
 * @h: Header क्रम potentially singular list.
 *
 * Check whether the node is the only node of the head without
 * accessing head, thus aव्योमing unnecessary cache misses.
 */
अटल अंतरभूत bool
hlist_is_singular_node(काष्ठा hlist_node *n, काष्ठा hlist_head *h)
अणु
	वापस !n->next && n->pprev == &h->first;
पूर्ण

/**
 * hlist_move_list - Move an hlist
 * @old: hlist_head क्रम old list.
 * @new: hlist_head क्रम new list.
 *
 * Move a list from one list head to another. Fixup the pprev
 * reference of the first entry अगर it exists.
 */
अटल अंतरभूत व्योम hlist_move_list(काष्ठा hlist_head *old,
				   काष्ठा hlist_head *new)
अणु
	new->first = old->first;
	अगर (new->first)
		new->first->pprev = &new->first;
	old->first = शून्य;
पूर्ण

#घोषणा hlist_entry(ptr, type, member) container_of(ptr,type,member)

#घोषणा hlist_क्रम_each(pos, head) \
	क्रम (pos = (head)->first; pos ; pos = pos->next)

#घोषणा hlist_क्रम_each_safe(pos, n, head) \
	क्रम (pos = (head)->first; pos && (अणु n = pos->next; 1; पूर्ण); \
	     pos = n)

#घोषणा hlist_entry_safe(ptr, type, member) \
	(अणु typeof(ptr) ____ptr = (ptr); \
	   ____ptr ? hlist_entry(____ptr, type, member) : शून्य; \
	पूर्ण)

/**
 * hlist_क्रम_each_entry	- iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 */
#घोषणा hlist_क्रम_each_entry(pos, head, member)				\
	क्रम (pos = hlist_entry_safe((head)->first, typeof(*(pos)), member);\
	     pos;							\
	     pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_जारी - iterate over a hlist continuing after current poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @member:	the name of the hlist_node within the काष्ठा.
 */
#घोषणा hlist_क्रम_each_entry_जारी(pos, member)			\
	क्रम (pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member);\
	     pos;							\
	     pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_from - iterate over a hlist continuing from current poपूर्णांक
 * @pos:	the type * to use as a loop cursor.
 * @member:	the name of the hlist_node within the काष्ठा.
 */
#घोषणा hlist_क्रम_each_entry_from(pos, member)				\
	क्रम (; pos;							\
	     pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))

/**
 * hlist_क्रम_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		a &काष्ठा hlist_node to use as temporary storage
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 */
#घोषणा hlist_क्रम_each_entry_safe(pos, n, head, member) 		\
	क्रम (pos = hlist_entry_safe((head)->first, typeof(*pos), member);\
	     pos && (अणु n = pos->member.next; 1; पूर्ण);			\
	     pos = hlist_entry_safe(n, typeof(*pos), member))

#पूर्ण_अगर
