<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * uptodate.c
 *
 * Tracking the up-to-date-ness of a local buffer_head with respect to
 * the cluster.
 *
 * Copyright (C) 2002, 2004, 2005 Oracle.  All rights reserved.
 *
 * Standard buffer head caching flags (uptodate, etc) are insufficient
 * in a clustered environment - a buffer may be marked up to date on
 * our local node but could have been modअगरied by another cluster
 * member. As a result an additional (and perक्रमmant) caching scheme
 * is required. A further requirement is that we consume as little
 * memory as possible - we never pin buffer_head काष्ठाures in order
 * to cache them.
 *
 * We track the existence of up to date buffers on the inodes which
 * are associated with them. Because we करोn't want to pin
 * buffer_heads, this is only a (strong) hपूर्णांक and several other checks
 * are made in the I/O path to ensure that we करोn't use a stale or
 * invalid buffer without going to disk:
 *	- buffer_jbd is used liberally - अगर a bh is in the journal on
 *	  this node then it *must* be up to date.
 *	- the standard buffer_uptodate() macro is used to detect buffers
 *	  which may be invalid (even अगर we have an up to date tracking
 * 	  item क्रम them)
 *
 * For a full understanding of how this code works together, one
 * should पढ़ो the callers in dlmglue.c, the I/O functions in
 * buffer_head_io.c and ocfs2_journal_access in journal.c
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/rbtree.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "inode.h"
#समावेश "uptodate.h"
#समावेश "ocfs2_trace.h"

काष्ठा ocfs2_meta_cache_item अणु
	काष्ठा rb_node	c_node;
	sector_t	c_block;
पूर्ण;

अटल काष्ठा kmem_cache *ocfs2_uptodate_cachep;

u64 ocfs2_metadata_cache_owner(काष्ठा ocfs2_caching_info *ci)
अणु
	BUG_ON(!ci || !ci->ci_ops);

	वापस ci->ci_ops->co_owner(ci);
पूर्ण

काष्ठा super_block *ocfs2_metadata_cache_get_super(काष्ठा ocfs2_caching_info *ci)
अणु
	BUG_ON(!ci || !ci->ci_ops);

	वापस ci->ci_ops->co_get_super(ci);
पूर्ण

अटल व्योम ocfs2_metadata_cache_lock(काष्ठा ocfs2_caching_info *ci)
अणु
	BUG_ON(!ci || !ci->ci_ops);

	ci->ci_ops->co_cache_lock(ci);
पूर्ण

अटल व्योम ocfs2_metadata_cache_unlock(काष्ठा ocfs2_caching_info *ci)
अणु
	BUG_ON(!ci || !ci->ci_ops);

	ci->ci_ops->co_cache_unlock(ci);
पूर्ण

व्योम ocfs2_metadata_cache_io_lock(काष्ठा ocfs2_caching_info *ci)
अणु
	BUG_ON(!ci || !ci->ci_ops);

	ci->ci_ops->co_io_lock(ci);
पूर्ण

व्योम ocfs2_metadata_cache_io_unlock(काष्ठा ocfs2_caching_info *ci)
अणु
	BUG_ON(!ci || !ci->ci_ops);

	ci->ci_ops->co_io_unlock(ci);
पूर्ण


अटल व्योम ocfs2_metadata_cache_reset(काष्ठा ocfs2_caching_info *ci,
				       पूर्णांक clear)
अणु
	ci->ci_flags |= OCFS2_CACHE_FL_INLINE;
	ci->ci_num_cached = 0;

	अगर (clear) अणु
		ci->ci_created_trans = 0;
		ci->ci_last_trans = 0;
	पूर्ण
पूर्ण

व्योम ocfs2_metadata_cache_init(काष्ठा ocfs2_caching_info *ci,
			       स्थिर काष्ठा ocfs2_caching_operations *ops)
अणु
	BUG_ON(!ops);

	ci->ci_ops = ops;
	ocfs2_metadata_cache_reset(ci, 1);
पूर्ण

व्योम ocfs2_metadata_cache_निकास(काष्ठा ocfs2_caching_info *ci)
अणु
	ocfs2_metadata_cache_purge(ci);
	ocfs2_metadata_cache_reset(ci, 1);
पूर्ण


/* No lock taken here as 'root' is not expected to be visible to other
 * processes. */
अटल अचिन्हित पूर्णांक ocfs2_purge_copied_metadata_tree(काष्ठा rb_root *root)
अणु
	अचिन्हित पूर्णांक purged = 0;
	काष्ठा rb_node *node;
	काष्ठा ocfs2_meta_cache_item *item;

	जबतक ((node = rb_last(root)) != शून्य) अणु
		item = rb_entry(node, काष्ठा ocfs2_meta_cache_item, c_node);

		trace_ocfs2_purge_copied_metadata_tree(
					(अचिन्हित दीर्घ दीर्घ) item->c_block);

		rb_erase(&item->c_node, root);
		kmem_cache_मुक्त(ocfs2_uptodate_cachep, item);

		purged++;
	पूर्ण
	वापस purged;
पूर्ण

/* Called from locking and called from ocfs2_clear_inode. Dump the
 * cache क्रम a given inode.
 *
 * This function is a few more lines दीर्घer than necessary due to some
 * accounting करोne here, but I think it's worth tracking करोwn those
 * bugs sooner -- Mark */
व्योम ocfs2_metadata_cache_purge(काष्ठा ocfs2_caching_info *ci)
अणु
	अचिन्हित पूर्णांक tree, to_purge, purged;
	काष्ठा rb_root root = RB_ROOT;

	BUG_ON(!ci || !ci->ci_ops);

	ocfs2_metadata_cache_lock(ci);
	tree = !(ci->ci_flags & OCFS2_CACHE_FL_INLINE);
	to_purge = ci->ci_num_cached;

	trace_ocfs2_metadata_cache_purge(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		to_purge, tree);

	/* If we're a tree, save off the root so that we can safely
	 * initialize the cache. We करो the work to मुक्त tree members
	 * without the spinlock. */
	अगर (tree)
		root = ci->ci_cache.ci_tree;

	ocfs2_metadata_cache_reset(ci, 0);
	ocfs2_metadata_cache_unlock(ci);

	purged = ocfs2_purge_copied_metadata_tree(&root);
	/* If possible, track the number wiped so that we can more
	 * easily detect counting errors. Unक्रमtunately, this is only
	 * meaningful क्रम trees. */
	अगर (tree && purged != to_purge)
		mlog(ML_ERROR, "Owner %llu, count = %u, purged = %u\n",
		     (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		     to_purge, purged);
पूर्ण

/* Returns the index in the cache array, -1 अगर not found.
 * Requires ip_lock. */
अटल पूर्णांक ocfs2_search_cache_array(काष्ठा ocfs2_caching_info *ci,
				    sector_t item)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ci->ci_num_cached; i++) अणु
		अगर (item == ci->ci_cache.ci_array[i])
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/* Returns the cache item अगर found, otherwise शून्य.
 * Requires ip_lock. */
अटल काष्ठा ocfs2_meta_cache_item *
ocfs2_search_cache_tree(काष्ठा ocfs2_caching_info *ci,
			sector_t block)
अणु
	काष्ठा rb_node * n = ci->ci_cache.ci_tree.rb_node;
	काष्ठा ocfs2_meta_cache_item *item = शून्य;

	जबतक (n) अणु
		item = rb_entry(n, काष्ठा ocfs2_meta_cache_item, c_node);

		अगर (block < item->c_block)
			n = n->rb_left;
		अन्यथा अगर (block > item->c_block)
			n = n->rb_right;
		अन्यथा
			वापस item;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ocfs2_buffer_cached(काष्ठा ocfs2_caching_info *ci,
			       काष्ठा buffer_head *bh)
अणु
	पूर्णांक index = -1;
	काष्ठा ocfs2_meta_cache_item *item = शून्य;

	ocfs2_metadata_cache_lock(ci);

	trace_ocfs2_buffer_cached_begin(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ) bh->b_blocknr,
		!!(ci->ci_flags & OCFS2_CACHE_FL_INLINE));

	अगर (ci->ci_flags & OCFS2_CACHE_FL_INLINE)
		index = ocfs2_search_cache_array(ci, bh->b_blocknr);
	अन्यथा
		item = ocfs2_search_cache_tree(ci, bh->b_blocknr);

	ocfs2_metadata_cache_unlock(ci);

	trace_ocfs2_buffer_cached_end(index, item);

	वापस (index != -1) || (item != शून्य);
पूर्ण

/* Warning: even अगर it वापसs true, this करोes *not* guarantee that
 * the block is stored in our inode metadata cache.
 *
 * This can be called under lock_buffer()
 */
पूर्णांक ocfs2_buffer_uptodate(काष्ठा ocfs2_caching_info *ci,
			  काष्ठा buffer_head *bh)
अणु
	/* Doesn't matter if the bh is in our cache or not -- if it's
	 * not marked uptodate then we know it can't have correct
	 * data. */
	अगर (!buffer_uptodate(bh))
		वापस 0;

	/* OCFS2 करोes not allow multiple nodes to be changing the same
	 * block at the same समय. */
	अगर (buffer_jbd(bh))
		वापस 1;

	/* Ok, locally the buffer is marked as up to date, now search
	 * our cache to see अगर we can trust that. */
	वापस ocfs2_buffer_cached(ci, bh);
पूर्ण

/*
 * Determine whether a buffer is currently out on a पढ़ो-ahead request.
 * ci_io_sem should be held to serialize submitters with the logic here.
 */
पूर्णांक ocfs2_buffer_पढ़ो_ahead(काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh)
अणु
	वापस buffer_locked(bh) && ocfs2_buffer_cached(ci, bh);
पूर्ण

/* Requires ip_lock */
अटल व्योम ocfs2_append_cache_array(काष्ठा ocfs2_caching_info *ci,
				     sector_t block)
अणु
	BUG_ON(ci->ci_num_cached >= OCFS2_CACHE_INFO_MAX_ARRAY);

	trace_ocfs2_append_cache_array(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)block, ci->ci_num_cached);

	ci->ci_cache.ci_array[ci->ci_num_cached] = block;
	ci->ci_num_cached++;
पूर्ण

/* By now the caller should have checked that the item करोes *not*
 * exist in the tree.
 * Requires ip_lock. */
अटल व्योम __ocfs2_insert_cache_tree(काष्ठा ocfs2_caching_info *ci,
				      काष्ठा ocfs2_meta_cache_item *new)
अणु
	sector_t block = new->c_block;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rb_node **p = &ci->ci_cache.ci_tree.rb_node;
	काष्ठा ocfs2_meta_cache_item *पंचांगp;

	trace_ocfs2_insert_cache_tree(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)block, ci->ci_num_cached);

	जबतक(*p) अणु
		parent = *p;

		पंचांगp = rb_entry(parent, काष्ठा ocfs2_meta_cache_item, c_node);

		अगर (block < पंचांगp->c_block)
			p = &(*p)->rb_left;
		अन्यथा अगर (block > पंचांगp->c_block)
			p = &(*p)->rb_right;
		अन्यथा अणु
			/* This should never happen! */
			mlog(ML_ERROR, "Duplicate block %llu cached!\n",
			     (अचिन्हित दीर्घ दीर्घ) block);
			BUG();
		पूर्ण
	पूर्ण

	rb_link_node(&new->c_node, parent, p);
	rb_insert_color(&new->c_node, &ci->ci_cache.ci_tree);
	ci->ci_num_cached++;
पूर्ण

/* co_cache_lock() must be held */
अटल अंतरभूत पूर्णांक ocfs2_insert_can_use_array(काष्ठा ocfs2_caching_info *ci)
अणु
	वापस (ci->ci_flags & OCFS2_CACHE_FL_INLINE) &&
		(ci->ci_num_cached < OCFS2_CACHE_INFO_MAX_ARRAY);
पूर्ण

/* tree should be exactly OCFS2_CACHE_INFO_MAX_ARRAY wide. शून्य the
 * poपूर्णांकers in tree after we use them - this allows caller to detect
 * when to मुक्त in हाल of error.
 *
 * The co_cache_lock() must be held. */
अटल व्योम ocfs2_expand_cache(काष्ठा ocfs2_caching_info *ci,
			       काष्ठा ocfs2_meta_cache_item **tree)
अणु
	पूर्णांक i;

	mlog_bug_on_msg(ci->ci_num_cached != OCFS2_CACHE_INFO_MAX_ARRAY,
			"Owner %llu, num cached = %u, should be %u\n",
			(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
			ci->ci_num_cached, OCFS2_CACHE_INFO_MAX_ARRAY);
	mlog_bug_on_msg(!(ci->ci_flags & OCFS2_CACHE_FL_INLINE),
			"Owner %llu not marked as inline anymore!\n",
			(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci));

	/* Be careful to initialize the tree members *first* because
	 * once the ci_tree is used, the array is junk... */
	क्रम (i = 0; i < OCFS2_CACHE_INFO_MAX_ARRAY; i++)
		tree[i]->c_block = ci->ci_cache.ci_array[i];

	ci->ci_flags &= ~OCFS2_CACHE_FL_INLINE;
	ci->ci_cache.ci_tree = RB_ROOT;
	/* this will be set again by __ocfs2_insert_cache_tree */
	ci->ci_num_cached = 0;

	क्रम (i = 0; i < OCFS2_CACHE_INFO_MAX_ARRAY; i++) अणु
		__ocfs2_insert_cache_tree(ci, tree[i]);
		tree[i] = शून्य;
	पूर्ण

	trace_ocfs2_expand_cache(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		ci->ci_flags, ci->ci_num_cached);
पूर्ण

/* Slow path function - memory allocation is necessary. See the
 * comment above ocfs2_set_buffer_uptodate क्रम more inक्रमmation. */
अटल व्योम __ocfs2_set_buffer_uptodate(काष्ठा ocfs2_caching_info *ci,
					sector_t block,
					पूर्णांक expand_tree)
अणु
	पूर्णांक i;
	काष्ठा ocfs2_meta_cache_item *new = शून्य;
	काष्ठा ocfs2_meta_cache_item *tree[OCFS2_CACHE_INFO_MAX_ARRAY] =
		अणु शून्य, पूर्ण;

	trace_ocfs2_set_buffer_uptodate(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)block, expand_tree);

	new = kmem_cache_alloc(ocfs2_uptodate_cachep, GFP_NOFS);
	अगर (!new) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		वापस;
	पूर्ण
	new->c_block = block;

	अगर (expand_tree) अणु
		/* Do *not* allocate an array here - the removal code
		 * has no way of tracking that. */
		क्रम (i = 0; i < OCFS2_CACHE_INFO_MAX_ARRAY; i++) अणु
			tree[i] = kmem_cache_alloc(ocfs2_uptodate_cachep,
						   GFP_NOFS);
			अगर (!tree[i]) अणु
				mlog_त्रुटि_सं(-ENOMEM);
				जाओ out_मुक्त;
			पूर्ण

			/* These are initialized in ocfs2_expand_cache! */
		पूर्ण
	पूर्ण

	ocfs2_metadata_cache_lock(ci);
	अगर (ocfs2_insert_can_use_array(ci)) अणु
		/* Ok, items were हटाओd from the cache in between
		 * locks. Detect this and revert back to the fast path */
		ocfs2_append_cache_array(ci, block);
		ocfs2_metadata_cache_unlock(ci);
		जाओ out_मुक्त;
	पूर्ण

	अगर (expand_tree)
		ocfs2_expand_cache(ci, tree);

	__ocfs2_insert_cache_tree(ci, new);
	ocfs2_metadata_cache_unlock(ci);

	new = शून्य;
out_मुक्त:
	अगर (new)
		kmem_cache_मुक्त(ocfs2_uptodate_cachep, new);

	/* If these were used, then ocfs2_expand_cache re-set them to
	 * शून्य क्रम us. */
	अगर (tree[0]) अणु
		क्रम (i = 0; i < OCFS2_CACHE_INFO_MAX_ARRAY; i++)
			अगर (tree[i])
				kmem_cache_मुक्त(ocfs2_uptodate_cachep,
						tree[i]);
	पूर्ण
पूर्ण

/* Item insertion is guarded by co_io_lock(), so the insertion path takes
 * advantage of this by not rechecking क्रम a duplicate insert during
 * the slow हाल. Additionally, अगर the cache needs to be bumped up to
 * a tree, the code will not recheck after acquiring the lock --
 * multiple paths cannot be expanding to a tree at the same समय.
 *
 * The slow path takes पूर्णांकo account that items can be हटाओd
 * (including the whole tree wiped and reset) when this process it out
 * allocating memory. In those हालs, it reverts back to the fast
 * path.
 *
 * Note that this function may actually fail to insert the block अगर
 * memory cannot be allocated. This is not fatal however (but may
 * result in a perक्रमmance penalty)
 *
 * Readahead buffers can be passed in here beक्रमe the I/O request is
 * completed.
 */
व्योम ocfs2_set_buffer_uptodate(काष्ठा ocfs2_caching_info *ci,
			       काष्ठा buffer_head *bh)
अणु
	पूर्णांक expand;

	/* The block may very well exist in our cache alपढ़ोy, so aव्योम
	 * करोing any more work in that हाल. */
	अगर (ocfs2_buffer_cached(ci, bh))
		वापस;

	trace_ocfs2_set_buffer_uptodate_begin(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	/* No need to recheck under spinlock - insertion is guarded by
	 * co_io_lock() */
	ocfs2_metadata_cache_lock(ci);
	अगर (ocfs2_insert_can_use_array(ci)) अणु
		/* Fast हाल - it's an array and there's a मुक्त
		 * spot. */
		ocfs2_append_cache_array(ci, bh->b_blocknr);
		ocfs2_metadata_cache_unlock(ci);
		वापस;
	पूर्ण

	expand = 0;
	अगर (ci->ci_flags & OCFS2_CACHE_FL_INLINE) अणु
		/* We need to bump things up to a tree. */
		expand = 1;
	पूर्ण
	ocfs2_metadata_cache_unlock(ci);

	__ocfs2_set_buffer_uptodate(ci, bh->b_blocknr, expand);
पूर्ण

/* Called against a newly allocated buffer. Most likely nobody should
 * be able to पढ़ो this sort of metadata जबतक it's still being
 * allocated, but this is careful to take co_io_lock() anyway. */
व्योम ocfs2_set_new_buffer_uptodate(काष्ठा ocfs2_caching_info *ci,
				   काष्ठा buffer_head *bh)
अणु
	/* This should definitely *not* exist in our cache */
	BUG_ON(ocfs2_buffer_cached(ci, bh));

	set_buffer_uptodate(bh);

	ocfs2_metadata_cache_io_lock(ci);
	ocfs2_set_buffer_uptodate(ci, bh);
	ocfs2_metadata_cache_io_unlock(ci);
पूर्ण

/* Requires ip_lock. */
अटल व्योम ocfs2_हटाओ_metadata_array(काष्ठा ocfs2_caching_info *ci,
					पूर्णांक index)
अणु
	sector_t *array = ci->ci_cache.ci_array;
	पूर्णांक bytes;

	BUG_ON(index < 0 || index >= OCFS2_CACHE_INFO_MAX_ARRAY);
	BUG_ON(index >= ci->ci_num_cached);
	BUG_ON(!ci->ci_num_cached);

	trace_ocfs2_हटाओ_metadata_array(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		index, ci->ci_num_cached);

	ci->ci_num_cached--;

	/* करोn't need to copy अगर the array is now empty, or अगर we
	 * हटाओd at the tail */
	अगर (ci->ci_num_cached && index < ci->ci_num_cached) अणु
		bytes = माप(sector_t) * (ci->ci_num_cached - index);
		स_हटाओ(&array[index], &array[index + 1], bytes);
	पूर्ण
पूर्ण

/* Requires ip_lock. */
अटल व्योम ocfs2_हटाओ_metadata_tree(काष्ठा ocfs2_caching_info *ci,
				       काष्ठा ocfs2_meta_cache_item *item)
अणु
	trace_ocfs2_हटाओ_metadata_tree(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)item->c_block);

	rb_erase(&item->c_node, &ci->ci_cache.ci_tree);
	ci->ci_num_cached--;
पूर्ण

अटल व्योम ocfs2_हटाओ_block_from_cache(काष्ठा ocfs2_caching_info *ci,
					  sector_t block)
अणु
	पूर्णांक index;
	काष्ठा ocfs2_meta_cache_item *item = शून्य;

	ocfs2_metadata_cache_lock(ci);
	trace_ocfs2_हटाओ_block_from_cache(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ) block, ci->ci_num_cached,
		ci->ci_flags);

	अगर (ci->ci_flags & OCFS2_CACHE_FL_INLINE) अणु
		index = ocfs2_search_cache_array(ci, block);
		अगर (index != -1)
			ocfs2_हटाओ_metadata_array(ci, index);
	पूर्ण अन्यथा अणु
		item = ocfs2_search_cache_tree(ci, block);
		अगर (item)
			ocfs2_हटाओ_metadata_tree(ci, item);
	पूर्ण
	ocfs2_metadata_cache_unlock(ci);

	अगर (item)
		kmem_cache_मुक्त(ocfs2_uptodate_cachep, item);
पूर्ण

/*
 * Called when we हटाओ a chunk of metadata from an inode. We करोn't
 * bother reverting things to an अंतरभूतd array in the हाल of a हटाओ
 * which moves us back under the limit.
 */
व्योम ocfs2_हटाओ_from_cache(काष्ठा ocfs2_caching_info *ci,
			     काष्ठा buffer_head *bh)
अणु
	sector_t block = bh->b_blocknr;

	ocfs2_हटाओ_block_from_cache(ci, block);
पूर्ण

/* Called when we हटाओ xattr clusters from an inode. */
व्योम ocfs2_हटाओ_xattr_clusters_from_cache(काष्ठा ocfs2_caching_info *ci,
					    sector_t block,
					    u32 c_len)
अणु
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(ci);
	अचिन्हित पूर्णांक i, b_len = ocfs2_clusters_to_blocks(sb, 1) * c_len;

	क्रम (i = 0; i < b_len; i++, block++)
		ocfs2_हटाओ_block_from_cache(ci, block);
पूर्ण

पूर्णांक __init init_ocfs2_uptodate_cache(व्योम)
अणु
	ocfs2_uptodate_cachep = kmem_cache_create("ocfs2_uptodate",
				  माप(काष्ठा ocfs2_meta_cache_item),
				  0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ocfs2_uptodate_cachep)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम निकास_ocfs2_uptodate_cache(व्योम)
अणु
	kmem_cache_destroy(ocfs2_uptodate_cachep);
पूर्ण
