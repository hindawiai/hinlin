<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "block-group.h"
#समावेश "space-info.h"
#समावेश "disk-io.h"
#समावेश "free-space-cache.h"
#समावेश "free-space-tree.h"
#समावेश "volumes.h"
#समावेश "transaction.h"
#समावेश "ref-verify.h"
#समावेश "sysfs.h"
#समावेश "tree-log.h"
#समावेश "delalloc-space.h"
#समावेश "discard.h"
#समावेश "raid56.h"
#समावेश "zoned.h"

/*
 * Return target flags in extended क्रमmat or 0 अगर restripe क्रम this chunk_type
 * is not in progress
 *
 * Should be called with balance_lock held
 */
अटल u64 get_restripe_target(काष्ठा btrfs_fs_info *fs_info, u64 flags)
अणु
	काष्ठा btrfs_balance_control *bctl = fs_info->balance_ctl;
	u64 target = 0;

	अगर (!bctl)
		वापस 0;

	अगर (flags & BTRFS_BLOCK_GROUP_DATA &&
	    bctl->data.flags & BTRFS_BALANCE_ARGS_CONVERT) अणु
		target = BTRFS_BLOCK_GROUP_DATA | bctl->data.target;
	पूर्ण अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_SYSTEM &&
		   bctl->sys.flags & BTRFS_BALANCE_ARGS_CONVERT) अणु
		target = BTRFS_BLOCK_GROUP_SYSTEM | bctl->sys.target;
	पूर्ण अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_METADATA &&
		   bctl->meta.flags & BTRFS_BALANCE_ARGS_CONVERT) अणु
		target = BTRFS_BLOCK_GROUP_METADATA | bctl->meta.target;
	पूर्ण

	वापस target;
पूर्ण

/*
 * @flags: available profiles in extended क्रमmat (see ctree.h)
 *
 * Return reduced profile in chunk क्रमmat.  If profile changing is in progress
 * (either running or छोड़ोd) picks the target profile (अगर it's alपढ़ोy
 * available), otherwise falls back to plain reducing.
 */
अटल u64 btrfs_reduce_alloc_profile(काष्ठा btrfs_fs_info *fs_info, u64 flags)
अणु
	u64 num_devices = fs_info->fs_devices->rw_devices;
	u64 target;
	u64 raid_type;
	u64 allowed = 0;

	/*
	 * See अगर restripe क्रम this chunk_type is in progress, अगर so try to
	 * reduce to the target profile
	 */
	spin_lock(&fs_info->balance_lock);
	target = get_restripe_target(fs_info, flags);
	अगर (target) अणु
		spin_unlock(&fs_info->balance_lock);
		वापस extended_to_chunk(target);
	पूर्ण
	spin_unlock(&fs_info->balance_lock);

	/* First, mask out the RAID levels which aren't possible */
	क्रम (raid_type = 0; raid_type < BTRFS_NR_RAID_TYPES; raid_type++) अणु
		अगर (num_devices >= btrfs_raid_array[raid_type].devs_min)
			allowed |= btrfs_raid_array[raid_type].bg_flag;
	पूर्ण
	allowed &= flags;

	अगर (allowed & BTRFS_BLOCK_GROUP_RAID6)
		allowed = BTRFS_BLOCK_GROUP_RAID6;
	अन्यथा अगर (allowed & BTRFS_BLOCK_GROUP_RAID5)
		allowed = BTRFS_BLOCK_GROUP_RAID5;
	अन्यथा अगर (allowed & BTRFS_BLOCK_GROUP_RAID10)
		allowed = BTRFS_BLOCK_GROUP_RAID10;
	अन्यथा अगर (allowed & BTRFS_BLOCK_GROUP_RAID1)
		allowed = BTRFS_BLOCK_GROUP_RAID1;
	अन्यथा अगर (allowed & BTRFS_BLOCK_GROUP_RAID0)
		allowed = BTRFS_BLOCK_GROUP_RAID0;

	flags &= ~BTRFS_BLOCK_GROUP_PROखाता_MASK;

	वापस extended_to_chunk(flags | allowed);
पूर्ण

u64 btrfs_get_alloc_profile(काष्ठा btrfs_fs_info *fs_info, u64 orig_flags)
अणु
	अचिन्हित seq;
	u64 flags;

	करो अणु
		flags = orig_flags;
		seq = पढ़ो_seqbegin(&fs_info->profiles_lock);

		अगर (flags & BTRFS_BLOCK_GROUP_DATA)
			flags |= fs_info->avail_data_alloc_bits;
		अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_SYSTEM)
			flags |= fs_info->avail_प्रणाली_alloc_bits;
		अन्यथा अगर (flags & BTRFS_BLOCK_GROUP_METADATA)
			flags |= fs_info->avail_metadata_alloc_bits;
	पूर्ण जबतक (पढ़ो_seqretry(&fs_info->profiles_lock, seq));

	वापस btrfs_reduce_alloc_profile(fs_info, flags);
पूर्ण

व्योम btrfs_get_block_group(काष्ठा btrfs_block_group *cache)
अणु
	refcount_inc(&cache->refs);
पूर्ण

व्योम btrfs_put_block_group(काष्ठा btrfs_block_group *cache)
अणु
	अगर (refcount_dec_and_test(&cache->refs)) अणु
		WARN_ON(cache->pinned > 0);
		WARN_ON(cache->reserved > 0);

		/*
		 * A block_group shouldn't be on the discard_list anymore.
		 * Remove the block_group from the discard_list to prevent us
		 * from causing a panic due to शून्य poपूर्णांकer dereference.
		 */
		अगर (WARN_ON(!list_empty(&cache->discard_list)))
			btrfs_discard_cancel_work(&cache->fs_info->discard_ctl,
						  cache);

		/*
		 * If not empty, someone is still holding mutex of
		 * full_stripe_lock, which can only be released by caller.
		 * And it will definitely cause use-after-मुक्त when caller
		 * tries to release full stripe lock.
		 *
		 * No better way to resolve, but only to warn.
		 */
		WARN_ON(!RB_EMPTY_ROOT(&cache->full_stripe_locks_root.root));
		kमुक्त(cache->मुक्त_space_ctl);
		kमुक्त(cache);
	पूर्ण
पूर्ण

/*
 * This adds the block group to the fs_info rb tree क्रम the block group cache
 */
अटल पूर्णांक btrfs_add_block_group_cache(काष्ठा btrfs_fs_info *info,
				       काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा btrfs_block_group *cache;

	ASSERT(block_group->length != 0);

	spin_lock(&info->block_group_cache_lock);
	p = &info->block_group_cache_tree.rb_node;

	जबतक (*p) अणु
		parent = *p;
		cache = rb_entry(parent, काष्ठा btrfs_block_group, cache_node);
		अगर (block_group->start < cache->start) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (block_group->start > cache->start) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			spin_unlock(&info->block_group_cache_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	rb_link_node(&block_group->cache_node, parent, p);
	rb_insert_color(&block_group->cache_node,
			&info->block_group_cache_tree);

	अगर (info->first_logical_byte > block_group->start)
		info->first_logical_byte = block_group->start;

	spin_unlock(&info->block_group_cache_lock);

	वापस 0;
पूर्ण

/*
 * This will वापस the block group at or after bytenr अगर contains is 0, अन्यथा
 * it will वापस the block group that contains the bytenr
 */
अटल काष्ठा btrfs_block_group *block_group_cache_tree_search(
		काष्ठा btrfs_fs_info *info, u64 bytenr, पूर्णांक contains)
अणु
	काष्ठा btrfs_block_group *cache, *ret = शून्य;
	काष्ठा rb_node *n;
	u64 end, start;

	spin_lock(&info->block_group_cache_lock);
	n = info->block_group_cache_tree.rb_node;

	जबतक (n) अणु
		cache = rb_entry(n, काष्ठा btrfs_block_group, cache_node);
		end = cache->start + cache->length - 1;
		start = cache->start;

		अगर (bytenr < start) अणु
			अगर (!contains && (!ret || start < ret->start))
				ret = cache;
			n = n->rb_left;
		पूर्ण अन्यथा अगर (bytenr > start) अणु
			अगर (contains && bytenr <= end) अणु
				ret = cache;
				अवरोध;
			पूर्ण
			n = n->rb_right;
		पूर्ण अन्यथा अणु
			ret = cache;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		btrfs_get_block_group(ret);
		अगर (bytenr == 0 && info->first_logical_byte > ret->start)
			info->first_logical_byte = ret->start;
	पूर्ण
	spin_unlock(&info->block_group_cache_lock);

	वापस ret;
पूर्ण

/*
 * Return the block group that starts at or after bytenr
 */
काष्ठा btrfs_block_group *btrfs_lookup_first_block_group(
		काष्ठा btrfs_fs_info *info, u64 bytenr)
अणु
	वापस block_group_cache_tree_search(info, bytenr, 0);
पूर्ण

/*
 * Return the block group that contains the given bytenr
 */
काष्ठा btrfs_block_group *btrfs_lookup_block_group(
		काष्ठा btrfs_fs_info *info, u64 bytenr)
अणु
	वापस block_group_cache_tree_search(info, bytenr, 1);
पूर्ण

काष्ठा btrfs_block_group *btrfs_next_block_group(
		काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा rb_node *node;

	spin_lock(&fs_info->block_group_cache_lock);

	/* If our block group was हटाओd, we need a full search. */
	अगर (RB_EMPTY_NODE(&cache->cache_node)) अणु
		स्थिर u64 next_bytenr = cache->start + cache->length;

		spin_unlock(&fs_info->block_group_cache_lock);
		btrfs_put_block_group(cache);
		cache = btrfs_lookup_first_block_group(fs_info, next_bytenr); वापस cache;
	पूर्ण
	node = rb_next(&cache->cache_node);
	btrfs_put_block_group(cache);
	अगर (node) अणु
		cache = rb_entry(node, काष्ठा btrfs_block_group, cache_node);
		btrfs_get_block_group(cache);
	पूर्ण अन्यथा
		cache = शून्य;
	spin_unlock(&fs_info->block_group_cache_lock);
	वापस cache;
पूर्ण

bool btrfs_inc_nocow_ग_लिखोrs(काष्ठा btrfs_fs_info *fs_info, u64 bytenr)
अणु
	काष्ठा btrfs_block_group *bg;
	bool ret = true;

	bg = btrfs_lookup_block_group(fs_info, bytenr);
	अगर (!bg)
		वापस false;

	spin_lock(&bg->lock);
	अगर (bg->ro)
		ret = false;
	अन्यथा
		atomic_inc(&bg->nocow_ग_लिखोrs);
	spin_unlock(&bg->lock);

	/* No put on block group, करोne by btrfs_dec_nocow_ग_लिखोrs */
	अगर (!ret)
		btrfs_put_block_group(bg);

	वापस ret;
पूर्ण

व्योम btrfs_dec_nocow_ग_लिखोrs(काष्ठा btrfs_fs_info *fs_info, u64 bytenr)
अणु
	काष्ठा btrfs_block_group *bg;

	bg = btrfs_lookup_block_group(fs_info, bytenr);
	ASSERT(bg);
	अगर (atomic_dec_and_test(&bg->nocow_ग_लिखोrs))
		wake_up_var(&bg->nocow_ग_लिखोrs);
	/*
	 * Once क्रम our lookup and once क्रम the lookup करोne by a previous call
	 * to btrfs_inc_nocow_ग_लिखोrs()
	 */
	btrfs_put_block_group(bg);
	btrfs_put_block_group(bg);
पूर्ण

व्योम btrfs_रुको_nocow_ग_लिखोrs(काष्ठा btrfs_block_group *bg)
अणु
	रुको_var_event(&bg->nocow_ग_लिखोrs, !atomic_पढ़ो(&bg->nocow_ग_लिखोrs));
पूर्ण

व्योम btrfs_dec_block_group_reservations(काष्ठा btrfs_fs_info *fs_info,
					स्थिर u64 start)
अणु
	काष्ठा btrfs_block_group *bg;

	bg = btrfs_lookup_block_group(fs_info, start);
	ASSERT(bg);
	अगर (atomic_dec_and_test(&bg->reservations))
		wake_up_var(&bg->reservations);
	btrfs_put_block_group(bg);
पूर्ण

व्योम btrfs_रुको_block_group_reservations(काष्ठा btrfs_block_group *bg)
अणु
	काष्ठा btrfs_space_info *space_info = bg->space_info;

	ASSERT(bg->ro);

	अगर (!(bg->flags & BTRFS_BLOCK_GROUP_DATA))
		वापस;

	/*
	 * Our block group is पढ़ो only but beक्रमe we set it to पढ़ो only,
	 * some task might have had allocated an extent from it alपढ़ोy, but it
	 * has not yet created a respective ordered extent (and added it to a
	 * root's list of ordered extents).
	 * Thereक्रमe रुको क्रम any task currently allocating extents, since the
	 * block group's reservations counter is incremented जबतक a पढ़ो lock
	 * on the groups' semaphore is held and decremented after releasing
	 * the पढ़ो access on that semaphore and creating the ordered extent.
	 */
	करोwn_ग_लिखो(&space_info->groups_sem);
	up_ग_लिखो(&space_info->groups_sem);

	रुको_var_event(&bg->reservations, !atomic_पढ़ो(&bg->reservations));
पूर्ण

काष्ठा btrfs_caching_control *btrfs_get_caching_control(
		काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_caching_control *ctl;

	spin_lock(&cache->lock);
	अगर (!cache->caching_ctl) अणु
		spin_unlock(&cache->lock);
		वापस शून्य;
	पूर्ण

	ctl = cache->caching_ctl;
	refcount_inc(&ctl->count);
	spin_unlock(&cache->lock);
	वापस ctl;
पूर्ण

व्योम btrfs_put_caching_control(काष्ठा btrfs_caching_control *ctl)
अणु
	अगर (refcount_dec_and_test(&ctl->count))
		kमुक्त(ctl);
पूर्ण

/*
 * When we रुको क्रम progress in the block group caching, its because our
 * allocation attempt failed at least once.  So, we must sleep and let some
 * progress happen beक्रमe we try again.
 *
 * This function will sleep at least once रुकोing क्रम new मुक्त space to show
 * up, and then it will check the block group मुक्त space numbers क्रम our min
 * num_bytes.  Another option is to have it go ahead and look in the rbtree क्रम
 * a मुक्त extent of a given size, but this is a good start.
 *
 * Callers of this must check अगर cache->cached == BTRFS_CACHE_ERROR beक्रमe using
 * any of the inक्रमmation in this block group.
 */
व्योम btrfs_रुको_block_group_cache_progress(काष्ठा btrfs_block_group *cache,
					   u64 num_bytes)
अणु
	काष्ठा btrfs_caching_control *caching_ctl;

	caching_ctl = btrfs_get_caching_control(cache);
	अगर (!caching_ctl)
		वापस;

	रुको_event(caching_ctl->रुको, btrfs_block_group_करोne(cache) ||
		   (cache->मुक्त_space_ctl->मुक्त_space >= num_bytes));

	btrfs_put_caching_control(caching_ctl);
पूर्ण

पूर्णांक btrfs_रुको_block_group_cache_करोne(काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_caching_control *caching_ctl;
	पूर्णांक ret = 0;

	caching_ctl = btrfs_get_caching_control(cache);
	अगर (!caching_ctl)
		वापस (cache->cached == BTRFS_CACHE_ERROR) ? -EIO : 0;

	रुको_event(caching_ctl->रुको, btrfs_block_group_करोne(cache));
	अगर (cache->cached == BTRFS_CACHE_ERROR)
		ret = -EIO;
	btrfs_put_caching_control(caching_ctl);
	वापस ret;
पूर्ण

अटल bool space_cache_v1_करोne(काष्ठा btrfs_block_group *cache)
अणु
	bool ret;

	spin_lock(&cache->lock);
	ret = cache->cached != BTRFS_CACHE_FAST;
	spin_unlock(&cache->lock);

	वापस ret;
पूर्ण

व्योम btrfs_रुको_space_cache_v1_finished(काष्ठा btrfs_block_group *cache,
				काष्ठा btrfs_caching_control *caching_ctl)
अणु
	रुको_event(caching_ctl->रुको, space_cache_v1_करोne(cache));
पूर्ण

#अगर_घोषित CONFIG_BTRFS_DEBUG
अटल व्योम fragment_मुक्त_space(काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	u64 start = block_group->start;
	u64 len = block_group->length;
	u64 chunk = block_group->flags & BTRFS_BLOCK_GROUP_METADATA ?
		fs_info->nodesize : fs_info->sectorsize;
	u64 step = chunk << 1;

	जबतक (len > chunk) अणु
		btrfs_हटाओ_मुक्त_space(block_group, start, chunk);
		start += step;
		अगर (len < step)
			len = 0;
		अन्यथा
			len -= step;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * This is only called by btrfs_cache_block_group, since we could have मुक्तd
 * extents we need to check the pinned_extents क्रम any extents that can't be
 * used yet since their मुक्त space will be released as soon as the transaction
 * commits.
 */
u64 add_new_मुक्त_space(काष्ठा btrfs_block_group *block_group, u64 start, u64 end)
अणु
	काष्ठा btrfs_fs_info *info = block_group->fs_info;
	u64 extent_start, extent_end, size, total_added = 0;
	पूर्णांक ret;

	जबतक (start < end) अणु
		ret = find_first_extent_bit(&info->excluded_extents, start,
					    &extent_start, &extent_end,
					    EXTENT_सूचीTY | EXTENT_UPTODATE,
					    शून्य);
		अगर (ret)
			अवरोध;

		अगर (extent_start <= start) अणु
			start = extent_end + 1;
		पूर्ण अन्यथा अगर (extent_start > start && extent_start < end) अणु
			size = extent_start - start;
			total_added += size;
			ret = btrfs_add_मुक्त_space_async_trimmed(block_group,
								 start, size);
			BUG_ON(ret); /* -ENOMEM or logic error */
			start = extent_end + 1;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (start < end) अणु
		size = end - start;
		total_added += size;
		ret = btrfs_add_मुक्त_space_async_trimmed(block_group, start,
							 size);
		BUG_ON(ret); /* -ENOMEM or logic error */
	पूर्ण

	वापस total_added;
पूर्ण

अटल पूर्णांक load_extent_tree_मुक्त(काष्ठा btrfs_caching_control *caching_ctl)
अणु
	काष्ठा btrfs_block_group *block_group = caching_ctl->block_group;
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_root *extent_root = fs_info->extent_root;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	u64 total_found = 0;
	u64 last = 0;
	u32 nritems;
	पूर्णांक ret;
	bool wakeup = true;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	last = max_t(u64, block_group->start, BTRFS_SUPER_INFO_OFFSET);

#अगर_घोषित CONFIG_BTRFS_DEBUG
	/*
	 * If we're fragmenting we don't want to make anybody think we can
	 * allocate from this block group until we've had a chance to fragment
	 * the मुक्त space.
	 */
	अगर (btrfs_should_fragment_मुक्त_space(block_group))
		wakeup = false;
#पूर्ण_अगर
	/*
	 * We करोn't want to deadlock with somebody trying to allocate a new
	 * extent क्रम the extent root जबतक also trying to search the extent
	 * root to add मुक्त space.  So we skip locking and search the commit
	 * root, since its पढ़ो-only
	 */
	path->skip_locking = 1;
	path->search_commit_root = 1;
	path->पढ़ोa = READA_FORWARD;

	key.objectid = last;
	key.offset = 0;
	key.type = BTRFS_EXTENT_ITEM_KEY;

next:
	ret = btrfs_search_slot(शून्य, extent_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	leaf = path->nodes[0];
	nritems = btrfs_header_nritems(leaf);

	जबतक (1) अणु
		अगर (btrfs_fs_closing(fs_info) > 1) अणु
			last = (u64)-1;
			अवरोध;
		पूर्ण

		अगर (path->slots[0] < nritems) अणु
			btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		पूर्ण अन्यथा अणु
			ret = btrfs_find_next_key(extent_root, path, &key, 0, 0);
			अगर (ret)
				अवरोध;

			अगर (need_resched() ||
			    rwsem_is_contended(&fs_info->commit_root_sem)) अणु
				अगर (wakeup)
					caching_ctl->progress = last;
				btrfs_release_path(path);
				up_पढ़ो(&fs_info->commit_root_sem);
				mutex_unlock(&caching_ctl->mutex);
				cond_resched();
				mutex_lock(&caching_ctl->mutex);
				करोwn_पढ़ो(&fs_info->commit_root_sem);
				जाओ next;
			पूर्ण

			ret = btrfs_next_leaf(extent_root, path);
			अगर (ret < 0)
				जाओ out;
			अगर (ret)
				अवरोध;
			leaf = path->nodes[0];
			nritems = btrfs_header_nritems(leaf);
			जारी;
		पूर्ण

		अगर (key.objectid < last) अणु
			key.objectid = last;
			key.offset = 0;
			key.type = BTRFS_EXTENT_ITEM_KEY;

			अगर (wakeup)
				caching_ctl->progress = last;
			btrfs_release_path(path);
			जाओ next;
		पूर्ण

		अगर (key.objectid < block_group->start) अणु
			path->slots[0]++;
			जारी;
		पूर्ण

		अगर (key.objectid >= block_group->start + block_group->length)
			अवरोध;

		अगर (key.type == BTRFS_EXTENT_ITEM_KEY ||
		    key.type == BTRFS_METADATA_ITEM_KEY) अणु
			total_found += add_new_मुक्त_space(block_group, last,
							  key.objectid);
			अगर (key.type == BTRFS_METADATA_ITEM_KEY)
				last = key.objectid +
					fs_info->nodesize;
			अन्यथा
				last = key.objectid + key.offset;

			अगर (total_found > CACHING_CTL_WAKE_UP) अणु
				total_found = 0;
				अगर (wakeup)
					wake_up(&caching_ctl->रुको);
			पूर्ण
		पूर्ण
		path->slots[0]++;
	पूर्ण
	ret = 0;

	total_found += add_new_मुक्त_space(block_group, last,
				block_group->start + block_group->length);
	caching_ctl->progress = (u64)-1;

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल noअंतरभूत व्योम caching_thपढ़ो(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_caching_control *caching_ctl;
	पूर्णांक ret;

	caching_ctl = container_of(work, काष्ठा btrfs_caching_control, work);
	block_group = caching_ctl->block_group;
	fs_info = block_group->fs_info;

	mutex_lock(&caching_ctl->mutex);
	करोwn_पढ़ो(&fs_info->commit_root_sem);

	अगर (btrfs_test_opt(fs_info, SPACE_CACHE)) अणु
		ret = load_मुक्त_space_cache(block_group);
		अगर (ret == 1) अणु
			ret = 0;
			जाओ करोne;
		पूर्ण

		/*
		 * We failed to load the space cache, set ourselves to
		 * CACHE_STARTED and carry on.
		 */
		spin_lock(&block_group->lock);
		block_group->cached = BTRFS_CACHE_STARTED;
		spin_unlock(&block_group->lock);
		wake_up(&caching_ctl->रुको);
	पूर्ण

	/*
	 * If we are in the transaction that populated the मुक्त space tree we
	 * can't actually cache from the मुक्त space tree as our commit root and
	 * real root are the same, so we could change the contents of the blocks
	 * जबतक caching.  Instead करो the slow caching in this हाल, and after
	 * the transaction has committed we will be safe.
	 */
	अगर (btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE) &&
	    !(test_bit(BTRFS_FS_FREE_SPACE_TREE_UNTRUSTED, &fs_info->flags)))
		ret = load_मुक्त_space_tree(caching_ctl);
	अन्यथा
		ret = load_extent_tree_मुक्त(caching_ctl);
करोne:
	spin_lock(&block_group->lock);
	block_group->caching_ctl = शून्य;
	block_group->cached = ret ? BTRFS_CACHE_ERROR : BTRFS_CACHE_FINISHED;
	spin_unlock(&block_group->lock);

#अगर_घोषित CONFIG_BTRFS_DEBUG
	अगर (btrfs_should_fragment_मुक्त_space(block_group)) अणु
		u64 bytes_used;

		spin_lock(&block_group->space_info->lock);
		spin_lock(&block_group->lock);
		bytes_used = block_group->length - block_group->used;
		block_group->space_info->bytes_used += bytes_used >> 1;
		spin_unlock(&block_group->lock);
		spin_unlock(&block_group->space_info->lock);
		fragment_मुक्त_space(block_group);
	पूर्ण
#पूर्ण_अगर

	caching_ctl->progress = (u64)-1;

	up_पढ़ो(&fs_info->commit_root_sem);
	btrfs_मुक्त_excluded_extents(block_group);
	mutex_unlock(&caching_ctl->mutex);

	wake_up(&caching_ctl->रुको);

	btrfs_put_caching_control(caching_ctl);
	btrfs_put_block_group(block_group);
पूर्ण

पूर्णांक btrfs_cache_block_group(काष्ठा btrfs_block_group *cache, पूर्णांक load_cache_only)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा btrfs_caching_control *caching_ctl = शून्य;
	पूर्णांक ret = 0;

	/* Allocator क्रम zoned fileप्रणालीs करोes not use the cache at all */
	अगर (btrfs_is_zoned(fs_info))
		वापस 0;

	caching_ctl = kzalloc(माप(*caching_ctl), GFP_NOFS);
	अगर (!caching_ctl)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&caching_ctl->list);
	mutex_init(&caching_ctl->mutex);
	init_रुकोqueue_head(&caching_ctl->रुको);
	caching_ctl->block_group = cache;
	caching_ctl->progress = cache->start;
	refcount_set(&caching_ctl->count, 2);
	btrfs_init_work(&caching_ctl->work, caching_thपढ़ो, शून्य, शून्य);

	spin_lock(&cache->lock);
	अगर (cache->cached != BTRFS_CACHE_NO) अणु
		kमुक्त(caching_ctl);

		caching_ctl = cache->caching_ctl;
		अगर (caching_ctl)
			refcount_inc(&caching_ctl->count);
		spin_unlock(&cache->lock);
		जाओ out;
	पूर्ण
	WARN_ON(cache->caching_ctl);
	cache->caching_ctl = caching_ctl;
	अगर (btrfs_test_opt(fs_info, SPACE_CACHE))
		cache->cached = BTRFS_CACHE_FAST;
	अन्यथा
		cache->cached = BTRFS_CACHE_STARTED;
	cache->has_caching_ctl = 1;
	spin_unlock(&cache->lock);

	spin_lock(&fs_info->block_group_cache_lock);
	refcount_inc(&caching_ctl->count);
	list_add_tail(&caching_ctl->list, &fs_info->caching_block_groups);
	spin_unlock(&fs_info->block_group_cache_lock);

	btrfs_get_block_group(cache);

	btrfs_queue_work(fs_info->caching_workers, &caching_ctl->work);
out:
	अगर (load_cache_only && caching_ctl)
		btrfs_रुको_space_cache_v1_finished(cache, caching_ctl);
	अगर (caching_ctl)
		btrfs_put_caching_control(caching_ctl);

	वापस ret;
पूर्ण

अटल व्योम clear_avail_alloc_bits(काष्ठा btrfs_fs_info *fs_info, u64 flags)
अणु
	u64 extra_flags = chunk_to_extended(flags) &
				BTRFS_EXTENDED_PROखाता_MASK;

	ग_लिखो_seqlock(&fs_info->profiles_lock);
	अगर (flags & BTRFS_BLOCK_GROUP_DATA)
		fs_info->avail_data_alloc_bits &= ~extra_flags;
	अगर (flags & BTRFS_BLOCK_GROUP_METADATA)
		fs_info->avail_metadata_alloc_bits &= ~extra_flags;
	अगर (flags & BTRFS_BLOCK_GROUP_SYSTEM)
		fs_info->avail_प्रणाली_alloc_bits &= ~extra_flags;
	ग_लिखो_sequnlock(&fs_info->profiles_lock);
पूर्ण

/*
 * Clear incompat bits क्रम the following feature(s):
 *
 * - RAID56 - in हाल there's neither RAID5 nor RAID6 profile block group
 *            in the whole fileप्रणाली
 *
 * - RAID1C34 - same as above क्रम RAID1C3 and RAID1C4 block groups
 */
अटल व्योम clear_incompat_bg_bits(काष्ठा btrfs_fs_info *fs_info, u64 flags)
अणु
	bool found_raid56 = false;
	bool found_raid1c34 = false;

	अगर ((flags & BTRFS_BLOCK_GROUP_RAID56_MASK) ||
	    (flags & BTRFS_BLOCK_GROUP_RAID1C3) ||
	    (flags & BTRFS_BLOCK_GROUP_RAID1C4)) अणु
		काष्ठा list_head *head = &fs_info->space_info;
		काष्ठा btrfs_space_info *sinfo;

		list_क्रम_each_entry_rcu(sinfo, head, list) अणु
			करोwn_पढ़ो(&sinfo->groups_sem);
			अगर (!list_empty(&sinfo->block_groups[BTRFS_RAID_RAID5]))
				found_raid56 = true;
			अगर (!list_empty(&sinfo->block_groups[BTRFS_RAID_RAID6]))
				found_raid56 = true;
			अगर (!list_empty(&sinfo->block_groups[BTRFS_RAID_RAID1C3]))
				found_raid1c34 = true;
			अगर (!list_empty(&sinfo->block_groups[BTRFS_RAID_RAID1C4]))
				found_raid1c34 = true;
			up_पढ़ो(&sinfo->groups_sem);
		पूर्ण
		अगर (!found_raid56)
			btrfs_clear_fs_incompat(fs_info, RAID56);
		अगर (!found_raid1c34)
			btrfs_clear_fs_incompat(fs_info, RAID1C34);
	पूर्ण
पूर्ण

अटल पूर्णांक हटाओ_block_group_item(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_path *path,
				   काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	root = fs_info->extent_root;
	key.objectid = block_group->start;
	key.type = BTRFS_BLOCK_GROUP_ITEM_KEY;
	key.offset = block_group->length;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret > 0)
		ret = -ENOENT;
	अगर (ret < 0)
		वापस ret;

	ret = btrfs_del_item(trans, root, path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_हटाओ_block_group(काष्ठा btrfs_trans_handle *trans,
			     u64 group_start, काष्ठा extent_map *em)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_मुक्त_cluster *cluster;
	काष्ठा inode *inode;
	काष्ठा kobject *kobj = शून्य;
	पूर्णांक ret;
	पूर्णांक index;
	पूर्णांक factor;
	काष्ठा btrfs_caching_control *caching_ctl = शून्य;
	bool हटाओ_em;
	bool हटाओ_rsv = false;

	block_group = btrfs_lookup_block_group(fs_info, group_start);
	BUG_ON(!block_group);
	BUG_ON(!block_group->ro);

	trace_btrfs_हटाओ_block_group(block_group);
	/*
	 * Free the reserved super bytes from this block group beक्रमe
	 * हटाओ it.
	 */
	btrfs_मुक्त_excluded_extents(block_group);
	btrfs_मुक्त_ref_tree_range(fs_info, block_group->start,
				  block_group->length);

	index = btrfs_bg_flags_to_raid_index(block_group->flags);
	factor = btrfs_bg_type_to_factor(block_group->flags);

	/* make sure this block group isn't part of an allocation cluster */
	cluster = &fs_info->data_alloc_cluster;
	spin_lock(&cluster->refill_lock);
	btrfs_वापस_cluster_to_मुक्त_space(block_group, cluster);
	spin_unlock(&cluster->refill_lock);

	/*
	 * make sure this block group isn't part of a metadata
	 * allocation cluster
	 */
	cluster = &fs_info->meta_alloc_cluster;
	spin_lock(&cluster->refill_lock);
	btrfs_वापस_cluster_to_मुक्त_space(block_group, cluster);
	spin_unlock(&cluster->refill_lock);

	btrfs_clear_treelog_bg(block_group);

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * get the inode first so any iput calls करोne क्रम the io_list
	 * aren't the final iput (no unlinks allowed now)
	 */
	inode = lookup_मुक्त_space_inode(block_group, path);

	mutex_lock(&trans->transaction->cache_ग_लिखो_mutex);
	/*
	 * Make sure our मुक्त space cache IO is करोne beक्रमe removing the
	 * मुक्त space inode
	 */
	spin_lock(&trans->transaction->dirty_bgs_lock);
	अगर (!list_empty(&block_group->io_list)) अणु
		list_del_init(&block_group->io_list);

		WARN_ON(!IS_ERR(inode) && inode != block_group->io_ctl.inode);

		spin_unlock(&trans->transaction->dirty_bgs_lock);
		btrfs_रुको_cache_io(trans, block_group, path);
		btrfs_put_block_group(block_group);
		spin_lock(&trans->transaction->dirty_bgs_lock);
	पूर्ण

	अगर (!list_empty(&block_group->dirty_list)) अणु
		list_del_init(&block_group->dirty_list);
		हटाओ_rsv = true;
		btrfs_put_block_group(block_group);
	पूर्ण
	spin_unlock(&trans->transaction->dirty_bgs_lock);
	mutex_unlock(&trans->transaction->cache_ग_लिखो_mutex);

	ret = btrfs_हटाओ_मुक्त_space_inode(trans, inode, block_group);
	अगर (ret)
		जाओ out;

	spin_lock(&fs_info->block_group_cache_lock);
	rb_erase(&block_group->cache_node,
		 &fs_info->block_group_cache_tree);
	RB_CLEAR_NODE(&block_group->cache_node);

	/* Once क्रम the block groups rbtree */
	btrfs_put_block_group(block_group);

	अगर (fs_info->first_logical_byte == block_group->start)
		fs_info->first_logical_byte = (u64)-1;
	spin_unlock(&fs_info->block_group_cache_lock);

	करोwn_ग_लिखो(&block_group->space_info->groups_sem);
	/*
	 * we must use list_del_init so people can check to see अगर they
	 * are still on the list after taking the semaphore
	 */
	list_del_init(&block_group->list);
	अगर (list_empty(&block_group->space_info->block_groups[index])) अणु
		kobj = block_group->space_info->block_group_kobjs[index];
		block_group->space_info->block_group_kobjs[index] = शून्य;
		clear_avail_alloc_bits(fs_info, block_group->flags);
	पूर्ण
	up_ग_लिखो(&block_group->space_info->groups_sem);
	clear_incompat_bg_bits(fs_info, block_group->flags);
	अगर (kobj) अणु
		kobject_del(kobj);
		kobject_put(kobj);
	पूर्ण

	अगर (block_group->has_caching_ctl)
		caching_ctl = btrfs_get_caching_control(block_group);
	अगर (block_group->cached == BTRFS_CACHE_STARTED)
		btrfs_रुको_block_group_cache_करोne(block_group);
	अगर (block_group->has_caching_ctl) अणु
		spin_lock(&fs_info->block_group_cache_lock);
		अगर (!caching_ctl) अणु
			काष्ठा btrfs_caching_control *ctl;

			list_क्रम_each_entry(ctl,
				    &fs_info->caching_block_groups, list)
				अगर (ctl->block_group == block_group) अणु
					caching_ctl = ctl;
					refcount_inc(&caching_ctl->count);
					अवरोध;
				पूर्ण
		पूर्ण
		अगर (caching_ctl)
			list_del_init(&caching_ctl->list);
		spin_unlock(&fs_info->block_group_cache_lock);
		अगर (caching_ctl) अणु
			/* Once क्रम the caching bgs list and once क्रम us. */
			btrfs_put_caching_control(caching_ctl);
			btrfs_put_caching_control(caching_ctl);
		पूर्ण
	पूर्ण

	spin_lock(&trans->transaction->dirty_bgs_lock);
	WARN_ON(!list_empty(&block_group->dirty_list));
	WARN_ON(!list_empty(&block_group->io_list));
	spin_unlock(&trans->transaction->dirty_bgs_lock);

	btrfs_हटाओ_मुक्त_space_cache(block_group);

	spin_lock(&block_group->space_info->lock);
	list_del_init(&block_group->ro_list);

	अगर (btrfs_test_opt(fs_info, ENOSPC_DEBUG)) अणु
		WARN_ON(block_group->space_info->total_bytes
			< block_group->length);
		WARN_ON(block_group->space_info->bytes_पढ़ोonly
			< block_group->length - block_group->zone_unusable);
		WARN_ON(block_group->space_info->bytes_zone_unusable
			< block_group->zone_unusable);
		WARN_ON(block_group->space_info->disk_total
			< block_group->length * factor);
	पूर्ण
	block_group->space_info->total_bytes -= block_group->length;
	block_group->space_info->bytes_पढ़ोonly -=
		(block_group->length - block_group->zone_unusable);
	block_group->space_info->bytes_zone_unusable -=
		block_group->zone_unusable;
	block_group->space_info->disk_total -= block_group->length * factor;

	spin_unlock(&block_group->space_info->lock);

	/*
	 * Remove the मुक्त space क्रम the block group from the मुक्त space tree
	 * and the block group's item from the extent tree beक्रमe marking the
	 * block group as हटाओd. This is to prevent races with tasks that
	 * मुक्तze and unमुक्तze a block group, this task and another task
	 * allocating a new block group - the unमुक्तze task ends up removing
	 * the block group's extent map beक्रमe the task calling this function
	 * deletes the block group item from the extent tree, allowing क्रम
	 * another task to attempt to create another block group with the same
	 * item key (and failing with -EEXIST and a transaction पात).
	 */
	ret = हटाओ_block_group_मुक्त_space(trans, block_group);
	अगर (ret)
		जाओ out;

	ret = हटाओ_block_group_item(trans, path, block_group);
	अगर (ret < 0)
		जाओ out;

	spin_lock(&block_group->lock);
	block_group->हटाओd = 1;
	/*
	 * At this poपूर्णांक trimming or scrub can't start on this block group,
	 * because we हटाओd the block group from the rbtree
	 * fs_info->block_group_cache_tree so no one can't find it anymore and
	 * even अगर someone alपढ़ोy got this block group beक्रमe we हटाओd it
	 * from the rbtree, they have alपढ़ोy incremented block_group->frozen -
	 * अगर they didn't, for the trimming case they won't find any मुक्त space
	 * entries because we alपढ़ोy हटाओd them all when we called
	 * btrfs_हटाओ_मुक्त_space_cache().
	 *
	 * And we must not हटाओ the extent map from the fs_info->mapping_tree
	 * to prevent the same logical address range and physical device space
	 * ranges from being reused क्रम a new block group. This is needed to
	 * aव्योम races with trimming and scrub.
	 *
	 * An fs trim operation (btrfs_trim_fs() / btrfs_ioctl_fitrim()) is
	 * completely transactionless, so जबतक it is trimming a range the
	 * currently running transaction might finish and a new one start,
	 * allowing क्रम new block groups to be created that can reuse the same
	 * physical device locations unless we take this special care.
	 *
	 * There may also be an implicit trim operation अगर the file प्रणाली
	 * is mounted with -odiscard. The same protections must reमुख्य
	 * in place until the extents have been discarded completely when
	 * the transaction commit has completed.
	 */
	हटाओ_em = (atomic_पढ़ो(&block_group->frozen) == 0);
	spin_unlock(&block_group->lock);

	अगर (हटाओ_em) अणु
		काष्ठा extent_map_tree *em_tree;

		em_tree = &fs_info->mapping_tree;
		ग_लिखो_lock(&em_tree->lock);
		हटाओ_extent_mapping(em_tree, em);
		ग_लिखो_unlock(&em_tree->lock);
		/* once क्रम the tree */
		मुक्त_extent_map(em);
	पूर्ण

out:
	/* Once क्रम the lookup reference */
	btrfs_put_block_group(block_group);
	अगर (हटाओ_rsv)
		btrfs_delayed_refs_rsv_release(fs_info, 1);
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

काष्ठा btrfs_trans_handle *btrfs_start_trans_हटाओ_block_group(
		काष्ठा btrfs_fs_info *fs_info, स्थिर u64 chunk_offset)
अणु
	काष्ठा extent_map_tree *em_tree = &fs_info->mapping_tree;
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	अचिन्हित पूर्णांक num_items;

	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, chunk_offset, 1);
	पढ़ो_unlock(&em_tree->lock);
	ASSERT(em && em->start == chunk_offset);

	/*
	 * We need to reserve 3 + N units from the metadata space info in order
	 * to हटाओ a block group (करोne at btrfs_हटाओ_chunk() and at
	 * btrfs_हटाओ_block_group()), which are used क्रम:
	 *
	 * 1 unit क्रम adding the मुक्त space inode's orphan (located in the tree
	 * of tree roots).
	 * 1 unit क्रम deleting the block group item (located in the extent
	 * tree).
	 * 1 unit क्रम deleting the मुक्त space item (located in tree of tree
	 * roots).
	 * N units क्रम deleting N device extent items corresponding to each
	 * stripe (located in the device tree).
	 *
	 * In order to हटाओ a block group we also need to reserve units in the
	 * प्रणाली space info in order to update the chunk tree (update one or
	 * more device items and हटाओ one chunk item), but this is करोne at
	 * btrfs_हटाओ_chunk() through a call to check_प्रणाली_chunk().
	 */
	map = em->map_lookup;
	num_items = 3 + map->num_stripes;
	मुक्त_extent_map(em);

	वापस btrfs_start_transaction_fallback_global_rsv(fs_info->extent_root,
							   num_items);
पूर्ण

/*
 * Mark block group @cache पढ़ो-only, so later ग_लिखो won't happen to block
 * group @cache.
 *
 * If @क्रमce is not set, this function will only mark the block group पढ़ोonly
 * अगर we have enough मुक्त space (1M) in other metadata/प्रणाली block groups.
 * If @क्रमce is not set, this function will mark the block group पढ़ोonly
 * without checking मुक्त space.
 *
 * NOTE: This function करोesn't care अगर other block groups can contain all the
 * data in this block group. That check should be करोne by relocation routine,
 * not this function.
 */
अटल पूर्णांक inc_block_group_ro(काष्ठा btrfs_block_group *cache, पूर्णांक क्रमce)
अणु
	काष्ठा btrfs_space_info *sinfo = cache->space_info;
	u64 num_bytes;
	पूर्णांक ret = -ENOSPC;

	spin_lock(&sinfo->lock);
	spin_lock(&cache->lock);

	अगर (cache->swap_extents) अणु
		ret = -ETXTBSY;
		जाओ out;
	पूर्ण

	अगर (cache->ro) अणु
		cache->ro++;
		ret = 0;
		जाओ out;
	पूर्ण

	num_bytes = cache->length - cache->reserved - cache->pinned -
		    cache->bytes_super - cache->zone_unusable - cache->used;

	/*
	 * Data never overcommits, even in mixed mode, so करो just the straight
	 * check of left over space in how much we have allocated.
	 */
	अगर (क्रमce) अणु
		ret = 0;
	पूर्ण अन्यथा अगर (sinfo->flags & BTRFS_BLOCK_GROUP_DATA) अणु
		u64 sinfo_used = btrfs_space_info_used(sinfo, true);

		/*
		 * Here we make sure अगर we mark this bg RO, we still have enough
		 * मुक्त space as buffer.
		 */
		अगर (sinfo_used + num_bytes <= sinfo->total_bytes)
			ret = 0;
	पूर्ण अन्यथा अणु
		/*
		 * We overcommit metadata, so we need to करो the
		 * btrfs_can_overcommit check here, and we need to pass in
		 * BTRFS_RESERVE_NO_FLUSH to give ourselves the most amount of
		 * leeway to allow us to mark this block group as पढ़ो only.
		 */
		अगर (btrfs_can_overcommit(cache->fs_info, sinfo, num_bytes,
					 BTRFS_RESERVE_NO_FLUSH))
			ret = 0;
	पूर्ण

	अगर (!ret) अणु
		sinfo->bytes_पढ़ोonly += num_bytes;
		अगर (btrfs_is_zoned(cache->fs_info)) अणु
			/* Migrate zone_unusable bytes to पढ़ोonly */
			sinfo->bytes_पढ़ोonly += cache->zone_unusable;
			sinfo->bytes_zone_unusable -= cache->zone_unusable;
			cache->zone_unusable = 0;
		पूर्ण
		cache->ro++;
		list_add_tail(&cache->ro_list, &sinfo->ro_bgs);
	पूर्ण
out:
	spin_unlock(&cache->lock);
	spin_unlock(&sinfo->lock);
	अगर (ret == -ENOSPC && btrfs_test_opt(cache->fs_info, ENOSPC_DEBUG)) अणु
		btrfs_info(cache->fs_info,
			"unable to make block group %llu ro", cache->start);
		btrfs_dump_space_info(cache->fs_info, cache->space_info, 0, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool clean_pinned_extents(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_block_group *bg)
अणु
	काष्ठा btrfs_fs_info *fs_info = bg->fs_info;
	काष्ठा btrfs_transaction *prev_trans = शून्य;
	स्थिर u64 start = bg->start;
	स्थिर u64 end = start + bg->length - 1;
	पूर्णांक ret;

	spin_lock(&fs_info->trans_lock);
	अगर (trans->transaction->list.prev != &fs_info->trans_list) अणु
		prev_trans = list_last_entry(&trans->transaction->list,
					     काष्ठा btrfs_transaction, list);
		refcount_inc(&prev_trans->use_count);
	पूर्ण
	spin_unlock(&fs_info->trans_lock);

	/*
	 * Hold the unused_bg_unpin_mutex lock to aव्योम racing with
	 * btrfs_finish_extent_commit(). If we are at transaction N, another
	 * task might be running finish_extent_commit() क्रम the previous
	 * transaction N - 1, and have seen a range beदीर्घing to the block
	 * group in pinned_extents beक्रमe we were able to clear the whole block
	 * group range from pinned_extents. This means that task can lookup क्रम
	 * the block group after we unpinned it from pinned_extents and हटाओd
	 * it, leading to a BUG_ON() at unpin_extent_range().
	 */
	mutex_lock(&fs_info->unused_bg_unpin_mutex);
	अगर (prev_trans) अणु
		ret = clear_extent_bits(&prev_trans->pinned_extents, start, end,
					EXTENT_सूचीTY);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = clear_extent_bits(&trans->transaction->pinned_extents, start, end,
				EXTENT_सूचीTY);
out:
	mutex_unlock(&fs_info->unused_bg_unpin_mutex);
	अगर (prev_trans)
		btrfs_put_transaction(prev_trans);

	वापस ret == 0;
पूर्ण

/*
 * Process the unused_bgs list and हटाओ any that करोn't have any allocated
 * space inside of them.
 */
व्योम btrfs_delete_unused_bgs(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_space_info *space_info;
	काष्ठा btrfs_trans_handle *trans;
	स्थिर bool async_trim_enabled = btrfs_test_opt(fs_info, DISCARD_ASYNC);
	पूर्णांक ret = 0;

	अगर (!test_bit(BTRFS_FS_OPEN, &fs_info->flags))
		वापस;

	/*
	 * Long running balances can keep us blocked here क्रम eternity, so
	 * simply skip deletion अगर we're unable to get the mutex.
	 */
	अगर (!mutex_trylock(&fs_info->reclaim_bgs_lock))
		वापस;

	spin_lock(&fs_info->unused_bgs_lock);
	जबतक (!list_empty(&fs_info->unused_bgs)) अणु
		पूर्णांक trimming;

		block_group = list_first_entry(&fs_info->unused_bgs,
					       काष्ठा btrfs_block_group,
					       bg_list);
		list_del_init(&block_group->bg_list);

		space_info = block_group->space_info;

		अगर (ret || btrfs_mixed_space_info(space_info)) अणु
			btrfs_put_block_group(block_group);
			जारी;
		पूर्ण
		spin_unlock(&fs_info->unused_bgs_lock);

		btrfs_discard_cancel_work(&fs_info->discard_ctl, block_group);

		/* Don't want to race with allocators so take the groups_sem */
		करोwn_ग_लिखो(&space_info->groups_sem);

		/*
		 * Async discard moves the final block group discard to be prior
		 * to the unused_bgs code path.  Thereक्रमe, अगर it's not fully
		 * trimmed, punt it back to the async discard lists.
		 */
		अगर (btrfs_test_opt(fs_info, DISCARD_ASYNC) &&
		    !btrfs_is_मुक्त_space_trimmed(block_group)) अणु
			trace_btrfs_skip_unused_block_group(block_group);
			up_ग_लिखो(&space_info->groups_sem);
			/* Requeue अगर we failed because of async discard */
			btrfs_discard_queue_work(&fs_info->discard_ctl,
						 block_group);
			जाओ next;
		पूर्ण

		spin_lock(&block_group->lock);
		अगर (block_group->reserved || block_group->pinned ||
		    block_group->used || block_group->ro ||
		    list_is_singular(&block_group->list)) अणु
			/*
			 * We want to bail अगर we made new allocations or have
			 * outstanding allocations in this block group.  We करो
			 * the ro check in हाल balance is currently acting on
			 * this block group.
			 */
			trace_btrfs_skip_unused_block_group(block_group);
			spin_unlock(&block_group->lock);
			up_ग_लिखो(&space_info->groups_sem);
			जाओ next;
		पूर्ण
		spin_unlock(&block_group->lock);

		/* We करोn't want to force the issue, only flip if it's ok. */
		ret = inc_block_group_ro(block_group, 0);
		up_ग_लिखो(&space_info->groups_sem);
		अगर (ret < 0) अणु
			ret = 0;
			जाओ next;
		पूर्ण

		/*
		 * Want to करो this beक्रमe we करो anything अन्यथा so we can recover
		 * properly अगर we fail to join the transaction.
		 */
		trans = btrfs_start_trans_हटाओ_block_group(fs_info,
						     block_group->start);
		अगर (IS_ERR(trans)) अणु
			btrfs_dec_block_group_ro(block_group);
			ret = PTR_ERR(trans);
			जाओ next;
		पूर्ण

		/*
		 * We could have pending pinned extents क्रम this block group,
		 * just delete them, we करोn't care about them anymore.
		 */
		अगर (!clean_pinned_extents(trans, block_group)) अणु
			btrfs_dec_block_group_ro(block_group);
			जाओ end_trans;
		पूर्ण

		/*
		 * At this poपूर्णांक, the block_group is पढ़ो only and should fail
		 * new allocations.  However, btrfs_finish_extent_commit() can
		 * cause this block_group to be placed back on the discard
		 * lists because now the block_group isn't fully discarded.
		 * Bail here and try again later after discarding everything.
		 */
		spin_lock(&fs_info->discard_ctl.lock);
		अगर (!list_empty(&block_group->discard_list)) अणु
			spin_unlock(&fs_info->discard_ctl.lock);
			btrfs_dec_block_group_ro(block_group);
			btrfs_discard_queue_work(&fs_info->discard_ctl,
						 block_group);
			जाओ end_trans;
		पूर्ण
		spin_unlock(&fs_info->discard_ctl.lock);

		/* Reset pinned so btrfs_put_block_group करोesn't complain */
		spin_lock(&space_info->lock);
		spin_lock(&block_group->lock);

		btrfs_space_info_update_bytes_pinned(fs_info, space_info,
						     -block_group->pinned);
		space_info->bytes_पढ़ोonly += block_group->pinned;
		__btrfs_mod_total_bytes_pinned(space_info, -block_group->pinned);
		block_group->pinned = 0;

		spin_unlock(&block_group->lock);
		spin_unlock(&space_info->lock);

		/*
		 * The normal path here is an unused block group is passed here,
		 * then trimming is handled in the transaction commit path.
		 * Async discard पूर्णांकerposes beक्रमe this to करो the trimming
		 * beक्रमe coming करोwn the unused block group path as trimming
		 * will no दीर्घer be करोne later in the transaction commit path.
		 */
		अगर (!async_trim_enabled && btrfs_test_opt(fs_info, DISCARD_ASYNC))
			जाओ flip_async;

		/*
		 * DISCARD can flip during remount. On zoned fileप्रणालीs, we
		 * need to reset sequential-required zones.
		 */
		trimming = btrfs_test_opt(fs_info, DISCARD_SYNC) ||
				btrfs_is_zoned(fs_info);

		/* Implicit trim during transaction commit. */
		अगर (trimming)
			btrfs_मुक्तze_block_group(block_group);

		/*
		 * Btrfs_हटाओ_chunk will पात the transaction अगर things go
		 * horribly wrong.
		 */
		ret = btrfs_हटाओ_chunk(trans, block_group->start);

		अगर (ret) अणु
			अगर (trimming)
				btrfs_unमुक्तze_block_group(block_group);
			जाओ end_trans;
		पूर्ण

		/*
		 * If we're not mounted with -odiscard, we can just क्रमget
		 * about this block group. Otherwise we'll need to रुको
		 * until transaction commit to करो the actual discard.
		 */
		अगर (trimming) अणु
			spin_lock(&fs_info->unused_bgs_lock);
			/*
			 * A concurrent scrub might have added us to the list
			 * fs_info->unused_bgs, so use a list_move operation
			 * to add the block group to the deleted_bgs list.
			 */
			list_move(&block_group->bg_list,
				  &trans->transaction->deleted_bgs);
			spin_unlock(&fs_info->unused_bgs_lock);
			btrfs_get_block_group(block_group);
		पूर्ण
end_trans:
		btrfs_end_transaction(trans);
next:
		btrfs_put_block_group(block_group);
		spin_lock(&fs_info->unused_bgs_lock);
	पूर्ण
	spin_unlock(&fs_info->unused_bgs_lock);
	mutex_unlock(&fs_info->reclaim_bgs_lock);
	वापस;

flip_async:
	btrfs_end_transaction(trans);
	mutex_unlock(&fs_info->reclaim_bgs_lock);
	btrfs_put_block_group(block_group);
	btrfs_discard_punt_unused_bgs_list(fs_info);
पूर्ण

व्योम btrfs_mark_bg_unused(काष्ठा btrfs_block_group *bg)
अणु
	काष्ठा btrfs_fs_info *fs_info = bg->fs_info;

	spin_lock(&fs_info->unused_bgs_lock);
	अगर (list_empty(&bg->bg_list)) अणु
		btrfs_get_block_group(bg);
		trace_btrfs_add_unused_block_group(bg);
		list_add_tail(&bg->bg_list, &fs_info->unused_bgs);
	पूर्ण
	spin_unlock(&fs_info->unused_bgs_lock);
पूर्ण

व्योम btrfs_reclaim_bgs_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btrfs_fs_info *fs_info =
		container_of(work, काष्ठा btrfs_fs_info, reclaim_bgs_work);
	काष्ठा btrfs_block_group *bg;
	काष्ठा btrfs_space_info *space_info;
	पूर्णांक ret;

	अगर (!test_bit(BTRFS_FS_OPEN, &fs_info->flags))
		वापस;

	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_BALANCE))
		वापस;

	mutex_lock(&fs_info->reclaim_bgs_lock);
	spin_lock(&fs_info->unused_bgs_lock);
	जबतक (!list_empty(&fs_info->reclaim_bgs)) अणु
		bg = list_first_entry(&fs_info->reclaim_bgs,
				      काष्ठा btrfs_block_group,
				      bg_list);
		list_del_init(&bg->bg_list);

		space_info = bg->space_info;
		spin_unlock(&fs_info->unused_bgs_lock);

		/* Don't race with allocators so take the groups_sem */
		करोwn_ग_लिखो(&space_info->groups_sem);

		spin_lock(&bg->lock);
		अगर (bg->reserved || bg->pinned || bg->ro) अणु
			/*
			 * We want to bail अगर we made new allocations or have
			 * outstanding allocations in this block group.  We करो
			 * the ro check in हाल balance is currently acting on
			 * this block group.
			 */
			spin_unlock(&bg->lock);
			up_ग_लिखो(&space_info->groups_sem);
			जाओ next;
		पूर्ण
		spin_unlock(&bg->lock);

		/* Get out fast, in हाल we're unmounting the fileप्रणाली */
		अगर (btrfs_fs_closing(fs_info)) अणु
			up_ग_लिखो(&space_info->groups_sem);
			जाओ next;
		पूर्ण

		ret = inc_block_group_ro(bg, 0);
		up_ग_लिखो(&space_info->groups_sem);
		अगर (ret < 0)
			जाओ next;

		btrfs_info(fs_info, "reclaiming chunk %llu with %llu%% used",
				bg->start, भाग_u64(bg->used * 100, bg->length));
		trace_btrfs_reclaim_block_group(bg);
		ret = btrfs_relocate_chunk(fs_info, bg->start);
		अगर (ret)
			btrfs_err(fs_info, "error relocating chunk %llu",
				  bg->start);

next:
		btrfs_put_block_group(bg);
		spin_lock(&fs_info->unused_bgs_lock);
	पूर्ण
	spin_unlock(&fs_info->unused_bgs_lock);
	mutex_unlock(&fs_info->reclaim_bgs_lock);
	btrfs_exclop_finish(fs_info);
पूर्ण

व्योम btrfs_reclaim_bgs(काष्ठा btrfs_fs_info *fs_info)
अणु
	spin_lock(&fs_info->unused_bgs_lock);
	अगर (!list_empty(&fs_info->reclaim_bgs))
		queue_work(प्रणाली_unbound_wq, &fs_info->reclaim_bgs_work);
	spin_unlock(&fs_info->unused_bgs_lock);
पूर्ण

व्योम btrfs_mark_bg_to_reclaim(काष्ठा btrfs_block_group *bg)
अणु
	काष्ठा btrfs_fs_info *fs_info = bg->fs_info;

	spin_lock(&fs_info->unused_bgs_lock);
	अगर (list_empty(&bg->bg_list)) अणु
		btrfs_get_block_group(bg);
		trace_btrfs_add_reclaim_block_group(bg);
		list_add_tail(&bg->bg_list, &fs_info->reclaim_bgs);
	पूर्ण
	spin_unlock(&fs_info->unused_bgs_lock);
पूर्ण

अटल पूर्णांक पढ़ो_bg_from_eb(काष्ठा btrfs_fs_info *fs_info, काष्ठा btrfs_key *key,
			   काष्ठा btrfs_path *path)
अणु
	काष्ठा extent_map_tree *em_tree;
	काष्ठा extent_map *em;
	काष्ठा btrfs_block_group_item bg;
	काष्ठा extent_buffer *leaf;
	पूर्णांक slot;
	u64 flags;
	पूर्णांक ret = 0;

	slot = path->slots[0];
	leaf = path->nodes[0];

	em_tree = &fs_info->mapping_tree;
	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, key->objectid, key->offset);
	पढ़ो_unlock(&em_tree->lock);
	अगर (!em) अणु
		btrfs_err(fs_info,
			  "logical %llu len %llu found bg but no related chunk",
			  key->objectid, key->offset);
		वापस -ENOENT;
	पूर्ण

	अगर (em->start != key->objectid || em->len != key->offset) अणु
		btrfs_err(fs_info,
			"block group %llu len %llu mismatch with chunk %llu len %llu",
			key->objectid, key->offset, em->start, em->len);
		ret = -EUCLEAN;
		जाओ out_मुक्त_em;
	पूर्ण

	पढ़ो_extent_buffer(leaf, &bg, btrfs_item_ptr_offset(leaf, slot),
			   माप(bg));
	flags = btrfs_stack_block_group_flags(&bg) &
		BTRFS_BLOCK_GROUP_TYPE_MASK;

	अगर (flags != (em->map_lookup->type & BTRFS_BLOCK_GROUP_TYPE_MASK)) अणु
		btrfs_err(fs_info,
"block group %llu len %llu type flags 0x%llx mismatch with chunk type flags 0x%llx",
			  key->objectid, key->offset, flags,
			  (BTRFS_BLOCK_GROUP_TYPE_MASK & em->map_lookup->type));
		ret = -EUCLEAN;
	पूर्ण

out_मुक्त_em:
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

अटल पूर्णांक find_first_block_group(काष्ठा btrfs_fs_info *fs_info,
				  काष्ठा btrfs_path *path,
				  काष्ठा btrfs_key *key)
अणु
	काष्ठा btrfs_root *root = fs_info->extent_root;
	पूर्णांक ret;
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *leaf;
	पूर्णांक slot;

	ret = btrfs_search_slot(शून्य, root, key, path, 0, 0);
	अगर (ret < 0)
		वापस ret;

	जबतक (1) अणु
		slot = path->slots[0];
		leaf = path->nodes[0];
		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret == 0)
				जारी;
			अगर (ret < 0)
				जाओ out;
			अवरोध;
		पूर्ण
		btrfs_item_key_to_cpu(leaf, &found_key, slot);

		अगर (found_key.objectid >= key->objectid &&
		    found_key.type == BTRFS_BLOCK_GROUP_ITEM_KEY) अणु
			ret = पढ़ो_bg_from_eb(fs_info, &found_key, path);
			अवरोध;
		पूर्ण

		path->slots[0]++;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम set_avail_alloc_bits(काष्ठा btrfs_fs_info *fs_info, u64 flags)
अणु
	u64 extra_flags = chunk_to_extended(flags) &
				BTRFS_EXTENDED_PROखाता_MASK;

	ग_लिखो_seqlock(&fs_info->profiles_lock);
	अगर (flags & BTRFS_BLOCK_GROUP_DATA)
		fs_info->avail_data_alloc_bits |= extra_flags;
	अगर (flags & BTRFS_BLOCK_GROUP_METADATA)
		fs_info->avail_metadata_alloc_bits |= extra_flags;
	अगर (flags & BTRFS_BLOCK_GROUP_SYSTEM)
		fs_info->avail_प्रणाली_alloc_bits |= extra_flags;
	ग_लिखो_sequnlock(&fs_info->profiles_lock);
पूर्ण

/**
 * Map a physical disk address to a list of logical addresses
 *
 * @fs_info:       the fileप्रणाली
 * @chunk_start:   logical address of block group
 * @bdev:	   physical device to resolve, can be शून्य to indicate any device
 * @physical:	   physical address to map to logical addresses
 * @logical:	   वापस array of logical addresses which map to @physical
 * @naddrs:	   length of @logical
 * @stripe_len:    size of IO stripe क्रम the given block group
 *
 * Maps a particular @physical disk address to a list of @logical addresses.
 * Used primarily to exclude those portions of a block group that contain super
 * block copies.
 */
पूर्णांक btrfs_rmap_block(काष्ठा btrfs_fs_info *fs_info, u64 chunk_start,
		     काष्ठा block_device *bdev, u64 physical, u64 **logical,
		     पूर्णांक *naddrs, पूर्णांक *stripe_len)
अणु
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	u64 *buf;
	u64 bytenr;
	u64 data_stripe_length;
	u64 io_stripe_size;
	पूर्णांक i, nr = 0;
	पूर्णांक ret = 0;

	em = btrfs_get_chunk_map(fs_info, chunk_start, 1);
	अगर (IS_ERR(em))
		वापस -EIO;

	map = em->map_lookup;
	data_stripe_length = em->orig_block_len;
	io_stripe_size = map->stripe_len;
	chunk_start = em->start;

	/* For RAID5/6 adjust to a full IO stripe length */
	अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK)
		io_stripe_size = map->stripe_len * nr_data_stripes(map);

	buf = kसुस्मृति(map->num_stripes, माप(u64), GFP_NOFS);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < map->num_stripes; i++) अणु
		bool alपढ़ोy_inserted = false;
		u64 stripe_nr;
		u64 offset;
		पूर्णांक j;

		अगर (!in_range(physical, map->stripes[i].physical,
			      data_stripe_length))
			जारी;

		अगर (bdev && map->stripes[i].dev->bdev != bdev)
			जारी;

		stripe_nr = physical - map->stripes[i].physical;
		stripe_nr = भाग64_u64_rem(stripe_nr, map->stripe_len, &offset);

		अगर (map->type & BTRFS_BLOCK_GROUP_RAID10) अणु
			stripe_nr = stripe_nr * map->num_stripes + i;
			stripe_nr = भाग_u64(stripe_nr, map->sub_stripes);
		पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID0) अणु
			stripe_nr = stripe_nr * map->num_stripes + i;
		पूर्ण
		/*
		 * The reमुख्यing हाल would be क्रम RAID56, multiply by
		 * nr_data_stripes().  Alternatively, just use rmap_len below
		 * instead of map->stripe_len
		 */

		bytenr = chunk_start + stripe_nr * io_stripe_size + offset;

		/* Ensure we करोn't add duplicate addresses */
		क्रम (j = 0; j < nr; j++) अणु
			अगर (buf[j] == bytenr) अणु
				alपढ़ोy_inserted = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!alपढ़ोy_inserted)
			buf[nr++] = bytenr;
	पूर्ण

	*logical = buf;
	*naddrs = nr;
	*stripe_len = io_stripe_size;
out:
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

अटल पूर्णांक exclude_super_stripes(काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	स्थिर bool zoned = btrfs_is_zoned(fs_info);
	u64 bytenr;
	u64 *logical;
	पूर्णांक stripe_len;
	पूर्णांक i, nr, ret;

	अगर (cache->start < BTRFS_SUPER_INFO_OFFSET) अणु
		stripe_len = BTRFS_SUPER_INFO_OFFSET - cache->start;
		cache->bytes_super += stripe_len;
		ret = btrfs_add_excluded_extent(fs_info, cache->start,
						stripe_len);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < BTRFS_SUPER_MIRROR_MAX; i++) अणु
		bytenr = btrfs_sb_offset(i);
		ret = btrfs_rmap_block(fs_info, cache->start, शून्य,
				       bytenr, &logical, &nr, &stripe_len);
		अगर (ret)
			वापस ret;

		/* Shouldn't have super stripes in sequential zones */
		अगर (zoned && nr) अणु
			btrfs_err(fs_info,
			"zoned: block group %llu must not contain super block",
				  cache->start);
			वापस -EUCLEAN;
		पूर्ण

		जबतक (nr--) अणु
			u64 len = min_t(u64, stripe_len,
				cache->start + cache->length - logical[nr]);

			cache->bytes_super += len;
			ret = btrfs_add_excluded_extent(fs_info, logical[nr],
							len);
			अगर (ret) अणु
				kमुक्त(logical);
				वापस ret;
			पूर्ण
		पूर्ण

		kमुक्त(logical);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम link_block_group(काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_space_info *space_info = cache->space_info;
	पूर्णांक index = btrfs_bg_flags_to_raid_index(cache->flags);

	करोwn_ग_लिखो(&space_info->groups_sem);
	list_add_tail(&cache->list, &space_info->block_groups[index]);
	up_ग_लिखो(&space_info->groups_sem);
पूर्ण

अटल काष्ठा btrfs_block_group *btrfs_create_block_group_cache(
		काष्ठा btrfs_fs_info *fs_info, u64 start)
अणु
	काष्ठा btrfs_block_group *cache;

	cache = kzalloc(माप(*cache), GFP_NOFS);
	अगर (!cache)
		वापस शून्य;

	cache->मुक्त_space_ctl = kzalloc(माप(*cache->मुक्त_space_ctl),
					GFP_NOFS);
	अगर (!cache->मुक्त_space_ctl) अणु
		kमुक्त(cache);
		वापस शून्य;
	पूर्ण

	cache->start = start;

	cache->fs_info = fs_info;
	cache->full_stripe_len = btrfs_full_stripe_len(fs_info, start);

	cache->discard_index = BTRFS_DISCARD_INDEX_UNUSED;

	refcount_set(&cache->refs, 1);
	spin_lock_init(&cache->lock);
	init_rwsem(&cache->data_rwsem);
	INIT_LIST_HEAD(&cache->list);
	INIT_LIST_HEAD(&cache->cluster_list);
	INIT_LIST_HEAD(&cache->bg_list);
	INIT_LIST_HEAD(&cache->ro_list);
	INIT_LIST_HEAD(&cache->discard_list);
	INIT_LIST_HEAD(&cache->dirty_list);
	INIT_LIST_HEAD(&cache->io_list);
	btrfs_init_मुक्त_space_ctl(cache, cache->मुक्त_space_ctl);
	atomic_set(&cache->frozen, 0);
	mutex_init(&cache->मुक्त_space_lock);
	btrfs_init_full_stripe_locks_tree(&cache->full_stripe_locks_root);

	वापस cache;
पूर्ण

/*
 * Iterate all chunks and verअगरy that each of them has the corresponding block
 * group
 */
अटल पूर्णांक check_chunk_block_group_mappings(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा extent_map_tree *map_tree = &fs_info->mapping_tree;
	काष्ठा extent_map *em;
	काष्ठा btrfs_block_group *bg;
	u64 start = 0;
	पूर्णांक ret = 0;

	जबतक (1) अणु
		पढ़ो_lock(&map_tree->lock);
		/*
		 * lookup_extent_mapping will वापस the first extent map
		 * पूर्णांकersecting the range, so setting @len to 1 is enough to
		 * get the first chunk.
		 */
		em = lookup_extent_mapping(map_tree, start, 1);
		पढ़ो_unlock(&map_tree->lock);
		अगर (!em)
			अवरोध;

		bg = btrfs_lookup_block_group(fs_info, em->start);
		अगर (!bg) अणु
			btrfs_err(fs_info,
	"chunk start=%llu len=%llu doesn't have corresponding block group",
				     em->start, em->len);
			ret = -EUCLEAN;
			मुक्त_extent_map(em);
			अवरोध;
		पूर्ण
		अगर (bg->start != em->start || bg->length != em->len ||
		    (bg->flags & BTRFS_BLOCK_GROUP_TYPE_MASK) !=
		    (em->map_lookup->type & BTRFS_BLOCK_GROUP_TYPE_MASK)) अणु
			btrfs_err(fs_info,
"chunk start=%llu len=%llu flags=0x%llx doesn't match block group start=%llu len=%llu flags=0x%llx",
				em->start, em->len,
				em->map_lookup->type & BTRFS_BLOCK_GROUP_TYPE_MASK,
				bg->start, bg->length,
				bg->flags & BTRFS_BLOCK_GROUP_TYPE_MASK);
			ret = -EUCLEAN;
			मुक्त_extent_map(em);
			btrfs_put_block_group(bg);
			अवरोध;
		पूर्ण
		start = em->start + em->len;
		मुक्त_extent_map(em);
		btrfs_put_block_group(bg);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_one_block_group(काष्ठा btrfs_fs_info *info,
				काष्ठा btrfs_block_group_item *bgi,
				स्थिर काष्ठा btrfs_key *key,
				पूर्णांक need_clear)
अणु
	काष्ठा btrfs_block_group *cache;
	काष्ठा btrfs_space_info *space_info;
	स्थिर bool mixed = btrfs_fs_incompat(info, MIXED_GROUPS);
	पूर्णांक ret;

	ASSERT(key->type == BTRFS_BLOCK_GROUP_ITEM_KEY);

	cache = btrfs_create_block_group_cache(info, key->objectid);
	अगर (!cache)
		वापस -ENOMEM;

	cache->length = key->offset;
	cache->used = btrfs_stack_block_group_used(bgi);
	cache->flags = btrfs_stack_block_group_flags(bgi);

	set_मुक्त_space_tree_thresholds(cache);

	अगर (need_clear) अणु
		/*
		 * When we mount with old space cache, we need to
		 * set BTRFS_DC_CLEAR and set dirty flag.
		 *
		 * a) Setting 'BTRFS_DC_CLEAR' makes sure that we
		 *    truncate the old मुक्त space cache inode and
		 *    setup a new one.
		 * b) Setting 'dirty flag' makes sure that we flush
		 *    the new space cache info onto disk.
		 */
		अगर (btrfs_test_opt(info, SPACE_CACHE))
			cache->disk_cache_state = BTRFS_DC_CLEAR;
	पूर्ण
	अगर (!mixed && ((cache->flags & BTRFS_BLOCK_GROUP_METADATA) &&
	    (cache->flags & BTRFS_BLOCK_GROUP_DATA))) अणु
			btrfs_err(info,
"bg %llu is a mixed block group but filesystem hasn't enabled mixed block groups",
				  cache->start);
			ret = -EINVAL;
			जाओ error;
	पूर्ण

	ret = btrfs_load_block_group_zone_info(cache, false);
	अगर (ret) अणु
		btrfs_err(info, "zoned: failed to load zone info of bg %llu",
			  cache->start);
		जाओ error;
	पूर्ण

	/*
	 * We need to exclude the super stripes now so that the space info has
	 * super bytes accounted क्रम, otherwise we'll think we have more space
	 * than we actually करो.
	 */
	ret = exclude_super_stripes(cache);
	अगर (ret) अणु
		/* We may have excluded something, so call this just in हाल. */
		btrfs_मुक्त_excluded_extents(cache);
		जाओ error;
	पूर्ण

	/*
	 * For zoned fileप्रणाली, space after the allocation offset is the only
	 * मुक्त space क्रम a block group. So, we करोn't need any caching work.
	 * btrfs_calc_zone_unusable() will set the amount of मुक्त space and
	 * zone_unusable space.
	 *
	 * For regular fileप्रणाली, check क्रम two हालs, either we are full, and
	 * thereक्रमe करोn't need to bother with the caching work since we won't
	 * find any space, or we are empty, and we can just add all the space
	 * in and be करोne with it.  This saves us _a_lot_ of समय, particularly
	 * in the full हाल.
	 */
	अगर (btrfs_is_zoned(info)) अणु
		btrfs_calc_zone_unusable(cache);
	पूर्ण अन्यथा अगर (cache->length == cache->used) अणु
		cache->last_byte_to_unpin = (u64)-1;
		cache->cached = BTRFS_CACHE_FINISHED;
		btrfs_मुक्त_excluded_extents(cache);
	पूर्ण अन्यथा अगर (cache->used == 0) अणु
		cache->last_byte_to_unpin = (u64)-1;
		cache->cached = BTRFS_CACHE_FINISHED;
		add_new_मुक्त_space(cache, cache->start,
				   cache->start + cache->length);
		btrfs_मुक्त_excluded_extents(cache);
	पूर्ण

	ret = btrfs_add_block_group_cache(info, cache);
	अगर (ret) अणु
		btrfs_हटाओ_मुक्त_space_cache(cache);
		जाओ error;
	पूर्ण
	trace_btrfs_add_block_group(info, cache, 0);
	btrfs_update_space_info(info, cache->flags, cache->length,
				cache->used, cache->bytes_super,
				cache->zone_unusable, &space_info);

	cache->space_info = space_info;

	link_block_group(cache);

	set_avail_alloc_bits(info, cache->flags);
	अगर (btrfs_chunk_पढ़ोonly(info, cache->start)) अणु
		inc_block_group_ro(cache, 1);
	पूर्ण अन्यथा अगर (cache->used == 0) अणु
		ASSERT(list_empty(&cache->bg_list));
		अगर (btrfs_test_opt(info, DISCARD_ASYNC))
			btrfs_discard_queue_work(&info->discard_ctl, cache);
		अन्यथा
			btrfs_mark_bg_unused(cache);
	पूर्ण
	वापस 0;
error:
	btrfs_put_block_group(cache);
	वापस ret;
पूर्ण

अटल पूर्णांक fill_dummy_bgs(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा extent_map_tree *em_tree = &fs_info->mapping_tree;
	काष्ठा btrfs_space_info *space_info;
	काष्ठा rb_node *node;
	पूर्णांक ret = 0;

	क्रम (node = rb_first_cached(&em_tree->map); node; node = rb_next(node)) अणु
		काष्ठा extent_map *em;
		काष्ठा map_lookup *map;
		काष्ठा btrfs_block_group *bg;

		em = rb_entry(node, काष्ठा extent_map, rb_node);
		map = em->map_lookup;
		bg = btrfs_create_block_group_cache(fs_info, em->start);
		अगर (!bg) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		/* Fill dummy cache as FULL */
		bg->length = em->len;
		bg->flags = map->type;
		bg->last_byte_to_unpin = (u64)-1;
		bg->cached = BTRFS_CACHE_FINISHED;
		bg->used = em->len;
		bg->flags = map->type;
		ret = btrfs_add_block_group_cache(fs_info, bg);
		अगर (ret) अणु
			btrfs_हटाओ_मुक्त_space_cache(bg);
			btrfs_put_block_group(bg);
			अवरोध;
		पूर्ण
		btrfs_update_space_info(fs_info, bg->flags, em->len, em->len,
					0, 0, &space_info);
		bg->space_info = space_info;
		link_block_group(bg);

		set_avail_alloc_bits(fs_info, bg->flags);
	पूर्ण
	अगर (!ret)
		btrfs_init_global_block_rsv(fs_info);
	वापस ret;
पूर्ण

पूर्णांक btrfs_पढ़ो_block_groups(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा btrfs_path *path;
	पूर्णांक ret;
	काष्ठा btrfs_block_group *cache;
	काष्ठा btrfs_space_info *space_info;
	काष्ठा btrfs_key key;
	पूर्णांक need_clear = 0;
	u64 cache_gen;

	अगर (!info->extent_root)
		वापस fill_dummy_bgs(info);

	key.objectid = 0;
	key.offset = 0;
	key.type = BTRFS_BLOCK_GROUP_ITEM_KEY;
	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	cache_gen = btrfs_super_cache_generation(info->super_copy);
	अगर (btrfs_test_opt(info, SPACE_CACHE) &&
	    btrfs_super_generation(info->super_copy) != cache_gen)
		need_clear = 1;
	अगर (btrfs_test_opt(info, CLEAR_CACHE))
		need_clear = 1;

	जबतक (1) अणु
		काष्ठा btrfs_block_group_item bgi;
		काष्ठा extent_buffer *leaf;
		पूर्णांक slot;

		ret = find_first_block_group(info, path, &key);
		अगर (ret > 0)
			अवरोध;
		अगर (ret != 0)
			जाओ error;

		leaf = path->nodes[0];
		slot = path->slots[0];

		पढ़ो_extent_buffer(leaf, &bgi, btrfs_item_ptr_offset(leaf, slot),
				   माप(bgi));

		btrfs_item_key_to_cpu(leaf, &key, slot);
		btrfs_release_path(path);
		ret = पढ़ो_one_block_group(info, &bgi, &key, need_clear);
		अगर (ret < 0)
			जाओ error;
		key.objectid += key.offset;
		key.offset = 0;
	पूर्ण
	btrfs_release_path(path);

	list_क्रम_each_entry(space_info, &info->space_info, list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < BTRFS_NR_RAID_TYPES; i++) अणु
			अगर (list_empty(&space_info->block_groups[i]))
				जारी;
			cache = list_first_entry(&space_info->block_groups[i],
						 काष्ठा btrfs_block_group,
						 list);
			btrfs_sysfs_add_block_group_type(cache);
		पूर्ण

		अगर (!(btrfs_get_alloc_profile(info, space_info->flags) &
		      (BTRFS_BLOCK_GROUP_RAID10 |
		       BTRFS_BLOCK_GROUP_RAID1_MASK |
		       BTRFS_BLOCK_GROUP_RAID56_MASK |
		       BTRFS_BLOCK_GROUP_DUP)))
			जारी;
		/*
		 * Aव्योम allocating from un-mirrored block group अगर there are
		 * mirrored block groups.
		 */
		list_क्रम_each_entry(cache,
				&space_info->block_groups[BTRFS_RAID_RAID0],
				list)
			inc_block_group_ro(cache, 1);
		list_क्रम_each_entry(cache,
				&space_info->block_groups[BTRFS_RAID_SINGLE],
				list)
			inc_block_group_ro(cache, 1);
	पूर्ण

	btrfs_init_global_block_rsv(info);
	ret = check_chunk_block_group_mappings(info);
error:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक insert_block_group_item(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_block_group_item bgi;
	काष्ठा btrfs_root *root;
	काष्ठा btrfs_key key;

	spin_lock(&block_group->lock);
	btrfs_set_stack_block_group_used(&bgi, block_group->used);
	btrfs_set_stack_block_group_chunk_objectid(&bgi,
				BTRFS_FIRST_CHUNK_TREE_OBJECTID);
	btrfs_set_stack_block_group_flags(&bgi, block_group->flags);
	key.objectid = block_group->start;
	key.type = BTRFS_BLOCK_GROUP_ITEM_KEY;
	key.offset = block_group->length;
	spin_unlock(&block_group->lock);

	root = fs_info->extent_root;
	वापस btrfs_insert_item(trans, root, &key, &bgi, माप(bgi));
पूर्ण

व्योम btrfs_create_pending_block_groups(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_block_group *block_group;
	पूर्णांक ret = 0;

	अगर (!trans->can_flush_pending_bgs)
		वापस;

	जबतक (!list_empty(&trans->new_bgs)) अणु
		पूर्णांक index;

		block_group = list_first_entry(&trans->new_bgs,
					       काष्ठा btrfs_block_group,
					       bg_list);
		अगर (ret)
			जाओ next;

		index = btrfs_bg_flags_to_raid_index(block_group->flags);

		ret = insert_block_group_item(trans, block_group);
		अगर (ret)
			btrfs_पात_transaction(trans, ret);
		ret = btrfs_finish_chunk_alloc(trans, block_group->start,
					block_group->length);
		अगर (ret)
			btrfs_पात_transaction(trans, ret);
		add_block_group_मुक्त_space(trans, block_group);

		/*
		 * If we restriped during balance, we may have added a new raid
		 * type, so now add the sysfs entries when it is safe to करो so.
		 * We करोn't have to worry about locking here as it's handled in
		 * btrfs_sysfs_add_block_group_type.
		 */
		अगर (block_group->space_info->block_group_kobjs[index] == शून्य)
			btrfs_sysfs_add_block_group_type(block_group);

		/* Alपढ़ोy पातed the transaction अगर it failed. */
next:
		btrfs_delayed_refs_rsv_release(fs_info, 1);
		list_del_init(&block_group->bg_list);
	पूर्ण
	btrfs_trans_release_chunk_metadata(trans);
पूर्ण

पूर्णांक btrfs_make_block_group(काष्ठा btrfs_trans_handle *trans, u64 bytes_used,
			   u64 type, u64 chunk_offset, u64 size)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_block_group *cache;
	पूर्णांक ret;

	btrfs_set_log_full_commit(trans);

	cache = btrfs_create_block_group_cache(fs_info, chunk_offset);
	अगर (!cache)
		वापस -ENOMEM;

	cache->length = size;
	set_मुक्त_space_tree_thresholds(cache);
	cache->used = bytes_used;
	cache->flags = type;
	cache->last_byte_to_unpin = (u64)-1;
	cache->cached = BTRFS_CACHE_FINISHED;
	अगर (btrfs_fs_compat_ro(fs_info, FREE_SPACE_TREE))
		cache->needs_मुक्त_space = 1;

	ret = btrfs_load_block_group_zone_info(cache, true);
	अगर (ret) अणु
		btrfs_put_block_group(cache);
		वापस ret;
	पूर्ण

	ret = exclude_super_stripes(cache);
	अगर (ret) अणु
		/* We may have excluded something, so call this just in हाल */
		btrfs_मुक्त_excluded_extents(cache);
		btrfs_put_block_group(cache);
		वापस ret;
	पूर्ण

	add_new_मुक्त_space(cache, chunk_offset, chunk_offset + size);

	btrfs_मुक्त_excluded_extents(cache);

#अगर_घोषित CONFIG_BTRFS_DEBUG
	अगर (btrfs_should_fragment_मुक्त_space(cache)) अणु
		u64 new_bytes_used = size - bytes_used;

		bytes_used += new_bytes_used >> 1;
		fragment_मुक्त_space(cache);
	पूर्ण
#पूर्ण_अगर
	/*
	 * Ensure the corresponding space_info object is created and
	 * asचिन्हित to our block group. We want our bg to be added to the rbtree
	 * with its ->space_info set.
	 */
	cache->space_info = btrfs_find_space_info(fs_info, cache->flags);
	ASSERT(cache->space_info);

	ret = btrfs_add_block_group_cache(fs_info, cache);
	अगर (ret) अणु
		btrfs_हटाओ_मुक्त_space_cache(cache);
		btrfs_put_block_group(cache);
		वापस ret;
	पूर्ण

	/*
	 * Now that our block group has its ->space_info set and is inserted in
	 * the rbtree, update the space info's counters.
	 */
	trace_btrfs_add_block_group(fs_info, cache, 1);
	btrfs_update_space_info(fs_info, cache->flags, size, bytes_used,
				cache->bytes_super, 0, &cache->space_info);
	btrfs_update_global_block_rsv(fs_info);

	link_block_group(cache);

	list_add_tail(&cache->bg_list, &trans->new_bgs);
	trans->delayed_ref_updates++;
	btrfs_update_delayed_refs_rsv(trans);

	set_avail_alloc_bits(fs_info, type);
	वापस 0;
पूर्ण

/*
 * Mark one block group RO, can be called several बार क्रम the same block
 * group.
 *
 * @cache:		the destination block group
 * @करो_chunk_alloc:	whether need to करो chunk pre-allocation, this is to
 * 			ensure we still have some मुक्त space after marking this
 * 			block group RO.
 */
पूर्णांक btrfs_inc_block_group_ro(काष्ठा btrfs_block_group *cache,
			     bool करो_chunk_alloc)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा btrfs_trans_handle *trans;
	u64 alloc_flags;
	पूर्णांक ret;
	bool dirty_bg_running;

	करो अणु
		trans = btrfs_join_transaction(fs_info->extent_root);
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);

		dirty_bg_running = false;

		/*
		 * We're not allowed to set block groups पढ़ोonly after the dirty
		 * block group cache has started writing.  If it alपढ़ोy started,
		 * back off and let this transaction commit.
		 */
		mutex_lock(&fs_info->ro_block_group_mutex);
		अगर (test_bit(BTRFS_TRANS_सूचीTY_BG_RUN, &trans->transaction->flags)) अणु
			u64 transid = trans->transid;

			mutex_unlock(&fs_info->ro_block_group_mutex);
			btrfs_end_transaction(trans);

			ret = btrfs_रुको_क्रम_commit(fs_info, transid);
			अगर (ret)
				वापस ret;
			dirty_bg_running = true;
		पूर्ण
	पूर्ण जबतक (dirty_bg_running);

	अगर (करो_chunk_alloc) अणु
		/*
		 * If we are changing raid levels, try to allocate a
		 * corresponding block group with the new raid level.
		 */
		alloc_flags = btrfs_get_alloc_profile(fs_info, cache->flags);
		अगर (alloc_flags != cache->flags) अणु
			ret = btrfs_chunk_alloc(trans, alloc_flags,
						CHUNK_ALLOC_FORCE);
			/*
			 * ENOSPC is allowed here, we may have enough space
			 * alपढ़ोy allocated at the new raid level to carry on
			 */
			अगर (ret == -ENOSPC)
				ret = 0;
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	ret = inc_block_group_ro(cache, 0);
	अगर (!करो_chunk_alloc || ret == -ETXTBSY)
		जाओ unlock_out;
	अगर (!ret)
		जाओ out;
	alloc_flags = btrfs_get_alloc_profile(fs_info, cache->space_info->flags);
	ret = btrfs_chunk_alloc(trans, alloc_flags, CHUNK_ALLOC_FORCE);
	अगर (ret < 0)
		जाओ out;
	ret = inc_block_group_ro(cache, 0);
	अगर (ret == -ETXTBSY)
		जाओ unlock_out;
out:
	अगर (cache->flags & BTRFS_BLOCK_GROUP_SYSTEM) अणु
		alloc_flags = btrfs_get_alloc_profile(fs_info, cache->flags);
		mutex_lock(&fs_info->chunk_mutex);
		check_प्रणाली_chunk(trans, alloc_flags);
		mutex_unlock(&fs_info->chunk_mutex);
	पूर्ण
unlock_out:
	mutex_unlock(&fs_info->ro_block_group_mutex);

	btrfs_end_transaction(trans);
	वापस ret;
पूर्ण

व्योम btrfs_dec_block_group_ro(काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_space_info *sinfo = cache->space_info;
	u64 num_bytes;

	BUG_ON(!cache->ro);

	spin_lock(&sinfo->lock);
	spin_lock(&cache->lock);
	अगर (!--cache->ro) अणु
		अगर (btrfs_is_zoned(cache->fs_info)) अणु
			/* Migrate zone_unusable bytes back */
			cache->zone_unusable = cache->alloc_offset - cache->used;
			sinfo->bytes_zone_unusable += cache->zone_unusable;
			sinfo->bytes_पढ़ोonly -= cache->zone_unusable;
		पूर्ण
		num_bytes = cache->length - cache->reserved -
			    cache->pinned - cache->bytes_super -
			    cache->zone_unusable - cache->used;
		sinfo->bytes_पढ़ोonly -= num_bytes;
		list_del_init(&cache->ro_list);
	पूर्ण
	spin_unlock(&cache->lock);
	spin_unlock(&sinfo->lock);
पूर्ण

अटल पूर्णांक update_block_group_item(काष्ठा btrfs_trans_handle *trans,
				   काष्ठा btrfs_path *path,
				   काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret;
	काष्ठा btrfs_root *root = fs_info->extent_root;
	अचिन्हित दीर्घ bi;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_block_group_item bgi;
	काष्ठा btrfs_key key;

	key.objectid = cache->start;
	key.type = BTRFS_BLOCK_GROUP_ITEM_KEY;
	key.offset = cache->length;

	ret = btrfs_search_slot(trans, root, &key, path, 0, 1);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = -ENOENT;
		जाओ fail;
	पूर्ण

	leaf = path->nodes[0];
	bi = btrfs_item_ptr_offset(leaf, path->slots[0]);
	btrfs_set_stack_block_group_used(&bgi, cache->used);
	btrfs_set_stack_block_group_chunk_objectid(&bgi,
			BTRFS_FIRST_CHUNK_TREE_OBJECTID);
	btrfs_set_stack_block_group_flags(&bgi, cache->flags);
	ग_लिखो_extent_buffer(leaf, &bgi, bi, माप(bgi));
	btrfs_mark_buffer_dirty(leaf);
fail:
	btrfs_release_path(path);
	वापस ret;

पूर्ण

अटल पूर्णांक cache_save_setup(काष्ठा btrfs_block_group *block_group,
			    काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा inode *inode = शून्य;
	काष्ठा extent_changeset *data_reserved = शून्य;
	u64 alloc_hपूर्णांक = 0;
	पूर्णांक dcs = BTRFS_DC_ERROR;
	u64 num_pages = 0;
	पूर्णांक retries = 0;
	पूर्णांक ret = 0;

	अगर (!btrfs_test_opt(fs_info, SPACE_CACHE))
		वापस 0;

	/*
	 * If this block group is smaller than 100 megs करोn't bother caching the
	 * block group.
	 */
	अगर (block_group->length < (100 * SZ_1M)) अणु
		spin_lock(&block_group->lock);
		block_group->disk_cache_state = BTRFS_DC_WRITTEN;
		spin_unlock(&block_group->lock);
		वापस 0;
	पूर्ण

	अगर (TRANS_ABORTED(trans))
		वापस 0;
again:
	inode = lookup_मुक्त_space_inode(block_group, path);
	अगर (IS_ERR(inode) && PTR_ERR(inode) != -ENOENT) अणु
		ret = PTR_ERR(inode);
		btrfs_release_path(path);
		जाओ out;
	पूर्ण

	अगर (IS_ERR(inode)) अणु
		BUG_ON(retries);
		retries++;

		अगर (block_group->ro)
			जाओ out_मुक्त;

		ret = create_मुक्त_space_inode(trans, block_group, path);
		अगर (ret)
			जाओ out_मुक्त;
		जाओ again;
	पूर्ण

	/*
	 * We want to set the generation to 0, that way अगर anything goes wrong
	 * from here on out we know not to trust this cache when we load up next
	 * समय.
	 */
	BTRFS_I(inode)->generation = 0;
	ret = btrfs_update_inode(trans, root, BTRFS_I(inode));
	अगर (ret) अणु
		/*
		 * So theoretically we could recover from this, simply set the
		 * super cache generation to 0 so we know to invalidate the
		 * cache, but then we'd have to keep track of the block groups
		 * that fail this way so we know we _have_ to reset this cache
		 * beक्रमe the next commit or risk पढ़ोing stale cache.  So to
		 * limit our exposure to horrible edge हालs lets just पात the
		 * transaction, this only happens in really bad situations
		 * anyway.
		 */
		btrfs_पात_transaction(trans, ret);
		जाओ out_put;
	पूर्ण
	WARN_ON(ret);

	/* We've alपढ़ोy setup this transaction, go ahead and निकास */
	अगर (block_group->cache_generation == trans->transid &&
	    i_size_पढ़ो(inode)) अणु
		dcs = BTRFS_DC_SETUP;
		जाओ out_put;
	पूर्ण

	अगर (i_size_पढ़ो(inode) > 0) अणु
		ret = btrfs_check_trunc_cache_मुक्त_space(fs_info,
					&fs_info->global_block_rsv);
		अगर (ret)
			जाओ out_put;

		ret = btrfs_truncate_मुक्त_space_cache(trans, शून्य, inode);
		अगर (ret)
			जाओ out_put;
	पूर्ण

	spin_lock(&block_group->lock);
	अगर (block_group->cached != BTRFS_CACHE_FINISHED ||
	    !btrfs_test_opt(fs_info, SPACE_CACHE)) अणु
		/*
		 * करोn't bother trying to ग_लिखो stuff out _अगर_
		 * a) we're not cached,
		 * b) we're with nospace_cache mount option,
		 * c) we're with v2 space_cache (FREE_SPACE_TREE).
		 */
		dcs = BTRFS_DC_WRITTEN;
		spin_unlock(&block_group->lock);
		जाओ out_put;
	पूर्ण
	spin_unlock(&block_group->lock);

	/*
	 * We hit an ENOSPC when setting up the cache in this transaction, just
	 * skip करोing the setup, we've already cleared the cache so we're safe.
	 */
	अगर (test_bit(BTRFS_TRANS_CACHE_ENOSPC, &trans->transaction->flags)) अणु
		ret = -ENOSPC;
		जाओ out_put;
	पूर्ण

	/*
	 * Try to pपुनः_स्मृतिate enough space based on how big the block group is.
	 * Keep in mind this has to include any pinned space which could end up
	 * taking up quite a bit since it's not folded पूर्णांकo the other space
	 * cache.
	 */
	num_pages = भाग_u64(block_group->length, SZ_256M);
	अगर (!num_pages)
		num_pages = 1;

	num_pages *= 16;
	num_pages *= PAGE_SIZE;

	ret = btrfs_check_data_मुक्त_space(BTRFS_I(inode), &data_reserved, 0,
					  num_pages);
	अगर (ret)
		जाओ out_put;

	ret = btrfs_pपुनः_स्मृति_file_range_trans(inode, trans, 0, 0, num_pages,
					      num_pages, num_pages,
					      &alloc_hपूर्णांक);
	/*
	 * Our cache requires contiguous chunks so that we करोn't modअगरy a bunch
	 * of metadata or split extents when writing the cache out, which means
	 * we can enospc अगर we are heavily fragmented in addition to just normal
	 * out of space conditions.  So अगर we hit this just skip setting up any
	 * other block groups क्रम this transaction, maybe we'll unpin enough
	 * space the next समय around.
	 */
	अगर (!ret)
		dcs = BTRFS_DC_SETUP;
	अन्यथा अगर (ret == -ENOSPC)
		set_bit(BTRFS_TRANS_CACHE_ENOSPC, &trans->transaction->flags);

out_put:
	iput(inode);
out_मुक्त:
	btrfs_release_path(path);
out:
	spin_lock(&block_group->lock);
	अगर (!ret && dcs == BTRFS_DC_SETUP)
		block_group->cache_generation = trans->transid;
	block_group->disk_cache_state = dcs;
	spin_unlock(&block_group->lock);

	extent_changeset_मुक्त(data_reserved);
	वापस ret;
पूर्ण

पूर्णांक btrfs_setup_space_cache(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_block_group *cache, *पंचांगp;
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;
	काष्ठा btrfs_path *path;

	अगर (list_empty(&cur_trans->dirty_bgs) ||
	    !btrfs_test_opt(fs_info, SPACE_CACHE))
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/* Could add new block groups, use _safe just in हाल */
	list_क्रम_each_entry_safe(cache, पंचांगp, &cur_trans->dirty_bgs,
				 dirty_list) अणु
		अगर (cache->disk_cache_state == BTRFS_DC_CLEAR)
			cache_save_setup(cache, trans, path);
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस 0;
पूर्ण

/*
 * Transaction commit करोes final block group cache ग_लिखोback during a critical
 * section where nothing is allowed to change the FS.  This is required in
 * order क्रम the cache to actually match the block group, but can पूर्णांकroduce a
 * lot of latency पूर्णांकo the commit.
 *
 * So, btrfs_start_dirty_block_groups is here to kick off block group cache IO.
 * There's a chance we'll have to reकरो some of it अगर the block group changes
 * again during the commit, but it greatly reduces the commit latency by
 * getting rid of the easy block groups जबतक we're still allowing others to
 * join the commit.
 */
पूर्णांक btrfs_start_dirty_block_groups(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_block_group *cache;
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;
	पूर्णांक ret = 0;
	पूर्णांक should_put;
	काष्ठा btrfs_path *path = शून्य;
	LIST_HEAD(dirty);
	काष्ठा list_head *io = &cur_trans->io_bgs;
	पूर्णांक num_started = 0;
	पूर्णांक loops = 0;

	spin_lock(&cur_trans->dirty_bgs_lock);
	अगर (list_empty(&cur_trans->dirty_bgs)) अणु
		spin_unlock(&cur_trans->dirty_bgs_lock);
		वापस 0;
	पूर्ण
	list_splice_init(&cur_trans->dirty_bgs, &dirty);
	spin_unlock(&cur_trans->dirty_bgs_lock);

again:
	/* Make sure all the block groups on our dirty list actually exist */
	btrfs_create_pending_block_groups(trans);

	अगर (!path) अणु
		path = btrfs_alloc_path();
		अगर (!path) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * cache_ग_लिखो_mutex is here only to save us from balance or स्वतःmatic
	 * removal of empty block groups deleting this block group जबतक we are
	 * writing out the cache
	 */
	mutex_lock(&trans->transaction->cache_ग_लिखो_mutex);
	जबतक (!list_empty(&dirty)) अणु
		bool drop_reserve = true;

		cache = list_first_entry(&dirty, काष्ठा btrfs_block_group,
					 dirty_list);
		/*
		 * This can happen अगर something re-dirties a block group that
		 * is alपढ़ोy under IO.  Just रुको क्रम it to finish and then करो
		 * it all again
		 */
		अगर (!list_empty(&cache->io_list)) अणु
			list_del_init(&cache->io_list);
			btrfs_रुको_cache_io(trans, cache, path);
			btrfs_put_block_group(cache);
		पूर्ण


		/*
		 * btrfs_रुको_cache_io uses the cache->dirty_list to decide अगर
		 * it should update the cache_state.  Don't delete until after
		 * we रुको.
		 *
		 * Since we're not running in the commit critical section
		 * we need the dirty_bgs_lock to protect from update_block_group
		 */
		spin_lock(&cur_trans->dirty_bgs_lock);
		list_del_init(&cache->dirty_list);
		spin_unlock(&cur_trans->dirty_bgs_lock);

		should_put = 1;

		cache_save_setup(cache, trans, path);

		अगर (cache->disk_cache_state == BTRFS_DC_SETUP) अणु
			cache->io_ctl.inode = शून्य;
			ret = btrfs_ग_लिखो_out_cache(trans, cache, path);
			अगर (ret == 0 && cache->io_ctl.inode) अणु
				num_started++;
				should_put = 0;

				/*
				 * The cache_ग_लिखो_mutex is protecting the
				 * io_list, also refer to the definition of
				 * btrfs_transaction::io_bgs क्रम more details
				 */
				list_add_tail(&cache->io_list, io);
			पूर्ण अन्यथा अणु
				/*
				 * If we failed to ग_लिखो the cache, the
				 * generation will be bad and lअगरe goes on
				 */
				ret = 0;
			पूर्ण
		पूर्ण
		अगर (!ret) अणु
			ret = update_block_group_item(trans, path, cache);
			/*
			 * Our block group might still be attached to the list
			 * of new block groups in the transaction handle of some
			 * other task (काष्ठा btrfs_trans_handle->new_bgs). This
			 * means its block group item isn't yet in the extent
			 * tree. If this happens ignore the error, as we will
			 * try again later in the critical section of the
			 * transaction commit.
			 */
			अगर (ret == -ENOENT) अणु
				ret = 0;
				spin_lock(&cur_trans->dirty_bgs_lock);
				अगर (list_empty(&cache->dirty_list)) अणु
					list_add_tail(&cache->dirty_list,
						      &cur_trans->dirty_bgs);
					btrfs_get_block_group(cache);
					drop_reserve = false;
				पूर्ण
				spin_unlock(&cur_trans->dirty_bgs_lock);
			पूर्ण अन्यथा अगर (ret) अणु
				btrfs_पात_transaction(trans, ret);
			पूर्ण
		पूर्ण

		/* If it's not on the io list, we need to put the block group */
		अगर (should_put)
			btrfs_put_block_group(cache);
		अगर (drop_reserve)
			btrfs_delayed_refs_rsv_release(fs_info, 1);
		/*
		 * Aव्योम blocking other tasks क्रम too दीर्घ. It might even save
		 * us from writing caches क्रम block groups that are going to be
		 * हटाओd.
		 */
		mutex_unlock(&trans->transaction->cache_ग_लिखो_mutex);
		अगर (ret)
			जाओ out;
		mutex_lock(&trans->transaction->cache_ग_लिखो_mutex);
	पूर्ण
	mutex_unlock(&trans->transaction->cache_ग_लिखो_mutex);

	/*
	 * Go through delayed refs क्रम all the stuff we've just kicked off
	 * and then loop back (just once)
	 */
	अगर (!ret)
		ret = btrfs_run_delayed_refs(trans, 0);
	अगर (!ret && loops == 0) अणु
		loops++;
		spin_lock(&cur_trans->dirty_bgs_lock);
		list_splice_init(&cur_trans->dirty_bgs, &dirty);
		/*
		 * dirty_bgs_lock protects us from concurrent block group
		 * deletes too (not just cache_ग_लिखो_mutex).
		 */
		अगर (!list_empty(&dirty)) अणु
			spin_unlock(&cur_trans->dirty_bgs_lock);
			जाओ again;
		पूर्ण
		spin_unlock(&cur_trans->dirty_bgs_lock);
	पूर्ण
out:
	अगर (ret < 0) अणु
		spin_lock(&cur_trans->dirty_bgs_lock);
		list_splice_init(&dirty, &cur_trans->dirty_bgs);
		spin_unlock(&cur_trans->dirty_bgs_lock);
		btrfs_cleanup_dirty_bgs(cur_trans, fs_info);
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_ग_लिखो_dirty_block_groups(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_block_group *cache;
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;
	पूर्णांक ret = 0;
	पूर्णांक should_put;
	काष्ठा btrfs_path *path;
	काष्ठा list_head *io = &cur_trans->io_bgs;
	पूर्णांक num_started = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/*
	 * Even though we are in the critical section of the transaction commit,
	 * we can still have concurrent tasks adding elements to this
	 * transaction's list of dirty block groups. These tasks correspond to
	 * endio मुक्त space workers started when ग_लिखोback finishes क्रम a
	 * space cache, which run inode.c:btrfs_finish_ordered_io(), and can
	 * allocate new block groups as a result of COWing nodes of the root
	 * tree when updating the मुक्त space inode. The ग_लिखोback क्रम the space
	 * caches is triggered by an earlier call to
	 * btrfs_start_dirty_block_groups() and iterations of the following
	 * loop.
	 * Also we want to करो the cache_save_setup first and then run the
	 * delayed refs to make sure we have the best chance at करोing this all
	 * in one shot.
	 */
	spin_lock(&cur_trans->dirty_bgs_lock);
	जबतक (!list_empty(&cur_trans->dirty_bgs)) अणु
		cache = list_first_entry(&cur_trans->dirty_bgs,
					 काष्ठा btrfs_block_group,
					 dirty_list);

		/*
		 * This can happen अगर cache_save_setup re-dirties a block group
		 * that is alपढ़ोy under IO.  Just रुको क्रम it to finish and
		 * then करो it all again
		 */
		अगर (!list_empty(&cache->io_list)) अणु
			spin_unlock(&cur_trans->dirty_bgs_lock);
			list_del_init(&cache->io_list);
			btrfs_रुको_cache_io(trans, cache, path);
			btrfs_put_block_group(cache);
			spin_lock(&cur_trans->dirty_bgs_lock);
		पूर्ण

		/*
		 * Don't remove from the dirty list until after we've रुकोed on
		 * any pending IO
		 */
		list_del_init(&cache->dirty_list);
		spin_unlock(&cur_trans->dirty_bgs_lock);
		should_put = 1;

		cache_save_setup(cache, trans, path);

		अगर (!ret)
			ret = btrfs_run_delayed_refs(trans,
						     (अचिन्हित दीर्घ) -1);

		अगर (!ret && cache->disk_cache_state == BTRFS_DC_SETUP) अणु
			cache->io_ctl.inode = शून्य;
			ret = btrfs_ग_लिखो_out_cache(trans, cache, path);
			अगर (ret == 0 && cache->io_ctl.inode) अणु
				num_started++;
				should_put = 0;
				list_add_tail(&cache->io_list, io);
			पूर्ण अन्यथा अणु
				/*
				 * If we failed to ग_लिखो the cache, the
				 * generation will be bad and lअगरe goes on
				 */
				ret = 0;
			पूर्ण
		पूर्ण
		अगर (!ret) अणु
			ret = update_block_group_item(trans, path, cache);
			/*
			 * One of the मुक्त space endio workers might have
			 * created a new block group जबतक updating a मुक्त space
			 * cache's inode (at inode.c:btrfs_finish_ordered_io())
			 * and hasn't released its transaction handle yet, in
			 * which हाल the new block group is still attached to
			 * its transaction handle and its creation has not
			 * finished yet (no block group item in the extent tree
			 * yet, etc). If this is the हाल, रुको क्रम all मुक्त
			 * space endio workers to finish and retry. This is a
			 * very rare हाल so no need क्रम a more efficient and
			 * complex approach.
			 */
			अगर (ret == -ENOENT) अणु
				रुको_event(cur_trans->ग_लिखोr_रुको,
				   atomic_पढ़ो(&cur_trans->num_ग_लिखोrs) == 1);
				ret = update_block_group_item(trans, path, cache);
			पूर्ण
			अगर (ret)
				btrfs_पात_transaction(trans, ret);
		पूर्ण

		/* If its not on the io list, we need to put the block group */
		अगर (should_put)
			btrfs_put_block_group(cache);
		btrfs_delayed_refs_rsv_release(fs_info, 1);
		spin_lock(&cur_trans->dirty_bgs_lock);
	पूर्ण
	spin_unlock(&cur_trans->dirty_bgs_lock);

	/*
	 * Refer to the definition of io_bgs member क्रम details why it's safe
	 * to use it without any locking
	 */
	जबतक (!list_empty(io)) अणु
		cache = list_first_entry(io, काष्ठा btrfs_block_group,
					 io_list);
		list_del_init(&cache->io_list);
		btrfs_रुको_cache_io(trans, cache, path);
		btrfs_put_block_group(cache);
	पूर्ण

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_update_block_group(काष्ठा btrfs_trans_handle *trans,
			     u64 bytenr, u64 num_bytes, पूर्णांक alloc)
अणु
	काष्ठा btrfs_fs_info *info = trans->fs_info;
	काष्ठा btrfs_block_group *cache = शून्य;
	u64 total = num_bytes;
	u64 old_val;
	u64 byte_in_group;
	पूर्णांक factor;
	पूर्णांक ret = 0;

	/* Block accounting क्रम super block */
	spin_lock(&info->delalloc_root_lock);
	old_val = btrfs_super_bytes_used(info->super_copy);
	अगर (alloc)
		old_val += num_bytes;
	अन्यथा
		old_val -= num_bytes;
	btrfs_set_super_bytes_used(info->super_copy, old_val);
	spin_unlock(&info->delalloc_root_lock);

	जबतक (total) अणु
		cache = btrfs_lookup_block_group(info, bytenr);
		अगर (!cache) अणु
			ret = -ENOENT;
			अवरोध;
		पूर्ण
		factor = btrfs_bg_type_to_factor(cache->flags);

		/*
		 * If this block group has मुक्त space cache written out, we
		 * need to make sure to load it अगर we are removing space.  This
		 * is because we need the unpinning stage to actually add the
		 * space back to the block group, otherwise we will leak space.
		 */
		अगर (!alloc && !btrfs_block_group_करोne(cache))
			btrfs_cache_block_group(cache, 1);

		byte_in_group = bytenr - cache->start;
		WARN_ON(byte_in_group > cache->length);

		spin_lock(&cache->space_info->lock);
		spin_lock(&cache->lock);

		अगर (btrfs_test_opt(info, SPACE_CACHE) &&
		    cache->disk_cache_state < BTRFS_DC_CLEAR)
			cache->disk_cache_state = BTRFS_DC_CLEAR;

		old_val = cache->used;
		num_bytes = min(total, cache->length - byte_in_group);
		अगर (alloc) अणु
			old_val += num_bytes;
			cache->used = old_val;
			cache->reserved -= num_bytes;
			cache->space_info->bytes_reserved -= num_bytes;
			cache->space_info->bytes_used += num_bytes;
			cache->space_info->disk_used += num_bytes * factor;
			spin_unlock(&cache->lock);
			spin_unlock(&cache->space_info->lock);
		पूर्ण अन्यथा अणु
			old_val -= num_bytes;
			cache->used = old_val;
			cache->pinned += num_bytes;
			btrfs_space_info_update_bytes_pinned(info,
					cache->space_info, num_bytes);
			cache->space_info->bytes_used -= num_bytes;
			cache->space_info->disk_used -= num_bytes * factor;
			spin_unlock(&cache->lock);
			spin_unlock(&cache->space_info->lock);

			__btrfs_mod_total_bytes_pinned(cache->space_info,
						       num_bytes);
			set_extent_dirty(&trans->transaction->pinned_extents,
					 bytenr, bytenr + num_bytes - 1,
					 GFP_NOFS | __GFP_NOFAIL);
		पूर्ण

		spin_lock(&trans->transaction->dirty_bgs_lock);
		अगर (list_empty(&cache->dirty_list)) अणु
			list_add_tail(&cache->dirty_list,
				      &trans->transaction->dirty_bgs);
			trans->delayed_ref_updates++;
			btrfs_get_block_group(cache);
		पूर्ण
		spin_unlock(&trans->transaction->dirty_bgs_lock);

		/*
		 * No दीर्घer have used bytes in this block group, queue it क्रम
		 * deletion. We करो this after adding the block group to the
		 * dirty list to aव्योम races between cleaner kthपढ़ो and space
		 * cache ग_लिखोout.
		 */
		अगर (!alloc && old_val == 0) अणु
			अगर (!btrfs_test_opt(info, DISCARD_ASYNC))
				btrfs_mark_bg_unused(cache);
		पूर्ण

		btrfs_put_block_group(cache);
		total -= num_bytes;
		bytenr += num_bytes;
	पूर्ण

	/* Modअगरied block groups are accounted क्रम in the delayed_refs_rsv. */
	btrfs_update_delayed_refs_rsv(trans);
	वापस ret;
पूर्ण

/**
 * btrfs_add_reserved_bytes - update the block_group and space info counters
 * @cache:	The cache we are manipulating
 * @ram_bytes:  The number of bytes of file content, and will be same to
 *              @num_bytes except क्रम the compress path.
 * @num_bytes:	The number of bytes in question
 * @delalloc:   The blocks are allocated क्रम the delalloc ग_लिखो
 *
 * This is called by the allocator when it reserves space. If this is a
 * reservation and the block group has become पढ़ो only we cannot make the
 * reservation and वापस -EAGAIN, otherwise this function always succeeds.
 */
पूर्णांक btrfs_add_reserved_bytes(काष्ठा btrfs_block_group *cache,
			     u64 ram_bytes, u64 num_bytes, पूर्णांक delalloc)
अणु
	काष्ठा btrfs_space_info *space_info = cache->space_info;
	पूर्णांक ret = 0;

	spin_lock(&space_info->lock);
	spin_lock(&cache->lock);
	अगर (cache->ro) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		cache->reserved += num_bytes;
		space_info->bytes_reserved += num_bytes;
		trace_btrfs_space_reservation(cache->fs_info, "space_info",
					      space_info->flags, num_bytes, 1);
		btrfs_space_info_update_bytes_may_use(cache->fs_info,
						      space_info, -ram_bytes);
		अगर (delalloc)
			cache->delalloc_bytes += num_bytes;

		/*
		 * Compression can use less space than we reserved, so wake
		 * tickets अगर that happens
		 */
		अगर (num_bytes < ram_bytes)
			btrfs_try_granting_tickets(cache->fs_info, space_info);
	पूर्ण
	spin_unlock(&cache->lock);
	spin_unlock(&space_info->lock);
	वापस ret;
पूर्ण

/**
 * btrfs_मुक्त_reserved_bytes - update the block_group and space info counters
 * @cache:      The cache we are manipulating
 * @num_bytes:  The number of bytes in question
 * @delalloc:   The blocks are allocated क्रम the delalloc ग_लिखो
 *
 * This is called by somebody who is मुक्तing space that was never actually used
 * on disk.  For example अगर you reserve some space क्रम a new leaf in transaction
 * A and beक्रमe transaction A commits you मुक्त that leaf, you call this with
 * reserve set to 0 in order to clear the reservation.
 */
व्योम btrfs_मुक्त_reserved_bytes(काष्ठा btrfs_block_group *cache,
			       u64 num_bytes, पूर्णांक delalloc)
अणु
	काष्ठा btrfs_space_info *space_info = cache->space_info;

	spin_lock(&space_info->lock);
	spin_lock(&cache->lock);
	अगर (cache->ro)
		space_info->bytes_पढ़ोonly += num_bytes;
	cache->reserved -= num_bytes;
	space_info->bytes_reserved -= num_bytes;
	space_info->max_extent_size = 0;

	अगर (delalloc)
		cache->delalloc_bytes -= num_bytes;
	spin_unlock(&cache->lock);

	btrfs_try_granting_tickets(cache->fs_info, space_info);
	spin_unlock(&space_info->lock);
पूर्ण

अटल व्योम क्रमce_metadata_allocation(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा list_head *head = &info->space_info;
	काष्ठा btrfs_space_info *found;

	list_क्रम_each_entry(found, head, list) अणु
		अगर (found->flags & BTRFS_BLOCK_GROUP_METADATA)
			found->क्रमce_alloc = CHUNK_ALLOC_FORCE;
	पूर्ण
पूर्ण

अटल पूर्णांक should_alloc_chunk(काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा btrfs_space_info *sinfo, पूर्णांक क्रमce)
अणु
	u64 bytes_used = btrfs_space_info_used(sinfo, false);
	u64 thresh;

	अगर (क्रमce == CHUNK_ALLOC_FORCE)
		वापस 1;

	/*
	 * in limited mode, we want to have some मुक्त space up to
	 * about 1% of the FS size.
	 */
	अगर (क्रमce == CHUNK_ALLOC_LIMITED) अणु
		thresh = btrfs_super_total_bytes(fs_info->super_copy);
		thresh = max_t(u64, SZ_64M, भाग_factor_fine(thresh, 1));

		अगर (sinfo->total_bytes - bytes_used < thresh)
			वापस 1;
	पूर्ण

	अगर (bytes_used + SZ_2M < भाग_factor(sinfo->total_bytes, 8))
		वापस 0;
	वापस 1;
पूर्ण

पूर्णांक btrfs_क्रमce_chunk_alloc(काष्ठा btrfs_trans_handle *trans, u64 type)
अणु
	u64 alloc_flags = btrfs_get_alloc_profile(trans->fs_info, type);

	वापस btrfs_chunk_alloc(trans, alloc_flags, CHUNK_ALLOC_FORCE);
पूर्ण

/*
 * If क्रमce is CHUNK_ALLOC_FORCE:
 *    - वापस 1 अगर it successfully allocates a chunk,
 *    - वापस errors including -ENOSPC otherwise.
 * If क्रमce is NOT CHUNK_ALLOC_FORCE:
 *    - वापस 0 अगर it करोesn't need to allocate a new chunk,
 *    - वापस 1 अगर it successfully allocates a chunk,
 *    - वापस errors including -ENOSPC otherwise.
 */
पूर्णांक btrfs_chunk_alloc(काष्ठा btrfs_trans_handle *trans, u64 flags,
		      क्रमागत btrfs_chunk_alloc_क्रमागत क्रमce)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_space_info *space_info;
	bool रुको_क्रम_alloc = false;
	bool should_alloc = false;
	पूर्णांक ret = 0;

	/* Don't re-enter if we're alपढ़ोy allocating a chunk */
	अगर (trans->allocating_chunk)
		वापस -ENOSPC;

	space_info = btrfs_find_space_info(fs_info, flags);
	ASSERT(space_info);

	करो अणु
		spin_lock(&space_info->lock);
		अगर (क्रमce < space_info->क्रमce_alloc)
			क्रमce = space_info->क्रमce_alloc;
		should_alloc = should_alloc_chunk(fs_info, space_info, क्रमce);
		अगर (space_info->full) अणु
			/* No more मुक्त physical space */
			अगर (should_alloc)
				ret = -ENOSPC;
			अन्यथा
				ret = 0;
			spin_unlock(&space_info->lock);
			वापस ret;
		पूर्ण अन्यथा अगर (!should_alloc) अणु
			spin_unlock(&space_info->lock);
			वापस 0;
		पूर्ण अन्यथा अगर (space_info->chunk_alloc) अणु
			/*
			 * Someone is alपढ़ोy allocating, so we need to block
			 * until this someone is finished and then loop to
			 * recheck अगर we should जारी with our allocation
			 * attempt.
			 */
			रुको_क्रम_alloc = true;
			spin_unlock(&space_info->lock);
			mutex_lock(&fs_info->chunk_mutex);
			mutex_unlock(&fs_info->chunk_mutex);
		पूर्ण अन्यथा अणु
			/* Proceed with allocation */
			space_info->chunk_alloc = 1;
			रुको_क्रम_alloc = false;
			spin_unlock(&space_info->lock);
		पूर्ण

		cond_resched();
	पूर्ण जबतक (रुको_क्रम_alloc);

	mutex_lock(&fs_info->chunk_mutex);
	trans->allocating_chunk = true;

	/*
	 * If we have mixed data/metadata chunks we want to make sure we keep
	 * allocating mixed chunks instead of inभागidual chunks.
	 */
	अगर (btrfs_mixed_space_info(space_info))
		flags |= (BTRFS_BLOCK_GROUP_DATA | BTRFS_BLOCK_GROUP_METADATA);

	/*
	 * अगर we're करोing a data chunk, go ahead and make sure that
	 * we keep a reasonable number of metadata chunks allocated in the
	 * FS as well.
	 */
	अगर (flags & BTRFS_BLOCK_GROUP_DATA && fs_info->metadata_ratio) अणु
		fs_info->data_chunk_allocations++;
		अगर (!(fs_info->data_chunk_allocations %
		      fs_info->metadata_ratio))
			क्रमce_metadata_allocation(fs_info);
	पूर्ण

	/*
	 * Check अगर we have enough space in SYSTEM chunk because we may need
	 * to update devices.
	 */
	check_प्रणाली_chunk(trans, flags);

	ret = btrfs_alloc_chunk(trans, flags);
	trans->allocating_chunk = false;

	spin_lock(&space_info->lock);
	अगर (ret < 0) अणु
		अगर (ret == -ENOSPC)
			space_info->full = 1;
		अन्यथा
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = 1;
		space_info->max_extent_size = 0;
	पूर्ण

	space_info->क्रमce_alloc = CHUNK_ALLOC_NO_FORCE;
out:
	space_info->chunk_alloc = 0;
	spin_unlock(&space_info->lock);
	mutex_unlock(&fs_info->chunk_mutex);
	/*
	 * When we allocate a new chunk we reserve space in the chunk block
	 * reserve to make sure we can COW nodes/leafs in the chunk tree or
	 * add new nodes/leafs to it अगर we end up needing to करो it when
	 * inserting the chunk item and updating device items as part of the
	 * second phase of chunk allocation, perक्रमmed by
	 * btrfs_finish_chunk_alloc(). So make sure we करोn't accumulate a
	 * large number of new block groups to create in our transaction
	 * handle's new_bgs list to aव्योम exhausting the chunk block reserve
	 * in extreme हालs - like having a single transaction create many new
	 * block groups when starting to ग_लिखो out the मुक्त space caches of all
	 * the block groups that were made dirty during the lअगरeसमय of the
	 * transaction.
	 */
	अगर (trans->chunk_bytes_reserved >= (u64)SZ_2M)
		btrfs_create_pending_block_groups(trans);

	वापस ret;
पूर्ण

अटल u64 get_profile_num_devs(काष्ठा btrfs_fs_info *fs_info, u64 type)
अणु
	u64 num_dev;

	num_dev = btrfs_raid_array[btrfs_bg_flags_to_raid_index(type)].devs_max;
	अगर (!num_dev)
		num_dev = fs_info->fs_devices->rw_devices;

	वापस num_dev;
पूर्ण

/*
 * Reserve space in the प्रणाली space क्रम allocating or removing a chunk
 */
व्योम check_प्रणाली_chunk(काष्ठा btrfs_trans_handle *trans, u64 type)
अणु
	काष्ठा btrfs_transaction *cur_trans = trans->transaction;
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_space_info *info;
	u64 left;
	u64 thresh;
	पूर्णांक ret = 0;
	u64 num_devs;

	/*
	 * Needed because we can end up allocating a प्रणाली chunk and क्रम an
	 * atomic and race मुक्त space reservation in the chunk block reserve.
	 */
	lockdep_निश्चित_held(&fs_info->chunk_mutex);

	info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_SYSTEM);
again:
	spin_lock(&info->lock);
	left = info->total_bytes - btrfs_space_info_used(info, true);
	spin_unlock(&info->lock);

	num_devs = get_profile_num_devs(fs_info, type);

	/* num_devs device items to update and 1 chunk item to add or हटाओ */
	thresh = btrfs_calc_metadata_size(fs_info, num_devs) +
		btrfs_calc_insert_metadata_size(fs_info, 1);

	अगर (left < thresh && btrfs_test_opt(fs_info, ENOSPC_DEBUG)) अणु
		btrfs_info(fs_info, "left=%llu, need=%llu, flags=%llu",
			   left, thresh, type);
		btrfs_dump_space_info(fs_info, info, 0, 0);
	पूर्ण

	अगर (left < thresh) अणु
		u64 flags = btrfs_प्रणाली_alloc_profile(fs_info);
		u64 reserved = atomic64_पढ़ो(&cur_trans->chunk_bytes_reserved);

		/*
		 * If there's not available space क्रम the chunk tree (प्रणाली
		 * space) and there are other tasks that reserved space क्रम
		 * creating a new प्रणाली block group, रुको क्रम them to complete
		 * the creation of their प्रणाली block group and release excess
		 * reserved space. We करो this because:
		 *
		 * *) We can end up allocating more प्रणाली chunks than necessary
		 *    when there are multiple tasks that are concurrently
		 *    allocating block groups, which can lead to exhaustion of
		 *    the प्रणाली array in the superblock;
		 *
		 * *) If we allocate extra and unnecessary प्रणाली block groups,
		 *    despite being empty क्रम a दीर्घ समय, and possibly क्रमever,
		 *    they end not being added to the list of unused block groups
		 *    because that typically happens only when deallocating the
		 *    last extent from a block group - which never happens since
		 *    we never allocate from them in the first place. The few
		 *    exceptions are when mounting a fileप्रणाली or running scrub,
		 *    which add unused block groups to the list of unused block
		 *    groups, to be deleted by the cleaner kthपढ़ो.
		 *    And even when they are added to the list of unused block
		 *    groups, it can take a दीर्घ समय until they get deleted,
		 *    since the cleaner kthपढ़ो might be sleeping or busy with
		 *    other work (deleting subvolumes, running delayed iमाला_दो,
		 *    defrag scheduling, etc);
		 *
		 * This is rare in practice, but can happen when too many tasks
		 * are allocating blocks groups in parallel (via fallocate())
		 * and beक्रमe the one that reserved space क्रम a new प्रणाली block
		 * group finishes the block group creation and releases the space
		 * reserved in excess (at btrfs_create_pending_block_groups()),
		 * other tasks end up here and see मुक्त प्रणाली space temporarily
		 * not enough क्रम updating the chunk tree.
		 *
		 * We unlock the chunk mutex beक्रमe रुकोing क्रम such tasks and
		 * lock it again after the रुको, otherwise we would deadlock.
		 * It is safe to करो so because allocating a प्रणाली chunk is the
		 * first thing करोne जबतक allocating a new block group.
		 */
		अगर (reserved > trans->chunk_bytes_reserved) अणु
			स्थिर u64 min_needed = reserved - thresh;

			mutex_unlock(&fs_info->chunk_mutex);
			रुको_event(cur_trans->chunk_reserve_रुको,
			   atomic64_पढ़ो(&cur_trans->chunk_bytes_reserved) <=
			   min_needed);
			mutex_lock(&fs_info->chunk_mutex);
			जाओ again;
		पूर्ण

		/*
		 * Ignore failure to create प्रणाली chunk. We might end up not
		 * needing it, as we might not need to COW all nodes/leafs from
		 * the paths we visit in the chunk tree (they were alपढ़ोy COWed
		 * or created in the current transaction क्रम example).
		 */
		ret = btrfs_alloc_chunk(trans, flags);
	पूर्ण

	अगर (!ret) अणु
		ret = btrfs_block_rsv_add(fs_info->chunk_root,
					  &fs_info->chunk_block_rsv,
					  thresh, BTRFS_RESERVE_NO_FLUSH);
		अगर (!ret) अणु
			atomic64_add(thresh, &cur_trans->chunk_bytes_reserved);
			trans->chunk_bytes_reserved += thresh;
		पूर्ण
	पूर्ण
पूर्ण

व्योम btrfs_put_block_group_cache(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा btrfs_block_group *block_group;
	u64 last = 0;

	जबतक (1) अणु
		काष्ठा inode *inode;

		block_group = btrfs_lookup_first_block_group(info, last);
		जबतक (block_group) अणु
			btrfs_रुको_block_group_cache_करोne(block_group);
			spin_lock(&block_group->lock);
			अगर (block_group->iref)
				अवरोध;
			spin_unlock(&block_group->lock);
			block_group = btrfs_next_block_group(block_group);
		पूर्ण
		अगर (!block_group) अणु
			अगर (last == 0)
				अवरोध;
			last = 0;
			जारी;
		पूर्ण

		inode = block_group->inode;
		block_group->iref = 0;
		block_group->inode = शून्य;
		spin_unlock(&block_group->lock);
		ASSERT(block_group->io_ctl.inode == शून्य);
		iput(inode);
		last = block_group->start + block_group->length;
		btrfs_put_block_group(block_group);
	पूर्ण
पूर्ण

/*
 * Must be called only after stopping all workers, since we could have block
 * group caching kthपढ़ोs running, and thereक्रमe they could race with us अगर we
 * मुक्तd the block groups beक्रमe stopping them.
 */
पूर्णांक btrfs_मुक्त_block_groups(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा btrfs_block_group *block_group;
	काष्ठा btrfs_space_info *space_info;
	काष्ठा btrfs_caching_control *caching_ctl;
	काष्ठा rb_node *n;

	spin_lock(&info->block_group_cache_lock);
	जबतक (!list_empty(&info->caching_block_groups)) अणु
		caching_ctl = list_entry(info->caching_block_groups.next,
					 काष्ठा btrfs_caching_control, list);
		list_del(&caching_ctl->list);
		btrfs_put_caching_control(caching_ctl);
	पूर्ण
	spin_unlock(&info->block_group_cache_lock);

	spin_lock(&info->unused_bgs_lock);
	जबतक (!list_empty(&info->unused_bgs)) अणु
		block_group = list_first_entry(&info->unused_bgs,
					       काष्ठा btrfs_block_group,
					       bg_list);
		list_del_init(&block_group->bg_list);
		btrfs_put_block_group(block_group);
	पूर्ण
	spin_unlock(&info->unused_bgs_lock);

	spin_lock(&info->unused_bgs_lock);
	जबतक (!list_empty(&info->reclaim_bgs)) अणु
		block_group = list_first_entry(&info->reclaim_bgs,
					       काष्ठा btrfs_block_group,
					       bg_list);
		list_del_init(&block_group->bg_list);
		btrfs_put_block_group(block_group);
	पूर्ण
	spin_unlock(&info->unused_bgs_lock);

	spin_lock(&info->block_group_cache_lock);
	जबतक ((n = rb_last(&info->block_group_cache_tree)) != शून्य) अणु
		block_group = rb_entry(n, काष्ठा btrfs_block_group,
				       cache_node);
		rb_erase(&block_group->cache_node,
			 &info->block_group_cache_tree);
		RB_CLEAR_NODE(&block_group->cache_node);
		spin_unlock(&info->block_group_cache_lock);

		करोwn_ग_लिखो(&block_group->space_info->groups_sem);
		list_del(&block_group->list);
		up_ग_लिखो(&block_group->space_info->groups_sem);

		/*
		 * We haven't cached this block group, which means we could
		 * possibly have excluded extents on this block group.
		 */
		अगर (block_group->cached == BTRFS_CACHE_NO ||
		    block_group->cached == BTRFS_CACHE_ERROR)
			btrfs_मुक्त_excluded_extents(block_group);

		btrfs_हटाओ_मुक्त_space_cache(block_group);
		ASSERT(block_group->cached != BTRFS_CACHE_STARTED);
		ASSERT(list_empty(&block_group->dirty_list));
		ASSERT(list_empty(&block_group->io_list));
		ASSERT(list_empty(&block_group->bg_list));
		ASSERT(refcount_पढ़ो(&block_group->refs) == 1);
		ASSERT(block_group->swap_extents == 0);
		btrfs_put_block_group(block_group);

		spin_lock(&info->block_group_cache_lock);
	पूर्ण
	spin_unlock(&info->block_group_cache_lock);

	btrfs_release_global_block_rsv(info);

	जबतक (!list_empty(&info->space_info)) अणु
		space_info = list_entry(info->space_info.next,
					काष्ठा btrfs_space_info,
					list);

		/*
		 * Do not hide this behind enospc_debug, this is actually
		 * important and indicates a real bug अगर this happens.
		 */
		अगर (WARN_ON(space_info->bytes_pinned > 0 ||
			    space_info->bytes_reserved > 0 ||
			    space_info->bytes_may_use > 0))
			btrfs_dump_space_info(info, space_info, 0, 0);
		WARN_ON(space_info->reclaim_size > 0);
		list_del(&space_info->list);
		btrfs_sysfs_हटाओ_space_info(space_info);
	पूर्ण
	वापस 0;
पूर्ण

व्योम btrfs_मुक्तze_block_group(काष्ठा btrfs_block_group *cache)
अणु
	atomic_inc(&cache->frozen);
पूर्ण

व्योम btrfs_unमुक्तze_block_group(काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;
	काष्ठा extent_map_tree *em_tree;
	काष्ठा extent_map *em;
	bool cleanup;

	spin_lock(&block_group->lock);
	cleanup = (atomic_dec_and_test(&block_group->frozen) &&
		   block_group->हटाओd);
	spin_unlock(&block_group->lock);

	अगर (cleanup) अणु
		em_tree = &fs_info->mapping_tree;
		ग_लिखो_lock(&em_tree->lock);
		em = lookup_extent_mapping(em_tree, block_group->start,
					   1);
		BUG_ON(!em); /* logic error, can't happen */
		हटाओ_extent_mapping(em_tree, em);
		ग_लिखो_unlock(&em_tree->lock);

		/* once क्रम us and once क्रम the tree */
		मुक्त_extent_map(em);
		मुक्त_extent_map(em);

		/*
		 * We may have left one मुक्त space entry and other possible
		 * tasks trimming this block group have left 1 entry each one.
		 * Free them अगर any.
		 */
		__btrfs_हटाओ_मुक्त_space_cache(block_group->मुक्त_space_ctl);
	पूर्ण
पूर्ण

bool btrfs_inc_block_group_swap_extents(काष्ठा btrfs_block_group *bg)
अणु
	bool ret = true;

	spin_lock(&bg->lock);
	अगर (bg->ro)
		ret = false;
	अन्यथा
		bg->swap_extents++;
	spin_unlock(&bg->lock);

	वापस ret;
पूर्ण

व्योम btrfs_dec_block_group_swap_extents(काष्ठा btrfs_block_group *bg, पूर्णांक amount)
अणु
	spin_lock(&bg->lock);
	ASSERT(!bg->ro);
	ASSERT(bg->swap_extents >= amount);
	bg->swap_extents -= amount;
	spin_unlock(&bg->lock);
पूर्ण
