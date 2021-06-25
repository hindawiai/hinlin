<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2001
 */
#अगर_अघोषित	_H_JFS_INODE
#घोषणा _H_JFS_INODE

काष्ठा fid;

बाह्य काष्ठा inode *ialloc(काष्ठा inode *, umode_t);
बाह्य पूर्णांक jfs_fsync(काष्ठा file *, loff_t, loff_t, पूर्णांक);
बाह्य पूर्णांक jfs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa);
बाह्य पूर्णांक jfs_fileattr_set(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry, काष्ठा fileattr *fa);
बाह्य दीर्घ jfs_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
बाह्य काष्ठा inode *jfs_iget(काष्ठा super_block *, अचिन्हित दीर्घ);
बाह्य पूर्णांक jfs_commit_inode(काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक jfs_ग_लिखो_inode(काष्ठा inode *, काष्ठा ग_लिखोback_control *);
बाह्य व्योम jfs_evict_inode(काष्ठा inode *);
बाह्य व्योम jfs_dirty_inode(काष्ठा inode *, पूर्णांक);
बाह्य व्योम jfs_truncate(काष्ठा inode *);
बाह्य व्योम jfs_truncate_nolock(काष्ठा inode *, loff_t);
बाह्य व्योम jfs_मुक्त_zero_link(काष्ठा inode *);
बाह्य काष्ठा dentry *jfs_get_parent(काष्ठा dentry *dentry);
बाह्य काष्ठा dentry *jfs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
	पूर्णांक fh_len, पूर्णांक fh_type);
बाह्य काष्ठा dentry *jfs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
	पूर्णांक fh_len, पूर्णांक fh_type);
बाह्य व्योम jfs_set_inode_flags(काष्ठा inode *);
बाह्य पूर्णांक jfs_get_block(काष्ठा inode *, sector_t, काष्ठा buffer_head *, पूर्णांक);
बाह्य पूर्णांक jfs_setattr(काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);

बाह्य स्थिर काष्ठा address_space_operations jfs_aops;
बाह्य स्थिर काष्ठा inode_operations jfs_dir_inode_operations;
बाह्य स्थिर काष्ठा file_operations jfs_dir_operations;
बाह्य स्थिर काष्ठा inode_operations jfs_file_inode_operations;
बाह्य स्थिर काष्ठा file_operations jfs_file_operations;
बाह्य स्थिर काष्ठा inode_operations jfs_symlink_inode_operations;
बाह्य स्थिर काष्ठा inode_operations jfs_fast_symlink_inode_operations;
बाह्य स्थिर काष्ठा dentry_operations jfs_ci_dentry_operations;
#पूर्ण_अगर				/* _H_JFS_INODE */
