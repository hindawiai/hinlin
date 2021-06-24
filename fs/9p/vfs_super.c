<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/9p/vfs_super.c
 *
 * This file contians superblock ops क्रम 9P2000. It is पूर्णांकended that
 * you mount this file प्रणाली on directories.
 *
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/inet.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mount.h>
#समावेश <linux/idr.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/statfs.h>
#समावेश <linux/magic.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "fid.h"
#समावेश "xattr.h"
#समावेश "acl.h"

अटल स्थिर काष्ठा super_operations v9fs_super_ops, v9fs_super_ops_करोtl;

/**
 * v9fs_set_super - set the superblock
 * @s: super block
 * @data: file प्रणाली specअगरic data
 *
 */

अटल पूर्णांक v9fs_set_super(काष्ठा super_block *s, व्योम *data)
अणु
	s->s_fs_info = data;
	वापस set_anon_super(s, data);
पूर्ण

/**
 * v9fs_fill_super - populate superblock with info
 * @sb: superblock
 * @v9ses: session inक्रमmation
 * @flags: flags propagated from v9fs_mount()
 *
 */

अटल पूर्णांक
v9fs_fill_super(काष्ठा super_block *sb, काष्ठा v9fs_session_info *v9ses,
		पूर्णांक flags)
अणु
	पूर्णांक ret;

	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_blocksize_bits = fls(v9ses->maxdata - 1);
	sb->s_blocksize = 1 << sb->s_blocksize_bits;
	sb->s_magic = V9FS_MAGIC;
	अगर (v9fs_proto_करोtl(v9ses)) अणु
		sb->s_op = &v9fs_super_ops_करोtl;
		sb->s_xattr = v9fs_xattr_handlers;
	पूर्ण अन्यथा अणु
		sb->s_op = &v9fs_super_ops;
		sb->s_समय_max = U32_MAX;
	पूर्ण

	sb->s_समय_min = 0;

	ret = super_setup_bdi(sb);
	अगर (ret)
		वापस ret;

	अगर (!v9ses->cache) अणु
		sb->s_bdi->ra_pages = 0;
		sb->s_bdi->io_pages = 0;
	पूर्ण

	sb->s_flags |= SB_ACTIVE | SB_सूचीSYNC;
	अगर (!v9ses->cache)
		sb->s_flags |= SB_SYNCHRONOUS;

#अगर_घोषित CONFIG_9P_FS_POSIX_ACL
	अगर ((v9ses->flags & V9FS_ACL_MASK) == V9FS_POSIX_ACL)
		sb->s_flags |= SB_POSIXACL;
#पूर्ण_अगर

	वापस 0;
पूर्ण

/**
 * v9fs_mount - mount a superblock
 * @fs_type: file प्रणाली type
 * @flags: mount flags
 * @dev_name: device name that was mounted
 * @data: mount options
 *
 */

अटल काष्ठा dentry *v9fs_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
		       स्थिर अक्षर *dev_name, व्योम *data)
अणु
	काष्ठा super_block *sb = शून्य;
	काष्ठा inode *inode = शून्य;
	काष्ठा dentry *root = शून्य;
	काष्ठा v9fs_session_info *v9ses = शून्य;
	umode_t mode = S_IRWXUGO | S_ISVTX;
	काष्ठा p9_fid *fid;
	पूर्णांक retval = 0;

	p9_debug(P9_DEBUG_VFS, "\n");

	v9ses = kzalloc(माप(काष्ठा v9fs_session_info), GFP_KERNEL);
	अगर (!v9ses)
		वापस ERR_PTR(-ENOMEM);

	fid = v9fs_session_init(v9ses, dev_name, data);
	अगर (IS_ERR(fid)) अणु
		retval = PTR_ERR(fid);
		जाओ मुक्त_session;
	पूर्ण

	sb = sget(fs_type, शून्य, v9fs_set_super, flags, v9ses);
	अगर (IS_ERR(sb)) अणु
		retval = PTR_ERR(sb);
		जाओ clunk_fid;
	पूर्ण
	retval = v9fs_fill_super(sb, v9ses, flags);
	अगर (retval)
		जाओ release_sb;

	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		sb->s_d_op = &v9fs_cached_dentry_operations;
	अन्यथा
		sb->s_d_op = &v9fs_dentry_operations;

	inode = v9fs_get_inode(sb, S_IFसूची | mode, 0);
	अगर (IS_ERR(inode)) अणु
		retval = PTR_ERR(inode);
		जाओ release_sb;
	पूर्ण

	root = d_make_root(inode);
	अगर (!root) अणु
		retval = -ENOMEM;
		जाओ release_sb;
	पूर्ण
	sb->s_root = root;
	अगर (v9fs_proto_करोtl(v9ses)) अणु
		काष्ठा p9_stat_करोtl *st = शून्य;
		st = p9_client_getattr_करोtl(fid, P9_STATS_BASIC);
		अगर (IS_ERR(st)) अणु
			retval = PTR_ERR(st);
			जाओ release_sb;
		पूर्ण
		d_inode(root)->i_ino = v9fs_qid2ino(&st->qid);
		v9fs_stat2inode_करोtl(st, d_inode(root), 0);
		kमुक्त(st);
	पूर्ण अन्यथा अणु
		काष्ठा p9_wstat *st = शून्य;
		st = p9_client_stat(fid);
		अगर (IS_ERR(st)) अणु
			retval = PTR_ERR(st);
			जाओ release_sb;
		पूर्ण

		d_inode(root)->i_ino = v9fs_qid2ino(&st->qid);
		v9fs_stat2inode(st, d_inode(root), sb, 0);

		p9stat_मुक्त(st);
		kमुक्त(st);
	पूर्ण
	retval = v9fs_get_acl(inode, fid);
	अगर (retval)
		जाओ release_sb;
	v9fs_fid_add(root, fid);

	p9_debug(P9_DEBUG_VFS, " simple set mount, return 0\n");
	वापस dget(sb->s_root);

clunk_fid:
	p9_client_clunk(fid);
	v9fs_session_बंद(v9ses);
मुक्त_session:
	kमुक्त(v9ses);
	वापस ERR_PTR(retval);

release_sb:
	/*
	 * we will करो the session_बंद and root dentry release
	 * in the below call. But we need to clunk fid, because we haven't
	 * attached the fid to dentry so it won't get clunked
	 * स्वतःmatically.
	 */
	p9_client_clunk(fid);
	deactivate_locked_super(sb);
	वापस ERR_PTR(retval);
पूर्ण

/**
 * v9fs_समाप्त_super - Kill Superblock
 * @s: superblock
 *
 */

अटल व्योम v9fs_समाप्त_super(काष्ठा super_block *s)
अणु
	काष्ठा v9fs_session_info *v9ses = s->s_fs_info;

	p9_debug(P9_DEBUG_VFS, " %p\n", s);

	समाप्त_anon_super(s);

	v9fs_session_cancel(v9ses);
	v9fs_session_बंद(v9ses);
	kमुक्त(v9ses);
	s->s_fs_info = शून्य;
	p9_debug(P9_DEBUG_VFS, "exiting kill_super\n");
पूर्ण

अटल व्योम
v9fs_umount_begin(काष्ठा super_block *sb)
अणु
	काष्ठा v9fs_session_info *v9ses;

	v9ses = sb->s_fs_info;
	v9fs_session_begin_cancel(v9ses);
पूर्ण

अटल पूर्णांक v9fs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid;
	काष्ठा p9_rstatfs rs;
	पूर्णांक res;

	fid = v9fs_fid_lookup(dentry);
	अगर (IS_ERR(fid)) अणु
		res = PTR_ERR(fid);
		जाओ करोne;
	पूर्ण

	v9ses = v9fs_dentry2v9ses(dentry);
	अगर (v9fs_proto_करोtl(v9ses)) अणु
		res = p9_client_statfs(fid, &rs);
		अगर (res == 0) अणु
			buf->f_type = rs.type;
			buf->f_bsize = rs.bsize;
			buf->f_blocks = rs.blocks;
			buf->f_bमुक्त = rs.bमुक्त;
			buf->f_bavail = rs.bavail;
			buf->f_files = rs.files;
			buf->f_fमुक्त = rs.fमुक्त;
			buf->f_fsid = u64_to_fsid(rs.fsid);
			buf->f_namelen = rs.namelen;
		पूर्ण
		अगर (res != -ENOSYS)
			जाओ करोne;
	पूर्ण
	res = simple_statfs(dentry, buf);
करोne:
	p9_client_clunk(fid);
	वापस res;
पूर्ण

अटल पूर्णांक v9fs_drop_inode(काष्ठा inode *inode)
अणु
	काष्ठा v9fs_session_info *v9ses;
	v9ses = v9fs_inode2v9ses(inode);
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		वापस generic_drop_inode(inode);
	/*
	 * in हाल of non cached mode always drop the
	 * the inode because we want the inode attribute
	 * to always match that on the server.
	 */
	वापस 1;
पूर्ण

अटल पूर्णांक v9fs_ग_लिखो_inode(काष्ठा inode *inode,
			    काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;
	काष्ठा p9_wstat wstat;
	काष्ठा v9fs_inode *v9inode;
	/*
	 * send an fsync request to server irrespective of
	 * wbc->sync_mode.
	 */
	p9_debug(P9_DEBUG_VFS, "%s: inode %p\n", __func__, inode);
	v9inode = V9FS_I(inode);
	अगर (!v9inode->ग_लिखोback_fid)
		वापस 0;
	v9fs_blank_wstat(&wstat);

	ret = p9_client_wstat(v9inode->ग_लिखोback_fid, &wstat);
	अगर (ret < 0) अणु
		__mark_inode_dirty(inode, I_सूचीTY_DATASYNC);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक v9fs_ग_लिखो_inode_करोtl(काष्ठा inode *inode,
				 काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;
	काष्ठा v9fs_inode *v9inode;
	/*
	 * send an fsync request to server irrespective of
	 * wbc->sync_mode.
	 */
	v9inode = V9FS_I(inode);
	p9_debug(P9_DEBUG_VFS, "%s: inode %p, writeback_fid %p\n",
		 __func__, inode, v9inode->ग_लिखोback_fid);
	अगर (!v9inode->ग_लिखोback_fid)
		वापस 0;

	ret = p9_client_fsync(v9inode->ग_लिखोback_fid, 0);
	अगर (ret < 0) अणु
		__mark_inode_dirty(inode, I_सूचीTY_DATASYNC);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations v9fs_super_ops = अणु
	.alloc_inode = v9fs_alloc_inode,
	.मुक्त_inode = v9fs_मुक्त_inode,
	.statfs = simple_statfs,
	.evict_inode = v9fs_evict_inode,
	.show_options = v9fs_show_options,
	.umount_begin = v9fs_umount_begin,
	.ग_लिखो_inode = v9fs_ग_लिखो_inode,
पूर्ण;

अटल स्थिर काष्ठा super_operations v9fs_super_ops_करोtl = अणु
	.alloc_inode = v9fs_alloc_inode,
	.मुक्त_inode = v9fs_मुक्त_inode,
	.statfs = v9fs_statfs,
	.drop_inode = v9fs_drop_inode,
	.evict_inode = v9fs_evict_inode,
	.show_options = v9fs_show_options,
	.umount_begin = v9fs_umount_begin,
	.ग_लिखो_inode = v9fs_ग_लिखो_inode_करोtl,
पूर्ण;

काष्ठा file_प्रणाली_type v9fs_fs_type = अणु
	.name = "9p",
	.mount = v9fs_mount,
	.समाप्त_sb = v9fs_समाप्त_super,
	.owner = THIS_MODULE,
	.fs_flags = FS_RENAME_DOES_D_MOVE,
पूर्ण;
MODULE_ALIAS_FS("9p");
