<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerval_tree.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/समयx.h>

#घोषणा __param(type, name, init, msg)		\
	अटल type name = init;		\
	module_param(name, type, 0444);		\
	MODULE_PARM_DESC(name, msg);

__param(पूर्णांक, nnodes, 100, "Number of nodes in the interval tree");
__param(पूर्णांक, perf_loops, 1000, "Number of iterations modifying the tree");

__param(पूर्णांक, nsearches, 100, "Number of searches to the interval tree");
__param(पूर्णांक, search_loops, 1000, "Number of iterations searching the tree");
__param(bool, search_all, false, "Searches will iterate all nodes in the tree");

__param(uपूर्णांक, max_endpoपूर्णांक, ~0, "Largest value for the interval's endpoint");

अटल काष्ठा rb_root_cached root = RB_ROOT_CACHED;
अटल काष्ठा पूर्णांकerval_tree_node *nodes = शून्य;
अटल u32 *queries = शून्य;

अटल काष्ठा rnd_state rnd;

अटल अंतरभूत अचिन्हित दीर्घ
search(काष्ठा rb_root_cached *root, अचिन्हित दीर्घ start, अचिन्हित दीर्घ last)
अणु
	काष्ठा पूर्णांकerval_tree_node *node;
	अचिन्हित दीर्घ results = 0;

	क्रम (node = पूर्णांकerval_tree_iter_first(root, start, last); node;
	     node = पूर्णांकerval_tree_iter_next(node, start, last))
		results++;
	वापस results;
पूर्ण

अटल व्योम init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nnodes; i++) अणु
		u32 b = (pअक्रमom_u32_state(&rnd) >> 4) % max_endpoपूर्णांक;
		u32 a = (pअक्रमom_u32_state(&rnd) >> 4) % b;

		nodes[i].start = a;
		nodes[i].last = b;
	पूर्ण

	/*
	 * Limit the search scope to what the user defined.
	 * Otherwise we are merely measuring empty walks,
	 * which is poपूर्णांकless.
	 */
	क्रम (i = 0; i < nsearches; i++)
		queries[i] = (pअक्रमom_u32_state(&rnd) >> 4) % max_endpoपूर्णांक;
पूर्ण

अटल पूर्णांक पूर्णांकerval_tree_test_init(व्योम)
अणु
	पूर्णांक i, j;
	अचिन्हित दीर्घ results;
	cycles_t समय1, समय2, समय;

	nodes = kदो_स्मृति_array(nnodes, माप(काष्ठा पूर्णांकerval_tree_node),
			      GFP_KERNEL);
	अगर (!nodes)
		वापस -ENOMEM;

	queries = kदो_स्मृति_array(nsearches, माप(पूर्णांक), GFP_KERNEL);
	अगर (!queries) अणु
		kमुक्त(nodes);
		वापस -ENOMEM;
	पूर्ण

	prपूर्णांकk(KERN_ALERT "interval tree insert/remove");

	pअक्रमom_seed_state(&rnd, 3141592653589793238ULL);
	init();

	समय1 = get_cycles();

	क्रम (i = 0; i < perf_loops; i++) अणु
		क्रम (j = 0; j < nnodes; j++)
			पूर्णांकerval_tree_insert(nodes + j, &root);
		क्रम (j = 0; j < nnodes; j++)
			पूर्णांकerval_tree_हटाओ(nodes + j, &root);
	पूर्ण

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, perf_loops);
	prपूर्णांकk(" -> %llu cycles\n", (अचिन्हित दीर्घ दीर्घ)समय);

	prपूर्णांकk(KERN_ALERT "interval tree search");

	क्रम (j = 0; j < nnodes; j++)
		पूर्णांकerval_tree_insert(nodes + j, &root);

	समय1 = get_cycles();

	results = 0;
	क्रम (i = 0; i < search_loops; i++)
		क्रम (j = 0; j < nsearches; j++) अणु
			अचिन्हित दीर्घ start = search_all ? 0 : queries[j];
			अचिन्हित दीर्घ last = search_all ? max_endpoपूर्णांक : queries[j];

			results += search(&root, start, last);
		पूर्ण

	समय2 = get_cycles();
	समय = समय2 - समय1;

	समय = भाग_u64(समय, search_loops);
	results = भाग_u64(results, search_loops);
	prपूर्णांकk(" -> %llu cycles (%lu results)\n",
	       (अचिन्हित दीर्घ दीर्घ)समय, results);

	kमुक्त(queries);
	kमुक्त(nodes);

	वापस -EAGAIN; /* Fail will directly unload the module */
पूर्ण

अटल व्योम पूर्णांकerval_tree_test_निकास(व्योम)
अणु
	prपूर्णांकk(KERN_ALERT "test exit\n");
पूर्ण

module_init(पूर्णांकerval_tree_test_init)
module_निकास(पूर्णांकerval_tree_test_निकास)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michel Lespinasse");
MODULE_DESCRIPTION("Interval Tree test");
