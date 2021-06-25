<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  ext4.h
 *
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

#अगर_अघोषित _EXT4_H
#घोषणा _EXT4_H

#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/magic.h>
#समावेश <linux/jbd2.h>
#समावेश <linux/quota.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/blockgroup_lock.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/ratelimit.h>
#समावेश <crypto/hash.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/percpu-rwsem.h>
#समावेश <linux/fiemap.h>
#अगर_घोषित __KERNEL__
#समावेश <linux/compat.h>
#पूर्ण_अगर

#समावेश <linux/fscrypt.h>
#समावेश <linux/fsverity.h>

#समावेश <linux/compiler.h>

/*
 * The fourth extended fileप्रणाली स्थिरants/काष्ठाures
 */

/*
 * with AGGRESSIVE_CHECK allocator runs consistency checks over
 * काष्ठाures. these checks slow things करोwn a lot
 */
#घोषणा AGGRESSIVE_CHECK__

/*
 * with DOUBLE_CHECK defined mballoc creates persistent in-core
 * biपंचांगaps, मुख्यtains and uses them to check क्रम द्विगुन allocations
 */
#घोषणा DOUBLE_CHECK__

/*
 * Define EXT4FS_DEBUG to produce debug messages
 */
#अघोषित EXT4FS_DEBUG

/*
 * Debug code
 */
#अगर_घोषित EXT4FS_DEBUG
#घोषणा ext4_debug(f, a...)						\
	करो अणु								\
		prपूर्णांकk(KERN_DEBUG "EXT4-fs DEBUG (%s, %d): %s:",	\
			__खाता__, __LINE__, __func__);			\
		prपूर्णांकk(KERN_DEBUG f, ## a);				\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा ext4_debug(fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

 /*
  * Turn on EXT_DEBUG to enable ext4_ext_show_path/leaf/move in extents.c
  */
#घोषणा EXT_DEBUG__

/*
 * Dynamic prपूर्णांकk क्रम controlled extents debugging.
 */
#अगर_घोषित CONFIG_EXT4_DEBUG
#घोषणा ext_debug(ino, fmt, ...)					\
	pr_debug("[%s/%d] EXT4-fs (%s): ino %lu: (%s, %d): %s:" fmt,	\
		 current->comm, task_pid_nr(current),			\
		 ino->i_sb->s_id, ino->i_ino, __खाता__, __LINE__,	\
		 __func__, ##__VA_ARGS__)
#अन्यथा
#घोषणा ext_debug(ino, fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा ASSERT(निश्चित)						\
करो अणु									\
	अगर (unlikely(!(निश्चित))) अणु					\
		prपूर्णांकk(KERN_EMERG					\
		       "Assertion failure in %s() at %s:%d: '%s'\n",	\
		       __func__, __खाता__, __LINE__, #निश्चित);		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

/* data type क्रम block offset of block group */
प्रकार पूर्णांक ext4_grpblk_t;

/* data type क्रम fileप्रणाली-wide blocks number */
प्रकार अचिन्हित दीर्घ दीर्घ ext4_fsblk_t;

/* data type क्रम file logical block number */
प्रकार __u32 ext4_lblk_t;

/* data type क्रम block group number */
प्रकार अचिन्हित पूर्णांक ext4_group_t;

क्रमागत SHIFT_सूचीECTION अणु
	SHIFT_LEFT = 0,
	SHIFT_RIGHT,
पूर्ण;

/*
 * Flags used in mballoc's allocation_context flags field.
 *
 * Also used to show what's going on क्रम debugging purposes when the
 * flag field is exported via the traceport पूर्णांकerface
 */

/* prefer goal again. length */
#घोषणा EXT4_MB_HINT_MERGE		0x0001
/* blocks alपढ़ोy reserved */
#घोषणा EXT4_MB_HINT_RESERVED		0x0002
/* metadata is being allocated */
#घोषणा EXT4_MB_HINT_METADATA		0x0004
/* first blocks in the file */
#घोषणा EXT4_MB_HINT_FIRST		0x0008
/* search क्रम the best chunk */
#घोषणा EXT4_MB_HINT_BEST		0x0010
/* data is being allocated */
#घोषणा EXT4_MB_HINT_DATA		0x0020
/* करोn't pपुनः_स्मृतिate (क्रम tails) */
#घोषणा EXT4_MB_HINT_NOPREALLOC		0x0040
/* allocate क्रम locality group */
#घोषणा EXT4_MB_HINT_GROUP_ALLOC	0x0080
/* allocate goal blocks or none */
#घोषणा EXT4_MB_HINT_GOAL_ONLY		0x0100
/* goal is meaningful */
#घोषणा EXT4_MB_HINT_TRY_GOAL		0x0200
/* blocks alपढ़ोy pre-reserved by delayed allocation */
#घोषणा EXT4_MB_DELALLOC_RESERVED	0x0400
/* We are करोing stream allocation */
#घोषणा EXT4_MB_STREAM_ALLOC		0x0800
/* Use reserved root blocks अगर needed */
#घोषणा EXT4_MB_USE_ROOT_BLOCKS		0x1000
/* Use blocks from reserved pool */
#घोषणा EXT4_MB_USE_RESERVED		0x2000
/* Do strict check क्रम मुक्त blocks जबतक retrying block allocation */
#घोषणा EXT4_MB_STRICT_CHECK		0x4000
/* Large fragment size list lookup succeeded at least once क्रम cr = 0 */
#घोषणा EXT4_MB_CR0_OPTIMIZED		0x8000
/* Avg fragment size rb tree lookup succeeded at least once क्रम cr = 1 */
#घोषणा EXT4_MB_CR1_OPTIMIZED		0x00010000
/* Perक्रमm linear traversal क्रम one group */
#घोषणा EXT4_MB_SEARCH_NEXT_LINEAR	0x00020000
काष्ठा ext4_allocation_request अणु
	/* target inode क्रम block we're allocating */
	काष्ठा inode *inode;
	/* how many blocks we want to allocate */
	अचिन्हित पूर्णांक len;
	/* logical block in target inode */
	ext4_lblk_t logical;
	/* the बंदst logical allocated block to the left */
	ext4_lblk_t lleft;
	/* the बंदst logical allocated block to the right */
	ext4_lblk_t lright;
	/* phys. target (a hपूर्णांक) */
	ext4_fsblk_t goal;
	/* phys. block क्रम the बंदst logical allocated block to the left */
	ext4_fsblk_t pleft;
	/* phys. block क्रम the बंदst logical allocated block to the right */
	ext4_fsblk_t pright;
	/* flags. see above EXT4_MB_HINT_* */
	अचिन्हित पूर्णांक flags;
पूर्ण;

/*
 * Logical to physical block mapping, used by ext4_map_blocks()
 *
 * This काष्ठाure is used to pass requests पूर्णांकo ext4_map_blocks() as
 * well as to store the inक्रमmation वापसed by ext4_map_blocks().  It
 * takes less room on the stack than a काष्ठा buffer_head.
 */
#घोषणा EXT4_MAP_NEW		BIT(BH_New)
#घोषणा EXT4_MAP_MAPPED		BIT(BH_Mapped)
#घोषणा EXT4_MAP_UNWRITTEN	BIT(BH_Unwritten)
#घोषणा EXT4_MAP_BOUNDARY	BIT(BH_Boundary)
#घोषणा EXT4_MAP_FLAGS		(EXT4_MAP_NEW | EXT4_MAP_MAPPED |\
				 EXT4_MAP_UNWRITTEN | EXT4_MAP_BOUNDARY)

काष्ठा ext4_map_blocks अणु
	ext4_fsblk_t m_pblk;
	ext4_lblk_t m_lblk;
	अचिन्हित पूर्णांक m_len;
	अचिन्हित पूर्णांक m_flags;
पूर्ण;

/*
 * Block validity checking, प्रणाली zone rbtree.
 */
काष्ठा ext4_प्रणाली_blocks अणु
	काष्ठा rb_root root;
	काष्ठा rcu_head rcu;
पूर्ण;

/*
 * Flags क्रम ext4_io_end->flags
 */
#घोषणा	EXT4_IO_END_UNWRITTEN	0x0001

काष्ठा ext4_io_end_vec अणु
	काष्ठा list_head list;		/* list of io_end_vec */
	loff_t offset;			/* offset in the file */
	sमाप_प्रकार size;			/* size of the extent */
पूर्ण;

/*
 * For converting unwritten extents on a work queue. 'handle' is used क्रम
 * buffered ग_लिखोback.
 */
प्रकार काष्ठा ext4_io_end अणु
	काष्ठा list_head	list;		/* per-file finished IO list */
	handle_t		*handle;	/* handle reserved क्रम extent
						 * conversion */
	काष्ठा inode		*inode;		/* file being written to */
	काष्ठा bio		*bio;		/* Linked list of completed
						 * bios covering the extent */
	अचिन्हित पूर्णांक		flag;		/* unwritten or not */
	atomic_t		count;		/* reference counter */
	काष्ठा list_head	list_vec;	/* list of ext4_io_end_vec */
पूर्ण ext4_io_end_t;

काष्ठा ext4_io_submit अणु
	काष्ठा ग_लिखोback_control *io_wbc;
	काष्ठा bio		*io_bio;
	ext4_io_end_t		*io_end;
	sector_t		io_next_block;
पूर्ण;

/*
 * Special inodes numbers
 */
#घोषणा	EXT4_BAD_INO		 1	/* Bad blocks inode */
#घोषणा EXT4_ROOT_INO		 2	/* Root inode */
#घोषणा EXT4_USR_QUOTA_INO	 3	/* User quota inode */
#घोषणा EXT4_GRP_QUOTA_INO	 4	/* Group quota inode */
#घोषणा EXT4_BOOT_LOADER_INO	 5	/* Boot loader inode */
#घोषणा EXT4_UNDEL_सूची_INO	 6	/* Undelete directory inode */
#घोषणा EXT4_RESIZE_INO		 7	/* Reserved group descriptors inode */
#घोषणा EXT4_JOURNAL_INO	 8	/* Journal inode */

/* First non-reserved inode क्रम old ext4 fileप्रणालीs */
#घोषणा EXT4_GOOD_OLD_FIRST_INO	11

/*
 * Maximal count of links to a file
 */
#घोषणा EXT4_LINK_MAX		65000

/*
 * Macro-inकाष्ठाions used to manage several block sizes
 */
#घोषणा EXT4_MIN_BLOCK_SIZE		1024
#घोषणा	EXT4_MAX_BLOCK_SIZE		65536
#घोषणा EXT4_MIN_BLOCK_LOG_SIZE		10
#घोषणा EXT4_MAX_BLOCK_LOG_SIZE		16
#घोषणा EXT4_MAX_CLUSTER_LOG_SIZE	30
#अगर_घोषित __KERNEL__
# define EXT4_BLOCK_SIZE(s)		((s)->s_blocksize)
#अन्यथा
# define EXT4_BLOCK_SIZE(s)		(EXT4_MIN_BLOCK_SIZE << (s)->s_log_block_size)
#पूर्ण_अगर
#घोषणा	EXT4_ADDR_PER_BLOCK(s)		(EXT4_BLOCK_SIZE(s) / माप(__u32))
#घोषणा EXT4_CLUSTER_SIZE(s)		(EXT4_BLOCK_SIZE(s) << \
					 EXT4_SB(s)->s_cluster_bits)
#अगर_घोषित __KERNEL__
# define EXT4_BLOCK_SIZE_BITS(s)	((s)->s_blocksize_bits)
# define EXT4_CLUSTER_BITS(s)		(EXT4_SB(s)->s_cluster_bits)
#अन्यथा
# define EXT4_BLOCK_SIZE_BITS(s)	((s)->s_log_block_size + 10)
#पूर्ण_अगर
#अगर_घोषित __KERNEL__
#घोषणा	EXT4_ADDR_PER_BLOCK_BITS(s)	(EXT4_SB(s)->s_addr_per_block_bits)
#घोषणा EXT4_INODE_SIZE(s)		(EXT4_SB(s)->s_inode_size)
#घोषणा EXT4_FIRST_INO(s)		(EXT4_SB(s)->s_first_ino)
#अन्यथा
#घोषणा EXT4_INODE_SIZE(s)	(((s)->s_rev_level == EXT4_GOOD_OLD_REV) ? \
				 EXT4_GOOD_OLD_INODE_SIZE : \
				 (s)->s_inode_size)
#घोषणा EXT4_FIRST_INO(s)	(((s)->s_rev_level == EXT4_GOOD_OLD_REV) ? \
				 EXT4_GOOD_OLD_FIRST_INO : \
				 (s)->s_first_ino)
#पूर्ण_अगर
#घोषणा EXT4_BLOCK_ALIGN(size, blkbits)		ALIGN((size), (1 << (blkbits)))
#घोषणा EXT4_MAX_BLOCKS(size, offset, blkbits) \
	((EXT4_BLOCK_ALIGN(size + offset, blkbits) >> blkbits) - (offset >> \
								  blkbits))

/* Translate a block number to a cluster number */
#घोषणा EXT4_B2C(sbi, blk)	((blk) >> (sbi)->s_cluster_bits)
/* Translate a cluster number to a block number */
#घोषणा EXT4_C2B(sbi, cluster)	((cluster) << (sbi)->s_cluster_bits)
/* Translate # of blks to # of clusters */
#घोषणा EXT4_NUM_B2C(sbi, blks)	(((blks) + (sbi)->s_cluster_ratio - 1) >> \
				 (sbi)->s_cluster_bits)
/* Mask out the low bits to get the starting block of the cluster */
#घोषणा EXT4_PBLK_CMASK(s, pblk) ((pblk) &				\
				  ~((ext4_fsblk_t) (s)->s_cluster_ratio - 1))
#घोषणा EXT4_LBLK_CMASK(s, lblk) ((lblk) &				\
				  ~((ext4_lblk_t) (s)->s_cluster_ratio - 1))
/* Fill in the low bits to get the last block of the cluster */
#घोषणा EXT4_LBLK_CFILL(sbi, lblk) ((lblk) |				\
				    ((ext4_lblk_t) (sbi)->s_cluster_ratio - 1))
/* Get the cluster offset */
#घोषणा EXT4_PBLK_COFF(s, pblk) ((pblk) &				\
				 ((ext4_fsblk_t) (s)->s_cluster_ratio - 1))
#घोषणा EXT4_LBLK_COFF(s, lblk) ((lblk) &				\
				 ((ext4_lblk_t) (s)->s_cluster_ratio - 1))

/*
 * Structure of a blocks group descriptor
 */
काष्ठा ext4_group_desc
अणु
	__le32	bg_block_biपंचांगap_lo;	/* Blocks biपंचांगap block */
	__le32	bg_inode_biपंचांगap_lo;	/* Inodes biपंचांगap block */
	__le32	bg_inode_table_lo;	/* Inodes table block */
	__le16	bg_मुक्त_blocks_count_lo;/* Free blocks count */
	__le16	bg_मुक्त_inodes_count_lo;/* Free inodes count */
	__le16	bg_used_dirs_count_lo;	/* Directories count */
	__le16	bg_flags;		/* EXT4_BG_flags (INODE_UNINIT, etc) */
	__le32  bg_exclude_biपंचांगap_lo;   /* Exclude biपंचांगap क्रम snapshots */
	__le16  bg_block_biपंचांगap_csum_lo;/* crc32c(s_uuid+grp_num+bbiपंचांगap) LE */
	__le16  bg_inode_biपंचांगap_csum_lo;/* crc32c(s_uuid+grp_num+ibiपंचांगap) LE */
	__le16  bg_itable_unused_lo;	/* Unused inodes count */
	__le16  bg_checksum;		/* crc16(sb_uuid+group+desc) */
	__le32	bg_block_biपंचांगap_hi;	/* Blocks biपंचांगap block MSB */
	__le32	bg_inode_biपंचांगap_hi;	/* Inodes biपंचांगap block MSB */
	__le32	bg_inode_table_hi;	/* Inodes table block MSB */
	__le16	bg_मुक्त_blocks_count_hi;/* Free blocks count MSB */
	__le16	bg_मुक्त_inodes_count_hi;/* Free inodes count MSB */
	__le16	bg_used_dirs_count_hi;	/* Directories count MSB */
	__le16  bg_itable_unused_hi;    /* Unused inodes count MSB */
	__le32  bg_exclude_biपंचांगap_hi;   /* Exclude biपंचांगap block MSB */
	__le16  bg_block_biपंचांगap_csum_hi;/* crc32c(s_uuid+grp_num+bbiपंचांगap) BE */
	__le16  bg_inode_biपंचांगap_csum_hi;/* crc32c(s_uuid+grp_num+ibiपंचांगap) BE */
	__u32   bg_reserved;
पूर्ण;

#घोषणा EXT4_BG_INODE_BITMAP_CSUM_HI_END	\
	(दुरत्व(काष्ठा ext4_group_desc, bg_inode_biपंचांगap_csum_hi) + \
	 माप(__le16))
#घोषणा EXT4_BG_BLOCK_BITMAP_CSUM_HI_END	\
	(दुरत्व(काष्ठा ext4_group_desc, bg_block_biपंचांगap_csum_hi) + \
	 माप(__le16))

/*
 * Structure of a flex block group info
 */

काष्ठा flex_groups अणु
	atomic64_t	मुक्त_clusters;
	atomic_t	मुक्त_inodes;
	atomic_t	used_dirs;
पूर्ण;

#घोषणा EXT4_BG_INODE_UNINIT	0x0001 /* Inode table/biपंचांगap not in use */
#घोषणा EXT4_BG_BLOCK_UNINIT	0x0002 /* Block biपंचांगap not in use */
#घोषणा EXT4_BG_INODE_ZEROED	0x0004 /* On-disk itable initialized to zero */

/*
 * Macro-inकाष्ठाions used to manage group descriptors
 */
#घोषणा EXT4_MIN_DESC_SIZE		32
#घोषणा EXT4_MIN_DESC_SIZE_64BIT	64
#घोषणा	EXT4_MAX_DESC_SIZE		EXT4_MIN_BLOCK_SIZE
#घोषणा EXT4_DESC_SIZE(s)		(EXT4_SB(s)->s_desc_size)
#अगर_घोषित __KERNEL__
# define EXT4_BLOCKS_PER_GROUP(s)	(EXT4_SB(s)->s_blocks_per_group)
# define EXT4_CLUSTERS_PER_GROUP(s)	(EXT4_SB(s)->s_clusters_per_group)
# define EXT4_DESC_PER_BLOCK(s)		(EXT4_SB(s)->s_desc_per_block)
# define EXT4_INODES_PER_GROUP(s)	(EXT4_SB(s)->s_inodes_per_group)
# define EXT4_DESC_PER_BLOCK_BITS(s)	(EXT4_SB(s)->s_desc_per_block_bits)
#अन्यथा
# define EXT4_BLOCKS_PER_GROUP(s)	((s)->s_blocks_per_group)
# define EXT4_DESC_PER_BLOCK(s)		(EXT4_BLOCK_SIZE(s) / EXT4_DESC_SIZE(s))
# define EXT4_INODES_PER_GROUP(s)	((s)->s_inodes_per_group)
#पूर्ण_अगर

/*
 * Constants relative to the data blocks
 */
#घोषणा	EXT4_Nसूची_BLOCKS		12
#घोषणा	EXT4_IND_BLOCK			EXT4_Nसूची_BLOCKS
#घोषणा	EXT4_DIND_BLOCK			(EXT4_IND_BLOCK + 1)
#घोषणा	EXT4_TIND_BLOCK			(EXT4_DIND_BLOCK + 1)
#घोषणा	EXT4_N_BLOCKS			(EXT4_TIND_BLOCK + 1)

/*
 * Inode flags
 */
#घोषणा	EXT4_SECRM_FL			0x00000001 /* Secure deletion */
#घोषणा	EXT4_UNRM_FL			0x00000002 /* Undelete */
#घोषणा	EXT4_COMPR_FL			0x00000004 /* Compress file */
#घोषणा EXT4_SYNC_FL			0x00000008 /* Synchronous updates */
#घोषणा EXT4_IMMUTABLE_FL		0x00000010 /* Immutable file */
#घोषणा EXT4_APPEND_FL			0x00000020 /* ग_लिखोs to file may only append */
#घोषणा EXT4_NODUMP_FL			0x00000040 /* करो not dump file */
#घोषणा EXT4_NOATIME_FL			0x00000080 /* करो not update aसमय */
/* Reserved क्रम compression usage... */
#घोषणा EXT4_सूचीTY_FL			0x00000100
#घोषणा EXT4_COMPRBLK_FL		0x00000200 /* One or more compressed clusters */
#घोषणा EXT4_NOCOMPR_FL			0x00000400 /* Don't compress */
	/* nb: was previously EXT2_ECOMPR_FL */
#घोषणा EXT4_ENCRYPT_FL			0x00000800 /* encrypted file */
/* End compression flags --- maybe not all used */
#घोषणा EXT4_INDEX_FL			0x00001000 /* hash-indexed directory */
#घोषणा EXT4_IMAGIC_FL			0x00002000 /* AFS directory */
#घोषणा EXT4_JOURNAL_DATA_FL		0x00004000 /* file data should be journaled */
#घोषणा EXT4_NOTAIL_FL			0x00008000 /* file tail should not be merged */
#घोषणा EXT4_सूचीSYNC_FL			0x00010000 /* dirsync behaviour (directories only) */
#घोषणा EXT4_TOPसूची_FL			0x00020000 /* Top of directory hierarchies*/
#घोषणा EXT4_HUGE_खाता_FL               0x00040000 /* Set to each huge file */
#घोषणा EXT4_EXTENTS_FL			0x00080000 /* Inode uses extents */
#घोषणा EXT4_VERITY_FL			0x00100000 /* Verity रक्षित inode */
#घोषणा EXT4_EA_INODE_FL	        0x00200000 /* Inode used क्रम large EA */
/* 0x00400000 was क्रमmerly EXT4_खातापूर्णBLOCKS_FL */

#घोषणा EXT4_DAX_FL			0x02000000 /* Inode is DAX */

#घोषणा EXT4_INLINE_DATA_FL		0x10000000 /* Inode has अंतरभूत data. */
#घोषणा EXT4_PROJINHERIT_FL		0x20000000 /* Create with parents projid */
#घोषणा EXT4_CASEFOLD_FL		0x40000000 /* Casefolded directory */
#घोषणा EXT4_RESERVED_FL		0x80000000 /* reserved क्रम ext4 lib */

/* User modअगरiable flags */
#घोषणा EXT4_FL_USER_MODIFIABLE		(EXT4_SECRM_FL | \
					 EXT4_UNRM_FL | \
					 EXT4_COMPR_FL | \
					 EXT4_SYNC_FL | \
					 EXT4_IMMUTABLE_FL | \
					 EXT4_APPEND_FL | \
					 EXT4_NODUMP_FL | \
					 EXT4_NOATIME_FL | \
					 EXT4_JOURNAL_DATA_FL | \
					 EXT4_NOTAIL_FL | \
					 EXT4_सूचीSYNC_FL | \
					 EXT4_TOPसूची_FL | \
					 EXT4_EXTENTS_FL | \
					 0x00400000 /* EXT4_खातापूर्णBLOCKS_FL */ | \
					 EXT4_DAX_FL | \
					 EXT4_PROJINHERIT_FL | \
					 EXT4_CASEFOLD_FL)

/* User visible flags */
#घोषणा EXT4_FL_USER_VISIBLE		(EXT4_FL_USER_MODIFIABLE | \
					 EXT4_सूचीTY_FL | \
					 EXT4_COMPRBLK_FL | \
					 EXT4_NOCOMPR_FL | \
					 EXT4_ENCRYPT_FL | \
					 EXT4_INDEX_FL | \
					 EXT4_VERITY_FL | \
					 EXT4_INLINE_DATA_FL)

/* Flags that should be inherited by new inodes from their parent. */
#घोषणा EXT4_FL_INHERITED (EXT4_SECRM_FL | EXT4_UNRM_FL | EXT4_COMPR_FL |\
			   EXT4_SYNC_FL | EXT4_NODUMP_FL | EXT4_NOATIME_FL |\
			   EXT4_NOCOMPR_FL | EXT4_JOURNAL_DATA_FL |\
			   EXT4_NOTAIL_FL | EXT4_सूचीSYNC_FL |\
			   EXT4_PROJINHERIT_FL | EXT4_CASEFOLD_FL |\
			   EXT4_DAX_FL)

/* Flags that are appropriate क्रम regular files (all but dir-specअगरic ones). */
#घोषणा EXT4_REG_FLMASK (~(EXT4_सूचीSYNC_FL | EXT4_TOPसूची_FL | EXT4_CASEFOLD_FL |\
			   EXT4_PROJINHERIT_FL))

/* Flags that are appropriate क्रम non-directories/regular files. */
#घोषणा EXT4_OTHER_FLMASK (EXT4_NODUMP_FL | EXT4_NOATIME_FL)

/* The only flags that should be swapped */
#घोषणा EXT4_FL_SHOULD_SWAP (EXT4_HUGE_खाता_FL | EXT4_EXTENTS_FL)

/* Flags which are mutually exclusive to DAX */
#घोषणा EXT4_DAX_MUT_EXCL (EXT4_VERITY_FL | EXT4_ENCRYPT_FL |\
			   EXT4_JOURNAL_DATA_FL | EXT4_INLINE_DATA_FL)

/* Mask out flags that are inappropriate क्रम the given type of inode. */
अटल अंतरभूत __u32 ext4_mask_flags(umode_t mode, __u32 flags)
अणु
	अगर (S_ISसूची(mode))
		वापस flags;
	अन्यथा अगर (S_ISREG(mode))
		वापस flags & EXT4_REG_FLMASK;
	अन्यथा
		वापस flags & EXT4_OTHER_FLMASK;
पूर्ण

/*
 * Inode flags used क्रम atomic set/get
 */
क्रमागत अणु
	EXT4_INODE_SECRM	= 0,	/* Secure deletion */
	EXT4_INODE_UNRM		= 1,	/* Undelete */
	EXT4_INODE_COMPR	= 2,	/* Compress file */
	EXT4_INODE_SYNC		= 3,	/* Synchronous updates */
	EXT4_INODE_IMMUTABLE	= 4,	/* Immutable file */
	EXT4_INODE_APPEND	= 5,	/* ग_लिखोs to file may only append */
	EXT4_INODE_NODUMP	= 6,	/* करो not dump file */
	EXT4_INODE_NOATIME	= 7,	/* करो not update aसमय */
/* Reserved क्रम compression usage... */
	EXT4_INODE_सूचीTY	= 8,
	EXT4_INODE_COMPRBLK	= 9,	/* One or more compressed clusters */
	EXT4_INODE_NOCOMPR	= 10,	/* Don't compress */
	EXT4_INODE_ENCRYPT	= 11,	/* Encrypted file */
/* End compression flags --- maybe not all used */
	EXT4_INODE_INDEX	= 12,	/* hash-indexed directory */
	EXT4_INODE_IMAGIC	= 13,	/* AFS directory */
	EXT4_INODE_JOURNAL_DATA	= 14,	/* file data should be journaled */
	EXT4_INODE_NOTAIL	= 15,	/* file tail should not be merged */
	EXT4_INODE_सूचीSYNC	= 16,	/* dirsync behaviour (directories only) */
	EXT4_INODE_TOPसूची	= 17,	/* Top of directory hierarchies*/
	EXT4_INODE_HUGE_खाता	= 18,	/* Set to each huge file */
	EXT4_INODE_EXTENTS	= 19,	/* Inode uses extents */
	EXT4_INODE_VERITY	= 20,	/* Verity रक्षित inode */
	EXT4_INODE_EA_INODE	= 21,	/* Inode used क्रम large EA */
/* 22 was क्रमmerly EXT4_INODE_खातापूर्णBLOCKS */
	EXT4_INODE_DAX		= 25,	/* Inode is DAX */
	EXT4_INODE_INLINE_DATA	= 28,	/* Data in inode. */
	EXT4_INODE_PROJINHERIT	= 29,	/* Create with parents projid */
	EXT4_INODE_CASEFOLD	= 30,	/* Casefolded directory */
	EXT4_INODE_RESERVED	= 31,	/* reserved क्रम ext4 lib */
पूर्ण;

/*
 * Since it's pretty easy to mix up bit numbers and hex values, we use a
 * build-समय check to make sure that EXT4_XXX_FL is consistent with respect to
 * EXT4_INODE_XXX. If all is well, the macros will be dropped, so, it won't cost
 * any extra space in the compiled kernel image, otherwise, the build will fail.
 * It's important that these values are the same, since we are using
 * EXT4_INODE_XXX to test क्रम flag values, but EXT4_XXX_FL must be consistent
 * with the values of FS_XXX_FL defined in include/linux/fs.h and the on-disk
 * values found in ext2, ext3 and ext4 fileप्रणालीs, and of course the values
 * defined in e2fsprogs.
 *
 * It's not paranoia if the Murphy's Law really *is* out to get you.  :-)
 */
#घोषणा TEST_FLAG_VALUE(FLAG) (EXT4_##FLAG##_FL == (1 << EXT4_INODE_##FLAG))
#घोषणा CHECK_FLAG_VALUE(FLAG) BUILD_BUG_ON(!TEST_FLAG_VALUE(FLAG))

अटल अंतरभूत व्योम ext4_check_flag_values(व्योम)
अणु
	CHECK_FLAG_VALUE(SECRM);
	CHECK_FLAG_VALUE(UNRM);
	CHECK_FLAG_VALUE(COMPR);
	CHECK_FLAG_VALUE(SYNC);
	CHECK_FLAG_VALUE(IMMUTABLE);
	CHECK_FLAG_VALUE(APPEND);
	CHECK_FLAG_VALUE(NODUMP);
	CHECK_FLAG_VALUE(NOATIME);
	CHECK_FLAG_VALUE(सूचीTY);
	CHECK_FLAG_VALUE(COMPRBLK);
	CHECK_FLAG_VALUE(NOCOMPR);
	CHECK_FLAG_VALUE(ENCRYPT);
	CHECK_FLAG_VALUE(INDEX);
	CHECK_FLAG_VALUE(IMAGIC);
	CHECK_FLAG_VALUE(JOURNAL_DATA);
	CHECK_FLAG_VALUE(NOTAIL);
	CHECK_FLAG_VALUE(सूचीSYNC);
	CHECK_FLAG_VALUE(TOPसूची);
	CHECK_FLAG_VALUE(HUGE_खाता);
	CHECK_FLAG_VALUE(EXTENTS);
	CHECK_FLAG_VALUE(VERITY);
	CHECK_FLAG_VALUE(EA_INODE);
	CHECK_FLAG_VALUE(INLINE_DATA);
	CHECK_FLAG_VALUE(PROJINHERIT);
	CHECK_FLAG_VALUE(CASEFOLD);
	CHECK_FLAG_VALUE(RESERVED);
पूर्ण

/* Used to pass group descriptor data when online resize is करोne */
काष्ठा ext4_new_group_input अणु
	__u32 group;		/* Group number क्रम this data */
	__u64 block_biपंचांगap;	/* Absolute block number of block biपंचांगap */
	__u64 inode_biपंचांगap;	/* Absolute block number of inode biपंचांगap */
	__u64 inode_table;	/* Absolute block number of inode table start */
	__u32 blocks_count;	/* Total number of blocks in this group */
	__u16 reserved_blocks;	/* Number of reserved blocks in this group */
	__u16 unused;
पूर्ण;

#अगर defined(__KERNEL__) && defined(CONFIG_COMPAT)
काष्ठा compat_ext4_new_group_input अणु
	u32 group;
	compat_u64 block_biपंचांगap;
	compat_u64 inode_biपंचांगap;
	compat_u64 inode_table;
	u32 blocks_count;
	u16 reserved_blocks;
	u16 unused;
पूर्ण;
#पूर्ण_अगर

/* The काष्ठा ext4_new_group_input in kernel space, with मुक्त_blocks_count */
काष्ठा ext4_new_group_data अणु
	__u32 group;
	__u64 block_biपंचांगap;
	__u64 inode_biपंचांगap;
	__u64 inode_table;
	__u32 blocks_count;
	__u16 reserved_blocks;
	__u16 mdata_blocks;
	__u32 मुक्त_clusters_count;
पूर्ण;

/* Indexes used to index group tables in ext4_new_group_data */
क्रमागत अणु
	BLOCK_BITMAP = 0,	/* block biपंचांगap */
	INODE_BITMAP,		/* inode biपंचांगap */
	INODE_TABLE,		/* inode tables */
	GROUP_TABLE_COUNT,
पूर्ण;

/*
 * Flags used by ext4_map_blocks()
 */
	/* Allocate any needed blocks and/or convert an unwritten
	   extent to be an initialized ext4 */
#घोषणा EXT4_GET_BLOCKS_CREATE			0x0001
	/* Request the creation of an unwritten extent */
#घोषणा EXT4_GET_BLOCKS_UNWRIT_EXT		0x0002
#घोषणा EXT4_GET_BLOCKS_CREATE_UNWRIT_EXT	(EXT4_GET_BLOCKS_UNWRIT_EXT|\
						 EXT4_GET_BLOCKS_CREATE)
	/* Caller is from the delayed allocation ग_लिखोout path
	 * finally करोing the actual allocation of delayed blocks */
#घोषणा EXT4_GET_BLOCKS_DELALLOC_RESERVE	0x0004
	/* caller is from the direct IO path, request to creation of an
	unwritten extents अगर not allocated, split the unwritten
	extent अगर blocks has been pपुनः_स्मृतिated alपढ़ोy*/
#घोषणा EXT4_GET_BLOCKS_PRE_IO			0x0008
#घोषणा EXT4_GET_BLOCKS_CONVERT			0x0010
#घोषणा EXT4_GET_BLOCKS_IO_CREATE_EXT		(EXT4_GET_BLOCKS_PRE_IO|\
					 EXT4_GET_BLOCKS_CREATE_UNWRIT_EXT)
	/* Convert extent to initialized after IO complete */
#घोषणा EXT4_GET_BLOCKS_IO_CONVERT_EXT		(EXT4_GET_BLOCKS_CONVERT|\
					 EXT4_GET_BLOCKS_CREATE_UNWRIT_EXT)
	/* Eventual metadata allocation (due to growing extent tree)
	 * should not fail, so try to use reserved blocks क्रम that.*/
#घोषणा EXT4_GET_BLOCKS_METADATA_NOFAIL		0x0020
	/* Don't normalize allocation size (used क्रम fallocate) */
#घोषणा EXT4_GET_BLOCKS_NO_NORMALIZE		0x0040
	/* Convert written extents to unwritten */
#घोषणा EXT4_GET_BLOCKS_CONVERT_UNWRITTEN	0x0100
	/* Write zeros to newly created written extents */
#घोषणा EXT4_GET_BLOCKS_ZERO			0x0200
#घोषणा EXT4_GET_BLOCKS_CREATE_ZERO		(EXT4_GET_BLOCKS_CREATE |\
					EXT4_GET_BLOCKS_ZERO)
	/* Caller will submit data beक्रमe dropping transaction handle. This
	 * allows jbd2 to aव्योम submitting data beक्रमe commit. */
#घोषणा EXT4_GET_BLOCKS_IO_SUBMIT		0x0400

/*
 * The bit position of these flags must not overlap with any of the
 * EXT4_GET_BLOCKS_*.  They are used by ext4_find_extent(),
 * पढ़ो_extent_tree_block(), ext4_split_extent_at(),
 * ext4_ext_insert_extent(), and ext4_ext_create_new_leaf().
 * EXT4_EX_NOCACHE is used to indicate that the we shouldn't be
 * caching the extents when पढ़ोing from the extent tree जबतक a
 * truncate or punch hole operation is in progress.
 */
#घोषणा EXT4_EX_NOCACHE				0x40000000
#घोषणा EXT4_EX_FORCE_CACHE			0x20000000
#घोषणा EXT4_EX_NOFAIL				0x10000000

/*
 * Flags used by ext4_मुक्त_blocks
 */
#घोषणा EXT4_FREE_BLOCKS_METADATA		0x0001
#घोषणा EXT4_FREE_BLOCKS_FORGET			0x0002
#घोषणा EXT4_FREE_BLOCKS_VALIDATED		0x0004
#घोषणा EXT4_FREE_BLOCKS_NO_QUOT_UPDATE		0x0008
#घोषणा EXT4_FREE_BLOCKS_NOFREE_FIRST_CLUSTER	0x0010
#घोषणा EXT4_FREE_BLOCKS_NOFREE_LAST_CLUSTER	0x0020
#घोषणा EXT4_FREE_BLOCKS_RERESERVE_CLUSTER      0x0040

/*
 * ioctl commands
 */
#घोषणा	EXT4_IOC_GETVERSION		_IOR('f', 3, दीर्घ)
#घोषणा	EXT4_IOC_SETVERSION		_IOW('f', 4, दीर्घ)
#घोषणा	EXT4_IOC_GETVERSION_OLD		FS_IOC_GETVERSION
#घोषणा	EXT4_IOC_SETVERSION_OLD		FS_IOC_SETVERSION
#घोषणा EXT4_IOC_GETRSVSZ		_IOR('f', 5, दीर्घ)
#घोषणा EXT4_IOC_SETRSVSZ		_IOW('f', 6, दीर्घ)
#घोषणा EXT4_IOC_GROUP_EXTEND		_IOW('f', 7, अचिन्हित दीर्घ)
#घोषणा EXT4_IOC_GROUP_ADD		_IOW('f', 8, काष्ठा ext4_new_group_input)
#घोषणा EXT4_IOC_MIGRATE		_IO('f', 9)
 /* note ioctl 10 reserved क्रम an early version of the FIEMAP ioctl */
 /* note ioctl 11 reserved क्रम fileप्रणाली-independent FIEMAP ioctl */
#घोषणा EXT4_IOC_ALLOC_DA_BLKS		_IO('f', 12)
#घोषणा EXT4_IOC_MOVE_EXT		_IOWR('f', 15, काष्ठा move_extent)
#घोषणा EXT4_IOC_RESIZE_FS		_IOW('f', 16, __u64)
#घोषणा EXT4_IOC_SWAP_BOOT		_IO('f', 17)
#घोषणा EXT4_IOC_PRECACHE_EXTENTS	_IO('f', 18)
/* ioctl codes 19--39 are reserved क्रम fscrypt */
#घोषणा EXT4_IOC_CLEAR_ES_CACHE		_IO('f', 40)
#घोषणा EXT4_IOC_GETSTATE		_IOW('f', 41, __u32)
#घोषणा EXT4_IOC_GET_ES_CACHE		_IOWR('f', 42, काष्ठा fiemap)

#घोषणा EXT4_IOC_SHUTDOWN _IOR ('X', 125, __u32)

/*
 * Flags क्रम going करोwn operation
 */
#घोषणा EXT4_GOING_FLAGS_DEFAULT		0x0	/* going करोwn */
#घोषणा EXT4_GOING_FLAGS_LOGFLUSH		0x1	/* flush log but not data */
#घोषणा EXT4_GOING_FLAGS_NOLOGFLUSH		0x2	/* करोn't flush log nor data */

/*
 * Flags वापसed by EXT4_IOC_GETSTATE
 *
 * We only expose to userspace a subset of the state flags in
 * i_state_flags
 */
#घोषणा EXT4_STATE_FLAG_EXT_PRECACHED	0x00000001
#घोषणा EXT4_STATE_FLAG_NEW		0x00000002
#घोषणा EXT4_STATE_FLAG_NEWENTRY	0x00000004
#घोषणा EXT4_STATE_FLAG_DA_ALLOC_CLOSE	0x00000008

#अगर defined(__KERNEL__) && defined(CONFIG_COMPAT)
/*
 * ioctl commands in 32 bit emulation
 */
#घोषणा EXT4_IOC32_GETVERSION		_IOR('f', 3, पूर्णांक)
#घोषणा EXT4_IOC32_SETVERSION		_IOW('f', 4, पूर्णांक)
#घोषणा EXT4_IOC32_GETRSVSZ		_IOR('f', 5, पूर्णांक)
#घोषणा EXT4_IOC32_SETRSVSZ		_IOW('f', 6, पूर्णांक)
#घोषणा EXT4_IOC32_GROUP_EXTEND		_IOW('f', 7, अचिन्हित पूर्णांक)
#घोषणा EXT4_IOC32_GROUP_ADD		_IOW('f', 8, काष्ठा compat_ext4_new_group_input)
#घोषणा EXT4_IOC32_GETVERSION_OLD	FS_IOC32_GETVERSION
#घोषणा EXT4_IOC32_SETVERSION_OLD	FS_IOC32_SETVERSION
#पूर्ण_अगर

/*
 * Returned by EXT4_IOC_GET_ES_CACHE as an additional possible flag.
 * It indicates that the entry in extent status cache is क्रम a hole.
 */
#घोषणा EXT4_FIEMAP_EXTENT_HOLE		0x08000000

/* Max physical block we can address w/o extents */
#घोषणा EXT4_MAX_BLOCK_खाता_PHYS	0xFFFFFFFF

/* Max logical block we can support */
#घोषणा EXT4_MAX_LOGICAL_BLOCK		0xFFFFFFFE

/*
 * Structure of an inode on the disk
 */
काष्ठा ext4_inode अणु
	__le16	i_mode;		/* File mode */
	__le16	i_uid;		/* Low 16 bits of Owner Uid */
	__le32	i_size_lo;	/* Size in bytes */
	__le32	i_aसमय;	/* Access समय */
	__le32	i_स_समय;	/* Inode Change समय */
	__le32	i_mसमय;	/* Modअगरication समय */
	__le32	i_dसमय;	/* Deletion Time */
	__le16	i_gid;		/* Low 16 bits of Group Id */
	__le16	i_links_count;	/* Links count */
	__le32	i_blocks_lo;	/* Blocks count */
	__le32	i_flags;	/* File flags */
	जोड़ अणु
		काष्ठा अणु
			__le32  l_i_version;
		पूर्ण linux1;
		काष्ठा अणु
			__u32  h_i_translator;
		पूर्ण hurd1;
		काष्ठा अणु
			__u32  m_i_reserved1;
		पूर्ण masix1;
	पूर्ण osd1;				/* OS dependent 1 */
	__le32	i_block[EXT4_N_BLOCKS];/* Poपूर्णांकers to blocks */
	__le32	i_generation;	/* File version (क्रम NFS) */
	__le32	i_file_acl_lo;	/* File ACL */
	__le32	i_size_high;
	__le32	i_obso_faddr;	/* Obsoleted fragment address */
	जोड़ अणु
		काष्ठा अणु
			__le16	l_i_blocks_high; /* were l_i_reserved1 */
			__le16	l_i_file_acl_high;
			__le16	l_i_uid_high;	/* these 2 fields */
			__le16	l_i_gid_high;	/* were reserved2[0] */
			__le16	l_i_checksum_lo;/* crc32c(uuid+inum+inode) LE */
			__le16	l_i_reserved;
		पूर्ण linux2;
		काष्ठा अणु
			__le16	h_i_reserved1;	/* Obsoleted fragment number/size which are हटाओd in ext4 */
			__u16	h_i_mode_high;
			__u16	h_i_uid_high;
			__u16	h_i_gid_high;
			__u32	h_i_author;
		पूर्ण hurd2;
		काष्ठा अणु
			__le16	h_i_reserved1;	/* Obsoleted fragment number/size which are हटाओd in ext4 */
			__le16	m_i_file_acl_high;
			__u32	m_i_reserved2[2];
		पूर्ण masix2;
	पूर्ण osd2;				/* OS dependent 2 */
	__le16	i_extra_isize;
	__le16	i_checksum_hi;	/* crc32c(uuid+inum+inode) BE */
	__le32  i_स_समय_extra;  /* extra Change समय      (nsec << 2 | epoch) */
	__le32  i_mसमय_extra;  /* extra Modअगरication समय(nsec << 2 | epoch) */
	__le32  i_aसमय_extra;  /* extra Access समय      (nsec << 2 | epoch) */
	__le32  i_crसमय;       /* File Creation समय */
	__le32  i_crसमय_extra; /* extra FileCreationसमय (nsec << 2 | epoch) */
	__le32  i_version_hi;	/* high 32 bits क्रम 64-bit version */
	__le32	i_projid;	/* Project ID */
पूर्ण;

काष्ठा move_extent अणु
	__u32 reserved;		/* should be zero */
	__u32 करोnor_fd;		/* करोnor file descriptor */
	__u64 orig_start;	/* logical start offset in block क्रम orig */
	__u64 करोnor_start;	/* logical start offset in block क्रम करोnor */
	__u64 len;		/* block length to be moved */
	__u64 moved_len;	/* moved block length */
पूर्ण;

#घोषणा EXT4_EPOCH_BITS 2
#घोषणा EXT4_EPOCH_MASK ((1 << EXT4_EPOCH_BITS) - 1)
#घोषणा EXT4_NSEC_MASK  (~0UL << EXT4_EPOCH_BITS)

/*
 * Extended fields will fit पूर्णांकo an inode अगर the fileप्रणाली was क्रमmatted
 * with large inodes (-I 256 or larger) and there are not currently any EAs
 * consuming all of the available space. For new inodes we always reserve
 * enough space क्रम the kernel's known extended fields, but क्रम inodes
 * created with an old kernel this might not have been the हाल. None of
 * the extended inode fields is critical क्रम correct fileप्रणाली operation.
 * This macro checks अगर a certain field fits in the inode. Note that
 * inode-size = GOOD_OLD_INODE_SIZE + i_extra_isize
 */
#घोषणा EXT4_FITS_IN_INODE(ext4_inode, einode, field)	\
	((दुरत्व(typeof(*ext4_inode), field) +	\
	  माप((ext4_inode)->field))			\
	<= (EXT4_GOOD_OLD_INODE_SIZE +			\
	    (einode)->i_extra_isize))			\

/*
 * We use an encoding that preserves the बार क्रम extra epoch "00":
 *
 * extra  msb of                         adjust क्रम चिन्हित
 * epoch  32-bit                         32-bit tv_sec to
 * bits   समय    decoded 64-bit tv_sec  64-bit tv_sec      valid समय range
 * 0 0    1    -0x80000000..-0x00000001  0x000000000 1901-12-13..1969-12-31
 * 0 0    0    0x000000000..0x07fffffff  0x000000000 1970-01-01..2038-01-19
 * 0 1    1    0x080000000..0x0ffffffff  0x100000000 2038-01-19..2106-02-07
 * 0 1    0    0x100000000..0x17fffffff  0x100000000 2106-02-07..2174-02-25
 * 1 0    1    0x180000000..0x1ffffffff  0x200000000 2174-02-25..2242-03-16
 * 1 0    0    0x200000000..0x27fffffff  0x200000000 2242-03-16..2310-04-04
 * 1 1    1    0x280000000..0x2ffffffff  0x300000000 2310-04-04..2378-04-22
 * 1 1    0    0x300000000..0x37fffffff  0x300000000 2378-04-22..2446-05-10
 *
 * Note that previous versions of the kernel on 64-bit प्रणालीs would
 * incorrectly use extra epoch bits 1,1 क्रम dates between 1901 and
 * 1970.  e2fsck will correct this, assuming that it is run on the
 * affected fileप्रणाली beक्रमe 2242.
 */

अटल अंतरभूत __le32 ext4_encode_extra_समय(काष्ठा बारpec64 *समय)
अणु
	u32 extra =((समय->tv_sec - (s32)समय->tv_sec) >> 32) & EXT4_EPOCH_MASK;
	वापस cpu_to_le32(extra | (समय->tv_nsec << EXT4_EPOCH_BITS));
पूर्ण

अटल अंतरभूत व्योम ext4_decode_extra_समय(काष्ठा बारpec64 *समय,
					  __le32 extra)
अणु
	अगर (unlikely(extra & cpu_to_le32(EXT4_EPOCH_MASK)))
		समय->tv_sec += (u64)(le32_to_cpu(extra) & EXT4_EPOCH_MASK) << 32;
	समय->tv_nsec = (le32_to_cpu(extra) & EXT4_NSEC_MASK) >> EXT4_EPOCH_BITS;
पूर्ण

#घोषणा EXT4_INODE_SET_XTIME(xसमय, inode, raw_inode)				\
करो अणु										\
	अगर (EXT4_FITS_IN_INODE(raw_inode, EXT4_I(inode), xसमय ## _extra))     अणु\
		(raw_inode)->xसमय = cpu_to_le32((inode)->xसमय.tv_sec);	\
		(raw_inode)->xसमय ## _extra =					\
				ext4_encode_extra_समय(&(inode)->xसमय);	\
		पूर्ण								\
	अन्यथा	\
		(raw_inode)->xसमय = cpu_to_le32(clamp_t(पूर्णांक32_t, (inode)->xसमय.tv_sec, S32_MIN, S32_MAX));	\
पूर्ण जबतक (0)

#घोषणा EXT4_EINODE_SET_XTIME(xसमय, einode, raw_inode)			       \
करो अणु									       \
	अगर (EXT4_FITS_IN_INODE(raw_inode, einode, xसमय))		       \
		(raw_inode)->xसमय = cpu_to_le32((einode)->xसमय.tv_sec);      \
	अगर (EXT4_FITS_IN_INODE(raw_inode, einode, xसमय ## _extra))	       \
		(raw_inode)->xसमय ## _extra =				       \
				ext4_encode_extra_समय(&(einode)->xसमय);      \
पूर्ण जबतक (0)

#घोषणा EXT4_INODE_GET_XTIME(xसमय, inode, raw_inode)				\
करो अणु										\
	(inode)->xसमय.tv_sec = (चिन्हित)le32_to_cpu((raw_inode)->xसमय);	\
	अगर (EXT4_FITS_IN_INODE(raw_inode, EXT4_I(inode), xसमय ## _extra)) अणु	\
		ext4_decode_extra_समय(&(inode)->xसमय,				\
				       raw_inode->xसमय ## _extra);		\
		पूर्ण								\
	अन्यथा									\
		(inode)->xसमय.tv_nsec = 0;					\
पूर्ण जबतक (0)


#घोषणा EXT4_EINODE_GET_XTIME(xसमय, einode, raw_inode)			       \
करो अणु									       \
	अगर (EXT4_FITS_IN_INODE(raw_inode, einode, xसमय))		       \
		(einode)->xसमय.tv_sec = 				       \
			(चिन्हित)le32_to_cpu((raw_inode)->xसमय);	       \
	अन्यथा								       \
		(einode)->xसमय.tv_sec = 0;				       \
	अगर (EXT4_FITS_IN_INODE(raw_inode, einode, xसमय ## _extra))	       \
		ext4_decode_extra_समय(&(einode)->xसमय,		       \
				       raw_inode->xसमय ## _extra);	       \
	अन्यथा								       \
		(einode)->xसमय.tv_nsec = 0;				       \
पूर्ण जबतक (0)

#घोषणा i_disk_version osd1.linux1.l_i_version

#अगर defined(__KERNEL__) || defined(__linux__)
#घोषणा i_reserved1	osd1.linux1.l_i_reserved1
#घोषणा i_file_acl_high	osd2.linux2.l_i_file_acl_high
#घोषणा i_blocks_high	osd2.linux2.l_i_blocks_high
#घोषणा i_uid_low	i_uid
#घोषणा i_gid_low	i_gid
#घोषणा i_uid_high	osd2.linux2.l_i_uid_high
#घोषणा i_gid_high	osd2.linux2.l_i_gid_high
#घोषणा i_checksum_lo	osd2.linux2.l_i_checksum_lo

#या_अगर defined(__GNU__)

#घोषणा i_translator	osd1.hurd1.h_i_translator
#घोषणा i_uid_high	osd2.hurd2.h_i_uid_high
#घोषणा i_gid_high	osd2.hurd2.h_i_gid_high
#घोषणा i_author	osd2.hurd2.h_i_author

#या_अगर defined(__masix__)

#घोषणा i_reserved1	osd1.masix1.m_i_reserved1
#घोषणा i_file_acl_high	osd2.masix2.m_i_file_acl_high
#घोषणा i_reserved2	osd2.masix2.m_i_reserved2

#पूर्ण_अगर /* defined(__KERNEL__) || defined(__linux__) */

#समावेश "extents_status.h"
#समावेश "fast_commit.h"

/*
 * Lock subclasses क्रम i_data_sem in the ext4_inode_info काष्ठाure.
 *
 * These are needed to aव्योम lockdep false positives when we need to
 * allocate blocks to the quota inode during ext4_map_blocks(), जबतक
 * holding i_data_sem क्रम a normal (non-quota) inode.  Since we करोn't
 * करो quota tracking क्रम the quota inode, this aव्योमs deadlock (as
 * well as infinite recursion, since it isn't turtles all the way
 * करोwn...)
 *
 *  I_DATA_SEM_NORMAL - Used क्रम most inodes
 *  I_DATA_SEM_OTHER  - Used by move_inode.c क्रम the second normal inode
 *			  where the second inode has larger inode number
 *			  than the first
 *  I_DATA_SEM_QUOTA  - Used क्रम quota inodes only
 */
क्रमागत अणु
	I_DATA_SEM_NORMAL = 0,
	I_DATA_SEM_OTHER,
	I_DATA_SEM_QUOTA,
पूर्ण;


/*
 * fourth extended file प्रणाली inode data in memory
 */
काष्ठा ext4_inode_info अणु
	__le32	i_data[15];	/* unconverted */
	__u32	i_dसमय;
	ext4_fsblk_t	i_file_acl;

	/*
	 * i_block_group is the number of the block group which contains
	 * this file's inode.  Constant across the lअगरeसमय of the inode,
	 * it is used क्रम making block allocation decisions - we try to
	 * place a file's data blocks near its inode block, and new inodes
	 * near to their parent directory's inode.
	 */
	ext4_group_t	i_block_group;
	ext4_lblk_t	i_dir_start_lookup;
#अगर (BITS_PER_LONG < 64)
	अचिन्हित दीर्घ	i_state_flags;		/* Dynamic state flags */
#पूर्ण_अगर
	अचिन्हित दीर्घ	i_flags;

	/*
	 * Extended attributes can be पढ़ो independently of the मुख्य file
	 * data. Taking i_mutex even when पढ़ोing would cause contention
	 * between पढ़ोers of EAs and ग_लिखोrs of regular file data, so
	 * instead we synchronize on xattr_sem when पढ़ोing or changing
	 * EAs.
	 */
	काष्ठा rw_semaphore xattr_sem;

	काष्ठा list_head i_orphan;	/* unlinked but खोलो inodes */

	/* Fast commit related info */

	काष्ठा list_head i_fc_list;	/*
					 * inodes that need fast commit
					 * रक्षित by sbi->s_fc_lock.
					 */

	/* Start of lblk range that needs to be committed in this fast commit */
	ext4_lblk_t i_fc_lblk_start;

	/* End of lblk range that needs to be committed in this fast commit */
	ext4_lblk_t i_fc_lblk_len;

	/* Number of ongoing updates on this inode */
	atomic_t  i_fc_updates;

	/* Fast commit रुको queue क्रम this inode */
	रुको_queue_head_t i_fc_रुको;

	/* Protect concurrent accesses on i_fc_lblk_start, i_fc_lblk_len */
	काष्ठा mutex i_fc_lock;

	/*
	 * i_disksize keeps track of what the inode size is ON DISK, not
	 * in memory.  During truncate, i_size is set to the new size by
	 * the VFS prior to calling ext4_truncate(), but the fileप्रणाली won't
	 * set i_disksize to 0 until the truncate is actually under way.
	 *
	 * The पूर्णांकent is that i_disksize always represents the blocks which
	 * are used by this file.  This allows recovery to restart truncate
	 * on orphans अगर we crash during truncate.  We actually ग_लिखो i_disksize
	 * पूर्णांकo the on-disk inode when writing inodes out, instead of i_size.
	 *
	 * The only समय when i_disksize and i_size may be dअगरferent is when
	 * a truncate is in progress.  The only things which change i_disksize
	 * are ext4_get_block (growth) and ext4_truncate (shrinkth).
	 */
	loff_t	i_disksize;

	/*
	 * i_data_sem is क्रम serialising ext4_truncate() against
	 * ext4_getblock().  In the 2.4 ext2 design, great chunks of inode's
	 * data tree are chopped off during truncate. We can't करो that in
	 * ext4 because whenever we perक्रमm पूर्णांकermediate commits during
	 * truncate, the inode and all the metadata blocks *must* be in a
	 * consistent state which allows truncation of the orphans to restart
	 * during recovery.  Hence we must fix the get_block-vs-truncate race
	 * by other means, so we have i_data_sem.
	 */
	काष्ठा rw_semaphore i_data_sem;
	/*
	 * i_mmap_sem is क्रम serializing page faults with truncate / punch hole
	 * operations. We have to make sure that new page cannot be faulted in
	 * a section of the inode that is being punched. We cannot easily use
	 * i_data_sem क्रम this since we need protection क्रम the whole punch
	 * operation and i_data_sem ranks below transaction start so we have
	 * to occasionally drop it.
	 */
	काष्ठा rw_semaphore i_mmap_sem;
	काष्ठा inode vfs_inode;
	काष्ठा jbd2_inode *jinode;

	spinlock_t i_raw_lock;	/* protects updates to the raw inode */

	/*
	 * File creation समय. Its function is same as that of
	 * काष्ठा बारpec64 i_अणुa,c,mपूर्णसमय in the generic inode.
	 */
	काष्ठा बारpec64 i_crसमय;

	/* mballoc */
	atomic_t i_pपुनः_स्मृति_active;
	काष्ठा list_head i_pपुनः_स्मृति_list;
	spinlock_t i_pपुनः_स्मृति_lock;

	/* extents status tree */
	काष्ठा ext4_es_tree i_es_tree;
	rwlock_t i_es_lock;
	काष्ठा list_head i_es_list;
	अचिन्हित पूर्णांक i_es_all_nr;	/* रक्षित by i_es_lock */
	अचिन्हित पूर्णांक i_es_shk_nr;	/* रक्षित by i_es_lock */
	ext4_lblk_t i_es_shrink_lblk;	/* Offset where we start searching क्रम
					   extents to shrink. Protected by
					   i_es_lock  */

	/* ialloc */
	ext4_group_t	i_last_alloc_group;

	/* allocation reservation info क्रम delalloc */
	/* In हाल of bigalloc, this refer to clusters rather than blocks */
	अचिन्हित पूर्णांक i_reserved_data_blocks;

	/* pending cluster reservations क्रम bigalloc file प्रणालीs */
	काष्ठा ext4_pending_tree i_pending_tree;

	/* on-disk additional length */
	__u16 i_extra_isize;

	/* Indicate the अंतरभूत data space. */
	u16 i_अंतरभूत_off;
	u16 i_अंतरभूत_size;

#अगर_घोषित CONFIG_QUOTA
	/* quota space reservation, managed पूर्णांकernally by quota code */
	qमाप_प्रकार i_reserved_quota;
#पूर्ण_अगर

	/* Lock protecting lists below */
	spinlock_t i_completed_io_lock;
	/*
	 * Completed IOs that need unwritten extents handling and have
	 * transaction reserved
	 */
	काष्ठा list_head i_rsv_conversion_list;
	काष्ठा work_काष्ठा i_rsv_conversion_work;
	atomic_t i_unwritten; /* Nr. of inflight conversions pending */

	spinlock_t i_block_reservation_lock;

	/*
	 * Transactions that contain inode's metadata needed to complete
	 * fsync and fdatasync, respectively.
	 */
	tid_t i_sync_tid;
	tid_t i_datasync_tid;

#अगर_घोषित CONFIG_QUOTA
	काष्ठा dquot *i_dquot[MAXQUOTAS];
#पूर्ण_अगर

	/* Precomputed uuid+inum+igen checksum क्रम seeding inode checksums */
	__u32 i_csum_seed;

	kprojid_t i_projid;
पूर्ण;

/*
 * File प्रणाली states
 */
#घोषणा	EXT4_VALID_FS			0x0001	/* Unmounted cleanly */
#घोषणा	EXT4_ERROR_FS			0x0002	/* Errors detected */
#घोषणा	EXT4_ORPHAN_FS			0x0004	/* Orphans being recovered */
#घोषणा EXT4_FC_REPLAY			0x0020	/* Fast commit replay ongoing */

/*
 * Misc. fileप्रणाली flags
 */
#घोषणा EXT2_FLAGS_SIGNED_HASH		0x0001  /* Signed dirhash in use */
#घोषणा EXT2_FLAGS_UNSIGNED_HASH	0x0002  /* Unचिन्हित dirhash in use */
#घोषणा EXT2_FLAGS_TEST_खाताSYS		0x0004	/* to test development code */

/*
 * Mount flags set via mount options or शेषs
 */
#घोषणा EXT4_MOUNT_NO_MBCACHE		0x00001 /* Do not use mbcache */
#घोषणा EXT4_MOUNT_GRPID		0x00004	/* Create files with directory's group */
#घोषणा EXT4_MOUNT_DEBUG		0x00008	/* Some debugging messages */
#घोषणा EXT4_MOUNT_ERRORS_CONT		0x00010	/* Continue on errors */
#घोषणा EXT4_MOUNT_ERRORS_RO		0x00020	/* Remount fs ro on errors */
#घोषणा EXT4_MOUNT_ERRORS_PANIC		0x00040	/* Panic on errors */
#घोषणा EXT4_MOUNT_ERRORS_MASK		0x00070
#घोषणा EXT4_MOUNT_MINIX_DF		0x00080	/* Mimics the Minix statfs */
#घोषणा EXT4_MOUNT_NOLOAD		0x00100	/* Don't use existing journal*/
#अगर_घोषित CONFIG_FS_DAX
#घोषणा EXT4_MOUNT_DAX_ALWAYS		0x00200	/* Direct Access */
#अन्यथा
#घोषणा EXT4_MOUNT_DAX_ALWAYS		0
#पूर्ण_अगर
#घोषणा EXT4_MOUNT_DATA_FLAGS		0x00C00	/* Mode क्रम data ग_लिखोs: */
#घोषणा EXT4_MOUNT_JOURNAL_DATA		0x00400	/* Write data to journal */
#घोषणा EXT4_MOUNT_ORDERED_DATA		0x00800	/* Flush data beक्रमe commit */
#घोषणा EXT4_MOUNT_WRITEBACK_DATA	0x00C00	/* No data ordering */
#घोषणा EXT4_MOUNT_UPDATE_JOURNAL	0x01000	/* Update the journal क्रमmat */
#घोषणा EXT4_MOUNT_NO_UID32		0x02000  /* Disable 32-bit UIDs */
#घोषणा EXT4_MOUNT_XATTR_USER		0x04000	/* Extended user attributes */
#घोषणा EXT4_MOUNT_POSIX_ACL		0x08000	/* POSIX Access Control Lists */
#घोषणा EXT4_MOUNT_NO_AUTO_DA_ALLOC	0x10000	/* No स्वतः delalloc mapping */
#घोषणा EXT4_MOUNT_BARRIER		0x20000 /* Use block barriers */
#घोषणा EXT4_MOUNT_QUOTA		0x40000 /* Some quota option set */
#घोषणा EXT4_MOUNT_USRQUOTA		0x80000 /* "old" user quota,
						 * enable enक्रमcement क्रम hidden
						 * quota files */
#घोषणा EXT4_MOUNT_GRPQUOTA		0x100000 /* "old" group quota, enable
						  * enक्रमcement क्रम hidden quota
						  * files */
#घोषणा EXT4_MOUNT_PRJQUOTA		0x200000 /* Enable project quota
						  * enक्रमcement */
#घोषणा EXT4_MOUNT_DIOREAD_NOLOCK	0x400000 /* Enable support क्रम dio पढ़ो nolocking */
#घोषणा EXT4_MOUNT_JOURNAL_CHECKSUM	0x800000 /* Journal checksums */
#घोषणा EXT4_MOUNT_JOURNAL_ASYNC_COMMIT	0x1000000 /* Journal Async Commit */
#घोषणा EXT4_MOUNT_WARN_ON_ERROR	0x2000000 /* Trigger WARN_ON on error */
#घोषणा EXT4_MOUNT_NO_PREFETCH_BLOCK_BITMAPS 0x4000000
#घोषणा EXT4_MOUNT_DELALLOC		0x8000000 /* Delalloc support */
#घोषणा EXT4_MOUNT_DATA_ERR_ABORT	0x10000000 /* Abort on file data ग_लिखो */
#घोषणा EXT4_MOUNT_BLOCK_VALIDITY	0x20000000 /* Block validity checking */
#घोषणा EXT4_MOUNT_DISCARD		0x40000000 /* Issue DISCARD requests */
#घोषणा EXT4_MOUNT_INIT_INODE_TABLE	0x80000000 /* Initialize uninitialized itables */

/*
 * Mount flags set either स्वतःmatically (could not be set by mount option)
 * based on per file प्रणाली feature or property or in special हालs such as
 * distinguishing between explicit mount option definition and शेष.
 */
#घोषणा EXT4_MOUNT2_EXPLICIT_DELALLOC	0x00000001 /* User explicitly
						      specअगरied delalloc */
#घोषणा EXT4_MOUNT2_STD_GROUP_SIZE	0x00000002 /* We have standard group
						      size of blocksize * 8
						      blocks */
#घोषणा EXT4_MOUNT2_HURD_COMPAT		0x00000004 /* Support HURD-castrated
						      file प्रणालीs */
#घोषणा EXT4_MOUNT2_EXPLICIT_JOURNAL_CHECKSUM	0x00000008 /* User explicitly
						specअगरied journal checksum */

#घोषणा EXT4_MOUNT2_JOURNAL_FAST_COMMIT	0x00000010 /* Journal fast commit */
#घोषणा EXT4_MOUNT2_DAX_NEVER		0x00000020 /* Do not allow Direct Access */
#घोषणा EXT4_MOUNT2_DAX_INODE		0x00000040 /* For prपूर्णांकing options only */
#घोषणा EXT4_MOUNT2_MB_OPTIMIZE_SCAN	0x00000080 /* Optimize group
						    * scanning in mballoc
						    */

#घोषणा clear_opt(sb, opt)		EXT4_SB(sb)->s_mount_opt &= \
						~EXT4_MOUNT_##opt
#घोषणा set_opt(sb, opt)		EXT4_SB(sb)->s_mount_opt |= \
						EXT4_MOUNT_##opt
#घोषणा test_opt(sb, opt)		(EXT4_SB(sb)->s_mount_opt & \
					 EXT4_MOUNT_##opt)

#घोषणा clear_opt2(sb, opt)		EXT4_SB(sb)->s_mount_opt2 &= \
						~EXT4_MOUNT2_##opt
#घोषणा set_opt2(sb, opt)		EXT4_SB(sb)->s_mount_opt2 |= \
						EXT4_MOUNT2_##opt
#घोषणा test_opt2(sb, opt)		(EXT4_SB(sb)->s_mount_opt2 & \
					 EXT4_MOUNT2_##opt)

#घोषणा ext4_test_and_set_bit		__test_and_set_bit_le
#घोषणा ext4_set_bit			__set_bit_le
#घोषणा ext4_set_bit_atomic		ext2_set_bit_atomic
#घोषणा ext4_test_and_clear_bit		__test_and_clear_bit_le
#घोषणा ext4_clear_bit			__clear_bit_le
#घोषणा ext4_clear_bit_atomic		ext2_clear_bit_atomic
#घोषणा ext4_test_bit			test_bit_le
#घोषणा ext4_find_next_zero_bit		find_next_zero_bit_le
#घोषणा ext4_find_next_bit		find_next_bit_le

बाह्य व्योम ext4_set_bits(व्योम *bm, पूर्णांक cur, पूर्णांक len);

/*
 * Maximal mount counts between two fileप्रणाली checks
 */
#घोषणा EXT4_DFL_MAX_MNT_COUNT		20	/* Allow 20 mounts */
#घोषणा EXT4_DFL_CHECKINTERVAL		0	/* Don't use पूर्णांकerval check */

/*
 * Behaviour when detecting errors
 */
#घोषणा EXT4_ERRORS_CONTINUE		1	/* Continue execution */
#घोषणा EXT4_ERRORS_RO			2	/* Remount fs पढ़ो-only */
#घोषणा EXT4_ERRORS_PANIC		3	/* Panic */
#घोषणा EXT4_ERRORS_DEFAULT		EXT4_ERRORS_CONTINUE

/* Metadata checksum algorithm codes */
#घोषणा EXT4_CRC32C_CHKSUM		1

/*
 * Structure of the super block
 */
काष्ठा ext4_super_block अणु
/*00*/	__le32	s_inodes_count;		/* Inodes count */
	__le32	s_blocks_count_lo;	/* Blocks count */
	__le32	s_r_blocks_count_lo;	/* Reserved blocks count */
	__le32	s_मुक्त_blocks_count_lo;	/* Free blocks count */
/*10*/	__le32	s_मुक्त_inodes_count;	/* Free inodes count */
	__le32	s_first_data_block;	/* First Data Block */
	__le32	s_log_block_size;	/* Block size */
	__le32	s_log_cluster_size;	/* Allocation cluster size */
/*20*/	__le32	s_blocks_per_group;	/* # Blocks per group */
	__le32	s_clusters_per_group;	/* # Clusters per group */
	__le32	s_inodes_per_group;	/* # Inodes per group */
	__le32	s_mसमय;		/* Mount समय */
/*30*/	__le32	s_wसमय;		/* Write समय */
	__le16	s_mnt_count;		/* Mount count */
	__le16	s_max_mnt_count;	/* Maximal mount count */
	__le16	s_magic;		/* Magic signature */
	__le16	s_state;		/* File प्रणाली state */
	__le16	s_errors;		/* Behaviour when detecting errors */
	__le16	s_minor_rev_level;	/* minor revision level */
/*40*/	__le32	s_lastcheck;		/* समय of last check */
	__le32	s_checkपूर्णांकerval;	/* max. समय between checks */
	__le32	s_creator_os;		/* OS */
	__le32	s_rev_level;		/* Revision level */
/*50*/	__le16	s_def_resuid;		/* Default uid क्रम reserved blocks */
	__le16	s_def_resgid;		/* Default gid क्रम reserved blocks */
	/*
	 * These fields are क्रम EXT4_DYNAMIC_REV superblocks only.
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
	__le32	s_first_ino;		/* First non-reserved inode */
	__le16  s_inode_size;		/* size of inode काष्ठाure */
	__le16	s_block_group_nr;	/* block group # of this superblock */
	__le32	s_feature_compat;	/* compatible feature set */
/*60*/	__le32	s_feature_incompat;	/* incompatible feature set */
	__le32	s_feature_ro_compat;	/* पढ़ोonly-compatible feature set */
/*68*/	__u8	s_uuid[16];		/* 128-bit uuid क्रम volume */
/*78*/	अक्षर	s_volume_name[16];	/* volume name */
/*88*/	अक्षर	s_last_mounted[64] __nonstring;	/* directory where last mounted */
/*C8*/	__le32	s_algorithm_usage_biपंचांगap; /* For compression */
	/*
	 * Perक्रमmance hपूर्णांकs.  Directory pपुनः_स्मृतिation should only
	 * happen अगर the EXT4_FEATURE_COMPAT_सूची_PREALLOC flag is on.
	 */
	__u8	s_pपुनः_स्मृति_blocks;	/* Nr of blocks to try to pपुनः_स्मृतिate*/
	__u8	s_pपुनः_स्मृति_dir_blocks;	/* Nr to pपुनः_स्मृतिate क्रम dirs */
	__le16	s_reserved_gdt_blocks;	/* Per group desc क्रम online growth */
	/*
	 * Journaling support valid अगर EXT4_FEATURE_COMPAT_HAS_JOURNAL set.
	 */
/*D0*/	__u8	s_journal_uuid[16];	/* uuid of journal superblock */
/*E0*/	__le32	s_journal_inum;		/* inode number of journal file */
	__le32	s_journal_dev;		/* device number of journal file */
	__le32	s_last_orphan;		/* start of list of inodes to delete */
	__le32	s_hash_seed[4];		/* HTREE hash seed */
	__u8	s_def_hash_version;	/* Default hash version to use */
	__u8	s_jnl_backup_type;
	__le16  s_desc_size;		/* size of group descriptor */
/*100*/	__le32	s_शेष_mount_opts;
	__le32	s_first_meta_bg;	/* First metablock block group */
	__le32	s_mkfs_समय;		/* When the fileप्रणाली was created */
	__le32	s_jnl_blocks[17];	/* Backup of the journal inode */
	/* 64bit support valid अगर EXT4_FEATURE_COMPAT_64BIT */
/*150*/	__le32	s_blocks_count_hi;	/* Blocks count */
	__le32	s_r_blocks_count_hi;	/* Reserved blocks count */
	__le32	s_मुक्त_blocks_count_hi;	/* Free blocks count */
	__le16	s_min_extra_isize;	/* All inodes have at least # bytes */
	__le16	s_want_extra_isize; 	/* New inodes should reserve # bytes */
	__le32	s_flags;		/* Miscellaneous flags */
	__le16  s_raid_stride;		/* RAID stride */
	__le16  s_mmp_update_पूर्णांकerval;  /* # seconds to रुको in MMP checking */
	__le64  s_mmp_block;            /* Block क्रम multi-mount protection */
	__le32  s_raid_stripe_width;    /* blocks on all data disks (N*stride)*/
	__u8	s_log_groups_per_flex;  /* FLEX_BG group size */
	__u8	s_checksum_type;	/* metadata checksum algorithm used */
	__u8	s_encryption_level;	/* versioning level क्रम encryption */
	__u8	s_reserved_pad;		/* Padding to next 32bits */
	__le64	s_kbytes_written;	/* nr of lअगरeसमय kilobytes written */
	__le32	s_snapshot_inum;	/* Inode number of active snapshot */
	__le32	s_snapshot_id;		/* sequential ID of active snapshot */
	__le64	s_snapshot_r_blocks_count; /* reserved blocks क्रम active
					      snapshot's future use */
	__le32	s_snapshot_list;	/* inode number of the head of the
					   on-disk snapshot list */
#घोषणा EXT4_S_ERR_START दुरत्व(काष्ठा ext4_super_block, s_error_count)
	__le32	s_error_count;		/* number of fs errors */
	__le32	s_first_error_समय;	/* first समय an error happened */
	__le32	s_first_error_ino;	/* inode involved in first error */
	__le64	s_first_error_block;	/* block involved of first error */
	__u8	s_first_error_func[32] __nonstring;	/* function where the error happened */
	__le32	s_first_error_line;	/* line number where error happened */
	__le32	s_last_error_समय;	/* most recent समय of an error */
	__le32	s_last_error_ino;	/* inode involved in last error */
	__le32	s_last_error_line;	/* line number where error happened */
	__le64	s_last_error_block;	/* block involved of last error */
	__u8	s_last_error_func[32] __nonstring;	/* function where the error happened */
#घोषणा EXT4_S_ERR_END दुरत्व(काष्ठा ext4_super_block, s_mount_opts)
	__u8	s_mount_opts[64];
	__le32	s_usr_quota_inum;	/* inode क्रम tracking user quota */
	__le32	s_grp_quota_inum;	/* inode क्रम tracking group quota */
	__le32	s_overhead_clusters;	/* overhead blocks/clusters in fs */
	__le32	s_backup_bgs[2];	/* groups with sparse_super2 SBs */
	__u8	s_encrypt_algos[4];	/* Encryption algorithms in use  */
	__u8	s_encrypt_pw_salt[16];	/* Salt used क्रम string2key algorithm */
	__le32	s_lpf_ino;		/* Location of the lost+found inode */
	__le32	s_prj_quota_inum;	/* inode क्रम tracking project quota */
	__le32	s_checksum_seed;	/* crc32c(uuid) अगर csum_seed set */
	__u8	s_wसमय_hi;
	__u8	s_mसमय_hi;
	__u8	s_mkfs_समय_hi;
	__u8	s_lastcheck_hi;
	__u8	s_first_error_समय_hi;
	__u8	s_last_error_समय_hi;
	__u8	s_first_error_errcode;
	__u8    s_last_error_errcode;
	__le16  s_encoding;		/* Filename अक्षरset encoding */
	__le16  s_encoding_flags;	/* Filename अक्षरset encoding flags */
	__le32	s_reserved[95];		/* Padding to the end of the block */
	__le32	s_checksum;		/* crc32c(superblock) */
पूर्ण;

#घोषणा EXT4_S_ERR_LEN (EXT4_S_ERR_END - EXT4_S_ERR_START)

#अगर_घोषित __KERNEL__

#अगर_घोषित CONFIG_FS_ENCRYPTION
#घोषणा DUMMY_ENCRYPTION_ENABLED(sbi) ((sbi)->s_dummy_enc_policy.policy != शून्य)
#अन्यथा
#घोषणा DUMMY_ENCRYPTION_ENABLED(sbi) (0)
#पूर्ण_अगर

/* Number of quota types we support */
#घोषणा EXT4_MAXQUOTAS 3

#घोषणा EXT4_ENC_UTF8_12_1	1

/*
 * fourth extended-fs super-block data in memory
 */
काष्ठा ext4_sb_info अणु
	अचिन्हित दीर्घ s_desc_size;	/* Size of a group descriptor in bytes */
	अचिन्हित दीर्घ s_inodes_per_block;/* Number of inodes per block */
	अचिन्हित दीर्घ s_blocks_per_group;/* Number of blocks in a group */
	अचिन्हित दीर्घ s_clusters_per_group; /* Number of clusters in a group */
	अचिन्हित दीर्घ s_inodes_per_group;/* Number of inodes in a group */
	अचिन्हित दीर्घ s_itb_per_group;	/* Number of inode table blocks per group */
	अचिन्हित दीर्घ s_gdb_count;	/* Number of group descriptor blocks */
	अचिन्हित दीर्घ s_desc_per_block;	/* Number of group descriptors per block */
	ext4_group_t s_groups_count;	/* Number of groups in the fs */
	ext4_group_t s_blockfile_groups;/* Groups acceptable क्रम non-extent files */
	अचिन्हित दीर्घ s_overhead;  /* # of fs overhead clusters */
	अचिन्हित पूर्णांक s_cluster_ratio;	/* Number of blocks per cluster */
	अचिन्हित पूर्णांक s_cluster_bits;	/* log2 of s_cluster_ratio */
	loff_t s_biपंचांगap_maxbytes;	/* max bytes क्रम biपंचांगap files */
	काष्ठा buffer_head * s_sbh;	/* Buffer containing the super block */
	काष्ठा ext4_super_block *s_es;	/* Poपूर्णांकer to the super block in the buffer */
	काष्ठा buffer_head * __rcu *s_group_desc;
	अचिन्हित पूर्णांक s_mount_opt;
	अचिन्हित पूर्णांक s_mount_opt2;
	अचिन्हित दीर्घ s_mount_flags;
	अचिन्हित पूर्णांक s_def_mount_opt;
	ext4_fsblk_t s_sb_block;
	atomic64_t s_resv_clusters;
	kuid_t s_resuid;
	kgid_t s_resgid;
	अचिन्हित लघु s_mount_state;
	अचिन्हित लघु s_pad;
	पूर्णांक s_addr_per_block_bits;
	पूर्णांक s_desc_per_block_bits;
	पूर्णांक s_inode_size;
	पूर्णांक s_first_ino;
	अचिन्हित पूर्णांक s_inode_पढ़ोahead_blks;
	अचिन्हित पूर्णांक s_inode_goal;
	u32 s_hash_seed[4];
	पूर्णांक s_def_hash_version;
	पूर्णांक s_hash_अचिन्हित;	/* 3 अगर hash should be चिन्हित, 0 अगर not */
	काष्ठा percpu_counter s_मुक्तclusters_counter;
	काष्ठा percpu_counter s_मुक्तinodes_counter;
	काष्ठा percpu_counter s_dirs_counter;
	काष्ठा percpu_counter s_dirtyclusters_counter;
	काष्ठा percpu_counter s_sra_exceeded_retry_limit;
	काष्ठा blockgroup_lock *s_blockgroup_lock;
	काष्ठा proc_dir_entry *s_proc;
	काष्ठा kobject s_kobj;
	काष्ठा completion s_kobj_unरेजिस्टर;
	काष्ठा super_block *s_sb;

	/* Journaling */
	काष्ठा journal_s *s_journal;
	काष्ठा list_head s_orphan;
	काष्ठा mutex s_orphan_lock;
	अचिन्हित दीर्घ s_ext4_flags;		/* Ext4 superblock flags */
	अचिन्हित दीर्घ s_commit_पूर्णांकerval;
	u32 s_max_batch_समय;
	u32 s_min_batch_समय;
	काष्ठा block_device *s_journal_bdev;
#अगर_घोषित CONFIG_QUOTA
	/* Names of quota files with journalled quota */
	अक्षर __rcu *s_qf_names[EXT4_MAXQUOTAS];
	पूर्णांक s_jquota_fmt;			/* Format of quota to use */
#पूर्ण_अगर
	अचिन्हित पूर्णांक s_want_extra_isize; /* New inodes should reserve # bytes */
	काष्ठा ext4_प्रणाली_blocks __rcu *s_प्रणाली_blks;

#अगर_घोषित EXTENTS_STATS
	/* ext4 extents stats */
	अचिन्हित दीर्घ s_ext_min;
	अचिन्हित दीर्घ s_ext_max;
	अचिन्हित दीर्घ s_depth_max;
	spinlock_t s_ext_stats_lock;
	अचिन्हित दीर्घ s_ext_blocks;
	अचिन्हित दीर्घ s_ext_extents;
#पूर्ण_अगर

	/* क्रम buddy allocator */
	काष्ठा ext4_group_info ** __rcu *s_group_info;
	काष्ठा inode *s_buddy_cache;
	spinlock_t s_md_lock;
	अचिन्हित लघु *s_mb_offsets;
	अचिन्हित पूर्णांक *s_mb_maxs;
	अचिन्हित पूर्णांक s_group_info_size;
	अचिन्हित पूर्णांक s_mb_मुक्त_pending;
	काष्ठा list_head s_मुक्तd_data_list;	/* List of blocks to be मुक्तd
						   after commit completed */
	काष्ठा rb_root s_mb_avg_fragment_size_root;
	rwlock_t s_mb_rb_lock;
	काष्ठा list_head *s_mb_largest_मुक्त_orders;
	rwlock_t *s_mb_largest_मुक्त_orders_locks;

	/* tunables */
	अचिन्हित दीर्घ s_stripe;
	अचिन्हित पूर्णांक s_mb_max_linear_groups;
	अचिन्हित पूर्णांक s_mb_stream_request;
	अचिन्हित पूर्णांक s_mb_max_to_scan;
	अचिन्हित पूर्णांक s_mb_min_to_scan;
	अचिन्हित पूर्णांक s_mb_stats;
	अचिन्हित पूर्णांक s_mb_order2_reqs;
	अचिन्हित पूर्णांक s_mb_group_pपुनः_स्मृति;
	अचिन्हित पूर्णांक s_mb_max_inode_pपुनः_स्मृति;
	अचिन्हित पूर्णांक s_max_dir_size_kb;
	/* where last allocation was करोne - क्रम stream allocation */
	अचिन्हित दीर्घ s_mb_last_group;
	अचिन्हित दीर्घ s_mb_last_start;
	अचिन्हित पूर्णांक s_mb_prefetch;
	अचिन्हित पूर्णांक s_mb_prefetch_limit;

	/* stats क्रम buddy allocator */
	atomic_t s_bal_reqs;	/* number of reqs with len > 1 */
	atomic_t s_bal_success;	/* we found दीर्घ enough chunks */
	atomic_t s_bal_allocated;	/* in blocks */
	atomic_t s_bal_ex_scanned;	/* total extents scanned */
	atomic_t s_bal_groups_scanned;	/* number of groups scanned */
	atomic_t s_bal_goals;	/* goal hits */
	atomic_t s_bal_अवरोधs;	/* too दीर्घ searches */
	atomic_t s_bal_2orders;	/* 2^order hits */
	atomic_t s_bal_cr0_bad_suggestions;
	atomic_t s_bal_cr1_bad_suggestions;
	atomic64_t s_bal_cX_groups_considered[4];
	atomic64_t s_bal_cX_hits[4];
	atomic64_t s_bal_cX_failed[4];		/* cX loop didn't find blocks */
	atomic_t s_mb_buddies_generated;	/* number of buddies generated */
	atomic64_t s_mb_generation_समय;
	atomic_t s_mb_lost_chunks;
	atomic_t s_mb_pपुनः_स्मृतिated;
	atomic_t s_mb_discarded;
	atomic_t s_lock_busy;

	/* locality groups */
	काष्ठा ext4_locality_group __percpu *s_locality_groups;

	/* क्रम ग_लिखो statistics */
	अचिन्हित दीर्घ s_sectors_written_start;
	u64 s_kbytes_written;

	/* the size of zero-out chunk */
	अचिन्हित पूर्णांक s_extent_max_zeroout_kb;

	अचिन्हित पूर्णांक s_log_groups_per_flex;
	काष्ठा flex_groups * __rcu *s_flex_groups;
	ext4_group_t s_flex_groups_allocated;

	/* workqueue क्रम reserved extent conversions (buffered io) */
	काष्ठा workqueue_काष्ठा *rsv_conversion_wq;

	/* समयr क्रम periodic error stats prपूर्णांकing */
	काष्ठा समयr_list s_err_report;

	/* Lazy inode table initialization info */
	काष्ठा ext4_li_request *s_li_request;
	/* Wait multiplier क्रम lazy initialization thपढ़ो */
	अचिन्हित पूर्णांक s_li_रुको_mult;

	/* Kernel thपढ़ो क्रम multiple mount protection */
	काष्ठा task_काष्ठा *s_mmp_tsk;

	/* record the last minlen when FITRIM is called. */
	atomic_t s_last_trim_minblks;

	/* Reference to checksum algorithm driver via cryptoapi */
	काष्ठा crypto_shash *s_chksum_driver;

	/* Precomputed FS UUID checksum क्रम seeding other checksums */
	__u32 s_csum_seed;

	/* Reclaim extents from extent status tree */
	काष्ठा shrinker s_es_shrinker;
	काष्ठा list_head s_es_list;	/* List of inodes with reclaimable extents */
	दीर्घ s_es_nr_inode;
	काष्ठा ext4_es_stats s_es_stats;
	काष्ठा mb_cache *s_ea_block_cache;
	काष्ठा mb_cache *s_ea_inode_cache;
	spinlock_t s_es_lock ____cacheline_aligned_in_smp;

	/* Ratelimit ext4 messages. */
	काष्ठा ratelimit_state s_err_ratelimit_state;
	काष्ठा ratelimit_state s_warning_ratelimit_state;
	काष्ठा ratelimit_state s_msg_ratelimit_state;
	atomic_t s_warning_count;
	atomic_t s_msg_count;

	/* Encryption policy क्रम '-o test_dummy_encryption' */
	काष्ठा fscrypt_dummy_policy s_dummy_enc_policy;

	/*
	 * Barrier between ग_लिखोpages ops and changing any inode's JOURNAL_DATA
	 * or EXTENTS flag.
	 */
	काष्ठा percpu_rw_semaphore s_ग_लिखोpages_rwsem;
	काष्ठा dax_device *s_daxdev;
#अगर_घोषित CONFIG_EXT4_DEBUG
	अचिन्हित दीर्घ s_simulate_fail;
#पूर्ण_अगर
	/* Record the errseq of the backing block device */
	errseq_t s_bdev_wb_err;
	spinlock_t s_bdev_wb_lock;

	/* Inक्रमmation about errors that happened during this mount */
	spinlock_t s_error_lock;
	पूर्णांक s_add_error_count;
	पूर्णांक s_first_error_code;
	__u32 s_first_error_line;
	__u32 s_first_error_ino;
	__u64 s_first_error_block;
	स्थिर अक्षर *s_first_error_func;
	समय64_t s_first_error_समय;
	पूर्णांक s_last_error_code;
	__u32 s_last_error_line;
	__u32 s_last_error_ino;
	__u64 s_last_error_block;
	स्थिर अक्षर *s_last_error_func;
	समय64_t s_last_error_समय;
	/*
	 * If we are in a context where we cannot update error inक्रमmation in
	 * the on-disk superblock, we queue this work to करो it.
	 */
	काष्ठा work_काष्ठा s_error_work;

	/* Ext4 fast commit stuff */
	atomic_t s_fc_subtid;
	atomic_t s_fc_ineligible_updates;
	/*
	 * After commit starts, the मुख्य queue माला_लो locked, and the further
	 * updates get added in the staging queue.
	 */
#घोषणा FC_Q_MAIN	0
#घोषणा FC_Q_STAGING	1
	काष्ठा list_head s_fc_q[2];	/* Inodes staged क्रम fast commit
					 * that have data changes in them.
					 */
	काष्ठा list_head s_fc_dentry_q[2];	/* directory entry updates */
	अचिन्हित पूर्णांक s_fc_bytes;
	/*
	 * Main fast commit lock. This lock protects accesses to the
	 * following fields:
	 * ei->i_fc_list, s_fc_dentry_q, s_fc_q, s_fc_bytes, s_fc_bh.
	 */
	spinlock_t s_fc_lock;
	काष्ठा buffer_head *s_fc_bh;
	काष्ठा ext4_fc_stats s_fc_stats;
	u64 s_fc_avg_commit_समय;
#अगर_घोषित CONFIG_EXT4_DEBUG
	पूर्णांक s_fc_debug_max_replay;
#पूर्ण_अगर
	काष्ठा ext4_fc_replay_state s_fc_replay_state;
पूर्ण;

अटल अंतरभूत काष्ठा ext4_sb_info *EXT4_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण
अटल अंतरभूत काष्ठा ext4_inode_info *EXT4_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा ext4_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_valid_inum(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	वापस ino == EXT4_ROOT_INO ||
		(ino >= EXT4_FIRST_INO(sb) &&
		 ino <= le32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count));
पूर्ण

/*
 * Returns: sbi->field[index]
 * Used to access an array element from the following sbi fields which require
 * rcu protection to aव्योम dereferencing an invalid poपूर्णांकer due to reassignment
 * - s_group_desc
 * - s_group_info
 * - s_flex_group
 */
#घोषणा sbi_array_rcu_deref(sbi, field, index)				   \
(अणु									   \
	typeof(*((sbi)->field)) _v;					   \
	rcu_पढ़ो_lock();						   \
	_v = ((typeof(_v)*)rcu_dereference((sbi)->field))[index];	   \
	rcu_पढ़ो_unlock();						   \
	_v;								   \
पूर्ण)

/*
 * run-समय mount flags
 */
क्रमागत अणु
	EXT4_MF_MNTसूची_SAMPLED,
	EXT4_MF_FS_ABORTED,	/* Fatal error detected */
	EXT4_MF_FC_INELIGIBLE,	/* Fast commit ineligible */
	EXT4_MF_FC_COMMITTING	/* File प्रणाली underoing a fast
				 * commit.
				 */
पूर्ण;

अटल अंतरभूत व्योम ext4_set_mount_flag(काष्ठा super_block *sb, पूर्णांक bit)
अणु
	set_bit(bit, &EXT4_SB(sb)->s_mount_flags);
पूर्ण

अटल अंतरभूत व्योम ext4_clear_mount_flag(काष्ठा super_block *sb, पूर्णांक bit)
अणु
	clear_bit(bit, &EXT4_SB(sb)->s_mount_flags);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_test_mount_flag(काष्ठा super_block *sb, पूर्णांक bit)
अणु
	वापस test_bit(bit, &EXT4_SB(sb)->s_mount_flags);
पूर्ण


/*
 * Simulate_fail codes
 */
#घोषणा EXT4_SIM_BBITMAP_EIO	1
#घोषणा EXT4_SIM_BBITMAP_CRC	2
#घोषणा EXT4_SIM_IBITMAP_EIO	3
#घोषणा EXT4_SIM_IBITMAP_CRC	4
#घोषणा EXT4_SIM_INODE_EIO	5
#घोषणा EXT4_SIM_INODE_CRC	6
#घोषणा EXT4_SIM_सूचीBLOCK_EIO	7
#घोषणा EXT4_SIM_सूचीBLOCK_CRC	8

अटल अंतरभूत bool ext4_simulate_fail(काष्ठा super_block *sb,
				     अचिन्हित दीर्घ code)
अणु
#अगर_घोषित CONFIG_EXT4_DEBUG
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (unlikely(sbi->s_simulate_fail == code)) अणु
		sbi->s_simulate_fail = 0;
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत व्योम ext4_simulate_fail_bh(काष्ठा super_block *sb,
					 काष्ठा buffer_head *bh,
					 अचिन्हित दीर्घ code)
अणु
	अगर (!IS_ERR(bh) && ext4_simulate_fail(sb, code))
		clear_buffer_uptodate(bh);
पूर्ण

/*
 * Error number codes क्रम s_अणुfirst,lastपूर्ण_error_त्रुटि_सं
 *
 * Linux त्रुटि_सं numbers are architecture specअगरic, so we need to translate
 * them पूर्णांकo something which is architecture independent.   We करोn't define
 * codes क्रम all त्रुटि_सं's; just the ones which are most likely to be the cause
 * of an ext4_error() call.
 */
#घोषणा EXT4_ERR_UNKNOWN	 1
#घोषणा EXT4_ERR_EIO		 2
#घोषणा EXT4_ERR_ENOMEM		 3
#घोषणा EXT4_ERR_EFSBADCRC	 4
#घोषणा EXT4_ERR_EFSCORRUPTED	 5
#घोषणा EXT4_ERR_ENOSPC		 6
#घोषणा EXT4_ERR_ENOKEY		 7
#घोषणा EXT4_ERR_EROFS		 8
#घोषणा EXT4_ERR_EFBIG		 9
#घोषणा EXT4_ERR_EEXIST		10
#घोषणा EXT4_ERR_दुस्फल		11
#घोषणा EXT4_ERR_EOVERFLOW	12
#घोषणा EXT4_ERR_EBUSY		13
#घोषणा EXT4_ERR_ENOTसूची	14
#घोषणा EXT4_ERR_ENOTEMPTY	15
#घोषणा EXT4_ERR_ESHUTDOWN	16
#घोषणा EXT4_ERR_EFAULT		17

/*
 * Inode dynamic state flags
 */
क्रमागत अणु
	EXT4_STATE_JDATA,		/* journaled data exists */
	EXT4_STATE_NEW,			/* inode is newly created */
	EXT4_STATE_XATTR,		/* has in-inode xattrs */
	EXT4_STATE_NO_EXPAND,		/* No space क्रम expansion */
	EXT4_STATE_DA_ALLOC_CLOSE,	/* Alloc DA blks on बंद */
	EXT4_STATE_EXT_MIGRATE,		/* Inode is migrating */
	EXT4_STATE_NEWENTRY,		/* File just added to dir */
	EXT4_STATE_MAY_INLINE_DATA,	/* may have in-inode data */
	EXT4_STATE_EXT_PRECACHED,	/* extents have been precached */
	EXT4_STATE_LUSTRE_EA_INODE,	/* Lustre-style ea_inode */
	EXT4_STATE_VERITY_IN_PROGRESS,	/* building fs-verity Merkle tree */
	EXT4_STATE_FC_COMMITTING,	/* Fast commit ongoing */
पूर्ण;

#घोषणा EXT4_INODE_BIT_FNS(name, field, offset)				\
अटल अंतरभूत पूर्णांक ext4_test_inode_##name(काष्ठा inode *inode, पूर्णांक bit)	\
अणु									\
	वापस test_bit(bit + (offset), &EXT4_I(inode)->i_##field);	\
पूर्ण									\
अटल अंतरभूत व्योम ext4_set_inode_##name(काष्ठा inode *inode, पूर्णांक bit)	\
अणु									\
	set_bit(bit + (offset), &EXT4_I(inode)->i_##field);		\
पूर्ण									\
अटल अंतरभूत व्योम ext4_clear_inode_##name(काष्ठा inode *inode, पूर्णांक bit) \
अणु									\
	clear_bit(bit + (offset), &EXT4_I(inode)->i_##field);		\
पूर्ण

/* Add these declarations here only so that these functions can be
 * found by name.  Otherwise, they are very hard to locate. */
अटल अंतरभूत पूर्णांक ext4_test_inode_flag(काष्ठा inode *inode, पूर्णांक bit);
अटल अंतरभूत व्योम ext4_set_inode_flag(काष्ठा inode *inode, पूर्णांक bit);
अटल अंतरभूत व्योम ext4_clear_inode_flag(काष्ठा inode *inode, पूर्णांक bit);
EXT4_INODE_BIT_FNS(flag, flags, 0)

/* Add these declarations here only so that these functions can be
 * found by name.  Otherwise, they are very hard to locate. */
अटल अंतरभूत पूर्णांक ext4_test_inode_state(काष्ठा inode *inode, पूर्णांक bit);
अटल अंतरभूत व्योम ext4_set_inode_state(काष्ठा inode *inode, पूर्णांक bit);
अटल अंतरभूत व्योम ext4_clear_inode_state(काष्ठा inode *inode, पूर्णांक bit);
#अगर (BITS_PER_LONG < 64)
EXT4_INODE_BIT_FNS(state, state_flags, 0)

अटल अंतरभूत व्योम ext4_clear_state_flags(काष्ठा ext4_inode_info *ei)
अणु
	(ei)->i_state_flags = 0;
पूर्ण
#अन्यथा
EXT4_INODE_BIT_FNS(state, flags, 32)

अटल अंतरभूत व्योम ext4_clear_state_flags(काष्ठा ext4_inode_info *ei)
अणु
	/* We depend on the fact that callers will set i_flags */
पूर्ण
#पूर्ण_अगर
#अन्यथा
/* Assume that user mode programs are passing in an ext4fs superblock, not
 * a kernel काष्ठा super_block.  This will allow us to call the feature-test
 * macros from user land. */
#घोषणा EXT4_SB(sb)	(sb)
#पूर्ण_अगर

अटल अंतरभूत bool ext4_verity_in_progress(काष्ठा inode *inode)
अणु
	वापस IS_ENABLED(CONFIG_FS_VERITY) &&
	       ext4_test_inode_state(inode, EXT4_STATE_VERITY_IN_PROGRESS);
पूर्ण

#घोषणा NEXT_ORPHAN(inode) EXT4_I(inode)->i_dसमय

/*
 * Codes क्रम operating प्रणालीs
 */
#घोषणा EXT4_OS_LINUX		0
#घोषणा EXT4_OS_HURD		1
#घोषणा EXT4_OS_MASIX		2
#घोषणा EXT4_OS_FREEBSD		3
#घोषणा EXT4_OS_LITES		4

/*
 * Revision levels
 */
#घोषणा EXT4_GOOD_OLD_REV	0	/* The good old (original) क्रमmat */
#घोषणा EXT4_DYNAMIC_REV	1	/* V2 क्रमmat w/ dynamic inode sizes */

#घोषणा EXT4_MAX_SUPP_REV	EXT4_DYNAMIC_REV

#घोषणा EXT4_GOOD_OLD_INODE_SIZE 128

#घोषणा EXT4_EXTRA_TIMESTAMP_MAX	(((s64)1 << 34) - 1  + S32_MIN)
#घोषणा EXT4_NON_EXTRA_TIMESTAMP_MAX	S32_MAX
#घोषणा EXT4_TIMESTAMP_MIN		S32_MIN

/*
 * Feature set definitions
 */

#घोषणा EXT4_FEATURE_COMPAT_सूची_PREALLOC	0x0001
#घोषणा EXT4_FEATURE_COMPAT_IMAGIC_INODES	0x0002
#घोषणा EXT4_FEATURE_COMPAT_HAS_JOURNAL		0x0004
#घोषणा EXT4_FEATURE_COMPAT_EXT_ATTR		0x0008
#घोषणा EXT4_FEATURE_COMPAT_RESIZE_INODE	0x0010
#घोषणा EXT4_FEATURE_COMPAT_सूची_INDEX		0x0020
#घोषणा EXT4_FEATURE_COMPAT_SPARSE_SUPER2	0x0200
/*
 * The reason why "FAST_COMMIT" is a compat feature is that, FS becomes
 * incompatible only अगर fast commit blocks are present in the FS. Since we
 * clear the journal (and thus the fast commit blocks), we करोn't mark FS as
 * incompatible. We also have a JBD2 incompat feature, which माला_लो set when
 * there are fast commit blocks present in the journal.
 */
#घोषणा EXT4_FEATURE_COMPAT_FAST_COMMIT		0x0400
#घोषणा EXT4_FEATURE_COMPAT_STABLE_INODES	0x0800

#घोषणा EXT4_FEATURE_RO_COMPAT_SPARSE_SUPER	0x0001
#घोषणा EXT4_FEATURE_RO_COMPAT_LARGE_खाता	0x0002
#घोषणा EXT4_FEATURE_RO_COMPAT_BTREE_सूची	0x0004
#घोषणा EXT4_FEATURE_RO_COMPAT_HUGE_खाता        0x0008
#घोषणा EXT4_FEATURE_RO_COMPAT_GDT_CSUM		0x0010
#घोषणा EXT4_FEATURE_RO_COMPAT_सूची_NLINK	0x0020
#घोषणा EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE	0x0040
#घोषणा EXT4_FEATURE_RO_COMPAT_QUOTA		0x0100
#घोषणा EXT4_FEATURE_RO_COMPAT_BIGALLOC		0x0200
/*
 * METADATA_CSUM also enables group descriptor checksums (GDT_CSUM).  When
 * METADATA_CSUM is set, group descriptor checksums use the same algorithm as
 * all other data काष्ठाures' checksums.  However, the METADATA_CSUM and
 * GDT_CSUM bits are mutually exclusive.
 */
#घोषणा EXT4_FEATURE_RO_COMPAT_METADATA_CSUM	0x0400
#घोषणा EXT4_FEATURE_RO_COMPAT_READONLY		0x1000
#घोषणा EXT4_FEATURE_RO_COMPAT_PROJECT		0x2000
#घोषणा EXT4_FEATURE_RO_COMPAT_VERITY		0x8000

#घोषणा EXT4_FEATURE_INCOMPAT_COMPRESSION	0x0001
#घोषणा EXT4_FEATURE_INCOMPAT_खाताTYPE		0x0002
#घोषणा EXT4_FEATURE_INCOMPAT_RECOVER		0x0004 /* Needs recovery */
#घोषणा EXT4_FEATURE_INCOMPAT_JOURNAL_DEV	0x0008 /* Journal device */
#घोषणा EXT4_FEATURE_INCOMPAT_META_BG		0x0010
#घोषणा EXT4_FEATURE_INCOMPAT_EXTENTS		0x0040 /* extents support */
#घोषणा EXT4_FEATURE_INCOMPAT_64BIT		0x0080
#घोषणा EXT4_FEATURE_INCOMPAT_MMP               0x0100
#घोषणा EXT4_FEATURE_INCOMPAT_FLEX_BG		0x0200
#घोषणा EXT4_FEATURE_INCOMPAT_EA_INODE		0x0400 /* EA in inode */
#घोषणा EXT4_FEATURE_INCOMPAT_सूचीDATA		0x1000 /* data in dirent */
#घोषणा EXT4_FEATURE_INCOMPAT_CSUM_SEED		0x2000
#घोषणा EXT4_FEATURE_INCOMPAT_LARGEसूची		0x4000 /* >2GB or 3-lvl htree */
#घोषणा EXT4_FEATURE_INCOMPAT_INLINE_DATA	0x8000 /* data in inode */
#घोषणा EXT4_FEATURE_INCOMPAT_ENCRYPT		0x10000
#घोषणा EXT4_FEATURE_INCOMPAT_CASEFOLD		0x20000

बाह्य व्योम ext4_update_dynamic_rev(काष्ठा super_block *sb);

#घोषणा EXT4_FEATURE_COMPAT_FUNCS(name, flagname) \
अटल अंतरभूत bool ext4_has_feature_##name(काष्ठा super_block *sb) \
अणु \
	वापस ((EXT4_SB(sb)->s_es->s_feature_compat & \
		cpu_to_le32(EXT4_FEATURE_COMPAT_##flagname)) != 0); \
पूर्ण \
अटल अंतरभूत व्योम ext4_set_feature_##name(काष्ठा super_block *sb) \
अणु \
	ext4_update_dynamic_rev(sb); \
	EXT4_SB(sb)->s_es->s_feature_compat |= \
		cpu_to_le32(EXT4_FEATURE_COMPAT_##flagname); \
पूर्ण \
अटल अंतरभूत व्योम ext4_clear_feature_##name(काष्ठा super_block *sb) \
अणु \
	EXT4_SB(sb)->s_es->s_feature_compat &= \
		~cpu_to_le32(EXT4_FEATURE_COMPAT_##flagname); \
पूर्ण

#घोषणा EXT4_FEATURE_RO_COMPAT_FUNCS(name, flagname) \
अटल अंतरभूत bool ext4_has_feature_##name(काष्ठा super_block *sb) \
अणु \
	वापस ((EXT4_SB(sb)->s_es->s_feature_ro_compat & \
		cpu_to_le32(EXT4_FEATURE_RO_COMPAT_##flagname)) != 0); \
पूर्ण \
अटल अंतरभूत व्योम ext4_set_feature_##name(काष्ठा super_block *sb) \
अणु \
	ext4_update_dynamic_rev(sb); \
	EXT4_SB(sb)->s_es->s_feature_ro_compat |= \
		cpu_to_le32(EXT4_FEATURE_RO_COMPAT_##flagname); \
पूर्ण \
अटल अंतरभूत व्योम ext4_clear_feature_##name(काष्ठा super_block *sb) \
अणु \
	EXT4_SB(sb)->s_es->s_feature_ro_compat &= \
		~cpu_to_le32(EXT4_FEATURE_RO_COMPAT_##flagname); \
पूर्ण

#घोषणा EXT4_FEATURE_INCOMPAT_FUNCS(name, flagname) \
अटल अंतरभूत bool ext4_has_feature_##name(काष्ठा super_block *sb) \
अणु \
	वापस ((EXT4_SB(sb)->s_es->s_feature_incompat & \
		cpu_to_le32(EXT4_FEATURE_INCOMPAT_##flagname)) != 0); \
पूर्ण \
अटल अंतरभूत व्योम ext4_set_feature_##name(काष्ठा super_block *sb) \
अणु \
	ext4_update_dynamic_rev(sb); \
	EXT4_SB(sb)->s_es->s_feature_incompat |= \
		cpu_to_le32(EXT4_FEATURE_INCOMPAT_##flagname); \
पूर्ण \
अटल अंतरभूत व्योम ext4_clear_feature_##name(काष्ठा super_block *sb) \
अणु \
	EXT4_SB(sb)->s_es->s_feature_incompat &= \
		~cpu_to_le32(EXT4_FEATURE_INCOMPAT_##flagname); \
पूर्ण

EXT4_FEATURE_COMPAT_FUNCS(dir_pपुनः_स्मृति,		सूची_PREALLOC)
EXT4_FEATURE_COMPAT_FUNCS(imagic_inodes,	IMAGIC_INODES)
EXT4_FEATURE_COMPAT_FUNCS(journal,		HAS_JOURNAL)
EXT4_FEATURE_COMPAT_FUNCS(xattr,		EXT_ATTR)
EXT4_FEATURE_COMPAT_FUNCS(resize_inode,		RESIZE_INODE)
EXT4_FEATURE_COMPAT_FUNCS(dir_index,		सूची_INDEX)
EXT4_FEATURE_COMPAT_FUNCS(sparse_super2,	SPARSE_SUPER2)
EXT4_FEATURE_COMPAT_FUNCS(fast_commit,		FAST_COMMIT)
EXT4_FEATURE_COMPAT_FUNCS(stable_inodes,	STABLE_INODES)

EXT4_FEATURE_RO_COMPAT_FUNCS(sparse_super,	SPARSE_SUPER)
EXT4_FEATURE_RO_COMPAT_FUNCS(large_file,	LARGE_खाता)
EXT4_FEATURE_RO_COMPAT_FUNCS(btree_dir,		BTREE_सूची)
EXT4_FEATURE_RO_COMPAT_FUNCS(huge_file,		HUGE_खाता)
EXT4_FEATURE_RO_COMPAT_FUNCS(gdt_csum,		GDT_CSUM)
EXT4_FEATURE_RO_COMPAT_FUNCS(dir_nlink,		सूची_NLINK)
EXT4_FEATURE_RO_COMPAT_FUNCS(extra_isize,	EXTRA_ISIZE)
EXT4_FEATURE_RO_COMPAT_FUNCS(quota,		QUOTA)
EXT4_FEATURE_RO_COMPAT_FUNCS(bigalloc,		BIGALLOC)
EXT4_FEATURE_RO_COMPAT_FUNCS(metadata_csum,	METADATA_CSUM)
EXT4_FEATURE_RO_COMPAT_FUNCS(पढ़ोonly,		READONLY)
EXT4_FEATURE_RO_COMPAT_FUNCS(project,		PROJECT)
EXT4_FEATURE_RO_COMPAT_FUNCS(verity,		VERITY)

EXT4_FEATURE_INCOMPAT_FUNCS(compression,	COMPRESSION)
EXT4_FEATURE_INCOMPAT_FUNCS(filetype,		खाताTYPE)
EXT4_FEATURE_INCOMPAT_FUNCS(journal_needs_recovery,	RECOVER)
EXT4_FEATURE_INCOMPAT_FUNCS(journal_dev,	JOURNAL_DEV)
EXT4_FEATURE_INCOMPAT_FUNCS(meta_bg,		META_BG)
EXT4_FEATURE_INCOMPAT_FUNCS(extents,		EXTENTS)
EXT4_FEATURE_INCOMPAT_FUNCS(64bit,		64BIT)
EXT4_FEATURE_INCOMPAT_FUNCS(mmp,		MMP)
EXT4_FEATURE_INCOMPAT_FUNCS(flex_bg,		FLEX_BG)
EXT4_FEATURE_INCOMPAT_FUNCS(ea_inode,		EA_INODE)
EXT4_FEATURE_INCOMPAT_FUNCS(dirdata,		सूचीDATA)
EXT4_FEATURE_INCOMPAT_FUNCS(csum_seed,		CSUM_SEED)
EXT4_FEATURE_INCOMPAT_FUNCS(largedir,		LARGEसूची)
EXT4_FEATURE_INCOMPAT_FUNCS(अंतरभूत_data,	INLINE_DATA)
EXT4_FEATURE_INCOMPAT_FUNCS(encrypt,		ENCRYPT)
EXT4_FEATURE_INCOMPAT_FUNCS(हालfold,		CASEFOLD)

#घोषणा EXT2_FEATURE_COMPAT_SUPP	EXT4_FEATURE_COMPAT_EXT_ATTR
#घोषणा EXT2_FEATURE_INCOMPAT_SUPP	(EXT4_FEATURE_INCOMPAT_खाताTYPE| \
					 EXT4_FEATURE_INCOMPAT_META_BG)
#घोषणा EXT2_FEATURE_RO_COMPAT_SUPP	(EXT4_FEATURE_RO_COMPAT_SPARSE_SUPER| \
					 EXT4_FEATURE_RO_COMPAT_LARGE_खाता| \
					 EXT4_FEATURE_RO_COMPAT_BTREE_सूची)

#घोषणा EXT3_FEATURE_COMPAT_SUPP	EXT4_FEATURE_COMPAT_EXT_ATTR
#घोषणा EXT3_FEATURE_INCOMPAT_SUPP	(EXT4_FEATURE_INCOMPAT_खाताTYPE| \
					 EXT4_FEATURE_INCOMPAT_RECOVER| \
					 EXT4_FEATURE_INCOMPAT_META_BG)
#घोषणा EXT3_FEATURE_RO_COMPAT_SUPP	(EXT4_FEATURE_RO_COMPAT_SPARSE_SUPER| \
					 EXT4_FEATURE_RO_COMPAT_LARGE_खाता| \
					 EXT4_FEATURE_RO_COMPAT_BTREE_सूची)

#घोषणा EXT4_FEATURE_COMPAT_SUPP	EXT4_FEATURE_COMPAT_EXT_ATTR
#घोषणा EXT4_FEATURE_INCOMPAT_SUPP	(EXT4_FEATURE_INCOMPAT_खाताTYPE| \
					 EXT4_FEATURE_INCOMPAT_RECOVER| \
					 EXT4_FEATURE_INCOMPAT_META_BG| \
					 EXT4_FEATURE_INCOMPAT_EXTENTS| \
					 EXT4_FEATURE_INCOMPAT_64BIT| \
					 EXT4_FEATURE_INCOMPAT_FLEX_BG| \
					 EXT4_FEATURE_INCOMPAT_EA_INODE| \
					 EXT4_FEATURE_INCOMPAT_MMP | \
					 EXT4_FEATURE_INCOMPAT_INLINE_DATA | \
					 EXT4_FEATURE_INCOMPAT_ENCRYPT | \
					 EXT4_FEATURE_INCOMPAT_CASEFOLD | \
					 EXT4_FEATURE_INCOMPAT_CSUM_SEED | \
					 EXT4_FEATURE_INCOMPAT_LARGEसूची)
#घोषणा EXT4_FEATURE_RO_COMPAT_SUPP	(EXT4_FEATURE_RO_COMPAT_SPARSE_SUPER| \
					 EXT4_FEATURE_RO_COMPAT_LARGE_खाता| \
					 EXT4_FEATURE_RO_COMPAT_GDT_CSUM| \
					 EXT4_FEATURE_RO_COMPAT_सूची_NLINK | \
					 EXT4_FEATURE_RO_COMPAT_EXTRA_ISIZE | \
					 EXT4_FEATURE_RO_COMPAT_BTREE_सूची |\
					 EXT4_FEATURE_RO_COMPAT_HUGE_खाता |\
					 EXT4_FEATURE_RO_COMPAT_BIGALLOC |\
					 EXT4_FEATURE_RO_COMPAT_METADATA_CSUM|\
					 EXT4_FEATURE_RO_COMPAT_QUOTA |\
					 EXT4_FEATURE_RO_COMPAT_PROJECT |\
					 EXT4_FEATURE_RO_COMPAT_VERITY)

#घोषणा EXTN_FEATURE_FUNCS(ver) \
अटल अंतरभूत bool ext4_has_unknown_ext##ver##_compat_features(काष्ठा super_block *sb) \
अणु \
	वापस ((EXT4_SB(sb)->s_es->s_feature_compat & \
		cpu_to_le32(~EXT##ver##_FEATURE_COMPAT_SUPP)) != 0); \
पूर्ण \
अटल अंतरभूत bool ext4_has_unknown_ext##ver##_ro_compat_features(काष्ठा super_block *sb) \
अणु \
	वापस ((EXT4_SB(sb)->s_es->s_feature_ro_compat & \
		cpu_to_le32(~EXT##ver##_FEATURE_RO_COMPAT_SUPP)) != 0); \
पूर्ण \
अटल अंतरभूत bool ext4_has_unknown_ext##ver##_incompat_features(काष्ठा super_block *sb) \
अणु \
	वापस ((EXT4_SB(sb)->s_es->s_feature_incompat & \
		cpu_to_le32(~EXT##ver##_FEATURE_INCOMPAT_SUPP)) != 0); \
पूर्ण

EXTN_FEATURE_FUNCS(2)
EXTN_FEATURE_FUNCS(3)
EXTN_FEATURE_FUNCS(4)

अटल अंतरभूत bool ext4_has_compat_features(काष्ठा super_block *sb)
अणु
	वापस (EXT4_SB(sb)->s_es->s_feature_compat != 0);
पूर्ण
अटल अंतरभूत bool ext4_has_ro_compat_features(काष्ठा super_block *sb)
अणु
	वापस (EXT4_SB(sb)->s_es->s_feature_ro_compat != 0);
पूर्ण
अटल अंतरभूत bool ext4_has_incompat_features(काष्ठा super_block *sb)
अणु
	वापस (EXT4_SB(sb)->s_es->s_feature_incompat != 0);
पूर्ण

/*
 * Superblock flags
 */
#घोषणा EXT4_FLAGS_RESIZING	0
#घोषणा EXT4_FLAGS_SHUTDOWN	1
#घोषणा EXT4_FLAGS_BDEV_IS_DAX	2

अटल अंतरभूत पूर्णांक ext4_क्रमced_shutकरोwn(काष्ठा ext4_sb_info *sbi)
अणु
	वापस test_bit(EXT4_FLAGS_SHUTDOWN, &sbi->s_ext4_flags);
पूर्ण


/*
 * Default values क्रम user and/or group using reserved blocks
 */
#घोषणा	EXT4_DEF_RESUID		0
#घोषणा	EXT4_DEF_RESGID		0

/*
 * Default project ID
 */
#घोषणा	EXT4_DEF_PROJID		0

#घोषणा EXT4_DEF_INODE_READAHEAD_BLKS	32

/*
 * Default mount options
 */
#घोषणा EXT4_DEFM_DEBUG		0x0001
#घोषणा EXT4_DEFM_BSDGROUPS	0x0002
#घोषणा EXT4_DEFM_XATTR_USER	0x0004
#घोषणा EXT4_DEFM_ACL		0x0008
#घोषणा EXT4_DEFM_UID16		0x0010
#घोषणा EXT4_DEFM_JMODE		0x0060
#घोषणा EXT4_DEFM_JMODE_DATA	0x0020
#घोषणा EXT4_DEFM_JMODE_ORDERED	0x0040
#घोषणा EXT4_DEFM_JMODE_WBACK	0x0060
#घोषणा EXT4_DEFM_NOBARRIER	0x0100
#घोषणा EXT4_DEFM_BLOCK_VALIDITY 0x0200
#घोषणा EXT4_DEFM_DISCARD	0x0400
#घोषणा EXT4_DEFM_NODELALLOC	0x0800

/*
 * Default journal batch बार
 */
#घोषणा EXT4_DEF_MIN_BATCH_TIME	0
#घोषणा EXT4_DEF_MAX_BATCH_TIME	15000 /* 15ms */

/*
 * Minimum number of groups in a flexgroup beक्रमe we separate out
 * directories पूर्णांकo the first block group of a flexgroup
 */
#घोषणा EXT4_FLEX_SIZE_सूची_ALLOC_SCHEME	4

/*
 * Structure of a directory entry
 */
#घोषणा EXT4_NAME_LEN 255

काष्ठा ext4_dir_entry अणु
	__le32	inode;			/* Inode number */
	__le16	rec_len;		/* Directory entry length */
	__le16	name_len;		/* Name length */
	अक्षर	name[EXT4_NAME_LEN];	/* File name */
पूर्ण;


/*
 * Encrypted Casefolded entries require saving the hash on disk. This काष्ठाure
 * followed ext4_dir_entry_2's name[name_len] at the next 4 byte aligned
 * boundary.
 */
काष्ठा ext4_dir_entry_hash अणु
	__le32 hash;
	__le32 minor_hash;
पूर्ण;

/*
 * The new version of the directory entry.  Since EXT4 काष्ठाures are
 * stored in पूर्णांकel byte order, and the name_len field could never be
 * bigger than 255 अक्षरs, it's safe to reclaim the extra byte क्रम the
 * file_type field.
 */
काष्ठा ext4_dir_entry_2 अणु
	__le32	inode;			/* Inode number */
	__le16	rec_len;		/* Directory entry length */
	__u8	name_len;		/* Name length */
	__u8	file_type;		/* See file type macros EXT4_FT_* below */
	अक्षर	name[EXT4_NAME_LEN];	/* File name */
पूर्ण;

/*
 * Access the hashes at the end of ext4_dir_entry_2
 */
#घोषणा EXT4_सूचीENT_HASHES(entry) \
	((काष्ठा ext4_dir_entry_hash *) \
		(((व्योम *)(entry)) + \
		((8 + (entry)->name_len + EXT4_सूची_ROUND) & ~EXT4_सूची_ROUND)))
#घोषणा EXT4_सूचीENT_HASH(entry) le32_to_cpu(EXT4_सूचीENT_HASHES(de)->hash)
#घोषणा EXT4_सूचीENT_MINOR_HASH(entry) \
		le32_to_cpu(EXT4_सूचीENT_HASHES(de)->minor_hash)

अटल अंतरभूत bool ext4_hash_in_dirent(स्थिर काष्ठा inode *inode)
अणु
	वापस IS_CASEFOLDED(inode) && IS_ENCRYPTED(inode);
पूर्ण

/*
 * This is a bogus directory entry at the end of each leaf block that
 * records checksums.
 */
काष्ठा ext4_dir_entry_tail अणु
	__le32	det_reserved_zero1;	/* Pretend to be unused */
	__le16	det_rec_len;		/* 12 */
	__u8	det_reserved_zero2;	/* Zero name length */
	__u8	det_reserved_ft;	/* 0xDE, fake file type */
	__le32	det_checksum;		/* crc32c(uuid+inum+dirblock) */
पूर्ण;

#घोषणा EXT4_सूचीENT_TAIL(block, blocksize) \
	((काष्ठा ext4_dir_entry_tail *)(((व्योम *)(block)) + \
					((blocksize) - \
					 माप(काष्ठा ext4_dir_entry_tail))))

/*
 * Ext4 directory file types.  Only the low 3 bits are used.  The
 * other bits are reserved क्रम now.
 */
#घोषणा EXT4_FT_UNKNOWN		0
#घोषणा EXT4_FT_REG_खाता	1
#घोषणा EXT4_FT_सूची		2
#घोषणा EXT4_FT_CHRDEV		3
#घोषणा EXT4_FT_BLKDEV		4
#घोषणा EXT4_FT_FIFO		5
#घोषणा EXT4_FT_SOCK		6
#घोषणा EXT4_FT_SYMLINK		7

#घोषणा EXT4_FT_MAX		8

#घोषणा EXT4_FT_सूची_CSUM	0xDE

/*
 * EXT4_सूची_PAD defines the directory entries boundaries
 *
 * NOTE: It must be a multiple of 4
 */
#घोषणा EXT4_सूची_PAD			4
#घोषणा EXT4_सूची_ROUND			(EXT4_सूची_PAD - 1)
#घोषणा EXT4_MAX_REC_LEN		((1<<16)-1)

/*
 * The rec_len is dependent on the type of directory. Directories that are
 * हालfolded and encrypted need to store the hash as well, so we add room क्रम
 * ext4_extended_dir_entry_2. For all entries related to '.' or '..' you should
 * pass शून्य क्रम dir, as those entries करो not use the extra fields.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ext4_dir_rec_len(__u8 name_len,
						स्थिर काष्ठा inode *dir)
अणु
	पूर्णांक rec_len = (name_len + 8 + EXT4_सूची_ROUND);

	अगर (dir && ext4_hash_in_dirent(dir))
		rec_len += माप(काष्ठा ext4_dir_entry_hash);
	वापस (rec_len & ~EXT4_सूची_ROUND);
पूर्ण

/*
 * If we ever get support क्रम fs block sizes > page_size, we'll need
 * to हटाओ the #अगर statements in the next two functions...
 */
अटल अंतरभूत अचिन्हित पूर्णांक
ext4_rec_len_from_disk(__le16 dlen, अचिन्हित blocksize)
अणु
	अचिन्हित len = le16_to_cpu(dlen);

#अगर (PAGE_SIZE >= 65536)
	अगर (len == EXT4_MAX_REC_LEN || len == 0)
		वापस blocksize;
	वापस (len & 65532) | ((len & 3) << 16);
#अन्यथा
	वापस len;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __le16 ext4_rec_len_to_disk(अचिन्हित len, अचिन्हित blocksize)
अणु
	अगर ((len > blocksize) || (blocksize > (1 << 18)) || (len & 3))
		BUG();
#अगर (PAGE_SIZE >= 65536)
	अगर (len < 65536)
		वापस cpu_to_le16(len);
	अगर (len == blocksize) अणु
		अगर (blocksize == 65536)
			वापस cpu_to_le16(EXT4_MAX_REC_LEN);
		अन्यथा
			वापस cpu_to_le16(0);
	पूर्ण
	वापस cpu_to_le16((len & 65532) | ((len >> 16) & 3));
#अन्यथा
	वापस cpu_to_le16(len);
#पूर्ण_अगर
पूर्ण

/*
 * Hash Tree Directory indexing
 * (c) Daniel Phillips, 2001
 */

#घोषणा is_dx(dir) (ext4_has_feature_dir_index((dir)->i_sb) && \
		    ext4_test_inode_flag((dir), EXT4_INODE_INDEX))
#घोषणा EXT4_सूची_LINK_MAX(dir) unlikely((dir)->i_nlink >= EXT4_LINK_MAX && \
		    !(ext4_has_feature_dir_nlink((dir)->i_sb) && is_dx(dir)))
#घोषणा EXT4_सूची_LINK_EMPTY(dir) ((dir)->i_nlink == 2 || (dir)->i_nlink == 1)

/* Legal values क्रम the dx_root hash_version field: */

#घोषणा DX_HASH_LEGACY			0
#घोषणा DX_HASH_HALF_MD4		1
#घोषणा DX_HASH_TEA			2
#घोषणा DX_HASH_LEGACY_UNSIGNED		3
#घोषणा DX_HASH_HALF_MD4_UNSIGNED	4
#घोषणा DX_HASH_TEA_UNSIGNED		5
#घोषणा DX_HASH_SIPHASH			6

अटल अंतरभूत u32 ext4_chksum(काष्ठा ext4_sb_info *sbi, u32 crc,
			      स्थिर व्योम *address, अचिन्हित पूर्णांक length)
अणु
	काष्ठा अणु
		काष्ठा shash_desc shash;
		अक्षर ctx[4];
	पूर्ण desc;

	BUG_ON(crypto_shash_descsize(sbi->s_chksum_driver)!=माप(desc.ctx));

	desc.shash.tfm = sbi->s_chksum_driver;
	*(u32 *)desc.ctx = crc;

	BUG_ON(crypto_shash_update(&desc.shash, address, length));

	वापस *(u32 *)desc.ctx;
पूर्ण

#अगर_घोषित __KERNEL__

/* hash info काष्ठाure used by the directory hash */
काष्ठा dx_hash_info
अणु
	u32		hash;
	u32		minor_hash;
	पूर्णांक		hash_version;
	u32		*seed;
पूर्ण;


/* 32 and 64 bit चिन्हित खातापूर्ण क्रम dx directories */
#घोषणा EXT4_HTREE_खातापूर्ण_32BIT   ((1UL  << (32 - 1)) - 1)
#घोषणा EXT4_HTREE_खातापूर्ण_64BIT   ((1ULL << (64 - 1)) - 1)


/*
 * Control parameters used by ext4_htree_next_block
 */
#घोषणा HASH_NB_ALWAYS		1

काष्ठा ext4_filename अणु
	स्थिर काष्ठा qstr *usr_fname;
	काष्ठा fscrypt_str disk_name;
	काष्ठा dx_hash_info hinfo;
#अगर_घोषित CONFIG_FS_ENCRYPTION
	काष्ठा fscrypt_str crypto_buf;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UNICODE
	काष्ठा fscrypt_str cf_name;
#पूर्ण_अगर
पूर्ण;

#घोषणा fname_name(p) ((p)->disk_name.name)
#घोषणा fname_usr_name(p) ((p)->usr_fname->name)
#घोषणा fname_len(p)  ((p)->disk_name.len)

/*
 * Describe an inode's exact location on disk and in memory
 */
काष्ठा ext4_iloc
अणु
	काष्ठा buffer_head *bh;
	अचिन्हित दीर्घ offset;
	ext4_group_t block_group;
पूर्ण;

अटल अंतरभूत काष्ठा ext4_inode *ext4_raw_inode(काष्ठा ext4_iloc *iloc)
अणु
	वापस (काष्ठा ext4_inode *) (iloc->bh->b_data + iloc->offset);
पूर्ण

अटल अंतरभूत bool ext4_is_quota_file(काष्ठा inode *inode)
अणु
	वापस IS_NOQUOTA(inode) &&
	       !(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL);
पूर्ण

/*
 * This काष्ठाure is stuffed पूर्णांकo the काष्ठा file's निजी_data field
 * क्रम directories.  It is where we put inक्रमmation so that we can करो
 * सूची_पढ़ो operations in hash tree order.
 */
काष्ठा dir_निजी_info अणु
	काष्ठा rb_root	root;
	काष्ठा rb_node	*curr_node;
	काष्ठा fname	*extra_fname;
	loff_t		last_pos;
	__u32		curr_hash;
	__u32		curr_minor_hash;
	__u32		next_hash;
पूर्ण;

/* calculate the first block number of the group */
अटल अंतरभूत ext4_fsblk_t
ext4_group_first_block_no(काष्ठा super_block *sb, ext4_group_t group_no)
अणु
	वापस group_no * (ext4_fsblk_t)EXT4_BLOCKS_PER_GROUP(sb) +
		le32_to_cpu(EXT4_SB(sb)->s_es->s_first_data_block);
पूर्ण

/*
 * Special error वापस code only used by dx_probe() and its callers.
 */
#घोषणा ERR_BAD_DX_सूची	(-(MAX_ERRNO - 1))

/* htree levels क्रम ext4 */
#घोषणा	EXT4_HTREE_LEVEL_COMPAT	2
#घोषणा	EXT4_HTREE_LEVEL	3

अटल अंतरभूत पूर्णांक ext4_dir_htree_level(काष्ठा super_block *sb)
अणु
	वापस ext4_has_feature_largedir(sb) ?
		EXT4_HTREE_LEVEL : EXT4_HTREE_LEVEL_COMPAT;
पूर्ण

/*
 * Timeout and state flag क्रम lazy initialization inode thपढ़ो.
 */
#घोषणा EXT4_DEF_LI_WAIT_MULT			10
#घोषणा EXT4_DEF_LI_MAX_START_DELAY		5
#घोषणा EXT4_LAZYINIT_QUIT			0x0001
#घोषणा EXT4_LAZYINIT_RUNNING			0x0002

/*
 * Lazy inode table initialization info
 */
काष्ठा ext4_lazy_init अणु
	अचिन्हित दीर्घ		li_state;
	काष्ठा list_head	li_request_list;
	काष्ठा mutex		li_list_mtx;
पूर्ण;

क्रमागत ext4_li_mode अणु
	EXT4_LI_MODE_PREFETCH_BBITMAP,
	EXT4_LI_MODE_ITABLE,
पूर्ण;

काष्ठा ext4_li_request अणु
	काष्ठा super_block	*lr_super;
	क्रमागत ext4_li_mode	lr_mode;
	ext4_group_t		lr_first_not_zeroed;
	ext4_group_t		lr_next_group;
	काष्ठा list_head	lr_request;
	अचिन्हित दीर्घ		lr_next_sched;
	अचिन्हित दीर्घ		lr_समयout;
पूर्ण;

काष्ठा ext4_features अणु
	काष्ठा kobject f_kobj;
	काष्ठा completion f_kobj_unरेजिस्टर;
पूर्ण;

/*
 * This काष्ठाure will be used क्रम multiple mount protection. It will be
 * written पूर्णांकo the block number saved in the s_mmp_block field in the
 * superblock. Programs that check MMP should assume that अगर
 * SEQ_FSCK (or any unknown code above SEQ_MAX) is present then it is NOT safe
 * to use the fileप्रणाली, regardless of how old the बारtamp is.
 */
#घोषणा EXT4_MMP_MAGIC     0x004D4D50U /* ASCII क्रम MMP */
#घोषणा EXT4_MMP_SEQ_CLEAN 0xFF4D4D50U /* mmp_seq value क्रम clean unmount */
#घोषणा EXT4_MMP_SEQ_FSCK  0xE24D4D50U /* mmp_seq value when being fscked */
#घोषणा EXT4_MMP_SEQ_MAX   0xE24D4D4FU /* maximum valid mmp_seq value */

काष्ठा mmp_काष्ठा अणु
	__le32	mmp_magic;		/* Magic number क्रम MMP */
	__le32	mmp_seq;		/* Sequence no. updated periodically */

	/*
	 * mmp_समय, mmp_nodename & mmp_bdevname are only used क्रम inक्रमmation
	 * purposes and करो not affect the correctness of the algorithm
	 */
	__le64	mmp_समय;		/* Time last updated */
	अक्षर	mmp_nodename[64];	/* Node which last updated MMP block */
	अक्षर	mmp_bdevname[32];	/* Bdev which last updated MMP block */

	/*
	 * mmp_check_पूर्णांकerval is used to verअगरy अगर the MMP block has been
	 * updated on the block device. The value is updated based on the
	 * maximum समय to ग_लिखो the MMP block during an update cycle.
	 */
	__le16	mmp_check_पूर्णांकerval;

	__le16	mmp_pad1;
	__le32	mmp_pad2[226];
	__le32	mmp_checksum;		/* crc32c(uuid+mmp_block) */
पूर्ण;

/* arguments passed to the mmp thपढ़ो */
काष्ठा mmpd_data अणु
	काष्ठा buffer_head *bh; /* bh from initial पढ़ो_mmp_block() */
	काष्ठा super_block *sb;  /* super block of the fs */
पूर्ण;

/*
 * Check पूर्णांकerval multiplier
 * The MMP block is written every update पूर्णांकerval and initially checked every
 * update पूर्णांकerval x the multiplier (the value is then adapted based on the
 * ग_लिखो latency). The reason is that ग_लिखोs can be delayed under load and we
 * करोn't want पढ़ोers to incorrectly assume that the fileप्रणाली is no दीर्घer
 * in use.
 */
#घोषणा EXT4_MMP_CHECK_MULT		2UL

/*
 * Minimum पूर्णांकerval क्रम MMP checking in seconds.
 */
#घोषणा EXT4_MMP_MIN_CHECK_INTERVAL	5UL

/*
 * Maximum पूर्णांकerval क्रम MMP checking in seconds.
 */
#घोषणा EXT4_MMP_MAX_CHECK_INTERVAL	300UL

/*
 * Function prototypes
 */

/*
 * Ok, these declarations are also in <linux/kernel.h> but none of the
 * ext4 source programs needs to include it so they are duplicated here.
 */
# define NORET_TYPE	/**/
# define ATTRIB_NORET	__attribute__((noवापस))
# define NORET_AND	noवापस,

/* biपंचांगap.c */
बाह्य अचिन्हित पूर्णांक ext4_count_मुक्त(अक्षर *biपंचांगap, अचिन्हित numअक्षरs);
व्योम ext4_inode_biपंचांगap_csum_set(काष्ठा super_block *sb, ext4_group_t group,
				काष्ठा ext4_group_desc *gdp,
				काष्ठा buffer_head *bh, पूर्णांक sz);
पूर्णांक ext4_inode_biपंचांगap_csum_verअगरy(काष्ठा super_block *sb, ext4_group_t group,
				  काष्ठा ext4_group_desc *gdp,
				  काष्ठा buffer_head *bh, पूर्णांक sz);
व्योम ext4_block_biपंचांगap_csum_set(काष्ठा super_block *sb, ext4_group_t group,
				काष्ठा ext4_group_desc *gdp,
				काष्ठा buffer_head *bh);
पूर्णांक ext4_block_biपंचांगap_csum_verअगरy(काष्ठा super_block *sb, ext4_group_t group,
				  काष्ठा ext4_group_desc *gdp,
				  काष्ठा buffer_head *bh);

/* balloc.c */
बाह्य व्योम ext4_get_group_no_and_offset(काष्ठा super_block *sb,
					 ext4_fsblk_t blocknr,
					 ext4_group_t *blockgrpp,
					 ext4_grpblk_t *offsetp);
बाह्य ext4_group_t ext4_get_group_number(काष्ठा super_block *sb,
					  ext4_fsblk_t block);

बाह्य अचिन्हित पूर्णांक ext4_block_group(काष्ठा super_block *sb,
			ext4_fsblk_t blocknr);
बाह्य ext4_grpblk_t ext4_block_group_offset(काष्ठा super_block *sb,
			ext4_fsblk_t blocknr);
बाह्य पूर्णांक ext4_bg_has_super(काष्ठा super_block *sb, ext4_group_t group);
बाह्य अचिन्हित दीर्घ ext4_bg_num_gdb(काष्ठा super_block *sb,
			ext4_group_t group);
बाह्य ext4_fsblk_t ext4_new_meta_blocks(handle_t *handle, काष्ठा inode *inode,
					 ext4_fsblk_t goal,
					 अचिन्हित पूर्णांक flags,
					 अचिन्हित दीर्घ *count,
					 पूर्णांक *errp);
बाह्य पूर्णांक ext4_claim_मुक्त_clusters(काष्ठा ext4_sb_info *sbi,
				    s64 nclusters, अचिन्हित पूर्णांक flags);
बाह्य ext4_fsblk_t ext4_count_मुक्त_clusters(काष्ठा super_block *);
बाह्य व्योम ext4_check_blocks_biपंचांगap(काष्ठा super_block *);
बाह्य काष्ठा ext4_group_desc * ext4_get_group_desc(काष्ठा super_block * sb,
						    ext4_group_t block_group,
						    काष्ठा buffer_head ** bh);
बाह्य पूर्णांक ext4_should_retry_alloc(काष्ठा super_block *sb, पूर्णांक *retries);

बाह्य काष्ठा buffer_head *ext4_पढ़ो_block_biपंचांगap_noरुको(काष्ठा super_block *sb,
						ext4_group_t block_group,
						bool ignore_locked);
बाह्य पूर्णांक ext4_रुको_block_biपंचांगap(काष्ठा super_block *sb,
				  ext4_group_t block_group,
				  काष्ठा buffer_head *bh);
बाह्य काष्ठा buffer_head *ext4_पढ़ो_block_biपंचांगap(काष्ठा super_block *sb,
						  ext4_group_t block_group);
बाह्य अचिन्हित ext4_मुक्त_clusters_after_init(काष्ठा super_block *sb,
					      ext4_group_t block_group,
					      काष्ठा ext4_group_desc *gdp);
ext4_fsblk_t ext4_inode_to_goal_block(काष्ठा inode *);

#अगर_घोषित CONFIG_UNICODE
बाह्य पूर्णांक ext4_fname_setup_ci_filename(काष्ठा inode *dir,
					 स्थिर काष्ठा qstr *iname,
					 काष्ठा ext4_filename *fname);
#पूर्ण_अगर

#अगर_घोषित CONFIG_FS_ENCRYPTION
अटल अंतरभूत व्योम ext4_fname_from_fscrypt_name(काष्ठा ext4_filename *dst,
						स्थिर काष्ठा fscrypt_name *src)
अणु
	स_रखो(dst, 0, माप(*dst));

	dst->usr_fname = src->usr_fname;
	dst->disk_name = src->disk_name;
	dst->hinfo.hash = src->hash;
	dst->hinfo.minor_hash = src->minor_hash;
	dst->crypto_buf = src->crypto_buf;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_fname_setup_filename(काष्ठा inode *dir,
					    स्थिर काष्ठा qstr *iname,
					    पूर्णांक lookup,
					    काष्ठा ext4_filename *fname)
अणु
	काष्ठा fscrypt_name name;
	पूर्णांक err;

	err = fscrypt_setup_filename(dir, iname, lookup, &name);
	अगर (err)
		वापस err;

	ext4_fname_from_fscrypt_name(fname, &name);

#अगर_घोषित CONFIG_UNICODE
	err = ext4_fname_setup_ci_filename(dir, iname, fname);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_fname_prepare_lookup(काष्ठा inode *dir,
					    काष्ठा dentry *dentry,
					    काष्ठा ext4_filename *fname)
अणु
	काष्ठा fscrypt_name name;
	पूर्णांक err;

	err = fscrypt_prepare_lookup(dir, dentry, &name);
	अगर (err)
		वापस err;

	ext4_fname_from_fscrypt_name(fname, &name);

#अगर_घोषित CONFIG_UNICODE
	err = ext4_fname_setup_ci_filename(dir, &dentry->d_name, fname);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल अंतरभूत व्योम ext4_fname_मुक्त_filename(काष्ठा ext4_filename *fname)
अणु
	काष्ठा fscrypt_name name;

	name.crypto_buf = fname->crypto_buf;
	fscrypt_मुक्त_filename(&name);

	fname->crypto_buf.name = शून्य;
	fname->usr_fname = शून्य;
	fname->disk_name.name = शून्य;

#अगर_घोषित CONFIG_UNICODE
	kमुक्त(fname->cf_name.name);
	fname->cf_name.name = शून्य;
#पूर्ण_अगर
पूर्ण
#अन्यथा /* !CONFIG_FS_ENCRYPTION */
अटल अंतरभूत पूर्णांक ext4_fname_setup_filename(काष्ठा inode *dir,
					    स्थिर काष्ठा qstr *iname,
					    पूर्णांक lookup,
					    काष्ठा ext4_filename *fname)
अणु
	पूर्णांक err = 0;
	fname->usr_fname = iname;
	fname->disk_name.name = (अचिन्हित अक्षर *) iname->name;
	fname->disk_name.len = iname->len;

#अगर_घोषित CONFIG_UNICODE
	err = ext4_fname_setup_ci_filename(dir, iname, fname);
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_fname_prepare_lookup(काष्ठा inode *dir,
					    काष्ठा dentry *dentry,
					    काष्ठा ext4_filename *fname)
अणु
	वापस ext4_fname_setup_filename(dir, &dentry->d_name, 1, fname);
पूर्ण

अटल अंतरभूत व्योम ext4_fname_मुक्त_filename(काष्ठा ext4_filename *fname)
अणु
#अगर_घोषित CONFIG_UNICODE
	kमुक्त(fname->cf_name.name);
	fname->cf_name.name = शून्य;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* !CONFIG_FS_ENCRYPTION */

/* dir.c */
बाह्य पूर्णांक __ext4_check_dir_entry(स्थिर अक्षर *, अचिन्हित पूर्णांक, काष्ठा inode *,
				  काष्ठा file *,
				  काष्ठा ext4_dir_entry_2 *,
				  काष्ठा buffer_head *, अक्षर *, पूर्णांक,
				  अचिन्हित पूर्णांक);
#घोषणा ext4_check_dir_entry(dir, filp, de, bh, buf, size, offset) \
	unlikely(__ext4_check_dir_entry(__func__, __LINE__, (dir), (filp), \
				(de), (bh), (buf), (size), (offset)))
बाह्य पूर्णांक ext4_htree_store_dirent(काष्ठा file *dir_file, __u32 hash,
				__u32 minor_hash,
				काष्ठा ext4_dir_entry_2 *dirent,
				काष्ठा fscrypt_str *ent_name);
बाह्य व्योम ext4_htree_मुक्त_dir_info(काष्ठा dir_निजी_info *p);
बाह्य पूर्णांक ext4_find_dest_de(काष्ठा inode *dir, काष्ठा inode *inode,
			     काष्ठा buffer_head *bh,
			     व्योम *buf, पूर्णांक buf_size,
			     काष्ठा ext4_filename *fname,
			     काष्ठा ext4_dir_entry_2 **dest_de);
व्योम ext4_insert_dentry(काष्ठा inode *dir, काष्ठा inode *inode,
			काष्ठा ext4_dir_entry_2 *de,
			पूर्णांक buf_size,
			काष्ठा ext4_filename *fname);
अटल अंतरभूत व्योम ext4_update_dx_flag(काष्ठा inode *inode)
अणु
	अगर (!ext4_has_feature_dir_index(inode->i_sb) &&
	    ext4_test_inode_flag(inode, EXT4_INODE_INDEX)) अणु
		/* ext4_iget() should have caught this... */
		WARN_ON_ONCE(ext4_has_feature_metadata_csum(inode->i_sb));
		ext4_clear_inode_flag(inode, EXT4_INODE_INDEX);
	पूर्ण
पूर्ण
अटल स्थिर अचिन्हित अक्षर ext4_filetype_table[] = अणु
	DT_UNKNOWN, DT_REG, DT_सूची, DT_CHR, DT_BLK, DT_FIFO, DT_SOCK, DT_LNK
पूर्ण;

अटल अंतरभूत  अचिन्हित अक्षर get_dtype(काष्ठा super_block *sb, पूर्णांक filetype)
अणु
	अगर (!ext4_has_feature_filetype(sb) || filetype >= EXT4_FT_MAX)
		वापस DT_UNKNOWN;

	वापस ext4_filetype_table[filetype];
पूर्ण
बाह्य पूर्णांक ext4_check_all_de(काष्ठा inode *dir, काष्ठा buffer_head *bh,
			     व्योम *buf, पूर्णांक buf_size);

/* fsync.c */
बाह्य पूर्णांक ext4_sync_file(काष्ठा file *, loff_t, loff_t, पूर्णांक);

/* hash.c */
बाह्य पूर्णांक ext4fs_dirhash(स्थिर काष्ठा inode *dir, स्थिर अक्षर *name, पूर्णांक len,
			  काष्ठा dx_hash_info *hinfo);

/* ialloc.c */
बाह्य पूर्णांक ext4_mark_inode_used(काष्ठा super_block *sb, पूर्णांक ino);
बाह्य काष्ठा inode *__ext4_new_inode(काष्ठा user_namespace *, handle_t *,
				      काष्ठा inode *, umode_t,
				      स्थिर काष्ठा qstr *qstr, __u32 goal,
				      uid_t *owner, __u32 i_flags,
				      पूर्णांक handle_type, अचिन्हित पूर्णांक line_no,
				      पूर्णांक nblocks);

#घोषणा ext4_new_inode(handle, dir, mode, qstr, goal, owner, i_flags)          \
	__ext4_new_inode(&init_user_ns, (handle), (dir), (mode), (qstr),       \
			 (goal), (owner), i_flags, 0, 0, 0)
#घोषणा ext4_new_inode_start_handle(mnt_userns, dir, mode, qstr, goal, owner, \
				    type, nblocks)		    \
	__ext4_new_inode((mnt_userns), शून्य, (dir), (mode), (qstr), (goal), (owner), \
			 0, (type), __LINE__, (nblocks))


बाह्य व्योम ext4_मुक्त_inode(handle_t *, काष्ठा inode *);
बाह्य काष्ठा inode * ext4_orphan_get(काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ ext4_count_मुक्त_inodes(काष्ठा super_block *);
बाह्य अचिन्हित दीर्घ ext4_count_dirs(काष्ठा super_block *);
बाह्य व्योम ext4_check_inodes_biपंचांगap(काष्ठा super_block *);
बाह्य व्योम ext4_mark_biपंचांगap_end(पूर्णांक start_bit, पूर्णांक end_bit, अक्षर *biपंचांगap);
बाह्य पूर्णांक ext4_init_inode_table(काष्ठा super_block *sb,
				 ext4_group_t group, पूर्णांक barrier);
बाह्य व्योम ext4_end_biपंचांगap_पढ़ो(काष्ठा buffer_head *bh, पूर्णांक uptodate);

/* fast_commit.c */
पूर्णांक ext4_fc_info_show(काष्ठा seq_file *seq, व्योम *v);
व्योम ext4_fc_init(काष्ठा super_block *sb, journal_t *journal);
व्योम ext4_fc_init_inode(काष्ठा inode *inode);
व्योम ext4_fc_track_range(handle_t *handle, काष्ठा inode *inode, ext4_lblk_t start,
			 ext4_lblk_t end);
व्योम __ext4_fc_track_unlink(handle_t *handle, काष्ठा inode *inode,
	काष्ठा dentry *dentry);
व्योम __ext4_fc_track_link(handle_t *handle, काष्ठा inode *inode,
	काष्ठा dentry *dentry);
व्योम ext4_fc_track_unlink(handle_t *handle, काष्ठा dentry *dentry);
व्योम ext4_fc_track_link(handle_t *handle, काष्ठा dentry *dentry);
व्योम __ext4_fc_track_create(handle_t *handle, काष्ठा inode *inode,
			    काष्ठा dentry *dentry);
व्योम ext4_fc_track_create(handle_t *handle, काष्ठा dentry *dentry);
व्योम ext4_fc_track_inode(handle_t *handle, काष्ठा inode *inode);
व्योम ext4_fc_mark_ineligible(काष्ठा super_block *sb, पूर्णांक reason);
व्योम ext4_fc_start_ineligible(काष्ठा super_block *sb, पूर्णांक reason);
व्योम ext4_fc_stop_ineligible(काष्ठा super_block *sb);
व्योम ext4_fc_start_update(काष्ठा inode *inode);
व्योम ext4_fc_stop_update(काष्ठा inode *inode);
व्योम ext4_fc_del(काष्ठा inode *inode);
bool ext4_fc_replay_check_excluded(काष्ठा super_block *sb, ext4_fsblk_t block);
व्योम ext4_fc_replay_cleanup(काष्ठा super_block *sb);
पूर्णांक ext4_fc_commit(journal_t *journal, tid_t commit_tid);
पूर्णांक __init ext4_fc_init_dentry_cache(व्योम);

/* mballoc.c */
बाह्य स्थिर काष्ठा seq_operations ext4_mb_seq_groups_ops;
बाह्य स्थिर काष्ठा seq_operations ext4_mb_seq_काष्ठाs_summary_ops;
बाह्य दीर्घ ext4_mb_stats;
बाह्य दीर्घ ext4_mb_max_to_scan;
बाह्य पूर्णांक ext4_seq_mb_stats_show(काष्ठा seq_file *seq, व्योम *offset);
बाह्य पूर्णांक ext4_mb_init(काष्ठा super_block *);
बाह्य पूर्णांक ext4_mb_release(काष्ठा super_block *);
बाह्य ext4_fsblk_t ext4_mb_new_blocks(handle_t *,
				काष्ठा ext4_allocation_request *, पूर्णांक *);
बाह्य पूर्णांक ext4_mb_reserve_blocks(काष्ठा super_block *, पूर्णांक);
बाह्य व्योम ext4_discard_pपुनः_स्मृतिations(काष्ठा inode *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक __init ext4_init_mballoc(व्योम);
बाह्य व्योम ext4_निकास_mballoc(व्योम);
बाह्य ext4_group_t ext4_mb_prefetch(काष्ठा super_block *sb,
				     ext4_group_t group,
				     अचिन्हित पूर्णांक nr, पूर्णांक *cnt);
बाह्य व्योम ext4_mb_prefetch_fini(काष्ठा super_block *sb, ext4_group_t group,
				  अचिन्हित पूर्णांक nr);

बाह्य व्योम ext4_मुक्त_blocks(handle_t *handle, काष्ठा inode *inode,
			     काष्ठा buffer_head *bh, ext4_fsblk_t block,
			     अचिन्हित दीर्घ count, पूर्णांक flags);
बाह्य पूर्णांक ext4_mb_alloc_groupinfo(काष्ठा super_block *sb,
				   ext4_group_t ngroups);
बाह्य पूर्णांक ext4_mb_add_groupinfo(काष्ठा super_block *sb,
		ext4_group_t i, काष्ठा ext4_group_desc *desc);
बाह्य पूर्णांक ext4_group_add_blocks(handle_t *handle, काष्ठा super_block *sb,
				ext4_fsblk_t block, अचिन्हित दीर्घ count);
बाह्य पूर्णांक ext4_trim_fs(काष्ठा super_block *, काष्ठा fstrim_range *);
बाह्य व्योम ext4_process_मुक्तd_data(काष्ठा super_block *sb, tid_t commit_tid);
बाह्य व्योम ext4_mb_mark_bb(काष्ठा super_block *sb, ext4_fsblk_t block,
		       पूर्णांक len, पूर्णांक state);

/* inode.c */
व्योम ext4_inode_csum_set(काष्ठा inode *inode, काष्ठा ext4_inode *raw,
			 काष्ठा ext4_inode_info *ei);
पूर्णांक ext4_inode_is_fast_symlink(काष्ठा inode *inode);
काष्ठा buffer_head *ext4_getblk(handle_t *, काष्ठा inode *, ext4_lblk_t, पूर्णांक);
काष्ठा buffer_head *ext4_bपढ़ो(handle_t *, काष्ठा inode *, ext4_lblk_t, पूर्णांक);
पूर्णांक ext4_bपढ़ो_batch(काष्ठा inode *inode, ext4_lblk_t block, पूर्णांक bh_count,
		     bool रुको, काष्ठा buffer_head **bhs);
पूर्णांक ext4_get_block_unwritten(काष्ठा inode *inode, sector_t iblock,
			     काष्ठा buffer_head *bh_result, पूर्णांक create);
पूर्णांक ext4_get_block(काष्ठा inode *inode, sector_t iblock,
		   काष्ठा buffer_head *bh_result, पूर्णांक create);
पूर्णांक ext4_da_get_block_prep(काष्ठा inode *inode, sector_t iblock,
			   काष्ठा buffer_head *bh, पूर्णांक create);
पूर्णांक ext4_walk_page_buffers(handle_t *handle,
			   काष्ठा buffer_head *head,
			   अचिन्हित from,
			   अचिन्हित to,
			   पूर्णांक *partial,
			   पूर्णांक (*fn)(handle_t *handle,
				     काष्ठा buffer_head *bh));
पूर्णांक करो_journal_get_ग_लिखो_access(handle_t *handle,
				काष्ठा buffer_head *bh);
#घोषणा FALL_BACK_TO_NONDELALLOC 1
#घोषणा CONVERT_INLINE_DATA	 2

प्रकार क्रमागत अणु
	EXT4_IGET_NORMAL =	0,
	EXT4_IGET_SPECIAL =	0x0001, /* OK to iget a प्रणाली inode */
	EXT4_IGET_HANDLE = 	0x0002	/* Inode # is from a handle */
पूर्ण ext4_iget_flags;

बाह्य काष्ठा inode *__ext4_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino,
				 ext4_iget_flags flags, स्थिर अक्षर *function,
				 अचिन्हित पूर्णांक line);

#घोषणा ext4_iget(sb, ino, flags) \
	__ext4_iget((sb), (ino), (flags), __func__, __LINE__)

बाह्य पूर्णांक  ext4_ग_लिखो_inode(काष्ठा inode *, काष्ठा ग_लिखोback_control *);
बाह्य पूर्णांक  ext4_setattr(काष्ठा user_namespace *, काष्ठा dentry *,
			 काष्ठा iattr *);
बाह्य पूर्णांक  ext4_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *,
			 काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य व्योम ext4_evict_inode(काष्ठा inode *);
बाह्य व्योम ext4_clear_inode(काष्ठा inode *);
बाह्य पूर्णांक  ext4_file_getattr(काष्ठा user_namespace *, स्थिर काष्ठा path *,
			      काष्ठा kstat *, u32, अचिन्हित पूर्णांक);
बाह्य पूर्णांक  ext4_sync_inode(handle_t *, काष्ठा inode *);
बाह्य व्योम ext4_dirty_inode(काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक ext4_change_inode_journal_flag(काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक ext4_get_inode_loc(काष्ठा inode *, काष्ठा ext4_iloc *);
बाह्य पूर्णांक ext4_get_fc_inode_loc(काष्ठा super_block *sb, अचिन्हित दीर्घ ino,
			  काष्ठा ext4_iloc *iloc);
बाह्य पूर्णांक ext4_inode_attach_jinode(काष्ठा inode *inode);
बाह्य पूर्णांक ext4_can_truncate(काष्ठा inode *inode);
बाह्य पूर्णांक ext4_truncate(काष्ठा inode *);
बाह्य पूर्णांक ext4_अवरोध_layouts(काष्ठा inode *);
बाह्य पूर्णांक ext4_punch_hole(काष्ठा inode *inode, loff_t offset, loff_t length);
बाह्य व्योम ext4_set_inode_flags(काष्ठा inode *, bool init);
बाह्य पूर्णांक ext4_alloc_da_blocks(काष्ठा inode *inode);
बाह्य व्योम ext4_set_aops(काष्ठा inode *inode);
बाह्य पूर्णांक ext4_ग_लिखोpage_trans_blocks(काष्ठा inode *);
बाह्य पूर्णांक ext4_chunk_trans_blocks(काष्ठा inode *, पूर्णांक nrblocks);
बाह्य पूर्णांक ext4_zero_partial_blocks(handle_t *handle, काष्ठा inode *inode,
			     loff_t lstart, loff_t lend);
बाह्य vm_fault_t ext4_page_mkग_लिखो(काष्ठा vm_fault *vmf);
बाह्य vm_fault_t ext4_filemap_fault(काष्ठा vm_fault *vmf);
बाह्य qमाप_प्रकार *ext4_get_reserved_space(काष्ठा inode *inode);
बाह्य पूर्णांक ext4_get_projid(काष्ठा inode *inode, kprojid_t *projid);
बाह्य व्योम ext4_da_release_space(काष्ठा inode *inode, पूर्णांक to_मुक्त);
बाह्य व्योम ext4_da_update_reserve_space(काष्ठा inode *inode,
					पूर्णांक used, पूर्णांक quota_claim);
बाह्य पूर्णांक ext4_issue_zeroout(काष्ठा inode *inode, ext4_lblk_t lblk,
			      ext4_fsblk_t pblk, ext4_lblk_t len);

/* indirect.c */
बाह्य पूर्णांक ext4_ind_map_blocks(handle_t *handle, काष्ठा inode *inode,
				काष्ठा ext4_map_blocks *map, पूर्णांक flags);
बाह्य पूर्णांक ext4_ind_trans_blocks(काष्ठा inode *inode, पूर्णांक nrblocks);
बाह्य व्योम ext4_ind_truncate(handle_t *, काष्ठा inode *inode);
बाह्य पूर्णांक ext4_ind_हटाओ_space(handle_t *handle, काष्ठा inode *inode,
				 ext4_lblk_t start, ext4_lblk_t end);

/* ioctl.c */
बाह्य दीर्घ ext4_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
बाह्य दीर्घ ext4_compat_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
पूर्णांक ext4_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa);
पूर्णांक ext4_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
बाह्य व्योम ext4_reset_inode_seed(काष्ठा inode *inode);

/* migrate.c */
बाह्य पूर्णांक ext4_ext_migrate(काष्ठा inode *);
बाह्य पूर्णांक ext4_ind_migrate(काष्ठा inode *inode);

/* namei.c */
बाह्य पूर्णांक ext4_init_new_dir(handle_t *handle, काष्ठा inode *dir,
			     काष्ठा inode *inode);
बाह्य पूर्णांक ext4_dirblock_csum_verअगरy(काष्ठा inode *inode,
				     काष्ठा buffer_head *bh);
बाह्य पूर्णांक ext4_orphan_add(handle_t *, काष्ठा inode *);
बाह्य पूर्णांक ext4_orphan_del(handle_t *, काष्ठा inode *);
बाह्य पूर्णांक ext4_htree_fill_tree(काष्ठा file *dir_file, __u32 start_hash,
				__u32 start_minor_hash, __u32 *next_hash);
बाह्य पूर्णांक ext4_search_dir(काष्ठा buffer_head *bh,
			   अक्षर *search_buf,
			   पूर्णांक buf_size,
			   काष्ठा inode *dir,
			   काष्ठा ext4_filename *fname,
			   अचिन्हित पूर्णांक offset,
			   काष्ठा ext4_dir_entry_2 **res_dir);
बाह्य पूर्णांक ext4_generic_delete_entry(काष्ठा inode *dir,
				     काष्ठा ext4_dir_entry_2 *de_del,
				     काष्ठा buffer_head *bh,
				     व्योम *entry_buf,
				     पूर्णांक buf_size,
				     पूर्णांक csum_size);
बाह्य bool ext4_empty_dir(काष्ठा inode *inode);

/* resize.c */
बाह्य व्योम ext4_kvमुक्त_array_rcu(व्योम *to_मुक्त);
बाह्य पूर्णांक ext4_group_add(काष्ठा super_block *sb,
				काष्ठा ext4_new_group_data *input);
बाह्य पूर्णांक ext4_group_extend(काष्ठा super_block *sb,
				काष्ठा ext4_super_block *es,
				ext4_fsblk_t n_blocks_count);
बाह्य पूर्णांक ext4_resize_fs(काष्ठा super_block *sb, ext4_fsblk_t n_blocks_count);

/* super.c */
बाह्य काष्ठा buffer_head *ext4_sb_bपढ़ो(काष्ठा super_block *sb,
					 sector_t block, पूर्णांक op_flags);
बाह्य काष्ठा buffer_head *ext4_sb_bपढ़ो_unmovable(काष्ठा super_block *sb,
						   sector_t block);
बाह्य व्योम ext4_पढ़ो_bh_noरुको(काष्ठा buffer_head *bh, पूर्णांक op_flags,
				bh_end_io_t *end_io);
बाह्य पूर्णांक ext4_पढ़ो_bh(काष्ठा buffer_head *bh, पूर्णांक op_flags,
			bh_end_io_t *end_io);
बाह्य पूर्णांक ext4_पढ़ो_bh_lock(काष्ठा buffer_head *bh, पूर्णांक op_flags, bool रुको);
बाह्य व्योम ext4_sb_bपढ़ोahead_unmovable(काष्ठा super_block *sb, sector_t block);
बाह्य पूर्णांक ext4_seq_options_show(काष्ठा seq_file *seq, व्योम *offset);
बाह्य पूर्णांक ext4_calculate_overhead(काष्ठा super_block *sb);
बाह्य व्योम ext4_superblock_csum_set(काष्ठा super_block *sb);
बाह्य पूर्णांक ext4_alloc_flex_bg_array(काष्ठा super_block *sb,
				    ext4_group_t ngroup);
बाह्य स्थिर अक्षर *ext4_decode_error(काष्ठा super_block *sb, पूर्णांक त्रुटि_सं,
				     अक्षर nbuf[16]);
बाह्य व्योम ext4_mark_group_biपंचांगap_corrupted(काष्ठा super_block *sb,
					     ext4_group_t block_group,
					     अचिन्हित पूर्णांक flags);

बाह्य __म_लिखो(7, 8)
व्योम __ext4_error(काष्ठा super_block *, स्थिर अक्षर *, अचिन्हित पूर्णांक, bool,
		  पूर्णांक, __u64, स्थिर अक्षर *, ...);
बाह्य __म_लिखो(6, 7)
व्योम __ext4_error_inode(काष्ठा inode *, स्थिर अक्षर *, अचिन्हित पूर्णांक,
			ext4_fsblk_t, पूर्णांक, स्थिर अक्षर *, ...);
बाह्य __म_लिखो(5, 6)
व्योम __ext4_error_file(काष्ठा file *, स्थिर अक्षर *, अचिन्हित पूर्णांक, ext4_fsblk_t,
		     स्थिर अक्षर *, ...);
बाह्य व्योम __ext4_std_error(काष्ठा super_block *, स्थिर अक्षर *,
			     अचिन्हित पूर्णांक, पूर्णांक);
बाह्य __म_लिखो(4, 5)
व्योम __ext4_warning(काष्ठा super_block *, स्थिर अक्षर *, अचिन्हित पूर्णांक,
		    स्थिर अक्षर *, ...);
बाह्य __म_लिखो(4, 5)
व्योम __ext4_warning_inode(स्थिर काष्ठा inode *inode, स्थिर अक्षर *function,
			  अचिन्हित पूर्णांक line, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(3, 4)
व्योम __ext4_msg(काष्ठा super_block *, स्थिर अक्षर *, स्थिर अक्षर *, ...);
बाह्य व्योम __dump_mmp_msg(काष्ठा super_block *, काष्ठा mmp_काष्ठा *mmp,
			   स्थिर अक्षर *, अचिन्हित पूर्णांक, स्थिर अक्षर *);
बाह्य __म_लिखो(7, 8)
व्योम __ext4_grp_locked_error(स्थिर अक्षर *, अचिन्हित पूर्णांक,
			     काष्ठा super_block *, ext4_group_t,
			     अचिन्हित दीर्घ, ext4_fsblk_t,
			     स्थिर अक्षर *, ...);

#घोषणा EXT4_ERROR_INODE(inode, fmt, a...) \
	ext4_error_inode((inode), __func__, __LINE__, 0, (fmt), ## a)

#घोषणा EXT4_ERROR_INODE_ERR(inode, err, fmt, a...)			\
	__ext4_error_inode((inode), __func__, __LINE__, 0, (err), (fmt), ## a)

#घोषणा ext4_error_inode_block(inode, block, err, fmt, a...)		\
	__ext4_error_inode((inode), __func__, __LINE__, (block), (err),	\
			   (fmt), ## a)

#घोषणा EXT4_ERROR_खाता(file, block, fmt, a...)				\
	ext4_error_file((file), __func__, __LINE__, (block), (fmt), ## a)

#घोषणा ext4_पात(sb, err, fmt, a...)					\
	__ext4_error((sb), __func__, __LINE__, true, (err), 0, (fmt), ## a)

#अगर_घोषित CONFIG_PRINTK

#घोषणा ext4_error_inode(inode, func, line, block, fmt, ...)		\
	__ext4_error_inode(inode, func, line, block, 0, fmt, ##__VA_ARGS__)
#घोषणा ext4_error_inode_err(inode, func, line, block, err, fmt, ...)	\
	__ext4_error_inode((inode), (func), (line), (block), 		\
			   (err), (fmt), ##__VA_ARGS__)
#घोषणा ext4_error_file(file, func, line, block, fmt, ...)		\
	__ext4_error_file(file, func, line, block, fmt, ##__VA_ARGS__)
#घोषणा ext4_error(sb, fmt, ...)					\
	__ext4_error((sb), __func__, __LINE__, false, 0, 0, (fmt),	\
		##__VA_ARGS__)
#घोषणा ext4_error_err(sb, err, fmt, ...)				\
	__ext4_error((sb), __func__, __LINE__, false, (err), 0, (fmt),	\
		##__VA_ARGS__)
#घोषणा ext4_warning(sb, fmt, ...)					\
	__ext4_warning(sb, __func__, __LINE__, fmt, ##__VA_ARGS__)
#घोषणा ext4_warning_inode(inode, fmt, ...)				\
	__ext4_warning_inode(inode, __func__, __LINE__, fmt, ##__VA_ARGS__)
#घोषणा ext4_msg(sb, level, fmt, ...)				\
	__ext4_msg(sb, level, fmt, ##__VA_ARGS__)
#घोषणा dump_mmp_msg(sb, mmp, msg)					\
	__dump_mmp_msg(sb, mmp, __func__, __LINE__, msg)
#घोषणा ext4_grp_locked_error(sb, grp, ino, block, fmt, ...)		\
	__ext4_grp_locked_error(__func__, __LINE__, sb, grp, ino, block, \
				fmt, ##__VA_ARGS__)

#अन्यथा

#घोषणा ext4_error_inode(inode, func, line, block, fmt, ...)		\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);					\
	__ext4_error_inode(inode, "", 0, block, 0, " ");		\
पूर्ण जबतक (0)
#घोषणा ext4_error_inode_err(inode, func, line, block, err, fmt, ...)	\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);					\
	__ext4_error_inode(inode, "", 0, block, err, " ");		\
पूर्ण जबतक (0)
#घोषणा ext4_error_file(file, func, line, block, fmt, ...)		\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);					\
	__ext4_error_file(file, "", 0, block, " ");			\
पूर्ण जबतक (0)
#घोषणा ext4_error(sb, fmt, ...)					\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);					\
	__ext4_error(sb, "", 0, false, 0, 0, " ");			\
पूर्ण जबतक (0)
#घोषणा ext4_error_err(sb, err, fmt, ...)				\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);					\
	__ext4_error(sb, "", 0, false, err, 0, " ");			\
पूर्ण जबतक (0)
#घोषणा ext4_warning(sb, fmt, ...)					\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);					\
	__ext4_warning(sb, "", 0, " ");					\
पूर्ण जबतक (0)
#घोषणा ext4_warning_inode(inode, fmt, ...)				\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);					\
	__ext4_warning_inode(inode, "", 0, " ");			\
पूर्ण जबतक (0)
#घोषणा ext4_msg(sb, level, fmt, ...)					\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);					\
	__ext4_msg(sb, "", " ");					\
पूर्ण जबतक (0)
#घोषणा dump_mmp_msg(sb, mmp, msg)					\
	__dump_mmp_msg(sb, mmp, "", 0, "")
#घोषणा ext4_grp_locked_error(sb, grp, ino, block, fmt, ...)		\
करो अणु									\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__);				\
	__ext4_grp_locked_error("", 0, sb, grp, ino, block, " ");	\
पूर्ण जबतक (0)

#पूर्ण_अगर

बाह्य ext4_fsblk_t ext4_block_biपंचांगap(काष्ठा super_block *sb,
				      काष्ठा ext4_group_desc *bg);
बाह्य ext4_fsblk_t ext4_inode_biपंचांगap(काष्ठा super_block *sb,
				      काष्ठा ext4_group_desc *bg);
बाह्य ext4_fsblk_t ext4_inode_table(काष्ठा super_block *sb,
				     काष्ठा ext4_group_desc *bg);
बाह्य __u32 ext4_मुक्त_group_clusters(काष्ठा super_block *sb,
				      काष्ठा ext4_group_desc *bg);
बाह्य __u32 ext4_मुक्त_inodes_count(काष्ठा super_block *sb,
				 काष्ठा ext4_group_desc *bg);
बाह्य __u32 ext4_used_dirs_count(काष्ठा super_block *sb,
				काष्ठा ext4_group_desc *bg);
बाह्य __u32 ext4_itable_unused_count(काष्ठा super_block *sb,
				   काष्ठा ext4_group_desc *bg);
बाह्य व्योम ext4_block_biपंचांगap_set(काष्ठा super_block *sb,
				  काष्ठा ext4_group_desc *bg, ext4_fsblk_t blk);
बाह्य व्योम ext4_inode_biपंचांगap_set(काष्ठा super_block *sb,
				  काष्ठा ext4_group_desc *bg, ext4_fsblk_t blk);
बाह्य व्योम ext4_inode_table_set(काष्ठा super_block *sb,
				 काष्ठा ext4_group_desc *bg, ext4_fsblk_t blk);
बाह्य व्योम ext4_मुक्त_group_clusters_set(काष्ठा super_block *sb,
					 काष्ठा ext4_group_desc *bg,
					 __u32 count);
बाह्य व्योम ext4_मुक्त_inodes_set(काष्ठा super_block *sb,
				काष्ठा ext4_group_desc *bg, __u32 count);
बाह्य व्योम ext4_used_dirs_set(काष्ठा super_block *sb,
				काष्ठा ext4_group_desc *bg, __u32 count);
बाह्य व्योम ext4_itable_unused_set(काष्ठा super_block *sb,
				   काष्ठा ext4_group_desc *bg, __u32 count);
बाह्य पूर्णांक ext4_group_desc_csum_verअगरy(काष्ठा super_block *sb, __u32 group,
				       काष्ठा ext4_group_desc *gdp);
बाह्य व्योम ext4_group_desc_csum_set(काष्ठा super_block *sb, __u32 group,
				     काष्ठा ext4_group_desc *gdp);
बाह्य पूर्णांक ext4_रेजिस्टर_li_request(काष्ठा super_block *sb,
				    ext4_group_t first_not_zeroed);

अटल अंतरभूत पूर्णांक ext4_has_metadata_csum(काष्ठा super_block *sb)
अणु
	WARN_ON_ONCE(ext4_has_feature_metadata_csum(sb) &&
		     !EXT4_SB(sb)->s_chksum_driver);

	वापस ext4_has_feature_metadata_csum(sb) &&
	       (EXT4_SB(sb)->s_chksum_driver != शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_has_group_desc_csum(काष्ठा super_block *sb)
अणु
	वापस ext4_has_feature_gdt_csum(sb) || ext4_has_metadata_csum(sb);
पूर्ण

#घोषणा ext4_पढ़ो_incompat_64bit_val(es, name) \
	(((es)->s_feature_incompat & cpu_to_le32(EXT4_FEATURE_INCOMPAT_64BIT) \
		? (ext4_fsblk_t)le32_to_cpu(es->name##_hi) << 32 : 0) | \
		le32_to_cpu(es->name##_lo))

अटल अंतरभूत ext4_fsblk_t ext4_blocks_count(काष्ठा ext4_super_block *es)
अणु
	वापस ext4_पढ़ो_incompat_64bit_val(es, s_blocks_count);
पूर्ण

अटल अंतरभूत ext4_fsblk_t ext4_r_blocks_count(काष्ठा ext4_super_block *es)
अणु
	वापस ext4_पढ़ो_incompat_64bit_val(es, s_r_blocks_count);
पूर्ण

अटल अंतरभूत ext4_fsblk_t ext4_मुक्त_blocks_count(काष्ठा ext4_super_block *es)
अणु
	वापस ext4_पढ़ो_incompat_64bit_val(es, s_मुक्त_blocks_count);
पूर्ण

अटल अंतरभूत व्योम ext4_blocks_count_set(काष्ठा ext4_super_block *es,
					 ext4_fsblk_t blk)
अणु
	es->s_blocks_count_lo = cpu_to_le32((u32)blk);
	es->s_blocks_count_hi = cpu_to_le32(blk >> 32);
पूर्ण

अटल अंतरभूत व्योम ext4_मुक्त_blocks_count_set(काष्ठा ext4_super_block *es,
					      ext4_fsblk_t blk)
अणु
	es->s_मुक्त_blocks_count_lo = cpu_to_le32((u32)blk);
	es->s_मुक्त_blocks_count_hi = cpu_to_le32(blk >> 32);
पूर्ण

अटल अंतरभूत व्योम ext4_r_blocks_count_set(काष्ठा ext4_super_block *es,
					   ext4_fsblk_t blk)
अणु
	es->s_r_blocks_count_lo = cpu_to_le32((u32)blk);
	es->s_r_blocks_count_hi = cpu_to_le32(blk >> 32);
पूर्ण

अटल अंतरभूत loff_t ext4_isize(काष्ठा super_block *sb,
				काष्ठा ext4_inode *raw_inode)
अणु
	अगर (ext4_has_feature_largedir(sb) ||
	    S_ISREG(le16_to_cpu(raw_inode->i_mode)))
		वापस ((loff_t)le32_to_cpu(raw_inode->i_size_high) << 32) |
			le32_to_cpu(raw_inode->i_size_lo);

	वापस (loff_t) le32_to_cpu(raw_inode->i_size_lo);
पूर्ण

अटल अंतरभूत व्योम ext4_isize_set(काष्ठा ext4_inode *raw_inode, loff_t i_size)
अणु
	raw_inode->i_size_lo = cpu_to_le32(i_size);
	raw_inode->i_size_high = cpu_to_le32(i_size >> 32);
पूर्ण

अटल अंतरभूत
काष्ठा ext4_group_info *ext4_get_group_info(काष्ठा super_block *sb,
					    ext4_group_t group)
अणु
	 काष्ठा ext4_group_info **grp_info;
	 दीर्घ indexv, indexh;
	 BUG_ON(group >= EXT4_SB(sb)->s_groups_count);
	 indexv = group >> (EXT4_DESC_PER_BLOCK_BITS(sb));
	 indexh = group & ((EXT4_DESC_PER_BLOCK(sb)) - 1);
	 grp_info = sbi_array_rcu_deref(EXT4_SB(sb), s_group_info, indexv);
	 वापस grp_info[indexh];
पूर्ण

/*
 * Reading s_groups_count requires using smp_rmb() afterwards.  See
 * the locking protocol करोcumented in the comments of ext4_group_add()
 * in resize.c
 */
अटल अंतरभूत ext4_group_t ext4_get_groups_count(काष्ठा super_block *sb)
अणु
	ext4_group_t	ngroups = EXT4_SB(sb)->s_groups_count;

	smp_rmb();
	वापस ngroups;
पूर्ण

अटल अंतरभूत ext4_group_t ext4_flex_group(काष्ठा ext4_sb_info *sbi,
					     ext4_group_t block_group)
अणु
	वापस block_group >> sbi->s_log_groups_per_flex;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ext4_flex_bg_size(काष्ठा ext4_sb_info *sbi)
अणु
	वापस 1 << sbi->s_log_groups_per_flex;
पूर्ण

#घोषणा ext4_std_error(sb, त्रुटि_सं)				\
करो अणु								\
	अगर ((त्रुटि_सं))						\
		__ext4_std_error((sb), __func__, __LINE__, (त्रुटि_सं));	\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_SMP
/* Each CPU can accumulate percpu_counter_batch clusters in their local
 * counters. So we need to make sure we have मुक्त clusters more
 * than percpu_counter_batch  * nr_cpu_ids. Also add a winकरोw of 4 बार.
 */
#घोषणा EXT4_FREECLUSTERS_WATERMARK (4 * (percpu_counter_batch * nr_cpu_ids))
#अन्यथा
#घोषणा EXT4_FREECLUSTERS_WATERMARK 0
#पूर्ण_अगर

/* Update i_disksize. Requires i_mutex to aव्योम races with truncate */
अटल अंतरभूत व्योम ext4_update_i_disksize(काष्ठा inode *inode, loff_t newsize)
अणु
	WARN_ON_ONCE(S_ISREG(inode->i_mode) &&
		     !inode_is_locked(inode));
	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	अगर (newsize > EXT4_I(inode)->i_disksize)
		WRITE_ONCE(EXT4_I(inode)->i_disksize, newsize);
	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
पूर्ण

/* Update i_size, i_disksize. Requires i_mutex to aव्योम races with truncate */
अटल अंतरभूत पूर्णांक ext4_update_inode_size(काष्ठा inode *inode, loff_t newsize)
अणु
	पूर्णांक changed = 0;

	अगर (newsize > inode->i_size) अणु
		i_size_ग_लिखो(inode, newsize);
		changed = 1;
	पूर्ण
	अगर (newsize > EXT4_I(inode)->i_disksize) अणु
		ext4_update_i_disksize(inode, newsize);
		changed |= 2;
	पूर्ण
	वापस changed;
पूर्ण

पूर्णांक ext4_update_disksize_beक्रमe_punch(काष्ठा inode *inode, loff_t offset,
				      loff_t len);

काष्ठा ext4_group_info अणु
	अचिन्हित दीर्घ   bb_state;
#अगर_घोषित AGGRESSIVE_CHECK
	अचिन्हित दीर्घ	bb_check_counter;
#पूर्ण_अगर
	काष्ठा rb_root  bb_मुक्त_root;
	ext4_grpblk_t	bb_first_मुक्त;	/* first मुक्त block */
	ext4_grpblk_t	bb_मुक्त;	/* total मुक्त blocks */
	ext4_grpblk_t	bb_fragments;	/* nr of मुक्तspace fragments */
	ext4_grpblk_t	bb_largest_मुक्त_order;/* order of largest frag in BG */
	ext4_group_t	bb_group;	/* Group number */
	काष्ठा          list_head bb_pपुनः_स्मृति_list;
#अगर_घोषित DOUBLE_CHECK
	व्योम            *bb_biपंचांगap;
#पूर्ण_अगर
	काष्ठा rw_semaphore alloc_sem;
	काष्ठा rb_node	bb_avg_fragment_size_rb;
	काष्ठा list_head bb_largest_मुक्त_order_node;
	ext4_grpblk_t	bb_counters[];	/* Nr of मुक्त घातer-of-two-block
					 * regions, index is order.
					 * bb_counters[3] = 5 means
					 * 5 मुक्त 8-block regions. */
पूर्ण;

#घोषणा EXT4_GROUP_INFO_NEED_INIT_BIT		0
#घोषणा EXT4_GROUP_INFO_WAS_TRIMMED_BIT		1
#घोषणा EXT4_GROUP_INFO_BBITMAP_CORRUPT_BIT	2
#घोषणा EXT4_GROUP_INFO_IBITMAP_CORRUPT_BIT	3
#घोषणा EXT4_GROUP_INFO_BBITMAP_CORRUPT		\
	(1 << EXT4_GROUP_INFO_BBITMAP_CORRUPT_BIT)
#घोषणा EXT4_GROUP_INFO_IBITMAP_CORRUPT		\
	(1 << EXT4_GROUP_INFO_IBITMAP_CORRUPT_BIT)
#घोषणा EXT4_GROUP_INFO_BBITMAP_READ_BIT	4

#घोषणा EXT4_MB_GRP_NEED_INIT(grp)	\
	(test_bit(EXT4_GROUP_INFO_NEED_INIT_BIT, &((grp)->bb_state)))
#घोषणा EXT4_MB_GRP_BBITMAP_CORRUPT(grp)	\
	(test_bit(EXT4_GROUP_INFO_BBITMAP_CORRUPT_BIT, &((grp)->bb_state)))
#घोषणा EXT4_MB_GRP_IBITMAP_CORRUPT(grp)	\
	(test_bit(EXT4_GROUP_INFO_IBITMAP_CORRUPT_BIT, &((grp)->bb_state)))

#घोषणा EXT4_MB_GRP_WAS_TRIMMED(grp)	\
	(test_bit(EXT4_GROUP_INFO_WAS_TRIMMED_BIT, &((grp)->bb_state)))
#घोषणा EXT4_MB_GRP_SET_TRIMMED(grp)	\
	(set_bit(EXT4_GROUP_INFO_WAS_TRIMMED_BIT, &((grp)->bb_state)))
#घोषणा EXT4_MB_GRP_CLEAR_TRIMMED(grp)	\
	(clear_bit(EXT4_GROUP_INFO_WAS_TRIMMED_BIT, &((grp)->bb_state)))
#घोषणा EXT4_MB_GRP_TEST_AND_SET_READ(grp)	\
	(test_and_set_bit(EXT4_GROUP_INFO_BBITMAP_READ_BIT, &((grp)->bb_state)))

#घोषणा EXT4_MAX_CONTENTION		8
#घोषणा EXT4_CONTENTION_THRESHOLD	2

अटल अंतरभूत spinlock_t *ext4_group_lock_ptr(काष्ठा super_block *sb,
					      ext4_group_t group)
अणु
	वापस bgl_lock_ptr(EXT4_SB(sb)->s_blockgroup_lock, group);
पूर्ण

/*
 * Returns true अगर the fileप्रणाली is busy enough that attempts to
 * access the block group locks has run पूर्णांकo contention.
 */
अटल अंतरभूत पूर्णांक ext4_fs_is_busy(काष्ठा ext4_sb_info *sbi)
अणु
	वापस (atomic_पढ़ो(&sbi->s_lock_busy) > EXT4_CONTENTION_THRESHOLD);
पूर्ण

अटल अंतरभूत व्योम ext4_lock_group(काष्ठा super_block *sb, ext4_group_t group)
अणु
	spinlock_t *lock = ext4_group_lock_ptr(sb, group);
	अगर (spin_trylock(lock))
		/*
		 * We're able to grab the lock right away, so drop the
		 * lock contention counter.
		 */
		atomic_add_unless(&EXT4_SB(sb)->s_lock_busy, -1, 0);
	अन्यथा अणु
		/*
		 * The lock is busy, so bump the contention counter,
		 * and then रुको on the spin lock.
		 */
		atomic_add_unless(&EXT4_SB(sb)->s_lock_busy, 1,
				  EXT4_MAX_CONTENTION);
		spin_lock(lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ext4_unlock_group(काष्ठा super_block *sb,
					ext4_group_t group)
अणु
	spin_unlock(ext4_group_lock_ptr(sb, group));
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल अंतरभूत bool ext4_quota_capable(काष्ठा super_block *sb)
अणु
	वापस (test_opt(sb, QUOTA) || ext4_has_feature_quota(sb));
पूर्ण

अटल अंतरभूत bool ext4_is_quota_journalled(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	वापस (ext4_has_feature_quota(sb) ||
		sbi->s_qf_names[USRQUOTA] || sbi->s_qf_names[GRPQUOTA]);
पूर्ण
#पूर्ण_अगर

/*
 * Block validity checking
 */
#घोषणा ext4_check_indirect_blockref(inode, bh)				\
	ext4_check_blockref(__func__, __LINE__, inode,			\
			    (__le32 *)(bh)->b_data,			\
			    EXT4_ADDR_PER_BLOCK((inode)->i_sb))

#घोषणा ext4_ind_check_inode(inode)					\
	ext4_check_blockref(__func__, __LINE__, inode,			\
			    EXT4_I(inode)->i_data,			\
			    EXT4_Nसूची_BLOCKS)

/*
 * Inodes and files operations
 */

/* dir.c */
बाह्य स्थिर काष्ठा file_operations ext4_dir_operations;

/* file.c */
बाह्य स्थिर काष्ठा inode_operations ext4_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations ext4_file_operations;
बाह्य loff_t ext4_llseek(काष्ठा file *file, loff_t offset, पूर्णांक origin);

/* अंतरभूत.c */
बाह्य पूर्णांक ext4_get_max_अंतरभूत_size(काष्ठा inode *inode);
बाह्य पूर्णांक ext4_find_अंतरभूत_data_nolock(काष्ठा inode *inode);
बाह्य पूर्णांक ext4_init_अंतरभूत_data(handle_t *handle, काष्ठा inode *inode,
				 अचिन्हित पूर्णांक len);
बाह्य पूर्णांक ext4_destroy_अंतरभूत_data(handle_t *handle, काष्ठा inode *inode);

बाह्य पूर्णांक ext4_पढ़ोpage_अंतरभूत(काष्ठा inode *inode, काष्ठा page *page);
बाह्य पूर्णांक ext4_try_to_ग_लिखो_अंतरभूत_data(काष्ठा address_space *mapping,
					 काष्ठा inode *inode,
					 loff_t pos, अचिन्हित len,
					 अचिन्हित flags,
					 काष्ठा page **pagep);
बाह्य पूर्णांक ext4_ग_लिखो_अंतरभूत_data_end(काष्ठा inode *inode,
				      loff_t pos, अचिन्हित len,
				      अचिन्हित copied,
				      काष्ठा page *page);
बाह्य काष्ठा buffer_head *
ext4_journalled_ग_लिखो_अंतरभूत_data(काष्ठा inode *inode,
				  अचिन्हित len,
				  काष्ठा page *page);
बाह्य पूर्णांक ext4_da_ग_लिखो_अंतरभूत_data_begin(काष्ठा address_space *mapping,
					   काष्ठा inode *inode,
					   loff_t pos, अचिन्हित len,
					   अचिन्हित flags,
					   काष्ठा page **pagep,
					   व्योम **fsdata);
बाह्य पूर्णांक ext4_da_ग_लिखो_अंतरभूत_data_end(काष्ठा inode *inode, loff_t pos,
					 अचिन्हित len, अचिन्हित copied,
					 काष्ठा page *page);
बाह्य पूर्णांक ext4_try_add_अंतरभूत_entry(handle_t *handle,
				     काष्ठा ext4_filename *fname,
				     काष्ठा inode *dir, काष्ठा inode *inode);
बाह्य पूर्णांक ext4_try_create_अंतरभूत_dir(handle_t *handle,
				      काष्ठा inode *parent,
				      काष्ठा inode *inode);
बाह्य पूर्णांक ext4_पढ़ो_अंतरभूत_dir(काष्ठा file *filp,
				काष्ठा dir_context *ctx,
				पूर्णांक *has_अंतरभूत_data);
बाह्य पूर्णांक ext4_अंतरभूतdir_to_tree(काष्ठा file *dir_file,
				  काष्ठा inode *dir, ext4_lblk_t block,
				  काष्ठा dx_hash_info *hinfo,
				  __u32 start_hash, __u32 start_minor_hash,
				  पूर्णांक *has_अंतरभूत_data);
बाह्य काष्ठा buffer_head *ext4_find_अंतरभूत_entry(काष्ठा inode *dir,
					काष्ठा ext4_filename *fname,
					काष्ठा ext4_dir_entry_2 **res_dir,
					पूर्णांक *has_अंतरभूत_data);
बाह्य पूर्णांक ext4_delete_अंतरभूत_entry(handle_t *handle,
				    काष्ठा inode *dir,
				    काष्ठा ext4_dir_entry_2 *de_del,
				    काष्ठा buffer_head *bh,
				    पूर्णांक *has_अंतरभूत_data);
बाह्य bool empty_अंतरभूत_dir(काष्ठा inode *dir, पूर्णांक *has_अंतरभूत_data);
बाह्य काष्ठा buffer_head *ext4_get_first_अंतरभूत_block(काष्ठा inode *inode,
					काष्ठा ext4_dir_entry_2 **parent_de,
					पूर्णांक *retval);
बाह्य पूर्णांक ext4_अंतरभूत_data_fiemap(काष्ठा inode *inode,
				   काष्ठा fiemap_extent_info *fieinfo,
				   पूर्णांक *has_अंतरभूत, __u64 start, __u64 len);

काष्ठा iomap;
बाह्य पूर्णांक ext4_अंतरभूत_data_iomap(काष्ठा inode *inode, काष्ठा iomap *iomap);

बाह्य पूर्णांक ext4_अंतरभूत_data_truncate(काष्ठा inode *inode, पूर्णांक *has_अंतरभूत);

बाह्य पूर्णांक ext4_convert_अंतरभूत_data(काष्ठा inode *inode);

अटल अंतरभूत पूर्णांक ext4_has_अंतरभूत_data(काष्ठा inode *inode)
अणु
	वापस ext4_test_inode_flag(inode, EXT4_INODE_INLINE_DATA) &&
	       EXT4_I(inode)->i_अंतरभूत_off;
पूर्ण

/* namei.c */
बाह्य स्थिर काष्ठा inode_operations ext4_dir_inode_operations;
बाह्य स्थिर काष्ठा inode_operations ext4_special_inode_operations;
बाह्य काष्ठा dentry *ext4_get_parent(काष्ठा dentry *child);
बाह्य काष्ठा ext4_dir_entry_2 *ext4_init_करोt_करोtकरोt(काष्ठा inode *inode,
				 काष्ठा ext4_dir_entry_2 *de,
				 पूर्णांक blocksize, पूर्णांक csum_size,
				 अचिन्हित पूर्णांक parent_ino, पूर्णांक करोtकरोt_real_len);
बाह्य व्योम ext4_initialize_dirent_tail(काष्ठा buffer_head *bh,
					अचिन्हित पूर्णांक blocksize);
बाह्य पूर्णांक ext4_handle_dirty_dirblock(handle_t *handle, काष्ठा inode *inode,
				      काष्ठा buffer_head *bh);
बाह्य पूर्णांक __ext4_unlink(handle_t *handle, काष्ठा inode *dir, स्थिर काष्ठा qstr *d_name,
			 काष्ठा inode *inode);
बाह्य पूर्णांक __ext4_link(काष्ठा inode *dir, काष्ठा inode *inode,
		       काष्ठा dentry *dentry);

#घोषणा S_SHIFT 12
अटल स्थिर अचिन्हित अक्षर ext4_type_by_mode[(S_IFMT >> S_SHIFT) + 1] = अणु
	[S_IFREG >> S_SHIFT]	= EXT4_FT_REG_खाता,
	[S_IFसूची >> S_SHIFT]	= EXT4_FT_सूची,
	[S_IFCHR >> S_SHIFT]	= EXT4_FT_CHRDEV,
	[S_IFBLK >> S_SHIFT]	= EXT4_FT_BLKDEV,
	[S_IFIFO >> S_SHIFT]	= EXT4_FT_FIFO,
	[S_IFSOCK >> S_SHIFT]	= EXT4_FT_SOCK,
	[S_IFLNK >> S_SHIFT]	= EXT4_FT_SYMLINK,
पूर्ण;

अटल अंतरभूत व्योम ext4_set_de_type(काष्ठा super_block *sb,
				काष्ठा ext4_dir_entry_2 *de,
				umode_t mode) अणु
	अगर (ext4_has_feature_filetype(sb))
		de->file_type = ext4_type_by_mode[(mode & S_IFMT)>>S_SHIFT];
पूर्ण

/* पढ़ोpages.c */
बाह्य पूर्णांक ext4_mpage_पढ़ोpages(काष्ठा inode *inode,
		काष्ठा पढ़ोahead_control *rac, काष्ठा page *page);
बाह्य पूर्णांक __init ext4_init_post_पढ़ो_processing(व्योम);
बाह्य व्योम ext4_निकास_post_पढ़ो_processing(व्योम);

/* symlink.c */
बाह्य स्थिर काष्ठा inode_operations ext4_encrypted_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations ext4_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations ext4_fast_symlink_inode_operations;

/* sysfs.c */
बाह्य पूर्णांक ext4_रेजिस्टर_sysfs(काष्ठा super_block *sb);
बाह्य व्योम ext4_unरेजिस्टर_sysfs(काष्ठा super_block *sb);
बाह्य पूर्णांक __init ext4_init_sysfs(व्योम);
बाह्य व्योम ext4_निकास_sysfs(व्योम);

/* block_validity */
बाह्य व्योम ext4_release_प्रणाली_zone(काष्ठा super_block *sb);
बाह्य पूर्णांक ext4_setup_प्रणाली_zone(काष्ठा super_block *sb);
बाह्य पूर्णांक __init ext4_init_प्रणाली_zone(व्योम);
बाह्य व्योम ext4_निकास_प्रणाली_zone(व्योम);
बाह्य पूर्णांक ext4_inode_block_valid(काष्ठा inode *inode,
				  ext4_fsblk_t start_blk,
				  अचिन्हित पूर्णांक count);
बाह्य पूर्णांक ext4_check_blockref(स्थिर अक्षर *, अचिन्हित पूर्णांक,
			       काष्ठा inode *, __le32 *, अचिन्हित पूर्णांक);

/* extents.c */
काष्ठा ext4_ext_path;
काष्ठा ext4_extent;

/*
 * Maximum number of logical blocks in a file; ext4_extent's ee_block is
 * __le32.
 */
#घोषणा EXT_MAX_BLOCKS	0xffffffff

बाह्य व्योम ext4_ext_tree_init(handle_t *handle, काष्ठा inode *inode);
बाह्य पूर्णांक ext4_ext_index_trans_blocks(काष्ठा inode *inode, पूर्णांक extents);
बाह्य पूर्णांक ext4_ext_map_blocks(handle_t *handle, काष्ठा inode *inode,
			       काष्ठा ext4_map_blocks *map, पूर्णांक flags);
बाह्य पूर्णांक ext4_ext_truncate(handle_t *, काष्ठा inode *);
बाह्य पूर्णांक ext4_ext_हटाओ_space(काष्ठा inode *inode, ext4_lblk_t start,
				 ext4_lblk_t end);
बाह्य व्योम ext4_ext_init(काष्ठा super_block *);
बाह्य व्योम ext4_ext_release(काष्ठा super_block *);
बाह्य दीर्घ ext4_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset,
			  loff_t len);
बाह्य पूर्णांक ext4_convert_unwritten_extents(handle_t *handle, काष्ठा inode *inode,
					  loff_t offset, sमाप_प्रकार len);
बाह्य पूर्णांक ext4_convert_unwritten_io_end_vec(handle_t *handle,
					     ext4_io_end_t *io_end);
बाह्य पूर्णांक ext4_map_blocks(handle_t *handle, काष्ठा inode *inode,
			   काष्ठा ext4_map_blocks *map, पूर्णांक flags);
बाह्य पूर्णांक ext4_ext_calc_credits_क्रम_single_extent(काष्ठा inode *inode,
						   पूर्णांक num,
						   काष्ठा ext4_ext_path *path);
बाह्य पूर्णांक ext4_ext_insert_extent(handle_t *, काष्ठा inode *,
				  काष्ठा ext4_ext_path **,
				  काष्ठा ext4_extent *, पूर्णांक);
बाह्य काष्ठा ext4_ext_path *ext4_find_extent(काष्ठा inode *, ext4_lblk_t,
					      काष्ठा ext4_ext_path **,
					      पूर्णांक flags);
बाह्य व्योम ext4_ext_drop_refs(काष्ठा ext4_ext_path *);
बाह्य पूर्णांक ext4_ext_check_inode(काष्ठा inode *inode);
बाह्य ext4_lblk_t ext4_ext_next_allocated_block(काष्ठा ext4_ext_path *path);
बाह्य पूर्णांक ext4_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
			__u64 start, __u64 len);
बाह्य पूर्णांक ext4_get_es_cache(काष्ठा inode *inode,
			     काष्ठा fiemap_extent_info *fieinfo,
			     __u64 start, __u64 len);
बाह्य पूर्णांक ext4_ext_precache(काष्ठा inode *inode);
बाह्य पूर्णांक ext4_swap_extents(handle_t *handle, काष्ठा inode *inode1,
				काष्ठा inode *inode2, ext4_lblk_t lblk1,
			     ext4_lblk_t lblk2,  ext4_lblk_t count,
			     पूर्णांक mark_unwritten,पूर्णांक *err);
बाह्य पूर्णांक ext4_clu_mapped(काष्ठा inode *inode, ext4_lblk_t lclu);
बाह्य पूर्णांक ext4_datasem_ensure_credits(handle_t *handle, काष्ठा inode *inode,
				       पूर्णांक check_cred, पूर्णांक restart_cred,
				       पूर्णांक revoke_cred);
बाह्य व्योम ext4_ext_replay_shrink_inode(काष्ठा inode *inode, ext4_lblk_t end);
बाह्य पूर्णांक ext4_ext_replay_set_iblocks(काष्ठा inode *inode);
बाह्य पूर्णांक ext4_ext_replay_update_ex(काष्ठा inode *inode, ext4_lblk_t start,
		पूर्णांक len, पूर्णांक unwritten, ext4_fsblk_t pblk);
बाह्य पूर्णांक ext4_ext_clear_bb(काष्ठा inode *inode);


/* move_extent.c */
बाह्य व्योम ext4_द्विगुन_करोwn_ग_लिखो_data_sem(काष्ठा inode *first,
					    काष्ठा inode *second);
बाह्य व्योम ext4_द्विगुन_up_ग_लिखो_data_sem(काष्ठा inode *orig_inode,
					  काष्ठा inode *करोnor_inode);
बाह्य पूर्णांक ext4_move_extents(काष्ठा file *o_filp, काष्ठा file *d_filp,
			     __u64 start_orig, __u64 start_करोnor,
			     __u64 len, __u64 *moved_len);

/* page-io.c */
बाह्य पूर्णांक __init ext4_init_pageio(व्योम);
बाह्य व्योम ext4_निकास_pageio(व्योम);
बाह्य ext4_io_end_t *ext4_init_io_end(काष्ठा inode *inode, gfp_t flags);
बाह्य ext4_io_end_t *ext4_get_io_end(ext4_io_end_t *io_end);
बाह्य पूर्णांक ext4_put_io_end(ext4_io_end_t *io_end);
बाह्य व्योम ext4_put_io_end_defer(ext4_io_end_t *io_end);
बाह्य व्योम ext4_io_submit_init(काष्ठा ext4_io_submit *io,
				काष्ठा ग_लिखोback_control *wbc);
बाह्य व्योम ext4_end_io_rsv_work(काष्ठा work_काष्ठा *work);
बाह्य व्योम ext4_io_submit(काष्ठा ext4_io_submit *io);
बाह्य पूर्णांक ext4_bio_ग_लिखो_page(काष्ठा ext4_io_submit *io,
			       काष्ठा page *page,
			       पूर्णांक len,
			       bool keep_toग_लिखो);
बाह्य काष्ठा ext4_io_end_vec *ext4_alloc_io_end_vec(ext4_io_end_t *io_end);
बाह्य काष्ठा ext4_io_end_vec *ext4_last_io_end_vec(ext4_io_end_t *io_end);

/* mmp.c */
बाह्य पूर्णांक ext4_multi_mount_protect(काष्ठा super_block *, ext4_fsblk_t);

/* verity.c */
बाह्य स्थिर काष्ठा fsverity_operations ext4_verityops;

/*
 * Add new method to test whether block and inode biपंचांगaps are properly
 * initialized. With uninit_bg पढ़ोing the block from disk is not enough
 * to mark the biपंचांगap uptodate. We need to also zero-out the biपंचांगap
 */
#घोषणा BH_BITMAP_UPTODATE BH_JBDPrivateStart

अटल अंतरभूत पूर्णांक biपंचांगap_uptodate(काष्ठा buffer_head *bh)
अणु
	वापस (buffer_uptodate(bh) &&
			test_bit(BH_BITMAP_UPTODATE, &(bh)->b_state));
पूर्ण
अटल अंतरभूत व्योम set_biपंचांगap_uptodate(काष्ठा buffer_head *bh)
अणु
	set_bit(BH_BITMAP_UPTODATE, &(bh)->b_state);
पूर्ण

#घोषणा in_range(b, first, len)	((b) >= (first) && (b) <= (first) + (len) - 1)

/* For ioend & aio unwritten conversion रुको queues */
#घोषणा EXT4_WQ_HASH_SZ		37
#घोषणा ext4_ioend_wq(v)   (&ext4__ioend_wq[((अचिन्हित दीर्घ)(v)) %\
					    EXT4_WQ_HASH_SZ])
बाह्य रुको_queue_head_t ext4__ioend_wq[EXT4_WQ_HASH_SZ];

बाह्य पूर्णांक ext4_resize_begin(काष्ठा super_block *sb);
बाह्य व्योम ext4_resize_end(काष्ठा super_block *sb);

अटल अंतरभूत व्योम ext4_set_io_unwritten_flag(काष्ठा inode *inode,
					      काष्ठा ext4_io_end *io_end)
अणु
	अगर (!(io_end->flag & EXT4_IO_END_UNWRITTEN)) अणु
		io_end->flag |= EXT4_IO_END_UNWRITTEN;
		atomic_inc(&EXT4_I(inode)->i_unwritten);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ext4_clear_io_unwritten_flag(ext4_io_end_t *io_end)
अणु
	काष्ठा inode *inode = io_end->inode;

	अगर (io_end->flag & EXT4_IO_END_UNWRITTEN) अणु
		io_end->flag &= ~EXT4_IO_END_UNWRITTEN;
		/* Wake up anyone रुकोing on unwritten extent conversion */
		अगर (atomic_dec_and_test(&EXT4_I(inode)->i_unwritten))
			wake_up_all(ext4_ioend_wq(inode));
	पूर्ण
पूर्ण

बाह्य स्थिर काष्ठा iomap_ops ext4_iomap_ops;
बाह्य स्थिर काष्ठा iomap_ops ext4_iomap_overग_लिखो_ops;
बाह्य स्थिर काष्ठा iomap_ops ext4_iomap_report_ops;

अटल अंतरभूत पूर्णांक ext4_buffer_uptodate(काष्ठा buffer_head *bh)
अणु
	/*
	 * If the buffer has the ग_लिखो error flag, we have failed
	 * to ग_लिखो out data in the block.  In this  हाल, we करोn't
	 * have to पढ़ो the block because we may पढ़ो the old data
	 * successfully.
	 */
	अगर (!buffer_uptodate(bh) && buffer_ग_लिखो_io_error(bh))
		set_buffer_uptodate(bh);
	वापस buffer_uptodate(bh);
पूर्ण

#पूर्ण_अगर	/* __KERNEL__ */

#घोषणा EFSBADCRC	EBADMSG		/* Bad CRC detected */
#घोषणा EFSCORRUPTED	EUCLEAN		/* Fileप्रणाली is corrupted */

#पूर्ण_अगर	/* _EXT4_H */
