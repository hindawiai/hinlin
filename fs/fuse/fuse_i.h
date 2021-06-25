<शैली गुरु>
/*
  FUSE: Fileप्रणाली in Userspace
  Copyright (C) 2001-2008  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

#अगर_अघोषित _FS_FUSE_I_H
#घोषणा _FS_FUSE_I_H

#अगर_अघोषित pr_fmt
# define pr_fmt(fmt) "fuse: " fmt
#पूर्ण_अगर

#समावेश <linux/fuse.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/poll.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kref.h>
#समावेश <linux/xattr.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/refcount.h>
#समावेश <linux/user_namespace.h>

/** Default max number of pages that can be used in a single पढ़ो request */
#घोषणा FUSE_DEFAULT_MAX_PAGES_PER_REQ 32

/** Maximum of max_pages received in init_out */
#घोषणा FUSE_MAX_MAX_PAGES 256

/** Bias क्रम fi->ग_लिखोctr, meaning new ग_लिखोpages must not be sent */
#घोषणा FUSE_NOWRITE पूर्णांक_न्यून

/** It could be as large as PATH_MAX, but would that have any uses? */
#घोषणा FUSE_NAME_MAX 1024

/** Number of dentries क्रम each connection in the control fileप्रणाली */
#घोषणा FUSE_CTL_NUM_DENTRIES 5

/** List of active connections */
बाह्य काष्ठा list_head fuse_conn_list;

/** Global mutex protecting fuse_conn_list and the control fileप्रणाली */
बाह्य काष्ठा mutex fuse_mutex;

/** Module parameters */
बाह्य अचिन्हित max_user_bgreq;
बाह्य अचिन्हित max_user_congthresh;

/* One क्रमget request */
काष्ठा fuse_क्रमget_link अणु
	काष्ठा fuse_क्रमget_one क्रमget_one;
	काष्ठा fuse_क्रमget_link *next;
पूर्ण;

/** FUSE inode */
काष्ठा fuse_inode अणु
	/** Inode data */
	काष्ठा inode inode;

	/** Unique ID, which identअगरies the inode between userspace
	 * and kernel */
	u64 nodeid;

	/** Number of lookups on this inode */
	u64 nlookup;

	/** The request used क्रम sending the FORGET message */
	काष्ठा fuse_क्रमget_link *क्रमget;

	/** Time in jअगरfies until the file attributes are valid */
	u64 i_समय;

	/* Which attributes are invalid */
	u32 inval_mask;

	/** The sticky bit in inode->i_mode may have been हटाओd, so
	    preserve the original mode */
	umode_t orig_i_mode;

	/** 64 bit inode number */
	u64 orig_ino;

	/** Version of last attribute change */
	u64 attr_version;

	जोड़ अणु
		/* Write related fields (regular file only) */
		काष्ठा अणु
			/* Files usable in ग_लिखोpage.  Protected by fi->lock */
			काष्ठा list_head ग_लिखो_files;

			/* Writepages pending on truncate or fsync */
			काष्ठा list_head queued_ग_लिखोs;

			/* Number of sent ग_लिखोs, a negative bias
			 * (FUSE_NOWRITE) means more ग_लिखोs are blocked */
			पूर्णांक ग_लिखोctr;

			/* Waitq क्रम ग_लिखोpage completion */
			रुको_queue_head_t page_रुकोq;

			/* List of ग_लिखोpage requestst (pending or sent) */
			काष्ठा rb_root ग_लिखोpages;
		पूर्ण;

		/* सूची_पढ़ो cache (directory only) */
		काष्ठा अणु
			/* true अगर fully cached */
			bool cached;

			/* size of cache */
			loff_t size;

			/* position at end of cache (position of next entry) */
			loff_t pos;

			/* version of the cache */
			u64 version;

			/* modअगरication समय of directory when cache was
			 * started */
			काष्ठा बारpec64 mसमय;

			/* iversion of directory when cache was started */
			u64 iversion;

			/* protects above fields */
			spinlock_t lock;
		पूर्ण rdc;
	पूर्ण;

	/** Miscellaneous bits describing inode state */
	अचिन्हित दीर्घ state;

	/** Lock क्रम serializing lookup and सूची_पढ़ो क्रम back compatibility*/
	काष्ठा mutex mutex;

	/** Lock to protect ग_लिखो related fields */
	spinlock_t lock;

	/**
	 * Can't take inode lock in fault path (leads to circular dependency).
	 * Introduce another semaphore which can be taken in fault path and
	 * then other fileप्रणाली paths can take this to block faults.
	 */
	काष्ठा rw_semaphore i_mmap_sem;

#अगर_घोषित CONFIG_FUSE_DAX
	/*
	 * Dax specअगरic inode data
	 */
	काष्ठा fuse_inode_dax *dax;
#पूर्ण_अगर
पूर्ण;

/** FUSE inode state bits */
क्रमागत अणु
	/** Advise सूची_पढ़ोplus  */
	FUSE_I_ADVISE_RDPLUS,
	/** Initialized with सूची_पढ़ोplus */
	FUSE_I_INIT_RDPLUS,
	/** An operation changing file size is in progress  */
	FUSE_I_SIZE_UNSTABLE,
	/* Bad inode */
	FUSE_I_BAD,
पूर्ण;

काष्ठा fuse_conn;
काष्ठा fuse_mount;
काष्ठा fuse_release_args;

/** FUSE specअगरic file data */
काष्ठा fuse_file अणु
	/** Fuse connection क्रम this file */
	काष्ठा fuse_mount *fm;

	/* Argument space reserved क्रम release */
	काष्ठा fuse_release_args *release_args;

	/** Kernel file handle guaranteed to be unique */
	u64 kh;

	/** File handle used by userspace */
	u64 fh;

	/** Node id of this file */
	u64 nodeid;

	/** Refcount */
	refcount_t count;

	/** FOPEN_* flags वापसed by खोलो */
	u32 खोलो_flags;

	/** Entry on inode's ग_लिखो_files list */
	काष्ठा list_head ग_लिखो_entry;

	/* Readdir related */
	काष्ठा अणु
		/*
		 * Protects below fields against (crazy) parallel सूची_पढ़ो on
		 * same खोलो file.  Uncontended in the normal हाल.
		 */
		काष्ठा mutex lock;

		/* Dir stream position */
		loff_t pos;

		/* Offset in cache */
		loff_t cache_off;

		/* Version of cache we are पढ़ोing */
		u64 version;

	पूर्ण सूची_पढ़ो;

	/** RB node to be linked on fuse_conn->polled_files */
	काष्ठा rb_node polled_node;

	/** Wait queue head क्रम poll */
	रुको_queue_head_t poll_रुको;

	/** Has flock been perक्रमmed on this file? */
	bool flock:1;
पूर्ण;

/** One input argument of a request */
काष्ठा fuse_in_arg अणु
	अचिन्हित size;
	स्थिर व्योम *value;
पूर्ण;

/** One output argument of a request */
काष्ठा fuse_arg अणु
	अचिन्हित size;
	व्योम *value;
पूर्ण;

/** FUSE page descriptor */
काष्ठा fuse_page_desc अणु
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक offset;
पूर्ण;

काष्ठा fuse_args अणु
	uपूर्णांक64_t nodeid;
	uपूर्णांक32_t opcode;
	अचिन्हित लघु in_numargs;
	अचिन्हित लघु out_numargs;
	bool क्रमce:1;
	bool noreply:1;
	bool nocreds:1;
	bool in_pages:1;
	bool out_pages:1;
	bool out_argvar:1;
	bool page_zeroing:1;
	bool page_replace:1;
	bool may_block:1;
	काष्ठा fuse_in_arg in_args[3];
	काष्ठा fuse_arg out_args[2];
	व्योम (*end)(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args, पूर्णांक error);
पूर्ण;

काष्ठा fuse_args_pages अणु
	काष्ठा fuse_args args;
	काष्ठा page **pages;
	काष्ठा fuse_page_desc *descs;
	अचिन्हित पूर्णांक num_pages;
पूर्ण;

#घोषणा FUSE_ARGS(args) काष्ठा fuse_args args = अणुपूर्ण

/** The request IO state (क्रम asynchronous processing) */
काष्ठा fuse_io_priv अणु
	काष्ठा kref refcnt;
	पूर्णांक async;
	spinlock_t lock;
	अचिन्हित reqs;
	sमाप_प्रकार bytes;
	माप_प्रकार size;
	__u64 offset;
	bool ग_लिखो;
	bool should_dirty;
	पूर्णांक err;
	काष्ठा kiocb *iocb;
	काष्ठा completion *करोne;
	bool blocking;
पूर्ण;

#घोषणा FUSE_IO_PRIV_SYNC(i) \
अणु					\
	.refcnt = KREF_INIT(1),		\
	.async = 0,			\
	.iocb = i,			\
पूर्ण

/**
 * Request flags
 *
 * FR_ISREPLY:		set अगर the request has reply
 * FR_FORCE:		क्रमce sending of the request even अगर पूर्णांकerrupted
 * FR_BACKGROUND:	request is sent in the background
 * FR_WAITING:		request is counted as "waiting"
 * FR_ABORTED:		the request was पातed
 * FR_INTERRUPTED:	the request has been पूर्णांकerrupted
 * FR_LOCKED:		data is being copied to/from the request
 * FR_PENDING:		request is not yet in userspace
 * FR_SENT:		request is in userspace, रुकोing क्रम an answer
 * FR_FINISHED:		request is finished
 * FR_PRIVATE:		request is on निजी list
 * FR_ASYNC:		request is asynchronous
 */
क्रमागत fuse_req_flag अणु
	FR_ISREPLY,
	FR_FORCE,
	FR_BACKGROUND,
	FR_WAITING,
	FR_ABORTED,
	FR_INTERRUPTED,
	FR_LOCKED,
	FR_PENDING,
	FR_SENT,
	FR_FINISHED,
	FR_PRIVATE,
	FR_ASYNC,
पूर्ण;

/**
 * A request to the client
 *
 * .रुकोq.lock protects the following fields:
 *   - FR_ABORTED
 *   - FR_LOCKED (may also be modअगरied under fc->lock, tested under both)
 */
काष्ठा fuse_req अणु
	/** This can be on either pending processing or io lists in
	    fuse_conn */
	काष्ठा list_head list;

	/** Entry on the पूर्णांकerrupts list  */
	काष्ठा list_head पूर्णांकr_entry;

	/* Input/output arguments */
	काष्ठा fuse_args *args;

	/** refcount */
	refcount_t count;

	/* Request flags, updated with test/set/clear_bit() */
	अचिन्हित दीर्घ flags;

	/* The request input header */
	काष्ठा अणु
		काष्ठा fuse_in_header h;
	पूर्ण in;

	/* The request output header */
	काष्ठा अणु
		काष्ठा fuse_out_header h;
	पूर्ण out;

	/** Used to wake up the task रुकोing क्रम completion of request*/
	रुको_queue_head_t रुकोq;

#अगर IS_ENABLED(CONFIG_VIRTIO_FS)
	/** virtio-fs's physically contiguous buffer क्रम in and out args */
	व्योम *argbuf;
#पूर्ण_अगर

	/** fuse_mount this request beदीर्घs to */
	काष्ठा fuse_mount *fm;
पूर्ण;

काष्ठा fuse_iqueue;

/**
 * Input queue callbacks
 *
 * Input queue संकेतling is device-specअगरic.  For example, the /dev/fuse file
 * uses fiq->रुकोq and fasync to wake processes that are रुकोing on queue
 * पढ़ोiness.  These callbacks allow other device types to respond to input
 * queue activity.
 */
काष्ठा fuse_iqueue_ops अणु
	/**
	 * Signal that a क्रमget has been queued
	 */
	व्योम (*wake_क्रमget_and_unlock)(काष्ठा fuse_iqueue *fiq)
		__releases(fiq->lock);

	/**
	 * Signal that an INTERRUPT request has been queued
	 */
	व्योम (*wake_पूर्णांकerrupt_and_unlock)(काष्ठा fuse_iqueue *fiq)
		__releases(fiq->lock);

	/**
	 * Signal that a request has been queued
	 */
	व्योम (*wake_pending_and_unlock)(काष्ठा fuse_iqueue *fiq)
		__releases(fiq->lock);

	/**
	 * Clean up when fuse_iqueue is destroyed
	 */
	व्योम (*release)(काष्ठा fuse_iqueue *fiq);
पूर्ण;

/** /dev/fuse input queue operations */
बाह्य स्थिर काष्ठा fuse_iqueue_ops fuse_dev_fiq_ops;

काष्ठा fuse_iqueue अणु
	/** Connection established */
	अचिन्हित connected;

	/** Lock protecting accesses to members of this काष्ठाure */
	spinlock_t lock;

	/** Readers of the connection are रुकोing on this */
	रुको_queue_head_t रुकोq;

	/** The next unique request id */
	u64 reqctr;

	/** The list of pending requests */
	काष्ठा list_head pending;

	/** Pending पूर्णांकerrupts */
	काष्ठा list_head पूर्णांकerrupts;

	/** Queue of pending क्रममाला_लो */
	काष्ठा fuse_क्रमget_link क्रमget_list_head;
	काष्ठा fuse_क्रमget_link *क्रमget_list_tail;

	/** Batching of FORGET requests (positive indicates FORGET batch) */
	पूर्णांक क्रमget_batch;

	/** O_ASYNC requests */
	काष्ठा fasync_काष्ठा *fasync;

	/** Device-specअगरic callbacks */
	स्थिर काष्ठा fuse_iqueue_ops *ops;

	/** Device-specअगरic state */
	व्योम *priv;
पूर्ण;

#घोषणा FUSE_PQ_HASH_BITS 8
#घोषणा FUSE_PQ_HASH_SIZE (1 << FUSE_PQ_HASH_BITS)

काष्ठा fuse_pqueue अणु
	/** Connection established */
	अचिन्हित connected;

	/** Lock protecting accessess to  members of this काष्ठाure */
	spinlock_t lock;

	/** Hash table of requests being processed */
	काष्ठा list_head *processing;

	/** The list of requests under I/O */
	काष्ठा list_head io;
पूर्ण;

/**
 * Fuse device instance
 */
काष्ठा fuse_dev अणु
	/** Fuse connection क्रम this device */
	काष्ठा fuse_conn *fc;

	/** Processing queue */
	काष्ठा fuse_pqueue pq;

	/** list entry on fc->devices */
	काष्ठा list_head entry;
पूर्ण;

काष्ठा fuse_fs_context अणु
	पूर्णांक fd;
	अचिन्हित पूर्णांक rooपंचांगode;
	kuid_t user_id;
	kgid_t group_id;
	bool is_bdev:1;
	bool fd_present:1;
	bool rooपंचांगode_present:1;
	bool user_id_present:1;
	bool group_id_present:1;
	bool शेष_permissions:1;
	bool allow_other:1;
	bool destroy:1;
	bool no_control:1;
	bool no_क्रमce_umount:1;
	bool legacy_opts_show:1;
	bool dax:1;
	अचिन्हित पूर्णांक max_पढ़ो;
	अचिन्हित पूर्णांक blksize;
	स्थिर अक्षर *subtype;

	/* DAX device, may be शून्य */
	काष्ठा dax_device *dax_dev;

	/* fuse_dev poपूर्णांकer to fill in, should contain शून्य on entry */
	व्योम **fudptr;
पूर्ण;

/**
 * A Fuse connection.
 *
 * This काष्ठाure is created, when the root fileप्रणाली is mounted, and
 * is destroyed, when the client device is बंदd and the last
 * fuse_mount is destroyed.
 */
काष्ठा fuse_conn अणु
	/** Lock protecting accessess to  members of this काष्ठाure */
	spinlock_t lock;

	/** Refcount */
	refcount_t count;

	/** Number of fuse_dev's */
	atomic_t dev_count;

	काष्ठा rcu_head rcu;

	/** The user id क्रम this mount */
	kuid_t user_id;

	/** The group id क्रम this mount */
	kgid_t group_id;

	/** The pid namespace क्रम this mount */
	काष्ठा pid_namespace *pid_ns;

	/** The user namespace क्रम this mount */
	काष्ठा user_namespace *user_ns;

	/** Maximum पढ़ो size */
	अचिन्हित max_पढ़ो;

	/** Maximum ग_लिखो size */
	अचिन्हित max_ग_लिखो;

	/** Maximum number of pages that can be used in a single request */
	अचिन्हित पूर्णांक max_pages;

	/** Constrain ->max_pages to this value during feature negotiation */
	अचिन्हित पूर्णांक max_pages_limit;

	/** Input queue */
	काष्ठा fuse_iqueue iq;

	/** The next unique kernel file handle */
	atomic64_t khctr;

	/** rbtree of fuse_files रुकोing क्रम poll events indexed by ph */
	काष्ठा rb_root polled_files;

	/** Maximum number of outstanding background requests */
	अचिन्हित max_background;

	/** Number of background requests at which congestion starts */
	अचिन्हित congestion_threshold;

	/** Number of requests currently in the background */
	अचिन्हित num_background;

	/** Number of background requests currently queued क्रम userspace */
	अचिन्हित active_background;

	/** The list of background requests set aside क्रम later queuing */
	काष्ठा list_head bg_queue;

	/** Protects: max_background, congestion_threshold, num_background,
	 * active_background, bg_queue, blocked */
	spinlock_t bg_lock;

	/** Flag indicating that INIT reply has been received. Allocating
	 * any fuse request will be suspended until the flag is set */
	पूर्णांक initialized;

	/** Flag indicating अगर connection is blocked.  This will be
	    the हाल beक्रमe the INIT reply is received, and अगर there
	    are too many outstading backgrounds requests */
	पूर्णांक blocked;

	/** रुकोq क्रम blocked connection */
	रुको_queue_head_t blocked_रुकोq;

	/** Connection established, cleared on umount, connection
	    पात and device release */
	अचिन्हित connected;

	/** Connection पातed via sysfs */
	bool पातed;

	/** Connection failed (version mismatch).  Cannot race with
	    setting other bitfields since it is only set once in INIT
	    reply, beक्रमe any other request, and never cleared */
	अचिन्हित conn_error:1;

	/** Connection successful.  Only set in INIT */
	अचिन्हित conn_init:1;

	/** Do पढ़ोpages asynchronously?  Only set in INIT */
	अचिन्हित async_पढ़ो:1;

	/** Return an unique पढ़ो error after पात.  Only set in INIT */
	अचिन्हित पात_err:1;

	/** Do not send separate SETATTR request beक्रमe खोलो(O_TRUNC)  */
	अचिन्हित atomic_o_trunc:1;

	/** Fileप्रणाली supports NFS exporting.  Only set in INIT */
	अचिन्हित export_support:1;

	/** ग_लिखो-back cache policy (शेष is ग_लिखो-through) */
	अचिन्हित ग_लिखोback_cache:1;

	/** allow parallel lookups and सूची_पढ़ो (शेष is serialized) */
	अचिन्हित parallel_dirops:1;

	/** handle fs handles समाप्तing suid/sgid/cap on ग_लिखो/chown/trunc */
	अचिन्हित handle_समाप्तpriv:1;

	/** cache READLINK responses in page cache */
	अचिन्हित cache_symlinks:1;

	/* show legacy mount options */
	अचिन्हित पूर्णांक legacy_opts_show:1;

	/*
	 * fs समाप्तs suid/sgid/cap on ग_लिखो/chown/trunc. suid is समाप्तed on
	 * ग_लिखो/trunc only अगर caller did not have CAP_FSETID.  sgid is समाप्तed
	 * on ग_लिखो/truncate only अगर caller did not have CAP_FSETID as well as
	 * file has group execute permission.
	 */
	अचिन्हित handle_समाप्तpriv_v2:1;

	/*
	 * The following bitfields are only क्रम optimization purposes
	 * and hence races in setting them will not cause malfunction
	 */

	/** Is खोलो/release not implemented by fs? */
	अचिन्हित no_खोलो:1;

	/** Is सूची_खोलो/releasedir not implemented by fs? */
	अचिन्हित no_सूची_खोलो:1;

	/** Is fsync not implemented by fs? */
	अचिन्हित no_fsync:1;

	/** Is fsyncdir not implemented by fs? */
	अचिन्हित no_fsyncdir:1;

	/** Is flush not implemented by fs? */
	अचिन्हित no_flush:1;

	/** Is setxattr not implemented by fs? */
	अचिन्हित no_setxattr:1;

	/** Does file server support extended setxattr */
	अचिन्हित setxattr_ext:1;

	/** Is getxattr not implemented by fs? */
	अचिन्हित no_getxattr:1;

	/** Is listxattr not implemented by fs? */
	अचिन्हित no_listxattr:1;

	/** Is हटाओxattr not implemented by fs? */
	अचिन्हित no_हटाओxattr:1;

	/** Are posix file locking primitives not implemented by fs? */
	अचिन्हित no_lock:1;

	/** Is access not implemented by fs? */
	अचिन्हित no_access:1;

	/** Is create not implemented by fs? */
	अचिन्हित no_create:1;

	/** Is पूर्णांकerrupt not implemented by fs? */
	अचिन्हित no_पूर्णांकerrupt:1;

	/** Is bmap not implemented by fs? */
	अचिन्हित no_bmap:1;

	/** Is poll not implemented by fs? */
	अचिन्हित no_poll:1;

	/** Do multi-page cached ग_लिखोs */
	अचिन्हित big_ग_लिखोs:1;

	/** Don't apply umask to creation modes */
	अचिन्हित करोnt_mask:1;

	/** Are BSD file locking primitives not implemented by fs? */
	अचिन्हित no_flock:1;

	/** Is fallocate not implemented by fs? */
	अचिन्हित no_fallocate:1;

	/** Is नाम with flags implemented by fs? */
	अचिन्हित no_नाम2:1;

	/** Use enhanced/स्वतःmatic page cache invalidation. */
	अचिन्हित स्वतः_inval_data:1;

	/** Fileप्रणाली is fully responsible क्रम page cache invalidation. */
	अचिन्हित explicit_inval_data:1;

	/** Does the fileप्रणाली support सूची_पढ़ोplus? */
	अचिन्हित करो_सूची_पढ़ोplus:1;

	/** Does the fileप्रणाली want adaptive सूची_पढ़ोplus? */
	अचिन्हित सूची_पढ़ोplus_स्वतः:1;

	/** Does the fileप्रणाली support asynchronous direct-IO submission? */
	अचिन्हित async_dio:1;

	/** Is lseek not implemented by fs? */
	अचिन्हित no_lseek:1;

	/** Does the fileप्रणाली support posix acls? */
	अचिन्हित posix_acl:1;

	/** Check permissions based on the file mode or not? */
	अचिन्हित शेष_permissions:1;

	/** Allow other than the mounter user to access the fileप्रणाली ? */
	अचिन्हित allow_other:1;

	/** Does the fileप्रणाली support copy_file_range? */
	अचिन्हित no_copy_file_range:1;

	/* Send DESTROY request */
	अचिन्हित पूर्णांक destroy:1;

	/* Delete dentries that have gone stale */
	अचिन्हित पूर्णांक delete_stale:1;

	/** Do not create entry in fusectl fs */
	अचिन्हित पूर्णांक no_control:1;

	/** Do not allow MNT_FORCE umount */
	अचिन्हित पूर्णांक no_क्रमce_umount:1;

	/* Auto-mount submounts announced by the server */
	अचिन्हित पूर्णांक स्वतः_submounts:1;

	/** The number of requests रुकोing क्रम completion */
	atomic_t num_रुकोing;

	/** Negotiated minor version */
	अचिन्हित minor;

	/** Entry on the fuse_mount_list */
	काष्ठा list_head entry;

	/** Device ID from the root super block */
	dev_t dev;

	/** Dentries in the control fileप्रणाली */
	काष्ठा dentry *ctl_dentry[FUSE_CTL_NUM_DENTRIES];

	/** number of dentries used in the above array */
	पूर्णांक ctl_ndents;

	/** Key क्रम lock owner ID scrambling */
	u32 scramble_key[4];

	/** Version counter क्रम attribute changes */
	atomic64_t attr_version;

	/** Called on final put */
	व्योम (*release)(काष्ठा fuse_conn *);

	/**
	 * Read/ग_लिखो semaphore to hold when accessing the sb of any
	 * fuse_mount beदीर्घing to this connection
	 */
	काष्ठा rw_semaphore समाप्तsb;

	/** List of device instances beदीर्घing to this connection */
	काष्ठा list_head devices;

#अगर_घोषित CONFIG_FUSE_DAX
	/* Dax specअगरic conn data, non-शून्य अगर DAX is enabled */
	काष्ठा fuse_conn_dax *dax;
#पूर्ण_अगर

	/** List of fileप्रणालीs using this connection */
	काष्ठा list_head mounts;
पूर्ण;

/*
 * Represents a mounted fileप्रणाली, potentially a submount.
 *
 * This object allows sharing a fuse_conn between separate mounts to
 * allow submounts with dedicated superblocks and thus separate device
 * IDs.
 */
काष्ठा fuse_mount अणु
	/* Underlying (potentially shared) connection to the FUSE server */
	काष्ठा fuse_conn *fc;

	/*
	 * Super block क्रम this connection (fc->समाप्तsb must be held when
	 * accessing this).
	 */
	काष्ठा super_block *sb;

	/* Entry on fc->mounts */
	काष्ठा list_head fc_entry;
पूर्ण;

अटल अंतरभूत काष्ठा fuse_mount *get_fuse_mount_super(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा fuse_conn *get_fuse_conn_super(काष्ठा super_block *sb)
अणु
	वापस get_fuse_mount_super(sb)->fc;
पूर्ण

अटल अंतरभूत काष्ठा fuse_mount *get_fuse_mount(काष्ठा inode *inode)
अणु
	वापस get_fuse_mount_super(inode->i_sb);
पूर्ण

अटल अंतरभूत काष्ठा fuse_conn *get_fuse_conn(काष्ठा inode *inode)
अणु
	वापस get_fuse_mount_super(inode->i_sb)->fc;
पूर्ण

अटल अंतरभूत काष्ठा fuse_inode *get_fuse_inode(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा fuse_inode, inode);
पूर्ण

अटल अंतरभूत u64 get_node_id(काष्ठा inode *inode)
अणु
	वापस get_fuse_inode(inode)->nodeid;
पूर्ण

अटल अंतरभूत पूर्णांक invalid_nodeid(u64 nodeid)
अणु
	वापस !nodeid || nodeid == FUSE_ROOT_ID;
पूर्ण

अटल अंतरभूत u64 fuse_get_attr_version(काष्ठा fuse_conn *fc)
अणु
	वापस atomic64_पढ़ो(&fc->attr_version);
पूर्ण

अटल अंतरभूत व्योम fuse_make_bad(काष्ठा inode *inode)
अणु
	हटाओ_inode_hash(inode);
	set_bit(FUSE_I_BAD, &get_fuse_inode(inode)->state);
पूर्ण

अटल अंतरभूत bool fuse_is_bad(काष्ठा inode *inode)
अणु
	वापस unlikely(test_bit(FUSE_I_BAD, &get_fuse_inode(inode)->state));
पूर्ण

अटल अंतरभूत काष्ठा page **fuse_pages_alloc(अचिन्हित पूर्णांक npages, gfp_t flags,
					     काष्ठा fuse_page_desc **desc)
अणु
	काष्ठा page **pages;

	pages = kzalloc(npages * (माप(काष्ठा page *) +
				  माप(काष्ठा fuse_page_desc)), flags);
	*desc = (व्योम *) (pages + npages);

	वापस pages;
पूर्ण

अटल अंतरभूत व्योम fuse_page_descs_length_init(काष्ठा fuse_page_desc *descs,
					       अचिन्हित पूर्णांक index,
					       अचिन्हित पूर्णांक nr_pages)
अणु
	पूर्णांक i;

	क्रम (i = index; i < index + nr_pages; i++)
		descs[i].length = PAGE_SIZE - descs[i].offset;
पूर्ण

/** Device operations */
बाह्य स्थिर काष्ठा file_operations fuse_dev_operations;

बाह्य स्थिर काष्ठा dentry_operations fuse_dentry_operations;
बाह्य स्थिर काष्ठा dentry_operations fuse_root_dentry_operations;

/**
 * Get a filled in inode
 */
काष्ठा inode *fuse_iget(काष्ठा super_block *sb, u64 nodeid,
			पूर्णांक generation, काष्ठा fuse_attr *attr,
			u64 attr_valid, u64 attr_version);

पूर्णांक fuse_lookup_name(काष्ठा super_block *sb, u64 nodeid, स्थिर काष्ठा qstr *name,
		     काष्ठा fuse_entry_out *outarg, काष्ठा inode **inode);

/**
 * Send FORGET command
 */
व्योम fuse_queue_क्रमget(काष्ठा fuse_conn *fc, काष्ठा fuse_क्रमget_link *क्रमget,
		       u64 nodeid, u64 nlookup);

काष्ठा fuse_क्रमget_link *fuse_alloc_क्रमget(व्योम);

काष्ठा fuse_क्रमget_link *fuse_dequeue_क्रमget(काष्ठा fuse_iqueue *fiq,
					     अचिन्हित पूर्णांक max,
					     अचिन्हित पूर्णांक *countp);

/*
 * Initialize READ or READसूची request
 */
काष्ठा fuse_io_args अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा fuse_पढ़ो_in in;
			u64 attr_ver;
		पूर्ण पढ़ो;
		काष्ठा अणु
			काष्ठा fuse_ग_लिखो_in in;
			काष्ठा fuse_ग_लिखो_out out;
			bool page_locked;
		पूर्ण ग_लिखो;
	पूर्ण;
	काष्ठा fuse_args_pages ap;
	काष्ठा fuse_io_priv *io;
	काष्ठा fuse_file *ff;
पूर्ण;

व्योम fuse_पढ़ो_args_fill(काष्ठा fuse_io_args *ia, काष्ठा file *file, loff_t pos,
			 माप_प्रकार count, पूर्णांक opcode);


/**
 * Send OPEN or OPENसूची request
 */
पूर्णांक fuse_खोलो_common(काष्ठा inode *inode, काष्ठा file *file, bool isdir);

काष्ठा fuse_file *fuse_file_alloc(काष्ठा fuse_mount *fm);
व्योम fuse_file_मुक्त(काष्ठा fuse_file *ff);
व्योम fuse_finish_खोलो(काष्ठा inode *inode, काष्ठा file *file);

व्योम fuse_sync_release(काष्ठा fuse_inode *fi, काष्ठा fuse_file *ff,
		       अचिन्हित पूर्णांक flags);

/**
 * Send RELEASE or RELEASEसूची request
 */
व्योम fuse_release_common(काष्ठा file *file, bool isdir);

/**
 * Send FSYNC or FSYNCसूची request
 */
पूर्णांक fuse_fsync_common(काष्ठा file *file, loff_t start, loff_t end,
		      पूर्णांक datasync, पूर्णांक opcode);

/**
 * Notअगरy poll wakeup
 */
पूर्णांक fuse_notअगरy_poll_wakeup(काष्ठा fuse_conn *fc,
			    काष्ठा fuse_notअगरy_poll_wakeup_out *outarg);

/**
 * Initialize file operations on a regular file
 */
व्योम fuse_init_file_inode(काष्ठा inode *inode);

/**
 * Initialize inode operations on regular files and special files
 */
व्योम fuse_init_common(काष्ठा inode *inode);

/**
 * Initialize inode and file operations on a directory
 */
व्योम fuse_init_dir(काष्ठा inode *inode);

/**
 * Initialize inode operations on a symlink
 */
व्योम fuse_init_symlink(काष्ठा inode *inode);

/**
 * Change attributes of an inode
 */
व्योम fuse_change_attributes(काष्ठा inode *inode, काष्ठा fuse_attr *attr,
			    u64 attr_valid, u64 attr_version);

व्योम fuse_change_attributes_common(काष्ठा inode *inode, काष्ठा fuse_attr *attr,
				   u64 attr_valid);

/**
 * Initialize the client device
 */
पूर्णांक fuse_dev_init(व्योम);

/**
 * Cleanup the client device
 */
व्योम fuse_dev_cleanup(व्योम);

पूर्णांक fuse_ctl_init(व्योम);
व्योम __निकास fuse_ctl_cleanup(व्योम);

/**
 * Simple request sending that करोes request allocation and मुक्तing
 */
sमाप_प्रकार fuse_simple_request(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args);
पूर्णांक fuse_simple_background(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
			   gfp_t gfp_flags);

/**
 * End a finished request
 */
व्योम fuse_request_end(काष्ठा fuse_req *req);

/* Abort all requests */
व्योम fuse_पात_conn(काष्ठा fuse_conn *fc);
व्योम fuse_रुको_पातed(काष्ठा fuse_conn *fc);

/**
 * Invalidate inode attributes
 */
व्योम fuse_invalidate_attr(काष्ठा inode *inode);

व्योम fuse_invalidate_entry_cache(काष्ठा dentry *entry);

व्योम fuse_invalidate_aसमय(काष्ठा inode *inode);

u64 entry_attr_समयout(काष्ठा fuse_entry_out *o);
व्योम fuse_change_entry_समयout(काष्ठा dentry *entry, काष्ठा fuse_entry_out *o);

/**
 * Acquire reference to fuse_conn
 */
काष्ठा fuse_conn *fuse_conn_get(काष्ठा fuse_conn *fc);

/**
 * Initialize fuse_conn
 */
व्योम fuse_conn_init(काष्ठा fuse_conn *fc, काष्ठा fuse_mount *fm,
		    काष्ठा user_namespace *user_ns,
		    स्थिर काष्ठा fuse_iqueue_ops *fiq_ops, व्योम *fiq_priv);

/**
 * Release reference to fuse_conn
 */
व्योम fuse_conn_put(काष्ठा fuse_conn *fc);

काष्ठा fuse_dev *fuse_dev_alloc_install(काष्ठा fuse_conn *fc);
काष्ठा fuse_dev *fuse_dev_alloc(व्योम);
व्योम fuse_dev_install(काष्ठा fuse_dev *fud, काष्ठा fuse_conn *fc);
व्योम fuse_dev_मुक्त(काष्ठा fuse_dev *fud);
व्योम fuse_send_init(काष्ठा fuse_mount *fm);

/**
 * Fill in superblock and initialize fuse connection
 * @sb: partially-initialized superblock to fill in
 * @ctx: mount context
 */
पूर्णांक fuse_fill_super_common(काष्ठा super_block *sb, काष्ठा fuse_fs_context *ctx);

/*
 * Fill in superblock क्रम submounts
 * @sb: partially-initialized superblock to fill in
 * @parent_fi: The fuse_inode of the parent fileप्रणाली where this submount is
 * 	       mounted
 */
पूर्णांक fuse_fill_super_submount(काष्ठा super_block *sb,
			     काष्ठा fuse_inode *parent_fi);

/*
 * Remove the mount from the connection
 *
 * Returns whether this was the last mount
 */
bool fuse_mount_हटाओ(काष्ठा fuse_mount *fm);

/*
 * Shut करोwn the connection (possibly sending DESTROY request).
 */
व्योम fuse_conn_destroy(काष्ठा fuse_mount *fm);

/**
 * Add connection to control fileप्रणाली
 */
पूर्णांक fuse_ctl_add_conn(काष्ठा fuse_conn *fc);

/**
 * Remove connection from control fileप्रणाली
 */
व्योम fuse_ctl_हटाओ_conn(काष्ठा fuse_conn *fc);

/**
 * Is file type valid?
 */
पूर्णांक fuse_valid_type(पूर्णांक m);

bool fuse_invalid_attr(काष्ठा fuse_attr *attr);

/**
 * Is current process allowed to perक्रमm fileप्रणाली operation?
 */
पूर्णांक fuse_allow_current_process(काष्ठा fuse_conn *fc);

u64 fuse_lock_owner_id(काष्ठा fuse_conn *fc, fl_owner_t id);

व्योम fuse_update_स_समय(काष्ठा inode *inode);

पूर्णांक fuse_update_attributes(काष्ठा inode *inode, काष्ठा file *file);

व्योम fuse_flush_ग_लिखोpages(काष्ठा inode *inode);

व्योम fuse_set_noग_लिखो(काष्ठा inode *inode);
व्योम fuse_release_noग_लिखो(काष्ठा inode *inode);

/**
 * Scan all fuse_mounts beदीर्घing to fc to find the first where
 * ilookup5() वापसs a result.  Return that result and the
 * respective fuse_mount in *fm (unless fm is शून्य).
 *
 * The caller must hold fc->समाप्तsb.
 */
काष्ठा inode *fuse_ilookup(काष्ठा fuse_conn *fc, u64 nodeid,
			   काष्ठा fuse_mount **fm);

/**
 * File-प्रणाली tells the kernel to invalidate cache क्रम the given node id.
 */
पूर्णांक fuse_reverse_inval_inode(काष्ठा fuse_conn *fc, u64 nodeid,
			     loff_t offset, loff_t len);

/**
 * File-प्रणाली tells the kernel to invalidate parent attributes and
 * the dentry matching parent/name.
 *
 * If the child_nodeid is non-zero and:
 *    - matches the inode number क्रम the dentry matching parent/name,
 *    - is not a mount poपूर्णांक
 *    - is a file or oan empty directory
 * then the dentry is unhashed (d_delete()).
 */
पूर्णांक fuse_reverse_inval_entry(काष्ठा fuse_conn *fc, u64 parent_nodeid,
			     u64 child_nodeid, काष्ठा qstr *name);

पूर्णांक fuse_करो_खोलो(काष्ठा fuse_mount *fm, u64 nodeid, काष्ठा file *file,
		 bool isdir);

/**
 * fuse_direct_io() flags
 */

/** If set, it is WRITE; otherwise - READ */
#घोषणा FUSE_DIO_WRITE (1 << 0)

/** CUSE pass fuse_direct_io() a file which f_mapping->host is not from FUSE */
#घोषणा FUSE_DIO_CUSE  (1 << 1)

sमाप_प्रकार fuse_direct_io(काष्ठा fuse_io_priv *io, काष्ठा iov_iter *iter,
		       loff_t *ppos, पूर्णांक flags);
दीर्घ fuse_करो_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		   अचिन्हित पूर्णांक flags);
दीर्घ fuse_ioctl_common(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg, अचिन्हित पूर्णांक flags);
__poll_t fuse_file_poll(काष्ठा file *file, poll_table *रुको);
पूर्णांक fuse_dev_release(काष्ठा inode *inode, काष्ठा file *file);

bool fuse_ग_लिखो_update_size(काष्ठा inode *inode, loff_t pos);

पूर्णांक fuse_flush_बार(काष्ठा inode *inode, काष्ठा fuse_file *ff);
पूर्णांक fuse_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);

पूर्णांक fuse_करो_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr,
		    काष्ठा file *file);

व्योम fuse_set_initialized(काष्ठा fuse_conn *fc);

व्योम fuse_unlock_inode(काष्ठा inode *inode, bool locked);
bool fuse_lock_inode(काष्ठा inode *inode);

पूर्णांक fuse_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *value,
		  माप_प्रकार size, पूर्णांक flags, अचिन्हित पूर्णांक extra_flags);
sमाप_प्रकार fuse_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *value,
		      माप_प्रकार size);
sमाप_प्रकार fuse_listxattr(काष्ठा dentry *entry, अक्षर *list, माप_प्रकार size);
पूर्णांक fuse_हटाओxattr(काष्ठा inode *inode, स्थिर अक्षर *name);
बाह्य स्थिर काष्ठा xattr_handler *fuse_xattr_handlers[];
बाह्य स्थिर काष्ठा xattr_handler *fuse_acl_xattr_handlers[];
बाह्य स्थिर काष्ठा xattr_handler *fuse_no_acl_xattr_handlers[];

काष्ठा posix_acl;
काष्ठा posix_acl *fuse_get_acl(काष्ठा inode *inode, पूर्णांक type);
पूर्णांक fuse_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		 काष्ठा posix_acl *acl, पूर्णांक type);

/* सूची_पढ़ो.c */
पूर्णांक fuse_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx);

/**
 * Return the number of bytes in an arguments list
 */
अचिन्हित पूर्णांक fuse_len_args(अचिन्हित पूर्णांक numargs, काष्ठा fuse_arg *args);

/**
 * Get the next unique ID क्रम a request
 */
u64 fuse_get_unique(काष्ठा fuse_iqueue *fiq);
व्योम fuse_मुक्त_conn(काष्ठा fuse_conn *fc);

/* dax.c */

#घोषणा FUSE_IS_DAX(inode) (IS_ENABLED(CONFIG_FUSE_DAX) && IS_DAX(inode))

sमाप_प्रकार fuse_dax_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to);
sमाप_प्रकार fuse_dax_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from);
पूर्णांक fuse_dax_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक fuse_dax_अवरोध_layouts(काष्ठा inode *inode, u64 dmap_start, u64 dmap_end);
पूर्णांक fuse_dax_conn_alloc(काष्ठा fuse_conn *fc, काष्ठा dax_device *dax_dev);
व्योम fuse_dax_conn_मुक्त(काष्ठा fuse_conn *fc);
bool fuse_dax_inode_alloc(काष्ठा super_block *sb, काष्ठा fuse_inode *fi);
व्योम fuse_dax_inode_init(काष्ठा inode *inode);
व्योम fuse_dax_inode_cleanup(काष्ठा inode *inode);
bool fuse_dax_check_alignment(काष्ठा fuse_conn *fc, अचिन्हित पूर्णांक map_alignment);
व्योम fuse_dax_cancel_work(काष्ठा fuse_conn *fc);

/* ioctl.c */
दीर्घ fuse_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ fuse_file_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg);
पूर्णांक fuse_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक fuse_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa);

/* file.c */

काष्ठा fuse_file *fuse_file_खोलो(काष्ठा fuse_mount *fm, u64 nodeid,
				 अचिन्हित पूर्णांक खोलो_flags, bool isdir);
व्योम fuse_file_release(काष्ठा inode *inode, काष्ठा fuse_file *ff,
		       अचिन्हित पूर्णांक खोलो_flags, fl_owner_t id, bool isdir);

#पूर्ण_अगर /* _FS_FUSE_I_H */
