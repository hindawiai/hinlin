<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Shaohua Li <shli@fb.com>
 * Copyright (C) 2016 Song Liu <songliubraving@fb.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/raid/md_p.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/types.h>
#समावेश "md.h"
#समावेश "raid5.h"
#समावेश "md-bitmap.h"
#समावेश "raid5-log.h"

/*
 * metadata/data stored in disk with 4k size unit (a block) regardless
 * underneath hardware sector size. only works with PAGE_SIZE == 4096
 */
#घोषणा BLOCK_SECTORS (8)
#घोषणा BLOCK_SECTOR_SHIFT (3)

/*
 * log->max_मुक्त_space is min(1/4 disk size, 10G reclaimable space).
 *
 * In ग_लिखो through mode, the reclaim runs every log->max_मुक्त_space.
 * This can prevent the recovery scans क्रम too दीर्घ
 */
#घोषणा RECLAIM_MAX_FREE_SPACE (10 * 1024 * 1024 * 2) /* sector */
#घोषणा RECLAIM_MAX_FREE_SPACE_SHIFT (2)

/* wake up reclaim thपढ़ो periodically */
#घोषणा R5C_RECLAIM_WAKEUP_INTERVAL (30 * HZ)
/* start flush with these full stripes */
#घोषणा R5C_FULL_STRIPE_FLUSH_BATCH(conf) (conf->max_nr_stripes / 4)
/* reclaim stripes in groups */
#घोषणा R5C_RECLAIM_STRIPE_GROUP (NR_STRIPE_HASH_LOCKS * 2)

/*
 * We only need 2 bios per I/O unit to make progress, but ensure we
 * have a few more available to not get too tight.
 */
#घोषणा R5L_POOL_SIZE	4

अटल अक्षर *r5c_journal_mode_str[] = अणु"write-through",
				       "write-back"पूर्ण;
/*
 * raid5 cache state machine
 *
 * With the RAID cache, each stripe works in two phases:
 *	- caching phase
 *	- writing-out phase
 *
 * These two phases are controlled by bit STRIPE_R5C_CACHING:
 *   अगर STRIPE_R5C_CACHING == 0, the stripe is in writing-out phase
 *   अगर STRIPE_R5C_CACHING == 1, the stripe is in caching phase
 *
 * When there is no journal, or the journal is in ग_लिखो-through mode,
 * the stripe is always in writing-out phase.
 *
 * For ग_लिखो-back journal, the stripe is sent to caching phase on ग_लिखो
 * (r5c_try_caching_ग_लिखो). r5c_make_stripe_ग_लिखो_out() kicks off
 * the ग_लिखो-out phase by clearing STRIPE_R5C_CACHING.
 *
 * Stripes in caching phase करो not ग_लिखो the raid disks. Instead, all
 * ग_लिखोs are committed from the log device. Thereक्रमe, a stripe in
 * caching phase handles ग_लिखोs as:
 *	- ग_लिखो to log device
 *	- वापस IO
 *
 * Stripes in writing-out phase handle ग_लिखोs as:
 *	- calculate parity
 *	- ग_लिखो pending data and parity to journal
 *	- ग_लिखो data and parity to raid disks
 *	- वापस IO क्रम pending ग_लिखोs
 */

काष्ठा r5l_log अणु
	काष्ठा md_rdev *rdev;

	u32 uuid_checksum;

	sector_t device_size;		/* log device size, round to
					 * BLOCK_SECTORS */
	sector_t max_मुक्त_space;	/* reclaim run अगर मुक्त space is at
					 * this size */

	sector_t last_checkpoपूर्णांक;	/* log tail. where recovery scan
					 * starts from */
	u64 last_cp_seq;		/* log tail sequence */

	sector_t log_start;		/* log head. where new data appends */
	u64 seq;			/* log head sequence */

	sector_t next_checkpoपूर्णांक;

	काष्ठा mutex io_mutex;
	काष्ठा r5l_io_unit *current_io;	/* current io_unit accepting new data */

	spinlock_t io_list_lock;
	काष्ठा list_head running_ios;	/* io_units which are still running,
					 * and have not yet been completely
					 * written to the log */
	काष्ठा list_head io_end_ios;	/* io_units which have been completely
					 * written to the log but not yet written
					 * to the RAID */
	काष्ठा list_head flushing_ios;	/* io_units which are रुकोing क्रम log
					 * cache flush */
	काष्ठा list_head finished_ios;	/* io_units which settle करोwn in log disk */
	काष्ठा bio flush_bio;

	काष्ठा list_head no_mem_stripes;   /* pending stripes, -ENOMEM */

	काष्ठा kmem_cache *io_kc;
	mempool_t io_pool;
	काष्ठा bio_set bs;
	mempool_t meta_pool;

	काष्ठा md_thपढ़ो *reclaim_thपढ़ो;
	अचिन्हित दीर्घ reclaim_target;	/* number of space that need to be
					 * reclaimed.  अगर it's 0, reclaim spaces
					 * used by io_units which are in
					 * IO_UNIT_STRIPE_END state (eg, reclaim
					 * करोnes't रुको क्रम specअगरic io_unit
					 * चयनing to IO_UNIT_STRIPE_END
					 * state) */
	रुको_queue_head_t iounit_रुको;

	काष्ठा list_head no_space_stripes; /* pending stripes, log has no space */
	spinlock_t no_space_stripes_lock;

	bool need_cache_flush;

	/* क्रम r5c_cache */
	क्रमागत r5c_journal_mode r5c_journal_mode;

	/* all stripes in r5cache, in the order of seq at sh->log_start */
	काष्ठा list_head stripe_in_journal_list;

	spinlock_t stripe_in_journal_lock;
	atomic_t stripe_in_journal_count;

	/* to submit async io_units, to fulfill ordering of flush */
	काष्ठा work_काष्ठा deferred_io_work;
	/* to disable ग_लिखो back during in degraded mode */
	काष्ठा work_काष्ठा disable_ग_लिखोback_work;

	/* to क्रम chunk_aligned_पढ़ो in ग_लिखोback mode, details below */
	spinlock_t tree_lock;
	काष्ठा radix_tree_root big_stripe_tree;
पूर्ण;

/*
 * Enable chunk_aligned_पढ़ो() with ग_लिखो back cache.
 *
 * Each chunk may contain more than one stripe (क्रम example, a 256kB
 * chunk contains 64 4kB-page, so this chunk contain 64 stripes). For
 * chunk_aligned_पढ़ो, these stripes are grouped पूर्णांकo one "big_stripe".
 * For each big_stripe, we count how many stripes of this big_stripe
 * are in the ग_लिखो back cache. These data are tracked in a radix tree
 * (big_stripe_tree). We use radix_tree item poपूर्णांकer as the counter.
 * r5c_tree_index() is used to calculate keys क्रम the radix tree.
 *
 * chunk_aligned_पढ़ो() calls r5c_big_stripe_cached() to look up
 * big_stripe of each chunk in the tree. If this big_stripe is in the
 * tree, chunk_aligned_पढ़ो() पातs. This look up is रक्षित by
 * rcu_पढ़ो_lock().
 *
 * It is necessary to remember whether a stripe is counted in
 * big_stripe_tree. Instead of adding new flag, we reuses existing flags:
 * STRIPE_R5C_PARTIAL_STRIPE and STRIPE_R5C_FULL_STRIPE. If either of these
 * two flags are set, the stripe is counted in big_stripe_tree. This
 * requires moving set_bit(STRIPE_R5C_PARTIAL_STRIPE) to
 * r5c_try_caching_ग_लिखो(); and moving clear_bit of
 * STRIPE_R5C_PARTIAL_STRIPE and STRIPE_R5C_FULL_STRIPE to
 * r5c_finish_stripe_ग_लिखो_out().
 */

/*
 * radix tree requests lowest 2 bits of data poपूर्णांकer to be 2b'00.
 * So it is necessary to left shअगरt the counter by 2 bits beक्रमe using it
 * as data poपूर्णांकer of the tree.
 */
#घोषणा R5C_RADIX_COUNT_SHIFT 2

/*
 * calculate key क्रम big_stripe_tree
 *
 * sect: align_bi->bi_iter.bi_sector or sh->sector
 */
अटल अंतरभूत sector_t r5c_tree_index(काष्ठा r5conf *conf,
				      sector_t sect)
अणु
	sector_भाग(sect, conf->chunk_sectors);
	वापस sect;
पूर्ण

/*
 * an IO range starts from a meta data block and end at the next meta data
 * block. The io unit's the meta data block tracks data/parity followed it. io
 * unit is written to log disk with normal ग_लिखो, as we always flush log disk
 * first and then start move data to raid disks, there is no requirement to
 * ग_लिखो io unit with FLUSH/FUA
 */
काष्ठा r5l_io_unit अणु
	काष्ठा r5l_log *log;

	काष्ठा page *meta_page;	/* store meta block */
	पूर्णांक meta_offset;	/* current offset in meta_page */

	काष्ठा bio *current_bio;/* current_bio accepting new data */

	atomic_t pending_stripe;/* how many stripes not flushed to raid */
	u64 seq;		/* seq number of the metablock */
	sector_t log_start;	/* where the io_unit starts */
	sector_t log_end;	/* where the io_unit ends */
	काष्ठा list_head log_sibling; /* log->running_ios */
	काष्ठा list_head stripe_list; /* stripes added to the io_unit */

	पूर्णांक state;
	bool need_split_bio;
	काष्ठा bio *split_bio;

	अचिन्हित पूर्णांक has_flush:1;		/* include flush request */
	अचिन्हित पूर्णांक has_fua:1;			/* include fua request */
	अचिन्हित पूर्णांक has_null_flush:1;		/* include null flush request */
	अचिन्हित पूर्णांक has_flush_payload:1;	/* include flush payload  */
	/*
	 * io isn't sent yet, flush/fua request can only be submitted till it's
	 * the first IO in running_ios list
	 */
	अचिन्हित पूर्णांक io_deferred:1;

	काष्ठा bio_list flush_barriers;   /* size == 0 flush bios */
पूर्ण;

/* r5l_io_unit state */
क्रमागत r5l_io_unit_state अणु
	IO_UNIT_RUNNING = 0,	/* accepting new IO */
	IO_UNIT_IO_START = 1,	/* io_unit bio start writing to log,
				 * करोn't accepting new bio */
	IO_UNIT_IO_END = 2,	/* io_unit bio finish writing to log */
	IO_UNIT_STRIPE_END = 3,	/* stripes data finished writing to raid */
पूर्ण;

bool r5c_is_ग_लिखोback(काष्ठा r5l_log *log)
अणु
	वापस (log != शून्य &&
		log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_BACK);
पूर्ण

अटल sector_t r5l_ring_add(काष्ठा r5l_log *log, sector_t start, sector_t inc)
अणु
	start += inc;
	अगर (start >= log->device_size)
		start = start - log->device_size;
	वापस start;
पूर्ण

अटल sector_t r5l_ring_distance(काष्ठा r5l_log *log, sector_t start,
				  sector_t end)
अणु
	अगर (end >= start)
		वापस end - start;
	अन्यथा
		वापस end + log->device_size - start;
पूर्ण

अटल bool r5l_has_मुक्त_space(काष्ठा r5l_log *log, sector_t size)
अणु
	sector_t used_size;

	used_size = r5l_ring_distance(log, log->last_checkpoपूर्णांक,
					log->log_start);

	वापस log->device_size > used_size + size;
पूर्ण

अटल व्योम __r5l_set_io_unit_state(काष्ठा r5l_io_unit *io,
				    क्रमागत r5l_io_unit_state state)
अणु
	अगर (WARN_ON(io->state >= state))
		वापस;
	io->state = state;
पूर्ण

अटल व्योम
r5c_वापस_dev_pending_ग_लिखोs(काष्ठा r5conf *conf, काष्ठा r5dev *dev)
अणु
	काष्ठा bio *wbi, *wbi2;

	wbi = dev->written;
	dev->written = शून्य;
	जबतक (wbi && wbi->bi_iter.bi_sector <
	       dev->sector + RAID5_STRIPE_SECTORS(conf)) अणु
		wbi2 = r5_next_bio(conf, wbi, dev->sector);
		md_ग_लिखो_end(conf->mddev);
		bio_endio(wbi);
		wbi = wbi2;
	पूर्ण
पूर्ण

व्योम r5c_handle_cached_data_endio(काष्ठा r5conf *conf,
				  काष्ठा stripe_head *sh, पूर्णांक disks)
अणु
	पूर्णांक i;

	क्रम (i = sh->disks; i--; ) अणु
		अगर (sh->dev[i].written) अणु
			set_bit(R5_UPTODATE, &sh->dev[i].flags);
			r5c_वापस_dev_pending_ग_लिखोs(conf, &sh->dev[i]);
			md_biपंचांगap_endग_लिखो(conf->mddev->biपंचांगap, sh->sector,
					   RAID5_STRIPE_SECTORS(conf),
					   !test_bit(STRIPE_DEGRADED, &sh->state),
					   0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम r5l_wake_reclaim(काष्ठा r5l_log *log, sector_t space);

/* Check whether we should flush some stripes to मुक्त up stripe cache */
व्योम r5c_check_stripe_cache_usage(काष्ठा r5conf *conf)
अणु
	पूर्णांक total_cached;

	अगर (!r5c_is_ग_लिखोback(conf->log))
		वापस;

	total_cached = atomic_पढ़ो(&conf->r5c_cached_partial_stripes) +
		atomic_पढ़ो(&conf->r5c_cached_full_stripes);

	/*
	 * The following condition is true क्रम either of the following:
	 *   - stripe cache pressure high:
	 *          total_cached > 3/4 min_nr_stripes ||
	 *          empty_inactive_list_nr > 0
	 *   - stripe cache pressure moderate:
	 *          total_cached > 1/2 min_nr_stripes
	 */
	अगर (total_cached > conf->min_nr_stripes * 1 / 2 ||
	    atomic_पढ़ो(&conf->empty_inactive_list_nr) > 0)
		r5l_wake_reclaim(conf->log, 0);
पूर्ण

/*
 * flush cache when there are R5C_FULL_STRIPE_FLUSH_BATCH or more full
 * stripes in the cache
 */
व्योम r5c_check_cached_full_stripe(काष्ठा r5conf *conf)
अणु
	अगर (!r5c_is_ग_लिखोback(conf->log))
		वापस;

	/*
	 * wake up reclaim क्रम R5C_FULL_STRIPE_FLUSH_BATCH cached stripes
	 * or a full stripe (chunk size / 4k stripes).
	 */
	अगर (atomic_पढ़ो(&conf->r5c_cached_full_stripes) >=
	    min(R5C_FULL_STRIPE_FLUSH_BATCH(conf),
		conf->chunk_sectors >> RAID5_STRIPE_SHIFT(conf)))
		r5l_wake_reclaim(conf->log, 0);
पूर्ण

/*
 * Total log space (in sectors) needed to flush all data in cache
 *
 * To aव्योम deadlock due to log space, it is necessary to reserve log
 * space to flush critical stripes (stripes that occupying log space near
 * last_checkpoपूर्णांक). This function helps check how much log space is
 * required to flush all cached stripes.
 *
 * To reduce log space requirements, two mechanisms are used to give cache
 * flush higher priorities:
 *    1. In handle_stripe_dirtying() and schedule_reस्थिरruction(),
 *       stripes ALREADY in journal can be flushed w/o pending ग_लिखोs;
 *    2. In r5l_ग_लिखो_stripe() and r5c_cache_data(), stripes NOT in journal
 *       can be delayed (r5l_add_no_space_stripe).
 *
 * In cache flush, the stripe goes through 1 and then 2. For a stripe that
 * alपढ़ोy passed 1, flushing it requires at most (conf->max_degraded + 1)
 * pages of journal space. For stripes that has not passed 1, flushing it
 * requires (conf->raid_disks + 1) pages of journal space. There are at
 * most (conf->group_cnt + 1) stripe that passed 1. So total journal space
 * required to flush all cached stripes (in pages) is:
 *
 *     (stripe_in_journal_count - group_cnt - 1) * (max_degraded + 1) +
 *     (group_cnt + 1) * (raid_disks + 1)
 * or
 *     (stripe_in_journal_count) * (max_degraded + 1) +
 *     (group_cnt + 1) * (raid_disks - max_degraded)
 */
अटल sector_t r5c_log_required_to_flush_cache(काष्ठा r5conf *conf)
अणु
	काष्ठा r5l_log *log = conf->log;

	अगर (!r5c_is_ग_लिखोback(log))
		वापस 0;

	वापस BLOCK_SECTORS *
		((conf->max_degraded + 1) * atomic_पढ़ो(&log->stripe_in_journal_count) +
		 (conf->raid_disks - conf->max_degraded) * (conf->group_cnt + 1));
पूर्ण

/*
 * evaluate log space usage and update R5C_LOG_TIGHT and R5C_LOG_CRITICAL
 *
 * R5C_LOG_TIGHT is set when मुक्त space on the log device is less than 3x of
 * reclaim_required_space. R5C_LOG_CRITICAL is set when मुक्त space on the log
 * device is less than 2x of reclaim_required_space.
 */
अटल अंतरभूत व्योम r5c_update_log_state(काष्ठा r5l_log *log)
अणु
	काष्ठा r5conf *conf = log->rdev->mddev->निजी;
	sector_t मुक्त_space;
	sector_t reclaim_space;
	bool wake_reclaim = false;

	अगर (!r5c_is_ग_लिखोback(log))
		वापस;

	मुक्त_space = r5l_ring_distance(log, log->log_start,
				       log->last_checkpoपूर्णांक);
	reclaim_space = r5c_log_required_to_flush_cache(conf);
	अगर (मुक्त_space < 2 * reclaim_space)
		set_bit(R5C_LOG_CRITICAL, &conf->cache_state);
	अन्यथा अणु
		अगर (test_bit(R5C_LOG_CRITICAL, &conf->cache_state))
			wake_reclaim = true;
		clear_bit(R5C_LOG_CRITICAL, &conf->cache_state);
	पूर्ण
	अगर (मुक्त_space < 3 * reclaim_space)
		set_bit(R5C_LOG_TIGHT, &conf->cache_state);
	अन्यथा
		clear_bit(R5C_LOG_TIGHT, &conf->cache_state);

	अगर (wake_reclaim)
		r5l_wake_reclaim(log, 0);
पूर्ण

/*
 * Put the stripe पूर्णांकo writing-out phase by clearing STRIPE_R5C_CACHING.
 * This function should only be called in ग_लिखो-back mode.
 */
व्योम r5c_make_stripe_ग_लिखो_out(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	काष्ठा r5l_log *log = conf->log;

	BUG_ON(!r5c_is_ग_लिखोback(log));

	WARN_ON(!test_bit(STRIPE_R5C_CACHING, &sh->state));
	clear_bit(STRIPE_R5C_CACHING, &sh->state);

	अगर (!test_and_set_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
		atomic_inc(&conf->preपढ़ो_active_stripes);
पूर्ण

अटल व्योम r5c_handle_data_cached(काष्ठा stripe_head *sh)
अणु
	पूर्णांक i;

	क्रम (i = sh->disks; i--; )
		अगर (test_and_clear_bit(R5_Wantग_लिखो, &sh->dev[i].flags)) अणु
			set_bit(R5_InJournal, &sh->dev[i].flags);
			clear_bit(R5_LOCKED, &sh->dev[i].flags);
		पूर्ण
	clear_bit(STRIPE_LOG_TRAPPED, &sh->state);
पूर्ण

/*
 * this journal ग_लिखो must contain full parity,
 * it may also contain some data pages
 */
अटल व्योम r5c_handle_parity_cached(काष्ठा stripe_head *sh)
अणु
	पूर्णांक i;

	क्रम (i = sh->disks; i--; )
		अगर (test_bit(R5_InJournal, &sh->dev[i].flags))
			set_bit(R5_Wantग_लिखो, &sh->dev[i].flags);
पूर्ण

/*
 * Setting proper flags after writing (or flushing) data and/or parity to the
 * log device. This is called from r5l_log_endio() or r5l_log_flush_endio().
 */
अटल व्योम r5c_finish_cache_stripe(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5l_log *log = sh->raid_conf->log;

	अगर (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH) अणु
		BUG_ON(test_bit(STRIPE_R5C_CACHING, &sh->state));
		/*
		 * Set R5_InJournal क्रम parity dev[pd_idx]. This means
		 * all data AND parity in the journal. For RAID 6, it is
		 * NOT necessary to set the flag क्रम dev[qd_idx], as the
		 * two parities are written out together.
		 */
		set_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags);
	पूर्ण अन्यथा अगर (test_bit(STRIPE_R5C_CACHING, &sh->state)) अणु
		r5c_handle_data_cached(sh);
	पूर्ण अन्यथा अणु
		r5c_handle_parity_cached(sh);
		set_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags);
	पूर्ण
पूर्ण

अटल व्योम r5l_io_run_stripes(काष्ठा r5l_io_unit *io)
अणु
	काष्ठा stripe_head *sh, *next;

	list_क्रम_each_entry_safe(sh, next, &io->stripe_list, log_list) अणु
		list_del_init(&sh->log_list);

		r5c_finish_cache_stripe(sh);

		set_bit(STRIPE_HANDLE, &sh->state);
		raid5_release_stripe(sh);
	पूर्ण
पूर्ण

अटल व्योम r5l_log_run_stripes(काष्ठा r5l_log *log)
अणु
	काष्ठा r5l_io_unit *io, *next;

	lockdep_निश्चित_held(&log->io_list_lock);

	list_क्रम_each_entry_safe(io, next, &log->running_ios, log_sibling) अणु
		/* करोn't change list order */
		अगर (io->state < IO_UNIT_IO_END)
			अवरोध;

		list_move_tail(&io->log_sibling, &log->finished_ios);
		r5l_io_run_stripes(io);
	पूर्ण
पूर्ण

अटल व्योम r5l_move_to_end_ios(काष्ठा r5l_log *log)
अणु
	काष्ठा r5l_io_unit *io, *next;

	lockdep_निश्चित_held(&log->io_list_lock);

	list_क्रम_each_entry_safe(io, next, &log->running_ios, log_sibling) अणु
		/* करोn't change list order */
		अगर (io->state < IO_UNIT_IO_END)
			अवरोध;
		list_move_tail(&io->log_sibling, &log->io_end_ios);
	पूर्ण
पूर्ण

अटल व्योम __r5l_stripe_ग_लिखो_finished(काष्ठा r5l_io_unit *io);
अटल व्योम r5l_log_endio(काष्ठा bio *bio)
अणु
	काष्ठा r5l_io_unit *io = bio->bi_निजी;
	काष्ठा r5l_io_unit *io_deferred;
	काष्ठा r5l_log *log = io->log;
	अचिन्हित दीर्घ flags;
	bool has_null_flush;
	bool has_flush_payload;

	अगर (bio->bi_status)
		md_error(log->rdev->mddev, log->rdev);

	bio_put(bio);
	mempool_मुक्त(io->meta_page, &log->meta_pool);

	spin_lock_irqsave(&log->io_list_lock, flags);
	__r5l_set_io_unit_state(io, IO_UNIT_IO_END);

	/*
	 * अगर the io करोesn't not have null_flush or flush payload,
	 * it is not safe to access it after releasing io_list_lock.
	 * Thereक्रमe, it is necessary to check the condition with
	 * the lock held.
	 */
	has_null_flush = io->has_null_flush;
	has_flush_payload = io->has_flush_payload;

	अगर (log->need_cache_flush && !list_empty(&io->stripe_list))
		r5l_move_to_end_ios(log);
	अन्यथा
		r5l_log_run_stripes(log);
	अगर (!list_empty(&log->running_ios)) अणु
		/*
		 * FLUSH/FUA io_unit is deferred because of ordering, now we
		 * can dispatch it
		 */
		io_deferred = list_first_entry(&log->running_ios,
					       काष्ठा r5l_io_unit, log_sibling);
		अगर (io_deferred->io_deferred)
			schedule_work(&log->deferred_io_work);
	पूर्ण

	spin_unlock_irqrestore(&log->io_list_lock, flags);

	अगर (log->need_cache_flush)
		md_wakeup_thपढ़ो(log->rdev->mddev->thपढ़ो);

	/* finish flush only io_unit and PAYLOAD_FLUSH only io_unit */
	अगर (has_null_flush) अणु
		काष्ठा bio *bi;

		WARN_ON(bio_list_empty(&io->flush_barriers));
		जबतक ((bi = bio_list_pop(&io->flush_barriers)) != शून्य) अणु
			bio_endio(bi);
			अगर (atomic_dec_and_test(&io->pending_stripe)) अणु
				__r5l_stripe_ग_लिखो_finished(io);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	/* decrease pending_stripe क्रम flush payload */
	अगर (has_flush_payload)
		अगर (atomic_dec_and_test(&io->pending_stripe))
			__r5l_stripe_ग_लिखो_finished(io);
पूर्ण

अटल व्योम r5l_करो_submit_io(काष्ठा r5l_log *log, काष्ठा r5l_io_unit *io)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&log->io_list_lock, flags);
	__r5l_set_io_unit_state(io, IO_UNIT_IO_START);
	spin_unlock_irqrestore(&log->io_list_lock, flags);

	/*
	 * In हाल of journal device failures, submit_bio will get error
	 * and calls endio, then active stripes will जारी ग_लिखो
	 * process. Thereक्रमe, it is not necessary to check Faulty bit
	 * of journal device here.
	 *
	 * We can't check split_bio after current_bio is submitted. If
	 * io->split_bio is null, after current_bio is submitted, current_bio
	 * might alपढ़ोy be completed and the io_unit is मुक्तd. We submit
	 * split_bio first to aव्योम the issue.
	 */
	अगर (io->split_bio) अणु
		अगर (io->has_flush)
			io->split_bio->bi_opf |= REQ_PREFLUSH;
		अगर (io->has_fua)
			io->split_bio->bi_opf |= REQ_FUA;
		submit_bio(io->split_bio);
	पूर्ण

	अगर (io->has_flush)
		io->current_bio->bi_opf |= REQ_PREFLUSH;
	अगर (io->has_fua)
		io->current_bio->bi_opf |= REQ_FUA;
	submit_bio(io->current_bio);
पूर्ण

/* deferred io_unit will be dispatched here */
अटल व्योम r5l_submit_io_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r5l_log *log = container_of(work, काष्ठा r5l_log,
					   deferred_io_work);
	काष्ठा r5l_io_unit *io = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&log->io_list_lock, flags);
	अगर (!list_empty(&log->running_ios)) अणु
		io = list_first_entry(&log->running_ios, काष्ठा r5l_io_unit,
				      log_sibling);
		अगर (!io->io_deferred)
			io = शून्य;
		अन्यथा
			io->io_deferred = 0;
	पूर्ण
	spin_unlock_irqrestore(&log->io_list_lock, flags);
	अगर (io)
		r5l_करो_submit_io(log, io);
पूर्ण

अटल व्योम r5c_disable_ग_लिखोback_async(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा r5l_log *log = container_of(work, काष्ठा r5l_log,
					   disable_ग_लिखोback_work);
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक locked = 0;

	अगर (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH)
		वापस;
	pr_info("md/raid:%s: Disabling writeback cache for degraded array.\n",
		mdname(mddev));

	/* रुको superblock change beक्रमe suspend */
	रुको_event(mddev->sb_रुको,
		   conf->log == शून्य ||
		   (!test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags) &&
		    (locked = mddev_trylock(mddev))));
	अगर (locked) अणु
		mddev_suspend(mddev);
		log->r5c_journal_mode = R5C_JOURNAL_MODE_WRITE_THROUGH;
		mddev_resume(mddev);
		mddev_unlock(mddev);
	पूर्ण
पूर्ण

अटल व्योम r5l_submit_current_io(काष्ठा r5l_log *log)
अणु
	काष्ठा r5l_io_unit *io = log->current_io;
	काष्ठा r5l_meta_block *block;
	अचिन्हित दीर्घ flags;
	u32 crc;
	bool करो_submit = true;

	अगर (!io)
		वापस;

	block = page_address(io->meta_page);
	block->meta_size = cpu_to_le32(io->meta_offset);
	crc = crc32c_le(log->uuid_checksum, block, PAGE_SIZE);
	block->checksum = cpu_to_le32(crc);

	log->current_io = शून्य;
	spin_lock_irqsave(&log->io_list_lock, flags);
	अगर (io->has_flush || io->has_fua) अणु
		अगर (io != list_first_entry(&log->running_ios,
					   काष्ठा r5l_io_unit, log_sibling)) अणु
			io->io_deferred = 1;
			करो_submit = false;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&log->io_list_lock, flags);
	अगर (करो_submit)
		r5l_करो_submit_io(log, io);
पूर्ण

अटल काष्ठा bio *r5l_bio_alloc(काष्ठा r5l_log *log)
अणु
	काष्ठा bio *bio = bio_alloc_bioset(GFP_NOIO, BIO_MAX_VECS, &log->bs);

	bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
	bio_set_dev(bio, log->rdev->bdev);
	bio->bi_iter.bi_sector = log->rdev->data_offset + log->log_start;

	वापस bio;
पूर्ण

अटल व्योम r5_reserve_log_entry(काष्ठा r5l_log *log, काष्ठा r5l_io_unit *io)
अणु
	log->log_start = r5l_ring_add(log, log->log_start, BLOCK_SECTORS);

	r5c_update_log_state(log);
	/*
	 * If we filled up the log device start from the beginning again,
	 * which will require a new bio.
	 *
	 * Note: क्रम this to work properly the log size needs to me a multiple
	 * of BLOCK_SECTORS.
	 */
	अगर (log->log_start == 0)
		io->need_split_bio = true;

	io->log_end = log->log_start;
पूर्ण

अटल काष्ठा r5l_io_unit *r5l_new_meta(काष्ठा r5l_log *log)
अणु
	काष्ठा r5l_io_unit *io;
	काष्ठा r5l_meta_block *block;

	io = mempool_alloc(&log->io_pool, GFP_ATOMIC);
	अगर (!io)
		वापस शून्य;
	स_रखो(io, 0, माप(*io));

	io->log = log;
	INIT_LIST_HEAD(&io->log_sibling);
	INIT_LIST_HEAD(&io->stripe_list);
	bio_list_init(&io->flush_barriers);
	io->state = IO_UNIT_RUNNING;

	io->meta_page = mempool_alloc(&log->meta_pool, GFP_NOIO);
	block = page_address(io->meta_page);
	clear_page(block);
	block->magic = cpu_to_le32(R5LOG_MAGIC);
	block->version = R5LOG_VERSION;
	block->seq = cpu_to_le64(log->seq);
	block->position = cpu_to_le64(log->log_start);

	io->log_start = log->log_start;
	io->meta_offset = माप(काष्ठा r5l_meta_block);
	io->seq = log->seq++;

	io->current_bio = r5l_bio_alloc(log);
	io->current_bio->bi_end_io = r5l_log_endio;
	io->current_bio->bi_निजी = io;
	bio_add_page(io->current_bio, io->meta_page, PAGE_SIZE, 0);

	r5_reserve_log_entry(log, io);

	spin_lock_irq(&log->io_list_lock);
	list_add_tail(&io->log_sibling, &log->running_ios);
	spin_unlock_irq(&log->io_list_lock);

	वापस io;
पूर्ण

अटल पूर्णांक r5l_get_meta(काष्ठा r5l_log *log, अचिन्हित पूर्णांक payload_size)
अणु
	अगर (log->current_io &&
	    log->current_io->meta_offset + payload_size > PAGE_SIZE)
		r5l_submit_current_io(log);

	अगर (!log->current_io) अणु
		log->current_io = r5l_new_meta(log);
		अगर (!log->current_io)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम r5l_append_payload_meta(काष्ठा r5l_log *log, u16 type,
				    sector_t location,
				    u32 checksum1, u32 checksum2,
				    bool checksum2_valid)
अणु
	काष्ठा r5l_io_unit *io = log->current_io;
	काष्ठा r5l_payload_data_parity *payload;

	payload = page_address(io->meta_page) + io->meta_offset;
	payload->header.type = cpu_to_le16(type);
	payload->header.flags = cpu_to_le16(0);
	payload->size = cpu_to_le32((1 + !!checksum2_valid) <<
				    (PAGE_SHIFT - 9));
	payload->location = cpu_to_le64(location);
	payload->checksum[0] = cpu_to_le32(checksum1);
	अगर (checksum2_valid)
		payload->checksum[1] = cpu_to_le32(checksum2);

	io->meta_offset += माप(काष्ठा r5l_payload_data_parity) +
		माप(__le32) * (1 + !!checksum2_valid);
पूर्ण

अटल व्योम r5l_append_payload_page(काष्ठा r5l_log *log, काष्ठा page *page)
अणु
	काष्ठा r5l_io_unit *io = log->current_io;

	अगर (io->need_split_bio) अणु
		BUG_ON(io->split_bio);
		io->split_bio = io->current_bio;
		io->current_bio = r5l_bio_alloc(log);
		bio_chain(io->current_bio, io->split_bio);
		io->need_split_bio = false;
	पूर्ण

	अगर (!bio_add_page(io->current_bio, page, PAGE_SIZE, 0))
		BUG();

	r5_reserve_log_entry(log, io);
पूर्ण

अटल व्योम r5l_append_flush_payload(काष्ठा r5l_log *log, sector_t sect)
अणु
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा r5l_io_unit *io;
	काष्ठा r5l_payload_flush *payload;
	पूर्णांक meta_size;

	/*
	 * payload_flush requires extra ग_लिखोs to the journal.
	 * To aव्योम handling the extra IO in quiesce, just skip
	 * flush_payload
	 */
	अगर (conf->quiesce)
		वापस;

	mutex_lock(&log->io_mutex);
	meta_size = माप(काष्ठा r5l_payload_flush) + माप(__le64);

	अगर (r5l_get_meta(log, meta_size)) अणु
		mutex_unlock(&log->io_mutex);
		वापस;
	पूर्ण

	/* current implementation is one stripe per flush payload */
	io = log->current_io;
	payload = page_address(io->meta_page) + io->meta_offset;
	payload->header.type = cpu_to_le16(R5LOG_PAYLOAD_FLUSH);
	payload->header.flags = cpu_to_le16(0);
	payload->size = cpu_to_le32(माप(__le64));
	payload->flush_stripes[0] = cpu_to_le64(sect);
	io->meta_offset += meta_size;
	/* multiple flush payloads count as one pending_stripe */
	अगर (!io->has_flush_payload) अणु
		io->has_flush_payload = 1;
		atomic_inc(&io->pending_stripe);
	पूर्ण
	mutex_unlock(&log->io_mutex);
पूर्ण

अटल पूर्णांक r5l_log_stripe(काष्ठा r5l_log *log, काष्ठा stripe_head *sh,
			   पूर्णांक data_pages, पूर्णांक parity_pages)
अणु
	पूर्णांक i;
	पूर्णांक meta_size;
	पूर्णांक ret;
	काष्ठा r5l_io_unit *io;

	meta_size =
		((माप(काष्ठा r5l_payload_data_parity) + माप(__le32))
		 * data_pages) +
		माप(काष्ठा r5l_payload_data_parity) +
		माप(__le32) * parity_pages;

	ret = r5l_get_meta(log, meta_size);
	अगर (ret)
		वापस ret;

	io = log->current_io;

	अगर (test_and_clear_bit(STRIPE_R5C_PREFLUSH, &sh->state))
		io->has_flush = 1;

	क्रम (i = 0; i < sh->disks; i++) अणु
		अगर (!test_bit(R5_Wantग_लिखो, &sh->dev[i].flags) ||
		    test_bit(R5_InJournal, &sh->dev[i].flags))
			जारी;
		अगर (i == sh->pd_idx || i == sh->qd_idx)
			जारी;
		अगर (test_bit(R5_WantFUA, &sh->dev[i].flags) &&
		    log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_BACK) अणु
			io->has_fua = 1;
			/*
			 * we need to flush journal to make sure recovery can
			 * reach the data with fua flag
			 */
			io->has_flush = 1;
		पूर्ण
		r5l_append_payload_meta(log, R5LOG_PAYLOAD_DATA,
					raid5_compute_blocknr(sh, i, 0),
					sh->dev[i].log_checksum, 0, false);
		r5l_append_payload_page(log, sh->dev[i].page);
	पूर्ण

	अगर (parity_pages == 2) अणु
		r5l_append_payload_meta(log, R5LOG_PAYLOAD_PARITY,
					sh->sector, sh->dev[sh->pd_idx].log_checksum,
					sh->dev[sh->qd_idx].log_checksum, true);
		r5l_append_payload_page(log, sh->dev[sh->pd_idx].page);
		r5l_append_payload_page(log, sh->dev[sh->qd_idx].page);
	पूर्ण अन्यथा अगर (parity_pages == 1) अणु
		r5l_append_payload_meta(log, R5LOG_PAYLOAD_PARITY,
					sh->sector, sh->dev[sh->pd_idx].log_checksum,
					0, false);
		r5l_append_payload_page(log, sh->dev[sh->pd_idx].page);
	पूर्ण अन्यथा  /* Just writing data, not parity, in caching phase */
		BUG_ON(parity_pages != 0);

	list_add_tail(&sh->log_list, &io->stripe_list);
	atomic_inc(&io->pending_stripe);
	sh->log_io = io;

	अगर (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH)
		वापस 0;

	अगर (sh->log_start == MaxSector) अणु
		BUG_ON(!list_empty(&sh->r5c));
		sh->log_start = io->log_start;
		spin_lock_irq(&log->stripe_in_journal_lock);
		list_add_tail(&sh->r5c,
			      &log->stripe_in_journal_list);
		spin_unlock_irq(&log->stripe_in_journal_lock);
		atomic_inc(&log->stripe_in_journal_count);
	पूर्ण
	वापस 0;
पूर्ण

/* add stripe to no_space_stripes, and then wake up reclaim */
अटल अंतरभूत व्योम r5l_add_no_space_stripe(काष्ठा r5l_log *log,
					   काष्ठा stripe_head *sh)
अणु
	spin_lock(&log->no_space_stripes_lock);
	list_add_tail(&sh->log_list, &log->no_space_stripes);
	spin_unlock(&log->no_space_stripes_lock);
पूर्ण

/*
 * running in raid5d, where reclaim could रुको क्रम raid5d too (when it flushes
 * data from log to raid disks), so we shouldn't रुको क्रम reclaim here
 */
पूर्णांक r5l_ग_लिखो_stripe(काष्ठा r5l_log *log, काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक ग_लिखो_disks = 0;
	पूर्णांक data_pages, parity_pages;
	पूर्णांक reserve;
	पूर्णांक i;
	पूर्णांक ret = 0;
	bool wake_reclaim = false;

	अगर (!log)
		वापस -EAGAIN;
	/* Don't support stripe batch */
	अगर (sh->log_io || !test_bit(R5_Wantग_लिखो, &sh->dev[sh->pd_idx].flags) ||
	    test_bit(STRIPE_SYNCING, &sh->state)) अणु
		/* the stripe is written to log, we start writing it to raid */
		clear_bit(STRIPE_LOG_TRAPPED, &sh->state);
		वापस -EAGAIN;
	पूर्ण

	WARN_ON(test_bit(STRIPE_R5C_CACHING, &sh->state));

	क्रम (i = 0; i < sh->disks; i++) अणु
		व्योम *addr;

		अगर (!test_bit(R5_Wantग_लिखो, &sh->dev[i].flags) ||
		    test_bit(R5_InJournal, &sh->dev[i].flags))
			जारी;

		ग_लिखो_disks++;
		/* checksum is alपढ़ोy calculated in last run */
		अगर (test_bit(STRIPE_LOG_TRAPPED, &sh->state))
			जारी;
		addr = kmap_atomic(sh->dev[i].page);
		sh->dev[i].log_checksum = crc32c_le(log->uuid_checksum,
						    addr, PAGE_SIZE);
		kunmap_atomic(addr);
	पूर्ण
	parity_pages = 1 + !!(sh->qd_idx >= 0);
	data_pages = ग_लिखो_disks - parity_pages;

	set_bit(STRIPE_LOG_TRAPPED, &sh->state);
	/*
	 * The stripe must enter state machine again to finish the ग_लिखो, so
	 * करोn't delay.
	 */
	clear_bit(STRIPE_DELAYED, &sh->state);
	atomic_inc(&sh->count);

	mutex_lock(&log->io_mutex);
	/* meta + data */
	reserve = (1 + ग_लिखो_disks) << (PAGE_SHIFT - 9);

	अगर (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH) अणु
		अगर (!r5l_has_मुक्त_space(log, reserve)) अणु
			r5l_add_no_space_stripe(log, sh);
			wake_reclaim = true;
		पूर्ण अन्यथा अणु
			ret = r5l_log_stripe(log, sh, data_pages, parity_pages);
			अगर (ret) अणु
				spin_lock_irq(&log->io_list_lock);
				list_add_tail(&sh->log_list,
					      &log->no_mem_stripes);
				spin_unlock_irq(&log->io_list_lock);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु  /* R5C_JOURNAL_MODE_WRITE_BACK */
		/*
		 * log space critical, करो not process stripes that are
		 * not in cache yet (sh->log_start == MaxSector).
		 */
		अगर (test_bit(R5C_LOG_CRITICAL, &conf->cache_state) &&
		    sh->log_start == MaxSector) अणु
			r5l_add_no_space_stripe(log, sh);
			wake_reclaim = true;
			reserve = 0;
		पूर्ण अन्यथा अगर (!r5l_has_मुक्त_space(log, reserve)) अणु
			अगर (sh->log_start == log->last_checkpoपूर्णांक)
				BUG();
			अन्यथा
				r5l_add_no_space_stripe(log, sh);
		पूर्ण अन्यथा अणु
			ret = r5l_log_stripe(log, sh, data_pages, parity_pages);
			अगर (ret) अणु
				spin_lock_irq(&log->io_list_lock);
				list_add_tail(&sh->log_list,
					      &log->no_mem_stripes);
				spin_unlock_irq(&log->io_list_lock);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&log->io_mutex);
	अगर (wake_reclaim)
		r5l_wake_reclaim(log, reserve);
	वापस 0;
पूर्ण

व्योम r5l_ग_लिखो_stripe_run(काष्ठा r5l_log *log)
अणु
	अगर (!log)
		वापस;
	mutex_lock(&log->io_mutex);
	r5l_submit_current_io(log);
	mutex_unlock(&log->io_mutex);
पूर्ण

पूर्णांक r5l_handle_flush_request(काष्ठा r5l_log *log, काष्ठा bio *bio)
अणु
	अगर (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH) अणु
		/*
		 * in ग_लिखो through (journal only)
		 * we flush log disk cache first, then ग_लिखो stripe data to
		 * raid disks. So अगर bio is finished, the log disk cache is
		 * flushed alपढ़ोy. The recovery guarantees we can recovery
		 * the bio from log disk, so we करोn't need to flush again
		 */
		अगर (bio->bi_iter.bi_size == 0) अणु
			bio_endio(bio);
			वापस 0;
		पूर्ण
		bio->bi_opf &= ~REQ_PREFLUSH;
	पूर्ण अन्यथा अणु
		/* ग_लिखो back (with cache) */
		अगर (bio->bi_iter.bi_size == 0) अणु
			mutex_lock(&log->io_mutex);
			r5l_get_meta(log, 0);
			bio_list_add(&log->current_io->flush_barriers, bio);
			log->current_io->has_flush = 1;
			log->current_io->has_null_flush = 1;
			atomic_inc(&log->current_io->pending_stripe);
			r5l_submit_current_io(log);
			mutex_unlock(&log->io_mutex);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EAGAIN;
पूर्ण

/* This will run after log space is reclaimed */
अटल व्योम r5l_run_no_space_stripes(काष्ठा r5l_log *log)
अणु
	काष्ठा stripe_head *sh;

	spin_lock(&log->no_space_stripes_lock);
	जबतक (!list_empty(&log->no_space_stripes)) अणु
		sh = list_first_entry(&log->no_space_stripes,
				      काष्ठा stripe_head, log_list);
		list_del_init(&sh->log_list);
		set_bit(STRIPE_HANDLE, &sh->state);
		raid5_release_stripe(sh);
	पूर्ण
	spin_unlock(&log->no_space_stripes_lock);
पूर्ण

/*
 * calculate new last_checkpoपूर्णांक
 * क्रम ग_लिखो through mode, वापसs log->next_checkpoपूर्णांक
 * क्रम ग_लिखो back, वापसs log_start of first sh in stripe_in_journal_list
 */
अटल sector_t r5c_calculate_new_cp(काष्ठा r5conf *conf)
अणु
	काष्ठा stripe_head *sh;
	काष्ठा r5l_log *log = conf->log;
	sector_t new_cp;
	अचिन्हित दीर्घ flags;

	अगर (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH)
		वापस log->next_checkpoपूर्णांक;

	spin_lock_irqsave(&log->stripe_in_journal_lock, flags);
	अगर (list_empty(&conf->log->stripe_in_journal_list)) अणु
		/* all stripes flushed */
		spin_unlock_irqrestore(&log->stripe_in_journal_lock, flags);
		वापस log->next_checkpoपूर्णांक;
	पूर्ण
	sh = list_first_entry(&conf->log->stripe_in_journal_list,
			      काष्ठा stripe_head, r5c);
	new_cp = sh->log_start;
	spin_unlock_irqrestore(&log->stripe_in_journal_lock, flags);
	वापस new_cp;
पूर्ण

अटल sector_t r5l_reclaimable_space(काष्ठा r5l_log *log)
अणु
	काष्ठा r5conf *conf = log->rdev->mddev->निजी;

	वापस r5l_ring_distance(log, log->last_checkpoपूर्णांक,
				 r5c_calculate_new_cp(conf));
पूर्ण

अटल व्योम r5l_run_no_mem_stripe(काष्ठा r5l_log *log)
अणु
	काष्ठा stripe_head *sh;

	lockdep_निश्चित_held(&log->io_list_lock);

	अगर (!list_empty(&log->no_mem_stripes)) अणु
		sh = list_first_entry(&log->no_mem_stripes,
				      काष्ठा stripe_head, log_list);
		list_del_init(&sh->log_list);
		set_bit(STRIPE_HANDLE, &sh->state);
		raid5_release_stripe(sh);
	पूर्ण
पूर्ण

अटल bool r5l_complete_finished_ios(काष्ठा r5l_log *log)
अणु
	काष्ठा r5l_io_unit *io, *next;
	bool found = false;

	lockdep_निश्चित_held(&log->io_list_lock);

	list_क्रम_each_entry_safe(io, next, &log->finished_ios, log_sibling) अणु
		/* करोn't change list order */
		अगर (io->state < IO_UNIT_STRIPE_END)
			अवरोध;

		log->next_checkpoपूर्णांक = io->log_start;

		list_del(&io->log_sibling);
		mempool_मुक्त(io, &log->io_pool);
		r5l_run_no_mem_stripe(log);

		found = true;
	पूर्ण

	वापस found;
पूर्ण

अटल व्योम __r5l_stripe_ग_लिखो_finished(काष्ठा r5l_io_unit *io)
अणु
	काष्ठा r5l_log *log = io->log;
	काष्ठा r5conf *conf = log->rdev->mddev->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&log->io_list_lock, flags);
	__r5l_set_io_unit_state(io, IO_UNIT_STRIPE_END);

	अगर (!r5l_complete_finished_ios(log)) अणु
		spin_unlock_irqrestore(&log->io_list_lock, flags);
		वापस;
	पूर्ण

	अगर (r5l_reclaimable_space(log) > log->max_मुक्त_space ||
	    test_bit(R5C_LOG_TIGHT, &conf->cache_state))
		r5l_wake_reclaim(log, 0);

	spin_unlock_irqrestore(&log->io_list_lock, flags);
	wake_up(&log->iounit_रुको);
पूर्ण

व्योम r5l_stripe_ग_लिखो_finished(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5l_io_unit *io;

	io = sh->log_io;
	sh->log_io = शून्य;

	अगर (io && atomic_dec_and_test(&io->pending_stripe))
		__r5l_stripe_ग_लिखो_finished(io);
पूर्ण

अटल व्योम r5l_log_flush_endio(काष्ठा bio *bio)
अणु
	काष्ठा r5l_log *log = container_of(bio, काष्ठा r5l_log,
		flush_bio);
	अचिन्हित दीर्घ flags;
	काष्ठा r5l_io_unit *io;

	अगर (bio->bi_status)
		md_error(log->rdev->mddev, log->rdev);

	spin_lock_irqsave(&log->io_list_lock, flags);
	list_क्रम_each_entry(io, &log->flushing_ios, log_sibling)
		r5l_io_run_stripes(io);
	list_splice_tail_init(&log->flushing_ios, &log->finished_ios);
	spin_unlock_irqrestore(&log->io_list_lock, flags);
पूर्ण

/*
 * Starting dispatch IO to raid.
 * io_unit(meta) consists of a log. There is one situation we want to aव्योम. A
 * broken meta in the middle of a log causes recovery can't find meta at the
 * head of log. If operations require meta at the head persistent in log, we
 * must make sure meta beक्रमe it persistent in log too. A हाल is:
 *
 * stripe data/parity is in log, we start ग_लिखो stripe to raid disks. stripe
 * data/parity must be persistent in log beक्रमe we करो the ग_लिखो to raid disks.
 *
 * The solution is we restrictly मुख्यtain io_unit list order. In this हाल, we
 * only ग_लिखो stripes of an io_unit to raid disks till the io_unit is the first
 * one whose data/parity is in log.
 */
व्योम r5l_flush_stripe_to_raid(काष्ठा r5l_log *log)
अणु
	bool करो_flush;

	अगर (!log || !log->need_cache_flush)
		वापस;

	spin_lock_irq(&log->io_list_lock);
	/* flush bio is running */
	अगर (!list_empty(&log->flushing_ios)) अणु
		spin_unlock_irq(&log->io_list_lock);
		वापस;
	पूर्ण
	list_splice_tail_init(&log->io_end_ios, &log->flushing_ios);
	करो_flush = !list_empty(&log->flushing_ios);
	spin_unlock_irq(&log->io_list_lock);

	अगर (!करो_flush)
		वापस;
	bio_reset(&log->flush_bio);
	bio_set_dev(&log->flush_bio, log->rdev->bdev);
	log->flush_bio.bi_end_io = r5l_log_flush_endio;
	log->flush_bio.bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
	submit_bio(&log->flush_bio);
पूर्ण

अटल व्योम r5l_ग_लिखो_super(काष्ठा r5l_log *log, sector_t cp);
अटल व्योम r5l_ग_लिखो_super_and_discard_space(काष्ठा r5l_log *log,
	sector_t end)
अणु
	काष्ठा block_device *bdev = log->rdev->bdev;
	काष्ठा mddev *mddev;

	r5l_ग_लिखो_super(log, end);

	अगर (!blk_queue_discard(bdev_get_queue(bdev)))
		वापस;

	mddev = log->rdev->mddev;
	/*
	 * Discard could zero data, so beक्रमe discard we must make sure
	 * superblock is updated to new log tail. Updating superblock (either
	 * directly call md_update_sb() or depend on md thपढ़ो) must hold
	 * reconfig mutex. On the other hand, raid5_quiesce is called with
	 * reconfig_mutex hold. The first step of raid5_quiesce() is रुकोting
	 * क्रम all IO finish, hence रुकोting क्रम reclaim thपढ़ो, जबतक reclaim
	 * thपढ़ो is calling this function and रुकोting क्रम reconfig mutex. So
	 * there is a deadlock. We workaround this issue with a trylock.
	 * FIXME: we could miss discard अगर we can't take reconfig mutex
	 */
	set_mask_bits(&mddev->sb_flags, 0,
		BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	अगर (!mddev_trylock(mddev))
		वापस;
	md_update_sb(mddev, 1);
	mddev_unlock(mddev);

	/* discard IO error really करोesn't matter, ignore it */
	अगर (log->last_checkpoपूर्णांक < end) अणु
		blkdev_issue_discard(bdev,
				log->last_checkpoपूर्णांक + log->rdev->data_offset,
				end - log->last_checkpoपूर्णांक, GFP_NOIO, 0);
	पूर्ण अन्यथा अणु
		blkdev_issue_discard(bdev,
				log->last_checkpoपूर्णांक + log->rdev->data_offset,
				log->device_size - log->last_checkpoपूर्णांक,
				GFP_NOIO, 0);
		blkdev_issue_discard(bdev, log->rdev->data_offset, end,
				GFP_NOIO, 0);
	पूर्ण
पूर्ण

/*
 * r5c_flush_stripe moves stripe from cached list to handle_list. When called,
 * the stripe must be on r5c_cached_full_stripes or r5c_cached_partial_stripes.
 *
 * must hold conf->device_lock
 */
अटल व्योम r5c_flush_stripe(काष्ठा r5conf *conf, काष्ठा stripe_head *sh)
अणु
	BUG_ON(list_empty(&sh->lru));
	BUG_ON(!test_bit(STRIPE_R5C_CACHING, &sh->state));
	BUG_ON(test_bit(STRIPE_HANDLE, &sh->state));

	/*
	 * The stripe is not ON_RELEASE_LIST, so it is safe to call
	 * raid5_release_stripe() जबतक holding conf->device_lock
	 */
	BUG_ON(test_bit(STRIPE_ON_RELEASE_LIST, &sh->state));
	lockdep_निश्चित_held(&conf->device_lock);

	list_del_init(&sh->lru);
	atomic_inc(&sh->count);

	set_bit(STRIPE_HANDLE, &sh->state);
	atomic_inc(&conf->active_stripes);
	r5c_make_stripe_ग_लिखो_out(sh);

	अगर (test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state))
		atomic_inc(&conf->r5c_flushing_partial_stripes);
	अन्यथा
		atomic_inc(&conf->r5c_flushing_full_stripes);
	raid5_release_stripe(sh);
पूर्ण

/*
 * अगर num == 0, flush all full stripes
 * अगर num > 0, flush all full stripes. If less than num full stripes are
 *             flushed, flush some partial stripes until totally num stripes are
 *             flushed or there is no more cached stripes.
 */
व्योम r5c_flush_cache(काष्ठा r5conf *conf, पूर्णांक num)
अणु
	पूर्णांक count;
	काष्ठा stripe_head *sh, *next;

	lockdep_निश्चित_held(&conf->device_lock);
	अगर (!conf->log)
		वापस;

	count = 0;
	list_क्रम_each_entry_safe(sh, next, &conf->r5c_full_stripe_list, lru) अणु
		r5c_flush_stripe(conf, sh);
		count++;
	पूर्ण

	अगर (count >= num)
		वापस;
	list_क्रम_each_entry_safe(sh, next,
				 &conf->r5c_partial_stripe_list, lru) अणु
		r5c_flush_stripe(conf, sh);
		अगर (++count >= num)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम r5c_करो_reclaim(काष्ठा r5conf *conf)
अणु
	काष्ठा r5l_log *log = conf->log;
	काष्ठा stripe_head *sh;
	पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक total_cached;
	पूर्णांक stripes_to_flush;
	पूर्णांक flushing_partial, flushing_full;

	अगर (!r5c_is_ग_लिखोback(log))
		वापस;

	flushing_partial = atomic_पढ़ो(&conf->r5c_flushing_partial_stripes);
	flushing_full = atomic_पढ़ो(&conf->r5c_flushing_full_stripes);
	total_cached = atomic_पढ़ो(&conf->r5c_cached_partial_stripes) +
		atomic_पढ़ो(&conf->r5c_cached_full_stripes) -
		flushing_full - flushing_partial;

	अगर (total_cached > conf->min_nr_stripes * 3 / 4 ||
	    atomic_पढ़ो(&conf->empty_inactive_list_nr) > 0)
		/*
		 * अगर stripe cache pressure high, flush all full stripes and
		 * some partial stripes
		 */
		stripes_to_flush = R5C_RECLAIM_STRIPE_GROUP;
	अन्यथा अगर (total_cached > conf->min_nr_stripes * 1 / 2 ||
		 atomic_पढ़ो(&conf->r5c_cached_full_stripes) - flushing_full >
		 R5C_FULL_STRIPE_FLUSH_BATCH(conf))
		/*
		 * अगर stripe cache pressure moderate, or अगर there is many full
		 * stripes,flush all full stripes
		 */
		stripes_to_flush = 0;
	अन्यथा
		/* no need to flush */
		stripes_to_flush = -1;

	अगर (stripes_to_flush >= 0) अणु
		spin_lock_irqsave(&conf->device_lock, flags);
		r5c_flush_cache(conf, stripes_to_flush);
		spin_unlock_irqrestore(&conf->device_lock, flags);
	पूर्ण

	/* अगर log space is tight, flush stripes on stripe_in_journal_list */
	अगर (test_bit(R5C_LOG_TIGHT, &conf->cache_state)) अणु
		spin_lock_irqsave(&log->stripe_in_journal_lock, flags);
		spin_lock(&conf->device_lock);
		list_क्रम_each_entry(sh, &log->stripe_in_journal_list, r5c) अणु
			/*
			 * stripes on stripe_in_journal_list could be in any
			 * state of the stripe_cache state machine. In this
			 * हाल, we only want to flush stripe on
			 * r5c_cached_full/partial_stripes. The following
			 * condition makes sure the stripe is on one of the
			 * two lists.
			 */
			अगर (!list_empty(&sh->lru) &&
			    !test_bit(STRIPE_HANDLE, &sh->state) &&
			    atomic_पढ़ो(&sh->count) == 0) अणु
				r5c_flush_stripe(conf, sh);
				अगर (count++ >= R5C_RECLAIM_STRIPE_GROUP)
					अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&conf->device_lock);
		spin_unlock_irqrestore(&log->stripe_in_journal_lock, flags);
	पूर्ण

	अगर (!test_bit(R5C_LOG_CRITICAL, &conf->cache_state))
		r5l_run_no_space_stripes(log);

	md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
पूर्ण

अटल व्योम r5l_करो_reclaim(काष्ठा r5l_log *log)
अणु
	काष्ठा r5conf *conf = log->rdev->mddev->निजी;
	sector_t reclaim_target = xchg(&log->reclaim_target, 0);
	sector_t reclaimable;
	sector_t next_checkpoपूर्णांक;
	bool ग_लिखो_super;

	spin_lock_irq(&log->io_list_lock);
	ग_लिखो_super = r5l_reclaimable_space(log) > log->max_मुक्त_space ||
		reclaim_target != 0 || !list_empty(&log->no_space_stripes);
	/*
	 * move proper io_unit to reclaim list. We should not change the order.
	 * reclaimable/unreclaimable io_unit can be mixed in the list, we
	 * shouldn't reuse space of an unreclaimable io_unit
	 */
	जबतक (1) अणु
		reclaimable = r5l_reclaimable_space(log);
		अगर (reclaimable >= reclaim_target ||
		    (list_empty(&log->running_ios) &&
		     list_empty(&log->io_end_ios) &&
		     list_empty(&log->flushing_ios) &&
		     list_empty(&log->finished_ios)))
			अवरोध;

		md_wakeup_thपढ़ो(log->rdev->mddev->thपढ़ो);
		रुको_event_lock_irq(log->iounit_रुको,
				    r5l_reclaimable_space(log) > reclaimable,
				    log->io_list_lock);
	पूर्ण

	next_checkpoपूर्णांक = r5c_calculate_new_cp(conf);
	spin_unlock_irq(&log->io_list_lock);

	अगर (reclaimable == 0 || !ग_लिखो_super)
		वापस;

	/*
	 * ग_लिखो_super will flush cache of each raid disk. We must ग_लिखो super
	 * here, because the log area might be reused soon and we करोn't want to
	 * confuse recovery
	 */
	r5l_ग_लिखो_super_and_discard_space(log, next_checkpoपूर्णांक);

	mutex_lock(&log->io_mutex);
	log->last_checkpoपूर्णांक = next_checkpoपूर्णांक;
	r5c_update_log_state(log);
	mutex_unlock(&log->io_mutex);

	r5l_run_no_space_stripes(log);
पूर्ण

अटल व्योम r5l_reclaim_thपढ़ो(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	काष्ठा mddev *mddev = thपढ़ो->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा r5l_log *log = conf->log;

	अगर (!log)
		वापस;
	r5c_करो_reclaim(conf);
	r5l_करो_reclaim(log);
पूर्ण

व्योम r5l_wake_reclaim(काष्ठा r5l_log *log, sector_t space)
अणु
	अचिन्हित दीर्घ target;
	अचिन्हित दीर्घ new = (अचिन्हित दीर्घ)space; /* overflow in theory */

	अगर (!log)
		वापस;
	करो अणु
		target = log->reclaim_target;
		अगर (new < target)
			वापस;
	पूर्ण जबतक (cmpxchg(&log->reclaim_target, target, new) != target);
	md_wakeup_thपढ़ो(log->reclaim_thपढ़ो);
पूर्ण

व्योम r5l_quiesce(काष्ठा r5l_log *log, पूर्णांक quiesce)
अणु
	काष्ठा mddev *mddev;

	अगर (quiesce) अणु
		/* make sure r5l_ग_लिखो_super_and_discard_space निकासs */
		mddev = log->rdev->mddev;
		wake_up(&mddev->sb_रुको);
		kthपढ़ो_park(log->reclaim_thपढ़ो->tsk);
		r5l_wake_reclaim(log, MaxSector);
		r5l_करो_reclaim(log);
	पूर्ण अन्यथा
		kthपढ़ो_unpark(log->reclaim_thपढ़ो->tsk);
पूर्ण

bool r5l_log_disk_error(काष्ठा r5conf *conf)
अणु
	काष्ठा r5l_log *log;
	bool ret;
	/* करोn't allow ग_लिखो अगर journal disk is missing */
	rcu_पढ़ो_lock();
	log = rcu_dereference(conf->log);

	अगर (!log)
		ret = test_bit(MD_HAS_JOURNAL, &conf->mddev->flags);
	अन्यथा
		ret = test_bit(Faulty, &log->rdev->flags);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

#घोषणा R5L_RECOVERY_PAGE_POOL_SIZE 256

काष्ठा r5l_recovery_ctx अणु
	काष्ठा page *meta_page;		/* current meta */
	sector_t meta_total_blocks;	/* total size of current meta and data */
	sector_t pos;			/* recovery position */
	u64 seq;			/* recovery position seq */
	पूर्णांक data_parity_stripes;	/* number of data_parity stripes */
	पूर्णांक data_only_stripes;		/* number of data_only stripes */
	काष्ठा list_head cached_list;

	/*
	 * पढ़ो ahead page pool (ra_pool)
	 * in recovery, log is पढ़ो sequentially. It is not efficient to
	 * पढ़ो every page with sync_page_io(). The पढ़ो ahead page pool
	 * पढ़ोs multiple pages with one IO, so further log पढ़ो can
	 * just copy data from the pool.
	 */
	काष्ठा page *ra_pool[R5L_RECOVERY_PAGE_POOL_SIZE];
	sector_t pool_offset;	/* offset of first page in the pool */
	पूर्णांक total_pages;	/* total allocated pages */
	पूर्णांक valid_pages;	/* pages with valid data */
	काष्ठा bio *ra_bio;	/* bio to करो the पढ़ो ahead */
पूर्ण;

अटल पूर्णांक r5l_recovery_allocate_ra_pool(काष्ठा r5l_log *log,
					    काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा page *page;

	ctx->ra_bio = bio_alloc_bioset(GFP_KERNEL, BIO_MAX_VECS, &log->bs);
	अगर (!ctx->ra_bio)
		वापस -ENOMEM;

	ctx->valid_pages = 0;
	ctx->total_pages = 0;
	जबतक (ctx->total_pages < R5L_RECOVERY_PAGE_POOL_SIZE) अणु
		page = alloc_page(GFP_KERNEL);

		अगर (!page)
			अवरोध;
		ctx->ra_pool[ctx->total_pages] = page;
		ctx->total_pages += 1;
	पूर्ण

	अगर (ctx->total_pages == 0) अणु
		bio_put(ctx->ra_bio);
		वापस -ENOMEM;
	पूर्ण

	ctx->pool_offset = 0;
	वापस 0;
पूर्ण

अटल व्योम r5l_recovery_मुक्त_ra_pool(काष्ठा r5l_log *log,
					काष्ठा r5l_recovery_ctx *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ctx->total_pages; ++i)
		put_page(ctx->ra_pool[i]);
	bio_put(ctx->ra_bio);
पूर्ण

/*
 * fetch ctx->valid_pages pages from offset
 * In normal हालs, ctx->valid_pages == ctx->total_pages after the call.
 * However, अगर the offset is बंद to the end of the journal device,
 * ctx->valid_pages could be smaller than ctx->total_pages
 */
अटल पूर्णांक r5l_recovery_fetch_ra_pool(काष्ठा r5l_log *log,
				      काष्ठा r5l_recovery_ctx *ctx,
				      sector_t offset)
अणु
	bio_reset(ctx->ra_bio);
	bio_set_dev(ctx->ra_bio, log->rdev->bdev);
	bio_set_op_attrs(ctx->ra_bio, REQ_OP_READ, 0);
	ctx->ra_bio->bi_iter.bi_sector = log->rdev->data_offset + offset;

	ctx->valid_pages = 0;
	ctx->pool_offset = offset;

	जबतक (ctx->valid_pages < ctx->total_pages) अणु
		bio_add_page(ctx->ra_bio,
			     ctx->ra_pool[ctx->valid_pages], PAGE_SIZE, 0);
		ctx->valid_pages += 1;

		offset = r5l_ring_add(log, offset, BLOCK_SECTORS);

		अगर (offset == 0)  /* reached end of the device */
			अवरोध;
	पूर्ण

	वापस submit_bio_रुको(ctx->ra_bio);
पूर्ण

/*
 * try पढ़ो a page from the पढ़ो ahead page pool, अगर the page is not in the
 * pool, call r5l_recovery_fetch_ra_pool
 */
अटल पूर्णांक r5l_recovery_पढ़ो_page(काष्ठा r5l_log *log,
				  काष्ठा r5l_recovery_ctx *ctx,
				  काष्ठा page *page,
				  sector_t offset)
अणु
	पूर्णांक ret;

	अगर (offset < ctx->pool_offset ||
	    offset >= ctx->pool_offset + ctx->valid_pages * BLOCK_SECTORS) अणु
		ret = r5l_recovery_fetch_ra_pool(log, ctx, offset);
		अगर (ret)
			वापस ret;
	पूर्ण

	BUG_ON(offset < ctx->pool_offset ||
	       offset >= ctx->pool_offset + ctx->valid_pages * BLOCK_SECTORS);

	स_नकल(page_address(page),
	       page_address(ctx->ra_pool[(offset - ctx->pool_offset) >>
					 BLOCK_SECTOR_SHIFT]),
	       PAGE_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक r5l_recovery_पढ़ो_meta_block(काष्ठा r5l_log *log,
					काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा page *page = ctx->meta_page;
	काष्ठा r5l_meta_block *mb;
	u32 crc, stored_crc;
	पूर्णांक ret;

	ret = r5l_recovery_पढ़ो_page(log, ctx, page, ctx->pos);
	अगर (ret != 0)
		वापस ret;

	mb = page_address(page);
	stored_crc = le32_to_cpu(mb->checksum);
	mb->checksum = 0;

	अगर (le32_to_cpu(mb->magic) != R5LOG_MAGIC ||
	    le64_to_cpu(mb->seq) != ctx->seq ||
	    mb->version != R5LOG_VERSION ||
	    le64_to_cpu(mb->position) != ctx->pos)
		वापस -EINVAL;

	crc = crc32c_le(log->uuid_checksum, mb, PAGE_SIZE);
	अगर (stored_crc != crc)
		वापस -EINVAL;

	अगर (le32_to_cpu(mb->meta_size) > PAGE_SIZE)
		वापस -EINVAL;

	ctx->meta_total_blocks = BLOCK_SECTORS;

	वापस 0;
पूर्ण

अटल व्योम
r5l_recovery_create_empty_meta_block(काष्ठा r5l_log *log,
				     काष्ठा page *page,
				     sector_t pos, u64 seq)
अणु
	काष्ठा r5l_meta_block *mb;

	mb = page_address(page);
	clear_page(mb);
	mb->magic = cpu_to_le32(R5LOG_MAGIC);
	mb->version = R5LOG_VERSION;
	mb->meta_size = cpu_to_le32(माप(काष्ठा r5l_meta_block));
	mb->seq = cpu_to_le64(seq);
	mb->position = cpu_to_le64(pos);
पूर्ण

अटल पूर्णांक r5l_log_ग_लिखो_empty_meta_block(काष्ठा r5l_log *log, sector_t pos,
					  u64 seq)
अणु
	काष्ठा page *page;
	काष्ठा r5l_meta_block *mb;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;
	r5l_recovery_create_empty_meta_block(log, page, pos, seq);
	mb = page_address(page);
	mb->checksum = cpu_to_le32(crc32c_le(log->uuid_checksum,
					     mb, PAGE_SIZE));
	अगर (!sync_page_io(log->rdev, pos, PAGE_SIZE, page, REQ_OP_WRITE,
			  REQ_SYNC | REQ_FUA, false)) अणु
		__मुक्त_page(page);
		वापस -EIO;
	पूर्ण
	__मुक्त_page(page);
	वापस 0;
पूर्ण

/*
 * r5l_recovery_load_data and r5l_recovery_load_parity uses flag R5_Wantग_लिखो
 * to mark valid (potentially not flushed) data in the journal.
 *
 * We alपढ़ोy verअगरied checksum in r5l_recovery_verअगरy_data_checksum_क्रम_mb,
 * so there should not be any mismatch here.
 */
अटल व्योम r5l_recovery_load_data(काष्ठा r5l_log *log,
				   काष्ठा stripe_head *sh,
				   काष्ठा r5l_recovery_ctx *ctx,
				   काष्ठा r5l_payload_data_parity *payload,
				   sector_t log_offset)
अणु
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	पूर्णांक dd_idx;

	raid5_compute_sector(conf,
			     le64_to_cpu(payload->location), 0,
			     &dd_idx, sh);
	r5l_recovery_पढ़ो_page(log, ctx, sh->dev[dd_idx].page, log_offset);
	sh->dev[dd_idx].log_checksum =
		le32_to_cpu(payload->checksum[0]);
	ctx->meta_total_blocks += BLOCK_SECTORS;

	set_bit(R5_Wantग_लिखो, &sh->dev[dd_idx].flags);
	set_bit(STRIPE_R5C_CACHING, &sh->state);
पूर्ण

अटल व्योम r5l_recovery_load_parity(काष्ठा r5l_log *log,
				     काष्ठा stripe_head *sh,
				     काष्ठा r5l_recovery_ctx *ctx,
				     काष्ठा r5l_payload_data_parity *payload,
				     sector_t log_offset)
अणु
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा r5conf *conf = mddev->निजी;

	ctx->meta_total_blocks += BLOCK_SECTORS * conf->max_degraded;
	r5l_recovery_पढ़ो_page(log, ctx, sh->dev[sh->pd_idx].page, log_offset);
	sh->dev[sh->pd_idx].log_checksum =
		le32_to_cpu(payload->checksum[0]);
	set_bit(R5_Wantग_लिखो, &sh->dev[sh->pd_idx].flags);

	अगर (sh->qd_idx >= 0) अणु
		r5l_recovery_पढ़ो_page(
			log, ctx, sh->dev[sh->qd_idx].page,
			r5l_ring_add(log, log_offset, BLOCK_SECTORS));
		sh->dev[sh->qd_idx].log_checksum =
			le32_to_cpu(payload->checksum[1]);
		set_bit(R5_Wantग_लिखो, &sh->dev[sh->qd_idx].flags);
	पूर्ण
	clear_bit(STRIPE_R5C_CACHING, &sh->state);
पूर्ण

अटल व्योम r5l_recovery_reset_stripe(काष्ठा stripe_head *sh)
अणु
	पूर्णांक i;

	sh->state = 0;
	sh->log_start = MaxSector;
	क्रम (i = sh->disks; i--; )
		sh->dev[i].flags = 0;
पूर्ण

अटल व्योम
r5l_recovery_replay_one_stripe(काष्ठा r5conf *conf,
			       काष्ठा stripe_head *sh,
			       काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा md_rdev *rdev, *rrdev;
	पूर्णांक disk_index;
	पूर्णांक data_count = 0;

	क्रम (disk_index = 0; disk_index < sh->disks; disk_index++) अणु
		अगर (!test_bit(R5_Wantग_लिखो, &sh->dev[disk_index].flags))
			जारी;
		अगर (disk_index == sh->qd_idx || disk_index == sh->pd_idx)
			जारी;
		data_count++;
	पूर्ण

	/*
	 * stripes that only have parity must have been flushed
	 * beक्रमe the crash that we are now recovering from, so
	 * there is nothing more to recovery.
	 */
	अगर (data_count == 0)
		जाओ out;

	क्रम (disk_index = 0; disk_index < sh->disks; disk_index++) अणु
		अगर (!test_bit(R5_Wantग_लिखो, &sh->dev[disk_index].flags))
			जारी;

		/* in हाल device is broken */
		rcu_पढ़ो_lock();
		rdev = rcu_dereference(conf->disks[disk_index].rdev);
		अगर (rdev) अणु
			atomic_inc(&rdev->nr_pending);
			rcu_पढ़ो_unlock();
			sync_page_io(rdev, sh->sector, PAGE_SIZE,
				     sh->dev[disk_index].page, REQ_OP_WRITE, 0,
				     false);
			rdev_dec_pending(rdev, rdev->mddev);
			rcu_पढ़ो_lock();
		पूर्ण
		rrdev = rcu_dereference(conf->disks[disk_index].replacement);
		अगर (rrdev) अणु
			atomic_inc(&rrdev->nr_pending);
			rcu_पढ़ो_unlock();
			sync_page_io(rrdev, sh->sector, PAGE_SIZE,
				     sh->dev[disk_index].page, REQ_OP_WRITE, 0,
				     false);
			rdev_dec_pending(rrdev, rrdev->mddev);
			rcu_पढ़ो_lock();
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	ctx->data_parity_stripes++;
out:
	r5l_recovery_reset_stripe(sh);
पूर्ण

अटल काष्ठा stripe_head *
r5c_recovery_alloc_stripe(
		काष्ठा r5conf *conf,
		sector_t stripe_sect,
		पूर्णांक noblock)
अणु
	काष्ठा stripe_head *sh;

	sh = raid5_get_active_stripe(conf, stripe_sect, 0, noblock, 0);
	अगर (!sh)
		वापस शून्य;  /* no more stripe available */

	r5l_recovery_reset_stripe(sh);

	वापस sh;
पूर्ण

अटल काष्ठा stripe_head *
r5c_recovery_lookup_stripe(काष्ठा list_head *list, sector_t sect)
अणु
	काष्ठा stripe_head *sh;

	list_क्रम_each_entry(sh, list, lru)
		अगर (sh->sector == sect)
			वापस sh;
	वापस शून्य;
पूर्ण

अटल व्योम
r5c_recovery_drop_stripes(काष्ठा list_head *cached_stripe_list,
			  काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा stripe_head *sh, *next;

	list_क्रम_each_entry_safe(sh, next, cached_stripe_list, lru) अणु
		r5l_recovery_reset_stripe(sh);
		list_del_init(&sh->lru);
		raid5_release_stripe(sh);
	पूर्ण
पूर्ण

अटल व्योम
r5c_recovery_replay_stripes(काष्ठा list_head *cached_stripe_list,
			    काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा stripe_head *sh, *next;

	list_क्रम_each_entry_safe(sh, next, cached_stripe_list, lru)
		अगर (!test_bit(STRIPE_R5C_CACHING, &sh->state)) अणु
			r5l_recovery_replay_one_stripe(sh->raid_conf, sh, ctx);
			list_del_init(&sh->lru);
			raid5_release_stripe(sh);
		पूर्ण
पूर्ण

/* अगर matches वापस 0; otherwise वापस -EINVAL */
अटल पूर्णांक
r5l_recovery_verअगरy_data_checksum(काष्ठा r5l_log *log,
				  काष्ठा r5l_recovery_ctx *ctx,
				  काष्ठा page *page,
				  sector_t log_offset, __le32 log_checksum)
अणु
	व्योम *addr;
	u32 checksum;

	r5l_recovery_पढ़ो_page(log, ctx, page, log_offset);
	addr = kmap_atomic(page);
	checksum = crc32c_le(log->uuid_checksum, addr, PAGE_SIZE);
	kunmap_atomic(addr);
	वापस (le32_to_cpu(log_checksum) == checksum) ? 0 : -EINVAL;
पूर्ण

/*
 * beक्रमe loading data to stripe cache, we need verअगरy checksum क्रम all data,
 * अगर there is mismatch क्रम any data page, we drop all data in the mata block
 */
अटल पूर्णांक
r5l_recovery_verअगरy_data_checksum_क्रम_mb(काष्ठा r5l_log *log,
					 काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा r5l_meta_block *mb = page_address(ctx->meta_page);
	sector_t mb_offset = माप(काष्ठा r5l_meta_block);
	sector_t log_offset = r5l_ring_add(log, ctx->pos, BLOCK_SECTORS);
	काष्ठा page *page;
	काष्ठा r5l_payload_data_parity *payload;
	काष्ठा r5l_payload_flush *payload_flush;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	जबतक (mb_offset < le32_to_cpu(mb->meta_size)) अणु
		payload = (व्योम *)mb + mb_offset;
		payload_flush = (व्योम *)mb + mb_offset;

		अगर (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_DATA) अणु
			अगर (r5l_recovery_verअगरy_data_checksum(
				    log, ctx, page, log_offset,
				    payload->checksum[0]) < 0)
				जाओ mismatch;
		पूर्ण अन्यथा अगर (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_PARITY) अणु
			अगर (r5l_recovery_verअगरy_data_checksum(
				    log, ctx, page, log_offset,
				    payload->checksum[0]) < 0)
				जाओ mismatch;
			अगर (conf->max_degraded == 2 && /* q क्रम RAID 6 */
			    r5l_recovery_verअगरy_data_checksum(
				    log, ctx, page,
				    r5l_ring_add(log, log_offset,
						 BLOCK_SECTORS),
				    payload->checksum[1]) < 0)
				जाओ mismatch;
		पूर्ण अन्यथा अगर (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_FLUSH) अणु
			/* nothing to करो क्रम R5LOG_PAYLOAD_FLUSH here */
		पूर्ण अन्यथा /* not R5LOG_PAYLOAD_DATA/PARITY/FLUSH */
			जाओ mismatch;

		अगर (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_FLUSH) अणु
			mb_offset += माप(काष्ठा r5l_payload_flush) +
				le32_to_cpu(payload_flush->size);
		पूर्ण अन्यथा अणु
			/* DATA or PARITY payload */
			log_offset = r5l_ring_add(log, log_offset,
						  le32_to_cpu(payload->size));
			mb_offset += माप(काष्ठा r5l_payload_data_parity) +
				माप(__le32) *
				(le32_to_cpu(payload->size) >> (PAGE_SHIFT - 9));
		पूर्ण

	पूर्ण

	put_page(page);
	वापस 0;

mismatch:
	put_page(page);
	वापस -EINVAL;
पूर्ण

/*
 * Analyze all data/parity pages in one meta block
 * Returns:
 * 0 क्रम success
 * -EINVAL क्रम unknown playload type
 * -EAGAIN क्रम checksum mismatch of data page
 * -ENOMEM क्रम run out of memory (alloc_page failed or run out of stripes)
 */
अटल पूर्णांक
r5c_recovery_analyze_meta_block(काष्ठा r5l_log *log,
				काष्ठा r5l_recovery_ctx *ctx,
				काष्ठा list_head *cached_stripe_list)
अणु
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा r5l_meta_block *mb;
	काष्ठा r5l_payload_data_parity *payload;
	काष्ठा r5l_payload_flush *payload_flush;
	पूर्णांक mb_offset;
	sector_t log_offset;
	sector_t stripe_sect;
	काष्ठा stripe_head *sh;
	पूर्णांक ret;

	/*
	 * क्रम mismatch in data blocks, we will drop all data in this mb, but
	 * we will still पढ़ो next mb क्रम other data with FLUSH flag, as
	 * io_unit could finish out of order.
	 */
	ret = r5l_recovery_verअगरy_data_checksum_क्रम_mb(log, ctx);
	अगर (ret == -EINVAL)
		वापस -EAGAIN;
	अन्यथा अगर (ret)
		वापस ret;   /* -ENOMEM duo to alloc_page() failed */

	mb = page_address(ctx->meta_page);
	mb_offset = माप(काष्ठा r5l_meta_block);
	log_offset = r5l_ring_add(log, ctx->pos, BLOCK_SECTORS);

	जबतक (mb_offset < le32_to_cpu(mb->meta_size)) अणु
		पूर्णांक dd;

		payload = (व्योम *)mb + mb_offset;
		payload_flush = (व्योम *)mb + mb_offset;

		अगर (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_FLUSH) अणु
			पूर्णांक i, count;

			count = le32_to_cpu(payload_flush->size) / माप(__le64);
			क्रम (i = 0; i < count; ++i) अणु
				stripe_sect = le64_to_cpu(payload_flush->flush_stripes[i]);
				sh = r5c_recovery_lookup_stripe(cached_stripe_list,
								stripe_sect);
				अगर (sh) अणु
					WARN_ON(test_bit(STRIPE_R5C_CACHING, &sh->state));
					r5l_recovery_reset_stripe(sh);
					list_del_init(&sh->lru);
					raid5_release_stripe(sh);
				पूर्ण
			पूर्ण

			mb_offset += माप(काष्ठा r5l_payload_flush) +
				le32_to_cpu(payload_flush->size);
			जारी;
		पूर्ण

		/* DATA or PARITY payload */
		stripe_sect = (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_DATA) ?
			raid5_compute_sector(
				conf, le64_to_cpu(payload->location), 0, &dd,
				शून्य)
			: le64_to_cpu(payload->location);

		sh = r5c_recovery_lookup_stripe(cached_stripe_list,
						stripe_sect);

		अगर (!sh) अणु
			sh = r5c_recovery_alloc_stripe(conf, stripe_sect, 1);
			/*
			 * cannot get stripe from raid5_get_active_stripe
			 * try replay some stripes
			 */
			अगर (!sh) अणु
				r5c_recovery_replay_stripes(
					cached_stripe_list, ctx);
				sh = r5c_recovery_alloc_stripe(
					conf, stripe_sect, 1);
			पूर्ण
			अगर (!sh) अणु
				पूर्णांक new_size = conf->min_nr_stripes * 2;
				pr_debug("md/raid:%s: Increasing stripe cache size to %d to recovery data on journal.\n",
					mdname(mddev),
					new_size);
				ret = raid5_set_cache_size(mddev, new_size);
				अगर (conf->min_nr_stripes <= new_size / 2) अणु
					pr_err("md/raid:%s: Cannot increase cache size, ret=%d, new_size=%d, min_nr_stripes=%d, max_nr_stripes=%d\n",
						mdname(mddev),
						ret,
						new_size,
						conf->min_nr_stripes,
						conf->max_nr_stripes);
					वापस -ENOMEM;
				पूर्ण
				sh = r5c_recovery_alloc_stripe(
					conf, stripe_sect, 0);
			पूर्ण
			अगर (!sh) अणु
				pr_err("md/raid:%s: Cannot get enough stripes due to memory pressure. Recovery failed.\n",
					mdname(mddev));
				वापस -ENOMEM;
			पूर्ण
			list_add_tail(&sh->lru, cached_stripe_list);
		पूर्ण

		अगर (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_DATA) अणु
			अगर (!test_bit(STRIPE_R5C_CACHING, &sh->state) &&
			    test_bit(R5_Wantग_लिखो, &sh->dev[sh->pd_idx].flags)) अणु
				r5l_recovery_replay_one_stripe(conf, sh, ctx);
				list_move_tail(&sh->lru, cached_stripe_list);
			पूर्ण
			r5l_recovery_load_data(log, sh, ctx, payload,
					       log_offset);
		पूर्ण अन्यथा अगर (le16_to_cpu(payload->header.type) == R5LOG_PAYLOAD_PARITY)
			r5l_recovery_load_parity(log, sh, ctx, payload,
						 log_offset);
		अन्यथा
			वापस -EINVAL;

		log_offset = r5l_ring_add(log, log_offset,
					  le32_to_cpu(payload->size));

		mb_offset += माप(काष्ठा r5l_payload_data_parity) +
			माप(__le32) *
			(le32_to_cpu(payload->size) >> (PAGE_SHIFT - 9));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Load the stripe पूर्णांकo cache. The stripe will be written out later by
 * the stripe cache state machine.
 */
अटल व्योम r5c_recovery_load_one_stripe(काष्ठा r5l_log *log,
					 काष्ठा stripe_head *sh)
अणु
	काष्ठा r5dev *dev;
	पूर्णांक i;

	क्रम (i = sh->disks; i--; ) अणु
		dev = sh->dev + i;
		अगर (test_and_clear_bit(R5_Wantग_लिखो, &dev->flags)) अणु
			set_bit(R5_InJournal, &dev->flags);
			set_bit(R5_UPTODATE, &dev->flags);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Scan through the log क्रम all to-be-flushed data
 *
 * For stripes with data and parity, namely Data-Parity stripe
 * (STRIPE_R5C_CACHING == 0), we simply replay all the ग_लिखोs.
 *
 * For stripes with only data, namely Data-Only stripe
 * (STRIPE_R5C_CACHING == 1), we load them to stripe cache state machine.
 *
 * For a stripe, अगर we see data after parity, we should discard all previous
 * data and parity क्रम this stripe, as these data are alपढ़ोy flushed to
 * the array.
 *
 * At the end of the scan, we वापस the new journal_tail, which poपूर्णांकs to
 * first data-only stripe on the journal device, or next invalid meta block.
 */
अटल पूर्णांक r5c_recovery_flush_log(काष्ठा r5l_log *log,
				  काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा stripe_head *sh;
	पूर्णांक ret = 0;

	/* scan through the log */
	जबतक (1) अणु
		अगर (r5l_recovery_पढ़ो_meta_block(log, ctx))
			अवरोध;

		ret = r5c_recovery_analyze_meta_block(log, ctx,
						      &ctx->cached_list);
		/*
		 * -EAGAIN means mismatch in data block, in this हाल, we still
		 * try scan the next metablock
		 */
		अगर (ret && ret != -EAGAIN)
			अवरोध;   /* ret == -EINVAL or -ENOMEM */
		ctx->seq++;
		ctx->pos = r5l_ring_add(log, ctx->pos, ctx->meta_total_blocks);
	पूर्ण

	अगर (ret == -ENOMEM) अणु
		r5c_recovery_drop_stripes(&ctx->cached_list, ctx);
		वापस ret;
	पूर्ण

	/* replay data-parity stripes */
	r5c_recovery_replay_stripes(&ctx->cached_list, ctx);

	/* load data-only stripes to stripe cache */
	list_क्रम_each_entry(sh, &ctx->cached_list, lru) अणु
		WARN_ON(!test_bit(STRIPE_R5C_CACHING, &sh->state));
		r5c_recovery_load_one_stripe(log, sh);
		ctx->data_only_stripes++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * we did a recovery. Now ctx.pos poपूर्णांकs to an invalid meta block. New
 * log will start here. but we can't let superblock poपूर्णांक to last valid
 * meta block. The log might looks like:
 * | meta 1| meta 2| meta 3|
 * meta 1 is valid, meta 2 is invalid. meta 3 could be valid. If
 * superblock poपूर्णांकs to meta 1, we ग_लिखो a new valid meta 2n.  अगर crash
 * happens again, new recovery will start from meta 1. Since meta 2n is
 * valid now, recovery will think meta 3 is valid, which is wrong.
 * The solution is we create a new meta in meta2 with its seq == meta
 * 1's seq + 10000 and let superblock poपूर्णांकs to meta2. The same recovery
 * will not think meta 3 is a valid meta, because its seq करोesn't match
 */

/*
 * Beक्रमe recovery, the log looks like the following
 *
 *   ---------------------------------------------
 *   |           valid log        | invalid log  |
 *   ---------------------------------------------
 *   ^
 *   |- log->last_checkpoपूर्णांक
 *   |- log->last_cp_seq
 *
 * Now we scan through the log until we see invalid entry
 *
 *   ---------------------------------------------
 *   |           valid log        | invalid log  |
 *   ---------------------------------------------
 *   ^                            ^
 *   |- log->last_checkpoपूर्णांक      |- ctx->pos
 *   |- log->last_cp_seq          |- ctx->seq
 *
 * From this poपूर्णांक, we need to increase seq number by 10 to aव्योम
 * confusing next recovery.
 *
 *   ---------------------------------------------
 *   |           valid log        | invalid log  |
 *   ---------------------------------------------
 *   ^                              ^
 *   |- log->last_checkpoपूर्णांक        |- ctx->pos+1
 *   |- log->last_cp_seq            |- ctx->seq+10001
 *
 * However, it is not safe to start the state machine yet, because data only
 * parities are not yet secured in RAID. To save these data only parities, we
 * reग_लिखो them from seq+11.
 *
 *   -----------------------------------------------------------------
 *   |           valid log        | data only stripes | invalid log  |
 *   -----------------------------------------------------------------
 *   ^                                                ^
 *   |- log->last_checkpoपूर्णांक                          |- ctx->pos+n
 *   |- log->last_cp_seq                              |- ctx->seq+10000+n
 *
 * If failure happens again during this process, the recovery can safe start
 * again from log->last_checkpoपूर्णांक.
 *
 * Once data only stripes are rewritten to journal, we move log_tail
 *
 *   -----------------------------------------------------------------
 *   |     old log        |    data only stripes    | invalid log  |
 *   -----------------------------------------------------------------
 *                        ^                         ^
 *                        |- log->last_checkpoपूर्णांक   |- ctx->pos+n
 *                        |- log->last_cp_seq       |- ctx->seq+10000+n
 *
 * Then we can safely start the state machine. If failure happens from this
 * poपूर्णांक on, the recovery will start from new log->last_checkpoपूर्णांक.
 */
अटल पूर्णांक
r5c_recovery_reग_लिखो_data_only_stripes(काष्ठा r5l_log *log,
				       काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा stripe_head *sh;
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा page *page;
	sector_t next_checkpoपूर्णांक = MaxSector;

	page = alloc_page(GFP_KERNEL);
	अगर (!page) अणु
		pr_err("md/raid:%s: cannot allocate memory to rewrite data only stripes\n",
		       mdname(mddev));
		वापस -ENOMEM;
	पूर्ण

	WARN_ON(list_empty(&ctx->cached_list));

	list_क्रम_each_entry(sh, &ctx->cached_list, lru) अणु
		काष्ठा r5l_meta_block *mb;
		पूर्णांक i;
		पूर्णांक offset;
		sector_t ग_लिखो_pos;

		WARN_ON(!test_bit(STRIPE_R5C_CACHING, &sh->state));
		r5l_recovery_create_empty_meta_block(log, page,
						     ctx->pos, ctx->seq);
		mb = page_address(page);
		offset = le32_to_cpu(mb->meta_size);
		ग_लिखो_pos = r5l_ring_add(log, ctx->pos, BLOCK_SECTORS);

		क्रम (i = sh->disks; i--; ) अणु
			काष्ठा r5dev *dev = &sh->dev[i];
			काष्ठा r5l_payload_data_parity *payload;
			व्योम *addr;

			अगर (test_bit(R5_InJournal, &dev->flags)) अणु
				payload = (व्योम *)mb + offset;
				payload->header.type = cpu_to_le16(
					R5LOG_PAYLOAD_DATA);
				payload->size = cpu_to_le32(BLOCK_SECTORS);
				payload->location = cpu_to_le64(
					raid5_compute_blocknr(sh, i, 0));
				addr = kmap_atomic(dev->page);
				payload->checksum[0] = cpu_to_le32(
					crc32c_le(log->uuid_checksum, addr,
						  PAGE_SIZE));
				kunmap_atomic(addr);
				sync_page_io(log->rdev, ग_लिखो_pos, PAGE_SIZE,
					     dev->page, REQ_OP_WRITE, 0, false);
				ग_लिखो_pos = r5l_ring_add(log, ग_लिखो_pos,
							 BLOCK_SECTORS);
				offset += माप(__le32) +
					माप(काष्ठा r5l_payload_data_parity);

			पूर्ण
		पूर्ण
		mb->meta_size = cpu_to_le32(offset);
		mb->checksum = cpu_to_le32(crc32c_le(log->uuid_checksum,
						     mb, PAGE_SIZE));
		sync_page_io(log->rdev, ctx->pos, PAGE_SIZE, page,
			     REQ_OP_WRITE, REQ_SYNC | REQ_FUA, false);
		sh->log_start = ctx->pos;
		list_add_tail(&sh->r5c, &log->stripe_in_journal_list);
		atomic_inc(&log->stripe_in_journal_count);
		ctx->pos = ग_लिखो_pos;
		ctx->seq += 1;
		next_checkpoपूर्णांक = sh->log_start;
	पूर्ण
	log->next_checkpoपूर्णांक = next_checkpoपूर्णांक;
	__मुक्त_page(page);
	वापस 0;
पूर्ण

अटल व्योम r5c_recovery_flush_data_only_stripes(काष्ठा r5l_log *log,
						 काष्ठा r5l_recovery_ctx *ctx)
अणु
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा stripe_head *sh, *next;
	bool cleared_pending = false;

	अगर (ctx->data_only_stripes == 0)
		वापस;

	अगर (test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags)) अणु
		cleared_pending = true;
		clear_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
	पूर्ण
	log->r5c_journal_mode = R5C_JOURNAL_MODE_WRITE_BACK;

	list_क्रम_each_entry_safe(sh, next, &ctx->cached_list, lru) अणु
		r5c_make_stripe_ग_लिखो_out(sh);
		set_bit(STRIPE_HANDLE, &sh->state);
		list_del_init(&sh->lru);
		raid5_release_stripe(sh);
	पूर्ण

	/* reuse conf->रुको_क्रम_quiescent in recovery */
	रुको_event(conf->रुको_क्रम_quiescent,
		   atomic_पढ़ो(&conf->active_stripes) == 0);

	log->r5c_journal_mode = R5C_JOURNAL_MODE_WRITE_THROUGH;
	अगर (cleared_pending)
		set_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
पूर्ण

अटल पूर्णांक r5l_recovery_log(काष्ठा r5l_log *log)
अणु
	काष्ठा mddev *mddev = log->rdev->mddev;
	काष्ठा r5l_recovery_ctx *ctx;
	पूर्णांक ret;
	sector_t pos;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->pos = log->last_checkpoपूर्णांक;
	ctx->seq = log->last_cp_seq;
	INIT_LIST_HEAD(&ctx->cached_list);
	ctx->meta_page = alloc_page(GFP_KERNEL);

	अगर (!ctx->meta_page) अणु
		ret =  -ENOMEM;
		जाओ meta_page;
	पूर्ण

	अगर (r5l_recovery_allocate_ra_pool(log, ctx) != 0) अणु
		ret = -ENOMEM;
		जाओ ra_pool;
	पूर्ण

	ret = r5c_recovery_flush_log(log, ctx);

	अगर (ret)
		जाओ error;

	pos = ctx->pos;
	ctx->seq += 10000;

	अगर ((ctx->data_only_stripes == 0) && (ctx->data_parity_stripes == 0))
		pr_info("md/raid:%s: starting from clean shutdown\n",
			 mdname(mddev));
	अन्यथा
		pr_info("md/raid:%s: recovering %d data-only stripes and %d data-parity stripes\n",
			 mdname(mddev), ctx->data_only_stripes,
			 ctx->data_parity_stripes);

	अगर (ctx->data_only_stripes == 0) अणु
		log->next_checkpoपूर्णांक = ctx->pos;
		r5l_log_ग_लिखो_empty_meta_block(log, ctx->pos, ctx->seq++);
		ctx->pos = r5l_ring_add(log, ctx->pos, BLOCK_SECTORS);
	पूर्ण अन्यथा अगर (r5c_recovery_reग_लिखो_data_only_stripes(log, ctx)) अणु
		pr_err("md/raid:%s: failed to rewrite stripes to journal\n",
		       mdname(mddev));
		ret =  -EIO;
		जाओ error;
	पूर्ण

	log->log_start = ctx->pos;
	log->seq = ctx->seq;
	log->last_checkpoपूर्णांक = pos;
	r5l_ग_लिखो_super(log, pos);

	r5c_recovery_flush_data_only_stripes(log, ctx);
	ret = 0;
error:
	r5l_recovery_मुक्त_ra_pool(log, ctx);
ra_pool:
	__मुक्त_page(ctx->meta_page);
meta_page:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

अटल व्योम r5l_ग_लिखो_super(काष्ठा r5l_log *log, sector_t cp)
अणु
	काष्ठा mddev *mddev = log->rdev->mddev;

	log->rdev->journal_tail = cp;
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
पूर्ण

अटल sमाप_प्रकार r5c_journal_mode_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	काष्ठा r5conf *conf;
	पूर्णांक ret;

	spin_lock(&mddev->lock);
	conf = mddev->निजी;
	अगर (!conf || !conf->log) अणु
		spin_unlock(&mddev->lock);
		वापस 0;
	पूर्ण

	चयन (conf->log->r5c_journal_mode) अणु
	हाल R5C_JOURNAL_MODE_WRITE_THROUGH:
		ret = snम_लिखो(
			page, PAGE_SIZE, "[%s] %s\n",
			r5c_journal_mode_str[R5C_JOURNAL_MODE_WRITE_THROUGH],
			r5c_journal_mode_str[R5C_JOURNAL_MODE_WRITE_BACK]);
		अवरोध;
	हाल R5C_JOURNAL_MODE_WRITE_BACK:
		ret = snम_लिखो(
			page, PAGE_SIZE, "%s [%s]\n",
			r5c_journal_mode_str[R5C_JOURNAL_MODE_WRITE_THROUGH],
			r5c_journal_mode_str[R5C_JOURNAL_MODE_WRITE_BACK]);
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण
	spin_unlock(&mddev->lock);
	वापस ret;
पूर्ण

/*
 * Set journal cache mode on @mddev (बाह्यal API initially needed by dm-raid).
 *
 * @mode as defined in 'enum r5c_journal_mode'.
 *
 */
पूर्णांक r5c_journal_mode_set(काष्ठा mddev *mddev, पूर्णांक mode)
अणु
	काष्ठा r5conf *conf;

	अगर (mode < R5C_JOURNAL_MODE_WRITE_THROUGH ||
	    mode > R5C_JOURNAL_MODE_WRITE_BACK)
		वापस -EINVAL;

	conf = mddev->निजी;
	अगर (!conf || !conf->log)
		वापस -ENODEV;

	अगर (raid5_calc_degraded(conf) > 0 &&
	    mode == R5C_JOURNAL_MODE_WRITE_BACK)
		वापस -EINVAL;

	mddev_suspend(mddev);
	conf->log->r5c_journal_mode = mode;
	mddev_resume(mddev);

	pr_debug("md/raid:%s: setting r5c cache mode to %d: %s\n",
		 mdname(mddev), mode, r5c_journal_mode_str[mode]);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(r5c_journal_mode_set);

अटल sमाप_प्रकार r5c_journal_mode_store(काष्ठा mddev *mddev,
				      स्थिर अक्षर *page, माप_प्रकार length)
अणु
	पूर्णांक mode = ARRAY_SIZE(r5c_journal_mode_str);
	माप_प्रकार len = length;
	पूर्णांक ret;

	अगर (len < 2)
		वापस -EINVAL;

	अगर (page[len - 1] == '\n')
		len--;

	जबतक (mode--)
		अगर (म_माप(r5c_journal_mode_str[mode]) == len &&
		    !म_भेदन(page, r5c_journal_mode_str[mode], len))
			अवरोध;
	ret = mddev_lock(mddev);
	अगर (ret)
		वापस ret;
	ret = r5c_journal_mode_set(mddev, mode);
	mddev_unlock(mddev);
	वापस ret ?: length;
पूर्ण

काष्ठा md_sysfs_entry
r5c_journal_mode = __ATTR(journal_mode, 0644,
			  r5c_journal_mode_show, r5c_journal_mode_store);

/*
 * Try handle ग_लिखो operation in caching phase. This function should only
 * be called in ग_लिखो-back mode.
 *
 * If all outstanding ग_लिखोs can be handled in caching phase, वापसs 0
 * If ग_लिखोs requires ग_लिखो-out phase, call r5c_make_stripe_ग_लिखो_out()
 * and वापसs -EAGAIN
 */
पूर्णांक r5c_try_caching_ग_लिखो(काष्ठा r5conf *conf,
			  काष्ठा stripe_head *sh,
			  काष्ठा stripe_head_state *s,
			  पूर्णांक disks)
अणु
	काष्ठा r5l_log *log = conf->log;
	पूर्णांक i;
	काष्ठा r5dev *dev;
	पूर्णांक to_cache = 0;
	व्योम **pslot;
	sector_t tree_index;
	पूर्णांक ret;
	uपूर्णांकptr_t refcount;

	BUG_ON(!r5c_is_ग_लिखोback(log));

	अगर (!test_bit(STRIPE_R5C_CACHING, &sh->state)) अणु
		/*
		 * There are two dअगरferent scenarios here:
		 *  1. The stripe has some data cached, and it is sent to
		 *     ग_लिखो-out phase क्रम reclaim
		 *  2. The stripe is clean, and this is the first ग_लिखो
		 *
		 * For 1, वापस -EAGAIN, so we जारी with
		 * handle_stripe_dirtying().
		 *
		 * For 2, set STRIPE_R5C_CACHING and जारी with caching
		 * ग_लिखो.
		 */

		/* हाल 1: anything injournal or anything in written */
		अगर (s->injournal > 0 || s->written > 0)
			वापस -EAGAIN;
		/* हाल 2 */
		set_bit(STRIPE_R5C_CACHING, &sh->state);
	पूर्ण

	/*
	 * When run in degraded mode, array is set to ग_लिखो-through mode.
	 * This check helps drain pending ग_लिखो safely in the transition to
	 * ग_लिखो-through mode.
	 *
	 * When a stripe is syncing, the ग_लिखो is also handled in ग_लिखो
	 * through mode.
	 */
	अगर (s->failed || test_bit(STRIPE_SYNCING, &sh->state)) अणु
		r5c_make_stripe_ग_लिखो_out(sh);
		वापस -EAGAIN;
	पूर्ण

	क्रम (i = disks; i--; ) अणु
		dev = &sh->dev[i];
		/* अगर non-overग_लिखो, use writing-out phase */
		अगर (dev->toग_लिखो && !test_bit(R5_OVERWRITE, &dev->flags) &&
		    !test_bit(R5_InJournal, &dev->flags)) अणु
			r5c_make_stripe_ग_लिखो_out(sh);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	/* अगर the stripe is not counted in big_stripe_tree, add it now */
	अगर (!test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state) &&
	    !test_bit(STRIPE_R5C_FULL_STRIPE, &sh->state)) अणु
		tree_index = r5c_tree_index(conf, sh->sector);
		spin_lock(&log->tree_lock);
		pslot = radix_tree_lookup_slot(&log->big_stripe_tree,
					       tree_index);
		अगर (pslot) अणु
			refcount = (uपूर्णांकptr_t)radix_tree_deref_slot_रक्षित(
				pslot, &log->tree_lock) >>
				R5C_RADIX_COUNT_SHIFT;
			radix_tree_replace_slot(
				&log->big_stripe_tree, pslot,
				(व्योम *)((refcount + 1) << R5C_RADIX_COUNT_SHIFT));
		पूर्ण अन्यथा अणु
			/*
			 * this radix_tree_insert can fail safely, so no
			 * need to call radix_tree_preload()
			 */
			ret = radix_tree_insert(
				&log->big_stripe_tree, tree_index,
				(व्योम *)(1 << R5C_RADIX_COUNT_SHIFT));
			अगर (ret) अणु
				spin_unlock(&log->tree_lock);
				r5c_make_stripe_ग_लिखो_out(sh);
				वापस -EAGAIN;
			पूर्ण
		पूर्ण
		spin_unlock(&log->tree_lock);

		/*
		 * set STRIPE_R5C_PARTIAL_STRIPE, this shows the stripe is
		 * counted in the radix tree
		 */
		set_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state);
		atomic_inc(&conf->r5c_cached_partial_stripes);
	पूर्ण

	क्रम (i = disks; i--; ) अणु
		dev = &sh->dev[i];
		अगर (dev->toग_लिखो) अणु
			set_bit(R5_Wantग_लिखो, &dev->flags);
			set_bit(R5_Wantdrain, &dev->flags);
			set_bit(R5_LOCKED, &dev->flags);
			to_cache++;
		पूर्ण
	पूर्ण

	अगर (to_cache) अणु
		set_bit(STRIPE_OP_BIODRAIN, &s->ops_request);
		/*
		 * set STRIPE_LOG_TRAPPED, which triggers r5c_cache_data()
		 * in ops_run_io(). STRIPE_LOG_TRAPPED will be cleared in
		 * r5c_handle_data_cached()
		 */
		set_bit(STRIPE_LOG_TRAPPED, &sh->state);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * मुक्त extra pages (orig_page) we allocated क्रम prexor
 */
व्योम r5c_release_extra_page(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक i;
	bool using_disk_info_extra_page;

	using_disk_info_extra_page =
		sh->dev[0].orig_page == conf->disks[0].extra_page;

	क्रम (i = sh->disks; i--; )
		अगर (sh->dev[i].page != sh->dev[i].orig_page) अणु
			काष्ठा page *p = sh->dev[i].orig_page;

			sh->dev[i].orig_page = sh->dev[i].page;
			clear_bit(R5_OrigPageUPTDODATE, &sh->dev[i].flags);

			अगर (!using_disk_info_extra_page)
				put_page(p);
		पूर्ण

	अगर (using_disk_info_extra_page) अणु
		clear_bit(R5C_EXTRA_PAGE_IN_USE, &conf->cache_state);
		md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
	पूर्ण
पूर्ण

व्योम r5c_use_extra_page(काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक i;
	काष्ठा r5dev *dev;

	क्रम (i = sh->disks; i--; ) अणु
		dev = &sh->dev[i];
		अगर (dev->orig_page != dev->page)
			put_page(dev->orig_page);
		dev->orig_page = conf->disks[i].extra_page;
	पूर्ण
पूर्ण

/*
 * clean up the stripe (clear R5_InJournal क्रम dev[pd_idx] etc.) after the
 * stripe is committed to RAID disks.
 */
व्योम r5c_finish_stripe_ग_लिखो_out(काष्ठा r5conf *conf,
				 काष्ठा stripe_head *sh,
				 काष्ठा stripe_head_state *s)
अणु
	काष्ठा r5l_log *log = conf->log;
	पूर्णांक i;
	पूर्णांक करो_wakeup = 0;
	sector_t tree_index;
	व्योम **pslot;
	uपूर्णांकptr_t refcount;

	अगर (!log || !test_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags))
		वापस;

	WARN_ON(test_bit(STRIPE_R5C_CACHING, &sh->state));
	clear_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags);

	अगर (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH)
		वापस;

	क्रम (i = sh->disks; i--; ) अणु
		clear_bit(R5_InJournal, &sh->dev[i].flags);
		अगर (test_and_clear_bit(R5_Overlap, &sh->dev[i].flags))
			करो_wakeup = 1;
	पूर्ण

	/*
	 * analyse_stripe() runs beक्रमe r5c_finish_stripe_ग_लिखो_out(),
	 * We updated R5_InJournal, so we also update s->injournal.
	 */
	s->injournal = 0;

	अगर (test_and_clear_bit(STRIPE_FULL_WRITE, &sh->state))
		अगर (atomic_dec_and_test(&conf->pending_full_ग_लिखोs))
			md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);

	अगर (करो_wakeup)
		wake_up(&conf->रुको_क्रम_overlap);

	spin_lock_irq(&log->stripe_in_journal_lock);
	list_del_init(&sh->r5c);
	spin_unlock_irq(&log->stripe_in_journal_lock);
	sh->log_start = MaxSector;

	atomic_dec(&log->stripe_in_journal_count);
	r5c_update_log_state(log);

	/* stop counting this stripe in big_stripe_tree */
	अगर (test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state) ||
	    test_bit(STRIPE_R5C_FULL_STRIPE, &sh->state)) अणु
		tree_index = r5c_tree_index(conf, sh->sector);
		spin_lock(&log->tree_lock);
		pslot = radix_tree_lookup_slot(&log->big_stripe_tree,
					       tree_index);
		BUG_ON(pslot == शून्य);
		refcount = (uपूर्णांकptr_t)radix_tree_deref_slot_रक्षित(
			pslot, &log->tree_lock) >>
			R5C_RADIX_COUNT_SHIFT;
		अगर (refcount == 1)
			radix_tree_delete(&log->big_stripe_tree, tree_index);
		अन्यथा
			radix_tree_replace_slot(
				&log->big_stripe_tree, pslot,
				(व्योम *)((refcount - 1) << R5C_RADIX_COUNT_SHIFT));
		spin_unlock(&log->tree_lock);
	पूर्ण

	अगर (test_and_clear_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state)) अणु
		BUG_ON(atomic_पढ़ो(&conf->r5c_cached_partial_stripes) == 0);
		atomic_dec(&conf->r5c_flushing_partial_stripes);
		atomic_dec(&conf->r5c_cached_partial_stripes);
	पूर्ण

	अगर (test_and_clear_bit(STRIPE_R5C_FULL_STRIPE, &sh->state)) अणु
		BUG_ON(atomic_पढ़ो(&conf->r5c_cached_full_stripes) == 0);
		atomic_dec(&conf->r5c_flushing_full_stripes);
		atomic_dec(&conf->r5c_cached_full_stripes);
	पूर्ण

	r5l_append_flush_payload(log, sh->sector);
	/* stripe is flused to raid disks, we can करो resync now */
	अगर (test_bit(STRIPE_SYNC_REQUESTED, &sh->state))
		set_bit(STRIPE_HANDLE, &sh->state);
पूर्ण

पूर्णांक r5c_cache_data(काष्ठा r5l_log *log, काष्ठा stripe_head *sh)
अणु
	काष्ठा r5conf *conf = sh->raid_conf;
	पूर्णांक pages = 0;
	पूर्णांक reserve;
	पूर्णांक i;
	पूर्णांक ret = 0;

	BUG_ON(!log);

	क्रम (i = 0; i < sh->disks; i++) अणु
		व्योम *addr;

		अगर (!test_bit(R5_Wantग_लिखो, &sh->dev[i].flags))
			जारी;
		addr = kmap_atomic(sh->dev[i].page);
		sh->dev[i].log_checksum = crc32c_le(log->uuid_checksum,
						    addr, PAGE_SIZE);
		kunmap_atomic(addr);
		pages++;
	पूर्ण
	WARN_ON(pages == 0);

	/*
	 * The stripe must enter state machine again to call endio, so
	 * करोn't delay.
	 */
	clear_bit(STRIPE_DELAYED, &sh->state);
	atomic_inc(&sh->count);

	mutex_lock(&log->io_mutex);
	/* meta + data */
	reserve = (1 + pages) << (PAGE_SHIFT - 9);

	अगर (test_bit(R5C_LOG_CRITICAL, &conf->cache_state) &&
	    sh->log_start == MaxSector)
		r5l_add_no_space_stripe(log, sh);
	अन्यथा अगर (!r5l_has_मुक्त_space(log, reserve)) अणु
		अगर (sh->log_start == log->last_checkpoपूर्णांक)
			BUG();
		अन्यथा
			r5l_add_no_space_stripe(log, sh);
	पूर्ण अन्यथा अणु
		ret = r5l_log_stripe(log, sh, pages, 0);
		अगर (ret) अणु
			spin_lock_irq(&log->io_list_lock);
			list_add_tail(&sh->log_list, &log->no_mem_stripes);
			spin_unlock_irq(&log->io_list_lock);
		पूर्ण
	पूर्ण

	mutex_unlock(&log->io_mutex);
	वापस 0;
पूर्ण

/* check whether this big stripe is in ग_लिखो back cache. */
bool r5c_big_stripe_cached(काष्ठा r5conf *conf, sector_t sect)
अणु
	काष्ठा r5l_log *log = conf->log;
	sector_t tree_index;
	व्योम *slot;

	अगर (!log)
		वापस false;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	tree_index = r5c_tree_index(conf, sect);
	slot = radix_tree_lookup(&log->big_stripe_tree, tree_index);
	वापस slot != शून्य;
पूर्ण

अटल पूर्णांक r5l_load_log(काष्ठा r5l_log *log)
अणु
	काष्ठा md_rdev *rdev = log->rdev;
	काष्ठा page *page;
	काष्ठा r5l_meta_block *mb;
	sector_t cp = log->rdev->journal_tail;
	u32 stored_crc, expected_crc;
	bool create_super = false;
	पूर्णांक ret = 0;

	/* Make sure it's valid */
	अगर (cp >= rdev->sectors || round_करोwn(cp, BLOCK_SECTORS) != cp)
		cp = 0;
	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	अगर (!sync_page_io(rdev, cp, PAGE_SIZE, page, REQ_OP_READ, 0, false)) अणु
		ret = -EIO;
		जाओ ioerr;
	पूर्ण
	mb = page_address(page);

	अगर (le32_to_cpu(mb->magic) != R5LOG_MAGIC ||
	    mb->version != R5LOG_VERSION) अणु
		create_super = true;
		जाओ create;
	पूर्ण
	stored_crc = le32_to_cpu(mb->checksum);
	mb->checksum = 0;
	expected_crc = crc32c_le(log->uuid_checksum, mb, PAGE_SIZE);
	अगर (stored_crc != expected_crc) अणु
		create_super = true;
		जाओ create;
	पूर्ण
	अगर (le64_to_cpu(mb->position) != cp) अणु
		create_super = true;
		जाओ create;
	पूर्ण
create:
	अगर (create_super) अणु
		log->last_cp_seq = pअक्रमom_u32();
		cp = 0;
		r5l_log_ग_लिखो_empty_meta_block(log, cp, log->last_cp_seq);
		/*
		 * Make sure super poपूर्णांकs to correct address. Log might have
		 * data very soon. If super hasn't correct log tail address,
		 * recovery can't find the log
		 */
		r5l_ग_लिखो_super(log, cp);
	पूर्ण अन्यथा
		log->last_cp_seq = le64_to_cpu(mb->seq);

	log->device_size = round_करोwn(rdev->sectors, BLOCK_SECTORS);
	log->max_मुक्त_space = log->device_size >> RECLAIM_MAX_FREE_SPACE_SHIFT;
	अगर (log->max_मुक्त_space > RECLAIM_MAX_FREE_SPACE)
		log->max_मुक्त_space = RECLAIM_MAX_FREE_SPACE;
	log->last_checkpoपूर्णांक = cp;

	__मुक्त_page(page);

	अगर (create_super) अणु
		log->log_start = r5l_ring_add(log, cp, BLOCK_SECTORS);
		log->seq = log->last_cp_seq + 1;
		log->next_checkpoपूर्णांक = cp;
	पूर्ण अन्यथा
		ret = r5l_recovery_log(log);

	r5c_update_log_state(log);
	वापस ret;
ioerr:
	__मुक्त_page(page);
	वापस ret;
पूर्ण

पूर्णांक r5l_start(काष्ठा r5l_log *log)
अणु
	पूर्णांक ret;

	अगर (!log)
		वापस 0;

	ret = r5l_load_log(log);
	अगर (ret) अणु
		काष्ठा mddev *mddev = log->rdev->mddev;
		काष्ठा r5conf *conf = mddev->निजी;

		r5l_निकास_log(conf);
	पूर्ण
	वापस ret;
पूर्ण

व्योम r5c_update_on_rdev_error(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा r5conf *conf = mddev->निजी;
	काष्ठा r5l_log *log = conf->log;

	अगर (!log)
		वापस;

	अगर ((raid5_calc_degraded(conf) > 0 ||
	     test_bit(Journal, &rdev->flags)) &&
	    conf->log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_BACK)
		schedule_work(&log->disable_ग_लिखोback_work);
पूर्ण

पूर्णांक r5l_init_log(काष्ठा r5conf *conf, काष्ठा md_rdev *rdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(rdev->bdev);
	काष्ठा r5l_log *log;
	अक्षर b[BDEVNAME_SIZE];
	पूर्णांक ret;

	pr_debug("md/raid:%s: using device %s as journal\n",
		 mdname(conf->mddev), bdevname(rdev->bdev, b));

	अगर (PAGE_SIZE != 4096)
		वापस -EINVAL;

	/*
	 * The PAGE_SIZE must be big enough to hold 1 r5l_meta_block and
	 * raid_disks r5l_payload_data_parity.
	 *
	 * Write journal and cache करोes not work क्रम very big array
	 * (raid_disks > 203)
	 */
	अगर (माप(काष्ठा r5l_meta_block) +
	    ((माप(काष्ठा r5l_payload_data_parity) + माप(__le32)) *
	     conf->raid_disks) > PAGE_SIZE) अणु
		pr_err("md/raid:%s: write journal/cache doesn't work for array with %d disks\n",
		       mdname(conf->mddev), conf->raid_disks);
		वापस -EINVAL;
	पूर्ण

	log = kzalloc(माप(*log), GFP_KERNEL);
	अगर (!log)
		वापस -ENOMEM;
	log->rdev = rdev;

	log->need_cache_flush = test_bit(QUEUE_FLAG_WC, &q->queue_flags) != 0;

	log->uuid_checksum = crc32c_le(~0, rdev->mddev->uuid,
				       माप(rdev->mddev->uuid));

	mutex_init(&log->io_mutex);

	spin_lock_init(&log->io_list_lock);
	INIT_LIST_HEAD(&log->running_ios);
	INIT_LIST_HEAD(&log->io_end_ios);
	INIT_LIST_HEAD(&log->flushing_ios);
	INIT_LIST_HEAD(&log->finished_ios);
	bio_init(&log->flush_bio, शून्य, 0);

	log->io_kc = KMEM_CACHE(r5l_io_unit, 0);
	अगर (!log->io_kc)
		जाओ io_kc;

	ret = mempool_init_slab_pool(&log->io_pool, R5L_POOL_SIZE, log->io_kc);
	अगर (ret)
		जाओ io_pool;

	ret = bioset_init(&log->bs, R5L_POOL_SIZE, 0, BIOSET_NEED_BVECS);
	अगर (ret)
		जाओ io_bs;

	ret = mempool_init_page_pool(&log->meta_pool, R5L_POOL_SIZE, 0);
	अगर (ret)
		जाओ out_mempool;

	spin_lock_init(&log->tree_lock);
	INIT_RADIX_TREE(&log->big_stripe_tree, GFP_NOWAIT | __GFP_NOWARN);

	log->reclaim_thपढ़ो = md_रेजिस्टर_thपढ़ो(r5l_reclaim_thपढ़ो,
						 log->rdev->mddev, "reclaim");
	अगर (!log->reclaim_thपढ़ो)
		जाओ reclaim_thपढ़ो;
	log->reclaim_thपढ़ो->समयout = R5C_RECLAIM_WAKEUP_INTERVAL;

	init_रुकोqueue_head(&log->iounit_रुको);

	INIT_LIST_HEAD(&log->no_mem_stripes);

	INIT_LIST_HEAD(&log->no_space_stripes);
	spin_lock_init(&log->no_space_stripes_lock);

	INIT_WORK(&log->deferred_io_work, r5l_submit_io_async);
	INIT_WORK(&log->disable_ग_लिखोback_work, r5c_disable_ग_लिखोback_async);

	log->r5c_journal_mode = R5C_JOURNAL_MODE_WRITE_THROUGH;
	INIT_LIST_HEAD(&log->stripe_in_journal_list);
	spin_lock_init(&log->stripe_in_journal_lock);
	atomic_set(&log->stripe_in_journal_count, 0);

	rcu_assign_poपूर्णांकer(conf->log, log);

	set_bit(MD_HAS_JOURNAL, &conf->mddev->flags);
	वापस 0;

reclaim_thपढ़ो:
	mempool_निकास(&log->meta_pool);
out_mempool:
	bioset_निकास(&log->bs);
io_bs:
	mempool_निकास(&log->io_pool);
io_pool:
	kmem_cache_destroy(log->io_kc);
io_kc:
	kमुक्त(log);
	वापस -EINVAL;
पूर्ण

व्योम r5l_निकास_log(काष्ठा r5conf *conf)
अणु
	काष्ठा r5l_log *log = conf->log;

	conf->log = शून्य;
	synchronize_rcu();

	/* Ensure disable_ग_लिखोback_work wakes up and निकासs */
	wake_up(&conf->mddev->sb_रुको);
	flush_work(&log->disable_ग_लिखोback_work);
	md_unरेजिस्टर_thपढ़ो(&log->reclaim_thपढ़ो);
	mempool_निकास(&log->meta_pool);
	bioset_निकास(&log->bs);
	mempool_निकास(&log->io_pool);
	kmem_cache_destroy(log->io_kc);
	kमुक्त(log);
पूर्ण
