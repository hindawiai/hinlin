<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * V9FS FID Management
 *
 *  Copyright (C) 2005 by Eric Van Hensbergen <ericvh@gmail.com>
 */
#अगर_अघोषित FS_9P_FID_H
#घोषणा FS_9P_FID_H
#समावेश <linux/list.h>

काष्ठा p9_fid *v9fs_fid_lookup(काष्ठा dentry *dentry);
अटल अंतरभूत काष्ठा p9_fid *v9fs_parent_fid(काष्ठा dentry *dentry)
अणु
	वापस v9fs_fid_lookup(dentry->d_parent);
पूर्ण
व्योम v9fs_fid_add(काष्ठा dentry *dentry, काष्ठा p9_fid *fid);
काष्ठा p9_fid *v9fs_ग_लिखोback_fid(काष्ठा dentry *dentry);
व्योम v9fs_खोलो_fid_add(काष्ठा inode *inode, काष्ठा p9_fid *fid);
अटल अंतरभूत काष्ठा p9_fid *clone_fid(काष्ठा p9_fid *fid)
अणु
	वापस IS_ERR(fid) ? fid :  p9_client_walk(fid, 0, शून्य, 1);
पूर्ण
अटल अंतरभूत काष्ठा p9_fid *v9fs_fid_clone(काष्ठा dentry *dentry)
अणु
	काष्ठा p9_fid *fid, *nfid;

	fid = v9fs_fid_lookup(dentry);
	अगर (!fid || IS_ERR(fid))
		वापस fid;

	nfid = clone_fid(fid);
	p9_client_clunk(fid);
	वापस nfid;
पूर्ण
#पूर्ण_अगर
