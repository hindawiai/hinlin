<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FS_H
#घोषणा _LINUX_FS_H

#समावेश <linux/linkage.h>
#समावेश <linux/रुको_bit.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/dcache.h>
#समावेश <linux/path.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/cache.h>
#समावेश <linux/list.h>
#समावेश <linux/list_lru.h>
#समावेश <linux/llist.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/xarray.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/init.h>
#समावेश <linux/pid.h>
#समावेश <linux/bug.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/capability.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/rculist_bl.h>
#समावेश <linux/atomic.h>
#समावेश <linux/shrinker.h>
#समावेश <linux/migrate_mode.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/percpu-rwsem.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delayed_call.h>
#समावेश <linux/uuid.h>
#समावेश <linux/errseq.h>
#समावेश <linux/ioprपन.स>
#समावेश <linux/fs_types.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/mount.h>
#समावेश <linux/cred.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <uapi/linux/fs.h>

काष्ठा backing_dev_info;
काष्ठा bdi_ग_लिखोback;
काष्ठा bio;
काष्ठा export_operations;
काष्ठा fiemap_extent_info;
काष्ठा hd_geometry;
काष्ठा iovec;
काष्ठा kiocb;
काष्ठा kobject;
काष्ठा pipe_inode_info;
काष्ठा poll_table_काष्ठा;
काष्ठा kstatfs;
काष्ठा vm_area_काष्ठा;
काष्ठा vfsmount;
काष्ठा cred;
काष्ठा swap_info_काष्ठा;
काष्ठा seq_file;
काष्ठा workqueue_काष्ठा;
काष्ठा iov_iter;
काष्ठा fscrypt_info;
काष्ठा fscrypt_operations;
काष्ठा fsverity_info;
काष्ठा fsverity_operations;
काष्ठा fs_context;
काष्ठा fs_parameter_spec;
काष्ठा fileattr;

बाह्य व्योम __init inode_init(व्योम);
बाह्य व्योम __init inode_init_early(व्योम);
बाह्य व्योम __init files_init(व्योम);
बाह्य व्योम __init files_maxfiles_init(व्योम);

बाह्य काष्ठा files_stat_काष्ठा files_stat;
बाह्य अचिन्हित दीर्घ get_max_files(व्योम);
बाह्य अचिन्हित पूर्णांक sysctl_nr_खोलो;
बाह्य काष्ठा inodes_stat_t inodes_stat;
बाह्य पूर्णांक leases_enable, lease_अवरोध_समय;
बाह्य पूर्णांक sysctl_रक्षित_symlinks;
बाह्य पूर्णांक sysctl_रक्षित_hardlinks;
बाह्य पूर्णांक sysctl_रक्षित_fअगरos;
बाह्य पूर्णांक sysctl_रक्षित_regular;

प्रकार __kernel_rwf_t rwf_t;

काष्ठा buffer_head;
प्रकार पूर्णांक (get_block_t)(काष्ठा inode *inode, sector_t iblock,
			काष्ठा buffer_head *bh_result, पूर्णांक create);
प्रकार पूर्णांक (dio_ioकरोne_t)(काष्ठा kiocb *iocb, loff_t offset,
			sमाप_प्रकार bytes, व्योम *निजी);

#घोषणा MAY_EXEC		0x00000001
#घोषणा MAY_WRITE		0x00000002
#घोषणा MAY_READ		0x00000004
#घोषणा MAY_APPEND		0x00000008
#घोषणा MAY_ACCESS		0x00000010
#घोषणा MAY_OPEN		0x00000020
#घोषणा MAY_CHसूची		0x00000040
/* called from RCU mode, करोn't block */
#घोषणा MAY_NOT_BLOCK		0x00000080

/*
 * flags in file.f_mode.  Note that FMODE_READ and FMODE_WRITE must correspond
 * to O_WRONLY and O_RDWR via the strange trick in करो_dentry_खोलो()
 */

/* file is खोलो क्रम पढ़ोing */
#घोषणा FMODE_READ		((__क्रमce भ_शेषe_t)0x1)
/* file is खोलो क्रम writing */
#घोषणा FMODE_WRITE		((__क्रमce भ_शेषe_t)0x2)
/* file is seekable */
#घोषणा FMODE_LSEEK		((__क्रमce भ_शेषe_t)0x4)
/* file can be accessed using pपढ़ो */
#घोषणा FMODE_PREAD		((__क्रमce भ_शेषe_t)0x8)
/* file can be accessed using pग_लिखो */
#घोषणा FMODE_PWRITE		((__क्रमce भ_शेषe_t)0x10)
/* File is खोलोed क्रम execution with sys_execve / sys_uselib */
#घोषणा FMODE_EXEC		((__क्रमce भ_शेषe_t)0x20)
/* File is खोलोed with O_NDELAY (only set क्रम block devices) */
#घोषणा FMODE_NDELAY		((__क्रमce भ_शेषe_t)0x40)
/* File is खोलोed with O_EXCL (only set क्रम block devices) */
#घोषणा FMODE_EXCL		((__क्रमce भ_शेषe_t)0x80)
/* File is खोलोed using खोलो(.., 3, ..) and is ग_लिखोable only क्रम ioctls
   (specialy hack क्रम floppy.c) */
#घोषणा FMODE_WRITE_IOCTL	((__क्रमce भ_शेषe_t)0x100)
/* 32bit hashes as llseek() offset (क्रम directories) */
#घोषणा FMODE_32BITHASH         ((__क्रमce भ_शेषe_t)0x200)
/* 64bit hashes as llseek() offset (क्रम directories) */
#घोषणा FMODE_64BITHASH         ((__क्रमce भ_शेषe_t)0x400)

/*
 * Don't update स_समय and mसमय.
 *
 * Currently a special hack क्रम the XFS खोलो_by_handle ioctl, but we'll
 * hopefully graduate it to a proper O_CMTIME flag supported by खोलो(2) soon.
 */
#घोषणा FMODE_NOCMTIME		((__क्रमce भ_शेषe_t)0x800)

/* Expect अक्रमom access pattern */
#घोषणा FMODE_RANDOM		((__क्रमce भ_शेषe_t)0x1000)

/* File is huge (eg. /dev/mem): treat loff_t as अचिन्हित */
#घोषणा FMODE_UNSIGNED_OFFSET	((__क्रमce भ_शेषe_t)0x2000)

/* File is खोलोed with O_PATH; almost nothing can be करोne with it */
#घोषणा FMODE_PATH		((__क्रमce भ_शेषe_t)0x4000)

/* File needs atomic accesses to f_pos */
#घोषणा FMODE_ATOMIC_POS	((__क्रमce भ_शेषe_t)0x8000)
/* Write access to underlying fs */
#घोषणा FMODE_WRITER		((__क्रमce भ_शेषe_t)0x10000)
/* Has पढ़ो method(s) */
#घोषणा FMODE_CAN_READ          ((__क्रमce भ_शेषe_t)0x20000)
/* Has ग_लिखो method(s) */
#घोषणा FMODE_CAN_WRITE         ((__क्रमce भ_शेषe_t)0x40000)

#घोषणा FMODE_OPENED		((__क्रमce भ_शेषe_t)0x80000)
#घोषणा FMODE_CREATED		((__क्रमce भ_शेषe_t)0x100000)

/* File is stream-like */
#घोषणा FMODE_STREAM		((__क्रमce भ_शेषe_t)0x200000)

/* File was खोलोed by fanotअगरy and shouldn't generate fanotअगरy events */
#घोषणा FMODE_NONOTIFY		((__क्रमce भ_शेषe_t)0x4000000)

/* File is capable of वापसing -EAGAIN अगर I/O will block */
#घोषणा FMODE_NOWAIT		((__क्रमce भ_शेषe_t)0x8000000)

/* File represents mount that needs unmounting */
#घोषणा FMODE_NEED_UNMOUNT	((__क्रमce भ_शेषe_t)0x10000000)

/* File करोes not contribute to nr_files count */
#घोषणा FMODE_NOACCOUNT		((__क्रमce भ_शेषe_t)0x20000000)

/* File supports async buffered पढ़ोs */
#घोषणा FMODE_BUF_RASYNC	((__क्रमce भ_शेषe_t)0x40000000)

/*
 * Attribute flags.  These should be or-ed together to figure out what
 * has been changed!
 */
#घोषणा ATTR_MODE	(1 << 0)
#घोषणा ATTR_UID	(1 << 1)
#घोषणा ATTR_GID	(1 << 2)
#घोषणा ATTR_SIZE	(1 << 3)
#घोषणा ATTR_ATIME	(1 << 4)
#घोषणा ATTR_MTIME	(1 << 5)
#घोषणा ATTR_CTIME	(1 << 6)
#घोषणा ATTR_ATIME_SET	(1 << 7)
#घोषणा ATTR_MTIME_SET	(1 << 8)
#घोषणा ATTR_FORCE	(1 << 9) /* Not a change, but a change it */
#घोषणा ATTR_KILL_SUID	(1 << 11)
#घोषणा ATTR_KILL_SGID	(1 << 12)
#घोषणा ATTR_खाता	(1 << 13)
#घोषणा ATTR_KILL_PRIV	(1 << 14)
#घोषणा ATTR_OPEN	(1 << 15) /* Truncating from खोलो(O_TRUNC) */
#घोषणा ATTR_TIMES_SET	(1 << 16)
#घोषणा ATTR_TOUCH	(1 << 17)

/*
 * Whiteout is represented by a अक्षर device.  The following स्थिरants define the
 * mode and device number to use.
 */
#घोषणा WHITEOUT_MODE 0
#घोषणा WHITEOUT_DEV 0

/*
 * This is the Inode Attributes काष्ठाure, used क्रम notअगरy_change().  It
 * uses the above definitions as flags, to know which values have changed.
 * Also, in this manner, a Fileप्रणाली can look at only the values it cares
 * about.  Basically, these are the attributes that the VFS layer can
 * request to change from the FS layer.
 *
 * Derek Atkins <warlord@MIT.EDU> 94-10-20
 */
काष्ठा iattr अणु
	अचिन्हित पूर्णांक	ia_valid;
	umode_t		ia_mode;
	kuid_t		ia_uid;
	kgid_t		ia_gid;
	loff_t		ia_size;
	काष्ठा बारpec64 ia_aसमय;
	काष्ठा बारpec64 ia_mसमय;
	काष्ठा बारpec64 ia_स_समय;

	/*
	 * Not an attribute, but an auxiliary info क्रम fileप्रणालीs wanting to
	 * implement an ftruncate() like method.  NOTE: fileप्रणाली should
	 * check क्रम (ia_valid & ATTR_खाता), and not क्रम (ia_file != शून्य).
	 */
	काष्ठा file	*ia_file;
पूर्ण;

/*
 * Includes क्रम diskquotas.
 */
#समावेश <linux/quota.h>

/*
 * Maximum number of layers of fs stack.  Needs to be limited to
 * prevent kernel stack overflow
 */
#घोषणा खाताSYSTEM_MAX_STACK_DEPTH 2

/** 
 * क्रमागत positive_aop_वापसs - aop वापस codes with specअगरic semantics
 *
 * @AOP_WRITEPAGE_ACTIVATE: Inक्रमms the caller that page ग_लिखोback has
 * 			    completed, that the page is still locked, and
 * 			    should be considered active.  The VM uses this hपूर्णांक
 * 			    to वापस the page to the active list -- it won't
 * 			    be a candidate क्रम ग_लिखोback again in the near
 * 			    future.  Other callers must be careful to unlock
 * 			    the page अगर they get this वापस.  Returned by
 * 			    ग_लिखोpage(); 
 *
 * @AOP_TRUNCATED_PAGE: The AOP method that was handed a locked page has
 *  			unlocked it and the page might have been truncated.
 *  			The caller should back up to acquiring a new page and
 *  			trying again.  The aop will be taking reasonable
 *  			precautions not to livelock.  If the caller held a page
 *  			reference, it should drop it beक्रमe retrying.  Returned
 *  			by पढ़ोpage().
 *
 * address_space_operation functions वापस these large स्थिरants to indicate
 * special semantics to the caller.  These are much larger than the bytes in a
 * page to allow क्रम functions that वापस the number of bytes operated on in a
 * given page.
 */

क्रमागत positive_aop_वापसs अणु
	AOP_WRITEPAGE_ACTIVATE	= 0x80000,
	AOP_TRUNCATED_PAGE	= 0x80001,
पूर्ण;

#घोषणा AOP_FLAG_CONT_EXPAND		0x0001 /* called from cont_expand */
#घोषणा AOP_FLAG_NOFS			0x0002 /* used by fileप्रणाली to direct
						* helper code (eg buffer layer)
						* to clear GFP_FS from alloc */

/*
 * oh the beauties of C type declarations.
 */
काष्ठा page;
काष्ठा address_space;
काष्ठा ग_लिखोback_control;
काष्ठा पढ़ोahead_control;

/*
 * Write lअगरe समय hपूर्णांक values.
 * Stored in काष्ठा inode as u8.
 */
क्रमागत rw_hपूर्णांक अणु
	WRITE_LIFE_NOT_SET	= 0,
	WRITE_LIFE_NONE		= RWH_WRITE_LIFE_NONE,
	WRITE_LIFE_SHORT	= RWH_WRITE_LIFE_SHORT,
	WRITE_LIFE_MEDIUM	= RWH_WRITE_LIFE_MEDIUM,
	WRITE_LIFE_LONG		= RWH_WRITE_LIFE_LONG,
	WRITE_LIFE_EXTREME	= RWH_WRITE_LIFE_EXTREME,
पूर्ण;

/* Match RWF_* bits to IOCB bits */
#घोषणा IOCB_HIPRI		(__क्रमce पूर्णांक) RWF_HIPRI
#घोषणा IOCB_DSYNC		(__क्रमce पूर्णांक) RWF_DSYNC
#घोषणा IOCB_SYNC		(__क्रमce पूर्णांक) RWF_SYNC
#घोषणा IOCB_NOWAIT		(__क्रमce पूर्णांक) RWF_NOWAIT
#घोषणा IOCB_APPEND		(__क्रमce पूर्णांक) RWF_APPEND

/* non-RWF related bits - start at 16 */
#घोषणा IOCB_EVENTFD		(1 << 16)
#घोषणा IOCB_सूचीECT		(1 << 17)
#घोषणा IOCB_WRITE		(1 << 18)
/* iocb->ki_रुकोq is valid */
#घोषणा IOCB_WAITQ		(1 << 19)
#घोषणा IOCB_NOIO		(1 << 20)

काष्ठा kiocb अणु
	काष्ठा file		*ki_filp;

	/* The 'ki_filp' poपूर्णांकer is shared in a जोड़ क्रम aio */
	अक्रमomized_काष्ठा_fields_start

	loff_t			ki_pos;
	व्योम (*ki_complete)(काष्ठा kiocb *iocb, दीर्घ ret, दीर्घ ret2);
	व्योम			*निजी;
	पूर्णांक			ki_flags;
	u16			ki_hपूर्णांक;
	u16			ki_ioprio; /* See linux/ioprपन.स */
	जोड़ अणु
		अचिन्हित पूर्णांक		ki_cookie; /* क्रम ->iopoll */
		काष्ठा रुको_page_queue	*ki_रुकोq; /* क्रम async buffered IO */
	पूर्ण;

	अक्रमomized_काष्ठा_fields_end
पूर्ण;

अटल अंतरभूत bool is_sync_kiocb(काष्ठा kiocb *kiocb)
अणु
	वापस kiocb->ki_complete == शून्य;
पूर्ण

/*
 * "descriptor" क्रम what we're up to with a पढ़ो.
 * This allows us to use the same पढ़ो code yet
 * have multiple dअगरferent users of the data that
 * we पढ़ो from a file.
 *
 * The simplest हाल just copies the data to user
 * mode.
 */
प्रकार काष्ठा अणु
	माप_प्रकार written;
	माप_प्रकार count;
	जोड़ अणु
		अक्षर __user *buf;
		व्योम *data;
	पूर्ण arg;
	पूर्णांक error;
पूर्ण पढ़ो_descriptor_t;

प्रकार पूर्णांक (*पढ़ो_actor_t)(पढ़ो_descriptor_t *, काष्ठा page *,
		अचिन्हित दीर्घ, अचिन्हित दीर्घ);

काष्ठा address_space_operations अणु
	पूर्णांक (*ग_लिखोpage)(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc);
	पूर्णांक (*पढ़ोpage)(काष्ठा file *, काष्ठा page *);

	/* Write back some dirty pages from this mapping. */
	पूर्णांक (*ग_लिखोpages)(काष्ठा address_space *, काष्ठा ग_लिखोback_control *);

	/* Set a page dirty.  Return true अगर this dirtied it */
	पूर्णांक (*set_page_dirty)(काष्ठा page *page);

	/*
	 * Reads in the requested pages. Unlike ->पढ़ोpage(), this is
	 * PURELY used क्रम पढ़ो-ahead!.
	 */
	पूर्णांक (*पढ़ोpages)(काष्ठा file *filp, काष्ठा address_space *mapping,
			काष्ठा list_head *pages, अचिन्हित nr_pages);
	व्योम (*पढ़ोahead)(काष्ठा पढ़ोahead_control *);

	पूर्णांक (*ग_लिखो_begin)(काष्ठा file *, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित flags,
				काष्ठा page **pagep, व्योम **fsdata);
	पूर्णांक (*ग_लिखो_end)(काष्ठा file *, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित copied,
				काष्ठा page *page, व्योम *fsdata);

	/* Unक्रमtunately this kludge is needed क्रम FIBMAP. Don't use it */
	sector_t (*bmap)(काष्ठा address_space *, sector_t);
	व्योम (*invalidatepage) (काष्ठा page *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
	पूर्णांक (*releasepage) (काष्ठा page *, gfp_t);
	व्योम (*मुक्तpage)(काष्ठा page *);
	sमाप_प्रकार (*direct_IO)(काष्ठा kiocb *, काष्ठा iov_iter *iter);
	/*
	 * migrate the contents of a page to the specअगरied target. If
	 * migrate_mode is MIGRATE_ASYNC, it must not block.
	 */
	पूर्णांक (*migratepage) (काष्ठा address_space *,
			काष्ठा page *, काष्ठा page *, क्रमागत migrate_mode);
	bool (*isolate_page)(काष्ठा page *, isolate_mode_t);
	व्योम (*putback_page)(काष्ठा page *);
	पूर्णांक (*launder_page) (काष्ठा page *);
	पूर्णांक (*is_partially_uptodate) (काष्ठा page *, अचिन्हित दीर्घ,
					अचिन्हित दीर्घ);
	व्योम (*is_dirty_ग_लिखोback) (काष्ठा page *, bool *, bool *);
	पूर्णांक (*error_हटाओ_page)(काष्ठा address_space *, काष्ठा page *);

	/* swapfile support */
	पूर्णांक (*swap_activate)(काष्ठा swap_info_काष्ठा *sis, काष्ठा file *file,
				sector_t *span);
	व्योम (*swap_deactivate)(काष्ठा file *file);
पूर्ण;

बाह्य स्थिर काष्ठा address_space_operations empty_aops;

/*
 * pagecache_ग_लिखो_begin/pagecache_ग_लिखो_end must be used by general code
 * to ग_लिखो पूर्णांकo the pagecache.
 */
पूर्णांक pagecache_ग_लिखो_begin(काष्ठा file *, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित flags,
				काष्ठा page **pagep, व्योम **fsdata);

पूर्णांक pagecache_ग_लिखो_end(काष्ठा file *, काष्ठा address_space *mapping,
				loff_t pos, अचिन्हित len, अचिन्हित copied,
				काष्ठा page *page, व्योम *fsdata);

/**
 * काष्ठा address_space - Contents of a cacheable, mappable object.
 * @host: Owner, either the inode or the block_device.
 * @i_pages: Cached pages.
 * @gfp_mask: Memory allocation flags to use क्रम allocating pages.
 * @i_mmap_writable: Number of VM_SHARED mappings.
 * @nr_thps: Number of THPs in the pagecache (non-shmem only).
 * @i_mmap: Tree of निजी and shared mappings.
 * @i_mmap_rwsem: Protects @i_mmap and @i_mmap_writable.
 * @nrpages: Number of page entries, रक्षित by the i_pages lock.
 * @ग_लिखोback_index: Writeback starts here.
 * @a_ops: Methods.
 * @flags: Error bits and flags (AS_*).
 * @wb_err: The most recent error which has occurred.
 * @निजी_lock: For use by the owner of the address_space.
 * @निजी_list: For use by the owner of the address_space.
 * @निजी_data: For use by the owner of the address_space.
 */
काष्ठा address_space अणु
	काष्ठा inode		*host;
	काष्ठा xarray		i_pages;
	gfp_t			gfp_mask;
	atomic_t		i_mmap_writable;
#अगर_घोषित CONFIG_READ_ONLY_THP_FOR_FS
	/* number of thp, only क्रम non-shmem files */
	atomic_t		nr_thps;
#पूर्ण_अगर
	काष्ठा rb_root_cached	i_mmap;
	काष्ठा rw_semaphore	i_mmap_rwsem;
	अचिन्हित दीर्घ		nrpages;
	pgoff_t			ग_लिखोback_index;
	स्थिर काष्ठा address_space_operations *a_ops;
	अचिन्हित दीर्घ		flags;
	errseq_t		wb_err;
	spinlock_t		निजी_lock;
	काष्ठा list_head	निजी_list;
	व्योम			*निजी_data;
पूर्ण __attribute__((aligned(माप(दीर्घ)))) __अक्रमomize_layout;
	/*
	 * On most architectures that alignment is alपढ़ोy the हाल; but
	 * must be enक्रमced here क्रम CRIS, to let the least signअगरicant bit
	 * of काष्ठा page's "mapping" poपूर्णांकer be used क्रम PAGE_MAPPING_ANON.
	 */

/* XArray tags, क्रम tagging dirty and ग_लिखोback pages in the pagecache. */
#घोषणा PAGECACHE_TAG_सूचीTY	XA_MARK_0
#घोषणा PAGECACHE_TAG_WRITEBACK	XA_MARK_1
#घोषणा PAGECACHE_TAG_TOWRITE	XA_MARK_2

/*
 * Returns true अगर any of the pages in the mapping are marked with the tag.
 */
अटल अंतरभूत bool mapping_tagged(काष्ठा address_space *mapping, xa_mark_t tag)
अणु
	वापस xa_marked(&mapping->i_pages, tag);
पूर्ण

अटल अंतरभूत व्योम i_mmap_lock_ग_लिखो(काष्ठा address_space *mapping)
अणु
	करोwn_ग_लिखो(&mapping->i_mmap_rwsem);
पूर्ण

अटल अंतरभूत पूर्णांक i_mmap_trylock_ग_लिखो(काष्ठा address_space *mapping)
अणु
	वापस करोwn_ग_लिखो_trylock(&mapping->i_mmap_rwsem);
पूर्ण

अटल अंतरभूत व्योम i_mmap_unlock_ग_लिखो(काष्ठा address_space *mapping)
अणु
	up_ग_लिखो(&mapping->i_mmap_rwsem);
पूर्ण

अटल अंतरभूत व्योम i_mmap_lock_पढ़ो(काष्ठा address_space *mapping)
अणु
	करोwn_पढ़ो(&mapping->i_mmap_rwsem);
पूर्ण

अटल अंतरभूत व्योम i_mmap_unlock_पढ़ो(काष्ठा address_space *mapping)
अणु
	up_पढ़ो(&mapping->i_mmap_rwsem);
पूर्ण

अटल अंतरभूत व्योम i_mmap_निश्चित_locked(काष्ठा address_space *mapping)
अणु
	lockdep_निश्चित_held(&mapping->i_mmap_rwsem);
पूर्ण

अटल अंतरभूत व्योम i_mmap_निश्चित_ग_लिखो_locked(काष्ठा address_space *mapping)
अणु
	lockdep_निश्चित_held_ग_लिखो(&mapping->i_mmap_rwsem);
पूर्ण

/*
 * Might pages of this file be mapped पूर्णांकo userspace?
 */
अटल अंतरभूत पूर्णांक mapping_mapped(काष्ठा address_space *mapping)
अणु
	वापस	!RB_EMPTY_ROOT(&mapping->i_mmap.rb_root);
पूर्ण

/*
 * Might pages of this file have been modअगरied in userspace?
 * Note that i_mmap_writable counts all VM_SHARED vmas: करो_mmap
 * marks vma as VM_SHARED अगर it is shared, and the file was खोलोed क्रम
 * writing i.e. vma may be mरक्षित writable even अगर now पढ़ोonly.
 *
 * If i_mmap_writable is negative, no new writable mappings are allowed. You
 * can only deny writable mappings, अगर none exists right now.
 */
अटल अंतरभूत पूर्णांक mapping_writably_mapped(काष्ठा address_space *mapping)
अणु
	वापस atomic_पढ़ो(&mapping->i_mmap_writable) > 0;
पूर्ण

अटल अंतरभूत पूर्णांक mapping_map_writable(काष्ठा address_space *mapping)
अणु
	वापस atomic_inc_unless_negative(&mapping->i_mmap_writable) ?
		0 : -EPERM;
पूर्ण

अटल अंतरभूत व्योम mapping_unmap_writable(काष्ठा address_space *mapping)
अणु
	atomic_dec(&mapping->i_mmap_writable);
पूर्ण

अटल अंतरभूत पूर्णांक mapping_deny_writable(काष्ठा address_space *mapping)
अणु
	वापस atomic_dec_unless_positive(&mapping->i_mmap_writable) ?
		0 : -EBUSY;
पूर्ण

अटल अंतरभूत व्योम mapping_allow_writable(काष्ठा address_space *mapping)
अणु
	atomic_inc(&mapping->i_mmap_writable);
पूर्ण

/*
 * Use sequence counter to get consistent i_size on 32-bit processors.
 */
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
#समावेश <linux/seqlock.h>
#घोषणा __NEED_I_SIZE_ORDERED
#घोषणा i_size_ordered_init(inode) seqcount_init(&inode->i_size_seqcount)
#अन्यथा
#घोषणा i_size_ordered_init(inode) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा posix_acl;
#घोषणा ACL_NOT_CACHED ((व्योम *)(-1))
#घोषणा ACL_DONT_CACHE ((व्योम *)(-3))

अटल अंतरभूत काष्ठा posix_acl *
uncached_acl_sentinel(काष्ठा task_काष्ठा *task)
अणु
	वापस (व्योम *)task + 1;
पूर्ण

अटल अंतरभूत bool
is_uncached_acl(काष्ठा posix_acl *acl)
अणु
	वापस (दीर्घ)acl & 1;
पूर्ण

#घोषणा IOP_FASTPERM	0x0001
#घोषणा IOP_LOOKUP	0x0002
#घोषणा IOP_NOFOLLOW	0x0004
#घोषणा IOP_XATTR	0x0008
#घोषणा IOP_DEFAULT_READLINK	0x0010

काष्ठा fsnotअगरy_mark_connector;

/*
 * Keep mostly पढ़ो-only and often accessed (especially क्रम
 * the RCU path lookup and 'stat' data) fields at the beginning
 * of the 'struct inode'
 */
काष्ठा inode अणु
	umode_t			i_mode;
	अचिन्हित लघु		i_opflags;
	kuid_t			i_uid;
	kgid_t			i_gid;
	अचिन्हित पूर्णांक		i_flags;

#अगर_घोषित CONFIG_FS_POSIX_ACL
	काष्ठा posix_acl	*i_acl;
	काष्ठा posix_acl	*i_शेष_acl;
#पूर्ण_अगर

	स्थिर काष्ठा inode_operations	*i_op;
	काष्ठा super_block	*i_sb;
	काष्ठा address_space	*i_mapping;

#अगर_घोषित CONFIG_SECURITY
	व्योम			*i_security;
#पूर्ण_अगर

	/* Stat data, not accessed from path walking */
	अचिन्हित दीर्घ		i_ino;
	/*
	 * Fileप्रणालीs may only पढ़ो i_nlink directly.  They shall use the
	 * following functions क्रम modअगरication:
	 *
	 *    (set|clear|inc|drop)_nlink
	 *    inode_(inc|dec)_link_count
	 */
	जोड़ अणु
		स्थिर अचिन्हित पूर्णांक i_nlink;
		अचिन्हित पूर्णांक __i_nlink;
	पूर्ण;
	dev_t			i_rdev;
	loff_t			i_size;
	काष्ठा बारpec64	i_aसमय;
	काष्ठा बारpec64	i_mसमय;
	काष्ठा बारpec64	i_स_समय;
	spinlock_t		i_lock;	/* i_blocks, i_bytes, maybe i_size */
	अचिन्हित लघु          i_bytes;
	u8			i_blkbits;
	u8			i_ग_लिखो_hपूर्णांक;
	blkcnt_t		i_blocks;

#अगर_घोषित __NEED_I_SIZE_ORDERED
	seqcount_t		i_size_seqcount;
#पूर्ण_अगर

	/* Misc */
	अचिन्हित दीर्घ		i_state;
	काष्ठा rw_semaphore	i_rwsem;

	अचिन्हित दीर्घ		dirtied_when;	/* jअगरfies of first dirtying */
	अचिन्हित दीर्घ		dirtied_समय_when;

	काष्ठा hlist_node	i_hash;
	काष्ठा list_head	i_io_list;	/* backing dev IO list */
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	काष्ठा bdi_ग_लिखोback	*i_wb;		/* the associated cgroup wb */

	/* क्रमeign inode detection, see wbc_detach_inode() */
	पूर्णांक			i_wb_frn_winner;
	u16			i_wb_frn_avg_समय;
	u16			i_wb_frn_history;
#पूर्ण_अगर
	काष्ठा list_head	i_lru;		/* inode LRU list */
	काष्ठा list_head	i_sb_list;
	काष्ठा list_head	i_wb_list;	/* backing dev ग_लिखोback list */
	जोड़ अणु
		काष्ठा hlist_head	i_dentry;
		काष्ठा rcu_head		i_rcu;
	पूर्ण;
	atomic64_t		i_version;
	atomic64_t		i_sequence; /* see futex */
	atomic_t		i_count;
	atomic_t		i_dio_count;
	atomic_t		i_ग_लिखोcount;
#अगर defined(CONFIG_IMA) || defined(CONFIG_खाता_LOCKING)
	atomic_t		i_पढ़ोcount; /* काष्ठा files खोलो RO */
#पूर्ण_अगर
	जोड़ अणु
		स्थिर काष्ठा file_operations	*i_fop;	/* क्रमmer ->i_op->शेष_file_ops */
		व्योम (*मुक्त_inode)(काष्ठा inode *);
	पूर्ण;
	काष्ठा file_lock_context	*i_flctx;
	काष्ठा address_space	i_data;
	काष्ठा list_head	i_devices;
	जोड़ अणु
		काष्ठा pipe_inode_info	*i_pipe;
		काष्ठा cdev		*i_cdev;
		अक्षर			*i_link;
		अचिन्हित		i_dir_seq;
	पूर्ण;

	__u32			i_generation;

#अगर_घोषित CONFIG_FSNOTIFY
	__u32			i_fsnotअगरy_mask; /* all events this inode cares about */
	काष्ठा fsnotअगरy_mark_connector __rcu	*i_fsnotअगरy_marks;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FS_ENCRYPTION
	काष्ठा fscrypt_info	*i_crypt_info;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FS_VERITY
	काष्ठा fsverity_info	*i_verity_info;
#पूर्ण_अगर

	व्योम			*i_निजी; /* fs or device निजी poपूर्णांकer */
पूर्ण __अक्रमomize_layout;

काष्ठा बारpec64 बारtamp_truncate(काष्ठा बारpec64 t, काष्ठा inode *inode);

अटल अंतरभूत अचिन्हित पूर्णांक i_blocksize(स्थिर काष्ठा inode *node)
अणु
	वापस (1 << node->i_blkbits);
पूर्ण

अटल अंतरभूत पूर्णांक inode_unhashed(काष्ठा inode *inode)
अणु
	वापस hlist_unhashed(&inode->i_hash);
पूर्ण

/*
 * __mark_inode_dirty expects inodes to be hashed.  Since we करोn't
 * want special inodes in the fileset inode space, we make them
 * appear hashed, but करो not put on any lists.  hlist_del()
 * will work fine and require no locking.
 */
अटल अंतरभूत व्योम inode_fake_hash(काष्ठा inode *inode)
अणु
	hlist_add_fake(&inode->i_hash);
पूर्ण

/*
 * inode->i_mutex nesting subclasses क्रम the lock validator:
 *
 * 0: the object of the current VFS operation
 * 1: parent
 * 2: child/target
 * 3: xattr
 * 4: second non-directory
 * 5: second parent (when locking independent directories in नाम)
 *
 * I_MUTEX_NONसूची2 is क्रम certain operations (such as नाम) which lock two
 * non-directories at once.
 *
 * The locking order between these classes is
 * parent[2] -> child -> gअक्रमchild -> normal -> xattr -> second non-directory
 */
क्रमागत inode_i_mutex_lock_class
अणु
	I_MUTEX_NORMAL,
	I_MUTEX_PARENT,
	I_MUTEX_CHILD,
	I_MUTEX_XATTR,
	I_MUTEX_NONसूची2,
	I_MUTEX_PARENT2,
पूर्ण;

अटल अंतरभूत व्योम inode_lock(काष्ठा inode *inode)
अणु
	करोwn_ग_लिखो(&inode->i_rwsem);
पूर्ण

अटल अंतरभूत व्योम inode_unlock(काष्ठा inode *inode)
अणु
	up_ग_लिखो(&inode->i_rwsem);
पूर्ण

अटल अंतरभूत व्योम inode_lock_shared(काष्ठा inode *inode)
अणु
	करोwn_पढ़ो(&inode->i_rwsem);
पूर्ण

अटल अंतरभूत व्योम inode_unlock_shared(काष्ठा inode *inode)
अणु
	up_पढ़ो(&inode->i_rwsem);
पूर्ण

अटल अंतरभूत पूर्णांक inode_trylock(काष्ठा inode *inode)
अणु
	वापस करोwn_ग_लिखो_trylock(&inode->i_rwsem);
पूर्ण

अटल अंतरभूत पूर्णांक inode_trylock_shared(काष्ठा inode *inode)
अणु
	वापस करोwn_पढ़ो_trylock(&inode->i_rwsem);
पूर्ण

अटल अंतरभूत पूर्णांक inode_is_locked(काष्ठा inode *inode)
अणु
	वापस rwsem_is_locked(&inode->i_rwsem);
पूर्ण

अटल अंतरभूत व्योम inode_lock_nested(काष्ठा inode *inode, अचिन्हित subclass)
अणु
	करोwn_ग_लिखो_nested(&inode->i_rwsem, subclass);
पूर्ण

अटल अंतरभूत व्योम inode_lock_shared_nested(काष्ठा inode *inode, अचिन्हित subclass)
अणु
	करोwn_पढ़ो_nested(&inode->i_rwsem, subclass);
पूर्ण

व्योम lock_two_nondirectories(काष्ठा inode *, काष्ठा inode*);
व्योम unlock_two_nondirectories(काष्ठा inode *, काष्ठा inode*);

/*
 * NOTE: in a 32bit arch with a preemptable kernel and
 * an UP compile the i_size_पढ़ो/ग_लिखो must be atomic
 * with respect to the local cpu (unlike with preempt disabled),
 * but they करोn't need to be atomic with respect to other cpus like in
 * true SMP (so they need either to either locally disable irq around
 * the पढ़ो or क्रम example on x86 they can be still implemented as a
 * cmpxchg8b without the need of the lock prefix). For SMP compiles
 * and 64bit archs it makes no dअगरference अगर preempt is enabled or not.
 */
अटल अंतरभूत loff_t i_size_पढ़ो(स्थिर काष्ठा inode *inode)
अणु
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	loff_t i_size;
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqcount_begin(&inode->i_size_seqcount);
		i_size = inode->i_size;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&inode->i_size_seqcount, seq));
	वापस i_size;
#या_अगर BITS_PER_LONG==32 && defined(CONFIG_PREEMPTION)
	loff_t i_size;

	preempt_disable();
	i_size = inode->i_size;
	preempt_enable();
	वापस i_size;
#अन्यथा
	वापस inode->i_size;
#पूर्ण_अगर
पूर्ण

/*
 * NOTE: unlike i_size_पढ़ो(), i_size_ग_लिखो() करोes need locking around it
 * (normally i_mutex), otherwise on 32bit/SMP an update of i_size_seqcount
 * can be lost, resulting in subsequent i_size_पढ़ो() calls spinning क्रमever.
 */
अटल अंतरभूत व्योम i_size_ग_लिखो(काष्ठा inode *inode, loff_t i_size)
अणु
#अगर BITS_PER_LONG==32 && defined(CONFIG_SMP)
	preempt_disable();
	ग_लिखो_seqcount_begin(&inode->i_size_seqcount);
	inode->i_size = i_size;
	ग_लिखो_seqcount_end(&inode->i_size_seqcount);
	preempt_enable();
#या_अगर BITS_PER_LONG==32 && defined(CONFIG_PREEMPTION)
	preempt_disable();
	inode->i_size = i_size;
	preempt_enable();
#अन्यथा
	inode->i_size = i_size;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित iminor(स्थिर काष्ठा inode *inode)
अणु
	वापस MINOR(inode->i_rdev);
पूर्ण

अटल अंतरभूत अचिन्हित imajor(स्थिर काष्ठा inode *inode)
अणु
	वापस MAJOR(inode->i_rdev);
पूर्ण

काष्ठा fown_काष्ठा अणु
	rwlock_t lock;          /* protects pid, uid, euid fields */
	काष्ठा pid *pid;	/* pid or -pgrp where SIGIO should be sent */
	क्रमागत pid_type pid_type;	/* Kind of process group SIGIO should be sent to */
	kuid_t uid, euid;	/* uid/euid of process setting the owner */
	पूर्णांक signum;		/* posix.1b rt संकेत to be delivered on IO */
पूर्ण;

/**
 * काष्ठा file_ra_state - Track a file's पढ़ोahead state.
 * @start: Where the most recent पढ़ोahead started.
 * @size: Number of pages पढ़ो in the most recent पढ़ोahead.
 * @async_size: Start next पढ़ोahead when this many pages are left.
 * @ra_pages: Maximum size of a पढ़ोahead request.
 * @mmap_miss: How many mmap accesses missed in the page cache.
 * @prev_pos: The last byte in the most recent पढ़ो request.
 */
काष्ठा file_ra_state अणु
	pgoff_t start;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक async_size;
	अचिन्हित पूर्णांक ra_pages;
	अचिन्हित पूर्णांक mmap_miss;
	loff_t prev_pos;
पूर्ण;

/*
 * Check अगर @index falls in the पढ़ोahead winकरोws.
 */
अटल अंतरभूत पूर्णांक ra_has_index(काष्ठा file_ra_state *ra, pgoff_t index)
अणु
	वापस (index >= ra->start &&
		index <  ra->start + ra->size);
पूर्ण

काष्ठा file अणु
	जोड़ अणु
		काष्ठा llist_node	fu_llist;
		काष्ठा rcu_head 	fu_rcuhead;
	पूर्ण f_u;
	काष्ठा path		f_path;
	काष्ठा inode		*f_inode;	/* cached value */
	स्थिर काष्ठा file_operations	*f_op;

	/*
	 * Protects f_ep, f_flags.
	 * Must not be taken from IRQ context.
	 */
	spinlock_t		f_lock;
	क्रमागत rw_hपूर्णांक		f_ग_लिखो_hपूर्णांक;
	atomic_दीर्घ_t		f_count;
	अचिन्हित पूर्णांक 		f_flags;
	भ_शेषe_t			f_mode;
	काष्ठा mutex		f_pos_lock;
	loff_t			f_pos;
	काष्ठा fown_काष्ठा	f_owner;
	स्थिर काष्ठा cred	*f_cred;
	काष्ठा file_ra_state	f_ra;

	u64			f_version;
#अगर_घोषित CONFIG_SECURITY
	व्योम			*f_security;
#पूर्ण_अगर
	/* needed क्रम tty driver, and maybe others */
	व्योम			*निजी_data;

#अगर_घोषित CONFIG_EPOLL
	/* Used by fs/eventpoll.c to link all the hooks to this file */
	काष्ठा hlist_head	*f_ep;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_EPOLL */
	काष्ठा address_space	*f_mapping;
	errseq_t		f_wb_err;
	errseq_t		f_sb_err; /* क्रम syncfs */
पूर्ण __अक्रमomize_layout
  __attribute__((aligned(4)));	/* lest something weird decides that 2 is OK */

काष्ठा file_handle अणु
	__u32 handle_bytes;
	पूर्णांक handle_type;
	/* file identअगरier */
	अचिन्हित अक्षर f_handle[];
पूर्ण;

अटल अंतरभूत काष्ठा file *get_file(काष्ठा file *f)
अणु
	atomic_दीर्घ_inc(&f->f_count);
	वापस f;
पूर्ण
#घोषणा get_file_rcu_many(x, cnt)	\
	atomic_दीर्घ_add_unless(&(x)->f_count, (cnt), 0)
#घोषणा get_file_rcu(x) get_file_rcu_many((x), 1)
#घोषणा file_count(x)	atomic_दीर्घ_पढ़ो(&(x)->f_count)

#घोषणा	MAX_NON_LFS	((1UL<<31) - 1)

/* Page cache limit. The fileप्रणालीs should put that पूर्णांकo their s_maxbytes 
   limits, otherwise bad things can happen in VM. */ 
#अगर BITS_PER_LONG==32
#घोषणा MAX_LFS_खाताSIZE	((loff_t)अच_दीर्घ_उच्च << PAGE_SHIFT)
#या_अगर BITS_PER_LONG==64
#घोषणा MAX_LFS_खाताSIZE 	((loff_t)Lदीर्घ_उच्च)
#पूर्ण_अगर

#घोषणा FL_POSIX	1
#घोषणा FL_FLOCK	2
#घोषणा FL_DELEG	4	/* NFSv4 delegation */
#घोषणा FL_ACCESS	8	/* not trying to lock, just looking */
#घोषणा FL_EXISTS	16	/* when unlocking, test क्रम existence */
#घोषणा FL_LEASE	32	/* lease held on this file */
#घोषणा FL_CLOSE	64	/* unlock on बंद */
#घोषणा FL_SLEEP	128	/* A blocking lock */
#घोषणा FL_DOWNGRADE_PENDING	256 /* Lease is being करोwngraded */
#घोषणा FL_UNLOCK_PENDING	512 /* Lease is being broken */
#घोषणा FL_OFDLCK	1024	/* lock is "owned" by काष्ठा file */
#घोषणा FL_LAYOUT	2048	/* outstanding pNFS layout */

#घोषणा FL_CLOSE_POSIX (FL_POSIX | FL_CLOSE)

/*
 * Special वापस value from posix_lock_file() and vfs_lock_file() क्रम
 * asynchronous locking.
 */
#घोषणा खाता_LOCK_DEFERRED 1

/* legacy प्रकार, should eventually be हटाओd */
प्रकार व्योम *fl_owner_t;

काष्ठा file_lock;

काष्ठा file_lock_operations अणु
	व्योम (*fl_copy_lock)(काष्ठा file_lock *, काष्ठा file_lock *);
	व्योम (*fl_release_निजी)(काष्ठा file_lock *);
पूर्ण;

काष्ठा lock_manager_operations अणु
	fl_owner_t (*lm_get_owner)(fl_owner_t);
	व्योम (*lm_put_owner)(fl_owner_t);
	व्योम (*lm_notअगरy)(काष्ठा file_lock *);	/* unblock callback */
	पूर्णांक (*lm_grant)(काष्ठा file_lock *, पूर्णांक);
	bool (*lm_अवरोध)(काष्ठा file_lock *);
	पूर्णांक (*lm_change)(काष्ठा file_lock *, पूर्णांक, काष्ठा list_head *);
	व्योम (*lm_setup)(काष्ठा file_lock *, व्योम **);
	bool (*lm_अवरोधer_owns_lease)(काष्ठा file_lock *);
पूर्ण;

काष्ठा lock_manager अणु
	काष्ठा list_head list;
	/*
	 * NFSv4 and up also want खोलोs blocked during the grace period;
	 * NLM करोesn't care:
	 */
	bool block_खोलोs;
पूर्ण;

काष्ठा net;
व्योम locks_start_grace(काष्ठा net *, काष्ठा lock_manager *);
व्योम locks_end_grace(काष्ठा lock_manager *);
bool locks_in_grace(काष्ठा net *);
bool खोलोs_in_grace(काष्ठा net *);

/* that will die - we need it क्रम nfs_lock_info */
#समावेश <linux/nfs_fs_i.h>

/*
 * काष्ठा file_lock represents a generic "file lock". It's used to represent
 * POSIX byte range locks, BSD (flock) locks, and leases. It's important to
 * note that the same काष्ठा is used to represent both a request क्रम a lock and
 * the lock itself, but the same object is never used क्रम both.
 *
 * FIXME: should we create a separate "struct lock_request" to help distinguish
 * these two uses?
 *
 * The varous i_flctx lists are ordered by:
 *
 * 1) lock owner
 * 2) lock range start
 * 3) lock range end
 *
 * Obviously, the last two criteria only matter क्रम POSIX locks.
 */
काष्ठा file_lock अणु
	काष्ठा file_lock *fl_blocker;	/* The lock, that is blocking us */
	काष्ठा list_head fl_list;	/* link पूर्णांकo file_lock_context */
	काष्ठा hlist_node fl_link;	/* node in global lists */
	काष्ठा list_head fl_blocked_requests;	/* list of requests with
						 * ->fl_blocker poपूर्णांकing here
						 */
	काष्ठा list_head fl_blocked_member;	/* node in
						 * ->fl_blocker->fl_blocked_requests
						 */
	fl_owner_t fl_owner;
	अचिन्हित पूर्णांक fl_flags;
	अचिन्हित अक्षर fl_type;
	अचिन्हित पूर्णांक fl_pid;
	पूर्णांक fl_link_cpu;		/* what cpu's list is this on? */
	रुको_queue_head_t fl_रुको;
	काष्ठा file *fl_file;
	loff_t fl_start;
	loff_t fl_end;

	काष्ठा fasync_काष्ठा *	fl_fasync; /* क्रम lease अवरोध notअगरications */
	/* क्रम lease अवरोधs: */
	अचिन्हित दीर्घ fl_अवरोध_समय;
	अचिन्हित दीर्घ fl_करोwngrade_समय;

	स्थिर काष्ठा file_lock_operations *fl_ops;	/* Callbacks क्रम fileप्रणालीs */
	स्थिर काष्ठा lock_manager_operations *fl_lmops;	/* Callbacks क्रम lockmanagers */
	जोड़ अणु
		काष्ठा nfs_lock_info	nfs_fl;
		काष्ठा nfs4_lock_info	nfs4_fl;
		काष्ठा अणु
			काष्ठा list_head link;	/* link in AFS vnode's pending_locks list */
			पूर्णांक state;		/* state of grant or error अगर -ve */
			अचिन्हित पूर्णांक	debug_id;
		पूर्ण afs;
	पूर्ण fl_u;
पूर्ण __अक्रमomize_layout;

काष्ठा file_lock_context अणु
	spinlock_t		flc_lock;
	काष्ठा list_head	flc_flock;
	काष्ठा list_head	flc_posix;
	काष्ठा list_head	flc_lease;
पूर्ण;

/* The following स्थिरant reflects the upper bound of the file/locking space */
#अगर_अघोषित OFFSET_MAX
#घोषणा INT_LIMIT(x)	(~((x)1 << (माप(x)*8 - 1)))
#घोषणा OFFSET_MAX	INT_LIMIT(loff_t)
#घोषणा OFFT_OFFSET_MAX	INT_LIMIT(off_t)
#पूर्ण_अगर

बाह्य व्योम send_sigio(काष्ठा fown_काष्ठा *fown, पूर्णांक fd, पूर्णांक band);

#घोषणा locks_inode(f) file_inode(f)

#अगर_घोषित CONFIG_खाता_LOCKING
बाह्य पूर्णांक fcntl_getlk(काष्ठा file *, अचिन्हित पूर्णांक, काष्ठा flock *);
बाह्य पूर्णांक fcntl_setlk(अचिन्हित पूर्णांक, काष्ठा file *, अचिन्हित पूर्णांक,
			काष्ठा flock *);

#अगर BITS_PER_LONG == 32
बाह्य पूर्णांक fcntl_getlk64(काष्ठा file *, अचिन्हित पूर्णांक, काष्ठा flock64 *);
बाह्य पूर्णांक fcntl_setlk64(अचिन्हित पूर्णांक, काष्ठा file *, अचिन्हित पूर्णांक,
			काष्ठा flock64 *);
#पूर्ण_अगर

बाह्य पूर्णांक fcntl_setlease(अचिन्हित पूर्णांक fd, काष्ठा file *filp, दीर्घ arg);
बाह्य पूर्णांक fcntl_getlease(काष्ठा file *filp);

/* fs/locks.c */
व्योम locks_मुक्त_lock_context(काष्ठा inode *inode);
व्योम locks_मुक्त_lock(काष्ठा file_lock *fl);
बाह्य व्योम locks_init_lock(काष्ठा file_lock *);
बाह्य काष्ठा file_lock * locks_alloc_lock(व्योम);
बाह्य व्योम locks_copy_lock(काष्ठा file_lock *, काष्ठा file_lock *);
बाह्य व्योम locks_copy_conflock(काष्ठा file_lock *, काष्ठा file_lock *);
बाह्य व्योम locks_हटाओ_posix(काष्ठा file *, fl_owner_t);
बाह्य व्योम locks_हटाओ_file(काष्ठा file *);
बाह्य व्योम locks_release_निजी(काष्ठा file_lock *);
बाह्य व्योम posix_test_lock(काष्ठा file *, काष्ठा file_lock *);
बाह्य पूर्णांक posix_lock_file(काष्ठा file *, काष्ठा file_lock *, काष्ठा file_lock *);
बाह्य पूर्णांक locks_delete_block(काष्ठा file_lock *);
बाह्य पूर्णांक vfs_test_lock(काष्ठा file *, काष्ठा file_lock *);
बाह्य पूर्णांक vfs_lock_file(काष्ठा file *, अचिन्हित पूर्णांक, काष्ठा file_lock *, काष्ठा file_lock *);
बाह्य पूर्णांक vfs_cancel_lock(काष्ठा file *filp, काष्ठा file_lock *fl);
बाह्य पूर्णांक locks_lock_inode_रुको(काष्ठा inode *inode, काष्ठा file_lock *fl);
बाह्य पूर्णांक __अवरोध_lease(काष्ठा inode *inode, अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक type);
बाह्य व्योम lease_get_mसमय(काष्ठा inode *, काष्ठा बारpec64 *समय);
बाह्य पूर्णांक generic_setlease(काष्ठा file *, दीर्घ, काष्ठा file_lock **, व्योम **priv);
बाह्य पूर्णांक vfs_setlease(काष्ठा file *, दीर्घ, काष्ठा file_lock **, व्योम **);
बाह्य पूर्णांक lease_modअगरy(काष्ठा file_lock *, पूर्णांक, काष्ठा list_head *);

काष्ठा notअगरier_block;
बाह्य पूर्णांक lease_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *);
बाह्य व्योम lease_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *);

काष्ठा files_काष्ठा;
बाह्य व्योम show_fd_locks(काष्ठा seq_file *f,
			 काष्ठा file *filp, काष्ठा files_काष्ठा *files);
#अन्यथा /* !CONFIG_खाता_LOCKING */
अटल अंतरभूत पूर्णांक fcntl_getlk(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      काष्ठा flock __user *user)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक fcntl_setlk(अचिन्हित पूर्णांक fd, काष्ठा file *file,
			      अचिन्हित पूर्णांक cmd, काष्ठा flock __user *user)
अणु
	वापस -EACCES;
पूर्ण

#अगर BITS_PER_LONG == 32
अटल अंतरभूत पूर्णांक fcntl_getlk64(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				काष्ठा flock64 __user *user)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक fcntl_setlk64(अचिन्हित पूर्णांक fd, काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, काष्ठा flock64 __user *user)
अणु
	वापस -EACCES;
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत पूर्णांक fcntl_setlease(अचिन्हित पूर्णांक fd, काष्ठा file *filp, दीर्घ arg)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक fcntl_getlease(काष्ठा file *filp)
अणु
	वापस F_UNLCK;
पूर्ण

अटल अंतरभूत व्योम
locks_मुक्त_lock_context(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम locks_init_lock(काष्ठा file_lock *fl)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम locks_copy_conflock(काष्ठा file_lock *new, काष्ठा file_lock *fl)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम locks_copy_lock(काष्ठा file_lock *new, काष्ठा file_lock *fl)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम locks_हटाओ_posix(काष्ठा file *filp, fl_owner_t owner)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम locks_हटाओ_file(काष्ठा file *filp)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम posix_test_lock(काष्ठा file *filp, काष्ठा file_lock *fl)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक posix_lock_file(काष्ठा file *filp, काष्ठा file_lock *fl,
				  काष्ठा file_lock *conflock)
अणु
	वापस -ENOLCK;
पूर्ण

अटल अंतरभूत पूर्णांक locks_delete_block(काष्ठा file_lock *रुकोer)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत पूर्णांक vfs_test_lock(काष्ठा file *filp, काष्ठा file_lock *fl)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक vfs_lock_file(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				काष्ठा file_lock *fl, काष्ठा file_lock *conf)
अणु
	वापस -ENOLCK;
पूर्ण

अटल अंतरभूत पूर्णांक vfs_cancel_lock(काष्ठा file *filp, काष्ठा file_lock *fl)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक locks_lock_inode_रुको(काष्ठा inode *inode, काष्ठा file_lock *fl)
अणु
	वापस -ENOLCK;
पूर्ण

अटल अंतरभूत पूर्णांक __अवरोध_lease(काष्ठा inode *inode, अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम lease_get_mसमय(काष्ठा inode *inode,
				   काष्ठा बारpec64 *समय)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक generic_setlease(काष्ठा file *filp, दीर्घ arg,
				    काष्ठा file_lock **flp, व्योम **priv)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक vfs_setlease(काष्ठा file *filp, दीर्घ arg,
			       काष्ठा file_lock **lease, व्योम **priv)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक lease_modअगरy(काष्ठा file_lock *fl, पूर्णांक arg,
			       काष्ठा list_head *dispose)
अणु
	वापस -EINVAL;
पूर्ण

काष्ठा files_काष्ठा;
अटल अंतरभूत व्योम show_fd_locks(काष्ठा seq_file *f,
			काष्ठा file *filp, काष्ठा files_काष्ठा *files) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_खाता_LOCKING */

अटल अंतरभूत काष्ठा inode *file_inode(स्थिर काष्ठा file *f)
अणु
	वापस f->f_inode;
पूर्ण

अटल अंतरभूत काष्ठा dentry *file_dentry(स्थिर काष्ठा file *file)
अणु
	वापस d_real(file->f_path.dentry, file_inode(file));
पूर्ण

अटल अंतरभूत पूर्णांक locks_lock_file_रुको(काष्ठा file *filp, काष्ठा file_lock *fl)
अणु
	वापस locks_lock_inode_रुको(locks_inode(filp), fl);
पूर्ण

काष्ठा fasync_काष्ठा अणु
	rwlock_t		fa_lock;
	पूर्णांक			magic;
	पूर्णांक			fa_fd;
	काष्ठा fasync_काष्ठा	*fa_next; /* singly linked list */
	काष्ठा file		*fa_file;
	काष्ठा rcu_head		fa_rcu;
पूर्ण;

#घोषणा FASYNC_MAGIC 0x4601

/* SMP safe fasync helpers: */
बाह्य पूर्णांक fasync_helper(पूर्णांक, काष्ठा file *, पूर्णांक, काष्ठा fasync_काष्ठा **);
बाह्य काष्ठा fasync_काष्ठा *fasync_insert_entry(पूर्णांक, काष्ठा file *, काष्ठा fasync_काष्ठा **, काष्ठा fasync_काष्ठा *);
बाह्य पूर्णांक fasync_हटाओ_entry(काष्ठा file *, काष्ठा fasync_काष्ठा **);
बाह्य काष्ठा fasync_काष्ठा *fasync_alloc(व्योम);
बाह्य व्योम fasync_मुक्त(काष्ठा fasync_काष्ठा *);

/* can be called from पूर्णांकerrupts */
बाह्य व्योम समाप्त_fasync(काष्ठा fasync_काष्ठा **, पूर्णांक, पूर्णांक);

बाह्य व्योम __f_setown(काष्ठा file *filp, काष्ठा pid *, क्रमागत pid_type, पूर्णांक क्रमce);
बाह्य पूर्णांक f_setown(काष्ठा file *filp, अचिन्हित दीर्घ arg, पूर्णांक क्रमce);
बाह्य व्योम f_delown(काष्ठा file *filp);
बाह्य pid_t f_getown(काष्ठा file *filp);
बाह्य पूर्णांक send_sigurg(काष्ठा fown_काष्ठा *fown);

/*
 * sb->s_flags.  Note that these mirror the equivalent MS_* flags where
 * represented in both.
 */
#घोषणा SB_RDONLY	 1	/* Mount पढ़ो-only */
#घोषणा SB_NOSUID	 2	/* Ignore suid and sgid bits */
#घोषणा SB_NODEV	 4	/* Disallow access to device special files */
#घोषणा SB_NOEXEC	 8	/* Disallow program execution */
#घोषणा SB_SYNCHRONOUS	16	/* Writes are synced at once */
#घोषणा SB_MANDLOCK	64	/* Allow mandatory locks on an FS */
#घोषणा SB_सूचीSYNC	128	/* Directory modअगरications are synchronous */
#घोषणा SB_NOATIME	1024	/* Do not update access बार. */
#घोषणा SB_NOसूचीATIME	2048	/* Do not update directory access बार */
#घोषणा SB_SILENT	32768
#घोषणा SB_POSIXACL	(1<<16)	/* VFS करोes not apply the umask */
#घोषणा SB_INLINECRYPT	(1<<17)	/* Use blk-crypto क्रम encrypted files */
#घोषणा SB_KERNMOUNT	(1<<22) /* this is a kern_mount call */
#घोषणा SB_I_VERSION	(1<<23) /* Update inode I_version field */
#घोषणा SB_LAZYTIME	(1<<25) /* Update the on-disk [acm]बार lazily */

/* These sb flags are पूर्णांकernal to the kernel */
#घोषणा SB_SUBMOUNT     (1<<26)
#घोषणा SB_FORCE    	(1<<27)
#घोषणा SB_NOSEC	(1<<28)
#घोषणा SB_BORN		(1<<29)
#घोषणा SB_ACTIVE	(1<<30)
#घोषणा SB_NOUSER	(1<<31)

/* These flags relate to encoding and हालfolding */
#घोषणा SB_ENC_STRICT_MODE_FL	(1 << 0)

#घोषणा sb_has_strict_encoding(sb) \
	(sb->s_encoding_flags & SB_ENC_STRICT_MODE_FL)

/*
 *	Umount options
 */

#घोषणा MNT_FORCE	0x00000001	/* Attempt to क्रमcibily umount */
#घोषणा MNT_DETACH	0x00000002	/* Just detach from the tree */
#घोषणा MNT_EXPIRE	0x00000004	/* Mark क्रम expiry */
#घोषणा UMOUNT_NOFOLLOW	0x00000008	/* Don't follow symlink on umount */
#घोषणा UMOUNT_UNUSED	0x80000000	/* Flag guaranteed to be unused */

/* sb->s_अगरlags */
#घोषणा SB_I_CGROUPWB	0x00000001	/* cgroup-aware ग_लिखोback enabled */
#घोषणा SB_I_NOEXEC	0x00000002	/* Ignore executables on this fs */
#घोषणा SB_I_NODEV	0x00000004	/* Ignore devices on this fs */
#घोषणा SB_I_STABLE_WRITES 0x00000008	/* करोn't modअगरy blks until WB is करोne */

/* sb->s_अगरlags to limit user namespace mounts */
#घोषणा SB_I_USERNS_VISIBLE		0x00000010 /* fstype alपढ़ोy mounted */
#घोषणा SB_I_IMA_UNVERIFIABLE_SIGNATURE	0x00000020
#घोषणा SB_I_UNTRUSTED_MOUNTER		0x00000040

#घोषणा SB_I_SKIP_SYNC	0x00000100	/* Skip superblock at global sync */

/* Possible states of 'frozen' field */
क्रमागत अणु
	SB_UNFROZEN = 0,		/* FS is unfrozen */
	SB_FREEZE_WRITE	= 1,		/* Writes, dir ops, ioctls frozen */
	SB_FREEZE_PAGEFAULT = 2,	/* Page faults stopped as well */
	SB_FREEZE_FS = 3,		/* For पूर्णांकernal FS use (e.g. to stop
					 * पूर्णांकernal thपढ़ोs अगर needed) */
	SB_FREEZE_COMPLETE = 4,		/* ->मुक्तze_fs finished successfully */
पूर्ण;

#घोषणा SB_FREEZE_LEVELS (SB_FREEZE_COMPLETE - 1)

काष्ठा sb_ग_लिखोrs अणु
	पूर्णांक				frozen;		/* Is sb frozen? */
	रुको_queue_head_t		रुको_unfrozen;	/* रुको क्रम thaw */
	काष्ठा percpu_rw_semaphore	rw_sem[SB_FREEZE_LEVELS];
पूर्ण;

काष्ठा super_block अणु
	काष्ठा list_head	s_list;		/* Keep this first */
	dev_t			s_dev;		/* search index; _not_ kdev_t */
	अचिन्हित अक्षर		s_blocksize_bits;
	अचिन्हित दीर्घ		s_blocksize;
	loff_t			s_maxbytes;	/* Max file size */
	काष्ठा file_प्रणाली_type	*s_type;
	स्थिर काष्ठा super_operations	*s_op;
	स्थिर काष्ठा dquot_operations	*dq_op;
	स्थिर काष्ठा quotactl_ops	*s_qcop;
	स्थिर काष्ठा export_operations *s_export_op;
	अचिन्हित दीर्घ		s_flags;
	अचिन्हित दीर्घ		s_अगरlags;	/* पूर्णांकernal SB_I_* flags */
	अचिन्हित दीर्घ		s_magic;
	काष्ठा dentry		*s_root;
	काष्ठा rw_semaphore	s_umount;
	पूर्णांक			s_count;
	atomic_t		s_active;
#अगर_घोषित CONFIG_SECURITY
	व्योम                    *s_security;
#पूर्ण_अगर
	स्थिर काष्ठा xattr_handler **s_xattr;
#अगर_घोषित CONFIG_FS_ENCRYPTION
	स्थिर काष्ठा fscrypt_operations	*s_cop;
	काष्ठा key		*s_master_keys; /* master crypto keys in use */
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_VERITY
	स्थिर काष्ठा fsverity_operations *s_vop;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UNICODE
	काष्ठा unicode_map *s_encoding;
	__u16 s_encoding_flags;
#पूर्ण_अगर
	काष्ठा hlist_bl_head	s_roots;	/* alternate root dentries क्रम NFS */
	काष्ठा list_head	s_mounts;	/* list of mounts; _not_ क्रम fs use */
	काष्ठा block_device	*s_bdev;
	काष्ठा backing_dev_info *s_bdi;
	काष्ठा mtd_info		*s_mtd;
	काष्ठा hlist_node	s_instances;
	अचिन्हित पूर्णांक		s_quota_types;	/* Biपंचांगask of supported quota types */
	काष्ठा quota_info	s_dquot;	/* Diskquota specअगरic options */

	काष्ठा sb_ग_लिखोrs	s_ग_लिखोrs;

	/*
	 * Keep s_fs_info, s_समय_gran, s_fsnotअगरy_mask, and
	 * s_fsnotअगरy_marks together क्रम cache efficiency. They are frequently
	 * accessed and rarely modअगरied.
	 */
	व्योम			*s_fs_info;	/* Fileप्रणाली निजी info */

	/* Granularity of c/m/aसमय in ns (cannot be worse than a second) */
	u32			s_समय_gran;
	/* Time limits क्रम c/m/aसमय in seconds */
	समय64_t		   s_समय_min;
	समय64_t		   s_समय_max;
#अगर_घोषित CONFIG_FSNOTIFY
	__u32			s_fsnotअगरy_mask;
	काष्ठा fsnotअगरy_mark_connector __rcu	*s_fsnotअगरy_marks;
#पूर्ण_अगर

	अक्षर			s_id[32];	/* Inक्रमmational name */
	uuid_t			s_uuid;		/* UUID */

	अचिन्हित पूर्णांक		s_max_links;
	भ_शेषe_t			s_mode;

	/*
	 * The next field is क्रम VFS *only*. No fileप्रणालीs have any business
	 * even looking at it. You had been warned.
	 */
	काष्ठा mutex s_vfs_नाम_mutex;	/* Kludge */

	/*
	 * Fileप्रणाली subtype.  If non-empty the fileप्रणाली type field
	 * in /proc/mounts will be "type.subtype"
	 */
	स्थिर अक्षर *s_subtype;

	स्थिर काष्ठा dentry_operations *s_d_op; /* शेष d_op क्रम dentries */

	/*
	 * Saved pool identअगरier क्रम cleancache (-1 means none)
	 */
	पूर्णांक cleancache_poolid;

	काष्ठा shrinker s_shrink;	/* per-sb shrinker handle */

	/* Number of inodes with nlink == 0 but still referenced */
	atomic_दीर्घ_t s_हटाओ_count;

	/* Pending fsnotअगरy inode refs */
	atomic_दीर्घ_t s_fsnotअगरy_inode_refs;

	/* Being remounted पढ़ो-only */
	पूर्णांक s_पढ़ोonly_remount;

	/* per-sb errseq_t क्रम reporting ग_लिखोback errors via syncfs */
	errseq_t s_wb_err;

	/* AIO completions deferred from पूर्णांकerrupt context */
	काष्ठा workqueue_काष्ठा *s_dio_करोne_wq;
	काष्ठा hlist_head s_pins;

	/*
	 * Owning user namespace and शेष context in which to
	 * पूर्णांकerpret fileप्रणाली uids, gids, quotas, device nodes,
	 * xattrs and security labels.
	 */
	काष्ठा user_namespace *s_user_ns;

	/*
	 * The list_lru काष्ठाure is essentially just a poपूर्णांकer to a table
	 * of per-node lru lists, each of which has its own spinlock.
	 * There is no need to put them पूर्णांकo separate cachelines.
	 */
	काष्ठा list_lru		s_dentry_lru;
	काष्ठा list_lru		s_inode_lru;
	काष्ठा rcu_head		rcu;
	काष्ठा work_काष्ठा	destroy_work;

	काष्ठा mutex		s_sync_lock;	/* sync serialisation lock */

	/*
	 * Indicates how deep in a fileप्रणाली stack this SB is
	 */
	पूर्णांक s_stack_depth;

	/* s_inode_list_lock protects s_inodes */
	spinlock_t		s_inode_list_lock ____cacheline_aligned_in_smp;
	काष्ठा list_head	s_inodes;	/* all inodes */

	spinlock_t		s_inode_wblist_lock;
	काष्ठा list_head	s_inodes_wb;	/* ग_लिखोback inodes */
पूर्ण __अक्रमomize_layout;

/* Helper functions so that in most हालs fileप्रणालीs will
 * not need to deal directly with kuid_t and kgid_t and can
 * instead deal with the raw numeric values that are stored
 * in the fileप्रणाली.
 */
अटल अंतरभूत uid_t i_uid_पढ़ो(स्थिर काष्ठा inode *inode)
अणु
	वापस from_kuid(inode->i_sb->s_user_ns, inode->i_uid);
पूर्ण

अटल अंतरभूत gid_t i_gid_पढ़ो(स्थिर काष्ठा inode *inode)
अणु
	वापस from_kgid(inode->i_sb->s_user_ns, inode->i_gid);
पूर्ण

अटल अंतरभूत व्योम i_uid_ग_लिखो(काष्ठा inode *inode, uid_t uid)
अणु
	inode->i_uid = make_kuid(inode->i_sb->s_user_ns, uid);
पूर्ण

अटल अंतरभूत व्योम i_gid_ग_लिखो(काष्ठा inode *inode, gid_t gid)
अणु
	inode->i_gid = make_kgid(inode->i_sb->s_user_ns, gid);
पूर्ण

/**
 * kuid_पूर्णांकo_mnt - map a kuid करोwn पूर्णांकo a mnt_userns
 * @mnt_userns: user namespace of the relevant mount
 * @kuid: kuid to be mapped
 *
 * Return: @kuid mapped according to @mnt_userns.
 * If @kuid has no mapping INVALID_UID is वापसed.
 */
अटल अंतरभूत kuid_t kuid_पूर्णांकo_mnt(काष्ठा user_namespace *mnt_userns,
				   kuid_t kuid)
अणु
	वापस make_kuid(mnt_userns, __kuid_val(kuid));
पूर्ण

/**
 * kgid_पूर्णांकo_mnt - map a kgid करोwn पूर्णांकo a mnt_userns
 * @mnt_userns: user namespace of the relevant mount
 * @kgid: kgid to be mapped
 *
 * Return: @kgid mapped according to @mnt_userns.
 * If @kgid has no mapping INVALID_GID is वापसed.
 */
अटल अंतरभूत kgid_t kgid_पूर्णांकo_mnt(काष्ठा user_namespace *mnt_userns,
				   kgid_t kgid)
अणु
	वापस make_kgid(mnt_userns, __kgid_val(kgid));
पूर्ण

/**
 * i_uid_पूर्णांकo_mnt - map an inode's i_uid करोwn पूर्णांकo a mnt_userns
 * @mnt_userns: user namespace of the mount the inode was found from
 * @inode: inode to map
 *
 * Return: the inode's i_uid mapped करोwn according to @mnt_userns.
 * If the inode's i_uid has no mapping INVALID_UID is वापसed.
 */
अटल अंतरभूत kuid_t i_uid_पूर्णांकo_mnt(काष्ठा user_namespace *mnt_userns,
				    स्थिर काष्ठा inode *inode)
अणु
	वापस kuid_पूर्णांकo_mnt(mnt_userns, inode->i_uid);
पूर्ण

/**
 * i_gid_पूर्णांकo_mnt - map an inode's i_gid करोwn पूर्णांकo a mnt_userns
 * @mnt_userns: user namespace of the mount the inode was found from
 * @inode: inode to map
 *
 * Return: the inode's i_gid mapped करोwn according to @mnt_userns.
 * If the inode's i_gid has no mapping INVALID_GID is वापसed.
 */
अटल अंतरभूत kgid_t i_gid_पूर्णांकo_mnt(काष्ठा user_namespace *mnt_userns,
				    स्थिर काष्ठा inode *inode)
अणु
	वापस kgid_पूर्णांकo_mnt(mnt_userns, inode->i_gid);
पूर्ण

/**
 * kuid_from_mnt - map a kuid up पूर्णांकo a mnt_userns
 * @mnt_userns: user namespace of the relevant mount
 * @kuid: kuid to be mapped
 *
 * Return: @kuid mapped up according to @mnt_userns.
 * If @kuid has no mapping INVALID_UID is वापसed.
 */
अटल अंतरभूत kuid_t kuid_from_mnt(काष्ठा user_namespace *mnt_userns,
				   kuid_t kuid)
अणु
	वापस KUIDT_INIT(from_kuid(mnt_userns, kuid));
पूर्ण

/**
 * kgid_from_mnt - map a kgid up पूर्णांकo a mnt_userns
 * @mnt_userns: user namespace of the relevant mount
 * @kgid: kgid to be mapped
 *
 * Return: @kgid mapped up according to @mnt_userns.
 * If @kgid has no mapping INVALID_GID is वापसed.
 */
अटल अंतरभूत kgid_t kgid_from_mnt(काष्ठा user_namespace *mnt_userns,
				   kgid_t kgid)
अणु
	वापस KGIDT_INIT(from_kgid(mnt_userns, kgid));
पूर्ण

/**
 * mapped_fsuid - वापस caller's fsuid mapped up पूर्णांकo a mnt_userns
 * @mnt_userns: user namespace of the relevant mount
 *
 * Use this helper to initialize a new vfs or fileप्रणाली object based on
 * the caller's fsuid. A common example is initializing the i_uid field of
 * a newly allocated inode triggered by a creation event such as सूची_गढ़ो or
 * O_CREAT. Other examples include the allocation of quotas क्रम a specअगरic
 * user.
 *
 * Return: the caller's current fsuid mapped up according to @mnt_userns.
 */
अटल अंतरभूत kuid_t mapped_fsuid(काष्ठा user_namespace *mnt_userns)
अणु
	वापस kuid_from_mnt(mnt_userns, current_fsuid());
पूर्ण

/**
 * mapped_fsgid - वापस caller's fsgid mapped up पूर्णांकo a mnt_userns
 * @mnt_userns: user namespace of the relevant mount
 *
 * Use this helper to initialize a new vfs or fileप्रणाली object based on
 * the caller's fsgid. A common example is initializing the i_gid field of
 * a newly allocated inode triggered by a creation event such as सूची_गढ़ो or
 * O_CREAT. Other examples include the allocation of quotas क्रम a specअगरic
 * user.
 *
 * Return: the caller's current fsgid mapped up according to @mnt_userns.
 */
अटल अंतरभूत kgid_t mapped_fsgid(काष्ठा user_namespace *mnt_userns)
अणु
	वापस kgid_from_mnt(mnt_userns, current_fsgid());
पूर्ण

/**
 * inode_fsuid_set - initialize inode's i_uid field with callers fsuid
 * @inode: inode to initialize
 * @mnt_userns: user namespace of the mount the inode was found from
 *
 * Initialize the i_uid field of @inode. If the inode was found/created via
 * an idmapped mount map the caller's fsuid according to @mnt_users.
 */
अटल अंतरभूत व्योम inode_fsuid_set(काष्ठा inode *inode,
				   काष्ठा user_namespace *mnt_userns)
अणु
	inode->i_uid = mapped_fsuid(mnt_userns);
पूर्ण

/**
 * inode_fsgid_set - initialize inode's i_gid field with callers fsgid
 * @inode: inode to initialize
 * @mnt_userns: user namespace of the mount the inode was found from
 *
 * Initialize the i_gid field of @inode. If the inode was found/created via
 * an idmapped mount map the caller's fsgid according to @mnt_users.
 */
अटल अंतरभूत व्योम inode_fsgid_set(काष्ठा inode *inode,
				   काष्ठा user_namespace *mnt_userns)
अणु
	inode->i_gid = mapped_fsgid(mnt_userns);
पूर्ण

/**
 * fsuidgid_has_mapping() - check whether caller's fsuid/fsgid is mapped
 * @sb: the superblock we want a mapping in
 * @mnt_userns: user namespace of the relevant mount
 *
 * Check whether the caller's fsuid and fsgid have a valid mapping in the
 * s_user_ns of the superblock @sb. If the caller is on an idmapped mount map
 * the caller's fsuid and fsgid according to the @mnt_userns first.
 *
 * Return: true अगर fsuid and fsgid is mapped, false अगर not.
 */
अटल अंतरभूत bool fsuidgid_has_mapping(काष्ठा super_block *sb,
					काष्ठा user_namespace *mnt_userns)
अणु
	काष्ठा user_namespace *s_user_ns = sb->s_user_ns;

	वापस kuid_has_mapping(s_user_ns, mapped_fsuid(mnt_userns)) &&
	       kgid_has_mapping(s_user_ns, mapped_fsgid(mnt_userns));
पूर्ण

बाह्य काष्ठा बारpec64 current_समय(काष्ठा inode *inode);

/*
 * Snapshotting support.
 */

/*
 * These are पूर्णांकernal functions, please use sb_start_अणुग_लिखो,pagefault,पूर्णांकग_लिखोपूर्ण
 * instead.
 */
अटल अंतरभूत व्योम __sb_end_ग_लिखो(काष्ठा super_block *sb, पूर्णांक level)
अणु
	percpu_up_पढ़ो(sb->s_ग_लिखोrs.rw_sem + level-1);
पूर्ण

अटल अंतरभूत व्योम __sb_start_ग_लिखो(काष्ठा super_block *sb, पूर्णांक level)
अणु
	percpu_करोwn_पढ़ो(sb->s_ग_लिखोrs.rw_sem + level - 1);
पूर्ण

अटल अंतरभूत bool __sb_start_ग_लिखो_trylock(काष्ठा super_block *sb, पूर्णांक level)
अणु
	वापस percpu_करोwn_पढ़ो_trylock(sb->s_ग_लिखोrs.rw_sem + level - 1);
पूर्ण

#घोषणा __sb_ग_लिखोrs_acquired(sb, lev)	\
	percpu_rwsem_acquire(&(sb)->s_ग_लिखोrs.rw_sem[(lev)-1], 1, _THIS_IP_)
#घोषणा __sb_ग_लिखोrs_release(sb, lev)	\
	percpu_rwsem_release(&(sb)->s_ग_लिखोrs.rw_sem[(lev)-1], 1, _THIS_IP_)

/**
 * sb_end_ग_लिखो - drop ग_लिखो access to a superblock
 * @sb: the super we wrote to
 *
 * Decrement number of ग_लिखोrs to the fileप्रणाली. Wake up possible रुकोers
 * wanting to मुक्तze the fileप्रणाली.
 */
अटल अंतरभूत व्योम sb_end_ग_लिखो(काष्ठा super_block *sb)
अणु
	__sb_end_ग_लिखो(sb, SB_FREEZE_WRITE);
पूर्ण

/**
 * sb_end_pagefault - drop ग_लिखो access to a superblock from a page fault
 * @sb: the super we wrote to
 *
 * Decrement number of processes handling ग_लिखो page fault to the fileप्रणाली.
 * Wake up possible रुकोers wanting to मुक्तze the fileप्रणाली.
 */
अटल अंतरभूत व्योम sb_end_pagefault(काष्ठा super_block *sb)
अणु
	__sb_end_ग_लिखो(sb, SB_FREEZE_PAGEFAULT);
पूर्ण

/**
 * sb_end_पूर्णांकग_लिखो - drop ग_लिखो access to a superblock क्रम पूर्णांकernal fs purposes
 * @sb: the super we wrote to
 *
 * Decrement fs-पूर्णांकernal number of ग_लिखोrs to the fileप्रणाली.  Wake up possible
 * रुकोers wanting to मुक्तze the fileप्रणाली.
 */
अटल अंतरभूत व्योम sb_end_पूर्णांकग_लिखो(काष्ठा super_block *sb)
अणु
	__sb_end_ग_लिखो(sb, SB_FREEZE_FS);
पूर्ण

/**
 * sb_start_ग_लिखो - get ग_लिखो access to a superblock
 * @sb: the super we ग_लिखो to
 *
 * When a process wants to ग_लिखो data or metadata to a file प्रणाली (i.e. dirty
 * a page or an inode), it should embed the operation in a sb_start_ग_लिखो() -
 * sb_end_ग_लिखो() pair to get exclusion against file प्रणाली मुक्तzing. This
 * function increments number of ग_लिखोrs preventing मुक्तzing. If the file
 * प्रणाली is alपढ़ोy frozen, the function रुकोs until the file प्रणाली is
 * thawed.
 *
 * Since मुक्तze protection behaves as a lock, users have to preserve
 * ordering of मुक्तze protection and other fileप्रणाली locks. Generally,
 * मुक्तze protection should be the outermost lock. In particular, we have:
 *
 * sb_start_ग_लिखो
 *   -> i_mutex			(ग_लिखो path, truncate, directory ops, ...)
 *   -> s_umount		(मुक्तze_super, thaw_super)
 */
अटल अंतरभूत व्योम sb_start_ग_लिखो(काष्ठा super_block *sb)
अणु
	__sb_start_ग_लिखो(sb, SB_FREEZE_WRITE);
पूर्ण

अटल अंतरभूत bool sb_start_ग_लिखो_trylock(काष्ठा super_block *sb)
अणु
	वापस __sb_start_ग_लिखो_trylock(sb, SB_FREEZE_WRITE);
पूर्ण

/**
 * sb_start_pagefault - get ग_लिखो access to a superblock from a page fault
 * @sb: the super we ग_लिखो to
 *
 * When a process starts handling ग_लिखो page fault, it should embed the
 * operation पूर्णांकo sb_start_pagefault() - sb_end_pagefault() pair to get
 * exclusion against file प्रणाली मुक्तzing. This is needed since the page fault
 * is going to dirty a page. This function increments number of running page
 * faults preventing मुक्तzing. If the file प्रणाली is alपढ़ोy frozen, the
 * function रुकोs until the file प्रणाली is thawed.
 *
 * Since page fault मुक्तze protection behaves as a lock, users have to preserve
 * ordering of मुक्तze protection and other fileप्रणाली locks. It is advised to
 * put sb_start_pagefault() बंद to mmap_lock in lock ordering. Page fault
 * handling code implies lock dependency:
 *
 * mmap_lock
 *   -> sb_start_pagefault
 */
अटल अंतरभूत व्योम sb_start_pagefault(काष्ठा super_block *sb)
अणु
	__sb_start_ग_लिखो(sb, SB_FREEZE_PAGEFAULT);
पूर्ण

/**
 * sb_start_पूर्णांकग_लिखो - get ग_लिखो access to a superblock क्रम पूर्णांकernal fs purposes
 * @sb: the super we ग_लिखो to
 *
 * This is the third level of protection against fileप्रणाली मुक्तzing. It is
 * मुक्त क्रम use by a fileप्रणाली. The only requirement is that it must rank
 * below sb_start_pagefault.
 *
 * For example fileप्रणाली can call sb_start_पूर्णांकग_लिखो() when starting a
 * transaction which somewhat eases handling of मुक्तzing क्रम पूर्णांकernal sources
 * of fileप्रणाली changes (पूर्णांकernal fs thपढ़ोs, discarding pपुनः_स्मृतिation on file
 * बंद, etc.).
 */
अटल अंतरभूत व्योम sb_start_पूर्णांकग_लिखो(काष्ठा super_block *sb)
अणु
	__sb_start_ग_लिखो(sb, SB_FREEZE_FS);
पूर्ण

अटल अंतरभूत bool sb_start_पूर्णांकग_लिखो_trylock(काष्ठा super_block *sb)
अणु
	वापस __sb_start_ग_लिखो_trylock(sb, SB_FREEZE_FS);
पूर्ण

bool inode_owner_or_capable(काष्ठा user_namespace *mnt_userns,
			    स्थिर काष्ठा inode *inode);

/*
 * VFS helper functions..
 */
पूर्णांक vfs_create(काष्ठा user_namespace *, काष्ठा inode *,
	       काष्ठा dentry *, umode_t, bool);
पूर्णांक vfs_सूची_गढ़ो(काष्ठा user_namespace *, काष्ठा inode *,
	      काष्ठा dentry *, umode_t);
पूर्णांक vfs_mknod(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
              umode_t, dev_t);
पूर्णांक vfs_symlink(काष्ठा user_namespace *, काष्ठा inode *,
		काष्ठा dentry *, स्थिर अक्षर *);
पूर्णांक vfs_link(काष्ठा dentry *, काष्ठा user_namespace *, काष्ठा inode *,
	     काष्ठा dentry *, काष्ठा inode **);
पूर्णांक vfs_सूची_हटाओ(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *);
पूर्णांक vfs_unlink(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
	       काष्ठा inode **);

/**
 * काष्ठा नामdata - contains all inक्रमmation required क्रम renaming
 * @old_mnt_userns:    old user namespace of the mount the inode was found from
 * @old_dir:           parent of source
 * @old_dentry:                source
 * @new_mnt_userns:    new user namespace of the mount the inode was found from
 * @new_dir:           parent of destination
 * @new_dentry:                destination
 * @delegated_inode:   वापसs an inode needing a delegation अवरोध
 * @flags:             नाम flags
 */
काष्ठा नामdata अणु
	काष्ठा user_namespace *old_mnt_userns;
	काष्ठा inode *old_dir;
	काष्ठा dentry *old_dentry;
	काष्ठा user_namespace *new_mnt_userns;
	काष्ठा inode *new_dir;
	काष्ठा dentry *new_dentry;
	काष्ठा inode **delegated_inode;
	अचिन्हित पूर्णांक flags;
पूर्ण __अक्रमomize_layout;

पूर्णांक vfs_नाम(काष्ठा नामdata *);

अटल अंतरभूत पूर्णांक vfs_whiteout(काष्ठा user_namespace *mnt_userns,
			       काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	वापस vfs_mknod(mnt_userns, dir, dentry, S_IFCHR | WHITEOUT_MODE,
			 WHITEOUT_DEV);
पूर्ण

काष्ठा dentry *vfs_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
			   काष्ठा dentry *dentry, umode_t mode, पूर्णांक खोलो_flag);

पूर्णांक vfs_mkobj(काष्ठा dentry *, umode_t,
		पूर्णांक (*f)(काष्ठा dentry *, umode_t, व्योम *),
		व्योम *);

पूर्णांक vfs_fchown(काष्ठा file *file, uid_t user, gid_t group);
पूर्णांक vfs_fchmod(काष्ठा file *file, umode_t mode);
पूर्णांक vfs_uबार(स्थिर काष्ठा path *path, काष्ठा बारpec64 *बार);

बाह्य दीर्घ vfs_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

#अगर_घोषित CONFIG_COMPAT
बाह्य दीर्घ compat_ptr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
					अचिन्हित दीर्घ arg);
#अन्यथा
#घोषणा compat_ptr_ioctl शून्य
#पूर्ण_अगर

/*
 * VFS file helper functions.
 */
व्योम inode_init_owner(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		      स्थिर काष्ठा inode *dir, umode_t mode);
बाह्य bool may_खोलो_dev(स्थिर काष्ठा path *path);

/*
 * This is the "filldir" function type, used by सूची_पढ़ो() to let
 * the kernel specअगरy what kind of dirent layout it wants to have.
 * This allows the kernel to पढ़ो directories पूर्णांकo kernel space or
 * to have dअगरferent dirent layouts depending on the binary type.
 */
काष्ठा dir_context;
प्रकार पूर्णांक (*filldir_t)(काष्ठा dir_context *, स्थिर अक्षर *, पूर्णांक, loff_t, u64,
			 अचिन्हित);

काष्ठा dir_context अणु
	filldir_t actor;
	loff_t pos;
पूर्ण;

/*
 * These flags let !MMU mmap() govern direct device mapping vs immediate
 * copying more easily क्रम MAP_PRIVATE, especially क्रम ROM fileप्रणालीs.
 *
 * NOMMU_MAP_COPY:	Copy can be mapped (MAP_PRIVATE)
 * NOMMU_MAP_सूचीECT:	Can be mapped directly (MAP_SHARED)
 * NOMMU_MAP_READ:	Can be mapped क्रम पढ़ोing
 * NOMMU_MAP_WRITE:	Can be mapped क्रम writing
 * NOMMU_MAP_EXEC:	Can be mapped क्रम execution
 */
#घोषणा NOMMU_MAP_COPY		0x00000001
#घोषणा NOMMU_MAP_सूचीECT	0x00000008
#घोषणा NOMMU_MAP_READ		VM_MAYREAD
#घोषणा NOMMU_MAP_WRITE		VM_MAYWRITE
#घोषणा NOMMU_MAP_EXEC		VM_MAYEXEC

#घोषणा NOMMU_VMFLAGS \
	(NOMMU_MAP_READ | NOMMU_MAP_WRITE | NOMMU_MAP_EXEC)

/*
 * These flags control the behavior of the remap_file_range function poपूर्णांकer.
 * If it is called with len == 0 that means "remap to end of source file".
 * See Documentation/fileप्रणालीs/vfs.rst क्रम more details about this call.
 *
 * REMAP_खाता_DEDUP: only remap अगर contents identical (i.e. deduplicate)
 * REMAP_खाता_CAN_SHORTEN: caller can handle a लघुened request
 */
#घोषणा REMAP_खाता_DEDUP		(1 << 0)
#घोषणा REMAP_खाता_CAN_SHORTEN		(1 << 1)

/*
 * These flags संकेत that the caller is ok with altering various aspects of
 * the behavior of the remap operation.  The changes must be made by the
 * implementation; the vfs remap helper functions can take advantage of them.
 * Flags in this category exist to preserve the quirky behavior of the hoisted
 * btrfs clone/dedupe ioctls.
 */
#घोषणा REMAP_खाता_ADVISORY		(REMAP_खाता_CAN_SHORTEN)

काष्ठा iov_iter;

काष्ठा file_operations अणु
	काष्ठा module *owner;
	loff_t (*llseek) (काष्ठा file *, loff_t, पूर्णांक);
	sमाप_प्रकार (*पढ़ो) (काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
	sमाप_प्रकार (*ग_लिखो) (काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
	sमाप_प्रकार (*पढ़ो_iter) (काष्ठा kiocb *, काष्ठा iov_iter *);
	sमाप_प्रकार (*ग_लिखो_iter) (काष्ठा kiocb *, काष्ठा iov_iter *);
	पूर्णांक (*iopoll)(काष्ठा kiocb *kiocb, bool spin);
	पूर्णांक (*iterate) (काष्ठा file *, काष्ठा dir_context *);
	पूर्णांक (*iterate_shared) (काष्ठा file *, काष्ठा dir_context *);
	__poll_t (*poll) (काष्ठा file *, काष्ठा poll_table_काष्ठा *);
	दीर्घ (*unlocked_ioctl) (काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
	दीर्घ (*compat_ioctl) (काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
	पूर्णांक (*mmap) (काष्ठा file *, काष्ठा vm_area_काष्ठा *);
	अचिन्हित दीर्घ mmap_supported_flags;
	पूर्णांक (*खोलो) (काष्ठा inode *, काष्ठा file *);
	पूर्णांक (*flush) (काष्ठा file *, fl_owner_t id);
	पूर्णांक (*release) (काष्ठा inode *, काष्ठा file *);
	पूर्णांक (*fsync) (काष्ठा file *, loff_t, loff_t, पूर्णांक datasync);
	पूर्णांक (*fasync) (पूर्णांक, काष्ठा file *, पूर्णांक);
	पूर्णांक (*lock) (काष्ठा file *, पूर्णांक, काष्ठा file_lock *);
	sमाप_प्रकार (*sendpage) (काष्ठा file *, काष्ठा page *, पूर्णांक, माप_प्रकार, loff_t *, पूर्णांक);
	अचिन्हित दीर्घ (*get_unmapped_area)(काष्ठा file *, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	पूर्णांक (*check_flags)(पूर्णांक);
	पूर्णांक (*flock) (काष्ठा file *, पूर्णांक, काष्ठा file_lock *);
	sमाप_प्रकार (*splice_ग_लिखो)(काष्ठा pipe_inode_info *, काष्ठा file *, loff_t *, माप_प्रकार, अचिन्हित पूर्णांक);
	sमाप_प्रकार (*splice_पढ़ो)(काष्ठा file *, loff_t *, काष्ठा pipe_inode_info *, माप_प्रकार, अचिन्हित पूर्णांक);
	पूर्णांक (*setlease)(काष्ठा file *, दीर्घ, काष्ठा file_lock **, व्योम **);
	दीर्घ (*fallocate)(काष्ठा file *file, पूर्णांक mode, loff_t offset,
			  loff_t len);
	व्योम (*show_fdinfo)(काष्ठा seq_file *m, काष्ठा file *f);
#अगर_अघोषित CONFIG_MMU
	अचिन्हित (*mmap_capabilities)(काष्ठा file *);
#पूर्ण_अगर
	sमाप_प्रकार (*copy_file_range)(काष्ठा file *, loff_t, काष्ठा file *,
			loff_t, माप_प्रकार, अचिन्हित पूर्णांक);
	loff_t (*remap_file_range)(काष्ठा file *file_in, loff_t pos_in,
				   काष्ठा file *file_out, loff_t pos_out,
				   loff_t len, अचिन्हित पूर्णांक remap_flags);
	पूर्णांक (*fadvise)(काष्ठा file *, loff_t, loff_t, पूर्णांक);
पूर्ण __अक्रमomize_layout;

काष्ठा inode_operations अणु
	काष्ठा dentry * (*lookup) (काष्ठा inode *,काष्ठा dentry *, अचिन्हित पूर्णांक);
	स्थिर अक्षर * (*get_link) (काष्ठा dentry *, काष्ठा inode *, काष्ठा delayed_call *);
	पूर्णांक (*permission) (काष्ठा user_namespace *, काष्ठा inode *, पूर्णांक);
	काष्ठा posix_acl * (*get_acl)(काष्ठा inode *, पूर्णांक);

	पूर्णांक (*पढ़ोlink) (काष्ठा dentry *, अक्षर __user *,पूर्णांक);

	पूर्णांक (*create) (काष्ठा user_namespace *, काष्ठा inode *,काष्ठा dentry *,
		       umode_t, bool);
	पूर्णांक (*link) (काष्ठा dentry *,काष्ठा inode *,काष्ठा dentry *);
	पूर्णांक (*unlink) (काष्ठा inode *,काष्ठा dentry *);
	पूर्णांक (*symlink) (काष्ठा user_namespace *, काष्ठा inode *,काष्ठा dentry *,
			स्थिर अक्षर *);
	पूर्णांक (*सूची_गढ़ो) (काष्ठा user_namespace *, काष्ठा inode *,काष्ठा dentry *,
		      umode_t);
	पूर्णांक (*सूची_हटाओ) (काष्ठा inode *,काष्ठा dentry *);
	पूर्णांक (*mknod) (काष्ठा user_namespace *, काष्ठा inode *,काष्ठा dentry *,
		      umode_t,dev_t);
	पूर्णांक (*नाम) (काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
			काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक);
	पूर्णांक (*setattr) (काष्ठा user_namespace *, काष्ठा dentry *,
			काष्ठा iattr *);
	पूर्णांक (*getattr) (काष्ठा user_namespace *, स्थिर काष्ठा path *,
			काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
	sमाप_प्रकार (*listxattr) (काष्ठा dentry *, अक्षर *, माप_प्रकार);
	पूर्णांक (*fiemap)(काष्ठा inode *, काष्ठा fiemap_extent_info *, u64 start,
		      u64 len);
	पूर्णांक (*update_समय)(काष्ठा inode *, काष्ठा बारpec64 *, पूर्णांक);
	पूर्णांक (*atomic_खोलो)(काष्ठा inode *, काष्ठा dentry *,
			   काष्ठा file *, अचिन्हित खोलो_flag,
			   umode_t create_mode);
	पूर्णांक (*क्षणिक_ख) (काष्ठा user_namespace *, काष्ठा inode *,
			काष्ठा dentry *, umode_t);
	पूर्णांक (*set_acl)(काष्ठा user_namespace *, काष्ठा inode *,
		       काष्ठा posix_acl *, पूर्णांक);
	पूर्णांक (*fileattr_set)(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry, काष्ठा fileattr *fa);
	पूर्णांक (*fileattr_get)(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्ण ____cacheline_aligned;

अटल अंतरभूत sमाप_प्रकार call_पढ़ो_iter(काष्ठा file *file, काष्ठा kiocb *kio,
				     काष्ठा iov_iter *iter)
अणु
	वापस file->f_op->पढ़ो_iter(kio, iter);
पूर्ण

अटल अंतरभूत sमाप_प्रकार call_ग_लिखो_iter(काष्ठा file *file, काष्ठा kiocb *kio,
				      काष्ठा iov_iter *iter)
अणु
	वापस file->f_op->ग_लिखो_iter(kio, iter);
पूर्ण

अटल अंतरभूत पूर्णांक call_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस file->f_op->mmap(file, vma);
पूर्ण

बाह्य sमाप_प्रकार vfs_पढ़ो(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
बाह्य sमाप_प्रकार vfs_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
बाह्य sमाप_प्रकार vfs_copy_file_range(काष्ठा file *, loff_t , काष्ठा file *,
				   loff_t, माप_प्रकार, अचिन्हित पूर्णांक);
बाह्य sमाप_प्रकार generic_copy_file_range(काष्ठा file *file_in, loff_t pos_in,
				       काष्ठा file *file_out, loff_t pos_out,
				       माप_प्रकार len, अचिन्हित पूर्णांक flags);
बाह्य पूर्णांक generic_remap_file_range_prep(काष्ठा file *file_in, loff_t pos_in,
					 काष्ठा file *file_out, loff_t pos_out,
					 loff_t *count,
					 अचिन्हित पूर्णांक remap_flags);
बाह्य loff_t करो_clone_file_range(काष्ठा file *file_in, loff_t pos_in,
				  काष्ठा file *file_out, loff_t pos_out,
				  loff_t len, अचिन्हित पूर्णांक remap_flags);
बाह्य loff_t vfs_clone_file_range(काष्ठा file *file_in, loff_t pos_in,
				   काष्ठा file *file_out, loff_t pos_out,
				   loff_t len, अचिन्हित पूर्णांक remap_flags);
बाह्य पूर्णांक vfs_dedupe_file_range(काष्ठा file *file,
				 काष्ठा file_dedupe_range *same);
बाह्य loff_t vfs_dedupe_file_range_one(काष्ठा file *src_file, loff_t src_pos,
					काष्ठा file *dst_file, loff_t dst_pos,
					loff_t len, अचिन्हित पूर्णांक remap_flags);


काष्ठा super_operations अणु
   	काष्ठा inode *(*alloc_inode)(काष्ठा super_block *sb);
	व्योम (*destroy_inode)(काष्ठा inode *);
	व्योम (*मुक्त_inode)(काष्ठा inode *);

   	व्योम (*dirty_inode) (काष्ठा inode *, पूर्णांक flags);
	पूर्णांक (*ग_लिखो_inode) (काष्ठा inode *, काष्ठा ग_लिखोback_control *wbc);
	पूर्णांक (*drop_inode) (काष्ठा inode *);
	व्योम (*evict_inode) (काष्ठा inode *);
	व्योम (*put_super) (काष्ठा super_block *);
	पूर्णांक (*sync_fs)(काष्ठा super_block *sb, पूर्णांक रुको);
	पूर्णांक (*मुक्तze_super) (काष्ठा super_block *);
	पूर्णांक (*मुक्तze_fs) (काष्ठा super_block *);
	पूर्णांक (*thaw_super) (काष्ठा super_block *);
	पूर्णांक (*unमुक्तze_fs) (काष्ठा super_block *);
	पूर्णांक (*statfs) (काष्ठा dentry *, काष्ठा kstatfs *);
	पूर्णांक (*remount_fs) (काष्ठा super_block *, पूर्णांक *, अक्षर *);
	व्योम (*umount_begin) (काष्ठा super_block *);

	पूर्णांक (*show_options)(काष्ठा seq_file *, काष्ठा dentry *);
	पूर्णांक (*show_devname)(काष्ठा seq_file *, काष्ठा dentry *);
	पूर्णांक (*show_path)(काष्ठा seq_file *, काष्ठा dentry *);
	पूर्णांक (*show_stats)(काष्ठा seq_file *, काष्ठा dentry *);
#अगर_घोषित CONFIG_QUOTA
	sमाप_प्रकार (*quota_पढ़ो)(काष्ठा super_block *, पूर्णांक, अक्षर *, माप_प्रकार, loff_t);
	sमाप_प्रकार (*quota_ग_लिखो)(काष्ठा super_block *, पूर्णांक, स्थिर अक्षर *, माप_प्रकार, loff_t);
	काष्ठा dquot **(*get_dquots)(काष्ठा inode *);
#पूर्ण_अगर
	पूर्णांक (*bdev_try_to_मुक्त_page)(काष्ठा super_block*, काष्ठा page*, gfp_t);
	दीर्घ (*nr_cached_objects)(काष्ठा super_block *,
				  काष्ठा shrink_control *);
	दीर्घ (*मुक्त_cached_objects)(काष्ठा super_block *,
				    काष्ठा shrink_control *);
पूर्ण;

/*
 * Inode flags - they have no relation to superblock flags now
 */
#घोषणा S_SYNC		(1 << 0)  /* Writes are synced at once */
#घोषणा S_NOATIME	(1 << 1)  /* Do not update access बार */
#घोषणा S_APPEND	(1 << 2)  /* Append-only file */
#घोषणा S_IMMUTABLE	(1 << 3)  /* Immutable file */
#घोषणा S_DEAD		(1 << 4)  /* हटाओd, but still खोलो directory */
#घोषणा S_NOQUOTA	(1 << 5)  /* Inode is not counted to quota */
#घोषणा S_सूचीSYNC	(1 << 6)  /* Directory modअगरications are synchronous */
#घोषणा S_NOCMTIME	(1 << 7)  /* Do not update file c/mसमय */
#घोषणा S_SWAPखाता	(1 << 8)  /* Do not truncate: swapon got its bmaps */
#घोषणा S_PRIVATE	(1 << 9)  /* Inode is fs-पूर्णांकernal */
#घोषणा S_IMA		(1 << 10) /* Inode has an associated IMA काष्ठा */
#घोषणा S_AUTOMOUNT	(1 << 11) /* Automount/referral quasi-directory */
#घोषणा S_NOSEC		(1 << 12) /* no suid or xattr security attributes */
#अगर_घोषित CONFIG_FS_DAX
#घोषणा S_DAX		(1 << 13) /* Direct Access, aव्योमing the page cache */
#अन्यथा
#घोषणा S_DAX		0	  /* Make all the DAX code disappear */
#पूर्ण_अगर
#घोषणा S_ENCRYPTED	(1 << 14) /* Encrypted file (using fs/crypto/) */
#घोषणा S_CASEFOLD	(1 << 15) /* Casefolded file */
#घोषणा S_VERITY	(1 << 16) /* Verity file (using fs/verity/) */

/*
 * Note that nosuid etc flags are inode-specअगरic: setting some file-प्रणाली
 * flags just means all the inodes inherit those flags by शेष. It might be
 * possible to override it selectively अगर you really wanted to with some
 * ioctl() that is not currently implemented.
 *
 * Exception: SB_RDONLY is always applied to the entire file प्रणाली.
 *
 * Unक्रमtunately, it is possible to change a fileप्रणालीs flags with it mounted
 * with files in use.  This means that all of the inodes will not have their
 * i_flags updated.  Hence, i_flags no दीर्घer inherit the superblock mount
 * flags, so these have to be checked separately. -- rmk@arm.uk.linux.org
 */
#घोषणा __IS_FLG(inode, flg)	((inode)->i_sb->s_flags & (flg))

अटल अंतरभूत bool sb_rकरोnly(स्थिर काष्ठा super_block *sb) अणु वापस sb->s_flags & SB_RDONLY; पूर्ण
#घोषणा IS_RDONLY(inode)	sb_rकरोnly((inode)->i_sb)
#घोषणा IS_SYNC(inode)		(__IS_FLG(inode, SB_SYNCHRONOUS) || \
					((inode)->i_flags & S_SYNC))
#घोषणा IS_सूचीSYNC(inode)	(__IS_FLG(inode, SB_SYNCHRONOUS|SB_सूचीSYNC) || \
					((inode)->i_flags & (S_SYNC|S_सूचीSYNC)))
#घोषणा IS_MANDLOCK(inode)	__IS_FLG(inode, SB_MANDLOCK)
#घोषणा IS_NOATIME(inode)	__IS_FLG(inode, SB_RDONLY|SB_NOATIME)
#घोषणा IS_I_VERSION(inode)	__IS_FLG(inode, SB_I_VERSION)

#घोषणा IS_NOQUOTA(inode)	((inode)->i_flags & S_NOQUOTA)
#घोषणा IS_APPEND(inode)	((inode)->i_flags & S_APPEND)
#घोषणा IS_IMMUTABLE(inode)	((inode)->i_flags & S_IMMUTABLE)
#घोषणा IS_POSIXACL(inode)	__IS_FLG(inode, SB_POSIXACL)

#घोषणा IS_DEADसूची(inode)	((inode)->i_flags & S_DEAD)
#घोषणा IS_NOCMTIME(inode)	((inode)->i_flags & S_NOCMTIME)
#घोषणा IS_SWAPखाता(inode)	((inode)->i_flags & S_SWAPखाता)
#घोषणा IS_PRIVATE(inode)	((inode)->i_flags & S_PRIVATE)
#घोषणा IS_IMA(inode)		((inode)->i_flags & S_IMA)
#घोषणा IS_AUTOMOUNT(inode)	((inode)->i_flags & S_AUTOMOUNT)
#घोषणा IS_NOSEC(inode)		((inode)->i_flags & S_NOSEC)
#घोषणा IS_DAX(inode)		((inode)->i_flags & S_DAX)
#घोषणा IS_ENCRYPTED(inode)	((inode)->i_flags & S_ENCRYPTED)
#घोषणा IS_CASEFOLDED(inode)	((inode)->i_flags & S_CASEFOLD)
#घोषणा IS_VERITY(inode)	((inode)->i_flags & S_VERITY)

#घोषणा IS_WHITEOUT(inode)	(S_ISCHR(inode->i_mode) && \
				 (inode)->i_rdev == WHITEOUT_DEV)

अटल अंतरभूत bool HAS_UNMAPPED_ID(काष्ठा user_namespace *mnt_userns,
				   काष्ठा inode *inode)
अणु
	वापस !uid_valid(i_uid_पूर्णांकo_mnt(mnt_userns, inode)) ||
	       !gid_valid(i_gid_पूर्णांकo_mnt(mnt_userns, inode));
पूर्ण

अटल अंतरभूत क्रमागत rw_hपूर्णांक file_ग_लिखो_hपूर्णांक(काष्ठा file *file)
अणु
	अगर (file->f_ग_लिखो_hपूर्णांक != WRITE_LIFE_NOT_SET)
		वापस file->f_ग_लिखो_hपूर्णांक;

	वापस file_inode(file)->i_ग_लिखो_hपूर्णांक;
पूर्ण

अटल अंतरभूत पूर्णांक iocb_flags(काष्ठा file *file);

अटल अंतरभूत u16 ki_hपूर्णांक_validate(क्रमागत rw_hपूर्णांक hपूर्णांक)
अणु
	typeof(((काष्ठा kiocb *)0)->ki_hपूर्णांक) max_hपूर्णांक = -1;

	अगर (hपूर्णांक <= max_hपूर्णांक)
		वापस hपूर्णांक;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम init_sync_kiocb(काष्ठा kiocb *kiocb, काष्ठा file *filp)
अणु
	*kiocb = (काष्ठा kiocb) अणु
		.ki_filp = filp,
		.ki_flags = iocb_flags(filp),
		.ki_hपूर्णांक = ki_hपूर्णांक_validate(file_ग_लिखो_hपूर्णांक(filp)),
		.ki_ioprio = get_current_ioprio(),
	पूर्ण;
पूर्ण

अटल अंतरभूत व्योम kiocb_clone(काष्ठा kiocb *kiocb, काष्ठा kiocb *kiocb_src,
			       काष्ठा file *filp)
अणु
	*kiocb = (काष्ठा kiocb) अणु
		.ki_filp = filp,
		.ki_flags = kiocb_src->ki_flags,
		.ki_hपूर्णांक = kiocb_src->ki_hपूर्णांक,
		.ki_ioprio = kiocb_src->ki_ioprio,
		.ki_pos = kiocb_src->ki_pos,
	पूर्ण;
पूर्ण

/*
 * Inode state bits.  Protected by inode->i_lock
 *
 * Four bits determine the dirty state of the inode: I_सूचीTY_SYNC,
 * I_सूचीTY_DATASYNC, I_सूचीTY_PAGES, and I_सूचीTY_TIME.
 *
 * Four bits define the lअगरeसमय of an inode.  Initially, inodes are I_NEW,
 * until that flag is cleared.  I_WILL_FREE, I_FREEING and I_CLEAR are set at
 * various stages of removing an inode.
 *
 * Two bits are used क्रम locking and completion notअगरication, I_NEW and I_SYNC.
 *
 * I_सूचीTY_SYNC		Inode is dirty, but करोesn't have to be written on
 *			fdatasync() (unless I_सूचीTY_DATASYNC is also set).
 *			Timestamp updates are the usual cause.
 * I_सूचीTY_DATASYNC	Data-related inode changes pending.  We keep track of
 *			these changes separately from I_सूचीTY_SYNC so that we
 *			करोn't have to ग_लिखो inode on fdatasync() when only
 *			e.g. the बारtamps have changed.
 * I_सूचीTY_PAGES	Inode has dirty pages.  Inode itself may be clean.
 * I_सूचीTY_TIME		The inode itself only has dirty बारtamps, and the
 *			lazyसमय mount option is enabled.  We keep track of this
 *			separately from I_सूचीTY_SYNC in order to implement
 *			lazyसमय.  This माला_लो cleared अगर I_सूचीTY_INODE
 *			(I_सूचीTY_SYNC and/or I_सूचीTY_DATASYNC) माला_लो set.  I.e.
 *			either I_सूचीTY_TIME *or* I_सूचीTY_INODE can be set in
 *			i_state, but not both.  I_सूचीTY_PAGES may still be set.
 * I_NEW		Serves as both a mutex and completion notअगरication.
 *			New inodes set I_NEW.  If two processes both create
 *			the same inode, one of them will release its inode and
 *			रुको क्रम I_NEW to be released beक्रमe वापसing.
 *			Inodes in I_WILL_FREE, I_FREEING or I_CLEAR state can
 *			also cause रुकोing on I_NEW, without I_NEW actually
 *			being set.  find_inode() uses this to prevent वापसing
 *			nearly-dead inodes.
 * I_WILL_FREE		Must be set when calling ग_लिखो_inode_now() अगर i_count
 *			is zero.  I_FREEING must be set when I_WILL_FREE is
 *			cleared.
 * I_FREEING		Set when inode is about to be मुक्तd but still has dirty
 *			pages or buffers attached or the inode itself is still
 *			dirty.
 * I_CLEAR		Added by clear_inode().  In this state the inode is
 *			clean and can be destroyed.  Inode keeps I_FREEING.
 *
 *			Inodes that are I_WILL_FREE, I_FREEING or I_CLEAR are
 *			prohibited क्रम many purposes.  iget() must रुको क्रम
 *			the inode to be completely released, then create it
 *			anew.  Other functions will just ignore such inodes,
 *			अगर appropriate.  I_NEW is used क्रम रुकोing.
 *
 * I_SYNC		Writeback of inode is running. The bit is set during
 *			data ग_लिखोback, and cleared with a wakeup on the bit
 *			address once it is करोne. The bit is also used to pin
 *			the inode in memory क्रम flusher thपढ़ो.
 *
 * I_REFERENCED		Marks the inode as recently references on the LRU list.
 *
 * I_DIO_WAKEUP		Never set.  Only used as a key क्रम रुको_on_bit().
 *
 * I_WB_SWITCH		Cgroup bdi_ग_लिखोback चयनing in progress.  Used to
 *			synchronize competing चयनing instances and to tell
 *			wb stat updates to grab the i_pages lock.  See
 *			inode_चयन_wbs_work_fn() क्रम details.
 *
 * I_OVL_INUSE		Used by overlayfs to get exclusive ownership on upper
 *			and work dirs among overlayfs mounts.
 *
 * I_CREATING		New object's inode in the middle of setting up.
 *
 * I_DONTCACHE		Evict inode as soon as it is not used anymore.
 *
 * I_SYNC_QUEUED	Inode is queued in b_io or b_more_io ग_लिखोback lists.
 *			Used to detect that mark_inode_dirty() should not move
 * 			inode between dirty lists.
 *
 * Q: What is the dअगरference between I_WILL_FREE and I_FREEING?
 */
#घोषणा I_सूचीTY_SYNC		(1 << 0)
#घोषणा I_सूचीTY_DATASYNC	(1 << 1)
#घोषणा I_सूचीTY_PAGES		(1 << 2)
#घोषणा __I_NEW			3
#घोषणा I_NEW			(1 << __I_NEW)
#घोषणा I_WILL_FREE		(1 << 4)
#घोषणा I_FREEING		(1 << 5)
#घोषणा I_CLEAR			(1 << 6)
#घोषणा __I_SYNC		7
#घोषणा I_SYNC			(1 << __I_SYNC)
#घोषणा I_REFERENCED		(1 << 8)
#घोषणा __I_DIO_WAKEUP		9
#घोषणा I_DIO_WAKEUP		(1 << __I_DIO_WAKEUP)
#घोषणा I_LINKABLE		(1 << 10)
#घोषणा I_सूचीTY_TIME		(1 << 11)
#घोषणा I_WB_SWITCH		(1 << 13)
#घोषणा I_OVL_INUSE		(1 << 14)
#घोषणा I_CREATING		(1 << 15)
#घोषणा I_DONTCACHE		(1 << 16)
#घोषणा I_SYNC_QUEUED		(1 << 17)

#घोषणा I_सूचीTY_INODE (I_सूचीTY_SYNC | I_सूचीTY_DATASYNC)
#घोषणा I_सूचीTY (I_सूचीTY_INODE | I_सूचीTY_PAGES)
#घोषणा I_सूचीTY_ALL (I_सूचीTY | I_सूचीTY_TIME)

बाह्य व्योम __mark_inode_dirty(काष्ठा inode *, पूर्णांक);
अटल अंतरभूत व्योम mark_inode_dirty(काष्ठा inode *inode)
अणु
	__mark_inode_dirty(inode, I_सूचीTY);
पूर्ण

अटल अंतरभूत व्योम mark_inode_dirty_sync(काष्ठा inode *inode)
अणु
	__mark_inode_dirty(inode, I_सूचीTY_SYNC);
पूर्ण

/*
 * Returns true अगर the given inode itself only has dirty बारtamps (its pages
 * may still be dirty) and isn't currently being allocated or मुक्तd.
 * Fileप्रणालीs should call this अगर when writing an inode when lazyसमय is
 * enabled, they want to opportunistically ग_लिखो the बारtamps of other inodes
 * located very nearby on-disk, e.g. in the same inode block.  This वापसs true
 * अगर the given inode is in need of such an opportunistic update.  Requires
 * i_lock, or at least later re-checking under i_lock.
 */
अटल अंतरभूत bool inode_is_dirtyसमय_only(काष्ठा inode *inode)
अणु
	वापस (inode->i_state & (I_सूचीTY_TIME | I_NEW |
				  I_FREEING | I_WILL_FREE)) == I_सूचीTY_TIME;
पूर्ण

बाह्य व्योम inc_nlink(काष्ठा inode *inode);
बाह्य व्योम drop_nlink(काष्ठा inode *inode);
बाह्य व्योम clear_nlink(काष्ठा inode *inode);
बाह्य व्योम set_nlink(काष्ठा inode *inode, अचिन्हित पूर्णांक nlink);

अटल अंतरभूत व्योम inode_inc_link_count(काष्ठा inode *inode)
अणु
	inc_nlink(inode);
	mark_inode_dirty(inode);
पूर्ण

अटल अंतरभूत व्योम inode_dec_link_count(काष्ठा inode *inode)
अणु
	drop_nlink(inode);
	mark_inode_dirty(inode);
पूर्ण

क्रमागत file_समय_flags अणु
	S_ATIME = 1,
	S_MTIME = 2,
	S_CTIME = 4,
	S_VERSION = 8,
पूर्ण;

बाह्य bool aसमय_needs_update(स्थिर काष्ठा path *, काष्ठा inode *);
बाह्य व्योम touch_aसमय(स्थिर काष्ठा path *);
अटल अंतरभूत व्योम file_accessed(काष्ठा file *file)
अणु
	अगर (!(file->f_flags & O_NOATIME))
		touch_aसमय(&file->f_path);
पूर्ण

बाह्य पूर्णांक file_modअगरied(काष्ठा file *file);

पूर्णांक sync_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);
पूर्णांक sync_inode_metadata(काष्ठा inode *inode, पूर्णांक रुको);

काष्ठा file_प्रणाली_type अणु
	स्थिर अक्षर *name;
	पूर्णांक fs_flags;
#घोषणा FS_REQUIRES_DEV		1 
#घोषणा FS_BINARY_MOUNTDATA	2
#घोषणा FS_HAS_SUBTYPE		4
#घोषणा FS_USERNS_MOUNT		8	/* Can be mounted by userns root */
#घोषणा FS_DISALLOW_NOTIFY_PERM	16	/* Disable fanotअगरy permission events */
#घोषणा FS_ALLOW_IDMAP         32      /* FS has been updated to handle vfs idmappings. */
#घोषणा FS_THP_SUPPORT		8192	/* Remove once all fs converted */
#घोषणा FS_RENAME_DOES_D_MOVE	32768	/* FS will handle d_move() during नाम() पूर्णांकernally. */
	पूर्णांक (*init_fs_context)(काष्ठा fs_context *);
	स्थिर काष्ठा fs_parameter_spec *parameters;
	काष्ठा dentry *(*mount) (काष्ठा file_प्रणाली_type *, पूर्णांक,
		       स्थिर अक्षर *, व्योम *);
	व्योम (*समाप्त_sb) (काष्ठा super_block *);
	काष्ठा module *owner;
	काष्ठा file_प्रणाली_type * next;
	काष्ठा hlist_head fs_supers;

	काष्ठा lock_class_key s_lock_key;
	काष्ठा lock_class_key s_umount_key;
	काष्ठा lock_class_key s_vfs_नाम_key;
	काष्ठा lock_class_key s_ग_लिखोrs_key[SB_FREEZE_LEVELS];

	काष्ठा lock_class_key i_lock_key;
	काष्ठा lock_class_key i_mutex_key;
	काष्ठा lock_class_key i_mutex_dir_key;
पूर्ण;

#घोषणा MODULE_ALIAS_FS(NAME) MODULE_ALIAS("fs-" NAME)

बाह्य काष्ठा dentry *mount_bdev(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data,
	पूर्णांक (*fill_super)(काष्ठा super_block *, व्योम *, पूर्णांक));
बाह्य काष्ठा dentry *mount_single(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, व्योम *data,
	पूर्णांक (*fill_super)(काष्ठा super_block *, व्योम *, पूर्णांक));
बाह्य काष्ठा dentry *mount_nodev(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, व्योम *data,
	पूर्णांक (*fill_super)(काष्ठा super_block *, व्योम *, पूर्णांक));
बाह्य काष्ठा dentry *mount_subtree(काष्ठा vfsmount *mnt, स्थिर अक्षर *path);
व्योम generic_shutकरोwn_super(काष्ठा super_block *sb);
व्योम समाप्त_block_super(काष्ठा super_block *sb);
व्योम समाप्त_anon_super(काष्ठा super_block *sb);
व्योम समाप्त_litter_super(काष्ठा super_block *sb);
व्योम deactivate_super(काष्ठा super_block *sb);
व्योम deactivate_locked_super(काष्ठा super_block *sb);
पूर्णांक set_anon_super(काष्ठा super_block *s, व्योम *data);
पूर्णांक set_anon_super_fc(काष्ठा super_block *s, काष्ठा fs_context *fc);
पूर्णांक get_anon_bdev(dev_t *);
व्योम मुक्त_anon_bdev(dev_t);
काष्ठा super_block *sget_fc(काष्ठा fs_context *fc,
			    पूर्णांक (*test)(काष्ठा super_block *, काष्ठा fs_context *),
			    पूर्णांक (*set)(काष्ठा super_block *, काष्ठा fs_context *));
काष्ठा super_block *sget(काष्ठा file_प्रणाली_type *type,
			पूर्णांक (*test)(काष्ठा super_block *,व्योम *),
			पूर्णांक (*set)(काष्ठा super_block *,व्योम *),
			पूर्णांक flags, व्योम *data);

/* Alas, no aliases. Too much hassle with bringing module.h everywhere */
#घोषणा fops_get(fops) \
	(((fops) && try_module_get((fops)->owner) ? (fops) : शून्य))
#घोषणा fops_put(fops) \
	करो अणु अगर (fops) module_put((fops)->owner); पूर्ण जबतक(0)
/*
 * This one is to be used *ONLY* from ->खोलो() instances.
 * fops must be non-शून्य, pinned करोwn *and* module dependencies
 * should be sufficient to pin the caller करोwn as well.
 */
#घोषणा replace_fops(f, fops) \
	करो अणु	\
		काष्ठा file *__file = (f); \
		fops_put(__file->f_op); \
		BUG_ON(!(__file->f_op = (fops))); \
	पूर्ण जबतक(0)

बाह्य पूर्णांक रेजिस्टर_fileप्रणाली(काष्ठा file_प्रणाली_type *);
बाह्य पूर्णांक unरेजिस्टर_fileप्रणाली(काष्ठा file_प्रणाली_type *);
बाह्य काष्ठा vfsmount *kern_mount(काष्ठा file_प्रणाली_type *);
बाह्य व्योम kern_unmount(काष्ठा vfsmount *mnt);
बाह्य पूर्णांक may_umount_tree(काष्ठा vfsmount *);
बाह्य पूर्णांक may_umount(काष्ठा vfsmount *);
बाह्य दीर्घ करो_mount(स्थिर अक्षर *, स्थिर अक्षर __user *,
		     स्थिर अक्षर *, अचिन्हित दीर्घ, व्योम *);
बाह्य काष्ठा vfsmount *collect_mounts(स्थिर काष्ठा path *);
बाह्य व्योम drop_collected_mounts(काष्ठा vfsmount *);
बाह्य पूर्णांक iterate_mounts(पूर्णांक (*)(काष्ठा vfsmount *, व्योम *), व्योम *,
			  काष्ठा vfsmount *);
बाह्य पूर्णांक vfs_statfs(स्थिर काष्ठा path *, काष्ठा kstatfs *);
बाह्य पूर्णांक user_statfs(स्थिर अक्षर __user *, काष्ठा kstatfs *);
बाह्य पूर्णांक fd_statfs(पूर्णांक, काष्ठा kstatfs *);
बाह्य पूर्णांक मुक्तze_super(काष्ठा super_block *super);
बाह्य पूर्णांक thaw_super(काष्ठा super_block *super);
बाह्य bool our_mnt(काष्ठा vfsmount *mnt);
बाह्य __म_लिखो(2, 3)
पूर्णांक super_setup_bdi_name(काष्ठा super_block *sb, अक्षर *fmt, ...);
बाह्य पूर्णांक super_setup_bdi(काष्ठा super_block *sb);

बाह्य पूर्णांक current_umask(व्योम);

बाह्य व्योम ihold(काष्ठा inode * inode);
बाह्य व्योम iput(काष्ठा inode *);
बाह्य पूर्णांक generic_update_समय(काष्ठा inode *, काष्ठा बारpec64 *, पूर्णांक);

/* /sys/fs */
बाह्य काष्ठा kobject *fs_kobj;

#घोषणा MAX_RW_COUNT (पूर्णांक_उच्च & PAGE_MASK)

#अगर_घोषित CONFIG_MANDATORY_खाता_LOCKING
बाह्य पूर्णांक locks_mandatory_locked(काष्ठा file *);
बाह्य पूर्णांक locks_mandatory_area(काष्ठा inode *, काष्ठा file *, loff_t, loff_t, अचिन्हित अक्षर);

/*
 * Candidates क्रम mandatory locking have the setgid bit set
 * but no group execute bit -  an otherwise meaningless combination.
 */

अटल अंतरभूत पूर्णांक __mandatory_lock(काष्ठा inode *ino)
अणु
	वापस (ino->i_mode & (S_ISGID | S_IXGRP)) == S_ISGID;
पूर्ण

/*
 * ... and these candidates should be on SB_MANDLOCK mounted fs,
 * otherwise these will be advisory locks
 */

अटल अंतरभूत पूर्णांक mandatory_lock(काष्ठा inode *ino)
अणु
	वापस IS_MANDLOCK(ino) && __mandatory_lock(ino);
पूर्ण

अटल अंतरभूत पूर्णांक locks_verअगरy_locked(काष्ठा file *file)
अणु
	अगर (mandatory_lock(locks_inode(file)))
		वापस locks_mandatory_locked(file);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक locks_verअगरy_truncate(काष्ठा inode *inode,
				    काष्ठा file *f,
				    loff_t size)
अणु
	अगर (!inode->i_flctx || !mandatory_lock(inode))
		वापस 0;

	अगर (size < inode->i_size) अणु
		वापस locks_mandatory_area(inode, f, size, inode->i_size - 1,
				F_WRLCK);
	पूर्ण अन्यथा अणु
		वापस locks_mandatory_area(inode, f, inode->i_size, size - 1,
				F_WRLCK);
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_MANDATORY_खाता_LOCKING */

अटल अंतरभूत पूर्णांक locks_mandatory_locked(काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक locks_mandatory_area(काष्ठा inode *inode, काष्ठा file *filp,
                                       loff_t start, loff_t end, अचिन्हित अक्षर type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __mandatory_lock(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mandatory_lock(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक locks_verअगरy_locked(काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक locks_verअगरy_truncate(काष्ठा inode *inode, काष्ठा file *filp,
					माप_प्रकार size)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_MANDATORY_खाता_LOCKING */


#अगर_घोषित CONFIG_खाता_LOCKING
अटल अंतरभूत पूर्णांक अवरोध_lease(काष्ठा inode *inode, अचिन्हित पूर्णांक mode)
अणु
	/*
	 * Since this check is lockless, we must ensure that any refcounts
	 * taken are करोne beक्रमe checking i_flctx->flc_lease. Otherwise, we
	 * could end up racing with tasks trying to set a new lease on this
	 * file.
	 */
	smp_mb();
	अगर (inode->i_flctx && !list_empty_careful(&inode->i_flctx->flc_lease))
		वापस __अवरोध_lease(inode, mode, FL_LEASE);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक अवरोध_deleg(काष्ठा inode *inode, अचिन्हित पूर्णांक mode)
अणु
	/*
	 * Since this check is lockless, we must ensure that any refcounts
	 * taken are करोne beक्रमe checking i_flctx->flc_lease. Otherwise, we
	 * could end up racing with tasks trying to set a new lease on this
	 * file.
	 */
	smp_mb();
	अगर (inode->i_flctx && !list_empty_careful(&inode->i_flctx->flc_lease))
		वापस __अवरोध_lease(inode, mode, FL_DELEG);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक try_अवरोध_deleg(काष्ठा inode *inode, काष्ठा inode **delegated_inode)
अणु
	पूर्णांक ret;

	ret = अवरोध_deleg(inode, O_WRONLY|O_NONBLOCK);
	अगर (ret == -EWOULDBLOCK && delegated_inode) अणु
		*delegated_inode = inode;
		ihold(inode);
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक अवरोध_deleg_रुको(काष्ठा inode **delegated_inode)
अणु
	पूर्णांक ret;

	ret = अवरोध_deleg(*delegated_inode, O_WRONLY);
	iput(*delegated_inode);
	*delegated_inode = शून्य;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक अवरोध_layout(काष्ठा inode *inode, bool रुको)
अणु
	smp_mb();
	अगर (inode->i_flctx && !list_empty_careful(&inode->i_flctx->flc_lease))
		वापस __अवरोध_lease(inode,
				रुको ? O_WRONLY : O_WRONLY | O_NONBLOCK,
				FL_LAYOUT);
	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_खाता_LOCKING */
अटल अंतरभूत पूर्णांक अवरोध_lease(काष्ठा inode *inode, अचिन्हित पूर्णांक mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक अवरोध_deleg(काष्ठा inode *inode, अचिन्हित पूर्णांक mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक try_अवरोध_deleg(काष्ठा inode *inode, काष्ठा inode **delegated_inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक अवरोध_deleg_रुको(काष्ठा inode **delegated_inode)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक अवरोध_layout(काष्ठा inode *inode, bool रुको)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_खाता_LOCKING */

/* fs/खोलो.c */
काष्ठा audit_names;
काष्ठा filename अणु
	स्थिर अक्षर		*name;	/* poपूर्णांकer to actual string */
	स्थिर __user अक्षर	*uptr;	/* original userland poपूर्णांकer */
	पूर्णांक			refcnt;
	काष्ठा audit_names	*aname;
	स्थिर अक्षर		iname[];
पूर्ण;
अटल_निश्चित(दुरत्व(काष्ठा filename, iname) % माप(दीर्घ) == 0);

अटल अंतरभूत काष्ठा user_namespace *file_mnt_user_ns(काष्ठा file *file)
अणु
	वापस mnt_user_ns(file->f_path.mnt);
पूर्ण
बाह्य दीर्घ vfs_truncate(स्थिर काष्ठा path *, loff_t);
पूर्णांक करो_truncate(काष्ठा user_namespace *, काष्ठा dentry *, loff_t start,
		अचिन्हित पूर्णांक समय_attrs, काष्ठा file *filp);
बाह्य पूर्णांक vfs_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset,
			loff_t len);
बाह्य दीर्घ करो_sys_खोलो(पूर्णांक dfd, स्थिर अक्षर __user *filename, पूर्णांक flags,
			umode_t mode);
बाह्य काष्ठा file *file_खोलो_name(काष्ठा filename *, पूर्णांक, umode_t);
बाह्य काष्ठा file *filp_खोलो(स्थिर अक्षर *, पूर्णांक, umode_t);
बाह्य काष्ठा file *file_खोलो_root(काष्ठा dentry *, काष्ठा vfsmount *,
				   स्थिर अक्षर *, पूर्णांक, umode_t);
बाह्य काष्ठा file * dentry_खोलो(स्थिर काष्ठा path *, पूर्णांक, स्थिर काष्ठा cred *);
बाह्य काष्ठा file * खोलो_with_fake_path(स्थिर काष्ठा path *, पूर्णांक,
					 काष्ठा inode*, स्थिर काष्ठा cred *);
अटल अंतरभूत काष्ठा file *file_clone_खोलो(काष्ठा file *file)
अणु
	वापस dentry_खोलो(&file->f_path, file->f_flags, file->f_cred);
पूर्ण
बाह्य पूर्णांक filp_बंद(काष्ठा file *, fl_owner_t id);

बाह्य काष्ठा filename *getname_flags(स्थिर अक्षर __user *, पूर्णांक, पूर्णांक *);
बाह्य काष्ठा filename *getname(स्थिर अक्षर __user *);
बाह्य काष्ठा filename *getname_kernel(स्थिर अक्षर *);
बाह्य व्योम putname(काष्ठा filename *name);

बाह्य पूर्णांक finish_खोलो(काष्ठा file *file, काष्ठा dentry *dentry,
			पूर्णांक (*खोलो)(काष्ठा inode *, काष्ठा file *));
बाह्य पूर्णांक finish_no_खोलो(काष्ठा file *file, काष्ठा dentry *dentry);

/* fs/dcache.c */
बाह्य व्योम __init vfs_caches_init_early(व्योम);
बाह्य व्योम __init vfs_caches_init(व्योम);

बाह्य काष्ठा kmem_cache *names_cachep;

#घोषणा __getname()		kmem_cache_alloc(names_cachep, GFP_KERNEL)
#घोषणा __putname(name)		kmem_cache_मुक्त(names_cachep, (व्योम *)(name))

बाह्य काष्ठा super_block *blockdev_superblock;
अटल अंतरभूत bool sb_is_blkdev_sb(काष्ठा super_block *sb)
अणु
	वापस IS_ENABLED(CONFIG_BLOCK) && sb == blockdev_superblock;
पूर्ण

व्योम emergency_thaw_all(व्योम);
बाह्य पूर्णांक sync_fileप्रणाली(काष्ठा super_block *);
बाह्य स्थिर काष्ठा file_operations def_blk_fops;
बाह्य स्थिर काष्ठा file_operations def_chr_fops;

/* fs/अक्षर_dev.c */
#घोषणा CHRDEV_MAJOR_MAX 512
/* Marks the bottom of the first segment of मुक्त अक्षर majors */
#घोषणा CHRDEV_MAJOR_DYN_END 234
/* Marks the top and bottom of the second segment of मुक्त अक्षर majors */
#घोषणा CHRDEV_MAJOR_DYN_EXT_START 511
#घोषणा CHRDEV_MAJOR_DYN_EXT_END 384

बाह्य पूर्णांक alloc_chrdev_region(dev_t *, अचिन्हित, अचिन्हित, स्थिर अक्षर *);
बाह्य पूर्णांक रेजिस्टर_chrdev_region(dev_t, अचिन्हित, स्थिर अक्षर *);
बाह्य पूर्णांक __रेजिस्टर_chrdev(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक baseminor,
			     अचिन्हित पूर्णांक count, स्थिर अक्षर *name,
			     स्थिर काष्ठा file_operations *fops);
बाह्य व्योम __unरेजिस्टर_chrdev(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक baseminor,
				अचिन्हित पूर्णांक count, स्थिर अक्षर *name);
बाह्य व्योम unरेजिस्टर_chrdev_region(dev_t, अचिन्हित);
बाह्य व्योम chrdev_show(काष्ठा seq_file *,off_t);

अटल अंतरभूत पूर्णांक रेजिस्टर_chrdev(अचिन्हित पूर्णांक major, स्थिर अक्षर *name,
				  स्थिर काष्ठा file_operations *fops)
अणु
	वापस __रेजिस्टर_chrdev(major, 0, 256, name, fops);
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_chrdev(अचिन्हित पूर्णांक major, स्थिर अक्षर *name)
अणु
	__unरेजिस्टर_chrdev(major, 0, 256, name);
पूर्ण

बाह्य व्योम init_special_inode(काष्ठा inode *, umode_t, dev_t);

/* Invalid inode operations -- fs/bad_inode.c */
बाह्य व्योम make_bad_inode(काष्ठा inode *);
बाह्य bool is_bad_inode(काष्ठा inode *);

अचिन्हित दीर्घ invalidate_mapping_pages(काष्ठा address_space *mapping,
					pgoff_t start, pgoff_t end);

व्योम invalidate_mapping_pagevec(काष्ठा address_space *mapping,
				pgoff_t start, pgoff_t end,
				अचिन्हित दीर्घ *nr_pagevec);

अटल अंतरभूत व्योम invalidate_remote_inode(काष्ठा inode *inode)
अणु
	अगर (S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
	    S_ISLNK(inode->i_mode))
		invalidate_mapping_pages(inode->i_mapping, 0, -1);
पूर्ण
बाह्य पूर्णांक invalidate_inode_pages2(काष्ठा address_space *mapping);
बाह्य पूर्णांक invalidate_inode_pages2_range(काष्ठा address_space *mapping,
					 pgoff_t start, pgoff_t end);
बाह्य पूर्णांक ग_लिखो_inode_now(काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक filemap_fdataग_लिखो(काष्ठा address_space *);
बाह्य पूर्णांक filemap_flush(काष्ठा address_space *);
बाह्य पूर्णांक filemap_fdataरुको_keep_errors(काष्ठा address_space *mapping);
बाह्य पूर्णांक filemap_fdataरुको_range(काष्ठा address_space *, loff_t lstart,
				   loff_t lend);
बाह्य पूर्णांक filemap_fdataरुको_range_keep_errors(काष्ठा address_space *mapping,
		loff_t start_byte, loff_t end_byte);

अटल अंतरभूत पूर्णांक filemap_fdataरुको(काष्ठा address_space *mapping)
अणु
	वापस filemap_fdataरुको_range(mapping, 0, Lदीर्घ_उच्च);
पूर्ण

बाह्य bool filemap_range_has_page(काष्ठा address_space *, loff_t lstart,
				  loff_t lend);
बाह्य bool filemap_range_needs_ग_लिखोback(काष्ठा address_space *,
					  loff_t lstart, loff_t lend);
बाह्य पूर्णांक filemap_ग_लिखो_and_रुको_range(काष्ठा address_space *mapping,
				        loff_t lstart, loff_t lend);
बाह्य पूर्णांक __filemap_fdataग_लिखो_range(काष्ठा address_space *mapping,
				loff_t start, loff_t end, पूर्णांक sync_mode);
बाह्य पूर्णांक filemap_fdataग_लिखो_range(काष्ठा address_space *mapping,
				loff_t start, loff_t end);
बाह्य पूर्णांक filemap_check_errors(काष्ठा address_space *mapping);
बाह्य व्योम __filemap_set_wb_err(काष्ठा address_space *mapping, पूर्णांक err);

अटल अंतरभूत पूर्णांक filemap_ग_लिखो_and_रुको(काष्ठा address_space *mapping)
अणु
	वापस filemap_ग_लिखो_and_रुको_range(mapping, 0, Lदीर्घ_उच्च);
पूर्ण

बाह्य पूर्णांक __must_check file_fdataरुको_range(काष्ठा file *file, loff_t lstart,
						loff_t lend);
बाह्य पूर्णांक __must_check file_check_and_advance_wb_err(काष्ठा file *file);
बाह्य पूर्णांक __must_check file_ग_लिखो_and_रुको_range(काष्ठा file *file,
						loff_t start, loff_t end);

अटल अंतरभूत पूर्णांक file_ग_लिखो_and_रुको(काष्ठा file *file)
अणु
	वापस file_ग_लिखो_and_रुको_range(file, 0, Lदीर्घ_उच्च);
पूर्ण

/**
 * filemap_set_wb_err - set a ग_लिखोback error on an address_space
 * @mapping: mapping in which to set ग_लिखोback error
 * @err: error to be set in mapping
 *
 * When ग_लिखोback fails in some way, we must record that error so that
 * userspace can be inक्रमmed when fsync and the like are called.  We endeavor
 * to report errors on any file that was खोलो at the समय of the error.  Some
 * पूर्णांकernal callers also need to know when ग_लिखोback errors have occurred.
 *
 * When a ग_लिखोback error occurs, most fileप्रणालीs will want to call
 * filemap_set_wb_err to record the error in the mapping so that it will be
 * स्वतःmatically reported whenever fsync is called on the file.
 */
अटल अंतरभूत व्योम filemap_set_wb_err(काष्ठा address_space *mapping, पूर्णांक err)
अणु
	/* Fastpath क्रम common हाल of no error */
	अगर (unlikely(err))
		__filemap_set_wb_err(mapping, err);
पूर्ण

/**
 * filemap_check_wb_err - has an error occurred since the mark was sampled?
 * @mapping: mapping to check क्रम ग_लिखोback errors
 * @since: previously-sampled errseq_t
 *
 * Grab the errseq_t value from the mapping, and see अगर it has changed "since"
 * the given value was sampled.
 *
 * If it has then report the latest error set, otherwise वापस 0.
 */
अटल अंतरभूत पूर्णांक filemap_check_wb_err(काष्ठा address_space *mapping,
					errseq_t since)
अणु
	वापस errseq_check(&mapping->wb_err, since);
पूर्ण

/**
 * filemap_sample_wb_err - sample the current errseq_t to test क्रम later errors
 * @mapping: mapping to be sampled
 *
 * Writeback errors are always reported relative to a particular sample poपूर्णांक
 * in the past. This function provides those sample poपूर्णांकs.
 */
अटल अंतरभूत errseq_t filemap_sample_wb_err(काष्ठा address_space *mapping)
अणु
	वापस errseq_sample(&mapping->wb_err);
पूर्ण

/**
 * file_sample_sb_err - sample the current errseq_t to test क्रम later errors
 * @file: file poपूर्णांकer to be sampled
 *
 * Grab the most current superblock-level errseq_t value क्रम the given
 * काष्ठा file.
 */
अटल अंतरभूत errseq_t file_sample_sb_err(काष्ठा file *file)
अणु
	वापस errseq_sample(&file->f_path.dentry->d_sb->s_wb_err);
पूर्ण

बाह्य पूर्णांक vfs_fsync_range(काष्ठा file *file, loff_t start, loff_t end,
			   पूर्णांक datasync);
बाह्य पूर्णांक vfs_fsync(काष्ठा file *file, पूर्णांक datasync);

बाह्य पूर्णांक sync_file_range(काष्ठा file *file, loff_t offset, loff_t nbytes,
				अचिन्हित पूर्णांक flags);

/*
 * Sync the bytes written अगर this was a synchronous ग_लिखो.  Expect ki_pos
 * to alपढ़ोy be updated क्रम the ग_लिखो, and will वापस either the amount
 * of bytes passed in, or an error अगर syncing the file failed.
 */
अटल अंतरभूत sमाप_प्रकार generic_ग_लिखो_sync(काष्ठा kiocb *iocb, sमाप_प्रकार count)
अणु
	अगर (iocb->ki_flags & IOCB_DSYNC) अणु
		पूर्णांक ret = vfs_fsync_range(iocb->ki_filp,
				iocb->ki_pos - count, iocb->ki_pos - 1,
				(iocb->ki_flags & IOCB_SYNC) ? 0 : 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस count;
पूर्ण

बाह्य व्योम emergency_sync(व्योम);
बाह्य व्योम emergency_remount(व्योम);

#अगर_घोषित CONFIG_BLOCK
बाह्य पूर्णांक bmap(काष्ठा inode *inode, sector_t *block);
#अन्यथा
अटल अंतरभूत पूर्णांक bmap(काष्ठा inode *inode,  sector_t *block)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

पूर्णांक notअगरy_change(काष्ठा user_namespace *, काष्ठा dentry *,
		  काष्ठा iattr *, काष्ठा inode **);
पूर्णांक inode_permission(काष्ठा user_namespace *, काष्ठा inode *, पूर्णांक);
पूर्णांक generic_permission(काष्ठा user_namespace *, काष्ठा inode *, पूर्णांक);
अटल अंतरभूत पूर्णांक file_permission(काष्ठा file *file, पूर्णांक mask)
अणु
	वापस inode_permission(file_mnt_user_ns(file),
				file_inode(file), mask);
पूर्ण
अटल अंतरभूत पूर्णांक path_permission(स्थिर काष्ठा path *path, पूर्णांक mask)
अणु
	वापस inode_permission(mnt_user_ns(path->mnt),
				d_inode(path->dentry), mask);
पूर्ण
पूर्णांक __check_sticky(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		   काष्ठा inode *inode);

अटल अंतरभूत bool execute_ok(काष्ठा inode *inode)
अणु
	वापस (inode->i_mode & S_IXUGO) || S_ISसूची(inode->i_mode);
पूर्ण

अटल अंतरभूत bool inode_wrong_type(स्थिर काष्ठा inode *inode, umode_t mode)
अणु
	वापस (inode->i_mode ^ mode) & S_IFMT;
पूर्ण

अटल अंतरभूत व्योम file_start_ग_लिखो(काष्ठा file *file)
अणु
	अगर (!S_ISREG(file_inode(file)->i_mode))
		वापस;
	sb_start_ग_लिखो(file_inode(file)->i_sb);
पूर्ण

अटल अंतरभूत bool file_start_ग_लिखो_trylock(काष्ठा file *file)
अणु
	अगर (!S_ISREG(file_inode(file)->i_mode))
		वापस true;
	वापस sb_start_ग_लिखो_trylock(file_inode(file)->i_sb);
पूर्ण

अटल अंतरभूत व्योम file_end_ग_लिखो(काष्ठा file *file)
अणु
	अगर (!S_ISREG(file_inode(file)->i_mode))
		वापस;
	__sb_end_ग_लिखो(file_inode(file)->i_sb, SB_FREEZE_WRITE);
पूर्ण

/*
 * get_ग_लिखो_access() माला_लो ग_लिखो permission क्रम a file.
 * put_ग_लिखो_access() releases this ग_लिखो permission.
 * This is used क्रम regular files.
 * We cannot support ग_लिखो (and maybe mmap पढ़ो-ग_लिखो shared) accesses and
 * MAP_DENYWRITE mmappings simultaneously. The i_ग_लिखोcount field of an inode
 * can have the following values:
 * 0: no ग_लिखोrs, no VM_DENYWRITE mappings
 * < 0: (-i_ग_लिखोcount) vm_area_काष्ठाs with VM_DENYWRITE set exist
 * > 0: (i_ग_लिखोcount) users are writing to the file.
 *
 * Normally we operate on that counter with atomic_अणुinc,decपूर्ण and it's safe
 * except क्रम the हालs where we करोn't hold i_ग_लिखोcount yet. Then we need to
 * use अणुget,denyपूर्ण_ग_लिखो_access() - these functions check the sign and refuse
 * to करो the change अगर sign is wrong.
 */
अटल अंतरभूत पूर्णांक get_ग_लिखो_access(काष्ठा inode *inode)
अणु
	वापस atomic_inc_unless_negative(&inode->i_ग_लिखोcount) ? 0 : -ETXTBSY;
पूर्ण
अटल अंतरभूत पूर्णांक deny_ग_लिखो_access(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	वापस atomic_dec_unless_positive(&inode->i_ग_लिखोcount) ? 0 : -ETXTBSY;
पूर्ण
अटल अंतरभूत व्योम put_ग_लिखो_access(काष्ठा inode * inode)
अणु
	atomic_dec(&inode->i_ग_लिखोcount);
पूर्ण
अटल अंतरभूत व्योम allow_ग_लिखो_access(काष्ठा file *file)
अणु
	अगर (file)
		atomic_inc(&file_inode(file)->i_ग_लिखोcount);
पूर्ण
अटल अंतरभूत bool inode_is_खोलो_क्रम_ग_लिखो(स्थिर काष्ठा inode *inode)
अणु
	वापस atomic_पढ़ो(&inode->i_ग_लिखोcount) > 0;
पूर्ण

#अगर defined(CONFIG_IMA) || defined(CONFIG_खाता_LOCKING)
अटल अंतरभूत व्योम i_पढ़ोcount_dec(काष्ठा inode *inode)
अणु
	BUG_ON(!atomic_पढ़ो(&inode->i_पढ़ोcount));
	atomic_dec(&inode->i_पढ़ोcount);
पूर्ण
अटल अंतरभूत व्योम i_पढ़ोcount_inc(काष्ठा inode *inode)
अणु
	atomic_inc(&inode->i_पढ़ोcount);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम i_पढ़ोcount_dec(काष्ठा inode *inode)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम i_पढ़ोcount_inc(काष्ठा inode *inode)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक करो_pipe_flags(पूर्णांक *, पूर्णांक);

बाह्य sमाप_प्रकार kernel_पढ़ो(काष्ठा file *, व्योम *, माप_प्रकार, loff_t *);
sमाप_प्रकार __kernel_पढ़ो(काष्ठा file *file, व्योम *buf, माप_प्रकार count, loff_t *pos);
बाह्य sमाप_प्रकार kernel_ग_लिखो(काष्ठा file *, स्थिर व्योम *, माप_प्रकार, loff_t *);
बाह्य sमाप_प्रकार __kernel_ग_लिखो(काष्ठा file *, स्थिर व्योम *, माप_प्रकार, loff_t *);
बाह्य काष्ठा file * खोलो_exec(स्थिर अक्षर *);
 
/* fs/dcache.c -- generic fs support functions */
बाह्य bool is_subdir(काष्ठा dentry *, काष्ठा dentry *);
बाह्य bool path_is_under(स्थिर काष्ठा path *, स्थिर काष्ठा path *);

बाह्य अक्षर *file_path(काष्ठा file *, अक्षर *, पूर्णांक);

#समावेश <linux/err.h>

/* needed क्रम stackable file प्रणाली support */
बाह्य loff_t शेष_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence);

बाह्य loff_t vfs_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence);

बाह्य पूर्णांक inode_init_always(काष्ठा super_block *, काष्ठा inode *);
बाह्य व्योम inode_init_once(काष्ठा inode *);
बाह्य व्योम address_space_init_once(काष्ठा address_space *mapping);
बाह्य काष्ठा inode * igrab(काष्ठा inode *);
बाह्य ino_t iunique(काष्ठा super_block *, ino_t);
बाह्य पूर्णांक inode_needs_sync(काष्ठा inode *inode);
बाह्य पूर्णांक generic_delete_inode(काष्ठा inode *inode);
अटल अंतरभूत पूर्णांक generic_drop_inode(काष्ठा inode *inode)
अणु
	वापस !inode->i_nlink || inode_unhashed(inode);
पूर्ण
बाह्य व्योम d_mark_करोntcache(काष्ठा inode *inode);

बाह्य काष्ठा inode *ilookup5_noरुको(काष्ठा super_block *sb,
		अचिन्हित दीर्घ hashval, पूर्णांक (*test)(काष्ठा inode *, व्योम *),
		व्योम *data);
बाह्य काष्ठा inode *ilookup5(काष्ठा super_block *sb, अचिन्हित दीर्घ hashval,
		पूर्णांक (*test)(काष्ठा inode *, व्योम *), व्योम *data);
बाह्य काष्ठा inode *ilookup(काष्ठा super_block *sb, अचिन्हित दीर्घ ino);

बाह्य काष्ठा inode *inode_insert5(काष्ठा inode *inode, अचिन्हित दीर्घ hashval,
		पूर्णांक (*test)(काष्ठा inode *, व्योम *),
		पूर्णांक (*set)(काष्ठा inode *, व्योम *),
		व्योम *data);
बाह्य काष्ठा inode * iget5_locked(काष्ठा super_block *, अचिन्हित दीर्घ, पूर्णांक (*test)(काष्ठा inode *, व्योम *), पूर्णांक (*set)(काष्ठा inode *, व्योम *), व्योम *);
बाह्य काष्ठा inode * iget_locked(काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य काष्ठा inode *find_inode_noरुको(काष्ठा super_block *,
				       अचिन्हित दीर्घ,
				       पूर्णांक (*match)(काष्ठा inode *,
						    अचिन्हित दीर्घ, व्योम *),
				       व्योम *data);
बाह्य काष्ठा inode *find_inode_rcu(काष्ठा super_block *, अचिन्हित दीर्घ,
				    पूर्णांक (*)(काष्ठा inode *, व्योम *), व्योम *);
बाह्य काष्ठा inode *find_inode_by_ino_rcu(काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य पूर्णांक insert_inode_locked4(काष्ठा inode *, अचिन्हित दीर्घ, पूर्णांक (*test)(काष्ठा inode *, व्योम *), व्योम *);
बाह्य पूर्णांक insert_inode_locked(काष्ठा inode *);
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
बाह्य व्योम lockdep_annotate_inode_mutex_key(काष्ठा inode *inode);
#अन्यथा
अटल अंतरभूत व्योम lockdep_annotate_inode_mutex_key(काष्ठा inode *inode) अणु पूर्ण;
#पूर्ण_अगर
बाह्य व्योम unlock_new_inode(काष्ठा inode *);
बाह्य व्योम discard_new_inode(काष्ठा inode *);
बाह्य अचिन्हित पूर्णांक get_next_ino(व्योम);
बाह्य व्योम evict_inodes(काष्ठा super_block *sb);

/*
 * Userspace may rely on the the inode number being non-zero. For example, glibc
 * simply ignores files with zero i_ino in unlink() and other places.
 *
 * As an additional complication, अगर userspace was compiled with
 * _खाता_OFFSET_BITS=32 on a 64-bit kernel we'll only end up पढ़ोing out the
 * lower 32 bits, so we need to check that those aren't zero explicitly. With
 * _खाता_OFFSET_BITS=64, this may cause some harmless false-negatives, but
 * better safe than sorry.
 */
अटल अंतरभूत bool is_zero_ino(ino_t ino)
अणु
	वापस (u32)ino == 0;
पूर्ण

बाह्य व्योम __iget(काष्ठा inode * inode);
बाह्य व्योम iget_failed(काष्ठा inode *);
बाह्य व्योम clear_inode(काष्ठा inode *);
बाह्य व्योम __destroy_inode(काष्ठा inode *);
बाह्य काष्ठा inode *new_inode_pseuकरो(काष्ठा super_block *sb);
बाह्य काष्ठा inode *new_inode(काष्ठा super_block *sb);
बाह्य व्योम मुक्त_inode_nonrcu(काष्ठा inode *inode);
बाह्य पूर्णांक should_हटाओ_suid(काष्ठा dentry *);
बाह्य पूर्णांक file_हटाओ_privs(काष्ठा file *);

बाह्य व्योम __insert_inode_hash(काष्ठा inode *, अचिन्हित दीर्घ hashval);
अटल अंतरभूत व्योम insert_inode_hash(काष्ठा inode *inode)
अणु
	__insert_inode_hash(inode, inode->i_ino);
पूर्ण

बाह्य व्योम __हटाओ_inode_hash(काष्ठा inode *);
अटल अंतरभूत व्योम हटाओ_inode_hash(काष्ठा inode *inode)
अणु
	अगर (!inode_unhashed(inode) && !hlist_fake(&inode->i_hash))
		__हटाओ_inode_hash(inode);
पूर्ण

बाह्य व्योम inode_sb_list_add(काष्ठा inode *inode);

बाह्य पूर्णांक sb_set_blocksize(काष्ठा super_block *, पूर्णांक);
बाह्य पूर्णांक sb_min_blocksize(काष्ठा super_block *, पूर्णांक);

बाह्य पूर्णांक generic_file_mmap(काष्ठा file *, काष्ठा vm_area_काष्ठा *);
बाह्य पूर्णांक generic_file_पढ़ोonly_mmap(काष्ठा file *, काष्ठा vm_area_काष्ठा *);
बाह्य sमाप_प्रकार generic_ग_लिखो_checks(काष्ठा kiocb *, काष्ठा iov_iter *);
बाह्य पूर्णांक generic_ग_लिखो_check_limits(काष्ठा file *file, loff_t pos,
		loff_t *count);
बाह्य पूर्णांक generic_file_rw_checks(काष्ठा file *file_in, काष्ठा file *file_out);
sमाप_प्रकार filemap_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to,
		sमाप_प्रकार alपढ़ोy_पढ़ो);
बाह्य sमाप_प्रकार generic_file_पढ़ो_iter(काष्ठा kiocb *, काष्ठा iov_iter *);
बाह्य sमाप_प्रकार __generic_file_ग_लिखो_iter(काष्ठा kiocb *, काष्ठा iov_iter *);
बाह्य sमाप_प्रकार generic_file_ग_लिखो_iter(काष्ठा kiocb *, काष्ठा iov_iter *);
बाह्य sमाप_प्रकार generic_file_direct_ग_लिखो(काष्ठा kiocb *, काष्ठा iov_iter *);
बाह्य sमाप_प्रकार generic_perक्रमm_ग_लिखो(काष्ठा file *, काष्ठा iov_iter *, loff_t);

sमाप_प्रकार vfs_iter_पढ़ो(काष्ठा file *file, काष्ठा iov_iter *iter, loff_t *ppos,
		rwf_t flags);
sमाप_प्रकार vfs_iter_ग_लिखो(काष्ठा file *file, काष्ठा iov_iter *iter, loff_t *ppos,
		rwf_t flags);
sमाप_प्रकार vfs_iocb_iter_पढ़ो(काष्ठा file *file, काष्ठा kiocb *iocb,
			   काष्ठा iov_iter *iter);
sमाप_प्रकार vfs_iocb_iter_ग_लिखो(काष्ठा file *file, काष्ठा kiocb *iocb,
			    काष्ठा iov_iter *iter);

/* fs/block_dev.c */
बाह्य sमाप_प्रकार blkdev_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to);
बाह्य sमाप_प्रकार blkdev_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from);
बाह्य पूर्णांक blkdev_fsync(काष्ठा file *filp, loff_t start, loff_t end,
			पूर्णांक datasync);
बाह्य व्योम block_sync_page(काष्ठा page *page);

/* fs/splice.c */
बाह्य sमाप_प्रकार generic_file_splice_पढ़ो(काष्ठा file *, loff_t *,
		काष्ठा pipe_inode_info *, माप_प्रकार, अचिन्हित पूर्णांक);
बाह्य sमाप_प्रकार iter_file_splice_ग_लिखो(काष्ठा pipe_inode_info *,
		काष्ठा file *, loff_t *, माप_प्रकार, अचिन्हित पूर्णांक);
बाह्य sमाप_प्रकार generic_splice_sendpage(काष्ठा pipe_inode_info *pipe,
		काष्ठा file *out, loff_t *, माप_प्रकार len, अचिन्हित पूर्णांक flags);
बाह्य दीर्घ करो_splice_direct(काष्ठा file *in, loff_t *ppos, काष्ठा file *out,
		loff_t *opos, माप_प्रकार len, अचिन्हित पूर्णांक flags);


बाह्य व्योम
file_ra_state_init(काष्ठा file_ra_state *ra, काष्ठा address_space *mapping);
बाह्य loff_t noop_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence);
बाह्य loff_t no_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence);
बाह्य loff_t vfs_setpos(काष्ठा file *file, loff_t offset, loff_t maxsize);
बाह्य loff_t generic_file_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence);
बाह्य loff_t generic_file_llseek_size(काष्ठा file *file, loff_t offset,
		पूर्णांक whence, loff_t maxsize, loff_t eof);
बाह्य loff_t fixed_size_llseek(काष्ठा file *file, loff_t offset,
		पूर्णांक whence, loff_t size);
बाह्य loff_t no_seek_end_llseek_size(काष्ठा file *, loff_t, पूर्णांक, loff_t);
बाह्य loff_t no_seek_end_llseek(काष्ठा file *, loff_t, पूर्णांक);
बाह्य पूर्णांक generic_file_खोलो(काष्ठा inode * inode, काष्ठा file * filp);
बाह्य पूर्णांक nonseekable_खोलो(काष्ठा inode * inode, काष्ठा file * filp);
बाह्य पूर्णांक stream_खोलो(काष्ठा inode * inode, काष्ठा file * filp);

#अगर_घोषित CONFIG_BLOCK
प्रकार व्योम (dio_submit_t)(काष्ठा bio *bio, काष्ठा inode *inode,
			    loff_t file_offset);

क्रमागत अणु
	/* need locking between buffered and direct access */
	DIO_LOCKING	= 0x01,

	/* fileप्रणाली करोes not support filling holes */
	DIO_SKIP_HOLES	= 0x02,
पूर्ण;

sमाप_प्रकार __blockdev_direct_IO(काष्ठा kiocb *iocb, काष्ठा inode *inode,
			     काष्ठा block_device *bdev, काष्ठा iov_iter *iter,
			     get_block_t get_block,
			     dio_ioकरोne_t end_io, dio_submit_t submit_io,
			     पूर्णांक flags);

अटल अंतरभूत sमाप_प्रकार blockdev_direct_IO(काष्ठा kiocb *iocb,
					 काष्ठा inode *inode,
					 काष्ठा iov_iter *iter,
					 get_block_t get_block)
अणु
	वापस __blockdev_direct_IO(iocb, inode, inode->i_sb->s_bdev, iter,
			get_block, शून्य, शून्य, DIO_LOCKING | DIO_SKIP_HOLES);
पूर्ण
#पूर्ण_अगर

व्योम inode_dio_रुको(काष्ठा inode *inode);

/**
 * inode_dio_begin - संकेत start of a direct I/O requests
 * @inode: inode the direct I/O happens on
 *
 * This is called once we've finished processing a direct I/O request,
 * and is used to wake up callers रुकोing क्रम direct I/O to be quiesced.
 */
अटल अंतरभूत व्योम inode_dio_begin(काष्ठा inode *inode)
अणु
	atomic_inc(&inode->i_dio_count);
पूर्ण

/**
 * inode_dio_end - संकेत finish of a direct I/O requests
 * @inode: inode the direct I/O happens on
 *
 * This is called once we've finished processing a direct I/O request,
 * and is used to wake up callers रुकोing क्रम direct I/O to be quiesced.
 */
अटल अंतरभूत व्योम inode_dio_end(काष्ठा inode *inode)
अणु
	अगर (atomic_dec_and_test(&inode->i_dio_count))
		wake_up_bit(&inode->i_state, __I_DIO_WAKEUP);
पूर्ण

/*
 * Warn about a page cache invalidation failure diring a direct I/O ग_लिखो.
 */
व्योम dio_warn_stale_pagecache(काष्ठा file *filp);

बाह्य व्योम inode_set_flags(काष्ठा inode *inode, अचिन्हित पूर्णांक flags,
			    अचिन्हित पूर्णांक mask);

बाह्य स्थिर काष्ठा file_operations generic_ro_fops;

#घोषणा special_file(m) (S_ISCHR(m)||S_ISBLK(m)||S_ISFIFO(m)||S_ISSOCK(m))

बाह्य पूर्णांक पढ़ोlink_copy(अक्षर __user *, पूर्णांक, स्थिर अक्षर *);
बाह्य पूर्णांक page_पढ़ोlink(काष्ठा dentry *, अक्षर __user *, पूर्णांक);
बाह्य स्थिर अक्षर *page_get_link(काष्ठा dentry *, काष्ठा inode *,
				 काष्ठा delayed_call *);
बाह्य व्योम page_put_link(व्योम *);
बाह्य पूर्णांक __page_symlink(काष्ठा inode *inode, स्थिर अक्षर *symname, पूर्णांक len,
		पूर्णांक nofs);
बाह्य पूर्णांक page_symlink(काष्ठा inode *inode, स्थिर अक्षर *symname, पूर्णांक len);
बाह्य स्थिर काष्ठा inode_operations page_symlink_inode_operations;
बाह्य व्योम kमुक्त_link(व्योम *);
व्योम generic_fillattr(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा kstat *);
बाह्य पूर्णांक vfs_getattr_nosec(स्थिर काष्ठा path *, काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य पूर्णांक vfs_getattr(स्थिर काष्ठा path *, काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
व्योम __inode_add_bytes(काष्ठा inode *inode, loff_t bytes);
व्योम inode_add_bytes(काष्ठा inode *inode, loff_t bytes);
व्योम __inode_sub_bytes(काष्ठा inode *inode, loff_t bytes);
व्योम inode_sub_bytes(काष्ठा inode *inode, loff_t bytes);
अटल अंतरभूत loff_t __inode_get_bytes(काष्ठा inode *inode)
अणु
	वापस (((loff_t)inode->i_blocks) << 9) + inode->i_bytes;
पूर्ण
loff_t inode_get_bytes(काष्ठा inode *inode);
व्योम inode_set_bytes(काष्ठा inode *inode, loff_t bytes);
स्थिर अक्षर *simple_get_link(काष्ठा dentry *, काष्ठा inode *,
			    काष्ठा delayed_call *);
बाह्य स्थिर काष्ठा inode_operations simple_symlink_inode_operations;

बाह्य पूर्णांक iterate_dir(काष्ठा file *, काष्ठा dir_context *);

पूर्णांक vfs_ख_स्थितिat(पूर्णांक dfd, स्थिर अक्षर __user *filename, काष्ठा kstat *stat,
		पूर्णांक flags);
पूर्णांक vfs_ख_स्थिति(पूर्णांक fd, काष्ठा kstat *stat);

अटल अंतरभूत पूर्णांक vfs_stat(स्थिर अक्षर __user *filename, काष्ठा kstat *stat)
अणु
	वापस vfs_ख_स्थितिat(AT_FDCWD, filename, stat, 0);
पूर्ण
अटल अंतरभूत पूर्णांक vfs_lstat(स्थिर अक्षर __user *name, काष्ठा kstat *stat)
अणु
	वापस vfs_ख_स्थितिat(AT_FDCWD, name, stat, AT_SYMLINK_NOFOLLOW);
पूर्ण

बाह्य स्थिर अक्षर *vfs_get_link(काष्ठा dentry *, काष्ठा delayed_call *);
बाह्य पूर्णांक vfs_पढ़ोlink(काष्ठा dentry *, अक्षर __user *, पूर्णांक);

बाह्य काष्ठा file_प्रणाली_type *get_fileप्रणाली(काष्ठा file_प्रणाली_type *fs);
बाह्य व्योम put_fileप्रणाली(काष्ठा file_प्रणाली_type *fs);
बाह्य काष्ठा file_प्रणाली_type *get_fs_type(स्थिर अक्षर *name);
बाह्य काष्ठा super_block *get_super(काष्ठा block_device *);
बाह्य काष्ठा super_block *get_active_super(काष्ठा block_device *bdev);
बाह्य व्योम drop_super(काष्ठा super_block *sb);
बाह्य व्योम drop_super_exclusive(काष्ठा super_block *sb);
बाह्य व्योम iterate_supers(व्योम (*)(काष्ठा super_block *, व्योम *), व्योम *);
बाह्य व्योम iterate_supers_type(काष्ठा file_प्रणाली_type *,
			        व्योम (*)(काष्ठा super_block *, व्योम *), व्योम *);

बाह्य पूर्णांक dcache_dir_खोलो(काष्ठा inode *, काष्ठा file *);
बाह्य पूर्णांक dcache_dir_बंद(काष्ठा inode *, काष्ठा file *);
बाह्य loff_t dcache_dir_lseek(काष्ठा file *, loff_t, पूर्णांक);
बाह्य पूर्णांक dcache_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);
बाह्य पूर्णांक simple_setattr(काष्ठा user_namespace *, काष्ठा dentry *,
			  काष्ठा iattr *);
बाह्य पूर्णांक simple_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *,
			  काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य पूर्णांक simple_statfs(काष्ठा dentry *, काष्ठा kstatfs *);
बाह्य पूर्णांक simple_खोलो(काष्ठा inode *inode, काष्ठा file *file);
बाह्य पूर्णांक simple_link(काष्ठा dentry *, काष्ठा inode *, काष्ठा dentry *);
बाह्य पूर्णांक simple_unlink(काष्ठा inode *, काष्ठा dentry *);
बाह्य पूर्णांक simple_सूची_हटाओ(काष्ठा inode *, काष्ठा dentry *);
बाह्य पूर्णांक simple_नाम(काष्ठा user_namespace *, काष्ठा inode *,
			 काष्ठा dentry *, काष्ठा inode *, काष्ठा dentry *,
			 अचिन्हित पूर्णांक);
बाह्य व्योम simple_recursive_removal(काष्ठा dentry *,
                              व्योम (*callback)(काष्ठा dentry *));
बाह्य पूर्णांक noop_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);
बाह्य पूर्णांक noop_set_page_dirty(काष्ठा page *page);
बाह्य व्योम noop_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक length);
बाह्य sमाप_प्रकार noop_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter);
बाह्य पूर्णांक simple_empty(काष्ठा dentry *);
बाह्य पूर्णांक simple_पढ़ोpage(काष्ठा file *file, काष्ठा page *page);
बाह्य पूर्णांक simple_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata);
बाह्य पूर्णांक simple_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata);
बाह्य पूर्णांक always_delete_dentry(स्थिर काष्ठा dentry *);
बाह्य काष्ठा inode *alloc_anon_inode(काष्ठा super_block *);
बाह्य पूर्णांक simple_nosetlease(काष्ठा file *, दीर्घ, काष्ठा file_lock **, व्योम **);
बाह्य स्थिर काष्ठा dentry_operations simple_dentry_operations;

बाह्य काष्ठा dentry *simple_lookup(काष्ठा inode *, काष्ठा dentry *, अचिन्हित पूर्णांक flags);
बाह्य sमाप_प्रकार generic_पढ़ो_dir(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
बाह्य स्थिर काष्ठा file_operations simple_dir_operations;
बाह्य स्थिर काष्ठा inode_operations simple_dir_inode_operations;
बाह्य व्योम make_empty_dir_inode(काष्ठा inode *inode);
बाह्य bool is_empty_dir_inode(काष्ठा inode *inode);
काष्ठा tree_descr अणु स्थिर अक्षर *name; स्थिर काष्ठा file_operations *ops; पूर्णांक mode; पूर्ण;
काष्ठा dentry *d_alloc_name(काष्ठा dentry *, स्थिर अक्षर *);
बाह्य पूर्णांक simple_fill_super(काष्ठा super_block *, अचिन्हित दीर्घ,
			     स्थिर काष्ठा tree_descr *);
बाह्य पूर्णांक simple_pin_fs(काष्ठा file_प्रणाली_type *, काष्ठा vfsmount **mount, पूर्णांक *count);
बाह्य व्योम simple_release_fs(काष्ठा vfsmount **mount, पूर्णांक *count);

बाह्य sमाप_प्रकार simple_पढ़ो_from_buffer(व्योम __user *to, माप_प्रकार count,
			loff_t *ppos, स्थिर व्योम *from, माप_प्रकार available);
बाह्य sमाप_प्रकार simple_ग_लिखो_to_buffer(व्योम *to, माप_प्रकार available, loff_t *ppos,
		स्थिर व्योम __user *from, माप_प्रकार count);

बाह्य पूर्णांक __generic_file_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);
बाह्य पूर्णांक generic_file_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);

बाह्य पूर्णांक generic_check_addressable(अचिन्हित, u64);

बाह्य व्योम generic_set_encrypted_ci_d_ops(काष्ठा dentry *dentry);

#अगर_घोषित CONFIG_MIGRATION
बाह्य पूर्णांक buffer_migrate_page(काष्ठा address_space *,
				काष्ठा page *, काष्ठा page *,
				क्रमागत migrate_mode);
बाह्य पूर्णांक buffer_migrate_page_norefs(काष्ठा address_space *,
				काष्ठा page *, काष्ठा page *,
				क्रमागत migrate_mode);
#अन्यथा
#घोषणा buffer_migrate_page शून्य
#घोषणा buffer_migrate_page_norefs शून्य
#पूर्ण_अगर

पूर्णांक setattr_prepare(काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);
बाह्य पूर्णांक inode_newsize_ok(स्थिर काष्ठा inode *, loff_t offset);
व्योम setattr_copy(काष्ठा user_namespace *, काष्ठा inode *inode,
		  स्थिर काष्ठा iattr *attr);

बाह्य पूर्णांक file_update_समय(काष्ठा file *file);

अटल अंतरभूत bool vma_is_dax(स्थिर काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_file && IS_DAX(vma->vm_file->f_mapping->host);
पूर्ण

अटल अंतरभूत bool vma_is_fsdax(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode;

	अगर (!IS_ENABLED(CONFIG_FS_DAX) || !vma->vm_file)
		वापस false;
	अगर (!vma_is_dax(vma))
		वापस false;
	inode = file_inode(vma->vm_file);
	अगर (S_ISCHR(inode->i_mode))
		वापस false; /* device-dax */
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक iocb_flags(काष्ठा file *file)
अणु
	पूर्णांक res = 0;
	अगर (file->f_flags & O_APPEND)
		res |= IOCB_APPEND;
	अगर (file->f_flags & O_सूचीECT)
		res |= IOCB_सूचीECT;
	अगर ((file->f_flags & O_DSYNC) || IS_SYNC(file->f_mapping->host))
		res |= IOCB_DSYNC;
	अगर (file->f_flags & __O_SYNC)
		res |= IOCB_SYNC;
	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक kiocb_set_rw_flags(काष्ठा kiocb *ki, rwf_t flags)
अणु
	पूर्णांक kiocb_flags = 0;

	/* make sure there's no overlap between RWF and निजी IOCB flags */
	BUILD_BUG_ON((__क्रमce पूर्णांक) RWF_SUPPORTED & IOCB_EVENTFD);

	अगर (!flags)
		वापस 0;
	अगर (unlikely(flags & ~RWF_SUPPORTED))
		वापस -EOPNOTSUPP;

	अगर (flags & RWF_NOWAIT) अणु
		अगर (!(ki->ki_filp->f_mode & FMODE_NOWAIT))
			वापस -EOPNOTSUPP;
		kiocb_flags |= IOCB_NOIO;
	पूर्ण
	kiocb_flags |= (__क्रमce पूर्णांक) (flags & RWF_SUPPORTED);
	अगर (flags & RWF_SYNC)
		kiocb_flags |= IOCB_DSYNC;

	ki->ki_flags |= kiocb_flags;
	वापस 0;
पूर्ण

अटल अंतरभूत ino_t parent_ino(काष्ठा dentry *dentry)
अणु
	ino_t res;

	/*
	 * Don't strictly need d_lock here? If the parent ino could change
	 * then surely we'd have a deeper race in the caller?
	 */
	spin_lock(&dentry->d_lock);
	res = dentry->d_parent->d_inode->i_ino;
	spin_unlock(&dentry->d_lock);
	वापस res;
पूर्ण

/* Transaction based IO helpers */

/*
 * An argresp is stored in an allocated page and holds the
 * size of the argument or response, aदीर्घ with its content
 */
काष्ठा simple_transaction_argresp अणु
	sमाप_प्रकार size;
	अक्षर data[];
पूर्ण;

#घोषणा SIMPLE_TRANSACTION_LIMIT (PAGE_SIZE - माप(काष्ठा simple_transaction_argresp))

अक्षर *simple_transaction_get(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार size);
sमाप_प्रकार simple_transaction_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार size, loff_t *pos);
पूर्णांक simple_transaction_release(काष्ठा inode *inode, काष्ठा file *file);

व्योम simple_transaction_set(काष्ठा file *file, माप_प्रकार n);

/*
 * simple attribute files
 *
 * These attributes behave similar to those in sysfs:
 *
 * Writing to an attribute immediately sets a value, an खोलो file can be
 * written to multiple बार.
 *
 * Reading from an attribute creates a buffer from the value that might get
 * पढ़ो with multiple पढ़ो calls. When the attribute has been पढ़ो
 * completely, no further पढ़ो calls are possible until the file is खोलोed
 * again.
 *
 * All attributes contain a text representation of a numeric value
 * that are accessed with the get() and set() functions.
 */
#घोषणा DEFINE_SIMPLE_ATTRIBUTE(__fops, __get, __set, __fmt)		\
अटल पूर्णांक __fops ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	__simple_attr_check_क्रमmat(__fmt, 0ull);			\
	वापस simple_attr_खोलो(inode, file, __get, __set, __fmt);	\
पूर्ण									\
अटल स्थिर काष्ठा file_operations __fops = अणु				\
	.owner	 = THIS_MODULE,						\
	.खोलो	 = __fops ## _खोलो,					\
	.release = simple_attr_release,					\
	.पढ़ो	 = simple_attr_पढ़ो,					\
	.ग_लिखो	 = simple_attr_ग_लिखो,					\
	.llseek	 = generic_file_llseek,					\
पूर्ण

अटल अंतरभूत __म_लिखो(1, 2)
व्योम __simple_attr_check_क्रमmat(स्थिर अक्षर *fmt, ...)
अणु
	/* करोn't करो anything, just let the compiler check the arguments; */
पूर्ण

पूर्णांक simple_attr_खोलो(काष्ठा inode *inode, काष्ठा file *file,
		     पूर्णांक (*get)(व्योम *, u64 *), पूर्णांक (*set)(व्योम *, u64),
		     स्थिर अक्षर *fmt);
पूर्णांक simple_attr_release(काष्ठा inode *inode, काष्ठा file *file);
sमाप_प्रकार simple_attr_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार len, loff_t *ppos);
sमाप_प्रकार simple_attr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार len, loff_t *ppos);

काष्ठा ctl_table;
पूर्णांक proc_nr_files(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक proc_nr_dentry(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक proc_nr_inodes(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक __init get_fileप्रणाली_list(अक्षर *buf);

#घोषणा __FMODE_EXEC		((__क्रमce पूर्णांक) FMODE_EXEC)
#घोषणा __FMODE_NONOTIFY	((__क्रमce पूर्णांक) FMODE_NONOTIFY)

#घोषणा ACC_MODE(x) ("\004\002\006\006"[(x)&O_ACCMODE])
#घोषणा OPEN_FMODE(flag) ((__क्रमce भ_शेषe_t)(((flag + 1) & O_ACCMODE) | \
					    (flag & __FMODE_NONOTIFY)))

अटल अंतरभूत bool is_sxid(umode_t mode)
अणु
	वापस (mode & S_ISUID) || ((mode & S_ISGID) && (mode & S_IXGRP));
पूर्ण

अटल अंतरभूत पूर्णांक check_sticky(काष्ठा user_namespace *mnt_userns,
			       काष्ठा inode *dir, काष्ठा inode *inode)
अणु
	अगर (!(dir->i_mode & S_ISVTX))
		वापस 0;

	वापस __check_sticky(mnt_userns, dir, inode);
पूर्ण

अटल अंतरभूत व्योम inode_has_no_xattr(काष्ठा inode *inode)
अणु
	अगर (!is_sxid(inode->i_mode) && (inode->i_sb->s_flags & SB_NOSEC))
		inode->i_flags |= S_NOSEC;
पूर्ण

अटल अंतरभूत bool is_root_inode(काष्ठा inode *inode)
अणु
	वापस inode == inode->i_sb->s_root->d_inode;
पूर्ण

अटल अंतरभूत bool dir_emit(काष्ठा dir_context *ctx,
			    स्थिर अक्षर *name, पूर्णांक namelen,
			    u64 ino, अचिन्हित type)
अणु
	वापस ctx->actor(ctx, name, namelen, ctx->pos, ino, type) == 0;
पूर्ण
अटल अंतरभूत bool dir_emit_करोt(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस ctx->actor(ctx, ".", 1, ctx->pos,
			  file->f_path.dentry->d_inode->i_ino, DT_सूची) == 0;
पूर्ण
अटल अंतरभूत bool dir_emit_करोtकरोt(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस ctx->actor(ctx, "..", 2, ctx->pos,
			  parent_ino(file->f_path.dentry), DT_सूची) == 0;
पूर्ण
अटल अंतरभूत bool dir_emit_करोts(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	अगर (ctx->pos == 0) अणु
		अगर (!dir_emit_करोt(file, ctx))
			वापस false;
		ctx->pos = 1;
	पूर्ण
	अगर (ctx->pos == 1) अणु
		अगर (!dir_emit_करोtकरोt(file, ctx))
			वापस false;
		ctx->pos = 2;
	पूर्ण
	वापस true;
पूर्ण
अटल अंतरभूत bool dir_relax(काष्ठा inode *inode)
अणु
	inode_unlock(inode);
	inode_lock(inode);
	वापस !IS_DEADसूची(inode);
पूर्ण

अटल अंतरभूत bool dir_relax_shared(काष्ठा inode *inode)
अणु
	inode_unlock_shared(inode);
	inode_lock_shared(inode);
	वापस !IS_DEADसूची(inode);
पूर्ण

बाह्य bool path_noexec(स्थिर काष्ठा path *path);
बाह्य व्योम inode_nohighmem(काष्ठा inode *inode);

/* mm/fadvise.c */
बाह्य पूर्णांक vfs_fadvise(काष्ठा file *file, loff_t offset, loff_t len,
		       पूर्णांक advice);
बाह्य पूर्णांक generic_fadvise(काष्ठा file *file, loff_t offset, loff_t len,
			   पूर्णांक advice);

/*
 * Flush file data beक्रमe changing attributes.  Caller must hold any locks
 * required to prevent further ग_लिखोs to this file until we're करोne setting
 * flags.
 */
अटल अंतरभूत पूर्णांक inode_drain_ग_लिखोs(काष्ठा inode *inode)
अणु
	inode_dio_रुको(inode);
	वापस filemap_ग_लिखो_and_रुको(inode->i_mapping);
पूर्ण

#पूर्ण_अगर /* _LINUX_FS_H */
