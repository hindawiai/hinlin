<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश "ctree.h"
#समावेश "volumes.h"
#समावेश "extent_map.h"
#समावेश "compression.h"


अटल काष्ठा kmem_cache *extent_map_cache;

पूर्णांक __init extent_map_init(व्योम)
अणु
	extent_map_cache = kmem_cache_create("btrfs_extent_map",
			माप(काष्ठा extent_map), 0,
			SLAB_MEM_SPREAD, शून्य);
	अगर (!extent_map_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम __cold extent_map_निकास(व्योम)
अणु
	kmem_cache_destroy(extent_map_cache);
पूर्ण

/**
 * extent_map_tree_init - initialize extent map tree
 * @tree:		tree to initialize
 *
 * Initialize the extent tree @tree.  Should be called क्रम each new inode
 * or other user of the extent_map पूर्णांकerface.
 */
व्योम extent_map_tree_init(काष्ठा extent_map_tree *tree)
अणु
	tree->map = RB_ROOT_CACHED;
	INIT_LIST_HEAD(&tree->modअगरied_extents);
	rwlock_init(&tree->lock);
पूर्ण

/**
 * alloc_extent_map - allocate new extent map काष्ठाure
 *
 * Allocate a new extent_map काष्ठाure.  The new काष्ठाure is
 * वापसed with a reference count of one and needs to be
 * मुक्तd using मुक्त_extent_map()
 */
काष्ठा extent_map *alloc_extent_map(व्योम)
अणु
	काष्ठा extent_map *em;
	em = kmem_cache_zalloc(extent_map_cache, GFP_NOFS);
	अगर (!em)
		वापस शून्य;
	RB_CLEAR_NODE(&em->rb_node);
	em->flags = 0;
	em->compress_type = BTRFS_COMPRESS_NONE;
	em->generation = 0;
	refcount_set(&em->refs, 1);
	INIT_LIST_HEAD(&em->list);
	वापस em;
पूर्ण

/**
 * मुक्त_extent_map - drop reference count of an extent_map
 * @em:		extent map being released
 *
 * Drops the reference out on @em by one and मुक्त the काष्ठाure
 * अगर the reference count hits zero.
 */
व्योम मुक्त_extent_map(काष्ठा extent_map *em)
अणु
	अगर (!em)
		वापस;
	WARN_ON(refcount_पढ़ो(&em->refs) == 0);
	अगर (refcount_dec_and_test(&em->refs)) अणु
		WARN_ON(extent_map_in_tree(em));
		WARN_ON(!list_empty(&em->list));
		अगर (test_bit(EXTENT_FLAG_FS_MAPPING, &em->flags))
			kमुक्त(em->map_lookup);
		kmem_cache_मुक्त(extent_map_cache, em);
	पूर्ण
पूर्ण

/* simple helper to करो math around the end of an extent, handling wrap */
अटल u64 range_end(u64 start, u64 len)
अणु
	अगर (start + len < start)
		वापस (u64)-1;
	वापस start + len;
पूर्ण

अटल पूर्णांक tree_insert(काष्ठा rb_root_cached *root, काष्ठा extent_map *em)
अणु
	काष्ठा rb_node **p = &root->rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा extent_map *entry = शून्य;
	काष्ठा rb_node *orig_parent = शून्य;
	u64 end = range_end(em->start, em->len);
	bool lefपंचांगost = true;

	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा extent_map, rb_node);

		अगर (em->start < entry->start) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (em->start >= extent_map_end(entry)) अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण अन्यथा अणु
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	orig_parent = parent;
	जबतक (parent && em->start >= extent_map_end(entry)) अणु
		parent = rb_next(parent);
		entry = rb_entry(parent, काष्ठा extent_map, rb_node);
	पूर्ण
	अगर (parent)
		अगर (end > entry->start && em->start < extent_map_end(entry))
			वापस -EEXIST;

	parent = orig_parent;
	entry = rb_entry(parent, काष्ठा extent_map, rb_node);
	जबतक (parent && em->start < entry->start) अणु
		parent = rb_prev(parent);
		entry = rb_entry(parent, काष्ठा extent_map, rb_node);
	पूर्ण
	अगर (parent)
		अगर (end > entry->start && em->start < extent_map_end(entry))
			वापस -EEXIST;

	rb_link_node(&em->rb_node, orig_parent, p);
	rb_insert_color_cached(&em->rb_node, root, lefपंचांगost);
	वापस 0;
पूर्ण

/*
 * search through the tree क्रम an extent_map with a given offset.  If
 * it can't be found, try to find some neighboring extents
 */
अटल काष्ठा rb_node *__tree_search(काष्ठा rb_root *root, u64 offset,
				     काष्ठा rb_node **prev_ret,
				     काष्ठा rb_node **next_ret)
अणु
	काष्ठा rb_node *n = root->rb_node;
	काष्ठा rb_node *prev = शून्य;
	काष्ठा rb_node *orig_prev = शून्य;
	काष्ठा extent_map *entry;
	काष्ठा extent_map *prev_entry = शून्य;

	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा extent_map, rb_node);
		prev = n;
		prev_entry = entry;

		अगर (offset < entry->start)
			n = n->rb_left;
		अन्यथा अगर (offset >= extent_map_end(entry))
			n = n->rb_right;
		अन्यथा
			वापस n;
	पूर्ण

	अगर (prev_ret) अणु
		orig_prev = prev;
		जबतक (prev && offset >= extent_map_end(prev_entry)) अणु
			prev = rb_next(prev);
			prev_entry = rb_entry(prev, काष्ठा extent_map, rb_node);
		पूर्ण
		*prev_ret = prev;
		prev = orig_prev;
	पूर्ण

	अगर (next_ret) अणु
		prev_entry = rb_entry(prev, काष्ठा extent_map, rb_node);
		जबतक (prev && offset < prev_entry->start) अणु
			prev = rb_prev(prev);
			prev_entry = rb_entry(prev, काष्ठा extent_map, rb_node);
		पूर्ण
		*next_ret = prev;
	पूर्ण
	वापस शून्य;
पूर्ण

/* check to see अगर two extent_map काष्ठाs are adjacent and safe to merge */
अटल पूर्णांक mergable_maps(काष्ठा extent_map *prev, काष्ठा extent_map *next)
अणु
	अगर (test_bit(EXTENT_FLAG_PINNED, &prev->flags))
		वापस 0;

	/*
	 * करोn't merge compressed extents, we need to know their
	 * actual size
	 */
	अगर (test_bit(EXTENT_FLAG_COMPRESSED, &prev->flags))
		वापस 0;

	अगर (test_bit(EXTENT_FLAG_LOGGING, &prev->flags) ||
	    test_bit(EXTENT_FLAG_LOGGING, &next->flags))
		वापस 0;

	/*
	 * We करोn't want to merge stuff that hasn't been written to the log yet
	 * since it may not reflect exactly what is on disk, and that would be
	 * bad.
	 */
	अगर (!list_empty(&prev->list) || !list_empty(&next->list))
		वापस 0;

	ASSERT(next->block_start != EXTENT_MAP_DELALLOC &&
	       prev->block_start != EXTENT_MAP_DELALLOC);

	अगर (prev->map_lookup || next->map_lookup)
		ASSERT(test_bit(EXTENT_FLAG_FS_MAPPING, &prev->flags) &&
		       test_bit(EXTENT_FLAG_FS_MAPPING, &next->flags));

	अगर (extent_map_end(prev) == next->start &&
	    prev->flags == next->flags &&
	    prev->map_lookup == next->map_lookup &&
	    ((next->block_start == EXTENT_MAP_HOLE &&
	      prev->block_start == EXTENT_MAP_HOLE) ||
	     (next->block_start == EXTENT_MAP_INLINE &&
	      prev->block_start == EXTENT_MAP_INLINE) ||
	     (next->block_start < EXTENT_MAP_LAST_BYTE - 1 &&
	      next->block_start == extent_map_block_end(prev)))) अणु
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम try_merge_map(काष्ठा extent_map_tree *tree, काष्ठा extent_map *em)
अणु
	काष्ठा extent_map *merge = शून्य;
	काष्ठा rb_node *rb;

	/*
	 * We can't modअगरy an extent map that is in the tree and that is being
	 * used by another task, as it can cause that other task to see it in
	 * inconsistent state during the merging. We always have 1 reference क्रम
	 * the tree and 1 क्रम this task (which is unpinning the extent map or
	 * clearing the logging flag), so anything > 2 means it's being used by
	 * other tasks too.
	 */
	अगर (refcount_पढ़ो(&em->refs) > 2)
		वापस;

	अगर (em->start != 0) अणु
		rb = rb_prev(&em->rb_node);
		अगर (rb)
			merge = rb_entry(rb, काष्ठा extent_map, rb_node);
		अगर (rb && mergable_maps(merge, em)) अणु
			em->start = merge->start;
			em->orig_start = merge->orig_start;
			em->len += merge->len;
			em->block_len += merge->block_len;
			em->block_start = merge->block_start;
			em->mod_len = (em->mod_len + em->mod_start) - merge->mod_start;
			em->mod_start = merge->mod_start;
			em->generation = max(em->generation, merge->generation);

			rb_erase_cached(&merge->rb_node, &tree->map);
			RB_CLEAR_NODE(&merge->rb_node);
			मुक्त_extent_map(merge);
		पूर्ण
	पूर्ण

	rb = rb_next(&em->rb_node);
	अगर (rb)
		merge = rb_entry(rb, काष्ठा extent_map, rb_node);
	अगर (rb && mergable_maps(em, merge)) अणु
		em->len += merge->len;
		em->block_len += merge->block_len;
		rb_erase_cached(&merge->rb_node, &tree->map);
		RB_CLEAR_NODE(&merge->rb_node);
		em->mod_len = (merge->mod_start + merge->mod_len) - em->mod_start;
		em->generation = max(em->generation, merge->generation);
		मुक्त_extent_map(merge);
	पूर्ण
पूर्ण

/**
 * unpin_extent_cache - unpin an extent from the cache
 * @tree:	tree to unpin the extent in
 * @start:	logical offset in the file
 * @len:	length of the extent
 * @gen:	generation that this extent has been modअगरied in
 *
 * Called after an extent has been written to disk properly.  Set the generation
 * to the generation that actually added the file item to the inode so we know
 * we need to sync this extent when we call fsync().
 */
पूर्णांक unpin_extent_cache(काष्ठा extent_map_tree *tree, u64 start, u64 len,
		       u64 gen)
अणु
	पूर्णांक ret = 0;
	काष्ठा extent_map *em;
	bool pपुनः_स्मृति = false;

	ग_लिखो_lock(&tree->lock);
	em = lookup_extent_mapping(tree, start, len);

	WARN_ON(!em || em->start != start);

	अगर (!em)
		जाओ out;

	em->generation = gen;
	clear_bit(EXTENT_FLAG_PINNED, &em->flags);
	em->mod_start = em->start;
	em->mod_len = em->len;

	अगर (test_bit(EXTENT_FLAG_FILLING, &em->flags)) अणु
		pपुनः_स्मृति = true;
		clear_bit(EXTENT_FLAG_FILLING, &em->flags);
	पूर्ण

	try_merge_map(tree, em);

	अगर (pपुनः_स्मृति) अणु
		em->mod_start = em->start;
		em->mod_len = em->len;
	पूर्ण

	मुक्त_extent_map(em);
out:
	ग_लिखो_unlock(&tree->lock);
	वापस ret;

पूर्ण

व्योम clear_em_logging(काष्ठा extent_map_tree *tree, काष्ठा extent_map *em)
अणु
	clear_bit(EXTENT_FLAG_LOGGING, &em->flags);
	अगर (extent_map_in_tree(em))
		try_merge_map(tree, em);
पूर्ण

अटल अंतरभूत व्योम setup_extent_mapping(काष्ठा extent_map_tree *tree,
					काष्ठा extent_map *em,
					पूर्णांक modअगरied)
अणु
	refcount_inc(&em->refs);
	em->mod_start = em->start;
	em->mod_len = em->len;

	अगर (modअगरied)
		list_move(&em->list, &tree->modअगरied_extents);
	अन्यथा
		try_merge_map(tree, em);
पूर्ण

अटल व्योम extent_map_device_set_bits(काष्ठा extent_map *em, अचिन्हित bits)
अणु
	काष्ठा map_lookup *map = em->map_lookup;
	u64 stripe_size = em->orig_block_len;
	पूर्णांक i;

	क्रम (i = 0; i < map->num_stripes; i++) अणु
		काष्ठा btrfs_bio_stripe *stripe = &map->stripes[i];
		काष्ठा btrfs_device *device = stripe->dev;

		set_extent_bits_noरुको(&device->alloc_state, stripe->physical,
				 stripe->physical + stripe_size - 1, bits);
	पूर्ण
पूर्ण

अटल व्योम extent_map_device_clear_bits(काष्ठा extent_map *em, अचिन्हित bits)
अणु
	काष्ठा map_lookup *map = em->map_lookup;
	u64 stripe_size = em->orig_block_len;
	पूर्णांक i;

	क्रम (i = 0; i < map->num_stripes; i++) अणु
		काष्ठा btrfs_bio_stripe *stripe = &map->stripes[i];
		काष्ठा btrfs_device *device = stripe->dev;

		__clear_extent_bit(&device->alloc_state, stripe->physical,
				   stripe->physical + stripe_size - 1, bits,
				   0, 0, शून्य, GFP_NOWAIT, शून्य);
	पूर्ण
पूर्ण

/**
 * Add new extent map to the extent tree
 *
 * @tree:	tree to insert new map in
 * @em:		map to insert
 * @modअगरied:	indicate whether the given @em should be added to the
 *	        modअगरied list, which indicates the extent needs to be logged
 *
 * Insert @em पूर्णांकo @tree or perक्रमm a simple क्रमward/backward merge with
 * existing mappings.  The extent_map काष्ठा passed in will be inserted
 * पूर्णांकo the tree directly, with an additional reference taken, or a
 * reference dropped अगर the merge attempt was successful.
 */
पूर्णांक add_extent_mapping(काष्ठा extent_map_tree *tree,
		       काष्ठा extent_map *em, पूर्णांक modअगरied)
अणु
	पूर्णांक ret = 0;

	lockdep_निश्चित_held_ग_लिखो(&tree->lock);

	ret = tree_insert(&tree->map, em);
	अगर (ret)
		जाओ out;

	setup_extent_mapping(tree, em, modअगरied);
	अगर (test_bit(EXTENT_FLAG_FS_MAPPING, &em->flags)) अणु
		extent_map_device_set_bits(em, CHUNK_ALLOCATED);
		extent_map_device_clear_bits(em, CHUNK_TRIMMED);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल काष्ठा extent_map *
__lookup_extent_mapping(काष्ठा extent_map_tree *tree,
			u64 start, u64 len, पूर्णांक strict)
अणु
	काष्ठा extent_map *em;
	काष्ठा rb_node *rb_node;
	काष्ठा rb_node *prev = शून्य;
	काष्ठा rb_node *next = शून्य;
	u64 end = range_end(start, len);

	rb_node = __tree_search(&tree->map.rb_root, start, &prev, &next);
	अगर (!rb_node) अणु
		अगर (prev)
			rb_node = prev;
		अन्यथा अगर (next)
			rb_node = next;
		अन्यथा
			वापस शून्य;
	पूर्ण

	em = rb_entry(rb_node, काष्ठा extent_map, rb_node);

	अगर (strict && !(end > em->start && start < extent_map_end(em)))
		वापस शून्य;

	refcount_inc(&em->refs);
	वापस em;
पूर्ण

/**
 * lookup_extent_mapping - lookup extent_map
 * @tree:	tree to lookup in
 * @start:	byte offset to start the search
 * @len:	length of the lookup range
 *
 * Find and वापस the first extent_map काष्ठा in @tree that पूर्णांकersects the
 * [start, len] range.  There may be additional objects in the tree that
 * पूर्णांकersect, so check the object वापसed carefully to make sure that no
 * additional lookups are needed.
 */
काष्ठा extent_map *lookup_extent_mapping(काष्ठा extent_map_tree *tree,
					 u64 start, u64 len)
अणु
	वापस __lookup_extent_mapping(tree, start, len, 1);
पूर्ण

/**
 * search_extent_mapping - find a nearby extent map
 * @tree:	tree to lookup in
 * @start:	byte offset to start the search
 * @len:	length of the lookup range
 *
 * Find and वापस the first extent_map काष्ठा in @tree that पूर्णांकersects the
 * [start, len] range.
 *
 * If one can't be found, any nearby extent may be वापसed
 */
काष्ठा extent_map *search_extent_mapping(काष्ठा extent_map_tree *tree,
					 u64 start, u64 len)
अणु
	वापस __lookup_extent_mapping(tree, start, len, 0);
पूर्ण

/**
 * हटाओ_extent_mapping - हटाओs an extent_map from the extent tree
 * @tree:	extent tree to हटाओ from
 * @em:		extent map being हटाओd
 *
 * Removes @em from @tree.  No reference counts are dropped, and no checks
 * are करोne to see अगर the range is in use
 */
व्योम हटाओ_extent_mapping(काष्ठा extent_map_tree *tree, काष्ठा extent_map *em)
अणु
	WARN_ON(test_bit(EXTENT_FLAG_PINNED, &em->flags));
	rb_erase_cached(&em->rb_node, &tree->map);
	अगर (!test_bit(EXTENT_FLAG_LOGGING, &em->flags))
		list_del_init(&em->list);
	अगर (test_bit(EXTENT_FLAG_FS_MAPPING, &em->flags))
		extent_map_device_clear_bits(em, CHUNK_ALLOCATED);
	RB_CLEAR_NODE(&em->rb_node);
पूर्ण

व्योम replace_extent_mapping(काष्ठा extent_map_tree *tree,
			    काष्ठा extent_map *cur,
			    काष्ठा extent_map *new,
			    पूर्णांक modअगरied)
अणु
	WARN_ON(test_bit(EXTENT_FLAG_PINNED, &cur->flags));
	ASSERT(extent_map_in_tree(cur));
	अगर (!test_bit(EXTENT_FLAG_LOGGING, &cur->flags))
		list_del_init(&cur->list);
	rb_replace_node_cached(&cur->rb_node, &new->rb_node, &tree->map);
	RB_CLEAR_NODE(&cur->rb_node);

	setup_extent_mapping(tree, new, modअगरied);
पूर्ण

अटल काष्ठा extent_map *next_extent_map(काष्ठा extent_map *em)
अणु
	काष्ठा rb_node *next;

	next = rb_next(&em->rb_node);
	अगर (!next)
		वापस शून्य;
	वापस container_of(next, काष्ठा extent_map, rb_node);
पूर्ण

अटल काष्ठा extent_map *prev_extent_map(काष्ठा extent_map *em)
अणु
	काष्ठा rb_node *prev;

	prev = rb_prev(&em->rb_node);
	अगर (!prev)
		वापस शून्य;
	वापस container_of(prev, काष्ठा extent_map, rb_node);
पूर्ण

/*
 * Helper क्रम btrfs_get_extent.  Given an existing extent in the tree,
 * the existing extent is the nearest extent to map_start,
 * and an extent that you want to insert, deal with overlap and insert
 * the best fitted new extent पूर्णांकo the tree.
 */
अटल noअंतरभूत पूर्णांक merge_extent_mapping(काष्ठा extent_map_tree *em_tree,
					 काष्ठा extent_map *existing,
					 काष्ठा extent_map *em,
					 u64 map_start)
अणु
	काष्ठा extent_map *prev;
	काष्ठा extent_map *next;
	u64 start;
	u64 end;
	u64 start_dअगरf;

	BUG_ON(map_start < em->start || map_start >= extent_map_end(em));

	अगर (existing->start > map_start) अणु
		next = existing;
		prev = prev_extent_map(next);
	पूर्ण अन्यथा अणु
		prev = existing;
		next = next_extent_map(prev);
	पूर्ण

	start = prev ? extent_map_end(prev) : em->start;
	start = max_t(u64, start, em->start);
	end = next ? next->start : extent_map_end(em);
	end = min_t(u64, end, extent_map_end(em));
	start_dअगरf = start - em->start;
	em->start = start;
	em->len = end - start;
	अगर (em->block_start < EXTENT_MAP_LAST_BYTE &&
	    !test_bit(EXTENT_FLAG_COMPRESSED, &em->flags)) अणु
		em->block_start += start_dअगरf;
		em->block_len = em->len;
	पूर्ण
	वापस add_extent_mapping(em_tree, em, 0);
पूर्ण

/**
 * Add extent mapping पूर्णांकo em_tree
 *
 * @fs_info:  the fileप्रणाली
 * @em_tree:  extent tree पूर्णांकo which we want to insert the extent mapping
 * @em_in:    extent we are inserting
 * @start:    start of the logical range btrfs_get_extent() is requesting
 * @len:      length of the logical range btrfs_get_extent() is requesting
 *
 * Note that @em_in's range may be dअगरferent from [start, start+len),
 * but they must be overlapped.
 *
 * Insert @em_in पूर्णांकo @em_tree. In हाल there is an overlapping range, handle
 * the -EEXIST by either:
 * a) Returning the existing extent in @em_in अगर @start is within the
 *    existing em.
 * b) Merge the existing extent with @em_in passed in.
 *
 * Return 0 on success, otherwise -EEXIST.
 *
 */
पूर्णांक btrfs_add_extent_mapping(काष्ठा btrfs_fs_info *fs_info,
			     काष्ठा extent_map_tree *em_tree,
			     काष्ठा extent_map **em_in, u64 start, u64 len)
अणु
	पूर्णांक ret;
	काष्ठा extent_map *em = *em_in;

	ret = add_extent_mapping(em_tree, em, 0);
	/* it is possible that someone inserted the extent पूर्णांकo the tree
	 * जबतक we had the lock dropped.  It is also possible that
	 * an overlapping map exists in the tree
	 */
	अगर (ret == -EEXIST) अणु
		काष्ठा extent_map *existing;

		ret = 0;

		existing = search_extent_mapping(em_tree, start, len);

		trace_btrfs_handle_em_exist(fs_info, existing, em, start, len);

		/*
		 * existing will always be non-शून्य, since there must be
		 * extent causing the -EEXIST.
		 */
		अगर (start >= existing->start &&
		    start < extent_map_end(existing)) अणु
			मुक्त_extent_map(em);
			*em_in = existing;
			ret = 0;
		पूर्ण अन्यथा अणु
			u64 orig_start = em->start;
			u64 orig_len = em->len;

			/*
			 * The existing extent map is the one nearest to
			 * the [start, start + len) range which overlaps
			 */
			ret = merge_extent_mapping(em_tree, existing,
						   em, start);
			अगर (ret) अणु
				मुक्त_extent_map(em);
				*em_in = शून्य;
				WARN_ONCE(ret,
"unexpected error %d: merge existing(start %llu len %llu) with em(start %llu len %llu)\n",
					  ret, existing->start, existing->len,
					  orig_start, orig_len);
			पूर्ण
			मुक्त_extent_map(existing);
		पूर्ण
	पूर्ण

	ASSERT(ret == 0 || ret == -EEXIST);
	वापस ret;
पूर्ण
