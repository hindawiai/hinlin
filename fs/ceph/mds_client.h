<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_MDS_CLIENT_H
#घोषणा _FS_CEPH_MDS_CLIENT_H

#समावेश <linux/completion.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/refcount.h>
#समावेश <linux/utsname.h>
#समावेश <linux/kसमय.स>

#समावेश <linux/ceph/types.h>
#समावेश <linux/ceph/messenger.h>
#समावेश <linux/ceph/mdsmap.h>
#समावेश <linux/ceph/auth.h>

#समावेश "metric.h"
#समावेश "super.h"

/* The first 8 bits are reserved क्रम old ceph releases */
क्रमागत ceph_feature_type अणु
	CEPHFS_FEATURE_MIMIC = 8,
	CEPHFS_FEATURE_REPLY_ENCODING,
	CEPHFS_FEATURE_RECLAIM_CLIENT,
	CEPHFS_FEATURE_LAZY_CAP_WANTED,
	CEPHFS_FEATURE_MULTI_RECONNECT,
	CEPHFS_FEATURE_DELEG_INO,
	CEPHFS_FEATURE_METRIC_COLLECT,

	CEPHFS_FEATURE_MAX = CEPHFS_FEATURE_METRIC_COLLECT,
पूर्ण;

/*
 * This will always have the highest feature bit value
 * as the last element of the array.
 */
#घोषणा CEPHFS_FEATURES_CLIENT_SUPPORTED अणु	\
	0, 1, 2, 3, 4, 5, 6, 7,			\
	CEPHFS_FEATURE_MIMIC,			\
	CEPHFS_FEATURE_REPLY_ENCODING,		\
	CEPHFS_FEATURE_LAZY_CAP_WANTED,		\
	CEPHFS_FEATURE_MULTI_RECONNECT,		\
	CEPHFS_FEATURE_DELEG_INO,		\
	CEPHFS_FEATURE_METRIC_COLLECT,		\
						\
	CEPHFS_FEATURE_MAX,			\
पूर्ण
#घोषणा CEPHFS_FEATURES_CLIENT_REQUIRED अणुपूर्ण

/*
 * Some lock dependencies:
 *
 * session->s_mutex
 *         mdsc->mutex
 *
 *         mdsc->snap_rwsem
 *
 *         ci->i_ceph_lock
 *                 mdsc->snap_flush_lock
 *                 mdsc->cap_delay_lock
 *
 */

काष्ठा ceph_fs_client;
काष्ठा ceph_cap;

/*
 * parsed info about a single inode.  poपूर्णांकers are पूर्णांकo the encoded
 * on-wire काष्ठाures within the mds reply message payload.
 */
काष्ठा ceph_mds_reply_info_in अणु
	काष्ठा ceph_mds_reply_inode *in;
	काष्ठा ceph_dir_layout dir_layout;
	u32 symlink_len;
	अक्षर *symlink;
	u32 xattr_len;
	अक्षर *xattr_data;
	u64 अंतरभूत_version;
	u32 अंतरभूत_len;
	अक्षर *अंतरभूत_data;
	u32 pool_ns_len;
	अक्षर *pool_ns_data;
	u64 max_bytes;
	u64 max_files;
	s32 dir_pin;
	काष्ठा ceph_बारpec bसमय;
	काष्ठा ceph_बारpec snap_bसमय;
	u64 rsnaps;
	u64 change_attr;
पूर्ण;

काष्ठा ceph_mds_reply_dir_entry अणु
	अक्षर                          *name;
	u32                           name_len;
	काष्ठा ceph_mds_reply_lease   *lease;
	काष्ठा ceph_mds_reply_info_in inode;
	loff_t			      offset;
पूर्ण;

/*
 * parsed info about an mds reply, including inक्रमmation about
 * either: 1) the target inode and/or its parent directory and dentry,
 * and directory contents (क्रम सूची_पढ़ो results), or
 * 2) the file range lock info (क्रम fcntl F_GETLK results).
 */
काष्ठा ceph_mds_reply_info_parsed अणु
	काष्ठा ceph_mds_reply_head    *head;

	/* trace */
	काष्ठा ceph_mds_reply_info_in diri, targeti;
	काष्ठा ceph_mds_reply_dirfrag *dirfrag;
	अक्षर                          *dname;
	u32                           dname_len;
	काष्ठा ceph_mds_reply_lease   *dlease;

	/* extra */
	जोड़ अणु
		/* क्रम fcntl F_GETLK results */
		काष्ठा ceph_filelock *filelock_reply;

		/* क्रम सूची_पढ़ो results */
		काष्ठा अणु
			काष्ठा ceph_mds_reply_dirfrag *dir_dir;
			माप_प्रकार			      dir_buf_size;
			पूर्णांक                           dir_nr;
			bool			      dir_end;
			bool			      dir_complete;
			bool			      hash_order;
			bool			      offset_hash;
			काष्ठा ceph_mds_reply_dir_entry  *dir_entries;
		पूर्ण;

		/* क्रम create results */
		काष्ठा अणु
			bool has_create_ino;
			u64 ino;
		पूर्ण;
	पूर्ण;

	/* encoded blob describing snapshot contexts क्रम certain
	   operations (e.g., खोलो) */
	व्योम *snapblob;
	पूर्णांक snapblob_len;
पूर्ण;


/*
 * cap releases are batched and sent to the MDS en masse.
 *
 * Account क्रम per-message overhead of mds_cap_release header
 * and __le32 क्रम osd epoch barrier trailing field.
 */
#घोषणा CEPH_CAPS_PER_RELEASE ((PAGE_SIZE - माप(u32) -		\
				माप(काष्ठा ceph_mds_cap_release)) /	\
			        माप(काष्ठा ceph_mds_cap_item))


/*
 * state associated with each MDS<->client session
 */
क्रमागत अणु
	CEPH_MDS_SESSION_NEW = 1,
	CEPH_MDS_SESSION_OPENING = 2,
	CEPH_MDS_SESSION_OPEN = 3,
	CEPH_MDS_SESSION_HUNG = 4,
	CEPH_MDS_SESSION_RESTARTING = 5,
	CEPH_MDS_SESSION_RECONNECTING = 6,
	CEPH_MDS_SESSION_CLOSING = 7,
	CEPH_MDS_SESSION_CLOSED = 8,
	CEPH_MDS_SESSION_REJECTED = 9,
पूर्ण;

काष्ठा ceph_mds_session अणु
	काष्ठा ceph_mds_client *s_mdsc;
	पूर्णांक               s_mds;
	पूर्णांक               s_state;
	अचिन्हित दीर्घ     s_ttl;      /* समय until mds समाप्तs us */
	अचिन्हित दीर्घ	  s_features;
	u64               s_seq;      /* incoming msg seq # */
	काष्ठा mutex      s_mutex;    /* serialize session messages */

	काष्ठा ceph_connection s_con;

	काष्ठा ceph_auth_handshake s_auth;

	/* रक्षित by s_gen_ttl_lock */
	spinlock_t        s_gen_ttl_lock;
	u32               s_cap_gen;  /* inc each समय we get mds stale msg */
	अचिन्हित दीर्घ     s_cap_ttl;  /* when session caps expire */

	/* रक्षित by s_cap_lock */
	spinlock_t        s_cap_lock;
	refcount_t        s_ref;
	काष्ठा list_head  s_caps;     /* all caps issued by this session */
	काष्ठा ceph_cap  *s_cap_iterator;
	पूर्णांक               s_nr_caps;
	पूर्णांक               s_num_cap_releases;
	पूर्णांक		  s_cap_reconnect;
	पूर्णांक		  s_पढ़ोonly;
	काष्ठा list_head  s_cap_releases; /* रुकोing cap_release messages */
	काष्ठा work_काष्ठा s_cap_release_work;

	/* See ceph_inode_info->i_dirty_item. */
	काष्ठा list_head  s_cap_dirty;	      /* inodes w/ dirty caps */

	/* See ceph_inode_info->i_flushing_item. */
	काष्ठा list_head  s_cap_flushing;     /* inodes w/ flushing caps */

	अचिन्हित दीर्घ     s_renew_requested; /* last समय we sent a renew req */
	u64               s_renew_seq;

	काष्ठा list_head  s_रुकोing;  /* रुकोing requests */
	काष्ठा list_head  s_unsafe;   /* unsafe requests */
	काष्ठा xarray	  s_delegated_inos;
पूर्ण;

/*
 * modes of choosing which MDS to send a request to
 */
क्रमागत अणु
	USE_ANY_MDS,
	USE_RANDOM_MDS,
	USE_AUTH_MDS,   /* prefer authoritative mds क्रम this metadata item */
पूर्ण;

काष्ठा ceph_mds_request;
काष्ठा ceph_mds_client;

/*
 * request completion callback
 */
प्रकार व्योम (*ceph_mds_request_callback_t) (काष्ठा ceph_mds_client *mdsc,
					     काष्ठा ceph_mds_request *req);
/*
 * रुको क्रम request completion callback
 */
प्रकार पूर्णांक (*ceph_mds_request_रुको_callback_t) (काष्ठा ceph_mds_client *mdsc,
						 काष्ठा ceph_mds_request *req);

/*
 * an in-flight mds request
 */
काष्ठा ceph_mds_request अणु
	u64 r_tid;                   /* transaction id */
	काष्ठा rb_node r_node;
	काष्ठा ceph_mds_client *r_mdsc;

	काष्ठा kref       r_kref;
	पूर्णांक r_op;                    /* mds op code */

	/* operation on what? */
	काष्ठा inode *r_inode;              /* arg1 */
	काष्ठा dentry *r_dentry;            /* arg1 */
	काष्ठा dentry *r_old_dentry;        /* arg2: नाम from or link from */
	काष्ठा inode *r_old_dentry_dir;     /* arg2: old dentry's parent dir */
	अक्षर *r_path1, *r_path2;
	काष्ठा ceph_vino r_ino1, r_ino2;

	काष्ठा inode *r_parent;		    /* parent dir inode */
	काष्ठा inode *r_target_inode;       /* resulting inode */

#घोषणा CEPH_MDS_R_सूचीECT_IS_HASH	(1) /* r_direct_hash is valid */
#घोषणा CEPH_MDS_R_ABORTED		(2) /* call was पातed */
#घोषणा CEPH_MDS_R_GOT_UNSAFE		(3) /* got an unsafe reply */
#घोषणा CEPH_MDS_R_GOT_SAFE		(4) /* got a safe reply */
#घोषणा CEPH_MDS_R_GOT_RESULT		(5) /* got a result */
#घोषणा CEPH_MDS_R_DID_PREPOPULATE	(6) /* prepopulated सूची_पढ़ो */
#घोषणा CEPH_MDS_R_PARENT_LOCKED	(7) /* is r_parent->i_rwsem wlocked? */
#घोषणा CEPH_MDS_R_ASYNC		(8) /* async request */
	अचिन्हित दीर्घ	r_req_flags;

	काष्ठा mutex r_fill_mutex;

	जोड़ ceph_mds_request_args r_args;
	पूर्णांक r_भ_शेषe;        /* file mode, अगर expecting cap */
	स्थिर काष्ठा cred *r_cred;
	पूर्णांक r_request_release_offset;
	काष्ठा बारpec64 r_stamp;

	/* क्रम choosing which mds to send this request to */
	पूर्णांक r_direct_mode;
	u32 r_direct_hash;      /* choose dir frag based on this dentry hash */

	/* data payload is used क्रम xattr ops */
	काष्ठा ceph_pagelist *r_pagelist;

	/* what caps shall we drop? */
	पूर्णांक r_inode_drop, r_inode_unless;
	पूर्णांक r_dentry_drop, r_dentry_unless;
	पूर्णांक r_old_dentry_drop, r_old_dentry_unless;
	काष्ठा inode *r_old_inode;
	पूर्णांक r_old_inode_drop, r_old_inode_unless;

	काष्ठा ceph_msg  *r_request;  /* original request */
	काष्ठा ceph_msg  *r_reply;
	काष्ठा ceph_mds_reply_info_parsed r_reply_info;
	पूर्णांक r_err;


	काष्ठा page *r_locked_page;
	पूर्णांक r_dir_caps;
	पूर्णांक r_num_caps;
	u32               r_सूची_पढ़ो_offset;

	अचिन्हित दीर्घ r_समयout;  /* optional.  jअगरfies, 0 is "wait forever" */
	अचिन्हित दीर्घ r_started;  /* start समय to measure समयout against */
	अचिन्हित दीर्घ r_start_latency;  /* start समय to measure latency */
	अचिन्हित दीर्घ r_end_latency;    /* finish समय to measure latency */
	अचिन्हित दीर्घ r_request_started; /* start समय क्रम mds request only,
					    used to measure lease durations */

	/* link unsafe requests to parent directory, क्रम fsync */
	काष्ठा inode	*r_unsafe_dir;
	काष्ठा list_head r_unsafe_dir_item;

	/* unsafe requests that modअगरy the target inode */
	काष्ठा list_head r_unsafe_target_item;

	काष्ठा ceph_mds_session *r_session;

	पूर्णांक               r_attempts;   /* resend attempts */
	पूर्णांक               r_num_fwd;    /* number of क्रमward attempts */
	पूर्णांक               r_resend_mds; /* mds to resend to next, अगर any*/
	u32               r_sent_on_mseq; /* cap mseq request was sent at*/
	u64		  r_deleg_ino;

	काष्ठा list_head  r_रुको;
	काष्ठा completion r_completion;
	काष्ठा completion r_safe_completion;
	ceph_mds_request_callback_t r_callback;
	ceph_mds_request_रुको_callback_t r_रुको_क्रम_completion;
	काष्ठा list_head  r_unsafe_item;  /* per-session unsafe list item */

	दीर्घ दीर्घ	  r_dir_release_cnt;
	दीर्घ दीर्घ	  r_dir_ordered_cnt;
	पूर्णांक		  r_सूची_पढ़ो_cache_idx;

	काष्ठा ceph_cap_reservation r_caps_reservation;
पूर्ण;

काष्ठा ceph_pool_perm अणु
	काष्ठा rb_node node;
	पूर्णांक perm;
	s64 pool;
	माप_प्रकार pool_ns_len;
	अक्षर pool_ns[];
पूर्ण;

काष्ठा ceph_snapid_map अणु
	काष्ठा rb_node node;
	काष्ठा list_head lru;
	atomic_t ref;
	u64 snap;
	dev_t dev;
	अचिन्हित दीर्घ last_used;
पूर्ण;

/*
 * node क्रम list of quotarealm inodes that are not visible from the fileप्रणाली
 * mountpoपूर्णांक, but required to handle, e.g. quotas.
 */
काष्ठा ceph_quotarealm_inode अणु
	काष्ठा rb_node node;
	u64 ino;
	अचिन्हित दीर्घ समयout; /* last समय a lookup failed क्रम this inode */
	काष्ठा mutex mutex;
	काष्ठा inode *inode;
पूर्ण;

काष्ठा cap_रुको अणु
	काष्ठा list_head	list;
	u64			ino;
	pid_t			tgid;
	पूर्णांक			need;
	पूर्णांक			want;
पूर्ण;

/*
 * mds client state
 */
काष्ठा ceph_mds_client अणु
	काष्ठा ceph_fs_client  *fsc;
	काष्ठा mutex            mutex;         /* all nested काष्ठाures */

	काष्ठा ceph_mdsmap      *mdsmap;
	काष्ठा completion       safe_umount_रुकोers;
	रुको_queue_head_t       session_बंद_wq;
	काष्ठा list_head        रुकोing_क्रम_map;
	पूर्णांक 			mdsmap_err;

	काष्ठा ceph_mds_session **sessions;    /* शून्य क्रम mds अगर no session */
	atomic_t		num_sessions;
	पूर्णांक                     max_sessions;  /* len of sessions array */
	पूर्णांक                     stopping;      /* true अगर shutting करोwn */

	atomic64_t		quotarealms_count; /* # realms with quota */
	/*
	 * We keep a list of inodes we करोn't see in the mountpoपूर्णांक but that we
	 * need to track quota realms.
	 */
	काष्ठा rb_root		quotarealms_inodes;
	काष्ठा mutex		quotarealms_inodes_mutex;

	/*
	 * snap_rwsem will cover cap linkage पूर्णांकo snaprealms, and
	 * realm snap contexts.  (later, we can करो per-realm snap
	 * contexts locks..)  the empty list contains realms with no
	 * references (implying they contain no inodes with caps) that
	 * should be destroyed.
	 */
	u64			last_snap_seq;
	काष्ठा rw_semaphore     snap_rwsem;
	काष्ठा rb_root          snap_realms;
	काष्ठा list_head        snap_empty;
	पूर्णांक			num_snap_realms;
	spinlock_t              snap_empty_lock;  /* protect snap_empty */

	u64                    last_tid;      /* most recent mds request */
	u64                    oldest_tid;    /* oldest incomplete mds request,
						 excluding setfilelock requests */
	काष्ठा rb_root         request_tree;  /* pending mds requests */
	काष्ठा delayed_work    delayed_work;  /* delayed work */
	अचिन्हित दीर्घ    last_renew_caps;  /* last समय we renewed our caps */
	काष्ठा list_head cap_delay_list;   /* caps with delayed release */
	spinlock_t       cap_delay_lock;   /* protects cap_delay_list */
	काष्ठा list_head snap_flush_list;  /* cap_snaps पढ़ोy to flush */
	spinlock_t       snap_flush_lock;

	u64               last_cap_flush_tid;
	काष्ठा list_head  cap_flush_list;
	काष्ठा list_head  cap_dirty_migrating; /* ...that are migration... */
	पूर्णांक               num_cap_flushing; /* # caps we are flushing */
	spinlock_t        cap_dirty_lock;   /* protects above items */
	रुको_queue_head_t cap_flushing_wq;

	काष्ठा work_काष्ठा cap_reclaim_work;
	atomic_t	   cap_reclaim_pending;

	/*
	 * Cap reservations
	 *
	 * Maपूर्णांकain a global pool of pपुनः_स्मृतिated काष्ठा ceph_caps, referenced
	 * by काष्ठा ceph_caps_reservations.  This ensures that we pपुनः_स्मृतिate
	 * memory needed to successfully process an MDS response.  (If an MDS
	 * sends us cap inक्रमmation and we fail to process it, we will have
	 * problems due to the client and MDS being out of sync.)
	 *
	 * Reservations are 'owned' by a ceph_cap_reservation context.
	 */
	spinlock_t	caps_list_lock;
	काष्ठा		list_head caps_list; /* unused (reserved or
						unreserved) */
	काष्ठा		list_head cap_रुको_list;
	पूर्णांक		caps_total_count;    /* total caps allocated */
	पूर्णांक		caps_use_count;      /* in use */
	पूर्णांक		caps_use_max;	     /* max used caps */
	पूर्णांक		caps_reserve_count;  /* unused, reserved */
	पूर्णांक		caps_avail_count;    /* unused, unreserved */
	पूर्णांक		caps_min_count;      /* keep at least this many
						(unreserved) */
	spinlock_t	  dentry_list_lock;
	काष्ठा list_head  dentry_leases;     /* fअगरo list */
	काष्ठा list_head  dentry_dir_leases; /* lru list */

	काष्ठा ceph_client_metric metric;

	spinlock_t		snapid_map_lock;
	काष्ठा rb_root		snapid_map_tree;
	काष्ठा list_head	snapid_map_lru;

	काष्ठा rw_semaphore     pool_perm_rwsem;
	काष्ठा rb_root		pool_perm_tree;

	अक्षर nodename[__NEW_UTS_LEN + 1];
पूर्ण;

बाह्य स्थिर अक्षर *ceph_mds_op_name(पूर्णांक op);

बाह्य bool check_session_state(काष्ठा ceph_mds_session *s);
व्योम inc_session_sequence(काष्ठा ceph_mds_session *s);

बाह्य काष्ठा ceph_mds_session *
__ceph_lookup_mds_session(काष्ठा ceph_mds_client *, पूर्णांक mds);

बाह्य स्थिर अक्षर *ceph_session_state_name(पूर्णांक s);

बाह्य काष्ठा ceph_mds_session *
ceph_get_mds_session(काष्ठा ceph_mds_session *s);
बाह्य व्योम ceph_put_mds_session(काष्ठा ceph_mds_session *s);

बाह्य पूर्णांक ceph_send_msg_mds(काष्ठा ceph_mds_client *mdsc,
			     काष्ठा ceph_msg *msg, पूर्णांक mds);

बाह्य पूर्णांक ceph_mdsc_init(काष्ठा ceph_fs_client *fsc);
बाह्य व्योम ceph_mdsc_बंद_sessions(काष्ठा ceph_mds_client *mdsc);
बाह्य व्योम ceph_mdsc_क्रमce_umount(काष्ठा ceph_mds_client *mdsc);
बाह्य व्योम ceph_mdsc_destroy(काष्ठा ceph_fs_client *fsc);

बाह्य व्योम ceph_mdsc_sync(काष्ठा ceph_mds_client *mdsc);

बाह्य व्योम ceph_invalidate_dir_request(काष्ठा ceph_mds_request *req);
बाह्य पूर्णांक ceph_alloc_सूची_पढ़ो_reply_buffer(काष्ठा ceph_mds_request *req,
					   काष्ठा inode *dir);
बाह्य काष्ठा ceph_mds_request *
ceph_mdsc_create_request(काष्ठा ceph_mds_client *mdsc, पूर्णांक op, पूर्णांक mode);
बाह्य पूर्णांक ceph_mdsc_submit_request(काष्ठा ceph_mds_client *mdsc,
				    काष्ठा inode *dir,
				    काष्ठा ceph_mds_request *req);
बाह्य पूर्णांक ceph_mdsc_करो_request(काष्ठा ceph_mds_client *mdsc,
				काष्ठा inode *dir,
				काष्ठा ceph_mds_request *req);
बाह्य व्योम ceph_mdsc_release_dir_caps(काष्ठा ceph_mds_request *req);
बाह्य व्योम ceph_mdsc_release_dir_caps_no_check(काष्ठा ceph_mds_request *req);
अटल अंतरभूत व्योम ceph_mdsc_get_request(काष्ठा ceph_mds_request *req)
अणु
	kref_get(&req->r_kref);
पूर्ण
बाह्य व्योम ceph_mdsc_release_request(काष्ठा kref *kref);
अटल अंतरभूत व्योम ceph_mdsc_put_request(काष्ठा ceph_mds_request *req)
अणु
	kref_put(&req->r_kref, ceph_mdsc_release_request);
पूर्ण

बाह्य व्योम __ceph_queue_cap_release(काष्ठा ceph_mds_session *session,
				    काष्ठा ceph_cap *cap);
बाह्य व्योम ceph_flush_cap_releases(काष्ठा ceph_mds_client *mdsc,
				    काष्ठा ceph_mds_session *session);
बाह्य व्योम ceph_queue_cap_reclaim_work(काष्ठा ceph_mds_client *mdsc);
बाह्य व्योम ceph_reclaim_caps_nr(काष्ठा ceph_mds_client *mdsc, पूर्णांक nr);
बाह्य पूर्णांक ceph_iterate_session_caps(काष्ठा ceph_mds_session *session,
				     पूर्णांक (*cb)(काष्ठा inode *,
					       काष्ठा ceph_cap *, व्योम *),
				     व्योम *arg);
बाह्य व्योम ceph_mdsc_pre_umount(काष्ठा ceph_mds_client *mdsc);

अटल अंतरभूत व्योम ceph_mdsc_मुक्त_path(अक्षर *path, पूर्णांक len)
अणु
	अगर (!IS_ERR_OR_शून्य(path))
		__putname(path - (PATH_MAX - 1 - len));
पूर्ण

बाह्य अक्षर *ceph_mdsc_build_path(काष्ठा dentry *dentry, पूर्णांक *plen, u64 *base,
				  पूर्णांक stop_on_nosnap);

बाह्य व्योम __ceph_mdsc_drop_dentry_lease(काष्ठा dentry *dentry);
बाह्य व्योम ceph_mdsc_lease_send_msg(काष्ठा ceph_mds_session *session,
				     काष्ठा dentry *dentry, अक्षर action,
				     u32 seq);

बाह्य व्योम ceph_mdsc_handle_mdsmap(काष्ठा ceph_mds_client *mdsc,
				    काष्ठा ceph_msg *msg);
बाह्य व्योम ceph_mdsc_handle_fsmap(काष्ठा ceph_mds_client *mdsc,
				   काष्ठा ceph_msg *msg);

बाह्य काष्ठा ceph_mds_session *
ceph_mdsc_खोलो_export_target_session(काष्ठा ceph_mds_client *mdsc, पूर्णांक target);
बाह्य व्योम ceph_mdsc_खोलो_export_target_sessions(काष्ठा ceph_mds_client *mdsc,
					  काष्ठा ceph_mds_session *session);

बाह्य पूर्णांक ceph_trim_caps(काष्ठा ceph_mds_client *mdsc,
			  काष्ठा ceph_mds_session *session,
			  पूर्णांक max_caps);

अटल अंतरभूत पूर्णांक ceph_रुको_on_async_create(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	वापस रुको_on_bit(&ci->i_ceph_flags, CEPH_ASYNC_CREATE_BIT,
			   TASK_INTERRUPTIBLE);
पूर्ण

बाह्य u64 ceph_get_deleg_ino(काष्ठा ceph_mds_session *session);
बाह्य पूर्णांक ceph_restore_deleg_ino(काष्ठा ceph_mds_session *session, u64 ino);
#पूर्ण_अगर
