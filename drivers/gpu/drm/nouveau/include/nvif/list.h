<शैली गुरु>
/*
 * Copyright तऊ 2010 Intel Corporation
 * Copyright तऊ 2010 Francisco Jerez <currojerez@riseup.net>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

/* Modअगरied by Ben Skeggs <bskeggs@redhat.com> to match kernel list APIs */

#अगर_अघोषित _XORG_LIST_H_
#घोषणा _XORG_LIST_H_

/**
 * @file Classic करोubly-link circular list implementation.
 * For real usage examples of the linked list, see the file test/list.c
 *
 * Example:
 * We need to keep a list of काष्ठा foo in the parent काष्ठा bar, i.e. what
 * we want is something like this.
 *
 *     काष्ठा bar अणु
 *          ...
 *          काष्ठा foo *list_of_foos; -----> काष्ठा foo अणुपूर्ण, काष्ठा foo अणुपूर्ण, काष्ठा fooअणुपूर्ण
 *          ...
 *     पूर्ण
 *
 * We need one list head in bar and a list element in all list_of_foos (both are of
 * data type 'struct list_head').
 *
 *     काष्ठा bar अणु
 *          ...
 *          काष्ठा list_head list_of_foos;
 *          ...
 *     पूर्ण
 *
 *     काष्ठा foo अणु
 *          ...
 *          काष्ठा list_head entry;
 *          ...
 *     पूर्ण
 *
 * Now we initialize the list head:
 *
 *     काष्ठा bar bar;
 *     ...
 *     INIT_LIST_HEAD(&bar.list_of_foos);
 *
 * Then we create the first element and add it to this list:
 *
 *     काष्ठा foo *foo = दो_स्मृति(...);
 *     ....
 *     list_add(&foo->entry, &bar.list_of_foos);
 *
 * Repeat the above क्रम each element you want to add to the list. Deleting
 * works with the element itself.
 *      list_del(&foo->entry);
 *      मुक्त(foo);
 *
 * Note: calling list_del(&bar.list_of_foos) will set bar.list_of_foos to an empty
 * list again.
 *
 * Looping through the list requires a 'struct foo' as iterator and the
 * name of the field the subnodes use.
 *
 * काष्ठा foo *iterator;
 * list_क्रम_each_entry(iterator, &bar.list_of_foos, entry) अणु
 *      अगर (iterator->something == ...)
 *             ...
 * पूर्ण
 *
 * Note: You must not call list_del() on the iterator अगर you जारी the
 * loop. You need to run the safe क्रम-each loop instead:
 *
 * काष्ठा foo *iterator, *next;
 * list_क्रम_each_entry_safe(iterator, next, &bar.list_of_foos, entry) अणु
 *      अगर (...)
 *              list_del(&iterator->entry);
 * पूर्ण
 *
 */

/**
 * The linkage काष्ठा क्रम list nodes. This काष्ठा must be part of your
 * to-be-linked काष्ठा. काष्ठा list_head is required क्रम both the head of the
 * list and क्रम each list node.
 *
 * Position and name of the काष्ठा list_head field is irrelevant.
 * There are no requirements that elements of a list are of the same type.
 * There are no requirements क्रम a list head, any काष्ठा list_head can be a list
 * head.
 */
काष्ठा list_head अणु
    काष्ठा list_head *next, *prev;
पूर्ण;

/**
 * Initialize the list as an empty list.
 *
 * Example:
 * INIT_LIST_HEAD(&bar->list_of_foos);
 *
 * @param The list to initialized.
 */
#घोषणा LIST_HEAD_INIT(name) अणु &(name), &(name) पूर्ण

#घोषणा LIST_HEAD(name) \
	काष्ठा list_head name = LIST_HEAD_INIT(name)

अटल अंतरभूत व्योम
INIT_LIST_HEAD(काष्ठा list_head *list)
अणु
    list->next = list->prev = list;
पूर्ण

अटल अंतरभूत व्योम
__list_add(काष्ठा list_head *entry,
                काष्ठा list_head *prev, काष्ठा list_head *next)
अणु
    next->prev = entry;
    entry->next = next;
    entry->prev = prev;
    prev->next = entry;
पूर्ण

/**
 * Insert a new element after the given list head. The new element करोes not
 * need to be initialised as empty list.
 * The list changes from:
 *      head ै some element ै ...
 * to
 *      head ै new element ै older element ै ...
 *
 * Example:
 * काष्ठा foo *newfoo = दो_स्मृति(...);
 * list_add(&newfoo->entry, &bar->list_of_foos);
 *
 * @param entry The new element to prepend to the list.
 * @param head The existing list.
 */
अटल अंतरभूत व्योम
list_add(काष्ठा list_head *entry, काष्ठा list_head *head)
अणु
    __list_add(entry, head, head->next);
पूर्ण

/**
 * Append a new element to the end of the list given with this list head.
 *
 * The list changes from:
 *      head ै some element ै ... ै lastelement
 * to
 *      head ै some element ै ... ै lastelement ै new element
 *
 * Example:
 * काष्ठा foo *newfoo = दो_स्मृति(...);
 * list_add_tail(&newfoo->entry, &bar->list_of_foos);
 *
 * @param entry The new element to prepend to the list.
 * @param head The existing list.
 */
अटल अंतरभूत व्योम
list_add_tail(काष्ठा list_head *entry, काष्ठा list_head *head)
अणु
    __list_add(entry, head->prev, head);
पूर्ण

अटल अंतरभूत व्योम
__list_del(काष्ठा list_head *prev, काष्ठा list_head *next)
अणु
    next->prev = prev;
    prev->next = next;
पूर्ण

/**
 * Remove the element from the list it is in. Using this function will reset
 * the poपूर्णांकers to/from this element so it is हटाओd from the list. It करोes
 * NOT मुक्त the element itself or manipulate it otherwise.
 *
 * Using list_del on a pure list head (like in the example at the top of
 * this file) will NOT हटाओ the first element from
 * the list but rather reset the list as empty list.
 *
 * Example:
 * list_del(&foo->entry);
 *
 * @param entry The element to हटाओ.
 */
अटल अंतरभूत व्योम
list_del(काष्ठा list_head *entry)
अणु
    __list_del(entry->prev, entry->next);
पूर्ण

अटल अंतरभूत व्योम
list_del_init(काष्ठा list_head *entry)
अणु
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
पूर्ण

अटल अंतरभूत व्योम list_move_tail(काष्ठा list_head *list,
				  काष्ठा list_head *head)
अणु
	__list_del(list->prev, list->next);
	list_add_tail(list, head);
पूर्ण

/**
 * Check अगर the list is empty.
 *
 * Example:
 * list_empty(&bar->list_of_foos);
 *
 * @वापस True अगर the list contains one or more elements or False otherwise.
 */
अटल अंतरभूत bool
list_empty(काष्ठा list_head *head)
अणु
    वापस head->next == head;
पूर्ण

/**
 * Returns a poपूर्णांकer to the container of this list element.
 *
 * Example:
 * काष्ठा foo* f;
 * f = container_of(&foo->entry, काष्ठा foo, entry);
 * निश्चित(f == foo);
 *
 * @param ptr Poपूर्णांकer to the काष्ठा list_head.
 * @param type Data type of the list element.
 * @param member Member name of the काष्ठा list_head field in the list element.
 * @वापस A poपूर्णांकer to the data काष्ठा containing the list head.
 */
#अगर_अघोषित container_of
#घोषणा container_of(ptr, type, member) \
    (type *)((अक्षर *)(ptr) - (अक्षर *) &((type *)0)->member)
#पूर्ण_अगर

/**
 * Alias of container_of
 */
#घोषणा list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * Retrieve the first list entry क्रम the given list poपूर्णांकer.
 *
 * Example:
 * काष्ठा foo *first;
 * first = list_first_entry(&bar->list_of_foos, काष्ठा foo, list_of_foos);
 *
 * @param ptr The list head
 * @param type Data type of the list element to retrieve
 * @param member Member name of the काष्ठा list_head field in the list element.
 * @वापस A poपूर्णांकer to the first list element.
 */
#घोषणा list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
 * Retrieve the last list entry क्रम the given listpoपूर्णांकer.
 *
 * Example:
 * काष्ठा foo *first;
 * first = list_last_entry(&bar->list_of_foos, काष्ठा foo, list_of_foos);
 *
 * @param ptr The list head
 * @param type Data type of the list element to retrieve
 * @param member Member name of the काष्ठा list_head field in the list element.
 * @वापस A poपूर्णांकer to the last list element.
 */
#घोषणा list_last_entry(ptr, type, member) \
    list_entry((ptr)->prev, type, member)

#घोषणा __container_of(ptr, sample, member)				\
    (व्योम *)container_of((ptr), typeof(*(sample)), member)

/**
 * Loop through the list given by head and set pos to काष्ठा in the list.
 *
 * Example:
 * काष्ठा foo *iterator;
 * list_क्रम_each_entry(iterator, &bar->list_of_foos, entry) अणु
 *      [modअगरy iterator]
 * पूर्ण
 *
 * This macro is not safe क्रम node deletion. Use list_क्रम_each_entry_safe
 * instead.
 *
 * @param pos Iterator variable of the type of the list elements.
 * @param head List head
 * @param member Member name of the काष्ठा list_head in the list elements.
 *
 */
#घोषणा list_क्रम_each_entry(pos, head, member)				\
    क्रम (pos = __container_of((head)->next, pos, member);		\
	 &pos->member != (head);					\
	 pos = __container_of(pos->member.next, pos, member))

/**
 * Loop through the list, keeping a backup poपूर्णांकer to the element. This
 * macro allows क्रम the deletion of a list element जबतक looping through the
 * list.
 *
 * See list_क्रम_each_entry क्रम more details.
 */
#घोषणा list_क्रम_each_entry_safe(pos, पंचांगp, head, member)		\
    क्रम (pos = __container_of((head)->next, pos, member),		\
	 पंचांगp = __container_of(pos->member.next, pos, member);		\
	 &pos->member != (head);					\
	 pos = पंचांगp, पंचांगp = __container_of(pos->member.next, पंचांगp, member))


#घोषणा list_क्रम_each_entry_reverse(pos, head, member)			\
	क्रम (pos = __container_of((head)->prev, pos, member);		\
	     &pos->member != (head);					\
	     pos = __container_of(pos->member.prev, pos, member))

#घोषणा list_क्रम_each_entry_जारी(pos, head, member)			\
	क्रम (pos = __container_of(pos->member.next, pos, member);	\
	     &pos->member != (head);					\
	     pos = __container_of(pos->member.next, pos, member))

#घोषणा list_क्रम_each_entry_जारी_reverse(pos, head, member)		\
	क्रम (pos = __container_of(pos->member.prev, pos, member);	\
	     &pos->member != (head);					\
	     pos = __container_of(pos->member.prev, pos, member))

#घोषणा list_क्रम_each_entry_from(pos, head, member)			\
	क्रम (;								\
	     &pos->member != (head);					\
	     pos = __container_of(pos->member.next, pos, member))

#पूर्ण_अगर
