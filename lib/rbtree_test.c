<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/rbtree_augmented.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/समयx.h>

#घोषणा __param(type, name, init, msg)		\
	अटल type name = init;		\
	module_param(name, type, 0444);		\
	MODULE_PARM_DESC(name, msg);

__param(पूर्णांक, nnodes, 100, "Number of nodes in the rb-tree");
__param(पूर्णांक, perf_loops, 1000, "Number of iterations modifying the rb-tree");
__param(पूर्णांक, check_loops, 100, "Number of iterations modifying and verifying the rb-tree");

काष्ठा test_node अणु
	u32 key;
	काष्ठा rb_node rb;

	/* following fields used क्रम testing augmented rbtree functionality */
	u32 val;
	u32 augmented;
पूर्ण;

अटल काष्ठा rb_root_cached root = RB_ROOT_CACHED;
अटल काष्ठा test_node *nodes = शून्य;

अटल काष्ठा rnd_state rnd;

अटल व्योम insert(काष्ठा test_node *node, काष्ठा rb_root_cached *root)
अणु
	काष्ठा rb_node **new = &root->rb_root.rb_node, *parent = शून्य;
	u32 key = node->key;

	जबतक (*new) अणु
		parent = *new;
		अगर (key < rb_entry(parent, काष्ठा test_node, rb)->key)
			new = &parent->rb_left;
		अन्यथा
			new = &parent->rb_right;
	पूर्ण

	rb_link_node(&node->rb, parent, new);
	rb_insert_color(&node->rb, &root->rb_root);
पूर्ण

अटल व्योम insert_cached(काष्ठा test_node *node, काष्ठा rb_root_cached *root)
अणु
	काष्ठा rb_node **new = &root->rb_root.rb_node, *parent = शून्य;
	u32 key = node->key;
	bool lefपंचांगost = true;

	जबतक (*new) अणु
		parent = *new;
		अगर (key < rb_entry(parent, काष्ठा test_node, rb)->key)
			new = &parent->rb_left;
		अन्यथा अणु
			new = &parent->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(&node->rb, parent, new);
	rb_insert_color_cached(&node->rb, root, lefपंचांगost);
पूर्ण

अटल अंतरभूत व्योम erase(काष्ठा test_node *node, काष्ठा rb_root_cached *root)
अणु
	rb_erase(&node->rb, &root->rb_root);
पूर्ण

अटल अंतरभूत व्योम erase_cached(काष्ठा test_node *node, काष्ठा rb_root_cached *root)
अणु
	rb_erase_cached(&node->rb, root);
पूर्ण


#घोषणा NODE_VAL(node) ((node)->val)

RB_DECLARE_CALLBACKS_MAX(अटल, augment_callbacks,
			 काष्ठा test_node, rb, u32, augmented, NODE_VAL)

अटल व्योम insert_augmented(काष्ठा test_node *node,
			     काष्ठा rb_root_cached *root)
अणु
	काष्ठा rb_node **new = &root->rb_root.rb_node, *rb_parent = शून्य;
	u32 key = node->key;
	u32 val = node->val;
	काष्ठा test_node *parent;

	जबतक (*new) अणु
		rb_parent = *new;
		parent = rb_entry(rb_parent, काष्ठा test_node, rb);
		अगर (parent->augmented < val)
			parent->augmented = val;
		अगर (key < parent->key)
			new = &parent->rb.rb_left;
		अन्यथा
			new = &parent->rb.rb_right;
	पूर्ण

	node->augmented = val;
	rb_link_node(&node->rb, rb_parent, new);
	rb_insert_augmented(&node->rb, &root->rb_root, &augment_callbacks);
पूर्ण

अटल व्योम insert_augmented_cached(काष्ठा test_node *node,
				    काष्ठा rb_root_cached *root)
अणु
	काष्ठा rb_node **new = &root->rb_root.rb_node, *rb_parent = शून्य;
	u32 key = node->key;
	u32 val = node->val;
	काष्ठा test_node *parent;
	bool lefपंचांगost = true;

	जबतक (*new) अणु
		rb_parent = *new;
		parent = rb_entry(rb_parent, काष्ठा test_node, rb);
		अगर (parent->augmented < val)
			parent->augmented = val;
		अगर (key < parent->key)
			new = &parent->rb.rb_left;
		अन्यथा अणु
			new = &parent->rb.rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	node->augmented = val;
	rb_link_node(&node->rb, rb_parent, new);
	rb_insert_augmented_cached(&node->rb, root,
				   lefपंचांगost, &augment_callbacks);
पूर्ण


अटल व्योम erase_augmented(काष्ठा test_node *node, काष्ठा rb_root_cached *root)
अणु
	rb_erase_augmented(&node->rb, &root->rb_root, &augment_callbacks);
पूर्ण

अटल व्योम erase_augmented_cached(काष्ठा test_node *node,
				   काष्ठा rb_root_cached *root)
अणु
	rb_erase_augmented_cached(&node->rb, root, &augment_callbacks);
पूर्ण

अटल व्योम init(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < nnodes; i++) अणु
		nodes[i].key = pअक्रमom_u32_state(&rnd);
		nodes[i].val = pअक्रमom_u32_state(&rnd);
	पूर्ण
पूर्ण

अटल bool is_red(काष्ठा rb_node *rb)
अणु
	वापस !(rb->__rb_parent_color & 1);
पूर्ण

अटल पूर्णांक black_path_count(काष्ठा rb_node *rb)
अणु
	पूर्णांक count;
	क्रम (count = 0; rb; rb = rb_parent(rb))
		count += !is_red(rb);
	वापस count;
पूर्ण

अटल व्योम check_postorder_क्रमeach(पूर्णांक nr_nodes)
अणु
	काष्ठा test_node *cur, *n;
	पूर्णांक count = 0;
	rbtree_postorder_क्रम_each_entry_safe(cur, n, &root.rb_root, rb)
		count++;

	WARN_ON_ONCE(count != nr_nodes);
पूर्ण

अटल व्योम check_postorder(पूर्णांक nr_nodes)
अणु
	काष्ठा rb_node *rb;
	पूर्णांक count = 0;
	क्रम (rb = rb_first_postorder(&root.rb_root); rb; rb = rb_next_postorder(rb))
		count++;

	WARN_ON_ONCE(count != nr_nodes);
पूर्ण

अटल व्योम check(पूर्णांक nr_nodes)
अणु
	काष्ठा rb_node *rb;
	पूर्णांक count = 0, blacks = 0;
	u32 prev_key = 0;

	क्रम (rb = rb_first(&root.rb_root); rb; rb = rb_next(rb)) अणु
		काष्ठा test_node *node = rb_entry(rb, काष्ठा test_node, rb);
		WARN_ON_ONCE(node->key < prev_key);
		WARN_ON_ONCE(is_red(rb) &&
			     (!rb_parent(rb) || is_red(rb_parent(rb))));
		अगर (!count)
			blacks = black_path_count(rb);
		अन्यथा
			WARN_ON_ONCE((!rb->rb_left || !rb->rb_right) &&
				     blacks != black_path_count(rb));
		prev_key = node->key;
		count++;
	पूर्ण

	WARN_ON_ONCE(count != nr_nodes);
	WARN_ON_ONCE(count < (1 << black_path_count(rb_last(&root.rb_root))) - 1);

	check_postorder(nr_nodes);
	check_postorder_क्रमeach(nr_nodes);
पूर्ण

अटल व्योम check_augmented(पूर्णांक nr_nodes)
अणु
	काष्ठा rb_node *rb;

	check(nr_nodes);
	क्रम (rb = rb_first(&root.rb_root); rb; rb = rb_next(rb)) अणु
		काष्ठा test_node *node = rb_entry(rb, काष्ठा test_node, rb);
		u32 subtree, max = node->val;
		अगर (node->rb.rb_left) अणु
			subtree = rb_entry(node->rb.rb_left, काष्ठा test_node,
					   rb)->augmented;
			अगर (max < subtree)
				max = subtree;
		पूर्ण
		अगर (node->rb.rb_right) अणु
			subtree = rb_entry(node->rb.rb_right, काष्ठा test_node,
					   rb)->augmented;
			अगर (max < subtree)
				max = subtree;
		पूर्ण
		WARN_ON_ONCE(node->augmented != max);
	पूर्ण
पूर्ण

अटल पूर्णांक __init rbtree_test_init(व्योम)
अणु
	पूर्णांक i, j;
	cycles_t समय1, समय2, समय;
	काष्ठा rb_node *node;

	nodes = kदो_स्मृति_array(nnodes, माप(*nodes), GFP_KERNEL);
	अगर (!nodes)
		वापस -ENOMEM;

	prपूर्णांकk(KERN_ALERT "rbtree testing");

	pअक्रमom_seed_state(&rnd, 3141592653589793238ULL);
	init();

	समय1 = get_cycles();

	क्रम (i = 0; i < perf_loops; i++) अणु
		क्रम (j = 0; j < nnodes; j++)
			insert(nodes + j, &root);
		क्रम (j = 0; j < nnodes; j++)
			erase(nodes + j, &root);
	पूर्ण

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, perf_loops);
	prपूर्णांकk(" -> test 1 (latency of nnodes insert+delete): %llu cycles\n",
	       (अचिन्हित दीर्घ दीर्घ)समय);

	समय1 = get_cycles();

	क्रम (i = 0; i < perf_loops; i++) अणु
		क्रम (j = 0; j < nnodes; j++)
			insert_cached(nodes + j, &root);
		क्रम (j = 0; j < nnodes; j++)
			erase_cached(nodes + j, &root);
	पूर्ण

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, perf_loops);
	prपूर्णांकk(" -> test 2 (latency of nnodes cached insert+delete): %llu cycles\n",
	       (अचिन्हित दीर्घ दीर्घ)समय);

	क्रम (i = 0; i < nnodes; i++)
		insert(nodes + i, &root);

	समय1 = get_cycles();

	क्रम (i = 0; i < perf_loops; i++) अणु
		क्रम (node = rb_first(&root.rb_root); node; node = rb_next(node))
			;
	पूर्ण

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, perf_loops);
	prपूर्णांकk(" -> test 3 (latency of inorder traversal): %llu cycles\n",
	       (अचिन्हित दीर्घ दीर्घ)समय);

	समय1 = get_cycles();

	क्रम (i = 0; i < perf_loops; i++)
		node = rb_first(&root.rb_root);

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, perf_loops);
	prपूर्णांकk(" -> test 4 (latency to fetch first node)\n");
	prपूर्णांकk("        non-cached: %llu cycles\n", (अचिन्हित दीर्घ दीर्घ)समय);

	समय1 = get_cycles();

	क्रम (i = 0; i < perf_loops; i++)
		node = rb_first_cached(&root);

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, perf_loops);
	prपूर्णांकk("        cached: %llu cycles\n", (अचिन्हित दीर्घ दीर्घ)समय);

	क्रम (i = 0; i < nnodes; i++)
		erase(nodes + i, &root);

	/* run checks */
	क्रम (i = 0; i < check_loops; i++) अणु
		init();
		क्रम (j = 0; j < nnodes; j++) अणु
			check(j);
			insert(nodes + j, &root);
		पूर्ण
		क्रम (j = 0; j < nnodes; j++) अणु
			check(nnodes - j);
			erase(nodes + j, &root);
		पूर्ण
		check(0);
	पूर्ण

	prपूर्णांकk(KERN_ALERT "augmented rbtree testing");

	init();

	समय1 = get_cycles();

	क्रम (i = 0; i < perf_loops; i++) अणु
		क्रम (j = 0; j < nnodes; j++)
			insert_augmented(nodes + j, &root);
		क्रम (j = 0; j < nnodes; j++)
			erase_augmented(nodes + j, &root);
	पूर्ण

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, perf_loops);
	prपूर्णांकk(" -> test 1 (latency of nnodes insert+delete): %llu cycles\n", (अचिन्हित दीर्घ दीर्घ)समय);

	समय1 = get_cycles();

	क्रम (i = 0; i < perf_loops; i++) अणु
		क्रम (j = 0; j < nnodes; j++)
			insert_augmented_cached(nodes + j, &root);
		क्रम (j = 0; j < nnodes; j++)
			erase_augmented_cached(nodes + j, &root);
	पूर्ण

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, perf_loops);
	prपूर्णांकk(" -> test 2 (latency of nnodes cached insert+delete): %llu cycles\n", (अचिन्हित दीर्घ दीर्घ)समय);

	क्रम (i = 0; i < check_loops; i++) अणु
		init();
		क्रम (j = 0; j < nnodes; j++) अणु
			check_augmented(j);
			insert_augmented(nodes + j, &root);
		पूर्ण
		क्रम (j = 0; j < nnodes; j++) अणु
			check_augmented(nnodes - j);
			erase_augmented(nodes + j, &root);
		पूर्ण
		check_augmented(0);
	पूर्ण

	kमुक्त(nodes);

	वापस -EAGAIN; /* Fail will directly unload the module */
पूर्ण

अटल व्योम __निकास rbtree_test_निकास(व्योम)
अणु
	prपूर्णांकk(KERN_ALERT "test exit\n");
पूर्ण

module_init(rbtree_test_init)
module_निकास(rbtree_test_निकास)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michel Lespinasse");
MODULE_DESCRIPTION("Red Black Tree test");
