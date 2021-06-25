<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *	include/linux/bfs_fs.h - BFS data काष्ठाures on disk.
 *	Copyright (C) 1999-2018 Tigran Aivazian <aivazian.tigran@gmail.com>
 */

#अगर_अघोषित _LINUX_BFS_FS_H
#घोषणा _LINUX_BFS_FS_H

#समावेश <linux/types.h>

#घोषणा BFS_BSIZE_BITS		9
#घोषणा BFS_BSIZE		(1<<BFS_BSIZE_BITS)

#घोषणा BFS_MAGIC		0x1BADFACE
#घोषणा BFS_ROOT_INO		2
#घोषणा BFS_INODES_PER_BLOCK	8

/* SVR4 vnode type values (bfs_inode->i_vtype) */
#घोषणा BFS_Vसूची 2L
#घोषणा BFS_VREG 1L

/* BFS inode layout on disk */
काष्ठा bfs_inode अणु
	__le16 i_ino;
	__u16 i_unused;
	__le32 i_sblock;
	__le32 i_eblock;
	__le32 i_eoffset;
	__le32 i_vtype;
	__le32 i_mode;
	__le32 i_uid;
	__le32 i_gid;
	__le32 i_nlink;
	__le32 i_aसमय;
	__le32 i_mसमय;
	__le32 i_स_समय;
	__u32 i_padding[4];
पूर्ण;

#घोषणा BFS_NAMELEN		14	
#घोषणा BFS_सूचीENT_SIZE		16
#घोषणा BFS_सूचीS_PER_BLOCK	32

काष्ठा bfs_dirent अणु
	__le16 ino;
	अक्षर name[BFS_NAMELEN];
पूर्ण;

/* BFS superblock layout on disk */
काष्ठा bfs_super_block अणु
	__le32 s_magic;
	__le32 s_start;
	__le32 s_end;
	__le32 s_from;
	__le32 s_to;
	__s32 s_bfrom;
	__s32 s_bto;
	अक्षर  s_fsname[6];
	अक्षर  s_volume[6];
	__u32 s_padding[118];
पूर्ण;


#घोषणा BFS_OFF2INO(offset) \
        ((((offset) - BFS_BSIZE) / माप(काष्ठा bfs_inode)) + BFS_ROOT_INO)

#घोषणा BFS_INO2OFF(ino) \
	((__u32)(((ino) - BFS_ROOT_INO) * माप(काष्ठा bfs_inode)) + BFS_BSIZE)
#घोषणा BFS_NZखाताSIZE(ip) \
        ((le32_to_cpu((ip)->i_eoffset) + 1) -  le32_to_cpu((ip)->i_sblock) * BFS_BSIZE)

#घोषणा BFS_खाताSIZE(ip) \
        ((ip)->i_sblock == 0 ? 0 : BFS_NZखाताSIZE(ip))

#घोषणा BFS_खाताBLOCKS(ip) \
        ((ip)->i_sblock == 0 ? 0 : (le32_to_cpu((ip)->i_eblock) + 1) -  le32_to_cpu((ip)->i_sblock))
#घोषणा BFS_UNCLEAN(bfs_sb, sb)	\
	((le32_to_cpu(bfs_sb->s_from) != -1) && (le32_to_cpu(bfs_sb->s_to) != -1) && !(sb->s_flags & SB_RDONLY))


#पूर्ण_अगर	/* _LINUX_BFS_FS_H */
