<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ceph_fs.h - Ceph स्थिरants and data types to share between kernel and
 * user space.
 *
 * Most types in this file are defined as little-endian, and are
 * primarily पूर्णांकended to describe data काष्ठाures that pass over the
 * wire or that are stored on disk.
 *
 * LGPL2
 */

#अगर_अघोषित CEPH_FS_H
#घोषणा CEPH_FS_H

#समावेश <linux/ceph/msgr.h>
#समावेश <linux/ceph/raडॉस.स>

/*
 * subprotocol versions.  when specअगरic messages types or high-level
 * protocols change, bump the affected components.  we keep rev
 * पूर्णांकernal cluster protocols separately from the खुला,
 * client-facing protocol.
 */
#घोषणा CEPH_OSDC_PROTOCOL   24 /* server/client */
#घोषणा CEPH_MDSC_PROTOCOL   32 /* server/client */
#घोषणा CEPH_MONC_PROTOCOL   15 /* server/client */


#घोषणा CEPH_INO_ROOT   1
#घोषणा CEPH_INO_CEPH   2       /* hidden .ceph dir */
#घोषणा CEPH_INO_DOTDOT 3	/* used by ceph fuse क्रम parent (..) */

/* arbitrary limit on max # of monitors (cluster of 3 is typical) */
#घोषणा CEPH_MAX_MON   31

/*
 * legacy ceph_file_layoute
 */
काष्ठा ceph_file_layout_legacy अणु
	/* file -> object mapping */
	__le32 fl_stripe_unit;     /* stripe unit, in bytes.  must be multiple
				      of page size. */
	__le32 fl_stripe_count;    /* over this many objects */
	__le32 fl_object_size;     /* until objects are this big, then move to
				      new objects */
	__le32 fl_cas_hash;        /* UNUSED.  0 = none; 1 = sha256 */

	/* pg -> disk layout */
	__le32 fl_object_stripe_unit;  /* UNUSED.  क्रम per-object parity, अगर any */

	/* object -> pg layout */
	__le32 fl_unused;       /* unused; used to be preferred primary क्रम pg (-1 क्रम none) */
	__le32 fl_pg_pool;      /* namespace, crush ruleset, rep level */
पूर्ण __attribute__ ((packed));

काष्ठा ceph_string;
/*
 * ceph_file_layout - describe data layout क्रम a file/inode
 */
काष्ठा ceph_file_layout अणु
	/* file -> object mapping */
	u32 stripe_unit;   /* stripe unit, in bytes */
	u32 stripe_count;  /* over this many objects */
	u32 object_size;   /* until objects are this big */
	s64 pool_id;        /* raकरोs pool id */
	काष्ठा ceph_string __rcu *pool_ns; /* raकरोs pool namespace */
पूर्ण;

बाह्य पूर्णांक ceph_file_layout_is_valid(स्थिर काष्ठा ceph_file_layout *layout);
बाह्य व्योम ceph_file_layout_from_legacy(काष्ठा ceph_file_layout *fl,
				काष्ठा ceph_file_layout_legacy *legacy);
बाह्य व्योम ceph_file_layout_to_legacy(काष्ठा ceph_file_layout *fl,
				काष्ठा ceph_file_layout_legacy *legacy);

#घोषणा CEPH_MIN_STRIPE_UNIT 65536

काष्ठा ceph_dir_layout अणु
	__u8   dl_dir_hash;   /* see ceph_hash.h क्रम ids */
	__u8   dl_unused1;
	__u16  dl_unused2;
	__u32  dl_unused3;
पूर्ण __attribute__ ((packed));

/* crypto algorithms */
#घोषणा CEPH_CRYPTO_NONE 0x0
#घोषणा CEPH_CRYPTO_AES  0x1

#घोषणा CEPH_AES_IV "cephsageyudagreg"

/* security/authentication protocols */
#घोषणा CEPH_AUTH_UNKNOWN	0x0
#घोषणा CEPH_AUTH_NONE	 	0x1
#घोषणा CEPH_AUTH_CEPHX	 	0x2

#घोषणा CEPH_AUTH_MODE_NONE		0
#घोषणा CEPH_AUTH_MODE_AUTHORIZER	1
#घोषणा CEPH_AUTH_MODE_MON		10

/* msgr2 protocol modes */
#घोषणा CEPH_CON_MODE_UNKNOWN	0x0
#घोषणा CEPH_CON_MODE_CRC	0x1
#घोषणा CEPH_CON_MODE_SECURE	0x2

#घोषणा CEPH_AUTH_UID_DEFAULT ((__u64) -1)

स्थिर अक्षर *ceph_auth_proto_name(पूर्णांक proto);
स्थिर अक्षर *ceph_con_mode_name(पूर्णांक mode);

/*********************************************
 * message layer
 */

/*
 * message types
 */

/* misc */
#घोषणा CEPH_MSG_SHUTDOWN               1
#घोषणा CEPH_MSG_PING                   2

/* client <-> monitor */
#घोषणा CEPH_MSG_MON_MAP                4
#घोषणा CEPH_MSG_MON_GET_MAP            5
#घोषणा CEPH_MSG_STATFS                 13
#घोषणा CEPH_MSG_STATFS_REPLY           14
#घोषणा CEPH_MSG_MON_SUBSCRIBE          15
#घोषणा CEPH_MSG_MON_SUBSCRIBE_ACK      16
#घोषणा CEPH_MSG_AUTH			17
#घोषणा CEPH_MSG_AUTH_REPLY		18
#घोषणा CEPH_MSG_MON_GET_VERSION        19
#घोषणा CEPH_MSG_MON_GET_VERSION_REPLY  20

/* client <-> mds */
#घोषणा CEPH_MSG_MDS_MAP                21
#घोषणा CEPH_MSG_FS_MAP_USER            103

#घोषणा CEPH_MSG_CLIENT_SESSION         22
#घोषणा CEPH_MSG_CLIENT_RECONNECT       23

#घोषणा CEPH_MSG_CLIENT_REQUEST         24
#घोषणा CEPH_MSG_CLIENT_REQUEST_FORWARD 25
#घोषणा CEPH_MSG_CLIENT_REPLY           26
#घोषणा CEPH_MSG_CLIENT_METRICS         29
#घोषणा CEPH_MSG_CLIENT_CAPS            0x310
#घोषणा CEPH_MSG_CLIENT_LEASE           0x311
#घोषणा CEPH_MSG_CLIENT_SNAP            0x312
#घोषणा CEPH_MSG_CLIENT_CAPRELEASE      0x313
#घोषणा CEPH_MSG_CLIENT_QUOTA           0x314

/* pool ops */
#घोषणा CEPH_MSG_POOLOP_REPLY           48
#घोषणा CEPH_MSG_POOLOP                 49

/* mon commands */
#घोषणा CEPH_MSG_MON_COMMAND            50
#घोषणा CEPH_MSG_MON_COMMAND_ACK        51

/* osd */
#घोषणा CEPH_MSG_OSD_MAP                41
#घोषणा CEPH_MSG_OSD_OP                 42
#घोषणा CEPH_MSG_OSD_OPREPLY            43
#घोषणा CEPH_MSG_WATCH_NOTIFY           44
#घोषणा CEPH_MSG_OSD_BACKOFF            61


/* watch-notअगरy operations */
क्रमागत अणु
	CEPH_WATCH_EVENT_NOTIFY		  = 1, /* notअगरying watcher */
	CEPH_WATCH_EVENT_NOTIFY_COMPLETE  = 2, /* notअगरier notअगरied when करोne */
	CEPH_WATCH_EVENT_DISCONNECT       = 3, /* we were disconnected */
पूर्ण;


काष्ठा ceph_mon_request_header अणु
	__le64 have_version;
	__le16 session_mon;
	__le64 session_mon_tid;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_mon_statfs अणु
	काष्ठा ceph_mon_request_header monhdr;
	काष्ठा ceph_fsid fsid;
	__u8 contains_data_pool;
	__le64 data_pool;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_statfs अणु
	__le64 kb, kb_used, kb_avail;
	__le64 num_objects;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_mon_statfs_reply अणु
	काष्ठा ceph_fsid fsid;
	__le64 version;
	काष्ठा ceph_statfs st;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_mon_command अणु
	काष्ठा ceph_mon_request_header monhdr;
	काष्ठा ceph_fsid fsid;
	__le32 num_strs;         /* always 1 */
	__le32 str_len;
	अक्षर str[];
पूर्ण __attribute__ ((packed));

काष्ठा ceph_osd_geपंचांगap अणु
	काष्ठा ceph_mon_request_header monhdr;
	काष्ठा ceph_fsid fsid;
	__le32 start;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_mds_geपंचांगap अणु
	काष्ठा ceph_mon_request_header monhdr;
	काष्ठा ceph_fsid fsid;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_client_mount अणु
	काष्ठा ceph_mon_request_header monhdr;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_SUBSCRIBE_ONETIME    1  /* i want only 1 update after have */

काष्ठा ceph_mon_subscribe_item अणु
	__le64 start;
	__u8 flags;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_mon_subscribe_ack अणु
	__le32 duration;         /* seconds */
	काष्ठा ceph_fsid fsid;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_FS_CLUSTER_ID_NONE  -1

/*
 * mdsmap flags
 */
#घोषणा CEPH_MDSMAP_DOWN    (1<<0)  /* cluster deliberately करोwn */

/*
 * mds states
 *   > 0 -> in
 *  <= 0 -> out
 */
#घोषणा CEPH_MDS_STATE_DNE          0  /* करोwn, करोes not exist. */
#घोषणा CEPH_MDS_STATE_STOPPED     -1  /* करोwn, once existed, but no subtrees.
					  empty log. */
#घोषणा CEPH_MDS_STATE_BOOT        -4  /* up, boot announcement. */
#घोषणा CEPH_MDS_STATE_STANDBY     -5  /* up, idle.  रुकोing क्रम assignment. */
#घोषणा CEPH_MDS_STATE_CREATING    -6  /* up, creating MDS instance. */
#घोषणा CEPH_MDS_STATE_STARTING    -7  /* up, starting previously stopped mds */
#घोषणा CEPH_MDS_STATE_STANDBY_REPLAY -8 /* up, tailing active node's journal */
#घोषणा CEPH_MDS_STATE_REPLAYONCE   -9 /* up, replaying an active node's journal */

#घोषणा CEPH_MDS_STATE_REPLAY       8  /* up, replaying journal. */
#घोषणा CEPH_MDS_STATE_RESOLVE      9  /* up, disambiguating distributed
					  operations (import, नाम, etc.) */
#घोषणा CEPH_MDS_STATE_RECONNECT    10 /* up, reconnect to clients */
#घोषणा CEPH_MDS_STATE_REJOIN       11 /* up, rejoining distributed cache */
#घोषणा CEPH_MDS_STATE_CLIENTREPLAY 12 /* up, replaying client operations */
#घोषणा CEPH_MDS_STATE_ACTIVE       13 /* up, active */
#घोषणा CEPH_MDS_STATE_STOPPING     14 /* up, but exporting metadata */

बाह्य स्थिर अक्षर *ceph_mds_state_name(पूर्णांक s);


/*
 * metadata lock types.
 *  - these are biपंचांगasks.. we can compose them
 *  - they also define the lock ordering by the MDS
 *  - a few of these are पूर्णांकernal to the mds
 */
#घोषणा CEPH_LOCK_DVERSION    1
#घोषणा CEPH_LOCK_DN          2
#घोषणा CEPH_LOCK_ISNAP       16
#घोषणा CEPH_LOCK_IVERSION    32    /* mds पूर्णांकernal */
#घोषणा CEPH_LOCK_Iखाता       64
#घोषणा CEPH_LOCK_IAUTH       128
#घोषणा CEPH_LOCK_ILINK       256
#घोषणा CEPH_LOCK_IDFT        512   /* dir frag tree */
#घोषणा CEPH_LOCK_INEST       1024  /* mds पूर्णांकernal */
#घोषणा CEPH_LOCK_IXATTR      2048
#घोषणा CEPH_LOCK_IFLOCK      4096  /* advisory file locks */
#घोषणा CEPH_LOCK_INO         8192  /* immutable inode bits; not a lock */
#घोषणा CEPH_LOCK_IPOLICY     16384 /* policy lock on dirs. MDS पूर्णांकernal */

/* client_session ops */
क्रमागत अणु
	CEPH_SESSION_REQUEST_OPEN,
	CEPH_SESSION_OPEN,
	CEPH_SESSION_REQUEST_CLOSE,
	CEPH_SESSION_CLOSE,
	CEPH_SESSION_REQUEST_RENEWCAPS,
	CEPH_SESSION_RENEWCAPS,
	CEPH_SESSION_STALE,
	CEPH_SESSION_RECALL_STATE,
	CEPH_SESSION_FLUSHMSG,
	CEPH_SESSION_FLUSHMSG_ACK,
	CEPH_SESSION_FORCE_RO,
	CEPH_SESSION_REJECT,
पूर्ण;

बाह्य स्थिर अक्षर *ceph_session_op_name(पूर्णांक op);

काष्ठा ceph_mds_session_head अणु
	__le32 op;
	__le64 seq;
	काष्ठा ceph_बारpec stamp;
	__le32 max_caps, max_leases;
पूर्ण __attribute__ ((packed));

/* client_request */
/*
 * metadata ops.
 *  & 0x001000 -> ग_लिखो op
 *  & 0x010000 -> follow symlink (e.g. stat(), not lstat()).
 &  & 0x100000 -> use weird ino/path trace
 */
#घोषणा CEPH_MDS_OP_WRITE        0x001000
क्रमागत अणु
	CEPH_MDS_OP_LOOKUP     = 0x00100,
	CEPH_MDS_OP_GETATTR    = 0x00101,
	CEPH_MDS_OP_LOOKUPHASH = 0x00102,
	CEPH_MDS_OP_LOOKUPPARENT = 0x00103,
	CEPH_MDS_OP_LOOKUPINO  = 0x00104,
	CEPH_MDS_OP_LOOKUPNAME = 0x00105,

	CEPH_MDS_OP_SETXATTR   = 0x01105,
	CEPH_MDS_OP_RMXATTR    = 0x01106,
	CEPH_MDS_OP_SETLAYOUT  = 0x01107,
	CEPH_MDS_OP_SETATTR    = 0x01108,
	CEPH_MDS_OP_SETखाताLOCK= 0x01109,
	CEPH_MDS_OP_GETखाताLOCK= 0x00110,
	CEPH_MDS_OP_SETसूचीLAYOUT=0x0110a,

	CEPH_MDS_OP_MKNOD      = 0x01201,
	CEPH_MDS_OP_LINK       = 0x01202,
	CEPH_MDS_OP_UNLINK     = 0x01203,
	CEPH_MDS_OP_RENAME     = 0x01204,
	CEPH_MDS_OP_MKसूची      = 0x01220,
	CEPH_MDS_OP_RMसूची      = 0x01221,
	CEPH_MDS_OP_SYMLINK    = 0x01222,

	CEPH_MDS_OP_CREATE     = 0x01301,
	CEPH_MDS_OP_OPEN       = 0x00302,
	CEPH_MDS_OP_READसूची    = 0x00305,

	CEPH_MDS_OP_LOOKUPSNAP = 0x00400,
	CEPH_MDS_OP_MKSNAP     = 0x01400,
	CEPH_MDS_OP_RMSNAP     = 0x01401,
	CEPH_MDS_OP_LSSNAP     = 0x00402,
	CEPH_MDS_OP_RENAMESNAP = 0x01403,
पूर्ण;

बाह्य स्थिर अक्षर *ceph_mds_op_name(पूर्णांक op);


#घोषणा CEPH_SETATTR_MODE   1
#घोषणा CEPH_SETATTR_UID    2
#घोषणा CEPH_SETATTR_GID    4
#घोषणा CEPH_SETATTR_MTIME  8
#घोषणा CEPH_SETATTR_ATIME 16
#घोषणा CEPH_SETATTR_SIZE  32
#घोषणा CEPH_SETATTR_CTIME 64

/*
 * Ceph setxattr request flags.
 */
#घोषणा CEPH_XATTR_CREATE  (1 << 0)
#घोषणा CEPH_XATTR_REPLACE (1 << 1)
#घोषणा CEPH_XATTR_REMOVE  (1 << 31)

/*
 * सूची_पढ़ो request flags;
 */
#घोषणा CEPH_READसूची_REPLY_BITFLAGS	(1<<0)

/*
 * सूची_पढ़ो reply flags.
 */
#घोषणा CEPH_READसूची_FRAG_END		(1<<0)
#घोषणा CEPH_READसूची_FRAG_COMPLETE	(1<<8)
#घोषणा CEPH_READसूची_HASH_ORDER		(1<<9)
#घोषणा CEPH_READसूची_OFFSET_HASH	(1<<10)

/*
 * खोलो request flags
 */
#घोषणा CEPH_O_RDONLY		00000000
#घोषणा CEPH_O_WRONLY		00000001
#घोषणा CEPH_O_RDWR		00000002
#घोषणा CEPH_O_CREAT		00000100
#घोषणा CEPH_O_EXCL		00000200
#घोषणा CEPH_O_TRUNC		00001000
#घोषणा CEPH_O_सूचीECTORY	00200000
#घोषणा CEPH_O_NOFOLLOW		00400000

जोड़ ceph_mds_request_args अणु
	काष्ठा अणु
		__le32 mask;                 /* CEPH_CAP_* */
	पूर्ण __attribute__ ((packed)) getattr;
	काष्ठा अणु
		__le32 mode;
		__le32 uid;
		__le32 gid;
		काष्ठा ceph_बारpec mसमय;
		काष्ठा ceph_बारpec aसमय;
		__le64 size, old_size;       /* old_size needed by truncate */
		__le32 mask;                 /* CEPH_SETATTR_* */
	पूर्ण __attribute__ ((packed)) setattr;
	काष्ठा अणु
		__le32 frag;                 /* which dir fragment */
		__le32 max_entries;          /* how many dentries to grab */
		__le32 max_bytes;
		__le16 flags;
		__le32 offset_hash;
	पूर्ण __attribute__ ((packed)) सूची_पढ़ो;
	काष्ठा अणु
		__le32 mode;
		__le32 rdev;
	पूर्ण __attribute__ ((packed)) mknod;
	काष्ठा अणु
		__le32 mode;
	पूर्ण __attribute__ ((packed)) सूची_गढ़ो;
	काष्ठा अणु
		__le32 flags;
		__le32 mode;
		__le32 stripe_unit;          /* layout क्रम newly created file */
		__le32 stripe_count;         /* ... */
		__le32 object_size;
		__le32 file_replication;
               __le32 mask;                 /* CEPH_CAP_* */
               __le32 old_size;
	पूर्ण __attribute__ ((packed)) खोलो;
	काष्ठा अणु
		__le32 flags;
		__le32 osdmap_epoch; /* used क्रम setting file/dir layouts */
	पूर्ण __attribute__ ((packed)) setxattr;
	काष्ठा अणु
		काष्ठा ceph_file_layout_legacy layout;
	पूर्ण __attribute__ ((packed)) setlayout;
	काष्ठा अणु
		__u8 rule; /* currently fcntl or flock */
		__u8 type; /* shared, exclusive, हटाओ*/
		__le64 owner; /* owner of the lock */
		__le64 pid; /* process id requesting the lock */
		__le64 start; /* initial location to lock */
		__le64 length; /* num bytes to lock from start */
		__u8 रुको; /* will caller रुको क्रम lock to become available? */
	पूर्ण __attribute__ ((packed)) filelock_change;
	काष्ठा अणु
		__le32 mask;                 /* CEPH_CAP_* */
		__le64 snapid;
		__le64 parent;
		__le32 hash;
	पूर्ण __attribute__ ((packed)) lookupino;
पूर्ण __attribute__ ((packed));

जोड़ ceph_mds_request_args_ext अणु
	जोड़ ceph_mds_request_args old;
	काष्ठा अणु
		__le32 mode;
		__le32 uid;
		__le32 gid;
		काष्ठा ceph_बारpec mसमय;
		काष्ठा ceph_बारpec aसमय;
		__le64 size, old_size;       /* old_size needed by truncate */
		__le32 mask;                 /* CEPH_SETATTR_* */
		काष्ठा ceph_बारpec bसमय;
	पूर्ण __attribute__ ((packed)) setattr_ext;
पूर्ण;

#घोषणा CEPH_MDS_FLAG_REPLAY		1 /* this is a replayed op */
#घोषणा CEPH_MDS_FLAG_WANT_DENTRY	2 /* want dentry in reply */
#घोषणा CEPH_MDS_FLAG_ASYNC		4 /* request is asynchronous */

काष्ठा ceph_mds_request_head_old अणु
	__le64 oldest_client_tid;
	__le32 mdsmap_epoch;           /* on client */
	__le32 flags;                  /* CEPH_MDS_FLAG_* */
	__u8 num_retry, num_fwd;       /* count retry, fwd attempts */
	__le16 num_releases;           /* # include cap/lease release records */
	__le32 op;                     /* mds op code */
	__le32 caller_uid, caller_gid;
	__le64 ino;                    /* use this ino क्रम खोलोc, सूची_गढ़ो, mknod,
					  etc. (अगर replaying) */
	जोड़ ceph_mds_request_args args;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_MDS_REQUEST_HEAD_VERSION  1

काष्ठा ceph_mds_request_head अणु
	__le16 version;                /* काष्ठा version */
	__le64 oldest_client_tid;
	__le32 mdsmap_epoch;           /* on client */
	__le32 flags;                  /* CEPH_MDS_FLAG_* */
	__u8 num_retry, num_fwd;       /* count retry, fwd attempts */
	__le16 num_releases;           /* # include cap/lease release records */
	__le32 op;                     /* mds op code */
	__le32 caller_uid, caller_gid;
	__le64 ino;                    /* use this ino क्रम खोलोc, सूची_गढ़ो, mknod,
					  etc. (अगर replaying) */
	जोड़ ceph_mds_request_args_ext args;
पूर्ण __attribute__ ((packed));

/* cap/lease release record */
काष्ठा ceph_mds_request_release अणु
	__le64 ino, cap_id;            /* ino and unique cap id */
	__le32 caps, wanted;           /* new issued, wanted */
	__le32 seq, issue_seq, mseq;
	__le32 dname_seq;              /* अगर releasing a dentry lease, a */
	__le32 dname_len;              /* string follows. */
पूर्ण __attribute__ ((packed));

/* client reply */
काष्ठा ceph_mds_reply_head अणु
	__le32 op;
	__le32 result;
	__le32 mdsmap_epoch;
	__u8 safe;                     /* true अगर committed to disk */
	__u8 is_dentry, is_target;     /* true अगर dentry, target inode records
					  are included with reply */
पूर्ण __attribute__ ((packed));

/* one क्रम each node split */
काष्ठा ceph_frag_tree_split अणु
	__le32 frag;                   /* this frag splits... */
	__le32 by;                     /* ...by this many bits */
पूर्ण __attribute__ ((packed));

काष्ठा ceph_frag_tree_head अणु
	__le32 nsplits;                /* num ceph_frag_tree_split records */
	काष्ठा ceph_frag_tree_split splits[];
पूर्ण __attribute__ ((packed));

/* capability issue, क्रम bundling with mds reply */
काष्ठा ceph_mds_reply_cap अणु
	__le32 caps, wanted;           /* caps issued, wanted */
	__le64 cap_id;
	__le32 seq, mseq;
	__le64 realm;                  /* snap realm */
	__u8 flags;                    /* CEPH_CAP_FLAG_* */
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_CAP_FLAG_AUTH	(1 << 0)  /* cap is issued by auth mds */
#घोषणा CEPH_CAP_FLAG_RELEASE	(1 << 1)  /* release the cap */

/* inode record, क्रम bundling with mds reply */
काष्ठा ceph_mds_reply_inode अणु
	__le64 ino;
	__le64 snapid;
	__le32 rdev;
	__le64 version;                /* inode version */
	__le64 xattr_version;          /* version क्रम xattr blob */
	काष्ठा ceph_mds_reply_cap cap; /* caps issued क्रम this inode */
	काष्ठा ceph_file_layout_legacy layout;
	काष्ठा ceph_बारpec स_समय, mसमय, aसमय;
	__le32 समय_warp_seq;
	__le64 size, max_size, truncate_size;
	__le32 truncate_seq;
	__le32 mode, uid, gid;
	__le32 nlink;
	__le64 files, subdirs, rbytes, rfiles, rsubdirs;  /* dir stats */
	काष्ठा ceph_बारpec rस_समय;
	काष्ठा ceph_frag_tree_head fragtree;  /* (must be at end of काष्ठा) */
पूर्ण __attribute__ ((packed));
/* followed by frag array, symlink string, dir layout, xattr blob */

/* reply_lease follows dname, and reply_inode */
काष्ठा ceph_mds_reply_lease अणु
	__le16 mask;            /* lease type(s) */
	__le32 duration_ms;     /* lease duration */
	__le32 seq;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_LEASE_VALID        (1 | 2) /* old and new bit values */
#घोषणा CEPH_LEASE_PRIMARY_LINK 4       /* primary linkage */

काष्ठा ceph_mds_reply_dirfrag अणु
	__le32 frag;            /* fragment */
	__le32 auth;            /* auth mds, अगर this is a delegation poपूर्णांक */
	__le32 ndist;           /* number of mds' this is replicated on */
	__le32 dist[];
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_LOCK_FCNTL		1
#घोषणा CEPH_LOCK_FLOCK		2
#घोषणा CEPH_LOCK_FCNTL_INTR    3
#घोषणा CEPH_LOCK_FLOCK_INTR    4


#घोषणा CEPH_LOCK_SHARED   1
#घोषणा CEPH_LOCK_EXCL     2
#घोषणा CEPH_LOCK_UNLOCK   4

काष्ठा ceph_filelock अणु
	__le64 start;/* file offset to start lock at */
	__le64 length; /* num bytes to lock; 0 क्रम all following start */
	__le64 client; /* which client holds the lock */
	__le64 owner; /* owner the lock */
	__le64 pid; /* process id holding the lock on the client */
	__u8 type; /* shared lock, exclusive lock, or unlock */
पूर्ण __attribute__ ((packed));


/* file access modes */
#घोषणा CEPH_खाता_MODE_PIN        0
#घोषणा CEPH_खाता_MODE_RD         1
#घोषणा CEPH_खाता_MODE_WR         2
#घोषणा CEPH_खाता_MODE_RDWR       3  /* RD | WR */
#घोषणा CEPH_खाता_MODE_LAZY       4  /* lazy io */
#घोषणा CEPH_खाता_MODE_BITS       4
#घोषणा CEPH_खाता_MODE_MASK       ((1 << CEPH_खाता_MODE_BITS) - 1)

पूर्णांक ceph_flags_to_mode(पूर्णांक flags);

#घोषणा CEPH_INLINE_NONE	((__u64)-1)

/* capability bits */
#घोषणा CEPH_CAP_PIN         1  /* no specअगरic capabilities beyond the pin */

/* generic cap bits */
#घोषणा CEPH_CAP_GSHARED     1  /* client can पढ़ोs */
#घोषणा CEPH_CAP_GEXCL       2  /* client can पढ़ो and update */
#घोषणा CEPH_CAP_GCACHE      4  /* (file) client can cache पढ़ोs */
#घोषणा CEPH_CAP_GRD         8  /* (file) client can पढ़ो */
#घोषणा CEPH_CAP_GWR        16  /* (file) client can ग_लिखो */
#घोषणा CEPH_CAP_GBUFFER    32  /* (file) client can buffer ग_लिखोs */
#घोषणा CEPH_CAP_GWREXTEND  64  /* (file) client can extend खातापूर्ण */
#घोषणा CEPH_CAP_GLAZYIO   128  /* (file) client can perक्रमm lazy io */

#घोषणा CEPH_CAP_SIMPLE_BITS  2
#घोषणा CEPH_CAP_खाता_BITS    8

/* per-lock shअगरt */
#घोषणा CEPH_CAP_SAUTH      2
#घोषणा CEPH_CAP_SLINK      4
#घोषणा CEPH_CAP_SXATTR     6
#घोषणा CEPH_CAP_Sखाता      8
#घोषणा CEPH_CAP_SFLOCK    20

#घोषणा CEPH_CAP_BITS      22

/* composed values */
#घोषणा CEPH_CAP_AUTH_SHARED  (CEPH_CAP_GSHARED  << CEPH_CAP_SAUTH)
#घोषणा CEPH_CAP_AUTH_EXCL     (CEPH_CAP_GEXCL     << CEPH_CAP_SAUTH)
#घोषणा CEPH_CAP_LINK_SHARED  (CEPH_CAP_GSHARED  << CEPH_CAP_SLINK)
#घोषणा CEPH_CAP_LINK_EXCL     (CEPH_CAP_GEXCL     << CEPH_CAP_SLINK)
#घोषणा CEPH_CAP_XATTR_SHARED (CEPH_CAP_GSHARED  << CEPH_CAP_SXATTR)
#घोषणा CEPH_CAP_XATTR_EXCL    (CEPH_CAP_GEXCL     << CEPH_CAP_SXATTR)
#घोषणा CEPH_CAP_खाता(x)    (x << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_खाता_SHARED   (CEPH_CAP_GSHARED   << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_खाता_EXCL     (CEPH_CAP_GEXCL     << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_खाता_CACHE    (CEPH_CAP_GCACHE    << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_खाता_RD       (CEPH_CAP_GRD       << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_खाता_WR       (CEPH_CAP_GWR       << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_खाता_BUFFER   (CEPH_CAP_GBUFFER   << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_खाता_WREXTEND (CEPH_CAP_GWREXTEND << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_खाता_LAZYIO   (CEPH_CAP_GLAZYIO   << CEPH_CAP_Sखाता)
#घोषणा CEPH_CAP_FLOCK_SHARED  (CEPH_CAP_GSHARED   << CEPH_CAP_SFLOCK)
#घोषणा CEPH_CAP_FLOCK_EXCL    (CEPH_CAP_GEXCL     << CEPH_CAP_SFLOCK)


/* cap masks (क्रम getattr) */
#घोषणा CEPH_STAT_CAP_INODE    CEPH_CAP_PIN
#घोषणा CEPH_STAT_CAP_TYPE     CEPH_CAP_PIN  /* mode >> 12 */
#घोषणा CEPH_STAT_CAP_SYMLINK  CEPH_CAP_PIN
#घोषणा CEPH_STAT_CAP_UID      CEPH_CAP_AUTH_SHARED
#घोषणा CEPH_STAT_CAP_GID      CEPH_CAP_AUTH_SHARED
#घोषणा CEPH_STAT_CAP_MODE     CEPH_CAP_AUTH_SHARED
#घोषणा CEPH_STAT_CAP_NLINK    CEPH_CAP_LINK_SHARED
#घोषणा CEPH_STAT_CAP_LAYOUT   CEPH_CAP_खाता_SHARED
#घोषणा CEPH_STAT_CAP_MTIME    CEPH_CAP_खाता_SHARED
#घोषणा CEPH_STAT_CAP_SIZE     CEPH_CAP_खाता_SHARED
#घोषणा CEPH_STAT_CAP_ATIME    CEPH_CAP_खाता_SHARED  /* fixme */
#घोषणा CEPH_STAT_CAP_XATTR    CEPH_CAP_XATTR_SHARED
#घोषणा CEPH_STAT_CAP_INODE_ALL (CEPH_CAP_PIN |			\
				 CEPH_CAP_AUTH_SHARED |	\
				 CEPH_CAP_LINK_SHARED |	\
				 CEPH_CAP_खाता_SHARED |	\
				 CEPH_CAP_XATTR_SHARED)
#घोषणा CEPH_STAT_CAP_INLINE_DATA (CEPH_CAP_खाता_SHARED | \
				   CEPH_CAP_खाता_RD)
#घोषणा CEPH_STAT_RSTAT CEPH_CAP_खाता_WREXTEND

#घोषणा CEPH_CAP_ANY_SHARED (CEPH_CAP_AUTH_SHARED |			\
			      CEPH_CAP_LINK_SHARED |			\
			      CEPH_CAP_XATTR_SHARED |			\
			      CEPH_CAP_खाता_SHARED)
#घोषणा CEPH_CAP_ANY_RD   (CEPH_CAP_ANY_SHARED | CEPH_CAP_खाता_RD |	\
			   CEPH_CAP_खाता_CACHE)

#घोषणा CEPH_CAP_ANY_EXCL (CEPH_CAP_AUTH_EXCL |		\
			   CEPH_CAP_LINK_EXCL |		\
			   CEPH_CAP_XATTR_EXCL |	\
			   CEPH_CAP_खाता_EXCL)
#घोषणा CEPH_CAP_ANY_खाता_RD (CEPH_CAP_खाता_RD | CEPH_CAP_खाता_CACHE | \
			      CEPH_CAP_खाता_SHARED)
#घोषणा CEPH_CAP_ANY_खाता_WR (CEPH_CAP_खाता_WR | CEPH_CAP_खाता_BUFFER |	\
			      CEPH_CAP_खाता_EXCL)
#घोषणा CEPH_CAP_ANY_WR   (CEPH_CAP_ANY_EXCL | CEPH_CAP_ANY_खाता_WR)
#घोषणा CEPH_CAP_ANY      (CEPH_CAP_ANY_RD | CEPH_CAP_ANY_EXCL | \
			   CEPH_CAP_ANY_खाता_WR | CEPH_CAP_खाता_LAZYIO | \
			   CEPH_CAP_PIN)
#घोषणा CEPH_CAP_ALL_खाता (CEPH_CAP_PIN | CEPH_CAP_ANY_SHARED | \
			   CEPH_CAP_AUTH_EXCL | CEPH_CAP_XATTR_EXCL | \
			   CEPH_CAP_ANY_खाता_RD | CEPH_CAP_ANY_खाता_WR)

#घोषणा CEPH_CAP_LOCKS (CEPH_LOCK_Iखाता | CEPH_LOCK_IAUTH | CEPH_LOCK_ILINK | \
			CEPH_LOCK_IXATTR)

/* cap masks async dir operations */
#घोषणा CEPH_CAP_सूची_CREATE	CEPH_CAP_खाता_CACHE
#घोषणा CEPH_CAP_सूची_UNLINK	CEPH_CAP_खाता_RD
#घोषणा CEPH_CAP_ANY_सूची_OPS	(CEPH_CAP_खाता_CACHE | CEPH_CAP_खाता_RD | \
				 CEPH_CAP_खाता_WREXTEND | CEPH_CAP_खाता_LAZYIO)

पूर्णांक ceph_caps_क्रम_mode(पूर्णांक mode);

क्रमागत अणु
	CEPH_CAP_OP_GRANT,         /* mds->client grant */
	CEPH_CAP_OP_REVOKE,        /* mds->client revoke */
	CEPH_CAP_OP_TRUNC,         /* mds->client trunc notअगरy */
	CEPH_CAP_OP_EXPORT,        /* mds has exported the cap */
	CEPH_CAP_OP_IMPORT,        /* mds has imported the cap */
	CEPH_CAP_OP_UPDATE,        /* client->mds update */
	CEPH_CAP_OP_DROP,          /* client->mds drop cap bits */
	CEPH_CAP_OP_FLUSH,         /* client->mds cap ग_लिखोback */
	CEPH_CAP_OP_FLUSH_ACK,     /* mds->client flushed */
	CEPH_CAP_OP_FLUSHSNAP,     /* client->mds flush snapped metadata */
	CEPH_CAP_OP_FLUSHSNAP_ACK, /* mds->client flushed snapped metadata */
	CEPH_CAP_OP_RELEASE,       /* client->mds release (clean) cap */
	CEPH_CAP_OP_RENEW,         /* client->mds renewal request */
पूर्ण;

बाह्य स्थिर अक्षर *ceph_cap_op_name(पूर्णांक op);

/* flags field in client cap messages (version >= 10) */
#घोषणा CEPH_CLIENT_CAPS_SYNC			(1<<0)
#घोषणा CEPH_CLIENT_CAPS_NO_CAPSNAP		(1<<1)
#घोषणा CEPH_CLIENT_CAPS_PENDING_CAPSNAP	(1<<2)

/*
 * caps message, used क्रम capability callbacks, acks, requests, etc.
 */
काष्ठा ceph_mds_caps अणु
	__le32 op;                  /* CEPH_CAP_OP_* */
	__le64 ino, realm;
	__le64 cap_id;
	__le32 seq, issue_seq;
	__le32 caps, wanted, dirty; /* latest issued/wanted/dirty */
	__le32 migrate_seq;
	__le64 snap_follows;
	__le32 snap_trace_len;

	/* authlock */
	__le32 uid, gid, mode;

	/* linklock */
	__le32 nlink;

	/* xattrlock */
	__le32 xattr_len;
	__le64 xattr_version;

	/* filelock */
	__le64 size, max_size, truncate_size;
	__le32 truncate_seq;
	काष्ठा ceph_बारpec mसमय, aसमय, स_समय;
	काष्ठा ceph_file_layout_legacy layout;
	__le32 समय_warp_seq;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_mds_cap_peer अणु
	__le64 cap_id;
	__le32 seq;
	__le32 mseq;
	__le32 mds;
	__u8   flags;
पूर्ण __attribute__ ((packed));

/* cap release msg head */
काष्ठा ceph_mds_cap_release अणु
	__le32 num;                /* number of cap_items that follow */
पूर्ण __attribute__ ((packed));

काष्ठा ceph_mds_cap_item अणु
	__le64 ino;
	__le64 cap_id;
	__le32 migrate_seq, seq;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_MDS_LEASE_REVOKE           1  /*    mds  -> client */
#घोषणा CEPH_MDS_LEASE_RELEASE          2  /* client  -> mds    */
#घोषणा CEPH_MDS_LEASE_RENEW            3  /* client <-> mds    */
#घोषणा CEPH_MDS_LEASE_REVOKE_ACK       4  /* client  -> mds    */

बाह्य स्थिर अक्षर *ceph_lease_op_name(पूर्णांक o);

/* lease msg header */
काष्ठा ceph_mds_lease अणु
	__u8 action;            /* CEPH_MDS_LEASE_* */
	__le16 mask;            /* which lease */
	__le64 ino;
	__le64 first, last;     /* snap range */
	__le32 seq;
	__le32 duration_ms;     /* duration of renewal */
पूर्ण __attribute__ ((packed));
/* followed by a __le32+string क्रम dname */

/* client reconnect */
काष्ठा ceph_mds_cap_reconnect अणु
	__le64 cap_id;
	__le32 wanted;
	__le32 issued;
	__le64 snaprealm;
	__le64 pathbase;        /* base ino क्रम our path to this ino */
	__le32 flock_len;       /* size of flock state blob, अगर any */
पूर्ण __attribute__ ((packed));
/* followed by flock blob */

काष्ठा ceph_mds_cap_reconnect_v1 अणु
	__le64 cap_id;
	__le32 wanted;
	__le32 issued;
	__le64 size;
	काष्ठा ceph_बारpec mसमय, aसमय;
	__le64 snaprealm;
	__le64 pathbase;        /* base ino क्रम our path to this ino */
पूर्ण __attribute__ ((packed));

काष्ठा ceph_mds_snaprealm_reconnect अणु
	__le64 ino;     /* snap realm base */
	__le64 seq;     /* snap seq क्रम this snap realm */
	__le64 parent;  /* parent realm */
पूर्ण __attribute__ ((packed));

/*
 * snaps
 */
क्रमागत अणु
	CEPH_SNAP_OP_UPDATE,  /* CREATE or DESTROY */
	CEPH_SNAP_OP_CREATE,
	CEPH_SNAP_OP_DESTROY,
	CEPH_SNAP_OP_SPLIT,
पूर्ण;

बाह्य स्थिर अक्षर *ceph_snap_op_name(पूर्णांक o);

/* snap msg header */
काष्ठा ceph_mds_snap_head अणु
	__le32 op;                /* CEPH_SNAP_OP_* */
	__le64 split;             /* ino to split off, अगर any */
	__le32 num_split_inos;    /* # inos beदीर्घing to new child realm */
	__le32 num_split_realms;  /* # child realms udner new child realm */
	__le32 trace_len;         /* size of snap trace blob */
पूर्ण __attribute__ ((packed));
/* followed by split ino list, then split realms, then the trace blob */

/*
 * encode info about a snaprealm, as viewed by a client
 */
काष्ठा ceph_mds_snap_realm अणु
	__le64 ino;           /* ino */
	__le64 created;       /* snap: when created */
	__le64 parent;        /* ino: parent realm */
	__le64 parent_since;  /* snap: same parent since */
	__le64 seq;           /* snap: version */
	__le32 num_snaps;
	__le32 num_prior_parent_snaps;
पूर्ण __attribute__ ((packed));
/* followed by my snap list, then prior parent snap list */

/*
 * quotas
 */
काष्ठा ceph_mds_quota अणु
	__le64 ino;		/* ino */
	काष्ठा ceph_बारpec rस_समय;
	__le64 rbytes;		/* dir stats */
	__le64 rfiles;
	__le64 rsubdirs;
	__u8 काष्ठा_v;		/* compat */
	__u8 काष्ठा_compat;
	__le32 काष्ठा_len;
	__le64 max_bytes;	/* quota max. bytes */
	__le64 max_files;	/* quota max. files */
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर
