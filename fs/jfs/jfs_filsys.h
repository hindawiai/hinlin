<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2003
 */
#अगर_अघोषित _H_JFS_FILSYS
#घोषणा _H_JFS_FILSYS

/*
 *	jfs_filsys.h
 *
 * file प्रणाली (implementation-dependent) स्थिरants
 *
 * refer to <सीमा.स> क्रम प्रणाली wide implementation-dependent स्थिरants
 */

/*
 *	 file प्रणाली option (superblock flag)
 */

/* directory option */
#घोषणा JFS_UNICODE	0x00000001	/* unicode name */

/* mount समय flags क्रम error handling */
#घोषणा JFS_ERR_REMOUNT_RO 0x00000002	/* remount पढ़ो-only */
#घोषणा JFS_ERR_CONTINUE   0x00000004	/* जारी */
#घोषणा JFS_ERR_PANIC      0x00000008	/* panic */

/* Quota support */
#घोषणा	JFS_USRQUOTA	0x00000010
#घोषणा	JFS_GRPQUOTA	0x00000020

/* mount समय flag to disable journaling to disk */
#घोषणा JFS_NOINTEGRITY 0x00000040

/* mount समय flag to enable TRIM to ssd disks */
#घोषणा JFS_DISCARD     0x00000080

/* commit option */
#घोषणा	JFS_COMMIT	0x00000f00	/* commit option mask */
#घोषणा	JFS_GROUPCOMMIT	0x00000100	/* group (of 1) commit */
#घोषणा	JFS_LAZYCOMMIT	0x00000200	/* lazy commit */
#घोषणा	JFS_TMPFS	0x00000400	/* temporary file प्रणाली -
					 * करो not log/commit:
					 * Never implemented
					 */

/* log logical volume option */
#घोषणा	JFS_INLINELOG	0x00000800	/* अंतरभूत log within file प्रणाली */
#घोषणा JFS_INLINEMOVE	0x00001000	/* अंतरभूत log being moved */

/* Secondary aggregate inode table */
#घोषणा JFS_BAD_SAIT	0x00010000	/* current secondary ait is bad */

/* sparse regular file support */
#घोषणा JFS_SPARSE	0x00020000	/* sparse regular file */

/* DASD Limits		F226941 */
#घोषणा JFS_DASD_ENABLED 0x00040000	/* DASD limits enabled */
#घोषणा	JFS_DASD_PRIME	0x00080000	/* Prime DASD usage on boot */

/* big endian flag */
#घोषणा	JFS_SWAP_BYTES	0x00100000	/* running on big endian computer */

/* Directory index */
#घोषणा JFS_सूची_INDEX	0x00200000	/* Persistent index क्रम */

/* platक्रमm options */
#घोषणा JFS_LINUX	0x10000000	/* Linux support */
#घोषणा JFS_DFS		0x20000000	/* DCE DFS LFS support */
/*	Never implemented */

#घोषणा JFS_OS2		0x40000000	/* OS/2 support */
/*	हाल-insensitive name/directory support */

#घोषणा JFS_AIX		0x80000000	/* AIX support */

/*
 *	buffer cache configuration
 */
/* page size */
#अगर_घोषित PSIZE
#अघोषित PSIZE
#पूर्ण_अगर
#घोषणा	PSIZE		4096	/* page size (in byte) */
#घोषणा	L2PSIZE		12	/* log2(PSIZE) */
#घोषणा	POFFSET		4095	/* offset within page */

/* buffer page size */
#घोषणा BPSIZE	PSIZE

/*
 *	fs fundamental size
 *
 * PSIZE >= file प्रणाली block size >= PBSIZE >= DISIZE
 */
#घोषणा	PBSIZE		512	/* physical block size (in byte) */
#घोषणा	L2PBSIZE	9	/* log2(PBSIZE) */

#घोषणा DISIZE		512	/* on-disk inode size (in byte) */
#घोषणा L2DISIZE	9	/* log2(DISIZE) */

#घोषणा IDATASIZE	256	/* inode अंतरभूत data size */
#घोषणा	IXATTRSIZE	128	/* inode अंतरभूत extended attribute size */

#घोषणा XTPAGE_SIZE	4096
#घोषणा log2_PAGESIZE	12

#घोषणा IAG_SIZE	4096
#घोषणा IAG_EXTENT_SIZE 4096
#घोषणा	INOSPERIAG	4096	/* number of disk inodes per iag */
#घोषणा	L2INOSPERIAG	12	/* l2 number of disk inodes per iag */
#घोषणा INOSPEREXT	32	/* number of disk inode per extent */
#घोषणा L2INOSPEREXT	5	/* l2 number of disk inode per extent */
#घोषणा	IXSIZE		(DISIZE * INOSPEREXT)	/* inode extent size */
#घोषणा	INOSPERPAGE	8	/* number of disk inodes per 4K page */
#घोषणा	L2INOSPERPAGE	3	/* log2(INOSPERPAGE) */

#घोषणा	IAGFREELIST_LWM	64

#घोषणा INODE_EXTENT_SIZE	IXSIZE	/* inode extent size */
#घोषणा NUM_INODE_PER_EXTENT	INOSPEREXT
#घोषणा NUM_INODE_PER_IAG	INOSPERIAG

#घोषणा MINBLOCKSIZE		512
#घोषणा MAXBLOCKSIZE		4096
#घोषणा	MAXखाताSIZE		((s64)1 << 52)

#घोषणा JFS_LINK_MAX		0xffffffff

/* Minimum number of bytes supported क्रम a JFS partition */
#घोषणा MINJFS			(0x1000000)
#घोषणा MINJFSTEXT		"16"

/*
 * file प्रणाली block size -> physical block size
 */
#घोषणा LBOFFSET(x)	((x) & (PBSIZE - 1))
#घोषणा LBNUMBER(x)	((x) >> L2PBSIZE)
#घोषणा	LBLK2PBLK(sb,b)	((b) << (sb->s_blocksize_bits - L2PBSIZE))
#घोषणा	PBLK2LBLK(sb,b)	((b) >> (sb->s_blocksize_bits - L2PBSIZE))
/* size in byte -> last page number */
#घोषणा	SIZE2PN(size)	( ((s64)((size) - 1)) >> (L2PSIZE) )
/* size in byte -> last file प्रणाली block number */
#घोषणा	SIZE2BN(size, l2bsize) ( ((s64)((size) - 1)) >> (l2bsize) )

/*
 * fixed physical block address (physical block size = 512 byte)
 *
 * NOTE: since we can't guarantee a physical block size of 512 bytes the use of
 *	 these macros should be हटाओd and the byte offset macros used instead.
 */
#घोषणा SUPER1_B	64	/* primary superblock */
#घोषणा	AIMAP_B		(SUPER1_B + 8)	/* 1st extent of aggregate inode map */
#घोषणा	AITBL_B		(AIMAP_B + 16)	/*
					 * 1st extent of aggregate inode table
					 */
#घोषणा	SUPER2_B	(AITBL_B + 32)	/* 2ndary superblock pbn */
#घोषणा	BMAP_B		(SUPER2_B + 8)	/* block allocation map */

/*
 * SIZE_OF_SUPER defines the total amount of space reserved on disk क्रम the
 * superblock.  This is not the same as the superblock काष्ठाure, since all of
 * this space is not currently being used.
 */
#घोषणा SIZE_OF_SUPER	PSIZE

/*
 * SIZE_OF_AG_TABLE defines the amount of space reserved to hold the AG table
 */
#घोषणा SIZE_OF_AG_TABLE	PSIZE

/*
 * SIZE_OF_MAP_PAGE defines the amount of disk space reserved क्रम each page of
 * the inode allocation map (to hold iag)
 */
#घोषणा SIZE_OF_MAP_PAGE	PSIZE

/*
 * fixed byte offset address
 */
#घोषणा SUPER1_OFF	0x8000	/* primary superblock */
#घोषणा AIMAP_OFF	(SUPER1_OFF + SIZE_OF_SUPER)
					/*
					 * Control page of aggregate inode map
					 * followed by 1st extent of map
					 */
#घोषणा AITBL_OFF	(AIMAP_OFF + (SIZE_OF_MAP_PAGE << 1))
					/*
					 * 1st extent of aggregate inode table
					 */
#घोषणा SUPER2_OFF	(AITBL_OFF + INODE_EXTENT_SIZE)
					/*
					 * secondary superblock
					 */
#घोषणा BMAP_OFF	(SUPER2_OFF + SIZE_OF_SUPER)
					/*
					 * block allocation map
					 */

/*
 * The following macro is used to indicate the number of reserved disk blocks at
 * the front of an aggregate, in terms of physical blocks.  This value is
 * currently defined to be 32K.  This turns out to be the same as the primary
 * superblock's address, since it directly follows the reserved blocks.
 */
#घोषणा AGGR_RSVD_BLOCKS	SUPER1_B

/*
 * The following macro is used to indicate the number of reserved bytes at the
 * front of an aggregate.  This value is currently defined to be 32K.  This
 * turns out to be the same as the primary superblock's byte offset, since it
 * directly follows the reserved blocks.
 */
#घोषणा AGGR_RSVD_BYTES	SUPER1_OFF

/*
 * The following macro defines the byte offset क्रम the first inode extent in
 * the aggregate inode table.  This allows us to find the self inode to find the
 * rest of the table.  Currently this value is 44K.
 */
#घोषणा AGGR_INODE_TABLE_START	AITBL_OFF

/*
 *	fixed reserved inode number
 */
/* aggregate inode */
#घोषणा AGGR_RESERVED_I	0	/* aggregate inode (reserved) */
#घोषणा	AGGREGATE_I	1	/* aggregate inode map inode */
#घोषणा	BMAP_I		2	/* aggregate block allocation map inode */
#घोषणा	LOG_I		3	/* aggregate अंतरभूत log inode */
#घोषणा BADBLOCK_I	4	/* aggregate bad block inode */
#घोषणा	खाताSYSTEM_I	16	/* 1st/only fileset inode in ait:
				 * fileset inode map inode
				 */

/* per fileset inode */
#घोषणा खाताSET_RSVD_I	0	/* fileset inode (reserved) */
#घोषणा खाताSET_EXT_I	1	/* fileset inode extension */
#घोषणा	ROOT_I		2	/* fileset root inode */
#घोषणा ACL_I		3	/* fileset ACL inode */

#घोषणा खाताSET_OBJECT_I 4	/* the first fileset inode available क्रम a file
				 * or directory or link...
				 */
#घोषणा FIRST_खाताSET_INO 16	/* the first aggregate inode which describes
				 * an inode.  (To fsck this is also the first
				 * inode in part 2 of the agg inode table.)
				 */

/*
 *	directory configuration
 */
#घोषणा JFS_NAME_MAX	255
#घोषणा JFS_PATH_MAX	BPSIZE


/*
 *	file प्रणाली state (superblock state)
 */
#घोषणा FM_CLEAN 0x00000000	/* file प्रणाली is unmounted and clean */
#घोषणा FM_MOUNT 0x00000001	/* file प्रणाली is mounted cleanly */
#घोषणा FM_सूचीTY 0x00000002	/* file प्रणाली was not unmounted and clean
				 * when mounted or
				 * commit failure occurred जबतक being mounted:
				 * fsck() must be run to repair
				 */
#घोषणा	FM_LOGREDO 0x00000004	/* log based recovery (logreकरो()) failed:
				 * fsck() must be run to repair
				 */
#घोषणा	FM_EXTENDFS 0x00000008	/* file प्रणाली extendfs() in progress */
#घोषणा	FM_STATE_MAX 0x0000000f	/* max value of s_state */

#पूर्ण_अगर				/* _H_JFS_FILSYS */
