<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RAID5_H
#घोषणा _RAID5_H

#समावेश <linux/raid/xor.h>
#समावेश <linux/dmaengine.h>

/*
 *
 * Each stripe contains one buffer per device.  Each buffer can be in
 * one of a number of states stored in "flags".  Changes between
 * these states happen *almost* exclusively under the protection of the
 * STRIPE_ACTIVE flag.  Some very specअगरic changes can happen in bi_end_io, and
 * these are not रक्षित by STRIPE_ACTIVE.
 *
 * The flag bits that are used to represent these states are:
 *   R5_UPTODATE and R5_LOCKED
 *
 * State Empty == !UPTODATE, !LOCK
 *        We have no data, and there is no active request
 * State Want == !UPTODATE, LOCK
 *        A पढ़ो request is being submitted क्रम this block
 * State Dirty == UPTODATE, LOCK
 *        Some new data is in this buffer, and it is being written out
 * State Clean == UPTODATE, !LOCK
 *        We have valid data which is the same as on disc
 *
 * The possible state transitions are:
 *
 *  Empty -> Want   - on पढ़ो or ग_लिखो to get old data क्रम  parity calc
 *  Empty -> Dirty  - on compute_parity to satisfy ग_लिखो/sync request.
 *  Empty -> Clean  - on compute_block when computing a block क्रम failed drive
 *  Want  -> Empty  - on failed पढ़ो
 *  Want  -> Clean  - on successful completion of पढ़ो request
 *  Dirty -> Clean  - on successful completion of ग_लिखो request
 *  Dirty -> Clean  - on failed ग_लिखो
 *  Clean -> Dirty  - on compute_parity to satisfy ग_लिखो/sync (RECONSTRUCT or RMW)
 *
 * The Want->Empty, Want->Clean, Dirty->Clean, transitions
 * all happen in b_end_io at पूर्णांकerrupt समय.
 * Each sets the Uptodate bit beक्रमe releasing the Lock bit.
 * This leaves one multi-stage transition:
 *    Want->Dirty->Clean
 * This is safe because thinking that a Clean buffer is actually dirty
 * will at worst delay some action, and the stripe will be scheduled
 * क्रम attention after the transition is complete.
 *
 * There is one possibility that is not covered by these states.  That
 * is अगर one drive has failed and there is a spare being rebuilt.  We
 * can't distinguish between a clean block that has been generated
 * from parity calculations, and a clean block that has been
 * successfully written to the spare ( or to parity when resyncing).
 * To distinguish these states we have a stripe bit STRIPE_INSYNC that
 * is set whenever a ग_लिखो is scheduled to the spare, or to the parity
 * disc अगर there is no spare.  A sync request clears this bit, and
 * when we find it set with no buffers locked, we know the sync is
 * complete.
 *
 * Buffers क्रम the md device that arrive via make_request are attached
 * to the appropriate stripe in one of two lists linked on b_reqnext.
 * One list (bh_पढ़ो) क्रम पढ़ो requests, one (bh_ग_लिखो) क्रम ग_लिखो.
 * There should never be more than one buffer on the two lists
 * together, but we are not guaranteed of that so we allow क्रम more.
 *
 * If a buffer is on the पढ़ो list when the associated cache buffer is
 * Uptodate, the data is copied पूर्णांकo the पढ़ो buffer and it's b_end_io
 * routine is called.  This may happen in the end_request routine only
 * अगर the buffer has just successfully been पढ़ो.  end_request should
 * हटाओ the buffers from the list and then set the Uptodate bit on
 * the buffer.  Other thपढ़ोs may करो this only अगर they first check
 * that the Uptodate bit is set.  Once they have checked that they may
 * take buffers off the पढ़ो queue.
 *
 * When a buffer on the ग_लिखो list is committed क्रम ग_लिखो it is copied
 * पूर्णांकo the cache buffer, which is then marked dirty, and moved onto a
 * third list, the written list (bh_written).  Once both the parity
 * block and the cached buffer are successfully written, any buffer on
 * a written list can be वापसed with b_end_io.
 *
 * The ग_लिखो list and पढ़ो list both act as fअगरos.  The पढ़ो list,
 * ग_लिखो list and written list are रक्षित by the device_lock.
 * The device_lock is only क्रम list manipulations and will only be
 * held क्रम a very लघु समय.  It can be claimed from पूर्णांकerrupts.
 *
 *
 * Stripes in the stripe cache can be on one of two lists (or on
 * neither).  The "inactive_list" contains stripes which are not
 * currently being used क्रम any request.  They can मुक्तly be reused
 * क्रम another stripe.  The "handle_list" contains stripes that need
 * to be handled in some way.  Both of these are fअगरo queues.  Each
 * stripe is also (potentially) linked to a hash bucket in the hash
 * table so that it can be found by sector number.  Stripes that are
 * not hashed must be on the inactive_list, and will normally be at
 * the front.  All stripes start lअगरe this way.
 *
 * The inactive_list, handle_list and hash bucket lists are all रक्षित by the
 * device_lock.
 *  - stripes have a reference counter. If count==0, they are on a list.
 *  - If a stripe might need handling, STRIPE_HANDLE is set.
 *  - When refcount reaches zero, then अगर STRIPE_HANDLE it is put on
 *    handle_list अन्यथा inactive_list
 *
 * This, combined with the fact that STRIPE_HANDLE is only ever
 * cleared जबतक a stripe has a non-zero count means that अगर the
 * refcount is 0 and STRIPE_HANDLE is set, then it is on the
 * handle_list and अगर recount is 0 and STRIPE_HANDLE is not set, then
 * the stripe is on inactive_list.
 *
 * The possible transitions are:
 *  activate an unhashed/inactive stripe (get_active_stripe())
 *     lockdev check-hash unlink-stripe cnt++ clean-stripe hash-stripe unlockdev
 *  activate a hashed, possibly active stripe (get_active_stripe())
 *     lockdev check-hash अगर(!cnt++)unlink-stripe unlockdev
 *  attach a request to an active stripe (add_stripe_bh())
 *     lockdev attach-buffer unlockdev
 *  handle a stripe (handle_stripe())
 *     setSTRIPE_ACTIVE,  clrSTRIPE_HANDLE ...
 *		(lockdev check-buffers unlockdev) ..
 *		change-state ..
 *		record io/ops needed clearSTRIPE_ACTIVE schedule io/ops
 *  release an active stripe (release_stripe())
 *     lockdev अगर (!--cnt) अणु अगर  STRIPE_HANDLE, add to handle_list अन्यथा add to inactive-list पूर्ण unlockdev
 *
 * The refcount counts each thपढ़ो that have activated the stripe,
 * plus raid5d अगर it is handling it, plus one क्रम each active request
 * on a cached buffer, and plus one अगर the stripe is undergoing stripe
 * operations.
 *
 * The stripe operations are:
 * -copying data between the stripe cache and user application buffers
 * -computing blocks to save a disk access, or to recover a missing block
 * -updating the parity on a ग_लिखो operation (reस्थिरruct ग_लिखो and
 *  पढ़ो-modअगरy-ग_लिखो)
 * -checking parity correctness
 * -running i/o to disk
 * These operations are carried out by raid5_run_ops which uses the async_tx
 * api to (optionally) offload operations to dedicated hardware engines.
 * When requesting an operation handle_stripe sets the pending bit क्रम the
 * operation and increments the count.  raid5_run_ops is then run whenever
 * the count is non-zero.
 * There are some critical dependencies between the operations that prevent some
 * from being requested जबतक another is in flight.
 * 1/ Parity check operations destroy the in cache version of the parity block,
 *    so we prevent parity dependent operations like ग_लिखोs and compute_blocks
 *    from starting जबतक a check is in progress.  Some dma engines can perक्रमm
 *    the check without damaging the parity block, in these हालs the parity
 *    block is re-marked up to date (assuming the check was successful) and is
 *    not re-पढ़ो from disk.
 * 2/ When a ग_लिखो operation is requested we immediately lock the affected
 *    blocks, and mark them as not up to date.  This causes new पढ़ो requests
 *    to be held off, as well as parity checks and compute block operations.
 * 3/ Once a compute block operation has been requested handle_stripe treats
 *    that block as अगर it is up to date.  raid5_run_ops guaruntees that any
 *    operation that is dependent on the compute block result is initiated after
 *    the compute block completes.
 */

/*
 * Operations state - पूर्णांकermediate states that are visible outside of
 *   STRIPE_ACTIVE.
 * In general _idle indicates nothing is running, _run indicates a data
 * processing operation is active, and _result means the data processing result
 * is stable and can be acted upon.  For simple operations like biofill and
 * compute that only have an _idle and _run state they are indicated with
 * sh->state flags (STRIPE_BIOFILL_RUN and STRIPE_COMPUTE_RUN)
 */
/**
 * क्रमागत check_states - handles syncing / repairing a stripe
 * @check_state_idle - check operations are quiesced
 * @check_state_run - check operation is running
 * @check_state_result - set outside lock when check result is valid
 * @check_state_compute_run - check failed and we are repairing
 * @check_state_compute_result - set outside lock when compute result is valid
 */
क्रमागत check_states अणु
	check_state_idle = 0,
	check_state_run, /* xor parity check */
	check_state_run_q, /* q-parity check */
	check_state_run_pq, /* pq dual parity check */
	check_state_check_result,
	check_state_compute_run, /* parity repair */
	check_state_compute_result,
पूर्ण;

/**
 * क्रमागत reस्थिरruct_states - handles writing or expanding a stripe
 */
क्रमागत reस्थिरruct_states अणु
	reस्थिरruct_state_idle = 0,
	reस्थिरruct_state_prexor_drain_run,	/* prexor-ग_लिखो */
	reस्थिरruct_state_drain_run,		/* ग_लिखो */
	reस्थिरruct_state_run,			/* expand */
	reस्थिरruct_state_prexor_drain_result,
	reस्थिरruct_state_drain_result,
	reस्थिरruct_state_result,
पूर्ण;

#घोषणा DEFAULT_STRIPE_SIZE	4096
काष्ठा stripe_head अणु
	काष्ठा hlist_node	hash;
	काष्ठा list_head	lru;	      /* inactive_list or handle_list */
	काष्ठा llist_node	release_list;
	काष्ठा r5conf		*raid_conf;
	लघु			generation;	/* increments with every
						 * reshape */
	sector_t		sector;		/* sector of this row */
	लघु			pd_idx;		/* parity disk index */
	लघु			qd_idx;		/* 'Q' disk index क्रम raid6 */
	लघु			ddf_layout;/* use DDF ordering to calculate Q */
	लघु			hash_lock_index;
	अचिन्हित दीर्घ		state;		/* state flags */
	atomic_t		count;	      /* nr of active thपढ़ो/requests */
	पूर्णांक			bm_seq;	/* sequence number क्रम biपंचांगap flushes */
	पूर्णांक			disks;		/* disks in stripe */
	पूर्णांक			overग_लिखो_disks; /* total overग_लिखो disks in stripe,
						  * this is only checked when stripe
						  * has STRIPE_BATCH_READY
						  */
	क्रमागत check_states	check_state;
	क्रमागत reस्थिरruct_states reस्थिरruct_state;
	spinlock_t		stripe_lock;
	पूर्णांक			cpu;
	काष्ठा r5worker_group	*group;

	काष्ठा stripe_head	*batch_head; /* रक्षित by stripe lock */
	spinlock_t		batch_lock; /* only header's lock is useful */
	काष्ठा list_head	batch_list; /* रक्षित by head's batch lock*/

	जोड़ अणु
		काष्ठा r5l_io_unit	*log_io;
		काष्ठा ppl_io_unit	*ppl_io;
	पूर्ण;

	काष्ठा list_head	log_list;
	sector_t		log_start; /* first meta block on the journal */
	काष्ठा list_head	r5c; /* क्रम r5c_cache->stripe_in_journal */

	काष्ठा page		*ppl_page; /* partial parity of this stripe */
	/**
	 * काष्ठा stripe_operations
	 * @target - STRIPE_OP_COMPUTE_BLK target
	 * @target2 - 2nd compute target in the raid6 हाल
	 * @zero_sum_result - P and Q verअगरication flags
	 * @request - async service request flags क्रम raid_run_ops
	 */
	काष्ठा stripe_operations अणु
		पूर्णांक 		     target, target2;
		क्रमागत sum_check_flags zero_sum_result;
	पूर्ण ops;

#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
	/* These pages will be used by bios in dev[i] */
	काष्ठा page	**pages;
	पूर्णांक	nr_pages;	/* page array size */
	पूर्णांक	stripes_per_page;
#पूर्ण_अगर
	काष्ठा r5dev अणु
		/* rreq and rvec are used क्रम the replacement device when
		 * writing data to both devices.
		 */
		काष्ठा bio	req, rreq;
		काष्ठा bio_vec	vec, rvec;
		काष्ठा page	*page, *orig_page;
		अचिन्हित पूर्णांक    offset;     /* offset of the page */
		काष्ठा bio	*toपढ़ो, *पढ़ो, *toग_लिखो, *written;
		sector_t	sector;			/* sector of this page */
		अचिन्हित दीर्घ	flags;
		u32		log_checksum;
		अचिन्हित लघु	ग_लिखो_hपूर्णांक;
	पूर्ण dev[1]; /* allocated with extra space depending of RAID geometry */
पूर्ण;

/* stripe_head_state - collects and tracks the dynamic state of a stripe_head
 *     क्रम handle_stripe.
 */
काष्ठा stripe_head_state अणु
	/* 'syncing' means that we need to पढ़ो all devices, either
	 * to check/correct parity, or to reस्थिरruct a missing device.
	 * 'replacing' means we are replacing one or more drives and
	 * the source is valid at this poपूर्णांक so we करोn't need to
	 * पढ़ो all devices, just the replacement tarमाला_लो.
	 */
	पूर्णांक syncing, expanding, expanded, replacing;
	पूर्णांक locked, uptodate, to_पढ़ो, to_ग_लिखो, failed, written;
	पूर्णांक to_fill, compute, req_compute, non_overग_लिखो;
	पूर्णांक injournal, just_cached;
	पूर्णांक failed_num[2];
	पूर्णांक p_failed, q_failed;
	पूर्णांक dec_preपढ़ो_active;
	अचिन्हित दीर्घ ops_request;

	काष्ठा md_rdev *blocked_rdev;
	पूर्णांक handle_bad_blocks;
	पूर्णांक log_failed;
	पूर्णांक रुकोing_extra_page;
पूर्ण;

/* Flags क्रम काष्ठा r5dev.flags */
क्रमागत r5dev_flags अणु
	R5_UPTODATE,	/* page contains current data */
	R5_LOCKED,	/* IO has been submitted on "req" */
	R5_DOUBLE_LOCKED,/* Cannot clear R5_LOCKED until 2 ग_लिखोs complete */
	R5_OVERWRITE,	/* toग_लिखो covers whole page */
/* and some that are पूर्णांकernal to handle_stripe */
	R5_Insync,	/* rdev && rdev->in_sync at start */
	R5_Wantपढ़ो,	/* want to schedule a पढ़ो */
	R5_Wantग_लिखो,
	R5_Overlap,	/* There is a pending overlapping request
			 * on this block */
	R5_ReadNoMerge, /* prevent bio from merging in block-layer */
	R5_ReadError,	/* seen a पढ़ो error here recently */
	R5_ReWrite,	/* have tried to over-ग_लिखो the पढ़ोerror */

	R5_Expanded,	/* This block now has post-expand data */
	R5_Wantcompute,	/* compute_block in progress treat as
			 * uptodate
			 */
	R5_Wantfill,	/* dev->toपढ़ो contains a bio that needs
			 * filling
			 */
	R5_Wantdrain,	/* dev->toग_लिखो needs to be drained */
	R5_WantFUA,	/* Write should be FUA */
	R5_SyncIO,	/* The IO is sync */
	R5_WriteError,	/* got a ग_लिखो error - need to record it */
	R5_MadeGood,	/* A bad block has been fixed by writing to it */
	R5_ReadRepl,	/* Will/did पढ़ो from replacement rather than orig */
	R5_MadeGoodRepl,/* A bad block on the replacement device has been
			 * fixed by writing to it */
	R5_NeedReplace,	/* This device has a replacement which is not
			 * up-to-date at this stripe. */
	R5_WantReplace, /* We need to update the replacement, we have पढ़ो
			 * data in, and now is a good समय to ग_लिखो it out.
			 */
	R5_Discard,	/* Discard the stripe */
	R5_SkipCopy,	/* Don't copy data from bio to stripe cache */
	R5_InJournal,	/* data being written is in the journal device.
			 * अगर R5_InJournal is set क्रम parity pd_idx, all the
			 * data and parity being written are in the journal
			 * device
			 */
	R5_OrigPageUPTDODATE,	/* with ग_लिखो back cache, we पढ़ो old data पूर्णांकo
				 * dev->orig_page क्रम prexor. When this flag is
				 * set, orig_page contains latest data in the
				 * raid disk.
				 */
पूर्ण;

/*
 * Stripe state
 */
क्रमागत अणु
	STRIPE_ACTIVE,
	STRIPE_HANDLE,
	STRIPE_SYNC_REQUESTED,
	STRIPE_SYNCING,
	STRIPE_INSYNC,
	STRIPE_REPLACED,
	STRIPE_PREREAD_ACTIVE,
	STRIPE_DELAYED,
	STRIPE_DEGRADED,
	STRIPE_BIT_DELAY,
	STRIPE_EXPANDING,
	STRIPE_EXPAND_SOURCE,
	STRIPE_EXPAND_READY,
	STRIPE_IO_STARTED,	/* करो not count towards 'bypass_count' */
	STRIPE_FULL_WRITE,	/* all blocks are set to be overwritten */
	STRIPE_BIOFILL_RUN,
	STRIPE_COMPUTE_RUN,
	STRIPE_ON_UNPLUG_LIST,
	STRIPE_DISCARD,
	STRIPE_ON_RELEASE_LIST,
	STRIPE_BATCH_READY,
	STRIPE_BATCH_ERR,
	STRIPE_BITMAP_PENDING,	/* Being added to biपंचांगap, करोn't add
				 * to batch yet.
				 */
	STRIPE_LOG_TRAPPED,	/* trapped पूर्णांकo log (see raid5-cache.c)
				 * this bit is used in two scenarios:
				 *
				 * 1. ग_लिखो-out phase
				 *  set in first entry of r5l_ग_लिखो_stripe
				 *  clear in second entry of r5l_ग_लिखो_stripe
				 *  used to bypass logic in handle_stripe
				 *
				 * 2. caching phase
				 *  set in r5c_try_caching_ग_लिखो()
				 *  clear when journal ग_लिखो is करोne
				 *  used to initiate r5c_cache_data()
				 *  also used to bypass logic in handle_stripe
				 */
	STRIPE_R5C_CACHING,	/* the stripe is in caching phase
				 * see more detail in the raid5-cache.c
				 */
	STRIPE_R5C_PARTIAL_STRIPE,	/* in r5c cache (to-be/being handled or
					 * in conf->r5c_partial_stripe_list)
					 */
	STRIPE_R5C_FULL_STRIPE,	/* in r5c cache (to-be/being handled or
				 * in conf->r5c_full_stripe_list)
				 */
	STRIPE_R5C_PREFLUSH,	/* need to flush journal device */
पूर्ण;

#घोषणा STRIPE_EXPAND_SYNC_FLAGS \
	((1 << STRIPE_EXPAND_SOURCE) |\
	(1 << STRIPE_EXPAND_READY) |\
	(1 << STRIPE_EXPANDING) |\
	(1 << STRIPE_SYNC_REQUESTED))
/*
 * Operation request flags
 */
क्रमागत अणु
	STRIPE_OP_BIOFILL,
	STRIPE_OP_COMPUTE_BLK,
	STRIPE_OP_PREXOR,
	STRIPE_OP_BIODRAIN,
	STRIPE_OP_RECONSTRUCT,
	STRIPE_OP_CHECK,
	STRIPE_OP_PARTIAL_PARITY,
पूर्ण;

/*
 * RAID parity calculation preferences
 */
क्रमागत अणु
	PARITY_DISABLE_RMW = 0,
	PARITY_ENABLE_RMW,
	PARITY_PREFER_RMW,
पूर्ण;

/*
 * Pages requested from set_syndrome_sources()
 */
क्रमागत अणु
	SYNDROME_SRC_ALL,
	SYNDROME_SRC_WANT_DRAIN,
	SYNDROME_SRC_WRITTEN,
पूर्ण;
/*
 * Plugging:
 *
 * To improve ग_लिखो throughput, we need to delay the handling of some
 * stripes until there has been a chance that several ग_लिखो requests
 * क्रम the one stripe have all been collected.
 * In particular, any ग_लिखो request that would require pre-पढ़ोing
 * is put on a "delayed" queue until there are no stripes currently
 * in a pre-पढ़ो phase.  Further, अगर the "delayed" queue is empty when
 * a stripe is put on it then we "plug" the queue and करो not process it
 * until an unplug call is made. (the unplug_io_fn() is called).
 *
 * When preपढ़ो is initiated on a stripe, we set PREREAD_ACTIVE and add
 * it to the count of preपढ़ोing stripes.
 * When ग_लिखो is initiated, or the stripe refcnt == 0 (just in हाल) we
 * clear the PREREAD_ACTIVE flag and decrement the count
 * Whenever the 'handle' queue is empty and the device is not plugged, we
 * move any strips from delayed to handle and clear the DELAYED flag and set
 * PREREAD_ACTIVE.
 * In stripe_handle, अगर we find pre-पढ़ोing is necessary, we करो it अगर
 * PREREAD_ACTIVE is set, अन्यथा we set DELAYED which will send it to the delayed queue.
 * HANDLE माला_लो cleared अगर stripe_handle leaves nothing locked.
 */

/* Note: disk_info.rdev can be set to शून्य asynchronously by raid5_हटाओ_disk.
 * There are three safe ways to access disk_info.rdev.
 * 1/ when holding mddev->reconfig_mutex
 * 2/ when resync/recovery/reshape is known to be happening - i.e. in code that
 *    is called as part of perक्रमming resync/recovery/reshape.
 * 3/ जबतक holding rcu_पढ़ो_lock(), use rcu_dereference to get the poपूर्णांकer
 *    and अगर it is non-शून्य, increment rdev->nr_pending beक्रमe dropping the RCU
 *    lock.
 * When .rdev is set to शून्य, the nr_pending count checked again and अगर
 * it has been incremented, the poपूर्णांकer is put back in .rdev.
 */

काष्ठा disk_info अणु
	काष्ठा md_rdev	*rdev, *replacement;
	काष्ठा page	*extra_page; /* extra page to use in prexor */
पूर्ण;

/*
 * Stripe cache
 */

#घोषणा NR_STRIPES		256

#अगर PAGE_SIZE == DEFAULT_STRIPE_SIZE
#घोषणा STRIPE_SIZE		PAGE_SIZE
#घोषणा STRIPE_SHIFT		(PAGE_SHIFT - 9)
#घोषणा STRIPE_SECTORS		(STRIPE_SIZE>>9)
#पूर्ण_अगर

#घोषणा	IO_THRESHOLD		1
#घोषणा BYPASS_THRESHOLD	1
#घोषणा NR_HASH			(PAGE_SIZE / माप(काष्ठा hlist_head))
#घोषणा HASH_MASK		(NR_HASH - 1)
#घोषणा MAX_STRIPE_BATCH	8

/* NOTE NR_STRIPE_HASH_LOCKS must reमुख्य below 64.
 * This is because we someबार take all the spinlocks
 * and creating that much locking depth can cause
 * problems.
 */
#घोषणा NR_STRIPE_HASH_LOCKS 8
#घोषणा STRIPE_HASH_LOCKS_MASK (NR_STRIPE_HASH_LOCKS - 1)

काष्ठा r5worker अणु
	काष्ठा work_काष्ठा work;
	काष्ठा r5worker_group *group;
	काष्ठा list_head temp_inactive_list[NR_STRIPE_HASH_LOCKS];
	bool working;
पूर्ण;

काष्ठा r5worker_group अणु
	काष्ठा list_head handle_list;
	काष्ठा list_head loprio_list;
	काष्ठा r5conf *conf;
	काष्ठा r5worker *workers;
	पूर्णांक stripes_cnt;
पूर्ण;

/*
 * r5c journal modes of the array: ग_लिखो-back or ग_लिखो-through.
 * ग_लिखो-through mode has identical behavior as existing log only
 * implementation.
 */
क्रमागत r5c_journal_mode अणु
	R5C_JOURNAL_MODE_WRITE_THROUGH = 0,
	R5C_JOURNAL_MODE_WRITE_BACK = 1,
पूर्ण;

क्रमागत r5_cache_state अणु
	R5_INACTIVE_BLOCKED,	/* release of inactive stripes blocked,
				 * रुकोing क्रम 25% to be मुक्त
				 */
	R5_ALLOC_MORE,		/* It might help to allocate another
				 * stripe.
				 */
	R5_DID_ALLOC,		/* A stripe was allocated, करोn't allocate
				 * more until at least one has been
				 * released.  This aव्योमs flooding
				 * the cache.
				 */
	R5C_LOG_TIGHT,		/* log device space tight, need to
				 * prioritize stripes at last_checkpoपूर्णांक
				 */
	R5C_LOG_CRITICAL,	/* log device is running out of space,
				 * only process stripes that are alपढ़ोy
				 * occupying the log
				 */
	R5C_EXTRA_PAGE_IN_USE,	/* a stripe is using disk_info.extra_page
				 * क्रम prexor
				 */
पूर्ण;

#घोषणा PENDING_IO_MAX 512
#घोषणा PENDING_IO_ONE_FLUSH 128
काष्ठा r5pending_data अणु
	काष्ठा list_head sibling;
	sector_t sector; /* stripe sector */
	काष्ठा bio_list bios;
पूर्ण;

काष्ठा r5conf अणु
	काष्ठा hlist_head	*stripe_hashtbl;
	/* only protect corresponding hash list and inactive_list */
	spinlock_t		hash_locks[NR_STRIPE_HASH_LOCKS];
	काष्ठा mddev		*mddev;
	पूर्णांक			chunk_sectors;
	पूर्णांक			level, algorithm, rmw_level;
	पूर्णांक			max_degraded;
	पूर्णांक			raid_disks;
	पूर्णांक			max_nr_stripes;
	पूर्णांक			min_nr_stripes;
#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
	अचिन्हित दीर्घ	stripe_size;
	अचिन्हित पूर्णांक	stripe_shअगरt;
	अचिन्हित दीर्घ	stripe_sectors;
#पूर्ण_अगर

	/* reshape_progress is the leading edge of a 'reshape'
	 * It has value MaxSector when no reshape is happening
	 * If delta_disks < 0, it is the last sector we started work on,
	 * अन्यथा is it the next sector to work on.
	 */
	sector_t		reshape_progress;
	/* reshape_safe is the trailing edge of a reshape.  We know that
	 * beक्रमe (or after) this address, all reshape has completed.
	 */
	sector_t		reshape_safe;
	पूर्णांक			previous_raid_disks;
	पूर्णांक			prev_chunk_sectors;
	पूर्णांक			prev_algo;
	लघु			generation; /* increments with every reshape */
	seqcount_spinlock_t	gen_lock;	/* lock against generation changes */
	अचिन्हित दीर्घ		reshape_checkpoपूर्णांक; /* Time we last updated
						     * metadata */
	दीर्घ दीर्घ		min_offset_dअगरf; /* minimum dअगरference between
						  * data_offset and
						  * new_data_offset across all
						  * devices.  May be negative,
						  * but is बंदst to zero.
						  */

	काष्ठा list_head	handle_list; /* stripes needing handling */
	काष्ठा list_head	loprio_list; /* low priority stripes */
	काष्ठा list_head	hold_list; /* preपढ़ो पढ़ोy stripes */
	काष्ठा list_head	delayed_list; /* stripes that have plugged requests */
	काष्ठा list_head	biपंचांगap_list; /* stripes delaying aरुकोing biपंचांगap update */
	काष्ठा bio		*retry_पढ़ो_aligned; /* currently retrying aligned bios   */
	अचिन्हित पूर्णांक		retry_पढ़ो_offset; /* sector offset पूर्णांकo retry_पढ़ो_aligned */
	काष्ठा bio		*retry_पढ़ो_aligned_list; /* aligned bios retry list  */
	atomic_t		preपढ़ो_active_stripes; /* stripes with scheduled io */
	atomic_t		active_aligned_पढ़ोs;
	atomic_t		pending_full_ग_लिखोs; /* full ग_लिखो backlog */
	पूर्णांक			bypass_count; /* bypassed preपढ़ोs */
	पूर्णांक			bypass_threshold; /* preपढ़ो nice */
	पूर्णांक			skip_copy; /* Don't copy data from bio to stripe cache */
	काष्ठा list_head	*last_hold; /* detect hold_list promotions */

	atomic_t		reshape_stripes; /* stripes with pending ग_लिखोs क्रम reshape */
	/* unक्रमtunately we need two cache names as we temporarily have
	 * two caches.
	 */
	पूर्णांक			active_name;
	अक्षर			cache_name[2][32];
	काष्ठा kmem_cache	*slab_cache; /* क्रम allocating stripes */
	काष्ठा mutex		cache_size_mutex; /* Protect changes to cache size */

	पूर्णांक			seq_flush, seq_ग_लिखो;
	पूर्णांक			quiesce;

	पूर्णांक			fullsync;  /* set to 1 अगर a full sync is needed,
					    * (fresh device added).
					    * Cleared when a sync completes.
					    */
	पूर्णांक			recovery_disabled;
	/* per cpu variables */
	काष्ठा raid5_percpu अणु
		काष्ठा page	*spare_page; /* Used when checking P/Q in raid6 */
		व्योम		*scribble;  /* space क्रम स्थिरructing buffer
					     * lists and perक्रमming address
					     * conversions
					     */
		पूर्णांक scribble_obj_size;
	पूर्ण __percpu *percpu;
	पूर्णांक scribble_disks;
	पूर्णांक scribble_sectors;
	काष्ठा hlist_node node;

	/*
	 * Free stripes pool
	 */
	atomic_t		active_stripes;
	काष्ठा list_head	inactive_list[NR_STRIPE_HASH_LOCKS];

	atomic_t		r5c_cached_full_stripes;
	काष्ठा list_head	r5c_full_stripe_list;
	atomic_t		r5c_cached_partial_stripes;
	काष्ठा list_head	r5c_partial_stripe_list;
	atomic_t		r5c_flushing_full_stripes;
	atomic_t		r5c_flushing_partial_stripes;

	atomic_t		empty_inactive_list_nr;
	काष्ठा llist_head	released_stripes;
	रुको_queue_head_t	रुको_क्रम_quiescent;
	रुको_queue_head_t	रुको_क्रम_stripe;
	रुको_queue_head_t	रुको_क्रम_overlap;
	अचिन्हित दीर्घ		cache_state;
	काष्ठा shrinker		shrinker;
	पूर्णांक			pool_size; /* number of disks in stripeheads in pool */
	spinlock_t		device_lock;
	काष्ठा disk_info	*disks;
	काष्ठा bio_set		bio_split;

	/* When taking over an array from a dअगरferent personality, we store
	 * the new thपढ़ो here until we fully activate the array.
	 */
	काष्ठा md_thपढ़ो	*thपढ़ो;
	काष्ठा list_head	temp_inactive_list[NR_STRIPE_HASH_LOCKS];
	काष्ठा r5worker_group	*worker_groups;
	पूर्णांक			group_cnt;
	पूर्णांक			worker_cnt_per_group;
	काष्ठा r5l_log		*log;
	व्योम			*log_निजी;

	spinlock_t		pending_bios_lock;
	bool			batch_bio_dispatch;
	काष्ठा r5pending_data	*pending_data;
	काष्ठा list_head	मुक्त_list;
	काष्ठा list_head	pending_list;
	पूर्णांक			pending_data_cnt;
	काष्ठा r5pending_data	*next_pending_data;
पूर्ण;

#अगर PAGE_SIZE == DEFAULT_STRIPE_SIZE
#घोषणा RAID5_STRIPE_SIZE(conf)	STRIPE_SIZE
#घोषणा RAID5_STRIPE_SHIFT(conf)	STRIPE_SHIFT
#घोषणा RAID5_STRIPE_SECTORS(conf)	STRIPE_SECTORS
#अन्यथा
#घोषणा RAID5_STRIPE_SIZE(conf)	((conf)->stripe_size)
#घोषणा RAID5_STRIPE_SHIFT(conf)	((conf)->stripe_shअगरt)
#घोषणा RAID5_STRIPE_SECTORS(conf)	((conf)->stripe_sectors)
#पूर्ण_अगर

/* bio's attached to a stripe+device क्रम I/O are linked together in bi_sector
 * order without overlap.  There may be several bio's per stripe+device, and
 * a bio could span several devices.
 * When walking this list क्रम a particular stripe+device, we must never proceed
 * beyond a bio that extends past this device, as the next bio might no दीर्घer
 * be valid.
 * This function is used to determine the 'next' bio in the list, given the
 * sector of the current stripe+device
 */
अटल अंतरभूत काष्ठा bio *r5_next_bio(काष्ठा r5conf *conf, काष्ठा bio *bio, sector_t sector)
अणु
	अगर (bio_end_sector(bio) < sector + RAID5_STRIPE_SECTORS(conf))
		वापस bio->bi_next;
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * Our supported algorithms
 */
#घोषणा ALGORITHM_LEFT_ASYMMETRIC	0 /* Rotating Parity N with Data Restart */
#घोषणा ALGORITHM_RIGHT_ASYMMETRIC	1 /* Rotating Parity 0 with Data Restart */
#घोषणा ALGORITHM_LEFT_SYMMETRIC	2 /* Rotating Parity N with Data Continuation */
#घोषणा ALGORITHM_RIGHT_SYMMETRIC	3 /* Rotating Parity 0 with Data Continuation */

/* Define non-rotating (raid4) algorithms.  These allow
 * conversion of raid4 to raid5.
 */
#घोषणा ALGORITHM_PARITY_0		4 /* P or P,Q are initial devices */
#घोषणा ALGORITHM_PARITY_N		5 /* P or P,Q are final devices. */

/* DDF RAID6 layouts dअगरfer from md/raid6 layouts in two ways.
 * Firstly, the exact positioning of the parity block is slightly
 * dअगरferent between the 'LEFT_*' modes of md and the "_N_*" modes
 * of DDF.
 * Secondly, or order of datablocks over which the Q syndrome is computed
 * is dअगरferent.
 * Consequently we have dअगरferent layouts क्रम DDF/raid6 than md/raid6.
 * These layouts are from the DDFv1.2 spec.
 * Interestingly DDFv1.2-Errata-A करोes not specअगरy N_CONTINUE but
 * leaves RLQ=3 as 'Vendor Specific'
 */

#घोषणा ALGORITHM_ROTATING_ZERO_RESTART	8 /* DDF PRL=6 RLQ=1 */
#घोषणा ALGORITHM_ROTATING_N_RESTART	9 /* DDF PRL=6 RLQ=2 */
#घोषणा ALGORITHM_ROTATING_N_CONTINUE	10 /*DDF PRL=6 RLQ=3 */

/* For every RAID5 algorithm we define a RAID6 algorithm
 * with exactly the same layout क्रम data and parity, and
 * with the Q block always on the last device (N-1).
 * This allows trivial conversion from RAID5 to RAID6
 */
#घोषणा ALGORITHM_LEFT_ASYMMETRIC_6	16
#घोषणा ALGORITHM_RIGHT_ASYMMETRIC_6	17
#घोषणा ALGORITHM_LEFT_SYMMETRIC_6	18
#घोषणा ALGORITHM_RIGHT_SYMMETRIC_6	19
#घोषणा ALGORITHM_PARITY_0_6		20
#घोषणा ALGORITHM_PARITY_N_6		ALGORITHM_PARITY_N

अटल अंतरभूत पूर्णांक algorithm_valid_raid5(पूर्णांक layout)
अणु
	वापस (layout >= 0) &&
		(layout <= 5);
पूर्ण
अटल अंतरभूत पूर्णांक algorithm_valid_raid6(पूर्णांक layout)
अणु
	वापस (layout >= 0 && layout <= 5)
		||
		(layout >= 8 && layout <= 10)
		||
		(layout >= 16 && layout <= 20);
पूर्ण

अटल अंतरभूत पूर्णांक algorithm_is_DDF(पूर्णांक layout)
अणु
	वापस layout >= 8 && layout <= 10;
पूर्ण

#अगर PAGE_SIZE != DEFAULT_STRIPE_SIZE
/*
 * Return offset of the corresponding page क्रम r5dev.
 */
अटल अंतरभूत पूर्णांक raid5_get_page_offset(काष्ठा stripe_head *sh, पूर्णांक disk_idx)
अणु
	वापस (disk_idx % sh->stripes_per_page) * RAID5_STRIPE_SIZE(sh->raid_conf);
पूर्ण

/*
 * Return corresponding page address क्रम r5dev.
 */
अटल अंतरभूत काष्ठा page *
raid5_get_dev_page(काष्ठा stripe_head *sh, पूर्णांक disk_idx)
अणु
	वापस sh->pages[disk_idx / sh->stripes_per_page];
पूर्ण
#पूर्ण_अगर

बाह्य व्योम md_raid5_kick_device(काष्ठा r5conf *conf);
बाह्य पूर्णांक raid5_set_cache_size(काष्ठा mddev *mddev, पूर्णांक size);
बाह्य sector_t raid5_compute_blocknr(काष्ठा stripe_head *sh, पूर्णांक i, पूर्णांक previous);
बाह्य व्योम raid5_release_stripe(काष्ठा stripe_head *sh);
बाह्य sector_t raid5_compute_sector(काष्ठा r5conf *conf, sector_t r_sector,
				     पूर्णांक previous, पूर्णांक *dd_idx,
				     काष्ठा stripe_head *sh);
बाह्य काष्ठा stripe_head *
raid5_get_active_stripe(काष्ठा r5conf *conf, sector_t sector,
			पूर्णांक previous, पूर्णांक noblock, पूर्णांक noquiesce);
बाह्य पूर्णांक raid5_calc_degraded(काष्ठा r5conf *conf);
बाह्य पूर्णांक r5c_journal_mode_set(काष्ठा mddev *mddev, पूर्णांक journal_mode);
#पूर्ण_अगर
