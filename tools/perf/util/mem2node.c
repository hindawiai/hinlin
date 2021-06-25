<शैली गुरु>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <यंत्र/bug.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश "debug.h"
#समावेश "env.h"
#समावेश "mem2node.h"

काष्ठा phys_entry अणु
	काष्ठा rb_node	rb_node;
	u64	start;
	u64	end;
	u64	node;
पूर्ण;

अटल व्योम phys_entry__insert(काष्ठा phys_entry *entry, काष्ठा rb_root *root)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा phys_entry *e;

	जबतक (*p != शून्य) अणु
		parent = *p;
		e = rb_entry(parent, काष्ठा phys_entry, rb_node);

		अगर (entry->start < e->start)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	rb_link_node(&entry->rb_node, parent, p);
	rb_insert_color(&entry->rb_node, root);
पूर्ण

अटल व्योम
phys_entry__init(काष्ठा phys_entry *entry, u64 start, u64 bsize, u64 node)
अणु
	entry->start = start;
	entry->end   = start + bsize;
	entry->node  = node;
	RB_CLEAR_NODE(&entry->rb_node);
पूर्ण

पूर्णांक mem2node__init(काष्ठा mem2node *map, काष्ठा perf_env *env)
अणु
	काष्ठा memory_node *n, *nodes = &env->memory_nodes[0];
	काष्ठा phys_entry *entries, *पंचांगp_entries;
	u64 bsize = env->memory_bsize;
	पूर्णांक i, j = 0, max = 0;

	स_रखो(map, 0x0, माप(*map));
	map->root = RB_ROOT;

	क्रम (i = 0; i < env->nr_memory_nodes; i++) अणु
		n = &nodes[i];
		max += biपंचांगap_weight(n->set, n->size);
	पूर्ण

	entries = zalloc(माप(*entries) * max);
	अगर (!entries)
		वापस -ENOMEM;

	क्रम (i = 0; i < env->nr_memory_nodes; i++) अणु
		u64 bit;

		n = &nodes[i];

		क्रम (bit = 0; bit < n->size; bit++) अणु
			u64 start;

			अगर (!test_bit(bit, n->set))
				जारी;

			start = bit * bsize;

			/*
			 * Merge nearby areas, we walk in order
			 * through the biपंचांगap, so no need to sort.
			 */
			अगर (j > 0) अणु
				काष्ठा phys_entry *prev = &entries[j - 1];

				अगर ((prev->end == start) &&
				    (prev->node == n->node)) अणु
					prev->end += bsize;
					जारी;
				पूर्ण
			पूर्ण

			phys_entry__init(&entries[j++], start, bsize, n->node);
		पूर्ण
	पूर्ण

	/* Cut unused entries, due to merging. */
	पंचांगp_entries = पुनः_स्मृति(entries, माप(*entries) * j);
	अगर (पंचांगp_entries ||
	    WARN_ONCE(j == 0, "No memory nodes, is CONFIG_MEMORY_HOTPLUG enabled?\n"))
		entries = पंचांगp_entries;

	क्रम (i = 0; i < j; i++) अणु
		pr_debug("mem2node %03" PRIu64 " [0x%016" PRIx64 "-0x%016" PRIx64 "]\n",
			 entries[i].node, entries[i].start, entries[i].end);

		phys_entry__insert(&entries[i], &map->root);
	पूर्ण

	map->entries = entries;
	वापस 0;
पूर्ण

व्योम mem2node__निकास(काष्ठा mem2node *map)
अणु
	zमुक्त(&map->entries);
पूर्ण

पूर्णांक mem2node__node(काष्ठा mem2node *map, u64 addr)
अणु
	काष्ठा rb_node **p, *parent = शून्य;
	काष्ठा phys_entry *entry;

	p = &map->root.rb_node;
	जबतक (*p != शून्य) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा phys_entry, rb_node);
		अगर (addr < entry->start)
			p = &(*p)->rb_left;
		अन्यथा अगर (addr >= entry->end)
			p = &(*p)->rb_right;
		अन्यथा
			जाओ out;
	पूर्ण

	entry = शून्य;
out:
	वापस entry ? (पूर्णांक) entry->node : -1;
पूर्ण
