<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/include/linux/minix_fs.h
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */
#समावेश <linux/fs.h>
#समावेश <linux/ext2_fs.h>
#समावेश <linux/blockgroup_lock.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>

/* XXX Here क्रम now... not पूर्णांकerested in reकाष्ठाing headers JUST now */

/* data type क्रम block offset of block group */
प्रकार पूर्णांक ext2_grpblk_t;

/* data type क्रम fileप्रणाली-wide blocks number */
प्रकार अचिन्हित दीर्घ ext2_fsblk_t;

#घोषणा E2FSBLK "%lu"

काष्ठा ext2_reserve_winकरोw अणु
	ext2_fsblk_t		_rsv_start;	/* First byte reserved */
	ext2_fsblk_t		_rsv_end;	/* Last byte reserved or 0 */
पूर्ण;

काष्ठा ext2_reserve_winकरोw_node अणु
	काष्ठा rb_node	 	rsv_node;
	__u32			rsv_goal_size;
	__u32			rsv_alloc_hit;
	काष्ठा ext2_reserve_winकरोw	rsv_winकरोw;
पूर्ण;

काष्ठा ext2_block_alloc_info अणु
	/* inक्रमmation about reservation winकरोw */
	काष्ठा ext2_reserve_winकरोw_node	rsv_winकरोw_node;
	/*
	 * was i_next_alloc_block in ext2_inode_info
	 * is the logical (file-relative) number of the
	 * most-recently-allocated block in this file.
	 * We use this क्रम detecting linearly ascending allocation requests.
	 */
	__u32			last_alloc_logical_block;
	/*
	 * Was i_next_alloc_goal in ext2_inode_info
	 * is the *physical* companion to i_next_alloc_block.
	 * it is the physical block number of the block which was most-recently
	 * allocated to this file.  This gives us the goal (target) क्रम the next
	 * allocation when we detect linearly ascending requests.
	 */
	ext2_fsblk_t		last_alloc_physical_block;
पूर्ण;

#घोषणा rsv_start rsv_winकरोw._rsv_start
#घोषणा rsv_end rsv_winकरोw._rsv_end

काष्ठा mb_cache;

/*
 * second extended-fs super-block data in memory
 */
काष्ठा ext2_sb_info अणु
	अचिन्हित दीर्घ s_frag_size;	/* Size of a fragment in bytes */
	अचिन्हित दीर्घ s_frags_per_block;/* Number of fragments per block */
	अचिन्हित दीर्घ s_inodes_per_block;/* Number of inodes per block */
	अचिन्हित दीर्घ s_frags_per_group;/* Number of fragments in a group */
	अचिन्हित दीर्घ s_blocks_per_group;/* Number of blocks in a group */
	अचिन्हित दीर्घ s_inodes_per_group;/* Number of inodes in a group */
	अचिन्हित दीर्घ s_itb_per_group;	/* Number of inode table blocks per group */
	अचिन्हित दीर्घ s_gdb_count;	/* Number of group descriptor blocks */
	अचिन्हित दीर्घ s_desc_per_block;	/* Number of group descriptors per block */
	अचिन्हित दीर्घ s_groups_count;	/* Number of groups in the fs */
	अचिन्हित दीर्घ s_overhead_last;  /* Last calculated overhead */
	अचिन्हित दीर्घ s_blocks_last;    /* Last seen block count */
	काष्ठा buffer_head * s_sbh;	/* Buffer containing the super block */
	काष्ठा ext2_super_block * s_es;	/* Poपूर्णांकer to the super block in the buffer */
	काष्ठा buffer_head ** s_group_desc;
	अचिन्हित दीर्घ  s_mount_opt;
	अचिन्हित दीर्घ s_sb_block;
	kuid_t s_resuid;
	kgid_t s_resgid;
	अचिन्हित लघु s_mount_state;
	अचिन्हित लघु s_pad;
	पूर्णांक s_addr_per_block_bits;
	पूर्णांक s_desc_per_block_bits;
	पूर्णांक s_inode_size;
	पूर्णांक s_first_ino;
	spinlock_t s_next_gen_lock;
	u32 s_next_generation;
	अचिन्हित दीर्घ s_dir_count;
	u8 *s_debts;
	काष्ठा percpu_counter s_मुक्तblocks_counter;
	काष्ठा percpu_counter s_मुक्तinodes_counter;
	काष्ठा percpu_counter s_dirs_counter;
	काष्ठा blockgroup_lock *s_blockgroup_lock;
	/* root of the per fs reservation winकरोw tree */
	spinlock_t s_rsv_winकरोw_lock;
	काष्ठा rb_root s_rsv_winकरोw_root;
	काष्ठा ext2_reserve_winकरोw_node s_rsv_winकरोw_head;
	/*
	 * s_lock protects against concurrent modअगरications of s_mount_state,
	 * s_blocks_last, s_overhead_last and the content of superblock's
	 * buffer poपूर्णांकed to by sbi->s_es.
	 *
	 * Note: It is used in ext2_show_options() to provide a consistent view
	 * of the mount options.
	 */
	spinlock_t s_lock;
	काष्ठा mb_cache *s_ea_block_cache;
	काष्ठा dax_device *s_daxdev;
पूर्ण;

अटल अंतरभूत spinlock_t *
sb_bgl_lock(काष्ठा ext2_sb_info *sbi, अचिन्हित पूर्णांक block_group)
अणु
	वापस bgl_lock_ptr(sbi->s_blockgroup_lock, block_group);
पूर्ण

/*
 * Define EXT2FS_DEBUG to produce debug messages
 */
#अघोषित EXT2FS_DEBUG

/*
 * Define EXT2_RESERVATION to reserve data blocks क्रम expanding files
 */
#घोषणा EXT2_DEFAULT_RESERVE_BLOCKS     8
/*max winकरोw size: 1024(direct blocks) + 3([t,d]indirect blocks) */
#घोषणा EXT2_MAX_RESERVE_BLOCKS         1027
#घोषणा EXT2_RESERVE_WINDOW_NOT_ALLOCATED 0
/*
 * The second extended file प्रणाली version
 */
#घोषणा EXT2FS_DATE		"95/08/09"
#घोषणा EXT2FS_VERSION		"0.5b"

/*
 * Debug code
 */
#अगर_घोषित EXT2FS_DEBUG
#	define ext2_debug(f, a...)	अणु \
					prपूर्णांकk ("EXT2-fs DEBUG (%s, %d): %s:", \
						__खाता__, __LINE__, __func__); \
				  	prपूर्णांकk (f, ## a); \
					पूर्ण
#अन्यथा
#	define ext2_debug(f, a...)	/**/
#पूर्ण_अगर

/*
 * Special inode numbers
 */
#घोषणा	EXT2_BAD_INO		 1	/* Bad blocks inode */
#घोषणा EXT2_ROOT_INO		 2	/* Root inode */
#घोषणा EXT2_BOOT_LOADER_INO	 5	/* Boot loader inode */
#घोषणा EXT2_UNDEL_सूची_INO	 6	/* Undelete directory inode */

/* First non-reserved inode क्रम old ext2 fileप्रणालीs */
#घोषणा EXT2_GOOD_OLD_FIRST_INO	11

अटल अंतरभूत काष्ठा ext2_sb_info *EXT2_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

/*
 * Macro-inकाष्ठाions used to manage several block sizes
 */
#घोषणा EXT2_MIN_BLOCK_SIZE		1024
#घोषणा	EXT2_MAX_BLOCK_SIZE		4096
#घोषणा EXT2_MIN_BLOCK_LOG_SIZE		  10
#घोषणा EXT2_BLOCK_SIZE(s)		((s)->s_blocksize)
#घोषणा	EXT2_ADDR_PER_BLOCK(s)		(EXT2_BLOCK_SIZE(s) / माप (__u32))
#घोषणा EXT2_BLOCK_SIZE_BITS(s)		((s)->s_blocksize_bits)
#घोषणा	EXT2_ADDR_PER_BLOCK_BITS(s)	(EXT2_SB(s)->s_addr_per_block_bits)
#घोषणा EXT2_INODE_SIZE(s)		(EXT2_SB(s)->s_inode_size)
#घोषणा EXT2_FIRST_INO(s)		(EXT2_SB(s)->s_first_ino)

/*
 * Macro-inकाष्ठाions used to manage fragments
 */
#घोषणा EXT2_MIN_FRAG_SIZE		1024
#घोषणा	EXT2_MAX_FRAG_SIZE		4096
#घोषणा EXT2_MIN_FRAG_LOG_SIZE		  10
#घोषणा EXT2_FRAG_SIZE(s)		(EXT2_SB(s)->s_frag_size)
#घोषणा EXT2_FRAGS_PER_BLOCK(s)		(EXT2_SB(s)->s_frags_per_block)

/*
 * Structure of a blocks group descriptor
 */
काष्ठा ext2_group_desc
अणु
	__le32	bg_block_biपंचांगap;		/* Blocks biपंचांगap block */
	__le32	bg_inode_biपंचांगap;		/* Inodes biपंचांगap block */
	__le32	bg_inode_table;		/* Inodes table block */
	__le16	bg_मुक्त_blocks_count;	/* Free blocks count */
	__le16	bg_मुक्त_inodes_count;	/* Free inodes count */
	__le16	bg_used_dirs_count;	/* Directories count */
	__le16	bg_pad;
	__le32	bg_reserved[3];
पूर्ण;

/*
 * Macro-inकाष्ठाions used to manage group descriptors
 */
#घोषणा EXT2_BLOCKS_PER_GROUP(s)	(EXT2_SB(s)->s_blocks_per_group)
#घोषणा EXT2_DESC_PER_BLOCK(s)		(EXT2_SB(s)->s_desc_per_block)
#घोषणा EXT2_INODES_PER_GROUP(s)	(EXT2_SB(s)->s_inodes_per_group)
#घोषणा EXT2_DESC_PER_BLOCK_BITS(s)	(EXT2_SB(s)->s_desc_per_block_bits)

/*
 * Constants relative to the data blocks
 */
#घोषणा	EXT2_Nसूची_BLOCKS		12
#घोषणा	EXT2_IND_BLOCK			EXT2_Nसूची_BLOCKS
#घोषणा	EXT2_DIND_BLOCK			(EXT2_IND_BLOCK + 1)
#घोषणा	EXT2_TIND_BLOCK			(EXT2_DIND_BLOCK + 1)
#घोषणा	EXT2_N_BLOCKS			(EXT2_TIND_BLOCK + 1)

/*
 * Inode flags (GETFLAGS/SETFLAGS)
 */
#घोषणा	EXT2_SECRM_FL			FS_SECRM_FL	/* Secure deletion */
#घोषणा	EXT2_UNRM_FL			FS_UNRM_FL	/* Undelete */
#घोषणा	EXT2_COMPR_FL			FS_COMPR_FL	/* Compress file */
#घोषणा EXT2_SYNC_FL			FS_SYNC_FL	/* Synchronous updates */
#घोषणा EXT2_IMMUTABLE_FL		FS_IMMUTABLE_FL	/* Immutable file */
#घोषणा EXT2_APPEND_FL			FS_APPEND_FL	/* ग_लिखोs to file may only append */
#घोषणा EXT2_NODUMP_FL			FS_NODUMP_FL	/* करो not dump file */
#घोषणा EXT2_NOATIME_FL			FS_NOATIME_FL	/* करो not update aसमय */
/* Reserved क्रम compression usage... */
#घोषणा EXT2_सूचीTY_FL			FS_सूचीTY_FL
#घोषणा EXT2_COMPRBLK_FL		FS_COMPRBLK_FL	/* One or more compressed clusters */
#घोषणा EXT2_NOCOMP_FL			FS_NOCOMP_FL	/* Don't compress */
#घोषणा EXT2_ECOMPR_FL			FS_ECOMPR_FL	/* Compression error */
/* End compression flags --- maybe not all used */	
#घोषणा EXT2_BTREE_FL			FS_BTREE_FL	/* btree क्रमmat dir */
#घोषणा EXT2_INDEX_FL			FS_INDEX_FL	/* hash-indexed directory */
#घोषणा EXT2_IMAGIC_FL			FS_IMAGIC_FL	/* AFS directory */
#घोषणा EXT2_JOURNAL_DATA_FL		FS_JOURNAL_DATA_FL /* Reserved क्रम ext3 */
#घोषणा EXT2_NOTAIL_FL			FS_NOTAIL_FL	/* file tail should not be merged */
#घोषणा EXT2_सूचीSYNC_FL			FS_सूचीSYNC_FL	/* dirsync behaviour (directories only) */
#घोषणा EXT2_TOPसूची_FL			FS_TOPसूची_FL	/* Top of directory hierarchies*/
#घोषणा EXT2_RESERVED_FL		FS_RESERVED_FL	/* reserved क्रम ext2 lib */

#घोषणा EXT2_FL_USER_VISIBLE		FS_FL_USER_VISIBLE	/* User visible flags */
#घोषणा EXT2_FL_USER_MODIFIABLE		FS_FL_USER_MODIFIABLE	/* User modअगरiable flags */

/* Flags that should be inherited by new inodes from their parent. */
#घोषणा EXT2_FL_INHERITED (EXT2_SECRM_FL | EXT2_UNRM_FL | EXT2_COMPR_FL |\
			   EXT2_SYNC_FL | EXT2_NODUMP_FL |\
			   EXT2_NOATIME_FL | EXT2_COMPRBLK_FL |\
			   EXT2_NOCOMP_FL | EXT2_JOURNAL_DATA_FL |\
			   EXT2_NOTAIL_FL | EXT2_सूचीSYNC_FL)

/* Flags that are appropriate क्रम regular files (all but dir-specअगरic ones). */
#घोषणा EXT2_REG_FLMASK (~(EXT2_सूचीSYNC_FL | EXT2_TOPसूची_FL))

/* Flags that are appropriate क्रम non-directories/regular files. */
#घोषणा EXT2_OTHER_FLMASK (EXT2_NODUMP_FL | EXT2_NOATIME_FL)

/* Mask out flags that are inappropriate क्रम the given type of inode. */
अटल अंतरभूत __u32 ext2_mask_flags(umode_t mode, __u32 flags)
अणु
	अगर (S_ISसूची(mode))
		वापस flags;
	अन्यथा अगर (S_ISREG(mode))
		वापस flags & EXT2_REG_FLMASK;
	अन्यथा
		वापस flags & EXT2_OTHER_FLMASK;
पूर्ण

/*
 * ioctl commands
 */
#घोषणा	EXT2_IOC_GETVERSION		FS_IOC_GETVERSION
#घोषणा	EXT2_IOC_SETVERSION		FS_IOC_SETVERSION
#घोषणा	EXT2_IOC_GETRSVSZ		_IOR('f', 5, दीर्घ)
#घोषणा	EXT2_IOC_SETRSVSZ		_IOW('f', 6, दीर्घ)

/*
 * ioctl commands in 32 bit emulation
 */
#घोषणा EXT2_IOC32_GETVERSION		FS_IOC32_GETVERSION
#घोषणा EXT2_IOC32_SETVERSION		FS_IOC32_SETVERSION

/*
 * Structure of an inode on the disk
 */
काष्ठा ext2_inode अणु
	__le16	i_mode;		/* File mode */
	__le16	i_uid;		/* Low 16 bits of Owner Uid */
	__le32	i_size;		/* Size in bytes */
	__le32	i_aसमय;	/* Access समय */
	__le32	i_स_समय;	/* Creation समय */
	__le32	i_mसमय;	/* Modअगरication समय */
	__le32	i_dसमय;	/* Deletion Time */
	__le16	i_gid;		/* Low 16 bits of Group Id */
	__le16	i_links_count;	/* Links count */
	__le32	i_blocks;	/* Blocks count */
	__le32	i_flags;	/* File flags */
	जोड़ अणु
		काष्ठा अणु
			__le32  l_i_reserved1;
		पूर्ण linux1;
		काष्ठा अणु
			__le32  h_i_translator;
		पूर्ण hurd1;
		काष्ठा अणु
			__le32  m_i_reserved1;
		पूर्ण masix1;
	पूर्ण osd1;				/* OS dependent 1 */
	__le32	i_block[EXT2_N_BLOCKS];/* Poपूर्णांकers to blocks */
	__le32	i_generation;	/* File version (क्रम NFS) */
	__le32	i_file_acl;	/* File ACL */
	__le32	i_dir_acl;	/* Directory ACL */
	__le32	i_faddr;	/* Fragment address */
	जोड़ अणु
		काष्ठा अणु
			__u8	l_i_frag;	/* Fragment number */
			__u8	l_i_fsize;	/* Fragment size */
			__u16	i_pad1;
			__le16	l_i_uid_high;	/* these 2 fields    */
			__le16	l_i_gid_high;	/* were reserved2[0] */
			__u32	l_i_reserved2;
		पूर्ण linux2;
		काष्ठा अणु
			__u8	h_i_frag;	/* Fragment number */
			__u8	h_i_fsize;	/* Fragment size */
			__le16	h_i_mode_high;
			__le16	h_i_uid_high;
			__le16	h_i_gid_high;
			__le32	h_i_author;
		पूर्ण hurd2;
		काष्ठा अणु
			__u8	m_i_frag;	/* Fragment number */
			__u8	m_i_fsize;	/* Fragment size */
			__u16	m_pad1;
			__u32	m_i_reserved2[2];
		पूर्ण masix2;
	पूर्ण osd2;				/* OS dependent 2 */
पूर्ण;

#घोषणा i_size_high	i_dir_acl

#घोषणा i_reserved1	osd1.linux1.l_i_reserved1
#घोषणा i_frag		osd2.linux2.l_i_frag
#घोषणा i_fsize		osd2.linux2.l_i_fsize
#घोषणा i_uid_low	i_uid
#घोषणा i_gid_low	i_gid
#घोषणा i_uid_high	osd2.linux2.l_i_uid_high
#घोषणा i_gid_high	osd2.linux2.l_i_gid_high
#घोषणा i_reserved2	osd2.linux2.l_i_reserved2

/*
 * File प्रणाली states
 */
#घोषणा	EXT2_VALID_FS			0x0001	/* Unmounted cleanly */
#घोषणा	EXT2_ERROR_FS			0x0002	/* Errors detected */
#घोषणा	EFSCORRUPTED			EUCLEAN	/* Fileप्रणाली is corrupted */

/*
 * Mount flags
 */
#घोषणा EXT2_MOUNT_OLDALLOC		0x000002  /* Don't use the new Orlov allocator */
#घोषणा EXT2_MOUNT_GRPID		0x000004  /* Create files with directory's group */
#घोषणा EXT2_MOUNT_DEBUG		0x000008  /* Some debugging messages */
#घोषणा EXT2_MOUNT_ERRORS_CONT		0x000010  /* Continue on errors */
#घोषणा EXT2_MOUNT_ERRORS_RO		0x000020  /* Remount fs ro on errors */
#घोषणा EXT2_MOUNT_ERRORS_PANIC		0x000040  /* Panic on errors */
#घोषणा EXT2_MOUNT_MINIX_DF		0x000080  /* Mimics the Minix statfs */
#घोषणा EXT2_MOUNT_NOBH			0x000100  /* No buffer_heads */
#घोषणा EXT2_MOUNT_NO_UID32		0x000200  /* Disable 32-bit UIDs */
#घोषणा EXT2_MOUNT_XATTR_USER		0x004000  /* Extended user attributes */
#घोषणा EXT2_MOUNT_POSIX_ACL		0x008000  /* POSIX Access Control Lists */
#घोषणा EXT2_MOUNT_XIP			0x010000  /* Obsolete, use DAX */
#घोषणा EXT2_MOUNT_USRQUOTA		0x020000  /* user quota */
#घोषणा EXT2_MOUNT_GRPQUOTA		0x040000  /* group quota */
#घोषणा EXT2_MOUNT_RESERVATION		0x080000  /* Pपुनः_स्मृतिation */
#घोषणा EXT2_MOUNT_DAX			0x100000  /* Direct Access */


#घोषणा clear_opt(o, opt)		o &= ~EXT2_MOUNT_##opt
#घोषणा set_opt(o, opt)			o |= EXT2_MOUNT_##opt
#घोषणा test_opt(sb, opt)		(EXT2_SB(sb)->s_mount_opt & \
					 EXT2_MOUNT_##opt)
/*
 * Maximal mount counts between two fileप्रणाली checks
 */
#घोषणा EXT2_DFL_MAX_MNT_COUNT		20	/* Allow 20 mounts */
#घोषणा EXT2_DFL_CHECKINTERVAL		0	/* Don't use पूर्णांकerval check */

/*
 * Behaviour when detecting errors
 */
#घोषणा EXT2_ERRORS_CONTINUE		1	/* Continue execution */
#घोषणा EXT2_ERRORS_RO			2	/* Remount fs पढ़ो-only */
#घोषणा EXT2_ERRORS_PANIC		3	/* Panic */
#घोषणा EXT2_ERRORS_DEFAULT		EXT2_ERRORS_CONTINUE

/*
 * Structure of the super block
 */
काष्ठा ext2_super_block अणु
	__le32	s_inodes_count;		/* Inodes count */
	__le32	s_blocks_count;		/* Blocks count */
	__le32	s_r_blocks_count;	/* Reserved blocks count */
	__le32	s_मुक्त_blocks_count;	/* Free blocks count */
	__le32	s_मुक्त_inodes_count;	/* Free inodes count */
	__le32	s_first_data_block;	/* First Data Block */
	__le32	s_log_block_size;	/* Block size */
	__le32	s_log_frag_size;	/* Fragment size */
	__le32	s_blocks_per_group;	/* # Blocks per group */
	__le32	s_frags_per_group;	/* # Fragments per group */
	__le32	s_inodes_per_group;	/* # Inodes per group */
	__le32	s_mसमय;		/* Mount समय */
	__le32	s_wसमय;		/* Write समय */
	__le16	s_mnt_count;		/* Mount count */
	__le16	s_max_mnt_count;	/* Maximal mount count */
	__le16	s_magic;		/* Magic signature */
	__le16	s_state;		/* File प्रणाली state */
	__le16	s_errors;		/* Behaviour when detecting errors */
	__le16	s_minor_rev_level; 	/* minor revision level */
	__le32	s_lastcheck;		/* समय of last check */
	__le32	s_checkपूर्णांकerval;	/* max. समय between checks */
	__le32	s_creator_os;		/* OS */
	__le32	s_rev_level;		/* Revision level */
	__le16	s_def_resuid;		/* Default uid क्रम reserved blocks */
	__le16	s_def_resgid;		/* Default gid क्रम reserved blocks */
	/*
	 * These fields are क्रम EXT2_DYNAMIC_REV superblocks only.
	 *
	 * Note: the dअगरference between the compatible feature set and
	 * the incompatible feature set is that अगर there is a bit set
	 * in the incompatible feature set that the kernel करोesn't
	 * know about, it should refuse to mount the fileप्रणाली.
	 * 
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must पात and not try to meddle with
	 * things it करोesn't understand...
	 */
	__le32	s_first_ino; 		/* First non-reserved inode */
	__le16   s_inode_size; 		/* size of inode काष्ठाure */
	__le16	s_block_group_nr; 	/* block group # of this superblock */
	__le32	s_feature_compat; 	/* compatible feature set */
	__le32	s_feature_incompat; 	/* incompatible feature set */
	__le32	s_feature_ro_compat; 	/* पढ़ोonly-compatible feature set */
	__u8	s_uuid[16];		/* 128-bit uuid क्रम volume */
	अक्षर	s_volume_name[16]; 	/* volume name */
	अक्षर	s_last_mounted[64]; 	/* directory where last mounted */
	__le32	s_algorithm_usage_biपंचांगap; /* For compression */
	/*
	 * Perक्रमmance hपूर्णांकs.  Directory pपुनः_स्मृतिation should only
	 * happen अगर the EXT2_COMPAT_PREALLOC flag is on.
	 */
	__u8	s_pपुनः_स्मृति_blocks;	/* Nr of blocks to try to pपुनः_स्मृतिate*/
	__u8	s_pपुनः_स्मृति_dir_blocks;	/* Nr to pपुनः_स्मृतिate क्रम dirs */
	__u16	s_padding1;
	/*
	 * Journaling support valid अगर EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
	 */
	__u8	s_journal_uuid[16];	/* uuid of journal superblock */
	__u32	s_journal_inum;		/* inode number of journal file */
	__u32	s_journal_dev;		/* device number of journal file */
	__u32	s_last_orphan;		/* start of list of inodes to delete */
	__u32	s_hash_seed[4];		/* HTREE hash seed */
	__u8	s_def_hash_version;	/* Default hash version to use */
	__u8	s_reserved_अक्षर_pad;
	__u16	s_reserved_word_pad;
	__le32	s_शेष_mount_opts;
 	__le32	s_first_meta_bg; 	/* First metablock block group */
	__u32	s_reserved[190];	/* Padding to the end of the block */
पूर्ण;

/*
 * Codes क्रम operating प्रणालीs
 */
#घोषणा EXT2_OS_LINUX		0
#घोषणा EXT2_OS_HURD		1
#घोषणा EXT2_OS_MASIX		2
#घोषणा EXT2_OS_FREEBSD		3
#घोषणा EXT2_OS_LITES		4

/*
 * Revision levels
 */
#घोषणा EXT2_GOOD_OLD_REV	0	/* The good old (original) क्रमmat */
#घोषणा EXT2_DYNAMIC_REV	1 	/* V2 क्रमmat w/ dynamic inode sizes */

#घोषणा EXT2_CURRENT_REV	EXT2_GOOD_OLD_REV
#घोषणा EXT2_MAX_SUPP_REV	EXT2_DYNAMIC_REV

#घोषणा EXT2_GOOD_OLD_INODE_SIZE 128

/*
 * Feature set definitions
 */

#घोषणा EXT2_HAS_COMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_compat & cpu_to_le32(mask) )
#घोषणा EXT2_HAS_RO_COMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_ro_compat & cpu_to_le32(mask) )
#घोषणा EXT2_HAS_INCOMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_incompat & cpu_to_le32(mask) )
#घोषणा EXT2_SET_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_compat |= cpu_to_le32(mask)
#घोषणा EXT2_SET_RO_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_ro_compat |= cpu_to_le32(mask)
#घोषणा EXT2_SET_INCOMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_incompat |= cpu_to_le32(mask)
#घोषणा EXT2_CLEAR_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_compat &= ~cpu_to_le32(mask)
#घोषणा EXT2_CLEAR_RO_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_ro_compat &= ~cpu_to_le32(mask)
#घोषणा EXT2_CLEAR_INCOMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_incompat &= ~cpu_to_le32(mask)

#घोषणा EXT2_FEATURE_COMPAT_सूची_PREALLOC	0x0001
#घोषणा EXT2_FEATURE_COMPAT_IMAGIC_INODES	0x0002
#घोषणा EXT3_FEATURE_COMPAT_HAS_JOURNAL		0x0004
#घोषणा EXT2_FEATURE_COMPAT_EXT_ATTR		0x0008
#घोषणा EXT2_FEATURE_COMPAT_RESIZE_INO		0x0010
#घोषणा EXT2_FEATURE_COMPAT_सूची_INDEX		0x0020
#घोषणा EXT2_FEATURE_COMPAT_ANY			0xffffffff

#घोषणा EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER	0x0001
#घोषणा EXT2_FEATURE_RO_COMPAT_LARGE_खाता	0x0002
#घोषणा EXT2_FEATURE_RO_COMPAT_BTREE_सूची	0x0004
#घोषणा EXT2_FEATURE_RO_COMPAT_ANY		0xffffffff

#घोषणा EXT2_FEATURE_INCOMPAT_COMPRESSION	0x0001
#घोषणा EXT2_FEATURE_INCOMPAT_खाताTYPE		0x0002
#घोषणा EXT3_FEATURE_INCOMPAT_RECOVER		0x0004
#घोषणा EXT3_FEATURE_INCOMPAT_JOURNAL_DEV	0x0008
#घोषणा EXT2_FEATURE_INCOMPAT_META_BG		0x0010
#घोषणा EXT2_FEATURE_INCOMPAT_ANY		0xffffffff

#घोषणा EXT2_FEATURE_COMPAT_SUPP	EXT2_FEATURE_COMPAT_EXT_ATTR
#घोषणा EXT2_FEATURE_INCOMPAT_SUPP	(EXT2_FEATURE_INCOMPAT_खाताTYPE| \
					 EXT2_FEATURE_INCOMPAT_META_BG)
#घोषणा EXT2_FEATURE_RO_COMPAT_SUPP	(EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER| \
					 EXT2_FEATURE_RO_COMPAT_LARGE_खाता| \
					 EXT2_FEATURE_RO_COMPAT_BTREE_सूची)
#घोषणा EXT2_FEATURE_RO_COMPAT_UNSUPPORTED	~EXT2_FEATURE_RO_COMPAT_SUPP
#घोषणा EXT2_FEATURE_INCOMPAT_UNSUPPORTED	~EXT2_FEATURE_INCOMPAT_SUPP

/*
 * Default values क्रम user and/or group using reserved blocks
 */
#घोषणा	EXT2_DEF_RESUID		0
#घोषणा	EXT2_DEF_RESGID		0

/*
 * Default mount options
 */
#घोषणा EXT2_DEFM_DEBUG		0x0001
#घोषणा EXT2_DEFM_BSDGROUPS	0x0002
#घोषणा EXT2_DEFM_XATTR_USER	0x0004
#घोषणा EXT2_DEFM_ACL		0x0008
#घोषणा EXT2_DEFM_UID16		0x0010
    /* Not used by ext2, but reserved क्रम use by ext3 */
#घोषणा EXT3_DEFM_JMODE		0x0060 
#घोषणा EXT3_DEFM_JMODE_DATA	0x0020
#घोषणा EXT3_DEFM_JMODE_ORDERED	0x0040
#घोषणा EXT3_DEFM_JMODE_WBACK	0x0060

/*
 * Structure of a directory entry
 */

काष्ठा ext2_dir_entry अणु
	__le32	inode;			/* Inode number */
	__le16	rec_len;		/* Directory entry length */
	__le16	name_len;		/* Name length */
	अक्षर	name[];			/* File name, up to EXT2_NAME_LEN */
पूर्ण;

/*
 * The new version of the directory entry.  Since EXT2 काष्ठाures are
 * stored in पूर्णांकel byte order, and the name_len field could never be
 * bigger than 255 अक्षरs, it's safe to reclaim the extra byte क्रम the
 * file_type field.
 */
काष्ठा ext2_dir_entry_2 अणु
	__le32	inode;			/* Inode number */
	__le16	rec_len;		/* Directory entry length */
	__u8	name_len;		/* Name length */
	__u8	file_type;
	अक्षर	name[];			/* File name, up to EXT2_NAME_LEN */
पूर्ण;

/*
 * EXT2_सूची_PAD defines the directory entries boundaries
 *
 * NOTE: It must be a multiple of 4
 */
#घोषणा EXT2_सूची_PAD		 	4
#घोषणा EXT2_सूची_ROUND 			(EXT2_सूची_PAD - 1)
#घोषणा EXT2_सूची_REC_LEN(name_len)	(((name_len) + 8 + EXT2_सूची_ROUND) & \
					 ~EXT2_सूची_ROUND)
#घोषणा EXT2_MAX_REC_LEN		((1<<16)-1)

अटल अंतरभूत व्योम verअगरy_offsets(व्योम)
अणु
#घोषणा A(x,y) BUILD_BUG_ON(x != दुरत्व(काष्ठा ext2_super_block, y));
	A(EXT2_SB_MAGIC_OFFSET, s_magic);
	A(EXT2_SB_BLOCKS_OFFSET, s_blocks_count);
	A(EXT2_SB_BSIZE_OFFSET, s_log_block_size);
#अघोषित A
पूर्ण

/*
 * ext2 mount options
 */
काष्ठा ext2_mount_options अणु
	अचिन्हित दीर्घ s_mount_opt;
	kuid_t s_resuid;
	kgid_t s_resgid;
पूर्ण;

/*
 * second extended file प्रणाली inode data in memory
 */
काष्ठा ext2_inode_info अणु
	__le32	i_data[15];
	__u32	i_flags;
	__u32	i_faddr;
	__u8	i_frag_no;
	__u8	i_frag_size;
	__u16	i_state;
	__u32	i_file_acl;
	__u32	i_dir_acl;
	__u32	i_dसमय;

	/*
	 * i_block_group is the number of the block group which contains
	 * this file's inode.  Constant across the lअगरeसमय of the inode,
	 * it is used क्रम making block allocation decisions - we try to
	 * place a file's data blocks near its inode block, and new inodes
	 * near to their parent directory's inode.
	 */
	__u32	i_block_group;

	/* block reservation info */
	काष्ठा ext2_block_alloc_info *i_block_alloc_info;

	__u32	i_dir_start_lookup;
#अगर_घोषित CONFIG_EXT2_FS_XATTR
	/*
	 * Extended attributes can be पढ़ो independently of the मुख्य file
	 * data. Taking i_mutex even when पढ़ोing would cause contention
	 * between पढ़ोers of EAs and ग_लिखोrs of regular file data, so
	 * instead we synchronize on xattr_sem when पढ़ोing or changing
	 * EAs.
	 */
	काष्ठा rw_semaphore xattr_sem;
#पूर्ण_अगर
	rwlock_t i_meta_lock;
#अगर_घोषित CONFIG_FS_DAX
	काष्ठा rw_semaphore dax_sem;
#पूर्ण_अगर

	/*
	 * truncate_mutex is क्रम serialising ext2_truncate() against
	 * ext2_getblock().  It also protects the पूर्णांकernals of the inode's
	 * reservation data काष्ठाures: ext2_reserve_winकरोw and
	 * ext2_reserve_winकरोw_node.
	 */
	काष्ठा mutex truncate_mutex;
	काष्ठा inode	vfs_inode;
	काष्ठा list_head i_orphan;	/* unlinked but खोलो inodes */
#अगर_घोषित CONFIG_QUOTA
	काष्ठा dquot *i_dquot[MAXQUOTAS];
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_FS_DAX
#घोषणा dax_sem_करोwn_ग_लिखो(ext2_inode)	करोwn_ग_लिखो(&(ext2_inode)->dax_sem)
#घोषणा dax_sem_up_ग_लिखो(ext2_inode)	up_ग_लिखो(&(ext2_inode)->dax_sem)
#अन्यथा
#घोषणा dax_sem_करोwn_ग_लिखो(ext2_inode)
#घोषणा dax_sem_up_ग_लिखो(ext2_inode)
#पूर्ण_अगर

/*
 * Inode dynamic state flags
 */
#घोषणा EXT2_STATE_NEW			0x00000001 /* inode is newly created */


/*
 * Function prototypes
 */

/*
 * Ok, these declarations are also in <linux/kernel.h> but none of the
 * ext2 source programs needs to include it so they are duplicated here.
 */

अटल अंतरभूत काष्ठा ext2_inode_info *EXT2_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा ext2_inode_info, vfs_inode);
पूर्ण

/* balloc.c */
बाह्य पूर्णांक ext2_bg_has_super(काष्ठा super_block *sb, पूर्णांक group);
बाह्य अचिन्हित दीर्घ ext2_bg_num_gdb(काष्ठा super_block *sb, पूर्णांक group);
बाह्य ext2_fsblk_t ext2_new_block(काष्ठा inode *, अचिन्हित दीर्घ, पूर्णांक *);
बाह्य ext2_fsblk_t ext2_new_blocks(काष्ठा inode *, अचिन्हित दीर्घ,
				अचिन्हित दीर्घ *, पूर्णांक *);
बाह्य पूर्णांक ext2_data_block_valid(काष्ठा ext2_sb_info *sbi, ext2_fsblk_t start_blk,
				 अचिन्हित पूर्णांक count);
बाह्य व्योम ext2_मुक्त_blocks (काष्ठा inode *, अचिन्हित दीर्घ,
			      अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ ext2_count_मुक्त_blocks (काष्ठा super_block *);
बाह्य अचिन्हित दीर्घ ext2_count_dirs (काष्ठा super_block *);
बाह्य काष्ठा ext2_group_desc * ext2_get_group_desc(काष्ठा super_block * sb,
						    अचिन्हित पूर्णांक block_group,
						    काष्ठा buffer_head ** bh);
बाह्य व्योम ext2_discard_reservation (काष्ठा inode *);
बाह्य पूर्णांक ext2_should_retry_alloc(काष्ठा super_block *sb, पूर्णांक *retries);
बाह्य व्योम ext2_init_block_alloc_info(काष्ठा inode *);
बाह्य व्योम ext2_rsv_winकरोw_add(काष्ठा super_block *sb, काष्ठा ext2_reserve_winकरोw_node *rsv);

/* dir.c */
बाह्य पूर्णांक ext2_add_link (काष्ठा dentry *, काष्ठा inode *);
बाह्य पूर्णांक ext2_inode_by_name(काष्ठा inode *dir,
			      स्थिर काष्ठा qstr *child, ino_t *ino);
बाह्य पूर्णांक ext2_make_empty(काष्ठा inode *, काष्ठा inode *);
बाह्य काष्ठा ext2_dir_entry_2 *ext2_find_entry(काष्ठा inode *, स्थिर काष्ठा qstr *,
						काष्ठा page **, व्योम **res_page_addr);
बाह्य पूर्णांक ext2_delete_entry (काष्ठा ext2_dir_entry_2 *, काष्ठा page *);
बाह्य पूर्णांक ext2_empty_dir (काष्ठा inode *);
बाह्य काष्ठा ext2_dir_entry_2 *ext2_करोtकरोt(काष्ठा inode *dir, काष्ठा page **p, व्योम **pa);
बाह्य व्योम ext2_set_link(काष्ठा inode *, काष्ठा ext2_dir_entry_2 *, काष्ठा page *, व्योम *,
			  काष्ठा inode *, पूर्णांक);
अटल अंतरभूत व्योम ext2_put_page(काष्ठा page *page, व्योम *page_addr)
अणु
	kunmap_local(page_addr);
	put_page(page);
पूर्ण

/* ialloc.c */
बाह्य काष्ठा inode * ext2_new_inode (काष्ठा inode *, umode_t, स्थिर काष्ठा qstr *);
बाह्य व्योम ext2_मुक्त_inode (काष्ठा inode *);
बाह्य अचिन्हित दीर्घ ext2_count_मुक्त_inodes (काष्ठा super_block *);
बाह्य अचिन्हित दीर्घ ext2_count_मुक्त (काष्ठा buffer_head *, अचिन्हित);

/* inode.c */
बाह्य काष्ठा inode *ext2_iget (काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य पूर्णांक ext2_ग_लिखो_inode (काष्ठा inode *, काष्ठा ग_लिखोback_control *);
बाह्य व्योम ext2_evict_inode(काष्ठा inode *);
बाह्य पूर्णांक ext2_get_block(काष्ठा inode *, sector_t, काष्ठा buffer_head *, पूर्णांक);
बाह्य पूर्णांक ext2_setattr (काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);
बाह्य पूर्णांक ext2_getattr (काष्ठा user_namespace *, स्थिर काष्ठा path *,
			 काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य व्योम ext2_set_inode_flags(काष्ठा inode *inode);
बाह्य पूर्णांक ext2_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		       u64 start, u64 len);

/* ioctl.c */
बाह्य पूर्णांक ext2_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
बाह्य पूर्णांक ext2_fileattr_set(काष्ठा user_namespace *mnt_userns,
			     काष्ठा dentry *dentry, काष्ठा fileattr *fa);
बाह्य दीर्घ ext2_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
बाह्य दीर्घ ext2_compat_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);

/* namei.c */
काष्ठा dentry *ext2_get_parent(काष्ठा dentry *child);

/* super.c */
बाह्य __म_लिखो(3, 4)
व्योम ext2_error(काष्ठा super_block *, स्थिर अक्षर *, स्थिर अक्षर *, ...);
बाह्य __म_लिखो(3, 4)
व्योम ext2_msg(काष्ठा super_block *, स्थिर अक्षर *, स्थिर अक्षर *, ...);
बाह्य व्योम ext2_update_dynamic_rev (काष्ठा super_block *sb);
बाह्य व्योम ext2_sync_super(काष्ठा super_block *sb, काष्ठा ext2_super_block *es,
			    पूर्णांक रुको);

/*
 * Inodes and files operations
 */

/* dir.c */
बाह्य स्थिर काष्ठा file_operations ext2_dir_operations;

/* file.c */
बाह्य पूर्णांक ext2_fsync(काष्ठा file *file, loff_t start, loff_t end,
		      पूर्णांक datasync);
बाह्य स्थिर काष्ठा inode_operations ext2_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations ext2_file_operations;

/* inode.c */
बाह्य व्योम ext2_set_file_ops(काष्ठा inode *inode);
बाह्य स्थिर काष्ठा address_space_operations ext2_aops;
बाह्य स्थिर काष्ठा address_space_operations ext2_nobh_aops;
बाह्य स्थिर काष्ठा iomap_ops ext2_iomap_ops;

/* namei.c */
बाह्य स्थिर काष्ठा inode_operations ext2_dir_inode_operations;
बाह्य स्थिर काष्ठा inode_operations ext2_special_inode_operations;

/* symlink.c */
बाह्य स्थिर काष्ठा inode_operations ext2_fast_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations ext2_symlink_inode_operations;

अटल अंतरभूत ext2_fsblk_t
ext2_group_first_block_no(काष्ठा super_block *sb, अचिन्हित दीर्घ group_no)
अणु
	वापस group_no * (ext2_fsblk_t)EXT2_BLOCKS_PER_GROUP(sb) +
		le32_to_cpu(EXT2_SB(sb)->s_es->s_first_data_block);
पूर्ण

अटल अंतरभूत ext2_fsblk_t
ext2_group_last_block_no(काष्ठा super_block *sb, अचिन्हित दीर्घ group_no)
अणु
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);

	अगर (group_no == sbi->s_groups_count - 1)
		वापस le32_to_cpu(sbi->s_es->s_blocks_count) - 1;
	अन्यथा
		वापस ext2_group_first_block_no(sb, group_no) +
			EXT2_BLOCKS_PER_GROUP(sb) - 1;
पूर्ण

#घोषणा ext2_set_bit	__test_and_set_bit_le
#घोषणा ext2_clear_bit	__test_and_clear_bit_le
#घोषणा ext2_test_bit	test_bit_le
#घोषणा ext2_find_first_zero_bit	find_first_zero_bit_le
#घोषणा ext2_find_next_zero_bit		find_next_zero_bit_le
