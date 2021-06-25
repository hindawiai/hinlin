<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * nilfs.h - NILFS local header file.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato and Ryusuke Konishi.
 */

#अगर_अघोषित _NILFS_H
#घोषणा _NILFS_H

#समावेश <linux/kernel.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/nilfs2_api.h>
#समावेश <linux/nilfs2_ondisk.h>
#समावेश "the_nilfs.h"
#समावेश "bmap.h"

/**
 * काष्ठा nilfs_inode_info - nilfs inode data in memory
 * @i_flags: inode flags
 * @i_state: dynamic state flags
 * @i_bmap: poपूर्णांकer on i_bmap_data
 * @i_bmap_data: raw block mapping
 * @i_xattr: <TODO>
 * @i_dir_start_lookup: page index of last successful search
 * @i_cno: checkpoपूर्णांक number क्रम GC inode
 * @i_btnode_cache: cached pages of b-tree nodes
 * @i_dirty: list क्रम connecting dirty files
 * @xattr_sem: semaphore क्रम extended attributes processing
 * @i_bh: buffer contains disk inode
 * @i_root: root object of the current fileप्रणाली tree
 * @vfs_inode: VFS inode object
 */
काष्ठा nilfs_inode_info अणु
	__u32 i_flags;
	अचिन्हित दीर्घ  i_state;		/* Dynamic state flags */
	काष्ठा nilfs_bmap *i_bmap;
	काष्ठा nilfs_bmap i_bmap_data;
	__u64 i_xattr;	/* sector_t ??? */
	__u32 i_dir_start_lookup;
	__u64 i_cno;		/* check poपूर्णांक number क्रम GC inode */
	काष्ठा address_space i_btnode_cache;
	काष्ठा list_head i_dirty;	/* List क्रम connecting dirty files */

#अगर_घोषित CONFIG_NILFS_XATTR
	/*
	 * Extended attributes can be पढ़ो independently of the मुख्य file
	 * data. Taking i_sem even when पढ़ोing would cause contention
	 * between पढ़ोers of EAs and ग_लिखोrs of regular file data, so
	 * instead we synchronize on xattr_sem when पढ़ोing or changing
	 * EAs.
	 */
	काष्ठा rw_semaphore xattr_sem;
#पूर्ण_अगर
	काष्ठा buffer_head *i_bh;	/*
					 * i_bh contains a new or dirty
					 * disk inode.
					 */
	काष्ठा nilfs_root *i_root;
	काष्ठा inode vfs_inode;
पूर्ण;

अटल अंतरभूत काष्ठा nilfs_inode_info *NILFS_I(स्थिर काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा nilfs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत काष्ठा nilfs_inode_info *
NILFS_BMAP_I(स्थिर काष्ठा nilfs_bmap *bmap)
अणु
	वापस container_of(bmap, काष्ठा nilfs_inode_info, i_bmap_data);
पूर्ण

अटल अंतरभूत काष्ठा inode *NILFS_BTNC_I(काष्ठा address_space *btnc)
अणु
	काष्ठा nilfs_inode_info *ii =
		container_of(btnc, काष्ठा nilfs_inode_info, i_btnode_cache);
	वापस &ii->vfs_inode;
पूर्ण

/*
 * Dynamic state flags of NILFS on-memory inode (i_state)
 */
क्रमागत अणु
	NILFS_I_NEW = 0,		/* Inode is newly created */
	NILFS_I_सूचीTY,			/* The file is dirty */
	NILFS_I_QUEUED,			/* inode is in dirty_files list */
	NILFS_I_BUSY,			/*
					 * Inode is grabbed by a segment
					 * स्थिरructor
					 */
	NILFS_I_COLLECTED,		/* All dirty blocks are collected */
	NILFS_I_UPDATED,		/* The file has been written back */
	NILFS_I_INODE_SYNC,		/* dsync is not allowed क्रम inode */
	NILFS_I_BMAP,			/* has bmap and btnode_cache */
	NILFS_I_GCINODE,		/* inode क्रम GC, on memory only */
पूर्ण;

/*
 * commit flags क्रम nilfs_commit_super and nilfs_sync_super
 */
क्रमागत अणु
	NILFS_SB_COMMIT = 0,	/* Commit a super block alternately */
	NILFS_SB_COMMIT_ALL	/* Commit both super blocks */
पूर्ण;

/*
 * Macros to check inode numbers
 */
#घोषणा NILFS_MDT_INO_BITS						\
	(BIT(NILFS_DAT_INO) | BIT(NILFS_CPखाता_INO) |			\
	 BIT(NILFS_SUखाता_INO) | BIT(NILFS_Iखाता_INO) |			\
	 BIT(NILFS_ATIME_INO) | BIT(NILFS_SKETCH_INO))

#घोषणा NILFS_SYS_INO_BITS (BIT(NILFS_ROOT_INO) | NILFS_MDT_INO_BITS)

#घोषणा NILFS_FIRST_INO(sb) (((काष्ठा the_nilfs *)sb->s_fs_info)->ns_first_ino)

#घोषणा NILFS_MDT_INODE(sb, ino) \
	((ino) < NILFS_FIRST_INO(sb) && (NILFS_MDT_INO_BITS & BIT(ino)))
#घोषणा NILFS_VALID_INODE(sb, ino) \
	((ino) >= NILFS_FIRST_INO(sb) || (NILFS_SYS_INO_BITS & BIT(ino)))

/**
 * काष्ठा nilfs_transaction_info: context inक्रमmation क्रम synchronization
 * @ti_magic: Magic number
 * @ti_save: Backup of journal_info field of task_काष्ठा
 * @ti_flags: Flags
 * @ti_count: Nest level
 */
काष्ठा nilfs_transaction_info अणु
	u32			ti_magic;
	व्योम		       *ti_save;
				/*
				 * This should never be used.  If it happens,
				 * one of other fileप्रणालीs has a bug.
				 */
	अचिन्हित लघु		ti_flags;
	अचिन्हित लघु		ti_count;
पूर्ण;

/* ti_magic */
#घोषणा NILFS_TI_MAGIC		0xd9e392fb

/* ti_flags */
#घोषणा NILFS_TI_DYNAMIC_ALLOC	0x0001  /* Allocated from slab */
#घोषणा NILFS_TI_SYNC		0x0002	/*
					 * Force to स्थिरruct segment at the
					 * end of transaction.
					 */
#घोषणा NILFS_TI_GC		0x0004	/* GC context */
#घोषणा NILFS_TI_COMMIT		0x0008	/* Change happened or not */
#घोषणा NILFS_TI_WRITER		0x0010	/* Conकाष्ठाor context */


पूर्णांक nilfs_transaction_begin(काष्ठा super_block *,
			    काष्ठा nilfs_transaction_info *, पूर्णांक);
पूर्णांक nilfs_transaction_commit(काष्ठा super_block *);
व्योम nilfs_transaction_पात(काष्ठा super_block *);

अटल अंतरभूत व्योम nilfs_set_transaction_flag(अचिन्हित पूर्णांक flag)
अणु
	काष्ठा nilfs_transaction_info *ti = current->journal_info;

	ti->ti_flags |= flag;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_test_transaction_flag(अचिन्हित पूर्णांक flag)
अणु
	काष्ठा nilfs_transaction_info *ti = current->journal_info;

	अगर (ti == शून्य || ti->ti_magic != NILFS_TI_MAGIC)
		वापस 0;
	वापस !!(ti->ti_flags & flag);
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_करोing_gc(व्योम)
अणु
	वापस nilfs_test_transaction_flag(NILFS_TI_GC);
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_करोing_स्थिरruction(व्योम)
अणु
	वापस nilfs_test_transaction_flag(NILFS_TI_WRITER);
पूर्ण

/*
 * function prototype
 */
#अगर_घोषित CONFIG_NILFS_POSIX_ACL
#त्रुटि "NILFS: not yet supported POSIX ACL"
बाह्य पूर्णांक nilfs_acl_chmod(काष्ठा inode *);
बाह्य पूर्णांक nilfs_init_acl(काष्ठा inode *, काष्ठा inode *);
#अन्यथा
अटल अंतरभूत पूर्णांक nilfs_acl_chmod(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_init_acl(काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	inode->i_mode &= ~current_umask();
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा NILFS_ATIME_DISABLE

/* Flags that should be inherited by new inodes from their parent. */
#घोषणा NILFS_FL_INHERITED						\
	(FS_SECRM_FL | FS_UNRM_FL | FS_COMPR_FL | FS_SYNC_FL |		\
	 FS_IMMUTABLE_FL | FS_APPEND_FL | FS_NODUMP_FL | FS_NOATIME_FL |\
	 FS_COMPRBLK_FL | FS_NOCOMP_FL | FS_NOTAIL_FL | FS_सूचीSYNC_FL)

/* Mask out flags that are inappropriate क्रम the given type of inode. */
अटल अंतरभूत __u32 nilfs_mask_flags(umode_t mode, __u32 flags)
अणु
	अगर (S_ISसूची(mode))
		वापस flags;
	अन्यथा अगर (S_ISREG(mode))
		वापस flags & ~(FS_सूचीSYNC_FL | FS_TOPसूची_FL);
	अन्यथा
		वापस flags & (FS_NODUMP_FL | FS_NOATIME_FL);
पूर्ण

/* dir.c */
बाह्य पूर्णांक nilfs_add_link(काष्ठा dentry *, काष्ठा inode *);
बाह्य ino_t nilfs_inode_by_name(काष्ठा inode *, स्थिर काष्ठा qstr *);
बाह्य पूर्णांक nilfs_make_empty(काष्ठा inode *, काष्ठा inode *);
बाह्य काष्ठा nilfs_dir_entry *
nilfs_find_entry(काष्ठा inode *, स्थिर काष्ठा qstr *, काष्ठा page **);
बाह्य पूर्णांक nilfs_delete_entry(काष्ठा nilfs_dir_entry *, काष्ठा page *);
बाह्य पूर्णांक nilfs_empty_dir(काष्ठा inode *);
बाह्य काष्ठा nilfs_dir_entry *nilfs_करोtकरोt(काष्ठा inode *, काष्ठा page **);
बाह्य व्योम nilfs_set_link(काष्ठा inode *, काष्ठा nilfs_dir_entry *,
			   काष्ठा page *, काष्ठा inode *);

/* file.c */
बाह्य पूर्णांक nilfs_sync_file(काष्ठा file *, loff_t, loff_t, पूर्णांक);

/* ioctl.c */
पूर्णांक nilfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *m);
पूर्णांक nilfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
		       काष्ठा dentry *dentry, काष्ठा fileattr *fa);
दीर्घ nilfs_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
दीर्घ nilfs_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक nilfs_ioctl_prepare_clean_segments(काष्ठा the_nilfs *, काष्ठा nilfs_argv *,
				       व्योम **);

/* inode.c */
व्योम nilfs_inode_add_blocks(काष्ठा inode *inode, पूर्णांक n);
व्योम nilfs_inode_sub_blocks(काष्ठा inode *inode, पूर्णांक n);
बाह्य काष्ठा inode *nilfs_new_inode(काष्ठा inode *, umode_t);
बाह्य पूर्णांक nilfs_get_block(काष्ठा inode *, sector_t, काष्ठा buffer_head *, पूर्णांक);
बाह्य व्योम nilfs_set_inode_flags(काष्ठा inode *);
बाह्य पूर्णांक nilfs_पढ़ो_inode_common(काष्ठा inode *, काष्ठा nilfs_inode *);
बाह्य व्योम nilfs_ग_लिखो_inode_common(काष्ठा inode *, काष्ठा nilfs_inode *, पूर्णांक);
काष्ठा inode *nilfs_ilookup(काष्ठा super_block *sb, काष्ठा nilfs_root *root,
			    अचिन्हित दीर्घ ino);
काष्ठा inode *nilfs_iget_locked(काष्ठा super_block *sb, काष्ठा nilfs_root *root,
				अचिन्हित दीर्घ ino);
काष्ठा inode *nilfs_iget(काष्ठा super_block *sb, काष्ठा nilfs_root *root,
			 अचिन्हित दीर्घ ino);
बाह्य काष्ठा inode *nilfs_iget_क्रम_gc(काष्ठा super_block *sb,
				       अचिन्हित दीर्घ ino, __u64 cno);
बाह्य व्योम nilfs_update_inode(काष्ठा inode *, काष्ठा buffer_head *, पूर्णांक);
बाह्य व्योम nilfs_truncate(काष्ठा inode *);
बाह्य व्योम nilfs_evict_inode(काष्ठा inode *);
बाह्य पूर्णांक nilfs_setattr(काष्ठा user_namespace *, काष्ठा dentry *,
			 काष्ठा iattr *);
बाह्य व्योम nilfs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to);
पूर्णांक nilfs_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		     पूर्णांक mask);
पूर्णांक nilfs_load_inode_block(काष्ठा inode *inode, काष्ठा buffer_head **pbh);
बाह्य पूर्णांक nilfs_inode_dirty(काष्ठा inode *);
पूर्णांक nilfs_set_file_dirty(काष्ठा inode *inode, अचिन्हित पूर्णांक nr_dirty);
बाह्य पूर्णांक __nilfs_mark_inode_dirty(काष्ठा inode *, पूर्णांक);
बाह्य व्योम nilfs_dirty_inode(काष्ठा inode *, पूर्णांक flags);
पूर्णांक nilfs_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		 __u64 start, __u64 len);
अटल अंतरभूत पूर्णांक nilfs_mark_inode_dirty(काष्ठा inode *inode)
अणु
	वापस __nilfs_mark_inode_dirty(inode, I_सूचीTY);
पूर्ण
अटल अंतरभूत पूर्णांक nilfs_mark_inode_dirty_sync(काष्ठा inode *inode)
अणु
	वापस __nilfs_mark_inode_dirty(inode, I_सूचीTY_SYNC);
पूर्ण

/* super.c */
बाह्य काष्ठा inode *nilfs_alloc_inode(काष्ठा super_block *);

__म_लिखो(2, 3)
व्योम __nilfs_msg(काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(3, 4)
व्योम __nilfs_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
		   स्थिर अक्षर *fmt, ...);

#अगर_घोषित CONFIG_PRINTK

#घोषणा nilfs_msg(sb, level, fmt, ...)					\
	__nilfs_msg(sb, level fmt, ##__VA_ARGS__)
#घोषणा nilfs_error(sb, fmt, ...)					\
	__nilfs_error(sb, __func__, fmt, ##__VA_ARGS__)

#अन्यथा

#घोषणा nilfs_msg(sb, level, fmt, ...)					\
	करो अणु								\
		no_prपूर्णांकk(level fmt, ##__VA_ARGS__);			\
		(व्योम)(sb);						\
	पूर्ण जबतक (0)
#घोषणा nilfs_error(sb, fmt, ...)					\
	करो अणु								\
		no_prपूर्णांकk(fmt, ##__VA_ARGS__);				\
		__nilfs_error(sb, "", " ");				\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_PRINTK */

#घोषणा nilfs_crit(sb, fmt, ...)					\
	nilfs_msg(sb, KERN_CRIT, fmt, ##__VA_ARGS__)
#घोषणा nilfs_err(sb, fmt, ...)						\
	nilfs_msg(sb, KERN_ERR, fmt, ##__VA_ARGS__)
#घोषणा nilfs_warn(sb, fmt, ...)					\
	nilfs_msg(sb, KERN_WARNING, fmt, ##__VA_ARGS__)
#घोषणा nilfs_info(sb, fmt, ...)					\
	nilfs_msg(sb, KERN_INFO, fmt, ##__VA_ARGS__)

बाह्य काष्ठा nilfs_super_block *
nilfs_पढ़ो_super_block(काष्ठा super_block *, u64, पूर्णांक, काष्ठा buffer_head **);
बाह्य पूर्णांक nilfs_store_magic_and_option(काष्ठा super_block *,
					काष्ठा nilfs_super_block *, अक्षर *);
बाह्य पूर्णांक nilfs_check_feature_compatibility(काष्ठा super_block *,
					     काष्ठा nilfs_super_block *);
बाह्य व्योम nilfs_set_log_cursor(काष्ठा nilfs_super_block *,
				 काष्ठा the_nilfs *);
काष्ठा nilfs_super_block **nilfs_prepare_super(काष्ठा super_block *sb,
					       पूर्णांक flip);
पूर्णांक nilfs_commit_super(काष्ठा super_block *sb, पूर्णांक flag);
पूर्णांक nilfs_cleanup_super(काष्ठा super_block *sb);
पूर्णांक nilfs_resize_fs(काष्ठा super_block *sb, __u64 newsize);
पूर्णांक nilfs_attach_checkpoपूर्णांक(काष्ठा super_block *sb, __u64 cno, पूर्णांक curr_mnt,
			    काष्ठा nilfs_root **root);
पूर्णांक nilfs_checkpoपूर्णांक_is_mounted(काष्ठा super_block *sb, __u64 cno);

/* gcinode.c */
पूर्णांक nilfs_gccache_submit_पढ़ो_data(काष्ठा inode *, sector_t, sector_t, __u64,
				   काष्ठा buffer_head **);
पूर्णांक nilfs_gccache_submit_पढ़ो_node(काष्ठा inode *, sector_t, __u64,
				   काष्ठा buffer_head **);
पूर्णांक nilfs_gccache_रुको_and_mark_dirty(काष्ठा buffer_head *);
पूर्णांक nilfs_init_gcinode(काष्ठा inode *inode);
व्योम nilfs_हटाओ_all_gcinodes(काष्ठा the_nilfs *nilfs);

/* sysfs.c */
पूर्णांक __init nilfs_sysfs_init(व्योम);
व्योम nilfs_sysfs_निकास(व्योम);
पूर्णांक nilfs_sysfs_create_device_group(काष्ठा super_block *);
व्योम nilfs_sysfs_delete_device_group(काष्ठा the_nilfs *);
पूर्णांक nilfs_sysfs_create_snapshot_group(काष्ठा nilfs_root *);
व्योम nilfs_sysfs_delete_snapshot_group(काष्ठा nilfs_root *);

/*
 * Inodes and files operations
 */
बाह्य स्थिर काष्ठा file_operations nilfs_dir_operations;
बाह्य स्थिर काष्ठा inode_operations nilfs_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations nilfs_file_operations;
बाह्य स्थिर काष्ठा address_space_operations nilfs_aops;
बाह्य स्थिर काष्ठा inode_operations nilfs_dir_inode_operations;
बाह्य स्थिर काष्ठा inode_operations nilfs_special_inode_operations;
बाह्य स्थिर काष्ठा inode_operations nilfs_symlink_inode_operations;

/*
 * fileप्रणाली type
 */
बाह्य काष्ठा file_प्रणाली_type nilfs_fs_type;


#पूर्ण_अगर	/* _NILFS_H */
