<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/9p/vfs_inode.c
 *
 * This file contains vfs inode ops क्रम the 9P2000 protocol.
 *
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

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

अटल स्थिर काष्ठा inode_operations v9fs_dir_inode_operations;
अटल स्थिर काष्ठा inode_operations v9fs_dir_inode_operations_करोtu;
अटल स्थिर काष्ठा inode_operations v9fs_file_inode_operations;
अटल स्थिर काष्ठा inode_operations v9fs_symlink_inode_operations;

/**
 * unixmode2p9mode - convert unix mode bits to plan 9
 * @v9ses: v9fs session inक्रमmation
 * @mode: mode to convert
 *
 */

अटल u32 unixmode2p9mode(काष्ठा v9fs_session_info *v9ses, umode_t mode)
अणु
	पूर्णांक res;
	res = mode & 0777;
	अगर (S_ISसूची(mode))
		res |= P9_DMसूची;
	अगर (v9fs_proto_करोtu(v9ses)) अणु
		अगर (v9ses->nodev == 0) अणु
			अगर (S_ISSOCK(mode))
				res |= P9_DMSOCKET;
			अगर (S_ISFIFO(mode))
				res |= P9_DMNAMEDPIPE;
			अगर (S_ISBLK(mode))
				res |= P9_DMDEVICE;
			अगर (S_ISCHR(mode))
				res |= P9_DMDEVICE;
		पूर्ण

		अगर ((mode & S_ISUID) == S_ISUID)
			res |= P9_DMSETUID;
		अगर ((mode & S_ISGID) == S_ISGID)
			res |= P9_DMSETGID;
		अगर ((mode & S_ISVTX) == S_ISVTX)
			res |= P9_DMSETVTX;
	पूर्ण
	वापस res;
पूर्ण

/**
 * p9mode2perm- convert plan9 mode bits to unix permission bits
 * @v9ses: v9fs session inक्रमmation
 * @stat: p9_wstat from which mode need to be derived
 *
 */
अटल पूर्णांक p9mode2perm(काष्ठा v9fs_session_info *v9ses,
		       काष्ठा p9_wstat *stat)
अणु
	पूर्णांक res;
	पूर्णांक mode = stat->mode;

	res = mode & S_IALLUGO;
	अगर (v9fs_proto_करोtu(v9ses)) अणु
		अगर ((mode & P9_DMSETUID) == P9_DMSETUID)
			res |= S_ISUID;

		अगर ((mode & P9_DMSETGID) == P9_DMSETGID)
			res |= S_ISGID;

		अगर ((mode & P9_DMSETVTX) == P9_DMSETVTX)
			res |= S_ISVTX;
	पूर्ण
	वापस res;
पूर्ण

/**
 * p9mode2unixmode- convert plan9 mode bits to unix mode bits
 * @v9ses: v9fs session inक्रमmation
 * @stat: p9_wstat from which mode need to be derived
 * @rdev: major number, minor number in हाल of device files.
 *
 */
अटल umode_t p9mode2unixmode(काष्ठा v9fs_session_info *v9ses,
			       काष्ठा p9_wstat *stat, dev_t *rdev)
अणु
	पूर्णांक res;
	u32 mode = stat->mode;

	*rdev = 0;
	res = p9mode2perm(v9ses, stat);

	अगर ((mode & P9_DMसूची) == P9_DMसूची)
		res |= S_IFसूची;
	अन्यथा अगर ((mode & P9_DMSYMLINK) && (v9fs_proto_करोtu(v9ses)))
		res |= S_IFLNK;
	अन्यथा अगर ((mode & P9_DMSOCKET) && (v9fs_proto_करोtu(v9ses))
		 && (v9ses->nodev == 0))
		res |= S_IFSOCK;
	अन्यथा अगर ((mode & P9_DMNAMEDPIPE) && (v9fs_proto_करोtu(v9ses))
		 && (v9ses->nodev == 0))
		res |= S_IFIFO;
	अन्यथा अगर ((mode & P9_DMDEVICE) && (v9fs_proto_करोtu(v9ses))
		 && (v9ses->nodev == 0)) अणु
		अक्षर type = 0, ext[32];
		पूर्णांक major = -1, minor = -1;

		strlcpy(ext, stat->extension, माप(ext));
		माला_पूछो(ext, "%c %i %i", &type, &major, &minor);
		चयन (type) अणु
		हाल 'c':
			res |= S_IFCHR;
			अवरोध;
		हाल 'b':
			res |= S_IFBLK;
			अवरोध;
		शेष:
			p9_debug(P9_DEBUG_ERROR, "Unknown special type %c %s\n",
				 type, stat->extension);
		पूर्ण
		*rdev = MKDEV(major, minor);
	पूर्ण अन्यथा
		res |= S_IFREG;

	वापस res;
पूर्ण

/**
 * v9fs_uflags2omode- convert posix खोलो flags to plan 9 mode bits
 * @uflags: flags to convert
 * @extended: अगर .u extensions are active
 */

पूर्णांक v9fs_uflags2omode(पूर्णांक uflags, पूर्णांक extended)
अणु
	पूर्णांक ret;

	ret = 0;
	चयन (uflags&3) अणु
	शेष:
	हाल O_RDONLY:
		ret = P9_OREAD;
		अवरोध;

	हाल O_WRONLY:
		ret = P9_OWRITE;
		अवरोध;

	हाल O_RDWR:
		ret = P9_ORDWR;
		अवरोध;
	पूर्ण

	अगर (extended) अणु
		अगर (uflags & O_EXCL)
			ret |= P9_OEXCL;

		अगर (uflags & O_APPEND)
			ret |= P9_OAPPEND;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * v9fs_blank_wstat - helper function to setup a 9P stat काष्ठाure
 * @wstat: काष्ठाure to initialize
 *
 */

व्योम
v9fs_blank_wstat(काष्ठा p9_wstat *wstat)
अणु
	wstat->type = ~0;
	wstat->dev = ~0;
	wstat->qid.type = ~0;
	wstat->qid.version = ~0;
	*((दीर्घ दीर्घ *)&wstat->qid.path) = ~0;
	wstat->mode = ~0;
	wstat->aसमय = ~0;
	wstat->mसमय = ~0;
	wstat->length = ~0;
	wstat->name = शून्य;
	wstat->uid = शून्य;
	wstat->gid = शून्य;
	wstat->muid = शून्य;
	wstat->n_uid = INVALID_UID;
	wstat->n_gid = INVALID_GID;
	wstat->n_muid = INVALID_UID;
	wstat->extension = शून्य;
पूर्ण

/**
 * v9fs_alloc_inode - helper function to allocate an inode
 *
 */
काष्ठा inode *v9fs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा v9fs_inode *v9inode;
	v9inode = kmem_cache_alloc(v9fs_inode_cache, GFP_KERNEL);
	अगर (!v9inode)
		वापस शून्य;
#अगर_घोषित CONFIG_9P_FSCACHE
	v9inode->fscache = शून्य;
	mutex_init(&v9inode->fscache_lock);
#पूर्ण_अगर
	v9inode->ग_लिखोback_fid = शून्य;
	v9inode->cache_validity = 0;
	mutex_init(&v9inode->v_mutex);
	वापस &v9inode->vfs_inode;
पूर्ण

/**
 * v9fs_मुक्त_inode - destroy an inode
 *
 */

व्योम v9fs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(v9fs_inode_cache, V9FS_I(inode));
पूर्ण

पूर्णांक v9fs_init_inode(काष्ठा v9fs_session_info *v9ses,
		    काष्ठा inode *inode, umode_t mode, dev_t rdev)
अणु
	पूर्णांक err = 0;

	inode_init_owner(&init_user_ns,inode,  शून्य, mode);
	inode->i_blocks = 0;
	inode->i_rdev = rdev;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	inode->i_mapping->a_ops = &v9fs_addr_operations;
	inode->i_निजी = शून्य;

	चयन (mode & S_IFMT) अणु
	हाल S_IFIFO:
	हाल S_IFBLK:
	हाल S_IFCHR:
	हाल S_IFSOCK:
		अगर (v9fs_proto_करोtl(v9ses)) अणु
			inode->i_op = &v9fs_file_inode_operations_करोtl;
		पूर्ण अन्यथा अगर (v9fs_proto_करोtu(v9ses)) अणु
			inode->i_op = &v9fs_file_inode_operations;
		पूर्ण अन्यथा अणु
			p9_debug(P9_DEBUG_ERROR,
				 "special files without extended mode\n");
			err = -EINVAL;
			जाओ error;
		पूर्ण
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		अवरोध;
	हाल S_IFREG:
		अगर (v9fs_proto_करोtl(v9ses)) अणु
			inode->i_op = &v9fs_file_inode_operations_करोtl;
			अगर (v9ses->cache == CACHE_LOOSE ||
			    v9ses->cache == CACHE_FSCACHE)
				inode->i_fop =
					&v9fs_cached_file_operations_करोtl;
			अन्यथा अगर (v9ses->cache == CACHE_MMAP)
				inode->i_fop = &v9fs_mmap_file_operations_करोtl;
			अन्यथा
				inode->i_fop = &v9fs_file_operations_करोtl;
		पूर्ण अन्यथा अणु
			inode->i_op = &v9fs_file_inode_operations;
			अगर (v9ses->cache == CACHE_LOOSE ||
			    v9ses->cache == CACHE_FSCACHE)
				inode->i_fop =
					&v9fs_cached_file_operations;
			अन्यथा अगर (v9ses->cache == CACHE_MMAP)
				inode->i_fop = &v9fs_mmap_file_operations;
			अन्यथा
				inode->i_fop = &v9fs_file_operations;
		पूर्ण

		अवरोध;
	हाल S_IFLNK:
		अगर (!v9fs_proto_करोtu(v9ses) && !v9fs_proto_करोtl(v9ses)) अणु
			p9_debug(P9_DEBUG_ERROR,
				 "extended modes used with legacy protocol\n");
			err = -EINVAL;
			जाओ error;
		पूर्ण

		अगर (v9fs_proto_करोtl(v9ses))
			inode->i_op = &v9fs_symlink_inode_operations_करोtl;
		अन्यथा
			inode->i_op = &v9fs_symlink_inode_operations;

		अवरोध;
	हाल S_IFसूची:
		inc_nlink(inode);
		अगर (v9fs_proto_करोtl(v9ses))
			inode->i_op = &v9fs_dir_inode_operations_करोtl;
		अन्यथा अगर (v9fs_proto_करोtu(v9ses))
			inode->i_op = &v9fs_dir_inode_operations_करोtu;
		अन्यथा
			inode->i_op = &v9fs_dir_inode_operations;

		अगर (v9fs_proto_करोtl(v9ses))
			inode->i_fop = &v9fs_dir_operations_करोtl;
		अन्यथा
			inode->i_fop = &v9fs_dir_operations;

		अवरोध;
	शेष:
		p9_debug(P9_DEBUG_ERROR, "BAD mode 0x%hx S_IFMT 0x%x\n",
			 mode, mode & S_IFMT);
		err = -EINVAL;
		जाओ error;
	पूर्ण
error:
	वापस err;

पूर्ण

/**
 * v9fs_get_inode - helper function to setup an inode
 * @sb: superblock
 * @mode: mode to setup inode with
 *
 */

काष्ठा inode *v9fs_get_inode(काष्ठा super_block *sb, umode_t mode, dev_t rdev)
अणु
	पूर्णांक err;
	काष्ठा inode *inode;
	काष्ठा v9fs_session_info *v9ses = sb->s_fs_info;

	p9_debug(P9_DEBUG_VFS, "super block: %p mode: %ho\n", sb, mode);

	inode = new_inode(sb);
	अगर (!inode) अणु
		pr_warn("%s (%d): Problem allocating inode\n",
			__func__, task_pid_nr(current));
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	err = v9fs_init_inode(v9ses, inode, mode, rdev);
	अगर (err) अणु
		iput(inode);
		वापस ERR_PTR(err);
	पूर्ण
	वापस inode;
पूर्ण

/**
 * v9fs_clear_inode - release an inode
 * @inode: inode to release
 *
 */
व्योम v9fs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	filemap_fdataग_लिखो(&inode->i_data);

	v9fs_cache_inode_put_cookie(inode);
	/* clunk the fid stashed in ग_लिखोback_fid */
	अगर (v9inode->ग_लिखोback_fid) अणु
		p9_client_clunk(v9inode->ग_लिखोback_fid);
		v9inode->ग_लिखोback_fid = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक v9fs_test_inode(काष्ठा inode *inode, व्योम *data)
अणु
	पूर्णांक umode;
	dev_t rdev;
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);
	काष्ठा p9_wstat *st = (काष्ठा p9_wstat *)data;
	काष्ठा v9fs_session_info *v9ses = v9fs_inode2v9ses(inode);

	umode = p9mode2unixmode(v9ses, st, &rdev);
	/* करोn't match inode of dअगरferent type */
	अगर (inode_wrong_type(inode, umode))
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

अटल पूर्णांक v9fs_test_new_inode(काष्ठा inode *inode, व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक v9fs_set_inode(काष्ठा inode *inode,  व्योम *data)
अणु
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);
	काष्ठा p9_wstat *st = (काष्ठा p9_wstat *)data;

	स_नकल(&v9inode->qid, &st->qid, माप(st->qid));
	वापस 0;
पूर्ण

अटल काष्ठा inode *v9fs_qid_iget(काष्ठा super_block *sb,
				   काष्ठा p9_qid *qid,
				   काष्ठा p9_wstat *st,
				   पूर्णांक new)
अणु
	dev_t rdev;
	पूर्णांक retval;
	umode_t umode;
	अचिन्हित दीर्घ i_ino;
	काष्ठा inode *inode;
	काष्ठा v9fs_session_info *v9ses = sb->s_fs_info;
	पूर्णांक (*test)(काष्ठा inode *, व्योम *);

	अगर (new)
		test = v9fs_test_new_inode;
	अन्यथा
		test = v9fs_test_inode;

	i_ino = v9fs_qid2ino(qid);
	inode = iget5_locked(sb, i_ino, test, v9fs_set_inode, st);
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
	umode = p9mode2unixmode(v9ses, st, &rdev);
	retval = v9fs_init_inode(v9ses, inode, umode, rdev);
	अगर (retval)
		जाओ error;

	v9fs_stat2inode(st, inode, sb, 0);
	v9fs_cache_inode_get_cookie(inode);
	unlock_new_inode(inode);
	वापस inode;
error:
	iget_failed(inode);
	वापस ERR_PTR(retval);

पूर्ण

काष्ठा inode *
v9fs_inode_from_fid(काष्ठा v9fs_session_info *v9ses, काष्ठा p9_fid *fid,
		    काष्ठा super_block *sb, पूर्णांक new)
अणु
	काष्ठा p9_wstat *st;
	काष्ठा inode *inode = शून्य;

	st = p9_client_stat(fid);
	अगर (IS_ERR(st))
		वापस ERR_CAST(st);

	inode = v9fs_qid_iget(sb, &st->qid, st, new);
	p9stat_मुक्त(st);
	kमुक्त(st);
	वापस inode;
पूर्ण

/**
 * v9fs_at_to_करोtl_flags- convert Linux specअगरic AT flags to
 * plan 9 AT flag.
 * @flags: flags to convert
 */
अटल पूर्णांक v9fs_at_to_करोtl_flags(पूर्णांक flags)
अणु
	पूर्णांक rflags = 0;
	अगर (flags & AT_REMOVEसूची)
		rflags |= P9_DOTL_AT_REMOVEसूची;
	वापस rflags;
पूर्ण

/**
 * v9fs_dec_count - helper functon to drop i_nlink.
 *
 * If a directory had nlink <= 2 (including . and ..), then we should not drop
 * the link count, which indicates the underlying exported fs करोesn't मुख्यtain
 * nlink accurately. e.g.
 * - overlayfs sets nlink to 1 क्रम merged dir
 * - ext4 (with dir_nlink feature enabled) sets nlink to 1 अगर a dir has more
 *   than EXT4_LINK_MAX (65000) links.
 *
 * @inode: inode whose nlink is being dropped
 */
अटल व्योम v9fs_dec_count(काष्ठा inode *inode)
अणु
	अगर (!S_ISसूची(inode->i_mode) || inode->i_nlink > 2)
		drop_nlink(inode);
पूर्ण

/**
 * v9fs_हटाओ - helper function to हटाओ files and directories
 * @dir: directory inode that is being deleted
 * @dentry:  dentry that is being deleted
 * @flags: removing a directory
 *
 */

अटल पूर्णांक v9fs_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry, पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	पूर्णांक retval = -EOPNOTSUPP;
	काष्ठा p9_fid *v9fid, *dfid;
	काष्ठा v9fs_session_info *v9ses;

	p9_debug(P9_DEBUG_VFS, "inode: %p dentry: %p rmdir: %x\n",
		 dir, dentry, flags);

	v9ses = v9fs_inode2v9ses(dir);
	inode = d_inode(dentry);
	dfid = v9fs_parent_fid(dentry);
	अगर (IS_ERR(dfid)) अणु
		retval = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", retval);
		वापस retval;
	पूर्ण
	अगर (v9fs_proto_करोtl(v9ses))
		retval = p9_client_unlinkat(dfid, dentry->d_name.name,
					    v9fs_at_to_करोtl_flags(flags));
	p9_client_clunk(dfid);
	अगर (retval == -EOPNOTSUPP) अणु
		/* Try the one based on path */
		v9fid = v9fs_fid_clone(dentry);
		अगर (IS_ERR(v9fid))
			वापस PTR_ERR(v9fid);
		retval = p9_client_हटाओ(v9fid);
	पूर्ण
	अगर (!retval) अणु
		/*
		 * directories on unlink should have zero
		 * link count
		 */
		अगर (flags & AT_REMOVEसूची) अणु
			clear_nlink(inode);
			v9fs_dec_count(dir);
		पूर्ण अन्यथा
			v9fs_dec_count(inode);

		v9fs_invalidate_inode_attr(inode);
		v9fs_invalidate_inode_attr(dir);

		/* invalidate all fids associated with dentry */
		/* NOTE: This will not include खोलो fids */
		dentry->d_op->d_release(dentry);
	पूर्ण
	वापस retval;
पूर्ण

/**
 * v9fs_create - Create a file
 * @v9ses: session inक्रमmation
 * @dir: directory that dentry is being created in
 * @dentry:  dentry that is being created
 * @extension: 9p2000.u extension string to support devices, etc.
 * @perm: create permissions
 * @mode: खोलो mode
 *
 */
अटल काष्ठा p9_fid *
v9fs_create(काष्ठा v9fs_session_info *v9ses, काष्ठा inode *dir,
		काष्ठा dentry *dentry, अक्षर *extension, u32 perm, u8 mode)
अणु
	पूर्णांक err;
	स्थिर अचिन्हित अक्षर *name;
	काष्ठा p9_fid *dfid, *ofid = शून्य, *fid = शून्य;
	काष्ठा inode *inode;

	p9_debug(P9_DEBUG_VFS, "name %pd\n", dentry);

	err = 0;
	name = dentry->d_name.name;
	dfid = v9fs_parent_fid(dentry);
	अगर (IS_ERR(dfid)) अणु
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		वापस ERR_PTR(err);
	पूर्ण

	/* clone a fid to use क्रम creation */
	ofid = clone_fid(dfid);
	अगर (IS_ERR(ofid)) अणु
		err = PTR_ERR(ofid);
		p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n", err);
		p9_client_clunk(dfid);
		वापस ERR_PTR(err);
	पूर्ण

	err = p9_client_fcreate(ofid, name, perm, mode, extension);
	अगर (err < 0) अणु
		p9_debug(P9_DEBUG_VFS, "p9_client_fcreate failed %d\n", err);
		p9_client_clunk(dfid);
		जाओ error;
	पूर्ण

	अगर (!(perm & P9_DMLINK)) अणु
		/* now walk from the parent so we can get unखोलोed fid */
		fid = p9_client_walk(dfid, 1, &name, 1);
		अगर (IS_ERR(fid)) अणु
			err = PTR_ERR(fid);
			p9_debug(P9_DEBUG_VFS,
				   "p9_client_walk failed %d\n", err);
			fid = शून्य;
			p9_client_clunk(dfid);
			जाओ error;
		पूर्ण
		/*
		 * instantiate inode and assign the unखोलोed fid to the dentry
		 */
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
		अगर (IS_ERR(inode)) अणु
			err = PTR_ERR(inode);
			p9_debug(P9_DEBUG_VFS,
				   "inode creation failed %d\n", err);
			p9_client_clunk(dfid);
			जाओ error;
		पूर्ण
		v9fs_fid_add(dentry, fid);
		d_instantiate(dentry, inode);
	पूर्ण
	p9_client_clunk(dfid);
	वापस ofid;
error:
	अगर (ofid)
		p9_client_clunk(ofid);

	अगर (fid)
		p9_client_clunk(fid);

	वापस ERR_PTR(err);
पूर्ण

/**
 * v9fs_vfs_create - VFS hook to create a regular file
 *
 * खोलो(.., O_CREAT) is handled in v9fs_vfs_atomic_खोलो().  This is only called
 * क्रम mknod(2).
 *
 * @dir: directory inode that is being created
 * @dentry:  dentry that is being deleted
 * @mode: create permissions
 *
 */

अटल पूर्णांक
v9fs_vfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा v9fs_session_info *v9ses = v9fs_inode2v9ses(dir);
	u32 perm = unixmode2p9mode(v9ses, mode);
	काष्ठा p9_fid *fid;

	/* P9_OEXCL? */
	fid = v9fs_create(v9ses, dir, dentry, शून्य, perm, P9_ORDWR);
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);

	v9fs_invalidate_inode_attr(dir);
	p9_client_clunk(fid);

	वापस 0;
पूर्ण

/**
 * v9fs_vfs_सूची_गढ़ो - VFS सूची_गढ़ो hook to create a directory
 * @dir:  inode that is being unlinked
 * @dentry: dentry that is being unlinked
 * @mode: mode क्रम new directory
 *
 */

अटल पूर्णांक v9fs_vfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			  काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक err;
	u32 perm;
	काष्ठा p9_fid *fid;
	काष्ठा v9fs_session_info *v9ses;

	p9_debug(P9_DEBUG_VFS, "name %pd\n", dentry);
	err = 0;
	v9ses = v9fs_inode2v9ses(dir);
	perm = unixmode2p9mode(v9ses, mode | S_IFसूची);
	fid = v9fs_create(v9ses, dir, dentry, शून्य, perm, P9_OREAD);
	अगर (IS_ERR(fid)) अणु
		err = PTR_ERR(fid);
		fid = शून्य;
	पूर्ण अन्यथा अणु
		inc_nlink(dir);
		v9fs_invalidate_inode_attr(dir);
	पूर्ण

	अगर (fid)
		p9_client_clunk(fid);

	वापस err;
पूर्ण

/**
 * v9fs_vfs_lookup - VFS lookup hook to "walk" to a new inode
 * @dir:  inode that is being walked from
 * @dentry: dentry that is being walked to?
 * @flags: lookup flags (unused)
 *
 */

काष्ठा dentry *v9fs_vfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				      अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *res;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *dfid, *fid;
	काष्ठा inode *inode;
	स्थिर अचिन्हित अक्षर *name;

	p9_debug(P9_DEBUG_VFS, "dir: %p dentry: (%pd) %p flags: %x\n",
		 dir, dentry, dentry, flags);

	अगर (dentry->d_name.len > NAME_MAX)
		वापस ERR_PTR(-ENAMETOOLONG);

	v9ses = v9fs_inode2v9ses(dir);
	/* We can walk d_parent because we hold the dir->i_mutex */
	dfid = v9fs_parent_fid(dentry);
	अगर (IS_ERR(dfid))
		वापस ERR_CAST(dfid);

	/*
	 * Make sure we करोn't use a wrong inode due to parallel
	 * unlink. For cached mode create calls request क्रम new
	 * inode. But with cache disabled, lookup should करो this.
	 */
	name = dentry->d_name.name;
	fid = p9_client_walk(dfid, 1, &name, 1);
	p9_client_clunk(dfid);
	अगर (fid == ERR_PTR(-ENOENT))
		inode = शून्य;
	अन्यथा अगर (IS_ERR(fid))
		inode = ERR_CAST(fid);
	अन्यथा अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		inode = v9fs_get_inode_from_fid(v9ses, fid, dir->i_sb);
	अन्यथा
		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
	/*
	 * If we had a नाम on the server and a parallel lookup
	 * क्रम the new name, then make sure we instantiate with
	 * the new name. ie look up क्रम a/b, जबतक on server somebody
	 * moved b under k and client parallely did a lookup क्रम
	 * k/b.
	 */
	res = d_splice_alias(inode, dentry);
	अगर (!IS_ERR(fid)) अणु
		अगर (!res)
			v9fs_fid_add(dentry, fid);
		अन्यथा अगर (!IS_ERR(res))
			v9fs_fid_add(res, fid);
		अन्यथा
			p9_client_clunk(fid);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक
v9fs_vfs_atomic_खोलो(काष्ठा inode *dir, काष्ठा dentry *dentry,
		     काष्ठा file *file, अचिन्हित flags, umode_t mode)
अणु
	पूर्णांक err;
	u32 perm;
	काष्ठा v9fs_inode *v9inode;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid, *inode_fid;
	काष्ठा dentry *res = शून्य;
	काष्ठा inode *inode;

	अगर (d_in_lookup(dentry)) अणु
		res = v9fs_vfs_lookup(dir, dentry, 0);
		अगर (IS_ERR(res))
			वापस PTR_ERR(res);

		अगर (res)
			dentry = res;
	पूर्ण

	/* Only creates */
	अगर (!(flags & O_CREAT) || d_really_is_positive(dentry))
		वापस finish_no_खोलो(file, res);

	err = 0;

	v9ses = v9fs_inode2v9ses(dir);
	perm = unixmode2p9mode(v9ses, mode);
	fid = v9fs_create(v9ses, dir, dentry, शून्य, perm,
				v9fs_uflags2omode(flags,
						v9fs_proto_करोtu(v9ses)));
	अगर (IS_ERR(fid)) अणु
		err = PTR_ERR(fid);
		fid = शून्य;
		जाओ error;
	पूर्ण

	v9fs_invalidate_inode_attr(dir);
	inode = d_inode(dentry);
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
			जाओ error;
		पूर्ण
		v9inode->ग_लिखोback_fid = (व्योम *) inode_fid;
	पूर्ण
	mutex_unlock(&v9inode->v_mutex);
	err = finish_खोलो(file, dentry, generic_file_खोलो);
	अगर (err)
		जाओ error;

	file->निजी_data = fid;
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		v9fs_cache_inode_set_cookie(d_inode(dentry), file);
	v9fs_खोलो_fid_add(inode, fid);

	file->f_mode |= FMODE_CREATED;
out:
	dput(res);
	वापस err;

error:
	अगर (fid)
		p9_client_clunk(fid);
	जाओ out;
पूर्ण

/**
 * v9fs_vfs_unlink - VFS unlink hook to delete an inode
 * @i:  inode that is being unlinked
 * @d: dentry that is being unlinked
 *
 */

पूर्णांक v9fs_vfs_unlink(काष्ठा inode *i, काष्ठा dentry *d)
अणु
	वापस v9fs_हटाओ(i, d, 0);
पूर्ण

/**
 * v9fs_vfs_सूची_हटाओ - VFS unlink hook to delete a directory
 * @i:  inode that is being unlinked
 * @d: dentry that is being unlinked
 *
 */

पूर्णांक v9fs_vfs_सूची_हटाओ(काष्ठा inode *i, काष्ठा dentry *d)
अणु
	वापस v9fs_हटाओ(i, d, AT_REMOVEसूची);
पूर्ण

/**
 * v9fs_vfs_नाम - VFS hook to नाम an inode
 * @old_dir:  old dir inode
 * @old_dentry: old dentry
 * @new_dir: new dir inode
 * @new_dentry: new dentry
 *
 */

पूर्णांक
v9fs_vfs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक retval;
	काष्ठा inode *old_inode;
	काष्ठा inode *new_inode;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *oldfid, *dfid;
	काष्ठा p9_fid *olddirfid;
	काष्ठा p9_fid *newdirfid;
	काष्ठा p9_wstat wstat;

	अगर (flags)
		वापस -EINVAL;

	p9_debug(P9_DEBUG_VFS, "\n");
	retval = 0;
	old_inode = d_inode(old_dentry);
	new_inode = d_inode(new_dentry);
	v9ses = v9fs_inode2v9ses(old_inode);
	oldfid = v9fs_fid_lookup(old_dentry);
	अगर (IS_ERR(oldfid))
		वापस PTR_ERR(oldfid);

	dfid = v9fs_parent_fid(old_dentry);
	olddirfid = clone_fid(dfid);
	अगर (dfid && !IS_ERR(dfid))
		p9_client_clunk(dfid);

	अगर (IS_ERR(olddirfid)) अणु
		retval = PTR_ERR(olddirfid);
		जाओ करोne;
	पूर्ण

	dfid = v9fs_parent_fid(new_dentry);
	newdirfid = clone_fid(dfid);
	p9_client_clunk(dfid);

	अगर (IS_ERR(newdirfid)) अणु
		retval = PTR_ERR(newdirfid);
		जाओ clunk_olddir;
	पूर्ण

	करोwn_ग_लिखो(&v9ses->नाम_sem);
	अगर (v9fs_proto_करोtl(v9ses)) अणु
		retval = p9_client_नामat(olddirfid, old_dentry->d_name.name,
					    newdirfid, new_dentry->d_name.name);
		अगर (retval == -EOPNOTSUPP)
			retval = p9_client_नाम(oldfid, newdirfid,
						  new_dentry->d_name.name);
		अगर (retval != -EOPNOTSUPP)
			जाओ clunk_newdir;
	पूर्ण
	अगर (old_dentry->d_parent != new_dentry->d_parent) अणु
		/*
		 * 9P .u can only handle file नाम in the same directory
		 */

		p9_debug(P9_DEBUG_ERROR, "old dir and new dir are different\n");
		retval = -EXDEV;
		जाओ clunk_newdir;
	पूर्ण
	v9fs_blank_wstat(&wstat);
	wstat.muid = v9ses->uname;
	wstat.name = new_dentry->d_name.name;
	retval = p9_client_wstat(oldfid, &wstat);

clunk_newdir:
	अगर (!retval) अणु
		अगर (new_inode) अणु
			अगर (S_ISसूची(new_inode->i_mode))
				clear_nlink(new_inode);
			अन्यथा
				v9fs_dec_count(new_inode);
		पूर्ण
		अगर (S_ISसूची(old_inode->i_mode)) अणु
			अगर (!new_inode)
				inc_nlink(new_dir);
			v9fs_dec_count(old_dir);
		पूर्ण
		v9fs_invalidate_inode_attr(old_inode);
		v9fs_invalidate_inode_attr(old_dir);
		v9fs_invalidate_inode_attr(new_dir);

		/* successful नाम */
		d_move(old_dentry, new_dentry);
	पूर्ण
	up_ग_लिखो(&v9ses->नाम_sem);
	p9_client_clunk(newdirfid);

clunk_olddir:
	p9_client_clunk(olddirfid);

करोne:
	p9_client_clunk(oldfid);
	वापस retval;
पूर्ण

/**
 * v9fs_vfs_getattr - retrieve file metadata
 * @path: Object to query
 * @stat: metadata काष्ठाure to populate
 * @request_mask: Mask of STATX_xxx flags indicating the caller's पूर्णांकerests
 * @flags: AT_STATX_xxx setting
 *
 */

अटल पूर्णांक
v9fs_vfs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid;
	काष्ठा p9_wstat *st;

	p9_debug(P9_DEBUG_VFS, "dentry: %p\n", dentry);
	v9ses = v9fs_dentry2v9ses(dentry);
	अगर (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) अणु
		generic_fillattr(&init_user_ns, d_inode(dentry), stat);
		वापस 0;
	पूर्ण
	fid = v9fs_fid_lookup(dentry);
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);

	st = p9_client_stat(fid);
	p9_client_clunk(fid);
	अगर (IS_ERR(st))
		वापस PTR_ERR(st);

	v9fs_stat2inode(st, d_inode(dentry), dentry->d_sb, 0);
	generic_fillattr(&init_user_ns, d_inode(dentry), stat);

	p9stat_मुक्त(st);
	kमुक्त(st);
	वापस 0;
पूर्ण

/**
 * v9fs_vfs_setattr - set file metadata
 * @dentry: file whose metadata to set
 * @iattr: metadata assignment काष्ठाure
 *
 */

अटल पूर्णांक v9fs_vfs_setattr(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry, काष्ठा iattr *iattr)
अणु
	पूर्णांक retval, use_dentry = 0;
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid = शून्य;
	काष्ठा p9_wstat wstat;

	p9_debug(P9_DEBUG_VFS, "\n");
	retval = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (retval)
		वापस retval;

	retval = -EPERM;
	v9ses = v9fs_dentry2v9ses(dentry);
	अगर (iattr->ia_valid & ATTR_खाता) अणु
		fid = iattr->ia_file->निजी_data;
		WARN_ON(!fid);
	पूर्ण
	अगर (!fid) अणु
		fid = v9fs_fid_lookup(dentry);
		use_dentry = 1;
	पूर्ण
	अगर(IS_ERR(fid))
		वापस PTR_ERR(fid);

	v9fs_blank_wstat(&wstat);
	अगर (iattr->ia_valid & ATTR_MODE)
		wstat.mode = unixmode2p9mode(v9ses, iattr->ia_mode);

	अगर (iattr->ia_valid & ATTR_MTIME)
		wstat.mसमय = iattr->ia_mसमय.tv_sec;

	अगर (iattr->ia_valid & ATTR_ATIME)
		wstat.aसमय = iattr->ia_aसमय.tv_sec;

	अगर (iattr->ia_valid & ATTR_SIZE)
		wstat.length = iattr->ia_size;

	अगर (v9fs_proto_करोtu(v9ses)) अणु
		अगर (iattr->ia_valid & ATTR_UID)
			wstat.n_uid = iattr->ia_uid;

		अगर (iattr->ia_valid & ATTR_GID)
			wstat.n_gid = iattr->ia_gid;
	पूर्ण

	/* Write all dirty data */
	अगर (d_is_reg(dentry))
		filemap_ग_लिखो_and_रुको(d_inode(dentry)->i_mapping);

	retval = p9_client_wstat(fid, &wstat);

	अगर (use_dentry)
		p9_client_clunk(fid);

	अगर (retval < 0)
		वापस retval;

	अगर ((iattr->ia_valid & ATTR_SIZE) &&
	    iattr->ia_size != i_size_पढ़ो(d_inode(dentry)))
		truncate_setsize(d_inode(dentry), iattr->ia_size);

	v9fs_invalidate_inode_attr(d_inode(dentry));

	setattr_copy(&init_user_ns, d_inode(dentry), iattr);
	mark_inode_dirty(d_inode(dentry));
	वापस 0;
पूर्ण

/**
 * v9fs_stat2inode - populate an inode काष्ठाure with mistat info
 * @stat: Plan 9 metadata (mistat) काष्ठाure
 * @inode: inode to populate
 * @sb: superblock of fileप्रणाली
 * @flags: control flags (e.g. V9FS_STAT2INODE_KEEP_ISIZE)
 *
 */

व्योम
v9fs_stat2inode(काष्ठा p9_wstat *stat, काष्ठा inode *inode,
		 काष्ठा super_block *sb, अचिन्हित पूर्णांक flags)
अणु
	umode_t mode;
	काष्ठा v9fs_session_info *v9ses = sb->s_fs_info;
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);

	set_nlink(inode, 1);

	inode->i_aसमय.tv_sec = stat->aसमय;
	inode->i_mसमय.tv_sec = stat->mसमय;
	inode->i_स_समय.tv_sec = stat->mसमय;

	inode->i_uid = v9ses->dfltuid;
	inode->i_gid = v9ses->dfltgid;

	अगर (v9fs_proto_करोtu(v9ses)) अणु
		inode->i_uid = stat->n_uid;
		inode->i_gid = stat->n_gid;
	पूर्ण
	अगर ((S_ISREG(inode->i_mode)) || (S_ISसूची(inode->i_mode))) अणु
		अगर (v9fs_proto_करोtu(v9ses)) अणु
			अचिन्हित पूर्णांक i_nlink;
			/*
			 * Hadlink support got added later to the .u extension.
			 * So there can be a server out there that करोesn't
			 * support this even with .u extension. That would
			 * just leave us with stat->extension being an empty
			 * string, though.
			 */
			/* HARDLINKCOUNT %u */
			अगर (माला_पूछो(stat->extension,
				   " HARDLINKCOUNT %u", &i_nlink) == 1)
				set_nlink(inode, i_nlink);
		पूर्ण
	पूर्ण
	mode = p9mode2perm(v9ses, stat);
	mode |= inode->i_mode & ~S_IALLUGO;
	inode->i_mode = mode;

	अगर (!(flags & V9FS_STAT2INODE_KEEP_ISIZE))
		v9fs_i_size_ग_लिखो(inode, stat->length);
	/* not real number of blocks, but 512 byte ones ... */
	inode->i_blocks = (stat->length + 512 - 1) >> 9;
	v9inode->cache_validity &= ~V9FS_INO_INVALID_ATTR;
पूर्ण

/**
 * v9fs_qid2ino - convert qid पूर्णांकo inode number
 * @qid: qid to hash
 *
 * BUG: potential क्रम inode number collisions?
 */

ino_t v9fs_qid2ino(काष्ठा p9_qid *qid)
अणु
	u64 path = qid->path + 2;
	ino_t i = 0;

	अगर (माप(ino_t) == माप(path))
		स_नकल(&i, &path, माप(ino_t));
	अन्यथा
		i = (ino_t) (path ^ (path >> 32));

	वापस i;
पूर्ण

/**
 * v9fs_vfs_get_link - follow a symlink path
 * @dentry: dentry क्रम symlink
 * @inode: inode क्रम symlink
 * @करोne: delayed call क्रम when we are करोne with the वापस value
 */

अटल स्थिर अक्षर *v9fs_vfs_get_link(काष्ठा dentry *dentry,
				     काष्ठा inode *inode,
				     काष्ठा delayed_call *करोne)
अणु
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा p9_fid *fid;
	काष्ठा p9_wstat *st;
	अक्षर *res;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	v9ses = v9fs_dentry2v9ses(dentry);
	fid = v9fs_fid_lookup(dentry);
	p9_debug(P9_DEBUG_VFS, "%pd\n", dentry);

	अगर (IS_ERR(fid))
		वापस ERR_CAST(fid);

	अगर (!v9fs_proto_करोtu(v9ses))
		वापस ERR_PTR(-EBADF);

	st = p9_client_stat(fid);
	p9_client_clunk(fid);
	अगर (IS_ERR(st))
		वापस ERR_CAST(st);

	अगर (!(st->mode & P9_DMSYMLINK)) अणु
		p9stat_मुक्त(st);
		kमुक्त(st);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	res = st->extension;
	st->extension = शून्य;
	अगर (म_माप(res) >= PATH_MAX)
		res[PATH_MAX - 1] = '\0';

	p9stat_मुक्त(st);
	kमुक्त(st);
	set_delayed_call(करोne, kमुक्त_link, res);
	वापस res;
पूर्ण

/**
 * v9fs_vfs_mkspecial - create a special file
 * @dir: inode to create special file in
 * @dentry: dentry to create
 * @perm: mode to create special file
 * @extension: 9p2000.u क्रमmat extension string representing special file
 *
 */

अटल पूर्णांक v9fs_vfs_mkspecial(काष्ठा inode *dir, काष्ठा dentry *dentry,
	u32 perm, स्थिर अक्षर *extension)
अणु
	काष्ठा p9_fid *fid;
	काष्ठा v9fs_session_info *v9ses;

	v9ses = v9fs_inode2v9ses(dir);
	अगर (!v9fs_proto_करोtu(v9ses)) अणु
		p9_debug(P9_DEBUG_ERROR, "not extended\n");
		वापस -EPERM;
	पूर्ण

	fid = v9fs_create(v9ses, dir, dentry, (अक्षर *) extension, perm,
								P9_OREAD);
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);

	v9fs_invalidate_inode_attr(dir);
	p9_client_clunk(fid);
	वापस 0;
पूर्ण

/**
 * v9fs_vfs_symlink - helper function to create symlinks
 * @dir: directory inode containing symlink
 * @dentry: dentry क्रम symlink
 * @symname: symlink data
 *
 * See Also: 9P2000.u RFC क्रम more inक्रमmation
 *
 */

अटल पूर्णांक
v9fs_vfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		 काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	p9_debug(P9_DEBUG_VFS, " %lu,%pd,%s\n",
		 dir->i_ino, dentry, symname);

	वापस v9fs_vfs_mkspecial(dir, dentry, P9_DMSYMLINK, symname);
पूर्ण

#घोषणा U32_MAX_DIGITS 10

/**
 * v9fs_vfs_link - create a hardlink
 * @old_dentry: dentry क्रम file to link to
 * @dir: inode destination क्रम new link
 * @dentry: dentry क्रम link
 *
 */

अटल पूर्णांक
v9fs_vfs_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
	      काष्ठा dentry *dentry)
अणु
	पूर्णांक retval;
	अक्षर name[1 + U32_MAX_DIGITS + 2]; /* sign + number + \न + \0 */
	काष्ठा p9_fid *oldfid;

	p9_debug(P9_DEBUG_VFS, " %lu,%pd,%pd\n",
		 dir->i_ino, dentry, old_dentry);

	oldfid = v9fs_fid_clone(old_dentry);
	अगर (IS_ERR(oldfid))
		वापस PTR_ERR(oldfid);

	प्र_लिखो(name, "%d\n", oldfid->fid);
	retval = v9fs_vfs_mkspecial(dir, dentry, P9_DMLINK, name);
	अगर (!retval) अणु
		v9fs_refresh_inode(oldfid, d_inode(old_dentry));
		v9fs_invalidate_inode_attr(dir);
	पूर्ण
	p9_client_clunk(oldfid);
	वापस retval;
पूर्ण

/**
 * v9fs_vfs_mknod - create a special file
 * @dir: inode destination क्रम new link
 * @dentry: dentry क्रम file
 * @mode: mode क्रम creation
 * @rdev: device associated with special file
 *
 */

अटल पूर्णांक
v9fs_vfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	       काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा v9fs_session_info *v9ses = v9fs_inode2v9ses(dir);
	पूर्णांक retval;
	अक्षर name[2 + U32_MAX_DIGITS + 1 + U32_MAX_DIGITS + 1];
	u32 perm;

	p9_debug(P9_DEBUG_VFS, " %lu,%pd mode: %hx MAJOR: %u MINOR: %u\n",
		 dir->i_ino, dentry, mode,
		 MAJOR(rdev), MINOR(rdev));

	/* build extension */
	अगर (S_ISBLK(mode))
		प्र_लिखो(name, "b %u %u", MAJOR(rdev), MINOR(rdev));
	अन्यथा अगर (S_ISCHR(mode))
		प्र_लिखो(name, "c %u %u", MAJOR(rdev), MINOR(rdev));
	अन्यथा
		*name = 0;

	perm = unixmode2p9mode(v9ses, mode);
	retval = v9fs_vfs_mkspecial(dir, dentry, perm, name);

	वापस retval;
पूर्ण

पूर्णांक v9fs_refresh_inode(काष्ठा p9_fid *fid, काष्ठा inode *inode)
अणु
	पूर्णांक umode;
	dev_t rdev;
	काष्ठा p9_wstat *st;
	काष्ठा v9fs_session_info *v9ses;
	अचिन्हित पूर्णांक flags;

	v9ses = v9fs_inode2v9ses(inode);
	st = p9_client_stat(fid);
	अगर (IS_ERR(st))
		वापस PTR_ERR(st);
	/*
	 * Don't update inode अगर the file type is dअगरferent
	 */
	umode = p9mode2unixmode(v9ses, st, &rdev);
	अगर (inode_wrong_type(inode, umode))
		जाओ out;

	/*
	 * We करोn't want to refresh inode->i_size,
	 * because we may have cached data
	 */
	flags = (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) ?
		V9FS_STAT2INODE_KEEP_ISIZE : 0;
	v9fs_stat2inode(st, inode, inode->i_sb, flags);
out:
	p9stat_मुक्त(st);
	kमुक्त(st);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations v9fs_dir_inode_operations_करोtu = अणु
	.create = v9fs_vfs_create,
	.lookup = v9fs_vfs_lookup,
	.atomic_खोलो = v9fs_vfs_atomic_खोलो,
	.symlink = v9fs_vfs_symlink,
	.link = v9fs_vfs_link,
	.unlink = v9fs_vfs_unlink,
	.सूची_गढ़ो = v9fs_vfs_सूची_गढ़ो,
	.सूची_हटाओ = v9fs_vfs_सूची_हटाओ,
	.mknod = v9fs_vfs_mknod,
	.नाम = v9fs_vfs_नाम,
	.getattr = v9fs_vfs_getattr,
	.setattr = v9fs_vfs_setattr,
पूर्ण;

अटल स्थिर काष्ठा inode_operations v9fs_dir_inode_operations = अणु
	.create = v9fs_vfs_create,
	.lookup = v9fs_vfs_lookup,
	.atomic_खोलो = v9fs_vfs_atomic_खोलो,
	.unlink = v9fs_vfs_unlink,
	.सूची_गढ़ो = v9fs_vfs_सूची_गढ़ो,
	.सूची_हटाओ = v9fs_vfs_सूची_हटाओ,
	.mknod = v9fs_vfs_mknod,
	.नाम = v9fs_vfs_नाम,
	.getattr = v9fs_vfs_getattr,
	.setattr = v9fs_vfs_setattr,
पूर्ण;

अटल स्थिर काष्ठा inode_operations v9fs_file_inode_operations = अणु
	.getattr = v9fs_vfs_getattr,
	.setattr = v9fs_vfs_setattr,
पूर्ण;

अटल स्थिर काष्ठा inode_operations v9fs_symlink_inode_operations = अणु
	.get_link = v9fs_vfs_get_link,
	.getattr = v9fs_vfs_getattr,
	.setattr = v9fs_vfs_setattr,
पूर्ण;

