<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LIST_BL_H
#घोषणा _LINUX_LIST_BL_H

#समावेश <linux/list.h>
#समावेश <linux/bit_spinlock.h>

/*
 * Special version of lists, where head of the list has a lock in the lowest
 * bit. This is useful क्रम scalable hash tables without increasing memory
 * footprपूर्णांक overhead.
 *
 * For modअगरication operations, the 0 bit of hlist_bl_head->first
 * poपूर्णांकer must be set.
 *
 * With some small modअगरications, this can easily be adapted to store several
 * arbitrary bits (not just a single lock bit), अगर the need arises to store
 * some fast and compact auxiliary data.
 */

#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
#घोषणा LIST_BL_LOCKMASK	1UL
#अन्यथा
#घोषणा LIST_BL_LOCKMASK	0UL
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_LIST
#घोषणा LIST_BL_BUG_ON(x) BUG_ON(x)
#अन्यथा
#घोषणा LIST_BL_BUG_ON(x)
#पूर्ण_अगर


काष्ठा hlist_bl_head अणु
	काष्ठा hlist_bl_node *first;
पूर्ण;

काष्ठा hlist_bl_node अणु
	काष्ठा hlist_bl_node *next, **pprev;
पूर्ण;
#घोषणा INIT_HLIST_BL_HEAD(ptr) \
	((ptr)->first = शून्य)

अटल अंतरभूत व्योम INIT_HLIST_BL_NODE(काष्ठा hlist_bl_node *h)
अणु
	h->next = शून्य;
	h->pprev = शून्य;
पूर्ण

#घोषणा hlist_bl_entry(ptr, type, member) container_of(ptr,type,member)

अटल अंतरभूत bool  hlist_bl_unhashed(स्थिर काष्ठा hlist_bl_node *h)
अणु
	वापस !h->pprev;
पूर्ण

अटल अंतरभूत काष्ठा hlist_bl_node *hlist_bl_first(काष्ठा hlist_bl_head *h)
अणु
	वापस (काष्ठा hlist_bl_node *)
		((अचिन्हित दीर्घ)h->first & ~LIST_BL_LOCKMASK);
पूर्ण

अटल अंतरभूत व्योम hlist_bl_set_first(काष्ठा hlist_bl_head *h,
					काष्ठा hlist_bl_node *n)
अणु
	LIST_BL_BUG_ON((अचिन्हित दीर्घ)n & LIST_BL_LOCKMASK);
	LIST_BL_BUG_ON(((अचिन्हित दीर्घ)h->first & LIST_BL_LOCKMASK) !=
							LIST_BL_LOCKMASK);
	h->first = (काष्ठा hlist_bl_node *)((अचिन्हित दीर्घ)n | LIST_BL_LOCKMASK);
पूर्ण

अटल अंतरभूत bool hlist_bl_empty(स्थिर काष्ठा hlist_bl_head *h)
अणु
	वापस !((अचिन्हित दीर्घ)READ_ONCE(h->first) & ~LIST_BL_LOCKMASK);
पूर्ण

अटल अंतरभूत व्योम hlist_bl_add_head(काष्ठा hlist_bl_node *n,
					काष्ठा hlist_bl_head *h)
अणु
	काष्ठा hlist_bl_node *first = hlist_bl_first(h);

	n->next = first;
	अगर (first)
		first->pprev = &n->next;
	n->pprev = &h->first;
	hlist_bl_set_first(h, n);
पूर्ण

अटल अंतरभूत व्योम hlist_bl_add_beक्रमe(काष्ठा hlist_bl_node *n,
				       काष्ठा hlist_bl_node *next)
अणु
	काष्ठा hlist_bl_node **pprev = next->pprev;

	n->pprev = pprev;
	n->next = next;
	next->pprev = &n->next;

	/* pprev may be `first`, so be careful not to lose the lock bit */
	WRITE_ONCE(*pprev,
		   (काष्ठा hlist_bl_node *)
			((uपूर्णांकptr_t)n | ((uपूर्णांकptr_t)*pprev & LIST_BL_LOCKMASK)));
पूर्ण

अटल अंतरभूत व्योम hlist_bl_add_behind(काष्ठा hlist_bl_node *n,
				       काष्ठा hlist_bl_node *prev)
अणु
	n->next = prev->next;
	n->pprev = &prev->next;
	prev->next = n;

	अगर (n->next)
		n->next->pprev = &n->next;
पूर्ण

अटल अंतरभूत व्योम __hlist_bl_del(काष्ठा hlist_bl_node *n)
अणु
	काष्ठा hlist_bl_node *next = n->next;
	काष्ठा hlist_bl_node **pprev = n->pprev;

	LIST_BL_BUG_ON((अचिन्हित दीर्घ)n & LIST_BL_LOCKMASK);

	/* pprev may be `first`, so be careful not to lose the lock bit */
	WRITE_ONCE(*pprev,
		   (काष्ठा hlist_bl_node *)
			((अचिन्हित दीर्घ)next |
			 ((अचिन्हित दीर्घ)*pprev & LIST_BL_LOCKMASK)));
	अगर (next)
		next->pprev = pprev;
पूर्ण

अटल अंतरभूत व्योम hlist_bl_del(काष्ठा hlist_bl_node *n)
अणु
	__hlist_bl_del(n);
	n->next = LIST_POISON1;
	n->pprev = LIST_POISON2;
पूर्ण

अटल अंतरभूत व्योम hlist_bl_del_init(काष्ठा hlist_bl_node *n)
अणु
	अगर (!hlist_bl_unhashed(n)) अणु
		__hlist_bl_del(n);
		INIT_HLIST_BL_NODE(n);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hlist_bl_lock(काष्ठा hlist_bl_head *b)
अणु
	bit_spin_lock(0, (अचिन्हित दीर्घ *)b);
पूर्ण

अटल अंतरभूत व्योम hlist_bl_unlock(काष्ठा hlist_bl_head *b)
अणु
	__bit_spin_unlock(0, (अचिन्हित दीर्घ *)b);
पूर्ण

अटल अंतरभूत bool hlist_bl_is_locked(काष्ठा hlist_bl_head *b)
अणु
	वापस bit_spin_is_locked(0, (अचिन्हित दीर्घ *)b);
पूर्ण

/**
 * hlist_bl_क्रम_each_entry	- iterate over list of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा hlist_node to use as a loop cursor.
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 *
 */
#घोषणा hlist_bl_क्रम_each_entry(tpos, pos, head, member)		\
	क्रम (pos = hlist_bl_first(head);				\
	     pos &&							\
		(अणु tpos = hlist_bl_entry(pos, typeof(*tpos), member); 1;पूर्ण); \
	     pos = pos->next)

/**
 * hlist_bl_क्रम_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा hlist_node to use as a loop cursor.
 * @n:		another &काष्ठा hlist_node to use as temporary storage
 * @head:	the head क्रम your list.
 * @member:	the name of the hlist_node within the काष्ठा.
 */
#घोषणा hlist_bl_क्रम_each_entry_safe(tpos, pos, n, head, member)	 \
	क्रम (pos = hlist_bl_first(head);				 \
	     pos && (अणु n = pos->next; 1; पूर्ण) && 				 \
		(अणु tpos = hlist_bl_entry(pos, typeof(*tpos), member); 1;पूर्ण); \
	     pos = n)

#पूर्ण_अगर
