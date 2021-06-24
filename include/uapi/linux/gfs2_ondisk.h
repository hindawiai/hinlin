<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modअगरy, copy, or redistribute it subject to the terms and conditions
 * of the GNU General Public License v.2.
 */

#अगर_अघोषित __GFS2_ONDISK_DOT_H__
#घोषणा __GFS2_ONDISK_DOT_H__

#समावेश <linux/types.h>

#घोषणा GFS2_MAGIC		0x01161970
#घोषणा GFS2_BASIC_BLOCK	512
#घोषणा GFS2_BASIC_BLOCK_SHIFT	9

/* Lock numbers of the LM_TYPE_NONDISK type */

#घोषणा GFS2_MOUNT_LOCK		0
#घोषणा GFS2_LIVE_LOCK		1
#घोषणा GFS2_FREEZE_LOCK	2
#घोषणा GFS2_RENAME_LOCK	3
#घोषणा GFS2_CONTROL_LOCK	4
#घोषणा GFS2_MOUNTED_LOCK	5

/* Format numbers क्रम various metadata types */

#घोषणा GFS2_FORMAT_NONE	0
#घोषणा GFS2_FORMAT_SB		100
#घोषणा GFS2_FORMAT_RG		200
#घोषणा GFS2_FORMAT_RB		300
#घोषणा GFS2_FORMAT_DI		400
#घोषणा GFS2_FORMAT_IN		500
#घोषणा GFS2_FORMAT_LF		600
#घोषणा GFS2_FORMAT_JD		700
#घोषणा GFS2_FORMAT_LH		800
#घोषणा GFS2_FORMAT_LD		900
#घोषणा GFS2_FORMAT_LB		1000
#घोषणा GFS2_FORMAT_EA		1600
#घोषणा GFS2_FORMAT_ED		1700
#घोषणा GFS2_FORMAT_QC		1400
/* These are क्रमmat numbers क्रम entities contained in files */
#घोषणा GFS2_FORMAT_RI		1100
#घोषणा GFS2_FORMAT_DE		1200
#घोषणा GFS2_FORMAT_QU		1500
/* These are part of the superblock */
#घोषणा GFS2_FORMAT_FS		1802
#घोषणा GFS2_FORMAT_MULTI	1900

/*
 * An on-disk inode number
 */

काष्ठा gfs2_inum अणु
	__be64 no_क्रमmal_ino;
	__be64 no_addr;
पूर्ण;

/*
 * Generic metadata head काष्ठाure
 * Every inplace buffer logged in the journal must start with this.
 */

#घोषणा GFS2_METATYPE_NONE	0
#घोषणा GFS2_METATYPE_SB	1
#घोषणा GFS2_METATYPE_RG	2
#घोषणा GFS2_METATYPE_RB	3
#घोषणा GFS2_METATYPE_DI	4
#घोषणा GFS2_METATYPE_IN	5
#घोषणा GFS2_METATYPE_LF	6
#घोषणा GFS2_METATYPE_JD	7
#घोषणा GFS2_METATYPE_LH	8
#घोषणा GFS2_METATYPE_LD	9
#घोषणा GFS2_METATYPE_LB	12
#घोषणा GFS2_METATYPE_EA	10
#घोषणा GFS2_METATYPE_ED	11
#घोषणा GFS2_METATYPE_QC	14

काष्ठा gfs2_meta_header अणु
	__be32 mh_magic;
	__be32 mh_type;
	__be64 __pad0;		/* Was generation number in gfs1 */
	__be32 mh_क्रमmat;
	/* This जोड़ is to keep userspace happy */
	जोड़ अणु
		__be32 mh_jid;		/* Was incarnation number in gfs1 */
		__be32 __pad1;
	पूर्ण;
पूर्ण;

/*
 * super-block काष्ठाure
 *
 * It's probably good अगर SIZखातापूर्ण_SB <= GFS2_BASIC_BLOCK (512 bytes)
 *
 * Order is important, need to be able to पढ़ो old superblocks to करो on-disk
 * version upgrades.
 */

/* Address of superblock in GFS2 basic blocks */
#घोषणा GFS2_SB_ADDR		128

/* The lock number क्रम the superblock (must be zero) */
#घोषणा GFS2_SB_LOCK		0

/* Requirement:  GFS2_LOCKNAME_LEN % 8 == 0
   Includes: the fencing zero at the end */
#घोषणा GFS2_LOCKNAME_LEN	64

काष्ठा gfs2_sb अणु
	काष्ठा gfs2_meta_header sb_header;

	__be32 sb_fs_क्रमmat;
	__be32 sb_multihost_क्रमmat;
	__u32  __pad0;	/* Was superblock flags in gfs1 */

	__be32 sb_bsize;
	__be32 sb_bsize_shअगरt;
	__u32 __pad1;	/* Was journal segment size in gfs1 */

	काष्ठा gfs2_inum sb_master_dir; /* Was jindex dinode in gfs1 */
	काष्ठा gfs2_inum __pad2; /* Was rindex dinode in gfs1 */
	काष्ठा gfs2_inum sb_root_dir;

	अक्षर sb_lockproto[GFS2_LOCKNAME_LEN];
	अक्षर sb_locktable[GFS2_LOCKNAME_LEN];

	काष्ठा gfs2_inum __pad3; /* Was quota inode in gfs1 */
	काष्ठा gfs2_inum __pad4; /* Was licence inode in gfs1 */
#घोषणा GFS2_HAS_UUID 1
	__u8 sb_uuid[16]; /* The UUID, maybe 0 क्रम backwards compat */
पूर्ण;

/*
 * resource index काष्ठाure
 */

काष्ठा gfs2_rindex अणु
	__be64 ri_addr;	/* grp block disk address */
	__be32 ri_length;	/* length of rgrp header in fs blocks */
	__u32 __pad;

	__be64 ri_data0;	/* first data location */
	__be32 ri_data;	/* num of data blocks in rgrp */

	__be32 ri_bitbytes;	/* number of bytes in data biपंचांगaps */

	__u8 ri_reserved[64];
पूर्ण;

/*
 * resource group header काष्ठाure
 */

/* Number of blocks per byte in rgrp */
#घोषणा GFS2_NBBY		4
#घोषणा GFS2_BIT_SIZE		2
#घोषणा GFS2_BIT_MASK		0x00000003

#घोषणा GFS2_BLKST_FREE		0
#घोषणा GFS2_BLKST_USED		1
#घोषणा GFS2_BLKST_UNLINKED	2
#घोषणा GFS2_BLKST_DINODE	3

#घोषणा GFS2_RGF_JOURNAL	0x00000001
#घोषणा GFS2_RGF_METAONLY	0x00000002
#घोषणा GFS2_RGF_DATAONLY	0x00000004
#घोषणा GFS2_RGF_NOALLOC	0x00000008
#घोषणा GFS2_RGF_TRIMMED	0x00000010

काष्ठा gfs2_inode_lvb अणु
	__be32 ri_magic;
	__be32 __pad;
	__be64 ri_generation_deleted;
पूर्ण;

काष्ठा gfs2_rgrp_lvb अणु
	__be32 rl_magic;
	__be32 rl_flags;
	__be32 rl_मुक्त;
	__be32 rl_dinodes;
	__be64 rl_igeneration;
	__be32 rl_unlinked;
	__be32 __pad;
पूर्ण;

काष्ठा gfs2_rgrp अणु
	काष्ठा gfs2_meta_header rg_header;

	__be32 rg_flags;
	__be32 rg_मुक्त;
	__be32 rg_dinodes;
	जोड़ अणु
		__be32 __pad;
		__be32 rg_skip; /* Distance to the next rgrp in fs blocks */
	पूर्ण;
	__be64 rg_igeneration;
	/* The following 3 fields are duplicated from gfs2_rindex to reduce
	   reliance on the rindex */
	__be64 rg_data0;     /* First data location */
	__be32 rg_data;      /* Number of data blocks in rgrp */
	__be32 rg_bitbytes;  /* Number of bytes in data biपंचांगaps */
	__be32 rg_crc;       /* crc32 of the काष्ठाure with this field 0 */

	__u8 rg_reserved[60]; /* Several fields from gfs1 now reserved */
पूर्ण;

/*
 * quota काष्ठाure
 */

काष्ठा gfs2_quota अणु
	__be64 qu_limit;
	__be64 qu_warn;
	__be64 qu_value;
	__u8 qu_reserved[64];
पूर्ण;

/*
 * dinode काष्ठाure
 */

#घोषणा GFS2_MAX_META_HEIGHT	10
#घोषणा GFS2_सूची_MAX_DEPTH	17

#घोषणा DT2IF(dt) (((dt) << 12) & S_IFMT)
#घोषणा IF2DT(sअगर) (((sअगर) & S_IFMT) >> 12)

क्रमागत अणु
	gfs2fl_Jdata		= 0,
	gfs2fl_ExHash		= 1,
	gfs2fl_Unused		= 2,
	gfs2fl_EaIndirect	= 3,
	gfs2fl_Directio		= 4,
	gfs2fl_Immutable	= 5,
	gfs2fl_AppendOnly	= 6,
	gfs2fl_NoAसमय		= 7,
	gfs2fl_Sync		= 8,
	gfs2fl_System		= 9,
	gfs2fl_TopLevel		= 10,
	gfs2fl_TruncInProg	= 29,
	gfs2fl_InheritDirectio	= 30,
	gfs2fl_InheritJdata	= 31,
पूर्ण;

/* Dinode flags */
#घोषणा GFS2_DIF_JDATA			0x00000001
#घोषणा GFS2_DIF_EXHASH			0x00000002
#घोषणा GFS2_DIF_UNUSED			0x00000004  /* only in gfs1 */
#घोषणा GFS2_DIF_EA_INसूचीECT		0x00000008
#घोषणा GFS2_DIF_सूचीECTIO		0x00000010
#घोषणा GFS2_DIF_IMMUTABLE		0x00000020
#घोषणा GFS2_DIF_APPENDONLY		0x00000040
#घोषणा GFS2_DIF_NOATIME		0x00000080
#घोषणा GFS2_DIF_SYNC			0x00000100
#घोषणा GFS2_DIF_SYSTEM			0x00000200 /* New in gfs2 */
#घोषणा GFS2_DIF_TOPसूची			0x00000400 /* New in gfs2 */
#घोषणा GFS2_DIF_TRUNC_IN_PROG		0x20000000 /* New in gfs2 */
#घोषणा GFS2_DIF_INHERIT_सूचीECTIO	0x40000000 /* only in gfs1 */
#घोषणा GFS2_DIF_INHERIT_JDATA		0x80000000

काष्ठा gfs2_dinode अणु
	काष्ठा gfs2_meta_header di_header;

	काष्ठा gfs2_inum di_num;

	__be32 di_mode;	/* mode of file */
	__be32 di_uid;	/* owner's user id */
	__be32 di_gid;	/* owner's group id */
	__be32 di_nlink;	/* number of links to this file */
	__be64 di_size;	/* number of bytes in file */
	__be64 di_blocks;	/* number of blocks in file */
	__be64 di_aसमय;	/* समय last accessed */
	__be64 di_mसमय;	/* समय last modअगरied */
	__be64 di_स_समय;	/* समय last changed */
	__be32 di_major;	/* device major number */
	__be32 di_minor;	/* device minor number */

	/* This section varies from gfs1. Padding added to align with
         * reमुख्यder of dinode
	 */
	__be64 di_goal_meta;	/* rgrp to alloc from next */
	__be64 di_goal_data;	/* data block goal */
	__be64 di_generation;	/* generation number क्रम NFS */

	__be32 di_flags;	/* GFS2_DIF_... */
	__be32 di_payload_क्रमmat;  /* GFS2_FORMAT_... */
	__u16 __pad1;	/* Was ditype in gfs1 */
	__be16 di_height;	/* height of metadata */
	__u32 __pad2;	/* Unused incarnation number from gfs1 */

	/* These only apply to directories  */
	__u16 __pad3;	/* Padding */
	__be16 di_depth;	/* Number of bits in the table */
	__be32 di_entries;	/* The number of entries in the directory */

	काष्ठा gfs2_inum __pad4; /* Unused even in current gfs1 */

	__be64 di_eattr;	/* extended attribute block number */
	__be32 di_aसमय_nsec;   /* nsec portion of aसमय */
	__be32 di_mसमय_nsec;   /* nsec portion of mसमय */
	__be32 di_स_समय_nsec;   /* nsec portion of स_समय */

	__u8 di_reserved[44];
पूर्ण;

/*
 * directory काष्ठाure - many of these per directory file
 */

#घोषणा GFS2_FNAMESIZE		255
#घोषणा GFS2_सूचीENT_SIZE(name_len) ((माप(काष्ठा gfs2_dirent) + (name_len) + 7) & ~7)
#घोषणा GFS2_MIN_सूचीENT_SIZE (GFS2_सूचीENT_SIZE(1))


काष्ठा gfs2_dirent अणु
	काष्ठा gfs2_inum de_inum;
	__be32 de_hash;
	__be16 de_rec_len;
	__be16 de_name_len;
	__be16 de_type;
	__be16 de_rahead;
	जोड़ अणु
		__u8 __pad[12];
		काष्ठा अणु
			__u32 de_cookie; /* ondisk value not used */
			__u8 pad3[8];
		पूर्ण;
	पूर्ण;
पूर्ण;

/*
 * Header of leaf directory nodes
 */

काष्ठा gfs2_leaf अणु
	काष्ठा gfs2_meta_header lf_header;

	__be16 lf_depth;		/* Depth of leaf */
	__be16 lf_entries;		/* Number of dirents in leaf */
	__be32 lf_dirent_क्रमmat;	/* Format of the dirents */
	__be64 lf_next;			/* Next leaf, अगर overflow */

	जोड़ अणु
		__u8 lf_reserved[64];
		काष्ठा अणु
			__be64 lf_inode;	/* Dir inode number */
			__be32 lf_dist;		/* Dist from inode on chain */
			__be32 lf_nsec;		/* Last ins/del usecs */
			__be64 lf_sec;		/* Last ins/del in secs */
			__u8 lf_reserved2[40];
		पूर्ण;
	पूर्ण;
पूर्ण;

/*
 * Extended attribute header क्रमmat
 *
 * This works in a similar way to dirents. There is a fixed size header
 * followed by a variable length section made up of the name and the
 * associated data. In the हाल of a "stuffed" entry, the value is
 * अंतरभूत directly after the name, the ea_num_ptrs entry will be
 * zero in that हाल. For non-"stuffed" entries, there will be
 * a set of poपूर्णांकers (aligned to 8 byte boundary) to the block(s)
 * containing the value.
 *
 * The blocks containing the values and the blocks containing the
 * extended attribute headers themselves all start with the common
 * metadata header. Each inode, अगर it has extended attributes, will
 * have either a single block containing the extended attribute headers
 * or a single indirect block poपूर्णांकing to blocks containing the
 * extended attribute headers.
 *
 * The maximum size of the data part of an extended attribute is 64k
 * so the number of blocks required depends upon block size. Since the
 * block size also determines the number of poपूर्णांकers in an indirect
 * block, its a fairly complicated calculation to work out the maximum
 * number of blocks that an inode may have relating to extended attributes.
 *
 */

#घोषणा GFS2_EA_MAX_NAME_LEN	255
#घोषणा GFS2_EA_MAX_DATA_LEN	65536

#घोषणा GFS2_EATYPE_UNUSED	0
#घोषणा GFS2_EATYPE_USR		1
#घोषणा GFS2_EATYPE_SYS		2
#घोषणा GFS2_EATYPE_SECURITY	3
#घोषणा GFS2_EATYPE_TRUSTED	4

#घोषणा GFS2_EATYPE_LAST	4
#घोषणा GFS2_EATYPE_VALID(x)	((x) <= GFS2_EATYPE_LAST)

#घोषणा GFS2_EAFLAG_LAST	0x01	/* last ea in block */

काष्ठा gfs2_ea_header अणु
	__be32 ea_rec_len;
	__be32 ea_data_len;
	__u8 ea_name_len;	/* no शून्य poपूर्णांकer after the string */
	__u8 ea_type;		/* GFS2_EATYPE_... */
	__u8 ea_flags;		/* GFS2_EAFLAG_... */
	__u8 ea_num_ptrs;
	__u32 __pad;
पूर्ण;

/*
 * Log header काष्ठाure
 */

#घोषणा GFS2_LOG_HEAD_UNMOUNT		0x00000001 /* log is clean */
#घोषणा GFS2_LOG_HEAD_FLUSH_NORMAL	0x00000002 /* normal log flush */
#घोषणा GFS2_LOG_HEAD_FLUSH_SYNC	0x00000004 /* Sync log flush */
#घोषणा GFS2_LOG_HEAD_FLUSH_SHUTDOWN	0x00000008 /* Shutकरोwn log flush */
#घोषणा GFS2_LOG_HEAD_FLUSH_FREEZE	0x00000010 /* Freeze flush */
#घोषणा GFS2_LOG_HEAD_RECOVERY		0x00000020 /* Journal recovery */
#घोषणा GFS2_LOG_HEAD_USERSPACE		0x80000000 /* Written by gfs2-utils */

/* Log flush callers */
#घोषणा GFS2_LFC_SHUTDOWN		0x00000100
#घोषणा GFS2_LFC_JDATA_WPAGES		0x00000200
#घोषणा GFS2_LFC_SET_FLAGS		0x00000400
#घोषणा GFS2_LFC_AIL_EMPTY_GL		0x00000800
#घोषणा GFS2_LFC_AIL_FLUSH		0x00001000
#घोषणा GFS2_LFC_RGRP_GO_SYNC		0x00002000
#घोषणा GFS2_LFC_INODE_GO_SYNC		0x00004000
#घोषणा GFS2_LFC_INODE_GO_INVAL		0x00008000
#घोषणा GFS2_LFC_FREEZE_GO_SYNC		0x00010000
#घोषणा GFS2_LFC_KILL_SB		0x00020000
#घोषणा GFS2_LFC_DO_SYNC		0x00040000
#घोषणा GFS2_LFC_INPLACE_RESERVE	0x00080000
#घोषणा GFS2_LFC_WRITE_INODE		0x00100000
#घोषणा GFS2_LFC_MAKE_FS_RO		0x00200000
#घोषणा GFS2_LFC_SYNC_FS		0x00400000
#घोषणा GFS2_LFC_EVICT_INODE		0x00800000
#घोषणा GFS2_LFC_TRANS_END		0x01000000
#घोषणा GFS2_LFC_LOGD_JFLUSH_REQD	0x02000000
#घोषणा GFS2_LFC_LOGD_AIL_FLUSH_REQD	0x04000000

#घोषणा LH_V1_SIZE (दुरत्वend(काष्ठा gfs2_log_header, lh_hash))

काष्ठा gfs2_log_header अणु
	काष्ठा gfs2_meta_header lh_header;

	__be64 lh_sequence;	/* Sequence number of this transaction */
	__be32 lh_flags;	/* GFS2_LOG_HEAD_... */
	__be32 lh_tail;		/* Block number of log tail */
	__be32 lh_blkno;
	__be32 lh_hash;		/* crc up to here with this field 0 */

	/* Version 2 additional fields start here */
	__be32 lh_crc;		/* crc32c from lh_nsec to end of block */
	__be32 lh_nsec;		/* Nanoseconds of बारtamp */
	__be64 lh_sec;		/* Seconds of बारtamp */
	__be64 lh_addr;		/* Block addr of this log header (असलolute) */
	__be64 lh_jinode;	/* Journal inode number */
	__be64 lh_statfs_addr;	/* Local statfs inode number */
	__be64 lh_quota_addr;	/* Local quota change inode number */

	/* Statfs local changes (i.e. dअगरf from global statfs) */
	__be64 lh_local_total;
	__be64 lh_local_मुक्त;
	__be64 lh_local_dinodes;
पूर्ण;

/*
 * Log type descriptor
 */

#घोषणा GFS2_LOG_DESC_METADATA	300
/* ld_data1 is the number of metadata blocks in the descriptor.
   ld_data2 is unused. */

#घोषणा GFS2_LOG_DESC_REVOKE	301
/* ld_data1 is the number of revoke blocks in the descriptor.
   ld_data2 is unused. */

#घोषणा GFS2_LOG_DESC_JDATA	302
/* ld_data1 is the number of data blocks in the descriptor.
   ld_data2 is unused. */

काष्ठा gfs2_log_descriptor अणु
	काष्ठा gfs2_meta_header ld_header;

	__be32 ld_type;		/* GFS2_LOG_DESC_... */
	__be32 ld_length;	/* Number of buffers in this chunk */
	__be32 ld_data1;	/* descriptor-specअगरic field */
	__be32 ld_data2;	/* descriptor-specअगरic field */

	__u8 ld_reserved[32];
पूर्ण;

/*
 * Inum Range
 * Describe a range of क्रमmal inode numbers allocated to
 * one machine to assign to inodes.
 */

#घोषणा GFS2_INUM_QUANTUM	1048576

काष्ठा gfs2_inum_range अणु
	__be64 ir_start;
	__be64 ir_length;
पूर्ण;

/*
 * Statfs change
 * Describes an change to the pool of मुक्त and allocated
 * blocks.
 */

काष्ठा gfs2_statfs_change अणु
	__be64 sc_total;
	__be64 sc_मुक्त;
	__be64 sc_dinodes;
पूर्ण;

/*
 * Quota change
 * Describes an allocation change क्रम a particular
 * user or group.
 */

#घोषणा GFS2_QCF_USER		0x00000001

काष्ठा gfs2_quota_change अणु
	__be64 qc_change;
	__be32 qc_flags;	/* GFS2_QCF_... */
	__be32 qc_id;
पूर्ण;

काष्ठा gfs2_quota_lvb अणु
        __be32 qb_magic;
        __u32 __pad;
        __be64 qb_limit;      /* Hard limit of # blocks to alloc */
        __be64 qb_warn;       /* Warn user when alloc is above this # */
        __be64 qb_value;       /* Current # blocks allocated */
पूर्ण;

#पूर्ण_अगर /* __GFS2_ONDISK_DOT_H__ */
