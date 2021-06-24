<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
  Red Black Trees
  (C) 1999  Andrea Arcangeli <andrea@suse.de>
  

  linux/include/linux/rbtree.h

  To use rbtrees you'll have to implement your own insert and search cores.
  This will aव्योम us to use callbacks and to drop drammatically perक्रमmances.
  I know it's not the cleaner way,  but in C (not in C++) to get
  perक्रमmances and genericity...

  See Documentation/core-api/rbtree.rst क्रम करोcumentation and samples.
*/

#अगर_अघोषित	_LINUX_RBTREE_H
#घोषणा	_LINUX_RBTREE_H

#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/rcupdate.h>

काष्ठा rb_node अणु
	अचिन्हित दीर्घ  __rb_parent_color;
	काष्ठा rb_node *rb_right;
	काष्ठा rb_node *rb_left;
पूर्ण __attribute__((aligned(माप(दीर्घ))));
    /* The alignment might seem poपूर्णांकless, but allegedly CRIS needs it */

काष्ठा rb_root अणु
	काष्ठा rb_node *rb_node;
पूर्ण;

#घोषणा rb_parent(r)   ((काष्ठा rb_node *)((r)->__rb_parent_color & ~3))

#घोषणा RB_ROOT	(काष्ठा rb_root) अणु शून्य, पूर्ण
#घोषणा	rb_entry(ptr, type, member) container_of(ptr, type, member)

#घोषणा RB_EMPTY_ROOT(root)  (READ_ONCE((root)->rb_node) == शून्य)

/* 'empty' nodes are nodes that are known not to be inserted in an rbtree */
#घोषणा RB_EMPTY_NODE(node)  \
	((node)->__rb_parent_color == (अचिन्हित दीर्घ)(node))
#घोषणा RB_CLEAR_NODE(node)  \
	((node)->__rb_parent_color = (अचिन्हित दीर्घ)(node))


बाह्य व्योम rb_insert_color(काष्ठा rb_node *, काष्ठा rb_root *);
बाह्य व्योम rb_erase(काष्ठा rb_node *, काष्ठा rb_root *);


/* Find logical next and previous nodes in a tree */
बाह्य काष्ठा rb_node *rb_next(स्थिर काष्ठा rb_node *);
बाह्य काष्ठा rb_node *rb_prev(स्थिर काष्ठा rb_node *);
बाह्य काष्ठा rb_node *rb_first(स्थिर काष्ठा rb_root *);
बाह्य काष्ठा rb_node *rb_last(स्थिर काष्ठा rb_root *);

/* Postorder iteration - always visit the parent after its children */
बाह्य काष्ठा rb_node *rb_first_postorder(स्थिर काष्ठा rb_root *);
बाह्य काष्ठा rb_node *rb_next_postorder(स्थिर काष्ठा rb_node *);

/* Fast replacement of a single node without हटाओ/rebalance/add/rebalance */
बाह्य व्योम rb_replace_node(काष्ठा rb_node *victim, काष्ठा rb_node *new,
			    काष्ठा rb_root *root);
बाह्य व्योम rb_replace_node_rcu(काष्ठा rb_node *victim, काष्ठा rb_node *new,
				काष्ठा rb_root *root);

अटल अंतरभूत व्योम rb_link_node(काष्ठा rb_node *node, काष्ठा rb_node *parent,
				काष्ठा rb_node **rb_link)
अणु
	node->__rb_parent_color = (अचिन्हित दीर्घ)parent;
	node->rb_left = node->rb_right = शून्य;

	*rb_link = node;
पूर्ण

अटल अंतरभूत व्योम rb_link_node_rcu(काष्ठा rb_node *node, काष्ठा rb_node *parent,
				    काष्ठा rb_node **rb_link)
अणु
	node->__rb_parent_color = (अचिन्हित दीर्घ)parent;
	node->rb_left = node->rb_right = शून्य;

	rcu_assign_poपूर्णांकer(*rb_link, node);
पूर्ण

#घोषणा rb_entry_safe(ptr, type, member) \
	(अणु typeof(ptr) ____ptr = (ptr); \
	   ____ptr ? rb_entry(____ptr, type, member) : शून्य; \
	पूर्ण)

/**
 * rbtree_postorder_क्रम_each_entry_safe - iterate in post-order over rb_root of
 * given type allowing the backing memory of @pos to be invalidated
 *
 * @pos:	the 'type *' to use as a loop cursor.
 * @n:		another 'type *' to use as temporary storage
 * @root:	'rb_root *' of the rbtree.
 * @field:	the name of the rb_node field within 'type'.
 *
 * rbtree_postorder_क्रम_each_entry_safe() provides a similar guarantee as
 * list_क्रम_each_entry_safe() and allows the iteration to जारी independent
 * of changes to @pos by the body of the loop.
 *
 * Note, however, that it cannot handle other modअगरications that re-order the
 * rbtree it is iterating over. This includes calling rb_erase() on @pos, as
 * rb_erase() may rebalance the tree, causing us to miss some nodes.
 */
#घोषणा rbtree_postorder_क्रम_each_entry_safe(pos, n, root, field) \
	क्रम (pos = rb_entry_safe(rb_first_postorder(root), typeof(*pos), field); \
	     pos && (अणु n = rb_entry_safe(rb_next_postorder(&pos->field), \
			typeof(*pos), field); 1; पूर्ण); \
	     pos = n)

/*
 * Lefपंचांगost-cached rbtrees.
 *
 * We करो not cache the righपंचांगost node based on footprपूर्णांक
 * size vs number of potential users that could benefit
 * from O(1) rb_last(). Just not worth it, users that want
 * this feature can always implement the logic explicitly.
 * Furthermore, users that want to cache both poपूर्णांकers may
 * find it a bit asymmetric, but that's ok.
 */
काष्ठा rb_root_cached अणु
	काष्ठा rb_root rb_root;
	काष्ठा rb_node *rb_lefपंचांगost;
पूर्ण;

#घोषणा RB_ROOT_CACHED (काष्ठा rb_root_cached) अणु अणुशून्य, पूर्ण, शून्य पूर्ण

/* Same as rb_first(), but O(1) */
#घोषणा rb_first_cached(root) (root)->rb_lefपंचांगost

अटल अंतरभूत व्योम rb_insert_color_cached(काष्ठा rb_node *node,
					  काष्ठा rb_root_cached *root,
					  bool lefपंचांगost)
अणु
	अगर (lefपंचांगost)
		root->rb_lefपंचांगost = node;
	rb_insert_color(node, &root->rb_root);
पूर्ण


अटल अंतरभूत काष्ठा rb_node *
rb_erase_cached(काष्ठा rb_node *node, काष्ठा rb_root_cached *root)
अणु
	काष्ठा rb_node *lefपंचांगost = शून्य;

	अगर (root->rb_lefपंचांगost == node)
		lefपंचांगost = root->rb_lefपंचांगost = rb_next(node);

	rb_erase(node, &root->rb_root);

	वापस lefपंचांगost;
पूर्ण

अटल अंतरभूत व्योम rb_replace_node_cached(काष्ठा rb_node *victim,
					  काष्ठा rb_node *new,
					  काष्ठा rb_root_cached *root)
अणु
	अगर (root->rb_lefपंचांगost == victim)
		root->rb_lefपंचांगost = new;
	rb_replace_node(victim, new, &root->rb_root);
पूर्ण

/*
 * The below helper functions use 2 चालकs with 3 dअगरferent
 * calling conventions. The चालकs are related like:
 *
 *	comp(a->key,b) < 0  := less(a,b)
 *	comp(a->key,b) > 0  := less(b,a)
 *	comp(a->key,b) == 0 := !less(a,b) && !less(b,a)
 *
 * If these चालकs define a partial order on the elements we make no
 * guarantee on which of the elements matching the key is found. See
 * rb_find().
 *
 * The reason क्रम this is to allow the find() पूर्णांकerface without requiring an
 * on-stack dummy object, which might not be feasible due to object size.
 */

/**
 * rb_add_cached() - insert @node पूर्णांकo the lefपंचांगost cached tree @tree
 * @node: node to insert
 * @tree: lefपंचांगost cached tree to insert @node पूर्णांकo
 * @less: चालक defining the (partial) node order
 *
 * Returns @node when it is the new lefपंचांगost, or शून्य.
 */
अटल __always_अंतरभूत काष्ठा rb_node *
rb_add_cached(काष्ठा rb_node *node, काष्ठा rb_root_cached *tree,
	      bool (*less)(काष्ठा rb_node *, स्थिर काष्ठा rb_node *))
अणु
	काष्ठा rb_node **link = &tree->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	bool lefपंचांगost = true;

	जबतक (*link) अणु
		parent = *link;
		अगर (less(node, parent)) अणु
			link = &parent->rb_left;
		पूर्ण अन्यथा अणु
			link = &parent->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(node, parent, link);
	rb_insert_color_cached(node, tree, lefपंचांगost);

	वापस lefपंचांगost ? node : शून्य;
पूर्ण

/**
 * rb_add() - insert @node पूर्णांकo @tree
 * @node: node to insert
 * @tree: tree to insert @node पूर्णांकo
 * @less: चालक defining the (partial) node order
 */
अटल __always_अंतरभूत व्योम
rb_add(काष्ठा rb_node *node, काष्ठा rb_root *tree,
       bool (*less)(काष्ठा rb_node *, स्थिर काष्ठा rb_node *))
अणु
	काष्ठा rb_node **link = &tree->rb_node;
	काष्ठा rb_node *parent = शून्य;

	जबतक (*link) अणु
		parent = *link;
		अगर (less(node, parent))
			link = &parent->rb_left;
		अन्यथा
			link = &parent->rb_right;
	पूर्ण

	rb_link_node(node, parent, link);
	rb_insert_color(node, tree);
पूर्ण

/**
 * rb_find_add() - find equivalent @node in @tree, or add @node
 * @node: node to look-क्रम / insert
 * @tree: tree to search / modअगरy
 * @cmp: चालक defining the node order
 *
 * Returns the rb_node matching @node, or शून्य when no match is found and @node
 * is inserted.
 */
अटल __always_अंतरभूत काष्ठा rb_node *
rb_find_add(काष्ठा rb_node *node, काष्ठा rb_root *tree,
	    पूर्णांक (*cmp)(काष्ठा rb_node *, स्थिर काष्ठा rb_node *))
अणु
	काष्ठा rb_node **link = &tree->rb_node;
	काष्ठा rb_node *parent = शून्य;
	पूर्णांक c;

	जबतक (*link) अणु
		parent = *link;
		c = cmp(node, parent);

		अगर (c < 0)
			link = &parent->rb_left;
		अन्यथा अगर (c > 0)
			link = &parent->rb_right;
		अन्यथा
			वापस parent;
	पूर्ण

	rb_link_node(node, parent, link);
	rb_insert_color(node, tree);
	वापस शून्य;
पूर्ण

/**
 * rb_find() - find @key in tree @tree
 * @key: key to match
 * @tree: tree to search
 * @cmp: चालक defining the node order
 *
 * Returns the rb_node matching @key or शून्य.
 */
अटल __always_अंतरभूत काष्ठा rb_node *
rb_find(स्थिर व्योम *key, स्थिर काष्ठा rb_root *tree,
	पूर्णांक (*cmp)(स्थिर व्योम *key, स्थिर काष्ठा rb_node *))
अणु
	काष्ठा rb_node *node = tree->rb_node;

	जबतक (node) अणु
		पूर्णांक c = cmp(key, node);

		अगर (c < 0)
			node = node->rb_left;
		अन्यथा अगर (c > 0)
			node = node->rb_right;
		अन्यथा
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * rb_find_first() - find the first @key in @tree
 * @key: key to match
 * @tree: tree to search
 * @cmp: चालक defining node order
 *
 * Returns the lefपंचांगost node matching @key, or शून्य.
 */
अटल __always_अंतरभूत काष्ठा rb_node *
rb_find_first(स्थिर व्योम *key, स्थिर काष्ठा rb_root *tree,
	      पूर्णांक (*cmp)(स्थिर व्योम *key, स्थिर काष्ठा rb_node *))
अणु
	काष्ठा rb_node *node = tree->rb_node;
	काष्ठा rb_node *match = शून्य;

	जबतक (node) अणु
		पूर्णांक c = cmp(key, node);

		अगर (c <= 0) अणु
			अगर (!c)
				match = node;
			node = node->rb_left;
		पूर्ण अन्यथा अगर (c > 0) अणु
			node = node->rb_right;
		पूर्ण
	पूर्ण

	वापस match;
पूर्ण

/**
 * rb_next_match() - find the next @key in @tree
 * @key: key to match
 * @tree: tree to search
 * @cmp: चालक defining node order
 *
 * Returns the next node matching @key, or शून्य.
 */
अटल __always_अंतरभूत काष्ठा rb_node *
rb_next_match(स्थिर व्योम *key, काष्ठा rb_node *node,
	      पूर्णांक (*cmp)(स्थिर व्योम *key, स्थिर काष्ठा rb_node *))
अणु
	node = rb_next(node);
	अगर (node && cmp(key, node))
		node = शून्य;
	वापस node;
पूर्ण

/**
 * rb_क्रम_each() - iterates a subtree matching @key
 * @node: iterator
 * @key: key to match
 * @tree: tree to search
 * @cmp: चालक defining node order
 */
#घोषणा rb_क्रम_each(node, key, tree, cmp) \
	क्रम ((node) = rb_find_first((key), (tree), (cmp)); \
	     (node); (node) = rb_next_match((key), (node), (cmp)))

#पूर्ण_अगर	/* _LINUX_RBTREE_H */
