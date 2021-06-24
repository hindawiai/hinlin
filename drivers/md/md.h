<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
   md.h : kernel पूर्णांकernal काष्ठाure of the Linux MD driver
          Copyright (C) 1996-98 Ingo Molnar, Gadi Oxman

*/

#अगर_अघोषित _MD_MD_H
#घोषणा _MD_MD_H

#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/badblocks.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश "md-cluster.h"

#घोषणा MaxSector (~(sector_t)0)

/*
 * These flags should really be called "NO_RETRY" rather than
 * "FAILFAST" because they करोn't make any promise about समय lapse,
 * only about the number of retries, which will be zero.
 * REQ_FAILFAST_DRIVER is not included because
 * Commit: 4a27446f3e39 ("[SCSI] modify scsi to handle new fail fast flags.")
 * seems to suggest that the errors it aव्योमs retrying should usually
 * be retried.
 */
#घोषणा	MD_FAILFAST	(REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT)

/*
 * The काष्ठा embedded in rdev is used to serialize IO.
 */
काष्ठा serial_in_rdev अणु
	काष्ठा rb_root_cached serial_rb;
	spinlock_t serial_lock;
	रुको_queue_head_t serial_io_रुको;
पूर्ण;

/*
 * MD's 'extended' device
 */
काष्ठा md_rdev अणु
	काष्ठा list_head same_set;	/* RAID devices within the same set */

	sector_t sectors;		/* Device size (in 512bytes sectors) */
	काष्ठा mddev *mddev;		/* RAID array अगर running */
	पूर्णांक last_events;		/* IO event बारtamp */

	/*
	 * If meta_bdev is non-शून्य, it means that a separate device is
	 * being used to store the metadata (superblock/biपंचांगap) which
	 * would otherwise be contained on the same device as the data (bdev).
	 */
	काष्ठा block_device *meta_bdev;
	काष्ठा block_device *bdev;	/* block device handle */

	काष्ठा page	*sb_page, *bb_page;
	पूर्णांक		sb_loaded;
	__u64		sb_events;
	sector_t	data_offset;	/* start of data in array */
	sector_t	new_data_offset;/* only relevant जबतक reshaping */
	sector_t	sb_start;	/* offset of the super block (in 512byte sectors) */
	पूर्णांक		sb_size;	/* bytes in the superblock */
	पूर्णांक		preferred_minor;	/* स्वतःrun support */

	काष्ठा kobject	kobj;

	/* A device can be in one of three states based on two flags:
	 * Not working:   faulty==1 in_sync==0
	 * Fully working: faulty==0 in_sync==1
	 * Working, but not
	 * in sync with array
	 *                faulty==0 in_sync==0
	 *
	 * It can never have faulty==1, in_sync==1
	 * This reduces the burden of testing multiple flags in many हालs
	 */

	अचिन्हित दीर्घ	flags;	/* bit set of 'enum flag_bits' bits. */
	रुको_queue_head_t blocked_रुको;

	पूर्णांक desc_nr;			/* descriptor index in the superblock */
	पूर्णांक raid_disk;			/* role of device in array */
	पूर्णांक new_raid_disk;		/* role that the device will have in
					 * the array after a level-change completes.
					 */
	पूर्णांक saved_raid_disk;		/* role that device used to have in the
					 * array and could again अगर we did a partial
					 * resync from the biपंचांगap
					 */
	जोड़ अणु
		sector_t recovery_offset;/* If this device has been partially
					 * recovered, this is where we were
					 * up to.
					 */
		sector_t journal_tail;	/* If this device is a journal device,
					 * this is the journal tail (journal
					 * recovery start poपूर्णांक)
					 */
	पूर्ण;

	atomic_t	nr_pending;	/* number of pending requests.
					 * only मुख्यtained क्रम arrays that
					 * support hot removal
					 */
	atomic_t	पढ़ो_errors;	/* number of consecutive पढ़ो errors that
					 * we have tried to ignore.
					 */
	समय64_t	last_पढ़ो_error;	/* monotonic समय since our
						 * last पढ़ो error
						 */
	atomic_t	corrected_errors; /* number of corrected पढ़ो errors,
					   * क्रम reporting to userspace and storing
					   * in superblock.
					   */

	काष्ठा serial_in_rdev *serial;  /* used क्रम raid1 io serialization */

	काष्ठा work_काष्ठा del_work;	/* used क्रम delayed sysfs removal */

	काष्ठा kernfs_node *sysfs_state; /* handle क्रम 'state'
					   * sysfs entry */
	/* handle क्रम 'unacknowledged_bad_blocks' sysfs dentry */
	काष्ठा kernfs_node *sysfs_unack_badblocks;
	/* handle क्रम 'bad_blocks' sysfs dentry */
	काष्ठा kernfs_node *sysfs_badblocks;
	काष्ठा badblocks badblocks;

	काष्ठा अणु
		लघु offset;	/* Offset from superblock to start of PPL.
				 * Not used by बाह्यal metadata. */
		अचिन्हित पूर्णांक size;	/* Size in sectors of the PPL space */
		sector_t sector;	/* First sector of the PPL space */
	पूर्ण ppl;
पूर्ण;
क्रमागत flag_bits अणु
	Faulty,			/* device is known to have a fault */
	In_sync,		/* device is in_sync with rest of array */
	Biपंचांगap_sync,		/* ..actually, not quite In_sync.  Need a
				 * biपंचांगap-based recovery to get fully in sync.
				 * The bit is only meaningful beक्रमe device
				 * has been passed to pers->hot_add_disk.
				 */
	WriteMostly,		/* Aव्योम पढ़ोing अगर at all possible */
	AutoDetected,		/* added by स्वतः-detect */
	Blocked,		/* An error occurred but has not yet
				 * been acknowledged by the metadata
				 * handler, so करोn't allow ग_लिखोs
				 * until it is cleared */
	WriteErrorSeen,		/* A ग_लिखो error has been seen on this
				 * device
				 */
	FaultRecorded,		/* Intermediate state क्रम clearing
				 * Blocked.  The Fault is/will-be
				 * recorded in the metadata, but that
				 * metadata hasn't been stored safely
				 * on disk yet.
				 */
	BlockedBadBlocks,	/* A ग_लिखोr is blocked because they
				 * found an unacknowledged bad-block.
				 * This can safely be cleared at any
				 * समय, and the ग_लिखोr will re-check.
				 * It may be set at any समय, and at
				 * worst the ग_लिखोr will समयout and
				 * re-check.  So setting it as
				 * accurately as possible is good, but
				 * not असलolutely critical.
				 */
	WantReplacement,	/* This device is a candidate to be
				 * hot-replaced, either because it has
				 * reported some faults, or because
				 * of explicit request.
				 */
	Replacement,		/* This device is a replacement क्रम
				 * a want_replacement device with same
				 * raid_disk number.
				 */
	Candidate,		/* For clustered environments only:
				 * This device is seen locally but not
				 * by the whole cluster
				 */
	Journal,		/* This device is used as journal क्रम
				 * raid-5/6.
				 * Usually, this device should be faster
				 * than other devices in the array
				 */
	ClusterRemove,
	RemoveSynchronized,	/* synchronize_rcu() was called after
				 * this device was known to be faulty,
				 * so it is safe to हटाओ without
				 * another synchronize_rcu() call.
				 */
	ExternalBbl,            /* External metadata provides bad
				 * block management क्रम a disk
				 */
	FailFast,		/* Minimal retries should be attempted on
				 * this device, so use REQ_FAILFAST_DEV.
				 * Also करोn't try to repair failed पढ़ोs.
				 * It is expects that no bad block log
				 * is present.
				 */
	LastDev,		/* Seems to be the last working dev as
				 * it didn't fail, so don't use FailFast
				 * any more क्रम metadata
				 */
	CollisionCheck,		/*
				 * check अगर there is collision between raid1
				 * serial bios.
				 */
पूर्ण;

अटल अंतरभूत पूर्णांक is_badblock(काष्ठा md_rdev *rdev, sector_t s, पूर्णांक sectors,
			      sector_t *first_bad, पूर्णांक *bad_sectors)
अणु
	अगर (unlikely(rdev->badblocks.count)) अणु
		पूर्णांक rv = badblocks_check(&rdev->badblocks, rdev->data_offset + s,
					sectors,
					first_bad, bad_sectors);
		अगर (rv)
			*first_bad -= rdev->data_offset;
		वापस rv;
	पूर्ण
	वापस 0;
पूर्ण
बाह्य पूर्णांक rdev_set_badblocks(काष्ठा md_rdev *rdev, sector_t s, पूर्णांक sectors,
			      पूर्णांक is_new);
बाह्य पूर्णांक rdev_clear_badblocks(काष्ठा md_rdev *rdev, sector_t s, पूर्णांक sectors,
				पूर्णांक is_new);
काष्ठा md_cluster_info;

/* change UNSUPPORTED_MDDEV_FLAGS क्रम each array type अगर new flag is added */
क्रमागत mddev_flags अणु
	MD_ARRAY_FIRST_USE,	/* First use of array, needs initialization */
	MD_CLOSING,		/* If set, we are closing the array, करो not खोलो
				 * it then */
	MD_JOURNAL_CLEAN,	/* A raid with journal is alपढ़ोy clean */
	MD_HAS_JOURNAL,		/* The raid array has journal feature set */
	MD_CLUSTER_RESYNC_LOCKED, /* cluster raid only, which means node
				   * alपढ़ोy took resync lock, need to
				   * release the lock */
	MD_FAILFAST_SUPPORTED,	/* Using MD_FAILFAST on metadata ग_लिखोs is
				 * supported as calls to md_error() will
				 * never cause the array to become failed.
				 */
	MD_HAS_PPL,		/* The raid array has PPL feature set */
	MD_HAS_MULTIPLE_PPLS,	/* The raid array has multiple PPLs feature set */
	MD_ALLOW_SB_UPDATE,	/* md_check_recovery is allowed to update
				 * the metadata without taking reconfig_mutex.
				 */
	MD_UPDATING_SB,		/* md_check_recovery is updating the metadata
				 * without explicitly holding reconfig_mutex.
				 */
	MD_NOT_READY,		/* करो_md_run() is active, so 'array_state'
				 * must not report that array is पढ़ोy yet
				 */
	MD_BROKEN,              /* This is used in RAID-0/LINEAR only, to stop
				 * I/O in हाल an array member is gone/failed.
				 */
पूर्ण;

क्रमागत mddev_sb_flags अणु
	MD_SB_CHANGE_DEVS,		/* Some device status has changed */
	MD_SB_CHANGE_CLEAN,	/* transition to or from 'clean' */
	MD_SB_CHANGE_PENDING,	/* चयन from 'clean' to 'active' in progress */
	MD_SB_NEED_REWRITE,	/* metadata ग_लिखो needs to be repeated */
पूर्ण;

#घोषणा NR_SERIAL_INFOS		8
/* record current range of serialize IOs */
काष्ठा serial_info अणु
	काष्ठा rb_node node;
	sector_t start;		/* start sector of rb node */
	sector_t last;		/* end sector of rb node */
	sector_t _subtree_last; /* highest sector in subtree of rb node */
पूर्ण;

काष्ठा mddev अणु
	व्योम				*निजी;
	काष्ठा md_personality		*pers;
	dev_t				unit;
	पूर्णांक				md_minor;
	काष्ठा list_head		disks;
	अचिन्हित दीर्घ			flags;
	अचिन्हित दीर्घ			sb_flags;

	पूर्णांक				suspended;
	atomic_t			active_io;
	पूर्णांक				ro;
	पूर्णांक				sysfs_active; /* set when sysfs deletes
						       * are happening, so run/
						       * takeover/stop are not safe
						       */
	काष्ठा gendisk			*gendisk;

	काष्ठा kobject			kobj;
	पूर्णांक				hold_active;
#घोषणा	UNTIL_IOCTL	1
#घोषणा	UNTIL_STOP	2

	/* Superblock inक्रमmation */
	पूर्णांक				major_version,
					minor_version,
					patch_version;
	पूर्णांक				persistent;
	पूर्णांक				बाह्यal;	/* metadata is
							 * managed बाह्यally */
	अक्षर				metadata_type[17]; /* बाह्यally set*/
	पूर्णांक				chunk_sectors;
	समय64_t			स_समय, uसमय;
	पूर्णांक				level, layout;
	अक्षर				clevel[16];
	पूर्णांक				raid_disks;
	पूर्णांक				max_disks;
	sector_t			dev_sectors;	/* used size of
							 * component devices */
	sector_t			array_sectors; /* exported array size */
	पूर्णांक				बाह्यal_size; /* size managed
							* बाह्यally */
	__u64				events;
	/* If the last 'event' was simply a clean->dirty transition, and
	 * we didn't ग_लिखो it to the spares, then it is safe and simple
	 * to just decrement the event count on a dirty->clean transition.
	 * So we record that possibility here.
	 */
	पूर्णांक				can_decrease_events;

	अक्षर				uuid[16];

	/* If the array is being reshaped, we need to record the
	 * new shape and an indication of where we are up to.
	 * This is written to the superblock.
	 * If reshape_position is MaxSector, then no reshape is happening (yet).
	 */
	sector_t			reshape_position;
	पूर्णांक				delta_disks, new_level, new_layout;
	पूर्णांक				new_chunk_sectors;
	पूर्णांक				reshape_backwards;

	काष्ठा md_thपढ़ो		*thपढ़ो;	/* management thपढ़ो */
	काष्ठा md_thपढ़ो		*sync_thपढ़ो;	/* करोing resync or reस्थिरruct */

	/* 'last_sync_action' is initialized to "none".  It is set when a
	 * sync operation (i.e "data-check", "requested-resync", "resync",
	 * "recovery", or "reshape") is started.  It holds this value even
	 * when the sync thपढ़ो is "frozen" (पूर्णांकerrupted) or "idle" (stopped
	 * or finished).  It is overwritten when a new sync operation is begun.
	 */
	अक्षर				*last_sync_action;
	sector_t			curr_resync;	/* last block scheduled */
	/* As resync requests can complete out of order, we cannot easily track
	 * how much resync has been completed.  So we occasionally छोड़ो until
	 * everything completes, then set curr_resync_completed to curr_resync.
	 * As such it may be well behind the real resync mark, but it is a value
	 * we are certain of.
	 */
	sector_t			curr_resync_completed;
	अचिन्हित दीर्घ			resync_mark;	/* a recent बारtamp */
	sector_t			resync_mark_cnt;/* blocks written at resync_mark */
	sector_t			curr_mark_cnt; /* blocks scheduled now */

	sector_t			resync_max_sectors; /* may be set by personality */

	atomic64_t			resync_mismatches; /* count of sectors where
							    * parity/replica mismatch found
							    */

	/* allow user-space to request suspension of IO to regions of the array */
	sector_t			suspend_lo;
	sector_t			suspend_hi;
	/* अगर zero, use the प्रणाली-wide शेष */
	पूर्णांक				sync_speed_min;
	पूर्णांक				sync_speed_max;

	/* resync even though the same disks are shared among md-devices */
	पूर्णांक				parallel_resync;

	पूर्णांक				ok_start_degraded;

	अचिन्हित दीर्घ			recovery;
	/* If a RAID personality determines that recovery (of a particular
	 * device) will fail due to a पढ़ो error on the source device, it
	 * takes a copy of this number and करोes not attempt recovery again
	 * until this number changes.
	 */
	पूर्णांक				recovery_disabled;

	पूर्णांक				in_sync;	/* know to not need resync */
	/* 'open_mutex' avoids races between 'md_open' and 'do_md_stop', so
	 * that we are never stopping an array जबतक it is खोलो.
	 * 'reconfig_mutex' protects all other reconfiguration.
	 * These locks are separate due to conflicting पूर्णांकeractions
	 * with bdev->bd_mutex.
	 * Lock ordering is:
	 *  reconfig_mutex -> bd_mutex
	 *  bd_mutex -> खोलो_mutex:  e.g. __blkdev_get -> md_खोलो
	 */
	काष्ठा mutex			खोलो_mutex;
	काष्ठा mutex			reconfig_mutex;
	atomic_t			active;		/* general refcount */
	atomic_t			खोलोers;	/* number of active खोलोs */

	पूर्णांक				changed;	/* True अगर we might need to
							 * reपढ़ो partition info */
	पूर्णांक				degraded;	/* whether md should consider
							 * adding a spare
							 */

	atomic_t			recovery_active; /* blocks scheduled, but not written */
	रुको_queue_head_t		recovery_रुको;
	sector_t			recovery_cp;
	sector_t			resync_min;	/* user requested sync
							 * starts here */
	sector_t			resync_max;	/* resync should छोड़ो
							 * when it माला_लो here */

	काष्ठा kernfs_node		*sysfs_state;	/* handle क्रम 'array_state'
							 * file in sysfs.
							 */
	काष्ठा kernfs_node		*sysfs_action;  /* handle क्रम 'sync_action' */
	काष्ठा kernfs_node		*sysfs_completed;	/*handle क्रम 'sync_completed' */
	काष्ठा kernfs_node		*sysfs_degraded;	/*handle क्रम 'degraded' */
	काष्ठा kernfs_node		*sysfs_level;		/*handle क्रम 'level' */

	काष्ठा work_काष्ठा del_work;	/* used क्रम delayed sysfs removal */

	/* "lock" protects:
	 *   flush_bio transition from शून्य to !शून्य
	 *   rdev superblocks, events
	 *   clearing MD_CHANGE_*
	 *   in_sync - and related safemode and MD_CHANGE changes
	 *   pers (also रक्षित by reconfig_mutex and pending IO).
	 *   clearing ->biपंचांगap
	 *   clearing ->biपंचांगap_info.file
	 *   changing ->resync_अणुmin,maxपूर्ण
	 *   setting MD_RECOVERY_RUNNING (which पूर्णांकeracts with resync_अणुmin,maxपूर्ण)
	 */
	spinlock_t			lock;
	रुको_queue_head_t		sb_रुको;	/* क्रम रुकोing on superblock updates */
	atomic_t			pending_ग_लिखोs;	/* number of active superblock ग_लिखोs */

	अचिन्हित पूर्णांक			safemode;	/* अगर set, update "clean" superblock
							 * when no ग_लिखोs pending.
							 */
	अचिन्हित पूर्णांक			safemode_delay;
	काष्ठा समयr_list		safemode_समयr;
	काष्ठा percpu_ref		ग_लिखोs_pending;
	पूर्णांक				sync_checkers;	/* # of thपढ़ोs checking ग_लिखोs_pending */
	काष्ठा request_queue		*queue;	/* क्रम plugging ... */

	काष्ठा biपंचांगap			*biपंचांगap; /* the biपंचांगap क्रम the device */
	काष्ठा अणु
		काष्ठा file		*file; /* the biपंचांगap file */
		loff_t			offset; /* offset from superblock of
						 * start of biपंचांगap. May be
						 * negative, but not '0'
						 * For बाह्यal metadata, offset
						 * from start of device.
						 */
		अचिन्हित दीर्घ		space; /* space available at this offset */
		loff_t			शेष_offset; /* this is the offset to use when
							 * hot-adding a biपंचांगap.  It should
							 * eventually be settable by sysfs.
							 */
		अचिन्हित दीर्घ		शेष_space; /* space available at
							* शेष offset */
		काष्ठा mutex		mutex;
		अचिन्हित दीर्घ		chunksize;
		अचिन्हित दीर्घ		daemon_sleep; /* how many jअगरfies between updates? */
		अचिन्हित दीर्घ		max_ग_लिखो_behind; /* ग_लिखो-behind mode */
		पूर्णांक			बाह्यal;
		पूर्णांक			nodes; /* Maximum number of nodes in the cluster */
		अक्षर                    cluster_name[64]; /* Name of the cluster */
	पूर्ण biपंचांगap_info;

	atomic_t			max_corr_पढ़ो_errors; /* max पढ़ो retries */
	काष्ठा list_head		all_mddevs;

	काष्ठा attribute_group		*to_हटाओ;

	काष्ठा bio_set			bio_set;
	काष्ठा bio_set			sync_set; /* क्रम sync operations like
						   * metadata and biपंचांगap ग_लिखोs
						   */
	mempool_t			md_io_pool;

	/* Generic flush handling.
	 * The last to finish preflush schedules a worker to submit
	 * the rest of the request (without the REQ_PREFLUSH flag).
	 */
	काष्ठा bio *flush_bio;
	atomic_t flush_pending;
	kसमय_प्रकार start_flush, prev_flush_start; /* prev_flush_start is when the previous completed
						* flush was started.
						*/
	काष्ठा work_काष्ठा flush_work;
	काष्ठा work_काष्ठा event_work;	/* used by dm to report failure event */
	mempool_t *serial_info_pool;
	व्योम (*sync_super)(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev);
	काष्ठा md_cluster_info		*cluster_info;
	अचिन्हित पूर्णांक			good_device_nr;	/* good device num within cluster raid */
	अचिन्हित पूर्णांक			noio_flag; /* क्रम meदो_स्मृति scope API */

	bool	has_superblocks:1;
	bool	fail_last_dev:1;
	bool	serialize_policy:1;
पूर्ण;

क्रमागत recovery_flags अणु
	/*
	 * If neither SYNC or RESHAPE are set, then it is a recovery.
	 */
	MD_RECOVERY_RUNNING,	/* a thपढ़ो is running, or about to be started */
	MD_RECOVERY_SYNC,	/* actually करोing a resync, not a recovery */
	MD_RECOVERY_RECOVER,	/* करोing recovery, or need to try it. */
	MD_RECOVERY_INTR,	/* resync needs to be पातed क्रम some reason */
	MD_RECOVERY_DONE,	/* thपढ़ो is करोne and is रुकोing to be reaped */
	MD_RECOVERY_NEEDED,	/* we might need to start a resync/recover */
	MD_RECOVERY_REQUESTED,	/* user-space has requested a sync (used with SYNC) */
	MD_RECOVERY_CHECK,	/* user-space request क्रम check-only, no repair */
	MD_RECOVERY_RESHAPE,	/* A reshape is happening */
	MD_RECOVERY_FROZEN,	/* User request to पात, and not restart, any action */
	MD_RECOVERY_ERROR,	/* sync-action पूर्णांकerrupted because io-error */
	MD_RECOVERY_WAIT,	/* रुकोing क्रम pers->start() to finish */
	MD_RESYNCING_REMOTE,	/* remote node is running resync thपढ़ो */
पूर्ण;

अटल अंतरभूत पूर्णांक __must_check mddev_lock(काष्ठा mddev *mddev)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&mddev->reconfig_mutex);
पूर्ण

/* Someबार we need to take the lock in a situation where
 * failure due to पूर्णांकerrupts is not acceptable.
 */
अटल अंतरभूत व्योम mddev_lock_noपूर्णांकr(काष्ठा mddev *mddev)
अणु
	mutex_lock(&mddev->reconfig_mutex);
पूर्ण

अटल अंतरभूत पूर्णांक mddev_trylock(काष्ठा mddev *mddev)
अणु
	वापस mutex_trylock(&mddev->reconfig_mutex);
पूर्ण
बाह्य व्योम mddev_unlock(काष्ठा mddev *mddev);

अटल अंतरभूत व्योम md_sync_acct(काष्ठा block_device *bdev, अचिन्हित दीर्घ nr_sectors)
अणु
	atomic_add(nr_sectors, &bdev->bd_disk->sync_io);
पूर्ण

अटल अंतरभूत व्योम md_sync_acct_bio(काष्ठा bio *bio, अचिन्हित दीर्घ nr_sectors)
अणु
	md_sync_acct(bio->bi_bdev, nr_sectors);
पूर्ण

काष्ठा md_personality
अणु
	अक्षर *name;
	पूर्णांक level;
	काष्ठा list_head list;
	काष्ठा module *owner;
	bool __must_check (*make_request)(काष्ठा mddev *mddev, काष्ठा bio *bio);
	/*
	 * start up works that करो NOT require md_thपढ़ो. tasks that
	 * requires md_thपढ़ो should go पूर्णांकo start()
	 */
	पूर्णांक (*run)(काष्ठा mddev *mddev);
	/* start up works that require md thपढ़ोs */
	पूर्णांक (*start)(काष्ठा mddev *mddev);
	व्योम (*मुक्त)(काष्ठा mddev *mddev, व्योम *priv);
	व्योम (*status)(काष्ठा seq_file *seq, काष्ठा mddev *mddev);
	/* error_handler must set ->faulty and clear ->in_sync
	 * अगर appropriate, and should पात recovery अगर needed
	 */
	व्योम (*error_handler)(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev);
	पूर्णांक (*hot_add_disk) (काष्ठा mddev *mddev, काष्ठा md_rdev *rdev);
	पूर्णांक (*hot_हटाओ_disk) (काष्ठा mddev *mddev, काष्ठा md_rdev *rdev);
	पूर्णांक (*spare_active) (काष्ठा mddev *mddev);
	sector_t (*sync_request)(काष्ठा mddev *mddev, sector_t sector_nr, पूर्णांक *skipped);
	पूर्णांक (*resize) (काष्ठा mddev *mddev, sector_t sectors);
	sector_t (*size) (काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks);
	पूर्णांक (*check_reshape) (काष्ठा mddev *mddev);
	पूर्णांक (*start_reshape) (काष्ठा mddev *mddev);
	व्योम (*finish_reshape) (काष्ठा mddev *mddev);
	व्योम (*update_reshape_pos) (काष्ठा mddev *mddev);
	/* quiesce suspends or resumes पूर्णांकernal processing.
	 * 1 - stop new actions and रुको क्रम action io to complete
	 * 0 - वापस to normal behaviour
	 */
	व्योम (*quiesce) (काष्ठा mddev *mddev, पूर्णांक quiesce);
	/* takeover is used to transition an array from one
	 * personality to another.  The new personality must be able
	 * to handle the data in the current layout.
	 * e.g. 2drive raid1 -> 2drive raid5
	 *      ndrive raid5 -> degraded n+1drive raid6 with special layout
	 * If the takeover succeeds, a new 'private' काष्ठाure is वापसed.
	 * This needs to be installed and then ->run used to activate the
	 * array.
	 */
	व्योम *(*takeover) (काष्ठा mddev *mddev);
	/* Changes the consistency policy of an active array. */
	पूर्णांक (*change_consistency_policy)(काष्ठा mddev *mddev, स्थिर अक्षर *buf);
पूर्ण;

काष्ठा md_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा mddev *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा mddev *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;
बाह्य काष्ठा attribute_group md_biपंचांगap_group;

अटल अंतरभूत काष्ठा kernfs_node *sysfs_get_dirent_safe(काष्ठा kernfs_node *sd, अक्षर *name)
अणु
	अगर (sd)
		वापस sysfs_get_dirent(sd, name);
	वापस sd;
पूर्ण
अटल अंतरभूत व्योम sysfs_notअगरy_dirent_safe(काष्ठा kernfs_node *sd)
अणु
	अगर (sd)
		sysfs_notअगरy_dirent(sd);
पूर्ण

अटल अंतरभूत अक्षर * mdname (काष्ठा mddev * mddev)
अणु
	वापस mddev->gendisk ? mddev->gendisk->disk_name : "mdX";
पूर्ण

अटल अंतरभूत पूर्णांक sysfs_link_rdev(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	अक्षर nm[20];
	अगर (!test_bit(Replacement, &rdev->flags) &&
	    !test_bit(Journal, &rdev->flags) &&
	    mddev->kobj.sd) अणु
		प्र_लिखो(nm, "rd%d", rdev->raid_disk);
		वापस sysfs_create_link(&mddev->kobj, &rdev->kobj, nm);
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_unlink_rdev(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	अक्षर nm[20];
	अगर (!test_bit(Replacement, &rdev->flags) &&
	    !test_bit(Journal, &rdev->flags) &&
	    mddev->kobj.sd) अणु
		प्र_लिखो(nm, "rd%d", rdev->raid_disk);
		sysfs_हटाओ_link(&mddev->kobj, nm);
	पूर्ण
पूर्ण

/*
 * iterates through some rdev ringlist. It's safe to हटाओ the
 * current 'rdev'. Dont touch 'tmp' though.
 */
#घोषणा rdev_क्रम_each_list(rdev, पंचांगp, head)				\
	list_क्रम_each_entry_safe(rdev, पंचांगp, head, same_set)

/*
 * iterates through the 'same array disks' ringlist
 */
#घोषणा rdev_क्रम_each(rdev, mddev)				\
	list_क्रम_each_entry(rdev, &((mddev)->disks), same_set)

#घोषणा rdev_क्रम_each_safe(rdev, पंचांगp, mddev)				\
	list_क्रम_each_entry_safe(rdev, पंचांगp, &((mddev)->disks), same_set)

#घोषणा rdev_क्रम_each_rcu(rdev, mddev)				\
	list_क्रम_each_entry_rcu(rdev, &((mddev)->disks), same_set)

काष्ठा md_thपढ़ो अणु
	व्योम			(*run) (काष्ठा md_thपढ़ो *thपढ़ो);
	काष्ठा mddev		*mddev;
	रुको_queue_head_t	wqueue;
	अचिन्हित दीर्घ		flags;
	काष्ठा task_काष्ठा	*tsk;
	अचिन्हित दीर्घ		समयout;
	व्योम			*निजी;
पूर्ण;

#घोषणा THREAD_WAKEUP  0

अटल अंतरभूत व्योम safe_put_page(काष्ठा page *p)
अणु
	अगर (p) put_page(p);
पूर्ण

बाह्य पूर्णांक रेजिस्टर_md_personality(काष्ठा md_personality *p);
बाह्य पूर्णांक unरेजिस्टर_md_personality(काष्ठा md_personality *p);
बाह्य पूर्णांक रेजिस्टर_md_cluster_operations(काष्ठा md_cluster_operations *ops,
		काष्ठा module *module);
बाह्य पूर्णांक unरेजिस्टर_md_cluster_operations(व्योम);
बाह्य पूर्णांक md_setup_cluster(काष्ठा mddev *mddev, पूर्णांक nodes);
बाह्य व्योम md_cluster_stop(काष्ठा mddev *mddev);
बाह्य काष्ठा md_thपढ़ो *md_रेजिस्टर_thपढ़ो(
	व्योम (*run)(काष्ठा md_thपढ़ो *thपढ़ो),
	काष्ठा mddev *mddev,
	स्थिर अक्षर *name);
बाह्य व्योम md_unरेजिस्टर_thपढ़ो(काष्ठा md_thपढ़ो **thपढ़ोp);
बाह्य व्योम md_wakeup_thपढ़ो(काष्ठा md_thपढ़ो *thपढ़ो);
बाह्य व्योम md_check_recovery(काष्ठा mddev *mddev);
बाह्य व्योम md_reap_sync_thपढ़ो(काष्ठा mddev *mddev);
बाह्य पूर्णांक mddev_init_ग_लिखोs_pending(काष्ठा mddev *mddev);
बाह्य bool md_ग_लिखो_start(काष्ठा mddev *mddev, काष्ठा bio *bi);
बाह्य व्योम md_ग_लिखो_inc(काष्ठा mddev *mddev, काष्ठा bio *bi);
बाह्य व्योम md_ग_लिखो_end(काष्ठा mddev *mddev);
बाह्य व्योम md_करोne_sync(काष्ठा mddev *mddev, पूर्णांक blocks, पूर्णांक ok);
बाह्य व्योम md_error(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev);
बाह्य व्योम md_finish_reshape(काष्ठा mddev *mddev);
व्योम md_submit_discard_bio(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev,
			काष्ठा bio *bio, sector_t start, sector_t size);

बाह्य bool __must_check md_flush_request(काष्ठा mddev *mddev, काष्ठा bio *bio);
बाह्य व्योम md_super_ग_लिखो(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev,
			   sector_t sector, पूर्णांक size, काष्ठा page *page);
बाह्य पूर्णांक md_super_रुको(काष्ठा mddev *mddev);
बाह्य पूर्णांक sync_page_io(काष्ठा md_rdev *rdev, sector_t sector, पूर्णांक size,
			काष्ठा page *page, पूर्णांक op, पूर्णांक op_flags,
			bool metadata_op);
बाह्य व्योम md_करो_sync(काष्ठा md_thपढ़ो *thपढ़ो);
बाह्य व्योम md_new_event(काष्ठा mddev *mddev);
बाह्य व्योम md_allow_ग_लिखो(काष्ठा mddev *mddev);
बाह्य व्योम md_रुको_क्रम_blocked_rdev(काष्ठा md_rdev *rdev, काष्ठा mddev *mddev);
बाह्य व्योम md_set_array_sectors(काष्ठा mddev *mddev, sector_t array_sectors);
बाह्य पूर्णांक md_check_no_biपंचांगap(काष्ठा mddev *mddev);
बाह्य पूर्णांक md_पूर्णांकegrity_रेजिस्टर(काष्ठा mddev *mddev);
बाह्य पूर्णांक md_पूर्णांकegrity_add_rdev(काष्ठा md_rdev *rdev, काष्ठा mddev *mddev);
बाह्य पूर्णांक strict_म_से_अदीर्घ_scaled(स्थिर अक्षर *cp, अचिन्हित दीर्घ *res, पूर्णांक scale);

बाह्य व्योम mddev_init(काष्ठा mddev *mddev);
बाह्य पूर्णांक md_run(काष्ठा mddev *mddev);
बाह्य पूर्णांक md_start(काष्ठा mddev *mddev);
बाह्य व्योम md_stop(काष्ठा mddev *mddev);
बाह्य व्योम md_stop_ग_लिखोs(काष्ठा mddev *mddev);
बाह्य पूर्णांक md_rdev_init(काष्ठा md_rdev *rdev);
बाह्य व्योम md_rdev_clear(काष्ठा md_rdev *rdev);

बाह्य व्योम md_handle_request(काष्ठा mddev *mddev, काष्ठा bio *bio);
बाह्य व्योम mddev_suspend(काष्ठा mddev *mddev);
बाह्य व्योम mddev_resume(काष्ठा mddev *mddev);

बाह्य व्योम md_reload_sb(काष्ठा mddev *mddev, पूर्णांक raid_disk);
बाह्य व्योम md_update_sb(काष्ठा mddev *mddev, पूर्णांक क्रमce);
बाह्य व्योम md_kick_rdev_from_array(काष्ठा md_rdev * rdev);
बाह्य व्योम mddev_create_serial_pool(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev,
				     bool is_suspend);
बाह्य व्योम mddev_destroy_serial_pool(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev,
				      bool is_suspend);
काष्ठा md_rdev *md_find_rdev_nr_rcu(काष्ठा mddev *mddev, पूर्णांक nr);
काष्ठा md_rdev *md_find_rdev_rcu(काष्ठा mddev *mddev, dev_t dev);

अटल अंतरभूत bool is_mddev_broken(काष्ठा md_rdev *rdev, स्थिर अक्षर *md_type)
अणु
	पूर्णांक flags = rdev->bdev->bd_disk->flags;

	अगर (!(flags & GENHD_FL_UP)) अणु
		अगर (!test_and_set_bit(MD_BROKEN, &rdev->mddev->flags))
			pr_warn("md: %s: %s array has a missing/failed member\n",
				mdname(rdev->mddev), md_type);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम rdev_dec_pending(काष्ठा md_rdev *rdev, काष्ठा mddev *mddev)
अणु
	पूर्णांक faulty = test_bit(Faulty, &rdev->flags);
	अगर (atomic_dec_and_test(&rdev->nr_pending) && faulty) अणु
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
	पूर्ण
पूर्ण

बाह्य काष्ठा md_cluster_operations *md_cluster_ops;
अटल अंतरभूत पूर्णांक mddev_is_clustered(काष्ठा mddev *mddev)
अणु
	वापस mddev->cluster_info && mddev->biपंचांगap_info.nodes > 1;
पूर्ण

/* clear unsupported mddev_flags */
अटल अंतरभूत व्योम mddev_clear_unsupported_flags(काष्ठा mddev *mddev,
	अचिन्हित दीर्घ unsupported_flags)
अणु
	mddev->flags &= ~unsupported_flags;
पूर्ण

अटल अंतरभूत व्योम mddev_check_ग_लिखोsame(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	अगर (bio_op(bio) == REQ_OP_WRITE_SAME &&
	    !bio->bi_bdev->bd_disk->queue->limits.max_ग_लिखो_same_sectors)
		mddev->queue->limits.max_ग_लिखो_same_sectors = 0;
पूर्ण

अटल अंतरभूत व्योम mddev_check_ग_लिखो_zeroes(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	अगर (bio_op(bio) == REQ_OP_WRITE_ZEROES &&
	    !bio->bi_bdev->bd_disk->queue->limits.max_ग_लिखो_zeroes_sectors)
		mddev->queue->limits.max_ग_लिखो_zeroes_sectors = 0;
पूर्ण

काष्ठा mdu_array_info_s;
काष्ठा mdu_disk_info_s;

बाह्य पूर्णांक mdp_major;
व्योम md_स्वतःstart_arrays(पूर्णांक part);
पूर्णांक md_set_array_info(काष्ठा mddev *mddev, काष्ठा mdu_array_info_s *info);
पूर्णांक md_add_new_disk(काष्ठा mddev *mddev, काष्ठा mdu_disk_info_s *info);
पूर्णांक करो_md_run(काष्ठा mddev *mddev);

बाह्य स्थिर काष्ठा block_device_operations md_fops;

#पूर्ण_अगर /* _MD_MD_H */
