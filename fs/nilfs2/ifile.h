<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * अगरile.h - NILFS inode file
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Amagai Yoshiji.
 * Revised by Ryusuke Konishi.
 *
 */

#अगर_अघोषित _NILFS_Iखाता_H
#घोषणा _NILFS_Iखाता_H

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश "mdt.h"
#समावेश "alloc.h"


अटल अंतरभूत काष्ठा nilfs_inode *
nilfs_अगरile_map_inode(काष्ठा inode *अगरile, ino_t ino, काष्ठा buffer_head *ibh)
अणु
	व्योम *kaddr = kmap(ibh->b_page);

	वापस nilfs_palloc_block_get_entry(अगरile, ino, ibh, kaddr);
पूर्ण

अटल अंतरभूत व्योम nilfs_अगरile_unmap_inode(काष्ठा inode *अगरile, ino_t ino,
					   काष्ठा buffer_head *ibh)
अणु
	kunmap(ibh->b_page);
पूर्ण

पूर्णांक nilfs_अगरile_create_inode(काष्ठा inode *, ino_t *, काष्ठा buffer_head **);
पूर्णांक nilfs_अगरile_delete_inode(काष्ठा inode *, ino_t);
पूर्णांक nilfs_अगरile_get_inode_block(काष्ठा inode *, ino_t, काष्ठा buffer_head **);

पूर्णांक nilfs_अगरile_count_मुक्त_inodes(काष्ठा inode *, u64 *, u64 *);

पूर्णांक nilfs_अगरile_पढ़ो(काष्ठा super_block *sb, काष्ठा nilfs_root *root,
		     माप_प्रकार inode_size, काष्ठा nilfs_inode *raw_inode,
		     काष्ठा inode **inodep);

#पूर्ण_अगर	/* _NILFS_Iखाता_H */
