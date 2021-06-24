<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_MINIX_FS_H
#घोषणा _LINUX_MINIX_FS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

/*
 * The minix fileप्रणाली स्थिरants/काष्ठाures
 */

/*
 * Thanks to Kees J Bot क्रम sending me the definitions of the new
 * minix fileप्रणाली (aka V2) with bigger inodes and 32-bit block
 * poपूर्णांकers.
 */

#घोषणा MINIX_ROOT_INO 1

/* Not the same as the bogus LINK_MAX in <linux/सीमा.स>. Oh well. */
#घोषणा MINIX_LINK_MAX	250
#घोषणा MINIX2_LINK_MAX	65530

#घोषणा MINIX_I_MAP_SLOTS	8
#घोषणा MINIX_Z_MAP_SLOTS	64
#घोषणा MINIX_VALID_FS		0x0001		/* Clean fs. */
#घोषणा MINIX_ERROR_FS		0x0002		/* fs has errors. */

#घोषणा MINIX_INODES_PER_BLOCK ((BLOCK_SIZE)/(माप (काष्ठा minix_inode)))

/*
 * This is the original minix inode layout on disk.
 * Note the 8-bit gid and aसमय and स_समय.
 */
काष्ठा minix_inode अणु
	__u16 i_mode;
	__u16 i_uid;
	__u32 i_size;
	__u32 i_समय;
	__u8  i_gid;
	__u8  i_nlinks;
	__u16 i_zone[9];
पूर्ण;

/*
 * The new minix inode has all the समय entries, as well as
 * दीर्घ block numbers and a third indirect block (7+1+1+1
 * instead of 7+1+1). Also, some previously 8-bit values are
 * now 16-bit. The inode is now 64 bytes instead of 32.
 */
काष्ठा minix2_inode अणु
	__u16 i_mode;
	__u16 i_nlinks;
	__u16 i_uid;
	__u16 i_gid;
	__u32 i_size;
	__u32 i_aसमय;
	__u32 i_mसमय;
	__u32 i_स_समय;
	__u32 i_zone[10];
पूर्ण;

/*
 * minix super-block data on disk
 */
काष्ठा minix_super_block अणु
	__u16 s_ninodes;
	__u16 s_nzones;
	__u16 s_imap_blocks;
	__u16 s_zmap_blocks;
	__u16 s_firstdatazone;
	__u16 s_log_zone_size;
	__u32 s_max_size;
	__u16 s_magic;
	__u16 s_state;
	__u32 s_zones;
पूर्ण;

/*
 * V3 minix super-block data on disk
 */
काष्ठा minix3_super_block अणु
	__u32 s_ninodes;
	__u16 s_pad0;
	__u16 s_imap_blocks;
	__u16 s_zmap_blocks;
	__u16 s_firstdatazone;
	__u16 s_log_zone_size;
	__u16 s_pad1;
	__u32 s_max_size;
	__u32 s_zones;
	__u16 s_magic;
	__u16 s_pad2;
	__u16 s_blocksize;
	__u8  s_disk_version;
पूर्ण;

काष्ठा minix_dir_entry अणु
	__u16 inode;
	अक्षर name[0];
पूर्ण;

काष्ठा minix3_dir_entry अणु
	__u32 inode;
	अक्षर name[0];
पूर्ण;
#पूर्ण_अगर
