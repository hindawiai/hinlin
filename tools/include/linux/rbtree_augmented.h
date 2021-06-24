<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
  Red Black Trees
  (C) 1999  Andrea Arcangeli <andrea@suse.de>
  (C) 2002  David Woodhouse <dwmw2@infradead.org>
  (C) 2012  Michel Lespinasse <walken@google.com>


  tools/linux/include/linux/rbtree_augmented.h

  Copied from:
  linux/include/linux/rbtree_augmented.h
*/

#अगर_अघोषित _TOOLS_LINUX_RBTREE_AUGMENTED_H
#घोषणा _TOOLS_LINUX_RBTREE_AUGMENTED_H

#समावेश <linux/compiler.h>
#समावेश <linux/rbtree.h>

/*
 * Please note - only काष्ठा rb_augment_callbacks and the prototypes क्रम
 * rb_insert_augmented() and rb_erase_augmented() are पूर्णांकended to be खुला.
 * The rest are implementation details you are not expected to depend on.
 *
 * See Documentation/core-api/rbtree.rst क्रम करोcumentation and samples.
 */

काष्ठा rb_augment_callbacks अणु
	व्योम (*propagate)(काष्ठा rb_node *node, काष्ठा rb_node *stop);
	व्योम (*copy)(काष्ठा rb_node *old, काष्ठा rb_node *new);
	व्योम (*rotate)(काष्ठा rb_node *old, काष्ठा rb_node *new);
पूर्ण;

बाह्य व्योम __rb_insert_augmented(काष्ठा rb_node *node, काष्ठा rb_root *root,
	व्योम (*augment_rotate)(काष्ठा rb_node *old, काष्ठा rb_node *new));

/*
 * Fixup the rbtree and update the augmented inक्रमmation when rebalancing.
 *
 * On insertion, the user must update the augmented inक्रमmation on the path
 * leading to the inserted node, then call rb_link_node() as usual and
 * rb_insert_augmented() instead of the usual rb_insert_color() call.
 * If rb_insert_augmented() rebalances the rbtree, it will callback पूर्णांकo
 * a user provided function to update the augmented inक्रमmation on the
 * affected subtrees.
 */
अटल अंतरभूत व्योम
rb_insert_augmented(काष्ठा rb_node *node, काष्ठा rb_root *root,
		    स्थिर काष्ठा rb_augment_callbacks *augment)
अणु
	__rb_insert_augmented(node, root, augment->rotate);
पूर्ण

अटल अंतरभूत व्योम
rb_insert_augmented_cached(काष्ठा rb_node *node,
			   काष्ठा rb_root_cached *root, bool newleft,
			   स्थिर काष्ठा rb_augment_callbacks *augment)
अणु
	अगर (newleft)
		root->rb_lefपंचांगost = node;
	rb_insert_augmented(node, &root->rb_root, augment);
पूर्ण

/*
 * Template क्रम declaring augmented rbtree callbacks (generic हाल)
 *
 * RBSTATIC:    'static' or empty
 * RBNAME:      name of the rb_augment_callbacks काष्ठाure
 * RBSTRUCT:    काष्ठा type of the tree nodes
 * RBFIELD:     name of काष्ठा rb_node field within RBSTRUCT
 * RBAUGMENTED: name of field within RBSTRUCT holding data क्रम subtree
 * RBCOMPUTE:   name of function that recomputes the RBAUGMENTED data
 */

#घोषणा RB_DECLARE_CALLBACKS(RBSTATIC, RBNAME,				\
			     RBSTRUCT, RBFIELD, RBAUGMENTED, RBCOMPUTE)	\
अटल अंतरभूत व्योम							\
RBNAME ## _propagate(काष्ठा rb_node *rb, काष्ठा rb_node *stop)		\
अणु									\
	जबतक (rb != stop) अणु						\
		RBSTRUCT *node = rb_entry(rb, RBSTRUCT, RBFIELD);	\
		अगर (RBCOMPUTE(node, true))				\
			अवरोध;						\
		rb = rb_parent(&node->RBFIELD);				\
	पूर्ण								\
पूर्ण									\
अटल अंतरभूत व्योम							\
RBNAME ## _copy(काष्ठा rb_node *rb_old, काष्ठा rb_node *rb_new)		\
अणु									\
	RBSTRUCT *old = rb_entry(rb_old, RBSTRUCT, RBFIELD);		\
	RBSTRUCT *new = rb_entry(rb_new, RBSTRUCT, RBFIELD);		\
	new->RBAUGMENTED = old->RBAUGMENTED;				\
पूर्ण									\
अटल व्योम								\
RBNAME ## _rotate(काष्ठा rb_node *rb_old, काष्ठा rb_node *rb_new)	\
अणु									\
	RBSTRUCT *old = rb_entry(rb_old, RBSTRUCT, RBFIELD);		\
	RBSTRUCT *new = rb_entry(rb_new, RBSTRUCT, RBFIELD);		\
	new->RBAUGMENTED = old->RBAUGMENTED;				\
	RBCOMPUTE(old, false);						\
पूर्ण									\
RBSTATIC स्थिर काष्ठा rb_augment_callbacks RBNAME = अणु			\
	.propagate = RBNAME ## _propagate,				\
	.copy = RBNAME ## _copy,					\
	.rotate = RBNAME ## _rotate					\
पूर्ण;

/*
 * Template क्रम declaring augmented rbtree callbacks,
 * computing RBAUGMENTED scalar as max(RBCOMPUTE(node)) क्रम all subtree nodes.
 *
 * RBSTATIC:    'static' or empty
 * RBNAME:      name of the rb_augment_callbacks काष्ठाure
 * RBSTRUCT:    काष्ठा type of the tree nodes
 * RBFIELD:     name of काष्ठा rb_node field within RBSTRUCT
 * RBTYPE:      type of the RBAUGMENTED field
 * RBAUGMENTED: name of RBTYPE field within RBSTRUCT holding data क्रम subtree
 * RBCOMPUTE:   name of function that वापसs the per-node RBTYPE scalar
 */

#घोषणा RB_DECLARE_CALLBACKS_MAX(RBSTATIC, RBNAME, RBSTRUCT, RBFIELD,	      \
				 RBTYPE, RBAUGMENTED, RBCOMPUTE)	      \
अटल अंतरभूत bool RBNAME ## _compute_max(RBSTRUCT *node, bool निकास)	      \
अणु									      \
	RBSTRUCT *child;						      \
	RBTYPE max = RBCOMPUTE(node);					      \
	अगर (node->RBFIELD.rb_left) अणु					      \
		child = rb_entry(node->RBFIELD.rb_left, RBSTRUCT, RBFIELD);   \
		अगर (child->RBAUGMENTED > max)				      \
			max = child->RBAUGMENTED;			      \
	पूर्ण								      \
	अगर (node->RBFIELD.rb_right) अणु					      \
		child = rb_entry(node->RBFIELD.rb_right, RBSTRUCT, RBFIELD);  \
		अगर (child->RBAUGMENTED > max)				      \
			max = child->RBAUGMENTED;			      \
	पूर्ण								      \
	अगर (निकास && node->RBAUGMENTED == max)				      \
		वापस true;						      \
	node->RBAUGMENTED = max;					      \
	वापस false;							      \
पूर्ण									      \
RB_DECLARE_CALLBACKS(RBSTATIC, RBNAME,					      \
		     RBSTRUCT, RBFIELD, RBAUGMENTED, RBNAME ## _compute_max)


#घोषणा	RB_RED		0
#घोषणा	RB_BLACK	1

#घोषणा __rb_parent(pc)    ((काष्ठा rb_node *)(pc & ~3))

#घोषणा __rb_color(pc)     ((pc) & 1)
#घोषणा __rb_is_black(pc)  __rb_color(pc)
#घोषणा __rb_is_red(pc)    (!__rb_color(pc))
#घोषणा rb_color(rb)       __rb_color((rb)->__rb_parent_color)
#घोषणा rb_is_red(rb)      __rb_is_red((rb)->__rb_parent_color)
#घोषणा rb_is_black(rb)    __rb_is_black((rb)->__rb_parent_color)

अटल अंतरभूत व्योम rb_set_parent(काष्ठा rb_node *rb, काष्ठा rb_node *p)
अणु
	rb->__rb_parent_color = rb_color(rb) | (अचिन्हित दीर्घ)p;
पूर्ण

अटल अंतरभूत व्योम rb_set_parent_color(काष्ठा rb_node *rb,
				       काष्ठा rb_node *p, पूर्णांक color)
अणु
	rb->__rb_parent_color = (अचिन्हित दीर्घ)p | color;
पूर्ण

अटल अंतरभूत व्योम
__rb_change_child(काष्ठा rb_node *old, काष्ठा rb_node *new,
		  काष्ठा rb_node *parent, काष्ठा rb_root *root)
अणु
	अगर (parent) अणु
		अगर (parent->rb_left == old)
			WRITE_ONCE(parent->rb_left, new);
		अन्यथा
			WRITE_ONCE(parent->rb_right, new);
	पूर्ण अन्यथा
		WRITE_ONCE(root->rb_node, new);
पूर्ण

बाह्य व्योम __rb_erase_color(काष्ठा rb_node *parent, काष्ठा rb_root *root,
	व्योम (*augment_rotate)(काष्ठा rb_node *old, काष्ठा rb_node *new));

अटल __always_अंतरभूत काष्ठा rb_node *
__rb_erase_augmented(काष्ठा rb_node *node, काष्ठा rb_root *root,
		     स्थिर काष्ठा rb_augment_callbacks *augment)
अणु
	काष्ठा rb_node *child = node->rb_right;
	काष्ठा rb_node *पंचांगp = node->rb_left;
	काष्ठा rb_node *parent, *rebalance;
	अचिन्हित दीर्घ pc;

	अगर (!पंचांगp) अणु
		/*
		 * Case 1: node to erase has no more than 1 child (easy!)
		 *
		 * Note that अगर there is one child it must be red due to 5)
		 * and node must be black due to 4). We adjust colors locally
		 * so as to bypass __rb_erase_color() later on.
		 */
		pc = node->__rb_parent_color;
		parent = __rb_parent(pc);
		__rb_change_child(node, child, parent, root);
		अगर (child) अणु
			child->__rb_parent_color = pc;
			rebalance = शून्य;
		पूर्ण अन्यथा
			rebalance = __rb_is_black(pc) ? parent : शून्य;
		पंचांगp = parent;
	पूर्ण अन्यथा अगर (!child) अणु
		/* Still हाल 1, but this समय the child is node->rb_left */
		पंचांगp->__rb_parent_color = pc = node->__rb_parent_color;
		parent = __rb_parent(pc);
		__rb_change_child(node, पंचांगp, parent, root);
		rebalance = शून्य;
		पंचांगp = parent;
	पूर्ण अन्यथा अणु
		काष्ठा rb_node *successor = child, *child2;

		पंचांगp = child->rb_left;
		अगर (!पंचांगp) अणु
			/*
			 * Case 2: node's successor is its right child
			 *
			 *    (n)          (s)
			 *    / \          / \
			 *  (x) (s)  ->  (x) (c)
			 *        \
			 *        (c)
			 */
			parent = successor;
			child2 = successor->rb_right;

			augment->copy(node, successor);
		पूर्ण अन्यथा अणु
			/*
			 * Case 3: node's successor is lefपंचांगost under
			 * node's right child subtree
			 *
			 *    (n)          (s)
			 *    / \          / \
			 *  (x) (y)  ->  (x) (y)
			 *      /            /
			 *    (p)          (p)
			 *    /            /
			 *  (s)          (c)
			 *    \
			 *    (c)
			 */
			करो अणु
				parent = successor;
				successor = पंचांगp;
				पंचांगp = पंचांगp->rb_left;
			पूर्ण जबतक (पंचांगp);
			child2 = successor->rb_right;
			WRITE_ONCE(parent->rb_left, child2);
			WRITE_ONCE(successor->rb_right, child);
			rb_set_parent(child, successor);

			augment->copy(node, successor);
			augment->propagate(parent, successor);
		पूर्ण

		पंचांगp = node->rb_left;
		WRITE_ONCE(successor->rb_left, पंचांगp);
		rb_set_parent(पंचांगp, successor);

		pc = node->__rb_parent_color;
		पंचांगp = __rb_parent(pc);
		__rb_change_child(node, successor, पंचांगp, root);

		अगर (child2) अणु
			successor->__rb_parent_color = pc;
			rb_set_parent_color(child2, parent, RB_BLACK);
			rebalance = शून्य;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ pc2 = successor->__rb_parent_color;
			successor->__rb_parent_color = pc;
			rebalance = __rb_is_black(pc2) ? parent : शून्य;
		पूर्ण
		पंचांगp = successor;
	पूर्ण

	augment->propagate(पंचांगp, शून्य);
	वापस rebalance;
पूर्ण

अटल __always_अंतरभूत व्योम
rb_erase_augmented(काष्ठा rb_node *node, काष्ठा rb_root *root,
		   स्थिर काष्ठा rb_augment_callbacks *augment)
अणु
	काष्ठा rb_node *rebalance = __rb_erase_augmented(node, root, augment);
	अगर (rebalance)
		__rb_erase_color(rebalance, root, augment->rotate);
पूर्ण

अटल __always_अंतरभूत व्योम
rb_erase_augmented_cached(काष्ठा rb_node *node, काष्ठा rb_root_cached *root,
			  स्थिर काष्ठा rb_augment_callbacks *augment)
अणु
	अगर (root->rb_lefपंचांगost == node)
		root->rb_lefपंचांगost = rb_next(node);
	rb_erase_augmented(node, &root->rb_root, augment);
पूर्ण

#पूर्ण_अगर /* _TOOLS_LINUX_RBTREE_AUGMENTED_H */
