<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * V9FS VFS extensions.
 *
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */
#अगर_अघोषित FS_9P_V9FS_VFS_H
#घोषणा FS_9P_V9FS_VFS_H

/* plan9 semantics are that created files are implicitly खोलोed.
 * But linux semantics are that you call create, then खोलो.
 * the plan9 approach is superior as it provides an atomic
 * खोलो.
 * we track the create fid here. When the file is खोलोed, अगर fiकरोpen is
 * non-zero, we use the fid and can skip some steps.
 * there may be a better way to करो this, but I करोn't know it.
 * one BAD way is to clunk the fid on create, then खोलो it again:
 * you lose the atomicity of file खोलो
 */

/* special हाल:
 * unlink calls हटाओ, which is an implicit clunk. So we have to track
 * that kind of thing so that we करोn't try to clunk a dead fid.
 */
#घोषणा P9_LOCK_TIMEOUT (30*HZ)

/* flags क्रम v9fs_stat2inode() & v9fs_stat2inode_करोtl() */
#घोषणा V9FS_STAT2INODE_KEEP_ISIZE 1

बाह्य काष्ठा file_प्रणाली_type v9fs_fs_type;
बाह्य स्थिर काष्ठा address_space_operations v9fs_addr_operations;
बाह्य स्थिर काष्ठा file_operations v9fs_file_operations;
बाह्य स्थिर काष्ठा file_operations v9fs_file_operations_करोtl;
बाह्य स्थिर काष्ठा file_operations v9fs_dir_operations;
बाह्य स्थिर काष्ठा file_operations v9fs_dir_operations_करोtl;
बाह्य स्थिर काष्ठा dentry_operations v9fs_dentry_operations;
बाह्य स्थिर काष्ठा dentry_operations v9fs_cached_dentry_operations;
बाह्य स्थिर काष्ठा file_operations v9fs_cached_file_operations;
बाह्य स्थिर काष्ठा file_operations v9fs_cached_file_operations_करोtl;
बाह्य स्थिर काष्ठा file_operations v9fs_mmap_file_operations;
बाह्य स्थिर काष्ठा file_operations v9fs_mmap_file_operations_करोtl;
बाह्य काष्ठा kmem_cache *v9fs_inode_cache;

काष्ठा inode *v9fs_alloc_inode(काष्ठा super_block *sb);
व्योम v9fs_मुक्त_inode(काष्ठा inode *inode);
काष्ठा inode *v9fs_get_inode(काष्ठा super_block *sb, umode_t mode, dev_t);
पूर्णांक v9fs_init_inode(काष्ठा v9fs_session_info *v9ses,
		    काष्ठा inode *inode, umode_t mode, dev_t);
व्योम v9fs_evict_inode(काष्ठा inode *inode);
ino_t v9fs_qid2ino(काष्ठा p9_qid *qid);
व्योम v9fs_stat2inode(काष्ठा p9_wstat *stat, काष्ठा inode *inode,
		      काष्ठा super_block *sb, अचिन्हित पूर्णांक flags);
व्योम v9fs_stat2inode_करोtl(काष्ठा p9_stat_करोtl *stat, काष्ठा inode *inode,
			   अचिन्हित पूर्णांक flags);
पूर्णांक v9fs_dir_release(काष्ठा inode *inode, काष्ठा file *filp);
पूर्णांक v9fs_file_खोलो(काष्ठा inode *inode, काष्ठा file *file);
व्योम v9fs_inode2stat(काष्ठा inode *inode, काष्ठा p9_wstat *stat);
पूर्णांक v9fs_uflags2omode(पूर्णांक uflags, पूर्णांक extended);

व्योम v9fs_blank_wstat(काष्ठा p9_wstat *wstat);
पूर्णांक v9fs_vfs_setattr_करोtl(काष्ठा user_namespace *, काष्ठा dentry *,
			  काष्ठा iattr *);
पूर्णांक v9fs_file_fsync_करोtl(काष्ठा file *filp, loff_t start, loff_t end,
			 पूर्णांक datasync);
पूर्णांक v9fs_refresh_inode(काष्ठा p9_fid *fid, काष्ठा inode *inode);
पूर्णांक v9fs_refresh_inode_करोtl(काष्ठा p9_fid *fid, काष्ठा inode *inode);
अटल अंतरभूत व्योम v9fs_invalidate_inode_attr(काष्ठा inode *inode)
अणु
	काष्ठा v9fs_inode *v9inode;
	v9inode = V9FS_I(inode);
	v9inode->cache_validity |= V9FS_INO_INVALID_ATTR;
	वापस;
पूर्ण

पूर्णांक v9fs_खोलो_to_करोtl_flags(पूर्णांक flags);

अटल अंतरभूत व्योम v9fs_i_size_ग_लिखो(काष्ठा inode *inode, loff_t i_size)
अणु
	/*
	 * 32-bit need the lock, concurrent updates could अवरोध the
	 * sequences and make i_size_पढ़ो() loop क्रमever.
	 * 64-bit updates are atomic and can skip the locking.
	 */
	अगर (माप(i_size) > माप(दीर्घ))
		spin_lock(&inode->i_lock);
	i_size_ग_लिखो(inode, i_size);
	अगर (माप(i_size) > माप(दीर्घ))
		spin_unlock(&inode->i_lock);
पूर्ण
#पूर्ण_अगर
