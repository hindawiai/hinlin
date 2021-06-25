<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

/*
 *  The ORANGEFS Linux kernel support allows ORANGEFS volumes to be mounted and
 *  accessed through the Linux VFS (i.e. using standard I/O प्रणाली calls).
 *  This support is only needed on clients that wish to mount the file प्रणाली.
 *
 */

/*
 *  Declarations and macros क्रम the ORANGEFS Linux kernel support.
 */

#अगर_अघोषित __ORANGEFSKERNEL_H
#घोषणा __ORANGEFSKERNEL_H

#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/statfs.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/device.h>
#समावेश <linux/mpage.h>
#समावेश <linux/namei.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/aपन.स>
#समावेश <linux/posix_acl.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/compat.h>
#समावेश <linux/mount.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uपन.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dcache.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/poll.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/xattr.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/hashtable.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "orangefs-dev-proto.h"

#घोषणा ORANGEFS_DEFAULT_OP_TIMEOUT_SECS       20

#घोषणा ORANGEFS_BUFMAP_WAIT_TIMEOUT_SECS   30

#घोषणा ORANGEFS_DEFAULT_SLOT_TIMEOUT_SECS     900	/* 15 minutes */

#घोषणा ORANGEFS_REQDEVICE_NAME          "pvfs2-req"

#घोषणा ORANGEFS_DEVREQ_MAGIC             0x20030529
#घोषणा ORANGEFS_PURGE_RETRY_COUNT     0x00000005

#घोषणा MAX_DEV_REQ_UPSIZE (2 * माप(__s32) +   \
माप(__u64) + माप(काष्ठा orangefs_upcall_s))
#घोषणा MAX_DEV_REQ_DOWNSIZE (2 * माप(__s32) + \
माप(__u64) + माप(काष्ठा orangefs_करोwncall_s))

/*
 * valid orangefs kernel operation states
 *
 * unknown  - op was just initialized
 * रुकोing  - op is on request_list (upward bound)
 * inprogr  - op is in progress (रुकोing क्रम करोwncall)
 * serviced - op has matching करोwncall; ok
 * purged   - op has to start a समयr since client-core
 *            निकासed uncleanly beक्रमe servicing op
 * given up - submitter has given up रुकोing क्रम it
 */
क्रमागत orangefs_vfs_op_states अणु
	OP_VFS_STATE_UNKNOWN = 0,
	OP_VFS_STATE_WAITING = 1,
	OP_VFS_STATE_INPROGR = 2,
	OP_VFS_STATE_SERVICED = 4,
	OP_VFS_STATE_PURGED = 8,
	OP_VFS_STATE_GIVEN_UP = 16,
पूर्ण;

/*
 * orangefs kernel memory related flags
 */

#अगर (defined CONFIG_DEBUG_SLAB)
#घोषणा ORANGEFS_CACHE_CREATE_FLAGS SLAB_RED_ZONE
#अन्यथा
#घोषणा ORANGEFS_CACHE_CREATE_FLAGS 0
#पूर्ण_अगर

बाह्य पूर्णांक orangefs_init_acl(काष्ठा inode *inode, काष्ठा inode *dir);
बाह्य स्थिर काष्ठा xattr_handler *orangefs_xattr_handlers[];

बाह्य काष्ठा posix_acl *orangefs_get_acl(काष्ठा inode *inode, पूर्णांक type);
बाह्य पूर्णांक orangefs_set_acl(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *inode, काष्ठा posix_acl *acl,
			    पूर्णांक type);

/*
 * orangefs data काष्ठाures
 */
काष्ठा orangefs_kernel_op_s अणु
	क्रमागत orangefs_vfs_op_states op_state;
	__u64 tag;

	/*
	 * Set uses_shared_memory to non zero अगर this operation uses
	 * shared memory. If true, then a retry on the op must also
	 * get a new shared memory buffer and re-populate it.
	 * Cancels करोn't care - it only matters क्रम service_operation()
	 * retry logics and cancels करोn't go through it anymore. It
	 * safely stays non-zero when we use it as slot_to_मुक्त.
	 */
	जोड़ अणु
		पूर्णांक uses_shared_memory;
		पूर्णांक slot_to_मुक्त;
	पूर्ण;

	काष्ठा orangefs_upcall_s upcall;
	काष्ठा orangefs_करोwncall_s करोwncall;

	काष्ठा completion रुकोq;
	spinlock_t lock;

	पूर्णांक attempts;

	काष्ठा list_head list;
पूर्ण;

#घोषणा set_op_state_रुकोing(op)     ((op)->op_state = OP_VFS_STATE_WAITING)
#घोषणा set_op_state_inprogress(op)  ((op)->op_state = OP_VFS_STATE_INPROGR)
#घोषणा set_op_state_given_up(op)  ((op)->op_state = OP_VFS_STATE_GIVEN_UP)
अटल अंतरभूत व्योम set_op_state_serviced(काष्ठा orangefs_kernel_op_s *op)
अणु
	op->op_state = OP_VFS_STATE_SERVICED;
	complete(&op->रुकोq);
पूर्ण

#घोषणा op_state_रुकोing(op)     ((op)->op_state & OP_VFS_STATE_WAITING)
#घोषणा op_state_in_progress(op) ((op)->op_state & OP_VFS_STATE_INPROGR)
#घोषणा op_state_serviced(op)    ((op)->op_state & OP_VFS_STATE_SERVICED)
#घोषणा op_state_purged(op)      ((op)->op_state & OP_VFS_STATE_PURGED)
#घोषणा op_state_given_up(op)    ((op)->op_state & OP_VFS_STATE_GIVEN_UP)
#घोषणा op_is_cancel(op)         ((op)->upcall.type == ORANGEFS_VFS_OP_CANCEL)

व्योम op_release(काष्ठा orangefs_kernel_op_s *op);

बाह्य व्योम orangefs_bufmap_put(पूर्णांक);
अटल अंतरभूत व्योम put_cancel(काष्ठा orangefs_kernel_op_s *op)
अणु
	orangefs_bufmap_put(op->slot_to_मुक्त);
	op_release(op);
पूर्ण

अटल अंतरभूत व्योम set_op_state_purged(काष्ठा orangefs_kernel_op_s *op)
अणु
	spin_lock(&op->lock);
	अगर (unlikely(op_is_cancel(op))) अणु
		list_del_init(&op->list);
		spin_unlock(&op->lock);
		put_cancel(op);
	पूर्ण अन्यथा अणु
		op->op_state |= OP_VFS_STATE_PURGED;
		complete(&op->रुकोq);
		spin_unlock(&op->lock);
	पूर्ण
पूर्ण

/* per inode निजी orangefs info */
काष्ठा orangefs_inode_s अणु
	काष्ठा orangefs_object_kref refn;
	अक्षर link_target[ORANGEFS_NAME_MAX];
	/*
	 * Reading/Writing Extended attributes need to acquire the appropriate
	 * पढ़ोer/ग_लिखोr semaphore on the orangefs_inode_s काष्ठाure.
	 */
	काष्ठा rw_semaphore xattr_sem;

	काष्ठा inode vfs_inode;
	sector_t last_failed_block_index_पढ़ो;

	अचिन्हित दीर्घ getattr_समय;
	अचिन्हित दीर्घ mapping_समय;
	पूर्णांक attr_valid;
	kuid_t attr_uid;
	kgid_t attr_gid;
	अचिन्हित दीर्घ bitlock;

	DECLARE_HASHTABLE(xattr_cache, 4);
पूर्ण;

/* per superblock निजी orangefs info */
काष्ठा orangefs_sb_info_s अणु
	काष्ठा orangefs_khandle root_khandle;
	__s32 fs_id;
	पूर्णांक id;
	पूर्णांक flags;
#घोषणा ORANGEFS_OPT_INTR	0x01
#घोषणा ORANGEFS_OPT_LOCAL_LOCK	0x02
	अक्षर devname[ORANGEFS_MAX_SERVER_ADDR_LEN];
	काष्ठा super_block *sb;
	पूर्णांक mount_pending;
	पूर्णांक no_list;
	काष्ठा list_head list;
पूर्ण;

काष्ठा orangefs_stats अणु
	अचिन्हित दीर्घ cache_hits;
	अचिन्हित दीर्घ cache_misses;
	अचिन्हित दीर्घ पढ़ोs;
	अचिन्हित दीर्घ ग_लिखोs;
पूर्ण;

काष्ठा orangefs_cached_xattr अणु
	काष्ठा hlist_node node;
	अक्षर key[ORANGEFS_MAX_XATTR_NAMELEN];
	अक्षर val[ORANGEFS_MAX_XATTR_VALUELEN];
	sमाप_प्रकार length;
	अचिन्हित दीर्घ समयout;
पूर्ण;

काष्ठा orangefs_ग_लिखो_range अणु
	loff_t pos;
	माप_प्रकार len;
	kuid_t uid;
	kgid_t gid;
पूर्ण;

बाह्य काष्ठा orangefs_stats orangefs_stats;

/*
 * NOTE: See Documentation/fileप्रणालीs/porting.rst क्रम inक्रमmation
 * on implementing FOO_I and properly accessing fs निजी data
 */
अटल अंतरभूत काष्ठा orangefs_inode_s *ORANGEFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा orangefs_inode_s, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा orangefs_sb_info_s *ORANGEFS_SB(काष्ठा super_block *sb)
अणु
	वापस (काष्ठा orangefs_sb_info_s *) sb->s_fs_info;
पूर्ण

/* ino_t descends from "unsigned long", 8 bytes, 64 bits. */
अटल अंतरभूत ino_t orangefs_khandle_to_ino(काष्ठा orangefs_khandle *khandle)
अणु
	जोड़ अणु
		अचिन्हित अक्षर u[8];
		__u64 ino;
	पूर्ण ihandle;

	ihandle.u[0] = khandle->u[0] ^ khandle->u[4];
	ihandle.u[1] = khandle->u[1] ^ khandle->u[5];
	ihandle.u[2] = khandle->u[2] ^ khandle->u[6];
	ihandle.u[3] = khandle->u[3] ^ khandle->u[7];
	ihandle.u[4] = khandle->u[12] ^ khandle->u[8];
	ihandle.u[5] = khandle->u[13] ^ khandle->u[9];
	ihandle.u[6] = khandle->u[14] ^ khandle->u[10];
	ihandle.u[7] = khandle->u[15] ^ khandle->u[11];

	वापस ihandle.ino;
पूर्ण

अटल अंतरभूत काष्ठा orangefs_khandle *get_khandle_from_ino(काष्ठा inode *inode)
अणु
	वापस &(ORANGEFS_I(inode)->refn.khandle);
पूर्ण

अटल अंतरभूत पूर्णांक is_root_handle(काष्ठा inode *inode)
अणु
	gossip_debug(GOSSIP_DCACHE_DEBUG,
		     "%s: root handle: %pU, this handle: %pU:\n",
		     __func__,
		     &ORANGEFS_SB(inode->i_sb)->root_khandle,
		     get_khandle_from_ino(inode));

	अगर (ORANGEFS_khandle_cmp(&(ORANGEFS_SB(inode->i_sb)->root_khandle),
			     get_khandle_from_ino(inode)))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक match_handle(काष्ठा orangefs_khandle resp_handle,
			       काष्ठा inode *inode)
अणु
	gossip_debug(GOSSIP_DCACHE_DEBUG,
		     "%s: one handle: %pU, another handle:%pU:\n",
		     __func__,
		     &resp_handle,
		     get_khandle_from_ino(inode));

	अगर (ORANGEFS_khandle_cmp(&resp_handle, get_khandle_from_ino(inode)))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

/*
 * defined in orangefs-cache.c
 */
पूर्णांक op_cache_initialize(व्योम);
पूर्णांक op_cache_finalize(व्योम);
काष्ठा orangefs_kernel_op_s *op_alloc(__s32 type);
व्योम orangefs_new_tag(काष्ठा orangefs_kernel_op_s *op);
अक्षर *get_opname_string(काष्ठा orangefs_kernel_op_s *new_op);

पूर्णांक orangefs_inode_cache_initialize(व्योम);
पूर्णांक orangefs_inode_cache_finalize(व्योम);

/*
 * defined in orangefs-mod.c
 */
व्योम purge_inprogress_ops(व्योम);

/*
 * defined in रुकोqueue.c
 */
व्योम purge_रुकोing_ops(व्योम);

/*
 * defined in super.c
 */
बाह्य uपूर्णांक64_t orangefs_features;

काष्ठा dentry *orangefs_mount(काष्ठा file_प्रणाली_type *fst,
			   पूर्णांक flags,
			   स्थिर अक्षर *devname,
			   व्योम *data);

व्योम orangefs_समाप्त_sb(काष्ठा super_block *sb);
पूर्णांक orangefs_remount(काष्ठा orangefs_sb_info_s *);

पूर्णांक fsid_key_table_initialize(व्योम);
व्योम fsid_key_table_finalize(व्योम);

/*
 * defined in inode.c
 */
vm_fault_t orangefs_page_mkग_लिखो(काष्ठा vm_fault *);
काष्ठा inode *orangefs_new_inode(काष्ठा super_block *sb,
			      काष्ठा inode *dir,
			      पूर्णांक mode,
			      dev_t dev,
			      काष्ठा orangefs_object_kref *ref);

पूर्णांक __orangefs_setattr(काष्ठा inode *, काष्ठा iattr *);
पूर्णांक orangefs_setattr(काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);

पूर्णांक orangefs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		     काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags);

पूर्णांक orangefs_permission(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *inode, पूर्णांक mask);

पूर्णांक orangefs_update_समय(काष्ठा inode *, काष्ठा बारpec64 *, पूर्णांक);

/*
 * defined in xattr.c
 */
sमाप_प्रकार orangefs_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size);

/*
 * defined in namei.c
 */
काष्ठा inode *orangefs_iget(काष्ठा super_block *sb,
			 काष्ठा orangefs_object_kref *ref);

/*
 * defined in devorangefs-req.c
 */
बाह्य uपूर्णांक32_t orangefs_userspace_version;

पूर्णांक orangefs_dev_init(व्योम);
व्योम orangefs_dev_cleanup(व्योम);
पूर्णांक is_daemon_in_service(व्योम);
bool __is_daemon_in_service(व्योम);

/*
 * defined in file.c
 */
पूर्णांक orangefs_revalidate_mapping(काष्ठा inode *);
sमाप_प्रकार रुको_क्रम_direct_io(क्रमागत ORANGEFS_io_type, काष्ठा inode *, loff_t *,
    काष्ठा iov_iter *, माप_प्रकार, loff_t, काष्ठा orangefs_ग_लिखो_range *, पूर्णांक *,
    काष्ठा file *);
sमाप_प्रकार करो_पढ़ोv_ग_लिखोv(क्रमागत ORANGEFS_io_type, काष्ठा file *, loff_t *,
    काष्ठा iov_iter *);

/*
 * defined in orangefs-utils.c
 */
__s32 fsid_of_op(काष्ठा orangefs_kernel_op_s *op);

sमाप_प्रकार orangefs_inode_getxattr(काष्ठा inode *inode,
			     स्थिर अक्षर *name,
			     व्योम *buffer,
			     माप_प्रकार size);

पूर्णांक orangefs_inode_setxattr(काष्ठा inode *inode,
			 स्थिर अक्षर *name,
			 स्थिर व्योम *value,
			 माप_प्रकार size,
			 पूर्णांक flags);

#घोषणा ORANGEFS_GETATTR_NEW 1
#घोषणा ORANGEFS_GETATTR_SIZE 2

पूर्णांक orangefs_inode_getattr(काष्ठा inode *, पूर्णांक);

पूर्णांक orangefs_inode_check_changed(काष्ठा inode *inode);

पूर्णांक orangefs_inode_setattr(काष्ठा inode *inode);

bool orangefs_cancel_op_in_progress(काष्ठा orangefs_kernel_op_s *op);

पूर्णांक orangefs_normalize_to_त्रुटि_सं(__s32 error_code);

बाह्य काष्ठा mutex orangefs_request_mutex;
बाह्य पूर्णांक op_समयout_secs;
बाह्य पूर्णांक slot_समयout_secs;
बाह्य पूर्णांक orangefs_cache_समयout_msecs;
बाह्य पूर्णांक orangefs_dcache_समयout_msecs;
बाह्य पूर्णांक orangefs_getattr_समयout_msecs;
बाह्य काष्ठा list_head orangefs_superblocks;
बाह्य spinlock_t orangefs_superblocks_lock;
बाह्य काष्ठा list_head orangefs_request_list;
बाह्य spinlock_t orangefs_request_list_lock;
बाह्य रुको_queue_head_t orangefs_request_list_रुकोq;
बाह्य काष्ठा list_head *orangefs_htable_ops_in_progress;
बाह्य spinlock_t orangefs_htable_ops_in_progress_lock;
बाह्य पूर्णांक hash_table_size;

बाह्य स्थिर काष्ठा file_operations orangefs_file_operations;
बाह्य स्थिर काष्ठा inode_operations orangefs_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations orangefs_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations orangefs_dir_operations;
बाह्य स्थिर काष्ठा dentry_operations orangefs_dentry_operations;

/*
 * misc convenience macros
 */

#घोषणा ORANGEFS_OP_INTERRUPTIBLE 1   /* service_operation() is पूर्णांकerruptible */
#घोषणा ORANGEFS_OP_PRIORITY      2   /* service_operation() is high priority */
#घोषणा ORANGEFS_OP_CANCELLATION  4   /* this is a cancellation */
#घोषणा ORANGEFS_OP_NO_MUTEX      8   /* करोn't acquire request_mutex */
#घोषणा ORANGEFS_OP_ASYNC         16  /* Queue it, but करोn't रुको */
#घोषणा ORANGEFS_OP_WRITEBACK     32

पूर्णांक service_operation(काष्ठा orangefs_kernel_op_s *op,
		      स्थिर अक्षर *op_name,
		      पूर्णांक flags);

#घोषणा get_पूर्णांकerruptible_flag(inode) \
	((ORANGEFS_SB(inode->i_sb)->flags & ORANGEFS_OPT_INTR) ? \
		ORANGEFS_OP_INTERRUPTIBLE : 0)

#घोषणा fill_शेष_sys_attrs(sys_attr, type, mode)			\
करो अणु									\
	sys_attr.owner = from_kuid(&init_user_ns, current_fsuid()); \
	sys_attr.group = from_kgid(&init_user_ns, current_fsgid()); \
	sys_attr.perms = ORANGEFS_util_translate_mode(mode);		\
	sys_attr.mसमय = 0;						\
	sys_attr.aसमय = 0;						\
	sys_attr.स_समय = 0;						\
	sys_attr.mask = ORANGEFS_ATTR_SYS_ALL_SETABLE;			\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम orangefs_set_समयout(काष्ठा dentry *dentry)
अणु
	अचिन्हित दीर्घ समय = jअगरfies + orangefs_dcache_समयout_msecs*HZ/1000;

	dentry->d_fsdata = (व्योम *) समय;
पूर्ण

#पूर्ण_अगर /* __ORANGEFSKERNEL_H */
