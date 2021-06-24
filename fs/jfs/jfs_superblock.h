<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2003
 */
#अगर_अघोषित	_H_JFS_SUPERBLOCK
#घोषणा _H_JFS_SUPERBLOCK

#समावेश <linux/uuid.h>

/*
 * make the magic number something a human could पढ़ो
 */
#घोषणा JFS_MAGIC	"JFS1"	/* Magic word */

#घोषणा JFS_VERSION	2	/* Version number: Version 2 */

#घोषणा LV_NAME_SIZE	11	/* MUST BE 11 क्रम OS/2 boot sector */

/*
 *	aggregate superblock
 *
 * The name superblock is too बंद to super_block, so the name has been
 * changed to jfs_superblock.  The utilities are still using the old name.
 */
काष्ठा jfs_superblock अणु
	अक्षर s_magic[4];	/* 4: magic number */
	__le32 s_version;	/* 4: version number */

	__le64 s_size;		/* 8: aggregate size in hardware/LVM blocks;
				 * VFS: number of blocks
				 */
	__le32 s_bsize;		/* 4: aggregate block size in bytes;
				 * VFS: fragment size
				 */
	__le16 s_l2bsize;	/* 2: log2 of s_bsize */
	__le16 s_l2bfactor;	/* 2: log2(s_bsize/hardware block size) */
	__le32 s_pbsize;	/* 4: hardware/LVM block size in bytes */
	__le16 s_l2pbsize;	/* 2: log2 of s_pbsize */
	__le16 pad;		/* 2: padding necessary क्रम alignment */

	__le32 s_agsize;	/* 4: allocation group size in aggr. blocks */

	__le32 s_flag;		/* 4: aggregate attributes:
				 *    see jfs_filsys.h
				 */
	__le32 s_state;		/* 4: mount/unmount/recovery state:
				 *    see jfs_filsys.h
				 */
	__le32 s_compress;		/* 4: > 0 अगर data compression */

	pxd_t s_ait2;		/* 8: first extent of secondary
				 *    aggregate inode table
				 */

	pxd_t s_aim2;		/* 8: first extent of secondary
				 *    aggregate inode map
				 */
	__le32 s_logdev;		/* 4: device address of log */
	__le32 s_logserial;	/* 4: log serial number at aggregate mount */
	pxd_t s_logpxd;		/* 8: अंतरभूत log extent */

	pxd_t s_fsckpxd;	/* 8: अंतरभूत fsck work space extent */

	काष्ठा बारtruc_t s_समय;	/* 8: समय last updated */

	__le32 s_fsckloglen;	/* 4: Number of fileप्रणाली blocks reserved क्रम
				 *    the fsck service log.
				 *    N.B. These blocks are भागided among the
				 *         versions kept.  This is not a per
				 *         version size.
				 *    N.B. These blocks are included in the
				 *         length field of s_fsckpxd.
				 */
	s8 s_fscklog;		/* 1: which fsck service log is most recent
				 *    0 => no service log data yet
				 *    1 => the first one
				 *    2 => the 2nd one
				 */
	अक्षर s_fpack[11];	/* 11: file प्रणाली volume name
				 *     N.B. This must be 11 bytes to
				 *          conक्रमm with the OS/2 BootSector
				 *          requirements
				 *          Only used when s_version is 1
				 */

	/* extendfs() parameter under s_state & FM_EXTENDFS */
	__le64 s_xsize;		/* 8: extendfs s_size */
	pxd_t s_xfsckpxd;	/* 8: extendfs fsckpxd */
	pxd_t s_xlogpxd;	/* 8: extendfs logpxd */
	uuid_t s_uuid;		/* 16: 128-bit uuid क्रम volume */
	अक्षर s_label[16];	/* 16: volume label */
	uuid_t s_loguuid;	/* 16: 128-bit uuid क्रम log device */

पूर्ण;

बाह्य पूर्णांक पढ़ोSuper(काष्ठा super_block *, काष्ठा buffer_head **);
बाह्य पूर्णांक updateSuper(काष्ठा super_block *, uपूर्णांक);
__म_लिखो(2, 3)
बाह्य व्योम jfs_error(काष्ठा super_block *, स्थिर अक्षर *, ...);
बाह्य पूर्णांक jfs_mount(काष्ठा super_block *);
बाह्य पूर्णांक jfs_mount_rw(काष्ठा super_block *, पूर्णांक);
बाह्य पूर्णांक jfs_umount(काष्ठा super_block *);
बाह्य पूर्णांक jfs_umount_rw(काष्ठा super_block *);
बाह्य पूर्णांक jfs_extendfs(काष्ठा super_block *, s64, पूर्णांक);

बाह्य काष्ठा task_काष्ठा *jfsIOthपढ़ो;
बाह्य काष्ठा task_काष्ठा *jfsSyncThपढ़ो;

#पूर्ण_अगर /*_H_JFS_SUPERBLOCK */
