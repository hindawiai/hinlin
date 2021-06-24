<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Generic Timer-queue
 *
 *  Manages a simple queue of समयrs, ordered by expiration समय.
 *  Uses rbtrees क्रम quick list adds and expiration.
 *
 *  NOTE: All of the following functions need to be serialized
 *  to aव्योम races. No locking is करोne by this library code.
 */

#समावेश <linux/bug.h>
#समावेश <linux/समयrqueue.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/export.h>

#घोषणा __node_2_tq(_n) \
	rb_entry((_n), काष्ठा समयrqueue_node, node)

अटल अंतरभूत bool __समयrqueue_less(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	वापस __node_2_tq(a)->expires < __node_2_tq(b)->expires;
पूर्ण

/**
 * समयrqueue_add - Adds समयr to समयrqueue.
 *
 * @head: head of समयrqueue
 * @node: समयr node to be added
 *
 * Adds the समयr node to the समयrqueue, sorted by the node's expires
 * value. Returns true अगर the newly added समयr is the first expiring समयr in
 * the queue.
 */
bool समयrqueue_add(काष्ठा समयrqueue_head *head, काष्ठा समयrqueue_node *node)
अणु
	/* Make sure we करोn't add nodes that are alपढ़ोy added */
	WARN_ON_ONCE(!RB_EMPTY_NODE(&node->node));

	वापस rb_add_cached(&node->node, &head->rb_root, __समयrqueue_less);
पूर्ण
EXPORT_SYMBOL_GPL(समयrqueue_add);

/**
 * समयrqueue_del - Removes a समयr from the समयrqueue.
 *
 * @head: head of समयrqueue
 * @node: समयr node to be हटाओd
 *
 * Removes the समयr node from the समयrqueue. Returns true अगर the queue is
 * not empty after the हटाओ.
 */
bool समयrqueue_del(काष्ठा समयrqueue_head *head, काष्ठा समयrqueue_node *node)
अणु
	WARN_ON_ONCE(RB_EMPTY_NODE(&node->node));

	rb_erase_cached(&node->node, &head->rb_root);
	RB_CLEAR_NODE(&node->node);

	वापस !RB_EMPTY_ROOT(&head->rb_root.rb_root);
पूर्ण
EXPORT_SYMBOL_GPL(समयrqueue_del);

/**
 * समयrqueue_iterate_next - Returns the समयr after the provided समयr
 *
 * @node: Poपूर्णांकer to a समयr.
 *
 * Provides the समयr that is after the given node. This is used, when
 * necessary, to iterate through the list of समयrs in a समयr list
 * without modअगरying the list.
 */
काष्ठा समयrqueue_node *समयrqueue_iterate_next(काष्ठा समयrqueue_node *node)
अणु
	काष्ठा rb_node *next;

	अगर (!node)
		वापस शून्य;
	next = rb_next(&node->node);
	अगर (!next)
		वापस शून्य;
	वापस container_of(next, काष्ठा समयrqueue_node, node);
पूर्ण
EXPORT_SYMBOL_GPL(समयrqueue_iterate_next);
