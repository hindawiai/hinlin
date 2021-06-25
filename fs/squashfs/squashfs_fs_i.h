<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित SQUASHFS_FS_I
#घोषणा SQUASHFS_FS_I
/*
 * Squashfs
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * squashfs_fs_i.h
 */

काष्ठा squashfs_inode_info अणु
	u64		start;
	पूर्णांक		offset;
	u64		xattr;
	अचिन्हित पूर्णांक	xattr_size;
	पूर्णांक		xattr_count;
	जोड़ अणु
		काष्ठा अणु
			u64		fragment_block;
			पूर्णांक		fragment_size;
			पूर्णांक		fragment_offset;
			u64		block_list_start;
		पूर्ण;
		काष्ठा अणु
			u64		dir_idx_start;
			पूर्णांक		dir_idx_offset;
			पूर्णांक		dir_idx_cnt;
			पूर्णांक		parent;
		पूर्ण;
	पूर्ण;
	काष्ठा inode	vfs_inode;
पूर्ण;


अटल अंतरभूत काष्ठा squashfs_inode_info *squashfs_i(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा squashfs_inode_info, vfs_inode);
पूर्ण
#पूर्ण_अगर
