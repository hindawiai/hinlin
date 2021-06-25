<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * dcache.h
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_DCACHE_H
#घोषणा OCFS2_DCACHE_H

बाह्य स्थिर काष्ठा dentry_operations ocfs2_dentry_ops;

काष्ठा ocfs2_dentry_lock अणु
	अचिन्हित पूर्णांक		dl_count;
	u64			dl_parent_blkno;

	/*
	 * The ocfs2_dentry_lock keeps an inode reference until
	 * dl_lockres has been destroyed. This is usually करोne in
	 * ->d_iput() anyway, so there should be minimal impact.
	 */
	काष्ठा inode		*dl_inode;
	काष्ठा ocfs2_lock_res	dl_lockres;
पूर्ण;

पूर्णांक ocfs2_dentry_attach_lock(काष्ठा dentry *dentry, काष्ठा inode *inode,
			     u64 parent_blkno);

व्योम ocfs2_dentry_lock_put(काष्ठा ocfs2_super *osb,
			   काष्ठा ocfs2_dentry_lock *dl);

काष्ठा dentry *ocfs2_find_local_alias(काष्ठा inode *inode, u64 parent_blkno,
				      पूर्णांक skip_unhashed);

व्योम ocfs2_dentry_move(काष्ठा dentry *dentry, काष्ठा dentry *target,
		       काष्ठा inode *old_dir, काष्ठा inode *new_dir);

बाह्य spinlock_t dentry_attach_lock;
व्योम ocfs2_dentry_attach_gen(काष्ठा dentry *dentry);

#पूर्ण_अगर /* OCFS2_DCACHE_H */
