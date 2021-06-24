<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * efs_fs_sb.h
 *
 * Copyright (c) 1999 Al Smith
 *
 * Portions derived from IRIX header files (c) 1988 Silicon Graphics
 */

#अगर_अघोषित __EFS_FS_SB_H__
#घोषणा __EFS_FS_SB_H__

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

/* EFS superblock magic numbers */
#घोषणा EFS_MAGIC	0x072959
#घोषणा EFS_NEWMAGIC	0x07295a

#घोषणा IS_EFS_MAGIC(x)	((x == EFS_MAGIC) || (x == EFS_NEWMAGIC))

#घोषणा EFS_SUPER		1
#घोषणा EFS_ROOTINODE		2

/* efs superblock on disk */
काष्ठा efs_super अणु
	__be32		fs_size;        /* size of fileप्रणाली, in sectors */
	__be32		fs_firstcg;     /* bb offset to first cg */
	__be32		fs_cgfsize;     /* size of cylinder group in bb's */
	__be16		fs_cgisize;     /* bb's of inodes per cylinder group */
	__be16		fs_sectors;     /* sectors per track */
	__be16		fs_heads;       /* heads per cylinder */
	__be16		fs_ncg;         /* # of cylinder groups in fileप्रणाली */
	__be16		fs_dirty;       /* fs needs to be fsck'd */
	__be32		fs_समय;        /* last super-block update */
	__be32		fs_magic;       /* magic number */
	अक्षर		fs_fname[6];    /* file प्रणाली name */
	अक्षर		fs_fpack[6];    /* file प्रणाली pack name */
	__be32		fs_bmsize;      /* size of biपंचांगap in bytes */
	__be32		fs_tमुक्त;       /* total मुक्त data blocks */
	__be32		fs_tinode;      /* total मुक्त inodes */
	__be32		fs_bmblock;     /* biपंचांगap location. */
	__be32		fs_replsb;      /* Location of replicated superblock. */
	__be32		fs_lastialloc;  /* last allocated inode */
	अक्षर		fs_spare[20];   /* space क्रम expansion - MUST BE ZERO */
	__be32		fs_checksum;    /* checksum of volume portion of fs */
पूर्ण;

/* efs superblock inक्रमmation in memory */
काष्ठा efs_sb_info अणु
	__u32	fs_magic;	/* superblock magic number */
	__u32	fs_start;	/* first block of fileप्रणाली */
	__u32	first_block;	/* first data block in fileप्रणाली */
	__u32	total_blocks;	/* total number of blocks in fileप्रणाली */
	__u32	group_size;	/* # of blocks a group consists of */ 
	__u32	data_मुक्त;	/* # of मुक्त data blocks */
	__u32	inode_मुक्त;	/* # of मुक्त inodes */
	__u16	inode_blocks;	/* # of blocks used क्रम inodes in every grp */
	__u16	total_groups;	/* # of groups */
पूर्ण;

#पूर्ण_अगर /* __EFS_FS_SB_H__ */

