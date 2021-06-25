<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_SPACE_INFO_H
#घोषणा BTRFS_SPACE_INFO_H

काष्ठा btrfs_space_info अणु
	spinlock_t lock;

	u64 total_bytes;	/* total bytes in the space,
				   this करोesn't take mirrors पूर्णांकo account */
	u64 bytes_used;		/* total bytes used,
				   this करोesn't take mirrors पूर्णांकo account */
	u64 bytes_pinned;	/* total bytes pinned, will be मुक्तd when the
				   transaction finishes */
	u64 bytes_reserved;	/* total bytes the allocator has reserved क्रम
				   current allocations */
	u64 bytes_may_use;	/* number of bytes that may be used क्रम
				   delalloc/allocations */
	u64 bytes_पढ़ोonly;	/* total bytes that are पढ़ो only */
	u64 bytes_zone_unusable;	/* total bytes that are unusable until
					   resetting the device zone */

	u64 max_extent_size;	/* This will hold the maximum extent size of
				   the space info अगर we had an ENOSPC in the
				   allocator. */

	पूर्णांक clamp;		/* Used to scale our threshold क्रम preemptive
				   flushing. The value is >> clamp, so turns
				   out to be a 2^clamp भागisor. */

	अचिन्हित पूर्णांक full:1;	/* indicates that we cannot allocate any more
				   chunks क्रम this space */
	अचिन्हित पूर्णांक chunk_alloc:1;	/* set अगर we are allocating a chunk */

	अचिन्हित पूर्णांक flush:1;		/* set अगर we are trying to make space */

	अचिन्हित पूर्णांक क्रमce_alloc;	/* set अगर we need to क्रमce a chunk
					   alloc क्रम this space */

	u64 disk_used;		/* total bytes used on disk */
	u64 disk_total;		/* total bytes on disk, takes mirrors पूर्णांकo
				   account */

	u64 flags;

	/*
	 * bytes_pinned is kept in line with what is actually pinned, as in
	 * we've called update_block_group and dropped the bytes_used counter
	 * and increased the bytes_pinned counter.  However this means that
	 * bytes_pinned करोes not reflect the bytes that will be pinned once the
	 * delayed refs are flushed, so this counter is inc'ed every समय we
	 * call btrfs_मुक्त_extent so it is a realसमय count of what will be
	 * मुक्तd once the transaction is committed.  It will be zeroed every
	 * समय the transaction commits.
	 */
	काष्ठा percpu_counter total_bytes_pinned;

	काष्ठा list_head list;
	/* Protected by the spinlock 'lock'. */
	काष्ठा list_head ro_bgs;
	काष्ठा list_head priority_tickets;
	काष्ठा list_head tickets;

	/*
	 * Size of space that needs to be reclaimed in order to satisfy pending
	 * tickets
	 */
	u64 reclaim_size;

	/*
	 * tickets_id just indicates the next ticket will be handled, so note
	 * it's not stored per ticket.
	 */
	u64 tickets_id;

	काष्ठा rw_semaphore groups_sem;
	/* क्रम block groups in our same type */
	काष्ठा list_head block_groups[BTRFS_NR_RAID_TYPES];

	काष्ठा kobject kobj;
	काष्ठा kobject *block_group_kobjs[BTRFS_NR_RAID_TYPES];
पूर्ण;

काष्ठा reserve_ticket अणु
	u64 bytes;
	पूर्णांक error;
	bool steal;
	काष्ठा list_head list;
	रुको_queue_head_t रुको;
पूर्ण;

अटल अंतरभूत bool btrfs_mixed_space_info(काष्ठा btrfs_space_info *space_info)
अणु
	वापस ((space_info->flags & BTRFS_BLOCK_GROUP_METADATA) &&
		(space_info->flags & BTRFS_BLOCK_GROUP_DATA));
पूर्ण

/*
 *
 * Declare a helper function to detect underflow of various space info members
 */
#घोषणा DECLARE_SPACE_INFO_UPDATE(name, trace_name)			\
अटल अंतरभूत व्योम							\
btrfs_space_info_update_##name(काष्ठा btrfs_fs_info *fs_info,		\
			       काष्ठा btrfs_space_info *sinfo,		\
			       s64 bytes)				\
अणु									\
	स्थिर u64 असल_bytes = (bytes < 0) ? -bytes : bytes;		\
	lockdep_निश्चित_held(&sinfo->lock);				\
	trace_update_##name(fs_info, sinfo, sinfo->name, bytes);	\
	trace_btrfs_space_reservation(fs_info, trace_name,		\
				      sinfo->flags, असल_bytes,		\
				      bytes > 0);			\
	अगर (bytes < 0 && sinfo->name < -bytes) अणु			\
		WARN_ON(1);						\
		sinfo->name = 0;					\
		वापस;							\
	पूर्ण								\
	sinfo->name += bytes;						\
पूर्ण

DECLARE_SPACE_INFO_UPDATE(bytes_may_use, "space_info");
DECLARE_SPACE_INFO_UPDATE(bytes_pinned, "pinned");

पूर्णांक btrfs_init_space_info(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_update_space_info(काष्ठा btrfs_fs_info *info, u64 flags,
			     u64 total_bytes, u64 bytes_used,
			     u64 bytes_पढ़ोonly, u64 bytes_zone_unusable,
			     काष्ठा btrfs_space_info **space_info);
काष्ठा btrfs_space_info *btrfs_find_space_info(काष्ठा btrfs_fs_info *info,
					       u64 flags);
u64 __pure btrfs_space_info_used(काष्ठा btrfs_space_info *s_info,
			  bool may_use_included);
व्योम btrfs_clear_space_info_full(काष्ठा btrfs_fs_info *info);
व्योम btrfs_dump_space_info(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_space_info *info, u64 bytes,
			   पूर्णांक dump_block_groups);
पूर्णांक btrfs_reserve_metadata_bytes(काष्ठा btrfs_root *root,
				 काष्ठा btrfs_block_rsv *block_rsv,
				 u64 orig_bytes,
				 क्रमागत btrfs_reserve_flush_क्रमागत flush);
व्योम btrfs_try_granting_tickets(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_space_info *space_info);
पूर्णांक btrfs_can_overcommit(काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा btrfs_space_info *space_info, u64 bytes,
			 क्रमागत btrfs_reserve_flush_क्रमागत flush);

अटल अंतरभूत व्योम btrfs_space_info_मुक्त_bytes_may_use(
				काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_space_info *space_info,
				u64 num_bytes)
अणु
	spin_lock(&space_info->lock);
	btrfs_space_info_update_bytes_may_use(fs_info, space_info, -num_bytes);
	btrfs_try_granting_tickets(fs_info, space_info);
	spin_unlock(&space_info->lock);
पूर्ण
पूर्णांक btrfs_reserve_data_bytes(काष्ठा btrfs_fs_info *fs_info, u64 bytes,
			     क्रमागत btrfs_reserve_flush_क्रमागत flush);

अटल अंतरभूत व्योम __btrfs_mod_total_bytes_pinned(
					काष्ठा btrfs_space_info *space_info,
					s64 mod)
अणु
	percpu_counter_add_batch(&space_info->total_bytes_pinned, mod,
				 BTRFS_TOTAL_BYTES_PINNED_BATCH);
पूर्ण

अटल अंतरभूत व्योम btrfs_mod_total_bytes_pinned(काष्ठा btrfs_fs_info *fs_info,
						u64 flags, s64 mod)
अणु
	काष्ठा btrfs_space_info *space_info = btrfs_find_space_info(fs_info, flags);

	ASSERT(space_info);
	__btrfs_mod_total_bytes_pinned(space_info, mod);
पूर्ण

#पूर्ण_अगर /* BTRFS_SPACE_INFO_H */
