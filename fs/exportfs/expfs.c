<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Neil Brown 2002
 * Copyright (C) Christoph Hellwig 2007
 *
 * This file contains the code mapping from inodes to NFS file handles,
 * and क्रम mapping back from file handles to dentries.
 *
 * For details on why we करो all the strange and hairy things in here
 * take a look at Documentation/fileप्रणालीs/nfs/exporting.rst.
 */
#समावेश <linux/exportfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>

#घोषणा dprपूर्णांकk(fmt, args...) करोअणुपूर्णजबतक(0)


अटल पूर्णांक get_name(स्थिर काष्ठा path *path, अक्षर *name, काष्ठा dentry *child);


अटल पूर्णांक exportfs_get_name(काष्ठा vfsmount *mnt, काष्ठा dentry *dir,
		अक्षर *name, काष्ठा dentry *child)
अणु
	स्थिर काष्ठा export_operations *nop = dir->d_sb->s_export_op;
	काष्ठा path path = अणु.mnt = mnt, .dentry = dirपूर्ण;

	अगर (nop->get_name)
		वापस nop->get_name(dir, name, child);
	अन्यथा
		वापस get_name(&path, name, child);
पूर्ण

/*
 * Check अगर the dentry or any of it's aliases is acceptable.
 */
अटल काष्ठा dentry *
find_acceptable_alias(काष्ठा dentry *result,
		पूर्णांक (*acceptable)(व्योम *context, काष्ठा dentry *dentry),
		व्योम *context)
अणु
	काष्ठा dentry *dentry, *toput = शून्य;
	काष्ठा inode *inode;

	अगर (acceptable(context, result))
		वापस result;

	inode = result->d_inode;
	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(dentry, &inode->i_dentry, d_u.d_alias) अणु
		dget(dentry);
		spin_unlock(&inode->i_lock);
		अगर (toput)
			dput(toput);
		अगर (dentry != result && acceptable(context, dentry)) अणु
			dput(result);
			वापस dentry;
		पूर्ण
		spin_lock(&inode->i_lock);
		toput = dentry;
	पूर्ण
	spin_unlock(&inode->i_lock);

	अगर (toput)
		dput(toput);
	वापस शून्य;
पूर्ण

अटल bool dentry_connected(काष्ठा dentry *dentry)
अणु
	dget(dentry);
	जबतक (dentry->d_flags & DCACHE_DISCONNECTED) अणु
		काष्ठा dentry *parent = dget_parent(dentry);

		dput(dentry);
		अगर (dentry == parent) अणु
			dput(parent);
			वापस false;
		पूर्ण
		dentry = parent;
	पूर्ण
	dput(dentry);
	वापस true;
पूर्ण

अटल व्योम clear_disconnected(काष्ठा dentry *dentry)
अणु
	dget(dentry);
	जबतक (dentry->d_flags & DCACHE_DISCONNECTED) अणु
		काष्ठा dentry *parent = dget_parent(dentry);

		WARN_ON_ONCE(IS_ROOT(dentry));

		spin_lock(&dentry->d_lock);
		dentry->d_flags &= ~DCACHE_DISCONNECTED;
		spin_unlock(&dentry->d_lock);

		dput(dentry);
		dentry = parent;
	पूर्ण
	dput(dentry);
पूर्ण

/*
 * Reconnect a directory dentry with its parent.
 *
 * This can वापस a dentry, or शून्य, or an error.
 *
 * In the first हाल the वापसed dentry is the parent of the given
 * dentry, and may itself need to be reconnected to its parent.
 *
 * In the शून्य हाल, a concurrent VFS operation has either नामd or
 * हटाओd this directory.  The concurrent operation has reconnected our
 * dentry, so we no दीर्घer need to.
 */
अटल काष्ठा dentry *reconnect_one(काष्ठा vfsmount *mnt,
		काष्ठा dentry *dentry, अक्षर *nbuf)
अणु
	काष्ठा dentry *parent;
	काष्ठा dentry *पंचांगp;
	पूर्णांक err;

	parent = ERR_PTR(-EACCES);
	inode_lock(dentry->d_inode);
	अगर (mnt->mnt_sb->s_export_op->get_parent)
		parent = mnt->mnt_sb->s_export_op->get_parent(dentry);
	inode_unlock(dentry->d_inode);

	अगर (IS_ERR(parent)) अणु
		dprपूर्णांकk("%s: get_parent of %ld failed, err %d\n",
			__func__, dentry->d_inode->i_ino, PTR_ERR(parent));
		वापस parent;
	पूर्ण

	dprपूर्णांकk("%s: find name of %lu in %lu\n", __func__,
		dentry->d_inode->i_ino, parent->d_inode->i_ino);
	err = exportfs_get_name(mnt, parent, nbuf, dentry);
	अगर (err == -ENOENT)
		जाओ out_reconnected;
	अगर (err)
		जाओ out_err;
	dprपूर्णांकk("%s: found name: %s\n", __func__, nbuf);
	पंचांगp = lookup_one_len_unlocked(nbuf, parent, म_माप(nbuf));
	अगर (IS_ERR(पंचांगp)) अणु
		dprपूर्णांकk("%s: lookup failed: %d\n", __func__, PTR_ERR(पंचांगp));
		err = PTR_ERR(पंचांगp);
		जाओ out_err;
	पूर्ण
	अगर (पंचांगp != dentry) अणु
		/*
		 * Somebody has नामd it since exportfs_get_name();
		 * great, since it could've only been नामd अगर it
		 * got looked up and thus connected, and it would
		 * reमुख्य connected afterwards.  We are करोne.
		 */
		dput(पंचांगp);
		जाओ out_reconnected;
	पूर्ण
	dput(पंचांगp);
	अगर (IS_ROOT(dentry)) अणु
		err = -ESTALE;
		जाओ out_err;
	पूर्ण
	वापस parent;

out_err:
	dput(parent);
	वापस ERR_PTR(err);
out_reconnected:
	dput(parent);
	/*
	 * Someone must have नामd our entry पूर्णांकo another parent, in
	 * which हाल it has been reconnected by the नाम.
	 *
	 * Or someone हटाओd it entirely, in which हाल filehandle
	 * lookup will succeed but the directory is now IS_DEAD and
	 * subsequent operations on it will fail.
	 *
	 * Alternatively, maybe there was no race at all, and the
	 * fileप्रणाली is just corrupt and gave us a parent that करोesn't
	 * actually contain any entry poपूर्णांकing to this inode.  So,
	 * द्विगुन check that this worked and वापस -ESTALE अगर not:
	 */
	अगर (!dentry_connected(dentry))
		वापस ERR_PTR(-ESTALE);
	वापस शून्य;
पूर्ण

/*
 * Make sure target_dir is fully connected to the dentry tree.
 *
 * On successful वापस, DCACHE_DISCONNECTED will be cleared on
 * target_dir, and target_dir->d_parent->...->d_parent will reach the
 * root of the fileप्रणाली.
 *
 * Whenever DCACHE_DISCONNECTED is unset, target_dir is fully connected.
 * But the converse is not true: target_dir may have DCACHE_DISCONNECTED
 * set but alपढ़ोy be connected.  In that हाल we'll verअगरy the
 * connection to root and then clear the flag.
 *
 * Note that target_dir could be हटाओd by a concurrent operation.  In
 * that हाल reconnect_path may still succeed with target_dir fully
 * connected, but further operations using the filehandle will fail when
 * necessary (due to S_DEAD being set on the directory).
 */
अटल पूर्णांक
reconnect_path(काष्ठा vfsmount *mnt, काष्ठा dentry *target_dir, अक्षर *nbuf)
अणु
	काष्ठा dentry *dentry, *parent;

	dentry = dget(target_dir);

	जबतक (dentry->d_flags & DCACHE_DISCONNECTED) अणु
		BUG_ON(dentry == mnt->mnt_sb->s_root);

		अगर (IS_ROOT(dentry))
			parent = reconnect_one(mnt, dentry, nbuf);
		अन्यथा
			parent = dget_parent(dentry);

		अगर (!parent)
			अवरोध;
		dput(dentry);
		अगर (IS_ERR(parent))
			वापस PTR_ERR(parent);
		dentry = parent;
	पूर्ण
	dput(dentry);
	clear_disconnected(target_dir);
	वापस 0;
पूर्ण

काष्ठा getdents_callback अणु
	काष्ठा dir_context ctx;
	अक्षर *name;		/* name that was found. It alपढ़ोy poपूर्णांकs to a
				   buffer NAME_MAX+1 is size */
	u64 ino;		/* the inum we are looking क्रम */
	पूर्णांक found;		/* inode matched? */
	पूर्णांक sequence;		/* sequence counter */
पूर्ण;

/*
 * A rather strange filldir function to capture
 * the name matching the specअगरied inode number.
 */
अटल पूर्णांक filldir_one(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक len,
			loff_t pos, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा getdents_callback *buf =
		container_of(ctx, काष्ठा getdents_callback, ctx);
	पूर्णांक result = 0;

	buf->sequence++;
	अगर (buf->ino == ino && len <= NAME_MAX) अणु
		स_नकल(buf->name, name, len);
		buf->name[len] = '\0';
		buf->found = 1;
		result = -1;
	पूर्ण
	वापस result;
पूर्ण

/**
 * get_name - शेष export_operations->get_name function
 * @path:   the directory in which to find a name
 * @name:   a poपूर्णांकer to a %NAME_MAX+1 अक्षर buffer to store the name
 * @child:  the dentry क्रम the child directory.
 *
 * calls सूची_पढ़ो on the parent until it finds an entry with
 * the same inode number as the child, and वापसs that.
 */
अटल पूर्णांक get_name(स्थिर काष्ठा path *path, अक्षर *name, काष्ठा dentry *child)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा inode *dir = path->dentry->d_inode;
	पूर्णांक error;
	काष्ठा file *file;
	काष्ठा kstat stat;
	काष्ठा path child_path = अणु
		.mnt = path->mnt,
		.dentry = child,
	पूर्ण;
	काष्ठा getdents_callback buffer = अणु
		.ctx.actor = filldir_one,
		.name = name,
	पूर्ण;

	error = -ENOTसूची;
	अगर (!dir || !S_ISसूची(dir->i_mode))
		जाओ out;
	error = -EINVAL;
	अगर (!dir->i_fop)
		जाओ out;
	/*
	 * inode->i_ino is अचिन्हित दीर्घ, kstat->ino is u64, so the
	 * क्रमmer would be insufficient on 32-bit hosts when the
	 * fileप्रणाली supports 64-bit inode numbers.  So we need to
	 * actually call ->getattr, not just पढ़ो i_ino:
	 */
	error = vfs_getattr_nosec(&child_path, &stat,
				  STATX_INO, AT_STATX_SYNC_AS_STAT);
	अगर (error)
		वापस error;
	buffer.ino = stat.ino;
	/*
	 * Open the directory ...
	 */
	file = dentry_खोलो(path, O_RDONLY, cred);
	error = PTR_ERR(file);
	अगर (IS_ERR(file))
		जाओ out;

	error = -EINVAL;
	अगर (!file->f_op->iterate && !file->f_op->iterate_shared)
		जाओ out_बंद;

	buffer.sequence = 0;
	जबतक (1) अणु
		पूर्णांक old_seq = buffer.sequence;

		error = iterate_dir(file, &buffer.ctx);
		अगर (buffer.found) अणु
			error = 0;
			अवरोध;
		पूर्ण

		अगर (error < 0)
			अवरोध;

		error = -ENOENT;
		अगर (old_seq == buffer.sequence)
			अवरोध;
	पूर्ण

out_बंद:
	fput(file);
out:
	वापस error;
पूर्ण

/**
 * export_encode_fh - शेष export_operations->encode_fh function
 * @inode:   the object to encode
 * @fid:     where to store the file handle fragment
 * @max_len: maximum length to store there
 * @parent:  parent directory inode, अगर wanted
 *
 * This शेष encode_fh function assumes that the 32 inode number
 * is suitable क्रम locating an inode, and that the generation number
 * can be used to check that it is still valid.  It places them in the
 * filehandle fragment where export_decode_fh expects to find them.
 */
अटल पूर्णांक export_encode_fh(काष्ठा inode *inode, काष्ठा fid *fid,
		पूर्णांक *max_len, काष्ठा inode *parent)
अणु
	पूर्णांक len = *max_len;
	पूर्णांक type = खाताID_INO32_GEN;

	अगर (parent && (len < 4)) अणु
		*max_len = 4;
		वापस खाताID_INVALID;
	पूर्ण अन्यथा अगर (len < 2) अणु
		*max_len = 2;
		वापस खाताID_INVALID;
	पूर्ण

	len = 2;
	fid->i32.ino = inode->i_ino;
	fid->i32.gen = inode->i_generation;
	अगर (parent) अणु
		fid->i32.parent_ino = parent->i_ino;
		fid->i32.parent_gen = parent->i_generation;
		len = 4;
		type = खाताID_INO32_GEN_PARENT;
	पूर्ण
	*max_len = len;
	वापस type;
पूर्ण

पूर्णांक exportfs_encode_inode_fh(काष्ठा inode *inode, काष्ठा fid *fid,
			     पूर्णांक *max_len, काष्ठा inode *parent)
अणु
	स्थिर काष्ठा export_operations *nop = inode->i_sb->s_export_op;

	अगर (nop && nop->encode_fh)
		वापस nop->encode_fh(inode, fid->raw, max_len, parent);

	वापस export_encode_fh(inode, fid, max_len, parent);
पूर्ण
EXPORT_SYMBOL_GPL(exportfs_encode_inode_fh);

पूर्णांक exportfs_encode_fh(काष्ठा dentry *dentry, काष्ठा fid *fid, पूर्णांक *max_len,
		पूर्णांक connectable)
अणु
	पूर्णांक error;
	काष्ठा dentry *p = शून्य;
	काष्ठा inode *inode = dentry->d_inode, *parent = शून्य;

	अगर (connectable && !S_ISसूची(inode->i_mode)) अणु
		p = dget_parent(dentry);
		/*
		 * note that जबतक p might've ceased to be our parent alपढ़ोy,
		 * it's still pinned by and still positive.
		 */
		parent = p->d_inode;
	पूर्ण

	error = exportfs_encode_inode_fh(inode, fid, max_len, parent);
	dput(p);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(exportfs_encode_fh);

काष्ठा dentry *
exportfs_decode_fh_raw(काष्ठा vfsmount *mnt, काष्ठा fid *fid, पूर्णांक fh_len,
		       पूर्णांक fileid_type,
		       पूर्णांक (*acceptable)(व्योम *, काष्ठा dentry *),
		       व्योम *context)
अणु
	स्थिर काष्ठा export_operations *nop = mnt->mnt_sb->s_export_op;
	काष्ठा dentry *result, *alias;
	अक्षर nbuf[NAME_MAX+1];
	पूर्णांक err;

	/*
	 * Try to get any dentry क्रम the given file handle from the fileप्रणाली.
	 */
	अगर (!nop || !nop->fh_to_dentry)
		वापस ERR_PTR(-ESTALE);
	result = nop->fh_to_dentry(mnt->mnt_sb, fid, fh_len, fileid_type);
	अगर (IS_ERR_OR_शून्य(result))
		वापस result;

	/*
	 * If no acceptance criteria was specअगरied by caller, a disconnected
	 * dentry is also accepatable. Callers may use this mode to query अगर
	 * file handle is stale or to get a reference to an inode without
	 * risking the high overhead caused by directory reconnect.
	 */
	अगर (!acceptable)
		वापस result;

	अगर (d_is_dir(result)) अणु
		/*
		 * This request is क्रम a directory.
		 *
		 * On the positive side there is only one dentry क्रम each
		 * directory inode.  On the negative side this implies that we
		 * to ensure our dentry is connected all the way up to the
		 * fileप्रणाली root.
		 */
		अगर (result->d_flags & DCACHE_DISCONNECTED) अणु
			err = reconnect_path(mnt, result, nbuf);
			अगर (err)
				जाओ err_result;
		पूर्ण

		अगर (!acceptable(context, result)) अणु
			err = -EACCES;
			जाओ err_result;
		पूर्ण

		वापस result;
	पूर्ण अन्यथा अणु
		/*
		 * It's not a directory.  Lअगरe is a little more complicated.
		 */
		काष्ठा dentry *target_dir, *nresult;

		/*
		 * See अगर either the dentry we just got from the fileप्रणाली
		 * or any alias क्रम it is acceptable.  This is always true
		 * अगर this fileप्रणाली is exported without the subtreecheck
		 * option.  If the fileप्रणाली is exported with the subtree
		 * check option there's a fair chance we need to look at
		 * the parent directory in the file handle and make sure
		 * it's connected to the fileप्रणाली root.
		 */
		alias = find_acceptable_alias(result, acceptable, context);
		अगर (alias)
			वापस alias;

		/*
		 * Try to extract a dentry क्रम the parent directory from the
		 * file handle.  If this fails we'll have to give up.
		 */
		err = -ESTALE;
		अगर (!nop->fh_to_parent)
			जाओ err_result;

		target_dir = nop->fh_to_parent(mnt->mnt_sb, fid,
				fh_len, fileid_type);
		अगर (!target_dir)
			जाओ err_result;
		err = PTR_ERR(target_dir);
		अगर (IS_ERR(target_dir))
			जाओ err_result;

		/*
		 * And as usual we need to make sure the parent directory is
		 * connected to the fileप्रणाली root.  The VFS really करोesn't
		 * like disconnected directories..
		 */
		err = reconnect_path(mnt, target_dir, nbuf);
		अगर (err) अणु
			dput(target_dir);
			जाओ err_result;
		पूर्ण

		/*
		 * Now that we've got both a well-connected parent and a
		 * dentry क्रम the inode we're after, make sure that our
		 * inode is actually connected to the parent.
		 */
		err = exportfs_get_name(mnt, target_dir, nbuf, result);
		अगर (err) अणु
			dput(target_dir);
			जाओ err_result;
		पूर्ण

		inode_lock(target_dir->d_inode);
		nresult = lookup_one_len(nbuf, target_dir, म_माप(nbuf));
		अगर (!IS_ERR(nresult)) अणु
			अगर (unlikely(nresult->d_inode != result->d_inode)) अणु
				dput(nresult);
				nresult = ERR_PTR(-ESTALE);
			पूर्ण
		पूर्ण
		inode_unlock(target_dir->d_inode);
		/*
		 * At this poपूर्णांक we are करोne with the parent, but it's pinned
		 * by the child dentry anyway.
		 */
		dput(target_dir);

		अगर (IS_ERR(nresult)) अणु
			err = PTR_ERR(nresult);
			जाओ err_result;
		पूर्ण
		dput(result);
		result = nresult;

		/*
		 * And finally make sure the dentry is actually acceptable
		 * to NFSD.
		 */
		alias = find_acceptable_alias(result, acceptable, context);
		अगर (!alias) अणु
			err = -EACCES;
			जाओ err_result;
		पूर्ण

		वापस alias;
	पूर्ण

 err_result:
	dput(result);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(exportfs_decode_fh_raw);

काष्ठा dentry *exportfs_decode_fh(काष्ठा vfsmount *mnt, काष्ठा fid *fid,
				  पूर्णांक fh_len, पूर्णांक fileid_type,
				  पूर्णांक (*acceptable)(व्योम *, काष्ठा dentry *),
				  व्योम *context)
अणु
	काष्ठा dentry *ret;

	ret = exportfs_decode_fh_raw(mnt, fid, fh_len, fileid_type,
				     acceptable, context);
	अगर (IS_ERR_OR_शून्य(ret)) अणु
		अगर (ret == ERR_PTR(-ENOMEM))
			वापस ret;
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(exportfs_decode_fh);

MODULE_LICENSE("GPL");
