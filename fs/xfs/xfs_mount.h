<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_MOUNT_H__
#घोषणा	__XFS_MOUNT_H__

काष्ठा xlog;
काष्ठा xfs_inode;
काष्ठा xfs_mru_cache;
काष्ठा xfs_ail;
काष्ठा xfs_quotainfo;
काष्ठा xfs_da_geometry;

/* dynamic pपुनः_स्मृतिation मुक्त space thresholds, 5% करोwn to 1% */
क्रमागत अणु
	XFS_LOWSP_1_PCNT = 0,
	XFS_LOWSP_2_PCNT,
	XFS_LOWSP_3_PCNT,
	XFS_LOWSP_4_PCNT,
	XFS_LOWSP_5_PCNT,
	XFS_LOWSP_MAX,
पूर्ण;

/*
 * Error Configuration
 *
 * Error classes define the subप्रणाली the configuration beदीर्घs to.
 * Error numbers define the errors that are configurable.
 */
क्रमागत अणु
	XFS_ERR_METADATA,
	XFS_ERR_CLASS_MAX,
पूर्ण;
क्रमागत अणु
	XFS_ERR_DEFAULT,
	XFS_ERR_EIO,
	XFS_ERR_ENOSPC,
	XFS_ERR_ENODEV,
	XFS_ERR_ERRNO_MAX,
पूर्ण;

#घोषणा XFS_ERR_RETRY_FOREVER	-1

/*
 * Although retry_समयout is in jअगरfies which is normally an अचिन्हित दीर्घ,
 * we limit the retry समयout to 86400 seconds, or one day.  So even a
 * चिन्हित 32-bit दीर्घ is sufficient क्रम a HZ value up to 24855.  Making it
 * चिन्हित lets us store the special "-1" value, meaning retry क्रमever.
 */
काष्ठा xfs_error_cfg अणु
	काष्ठा xfs_kobj	kobj;
	पूर्णांक		max_retries;
	दीर्घ		retry_समयout;	/* in jअगरfies, -1 = infinite */
पूर्ण;

/*
 * The काष्ठा xfsmount layout is optimised to separate पढ़ो-mostly variables
 * from variables that are frequently modअगरied. We put the पढ़ो-mostly variables
 * first, then place all the other variables at the end.
 *
 * Typically, पढ़ो-mostly variables are those that are set at mount समय and
 * never changed again, or only change rarely as a result of things like sysfs
 * knobs being tweaked.
 */
प्रकार काष्ठा xfs_mount अणु
	काष्ठा xfs_sb		m_sb;		/* copy of fs superblock */
	काष्ठा super_block	*m_super;
	काष्ठा xfs_ail		*m_ail;		/* fs active log item list */
	काष्ठा xfs_buf		*m_sb_bp;	/* buffer क्रम superblock */
	अक्षर			*m_rtname;	/* realसमय device name */
	अक्षर			*m_logname;	/* बाह्यal log device name */
	काष्ठा xfs_da_geometry	*m_dir_geo;	/* directory block geometry */
	काष्ठा xfs_da_geometry	*m_attr_geo;	/* attribute block geometry */
	काष्ठा xlog		*m_log;		/* log specअगरic stuff */
	काष्ठा xfs_inode	*m_rbmip;	/* poपूर्णांकer to biपंचांगap inode */
	काष्ठा xfs_inode	*m_rsumip;	/* poपूर्णांकer to summary inode */
	काष्ठा xfs_inode	*m_rootip;	/* poपूर्णांकer to root directory */
	काष्ठा xfs_quotainfo	*m_quotainfo;	/* disk quota inक्रमmation */
	xfs_buftarg_t		*m_ddev_targp;	/* saves taking the address */
	xfs_buftarg_t		*m_logdev_targp;/* ptr to log device */
	xfs_buftarg_t		*m_rtdev_targp;	/* ptr to rt device */
	/*
	 * Optional cache of rt summary level per biपंचांगap block with the
	 * invariant that m_rsum_cache[bbno] <= the minimum i क्रम which
	 * rsum[i][bbno] != 0. Reads and ग_लिखोs are serialized by the rsumip
	 * inode lock.
	 */
	uपूर्णांक8_t			*m_rsum_cache;
	काष्ठा xfs_mru_cache	*m_filestream;  /* per-mount filestream data */
	काष्ठा workqueue_काष्ठा *m_buf_workqueue;
	काष्ठा workqueue_काष्ठा	*m_unwritten_workqueue;
	काष्ठा workqueue_काष्ठा	*m_cil_workqueue;
	काष्ठा workqueue_काष्ठा	*m_reclaim_workqueue;
	काष्ठा workqueue_काष्ठा *m_gc_workqueue;
	काष्ठा workqueue_काष्ठा	*m_sync_workqueue;

	पूर्णांक			m_bsize;	/* fs logical block size */
	uपूर्णांक8_t			m_blkbit_log;	/* blocklog + NBBY */
	uपूर्णांक8_t			m_blkbb_log;	/* blocklog - BBSHIFT */
	uपूर्णांक8_t			m_agno_log;	/* log #ag's */
	uपूर्णांक8_t			m_sectbb_log;	/* sectlog - BBSHIFT */
	uपूर्णांक			m_blockmask;	/* sb_blocksize-1 */
	uपूर्णांक			m_blockwsize;	/* sb_blocksize in words */
	uपूर्णांक			m_blockwmask;	/* blockwsize-1 */
	uपूर्णांक			m_alloc_mxr[2];	/* max alloc btree records */
	uपूर्णांक			m_alloc_mnr[2];	/* min alloc btree records */
	uपूर्णांक			m_bmap_dmxr[2];	/* max bmap btree records */
	uपूर्णांक			m_bmap_dmnr[2];	/* min bmap btree records */
	uपूर्णांक			m_rmap_mxr[2];	/* max rmap btree records */
	uपूर्णांक			m_rmap_mnr[2];	/* min rmap btree records */
	uपूर्णांक			m_refc_mxr[2];	/* max refc btree records */
	uपूर्णांक			m_refc_mnr[2];	/* min refc btree records */
	uपूर्णांक			m_ag_maxlevels;	/* XFS_AG_MAXLEVELS */
	uपूर्णांक			m_bm_maxlevels[2]; /* XFS_BM_MAXLEVELS */
	uपूर्णांक			m_rmap_maxlevels; /* max rmap btree levels */
	uपूर्णांक			m_refc_maxlevels; /* max refcount btree level */
	xfs_extlen_t		m_ag_pपुनः_स्मृति_blocks; /* reserved ag blocks */
	uपूर्णांक			m_alloc_set_aside; /* space we can't use */
	uपूर्णांक			m_ag_max_usable; /* max space per AG */
	पूर्णांक			m_dalign;	/* stripe unit */
	पूर्णांक			m_swidth;	/* stripe width */
	xfs_agnumber_t		m_maxagi;	/* highest inode alloc group */
	uपूर्णांक			m_allocsize_log;/* min ग_लिखो size log bytes */
	uपूर्णांक			m_allocsize_blocks; /* min ग_लिखो size blocks */
	पूर्णांक			m_logbufs;	/* number of log buffers */
	पूर्णांक			m_logbsize;	/* size of each log buffer */
	uपूर्णांक			m_rsumlevels;	/* rt summary levels */
	uपूर्णांक			m_rsumsize;	/* size of rt summary, bytes */
	पूर्णांक			m_fixedfsid[2];	/* unchanged क्रम lअगरe of FS */
	uपूर्णांक			m_qflags;	/* quota status flags */
	uपूर्णांक64_t		m_flags;	/* global mount flags */
	पूर्णांक64_t			m_low_space[XFS_LOWSP_MAX];
	काष्ठा xfs_ino_geometry	m_ino_geo;	/* inode geometry */
	काष्ठा xfs_trans_resv	m_resv;		/* precomputed res values */
						/* low मुक्त space thresholds */
	bool			m_always_cow;
	bool			m_fail_unmount;
	bool			m_finobt_nores; /* no per-AG finobt resv. */
	bool			m_update_sb;	/* sb needs update in mount */

	/*
	 * Bitsets of per-fs metadata that have been checked and/or are sick.
	 * Callers must hold m_sb_lock to access these two fields.
	 */
	uपूर्णांक8_t			m_fs_checked;
	uपूर्णांक8_t			m_fs_sick;
	/*
	 * Bitsets of rt metadata that have been checked and/or are sick.
	 * Callers must hold m_sb_lock to access this field.
	 */
	uपूर्णांक8_t			m_rt_checked;
	uपूर्णांक8_t			m_rt_sick;

	/*
	 * End of पढ़ो-mostly variables. Frequently written variables and locks
	 * should be placed below this comment from now on. The first variable
	 * here is marked as cacheline aligned so they it is separated from
	 * the पढ़ो-mostly variables.
	 */

	spinlock_t ____cacheline_aligned m_sb_lock; /* sb counter lock */
	काष्ठा percpu_counter	m_icount;	/* allocated inodes counter */
	काष्ठा percpu_counter	m_अगरree;	/* मुक्त inodes counter */
	काष्ठा percpu_counter	m_fdblocks;	/* मुक्त block counter */
	/*
	 * Count of data device blocks reserved क्रम delayed allocations,
	 * including indlen blocks.  Does not include allocated CoW staging
	 * extents or anything related to the rt device.
	 */
	काष्ठा percpu_counter	m_delalloc_blks;
	/*
	 * Global count of allocation btree blocks in use across all AGs. Only
	 * used when perag reservation is enabled. Helps prevent block
	 * reservation from attempting to reserve allocation btree blocks.
	 */
	atomic64_t		m_allocbt_blks;

	काष्ठा radix_tree_root	m_perag_tree;	/* per-ag accounting info */
	spinlock_t		m_perag_lock;	/* lock क्रम m_perag_tree */
	uपूर्णांक64_t		m_resblks;	/* total reserved blocks */
	uपूर्णांक64_t		m_resblks_avail;/* available reserved blocks */
	uपूर्णांक64_t		m_resblks_save;	/* reserved blks @ remount,ro */
	काष्ठा delayed_work	m_reclaim_work;	/* background inode reclaim */
	काष्ठा xfs_kobj		m_kobj;
	काष्ठा xfs_kobj		m_error_kobj;
	काष्ठा xfs_kobj		m_error_meta_kobj;
	काष्ठा xfs_error_cfg	m_error_cfg[XFS_ERR_CLASS_MAX][XFS_ERR_ERRNO_MAX];
	काष्ठा xstats		m_stats;	/* per-fs stats */
	xfs_agnumber_t		m_agfrotor;	/* last ag where space found */
	xfs_agnumber_t		m_agirotor;	/* last ag dir inode alloced */
	spinlock_t		m_agirotor_lock;/* .. and lock protecting it */

	/*
	 * Workqueue item so that we can coalesce multiple inode flush attempts
	 * पूर्णांकo a single flush.
	 */
	काष्ठा work_काष्ठा	m_flush_inodes_work;

	/*
	 * Generation of the filesysyem layout.  This is incremented by each
	 * growfs, and used by the pNFS server to ensure the client updates
	 * its view of the block device once it माला_लो a layout that might
	 * reference the newly added blocks.  Does not need to be persistent
	 * as दीर्घ as we only allow file प्रणाली size increments, but अगर we
	 * ever support shrinks it would have to be persisted in addition
	 * to various other kinds of pain inflicted on the pNFS server.
	 */
	uपूर्णांक32_t		m_generation;
	काष्ठा mutex		m_growlock;	/* growfs mutex */

#अगर_घोषित DEBUG
	/*
	 * Frequency with which errors are injected.  Replaces xfs_etest; the
	 * value stored in here is the inverse of the frequency with which the
	 * error triggers.  1 = always, 2 = half the समय, etc.
	 */
	अचिन्हित पूर्णांक		*m_errortag;
	काष्ठा xfs_kobj		m_errortag_kobj;
#पूर्ण_अगर
पूर्ण xfs_mount_t;

#घोषणा M_IGEO(mp)		(&(mp)->m_ino_geo)

/*
 * Flags क्रम m_flags.
 */
#घोषणा XFS_MOUNT_WSYNC		(1ULL << 0)	/* क्रम nfs - all metadata ops
						   must be synchronous except
						   क्रम space allocations */
#घोषणा XFS_MOUNT_UNMOUNTING	(1ULL << 1)	/* fileप्रणाली is unmounting */
#घोषणा XFS_MOUNT_WAS_CLEAN	(1ULL << 3)
#घोषणा XFS_MOUNT_FS_SHUTDOWN	(1ULL << 4)	/* atomic stop of all fileप्रणाली
						   operations, typically क्रम
						   disk errors in metadata */
#घोषणा XFS_MOUNT_DISCARD	(1ULL << 5)	/* discard unused blocks */
#घोषणा XFS_MOUNT_NOALIGN	(1ULL << 7)	/* turn off stripe alignment
						   allocations */
#घोषणा XFS_MOUNT_ATTR2		(1ULL << 8)	/* allow use of attr2 क्रमmat */
#घोषणा XFS_MOUNT_GRPID		(1ULL << 9)	/* group-ID asचिन्हित from directory */
#घोषणा XFS_MOUNT_NORECOVERY	(1ULL << 10)	/* no recovery - dirty fs */
#घोषणा XFS_MOUNT_ALLOCSIZE	(1ULL << 12)	/* specअगरied allocation size */
#घोषणा XFS_MOUNT_SMALL_INUMS	(1ULL << 14)	/* user wants 32bit inodes */
#घोषणा XFS_MOUNT_32BITINODES	(1ULL << 15)	/* inode32 allocator active */
#घोषणा XFS_MOUNT_NOUUID	(1ULL << 16)	/* ignore uuid during mount */
#घोषणा XFS_MOUNT_IKEEP		(1ULL << 18)	/* keep empty inode clusters*/
#घोषणा XFS_MOUNT_SWALLOC	(1ULL << 19)	/* turn on stripe width
						 * allocation */
#घोषणा XFS_MOUNT_RDONLY	(1ULL << 20)	/* पढ़ो-only fs */
#घोषणा XFS_MOUNT_सूचीSYNC	(1ULL << 21)	/* synchronous directory ops */
#घोषणा XFS_MOUNT_LARGEIO	(1ULL << 22)	/* report large preferred
						 * I/O size in stat() */
#घोषणा XFS_MOUNT_खाताSTREAMS	(1ULL << 24)	/* enable the filestreams
						   allocator */
#घोषणा XFS_MOUNT_NOATTR2	(1ULL << 25)	/* disable use of attr2 क्रमmat */
#घोषणा XFS_MOUNT_DAX_ALWAYS	(1ULL << 26)
#घोषणा XFS_MOUNT_DAX_NEVER	(1ULL << 27)

/*
 * Max and min values क्रम mount-option defined I/O
 * pपुनः_स्मृतिation sizes.
 */
#घोषणा XFS_MAX_IO_LOG		30	/* 1G */
#घोषणा XFS_MIN_IO_LOG		PAGE_SHIFT

#घोषणा XFS_LAST_UNMOUNT_WAS_CLEAN(mp)	\
				((mp)->m_flags & XFS_MOUNT_WAS_CLEAN)
#घोषणा XFS_FORCED_SHUTDOWN(mp)	((mp)->m_flags & XFS_MOUNT_FS_SHUTDOWN)
व्योम xfs_करो_क्रमce_shutकरोwn(काष्ठा xfs_mount *mp, पूर्णांक flags, अक्षर *fname,
		पूर्णांक lnnum);
#घोषणा xfs_क्रमce_shutकरोwn(m,f)	\
	xfs_करो_क्रमce_shutकरोwn(m, f, __खाता__, __LINE__)

#घोषणा SHUTDOWN_META_IO_ERROR	0x0001	/* ग_लिखो attempt to metadata failed */
#घोषणा SHUTDOWN_LOG_IO_ERROR	0x0002	/* ग_लिखो attempt to the log failed */
#घोषणा SHUTDOWN_FORCE_UMOUNT	0x0004	/* shutकरोwn from a क्रमced unmount */
#घोषणा SHUTDOWN_CORRUPT_INCORE	0x0008	/* corrupt in-memory data काष्ठाures */

/*
 * Flags क्रम xfs_mountfs
 */
#घोषणा XFS_MFSI_QUIET		0x40	/* Be silent अगर mount errors found */

अटल अंतरभूत xfs_agnumber_t
xfs_daddr_to_agno(काष्ठा xfs_mount *mp, xfs_daddr_t d)
अणु
	xfs_rfsblock_t ld = XFS_BB_TO_FSBT(mp, d);
	करो_भाग(ld, mp->m_sb.sb_agblocks);
	वापस (xfs_agnumber_t) ld;
पूर्ण

अटल अंतरभूत xfs_agblock_t
xfs_daddr_to_agbno(काष्ठा xfs_mount *mp, xfs_daddr_t d)
अणु
	xfs_rfsblock_t ld = XFS_BB_TO_FSBT(mp, d);
	वापस (xfs_agblock_t) करो_भाग(ld, mp->m_sb.sb_agblocks);
पूर्ण

/* per-AG block reservation data काष्ठाures*/
काष्ठा xfs_ag_resv अणु
	/* number of blocks originally reserved here */
	xfs_extlen_t			ar_orig_reserved;
	/* number of blocks reserved here */
	xfs_extlen_t			ar_reserved;
	/* number of blocks originally asked क्रम */
	xfs_extlen_t			ar_asked;
पूर्ण;

/*
 * Per-ag incore काष्ठाure, copies of inक्रमmation in agf and agi, to improve the
 * perक्रमmance of allocation group selection.
 */
प्रकार काष्ठा xfs_perag अणु
	काष्ठा xfs_mount *pag_mount;	/* owner fileप्रणाली */
	xfs_agnumber_t	pag_agno;	/* AG this काष्ठाure beदीर्घs to */
	atomic_t	pag_ref;	/* perag reference count */
	अक्षर		pagf_init;	/* this agf's entry is initialized */
	अक्षर		pagi_init;	/* this agi's entry is initialized */
	अक्षर		pagf_metadata;	/* the agf is preferred to be metadata */
	अक्षर		pagi_inodeok;	/* The agi is ok क्रम inodes */
	uपूर्णांक8_t		pagf_levels[XFS_BTNUM_AGF];
					/* # of levels in bno & cnt btree */
	bool		pagf_agflreset; /* agfl requires reset beक्रमe use */
	uपूर्णांक32_t	pagf_flcount;	/* count of blocks in मुक्तlist */
	xfs_extlen_t	pagf_मुक्तblks;	/* total मुक्त blocks */
	xfs_extlen_t	pagf_दीर्घest;	/* दीर्घest मुक्त space */
	uपूर्णांक32_t	pagf_btreeblks;	/* # of blocks held in AGF btrees */
	xfs_agino_t	pagi_मुक्तcount;	/* number of मुक्त inodes */
	xfs_agino_t	pagi_count;	/* number of allocated inodes */

	/*
	 * Inode allocation search lookup optimisation.
	 * If the pagino matches, the search क्रम new inodes
	 * करोesn't need to search the near ones again straight away
	 */
	xfs_agino_t	pagl_pagino;
	xfs_agino_t	pagl_leftrec;
	xfs_agino_t	pagl_rightrec;

	/*
	 * Bitsets of per-ag metadata that have been checked and/or are sick.
	 * Callers should hold pag_state_lock beक्रमe accessing this field.
	 */
	uपूर्णांक16_t	pag_checked;
	uपूर्णांक16_t	pag_sick;
	spinlock_t	pag_state_lock;

	spinlock_t	pagb_lock;	/* lock क्रम pagb_tree */
	काष्ठा rb_root	pagb_tree;	/* ordered tree of busy extents */
	अचिन्हित पूर्णांक	pagb_gen;	/* generation count क्रम pagb_tree */
	रुको_queue_head_t pagb_रुको;	/* woken when pagb_gen changes */

	atomic_t        pagf_fstrms;    /* # of filestreams active in this AG */

	spinlock_t	pag_ici_lock;	/* incore inode cache lock */
	काष्ठा radix_tree_root pag_ici_root;	/* incore inode cache root */
	पूर्णांक		pag_ici_reclaimable;	/* reclaimable inodes */
	अचिन्हित दीर्घ	pag_ici_reclaim_cursor;	/* reclaim restart poपूर्णांक */

	/* buffer cache index */
	spinlock_t	pag_buf_lock;	/* lock क्रम pag_buf_hash */
	काष्ठा rhashtable pag_buf_hash;

	/* क्रम rcu-safe मुक्तing */
	काष्ठा rcu_head	rcu_head;
	पूर्णांक		pagb_count;	/* pagb slots in use */

	/* Blocks reserved क्रम all kinds of metadata. */
	काष्ठा xfs_ag_resv	pag_meta_resv;
	/* Blocks reserved क्रम the reverse mapping btree. */
	काष्ठा xfs_ag_resv	pag_rmapbt_resv;

	/* background pपुनः_स्मृति block trimming */
	काष्ठा delayed_work	pag_blockgc_work;

	/* reference count */
	uपूर्णांक8_t			pagf_refcount_level;

	/*
	 * Unlinked inode inक्रमmation.  This incore inक्रमmation reflects
	 * data stored in the AGI, so callers must hold the AGI buffer lock
	 * or have some other means to control concurrency.
	 */
	काष्ठा rhashtable	pagi_unlinked_hash;
पूर्ण xfs_perag_t;

अटल अंतरभूत काष्ठा xfs_ag_resv *
xfs_perag_resv(
	काष्ठा xfs_perag	*pag,
	क्रमागत xfs_ag_resv_type	type)
अणु
	चयन (type) अणु
	हाल XFS_AG_RESV_METADATA:
		वापस &pag->pag_meta_resv;
	हाल XFS_AG_RESV_RMAPBT:
		वापस &pag->pag_rmapbt_resv;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

पूर्णांक xfs_buf_hash_init(xfs_perag_t *pag);
व्योम xfs_buf_hash_destroy(xfs_perag_t *pag);

बाह्य व्योम	xfs_uuid_table_मुक्त(व्योम);
बाह्य uपूर्णांक64_t xfs_शेष_resblks(xfs_mount_t *mp);
बाह्य पूर्णांक	xfs_mountfs(xfs_mount_t *mp);
बाह्य पूर्णांक	xfs_initialize_perag(xfs_mount_t *mp, xfs_agnumber_t agcount,
				     xfs_agnumber_t *maxagi);
बाह्य व्योम	xfs_unmountfs(xfs_mount_t *);

बाह्य पूर्णांक	xfs_mod_fdblocks(काष्ठा xfs_mount *mp, पूर्णांक64_t delta,
				 bool reserved);
बाह्य पूर्णांक	xfs_mod_frextents(काष्ठा xfs_mount *mp, पूर्णांक64_t delta);

बाह्य पूर्णांक	xfs_पढ़ोsb(xfs_mount_t *, पूर्णांक);
बाह्य व्योम	xfs_मुक्तsb(xfs_mount_t *);
बाह्य bool	xfs_fs_writable(काष्ठा xfs_mount *mp, पूर्णांक level);
बाह्य पूर्णांक	xfs_sb_validate_fsb_count(काष्ठा xfs_sb *, uपूर्णांक64_t);

बाह्य पूर्णांक	xfs_dev_is_पढ़ो_only(काष्ठा xfs_mount *, अक्षर *);

बाह्य व्योम	xfs_set_low_space_thresholds(काष्ठा xfs_mount *);

पूर्णांक	xfs_zero_extent(काष्ठा xfs_inode *ip, xfs_fsblock_t start_fsb,
			xfs_off_t count_fsb);

काष्ठा xfs_error_cfg * xfs_error_get_cfg(काष्ठा xfs_mount *mp,
		पूर्णांक error_class, पूर्णांक error);
व्योम xfs_क्रमce_summary_recalc(काष्ठा xfs_mount *mp);
व्योम xfs_mod_delalloc(काष्ठा xfs_mount *mp, पूर्णांक64_t delta);

#पूर्ण_अगर	/* __XFS_MOUNT_H__ */
