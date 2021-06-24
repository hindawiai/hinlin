<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * nilfs2_ondisk.h - NILFS2 on-disk काष्ठाures
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 */
/*
 *  linux/include/linux/ext2_fs.h
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

#अगर_अघोषित _LINUX_NILFS2_ONDISK_H
#घोषणा _LINUX_NILFS2_ONDISK_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा NILFS_INODE_BMAP_SIZE	7

/**
 * काष्ठा nilfs_inode - काष्ठाure of an inode on disk
 * @i_blocks: blocks count
 * @i_size: size in bytes
 * @i_स_समय: creation समय (seconds)
 * @i_mसमय: modअगरication समय (seconds)
 * @i_स_समय_nsec: creation समय (nano seconds)
 * @i_mसमय_nsec: modअगरication समय (nano seconds)
 * @i_uid: user id
 * @i_gid: group id
 * @i_mode: file mode
 * @i_links_count: links count
 * @i_flags: file flags
 * @i_bmap: block mapping
 * @i_xattr: extended attributes
 * @i_generation: file generation (क्रम NFS)
 * @i_pad: padding
 */
काष्ठा nilfs_inode अणु
	__le64	i_blocks;
	__le64	i_size;
	__le64	i_स_समय;
	__le64	i_mसमय;
	__le32	i_स_समय_nsec;
	__le32	i_mसमय_nsec;
	__le32	i_uid;
	__le32	i_gid;
	__le16	i_mode;
	__le16	i_links_count;
	__le32	i_flags;
	__le64	i_bmap[NILFS_INODE_BMAP_SIZE];
#घोषणा i_device_code	i_bmap[0]
	__le64	i_xattr;
	__le32	i_generation;
	__le32	i_pad;
पूर्ण;

#घोषणा NILFS_MIN_INODE_SIZE		128

/**
 * काष्ठा nilfs_super_root - काष्ठाure of super root
 * @sr_sum: check sum
 * @sr_bytes: byte count of the काष्ठाure
 * @sr_flags: flags (reserved)
 * @sr_nongc_स_समय: ग_लिखो समय of the last segment not क्रम cleaner operation
 * @sr_dat: DAT file inode
 * @sr_cpfile: checkpoपूर्णांक file inode
 * @sr_sufile: segment usage file inode
 */
काष्ठा nilfs_super_root अणु
	__le32 sr_sum;
	__le16 sr_bytes;
	__le16 sr_flags;
	__le64 sr_nongc_स_समय;
	काष्ठा nilfs_inode sr_dat;
	काष्ठा nilfs_inode sr_cpfile;
	काष्ठा nilfs_inode sr_sufile;
पूर्ण;

#घोषणा NILFS_SR_MDT_OFFSET(inode_size, i)  \
	((अचिन्हित दीर्घ)&((काष्ठा nilfs_super_root *)0)->sr_dat + \
			(inode_size) * (i))
#घोषणा NILFS_SR_DAT_OFFSET(inode_size)     NILFS_SR_MDT_OFFSET(inode_size, 0)
#घोषणा NILFS_SR_CPखाता_OFFSET(inode_size)  NILFS_SR_MDT_OFFSET(inode_size, 1)
#घोषणा NILFS_SR_SUखाता_OFFSET(inode_size)  NILFS_SR_MDT_OFFSET(inode_size, 2)
#घोषणा NILFS_SR_BYTES(inode_size)	    NILFS_SR_MDT_OFFSET(inode_size, 3)

/*
 * Maximal mount counts
 */
#घोषणा NILFS_DFL_MAX_MNT_COUNT		50      /* 50 mounts */

/*
 * File प्रणाली states (sbp->s_state, nilfs->ns_mount_state)
 */
#घोषणा NILFS_VALID_FS			0x0001  /* Unmounted cleanly */
#घोषणा NILFS_ERROR_FS			0x0002  /* Errors detected */
#घोषणा NILFS_RESIZE_FS			0x0004	/* Resize required */

/*
 * Mount flags (sbi->s_mount_opt)
 */
#घोषणा NILFS_MOUNT_ERROR_MODE		0x0070  /* Error mode mask */
#घोषणा NILFS_MOUNT_ERRORS_CONT		0x0010  /* Continue on errors */
#घोषणा NILFS_MOUNT_ERRORS_RO		0x0020  /* Remount fs ro on errors */
#घोषणा NILFS_MOUNT_ERRORS_PANIC	0x0040  /* Panic on errors */
#घोषणा NILFS_MOUNT_BARRIER		0x1000  /* Use block barriers */
#घोषणा NILFS_MOUNT_STRICT_ORDER	0x2000  /*
						 * Apply strict in-order
						 * semantics also क्रम data
						 */
#घोषणा NILFS_MOUNT_NORECOVERY		0x4000  /*
						 * Disable ग_लिखो access during
						 * mount-समय recovery
						 */
#घोषणा NILFS_MOUNT_DISCARD		0x8000  /* Issue DISCARD requests */


/**
 * काष्ठा nilfs_super_block - काष्ठाure of super block on disk
 */
काष्ठा nilfs_super_block अणु
/*00*/	__le32	s_rev_level;		/* Revision level */
	__le16	s_minor_rev_level;	/* minor revision level */
	__le16	s_magic;		/* Magic signature */

	__le16  s_bytes;		/*
					 * Bytes count of CRC calculation
					 * क्रम this काष्ठाure. s_reserved
					 * is excluded.
					 */
	__le16  s_flags;		/* flags */
	__le32  s_crc_seed;		/* Seed value of CRC calculation */
/*10*/	__le32	s_sum;			/* Check sum of super block */

	__le32	s_log_block_size;	/*
					 * Block size represented as follows
					 * blocksize =
					 *     1 << (s_log_block_size + 10)
					 */
	__le64  s_nsegments;		/* Number of segments in fileप्रणाली */
/*20*/	__le64  s_dev_size;		/* block device size in bytes */
	__le64	s_first_data_block;	/* 1st seg disk block number */
/*30*/	__le32  s_blocks_per_segment;   /* number of blocks per full segment */
	__le32	s_r_segments_percentage; /* Reserved segments percentage */

	__le64  s_last_cno;		/* Last checkpoपूर्णांक number */
/*40*/	__le64  s_last_pseg;		/* disk block addr pseg written last */
	__le64  s_last_seq;             /* seq. number of seg written last */
/*50*/	__le64	s_मुक्त_blocks_count;	/* Free blocks count */

	__le64	s_स_समय;		/*
					 * Creation समय (execution समय of
					 * newfs)
					 */
/*60*/	__le64	s_mसमय;		/* Mount समय */
	__le64	s_wसमय;		/* Write समय */
/*70*/	__le16	s_mnt_count;		/* Mount count */
	__le16	s_max_mnt_count;	/* Maximal mount count */
	__le16	s_state;		/* File प्रणाली state */
	__le16	s_errors;		/* Behaviour when detecting errors */
	__le64	s_lastcheck;		/* समय of last check */

/*80*/	__le32	s_checkपूर्णांकerval;	/* max. समय between checks */
	__le32	s_creator_os;		/* OS */
	__le16	s_def_resuid;		/* Default uid क्रम reserved blocks */
	__le16	s_def_resgid;		/* Default gid क्रम reserved blocks */
	__le32	s_first_ino;		/* First non-reserved inode */

/*90*/	__le16  s_inode_size;		/* Size of an inode */
	__le16  s_dat_entry_size;       /* Size of a dat entry */
	__le16  s_checkpoपूर्णांक_size;      /* Size of a checkpoपूर्णांक */
	__le16	s_segment_usage_size;	/* Size of a segment usage */

/*98*/	__u8	s_uuid[16];		/* 128-bit uuid क्रम volume */
/*A8*/	अक्षर	s_volume_name[80];	/* volume name */

/*F8*/	__le32  s_c_पूर्णांकerval;           /* Commit पूर्णांकerval of segment */
	__le32  s_c_block_max;          /*
					 * Threshold of data amount क्रम
					 * the segment स्थिरruction
					 */
/*100*/	__le64  s_feature_compat;	/* Compatible feature set */
	__le64  s_feature_compat_ro;	/* Read-only compatible feature set */
	__le64  s_feature_incompat;	/* Incompatible feature set */
	__u32	s_reserved[186];	/* padding to the end of the block */
पूर्ण;

/*
 * Codes क्रम operating प्रणालीs
 */
#घोषणा NILFS_OS_LINUX		0
/* Codes from 1 to 4 are reserved to keep compatibility with ext2 creator-OS */

/*
 * Revision levels
 */
#घोषणा NILFS_CURRENT_REV	2	/* current major revision */
#घोषणा NILFS_MINOR_REV		0	/* minor revision */
#घोषणा NILFS_MIN_SUPP_REV	2	/* minimum supported revision */

/*
 * Feature set definitions
 *
 * If there is a bit set in the incompatible feature set that the kernel
 * करोesn't know about, it should refuse to mount the fileप्रणाली.
 */
#घोषणा NILFS_FEATURE_COMPAT_RO_BLOCK_COUNT	0x00000001ULL

#घोषणा NILFS_FEATURE_COMPAT_SUPP	0ULL
#घोषणा NILFS_FEATURE_COMPAT_RO_SUPP	NILFS_FEATURE_COMPAT_RO_BLOCK_COUNT
#घोषणा NILFS_FEATURE_INCOMPAT_SUPP	0ULL

/*
 * Bytes count of super_block क्रम CRC-calculation
 */
#घोषणा NILFS_SB_BYTES  \
	((दीर्घ)&((काष्ठा nilfs_super_block *)0)->s_reserved)

/*
 * Special inode number
 */
#घोषणा NILFS_ROOT_INO		2	/* Root file inode */
#घोषणा NILFS_DAT_INO		3	/* DAT file */
#घोषणा NILFS_CPखाता_INO	4	/* checkpoपूर्णांक file */
#घोषणा NILFS_SUखाता_INO	5	/* segment usage file */
#घोषणा NILFS_Iखाता_INO		6	/* अगरile */
#घोषणा NILFS_ATIME_INO		7	/* Aसमय file (reserved) */
#घोषणा NILFS_XATTR_INO		8	/* Xattribute file (reserved) */
#घोषणा NILFS_SKETCH_INO	10	/* Sketch file */
#घोषणा NILFS_USER_INO		11	/* Fisrt user's file inode number */

#घोषणा NILFS_SB_OFFSET_BYTES	1024	/* byte offset of nilfs superblock */

#घोषणा NILFS_SEG_MIN_BLOCKS	16	/*
					 * Minimum number of blocks in
					 * a full segment
					 */
#घोषणा NILFS_PSEG_MIN_BLOCKS	2	/*
					 * Minimum number of blocks in
					 * a partial segment
					 */
#घोषणा NILFS_MIN_NRSVSEGS	8	/*
					 * Minimum number of reserved
					 * segments
					 */

/*
 * We call DAT, cpfile, and sufile root metadata files.  Inodes of
 * these files are written in super root block instead of अगरile, and
 * garbage collector करोesn't keep any past versions of these files.
 */
#घोषणा NILFS_ROOT_METADATA_खाता(ino) \
	((ino) >= NILFS_DAT_INO && (ino) <= NILFS_SUखाता_INO)

/*
 * bytes offset of secondary super block
 */
#घोषणा NILFS_SB2_OFFSET_BYTES(devsize)	((((devsize) >> 12) - 1) << 12)

/*
 * Maximal count of links to a file
 */
#घोषणा NILFS_LINK_MAX		32000

/*
 * Structure of a directory entry
 *  (Same as ext2)
 */

#घोषणा NILFS_NAME_LEN 255

/*
 * Block size limitations
 */
#घोषणा NILFS_MIN_BLOCK_SIZE		1024
#घोषणा NILFS_MAX_BLOCK_SIZE		65536

/*
 * The new version of the directory entry.  Since V0 काष्ठाures are
 * stored in पूर्णांकel byte order, and the name_len field could never be
 * bigger than 255 अक्षरs, it's safe to reclaim the extra byte क्रम the
 * file_type field.
 */
काष्ठा nilfs_dir_entry अणु
	__le64	inode;			/* Inode number */
	__le16	rec_len;		/* Directory entry length */
	__u8	name_len;		/* Name length */
	__u8	file_type;		/* Dir entry type (file, dir, etc) */
	अक्षर	name[NILFS_NAME_LEN];	/* File name */
	अक्षर    pad;
पूर्ण;

/*
 * NILFS directory file types.  Only the low 3 bits are used.  The
 * other bits are reserved क्रम now.
 */
क्रमागत अणु
	NILFS_FT_UNKNOWN,
	NILFS_FT_REG_खाता,
	NILFS_FT_सूची,
	NILFS_FT_CHRDEV,
	NILFS_FT_BLKDEV,
	NILFS_FT_FIFO,
	NILFS_FT_SOCK,
	NILFS_FT_SYMLINK,
	NILFS_FT_MAX
पूर्ण;

/*
 * NILFS_सूची_PAD defines the directory entries boundaries
 *
 * NOTE: It must be a multiple of 8
 */
#घोषणा NILFS_सूची_PAD			8
#घोषणा NILFS_सूची_ROUND			(NILFS_सूची_PAD - 1)
#घोषणा NILFS_सूची_REC_LEN(name_len)	(((name_len) + 12 + NILFS_सूची_ROUND) & \
					~NILFS_सूची_ROUND)
#घोषणा NILFS_MAX_REC_LEN		((1 << 16) - 1)

/**
 * काष्ठा nilfs_finfo - file inक्रमmation
 * @fi_ino: inode number
 * @fi_cno: checkpoपूर्णांक number
 * @fi_nblocks: number of blocks (including पूर्णांकermediate blocks)
 * @fi_ndatablk: number of file data blocks
 */
काष्ठा nilfs_finfo अणु
	__le64 fi_ino;
	__le64 fi_cno;
	__le32 fi_nblocks;
	__le32 fi_ndatablk;
पूर्ण;

/**
 * काष्ठा nilfs_binfo_v - inक्रमmation on a data block (except DAT)
 * @bi_vblocknr: भव block number
 * @bi_blkoff: block offset
 */
काष्ठा nilfs_binfo_v अणु
	__le64 bi_vblocknr;
	__le64 bi_blkoff;
पूर्ण;

/**
 * काष्ठा nilfs_binfo_dat - inक्रमmation on a DAT node block
 * @bi_blkoff: block offset
 * @bi_level: level
 * @bi_pad: padding
 */
काष्ठा nilfs_binfo_dat अणु
	__le64 bi_blkoff;
	__u8 bi_level;
	__u8 bi_pad[7];
पूर्ण;

/**
 * जोड़ nilfs_binfo: block inक्रमmation
 * @bi_v: nilfs_binfo_v काष्ठाure
 * @bi_dat: nilfs_binfo_dat काष्ठाure
 */
जोड़ nilfs_binfo अणु
	काष्ठा nilfs_binfo_v bi_v;
	काष्ठा nilfs_binfo_dat bi_dat;
पूर्ण;

/**
 * काष्ठा nilfs_segment_summary - segment summary header
 * @ss_datasum: checksum of data
 * @ss_sumsum: checksum of segment summary
 * @ss_magic: magic number
 * @ss_bytes: size of this काष्ठाure in bytes
 * @ss_flags: flags
 * @ss_seq: sequence number
 * @ss_create: creation बारtamp
 * @ss_next: next segment
 * @ss_nblocks: number of blocks
 * @ss_nfinfo: number of finfo काष्ठाures
 * @ss_sumbytes: total size of segment summary in bytes
 * @ss_pad: padding
 * @ss_cno: checkpoपूर्णांक number
 */
काष्ठा nilfs_segment_summary अणु
	__le32 ss_datasum;
	__le32 ss_sumsum;
	__le32 ss_magic;
	__le16 ss_bytes;
	__le16 ss_flags;
	__le64 ss_seq;
	__le64 ss_create;
	__le64 ss_next;
	__le32 ss_nblocks;
	__le32 ss_nfinfo;
	__le32 ss_sumbytes;
	__le32 ss_pad;
	__le64 ss_cno;
	/* array of finfo काष्ठाures */
पूर्ण;

#घोषणा NILFS_SEGSUM_MAGIC	0x1eaffa11  /* segment summary magic number */

/*
 * Segment summary flags
 */
#घोषणा NILFS_SS_LOGBGN 0x0001  /* begins a logical segment */
#घोषणा NILFS_SS_LOGEND 0x0002  /* ends a logical segment */
#घोषणा NILFS_SS_SR     0x0004  /* has super root */
#घोषणा NILFS_SS_SYNDT  0x0008  /* includes data only updates */
#घोषणा NILFS_SS_GC     0x0010  /* segment written क्रम cleaner operation */

/**
 * काष्ठा nilfs_btree_node - header of B-tree node block
 * @bn_flags: flags
 * @bn_level: level
 * @bn_nchildren: number of children
 * @bn_pad: padding
 */
काष्ठा nilfs_btree_node अणु
	__u8 bn_flags;
	__u8 bn_level;
	__le16 bn_nchildren;
	__le32 bn_pad;
पूर्ण;

/* flags */
#घोषणा NILFS_BTREE_NODE_ROOT   0x01

/* level */
#घोषणा NILFS_BTREE_LEVEL_DATA          0
#घोषणा NILFS_BTREE_LEVEL_NODE_MIN      (NILFS_BTREE_LEVEL_DATA + 1)
#घोषणा NILFS_BTREE_LEVEL_MAX           14	/* Max level (exclusive) */

/**
 * काष्ठा nilfs_direct_node - header of built-in bmap array
 * @dn_flags: flags
 * @dn_pad: padding
 */
काष्ठा nilfs_direct_node अणु
	__u8 dn_flags;
	__u8 pad[7];
पूर्ण;

/**
 * काष्ठा nilfs_palloc_group_desc - block group descriptor
 * @pg_nमुक्तs: number of मुक्त entries in block group
 */
काष्ठा nilfs_palloc_group_desc अणु
	__le32 pg_nमुक्तs;
पूर्ण;

/**
 * काष्ठा nilfs_dat_entry - disk address translation entry
 * @de_blocknr: block number
 * @de_start: start checkpoपूर्णांक number
 * @de_end: end checkpoपूर्णांक number
 * @de_rsv: reserved क्रम future use
 */
काष्ठा nilfs_dat_entry अणु
	__le64 de_blocknr;
	__le64 de_start;
	__le64 de_end;
	__le64 de_rsv;
पूर्ण;

#घोषणा NILFS_MIN_DAT_ENTRY_SIZE	32

/**
 * काष्ठा nilfs_snapshot_list - snapshot list
 * @ssl_next: next checkpoपूर्णांक number on snapshot list
 * @ssl_prev: previous checkpoपूर्णांक number on snapshot list
 */
काष्ठा nilfs_snapshot_list अणु
	__le64 ssl_next;
	__le64 ssl_prev;
पूर्ण;

/**
 * काष्ठा nilfs_checkpoपूर्णांक - checkpoपूर्णांक काष्ठाure
 * @cp_flags: flags
 * @cp_checkpoपूर्णांकs_count: checkpoपूर्णांकs count in a block
 * @cp_snapshot_list: snapshot list
 * @cp_cno: checkpoपूर्णांक number
 * @cp_create: creation बारtamp
 * @cp_nblk_inc: number of blocks incremented by this checkpoपूर्णांक
 * @cp_inodes_count: inodes count
 * @cp_blocks_count: blocks count
 * @cp_अगरile_inode: inode of अगरile
 */
काष्ठा nilfs_checkpoपूर्णांक अणु
	__le32 cp_flags;
	__le32 cp_checkpoपूर्णांकs_count;
	काष्ठा nilfs_snapshot_list cp_snapshot_list;
	__le64 cp_cno;
	__le64 cp_create;
	__le64 cp_nblk_inc;
	__le64 cp_inodes_count;
	__le64 cp_blocks_count;

	/*
	 * Do not change the byte offset of अगरile inode.
	 * To keep the compatibility of the disk क्रमmat,
	 * additional fields should be added behind cp_अगरile_inode.
	 */
	काष्ठा nilfs_inode cp_अगरile_inode;
पूर्ण;

#घोषणा NILFS_MIN_CHECKPOINT_SIZE	(64 + NILFS_MIN_INODE_SIZE)

/* checkpoपूर्णांक flags */
क्रमागत अणु
	NILFS_CHECKPOINT_SNAPSHOT,
	NILFS_CHECKPOINT_INVALID,
	NILFS_CHECKPOINT_SKETCH,
	NILFS_CHECKPOपूर्णांक_न्यूनOR,
पूर्ण;

#घोषणा NILFS_CHECKPOINT_FNS(flag, name)				\
अटल अंतरभूत व्योम							\
nilfs_checkpoपूर्णांक_set_##name(काष्ठा nilfs_checkpoपूर्णांक *cp)		\
अणु									\
	cp->cp_flags = __cpu_to_le32(__le32_to_cpu(cp->cp_flags) |	\
				     (1UL << NILFS_CHECKPOINT_##flag));	\
पूर्ण									\
अटल अंतरभूत व्योम							\
nilfs_checkpoपूर्णांक_clear_##name(काष्ठा nilfs_checkpoपूर्णांक *cp)		\
अणु									\
	cp->cp_flags = __cpu_to_le32(__le32_to_cpu(cp->cp_flags) &	\
				   ~(1UL << NILFS_CHECKPOINT_##flag));	\
पूर्ण									\
अटल अंतरभूत पूर्णांक							\
nilfs_checkpoपूर्णांक_##name(स्थिर काष्ठा nilfs_checkpoपूर्णांक *cp)		\
अणु									\
	वापस !!(__le32_to_cpu(cp->cp_flags) &				\
		  (1UL << NILFS_CHECKPOINT_##flag));			\
पूर्ण

NILFS_CHECKPOINT_FNS(SNAPSHOT, snapshot)
NILFS_CHECKPOINT_FNS(INVALID, invalid)
NILFS_CHECKPOINT_FNS(MINOR, minor)

/**
 * काष्ठा nilfs_cpfile_header - checkpoपूर्णांक file header
 * @ch_ncheckpoपूर्णांकs: number of checkpoपूर्णांकs
 * @ch_nsnapshots: number of snapshots
 * @ch_snapshot_list: snapshot list
 */
काष्ठा nilfs_cpfile_header अणु
	__le64 ch_ncheckpoपूर्णांकs;
	__le64 ch_nsnapshots;
	काष्ठा nilfs_snapshot_list ch_snapshot_list;
पूर्ण;

#घोषणा NILFS_CPखाता_FIRST_CHECKPOINT_OFFSET				\
	((माप(काष्ठा nilfs_cpfile_header) +				\
	  माप(काष्ठा nilfs_checkpoपूर्णांक) - 1) /			\
			माप(काष्ठा nilfs_checkpoपूर्णांक))

/**
 * काष्ठा nilfs_segment_usage - segment usage
 * @su_lasपंचांगod: last modअगरied बारtamp
 * @su_nblocks: number of blocks in segment
 * @su_flags: flags
 */
काष्ठा nilfs_segment_usage अणु
	__le64 su_lasपंचांगod;
	__le32 su_nblocks;
	__le32 su_flags;
पूर्ण;

#घोषणा NILFS_MIN_SEGMENT_USAGE_SIZE	16

/* segment usage flag */
क्रमागत अणु
	NILFS_SEGMENT_USAGE_ACTIVE,
	NILFS_SEGMENT_USAGE_सूचीTY,
	NILFS_SEGMENT_USAGE_ERROR,
पूर्ण;

#घोषणा NILFS_SEGMENT_USAGE_FNS(flag, name)				\
अटल अंतरभूत व्योम							\
nilfs_segment_usage_set_##name(काष्ठा nilfs_segment_usage *su)		\
अणु									\
	su->su_flags = __cpu_to_le32(__le32_to_cpu(su->su_flags) |	\
				   (1UL << NILFS_SEGMENT_USAGE_##flag));\
पूर्ण									\
अटल अंतरभूत व्योम							\
nilfs_segment_usage_clear_##name(काष्ठा nilfs_segment_usage *su)	\
अणु									\
	su->su_flags =							\
		__cpu_to_le32(__le32_to_cpu(su->su_flags) &		\
			    ~(1UL << NILFS_SEGMENT_USAGE_##flag));      \
पूर्ण									\
अटल अंतरभूत पूर्णांक							\
nilfs_segment_usage_##name(स्थिर काष्ठा nilfs_segment_usage *su)	\
अणु									\
	वापस !!(__le32_to_cpu(su->su_flags) &				\
		  (1UL << NILFS_SEGMENT_USAGE_##flag));			\
पूर्ण

NILFS_SEGMENT_USAGE_FNS(ACTIVE, active)
NILFS_SEGMENT_USAGE_FNS(सूचीTY, dirty)
NILFS_SEGMENT_USAGE_FNS(ERROR, error)

अटल अंतरभूत व्योम
nilfs_segment_usage_set_clean(काष्ठा nilfs_segment_usage *su)
अणु
	su->su_lasपंचांगod = __cpu_to_le64(0);
	su->su_nblocks = __cpu_to_le32(0);
	su->su_flags = __cpu_to_le32(0);
पूर्ण

अटल अंतरभूत पूर्णांक
nilfs_segment_usage_clean(स्थिर काष्ठा nilfs_segment_usage *su)
अणु
	वापस !__le32_to_cpu(su->su_flags);
पूर्ण

/**
 * काष्ठा nilfs_sufile_header - segment usage file header
 * @sh_ncleansegs: number of clean segments
 * @sh_ndirtysegs: number of dirty segments
 * @sh_last_alloc: last allocated segment number
 */
काष्ठा nilfs_sufile_header अणु
	__le64 sh_ncleansegs;
	__le64 sh_ndirtysegs;
	__le64 sh_last_alloc;
	/* ... */
पूर्ण;

#घोषणा NILFS_SUखाता_FIRST_SEGMENT_USAGE_OFFSET				\
	((माप(काष्ठा nilfs_sufile_header) +				\
	  माप(काष्ठा nilfs_segment_usage) - 1) /			\
			 माप(काष्ठा nilfs_segment_usage))

#पूर्ण_अगर	/* _LINUX_NILFS2_ONDISK_H */
