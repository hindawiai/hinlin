<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	fs/bfs/bfs.h
 *	Copyright (C) 1999-2018 Tigran Aivazian <aivazian.tigran@gmail.com>
 */
#अगर_अघोषित _FS_BFS_BFS_H
#घोषणा _FS_BFS_BFS_H

#समावेश <linux/bfs_fs.h>

/* In theory BFS supports up to 512 inodes, numbered from 2 (क्रम /) up to 513 inclusive.
   In actual fact, attempting to create the 512th inode (i.e. inode No. 513 or file No. 511)
   will fail with ENOSPC in bfs_add_entry(): the root directory cannot contain so many entries, counting '..'.
   So, mkfs.bfs(8) should really limit its -N option to 511 and not 512. For now, we just prपूर्णांक a warning
   अगर a fileप्रणाली is mounted with such "impossible to fill up" number of inodes */
#घोषणा BFS_MAX_LASTI	513

/*
 * BFS file प्रणाली in-core superblock info
 */
काष्ठा bfs_sb_info अणु
	अचिन्हित दीर्घ si_blocks;
	अचिन्हित दीर्घ si_मुक्तb;
	अचिन्हित दीर्घ si_मुक्तi;
	अचिन्हित दीर्घ si_lf_eblk;
	अचिन्हित दीर्घ si_lasti;
	DECLARE_BITMAP(si_imap, BFS_MAX_LASTI+1);
	काष्ठा mutex bfs_lock;
पूर्ण;

/*
 * BFS file प्रणाली in-core inode info
 */
काष्ठा bfs_inode_info अणु
	अचिन्हित दीर्घ i_dsk_ino; /* inode number from the disk, can be 0 */
	अचिन्हित दीर्घ i_sblock;
	अचिन्हित दीर्घ i_eblock;
	काष्ठा inode vfs_inode;
पूर्ण;

अटल अंतरभूत काष्ठा bfs_sb_info *BFS_SB(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत काष्ठा bfs_inode_info *BFS_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा bfs_inode_info, vfs_inode);
पूर्ण


#घोषणा म_लिखो(क्रमmat, args...) \
	prपूर्णांकk(KERN_ERR "BFS-fs: %s(): " क्रमmat, __func__, ## args)

/* inode.c */
बाह्य काष्ठा inode *bfs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino);
बाह्य व्योम bfs_dump_imap(स्थिर अक्षर *, काष्ठा super_block *);

/* file.c */
बाह्य स्थिर काष्ठा inode_operations bfs_file_inops;
बाह्य स्थिर काष्ठा file_operations bfs_file_operations;
बाह्य स्थिर काष्ठा address_space_operations bfs_aops;

/* dir.c */
बाह्य स्थिर काष्ठा inode_operations bfs_dir_inops;
बाह्य स्थिर काष्ठा file_operations bfs_dir_operations;

#पूर्ण_अगर /* _FS_BFS_BFS_H */
