<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_SUPER_H
#घोषणा _FS_CEPH_SUPER_H

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/completion.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/mempool.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/रुको.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/slab.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/refcount.h>
#समावेश <linux/security.h>

#समावेश <linux/ceph/libceph.h>

#अगर_घोषित CONFIG_CEPH_FSCACHE
#घोषणा FSCACHE_USE_NEW_IO_API
#समावेश <linux/fscache.h>
#पूर्ण_अगर

/* f_type in काष्ठा statfs */
#घोषणा CEPH_SUPER_MAGIC 0x00c36400

/* large granularity क्रम statfs utilization stats to facilitate
 * large volume sizes on 32-bit machines. */
#घोषणा CEPH_BLOCK_SHIFT   22  /* 4 MB */
#घोषणा CEPH_BLOCK         (1 << CEPH_BLOCK_SHIFT)

#घोषणा CEPH_MOUNT_OPT_CLEANRECOVER    (1<<1) /* स्वतः reonnect (clean mode) after blocklisted */
#घोषणा CEPH_MOUNT_OPT_सूचीSTAT         (1<<4) /* `cat स_नाम` क्रम stats */
#घोषणा CEPH_MOUNT_OPT_RBYTES          (1<<5) /* dir st_bytes = rbytes */
#घोषणा CEPH_MOUNT_OPT_NOASYNCREADसूची  (1<<7) /* no dcache सूची_पढ़ो */
#घोषणा CEPH_MOUNT_OPT_INO32           (1<<8) /* 32 bit inos */
#घोषणा CEPH_MOUNT_OPT_DCACHE          (1<<9) /* use dcache क्रम सूची_पढ़ो etc */
#घोषणा CEPH_MOUNT_OPT_FSCACHE         (1<<10) /* use fscache */
#घोषणा CEPH_MOUNT_OPT_NOPOOLPERM      (1<<11) /* no pool permission check */
#घोषणा CEPH_MOUNT_OPT_MOUNTWAIT       (1<<12) /* mount रुकोs अगर no mds is up */
#घोषणा CEPH_MOUNT_OPT_NOQUOTADF       (1<<13) /* no root dir quota in statfs */
#घोषणा CEPH_MOUNT_OPT_NOCOPYFROM      (1<<14) /* करोn't use RADOS 'copy-from' op */
#घोषणा CEPH_MOUNT_OPT_ASYNC_सूचीOPS    (1<<15) /* allow async directory ops */

#घोषणा CEPH_MOUNT_OPT_DEFAULT			\
	(CEPH_MOUNT_OPT_DCACHE |		\
	 CEPH_MOUNT_OPT_NOCOPYFROM)

#घोषणा ceph_set_mount_opt(fsc, opt) \
	(fsc)->mount_options->flags |= CEPH_MOUNT_OPT_##opt
#घोषणा ceph_clear_mount_opt(fsc, opt) \
	(fsc)->mount_options->flags &= ~CEPH_MOUNT_OPT_##opt
#घोषणा ceph_test_mount_opt(fsc, opt) \
	(!!((fsc)->mount_options->flags & CEPH_MOUNT_OPT_##opt))

/* max size of osd पढ़ो request, limited by libceph */
#घोषणा CEPH_MAX_READ_SIZE              CEPH_MSG_MAX_DATA_LEN
/* osd has a configurable limitaion of max ग_लिखो size.
 * CEPH_MSG_MAX_DATA_LEN should be small enough. */
#घोषणा CEPH_MAX_WRITE_SIZE		CEPH_MSG_MAX_DATA_LEN
#घोषणा CEPH_RASIZE_DEFAULT             (8192*1024)    /* max पढ़ोahead */
#घोषणा CEPH_MAX_READसूची_DEFAULT        1024
#घोषणा CEPH_MAX_READसूची_BYTES_DEFAULT  (512*1024)
#घोषणा CEPH_SNAPसूचीNAME_DEFAULT        ".snap"

/*
 * Delay telling the MDS we no दीर्घer want caps, in हाल we reखोलो
 * the file.  Delay a minimum amount of समय, even अगर we send a cap
 * message क्रम some other reason.  Otherwise, take the oppotunity to
 * update the mds to aव्योम sending another message later.
 */
#घोषणा CEPH_CAPS_WANTED_DELAY_MIN_DEFAULT      5  /* cap release delay */
#घोषणा CEPH_CAPS_WANTED_DELAY_MAX_DEFAULT     60  /* cap release delay */

काष्ठा ceph_mount_options अणु
	अचिन्हित पूर्णांक flags;

	अचिन्हित पूर्णांक wsize;            /* max ग_लिखो size */
	अचिन्हित पूर्णांक rsize;            /* max पढ़ो size */
	अचिन्हित पूर्णांक rasize;           /* max पढ़ोahead */
	अचिन्हित पूर्णांक congestion_kb;    /* max ग_लिखोback in flight */
	अचिन्हित पूर्णांक caps_wanted_delay_min, caps_wanted_delay_max;
	पूर्णांक caps_max;
	अचिन्हित पूर्णांक max_सूची_पढ़ो;       /* max सूची_पढ़ो result (entries) */
	अचिन्हित पूर्णांक max_सूची_पढ़ो_bytes; /* max सूची_पढ़ो result (bytes) */

	/*
	 * everything above this poपूर्णांक can be स_भेद'd; everything below
	 * is handled in compare_mount_options()
	 */

	अक्षर *snapdir_name;   /* शेष ".snap" */
	अक्षर *mds_namespace;  /* शेष शून्य */
	अक्षर *server_path;    /* शेष शून्य (means "/") */
	अक्षर *fscache_uniq;   /* शेष शून्य */
पूर्ण;

काष्ठा ceph_fs_client अणु
	काष्ठा super_block *sb;

	काष्ठा list_head metric_wakeup;

	काष्ठा ceph_mount_options *mount_options;
	काष्ठा ceph_client *client;

	पूर्णांक mount_state;

	bool blocklisted;

	bool have_copy_from2;

	u32 filp_gen;
	loff_t max_file_size;

	काष्ठा ceph_mds_client *mdsc;

	atomic_दीर्घ_t ग_लिखोback_count;

	काष्ठा workqueue_काष्ठा *inode_wq;
	काष्ठा workqueue_काष्ठा *cap_wq;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_dentry_lru, *debugfs_caps;
	काष्ठा dentry *debugfs_congestion_kb;
	काष्ठा dentry *debugfs_bdi;
	काष्ठा dentry *debugfs_mdsc, *debugfs_mdsmap;
	काष्ठा dentry *debugfs_metric;
	काष्ठा dentry *debugfs_status;
	काष्ठा dentry *debugfs_mds_sessions;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CEPH_FSCACHE
	काष्ठा fscache_cookie *fscache;
#पूर्ण_अगर
पूर्ण;


/*
 * File i/o capability.  This tracks shared state with the metadata
 * server that allows us to cache or ग_लिखोback attributes or to पढ़ो
 * and ग_लिखो data.  For any given inode, we should have one or more
 * capabilities, one issued by each metadata server, and our
 * cumulative access is the OR of all issued capabilities.
 *
 * Each cap is referenced by the inode's i_caps rbtree and by per-mds
 * session capability lists.
 */
काष्ठा ceph_cap अणु
	काष्ठा ceph_inode_info *ci;
	काष्ठा rb_node ci_node;          /* per-ci cap tree */
	काष्ठा ceph_mds_session *session;
	काष्ठा list_head session_caps;   /* per-session caplist */
	u64 cap_id;       /* unique cap id (mds provided) */
	जोड़ अणु
		/* in-use caps */
		काष्ठा अणु
			पूर्णांक issued;       /* latest, from the mds */
			पूर्णांक implemented;  /* implemented superset of
					     issued (क्रम revocation) */
			पूर्णांक mds;	  /* mds index क्रम this cap */
			पूर्णांक mds_wanted;   /* caps wanted from this mds */
		पूर्ण;
		/* caps to release */
		काष्ठा अणु
			u64 cap_ino;
			पूर्णांक queue_release;
		पूर्ण;
	पूर्ण;
	u32 seq, issue_seq, mseq;
	u32 cap_gen;      /* active/stale cycle */
	अचिन्हित दीर्घ last_used;
	काष्ठा list_head caps_item;
पूर्ण;

#घोषणा CHECK_CAPS_AUTHONLY   1  /* only check auth cap */
#घोषणा CHECK_CAPS_FLUSH      2  /* flush any dirty caps */
#घोषणा CHECK_CAPS_NOINVAL    4  /* करोn't invalidate pagecache */

काष्ठा ceph_cap_flush अणु
	u64 tid;
	पूर्णांक caps; /* 0 means capsnap */
	bool wake; /* wake up flush रुकोers when finish ? */
	काष्ठा list_head g_list; // global
	काष्ठा list_head i_list; // per inode
पूर्ण;

/*
 * Snapped cap state that is pending flush to mds.  When a snapshot occurs,
 * we first complete any in-process sync ग_लिखोs and ग_लिखोback any dirty
 * data beक्रमe flushing the snapped state (tracked here) back to the MDS.
 */
काष्ठा ceph_cap_snap अणु
	refcount_t nref;
	काष्ठा list_head ci_item;

	काष्ठा ceph_cap_flush cap_flush;

	u64 follows;
	पूर्णांक issued, dirty;
	काष्ठा ceph_snap_context *context;

	umode_t mode;
	kuid_t uid;
	kgid_t gid;

	काष्ठा ceph_buffer *xattr_blob;
	u64 xattr_version;

	u64 size;
	u64 change_attr;
	काष्ठा बारpec64 mसमय, aसमय, स_समय, bसमय;
	u64 समय_warp_seq;
	u64 truncate_size;
	u32 truncate_seq;
	पूर्णांक writing;   /* a sync ग_लिखो is still in progress */
	पूर्णांक dirty_pages;     /* dirty pages aरुकोing ग_लिखोback */
	bool अंतरभूत_data;
	bool need_flush;
पूर्ण;

अटल अंतरभूत व्योम ceph_put_cap_snap(काष्ठा ceph_cap_snap *capsnap)
अणु
	अगर (refcount_dec_and_test(&capsnap->nref)) अणु
		अगर (capsnap->xattr_blob)
			ceph_buffer_put(capsnap->xattr_blob);
		kमुक्त(capsnap);
	पूर्ण
पूर्ण

/*
 * The frag tree describes how a directory is fragmented, potentially across
 * multiple metadata servers.  It is also used to indicate poपूर्णांकs where
 * metadata authority is delegated, and whether/where metadata is replicated.
 *
 * A _leaf_ frag will be present in the i_fragtree IFF there is
 * delegation info.  That is, अगर mds >= 0 || ndist > 0.
 */
#घोषणा CEPH_MAX_सूचीFRAG_REP 4

काष्ठा ceph_inode_frag अणु
	काष्ठा rb_node node;

	/* fragtree state */
	u32 frag;
	पूर्णांक split_by;         /* i.e. 2^(split_by) children */

	/* delegation and replication info */
	पूर्णांक mds;              /* -1 अगर same authority as parent */
	पूर्णांक ndist;            /* >0 अगर replicated */
	पूर्णांक dist[CEPH_MAX_सूचीFRAG_REP];
पूर्ण;

/*
 * We cache inode xattrs as an encoded blob until they are first used,
 * at which poपूर्णांक we parse them पूर्णांकo an rbtree.
 */
काष्ठा ceph_inode_xattr अणु
	काष्ठा rb_node node;

	स्थिर अक्षर *name;
	पूर्णांक name_len;
	स्थिर अक्षर *val;
	पूर्णांक val_len;
	पूर्णांक dirty;

	पूर्णांक should_मुक्त_name;
	पूर्णांक should_मुक्त_val;
पूर्ण;

/*
 * Ceph dentry state
 */
काष्ठा ceph_dentry_info अणु
	काष्ठा dentry *dentry;
	काष्ठा ceph_mds_session *lease_session;
	काष्ठा list_head lease_list;
	अचिन्हित flags;
	पूर्णांक lease_shared_gen;
	u32 lease_gen;
	u32 lease_seq;
	अचिन्हित दीर्घ lease_renew_after, lease_renew_from;
	अचिन्हित दीर्घ समय;
	u64 offset;
पूर्ण;

#घोषणा CEPH_DENTRY_REFERENCED		1
#घोषणा CEPH_DENTRY_LEASE_LIST		2
#घोषणा CEPH_DENTRY_SHRINK_LIST		4
#घोषणा CEPH_DENTRY_PRIMARY_LINK	8

काष्ठा ceph_inode_xattrs_info अणु
	/*
	 * (still encoded) xattr blob. we aव्योम the overhead of parsing
	 * this until someone actually calls getxattr, etc.
	 *
	 * blob->vec.iov_len == 4 implies there are no xattrs; blob ==
	 * शून्य means we करोn't know.
	*/
	काष्ठा ceph_buffer *blob, *pपुनः_स्मृति_blob;

	काष्ठा rb_root index;
	bool dirty;
	पूर्णांक count;
	पूर्णांक names_size;
	पूर्णांक vals_size;
	u64 version, index_version;
पूर्ण;

/*
 * Ceph inode.
 */
काष्ठा ceph_inode_info अणु
	काष्ठा ceph_vino i_vino;   /* ceph ino + snap */

	spinlock_t i_ceph_lock;

	u64 i_version;
	u64 i_अंतरभूत_version;
	u32 i_समय_warp_seq;

	अचिन्हित दीर्घ i_ceph_flags;
	atomic64_t i_release_count;
	atomic64_t i_ordered_count;
	atomic64_t i_complete_seq[2];

	काष्ठा ceph_dir_layout i_dir_layout;
	काष्ठा ceph_file_layout i_layout;
	काष्ठा ceph_file_layout i_cached_layout;	// क्रम async creates
	अक्षर *i_symlink;

	/* क्रम dirs */
	काष्ठा बारpec64 i_rस_समय;
	u64 i_rbytes, i_rfiles, i_rsubdirs, i_rsnaps;
	u64 i_files, i_subdirs;

	/* quotas */
	u64 i_max_bytes, i_max_files;

	s32 i_dir_pin;

	काष्ठा rb_root i_fragtree;
	पूर्णांक i_fragtree_nsplits;
	काष्ठा mutex i_fragtree_mutex;

	काष्ठा ceph_inode_xattrs_info i_xattrs;

	/* capabilities.  रक्षित _both_ by i_ceph_lock and cap->session's
	 * s_mutex. */
	काष्ठा rb_root i_caps;           /* cap list */
	काष्ठा ceph_cap *i_auth_cap;     /* authoritative cap, अगर any */
	अचिन्हित i_dirty_caps, i_flushing_caps;     /* mask of dirtied fields */

	/*
	 * Link to the auth cap's session's s_cap_dirty list. s_cap_dirty
	 * is रक्षित by the mdsc->cap_dirty_lock, but each inभागidual item
	 * is also रक्षित by the inode's i_ceph_lock. Walking s_cap_dirty
	 * requires the mdsc->cap_dirty_lock. List presence क्रम an item can
	 * be tested under the i_ceph_lock. Changing anything requires both.
	 */
	काष्ठा list_head i_dirty_item;

	/*
	 * Link to session's s_cap_flushing list. Protected in a similar
	 * fashion to i_dirty_item, but also by the s_mutex क्रम changes. The
	 * s_cap_flushing list can be walked जबतक holding either the s_mutex
	 * or msdc->cap_dirty_lock. List presence can also be checked जबतक
	 * holding the i_ceph_lock क्रम this inode.
	 */
	काष्ठा list_head i_flushing_item;

	/* we need to track cap ग_लिखोback on a per-cap-bit basis, to allow
	 * overlapping, pipelined cap flushes to the mds.  we can probably
	 * reduce the tid to 8 bits अगर we're concerned about inode size. */
	काष्ठा ceph_cap_flush *i_pपुनः_स्मृति_cap_flush;
	काष्ठा list_head i_cap_flush_list;
	रुको_queue_head_t i_cap_wq;      /* thपढ़ोs रुकोing on a capability */
	अचिन्हित दीर्घ i_hold_caps_max; /* jअगरfies */
	काष्ठा list_head i_cap_delay_list;  /* क्रम delayed cap release to mds */
	काष्ठा ceph_cap_reservation i_cap_migration_resv;
	काष्ठा list_head i_cap_snaps;   /* snapped state pending flush to mds */
	काष्ठा ceph_snap_context *i_head_snapc;  /* set अगर wr_buffer_head > 0 or
						    dirty|flushing caps */
	अचिन्हित i_snap_caps;           /* cap bits क्रम snapped files */

	अचिन्हित दीर्घ i_last_rd;
	अचिन्हित दीर्घ i_last_wr;
	पूर्णांक i_nr_by_mode[CEPH_खाता_MODE_BITS];  /* खोलो file counts */

	काष्ठा mutex i_truncate_mutex;
	u32 i_truncate_seq;        /* last truncate to smaller size */
	u64 i_truncate_size;       /*  and the size we last truncated करोwn to */
	पूर्णांक i_truncate_pending;    /*  still need to call vmtruncate */

	u64 i_max_size;            /* max file size authorized by mds */
	u64 i_reported_size; /* (max_)size reported to or requested of mds */
	u64 i_wanted_max_size;     /* offset we'd like to ग_लिखो too */
	u64 i_requested_max_size;  /* max_size we've requested */

	/* held references to caps */
	पूर्णांक i_pin_ref;
	पूर्णांक i_rd_ref, i_rdcache_ref, i_wr_ref, i_wb_ref, i_fx_ref;
	पूर्णांक i_wrbuffer_ref, i_wrbuffer_ref_head;
	atomic_t i_filelock_ref;
	atomic_t i_shared_gen;       /* increment each समय we get खाता_SHARED */
	u32 i_rdcache_gen;      /* incremented each समय we get खाता_CACHE. */
	u32 i_rdcache_revoking; /* RDCACHE gen to async invalidate, अगर any */

	काष्ठा list_head i_unsafe_dirops; /* uncommitted mds dir ops */
	काष्ठा list_head i_unsafe_iops;   /* uncommitted mds inode ops */
	spinlock_t i_unsafe_lock;

	जोड़ अणु
		काष्ठा ceph_snap_realm *i_snap_realm; /* snap realm (अगर caps) */
		काष्ठा ceph_snapid_map *i_snapid_map; /* snapid -> dev_t */
	पूर्ण;
	पूर्णांक i_snap_realm_counter; /* snap realm (अगर caps) */
	काष्ठा list_head i_snap_realm_item;
	काष्ठा list_head i_snap_flush_item;
	काष्ठा बारpec64 i_bसमय;
	काष्ठा बारpec64 i_snap_bसमय;

	काष्ठा work_काष्ठा i_work;
	अचिन्हित दीर्घ  i_work_mask;

#अगर_घोषित CONFIG_CEPH_FSCACHE
	काष्ठा fscache_cookie *fscache;
#पूर्ण_अगर
	errseq_t i_meta_err;

	काष्ठा inode vfs_inode; /* at end */
पूर्ण;

अटल अंतरभूत काष्ठा ceph_inode_info *
ceph_inode(स्थिर काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा ceph_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा ceph_fs_client *
ceph_inode_to_client(स्थिर काष्ठा inode *inode)
अणु
	वापस (काष्ठा ceph_fs_client *)inode->i_sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा ceph_fs_client *
ceph_sb_to_client(स्थिर काष्ठा super_block *sb)
अणु
	वापस (काष्ठा ceph_fs_client *)sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा ceph_mds_client *
ceph_sb_to_mdsc(स्थिर काष्ठा super_block *sb)
अणु
	वापस (काष्ठा ceph_mds_client *)ceph_sb_to_client(sb)->mdsc;
पूर्ण

अटल अंतरभूत काष्ठा ceph_vino
ceph_vino(स्थिर काष्ठा inode *inode)
अणु
	वापस ceph_inode(inode)->i_vino;
पूर्ण

अटल अंतरभूत u32 ceph_ino_to_ino32(u64 vino)
अणु
	u32 ino = vino & 0xffffffff;
	ino ^= vino >> 32;
	अगर (!ino)
		ino = 2;
	वापस ino;
पूर्ण

/*
 * Inode numbers in cephfs are 64 bits, but inode->i_ino is 32-bits on
 * some arches. We generally करो not use this value inside the ceph driver, but
 * we करो want to set it to something, so that generic vfs code has an
 * appropriate value क्रम tracepoपूर्णांकs and the like.
 */
अटल अंतरभूत ino_t ceph_vino_to_ino_t(काष्ठा ceph_vino vino)
अणु
	अगर (माप(ino_t) == माप(u32))
		वापस ceph_ino_to_ino32(vino.ino);
	वापस (ino_t)vino.ino;
पूर्ण

/* क्रम म_लिखो-style क्रमmatting */
#घोषणा ceph_vinop(i) ceph_inode(i)->i_vino.ino, ceph_inode(i)->i_vino.snap

अटल अंतरभूत u64 ceph_ino(काष्ठा inode *inode)
अणु
	वापस ceph_inode(inode)->i_vino.ino;
पूर्ण

अटल अंतरभूत u64 ceph_snap(काष्ठा inode *inode)
अणु
	वापस ceph_inode(inode)->i_vino.snap;
पूर्ण

/**
 * ceph_present_ino - क्रमmat an inode number क्रम presentation to userland
 * @sb: superblock where the inode lives
 * @ino: inode number to (possibly) convert
 *
 * If the user mounted with the ino32 option, then the 64-bit value needs
 * to be converted to something that can fit inside 32 bits. Note that
 * पूर्णांकernal kernel code never uses this value, so this is entirely क्रम
 * userland consumption.
 */
अटल अंतरभूत u64 ceph_present_ino(काष्ठा super_block *sb, u64 ino)
अणु
	अगर (unlikely(ceph_test_mount_opt(ceph_sb_to_client(sb), INO32)))
		वापस ceph_ino_to_ino32(ino);
	वापस ino;
पूर्ण

अटल अंतरभूत u64 ceph_present_inode(काष्ठा inode *inode)
अणु
	वापस ceph_present_ino(inode->i_sb, ceph_ino(inode));
पूर्ण

अटल अंतरभूत पूर्णांक ceph_ino_compare(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा ceph_vino *pvino = (काष्ठा ceph_vino *)data;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	वापस ci->i_vino.ino == pvino->ino &&
		ci->i_vino.snap == pvino->snap;
पूर्ण

/*
 * The MDS reserves a set of inodes क्रम its own usage. These should never
 * be accessible by clients, and so the MDS has no reason to ever hand these
 * out. The range is CEPH_MDS_INO_MDSसूची_OFFSET..CEPH_INO_SYSTEM_BASE.
 *
 * These come from src/mds/mdstypes.h in the ceph sources.
 */
#घोषणा CEPH_MAX_MDS		0x100
#घोषणा CEPH_NUM_STRAY		10
#घोषणा CEPH_MDS_INO_MDSसूची_OFFSET	(1 * CEPH_MAX_MDS)
#घोषणा CEPH_INO_SYSTEM_BASE		((6*CEPH_MAX_MDS) + (CEPH_MAX_MDS * CEPH_NUM_STRAY))

अटल अंतरभूत bool ceph_vino_is_reserved(स्थिर काष्ठा ceph_vino vino)
अणु
	अगर (vino.ino < CEPH_INO_SYSTEM_BASE &&
	    vino.ino >= CEPH_MDS_INO_MDSसूची_OFFSET) अणु
		WARN_RATELIMIT(1, "Attempt to access reserved inode number 0x%llx", vino.ino);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा inode *ceph_find_inode(काष्ठा super_block *sb,
					    काष्ठा ceph_vino vino)
अणु
	अगर (ceph_vino_is_reserved(vino))
		वापस शून्य;

	/*
	 * NB: The hashval will be run through the fs/inode.c hash function
	 * anyway, so there is no need to squash the inode number करोwn to
	 * 32-bits first. Just use low-order bits on arches with 32-bit दीर्घ.
	 */
	वापस ilookup5(sb, (अचिन्हित दीर्घ)vino.ino, ceph_ino_compare, &vino);
पूर्ण


/*
 * Ceph inode.
 */
#घोषणा CEPH_I_सूची_ORDERED	(1 << 0)  /* dentries in dir are ordered */
#घोषणा CEPH_I_FLUSH		(1 << 2)  /* करो not delay flush of dirty metadata */
#घोषणा CEPH_I_POOL_PERM	(1 << 3)  /* pool rd/wr bits are valid */
#घोषणा CEPH_I_POOL_RD		(1 << 4)  /* can पढ़ो from pool */
#घोषणा CEPH_I_POOL_WR		(1 << 5)  /* can ग_लिखो to pool */
#घोषणा CEPH_I_SEC_INITED	(1 << 6)  /* security initialized */
#घोषणा CEPH_I_KICK_FLUSH	(1 << 7)  /* kick flushing caps */
#घोषणा CEPH_I_FLUSH_SNAPS	(1 << 8)  /* need flush snapss */
#घोषणा CEPH_I_ERROR_WRITE	(1 << 9) /* have seen ग_लिखो errors */
#घोषणा CEPH_I_ERROR_खाताLOCK	(1 << 10) /* have seen file lock errors */
#घोषणा CEPH_I_OसूचीECT		(1 << 11) /* inode in direct I/O mode */
#घोषणा CEPH_ASYNC_CREATE_BIT	(12)	  /* async create in flight क्रम this */
#घोषणा CEPH_I_ASYNC_CREATE	(1 << CEPH_ASYNC_CREATE_BIT)

/*
 * Masks of ceph inode work.
 */
#घोषणा CEPH_I_WORK_WRITEBACK		0
#घोषणा CEPH_I_WORK_INVALIDATE_PAGES	1
#घोषणा CEPH_I_WORK_VMTRUNCATE		2
#घोषणा CEPH_I_WORK_CHECK_CAPS		3
#घोषणा CEPH_I_WORK_FLUSH_SNAPS		4

/*
 * We set the ERROR_WRITE bit when we start seeing ग_लिखो errors on an inode
 * and then clear it when they start succeeding. Note that we करो a lockless
 * check first, and only take the lock अगर it looks like it needs to be changed.
 * The ग_लिखो submission code just takes this as a hपूर्णांक, so we're not too
 * worried अगर a few slip through in either direction.
 */
अटल अंतरभूत व्योम ceph_set_error_ग_लिखो(काष्ठा ceph_inode_info *ci)
अणु
	अगर (!(READ_ONCE(ci->i_ceph_flags) & CEPH_I_ERROR_WRITE)) अणु
		spin_lock(&ci->i_ceph_lock);
		ci->i_ceph_flags |= CEPH_I_ERROR_WRITE;
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ceph_clear_error_ग_लिखो(काष्ठा ceph_inode_info *ci)
अणु
	अगर (READ_ONCE(ci->i_ceph_flags) & CEPH_I_ERROR_WRITE) अणु
		spin_lock(&ci->i_ceph_lock);
		ci->i_ceph_flags &= ~CEPH_I_ERROR_WRITE;
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __ceph_dir_set_complete(काष्ठा ceph_inode_info *ci,
					   दीर्घ दीर्घ release_count,
					   दीर्घ दीर्घ ordered_count)
अणु
	/*
	 * Makes sure operations that setup सूची_पढ़ो cache (update page
	 * cache and i_size) are strongly ordered w.r.t. the following
	 * atomic64_set() operations.
	 */
	smp_mb();
	atomic64_set(&ci->i_complete_seq[0], release_count);
	atomic64_set(&ci->i_complete_seq[1], ordered_count);
पूर्ण

अटल अंतरभूत व्योम __ceph_dir_clear_complete(काष्ठा ceph_inode_info *ci)
अणु
	atomic64_inc(&ci->i_release_count);
पूर्ण

अटल अंतरभूत व्योम __ceph_dir_clear_ordered(काष्ठा ceph_inode_info *ci)
अणु
	atomic64_inc(&ci->i_ordered_count);
पूर्ण

अटल अंतरभूत bool __ceph_dir_is_complete(काष्ठा ceph_inode_info *ci)
अणु
	वापस atomic64_पढ़ो(&ci->i_complete_seq[0]) ==
		atomic64_पढ़ो(&ci->i_release_count);
पूर्ण

अटल अंतरभूत bool __ceph_dir_is_complete_ordered(काष्ठा ceph_inode_info *ci)
अणु
	वापस  atomic64_पढ़ो(&ci->i_complete_seq[0]) ==
		atomic64_पढ़ो(&ci->i_release_count) &&
		atomic64_पढ़ो(&ci->i_complete_seq[1]) ==
		atomic64_पढ़ो(&ci->i_ordered_count);
पूर्ण

अटल अंतरभूत व्योम ceph_dir_clear_complete(काष्ठा inode *inode)
अणु
	__ceph_dir_clear_complete(ceph_inode(inode));
पूर्ण

अटल अंतरभूत व्योम ceph_dir_clear_ordered(काष्ठा inode *inode)
अणु
	__ceph_dir_clear_ordered(ceph_inode(inode));
पूर्ण

अटल अंतरभूत bool ceph_dir_is_complete_ordered(काष्ठा inode *inode)
अणु
	bool ret = __ceph_dir_is_complete_ordered(ceph_inode(inode));
	smp_rmb();
	वापस ret;
पूर्ण

/* find a specअगरic frag @f */
बाह्य काष्ठा ceph_inode_frag *__ceph_find_frag(काष्ठा ceph_inode_info *ci,
						u32 f);

/*
 * choose fragment क्रम value @v.  copy frag content to pfrag, अगर leaf
 * exists
 */
बाह्य u32 ceph_choose_frag(काष्ठा ceph_inode_info *ci, u32 v,
			    काष्ठा ceph_inode_frag *pfrag,
			    पूर्णांक *found);

अटल अंतरभूत काष्ठा ceph_dentry_info *ceph_dentry(स्थिर काष्ठा dentry *dentry)
अणु
	वापस (काष्ठा ceph_dentry_info *)dentry->d_fsdata;
पूर्ण

/*
 * caps helpers
 */
अटल अंतरभूत bool __ceph_is_any_real_caps(काष्ठा ceph_inode_info *ci)
अणु
	वापस !RB_EMPTY_ROOT(&ci->i_caps);
पूर्ण

बाह्य पूर्णांक __ceph_caps_issued(काष्ठा ceph_inode_info *ci, पूर्णांक *implemented);
बाह्य पूर्णांक __ceph_caps_issued_mask(काष्ठा ceph_inode_info *ci, पूर्णांक mask, पूर्णांक t);
बाह्य पूर्णांक __ceph_caps_issued_mask_metric(काष्ठा ceph_inode_info *ci, पूर्णांक mask,
					  पूर्णांक t);
बाह्य पूर्णांक __ceph_caps_issued_other(काष्ठा ceph_inode_info *ci,
				    काष्ठा ceph_cap *cap);

अटल अंतरभूत पूर्णांक ceph_caps_issued(काष्ठा ceph_inode_info *ci)
अणु
	पूर्णांक issued;
	spin_lock(&ci->i_ceph_lock);
	issued = __ceph_caps_issued(ci, शून्य);
	spin_unlock(&ci->i_ceph_lock);
	वापस issued;
पूर्ण

अटल अंतरभूत पूर्णांक ceph_caps_issued_mask_metric(काष्ठा ceph_inode_info *ci,
					       पूर्णांक mask, पूर्णांक touch)
अणु
	पूर्णांक r;
	spin_lock(&ci->i_ceph_lock);
	r = __ceph_caps_issued_mask_metric(ci, mask, touch);
	spin_unlock(&ci->i_ceph_lock);
	वापस r;
पूर्ण

अटल अंतरभूत पूर्णांक __ceph_caps_dirty(काष्ठा ceph_inode_info *ci)
अणु
	वापस ci->i_dirty_caps | ci->i_flushing_caps;
पूर्ण
बाह्य काष्ठा ceph_cap_flush *ceph_alloc_cap_flush(व्योम);
बाह्य व्योम ceph_मुक्त_cap_flush(काष्ठा ceph_cap_flush *cf);
बाह्य पूर्णांक __ceph_mark_dirty_caps(काष्ठा ceph_inode_info *ci, पूर्णांक mask,
				  काष्ठा ceph_cap_flush **pcf);

बाह्य पूर्णांक __ceph_caps_revoking_other(काष्ठा ceph_inode_info *ci,
				      काष्ठा ceph_cap *ocap, पूर्णांक mask);
बाह्य पूर्णांक ceph_caps_revoking(काष्ठा ceph_inode_info *ci, पूर्णांक mask);
बाह्य पूर्णांक __ceph_caps_used(काष्ठा ceph_inode_info *ci);

अटल अंतरभूत bool __ceph_is_file_खोलोed(काष्ठा ceph_inode_info *ci)
अणु
	वापस ci->i_nr_by_mode[0];
पूर्ण
बाह्य पूर्णांक __ceph_caps_file_wanted(काष्ठा ceph_inode_info *ci);
बाह्य पूर्णांक __ceph_caps_wanted(काष्ठा ceph_inode_info *ci);

/* what the mds thinks we want */
बाह्य पूर्णांक __ceph_caps_mds_wanted(काष्ठा ceph_inode_info *ci, bool check);

बाह्य व्योम ceph_caps_init(काष्ठा ceph_mds_client *mdsc);
बाह्य व्योम ceph_caps_finalize(काष्ठा ceph_mds_client *mdsc);
बाह्य व्योम ceph_adjust_caps_max_min(काष्ठा ceph_mds_client *mdsc,
				     काष्ठा ceph_mount_options *fsopt);
बाह्य पूर्णांक ceph_reserve_caps(काष्ठा ceph_mds_client *mdsc,
			     काष्ठा ceph_cap_reservation *ctx, पूर्णांक need);
बाह्य व्योम ceph_unreserve_caps(काष्ठा ceph_mds_client *mdsc,
			       काष्ठा ceph_cap_reservation *ctx);
बाह्य व्योम ceph_reservation_status(काष्ठा ceph_fs_client *client,
				    पूर्णांक *total, पूर्णांक *avail, पूर्णांक *used,
				    पूर्णांक *reserved, पूर्णांक *min);



/*
 * we keep buffered सूची_पढ़ो results attached to file->निजी_data
 */
#घोषणा CEPH_F_SYNC     1
#घोषणा CEPH_F_ATEND    2

काष्ठा ceph_file_info अणु
	लघु भ_शेषe;     /* initialized on खोलो */
	लघु flags;     /* CEPH_F_* */

	spinlock_t rw_contexts_lock;
	काष्ठा list_head rw_contexts;

	errseq_t meta_err;
	u32 filp_gen;
	atomic_t num_locks;
पूर्ण;

काष्ठा ceph_dir_file_info अणु
	काष्ठा ceph_file_info file_info;

	/* सूची_पढ़ो: position within the dir */
	u32 frag;
	काष्ठा ceph_mds_request *last_सूची_पढ़ो;

	/* सूची_पढ़ो: position within a frag */
	अचिन्हित next_offset;  /* offset of next chunk (last_name's + 1) */
	अक्षर *last_name;       /* last entry in previous chunk */
	दीर्घ दीर्घ dir_release_count;
	दीर्घ दीर्घ dir_ordered_count;
	पूर्णांक सूची_पढ़ो_cache_idx;

	/* used क्रम -o dirstat पढ़ो() on directory thing */
	अक्षर *dir_info;
	पूर्णांक dir_info_len;
पूर्ण;

काष्ठा ceph_rw_context अणु
	काष्ठा list_head list;
	काष्ठा task_काष्ठा *thपढ़ो;
	पूर्णांक caps;
पूर्ण;

#घोषणा CEPH_DEFINE_RW_CONTEXT(_name, _caps)	\
	काष्ठा ceph_rw_context _name = अणु	\
		.thपढ़ो = current,		\
		.caps = _caps,			\
	पूर्ण

अटल अंतरभूत व्योम ceph_add_rw_context(काष्ठा ceph_file_info *cf,
				       काष्ठा ceph_rw_context *ctx)
अणु
	spin_lock(&cf->rw_contexts_lock);
	list_add(&ctx->list, &cf->rw_contexts);
	spin_unlock(&cf->rw_contexts_lock);
पूर्ण

अटल अंतरभूत व्योम ceph_del_rw_context(काष्ठा ceph_file_info *cf,
				       काष्ठा ceph_rw_context *ctx)
अणु
	spin_lock(&cf->rw_contexts_lock);
	list_del(&ctx->list);
	spin_unlock(&cf->rw_contexts_lock);
पूर्ण

अटल अंतरभूत काष्ठा ceph_rw_context*
ceph_find_rw_context(काष्ठा ceph_file_info *cf)
अणु
	काष्ठा ceph_rw_context *ctx, *found = शून्य;
	spin_lock(&cf->rw_contexts_lock);
	list_क्रम_each_entry(ctx, &cf->rw_contexts, list) अणु
		अगर (ctx->thपढ़ो == current) अणु
			found = ctx;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&cf->rw_contexts_lock);
	वापस found;
पूर्ण

काष्ठा ceph_सूची_पढ़ो_cache_control अणु
	काष्ठा page  *page;
	काष्ठा dentry **dentries;
	पूर्णांक index;
पूर्ण;

/*
 * A "snap realm" describes a subset of the file hierarchy sharing
 * the same set of snapshots that apply to it.  The realms themselves
 * are organized पूर्णांकo a hierarchy, such that children inherit (some of)
 * the snapshots of their parents.
 *
 * All inodes within the realm that have capabilities are linked पूर्णांकo a
 * per-realm list.
 */
काष्ठा ceph_snap_realm अणु
	u64 ino;
	काष्ठा inode *inode;
	atomic_t nref;
	काष्ठा rb_node node;

	u64 created, seq;
	u64 parent_ino;
	u64 parent_since;   /* snapid when our current parent became so */

	u64 *prior_parent_snaps;      /* snaps inherited from any parents we */
	u32 num_prior_parent_snaps;   /*  had prior to parent_since */
	u64 *snaps;                   /* snaps specअगरic to this realm */
	u32 num_snaps;

	काष्ठा ceph_snap_realm *parent;
	काष्ठा list_head children;       /* list of child realms */
	काष्ठा list_head child_item;

	काष्ठा list_head empty_item;     /* अगर i have ref==0 */

	काष्ठा list_head dirty_item;     /* अगर realm needs new context */

	/* the current set of snaps क्रम this realm */
	काष्ठा ceph_snap_context *cached_context;

	काष्ठा list_head inodes_with_caps;
	spinlock_t inodes_with_caps_lock;
पूर्ण;

अटल अंतरभूत पूर्णांक शेष_congestion_kb(व्योम)
अणु
	पूर्णांक congestion_kb;

	/*
	 * Copied from NFS
	 *
	 * congestion size, scale with available memory.
	 *
	 *  64MB:    8192k
	 * 128MB:   11585k
	 * 256MB:   16384k
	 * 512MB:   23170k
	 *   1GB:   32768k
	 *   2GB:   46340k
	 *   4GB:   65536k
	 *   8GB:   92681k
	 *  16GB:  131072k
	 *
	 * This allows larger machines to have larger/more transfers.
	 * Limit the शेष to 256M
	 */
	congestion_kb = (16*पूर्णांक_वर्ग_मूल(totalram_pages())) << (PAGE_SHIFT-10);
	अगर (congestion_kb > 256*1024)
		congestion_kb = 256*1024;

	वापस congestion_kb;
पूर्ण


/* super.c */
बाह्य पूर्णांक ceph_क्रमce_reconnect(काष्ठा super_block *sb);
/* snap.c */
काष्ठा ceph_snap_realm *ceph_lookup_snap_realm(काष्ठा ceph_mds_client *mdsc,
					       u64 ino);
बाह्य व्योम ceph_get_snap_realm(काष्ठा ceph_mds_client *mdsc,
				काष्ठा ceph_snap_realm *realm);
बाह्य व्योम ceph_put_snap_realm(काष्ठा ceph_mds_client *mdsc,
				काष्ठा ceph_snap_realm *realm);
बाह्य पूर्णांक ceph_update_snap_trace(काष्ठा ceph_mds_client *m,
				  व्योम *p, व्योम *e, bool deletion,
				  काष्ठा ceph_snap_realm **realm_ret);
बाह्य व्योम ceph_handle_snap(काष्ठा ceph_mds_client *mdsc,
			     काष्ठा ceph_mds_session *session,
			     काष्ठा ceph_msg *msg);
बाह्य व्योम ceph_queue_cap_snap(काष्ठा ceph_inode_info *ci);
बाह्य पूर्णांक __ceph_finish_cap_snap(काष्ठा ceph_inode_info *ci,
				  काष्ठा ceph_cap_snap *capsnap);
बाह्य व्योम ceph_cleanup_empty_realms(काष्ठा ceph_mds_client *mdsc);

बाह्य काष्ठा ceph_snapid_map *ceph_get_snapid_map(काष्ठा ceph_mds_client *mdsc,
						   u64 snap);
बाह्य व्योम ceph_put_snapid_map(काष्ठा ceph_mds_client* mdsc,
				काष्ठा ceph_snapid_map *sm);
बाह्य व्योम ceph_trim_snapid_map(काष्ठा ceph_mds_client *mdsc);
बाह्य व्योम ceph_cleanup_snapid_map(काष्ठा ceph_mds_client *mdsc);


/*
 * a cap_snap is "pending" अगर it is still aरुकोing an in-progress
 * sync ग_लिखो (that may/may not still update size, mसमय, etc.).
 */
अटल अंतरभूत bool __ceph_have_pending_cap_snap(काष्ठा ceph_inode_info *ci)
अणु
	वापस !list_empty(&ci->i_cap_snaps) &&
	       list_last_entry(&ci->i_cap_snaps, काष्ठा ceph_cap_snap,
			       ci_item)->writing;
पूर्ण

/* inode.c */
काष्ठा ceph_mds_reply_info_in;
काष्ठा ceph_mds_reply_dirfrag;

बाह्य स्थिर काष्ठा inode_operations ceph_file_iops;

बाह्य काष्ठा inode *ceph_alloc_inode(काष्ठा super_block *sb);
बाह्य व्योम ceph_evict_inode(काष्ठा inode *inode);
बाह्य व्योम ceph_मुक्त_inode(काष्ठा inode *inode);

बाह्य काष्ठा inode *ceph_get_inode(काष्ठा super_block *sb,
				    काष्ठा ceph_vino vino);
बाह्य काष्ठा inode *ceph_get_snapdir(काष्ठा inode *parent);
बाह्य पूर्णांक ceph_fill_file_size(काष्ठा inode *inode, पूर्णांक issued,
			       u32 truncate_seq, u64 truncate_size, u64 size);
बाह्य व्योम ceph_fill_file_समय(काष्ठा inode *inode, पूर्णांक issued,
				u64 समय_warp_seq, काष्ठा बारpec64 *स_समय,
				काष्ठा बारpec64 *mसमय,
				काष्ठा बारpec64 *aसमय);
बाह्य पूर्णांक ceph_fill_inode(काष्ठा inode *inode, काष्ठा page *locked_page,
		    काष्ठा ceph_mds_reply_info_in *iinfo,
		    काष्ठा ceph_mds_reply_dirfrag *dirinfo,
		    काष्ठा ceph_mds_session *session, पूर्णांक cap_भ_शेषe,
		    काष्ठा ceph_cap_reservation *caps_reservation);
बाह्य पूर्णांक ceph_fill_trace(काष्ठा super_block *sb,
			   काष्ठा ceph_mds_request *req);
बाह्य पूर्णांक ceph_सूची_पढ़ो_prepopulate(काष्ठा ceph_mds_request *req,
				    काष्ठा ceph_mds_session *session);

बाह्य पूर्णांक ceph_inode_holds_cap(काष्ठा inode *inode, पूर्णांक mask);

बाह्य bool ceph_inode_set_size(काष्ठा inode *inode, loff_t size);
बाह्य व्योम __ceph_करो_pending_vmtruncate(काष्ठा inode *inode);

बाह्य व्योम ceph_async_iput(काष्ठा inode *inode);

व्योम ceph_queue_inode_work(काष्ठा inode *inode, पूर्णांक work_bit);

अटल अंतरभूत व्योम ceph_queue_vmtruncate(काष्ठा inode *inode)
अणु
	ceph_queue_inode_work(inode, CEPH_I_WORK_VMTRUNCATE);
पूर्ण

अटल अंतरभूत व्योम ceph_queue_invalidate(काष्ठा inode *inode)
अणु
	ceph_queue_inode_work(inode, CEPH_I_WORK_INVALIDATE_PAGES);
पूर्ण

अटल अंतरभूत व्योम ceph_queue_ग_लिखोback(काष्ठा inode *inode)
अणु
	ceph_queue_inode_work(inode, CEPH_I_WORK_WRITEBACK);
पूर्ण

अटल अंतरभूत व्योम ceph_queue_check_caps(काष्ठा inode *inode)
अणु
	ceph_queue_inode_work(inode, CEPH_I_WORK_CHECK_CAPS);
पूर्ण

अटल अंतरभूत व्योम ceph_queue_flush_snaps(काष्ठा inode *inode)
अणु
	ceph_queue_inode_work(inode, CEPH_I_WORK_FLUSH_SNAPS);
पूर्ण

बाह्य पूर्णांक __ceph_करो_getattr(काष्ठा inode *inode, काष्ठा page *locked_page,
			     पूर्णांक mask, bool क्रमce);
अटल अंतरभूत पूर्णांक ceph_करो_getattr(काष्ठा inode *inode, पूर्णांक mask, bool क्रमce)
अणु
	वापस __ceph_करो_getattr(inode, शून्य, mask, क्रमce);
पूर्ण
बाह्य पूर्णांक ceph_permission(काष्ठा user_namespace *mnt_userns,
			   काष्ठा inode *inode, पूर्णांक mask);
बाह्य पूर्णांक __ceph_setattr(काष्ठा inode *inode, काष्ठा iattr *attr);
बाह्य पूर्णांक ceph_setattr(काष्ठा user_namespace *mnt_userns,
			काष्ठा dentry *dentry, काष्ठा iattr *attr);
बाह्य पूर्णांक ceph_getattr(काष्ठा user_namespace *mnt_userns,
			स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			u32 request_mask, अचिन्हित पूर्णांक flags);

/* xattr.c */
पूर्णांक __ceph_setxattr(काष्ठा inode *, स्थिर अक्षर *, स्थिर व्योम *, माप_प्रकार, पूर्णांक);
sमाप_प्रकार __ceph_getxattr(काष्ठा inode *, स्थिर अक्षर *, व्योम *, माप_प्रकार);
बाह्य sमाप_प्रकार ceph_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);
बाह्य काष्ठा ceph_buffer *__ceph_build_xattrs_blob(काष्ठा ceph_inode_info *ci);
बाह्य व्योम __ceph_destroy_xattrs(काष्ठा ceph_inode_info *ci);
बाह्य स्थिर काष्ठा xattr_handler *ceph_xattr_handlers[];

काष्ठा ceph_acl_sec_ctx अणु
#अगर_घोषित CONFIG_CEPH_FS_POSIX_ACL
	व्योम *शेष_acl;
	व्योम *acl;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CEPH_FS_SECURITY_LABEL
	व्योम *sec_ctx;
	u32 sec_ctxlen;
#पूर्ण_अगर
	काष्ठा ceph_pagelist *pagelist;
पूर्ण;

#अगर_घोषित CONFIG_SECURITY
बाह्य bool ceph_security_xattr_deadlock(काष्ठा inode *in);
बाह्य bool ceph_security_xattr_wanted(काष्ठा inode *in);
#अन्यथा
अटल अंतरभूत bool ceph_security_xattr_deadlock(काष्ठा inode *in)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool ceph_security_xattr_wanted(काष्ठा inode *in)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CEPH_FS_SECURITY_LABEL
बाह्य पूर्णांक ceph_security_init_secctx(काष्ठा dentry *dentry, umode_t mode,
				     काष्ठा ceph_acl_sec_ctx *ctx);
अटल अंतरभूत व्योम ceph_security_invalidate_secctx(काष्ठा inode *inode)
अणु
	security_inode_invalidate_secctx(inode);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ceph_security_init_secctx(काष्ठा dentry *dentry, umode_t mode,
					    काष्ठा ceph_acl_sec_ctx *ctx)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ceph_security_invalidate_secctx(काष्ठा inode *inode)
अणु
पूर्ण
#पूर्ण_अगर

व्योम ceph_release_acl_sec_ctx(काष्ठा ceph_acl_sec_ctx *as_ctx);

/* acl.c */
#अगर_घोषित CONFIG_CEPH_FS_POSIX_ACL

काष्ठा posix_acl *ceph_get_acl(काष्ठा inode *, पूर्णांक);
पूर्णांक ceph_set_acl(काष्ठा user_namespace *mnt_userns,
		 काष्ठा inode *inode, काष्ठा posix_acl *acl, पूर्णांक type);
पूर्णांक ceph_pre_init_acls(काष्ठा inode *dir, umode_t *mode,
		       काष्ठा ceph_acl_sec_ctx *as_ctx);
व्योम ceph_init_inode_acls(काष्ठा inode *inode,
			  काष्ठा ceph_acl_sec_ctx *as_ctx);

अटल अंतरभूत व्योम ceph_क्रमget_all_cached_acls(काष्ठा inode *inode)
अणु
       क्रमget_all_cached_acls(inode);
पूर्ण

#अन्यथा

#घोषणा ceph_get_acl शून्य
#घोषणा ceph_set_acl शून्य

अटल अंतरभूत पूर्णांक ceph_pre_init_acls(काष्ठा inode *dir, umode_t *mode,
				     काष्ठा ceph_acl_sec_ctx *as_ctx)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ceph_init_inode_acls(काष्ठा inode *inode,
					काष्ठा ceph_acl_sec_ctx *as_ctx)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ceph_acl_chmod(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ceph_क्रमget_all_cached_acls(काष्ठा inode *inode)
अणु
पूर्ण

#पूर्ण_अगर

/* caps.c */
बाह्य स्थिर अक्षर *ceph_cap_string(पूर्णांक c);
बाह्य व्योम ceph_handle_caps(काष्ठा ceph_mds_session *session,
			     काष्ठा ceph_msg *msg);
बाह्य काष्ठा ceph_cap *ceph_get_cap(काष्ठा ceph_mds_client *mdsc,
				     काष्ठा ceph_cap_reservation *ctx);
बाह्य व्योम ceph_add_cap(काष्ठा inode *inode,
			 काष्ठा ceph_mds_session *session, u64 cap_id,
			 अचिन्हित issued, अचिन्हित wanted,
			 अचिन्हित cap, अचिन्हित seq, u64 realmino, पूर्णांक flags,
			 काष्ठा ceph_cap **new_cap);
बाह्य व्योम __ceph_हटाओ_cap(काष्ठा ceph_cap *cap, bool queue_release);
बाह्य व्योम __ceph_हटाओ_caps(काष्ठा ceph_inode_info *ci);
बाह्य व्योम ceph_put_cap(काष्ठा ceph_mds_client *mdsc,
			 काष्ठा ceph_cap *cap);
बाह्य पूर्णांक ceph_is_any_caps(काष्ठा inode *inode);

बाह्य पूर्णांक ceph_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);
बाह्य पूर्णांक ceph_fsync(काष्ठा file *file, loff_t start, loff_t end,
		      पूर्णांक datasync);
बाह्य व्योम ceph_early_kick_flushing_caps(काष्ठा ceph_mds_client *mdsc,
					  काष्ठा ceph_mds_session *session);
बाह्य व्योम ceph_kick_flushing_caps(काष्ठा ceph_mds_client *mdsc,
				    काष्ठा ceph_mds_session *session);
व्योम ceph_kick_flushing_inode_caps(काष्ठा ceph_mds_session *session,
				   काष्ठा ceph_inode_info *ci);
बाह्य काष्ठा ceph_cap *ceph_get_cap_क्रम_mds(काष्ठा ceph_inode_info *ci,
					     पूर्णांक mds);
बाह्य व्योम ceph_take_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक caps,
				bool snap_rwsem_locked);
बाह्य व्योम ceph_get_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक caps);
बाह्य व्योम ceph_put_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक had);
बाह्य व्योम ceph_put_cap_refs_async(काष्ठा ceph_inode_info *ci, पूर्णांक had);
बाह्य व्योम ceph_put_cap_refs_no_check_caps(काष्ठा ceph_inode_info *ci,
					    पूर्णांक had);
बाह्य व्योम ceph_put_wrbuffer_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक nr,
				       काष्ठा ceph_snap_context *snapc);
बाह्य व्योम ceph_flush_snaps(काष्ठा ceph_inode_info *ci,
			     काष्ठा ceph_mds_session **psession);
बाह्य bool __ceph_should_report_size(काष्ठा ceph_inode_info *ci);
बाह्य व्योम ceph_check_caps(काष्ठा ceph_inode_info *ci, पूर्णांक flags,
			    काष्ठा ceph_mds_session *session);
बाह्य व्योम ceph_check_delayed_caps(काष्ठा ceph_mds_client *mdsc);
बाह्य व्योम ceph_flush_dirty_caps(काष्ठा ceph_mds_client *mdsc);
बाह्य पूर्णांक  ceph_drop_caps_क्रम_unlink(काष्ठा inode *inode);
बाह्य पूर्णांक ceph_encode_inode_release(व्योम **p, काष्ठा inode *inode,
				     पूर्णांक mds, पूर्णांक drop, पूर्णांक unless, पूर्णांक क्रमce);
बाह्य पूर्णांक ceph_encode_dentry_release(व्योम **p, काष्ठा dentry *dn,
				      काष्ठा inode *dir,
				      पूर्णांक mds, पूर्णांक drop, पूर्णांक unless);

बाह्य पूर्णांक ceph_get_caps(काष्ठा file *filp, पूर्णांक need, पूर्णांक want,
			 loff_t enकरोff, पूर्णांक *got);
बाह्य पूर्णांक ceph_try_get_caps(काष्ठा inode *inode,
			     पूर्णांक need, पूर्णांक want, bool nonblock, पूर्णांक *got);

/* क्रम counting खोलो files by mode */
बाह्य व्योम ceph_get_भ_शेषe(काष्ठा ceph_inode_info *ci, पूर्णांक mode, पूर्णांक count);
बाह्य व्योम ceph_put_भ_शेषe(काष्ठा ceph_inode_info *ci, पूर्णांक mode, पूर्णांक count);
बाह्य व्योम __ceph_touch_भ_शेषe(काष्ठा ceph_inode_info *ci,
			       काष्ठा ceph_mds_client *mdsc, पूर्णांक भ_शेषe);

/* addr.c */
बाह्य स्थिर काष्ठा address_space_operations ceph_aops;
बाह्य पूर्णांक ceph_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);
बाह्य पूर्णांक ceph_unअंतरभूत_data(काष्ठा file *filp, काष्ठा page *locked_page);
बाह्य पूर्णांक ceph_pool_perm_check(काष्ठा inode *inode, पूर्णांक need);
बाह्य व्योम ceph_pool_perm_destroy(काष्ठा ceph_mds_client* mdsc);

/* file.c */
बाह्य स्थिर काष्ठा file_operations ceph_file_fops;

बाह्य पूर्णांक ceph_renew_caps(काष्ठा inode *inode, पूर्णांक भ_शेषe);
बाह्य पूर्णांक ceph_खोलो(काष्ठा inode *inode, काष्ठा file *file);
बाह्य पूर्णांक ceph_atomic_खोलो(काष्ठा inode *dir, काष्ठा dentry *dentry,
			    काष्ठा file *file, अचिन्हित flags, umode_t mode);
बाह्य पूर्णांक ceph_release(काष्ठा inode *inode, काष्ठा file *filp);
बाह्य व्योम ceph_fill_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *locked_page,
				  अक्षर *data, माप_प्रकार len);

/* dir.c */
बाह्य स्थिर काष्ठा file_operations ceph_dir_fops;
बाह्य स्थिर काष्ठा file_operations ceph_snapdir_fops;
बाह्य स्थिर काष्ठा inode_operations ceph_dir_iops;
बाह्य स्थिर काष्ठा inode_operations ceph_snapdir_iops;
बाह्य स्थिर काष्ठा dentry_operations ceph_dentry_ops;

बाह्य loff_t ceph_make_fpos(अचिन्हित high, अचिन्हित off, bool hash_order);
बाह्य पूर्णांक ceph_handle_notrace_create(काष्ठा inode *dir, काष्ठा dentry *dentry);
बाह्य काष्ठा dentry *ceph_handle_snapdir(काष्ठा ceph_mds_request *req,
			       काष्ठा dentry *dentry, पूर्णांक err);
बाह्य काष्ठा dentry *ceph_finish_lookup(काष्ठा ceph_mds_request *req,
					 काष्ठा dentry *dentry, पूर्णांक err);

बाह्य व्योम __ceph_dentry_lease_touch(काष्ठा ceph_dentry_info *di);
बाह्य व्योम __ceph_dentry_dir_lease_touch(काष्ठा ceph_dentry_info *di);
बाह्य व्योम ceph_invalidate_dentry_lease(काष्ठा dentry *dentry);
बाह्य पूर्णांक ceph_trim_dentries(काष्ठा ceph_mds_client *mdsc);
बाह्य अचिन्हित ceph_dentry_hash(काष्ठा inode *dir, काष्ठा dentry *dn);
बाह्य व्योम ceph_सूची_पढ़ो_cache_release(काष्ठा ceph_सूची_पढ़ो_cache_control *ctl);

/* ioctl.c */
बाह्य दीर्घ ceph_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/* export.c */
बाह्य स्थिर काष्ठा export_operations ceph_export_ops;
काष्ठा inode *ceph_lookup_inode(काष्ठा super_block *sb, u64 ino);

/* locks.c */
बाह्य __init व्योम ceph_flock_init(व्योम);
बाह्य पूर्णांक ceph_lock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl);
बाह्य पूर्णांक ceph_flock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl);
बाह्य व्योम ceph_count_locks(काष्ठा inode *inode, पूर्णांक *p_num, पूर्णांक *f_num);
बाह्य पूर्णांक ceph_encode_locks_to_buffer(काष्ठा inode *inode,
				       काष्ठा ceph_filelock *flocks,
				       पूर्णांक num_fcntl_locks,
				       पूर्णांक num_flock_locks);
बाह्य पूर्णांक ceph_locks_to_pagelist(काष्ठा ceph_filelock *flocks,
				  काष्ठा ceph_pagelist *pagelist,
				  पूर्णांक num_fcntl_locks, पूर्णांक num_flock_locks);

/* debugfs.c */
बाह्य व्योम ceph_fs_debugfs_init(काष्ठा ceph_fs_client *client);
बाह्य व्योम ceph_fs_debugfs_cleanup(काष्ठा ceph_fs_client *client);

/* quota.c */
अटल अंतरभूत bool __ceph_has_any_quota(काष्ठा ceph_inode_info *ci)
अणु
	वापस ci->i_max_files || ci->i_max_bytes;
पूर्ण

बाह्य व्योम ceph_adjust_quota_realms_count(काष्ठा inode *inode, bool inc);

अटल अंतरभूत व्योम __ceph_update_quota(काष्ठा ceph_inode_info *ci,
				       u64 max_bytes, u64 max_files)
अणु
	bool had_quota, has_quota;
	had_quota = __ceph_has_any_quota(ci);
	ci->i_max_bytes = max_bytes;
	ci->i_max_files = max_files;
	has_quota = __ceph_has_any_quota(ci);

	अगर (had_quota != has_quota)
		ceph_adjust_quota_realms_count(&ci->vfs_inode, has_quota);
पूर्ण

बाह्य व्योम ceph_handle_quota(काष्ठा ceph_mds_client *mdsc,
			      काष्ठा ceph_mds_session *session,
			      काष्ठा ceph_msg *msg);
बाह्य bool ceph_quota_is_max_files_exceeded(काष्ठा inode *inode);
बाह्य bool ceph_quota_is_same_realm(काष्ठा inode *old, काष्ठा inode *new);
बाह्य bool ceph_quota_is_max_bytes_exceeded(काष्ठा inode *inode,
					     loff_t newlen);
बाह्य bool ceph_quota_is_max_bytes_approaching(काष्ठा inode *inode,
						loff_t newlen);
बाह्य bool ceph_quota_update_statfs(काष्ठा ceph_fs_client *fsc,
				     काष्ठा kstatfs *buf);
बाह्य व्योम ceph_cleanup_quotarealms_inodes(काष्ठा ceph_mds_client *mdsc);

#पूर्ण_अगर /* _FS_CEPH_SUPER_H */
