<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/9p/vfs_inode_करोtl.c
 *
 * This file contains vfs inode ops क्रम the 9P2000.L protocol.
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
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "fid.h"
#समावेश "cache.h"
#समावेश "xattr.h"
#समावेश "acl.h"

अटल पूर्णांक
v9fs_vfs_mknod_करोtl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		    काष्ठा dentry *dentry, umode_t omode, dev_t rdev);

/**
 * v9fs_get_fsgid_क्रम_create - Helper function to get the gid क्रम creating a
 * new file प्रणाली object. This checks the S_ISGID to determine the owning
 * group of the new file प्रणाली object.
 */

अटल kgid_t v9fs_get_fsgid_क्रम_create(काष्ठा inode *dir_inode)
अणु
	BUG_ON(dir_inode == शून्य);

	अगर (dir_inode->i_mode & S_ISGID) अणु
		/* set_gid bit is set.*/
		वापस dir_inode->i_gid;
	पूर्ण
	वापस current_fsgid();
पूर्ण

अटल पूर्णांक v9fs_test_inode_करोtl(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);
	काष्ठा p9_stat_करोtl *st = (काष्ठा p9_stat_करोtl *)data;

	/* करोn't match inode of dअगरferent type */
	अगर (inode_wrong_type(inode, st->st_mode))
		वापस 0;

	अगर (inode->i_generation != st->st_gen)
		वापस 0;

	/* compare qid details */
	अगर (स_भेद(&v9inode->qid.version,
		   &st->qid.version, माप(v9inode->qid.version)))
		वापस 0;

	अगर (v9inode->qid.type != st->qid.type)
		वापस 0;

	अगर (v9inode->qid.path != st->qid.path)
		वापस 0;
	वापस 1;
पूर्ण

/* Always get a new inode */
अटल पूर्णांक v9fs_test_new_inode_करोtl(काष्ठा inode *inode, व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक v9fs_set_inode_करोtl(काष्ठा inode *inode,  व्योम *data)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);
	काष्ठा p9_stat_करोtl *st = (काष्ठा p9_stat_करोtl *)data;

	स_नकल(&v9inode->qid, &st->qid, माप(st->qid));
	inode->i_generation = st->st_gen;
	वापस 0;
पूर्ण

अटल काष्ठा inode *v9fs_qid_iget_करोtl(काष्ठा super_block *sb,
					काष्ठा p9_qid *qid,
					काष्ठा p9_fid *fid,
					काष्ठा p9_stat_करोtl *st,
					पूर्णांक new)
अणु
	पूर्णांक retval;
	अचिन्हित दीर्घ i_ino;
	काष्ठा inode *inode;
	काष्ठा v9fs_session_info *v9ses = sb->s_fs_info;
	पूर्णांक (*test)(काष्ठा inode *, व्योम *);

	अगर (new)
		test = v9fs_test_new_inode_करोtl;
	अन्यथा
		test = v9fs_test_inode_करोtl;

	i_ino = v9fs_qid2ino(qid);
	inode = iget5_locked(sb, i_ino, test, v9fs_set_inode_करोtl, st);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;
	/*
	 * initialize the inode with the stat info
	 * FIXME!! we may need support क्रम stale inodes
	 * later.
	 */
	inode->i_ino = i_ino;
	retval = v9fs_init_inode(v9ses, inode,
				 st->st_mode, new_decode_dev(st->st_rdev));
	अगर (retval)
		जाओ error;

	v9fs_stat2inode_करोtl(st, inode, 0);
	v9fs_cache_inode_get_cookie(inode);
	retval = v9fs_get_acl(inode, fid);
	अगर (retval)
		जाओ error;

	unlock_new_inode(inode);
	वापस inode;
error:
	iget_failed(inode);
	वापस ERR_PTR(retval);

पूर्ण

काष्ठा inode *
v9fs_inode_from_fid_करोtl(काष्ठा v9fs_session_info *v9ses, काष्ठा p9_fid *fid,
			 काष्ठा super_block *sb, पूर्णांक new)
अणु
	काष्ठा p9_stat_करोtl *st;
	काष्ठा inode *inode = शून्य;

	st = p9_client_getattr_करोtl(fid, P9_STATS_BASIC | P9_STATS_GEN);
	अगर (IS_ERR(st))
		वापस ERR_CAST(st);

	inode = v9fs_qid_iget_करोtl(sb, &st->qid, fid, st, new);
	kमुक्त(st);
	वापस inode;
पूर्ण

काष्ठा करोtl_खोलोflag_map अणु
	पूर्णांक खोलो_flag;
	पूर्णांक करोtl_flag;
पूर्ण;

अटल पूर्णांक v9fs_mapped_करोtl_flags(पूर्णांक flags)
अणु
	पूर्णांक i;
	पूर्णांक rflags = 0;
	काष्ठा करोtl_खोलोflag_map करोtl_oflag_map[] = अणु
		अणु O_CREAT,	P9_DOTL_CREATE पूर्ण,
		अणु O_EXCL,	P9_DOTL_EXCL पूर्ण,
		अणु O_NOCTTY,	P9_DOTL_NOCTTY पूर्ण,
		अणु O_APPEND,	P9_DOTL_APPEND पूर्ण,
		अणु O_NONBLOCK,	P9_DOTL_NONBLOCK पूर्ण,
		अणु O_DSYNC,	P9_DOTL_DSYNC पूर्ण,
		अणु FASYNC,	P9_DOTL_FASYNC पूर्ण,
		अणु O_सूचीECT,	P9_DOTL_सूचीECT पूर्ण,
		अणु O_LARGEखाता,	P9_DOTL_LARGEखाता पूर्ण,
		अणु O_सूचीECTORY,	P9_DOTL_सूचीECTORY पूर्ण,
		अणु O_NOFOLLOW,	P9_DOTL_NOFOLLOW पूर्ण,
		अणु O_NOATIME,	P9_DOTL_NOATIME पूर्ण,
		अणु O_CLOEXEC,	P9_DOTL_CLOEXEC पूर्ण,
		अणु O_SYNC,	P9_DOTL_SYNCपूर्ण,
	पूर्ण;
	क्रम (i = 0; i < ARRAY_SIZE(करोtl_oflag_map); i++) अणु
		अगर (flags & करोtl_oflag_map[i].खोलो_flag)
			rflags |= करोtl_oflag_map[i].करोtl_flag;
	पूर्ण
	वापस rflags;
पूर्ण

/**
 * v9fs_खोलो_to_करोtl_flags- convert Linux specअगरic खोलो flags to
 * plan 9 खोलो flag.
 * @flags: flags to convert
 */
पूर्णांक v9fs_खोलो_to_करोtl_flags(पूर्णांक flags)
अणु
	पूर्णांक rflags = 0;

	/*
	 * We have same bits क्रम P9_DOTL_READONLY, P9_DOTL_WRONLY
	 * and P9_DOTL_NOACCESS
	 */
	rflags |= flags & O_ACCMODE;
	rflags |= v9fs_mapped_करोtl_flags(flags);

	वापस rflags;
पूर्ण

/**
 * v9fs_vfs_create_करोtl - VFS hook to create files क्रम 9P2000.L protocol.
 * @dir: directory inode that is being created
 * @dentry:  dentry that is being deleted
 * @omode: create permissions
 *
 */

अटल पूर्णांक
v9fs_vfs_create_करोtl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t omode, bool excl)
अणु
	वापस v9fs_vfs_mknod_करोtl(mnt_userns, dir, dentry, omode, 0);
पूर्ण

अटल पूर्णांक
v9fs_vfs_atomic_खोलो_करोtl(काष्ठा inode *dir, काष्ठा dentry *dentry,
			  काष्ठा file *file, अचिन्हित flags, umode_t omode)
अणु
	पूर्णांक err = 0;
	kgid_t gid;
	umode_t mode;
	स्थिर अचिन्हित अक्षर *name = शून्य;
	काष्ठा p9_qid qid;
	काष्ठा inode *inode;
	काष्ठा p9_fid *fid = शून्य;
	काष्ठा v9fs_inode *v9inode;
	काष्ठा p9_fid *dfid, *ofid, *inode_fid;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा posix_acl *pacl = शून्य, *dacl = शून्य;
	काष्ठा dentry *res = शून्य;

	अगर (d_in_lookup(dentry)) अणु
		res = v9fs_vfs_lookup(dir, dentry, 0);
		अगर (IS_ERR(res))
			वापस PTR_ERR(res);

		अगर (res)
			dentry = res;
	पूर्ण

	/* Only creates */
	अगर (!(flags & O_CREAT) || d_really_is_positive(dentry))
		वापस	finish_no_खोलो(file, res);

	v9ses = v9fs_inode2v9ses(dir);

	name = dentry->d_name.name;
	p9_debug(P9_DEBUG_VFS, "name:%s flags:0x%x mode:0x%hx\n",
		 name, flags, omode);

	dfid = v9fs_parent_fid(dentry);
	अगर (IS_ERR(dfid)) अणु
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		जाओ out;
	पूर्ण

	/* clone a fid to use क्रम creation */
	ofid = clone_fid(dfid);
	अगर (IS_ERR(ofid)) अणु
		err = PTR_ERR(ofid);
		p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n", err);
		जाओ out;
	पूर्ण

	gid = v9fs_get_fsgid_क्रम_create(dir);

	mode = omode;
	/* Update mode based on ACL value */
	err = v9fs_acl_mode(dir, &mode, &dacl, &pacl);
	अगर (err) अणु
		p9_debug(P9_DEBUG_VFS, "Failed to get acl values in creat %d\n",
			 err);
		जाओ error;
	पूर्ण
	err = p9_client_create_करोtl(ofid, name, v9fs_खोलो_to_करोtl_flags(flags),
				    mode, gid, &qid);
	अगर (err < 0) अणु
		p9_debug(P9_DEBUG_VFS, "p9_client_open_dotl failed in creat %d\n",
			 err);
		जाओ error;
	पूर्ण
	v9fs_invalidate_inode_attr(dir);

	/* instantiate inode and assign the unखोलोed fid to the dentry */
	fid = p9_client_walk(dfid, 1, &name, 1);
	p9_client_clunk(dfid);
	अगर (IS_ERR(fid)) अणु
		err = PTR_ERR(fid);
		p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n", err);
		fid = शून्य;
		जाओ error;
	पूर्ण
	inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		p9_debug(P9_DEBUG_VFS, "inode creation failed %d\n", err);
		जाओ error;
	पूर्ण
	/* Now set the ACL based on the शेष value */
	v9fs_set_create_acl(inode, fid, dacl, pacl);

	v9fs_fid_add(dentry, fid);
	d_instantiate(dentry, inode);

	v9inode = V9FS_I(inode);
	mutex_lock(&v9inode->v_mutex);
	अगर ((v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) &&
	    !v9inode->ग_लिखोback_fid &&
	    ((flags & O_ACCMODE) != O_RDONLY)) अणु
		/*
		 * clone a fid and add it to ग_लिखोback_fid
		 * we करो it during खोलो समय instead of
		 * page dirty समय via ग_लिखो_begin/page_mkग_लिखो
		 * because we want ग_लिखो after unlink useहाल
		 * to work.
		 */
		inode_fid = v9fs_ग_लिखोback_fid(dentry);
		अगर (IS_ERR(inode_fid)) अणु
			err = PTR_ERR(inode_fid);
			mutex_unlock(&v9inode->v_mutex);
			जाओ err_clunk_old_fid;
		पूर्ण
		v9inode->ग_लिखोback_fid = (व्योम *) inode_fid;
	पूर्ण
	mutex_unlock(&v9inode->v_mutex);
	/* Since we are खोलोing a file, assign the खोलो fid to the file */
	err = finish_खोलो(file, dentry, generic_file_खोलो);
	अगर (err)
		जाओ err_clunk_old_fid;
	file->निजी_data = ofid;
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		v9fs_cache_inode_set_cookie(inode, file);
	v9fs_खोलो_fid_add(inode, ofid);
	file->f_mode |= FMODE_CREATED;
out:
	v9fs_put_acl(dacl, pacl);
	dput(res);
	वापस err;

error:
	अगर (fid)
		p9_client_clunk(fid);
err_clunk_old_fid:
	अगर (ofid)
		p9_client_clunk(ofid);
	जाओ out;
पूर्ण

/**
 * v9fs_vfs_सूची_गढ़ो_करोtl - VFS सूची_गढ़ो hook to create a directory
 * @dir:  inode that is being unlinked
 * @dentry: dentry that is being unlinked
 * @omode: mode क्रम new directory
 *
 */

अटल पूर्णांक v9fs_vfs_सूची_गढ़ो_करोtl(काष्ठा user_namespace *mnt_userns,
			       काष्ठा inode *dir, काष्ठा dentry *dentry,
			       umode_t omode)
अणु
	पूर्णांक err;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid = शून्य, *dfid = शून्य;
	kgid_t gid;
	स्थिर अचिन्हित अक्षर *name;
	umode_t mode;
	काष्ठा inode *inode;
	काष्ठा p9_qid qid;
	काष्ठा posix_acl *dacl = शून्य, *pacl = शून्य;

	p9_debug(P9_DEBUG_VFS, "name %pd\n", dentry);
	err = 0;
	v9ses = v9fs_inode2v9ses(dir);

	omode |= S_IFसूची;
	अगर (dir->i_mode & S_ISGID)
		omode |= S_ISGID;

	dfid = v9fs_parent_fid(dentry);
	अगर (IS_ERR(dfid)) अणु
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		dfid = शून्य;
		जाओ error;
	पूर्ण

	gid = v9fs_get_fsgid_क्रम_create(dir);
	mode = omode;
	/* Update mode based on ACL value */
	err = v9fs_acl_mode(dir, &mode, &dacl, &pacl);
	अगर (err) अणु
		p9_debug(P9_DEBUG_VFS, "Failed to get acl values in mkdir %d\n",
			 err);
		जाओ error;
	पूर्ण
	name = dentry->d_name.name;
	err = p9_client_सूची_गढ़ो_करोtl(dfid, name, mode, gid, &qid);
	अगर (err < 0)
		जाओ error;
	fid = p9_client_walk(dfid, 1, &name, 1);
	अगर (IS_ERR(fid)) अणु
		err = PTR_ERR(fid);
		p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n",
			 err);
		fid = शून्य;
		जाओ error;
	पूर्ण

	/* instantiate inode and assign the unखोलोed fid to the dentry */
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) अणु
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			p9_debug(P9_DEBUG_VFS, "inode creation failed %d\n",
				 err);
			जाओ error;
		पूर्ण
		v9fs_fid_add(dentry, fid);
		v9fs_set_create_acl(inode, fid, dacl, pacl);
		d_instantiate(dentry, inode);
		fid = शून्य;
		err = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Not in cached mode. No need to populate
		 * inode with stat. We need to get an inode
		 * so that we can set the acl with dentry
		 */
		inode = v9fs_get_inode(dir->i_sb, mode, 0);
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			जाओ error;
		पूर्ण
		v9fs_set_create_acl(inode, fid, dacl, pacl);
		d_instantiate(dentry, inode);
	पूर्ण
	inc_nlink(dir);
	v9fs_invalidate_inode_attr(dir);
error:
	अगर (fid)
		p9_client_clunk(fid);
	v9fs_put_acl(dacl, pacl);
	p9_client_clunk(dfid);
	वापस err;
पूर्ण

अटल पूर्णांक
v9fs_vfs_getattr_करोtl(काष्ठा user_namespace *mnt_userns,
		      स्थिर काष्ठा path *path, काष्ठा kstat *stat,
		      u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid;
	काष्ठा p9_stat_करोtl *st;

	p9_debug(P9_DEBUG_VFS, "dentry: %p\n", dentry);
	v9ses = v9fs_dentry2v9ses(dentry);
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) अणु
		generic_fillattr(&init_user_ns, d_inode(dentry), stat);
		वापस 0;
	पूर्ण
	fid = v9fs_fid_lookup(dentry);
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);

	/* Ask क्रम all the fields in stat काष्ठाure. Server will वापस
	 * whatever it supports
	 */

	st = p9_client_getattr_करोtl(fid, P9_STATS_ALL);
	p9_client_clunk(fid);
	अगर (IS_ERR(st))
		वापस PTR_ERR(st);

	v9fs_stat2inode_करोtl(st, d_inode(dentry), 0);
	generic_fillattr(&init_user_ns, d_inode(dentry), stat);
	/* Change block size to what the server वापसed */
	stat->blksize = st->st_blksize;

	kमुक्त(st);
	वापस 0;
पूर्ण

/*
 * Attribute flags.
 */
#घोषणा P9_ATTR_MODE		(1 << 0)
#घोषणा P9_ATTR_UID		(1 << 1)
#घोषणा P9_ATTR_GID		(1 << 2)
#घोषणा P9_ATTR_SIZE		(1 << 3)
#घोषणा P9_ATTR_ATIME		(1 << 4)
#घोषणा P9_ATTR_MTIME		(1 << 5)
#घोषणा P9_ATTR_CTIME		(1 << 6)
#घोषणा P9_ATTR_ATIME_SET	(1 << 7)
#घोषणा P9_ATTR_MTIME_SET	(1 << 8)

काष्ठा करोtl_iattr_map अणु
	पूर्णांक iattr_valid;
	पूर्णांक p9_iattr_valid;
पूर्ण;

अटल पूर्णांक v9fs_mapped_iattr_valid(पूर्णांक iattr_valid)
अणु
	पूर्णांक i;
	पूर्णांक p9_iattr_valid = 0;
	काष्ठा करोtl_iattr_map करोtl_iattr_map[] = अणु
		अणु ATTR_MODE,		P9_ATTR_MODE पूर्ण,
		अणु ATTR_UID,		P9_ATTR_UID पूर्ण,
		अणु ATTR_GID,		P9_ATTR_GID पूर्ण,
		अणु ATTR_SIZE,		P9_ATTR_SIZE पूर्ण,
		अणु ATTR_ATIME,		P9_ATTR_ATIME पूर्ण,
		अणु ATTR_MTIME,		P9_ATTR_MTIME पूर्ण,
		अणु ATTR_CTIME,		P9_ATTR_CTIME पूर्ण,
		अणु ATTR_ATIME_SET,	P9_ATTR_ATIME_SET पूर्ण,
		अणु ATTR_MTIME_SET,	P9_ATTR_MTIME_SET पूर्ण,
	पूर्ण;
	क्रम (i = 0; i < ARRAY_SIZE(करोtl_iattr_map); i++) अणु
		अगर (iattr_valid & करोtl_iattr_map[i].iattr_valid)
			p9_iattr_valid |= करोtl_iattr_map[i].p9_iattr_valid;
	पूर्ण
	वापस p9_iattr_valid;
पूर्ण

/**
 * v9fs_vfs_setattr_करोtl - set file metadata
 * @dentry: file whose metadata to set
 * @iattr: metadata assignment काष्ठाure
 *
 */

पूर्णांक v9fs_vfs_setattr_करोtl(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, काष्ठा iattr *iattr)
अणु
	पूर्णांक retval, use_dentry = 0;
	काष्ठा p9_fid *fid = शून्य;
	काष्ठा p9_iattr_करोtl p9attr;
	काष्ठा inode *inode = d_inode(dentry);

	p9_debug(P9_DEBUG_VFS, "\n");

	retval = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (retval)
		वापस retval;

	p9attr.valid = v9fs_mapped_iattr_valid(iattr->ia_valid);
	p9attr.mode = iattr->ia_mode;
	p9attr.uid = iattr->ia_uid;
	p9attr.gid = iattr->ia_gid;
	p9attr.size = iattr->ia_size;
	p9attr.aसमय_sec = iattr->ia_aसमय.tv_sec;
	p9attr.aसमय_nsec = iattr->ia_aसमय.tv_nsec;
	p9attr.mसमय_sec = iattr->ia_mसमय.tv_sec;
	p9attr.mसमय_nsec = iattr->ia_mसमय.tv_nsec;

	अगर (iattr->ia_valid & ATTR_खाता) अणु
		fid = iattr->ia_file->निजी_data;
		WARN_ON(!fid);
	पूर्ण
	अगर (!fid) अणु
		fid = v9fs_fid_lookup(dentry);
		use_dentry = 1;
	पूर्ण
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);

	/* Write all dirty data */
	अगर (S_ISREG(inode->i_mode))
		filemap_ग_लिखो_and_रुको(inode->i_mapping);

	retval = p9_client_setattr(fid, &p9attr);
	अगर (retval < 0) अणु
		अगर (use_dentry)
			p9_client_clunk(fid);
		वापस retval;
	पूर्ण

	अगर ((iattr->ia_valid & ATTR_SIZE) &&
	    iattr->ia_size != i_size_पढ़ो(inode))
		truncate_setsize(inode, iattr->ia_size);

	v9fs_invalidate_inode_attr(inode);
	setattr_copy(&init_user_ns, inode, iattr);
	mark_inode_dirty(inode);
	अगर (iattr->ia_valid & ATTR_MODE) अणु
		/* We also want to update ACL when we update mode bits */
		retval = v9fs_acl_chmod(inode, fid);
		अगर (retval < 0) अणु
			अगर (use_dentry)
				p9_client_clunk(fid);
			वापस retval;
		पूर्ण
	पूर्ण
	अगर (use_dentry)
		p9_client_clunk(fid);

	वापस 0;
पूर्ण

/**
 * v9fs_stat2inode_करोtl - populate an inode काष्ठाure with stat info
 * @stat: stat काष्ठाure
 * @inode: inode to populate
 * @flags: ctrl flags (e.g. V9FS_STAT2INODE_KEEP_ISIZE)
 *
 */

व्योम
v9fs_stat2inode_करोtl(काष्ठा p9_stat_करोtl *stat, काष्ठा inode *inode,
		      अचिन्हित पूर्णांक flags)
अणु
	umode_t mode;
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	अगर ((stat->st_result_mask & P9_STATS_BASIC) == P9_STATS_BASIC) अणु
		inode->i_aसमय.tv_sec = stat->st_aसमय_sec;
		inode->i_aसमय.tv_nsec = stat->st_aसमय_nsec;
		inode->i_mसमय.tv_sec = stat->st_mसमय_sec;
		inode->i_mसमय.tv_nsec = stat->st_mसमय_nsec;
		inode->i_स_समय.tv_sec = stat->st_स_समय_sec;
		inode->i_स_समय.tv_nsec = stat->st_स_समय_nsec;
		inode->i_uid = stat->st_uid;
		inode->i_gid = stat->st_gid;
		set_nlink(inode, stat->st_nlink);

		mode = stat->st_mode & S_IALLUGO;
		mode |= inode->i_mode & ~S_IALLUGO;
		inode->i_mode = mode;

		अगर (!(flags & V9FS_STAT2INODE_KEEP_ISIZE))
			v9fs_i_size_ग_लिखो(inode, stat->st_size);
		inode->i_blocks = stat->st_blocks;
	पूर्ण अन्यथा अणु
		अगर (stat->st_result_mask & P9_STATS_ATIME) अणु
			inode->i_aसमय.tv_sec = stat->st_aसमय_sec;
			inode->i_aसमय.tv_nsec = stat->st_aसमय_nsec;
		पूर्ण
		अगर (stat->st_result_mask & P9_STATS_MTIME) अणु
			inode->i_mसमय.tv_sec = stat->st_mसमय_sec;
			inode->i_mसमय.tv_nsec = stat->st_mसमय_nsec;
		पूर्ण
		अगर (stat->st_result_mask & P9_STATS_CTIME) अणु
			inode->i_स_समय.tv_sec = stat->st_स_समय_sec;
			inode->i_स_समय.tv_nsec = stat->st_स_समय_nsec;
		पूर्ण
		अगर (stat->st_result_mask & P9_STATS_UID)
			inode->i_uid = stat->st_uid;
		अगर (stat->st_result_mask & P9_STATS_GID)
			inode->i_gid = stat->st_gid;
		अगर (stat->st_result_mask & P9_STATS_NLINK)
			set_nlink(inode, stat->st_nlink);
		अगर (stat->st_result_mask & P9_STATS_MODE) अणु
			mode = stat->st_mode & S_IALLUGO;
			mode |= inode->i_mode & ~S_IALLUGO;
			inode->i_mode = mode;
		पूर्ण
		अगर (!(flags & V9FS_STAT2INODE_KEEP_ISIZE) &&
		    stat->st_result_mask & P9_STATS_SIZE)
			v9fs_i_size_ग_लिखो(inode, stat->st_size);
		अगर (stat->st_result_mask & P9_STATS_BLOCKS)
			inode->i_blocks = stat->st_blocks;
	पूर्ण
	अगर (stat->st_result_mask & P9_STATS_GEN)
		inode->i_generation = stat->st_gen;

	/* Currently we करोn't support P9_STATS_BTIME and P9_STATS_DATA_VERSION
	 * because the inode काष्ठाure करोes not have fields क्रम them.
	 */
	v9inode->cache_validity &= ~V9FS_INO_INVALID_ATTR;
पूर्ण

अटल पूर्णांक
v9fs_vfs_symlink_करोtl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	पूर्णांक err;
	kgid_t gid;
	स्थिर अचिन्हित अक्षर *name;
	काष्ठा p9_qid qid;
	काष्ठा inode *inode;
	काष्ठा p9_fid *dfid;
	काष्ठा p9_fid *fid = शून्य;
	काष्ठा v9fs_session_info *v9ses;

	name = dentry->d_name.name;
	p9_debug(P9_DEBUG_VFS, "%lu,%s,%s\n", dir->i_ino, name, symname);
	v9ses = v9fs_inode2v9ses(dir);

	dfid = v9fs_parent_fid(dentry);
	अगर (IS_ERR(dfid)) अणु
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		वापस err;
	पूर्ण

	gid = v9fs_get_fsgid_क्रम_create(dir);

	/* Server करोesn't alter fid on TSYMLINK. Hence no need to clone it. */
	err = p9_client_symlink(dfid, name, symname, gid, &qid);

	अगर (err < 0) अणु
		p9_debug(P9_DEBUG_VFS, "p9_client_symlink failed %d\n", err);
		जाओ error;
	पूर्ण

	v9fs_invalidate_inode_attr(dir);
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) अणु
		/* Now walk from the parent so we can get an unखोलोed fid. */
		fid = p9_client_walk(dfid, 1, &name, 1);
		अगर (IS_ERR(fid)) अणु
			err = PTR_ERR(fid);
			p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n",
				 err);
			fid = शून्य;
			जाओ error;
		पूर्ण

		/* instantiate inode and assign the unखोलोed fid to dentry */
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			p9_debug(P9_DEBUG_VFS, "inode creation failed %d\n",
				 err);
			जाओ error;
		पूर्ण
		v9fs_fid_add(dentry, fid);
		d_instantiate(dentry, inode);
		fid = शून्य;
		err = 0;
	पूर्ण अन्यथा अणु
		/* Not in cached mode. No need to populate inode with stat */
		inode = v9fs_get_inode(dir->i_sb, S_IFLNK, 0);
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			जाओ error;
		पूर्ण
		d_instantiate(dentry, inode);
	पूर्ण

error:
	अगर (fid)
		p9_client_clunk(fid);

	p9_client_clunk(dfid);
	वापस err;
पूर्ण

/**
 * v9fs_vfs_link_करोtl - create a hardlink क्रम करोtl
 * @old_dentry: dentry क्रम file to link to
 * @dir: inode destination क्रम new link
 * @dentry: dentry क्रम link
 *
 */

अटल पूर्णांक
v9fs_vfs_link_करोtl(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
		काष्ठा dentry *dentry)
अणु
	पूर्णांक err;
	काष्ठा p9_fid *dfid, *oldfid;
	काष्ठा v9fs_session_info *v9ses;

	p9_debug(P9_DEBUG_VFS, "dir ino: %lu, old_name: %pd, new_name: %pd\n",
		 dir->i_ino, old_dentry, dentry);

	v9ses = v9fs_inode2v9ses(dir);
	dfid = v9fs_parent_fid(dentry);
	अगर (IS_ERR(dfid))
		वापस PTR_ERR(dfid);

	oldfid = v9fs_fid_lookup(old_dentry);
	अगर (IS_ERR(oldfid)) अणु
		p9_client_clunk(dfid);
		वापस PTR_ERR(oldfid);
	पूर्ण

	err = p9_client_link(dfid, oldfid, dentry->d_name.name);

	p9_client_clunk(dfid);
	p9_client_clunk(oldfid);
	अगर (err < 0) अणु
		p9_debug(P9_DEBUG_VFS, "p9_client_link failed %d\n", err);
		वापस err;
	पूर्ण

	v9fs_invalidate_inode_attr(dir);
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) अणु
		/* Get the latest stat info from server. */
		काष्ठा p9_fid *fid;
		fid = v9fs_fid_lookup(old_dentry);
		अगर (IS_ERR(fid))
			वापस PTR_ERR(fid);

		v9fs_refresh_inode_करोtl(fid, d_inode(old_dentry));
		p9_client_clunk(fid);
	पूर्ण
	ihold(d_inode(old_dentry));
	d_instantiate(dentry, d_inode(old_dentry));

	वापस err;
पूर्ण

/**
 * v9fs_vfs_mknod_करोtl - create a special file
 * @dir: inode destination क्रम new link
 * @dentry: dentry क्रम file
 * @omode: mode क्रम creation
 * @rdev: device associated with special file
 *
 */
अटल पूर्णांक
v9fs_vfs_mknod_करोtl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		    काष्ठा dentry *dentry, umode_t omode, dev_t rdev)
अणु
	पूर्णांक err;
	kgid_t gid;
	स्थिर अचिन्हित अक्षर *name;
	umode_t mode;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid = शून्य, *dfid = शून्य;
	काष्ठा inode *inode;
	काष्ठा p9_qid qid;
	काष्ठा posix_acl *dacl = शून्य, *pacl = शून्य;

	p9_debug(P9_DEBUG_VFS, " %lu,%pd mode: %hx MAJOR: %u MINOR: %u\n",
		 dir->i_ino, dentry, omode,
		 MAJOR(rdev), MINOR(rdev));

	v9ses = v9fs_inode2v9ses(dir);
	dfid = v9fs_parent_fid(dentry);
	अगर (IS_ERR(dfid)) अणु
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		dfid = शून्य;
		जाओ error;
	पूर्ण

	gid = v9fs_get_fsgid_क्रम_create(dir);
	mode = omode;
	/* Update mode based on ACL value */
	err = v9fs_acl_mode(dir, &mode, &dacl, &pacl);
	अगर (err) अणु
		p9_debug(P9_DEBUG_VFS, "Failed to get acl values in mknod %d\n",
			 err);
		जाओ error;
	पूर्ण
	name = dentry->d_name.name;

	err = p9_client_mknod_करोtl(dfid, name, mode, rdev, gid, &qid);
	अगर (err < 0)
		जाओ error;

	v9fs_invalidate_inode_attr(dir);
	fid = p9_client_walk(dfid, 1, &name, 1);
	अगर (IS_ERR(fid)) अणु
		err = PTR_ERR(fid);
		p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n",
			 err);
		fid = शून्य;
		जाओ error;
	पूर्ण

	/* instantiate inode and assign the unखोलोed fid to the dentry */
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) अणु
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			p9_debug(P9_DEBUG_VFS, "inode creation failed %d\n",
				 err);
			जाओ error;
		पूर्ण
		v9fs_set_create_acl(inode, fid, dacl, pacl);
		v9fs_fid_add(dentry, fid);
		d_instantiate(dentry, inode);
		fid = शून्य;
		err = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Not in cached mode. No need to populate inode with stat.
		 * socket syscall वापसs a fd, so we need instantiate
		 */
		inode = v9fs_get_inode(dir->i_sb, mode, rdev);
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			जाओ error;
		पूर्ण
		v9fs_set_create_acl(inode, fid, dacl, pacl);
		d_instantiate(dentry, inode);
	पूर्ण
error:
	अगर (fid)
		p9_client_clunk(fid);
	v9fs_put_acl(dacl, pacl);
	p9_client_clunk(dfid);

	वापस err;
पूर्ण

/**
 * v9fs_vfs_get_link_करोtl - follow a symlink path
 * @dentry: dentry क्रम symlink
 * @inode: inode क्रम symlink
 * @करोne: deकाष्ठाor क्रम वापस value
 */

अटल स्थिर अक्षर *
v9fs_vfs_get_link_करोtl(काष्ठा dentry *dentry,
		       काष्ठा inode *inode,
		       काष्ठा delayed_call *करोne)
अणु
	काष्ठा p9_fid *fid;
	अक्षर *target;
	पूर्णांक retval;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	p9_debug(P9_DEBUG_VFS, "%pd\n", dentry);

	fid = v9fs_fid_lookup(dentry);
	अगर (IS_ERR(fid))
		वापस ERR_CAST(fid);
	retval = p9_client_पढ़ोlink(fid, &target);
	p9_client_clunk(fid);
	अगर (retval)
		वापस ERR_PTR(retval);
	set_delayed_call(करोne, kमुक्त_link, target);
	वापस target;
पूर्ण

पूर्णांक v9fs_refresh_inode_करोtl(काष्ठा p9_fid *fid, काष्ठा inode *inode)
अणु
	काष्ठा p9_stat_करोtl *st;
	काष्ठा v9fs_session_info *v9ses;
	अचिन्हित पूर्णांक flags;

	v9ses = v9fs_inode2v9ses(inode);
	st = p9_client_getattr_करोtl(fid, P9_STATS_ALL);
	अगर (IS_ERR(st))
		वापस PTR_ERR(st);
	/*
	 * Don't update inode अगर the file type is dअगरferent
	 */
	अगर (inode_wrong_type(inode, st->st_mode))
		जाओ out;

	/*
	 * We करोn't want to refresh inode->i_size,
	 * because we may have cached data
	 */
	flags = (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) ?
		V9FS_STAT2INODE_KEEP_ISIZE : 0;
	v9fs_stat2inode_करोtl(st, inode, flags);
out:
	kमुक्त(st);
	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations v9fs_dir_inode_operations_करोtl = अणु
	.create = v9fs_vfs_create_करोtl,
	.atomic_खोलो = v9fs_vfs_atomic_खोलो_करोtl,
	.lookup = v9fs_vfs_lookup,
	.link = v9fs_vfs_link_करोtl,
	.symlink = v9fs_vfs_symlink_करोtl,
	.unlink = v9fs_vfs_unlink,
	.सूची_गढ़ो = v9fs_vfs_सूची_गढ़ो_करोtl,
	.सूची_हटाओ = v9fs_vfs_सूची_हटाओ,
	.mknod = v9fs_vfs_mknod_करोtl,
	.नाम = v9fs_vfs_नाम,
	.getattr = v9fs_vfs_getattr_करोtl,
	.setattr = v9fs_vfs_setattr_करोtl,
	.listxattr = v9fs_listxattr,
	.get_acl = v9fs_iop_get_acl,
पूर्ण;

स्थिर काष्ठा inode_operations v9fs_file_inode_operations_करोtl = अणु
	.getattr = v9fs_vfs_getattr_करोtl,
	.setattr = v9fs_vfs_setattr_करोtl,
	.listxattr = v9fs_listxattr,
	.get_acl = v9fs_iop_get_acl,
पूर्ण;

स्थिर काष्ठा inode_operations v9fs_symlink_inode_operations_करोtl = अणु
	.get_link = v9fs_vfs_get_link_करोtl,
	.getattr = v9fs_vfs_getattr_करोtl,
	.setattr = v9fs_vfs_setattr_करोtl,
	.listxattr = v9fs_listxattr,
पूर्ण;
