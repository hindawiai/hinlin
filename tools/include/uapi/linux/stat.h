<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_STAT_H
#घोषणा _UAPI_LINUX_STAT_H

#समावेश <linux/types.h>

#अगर defined(__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ < 2)

#घोषणा S_IFMT  00170000
#घोषणा S_IFSOCK 0140000
#घोषणा S_IFLNK	 0120000
#घोषणा S_IFREG  0100000
#घोषणा S_IFBLK  0060000
#घोषणा S_IFसूची  0040000
#घोषणा S_IFCHR  0020000
#घोषणा S_IFIFO  0010000
#घोषणा S_ISUID  0004000
#घोषणा S_ISGID  0002000
#घोषणा S_ISVTX  0001000

#घोषणा S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)
#घोषणा S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
#घोषणा S_ISसूची(m)	(((m) & S_IFMT) == S_IFसूची)
#घोषणा S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#घोषणा S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
#घोषणा S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
#घोषणा S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)

#घोषणा S_IRWXU 00700
#घोषणा S_IRUSR 00400
#घोषणा S_IWUSR 00200
#घोषणा S_IXUSR 00100

#घोषणा S_IRWXG 00070
#घोषणा S_IRGRP 00040
#घोषणा S_IWGRP 00020
#घोषणा S_IXGRP 00010

#घोषणा S_IRWXO 00007
#घोषणा S_IROTH 00004
#घोषणा S_IWOTH 00002
#घोषणा S_IXOTH 00001

#पूर्ण_अगर

/*
 * Timestamp काष्ठाure क्रम the बारtamps in काष्ठा statx.
 *
 * tv_sec holds the number of seconds beक्रमe (negative) or after (positive)
 * 00:00:00 1st January 1970 UTC.
 *
 * tv_nsec holds a number of nanoseconds (0..999,999,999) after the tv_sec समय.
 *
 * __reserved is held in हाल we need a yet finer resolution.
 */
काष्ठा statx_बारtamp अणु
	__s64	tv_sec;
	__u32	tv_nsec;
	__s32	__reserved;
पूर्ण;

/*
 * Structures क्रम the extended file attribute retrieval प्रणाली call
 * (statx()).
 *
 * The caller passes a mask of what they're specअगरically पूर्णांकerested in as a
 * parameter to statx().  What statx() actually got will be indicated in
 * st_mask upon वापस.
 *
 * For each bit in the mask argument:
 *
 * - अगर the datum is not supported:
 *
 *   - the bit will be cleared, and
 *
 *   - the datum will be set to an appropriate fabricated value अगर one is
 *     available (eg. CIFS can take a शेष uid and gid), otherwise
 *
 *   - the field will be cleared;
 *
 * - otherwise, अगर explicitly requested:
 *
 *   - the datum will be synchronised to the server अगर AT_STATX_FORCE_SYNC is
 *     set or अगर the datum is considered out of date, and
 *
 *   - the field will be filled in and the bit will be set;
 *
 * - otherwise, अगर not requested, but available in approximate क्रमm without any
 *   efक्रमt, it will be filled in anyway, and the bit will be set upon वापस
 *   (it might not be up to date, however, and no attempt will be made to
 *   synchronise the पूर्णांकernal state first);
 *
 * - otherwise the field and the bit will be cleared beक्रमe वापसing.
 *
 * Items in STATX_BASIC_STATS may be marked unavailable on वापस, but they
 * will have values installed क्रम compatibility purposes so that stat() and
 * co. can be emulated in userspace.
 */
काष्ठा statx अणु
	/* 0x00 */
	__u32	stx_mask;	/* What results were written [uncond] */
	__u32	stx_blksize;	/* Preferred general I/O size [uncond] */
	__u64	stx_attributes;	/* Flags conveying inक्रमmation about the file [uncond] */
	/* 0x10 */
	__u32	stx_nlink;	/* Number of hard links */
	__u32	stx_uid;	/* User ID of owner */
	__u32	stx_gid;	/* Group ID of owner */
	__u16	stx_mode;	/* File mode */
	__u16	__spare0[1];
	/* 0x20 */
	__u64	stx_ino;	/* Inode number */
	__u64	stx_size;	/* File size */
	__u64	stx_blocks;	/* Number of 512-byte blocks allocated */
	__u64	stx_attributes_mask; /* Mask to show what's supported in stx_attributes */
	/* 0x40 */
	काष्ठा statx_बारtamp	stx_aसमय;	/* Last access समय */
	काष्ठा statx_बारtamp	stx_bसमय;	/* File creation समय */
	काष्ठा statx_बारtamp	stx_स_समय;	/* Last attribute change समय */
	काष्ठा statx_बारtamp	stx_mसमय;	/* Last data modअगरication समय */
	/* 0x80 */
	__u32	stx_rdev_major;	/* Device ID of special file [अगर bdev/cdev] */
	__u32	stx_rdev_minor;
	__u32	stx_dev_major;	/* ID of device containing file [uncond] */
	__u32	stx_dev_minor;
	/* 0x90 */
	__u64	stx_mnt_id;
	__u64	__spare2;
	/* 0xa0 */
	__u64	__spare3[12];	/* Spare space क्रम future expansion */
	/* 0x100 */
पूर्ण;

/*
 * Flags to be stx_mask
 *
 * Query request/result mask क्रम statx() and काष्ठा statx::stx_mask.
 *
 * These bits should be set in the mask argument of statx() to request
 * particular items when calling statx().
 */
#घोषणा STATX_TYPE		0x00000001U	/* Want/got stx_mode & S_IFMT */
#घोषणा STATX_MODE		0x00000002U	/* Want/got stx_mode & ~S_IFMT */
#घोषणा STATX_NLINK		0x00000004U	/* Want/got stx_nlink */
#घोषणा STATX_UID		0x00000008U	/* Want/got stx_uid */
#घोषणा STATX_GID		0x00000010U	/* Want/got stx_gid */
#घोषणा STATX_ATIME		0x00000020U	/* Want/got stx_aसमय */
#घोषणा STATX_MTIME		0x00000040U	/* Want/got stx_mसमय */
#घोषणा STATX_CTIME		0x00000080U	/* Want/got stx_स_समय */
#घोषणा STATX_INO		0x00000100U	/* Want/got stx_ino */
#घोषणा STATX_SIZE		0x00000200U	/* Want/got stx_size */
#घोषणा STATX_BLOCKS		0x00000400U	/* Want/got stx_blocks */
#घोषणा STATX_BASIC_STATS	0x000007ffU	/* The stuff in the normal stat काष्ठा */
#घोषणा STATX_BTIME		0x00000800U	/* Want/got stx_bसमय */
#घोषणा STATX_MNT_ID		0x00001000U	/* Got stx_mnt_id */

#घोषणा STATX__RESERVED		0x80000000U	/* Reserved क्रम future काष्ठा statx expansion */

#अगर_अघोषित __KERNEL__
/*
 * This is deprecated, and shall reमुख्य the same value in the future.  To aव्योम
 * confusion please use the equivalent (STATX_BASIC_STATS | STATX_BTIME)
 * instead.
 */
#घोषणा STATX_ALL		0x00000fffU
#पूर्ण_अगर

/*
 * Attributes to be found in stx_attributes and masked in stx_attributes_mask.
 *
 * These give inक्रमmation about the features or the state of a file that might
 * be of use to ordinary userspace programs such as GUIs or ls rather than
 * specialised tools.
 *
 * Note that the flags marked [I] correspond to the FS_IOC_SETFLAGS flags
 * semantically.  Where possible, the numerical value is picked to correspond
 * also.  Note that the DAX attribute indicates that the file is in the CPU
 * direct access state.  It करोes not correspond to the per-inode flag that
 * some fileप्रणालीs support.
 *
 */
#घोषणा STATX_ATTR_COMPRESSED		0x00000004 /* [I] File is compressed by the fs */
#घोषणा STATX_ATTR_IMMUTABLE		0x00000010 /* [I] File is marked immutable */
#घोषणा STATX_ATTR_APPEND		0x00000020 /* [I] File is append-only */
#घोषणा STATX_ATTR_NODUMP		0x00000040 /* [I] File is not to be dumped */
#घोषणा STATX_ATTR_ENCRYPTED		0x00000800 /* [I] File requires key to decrypt in fs */
#घोषणा STATX_ATTR_AUTOMOUNT		0x00001000 /* Dir: Automount trigger */
#घोषणा STATX_ATTR_MOUNT_ROOT		0x00002000 /* Root of a mount */
#घोषणा STATX_ATTR_VERITY		0x00100000 /* [I] Verity रक्षित file */
#घोषणा STATX_ATTR_DAX			0x00200000 /* File is currently in DAX state */


#पूर्ण_अगर /* _UAPI_LINUX_STAT_H */
