<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Latched RB-trees
 *
 * Copyright (C) 2015 Intel Corp., Peter Zijlstra <peterz@infradead.org>
 *
 * Since RB-trees have non-atomic modअगरications they're not immediately suited
 * क्रम RCU/lockless queries. Even though we made RB-tree lookups non-fatal क्रम
 * lockless lookups; we cannot guarantee they वापस a correct result.
 *
 * The simplest solution is a seqlock + RB-tree, this will allow lockless
 * lookups; but has the स्थिरraपूर्णांक (inherent to the seqlock) that पढ़ो sides
 * cannot nest in ग_लिखो sides.
 *
 * If we need to allow unconditional lookups (say as required क्रम NMI context
 * usage) we need a more complex setup; this data काष्ठाure provides this by
 * employing the latch technique -- see @raw_ग_लिखो_seqcount_latch -- to
 * implement a latched RB-tree which करोes allow क्रम unconditional lookups by
 * virtue of always having (at least) one stable copy of the tree.
 *
 * However, जबतक we have the guarantee that there is at all बार one stable
 * copy, this करोes not guarantee an iteration will not observe modअगरications.
 * What might have been a stable copy at the start of the iteration, need not
 * reमुख्य so क्रम the duration of the iteration.
 *
 * Thereक्रमe, this करोes require a lockless RB-tree iteration to be non-fatal;
 * see the comment in lib/rbtree.c. Note however that we only require the first
 * condition -- not seeing partial stores -- because the latch thing isolates
 * us from loops. If we were to पूर्णांकerrupt a modअगरication the lookup would be
 * poपूर्णांकed at the stable tree and complete जबतक the modअगरication was halted.
 */

#अगर_अघोषित RB_TREE_LATCH_H
#घोषणा RB_TREE_LATCH_H

#समावेश <linux/rbtree.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/rcupdate.h>

काष्ठा latch_tree_node अणु
	काष्ठा rb_node node[2];
पूर्ण;

काष्ठा latch_tree_root अणु
	seqcount_latch_t	seq;
	काष्ठा rb_root		tree[2];
पूर्ण;

/**
 * latch_tree_ops - चालकs to define the tree order
 * @less: used क्रम insertion; provides the (partial) order between two elements.
 * @comp: used क्रम lookups; provides the order between the search key and an element.
 *
 * The चालकs are related like:
 *
 *	comp(a->key,b) < 0  := less(a,b)
 *	comp(a->key,b) > 0  := less(b,a)
 *	comp(a->key,b) == 0 := !less(a,b) && !less(b,a)
 *
 * If these चालकs define a partial order on the elements we make no
 * guarantee on which of the elements matching the key is found. See
 * latch_tree_find().
 */
काष्ठा latch_tree_ops अणु
	bool (*less)(काष्ठा latch_tree_node *a, काष्ठा latch_tree_node *b);
	पूर्णांक  (*comp)(व्योम *key,                 काष्ठा latch_tree_node *b);
पूर्ण;

अटल __always_अंतरभूत काष्ठा latch_tree_node *
__lt_from_rb(काष्ठा rb_node *node, पूर्णांक idx)
अणु
	वापस container_of(node, काष्ठा latch_tree_node, node[idx]);
पूर्ण

अटल __always_अंतरभूत व्योम
__lt_insert(काष्ठा latch_tree_node *ltn, काष्ठा latch_tree_root *ltr, पूर्णांक idx,
	    bool (*less)(काष्ठा latch_tree_node *a, काष्ठा latch_tree_node *b))
अणु
	काष्ठा rb_root *root = &ltr->tree[idx];
	काष्ठा rb_node **link = &root->rb_node;
	काष्ठा rb_node *node = &ltn->node[idx];
	काष्ठा rb_node *parent = शून्य;
	काष्ठा latch_tree_node *ltp;

	जबतक (*link) अणु
		parent = *link;
		ltp = __lt_from_rb(parent, idx);

		अगर (less(ltn, ltp))
			link = &parent->rb_left;
		अन्यथा
			link = &parent->rb_right;
	पूर्ण

	rb_link_node_rcu(node, parent, link);
	rb_insert_color(node, root);
पूर्ण

अटल __always_अंतरभूत व्योम
__lt_erase(काष्ठा latch_tree_node *ltn, काष्ठा latch_tree_root *ltr, पूर्णांक idx)
अणु
	rb_erase(&ltn->node[idx], &ltr->tree[idx]);
पूर्ण

अटल __always_अंतरभूत काष्ठा latch_tree_node *
__lt_find(व्योम *key, काष्ठा latch_tree_root *ltr, पूर्णांक idx,
	  पूर्णांक (*comp)(व्योम *key, काष्ठा latch_tree_node *node))
अणु
	काष्ठा rb_node *node = rcu_dereference_raw(ltr->tree[idx].rb_node);
	काष्ठा latch_tree_node *ltn;
	पूर्णांक c;

	जबतक (node) अणु
		ltn = __lt_from_rb(node, idx);
		c = comp(key, ltn);

		अगर (c < 0)
			node = rcu_dereference_raw(node->rb_left);
		अन्यथा अगर (c > 0)
			node = rcu_dereference_raw(node->rb_right);
		अन्यथा
			वापस ltn;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * latch_tree_insert() - insert @node पूर्णांकo the trees @root
 * @node: nodes to insert
 * @root: trees to insert @node पूर्णांकo
 * @ops: चालकs defining the node order
 *
 * It inserts @node पूर्णांकo @root in an ordered fashion such that we can always
 * observe one complete tree. See the comment क्रम raw_ग_लिखो_seqcount_latch().
 *
 * The inserts use rcu_assign_poपूर्णांकer() to publish the element such that the
 * tree काष्ठाure is stored beक्रमe we can observe the new @node.
 *
 * All modअगरications (latch_tree_insert, latch_tree_हटाओ) are assumed to be
 * serialized.
 */
अटल __always_अंतरभूत व्योम
latch_tree_insert(काष्ठा latch_tree_node *node,
		  काष्ठा latch_tree_root *root,
		  स्थिर काष्ठा latch_tree_ops *ops)
अणु
	raw_ग_लिखो_seqcount_latch(&root->seq);
	__lt_insert(node, root, 0, ops->less);
	raw_ग_लिखो_seqcount_latch(&root->seq);
	__lt_insert(node, root, 1, ops->less);
पूर्ण

/**
 * latch_tree_erase() - हटाओs @node from the trees @root
 * @node: nodes to remote
 * @root: trees to हटाओ @node from
 * @ops: चालकs defining the node order
 *
 * Removes @node from the trees @root in an ordered fashion such that we can
 * always observe one complete tree. See the comment क्रम
 * raw_ग_लिखो_seqcount_latch().
 *
 * It is assumed that @node will observe one RCU quiescent state beक्रमe being
 * reused of मुक्तd.
 *
 * All modअगरications (latch_tree_insert, latch_tree_हटाओ) are assumed to be
 * serialized.
 */
अटल __always_अंतरभूत व्योम
latch_tree_erase(काष्ठा latch_tree_node *node,
		 काष्ठा latch_tree_root *root,
		 स्थिर काष्ठा latch_tree_ops *ops)
अणु
	raw_ग_लिखो_seqcount_latch(&root->seq);
	__lt_erase(node, root, 0);
	raw_ग_लिखो_seqcount_latch(&root->seq);
	__lt_erase(node, root, 1);
पूर्ण

/**
 * latch_tree_find() - find the node matching @key in the trees @root
 * @key: search key
 * @root: trees to search क्रम @key
 * @ops: चालकs defining the node order
 *
 * Does a lockless lookup in the trees @root क्रम the node matching @key.
 *
 * It is assumed that this is called जबतक holding the appropriate RCU पढ़ो
 * side lock.
 *
 * If the चालकs define a partial order on the elements (there are multiple
 * elements which have the same key value) it is undefined which of these
 * elements will be found. Nor is it possible to iterate the tree to find
 * further elements with the same key value.
 *
 * Returns: a poपूर्णांकer to the node matching @key or शून्य.
 */
अटल __always_अंतरभूत काष्ठा latch_tree_node *
latch_tree_find(व्योम *key, काष्ठा latch_tree_root *root,
		स्थिर काष्ठा latch_tree_ops *ops)
अणु
	काष्ठा latch_tree_node *node;
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = raw_पढ़ो_seqcount_latch(&root->seq);
		node = __lt_find(key, root, seq & 1, ops->comp);
	पूर्ण जबतक (पढ़ो_seqcount_latch_retry(&root->seq, seq));

	वापस node;
पूर्ण

#पूर्ण_अगर /* RB_TREE_LATCH_H */
