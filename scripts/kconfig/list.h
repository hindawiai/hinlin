<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LIST_H
#घोषणा LIST_H

/*
 * Copied from include/linux/...
 */

#अघोषित दुरत्व
#घोषणा दुरत्व(TYPE, MEMBER) ((माप_प्रकार) &((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a काष्ठाure out to the containing काष्ठाure
 * @ptr:        the poपूर्णांकer to the member.
 * @type:       the type of the container काष्ठा this is embedded in.
 * @member:     the name of the member within the काष्ठा.
 *
 */
#घोषणा container_of(ptr, type, member) (अणु                      \
	स्थिर typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (अक्षर *)__mptr - दुरत्व(type,member) );पूर्ण)


काष्ठा list_head अणु
	काष्ठा list_head *next, *prev;
पूर्ण;


#घोषणा LIST_HEAD_INIT(name) अणु &(name), &(name) पूर्ण

#घोषणा LIST_HEAD(name) \
	काष्ठा list_head name = LIST_HEAD_INIT(name)

/**
 * list_entry - get the काष्ठा क्रम this entry
 * @ptr:	the &काष्ठा list_head poपूर्णांकer.
 * @type:	the type of the काष्ठा this is embedded in.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_क्रम_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_क्रम_each_entry(pos, head, member)				\
	क्रम (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * list_क्रम_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head क्रम your list.
 * @member:	the name of the list_head within the काष्ठा.
 */
#घोषणा list_क्रम_each_entry_safe(pos, n, head, member)			\
	क्रम (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
अटल अंतरभूत पूर्णांक list_empty(स्थिर काष्ठा list_head *head)
अणु
	वापस head->next == head;
पूर्ण

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only क्रम पूर्णांकernal list manipulation where we know
 * the prev/next entries alपढ़ोy!
 */
अटल अंतरभूत व्योम __list_add(काष्ठा list_head *_new,
			      काष्ठा list_head *prev,
			      काष्ठा list_head *next)
अणु
	next->prev = _new;
	_new->next = next;
	_new->prev = prev;
	prev->next = _new;
पूर्ण

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it beक्रमe
 *
 * Insert a new entry beक्रमe the specअगरied head.
 * This is useful क्रम implementing queues.
 */
अटल अंतरभूत व्योम list_add_tail(काष्ठा list_head *_new, काष्ठा list_head *head)
अणु
	__list_add(_new, head->prev, head);
पूर्ण

/*
 * Delete a list entry by making the prev/next entries
 * poपूर्णांक to each other.
 *
 * This is only क्रम पूर्णांकernal list manipulation where we know
 * the prev/next entries alपढ़ोy!
 */
अटल अंतरभूत व्योम __list_del(काष्ठा list_head *prev, काष्ठा list_head *next)
अणु
	next->prev = prev;
	prev->next = next;
पूर्ण

#घोषणा LIST_POISON1  ((व्योम *) 0x00100100)
#घोषणा LIST_POISON2  ((व्योम *) 0x00200200)
/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry करोes not वापस true after this, the entry is
 * in an undefined state.
 */
अटल अंतरभूत व्योम list_del(काष्ठा list_head *entry)
अणु
	__list_del(entry->prev, entry->next);
	entry->next = (काष्ठा list_head*)LIST_POISON1;
	entry->prev = (काष्ठा list_head*)LIST_POISON2;
पूर्ण
#पूर्ण_अगर
