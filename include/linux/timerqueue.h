<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TIMERQUEUE_H
#घोषणा _LINUX_TIMERQUEUE_H

#समावेश <linux/rbtree.h>
#समावेश <linux/kसमय.स>


काष्ठा समयrqueue_node अणु
	काष्ठा rb_node node;
	kसमय_प्रकार expires;
पूर्ण;

काष्ठा समयrqueue_head अणु
	काष्ठा rb_root_cached rb_root;
पूर्ण;


बाह्य bool समयrqueue_add(काष्ठा समयrqueue_head *head,
			   काष्ठा समयrqueue_node *node);
बाह्य bool समयrqueue_del(काष्ठा समयrqueue_head *head,
			   काष्ठा समयrqueue_node *node);
बाह्य काष्ठा समयrqueue_node *समयrqueue_iterate_next(
						काष्ठा समयrqueue_node *node);

/**
 * समयrqueue_getnext - Returns the समयr with the earliest expiration समय
 *
 * @head: head of समयrqueue
 *
 * Returns a poपूर्णांकer to the समयr node that has the earliest expiration समय.
 */
अटल अंतरभूत
काष्ठा समयrqueue_node *समयrqueue_getnext(काष्ठा समयrqueue_head *head)
अणु
	काष्ठा rb_node *lefपंचांगost = rb_first_cached(&head->rb_root);

	वापस rb_entry(lefपंचांगost, काष्ठा समयrqueue_node, node);
पूर्ण

अटल अंतरभूत व्योम समयrqueue_init(काष्ठा समयrqueue_node *node)
अणु
	RB_CLEAR_NODE(&node->node);
पूर्ण

अटल अंतरभूत bool समयrqueue_node_queued(काष्ठा समयrqueue_node *node)
अणु
	वापस !RB_EMPTY_NODE(&node->node);
पूर्ण

अटल अंतरभूत bool समयrqueue_node_expires(काष्ठा समयrqueue_node *node)
अणु
	वापस node->expires;
पूर्ण

अटल अंतरभूत व्योम समयrqueue_init_head(काष्ठा समयrqueue_head *head)
अणु
	head->rb_root = RB_ROOT_CACHED;
पूर्ण
#पूर्ण_अगर /* _LINUX_TIMERQUEUE_H */
