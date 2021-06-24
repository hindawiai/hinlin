<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__CRAMFS_H
#घोषणा _UAPI__CRAMFS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

#घोषणा CRAMFS_SIGNATURE	"Compressed ROMFS"

/*
 * Width of various bitfields in काष्ठा cramfs_inode.
 * Primarily used to generate warnings in mkcramfs.
 */
#घोषणा CRAMFS_MODE_WIDTH 16
#घोषणा CRAMFS_UID_WIDTH 16
#घोषणा CRAMFS_SIZE_WIDTH 24
#घोषणा CRAMFS_GID_WIDTH 8
#घोषणा CRAMFS_NAMELEN_WIDTH 6
#घोषणा CRAMFS_OFFSET_WIDTH 26

/*
 * Since inode.namelen is a अचिन्हित 6-bit number, the maximum cramfs
 * path length is 63 << 2 = 252.
 */
#घोषणा CRAMFS_MAXPATHLEN (((1 << CRAMFS_NAMELEN_WIDTH) - 1) << 2)

/*
 * Reasonably terse representation of the inode data.
 */
काष्ठा cramfs_inode अणु
	__u32 mode:CRAMFS_MODE_WIDTH, uid:CRAMFS_UID_WIDTH;
	/* SIZE क्रम device files is i_rdev */
	__u32 size:CRAMFS_SIZE_WIDTH, gid:CRAMFS_GID_WIDTH;
	/* NAMELEN is the length of the file name, भागided by 4 and
           rounded up.  (cramfs करोesn't support hard links.) */
	/* OFFSET: For symlinks and non-empty regular files, this
	   contains the offset (भागided by 4) of the file data in
	   compressed क्रमm (starting with an array of block poपूर्णांकers;
	   see README).  For non-empty directories it is the offset
	   (भागided by 4) of the inode of the first file in that
	   directory.  For anything अन्यथा, offset is zero. */
	__u32 namelen:CRAMFS_NAMELEN_WIDTH, offset:CRAMFS_OFFSET_WIDTH;
पूर्ण;

काष्ठा cramfs_info अणु
	__u32 crc;
	__u32 edition;
	__u32 blocks;
	__u32 files;
पूर्ण;

/*
 * Superblock inक्रमmation at the beginning of the FS.
 */
काष्ठा cramfs_super अणु
	__u32 magic;			/* 0x28cd3d45 - अक्रमom number */
	__u32 size;			/* length in bytes */
	__u32 flags;			/* feature flags */
	__u32 future;			/* reserved क्रम future use */
	__u8 signature[16];		/* "Compressed ROMFS" */
	काष्ठा cramfs_info fsid;	/* unique fileप्रणाली info */
	__u8 name[16];			/* user-defined name */
	काष्ठा cramfs_inode root;	/* root inode data */
पूर्ण;

/*
 * Feature flags
 *
 * 0x00000000 - 0x000000ff: features that work क्रम all past kernels
 * 0x00000100 - 0xffffffff: features that करोn't work क्रम past kernels
 */
#घोषणा CRAMFS_FLAG_FSID_VERSION_2	0x00000001	/* fsid version #2 */
#घोषणा CRAMFS_FLAG_SORTED_सूचीS		0x00000002	/* sorted dirs */
#घोषणा CRAMFS_FLAG_HOLES		0x00000100	/* support क्रम holes */
#घोषणा CRAMFS_FLAG_WRONG_SIGNATURE	0x00000200	/* reserved */
#घोषणा CRAMFS_FLAG_SHIFTED_ROOT_OFFSET	0x00000400	/* shअगरted root fs */
#घोषणा CRAMFS_FLAG_EXT_BLOCK_POINTERS	0x00000800	/* block poपूर्णांकer extensions */

/*
 * Valid values in super.flags.  Currently we refuse to mount
 * अगर (flags & ~CRAMFS_SUPPORTED_FLAGS).  Maybe that should be
 * changed to test super.future instead.
 */
#घोषणा CRAMFS_SUPPORTED_FLAGS	( 0x000000ff \
				| CRAMFS_FLAG_HOLES \
				| CRAMFS_FLAG_WRONG_SIGNATURE \
				| CRAMFS_FLAG_SHIFTED_ROOT_OFFSET \
				| CRAMFS_FLAG_EXT_BLOCK_POINTERS )

/*
 * Block poपूर्णांकer flags
 *
 * The maximum block offset that needs to be represented is roughly:
 *
 *   (1 << CRAMFS_OFFSET_WIDTH) * 4 +
 *   (1 << CRAMFS_SIZE_WIDTH) / PAGE_SIZE * (4 + PAGE_SIZE)
 *   = 0x11004000
 *
 * That leaves room क्रम 3 flag bits in the block poपूर्णांकer table.
 */
#घोषणा CRAMFS_BLK_FLAG_UNCOMPRESSED	(1 << 31)
#घोषणा CRAMFS_BLK_FLAG_सूचीECT_PTR	(1 << 30)

#घोषणा CRAMFS_BLK_FLAGS	( CRAMFS_BLK_FLAG_UNCOMPRESSED \
				| CRAMFS_BLK_FLAG_सूचीECT_PTR )

/*
 * Direct blocks are at least 4-byte aligned.
 * Poपूर्णांकers to direct blocks are shअगरted करोwn by 2 bits.
 */
#घोषणा CRAMFS_BLK_सूचीECT_PTR_SHIFT	2

#पूर्ण_अगर /* _UAPI__CRAMFS_H */
