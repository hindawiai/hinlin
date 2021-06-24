<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "space-info.h"
#समावेश "sysfs.h"
#समावेश "volumes.h"
#समावेश "free-space-cache.h"
#समावेश "ordered-data.h"
#समावेश "transaction.h"
#समावेश "block-group.h"

/*
 * HOW DOES SPACE RESERVATION WORK
 *
 * If you want to know about delalloc specअगरically, there is a separate comment
 * क्रम that with the delalloc code.  This comment is about how the whole प्रणाली
 * works generally.
 *
 * BASIC CONCEPTS
 *
 *   1) space_info.  This is the ultimate arbiter of how much space we can use.
 *   There's a description of the bytes_ fields with the काष्ठा declaration,
 *   refer to that क्रम specअगरics on each field.  Suffice it to say that क्रम
 *   reservations we care about total_bytes - SUM(space_info->bytes_) when
 *   determining अगर there is space to make an allocation.  There is a space_info
 *   क्रम METADATA, SYSTEM, and DATA areas.
 *
 *   2) block_rsv's.  These are basically buckets क्रम every dअगरferent type of
 *   metadata reservation we have.  You can see the comment in the block_rsv
 *   code on the rules क्रम each type, but generally block_rsv->reserved is how
 *   much space is accounted क्रम in space_info->bytes_may_use.
 *
 *   3) btrfs_calc*_size.  These are the worst हाल calculations we used based
 *   on the number of items we will want to modअगरy.  We have one क्रम changing
 *   items, and one क्रम inserting new items.  Generally we use these helpers to
 *   determine the size of the block reserves, and then use the actual bytes
 *   values to adjust the space_info counters.
 *
 * MAKING RESERVATIONS, THE NORMAL CASE
 *
 *   We call पूर्णांकo either btrfs_reserve_data_bytes() or
 *   btrfs_reserve_metadata_bytes(), depending on which we're looking क्रम, with
 *   num_bytes we want to reserve.
 *
 *   ->reserve
 *     space_info->bytes_may_reserve += num_bytes
 *
 *   ->extent allocation
 *     Call btrfs_add_reserved_bytes() which करोes
 *     space_info->bytes_may_reserve -= num_bytes
 *     space_info->bytes_reserved += extent_bytes
 *
 *   ->insert reference
 *     Call btrfs_update_block_group() which करोes
 *     space_info->bytes_reserved -= extent_bytes
 *     space_info->bytes_used += extent_bytes
 *
 * MAKING RESERVATIONS, FLUSHING NORMALLY (non-priority)
 *
 *   Assume we are unable to simply make the reservation because we करो not have
 *   enough space
 *
 *   -> __reserve_bytes
 *     create a reserve_ticket with ->bytes set to our reservation, add it to
 *     the tail of space_info->tickets, kick async flush thपढ़ो
 *
 *   ->handle_reserve_ticket
 *     रुको on ticket->रुको क्रम ->bytes to be reduced to 0, or ->error to be set
 *     on the ticket.
 *
 *   -> btrfs_async_reclaim_metadata_space/btrfs_async_reclaim_data_space
 *     Flushes various things attempting to मुक्त up space.
 *
 *   -> btrfs_try_granting_tickets()
 *     This is called by anything that either subtracts space from
 *     space_info->bytes_may_use, ->bytes_pinned, etc, or adds to the
 *     space_info->total_bytes.  This loops through the ->priority_tickets and
 *     then the ->tickets list checking to see अगर the reservation can be
 *     completed.  If it can the space is added to space_info->bytes_may_use and
 *     the ticket is woken up.
 *
 *   -> ticket wakeup
 *     Check अगर ->bytes == 0, अगर it करोes we got our reservation and we can carry
 *     on, अगर not वापस the appropriate error (ENOSPC, but can be EINTR अगर we
 *     were पूर्णांकerrupted.)
 *
 * MAKING RESERVATIONS, FLUSHING HIGH PRIORITY
 *
 *   Same as the above, except we add ourselves to the
 *   space_info->priority_tickets, and we करो not use ticket->रुको, we simply
 *   call flush_space() ourselves क्रम the states that are safe क्रम us to call
 *   without deadlocking and hope क्रम the best.
 *
 * THE FLUSHING STATES
 *
 *   Generally speaking we will have two हालs क्रम each state, a "nice" state
 *   and a "ALL THE THINGS" state.  In btrfs we delay a lot of work in order to
 *   reduce the locking over head on the various trees, and even to keep from
 *   करोing any work at all in the हाल of delayed refs.  Each of these delayed
 *   things however hold reservations, and so letting them run allows us to
 *   reclaim space so we can make new reservations.
 *
 *   FLUSH_DELAYED_ITEMS
 *     Every inode has a delayed item to update the inode.  Take a simple ग_लिखो
 *     क्रम example, we would update the inode item at ग_लिखो समय to update the
 *     mसमय, and then again at finish_ordered_io() समय in order to update the
 *     isize or bytes.  We keep these delayed items to coalesce these operations
 *     पूर्णांकo a single operation करोne on demand.  These are an easy way to reclaim
 *     metadata space.
 *
 *   FLUSH_DELALLOC
 *     Look at the delalloc comment to get an idea of how much space is reserved
 *     क्रम delayed allocation.  We can reclaim some of this space simply by
 *     running delalloc, but usually we need to रुको क्रम ordered extents to
 *     reclaim the bulk of this space.
 *
 *   FLUSH_DELAYED_REFS
 *     We have a block reserve क्रम the outstanding delayed refs space, and every
 *     delayed ref operation holds a reservation.  Running these is a quick way
 *     to reclaim space, but we want to hold this until the end because COW can
 *     churn a lot and we can aव्योम making some extent tree modअगरications अगर we
 *     are able to delay क्रम as दीर्घ as possible.
 *
 *   ALLOC_CHUNK
 *     We will skip this the first समय through space reservation, because of
 *     overcommit and we करोn't want to have a lot of useless metadata space when
 *     our worst हाल reservations will likely never come true.
 *
 *   RUN_DELAYED_IPUTS
 *     If we're freeing inodes we're likely मुक्तing checksums, file extent
 *     items, and extent tree items.  Loads of space could be मुक्तd up by these
 *     operations, however they won't be usable until the transaction commits.
 *
 *   COMMIT_TRANS
 *     may_commit_transaction() is the ultimate arbiter on whether we commit the
 *     transaction or not.  In order to aव्योम स्थिरantly churning we करो all the
 *     above flushing first and then commit the transaction as the last resort.
 *     However we need to take पूर्णांकo account things like pinned space that would
 *     be मुक्तd, plus any delayed work we may not have gotten rid of in the हाल
 *     of metadata.
 *
 *   FORCE_COMMIT_TRANS
 *     For use by the preemptive flusher.  We use this to bypass the ticketing
 *     checks in may_commit_transaction, as we have more inक्रमmation about the
 *     overall state of the प्रणाली and may want to commit the transaction ahead
 *     of actual ENOSPC conditions.
 *
 * OVERCOMMIT
 *
 *   Because we hold so many reservations क्रम metadata we will allow you to
 *   reserve more space than is currently मुक्त in the currently allocate
 *   metadata space.  This only happens with metadata, data करोes not allow
 *   overcommitting.
 *
 *   You can see the current logic क्रम when we allow overcommit in
 *   btrfs_can_overcommit(), but it only applies to unallocated space.  If there
 *   is no unallocated space to be had, all reservations are kept within the
 *   मुक्त space in the allocated metadata chunks.
 *
 *   Because of overcommitting, you generally want to use the
 *   btrfs_can_overcommit() logic क्रम metadata allocations, as it करोes the right
 *   thing with or without extra unallocated space.
 */

u64 __pure btrfs_space_info_used(काष्ठा btrfs_space_info *s_info,
			  bool may_use_included)
अणु
	ASSERT(s_info);
	वापस s_info->bytes_used + s_info->bytes_reserved +
		s_info->bytes_pinned + s_info->bytes_पढ़ोonly +
		s_info->bytes_zone_unusable +
		(may_use_included ? s_info->bytes_may_use : 0);
पूर्ण

/*
 * after adding space to the fileप्रणाली, we need to clear the full flags
 * on all the space infos.
 */
व्योम btrfs_clear_space_info_full(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा list_head *head = &info->space_info;
	काष्ठा btrfs_space_info *found;

	list_क्रम_each_entry(found, head, list)
		found->full = 0;
पूर्ण

अटल पूर्णांक create_space_info(काष्ठा btrfs_fs_info *info, u64 flags)
अणु

	काष्ठा btrfs_space_info *space_info;
	पूर्णांक i;
	पूर्णांक ret;

	space_info = kzalloc(माप(*space_info), GFP_NOFS);
	अगर (!space_info)
		वापस -ENOMEM;

	ret = percpu_counter_init(&space_info->total_bytes_pinned, 0,
				 GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(space_info);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < BTRFS_NR_RAID_TYPES; i++)
		INIT_LIST_HEAD(&space_info->block_groups[i]);
	init_rwsem(&space_info->groups_sem);
	spin_lock_init(&space_info->lock);
	space_info->flags = flags & BTRFS_BLOCK_GROUP_TYPE_MASK;
	space_info->क्रमce_alloc = CHUNK_ALLOC_NO_FORCE;
	INIT_LIST_HEAD(&space_info->ro_bgs);
	INIT_LIST_HEAD(&space_info->tickets);
	INIT_LIST_HEAD(&space_info->priority_tickets);
	space_info->clamp = 1;

	ret = btrfs_sysfs_add_space_info_type(info, space_info);
	अगर (ret)
		वापस ret;

	list_add(&space_info->list, &info->space_info);
	अगर (flags & BTRFS_BLOCK_GROUP_DATA)
		info->data_sinfo = space_info;

	वापस ret;
पूर्ण

पूर्णांक btrfs_init_space_info(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_super_block *disk_super;
	u64 features;
	u64 flags;
	पूर्णांक mixed = 0;
	पूर्णांक ret;

	disk_super = fs_info->super_copy;
	अगर (!btrfs_super_root(disk_super))
		वापस -EINVAL;

	features = btrfs_super_incompat_flags(disk_super);
	अगर (features & BTRFS_FEATURE_INCOMPAT_MIXED_GROUPS)
		mixed = 1;

	flags = BTRFS_BLOCK_GROUP_SYSTEM;
	ret = create_space_info(fs_info, flags);
	अगर (ret)
		जाओ out;

	अगर (mixed) अणु
		flags = BTRFS_BLOCK_GROUP_METADATA | BTRFS_BLOCK_GROUP_DATA;
		ret = create_space_info(fs_info, flags);
	पूर्ण अन्यथा अणु
		flags = BTRFS_BLOCK_GROUP_METADATA;
		ret = create_space_info(fs_info, flags);
		अगर (ret)
			जाओ out;

		flags = BTRFS_BLOCK_GROUP_DATA;
		ret = create_space_info(fs_info, flags);
	पूर्ण
out:
	वापस ret;
पूर्ण

व्योम btrfs_update_space_info(काष्ठा btrfs_fs_info *info, u64 flags,
			     u64 total_bytes, u64 bytes_used,
			     u64 bytes_पढ़ोonly, u64 bytes_zone_unusable,
			     काष्ठा btrfs_space_info **space_info)
अणु
	काष्ठा btrfs_space_info *found;
	पूर्णांक factor;

	factor = btrfs_bg_type_to_factor(flags);

	found = btrfs_find_space_info(info, flags);
	ASSERT(found);
	spin_lock(&found->lock);
	found->total_bytes += total_bytes;
	found->disk_total += total_bytes * factor;
	found->bytes_used += bytes_used;
	found->disk_used += bytes_used * factor;
	found->bytes_पढ़ोonly += bytes_पढ़ोonly;
	found->bytes_zone_unusable += bytes_zone_unusable;
	अगर (total_bytes > 0)
		found->full = 0;
	btrfs_try_granting_tickets(info, found);
	spin_unlock(&found->lock);
	*space_info = found;
पूर्ण

काष्ठा btrfs_space_info *btrfs_find_space_info(काष्ठा btrfs_fs_info *info,
					       u64 flags)
अणु
	काष्ठा list_head *head = &info->space_info;
	काष्ठा btrfs_space_info *found;

	flags &= BTRFS_BLOCK_GROUP_TYPE_MASK;

	list_क्रम_each_entry(found, head, list) अणु
		अगर (found->flags & flags)
			वापस found;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल u64 calc_available_मुक्त_space(काष्ठा btrfs_fs_info *fs_info,
			  काष्ठा btrfs_space_info *space_info,
			  क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	u64 profile;
	u64 avail;
	पूर्णांक factor;

	अगर (space_info->flags & BTRFS_BLOCK_GROUP_SYSTEM)
		profile = btrfs_प्रणाली_alloc_profile(fs_info);
	अन्यथा
		profile = btrfs_metadata_alloc_profile(fs_info);

	avail = atomic64_पढ़ो(&fs_info->मुक्त_chunk_space);

	/*
	 * If we have dup, raid1 or raid10 then only half of the मुक्त
	 * space is actually usable.  For raid56, the space info used
	 * करोesn't include the parity drive, so we don't have to
	 * change the math
	 */
	factor = btrfs_bg_type_to_factor(profile);
	avail = भाग_u64(avail, factor);

	/*
	 * If we aren't flushing all things, let us overcommit up to
	 * 1/2th of the space. If we can flush, करोn't let us overcommit
	 * too much, let it overcommit up to 1/8 of the space.
	 */
	अगर (flush == BTRFS_RESERVE_FLUSH_ALL)
		avail >>= 3;
	अन्यथा
		avail >>= 1;
	वापस avail;
पूर्ण

पूर्णांक btrfs_can_overcommit(काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा btrfs_space_info *space_info, u64 bytes,
			 क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	u64 avail;
	u64 used;

	/* Don't overcommit when in mixed mode */
	अगर (space_info->flags & BTRFS_BLOCK_GROUP_DATA)
		वापस 0;

	used = btrfs_space_info_used(space_info, true);
	avail = calc_available_मुक्त_space(fs_info, space_info, flush);

	अगर (used + bytes < space_info->total_bytes + avail)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम हटाओ_ticket(काष्ठा btrfs_space_info *space_info,
			  काष्ठा reserve_ticket *ticket)
अणु
	अगर (!list_empty(&ticket->list)) अणु
		list_del_init(&ticket->list);
		ASSERT(space_info->reclaim_size >= ticket->bytes);
		space_info->reclaim_size -= ticket->bytes;
	पूर्ण
पूर्ण

/*
 * This is क्रम space we alपढ़ोy have accounted in space_info->bytes_may_use, so
 * basically when we're returning space from block_rsv's.
 */
व्योम btrfs_try_granting_tickets(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_space_info *space_info)
अणु
	काष्ठा list_head *head;
	क्रमागत btrfs_reserve_flush_क्रमागत flush = BTRFS_RESERVE_NO_FLUSH;

	lockdep_निश्चित_held(&space_info->lock);

	head = &space_info->priority_tickets;
again:
	जबतक (!list_empty(head)) अणु
		काष्ठा reserve_ticket *ticket;
		u64 used = btrfs_space_info_used(space_info, true);

		ticket = list_first_entry(head, काष्ठा reserve_ticket, list);

		/* Check and see अगर our ticket can be satisअगरied now. */
		अगर ((used + ticket->bytes <= space_info->total_bytes) ||
		    btrfs_can_overcommit(fs_info, space_info, ticket->bytes,
					 flush)) अणु
			btrfs_space_info_update_bytes_may_use(fs_info,
							      space_info,
							      ticket->bytes);
			हटाओ_ticket(space_info, ticket);
			ticket->bytes = 0;
			space_info->tickets_id++;
			wake_up(&ticket->रुको);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (head == &space_info->priority_tickets) अणु
		head = &space_info->tickets;
		flush = BTRFS_RESERVE_FLUSH_ALL;
		जाओ again;
	पूर्ण
पूर्ण

#घोषणा DUMP_BLOCK_RSV(fs_info, rsv_name)				\
करो अणु									\
	काष्ठा btrfs_block_rsv *__rsv = &(fs_info)->rsv_name;		\
	spin_lock(&__rsv->lock);					\
	btrfs_info(fs_info, #rsv_name ": size %llu reserved %llu",	\
		   __rsv->size, __rsv->reserved);			\
	spin_unlock(&__rsv->lock);					\
पूर्ण जबतक (0)

अटल व्योम __btrfs_dump_space_info(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_space_info *info)
अणु
	lockdep_निश्चित_held(&info->lock);

	btrfs_info(fs_info, "space_info %llu has %llu free, is %sfull",
		   info->flags,
		   info->total_bytes - btrfs_space_info_used(info, true),
		   info->full ? "" : "not ");
	btrfs_info(fs_info,
		"space_info total=%llu, used=%llu, pinned=%llu, reserved=%llu, may_use=%llu, readonly=%llu zone_unusable=%llu",
		info->total_bytes, info->bytes_used, info->bytes_pinned,
		info->bytes_reserved, info->bytes_may_use,
		info->bytes_पढ़ोonly, info->bytes_zone_unusable);

	DUMP_BLOCK_RSV(fs_info, global_block_rsv);
	DUMP_BLOCK_RSV(fs_info, trans_block_rsv);
	DUMP_BLOCK_RSV(fs_info, chunk_block_rsv);
	DUMP_BLOCK_RSV(fs_info, delayed_block_rsv);
	DUMP_BLOCK_RSV(fs_info, delayed_refs_rsv);

पूर्ण

व्योम btrfs_dump_space_info(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_space_info *info, u64 bytes,
			   पूर्णांक dump_block_groups)
अणु
	काष्ठा btrfs_block_group *cache;
	पूर्णांक index = 0;

	spin_lock(&info->lock);
	__btrfs_dump_space_info(fs_info, info);
	spin_unlock(&info->lock);

	अगर (!dump_block_groups)
		वापस;

	करोwn_पढ़ो(&info->groups_sem);
again:
	list_क्रम_each_entry(cache, &info->block_groups[index], list) अणु
		spin_lock(&cache->lock);
		btrfs_info(fs_info,
			"block group %llu has %llu bytes, %llu used %llu pinned %llu reserved %llu zone_unusable %s",
			cache->start, cache->length, cache->used, cache->pinned,
			cache->reserved, cache->zone_unusable,
			cache->ro ? "[readonly]" : "");
		spin_unlock(&cache->lock);
		btrfs_dump_मुक्त_space(cache, bytes);
	पूर्ण
	अगर (++index < BTRFS_NR_RAID_TYPES)
		जाओ again;
	up_पढ़ो(&info->groups_sem);
पूर्ण

अटल अंतरभूत u64 calc_reclaim_items_nr(काष्ठा btrfs_fs_info *fs_info,
					u64 to_reclaim)
अणु
	u64 bytes;
	u64 nr;

	bytes = btrfs_calc_insert_metadata_size(fs_info, 1);
	nr = भाग64_u64(to_reclaim, bytes);
	अगर (!nr)
		nr = 1;
	वापस nr;
पूर्ण

#घोषणा EXTENT_SIZE_PER_ITEM	SZ_256K

/*
 * shrink metadata reservation क्रम delalloc
 */
अटल व्योम shrink_delalloc(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_space_info *space_info,
			    u64 to_reclaim, bool रुको_ordered)
अणु
	काष्ठा btrfs_trans_handle *trans;
	u64 delalloc_bytes;
	u64 ordered_bytes;
	u64 items;
	दीर्घ समय_left;
	पूर्णांक loops;

	/* Calc the number of the pages we need flush क्रम space reservation */
	अगर (to_reclaim == U64_MAX) अणु
		items = U64_MAX;
	पूर्ण अन्यथा अणु
		/*
		 * to_reclaim is set to however much metadata we need to
		 * reclaim, but reclaiming that much data करोesn't really track
		 * exactly, so increase the amount to reclaim by 2x in order to
		 * make sure we're flushing enough delalloc to hopefully reclaim
		 * some metadata reservations.
		 */
		items = calc_reclaim_items_nr(fs_info, to_reclaim) * 2;
		to_reclaim = items * EXTENT_SIZE_PER_ITEM;
	पूर्ण

	trans = (काष्ठा btrfs_trans_handle *)current->journal_info;

	delalloc_bytes = percpu_counter_sum_positive(
						&fs_info->delalloc_bytes);
	ordered_bytes = percpu_counter_sum_positive(&fs_info->ordered_bytes);
	अगर (delalloc_bytes == 0 && ordered_bytes == 0)
		वापस;

	/*
	 * If we are करोing more ordered than delalloc we need to just रुको on
	 * ordered extents, otherwise we'll waste समय trying to flush delalloc
	 * that likely won't give us the space back we need.
	 */
	अगर (ordered_bytes > delalloc_bytes)
		रुको_ordered = true;

	loops = 0;
	जबतक ((delalloc_bytes || ordered_bytes) && loops < 3) अणु
		u64 temp = min(delalloc_bytes, to_reclaim) >> PAGE_SHIFT;
		दीर्घ nr_pages = min_t(u64, temp, दीर्घ_उच्च);

		btrfs_start_delalloc_roots(fs_info, nr_pages, true);

		loops++;
		अगर (रुको_ordered && !trans) अणु
			btrfs_रुको_ordered_roots(fs_info, items, 0, (u64)-1);
		पूर्ण अन्यथा अणु
			समय_left = schedule_समयout_समाप्तable(1);
			अगर (समय_left)
				अवरोध;
		पूर्ण

		spin_lock(&space_info->lock);
		अगर (list_empty(&space_info->tickets) &&
		    list_empty(&space_info->priority_tickets)) अणु
			spin_unlock(&space_info->lock);
			अवरोध;
		पूर्ण
		spin_unlock(&space_info->lock);

		delalloc_bytes = percpu_counter_sum_positive(
						&fs_info->delalloc_bytes);
		ordered_bytes = percpu_counter_sum_positive(
						&fs_info->ordered_bytes);
	पूर्ण
पूर्ण

/**
 * Possibly commit the transaction अगर its ok to
 *
 * @fs_info:    the fileप्रणाली
 * @space_info: space_info we are checking क्रम commit, either data or metadata
 *
 * This will check to make sure that committing the transaction will actually
 * get us somewhere and then commit the transaction अगर it करोes.  Otherwise it
 * will वापस -ENOSPC.
 */
अटल पूर्णांक may_commit_transaction(काष्ठा btrfs_fs_info *fs_info,
				  काष्ठा btrfs_space_info *space_info)
अणु
	काष्ठा reserve_ticket *ticket = शून्य;
	काष्ठा btrfs_block_rsv *delayed_rsv = &fs_info->delayed_block_rsv;
	काष्ठा btrfs_block_rsv *delayed_refs_rsv = &fs_info->delayed_refs_rsv;
	काष्ठा btrfs_block_rsv *trans_rsv = &fs_info->trans_block_rsv;
	काष्ठा btrfs_trans_handle *trans;
	u64 reclaim_bytes = 0;
	u64 bytes_needed = 0;
	u64 cur_मुक्त_bytes = 0;

	trans = (काष्ठा btrfs_trans_handle *)current->journal_info;
	अगर (trans)
		वापस -EAGAIN;

	spin_lock(&space_info->lock);
	cur_मुक्त_bytes = btrfs_space_info_used(space_info, true);
	अगर (cur_मुक्त_bytes < space_info->total_bytes)
		cur_मुक्त_bytes = space_info->total_bytes - cur_मुक्त_bytes;
	अन्यथा
		cur_मुक्त_bytes = 0;

	अगर (!list_empty(&space_info->priority_tickets))
		ticket = list_first_entry(&space_info->priority_tickets,
					  काष्ठा reserve_ticket, list);
	अन्यथा अगर (!list_empty(&space_info->tickets))
		ticket = list_first_entry(&space_info->tickets,
					  काष्ठा reserve_ticket, list);
	अगर (ticket)
		bytes_needed = ticket->bytes;

	अगर (bytes_needed > cur_मुक्त_bytes)
		bytes_needed -= cur_मुक्त_bytes;
	अन्यथा
		bytes_needed = 0;
	spin_unlock(&space_info->lock);

	अगर (!bytes_needed)
		वापस 0;

	trans = btrfs_join_transaction(fs_info->extent_root);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	/*
	 * See अगर there is enough pinned space to make this reservation, or अगर
	 * we have block groups that are going to be मुक्तd, allowing us to
	 * possibly करो a chunk allocation the next loop through.
	 */
	अगर (test_bit(BTRFS_TRANS_HAVE_FREE_BGS, &trans->transaction->flags) ||
	    __percpu_counter_compare(&space_info->total_bytes_pinned,
				     bytes_needed,
				     BTRFS_TOTAL_BYTES_PINNED_BATCH) >= 0)
		जाओ commit;

	/*
	 * See अगर there is some space in the delayed insertion reserve क्रम this
	 * reservation.  If the space_info's don't match (like क्रम DATA or
	 * SYSTEM) then just go enospc, reclaiming this space won't recover any
	 * space to satisfy those reservations.
	 */
	अगर (space_info != delayed_rsv->space_info)
		जाओ enospc;

	spin_lock(&delayed_rsv->lock);
	reclaim_bytes += delayed_rsv->reserved;
	spin_unlock(&delayed_rsv->lock);

	spin_lock(&delayed_refs_rsv->lock);
	reclaim_bytes += delayed_refs_rsv->reserved;
	spin_unlock(&delayed_refs_rsv->lock);

	spin_lock(&trans_rsv->lock);
	reclaim_bytes += trans_rsv->reserved;
	spin_unlock(&trans_rsv->lock);

	अगर (reclaim_bytes >= bytes_needed)
		जाओ commit;
	bytes_needed -= reclaim_bytes;

	अगर (__percpu_counter_compare(&space_info->total_bytes_pinned,
				   bytes_needed,
				   BTRFS_TOTAL_BYTES_PINNED_BATCH) < 0)
		जाओ enospc;

commit:
	वापस btrfs_commit_transaction(trans);
enospc:
	btrfs_end_transaction(trans);
	वापस -ENOSPC;
पूर्ण

/*
 * Try to flush some data based on policy set by @state. This is only advisory
 * and may fail क्रम various reasons. The caller is supposed to examine the
 * state of @space_info to detect the outcome.
 */
अटल व्योम flush_space(काष्ठा btrfs_fs_info *fs_info,
		       काष्ठा btrfs_space_info *space_info, u64 num_bytes,
		       क्रमागत btrfs_flush_state state, bool क्रम_preempt)
अणु
	काष्ठा btrfs_root *root = fs_info->extent_root;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक nr;
	पूर्णांक ret = 0;

	चयन (state) अणु
	हाल FLUSH_DELAYED_ITEMS_NR:
	हाल FLUSH_DELAYED_ITEMS:
		अगर (state == FLUSH_DELAYED_ITEMS_NR)
			nr = calc_reclaim_items_nr(fs_info, num_bytes) * 2;
		अन्यथा
			nr = -1;

		trans = btrfs_join_transaction(root);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			अवरोध;
		पूर्ण
		ret = btrfs_run_delayed_items_nr(trans, nr);
		btrfs_end_transaction(trans);
		अवरोध;
	हाल FLUSH_DELALLOC:
	हाल FLUSH_DELALLOC_WAIT:
		shrink_delalloc(fs_info, space_info, num_bytes,
				state == FLUSH_DELALLOC_WAIT);
		अवरोध;
	हाल FLUSH_DELAYED_REFS_NR:
	हाल FLUSH_DELAYED_REFS:
		trans = btrfs_join_transaction(root);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			अवरोध;
		पूर्ण
		अगर (state == FLUSH_DELAYED_REFS_NR)
			nr = calc_reclaim_items_nr(fs_info, num_bytes);
		अन्यथा
			nr = 0;
		btrfs_run_delayed_refs(trans, nr);
		btrfs_end_transaction(trans);
		अवरोध;
	हाल ALLOC_CHUNK:
	हाल ALLOC_CHUNK_FORCE:
		trans = btrfs_join_transaction(root);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			अवरोध;
		पूर्ण
		ret = btrfs_chunk_alloc(trans,
				btrfs_get_alloc_profile(fs_info, space_info->flags),
				(state == ALLOC_CHUNK) ? CHUNK_ALLOC_NO_FORCE :
					CHUNK_ALLOC_FORCE);
		btrfs_end_transaction(trans);
		अगर (ret > 0 || ret == -ENOSPC)
			ret = 0;
		अवरोध;
	हाल RUN_DELAYED_IPUTS:
		/*
		 * If we have pending delayed iमाला_दो then we could मुक्त up a
		 * bunch of pinned space, so make sure we run the iमाला_दो beक्रमe
		 * we करो our pinned bytes check below.
		 */
		btrfs_run_delayed_iमाला_दो(fs_info);
		btrfs_रुको_on_delayed_iमाला_दो(fs_info);
		अवरोध;
	हाल COMMIT_TRANS:
		ret = may_commit_transaction(fs_info, space_info);
		अवरोध;
	हाल FORCE_COMMIT_TRANS:
		trans = btrfs_join_transaction(root);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			अवरोध;
		पूर्ण
		ret = btrfs_commit_transaction(trans);
		अवरोध;
	शेष:
		ret = -ENOSPC;
		अवरोध;
	पूर्ण

	trace_btrfs_flush_space(fs_info, space_info->flags, num_bytes, state,
				ret, क्रम_preempt);
	वापस;
पूर्ण

अटल अंतरभूत u64
btrfs_calc_reclaim_metadata_size(काष्ठा btrfs_fs_info *fs_info,
				 काष्ठा btrfs_space_info *space_info)
अणु
	u64 used;
	u64 avail;
	u64 to_reclaim = space_info->reclaim_size;

	lockdep_निश्चित_held(&space_info->lock);

	avail = calc_available_मुक्त_space(fs_info, space_info,
					  BTRFS_RESERVE_FLUSH_ALL);
	used = btrfs_space_info_used(space_info, true);

	/*
	 * We may be flushing because suddenly we have less space than we had
	 * beक्रमe, and now we're well over-committed based on our current मुक्त
	 * space.  If that's the हाल add in our overage so we make sure to put
	 * appropriate pressure on the flushing state machine.
	 */
	अगर (space_info->total_bytes + avail < used)
		to_reclaim += used - (space_info->total_bytes + avail);

	वापस to_reclaim;
पूर्ण

अटल bool need_preemptive_reclaim(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_space_info *space_info)
अणु
	u64 ordered, delalloc;
	u64 thresh = भाग_factor_fine(space_info->total_bytes, 98);
	u64 used;

	/* If we're just plain full then async reclaim just slows us करोwn. */
	अगर ((space_info->bytes_used + space_info->bytes_reserved) >= thresh)
		वापस false;

	/*
	 * We have tickets queued, bail so we करोn't compete with the async
	 * flushers.
	 */
	अगर (space_info->reclaim_size)
		वापस false;

	/*
	 * If we have over half of the मुक्त space occupied by reservations or
	 * pinned then we want to start flushing.
	 *
	 * We करो not करो the traditional thing here, which is to say
	 *
	 *   अगर (used >= ((total_bytes + avail) / 2))
	 *     वापस 1;
	 *
	 * because this करोesn't quite work how we want.  If we had more than 50%
	 * of the space_info used by bytes_used and we had 0 available we'd just
	 * स्थिरantly run the background flusher.  Instead we want it to kick in
	 * अगर our reclaimable space exceeds our clamped मुक्त space.
	 *
	 * Our clamping range is 2^1 -> 2^8.  Practically speaking that means
	 * the following:
	 *
	 * Amount of RAM        Minimum threshold       Maximum threshold
	 *
	 *        256GiB                     1GiB                  128GiB
	 *        128GiB                   512MiB                   64GiB
	 *         64GiB                   256MiB                   32GiB
	 *         32GiB                   128MiB                   16GiB
	 *         16GiB                    64MiB                    8GiB
	 *
	 * These are the range our thresholds will fall in, corresponding to how
	 * much delalloc we need क्रम the background flusher to kick in.
	 */

	thresh = calc_available_मुक्त_space(fs_info, space_info,
					   BTRFS_RESERVE_FLUSH_ALL);
	thresh += (space_info->total_bytes - space_info->bytes_used -
		   space_info->bytes_reserved - space_info->bytes_पढ़ोonly);
	thresh >>= space_info->clamp;

	used = space_info->bytes_pinned;

	/*
	 * If we have more ordered bytes than delalloc bytes then we're either
	 * करोing a lot of DIO, or we simply करोn't have a lot of delalloc रुकोing
	 * around.  Preemptive flushing is only useful in that it can मुक्त up
	 * space beक्रमe tickets need to रुको क्रम things to finish.  In the हाल
	 * of ordered extents, preemptively रुकोing on ordered extents माला_लो us
	 * nothing, अगर our reservations are tied up in ordered extents we'll
	 * simply have to slow करोwn ग_लिखोrs by क्रमcing them to रुको on ordered
	 * extents.
	 *
	 * In the हाल that ordered is larger than delalloc, only include the
	 * block reserves that we would actually be able to directly reclaim
	 * from.  In this हाल अगर we're heavy on metadata operations this will
	 * clearly be heavy enough to warrant preemptive flushing.  In the हाल
	 * of heavy DIO or ordered reservations, preemptive flushing will just
	 * waste समय and cause us to slow करोwn.
	 */
	ordered = percpu_counter_पढ़ो_positive(&fs_info->ordered_bytes);
	delalloc = percpu_counter_पढ़ो_positive(&fs_info->delalloc_bytes);
	अगर (ordered >= delalloc)
		used += fs_info->delayed_refs_rsv.reserved +
			fs_info->delayed_block_rsv.reserved;
	अन्यथा
		used += space_info->bytes_may_use;

	वापस (used >= thresh && !btrfs_fs_closing(fs_info) &&
		!test_bit(BTRFS_FS_STATE_REMOUNTING, &fs_info->fs_state));
पूर्ण

अटल bool steal_from_global_rsv(काष्ठा btrfs_fs_info *fs_info,
				  काष्ठा btrfs_space_info *space_info,
				  काष्ठा reserve_ticket *ticket)
अणु
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	u64 min_bytes;

	अगर (global_rsv->space_info != space_info)
		वापस false;

	spin_lock(&global_rsv->lock);
	min_bytes = भाग_factor(global_rsv->size, 1);
	अगर (global_rsv->reserved < min_bytes + ticket->bytes) अणु
		spin_unlock(&global_rsv->lock);
		वापस false;
	पूर्ण
	global_rsv->reserved -= ticket->bytes;
	हटाओ_ticket(space_info, ticket);
	ticket->bytes = 0;
	wake_up(&ticket->रुको);
	space_info->tickets_id++;
	अगर (global_rsv->reserved < global_rsv->size)
		global_rsv->full = 0;
	spin_unlock(&global_rsv->lock);

	वापस true;
पूर्ण

/*
 * maybe_fail_all_tickets - we've exhausted our flushing, start failing tickets
 * @fs_info - fs_info क्रम this fs
 * @space_info - the space info we were flushing
 *
 * We call this when we've exhausted our flushing ability and haven't made
 * progress in satisfying tickets.  The reservation code handles tickets in
 * order, so अगर there is a large ticket first and then smaller ones we could
 * very well satisfy the smaller tickets.  This will attempt to wake up any
 * tickets in the list to catch this हाल.
 *
 * This function वापसs true अगर it was able to make progress by clearing out
 * other tickets, or अगर it stumbles across a ticket that was smaller than the
 * first ticket.
 */
अटल bool maybe_fail_all_tickets(काष्ठा btrfs_fs_info *fs_info,
				   काष्ठा btrfs_space_info *space_info)
अणु
	काष्ठा reserve_ticket *ticket;
	u64 tickets_id = space_info->tickets_id;
	u64 first_ticket_bytes = 0;

	अगर (btrfs_test_opt(fs_info, ENOSPC_DEBUG)) अणु
		btrfs_info(fs_info, "cannot satisfy tickets, dumping space info");
		__btrfs_dump_space_info(fs_info, space_info);
	पूर्ण

	जबतक (!list_empty(&space_info->tickets) &&
	       tickets_id == space_info->tickets_id) अणु
		ticket = list_first_entry(&space_info->tickets,
					  काष्ठा reserve_ticket, list);

		अगर (ticket->steal &&
		    steal_from_global_rsv(fs_info, space_info, ticket))
			वापस true;

		/*
		 * may_commit_transaction will aव्योम committing the transaction
		 * अगर it करोesn't feel like the space reclaimed by the commit
		 * would result in the ticket succeeding.  However अगर we have a
		 * smaller ticket in the queue it may be small enough to be
		 * satisअगरied by committing the transaction, so अगर any
		 * subsequent ticket is smaller than the first ticket go ahead
		 * and send us back क्रम another loop through the enospc flushing
		 * code.
		 */
		अगर (first_ticket_bytes == 0)
			first_ticket_bytes = ticket->bytes;
		अन्यथा अगर (first_ticket_bytes > ticket->bytes)
			वापस true;

		अगर (btrfs_test_opt(fs_info, ENOSPC_DEBUG))
			btrfs_info(fs_info, "failing ticket with %llu bytes",
				   ticket->bytes);

		हटाओ_ticket(space_info, ticket);
		ticket->error = -ENOSPC;
		wake_up(&ticket->रुको);

		/*
		 * We're just throwing tickets away, so more flushing may not
		 * trip over btrfs_try_granting_tickets, so we need to call it
		 * here to see अगर we can make progress with the next ticket in
		 * the list.
		 */
		btrfs_try_granting_tickets(fs_info, space_info);
	पूर्ण
	वापस (tickets_id != space_info->tickets_id);
पूर्ण

/*
 * This is क्रम normal flushers, we can रुको all goddamned day अगर we want to.  We
 * will loop and continuously try to flush as दीर्घ as we are making progress.
 * We count progress as clearing off tickets each समय we have to loop.
 */
अटल व्योम btrfs_async_reclaim_metadata_space(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_space_info *space_info;
	u64 to_reclaim;
	क्रमागत btrfs_flush_state flush_state;
	पूर्णांक commit_cycles = 0;
	u64 last_tickets_id;

	fs_info = container_of(work, काष्ठा btrfs_fs_info, async_reclaim_work);
	space_info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_METADATA);

	spin_lock(&space_info->lock);
	to_reclaim = btrfs_calc_reclaim_metadata_size(fs_info, space_info);
	अगर (!to_reclaim) अणु
		space_info->flush = 0;
		spin_unlock(&space_info->lock);
		वापस;
	पूर्ण
	last_tickets_id = space_info->tickets_id;
	spin_unlock(&space_info->lock);

	flush_state = FLUSH_DELAYED_ITEMS_NR;
	करो अणु
		flush_space(fs_info, space_info, to_reclaim, flush_state, false);
		spin_lock(&space_info->lock);
		अगर (list_empty(&space_info->tickets)) अणु
			space_info->flush = 0;
			spin_unlock(&space_info->lock);
			वापस;
		पूर्ण
		to_reclaim = btrfs_calc_reclaim_metadata_size(fs_info,
							      space_info);
		अगर (last_tickets_id == space_info->tickets_id) अणु
			flush_state++;
		पूर्ण अन्यथा अणु
			last_tickets_id = space_info->tickets_id;
			flush_state = FLUSH_DELAYED_ITEMS_NR;
			अगर (commit_cycles)
				commit_cycles--;
		पूर्ण

		/*
		 * We करोn't want to force a chunk allocation until we've tried
		 * pretty hard to reclaim space.  Think of the हाल where we
		 * मुक्तd up a bunch of space and so have a lot of pinned space
		 * to reclaim.  We would rather use that than possibly create a
		 * underutilized metadata chunk.  So अगर this is our first run
		 * through the flushing state machine skip ALLOC_CHUNK_FORCE and
		 * commit the transaction.  If nothing has changed the next go
		 * around then we can क्रमce a chunk allocation.
		 */
		अगर (flush_state == ALLOC_CHUNK_FORCE && !commit_cycles)
			flush_state++;

		अगर (flush_state > COMMIT_TRANS) अणु
			commit_cycles++;
			अगर (commit_cycles > 2) अणु
				अगर (maybe_fail_all_tickets(fs_info, space_info)) अणु
					flush_state = FLUSH_DELAYED_ITEMS_NR;
					commit_cycles--;
				पूर्ण अन्यथा अणु
					space_info->flush = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				flush_state = FLUSH_DELAYED_ITEMS_NR;
			पूर्ण
		पूर्ण
		spin_unlock(&space_info->lock);
	पूर्ण जबतक (flush_state <= COMMIT_TRANS);
पूर्ण

/*
 * This handles pre-flushing of metadata space beक्रमe we get to the poपूर्णांक that
 * we need to start blocking thपढ़ोs on tickets.  The logic here is dअगरferent
 * from the other flush paths because it करोesn't rely on tickets to tell us how
 * much we need to flush, instead it attempts to keep us below the 80% full
 * watermark of space by flushing whichever reservation pool is currently the
 * largest.
 */
अटल व्योम btrfs_preempt_reclaim_metadata_space(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_space_info *space_info;
	काष्ठा btrfs_block_rsv *delayed_block_rsv;
	काष्ठा btrfs_block_rsv *delayed_refs_rsv;
	काष्ठा btrfs_block_rsv *global_rsv;
	काष्ठा btrfs_block_rsv *trans_rsv;
	पूर्णांक loops = 0;

	fs_info = container_of(work, काष्ठा btrfs_fs_info,
			       preempt_reclaim_work);
	space_info = btrfs_find_space_info(fs_info, BTRFS_BLOCK_GROUP_METADATA);
	delayed_block_rsv = &fs_info->delayed_block_rsv;
	delayed_refs_rsv = &fs_info->delayed_refs_rsv;
	global_rsv = &fs_info->global_block_rsv;
	trans_rsv = &fs_info->trans_block_rsv;

	spin_lock(&space_info->lock);
	जबतक (need_preemptive_reclaim(fs_info, space_info)) अणु
		क्रमागत btrfs_flush_state flush;
		u64 delalloc_size = 0;
		u64 to_reclaim, block_rsv_size;
		u64 global_rsv_size = global_rsv->reserved;

		loops++;

		/*
		 * We करोn't have a precise counter क्रम the metadata being
		 * reserved क्रम delalloc, so we'll approximate it by subtracting
		 * out the block rsv's space from the bytes_may_use.  If that
		 * amount is higher than the inभागidual reserves, then we can
		 * assume it's tied up in delalloc reservations.
		 */
		block_rsv_size = global_rsv_size +
			delayed_block_rsv->reserved +
			delayed_refs_rsv->reserved +
			trans_rsv->reserved;
		अगर (block_rsv_size < space_info->bytes_may_use)
			delalloc_size = space_info->bytes_may_use - block_rsv_size;
		spin_unlock(&space_info->lock);

		/*
		 * We करोn't want to include the global_rsv in our calculation,
		 * because that's space we can't touch.  Subtract it from the
		 * block_rsv_size क्रम the next checks.
		 */
		block_rsv_size -= global_rsv_size;

		/*
		 * We really want to aव्योम flushing delalloc too much, as it
		 * could result in poor allocation patterns, so only flush it अगर
		 * it's larger than the rest of the pools combined.
		 */
		अगर (delalloc_size > block_rsv_size) अणु
			to_reclaim = delalloc_size;
			flush = FLUSH_DELALLOC;
		पूर्ण अन्यथा अगर (space_info->bytes_pinned >
			   (delayed_block_rsv->reserved +
			    delayed_refs_rsv->reserved)) अणु
			to_reclaim = space_info->bytes_pinned;
			flush = FORCE_COMMIT_TRANS;
		पूर्ण अन्यथा अगर (delayed_block_rsv->reserved >
			   delayed_refs_rsv->reserved) अणु
			to_reclaim = delayed_block_rsv->reserved;
			flush = FLUSH_DELAYED_ITEMS_NR;
		पूर्ण अन्यथा अणु
			to_reclaim = delayed_refs_rsv->reserved;
			flush = FLUSH_DELAYED_REFS_NR;
		पूर्ण

		/*
		 * We करोn't want to reclaim everything, just a portion, so scale
		 * करोwn the to_reclaim by 1/4.  If it takes us करोwn to 0,
		 * reclaim 1 items worth.
		 */
		to_reclaim >>= 2;
		अगर (!to_reclaim)
			to_reclaim = btrfs_calc_insert_metadata_size(fs_info, 1);
		flush_space(fs_info, space_info, to_reclaim, flush, true);
		cond_resched();
		spin_lock(&space_info->lock);
	पूर्ण

	/* We only went through once, back off our clamping. */
	अगर (loops == 1 && !space_info->reclaim_size)
		space_info->clamp = max(1, space_info->clamp - 1);
	trace_btrfs_करोne_preemptive_reclaim(fs_info, space_info);
	spin_unlock(&space_info->lock);
पूर्ण

/*
 * FLUSH_DELALLOC_WAIT:
 *   Space is मुक्तd from flushing delalloc in one of two ways.
 *
 *   1) compression is on and we allocate less space than we reserved
 *   2) we are overwriting existing space
 *
 *   For #1 that extra space is reclaimed as soon as the delalloc pages are
 *   COWed, by way of btrfs_add_reserved_bytes() which adds the actual extent
 *   length to ->bytes_reserved, and subtracts the reserved space from
 *   ->bytes_may_use.
 *
 *   For #2 this is trickier.  Once the ordered extent runs we will drop the
 *   extent in the range we are overwriting, which creates a delayed ref क्रम
 *   that मुक्तd extent.  This however is not reclaimed until the transaction
 *   commits, thus the next stages.
 *
 * RUN_DELAYED_IPUTS
 *   If we are मुक्तing inodes, we want to make sure all delayed iमाला_दो have
 *   completed, because they could have been on an inode with i_nlink == 0, and
 *   thus have been truncated and मुक्तd up space.  But again this space is not
 *   immediately re-usable, it comes in the क्रमm of a delayed ref, which must be
 *   run and then the transaction must be committed.
 *
 * FLUSH_DELAYED_REFS
 *   The above two हालs generate delayed refs that will affect
 *   ->total_bytes_pinned.  However this counter can be inconsistent with
 *   reality अगर there are outstanding delayed refs.  This is because we adjust
 *   the counter based solely on the current set of delayed refs and disregard
 *   any on-disk state which might include more refs.  So क्रम example, अगर we
 *   have an extent with 2 references, but we only drop 1, we'll see that there
 *   is a negative delayed ref count क्रम the extent and assume that the space
 *   will be मुक्तd, and thus increase ->total_bytes_pinned.
 *
 *   Running the delayed refs gives us the actual real view of what will be
 *   मुक्तd at the transaction commit समय.  This stage will not actually मुक्त
 *   space क्रम us, it just makes sure that may_commit_transaction() has all of
 *   the inक्रमmation it needs to make the right decision.
 *
 * COMMIT_TRANS
 *   This is where we reclaim all of the pinned space generated by the previous
 *   two stages.  We will not commit the transaction अगर we करोn't think we're
 *   likely to satisfy our request, which means अगर our current मुक्त space +
 *   total_bytes_pinned < reservation we will not commit.  This is why the
 *   previous states are actually important, to make sure we know क्रम sure
 *   whether committing the transaction will allow us to make progress.
 *
 * ALLOC_CHUNK_FORCE
 *   For data we start with alloc chunk क्रमce, however we could have been full
 *   beक्रमe, and then the transaction commit could have मुक्तd new block groups,
 *   so अगर we now have space to allocate करो the क्रमce chunk allocation.
 */
अटल स्थिर क्रमागत btrfs_flush_state data_flush_states[] = अणु
	FLUSH_DELALLOC_WAIT,
	RUN_DELAYED_IPUTS,
	FLUSH_DELAYED_REFS,
	COMMIT_TRANS,
	ALLOC_CHUNK_FORCE,
पूर्ण;

अटल व्योम btrfs_async_reclaim_data_space(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_space_info *space_info;
	u64 last_tickets_id;
	क्रमागत btrfs_flush_state flush_state = 0;

	fs_info = container_of(work, काष्ठा btrfs_fs_info, async_data_reclaim_work);
	space_info = fs_info->data_sinfo;

	spin_lock(&space_info->lock);
	अगर (list_empty(&space_info->tickets)) अणु
		space_info->flush = 0;
		spin_unlock(&space_info->lock);
		वापस;
	पूर्ण
	last_tickets_id = space_info->tickets_id;
	spin_unlock(&space_info->lock);

	जबतक (!space_info->full) अणु
		flush_space(fs_info, space_info, U64_MAX, ALLOC_CHUNK_FORCE, false);
		spin_lock(&space_info->lock);
		अगर (list_empty(&space_info->tickets)) अणु
			space_info->flush = 0;
			spin_unlock(&space_info->lock);
			वापस;
		पूर्ण
		last_tickets_id = space_info->tickets_id;
		spin_unlock(&space_info->lock);
	पूर्ण

	जबतक (flush_state < ARRAY_SIZE(data_flush_states)) अणु
		flush_space(fs_info, space_info, U64_MAX,
			    data_flush_states[flush_state], false);
		spin_lock(&space_info->lock);
		अगर (list_empty(&space_info->tickets)) अणु
			space_info->flush = 0;
			spin_unlock(&space_info->lock);
			वापस;
		पूर्ण

		अगर (last_tickets_id == space_info->tickets_id) अणु
			flush_state++;
		पूर्ण अन्यथा अणु
			last_tickets_id = space_info->tickets_id;
			flush_state = 0;
		पूर्ण

		अगर (flush_state >= ARRAY_SIZE(data_flush_states)) अणु
			अगर (space_info->full) अणु
				अगर (maybe_fail_all_tickets(fs_info, space_info))
					flush_state = 0;
				अन्यथा
					space_info->flush = 0;
			पूर्ण अन्यथा अणु
				flush_state = 0;
			पूर्ण
		पूर्ण
		spin_unlock(&space_info->lock);
	पूर्ण
पूर्ण

व्योम btrfs_init_async_reclaim_work(काष्ठा btrfs_fs_info *fs_info)
अणु
	INIT_WORK(&fs_info->async_reclaim_work, btrfs_async_reclaim_metadata_space);
	INIT_WORK(&fs_info->async_data_reclaim_work, btrfs_async_reclaim_data_space);
	INIT_WORK(&fs_info->preempt_reclaim_work,
		  btrfs_preempt_reclaim_metadata_space);
पूर्ण

अटल स्थिर क्रमागत btrfs_flush_state priority_flush_states[] = अणु
	FLUSH_DELAYED_ITEMS_NR,
	FLUSH_DELAYED_ITEMS,
	ALLOC_CHUNK,
पूर्ण;

अटल स्थिर क्रमागत btrfs_flush_state evict_flush_states[] = अणु
	FLUSH_DELAYED_ITEMS_NR,
	FLUSH_DELAYED_ITEMS,
	FLUSH_DELAYED_REFS_NR,
	FLUSH_DELAYED_REFS,
	FLUSH_DELALLOC,
	FLUSH_DELALLOC_WAIT,
	ALLOC_CHUNK,
	COMMIT_TRANS,
पूर्ण;

अटल व्योम priority_reclaim_metadata_space(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_space_info *space_info,
				काष्ठा reserve_ticket *ticket,
				स्थिर क्रमागत btrfs_flush_state *states,
				पूर्णांक states_nr)
अणु
	u64 to_reclaim;
	पूर्णांक flush_state;

	spin_lock(&space_info->lock);
	to_reclaim = btrfs_calc_reclaim_metadata_size(fs_info, space_info);
	अगर (!to_reclaim) अणु
		spin_unlock(&space_info->lock);
		वापस;
	पूर्ण
	spin_unlock(&space_info->lock);

	flush_state = 0;
	करो अणु
		flush_space(fs_info, space_info, to_reclaim, states[flush_state],
			    false);
		flush_state++;
		spin_lock(&space_info->lock);
		अगर (ticket->bytes == 0) अणु
			spin_unlock(&space_info->lock);
			वापस;
		पूर्ण
		spin_unlock(&space_info->lock);
	पूर्ण जबतक (flush_state < states_nr);
पूर्ण

अटल व्योम priority_reclaim_data_space(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा btrfs_space_info *space_info,
					काष्ठा reserve_ticket *ticket)
अणु
	जबतक (!space_info->full) अणु
		flush_space(fs_info, space_info, U64_MAX, ALLOC_CHUNK_FORCE, false);
		spin_lock(&space_info->lock);
		अगर (ticket->bytes == 0) अणु
			spin_unlock(&space_info->lock);
			वापस;
		पूर्ण
		spin_unlock(&space_info->lock);
	पूर्ण
पूर्ण

अटल व्योम रुको_reserve_ticket(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_space_info *space_info,
				काष्ठा reserve_ticket *ticket)

अणु
	DEFINE_WAIT(रुको);
	पूर्णांक ret = 0;

	spin_lock(&space_info->lock);
	जबतक (ticket->bytes > 0 && ticket->error == 0) अणु
		ret = prepare_to_रुको_event(&ticket->रुको, &रुको, TASK_KILLABLE);
		अगर (ret) अणु
			/*
			 * Delete us from the list. After we unlock the space
			 * info, we करोn't want the async reclaim job to reserve
			 * space क्रम this ticket. If that would happen, then the
			 * ticket's task would not known that space was reserved
			 * despite getting an error, resulting in a space leak
			 * (bytes_may_use counter of our space_info).
			 */
			हटाओ_ticket(space_info, ticket);
			ticket->error = -EINTR;
			अवरोध;
		पूर्ण
		spin_unlock(&space_info->lock);

		schedule();

		finish_रुको(&ticket->रुको, &रुको);
		spin_lock(&space_info->lock);
	पूर्ण
	spin_unlock(&space_info->lock);
पूर्ण

/**
 * Do the appropriate flushing and रुकोing क्रम a ticket
 *
 * @fs_info:    the fileप्रणाली
 * @space_info: space info क्रम the reservation
 * @ticket:     ticket क्रम the reservation
 * @start_ns:   बारtamp when the reservation started
 * @orig_bytes: amount of bytes originally reserved
 * @flush:      how much we can flush
 *
 * This करोes the work of figuring out how to flush क्रम the ticket, रुकोing क्रम
 * the reservation, and वापसing the appropriate error अगर there is one.
 */
अटल पूर्णांक handle_reserve_ticket(काष्ठा btrfs_fs_info *fs_info,
				 काष्ठा btrfs_space_info *space_info,
				 काष्ठा reserve_ticket *ticket,
				 u64 start_ns, u64 orig_bytes,
				 क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	पूर्णांक ret;

	चयन (flush) अणु
	हाल BTRFS_RESERVE_FLUSH_DATA:
	हाल BTRFS_RESERVE_FLUSH_ALL:
	हाल BTRFS_RESERVE_FLUSH_ALL_STEAL:
		रुको_reserve_ticket(fs_info, space_info, ticket);
		अवरोध;
	हाल BTRFS_RESERVE_FLUSH_LIMIT:
		priority_reclaim_metadata_space(fs_info, space_info, ticket,
						priority_flush_states,
						ARRAY_SIZE(priority_flush_states));
		अवरोध;
	हाल BTRFS_RESERVE_FLUSH_EVICT:
		priority_reclaim_metadata_space(fs_info, space_info, ticket,
						evict_flush_states,
						ARRAY_SIZE(evict_flush_states));
		अवरोध;
	हाल BTRFS_RESERVE_FLUSH_FREE_SPACE_INODE:
		priority_reclaim_data_space(fs_info, space_info, ticket);
		अवरोध;
	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण

	spin_lock(&space_info->lock);
	ret = ticket->error;
	अगर (ticket->bytes || ticket->error) अणु
		/*
		 * We were a priority ticket, so we need to delete ourselves
		 * from the list.  Because we could have other priority tickets
		 * behind us that require less space, run
		 * btrfs_try_granting_tickets() to see अगर their reservations can
		 * now be made.
		 */
		अगर (!list_empty(&ticket->list)) अणु
			हटाओ_ticket(space_info, ticket);
			btrfs_try_granting_tickets(fs_info, space_info);
		पूर्ण

		अगर (!ret)
			ret = -ENOSPC;
	पूर्ण
	spin_unlock(&space_info->lock);
	ASSERT(list_empty(&ticket->list));
	/*
	 * Check that we can't have an error set अगर the reservation succeeded,
	 * as that would confuse tasks and lead them to error out without
	 * releasing reserved space (अगर an error happens the expectation is that
	 * space wasn't reserved at all).
	 */
	ASSERT(!(ticket->bytes == 0 && ticket->error));
	trace_btrfs_reserve_ticket(fs_info, space_info->flags, orig_bytes,
				   start_ns, flush, ticket->error);
	वापस ret;
पूर्ण

/*
 * This वापसs true अगर this flush state will go through the ordinary flushing
 * code.
 */
अटल अंतरभूत bool is_normal_flushing(क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	वापस	(flush == BTRFS_RESERVE_FLUSH_ALL) ||
		(flush == BTRFS_RESERVE_FLUSH_ALL_STEAL);
पूर्ण

अटल अंतरभूत व्योम maybe_clamp_preempt(काष्ठा btrfs_fs_info *fs_info,
				       काष्ठा btrfs_space_info *space_info)
अणु
	u64 ordered = percpu_counter_sum_positive(&fs_info->ordered_bytes);
	u64 delalloc = percpu_counter_sum_positive(&fs_info->delalloc_bytes);

	/*
	 * If we're heavy on ordered operations then clamping won't help us.  We
	 * need to clamp specअगरically to keep up with dirty'ing buffered
	 * ग_लिखोrs, because there's not a 1:1 correlation of writing delalloc
	 * and मुक्तing space, like there is with flushing delayed refs or
	 * delayed nodes.  If we're alपढ़ोy more ordered than delalloc then
	 * we're keeping up, otherwise we aren't and should probably clamp.
	 */
	अगर (ordered < delalloc)
		space_info->clamp = min(space_info->clamp + 1, 8);
पूर्ण

/**
 * Try to reserve bytes from the block_rsv's space
 *
 * @fs_info:    the fileप्रणाली
 * @space_info: space info we want to allocate from
 * @orig_bytes: number of bytes we want
 * @flush:      whether or not we can flush to make our reservation
 *
 * This will reserve orig_bytes number of bytes from the space info associated
 * with the block_rsv.  If there is not enough space it will make an attempt to
 * flush out space to make room.  It will करो this by flushing delalloc अगर
 * possible or committing the transaction.  If flush is 0 then no attempts to
 * regain reservations will be made and this will fail अगर there is not enough
 * space alपढ़ोy.
 */
अटल पूर्णांक __reserve_bytes(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_space_info *space_info, u64 orig_bytes,
			   क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	काष्ठा work_काष्ठा *async_work;
	काष्ठा reserve_ticket ticket;
	u64 start_ns = 0;
	u64 used;
	पूर्णांक ret = 0;
	bool pending_tickets;

	ASSERT(orig_bytes);
	ASSERT(!current->journal_info || flush != BTRFS_RESERVE_FLUSH_ALL);

	अगर (flush == BTRFS_RESERVE_FLUSH_DATA)
		async_work = &fs_info->async_data_reclaim_work;
	अन्यथा
		async_work = &fs_info->async_reclaim_work;

	spin_lock(&space_info->lock);
	ret = -ENOSPC;
	used = btrfs_space_info_used(space_info, true);

	/*
	 * We करोn't want NO_FLUSH allocations to jump everybody, they can
	 * generally handle ENOSPC in a dअगरferent way, so treat them the same as
	 * normal flushers when it comes to skipping pending tickets.
	 */
	अगर (is_normal_flushing(flush) || (flush == BTRFS_RESERVE_NO_FLUSH))
		pending_tickets = !list_empty(&space_info->tickets) ||
			!list_empty(&space_info->priority_tickets);
	अन्यथा
		pending_tickets = !list_empty(&space_info->priority_tickets);

	/*
	 * Carry on अगर we have enough space (लघु-circuit) OR call
	 * can_overcommit() to ensure we can overcommit to जारी.
	 */
	अगर (!pending_tickets &&
	    ((used + orig_bytes <= space_info->total_bytes) ||
	     btrfs_can_overcommit(fs_info, space_info, orig_bytes, flush))) अणु
		btrfs_space_info_update_bytes_may_use(fs_info, space_info,
						      orig_bytes);
		ret = 0;
	पूर्ण

	/*
	 * If we couldn't make a reservation then setup our reservation ticket
	 * and kick the async worker अगर it's not alपढ़ोy running.
	 *
	 * If we are a priority flusher then we just need to add our ticket to
	 * the list and we will करो our own flushing further करोwn.
	 */
	अगर (ret && flush != BTRFS_RESERVE_NO_FLUSH) अणु
		ticket.bytes = orig_bytes;
		ticket.error = 0;
		space_info->reclaim_size += ticket.bytes;
		init_रुकोqueue_head(&ticket.रुको);
		ticket.steal = (flush == BTRFS_RESERVE_FLUSH_ALL_STEAL);
		अगर (trace_btrfs_reserve_ticket_enabled())
			start_ns = kसमय_get_ns();

		अगर (flush == BTRFS_RESERVE_FLUSH_ALL ||
		    flush == BTRFS_RESERVE_FLUSH_ALL_STEAL ||
		    flush == BTRFS_RESERVE_FLUSH_DATA) अणु
			list_add_tail(&ticket.list, &space_info->tickets);
			अगर (!space_info->flush) अणु
				space_info->flush = 1;
				trace_btrfs_trigger_flush(fs_info,
							  space_info->flags,
							  orig_bytes, flush,
							  "enospc");
				queue_work(प्रणाली_unbound_wq, async_work);
			पूर्ण
		पूर्ण अन्यथा अणु
			list_add_tail(&ticket.list,
				      &space_info->priority_tickets);
		पूर्ण

		/*
		 * We were क्रमced to add a reserve ticket, so our preemptive
		 * flushing is unable to keep up.  Clamp करोwn on the threshold
		 * क्रम the preemptive flushing in order to keep up with the
		 * workload.
		 */
		maybe_clamp_preempt(fs_info, space_info);
	पूर्ण अन्यथा अगर (!ret && space_info->flags & BTRFS_BLOCK_GROUP_METADATA) अणु
		used += orig_bytes;
		/*
		 * We will करो the space reservation dance during log replay,
		 * which means we won't have fs_info->fs_root set, so don't करो
		 * the async reclaim as we will panic.
		 */
		अगर (!test_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags) &&
		    need_preemptive_reclaim(fs_info, space_info) &&
		    !work_busy(&fs_info->preempt_reclaim_work)) अणु
			trace_btrfs_trigger_flush(fs_info, space_info->flags,
						  orig_bytes, flush, "preempt");
			queue_work(प्रणाली_unbound_wq,
				   &fs_info->preempt_reclaim_work);
		पूर्ण
	पूर्ण
	spin_unlock(&space_info->lock);
	अगर (!ret || flush == BTRFS_RESERVE_NO_FLUSH)
		वापस ret;

	वापस handle_reserve_ticket(fs_info, space_info, &ticket, start_ns,
				     orig_bytes, flush);
पूर्ण

/**
 * Trye to reserve metadata bytes from the block_rsv's space
 *
 * @root:       the root we're allocating क्रम
 * @block_rsv:  block_rsv we're allocating क्रम
 * @orig_bytes: number of bytes we want
 * @flush:      whether or not we can flush to make our reservation
 *
 * This will reserve orig_bytes number of bytes from the space info associated
 * with the block_rsv.  If there is not enough space it will make an attempt to
 * flush out space to make room.  It will करो this by flushing delalloc अगर
 * possible or committing the transaction.  If flush is 0 then no attempts to
 * regain reservations will be made and this will fail अगर there is not enough
 * space alपढ़ोy.
 */
पूर्णांक btrfs_reserve_metadata_bytes(काष्ठा btrfs_root *root,
				 काष्ठा btrfs_block_rsv *block_rsv,
				 u64 orig_bytes,
				 क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	काष्ठा btrfs_fs_info *fs_info = root->fs_info;
	काष्ठा btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	पूर्णांक ret;

	ret = __reserve_bytes(fs_info, block_rsv->space_info, orig_bytes, flush);
	अगर (ret == -ENOSPC &&
	    unlikely(root->orphan_cleanup_state == ORPHAN_CLEANUP_STARTED)) अणु
		अगर (block_rsv != global_rsv &&
		    !btrfs_block_rsv_use_bytes(global_rsv, orig_bytes))
			ret = 0;
	पूर्ण
	अगर (ret == -ENOSPC) अणु
		trace_btrfs_space_reservation(fs_info, "space_info:enospc",
					      block_rsv->space_info->flags,
					      orig_bytes, 1);

		अगर (btrfs_test_opt(fs_info, ENOSPC_DEBUG))
			btrfs_dump_space_info(fs_info, block_rsv->space_info,
					      orig_bytes, 0);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * Try to reserve data bytes क्रम an allocation
 *
 * @fs_info: the fileप्रणाली
 * @bytes:   number of bytes we need
 * @flush:   how we are allowed to flush
 *
 * This will reserve bytes from the data space info.  If there is not enough
 * space then we will attempt to flush space as specअगरied by flush.
 */
पूर्णांक btrfs_reserve_data_bytes(काष्ठा btrfs_fs_info *fs_info, u64 bytes,
			     क्रमागत btrfs_reserve_flush_क्रमागत flush)
अणु
	काष्ठा btrfs_space_info *data_sinfo = fs_info->data_sinfo;
	पूर्णांक ret;

	ASSERT(flush == BTRFS_RESERVE_FLUSH_DATA ||
	       flush == BTRFS_RESERVE_FLUSH_FREE_SPACE_INODE);
	ASSERT(!current->journal_info || flush != BTRFS_RESERVE_FLUSH_DATA);

	ret = __reserve_bytes(fs_info, data_sinfo, bytes, flush);
	अगर (ret == -ENOSPC) अणु
		trace_btrfs_space_reservation(fs_info, "space_info:enospc",
					      data_sinfo->flags, bytes, 1);
		अगर (btrfs_test_opt(fs_info, ENOSPC_DEBUG))
			btrfs_dump_space_info(fs_info, data_sinfo, bytes, 0);
	पूर्ण
	वापस ret;
पूर्ण
