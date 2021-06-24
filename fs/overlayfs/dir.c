<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2011 Novell Inc.
 */

#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/xattr.h>
#समावेश <linux/security.h>
#समावेश <linux/cred.h>
#समावेश <linux/module.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/atomic.h>
#समावेश <linux/ratelimit.h>
#समावेश "overlayfs.h"

अटल अचिन्हित लघु ovl_redirect_max = 256;
module_param_named(redirect_max, ovl_redirect_max, uलघु, 0644);
MODULE_PARM_DESC(redirect_max,
		 "Maximum length of absolute redirect xattr value");

अटल पूर्णांक ovl_set_redirect(काष्ठा dentry *dentry, bool samedir);

पूर्णांक ovl_cleanup(काष्ठा inode *wdir, काष्ठा dentry *wdentry)
अणु
	पूर्णांक err;

	dget(wdentry);
	अगर (d_is_dir(wdentry))
		err = ovl_करो_सूची_हटाओ(wdir, wdentry);
	अन्यथा
		err = ovl_करो_unlink(wdir, wdentry);
	dput(wdentry);

	अगर (err) अणु
		pr_err("cleanup of '%pd2' failed (%i)\n",
		       wdentry, err);
	पूर्ण

	वापस err;
पूर्ण

काष्ठा dentry *ovl_lookup_temp(काष्ठा dentry *workdir)
अणु
	काष्ठा dentry *temp;
	अक्षर name[20];
	अटल atomic_t temp_id = ATOMIC_INIT(0);

	/* counter is allowed to wrap, since temp dentries are ephemeral */
	snम_लिखो(name, माप(name), "#%x", atomic_inc_वापस(&temp_id));

	temp = lookup_one_len(name, workdir, म_माप(name));
	अगर (!IS_ERR(temp) && temp->d_inode) अणु
		pr_err("workdir/%s already exists\n", name);
		dput(temp);
		temp = ERR_PTR(-EIO);
	पूर्ण

	वापस temp;
पूर्ण

/* caller holds i_mutex on workdir */
अटल काष्ठा dentry *ovl_whiteout(काष्ठा ovl_fs *ofs)
अणु
	पूर्णांक err;
	काष्ठा dentry *whiteout;
	काष्ठा dentry *workdir = ofs->workdir;
	काष्ठा inode *wdir = workdir->d_inode;

	अगर (!ofs->whiteout) अणु
		whiteout = ovl_lookup_temp(workdir);
		अगर (IS_ERR(whiteout))
			जाओ out;

		err = ovl_करो_whiteout(wdir, whiteout);
		अगर (err) अणु
			dput(whiteout);
			whiteout = ERR_PTR(err);
			जाओ out;
		पूर्ण
		ofs->whiteout = whiteout;
	पूर्ण

	अगर (ofs->share_whiteout) अणु
		whiteout = ovl_lookup_temp(workdir);
		अगर (IS_ERR(whiteout))
			जाओ out;

		err = ovl_करो_link(ofs->whiteout, wdir, whiteout);
		अगर (!err)
			जाओ out;

		अगर (err != -EMLINK) अणु
			pr_warn("Failed to link whiteout - disabling whiteout inode sharing(nlink=%u, err=%i)\n",
				ofs->whiteout->d_inode->i_nlink, err);
			ofs->share_whiteout = false;
		पूर्ण
		dput(whiteout);
	पूर्ण
	whiteout = ofs->whiteout;
	ofs->whiteout = शून्य;
out:
	वापस whiteout;
पूर्ण

/* Caller must hold i_mutex on both workdir and dir */
पूर्णांक ovl_cleanup_and_whiteout(काष्ठा ovl_fs *ofs, काष्ठा inode *dir,
			     काष्ठा dentry *dentry)
अणु
	काष्ठा inode *wdir = ofs->workdir->d_inode;
	काष्ठा dentry *whiteout;
	पूर्णांक err;
	पूर्णांक flags = 0;

	whiteout = ovl_whiteout(ofs);
	err = PTR_ERR(whiteout);
	अगर (IS_ERR(whiteout))
		वापस err;

	अगर (d_is_dir(dentry))
		flags = RENAME_EXCHANGE;

	err = ovl_करो_नाम(wdir, whiteout, dir, dentry, flags);
	अगर (err)
		जाओ समाप्त_whiteout;
	अगर (flags)
		ovl_cleanup(wdir, dentry);

out:
	dput(whiteout);
	वापस err;

समाप्त_whiteout:
	ovl_cleanup(wdir, whiteout);
	जाओ out;
पूर्ण

अटल पूर्णांक ovl_सूची_गढ़ो_real(काष्ठा inode *dir, काष्ठा dentry **newdentry,
			  umode_t mode)
अणु
	पूर्णांक err;
	काष्ठा dentry *d, *dentry = *newdentry;

	err = ovl_करो_सूची_गढ़ो(dir, dentry, mode);
	अगर (err)
		वापस err;

	अगर (likely(!d_unhashed(dentry)))
		वापस 0;

	/*
	 * vfs_सूची_गढ़ो() may succeed and leave the dentry passed
	 * to it unhashed and negative. If that happens, try to
	 * lookup a new hashed and positive dentry.
	 */
	d = lookup_one_len(dentry->d_name.name, dentry->d_parent,
			   dentry->d_name.len);
	अगर (IS_ERR(d)) अणु
		pr_warn("failed lookup after mkdir (%pd2, err=%i).\n",
			dentry, err);
		वापस PTR_ERR(d);
	पूर्ण
	dput(dentry);
	*newdentry = d;

	वापस 0;
पूर्ण

काष्ठा dentry *ovl_create_real(काष्ठा inode *dir, काष्ठा dentry *newdentry,
			       काष्ठा ovl_cattr *attr)
अणु
	पूर्णांक err;

	अगर (IS_ERR(newdentry))
		वापस newdentry;

	err = -ESTALE;
	अगर (newdentry->d_inode)
		जाओ out;

	अगर (attr->hardlink) अणु
		err = ovl_करो_link(attr->hardlink, dir, newdentry);
	पूर्ण अन्यथा अणु
		चयन (attr->mode & S_IFMT) अणु
		हाल S_IFREG:
			err = ovl_करो_create(dir, newdentry, attr->mode);
			अवरोध;

		हाल S_IFसूची:
			/* सूची_गढ़ो is special... */
			err =  ovl_सूची_गढ़ो_real(dir, &newdentry, attr->mode);
			अवरोध;

		हाल S_IFCHR:
		हाल S_IFBLK:
		हाल S_IFIFO:
		हाल S_IFSOCK:
			err = ovl_करो_mknod(dir, newdentry, attr->mode,
					   attr->rdev);
			अवरोध;

		हाल S_IFLNK:
			err = ovl_करो_symlink(dir, newdentry, attr->link);
			अवरोध;

		शेष:
			err = -EPERM;
		पूर्ण
	पूर्ण
	अगर (!err && WARN_ON(!newdentry->d_inode)) अणु
		/*
		 * Not quite sure अगर non-instantiated dentry is legal or not.
		 * VFS करोesn't seem to care so check and warn here.
		 */
		err = -EIO;
	पूर्ण
out:
	अगर (err) अणु
		dput(newdentry);
		वापस ERR_PTR(err);
	पूर्ण
	वापस newdentry;
पूर्ण

काष्ठा dentry *ovl_create_temp(काष्ठा dentry *workdir, काष्ठा ovl_cattr *attr)
अणु
	वापस ovl_create_real(d_inode(workdir), ovl_lookup_temp(workdir),
			       attr);
पूर्ण

अटल पूर्णांक ovl_set_opaque_xerr(काष्ठा dentry *dentry, काष्ठा dentry *upper,
			       पूर्णांक xerr)
अणु
	पूर्णांक err;

	err = ovl_check_setxattr(dentry, upper, OVL_XATTR_OPAQUE, "y", 1, xerr);
	अगर (!err)
		ovl_dentry_set_opaque(dentry);

	वापस err;
पूर्ण

अटल पूर्णांक ovl_set_opaque(काष्ठा dentry *dentry, काष्ठा dentry *upperdentry)
अणु
	/*
	 * Fail with -EIO when trying to create opaque dir and upper करोesn't
	 * support xattrs. ovl_नाम() calls ovl_set_opaque_xerr(-EXDEV) to
	 * वापस a specअगरic error क्रम noxattr हाल.
	 */
	वापस ovl_set_opaque_xerr(dentry, upperdentry, -EIO);
पूर्ण

/*
 * Common operations required to be करोne after creation of file on upper.
 * If @hardlink is false, then @inode is a pre-allocated inode, we may or
 * may not use to instantiate the new dentry.
 */
अटल पूर्णांक ovl_instantiate(काष्ठा dentry *dentry, काष्ठा inode *inode,
			   काष्ठा dentry *newdentry, bool hardlink)
अणु
	काष्ठा ovl_inode_params oip = अणु
		.upperdentry = newdentry,
		.newinode = inode,
	पूर्ण;

	ovl_dir_modअगरied(dentry->d_parent, false);
	ovl_dentry_set_upper_alias(dentry);
	ovl_dentry_update_reval(dentry, newdentry,
			DCACHE_OP_REVALIDATE | DCACHE_OP_WEAK_REVALIDATE);

	अगर (!hardlink) अणु
		/*
		 * ovl_obtain_alias() can be called after ovl_create_real()
		 * and beक्रमe we get here, so we may get an inode from cache
		 * with the same real upperdentry that is not the inode we
		 * pre-allocated.  In this हाल we will use the cached inode
		 * to instantiate the new dentry.
		 *
		 * XXX: अगर we ever use ovl_obtain_alias() to decode directory
		 * file handles, need to use ovl_get_inode_locked() and
		 * d_instantiate_new() here to prevent from creating two
		 * hashed directory inode aliases.
		 */
		inode = ovl_get_inode(dentry->d_sb, &oip);
		अगर (IS_ERR(inode))
			वापस PTR_ERR(inode);
		अगर (inode == oip.newinode)
			ovl_set_flag(OVL_UPPERDATA, inode);
	पूर्ण अन्यथा अणु
		WARN_ON(ovl_inode_real(inode) != d_inode(newdentry));
		dput(newdentry);
		inc_nlink(inode);
	पूर्ण

	d_instantiate(dentry, inode);
	अगर (inode != oip.newinode) अणु
		pr_warn_ratelimited("newly created inode found in cache (%pd2)\n",
				    dentry);
	पूर्ण

	/* Force lookup of new upper hardlink to find its lower */
	अगर (hardlink)
		d_drop(dentry);

	वापस 0;
पूर्ण

अटल bool ovl_type_merge(काष्ठा dentry *dentry)
अणु
	वापस OVL_TYPE_MERGE(ovl_path_type(dentry));
पूर्ण

अटल bool ovl_type_origin(काष्ठा dentry *dentry)
अणु
	वापस OVL_TYPE_ORIGIN(ovl_path_type(dentry));
पूर्ण

अटल पूर्णांक ovl_create_upper(काष्ठा dentry *dentry, काष्ठा inode *inode,
			    काष्ठा ovl_cattr *attr)
अणु
	काष्ठा dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	काष्ठा inode *udir = upperdir->d_inode;
	काष्ठा dentry *newdentry;
	पूर्णांक err;

	अगर (!attr->hardlink && !IS_POSIXACL(udir))
		attr->mode &= ~current_umask();

	inode_lock_nested(udir, I_MUTEX_PARENT);
	newdentry = ovl_create_real(udir,
				    lookup_one_len(dentry->d_name.name,
						   upperdir,
						   dentry->d_name.len),
				    attr);
	err = PTR_ERR(newdentry);
	अगर (IS_ERR(newdentry))
		जाओ out_unlock;

	अगर (ovl_type_merge(dentry->d_parent) && d_is_dir(newdentry)) अणु
		/* Setting opaque here is just an optimization, allow to fail */
		ovl_set_opaque(dentry, newdentry);
	पूर्ण

	err = ovl_instantiate(dentry, inode, newdentry, !!attr->hardlink);
	अगर (err)
		जाओ out_cleanup;
out_unlock:
	inode_unlock(udir);
	वापस err;

out_cleanup:
	ovl_cleanup(udir, newdentry);
	dput(newdentry);
	जाओ out_unlock;
पूर्ण

अटल काष्ठा dentry *ovl_clear_empty(काष्ठा dentry *dentry,
				      काष्ठा list_head *list)
अणु
	काष्ठा dentry *workdir = ovl_workdir(dentry);
	काष्ठा inode *wdir = workdir->d_inode;
	काष्ठा dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	काष्ठा inode *udir = upperdir->d_inode;
	काष्ठा path upperpath;
	काष्ठा dentry *upper;
	काष्ठा dentry *opaquedir;
	काष्ठा kstat stat;
	पूर्णांक err;

	अगर (WARN_ON(!workdir))
		वापस ERR_PTR(-EROFS);

	err = ovl_lock_नाम_workdir(workdir, upperdir);
	अगर (err)
		जाओ out;

	ovl_path_upper(dentry, &upperpath);
	err = vfs_getattr(&upperpath, &stat,
			  STATX_BASIC_STATS, AT_STATX_SYNC_AS_STAT);
	अगर (err)
		जाओ out_unlock;

	err = -ESTALE;
	अगर (!S_ISसूची(stat.mode))
		जाओ out_unlock;
	upper = upperpath.dentry;
	अगर (upper->d_parent->d_inode != udir)
		जाओ out_unlock;

	opaquedir = ovl_create_temp(workdir, OVL_CATTR(stat.mode));
	err = PTR_ERR(opaquedir);
	अगर (IS_ERR(opaquedir))
		जाओ out_unlock;

	err = ovl_copy_xattr(dentry->d_sb, upper, opaquedir);
	अगर (err)
		जाओ out_cleanup;

	err = ovl_set_opaque(dentry, opaquedir);
	अगर (err)
		जाओ out_cleanup;

	inode_lock(opaquedir->d_inode);
	err = ovl_set_attr(opaquedir, &stat);
	inode_unlock(opaquedir->d_inode);
	अगर (err)
		जाओ out_cleanup;

	err = ovl_करो_नाम(wdir, opaquedir, udir, upper, RENAME_EXCHANGE);
	अगर (err)
		जाओ out_cleanup;

	ovl_cleanup_whiteouts(upper, list);
	ovl_cleanup(wdir, upper);
	unlock_नाम(workdir, upperdir);

	/* dentry's upper doesn't match now, get rid of it */
	d_drop(dentry);

	वापस opaquedir;

out_cleanup:
	ovl_cleanup(wdir, opaquedir);
	dput(opaquedir);
out_unlock:
	unlock_नाम(workdir, upperdir);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक ovl_set_upper_acl(काष्ठा dentry *upperdentry, स्थिर अक्षर *name,
			     स्थिर काष्ठा posix_acl *acl)
अणु
	व्योम *buffer;
	माप_प्रकार size;
	पूर्णांक err;

	अगर (!IS_ENABLED(CONFIG_FS_POSIX_ACL) || !acl)
		वापस 0;

	size = posix_acl_xattr_size(acl->a_count);
	buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	err = posix_acl_to_xattr(&init_user_ns, acl, buffer, size);
	अगर (err < 0)
		जाओ out_मुक्त;

	err = vfs_setxattr(&init_user_ns, upperdentry, name, buffer, size, XATTR_CREATE);
out_मुक्त:
	kमुक्त(buffer);
	वापस err;
पूर्ण

अटल पूर्णांक ovl_create_over_whiteout(काष्ठा dentry *dentry, काष्ठा inode *inode,
				    काष्ठा ovl_cattr *cattr)
अणु
	काष्ठा dentry *workdir = ovl_workdir(dentry);
	काष्ठा inode *wdir = workdir->d_inode;
	काष्ठा dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	काष्ठा inode *udir = upperdir->d_inode;
	काष्ठा dentry *upper;
	काष्ठा dentry *newdentry;
	पूर्णांक err;
	काष्ठा posix_acl *acl, *शेष_acl;
	bool hardlink = !!cattr->hardlink;

	अगर (WARN_ON(!workdir))
		वापस -EROFS;

	अगर (!hardlink) अणु
		err = posix_acl_create(dentry->d_parent->d_inode,
				       &cattr->mode, &शेष_acl, &acl);
		अगर (err)
			वापस err;
	पूर्ण

	err = ovl_lock_नाम_workdir(workdir, upperdir);
	अगर (err)
		जाओ out;

	upper = lookup_one_len(dentry->d_name.name, upperdir,
			       dentry->d_name.len);
	err = PTR_ERR(upper);
	अगर (IS_ERR(upper))
		जाओ out_unlock;

	err = -ESTALE;
	अगर (d_is_negative(upper) || !IS_WHITEOUT(d_inode(upper)))
		जाओ out_dput;

	newdentry = ovl_create_temp(workdir, cattr);
	err = PTR_ERR(newdentry);
	अगर (IS_ERR(newdentry))
		जाओ out_dput;

	/*
	 * mode could have been mutilated due to umask (e.g. sgid directory)
	 */
	अगर (!hardlink &&
	    !S_ISLNK(cattr->mode) &&
	    newdentry->d_inode->i_mode != cattr->mode) अणु
		काष्ठा iattr attr = अणु
			.ia_valid = ATTR_MODE,
			.ia_mode = cattr->mode,
		पूर्ण;
		inode_lock(newdentry->d_inode);
		err = notअगरy_change(&init_user_ns, newdentry, &attr, शून्य);
		inode_unlock(newdentry->d_inode);
		अगर (err)
			जाओ out_cleanup;
	पूर्ण
	अगर (!hardlink) अणु
		err = ovl_set_upper_acl(newdentry, XATTR_NAME_POSIX_ACL_ACCESS,
					acl);
		अगर (err)
			जाओ out_cleanup;

		err = ovl_set_upper_acl(newdentry, XATTR_NAME_POSIX_ACL_DEFAULT,
					शेष_acl);
		अगर (err)
			जाओ out_cleanup;
	पूर्ण

	अगर (!hardlink && S_ISसूची(cattr->mode)) अणु
		err = ovl_set_opaque(dentry, newdentry);
		अगर (err)
			जाओ out_cleanup;

		err = ovl_करो_नाम(wdir, newdentry, udir, upper,
				    RENAME_EXCHANGE);
		अगर (err)
			जाओ out_cleanup;

		ovl_cleanup(wdir, upper);
	पूर्ण अन्यथा अणु
		err = ovl_करो_नाम(wdir, newdentry, udir, upper, 0);
		अगर (err)
			जाओ out_cleanup;
	पूर्ण
	err = ovl_instantiate(dentry, inode, newdentry, hardlink);
	अगर (err)
		जाओ out_cleanup;
out_dput:
	dput(upper);
out_unlock:
	unlock_नाम(workdir, upperdir);
out:
	अगर (!hardlink) अणु
		posix_acl_release(acl);
		posix_acl_release(शेष_acl);
	पूर्ण
	वापस err;

out_cleanup:
	ovl_cleanup(wdir, newdentry);
	dput(newdentry);
	जाओ out_dput;
पूर्ण

अटल पूर्णांक ovl_create_or_link(काष्ठा dentry *dentry, काष्ठा inode *inode,
			      काष्ठा ovl_cattr *attr, bool origin)
अणु
	पूर्णांक err;
	स्थिर काष्ठा cred *old_cred;
	काष्ठा cred *override_cred;
	काष्ठा dentry *parent = dentry->d_parent;

	err = ovl_copy_up(parent);
	अगर (err)
		वापस err;

	old_cred = ovl_override_creds(dentry->d_sb);

	/*
	 * When linking a file with copy up origin पूर्णांकo a new parent, mark the
	 * new parent dir "impure".
	 */
	अगर (origin) अणु
		err = ovl_set_impure(parent, ovl_dentry_upper(parent));
		अगर (err)
			जाओ out_revert_creds;
	पूर्ण

	err = -ENOMEM;
	override_cred = prepare_creds();
	अगर (override_cred) अणु
		override_cred->fsuid = inode->i_uid;
		override_cred->fsgid = inode->i_gid;
		अगर (!attr->hardlink) अणु
			err = security_dentry_create_files_as(dentry,
					attr->mode, &dentry->d_name, old_cred,
					override_cred);
			अगर (err) अणु
				put_cred(override_cred);
				जाओ out_revert_creds;
			पूर्ण
		पूर्ण
		put_cred(override_creds(override_cred));
		put_cred(override_cred);

		अगर (!ovl_dentry_is_whiteout(dentry))
			err = ovl_create_upper(dentry, inode, attr);
		अन्यथा
			err = ovl_create_over_whiteout(dentry, inode, attr);
	पूर्ण
out_revert_creds:
	revert_creds(old_cred);
	वापस err;
पूर्ण

अटल पूर्णांक ovl_create_object(काष्ठा dentry *dentry, पूर्णांक mode, dev_t rdev,
			     स्थिर अक्षर *link)
अणु
	पूर्णांक err;
	काष्ठा inode *inode;
	काष्ठा ovl_cattr attr = अणु
		.rdev = rdev,
		.link = link,
	पूर्ण;

	err = ovl_want_ग_लिखो(dentry);
	अगर (err)
		जाओ out;

	/* Pपुनः_स्मृतिate inode to be used by ovl_get_inode() */
	err = -ENOMEM;
	inode = ovl_new_inode(dentry->d_sb, mode, rdev);
	अगर (!inode)
		जाओ out_drop_ग_लिखो;

	spin_lock(&inode->i_lock);
	inode->i_state |= I_CREATING;
	spin_unlock(&inode->i_lock);

	inode_init_owner(&init_user_ns, inode, dentry->d_parent->d_inode, mode);
	attr.mode = inode->i_mode;

	err = ovl_create_or_link(dentry, inode, &attr, false);
	/* Did we end up using the pपुनः_स्मृतिated inode? */
	अगर (inode != d_inode(dentry))
		iput(inode);

out_drop_ग_लिखो:
	ovl_drop_ग_लिखो(dentry);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ovl_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस ovl_create_object(dentry, (mode & 07777) | S_IFREG, 0, शून्य);
पूर्ण

अटल पूर्णांक ovl_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode)
अणु
	वापस ovl_create_object(dentry, (mode & 07777) | S_IFसूची, 0, शून्य);
पूर्ण

अटल पूर्णांक ovl_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	/* Don't allow creation of "whiteout" on overlay */
	अगर (S_ISCHR(mode) && rdev == WHITEOUT_DEV)
		वापस -EPERM;

	वापस ovl_create_object(dentry, mode, rdev, शून्य);
पूर्ण

अटल पूर्णांक ovl_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, स्थिर अक्षर *link)
अणु
	वापस ovl_create_object(dentry, S_IFLNK, 0, link);
पूर्ण

अटल पूर्णांक ovl_set_link_redirect(काष्ठा dentry *dentry)
अणु
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक err;

	old_cred = ovl_override_creds(dentry->d_sb);
	err = ovl_set_redirect(dentry, false);
	revert_creds(old_cred);

	वापस err;
पूर्ण

अटल पूर्णांक ovl_link(काष्ठा dentry *old, काष्ठा inode *newdir,
		    काष्ठा dentry *new)
अणु
	पूर्णांक err;
	काष्ठा inode *inode;

	err = ovl_want_ग_लिखो(old);
	अगर (err)
		जाओ out;

	err = ovl_copy_up(old);
	अगर (err)
		जाओ out_drop_ग_लिखो;

	err = ovl_copy_up(new->d_parent);
	अगर (err)
		जाओ out_drop_ग_लिखो;

	अगर (ovl_is_metacopy_dentry(old)) अणु
		err = ovl_set_link_redirect(old);
		अगर (err)
			जाओ out_drop_ग_लिखो;
	पूर्ण

	err = ovl_nlink_start(old);
	अगर (err)
		जाओ out_drop_ग_लिखो;

	inode = d_inode(old);
	ihold(inode);

	err = ovl_create_or_link(new, inode,
			&(काष्ठा ovl_cattr) अणु.hardlink = ovl_dentry_upper(old)पूर्ण,
			ovl_type_origin(old));
	अगर (err)
		iput(inode);

	ovl_nlink_end(old);
out_drop_ग_लिखो:
	ovl_drop_ग_लिखो(old);
out:
	वापस err;
पूर्ण

अटल bool ovl_matches_upper(काष्ठा dentry *dentry, काष्ठा dentry *upper)
अणु
	वापस d_inode(ovl_dentry_upper(dentry)) == d_inode(upper);
पूर्ण

अटल पूर्णांक ovl_हटाओ_and_whiteout(काष्ठा dentry *dentry,
				   काष्ठा list_head *list)
अणु
	काष्ठा ovl_fs *ofs = OVL_FS(dentry->d_sb);
	काष्ठा dentry *workdir = ovl_workdir(dentry);
	काष्ठा dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	काष्ठा dentry *upper;
	काष्ठा dentry *opaquedir = शून्य;
	पूर्णांक err;

	अगर (WARN_ON(!workdir))
		वापस -EROFS;

	अगर (!list_empty(list)) अणु
		opaquedir = ovl_clear_empty(dentry, list);
		err = PTR_ERR(opaquedir);
		अगर (IS_ERR(opaquedir))
			जाओ out;
	पूर्ण

	err = ovl_lock_नाम_workdir(workdir, upperdir);
	अगर (err)
		जाओ out_dput;

	upper = lookup_one_len(dentry->d_name.name, upperdir,
			       dentry->d_name.len);
	err = PTR_ERR(upper);
	अगर (IS_ERR(upper))
		जाओ out_unlock;

	err = -ESTALE;
	अगर ((opaquedir && upper != opaquedir) ||
	    (!opaquedir && ovl_dentry_upper(dentry) &&
	     !ovl_matches_upper(dentry, upper))) अणु
		जाओ out_dput_upper;
	पूर्ण

	err = ovl_cleanup_and_whiteout(ofs, d_inode(upperdir), upper);
	अगर (err)
		जाओ out_d_drop;

	ovl_dir_modअगरied(dentry->d_parent, true);
out_d_drop:
	d_drop(dentry);
out_dput_upper:
	dput(upper);
out_unlock:
	unlock_नाम(workdir, upperdir);
out_dput:
	dput(opaquedir);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ovl_हटाओ_upper(काष्ठा dentry *dentry, bool is_dir,
			    काष्ठा list_head *list)
अणु
	काष्ठा dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	काष्ठा inode *dir = upperdir->d_inode;
	काष्ठा dentry *upper;
	काष्ठा dentry *opaquedir = शून्य;
	पूर्णांक err;

	अगर (!list_empty(list)) अणु
		opaquedir = ovl_clear_empty(dentry, list);
		err = PTR_ERR(opaquedir);
		अगर (IS_ERR(opaquedir))
			जाओ out;
	पूर्ण

	inode_lock_nested(dir, I_MUTEX_PARENT);
	upper = lookup_one_len(dentry->d_name.name, upperdir,
			       dentry->d_name.len);
	err = PTR_ERR(upper);
	अगर (IS_ERR(upper))
		जाओ out_unlock;

	err = -ESTALE;
	अगर ((opaquedir && upper != opaquedir) ||
	    (!opaquedir && !ovl_matches_upper(dentry, upper)))
		जाओ out_dput_upper;

	अगर (is_dir)
		err = vfs_सूची_हटाओ(&init_user_ns, dir, upper);
	अन्यथा
		err = vfs_unlink(&init_user_ns, dir, upper, शून्य);
	ovl_dir_modअगरied(dentry->d_parent, ovl_type_origin(dentry));

	/*
	 * Keeping this dentry hashed would mean having to release
	 * upperpath/lowerpath, which could only be करोne अगर we are the
	 * sole user of this dentry.  Too tricky...  Just unhash क्रम
	 * now.
	 */
	अगर (!err)
		d_drop(dentry);
out_dput_upper:
	dput(upper);
out_unlock:
	inode_unlock(dir);
	dput(opaquedir);
out:
	वापस err;
पूर्ण

अटल bool ovl_pure_upper(काष्ठा dentry *dentry)
अणु
	वापस !ovl_dentry_lower(dentry) &&
	       !ovl_test_flag(OVL_WHITEOUTS, d_inode(dentry));
पूर्ण

अटल व्योम ovl_drop_nlink(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा dentry *alias;

	/* Try to find another, hashed alias */
	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(alias, &inode->i_dentry, d_u.d_alias) अणु
		अगर (alias != dentry && !d_unhashed(alias))
			अवरोध;
	पूर्ण
	spin_unlock(&inode->i_lock);

	/*
	 * Changes to underlying layers may cause i_nlink to lose sync with
	 * reality.  In this हाल prevent the link count from going to zero
	 * prematurely.
	 */
	अगर (inode->i_nlink > !!alias)
		drop_nlink(inode);
पूर्ण

अटल पूर्णांक ovl_करो_हटाओ(काष्ठा dentry *dentry, bool is_dir)
अणु
	पूर्णांक err;
	स्थिर काष्ठा cred *old_cred;
	काष्ठा dentry *upperdentry;
	bool lower_positive = ovl_lower_positive(dentry);
	LIST_HEAD(list);

	/* No need to clean pure upper हटाओd by vfs_सूची_हटाओ() */
	अगर (is_dir && (lower_positive || !ovl_pure_upper(dentry))) अणु
		err = ovl_check_empty_dir(dentry, &list);
		अगर (err)
			जाओ out;
	पूर्ण

	err = ovl_want_ग_लिखो(dentry);
	अगर (err)
		जाओ out;

	err = ovl_copy_up(dentry->d_parent);
	अगर (err)
		जाओ out_drop_ग_लिखो;

	err = ovl_nlink_start(dentry);
	अगर (err)
		जाओ out_drop_ग_लिखो;

	old_cred = ovl_override_creds(dentry->d_sb);
	अगर (!lower_positive)
		err = ovl_हटाओ_upper(dentry, is_dir, &list);
	अन्यथा
		err = ovl_हटाओ_and_whiteout(dentry, &list);
	revert_creds(old_cred);
	अगर (!err) अणु
		अगर (is_dir)
			clear_nlink(dentry->d_inode);
		अन्यथा
			ovl_drop_nlink(dentry);
	पूर्ण
	ovl_nlink_end(dentry);

	/*
	 * Copy स_समय
	 *
	 * Note: we fail to update स_समय अगर there was no copy-up, only a
	 * whiteout
	 */
	upperdentry = ovl_dentry_upper(dentry);
	अगर (upperdentry)
		ovl_copyattr(d_inode(upperdentry), d_inode(dentry));

out_drop_ग_लिखो:
	ovl_drop_ग_लिखो(dentry);
out:
	ovl_cache_मुक्त(&list);
	वापस err;
पूर्ण

अटल पूर्णांक ovl_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	वापस ovl_करो_हटाओ(dentry, false);
पूर्ण

अटल पूर्णांक ovl_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	वापस ovl_करो_हटाओ(dentry, true);
पूर्ण

अटल bool ovl_type_merge_or_lower(काष्ठा dentry *dentry)
अणु
	क्रमागत ovl_path_type type = ovl_path_type(dentry);

	वापस OVL_TYPE_MERGE(type) || !OVL_TYPE_UPPER(type);
पूर्ण

अटल bool ovl_can_move(काष्ठा dentry *dentry)
अणु
	वापस ovl_redirect_dir(dentry->d_sb) ||
		!d_is_dir(dentry) || !ovl_type_merge_or_lower(dentry);
पूर्ण

अटल अक्षर *ovl_get_redirect(काष्ठा dentry *dentry, bool असल_redirect)
अणु
	अक्षर *buf, *ret;
	काष्ठा dentry *d, *पंचांगp;
	पूर्णांक buflen = ovl_redirect_max + 1;

	अगर (!असल_redirect) अणु
		ret = kstrndup(dentry->d_name.name, dentry->d_name.len,
			       GFP_KERNEL);
		जाओ out;
	पूर्ण

	buf = ret = kदो_स्मृति(buflen, GFP_KERNEL);
	अगर (!buf)
		जाओ out;

	buflen--;
	buf[buflen] = '\0';
	क्रम (d = dget(dentry); !IS_ROOT(d);) अणु
		स्थिर अक्षर *name;
		पूर्णांक thislen;

		spin_lock(&d->d_lock);
		name = ovl_dentry_get_redirect(d);
		अगर (name) अणु
			thislen = म_माप(name);
		पूर्ण अन्यथा अणु
			name = d->d_name.name;
			thislen = d->d_name.len;
		पूर्ण

		/* If path is too दीर्घ, fall back to userspace move */
		अगर (thislen + (name[0] != '/') > buflen) अणु
			ret = ERR_PTR(-EXDEV);
			spin_unlock(&d->d_lock);
			जाओ out_put;
		पूर्ण

		buflen -= thislen;
		स_नकल(&buf[buflen], name, thislen);
		spin_unlock(&d->d_lock);
		पंचांगp = dget_parent(d);

		dput(d);
		d = पंचांगp;

		/* Absolute redirect: finished */
		अगर (buf[buflen] == '/')
			अवरोध;
		buflen--;
		buf[buflen] = '/';
	पूर्ण
	ret = kstrdup(&buf[buflen], GFP_KERNEL);
out_put:
	dput(d);
	kमुक्त(buf);
out:
	वापस ret ? ret : ERR_PTR(-ENOMEM);
पूर्ण

अटल bool ovl_need_असलolute_redirect(काष्ठा dentry *dentry, bool samedir)
अणु
	काष्ठा dentry *lowerdentry;

	अगर (!samedir)
		वापस true;

	अगर (d_is_dir(dentry))
		वापस false;

	/*
	 * For non-dir hardlinked files, we need असलolute redirects
	 * in general as two upper hardlinks could be in dअगरferent
	 * dirs. We could put a relative redirect now and convert
	 * it to असलolute redirect later. But when nlink > 1 and
	 * indexing is on, that means relative redirect needs to be
	 * converted to असलolute during copy up of another lower
	 * hardllink as well.
	 *
	 * So without optimizing too much, just check अगर lower is
	 * a hard link or not. If lower is hard link, put असलolute
	 * redirect.
	 */
	lowerdentry = ovl_dentry_lower(dentry);
	वापस (d_inode(lowerdentry)->i_nlink > 1);
पूर्ण

अटल पूर्णांक ovl_set_redirect(काष्ठा dentry *dentry, bool samedir)
अणु
	पूर्णांक err;
	स्थिर अक्षर *redirect = ovl_dentry_get_redirect(dentry);
	bool असलolute_redirect = ovl_need_असलolute_redirect(dentry, samedir);

	अगर (redirect && (!असलolute_redirect || redirect[0] == '/'))
		वापस 0;

	redirect = ovl_get_redirect(dentry, असलolute_redirect);
	अगर (IS_ERR(redirect))
		वापस PTR_ERR(redirect);

	err = ovl_check_setxattr(dentry, ovl_dentry_upper(dentry),
				 OVL_XATTR_REसूचीECT,
				 redirect, म_माप(redirect), -EXDEV);
	अगर (!err) अणु
		spin_lock(&dentry->d_lock);
		ovl_dentry_set_redirect(dentry, redirect);
		spin_unlock(&dentry->d_lock);
	पूर्ण अन्यथा अणु
		kमुक्त(redirect);
		pr_warn_ratelimited("failed to set redirect (%i)\n",
				    err);
		/* Fall back to userspace copy-up */
		err = -EXDEV;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ovl_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *olddir,
		      काष्ठा dentry *old, काष्ठा inode *newdir,
		      काष्ठा dentry *new, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा dentry *old_upperdir;
	काष्ठा dentry *new_upperdir;
	काष्ठा dentry *olddentry;
	काष्ठा dentry *newdentry;
	काष्ठा dentry *trap;
	bool old_opaque;
	bool new_opaque;
	bool cleanup_whiteout = false;
	bool update_nlink = false;
	bool overग_लिखो = !(flags & RENAME_EXCHANGE);
	bool is_dir = d_is_dir(old);
	bool new_is_dir = d_is_dir(new);
	bool samedir = olddir == newdir;
	काष्ठा dentry *opaquedir = शून्य;
	स्थिर काष्ठा cred *old_cred = शून्य;
	LIST_HEAD(list);

	err = -EINVAL;
	अगर (flags & ~(RENAME_EXCHANGE | RENAME_NOREPLACE))
		जाओ out;

	flags &= ~RENAME_NOREPLACE;

	/* Don't copy up directory trees */
	err = -EXDEV;
	अगर (!ovl_can_move(old))
		जाओ out;
	अगर (!overग_लिखो && !ovl_can_move(new))
		जाओ out;

	अगर (overग_लिखो && new_is_dir && !ovl_pure_upper(new)) अणु
		err = ovl_check_empty_dir(new, &list);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (overग_लिखो) अणु
		अगर (ovl_lower_positive(old)) अणु
			अगर (!ovl_dentry_is_whiteout(new)) अणु
				/* Whiteout source */
				flags |= RENAME_WHITEOUT;
			पूर्ण अन्यथा अणु
				/* Switch whiteouts */
				flags |= RENAME_EXCHANGE;
			पूर्ण
		पूर्ण अन्यथा अगर (is_dir && ovl_dentry_is_whiteout(new)) अणु
			flags |= RENAME_EXCHANGE;
			cleanup_whiteout = true;
		पूर्ण
	पूर्ण

	err = ovl_want_ग_लिखो(old);
	अगर (err)
		जाओ out;

	err = ovl_copy_up(old);
	अगर (err)
		जाओ out_drop_ग_लिखो;

	err = ovl_copy_up(new->d_parent);
	अगर (err)
		जाओ out_drop_ग_लिखो;
	अगर (!overग_लिखो) अणु
		err = ovl_copy_up(new);
		अगर (err)
			जाओ out_drop_ग_लिखो;
	पूर्ण अन्यथा अगर (d_inode(new)) अणु
		err = ovl_nlink_start(new);
		अगर (err)
			जाओ out_drop_ग_लिखो;

		update_nlink = true;
	पूर्ण

	old_cred = ovl_override_creds(old->d_sb);

	अगर (!list_empty(&list)) अणु
		opaquedir = ovl_clear_empty(new, &list);
		err = PTR_ERR(opaquedir);
		अगर (IS_ERR(opaquedir)) अणु
			opaquedir = शून्य;
			जाओ out_revert_creds;
		पूर्ण
	पूर्ण

	old_upperdir = ovl_dentry_upper(old->d_parent);
	new_upperdir = ovl_dentry_upper(new->d_parent);

	अगर (!samedir) अणु
		/*
		 * When moving a merge dir or non-dir with copy up origin पूर्णांकo
		 * a new parent, we are marking the new parent dir "impure".
		 * When ovl_iterate() iterates an "impure" upper dir, it will
		 * lookup the origin inodes of the entries to fill d_ino.
		 */
		अगर (ovl_type_origin(old)) अणु
			err = ovl_set_impure(new->d_parent, new_upperdir);
			अगर (err)
				जाओ out_revert_creds;
		पूर्ण
		अगर (!overग_लिखो && ovl_type_origin(new)) अणु
			err = ovl_set_impure(old->d_parent, old_upperdir);
			अगर (err)
				जाओ out_revert_creds;
		पूर्ण
	पूर्ण

	trap = lock_नाम(new_upperdir, old_upperdir);

	olddentry = lookup_one_len(old->d_name.name, old_upperdir,
				   old->d_name.len);
	err = PTR_ERR(olddentry);
	अगर (IS_ERR(olddentry))
		जाओ out_unlock;

	err = -ESTALE;
	अगर (!ovl_matches_upper(old, olddentry))
		जाओ out_dput_old;

	newdentry = lookup_one_len(new->d_name.name, new_upperdir,
				   new->d_name.len);
	err = PTR_ERR(newdentry);
	अगर (IS_ERR(newdentry))
		जाओ out_dput_old;

	old_opaque = ovl_dentry_is_opaque(old);
	new_opaque = ovl_dentry_is_opaque(new);

	err = -ESTALE;
	अगर (d_inode(new) && ovl_dentry_upper(new)) अणु
		अगर (opaquedir) अणु
			अगर (newdentry != opaquedir)
				जाओ out_dput;
		पूर्ण अन्यथा अणु
			अगर (!ovl_matches_upper(new, newdentry))
				जाओ out_dput;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!d_is_negative(newdentry) &&
		    (!new_opaque || !ovl_is_whiteout(newdentry)))
			जाओ out_dput;
	पूर्ण

	अगर (olddentry == trap)
		जाओ out_dput;
	अगर (newdentry == trap)
		जाओ out_dput;

	अगर (olddentry->d_inode == newdentry->d_inode)
		जाओ out_dput;

	err = 0;
	अगर (ovl_type_merge_or_lower(old))
		err = ovl_set_redirect(old, samedir);
	अन्यथा अगर (is_dir && !old_opaque && ovl_type_merge(new->d_parent))
		err = ovl_set_opaque_xerr(old, olddentry, -EXDEV);
	अगर (err)
		जाओ out_dput;

	अगर (!overग_लिखो && ovl_type_merge_or_lower(new))
		err = ovl_set_redirect(new, samedir);
	अन्यथा अगर (!overग_लिखो && new_is_dir && !new_opaque &&
		 ovl_type_merge(old->d_parent))
		err = ovl_set_opaque_xerr(new, newdentry, -EXDEV);
	अगर (err)
		जाओ out_dput;

	err = ovl_करो_नाम(old_upperdir->d_inode, olddentry,
			    new_upperdir->d_inode, newdentry, flags);
	अगर (err)
		जाओ out_dput;

	अगर (cleanup_whiteout)
		ovl_cleanup(old_upperdir->d_inode, newdentry);

	अगर (overग_लिखो && d_inode(new)) अणु
		अगर (new_is_dir)
			clear_nlink(d_inode(new));
		अन्यथा
			ovl_drop_nlink(new);
	पूर्ण

	ovl_dir_modअगरied(old->d_parent, ovl_type_origin(old) ||
			 (!overग_लिखो && ovl_type_origin(new)));
	ovl_dir_modअगरied(new->d_parent, ovl_type_origin(old) ||
			 (d_inode(new) && ovl_type_origin(new)));

	/* copy स_समय: */
	ovl_copyattr(d_inode(olddentry), d_inode(old));
	अगर (d_inode(new) && ovl_dentry_upper(new))
		ovl_copyattr(d_inode(newdentry), d_inode(new));

out_dput:
	dput(newdentry);
out_dput_old:
	dput(olddentry);
out_unlock:
	unlock_नाम(new_upperdir, old_upperdir);
out_revert_creds:
	revert_creds(old_cred);
	अगर (update_nlink)
		ovl_nlink_end(new);
out_drop_ग_लिखो:
	ovl_drop_ग_लिखो(old);
out:
	dput(opaquedir);
	ovl_cache_मुक्त(&list);
	वापस err;
पूर्ण

स्थिर काष्ठा inode_operations ovl_dir_inode_operations = अणु
	.lookup		= ovl_lookup,
	.सूची_गढ़ो		= ovl_सूची_गढ़ो,
	.symlink	= ovl_symlink,
	.unlink		= ovl_unlink,
	.सूची_हटाओ		= ovl_सूची_हटाओ,
	.नाम		= ovl_नाम,
	.link		= ovl_link,
	.setattr	= ovl_setattr,
	.create		= ovl_create,
	.mknod		= ovl_mknod,
	.permission	= ovl_permission,
	.getattr	= ovl_getattr,
	.listxattr	= ovl_listxattr,
	.get_acl	= ovl_get_acl,
	.update_समय	= ovl_update_समय,
	.fileattr_get	= ovl_fileattr_get,
	.fileattr_set	= ovl_fileattr_set,
पूर्ण;
