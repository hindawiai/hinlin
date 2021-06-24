<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  Name                         : qnx4_fs.h
 *  Author                       : Riअक्षरd Frowijn
 *  Function                     : qnx4 global fileप्रणाली definitions
 *  History                      : 23-03-1998 created
 */
#अगर_अघोषित _LINUX_QNX4_FS_H
#घोषणा _LINUX_QNX4_FS_H

#समावेश <linux/types.h>
#समावेश <linux/qnxtypes.h>
#समावेश <linux/magic.h>

#घोषणा QNX4_ROOT_INO 1

#घोषणा QNX4_MAX_XTNTS_PER_XBLK	60
/* क्रम di_status */
#घोषणा QNX4_खाता_USED          0x01
#घोषणा QNX4_खाता_MODIFIED      0x02
#घोषणा QNX4_खाता_BUSY          0x04
#घोषणा QNX4_खाता_LINK          0x08
#घोषणा QNX4_खाता_INODE         0x10
#घोषणा QNX4_खाता_FSYSCLEAN     0x20

#घोषणा QNX4_I_MAP_SLOTS	8
#घोषणा QNX4_Z_MAP_SLOTS	64
#घोषणा QNX4_VALID_FS		0x0001	/* Clean fs. */
#घोषणा QNX4_ERROR_FS		0x0002	/* fs has errors. */
#घोषणा QNX4_BLOCK_SIZE         0x200	/* blocksize of 512 bytes */
#घोषणा QNX4_BLOCK_SIZE_BITS    9	/* blocksize shअगरt */
#घोषणा QNX4_सूची_ENTRY_SIZE     0x040	/* dir entry size of 64 bytes */
#घोषणा QNX4_सूची_ENTRY_SIZE_BITS 6	/* dir entry size shअगरt */
#घोषणा QNX4_XBLK_ENTRY_SIZE    0x200	/* xblk entry size */
#घोषणा QNX4_INODES_PER_BLOCK   0x08	/* 512 / 64 */

/* क्रम filenames */
#घोषणा QNX4_SHORT_NAME_MAX	16
#घोषणा QNX4_NAME_MAX		48

/*
 * This is the original qnx4 inode layout on disk.
 */
काष्ठा qnx4_inode_entry अणु
	अक्षर		di_fname[QNX4_SHORT_NAME_MAX];
	qnx4_off_t	di_size;
	qnx4_xtnt_t	di_first_xtnt;
	__le32		di_xblk;
	__le32		di_fसमय;
	__le32		di_mसमय;
	__le32		di_aसमय;
	__le32		di_स_समय;
	qnx4_nxtnt_t	di_num_xtnts;
	qnx4_mode_t	di_mode;
	qnx4_muid_t	di_uid;
	qnx4_mgid_t	di_gid;
	qnx4_nlink_t	di_nlink;
	__u8		di_zero[4];
	qnx4_ftype_t	di_type;
	__u8		di_status;
पूर्ण;

काष्ठा qnx4_link_info अणु
	अक्षर		dl_fname[QNX4_NAME_MAX];
	__le32		dl_inode_blk;
	__u8		dl_inode_ndx;
	__u8		dl_spare[10];
	__u8		dl_status;
पूर्ण;

काष्ठा qnx4_xblk अणु
	__le32		xblk_next_xblk;
	__le32		xblk_prev_xblk;
	__u8		xblk_num_xtnts;
	__u8		xblk_spare[3];
	__le32		xblk_num_blocks;
	qnx4_xtnt_t	xblk_xtnts[QNX4_MAX_XTNTS_PER_XBLK];
	अक्षर		xblk_signature[8];
	qnx4_xtnt_t	xblk_first_xtnt;
पूर्ण;

काष्ठा qnx4_super_block अणु
	काष्ठा qnx4_inode_entry RootDir;
	काष्ठा qnx4_inode_entry Inode;
	काष्ठा qnx4_inode_entry Boot;
	काष्ठा qnx4_inode_entry AltBoot;
पूर्ण;

#पूर्ण_अगर
