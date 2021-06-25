<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * biपंचांगap.h: Copyright (C) Peter T. Breuer (ptb@ot.uc3m.es) 2003
 *
 * additions: Copyright (C) 2003-2004, Paul Clements, SteelEye Technology, Inc.
 */
#अगर_अघोषित BITMAP_H
#घोषणा BITMAP_H 1

#घोषणा BITMAP_MAJOR_LO 3
/* version 4 insists the biपंचांगap is in little-endian order
 * with version 3, it is host-endian which is non-portable
 * Version 5 is currently set only क्रम clustered devices
 */
#घोषणा BITMAP_MAJOR_HI 4
#घोषणा BITMAP_MAJOR_CLUSTERED 5
#घोषणा	BITMAP_MAJOR_HOSTENDIAN 3

/*
 * in-memory biपंचांगap:
 *
 * Use 16 bit block counters to track pending ग_लिखोs to each "chunk".
 * The 2 high order bits are special-purpose, the first is a flag indicating
 * whether a resync is needed.  The second is a flag indicating whether a
 * resync is active.
 * This means that the counter is actually 14 bits:
 *
 * +--------+--------+------------------------------------------------+
 * | resync | resync |               counter                          |
 * | needed | active |                                                |
 * |  (0-1) |  (0-1) |              (0-16383)                         |
 * +--------+--------+------------------------------------------------+
 *
 * The "resync needed" bit is set when:
 *    a '1' bit is पढ़ो from storage at startup.
 *    a ग_लिखो request fails on some drives
 *    a resync is पातed on a chunk with 'resync active' set
 * It is cleared (and resync-active set) when a resync starts across all drives
 * of the chunk.
 *
 *
 * The "resync active" bit is set when:
 *    a resync is started on all drives, and resync_needed is set.
 *       resync_needed will be cleared (as दीर्घ as resync_active wasn't alपढ़ोy set).
 * It is cleared when a resync completes.
 *
 * The counter counts pending ग_लिखो requests, plus the on-disk bit.
 * When the counter is '1' and the resync bits are clear, the on-disk
 * bit can be cleared as well, thus setting the counter to 0.
 * When we set a bit, or in the counter (to start a ग_लिखो), अगर the fields is
 * 0, we first set the disk bit and set the counter to 1.
 *
 * If the counter is 0, the on-disk bit is clear and the stripe is clean
 * Anything that dirties the stripe pushes the counter to 2 (at least)
 * and sets the on-disk bit (lazily).
 * If a periodic sweep find the counter at 2, it is decremented to 1.
 * If the sweep find the counter at 1, the on-disk bit is cleared and the
 * counter goes to zero.
 *
 * Also, we'll hijack the "map" poपूर्णांकer itself and use it as two 16 bit block
 * counters as a fallback when "page" memory cannot be allocated:
 *
 * Normal हाल (page memory allocated):
 *
 *     page poपूर्णांकer (32-bit)
 *
 *     [ ] ------+
 *               |
 *               +-------> [   ][   ]..[   ] (4096 byte page == 2048 counters)
 *                          c1   c2    c2048
 *
 * Hijacked हाल (page memory allocation failed):
 *
 *     hijacked page poपूर्णांकer (32-bit)
 *
 *     [		  ][		  ] (no page memory allocated)
 *      counter #1 (16-bit) counter #2 (16-bit)
 *
 */

#अगर_घोषित __KERNEL__

#घोषणा PAGE_BITS (PAGE_SIZE << 3)
#घोषणा PAGE_BIT_SHIFT (PAGE_SHIFT + 3)

प्रकार __u16 biपंचांगap_counter_t;
#घोषणा COUNTER_BITS 16
#घोषणा COUNTER_BIT_SHIFT 4
#घोषणा COUNTER_BYTE_SHIFT (COUNTER_BIT_SHIFT - 3)

#घोषणा NEEDED_MASK ((biपंचांगap_counter_t) (1 << (COUNTER_BITS - 1)))
#घोषणा RESYNC_MASK ((biपंचांगap_counter_t) (1 << (COUNTER_BITS - 2)))
#घोषणा COUNTER_MAX ((biपंचांगap_counter_t) RESYNC_MASK - 1)
#घोषणा NEEDED(x) (((biपंचांगap_counter_t) x) & NEEDED_MASK)
#घोषणा RESYNC(x) (((biपंचांगap_counter_t) x) & RESYNC_MASK)
#घोषणा COUNTER(x) (((biपंचांगap_counter_t) x) & COUNTER_MAX)

/* how many counters per page? */
#घोषणा PAGE_COUNTER_RATIO (PAGE_BITS / COUNTER_BITS)
/* same, except a shअगरt value क्रम more efficient bitops */
#घोषणा PAGE_COUNTER_SHIFT (PAGE_BIT_SHIFT - COUNTER_BIT_SHIFT)
/* same, except a mask value क्रम more efficient bitops */
#घोषणा PAGE_COUNTER_MASK  (PAGE_COUNTER_RATIO - 1)

#घोषणा BITMAP_BLOCK_SHIFT 9

#पूर्ण_अगर

/*
 * biपंचांगap काष्ठाures:
 */

#घोषणा BITMAP_MAGIC 0x6d746962

/* use these क्रम biपंचांगap->flags and biपंचांगap->sb->state bit-fields */
क्रमागत biपंचांगap_state अणु
	BITMAP_STALE	   = 1,  /* the biपंचांगap file is out of date or had -EIO */
	BITMAP_WRITE_ERROR = 2, /* A ग_लिखो error has occurred */
	BITMAP_HOSTENDIAN  =15,
पूर्ण;

/* the superblock at the front of the biपंचांगap file -- little endian */
प्रकार काष्ठा biपंचांगap_super_s अणु
	__le32 magic;        /*  0  BITMAP_MAGIC */
	__le32 version;      /*  4  the biपंचांगap major क्रम now, could change... */
	__u8  uuid[16];      /*  8  128 bit uuid - must match md device uuid */
	__le64 events;       /* 24  event counter क्रम the biपंचांगap (1)*/
	__le64 events_cleared;/*32  event counter when last bit cleared (2) */
	__le64 sync_size;    /* 40  the size of the md device's sync range(3) */
	__le32 state;        /* 48  biपंचांगap state inक्रमmation */
	__le32 chunksize;    /* 52  the biपंचांगap chunk size in bytes */
	__le32 daemon_sleep; /* 56  seconds between disk flushes */
	__le32 ग_लिखो_behind; /* 60  number of outstanding ग_लिखो-behind ग_लिखोs */
	__le32 sectors_reserved; /* 64 number of 512-byte sectors that are
				  * reserved क्रम the biपंचांगap. */
	__le32 nodes;        /* 68 the maximum number of nodes in cluster. */
	__u8 cluster_name[64]; /* 72 cluster name to which this md beदीर्घs */
	__u8  pad[256 - 136]; /* set to zero */
पूर्ण biपंचांगap_super_t;

/* notes:
 * (1) This event counter is updated beक्रमe the eventcounter in the md superblock
 *    When a biपंचांगap is loaded, it is only accepted अगर this event counter is equal
 *    to, or one greater than, the event counter in the superblock.
 * (2) This event counter is updated when the other one is *अगर*and*only*अगर* the
 *    array is not degraded.  As bits are not cleared when the array is degraded,
 *    this represents the last समय that any bits were cleared.
 *    If a device is being added that has an event count with this value or
 *    higher, it is accepted as conक्रमming to the biपंचांगap.
 * (3)This is the number of sectors represented by the biपंचांगap, and is the range that
 *    resync happens across.  For raid1 and raid5/6 it is the size of inभागidual
 *    devices.  For raid10 it is the size of the array.
 */

#अगर_घोषित __KERNEL__

/* the in-memory biपंचांगap is represented by biपंचांगap_pages */
काष्ठा biपंचांगap_page अणु
	/*
	 * map poपूर्णांकs to the actual memory page
	 */
	अक्षर *map;
	/*
	 * in emergencies (when map cannot be alloced), hijack the map
	 * poपूर्णांकer and use it as two counters itself
	 */
	अचिन्हित पूर्णांक hijacked:1;
	/*
	 * If any counter in this page is '1' or '2' - and so could be
	 * cleared then that page is marked as 'pending'
	 */
	अचिन्हित पूर्णांक pending:1;
	/*
	 * count of dirty bits on the page
	 */
	अचिन्हित पूर्णांक  count:30;
पूर्ण;

/* the मुख्य biपंचांगap काष्ठाure - one per mddev */
काष्ठा biपंचांगap अणु

	काष्ठा biपंचांगap_counts अणु
		spinlock_t lock;
		काष्ठा biपंचांगap_page *bp;
		अचिन्हित दीर्घ pages;		/* total number of pages
						 * in the biपंचांगap */
		अचिन्हित दीर्घ missing_pages;	/* number of pages
						 * not yet allocated */
		अचिन्हित दीर्घ chunkshअगरt;	/* chunksize = 2^chunkshअगरt
						 * (क्रम bitops) */
		अचिन्हित दीर्घ chunks;		/* Total number of data
						 * chunks क्रम the array */
	पूर्ण counts;

	काष्ठा mddev *mddev; /* the md device that the biपंचांगap is क्रम */

	__u64	events_cleared;
	पूर्णांक need_sync;

	काष्ठा biपंचांगap_storage अणु
		काष्ठा file *file;		/* backing disk file */
		काष्ठा page *sb_page;		/* cached copy of the biपंचांगap
						 * file superblock */
		काष्ठा page **filemap;		/* list of cache pages क्रम
						 * the file */
		अचिन्हित दीर्घ *filemap_attr;	/* attributes associated
						 * w/ filemap pages */
		अचिन्हित दीर्घ file_pages;	/* number of pages in the file*/
		अचिन्हित दीर्घ bytes;		/* total bytes in the biपंचांगap */
	पूर्ण storage;

	अचिन्हित दीर्घ flags;

	पूर्णांक allclean;

	atomic_t behind_ग_लिखोs;
	अचिन्हित दीर्घ behind_ग_लिखोs_used; /* highest actual value at runसमय */

	/*
	 * the biपंचांगap daemon - periodically wakes up and sweeps the biपंचांगap
	 * file, cleaning up bits and flushing out pages to disk as necessary
	 */
	अचिन्हित दीर्घ daemon_lastrun; /* jअगरfies of last run */
	अचिन्हित दीर्घ last_end_sync; /* when we lasted called end_sync to
				      * update biपंचांगap with resync progress */

	atomic_t pending_ग_लिखोs; /* pending ग_लिखोs to the biपंचांगap file */
	रुको_queue_head_t ग_लिखो_रुको;
	रुको_queue_head_t overflow_रुको;
	रुको_queue_head_t behind_रुको;

	काष्ठा kernfs_node *sysfs_can_clear;
	पूर्णांक cluster_slot;		/* Slot offset क्रम clustered env */
पूर्ण;

/* the biपंचांगap API */

/* these are used only by md/biपंचांगap */
काष्ठा biपंचांगap *md_biपंचांगap_create(काष्ठा mddev *mddev, पूर्णांक slot);
पूर्णांक md_biपंचांगap_load(काष्ठा mddev *mddev);
व्योम md_biपंचांगap_flush(काष्ठा mddev *mddev);
व्योम md_biपंचांगap_destroy(काष्ठा mddev *mddev);

व्योम md_biपंचांगap_prपूर्णांक_sb(काष्ठा biपंचांगap *biपंचांगap);
व्योम md_biपंचांगap_update_sb(काष्ठा biपंचांगap *biपंचांगap);
व्योम md_biपंचांगap_status(काष्ठा seq_file *seq, काष्ठा biपंचांगap *biपंचांगap);

पूर्णांक  md_biपंचांगap_setallbits(काष्ठा biपंचांगap *biपंचांगap);
व्योम md_biपंचांगap_ग_लिखो_all(काष्ठा biपंचांगap *biपंचांगap);

व्योम md_biपंचांगap_dirty_bits(काष्ठा biपंचांगap *biपंचांगap, अचिन्हित दीर्घ s, अचिन्हित दीर्घ e);

/* these are exported */
पूर्णांक md_biपंचांगap_startग_लिखो(काष्ठा biपंचांगap *biपंचांगap, sector_t offset,
			 अचिन्हित दीर्घ sectors, पूर्णांक behind);
व्योम md_biपंचांगap_endग_लिखो(काष्ठा biपंचांगap *biपंचांगap, sector_t offset,
			अचिन्हित दीर्घ sectors, पूर्णांक success, पूर्णांक behind);
पूर्णांक md_biपंचांगap_start_sync(काष्ठा biपंचांगap *biपंचांगap, sector_t offset, sector_t *blocks, पूर्णांक degraded);
व्योम md_biपंचांगap_end_sync(काष्ठा biपंचांगap *biपंचांगap, sector_t offset, sector_t *blocks, पूर्णांक पातed);
व्योम md_biपंचांगap_बंद_sync(काष्ठा biपंचांगap *biपंचांगap);
व्योम md_biपंचांगap_cond_end_sync(काष्ठा biपंचांगap *biपंचांगap, sector_t sector, bool क्रमce);
व्योम md_biपंचांगap_sync_with_cluster(काष्ठा mddev *mddev,
				 sector_t old_lo, sector_t old_hi,
				 sector_t new_lo, sector_t new_hi);

व्योम md_biपंचांगap_unplug(काष्ठा biपंचांगap *biपंचांगap);
व्योम md_biपंचांगap_daemon_work(काष्ठा mddev *mddev);

पूर्णांक md_biपंचांगap_resize(काष्ठा biपंचांगap *biपंचांगap, sector_t blocks,
		     पूर्णांक chunksize, पूर्णांक init);
काष्ठा biपंचांगap *get_biपंचांगap_from_slot(काष्ठा mddev *mddev, पूर्णांक slot);
पूर्णांक md_biपंचांगap_copy_from_slot(काष्ठा mddev *mddev, पूर्णांक slot,
			     sector_t *lo, sector_t *hi, bool clear_bits);
व्योम md_biपंचांगap_मुक्त(काष्ठा biपंचांगap *biपंचांगap);
व्योम md_biपंचांगap_रुको_behind_ग_लिखोs(काष्ठा mddev *mddev);
#पूर्ण_अगर

#पूर्ण_अगर
