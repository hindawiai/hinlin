<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
काष्ठा list अणु
	काष्ठा list *next, *prev;
पूर्ण;

अटल अंतरभूत व्योम
list_init(काष्ठा list *list)
अणु
	list->next = list;
	list->prev = list;
पूर्ण

अटल अंतरभूत पूर्णांक
list_empty(काष्ठा list *list)
अणु
	वापस list->next == list;
पूर्ण

अटल अंतरभूत व्योम
list_insert(काष्ठा list *link, काष्ठा list *new_link)
अणु
	new_link->prev		= link->prev;
	new_link->next		= link;
	new_link->prev->next	= new_link;
	new_link->next->prev	= new_link;
पूर्ण

अटल अंतरभूत व्योम
list_append(काष्ठा list *list, काष्ठा list *new_link)
अणु
	list_insert((काष्ठा list *)list, new_link);
पूर्ण

अटल अंतरभूत व्योम
list_prepend(काष्ठा list *list, काष्ठा list *new_link)
अणु
	list_insert(list->next, new_link);
पूर्ण

अटल अंतरभूत व्योम
list_हटाओ(काष्ठा list *link)
अणु
	link->prev->next = link->next;
	link->next->prev = link->prev;
पूर्ण

#घोषणा list_entry(link, type, member) \
	((type *)((अक्षर *)(link)-(अचिन्हित दीर्घ)(&((type *)0)->member)))

#घोषणा list_head(list, type, member)		\
	list_entry((list)->next, type, member)

#घोषणा list_tail(list, type, member)		\
	list_entry((list)->prev, type, member)

#घोषणा list_next(elm, member)					\
	list_entry((elm)->member.next, typeof(*elm), member)

#घोषणा list_क्रम_each_entry(pos, list, member)			\
	क्रम (pos = list_head(list, typeof(*pos), member);	\
	     &pos->member != (list);				\
	     pos = list_next(pos, member))

