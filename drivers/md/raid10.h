<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RAID10_H
#घोषणा _RAID10_H

/* Note: raid10_info.rdev can be set to शून्य asynchronously by
 * raid10_हटाओ_disk.
 * There are three safe ways to access raid10_info.rdev.
 * 1/ when holding mddev->reconfig_mutex
 * 2/ when resync/recovery/reshape is known to be happening - i.e. in code
 *    that is called as part of perक्रमming resync/recovery/reshape.
 * 3/ जबतक holding rcu_पढ़ो_lock(), use rcu_dereference to get the poपूर्णांकer
 *    and अगर it is non-शून्य, increment rdev->nr_pending beक्रमe dropping the
 *    RCU lock.
 * When .rdev is set to शून्य, the nr_pending count checked again and अगर it has
 * been incremented, the poपूर्णांकer is put back in .rdev.
 */

काष्ठा raid10_info अणु
	काष्ठा md_rdev	*rdev, *replacement;
	sector_t	head_position;
	पूर्णांक		recovery_disabled;	/* matches
						 * mddev->recovery_disabled
						 * when we shouldn't try
						 * recovering this device.
						 */
पूर्ण;

काष्ठा r10conf अणु
	काष्ठा mddev		*mddev;
	काष्ठा raid10_info	*mirrors;
	काष्ठा raid10_info	*mirrors_new, *mirrors_old;
	spinlock_t		device_lock;

	/* geometry */
	काष्ठा geom अणु
		पूर्णांक		raid_disks;
		पूर्णांक		near_copies;  /* number of copies laid out
					       * raid0 style */
		पूर्णांक		far_copies;   /* number of copies laid out
					       * at large strides across drives
					       */
		पूर्णांक		far_offset;   /* far_copies are offset by 1
					       * stripe instead of many
					       */
		sector_t	stride;	      /* distance between far copies.
					       * This is size / far_copies unless
					       * far_offset, in which हाल it is
					       * 1 stripe.
					       */
		पूर्णांक             far_set_size; /* The number of devices in a set,
					       * where a 'set' are devices that
					       * contain far/offset copies of
					       * each other.
					       */
		पूर्णांक		chunk_shअगरt; /* shअगरt from chunks to sectors */
		sector_t	chunk_mask;
	पूर्ण prev, geo;
	पूर्णांक			copies;	      /* near_copies * far_copies.
					       * must be <= raid_disks
					       */

	sector_t		dev_sectors;  /* temp copy of
					       * mddev->dev_sectors */
	sector_t		reshape_progress;
	sector_t		reshape_safe;
	अचिन्हित दीर्घ		reshape_checkpoपूर्णांक;
	sector_t		offset_dअगरf;

	काष्ठा list_head	retry_list;
	/* A separate list of r1bio which just need raid_end_bio_io called.
	 * This mustn't happen क्रम ग_लिखोs which had any errors अगर the superblock
	 * needs to be written.
	 */
	काष्ठा list_head	bio_end_io_list;

	/* queue pending ग_लिखोs and submit them on unplug */
	काष्ठा bio_list		pending_bio_list;
	पूर्णांक			pending_count;

	spinlock_t		resync_lock;
	atomic_t		nr_pending;
	पूर्णांक			nr_रुकोing;
	पूर्णांक			nr_queued;
	पूर्णांक			barrier;
	पूर्णांक			array_मुक्तze_pending;
	sector_t		next_resync;
	पूर्णांक			fullsync;  /* set to 1 अगर a full sync is needed,
					    * (fresh device added).
					    * Cleared when a sync completes.
					    */
	पूर्णांक			have_replacement; /* There is at least one
						   * replacement device.
						   */
	रुको_queue_head_t	रुको_barrier;

	mempool_t		r10bio_pool;
	mempool_t		r10buf_pool;
	काष्ठा page		*पंचांगppage;
	काष्ठा bio_set		bio_split;

	/* When taking over an array from a dअगरferent personality, we store
	 * the new thपढ़ो here until we fully activate the array.
	 */
	काष्ठा md_thपढ़ो	*thपढ़ो;

	/*
	 * Keep track of cluster resync winकरोw to send to other nodes.
	 */
	sector_t		cluster_sync_low;
	sector_t		cluster_sync_high;
पूर्ण;

/*
 * this is our 'private' RAID10 bio.
 *
 * it contains inक्रमmation about what kind of IO operations were started
 * क्रम this RAID10 operation, and about their status:
 */

काष्ठा r10bio अणु
	atomic_t		reमुख्यing; /* 'have we finished' count,
					    * used from IRQ handlers
					    */
	sector_t		sector;	/* भव sector number */
	पूर्णांक			sectors;
	अचिन्हित दीर्घ		state;
	काष्ठा mddev		*mddev;
	/*
	 * original bio going to /dev/mdx
	 */
	काष्ठा bio		*master_bio;
	/*
	 * अगर the IO is in READ direction, then this is where we पढ़ो
	 */
	पूर्णांक			पढ़ो_slot;

	काष्ठा list_head	retry_list;
	/*
	 * अगर the IO is in WRITE direction, then multiple bios are used,
	 * one क्रम each copy.
	 * When resyncing we also use one क्रम each copy.
	 * When reस्थिरructing, we use 2 bios, one क्रम पढ़ो, one क्रम ग_लिखो.
	 * We choose the number when they are allocated.
	 * We someबार need an extra bio to ग_लिखो to the replacement.
	 */
	काष्ठा r10dev अणु
		काष्ठा bio	*bio;
		जोड़ अणु
			काष्ठा bio	*repl_bio; /* used क्रम resync and
						    * ग_लिखोs */
			काष्ठा md_rdev	*rdev;	   /* used क्रम पढ़ोs
						    * (पढ़ो_slot >= 0) */
		पूर्ण;
		sector_t	addr;
		पूर्णांक		devnum;
	पूर्ण devs[];
पूर्ण;

/* bits क्रम r10bio.state */
क्रमागत r10bio_state अणु
	R10BIO_Uptodate,
	R10BIO_IsSync,
	R10BIO_IsRecover,
	R10BIO_IsReshape,
	R10BIO_Degraded,
/* Set ReadError on bios that experience a पढ़ो error
 * so that raid10d knows what to करो with them.
 */
	R10BIO_ReadError,
/* If a ग_लिखो क्रम this request means we can clear some
 * known-bad-block records, we set this flag.
 */
	R10BIO_MadeGood,
	R10BIO_WriteError,
/* During a reshape we might be perक्रमming IO on the
 * 'previous' part of the array, in which हाल this
 * flag is set
 */
	R10BIO_Previous,
/* failfast devices did receive failfast requests. */
	R10BIO_FailFast,
	R10BIO_Discard,
पूर्ण;
#पूर्ण_अगर
