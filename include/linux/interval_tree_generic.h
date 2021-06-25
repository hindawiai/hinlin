<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
  Interval Trees
  (C) 2012  Michel Lespinasse <walken@google.com>


  include/linux/पूर्णांकerval_tree_generic.h
*/

#समावेश <linux/rbtree_augmented.h>

/*
 * Template क्रम implementing पूर्णांकerval trees
 *
 * ITSTRUCT:   काष्ठा type of the पूर्णांकerval tree nodes
 * ITRB:       name of काष्ठा rb_node field within ITSTRUCT
 * ITTYPE:     type of the पूर्णांकerval endpoपूर्णांकs
 * ITSUBTREE:  name of ITTYPE field within ITSTRUCT holding last-in-subtree
 * ITSTART(n): start endpoपूर्णांक of ITSTRUCT node n
 * ITLAST(n):  last endpoपूर्णांक of ITSTRUCT node n
 * ITSTATIC:   'static' or empty
 * ITPREFIX:   prefix to use क्रम the अंतरभूत tree definitions
 *
 * Note - beक्रमe using this, please consider अगर generic version
 * (पूर्णांकerval_tree.h) would work क्रम you...
 */

#घोषणा INTERVAL_TREE_DEFINE(ITSTRUCT, ITRB, ITTYPE, ITSUBTREE,		      \
			     ITSTART, ITLAST, ITSTATIC, ITPREFIX)	      \
									      \
/* Callbacks क्रम augmented rbtree insert and हटाओ */			      \
									      \
RB_DECLARE_CALLBACKS_MAX(अटल, ITPREFIX ## _augment,			      \
			 ITSTRUCT, ITRB, ITTYPE, ITSUBTREE, ITLAST)	      \
									      \
/* Insert / हटाओ पूर्णांकerval nodes from the tree */			      \
									      \
ITSTATIC व्योम ITPREFIX ## _insert(ITSTRUCT *node,			      \
				  काष्ठा rb_root_cached *root)	 	      \
अणु									      \
	काष्ठा rb_node **link = &root->rb_root.rb_node, *rb_parent = शून्य;    \
	ITTYPE start = ITSTART(node), last = ITLAST(node);		      \
	ITSTRUCT *parent;						      \
	bool lefपंचांगost = true;						      \
									      \
	जबतक (*link) अणु							      \
		rb_parent = *link;					      \
		parent = rb_entry(rb_parent, ITSTRUCT, ITRB);		      \
		अगर (parent->ITSUBTREE < last)				      \
			parent->ITSUBTREE = last;			      \
		अगर (start < ITSTART(parent))				      \
			link = &parent->ITRB.rb_left;			      \
		अन्यथा अणु							      \
			link = &parent->ITRB.rb_right;			      \
			lefपंचांगost = false;				      \
		पूर्ण							      \
	पूर्ण								      \
									      \
	node->ITSUBTREE = last;						      \
	rb_link_node(&node->ITRB, rb_parent, link);			      \
	rb_insert_augmented_cached(&node->ITRB, root,			      \
				   lefपंचांगost, &ITPREFIX ## _augment);	      \
पूर्ण									      \
									      \
ITSTATIC व्योम ITPREFIX ## _हटाओ(ITSTRUCT *node,			      \
				  काष्ठा rb_root_cached *root)		      \
अणु									      \
	rb_erase_augmented_cached(&node->ITRB, root, &ITPREFIX ## _augment);  \
पूर्ण									      \
									      \
/*									      \
 * Iterate over पूर्णांकervals पूर्णांकersecting [start;last]			      \
 *									      \
 * Note that a node's पूर्णांकerval पूर्णांकersects [start;last] अगरf:		      \
 *   Cond1: ITSTART(node) <= last					      \
 * and									      \
 *   Cond2: start <= ITLAST(node)					      \
 */									      \
									      \
अटल ITSTRUCT *							      \
ITPREFIX ## _subtree_search(ITSTRUCT *node, ITTYPE start, ITTYPE last)	      \
अणु									      \
	जबतक (true) अणु							      \
		/*							      \
		 * Loop invariant: start <= node->ITSUBTREE		      \
		 * (Cond2 is satisfied by one of the subtree nodes)	      \
		 */							      \
		अगर (node->ITRB.rb_left) अणु				      \
			ITSTRUCT *left = rb_entry(node->ITRB.rb_left,	      \
						  ITSTRUCT, ITRB);	      \
			अगर (start <= left->ITSUBTREE) अणु			      \
				/*					      \
				 * Some nodes in left subtree satisfy Cond2.  \
				 * Iterate to find the lefपंचांगost such node N.  \
				 * If it also satisfies Cond1, that's the     \
				 * match we are looking क्रम. Otherwise, there \
				 * is no matching पूर्णांकerval as nodes to the    \
				 * right of N can't satisfy Cond1 either.     \
				 */					      \
				node = left;				      \
				जारी;				      \
			पूर्ण						      \
		पूर्ण							      \
		अगर (ITSTART(node) <= last) अणु		/* Cond1 */	      \
			अगर (start <= ITLAST(node))	/* Cond2 */	      \
				वापस node;	/* node is lefपंचांगost match */  \
			अगर (node->ITRB.rb_right) अणु			      \
				node = rb_entry(node->ITRB.rb_right,	      \
						ITSTRUCT, ITRB);	      \
				अगर (start <= node->ITSUBTREE)		      \
					जारी;			      \
			पूर्ण						      \
		पूर्ण							      \
		वापस शून्य;	/* No match */				      \
	पूर्ण								      \
पूर्ण									      \
									      \
ITSTATIC ITSTRUCT *							      \
ITPREFIX ## _iter_first(काष्ठा rb_root_cached *root,			      \
			ITTYPE start, ITTYPE last)			      \
अणु									      \
	ITSTRUCT *node, *lefपंचांगost;					      \
									      \
	अगर (!root->rb_root.rb_node)					      \
		वापस शून्य;						      \
									      \
	/*								      \
	 * Fastpath range पूर्णांकersection/overlap between A: [a0, a1] and	      \
	 * B: [b0, b1] is given by:					      \
	 *								      \
	 *         a0 <= b1 && b0 <= a1					      \
	 *								      \
	 *  ... where A holds the lock range and B holds the smallest	      \
	 * 'start' and largest 'last' in the tree. For the later, we	      \
	 * rely on the root node, which by augmented पूर्णांकerval tree	      \
	 * property, holds the largest value in its last-in-subtree.	      \
	 * This allows mitigating some of the tree walk overhead क्रम	      \
	 * क्रम non-पूर्णांकersecting ranges, मुख्यtained and consulted in O(1).     \
	 */								      \
	node = rb_entry(root->rb_root.rb_node, ITSTRUCT, ITRB);		      \
	अगर (node->ITSUBTREE < start)					      \
		वापस शून्य;						      \
									      \
	lefपंचांगost = rb_entry(root->rb_lefपंचांगost, ITSTRUCT, ITRB);		      \
	अगर (ITSTART(lefपंचांगost) > last)					      \
		वापस शून्य;						      \
									      \
	वापस ITPREFIX ## _subtree_search(node, start, last);		      \
पूर्ण									      \
									      \
ITSTATIC ITSTRUCT *							      \
ITPREFIX ## _iter_next(ITSTRUCT *node, ITTYPE start, ITTYPE last)	      \
अणु									      \
	काष्ठा rb_node *rb = node->ITRB.rb_right, *prev;		      \
									      \
	जबतक (true) अणु							      \
		/*							      \
		 * Loop invariants:					      \
		 *   Cond1: ITSTART(node) <= last			      \
		 *   rb == node->ITRB.rb_right				      \
		 *							      \
		 * First, search right subtree अगर suitable		      \
		 */							      \
		अगर (rb) अणु						      \
			ITSTRUCT *right = rb_entry(rb, ITSTRUCT, ITRB);	      \
			अगर (start <= right->ITSUBTREE)			      \
				वापस ITPREFIX ## _subtree_search(right,     \
								start, last); \
		पूर्ण							      \
									      \
		/* Move up the tree until we come from a node's left child */ \
		करो अणु							      \
			rb = rb_parent(&node->ITRB);			      \
			अगर (!rb)					      \
				वापस शून्य;				      \
			prev = &node->ITRB;				      \
			node = rb_entry(rb, ITSTRUCT, ITRB);		      \
			rb = node->ITRB.rb_right;			      \
		पूर्ण जबतक (prev == rb);					      \
									      \
		/* Check अगर the node पूर्णांकersects [start;last] */		      \
		अगर (last < ITSTART(node))		/* !Cond1 */	      \
			वापस शून्य;					      \
		अन्यथा अगर (start <= ITLAST(node))		/* Cond2 */	      \
			वापस node;					      \
	पूर्ण								      \
पूर्ण
