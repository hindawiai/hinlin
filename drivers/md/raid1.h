<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RAID1_H
#घोषणा _RAID1_H

/*
 * each barrier unit size is 64MB fow now
 * note: it must be larger than RESYNC_DEPTH
 */
#घोषणा BARRIER_UNIT_SECTOR_BITS	17
#घोषणा BARRIER_UNIT_SECTOR_SIZE	(1<<17)
/*
 * In काष्ठा r1conf, the following members are related to I/O barrier
 * buckets,
 *	atomic_t	*nr_pending;
 *	atomic_t	*nr_रुकोing;
 *	atomic_t	*nr_queued;
 *	atomic_t	*barrier;
 * Each of them poपूर्णांकs to array of atomic_t variables, each array is
 * deचिन्हित to have BARRIER_BUCKETS_NR elements and occupy a single
 * memory page. The data width of atomic_t variables is 4 bytes, equal
 * to 1<<(ilog2(माप(atomic_t))), BARRIER_BUCKETS_NR_BITS is defined
 * as (PAGE_SHIFT - ilog2(माप(पूर्णांक))) to make sure an array of
 * atomic_t variables with BARRIER_BUCKETS_NR elements just exactly
 * occupies a single memory page.
 */
#घोषणा BARRIER_BUCKETS_NR_BITS		(PAGE_SHIFT - ilog2(माप(atomic_t)))
#घोषणा BARRIER_BUCKETS_NR		(1<<BARRIER_BUCKETS_NR_BITS)

/* Note: raid1_info.rdev can be set to शून्य asynchronously by raid1_हटाओ_disk.
 * There are three safe ways to access raid1_info.rdev.
 * 1/ when holding mddev->reconfig_mutex
 * 2/ when resync/recovery is known to be happening - i.e. in code that is
 *    called as part of perक्रमming resync/recovery.
 * 3/ जबतक holding rcu_पढ़ो_lock(), use rcu_dereference to get the poपूर्णांकer
 *    and अगर it is non-शून्य, increment rdev->nr_pending beक्रमe dropping the
 *    RCU lock.
 * When .rdev is set to शून्य, the nr_pending count checked again and अगर it has
 * been incremented, the poपूर्णांकer is put back in .rdev.
 */

काष्ठा raid1_info अणु
	काष्ठा md_rdev	*rdev;
	sector_t	head_position;

	/* When choose the best device क्रम a पढ़ो (पढ़ो_balance())
	 * we try to keep sequential पढ़ोs one the same device
	 */
	sector_t	next_seq_sect;
	sector_t	seq_start;
पूर्ण;

/*
 * memory pools need a poपूर्णांकer to the mddev, so they can क्रमce an unplug
 * when memory is tight, and a count of the number of drives that the
 * pool was allocated क्रम, so they know how much to allocate and मुक्त.
 * mddev->raid_disks cannot be used, as it can change जबतक a pool is active
 * These two datums are stored in a kदो_स्मृतिed काष्ठा.
 * The 'raid_disks' here is twice the raid_disks in r1conf.
 * This allows space क्रम each 'real' device can have a replacement in the
 * second half of the array.
 */

काष्ठा pool_info अणु
	काष्ठा mddev *mddev;
	पूर्णांक	raid_disks;
पूर्ण;

काष्ठा r1conf अणु
	काष्ठा mddev		*mddev;
	काष्ठा raid1_info	*mirrors;	/* twice 'raid_disks' to
						 * allow क्रम replacements.
						 */
	पूर्णांक			raid_disks;

	spinlock_t		device_lock;

	/* list of 'struct r1bio' that need to be processed by raid1d,
	 * whether to retry a पढ़ो, ग_लिखोout a resync or recovery
	 * block, or anything अन्यथा.
	 */
	काष्ठा list_head	retry_list;
	/* A separate list of r1bio which just need raid_end_bio_io called.
	 * This mustn't happen क्रम ग_लिखोs which had any errors अगर the superblock
	 * needs to be written.
	 */
	काष्ठा list_head	bio_end_io_list;

	/* queue pending ग_लिखोs to be submitted on unplug */
	काष्ठा bio_list		pending_bio_list;
	पूर्णांक			pending_count;

	/* क्रम use when syncing mirrors:
	 * We करोn't allow both normal IO and resync/recovery IO at
	 * the same समय - resync/recovery can only happen when there
	 * is no other IO.  So when either is active, the other has to रुको.
	 * See more details description in raid1.c near उठाओ_barrier().
	 */
	रुको_queue_head_t	रुको_barrier;
	spinlock_t		resync_lock;
	atomic_t		nr_sync_pending;
	atomic_t		*nr_pending;
	atomic_t		*nr_रुकोing;
	atomic_t		*nr_queued;
	atomic_t		*barrier;
	पूर्णांक			array_frozen;

	/* Set to 1 अगर a full sync is needed, (fresh device added).
	 * Cleared when a sync completes.
	 */
	पूर्णांक			fullsync;

	/* When the same as mddev->recovery_disabled we करोn't allow
	 * recovery to be attempted as we expect a पढ़ो error.
	 */
	पूर्णांक			recovery_disabled;

	/* poolinfo contains inक्रमmation about the content of the
	 * mempools - it changes when the array grows or shrinks
	 */
	काष्ठा pool_info	*poolinfo;
	mempool_t		r1bio_pool;
	mempool_t		r1buf_pool;

	काष्ठा bio_set		bio_split;

	/* temporary buffer to synchronous IO when attempting to repair
	 * a पढ़ो error.
	 */
	काष्ठा page		*पंचांगppage;

	/* When taking over an array from a dअगरferent personality, we store
	 * the new thपढ़ो here until we fully activate the array.
	 */
	काष्ठा md_thपढ़ो	*thपढ़ो;

	/* Keep track of cluster resync winकरोw to send to other
	 * nodes.
	 */
	sector_t		cluster_sync_low;
	sector_t		cluster_sync_high;

पूर्ण;

/*
 * this is our 'private' RAID1 bio.
 *
 * it contains inक्रमmation about what kind of IO operations were started
 * क्रम this RAID1 operation, and about their status:
 */

काष्ठा r1bio अणु
	atomic_t		reमुख्यing; /* 'have we finished' count,
					    * used from IRQ handlers
					    */
	atomic_t		behind_reमुख्यing; /* number of ग_लिखो-behind ios reमुख्यing
						 * in this BehindIO request
						 */
	sector_t		sector;
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
	पूर्णांक			पढ़ो_disk;

	काष्ठा list_head	retry_list;

	/*
	 * When R1BIO_BehindIO is set, we store pages क्रम ग_लिखो behind
	 * in behind_master_bio.
	 */
	काष्ठा bio		*behind_master_bio;

	/*
	 * अगर the IO is in WRITE direction, then multiple bios are used.
	 * We choose the number when they are allocated.
	 */
	काष्ठा bio		*bios[];
	/* DO NOT PUT ANY NEW FIELDS HERE - bios array is contiguously alloced*/
पूर्ण;

/* bits क्रम r1bio.state */
क्रमागत r1bio_state अणु
	R1BIO_Uptodate,
	R1BIO_IsSync,
	R1BIO_Degraded,
	R1BIO_BehindIO,
/* Set ReadError on bios that experience a पढ़ोerror so that
 * raid1d knows what to करो with them.
 */
	R1BIO_ReadError,
/* For ग_लिखो-behind requests, we call bi_end_io when
 * the last non-ग_लिखो-behind device completes, providing
 * any ग_लिखो was successful.  Otherwise we call when
 * any ग_लिखो-behind ग_लिखो succeeds, otherwise we call
 * with failure when last ग_लिखो completes (and all failed).
 * Record that bi_end_io was called with this flag...
 */
	R1BIO_Returned,
/* If a ग_लिखो क्रम this request means we can clear some
 * known-bad-block records, we set this flag
 */
	R1BIO_MadeGood,
	R1BIO_WriteError,
	R1BIO_FailFast,
पूर्ण;

अटल अंतरभूत पूर्णांक sector_to_idx(sector_t sector)
अणु
	वापस hash_दीर्घ(sector >> BARRIER_UNIT_SECTOR_BITS,
			 BARRIER_BUCKETS_NR_BITS);
पूर्ण
#पूर्ण_अगर
