<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
  Red Black Trees
  (C) 1999  Andrea Arcangeli <andrea@suse.de>
  (C) 2002  David Woodhouse <dwmw2@infradead.org>
  (C) 2012  Michel Lespinasse <walken@google.com>


  linux/lib/rbtree.c
*/

#समावेश <linux/rbtree_augmented.h>
#समावेश <linux/export.h>

/*
 * red-black trees properties:  https://en.wikipedia.org/wiki/Rbtree
 *
 *  1) A node is either red or black
 *  2) The root is black
 *  3) All leaves (शून्य) are black
 *  4) Both children of every red node are black
 *  5) Every simple path from root to leaves contains the same number
 *     of black nodes.
 *
 *  4 and 5 give the O(log n) guarantee, since 4 implies you cannot have two
 *  consecutive red nodes in a path and every red node is thereक्रमe followed by
 *  a black. So अगर B is the number of black nodes on every simple path (as per
 *  5), then the दीर्घest possible path due to 4 is 2B.
 *
 *  We shall indicate color with हाल, where black nodes are upperहाल and red
 *  nodes will be lowerहाल. Unknown color nodes shall be drawn as red within
 *  parentheses and have some accompanying text comment.
 */

/*
 * Notes on lockless lookups:
 *
 * All stores to the tree काष्ठाure (rb_left and rb_right) must be करोne using
 * WRITE_ONCE(). And we must not inadvertently cause (temporary) loops in the
 * tree काष्ठाure as seen in program order.
 *
 * These two requirements will allow lockless iteration of the tree -- not
 * correct iteration mind you, tree rotations are not atomic so a lookup might
 * miss entire subtrees.
 *
 * But they करो guarantee that any such traversal will only see valid elements
 * and that it will indeed complete -- करोes not get stuck in a loop.
 *
 * It also guarantees that अगर the lookup वापसs an element it is the 'correct'
 * one. But not वापसing an element करोes _NOT_ mean it's not present.
 *
 * NOTE:
 *
 * Stores to __rb_parent_color are not important क्रम simple lookups so those
 * are left unकरोne as of now. Nor did I check क्रम loops involving parent
 * poपूर्णांकers.
 */

अटल अंतरभूत व्योम rb_set_black(काष्ठा rb_node *rb)
अणु
	rb->__rb_parent_color |= RB_BLACK;
पूर्ण

अटल अंतरभूत काष्ठा rb_node *rb_red_parent(काष्ठा rb_node *red)
अणु
	वापस (काष्ठा rb_node *)red->__rb_parent_color;
पूर्ण

/*
 * Helper function क्रम rotations:
 * - old's parent and color get asचिन्हित to new
 * - old माला_लो asचिन्हित new as a parent and 'color' as a color.
 */
अटल अंतरभूत व्योम
__rb_rotate_set_parents(काष्ठा rb_node *old, काष्ठा rb_node *new,
			काष्ठा rb_root *root, पूर्णांक color)
अणु
	काष्ठा rb_node *parent = rb_parent(old);
	new->__rb_parent_color = old->__rb_parent_color;
	rb_set_parent_color(old, new, color);
	__rb_change_child(old, new, parent, root);
पूर्ण

अटल __always_अंतरभूत व्योम
__rb_insert(काष्ठा rb_node *node, काष्ठा rb_root *root,
	    व्योम (*augment_rotate)(काष्ठा rb_node *old, काष्ठा rb_node *new))
अणु
	काष्ठा rb_node *parent = rb_red_parent(node), *gparent, *पंचांगp;

	जबतक (true) अणु
		/*
		 * Loop invariant: node is red.
		 */
		अगर (unlikely(!parent)) अणु
			/*
			 * The inserted node is root. Either this is the
			 * first node, or we recursed at Case 1 below and
			 * are no दीर्घer violating 4).
			 */
			rb_set_parent_color(node, शून्य, RB_BLACK);
			अवरोध;
		पूर्ण

		/*
		 * If there is a black parent, we are करोne.
		 * Otherwise, take some corrective action as,
		 * per 4), we करोn't want a red root or two
		 * consecutive red nodes.
		 */
		अगर(rb_is_black(parent))
			अवरोध;

		gparent = rb_red_parent(parent);

		पंचांगp = gparent->rb_right;
		अगर (parent != पंचांगp) अणु	/* parent == gparent->rb_left */
			अगर (पंचांगp && rb_is_red(पंचांगp)) अणु
				/*
				 * Case 1 - node's uncle is red (color flips).
				 *
				 *       G            g
				 *      / \          / \
				 *     p   u  -->   P   U
				 *    /            /
				 *   n            n
				 *
				 * However, since g's parent might be red, and
				 * 4) करोes not allow this, we need to recurse
				 * at g.
				 */
				rb_set_parent_color(पंचांगp, gparent, RB_BLACK);
				rb_set_parent_color(parent, gparent, RB_BLACK);
				node = gparent;
				parent = rb_parent(node);
				rb_set_parent_color(node, parent, RB_RED);
				जारी;
			पूर्ण

			पंचांगp = parent->rb_right;
			अगर (node == पंचांगp) अणु
				/*
				 * Case 2 - node's uncle is black and node is
				 * the parent's right child (left rotate at parent).
				 *
				 *      G             G
				 *     / \           / \
				 *    p   U  -->    n   U
				 *     \           /
				 *      n         p
				 *
				 * This still leaves us in violation of 4), the
				 * continuation पूर्णांकo Case 3 will fix that.
				 */
				पंचांगp = node->rb_left;
				WRITE_ONCE(parent->rb_right, पंचांगp);
				WRITE_ONCE(node->rb_left, parent);
				अगर (पंचांगp)
					rb_set_parent_color(पंचांगp, parent,
							    RB_BLACK);
				rb_set_parent_color(parent, node, RB_RED);
				augment_rotate(parent, node);
				parent = node;
				पंचांगp = node->rb_right;
			पूर्ण

			/*
			 * Case 3 - node's uncle is black and node is
			 * the parent's left child (right rotate at gparent).
			 *
			 *        G           P
			 *       / \         / \
			 *      p   U  -->  n   g
			 *     /                 \
			 *    n                   U
			 */
			WRITE_ONCE(gparent->rb_left, पंचांगp); /* == parent->rb_right */
			WRITE_ONCE(parent->rb_right, gparent);
			अगर (पंचांगp)
				rb_set_parent_color(पंचांगp, gparent, RB_BLACK);
			__rb_rotate_set_parents(gparent, parent, root, RB_RED);
			augment_rotate(gparent, parent);
			अवरोध;
		पूर्ण अन्यथा अणु
			पंचांगp = gparent->rb_left;
			अगर (पंचांगp && rb_is_red(पंचांगp)) अणु
				/* Case 1 - color flips */
				rb_set_parent_color(पंचांगp, gparent, RB_BLACK);
				rb_set_parent_color(parent, gparent, RB_BLACK);
				node = gparent;
				parent = rb_parent(node);
				rb_set_parent_color(node, parent, RB_RED);
				जारी;
			पूर्ण

			पंचांगp = parent->rb_left;
			अगर (node == पंचांगp) अणु
				/* Case 2 - right rotate at parent */
				पंचांगp = node->rb_right;
				WRITE_ONCE(parent->rb_left, पंचांगp);
				WRITE_ONCE(node->rb_right, parent);
				अगर (पंचांगp)
					rb_set_parent_color(पंचांगp, parent,
							    RB_BLACK);
				rb_set_parent_color(parent, node, RB_RED);
				augment_rotate(parent, node);
				parent = node;
				पंचांगp = node->rb_left;
			पूर्ण

			/* Case 3 - left rotate at gparent */
			WRITE_ONCE(gparent->rb_right, पंचांगp); /* == parent->rb_left */
			WRITE_ONCE(parent->rb_left, gparent);
			अगर (पंचांगp)
				rb_set_parent_color(पंचांगp, gparent, RB_BLACK);
			__rb_rotate_set_parents(gparent, parent, root, RB_RED);
			augment_rotate(gparent, parent);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Inline version क्रम rb_erase() use - we want to be able to अंतरभूत
 * and eliminate the dummy_rotate callback there
 */
अटल __always_अंतरभूत व्योम
____rb_erase_color(काष्ठा rb_node *parent, काष्ठा rb_root *root,
	व्योम (*augment_rotate)(काष्ठा rb_node *old, काष्ठा rb_node *new))
अणु
	काष्ठा rb_node *node = शून्य, *sibling, *पंचांगp1, *पंचांगp2;

	जबतक (true) अणु
		/*
		 * Loop invariants:
		 * - node is black (or शून्य on first iteration)
		 * - node is not the root (parent is not शून्य)
		 * - All leaf paths going through parent and node have a
		 *   black node count that is 1 lower than other leaf paths.
		 */
		sibling = parent->rb_right;
		अगर (node != sibling) अणु	/* node == parent->rb_left */
			अगर (rb_is_red(sibling)) अणु
				/*
				 * Case 1 - left rotate at parent
				 *
				 *     P               S
				 *    / \             / \
				 *   N   s    -->    p   Sr
				 *      / \         / \
				 *     Sl  Sr      N   Sl
				 */
				पंचांगp1 = sibling->rb_left;
				WRITE_ONCE(parent->rb_right, पंचांगp1);
				WRITE_ONCE(sibling->rb_left, parent);
				rb_set_parent_color(पंचांगp1, parent, RB_BLACK);
				__rb_rotate_set_parents(parent, sibling, root,
							RB_RED);
				augment_rotate(parent, sibling);
				sibling = पंचांगp1;
			पूर्ण
			पंचांगp1 = sibling->rb_right;
			अगर (!पंचांगp1 || rb_is_black(पंचांगp1)) अणु
				पंचांगp2 = sibling->rb_left;
				अगर (!पंचांगp2 || rb_is_black(पंचांगp2)) अणु
					/*
					 * Case 2 - sibling color flip
					 * (p could be either color here)
					 *
					 *    (p)           (p)
					 *    / \           / \
					 *   N   S    -->  N   s
					 *      / \           / \
					 *     Sl  Sr        Sl  Sr
					 *
					 * This leaves us violating 5) which
					 * can be fixed by flipping p to black
					 * अगर it was red, or by recursing at p.
					 * p is red when coming from Case 1.
					 */
					rb_set_parent_color(sibling, parent,
							    RB_RED);
					अगर (rb_is_red(parent))
						rb_set_black(parent);
					अन्यथा अणु
						node = parent;
						parent = rb_parent(node);
						अगर (parent)
							जारी;
					पूर्ण
					अवरोध;
				पूर्ण
				/*
				 * Case 3 - right rotate at sibling
				 * (p could be either color here)
				 *
				 *   (p)           (p)
				 *   / \           / \
				 *  N   S    -->  N   sl
				 *     / \             \
				 *    sl  Sr            S
				 *                       \
				 *                        Sr
				 *
				 * Note: p might be red, and then both
				 * p and sl are red after rotation(which
				 * अवरोधs property 4). This is fixed in
				 * Case 4 (in __rb_rotate_set_parents()
				 *         which set sl the color of p
				 *         and set p RB_BLACK)
				 *
				 *   (p)            (sl)
				 *   / \            /  \
				 *  N   sl   -->   P    S
				 *       \        /      \
				 *        S      N        Sr
				 *         \
				 *          Sr
				 */
				पंचांगp1 = पंचांगp2->rb_right;
				WRITE_ONCE(sibling->rb_left, पंचांगp1);
				WRITE_ONCE(पंचांगp2->rb_right, sibling);
				WRITE_ONCE(parent->rb_right, पंचांगp2);
				अगर (पंचांगp1)
					rb_set_parent_color(पंचांगp1, sibling,
							    RB_BLACK);
				augment_rotate(sibling, पंचांगp2);
				पंचांगp1 = sibling;
				sibling = पंचांगp2;
			पूर्ण
			/*
			 * Case 4 - left rotate at parent + color flips
			 * (p and sl could be either color here.
			 *  After rotation, p becomes black, s acquires
			 *  p's color, and sl keeps its color)
			 *
			 *      (p)             (s)
			 *      / \             / \
			 *     N   S     -->   P   Sr
			 *        / \         / \
			 *      (sl) sr      N  (sl)
			 */
			पंचांगp2 = sibling->rb_left;
			WRITE_ONCE(parent->rb_right, पंचांगp2);
			WRITE_ONCE(sibling->rb_left, parent);
			rb_set_parent_color(पंचांगp1, sibling, RB_BLACK);
			अगर (पंचांगp2)
				rb_set_parent(पंचांगp2, parent);
			__rb_rotate_set_parents(parent, sibling, root,
						RB_BLACK);
			augment_rotate(parent, sibling);
			अवरोध;
		पूर्ण अन्यथा अणु
			sibling = parent->rb_left;
			अगर (rb_is_red(sibling)) अणु
				/* Case 1 - right rotate at parent */
				पंचांगp1 = sibling->rb_right;
				WRITE_ONCE(parent->rb_left, पंचांगp1);
				WRITE_ONCE(sibling->rb_right, parent);
				rb_set_parent_color(पंचांगp1, parent, RB_BLACK);
				__rb_rotate_set_parents(parent, sibling, root,
							RB_RED);
				augment_rotate(parent, sibling);
				sibling = पंचांगp1;
			पूर्ण
			पंचांगp1 = sibling->rb_left;
			अगर (!पंचांगp1 || rb_is_black(पंचांगp1)) अणु
				पंचांगp2 = sibling->rb_right;
				अगर (!पंचांगp2 || rb_is_black(पंचांगp2)) अणु
					/* Case 2 - sibling color flip */
					rb_set_parent_color(sibling, parent,
							    RB_RED);
					अगर (rb_is_red(parent))
						rb_set_black(parent);
					अन्यथा अणु
						node = parent;
						parent = rb_parent(node);
						अगर (parent)
							जारी;
					पूर्ण
					अवरोध;
				पूर्ण
				/* Case 3 - left rotate at sibling */
				पंचांगp1 = पंचांगp2->rb_left;
				WRITE_ONCE(sibling->rb_right, पंचांगp1);
				WRITE_ONCE(पंचांगp2->rb_left, sibling);
				WRITE_ONCE(parent->rb_left, पंचांगp2);
				अगर (पंचांगp1)
					rb_set_parent_color(पंचांगp1, sibling,
							    RB_BLACK);
				augment_rotate(sibling, पंचांगp2);
				पंचांगp1 = sibling;
				sibling = पंचांगp2;
			पूर्ण
			/* Case 4 - right rotate at parent + color flips */
			पंचांगp2 = sibling->rb_right;
			WRITE_ONCE(parent->rb_left, पंचांगp2);
			WRITE_ONCE(sibling->rb_right, parent);
			rb_set_parent_color(पंचांगp1, sibling, RB_BLACK);
			अगर (पंचांगp2)
				rb_set_parent(पंचांगp2, parent);
			__rb_rotate_set_parents(parent, sibling, root,
						RB_BLACK);
			augment_rotate(parent, sibling);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Non-अंतरभूत version क्रम rb_erase_augmented() use */
व्योम __rb_erase_color(काष्ठा rb_node *parent, काष्ठा rb_root *root,
	व्योम (*augment_rotate)(काष्ठा rb_node *old, काष्ठा rb_node *new))
अणु
	____rb_erase_color(parent, root, augment_rotate);
पूर्ण

/*
 * Non-augmented rbtree manipulation functions.
 *
 * We use dummy augmented callbacks here, and have the compiler optimize them
 * out of the rb_insert_color() and rb_erase() function definitions.
 */

अटल अंतरभूत व्योम dummy_propagate(काष्ठा rb_node *node, काष्ठा rb_node *stop) अणुपूर्ण
अटल अंतरभूत व्योम dummy_copy(काष्ठा rb_node *old, काष्ठा rb_node *new) अणुपूर्ण
अटल अंतरभूत व्योम dummy_rotate(काष्ठा rb_node *old, काष्ठा rb_node *new) अणुपूर्ण

अटल स्थिर काष्ठा rb_augment_callbacks dummy_callbacks = अणु
	.propagate = dummy_propagate,
	.copy = dummy_copy,
	.rotate = dummy_rotate
पूर्ण;

व्योम rb_insert_color(काष्ठा rb_node *node, काष्ठा rb_root *root)
अणु
	__rb_insert(node, root, dummy_rotate);
पूर्ण

व्योम rb_erase(काष्ठा rb_node *node, काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *rebalance;
	rebalance = __rb_erase_augmented(node, root, &dummy_callbacks);
	अगर (rebalance)
		____rb_erase_color(rebalance, root, dummy_rotate);
पूर्ण

/*
 * Augmented rbtree manipulation functions.
 *
 * This instantiates the same __always_अंतरभूत functions as in the non-augmented
 * हाल, but this समय with user-defined callbacks.
 */

व्योम __rb_insert_augmented(काष्ठा rb_node *node, काष्ठा rb_root *root,
	व्योम (*augment_rotate)(काष्ठा rb_node *old, काष्ठा rb_node *new))
अणु
	__rb_insert(node, root, augment_rotate);
पूर्ण

/*
 * This function वापसs the first node (in sort order) of the tree.
 */
काष्ठा rb_node *rb_first(स्थिर काष्ठा rb_root *root)
अणु
	काष्ठा rb_node	*n;

	n = root->rb_node;
	अगर (!n)
		वापस शून्य;
	जबतक (n->rb_left)
		n = n->rb_left;
	वापस n;
पूर्ण

काष्ठा rb_node *rb_last(स्थिर काष्ठा rb_root *root)
अणु
	काष्ठा rb_node	*n;

	n = root->rb_node;
	अगर (!n)
		वापस शून्य;
	जबतक (n->rb_right)
		n = n->rb_right;
	वापस n;
पूर्ण

काष्ठा rb_node *rb_next(स्थिर काष्ठा rb_node *node)
अणु
	काष्ठा rb_node *parent;

	अगर (RB_EMPTY_NODE(node))
		वापस शून्य;

	/*
	 * If we have a right-hand child, go करोwn and then left as far
	 * as we can.
	 */
	अगर (node->rb_right) अणु
		node = node->rb_right;
		जबतक (node->rb_left)
			node = node->rb_left;
		वापस (काष्ठा rb_node *)node;
	पूर्ण

	/*
	 * No right-hand children. Everything करोwn and left is smaller than us,
	 * so any 'next' node must be in the general direction of our parent.
	 * Go up the tree; any समय the ancestor is a right-hand child of its
	 * parent, keep going up. First समय it's a left-hand child of its
	 * parent, said parent is our 'next' node.
	 */
	जबतक ((parent = rb_parent(node)) && node == parent->rb_right)
		node = parent;

	वापस parent;
पूर्ण

काष्ठा rb_node *rb_prev(स्थिर काष्ठा rb_node *node)
अणु
	काष्ठा rb_node *parent;

	अगर (RB_EMPTY_NODE(node))
		वापस शून्य;

	/*
	 * If we have a left-hand child, go करोwn and then right as far
	 * as we can.
	 */
	अगर (node->rb_left) अणु
		node = node->rb_left;
		जबतक (node->rb_right)
			node = node->rb_right;
		वापस (काष्ठा rb_node *)node;
	पूर्ण

	/*
	 * No left-hand children. Go up till we find an ancestor which
	 * is a right-hand child of its parent.
	 */
	जबतक ((parent = rb_parent(node)) && node == parent->rb_left)
		node = parent;

	वापस parent;
पूर्ण

व्योम rb_replace_node(काष्ठा rb_node *victim, काष्ठा rb_node *new,
		     काष्ठा rb_root *root)
अणु
	काष्ठा rb_node *parent = rb_parent(victim);

	/* Copy the poपूर्णांकers/colour from the victim to the replacement */
	*new = *victim;

	/* Set the surrounding nodes to poपूर्णांक to the replacement */
	अगर (victim->rb_left)
		rb_set_parent(victim->rb_left, new);
	अगर (victim->rb_right)
		rb_set_parent(victim->rb_right, new);
	__rb_change_child(victim, new, parent, root);
पूर्ण

अटल काष्ठा rb_node *rb_left_deepest_node(स्थिर काष्ठा rb_node *node)
अणु
	क्रम (;;) अणु
		अगर (node->rb_left)
			node = node->rb_left;
		अन्यथा अगर (node->rb_right)
			node = node->rb_right;
		अन्यथा
			वापस (काष्ठा rb_node *)node;
	पूर्ण
पूर्ण

काष्ठा rb_node *rb_next_postorder(स्थिर काष्ठा rb_node *node)
अणु
	स्थिर काष्ठा rb_node *parent;
	अगर (!node)
		वापस शून्य;
	parent = rb_parent(node);

	/* If we're sitting on node, we've alपढ़ोy seen our children */
	अगर (parent && node == parent->rb_left && parent->rb_right) अणु
		/* If we are the parent's left node, go to the parent's right
		 * node then all the way करोwn to the left */
		वापस rb_left_deepest_node(parent->rb_right);
	पूर्ण अन्यथा
		/* Otherwise we are the parent's right node, and the parent
		 * should be next */
		वापस (काष्ठा rb_node *)parent;
पूर्ण

काष्ठा rb_node *rb_first_postorder(स्थिर काष्ठा rb_root *root)
अणु
	अगर (!root->rb_node)
		वापस शून्य;

	वापस rb_left_deepest_node(root->rb_node);
पूर्ण
