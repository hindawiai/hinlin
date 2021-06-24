<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/9p/vfs_dentry.c
 *
 * This file contians vfs dentry ops क्रम the 9P2000 protocol.
 *
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/inet.h>
#समावेश <linux/namei.h>
#समावेश <linux/idr.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "fid.h"

/**
 * v9fs_cached_dentry_delete - called when dentry refcount equals 0
 * @dentry:  dentry in question
 *
 */
अटल पूर्णांक v9fs_cached_dentry_delete(स्थिर काष्ठा dentry *dentry)
अणु
	p9_debug(P9_DEBUG_VFS, " dentry: %pd (%p)\n",
		 dentry, dentry);

	/* Don't cache negative dentries */
	अगर (d_really_is_negative(dentry))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * v9fs_dentry_release - called when dentry is going to be मुक्तd
 * @dentry:  dentry that is being release
 *
 */

अटल व्योम v9fs_dentry_release(काष्ठा dentry *dentry)
अणु
	काष्ठा hlist_node *p, *n;
	p9_debug(P9_DEBUG_VFS, " dentry: %pd (%p)\n",
		 dentry, dentry);
	hlist_क्रम_each_safe(p, n, (काष्ठा hlist_head *)&dentry->d_fsdata)
		p9_client_clunk(hlist_entry(p, काष्ठा p9_fid, dlist));
	dentry->d_fsdata = शून्य;
पूर्ण

अटल पूर्णांक v9fs_lookup_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा p9_fid *fid;
	काष्ठा inode *inode;
	काष्ठा v9fs_inode *v9inode;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	inode = d_inode(dentry);
	अगर (!inode)
		जाओ out_valid;

	v9inode = V9FS_I(inode);
	अगर (v9inode->cache_validity & V9FS_INO_INVALID_ATTR) अणु
		पूर्णांक retval;
		काष्ठा v9fs_session_info *v9ses;
		fid = v9fs_fid_lookup(dentry);
		अगर (IS_ERR(fid))
			वापस PTR_ERR(fid);

		v9ses = v9fs_inode2v9ses(inode);
		अगर (v9fs_proto_करोtl(v9ses))
			retval = v9fs_refresh_inode_करोtl(fid, inode);
		अन्यथा
			retval = v9fs_refresh_inode(fid, inode);
		p9_client_clunk(fid);

		अगर (retval == -ENOENT)
			वापस 0;
		अगर (retval < 0)
			वापस retval;
	पूर्ण
out_valid:
	वापस 1;
पूर्ण

स्थिर काष्ठा dentry_operations v9fs_cached_dentry_operations = अणु
	.d_revalidate = v9fs_lookup_revalidate,
	.d_weak_revalidate = v9fs_lookup_revalidate,
	.d_delete = v9fs_cached_dentry_delete,
	.d_release = v9fs_dentry_release,
पूर्ण;

स्थिर काष्ठा dentry_operations v9fs_dentry_operations = अणु
	.d_delete = always_delete_dentry,
	.d_release = v9fs_dentry_release,
पूर्ण;
