<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only OR BSD-2-Clause */
#अगर_अघोषित FREELIST_H
#घोषणा FREELIST_H

#समावेश <linux/atomic.h>

/*
 * Copyright: cameron@moodycamel.com
 *
 * A simple CAS-based lock-मुक्त मुक्त list. Not the fastest thing in the world
 * under heavy contention, but simple and correct (assuming nodes are never
 * मुक्तd until after the मुक्त list is destroyed), and fairly speedy under low
 * contention.
 *
 * Adapted from: https://moodycamel.com/blog/2014/solving-the-aba-problem-क्रम-lock-मुक्त-मुक्त-lists
 */

काष्ठा मुक्तlist_node अणु
	atomic_t		refs;
	काष्ठा मुक्तlist_node	*next;
पूर्ण;

काष्ठा मुक्तlist_head अणु
	काष्ठा मुक्तlist_node	*head;
पूर्ण;

#घोषणा REFS_ON_FREELIST 0x80000000
#घोषणा REFS_MASK	 0x7FFFFFFF

अटल अंतरभूत व्योम __मुक्तlist_add(काष्ठा मुक्तlist_node *node, काष्ठा मुक्तlist_head *list)
अणु
	/*
	 * Since the refcount is zero, and nobody can increase it once it's
	 * zero (except us, and we run only one copy of this method per node at
	 * a समय, i.e. the single thपढ़ो हाल), then we know we can safely
	 * change the next poपूर्णांकer of the node; however, once the refcount is
	 * back above zero, then other thपढ़ोs could increase it (happens under
	 * heavy contention, when the refcount goes to zero in between a load
	 * and a refcount increment of a node in try_get, then back up to
	 * something non-zero, then the refcount increment is करोne by the other
	 * thपढ़ो) -- so अगर the CAS to add the node to the actual list fails,
	 * decrese the refcount and leave the add operation to the next thपढ़ो
	 * who माला_दो the refcount back to zero (which could be us, hence the
	 * loop).
	 */
	काष्ठा मुक्तlist_node *head = READ_ONCE(list->head);

	क्रम (;;) अणु
		WRITE_ONCE(node->next, head);
		atomic_set_release(&node->refs, 1);

		अगर (!try_cmpxchg_release(&list->head, &head, node)) अणु
			/*
			 * Hmm, the add failed, but we can only try again when
			 * the refcount goes back to zero.
			 */
			अगर (atomic_fetch_add_release(REFS_ON_FREELIST - 1, &node->refs) == 1)
				जारी;
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम मुक्तlist_add(काष्ठा मुक्तlist_node *node, काष्ठा मुक्तlist_head *list)
अणु
	/*
	 * We know that the should-be-on-मुक्तlist bit is 0 at this poपूर्णांक, so
	 * it's safe to set it using a fetch_add.
	 */
	अगर (!atomic_fetch_add_release(REFS_ON_FREELIST, &node->refs)) अणु
		/*
		 * Oh look! We were the last ones referencing this node, and we
		 * know we want to add it to the मुक्त list, so let's करो it!
		 */
		__मुक्तlist_add(node, list);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा मुक्तlist_node *मुक्तlist_try_get(काष्ठा मुक्तlist_head *list)
अणु
	काष्ठा मुक्तlist_node *prev, *next, *head = smp_load_acquire(&list->head);
	अचिन्हित पूर्णांक refs;

	जबतक (head) अणु
		prev = head;
		refs = atomic_पढ़ो(&head->refs);
		अगर ((refs & REFS_MASK) == 0 ||
		    !atomic_try_cmpxchg_acquire(&head->refs, &refs, refs+1)) अणु
			head = smp_load_acquire(&list->head);
			जारी;
		पूर्ण

		/*
		 * Good, reference count has been incremented (it wasn't at
		 * zero), which means we can पढ़ो the next and not worry about
		 * it changing between now and the समय we करो the CAS.
		 */
		next = READ_ONCE(head->next);
		अगर (try_cmpxchg_acquire(&list->head, &head, next)) अणु
			/*
			 * Yay, got the node. This means it was on the list,
			 * which means should-be-on-मुक्तlist must be false no
			 * matter the refcount (because nobody अन्यथा knows it's
			 * been taken off yet, it can't have been put back on).
			 */
			WARN_ON_ONCE(atomic_पढ़ो(&head->refs) & REFS_ON_FREELIST);

			/*
			 * Decrease refcount twice, once क्रम our ref, and once
			 * क्रम the list's ref.
			 */
			atomic_fetch_add(-2, &head->refs);

			वापस head;
		पूर्ण

		/*
		 * OK, the head must have changed on us, but we still need to decrement
		 * the refcount we increased.
		 */
		refs = atomic_fetch_add(-1, &prev->refs);
		अगर (refs == REFS_ON_FREELIST + 1)
			__मुक्तlist_add(prev, list);
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* FREELIST_H */
