<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Name                 : qnx6_fs.h
 *  Author               : Kai Bankett
 *  Function             : qnx6 global fileप्रणाली definitions
 *  History              : 17-01-2012 created
 */
#अगर_अघोषित _LINUX_QNX6_FS_H
#घोषणा _LINUX_QNX6_FS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

#घोषणा QNX6_ROOT_INO 1

/* क्रम di_status */
#घोषणा QNX6_खाता_सूचीECTORY	0x01
#घोषणा QNX6_खाता_DELETED	0x02
#घोषणा QNX6_खाता_NORMAL	0x03

#घोषणा QNX6_SUPERBLOCK_SIZE	0x200	/* superblock always is 512 bytes */
#घोषणा QNX6_SUPERBLOCK_AREA	0x1000	/* area reserved क्रम superblock */
#घोषणा	QNX6_BOOTBLOCK_SIZE	0x2000	/* heading bootblock area */
#घोषणा QNX6_सूची_ENTRY_SIZE	0x20	/* dir entry size of 32 bytes */
#घोषणा QNX6_INODE_SIZE		0x80	/* each inode is 128 bytes */
#घोषणा QNX6_INODE_SIZE_BITS	7	/* inode entry size shअगरt */

#घोषणा QNX6_NO_सूचीECT_POINTERS	16	/* 16 blockptrs in sbl/inode */
#घोषणा QNX6_PTR_MAX_LEVELS	5	/* maximum indirect levels */

/* क्रम filenames */
#घोषणा QNX6_SHORT_NAME_MAX	27
#घोषणा QNX6_LONG_NAME_MAX	510

/* list of mount options */
#घोषणा QNX6_MOUNT_MMI_FS	0x010000 /* mount as Audi MMI 3G fs */

/*
 * This is the original qnx6 inode layout on disk.
 * Each inode is 128 byte दीर्घ.
 */
काष्ठा qnx6_inode_entry अणु
	__fs64		di_size;
	__fs32		di_uid;
	__fs32		di_gid;
	__fs32		di_fसमय;
	__fs32		di_mसमय;
	__fs32		di_aसमय;
	__fs32		di_स_समय;
	__fs16		di_mode;
	__fs16		di_ext_mode;
	__fs32		di_block_ptr[QNX6_NO_सूचीECT_POINTERS];
	__u8		di_filelevels;
	__u8		di_status;
	__u8		di_unknown2[2];
	__fs32		di_zero2[6];
पूर्ण;

/*
 * Each directory entry is maximum 32 bytes दीर्घ.
 * If more अक्षरacters or special अक्षरacters required it is stored
 * in the दीर्घfilenames काष्ठाure.
 */
काष्ठा qnx6_dir_entry अणु
	__fs32		de_inode;
	__u8		de_size;
	अक्षर		de_fname[QNX6_SHORT_NAME_MAX];
पूर्ण;

/*
 * Longfilename direntries have a dअगरferent काष्ठाure
 */
काष्ठा qnx6_दीर्घ_dir_entry अणु
	__fs32		de_inode;
	__u8		de_size;
	__u8		de_unknown[3];
	__fs32		de_दीर्घ_inode;
	__fs32		de_checksum;
पूर्ण;

काष्ठा qnx6_दीर्घ_filename अणु
	__fs16		lf_size;
	__u8		lf_fname[QNX6_LONG_NAME_MAX];
पूर्ण;

काष्ठा qnx6_root_node अणु
	__fs64		size;
	__fs32		ptr[QNX6_NO_सूचीECT_POINTERS];
	__u8		levels;
	__u8		mode;
	__u8		spare[6];
पूर्ण;

काष्ठा qnx6_super_block अणु
	__fs32		sb_magic;
	__fs32		sb_checksum;
	__fs64		sb_serial;
	__fs32		sb_स_समय;	/* समय the fs was created */
	__fs32		sb_aसमय;	/* last access समय */
	__fs32		sb_flags;
	__fs16		sb_version1;	/* fileप्रणाली version inक्रमmation */
	__fs16		sb_version2;	/* fileप्रणाली version inक्रमmation */
	__u8		sb_volumeid[16];
	__fs32		sb_blocksize;
	__fs32		sb_num_inodes;
	__fs32		sb_मुक्त_inodes;
	__fs32		sb_num_blocks;
	__fs32		sb_मुक्त_blocks;
	__fs32		sb_allocgroup;
	काष्ठा qnx6_root_node Inode;
	काष्ठा qnx6_root_node Biपंचांगap;
	काष्ठा qnx6_root_node Longfile;
	काष्ठा qnx6_root_node Unknown;
पूर्ण;

/* Audi MMI 3G superblock layout is dअगरferent to plain qnx6 */
काष्ठा qnx6_mmi_super_block अणु
	__fs32		sb_magic;
	__fs32		sb_checksum;
	__fs64		sb_serial;
	__u8		sb_spare0[12];
	__u8		sb_id[12];
	__fs32		sb_blocksize;
	__fs32		sb_num_inodes;
	__fs32		sb_मुक्त_inodes;
	__fs32		sb_num_blocks;
	__fs32		sb_मुक्त_blocks;
	__u8		sb_spare1[4];
	काष्ठा qnx6_root_node Inode;
	काष्ठा qnx6_root_node Biपंचांगap;
	काष्ठा qnx6_root_node Longfile;
	काष्ठा qnx6_root_node Unknown;
पूर्ण;

#पूर्ण_अगर
