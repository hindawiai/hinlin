<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_BLOCK_GROUP_H
#घोषणा BTRFS_BLOCK_GROUP_H

#समावेश "free-space-cache.h"

क्रमागत btrfs_disk_cache_state अणु
	BTRFS_DC_WRITTEN,
	BTRFS_DC_ERROR,
	BTRFS_DC_CLEAR,
	BTRFS_DC_SETUP,
पूर्ण;

/*
 * This describes the state of the block_group क्रम async discard.  This is due
 * to the two pass nature of it where extent discarding is prioritized over
 * biपंचांगap discarding.  BTRFS_DISCARD_RESET_CURSOR is set when we are resetting
 * between lists to prevent contention क्रम discard state variables
 * (eg. discard_cursor).
 */
क्रमागत btrfs_discard_state अणु
	BTRFS_DISCARD_EXTENTS,
	BTRFS_DISCARD_BITMAPS,
	BTRFS_DISCARD_RESET_CURSOR,
पूर्ण;

/*
 * Control flags क्रम करो_chunk_alloc's क्रमce field CHUNK_ALLOC_NO_FORCE means to
 * only allocate a chunk अगर we really need one.
 *
 * CHUNK_ALLOC_LIMITED means to only try and allocate one अगर we have very few
 * chunks alपढ़ोy allocated.  This is used as part of the clustering code to
 * help make sure we have a good pool of storage to cluster in, without filling
 * the FS with empty chunks
 *
 * CHUNK_ALLOC_FORCE means it must try to allocate one
 */
क्रमागत btrfs_chunk_alloc_क्रमागत अणु
	CHUNK_ALLOC_NO_FORCE,
	CHUNK_ALLOC_LIMITED,
	CHUNK_ALLOC_FORCE,
पूर्ण;

काष्ठा btrfs_caching_control अणु
	काष्ठा list_head list;
	काष्ठा mutex mutex;
	रुको_queue_head_t रुको;
	काष्ठा btrfs_work work;
	काष्ठा btrfs_block_group *block_group;
	u64 progress;
	refcount_t count;
पूर्ण;

/* Once caching_thपढ़ो() finds this much मुक्त space, it will wake up रुकोers. */
#घोषणा CACHING_CTL_WAKE_UP SZ_2M

काष्ठा btrfs_block_group अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा inode *inode;
	spinlock_t lock;
	u64 start;
	u64 length;
	u64 pinned;
	u64 reserved;
	u64 used;
	u64 delalloc_bytes;
	u64 bytes_super;
	u64 flags;
	u64 cache_generation;

	/*
	 * If the मुक्त space extent count exceeds this number, convert the block
	 * group to biपंचांगaps.
	 */
	u32 biपंचांगap_high_thresh;

	/*
	 * If the मुक्त space extent count drops below this number, convert the
	 * block group back to extents.
	 */
	u32 biपंचांगap_low_thresh;

	/*
	 * It is just used क्रम the delayed data space allocation because
	 * only the data space allocation and the relative metadata update
	 * can be करोne cross the transaction.
	 */
	काष्ठा rw_semaphore data_rwsem;

	/* For raid56, this is a full stripe, without parity */
	अचिन्हित दीर्घ full_stripe_len;

	अचिन्हित पूर्णांक ro;
	अचिन्हित पूर्णांक iref:1;
	अचिन्हित पूर्णांक has_caching_ctl:1;
	अचिन्हित पूर्णांक हटाओd:1;
	अचिन्हित पूर्णांक to_copy:1;
	अचिन्हित पूर्णांक relocating_repair:1;

	पूर्णांक disk_cache_state;

	/* Cache tracking stuff */
	पूर्णांक cached;
	काष्ठा btrfs_caching_control *caching_ctl;
	u64 last_byte_to_unpin;

	काष्ठा btrfs_space_info *space_info;

	/* Free space cache stuff */
	काष्ठा btrfs_मुक्त_space_ctl *मुक्त_space_ctl;

	/* Block group cache stuff */
	काष्ठा rb_node cache_node;

	/* For block groups in the same raid type */
	काष्ठा list_head list;

	refcount_t refs;

	/*
	 * List of काष्ठा btrfs_मुक्त_clusters क्रम this block group.
	 * Today it will only have one thing on it, but that may change
	 */
	काष्ठा list_head cluster_list;

	/* For delayed block group creation or deletion of empty block groups */
	काष्ठा list_head bg_list;

	/* For पढ़ो-only block groups */
	काष्ठा list_head ro_list;

	/*
	 * When non-zero it means the block group's logical address and its
	 * device extents can not be reused क्रम future block group allocations
	 * until the counter goes करोwn to 0. This is to prevent them from being
	 * reused जबतक some task is still using the block group after it was
	 * deleted - we want to make sure they can only be reused क्रम new block
	 * groups after that task is करोne with the deleted block group.
	 */
	atomic_t frozen;

	/* For discard operations */
	काष्ठा list_head discard_list;
	पूर्णांक discard_index;
	u64 discard_eligible_समय;
	u64 discard_cursor;
	क्रमागत btrfs_discard_state discard_state;

	/* For dirty block groups */
	काष्ठा list_head dirty_list;
	काष्ठा list_head io_list;

	काष्ठा btrfs_io_ctl io_ctl;

	/*
	 * Incremented when करोing extent allocations and holding a पढ़ो lock
	 * on the space_info's groups_sem semaphore.
	 * Decremented when an ordered extent that represents an IO against this
	 * block group's range is created (after it's added to its inode's
	 * root's list of ordered extents) or immediately after the allocation
	 * अगर it's a metadata extent or fallocate extent (क्रम these हालs we
	 * करोn't create ordered extents).
	 */
	atomic_t reservations;

	/*
	 * Incremented जबतक holding the spinlock *lock* by a task checking अगर
	 * it can perक्रमm a nocow ग_लिखो (incremented अगर the value क्रम the *ro*
	 * field is 0). Decremented by such tasks once they create an ordered
	 * extent or beक्रमe that अगर some error happens beक्रमe reaching that step.
	 * This is to prevent races between block group relocation and nocow
	 * ग_लिखोs through direct IO.
	 */
	atomic_t nocow_ग_लिखोrs;

	/* Lock क्रम मुक्त space tree operations. */
	काष्ठा mutex मुक्त_space_lock;

	/*
	 * Does the block group need to be added to the मुक्त space tree?
	 * Protected by मुक्त_space_lock.
	 */
	पूर्णांक needs_मुक्त_space;

	/* Flag indicating this block group is placed on a sequential zone */
	bool seq_zone;

	/*
	 * Number of extents in this block group used क्रम swap files.
	 * All accesses रक्षित by the spinlock 'lock'.
	 */
	पूर्णांक swap_extents;

	/* Record locked full stripes क्रम RAID5/6 block group */
	काष्ठा btrfs_full_stripe_locks_tree full_stripe_locks_root;

	/*
	 * Allocation offset क्रम the block group to implement sequential
	 * allocation. This is used only on a zoned fileप्रणाली.
	 */
	u64 alloc_offset;
	u64 zone_unusable;
	u64 meta_ग_लिखो_poपूर्णांकer;
पूर्ण;

अटल अंतरभूत u64 btrfs_block_group_end(काष्ठा btrfs_block_group *block_group)
अणु
	वापस (block_group->start + block_group->length);
पूर्ण

अटल अंतरभूत bool btrfs_is_block_group_data_only(
					काष्ठा btrfs_block_group *block_group)
अणु
	/*
	 * In mixed mode the fragmentation is expected to be high, lowering the
	 * efficiency, so only proper data block groups are considered.
	 */
	वापस (block_group->flags & BTRFS_BLOCK_GROUP_DATA) &&
	       !(block_group->flags & BTRFS_BLOCK_GROUP_METADATA);
पूर्ण

#अगर_घोषित CONFIG_BTRFS_DEBUG
अटल अंतरभूत पूर्णांक btrfs_should_fragment_मुक्त_space(
		काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_fs_info *fs_info = block_group->fs_info;

	वापस (btrfs_test_opt(fs_info, FRAGMENT_METADATA) &&
		block_group->flags & BTRFS_BLOCK_GROUP_METADATA) ||
	       (btrfs_test_opt(fs_info, FRAGMENT_DATA) &&
		block_group->flags &  BTRFS_BLOCK_GROUP_DATA);
पूर्ण
#पूर्ण_अगर

काष्ठा btrfs_block_group *btrfs_lookup_first_block_group(
		काष्ठा btrfs_fs_info *info, u64 bytenr);
काष्ठा btrfs_block_group *btrfs_lookup_block_group(
		काष्ठा btrfs_fs_info *info, u64 bytenr);
काष्ठा btrfs_block_group *btrfs_next_block_group(
		काष्ठा btrfs_block_group *cache);
व्योम btrfs_get_block_group(काष्ठा btrfs_block_group *cache);
व्योम btrfs_put_block_group(काष्ठा btrfs_block_group *cache);
व्योम btrfs_dec_block_group_reservations(काष्ठा btrfs_fs_info *fs_info,
					स्थिर u64 start);
व्योम btrfs_रुको_block_group_reservations(काष्ठा btrfs_block_group *bg);
bool btrfs_inc_nocow_ग_लिखोrs(काष्ठा btrfs_fs_info *fs_info, u64 bytenr);
व्योम btrfs_dec_nocow_ग_लिखोrs(काष्ठा btrfs_fs_info *fs_info, u64 bytenr);
व्योम btrfs_रुको_nocow_ग_लिखोrs(काष्ठा btrfs_block_group *bg);
व्योम btrfs_रुको_block_group_cache_progress(काष्ठा btrfs_block_group *cache,
				           u64 num_bytes);
पूर्णांक btrfs_रुको_block_group_cache_करोne(काष्ठा btrfs_block_group *cache);
पूर्णांक btrfs_cache_block_group(काष्ठा btrfs_block_group *cache,
			    पूर्णांक load_cache_only);
व्योम btrfs_put_caching_control(काष्ठा btrfs_caching_control *ctl);
काष्ठा btrfs_caching_control *btrfs_get_caching_control(
		काष्ठा btrfs_block_group *cache);
u64 add_new_मुक्त_space(काष्ठा btrfs_block_group *block_group,
		       u64 start, u64 end);
काष्ठा btrfs_trans_handle *btrfs_start_trans_हटाओ_block_group(
				काष्ठा btrfs_fs_info *fs_info,
				स्थिर u64 chunk_offset);
पूर्णांक btrfs_हटाओ_block_group(काष्ठा btrfs_trans_handle *trans,
			     u64 group_start, काष्ठा extent_map *em);
व्योम btrfs_delete_unused_bgs(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_mark_bg_unused(काष्ठा btrfs_block_group *bg);
व्योम btrfs_reclaim_bgs_work(काष्ठा work_काष्ठा *work);
व्योम btrfs_reclaim_bgs(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_mark_bg_to_reclaim(काष्ठा btrfs_block_group *bg);
पूर्णांक btrfs_पढ़ो_block_groups(काष्ठा btrfs_fs_info *info);
पूर्णांक btrfs_make_block_group(काष्ठा btrfs_trans_handle *trans, u64 bytes_used,
			   u64 type, u64 chunk_offset, u64 size);
व्योम btrfs_create_pending_block_groups(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_inc_block_group_ro(काष्ठा btrfs_block_group *cache,
			     bool करो_chunk_alloc);
व्योम btrfs_dec_block_group_ro(काष्ठा btrfs_block_group *cache);
पूर्णांक btrfs_start_dirty_block_groups(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_ग_लिखो_dirty_block_groups(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_setup_space_cache(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_update_block_group(काष्ठा btrfs_trans_handle *trans,
			     u64 bytenr, u64 num_bytes, पूर्णांक alloc);
पूर्णांक btrfs_add_reserved_bytes(काष्ठा btrfs_block_group *cache,
			     u64 ram_bytes, u64 num_bytes, पूर्णांक delalloc);
व्योम btrfs_मुक्त_reserved_bytes(काष्ठा btrfs_block_group *cache,
			       u64 num_bytes, पूर्णांक delalloc);
पूर्णांक btrfs_chunk_alloc(काष्ठा btrfs_trans_handle *trans, u64 flags,
		      क्रमागत btrfs_chunk_alloc_क्रमागत क्रमce);
पूर्णांक btrfs_क्रमce_chunk_alloc(काष्ठा btrfs_trans_handle *trans, u64 type);
व्योम check_प्रणाली_chunk(काष्ठा btrfs_trans_handle *trans, स्थिर u64 type);
u64 btrfs_get_alloc_profile(काष्ठा btrfs_fs_info *fs_info, u64 orig_flags);
व्योम btrfs_put_block_group_cache(काष्ठा btrfs_fs_info *info);
पूर्णांक btrfs_मुक्त_block_groups(काष्ठा btrfs_fs_info *info);
व्योम btrfs_रुको_space_cache_v1_finished(काष्ठा btrfs_block_group *cache,
				काष्ठा btrfs_caching_control *caching_ctl);
पूर्णांक btrfs_rmap_block(काष्ठा btrfs_fs_info *fs_info, u64 chunk_start,
		       काष्ठा block_device *bdev, u64 physical, u64 **logical,
		       पूर्णांक *naddrs, पूर्णांक *stripe_len);

अटल अंतरभूत u64 btrfs_data_alloc_profile(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस btrfs_get_alloc_profile(fs_info, BTRFS_BLOCK_GROUP_DATA);
पूर्ण

अटल अंतरभूत u64 btrfs_metadata_alloc_profile(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस btrfs_get_alloc_profile(fs_info, BTRFS_BLOCK_GROUP_METADATA);
पूर्ण

अटल अंतरभूत u64 btrfs_प्रणाली_alloc_profile(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस btrfs_get_alloc_profile(fs_info, BTRFS_BLOCK_GROUP_SYSTEM);
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_block_group_करोne(काष्ठा btrfs_block_group *cache)
अणु
	smp_mb();
	वापस cache->cached == BTRFS_CACHE_FINISHED ||
		cache->cached == BTRFS_CACHE_ERROR;
पूर्ण

व्योम btrfs_मुक्तze_block_group(काष्ठा btrfs_block_group *cache);
व्योम btrfs_unमुक्तze_block_group(काष्ठा btrfs_block_group *cache);

bool btrfs_inc_block_group_swap_extents(काष्ठा btrfs_block_group *bg);
व्योम btrfs_dec_block_group_swap_extents(काष्ठा btrfs_block_group *bg, पूर्णांक amount);

#पूर्ण_अगर /* BTRFS_BLOCK_GROUP_H */
