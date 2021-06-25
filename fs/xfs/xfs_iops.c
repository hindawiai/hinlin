<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_acl.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_symlink.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_iomap.h"
#समावेश "xfs_error.h"
#समावेश "xfs_ioctl.h"

#समावेश <linux/posix_acl.h>
#समावेश <linux/security.h>
#समावेश <linux/iversion.h>
#समावेश <linux/fiemap.h>

/*
 * Directories have dअगरferent lock order w.r.t. mmap_lock compared to regular
 * files. This is due to सूची_पढ़ो potentially triggering page faults on a user
 * buffer inside filldir(), and this happens with the ilock on the directory
 * held. For regular files, the lock order is the other way around - the
 * mmap_lock is taken during the page fault, and then we lock the ilock to करो
 * block mapping. Hence we need a dअगरferent class क्रम the directory ilock so
 * that lockdep can tell them apart.
 */
अटल काष्ठा lock_class_key xfs_nondir_ilock_class;
अटल काष्ठा lock_class_key xfs_dir_ilock_class;

अटल पूर्णांक
xfs_initxattrs(
	काष्ठा inode		*inode,
	स्थिर काष्ठा xattr	*xattr_array,
	व्योम			*fs_info)
अणु
	स्थिर काष्ठा xattr	*xattr;
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	पूर्णांक			error = 0;

	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		काष्ठा xfs_da_args	args = अणु
			.dp		= ip,
			.attr_filter	= XFS_ATTR_SECURE,
			.name		= xattr->name,
			.namelen	= म_माप(xattr->name),
			.value		= xattr->value,
			.valuelen	= xattr->value_len,
		पूर्ण;
		error = xfs_attr_set(&args);
		अगर (error < 0)
			अवरोध;
	पूर्ण
	वापस error;
पूर्ण

/*
 * Hook in SELinux.  This is not quite correct yet, what we really need
 * here (as we करो क्रम शेष ACLs) is a mechanism by which creation of
 * these attrs can be journalled at inode creation समय (aदीर्घ with the
 * inode, of course, such that log replay can't cause these to be lost).
 */

STATIC पूर्णांक
xfs_init_security(
	काष्ठा inode	*inode,
	काष्ठा inode	*dir,
	स्थिर काष्ठा qstr *qstr)
अणु
	वापस security_inode_init_security(inode, dir, qstr,
					     &xfs_initxattrs, शून्य);
पूर्ण

अटल व्योम
xfs_dentry_to_name(
	काष्ठा xfs_name	*namep,
	काष्ठा dentry	*dentry)
अणु
	namep->name = dentry->d_name.name;
	namep->len = dentry->d_name.len;
	namep->type = XFS_सूची3_FT_UNKNOWN;
पूर्ण

अटल पूर्णांक
xfs_dentry_mode_to_name(
	काष्ठा xfs_name	*namep,
	काष्ठा dentry	*dentry,
	पूर्णांक		mode)
अणु
	namep->name = dentry->d_name.name;
	namep->len = dentry->d_name.len;
	namep->type = xfs_mode_to_ftype(mode);

	अगर (unlikely(namep->type == XFS_सूची3_FT_UNKNOWN))
		वापस -EFSCORRUPTED;

	वापस 0;
पूर्ण

STATIC व्योम
xfs_cleanup_inode(
	काष्ठा inode	*dir,
	काष्ठा inode	*inode,
	काष्ठा dentry	*dentry)
अणु
	काष्ठा xfs_name	tearकरोwn;

	/* Oh, the horror.
	 * If we can't add the ACL or we fail in
	 * xfs_init_security we must back out.
	 * ENOSPC can hit here, among other things.
	 */
	xfs_dentry_to_name(&tearकरोwn, dentry);

	xfs_हटाओ(XFS_I(dir), &tearकरोwn, XFS_I(inode));
पूर्ण

/*
 * Check to see अगर we are likely to need an extended attribute to be added to
 * the inode we are about to allocate. This allows the attribute विभाजन to be
 * created during the inode allocation, reducing the number of transactions we
 * need to करो in this fast path.
 *
 * The security checks are optimistic, but not guaranteed. The two LSMs that
 * require xattrs to be added here (selinux and smack) are also the only two
 * LSMs that add a sb->s_security काष्ठाure to the superblock. Hence अगर security
 * is enabled and sb->s_security is set, we have a pretty good idea that we are
 * going to be asked to add a security xattr immediately after allocating the
 * xfs inode and instantiating the VFS inode.
 */
अटल अंतरभूत bool
xfs_create_need_xattr(
	काष्ठा inode	*dir,
	काष्ठा posix_acl *शेष_acl,
	काष्ठा posix_acl *acl)
अणु
	अगर (acl)
		वापस true;
	अगर (शेष_acl)
		वापस true;
#अगर IS_ENABLED(CONFIG_SECURITY)
	अगर (dir->i_sb->s_security)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण


STATIC पूर्णांक
xfs_generic_create(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा inode	*dir,
	काष्ठा dentry	*dentry,
	umode_t		mode,
	dev_t		rdev,
	bool		क्षणिक_ख)	/* unnamed file */
अणु
	काष्ठा inode	*inode;
	काष्ठा xfs_inode *ip = शून्य;
	काष्ठा posix_acl *शेष_acl, *acl;
	काष्ठा xfs_name	name;
	पूर्णांक		error;

	/*
	 * Irix uses Missed'em'V split, but doesn't want to see
	 * the upper 5 bits of (14bit) major.
	 */
	अगर (S_ISCHR(mode) || S_ISBLK(mode)) अणु
		अगर (unlikely(!sysv_valid_dev(rdev) || MAJOR(rdev) & ~0x1ff))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		rdev = 0;
	पूर्ण

	error = posix_acl_create(dir, &mode, &शेष_acl, &acl);
	अगर (error)
		वापस error;

	/* Verअगरy mode is valid also क्रम क्षणिक_ख हाल */
	error = xfs_dentry_mode_to_name(&name, dentry, mode);
	अगर (unlikely(error))
		जाओ out_मुक्त_acl;

	अगर (!क्षणिक_ख) अणु
		error = xfs_create(mnt_userns, XFS_I(dir), &name, mode, rdev,
				xfs_create_need_xattr(dir, शेष_acl, acl),
				&ip);
	पूर्ण अन्यथा अणु
		error = xfs_create_क्षणिक_ख(mnt_userns, XFS_I(dir), mode, &ip);
	पूर्ण
	अगर (unlikely(error))
		जाओ out_मुक्त_acl;

	inode = VFS_I(ip);

	error = xfs_init_security(inode, dir, &dentry->d_name);
	अगर (unlikely(error))
		जाओ out_cleanup_inode;

#अगर_घोषित CONFIG_XFS_POSIX_ACL
	अगर (शेष_acl) अणु
		error = __xfs_set_acl(inode, शेष_acl, ACL_TYPE_DEFAULT);
		अगर (error)
			जाओ out_cleanup_inode;
	पूर्ण
	अगर (acl) अणु
		error = __xfs_set_acl(inode, acl, ACL_TYPE_ACCESS);
		अगर (error)
			जाओ out_cleanup_inode;
	पूर्ण
#पूर्ण_अगर

	xfs_setup_iops(ip);

	अगर (क्षणिक_ख) अणु
		/*
		 * The VFS requires that any inode fed to d_क्षणिक_ख must have
		 * nlink == 1 so that it can decrement the nlink in d_क्षणिक_ख.
		 * However, we created the temp file with nlink == 0 because
		 * we're not allowed to put an inode with nlink > 0 on the
		 * unlinked list.  Thereक्रमe we have to set nlink to 1 so that
		 * d_क्षणिक_ख can immediately set it back to zero.
		 */
		set_nlink(inode, 1);
		d_क्षणिक_ख(dentry, inode);
	पूर्ण अन्यथा
		d_instantiate(dentry, inode);

	xfs_finish_inode_setup(ip);

 out_मुक्त_acl:
	posix_acl_release(शेष_acl);
	posix_acl_release(acl);
	वापस error;

 out_cleanup_inode:
	xfs_finish_inode_setup(ip);
	अगर (!क्षणिक_ख)
		xfs_cleanup_inode(dir, inode, dentry);
	xfs_irele(ip);
	जाओ out_मुक्त_acl;
पूर्ण

STATIC पूर्णांक
xfs_vn_mknod(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा inode		*dir,
	काष्ठा dentry		*dentry,
	umode_t			mode,
	dev_t			rdev)
अणु
	वापस xfs_generic_create(mnt_userns, dir, dentry, mode, rdev, false);
पूर्ण

STATIC पूर्णांक
xfs_vn_create(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा inode		*dir,
	काष्ठा dentry		*dentry,
	umode_t			mode,
	bool			flags)
अणु
	वापस xfs_generic_create(mnt_userns, dir, dentry, mode, 0, false);
पूर्ण

STATIC पूर्णांक
xfs_vn_सूची_गढ़ो(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा inode		*dir,
	काष्ठा dentry		*dentry,
	umode_t			mode)
अणु
	वापस xfs_generic_create(mnt_userns, dir, dentry, mode | S_IFसूची, 0,
				  false);
पूर्ण

STATIC काष्ठा dentry *
xfs_vn_lookup(
	काष्ठा inode	*dir,
	काष्ठा dentry	*dentry,
	अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	काष्ठा xfs_inode *cip;
	काष्ठा xfs_name	name;
	पूर्णांक		error;

	अगर (dentry->d_name.len >= MAXNAMELEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	xfs_dentry_to_name(&name, dentry);
	error = xfs_lookup(XFS_I(dir), &name, &cip, शून्य);
	अगर (likely(!error))
		inode = VFS_I(cip);
	अन्यथा अगर (likely(error == -ENOENT))
		inode = शून्य;
	अन्यथा
		inode = ERR_PTR(error);
	वापस d_splice_alias(inode, dentry);
पूर्ण

STATIC काष्ठा dentry *
xfs_vn_ci_lookup(
	काष्ठा inode	*dir,
	काष्ठा dentry	*dentry,
	अचिन्हित पूर्णांक flags)
अणु
	काष्ठा xfs_inode *ip;
	काष्ठा xfs_name	xname;
	काष्ठा xfs_name ci_name;
	काष्ठा qstr	dname;
	पूर्णांक		error;

	अगर (dentry->d_name.len >= MAXNAMELEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	xfs_dentry_to_name(&xname, dentry);
	error = xfs_lookup(XFS_I(dir), &xname, &ip, &ci_name);
	अगर (unlikely(error)) अणु
		अगर (unlikely(error != -ENOENT))
			वापस ERR_PTR(error);
		/*
		 * call d_add(dentry, शून्य) here when d_drop_negative_children
		 * is called in xfs_vn_mknod (ie. allow negative dentries
		 * with CI fileप्रणालीs).
		 */
		वापस शून्य;
	पूर्ण

	/* अगर exact match, just splice and निकास */
	अगर (!ci_name.name)
		वापस d_splice_alias(VFS_I(ip), dentry);

	/* अन्यथा हाल-insensitive match... */
	dname.name = ci_name.name;
	dname.len = ci_name.len;
	dentry = d_add_ci(dentry, VFS_I(ip), &dname);
	kmem_मुक्त(ci_name.name);
	वापस dentry;
पूर्ण

STATIC पूर्णांक
xfs_vn_link(
	काष्ठा dentry	*old_dentry,
	काष्ठा inode	*dir,
	काष्ठा dentry	*dentry)
अणु
	काष्ठा inode	*inode = d_inode(old_dentry);
	काष्ठा xfs_name	name;
	पूर्णांक		error;

	error = xfs_dentry_mode_to_name(&name, dentry, inode->i_mode);
	अगर (unlikely(error))
		वापस error;

	error = xfs_link(XFS_I(dir), XFS_I(inode), &name);
	अगर (unlikely(error))
		वापस error;

	ihold(inode);
	d_instantiate(dentry, inode);
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_vn_unlink(
	काष्ठा inode	*dir,
	काष्ठा dentry	*dentry)
अणु
	काष्ठा xfs_name	name;
	पूर्णांक		error;

	xfs_dentry_to_name(&name, dentry);

	error = xfs_हटाओ(XFS_I(dir), &name, XFS_I(d_inode(dentry)));
	अगर (error)
		वापस error;

	/*
	 * With unlink, the VFS makes the dentry "negative": no inode,
	 * but still hashed. This is incompatible with हाल-insensitive
	 * mode, so invalidate (unhash) the dentry in CI-mode.
	 */
	अगर (xfs_sb_version_hasasciici(&XFS_M(dir->i_sb)->m_sb))
		d_invalidate(dentry);
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_vn_symlink(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा inode		*dir,
	काष्ठा dentry		*dentry,
	स्थिर अक्षर		*symname)
अणु
	काष्ठा inode	*inode;
	काष्ठा xfs_inode *cip = शून्य;
	काष्ठा xfs_name	name;
	पूर्णांक		error;
	umode_t		mode;

	mode = S_IFLNK |
		(irix_symlink_mode ? 0777 & ~current_umask() : S_IRWXUGO);
	error = xfs_dentry_mode_to_name(&name, dentry, mode);
	अगर (unlikely(error))
		जाओ out;

	error = xfs_symlink(mnt_userns, XFS_I(dir), &name, symname, mode, &cip);
	अगर (unlikely(error))
		जाओ out;

	inode = VFS_I(cip);

	error = xfs_init_security(inode, dir, &dentry->d_name);
	अगर (unlikely(error))
		जाओ out_cleanup_inode;

	xfs_setup_iops(cip);

	d_instantiate(dentry, inode);
	xfs_finish_inode_setup(cip);
	वापस 0;

 out_cleanup_inode:
	xfs_finish_inode_setup(cip);
	xfs_cleanup_inode(dir, inode, dentry);
	xfs_irele(cip);
 out:
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_vn_नाम(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा inode		*odir,
	काष्ठा dentry		*odentry,
	काष्ठा inode		*ndir,
	काष्ठा dentry		*ndentry,
	अचिन्हित पूर्णांक		flags)
अणु
	काष्ठा inode	*new_inode = d_inode(ndentry);
	पूर्णांक		omode = 0;
	पूर्णांक		error;
	काष्ठा xfs_name	oname;
	काष्ठा xfs_name	nname;

	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT))
		वापस -EINVAL;

	/* अगर we are exchanging files, we need to set i_mode of both files */
	अगर (flags & RENAME_EXCHANGE)
		omode = d_inode(ndentry)->i_mode;

	error = xfs_dentry_mode_to_name(&oname, odentry, omode);
	अगर (omode && unlikely(error))
		वापस error;

	error = xfs_dentry_mode_to_name(&nname, ndentry,
					d_inode(odentry)->i_mode);
	अगर (unlikely(error))
		वापस error;

	वापस xfs_नाम(mnt_userns, XFS_I(odir), &oname,
			  XFS_I(d_inode(odentry)), XFS_I(ndir), &nname,
			  new_inode ? XFS_I(new_inode) : शून्य, flags);
पूर्ण

/*
 * careful here - this function can get called recursively, so
 * we need to be very careful about how much stack we use.
 * uio is kदो_स्मृतिed क्रम this reason...
 */
STATIC स्थिर अक्षर *
xfs_vn_get_link(
	काष्ठा dentry		*dentry,
	काष्ठा inode		*inode,
	काष्ठा delayed_call	*करोne)
अणु
	अक्षर			*link;
	पूर्णांक			error = -ENOMEM;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	link = kदो_स्मृति(XFS_SYMLINK_MAXLEN+1, GFP_KERNEL);
	अगर (!link)
		जाओ out_err;

	error = xfs_पढ़ोlink(XFS_I(d_inode(dentry)), link);
	अगर (unlikely(error))
		जाओ out_kमुक्त;

	set_delayed_call(करोne, kमुक्त_link, link);
	वापस link;

 out_kमुक्त:
	kमुक्त(link);
 out_err:
	वापस ERR_PTR(error);
पूर्ण

STATIC स्थिर अक्षर *
xfs_vn_get_link_अंतरभूत(
	काष्ठा dentry		*dentry,
	काष्ठा inode		*inode,
	काष्ठा delayed_call	*करोne)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	अक्षर			*link;

	ASSERT(ip->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);

	/*
	 * The VFS crashes on a शून्य poपूर्णांकer, so वापस -EFSCORRUPTED अगर
	 * अगर_data is junk.
	 */
	link = ip->i_df.अगर_u1.अगर_data;
	अगर (XFS_IS_CORRUPT(ip->i_mount, !link))
		वापस ERR_PTR(-EFSCORRUPTED);
	वापस link;
पूर्ण

अटल uपूर्णांक32_t
xfs_stat_blksize(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;

	/*
	 * If the file blocks are being allocated from a realसमय volume, then
	 * always वापस the realसमय extent size.
	 */
	अगर (XFS_IS_REALTIME_INODE(ip))
		वापस xfs_get_extsz_hपूर्णांक(ip) << mp->m_sb.sb_blocklog;

	/*
	 * Allow large block sizes to be reported to userspace programs अगर the
	 * "largeio" mount option is used.
	 *
	 * If compatibility mode is specअगरied, simply वापस the basic unit of
	 * caching so that we करोn't get inefficient पढ़ो/modअगरy/ग_लिखो I/O from
	 * user apps. Otherwise....
	 *
	 * If the underlying volume is a stripe, then वापस the stripe width in
	 * bytes as the recommended I/O size. It is not a stripe and we've set a
	 * शेष buffered I/O size, वापस that, otherwise वापस the compat
	 * शेष.
	 */
	अगर (mp->m_flags & XFS_MOUNT_LARGEIO) अणु
		अगर (mp->m_swidth)
			वापस mp->m_swidth << mp->m_sb.sb_blocklog;
		अगर (mp->m_flags & XFS_MOUNT_ALLOCSIZE)
			वापस 1U << mp->m_allocsize_log;
	पूर्ण

	वापस PAGE_SIZE;
पूर्ण

STATIC पूर्णांक
xfs_vn_getattr(
	काष्ठा user_namespace	*mnt_userns,
	स्थिर काष्ठा path	*path,
	काष्ठा kstat		*stat,
	u32			request_mask,
	अचिन्हित पूर्णांक		query_flags)
अणु
	काष्ठा inode		*inode = d_inode(path->dentry);
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;

	trace_xfs_getattr(ip);

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	stat->size = XFS_ISIZE(ip);
	stat->dev = inode->i_sb->s_dev;
	stat->mode = inode->i_mode;
	stat->nlink = inode->i_nlink;
	stat->uid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
	stat->gid = i_gid_पूर्णांकo_mnt(mnt_userns, inode);
	stat->ino = ip->i_ino;
	stat->aसमय = inode->i_aसमय;
	stat->mसमय = inode->i_mसमय;
	stat->स_समय = inode->i_स_समय;
	stat->blocks = XFS_FSB_TO_BB(mp, ip->i_nblocks + ip->i_delayed_blks);

	अगर (xfs_sb_version_has_v3inode(&mp->m_sb)) अणु
		अगर (request_mask & STATX_BTIME) अणु
			stat->result_mask |= STATX_BTIME;
			stat->bसमय = ip->i_crसमय;
		पूर्ण
	पूर्ण

	/*
	 * Note: If you add another clause to set an attribute flag, please
	 * update attributes_mask below.
	 */
	अगर (ip->i_dअगरlags & XFS_DIFLAG_IMMUTABLE)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	अगर (ip->i_dअगरlags & XFS_DIFLAG_APPEND)
		stat->attributes |= STATX_ATTR_APPEND;
	अगर (ip->i_dअगरlags & XFS_DIFLAG_NODUMP)
		stat->attributes |= STATX_ATTR_NODUMP;

	stat->attributes_mask |= (STATX_ATTR_IMMUTABLE |
				  STATX_ATTR_APPEND |
				  STATX_ATTR_NODUMP);

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFBLK:
	हाल S_IFCHR:
		stat->blksize = BLKDEV_IOSIZE;
		stat->rdev = inode->i_rdev;
		अवरोध;
	शेष:
		stat->blksize = xfs_stat_blksize(ip);
		stat->rdev = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
xfs_setattr_mode(
	काष्ठा xfs_inode	*ip,
	काष्ठा iattr		*iattr)
अणु
	काष्ठा inode		*inode = VFS_I(ip);
	umode_t			mode = iattr->ia_mode;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	inode->i_mode &= S_IFMT;
	inode->i_mode |= mode & ~S_IFMT;
पूर्ण

व्योम
xfs_setattr_समय(
	काष्ठा xfs_inode	*ip,
	काष्ठा iattr		*iattr)
अणु
	काष्ठा inode		*inode = VFS_I(ip);

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	अगर (iattr->ia_valid & ATTR_ATIME)
		inode->i_aसमय = iattr->ia_aसमय;
	अगर (iattr->ia_valid & ATTR_CTIME)
		inode->i_स_समय = iattr->ia_स_समय;
	अगर (iattr->ia_valid & ATTR_MTIME)
		inode->i_mसमय = iattr->ia_mसमय;
पूर्ण

अटल पूर्णांक
xfs_vn_change_ok(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा dentry		*dentry,
	काष्ठा iattr		*iattr)
अणु
	काष्ठा xfs_mount	*mp = XFS_I(d_inode(dentry))->i_mount;

	अगर (mp->m_flags & XFS_MOUNT_RDONLY)
		वापस -EROFS;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	वापस setattr_prepare(mnt_userns, dentry, iattr);
पूर्ण

/*
 * Set non-size attributes of an inode.
 *
 * Caution: The caller of this function is responsible क्रम calling
 * setattr_prepare() or otherwise verअगरying the change is fine.
 */
अटल पूर्णांक
xfs_setattr_nonsize(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_inode	*ip,
	काष्ठा iattr		*iattr)
अणु
	xfs_mount_t		*mp = ip->i_mount;
	काष्ठा inode		*inode = VFS_I(ip);
	पूर्णांक			mask = iattr->ia_valid;
	xfs_trans_t		*tp;
	पूर्णांक			error;
	kuid_t			uid = GLOBAL_ROOT_UID, iuid = GLOBAL_ROOT_UID;
	kgid_t			gid = GLOBAL_ROOT_GID, igid = GLOBAL_ROOT_GID;
	काष्ठा xfs_dquot	*udqp = शून्य, *gdqp = शून्य;
	काष्ठा xfs_dquot	*olddquot1 = शून्य, *olddquot2 = शून्य;

	ASSERT((mask & ATTR_SIZE) == 0);

	/*
	 * If disk quotas is on, we make sure that the dquots करो exist on disk,
	 * beक्रमe we start any other transactions. Trying to करो this later
	 * is messy. We करोn't care to take a पढ़ोlock to look at the ids
	 * in inode here, because we can't hold it across the trans_reserve.
	 * If the IDs करो change beक्रमe we take the ilock, we're covered
	 * because the i_*dquot fields will get updated anyway.
	 */
	अगर (XFS_IS_QUOTA_ON(mp) && (mask & (ATTR_UID|ATTR_GID))) अणु
		uपूर्णांक	qflags = 0;

		अगर ((mask & ATTR_UID) && XFS_IS_UQUOTA_ON(mp)) अणु
			uid = iattr->ia_uid;
			qflags |= XFS_QMOPT_UQUOTA;
		पूर्ण अन्यथा अणु
			uid = inode->i_uid;
		पूर्ण
		अगर ((mask & ATTR_GID) && XFS_IS_GQUOTA_ON(mp)) अणु
			gid = iattr->ia_gid;
			qflags |= XFS_QMOPT_GQUOTA;
		पूर्ण  अन्यथा अणु
			gid = inode->i_gid;
		पूर्ण

		/*
		 * We take a reference when we initialize udqp and gdqp,
		 * so it is important that we never blindly द्विगुन trip on
		 * the same variable. See xfs_create() क्रम an example.
		 */
		ASSERT(udqp == शून्य);
		ASSERT(gdqp == शून्य);
		error = xfs_qm_vop_dqalloc(ip, uid, gid, ip->i_projid,
					   qflags, &udqp, &gdqp, शून्य);
		अगर (error)
			वापस error;
	पूर्ण

	error = xfs_trans_alloc_ichange(ip, udqp, gdqp, शून्य,
			capable(CAP_FOWNER), &tp);
	अगर (error)
		जाओ out_dqrele;

	/*
	 * Change file ownership.  Must be the owner or privileged.
	 */
	अगर (mask & (ATTR_UID|ATTR_GID)) अणु
		/*
		 * These IDs could have changed since we last looked at them.
		 * But, we're assured that अगर the ownership did change
		 * जबतक we didn't have the inode locked, inode's dquot(s)
		 * would have changed also.
		 */
		iuid = inode->i_uid;
		igid = inode->i_gid;
		gid = (mask & ATTR_GID) ? iattr->ia_gid : igid;
		uid = (mask & ATTR_UID) ? iattr->ia_uid : iuid;

		/*
		 * CAP_FSETID overrides the following restrictions:
		 *
		 * The set-user-ID and set-group-ID bits of a file will be
		 * cleared upon successful वापस from chown()
		 */
		अगर ((inode->i_mode & (S_ISUID|S_ISGID)) &&
		    !capable(CAP_FSETID))
			inode->i_mode &= ~(S_ISUID|S_ISGID);

		/*
		 * Change the ownerships and रेजिस्टर quota modअगरications
		 * in the transaction.
		 */
		अगर (!uid_eq(iuid, uid)) अणु
			अगर (XFS_IS_QUOTA_RUNNING(mp) && XFS_IS_UQUOTA_ON(mp)) अणु
				ASSERT(mask & ATTR_UID);
				ASSERT(udqp);
				olddquot1 = xfs_qm_vop_chown(tp, ip,
							&ip->i_udquot, udqp);
			पूर्ण
			inode->i_uid = uid;
		पूर्ण
		अगर (!gid_eq(igid, gid)) अणु
			अगर (XFS_IS_QUOTA_RUNNING(mp) && XFS_IS_GQUOTA_ON(mp)) अणु
				ASSERT(xfs_sb_version_has_pquotino(&mp->m_sb) ||
				       !XFS_IS_PQUOTA_ON(mp));
				ASSERT(mask & ATTR_GID);
				ASSERT(gdqp);
				olddquot2 = xfs_qm_vop_chown(tp, ip,
							&ip->i_gdquot, gdqp);
			पूर्ण
			inode->i_gid = gid;
		पूर्ण
	पूर्ण

	अगर (mask & ATTR_MODE)
		xfs_setattr_mode(ip, iattr);
	अगर (mask & (ATTR_ATIME|ATTR_CTIME|ATTR_MTIME))
		xfs_setattr_समय(ip, iattr);

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	XFS_STATS_INC(mp, xs_ig_attrchg);

	अगर (mp->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(tp);
	error = xfs_trans_commit(tp);

	/*
	 * Release any dquot(s) the inode had kept beक्रमe chown.
	 */
	xfs_qm_dqrele(olddquot1);
	xfs_qm_dqrele(olddquot2);
	xfs_qm_dqrele(udqp);
	xfs_qm_dqrele(gdqp);

	अगर (error)
		वापस error;

	/*
	 * XXX(hch): Updating the ACL entries is not atomic vs the i_mode
	 * 	     update.  We could aव्योम this with linked transactions
	 * 	     and passing करोwn the transaction poपूर्णांकer all the way
	 *	     to attr_set.  No previous user of the generic
	 * 	     Posix ACL code seems to care about this issue either.
	 */
	अगर (mask & ATTR_MODE) अणु
		error = posix_acl_chmod(mnt_userns, inode, inode->i_mode);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;

out_dqrele:
	xfs_qm_dqrele(udqp);
	xfs_qm_dqrele(gdqp);
	वापस error;
पूर्ण

/*
 * Truncate file.  Must have ग_लिखो permission and not be a directory.
 *
 * Caution: The caller of this function is responsible क्रम calling
 * setattr_prepare() or otherwise verअगरying the change is fine.
 */
STATIC पूर्णांक
xfs_setattr_size(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_inode	*ip,
	काष्ठा iattr		*iattr)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा inode		*inode = VFS_I(ip);
	xfs_off_t		oldsize, newsize;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;
	uपूर्णांक			lock_flags = 0;
	bool			did_zeroing = false;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL));
	ASSERT(xfs_isilocked(ip, XFS_MMAPLOCK_EXCL));
	ASSERT(S_ISREG(inode->i_mode));
	ASSERT((iattr->ia_valid & (ATTR_UID|ATTR_GID|ATTR_ATIME|ATTR_ATIME_SET|
		ATTR_MTIME_SET|ATTR_TIMES_SET)) == 0);

	oldsize = inode->i_size;
	newsize = iattr->ia_size;

	/*
	 * Short circuit the truncate हाल क्रम zero length files.
	 */
	अगर (newsize == 0 && oldsize == 0 && ip->i_df.अगर_nextents == 0) अणु
		अगर (!(iattr->ia_valid & (ATTR_CTIME|ATTR_MTIME)))
			वापस 0;

		/*
		 * Use the regular setattr path to update the बारtamps.
		 */
		iattr->ia_valid &= ~ATTR_SIZE;
		वापस xfs_setattr_nonsize(mnt_userns, ip, iattr);
	पूर्ण

	/*
	 * Make sure that the dquots are attached to the inode.
	 */
	error = xfs_qm_dqattach(ip);
	अगर (error)
		वापस error;

	/*
	 * Wait क्रम all direct I/O to complete.
	 */
	inode_dio_रुको(inode);

	/*
	 * File data changes must be complete beक्रमe we start the transaction to
	 * modअगरy the inode.  This needs to be करोne beक्रमe joining the inode to
	 * the transaction because the inode cannot be unlocked once it is a
	 * part of the transaction.
	 *
	 * Start with zeroing any data beyond खातापूर्ण that we may expose on file
	 * extension, or zeroing out the rest of the block on a करोwnward
	 * truncate.
	 */
	अगर (newsize > oldsize) अणु
		trace_xfs_zero_eof(ip, oldsize, newsize - oldsize);
		error = iomap_zero_range(inode, oldsize, newsize - oldsize,
				&did_zeroing, &xfs_buffered_ग_लिखो_iomap_ops);
	पूर्ण अन्यथा अणु
		/*
		 * iomap won't detect a dirty page over an unwritten block (or a
		 * cow block over a hole) and subsequently skips zeroing the
		 * newly post-खातापूर्ण portion of the page. Flush the new खातापूर्ण to
		 * convert the block beक्रमe the pagecache truncate.
		 */
		error = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, newsize,
						     newsize);
		अगर (error)
			वापस error;
		error = iomap_truncate_page(inode, newsize, &did_zeroing,
				&xfs_buffered_ग_लिखो_iomap_ops);
	पूर्ण

	अगर (error)
		वापस error;

	/*
	 * We've alपढ़ोy locked out new page faults, so now we can safely हटाओ
	 * pages from the page cache knowing they won't get refaulted until we
	 * drop the XFS_MMAP_EXCL lock after the extent manipulations are
	 * complete. The truncate_setsize() call also cleans partial खातापूर्ण page
	 * PTEs on extending truncates and hence ensures sub-page block size
	 * fileप्रणालीs are correctly handled, too.
	 *
	 * We have to करो all the page cache truncate work outside the
	 * transaction context as the "lock" order is page lock->log space
	 * reservation as defined by extent allocation in the ग_लिखोback path.
	 * Hence a truncate can fail with ENOMEM from xfs_trans_alloc(), but
	 * having alपढ़ोy truncated the in-memory version of the file (i.e. made
	 * user visible changes). There's not much we can करो about this, except
	 * to hope that the caller sees ENOMEM and retries the truncate
	 * operation.
	 *
	 * And we update in-core i_size and truncate page cache beyond newsize
	 * beक्रमe ग_लिखोback the [i_disk_size, newsize] range, so we're
	 * guaranteed not to ग_लिखो stale data past the new खातापूर्ण on truncate करोwn.
	 */
	truncate_setsize(inode, newsize);

	/*
	 * We are going to log the inode size change in this transaction so
	 * any previous ग_लिखोs that are beyond the on disk खातापूर्ण and the new
	 * खातापूर्ण that have not been written out need to be written here.  If we
	 * करो not ग_लिखो the data out, we expose ourselves to the null files
	 * problem. Note that this includes any block zeroing we did above;
	 * otherwise those blocks may not be zeroed after a crash.
	 */
	अगर (did_zeroing ||
	    (newsize > ip->i_disk_size && oldsize != ip->i_disk_size)) अणु
		error = filemap_ग_लिखो_and_रुको_range(VFS_I(ip)->i_mapping,
						ip->i_disk_size, newsize - 1);
		अगर (error)
			वापस error;
	पूर्ण

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	lock_flags |= XFS_ILOCK_EXCL;
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	/*
	 * Only change the c/mसमय अगर we are changing the size or we are
	 * explicitly asked to change it.  This handles the semantic dअगरference
	 * between truncate() and ftruncate() as implemented in the VFS.
	 *
	 * The regular truncate() हाल without ATTR_CTIME and ATTR_MTIME is a
	 * special हाल where we need to update the बार despite not having
	 * these flags set.  For all other operations the VFS set these flags
	 * explicitly अगर it wants a बारtamp update.
	 */
	अगर (newsize != oldsize &&
	    !(iattr->ia_valid & (ATTR_CTIME | ATTR_MTIME))) अणु
		iattr->ia_स_समय = iattr->ia_mसमय =
			current_समय(inode);
		iattr->ia_valid |= ATTR_CTIME | ATTR_MTIME;
	पूर्ण

	/*
	 * The first thing we करो is set the size to new_size permanently on
	 * disk.  This way we करोn't have to worry about anyone ever being able
	 * to look at the data being मुक्तd even in the face of a crash.
	 * What we're getting around here is the हाल where we मुक्त a block, it
	 * is allocated to another file, it is written to, and then we crash.
	 * If the new data माला_लो written to the file but the log buffers
	 * containing the मुक्त and पुनः_स्मृतिation करोn't, then we'd end up with
	 * garbage in the blocks being मुक्तd.  As दीर्घ as we make the new size
	 * permanent beक्रमe actually मुक्तing any blocks it करोesn't matter अगर
	 * they get written to.
	 */
	ip->i_disk_size = newsize;
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	अगर (newsize <= oldsize) अणु
		error = xfs_itruncate_extents(&tp, ip, XFS_DATA_FORK, newsize);
		अगर (error)
			जाओ out_trans_cancel;

		/*
		 * Truncated "down", so we're removing references to old data
		 * here - अगर we delay flushing क्रम a दीर्घ समय, we expose
		 * ourselves unduly to the notorious शून्य files problem.  So,
		 * we mark this inode and flush it when the file is बंदd,
		 * and करो not रुको the usual (दीर्घ) समय क्रम ग_लिखोout.
		 */
		xfs_अगरlags_set(ip, XFS_ITRUNCATED);

		/* A truncate करोwn always हटाओs post-खातापूर्ण blocks. */
		xfs_inode_clear_eofblocks_tag(ip);
	पूर्ण

	अगर (iattr->ia_valid & ATTR_MODE)
		xfs_setattr_mode(ip, iattr);
	अगर (iattr->ia_valid & (ATTR_ATIME|ATTR_CTIME|ATTR_MTIME))
		xfs_setattr_समय(ip, iattr);

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	XFS_STATS_INC(mp, xs_ig_attrchg);

	अगर (mp->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(tp);

	error = xfs_trans_commit(tp);
out_unlock:
	अगर (lock_flags)
		xfs_iunlock(ip, lock_flags);
	वापस error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	जाओ out_unlock;
पूर्ण

पूर्णांक
xfs_vn_setattr_size(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा dentry		*dentry,
	काष्ठा iattr		*iattr)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(d_inode(dentry));
	पूर्णांक error;

	trace_xfs_setattr(ip);

	error = xfs_vn_change_ok(mnt_userns, dentry, iattr);
	अगर (error)
		वापस error;
	वापस xfs_setattr_size(mnt_userns, ip, iattr);
पूर्ण

STATIC पूर्णांक
xfs_vn_setattr(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा dentry		*dentry,
	काष्ठा iattr		*iattr)
अणु
	काष्ठा inode		*inode = d_inode(dentry);
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	पूर्णांक			error;

	अगर (iattr->ia_valid & ATTR_SIZE) अणु
		uपूर्णांक			iolock;

		xfs_ilock(ip, XFS_MMAPLOCK_EXCL);
		iolock = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;

		error = xfs_अवरोध_layouts(inode, &iolock, BREAK_UNMAP);
		अगर (error) अणु
			xfs_iunlock(ip, XFS_MMAPLOCK_EXCL);
			वापस error;
		पूर्ण

		error = xfs_vn_setattr_size(mnt_userns, dentry, iattr);
		xfs_iunlock(ip, XFS_MMAPLOCK_EXCL);
	पूर्ण अन्यथा अणु
		trace_xfs_setattr(ip);

		error = xfs_vn_change_ok(mnt_userns, dentry, iattr);
		अगर (!error)
			error = xfs_setattr_nonsize(mnt_userns, ip, iattr);
	पूर्ण

	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_vn_update_समय(
	काष्ठा inode		*inode,
	काष्ठा बारpec64	*now,
	पूर्णांक			flags)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			log_flags = XFS_ILOG_TIMESTAMP;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	trace_xfs_update_समय(ip);

	अगर (inode->i_sb->s_flags & SB_LAZYTIME) अणु
		अगर (!((flags & S_VERSION) &&
		      inode_maybe_inc_iversion(inode, false)))
			वापस generic_update_समय(inode, now, flags);

		/* Capture the iversion update that just occurred */
		log_flags |= XFS_ILOG_CORE;
	पूर्ण

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_fsyncts, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	अगर (flags & S_CTIME)
		inode->i_स_समय = *now;
	अगर (flags & S_MTIME)
		inode->i_mसमय = *now;
	अगर (flags & S_ATIME)
		inode->i_aसमय = *now;

	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
	xfs_trans_log_inode(tp, ip, log_flags);
	वापस xfs_trans_commit(tp);
पूर्ण

STATIC पूर्णांक
xfs_vn_fiemap(
	काष्ठा inode		*inode,
	काष्ठा fiemap_extent_info *fieinfo,
	u64			start,
	u64			length)
अणु
	पूर्णांक			error;

	xfs_ilock(XFS_I(inode), XFS_IOLOCK_SHARED);
	अगर (fieinfo->fi_flags & FIEMAP_FLAG_XATTR) अणु
		fieinfo->fi_flags &= ~FIEMAP_FLAG_XATTR;
		error = iomap_fiemap(inode, fieinfo, start, length,
				&xfs_xattr_iomap_ops);
	पूर्ण अन्यथा अणु
		error = iomap_fiemap(inode, fieinfo, start, length,
				&xfs_पढ़ो_iomap_ops);
	पूर्ण
	xfs_iunlock(XFS_I(inode), XFS_IOLOCK_SHARED);

	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_vn_क्षणिक_ख(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा inode		*dir,
	काष्ठा dentry		*dentry,
	umode_t			mode)
अणु
	वापस xfs_generic_create(mnt_userns, dir, dentry, mode, 0, true);
पूर्ण

अटल स्थिर काष्ठा inode_operations xfs_inode_operations = अणु
	.get_acl		= xfs_get_acl,
	.set_acl		= xfs_set_acl,
	.getattr		= xfs_vn_getattr,
	.setattr		= xfs_vn_setattr,
	.listxattr		= xfs_vn_listxattr,
	.fiemap			= xfs_vn_fiemap,
	.update_समय		= xfs_vn_update_समय,
	.fileattr_get		= xfs_fileattr_get,
	.fileattr_set		= xfs_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा inode_operations xfs_dir_inode_operations = अणु
	.create			= xfs_vn_create,
	.lookup			= xfs_vn_lookup,
	.link			= xfs_vn_link,
	.unlink			= xfs_vn_unlink,
	.symlink		= xfs_vn_symlink,
	.सूची_गढ़ो			= xfs_vn_सूची_गढ़ो,
	/*
	 * Yes, XFS uses the same method क्रम सूची_हटाओ and unlink.
	 *
	 * There are some subtile dअगरferences deeper in the code,
	 * but we use S_ISसूची to check क्रम those.
	 */
	.सूची_हटाओ			= xfs_vn_unlink,
	.mknod			= xfs_vn_mknod,
	.नाम			= xfs_vn_नाम,
	.get_acl		= xfs_get_acl,
	.set_acl		= xfs_set_acl,
	.getattr		= xfs_vn_getattr,
	.setattr		= xfs_vn_setattr,
	.listxattr		= xfs_vn_listxattr,
	.update_समय		= xfs_vn_update_समय,
	.क्षणिक_ख		= xfs_vn_क्षणिक_ख,
	.fileattr_get		= xfs_fileattr_get,
	.fileattr_set		= xfs_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा inode_operations xfs_dir_ci_inode_operations = अणु
	.create			= xfs_vn_create,
	.lookup			= xfs_vn_ci_lookup,
	.link			= xfs_vn_link,
	.unlink			= xfs_vn_unlink,
	.symlink		= xfs_vn_symlink,
	.सूची_गढ़ो			= xfs_vn_सूची_गढ़ो,
	/*
	 * Yes, XFS uses the same method क्रम सूची_हटाओ and unlink.
	 *
	 * There are some subtile dअगरferences deeper in the code,
	 * but we use S_ISसूची to check क्रम those.
	 */
	.सूची_हटाओ			= xfs_vn_unlink,
	.mknod			= xfs_vn_mknod,
	.नाम			= xfs_vn_नाम,
	.get_acl		= xfs_get_acl,
	.set_acl		= xfs_set_acl,
	.getattr		= xfs_vn_getattr,
	.setattr		= xfs_vn_setattr,
	.listxattr		= xfs_vn_listxattr,
	.update_समय		= xfs_vn_update_समय,
	.क्षणिक_ख		= xfs_vn_क्षणिक_ख,
	.fileattr_get		= xfs_fileattr_get,
	.fileattr_set		= xfs_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा inode_operations xfs_symlink_inode_operations = अणु
	.get_link		= xfs_vn_get_link,
	.getattr		= xfs_vn_getattr,
	.setattr		= xfs_vn_setattr,
	.listxattr		= xfs_vn_listxattr,
	.update_समय		= xfs_vn_update_समय,
पूर्ण;

अटल स्थिर काष्ठा inode_operations xfs_अंतरभूत_symlink_inode_operations = अणु
	.get_link		= xfs_vn_get_link_अंतरभूत,
	.getattr		= xfs_vn_getattr,
	.setattr		= xfs_vn_setattr,
	.listxattr		= xfs_vn_listxattr,
	.update_समय		= xfs_vn_update_समय,
पूर्ण;

/* Figure out अगर this file actually supports DAX. */
अटल bool
xfs_inode_supports_dax(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;

	/* Only supported on regular files. */
	अगर (!S_ISREG(VFS_I(ip)->i_mode))
		वापस false;

	/* Only supported on non-reflinked files. */
	अगर (xfs_is_reflink_inode(ip))
		वापस false;

	/* Block size must match page size */
	अगर (mp->m_sb.sb_blocksize != PAGE_SIZE)
		वापस false;

	/* Device has to support DAX too. */
	वापस xfs_inode_buftarg(ip)->bt_daxdev != शून्य;
पूर्ण

अटल bool
xfs_inode_should_enable_dax(
	काष्ठा xfs_inode *ip)
अणु
	अगर (!IS_ENABLED(CONFIG_FS_DAX))
		वापस false;
	अगर (ip->i_mount->m_flags & XFS_MOUNT_DAX_NEVER)
		वापस false;
	अगर (!xfs_inode_supports_dax(ip))
		वापस false;
	अगर (ip->i_mount->m_flags & XFS_MOUNT_DAX_ALWAYS)
		वापस true;
	अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_DAX)
		वापस true;
	वापस false;
पूर्ण

व्योम
xfs_dअगरlags_to_अगरlags(
	काष्ठा xfs_inode	*ip,
	bool init)
अणु
	काष्ठा inode            *inode = VFS_I(ip);
	अचिन्हित पूर्णांक            xflags = xfs_ip2xflags(ip);
	अचिन्हित पूर्णांक            flags = 0;

	ASSERT(!(IS_DAX(inode) && init));

	अगर (xflags & FS_XFLAG_IMMUTABLE)
		flags |= S_IMMUTABLE;
	अगर (xflags & FS_XFLAG_APPEND)
		flags |= S_APPEND;
	अगर (xflags & FS_XFLAG_SYNC)
		flags |= S_SYNC;
	अगर (xflags & FS_XFLAG_NOATIME)
		flags |= S_NOATIME;
	अगर (init && xfs_inode_should_enable_dax(ip))
		flags |= S_DAX;

	/*
	 * S_DAX can only be set during inode initialization and is never set by
	 * the VFS, so we cannot mask off S_DAX in i_flags.
	 */
	inode->i_flags &= ~(S_IMMUTABLE | S_APPEND | S_SYNC | S_NOATIME);
	inode->i_flags |= flags;
पूर्ण

/*
 * Initialize the Linux inode.
 *
 * When पढ़ोing existing inodes from disk this is called directly from xfs_iget,
 * when creating a new inode it is called from xfs_ialloc after setting up the
 * inode. These callers have dअगरferent criteria क्रम clearing XFS_INEW, so leave
 * it up to the caller to deal with unlocking the inode appropriately.
 */
व्योम
xfs_setup_inode(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा inode		*inode = &ip->i_vnode;
	gfp_t			gfp_mask;

	inode->i_ino = ip->i_ino;
	inode->i_state = I_NEW;

	inode_sb_list_add(inode);
	/* make the inode look hashed क्रम the ग_लिखोback code */
	inode_fake_hash(inode);

	i_size_ग_लिखो(inode, ip->i_disk_size);
	xfs_dअगरlags_to_अगरlags(ip, true);

	अगर (S_ISसूची(inode->i_mode)) अणु
		/*
		 * We set the i_rwsem class here to aव्योम potential races with
		 * lockdep_annotate_inode_mutex_key() reinitialising the lock
		 * after a filehandle lookup has alपढ़ोy found the inode in
		 * cache beक्रमe it has been unlocked via unlock_new_inode().
		 */
		lockdep_set_class(&inode->i_rwsem,
				  &inode->i_sb->s_type->i_mutex_dir_key);
		lockdep_set_class(&ip->i_lock.mr_lock, &xfs_dir_ilock_class);
	पूर्ण अन्यथा अणु
		lockdep_set_class(&ip->i_lock.mr_lock, &xfs_nondir_ilock_class);
	पूर्ण

	/*
	 * Ensure all page cache allocations are करोne from GFP_NOFS context to
	 * prevent direct reclaim recursion back पूर्णांकo the fileप्रणाली and blowing
	 * stacks or deadlocking.
	 */
	gfp_mask = mapping_gfp_mask(inode->i_mapping);
	mapping_set_gfp_mask(inode->i_mapping, (gfp_mask & ~(__GFP_FS)));

	/*
	 * If there is no attribute विभाजन no ACL can exist on this inode,
	 * and it can't have any file capabilities attached to it either.
	 */
	अगर (!XFS_IFORK_Q(ip)) अणु
		inode_has_no_xattr(inode);
		cache_no_acl(inode);
	पूर्ण
पूर्ण

व्योम
xfs_setup_iops(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा inode		*inode = &ip->i_vnode;

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFREG:
		inode->i_op = &xfs_inode_operations;
		inode->i_fop = &xfs_file_operations;
		अगर (IS_DAX(inode))
			inode->i_mapping->a_ops = &xfs_dax_aops;
		अन्यथा
			inode->i_mapping->a_ops = &xfs_address_space_operations;
		अवरोध;
	हाल S_IFसूची:
		अगर (xfs_sb_version_hasasciici(&XFS_M(inode->i_sb)->m_sb))
			inode->i_op = &xfs_dir_ci_inode_operations;
		अन्यथा
			inode->i_op = &xfs_dir_inode_operations;
		inode->i_fop = &xfs_dir_file_operations;
		अवरोध;
	हाल S_IFLNK:
		अगर (ip->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL)
			inode->i_op = &xfs_अंतरभूत_symlink_inode_operations;
		अन्यथा
			inode->i_op = &xfs_symlink_inode_operations;
		अवरोध;
	शेष:
		inode->i_op = &xfs_inode_operations;
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		अवरोध;
	पूर्ण
पूर्ण
