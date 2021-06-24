<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIST_H
#घोषणा _LIST_H

/* Stripped करोwn implementation of linked list taken
 * from the Linux Kernel.
 */

/*
 * Simple करोubly linked list implementation.
 *
 * Some of the पूर्णांकernal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * someबार we alपढ़ोy know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

काष्ठा list_head अणु
	काष्ठा list_head *next, *prev;
पूर्ण;

#घोषणा LIST_HEAD_INIT(name) अणु &(name), &(name) पूर्ण

#घोषणा LIST_HEAD(name) \
	काष्ठा list_head name = LIST_HEAD_INIT(name)

अटल अंतरभूत व्योम INIT_LIST_HEAD(काष्ठा list_head *list)
अणु
	list->next = list;
	list->prev = list;
पूर्ण

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
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
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
	prev->next = next;
पूर्ण

#घोषणा POISON_POINTER_DELTA 0
#घोषणा LIST_POISON1  ((व्योम *) 0x00100100 + POISON_POINTER_DELTA)
#घोषणा LIST_POISON2  ((व्योम *) 0x00200200 + POISON_POINTER_DELTA)

अटल अंतरभूत व्योम __list_del_entry(काष्ठा list_head *entry)
अणु
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
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
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
 * list_क्रम_each	-	iterate over a list
 * @pos:	the &काष्ठा list_head to use as a loop cursor.
 * @head:	the head क्रम your list.
 */
#घोषणा list_क्रम_each(pos, head) \
	क्रम (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_क्रम_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &काष्ठा list_head to use as a loop cursor.
 * @n:		another &काष्ठा list_head to use as temporary storage
 * @head:	the head क्रम your list.
 */
#घोषणा list_क्रम_each_safe(pos, n, head) \
	क्रम (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

#घोषणा दुरत्व(TYPE, MEMBER) ((माप_प्रकार) &((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a काष्ठाure out to the containing काष्ठाure
 * @ptr:	the poपूर्णांकer to the member.
 * @type:	the type of the container काष्ठा this is embedded in.
 * @member:	the name of the member within the काष्ठा.
 *
 */
#घोषणा container_of(ptr, type, member) (अणु			\
	स्थिर typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (अक्षर *)__mptr - दुरत्व(type,member) );पूर्ण)

#पूर्ण_अगर
