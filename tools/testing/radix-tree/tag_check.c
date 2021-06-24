<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>
#समावेश <निश्चित.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>

#समावेश <linux/slab.h>
#समावेश <linux/radix-tree.h>

#समावेश "test.h"


अटल व्योम
__simple_checks(काष्ठा radix_tree_root *tree, अचिन्हित दीर्घ index, पूर्णांक tag)
अणु
	अचिन्हित दीर्घ first = 0;
	पूर्णांक ret;

	item_check_असलent(tree, index);
	निश्चित(item_tag_get(tree, index, tag) == 0);

	item_insert(tree, index);
	निश्चित(item_tag_get(tree, index, tag) == 0);
	item_tag_set(tree, index, tag);
	ret = item_tag_get(tree, index, tag);
	निश्चित(ret != 0);
	ret = tag_tagged_items(tree, first, ~0UL, 10, tag, !tag);
	निश्चित(ret == 1);
	ret = item_tag_get(tree, index, !tag);
	निश्चित(ret != 0);
	ret = item_delete(tree, index);
	निश्चित(ret != 0);
	item_insert(tree, index);
	ret = item_tag_get(tree, index, tag);
	निश्चित(ret == 0);
	ret = item_delete(tree, index);
	निश्चित(ret != 0);
	ret = item_delete(tree, index);
	निश्चित(ret == 0);
पूर्ण

व्योम simple_checks(व्योम)
अणु
	अचिन्हित दीर्घ index;
	RADIX_TREE(tree, GFP_KERNEL);

	क्रम (index = 0; index < 10000; index++) अणु
		__simple_checks(&tree, index, 0);
		__simple_checks(&tree, index, 1);
	पूर्ण
	verअगरy_tag_consistency(&tree, 0);
	verअगरy_tag_consistency(&tree, 1);
	prपूर्णांकv(2, "before item_kill_tree: %d allocated\n", nr_allocated);
	item_समाप्त_tree(&tree);
	rcu_barrier();
	prपूर्णांकv(2, "after item_kill_tree: %d allocated\n", nr_allocated);
पूर्ण

/*
 * Check that tags propagate correctly when extending a tree.
 */
अटल व्योम extend_checks(व्योम)
अणु
	RADIX_TREE(tree, GFP_KERNEL);

	item_insert(&tree, 43);
	निश्चित(item_tag_get(&tree, 43, 0) == 0);
	item_tag_set(&tree, 43, 0);
	निश्चित(item_tag_get(&tree, 43, 0) == 1);
	item_insert(&tree, 1000000);
	निश्चित(item_tag_get(&tree, 43, 0) == 1);

	item_insert(&tree, 0);
	item_tag_set(&tree, 0, 0);
	item_delete(&tree, 1000000);
	निश्चित(item_tag_get(&tree, 43, 0) != 0);
	item_delete(&tree, 43);
	निश्चित(item_tag_get(&tree, 43, 0) == 0);	/* crash */
	निश्चित(item_tag_get(&tree, 0, 0) == 1);

	verअगरy_tag_consistency(&tree, 0);

	item_समाप्त_tree(&tree);
पूर्ण

/*
 * Check that tags propagate correctly when contracting a tree.
 */
अटल व्योम contract_checks(व्योम)
अणु
	काष्ठा item *item;
	पूर्णांक पंचांगp;
	RADIX_TREE(tree, GFP_KERNEL);

	पंचांगp = 1<<RADIX_TREE_MAP_SHIFT;
	item_insert(&tree, पंचांगp);
	item_insert(&tree, पंचांगp+1);
	item_tag_set(&tree, पंचांगp, 0);
	item_tag_set(&tree, पंचांगp, 1);
	item_tag_set(&tree, पंचांगp+1, 0);
	item_delete(&tree, पंचांगp+1);
	item_tag_clear(&tree, पंचांगp, 1);

	निश्चित(radix_tree_gang_lookup_tag(&tree, (व्योम **)&item, 0, 1, 0) == 1);
	निश्चित(radix_tree_gang_lookup_tag(&tree, (व्योम **)&item, 0, 1, 1) == 0);

	निश्चित(item_tag_get(&tree, पंचांगp, 0) == 1);
	निश्चित(item_tag_get(&tree, पंचांगp, 1) == 0);

	verअगरy_tag_consistency(&tree, 0);
	item_समाप्त_tree(&tree);
पूर्ण

/*
 * Stupid tag thrasher
 *
 * Create a large linear array corresponding to the tree.   Each element in
 * the array is coherent with each node in the tree
 */

क्रमागत अणु
	NODE_ABSENT = 0,
	NODE_PRESENT = 1,
	NODE_TAGGED = 2,
पूर्ण;

#घोषणा THRASH_SIZE		(1000 * 1000)
#घोषणा N 127
#घोषणा BATCH	33

अटल व्योम gang_check(काष्ठा radix_tree_root *tree,
			अक्षर *thrash_state, पूर्णांक tag)
अणु
	काष्ठा item *items[BATCH];
	पूर्णांक nr_found;
	अचिन्हित दीर्घ index = 0;
	अचिन्हित दीर्घ last_index = 0;

	जबतक ((nr_found = radix_tree_gang_lookup_tag(tree, (व्योम **)items,
					index, BATCH, tag))) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nr_found; i++) अणु
			काष्ठा item *item = items[i];

			जबतक (last_index < item->index) अणु
				निश्चित(thrash_state[last_index] != NODE_TAGGED);
				last_index++;
			पूर्ण
			निश्चित(thrash_state[last_index] == NODE_TAGGED);
			last_index++;
		पूर्ण
		index = items[nr_found - 1]->index + 1;
	पूर्ण
पूर्ण

अटल व्योम करो_thrash(काष्ठा radix_tree_root *tree, अक्षर *thrash_state, पूर्णांक tag)
अणु
	पूर्णांक insert_chunk;
	पूर्णांक delete_chunk;
	पूर्णांक tag_chunk;
	पूर्णांक untag_chunk;
	पूर्णांक total_tagged = 0;
	पूर्णांक total_present = 0;

	क्रम (insert_chunk = 1; insert_chunk < THRASH_SIZE; insert_chunk *= N)
	क्रम (delete_chunk = 1; delete_chunk < THRASH_SIZE; delete_chunk *= N)
	क्रम (tag_chunk = 1; tag_chunk < THRASH_SIZE; tag_chunk *= N)
	क्रम (untag_chunk = 1; untag_chunk < THRASH_SIZE; untag_chunk *= N) अणु
		पूर्णांक i;
		अचिन्हित दीर्घ index;
		पूर्णांक nr_inserted = 0;
		पूर्णांक nr_deleted = 0;
		पूर्णांक nr_tagged = 0;
		पूर्णांक nr_untagged = 0;
		पूर्णांक actual_total_tagged;
		पूर्णांक actual_total_present;

		क्रम (i = 0; i < insert_chunk; i++) अणु
			index = अक्रम() % THRASH_SIZE;
			अगर (thrash_state[index] != NODE_ABSENT)
				जारी;
			item_check_असलent(tree, index);
			item_insert(tree, index);
			निश्चित(thrash_state[index] != NODE_PRESENT);
			thrash_state[index] = NODE_PRESENT;
			nr_inserted++;
			total_present++;
		पूर्ण

		क्रम (i = 0; i < delete_chunk; i++) अणु
			index = अक्रम() % THRASH_SIZE;
			अगर (thrash_state[index] == NODE_ABSENT)
				जारी;
			item_check_present(tree, index);
			अगर (item_tag_get(tree, index, tag)) अणु
				निश्चित(thrash_state[index] == NODE_TAGGED);
				total_tagged--;
			पूर्ण अन्यथा अणु
				निश्चित(thrash_state[index] == NODE_PRESENT);
			पूर्ण
			item_delete(tree, index);
			निश्चित(thrash_state[index] != NODE_ABSENT);
			thrash_state[index] = NODE_ABSENT;
			nr_deleted++;
			total_present--;
		पूर्ण

		क्रम (i = 0; i < tag_chunk; i++) अणु
			index = अक्रम() % THRASH_SIZE;
			अगर (thrash_state[index] != NODE_PRESENT) अणु
				अगर (item_lookup(tree, index))
					निश्चित(item_tag_get(tree, index, tag));
				जारी;
			पूर्ण
			item_tag_set(tree, index, tag);
			item_tag_set(tree, index, tag);
			निश्चित(thrash_state[index] != NODE_TAGGED);
			thrash_state[index] = NODE_TAGGED;
			nr_tagged++;
			total_tagged++;
		पूर्ण

		क्रम (i = 0; i < untag_chunk; i++) अणु
			index = अक्रम() % THRASH_SIZE;
			अगर (thrash_state[index] != NODE_TAGGED)
				जारी;
			item_check_present(tree, index);
			निश्चित(item_tag_get(tree, index, tag));
			item_tag_clear(tree, index, tag);
			item_tag_clear(tree, index, tag);
			निश्चित(thrash_state[index] != NODE_PRESENT);
			thrash_state[index] = NODE_PRESENT;
			nr_untagged++;
			total_tagged--;
		पूर्ण

		actual_total_tagged = 0;
		actual_total_present = 0;
		क्रम (index = 0; index < THRASH_SIZE; index++) अणु
			चयन (thrash_state[index]) अणु
			हाल NODE_ABSENT:
				item_check_असलent(tree, index);
				अवरोध;
			हाल NODE_PRESENT:
				item_check_present(tree, index);
				निश्चित(!item_tag_get(tree, index, tag));
				actual_total_present++;
				अवरोध;
			हाल NODE_TAGGED:
				item_check_present(tree, index);
				निश्चित(item_tag_get(tree, index, tag));
				actual_total_present++;
				actual_total_tagged++;
				अवरोध;
			पूर्ण
		पूर्ण

		gang_check(tree, thrash_state, tag);

		prपूर्णांकv(2, "%d(%d) %d(%d) %d(%d) %d(%d) / "
				"%d(%d) present, %d(%d) tagged\n",
			insert_chunk, nr_inserted,
			delete_chunk, nr_deleted,
			tag_chunk, nr_tagged,
			untag_chunk, nr_untagged,
			total_present, actual_total_present,
			total_tagged, actual_total_tagged);
	पूर्ण
पूर्ण

अटल व्योम thrash_tags(व्योम)
अणु
	RADIX_TREE(tree, GFP_KERNEL);
	अक्षर *thrash_state;

	thrash_state = दो_स्मृति(THRASH_SIZE);
	स_रखो(thrash_state, 0, THRASH_SIZE);

	करो_thrash(&tree, thrash_state, 0);

	verअगरy_tag_consistency(&tree, 0);
	item_समाप्त_tree(&tree);
	मुक्त(thrash_state);
पूर्ण

अटल व्योम leak_check(व्योम)
अणु
	RADIX_TREE(tree, GFP_KERNEL);

	item_insert(&tree, 1000000);
	item_delete(&tree, 1000000);
	item_समाप्त_tree(&tree);
पूर्ण

अटल व्योम __leak_check(व्योम)
अणु
	RADIX_TREE(tree, GFP_KERNEL);

	prपूर्णांकv(2, "%d: nr_allocated=%d\n", __LINE__, nr_allocated);
	item_insert(&tree, 1000000);
	prपूर्णांकv(2, "%d: nr_allocated=%d\n", __LINE__, nr_allocated);
	item_delete(&tree, 1000000);
	prपूर्णांकv(2, "%d: nr_allocated=%d\n", __LINE__, nr_allocated);
	item_समाप्त_tree(&tree);
	prपूर्णांकv(2, "%d: nr_allocated=%d\n", __LINE__, nr_allocated);
पूर्ण

अटल व्योम single_check(व्योम)
अणु
	काष्ठा item *items[BATCH];
	RADIX_TREE(tree, GFP_KERNEL);
	पूर्णांक ret;
	अचिन्हित दीर्घ first = 0;

	item_insert(&tree, 0);
	item_tag_set(&tree, 0, 0);
	ret = radix_tree_gang_lookup_tag(&tree, (व्योम **)items, 0, BATCH, 0);
	निश्चित(ret == 1);
	ret = radix_tree_gang_lookup_tag(&tree, (व्योम **)items, 1, BATCH, 0);
	निश्चित(ret == 0);
	verअगरy_tag_consistency(&tree, 0);
	verअगरy_tag_consistency(&tree, 1);
	ret = tag_tagged_items(&tree, first, 10, 10, XA_MARK_0, XA_MARK_1);
	निश्चित(ret == 1);
	ret = radix_tree_gang_lookup_tag(&tree, (व्योम **)items, 0, BATCH, 1);
	निश्चित(ret == 1);
	item_tag_clear(&tree, 0, 0);
	ret = radix_tree_gang_lookup_tag(&tree, (व्योम **)items, 0, BATCH, 0);
	निश्चित(ret == 0);
	item_समाप्त_tree(&tree);
पूर्ण

व्योम tag_check(व्योम)
अणु
	single_check();
	extend_checks();
	contract_checks();
	rcu_barrier();
	prपूर्णांकv(2, "after extend_checks: %d allocated\n", nr_allocated);
	__leak_check();
	leak_check();
	rcu_barrier();
	prपूर्णांकv(2, "after leak_check: %d allocated\n", nr_allocated);
	simple_checks();
	rcu_barrier();
	prपूर्णांकv(2, "after simple_checks: %d allocated\n", nr_allocated);
	thrash_tags();
	rcu_barrier();
	prपूर्णांकv(2, "after thrash_tags: %d allocated\n", nr_allocated);
पूर्ण
