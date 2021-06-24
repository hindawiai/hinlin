<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>
#समावेश <निश्चित.स>
#समावेश <मानकपन.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>

#समावेश "test.h"

काष्ठा item *
item_tag_set(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index, पूर्णांक tag)
अणु
	वापस radix_tree_tag_set(root, index, tag);
पूर्ण

काष्ठा item *
item_tag_clear(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index, पूर्णांक tag)
अणु
	वापस radix_tree_tag_clear(root, index, tag);
पूर्ण

पूर्णांक item_tag_get(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index, पूर्णांक tag)
अणु
	वापस radix_tree_tag_get(root, index, tag);
पूर्ण

काष्ठा item *item_create(अचिन्हित दीर्घ index, अचिन्हित पूर्णांक order)
अणु
	काष्ठा item *ret = दो_स्मृति(माप(*ret));

	ret->index = index;
	ret->order = order;
	वापस ret;
पूर्ण

पूर्णांक item_insert(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index)
अणु
	काष्ठा item *item = item_create(index, 0);
	पूर्णांक err = radix_tree_insert(root, item->index, item);
	अगर (err)
		मुक्त(item);
	वापस err;
पूर्ण

व्योम item_sanity(काष्ठा item *item, अचिन्हित दीर्घ index)
अणु
	अचिन्हित दीर्घ mask;
	निश्चित(!radix_tree_is_पूर्णांकernal_node(item));
	निश्चित(item->order < BITS_PER_LONG);
	mask = (1UL << item->order) - 1;
	निश्चित((item->index | mask) == (index | mask));
पूर्ण

व्योम item_मुक्त(काष्ठा item *item, अचिन्हित दीर्घ index)
अणु
	item_sanity(item, index);
	मुक्त(item);
पूर्ण

पूर्णांक item_delete(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index)
अणु
	काष्ठा item *item = radix_tree_delete(root, index);

	अगर (!item)
		वापस 0;

	item_मुक्त(item, index);
	वापस 1;
पूर्ण

अटल व्योम item_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा item *item = container_of(head, काष्ठा item, rcu_head);

	मुक्त(item);
पूर्ण

पूर्णांक item_delete_rcu(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	काष्ठा item *item = xa_erase(xa, index);

	अगर (item) अणु
		item_sanity(item, index);
		call_rcu(&item->rcu_head, item_मुक्त_rcu);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम item_check_present(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index)
अणु
	काष्ठा item *item;

	item = radix_tree_lookup(root, index);
	निश्चित(item != शून्य);
	item_sanity(item, index);
पूर्ण

काष्ठा item *item_lookup(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index)
अणु
	वापस radix_tree_lookup(root, index);
पूर्ण

व्योम item_check_असलent(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index)
अणु
	काष्ठा item *item;

	item = radix_tree_lookup(root, index);
	निश्चित(item == शून्य);
पूर्ण

/*
 * Scan only the passed (start, start+nr] क्रम present items
 */
व्योम item_gang_check_present(काष्ठा radix_tree_root *root,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr,
			पूर्णांक chunk, पूर्णांक hop)
अणु
	काष्ठा item *items[chunk];
	अचिन्हित दीर्घ पूर्णांकo;

	क्रम (पूर्णांकo = 0; पूर्णांकo < nr; ) अणु
		पूर्णांक nfound;
		पूर्णांक nr_to_find = chunk;
		पूर्णांक i;

		अगर (nr_to_find > (nr - पूर्णांकo))
			nr_to_find = nr - पूर्णांकo;

		nfound = radix_tree_gang_lookup(root, (व्योम **)items,
						start + पूर्णांकo, nr_to_find);
		निश्चित(nfound == nr_to_find);
		क्रम (i = 0; i < nfound; i++)
			निश्चित(items[i]->index == start + पूर्णांकo + i);
		पूर्णांकo += hop;
	पूर्ण
पूर्ण

/*
 * Scan the entire tree, only expecting present items (start, start+nr]
 */
व्योम item_full_scan(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ nr, पूर्णांक chunk)
अणु
	काष्ठा item *items[chunk];
	अचिन्हित दीर्घ पूर्णांकo = 0;
	अचिन्हित दीर्घ this_index = start;
	पूर्णांक nfound;
	पूर्णांक i;

//	म_लिखो("%s(0x%08lx, 0x%08lx, %d)\n", __FUNCTION__, start, nr, chunk);

	जबतक ((nfound = radix_tree_gang_lookup(root, (व्योम **)items, पूर्णांकo,
					chunk))) अणु
//		म_लिखो("At 0x%08lx, nfound=%d\n", पूर्णांकo, nfound);
		क्रम (i = 0; i < nfound; i++) अणु
			निश्चित(items[i]->index == this_index);
			this_index++;
		पूर्ण
//		म_लिखो("Found 0x%08lx->0x%08lx\n",
//			items[0]->index, items[nfound-1]->index);
		पूर्णांकo = this_index;
	पूर्ण
	अगर (chunk)
		निश्चित(this_index == start + nr);
	nfound = radix_tree_gang_lookup(root, (व्योम **)items,
					this_index, chunk);
	निश्चित(nfound == 0);
पूर्ण

/* Use the same pattern as tag_pages_क्रम_ग_लिखोback() in mm/page-ग_लिखोback.c */
पूर्णांक tag_tagged_items(काष्ठा xarray *xa, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		अचिन्हित batch, xa_mark_t अगरtag, xa_mark_t thentag)
अणु
	XA_STATE(xas, xa, start);
	अचिन्हित पूर्णांक tagged = 0;
	काष्ठा item *item;

	अगर (batch == 0)
		batch = 1;

	xas_lock_irq(&xas);
	xas_क्रम_each_marked(&xas, item, end, अगरtag) अणु
		xas_set_mark(&xas, thentag);
		अगर (++tagged % batch)
			जारी;

		xas_छोड़ो(&xas);
		xas_unlock_irq(&xas);
		rcu_barrier();
		xas_lock_irq(&xas);
	पूर्ण
	xas_unlock_irq(&xas);

	वापस tagged;
पूर्ण

अटल पूर्णांक verअगरy_node(काष्ठा radix_tree_node *slot, अचिन्हित पूर्णांक tag,
			पूर्णांक tagged)
अणु
	पूर्णांक anyset = 0;
	पूर्णांक i;
	पूर्णांक j;

	slot = entry_to_node(slot);

	/* Verअगरy consistency at this level */
	क्रम (i = 0; i < RADIX_TREE_TAG_LONGS; i++) अणु
		अगर (slot->tags[tag][i]) अणु
			anyset = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (tagged != anyset) अणु
		म_लिखो("tag: %u, shift %u, tagged: %d, anyset: %d\n",
			tag, slot->shअगरt, tagged, anyset);
		क्रम (j = 0; j < RADIX_TREE_MAX_TAGS; j++) अणु
			म_लिखो("tag %d: ", j);
			क्रम (i = 0; i < RADIX_TREE_TAG_LONGS; i++)
				म_लिखो("%016lx ", slot->tags[j][i]);
			म_लिखो("\n");
		पूर्ण
		वापस 1;
	पूर्ण
	निश्चित(tagged == anyset);

	/* Go क्रम next level */
	अगर (slot->shअगरt > 0) अणु
		क्रम (i = 0; i < RADIX_TREE_MAP_SIZE; i++)
			अगर (slot->slots[i])
				अगर (verअगरy_node(slot->slots[i], tag,
					    !!test_bit(i, slot->tags[tag]))) अणु
					म_लिखो("Failure at off %d\n", i);
					क्रम (j = 0; j < RADIX_TREE_MAX_TAGS; j++) अणु
						म_लिखो("tag %d: ", j);
						क्रम (i = 0; i < RADIX_TREE_TAG_LONGS; i++)
							म_लिखो("%016lx ", slot->tags[j][i]);
						म_लिखो("\n");
					पूर्ण
					वापस 1;
				पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम verअगरy_tag_consistency(काष्ठा radix_tree_root *root, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा radix_tree_node *node = root->xa_head;
	अगर (!radix_tree_is_पूर्णांकernal_node(node))
		वापस;
	verअगरy_node(node, tag, !!root_tag_get(root, tag));
पूर्ण

व्योम item_समाप्त_tree(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	व्योम *entry;

	xas_क्रम_each(&xas, entry, अच_दीर्घ_उच्च) अणु
		अगर (!xa_is_value(entry)) अणु
			item_मुक्त(entry, xas.xa_index);
		पूर्ण
		xas_store(&xas, शून्य);
	पूर्ण

	निश्चित(xa_empty(xa));
पूर्ण

व्योम tree_verअगरy_min_height(काष्ठा radix_tree_root *root, पूर्णांक maxindex)
अणु
	अचिन्हित shअगरt;
	काष्ठा radix_tree_node *node = root->xa_head;
	अगर (!radix_tree_is_पूर्णांकernal_node(node)) अणु
		निश्चित(maxindex == 0);
		वापस;
	पूर्ण

	node = entry_to_node(node);
	निश्चित(maxindex <= node_maxindex(node));

	shअगरt = node->shअगरt;
	अगर (shअगरt > 0)
		निश्चित(maxindex > shअगरt_maxindex(shअगरt - RADIX_TREE_MAP_SHIFT));
	अन्यथा
		निश्चित(maxindex > 0);
पूर्ण
