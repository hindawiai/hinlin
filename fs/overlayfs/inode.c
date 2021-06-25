<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2011 Novell Inc.
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/fiemap.h>
#समावेश <linux/fileattr.h>
#समावेश <linux/security.h>
#समावेश "overlayfs.h"


पूर्णांक ovl_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		काष्ठा iattr *attr)
अणु
	पूर्णांक err;
	bool full_copy_up = false;
	काष्ठा dentry *upperdentry;
	स्थिर काष्ठा cred *old_cred;

	err = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (err)
		वापस err;

	err = ovl_want_ग_लिखो(dentry);
	अगर (err)
		जाओ out;

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		काष्ठा inode *realinode = d_inode(ovl_dentry_real(dentry));

		err = -ETXTBSY;
		अगर (atomic_पढ़ो(&realinode->i_ग_लिखोcount) < 0)
			जाओ out_drop_ग_लिखो;

		/* Truncate should trigger data copy up as well */
		full_copy_up = true;
	पूर्ण

	अगर (!full_copy_up)
		err = ovl_copy_up(dentry);
	अन्यथा
		err = ovl_copy_up_with_data(dentry);
	अगर (!err) अणु
		काष्ठा inode *winode = शून्य;

		upperdentry = ovl_dentry_upper(dentry);

		अगर (attr->ia_valid & ATTR_SIZE) अणु
			winode = d_inode(upperdentry);
			err = get_ग_लिखो_access(winode);
			अगर (err)
				जाओ out_drop_ग_लिखो;
		पूर्ण

		अगर (attr->ia_valid & (ATTR_KILL_SUID|ATTR_KILL_SGID))
			attr->ia_valid &= ~ATTR_MODE;

		/*
		 * We might have to translate ovl file पूर्णांकo real file object
		 * once use हालs emerge.  For now, simply करोn't let underlying
		 * fileप्रणाली rely on attr->ia_file
		 */
		attr->ia_valid &= ~ATTR_खाता;

		/*
		 * If खोलो(O_TRUNC) is करोne, VFS calls ->setattr with ATTR_OPEN
		 * set.  Overlayfs करोes not pass O_TRUNC flag to underlying
		 * fileप्रणाली during खोलो -> करो not pass ATTR_OPEN.  This
		 * disables optimization in fuse which assumes खोलो(O_TRUNC)
		 * alपढ़ोy set file size to 0.  But we never passed O_TRUNC to
		 * fuse.  So by clearing ATTR_OPEN, fuse will be क्रमced to send
		 * setattr request to server.
		 */
		attr->ia_valid &= ~ATTR_OPEN;

		inode_lock(upperdentry->d_inode);
		old_cred = ovl_override_creds(dentry->d_sb);
		err = notअगरy_change(&init_user_ns, upperdentry, attr, शून्य);
		revert_creds(old_cred);
		अगर (!err)
			ovl_copyattr(upperdentry->d_inode, dentry->d_inode);
		inode_unlock(upperdentry->d_inode);

		अगर (winode)
			put_ग_लिखो_access(winode);
	पूर्ण
out_drop_ग_लिखो:
	ovl_drop_ग_लिखो(dentry);
out:
	वापस err;
पूर्ण

अटल व्योम ovl_map_dev_ino(काष्ठा dentry *dentry, काष्ठा kstat *stat, पूर्णांक fsid)
अणु
	bool samefs = ovl_same_fs(dentry->d_sb);
	अचिन्हित पूर्णांक xinobits = ovl_xino_bits(dentry->d_sb);
	अचिन्हित पूर्णांक xinoshअगरt = 64 - xinobits;

	अगर (samefs) अणु
		/*
		 * When all layers are on the same fs, all real inode
		 * number are unique, so we use the overlay st_dev,
		 * which is मित्रly to du -x.
		 */
		stat->dev = dentry->d_sb->s_dev;
		वापस;
	पूर्ण अन्यथा अगर (xinobits) अणु
		/*
		 * All inode numbers of underlying fs should not be using the
		 * high xinobits, so we use high xinobits to partition the
		 * overlay st_ino address space. The high bits holds the fsid
		 * (upper fsid is 0). The lowest xinobit is reserved क्रम mapping
		 * the non-persistent inode numbers range in हाल of overflow.
		 * This way all overlay inode numbers are unique and use the
		 * overlay st_dev.
		 */
		अगर (likely(!(stat->ino >> xinoshअगरt))) अणु
			stat->ino |= ((u64)fsid) << (xinoshअगरt + 1);
			stat->dev = dentry->d_sb->s_dev;
			वापस;
		पूर्ण अन्यथा अगर (ovl_xino_warn(dentry->d_sb)) अणु
			pr_warn_ratelimited("inode number too big (%pd2, ino=%llu, xinobits=%d)\n",
					    dentry, stat->ino, xinobits);
		पूर्ण
	पूर्ण

	/* The inode could not be mapped to a unअगरied st_ino address space */
	अगर (S_ISसूची(dentry->d_inode->i_mode)) अणु
		/*
		 * Always use the overlay st_dev क्रम directories, so 'find
		 * -xdev' will scan the entire overlay mount and won't cross the
		 * overlay mount boundaries.
		 *
		 * If not all layers are on the same fs the pair अणुreal st_ino;
		 * overlay st_devपूर्ण is not unique, so use the non persistent
		 * overlay st_ino क्रम directories.
		 */
		stat->dev = dentry->d_sb->s_dev;
		stat->ino = dentry->d_inode->i_ino;
	पूर्ण अन्यथा अणु
		/*
		 * For non-samefs setup, अगर we cannot map all layers st_ino
		 * to a unअगरied address space, we need to make sure that st_dev
		 * is unique per underlying fs, so we use the unique anonymous
		 * bdev asचिन्हित to the underlying fs.
		 */
		stat->dev = OVL_FS(dentry->d_sb)->fs[fsid].pseuकरो_dev;
	पूर्ण
पूर्ण

पूर्णांक ovl_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *dentry = path->dentry;
	क्रमागत ovl_path_type type;
	काष्ठा path realpath;
	स्थिर काष्ठा cred *old_cred;
	bool is_dir = S_ISसूची(dentry->d_inode->i_mode);
	पूर्णांक fsid = 0;
	पूर्णांक err;
	bool metacopy_blocks = false;

	metacopy_blocks = ovl_is_metacopy_dentry(dentry);

	type = ovl_path_real(dentry, &realpath);
	old_cred = ovl_override_creds(dentry->d_sb);
	err = vfs_getattr(&realpath, stat, request_mask, flags);
	अगर (err)
		जाओ out;

	/*
	 * For non-dir or same fs, we use st_ino of the copy up origin.
	 * This guaranties स्थिरant st_dev/st_ino across copy up.
	 * With xino feature and non-samefs, we use st_ino of the copy up
	 * origin masked with high bits that represent the layer id.
	 *
	 * If lower fileप्रणाली supports NFS file handles, this also guaranties
	 * persistent st_ino across mount cycle.
	 */
	अगर (!is_dir || ovl_same_dev(dentry->d_sb)) अणु
		अगर (!OVL_TYPE_UPPER(type)) अणु
			fsid = ovl_layer_lower(dentry)->fsid;
		पूर्ण अन्यथा अगर (OVL_TYPE_ORIGIN(type)) अणु
			काष्ठा kstat lowerstat;
			u32 lowermask = STATX_INO | STATX_BLOCKS |
					(!is_dir ? STATX_NLINK : 0);

			ovl_path_lower(dentry, &realpath);
			err = vfs_getattr(&realpath, &lowerstat,
					  lowermask, flags);
			अगर (err)
				जाओ out;

			/*
			 * Lower hardlinks may be broken on copy up to dअगरferent
			 * upper files, so we cannot use the lower origin st_ino
			 * क्रम those dअगरferent files, even क्रम the same fs हाल.
			 *
			 * Similarly, several redirected dirs can poपूर्णांक to the
			 * same dir on a lower layer. With the "verify_lower"
			 * feature, we करो not use the lower origin st_ino, अगर
			 * we haven't verअगरied that this redirect is unique.
			 *
			 * With inodes index enabled, it is safe to use st_ino
			 * of an indexed origin. The index validates that the
			 * upper hardlink is not broken and that a redirected
			 * dir is the only redirect to that origin.
			 */
			अगर (ovl_test_flag(OVL_INDEX, d_inode(dentry)) ||
			    (!ovl_verअगरy_lower(dentry->d_sb) &&
			     (is_dir || lowerstat.nlink == 1))) अणु
				fsid = ovl_layer_lower(dentry)->fsid;
				stat->ino = lowerstat.ino;
			पूर्ण

			/*
			 * If we are querying a metacopy dentry and lower
			 * dentry is data dentry, then use the blocks we
			 * queried just now. We करोn't have to करो additional
			 * vfs_getattr(). If lower itself is metacopy, then
			 * additional vfs_getattr() is unaव्योमable.
			 */
			अगर (metacopy_blocks &&
			    realpath.dentry == ovl_dentry_lowerdata(dentry)) अणु
				stat->blocks = lowerstat.blocks;
				metacopy_blocks = false;
			पूर्ण
		पूर्ण

		अगर (metacopy_blocks) अणु
			/*
			 * If lower is not same as lowerdata or अगर there was
			 * no origin on upper, we can end up here.
			 */
			काष्ठा kstat lowerdatastat;
			u32 lowermask = STATX_BLOCKS;

			ovl_path_lowerdata(dentry, &realpath);
			err = vfs_getattr(&realpath, &lowerdatastat,
					  lowermask, flags);
			अगर (err)
				जाओ out;
			stat->blocks = lowerdatastat.blocks;
		पूर्ण
	पूर्ण

	ovl_map_dev_ino(dentry, stat, fsid);

	/*
	 * It's probably not worth it to count subdirs to get the
	 * correct link count.  nlink=1 seems to pacअगरy 'find' and
	 * other utilities.
	 */
	अगर (is_dir && OVL_TYPE_MERGE(type))
		stat->nlink = 1;

	/*
	 * Return the overlay inode nlinks क्रम indexed upper inodes.
	 * Overlay inode nlink counts the जोड़ of the upper hardlinks
	 * and non-covered lower hardlinks. It करोes not include the upper
	 * index hardlink.
	 */
	अगर (!is_dir && ovl_test_flag(OVL_INDEX, d_inode(dentry)))
		stat->nlink = dentry->d_inode->i_nlink;

out:
	revert_creds(old_cred);

	वापस err;
पूर्ण

पूर्णांक ovl_permission(काष्ठा user_namespace *mnt_userns,
		   काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा inode *upperinode = ovl_inode_upper(inode);
	काष्ठा inode *realinode = upperinode ?: ovl_inode_lower(inode);
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक err;

	/* Careful in RCU walk mode */
	अगर (!realinode) अणु
		WARN_ON(!(mask & MAY_NOT_BLOCK));
		वापस -ECHILD;
	पूर्ण

	/*
	 * Check overlay inode with the creds of task and underlying inode
	 * with creds of mounter
	 */
	err = generic_permission(&init_user_ns, inode, mask);
	अगर (err)
		वापस err;

	old_cred = ovl_override_creds(inode->i_sb);
	अगर (!upperinode &&
	    !special_file(realinode->i_mode) && mask & MAY_WRITE) अणु
		mask &= ~(MAY_WRITE | MAY_APPEND);
		/* Make sure mounter can पढ़ो file क्रम copy up later */
		mask |= MAY_READ;
	पूर्ण
	err = inode_permission(&init_user_ns, realinode, mask);
	revert_creds(old_cred);

	वापस err;
पूर्ण

अटल स्थिर अक्षर *ovl_get_link(काष्ठा dentry *dentry,
				काष्ठा inode *inode,
				काष्ठा delayed_call *करोne)
अणु
	स्थिर काष्ठा cred *old_cred;
	स्थिर अक्षर *p;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	old_cred = ovl_override_creds(dentry->d_sb);
	p = vfs_get_link(ovl_dentry_real(dentry), करोne);
	revert_creds(old_cred);
	वापस p;
पूर्ण

bool ovl_is_निजी_xattr(काष्ठा super_block *sb, स्थिर अक्षर *name)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	अगर (ofs->config.userxattr)
		वापस म_भेदन(name, OVL_XATTR_USER_PREFIX,
			       माप(OVL_XATTR_USER_PREFIX) - 1) == 0;
	अन्यथा
		वापस म_भेदन(name, OVL_XATTR_TRUSTED_PREFIX,
			       माप(OVL_XATTR_TRUSTED_PREFIX) - 1) == 0;
पूर्ण

पूर्णांक ovl_xattr_set(काष्ठा dentry *dentry, काष्ठा inode *inode, स्थिर अक्षर *name,
		  स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा dentry *upperdentry = ovl_i_dentry_upper(inode);
	काष्ठा dentry *realdentry = upperdentry ?: ovl_dentry_lower(dentry);
	स्थिर काष्ठा cred *old_cred;

	err = ovl_want_ग_लिखो(dentry);
	अगर (err)
		जाओ out;

	अगर (!value && !upperdentry) अणु
		old_cred = ovl_override_creds(dentry->d_sb);
		err = vfs_getxattr(&init_user_ns, realdentry, name, शून्य, 0);
		revert_creds(old_cred);
		अगर (err < 0)
			जाओ out_drop_ग_लिखो;
	पूर्ण

	अगर (!upperdentry) अणु
		err = ovl_copy_up(dentry);
		अगर (err)
			जाओ out_drop_ग_लिखो;

		realdentry = ovl_dentry_upper(dentry);
	पूर्ण

	old_cred = ovl_override_creds(dentry->d_sb);
	अगर (value)
		err = vfs_setxattr(&init_user_ns, realdentry, name, value, size,
				   flags);
	अन्यथा अणु
		WARN_ON(flags != XATTR_REPLACE);
		err = vfs_हटाओxattr(&init_user_ns, realdentry, name);
	पूर्ण
	revert_creds(old_cred);

	/* copy c/mसमय */
	ovl_copyattr(d_inode(realdentry), inode);

out_drop_ग_लिखो:
	ovl_drop_ग_लिखो(dentry);
out:
	वापस err;
पूर्ण

पूर्णांक ovl_xattr_get(काष्ठा dentry *dentry, काष्ठा inode *inode, स्थिर अक्षर *name,
		  व्योम *value, माप_प्रकार size)
अणु
	sमाप_प्रकार res;
	स्थिर काष्ठा cred *old_cred;
	काष्ठा dentry *realdentry =
		ovl_i_dentry_upper(inode) ?: ovl_dentry_lower(dentry);

	old_cred = ovl_override_creds(dentry->d_sb);
	res = vfs_getxattr(&init_user_ns, realdentry, name, value, size);
	revert_creds(old_cred);
	वापस res;
पूर्ण

अटल bool ovl_can_list(काष्ठा super_block *sb, स्थिर अक्षर *s)
अणु
	/* Never list निजी (.overlay) */
	अगर (ovl_is_निजी_xattr(sb, s))
		वापस false;

	/* List all non-trusted xattrs */
	अगर (म_भेदन(s, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN) != 0)
		वापस true;

	/* list other trusted क्रम superuser only */
	वापस ns_capable_noaudit(&init_user_ns, CAP_SYS_ADMIN);
पूर्ण

sमाप_प्रकार ovl_listxattr(काष्ठा dentry *dentry, अक्षर *list, माप_प्रकार size)
अणु
	काष्ठा dentry *realdentry = ovl_dentry_real(dentry);
	sमाप_प्रकार res;
	माप_प्रकार len;
	अक्षर *s;
	स्थिर काष्ठा cred *old_cred;

	old_cred = ovl_override_creds(dentry->d_sb);
	res = vfs_listxattr(realdentry, list, size);
	revert_creds(old_cred);
	अगर (res <= 0 || size == 0)
		वापस res;

	/* filter out निजी xattrs */
	क्रम (s = list, len = res; len;) अणु
		माप_प्रकार slen = strnlen(s, len) + 1;

		/* underlying fs providing us with an broken xattr list? */
		अगर (WARN_ON(slen > len))
			वापस -EIO;

		len -= slen;
		अगर (!ovl_can_list(dentry->d_sb, s)) अणु
			res -= slen;
			स_हटाओ(s, s + slen, len);
		पूर्ण अन्यथा अणु
			s += slen;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

काष्ठा posix_acl *ovl_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा inode *realinode = ovl_inode_real(inode);
	स्थिर काष्ठा cred *old_cred;
	काष्ठा posix_acl *acl;

	अगर (!IS_ENABLED(CONFIG_FS_POSIX_ACL) || !IS_POSIXACL(realinode))
		वापस शून्य;

	old_cred = ovl_override_creds(inode->i_sb);
	acl = get_acl(realinode, type);
	revert_creds(old_cred);

	वापस acl;
पूर्ण

पूर्णांक ovl_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *ts, पूर्णांक flags)
अणु
	अगर (flags & S_ATIME) अणु
		काष्ठा ovl_fs *ofs = inode->i_sb->s_fs_info;
		काष्ठा path upperpath = अणु
			.mnt = ovl_upper_mnt(ofs),
			.dentry = ovl_upperdentry_dereference(OVL_I(inode)),
		पूर्ण;

		अगर (upperpath.dentry) अणु
			touch_aसमय(&upperpath);
			inode->i_aसमय = d_inode(upperpath.dentry)->i_aसमय;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ovl_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		      u64 start, u64 len)
अणु
	पूर्णांक err;
	काष्ठा inode *realinode = ovl_inode_realdata(inode);
	स्थिर काष्ठा cred *old_cred;

	अगर (!realinode->i_op->fiemap)
		वापस -EOPNOTSUPP;

	old_cred = ovl_override_creds(inode->i_sb);
	err = realinode->i_op->fiemap(realinode, fieinfo, start, len);
	revert_creds(old_cred);

	वापस err;
पूर्ण

/*
 * Work around the fact that security_file_ioctl() takes a file argument.
 * Introducing security_inode_fileattr_get/set() hooks would solve this issue
 * properly.
 */
अटल पूर्णांक ovl_security_fileattr(काष्ठा dentry *dentry, काष्ठा fileattr *fa,
				 bool set)
अणु
	काष्ठा path realpath;
	काष्ठा file *file;
	अचिन्हित पूर्णांक cmd;
	पूर्णांक err;

	ovl_path_real(dentry, &realpath);
	file = dentry_खोलो(&realpath, O_RDONLY, current_cred());
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	अगर (set)
		cmd = fa->fsx_valid ? FS_IOC_FSSETXATTR : FS_IOC_SETFLAGS;
	अन्यथा
		cmd = fa->fsx_valid ? FS_IOC_FSGETXATTR : FS_IOC_GETFLAGS;

	err = security_file_ioctl(file, cmd, 0);
	fput(file);

	वापस err;
पूर्ण

पूर्णांक ovl_fileattr_set(काष्ठा user_namespace *mnt_userns,
		     काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा dentry *upperdentry;
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक err;

	err = ovl_want_ग_लिखो(dentry);
	अगर (err)
		जाओ out;

	err = ovl_copy_up(dentry);
	अगर (!err) अणु
		upperdentry = ovl_dentry_upper(dentry);

		old_cred = ovl_override_creds(inode->i_sb);
		err = ovl_security_fileattr(dentry, fa, true);
		अगर (!err)
			err = vfs_fileattr_set(&init_user_ns, upperdentry, fa);
		revert_creds(old_cred);
		ovl_copyflags(ovl_inode_real(inode), inode);
	पूर्ण
	ovl_drop_ग_लिखो(dentry);
out:
	वापस err;
पूर्ण

पूर्णांक ovl_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा dentry *realdentry = ovl_dentry_real(dentry);
	स्थिर काष्ठा cred *old_cred;
	पूर्णांक err;

	old_cred = ovl_override_creds(inode->i_sb);
	err = ovl_security_fileattr(dentry, fa, false);
	अगर (!err)
		err = vfs_fileattr_get(realdentry, fa);
	revert_creds(old_cred);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा inode_operations ovl_file_inode_operations = अणु
	.setattr	= ovl_setattr,
	.permission	= ovl_permission,
	.getattr	= ovl_getattr,
	.listxattr	= ovl_listxattr,
	.get_acl	= ovl_get_acl,
	.update_समय	= ovl_update_समय,
	.fiemap		= ovl_fiemap,
	.fileattr_get	= ovl_fileattr_get,
	.fileattr_set	= ovl_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा inode_operations ovl_symlink_inode_operations = अणु
	.setattr	= ovl_setattr,
	.get_link	= ovl_get_link,
	.getattr	= ovl_getattr,
	.listxattr	= ovl_listxattr,
	.update_समय	= ovl_update_समय,
पूर्ण;

अटल स्थिर काष्ठा inode_operations ovl_special_inode_operations = अणु
	.setattr	= ovl_setattr,
	.permission	= ovl_permission,
	.getattr	= ovl_getattr,
	.listxattr	= ovl_listxattr,
	.get_acl	= ovl_get_acl,
	.update_समय	= ovl_update_समय,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations ovl_aops = अणु
	/* For O_सूचीECT dentry_खोलो() checks f_mapping->a_ops->direct_IO */
	.direct_IO		= noop_direct_IO,
पूर्ण;

/*
 * It is possible to stack overlayfs instance on top of another
 * overlayfs instance as lower layer. We need to annotate the
 * stackable i_mutex locks according to stack level of the super
 * block instance. An overlayfs instance can never be in stack
 * depth 0 (there is always a real fs below it).  An overlayfs
 * inode lock will use the lockdep annotation ovl_i_mutex_key[depth].
 *
 * For example, here is a snip from /proc/lockdep_chains after
 * dir_iterate of nested overlayfs:
 *
 * [...] &ovl_i_mutex_dir_key[depth]   (stack_depth=2)
 * [...] &ovl_i_mutex_dir_key[depth]#2 (stack_depth=1)
 * [...] &type->i_mutex_dir_key        (stack_depth=0)
 *
 * Locking order w.r.t ovl_want_ग_लिखो() is important क्रम nested overlayfs.
 *
 * This chain is valid:
 * - inode->i_rwsem			(inode_lock[2])
 * - upper_mnt->mnt_sb->s_ग_लिखोrs	(ovl_want_ग_लिखो[0])
 * - OVL_I(inode)->lock			(ovl_inode_lock[2])
 * - OVL_I(lowerinode)->lock		(ovl_inode_lock[1])
 *
 * And this chain is valid:
 * - inode->i_rwsem			(inode_lock[2])
 * - OVL_I(inode)->lock			(ovl_inode_lock[2])
 * - lowerinode->i_rwsem		(inode_lock[1])
 * - OVL_I(lowerinode)->lock		(ovl_inode_lock[1])
 *
 * But lowerinode->i_rwsem SHOULD NOT be acquired जबतक ovl_want_ग_लिखो() is
 * held, because it is in reverse order of the non-nested हाल using the same
 * upper fs:
 * - inode->i_rwsem			(inode_lock[1])
 * - upper_mnt->mnt_sb->s_ग_लिखोrs	(ovl_want_ग_लिखो[0])
 * - OVL_I(inode)->lock			(ovl_inode_lock[1])
 */
#घोषणा OVL_MAX_NESTING खाताSYSTEM_MAX_STACK_DEPTH

अटल अंतरभूत व्योम ovl_lockdep_annotate_inode_mutex_key(काष्ठा inode *inode)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	अटल काष्ठा lock_class_key ovl_i_mutex_key[OVL_MAX_NESTING];
	अटल काष्ठा lock_class_key ovl_i_mutex_dir_key[OVL_MAX_NESTING];
	अटल काष्ठा lock_class_key ovl_i_lock_key[OVL_MAX_NESTING];

	पूर्णांक depth = inode->i_sb->s_stack_depth - 1;

	अगर (WARN_ON_ONCE(depth < 0 || depth >= OVL_MAX_NESTING))
		depth = 0;

	अगर (S_ISसूची(inode->i_mode))
		lockdep_set_class(&inode->i_rwsem, &ovl_i_mutex_dir_key[depth]);
	अन्यथा
		lockdep_set_class(&inode->i_rwsem, &ovl_i_mutex_key[depth]);

	lockdep_set_class(&OVL_I(inode)->lock, &ovl_i_lock_key[depth]);
#पूर्ण_अगर
पूर्ण

अटल व्योम ovl_next_ino(काष्ठा inode *inode)
अणु
	काष्ठा ovl_fs *ofs = inode->i_sb->s_fs_info;

	inode->i_ino = atomic_दीर्घ_inc_वापस(&ofs->last_ino);
	अगर (unlikely(!inode->i_ino))
		inode->i_ino = atomic_दीर्घ_inc_वापस(&ofs->last_ino);
पूर्ण

अटल व्योम ovl_map_ino(काष्ठा inode *inode, अचिन्हित दीर्घ ino, पूर्णांक fsid)
अणु
	पूर्णांक xinobits = ovl_xino_bits(inode->i_sb);
	अचिन्हित पूर्णांक xinoshअगरt = 64 - xinobits;

	/*
	 * When d_ino is consistent with st_ino (samefs or i_ino has enough
	 * bits to encode layer), set the same value used क्रम st_ino to i_ino,
	 * so inode number exposed via /proc/locks and a like will be
	 * consistent with d_ino and st_ino values. An i_ino value inconsistent
	 * with d_ino also causes nfsd सूची_पढ़ोplus to fail.
	 */
	inode->i_ino = ino;
	अगर (ovl_same_fs(inode->i_sb)) अणु
		वापस;
	पूर्ण अन्यथा अगर (xinobits && likely(!(ino >> xinoshअगरt))) अणु
		inode->i_ino |= (अचिन्हित दीर्घ)fsid << (xinoshअगरt + 1);
		वापस;
	पूर्ण

	/*
	 * For directory inodes on non-samefs with xino disabled or xino
	 * overflow, we allocate a non-persistent inode number, to be used क्रम
	 * resolving st_ino collisions in ovl_map_dev_ino().
	 *
	 * To aव्योम ino collision with legitimate xino values from upper
	 * layer (fsid 0), use the lowest xinobit to map the non
	 * persistent inode numbers to the unअगरied st_ino address space.
	 */
	अगर (S_ISसूची(inode->i_mode)) अणु
		ovl_next_ino(inode);
		अगर (xinobits) अणु
			inode->i_ino &= ~0UL >> xinobits;
			inode->i_ino |= 1UL << xinoshअगरt;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ovl_inode_init(काष्ठा inode *inode, काष्ठा ovl_inode_params *oip,
		    अचिन्हित दीर्घ ino, पूर्णांक fsid)
अणु
	काष्ठा inode *realinode;

	अगर (oip->upperdentry)
		OVL_I(inode)->__upperdentry = oip->upperdentry;
	अगर (oip->lowerpath && oip->lowerpath->dentry)
		OVL_I(inode)->lower = igrab(d_inode(oip->lowerpath->dentry));
	अगर (oip->lowerdata)
		OVL_I(inode)->lowerdata = igrab(d_inode(oip->lowerdata));

	realinode = ovl_inode_real(inode);
	ovl_copyattr(realinode, inode);
	ovl_copyflags(realinode, inode);
	ovl_map_ino(inode, ino, fsid);
पूर्ण

अटल व्योम ovl_fill_inode(काष्ठा inode *inode, umode_t mode, dev_t rdev)
अणु
	inode->i_mode = mode;
	inode->i_flags |= S_NOCMTIME;
#अगर_घोषित CONFIG_FS_POSIX_ACL
	inode->i_acl = inode->i_शेष_acl = ACL_DONT_CACHE;
#पूर्ण_अगर

	ovl_lockdep_annotate_inode_mutex_key(inode);

	चयन (mode & S_IFMT) अणु
	हाल S_IFREG:
		inode->i_op = &ovl_file_inode_operations;
		inode->i_fop = &ovl_file_operations;
		inode->i_mapping->a_ops = &ovl_aops;
		अवरोध;

	हाल S_IFसूची:
		inode->i_op = &ovl_dir_inode_operations;
		inode->i_fop = &ovl_dir_operations;
		अवरोध;

	हाल S_IFLNK:
		inode->i_op = &ovl_symlink_inode_operations;
		अवरोध;

	शेष:
		inode->i_op = &ovl_special_inode_operations;
		init_special_inode(inode, mode, rdev);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * With inodes index enabled, an overlay inode nlink counts the जोड़ of upper
 * hardlinks and non-covered lower hardlinks. During the lअगरeसमय of a non-pure
 * upper inode, the following nlink modअगरying operations can happen:
 *
 * 1. Lower hardlink copy up
 * 2. Upper hardlink created, unlinked or नामd over
 * 3. Lower hardlink whiteout or नामd over
 *
 * For the first, copy up हाल, the जोड़ nlink करोes not change, whether the
 * operation succeeds or fails, but the upper inode nlink may change.
 * Thereक्रमe, beक्रमe copy up, we store the जोड़ nlink value relative to the
 * lower inode nlink in the index inode xattr .overlay.nlink.
 *
 * For the second, upper hardlink हाल, the जोड़ nlink should be incremented
 * or decremented IFF the operation succeeds, aligned with nlink change of the
 * upper inode. Thereक्रमe, beक्रमe link/unlink/नाम, we store the जोड़ nlink
 * value relative to the upper inode nlink in the index inode.
 *
 * For the last, lower cover up हाल, we simplअगरy things by preceding the
 * whiteout or cover up with copy up. This makes sure that there is an index
 * upper inode where the nlink xattr can be stored beक्रमe the copied up upper
 * entry is unlink.
 */
#घोषणा OVL_NLINK_ADD_UPPER	(1 << 0)

/*
 * On-disk क्रमmat क्रम indexed nlink:
 *
 * nlink relative to the upper inode - "U[+-]NUM"
 * nlink relative to the lower inode - "L[+-]NUM"
 */

अटल पूर्णांक ovl_set_nlink_common(काष्ठा dentry *dentry,
				काष्ठा dentry *realdentry, स्थिर अक्षर *क्रमmat)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा inode *realinode = d_inode(realdentry);
	अक्षर buf[13];
	पूर्णांक len;

	len = snम_लिखो(buf, माप(buf), क्रमmat,
		       (पूर्णांक) (inode->i_nlink - realinode->i_nlink));

	अगर (WARN_ON(len >= माप(buf)))
		वापस -EIO;

	वापस ovl_करो_setxattr(OVL_FS(inode->i_sb), ovl_dentry_upper(dentry),
			       OVL_XATTR_NLINK, buf, len);
पूर्ण

पूर्णांक ovl_set_nlink_upper(काष्ठा dentry *dentry)
अणु
	वापस ovl_set_nlink_common(dentry, ovl_dentry_upper(dentry), "U%+i");
पूर्ण

पूर्णांक ovl_set_nlink_lower(काष्ठा dentry *dentry)
अणु
	वापस ovl_set_nlink_common(dentry, ovl_dentry_lower(dentry), "L%+i");
पूर्ण

अचिन्हित पूर्णांक ovl_get_nlink(काष्ठा ovl_fs *ofs, काष्ठा dentry *lowerdentry,
			   काष्ठा dentry *upperdentry,
			   अचिन्हित पूर्णांक fallback)
अणु
	पूर्णांक nlink_dअगरf;
	पूर्णांक nlink;
	अक्षर buf[13];
	पूर्णांक err;

	अगर (!lowerdentry || !upperdentry || d_inode(lowerdentry)->i_nlink == 1)
		वापस fallback;

	err = ovl_करो_getxattr(ofs, upperdentry, OVL_XATTR_NLINK,
			      &buf, माप(buf) - 1);
	अगर (err < 0)
		जाओ fail;

	buf[err] = '\0';
	अगर ((buf[0] != 'L' && buf[0] != 'U') ||
	    (buf[1] != '+' && buf[1] != '-'))
		जाओ fail;

	err = kstrtoपूर्णांक(buf + 1, 10, &nlink_dअगरf);
	अगर (err < 0)
		जाओ fail;

	nlink = d_inode(buf[0] == 'L' ? lowerdentry : upperdentry)->i_nlink;
	nlink += nlink_dअगरf;

	अगर (nlink <= 0)
		जाओ fail;

	वापस nlink;

fail:
	pr_warn_ratelimited("failed to get index nlink (%pd2, err=%i)\n",
			    upperdentry, err);
	वापस fallback;
पूर्ण

काष्ठा inode *ovl_new_inode(काष्ठा super_block *sb, umode_t mode, dev_t rdev)
अणु
	काष्ठा inode *inode;

	inode = new_inode(sb);
	अगर (inode)
		ovl_fill_inode(inode, mode, rdev);

	वापस inode;
पूर्ण

अटल पूर्णांक ovl_inode_test(काष्ठा inode *inode, व्योम *data)
अणु
	वापस inode->i_निजी == data;
पूर्ण

अटल पूर्णांक ovl_inode_set(काष्ठा inode *inode, व्योम *data)
अणु
	inode->i_निजी = data;
	वापस 0;
पूर्ण

अटल bool ovl_verअगरy_inode(काष्ठा inode *inode, काष्ठा dentry *lowerdentry,
			     काष्ठा dentry *upperdentry, bool strict)
अणु
	/*
	 * For directories, @strict verअगरy from lookup path perक्रमms consistency
	 * checks, so शून्य lower/upper in dentry must match शून्य lower/upper in
	 * inode. Non @strict verअगरy from NFS handle decode path passes शून्य क्रम
	 * 'unknown' lower/upper.
	 */
	अगर (S_ISसूची(inode->i_mode) && strict) अणु
		/* Real lower dir moved to upper layer under us? */
		अगर (!lowerdentry && ovl_inode_lower(inode))
			वापस false;

		/* Lookup of an uncovered redirect origin? */
		अगर (!upperdentry && ovl_inode_upper(inode))
			वापस false;
	पूर्ण

	/*
	 * Allow non-शून्य lower inode in ovl_inode even अगर lowerdentry is शून्य.
	 * This happens when finding a copied up overlay inode क्रम a नामd
	 * or hardlinked overlay dentry and lower dentry cannot be followed
	 * by origin because lower fs करोes not support file handles.
	 */
	अगर (lowerdentry && ovl_inode_lower(inode) != d_inode(lowerdentry))
		वापस false;

	/*
	 * Allow non-शून्य __upperdentry in inode even अगर upperdentry is शून्य.
	 * This happens when finding a lower alias क्रम a copied up hard link.
	 */
	अगर (upperdentry && ovl_inode_upper(inode) != d_inode(upperdentry))
		वापस false;

	वापस true;
पूर्ण

काष्ठा inode *ovl_lookup_inode(काष्ठा super_block *sb, काष्ठा dentry *real,
			       bool is_upper)
अणु
	काष्ठा inode *inode, *key = d_inode(real);

	inode = ilookup5(sb, (अचिन्हित दीर्घ) key, ovl_inode_test, key);
	अगर (!inode)
		वापस शून्य;

	अगर (!ovl_verअगरy_inode(inode, is_upper ? शून्य : real,
			      is_upper ? real : शून्य, false)) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण

	वापस inode;
पूर्ण

bool ovl_lookup_trap_inode(काष्ठा super_block *sb, काष्ठा dentry *dir)
अणु
	काष्ठा inode *key = d_inode(dir);
	काष्ठा inode *trap;
	bool res;

	trap = ilookup5(sb, (अचिन्हित दीर्घ) key, ovl_inode_test, key);
	अगर (!trap)
		वापस false;

	res = IS_DEADसूची(trap) && !ovl_inode_upper(trap) &&
				  !ovl_inode_lower(trap);

	iput(trap);
	वापस res;
पूर्ण

/*
 * Create an inode cache entry क्रम layer root dir, that will पूर्णांकentionally
 * fail ovl_verअगरy_inode(), so any lookup that will find some layer root
 * will fail.
 */
काष्ठा inode *ovl_get_trap_inode(काष्ठा super_block *sb, काष्ठा dentry *dir)
अणु
	काष्ठा inode *key = d_inode(dir);
	काष्ठा inode *trap;

	अगर (!d_is_dir(dir))
		वापस ERR_PTR(-ENOTसूची);

	trap = iget5_locked(sb, (अचिन्हित दीर्घ) key, ovl_inode_test,
			    ovl_inode_set, key);
	अगर (!trap)
		वापस ERR_PTR(-ENOMEM);

	अगर (!(trap->i_state & I_NEW)) अणु
		/* Conflicting layer roots? */
		iput(trap);
		वापस ERR_PTR(-ELOOP);
	पूर्ण

	trap->i_mode = S_IFसूची;
	trap->i_flags = S_DEAD;
	unlock_new_inode(trap);

	वापस trap;
पूर्ण

/*
 * Does overlay inode need to be hashed by lower inode?
 */
अटल bool ovl_hash_bylower(काष्ठा super_block *sb, काष्ठा dentry *upper,
			     काष्ठा dentry *lower, bool index)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	/* No, अगर pure upper */
	अगर (!lower)
		वापस false;

	/* Yes, अगर alपढ़ोy indexed */
	अगर (index)
		वापस true;

	/* Yes, अगर won't be copied up */
	अगर (!ovl_upper_mnt(ofs))
		वापस true;

	/* No, अगर lower hardlink is or will be broken on copy up */
	अगर ((upper || !ovl_indexdir(sb)) &&
	    !d_is_dir(lower) && d_inode(lower)->i_nlink > 1)
		वापस false;

	/* No, अगर non-indexed upper with NFS export */
	अगर (sb->s_export_op && upper)
		वापस false;

	/* Otherwise, hash by lower inode क्रम fsnotअगरy */
	वापस true;
पूर्ण

अटल काष्ठा inode *ovl_iget5(काष्ठा super_block *sb, काष्ठा inode *newinode,
			       काष्ठा inode *key)
अणु
	वापस newinode ? inode_insert5(newinode, (अचिन्हित दीर्घ) key,
					 ovl_inode_test, ovl_inode_set, key) :
			  iget5_locked(sb, (अचिन्हित दीर्घ) key,
				       ovl_inode_test, ovl_inode_set, key);
पूर्ण

काष्ठा inode *ovl_get_inode(काष्ठा super_block *sb,
			    काष्ठा ovl_inode_params *oip)
अणु
	काष्ठा ovl_fs *ofs = OVL_FS(sb);
	काष्ठा dentry *upperdentry = oip->upperdentry;
	काष्ठा ovl_path *lowerpath = oip->lowerpath;
	काष्ठा inode *realinode = upperdentry ? d_inode(upperdentry) : शून्य;
	काष्ठा inode *inode;
	काष्ठा dentry *lowerdentry = lowerpath ? lowerpath->dentry : शून्य;
	bool bylower = ovl_hash_bylower(sb, upperdentry, lowerdentry,
					oip->index);
	पूर्णांक fsid = bylower ? lowerpath->layer->fsid : 0;
	bool is_dir;
	अचिन्हित दीर्घ ino = 0;
	पूर्णांक err = oip->newinode ? -EEXIST : -ENOMEM;

	अगर (!realinode)
		realinode = d_inode(lowerdentry);

	/*
	 * Copy up origin (lower) may exist क्रम non-indexed upper, but we must
	 * not use lower as hash key अगर this is a broken hardlink.
	 */
	is_dir = S_ISसूची(realinode->i_mode);
	अगर (upperdentry || bylower) अणु
		काष्ठा inode *key = d_inode(bylower ? lowerdentry :
						      upperdentry);
		अचिन्हित पूर्णांक nlink = is_dir ? 1 : realinode->i_nlink;

		inode = ovl_iget5(sb, oip->newinode, key);
		अगर (!inode)
			जाओ out_err;
		अगर (!(inode->i_state & I_NEW)) अणु
			/*
			 * Verअगरy that the underlying files stored in the inode
			 * match those in the dentry.
			 */
			अगर (!ovl_verअगरy_inode(inode, lowerdentry, upperdentry,
					      true)) अणु
				iput(inode);
				err = -ESTALE;
				जाओ out_err;
			पूर्ण

			dput(upperdentry);
			kमुक्त(oip->redirect);
			जाओ out;
		पूर्ण

		/* Recalculate nlink क्रम non-dir due to indexing */
		अगर (!is_dir)
			nlink = ovl_get_nlink(ofs, lowerdentry, upperdentry,
					      nlink);
		set_nlink(inode, nlink);
		ino = key->i_ino;
	पूर्ण अन्यथा अणु
		/* Lower hardlink that will be broken on copy up */
		inode = new_inode(sb);
		अगर (!inode) अणु
			err = -ENOMEM;
			जाओ out_err;
		पूर्ण
		ino = realinode->i_ino;
		fsid = lowerpath->layer->fsid;
	पूर्ण
	ovl_fill_inode(inode, realinode->i_mode, realinode->i_rdev);
	ovl_inode_init(inode, oip, ino, fsid);

	अगर (upperdentry && ovl_is_impuredir(sb, upperdentry))
		ovl_set_flag(OVL_IMPURE, inode);

	अगर (oip->index)
		ovl_set_flag(OVL_INDEX, inode);

	OVL_I(inode)->redirect = oip->redirect;

	अगर (bylower)
		ovl_set_flag(OVL_CONST_INO, inode);

	/* Check क्रम non-merge dir that may have whiteouts */
	अगर (is_dir) अणु
		अगर (((upperdentry && lowerdentry) || oip->numlower > 1) ||
		    ovl_check_origin_xattr(ofs, upperdentry ?: lowerdentry)) अणु
			ovl_set_flag(OVL_WHITEOUTS, inode);
		पूर्ण
	पूर्ण

	अगर (inode->i_state & I_NEW)
		unlock_new_inode(inode);
out:
	वापस inode;

out_err:
	pr_warn_ratelimited("failed to get inode (%i)\n", err);
	inode = ERR_PTR(err);
	जाओ out;
पूर्ण
