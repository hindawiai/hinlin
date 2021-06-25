<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ocfs2_fs.h
 *
 * On-disk काष्ठाures क्रम OCFS2.
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित _OCFS2_FS_H
#घोषणा _OCFS2_FS_H

#समावेश <linux/magic.h>

/* Version */
#घोषणा OCFS2_MAJOR_REV_LEVEL		0
#घोषणा OCFS2_MINOR_REV_LEVEL          	90

/*
 * An OCFS2 volume starts this way:
 * Sector 0: Valid ocfs1_vol_disk_hdr that cleanly fails to mount OCFS.
 * Sector 1: Valid ocfs1_vol_label that cleanly fails to mount OCFS.
 * Block OCFS2_SUPER_BLOCK_BLKNO: OCFS2 superblock.
 *
 * All other काष्ठाures are found from the superblock inक्रमmation.
 *
 * OCFS2_SUPER_BLOCK_BLKNO is in blocks, not sectors.  eg, क्रम a
 * blocksize of 2K, it is 4096 bytes पूर्णांकo disk.
 */
#घोषणा OCFS2_SUPER_BLOCK_BLKNO		2

/*
 * Cluster size limits. The maximum is kept arbitrarily at 1 MB, and could
 * grow अगर needed.
 */
#घोषणा OCFS2_MIN_CLUSTERSIZE		4096
#घोषणा OCFS2_MAX_CLUSTERSIZE		1048576

/*
 * Blocks cannot be bigger than clusters, so the maximum blocksize is the
 * minimum cluster size.
 */
#घोषणा OCFS2_MIN_BLOCKSIZE		512
#घोषणा OCFS2_MAX_BLOCKSIZE		OCFS2_MIN_CLUSTERSIZE

/* Object signatures */
#घोषणा OCFS2_SUPER_BLOCK_SIGNATURE	"OCFSV2"
#घोषणा OCFS2_INODE_SIGNATURE		"INODE01"
#घोषणा OCFS2_EXTENT_BLOCK_SIGNATURE	"EXBLK01"
#घोषणा OCFS2_GROUP_DESC_SIGNATURE      "GROUP01"
#घोषणा OCFS2_XATTR_BLOCK_SIGNATURE	"XATTR01"
#घोषणा OCFS2_सूची_TRAILER_SIGNATURE	"DIRTRL1"
#घोषणा OCFS2_DX_ROOT_SIGNATURE		"DXDIR01"
#घोषणा OCFS2_DX_LEAF_SIGNATURE		"DXLEAF1"
#घोषणा OCFS2_REFCOUNT_BLOCK_SIGNATURE	"REFCNT1"

/* Compatibility flags */
#घोषणा OCFS2_HAS_COMPAT_FEATURE(sb,mask)			\
	( OCFS2_SB(sb)->s_feature_compat & (mask) )
#घोषणा OCFS2_HAS_RO_COMPAT_FEATURE(sb,mask)			\
	( OCFS2_SB(sb)->s_feature_ro_compat & (mask) )
#घोषणा OCFS2_HAS_INCOMPAT_FEATURE(sb,mask)			\
	( OCFS2_SB(sb)->s_feature_incompat & (mask) )
#घोषणा OCFS2_SET_COMPAT_FEATURE(sb,mask)			\
	OCFS2_SB(sb)->s_feature_compat |= (mask)
#घोषणा OCFS2_SET_RO_COMPAT_FEATURE(sb,mask)			\
	OCFS2_SB(sb)->s_feature_ro_compat |= (mask)
#घोषणा OCFS2_SET_INCOMPAT_FEATURE(sb,mask)			\
	OCFS2_SB(sb)->s_feature_incompat |= (mask)
#घोषणा OCFS2_CLEAR_COMPAT_FEATURE(sb,mask)			\
	OCFS2_SB(sb)->s_feature_compat &= ~(mask)
#घोषणा OCFS2_CLEAR_RO_COMPAT_FEATURE(sb,mask)			\
	OCFS2_SB(sb)->s_feature_ro_compat &= ~(mask)
#घोषणा OCFS2_CLEAR_INCOMPAT_FEATURE(sb,mask)			\
	OCFS2_SB(sb)->s_feature_incompat &= ~(mask)

#घोषणा OCFS2_FEATURE_COMPAT_SUPP	(OCFS2_FEATURE_COMPAT_BACKUP_SB	\
					 | OCFS2_FEATURE_COMPAT_JBD2_SB)
#घोषणा OCFS2_FEATURE_INCOMPAT_SUPP	(OCFS2_FEATURE_INCOMPAT_LOCAL_MOUNT \
					 | OCFS2_FEATURE_INCOMPAT_SPARSE_ALLOC \
					 | OCFS2_FEATURE_INCOMPAT_INLINE_DATA \
					 | OCFS2_FEATURE_INCOMPAT_EXTENDED_SLOT_MAP \
					 | OCFS2_FEATURE_INCOMPAT_USERSPACE_STACK \
					 | OCFS2_FEATURE_INCOMPAT_XATTR \
					 | OCFS2_FEATURE_INCOMPAT_META_ECC \
					 | OCFS2_FEATURE_INCOMPAT_INDEXED_सूचीS \
					 | OCFS2_FEATURE_INCOMPAT_REFCOUNT_TREE \
					 | OCFS2_FEATURE_INCOMPAT_DISCONTIG_BG	\
					 | OCFS2_FEATURE_INCOMPAT_CLUSTERINFO \
					 | OCFS2_FEATURE_INCOMPAT_APPEND_DIO)
#घोषणा OCFS2_FEATURE_RO_COMPAT_SUPP	(OCFS2_FEATURE_RO_COMPAT_UNWRITTEN \
					 | OCFS2_FEATURE_RO_COMPAT_USRQUOTA \
					 | OCFS2_FEATURE_RO_COMPAT_GRPQUOTA)

/*
 * Heartbeat-only devices are missing journals and other files.  The
 * fileप्रणाली driver can't load them, but the library can.  Never put
 * this in OCFS2_FEATURE_INCOMPAT_SUPP, *ever*.
 */
#घोषणा OCFS2_FEATURE_INCOMPAT_HEARTBEAT_DEV	0x0002

/*
 * tunefs sets this incompat flag beक्रमe starting the resize and clears it
 * at the end. This flag protects users from inadvertently mounting the fs
 * after an पातed run without fsck-ing.
 */
#घोषणा OCFS2_FEATURE_INCOMPAT_RESIZE_INPROG    0x0004

/* Used to denote a non-clustered volume */
#घोषणा OCFS2_FEATURE_INCOMPAT_LOCAL_MOUNT	0x0008

/* Support क्रम sparse allocation in b-trees */
#घोषणा OCFS2_FEATURE_INCOMPAT_SPARSE_ALLOC	0x0010

/*
 * Tunefs sets this incompat flag beक्रमe starting an operation which
 * would require cleanup on पात. This is करोne to protect users from
 * inadvertently mounting the fs after an पातed run without
 * fsck-ing.
 *
 * s_tunefs_flags on the super block describes precisely which
 * operations were in progress.
 */
#घोषणा OCFS2_FEATURE_INCOMPAT_TUNEFS_INPROG	0x0020

/* Support क्रम data packed पूर्णांकo inode blocks */
#घोषणा OCFS2_FEATURE_INCOMPAT_INLINE_DATA	0x0040

/*
 * Support क्रम alternate, userspace cluster stacks.  If set, the superblock
 * field s_cluster_info contains a tag क्रम the alternate stack in use as
 * well as the name of the cluster being joined.
 * mount.ocfs2 must pass in a matching stack name.
 *
 * If not set, the classic stack will be used.  This is compatbile with
 * all older versions.
 */
#घोषणा OCFS2_FEATURE_INCOMPAT_USERSPACE_STACK	0x0080

/* Support क्रम the extended slot map */
#घोषणा OCFS2_FEATURE_INCOMPAT_EXTENDED_SLOT_MAP 0x100

/* Support क्रम extended attributes */
#घोषणा OCFS2_FEATURE_INCOMPAT_XATTR		0x0200

/* Support क्रम indexed directores */
#घोषणा OCFS2_FEATURE_INCOMPAT_INDEXED_सूचीS	0x0400

/* Metadata checksum and error correction */
#घोषणा OCFS2_FEATURE_INCOMPAT_META_ECC		0x0800

/* Refcount tree support */
#घोषणा OCFS2_FEATURE_INCOMPAT_REFCOUNT_TREE	0x1000

/* Discontiguous block groups */
#घोषणा OCFS2_FEATURE_INCOMPAT_DISCONTIG_BG	0x2000

/*
 * Incompat bit to indicate useable clusterinfo with stackflags क्रम all
 * cluster stacks (userspace adnd o2cb). If this bit is set,
 * INCOMPAT_USERSPACE_STACK becomes superfluous and thus should not be set.
 */
#घोषणा OCFS2_FEATURE_INCOMPAT_CLUSTERINFO	0x4000

/*
 * Append Direct IO support
 */
#घोषणा OCFS2_FEATURE_INCOMPAT_APPEND_DIO	0x8000

/*
 * backup superblock flag is used to indicate that this volume
 * has backup superblocks.
 */
#घोषणा OCFS2_FEATURE_COMPAT_BACKUP_SB		0x0001

/*
 * The fileप्रणाली will correctly handle journal feature bits.
 */
#घोषणा OCFS2_FEATURE_COMPAT_JBD2_SB		0x0002

/*
 * Unwritten extents support.
 */
#घोषणा OCFS2_FEATURE_RO_COMPAT_UNWRITTEN	0x0001

/*
 * Maपूर्णांकain quota inक्रमmation क्रम this fileप्रणाली
 */
#घोषणा OCFS2_FEATURE_RO_COMPAT_USRQUOTA	0x0002
#घोषणा OCFS2_FEATURE_RO_COMPAT_GRPQUOTA	0x0004


/* The byte offset of the first backup block will be 1G.
 * The following will be 4G, 16G, 64G, 256G and 1T.
 */
#घोषणा OCFS2_BACKUP_SB_START			1 << 30

/* the max backup superblock nums */
#घोषणा OCFS2_MAX_BACKUP_SUPERBLOCKS	6

/*
 * Flags on ocfs2_super_block.s_tunefs_flags
 */
#घोषणा OCFS2_TUNEFS_INPROG_REMOVE_SLOT		0x0001	/* Removing slots */

/*
 * Flags on ocfs2_dinode.i_flags
 */
#घोषणा OCFS2_VALID_FL		(0x00000001)	/* Inode is valid */
#घोषणा OCFS2_UNUSED2_FL	(0x00000002)
#घोषणा OCFS2_ORPHANED_FL	(0x00000004)	/* On the orphan list */
#घोषणा OCFS2_UNUSED3_FL	(0x00000008)
/* System inode flags */
#घोषणा OCFS2_SYSTEM_FL		(0x00000010)	/* System inode */
#घोषणा OCFS2_SUPER_BLOCK_FL	(0x00000020)	/* Super block */
#घोषणा OCFS2_LOCAL_ALLOC_FL	(0x00000040)	/* Slot local alloc biपंचांगap */
#घोषणा OCFS2_BITMAP_FL		(0x00000080)	/* Allocation biपंचांगap */
#घोषणा OCFS2_JOURNAL_FL	(0x00000100)	/* Slot local journal */
#घोषणा OCFS2_HEARTBEAT_FL	(0x00000200)	/* Heartbeat area */
#घोषणा OCFS2_CHAIN_FL		(0x00000400)	/* Chain allocator */
#घोषणा OCFS2_DEALLOC_FL	(0x00000800)	/* Truncate log */
#घोषणा OCFS2_QUOTA_FL		(0x00001000)	/* Quota file */
#घोषणा OCFS2_DIO_ORPHANED_FL	(0X00002000)	/* On the orphan list especially
						 * क्रम dio */

/*
 * Flags on ocfs2_dinode.i_dyn_features
 *
 * These can change much more often than i_flags. When adding flags,
 * keep in mind that i_dyn_features is only 16 bits wide.
 */
#घोषणा OCFS2_INLINE_DATA_FL	(0x0001)	/* Data stored in inode block */
#घोषणा OCFS2_HAS_XATTR_FL	(0x0002)
#घोषणा OCFS2_INLINE_XATTR_FL	(0x0004)
#घोषणा OCFS2_INDEXED_सूची_FL	(0x0008)
#घोषणा OCFS2_HAS_REFCOUNT_FL   (0x0010)

/* Inode attributes, keep in sync with EXT2 */
#घोषणा OCFS2_SECRM_FL			FS_SECRM_FL	/* Secure deletion */
#घोषणा OCFS2_UNRM_FL			FS_UNRM_FL	/* Undelete */
#घोषणा OCFS2_COMPR_FL			FS_COMPR_FL	/* Compress file */
#घोषणा OCFS2_SYNC_FL			FS_SYNC_FL	/* Synchronous updates */
#घोषणा OCFS2_IMMUTABLE_FL		FS_IMMUTABLE_FL	/* Immutable file */
#घोषणा OCFS2_APPEND_FL			FS_APPEND_FL	/* ग_लिखोs to file may only append */
#घोषणा OCFS2_NODUMP_FL			FS_NODUMP_FL	/* करो not dump file */
#घोषणा OCFS2_NOATIME_FL		FS_NOATIME_FL	/* करो not update aसमय */
/* Reserved क्रम compression usage... */
#घोषणा OCFS2_सूचीTY_FL			FS_सूचीTY_FL
#घोषणा OCFS2_COMPRBLK_FL		FS_COMPRBLK_FL	/* One or more compressed clusters */
#घोषणा OCFS2_NOCOMP_FL			FS_NOCOMP_FL	/* Don't compress */
#घोषणा OCFS2_ECOMPR_FL			FS_ECOMPR_FL	/* Compression error */
/* End compression flags --- maybe not all used */
#घोषणा OCFS2_BTREE_FL			FS_BTREE_FL	/* btree क्रमmat dir */
#घोषणा OCFS2_INDEX_FL			FS_INDEX_FL	/* hash-indexed directory */
#घोषणा OCFS2_IMAGIC_FL			FS_IMAGIC_FL	/* AFS directory */
#घोषणा OCFS2_JOURNAL_DATA_FL		FS_JOURNAL_DATA_FL /* Reserved क्रम ext3 */
#घोषणा OCFS2_NOTAIL_FL			FS_NOTAIL_FL	/* file tail should not be merged */
#घोषणा OCFS2_सूचीSYNC_FL		FS_सूचीSYNC_FL	/* dirsync behaviour (directories only) */
#घोषणा OCFS2_TOPसूची_FL			FS_TOPसूची_FL	/* Top of directory hierarchies*/
#घोषणा OCFS2_RESERVED_FL		FS_RESERVED_FL	/* reserved क्रम ext2 lib */

#घोषणा OCFS2_FL_VISIBLE		FS_FL_USER_VISIBLE	/* User visible flags */
#घोषणा OCFS2_FL_MODIFIABLE		FS_FL_USER_MODIFIABLE	/* User modअगरiable flags */

/*
 * Extent record flags (e_node.leaf.flags)
 */
#घोषणा OCFS2_EXT_UNWRITTEN		(0x01)	/* Extent is allocated but
						 * unwritten */
#घोषणा OCFS2_EXT_REFCOUNTED		(0x02)  /* Extent is reference
						 * counted in an associated
						 * refcount tree */

/*
 * Journal Flags (ocfs2_dinode.id1.journal1.i_flags)
 */
#घोषणा OCFS2_JOURNAL_सूचीTY_FL	(0x00000001)	/* Journal needs recovery */

/*
 * superblock s_state flags
 */
#घोषणा OCFS2_ERROR_FS		(0x00000001)	/* FS saw errors */

/* Limit of space in ocfs2_dir_entry */
#घोषणा OCFS2_MAX_खाताNAME_LEN		255

/* Maximum slots on an ocfs2 file प्रणाली */
#घोषणा OCFS2_MAX_SLOTS			255

/* Slot map indicator क्रम an empty slot */
#घोषणा OCFS2_INVALID_SLOT		((u16)-1)

#घोषणा OCFS2_VOL_UUID_LEN		16
#घोषणा OCFS2_MAX_VOL_LABEL_LEN		64

/* The cluster stack fields */
#घोषणा OCFS2_STACK_LABEL_LEN		4
#घोषणा OCFS2_CLUSTER_NAME_LEN		16

/* Classic (historically speaking) cluster stack */
#घोषणा OCFS2_CLASSIC_CLUSTER_STACK	"o2cb"

/* Journal limits (in bytes) */
#घोषणा OCFS2_MIN_JOURNAL_SIZE		(4 * 1024 * 1024)

/*
 * Inline extended attribute size (in bytes)
 * The value chosen should be aligned to 16 byte boundaries.
 */
#घोषणा OCFS2_MIN_XATTR_INLINE_SIZE     256

/*
 * Cluster info flags (ocfs2_cluster_info.ci_stackflags)
 */
#घोषणा OCFS2_CLUSTER_O2CB_GLOBAL_HEARTBEAT	(0x01)

काष्ठा ocfs2_प्रणाली_inode_info अणु
	अक्षर	*si_name;
	पूर्णांक	si_अगरlags;
	पूर्णांक	si_mode;
पूर्ण;

/* System file index */
क्रमागत अणु
	BAD_BLOCK_SYSTEM_INODE = 0,
	GLOBAL_INODE_ALLOC_SYSTEM_INODE,
#घोषणा OCFS2_FIRST_ONLINE_SYSTEM_INODE GLOBAL_INODE_ALLOC_SYSTEM_INODE
	SLOT_MAP_SYSTEM_INODE,
	HEARTBEAT_SYSTEM_INODE,
	GLOBAL_BITMAP_SYSTEM_INODE,
	USER_QUOTA_SYSTEM_INODE,
	GROUP_QUOTA_SYSTEM_INODE,
#घोषणा OCFS2_LAST_GLOBAL_SYSTEM_INODE GROUP_QUOTA_SYSTEM_INODE
#घोषणा OCFS2_FIRST_LOCAL_SYSTEM_INODE ORPHAN_सूची_SYSTEM_INODE
	ORPHAN_सूची_SYSTEM_INODE,
	EXTENT_ALLOC_SYSTEM_INODE,
	INODE_ALLOC_SYSTEM_INODE,
	JOURNAL_SYSTEM_INODE,
	LOCAL_ALLOC_SYSTEM_INODE,
	TRUNCATE_LOG_SYSTEM_INODE,
	LOCAL_USER_QUOTA_SYSTEM_INODE,
	LOCAL_GROUP_QUOTA_SYSTEM_INODE,
#घोषणा OCFS2_LAST_LOCAL_SYSTEM_INODE LOCAL_GROUP_QUOTA_SYSTEM_INODE
	NUM_SYSTEM_INODES
पूर्ण;
#घोषणा NUM_GLOBAL_SYSTEM_INODES OCFS2_FIRST_LOCAL_SYSTEM_INODE
#घोषणा NUM_LOCAL_SYSTEM_INODES	\
		(NUM_SYSTEM_INODES - OCFS2_FIRST_LOCAL_SYSTEM_INODE)

अटल काष्ठा ocfs2_प्रणाली_inode_info ocfs2_प्रणाली_inodes[NUM_SYSTEM_INODES] = अणु
	/* Global प्रणाली inodes (single copy) */
	/* The first two are only used from userspace mfks/tunefs */
	[BAD_BLOCK_SYSTEM_INODE]		= अणु "bad_blocks", 0, S_IFREG | 0644 पूर्ण,
	[GLOBAL_INODE_ALLOC_SYSTEM_INODE] 	= अणु "global_inode_alloc", OCFS2_BITMAP_FL | OCFS2_CHAIN_FL, S_IFREG | 0644 पूर्ण,

	/* These are used by the running fileप्रणाली */
	[SLOT_MAP_SYSTEM_INODE]			= अणु "slot_map", 0, S_IFREG | 0644 पूर्ण,
	[HEARTBEAT_SYSTEM_INODE]		= अणु "heartbeat", OCFS2_HEARTBEAT_FL, S_IFREG | 0644 पूर्ण,
	[GLOBAL_BITMAP_SYSTEM_INODE]		= अणु "global_bitmap", 0, S_IFREG | 0644 पूर्ण,
	[USER_QUOTA_SYSTEM_INODE]		= अणु "aquota.user", OCFS2_QUOTA_FL, S_IFREG | 0644 पूर्ण,
	[GROUP_QUOTA_SYSTEM_INODE]		= अणु "aquota.group", OCFS2_QUOTA_FL, S_IFREG | 0644 पूर्ण,

	/* Slot-specअगरic प्रणाली inodes (one copy per slot) */
	[ORPHAN_सूची_SYSTEM_INODE]		= अणु "orphan_dir:%04d", 0, S_IFसूची | 0755 पूर्ण,
	[EXTENT_ALLOC_SYSTEM_INODE]		= अणु "extent_alloc:%04d", OCFS2_BITMAP_FL | OCFS2_CHAIN_FL, S_IFREG | 0644 पूर्ण,
	[INODE_ALLOC_SYSTEM_INODE]		= अणु "inode_alloc:%04d", OCFS2_BITMAP_FL | OCFS2_CHAIN_FL, S_IFREG | 0644 पूर्ण,
	[JOURNAL_SYSTEM_INODE]			= अणु "journal:%04d", OCFS2_JOURNAL_FL, S_IFREG | 0644 पूर्ण,
	[LOCAL_ALLOC_SYSTEM_INODE]		= अणु "local_alloc:%04d", OCFS2_BITMAP_FL | OCFS2_LOCAL_ALLOC_FL, S_IFREG | 0644 पूर्ण,
	[TRUNCATE_LOG_SYSTEM_INODE]		= अणु "truncate_log:%04d", OCFS2_DEALLOC_FL, S_IFREG | 0644 पूर्ण,
	[LOCAL_USER_QUOTA_SYSTEM_INODE]		= अणु "aquota.user:%04d", OCFS2_QUOTA_FL, S_IFREG | 0644 पूर्ण,
	[LOCAL_GROUP_QUOTA_SYSTEM_INODE]	= अणु "aquota.group:%04d", OCFS2_QUOTA_FL, S_IFREG | 0644 पूर्ण,
पूर्ण;

/* Parameter passed from mount.ocfs2 to module */
#घोषणा OCFS2_HB_NONE			"heartbeat=none"
#घोषणा OCFS2_HB_LOCAL			"heartbeat=local"
#घोषणा OCFS2_HB_GLOBAL			"heartbeat=global"

/*
 * OCFS2_सूची_PAD defines the directory entries boundaries
 *
 * NOTE: It must be a multiple of 4
 */
#घोषणा OCFS2_सूची_PAD			4
#घोषणा OCFS2_सूची_ROUND			(OCFS2_सूची_PAD - 1)
#घोषणा OCFS2_सूची_MEMBER_LEN 		दुरत्व(काष्ठा ocfs2_dir_entry, name)
#घोषणा OCFS2_सूची_REC_LEN(name_len)	(((name_len) + OCFS2_सूची_MEMBER_LEN + \
                                          OCFS2_सूची_ROUND) & \
					 ~OCFS2_सूची_ROUND)
#घोषणा OCFS2_सूची_MIN_REC_LEN	OCFS2_सूची_REC_LEN(1)

#घोषणा OCFS2_LINK_MAX		32000
#घोषणा	OCFS2_DX_LINK_MAX	((1U << 31) - 1U)
#घोषणा	OCFS2_LINKS_HI_SHIFT	16
#घोषणा	OCFS2_DX_ENTRIES_MAX	(0xffffffffU)


/*
 * Convenience casts
 */
#घोषणा OCFS2_RAW_SB(dinode)		(&((dinode)->id2.i_super))

/*
 * Block checking काष्ठाure.  This is used in metadata to validate the
 * contents.  If OCFS2_FEATURE_INCOMPAT_META_ECC is not set, it is all
 * zeros.
 */
काष्ठा ocfs2_block_check अणु
/*00*/	__le32 bc_crc32e;	/* 802.3 Ethernet II CRC32 */
	__le16 bc_ecc;		/* Single-error-correction parity vector.
				   This is a simple Hamming code dependent
				   on the blocksize.  OCFS2's maximum
				   blocksize, 4K, requires 16 parity bits,
				   so we fit in __le16. */
	__le16 bc_reserved1;
/*08*/
पूर्ण;

/*
 * On disk extent record क्रम OCFS2
 * It describes a range of clusters on disk.
 *
 * Length fields are भागided पूर्णांकo पूर्णांकerior and leaf node versions.
 * This leaves room क्रम a flags field (OCFS2_EXT_*) in the leaf nodes.
 */
काष्ठा ocfs2_extent_rec अणु
/*00*/	__le32 e_cpos;		/* Offset पूर्णांकo the file, in clusters */
	जोड़ अणु
		__le32 e_पूर्णांक_clusters; /* Clusters covered by all children */
		काष्ठा अणु
			__le16 e_leaf_clusters; /* Clusters covered by this
						   extent */
			__u8 e_reserved1;
			__u8 e_flags; /* Extent flags */
		पूर्ण;
	पूर्ण;
	__le64 e_blkno;		/* Physical disk offset, in blocks */
/*10*/
पूर्ण;

काष्ठा ocfs2_chain_rec अणु
	__le32 c_मुक्त;	/* Number of मुक्त bits in this chain. */
	__le32 c_total;	/* Number of total bits in this chain */
	__le64 c_blkno;	/* Physical disk offset (blocks) of 1st group */
पूर्ण;

काष्ठा ocfs2_truncate_rec अणु
	__le32 t_start;		/* 1st cluster in this log */
	__le32 t_clusters;	/* Number of total clusters covered */
पूर्ण;

/*
 * On disk extent list क्रम OCFS2 (node in the tree).  Note that this
 * is contained inside ocfs2_dinode or ocfs2_extent_block, so the
 * offsets are relative to ocfs2_dinode.id2.i_list or
 * ocfs2_extent_block.h_list, respectively.
 */
काष्ठा ocfs2_extent_list अणु
/*00*/	__le16 l_tree_depth;		/* Extent tree depth from this
					   poपूर्णांक.  0 means data extents
					   hang directly off this
					   header (a leaf)
					   NOTE: The high 8 bits cannot be
					   used - tree_depth is never that big.
					*/
	__le16 l_count;			/* Number of extent records */
	__le16 l_next_मुक्त_rec;		/* Next unused extent slot */
	__le16 l_reserved1;
	__le64 l_reserved2;		/* Pad to
					   माप(ocfs2_extent_rec) */
/*10*/	काष्ठा ocfs2_extent_rec l_recs[];	/* Extent records */
पूर्ण;

/*
 * On disk allocation chain list क्रम OCFS2.  Note that this is
 * contained inside ocfs2_dinode, so the offsets are relative to
 * ocfs2_dinode.id2.i_chain.
 */
काष्ठा ocfs2_chain_list अणु
/*00*/	__le16 cl_cpg;			/* Clusters per Block Group */
	__le16 cl_bpc;			/* Bits per cluster */
	__le16 cl_count;		/* Total chains in this list */
	__le16 cl_next_मुक्त_rec;	/* Next unused chain slot */
	__le64 cl_reserved1;
/*10*/	काष्ठा ocfs2_chain_rec cl_recs[];	/* Chain records */
पूर्ण;

/*
 * On disk deallocation log क्रम OCFS2.  Note that this is
 * contained inside ocfs2_dinode, so the offsets are relative to
 * ocfs2_dinode.id2.i_dealloc.
 */
काष्ठा ocfs2_truncate_log अणु
/*00*/	__le16 tl_count;		/* Total records in this log */
	__le16 tl_used;			/* Number of records in use */
	__le32 tl_reserved1;
/*08*/	काष्ठा ocfs2_truncate_rec tl_recs[];	/* Truncate records */
पूर्ण;

/*
 * On disk extent block (indirect block) क्रम OCFS2
 */
काष्ठा ocfs2_extent_block
अणु
/*00*/	__u8 h_signature[8];		/* Signature क्रम verअगरication */
	काष्ठा ocfs2_block_check h_check;	/* Error checking */
/*10*/	__le16 h_suballoc_slot;		/* Slot suballocator this
					   extent_header beदीर्घs to */
	__le16 h_suballoc_bit;		/* Bit offset in suballocator
					   block group */
	__le32 h_fs_generation;		/* Must match super block */
	__le64 h_blkno;			/* Offset on disk, in blocks */
/*20*/	__le64 h_suballoc_loc;		/* Suballocator block group this
					   eb beदीर्घs to.  Only valid
					   अगर allocated from a
					   discontiguous block group */
	__le64 h_next_leaf_blk;		/* Offset on disk, in blocks,
					   of next leaf header poपूर्णांकing
					   to data */
/*30*/	काष्ठा ocfs2_extent_list h_list;	/* Extent record list */
/* Actual on-disk size is one block */
पूर्ण;

/*
 * On disk slot map क्रम OCFS2.  This defines the contents of the "slot_map"
 * प्रणाली file.  A slot is valid अगर it contains a node number >= 0.  The
 * value -1 (0xFFFF) is OCFS2_INVALID_SLOT.  This marks a slot empty.
 */
काष्ठा ocfs2_slot_map अणु
/*00*/	__le16 sm_slots[0];
/*
 * Actual on-disk size is one block.  OCFS2_MAX_SLOTS is 255,
 * 255 * माप(__le16) == 512B, within the 512B block minimum blocksize.
 */
पूर्ण;

काष्ठा ocfs2_extended_slot अणु
/*00*/	__u8	es_valid;
	__u8	es_reserved1[3];
	__le32	es_node_num;
/*08*/
पूर्ण;

/*
 * The extended slot map, used when OCFS2_FEATURE_INCOMPAT_EXTENDED_SLOT_MAP
 * is set.  It separates out the valid marker from the node number, and
 * has room to grow.  Unlike the old slot map, this क्रमmat is defined by
 * i_size.
 */
काष्ठा ocfs2_slot_map_extended अणु
/*00*/	काष्ठा ocfs2_extended_slot se_slots[0];
/*
 * Actual size is i_size of the slot_map प्रणाली file.  It should
 * match s_max_slots * माप(काष्ठा ocfs2_extended_slot)
 */
पूर्ण;

/*
 * ci_stackflags is only valid अगर the incompat bit
 * OCFS2_FEATURE_INCOMPAT_CLUSTERINFO is set.
 */
काष्ठा ocfs2_cluster_info अणु
/*00*/	__u8   ci_stack[OCFS2_STACK_LABEL_LEN];
	जोड़ अणु
		__le32 ci_reserved;
		काष्ठा अणु
			__u8 ci_stackflags;
			__u8 ci_reserved1;
			__u8 ci_reserved2;
			__u8 ci_reserved3;
		पूर्ण;
	पूर्ण;
/*08*/	__u8   ci_cluster[OCFS2_CLUSTER_NAME_LEN];
/*18*/
पूर्ण;

/*
 * On disk superblock क्रम OCFS2
 * Note that it is contained inside an ocfs2_dinode, so all offsets
 * are relative to the start of ocfs2_dinode.id2.
 */
काष्ठा ocfs2_super_block अणु
/*00*/	__le16 s_major_rev_level;
	__le16 s_minor_rev_level;
	__le16 s_mnt_count;
	__le16 s_max_mnt_count;
	__le16 s_state;			/* File प्रणाली state */
	__le16 s_errors;			/* Behaviour when detecting errors */
	__le32 s_checkपूर्णांकerval;		/* Max समय between checks */
/*10*/	__le64 s_lastcheck;		/* Time of last check */
	__le32 s_creator_os;		/* OS */
	__le32 s_feature_compat;		/* Compatible feature set */
/*20*/	__le32 s_feature_incompat;	/* Incompatible feature set */
	__le32 s_feature_ro_compat;	/* Reaकरोnly-compatible feature set */
	__le64 s_root_blkno;		/* Offset, in blocks, of root directory
					   dinode */
/*30*/	__le64 s_प्रणाली_dir_blkno;	/* Offset, in blocks, of प्रणाली
					   directory dinode */
	__le32 s_blocksize_bits;		/* Blocksize क्रम this fs */
	__le32 s_clustersize_bits;	/* Clustersize क्रम this fs */
/*40*/	__le16 s_max_slots;		/* Max number of simultaneous mounts
					   beक्रमe tunefs required */
	__le16 s_tunefs_flag;
	__le32 s_uuid_hash;		/* hash value of uuid */
	__le64 s_first_cluster_group;	/* Block offset of 1st cluster
					 * group header */
/*50*/	__u8  s_label[OCFS2_MAX_VOL_LABEL_LEN];	/* Label क्रम mounting, etc. */
/*90*/	__u8  s_uuid[OCFS2_VOL_UUID_LEN];	/* 128-bit uuid */
/*A0*/  काष्ठा ocfs2_cluster_info s_cluster_info; /* Only valid अगर either
						     userspace or clusterinfo
						     INCOMPAT flag set. */
/*B8*/	__le16 s_xattr_अंतरभूत_size;	/* extended attribute अंतरभूत size
					   क्रम this fs*/
	__le16 s_reserved0;
	__le32 s_dx_seed[3];		/* seed[0-2] क्रम dx dir hash.
					 * s_uuid_hash serves as seed[3]. */
/*C0*/  __le64 s_reserved2[15];		/* Fill out superblock */
/*140*/

	/*
	 * NOTE: As stated above, all offsets are relative to
	 * ocfs2_dinode.id2, which is at 0xC0 in the inode.
	 * 0xC0 + 0x140 = 0x200 or 512 bytes.  A superblock must fit within
	 * our smallest blocksize, which is 512 bytes.  To ensure this,
	 * we reserve the space in s_reserved2.  Anything past s_reserved2
	 * will not be available on the smallest blocksize.
	 */
पूर्ण;

/*
 * Local allocation biपंचांगap क्रम OCFS2 slots
 * Note that it exists inside an ocfs2_dinode, so all offsets are
 * relative to the start of ocfs2_dinode.id2.
 */
काष्ठा ocfs2_local_alloc
अणु
/*00*/	__le32 la_bm_off;	/* Starting bit offset in मुख्य biपंचांगap */
	__le16 la_size;		/* Size of included biपंचांगap, in bytes */
	__le16 la_reserved1;
	__le64 la_reserved2;
/*10*/	__u8   la_biपंचांगap[];
पूर्ण;

/*
 * Data-in-inode header. This is only used अगर i_dyn_features has
 * OCFS2_INLINE_DATA_FL set.
 */
काष्ठा ocfs2_अंतरभूत_data
अणु
/*00*/	__le16	id_count;	/* Number of bytes that can be used
				 * क्रम data, starting at id_data */
	__le16	id_reserved0;
	__le32	id_reserved1;
	__u8	id_data[];	/* Start of user data */
पूर्ण;

/*
 * On disk inode क्रम OCFS2
 */
काष्ठा ocfs2_dinode अणु
/*00*/	__u8 i_signature[8];		/* Signature क्रम validation */
	__le32 i_generation;		/* Generation number */
	__le16 i_suballoc_slot;		/* Slot suballocator this inode
					   beदीर्घs to */
	__le16 i_suballoc_bit;		/* Bit offset in suballocator
					   block group */
/*10*/	__le16 i_links_count_hi;	/* High 16 bits of links count */
	__le16 i_xattr_अंतरभूत_size;
	__le32 i_clusters;		/* Cluster count */
	__le32 i_uid;			/* Owner UID */
	__le32 i_gid;			/* Owning GID */
/*20*/	__le64 i_size;			/* Size in bytes */
	__le16 i_mode;			/* File mode */
	__le16 i_links_count;		/* Links count */
	__le32 i_flags;			/* File flags */
/*30*/	__le64 i_aसमय;			/* Access समय */
	__le64 i_स_समय;			/* Creation समय */
/*40*/	__le64 i_mसमय;			/* Modअगरication समय */
	__le64 i_dसमय;			/* Deletion समय */
/*50*/	__le64 i_blkno;			/* Offset on disk, in blocks */
	__le64 i_last_eb_blk;		/* Poपूर्णांकer to last extent
					   block */
/*60*/	__le32 i_fs_generation;		/* Generation per fs-instance */
	__le32 i_aसमय_nsec;
	__le32 i_स_समय_nsec;
	__le32 i_mसमय_nsec;
/*70*/	__le32 i_attr;
	__le16 i_orphaned_slot;		/* Only valid when OCFS2_ORPHANED_FL
					   was set in i_flags */
	__le16 i_dyn_features;
	__le64 i_xattr_loc;
/*80*/	काष्ठा ocfs2_block_check i_check;	/* Error checking */
/*88*/	__le64 i_dx_root;		/* Poपूर्णांकer to dir index root block */
/*90*/	__le64 i_refcount_loc;
	__le64 i_suballoc_loc;		/* Suballocator block group this
					   inode beदीर्घs to.  Only valid
					   अगर allocated from a
					   discontiguous block group */
/*A0*/	__le16 i_dio_orphaned_slot;	/* only used क्रम append dio ग_लिखो */
	__le16 i_reserved1[3];
	__le64 i_reserved2[2];
/*B8*/	जोड़ अणु
		__le64 i_pad1;		/* Generic way to refer to this
					   64bit जोड़ */
		काष्ठा अणु
			__le64 i_rdev;	/* Device number */
		पूर्ण dev1;
		काष्ठा अणु		/* Info क्रम biपंचांगap प्रणाली
					   inodes */
			__le32 i_used;	/* Bits (ie, clusters) used  */
			__le32 i_total;	/* Total bits (clusters)
					   available */
		पूर्ण biपंचांगap1;
		काष्ठा अणु		/* Info क्रम journal प्रणाली
					   inodes */
			__le32 ij_flags;	/* Mounted, version, etc. */
			__le32 ij_recovery_generation; /* Incremented when the
							  journal is recovered
							  after an unclean
							  shutकरोwn */
		पूर्ण journal1;
	पूर्ण id1;				/* Inode type dependent 1 */
/*C0*/	जोड़ अणु
		काष्ठा ocfs2_super_block	i_super;
		काष्ठा ocfs2_local_alloc	i_lab;
		काष्ठा ocfs2_chain_list		i_chain;
		काष्ठा ocfs2_extent_list	i_list;
		काष्ठा ocfs2_truncate_log	i_dealloc;
		काष्ठा ocfs2_अंतरभूत_data	i_data;
		__u8               		i_symlink[0];
	पूर्ण id2;
/* Actual on-disk size is one block */
पूर्ण;

/*
 * On-disk directory entry काष्ठाure क्रम OCFS2
 *
 * Packed as this काष्ठाure could be accessed unaligned on 64-bit platक्रमms
 */
काष्ठा ocfs2_dir_entry अणु
/*00*/	__le64   inode;                  /* Inode number */
	__le16   rec_len;                /* Directory entry length */
	__u8    name_len;               /* Name length */
	__u8    file_type;
/*0C*/	अक्षर    name[OCFS2_MAX_खाताNAME_LEN];   /* File name */
/* Actual on-disk length specअगरied by rec_len */
पूर्ण __attribute__ ((packed));

/*
 * Per-block record क्रम the unindexed directory btree. This is carefully
 * crafted so that the rec_len and name_len records of an ocfs2_dir_entry are
 * mirrored. That way, the directory manipulation code needs a minimal amount
 * of update.
 *
 * NOTE: Keep this काष्ठाure aligned to a multiple of 4 bytes.
 */
काष्ठा ocfs2_dir_block_trailer अणु
/*00*/	__le64		db_compat_inode;	/* Always zero. Was inode */

	__le16		db_compat_rec_len;	/* Backwards compatible with
						 * ocfs2_dir_entry. */
	__u8		db_compat_name_len;	/* Always zero. Was name_len */
	__u8		db_reserved0;
	__le16		db_reserved1;
	__le16		db_मुक्त_rec_len;	/* Size of largest empty hole
						 * in this block. (unused) */
/*10*/	__u8		db_signature[8];	/* Signature क्रम verअगरication */
	__le64		db_reserved2;
/*20*/	__le64		db_मुक्त_next;		/* Next block in list (unused) */
	__le64		db_blkno;		/* Offset on disk, in blocks */
/*30*/	__le64		db_parent_dinode;	/* dinode which owns me, in
						   blocks */
	काष्ठा ocfs2_block_check db_check;	/* Error checking */
/*40*/
पूर्ण;

 /*
 * A directory entry in the indexed tree. We करोn't store the full name here,
 * but instead provide a poपूर्णांकer to the full dirent in the unindexed tree.
 *
 * We also store name_len here so as to reduce the number of leaf blocks we
 * need to search in हाल of collisions.
 */
काष्ठा ocfs2_dx_entry अणु
	__le32		dx_major_hash;	/* Used to find logical
					 * cluster in index */
	__le32		dx_minor_hash;	/* Lower bits used to find
					 * block in cluster */
	__le64		dx_dirent_blk;	/* Physical block in unindexed
					 * tree holding this dirent. */
पूर्ण;

काष्ठा ocfs2_dx_entry_list अणु
	__le32		de_reserved;
	__le16		de_count;	/* Maximum number of entries
					 * possible in de_entries */
	__le16		de_num_used;	/* Current number of
					 * de_entries entries */
	काष्ठा	ocfs2_dx_entry		de_entries[];	/* Indexed dir entries
							 * in a packed array of
							 * length de_num_used */
पूर्ण;

#घोषणा OCFS2_DX_FLAG_INLINE	0x01

/*
 * A directory indexing block. Each indexed directory has one of these,
 * poपूर्णांकed to by ocfs2_dinode.
 *
 * This block stores an indexed btree root, and a set of मुक्त space
 * start-of-list poपूर्णांकers.
 */
काष्ठा ocfs2_dx_root_block अणु
	__u8		dr_signature[8];	/* Signature क्रम verअगरication */
	काष्ठा ocfs2_block_check dr_check;	/* Error checking */
	__le16		dr_suballoc_slot;	/* Slot suballocator this
						 * block beदीर्घs to. */
	__le16		dr_suballoc_bit;	/* Bit offset in suballocator
						 * block group */
	__le32		dr_fs_generation;	/* Must match super block */
	__le64		dr_blkno;		/* Offset on disk, in blocks */
	__le64		dr_last_eb_blk;		/* Poपूर्णांकer to last
						 * extent block */
	__le32		dr_clusters;		/* Clusters allocated
						 * to the indexed tree. */
	__u8		dr_flags;		/* OCFS2_DX_FLAG_* flags */
	__u8		dr_reserved0;
	__le16		dr_reserved1;
	__le64		dr_dir_blkno;		/* Poपूर्णांकer to parent inode */
	__le32		dr_num_entries;		/* Total number of
						 * names stored in
						 * this directory.*/
	__le32		dr_reserved2;
	__le64		dr_मुक्त_blk;		/* Poपूर्णांकer to head of मुक्त
						 * unindexed block list. */
	__le64		dr_suballoc_loc;	/* Suballocator block group
						   this root beदीर्घs to.
						   Only valid अगर allocated
						   from a discontiguous
						   block group */
	__le64		dr_reserved3[14];
	जोड़ अणु
		काष्ठा ocfs2_extent_list dr_list; /* Keep this aligned to 128
						   * bits क्रम maximum space
						   * efficiency. */
		काष्ठा ocfs2_dx_entry_list dr_entries; /* In-root-block list of
							* entries. We grow out
							* to extents अगर this
							* माला_लो too big. */
	पूर्ण;
पूर्ण;

/*
 * The header of a leaf block in the indexed tree.
 */
काष्ठा ocfs2_dx_leaf अणु
	__u8		dl_signature[8];/* Signature क्रम verअगरication */
	काष्ठा ocfs2_block_check dl_check;	/* Error checking */
	__le64		dl_blkno;	/* Offset on disk, in blocks */
	__le32		dl_fs_generation;/* Must match super block */
	__le32		dl_reserved0;
	__le64		dl_reserved1;
	काष्ठा ocfs2_dx_entry_list	dl_list;
पूर्ण;

/*
 * Largest biपंचांगap क्रम a block (suballocator) group in bytes.  This limit
 * करोes not affect cluster groups (global allocator).  Cluster group
 * biपंचांगaps run to the end of the block.
 */
#घोषणा OCFS2_MAX_BG_BITMAP_SIZE	256

/*
 * On disk allocator group काष्ठाure क्रम OCFS2
 */
काष्ठा ocfs2_group_desc
अणु
/*00*/	__u8    bg_signature[8];        /* Signature क्रम validation */
	__le16   bg_size;                /* Size of included biपंचांगap in
					   bytes. */
	__le16   bg_bits;                /* Bits represented by this
					   group. */
	__le16	bg_मुक्त_bits_count;     /* Free bits count */
	__le16   bg_chain;               /* What chain I am in. */
/*10*/	__le32   bg_generation;
	__le32	bg_reserved1;
	__le64   bg_next_group;          /* Next group in my list, in
					   blocks */
/*20*/	__le64   bg_parent_dinode;       /* dinode which owns me, in
					   blocks */
	__le64   bg_blkno;               /* Offset on disk, in blocks */
/*30*/	काष्ठा ocfs2_block_check bg_check;	/* Error checking */
	__le64   bg_reserved2;
/*40*/	जोड़ अणु
		__u8    bg_biपंचांगap[0];
		काष्ठा अणु
			/*
			 * Block groups may be discontiguous when
			 * OCFS2_FEATURE_INCOMPAT_DISCONTIG_BG is set.
			 * The extents of a discontiguous block group are
			 * stored in bg_list.  It is a flat list.
			 * l_tree_depth must always be zero.  A
			 * discontiguous group is signअगरied by a non-zero
			 * bg_list->l_next_मुक्त_rec.  Only block groups
			 * can be discontiguous; Cluster groups cannot.
			 * We've never made a block group with more than
			 * 2048 blocks (256 bytes of bg_biपंचांगap).  This
			 * codअगरies that limit so that we can fit bg_list.
			 * bg_size of a discontiguous block group will
			 * be 256 to match bg_biपंचांगap_filler.
			 */
			__u8 bg_biपंचांगap_filler[OCFS2_MAX_BG_BITMAP_SIZE];
/*140*/			काष्ठा ocfs2_extent_list bg_list;
		पूर्ण;
	पूर्ण;
/* Actual on-disk size is one block */
पूर्ण;

काष्ठा ocfs2_refcount_rec अणु
/*00*/	__le64 r_cpos;		/* Physical offset, in clusters */
	__le32 r_clusters;	/* Clusters covered by this extent */
	__le32 r_refcount;	/* Reference count of this extent */
/*10*/
पूर्ण;
#घोषणा OCFS2_32BIT_POS_MASK		(0xffffffffULL)

#घोषणा OCFS2_REFCOUNT_LEAF_FL          (0x00000001)
#घोषणा OCFS2_REFCOUNT_TREE_FL          (0x00000002)

काष्ठा ocfs2_refcount_list अणु
/*00*/	__le16 rl_count;	/* Maximum number of entries possible
				   in rl_records */
	__le16 rl_used;		/* Current number of used records */
	__le32 rl_reserved2;
	__le64 rl_reserved1;	/* Pad to माप(ocfs2_refcount_record) */
/*10*/	काष्ठा ocfs2_refcount_rec rl_recs[];	/* Refcount records */
पूर्ण;


काष्ठा ocfs2_refcount_block अणु
/*00*/	__u8 rf_signature[8];		/* Signature क्रम verअगरication */
	__le16 rf_suballoc_slot;	/* Slot suballocator this block
					   beदीर्घs to */
	__le16 rf_suballoc_bit;		/* Bit offset in suballocator
					   block group */
	__le32 rf_fs_generation;	/* Must match superblock */
/*10*/	__le64 rf_blkno;		/* Offset on disk, in blocks */
	__le64 rf_parent;		/* Parent block, only valid अगर
					   OCFS2_REFCOUNT_LEAF_FL is set in
					   rf_flags */
/*20*/	काष्ठा ocfs2_block_check rf_check;	/* Error checking */
	__le64 rf_last_eb_blk;		/* Poपूर्णांकer to last extent block */
/*30*/	__le32 rf_count;		/* Number of inodes sharing this
					   refcount tree */
	__le32 rf_flags;		/* See the flags above */
	__le32 rf_clusters;		/* clusters covered by refcount tree. */
	__le32 rf_cpos;			/* cluster offset in refcount tree.*/
/*40*/	__le32 rf_generation;		/* generation number. all be the same
					 * क्रम the same refcount tree. */
	__le32 rf_reserved0;
	__le64 rf_suballoc_loc;		/* Suballocator block group this
					   refcount block beदीर्घs to. Only
					   valid अगर allocated from a
					   discontiguous block group */
/*50*/	__le64 rf_reserved1[6];
/*80*/	जोड़ अणु
		काष्ठा ocfs2_refcount_list rf_records;  /* List of refcount
							  records */
		काष्ठा ocfs2_extent_list rf_list;	/* Extent record list,
							only valid अगर
							OCFS2_REFCOUNT_TREE_FL
							is set in rf_flags */
	पूर्ण;
/* Actual on-disk size is one block */
पूर्ण;

/*
 * On disk extended attribute काष्ठाure क्रम OCFS2.
 */

/*
 * ocfs2_xattr_entry indicates one extend attribute.
 *
 * Note that it can be stored in inode, one block or one xattr bucket.
 */
काष्ठा ocfs2_xattr_entry अणु
	__le32	xe_name_hash;    /* hash value of xattr prefix+suffix. */
	__le16	xe_name_offset;  /* byte offset from the 1st entry in the
				    local xattr storage(inode, xattr block or
				    xattr bucket). */
	__u8	xe_name_len;	 /* xattr name len, करोesn't include prefix. */
	__u8	xe_type;         /* the low 7 bits indicate the name prefix
				  * type and the highest bit indicates whether
				  * the EA is stored in the local storage. */
	__le64	xe_value_size;	 /* real xattr value length. */
पूर्ण;

/*
 * On disk काष्ठाure क्रम xattr header.
 *
 * One ocfs2_xattr_header describes how many ocfs2_xattr_entry records in
 * the local xattr storage.
 */
काष्ठा ocfs2_xattr_header अणु
	__le16	xh_count;                       /* contains the count of how
						   many records are in the
						   local xattr storage. */
	__le16	xh_मुक्त_start;                  /* current offset क्रम storing
						   xattr. */
	__le16	xh_name_value_len;              /* total length of name/value
						   length in this bucket. */
	__le16	xh_num_buckets;                 /* Number of xattr buckets
						   in this extent record,
						   only valid in the first
						   bucket. */
	काष्ठा ocfs2_block_check xh_check;	/* Error checking
						   (Note, this is only
						    used क्रम xattr
						    buckets.  A block uses
						    xb_check and sets
						    this field to zero.) */
	काष्ठा ocfs2_xattr_entry xh_entries[]; /* xattr entry list. */
पूर्ण;

/*
 * On disk काष्ठाure क्रम xattr value root.
 *
 * When an xattr's value is large enough, it is stored in an बाह्यal
 * b-tree like file data.  The xattr value root poपूर्णांकs to this काष्ठाure.
 */
काष्ठा ocfs2_xattr_value_root अणु
/*00*/	__le32	xr_clusters;              /* clusters covered by xattr value. */
	__le32	xr_reserved0;
	__le64	xr_last_eb_blk;           /* Poपूर्णांकer to last extent block */
/*10*/	काष्ठा ocfs2_extent_list xr_list; /* Extent record list */
पूर्ण;

/*
 * On disk काष्ठाure क्रम xattr tree root.
 *
 * It is used when there are too many extended attributes क्रम one file. These
 * attributes will be organized and stored in an indexed-btree.
 */
काष्ठा ocfs2_xattr_tree_root अणु
/*00*/	__le32	xt_clusters;              /* clusters covered by xattr. */
	__le32	xt_reserved0;
	__le64	xt_last_eb_blk;           /* Poपूर्णांकer to last extent block */
/*10*/	काष्ठा ocfs2_extent_list xt_list; /* Extent record list */
पूर्ण;

#घोषणा OCFS2_XATTR_INDEXED	0x1
#घोषणा OCFS2_HASH_SHIFT	5
#घोषणा OCFS2_XATTR_ROUND	3
#घोषणा OCFS2_XATTR_SIZE(size)	(((size) + OCFS2_XATTR_ROUND) & \
				~(OCFS2_XATTR_ROUND))

#घोषणा OCFS2_XATTR_BUCKET_SIZE			4096
#घोषणा OCFS2_XATTR_MAX_BLOCKS_PER_BUCKET 	(OCFS2_XATTR_BUCKET_SIZE \
						 / OCFS2_MIN_BLOCKSIZE)

/*
 * On disk काष्ठाure क्रम xattr block.
 */
काष्ठा ocfs2_xattr_block अणु
/*00*/	__u8	xb_signature[8];     /* Signature क्रम verअगरication */
	__le16	xb_suballoc_slot;    /* Slot suballocator this
					block beदीर्घs to. */
	__le16	xb_suballoc_bit;     /* Bit offset in suballocator
					block group */
	__le32	xb_fs_generation;    /* Must match super block */
/*10*/	__le64	xb_blkno;            /* Offset on disk, in blocks */
	काष्ठा ocfs2_block_check xb_check;	/* Error checking */
/*20*/	__le16	xb_flags;            /* Indicates whether this block contains
					real xattr or a xattr tree. */
	__le16	xb_reserved0;
	__le32  xb_reserved1;
	__le64	xb_suballoc_loc;	/* Suballocator block group this
					   xattr block beदीर्घs to. Only
					   valid अगर allocated from a
					   discontiguous block group */
/*30*/	जोड़ अणु
		काष्ठा ocfs2_xattr_header xb_header; /* xattr header अगर this
							block contains xattr */
		काष्ठा ocfs2_xattr_tree_root xb_root;/* xattr tree root अगर this
							block cotains xattr
							tree. */
	पूर्ण xb_attrs;
पूर्ण;

#घोषणा OCFS2_XATTR_ENTRY_LOCAL		0x80
#घोषणा OCFS2_XATTR_TYPE_MASK		0x7F
अटल अंतरभूत व्योम ocfs2_xattr_set_local(काष्ठा ocfs2_xattr_entry *xe,
					 पूर्णांक local)
अणु
	अगर (local)
		xe->xe_type |= OCFS2_XATTR_ENTRY_LOCAL;
	अन्यथा
		xe->xe_type &= ~OCFS2_XATTR_ENTRY_LOCAL;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_xattr_is_local(काष्ठा ocfs2_xattr_entry *xe)
अणु
	वापस xe->xe_type & OCFS2_XATTR_ENTRY_LOCAL;
पूर्ण

अटल अंतरभूत व्योम ocfs2_xattr_set_type(काष्ठा ocfs2_xattr_entry *xe, पूर्णांक type)
अणु
	xe->xe_type |= type & OCFS2_XATTR_TYPE_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_xattr_get_type(काष्ठा ocfs2_xattr_entry *xe)
अणु
	वापस xe->xe_type & OCFS2_XATTR_TYPE_MASK;
पूर्ण

/*
 *  On disk काष्ठाures क्रम global quota file
 */

/* Magic numbers and known versions क्रम global quota files */
#घोषणा OCFS2_GLOBAL_QMAGICS अणु\
	0x0cf52470, /* USRQUOTA */ \
	0x0cf52471  /* GRPQUOTA */ \
पूर्ण

#घोषणा OCFS2_GLOBAL_QVERSIONS अणु\
	0, \
	0, \
पूर्ण


/* Each block of each quota file has a certain fixed number of bytes reserved
 * क्रम OCFS2 पूर्णांकernal use at its end. OCFS2 can use it क्रम things like
 * checksums, etc. */
#घोषणा OCFS2_QBLK_RESERVED_SPACE 8

/* Generic header of all quota files */
काष्ठा ocfs2_disk_dqheader अणु
	__le32 dqh_magic;	/* Magic number identअगरying file */
	__le32 dqh_version;	/* Quota क्रमmat version */
पूर्ण;

#घोषणा OCFS2_GLOBAL_INFO_OFF (माप(काष्ठा ocfs2_disk_dqheader))

/* Inक्रमmation header of global quota file (immediately follows the generic
 * header) */
काष्ठा ocfs2_global_disk_dqinfo अणु
/*00*/	__le32 dqi_bgrace;	/* Grace समय क्रम space softlimit excess */
	__le32 dqi_igrace;	/* Grace समय क्रम inode softlimit excess */
	__le32 dqi_syncms;	/* Time after which we sync local changes to
				 * global quota file */
	__le32 dqi_blocks;	/* Number of blocks in quota file */
/*10*/	__le32 dqi_मुक्त_blk;	/* First मुक्त block in quota file */
	__le32 dqi_मुक्त_entry;	/* First block with मुक्त dquot entry in quota
				 * file */
पूर्ण;

/* Structure with global user / group inक्रमmation. We reserve some space
 * क्रम future use. */
काष्ठा ocfs2_global_disk_dqblk अणु
/*00*/	__le32 dqb_id;          /* ID the काष्ठाure beदीर्घs to */
	__le32 dqb_use_count;   /* Number of nodes having reference to this काष्ठाure */
	__le64 dqb_ihardlimit;  /* असलolute limit on allocated inodes */
/*10*/	__le64 dqb_isoftlimit;  /* preferred inode limit */
	__le64 dqb_curinodes;   /* current # allocated inodes */
/*20*/	__le64 dqb_bhardlimit;  /* असलolute limit on disk space */
	__le64 dqb_bsoftlimit;  /* preferred limit on disk space */
/*30*/	__le64 dqb_curspace;    /* current space occupied */
	__le64 dqb_bसमय;       /* समय limit क्रम excessive disk use */
/*40*/	__le64 dqb_iसमय;       /* समय limit क्रम excessive inode use */
	__le64 dqb_pad1;
/*50*/	__le64 dqb_pad2;
पूर्ण;

/*
 *  On-disk काष्ठाures क्रम local quota file
 */

/* Magic numbers and known versions क्रम local quota files */
#घोषणा OCFS2_LOCAL_QMAGICS अणु\
	0x0cf524c0, /* USRQUOTA */ \
	0x0cf524c1  /* GRPQUOTA */ \
पूर्ण

#घोषणा OCFS2_LOCAL_QVERSIONS अणु\
	0, \
	0, \
पूर्ण

/* Quota flags in dqinfo header */
#घोषणा OLQF_CLEAN	0x0001	/* Quota file is empty (this should be after\
				 * quota has been cleanly turned off) */

#घोषणा OCFS2_LOCAL_INFO_OFF (माप(काष्ठा ocfs2_disk_dqheader))

/* Inक्रमmation header of local quota file (immediately follows the generic
 * header) */
काष्ठा ocfs2_local_disk_dqinfo अणु
	__le32 dqi_flags;	/* Flags क्रम quota file */
	__le32 dqi_chunks;	/* Number of chunks of quota काष्ठाures
				 * with a biपंचांगap */
	__le32 dqi_blocks;	/* Number of blocks allocated क्रम quota file */
पूर्ण;

/* Header of one chunk of a quota file */
काष्ठा ocfs2_local_disk_chunk अणु
	__le32 dqc_मुक्त;	/* Number of मुक्त entries in the biपंचांगap */
	__u8 dqc_biपंचांगap[];	/* Biपंचांगap of entries in the corresponding
				 * chunk of quota file */
पूर्ण;

/* One entry in local quota file */
काष्ठा ocfs2_local_disk_dqblk अणु
/*00*/	__le64 dqb_id;		/* id this quota applies to */
	__le64 dqb_spacemod;	/* Change in the amount of used space */
/*10*/	__le64 dqb_inodemod;	/* Change in the amount of used inodes */
पूर्ण;


/*
 * The quota trailer lives at the end of each quota block.
 */

काष्ठा ocfs2_disk_dqtrailer अणु
/*00*/	काष्ठा ocfs2_block_check dq_check;	/* Error checking */
/*08*/	/* Cannot be larger than OCFS2_QBLK_RESERVED_SPACE */
पूर्ण;

अटल अंतरभूत काष्ठा ocfs2_disk_dqtrailer *ocfs2_block_dqtrailer(पूर्णांक blocksize,
								 व्योम *buf)
अणु
	अक्षर *ptr = buf;
	ptr += blocksize - OCFS2_QBLK_RESERVED_SPACE;

	वापस (काष्ठा ocfs2_disk_dqtrailer *)ptr;
पूर्ण

#अगर_घोषित __KERNEL__
अटल अंतरभूत पूर्णांक ocfs2_fast_symlink_अक्षरs(काष्ठा super_block *sb)
अणु
	वापस  sb->s_blocksize -
		 दुरत्व(काष्ठा ocfs2_dinode, id2.i_symlink);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_max_अंतरभूत_data_with_xattr(काष्ठा super_block *sb,
						   काष्ठा ocfs2_dinode *di)
अणु
	अचिन्हित पूर्णांक xattrsize = le16_to_cpu(di->i_xattr_अंतरभूत_size);

	अगर (le16_to_cpu(di->i_dyn_features) & OCFS2_INLINE_XATTR_FL)
		वापस sb->s_blocksize -
			दुरत्व(काष्ठा ocfs2_dinode, id2.i_data.id_data) -
			xattrsize;
	अन्यथा
		वापस sb->s_blocksize -
			दुरत्व(काष्ठा ocfs2_dinode, id2.i_data.id_data);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_extent_recs_per_inode(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_dinode, id2.i_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_extent_recs_per_inode_with_xattr(
						काष्ठा super_block *sb,
						काष्ठा ocfs2_dinode *di)
अणु
	पूर्णांक size;
	अचिन्हित पूर्णांक xattrsize = le16_to_cpu(di->i_xattr_अंतरभूत_size);

	अगर (le16_to_cpu(di->i_dyn_features) & OCFS2_INLINE_XATTR_FL)
		size = sb->s_blocksize -
			दुरत्व(काष्ठा ocfs2_dinode, id2.i_list.l_recs) -
			xattrsize;
	अन्यथा
		size = sb->s_blocksize -
			दुरत्व(काष्ठा ocfs2_dinode, id2.i_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_extent_recs_per_dx_root(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_dx_root_block, dr_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_chain_recs_per_inode(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_dinode, id2.i_chain.cl_recs);

	वापस size / माप(काष्ठा ocfs2_chain_rec);
पूर्ण

अटल अंतरभूत u16 ocfs2_extent_recs_per_eb(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_extent_block, h_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत u16 ocfs2_extent_recs_per_gd(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_group_desc, bg_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_dx_entries_per_leaf(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_dx_leaf, dl_list.de_entries);

	वापस size / माप(काष्ठा ocfs2_dx_entry);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_dx_entries_per_root(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_dx_root_block, dr_entries.de_entries);

	वापस size / माप(काष्ठा ocfs2_dx_entry);
पूर्ण

अटल अंतरभूत u16 ocfs2_local_alloc_size(काष्ठा super_block *sb)
अणु
	u16 size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_dinode, id2.i_lab.la_biपंचांगap);

	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_group_biपंचांगap_size(काष्ठा super_block *sb,
					  पूर्णांक suballocator,
					  u32 feature_incompat)
अणु
	पूर्णांक size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_group_desc, bg_biपंचांगap);

	/*
	 * The cluster allocator uses the entire block.  Suballocators have
	 * never used more than OCFS2_MAX_BG_BITMAP_SIZE.  Unक्रमtunately, older
	 * code expects bg_size set to the maximum.  Thus we must keep
	 * bg_size as-is unless discontig_bg is enabled.
	 */
	अगर (suballocator &&
	    (feature_incompat & OCFS2_FEATURE_INCOMPAT_DISCONTIG_BG))
		size = OCFS2_MAX_BG_BITMAP_SIZE;

	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_truncate_recs_per_inode(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_dinode, id2.i_dealloc.tl_recs);

	वापस size / माप(काष्ठा ocfs2_truncate_rec);
पूर्ण

अटल अंतरभूत u64 ocfs2_backup_super_blkno(काष्ठा super_block *sb, पूर्णांक index)
अणु
	u64 offset = OCFS2_BACKUP_SB_START;

	अगर (index >= 0 && index < OCFS2_MAX_BACKUP_SUPERBLOCKS) अणु
		offset <<= (2 * index);
		offset >>= sb->s_blocksize_bits;
		वापस offset;
	पूर्ण

	वापस 0;

पूर्ण

अटल अंतरभूत u16 ocfs2_xattr_recs_per_xb(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_xattr_block,
			 xb_attrs.xb_root.xt_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत u16 ocfs2_extent_recs_per_rb(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_refcount_block, rf_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत u16 ocfs2_refcount_recs_per_rb(काष्ठा super_block *sb)
अणु
	पूर्णांक size;

	size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_refcount_block, rf_records.rl_recs);

	वापस size / माप(काष्ठा ocfs2_refcount_rec);
पूर्ण

अटल अंतरभूत u32
ocfs2_get_ref_rec_low_cpos(स्थिर काष्ठा ocfs2_refcount_rec *rec)
अणु
	वापस le64_to_cpu(rec->r_cpos) & OCFS2_32BIT_POS_MASK;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ocfs2_fast_symlink_अक्षरs(पूर्णांक blocksize)
अणु
	वापस blocksize - दुरत्व(काष्ठा ocfs2_dinode, id2.i_symlink);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_max_अंतरभूत_data_with_xattr(पूर्णांक blocksize,
						   काष्ठा ocfs2_dinode *di)
अणु
	अगर (di && (di->i_dyn_features & OCFS2_INLINE_XATTR_FL))
		वापस blocksize -
			दुरत्व(काष्ठा ocfs2_dinode, id2.i_data.id_data) -
			di->i_xattr_अंतरभूत_size;
	अन्यथा
		वापस blocksize -
			दुरत्व(काष्ठा ocfs2_dinode, id2.i_data.id_data);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_extent_recs_per_inode(पूर्णांक blocksize)
अणु
	पूर्णांक size;

	size = blocksize -
		दुरत्व(काष्ठा ocfs2_dinode, id2.i_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_chain_recs_per_inode(पूर्णांक blocksize)
अणु
	पूर्णांक size;

	size = blocksize -
		दुरत्व(काष्ठा ocfs2_dinode, id2.i_chain.cl_recs);

	वापस size / माप(काष्ठा ocfs2_chain_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_extent_recs_per_eb(पूर्णांक blocksize)
अणु
	पूर्णांक size;

	size = blocksize -
		दुरत्व(काष्ठा ocfs2_extent_block, h_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_extent_recs_per_gd(पूर्णांक blocksize)
अणु
	पूर्णांक size;

	size = blocksize -
		दुरत्व(काष्ठा ocfs2_group_desc, bg_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_local_alloc_size(पूर्णांक blocksize)
अणु
	पूर्णांक size;

	size = blocksize -
		दुरत्व(काष्ठा ocfs2_dinode, id2.i_lab.la_biपंचांगap);

	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_group_biपंचांगap_size(पूर्णांक blocksize,
					  पूर्णांक suballocator,
					  uपूर्णांक32_t feature_incompat)
अणु
	पूर्णांक size = sb->s_blocksize -
		दुरत्व(काष्ठा ocfs2_group_desc, bg_biपंचांगap);

	/*
	 * The cluster allocator uses the entire block.  Suballocators have
	 * never used more than OCFS2_MAX_BG_BITMAP_SIZE.  Unक्रमtunately, older
	 * code expects bg_size set to the maximum.  Thus we must keep
	 * bg_size as-is unless discontig_bg is enabled.
	 */
	अगर (suballocator &&
	    (feature_incompat & OCFS2_FEATURE_INCOMPAT_DISCONTIG_BG))
		size = OCFS2_MAX_BG_BITMAP_SIZE;

	वापस size;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_truncate_recs_per_inode(पूर्णांक blocksize)
अणु
	पूर्णांक size;

	size = blocksize -
		दुरत्व(काष्ठा ocfs2_dinode, id2.i_dealloc.tl_recs);

	वापस size / माप(काष्ठा ocfs2_truncate_rec);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t ocfs2_backup_super_blkno(पूर्णांक blocksize, पूर्णांक index)
अणु
	uपूर्णांक64_t offset = OCFS2_BACKUP_SB_START;

	अगर (index >= 0 && index < OCFS2_MAX_BACKUP_SUPERBLOCKS) अणु
		offset <<= (2 * index);
		offset /= blocksize;
		वापस offset;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_xattr_recs_per_xb(पूर्णांक blocksize)
अणु
	पूर्णांक size;

	size = blocksize -
		दुरत्व(काष्ठा ocfs2_xattr_block,
			 xb_attrs.xb_root.xt_list.l_recs);

	वापस size / माप(काष्ठा ocfs2_extent_rec);
पूर्ण
#पूर्ण_अगर  /* __KERNEL__ */


अटल अंतरभूत पूर्णांक ocfs2_प्रणाली_inode_is_global(पूर्णांक type)
अणु
	वापस ((type >= 0) &&
		(type <= OCFS2_LAST_GLOBAL_SYSTEM_INODE));
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_प्र_लिखो_प्रणाली_inode_name(अक्षर *buf, पूर्णांक len,
						  पूर्णांक type, पूर्णांक slot)
अणु
	पूर्णांक अक्षरs;

        /*
         * Global प्रणाली inodes can only have one copy.  Everything
         * after OCFS2_LAST_GLOBAL_SYSTEM_INODE in the प्रणाली inode
         * list has a copy per slot.
         */
	अगर (type <= OCFS2_LAST_GLOBAL_SYSTEM_INODE)
		अक्षरs = snम_लिखो(buf, len, "%s",
				 ocfs2_प्रणाली_inodes[type].si_name);
	अन्यथा
		अक्षरs = snम_लिखो(buf, len,
				 ocfs2_प्रणाली_inodes[type].si_name,
				 slot);

	वापस अक्षरs;
पूर्ण

अटल अंतरभूत व्योम ocfs2_set_de_type(काष्ठा ocfs2_dir_entry *de,
				    umode_t mode)
अणु
	de->file_type = fs_umode_to_ftype(mode);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_gd_is_discontig(काष्ठा ocfs2_group_desc *gd)
अणु
	अगर ((दुरत्व(काष्ठा ocfs2_group_desc, bg_biपंचांगap) +
	     le16_to_cpu(gd->bg_size)) !=
	    दुरत्व(काष्ठा ocfs2_group_desc, bg_list))
		वापस 0;
	/*
	 * Only valid to check l_next_मुक्त_rec अगर
	 * bg_biपंचांगap + bg_size == bg_list.
	 */
	अगर (!gd->bg_list.l_next_मुक्त_rec)
		वापस 0;
	वापस 1;
पूर्ण
#पूर्ण_अगर  /* _OCFS2_FS_H */

