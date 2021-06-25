<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ocfs2.h
 *
 * Defines macros and काष्ठाures used in OCFS2
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_H
#घोषणा OCFS2_H

#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/llist.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/jbd2.h>

/* For जोड़ ocfs2_dlm_lksb */
#समावेश "stackglue.h"

#समावेश "ocfs2_fs.h"
#समावेश "ocfs2_lockid.h"
#समावेश "ocfs2_ioctl.h"

/* For काष्ठा ocfs2_blockcheck_stats */
#समावेश "blockcheck.h"

#समावेश "reservations.h"

#समावेश "filecheck.h"

/* Caching of metadata buffers */

/* Most user visible OCFS2 inodes will have very few pieces of
 * metadata, but larger files (including biपंचांगaps, etc) must be taken
 * पूर्णांकo account when designing an access scheme. We allow a small
 * amount of अंतरभूतd blocks to be stored on an array and grow the
 * काष्ठाure पूर्णांकo a rb tree when necessary. */
#घोषणा OCFS2_CACHE_INFO_MAX_ARRAY 2

/* Flags क्रम ocfs2_caching_info */

क्रमागत ocfs2_caching_info_flags अणु
	/* Indicates that the metadata cache is using the अंतरभूत array */
	OCFS2_CACHE_FL_INLINE	= 1<<1,
पूर्ण;

काष्ठा ocfs2_caching_operations;
काष्ठा ocfs2_caching_info अणु
	/*
	 * The parent काष्ठाure provides the locks, but because the
	 * parent काष्ठाure can dअगरfer, it provides locking operations
	 * to काष्ठा ocfs2_caching_info.
	 */
	स्थिर काष्ठा ocfs2_caching_operations *ci_ops;

	/* next two are रक्षित by trans_inc_lock */
	/* which transaction were we created on? Zero अगर none. */
	अचिन्हित दीर्घ		ci_created_trans;
	/* last transaction we were a part of. */
	अचिन्हित दीर्घ		ci_last_trans;

	/* Cache काष्ठाures */
	अचिन्हित पूर्णांक		ci_flags;
	अचिन्हित पूर्णांक		ci_num_cached;
	जोड़ अणु
	sector_t	ci_array[OCFS2_CACHE_INFO_MAX_ARRAY];
		काष्ठा rb_root	ci_tree;
	पूर्ण ci_cache;
पूर्ण;
/*
 * Need this prototype here instead of in uptodate.h because journal.h
 * uses it.
 */
काष्ठा super_block *ocfs2_metadata_cache_get_super(काष्ठा ocfs2_caching_info *ci);

/* this limits us to 256 nodes
 * अगर we need more, we can करो a kदो_स्मृति क्रम the map */
#घोषणा OCFS2_NODE_MAP_MAX_NODES    256
काष्ठा ocfs2_node_map अणु
	u16 num_nodes;
	अचिन्हित दीर्घ map[BITS_TO_LONGS(OCFS2_NODE_MAP_MAX_NODES)];
पूर्ण;

क्रमागत ocfs2_ast_action अणु
	OCFS2_AST_INVALID = 0,
	OCFS2_AST_ATTACH,
	OCFS2_AST_CONVERT,
	OCFS2_AST_DOWNCONVERT,
पूर्ण;

/* actions क्रम an unlockast function to take. */
क्रमागत ocfs2_unlock_action अणु
	OCFS2_UNLOCK_INVALID = 0,
	OCFS2_UNLOCK_CANCEL_CONVERT,
	OCFS2_UNLOCK_DROP_LOCK,
पूर्ण;

/* ocfs2_lock_res->l_flags flags. */
#घोषणा OCFS2_LOCK_ATTACHED      (0x00000001) /* we have initialized
					       * the lvb */
#घोषणा OCFS2_LOCK_BUSY          (0x00000002) /* we are currently in
					       * dlm_lock */
#घोषणा OCFS2_LOCK_BLOCKED       (0x00000004) /* blocked रुकोing to
					       * करोwnconvert*/
#घोषणा OCFS2_LOCK_LOCAL         (0x00000008) /* newly created inode */
#घोषणा OCFS2_LOCK_NEEDS_REFRESH (0x00000010)
#घोषणा OCFS2_LOCK_REFRESHING    (0x00000020)
#घोषणा OCFS2_LOCK_INITIALIZED   (0x00000040) /* track initialization
					       * क्रम shutकरोwn paths */
#घोषणा OCFS2_LOCK_FREEING       (0x00000080) /* help dlmglue track
					       * when to skip queueing
					       * a lock because it's
					       * about to be
					       * dropped. */
#घोषणा OCFS2_LOCK_QUEUED        (0x00000100) /* queued क्रम करोwnconvert */
#घोषणा OCFS2_LOCK_NOCACHE       (0x00000200) /* करोn't use a holder count */
#घोषणा OCFS2_LOCK_PENDING       (0x00000400) /* This lockres is pending a
						 call to dlm_lock.  Only
						 exists with BUSY set. */
#घोषणा OCFS2_LOCK_UPCONVERT_FINISHING (0x00000800) /* blocks the dc thपढ़ो
						     * from करोwnconverting
						     * beक्रमe the upconvert
						     * has completed */

#घोषणा OCFS2_LOCK_NONBLOCK_FINISHED (0x00001000) /* NONBLOCK cluster
						   * lock has alपढ़ोy
						   * वापसed, करो not block
						   * dc thपढ़ो from
						   * करोwnconverting */

काष्ठा ocfs2_lock_res_ops;

प्रकार व्योम (*ocfs2_lock_callback)(पूर्णांक status, अचिन्हित दीर्घ data);

#अगर_घोषित CONFIG_OCFS2_FS_STATS
काष्ठा ocfs2_lock_stats अणु
	u64		ls_total;	/* Total रुको in NSEC */
	u32		ls_माला_लो;	/* Num acquires */
	u32		ls_fail;	/* Num failed acquires */

	/* Storing max रुको in usecs saves 24 bytes per inode */
	u32		ls_max;		/* Max रुको in USEC */
	u64		ls_last;	/* Last unlock समय in USEC */
पूर्ण;
#पूर्ण_अगर

काष्ठा ocfs2_lock_res अणु
	व्योम                    *l_priv;
	काष्ठा ocfs2_lock_res_ops *l_ops;


	काष्ठा list_head         l_blocked_list;
	काष्ठा list_head         l_mask_रुकोers;
	काष्ठा list_head	 l_holders;

	अचिन्हित दीर्घ		 l_flags;
	अक्षर                     l_name[OCFS2_LOCK_ID_MAX_LEN];
	अचिन्हित पूर्णांक             l_ro_holders;
	अचिन्हित पूर्णांक             l_ex_holders;
	चिन्हित अक्षर		 l_level;
	चिन्हित अक्षर		 l_requested;
	चिन्हित अक्षर		 l_blocking;

	/* Data packed - type क्रमागत ocfs2_lock_type */
	अचिन्हित अक्षर            l_type;

	/* used from AST/BAST funcs. */
	/* Data packed - क्रमागत type ocfs2_ast_action */
	अचिन्हित अक्षर            l_action;
	/* Data packed - क्रमागत type ocfs2_unlock_action */
	अचिन्हित अक्षर            l_unlock_action;
	अचिन्हित पूर्णांक             l_pending_gen;

	spinlock_t               l_lock;

	काष्ठा ocfs2_dlm_lksb    l_lksb;

	रुको_queue_head_t        l_event;

	काष्ठा list_head         l_debug_list;

#अगर_घोषित CONFIG_OCFS2_FS_STATS
	काष्ठा ocfs2_lock_stats  l_lock_prmode;		/* PR mode stats */
	u32                      l_lock_refresh;	/* Disk refreshes */
	u64                      l_lock_रुको;	/* First lock रुको समय */
	काष्ठा ocfs2_lock_stats  l_lock_exmode;		/* EX mode stats */
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map	 l_lockdep_map;
#पूर्ण_अगर
पूर्ण;

क्रमागत ocfs2_orphan_reco_type अणु
	ORPHAN_NO_NEED_TRUNCATE = 0,
	ORPHAN_NEED_TRUNCATE,
पूर्ण;

क्रमागत ocfs2_orphan_scan_state अणु
	ORPHAN_SCAN_ACTIVE,
	ORPHAN_SCAN_INACTIVE
पूर्ण;

काष्ठा ocfs2_orphan_scan अणु
	काष्ठा mutex 		os_lock;
	काष्ठा ocfs2_super 	*os_osb;
	काष्ठा ocfs2_lock_res 	os_lockres;     /* lock to synchronize scans */
	काष्ठा delayed_work 	os_orphan_scan_work;
	समय64_t		os_scanसमय;  /* समय this node ran the scan */
	u32			os_count;      /* tracks node specअगरic scans */
	u32  			os_seqno;       /* tracks cluster wide scans */
	atomic_t		os_state;              /* ACTIVE or INACTIVE */
पूर्ण;

काष्ठा ocfs2_dlm_debug अणु
	काष्ठा kref d_refcnt;
	u32 d_filter_secs;
	काष्ठा list_head d_lockres_tracking;
पूर्ण;

क्रमागत ocfs2_vol_state
अणु
	VOLUME_INIT = 0,
	VOLUME_MOUNTED,
	VOLUME_MOUNTED_QUOTAS,
	VOLUME_DISMOUNTED,
	VOLUME_DISABLED
पूर्ण;

काष्ठा ocfs2_alloc_stats
अणु
	atomic_t moves;
	atomic_t local_data;
	atomic_t biपंचांगap_data;
	atomic_t bg_allocs;
	atomic_t bg_extends;
पूर्ण;

क्रमागत ocfs2_local_alloc_state
अणु
	OCFS2_LA_UNUSED = 0,	/* Local alloc will never be used क्रम
				 * this mountpoपूर्णांक. */
	OCFS2_LA_ENABLED,	/* Local alloc is in use. */
	OCFS2_LA_THROTTLED,	/* Local alloc is in use, but number
				 * of bits has been reduced. */
	OCFS2_LA_DISABLED	/* Local alloc has temporarily been
				 * disabled. */
पूर्ण;

क्रमागत ocfs2_mount_options
अणु
	OCFS2_MOUNT_HB_LOCAL = 1 << 0, /* Local heartbeat */
	OCFS2_MOUNT_BARRIER = 1 << 1,	/* Use block barriers */
	OCFS2_MOUNT_NOINTR  = 1 << 2,   /* Don't catch संकेतs */
	OCFS2_MOUNT_ERRORS_PANIC = 1 << 3, /* Panic on errors */
	OCFS2_MOUNT_DATA_WRITEBACK = 1 << 4, /* No data ordering */
	OCFS2_MOUNT_LOCALFLOCKS = 1 << 5, /* No cluster aware user file locks */
	OCFS2_MOUNT_NOUSERXATTR = 1 << 6, /* No user xattr */
	OCFS2_MOUNT_INODE64 = 1 << 7,	/* Allow inode numbers > 2^32 */
	OCFS2_MOUNT_POSIX_ACL = 1 << 8,	/* Force POSIX access control lists */
	OCFS2_MOUNT_NO_POSIX_ACL = 1 << 9,	/* Disable POSIX access
						   control lists */
	OCFS2_MOUNT_USRQUOTA = 1 << 10, /* We support user quotas */
	OCFS2_MOUNT_GRPQUOTA = 1 << 11, /* We support group quotas */
	OCFS2_MOUNT_COHERENCY_BUFFERED = 1 << 12, /* Allow concurrent O_सूचीECT
						     ग_लिखोs */
	OCFS2_MOUNT_HB_NONE = 1 << 13, /* No heartbeat */
	OCFS2_MOUNT_HB_GLOBAL = 1 << 14, /* Global heartbeat */

	OCFS2_MOUNT_JOURNAL_ASYNC_COMMIT = 1 << 15,  /* Journal Async Commit */
	OCFS2_MOUNT_ERRORS_CONT = 1 << 16, /* Return EIO to the calling process on error */
	OCFS2_MOUNT_ERRORS_ROFS = 1 << 17, /* Change fileप्रणाली to पढ़ो-only on error */
	OCFS2_MOUNT_NOCLUSTER = 1 << 18, /* No cluster aware fileप्रणाली mount */
पूर्ण;

#घोषणा OCFS2_OSB_SOFT_RO	0x0001
#घोषणा OCFS2_OSB_HARD_RO	0x0002
#घोषणा OCFS2_OSB_ERROR_FS	0x0004
#घोषणा OCFS2_DEFAULT_ATIME_QUANTUM	60

काष्ठा ocfs2_journal;
काष्ठा ocfs2_slot_info;
काष्ठा ocfs2_recovery_map;
काष्ठा ocfs2_replay_map;
काष्ठा ocfs2_quota_recovery;
काष्ठा ocfs2_super
अणु
	काष्ठा task_काष्ठा *commit_task;
	काष्ठा super_block *sb;
	काष्ठा inode *root_inode;
	काष्ठा inode *sys_root_inode;
	काष्ठा inode *global_प्रणाली_inodes[NUM_GLOBAL_SYSTEM_INODES];
	काष्ठा inode **local_प्रणाली_inodes;

	काष्ठा ocfs2_slot_info *slot_info;

	u32 *slot_recovery_generations;

	spinlock_t node_map_lock;

	u64 root_blkno;
	u64 प्रणाली_dir_blkno;
	u64 biपंचांगap_blkno;
	u32 biपंचांगap_cpg;
	अक्षर *uuid_str;
	u32 uuid_hash;
	u8 *vol_label;
	u64 first_cluster_group_blkno;
	u32 fs_generation;

	u32 s_feature_compat;
	u32 s_feature_incompat;
	u32 s_feature_ro_compat;

	/* Protects s_next_generation, osb_flags and s_inode_steal_slot.
	 * Could protect more on osb as it's very लघु lived.
	 */
	spinlock_t osb_lock;
	u32 s_next_generation;
	अचिन्हित दीर्घ osb_flags;
	u16 s_inode_steal_slot;
	u16 s_meta_steal_slot;
	atomic_t s_num_inodes_stolen;
	atomic_t s_num_meta_stolen;

	अचिन्हित दीर्घ s_mount_opt;
	अचिन्हित पूर्णांक s_aसमय_quantum;

	अचिन्हित पूर्णांक max_slots;
	अचिन्हित पूर्णांक node_num;
	पूर्णांक slot_num;
	पूर्णांक preferred_slot;
	पूर्णांक s_sectsize_bits;
	पूर्णांक s_clustersize;
	पूर्णांक s_clustersize_bits;
	अचिन्हित पूर्णांक s_xattr_अंतरभूत_size;

	atomic_t vol_state;
	काष्ठा mutex recovery_lock;
	काष्ठा ocfs2_recovery_map *recovery_map;
	काष्ठा ocfs2_replay_map *replay_map;
	काष्ठा task_काष्ठा *recovery_thपढ़ो_task;
	पूर्णांक disable_recovery;
	रुको_queue_head_t checkpoपूर्णांक_event;
	काष्ठा ocfs2_journal *journal;
	अचिन्हित दीर्घ osb_commit_पूर्णांकerval;

	काष्ठा delayed_work		la_enable_wq;

	/*
	 * Must hold local alloc i_mutex and osb->osb_lock to change
	 * local_alloc_bits. Reads can be करोne under either lock.
	 */
	अचिन्हित पूर्णांक local_alloc_bits;
	अचिन्हित पूर्णांक local_alloc_शेष_bits;
	/* osb_clusters_at_boot can become stale! Do not trust it to
	 * be up to date. */
	अचिन्हित पूर्णांक osb_clusters_at_boot;

	क्रमागत ocfs2_local_alloc_state local_alloc_state; /* रक्षित
							 * by osb_lock */

	काष्ठा buffer_head *local_alloc_bh;

	u64 la_last_gd;

	काष्ठा ocfs2_reservation_map	osb_la_resmap;

	अचिन्हित पूर्णांक	osb_resv_level;
	अचिन्हित पूर्णांक	osb_dir_resv_level;

	/* Next two fields are क्रम local node slot recovery during
	 * mount. */
	काष्ठा ocfs2_dinode *local_alloc_copy;
	काष्ठा ocfs2_quota_recovery *quota_rec;

	काष्ठा ocfs2_blockcheck_stats osb_ecc_stats;
	काष्ठा ocfs2_alloc_stats alloc_stats;
	अक्षर dev_str[20];		/* "major,minor" of the device */

	u8 osb_stackflags;

	अक्षर osb_cluster_stack[OCFS2_STACK_LABEL_LEN + 1];
	अक्षर osb_cluster_name[OCFS2_CLUSTER_NAME_LEN + 1];
	काष्ठा ocfs2_cluster_connection *cconn;
	काष्ठा ocfs2_lock_res osb_super_lockres;
	काष्ठा ocfs2_lock_res osb_नाम_lockres;
	काष्ठा ocfs2_lock_res osb_nfs_sync_lockres;
	काष्ठा rw_semaphore nfs_sync_rwlock;
	काष्ठा ocfs2_lock_res osb_trim_fs_lockres;
	काष्ठा mutex obs_trim_fs_mutex;
	काष्ठा ocfs2_dlm_debug *osb_dlm_debug;

	काष्ठा dentry *osb_debug_root;

	रुको_queue_head_t recovery_event;

	spinlock_t dc_task_lock;
	काष्ठा task_काष्ठा *dc_task;
	रुको_queue_head_t dc_event;
	अचिन्हित दीर्घ dc_wake_sequence;
	अचिन्हित दीर्घ dc_work_sequence;

	/*
	 * Any thपढ़ो can add locks to the list, but the करोwnconvert
	 * thपढ़ो is the only one allowed to हटाओ locks. Any change
	 * to this rule requires updating
	 * ocfs2_करोwnconvert_thपढ़ो_करो_work().
	 */
	काष्ठा list_head blocked_lock_list;
	अचिन्हित दीर्घ blocked_lock_count;

	/* List of dquot काष्ठाures to drop last reference to */
	काष्ठा llist_head dquot_drop_list;
	काष्ठा work_काष्ठा dquot_drop_work;

	रुको_queue_head_t		osb_mount_event;

	/* Truncate log info */
	काष्ठा inode			*osb_tl_inode;
	काष्ठा buffer_head		*osb_tl_bh;
	काष्ठा delayed_work		osb_truncate_log_wq;
	atomic_t			osb_tl_disable;
	/*
	 * How many clusters in our truncate log.
	 * It must be रक्षित by osb_tl_inode->i_mutex.
	 */
	अचिन्हित पूर्णांक truncated_clusters;

	काष्ठा ocfs2_node_map		osb_recovering_orphan_dirs;
	अचिन्हित पूर्णांक			*osb_orphan_wipes;
	रुको_queue_head_t		osb_wipe_event;

	काष्ठा ocfs2_orphan_scan	osb_orphan_scan;

	/* used to protect metaecc calculation check of xattr. */
	spinlock_t osb_xattr_lock;

	अचिन्हित पूर्णांक			osb_dx_mask;
	u32				osb_dx_seed[4];

	/* the group we used to allocate inodes. */
	u64				osb_inode_alloc_group;

	/* rb tree root क्रम refcount lock. */
	काष्ठा rb_root	osb_rf_lock_tree;
	काष्ठा ocfs2_refcount_tree *osb_ref_tree_lru;

	काष्ठा mutex प्रणाली_file_mutex;

	/*
	 * OCFS2 needs to schedule several dअगरferent types of work which
	 * require cluster locking, disk I/O, recovery रुकोs, etc. Since these
	 * types of work tend to be heavy we aव्योम using the kernel events
	 * workqueue and schedule on our own.
	 */
	काष्ठा workqueue_काष्ठा *ocfs2_wq;

	/* sysfs directory per partition */
	काष्ठा kset *osb_dev_kset;

	/* file check related stuff */
	काष्ठा ocfs2_filecheck_sysfs_entry osb_fc_ent;
पूर्ण;

#घोषणा OCFS2_SB(sb)	    ((काष्ठा ocfs2_super *)(sb)->s_fs_info)

/* Useful प्रकार क्रम passing around journal access functions */
प्रकार पूर्णांक (*ocfs2_journal_access_func)(handle_t *handle,
					 काष्ठा ocfs2_caching_info *ci,
					 काष्ठा buffer_head *bh, पूर्णांक type);

अटल अंतरभूत पूर्णांक ocfs2_should_order_data(काष्ठा inode *inode)
अणु
	अगर (!S_ISREG(inode->i_mode))
		वापस 0;
	अगर (OCFS2_SB(inode->i_sb)->s_mount_opt & OCFS2_MOUNT_DATA_WRITEBACK)
		वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_sparse_alloc(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_SPARSE_ALLOC)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_ग_लिखोs_unwritten_extents(काष्ठा ocfs2_super *osb)
अणु
	/*
	 * Support क्रम sparse files is a pre-requisite
	 */
	अगर (!ocfs2_sparse_alloc(osb))
		वापस 0;

	अगर (osb->s_feature_ro_compat & OCFS2_FEATURE_RO_COMPAT_UNWRITTEN)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_supports_append_dio(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_APPEND_DIO)
		वापस 1;
	वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक ocfs2_supports_अंतरभूत_data(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_INLINE_DATA)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_supports_xattr(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_XATTR)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_meta_ecc(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_META_ECC)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_supports_indexed_dirs(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_INDEXED_सूचीS)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_supports_discontig_bg(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_DISCONTIG_BG)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_link_max(काष्ठा ocfs2_super *osb)
अणु
	अगर (ocfs2_supports_indexed_dirs(osb))
		वापस OCFS2_DX_LINK_MAX;
	वापस OCFS2_LINK_MAX;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_पढ़ो_links_count(काष्ठा ocfs2_dinode *di)
अणु
	u32 nlink = le16_to_cpu(di->i_links_count);
	u32 hi = le16_to_cpu(di->i_links_count_hi);

	अगर (di->i_dyn_features & cpu_to_le16(OCFS2_INDEXED_सूची_FL))
		nlink |= (hi << OCFS2_LINKS_HI_SHIFT);

	वापस nlink;
पूर्ण

अटल अंतरभूत व्योम ocfs2_set_links_count(काष्ठा ocfs2_dinode *di, u32 nlink)
अणु
	u16 lo, hi;

	lo = nlink;
	hi = nlink >> OCFS2_LINKS_HI_SHIFT;

	di->i_links_count = cpu_to_le16(lo);
	di->i_links_count_hi = cpu_to_le16(hi);
पूर्ण

अटल अंतरभूत व्योम ocfs2_add_links_count(काष्ठा ocfs2_dinode *di, पूर्णांक n)
अणु
	u32 links = ocfs2_पढ़ो_links_count(di);

	links += n;

	ocfs2_set_links_count(di, links);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_refcount_tree(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_REFCOUNT_TREE)
		वापस 1;
	वापस 0;
पूर्ण

/* set / clear functions because cluster events can make these happen
 * in parallel so we want the transitions to be atomic. this also
 * means that any future flags osb_flags must be रक्षित by spinlock
 * too! */
अटल अंतरभूत व्योम ocfs2_set_osb_flag(काष्ठा ocfs2_super *osb,
				      अचिन्हित दीर्घ flag)
अणु
	spin_lock(&osb->osb_lock);
	osb->osb_flags |= flag;
	spin_unlock(&osb->osb_lock);
पूर्ण

अटल अंतरभूत व्योम ocfs2_set_ro_flag(काष्ठा ocfs2_super *osb,
				     पूर्णांक hard)
अणु
	spin_lock(&osb->osb_lock);
	osb->osb_flags &= ~(OCFS2_OSB_SOFT_RO|OCFS2_OSB_HARD_RO);
	अगर (hard)
		osb->osb_flags |= OCFS2_OSB_HARD_RO;
	अन्यथा
		osb->osb_flags |= OCFS2_OSB_SOFT_RO;
	spin_unlock(&osb->osb_lock);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_is_hard_पढ़ोonly(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक ret;

	spin_lock(&osb->osb_lock);
	ret = osb->osb_flags & OCFS2_OSB_HARD_RO;
	spin_unlock(&osb->osb_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_is_soft_पढ़ोonly(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक ret;

	spin_lock(&osb->osb_lock);
	ret = osb->osb_flags & OCFS2_OSB_SOFT_RO;
	spin_unlock(&osb->osb_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_clusterinfo_valid(काष्ठा ocfs2_super *osb)
अणु
	वापस (osb->s_feature_incompat &
		(OCFS2_FEATURE_INCOMPAT_USERSPACE_STACK |
		 OCFS2_FEATURE_INCOMPAT_CLUSTERINFO));
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_userspace_stack(काष्ठा ocfs2_super *osb)
अणु
	अगर (ocfs2_clusterinfo_valid(osb) &&
	    स_भेद(osb->osb_cluster_stack, OCFS2_CLASSIC_CLUSTER_STACK,
		   OCFS2_STACK_LABEL_LEN))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_o2cb_stack(काष्ठा ocfs2_super *osb)
अणु
	अगर (ocfs2_clusterinfo_valid(osb) &&
	    !स_भेद(osb->osb_cluster_stack, OCFS2_CLASSIC_CLUSTER_STACK,
		   OCFS2_STACK_LABEL_LEN))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_cluster_o2cb_global_heartbeat(काष्ठा ocfs2_super *osb)
अणु
	वापस ocfs2_o2cb_stack(osb) &&
		(osb->osb_stackflags & OCFS2_CLUSTER_O2CB_GLOBAL_HEARTBEAT);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_mount_local(काष्ठा ocfs2_super *osb)
अणु
	वापस ((osb->s_feature_incompat & OCFS2_FEATURE_INCOMPAT_LOCAL_MOUNT)
		|| (osb->s_mount_opt & OCFS2_MOUNT_NOCLUSTER));
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_uses_extended_slot_map(काष्ठा ocfs2_super *osb)
अणु
	वापस (osb->s_feature_incompat &
		OCFS2_FEATURE_INCOMPAT_EXTENDED_SLOT_MAP);
पूर्ण


#घोषणा OCFS2_IS_VALID_DINODE(ptr)					\
	(!म_भेद((ptr)->i_signature, OCFS2_INODE_SIGNATURE))

#घोषणा OCFS2_IS_VALID_EXTENT_BLOCK(ptr)				\
	(!म_भेद((ptr)->h_signature, OCFS2_EXTENT_BLOCK_SIGNATURE))

#घोषणा OCFS2_IS_VALID_GROUP_DESC(ptr)					\
	(!म_भेद((ptr)->bg_signature, OCFS2_GROUP_DESC_SIGNATURE))


#घोषणा OCFS2_IS_VALID_XATTR_BLOCK(ptr)					\
	(!म_भेद((ptr)->xb_signature, OCFS2_XATTR_BLOCK_SIGNATURE))

#घोषणा OCFS2_IS_VALID_सूची_TRAILER(ptr)					\
	(!म_भेद((ptr)->db_signature, OCFS2_सूची_TRAILER_SIGNATURE))

#घोषणा OCFS2_IS_VALID_DX_ROOT(ptr)					\
	(!म_भेद((ptr)->dr_signature, OCFS2_DX_ROOT_SIGNATURE))

#घोषणा OCFS2_IS_VALID_DX_LEAF(ptr)					\
	(!म_भेद((ptr)->dl_signature, OCFS2_DX_LEAF_SIGNATURE))

#घोषणा OCFS2_IS_VALID_REFCOUNT_BLOCK(ptr)				\
	(!म_भेद((ptr)->rf_signature, OCFS2_REFCOUNT_BLOCK_SIGNATURE))

अटल अंतरभूत अचिन्हित दीर्घ ino_from_blkno(काष्ठा super_block *sb,
					   u64 blkno)
अणु
	वापस (अचिन्हित दीर्घ)(blkno & (u64)अच_दीर्घ_उच्च);
पूर्ण

अटल अंतरभूत u64 ocfs2_clusters_to_blocks(काष्ठा super_block *sb,
					   u32 clusters)
अणु
	पूर्णांक c_to_b_bits = OCFS2_SB(sb)->s_clustersize_bits -
		sb->s_blocksize_bits;

	वापस (u64)clusters << c_to_b_bits;
पूर्ण

अटल अंतरभूत u32 ocfs2_clusters_क्रम_blocks(काष्ठा super_block *sb,
		u64 blocks)
अणु
	पूर्णांक b_to_c_bits = OCFS2_SB(sb)->s_clustersize_bits -
			sb->s_blocksize_bits;

	blocks += (1 << b_to_c_bits) - 1;
	वापस (u32)(blocks >> b_to_c_bits);
पूर्ण

अटल अंतरभूत u32 ocfs2_blocks_to_clusters(काष्ठा super_block *sb,
					   u64 blocks)
अणु
	पूर्णांक b_to_c_bits = OCFS2_SB(sb)->s_clustersize_bits -
		sb->s_blocksize_bits;

	वापस (u32)(blocks >> b_to_c_bits);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_clusters_क्रम_bytes(काष्ठा super_block *sb,
						    u64 bytes)
अणु
	पूर्णांक cl_bits = OCFS2_SB(sb)->s_clustersize_bits;
	अचिन्हित पूर्णांक clusters;

	bytes += OCFS2_SB(sb)->s_clustersize - 1;
	/* OCFS2 just cannot have enough clusters to overflow this */
	clusters = (अचिन्हित पूर्णांक)(bytes >> cl_bits);

	वापस clusters;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_bytes_to_clusters(काष्ठा super_block *sb,
		u64 bytes)
अणु
	पूर्णांक cl_bits = OCFS2_SB(sb)->s_clustersize_bits;
	अचिन्हित पूर्णांक clusters;

	clusters = (अचिन्हित पूर्णांक)(bytes >> cl_bits);
	वापस clusters;
पूर्ण

अटल अंतरभूत u64 ocfs2_blocks_क्रम_bytes(काष्ठा super_block *sb,
					 u64 bytes)
अणु
	bytes += sb->s_blocksize - 1;
	वापस bytes >> sb->s_blocksize_bits;
पूर्ण

अटल अंतरभूत u64 ocfs2_clusters_to_bytes(काष्ठा super_block *sb,
					  u32 clusters)
अणु
	वापस (u64)clusters << OCFS2_SB(sb)->s_clustersize_bits;
पूर्ण

अटल अंतरभूत u64 ocfs2_block_to_cluster_start(काष्ठा super_block *sb,
					       u64 blocks)
अणु
	पूर्णांक bits = OCFS2_SB(sb)->s_clustersize_bits - sb->s_blocksize_bits;
	अचिन्हित पूर्णांक clusters;

	clusters = ocfs2_blocks_to_clusters(sb, blocks);
	वापस (u64)clusters << bits;
पूर्ण

अटल अंतरभूत u64 ocfs2_align_bytes_to_clusters(काष्ठा super_block *sb,
						u64 bytes)
अणु
	पूर्णांक cl_bits = OCFS2_SB(sb)->s_clustersize_bits;
	अचिन्हित पूर्णांक clusters;

	clusters = ocfs2_clusters_क्रम_bytes(sb, bytes);
	वापस (u64)clusters << cl_bits;
पूर्ण

अटल अंतरभूत u64 ocfs2_align_bytes_to_blocks(काष्ठा super_block *sb,
					      u64 bytes)
अणु
	u64 blocks;

        blocks = ocfs2_blocks_क्रम_bytes(sb, bytes);
	वापस blocks << sb->s_blocksize_bits;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ocfs2_align_bytes_to_sectors(u64 bytes)
अणु
	वापस (अचिन्हित दीर्घ)((bytes + 511) >> 9);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_page_index_to_clusters(काष्ठा super_block *sb,
							अचिन्हित दीर्घ pg_index)
अणु
	u32 clusters = pg_index;
	अचिन्हित पूर्णांक cbits = OCFS2_SB(sb)->s_clustersize_bits;

	अगर (unlikely(PAGE_SHIFT > cbits))
		clusters = pg_index << (PAGE_SHIFT - cbits);
	अन्यथा अगर (PAGE_SHIFT < cbits)
		clusters = pg_index >> (cbits - PAGE_SHIFT);

	वापस clusters;
पूर्ण

/*
 * Find the 1st page index which covers the given clusters.
 */
अटल अंतरभूत pgoff_t ocfs2_align_clusters_to_page_index(काष्ठा super_block *sb,
							u32 clusters)
अणु
	अचिन्हित पूर्णांक cbits = OCFS2_SB(sb)->s_clustersize_bits;
        pgoff_t index = clusters;

	अगर (PAGE_SHIFT > cbits) अणु
		index = (pgoff_t)clusters >> (PAGE_SHIFT - cbits);
	पूर्ण अन्यथा अगर (PAGE_SHIFT < cbits) अणु
		index = (pgoff_t)clusters << (cbits - PAGE_SHIFT);
	पूर्ण

	वापस index;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_pages_per_cluster(काष्ठा super_block *sb)
अणु
	अचिन्हित पूर्णांक cbits = OCFS2_SB(sb)->s_clustersize_bits;
	अचिन्हित पूर्णांक pages_per_cluster = 1;

	अगर (PAGE_SHIFT < cbits)
		pages_per_cluster = 1 << (cbits - PAGE_SHIFT);

	वापस pages_per_cluster;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_megabytes_to_clusters(काष्ठा super_block *sb,
						       अचिन्हित पूर्णांक megs)
अणु
	BUILD_BUG_ON(OCFS2_MAX_CLUSTERSIZE > 1048576);

	वापस megs << (20 - OCFS2_SB(sb)->s_clustersize_bits);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_clusters_to_megabytes(काष्ठा super_block *sb,
						       अचिन्हित पूर्णांक clusters)
अणु
	वापस clusters >> (20 - OCFS2_SB(sb)->s_clustersize_bits);
पूर्ण

अटल अंतरभूत व्योम _ocfs2_set_bit(अचिन्हित पूर्णांक bit, अचिन्हित दीर्घ *biपंचांगap)
अणु
	__set_bit_le(bit, biपंचांगap);
पूर्ण
#घोषणा ocfs2_set_bit(bit, addr) _ocfs2_set_bit((bit), (अचिन्हित दीर्घ *)(addr))

अटल अंतरभूत व्योम _ocfs2_clear_bit(अचिन्हित पूर्णांक bit, अचिन्हित दीर्घ *biपंचांगap)
अणु
	__clear_bit_le(bit, biपंचांगap);
पूर्ण
#घोषणा ocfs2_clear_bit(bit, addr) _ocfs2_clear_bit((bit), (अचिन्हित दीर्घ *)(addr))

#घोषणा ocfs2_test_bit test_bit_le
#घोषणा ocfs2_find_next_zero_bit find_next_zero_bit_le
#घोषणा ocfs2_find_next_bit find_next_bit_le

अटल अंतरभूत व्योम *correct_addr_and_bit_unaligned(पूर्णांक *bit, व्योम *addr)
अणु
#अगर BITS_PER_LONG == 64
	*bit += ((अचिन्हित दीर्घ) addr & 7UL) << 3;
	addr = (व्योम *) ((अचिन्हित दीर्घ) addr & ~7UL);
#या_अगर BITS_PER_LONG == 32
	*bit += ((अचिन्हित दीर्घ) addr & 3UL) << 3;
	addr = (व्योम *) ((अचिन्हित दीर्घ) addr & ~3UL);
#अन्यथा
#त्रुटि "how many bits you are?!"
#पूर्ण_अगर
	वापस addr;
पूर्ण

अटल अंतरभूत व्योम ocfs2_set_bit_unaligned(पूर्णांक bit, व्योम *biपंचांगap)
अणु
	biपंचांगap = correct_addr_and_bit_unaligned(&bit, biपंचांगap);
	ocfs2_set_bit(bit, biपंचांगap);
पूर्ण

अटल अंतरभूत व्योम ocfs2_clear_bit_unaligned(पूर्णांक bit, व्योम *biपंचांगap)
अणु
	biपंचांगap = correct_addr_and_bit_unaligned(&bit, biपंचांगap);
	ocfs2_clear_bit(bit, biपंचांगap);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_test_bit_unaligned(पूर्णांक bit, व्योम *biपंचांगap)
अणु
	biपंचांगap = correct_addr_and_bit_unaligned(&bit, biपंचांगap);
	वापस ocfs2_test_bit(bit, biपंचांगap);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_find_next_zero_bit_unaligned(व्योम *biपंचांगap, पूर्णांक max,
							पूर्णांक start)
अणु
	पूर्णांक fix = 0, ret, पंचांगpmax;
	biपंचांगap = correct_addr_and_bit_unaligned(&fix, biपंचांगap);
	पंचांगpmax = max + fix;
	start += fix;

	ret = ocfs2_find_next_zero_bit(biपंचांगap, पंचांगpmax, start) - fix;
	अगर (ret > max)
		वापस max;
	वापस ret;
पूर्ण

#पूर्ण_अगर  /* OCFS2_H */

