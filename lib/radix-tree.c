<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Momchil Velikov
 * Portions Copyright (C) 2001 Christoph Hellwig
 * Copyright (C) 2005 SGI, Christoph Lameter
 * Copyright (C) 2006 Nick Piggin
 * Copyright (C) 2012 Konstantin Khlebnikov
 * Copyright (C) 2016 Intel, Matthew Wilcox
 * Copyright (C) 2016 Intel, Ross Zwisler
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/percpu.h>
#समावेश <linux/preempt.h>		/* in_पूर्णांकerrupt() */
#समावेश <linux/radix-tree.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/xarray.h>

/*
 * Radix tree node cache.
 */
काष्ठा kmem_cache *radix_tree_node_cachep;

/*
 * The radix tree is variable-height, so an insert operation not only has
 * to build the branch to its corresponding item, it also has to build the
 * branch to existing items अगर the size has to be increased (by
 * radix_tree_extend).
 *
 * The worst हाल is a zero height tree with just a single item at index 0,
 * and then inserting an item at index अच_दीर्घ_उच्च. This requires 2 new branches
 * of RADIX_TREE_MAX_PATH size to be created, with only the root node shared.
 * Hence:
 */
#घोषणा RADIX_TREE_PRELOAD_SIZE (RADIX_TREE_MAX_PATH * 2 - 1)

/*
 * The IDR करोes not have to be as high as the radix tree since it uses
 * चिन्हित पूर्णांकegers, not अचिन्हित दीर्घs.
 */
#घोषणा IDR_INDEX_BITS		(8 /* अक्षर_बिट */ * माप(पूर्णांक) - 1)
#घोषणा IDR_MAX_PATH		(DIV_ROUND_UP(IDR_INDEX_BITS, \
						RADIX_TREE_MAP_SHIFT))
#घोषणा IDR_PRELOAD_SIZE	(IDR_MAX_PATH * 2 - 1)

/*
 * Per-cpu pool of preloaded nodes
 */
DEFINE_PER_CPU(काष्ठा radix_tree_preload, radix_tree_preloads) = अणु
	.lock = INIT_LOCAL_LOCK(lock),
पूर्ण;
EXPORT_PER_CPU_SYMBOL_GPL(radix_tree_preloads);

अटल अंतरभूत काष्ठा radix_tree_node *entry_to_node(व्योम *ptr)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)ptr & ~RADIX_TREE_INTERNAL_NODE);
पूर्ण

अटल अंतरभूत व्योम *node_to_entry(व्योम *ptr)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)ptr | RADIX_TREE_INTERNAL_NODE);
पूर्ण

#घोषणा RADIX_TREE_RETRY	XA_RETRY_ENTRY

अटल अंतरभूत अचिन्हित दीर्घ
get_slot_offset(स्थिर काष्ठा radix_tree_node *parent, व्योम __rcu **slot)
अणु
	वापस parent ? slot - parent->slots : 0;
पूर्ण

अटल अचिन्हित पूर्णांक radix_tree_descend(स्थिर काष्ठा radix_tree_node *parent,
			काष्ठा radix_tree_node **nodep, अचिन्हित दीर्घ index)
अणु
	अचिन्हित पूर्णांक offset = (index >> parent->shअगरt) & RADIX_TREE_MAP_MASK;
	व्योम __rcu **entry = rcu_dereference_raw(parent->slots[offset]);

	*nodep = (व्योम *)entry;
	वापस offset;
पूर्ण

अटल अंतरभूत gfp_t root_gfp_mask(स्थिर काष्ठा radix_tree_root *root)
अणु
	वापस root->xa_flags & (__GFP_BITS_MASK & ~GFP_ZONEMASK);
पूर्ण

अटल अंतरभूत व्योम tag_set(काष्ठा radix_tree_node *node, अचिन्हित पूर्णांक tag,
		पूर्णांक offset)
अणु
	__set_bit(offset, node->tags[tag]);
पूर्ण

अटल अंतरभूत व्योम tag_clear(काष्ठा radix_tree_node *node, अचिन्हित पूर्णांक tag,
		पूर्णांक offset)
अणु
	__clear_bit(offset, node->tags[tag]);
पूर्ण

अटल अंतरभूत पूर्णांक tag_get(स्थिर काष्ठा radix_tree_node *node, अचिन्हित पूर्णांक tag,
		पूर्णांक offset)
अणु
	वापस test_bit(offset, node->tags[tag]);
पूर्ण

अटल अंतरभूत व्योम root_tag_set(काष्ठा radix_tree_root *root, अचिन्हित tag)
अणु
	root->xa_flags |= (__क्रमce gfp_t)(1 << (tag + ROOT_TAG_SHIFT));
पूर्ण

अटल अंतरभूत व्योम root_tag_clear(काष्ठा radix_tree_root *root, अचिन्हित tag)
अणु
	root->xa_flags &= (__क्रमce gfp_t)~(1 << (tag + ROOT_TAG_SHIFT));
पूर्ण

अटल अंतरभूत व्योम root_tag_clear_all(काष्ठा radix_tree_root *root)
अणु
	root->xa_flags &= (__क्रमce gfp_t)((1 << ROOT_TAG_SHIFT) - 1);
पूर्ण

अटल अंतरभूत पूर्णांक root_tag_get(स्थिर काष्ठा radix_tree_root *root, अचिन्हित tag)
अणु
	वापस (__क्रमce पूर्णांक)root->xa_flags & (1 << (tag + ROOT_TAG_SHIFT));
पूर्ण

अटल अंतरभूत अचिन्हित root_tags_get(स्थिर काष्ठा radix_tree_root *root)
अणु
	वापस (__क्रमce अचिन्हित)root->xa_flags >> ROOT_TAG_SHIFT;
पूर्ण

अटल अंतरभूत bool is_idr(स्थिर काष्ठा radix_tree_root *root)
अणु
	वापस !!(root->xa_flags & ROOT_IS_IDR);
पूर्ण

/*
 * Returns 1 अगर any slot in the node has this tag set.
 * Otherwise वापसs 0.
 */
अटल अंतरभूत पूर्णांक any_tag_set(स्थिर काष्ठा radix_tree_node *node,
							अचिन्हित पूर्णांक tag)
अणु
	अचिन्हित idx;
	क्रम (idx = 0; idx < RADIX_TREE_TAG_LONGS; idx++) अणु
		अगर (node->tags[tag][idx])
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम all_tag_set(काष्ठा radix_tree_node *node, अचिन्हित पूर्णांक tag)
अणु
	biपंचांगap_fill(node->tags[tag], RADIX_TREE_MAP_SIZE);
पूर्ण

/**
 * radix_tree_find_next_bit - find the next set bit in a memory region
 *
 * @node: where to begin the search
 * @tag: the tag index
 * @offset: the bitnumber to start searching at
 *
 * Unrollable variant of find_next_bit() क्रम स्थिरant size arrays.
 * Tail bits starting from size to roundup(size, BITS_PER_LONG) must be zero.
 * Returns next bit offset, or size अगर nothing found.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ
radix_tree_find_next_bit(काष्ठा radix_tree_node *node, अचिन्हित पूर्णांक tag,
			 अचिन्हित दीर्घ offset)
अणु
	स्थिर अचिन्हित दीर्घ *addr = node->tags[tag];

	अगर (offset < RADIX_TREE_MAP_SIZE) अणु
		अचिन्हित दीर्घ पंचांगp;

		addr += offset / BITS_PER_LONG;
		पंचांगp = *addr >> (offset % BITS_PER_LONG);
		अगर (पंचांगp)
			वापस __ffs(पंचांगp) + offset;
		offset = (offset + BITS_PER_LONG) & ~(BITS_PER_LONG - 1);
		जबतक (offset < RADIX_TREE_MAP_SIZE) अणु
			पंचांगp = *++addr;
			अगर (पंचांगp)
				वापस __ffs(पंचांगp) + offset;
			offset += BITS_PER_LONG;
		पूर्ण
	पूर्ण
	वापस RADIX_TREE_MAP_SIZE;
पूर्ण

अटल अचिन्हित पूर्णांक iter_offset(स्थिर काष्ठा radix_tree_iter *iter)
अणु
	वापस iter->index & RADIX_TREE_MAP_MASK;
पूर्ण

/*
 * The maximum index which can be stored in a radix tree
 */
अटल अंतरभूत अचिन्हित दीर्घ shअगरt_maxindex(अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (RADIX_TREE_MAP_SIZE << shअगरt) - 1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ node_maxindex(स्थिर काष्ठा radix_tree_node *node)
अणु
	वापस shअगरt_maxindex(node->shअगरt);
पूर्ण

अटल अचिन्हित दीर्घ next_index(अचिन्हित दीर्घ index,
				स्थिर काष्ठा radix_tree_node *node,
				अचिन्हित दीर्घ offset)
अणु
	वापस (index & ~node_maxindex(node)) + (offset << node->shअगरt);
पूर्ण

/*
 * This assumes that the caller has perक्रमmed appropriate pपुनः_स्मृतिation, and
 * that the caller has pinned this thपढ़ो of control to the current CPU.
 */
अटल काष्ठा radix_tree_node *
radix_tree_node_alloc(gfp_t gfp_mask, काष्ठा radix_tree_node *parent,
			काष्ठा radix_tree_root *root,
			अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक offset,
			अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक nr_values)
अणु
	काष्ठा radix_tree_node *ret = शून्य;

	/*
	 * Preload code isn't irq safe and it doesn't make sense to use
	 * preloading during an पूर्णांकerrupt anyway as all the allocations have
	 * to be atomic. So just करो normal allocation when in पूर्णांकerrupt.
	 */
	अगर (!gfpflags_allow_blocking(gfp_mask) && !in_पूर्णांकerrupt()) अणु
		काष्ठा radix_tree_preload *rtp;

		/*
		 * Even अगर the caller has preloaded, try to allocate from the
		 * cache first क्रम the new node to get accounted to the memory
		 * cgroup.
		 */
		ret = kmem_cache_alloc(radix_tree_node_cachep,
				       gfp_mask | __GFP_NOWARN);
		अगर (ret)
			जाओ out;

		/*
		 * Provided the caller has preloaded here, we will always
		 * succeed in getting a node here (and never reach
		 * kmem_cache_alloc)
		 */
		rtp = this_cpu_ptr(&radix_tree_preloads);
		अगर (rtp->nr) अणु
			ret = rtp->nodes;
			rtp->nodes = ret->parent;
			rtp->nr--;
		पूर्ण
		/*
		 * Update the allocation stack trace as this is more useful
		 * क्रम debugging.
		 */
		kmemleak_update_trace(ret);
		जाओ out;
	पूर्ण
	ret = kmem_cache_alloc(radix_tree_node_cachep, gfp_mask);
out:
	BUG_ON(radix_tree_is_पूर्णांकernal_node(ret));
	अगर (ret) अणु
		ret->shअगरt = shअगरt;
		ret->offset = offset;
		ret->count = count;
		ret->nr_values = nr_values;
		ret->parent = parent;
		ret->array = root;
	पूर्ण
	वापस ret;
पूर्ण

व्योम radix_tree_node_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा radix_tree_node *node =
			container_of(head, काष्ठा radix_tree_node, rcu_head);

	/*
	 * Must only मुक्त zeroed nodes पूर्णांकo the slab.  We can be left with
	 * non-शून्य entries by radix_tree_मुक्त_nodes, so clear the entries
	 * and tags here.
	 */
	स_रखो(node->slots, 0, माप(node->slots));
	स_रखो(node->tags, 0, माप(node->tags));
	INIT_LIST_HEAD(&node->निजी_list);

	kmem_cache_मुक्त(radix_tree_node_cachep, node);
पूर्ण

अटल अंतरभूत व्योम
radix_tree_node_मुक्त(काष्ठा radix_tree_node *node)
अणु
	call_rcu(&node->rcu_head, radix_tree_node_rcu_मुक्त);
पूर्ण

/*
 * Load up this CPU's radix_tree_node buffer with sufficient objects to
 * ensure that the addition of a single element in the tree cannot fail.  On
 * success, वापस zero, with preemption disabled.  On error, वापस -ENOMEM
 * with preemption not disabled.
 *
 * To make use of this facility, the radix tree must be initialised without
 * __GFP_सूचीECT_RECLAIM being passed to INIT_RADIX_TREE().
 */
अटल __must_check पूर्णांक __radix_tree_preload(gfp_t gfp_mask, अचिन्हित nr)
अणु
	काष्ठा radix_tree_preload *rtp;
	काष्ठा radix_tree_node *node;
	पूर्णांक ret = -ENOMEM;

	/*
	 * Nodes preloaded by one cgroup can be used by another cgroup, so
	 * they should never be accounted to any particular memory cgroup.
	 */
	gfp_mask &= ~__GFP_ACCOUNT;

	local_lock(&radix_tree_preloads.lock);
	rtp = this_cpu_ptr(&radix_tree_preloads);
	जबतक (rtp->nr < nr) अणु
		local_unlock(&radix_tree_preloads.lock);
		node = kmem_cache_alloc(radix_tree_node_cachep, gfp_mask);
		अगर (node == शून्य)
			जाओ out;
		local_lock(&radix_tree_preloads.lock);
		rtp = this_cpu_ptr(&radix_tree_preloads);
		अगर (rtp->nr < nr) अणु
			node->parent = rtp->nodes;
			rtp->nodes = node;
			rtp->nr++;
		पूर्ण अन्यथा अणु
			kmem_cache_मुक्त(radix_tree_node_cachep, node);
		पूर्ण
	पूर्ण
	ret = 0;
out:
	वापस ret;
पूर्ण

/*
 * Load up this CPU's radix_tree_node buffer with sufficient objects to
 * ensure that the addition of a single element in the tree cannot fail.  On
 * success, वापस zero, with preemption disabled.  On error, वापस -ENOMEM
 * with preemption not disabled.
 *
 * To make use of this facility, the radix tree must be initialised without
 * __GFP_सूचीECT_RECLAIM being passed to INIT_RADIX_TREE().
 */
पूर्णांक radix_tree_preload(gfp_t gfp_mask)
अणु
	/* Warn on non-sensical use... */
	WARN_ON_ONCE(!gfpflags_allow_blocking(gfp_mask));
	वापस __radix_tree_preload(gfp_mask, RADIX_TREE_PRELOAD_SIZE);
पूर्ण
EXPORT_SYMBOL(radix_tree_preload);

/*
 * The same as above function, except we करोn't guarantee preloading happens.
 * We करो it, अगर we decide it helps. On success, वापस zero with preemption
 * disabled. On error, वापस -ENOMEM with preemption not disabled.
 */
पूर्णांक radix_tree_maybe_preload(gfp_t gfp_mask)
अणु
	अगर (gfpflags_allow_blocking(gfp_mask))
		वापस __radix_tree_preload(gfp_mask, RADIX_TREE_PRELOAD_SIZE);
	/* Preloading करोesn't help anything with this gfp mask, skip it */
	local_lock(&radix_tree_preloads.lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(radix_tree_maybe_preload);

अटल अचिन्हित radix_tree_load_root(स्थिर काष्ठा radix_tree_root *root,
		काष्ठा radix_tree_node **nodep, अचिन्हित दीर्घ *maxindex)
अणु
	काष्ठा radix_tree_node *node = rcu_dereference_raw(root->xa_head);

	*nodep = node;

	अगर (likely(radix_tree_is_पूर्णांकernal_node(node))) अणु
		node = entry_to_node(node);
		*maxindex = node_maxindex(node);
		वापस node->shअगरt + RADIX_TREE_MAP_SHIFT;
	पूर्ण

	*maxindex = 0;
	वापस 0;
पूर्ण

/*
 *	Extend a radix tree so it can store key @index.
 */
अटल पूर्णांक radix_tree_extend(काष्ठा radix_tree_root *root, gfp_t gfp,
				अचिन्हित दीर्घ index, अचिन्हित पूर्णांक shअगरt)
अणु
	व्योम *entry;
	अचिन्हित पूर्णांक maxshअगरt;
	पूर्णांक tag;

	/* Figure out what the shअगरt should be.  */
	maxshअगरt = shअगरt;
	जबतक (index > shअगरt_maxindex(maxshअगरt))
		maxshअगरt += RADIX_TREE_MAP_SHIFT;

	entry = rcu_dereference_raw(root->xa_head);
	अगर (!entry && (!is_idr(root) || root_tag_get(root, IDR_FREE)))
		जाओ out;

	करो अणु
		काष्ठा radix_tree_node *node = radix_tree_node_alloc(gfp, शून्य,
							root, shअगरt, 0, 1, 0);
		अगर (!node)
			वापस -ENOMEM;

		अगर (is_idr(root)) अणु
			all_tag_set(node, IDR_FREE);
			अगर (!root_tag_get(root, IDR_FREE)) अणु
				tag_clear(node, IDR_FREE, 0);
				root_tag_set(root, IDR_FREE);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Propagate the aggregated tag info to the new child */
			क्रम (tag = 0; tag < RADIX_TREE_MAX_TAGS; tag++) अणु
				अगर (root_tag_get(root, tag))
					tag_set(node, tag, 0);
			पूर्ण
		पूर्ण

		BUG_ON(shअगरt > BITS_PER_LONG);
		अगर (radix_tree_is_पूर्णांकernal_node(entry)) अणु
			entry_to_node(entry)->parent = node;
		पूर्ण अन्यथा अगर (xa_is_value(entry)) अणु
			/* Moving a value entry root->xa_head to a node */
			node->nr_values = 1;
		पूर्ण
		/*
		 * entry was alपढ़ोy in the radix tree, so we करो not need
		 * rcu_assign_poपूर्णांकer here
		 */
		node->slots[0] = (व्योम __rcu *)entry;
		entry = node_to_entry(node);
		rcu_assign_poपूर्णांकer(root->xa_head, entry);
		shअगरt += RADIX_TREE_MAP_SHIFT;
	पूर्ण जबतक (shअगरt <= maxshअगरt);
out:
	वापस maxshअगरt + RADIX_TREE_MAP_SHIFT;
पूर्ण

/**
 *	radix_tree_shrink    -    shrink radix tree to minimum height
 *	@root:		radix tree root
 */
अटल अंतरभूत bool radix_tree_shrink(काष्ठा radix_tree_root *root)
अणु
	bool shrunk = false;

	क्रम (;;) अणु
		काष्ठा radix_tree_node *node = rcu_dereference_raw(root->xa_head);
		काष्ठा radix_tree_node *child;

		अगर (!radix_tree_is_पूर्णांकernal_node(node))
			अवरोध;
		node = entry_to_node(node);

		/*
		 * The candidate node has more than one child, or its child
		 * is not at the lefपंचांगost slot, we cannot shrink.
		 */
		अगर (node->count != 1)
			अवरोध;
		child = rcu_dereference_raw(node->slots[0]);
		अगर (!child)
			अवरोध;

		/*
		 * For an IDR, we must not shrink entry 0 पूर्णांकo the root in
		 * हाल somebody calls idr_replace() with a poपूर्णांकer that
		 * appears to be an पूर्णांकernal entry
		 */
		अगर (!node->shअगरt && is_idr(root))
			अवरोध;

		अगर (radix_tree_is_पूर्णांकernal_node(child))
			entry_to_node(child)->parent = शून्य;

		/*
		 * We करोn't need rcu_assign_poपूर्णांकer(), since we are simply
		 * moving the node from one part of the tree to another: अगर it
		 * was safe to dereference the old poपूर्णांकer to it
		 * (node->slots[0]), it will be safe to dereference the new
		 * one (root->xa_head) as far as dependent पढ़ो barriers go.
		 */
		root->xa_head = (व्योम __rcu *)child;
		अगर (is_idr(root) && !tag_get(node, IDR_FREE, 0))
			root_tag_clear(root, IDR_FREE);

		/*
		 * We have a dilemma here. The node's slot[0] must not be
		 * शून्यed in हाल there are concurrent lookups expecting to
		 * find the item. However अगर this was a bottom-level node,
		 * then it may be subject to the slot poपूर्णांकer being visible
		 * to callers dereferencing it. If item corresponding to
		 * slot[0] is subsequently deleted, these callers would expect
		 * their slot to become empty sooner or later.
		 *
		 * For example, lockless pagecache will look up a slot, deref
		 * the page poपूर्णांकer, and अगर the page has 0 refcount it means it
		 * was concurrently deleted from pagecache so try the deref
		 * again. Fortunately there is alपढ़ोy a requirement क्रम logic
		 * to retry the entire slot lookup -- the indirect poपूर्णांकer
		 * problem (replacing direct root node with an indirect poपूर्णांकer
		 * also results in a stale slot). So tag the slot as indirect
		 * to क्रमce callers to retry.
		 */
		node->count = 0;
		अगर (!radix_tree_is_पूर्णांकernal_node(child)) अणु
			node->slots[0] = (व्योम __rcu *)RADIX_TREE_RETRY;
		पूर्ण

		WARN_ON_ONCE(!list_empty(&node->निजी_list));
		radix_tree_node_मुक्त(node);
		shrunk = true;
	पूर्ण

	वापस shrunk;
पूर्ण

अटल bool delete_node(काष्ठा radix_tree_root *root,
			काष्ठा radix_tree_node *node)
अणु
	bool deleted = false;

	करो अणु
		काष्ठा radix_tree_node *parent;

		अगर (node->count) अणु
			अगर (node_to_entry(node) ==
					rcu_dereference_raw(root->xa_head))
				deleted |= radix_tree_shrink(root);
			वापस deleted;
		पूर्ण

		parent = node->parent;
		अगर (parent) अणु
			parent->slots[node->offset] = शून्य;
			parent->count--;
		पूर्ण अन्यथा अणु
			/*
			 * Shouldn't the tags alपढ़ोy have all been cleared
			 * by the caller?
			 */
			अगर (!is_idr(root))
				root_tag_clear_all(root);
			root->xa_head = शून्य;
		पूर्ण

		WARN_ON_ONCE(!list_empty(&node->निजी_list));
		radix_tree_node_मुक्त(node);
		deleted = true;

		node = parent;
	पूर्ण जबतक (node);

	वापस deleted;
पूर्ण

/**
 *	__radix_tree_create	-	create a slot in a radix tree
 *	@root:		radix tree root
 *	@index:		index key
 *	@nodep:		वापसs node
 *	@slotp:		वापसs slot
 *
 *	Create, अगर necessary, and वापस the node and slot क्रम an item
 *	at position @index in the radix tree @root.
 *
 *	Until there is more than one item in the tree, no nodes are
 *	allocated and @root->xa_head is used as a direct slot instead of
 *	poपूर्णांकing to a node, in which हाल *@nodep will be शून्य.
 *
 *	Returns -ENOMEM, or 0 क्रम success.
 */
अटल पूर्णांक __radix_tree_create(काष्ठा radix_tree_root *root,
		अचिन्हित दीर्घ index, काष्ठा radix_tree_node **nodep,
		व्योम __rcu ***slotp)
अणु
	काष्ठा radix_tree_node *node = शून्य, *child;
	व्योम __rcu **slot = (व्योम __rcu **)&root->xa_head;
	अचिन्हित दीर्घ maxindex;
	अचिन्हित पूर्णांक shअगरt, offset = 0;
	अचिन्हित दीर्घ max = index;
	gfp_t gfp = root_gfp_mask(root);

	shअगरt = radix_tree_load_root(root, &child, &maxindex);

	/* Make sure the tree is high enough.  */
	अगर (max > maxindex) अणु
		पूर्णांक error = radix_tree_extend(root, gfp, max, shअगरt);
		अगर (error < 0)
			वापस error;
		shअगरt = error;
		child = rcu_dereference_raw(root->xa_head);
	पूर्ण

	जबतक (shअगरt > 0) अणु
		shअगरt -= RADIX_TREE_MAP_SHIFT;
		अगर (child == शून्य) अणु
			/* Have to add a child node.  */
			child = radix_tree_node_alloc(gfp, node, root, shअगरt,
							offset, 0, 0);
			अगर (!child)
				वापस -ENOMEM;
			rcu_assign_poपूर्णांकer(*slot, node_to_entry(child));
			अगर (node)
				node->count++;
		पूर्ण अन्यथा अगर (!radix_tree_is_पूर्णांकernal_node(child))
			अवरोध;

		/* Go a level करोwn */
		node = entry_to_node(child);
		offset = radix_tree_descend(node, &child, index);
		slot = &node->slots[offset];
	पूर्ण

	अगर (nodep)
		*nodep = node;
	अगर (slotp)
		*slotp = slot;
	वापस 0;
पूर्ण

/*
 * Free any nodes below this node.  The tree is presumed to not need
 * shrinking, and any user data in the tree is presumed to not need a
 * deकाष्ठाor called on it.  If we need to add a deकाष्ठाor, we can
 * add that functionality later.  Note that we may not clear tags or
 * slots from the tree as an RCU walker may still have a poपूर्णांकer पूर्णांकo
 * this subtree.  We could replace the entries with RADIX_TREE_RETRY,
 * but we'll still have to clear those in rcu_मुक्त.
 */
अटल व्योम radix_tree_मुक्त_nodes(काष्ठा radix_tree_node *node)
अणु
	अचिन्हित offset = 0;
	काष्ठा radix_tree_node *child = entry_to_node(node);

	क्रम (;;) अणु
		व्योम *entry = rcu_dereference_raw(child->slots[offset]);
		अगर (xa_is_node(entry) && child->shअगरt) अणु
			child = entry_to_node(entry);
			offset = 0;
			जारी;
		पूर्ण
		offset++;
		जबतक (offset == RADIX_TREE_MAP_SIZE) अणु
			काष्ठा radix_tree_node *old = child;
			offset = child->offset + 1;
			child = child->parent;
			WARN_ON_ONCE(!list_empty(&old->निजी_list));
			radix_tree_node_मुक्त(old);
			अगर (old == entry_to_node(node))
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक insert_entries(काष्ठा radix_tree_node *node,
		व्योम __rcu **slot, व्योम *item, bool replace)
अणु
	अगर (*slot)
		वापस -EEXIST;
	rcu_assign_poपूर्णांकer(*slot, item);
	अगर (node) अणु
		node->count++;
		अगर (xa_is_value(item))
			node->nr_values++;
	पूर्ण
	वापस 1;
पूर्ण

/**
 *	radix_tree_insert    -    insert पूर्णांकo a radix tree
 *	@root:		radix tree root
 *	@index:		index key
 *	@item:		item to insert
 *
 *	Insert an item पूर्णांकo the radix tree at position @index.
 */
पूर्णांक radix_tree_insert(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index,
			व्योम *item)
अणु
	काष्ठा radix_tree_node *node;
	व्योम __rcu **slot;
	पूर्णांक error;

	BUG_ON(radix_tree_is_पूर्णांकernal_node(item));

	error = __radix_tree_create(root, index, &node, &slot);
	अगर (error)
		वापस error;

	error = insert_entries(node, slot, item, false);
	अगर (error < 0)
		वापस error;

	अगर (node) अणु
		अचिन्हित offset = get_slot_offset(node, slot);
		BUG_ON(tag_get(node, 0, offset));
		BUG_ON(tag_get(node, 1, offset));
		BUG_ON(tag_get(node, 2, offset));
	पूर्ण अन्यथा अणु
		BUG_ON(root_tags_get(root));
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(radix_tree_insert);

/**
 *	__radix_tree_lookup	-	lookup an item in a radix tree
 *	@root:		radix tree root
 *	@index:		index key
 *	@nodep:		वापसs node
 *	@slotp:		वापसs slot
 *
 *	Lookup and वापस the item at position @index in the radix
 *	tree @root.
 *
 *	Until there is more than one item in the tree, no nodes are
 *	allocated and @root->xa_head is used as a direct slot instead of
 *	poपूर्णांकing to a node, in which हाल *@nodep will be शून्य.
 */
व्योम *__radix_tree_lookup(स्थिर काष्ठा radix_tree_root *root,
			  अचिन्हित दीर्घ index, काष्ठा radix_tree_node **nodep,
			  व्योम __rcu ***slotp)
अणु
	काष्ठा radix_tree_node *node, *parent;
	अचिन्हित दीर्घ maxindex;
	व्योम __rcu **slot;

 restart:
	parent = शून्य;
	slot = (व्योम __rcu **)&root->xa_head;
	radix_tree_load_root(root, &node, &maxindex);
	अगर (index > maxindex)
		वापस शून्य;

	जबतक (radix_tree_is_पूर्णांकernal_node(node)) अणु
		अचिन्हित offset;

		parent = entry_to_node(node);
		offset = radix_tree_descend(parent, &node, index);
		slot = parent->slots + offset;
		अगर (node == RADIX_TREE_RETRY)
			जाओ restart;
		अगर (parent->shअगरt == 0)
			अवरोध;
	पूर्ण

	अगर (nodep)
		*nodep = parent;
	अगर (slotp)
		*slotp = slot;
	वापस node;
पूर्ण

/**
 *	radix_tree_lookup_slot    -    lookup a slot in a radix tree
 *	@root:		radix tree root
 *	@index:		index key
 *
 *	Returns:  the slot corresponding to the position @index in the
 *	radix tree @root. This is useful क्रम update-अगर-exists operations.
 *
 *	This function can be called under rcu_पढ़ो_lock अगरf the slot is not
 *	modअगरied by radix_tree_replace_slot, otherwise it must be called
 *	exclusive from other ग_लिखोrs. Any dereference of the slot must be करोne
 *	using radix_tree_deref_slot.
 */
व्योम __rcu **radix_tree_lookup_slot(स्थिर काष्ठा radix_tree_root *root,
				अचिन्हित दीर्घ index)
अणु
	व्योम __rcu **slot;

	अगर (!__radix_tree_lookup(root, index, शून्य, &slot))
		वापस शून्य;
	वापस slot;
पूर्ण
EXPORT_SYMBOL(radix_tree_lookup_slot);

/**
 *	radix_tree_lookup    -    perक्रमm lookup operation on a radix tree
 *	@root:		radix tree root
 *	@index:		index key
 *
 *	Lookup the item at the position @index in the radix tree @root.
 *
 *	This function can be called under rcu_पढ़ो_lock, however the caller
 *	must manage lअगरeबार of leaf nodes (eg. RCU may also be used to मुक्त
 *	them safely). No RCU barriers are required to access or modअगरy the
 *	वापसed item, however.
 */
व्योम *radix_tree_lookup(स्थिर काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index)
अणु
	वापस __radix_tree_lookup(root, index, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL(radix_tree_lookup);

अटल व्योम replace_slot(व्योम __rcu **slot, व्योम *item,
		काष्ठा radix_tree_node *node, पूर्णांक count, पूर्णांक values)
अणु
	अगर (node && (count || values)) अणु
		node->count += count;
		node->nr_values += values;
	पूर्ण

	rcu_assign_poपूर्णांकer(*slot, item);
पूर्ण

अटल bool node_tag_get(स्थिर काष्ठा radix_tree_root *root,
				स्थिर काष्ठा radix_tree_node *node,
				अचिन्हित पूर्णांक tag, अचिन्हित पूर्णांक offset)
अणु
	अगर (node)
		वापस tag_get(node, tag, offset);
	वापस root_tag_get(root, tag);
पूर्ण

/*
 * IDR users want to be able to store शून्य in the tree, so अगर the slot isn't
 * मुक्त, करोn't adjust the count, even if it's transitioning between शून्य and
 * non-शून्य.  For the IDA, we mark slots as being IDR_FREE जबतक they still
 * have empty bits, but it only stores शून्य in slots when they're being
 * deleted.
 */
अटल पूर्णांक calculate_count(काष्ठा radix_tree_root *root,
				काष्ठा radix_tree_node *node, व्योम __rcu **slot,
				व्योम *item, व्योम *old)
अणु
	अगर (is_idr(root)) अणु
		अचिन्हित offset = get_slot_offset(node, slot);
		bool मुक्त = node_tag_get(root, node, IDR_FREE, offset);
		अगर (!मुक्त)
			वापस 0;
		अगर (!old)
			वापस 1;
	पूर्ण
	वापस !!item - !!old;
पूर्ण

/**
 * __radix_tree_replace		- replace item in a slot
 * @root:		radix tree root
 * @node:		poपूर्णांकer to tree node
 * @slot:		poपूर्णांकer to slot in @node
 * @item:		new item to store in the slot.
 *
 * For use with __radix_tree_lookup().  Caller must hold tree ग_लिखो locked
 * across slot lookup and replacement.
 */
व्योम __radix_tree_replace(काष्ठा radix_tree_root *root,
			  काष्ठा radix_tree_node *node,
			  व्योम __rcu **slot, व्योम *item)
अणु
	व्योम *old = rcu_dereference_raw(*slot);
	पूर्णांक values = !!xa_is_value(item) - !!xa_is_value(old);
	पूर्णांक count = calculate_count(root, node, slot, item, old);

	/*
	 * This function supports replacing value entries and
	 * deleting entries, but that needs accounting against the
	 * node unless the slot is root->xa_head.
	 */
	WARN_ON_ONCE(!node && (slot != (व्योम __rcu **)&root->xa_head) &&
			(count || values));
	replace_slot(slot, item, node, count, values);

	अगर (!node)
		वापस;

	delete_node(root, node);
पूर्ण

/**
 * radix_tree_replace_slot	- replace item in a slot
 * @root:	radix tree root
 * @slot:	poपूर्णांकer to slot
 * @item:	new item to store in the slot.
 *
 * For use with radix_tree_lookup_slot() and
 * radix_tree_gang_lookup_tag_slot().  Caller must hold tree ग_लिखो locked
 * across slot lookup and replacement.
 *
 * NOTE: This cannot be used to चयन between non-entries (empty slots),
 * regular entries, and value entries, as that requires accounting
 * inside the radix tree node. When चयनing from one type of entry or
 * deleting, use __radix_tree_lookup() and __radix_tree_replace() or
 * radix_tree_iter_replace().
 */
व्योम radix_tree_replace_slot(काष्ठा radix_tree_root *root,
			     व्योम __rcu **slot, व्योम *item)
अणु
	__radix_tree_replace(root, शून्य, slot, item);
पूर्ण
EXPORT_SYMBOL(radix_tree_replace_slot);

/**
 * radix_tree_iter_replace - replace item in a slot
 * @root:	radix tree root
 * @iter:	iterator state
 * @slot:	poपूर्णांकer to slot
 * @item:	new item to store in the slot.
 *
 * For use with radix_tree_क्रम_each_slot().
 * Caller must hold tree ग_लिखो locked.
 */
व्योम radix_tree_iter_replace(काष्ठा radix_tree_root *root,
				स्थिर काष्ठा radix_tree_iter *iter,
				व्योम __rcu **slot, व्योम *item)
अणु
	__radix_tree_replace(root, iter->node, slot, item);
पूर्ण

अटल व्योम node_tag_set(काष्ठा radix_tree_root *root,
				काष्ठा radix_tree_node *node,
				अचिन्हित पूर्णांक tag, अचिन्हित पूर्णांक offset)
अणु
	जबतक (node) अणु
		अगर (tag_get(node, tag, offset))
			वापस;
		tag_set(node, tag, offset);
		offset = node->offset;
		node = node->parent;
	पूर्ण

	अगर (!root_tag_get(root, tag))
		root_tag_set(root, tag);
पूर्ण

/**
 *	radix_tree_tag_set - set a tag on a radix tree node
 *	@root:		radix tree root
 *	@index:		index key
 *	@tag:		tag index
 *
 *	Set the search tag (which must be < RADIX_TREE_MAX_TAGS)
 *	corresponding to @index in the radix tree.  From
 *	the root all the way करोwn to the leaf node.
 *
 *	Returns the address of the tagged item.  Setting a tag on a not-present
 *	item is a bug.
 */
व्योम *radix_tree_tag_set(काष्ठा radix_tree_root *root,
			अचिन्हित दीर्घ index, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा radix_tree_node *node, *parent;
	अचिन्हित दीर्घ maxindex;

	radix_tree_load_root(root, &node, &maxindex);
	BUG_ON(index > maxindex);

	जबतक (radix_tree_is_पूर्णांकernal_node(node)) अणु
		अचिन्हित offset;

		parent = entry_to_node(node);
		offset = radix_tree_descend(parent, &node, index);
		BUG_ON(!node);

		अगर (!tag_get(parent, tag, offset))
			tag_set(parent, tag, offset);
	पूर्ण

	/* set the root's tag bit */
	अगर (!root_tag_get(root, tag))
		root_tag_set(root, tag);

	वापस node;
पूर्ण
EXPORT_SYMBOL(radix_tree_tag_set);

अटल व्योम node_tag_clear(काष्ठा radix_tree_root *root,
				काष्ठा radix_tree_node *node,
				अचिन्हित पूर्णांक tag, अचिन्हित पूर्णांक offset)
अणु
	जबतक (node) अणु
		अगर (!tag_get(node, tag, offset))
			वापस;
		tag_clear(node, tag, offset);
		अगर (any_tag_set(node, tag))
			वापस;

		offset = node->offset;
		node = node->parent;
	पूर्ण

	/* clear the root's tag bit */
	अगर (root_tag_get(root, tag))
		root_tag_clear(root, tag);
पूर्ण

/**
 *	radix_tree_tag_clear - clear a tag on a radix tree node
 *	@root:		radix tree root
 *	@index:		index key
 *	@tag:		tag index
 *
 *	Clear the search tag (which must be < RADIX_TREE_MAX_TAGS)
 *	corresponding to @index in the radix tree.  If this causes
 *	the leaf node to have no tags set then clear the tag in the
 *	next-to-leaf node, etc.
 *
 *	Returns the address of the tagged item on success, अन्यथा शून्य.  ie:
 *	has the same वापस value and semantics as radix_tree_lookup().
 */
व्योम *radix_tree_tag_clear(काष्ठा radix_tree_root *root,
			अचिन्हित दीर्घ index, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा radix_tree_node *node, *parent;
	अचिन्हित दीर्घ maxindex;
	पूर्णांक offset;

	radix_tree_load_root(root, &node, &maxindex);
	अगर (index > maxindex)
		वापस शून्य;

	parent = शून्य;

	जबतक (radix_tree_is_पूर्णांकernal_node(node)) अणु
		parent = entry_to_node(node);
		offset = radix_tree_descend(parent, &node, index);
	पूर्ण

	अगर (node)
		node_tag_clear(root, parent, tag, offset);

	वापस node;
पूर्ण
EXPORT_SYMBOL(radix_tree_tag_clear);

/**
  * radix_tree_iter_tag_clear - clear a tag on the current iterator entry
  * @root: radix tree root
  * @iter: iterator state
  * @tag: tag to clear
  */
व्योम radix_tree_iter_tag_clear(काष्ठा radix_tree_root *root,
			स्थिर काष्ठा radix_tree_iter *iter, अचिन्हित पूर्णांक tag)
अणु
	node_tag_clear(root, iter->node, tag, iter_offset(iter));
पूर्ण

/**
 * radix_tree_tag_get - get a tag on a radix tree node
 * @root:		radix tree root
 * @index:		index key
 * @tag:		tag index (< RADIX_TREE_MAX_TAGS)
 *
 * Return values:
 *
 *  0: tag not present or not set
 *  1: tag set
 *
 * Note that the वापस value of this function may not be relied on, even अगर
 * the RCU lock is held, unless tag modअगरication and node deletion are excluded
 * from concurrency.
 */
पूर्णांक radix_tree_tag_get(स्थिर काष्ठा radix_tree_root *root,
			अचिन्हित दीर्घ index, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा radix_tree_node *node, *parent;
	अचिन्हित दीर्घ maxindex;

	अगर (!root_tag_get(root, tag))
		वापस 0;

	radix_tree_load_root(root, &node, &maxindex);
	अगर (index > maxindex)
		वापस 0;

	जबतक (radix_tree_is_पूर्णांकernal_node(node)) अणु
		अचिन्हित offset;

		parent = entry_to_node(node);
		offset = radix_tree_descend(parent, &node, index);

		अगर (!tag_get(parent, tag, offset))
			वापस 0;
		अगर (node == RADIX_TREE_RETRY)
			अवरोध;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL(radix_tree_tag_get);

/* Conकाष्ठा iter->tags bit-mask from node->tags[tag] array */
अटल व्योम set_iter_tags(काष्ठा radix_tree_iter *iter,
				काष्ठा radix_tree_node *node, अचिन्हित offset,
				अचिन्हित tag)
अणु
	अचिन्हित tag_दीर्घ = offset / BITS_PER_LONG;
	अचिन्हित tag_bit  = offset % BITS_PER_LONG;

	अगर (!node) अणु
		iter->tags = 1;
		वापस;
	पूर्ण

	iter->tags = node->tags[tag][tag_दीर्घ] >> tag_bit;

	/* This never happens अगर RADIX_TREE_TAG_LONGS == 1 */
	अगर (tag_दीर्घ < RADIX_TREE_TAG_LONGS - 1) अणु
		/* Pick tags from next element */
		अगर (tag_bit)
			iter->tags |= node->tags[tag][tag_दीर्घ + 1] <<
						(BITS_PER_LONG - tag_bit);
		/* Clip chunk size, here only BITS_PER_LONG tags */
		iter->next_index = __radix_tree_iter_add(iter, BITS_PER_LONG);
	पूर्ण
पूर्ण

व्योम __rcu **radix_tree_iter_resume(व्योम __rcu **slot,
					काष्ठा radix_tree_iter *iter)
अणु
	slot++;
	iter->index = __radix_tree_iter_add(iter, 1);
	iter->next_index = iter->index;
	iter->tags = 0;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(radix_tree_iter_resume);

/**
 * radix_tree_next_chunk - find next chunk of slots क्रम iteration
 *
 * @root:	radix tree root
 * @iter:	iterator state
 * @flags:	RADIX_TREE_ITER_* flags and tag index
 * Returns:	poपूर्णांकer to chunk first slot, or शून्य अगर iteration is over
 */
व्योम __rcu **radix_tree_next_chunk(स्थिर काष्ठा radix_tree_root *root,
			     काष्ठा radix_tree_iter *iter, अचिन्हित flags)
अणु
	अचिन्हित tag = flags & RADIX_TREE_ITER_TAG_MASK;
	काष्ठा radix_tree_node *node, *child;
	अचिन्हित दीर्घ index, offset, maxindex;

	अगर ((flags & RADIX_TREE_ITER_TAGGED) && !root_tag_get(root, tag))
		वापस शून्य;

	/*
	 * Catch next_index overflow after ~0UL. iter->index never overflows
	 * during iterating; it can be zero only at the beginning.
	 * And we cannot overflow iter->next_index in a single step,
	 * because RADIX_TREE_MAP_SHIFT < BITS_PER_LONG.
	 *
	 * This condition also used by radix_tree_next_slot() to stop
	 * contiguous iterating, and क्रमbid चयनing to the next chunk.
	 */
	index = iter->next_index;
	अगर (!index && iter->index)
		वापस शून्य;

 restart:
	radix_tree_load_root(root, &child, &maxindex);
	अगर (index > maxindex)
		वापस शून्य;
	अगर (!child)
		वापस शून्य;

	अगर (!radix_tree_is_पूर्णांकernal_node(child)) अणु
		/* Single-slot tree */
		iter->index = index;
		iter->next_index = maxindex + 1;
		iter->tags = 1;
		iter->node = शून्य;
		वापस (व्योम __rcu **)&root->xa_head;
	पूर्ण

	करो अणु
		node = entry_to_node(child);
		offset = radix_tree_descend(node, &child, index);

		अगर ((flags & RADIX_TREE_ITER_TAGGED) ?
				!tag_get(node, tag, offset) : !child) अणु
			/* Hole detected */
			अगर (flags & RADIX_TREE_ITER_CONTIG)
				वापस शून्य;

			अगर (flags & RADIX_TREE_ITER_TAGGED)
				offset = radix_tree_find_next_bit(node, tag,
						offset + 1);
			अन्यथा
				जबतक (++offset	< RADIX_TREE_MAP_SIZE) अणु
					व्योम *slot = rcu_dereference_raw(
							node->slots[offset]);
					अगर (slot)
						अवरोध;
				पूर्ण
			index &= ~node_maxindex(node);
			index += offset << node->shअगरt;
			/* Overflow after ~0UL */
			अगर (!index)
				वापस शून्य;
			अगर (offset == RADIX_TREE_MAP_SIZE)
				जाओ restart;
			child = rcu_dereference_raw(node->slots[offset]);
		पूर्ण

		अगर (!child)
			जाओ restart;
		अगर (child == RADIX_TREE_RETRY)
			अवरोध;
	पूर्ण जबतक (node->shअगरt && radix_tree_is_पूर्णांकernal_node(child));

	/* Update the iterator state */
	iter->index = (index &~ node_maxindex(node)) | offset;
	iter->next_index = (index | node_maxindex(node)) + 1;
	iter->node = node;

	अगर (flags & RADIX_TREE_ITER_TAGGED)
		set_iter_tags(iter, node, offset, tag);

	वापस node->slots + offset;
पूर्ण
EXPORT_SYMBOL(radix_tree_next_chunk);

/**
 *	radix_tree_gang_lookup - perक्रमm multiple lookup on a radix tree
 *	@root:		radix tree root
 *	@results:	where the results of the lookup are placed
 *	@first_index:	start the lookup from this key
 *	@max_items:	place up to this many items at *results
 *
 *	Perक्रमms an index-ascending scan of the tree क्रम present items.  Places
 *	them at *@results and वापसs the number of items which were placed at
 *	*@results.
 *
 *	The implementation is naive.
 *
 *	Like radix_tree_lookup, radix_tree_gang_lookup may be called under
 *	rcu_पढ़ो_lock. In this हाल, rather than the वापसed results being
 *	an atomic snapshot of the tree at a single poपूर्णांक in समय, the
 *	semantics of an RCU रक्षित gang lookup are as though multiple
 *	radix_tree_lookups have been issued in inभागidual locks, and results
 *	stored in 'results'.
 */
अचिन्हित पूर्णांक
radix_tree_gang_lookup(स्थिर काष्ठा radix_tree_root *root, व्योम **results,
			अचिन्हित दीर्घ first_index, अचिन्हित पूर्णांक max_items)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;
	अचिन्हित पूर्णांक ret = 0;

	अगर (unlikely(!max_items))
		वापस 0;

	radix_tree_क्रम_each_slot(slot, root, &iter, first_index) अणु
		results[ret] = rcu_dereference_raw(*slot);
		अगर (!results[ret])
			जारी;
		अगर (radix_tree_is_पूर्णांकernal_node(results[ret])) अणु
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
		अगर (++ret == max_items)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(radix_tree_gang_lookup);

/**
 *	radix_tree_gang_lookup_tag - perक्रमm multiple lookup on a radix tree
 *	                             based on a tag
 *	@root:		radix tree root
 *	@results:	where the results of the lookup are placed
 *	@first_index:	start the lookup from this key
 *	@max_items:	place up to this many items at *results
 *	@tag:		the tag index (< RADIX_TREE_MAX_TAGS)
 *
 *	Perक्रमms an index-ascending scan of the tree क्रम present items which
 *	have the tag indexed by @tag set.  Places the items at *@results and
 *	वापसs the number of items which were placed at *@results.
 */
अचिन्हित पूर्णांक
radix_tree_gang_lookup_tag(स्थिर काष्ठा radix_tree_root *root, व्योम **results,
		अचिन्हित दीर्घ first_index, अचिन्हित पूर्णांक max_items,
		अचिन्हित पूर्णांक tag)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;
	अचिन्हित पूर्णांक ret = 0;

	अगर (unlikely(!max_items))
		वापस 0;

	radix_tree_क्रम_each_tagged(slot, root, &iter, first_index, tag) अणु
		results[ret] = rcu_dereference_raw(*slot);
		अगर (!results[ret])
			जारी;
		अगर (radix_tree_is_पूर्णांकernal_node(results[ret])) अणु
			slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
		अगर (++ret == max_items)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(radix_tree_gang_lookup_tag);

/**
 *	radix_tree_gang_lookup_tag_slot - perक्रमm multiple slot lookup on a
 *					  radix tree based on a tag
 *	@root:		radix tree root
 *	@results:	where the results of the lookup are placed
 *	@first_index:	start the lookup from this key
 *	@max_items:	place up to this many items at *results
 *	@tag:		the tag index (< RADIX_TREE_MAX_TAGS)
 *
 *	Perक्रमms an index-ascending scan of the tree क्रम present items which
 *	have the tag indexed by @tag set.  Places the slots at *@results and
 *	वापसs the number of slots which were placed at *@results.
 */
अचिन्हित पूर्णांक
radix_tree_gang_lookup_tag_slot(स्थिर काष्ठा radix_tree_root *root,
		व्योम __rcu ***results, अचिन्हित दीर्घ first_index,
		अचिन्हित पूर्णांक max_items, अचिन्हित पूर्णांक tag)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम __rcu **slot;
	अचिन्हित पूर्णांक ret = 0;

	अगर (unlikely(!max_items))
		वापस 0;

	radix_tree_क्रम_each_tagged(slot, root, &iter, first_index, tag) अणु
		results[ret] = slot;
		अगर (++ret == max_items)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(radix_tree_gang_lookup_tag_slot);

अटल bool __radix_tree_delete(काष्ठा radix_tree_root *root,
				काष्ठा radix_tree_node *node, व्योम __rcu **slot)
अणु
	व्योम *old = rcu_dereference_raw(*slot);
	पूर्णांक values = xa_is_value(old) ? -1 : 0;
	अचिन्हित offset = get_slot_offset(node, slot);
	पूर्णांक tag;

	अगर (is_idr(root))
		node_tag_set(root, node, IDR_FREE, offset);
	अन्यथा
		क्रम (tag = 0; tag < RADIX_TREE_MAX_TAGS; tag++)
			node_tag_clear(root, node, tag, offset);

	replace_slot(slot, शून्य, node, -1, values);
	वापस node && delete_node(root, node);
पूर्ण

/**
 * radix_tree_iter_delete - delete the entry at this iterator position
 * @root: radix tree root
 * @iter: iterator state
 * @slot: poपूर्णांकer to slot
 *
 * Delete the entry at the position currently poपूर्णांकed to by the iterator.
 * This may result in the current node being मुक्तd; अगर it is, the iterator
 * is advanced so that it will not reference the मुक्तd memory.  This
 * function may be called without any locking अगर there are no other thपढ़ोs
 * which can access this tree.
 */
व्योम radix_tree_iter_delete(काष्ठा radix_tree_root *root,
				काष्ठा radix_tree_iter *iter, व्योम __rcu **slot)
अणु
	अगर (__radix_tree_delete(root, iter->node, slot))
		iter->index = iter->next_index;
पूर्ण
EXPORT_SYMBOL(radix_tree_iter_delete);

/**
 * radix_tree_delete_item - delete an item from a radix tree
 * @root: radix tree root
 * @index: index key
 * @item: expected item
 *
 * Remove @item at @index from the radix tree rooted at @root.
 *
 * Return: the deleted entry, or %शून्य अगर it was not present
 * or the entry at the given @index was not @item.
 */
व्योम *radix_tree_delete_item(काष्ठा radix_tree_root *root,
			     अचिन्हित दीर्घ index, व्योम *item)
अणु
	काष्ठा radix_tree_node *node = शून्य;
	व्योम __rcu **slot = शून्य;
	व्योम *entry;

	entry = __radix_tree_lookup(root, index, &node, &slot);
	अगर (!slot)
		वापस शून्य;
	अगर (!entry && (!is_idr(root) || node_tag_get(root, node, IDR_FREE,
						get_slot_offset(node, slot))))
		वापस शून्य;

	अगर (item && entry != item)
		वापस शून्य;

	__radix_tree_delete(root, node, slot);

	वापस entry;
पूर्ण
EXPORT_SYMBOL(radix_tree_delete_item);

/**
 * radix_tree_delete - delete an entry from a radix tree
 * @root: radix tree root
 * @index: index key
 *
 * Remove the entry at @index from the radix tree rooted at @root.
 *
 * Return: The deleted entry, or %शून्य अगर it was not present.
 */
व्योम *radix_tree_delete(काष्ठा radix_tree_root *root, अचिन्हित दीर्घ index)
अणु
	वापस radix_tree_delete_item(root, index, शून्य);
पूर्ण
EXPORT_SYMBOL(radix_tree_delete);

/**
 *	radix_tree_tagged - test whether any items in the tree are tagged
 *	@root:		radix tree root
 *	@tag:		tag to test
 */
पूर्णांक radix_tree_tagged(स्थिर काष्ठा radix_tree_root *root, अचिन्हित पूर्णांक tag)
अणु
	वापस root_tag_get(root, tag);
पूर्ण
EXPORT_SYMBOL(radix_tree_tagged);

/**
 * idr_preload - preload क्रम idr_alloc()
 * @gfp_mask: allocation mask to use क्रम preloading
 *
 * Pपुनः_स्मृतिate memory to use क्रम the next call to idr_alloc().  This function
 * वापसs with preemption disabled.  It will be enabled by idr_preload_end().
 */
व्योम idr_preload(gfp_t gfp_mask)
अणु
	अगर (__radix_tree_preload(gfp_mask, IDR_PRELOAD_SIZE))
		local_lock(&radix_tree_preloads.lock);
पूर्ण
EXPORT_SYMBOL(idr_preload);

व्योम __rcu **idr_get_मुक्त(काष्ठा radix_tree_root *root,
			      काष्ठा radix_tree_iter *iter, gfp_t gfp,
			      अचिन्हित दीर्घ max)
अणु
	काष्ठा radix_tree_node *node = शून्य, *child;
	व्योम __rcu **slot = (व्योम __rcu **)&root->xa_head;
	अचिन्हित दीर्घ maxindex, start = iter->next_index;
	अचिन्हित पूर्णांक shअगरt, offset = 0;

 grow:
	shअगरt = radix_tree_load_root(root, &child, &maxindex);
	अगर (!radix_tree_tagged(root, IDR_FREE))
		start = max(start, maxindex + 1);
	अगर (start > max)
		वापस ERR_PTR(-ENOSPC);

	अगर (start > maxindex) अणु
		पूर्णांक error = radix_tree_extend(root, gfp, start, shअगरt);
		अगर (error < 0)
			वापस ERR_PTR(error);
		shअगरt = error;
		child = rcu_dereference_raw(root->xa_head);
	पूर्ण
	अगर (start == 0 && shअगरt == 0)
		shअगरt = RADIX_TREE_MAP_SHIFT;

	जबतक (shअगरt) अणु
		shअगरt -= RADIX_TREE_MAP_SHIFT;
		अगर (child == शून्य) अणु
			/* Have to add a child node.  */
			child = radix_tree_node_alloc(gfp, node, root, shअगरt,
							offset, 0, 0);
			अगर (!child)
				वापस ERR_PTR(-ENOMEM);
			all_tag_set(child, IDR_FREE);
			rcu_assign_poपूर्णांकer(*slot, node_to_entry(child));
			अगर (node)
				node->count++;
		पूर्ण अन्यथा अगर (!radix_tree_is_पूर्णांकernal_node(child))
			अवरोध;

		node = entry_to_node(child);
		offset = radix_tree_descend(node, &child, start);
		अगर (!tag_get(node, IDR_FREE, offset)) अणु
			offset = radix_tree_find_next_bit(node, IDR_FREE,
							offset + 1);
			start = next_index(start, node, offset);
			अगर (start > max || start == 0)
				वापस ERR_PTR(-ENOSPC);
			जबतक (offset == RADIX_TREE_MAP_SIZE) अणु
				offset = node->offset + 1;
				node = node->parent;
				अगर (!node)
					जाओ grow;
				shअगरt = node->shअगरt;
			पूर्ण
			child = rcu_dereference_raw(node->slots[offset]);
		पूर्ण
		slot = &node->slots[offset];
	पूर्ण

	iter->index = start;
	अगर (node)
		iter->next_index = 1 + min(max, (start | node_maxindex(node)));
	अन्यथा
		iter->next_index = 1;
	iter->node = node;
	set_iter_tags(iter, node, offset, IDR_FREE);

	वापस slot;
पूर्ण

/**
 * idr_destroy - release all पूर्णांकernal memory from an IDR
 * @idr: idr handle
 *
 * After this function is called, the IDR is empty, and may be reused or
 * the data काष्ठाure containing it may be मुक्तd.
 *
 * A typical clean-up sequence क्रम objects stored in an idr tree will use
 * idr_क्रम_each() to मुक्त all objects, अगर necessary, then idr_destroy() to
 * मुक्त the memory used to keep track of those objects.
 */
व्योम idr_destroy(काष्ठा idr *idr)
अणु
	काष्ठा radix_tree_node *node = rcu_dereference_raw(idr->idr_rt.xa_head);
	अगर (radix_tree_is_पूर्णांकernal_node(node))
		radix_tree_मुक्त_nodes(node);
	idr->idr_rt.xa_head = शून्य;
	root_tag_set(&idr->idr_rt, IDR_FREE);
पूर्ण
EXPORT_SYMBOL(idr_destroy);

अटल व्योम
radix_tree_node_ctor(व्योम *arg)
अणु
	काष्ठा radix_tree_node *node = arg;

	स_रखो(node, 0, माप(*node));
	INIT_LIST_HEAD(&node->निजी_list);
पूर्ण

अटल पूर्णांक radix_tree_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा radix_tree_preload *rtp;
	काष्ठा radix_tree_node *node;

	/* Free per-cpu pool of preloaded nodes */
	rtp = &per_cpu(radix_tree_preloads, cpu);
	जबतक (rtp->nr) अणु
		node = rtp->nodes;
		rtp->nodes = node->parent;
		kmem_cache_मुक्त(radix_tree_node_cachep, node);
		rtp->nr--;
	पूर्ण
	वापस 0;
पूर्ण

व्योम __init radix_tree_init(व्योम)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(RADIX_TREE_MAX_TAGS + __GFP_BITS_SHIFT > 32);
	BUILD_BUG_ON(ROOT_IS_IDR & ~GFP_ZONEMASK);
	BUILD_BUG_ON(XA_CHUNK_SIZE > 255);
	radix_tree_node_cachep = kmem_cache_create("radix_tree_node",
			माप(काष्ठा radix_tree_node), 0,
			SLAB_PANIC | SLAB_RECLAIM_ACCOUNT,
			radix_tree_node_ctor);
	ret = cpuhp_setup_state_nocalls(CPUHP_RADIX_DEAD, "lib/radix:dead",
					शून्य, radix_tree_cpu_dead);
	WARN_ON(ret < 0);
पूर्ण
