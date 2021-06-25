<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/bपन.स>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/swap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/cleancache.h>
#समावेश "misc.h"
#समावेश "extent_io.h"
#समावेश "extent-io-tree.h"
#समावेश "extent_map.h"
#समावेश "ctree.h"
#समावेश "btrfs_inode.h"
#समावेश "volumes.h"
#समावेश "check-integrity.h"
#समावेश "locking.h"
#समावेश "rcu-string.h"
#समावेश "backref.h"
#समावेश "disk-io.h"
#समावेश "subpage.h"
#समावेश "zoned.h"
#समावेश "block-group.h"

अटल काष्ठा kmem_cache *extent_state_cache;
अटल काष्ठा kmem_cache *extent_buffer_cache;
अटल काष्ठा bio_set btrfs_bioset;

अटल अंतरभूत bool extent_state_in_tree(स्थिर काष्ठा extent_state *state)
अणु
	वापस !RB_EMPTY_NODE(&state->rb_node);
पूर्ण

#अगर_घोषित CONFIG_BTRFS_DEBUG
अटल LIST_HEAD(states);
अटल DEFINE_SPINLOCK(leak_lock);

अटल अंतरभूत व्योम btrfs_leak_debug_add(spinlock_t *lock,
					काष्ठा list_head *new,
					काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	list_add(new, head);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

अटल अंतरभूत व्योम btrfs_leak_debug_del(spinlock_t *lock,
					काष्ठा list_head *entry)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);
	list_del(entry);
	spin_unlock_irqrestore(lock, flags);
पूर्ण

व्योम btrfs_extent_buffer_leak_debug_check(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा extent_buffer *eb;
	अचिन्हित दीर्घ flags;

	/*
	 * If we didn't get पूर्णांकo खोलो_ctree our allocated_ebs will not be
	 * initialized, so just skip this.
	 */
	अगर (!fs_info->allocated_ebs.next)
		वापस;

	spin_lock_irqsave(&fs_info->eb_leak_lock, flags);
	जबतक (!list_empty(&fs_info->allocated_ebs)) अणु
		eb = list_first_entry(&fs_info->allocated_ebs,
				      काष्ठा extent_buffer, leak_list);
		pr_err(
	"BTRFS: buffer leak start %llu len %lu refs %d bflags %lu owner %llu\n",
		       eb->start, eb->len, atomic_पढ़ो(&eb->refs), eb->bflags,
		       btrfs_header_owner(eb));
		list_del(&eb->leak_list);
		kmem_cache_मुक्त(extent_buffer_cache, eb);
	पूर्ण
	spin_unlock_irqrestore(&fs_info->eb_leak_lock, flags);
पूर्ण

अटल अंतरभूत व्योम btrfs_extent_state_leak_debug_check(व्योम)
अणु
	काष्ठा extent_state *state;

	जबतक (!list_empty(&states)) अणु
		state = list_entry(states.next, काष्ठा extent_state, leak_list);
		pr_err("BTRFS: state leak: start %llu end %llu state %u in tree %d refs %d\n",
		       state->start, state->end, state->state,
		       extent_state_in_tree(state),
		       refcount_पढ़ो(&state->refs));
		list_del(&state->leak_list);
		kmem_cache_मुक्त(extent_state_cache, state);
	पूर्ण
पूर्ण

#घोषणा btrfs_debug_check_extent_io_range(tree, start, end)		\
	__btrfs_debug_check_extent_io_range(__func__, (tree), (start), (end))
अटल अंतरभूत व्योम __btrfs_debug_check_extent_io_range(स्थिर अक्षर *caller,
		काष्ठा extent_io_tree *tree, u64 start, u64 end)
अणु
	काष्ठा inode *inode = tree->निजी_data;
	u64 isize;

	अगर (!inode || !is_data_inode(inode))
		वापस;

	isize = i_size_पढ़ो(inode);
	अगर (end >= PAGE_SIZE && (end % 2) == 0 && end != isize - 1) अणु
		btrfs_debug_rl(BTRFS_I(inode)->root->fs_info,
		    "%s: ino %llu isize %llu odd range [%llu,%llu]",
			caller, btrfs_ino(BTRFS_I(inode)), isize, start, end);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा btrfs_leak_debug_add(lock, new, head)	करो अणुपूर्ण जबतक (0)
#घोषणा btrfs_leak_debug_del(lock, entry)	करो अणुपूर्ण जबतक (0)
#घोषणा btrfs_extent_state_leak_debug_check()	करो अणुपूर्ण जबतक (0)
#घोषणा btrfs_debug_check_extent_io_range(c, s, e)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा tree_entry अणु
	u64 start;
	u64 end;
	काष्ठा rb_node rb_node;
पूर्ण;

काष्ठा extent_page_data अणु
	काष्ठा bio *bio;
	/* tells ग_लिखोpage not to lock the state bits क्रम this range
	 * it still करोes the unlocking
	 */
	अचिन्हित पूर्णांक extent_locked:1;

	/* tells the submit_bio code to use REQ_SYNC */
	अचिन्हित पूर्णांक sync_io:1;
पूर्ण;

अटल पूर्णांक add_extent_changeset(काष्ठा extent_state *state, u32 bits,
				 काष्ठा extent_changeset *changeset,
				 पूर्णांक set)
अणु
	पूर्णांक ret;

	अगर (!changeset)
		वापस 0;
	अगर (set && (state->state & bits) == bits)
		वापस 0;
	अगर (!set && (state->state & bits) == 0)
		वापस 0;
	changeset->bytes_changed += state->end - state->start + 1;
	ret = ulist_add(&changeset->range_changed, state->start, state->end,
			GFP_ATOMIC);
	वापस ret;
पूर्ण

पूर्णांक __must_check submit_one_bio(काष्ठा bio *bio, पूर्णांक mirror_num,
				अचिन्हित दीर्घ bio_flags)
अणु
	blk_status_t ret = 0;
	काष्ठा extent_io_tree *tree = bio->bi_निजी;

	bio->bi_निजी = शून्य;

	अगर (is_data_inode(tree->निजी_data))
		ret = btrfs_submit_data_bio(tree->निजी_data, bio, mirror_num,
					    bio_flags);
	अन्यथा
		ret = btrfs_submit_metadata_bio(tree->निजी_data, bio,
						mirror_num, bio_flags);

	वापस blk_status_to_त्रुटि_सं(ret);
पूर्ण

/* Cleanup unsubmitted bios */
अटल व्योम end_ग_लिखो_bio(काष्ठा extent_page_data *epd, पूर्णांक ret)
अणु
	अगर (epd->bio) अणु
		epd->bio->bi_status = त्रुटि_सं_to_blk_status(ret);
		bio_endio(epd->bio);
		epd->bio = शून्य;
	पूर्ण
पूर्ण

/*
 * Submit bio from extent page data via submit_one_bio
 *
 * Return 0 अगर everything is OK.
 * Return <0 क्रम error.
 */
अटल पूर्णांक __must_check flush_ग_लिखो_bio(काष्ठा extent_page_data *epd)
अणु
	पूर्णांक ret = 0;

	अगर (epd->bio) अणु
		ret = submit_one_bio(epd->bio, 0, 0);
		/*
		 * Clean up of epd->bio is handled by its endio function.
		 * And endio is either triggered by successful bio execution
		 * or the error handler of submit bio hook.
		 * So at this poपूर्णांक, no matter what happened, we करोn't need
		 * to clean up epd->bio.
		 */
		epd->bio = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक __init extent_state_cache_init(व्योम)
अणु
	extent_state_cache = kmem_cache_create("btrfs_extent_state",
			माप(काष्ठा extent_state), 0,
			SLAB_MEM_SPREAD, शून्य);
	अगर (!extent_state_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

पूर्णांक __init extent_io_init(व्योम)
अणु
	extent_buffer_cache = kmem_cache_create("btrfs_extent_buffer",
			माप(काष्ठा extent_buffer), 0,
			SLAB_MEM_SPREAD, शून्य);
	अगर (!extent_buffer_cache)
		वापस -ENOMEM;

	अगर (bioset_init(&btrfs_bioset, BIO_POOL_SIZE,
			दुरत्व(काष्ठा btrfs_io_bio, bio),
			BIOSET_NEED_BVECS))
		जाओ मुक्त_buffer_cache;

	अगर (bioset_पूर्णांकegrity_create(&btrfs_bioset, BIO_POOL_SIZE))
		जाओ मुक्त_bioset;

	वापस 0;

मुक्त_bioset:
	bioset_निकास(&btrfs_bioset);

मुक्त_buffer_cache:
	kmem_cache_destroy(extent_buffer_cache);
	extent_buffer_cache = शून्य;
	वापस -ENOMEM;
पूर्ण

व्योम __cold extent_state_cache_निकास(व्योम)
अणु
	btrfs_extent_state_leak_debug_check();
	kmem_cache_destroy(extent_state_cache);
पूर्ण

व्योम __cold extent_io_निकास(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त are flushed beक्रमe we
	 * destroy caches.
	 */
	rcu_barrier();
	kmem_cache_destroy(extent_buffer_cache);
	bioset_निकास(&btrfs_bioset);
पूर्ण

/*
 * For the file_extent_tree, we want to hold the inode lock when we lookup and
 * update the disk_i_size, but lockdep will complain because our io_tree we hold
 * the tree lock and get the inode lock when setting delalloc.  These two things
 * are unrelated, so make a class क्रम the file_extent_tree so we करोn't get the
 * two locking patterns mixed up.
 */
अटल काष्ठा lock_class_key file_extent_tree_class;

व्योम extent_io_tree_init(काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा extent_io_tree *tree, अचिन्हित पूर्णांक owner,
			 व्योम *निजी_data)
अणु
	tree->fs_info = fs_info;
	tree->state = RB_ROOT;
	tree->dirty_bytes = 0;
	spin_lock_init(&tree->lock);
	tree->निजी_data = निजी_data;
	tree->owner = owner;
	अगर (owner == IO_TREE_INODE_खाता_EXTENT)
		lockdep_set_class(&tree->lock, &file_extent_tree_class);
पूर्ण

व्योम extent_io_tree_release(काष्ठा extent_io_tree *tree)
अणु
	spin_lock(&tree->lock);
	/*
	 * Do a single barrier क्रम the रुकोqueue_active check here, the state
	 * of the रुकोqueue should not change once extent_io_tree_release is
	 * called.
	 */
	smp_mb();
	जबतक (!RB_EMPTY_ROOT(&tree->state)) अणु
		काष्ठा rb_node *node;
		काष्ठा extent_state *state;

		node = rb_first(&tree->state);
		state = rb_entry(node, काष्ठा extent_state, rb_node);
		rb_erase(&state->rb_node, &tree->state);
		RB_CLEAR_NODE(&state->rb_node);
		/*
		 * btree io trees aren't supposed to have tasks रुकोing क्रम
		 * changes in the flags of extent states ever.
		 */
		ASSERT(!रुकोqueue_active(&state->wq));
		मुक्त_extent_state(state);

		cond_resched_lock(&tree->lock);
	पूर्ण
	spin_unlock(&tree->lock);
पूर्ण

अटल काष्ठा extent_state *alloc_extent_state(gfp_t mask)
अणु
	काष्ठा extent_state *state;

	/*
	 * The given mask might be not appropriate क्रम the slab allocator,
	 * drop the unsupported bits
	 */
	mask &= ~(__GFP_DMA32|__GFP_HIGHMEM);
	state = kmem_cache_alloc(extent_state_cache, mask);
	अगर (!state)
		वापस state;
	state->state = 0;
	state->failrec = शून्य;
	RB_CLEAR_NODE(&state->rb_node);
	btrfs_leak_debug_add(&leak_lock, &state->leak_list, &states);
	refcount_set(&state->refs, 1);
	init_रुकोqueue_head(&state->wq);
	trace_alloc_extent_state(state, mask, _RET_IP_);
	वापस state;
पूर्ण

व्योम मुक्त_extent_state(काष्ठा extent_state *state)
अणु
	अगर (!state)
		वापस;
	अगर (refcount_dec_and_test(&state->refs)) अणु
		WARN_ON(extent_state_in_tree(state));
		btrfs_leak_debug_del(&leak_lock, &state->leak_list);
		trace_मुक्त_extent_state(state, _RET_IP_);
		kmem_cache_मुक्त(extent_state_cache, state);
	पूर्ण
पूर्ण

अटल काष्ठा rb_node *tree_insert(काष्ठा rb_root *root,
				   काष्ठा rb_node *search_start,
				   u64 offset,
				   काष्ठा rb_node *node,
				   काष्ठा rb_node ***p_in,
				   काष्ठा rb_node **parent_in)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा tree_entry *entry;

	अगर (p_in && parent_in) अणु
		p = *p_in;
		parent = *parent_in;
		जाओ करो_insert;
	पूर्ण

	p = search_start ? &search_start : &root->rb_node;
	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा tree_entry, rb_node);

		अगर (offset < entry->start)
			p = &(*p)->rb_left;
		अन्यथा अगर (offset > entry->end)
			p = &(*p)->rb_right;
		अन्यथा
			वापस parent;
	पूर्ण

करो_insert:
	rb_link_node(node, parent, p);
	rb_insert_color(node, root);
	वापस शून्य;
पूर्ण

/**
 * Search @tree क्रम an entry that contains @offset. Such entry would have
 * entry->start <= offset && entry->end >= offset.
 *
 * @tree:       the tree to search
 * @offset:     offset that should fall within an entry in @tree
 * @next_ret:   poपूर्णांकer to the first entry whose range ends after @offset
 * @prev_ret:   poपूर्णांकer to the first entry whose range begins beक्रमe @offset
 * @p_ret:      poपूर्णांकer where new node should be anchored (used when inserting an
 *	        entry in the tree)
 * @parent_ret: poपूर्णांकs to entry which would have been the parent of the entry,
 *               containing @offset
 *
 * This function वापसs a poपूर्णांकer to the entry that contains @offset byte
 * address. If no such entry exists, then शून्य is वापसed and the other
 * poपूर्णांकer arguments to the function are filled, otherwise the found entry is
 * वापसed and other poपूर्णांकers are left untouched.
 */
अटल काष्ठा rb_node *__etree_search(काष्ठा extent_io_tree *tree, u64 offset,
				      काष्ठा rb_node **next_ret,
				      काष्ठा rb_node **prev_ret,
				      काष्ठा rb_node ***p_ret,
				      काष्ठा rb_node **parent_ret)
अणु
	काष्ठा rb_root *root = &tree->state;
	काष्ठा rb_node **n = &root->rb_node;
	काष्ठा rb_node *prev = शून्य;
	काष्ठा rb_node *orig_prev = शून्य;
	काष्ठा tree_entry *entry;
	काष्ठा tree_entry *prev_entry = शून्य;

	जबतक (*n) अणु
		prev = *n;
		entry = rb_entry(prev, काष्ठा tree_entry, rb_node);
		prev_entry = entry;

		अगर (offset < entry->start)
			n = &(*n)->rb_left;
		अन्यथा अगर (offset > entry->end)
			n = &(*n)->rb_right;
		अन्यथा
			वापस *n;
	पूर्ण

	अगर (p_ret)
		*p_ret = n;
	अगर (parent_ret)
		*parent_ret = prev;

	अगर (next_ret) अणु
		orig_prev = prev;
		जबतक (prev && offset > prev_entry->end) अणु
			prev = rb_next(prev);
			prev_entry = rb_entry(prev, काष्ठा tree_entry, rb_node);
		पूर्ण
		*next_ret = prev;
		prev = orig_prev;
	पूर्ण

	अगर (prev_ret) अणु
		prev_entry = rb_entry(prev, काष्ठा tree_entry, rb_node);
		जबतक (prev && offset < prev_entry->start) अणु
			prev = rb_prev(prev);
			prev_entry = rb_entry(prev, काष्ठा tree_entry, rb_node);
		पूर्ण
		*prev_ret = prev;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rb_node *
tree_search_क्रम_insert(काष्ठा extent_io_tree *tree,
		       u64 offset,
		       काष्ठा rb_node ***p_ret,
		       काष्ठा rb_node **parent_ret)
अणु
	काष्ठा rb_node *next= शून्य;
	काष्ठा rb_node *ret;

	ret = __etree_search(tree, offset, &next, शून्य, p_ret, parent_ret);
	अगर (!ret)
		वापस next;
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा rb_node *tree_search(काष्ठा extent_io_tree *tree,
					  u64 offset)
अणु
	वापस tree_search_क्रम_insert(tree, offset, शून्य, शून्य);
पूर्ण

/*
 * utility function to look क्रम merge candidates inside a given range.
 * Any extents with matching state are merged together पूर्णांकo a single
 * extent in the tree.  Extents with EXTENT_IO in their state field
 * are not merged because the end_io handlers need to be able to करो
 * operations on them without sleeping (or करोing allocations/splits).
 *
 * This should be called with the tree lock held.
 */
अटल व्योम merge_state(काष्ठा extent_io_tree *tree,
		        काष्ठा extent_state *state)
अणु
	काष्ठा extent_state *other;
	काष्ठा rb_node *other_node;

	अगर (state->state & (EXTENT_LOCKED | EXTENT_BOUNDARY))
		वापस;

	other_node = rb_prev(&state->rb_node);
	अगर (other_node) अणु
		other = rb_entry(other_node, काष्ठा extent_state, rb_node);
		अगर (other->end == state->start - 1 &&
		    other->state == state->state) अणु
			अगर (tree->निजी_data &&
			    is_data_inode(tree->निजी_data))
				btrfs_merge_delalloc_extent(tree->निजी_data,
							    state, other);
			state->start = other->start;
			rb_erase(&other->rb_node, &tree->state);
			RB_CLEAR_NODE(&other->rb_node);
			मुक्त_extent_state(other);
		पूर्ण
	पूर्ण
	other_node = rb_next(&state->rb_node);
	अगर (other_node) अणु
		other = rb_entry(other_node, काष्ठा extent_state, rb_node);
		अगर (other->start == state->end + 1 &&
		    other->state == state->state) अणु
			अगर (tree->निजी_data &&
			    is_data_inode(tree->निजी_data))
				btrfs_merge_delalloc_extent(tree->निजी_data,
							    state, other);
			state->end = other->end;
			rb_erase(&other->rb_node, &tree->state);
			RB_CLEAR_NODE(&other->rb_node);
			मुक्त_extent_state(other);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_state_bits(काष्ठा extent_io_tree *tree,
			   काष्ठा extent_state *state, u32 *bits,
			   काष्ठा extent_changeset *changeset);

/*
 * insert an extent_state काष्ठा पूर्णांकo the tree.  'bits' are set on the
 * काष्ठा beक्रमe it is inserted.
 *
 * This may वापस -EEXIST अगर the extent is alपढ़ोy there, in which हाल the
 * state काष्ठा is मुक्तd.
 *
 * The tree lock is not taken पूर्णांकernally.  This is a utility function and
 * probably isn't what you want to call (see set/clear_extent_bit).
 */
अटल पूर्णांक insert_state(काष्ठा extent_io_tree *tree,
			काष्ठा extent_state *state, u64 start, u64 end,
			काष्ठा rb_node ***p,
			काष्ठा rb_node **parent,
			u32 *bits, काष्ठा extent_changeset *changeset)
अणु
	काष्ठा rb_node *node;

	अगर (end < start) अणु
		btrfs_err(tree->fs_info,
			"insert state: end < start %llu %llu", end, start);
		WARN_ON(1);
	पूर्ण
	state->start = start;
	state->end = end;

	set_state_bits(tree, state, bits, changeset);

	node = tree_insert(&tree->state, शून्य, end, &state->rb_node, p, parent);
	अगर (node) अणु
		काष्ठा extent_state *found;
		found = rb_entry(node, काष्ठा extent_state, rb_node);
		btrfs_err(tree->fs_info,
		       "found node %llu %llu on insert of %llu %llu",
		       found->start, found->end, start, end);
		वापस -EEXIST;
	पूर्ण
	merge_state(tree, state);
	वापस 0;
पूर्ण

/*
 * split a given extent state काष्ठा in two, inserting the pपुनः_स्मृतिated
 * काष्ठा 'prealloc' as the newly created second half.  'split' indicates an
 * offset inside 'orig' where it should be split.
 *
 * Beक्रमe calling,
 * the tree has 'orig' at [orig->start, orig->end].  After calling, there
 * are two extent state काष्ठाs in the tree:
 * pपुनः_स्मृति: [orig->start, split - 1]
 * orig: [ split, orig->end ]
 *
 * The tree locks are not taken by this function. They need to be held
 * by the caller.
 */
अटल पूर्णांक split_state(काष्ठा extent_io_tree *tree, काष्ठा extent_state *orig,
		       काष्ठा extent_state *pपुनः_स्मृति, u64 split)
अणु
	काष्ठा rb_node *node;

	अगर (tree->निजी_data && is_data_inode(tree->निजी_data))
		btrfs_split_delalloc_extent(tree->निजी_data, orig, split);

	pपुनः_स्मृति->start = orig->start;
	pपुनः_स्मृति->end = split - 1;
	pपुनः_स्मृति->state = orig->state;
	orig->start = split;

	node = tree_insert(&tree->state, &orig->rb_node, pपुनः_स्मृति->end,
			   &pपुनः_स्मृति->rb_node, शून्य, शून्य);
	अगर (node) अणु
		मुक्त_extent_state(pपुनः_स्मृति);
		वापस -EEXIST;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा extent_state *next_state(काष्ठा extent_state *state)
अणु
	काष्ठा rb_node *next = rb_next(&state->rb_node);
	अगर (next)
		वापस rb_entry(next, काष्ठा extent_state, rb_node);
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * utility function to clear some bits in an extent state काष्ठा.
 * it will optionally wake up anyone रुकोing on this state (wake == 1).
 *
 * If no bits are set on the state काष्ठा after clearing things, the
 * काष्ठा is मुक्तd and हटाओd from the tree
 */
अटल काष्ठा extent_state *clear_state_bit(काष्ठा extent_io_tree *tree,
					    काष्ठा extent_state *state,
					    u32 *bits, पूर्णांक wake,
					    काष्ठा extent_changeset *changeset)
अणु
	काष्ठा extent_state *next;
	u32 bits_to_clear = *bits & ~EXTENT_CTLBITS;
	पूर्णांक ret;

	अगर ((bits_to_clear & EXTENT_सूचीTY) && (state->state & EXTENT_सूचीTY)) अणु
		u64 range = state->end - state->start + 1;
		WARN_ON(range > tree->dirty_bytes);
		tree->dirty_bytes -= range;
	पूर्ण

	अगर (tree->निजी_data && is_data_inode(tree->निजी_data))
		btrfs_clear_delalloc_extent(tree->निजी_data, state, bits);

	ret = add_extent_changeset(state, bits_to_clear, changeset, 0);
	BUG_ON(ret < 0);
	state->state &= ~bits_to_clear;
	अगर (wake)
		wake_up(&state->wq);
	अगर (state->state == 0) अणु
		next = next_state(state);
		अगर (extent_state_in_tree(state)) अणु
			rb_erase(&state->rb_node, &tree->state);
			RB_CLEAR_NODE(&state->rb_node);
			मुक्त_extent_state(state);
		पूर्ण अन्यथा अणु
			WARN_ON(1);
		पूर्ण
	पूर्ण अन्यथा अणु
		merge_state(tree, state);
		next = next_state(state);
	पूर्ण
	वापस next;
पूर्ण

अटल काष्ठा extent_state *
alloc_extent_state_atomic(काष्ठा extent_state *pपुनः_स्मृति)
अणु
	अगर (!pपुनः_स्मृति)
		pपुनः_स्मृति = alloc_extent_state(GFP_ATOMIC);

	वापस pपुनः_स्मृति;
पूर्ण

अटल व्योम extent_io_tree_panic(काष्ठा extent_io_tree *tree, पूर्णांक err)
अणु
	btrfs_panic(tree->fs_info, err,
	"locking error: extent tree was modified by another thread while locked");
पूर्ण

/*
 * clear some bits on a range in the tree.  This may require splitting
 * or inserting elements in the tree, so the gfp mask is used to
 * indicate which allocations or sleeping are allowed.
 *
 * pass 'wake' == 1 to kick any sleepers, and 'delete' == 1 to हटाओ
 * the given range from the tree regardless of state (ie क्रम truncate).
 *
 * the range [start, end] is inclusive.
 *
 * This takes the tree lock, and वापसs 0 on success and < 0 on error.
 */
पूर्णांक __clear_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		       u32 bits, पूर्णांक wake, पूर्णांक delete,
		       काष्ठा extent_state **cached_state,
		       gfp_t mask, काष्ठा extent_changeset *changeset)
अणु
	काष्ठा extent_state *state;
	काष्ठा extent_state *cached;
	काष्ठा extent_state *pपुनः_स्मृति = शून्य;
	काष्ठा rb_node *node;
	u64 last_end;
	पूर्णांक err;
	पूर्णांक clear = 0;

	btrfs_debug_check_extent_io_range(tree, start, end);
	trace_btrfs_clear_extent_bit(tree, start, end - start + 1, bits);

	अगर (bits & EXTENT_DELALLOC)
		bits |= EXTENT_NORESERVE;

	अगर (delete)
		bits |= ~EXTENT_CTLBITS;

	अगर (bits & (EXTENT_LOCKED | EXTENT_BOUNDARY))
		clear = 1;
again:
	अगर (!pपुनः_स्मृति && gfpflags_allow_blocking(mask)) अणु
		/*
		 * Don't care क्रम allocation failure here because we might end
		 * up not needing the pre-allocated extent state at all, which
		 * is the हाल अगर we only have in the tree extent states that
		 * cover our input range and करोn't cover too any other range.
		 * If we end up needing a new extent state we allocate it later.
		 */
		pपुनः_स्मृति = alloc_extent_state(mask);
	पूर्ण

	spin_lock(&tree->lock);
	अगर (cached_state) अणु
		cached = *cached_state;

		अगर (clear) अणु
			*cached_state = शून्य;
			cached_state = शून्य;
		पूर्ण

		अगर (cached && extent_state_in_tree(cached) &&
		    cached->start <= start && cached->end > start) अणु
			अगर (clear)
				refcount_dec(&cached->refs);
			state = cached;
			जाओ hit_next;
		पूर्ण
		अगर (clear)
			मुक्त_extent_state(cached);
	पूर्ण
	/*
	 * this search will find the extents that end after
	 * our range starts
	 */
	node = tree_search(tree, start);
	अगर (!node)
		जाओ out;
	state = rb_entry(node, काष्ठा extent_state, rb_node);
hit_next:
	अगर (state->start > end)
		जाओ out;
	WARN_ON(state->end < start);
	last_end = state->end;

	/* the state करोesn't have the wanted bits, go ahead */
	अगर (!(state->state & bits)) अणु
		state = next_state(state);
		जाओ next;
	पूर्ण

	/*
	 *     | ---- desired range ---- |
	 *  | state | or
	 *  | ------------- state -------------- |
	 *
	 * We need to split the extent we found, and may flip
	 * bits on second half.
	 *
	 * If the extent we found extends past our range, we
	 * just split and search again.  It'll get split again
	 * the next समय though.
	 *
	 * If the extent we found is inside our range, we clear
	 * the desired bit on it.
	 */

	अगर (state->start < start) अणु
		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		BUG_ON(!pपुनः_स्मृति);
		err = split_state(tree, state, pपुनः_स्मृति, start);
		अगर (err)
			extent_io_tree_panic(tree, err);

		pपुनः_स्मृति = शून्य;
		अगर (err)
			जाओ out;
		अगर (state->end <= end) अणु
			state = clear_state_bit(tree, state, &bits, wake,
						changeset);
			जाओ next;
		पूर्ण
		जाओ search_again;
	पूर्ण
	/*
	 * | ---- desired range ---- |
	 *                        | state |
	 * We need to split the extent, and clear the bit
	 * on the first half
	 */
	अगर (state->start <= end && state->end > end) अणु
		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		BUG_ON(!pपुनः_स्मृति);
		err = split_state(tree, state, pपुनः_स्मृति, end + 1);
		अगर (err)
			extent_io_tree_panic(tree, err);

		अगर (wake)
			wake_up(&state->wq);

		clear_state_bit(tree, pपुनः_स्मृति, &bits, wake, changeset);

		pपुनः_स्मृति = शून्य;
		जाओ out;
	पूर्ण

	state = clear_state_bit(tree, state, &bits, wake, changeset);
next:
	अगर (last_end == (u64)-1)
		जाओ out;
	start = last_end + 1;
	अगर (start <= end && state && !need_resched())
		जाओ hit_next;

search_again:
	अगर (start > end)
		जाओ out;
	spin_unlock(&tree->lock);
	अगर (gfpflags_allow_blocking(mask))
		cond_resched();
	जाओ again;

out:
	spin_unlock(&tree->lock);
	अगर (pपुनः_स्मृति)
		मुक्त_extent_state(pपुनः_स्मृति);

	वापस 0;

पूर्ण

अटल व्योम रुको_on_state(काष्ठा extent_io_tree *tree,
			  काष्ठा extent_state *state)
		__releases(tree->lock)
		__acquires(tree->lock)
अणु
	DEFINE_WAIT(रुको);
	prepare_to_रुको(&state->wq, &रुको, TASK_UNINTERRUPTIBLE);
	spin_unlock(&tree->lock);
	schedule();
	spin_lock(&tree->lock);
	finish_रुको(&state->wq, &रुको);
पूर्ण

/*
 * रुकोs क्रम one or more bits to clear on a range in the state tree.
 * The range [start, end] is inclusive.
 * The tree lock is taken by this function
 */
अटल व्योम रुको_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
			    u32 bits)
अणु
	काष्ठा extent_state *state;
	काष्ठा rb_node *node;

	btrfs_debug_check_extent_io_range(tree, start, end);

	spin_lock(&tree->lock);
again:
	जबतक (1) अणु
		/*
		 * this search will find all the extents that end after
		 * our range starts
		 */
		node = tree_search(tree, start);
process_node:
		अगर (!node)
			अवरोध;

		state = rb_entry(node, काष्ठा extent_state, rb_node);

		अगर (state->start > end)
			जाओ out;

		अगर (state->state & bits) अणु
			start = state->start;
			refcount_inc(&state->refs);
			रुको_on_state(tree, state);
			मुक्त_extent_state(state);
			जाओ again;
		पूर्ण
		start = state->end + 1;

		अगर (start > end)
			अवरोध;

		अगर (!cond_resched_lock(&tree->lock)) अणु
			node = rb_next(node);
			जाओ process_node;
		पूर्ण
	पूर्ण
out:
	spin_unlock(&tree->lock);
पूर्ण

अटल व्योम set_state_bits(काष्ठा extent_io_tree *tree,
			   काष्ठा extent_state *state,
			   u32 *bits, काष्ठा extent_changeset *changeset)
अणु
	u32 bits_to_set = *bits & ~EXTENT_CTLBITS;
	पूर्णांक ret;

	अगर (tree->निजी_data && is_data_inode(tree->निजी_data))
		btrfs_set_delalloc_extent(tree->निजी_data, state, bits);

	अगर ((bits_to_set & EXTENT_सूचीTY) && !(state->state & EXTENT_सूचीTY)) अणु
		u64 range = state->end - state->start + 1;
		tree->dirty_bytes += range;
	पूर्ण
	ret = add_extent_changeset(state, bits_to_set, changeset, 1);
	BUG_ON(ret < 0);
	state->state |= bits_to_set;
पूर्ण

अटल व्योम cache_state_अगर_flags(काष्ठा extent_state *state,
				 काष्ठा extent_state **cached_ptr,
				 अचिन्हित flags)
अणु
	अगर (cached_ptr && !(*cached_ptr)) अणु
		अगर (!flags || (state->state & flags)) अणु
			*cached_ptr = state;
			refcount_inc(&state->refs);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cache_state(काष्ठा extent_state *state,
			काष्ठा extent_state **cached_ptr)
अणु
	वापस cache_state_अगर_flags(state, cached_ptr,
				    EXTENT_LOCKED | EXTENT_BOUNDARY);
पूर्ण

/*
 * set some bits on a range in the tree.  This may require allocations or
 * sleeping, so the gfp mask is used to indicate what is allowed.
 *
 * If any of the exclusive bits are set, this will fail with -EEXIST अगर some
 * part of the range alपढ़ोy has the desired bits set.  The start of the
 * existing range is वापसed in failed_start in this हाल.
 *
 * [start, end] is inclusive This takes the tree lock.
 */
पूर्णांक set_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end, u32 bits,
		   u32 exclusive_bits, u64 *failed_start,
		   काष्ठा extent_state **cached_state, gfp_t mask,
		   काष्ठा extent_changeset *changeset)
अणु
	काष्ठा extent_state *state;
	काष्ठा extent_state *pपुनः_स्मृति = शून्य;
	काष्ठा rb_node *node;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent;
	पूर्णांक err = 0;
	u64 last_start;
	u64 last_end;

	btrfs_debug_check_extent_io_range(tree, start, end);
	trace_btrfs_set_extent_bit(tree, start, end - start + 1, bits);

	अगर (exclusive_bits)
		ASSERT(failed_start);
	अन्यथा
		ASSERT(failed_start == शून्य);
again:
	अगर (!pपुनः_स्मृति && gfpflags_allow_blocking(mask)) अणु
		/*
		 * Don't care क्रम allocation failure here because we might end
		 * up not needing the pre-allocated extent state at all, which
		 * is the हाल अगर we only have in the tree extent states that
		 * cover our input range and करोn't cover too any other range.
		 * If we end up needing a new extent state we allocate it later.
		 */
		pपुनः_स्मृति = alloc_extent_state(mask);
	पूर्ण

	spin_lock(&tree->lock);
	अगर (cached_state && *cached_state) अणु
		state = *cached_state;
		अगर (state->start <= start && state->end > start &&
		    extent_state_in_tree(state)) अणु
			node = &state->rb_node;
			जाओ hit_next;
		पूर्ण
	पूर्ण
	/*
	 * this search will find all the extents that end after
	 * our range starts.
	 */
	node = tree_search_क्रम_insert(tree, start, &p, &parent);
	अगर (!node) अणु
		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		BUG_ON(!pपुनः_स्मृति);
		err = insert_state(tree, pपुनः_स्मृति, start, end,
				   &p, &parent, &bits, changeset);
		अगर (err)
			extent_io_tree_panic(tree, err);

		cache_state(pपुनः_स्मृति, cached_state);
		pपुनः_स्मृति = शून्य;
		जाओ out;
	पूर्ण
	state = rb_entry(node, काष्ठा extent_state, rb_node);
hit_next:
	last_start = state->start;
	last_end = state->end;

	/*
	 * | ---- desired range ---- |
	 * | state |
	 *
	 * Just lock what we found and keep going
	 */
	अगर (state->start == start && state->end <= end) अणु
		अगर (state->state & exclusive_bits) अणु
			*failed_start = state->start;
			err = -EEXIST;
			जाओ out;
		पूर्ण

		set_state_bits(tree, state, &bits, changeset);
		cache_state(state, cached_state);
		merge_state(tree, state);
		अगर (last_end == (u64)-1)
			जाओ out;
		start = last_end + 1;
		state = next_state(state);
		अगर (start < end && state && state->start == start &&
		    !need_resched())
			जाओ hit_next;
		जाओ search_again;
	पूर्ण

	/*
	 *     | ---- desired range ---- |
	 * | state |
	 *   or
	 * | ------------- state -------------- |
	 *
	 * We need to split the extent we found, and may flip bits on
	 * second half.
	 *
	 * If the extent we found extends past our
	 * range, we just split and search again.  It'll get split
	 * again the next समय though.
	 *
	 * If the extent we found is inside our range, we set the
	 * desired bit on it.
	 */
	अगर (state->start < start) अणु
		अगर (state->state & exclusive_bits) अणु
			*failed_start = start;
			err = -EEXIST;
			जाओ out;
		पूर्ण

		/*
		 * If this extent alपढ़ोy has all the bits we want set, then
		 * skip it, not necessary to split it or करो anything with it.
		 */
		अगर ((state->state & bits) == bits) अणु
			start = state->end + 1;
			cache_state(state, cached_state);
			जाओ search_again;
		पूर्ण

		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		BUG_ON(!pपुनः_स्मृति);
		err = split_state(tree, state, pपुनः_स्मृति, start);
		अगर (err)
			extent_io_tree_panic(tree, err);

		pपुनः_स्मृति = शून्य;
		अगर (err)
			जाओ out;
		अगर (state->end <= end) अणु
			set_state_bits(tree, state, &bits, changeset);
			cache_state(state, cached_state);
			merge_state(tree, state);
			अगर (last_end == (u64)-1)
				जाओ out;
			start = last_end + 1;
			state = next_state(state);
			अगर (start < end && state && state->start == start &&
			    !need_resched())
				जाओ hit_next;
		पूर्ण
		जाओ search_again;
	पूर्ण
	/*
	 * | ---- desired range ---- |
	 *     | state | or               | state |
	 *
	 * There's a hole, we need to insert something in it and
	 * ignore the extent we found.
	 */
	अगर (state->start > start) अणु
		u64 this_end;
		अगर (end < last_start)
			this_end = end;
		अन्यथा
			this_end = last_start - 1;

		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		BUG_ON(!pपुनः_स्मृति);

		/*
		 * Aव्योम to मुक्त 'prealloc' अगर it can be merged with
		 * the later extent.
		 */
		err = insert_state(tree, pपुनः_स्मृति, start, this_end,
				   शून्य, शून्य, &bits, changeset);
		अगर (err)
			extent_io_tree_panic(tree, err);

		cache_state(pपुनः_स्मृति, cached_state);
		pपुनः_स्मृति = शून्य;
		start = this_end + 1;
		जाओ search_again;
	पूर्ण
	/*
	 * | ---- desired range ---- |
	 *                        | state |
	 * We need to split the extent, and set the bit
	 * on the first half
	 */
	अगर (state->start <= end && state->end > end) अणु
		अगर (state->state & exclusive_bits) अणु
			*failed_start = start;
			err = -EEXIST;
			जाओ out;
		पूर्ण

		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		BUG_ON(!pपुनः_स्मृति);
		err = split_state(tree, state, pपुनः_स्मृति, end + 1);
		अगर (err)
			extent_io_tree_panic(tree, err);

		set_state_bits(tree, pपुनः_स्मृति, &bits, changeset);
		cache_state(pपुनः_स्मृति, cached_state);
		merge_state(tree, pपुनः_स्मृति);
		pपुनः_स्मृति = शून्य;
		जाओ out;
	पूर्ण

search_again:
	अगर (start > end)
		जाओ out;
	spin_unlock(&tree->lock);
	अगर (gfpflags_allow_blocking(mask))
		cond_resched();
	जाओ again;

out:
	spin_unlock(&tree->lock);
	अगर (pपुनः_स्मृति)
		मुक्त_extent_state(pपुनः_स्मृति);

	वापस err;

पूर्ण

/**
 * convert_extent_bit - convert all bits in a given range from one bit to
 * 			another
 * @tree:	the io tree to search
 * @start:	the start offset in bytes
 * @end:	the end offset in bytes (inclusive)
 * @bits:	the bits to set in this range
 * @clear_bits:	the bits to clear in this range
 * @cached_state:	state that we're going to cache
 *
 * This will go through and set bits क्रम the given range.  If any states exist
 * alपढ़ोy in this range they are set with the given bit and cleared of the
 * clear_bits.  This is only meant to be used by things that are mergeable, ie
 * converting from say DELALLOC to सूचीTY.  This is not meant to be used with
 * boundary bits like LOCK.
 *
 * All allocations are करोne with GFP_NOFS.
 */
पूर्णांक convert_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		       u32 bits, u32 clear_bits,
		       काष्ठा extent_state **cached_state)
अणु
	काष्ठा extent_state *state;
	काष्ठा extent_state *pपुनः_स्मृति = शून्य;
	काष्ठा rb_node *node;
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent;
	पूर्णांक err = 0;
	u64 last_start;
	u64 last_end;
	bool first_iteration = true;

	btrfs_debug_check_extent_io_range(tree, start, end);
	trace_btrfs_convert_extent_bit(tree, start, end - start + 1, bits,
				       clear_bits);

again:
	अगर (!pपुनः_स्मृति) अणु
		/*
		 * Best efक्रमt, करोn't worry अगर extent state allocation fails
		 * here क्रम the first iteration. We might have a cached state
		 * that matches exactly the target range, in which हाल no
		 * extent state allocations are needed. We'll only know this
		 * after locking the tree.
		 */
		pपुनः_स्मृति = alloc_extent_state(GFP_NOFS);
		अगर (!pपुनः_स्मृति && !first_iteration)
			वापस -ENOMEM;
	पूर्ण

	spin_lock(&tree->lock);
	अगर (cached_state && *cached_state) अणु
		state = *cached_state;
		अगर (state->start <= start && state->end > start &&
		    extent_state_in_tree(state)) अणु
			node = &state->rb_node;
			जाओ hit_next;
		पूर्ण
	पूर्ण

	/*
	 * this search will find all the extents that end after
	 * our range starts.
	 */
	node = tree_search_क्रम_insert(tree, start, &p, &parent);
	अगर (!node) अणु
		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		अगर (!pपुनः_स्मृति) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		err = insert_state(tree, pपुनः_स्मृति, start, end,
				   &p, &parent, &bits, शून्य);
		अगर (err)
			extent_io_tree_panic(tree, err);
		cache_state(pपुनः_स्मृति, cached_state);
		pपुनः_स्मृति = शून्य;
		जाओ out;
	पूर्ण
	state = rb_entry(node, काष्ठा extent_state, rb_node);
hit_next:
	last_start = state->start;
	last_end = state->end;

	/*
	 * | ---- desired range ---- |
	 * | state |
	 *
	 * Just lock what we found and keep going
	 */
	अगर (state->start == start && state->end <= end) अणु
		set_state_bits(tree, state, &bits, शून्य);
		cache_state(state, cached_state);
		state = clear_state_bit(tree, state, &clear_bits, 0, शून्य);
		अगर (last_end == (u64)-1)
			जाओ out;
		start = last_end + 1;
		अगर (start < end && state && state->start == start &&
		    !need_resched())
			जाओ hit_next;
		जाओ search_again;
	पूर्ण

	/*
	 *     | ---- desired range ---- |
	 * | state |
	 *   or
	 * | ------------- state -------------- |
	 *
	 * We need to split the extent we found, and may flip bits on
	 * second half.
	 *
	 * If the extent we found extends past our
	 * range, we just split and search again.  It'll get split
	 * again the next समय though.
	 *
	 * If the extent we found is inside our range, we set the
	 * desired bit on it.
	 */
	अगर (state->start < start) अणु
		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		अगर (!pपुनः_स्मृति) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		err = split_state(tree, state, pपुनः_स्मृति, start);
		अगर (err)
			extent_io_tree_panic(tree, err);
		pपुनः_स्मृति = शून्य;
		अगर (err)
			जाओ out;
		अगर (state->end <= end) अणु
			set_state_bits(tree, state, &bits, शून्य);
			cache_state(state, cached_state);
			state = clear_state_bit(tree, state, &clear_bits, 0,
						शून्य);
			अगर (last_end == (u64)-1)
				जाओ out;
			start = last_end + 1;
			अगर (start < end && state && state->start == start &&
			    !need_resched())
				जाओ hit_next;
		पूर्ण
		जाओ search_again;
	पूर्ण
	/*
	 * | ---- desired range ---- |
	 *     | state | or               | state |
	 *
	 * There's a hole, we need to insert something in it and
	 * ignore the extent we found.
	 */
	अगर (state->start > start) अणु
		u64 this_end;
		अगर (end < last_start)
			this_end = end;
		अन्यथा
			this_end = last_start - 1;

		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		अगर (!pपुनः_स्मृति) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		/*
		 * Aव्योम to मुक्त 'prealloc' अगर it can be merged with
		 * the later extent.
		 */
		err = insert_state(tree, pपुनः_स्मृति, start, this_end,
				   शून्य, शून्य, &bits, शून्य);
		अगर (err)
			extent_io_tree_panic(tree, err);
		cache_state(pपुनः_स्मृति, cached_state);
		pपुनः_स्मृति = शून्य;
		start = this_end + 1;
		जाओ search_again;
	पूर्ण
	/*
	 * | ---- desired range ---- |
	 *                        | state |
	 * We need to split the extent, and set the bit
	 * on the first half
	 */
	अगर (state->start <= end && state->end > end) अणु
		pपुनः_स्मृति = alloc_extent_state_atomic(pपुनः_स्मृति);
		अगर (!pपुनः_स्मृति) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		err = split_state(tree, state, pपुनः_स्मृति, end + 1);
		अगर (err)
			extent_io_tree_panic(tree, err);

		set_state_bits(tree, pपुनः_स्मृति, &bits, शून्य);
		cache_state(pपुनः_स्मृति, cached_state);
		clear_state_bit(tree, pपुनः_स्मृति, &clear_bits, 0, शून्य);
		pपुनः_स्मृति = शून्य;
		जाओ out;
	पूर्ण

search_again:
	अगर (start > end)
		जाओ out;
	spin_unlock(&tree->lock);
	cond_resched();
	first_iteration = false;
	जाओ again;

out:
	spin_unlock(&tree->lock);
	अगर (pपुनः_स्मृति)
		मुक्त_extent_state(pपुनः_स्मृति);

	वापस err;
पूर्ण

/* wrappers around set/clear extent bit */
पूर्णांक set_record_extent_bits(काष्ठा extent_io_tree *tree, u64 start, u64 end,
			   u32 bits, काष्ठा extent_changeset *changeset)
अणु
	/*
	 * We करोn't support EXTENT_LOCKED yet, as current changeset will
	 * record any bits changed, so क्रम EXTENT_LOCKED हाल, it will
	 * either fail with -EEXIST or changeset will record the whole
	 * range.
	 */
	BUG_ON(bits & EXTENT_LOCKED);

	वापस set_extent_bit(tree, start, end, bits, 0, शून्य, शून्य, GFP_NOFS,
			      changeset);
पूर्ण

पूर्णांक set_extent_bits_noरुको(काष्ठा extent_io_tree *tree, u64 start, u64 end,
			   u32 bits)
अणु
	वापस set_extent_bit(tree, start, end, bits, 0, शून्य, शून्य,
			      GFP_NOWAIT, शून्य);
पूर्ण

पूर्णांक clear_extent_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		     u32 bits, पूर्णांक wake, पूर्णांक delete,
		     काष्ठा extent_state **cached)
अणु
	वापस __clear_extent_bit(tree, start, end, bits, wake, delete,
				  cached, GFP_NOFS, शून्य);
पूर्ण

पूर्णांक clear_record_extent_bits(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		u32 bits, काष्ठा extent_changeset *changeset)
अणु
	/*
	 * Don't support EXTENT_LOCKED हाल, same reason as
	 * set_record_extent_bits().
	 */
	BUG_ON(bits & EXTENT_LOCKED);

	वापस __clear_extent_bit(tree, start, end, bits, 0, 0, शून्य, GFP_NOFS,
				  changeset);
पूर्ण

/*
 * either insert or lock state काष्ठा between start and end use mask to tell
 * us अगर रुकोing is desired.
 */
पूर्णांक lock_extent_bits(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		     काष्ठा extent_state **cached_state)
अणु
	पूर्णांक err;
	u64 failed_start;

	जबतक (1) अणु
		err = set_extent_bit(tree, start, end, EXTENT_LOCKED,
				     EXTENT_LOCKED, &failed_start,
				     cached_state, GFP_NOFS, शून्य);
		अगर (err == -EEXIST) अणु
			रुको_extent_bit(tree, failed_start, end, EXTENT_LOCKED);
			start = failed_start;
		पूर्ण अन्यथा
			अवरोध;
		WARN_ON(start > end);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक try_lock_extent(काष्ठा extent_io_tree *tree, u64 start, u64 end)
अणु
	पूर्णांक err;
	u64 failed_start;

	err = set_extent_bit(tree, start, end, EXTENT_LOCKED, EXTENT_LOCKED,
			     &failed_start, शून्य, GFP_NOFS, शून्य);
	अगर (err == -EEXIST) अणु
		अगर (failed_start > start)
			clear_extent_bit(tree, start, failed_start - 1,
					 EXTENT_LOCKED, 1, 0, शून्य);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

व्योम extent_range_clear_dirty_क्रम_io(काष्ठा inode *inode, u64 start, u64 end)
अणु
	अचिन्हित दीर्घ index = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_index = end >> PAGE_SHIFT;
	काष्ठा page *page;

	जबतक (index <= end_index) अणु
		page = find_get_page(inode->i_mapping, index);
		BUG_ON(!page); /* Pages should be in the extent_io_tree */
		clear_page_dirty_क्रम_io(page);
		put_page(page);
		index++;
	पूर्ण
पूर्ण

व्योम extent_range_redirty_क्रम_io(काष्ठा inode *inode, u64 start, u64 end)
अणु
	अचिन्हित दीर्घ index = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_index = end >> PAGE_SHIFT;
	काष्ठा page *page;

	जबतक (index <= end_index) अणु
		page = find_get_page(inode->i_mapping, index);
		BUG_ON(!page); /* Pages should be in the extent_io_tree */
		__set_page_dirty_nobuffers(page);
		account_page_redirty(page);
		put_page(page);
		index++;
	पूर्ण
पूर्ण

/* find the first state काष्ठा with 'bits' set after 'start', and
 * वापस it.  tree->lock must be held.  शून्य will वापसed अगर
 * nothing was found after 'start'
 */
अटल काष्ठा extent_state *
find_first_extent_bit_state(काष्ठा extent_io_tree *tree, u64 start, u32 bits)
अणु
	काष्ठा rb_node *node;
	काष्ठा extent_state *state;

	/*
	 * this search will find all the extents that end after
	 * our range starts.
	 */
	node = tree_search(tree, start);
	अगर (!node)
		जाओ out;

	जबतक (1) अणु
		state = rb_entry(node, काष्ठा extent_state, rb_node);
		अगर (state->end >= start && (state->state & bits))
			वापस state;

		node = rb_next(node);
		अगर (!node)
			अवरोध;
	पूर्ण
out:
	वापस शून्य;
पूर्ण

/*
 * Find the first offset in the io tree with one or more @bits set.
 *
 * Note: If there are multiple bits set in @bits, any of them will match.
 *
 * Return 0 अगर we find something, and update @start_ret and @end_ret.
 * Return 1 अगर we found nothing.
 */
पूर्णांक find_first_extent_bit(काष्ठा extent_io_tree *tree, u64 start,
			  u64 *start_ret, u64 *end_ret, u32 bits,
			  काष्ठा extent_state **cached_state)
अणु
	काष्ठा extent_state *state;
	पूर्णांक ret = 1;

	spin_lock(&tree->lock);
	अगर (cached_state && *cached_state) अणु
		state = *cached_state;
		अगर (state->end == start - 1 && extent_state_in_tree(state)) अणु
			जबतक ((state = next_state(state)) != शून्य) अणु
				अगर (state->state & bits)
					जाओ got_it;
			पूर्ण
			मुक्त_extent_state(*cached_state);
			*cached_state = शून्य;
			जाओ out;
		पूर्ण
		मुक्त_extent_state(*cached_state);
		*cached_state = शून्य;
	पूर्ण

	state = find_first_extent_bit_state(tree, start, bits);
got_it:
	अगर (state) अणु
		cache_state_अगर_flags(state, cached_state, 0);
		*start_ret = state->start;
		*end_ret = state->end;
		ret = 0;
	पूर्ण
out:
	spin_unlock(&tree->lock);
	वापस ret;
पूर्ण

/**
 * Find a contiguous area of bits
 *
 * @tree:      io tree to check
 * @start:     offset to start the search from
 * @start_ret: the first offset we found with the bits set
 * @end_ret:   the final contiguous range of the bits that were set
 * @bits:      bits to look क्रम
 *
 * set_extent_bit and clear_extent_bit can temporarily split contiguous ranges
 * to set bits appropriately, and then merge them again.  During this समय it
 * will drop the tree->lock, so use this helper अगर you want to find the actual
 * contiguous area क्रम given bits.  We will search to the first bit we find, and
 * then walk करोwn the tree until we find a non-contiguous area.  The area
 * वापसed will be the full contiguous area with the bits set.
 */
पूर्णांक find_contiguous_extent_bit(काष्ठा extent_io_tree *tree, u64 start,
			       u64 *start_ret, u64 *end_ret, u32 bits)
अणु
	काष्ठा extent_state *state;
	पूर्णांक ret = 1;

	spin_lock(&tree->lock);
	state = find_first_extent_bit_state(tree, start, bits);
	अगर (state) अणु
		*start_ret = state->start;
		*end_ret = state->end;
		जबतक ((state = next_state(state)) != शून्य) अणु
			अगर (state->start > (*end_ret + 1))
				अवरोध;
			*end_ret = state->end;
		पूर्ण
		ret = 0;
	पूर्ण
	spin_unlock(&tree->lock);
	वापस ret;
पूर्ण

/**
 * Find the first range that has @bits not set. This range could start beक्रमe
 * @start.
 *
 * @tree:      the tree to search
 * @start:     offset at/after which the found extent should start
 * @start_ret: records the beginning of the range
 * @end_ret:   records the end of the range (inclusive)
 * @bits:      the set of bits which must be unset
 *
 * Since unallocated range is also considered one which करोesn't have the bits
 * set it's possible that @end_ret contains -1, this happens in हाल the range
 * spans (last_range_end, end of device]. In this हाल it's up to the caller to
 * trim @end_ret to the appropriate size.
 */
व्योम find_first_clear_extent_bit(काष्ठा extent_io_tree *tree, u64 start,
				 u64 *start_ret, u64 *end_ret, u32 bits)
अणु
	काष्ठा extent_state *state;
	काष्ठा rb_node *node, *prev = शून्य, *next;

	spin_lock(&tree->lock);

	/* Find first extent with bits cleared */
	जबतक (1) अणु
		node = __etree_search(tree, start, &next, &prev, शून्य, शून्य);
		अगर (!node && !next && !prev) अणु
			/*
			 * Tree is completely empty, send full range and let
			 * caller deal with it
			 */
			*start_ret = 0;
			*end_ret = -1;
			जाओ out;
		पूर्ण अन्यथा अगर (!node && !next) अणु
			/*
			 * We are past the last allocated chunk, set start at
			 * the end of the last extent.
			 */
			state = rb_entry(prev, काष्ठा extent_state, rb_node);
			*start_ret = state->end + 1;
			*end_ret = -1;
			जाओ out;
		पूर्ण अन्यथा अगर (!node) अणु
			node = next;
		पूर्ण
		/*
		 * At this poपूर्णांक 'node' either contains 'start' or start is
		 * beक्रमe 'node'
		 */
		state = rb_entry(node, काष्ठा extent_state, rb_node);

		अगर (in_range(start, state->start, state->end - state->start + 1)) अणु
			अगर (state->state & bits) अणु
				/*
				 * |--range with bits sets--|
				 *    |
				 *    start
				 */
				start = state->end + 1;
			पूर्ण अन्यथा अणु
				/*
				 * 'start' falls within a range that doesn't
				 * have the bits set, so take its start as
				 * the beginning of the desired range
				 *
				 * |--range with bits cleared----|
				 *      |
				 *      start
				 */
				*start_ret = state->start;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * |---prev range---|---hole/unset---|---node range---|
			 *                          |
			 *                        start
			 *
			 *                        or
			 *
			 * |---hole/unset--||--first node--|
			 * 0   |
			 *    start
			 */
			अगर (prev) अणु
				state = rb_entry(prev, काष्ठा extent_state,
						 rb_node);
				*start_ret = state->end + 1;
			पूर्ण अन्यथा अणु
				*start_ret = 0;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Find the दीर्घest stretch from start until an entry which has the
	 * bits set
	 */
	जबतक (1) अणु
		state = rb_entry(node, काष्ठा extent_state, rb_node);
		अगर (state->end >= start && !(state->state & bits)) अणु
			*end_ret = state->end;
		पूर्ण अन्यथा अणु
			*end_ret = state->start - 1;
			अवरोध;
		पूर्ण

		node = rb_next(node);
		अगर (!node)
			अवरोध;
	पूर्ण
out:
	spin_unlock(&tree->lock);
पूर्ण

/*
 * find a contiguous range of bytes in the file marked as delalloc, not
 * more than 'max_bytes'.  start and end are used to वापस the range,
 *
 * true is वापसed अगर we find something, false अगर nothing was in the tree
 */
bool btrfs_find_delalloc_range(काष्ठा extent_io_tree *tree, u64 *start,
			       u64 *end, u64 max_bytes,
			       काष्ठा extent_state **cached_state)
अणु
	काष्ठा rb_node *node;
	काष्ठा extent_state *state;
	u64 cur_start = *start;
	bool found = false;
	u64 total_bytes = 0;

	spin_lock(&tree->lock);

	/*
	 * this search will find all the extents that end after
	 * our range starts.
	 */
	node = tree_search(tree, cur_start);
	अगर (!node) अणु
		*end = (u64)-1;
		जाओ out;
	पूर्ण

	जबतक (1) अणु
		state = rb_entry(node, काष्ठा extent_state, rb_node);
		अगर (found && (state->start != cur_start ||
			      (state->state & EXTENT_BOUNDARY))) अणु
			जाओ out;
		पूर्ण
		अगर (!(state->state & EXTENT_DELALLOC)) अणु
			अगर (!found)
				*end = state->end;
			जाओ out;
		पूर्ण
		अगर (!found) अणु
			*start = state->start;
			*cached_state = state;
			refcount_inc(&state->refs);
		पूर्ण
		found = true;
		*end = state->end;
		cur_start = state->end + 1;
		node = rb_next(node);
		total_bytes += state->end - state->start + 1;
		अगर (total_bytes >= max_bytes)
			अवरोध;
		अगर (!node)
			अवरोध;
	पूर्ण
out:
	spin_unlock(&tree->lock);
	वापस found;
पूर्ण

अटल पूर्णांक __process_pages_contig(काष्ठा address_space *mapping,
				  काष्ठा page *locked_page,
				  pgoff_t start_index, pgoff_t end_index,
				  अचिन्हित दीर्घ page_ops, pgoff_t *index_ret);

अटल noअंतरभूत व्योम __unlock_क्रम_delalloc(काष्ठा inode *inode,
					   काष्ठा page *locked_page,
					   u64 start, u64 end)
अणु
	अचिन्हित दीर्घ index = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_index = end >> PAGE_SHIFT;

	ASSERT(locked_page);
	अगर (index == locked_page->index && end_index == index)
		वापस;

	__process_pages_contig(inode->i_mapping, locked_page, index, end_index,
			       PAGE_UNLOCK, शून्य);
पूर्ण

अटल noअंतरभूत पूर्णांक lock_delalloc_pages(काष्ठा inode *inode,
					काष्ठा page *locked_page,
					u64 delalloc_start,
					u64 delalloc_end)
अणु
	अचिन्हित दीर्घ index = delalloc_start >> PAGE_SHIFT;
	अचिन्हित दीर्घ index_ret = index;
	अचिन्हित दीर्घ end_index = delalloc_end >> PAGE_SHIFT;
	पूर्णांक ret;

	ASSERT(locked_page);
	अगर (index == locked_page->index && index == end_index)
		वापस 0;

	ret = __process_pages_contig(inode->i_mapping, locked_page, index,
				     end_index, PAGE_LOCK, &index_ret);
	अगर (ret == -EAGAIN)
		__unlock_क्रम_delalloc(inode, locked_page, delalloc_start,
				      (u64)index_ret << PAGE_SHIFT);
	वापस ret;
पूर्ण

/*
 * Find and lock a contiguous range of bytes in the file marked as delalloc, no
 * more than @max_bytes.  @Start and @end are used to वापस the range,
 *
 * Return: true अगर we find something
 *         false अगर nothing was in the tree
 */
EXPORT_FOR_TESTS
noअंतरभूत_क्रम_stack bool find_lock_delalloc_range(काष्ठा inode *inode,
				    काष्ठा page *locked_page, u64 *start,
				    u64 *end)
अणु
	काष्ठा extent_io_tree *tree = &BTRFS_I(inode)->io_tree;
	u64 max_bytes = BTRFS_MAX_EXTENT_SIZE;
	u64 delalloc_start;
	u64 delalloc_end;
	bool found;
	काष्ठा extent_state *cached_state = शून्य;
	पूर्णांक ret;
	पूर्णांक loops = 0;

again:
	/* step one, find a bunch of delalloc bytes starting at start */
	delalloc_start = *start;
	delalloc_end = 0;
	found = btrfs_find_delalloc_range(tree, &delalloc_start, &delalloc_end,
					  max_bytes, &cached_state);
	अगर (!found || delalloc_end <= *start) अणु
		*start = delalloc_start;
		*end = delalloc_end;
		मुक्त_extent_state(cached_state);
		वापस false;
	पूर्ण

	/*
	 * start comes from the offset of locked_page.  We have to lock
	 * pages in order, so we can't process delalloc bytes beक्रमe
	 * locked_page
	 */
	अगर (delalloc_start < *start)
		delalloc_start = *start;

	/*
	 * make sure to limit the number of pages we try to lock करोwn
	 */
	अगर (delalloc_end + 1 - delalloc_start > max_bytes)
		delalloc_end = delalloc_start + max_bytes - 1;

	/* step two, lock all the pages after the page that has start */
	ret = lock_delalloc_pages(inode, locked_page,
				  delalloc_start, delalloc_end);
	ASSERT(!ret || ret == -EAGAIN);
	अगर (ret == -EAGAIN) अणु
		/* some of the pages are gone, lets aव्योम looping by
		 * लघुening the size of the delalloc range we're searching
		 */
		मुक्त_extent_state(cached_state);
		cached_state = शून्य;
		अगर (!loops) अणु
			max_bytes = PAGE_SIZE;
			loops = 1;
			जाओ again;
		पूर्ण अन्यथा अणु
			found = false;
			जाओ out_failed;
		पूर्ण
	पूर्ण

	/* step three, lock the state bits क्रम the whole range */
	lock_extent_bits(tree, delalloc_start, delalloc_end, &cached_state);

	/* then test to make sure it is all still delalloc */
	ret = test_range_bit(tree, delalloc_start, delalloc_end,
			     EXTENT_DELALLOC, 1, cached_state);
	अगर (!ret) अणु
		unlock_extent_cached(tree, delalloc_start, delalloc_end,
				     &cached_state);
		__unlock_क्रम_delalloc(inode, locked_page,
			      delalloc_start, delalloc_end);
		cond_resched();
		जाओ again;
	पूर्ण
	मुक्त_extent_state(cached_state);
	*start = delalloc_start;
	*end = delalloc_end;
out_failed:
	वापस found;
पूर्ण

अटल पूर्णांक __process_pages_contig(काष्ठा address_space *mapping,
				  काष्ठा page *locked_page,
				  pgoff_t start_index, pgoff_t end_index,
				  अचिन्हित दीर्घ page_ops, pgoff_t *index_ret)
अणु
	अचिन्हित दीर्घ nr_pages = end_index - start_index + 1;
	अचिन्हित दीर्घ pages_processed = 0;
	pgoff_t index = start_index;
	काष्ठा page *pages[16];
	अचिन्हित ret;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (page_ops & PAGE_LOCK) अणु
		ASSERT(page_ops == PAGE_LOCK);
		ASSERT(index_ret && *index_ret == start_index);
	पूर्ण

	अगर ((page_ops & PAGE_SET_ERROR) && nr_pages > 0)
		mapping_set_error(mapping, -EIO);

	जबतक (nr_pages > 0) अणु
		ret = find_get_pages_contig(mapping, index,
				     min_t(अचिन्हित दीर्घ,
				     nr_pages, ARRAY_SIZE(pages)), pages);
		अगर (ret == 0) अणु
			/*
			 * Only अगर we're going to lock these pages,
			 * can we find nothing at @index.
			 */
			ASSERT(page_ops & PAGE_LOCK);
			err = -EAGAIN;
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < ret; i++) अणु
			अगर (page_ops & PAGE_SET_PRIVATE2)
				SetPagePrivate2(pages[i]);

			अगर (locked_page && pages[i] == locked_page) अणु
				put_page(pages[i]);
				pages_processed++;
				जारी;
			पूर्ण
			अगर (page_ops & PAGE_START_WRITEBACK) अणु
				clear_page_dirty_क्रम_io(pages[i]);
				set_page_ग_लिखोback(pages[i]);
			पूर्ण
			अगर (page_ops & PAGE_SET_ERROR)
				SetPageError(pages[i]);
			अगर (page_ops & PAGE_END_WRITEBACK)
				end_page_ग_लिखोback(pages[i]);
			अगर (page_ops & PAGE_UNLOCK)
				unlock_page(pages[i]);
			अगर (page_ops & PAGE_LOCK) अणु
				lock_page(pages[i]);
				अगर (!PageDirty(pages[i]) ||
				    pages[i]->mapping != mapping) अणु
					unlock_page(pages[i]);
					क्रम (; i < ret; i++)
						put_page(pages[i]);
					err = -EAGAIN;
					जाओ out;
				पूर्ण
			पूर्ण
			put_page(pages[i]);
			pages_processed++;
		पूर्ण
		nr_pages -= ret;
		index += ret;
		cond_resched();
	पूर्ण
out:
	अगर (err && index_ret)
		*index_ret = start_index + pages_processed - 1;
	वापस err;
पूर्ण

व्योम extent_clear_unlock_delalloc(काष्ठा btrfs_inode *inode, u64 start, u64 end,
				  काष्ठा page *locked_page,
				  u32 clear_bits, अचिन्हित दीर्घ page_ops)
अणु
	clear_extent_bit(&inode->io_tree, start, end, clear_bits, 1, 0, शून्य);

	__process_pages_contig(inode->vfs_inode.i_mapping, locked_page,
			       start >> PAGE_SHIFT, end >> PAGE_SHIFT,
			       page_ops, शून्य);
पूर्ण

/*
 * count the number of bytes in the tree that have a given bit(s)
 * set.  This can be fairly slow, except क्रम EXTENT_सूचीTY which is
 * cached.  The total number found is वापसed.
 */
u64 count_range_bits(काष्ठा extent_io_tree *tree,
		     u64 *start, u64 search_end, u64 max_bytes,
		     u32 bits, पूर्णांक contig)
अणु
	काष्ठा rb_node *node;
	काष्ठा extent_state *state;
	u64 cur_start = *start;
	u64 total_bytes = 0;
	u64 last = 0;
	पूर्णांक found = 0;

	अगर (WARN_ON(search_end <= cur_start))
		वापस 0;

	spin_lock(&tree->lock);
	अगर (cur_start == 0 && bits == EXTENT_सूचीTY) अणु
		total_bytes = tree->dirty_bytes;
		जाओ out;
	पूर्ण
	/*
	 * this search will find all the extents that end after
	 * our range starts.
	 */
	node = tree_search(tree, cur_start);
	अगर (!node)
		जाओ out;

	जबतक (1) अणु
		state = rb_entry(node, काष्ठा extent_state, rb_node);
		अगर (state->start > search_end)
			अवरोध;
		अगर (contig && found && state->start > last + 1)
			अवरोध;
		अगर (state->end >= cur_start && (state->state & bits) == bits) अणु
			total_bytes += min(search_end, state->end) + 1 -
				       max(cur_start, state->start);
			अगर (total_bytes >= max_bytes)
				अवरोध;
			अगर (!found) अणु
				*start = max(cur_start, state->start);
				found = 1;
			पूर्ण
			last = state->end;
		पूर्ण अन्यथा अगर (contig && found) अणु
			अवरोध;
		पूर्ण
		node = rb_next(node);
		अगर (!node)
			अवरोध;
	पूर्ण
out:
	spin_unlock(&tree->lock);
	वापस total_bytes;
पूर्ण

/*
 * set the निजी field क्रम a given byte offset in the tree.  If there isn't
 * an extent_state there alपढ़ोy, this करोes nothing.
 */
पूर्णांक set_state_failrec(काष्ठा extent_io_tree *tree, u64 start,
		      काष्ठा io_failure_record *failrec)
अणु
	काष्ठा rb_node *node;
	काष्ठा extent_state *state;
	पूर्णांक ret = 0;

	spin_lock(&tree->lock);
	/*
	 * this search will find all the extents that end after
	 * our range starts.
	 */
	node = tree_search(tree, start);
	अगर (!node) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	state = rb_entry(node, काष्ठा extent_state, rb_node);
	अगर (state->start != start) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	state->failrec = failrec;
out:
	spin_unlock(&tree->lock);
	वापस ret;
पूर्ण

काष्ठा io_failure_record *get_state_failrec(काष्ठा extent_io_tree *tree, u64 start)
अणु
	काष्ठा rb_node *node;
	काष्ठा extent_state *state;
	काष्ठा io_failure_record *failrec;

	spin_lock(&tree->lock);
	/*
	 * this search will find all the extents that end after
	 * our range starts.
	 */
	node = tree_search(tree, start);
	अगर (!node) अणु
		failrec = ERR_PTR(-ENOENT);
		जाओ out;
	पूर्ण
	state = rb_entry(node, काष्ठा extent_state, rb_node);
	अगर (state->start != start) अणु
		failrec = ERR_PTR(-ENOENT);
		जाओ out;
	पूर्ण

	failrec = state->failrec;
out:
	spin_unlock(&tree->lock);
	वापस failrec;
पूर्ण

/*
 * searches a range in the state tree क्रम a given mask.
 * If 'filled' == 1, this वापसs 1 only अगर every extent in the tree
 * has the bits set.  Otherwise, 1 is वापसed अगर any bit in the
 * range is found set.
 */
पूर्णांक test_range_bit(काष्ठा extent_io_tree *tree, u64 start, u64 end,
		   u32 bits, पूर्णांक filled, काष्ठा extent_state *cached)
अणु
	काष्ठा extent_state *state = शून्य;
	काष्ठा rb_node *node;
	पूर्णांक bitset = 0;

	spin_lock(&tree->lock);
	अगर (cached && extent_state_in_tree(cached) && cached->start <= start &&
	    cached->end > start)
		node = &cached->rb_node;
	अन्यथा
		node = tree_search(tree, start);
	जबतक (node && start <= end) अणु
		state = rb_entry(node, काष्ठा extent_state, rb_node);

		अगर (filled && state->start > start) अणु
			bitset = 0;
			अवरोध;
		पूर्ण

		अगर (state->start > end)
			अवरोध;

		अगर (state->state & bits) अणु
			bitset = 1;
			अगर (!filled)
				अवरोध;
		पूर्ण अन्यथा अगर (filled) अणु
			bitset = 0;
			अवरोध;
		पूर्ण

		अगर (state->end == (u64)-1)
			अवरोध;

		start = state->end + 1;
		अगर (start > end)
			अवरोध;
		node = rb_next(node);
		अगर (!node) अणु
			अगर (filled)
				bitset = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&tree->lock);
	वापस bitset;
पूर्ण

/*
 * helper function to set a given page up to date अगर all the
 * extents in the tree क्रम that page are up to date
 */
अटल व्योम check_page_uptodate(काष्ठा extent_io_tree *tree, काष्ठा page *page)
अणु
	u64 start = page_offset(page);
	u64 end = start + PAGE_SIZE - 1;
	अगर (test_range_bit(tree, start, end, EXTENT_UPTODATE, 1, शून्य))
		SetPageUptodate(page);
पूर्ण

पूर्णांक मुक्त_io_failure(काष्ठा extent_io_tree *failure_tree,
		    काष्ठा extent_io_tree *io_tree,
		    काष्ठा io_failure_record *rec)
अणु
	पूर्णांक ret;
	पूर्णांक err = 0;

	set_state_failrec(failure_tree, rec->start, शून्य);
	ret = clear_extent_bits(failure_tree, rec->start,
				rec->start + rec->len - 1,
				EXTENT_LOCKED | EXTENT_सूचीTY);
	अगर (ret)
		err = ret;

	ret = clear_extent_bits(io_tree, rec->start,
				rec->start + rec->len - 1,
				EXTENT_DAMAGED);
	अगर (ret && !err)
		err = ret;

	kमुक्त(rec);
	वापस err;
पूर्ण

/*
 * this bypasses the standard btrfs submit functions deliberately, as
 * the standard behavior is to ग_लिखो all copies in a raid setup. here we only
 * want to ग_लिखो the one bad copy. so we करो the mapping क्रम ourselves and issue
 * submit_bio directly.
 * to aव्योम any synchronization issues, रुको क्रम the data after writing, which
 * actually prevents the पढ़ो that triggered the error from finishing.
 * currently, there can be no more than two copies of every data bit. thus,
 * exactly one reग_लिखो is required.
 */
पूर्णांक repair_io_failure(काष्ठा btrfs_fs_info *fs_info, u64 ino, u64 start,
		      u64 length, u64 logical, काष्ठा page *page,
		      अचिन्हित पूर्णांक pg_offset, पूर्णांक mirror_num)
अणु
	काष्ठा bio *bio;
	काष्ठा btrfs_device *dev;
	u64 map_length = 0;
	u64 sector;
	काष्ठा btrfs_bio *bbio = शून्य;
	पूर्णांक ret;

	ASSERT(!(fs_info->sb->s_flags & SB_RDONLY));
	BUG_ON(!mirror_num);

	अगर (btrfs_is_zoned(fs_info))
		वापस btrfs_repair_one_zone(fs_info, logical);

	bio = btrfs_io_bio_alloc(1);
	bio->bi_iter.bi_size = 0;
	map_length = length;

	/*
	 * Aव्योम races with device replace and make sure our bbio has devices
	 * associated to its stripes that करोn't go away जबतक we are करोing the
	 * पढ़ो repair operation.
	 */
	btrfs_bio_counter_inc_blocked(fs_info);
	अगर (btrfs_is_parity_mirror(fs_info, logical, length)) अणु
		/*
		 * Note that we करोn't use BTRFS_MAP_WRITE because it's supposed
		 * to update all raid stripes, but here we just want to correct
		 * bad stripe, thus BTRFS_MAP_READ is abused to only get the bad
		 * stripe's dev and sector.
		 */
		ret = btrfs_map_block(fs_info, BTRFS_MAP_READ, logical,
				      &map_length, &bbio, 0);
		अगर (ret) अणु
			btrfs_bio_counter_dec(fs_info);
			bio_put(bio);
			वापस -EIO;
		पूर्ण
		ASSERT(bbio->mirror_num == 1);
	पूर्ण अन्यथा अणु
		ret = btrfs_map_block(fs_info, BTRFS_MAP_WRITE, logical,
				      &map_length, &bbio, mirror_num);
		अगर (ret) अणु
			btrfs_bio_counter_dec(fs_info);
			bio_put(bio);
			वापस -EIO;
		पूर्ण
		BUG_ON(mirror_num != bbio->mirror_num);
	पूर्ण

	sector = bbio->stripes[bbio->mirror_num - 1].physical >> 9;
	bio->bi_iter.bi_sector = sector;
	dev = bbio->stripes[bbio->mirror_num - 1].dev;
	btrfs_put_bbio(bbio);
	अगर (!dev || !dev->bdev ||
	    !test_bit(BTRFS_DEV_STATE_WRITEABLE, &dev->dev_state)) अणु
		btrfs_bio_counter_dec(fs_info);
		bio_put(bio);
		वापस -EIO;
	पूर्ण
	bio_set_dev(bio, dev->bdev);
	bio->bi_opf = REQ_OP_WRITE | REQ_SYNC;
	bio_add_page(bio, page, length, pg_offset);

	अगर (btrfsic_submit_bio_रुको(bio)) अणु
		/* try to remap that extent अन्यथाwhere? */
		btrfs_bio_counter_dec(fs_info);
		bio_put(bio);
		btrfs_dev_stat_inc_and_prपूर्णांक(dev, BTRFS_DEV_STAT_WRITE_ERRS);
		वापस -EIO;
	पूर्ण

	btrfs_info_rl_in_rcu(fs_info,
		"read error corrected: ino %llu off %llu (dev %s sector %llu)",
				  ino, start,
				  rcu_str_deref(dev->name), sector);
	btrfs_bio_counter_dec(fs_info);
	bio_put(bio);
	वापस 0;
पूर्ण

पूर्णांक btrfs_repair_eb_io_failure(स्थिर काष्ठा extent_buffer *eb, पूर्णांक mirror_num)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	u64 start = eb->start;
	पूर्णांक i, num_pages = num_extent_pages(eb);
	पूर्णांक ret = 0;

	अगर (sb_rकरोnly(fs_info->sb))
		वापस -EROFS;

	क्रम (i = 0; i < num_pages; i++) अणु
		काष्ठा page *p = eb->pages[i];

		ret = repair_io_failure(fs_info, 0, start, PAGE_SIZE, start, p,
					start - page_offset(p), mirror_num);
		अगर (ret)
			अवरोध;
		start += PAGE_SIZE;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * each समय an IO finishes, we करो a fast check in the IO failure tree
 * to see अगर we need to process or clean up an io_failure_record
 */
पूर्णांक clean_io_failure(काष्ठा btrfs_fs_info *fs_info,
		     काष्ठा extent_io_tree *failure_tree,
		     काष्ठा extent_io_tree *io_tree, u64 start,
		     काष्ठा page *page, u64 ino, अचिन्हित पूर्णांक pg_offset)
अणु
	u64 निजी;
	काष्ठा io_failure_record *failrec;
	काष्ठा extent_state *state;
	पूर्णांक num_copies;
	पूर्णांक ret;

	निजी = 0;
	ret = count_range_bits(failure_tree, &निजी, (u64)-1, 1,
			       EXTENT_सूचीTY, 0);
	अगर (!ret)
		वापस 0;

	failrec = get_state_failrec(failure_tree, start);
	अगर (IS_ERR(failrec))
		वापस 0;

	BUG_ON(!failrec->this_mirror);

	अगर (failrec->in_validation) अणु
		/* there was no real error, just मुक्त the record */
		btrfs_debug(fs_info,
			"clean_io_failure: freeing dummy error at %llu",
			failrec->start);
		जाओ out;
	पूर्ण
	अगर (sb_rकरोnly(fs_info->sb))
		जाओ out;

	spin_lock(&io_tree->lock);
	state = find_first_extent_bit_state(io_tree,
					    failrec->start,
					    EXTENT_LOCKED);
	spin_unlock(&io_tree->lock);

	अगर (state && state->start <= failrec->start &&
	    state->end >= failrec->start + failrec->len - 1) अणु
		num_copies = btrfs_num_copies(fs_info, failrec->logical,
					      failrec->len);
		अगर (num_copies > 1)  अणु
			repair_io_failure(fs_info, ino, start, failrec->len,
					  failrec->logical, page, pg_offset,
					  failrec->failed_mirror);
		पूर्ण
	पूर्ण

out:
	मुक्त_io_failure(failure_tree, io_tree, failrec);

	वापस 0;
पूर्ण

/*
 * Can be called when
 * - hold extent lock
 * - under ordered extent
 * - the inode is मुक्तing
 */
व्योम btrfs_मुक्त_io_failure_record(काष्ठा btrfs_inode *inode, u64 start, u64 end)
अणु
	काष्ठा extent_io_tree *failure_tree = &inode->io_failure_tree;
	काष्ठा io_failure_record *failrec;
	काष्ठा extent_state *state, *next;

	अगर (RB_EMPTY_ROOT(&failure_tree->state))
		वापस;

	spin_lock(&failure_tree->lock);
	state = find_first_extent_bit_state(failure_tree, start, EXTENT_सूचीTY);
	जबतक (state) अणु
		अगर (state->start > end)
			अवरोध;

		ASSERT(state->end <= end);

		next = next_state(state);

		failrec = state->failrec;
		मुक्त_extent_state(state);
		kमुक्त(failrec);

		state = next;
	पूर्ण
	spin_unlock(&failure_tree->lock);
पूर्ण

अटल काष्ठा io_failure_record *btrfs_get_io_failure_record(काष्ठा inode *inode,
							     u64 start, u64 end)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा io_failure_record *failrec;
	काष्ठा extent_map *em;
	काष्ठा extent_io_tree *failure_tree = &BTRFS_I(inode)->io_failure_tree;
	काष्ठा extent_io_tree *tree = &BTRFS_I(inode)->io_tree;
	काष्ठा extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	पूर्णांक ret;
	u64 logical;

	failrec = get_state_failrec(failure_tree, start);
	अगर (!IS_ERR(failrec)) अणु
		btrfs_debug(fs_info,
			"Get IO Failure Record: (found) logical=%llu, start=%llu, len=%llu, validation=%d",
			failrec->logical, failrec->start, failrec->len,
			failrec->in_validation);
		/*
		 * when data can be on disk more than twice, add to failrec here
		 * (e.g. with a list क्रम failed_mirror) to make
		 * clean_io_failure() clean all those errors at once.
		 */

		वापस failrec;
	पूर्ण

	failrec = kzalloc(माप(*failrec), GFP_NOFS);
	अगर (!failrec)
		वापस ERR_PTR(-ENOMEM);

	failrec->start = start;
	failrec->len = end - start + 1;
	failrec->this_mirror = 0;
	failrec->bio_flags = 0;
	failrec->in_validation = 0;

	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, start, failrec->len);
	अगर (!em) अणु
		पढ़ो_unlock(&em_tree->lock);
		kमुक्त(failrec);
		वापस ERR_PTR(-EIO);
	पूर्ण

	अगर (em->start > start || em->start + em->len <= start) अणु
		मुक्त_extent_map(em);
		em = शून्य;
	पूर्ण
	पढ़ो_unlock(&em_tree->lock);
	अगर (!em) अणु
		kमुक्त(failrec);
		वापस ERR_PTR(-EIO);
	पूर्ण

	logical = start - em->start;
	logical = em->block_start + logical;
	अगर (test_bit(EXTENT_FLAG_COMPRESSED, &em->flags)) अणु
		logical = em->block_start;
		failrec->bio_flags = EXTENT_BIO_COMPRESSED;
		extent_set_compress_type(&failrec->bio_flags, em->compress_type);
	पूर्ण

	btrfs_debug(fs_info,
		    "Get IO Failure Record: (new) logical=%llu, start=%llu, len=%llu",
		    logical, start, failrec->len);

	failrec->logical = logical;
	मुक्त_extent_map(em);

	/* Set the bits in the निजी failure tree */
	ret = set_extent_bits(failure_tree, start, end,
			      EXTENT_LOCKED | EXTENT_सूचीTY);
	अगर (ret >= 0) अणु
		ret = set_state_failrec(failure_tree, start, failrec);
		/* Set the bits in the inode's tree */
		ret = set_extent_bits(tree, start, end, EXTENT_DAMAGED);
	पूर्ण अन्यथा अगर (ret < 0) अणु
		kमुक्त(failrec);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस failrec;
पूर्ण

अटल bool btrfs_check_repairable(काष्ठा inode *inode, bool needs_validation,
				   काष्ठा io_failure_record *failrec,
				   पूर्णांक failed_mirror)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	पूर्णांक num_copies;

	num_copies = btrfs_num_copies(fs_info, failrec->logical, failrec->len);
	अगर (num_copies == 1) अणु
		/*
		 * we only have a single copy of the data, so करोn't bother with
		 * all the retry and error correction code that follows. no
		 * matter what the error is, it is very likely to persist.
		 */
		btrfs_debug(fs_info,
			"Check Repairable: cannot repair, num_copies=%d, next_mirror %d, failed_mirror %d",
			num_copies, failrec->this_mirror, failed_mirror);
		वापस false;
	पूर्ण

	/*
	 * there are two premises:
	 *	a) deliver good data to the caller
	 *	b) correct the bad sectors on disk
	 */
	अगर (needs_validation) अणु
		/*
		 * to fulfill b), we need to know the exact failing sectors, as
		 * we करोn't want to reग_लिखो any more than the failed ones. thus,
		 * we need separate पढ़ो requests क्रम the failed bio
		 *
		 * अगर the following BUG_ON triggers, our validation request got
		 * merged. we need separate requests क्रम our algorithm to work.
		 */
		BUG_ON(failrec->in_validation);
		failrec->in_validation = 1;
		failrec->this_mirror = failed_mirror;
	पूर्ण अन्यथा अणु
		/*
		 * we're पढ़ोy to fulfill a) and b) aदीर्घside. get a good copy
		 * of the failed sector and अगर we succeed, we have setup
		 * everything क्रम repair_io_failure to करो the rest क्रम us.
		 */
		अगर (failrec->in_validation) अणु
			BUG_ON(failrec->this_mirror != failed_mirror);
			failrec->in_validation = 0;
			failrec->this_mirror = 0;
		पूर्ण
		failrec->failed_mirror = failed_mirror;
		failrec->this_mirror++;
		अगर (failrec->this_mirror == failed_mirror)
			failrec->this_mirror++;
	पूर्ण

	अगर (failrec->this_mirror > num_copies) अणु
		btrfs_debug(fs_info,
			"Check Repairable: (fail) num_copies=%d, next_mirror %d, failed_mirror %d",
			num_copies, failrec->this_mirror, failed_mirror);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool btrfs_io_needs_validation(काष्ठा inode *inode, काष्ठा bio *bio)
अणु
	u64 len = 0;
	स्थिर u32 blocksize = inode->i_sb->s_blocksize;

	/*
	 * If bi_status is BLK_STS_OK, then this was a checksum error, not an
	 * I/O error. In this हाल, we alपढ़ोy know exactly which sector was
	 * bad, so we करोn't need to validate.
	 */
	अगर (bio->bi_status == BLK_STS_OK)
		वापस false;

	/*
	 * We need to validate each sector inभागidually अगर the failed I/O was
	 * क्रम multiple sectors.
	 *
	 * There are a few possible bios that can end up here:
	 * 1. A buffered पढ़ो bio, which is not cloned.
	 * 2. A direct I/O पढ़ो bio, which is cloned.
	 * 3. A (buffered or direct) repair bio, which is not cloned.
	 *
	 * For cloned bios (हाल 2), we can get the size from
	 * btrfs_io_bio->iter; क्रम non-cloned bios (हालs 1 and 3), we can get
	 * it from the bvecs.
	 */
	अगर (bio_flagged(bio, BIO_CLONED)) अणु
		अगर (btrfs_io_bio(bio)->iter.bi_size > blocksize)
			वापस true;
	पूर्ण अन्यथा अणु
		काष्ठा bio_vec *bvec;
		पूर्णांक i;

		bio_क्रम_each_bvec_all(bvec, bio, i) अणु
			len += bvec->bv_len;
			अगर (len > blocksize)
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

blk_status_t btrfs_submit_पढ़ो_repair(काष्ठा inode *inode,
				      काष्ठा bio *failed_bio, u32 bio_offset,
				      काष्ठा page *page, अचिन्हित पूर्णांक pgoff,
				      u64 start, u64 end, पूर्णांक failed_mirror,
				      submit_bio_hook_t *submit_bio_hook)
अणु
	काष्ठा io_failure_record *failrec;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	काष्ठा extent_io_tree *tree = &BTRFS_I(inode)->io_tree;
	काष्ठा extent_io_tree *failure_tree = &BTRFS_I(inode)->io_failure_tree;
	काष्ठा btrfs_io_bio *failed_io_bio = btrfs_io_bio(failed_bio);
	स्थिर पूर्णांक icsum = bio_offset >> fs_info->sectorsize_bits;
	bool need_validation;
	काष्ठा bio *repair_bio;
	काष्ठा btrfs_io_bio *repair_io_bio;
	blk_status_t status;

	btrfs_debug(fs_info,
		   "repair read error: read error at %llu", start);

	BUG_ON(bio_op(failed_bio) == REQ_OP_WRITE);

	failrec = btrfs_get_io_failure_record(inode, start, end);
	अगर (IS_ERR(failrec))
		वापस त्रुटि_सं_to_blk_status(PTR_ERR(failrec));

	need_validation = btrfs_io_needs_validation(inode, failed_bio);

	अगर (!btrfs_check_repairable(inode, need_validation, failrec,
				    failed_mirror)) अणु
		मुक्त_io_failure(failure_tree, tree, failrec);
		वापस BLK_STS_IOERR;
	पूर्ण

	repair_bio = btrfs_io_bio_alloc(1);
	repair_io_bio = btrfs_io_bio(repair_bio);
	repair_bio->bi_opf = REQ_OP_READ;
	अगर (need_validation)
		repair_bio->bi_opf |= REQ_FAILFAST_DEV;
	repair_bio->bi_end_io = failed_bio->bi_end_io;
	repair_bio->bi_iter.bi_sector = failrec->logical >> 9;
	repair_bio->bi_निजी = failed_bio->bi_निजी;

	अगर (failed_io_bio->csum) अणु
		स्थिर u32 csum_size = fs_info->csum_size;

		repair_io_bio->csum = repair_io_bio->csum_अंतरभूत;
		स_नकल(repair_io_bio->csum,
		       failed_io_bio->csum + csum_size * icsum, csum_size);
	पूर्ण

	bio_add_page(repair_bio, page, failrec->len, pgoff);
	repair_io_bio->logical = failrec->start;
	repair_io_bio->iter = repair_bio->bi_iter;

	btrfs_debug(btrfs_sb(inode->i_sb),
"repair read error: submitting new read to mirror %d, in_validation=%d",
		    failrec->this_mirror, failrec->in_validation);

	status = submit_bio_hook(inode, repair_bio, failrec->this_mirror,
				 failrec->bio_flags);
	अगर (status) अणु
		मुक्त_io_failure(failure_tree, tree, failrec);
		bio_put(repair_bio);
	पूर्ण
	वापस status;
पूर्ण

/* lots and lots of room क्रम perक्रमmance fixes in the end_bio funcs */

व्योम end_extent_ग_लिखोpage(काष्ठा page *page, पूर्णांक err, u64 start, u64 end)
अणु
	पूर्णांक uptodate = (err == 0);
	पूर्णांक ret = 0;

	btrfs_ग_लिखोpage_endio_finish_ordered(page, start, end, uptodate);

	अगर (!uptodate) अणु
		ClearPageUptodate(page);
		SetPageError(page);
		ret = err < 0 ? err : -EIO;
		mapping_set_error(page->mapping, ret);
	पूर्ण
पूर्ण

/*
 * after a ग_लिखोpage IO is करोne, we need to:
 * clear the uptodate bits on error
 * clear the ग_लिखोback bits in the extent tree क्रम this IO
 * end_page_ग_लिखोback अगर the page has no more pending IO
 *
 * Scheduling is not allowed, so the extent state tree is expected
 * to have one and only one object corresponding to this IO.
 */
अटल व्योम end_bio_extent_ग_लिखोpage(काष्ठा bio *bio)
अणु
	पूर्णांक error = blk_status_to_त्रुटि_सं(bio->bi_status);
	काष्ठा bio_vec *bvec;
	u64 start;
	u64 end;
	काष्ठा bvec_iter_all iter_all;
	bool first_bvec = true;

	ASSERT(!bio_flagged(bio, BIO_CLONED));
	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;
		काष्ठा inode *inode = page->mapping->host;
		काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);

		/* We always issue full-page पढ़ोs, but अगर some block
		 * in a page fails to पढ़ो, blk_update_request() will
		 * advance bv_offset and adjust bv_len to compensate.
		 * Prपूर्णांक a warning क्रम nonzero offsets, and an error
		 * अगर they करोn't add up to a full page.  */
		अगर (bvec->bv_offset || bvec->bv_len != PAGE_SIZE) अणु
			अगर (bvec->bv_offset + bvec->bv_len != PAGE_SIZE)
				btrfs_err(fs_info,
				   "partial page write in btrfs with offset %u and length %u",
					bvec->bv_offset, bvec->bv_len);
			अन्यथा
				btrfs_info(fs_info,
				   "incomplete page write in btrfs with offset %u and length %u",
					bvec->bv_offset, bvec->bv_len);
		पूर्ण

		start = page_offset(page);
		end = start + bvec->bv_offset + bvec->bv_len - 1;

		अगर (first_bvec) अणु
			btrfs_record_physical_zoned(inode, start, bio);
			first_bvec = false;
		पूर्ण

		end_extent_ग_लिखोpage(page, error, start, end);
		end_page_ग_लिखोback(page);
	पूर्ण

	bio_put(bio);
पूर्ण

/*
 * Record previously processed extent range
 *
 * For endio_पढ़ोpage_release_extent() to handle a full extent range, reducing
 * the extent io operations.
 */
काष्ठा processed_extent अणु
	काष्ठा btrfs_inode *inode;
	/* Start of the range in @inode */
	u64 start;
	/* End of the range in @inode */
	u64 end;
	bool uptodate;
पूर्ण;

/*
 * Try to release processed extent range
 *
 * May not release the extent range right now अगर the current range is
 * contiguous to processed extent.
 *
 * Will release processed extent when any of @inode, @uptodate, the range is
 * no दीर्घer contiguous to the processed range.
 *
 * Passing @inode == शून्य will क्रमce processed extent to be released.
 */
अटल व्योम endio_पढ़ोpage_release_extent(काष्ठा processed_extent *processed,
			      काष्ठा btrfs_inode *inode, u64 start, u64 end,
			      bool uptodate)
अणु
	काष्ठा extent_state *cached = शून्य;
	काष्ठा extent_io_tree *tree;

	/* The first extent, initialize @processed */
	अगर (!processed->inode)
		जाओ update;

	/*
	 * Contiguous to processed extent, just uptodate the end.
	 *
	 * Several things to notice:
	 *
	 * - bio can be merged as दीर्घ as on-disk bytenr is contiguous
	 *   This means we can have page beदीर्घing to other inodes, thus need to
	 *   check अगर the inode still matches.
	 * - bvec can contain range beyond current page क्रम multi-page bvec
	 *   Thus we need to करो processed->end + 1 >= start check
	 */
	अगर (processed->inode == inode && processed->uptodate == uptodate &&
	    processed->end + 1 >= start && end >= processed->end) अणु
		processed->end = end;
		वापस;
	पूर्ण

	tree = &processed->inode->io_tree;
	/*
	 * Now we करोn't have range contiguous to the processed range, release
	 * the processed range now.
	 */
	अगर (processed->uptodate && tree->track_uptodate)
		set_extent_uptodate(tree, processed->start, processed->end,
				    &cached, GFP_ATOMIC);
	unlock_extent_cached_atomic(tree, processed->start, processed->end,
				    &cached);

update:
	/* Update processed to current range */
	processed->inode = inode;
	processed->start = start;
	processed->end = end;
	processed->uptodate = uptodate;
पूर्ण

अटल व्योम begin_page_पढ़ो(काष्ठा btrfs_fs_info *fs_info, काष्ठा page *page)
अणु
	ASSERT(PageLocked(page));
	अगर (fs_info->sectorsize == PAGE_SIZE)
		वापस;

	ASSERT(PagePrivate(page));
	btrfs_subpage_start_पढ़ोer(fs_info, page, page_offset(page), PAGE_SIZE);
पूर्ण

अटल व्योम end_page_पढ़ो(काष्ठा page *page, bool uptodate, u64 start, u32 len)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(page->mapping->host->i_sb);

	ASSERT(page_offset(page) <= start &&
		start + len <= page_offset(page) + PAGE_SIZE);

	अगर (uptodate) अणु
		btrfs_page_set_uptodate(fs_info, page, start, len);
	पूर्ण अन्यथा अणु
		btrfs_page_clear_uptodate(fs_info, page, start, len);
		btrfs_page_set_error(fs_info, page, start, len);
	पूर्ण

	अगर (fs_info->sectorsize == PAGE_SIZE)
		unlock_page(page);
	अन्यथा अगर (is_data_inode(page->mapping->host))
		/*
		 * For subpage data, unlock the page अगर we're the last पढ़ोer.
		 * For subpage metadata, page lock is not utilized क्रम पढ़ो.
		 */
		btrfs_subpage_end_पढ़ोer(fs_info, page, start, len);
पूर्ण

/*
 * Find extent buffer क्रम a givne bytenr.
 *
 * This is क्रम end_bio_extent_पढ़ोpage(), thus we can't करो any unsafe locking
 * in endio context.
 */
अटल काष्ठा extent_buffer *find_extent_buffer_पढ़ोpage(
		काष्ठा btrfs_fs_info *fs_info, काष्ठा page *page, u64 bytenr)
अणु
	काष्ठा extent_buffer *eb;

	/*
	 * For regular sectorsize, we can use page->निजी to grab extent
	 * buffer
	 */
	अगर (fs_info->sectorsize == PAGE_SIZE) अणु
		ASSERT(PagePrivate(page) && page->निजी);
		वापस (काष्ठा extent_buffer *)page->निजी;
	पूर्ण

	/* For subpage हाल, we need to lookup buffer radix tree */
	rcu_पढ़ो_lock();
	eb = radix_tree_lookup(&fs_info->buffer_radix,
			       bytenr >> fs_info->sectorsize_bits);
	rcu_पढ़ो_unlock();
	ASSERT(eb);
	वापस eb;
पूर्ण

/*
 * after a पढ़ोpage IO is करोne, we need to:
 * clear the uptodate bits on error
 * set the uptodate bits अगर things worked
 * set the page up to date अगर all extents in the tree are uptodate
 * clear the lock bit in the extent tree
 * unlock the page अगर there are no other extents locked क्रम it
 *
 * Scheduling is not allowed, so the extent state tree is expected
 * to have one and only one object corresponding to this IO.
 */
अटल व्योम end_bio_extent_पढ़ोpage(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	पूर्णांक uptodate = !bio->bi_status;
	काष्ठा btrfs_io_bio *io_bio = btrfs_io_bio(bio);
	काष्ठा extent_io_tree *tree, *failure_tree;
	काष्ठा processed_extent processed = अणु 0 पूर्ण;
	/*
	 * The offset to the beginning of a bio, since one bio can never be
	 * larger than अच_पूर्णांक_उच्च, u32 here is enough.
	 */
	u32 bio_offset = 0;
	पूर्णांक mirror;
	पूर्णांक ret;
	काष्ठा bvec_iter_all iter_all;

	ASSERT(!bio_flagged(bio, BIO_CLONED));
	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;
		काष्ठा inode *inode = page->mapping->host;
		काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
		स्थिर u32 sectorsize = fs_info->sectorsize;
		u64 start;
		u64 end;
		u32 len;

		btrfs_debug(fs_info,
			"end_bio_extent_readpage: bi_sector=%llu, err=%d, mirror=%u",
			bio->bi_iter.bi_sector, bio->bi_status,
			io_bio->mirror_num);
		tree = &BTRFS_I(inode)->io_tree;
		failure_tree = &BTRFS_I(inode)->io_failure_tree;

		/*
		 * We always issue full-sector पढ़ोs, but अगर some block in a
		 * page fails to पढ़ो, blk_update_request() will advance
		 * bv_offset and adjust bv_len to compensate.  Prपूर्णांक a warning
		 * क्रम unaligned offsets, and an error अगर they करोn't add up to
		 * a full sector.
		 */
		अगर (!IS_ALIGNED(bvec->bv_offset, sectorsize))
			btrfs_err(fs_info,
		"partial page read in btrfs with offset %u and length %u",
				  bvec->bv_offset, bvec->bv_len);
		अन्यथा अगर (!IS_ALIGNED(bvec->bv_offset + bvec->bv_len,
				     sectorsize))
			btrfs_info(fs_info,
		"incomplete page read with offset %u and length %u",
				   bvec->bv_offset, bvec->bv_len);

		start = page_offset(page) + bvec->bv_offset;
		end = start + bvec->bv_len - 1;
		len = bvec->bv_len;

		mirror = io_bio->mirror_num;
		अगर (likely(uptodate)) अणु
			अगर (is_data_inode(inode))
				ret = btrfs_verअगरy_data_csum(io_bio,
						bio_offset, page, start, end);
			अन्यथा
				ret = btrfs_validate_metadata_buffer(io_bio,
					page, start, end, mirror);
			अगर (ret)
				uptodate = 0;
			अन्यथा
				clean_io_failure(BTRFS_I(inode)->root->fs_info,
						 failure_tree, tree, start,
						 page,
						 btrfs_ino(BTRFS_I(inode)), 0);
		पूर्ण

		अगर (likely(uptodate))
			जाओ पढ़ोpage_ok;

		अगर (is_data_inode(inode)) अणु

			/*
			 * The generic bio_पढ़ोpage_error handles errors the
			 * following way: If possible, new पढ़ो requests are
			 * created and submitted and will end up in
			 * end_bio_extent_पढ़ोpage as well (अगर we're lucky,
			 * not in the !uptodate हाल). In that हाल it वापसs
			 * 0 and we just go on with the next page in our bio.
			 * If it can't handle the error it will वापस -EIO and
			 * we reमुख्य responsible क्रम that page.
			 */
			अगर (!btrfs_submit_पढ़ो_repair(inode, bio, bio_offset,
						page,
						start - page_offset(page),
						start, end, mirror,
						btrfs_submit_data_bio)) अणु
				uptodate = !bio->bi_status;
				ASSERT(bio_offset + len > bio_offset);
				bio_offset += len;
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा extent_buffer *eb;

			eb = find_extent_buffer_पढ़ोpage(fs_info, page, start);
			set_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags);
			eb->पढ़ो_mirror = mirror;
			atomic_dec(&eb->io_pages);
			अगर (test_and_clear_bit(EXTENT_BUFFER_READAHEAD,
					       &eb->bflags))
				btree_पढ़ोahead_hook(eb, -EIO);
		पूर्ण
पढ़ोpage_ok:
		अगर (likely(uptodate)) अणु
			loff_t i_size = i_size_पढ़ो(inode);
			pgoff_t end_index = i_size >> PAGE_SHIFT;

			/*
			 * Zero out the reमुख्यing part अगर this range straddles
			 * i_size.
			 *
			 * Here we should only zero the range inside the bvec,
			 * not touch anything अन्यथा.
			 *
			 * NOTE: i_size is exclusive जबतक end is inclusive.
			 */
			अगर (page->index == end_index && i_size <= end) अणु
				u32 zero_start = max(offset_in_page(i_size),
						     offset_in_page(start));

				zero_user_segment(page, zero_start,
						  offset_in_page(end) + 1);
			पूर्ण
		पूर्ण
		ASSERT(bio_offset + len > bio_offset);
		bio_offset += len;

		/* Update page status and unlock */
		end_page_पढ़ो(page, uptodate, start, len);
		endio_पढ़ोpage_release_extent(&processed, BTRFS_I(inode),
					      start, end, uptodate);
	पूर्ण
	/* Release the last extent */
	endio_पढ़ोpage_release_extent(&processed, शून्य, 0, 0, false);
	btrfs_io_bio_मुक्त_csum(io_bio);
	bio_put(bio);
पूर्ण

/*
 * Initialize the members up to but not including 'bio'. Use after allocating a
 * new bio by bio_alloc_bioset as it करोes not initialize the bytes outside of
 * 'bio' because use of __GFP_ZERO is not supported.
 */
अटल अंतरभूत व्योम btrfs_io_bio_init(काष्ठा btrfs_io_bio *btrfs_bio)
अणु
	स_रखो(btrfs_bio, 0, दुरत्व(काष्ठा btrfs_io_bio, bio));
पूर्ण

/*
 * The following helpers allocate a bio. As it's backed by a bioset, it'll
 * never fail.  We're वापसing a bio right now but you can call btrfs_io_bio
 * क्रम the appropriate container_of magic
 */
काष्ठा bio *btrfs_bio_alloc(u64 first_byte)
अणु
	काष्ठा bio *bio;

	bio = bio_alloc_bioset(GFP_NOFS, BIO_MAX_VECS, &btrfs_bioset);
	bio->bi_iter.bi_sector = first_byte >> 9;
	btrfs_io_bio_init(btrfs_io_bio(bio));
	वापस bio;
पूर्ण

काष्ठा bio *btrfs_bio_clone(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_io_bio *btrfs_bio;
	काष्ठा bio *new;

	/* Bio allocation backed by a bioset करोes not fail */
	new = bio_clone_fast(bio, GFP_NOFS, &btrfs_bioset);
	btrfs_bio = btrfs_io_bio(new);
	btrfs_io_bio_init(btrfs_bio);
	btrfs_bio->iter = bio->bi_iter;
	वापस new;
पूर्ण

काष्ठा bio *btrfs_io_bio_alloc(अचिन्हित पूर्णांक nr_iovecs)
अणु
	काष्ठा bio *bio;

	/* Bio allocation backed by a bioset करोes not fail */
	bio = bio_alloc_bioset(GFP_NOFS, nr_iovecs, &btrfs_bioset);
	btrfs_io_bio_init(btrfs_io_bio(bio));
	वापस bio;
पूर्ण

काष्ठा bio *btrfs_bio_clone_partial(काष्ठा bio *orig, पूर्णांक offset, पूर्णांक size)
अणु
	काष्ठा bio *bio;
	काष्ठा btrfs_io_bio *btrfs_bio;

	/* this will never fail when it's backed by a bioset */
	bio = bio_clone_fast(orig, GFP_NOFS, &btrfs_bioset);
	ASSERT(bio);

	btrfs_bio = btrfs_io_bio(bio);
	btrfs_io_bio_init(btrfs_bio);

	bio_trim(bio, offset >> 9, size >> 9);
	btrfs_bio->iter = bio->bi_iter;
	वापस bio;
पूर्ण

/**
 * Attempt to add a page to bio
 *
 * @bio:	destination bio
 * @page:	page to add to the bio
 * @disk_bytenr:  offset of the new bio or to check whether we are adding
 *                a contiguous page to the previous one
 * @pg_offset:	starting offset in the page
 * @size:	portion of page that we want to ग_लिखो
 * @prev_bio_flags:  flags of previous bio to see अगर we can merge the current one
 * @bio_flags:	flags of the current bio to see अगर we can merge them
 * @वापस:	true अगर page was added, false otherwise
 *
 * Attempt to add a page to bio considering stripe alignment etc.
 *
 * Return true अगर successfully page added. Otherwise, वापस false.
 */
अटल bool btrfs_bio_add_page(काष्ठा bio *bio, काष्ठा page *page,
			       u64 disk_bytenr, अचिन्हित पूर्णांक size,
			       अचिन्हित पूर्णांक pg_offset,
			       अचिन्हित दीर्घ prev_bio_flags,
			       अचिन्हित दीर्घ bio_flags)
अणु
	स्थिर sector_t sector = disk_bytenr >> SECTOR_SHIFT;
	bool contig;
	पूर्णांक ret;

	अगर (prev_bio_flags != bio_flags)
		वापस false;

	अगर (prev_bio_flags & EXTENT_BIO_COMPRESSED)
		contig = bio->bi_iter.bi_sector == sector;
	अन्यथा
		contig = bio_end_sector(bio) == sector;
	अगर (!contig)
		वापस false;

	अगर (btrfs_bio_fits_in_stripe(page, size, bio, bio_flags))
		वापस false;

	अगर (bio_op(bio) == REQ_OP_ZONE_APPEND) अणु
		काष्ठा page *first_page = bio_first_bvec_all(bio)->bv_page;

		अगर (!btrfs_bio_fits_in_ordered_extent(first_page, bio, size))
			वापस false;
		ret = bio_add_zone_append_page(bio, page, size, pg_offset);
	पूर्ण अन्यथा अणु
		ret = bio_add_page(bio, page, size, pg_offset);
	पूर्ण

	वापस ret == size;
पूर्ण

/*
 * @opf:	bio REQ_OP_* and REQ_* flags as one value
 * @wbc:	optional ग_लिखोback control क्रम io accounting
 * @page:	page to add to the bio
 * @disk_bytenr: logical bytenr where the ग_लिखो will be
 * @size:	portion of page that we want to ग_लिखो to
 * @pg_offset:	offset of the new bio or to check whether we are adding
 *              a contiguous page to the previous one
 * @bio_ret:	must be valid poपूर्णांकer, newly allocated bio will be stored there
 * @end_io_func:     end_io callback क्रम new bio
 * @mirror_num:	     desired mirror to पढ़ो/ग_लिखो
 * @prev_bio_flags:  flags of previous bio to see अगर we can merge the current one
 * @bio_flags:	flags of the current bio to see अगर we can merge them
 */
अटल पूर्णांक submit_extent_page(अचिन्हित पूर्णांक opf,
			      काष्ठा ग_लिखोback_control *wbc,
			      काष्ठा page *page, u64 disk_bytenr,
			      माप_प्रकार size, अचिन्हित दीर्घ pg_offset,
			      काष्ठा bio **bio_ret,
			      bio_end_io_t end_io_func,
			      पूर्णांक mirror_num,
			      अचिन्हित दीर्घ prev_bio_flags,
			      अचिन्हित दीर्घ bio_flags,
			      bool क्रमce_bio_submit)
अणु
	पूर्णांक ret = 0;
	काष्ठा bio *bio;
	माप_प्रकार io_size = min_t(माप_प्रकार, size, PAGE_SIZE);
	काष्ठा btrfs_inode *inode = BTRFS_I(page->mapping->host);
	काष्ठा extent_io_tree *tree = &inode->io_tree;
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;

	ASSERT(bio_ret);

	अगर (*bio_ret) अणु
		bio = *bio_ret;
		अगर (क्रमce_bio_submit ||
		    !btrfs_bio_add_page(bio, page, disk_bytenr, io_size,
					pg_offset, prev_bio_flags, bio_flags)) अणु
			ret = submit_one_bio(bio, mirror_num, prev_bio_flags);
			अगर (ret < 0) अणु
				*bio_ret = शून्य;
				वापस ret;
			पूर्ण
			bio = शून्य;
		पूर्ण अन्यथा अणु
			अगर (wbc)
				wbc_account_cgroup_owner(wbc, page, io_size);
			वापस 0;
		पूर्ण
	पूर्ण

	bio = btrfs_bio_alloc(disk_bytenr);
	bio_add_page(bio, page, io_size, pg_offset);
	bio->bi_end_io = end_io_func;
	bio->bi_निजी = tree;
	bio->bi_ग_लिखो_hपूर्णांक = page->mapping->host->i_ग_लिखो_hपूर्णांक;
	bio->bi_opf = opf;
	अगर (wbc) अणु
		काष्ठा block_device *bdev;

		bdev = fs_info->fs_devices->latest_bdev;
		bio_set_dev(bio, bdev);
		wbc_init_bio(wbc, bio);
		wbc_account_cgroup_owner(wbc, page, io_size);
	पूर्ण
	अगर (btrfs_is_zoned(fs_info) && bio_op(bio) == REQ_OP_ZONE_APPEND) अणु
		काष्ठा extent_map *em;
		काष्ठा map_lookup *map;

		em = btrfs_get_chunk_map(fs_info, disk_bytenr, io_size);
		अगर (IS_ERR(em))
			वापस PTR_ERR(em);

		map = em->map_lookup;
		/* We only support single profile क्रम now */
		ASSERT(map->num_stripes == 1);
		btrfs_io_bio(bio)->device = map->stripes[0].dev;

		मुक्त_extent_map(em);
	पूर्ण

	*bio_ret = bio;

	वापस ret;
पूर्ण

अटल पूर्णांक attach_extent_buffer_page(काष्ठा extent_buffer *eb,
				     काष्ठा page *page,
				     काष्ठा btrfs_subpage *pपुनः_स्मृति)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	पूर्णांक ret = 0;

	/*
	 * If the page is mapped to btree inode, we should hold the निजी
	 * lock to prevent race.
	 * For cloned or dummy extent buffers, their pages are not mapped and
	 * will not race with any other ebs.
	 */
	अगर (page->mapping)
		lockdep_निश्चित_held(&page->mapping->निजी_lock);

	अगर (fs_info->sectorsize == PAGE_SIZE) अणु
		अगर (!PagePrivate(page))
			attach_page_निजी(page, eb);
		अन्यथा
			WARN_ON(page->निजी != (अचिन्हित दीर्घ)eb);
		वापस 0;
	पूर्ण

	/* Alपढ़ोy mapped, just मुक्त pपुनः_स्मृति */
	अगर (PagePrivate(page)) अणु
		btrfs_मुक्त_subpage(pपुनः_स्मृति);
		वापस 0;
	पूर्ण

	अगर (pपुनः_स्मृति)
		/* Has pपुनः_स्मृतिated memory क्रम subpage */
		attach_page_निजी(page, pपुनः_स्मृति);
	अन्यथा
		/* Do new allocation to attach subpage */
		ret = btrfs_attach_subpage(fs_info, page,
					   BTRFS_SUBPAGE_METADATA);
	वापस ret;
पूर्ण

पूर्णांक set_page_extent_mapped(काष्ठा page *page)
अणु
	काष्ठा btrfs_fs_info *fs_info;

	ASSERT(page->mapping);

	अगर (PagePrivate(page))
		वापस 0;

	fs_info = btrfs_sb(page->mapping->host->i_sb);

	अगर (fs_info->sectorsize < PAGE_SIZE)
		वापस btrfs_attach_subpage(fs_info, page, BTRFS_SUBPAGE_DATA);

	attach_page_निजी(page, (व्योम *)EXTENT_PAGE_PRIVATE);
	वापस 0;
पूर्ण

व्योम clear_page_extent_mapped(काष्ठा page *page)
अणु
	काष्ठा btrfs_fs_info *fs_info;

	ASSERT(page->mapping);

	अगर (!PagePrivate(page))
		वापस;

	fs_info = btrfs_sb(page->mapping->host->i_sb);
	अगर (fs_info->sectorsize < PAGE_SIZE)
		वापस btrfs_detach_subpage(fs_info, page);

	detach_page_निजी(page);
पूर्ण

अटल काष्ठा extent_map *
__get_extent_map(काष्ठा inode *inode, काष्ठा page *page, माप_प्रकार pg_offset,
		 u64 start, u64 len, काष्ठा extent_map **em_cached)
अणु
	काष्ठा extent_map *em;

	अगर (em_cached && *em_cached) अणु
		em = *em_cached;
		अगर (extent_map_in_tree(em) && start >= em->start &&
		    start < extent_map_end(em)) अणु
			refcount_inc(&em->refs);
			वापस em;
		पूर्ण

		मुक्त_extent_map(em);
		*em_cached = शून्य;
	पूर्ण

	em = btrfs_get_extent(BTRFS_I(inode), page, pg_offset, start, len);
	अगर (em_cached && !IS_ERR_OR_शून्य(em)) अणु
		BUG_ON(*em_cached);
		refcount_inc(&em->refs);
		*em_cached = em;
	पूर्ण
	वापस em;
पूर्ण
/*
 * basic पढ़ोpage implementation.  Locked extent state काष्ठाs are inserted
 * पूर्णांकo the tree that are हटाओd when the IO is करोne (by the end_io
 * handlers)
 * XXX JDM: This needs looking at to ensure proper page locking
 * वापस 0 on success, otherwise वापस error
 */
पूर्णांक btrfs_करो_पढ़ोpage(काष्ठा page *page, काष्ठा extent_map **em_cached,
		      काष्ठा bio **bio, अचिन्हित दीर्घ *bio_flags,
		      अचिन्हित पूर्णांक पढ़ो_flags, u64 *prev_em_start)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	u64 start = page_offset(page);
	स्थिर u64 end = start + PAGE_SIZE - 1;
	u64 cur = start;
	u64 extent_offset;
	u64 last_byte = i_size_पढ़ो(inode);
	u64 block_start;
	u64 cur_end;
	काष्ठा extent_map *em;
	पूर्णांक ret = 0;
	पूर्णांक nr = 0;
	माप_प्रकार pg_offset = 0;
	माप_प्रकार iosize;
	माप_प्रकार blocksize = inode->i_sb->s_blocksize;
	अचिन्हित दीर्घ this_bio_flag = 0;
	काष्ठा extent_io_tree *tree = &BTRFS_I(inode)->io_tree;

	ret = set_page_extent_mapped(page);
	अगर (ret < 0) अणु
		unlock_extent(tree, start, end);
		btrfs_page_set_error(fs_info, page, start, PAGE_SIZE);
		unlock_page(page);
		जाओ out;
	पूर्ण

	अगर (!PageUptodate(page)) अणु
		अगर (cleancache_get_page(page) == 0) अणु
			BUG_ON(blocksize != PAGE_SIZE);
			unlock_extent(tree, start, end);
			unlock_page(page);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (page->index == last_byte >> PAGE_SHIFT) अणु
		माप_प्रकार zero_offset = offset_in_page(last_byte);

		अगर (zero_offset) अणु
			iosize = PAGE_SIZE - zero_offset;
			memzero_page(page, zero_offset, iosize);
			flush_dcache_page(page);
		पूर्ण
	पूर्ण
	begin_page_पढ़ो(fs_info, page);
	जबतक (cur <= end) अणु
		bool क्रमce_bio_submit = false;
		u64 disk_bytenr;

		अगर (cur >= last_byte) अणु
			काष्ठा extent_state *cached = शून्य;

			iosize = PAGE_SIZE - pg_offset;
			memzero_page(page, pg_offset, iosize);
			flush_dcache_page(page);
			set_extent_uptodate(tree, cur, cur + iosize - 1,
					    &cached, GFP_NOFS);
			unlock_extent_cached(tree, cur,
					     cur + iosize - 1, &cached);
			end_page_पढ़ो(page, true, cur, iosize);
			अवरोध;
		पूर्ण
		em = __get_extent_map(inode, page, pg_offset, cur,
				      end - cur + 1, em_cached);
		अगर (IS_ERR_OR_शून्य(em)) अणु
			unlock_extent(tree, cur, end);
			end_page_पढ़ो(page, false, cur, end + 1 - cur);
			अवरोध;
		पूर्ण
		extent_offset = cur - em->start;
		BUG_ON(extent_map_end(em) <= cur);
		BUG_ON(end < cur);

		अगर (test_bit(EXTENT_FLAG_COMPRESSED, &em->flags)) अणु
			this_bio_flag |= EXTENT_BIO_COMPRESSED;
			extent_set_compress_type(&this_bio_flag,
						 em->compress_type);
		पूर्ण

		iosize = min(extent_map_end(em) - cur, end - cur + 1);
		cur_end = min(extent_map_end(em) - 1, end);
		iosize = ALIGN(iosize, blocksize);
		अगर (this_bio_flag & EXTENT_BIO_COMPRESSED)
			disk_bytenr = em->block_start;
		अन्यथा
			disk_bytenr = em->block_start + extent_offset;
		block_start = em->block_start;
		अगर (test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
			block_start = EXTENT_MAP_HOLE;

		/*
		 * If we have a file range that poपूर्णांकs to a compressed extent
		 * and it's followed by a consecutive file range that poपूर्णांकs
		 * to the same compressed extent (possibly with a dअगरferent
		 * offset and/or length, so it either poपूर्णांकs to the whole extent
		 * or only part of it), we must make sure we करो not submit a
		 * single bio to populate the pages क्रम the 2 ranges because
		 * this makes the compressed extent पढ़ो zero out the pages
		 * beदीर्घing to the 2nd range. Imagine the following scenario:
		 *
		 *  File layout
		 *  [0 - 8K]                     [8K - 24K]
		 *    |                               |
		 *    |                               |
		 * poपूर्णांकs to extent X,         poपूर्णांकs to extent X,
		 * offset 4K, length of 8K     offset 0, length 16K
		 *
		 * [extent X, compressed length = 4K uncompressed length = 16K]
		 *
		 * If the bio to पढ़ो the compressed extent covers both ranges,
		 * it will decompress extent X पूर्णांकo the pages beदीर्घing to the
		 * first range and then it will stop, zeroing out the reमुख्यing
		 * pages that beदीर्घ to the other range that poपूर्णांकs to extent X.
		 * So here we make sure we submit 2 bios, one क्रम the first
		 * range and another one क्रम the third range. Both will target
		 * the same physical extent from disk, but we can't currently
		 * make the compressed bio endio callback populate the pages
		 * क्रम both ranges because each compressed bio is tightly
		 * coupled with a single extent map, and each range can have
		 * an extent map with a dअगरferent offset value relative to the
		 * uncompressed data of our extent and dअगरferent lengths. This
		 * is a corner हाल so we prioritize correctness over
		 * non-optimal behavior (submitting 2 bios क्रम the same extent).
		 */
		अगर (test_bit(EXTENT_FLAG_COMPRESSED, &em->flags) &&
		    prev_em_start && *prev_em_start != (u64)-1 &&
		    *prev_em_start != em->start)
			क्रमce_bio_submit = true;

		अगर (prev_em_start)
			*prev_em_start = em->start;

		मुक्त_extent_map(em);
		em = शून्य;

		/* we've found a hole, just zero and go on */
		अगर (block_start == EXTENT_MAP_HOLE) अणु
			काष्ठा extent_state *cached = शून्य;

			memzero_page(page, pg_offset, iosize);
			flush_dcache_page(page);

			set_extent_uptodate(tree, cur, cur + iosize - 1,
					    &cached, GFP_NOFS);
			unlock_extent_cached(tree, cur,
					     cur + iosize - 1, &cached);
			end_page_पढ़ो(page, true, cur, iosize);
			cur = cur + iosize;
			pg_offset += iosize;
			जारी;
		पूर्ण
		/* the get_extent function alपढ़ोy copied पूर्णांकo the page */
		अगर (test_range_bit(tree, cur, cur_end,
				   EXTENT_UPTODATE, 1, शून्य)) अणु
			check_page_uptodate(tree, page);
			unlock_extent(tree, cur, cur + iosize - 1);
			end_page_पढ़ो(page, true, cur, iosize);
			cur = cur + iosize;
			pg_offset += iosize;
			जारी;
		पूर्ण
		/* we have an अंतरभूत extent but it didn't get marked up
		 * to date.  Error out
		 */
		अगर (block_start == EXTENT_MAP_INLINE) अणु
			unlock_extent(tree, cur, cur + iosize - 1);
			end_page_पढ़ो(page, false, cur, iosize);
			cur = cur + iosize;
			pg_offset += iosize;
			जारी;
		पूर्ण

		ret = submit_extent_page(REQ_OP_READ | पढ़ो_flags, शून्य,
					 page, disk_bytenr, iosize,
					 pg_offset, bio,
					 end_bio_extent_पढ़ोpage, 0,
					 *bio_flags,
					 this_bio_flag,
					 क्रमce_bio_submit);
		अगर (!ret) अणु
			nr++;
			*bio_flags = this_bio_flag;
		पूर्ण अन्यथा अणु
			unlock_extent(tree, cur, cur + iosize - 1);
			end_page_पढ़ो(page, false, cur, iosize);
			जाओ out;
		पूर्ण
		cur = cur + iosize;
		pg_offset += iosize;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम contiguous_पढ़ोpages(काष्ठा page *pages[], पूर्णांक nr_pages,
					     u64 start, u64 end,
					     काष्ठा extent_map **em_cached,
					     काष्ठा bio **bio,
					     अचिन्हित दीर्घ *bio_flags,
					     u64 *prev_em_start)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(pages[0]->mapping->host);
	पूर्णांक index;

	btrfs_lock_and_flush_ordered_range(inode, start, end, शून्य);

	क्रम (index = 0; index < nr_pages; index++) अणु
		btrfs_करो_पढ़ोpage(pages[index], em_cached, bio, bio_flags,
				  REQ_RAHEAD, prev_em_start);
		put_page(pages[index]);
	पूर्ण
पूर्ण

अटल व्योम update_nr_written(काष्ठा ग_लिखोback_control *wbc,
			      अचिन्हित दीर्घ nr_written)
अणु
	wbc->nr_to_ग_लिखो -= nr_written;
पूर्ण

/*
 * helper क्रम __extent_ग_लिखोpage, करोing all of the delayed allocation setup.
 *
 * This वापसs 1 अगर btrfs_run_delalloc_range function did all the work required
 * to ग_लिखो the page (copy पूर्णांकo अंतरभूत extent).  In this हाल the IO has
 * been started and the page is alपढ़ोy unlocked.
 *
 * This वापसs 0 अगर all went well (page still locked)
 * This वापसs < 0 अगर there were errors (page still locked)
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक ग_लिखोpage_delalloc(काष्ठा btrfs_inode *inode,
		काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
		u64 delalloc_start, अचिन्हित दीर्घ *nr_written)
अणु
	u64 page_end = delalloc_start + PAGE_SIZE - 1;
	bool found;
	u64 delalloc_to_ग_लिखो = 0;
	u64 delalloc_end = 0;
	पूर्णांक ret;
	पूर्णांक page_started = 0;


	जबतक (delalloc_end < page_end) अणु
		found = find_lock_delalloc_range(&inode->vfs_inode, page,
					       &delalloc_start,
					       &delalloc_end);
		अगर (!found) अणु
			delalloc_start = delalloc_end + 1;
			जारी;
		पूर्ण
		ret = btrfs_run_delalloc_range(inode, page, delalloc_start,
				delalloc_end, &page_started, nr_written, wbc);
		अगर (ret) अणु
			SetPageError(page);
			/*
			 * btrfs_run_delalloc_range should वापस < 0 क्रम error
			 * but just in हाल, we use > 0 here meaning the IO is
			 * started, so we करोn't want to वापस > 0 unless
			 * things are going well.
			 */
			वापस ret < 0 ? ret : -EIO;
		पूर्ण
		/*
		 * delalloc_end is alपढ़ोy one less than the total length, so
		 * we करोn't subtract one from PAGE_SIZE
		 */
		delalloc_to_ग_लिखो += (delalloc_end - delalloc_start +
				      PAGE_SIZE) >> PAGE_SHIFT;
		delalloc_start = delalloc_end + 1;
	पूर्ण
	अगर (wbc->nr_to_ग_लिखो < delalloc_to_ग_लिखो) अणु
		पूर्णांक thresh = 8192;

		अगर (delalloc_to_ग_लिखो < thresh * 2)
			thresh = delalloc_to_ग_लिखो;
		wbc->nr_to_ग_लिखो = min_t(u64, delalloc_to_ग_लिखो,
					 thresh);
	पूर्ण

	/* did the fill delalloc function alपढ़ोy unlock and start
	 * the IO?
	 */
	अगर (page_started) अणु
		/*
		 * we've unlocked the page, so we can't update
		 * the mapping's ग_लिखोback index, just update
		 * nr_to_ग_लिखो.
		 */
		wbc->nr_to_ग_लिखो -= *nr_written;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * helper क्रम __extent_ग_लिखोpage.  This calls the ग_लिखोpage start hooks,
 * and करोes the loop to map the page पूर्णांकo extents and bios.
 *
 * We वापस 1 अगर the IO is started and the page is unlocked,
 * 0 अगर all went well (page still locked)
 * < 0 अगर there were errors (page still locked)
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक __extent_ग_लिखोpage_io(काष्ठा btrfs_inode *inode,
				 काष्ठा page *page,
				 काष्ठा ग_लिखोback_control *wbc,
				 काष्ठा extent_page_data *epd,
				 loff_t i_size,
				 अचिन्हित दीर्घ nr_written,
				 पूर्णांक *nr_ret)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा extent_io_tree *tree = &inode->io_tree;
	u64 start = page_offset(page);
	u64 end = start + PAGE_SIZE - 1;
	u64 cur = start;
	u64 extent_offset;
	u64 block_start;
	काष्ठा extent_map *em;
	पूर्णांक ret = 0;
	पूर्णांक nr = 0;
	u32 opf = REQ_OP_WRITE;
	स्थिर अचिन्हित पूर्णांक ग_लिखो_flags = wbc_to_ग_लिखो_flags(wbc);
	bool compressed;

	ret = btrfs_ग_लिखोpage_cow_fixup(page, start, end);
	अगर (ret) अणु
		/* Fixup worker will requeue */
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		update_nr_written(wbc, nr_written);
		unlock_page(page);
		वापस 1;
	पूर्ण

	/*
	 * we करोn't want to touch the inode after unlocking the page,
	 * so we update the mapping ग_लिखोback index now
	 */
	update_nr_written(wbc, nr_written + 1);

	जबतक (cur <= end) अणु
		u64 disk_bytenr;
		u64 em_end;
		u32 iosize;

		अगर (cur >= i_size) अणु
			btrfs_ग_लिखोpage_endio_finish_ordered(page, cur, end, 1);
			अवरोध;
		पूर्ण
		em = btrfs_get_extent(inode, शून्य, 0, cur, end - cur + 1);
		अगर (IS_ERR_OR_शून्य(em)) अणु
			SetPageError(page);
			ret = PTR_ERR_OR_ZERO(em);
			अवरोध;
		पूर्ण

		extent_offset = cur - em->start;
		em_end = extent_map_end(em);
		ASSERT(cur <= em_end);
		ASSERT(cur < end);
		ASSERT(IS_ALIGNED(em->start, fs_info->sectorsize));
		ASSERT(IS_ALIGNED(em->len, fs_info->sectorsize));
		block_start = em->block_start;
		compressed = test_bit(EXTENT_FLAG_COMPRESSED, &em->flags);
		disk_bytenr = em->block_start + extent_offset;

		/* Note that em_end from extent_map_end() is exclusive */
		iosize = min(em_end, end + 1) - cur;

		अगर (btrfs_use_zone_append(inode, em->block_start))
			opf = REQ_OP_ZONE_APPEND;

		मुक्त_extent_map(em);
		em = शून्य;

		/*
		 * compressed and अंतरभूत extents are written through other
		 * paths in the FS
		 */
		अगर (compressed || block_start == EXTENT_MAP_HOLE ||
		    block_start == EXTENT_MAP_INLINE) अणु
			अगर (compressed)
				nr++;
			अन्यथा
				btrfs_ग_लिखोpage_endio_finish_ordered(page, cur,
							cur + iosize - 1, 1);
			cur += iosize;
			जारी;
		पूर्ण

		btrfs_set_range_ग_लिखोback(tree, cur, cur + iosize - 1);
		अगर (!PageWriteback(page)) अणु
			btrfs_err(inode->root->fs_info,
				   "page %lu not writeback, cur %llu end %llu",
			       page->index, cur, end);
		पूर्ण

		ret = submit_extent_page(opf | ग_लिखो_flags, wbc, page,
					 disk_bytenr, iosize,
					 cur - page_offset(page), &epd->bio,
					 end_bio_extent_ग_लिखोpage,
					 0, 0, 0, false);
		अगर (ret) अणु
			SetPageError(page);
			अगर (PageWriteback(page))
				end_page_ग_लिखोback(page);
		पूर्ण

		cur += iosize;
		nr++;
	पूर्ण
	*nr_ret = nr;
	वापस ret;
पूर्ण

/*
 * the ग_लिखोpage semantics are similar to regular ग_लिखोpage.  extent
 * records are inserted to lock ranges in the tree, and as dirty areas
 * are found, they are marked ग_लिखोback.  Then the lock bits are हटाओd
 * and the end_io handler clears the ग_लिखोback ranges
 *
 * Return 0 अगर everything goes well.
 * Return <0 क्रम error.
 */
अटल पूर्णांक __extent_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
			      काष्ठा extent_page_data *epd)
अणु
	काष्ठा inode *inode = page->mapping->host;
	u64 start = page_offset(page);
	u64 page_end = start + PAGE_SIZE - 1;
	पूर्णांक ret;
	पूर्णांक nr = 0;
	माप_प्रकार pg_offset;
	loff_t i_size = i_size_पढ़ो(inode);
	अचिन्हित दीर्घ end_index = i_size >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_written = 0;

	trace___extent_ग_लिखोpage(page, inode, wbc);

	WARN_ON(!PageLocked(page));

	ClearPageError(page);

	pg_offset = offset_in_page(i_size);
	अगर (page->index > end_index ||
	   (page->index == end_index && !pg_offset)) अणु
		page->mapping->a_ops->invalidatepage(page, 0, PAGE_SIZE);
		unlock_page(page);
		वापस 0;
	पूर्ण

	अगर (page->index == end_index) अणु
		memzero_page(page, pg_offset, PAGE_SIZE - pg_offset);
		flush_dcache_page(page);
	पूर्ण

	ret = set_page_extent_mapped(page);
	अगर (ret < 0) अणु
		SetPageError(page);
		जाओ करोne;
	पूर्ण

	अगर (!epd->extent_locked) अणु
		ret = ग_लिखोpage_delalloc(BTRFS_I(inode), page, wbc, start,
					 &nr_written);
		अगर (ret == 1)
			वापस 0;
		अगर (ret)
			जाओ करोne;
	पूर्ण

	ret = __extent_ग_लिखोpage_io(BTRFS_I(inode), page, wbc, epd, i_size,
				    nr_written, &nr);
	अगर (ret == 1)
		वापस 0;

करोne:
	अगर (nr == 0) अणु
		/* make sure the mapping tag क्रम page dirty माला_लो cleared */
		set_page_ग_लिखोback(page);
		end_page_ग_लिखोback(page);
	पूर्ण
	अगर (PageError(page)) अणु
		ret = ret < 0 ? ret : -EIO;
		end_extent_ग_लिखोpage(page, ret, start, page_end);
	पूर्ण
	unlock_page(page);
	ASSERT(ret <= 0);
	वापस ret;
पूर्ण

व्योम रुको_on_extent_buffer_ग_लिखोback(काष्ठा extent_buffer *eb)
अणु
	रुको_on_bit_io(&eb->bflags, EXTENT_BUFFER_WRITEBACK,
		       TASK_UNINTERRUPTIBLE);
पूर्ण

अटल व्योम end_extent_buffer_ग_लिखोback(काष्ठा extent_buffer *eb)
अणु
	clear_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags);
	smp_mb__after_atomic();
	wake_up_bit(&eb->bflags, EXTENT_BUFFER_WRITEBACK);
पूर्ण

/*
 * Lock extent buffer status and pages क्रम ग_लिखोback.
 *
 * May try to flush ग_लिखो bio अगर we can't get the lock.
 *
 * Return  0 अगर the extent buffer करोesn't need to be submitted.
 *           (E.g. the extent buffer is not dirty)
 * Return >0 is the extent buffer is submitted to bio.
 * Return <0 अगर something went wrong, no page is locked.
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक lock_extent_buffer_क्रम_io(काष्ठा extent_buffer *eb,
			  काष्ठा extent_page_data *epd)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	पूर्णांक i, num_pages, failed_page_nr;
	पूर्णांक flush = 0;
	पूर्णांक ret = 0;

	अगर (!btrfs_try_tree_ग_लिखो_lock(eb)) अणु
		ret = flush_ग_लिखो_bio(epd);
		अगर (ret < 0)
			वापस ret;
		flush = 1;
		btrfs_tree_lock(eb);
	पूर्ण

	अगर (test_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags)) अणु
		btrfs_tree_unlock(eb);
		अगर (!epd->sync_io)
			वापस 0;
		अगर (!flush) अणु
			ret = flush_ग_लिखो_bio(epd);
			अगर (ret < 0)
				वापस ret;
			flush = 1;
		पूर्ण
		जबतक (1) अणु
			रुको_on_extent_buffer_ग_लिखोback(eb);
			btrfs_tree_lock(eb);
			अगर (!test_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags))
				अवरोध;
			btrfs_tree_unlock(eb);
		पूर्ण
	पूर्ण

	/*
	 * We need to करो this to prevent races in people who check अगर the eb is
	 * under IO since we can end up having no IO bits set क्रम a लघु period
	 * of समय.
	 */
	spin_lock(&eb->refs_lock);
	अगर (test_and_clear_bit(EXTENT_BUFFER_सूचीTY, &eb->bflags)) अणु
		set_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags);
		spin_unlock(&eb->refs_lock);
		btrfs_set_header_flag(eb, BTRFS_HEADER_FLAG_WRITTEN);
		percpu_counter_add_batch(&fs_info->dirty_metadata_bytes,
					 -eb->len,
					 fs_info->dirty_metadata_batch);
		ret = 1;
	पूर्ण अन्यथा अणु
		spin_unlock(&eb->refs_lock);
	पूर्ण

	btrfs_tree_unlock(eb);

	/*
	 * Either we करोn't need to submit any tree block, or we're submitting
	 * subpage eb.
	 * Subpage metadata करोesn't use page locking at all, so we can skip
	 * the page locking.
	 */
	अगर (!ret || fs_info->sectorsize < PAGE_SIZE)
		वापस ret;

	num_pages = num_extent_pages(eb);
	क्रम (i = 0; i < num_pages; i++) अणु
		काष्ठा page *p = eb->pages[i];

		अगर (!trylock_page(p)) अणु
			अगर (!flush) अणु
				पूर्णांक err;

				err = flush_ग_लिखो_bio(epd);
				अगर (err < 0) अणु
					ret = err;
					failed_page_nr = i;
					जाओ err_unlock;
				पूर्ण
				flush = 1;
			पूर्ण
			lock_page(p);
		पूर्ण
	पूर्ण

	वापस ret;
err_unlock:
	/* Unlock alपढ़ोy locked pages */
	क्रम (i = 0; i < failed_page_nr; i++)
		unlock_page(eb->pages[i]);
	/*
	 * Clear EXTENT_BUFFER_WRITEBACK and wake up anyone रुकोing on it.
	 * Also set back EXTENT_BUFFER_सूचीTY so future attempts to this eb can
	 * be made and unकरो everything करोne beक्रमe.
	 */
	btrfs_tree_lock(eb);
	spin_lock(&eb->refs_lock);
	set_bit(EXTENT_BUFFER_सूचीTY, &eb->bflags);
	end_extent_buffer_ग_लिखोback(eb);
	spin_unlock(&eb->refs_lock);
	percpu_counter_add_batch(&fs_info->dirty_metadata_bytes, eb->len,
				 fs_info->dirty_metadata_batch);
	btrfs_clear_header_flag(eb, BTRFS_HEADER_FLAG_WRITTEN);
	btrfs_tree_unlock(eb);
	वापस ret;
पूर्ण

अटल व्योम set_btree_ioerr(काष्ठा page *page, काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;

	btrfs_page_set_error(fs_info, page, eb->start, eb->len);
	अगर (test_and_set_bit(EXTENT_BUFFER_WRITE_ERR, &eb->bflags))
		वापस;

	/*
	 * If we error out, we should add back the dirty_metadata_bytes
	 * to make it consistent.
	 */
	percpu_counter_add_batch(&fs_info->dirty_metadata_bytes,
				 eb->len, fs_info->dirty_metadata_batch);

	/*
	 * If ग_लिखोback क्रम a btree extent that करोesn't beदीर्घ to a log tree
	 * failed, increment the counter transaction->eb_ग_लिखो_errors.
	 * We करो this because जबतक the transaction is running and beक्रमe it's
	 * committing (when we call filemap_fdata[ग_लिखो|रुको]_range against
	 * the btree inode), we might have
	 * btree_inode->i_mapping->a_ops->ग_लिखोpages() called by the VM - अगर it
	 * वापसs an error or an error happens during ग_लिखोback, when we're
	 * committing the transaction we wouldn't know about it, since the pages
	 * can be no दीर्घer dirty nor marked anymore क्रम ग_लिखोback (अगर a
	 * subsequent modअगरication to the extent buffer didn't happen beक्रमe the
	 * transaction commit), which makes filemap_fdata[ग_लिखो|रुको]_range not
	 * able to find the pages tagged with SetPageError at transaction
	 * commit समय. So अगर this happens we must पात the transaction,
	 * otherwise we commit a super block with btree roots that poपूर्णांक to
	 * btree nodes/leafs whose content on disk is invalid - either garbage
	 * or the content of some node/leaf from a past generation that got
	 * cowed or deleted and is no दीर्घer valid.
	 *
	 * Note: setting AS_EIO/AS_ENOSPC in the btree inode's i_mapping would
	 * not be enough - we need to distinguish between log tree extents vs
	 * non-log tree extents, and the next filemap_fdataरुको_range() call
	 * will catch and clear such errors in the mapping - and that call might
	 * be from a log sync and not from a transaction commit. Also, checking
	 * क्रम the eb flag EXTENT_BUFFER_WRITE_ERR at transaction commit समय is
	 * not करोne and would not be reliable - the eb might have been released
	 * from memory and पढ़ोing it back again means that flag would not be
	 * set (since it's a runसमय flag, not persisted on disk).
	 *
	 * Using the flags below in the btree inode also makes us achieve the
	 * goal of AS_EIO/AS_ENOSPC when ग_लिखोpages() वापसs success, started
	 * ग_लिखोback क्रम all dirty pages and beक्रमe filemap_fdataरुको_range()
	 * is called, the ग_लिखोback क्रम all dirty pages had alपढ़ोy finished
	 * with errors - because we were not using AS_EIO/AS_ENOSPC,
	 * filemap_fdataरुको_range() would वापस success, as it could not know
	 * that ग_लिखोback errors happened (the pages were no दीर्घer tagged क्रम
	 * ग_लिखोback).
	 */
	चयन (eb->log_index) अणु
	हाल -1:
		set_bit(BTRFS_FS_BTREE_ERR, &fs_info->flags);
		अवरोध;
	हाल 0:
		set_bit(BTRFS_FS_LOG1_ERR, &fs_info->flags);
		अवरोध;
	हाल 1:
		set_bit(BTRFS_FS_LOG2_ERR, &fs_info->flags);
		अवरोध;
	शेष:
		BUG(); /* unexpected, logic error */
	पूर्ण
पूर्ण

/*
 * The endio specअगरic version which won't touch any unsafe spinlock in endio
 * context.
 */
अटल काष्ठा extent_buffer *find_extent_buffer_nolock(
		काष्ठा btrfs_fs_info *fs_info, u64 start)
अणु
	काष्ठा extent_buffer *eb;

	rcu_पढ़ो_lock();
	eb = radix_tree_lookup(&fs_info->buffer_radix,
			       start >> fs_info->sectorsize_bits);
	अगर (eb && atomic_inc_not_zero(&eb->refs)) अणु
		rcu_पढ़ो_unlock();
		वापस eb;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

/*
 * The endio function क्रम subpage extent buffer ग_लिखो.
 *
 * Unlike end_bio_extent_buffer_ग_लिखोpage(), we only call end_page_ग_लिखोback()
 * after all extent buffers in the page has finished their ग_लिखोback.
 */
अटल व्योम end_bio_subpage_eb_ग_लिखोpage(काष्ठा btrfs_fs_info *fs_info,
					 काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	ASSERT(!bio_flagged(bio, BIO_CLONED));
	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;
		u64 bvec_start = page_offset(page) + bvec->bv_offset;
		u64 bvec_end = bvec_start + bvec->bv_len - 1;
		u64 cur_bytenr = bvec_start;

		ASSERT(IS_ALIGNED(bvec->bv_len, fs_info->nodesize));

		/* Iterate through all extent buffers in the range */
		जबतक (cur_bytenr <= bvec_end) अणु
			काष्ठा extent_buffer *eb;
			पूर्णांक करोne;

			/*
			 * Here we can't use find_extent_buffer(), as it may
			 * try to lock eb->refs_lock, which is not safe in endio
			 * context.
			 */
			eb = find_extent_buffer_nolock(fs_info, cur_bytenr);
			ASSERT(eb);

			cur_bytenr = eb->start + eb->len;

			ASSERT(test_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags));
			करोne = atomic_dec_and_test(&eb->io_pages);
			ASSERT(करोne);

			अगर (bio->bi_status ||
			    test_bit(EXTENT_BUFFER_WRITE_ERR, &eb->bflags)) अणु
				ClearPageUptodate(page);
				set_btree_ioerr(page, eb);
			पूर्ण

			btrfs_subpage_clear_ग_लिखोback(fs_info, page, eb->start,
						      eb->len);
			end_extent_buffer_ग_लिखोback(eb);
			/*
			 * मुक्त_extent_buffer() will grab spinlock which is not
			 * safe in endio context. Thus here we manually dec
			 * the ref.
			 */
			atomic_dec(&eb->refs);
		पूर्ण
	पूर्ण
	bio_put(bio);
पूर्ण

अटल व्योम end_bio_extent_buffer_ग_लिखोpage(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा bio_vec *bvec;
	काष्ठा extent_buffer *eb;
	पूर्णांक करोne;
	काष्ठा bvec_iter_all iter_all;

	fs_info = btrfs_sb(bio_first_page_all(bio)->mapping->host->i_sb);
	अगर (fs_info->sectorsize < PAGE_SIZE)
		वापस end_bio_subpage_eb_ग_लिखोpage(fs_info, bio);

	ASSERT(!bio_flagged(bio, BIO_CLONED));
	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;

		eb = (काष्ठा extent_buffer *)page->निजी;
		BUG_ON(!eb);
		करोne = atomic_dec_and_test(&eb->io_pages);

		अगर (bio->bi_status ||
		    test_bit(EXTENT_BUFFER_WRITE_ERR, &eb->bflags)) अणु
			ClearPageUptodate(page);
			set_btree_ioerr(page, eb);
		पूर्ण

		end_page_ग_लिखोback(page);

		अगर (!करोne)
			जारी;

		end_extent_buffer_ग_लिखोback(eb);
	पूर्ण

	bio_put(bio);
पूर्ण

/*
 * Unlike the work in ग_लिखो_one_eb(), we rely completely on extent locking.
 * Page locking is only utilized at minimum to keep the VMM code happy.
 *
 * Caller should still call ग_लिखो_one_eb() other than this function directly.
 * As ग_लिखो_one_eb() has extra preparation beक्रमe submitting the extent buffer.
 */
अटल पूर्णांक ग_लिखो_one_subpage_eb(काष्ठा extent_buffer *eb,
				काष्ठा ग_लिखोback_control *wbc,
				काष्ठा extent_page_data *epd)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा page *page = eb->pages[0];
	अचिन्हित पूर्णांक ग_लिखो_flags = wbc_to_ग_लिखो_flags(wbc) | REQ_META;
	bool no_dirty_ebs = false;
	पूर्णांक ret;

	/* clear_page_dirty_क्रम_io() in subpage helper needs page locked */
	lock_page(page);
	btrfs_subpage_set_ग_लिखोback(fs_info, page, eb->start, eb->len);

	/* Check अगर this is the last dirty bit to update nr_written */
	no_dirty_ebs = btrfs_subpage_clear_and_test_dirty(fs_info, page,
							  eb->start, eb->len);
	अगर (no_dirty_ebs)
		clear_page_dirty_क्रम_io(page);

	ret = submit_extent_page(REQ_OP_WRITE | ग_लिखो_flags, wbc, page,
			eb->start, eb->len, eb->start - page_offset(page),
			&epd->bio, end_bio_extent_buffer_ग_लिखोpage, 0, 0, 0,
			false);
	अगर (ret) अणु
		btrfs_subpage_clear_ग_लिखोback(fs_info, page, eb->start, eb->len);
		set_btree_ioerr(page, eb);
		unlock_page(page);

		अगर (atomic_dec_and_test(&eb->io_pages))
			end_extent_buffer_ग_लिखोback(eb);
		वापस -EIO;
	पूर्ण
	unlock_page(page);
	/*
	 * Submission finished without problem, अगर no range of the page is
	 * dirty anymore, we have submitted a page.  Update nr_written in wbc.
	 */
	अगर (no_dirty_ebs)
		update_nr_written(wbc, 1);
	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक ग_लिखो_one_eb(काष्ठा extent_buffer *eb,
			काष्ठा ग_लिखोback_control *wbc,
			काष्ठा extent_page_data *epd)
अणु
	u64 disk_bytenr = eb->start;
	u32 nritems;
	पूर्णांक i, num_pages;
	अचिन्हित दीर्घ start, end;
	अचिन्हित पूर्णांक ग_लिखो_flags = wbc_to_ग_लिखो_flags(wbc) | REQ_META;
	पूर्णांक ret = 0;

	clear_bit(EXTENT_BUFFER_WRITE_ERR, &eb->bflags);
	num_pages = num_extent_pages(eb);
	atomic_set(&eb->io_pages, num_pages);

	/* set btree blocks beyond nritems with 0 to aव्योम stale content. */
	nritems = btrfs_header_nritems(eb);
	अगर (btrfs_header_level(eb) > 0) अणु
		end = btrfs_node_key_ptr_offset(nritems);

		memzero_extent_buffer(eb, end, eb->len - end);
	पूर्ण अन्यथा अणु
		/*
		 * leaf:
		 * header 0 1 2 .. N ... data_N .. data_2 data_1 data_0
		 */
		start = btrfs_item_nr_offset(nritems);
		end = BTRFS_LEAF_DATA_OFFSET + leaf_data_end(eb);
		memzero_extent_buffer(eb, start, end - start);
	पूर्ण

	अगर (eb->fs_info->sectorsize < PAGE_SIZE)
		वापस ग_लिखो_one_subpage_eb(eb, wbc, epd);

	क्रम (i = 0; i < num_pages; i++) अणु
		काष्ठा page *p = eb->pages[i];

		clear_page_dirty_क्रम_io(p);
		set_page_ग_लिखोback(p);
		ret = submit_extent_page(REQ_OP_WRITE | ग_लिखो_flags, wbc,
					 p, disk_bytenr, PAGE_SIZE, 0,
					 &epd->bio,
					 end_bio_extent_buffer_ग_लिखोpage,
					 0, 0, 0, false);
		अगर (ret) अणु
			set_btree_ioerr(p, eb);
			अगर (PageWriteback(p))
				end_page_ग_लिखोback(p);
			अगर (atomic_sub_and_test(num_pages - i, &eb->io_pages))
				end_extent_buffer_ग_लिखोback(eb);
			ret = -EIO;
			अवरोध;
		पूर्ण
		disk_bytenr += PAGE_SIZE;
		update_nr_written(wbc, 1);
		unlock_page(p);
	पूर्ण

	अगर (unlikely(ret)) अणु
		क्रम (; i < num_pages; i++) अणु
			काष्ठा page *p = eb->pages[i];
			clear_page_dirty_क्रम_io(p);
			unlock_page(p);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Submit one subpage btree page.
 *
 * The मुख्य dअगरference to submit_eb_page() is:
 * - Page locking
 *   For subpage, we करोn't rely on page locking at all.
 *
 * - Flush ग_लिखो bio
 *   We only flush bio अगर we may be unable to fit current extent buffers पूर्णांकo
 *   current bio.
 *
 * Return >=0 क्रम the number of submitted extent buffers.
 * Return <0 क्रम fatal error.
 */
अटल पूर्णांक submit_eb_subpage(काष्ठा page *page,
			     काष्ठा ग_लिखोback_control *wbc,
			     काष्ठा extent_page_data *epd)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(page->mapping->host->i_sb);
	पूर्णांक submitted = 0;
	u64 page_start = page_offset(page);
	पूर्णांक bit_start = 0;
	स्थिर पूर्णांक nbits = BTRFS_SUBPAGE_BITMAP_SIZE;
	पूर्णांक sectors_per_node = fs_info->nodesize >> fs_info->sectorsize_bits;
	पूर्णांक ret;

	/* Lock and ग_लिखो each dirty extent buffers in the range */
	जबतक (bit_start < nbits) अणु
		काष्ठा btrfs_subpage *subpage = (काष्ठा btrfs_subpage *)page->निजी;
		काष्ठा extent_buffer *eb;
		अचिन्हित दीर्घ flags;
		u64 start;

		/*
		 * Take निजी lock to ensure the subpage won't be detached
		 * in the meanसमय.
		 */
		spin_lock(&page->mapping->निजी_lock);
		अगर (!PagePrivate(page)) अणु
			spin_unlock(&page->mapping->निजी_lock);
			अवरोध;
		पूर्ण
		spin_lock_irqsave(&subpage->lock, flags);
		अगर (!((1 << bit_start) & subpage->dirty_biपंचांगap)) अणु
			spin_unlock_irqrestore(&subpage->lock, flags);
			spin_unlock(&page->mapping->निजी_lock);
			bit_start++;
			जारी;
		पूर्ण

		start = page_start + bit_start * fs_info->sectorsize;
		bit_start += sectors_per_node;

		/*
		 * Here we just want to grab the eb without touching extra
		 * spin locks, so call find_extent_buffer_nolock().
		 */
		eb = find_extent_buffer_nolock(fs_info, start);
		spin_unlock_irqrestore(&subpage->lock, flags);
		spin_unlock(&page->mapping->निजी_lock);

		/*
		 * The eb has alपढ़ोy reached 0 refs thus find_extent_buffer()
		 * करोesn't return it. We don't need to ग_लिखो back such eb
		 * anyway.
		 */
		अगर (!eb)
			जारी;

		ret = lock_extent_buffer_क्रम_io(eb, epd);
		अगर (ret == 0) अणु
			मुक्त_extent_buffer(eb);
			जारी;
		पूर्ण
		अगर (ret < 0) अणु
			मुक्त_extent_buffer(eb);
			जाओ cleanup;
		पूर्ण
		ret = ग_लिखो_one_eb(eb, wbc, epd);
		मुक्त_extent_buffer(eb);
		अगर (ret < 0)
			जाओ cleanup;
		submitted++;
	पूर्ण
	वापस submitted;

cleanup:
	/* We hit error, end bio क्रम the submitted extent buffers */
	end_ग_लिखो_bio(epd, ret);
	वापस ret;
पूर्ण

/*
 * Submit all page(s) of one extent buffer.
 *
 * @page:	the page of one extent buffer
 * @eb_context:	to determine अगर we need to submit this page, अगर current page
 *		beदीर्घs to this eb, we करोn't need to submit
 *
 * The caller should pass each page in their bytenr order, and here we use
 * @eb_context to determine अगर we have submitted pages of one extent buffer.
 *
 * If we have, we just skip until we hit a new page that करोesn't beदीर्घ to
 * current @eb_context.
 *
 * If not, we submit all the page(s) of the extent buffer.
 *
 * Return >0 अगर we have submitted the extent buffer successfully.
 * Return 0 अगर we करोn't need to submit the page, as it's alपढ़ोy submitted by
 * previous call.
 * Return <0 क्रम fatal error.
 */
अटल पूर्णांक submit_eb_page(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
			  काष्ठा extent_page_data *epd,
			  काष्ठा extent_buffer **eb_context)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा btrfs_block_group *cache = शून्य;
	काष्ठा extent_buffer *eb;
	पूर्णांक ret;

	अगर (!PagePrivate(page))
		वापस 0;

	अगर (btrfs_sb(page->mapping->host->i_sb)->sectorsize < PAGE_SIZE)
		वापस submit_eb_subpage(page, wbc, epd);

	spin_lock(&mapping->निजी_lock);
	अगर (!PagePrivate(page)) अणु
		spin_unlock(&mapping->निजी_lock);
		वापस 0;
	पूर्ण

	eb = (काष्ठा extent_buffer *)page->निजी;

	/*
	 * Shouldn't happen and normally this would be a BUG_ON but no poपूर्णांक
	 * crashing the machine क्रम something we can survive anyway.
	 */
	अगर (WARN_ON(!eb)) अणु
		spin_unlock(&mapping->निजी_lock);
		वापस 0;
	पूर्ण

	अगर (eb == *eb_context) अणु
		spin_unlock(&mapping->निजी_lock);
		वापस 0;
	पूर्ण
	ret = atomic_inc_not_zero(&eb->refs);
	spin_unlock(&mapping->निजी_lock);
	अगर (!ret)
		वापस 0;

	अगर (!btrfs_check_meta_ग_लिखो_poपूर्णांकer(eb->fs_info, eb, &cache)) अणु
		/*
		 * If क्रम_sync, this hole will be filled with
		 * trasnsaction commit.
		 */
		अगर (wbc->sync_mode == WB_SYNC_ALL && !wbc->क्रम_sync)
			ret = -EAGAIN;
		अन्यथा
			ret = 0;
		मुक्त_extent_buffer(eb);
		वापस ret;
	पूर्ण

	*eb_context = eb;

	ret = lock_extent_buffer_क्रम_io(eb, epd);
	अगर (ret <= 0) अणु
		btrfs_revert_meta_ग_लिखो_poपूर्णांकer(cache, eb);
		अगर (cache)
			btrfs_put_block_group(cache);
		मुक्त_extent_buffer(eb);
		वापस ret;
	पूर्ण
	अगर (cache)
		btrfs_put_block_group(cache);
	ret = ग_लिखो_one_eb(eb, wbc, epd);
	मुक्त_extent_buffer(eb);
	अगर (ret < 0)
		वापस ret;
	वापस 1;
पूर्ण

पूर्णांक btree_ग_लिखो_cache_pages(काष्ठा address_space *mapping,
				   काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा extent_buffer *eb_context = शून्य;
	काष्ठा extent_page_data epd = अणु
		.bio = शून्य,
		.extent_locked = 0,
		.sync_io = wbc->sync_mode == WB_SYNC_ALL,
	पूर्ण;
	काष्ठा btrfs_fs_info *fs_info = BTRFS_I(mapping->host)->root->fs_info;
	पूर्णांक ret = 0;
	पूर्णांक करोne = 0;
	पूर्णांक nr_to_ग_लिखो_करोne = 0;
	काष्ठा pagevec pvec;
	पूर्णांक nr_pages;
	pgoff_t index;
	pgoff_t end;		/* Inclusive */
	पूर्णांक scanned = 0;
	xa_mark_t tag;

	pagevec_init(&pvec);
	अगर (wbc->range_cyclic) अणु
		index = mapping->ग_लिखोback_index; /* Start from prev offset */
		end = -1;
		/*
		 * Start from the beginning करोes not need to cycle over the
		 * range, mark it as scanned.
		 */
		scanned = (index == 0);
	पूर्ण अन्यथा अणु
		index = wbc->range_start >> PAGE_SHIFT;
		end = wbc->range_end >> PAGE_SHIFT;
		scanned = 1;
	पूर्ण
	अगर (wbc->sync_mode == WB_SYNC_ALL)
		tag = PAGECACHE_TAG_TOWRITE;
	अन्यथा
		tag = PAGECACHE_TAG_सूचीTY;
	btrfs_zoned_meta_io_lock(fs_info);
retry:
	अगर (wbc->sync_mode == WB_SYNC_ALL)
		tag_pages_क्रम_ग_लिखोback(mapping, index, end);
	जबतक (!करोne && !nr_to_ग_लिखो_करोne && (index <= end) &&
	       (nr_pages = pagevec_lookup_range_tag(&pvec, mapping, &index, end,
			tag))) अणु
		अचिन्हित i;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			ret = submit_eb_page(page, wbc, &epd, &eb_context);
			अगर (ret == 0)
				जारी;
			अगर (ret < 0) अणु
				करोne = 1;
				अवरोध;
			पूर्ण

			/*
			 * the fileप्रणाली may choose to bump up nr_to_ग_लिखो.
			 * We have to make sure to honor the new nr_to_ग_लिखो
			 * at any समय
			 */
			nr_to_ग_लिखो_करोne = wbc->nr_to_ग_लिखो <= 0;
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
	अगर (!scanned && !करोne) अणु
		/*
		 * We hit the last page and there is more work to be करोne: wrap
		 * back to the start of the file
		 */
		scanned = 1;
		index = 0;
		जाओ retry;
	पूर्ण
	अगर (ret < 0) अणु
		end_ग_लिखो_bio(&epd, ret);
		जाओ out;
	पूर्ण
	/*
	 * If something went wrong, करोn't allow any metadata ग_लिखो bio to be
	 * submitted.
	 *
	 * This would prevent use-after-मुक्त अगर we had dirty pages not
	 * cleaned up, which can still happen by fuzzed images.
	 *
	 * - Bad extent tree
	 *   Allowing existing tree block to be allocated क्रम other trees.
	 *
	 * - Log tree operations
	 *   Exiting tree blocks get allocated to log tree, bumps its
	 *   generation, then get cleaned in tree re-balance.
	 *   Such tree block will not be written back, since it's clean,
	 *   thus no WRITTEN flag set.
	 *   And after log ग_लिखोs back, this tree block is not traced by
	 *   any dirty extent_io_tree.
	 *
	 * - Offending tree block माला_लो re-dirtied from its original owner
	 *   Since it has bumped generation, no WRITTEN flag, it can be
	 *   reused without COWing. This tree block will not be traced
	 *   by btrfs_transaction::dirty_pages.
	 *
	 *   Now such dirty tree block will not be cleaned by any dirty
	 *   extent io tree. Thus we करोn't want to submit such wild eb
	 *   अगर the fs alपढ़ोy has error.
	 */
	अगर (!test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state)) अणु
		ret = flush_ग_लिखो_bio(&epd);
	पूर्ण अन्यथा अणु
		ret = -EROFS;
		end_ग_लिखो_bio(&epd, ret);
	पूर्ण
out:
	btrfs_zoned_meta_io_unlock(fs_info);
	वापस ret;
पूर्ण

/**
 * Walk the list of dirty pages of the given address space and ग_लिखो all of them.
 *
 * @mapping: address space काष्ठाure to ग_लिखो
 * @wbc:     subtract the number of written pages from *@wbc->nr_to_ग_लिखो
 * @epd:     holds context क्रम the ग_लिखो, namely the bio
 *
 * If a page is alपढ़ोy under I/O, ग_लिखो_cache_pages() skips it, even
 * अगर it's dirty.  This is desirable behaviour क्रम memory-cleaning ग_लिखोback,
 * but it is INCORRECT क्रम data-पूर्णांकegrity प्रणाली calls such as fsync().  fsync()
 * and msync() need to guarantee that all the data which was dirty at the समय
 * the call was made get new I/O started against them.  If wbc->sync_mode is
 * WB_SYNC_ALL then we were called क्रम data पूर्णांकegrity and we must रुको क्रम
 * existing IO to complete.
 */
अटल पूर्णांक extent_ग_लिखो_cache_pages(काष्ठा address_space *mapping,
			     काष्ठा ग_लिखोback_control *wbc,
			     काष्ठा extent_page_data *epd)
अणु
	काष्ठा inode *inode = mapping->host;
	पूर्णांक ret = 0;
	पूर्णांक करोne = 0;
	पूर्णांक nr_to_ग_लिखो_करोne = 0;
	काष्ठा pagevec pvec;
	पूर्णांक nr_pages;
	pgoff_t index;
	pgoff_t end;		/* Inclusive */
	pgoff_t करोne_index;
	पूर्णांक range_whole = 0;
	पूर्णांक scanned = 0;
	xa_mark_t tag;

	/*
	 * We have to hold onto the inode so that ordered extents can करो their
	 * work when the IO finishes.  The alternative to this is failing to add
	 * an ordered extent अगर the igrab() fails there and that is a huge pain
	 * to deal with, so instead just hold onto the inode throughout the
	 * ग_लिखोpages operation.  If it fails here we are मुक्तing up the inode
	 * anyway and we'd rather not waste our समय writing out stuff that is
	 * going to be truncated anyway.
	 */
	अगर (!igrab(inode))
		वापस 0;

	pagevec_init(&pvec);
	अगर (wbc->range_cyclic) अणु
		index = mapping->ग_लिखोback_index; /* Start from prev offset */
		end = -1;
		/*
		 * Start from the beginning करोes not need to cycle over the
		 * range, mark it as scanned.
		 */
		scanned = (index == 0);
	पूर्ण अन्यथा अणु
		index = wbc->range_start >> PAGE_SHIFT;
		end = wbc->range_end >> PAGE_SHIFT;
		अगर (wbc->range_start == 0 && wbc->range_end == Lदीर्घ_उच्च)
			range_whole = 1;
		scanned = 1;
	पूर्ण

	/*
	 * We करो the tagged ग_लिखोpage as दीर्घ as the snapshot flush bit is set
	 * and we are the first one who करो the filemap_flush() on this inode.
	 *
	 * The nr_to_ग_लिखो == दीर्घ_उच्च is needed to make sure other flushers करो
	 * not race in and drop the bit.
	 */
	अगर (range_whole && wbc->nr_to_ग_लिखो == दीर्घ_उच्च &&
	    test_and_clear_bit(BTRFS_INODE_SNAPSHOT_FLUSH,
			       &BTRFS_I(inode)->runसमय_flags))
		wbc->tagged_ग_लिखोpages = 1;

	अगर (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages)
		tag = PAGECACHE_TAG_TOWRITE;
	अन्यथा
		tag = PAGECACHE_TAG_सूचीTY;
retry:
	अगर (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages)
		tag_pages_क्रम_ग_लिखोback(mapping, index, end);
	करोne_index = index;
	जबतक (!करोne && !nr_to_ग_लिखो_करोne && (index <= end) &&
			(nr_pages = pagevec_lookup_range_tag(&pvec, mapping,
						&index, end, tag))) अणु
		अचिन्हित i;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			करोne_index = page->index + 1;
			/*
			 * At this poपूर्णांक we hold neither the i_pages lock nor
			 * the page lock: the page may be truncated or
			 * invalidated (changing page->mapping to शून्य),
			 * or even swizzled back from swapper_space to
			 * पंचांगpfs file mapping
			 */
			अगर (!trylock_page(page)) अणु
				ret = flush_ग_लिखो_bio(epd);
				BUG_ON(ret < 0);
				lock_page(page);
			पूर्ण

			अगर (unlikely(page->mapping != mapping)) अणु
				unlock_page(page);
				जारी;
			पूर्ण

			अगर (wbc->sync_mode != WB_SYNC_NONE) अणु
				अगर (PageWriteback(page)) अणु
					ret = flush_ग_लिखो_bio(epd);
					BUG_ON(ret < 0);
				पूर्ण
				रुको_on_page_ग_लिखोback(page);
			पूर्ण

			अगर (PageWriteback(page) ||
			    !clear_page_dirty_क्रम_io(page)) अणु
				unlock_page(page);
				जारी;
			पूर्ण

			ret = __extent_ग_लिखोpage(page, wbc, epd);
			अगर (ret < 0) अणु
				करोne = 1;
				अवरोध;
			पूर्ण

			/*
			 * the fileप्रणाली may choose to bump up nr_to_ग_लिखो.
			 * We have to make sure to honor the new nr_to_ग_लिखो
			 * at any समय
			 */
			nr_to_ग_लिखो_करोne = wbc->nr_to_ग_लिखो <= 0;
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
	अगर (!scanned && !करोne) अणु
		/*
		 * We hit the last page and there is more work to be करोne: wrap
		 * back to the start of the file
		 */
		scanned = 1;
		index = 0;

		/*
		 * If we're looping we could run पूर्णांकo a page that is locked by a
		 * ग_लिखोr and that ग_लिखोr could be रुकोing on ग_लिखोback क्रम a
		 * page in our current bio, and thus deadlock, so flush the
		 * ग_लिखो bio here.
		 */
		ret = flush_ग_लिखो_bio(epd);
		अगर (!ret)
			जाओ retry;
	पूर्ण

	अगर (wbc->range_cyclic || (wbc->nr_to_ग_लिखो > 0 && range_whole))
		mapping->ग_लिखोback_index = करोne_index;

	btrfs_add_delayed_iput(inode);
	वापस ret;
पूर्ण

पूर्णांक extent_ग_लिखो_full_page(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;
	काष्ठा extent_page_data epd = अणु
		.bio = शून्य,
		.extent_locked = 0,
		.sync_io = wbc->sync_mode == WB_SYNC_ALL,
	पूर्ण;

	ret = __extent_ग_लिखोpage(page, wbc, &epd);
	ASSERT(ret <= 0);
	अगर (ret < 0) अणु
		end_ग_लिखो_bio(&epd, ret);
		वापस ret;
	पूर्ण

	ret = flush_ग_लिखो_bio(&epd);
	ASSERT(ret <= 0);
	वापस ret;
पूर्ण

पूर्णांक extent_ग_लिखो_locked_range(काष्ठा inode *inode, u64 start, u64 end,
			      पूर्णांक mode)
अणु
	पूर्णांक ret = 0;
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;
	अचिन्हित दीर्घ nr_pages = (end - start + PAGE_SIZE) >>
		PAGE_SHIFT;

	काष्ठा extent_page_data epd = अणु
		.bio = शून्य,
		.extent_locked = 1,
		.sync_io = mode == WB_SYNC_ALL,
	पूर्ण;
	काष्ठा ग_लिखोback_control wbc_ग_लिखोpages = अणु
		.sync_mode	= mode,
		.nr_to_ग_लिखो	= nr_pages * 2,
		.range_start	= start,
		.range_end	= end + 1,
		/* We're called from an async helper function */
		.punt_to_cgroup	= 1,
		.no_cgroup_owner = 1,
	पूर्ण;

	wbc_attach_fdataग_लिखो_inode(&wbc_ग_लिखोpages, inode);
	जबतक (start <= end) अणु
		page = find_get_page(mapping, start >> PAGE_SHIFT);
		अगर (clear_page_dirty_क्रम_io(page))
			ret = __extent_ग_लिखोpage(page, &wbc_ग_लिखोpages, &epd);
		अन्यथा अणु
			btrfs_ग_लिखोpage_endio_finish_ordered(page, start,
						    start + PAGE_SIZE - 1, 1);
			unlock_page(page);
		पूर्ण
		put_page(page);
		start += PAGE_SIZE;
	पूर्ण

	ASSERT(ret <= 0);
	अगर (ret == 0)
		ret = flush_ग_लिखो_bio(&epd);
	अन्यथा
		end_ग_लिखो_bio(&epd, ret);

	wbc_detach_inode(&wbc_ग_लिखोpages);
	वापस ret;
पूर्ण

पूर्णांक extent_ग_लिखोpages(काष्ठा address_space *mapping,
		      काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret = 0;
	काष्ठा extent_page_data epd = अणु
		.bio = शून्य,
		.extent_locked = 0,
		.sync_io = wbc->sync_mode == WB_SYNC_ALL,
	पूर्ण;

	ret = extent_ग_लिखो_cache_pages(mapping, wbc, &epd);
	ASSERT(ret <= 0);
	अगर (ret < 0) अणु
		end_ग_लिखो_bio(&epd, ret);
		वापस ret;
	पूर्ण
	ret = flush_ग_लिखो_bio(&epd);
	वापस ret;
पूर्ण

व्योम extent_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	काष्ठा bio *bio = शून्य;
	अचिन्हित दीर्घ bio_flags = 0;
	काष्ठा page *pagepool[16];
	काष्ठा extent_map *em_cached = शून्य;
	u64 prev_em_start = (u64)-1;
	पूर्णांक nr;

	जबतक ((nr = पढ़ोahead_page_batch(rac, pagepool))) अणु
		u64 contig_start = पढ़ोahead_pos(rac);
		u64 contig_end = contig_start + पढ़ोahead_batch_length(rac) - 1;

		contiguous_पढ़ोpages(pagepool, nr, contig_start, contig_end,
				&em_cached, &bio, &bio_flags, &prev_em_start);
	पूर्ण

	अगर (em_cached)
		मुक्त_extent_map(em_cached);

	अगर (bio) अणु
		अगर (submit_one_bio(bio, 0, bio_flags))
			वापस;
	पूर्ण
पूर्ण

/*
 * basic invalidatepage code, this रुकोs on any locked or ग_लिखोback
 * ranges corresponding to the page, and then deletes any extent state
 * records from the tree
 */
पूर्णांक extent_invalidatepage(काष्ठा extent_io_tree *tree,
			  काष्ठा page *page, अचिन्हित दीर्घ offset)
अणु
	काष्ठा extent_state *cached_state = शून्य;
	u64 start = page_offset(page);
	u64 end = start + PAGE_SIZE - 1;
	माप_प्रकार blocksize = page->mapping->host->i_sb->s_blocksize;

	/* This function is only called क्रम the btree inode */
	ASSERT(tree->owner == IO_TREE_BTREE_INODE_IO);

	start += ALIGN(offset, blocksize);
	अगर (start > end)
		वापस 0;

	lock_extent_bits(tree, start, end, &cached_state);
	रुको_on_page_ग_लिखोback(page);

	/*
	 * Currently क्रम btree io tree, only EXTENT_LOCKED is utilized,
	 * so here we only need to unlock the extent range to मुक्त any
	 * existing extent state.
	 */
	unlock_extent_cached(tree, start, end, &cached_state);
	वापस 0;
पूर्ण

/*
 * a helper क्रम releasepage, this tests क्रम areas of the page that
 * are locked or under IO and drops the related state bits अगर it is safe
 * to drop the page.
 */
अटल पूर्णांक try_release_extent_state(काष्ठा extent_io_tree *tree,
				    काष्ठा page *page, gfp_t mask)
अणु
	u64 start = page_offset(page);
	u64 end = start + PAGE_SIZE - 1;
	पूर्णांक ret = 1;

	अगर (test_range_bit(tree, start, end, EXTENT_LOCKED, 0, शून्य)) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		/*
		 * At this poपूर्णांक we can safely clear everything except the
		 * locked bit, the nodatasum bit and the delalloc new bit.
		 * The delalloc new bit will be cleared by ordered extent
		 * completion.
		 */
		ret = __clear_extent_bit(tree, start, end,
			 ~(EXTENT_LOCKED | EXTENT_NODATASUM | EXTENT_DELALLOC_NEW),
			 0, 0, शून्य, mask, शून्य);

		/* अगर clear_extent_bit failed क्रम enomem reasons,
		 * we can't allow the release to जारी.
		 */
		अगर (ret < 0)
			ret = 0;
		अन्यथा
			ret = 1;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * a helper क्रम releasepage.  As दीर्घ as there are no locked extents
 * in the range corresponding to the page, both state records and extent
 * map records are हटाओd
 */
पूर्णांक try_release_extent_mapping(काष्ठा page *page, gfp_t mask)
अणु
	काष्ठा extent_map *em;
	u64 start = page_offset(page);
	u64 end = start + PAGE_SIZE - 1;
	काष्ठा btrfs_inode *btrfs_inode = BTRFS_I(page->mapping->host);
	काष्ठा extent_io_tree *tree = &btrfs_inode->io_tree;
	काष्ठा extent_map_tree *map = &btrfs_inode->extent_tree;

	अगर (gfpflags_allow_blocking(mask) &&
	    page->mapping->host->i_size > SZ_16M) अणु
		u64 len;
		जबतक (start <= end) अणु
			काष्ठा btrfs_fs_info *fs_info;
			u64 cur_gen;

			len = end - start + 1;
			ग_लिखो_lock(&map->lock);
			em = lookup_extent_mapping(map, start, len);
			अगर (!em) अणु
				ग_लिखो_unlock(&map->lock);
				अवरोध;
			पूर्ण
			अगर (test_bit(EXTENT_FLAG_PINNED, &em->flags) ||
			    em->start != start) अणु
				ग_लिखो_unlock(&map->lock);
				मुक्त_extent_map(em);
				अवरोध;
			पूर्ण
			अगर (test_range_bit(tree, em->start,
					   extent_map_end(em) - 1,
					   EXTENT_LOCKED, 0, शून्य))
				जाओ next;
			/*
			 * If it's not in the list of modअगरied extents, used
			 * by a fast fsync, we can हटाओ it. If it's being
			 * logged we can safely हटाओ it since fsync took an
			 * extra reference on the em.
			 */
			अगर (list_empty(&em->list) ||
			    test_bit(EXTENT_FLAG_LOGGING, &em->flags))
				जाओ हटाओ_em;
			/*
			 * If it's in the list of modअगरied extents, हटाओ it
			 * only अगर its generation is older then the current one,
			 * in which हाल we करोn't need it क्रम a fast fsync.
			 * Otherwise करोn't हटाओ it, we could be racing with an
			 * ongoing fast fsync that could miss the new extent.
			 */
			fs_info = btrfs_inode->root->fs_info;
			spin_lock(&fs_info->trans_lock);
			cur_gen = fs_info->generation;
			spin_unlock(&fs_info->trans_lock);
			अगर (em->generation >= cur_gen)
				जाओ next;
हटाओ_em:
			/*
			 * We only हटाओ extent maps that are not in the list of
			 * modअगरied extents or that are in the list but with a
			 * generation lower then the current generation, so there
			 * is no need to set the full fsync flag on the inode (it
			 * hurts the fsync perक्रमmance क्रम workloads with a data
			 * size that exceeds or is बंद to the प्रणाली's memory).
			 */
			हटाओ_extent_mapping(map, em);
			/* once क्रम the rb tree */
			मुक्त_extent_map(em);
next:
			start = extent_map_end(em);
			ग_लिखो_unlock(&map->lock);

			/* once क्रम us */
			मुक्त_extent_map(em);

			cond_resched(); /* Allow large-extent preemption. */
		पूर्ण
	पूर्ण
	वापस try_release_extent_state(tree, page, mask);
पूर्ण

/*
 * helper function क्रम fiemap, which करोesn't want to see any holes.
 * This maps until we find something past 'last'
 */
अटल काष्ठा extent_map *get_extent_skip_holes(काष्ठा btrfs_inode *inode,
						u64 offset, u64 last)
अणु
	u64 sectorsize = btrfs_inode_sectorsize(inode);
	काष्ठा extent_map *em;
	u64 len;

	अगर (offset >= last)
		वापस शून्य;

	जबतक (1) अणु
		len = last - offset;
		अगर (len == 0)
			अवरोध;
		len = ALIGN(len, sectorsize);
		em = btrfs_get_extent_fiemap(inode, offset, len);
		अगर (IS_ERR_OR_शून्य(em))
			वापस em;

		/* अगर this isn't a hole वापस it */
		अगर (em->block_start != EXTENT_MAP_HOLE)
			वापस em;

		/* this is a hole, advance to the next extent */
		offset = extent_map_end(em);
		मुक्त_extent_map(em);
		अगर (offset >= last)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * To cache previous fiemap extent
 *
 * Will be used क्रम merging fiemap extent
 */
काष्ठा fiemap_cache अणु
	u64 offset;
	u64 phys;
	u64 len;
	u32 flags;
	bool cached;
पूर्ण;

/*
 * Helper to submit fiemap extent.
 *
 * Will try to merge current fiemap extent specअगरied by @offset, @phys,
 * @len and @flags with cached one.
 * And only when we fails to merge, cached one will be submitted as
 * fiemap extent.
 *
 * Return value is the same as fiemap_fill_next_extent().
 */
अटल पूर्णांक emit_fiemap_extent(काष्ठा fiemap_extent_info *fieinfo,
				काष्ठा fiemap_cache *cache,
				u64 offset, u64 phys, u64 len, u32 flags)
अणु
	पूर्णांक ret = 0;

	अगर (!cache->cached)
		जाओ assign;

	/*
	 * Sanity check, extent_fiemap() should have ensured that new
	 * fiemap extent won't overlap with cached one.
	 * Not recoverable.
	 *
	 * NOTE: Physical address can overlap, due to compression
	 */
	अगर (cache->offset + cache->len > offset) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Only merges fiemap extents अगर
	 * 1) Their logical addresses are continuous
	 *
	 * 2) Their physical addresses are continuous
	 *    So truly compressed (physical size smaller than logical size)
	 *    extents won't get merged with each other
	 *
	 * 3) Share same flags except FIEMAP_EXTENT_LAST
	 *    So regular extent won't get merged with pपुनः_स्मृति extent
	 */
	अगर (cache->offset + cache->len  == offset &&
	    cache->phys + cache->len == phys  &&
	    (cache->flags & ~FIEMAP_EXTENT_LAST) ==
			(flags & ~FIEMAP_EXTENT_LAST)) अणु
		cache->len += len;
		cache->flags |= flags;
		जाओ try_submit_last;
	पूर्ण

	/* Not mergeable, need to submit cached one */
	ret = fiemap_fill_next_extent(fieinfo, cache->offset, cache->phys,
				      cache->len, cache->flags);
	cache->cached = false;
	अगर (ret)
		वापस ret;
assign:
	cache->cached = true;
	cache->offset = offset;
	cache->phys = phys;
	cache->len = len;
	cache->flags = flags;
try_submit_last:
	अगर (cache->flags & FIEMAP_EXTENT_LAST) अणु
		ret = fiemap_fill_next_extent(fieinfo, cache->offset,
				cache->phys, cache->len, cache->flags);
		cache->cached = false;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Emit last fiemap cache
 *
 * The last fiemap cache may still be cached in the following हाल:
 * 0		      4k		    8k
 * |<- Fiemap range ->|
 * |<------------  First extent ----------->|
 *
 * In this हाल, the first extent range will be cached but not emitted.
 * So we must emit it beक्रमe ending extent_fiemap().
 */
अटल पूर्णांक emit_last_fiemap_cache(काष्ठा fiemap_extent_info *fieinfo,
				  काष्ठा fiemap_cache *cache)
अणु
	पूर्णांक ret;

	अगर (!cache->cached)
		वापस 0;

	ret = fiemap_fill_next_extent(fieinfo, cache->offset, cache->phys,
				      cache->len, cache->flags);
	cache->cached = false;
	अगर (ret > 0)
		ret = 0;
	वापस ret;
पूर्ण

पूर्णांक extent_fiemap(काष्ठा btrfs_inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		  u64 start, u64 len)
अणु
	पूर्णांक ret = 0;
	u64 off;
	u64 max = start + len;
	u32 flags = 0;
	u32 found_type;
	u64 last;
	u64 last_क्रम_get_extent = 0;
	u64 disko = 0;
	u64 isize = i_size_पढ़ो(&inode->vfs_inode);
	काष्ठा btrfs_key found_key;
	काष्ठा extent_map *em = शून्य;
	काष्ठा extent_state *cached_state = शून्य;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *root = inode->root;
	काष्ठा fiemap_cache cache = अणु 0 पूर्ण;
	काष्ठा ulist *roots;
	काष्ठा ulist *पंचांगp_ulist;
	पूर्णांक end = 0;
	u64 em_start = 0;
	u64 em_len = 0;
	u64 em_end = 0;

	अगर (len == 0)
		वापस -EINVAL;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	roots = ulist_alloc(GFP_KERNEL);
	पंचांगp_ulist = ulist_alloc(GFP_KERNEL);
	अगर (!roots || !पंचांगp_ulist) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_ulist;
	पूर्ण

	/*
	 * We can't initialize that to 'start' as this could miss extents due
	 * to extent item merging
	 */
	off = 0;
	start = round_करोwn(start, btrfs_inode_sectorsize(inode));
	len = round_up(max, btrfs_inode_sectorsize(inode)) - start;

	/*
	 * lookup the last file extent.  We're not using i_size here
	 * because there might be pपुनः_स्मृतिation past i_size
	 */
	ret = btrfs_lookup_file_extent(शून्य, root, path, btrfs_ino(inode), -1,
				       0);
	अगर (ret < 0) अणु
		जाओ out_मुक्त_ulist;
	पूर्ण अन्यथा अणु
		WARN_ON(!ret);
		अगर (ret == 1)
			ret = 0;
	पूर्ण

	path->slots[0]--;
	btrfs_item_key_to_cpu(path->nodes[0], &found_key, path->slots[0]);
	found_type = found_key.type;

	/* No extents, but there might be delalloc bits */
	अगर (found_key.objectid != btrfs_ino(inode) ||
	    found_type != BTRFS_EXTENT_DATA_KEY) अणु
		/* have to trust i_size as the end */
		last = (u64)-1;
		last_क्रम_get_extent = isize;
	पूर्ण अन्यथा अणु
		/*
		 * remember the start of the last extent.  There are a
		 * bunch of dअगरferent factors that go पूर्णांकo the length of the
		 * extent, so its much less complex to remember where it started
		 */
		last = found_key.offset;
		last_क्रम_get_extent = last + 1;
	पूर्ण
	btrfs_release_path(path);

	/*
	 * we might have some extents allocated but more delalloc past those
	 * extents.  so, we trust isize unless the start of the last extent is
	 * beyond isize
	 */
	अगर (last < isize) अणु
		last = (u64)-1;
		last_क्रम_get_extent = isize;
	पूर्ण

	lock_extent_bits(&inode->io_tree, start, start + len - 1,
			 &cached_state);

	em = get_extent_skip_holes(inode, start, last_क्रम_get_extent);
	अगर (!em)
		जाओ out;
	अगर (IS_ERR(em)) अणु
		ret = PTR_ERR(em);
		जाओ out;
	पूर्ण

	जबतक (!end) अणु
		u64 offset_in_extent = 0;

		/* अवरोध अगर the extent we found is outside the range */
		अगर (em->start >= max || extent_map_end(em) < off)
			अवरोध;

		/*
		 * get_extent may वापस an extent that starts beक्रमe our
		 * requested range.  We have to make sure the ranges
		 * we वापस to fiemap always move क्रमward and करोn't
		 * overlap, so adjust the offsets here
		 */
		em_start = max(em->start, off);

		/*
		 * record the offset from the start of the extent
		 * क्रम adjusting the disk offset below.  Only करो this अगर the
		 * extent isn't compressed since our in ram offset may be past
		 * what we have actually allocated on disk.
		 */
		अगर (!test_bit(EXTENT_FLAG_COMPRESSED, &em->flags))
			offset_in_extent = em_start - em->start;
		em_end = extent_map_end(em);
		em_len = em_end - em_start;
		flags = 0;
		अगर (em->block_start < EXTENT_MAP_LAST_BYTE)
			disko = em->block_start + offset_in_extent;
		अन्यथा
			disko = 0;

		/*
		 * bump off क्रम our next call to get_extent
		 */
		off = extent_map_end(em);
		अगर (off >= max)
			end = 1;

		अगर (em->block_start == EXTENT_MAP_LAST_BYTE) अणु
			end = 1;
			flags |= FIEMAP_EXTENT_LAST;
		पूर्ण अन्यथा अगर (em->block_start == EXTENT_MAP_INLINE) अणु
			flags |= (FIEMAP_EXTENT_DATA_INLINE |
				  FIEMAP_EXTENT_NOT_ALIGNED);
		पूर्ण अन्यथा अगर (em->block_start == EXTENT_MAP_DELALLOC) अणु
			flags |= (FIEMAP_EXTENT_DELALLOC |
				  FIEMAP_EXTENT_UNKNOWN);
		पूर्ण अन्यथा अगर (fieinfo->fi_extents_max) अणु
			u64 bytenr = em->block_start -
				(em->start - em->orig_start);

			/*
			 * As btrfs supports shared space, this inक्रमmation
			 * can be exported to userspace tools via
			 * flag FIEMAP_EXTENT_SHARED.  If fi_extents_max == 0
			 * then we're just getting a count and we can skip the
			 * lookup stuff.
			 */
			ret = btrfs_check_shared(root, btrfs_ino(inode),
						 bytenr, roots, पंचांगp_ulist);
			अगर (ret < 0)
				जाओ out_मुक्त;
			अगर (ret)
				flags |= FIEMAP_EXTENT_SHARED;
			ret = 0;
		पूर्ण
		अगर (test_bit(EXTENT_FLAG_COMPRESSED, &em->flags))
			flags |= FIEMAP_EXTENT_ENCODED;
		अगर (test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
			flags |= FIEMAP_EXTENT_UNWRITTEN;

		मुक्त_extent_map(em);
		em = शून्य;
		अगर ((em_start >= last) || em_len == (u64)-1 ||
		   (last == (u64)-1 && isize <= em_end)) अणु
			flags |= FIEMAP_EXTENT_LAST;
			end = 1;
		पूर्ण

		/* now scan क्रमward to see अगर this is really the last extent. */
		em = get_extent_skip_holes(inode, off, last_क्रम_get_extent);
		अगर (IS_ERR(em)) अणु
			ret = PTR_ERR(em);
			जाओ out;
		पूर्ण
		अगर (!em) अणु
			flags |= FIEMAP_EXTENT_LAST;
			end = 1;
		पूर्ण
		ret = emit_fiemap_extent(fieinfo, &cache, em_start, disko,
					   em_len, flags);
		अगर (ret) अणु
			अगर (ret == 1)
				ret = 0;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण
out_मुक्त:
	अगर (!ret)
		ret = emit_last_fiemap_cache(fieinfo, &cache);
	मुक्त_extent_map(em);
out:
	unlock_extent_cached(&inode->io_tree, start, start + len - 1,
			     &cached_state);

out_मुक्त_ulist:
	btrfs_मुक्त_path(path);
	ulist_मुक्त(roots);
	ulist_मुक्त(पंचांगp_ulist);
	वापस ret;
पूर्ण

अटल व्योम __मुक्त_extent_buffer(काष्ठा extent_buffer *eb)
अणु
	kmem_cache_मुक्त(extent_buffer_cache, eb);
पूर्ण

पूर्णांक extent_buffer_under_io(स्थिर काष्ठा extent_buffer *eb)
अणु
	वापस (atomic_पढ़ो(&eb->io_pages) ||
		test_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags) ||
		test_bit(EXTENT_BUFFER_सूचीTY, &eb->bflags));
पूर्ण

अटल bool page_range_has_eb(काष्ठा btrfs_fs_info *fs_info, काष्ठा page *page)
अणु
	काष्ठा btrfs_subpage *subpage;

	lockdep_निश्चित_held(&page->mapping->निजी_lock);

	अगर (PagePrivate(page)) अणु
		subpage = (काष्ठा btrfs_subpage *)page->निजी;
		अगर (atomic_पढ़ो(&subpage->eb_refs))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम detach_extent_buffer_page(काष्ठा extent_buffer *eb, काष्ठा page *page)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	स्थिर bool mapped = !test_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags);

	/*
	 * For mapped eb, we're going to change the page निजी, which should
	 * be करोne under the निजी_lock.
	 */
	अगर (mapped)
		spin_lock(&page->mapping->निजी_lock);

	अगर (!PagePrivate(page)) अणु
		अगर (mapped)
			spin_unlock(&page->mapping->निजी_lock);
		वापस;
	पूर्ण

	अगर (fs_info->sectorsize == PAGE_SIZE) अणु
		/*
		 * We करो this since we'll remove the pages after we've
		 * हटाओd the eb from the radix tree, so we could race
		 * and have this page now attached to the new eb.  So
		 * only clear page_निजी अगर it's still connected to
		 * this eb.
		 */
		अगर (PagePrivate(page) &&
		    page->निजी == (अचिन्हित दीर्घ)eb) अणु
			BUG_ON(test_bit(EXTENT_BUFFER_सूचीTY, &eb->bflags));
			BUG_ON(PageDirty(page));
			BUG_ON(PageWriteback(page));
			/*
			 * We need to make sure we haven't be attached
			 * to a new eb.
			 */
			detach_page_निजी(page);
		पूर्ण
		अगर (mapped)
			spin_unlock(&page->mapping->निजी_lock);
		वापस;
	पूर्ण

	/*
	 * For subpage, we can have dummy eb with page निजी.  In this हाल,
	 * we can directly detach the निजी as such page is only attached to
	 * one dummy eb, no sharing.
	 */
	अगर (!mapped) अणु
		btrfs_detach_subpage(fs_info, page);
		वापस;
	पूर्ण

	btrfs_page_dec_eb_refs(fs_info, page);

	/*
	 * We can only detach the page निजी अगर there are no other ebs in the
	 * page range.
	 */
	अगर (!page_range_has_eb(fs_info, page))
		btrfs_detach_subpage(fs_info, page);

	spin_unlock(&page->mapping->निजी_lock);
पूर्ण

/* Release all pages attached to the extent buffer */
अटल व्योम btrfs_release_extent_buffer_pages(काष्ठा extent_buffer *eb)
अणु
	पूर्णांक i;
	पूर्णांक num_pages;

	ASSERT(!extent_buffer_under_io(eb));

	num_pages = num_extent_pages(eb);
	क्रम (i = 0; i < num_pages; i++) अणु
		काष्ठा page *page = eb->pages[i];

		अगर (!page)
			जारी;

		detach_extent_buffer_page(eb, page);

		/* One क्रम when we allocated the page */
		put_page(page);
	पूर्ण
पूर्ण

/*
 * Helper क्रम releasing the extent buffer.
 */
अटल अंतरभूत व्योम btrfs_release_extent_buffer(काष्ठा extent_buffer *eb)
अणु
	btrfs_release_extent_buffer_pages(eb);
	btrfs_leak_debug_del(&eb->fs_info->eb_leak_lock, &eb->leak_list);
	__मुक्त_extent_buffer(eb);
पूर्ण

अटल काष्ठा extent_buffer *
__alloc_extent_buffer(काष्ठा btrfs_fs_info *fs_info, u64 start,
		      अचिन्हित दीर्घ len)
अणु
	काष्ठा extent_buffer *eb = शून्य;

	eb = kmem_cache_zalloc(extent_buffer_cache, GFP_NOFS|__GFP_NOFAIL);
	eb->start = start;
	eb->len = len;
	eb->fs_info = fs_info;
	eb->bflags = 0;
	init_rwsem(&eb->lock);

	btrfs_leak_debug_add(&fs_info->eb_leak_lock, &eb->leak_list,
			     &fs_info->allocated_ebs);
	INIT_LIST_HEAD(&eb->release_list);

	spin_lock_init(&eb->refs_lock);
	atomic_set(&eb->refs, 1);
	atomic_set(&eb->io_pages, 0);

	ASSERT(len <= BTRFS_MAX_METADATA_BLOCKSIZE);

	वापस eb;
पूर्ण

काष्ठा extent_buffer *btrfs_clone_extent_buffer(स्थिर काष्ठा extent_buffer *src)
अणु
	पूर्णांक i;
	काष्ठा page *p;
	काष्ठा extent_buffer *new;
	पूर्णांक num_pages = num_extent_pages(src);

	new = __alloc_extent_buffer(src->fs_info, src->start, src->len);
	अगर (new == शून्य)
		वापस शून्य;

	/*
	 * Set UNMAPPED beक्रमe calling btrfs_release_extent_buffer(), as
	 * btrfs_release_extent_buffer() have dअगरferent behavior क्रम
	 * UNMAPPED subpage extent buffer.
	 */
	set_bit(EXTENT_BUFFER_UNMAPPED, &new->bflags);

	क्रम (i = 0; i < num_pages; i++) अणु
		पूर्णांक ret;

		p = alloc_page(GFP_NOFS);
		अगर (!p) अणु
			btrfs_release_extent_buffer(new);
			वापस शून्य;
		पूर्ण
		ret = attach_extent_buffer_page(new, p, शून्य);
		अगर (ret < 0) अणु
			put_page(p);
			btrfs_release_extent_buffer(new);
			वापस शून्य;
		पूर्ण
		WARN_ON(PageDirty(p));
		new->pages[i] = p;
		copy_page(page_address(p), page_address(src->pages[i]));
	पूर्ण
	set_extent_buffer_uptodate(new);

	वापस new;
पूर्ण

काष्ठा extent_buffer *__alloc_dummy_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
						  u64 start, अचिन्हित दीर्घ len)
अणु
	काष्ठा extent_buffer *eb;
	पूर्णांक num_pages;
	पूर्णांक i;

	eb = __alloc_extent_buffer(fs_info, start, len);
	अगर (!eb)
		वापस शून्य;

	num_pages = num_extent_pages(eb);
	क्रम (i = 0; i < num_pages; i++) अणु
		पूर्णांक ret;

		eb->pages[i] = alloc_page(GFP_NOFS);
		अगर (!eb->pages[i])
			जाओ err;
		ret = attach_extent_buffer_page(eb, eb->pages[i], शून्य);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
	set_extent_buffer_uptodate(eb);
	btrfs_set_header_nritems(eb, 0);
	set_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags);

	वापस eb;
err:
	क्रम (; i > 0; i--) अणु
		detach_extent_buffer_page(eb, eb->pages[i - 1]);
		__मुक्त_page(eb->pages[i - 1]);
	पूर्ण
	__मुक्त_extent_buffer(eb);
	वापस शून्य;
पूर्ण

काष्ठा extent_buffer *alloc_dummy_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
						u64 start)
अणु
	वापस __alloc_dummy_extent_buffer(fs_info, start, fs_info->nodesize);
पूर्ण

अटल व्योम check_buffer_tree_ref(काष्ठा extent_buffer *eb)
अणु
	पूर्णांक refs;
	/*
	 * The TREE_REF bit is first set when the extent_buffer is added
	 * to the radix tree. It is also reset, अगर unset, when a new reference
	 * is created by find_extent_buffer.
	 *
	 * It is only cleared in two हालs: मुक्तing the last non-tree
	 * reference to the extent_buffer when its STALE bit is set or
	 * calling releasepage when the tree reference is the only reference.
	 *
	 * In both हालs, care is taken to ensure that the extent_buffer's
	 * pages are not under io. However, releasepage can be concurrently
	 * called with creating new references, which is prone to race
	 * conditions between the calls to check_buffer_tree_ref in those
	 * codepaths and clearing TREE_REF in try_release_extent_buffer.
	 *
	 * The actual lअगरeसमय of the extent_buffer in the radix tree is
	 * adequately रक्षित by the refcount, but the TREE_REF bit and
	 * its corresponding reference are not. To protect against this
	 * class of races, we call check_buffer_tree_ref from the codepaths
	 * which trigger io after they set eb->io_pages. Note that once io is
	 * initiated, TREE_REF can no दीर्घer be cleared, so that is the
	 * moment at which any such race is best fixed.
	 */
	refs = atomic_पढ़ो(&eb->refs);
	अगर (refs >= 2 && test_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags))
		वापस;

	spin_lock(&eb->refs_lock);
	अगर (!test_and_set_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags))
		atomic_inc(&eb->refs);
	spin_unlock(&eb->refs_lock);
पूर्ण

अटल व्योम mark_extent_buffer_accessed(काष्ठा extent_buffer *eb,
		काष्ठा page *accessed)
अणु
	पूर्णांक num_pages, i;

	check_buffer_tree_ref(eb);

	num_pages = num_extent_pages(eb);
	क्रम (i = 0; i < num_pages; i++) अणु
		काष्ठा page *p = eb->pages[i];

		अगर (p != accessed)
			mark_page_accessed(p);
	पूर्ण
पूर्ण

काष्ठा extent_buffer *find_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
					 u64 start)
अणु
	काष्ठा extent_buffer *eb;

	eb = find_extent_buffer_nolock(fs_info, start);
	अगर (!eb)
		वापस शून्य;
	/*
	 * Lock our eb's refs_lock to aव्योम races with मुक्त_extent_buffer().
	 * When we get our eb it might be flagged with EXTENT_BUFFER_STALE and
	 * another task running मुक्त_extent_buffer() might have seen that flag
	 * set, eb->refs == 2, that the buffer isn't under IO (dirty and
	 * ग_लिखोback flags not set) and it's still in the tree (flag
	 * EXTENT_BUFFER_TREE_REF set), thereक्रमe being in the process of
	 * decrementing the extent buffer's reference count twice.  So here we
	 * could race and increment the eb's reference count, clear its stale
	 * flag, mark it as dirty and drop our reference beक्रमe the other task
	 * finishes executing मुक्त_extent_buffer, which would later result in
	 * an attempt to मुक्त an extent buffer that is dirty.
	 */
	अगर (test_bit(EXTENT_BUFFER_STALE, &eb->bflags)) अणु
		spin_lock(&eb->refs_lock);
		spin_unlock(&eb->refs_lock);
	पूर्ण
	mark_extent_buffer_accessed(eb, शून्य);
	वापस eb;
पूर्ण

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
काष्ठा extent_buffer *alloc_test_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
					u64 start)
अणु
	काष्ठा extent_buffer *eb, *exists = शून्य;
	पूर्णांक ret;

	eb = find_extent_buffer(fs_info, start);
	अगर (eb)
		वापस eb;
	eb = alloc_dummy_extent_buffer(fs_info, start);
	अगर (!eb)
		वापस ERR_PTR(-ENOMEM);
	eb->fs_info = fs_info;
again:
	ret = radix_tree_preload(GFP_NOFS);
	अगर (ret) अणु
		exists = ERR_PTR(ret);
		जाओ मुक्त_eb;
	पूर्ण
	spin_lock(&fs_info->buffer_lock);
	ret = radix_tree_insert(&fs_info->buffer_radix,
				start >> fs_info->sectorsize_bits, eb);
	spin_unlock(&fs_info->buffer_lock);
	radix_tree_preload_end();
	अगर (ret == -EEXIST) अणु
		exists = find_extent_buffer(fs_info, start);
		अगर (exists)
			जाओ मुक्त_eb;
		अन्यथा
			जाओ again;
	पूर्ण
	check_buffer_tree_ref(eb);
	set_bit(EXTENT_BUFFER_IN_TREE, &eb->bflags);

	वापस eb;
मुक्त_eb:
	btrfs_release_extent_buffer(eb);
	वापस exists;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा extent_buffer *grab_extent_buffer(
		काष्ठा btrfs_fs_info *fs_info, काष्ठा page *page)
अणु
	काष्ठा extent_buffer *exists;

	/*
	 * For subpage हाल, we completely rely on radix tree to ensure we
	 * करोn't try to insert two ebs क्रम the same bytenr.  So here we always
	 * वापस शून्य and just जारी.
	 */
	अगर (fs_info->sectorsize < PAGE_SIZE)
		वापस शून्य;

	/* Page not yet attached to an extent buffer */
	अगर (!PagePrivate(page))
		वापस शून्य;

	/*
	 * We could have alपढ़ोy allocated an eb क्रम this page and attached one
	 * so lets see अगर we can get a ref on the existing eb, and अगर we can we
	 * know it's good and we can just वापस that one, अन्यथा we know we can
	 * just overग_लिखो page->निजी.
	 */
	exists = (काष्ठा extent_buffer *)page->निजी;
	अगर (atomic_inc_not_zero(&exists->refs))
		वापस exists;

	WARN_ON(PageDirty(page));
	detach_page_निजी(page);
	वापस शून्य;
पूर्ण

काष्ठा extent_buffer *alloc_extent_buffer(काष्ठा btrfs_fs_info *fs_info,
					  u64 start, u64 owner_root, पूर्णांक level)
अणु
	अचिन्हित दीर्घ len = fs_info->nodesize;
	पूर्णांक num_pages;
	पूर्णांक i;
	अचिन्हित दीर्घ index = start >> PAGE_SHIFT;
	काष्ठा extent_buffer *eb;
	काष्ठा extent_buffer *exists = शून्य;
	काष्ठा page *p;
	काष्ठा address_space *mapping = fs_info->btree_inode->i_mapping;
	पूर्णांक uptodate = 1;
	पूर्णांक ret;

	अगर (!IS_ALIGNED(start, fs_info->sectorsize)) अणु
		btrfs_err(fs_info, "bad tree block start %llu", start);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

#अगर BITS_PER_LONG == 32
	अगर (start >= MAX_LFS_खाताSIZE) अणु
		btrfs_err_rl(fs_info,
		"extent buffer %llu is beyond 32bit page cache limit", start);
		btrfs_err_32bit_limit(fs_info);
		वापस ERR_PTR(-EOVERFLOW);
	पूर्ण
	अगर (start >= BTRFS_32BIT_EARLY_WARN_THRESHOLD)
		btrfs_warn_32bit_limit(fs_info);
#पूर्ण_अगर

	अगर (fs_info->sectorsize < PAGE_SIZE &&
	    offset_in_page(start) + len > PAGE_SIZE) अणु
		btrfs_err(fs_info,
		"tree block crosses page boundary, start %llu nodesize %lu",
			  start, len);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	eb = find_extent_buffer(fs_info, start);
	अगर (eb)
		वापस eb;

	eb = __alloc_extent_buffer(fs_info, start, len);
	अगर (!eb)
		वापस ERR_PTR(-ENOMEM);
	btrfs_set_buffer_lockdep_class(owner_root, eb, level);

	num_pages = num_extent_pages(eb);
	क्रम (i = 0; i < num_pages; i++, index++) अणु
		काष्ठा btrfs_subpage *pपुनः_स्मृति = शून्य;

		p = find_or_create_page(mapping, index, GFP_NOFS|__GFP_NOFAIL);
		अगर (!p) अणु
			exists = ERR_PTR(-ENOMEM);
			जाओ मुक्त_eb;
		पूर्ण

		/*
		 * Pपुनः_स्मृतिate page->निजी क्रम subpage हाल, so that we won't
		 * allocate memory with निजी_lock hold.  The memory will be
		 * मुक्तd by attach_extent_buffer_page() or मुक्तd manually अगर
		 * we निकास earlier.
		 *
		 * Although we have ensured one subpage eb can only have one
		 * page, but it may change in the future क्रम 16K page size
		 * support, so we still pपुनः_स्मृतिate the memory in the loop.
		 */
		ret = btrfs_alloc_subpage(fs_info, &pपुनः_स्मृति,
					  BTRFS_SUBPAGE_METADATA);
		अगर (ret < 0) अणु
			unlock_page(p);
			put_page(p);
			exists = ERR_PTR(ret);
			जाओ मुक्त_eb;
		पूर्ण

		spin_lock(&mapping->निजी_lock);
		exists = grab_extent_buffer(fs_info, p);
		अगर (exists) अणु
			spin_unlock(&mapping->निजी_lock);
			unlock_page(p);
			put_page(p);
			mark_extent_buffer_accessed(exists, p);
			btrfs_मुक्त_subpage(pपुनः_स्मृति);
			जाओ मुक्त_eb;
		पूर्ण
		/* Should not fail, as we have pपुनः_स्मृतिated the memory */
		ret = attach_extent_buffer_page(eb, p, pपुनः_स्मृति);
		ASSERT(!ret);
		/*
		 * To inक्रमm we have extra eb under allocation, so that
		 * detach_extent_buffer_page() won't release the page निजी
		 * when the eb hasn't yet been inserted पूर्णांकo radix tree.
		 *
		 * The ref will be decreased when the eb released the page, in
		 * detach_extent_buffer_page().
		 * Thus needs no special handling in error path.
		 */
		btrfs_page_inc_eb_refs(fs_info, p);
		spin_unlock(&mapping->निजी_lock);

		WARN_ON(btrfs_page_test_dirty(fs_info, p, eb->start, eb->len));
		eb->pages[i] = p;
		अगर (!PageUptodate(p))
			uptodate = 0;

		/*
		 * We can't unlock the pages just yet since the extent buffer
		 * hasn't been properly inserted in the radix tree, this
		 * खोलोs a race with btree_releasepage which can मुक्त a page
		 * जबतक we are still filling in all pages क्रम the buffer and
		 * we could crash.
		 */
	पूर्ण
	अगर (uptodate)
		set_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
again:
	ret = radix_tree_preload(GFP_NOFS);
	अगर (ret) अणु
		exists = ERR_PTR(ret);
		जाओ मुक्त_eb;
	पूर्ण

	spin_lock(&fs_info->buffer_lock);
	ret = radix_tree_insert(&fs_info->buffer_radix,
				start >> fs_info->sectorsize_bits, eb);
	spin_unlock(&fs_info->buffer_lock);
	radix_tree_preload_end();
	अगर (ret == -EEXIST) अणु
		exists = find_extent_buffer(fs_info, start);
		अगर (exists)
			जाओ मुक्त_eb;
		अन्यथा
			जाओ again;
	पूर्ण
	/* add one reference क्रम the tree */
	check_buffer_tree_ref(eb);
	set_bit(EXTENT_BUFFER_IN_TREE, &eb->bflags);

	/*
	 * Now it's safe to unlock the pages because any calls to
	 * btree_releasepage will correctly detect that a page beदीर्घs to a
	 * live buffer and won't मुक्त them prematurely.
	 */
	क्रम (i = 0; i < num_pages; i++)
		unlock_page(eb->pages[i]);
	वापस eb;

मुक्त_eb:
	WARN_ON(!atomic_dec_and_test(&eb->refs));
	क्रम (i = 0; i < num_pages; i++) अणु
		अगर (eb->pages[i])
			unlock_page(eb->pages[i]);
	पूर्ण

	btrfs_release_extent_buffer(eb);
	वापस exists;
पूर्ण

अटल अंतरभूत व्योम btrfs_release_extent_buffer_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा extent_buffer *eb =
			container_of(head, काष्ठा extent_buffer, rcu_head);

	__मुक्त_extent_buffer(eb);
पूर्ण

अटल पूर्णांक release_extent_buffer(काष्ठा extent_buffer *eb)
	__releases(&eb->refs_lock)
अणु
	lockdep_निश्चित_held(&eb->refs_lock);

	WARN_ON(atomic_पढ़ो(&eb->refs) == 0);
	अगर (atomic_dec_and_test(&eb->refs)) अणु
		अगर (test_and_clear_bit(EXTENT_BUFFER_IN_TREE, &eb->bflags)) अणु
			काष्ठा btrfs_fs_info *fs_info = eb->fs_info;

			spin_unlock(&eb->refs_lock);

			spin_lock(&fs_info->buffer_lock);
			radix_tree_delete(&fs_info->buffer_radix,
					  eb->start >> fs_info->sectorsize_bits);
			spin_unlock(&fs_info->buffer_lock);
		पूर्ण अन्यथा अणु
			spin_unlock(&eb->refs_lock);
		पूर्ण

		btrfs_leak_debug_del(&eb->fs_info->eb_leak_lock, &eb->leak_list);
		/* Should be safe to release our pages at this poपूर्णांक */
		btrfs_release_extent_buffer_pages(eb);
#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
		अगर (unlikely(test_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags))) अणु
			__मुक्त_extent_buffer(eb);
			वापस 1;
		पूर्ण
#पूर्ण_अगर
		call_rcu(&eb->rcu_head, btrfs_release_extent_buffer_rcu);
		वापस 1;
	पूर्ण
	spin_unlock(&eb->refs_lock);

	वापस 0;
पूर्ण

व्योम मुक्त_extent_buffer(काष्ठा extent_buffer *eb)
अणु
	पूर्णांक refs;
	पूर्णांक old;
	अगर (!eb)
		वापस;

	जबतक (1) अणु
		refs = atomic_पढ़ो(&eb->refs);
		अगर ((!test_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags) && refs <= 3)
		    || (test_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags) &&
			refs == 1))
			अवरोध;
		old = atomic_cmpxchg(&eb->refs, refs, refs - 1);
		अगर (old == refs)
			वापस;
	पूर्ण

	spin_lock(&eb->refs_lock);
	अगर (atomic_पढ़ो(&eb->refs) == 2 &&
	    test_bit(EXTENT_BUFFER_STALE, &eb->bflags) &&
	    !extent_buffer_under_io(eb) &&
	    test_and_clear_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags))
		atomic_dec(&eb->refs);

	/*
	 * I know this is terrible, but it's temporary until we stop tracking
	 * the uptodate bits and such क्रम the extent buffers.
	 */
	release_extent_buffer(eb);
पूर्ण

व्योम मुक्त_extent_buffer_stale(काष्ठा extent_buffer *eb)
अणु
	अगर (!eb)
		वापस;

	spin_lock(&eb->refs_lock);
	set_bit(EXTENT_BUFFER_STALE, &eb->bflags);

	अगर (atomic_पढ़ो(&eb->refs) == 2 && !extent_buffer_under_io(eb) &&
	    test_and_clear_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags))
		atomic_dec(&eb->refs);
	release_extent_buffer(eb);
पूर्ण

अटल व्योम btree_clear_page_dirty(काष्ठा page *page)
अणु
	ASSERT(PageDirty(page));
	ASSERT(PageLocked(page));
	clear_page_dirty_क्रम_io(page);
	xa_lock_irq(&page->mapping->i_pages);
	अगर (!PageDirty(page))
		__xa_clear_mark(&page->mapping->i_pages,
				page_index(page), PAGECACHE_TAG_सूचीTY);
	xa_unlock_irq(&page->mapping->i_pages);
पूर्ण

अटल व्योम clear_subpage_extent_buffer_dirty(स्थिर काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा page *page = eb->pages[0];
	bool last;

	/* btree_clear_page_dirty() needs page locked */
	lock_page(page);
	last = btrfs_subpage_clear_and_test_dirty(fs_info, page, eb->start,
						  eb->len);
	अगर (last)
		btree_clear_page_dirty(page);
	unlock_page(page);
	WARN_ON(atomic_पढ़ो(&eb->refs) == 0);
पूर्ण

व्योम clear_extent_buffer_dirty(स्थिर काष्ठा extent_buffer *eb)
अणु
	पूर्णांक i;
	पूर्णांक num_pages;
	काष्ठा page *page;

	अगर (eb->fs_info->sectorsize < PAGE_SIZE)
		वापस clear_subpage_extent_buffer_dirty(eb);

	num_pages = num_extent_pages(eb);

	क्रम (i = 0; i < num_pages; i++) अणु
		page = eb->pages[i];
		अगर (!PageDirty(page))
			जारी;
		lock_page(page);
		btree_clear_page_dirty(page);
		ClearPageError(page);
		unlock_page(page);
	पूर्ण
	WARN_ON(atomic_पढ़ो(&eb->refs) == 0);
पूर्ण

bool set_extent_buffer_dirty(काष्ठा extent_buffer *eb)
अणु
	पूर्णांक i;
	पूर्णांक num_pages;
	bool was_dirty;

	check_buffer_tree_ref(eb);

	was_dirty = test_and_set_bit(EXTENT_BUFFER_सूचीTY, &eb->bflags);

	num_pages = num_extent_pages(eb);
	WARN_ON(atomic_पढ़ो(&eb->refs) == 0);
	WARN_ON(!test_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags));

	अगर (!was_dirty) अणु
		bool subpage = eb->fs_info->sectorsize < PAGE_SIZE;

		/*
		 * For subpage हाल, we can have other extent buffers in the
		 * same page, and in clear_subpage_extent_buffer_dirty() we
		 * have to clear page dirty without subpage lock held.
		 * This can cause race where our page माला_लो dirty cleared after
		 * we just set it.
		 *
		 * Thankfully, clear_subpage_extent_buffer_dirty() has locked
		 * its page क्रम other reasons, we can use page lock to prevent
		 * the above race.
		 */
		अगर (subpage)
			lock_page(eb->pages[0]);
		क्रम (i = 0; i < num_pages; i++)
			btrfs_page_set_dirty(eb->fs_info, eb->pages[i],
					     eb->start, eb->len);
		अगर (subpage)
			unlock_page(eb->pages[0]);
	पूर्ण
#अगर_घोषित CONFIG_BTRFS_DEBUG
	क्रम (i = 0; i < num_pages; i++)
		ASSERT(PageDirty(eb->pages[i]));
#पूर्ण_अगर

	वापस was_dirty;
पूर्ण

व्योम clear_extent_buffer_uptodate(काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा page *page;
	पूर्णांक num_pages;
	पूर्णांक i;

	clear_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
	num_pages = num_extent_pages(eb);
	क्रम (i = 0; i < num_pages; i++) अणु
		page = eb->pages[i];
		अगर (page)
			btrfs_page_clear_uptodate(fs_info, page,
						  eb->start, eb->len);
	पूर्ण
पूर्ण

व्योम set_extent_buffer_uptodate(काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा page *page;
	पूर्णांक num_pages;
	पूर्णांक i;

	set_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
	num_pages = num_extent_pages(eb);
	क्रम (i = 0; i < num_pages; i++) अणु
		page = eb->pages[i];
		btrfs_page_set_uptodate(fs_info, page, eb->start, eb->len);
	पूर्ण
पूर्ण

अटल पूर्णांक पढ़ो_extent_buffer_subpage(काष्ठा extent_buffer *eb, पूर्णांक रुको,
				      पूर्णांक mirror_num)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;
	काष्ठा extent_io_tree *io_tree;
	काष्ठा page *page = eb->pages[0];
	काष्ठा bio *bio = शून्य;
	पूर्णांक ret = 0;

	ASSERT(!test_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags));
	ASSERT(PagePrivate(page));
	io_tree = &BTRFS_I(fs_info->btree_inode)->io_tree;

	अगर (रुको == WAIT_NONE) अणु
		ret = try_lock_extent(io_tree, eb->start,
				      eb->start + eb->len - 1);
		अगर (ret <= 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = lock_extent(io_tree, eb->start, eb->start + eb->len - 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = 0;
	अगर (test_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags) ||
	    PageUptodate(page) ||
	    btrfs_subpage_test_uptodate(fs_info, page, eb->start, eb->len)) अणु
		set_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
		unlock_extent(io_tree, eb->start, eb->start + eb->len - 1);
		वापस ret;
	पूर्ण

	clear_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags);
	eb->पढ़ो_mirror = 0;
	atomic_set(&eb->io_pages, 1);
	check_buffer_tree_ref(eb);
	btrfs_subpage_clear_error(fs_info, page, eb->start, eb->len);

	ret = submit_extent_page(REQ_OP_READ | REQ_META, शून्य, page, eb->start,
				 eb->len, eb->start - page_offset(page), &bio,
				 end_bio_extent_पढ़ोpage, mirror_num, 0, 0,
				 true);
	अगर (ret) अणु
		/*
		 * In the endio function, अगर we hit something wrong we will
		 * increase the io_pages, so here we need to decrease it क्रम
		 * error path.
		 */
		atomic_dec(&eb->io_pages);
	पूर्ण
	अगर (bio) अणु
		पूर्णांक पंचांगp;

		पंचांगp = submit_one_bio(bio, mirror_num, 0);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
	पूर्ण
	अगर (ret || रुको != WAIT_COMPLETE)
		वापस ret;

	रुको_extent_bit(io_tree, eb->start, eb->start + eb->len - 1, EXTENT_LOCKED);
	अगर (!test_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags))
		ret = -EIO;
	वापस ret;
पूर्ण

पूर्णांक पढ़ो_extent_buffer_pages(काष्ठा extent_buffer *eb, पूर्णांक रुको, पूर्णांक mirror_num)
अणु
	पूर्णांक i;
	काष्ठा page *page;
	पूर्णांक err;
	पूर्णांक ret = 0;
	पूर्णांक locked_pages = 0;
	पूर्णांक all_uptodate = 1;
	पूर्णांक num_pages;
	अचिन्हित दीर्घ num_पढ़ोs = 0;
	काष्ठा bio *bio = शून्य;
	अचिन्हित दीर्घ bio_flags = 0;

	अगर (test_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags))
		वापस 0;

	अगर (eb->fs_info->sectorsize < PAGE_SIZE)
		वापस पढ़ो_extent_buffer_subpage(eb, रुको, mirror_num);

	num_pages = num_extent_pages(eb);
	क्रम (i = 0; i < num_pages; i++) अणु
		page = eb->pages[i];
		अगर (रुको == WAIT_NONE) अणु
			/*
			 * WAIT_NONE is only utilized by पढ़ोahead. If we can't
			 * acquire the lock atomically it means either the eb
			 * is being पढ़ो out or under modअगरication.
			 * Either way the eb will be or has been cached,
			 * पढ़ोahead can निकास safely.
			 */
			अगर (!trylock_page(page))
				जाओ unlock_निकास;
		पूर्ण अन्यथा अणु
			lock_page(page);
		पूर्ण
		locked_pages++;
	पूर्ण
	/*
	 * We need to firstly lock all pages to make sure that
	 * the uptodate bit of our pages won't be affected by
	 * clear_extent_buffer_uptodate().
	 */
	क्रम (i = 0; i < num_pages; i++) अणु
		page = eb->pages[i];
		अगर (!PageUptodate(page)) अणु
			num_पढ़ोs++;
			all_uptodate = 0;
		पूर्ण
	पूर्ण

	अगर (all_uptodate) अणु
		set_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
		जाओ unlock_निकास;
	पूर्ण

	clear_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags);
	eb->पढ़ो_mirror = 0;
	atomic_set(&eb->io_pages, num_पढ़ोs);
	/*
	 * It is possible क्रम releasepage to clear the TREE_REF bit beक्रमe we
	 * set io_pages. See check_buffer_tree_ref क्रम a more detailed comment.
	 */
	check_buffer_tree_ref(eb);
	क्रम (i = 0; i < num_pages; i++) अणु
		page = eb->pages[i];

		अगर (!PageUptodate(page)) अणु
			अगर (ret) अणु
				atomic_dec(&eb->io_pages);
				unlock_page(page);
				जारी;
			पूर्ण

			ClearPageError(page);
			err = submit_extent_page(REQ_OP_READ | REQ_META, शून्य,
					 page, page_offset(page), PAGE_SIZE, 0,
					 &bio, end_bio_extent_पढ़ोpage,
					 mirror_num, 0, 0, false);
			अगर (err) अणु
				/*
				 * We failed to submit the bio so it's the
				 * caller's responsibility to perक्रमm cleanup
				 * i.e unlock page/set error bit.
				 */
				ret = err;
				SetPageError(page);
				unlock_page(page);
				atomic_dec(&eb->io_pages);
			पूर्ण
		पूर्ण अन्यथा अणु
			unlock_page(page);
		पूर्ण
	पूर्ण

	अगर (bio) अणु
		err = submit_one_bio(bio, mirror_num, bio_flags);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (ret || रुको != WAIT_COMPLETE)
		वापस ret;

	क्रम (i = 0; i < num_pages; i++) अणु
		page = eb->pages[i];
		रुको_on_page_locked(page);
		अगर (!PageUptodate(page))
			ret = -EIO;
	पूर्ण

	वापस ret;

unlock_निकास:
	जबतक (locked_pages > 0) अणु
		locked_pages--;
		page = eb->pages[locked_pages];
		unlock_page(page);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool report_eb_range(स्थिर काष्ठा extent_buffer *eb, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ len)
अणु
	btrfs_warn(eb->fs_info,
		"access to eb bytenr %llu len %lu out of range start %lu len %lu",
		eb->start, eb->len, start, len);
	WARN_ON(IS_ENABLED(CONFIG_BTRFS_DEBUG));

	वापस true;
पूर्ण

/*
 * Check अगर the [start, start + len) range is valid beक्रमe पढ़ोing/writing
 * the eb.
 * NOTE: @start and @len are offset inside the eb, not logical address.
 *
 * Caller should not touch the dst/src memory अगर this function वापसs error.
 */
अटल अंतरभूत पूर्णांक check_eb_range(स्थिर काष्ठा extent_buffer *eb,
				 अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ offset;

	/* start, start + len should not go beyond eb->len nor overflow */
	अगर (unlikely(check_add_overflow(start, len, &offset) || offset > eb->len))
		वापस report_eb_range(eb, start, len);

	वापस false;
पूर्ण

व्योम पढ़ो_extent_buffer(स्थिर काष्ठा extent_buffer *eb, व्योम *dstv,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	माप_प्रकार cur;
	माप_प्रकार offset;
	काष्ठा page *page;
	अक्षर *kaddr;
	अक्षर *dst = (अक्षर *)dstv;
	अचिन्हित दीर्घ i = get_eb_page_index(start);

	अगर (check_eb_range(eb, start, len))
		वापस;

	offset = get_eb_offset_in_page(eb, start);

	जबतक (len > 0) अणु
		page = eb->pages[i];

		cur = min(len, (PAGE_SIZE - offset));
		kaddr = page_address(page);
		स_नकल(dst, kaddr + offset, cur);

		dst += cur;
		len -= cur;
		offset = 0;
		i++;
	पूर्ण
पूर्ण

पूर्णांक पढ़ो_extent_buffer_to_user_nofault(स्थिर काष्ठा extent_buffer *eb,
				       व्योम __user *dstv,
				       अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	माप_प्रकार cur;
	माप_प्रकार offset;
	काष्ठा page *page;
	अक्षर *kaddr;
	अक्षर __user *dst = (अक्षर __user *)dstv;
	अचिन्हित दीर्घ i = get_eb_page_index(start);
	पूर्णांक ret = 0;

	WARN_ON(start > eb->len);
	WARN_ON(start + len > eb->start + eb->len);

	offset = get_eb_offset_in_page(eb, start);

	जबतक (len > 0) अणु
		page = eb->pages[i];

		cur = min(len, (PAGE_SIZE - offset));
		kaddr = page_address(page);
		अगर (copy_to_user_nofault(dst, kaddr + offset, cur)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		dst += cur;
		len -= cur;
		offset = 0;
		i++;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक स_भेद_extent_buffer(स्थिर काष्ठा extent_buffer *eb, स्थिर व्योम *ptrv,
			 अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	माप_प्रकार cur;
	माप_प्रकार offset;
	काष्ठा page *page;
	अक्षर *kaddr;
	अक्षर *ptr = (अक्षर *)ptrv;
	अचिन्हित दीर्घ i = get_eb_page_index(start);
	पूर्णांक ret = 0;

	अगर (check_eb_range(eb, start, len))
		वापस -EINVAL;

	offset = get_eb_offset_in_page(eb, start);

	जबतक (len > 0) अणु
		page = eb->pages[i];

		cur = min(len, (PAGE_SIZE - offset));

		kaddr = page_address(page);
		ret = स_भेद(ptr, kaddr + offset, cur);
		अगर (ret)
			अवरोध;

		ptr += cur;
		len -= cur;
		offset = 0;
		i++;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Check that the extent buffer is uptodate.
 *
 * For regular sector size == PAGE_SIZE हाल, check अगर @page is uptodate.
 * For subpage हाल, check अगर the range covered by the eb has EXTENT_UPTODATE.
 */
अटल व्योम निश्चित_eb_page_uptodate(स्थिर काष्ठा extent_buffer *eb,
				    काष्ठा page *page)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;

	अगर (fs_info->sectorsize < PAGE_SIZE) अणु
		bool uptodate;

		uptodate = btrfs_subpage_test_uptodate(fs_info, page,
						       eb->start, eb->len);
		WARN_ON(!uptodate);
	पूर्ण अन्यथा अणु
		WARN_ON(!PageUptodate(page));
	पूर्ण
पूर्ण

व्योम ग_लिखो_extent_buffer_chunk_tree_uuid(स्थिर काष्ठा extent_buffer *eb,
		स्थिर व्योम *srcv)
अणु
	अक्षर *kaddr;

	निश्चित_eb_page_uptodate(eb, eb->pages[0]);
	kaddr = page_address(eb->pages[0]) + get_eb_offset_in_page(eb, 0);
	स_नकल(kaddr + दुरत्व(काष्ठा btrfs_header, chunk_tree_uuid), srcv,
			BTRFS_FSID_SIZE);
पूर्ण

व्योम ग_लिखो_extent_buffer_fsid(स्थिर काष्ठा extent_buffer *eb, स्थिर व्योम *srcv)
अणु
	अक्षर *kaddr;

	निश्चित_eb_page_uptodate(eb, eb->pages[0]);
	kaddr = page_address(eb->pages[0]) + get_eb_offset_in_page(eb, 0);
	स_नकल(kaddr + दुरत्व(काष्ठा btrfs_header, fsid), srcv,
			BTRFS_FSID_SIZE);
पूर्ण

व्योम ग_लिखो_extent_buffer(स्थिर काष्ठा extent_buffer *eb, स्थिर व्योम *srcv,
			 अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	माप_प्रकार cur;
	माप_प्रकार offset;
	काष्ठा page *page;
	अक्षर *kaddr;
	अक्षर *src = (अक्षर *)srcv;
	अचिन्हित दीर्घ i = get_eb_page_index(start);

	WARN_ON(test_bit(EXTENT_BUFFER_NO_CHECK, &eb->bflags));

	अगर (check_eb_range(eb, start, len))
		वापस;

	offset = get_eb_offset_in_page(eb, start);

	जबतक (len > 0) अणु
		page = eb->pages[i];
		निश्चित_eb_page_uptodate(eb, page);

		cur = min(len, PAGE_SIZE - offset);
		kaddr = page_address(page);
		स_नकल(kaddr + offset, src, cur);

		src += cur;
		len -= cur;
		offset = 0;
		i++;
	पूर्ण
पूर्ण

व्योम memzero_extent_buffer(स्थिर काष्ठा extent_buffer *eb, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ len)
अणु
	माप_प्रकार cur;
	माप_प्रकार offset;
	काष्ठा page *page;
	अक्षर *kaddr;
	अचिन्हित दीर्घ i = get_eb_page_index(start);

	अगर (check_eb_range(eb, start, len))
		वापस;

	offset = get_eb_offset_in_page(eb, start);

	जबतक (len > 0) अणु
		page = eb->pages[i];
		निश्चित_eb_page_uptodate(eb, page);

		cur = min(len, PAGE_SIZE - offset);
		kaddr = page_address(page);
		स_रखो(kaddr + offset, 0, cur);

		len -= cur;
		offset = 0;
		i++;
	पूर्ण
पूर्ण

व्योम copy_extent_buffer_full(स्थिर काष्ठा extent_buffer *dst,
			     स्थिर काष्ठा extent_buffer *src)
अणु
	पूर्णांक i;
	पूर्णांक num_pages;

	ASSERT(dst->len == src->len);

	अगर (dst->fs_info->sectorsize == PAGE_SIZE) अणु
		num_pages = num_extent_pages(dst);
		क्रम (i = 0; i < num_pages; i++)
			copy_page(page_address(dst->pages[i]),
				  page_address(src->pages[i]));
	पूर्ण अन्यथा अणु
		माप_प्रकार src_offset = get_eb_offset_in_page(src, 0);
		माप_प्रकार dst_offset = get_eb_offset_in_page(dst, 0);

		ASSERT(src->fs_info->sectorsize < PAGE_SIZE);
		स_नकल(page_address(dst->pages[0]) + dst_offset,
		       page_address(src->pages[0]) + src_offset,
		       src->len);
	पूर्ण
पूर्ण

व्योम copy_extent_buffer(स्थिर काष्ठा extent_buffer *dst,
			स्थिर काष्ठा extent_buffer *src,
			अचिन्हित दीर्घ dst_offset, अचिन्हित दीर्घ src_offset,
			अचिन्हित दीर्घ len)
अणु
	u64 dst_len = dst->len;
	माप_प्रकार cur;
	माप_प्रकार offset;
	काष्ठा page *page;
	अक्षर *kaddr;
	अचिन्हित दीर्घ i = get_eb_page_index(dst_offset);

	अगर (check_eb_range(dst, dst_offset, len) ||
	    check_eb_range(src, src_offset, len))
		वापस;

	WARN_ON(src->len != dst_len);

	offset = get_eb_offset_in_page(dst, dst_offset);

	जबतक (len > 0) अणु
		page = dst->pages[i];
		निश्चित_eb_page_uptodate(dst, page);

		cur = min(len, (अचिन्हित दीर्घ)(PAGE_SIZE - offset));

		kaddr = page_address(page);
		पढ़ो_extent_buffer(src, kaddr + offset, src_offset, cur);

		src_offset += cur;
		len -= cur;
		offset = 0;
		i++;
	पूर्ण
पूर्ण

/*
 * eb_biपंचांगap_offset() - calculate the page and offset of the byte containing the
 * given bit number
 * @eb: the extent buffer
 * @start: offset of the biपंचांगap item in the extent buffer
 * @nr: bit number
 * @page_index: वापस index of the page in the extent buffer that contains the
 * given bit number
 * @page_offset: वापस offset पूर्णांकo the page given by page_index
 *
 * This helper hides the ugliness of finding the byte in an extent buffer which
 * contains a given bit.
 */
अटल अंतरभूत व्योम eb_biपंचांगap_offset(स्थिर काष्ठा extent_buffer *eb,
				    अचिन्हित दीर्घ start, अचिन्हित दीर्घ nr,
				    अचिन्हित दीर्घ *page_index,
				    माप_प्रकार *page_offset)
अणु
	माप_प्रकार byte_offset = BIT_BYTE(nr);
	माप_प्रकार offset;

	/*
	 * The byte we want is the offset of the extent buffer + the offset of
	 * the biपंचांगap item in the extent buffer + the offset of the byte in the
	 * biपंचांगap item.
	 */
	offset = start + offset_in_page(eb->start) + byte_offset;

	*page_index = offset >> PAGE_SHIFT;
	*page_offset = offset_in_page(offset);
पूर्ण

/**
 * extent_buffer_test_bit - determine whether a bit in a biपंचांगap item is set
 * @eb: the extent buffer
 * @start: offset of the biपंचांगap item in the extent buffer
 * @nr: bit number to test
 */
पूर्णांक extent_buffer_test_bit(स्थिर काष्ठा extent_buffer *eb, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ nr)
अणु
	u8 *kaddr;
	काष्ठा page *page;
	अचिन्हित दीर्घ i;
	माप_प्रकार offset;

	eb_biपंचांगap_offset(eb, start, nr, &i, &offset);
	page = eb->pages[i];
	निश्चित_eb_page_uptodate(eb, page);
	kaddr = page_address(page);
	वापस 1U & (kaddr[offset] >> (nr & (BITS_PER_BYTE - 1)));
पूर्ण

/**
 * extent_buffer_biपंचांगap_set - set an area of a biपंचांगap
 * @eb: the extent buffer
 * @start: offset of the biपंचांगap item in the extent buffer
 * @pos: bit number of the first bit
 * @len: number of bits to set
 */
व्योम extent_buffer_biपंचांगap_set(स्थिर काष्ठा extent_buffer *eb, अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ pos, अचिन्हित दीर्घ len)
अणु
	u8 *kaddr;
	काष्ठा page *page;
	अचिन्हित दीर्घ i;
	माप_प्रकार offset;
	स्थिर अचिन्हित पूर्णांक size = pos + len;
	पूर्णांक bits_to_set = BITS_PER_BYTE - (pos % BITS_PER_BYTE);
	u8 mask_to_set = BITMAP_FIRST_BYTE_MASK(pos);

	eb_biपंचांगap_offset(eb, start, pos, &i, &offset);
	page = eb->pages[i];
	निश्चित_eb_page_uptodate(eb, page);
	kaddr = page_address(page);

	जबतक (len >= bits_to_set) अणु
		kaddr[offset] |= mask_to_set;
		len -= bits_to_set;
		bits_to_set = BITS_PER_BYTE;
		mask_to_set = ~0;
		अगर (++offset >= PAGE_SIZE && len > 0) अणु
			offset = 0;
			page = eb->pages[++i];
			निश्चित_eb_page_uptodate(eb, page);
			kaddr = page_address(page);
		पूर्ण
	पूर्ण
	अगर (len) अणु
		mask_to_set &= BITMAP_LAST_BYTE_MASK(size);
		kaddr[offset] |= mask_to_set;
	पूर्ण
पूर्ण


/**
 * extent_buffer_biपंचांगap_clear - clear an area of a biपंचांगap
 * @eb: the extent buffer
 * @start: offset of the biपंचांगap item in the extent buffer
 * @pos: bit number of the first bit
 * @len: number of bits to clear
 */
व्योम extent_buffer_biपंचांगap_clear(स्थिर काष्ठा extent_buffer *eb,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ pos,
				अचिन्हित दीर्घ len)
अणु
	u8 *kaddr;
	काष्ठा page *page;
	अचिन्हित दीर्घ i;
	माप_प्रकार offset;
	स्थिर अचिन्हित पूर्णांक size = pos + len;
	पूर्णांक bits_to_clear = BITS_PER_BYTE - (pos % BITS_PER_BYTE);
	u8 mask_to_clear = BITMAP_FIRST_BYTE_MASK(pos);

	eb_biपंचांगap_offset(eb, start, pos, &i, &offset);
	page = eb->pages[i];
	निश्चित_eb_page_uptodate(eb, page);
	kaddr = page_address(page);

	जबतक (len >= bits_to_clear) अणु
		kaddr[offset] &= ~mask_to_clear;
		len -= bits_to_clear;
		bits_to_clear = BITS_PER_BYTE;
		mask_to_clear = ~0;
		अगर (++offset >= PAGE_SIZE && len > 0) अणु
			offset = 0;
			page = eb->pages[++i];
			निश्चित_eb_page_uptodate(eb, page);
			kaddr = page_address(page);
		पूर्ण
	पूर्ण
	अगर (len) अणु
		mask_to_clear &= BITMAP_LAST_BYTE_MASK(size);
		kaddr[offset] &= ~mask_to_clear;
	पूर्ण
पूर्ण

अटल अंतरभूत bool areas_overlap(अचिन्हित दीर्घ src, अचिन्हित दीर्घ dst, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ distance = (src > dst) ? src - dst : dst - src;
	वापस distance < len;
पूर्ण

अटल व्योम copy_pages(काष्ठा page *dst_page, काष्ठा page *src_page,
		       अचिन्हित दीर्घ dst_off, अचिन्हित दीर्घ src_off,
		       अचिन्हित दीर्घ len)
अणु
	अक्षर *dst_kaddr = page_address(dst_page);
	अक्षर *src_kaddr;
	पूर्णांक must_स_हटाओ = 0;

	अगर (dst_page != src_page) अणु
		src_kaddr = page_address(src_page);
	पूर्ण अन्यथा अणु
		src_kaddr = dst_kaddr;
		अगर (areas_overlap(src_off, dst_off, len))
			must_स_हटाओ = 1;
	पूर्ण

	अगर (must_स_हटाओ)
		स_हटाओ(dst_kaddr + dst_off, src_kaddr + src_off, len);
	अन्यथा
		स_नकल(dst_kaddr + dst_off, src_kaddr + src_off, len);
पूर्ण

व्योम स_नकल_extent_buffer(स्थिर काष्ठा extent_buffer *dst,
			  अचिन्हित दीर्घ dst_offset, अचिन्हित दीर्घ src_offset,
			  अचिन्हित दीर्घ len)
अणु
	माप_प्रकार cur;
	माप_प्रकार dst_off_in_page;
	माप_प्रकार src_off_in_page;
	अचिन्हित दीर्घ dst_i;
	अचिन्हित दीर्घ src_i;

	अगर (check_eb_range(dst, dst_offset, len) ||
	    check_eb_range(dst, src_offset, len))
		वापस;

	जबतक (len > 0) अणु
		dst_off_in_page = get_eb_offset_in_page(dst, dst_offset);
		src_off_in_page = get_eb_offset_in_page(dst, src_offset);

		dst_i = get_eb_page_index(dst_offset);
		src_i = get_eb_page_index(src_offset);

		cur = min(len, (अचिन्हित दीर्घ)(PAGE_SIZE -
					       src_off_in_page));
		cur = min_t(अचिन्हित दीर्घ, cur,
			(अचिन्हित दीर्घ)(PAGE_SIZE - dst_off_in_page));

		copy_pages(dst->pages[dst_i], dst->pages[src_i],
			   dst_off_in_page, src_off_in_page, cur);

		src_offset += cur;
		dst_offset += cur;
		len -= cur;
	पूर्ण
पूर्ण

व्योम स_हटाओ_extent_buffer(स्थिर काष्ठा extent_buffer *dst,
			   अचिन्हित दीर्घ dst_offset, अचिन्हित दीर्घ src_offset,
			   अचिन्हित दीर्घ len)
अणु
	माप_प्रकार cur;
	माप_प्रकार dst_off_in_page;
	माप_प्रकार src_off_in_page;
	अचिन्हित दीर्घ dst_end = dst_offset + len - 1;
	अचिन्हित दीर्घ src_end = src_offset + len - 1;
	अचिन्हित दीर्घ dst_i;
	अचिन्हित दीर्घ src_i;

	अगर (check_eb_range(dst, dst_offset, len) ||
	    check_eb_range(dst, src_offset, len))
		वापस;
	अगर (dst_offset < src_offset) अणु
		स_नकल_extent_buffer(dst, dst_offset, src_offset, len);
		वापस;
	पूर्ण
	जबतक (len > 0) अणु
		dst_i = get_eb_page_index(dst_end);
		src_i = get_eb_page_index(src_end);

		dst_off_in_page = get_eb_offset_in_page(dst, dst_end);
		src_off_in_page = get_eb_offset_in_page(dst, src_end);

		cur = min_t(अचिन्हित दीर्घ, len, src_off_in_page + 1);
		cur = min(cur, dst_off_in_page + 1);
		copy_pages(dst->pages[dst_i], dst->pages[src_i],
			   dst_off_in_page - cur + 1,
			   src_off_in_page - cur + 1, cur);

		dst_end -= cur;
		src_end -= cur;
		len -= cur;
	पूर्ण
पूर्ण

अटल काष्ठा extent_buffer *get_next_extent_buffer(
		काष्ठा btrfs_fs_info *fs_info, काष्ठा page *page, u64 bytenr)
अणु
	काष्ठा extent_buffer *gang[BTRFS_SUBPAGE_BITMAP_SIZE];
	काष्ठा extent_buffer *found = शून्य;
	u64 page_start = page_offset(page);
	पूर्णांक ret;
	पूर्णांक i;

	ASSERT(in_range(bytenr, page_start, PAGE_SIZE));
	ASSERT(PAGE_SIZE / fs_info->nodesize <= BTRFS_SUBPAGE_BITMAP_SIZE);
	lockdep_निश्चित_held(&fs_info->buffer_lock);

	ret = radix_tree_gang_lookup(&fs_info->buffer_radix, (व्योम **)gang,
			bytenr >> fs_info->sectorsize_bits,
			PAGE_SIZE / fs_info->nodesize);
	क्रम (i = 0; i < ret; i++) अणु
		/* Alपढ़ोy beyond page end */
		अगर (gang[i]->start >= page_start + PAGE_SIZE)
			अवरोध;
		/* Found one */
		अगर (gang[i]->start >= bytenr) अणु
			found = gang[i];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

अटल पूर्णांक try_release_subpage_extent_buffer(काष्ठा page *page)
अणु
	काष्ठा btrfs_fs_info *fs_info = btrfs_sb(page->mapping->host->i_sb);
	u64 cur = page_offset(page);
	स्थिर u64 end = page_offset(page) + PAGE_SIZE;
	पूर्णांक ret;

	जबतक (cur < end) अणु
		काष्ठा extent_buffer *eb = शून्य;

		/*
		 * Unlike try_release_extent_buffer() which uses page->निजी
		 * to grab buffer, क्रम subpage हाल we rely on radix tree, thus
		 * we need to ensure radix tree consistency.
		 *
		 * We also want an atomic snapshot of the radix tree, thus go
		 * with spinlock rather than RCU.
		 */
		spin_lock(&fs_info->buffer_lock);
		eb = get_next_extent_buffer(fs_info, page, cur);
		अगर (!eb) अणु
			/* No more eb in the page range after or at cur */
			spin_unlock(&fs_info->buffer_lock);
			अवरोध;
		पूर्ण
		cur = eb->start + eb->len;

		/*
		 * The same as try_release_extent_buffer(), to ensure the eb
		 * won't disappear out from under us.
		 */
		spin_lock(&eb->refs_lock);
		अगर (atomic_पढ़ो(&eb->refs) != 1 || extent_buffer_under_io(eb)) अणु
			spin_unlock(&eb->refs_lock);
			spin_unlock(&fs_info->buffer_lock);
			अवरोध;
		पूर्ण
		spin_unlock(&fs_info->buffer_lock);

		/*
		 * If tree ref isn't set then we know the ref on this eb is a
		 * real ref, so just वापस, this eb will likely be मुक्तd soon
		 * anyway.
		 */
		अगर (!test_and_clear_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags)) अणु
			spin_unlock(&eb->refs_lock);
			अवरोध;
		पूर्ण

		/*
		 * Here we करोn't care about the वापस value, we will always
		 * check the page निजी at the end.  And
		 * release_extent_buffer() will release the refs_lock.
		 */
		release_extent_buffer(eb);
	पूर्ण
	/*
	 * Finally to check अगर we have cleared page निजी, as अगर we have
	 * released all ebs in the page, the page निजी should be cleared now.
	 */
	spin_lock(&page->mapping->निजी_lock);
	अगर (!PagePrivate(page))
		ret = 1;
	अन्यथा
		ret = 0;
	spin_unlock(&page->mapping->निजी_lock);
	वापस ret;

पूर्ण

पूर्णांक try_release_extent_buffer(काष्ठा page *page)
अणु
	काष्ठा extent_buffer *eb;

	अगर (btrfs_sb(page->mapping->host->i_sb)->sectorsize < PAGE_SIZE)
		वापस try_release_subpage_extent_buffer(page);

	/*
	 * We need to make sure nobody is changing page->निजी, as we rely on
	 * page->निजी as the poपूर्णांकer to extent buffer.
	 */
	spin_lock(&page->mapping->निजी_lock);
	अगर (!PagePrivate(page)) अणु
		spin_unlock(&page->mapping->निजी_lock);
		वापस 1;
	पूर्ण

	eb = (काष्ठा extent_buffer *)page->निजी;
	BUG_ON(!eb);

	/*
	 * This is a little awful but should be ok, we need to make sure that
	 * the eb करोesn't disappear out from under us while we're looking at
	 * this page.
	 */
	spin_lock(&eb->refs_lock);
	अगर (atomic_पढ़ो(&eb->refs) != 1 || extent_buffer_under_io(eb)) अणु
		spin_unlock(&eb->refs_lock);
		spin_unlock(&page->mapping->निजी_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&page->mapping->निजी_lock);

	/*
	 * If tree ref isn't set then we know the ref on this eb is a real ref,
	 * so just वापस, this page will likely be मुक्तd soon anyway.
	 */
	अगर (!test_and_clear_bit(EXTENT_BUFFER_TREE_REF, &eb->bflags)) अणु
		spin_unlock(&eb->refs_lock);
		वापस 0;
	पूर्ण

	वापस release_extent_buffer(eb);
पूर्ण

/*
 * btrfs_पढ़ोahead_tree_block - attempt to पढ़ोahead a child block
 * @fs_info:	the fs_info
 * @bytenr:	bytenr to पढ़ो
 * @owner_root: objectid of the root that owns this eb
 * @gen:	generation क्रम the uptodate check, can be 0
 * @level:	level क्रम the eb
 *
 * Attempt to पढ़ोahead a tree block at @bytenr.  If @gen is 0 then we करो a
 * normal uptodate check of the eb, without checking the generation.  If we have
 * to पढ़ो the block we will not block on anything.
 */
व्योम btrfs_पढ़ोahead_tree_block(काष्ठा btrfs_fs_info *fs_info,
				u64 bytenr, u64 owner_root, u64 gen, पूर्णांक level)
अणु
	काष्ठा extent_buffer *eb;
	पूर्णांक ret;

	eb = btrfs_find_create_tree_block(fs_info, bytenr, owner_root, level);
	अगर (IS_ERR(eb))
		वापस;

	अगर (btrfs_buffer_uptodate(eb, gen, 1)) अणु
		मुक्त_extent_buffer(eb);
		वापस;
	पूर्ण

	ret = पढ़ो_extent_buffer_pages(eb, WAIT_NONE, 0);
	अगर (ret < 0)
		मुक्त_extent_buffer_stale(eb);
	अन्यथा
		मुक्त_extent_buffer(eb);
पूर्ण

/*
 * btrfs_पढ़ोahead_node_child - पढ़ोahead a node's child block
 * @node:	parent node we're पढ़ोing from
 * @slot:	slot in the parent node क्रम the child we want to पढ़ो
 *
 * A helper क्रम btrfs_पढ़ोahead_tree_block, we simply पढ़ो the bytenr poपूर्णांकed at
 * the slot in the node provided.
 */
व्योम btrfs_पढ़ोahead_node_child(काष्ठा extent_buffer *node, पूर्णांक slot)
अणु
	btrfs_पढ़ोahead_tree_block(node->fs_info,
				   btrfs_node_blockptr(node, slot),
				   btrfs_header_owner(node),
				   btrfs_node_ptr_generation(node, slot),
				   btrfs_header_level(node) - 1);
पूर्ण
