<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/math64.h>
#समावेश <linux/sizes.h>
#समावेश <linux/workqueue.h>
#समावेश "ctree.h"
#समावेश "block-group.h"
#समावेश "discard.h"
#समावेश "free-space-cache.h"

/*
 * This contains the logic to handle async discard.
 *
 * Async discard manages trimming of मुक्त space outside of transaction commit.
 * Discarding is करोne by managing the block_groups on a LRU list based on मुक्त
 * space recency.  Two passes are used to first prioritize discarding extents
 * and then allow क्रम trimming in the biपंचांगap the best opportunity to coalesce.
 * The block_groups are मुख्यtained on multiple lists to allow क्रम multiple
 * passes with dअगरferent discard filter requirements.  A delayed work item is
 * used to manage discarding with समयout determined by a max of the delay
 * incurred by the iops rate limit, the byte rate limit, and the max delay of
 * BTRFS_DISCARD_MAX_DELAY.
 *
 * Note, this only keeps track of block_groups that are explicitly क्रम data.
 * Mixed block_groups are not supported.
 *
 * The first list is special to manage discarding of fully मुक्त block groups.
 * This is necessary because we issue a final trim क्रम a full मुक्त block group
 * after क्रमgetting it.  When a block group becomes unused, instead of directly
 * being added to the unused_bgs list, we add it to this first list.  Then
 * from there, अगर it becomes fully discarded, we place it onto the unused_bgs
 * list.
 *
 * The in-memory मुक्त space cache serves as the backing state क्रम discard.
 * Consequently this means there is no persistence.  We opt to load all the
 * block groups in as not discarded, so the mount हाल degenerates to the
 * crashing हाल.
 *
 * As the मुक्त space cache uses biपंचांगaps, there exists a tradeoff between
 * ease/efficiency क्रम find_मुक्त_extent() and the accuracy of discard state.
 * Here we opt to let untrimmed regions merge with everything जबतक only letting
 * trimmed regions merge with other trimmed regions.  This can cause
 * overtrimming, but the coalescing benefit seems to be worth it.  Additionally,
 * biपंचांगap state is tracked as a whole.  If we're able to fully trim a biपंचांगap,
 * the trimmed flag is set on the biपंचांगap.  Otherwise, अगर an allocation comes in,
 * this resets the state and we will retry trimming the whole biपंचांगap.  This is a
 * tradeoff between discard state accuracy and the cost of accounting.
 */

/* This is an initial delay to give some chance क्रम block reuse */
#घोषणा BTRFS_DISCARD_DELAY		(120ULL * NSEC_PER_SEC)
#घोषणा BTRFS_DISCARD_UNUSED_DELAY	(10ULL * NSEC_PER_SEC)

/* Target completion latency of discarding all discardable extents */
#घोषणा BTRFS_DISCARD_TARGET_MSEC	(6 * 60 * 60UL * MSEC_PER_SEC)
#घोषणा BTRFS_DISCARD_MIN_DELAY_MSEC	(1UL)
#घोषणा BTRFS_DISCARD_MAX_DELAY_MSEC	(1000UL)
#घोषणा BTRFS_DISCARD_MAX_IOPS		(10U)

/* Montonically decreasing minimum length filters after index 0 */
अटल पूर्णांक discard_minlen[BTRFS_NR_DISCARD_LISTS] = अणु
	0,
	BTRFS_ASYNC_DISCARD_MAX_FILTER,
	BTRFS_ASYNC_DISCARD_MIN_FILTER
पूर्ण;

अटल काष्ठा list_head *get_discard_list(काष्ठा btrfs_discard_ctl *discard_ctl,
					  काष्ठा btrfs_block_group *block_group)
अणु
	वापस &discard_ctl->discard_list[block_group->discard_index];
पूर्ण

अटल व्योम __add_to_discard_list(काष्ठा btrfs_discard_ctl *discard_ctl,
				  काष्ठा btrfs_block_group *block_group)
अणु
	अगर (!btrfs_run_discard_work(discard_ctl))
		वापस;

	अगर (list_empty(&block_group->discard_list) ||
	    block_group->discard_index == BTRFS_DISCARD_INDEX_UNUSED) अणु
		अगर (block_group->discard_index == BTRFS_DISCARD_INDEX_UNUSED)
			block_group->discard_index = BTRFS_DISCARD_INDEX_START;
		block_group->discard_eligible_समय = (kसमय_get_ns() +
						      BTRFS_DISCARD_DELAY);
		block_group->discard_state = BTRFS_DISCARD_RESET_CURSOR;
	पूर्ण

	list_move_tail(&block_group->discard_list,
		       get_discard_list(discard_ctl, block_group));
पूर्ण

अटल व्योम add_to_discard_list(काष्ठा btrfs_discard_ctl *discard_ctl,
				काष्ठा btrfs_block_group *block_group)
अणु
	अगर (!btrfs_is_block_group_data_only(block_group))
		वापस;

	spin_lock(&discard_ctl->lock);
	__add_to_discard_list(discard_ctl, block_group);
	spin_unlock(&discard_ctl->lock);
पूर्ण

अटल व्योम add_to_discard_unused_list(काष्ठा btrfs_discard_ctl *discard_ctl,
				       काष्ठा btrfs_block_group *block_group)
अणु
	spin_lock(&discard_ctl->lock);

	अगर (!btrfs_run_discard_work(discard_ctl)) अणु
		spin_unlock(&discard_ctl->lock);
		वापस;
	पूर्ण

	list_del_init(&block_group->discard_list);

	block_group->discard_index = BTRFS_DISCARD_INDEX_UNUSED;
	block_group->discard_eligible_समय = (kसमय_get_ns() +
					      BTRFS_DISCARD_UNUSED_DELAY);
	block_group->discard_state = BTRFS_DISCARD_RESET_CURSOR;
	list_add_tail(&block_group->discard_list,
		      &discard_ctl->discard_list[BTRFS_DISCARD_INDEX_UNUSED]);

	spin_unlock(&discard_ctl->lock);
पूर्ण

अटल bool हटाओ_from_discard_list(काष्ठा btrfs_discard_ctl *discard_ctl,
				     काष्ठा btrfs_block_group *block_group)
अणु
	bool running = false;

	spin_lock(&discard_ctl->lock);

	अगर (block_group == discard_ctl->block_group) अणु
		running = true;
		discard_ctl->block_group = शून्य;
	पूर्ण

	block_group->discard_eligible_समय = 0;
	list_del_init(&block_group->discard_list);

	spin_unlock(&discard_ctl->lock);

	वापस running;
पूर्ण

/**
 * find_next_block_group - find block_group that's up next क्रम discarding
 * @discard_ctl: discard control
 * @now: current समय
 *
 * Iterate over the discard lists to find the next block_group up क्रम
 * discarding checking the discard_eligible_समय of block_group.
 */
अटल काष्ठा btrfs_block_group *find_next_block_group(
					काष्ठा btrfs_discard_ctl *discard_ctl,
					u64 now)
अणु
	काष्ठा btrfs_block_group *ret_block_group = शून्य, *block_group;
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_NR_DISCARD_LISTS; i++) अणु
		काष्ठा list_head *discard_list = &discard_ctl->discard_list[i];

		अगर (!list_empty(discard_list)) अणु
			block_group = list_first_entry(discard_list,
						       काष्ठा btrfs_block_group,
						       discard_list);

			अगर (!ret_block_group)
				ret_block_group = block_group;

			अगर (ret_block_group->discard_eligible_समय < now)
				अवरोध;

			अगर (ret_block_group->discard_eligible_समय >
			    block_group->discard_eligible_समय)
				ret_block_group = block_group;
		पूर्ण
	पूर्ण

	वापस ret_block_group;
पूर्ण

/**
 * Wrap find_next_block_group()
 *
 * @discard_ctl:   discard control
 * @discard_state: the discard_state of the block_group after state management
 * @discard_index: the discard_index of the block_group after state management
 * @now:           समय when discard was invoked, in ns
 *
 * This wraps find_next_block_group() and sets the block_group to be in use.
 * discard_state's control flow is managed here.  Variables related to
 * discard_state are reset here as needed (eg discard_cursor).  @discard_state
 * and @discard_index are remembered as it may change जबतक we're discarding,
 * but we want the discard to execute in the context determined here.
 */
अटल काष्ठा btrfs_block_group *peek_discard_list(
					काष्ठा btrfs_discard_ctl *discard_ctl,
					क्रमागत btrfs_discard_state *discard_state,
					पूर्णांक *discard_index, u64 now)
अणु
	काष्ठा btrfs_block_group *block_group;

	spin_lock(&discard_ctl->lock);
again:
	block_group = find_next_block_group(discard_ctl, now);

	अगर (block_group && now >= block_group->discard_eligible_समय) अणु
		अगर (block_group->discard_index == BTRFS_DISCARD_INDEX_UNUSED &&
		    block_group->used != 0) अणु
			अगर (btrfs_is_block_group_data_only(block_group))
				__add_to_discard_list(discard_ctl, block_group);
			अन्यथा
				list_del_init(&block_group->discard_list);
			जाओ again;
		पूर्ण
		अगर (block_group->discard_state == BTRFS_DISCARD_RESET_CURSOR) अणु
			block_group->discard_cursor = block_group->start;
			block_group->discard_state = BTRFS_DISCARD_EXTENTS;
		पूर्ण
		discard_ctl->block_group = block_group;
	पूर्ण
	अगर (block_group) अणु
		*discard_state = block_group->discard_state;
		*discard_index = block_group->discard_index;
	पूर्ण
	spin_unlock(&discard_ctl->lock);

	वापस block_group;
पूर्ण

/**
 * btrfs_discard_check_filter - updates a block groups filters
 * @block_group: block group of पूर्णांकerest
 * @bytes: recently मुक्तd region size after coalescing
 *
 * Async discard मुख्यtains multiple lists with progressively smaller filters
 * to prioritize discarding based on size.  Should a मुक्त space that matches
 * a larger filter be वापसed to the मुक्त_space_cache, prioritize that discard
 * by moving @block_group to the proper filter.
 */
व्योम btrfs_discard_check_filter(काष्ठा btrfs_block_group *block_group,
				u64 bytes)
अणु
	काष्ठा btrfs_discard_ctl *discard_ctl;

	अगर (!block_group ||
	    !btrfs_test_opt(block_group->fs_info, DISCARD_ASYNC))
		वापस;

	discard_ctl = &block_group->fs_info->discard_ctl;

	अगर (block_group->discard_index > BTRFS_DISCARD_INDEX_START &&
	    bytes >= discard_minlen[block_group->discard_index - 1]) अणु
		पूर्णांक i;

		हटाओ_from_discard_list(discard_ctl, block_group);

		क्रम (i = BTRFS_DISCARD_INDEX_START; i < BTRFS_NR_DISCARD_LISTS;
		     i++) अणु
			अगर (bytes >= discard_minlen[i]) अणु
				block_group->discard_index = i;
				add_to_discard_list(discard_ctl, block_group);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * btrfs_update_discard_index - moves a block group aदीर्घ the discard lists
 * @discard_ctl: discard control
 * @block_group: block_group of पूर्णांकerest
 *
 * Increment @block_group's discard_index.  If it falls of the list, let it be.
 * Otherwise add it back to the appropriate list.
 */
अटल व्योम btrfs_update_discard_index(काष्ठा btrfs_discard_ctl *discard_ctl,
				       काष्ठा btrfs_block_group *block_group)
अणु
	block_group->discard_index++;
	अगर (block_group->discard_index == BTRFS_NR_DISCARD_LISTS) अणु
		block_group->discard_index = 1;
		वापस;
	पूर्ण

	add_to_discard_list(discard_ctl, block_group);
पूर्ण

/**
 * btrfs_discard_cancel_work - हटाओ a block_group from the discard lists
 * @discard_ctl: discard control
 * @block_group: block_group of पूर्णांकerest
 *
 * This हटाओs @block_group from the discard lists.  If necessary, it रुकोs on
 * the current work and then reschedules the delayed work.
 */
व्योम btrfs_discard_cancel_work(काष्ठा btrfs_discard_ctl *discard_ctl,
			       काष्ठा btrfs_block_group *block_group)
अणु
	अगर (हटाओ_from_discard_list(discard_ctl, block_group)) अणु
		cancel_delayed_work_sync(&discard_ctl->work);
		btrfs_discard_schedule_work(discard_ctl, true);
	पूर्ण
पूर्ण

/**
 * btrfs_discard_queue_work - handles queuing the block_groups
 * @discard_ctl: discard control
 * @block_group: block_group of पूर्णांकerest
 *
 * This मुख्यtains the LRU order of the discard lists.
 */
व्योम btrfs_discard_queue_work(काष्ठा btrfs_discard_ctl *discard_ctl,
			      काष्ठा btrfs_block_group *block_group)
अणु
	अगर (!block_group || !btrfs_test_opt(block_group->fs_info, DISCARD_ASYNC))
		वापस;

	अगर (block_group->used == 0)
		add_to_discard_unused_list(discard_ctl, block_group);
	अन्यथा
		add_to_discard_list(discard_ctl, block_group);

	अगर (!delayed_work_pending(&discard_ctl->work))
		btrfs_discard_schedule_work(discard_ctl, false);
पूर्ण

अटल व्योम __btrfs_discard_schedule_work(काष्ठा btrfs_discard_ctl *discard_ctl,
					  u64 now, bool override)
अणु
	काष्ठा btrfs_block_group *block_group;

	अगर (!btrfs_run_discard_work(discard_ctl))
		वापस;
	अगर (!override && delayed_work_pending(&discard_ctl->work))
		वापस;

	block_group = find_next_block_group(discard_ctl, now);
	अगर (block_group) अणु
		u64 delay = discard_ctl->delay_ms * NSEC_PER_MSEC;
		u32 kbps_limit = READ_ONCE(discard_ctl->kbps_limit);

		/*
		 * A single delayed workqueue item is responsible क्रम
		 * discarding, so we can manage the bytes rate limit by keeping
		 * track of the previous discard.
		 */
		अगर (kbps_limit && discard_ctl->prev_discard) अणु
			u64 bps_limit = ((u64)kbps_limit) * SZ_1K;
			u64 bps_delay = भाग64_u64(discard_ctl->prev_discard *
						  NSEC_PER_SEC, bps_limit);

			delay = max(delay, bps_delay);
		पूर्ण

		/*
		 * This समयout is to hopefully prevent immediate discarding
		 * in a recently allocated block group.
		 */
		अगर (now < block_group->discard_eligible_समय) अणु
			u64 bg_समयout = block_group->discard_eligible_समय - now;

			delay = max(delay, bg_समयout);
		पूर्ण

		अगर (override && discard_ctl->prev_discard) अणु
			u64 elapsed = now - discard_ctl->prev_discard_समय;

			अगर (delay > elapsed)
				delay -= elapsed;
			अन्यथा
				delay = 0;
		पूर्ण

		mod_delayed_work(discard_ctl->discard_workers,
				 &discard_ctl->work, nsecs_to_jअगरfies(delay));
	पूर्ण
पूर्ण

/*
 * btrfs_discard_schedule_work - responsible क्रम scheduling the discard work
 * @discard_ctl:  discard control
 * @override:     override the current समयr
 *
 * Discards are issued by a delayed workqueue item.  @override is used to
 * update the current delay as the baseline delay पूर्णांकerval is reevaluated on
 * transaction commit.  This is also maxed with any other rate limit.
 */
व्योम btrfs_discard_schedule_work(काष्ठा btrfs_discard_ctl *discard_ctl,
				 bool override)
अणु
	स्थिर u64 now = kसमय_get_ns();

	spin_lock(&discard_ctl->lock);
	__btrfs_discard_schedule_work(discard_ctl, now, override);
	spin_unlock(&discard_ctl->lock);
पूर्ण

/**
 * btrfs_finish_discard_pass - determine next step of a block_group
 * @discard_ctl: discard control
 * @block_group: block_group of पूर्णांकerest
 *
 * This determines the next step क्रम a block group after it's finished going
 * through a pass on a discard list.  If it is unused and fully trimmed, we can
 * mark it unused and send it to the unused_bgs path.  Otherwise, pass it onto
 * the appropriate filter list or let it fall off.
 */
अटल व्योम btrfs_finish_discard_pass(काष्ठा btrfs_discard_ctl *discard_ctl,
				      काष्ठा btrfs_block_group *block_group)
अणु
	हटाओ_from_discard_list(discard_ctl, block_group);

	अगर (block_group->used == 0) अणु
		अगर (btrfs_is_मुक्त_space_trimmed(block_group))
			btrfs_mark_bg_unused(block_group);
		अन्यथा
			add_to_discard_unused_list(discard_ctl, block_group);
	पूर्ण अन्यथा अणु
		btrfs_update_discard_index(discard_ctl, block_group);
	पूर्ण
पूर्ण

/**
 * btrfs_discard_workfn - discard work function
 * @work: work
 *
 * This finds the next block_group to start discarding and then discards a
 * single region.  It करोes this in a two-pass fashion: first extents and second
 * biपंचांगaps.  Completely discarded block groups are sent to the unused_bgs path.
 */
अटल व्योम btrfs_discard_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा btrfs_discard_ctl *discard_ctl;
	काष्ठा btrfs_block_group *block_group;
	क्रमागत btrfs_discard_state discard_state;
	पूर्णांक discard_index = 0;
	u64 trimmed = 0;
	u64 minlen = 0;
	u64 now = kसमय_get_ns();

	discard_ctl = container_of(work, काष्ठा btrfs_discard_ctl, work.work);

	block_group = peek_discard_list(discard_ctl, &discard_state,
					&discard_index, now);
	अगर (!block_group || !btrfs_run_discard_work(discard_ctl))
		वापस;
	अगर (now < block_group->discard_eligible_समय) अणु
		btrfs_discard_schedule_work(discard_ctl, false);
		वापस;
	पूर्ण

	/* Perक्रमm discarding */
	minlen = discard_minlen[discard_index];

	अगर (discard_state == BTRFS_DISCARD_BITMAPS) अणु
		u64 maxlen = 0;

		/*
		 * Use the previous levels minimum discard length as the max
		 * length filter.  In the हाल something is added to make a
		 * region go beyond the max filter, the entire biपंचांगap is set
		 * back to BTRFS_TRIM_STATE_UNTRIMMED.
		 */
		अगर (discard_index != BTRFS_DISCARD_INDEX_UNUSED)
			maxlen = discard_minlen[discard_index - 1];

		btrfs_trim_block_group_biपंचांगaps(block_group, &trimmed,
				       block_group->discard_cursor,
				       btrfs_block_group_end(block_group),
				       minlen, maxlen, true);
		discard_ctl->discard_biपंचांगap_bytes += trimmed;
	पूर्ण अन्यथा अणु
		btrfs_trim_block_group_extents(block_group, &trimmed,
				       block_group->discard_cursor,
				       btrfs_block_group_end(block_group),
				       minlen, true);
		discard_ctl->discard_extent_bytes += trimmed;
	पूर्ण

	/* Determine next steps क्रम a block_group */
	अगर (block_group->discard_cursor >= btrfs_block_group_end(block_group)) अणु
		अगर (discard_state == BTRFS_DISCARD_BITMAPS) अणु
			btrfs_finish_discard_pass(discard_ctl, block_group);
		पूर्ण अन्यथा अणु
			block_group->discard_cursor = block_group->start;
			spin_lock(&discard_ctl->lock);
			अगर (block_group->discard_state !=
			    BTRFS_DISCARD_RESET_CURSOR)
				block_group->discard_state =
							BTRFS_DISCARD_BITMAPS;
			spin_unlock(&discard_ctl->lock);
		पूर्ण
	पूर्ण

	now = kसमय_get_ns();
	spin_lock(&discard_ctl->lock);
	discard_ctl->prev_discard = trimmed;
	discard_ctl->prev_discard_समय = now;
	discard_ctl->block_group = शून्य;
	__btrfs_discard_schedule_work(discard_ctl, now, false);
	spin_unlock(&discard_ctl->lock);
पूर्ण

/**
 * btrfs_run_discard_work - determines अगर async discard should be running
 * @discard_ctl: discard control
 *
 * Checks अगर the file प्रणाली is ग_लिखोable and BTRFS_FS_DISCARD_RUNNING is set.
 */
bool btrfs_run_discard_work(काष्ठा btrfs_discard_ctl *discard_ctl)
अणु
	काष्ठा btrfs_fs_info *fs_info = container_of(discard_ctl,
						     काष्ठा btrfs_fs_info,
						     discard_ctl);

	वापस (!(fs_info->sb->s_flags & SB_RDONLY) &&
		test_bit(BTRFS_FS_DISCARD_RUNNING, &fs_info->flags));
पूर्ण

/**
 * btrfs_discard_calc_delay - recalculate the base delay
 * @discard_ctl: discard control
 *
 * Recalculate the base delay which is based off the total number of
 * discardable_extents.  Clamp this between the lower_limit (iops_limit or 1ms)
 * and the upper_limit (BTRFS_DISCARD_MAX_DELAY_MSEC).
 */
व्योम btrfs_discard_calc_delay(काष्ठा btrfs_discard_ctl *discard_ctl)
अणु
	s32 discardable_extents;
	s64 discardable_bytes;
	u32 iops_limit;
	अचिन्हित दीर्घ delay;

	discardable_extents = atomic_पढ़ो(&discard_ctl->discardable_extents);
	अगर (!discardable_extents)
		वापस;

	spin_lock(&discard_ctl->lock);

	/*
	 * The following is to fix a potential -1 discrepenancy that we're not
	 * sure how to reproduce. But given that this is the only place that
	 * utilizes these numbers and this is only called by from
	 * btrfs_finish_extent_commit() which is synchronized, we can correct
	 * here.
	 */
	अगर (discardable_extents < 0)
		atomic_add(-discardable_extents,
			   &discard_ctl->discardable_extents);

	discardable_bytes = atomic64_पढ़ो(&discard_ctl->discardable_bytes);
	अगर (discardable_bytes < 0)
		atomic64_add(-discardable_bytes,
			     &discard_ctl->discardable_bytes);

	अगर (discardable_extents <= 0) अणु
		spin_unlock(&discard_ctl->lock);
		वापस;
	पूर्ण

	iops_limit = READ_ONCE(discard_ctl->iops_limit);
	अगर (iops_limit)
		delay = MSEC_PER_SEC / iops_limit;
	अन्यथा
		delay = BTRFS_DISCARD_TARGET_MSEC / discardable_extents;

	delay = clamp(delay, BTRFS_DISCARD_MIN_DELAY_MSEC,
		      BTRFS_DISCARD_MAX_DELAY_MSEC);
	discard_ctl->delay_ms = delay;

	spin_unlock(&discard_ctl->lock);
पूर्ण

/**
 * btrfs_discard_update_discardable - propagate discard counters
 * @block_group: block_group of पूर्णांकerest
 *
 * This propagates deltas of counters up to the discard_ctl.  It मुख्यtains a
 * current counter and a previous counter passing the delta up to the global
 * stat.  Then the current counter value becomes the previous counter value.
 */
व्योम btrfs_discard_update_discardable(काष्ठा btrfs_block_group *block_group)
अणु
	काष्ठा btrfs_मुक्त_space_ctl *ctl;
	काष्ठा btrfs_discard_ctl *discard_ctl;
	s32 extents_delta;
	s64 bytes_delta;

	अगर (!block_group ||
	    !btrfs_test_opt(block_group->fs_info, DISCARD_ASYNC) ||
	    !btrfs_is_block_group_data_only(block_group))
		वापस;

	ctl = block_group->मुक्त_space_ctl;
	discard_ctl = &block_group->fs_info->discard_ctl;

	lockdep_निश्चित_held(&ctl->tree_lock);
	extents_delta = ctl->discardable_extents[BTRFS_STAT_CURR] -
			ctl->discardable_extents[BTRFS_STAT_PREV];
	अगर (extents_delta) अणु
		atomic_add(extents_delta, &discard_ctl->discardable_extents);
		ctl->discardable_extents[BTRFS_STAT_PREV] =
			ctl->discardable_extents[BTRFS_STAT_CURR];
	पूर्ण

	bytes_delta = ctl->discardable_bytes[BTRFS_STAT_CURR] -
		      ctl->discardable_bytes[BTRFS_STAT_PREV];
	अगर (bytes_delta) अणु
		atomic64_add(bytes_delta, &discard_ctl->discardable_bytes);
		ctl->discardable_bytes[BTRFS_STAT_PREV] =
			ctl->discardable_bytes[BTRFS_STAT_CURR];
	पूर्ण
पूर्ण

/**
 * btrfs_discard_punt_unused_bgs_list - punt unused_bgs list to discard lists
 * @fs_info: fs_info of पूर्णांकerest
 *
 * The unused_bgs list needs to be punted to the discard lists because the
 * order of operations is changed.  In the normal sychronous discard path, the
 * block groups are trimmed via a single large trim in transaction commit.  This
 * is ultimately what we are trying to aव्योम with asynchronous discard.  Thus,
 * it must be करोne beक्रमe going करोwn the unused_bgs path.
 */
व्योम btrfs_discard_punt_unused_bgs_list(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_block_group *block_group, *next;

	spin_lock(&fs_info->unused_bgs_lock);
	/* We enabled async discard, so punt all to the queue */
	list_क्रम_each_entry_safe(block_group, next, &fs_info->unused_bgs,
				 bg_list) अणु
		list_del_init(&block_group->bg_list);
		btrfs_put_block_group(block_group);
		btrfs_discard_queue_work(&fs_info->discard_ctl, block_group);
	पूर्ण
	spin_unlock(&fs_info->unused_bgs_lock);
पूर्ण

/**
 * btrfs_discard_purge_list - purge discard lists
 * @discard_ctl: discard control
 *
 * If we are disabling async discard, we may have पूर्णांकercepted block groups that
 * are completely मुक्त and पढ़ोy क्रम the unused_bgs path.  As discarding will
 * now happen in transaction commit or not at all, we can safely mark the
 * corresponding block groups as unused and they will be sent on their merry
 * way to the unused_bgs list.
 */
अटल व्योम btrfs_discard_purge_list(काष्ठा btrfs_discard_ctl *discard_ctl)
अणु
	काष्ठा btrfs_block_group *block_group, *next;
	पूर्णांक i;

	spin_lock(&discard_ctl->lock);
	क्रम (i = 0; i < BTRFS_NR_DISCARD_LISTS; i++) अणु
		list_क्रम_each_entry_safe(block_group, next,
					 &discard_ctl->discard_list[i],
					 discard_list) अणु
			list_del_init(&block_group->discard_list);
			spin_unlock(&discard_ctl->lock);
			अगर (block_group->used == 0)
				btrfs_mark_bg_unused(block_group);
			spin_lock(&discard_ctl->lock);
		पूर्ण
	पूर्ण
	spin_unlock(&discard_ctl->lock);
पूर्ण

व्योम btrfs_discard_resume(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!btrfs_test_opt(fs_info, DISCARD_ASYNC)) अणु
		btrfs_discard_cleanup(fs_info);
		वापस;
	पूर्ण

	btrfs_discard_punt_unused_bgs_list(fs_info);

	set_bit(BTRFS_FS_DISCARD_RUNNING, &fs_info->flags);
पूर्ण

व्योम btrfs_discard_stop(काष्ठा btrfs_fs_info *fs_info)
अणु
	clear_bit(BTRFS_FS_DISCARD_RUNNING, &fs_info->flags);
पूर्ण

व्योम btrfs_discard_init(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_discard_ctl *discard_ctl = &fs_info->discard_ctl;
	पूर्णांक i;

	spin_lock_init(&discard_ctl->lock);
	INIT_DELAYED_WORK(&discard_ctl->work, btrfs_discard_workfn);

	क्रम (i = 0; i < BTRFS_NR_DISCARD_LISTS; i++)
		INIT_LIST_HEAD(&discard_ctl->discard_list[i]);

	discard_ctl->prev_discard = 0;
	discard_ctl->prev_discard_समय = 0;
	atomic_set(&discard_ctl->discardable_extents, 0);
	atomic64_set(&discard_ctl->discardable_bytes, 0);
	discard_ctl->max_discard_size = BTRFS_ASYNC_DISCARD_DEFAULT_MAX_SIZE;
	discard_ctl->delay_ms = BTRFS_DISCARD_MAX_DELAY_MSEC;
	discard_ctl->iops_limit = BTRFS_DISCARD_MAX_IOPS;
	discard_ctl->kbps_limit = 0;
	discard_ctl->discard_extent_bytes = 0;
	discard_ctl->discard_biपंचांगap_bytes = 0;
	atomic64_set(&discard_ctl->discard_bytes_saved, 0);
पूर्ण

व्योम btrfs_discard_cleanup(काष्ठा btrfs_fs_info *fs_info)
अणु
	btrfs_discard_stop(fs_info);
	cancel_delayed_work_sync(&fs_info->discard_ctl.work);
	btrfs_discard_purge_list(&fs_info->discard_ctl);
पूर्ण
