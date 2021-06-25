<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Definitions of काष्ठाures क्रम vfsv0 quota क्रमmat
 */

#अगर_अघोषित _LINUX_QUOTAIO_V2_H
#घोषणा _LINUX_QUOTAIO_V2_H

#समावेश <linux/types.h>
#समावेश <linux/quota.h>

/*
 * Definitions of magics and versions of current quota files
 */
#घोषणा V2_INITQMAGICS अणु\
	0xd9c01f11,	/* USRQUOTA */\
	0xd9c01927,	/* GRPQUOTA */\
	0xd9c03f14,	/* PRJQUOTA */\
पूर्ण

#घोषणा V2_INITQVERSIONS अणु\
	1,		/* USRQUOTA */\
	1,		/* GRPQUOTA */\
	1,		/* PRJQUOTA */\
पूर्ण

/* First generic header */
काष्ठा v2_disk_dqheader अणु
	__le32 dqh_magic;	/* Magic number identअगरying file */
	__le32 dqh_version;	/* File version */
पूर्ण;

/*
 * The following काष्ठाure defines the क्रमmat of the disk quota file
 * (as it appears on disk) - the file is a radix tree whose leaves poपूर्णांक
 * to blocks of these काष्ठाures.
 */
काष्ठा v2r0_disk_dqblk अणु
	__le32 dqb_id;		/* id this quota applies to */
	__le32 dqb_ihardlimit;	/* असलolute limit on allocated inodes */
	__le32 dqb_isoftlimit;	/* preferred inode limit */
	__le32 dqb_curinodes;	/* current # allocated inodes */
	__le32 dqb_bhardlimit;	/* असलolute limit on disk space (in QUOTABLOCK_SIZE) */
	__le32 dqb_bsoftlimit;	/* preferred limit on disk space (in QUOTABLOCK_SIZE) */
	__le64 dqb_curspace;	/* current space occupied (in bytes) */
	__le64 dqb_bसमय;	/* समय limit क्रम excessive disk use */
	__le64 dqb_iसमय;	/* समय limit क्रम excessive inode use */
पूर्ण;

काष्ठा v2r1_disk_dqblk अणु
	__le32 dqb_id;		/* id this quota applies to */
	__le32 dqb_pad;
	__le64 dqb_ihardlimit;	/* असलolute limit on allocated inodes */
	__le64 dqb_isoftlimit;	/* preferred inode limit */
	__le64 dqb_curinodes;	/* current # allocated inodes */
	__le64 dqb_bhardlimit;	/* असलolute limit on disk space (in QUOTABLOCK_SIZE) */
	__le64 dqb_bsoftlimit;	/* preferred limit on disk space (in QUOTABLOCK_SIZE) */
	__le64 dqb_curspace;	/* current space occupied (in bytes) */
	__le64 dqb_bसमय;	/* समय limit क्रम excessive disk use */
	__le64 dqb_iसमय;	/* समय limit क्रम excessive inode use */
पूर्ण;

/* Header with type and version specअगरic inक्रमmation */
काष्ठा v2_disk_dqinfo अणु
	__le32 dqi_bgrace;	/* Time beक्रमe block soft limit becomes hard limit */
	__le32 dqi_igrace;	/* Time beक्रमe inode soft limit becomes hard limit */
	__le32 dqi_flags;	/* Flags क्रम quotafile (DQF_*) */
	__le32 dqi_blocks;	/* Number of blocks in file */
	__le32 dqi_मुक्त_blk;	/* Number of first मुक्त block in the list */
	__le32 dqi_मुक्त_entry;	/* Number of block with at least one मुक्त entry */
पूर्ण;

#घोषणा V2_DQINFOOFF	माप(काष्ठा v2_disk_dqheader)	/* Offset of info header in file */
#घोषणा V2_DQBLKSIZE_BITS 10				/* Size of leaf block in tree */

#पूर्ण_अगर /* _LINUX_QUOTAIO_V2_H */
