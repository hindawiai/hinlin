<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * include/linux/f2fs_fs.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#अगर_अघोषित _LINUX_F2FS_FS_H
#घोषणा _LINUX_F2FS_FS_H

#समावेश <linux/pagemap.h>
#समावेश <linux/types.h>

#घोषणा F2FS_SUPER_OFFSET		1024	/* byte-size offset */
#घोषणा F2FS_MIN_LOG_SECTOR_SIZE	9	/* 9 bits क्रम 512 bytes */
#घोषणा F2FS_MAX_LOG_SECTOR_SIZE	12	/* 12 bits क्रम 4096 bytes */
#घोषणा F2FS_LOG_SECTORS_PER_BLOCK	3	/* log number क्रम sector/blk */
#घोषणा F2FS_BLKSIZE			4096	/* support only 4KB block */
#घोषणा F2FS_BLKSIZE_BITS		12	/* bits क्रम F2FS_BLKSIZE */
#घोषणा F2FS_MAX_EXTENSION		64	/* # of extension entries */
#घोषणा F2FS_EXTENSION_LEN		8	/* max size of extension */
#घोषणा F2FS_BLK_ALIGN(x)	(((x) + F2FS_BLKSIZE - 1) >> F2FS_BLKSIZE_BITS)

#घोषणा शून्य_ADDR		((block_t)0)	/* used as block_t addresses */
#घोषणा NEW_ADDR		((block_t)-1)	/* used as block_t addresses */
#घोषणा COMPRESS_ADDR		((block_t)-2)	/* used as compressed data flag */

#घोषणा F2FS_BYTES_TO_BLK(bytes)	((bytes) >> F2FS_BLKSIZE_BITS)
#घोषणा F2FS_BLK_TO_BYTES(blk)		((blk) << F2FS_BLKSIZE_BITS)

/* 0, 1(node nid), 2(meta nid) are reserved node id */
#घोषणा F2FS_RESERVED_NODE_NUM		3

#घोषणा F2FS_ROOT_INO(sbi)	((sbi)->root_ino_num)
#घोषणा F2FS_NODE_INO(sbi)	((sbi)->node_ino_num)
#घोषणा F2FS_META_INO(sbi)	((sbi)->meta_ino_num)

#घोषणा F2FS_MAX_QUOTAS		3

#घोषणा F2FS_ENC_UTF8_12_1	1

#घोषणा F2FS_IO_SIZE(sbi)	(1 << F2FS_OPTION(sbi).ग_लिखो_io_size_bits) /* Blocks */
#घोषणा F2FS_IO_SIZE_KB(sbi)	(1 << (F2FS_OPTION(sbi).ग_लिखो_io_size_bits + 2)) /* KB */
#घोषणा F2FS_IO_SIZE_BYTES(sbi)	(1 << (F2FS_OPTION(sbi).ग_लिखो_io_size_bits + 12)) /* B */
#घोषणा F2FS_IO_SIZE_BITS(sbi)	(F2FS_OPTION(sbi).ग_लिखो_io_size_bits) /* घातer of 2 */
#घोषणा F2FS_IO_SIZE_MASK(sbi)	(F2FS_IO_SIZE(sbi) - 1)
#घोषणा F2FS_IO_ALIGNED(sbi)	(F2FS_IO_SIZE(sbi) > 1)

/* This flag is used by node and meta inodes, and by recovery */
#घोषणा GFP_F2FS_ZERO		(GFP_NOFS | __GFP_ZERO)

/*
 * For further optimization on multi-head logs, on-disk layout supports maximum
 * 16 logs by शेष. The number, 16, is expected to cover all the हालs
 * enoughly. The implementaion currently uses no more than 6 logs.
 * Half the logs are used क्रम nodes, and the other half are used क्रम data.
 */
#घोषणा MAX_ACTIVE_LOGS	16
#घोषणा MAX_ACTIVE_NODE_LOGS	8
#घोषणा MAX_ACTIVE_DATA_LOGS	8

#घोषणा VERSION_LEN	256
#घोषणा MAX_VOLUME_NAME		512
#घोषणा MAX_PATH_LEN		64
#घोषणा MAX_DEVICES		8

/*
 * For superblock
 */
काष्ठा f2fs_device अणु
	__u8 path[MAX_PATH_LEN];
	__le32 total_segments;
पूर्ण __packed;

काष्ठा f2fs_super_block अणु
	__le32 magic;			/* Magic Number */
	__le16 major_ver;		/* Major Version */
	__le16 minor_ver;		/* Minor Version */
	__le32 log_sectorsize;		/* log2 sector size in bytes */
	__le32 log_sectors_per_block;	/* log2 # of sectors per block */
	__le32 log_blocksize;		/* log2 block size in bytes */
	__le32 log_blocks_per_seg;	/* log2 # of blocks per segment */
	__le32 segs_per_sec;		/* # of segments per section */
	__le32 secs_per_zone;		/* # of sections per zone */
	__le32 checksum_offset;		/* checksum offset inside super block */
	__le64 block_count;		/* total # of user blocks */
	__le32 section_count;		/* total # of sections */
	__le32 segment_count;		/* total # of segments */
	__le32 segment_count_ckpt;	/* # of segments क्रम checkpoपूर्णांक */
	__le32 segment_count_sit;	/* # of segments क्रम SIT */
	__le32 segment_count_nat;	/* # of segments क्रम NAT */
	__le32 segment_count_ssa;	/* # of segments क्रम SSA */
	__le32 segment_count_मुख्य;	/* # of segments क्रम मुख्य area */
	__le32 segment0_blkaddr;	/* start block address of segment 0 */
	__le32 cp_blkaddr;		/* start block address of checkpoपूर्णांक */
	__le32 sit_blkaddr;		/* start block address of SIT */
	__le32 nat_blkaddr;		/* start block address of NAT */
	__le32 ssa_blkaddr;		/* start block address of SSA */
	__le32 मुख्य_blkaddr;		/* start block address of मुख्य area */
	__le32 root_ino;		/* root inode number */
	__le32 node_ino;		/* node inode number */
	__le32 meta_ino;		/* meta inode number */
	__u8 uuid[16];			/* 128-bit uuid क्रम volume */
	__le16 volume_name[MAX_VOLUME_NAME];	/* volume name */
	__le32 extension_count;		/* # of extensions below */
	__u8 extension_list[F2FS_MAX_EXTENSION][F2FS_EXTENSION_LEN];/* extension array */
	__le32 cp_payload;
	__u8 version[VERSION_LEN];	/* the kernel version */
	__u8 init_version[VERSION_LEN];	/* the initial kernel version */
	__le32 feature;			/* defined features */
	__u8 encryption_level;		/* versioning level क्रम encryption */
	__u8 encrypt_pw_salt[16];	/* Salt used क्रम string2key algorithm */
	काष्ठा f2fs_device devs[MAX_DEVICES];	/* device list */
	__le32 qf_ino[F2FS_MAX_QUOTAS];	/* quota inode numbers */
	__u8 hot_ext_count;		/* # of hot file extension */
	__le16  s_encoding;		/* Filename अक्षरset encoding */
	__le16  s_encoding_flags;	/* Filename अक्षरset encoding flags */
	__u8 reserved[306];		/* valid reserved region */
	__le32 crc;			/* checksum of superblock */
पूर्ण __packed;

/*
 * For checkpoपूर्णांक
 */
#घोषणा CP_RESIZEFS_FLAG		0x00004000
#घोषणा CP_DISABLED_QUICK_FLAG		0x00002000
#घोषणा CP_DISABLED_FLAG		0x00001000
#घोषणा CP_QUOTA_NEED_FSCK_FLAG		0x00000800
#घोषणा CP_LARGE_NAT_BITMAP_FLAG	0x00000400
#घोषणा CP_NOCRC_RECOVERY_FLAG	0x00000200
#घोषणा CP_TRIMMED_FLAG		0x00000100
#घोषणा CP_NAT_BITS_FLAG	0x00000080
#घोषणा CP_CRC_RECOVERY_FLAG	0x00000040
#घोषणा CP_FASTBOOT_FLAG	0x00000020
#घोषणा CP_FSCK_FLAG		0x00000010
#घोषणा CP_ERROR_FLAG		0x00000008
#घोषणा CP_COMPACT_SUM_FLAG	0x00000004
#घोषणा CP_ORPHAN_PRESENT_FLAG	0x00000002
#घोषणा CP_UMOUNT_FLAG		0x00000001

#घोषणा F2FS_CP_PACKS		2	/* # of checkpoपूर्णांक packs */

काष्ठा f2fs_checkpoपूर्णांक अणु
	__le64 checkpoपूर्णांक_ver;		/* checkpoपूर्णांक block version number */
	__le64 user_block_count;	/* # of user blocks */
	__le64 valid_block_count;	/* # of valid blocks in मुख्य area */
	__le32 rsvd_segment_count;	/* # of reserved segments क्रम gc */
	__le32 overprov_segment_count;	/* # of overprovision segments */
	__le32 मुक्त_segment_count;	/* # of मुक्त segments in मुख्य area */

	/* inक्रमmation of current node segments */
	__le32 cur_node_segno[MAX_ACTIVE_NODE_LOGS];
	__le16 cur_node_blkoff[MAX_ACTIVE_NODE_LOGS];
	/* inक्रमmation of current data segments */
	__le32 cur_data_segno[MAX_ACTIVE_DATA_LOGS];
	__le16 cur_data_blkoff[MAX_ACTIVE_DATA_LOGS];
	__le32 ckpt_flags;		/* Flags : umount and journal_present */
	__le32 cp_pack_total_block_count;	/* total # of one cp pack */
	__le32 cp_pack_start_sum;	/* start block number of data summary */
	__le32 valid_node_count;	/* Total number of valid nodes */
	__le32 valid_inode_count;	/* Total number of valid inodes */
	__le32 next_मुक्त_nid;		/* Next मुक्त node number */
	__le32 sit_ver_biपंचांगap_bytesize;	/* Default value 64 */
	__le32 nat_ver_biपंचांगap_bytesize; /* Default value 256 */
	__le32 checksum_offset;		/* checksum offset inside cp block */
	__le64 elapsed_समय;		/* mounted समय */
	/* allocation type of current segment */
	अचिन्हित अक्षर alloc_type[MAX_ACTIVE_LOGS];

	/* SIT and NAT version biपंचांगap */
	अचिन्हित अक्षर sit_nat_version_biपंचांगap[];
पूर्ण __packed;

#घोषणा CP_CHKSUM_OFFSET	4092	/* शेष chksum offset in checkpoपूर्णांक */
#घोषणा CP_MIN_CHKSUM_OFFSET						\
	(दुरत्व(काष्ठा f2fs_checkpoपूर्णांक, sit_nat_version_biपंचांगap))

/*
 * For orphan inode management
 */
#घोषणा F2FS_ORPHANS_PER_BLOCK	1020

#घोषणा GET_ORPHAN_BLOCKS(n)	(((n) + F2FS_ORPHANS_PER_BLOCK - 1) / \
					F2FS_ORPHANS_PER_BLOCK)

काष्ठा f2fs_orphan_block अणु
	__le32 ino[F2FS_ORPHANS_PER_BLOCK];	/* inode numbers */
	__le32 reserved;	/* reserved */
	__le16 blk_addr;	/* block index in current CP */
	__le16 blk_count;	/* Number of orphan inode blocks in CP */
	__le32 entry_count;	/* Total number of orphan nodes in current CP */
	__le32 check_sum;	/* CRC32 क्रम orphan inode block */
पूर्ण __packed;

/*
 * For NODE काष्ठाure
 */
काष्ठा f2fs_extent अणु
	__le32 fofs;		/* start file offset of the extent */
	__le32 blk;		/* start block address of the extent */
	__le32 len;		/* length of the extent */
पूर्ण __packed;

#घोषणा F2FS_NAME_LEN		255
/* 200 bytes क्रम अंतरभूत xattrs by शेष */
#घोषणा DEFAULT_INLINE_XATTR_ADDRS	50
#घोषणा DEF_ADDRS_PER_INODE	923	/* Address Poपूर्णांकers in an Inode */
#घोषणा CUR_ADDRS_PER_INODE(inode)	(DEF_ADDRS_PER_INODE - \
					get_extra_isize(inode))
#घोषणा DEF_NIDS_PER_INODE	5	/* Node IDs in an Inode */
#घोषणा ADDRS_PER_INODE(inode)	addrs_per_inode(inode)
#घोषणा DEF_ADDRS_PER_BLOCK	1018	/* Address Poपूर्णांकers in a Direct Block */
#घोषणा ADDRS_PER_BLOCK(inode)	addrs_per_block(inode)
#घोषणा NIDS_PER_BLOCK		1018	/* Node IDs in an Indirect Block */

#घोषणा ADDRS_PER_PAGE(page, inode)	\
	(IS_INODE(page) ? ADDRS_PER_INODE(inode) : ADDRS_PER_BLOCK(inode))

#घोषणा	NODE_सूची1_BLOCK		(DEF_ADDRS_PER_INODE + 1)
#घोषणा	NODE_सूची2_BLOCK		(DEF_ADDRS_PER_INODE + 2)
#घोषणा	NODE_IND1_BLOCK		(DEF_ADDRS_PER_INODE + 3)
#घोषणा	NODE_IND2_BLOCK		(DEF_ADDRS_PER_INODE + 4)
#घोषणा	NODE_DIND_BLOCK		(DEF_ADDRS_PER_INODE + 5)

#घोषणा F2FS_INLINE_XATTR	0x01	/* file अंतरभूत xattr flag */
#घोषणा F2FS_INLINE_DATA	0x02	/* file अंतरभूत data flag */
#घोषणा F2FS_INLINE_DENTRY	0x04	/* file अंतरभूत dentry flag */
#घोषणा F2FS_DATA_EXIST		0x08	/* file अंतरभूत data exist flag */
#घोषणा F2FS_INLINE_DOTS	0x10	/* file having implicit करोt dentries */
#घोषणा F2FS_EXTRA_ATTR		0x20	/* file having extra attribute */
#घोषणा F2FS_PIN_खाता		0x40	/* file should not be gced */

काष्ठा f2fs_inode अणु
	__le16 i_mode;			/* file mode */
	__u8 i_advise;			/* file hपूर्णांकs */
	__u8 i_अंतरभूत;			/* file अंतरभूत flags */
	__le32 i_uid;			/* user ID */
	__le32 i_gid;			/* group ID */
	__le32 i_links;			/* links count */
	__le64 i_size;			/* file size in bytes */
	__le64 i_blocks;		/* file size in blocks */
	__le64 i_aसमय;			/* access समय */
	__le64 i_स_समय;			/* change समय */
	__le64 i_mसमय;			/* modअगरication समय */
	__le32 i_aसमय_nsec;		/* access समय in nano scale */
	__le32 i_स_समय_nsec;		/* change समय in nano scale */
	__le32 i_mसमय_nsec;		/* modअगरication समय in nano scale */
	__le32 i_generation;		/* file version (क्रम NFS) */
	जोड़ अणु
		__le32 i_current_depth;	/* only क्रम directory depth */
		__le16 i_gc_failures;	/*
					 * # of gc failures on pinned file.
					 * only क्रम regular files.
					 */
	पूर्ण;
	__le32 i_xattr_nid;		/* nid to save xattr */
	__le32 i_flags;			/* file attributes */
	__le32 i_pino;			/* parent inode number */
	__le32 i_namelen;		/* file name length */
	__u8 i_name[F2FS_NAME_LEN];	/* file name क्रम SPOR */
	__u8 i_dir_level;		/* dentry_level क्रम large dir */

	काष्ठा f2fs_extent i_ext;	/* caching a largest extent */

	जोड़ अणु
		काष्ठा अणु
			__le16 i_extra_isize;	/* extra inode attribute size */
			__le16 i_अंतरभूत_xattr_size;	/* अंतरभूत xattr size, unit: 4 bytes */
			__le32 i_projid;	/* project id */
			__le32 i_inode_checksum;/* inode meta checksum */
			__le64 i_crसमय;	/* creation समय */
			__le32 i_crसमय_nsec;	/* creation समय in nano scale */
			__le64 i_compr_blocks;	/* # of compressed blocks */
			__u8 i_compress_algorithm;	/* compress algorithm */
			__u8 i_log_cluster_size;	/* log of cluster size */
			__le16 i_compress_flag;		/* compress flag */
						/* 0 bit: chksum flag
						 * [10,15] bits: compress level
						 */
			__le32 i_extra_end[0];	/* क्रम attribute size calculation */
		पूर्ण __packed;
		__le32 i_addr[DEF_ADDRS_PER_INODE];	/* Poपूर्णांकers to data blocks */
	पूर्ण;
	__le32 i_nid[DEF_NIDS_PER_INODE];	/* direct(2), indirect(2),
						द्विगुन_indirect(1) node id */
पूर्ण __packed;

काष्ठा direct_node अणु
	__le32 addr[DEF_ADDRS_PER_BLOCK];	/* array of data block address */
पूर्ण __packed;

काष्ठा indirect_node अणु
	__le32 nid[NIDS_PER_BLOCK];	/* array of data block address */
पूर्ण __packed;

क्रमागत अणु
	COLD_BIT_SHIFT = 0,
	FSYNC_BIT_SHIFT,
	DENT_BIT_SHIFT,
	OFFSET_BIT_SHIFT
पूर्ण;

#घोषणा OFFSET_BIT_MASK		(0x07)	/* (0x01 << OFFSET_BIT_SHIFT) - 1 */

काष्ठा node_footer अणु
	__le32 nid;		/* node id */
	__le32 ino;		/* inode number */
	__le32 flag;		/* include cold/fsync/dentry marks and offset */
	__le64 cp_ver;		/* checkpoपूर्णांक version */
	__le32 next_blkaddr;	/* next node page block address */
पूर्ण __packed;

काष्ठा f2fs_node अणु
	/* can be one of three types: inode, direct, and indirect types */
	जोड़ अणु
		काष्ठा f2fs_inode i;
		काष्ठा direct_node dn;
		काष्ठा indirect_node in;
	पूर्ण;
	काष्ठा node_footer footer;
पूर्ण __packed;

/*
 * For NAT entries
 */
#घोषणा NAT_ENTRY_PER_BLOCK (PAGE_SIZE / माप(काष्ठा f2fs_nat_entry))

काष्ठा f2fs_nat_entry अणु
	__u8 version;		/* latest version of cached nat entry */
	__le32 ino;		/* inode number */
	__le32 block_addr;	/* block address */
पूर्ण __packed;

काष्ठा f2fs_nat_block अणु
	काष्ठा f2fs_nat_entry entries[NAT_ENTRY_PER_BLOCK];
पूर्ण __packed;

/*
 * For SIT entries
 *
 * Each segment is 2MB in size by शेष so that a biपंचांगap क्रम validity of
 * there-in blocks should occupy 64 bytes, 512 bits.
 * Not allow to change this.
 */
#घोषणा SIT_VBLOCK_MAP_SIZE 64
#घोषणा SIT_ENTRY_PER_BLOCK (PAGE_SIZE / माप(काष्ठा f2fs_sit_entry))

/*
 * F2FS uses 4 bytes to represent block address. As a result, supported size of
 * disk is 16 TB and it equals to 16 * 1024 * 1024 / 2 segments.
 */
#घोषणा F2FS_MAX_SEGMENT       ((16 * 1024 * 1024) / 2)

/*
 * Note that f2fs_sit_entry->vblocks has the following bit-field inक्रमmation.
 * [15:10] : allocation type such as CURSEG_XXXX_TYPE
 * [9:0] : valid block count
 */
#घोषणा SIT_VBLOCKS_SHIFT	10
#घोषणा SIT_VBLOCKS_MASK	((1 << SIT_VBLOCKS_SHIFT) - 1)
#घोषणा GET_SIT_VBLOCKS(raw_sit)				\
	(le16_to_cpu((raw_sit)->vblocks) & SIT_VBLOCKS_MASK)
#घोषणा GET_SIT_TYPE(raw_sit)					\
	((le16_to_cpu((raw_sit)->vblocks) & ~SIT_VBLOCKS_MASK)	\
	 >> SIT_VBLOCKS_SHIFT)

काष्ठा f2fs_sit_entry अणु
	__le16 vblocks;				/* reference above */
	__u8 valid_map[SIT_VBLOCK_MAP_SIZE];	/* biपंचांगap क्रम valid blocks */
	__le64 mसमय;				/* segment age क्रम cleaning */
पूर्ण __packed;

काष्ठा f2fs_sit_block अणु
	काष्ठा f2fs_sit_entry entries[SIT_ENTRY_PER_BLOCK];
पूर्ण __packed;

/*
 * For segment summary
 *
 * One summary block contains exactly 512 summary entries, which represents
 * exactly 2MB segment by शेष. Not allow to change the basic units.
 *
 * NOTE: For initializing fields, you must use set_summary
 *
 * - If data page, nid represents dnode's nid
 * - If node page, nid represents the node page's nid.
 *
 * The ofs_in_node is used by only data page. It represents offset
 * from node's page's beginning to get a data block address.
 * ex) data_blkaddr = (block_t)(nodepage_start_address + ofs_in_node)
 */
#घोषणा ENTRIES_IN_SUM		512
#घोषणा	SUMMARY_SIZE		(7)	/* माप(काष्ठा summary) */
#घोषणा	SUM_FOOTER_SIZE		(5)	/* माप(काष्ठा summary_footer) */
#घोषणा SUM_ENTRY_SIZE		(SUMMARY_SIZE * ENTRIES_IN_SUM)

/* a summary entry क्रम a 4KB-sized block in a segment */
काष्ठा f2fs_summary अणु
	__le32 nid;		/* parent node id */
	जोड़ अणु
		__u8 reserved[3];
		काष्ठा अणु
			__u8 version;		/* node version number */
			__le16 ofs_in_node;	/* block index in parent node */
		पूर्ण __packed;
	पूर्ण;
पूर्ण __packed;

/* summary block type, node or data, is stored to the summary_footer */
#घोषणा SUM_TYPE_NODE		(1)
#घोषणा SUM_TYPE_DATA		(0)

काष्ठा summary_footer अणु
	अचिन्हित अक्षर entry_type;	/* SUM_TYPE_XXX */
	__le32 check_sum;		/* summary checksum */
पूर्ण __packed;

#घोषणा SUM_JOURNAL_SIZE	(F2FS_BLKSIZE - SUM_FOOTER_SIZE -\
				SUM_ENTRY_SIZE)
#घोषणा NAT_JOURNAL_ENTRIES	((SUM_JOURNAL_SIZE - 2) /\
				माप(काष्ठा nat_journal_entry))
#घोषणा NAT_JOURNAL_RESERVED	((SUM_JOURNAL_SIZE - 2) %\
				माप(काष्ठा nat_journal_entry))
#घोषणा SIT_JOURNAL_ENTRIES	((SUM_JOURNAL_SIZE - 2) /\
				माप(काष्ठा sit_journal_entry))
#घोषणा SIT_JOURNAL_RESERVED	((SUM_JOURNAL_SIZE - 2) %\
				माप(काष्ठा sit_journal_entry))

/* Reserved area should make size of f2fs_extra_info equals to
 * that of nat_journal and sit_journal.
 */
#घोषणा EXTRA_INFO_RESERVED	(SUM_JOURNAL_SIZE - 2 - 8)

/*
 * frequently updated NAT/SIT entries can be stored in the spare area in
 * summary blocks
 */
क्रमागत अणु
	NAT_JOURNAL = 0,
	SIT_JOURNAL
पूर्ण;

काष्ठा nat_journal_entry अणु
	__le32 nid;
	काष्ठा f2fs_nat_entry ne;
पूर्ण __packed;

काष्ठा nat_journal अणु
	काष्ठा nat_journal_entry entries[NAT_JOURNAL_ENTRIES];
	__u8 reserved[NAT_JOURNAL_RESERVED];
पूर्ण __packed;

काष्ठा sit_journal_entry अणु
	__le32 segno;
	काष्ठा f2fs_sit_entry se;
पूर्ण __packed;

काष्ठा sit_journal अणु
	काष्ठा sit_journal_entry entries[SIT_JOURNAL_ENTRIES];
	__u8 reserved[SIT_JOURNAL_RESERVED];
पूर्ण __packed;

काष्ठा f2fs_extra_info अणु
	__le64 kbytes_written;
	__u8 reserved[EXTRA_INFO_RESERVED];
पूर्ण __packed;

काष्ठा f2fs_journal अणु
	जोड़ अणु
		__le16 n_nats;
		__le16 n_sits;
	पूर्ण;
	/* spare area is used by NAT or SIT journals or extra info */
	जोड़ अणु
		काष्ठा nat_journal nat_j;
		काष्ठा sit_journal sit_j;
		काष्ठा f2fs_extra_info info;
	पूर्ण;
पूर्ण __packed;

/* 4KB-sized summary block काष्ठाure */
काष्ठा f2fs_summary_block अणु
	काष्ठा f2fs_summary entries[ENTRIES_IN_SUM];
	काष्ठा f2fs_journal journal;
	काष्ठा summary_footer footer;
पूर्ण __packed;

/*
 * For directory operations
 */
#घोषणा F2FS_DOT_HASH		0
#घोषणा F2FS_DDOT_HASH		F2FS_DOT_HASH
#घोषणा F2FS_MAX_HASH		(~((0x3ULL) << 62))
#घोषणा F2FS_HASH_COL_BIT	((0x1ULL) << 63)

प्रकार __le32	f2fs_hash_t;

/* One directory entry slot covers 8bytes-दीर्घ file name */
#घोषणा F2FS_SLOT_LEN		8
#घोषणा F2FS_SLOT_LEN_BITS	3

#घोषणा GET_DENTRY_SLOTS(x) (((x) + F2FS_SLOT_LEN - 1) >> F2FS_SLOT_LEN_BITS)

/* MAX level क्रम dir lookup */
#घोषणा MAX_सूची_HASH_DEPTH	63

/* MAX buckets in one level of dir */
#घोषणा MAX_सूची_BUCKETS		(1 << ((MAX_सूची_HASH_DEPTH / 2) - 1))

/*
 * space utilization of regular dentry and अंतरभूत dentry (w/o extra reservation)
 *		regular dentry		अंतरभूत dentry (def)	अंतरभूत dentry (min)
 * biपंचांगap	1 * 27 = 27		1 * 23 = 23		1 * 1 = 1
 * reserved	1 * 3 = 3		1 * 7 = 7		1 * 1 = 1
 * dentry	11 * 214 = 2354		11 * 182 = 2002		11 * 2 = 22
 * filename	8 * 214 = 1712		8 * 182 = 1456		8 * 2 = 16
 * total	4096			3488			40
 *
 * Note: there are more reserved space in अंतरभूत dentry than in regular
 * dentry, when converting अंतरभूत dentry we should handle this carefully.
 */
#घोषणा NR_DENTRY_IN_BLOCK	214	/* the number of dentry in a block */
#घोषणा SIZE_OF_सूची_ENTRY	11	/* by byte */
#घोषणा SIZE_OF_DENTRY_BITMAP	((NR_DENTRY_IN_BLOCK + BITS_PER_BYTE - 1) / \
					BITS_PER_BYTE)
#घोषणा SIZE_OF_RESERVED	(PAGE_SIZE - ((SIZE_OF_सूची_ENTRY + \
				F2FS_SLOT_LEN) * \
				NR_DENTRY_IN_BLOCK + SIZE_OF_DENTRY_BITMAP))
#घोषणा MIN_INLINE_DENTRY_SIZE		40	/* just include '.' and '..' entries */

/* One directory entry slot representing F2FS_SLOT_LEN-sized file name */
काष्ठा f2fs_dir_entry अणु
	__le32 hash_code;	/* hash code of file name */
	__le32 ino;		/* inode number */
	__le16 name_len;	/* length of file name */
	__u8 file_type;		/* file type */
पूर्ण __packed;

/* 4KB-sized directory entry block */
काष्ठा f2fs_dentry_block अणु
	/* validity biपंचांगap क्रम directory entries in each block */
	__u8 dentry_biपंचांगap[SIZE_OF_DENTRY_BITMAP];
	__u8 reserved[SIZE_OF_RESERVED];
	काष्ठा f2fs_dir_entry dentry[NR_DENTRY_IN_BLOCK];
	__u8 filename[NR_DENTRY_IN_BLOCK][F2FS_SLOT_LEN];
पूर्ण __packed;

/* file types used in inode_info->flags */
क्रमागत अणु
	F2FS_FT_UNKNOWN,
	F2FS_FT_REG_खाता,
	F2FS_FT_सूची,
	F2FS_FT_CHRDEV,
	F2FS_FT_BLKDEV,
	F2FS_FT_FIFO,
	F2FS_FT_SOCK,
	F2FS_FT_SYMLINK,
	F2FS_FT_MAX
पूर्ण;

#घोषणा S_SHIFT 12

#घोषणा	F2FS_DEF_PROJID		0	/* शेष project ID */

#पूर्ण_अगर  /* _LINUX_F2FS_FS_H */
