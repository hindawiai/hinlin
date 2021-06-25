<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/खोलो.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/namei.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/capability.h>
#समावेश <linux/securebits.h>
#समावेश <linux/security.h>
#समावेश <linux/mount.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/personality.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/audit.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/ima.h>
#समावेश <linux/dnotअगरy.h>
#समावेश <linux/compat.h>

#समावेश "internal.h"

पूर्णांक करो_truncate(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		loff_t length, अचिन्हित पूर्णांक समय_attrs, काष्ठा file *filp)
अणु
	पूर्णांक ret;
	काष्ठा iattr newattrs;

	/* Not pretty: "inode->i_size" shouldn't really be चिन्हित. But it is. */
	अगर (length < 0)
		वापस -EINVAL;

	newattrs.ia_size = length;
	newattrs.ia_valid = ATTR_SIZE | समय_attrs;
	अगर (filp) अणु
		newattrs.ia_file = filp;
		newattrs.ia_valid |= ATTR_खाता;
	पूर्ण

	/* Remove suid, sgid, and file capabilities on truncate too */
	ret = dentry_needs_हटाओ_privs(dentry);
	अगर (ret < 0)
		वापस ret;
	अगर (ret)
		newattrs.ia_valid |= ret | ATTR_FORCE;

	inode_lock(dentry->d_inode);
	/* Note any delegations or leases have alपढ़ोy been broken: */
	ret = notअगरy_change(mnt_userns, dentry, &newattrs, शून्य);
	inode_unlock(dentry->d_inode);
	वापस ret;
पूर्ण

दीर्घ vfs_truncate(स्थिर काष्ठा path *path, loff_t length)
अणु
	काष्ठा user_namespace *mnt_userns;
	काष्ठा inode *inode;
	दीर्घ error;

	inode = path->dentry->d_inode;

	/* For directories it's -EISसूची, क्रम other non-regulars - -EINVAL */
	अगर (S_ISसूची(inode->i_mode))
		वापस -EISसूची;
	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	error = mnt_want_ग_लिखो(path->mnt);
	अगर (error)
		जाओ out;

	mnt_userns = mnt_user_ns(path->mnt);
	error = inode_permission(mnt_userns, inode, MAY_WRITE);
	अगर (error)
		जाओ mnt_drop_ग_लिखो_and_out;

	error = -EPERM;
	अगर (IS_APPEND(inode))
		जाओ mnt_drop_ग_लिखो_and_out;

	error = get_ग_लिखो_access(inode);
	अगर (error)
		जाओ mnt_drop_ग_लिखो_and_out;

	/*
	 * Make sure that there are no leases.  get_ग_लिखो_access() protects
	 * against the truncate racing with a lease-granting setlease().
	 */
	error = अवरोध_lease(inode, O_WRONLY);
	अगर (error)
		जाओ put_ग_लिखो_and_out;

	error = locks_verअगरy_truncate(inode, शून्य, length);
	अगर (!error)
		error = security_path_truncate(path);
	अगर (!error)
		error = करो_truncate(mnt_userns, path->dentry, length, 0, शून्य);

put_ग_लिखो_and_out:
	put_ग_लिखो_access(inode);
mnt_drop_ग_लिखो_and_out:
	mnt_drop_ग_लिखो(path->mnt);
out:
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(vfs_truncate);

दीर्घ करो_sys_truncate(स्थिर अक्षर __user *pathname, loff_t length)
अणु
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_FOLLOW;
	काष्ठा path path;
	पूर्णांक error;

	अगर (length < 0)	/* sorry, but loff_t says... */
		वापस -EINVAL;

retry:
	error = user_path_at(AT_FDCWD, pathname, lookup_flags, &path);
	अगर (!error) अणु
		error = vfs_truncate(&path, length);
		path_put(&path);
	पूर्ण
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE2(truncate, स्थिर अक्षर __user *, path, दीर्घ, length)
अणु
	वापस करो_sys_truncate(path, length);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE2(truncate, स्थिर अक्षर __user *, path, compat_off_t, length)
अणु
	वापस करो_sys_truncate(path, length);
पूर्ण
#पूर्ण_अगर

दीर्घ करो_sys_ftruncate(अचिन्हित पूर्णांक fd, loff_t length, पूर्णांक small)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *dentry;
	काष्ठा fd f;
	पूर्णांक error;

	error = -EINVAL;
	अगर (length < 0)
		जाओ out;
	error = -EBADF;
	f = fdget(fd);
	अगर (!f.file)
		जाओ out;

	/* explicitly खोलोed as large or we are on 64-bit box */
	अगर (f.file->f_flags & O_LARGEखाता)
		small = 0;

	dentry = f.file->f_path.dentry;
	inode = dentry->d_inode;
	error = -EINVAL;
	अगर (!S_ISREG(inode->i_mode) || !(f.file->f_mode & FMODE_WRITE))
		जाओ out_putf;

	error = -EINVAL;
	/* Cannot ftruncate over 2^31 bytes without large file support */
	अगर (small && length > MAX_NON_LFS)
		जाओ out_putf;

	error = -EPERM;
	/* Check IS_APPEND on real upper inode */
	अगर (IS_APPEND(file_inode(f.file)))
		जाओ out_putf;
	sb_start_ग_लिखो(inode->i_sb);
	error = locks_verअगरy_truncate(inode, f.file, length);
	अगर (!error)
		error = security_path_truncate(&f.file->f_path);
	अगर (!error)
		error = करो_truncate(file_mnt_user_ns(f.file), dentry, length,
				    ATTR_MTIME | ATTR_CTIME, f.file);
	sb_end_ग_लिखो(inode->i_sb);
out_putf:
	fdput(f);
out:
	वापस error;
पूर्ण

SYSCALL_DEFINE2(ftruncate, अचिन्हित पूर्णांक, fd, अचिन्हित दीर्घ, length)
अणु
	वापस करो_sys_ftruncate(fd, length, 1);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE2(ftruncate, अचिन्हित पूर्णांक, fd, compat_uदीर्घ_t, length)
अणु
	वापस करो_sys_ftruncate(fd, length, 1);
पूर्ण
#पूर्ण_अगर

/* LFS versions of truncate are only needed on 32 bit machines */
#अगर BITS_PER_LONG == 32
SYSCALL_DEFINE2(truncate64, स्थिर अक्षर __user *, path, loff_t, length)
अणु
	वापस करो_sys_truncate(path, length);
पूर्ण

SYSCALL_DEFINE2(ftruncate64, अचिन्हित पूर्णांक, fd, loff_t, length)
अणु
	वापस करो_sys_ftruncate(fd, length, 0);
पूर्ण
#पूर्ण_अगर /* BITS_PER_LONG == 32 */


पूर्णांक vfs_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	दीर्घ ret;

	अगर (offset < 0 || len <= 0)
		वापस -EINVAL;

	/* Return error अगर mode is not supported */
	अगर (mode & ~FALLOC_FL_SUPPORTED_MASK)
		वापस -EOPNOTSUPP;

	/* Punch hole and zero range are mutually exclusive */
	अगर ((mode & (FALLOC_FL_PUNCH_HOLE | FALLOC_FL_ZERO_RANGE)) ==
	    (FALLOC_FL_PUNCH_HOLE | FALLOC_FL_ZERO_RANGE))
		वापस -EOPNOTSUPP;

	/* Punch hole must have keep size set */
	अगर ((mode & FALLOC_FL_PUNCH_HOLE) &&
	    !(mode & FALLOC_FL_KEEP_SIZE))
		वापस -EOPNOTSUPP;

	/* Collapse range should only be used exclusively. */
	अगर ((mode & FALLOC_FL_COLLAPSE_RANGE) &&
	    (mode & ~FALLOC_FL_COLLAPSE_RANGE))
		वापस -EINVAL;

	/* Insert range should only be used exclusively. */
	अगर ((mode & FALLOC_FL_INSERT_RANGE) &&
	    (mode & ~FALLOC_FL_INSERT_RANGE))
		वापस -EINVAL;

	/* Unshare range should only be used with allocate mode. */
	अगर ((mode & FALLOC_FL_UNSHARE_RANGE) &&
	    (mode & ~(FALLOC_FL_UNSHARE_RANGE | FALLOC_FL_KEEP_SIZE)))
		वापस -EINVAL;

	अगर (!(file->f_mode & FMODE_WRITE))
		वापस -EBADF;

	/*
	 * We can only allow pure fallocate on append only files
	 */
	अगर ((mode & ~FALLOC_FL_KEEP_SIZE) && IS_APPEND(inode))
		वापस -EPERM;

	अगर (IS_IMMUTABLE(inode))
		वापस -EPERM;

	/*
	 * We cannot allow any fallocate operation on an active swapfile
	 */
	अगर (IS_SWAPखाता(inode))
		वापस -ETXTBSY;

	/*
	 * Revalidate the ग_लिखो permissions, in हाल security policy has
	 * changed since the files were खोलोed.
	 */
	ret = security_file_permission(file, MAY_WRITE);
	अगर (ret)
		वापस ret;

	अगर (S_ISFIFO(inode->i_mode))
		वापस -ESPIPE;

	अगर (S_ISसूची(inode->i_mode))
		वापस -EISसूची;

	अगर (!S_ISREG(inode->i_mode) && !S_ISBLK(inode->i_mode))
		वापस -ENODEV;

	/* Check क्रम wrap through zero too */
	अगर (((offset + len) > inode->i_sb->s_maxbytes) || ((offset + len) < 0))
		वापस -EFBIG;

	अगर (!file->f_op->fallocate)
		वापस -EOPNOTSUPP;

	file_start_ग_लिखो(file);
	ret = file->f_op->fallocate(file, mode, offset, len);

	/*
	 * Create inotअगरy and fanotअगरy events.
	 *
	 * To keep the logic simple always create events अगर fallocate succeeds.
	 * This implies that events are even created अगर the file size reमुख्यs
	 * unchanged, e.g. when using flag FALLOC_FL_KEEP_SIZE.
	 */
	अगर (ret == 0)
		fsnotअगरy_modअगरy(file);

	file_end_ग_लिखो(file);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vfs_fallocate);

पूर्णांक ksys_fallocate(पूर्णांक fd, पूर्णांक mode, loff_t offset, loff_t len)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक error = -EBADF;

	अगर (f.file) अणु
		error = vfs_fallocate(f.file, mode, offset, len);
		fdput(f);
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE4(fallocate, पूर्णांक, fd, पूर्णांक, mode, loff_t, offset, loff_t, len)
अणु
	वापस ksys_fallocate(fd, mode, offset, len);
पूर्ण

/*
 * access() needs to use the real uid/gid, not the effective uid/gid.
 * We करो this by temporarily clearing all FS-related capabilities and
 * चयनing the fsuid/fsgid around to the real ones.
 */
अटल स्थिर काष्ठा cred *access_override_creds(व्योम)
अणु
	स्थिर काष्ठा cred *old_cred;
	काष्ठा cred *override_cred;

	override_cred = prepare_creds();
	अगर (!override_cred)
		वापस शून्य;

	override_cred->fsuid = override_cred->uid;
	override_cred->fsgid = override_cred->gid;

	अगर (!issecure(SECURE_NO_SETUID_FIXUP)) अणु
		/* Clear the capabilities अगर we चयन to a non-root user */
		kuid_t root_uid = make_kuid(override_cred->user_ns, 0);
		अगर (!uid_eq(override_cred->uid, root_uid))
			cap_clear(override_cred->cap_effective);
		अन्यथा
			override_cred->cap_effective =
				override_cred->cap_permitted;
	पूर्ण

	/*
	 * The new set of credentials can *only* be used in
	 * task-synchronous circumstances, and करोes not need
	 * RCU मुक्तing, unless somebody then takes a separate
	 * reference to it.
	 *
	 * NOTE! This is _only_ true because this credential
	 * is used purely क्रम override_creds() that installs
	 * it as the subjective cred. Other thपढ़ोs will be
	 * accessing ->real_cred, not the subjective cred.
	 *
	 * If somebody _करोes_ make a copy of this (using the
	 * 'get_current_cred()' function), that will clear the
	 * non_rcu field, because now that other user may be
	 * expecting RCU मुक्तing. But normal thपढ़ो-synchronous
	 * cred accesses will keep things non-RCY.
	 */
	override_cred->non_rcu = 1;

	old_cred = override_creds(override_cred);

	/* override_cred() माला_लो its own ref */
	put_cred(override_cred);

	वापस old_cred;
पूर्ण

अटल दीर्घ करो_faccessat(पूर्णांक dfd, स्थिर अक्षर __user *filename, पूर्णांक mode, पूर्णांक flags)
अणु
	काष्ठा path path;
	काष्ठा inode *inode;
	पूर्णांक res;
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_FOLLOW;
	स्थिर काष्ठा cred *old_cred = शून्य;

	अगर (mode & ~S_IRWXO)	/* where's F_OK, X_OK, W_OK, R_OK? */
		वापस -EINVAL;

	अगर (flags & ~(AT_EACCESS | AT_SYMLINK_NOFOLLOW | AT_EMPTY_PATH))
		वापस -EINVAL;

	अगर (flags & AT_SYMLINK_NOFOLLOW)
		lookup_flags &= ~LOOKUP_FOLLOW;
	अगर (flags & AT_EMPTY_PATH)
		lookup_flags |= LOOKUP_EMPTY;

	अगर (!(flags & AT_EACCESS)) अणु
		old_cred = access_override_creds();
		अगर (!old_cred)
			वापस -ENOMEM;
	पूर्ण

retry:
	res = user_path_at(dfd, filename, lookup_flags, &path);
	अगर (res)
		जाओ out;

	inode = d_backing_inode(path.dentry);

	अगर ((mode & MAY_EXEC) && S_ISREG(inode->i_mode)) अणु
		/*
		 * MAY_EXEC on regular files is denied अगर the fs is mounted
		 * with the "noexec" flag.
		 */
		res = -EACCES;
		अगर (path_noexec(&path))
			जाओ out_path_release;
	पूर्ण

	res = inode_permission(mnt_user_ns(path.mnt), inode, mode | MAY_ACCESS);
	/* SuS v2 requires we report a पढ़ो only fs too */
	अगर (res || !(mode & S_IWOTH) || special_file(inode->i_mode))
		जाओ out_path_release;
	/*
	 * This is a rare हाल where using __mnt_is_पढ़ोonly()
	 * is OK without a mnt_want/drop_ग_लिखो() pair.  Since
	 * no actual ग_लिखो to the fs is perक्रमmed here, we करो
	 * not need to telegraph to that to anyone.
	 *
	 * By करोing this, we accept that this access is
	 * inherently racy and know that the fs may change
	 * state beक्रमe we even see this result.
	 */
	अगर (__mnt_is_पढ़ोonly(path.mnt))
		res = -EROFS;

out_path_release:
	path_put(&path);
	अगर (retry_estale(res, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
out:
	अगर (old_cred)
		revert_creds(old_cred);

	वापस res;
पूर्ण

SYSCALL_DEFINE3(faccessat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename, पूर्णांक, mode)
अणु
	वापस करो_faccessat(dfd, filename, mode, 0);
पूर्ण

SYSCALL_DEFINE4(faccessat2, पूर्णांक, dfd, स्थिर अक्षर __user *, filename, पूर्णांक, mode,
		पूर्णांक, flags)
अणु
	वापस करो_faccessat(dfd, filename, mode, flags);
पूर्ण

SYSCALL_DEFINE2(access, स्थिर अक्षर __user *, filename, पूर्णांक, mode)
अणु
	वापस करो_faccessat(AT_FDCWD, filename, mode, 0);
पूर्ण

SYSCALL_DEFINE1(स_बदलो, स्थिर अक्षर __user *, filename)
अणु
	काष्ठा path path;
	पूर्णांक error;
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_FOLLOW | LOOKUP_सूचीECTORY;
retry:
	error = user_path_at(AT_FDCWD, filename, lookup_flags, &path);
	अगर (error)
		जाओ out;

	error = path_permission(&path, MAY_EXEC | MAY_CHसूची);
	अगर (error)
		जाओ dput_and_out;

	set_fs_pwd(current->fs, &path);

dput_and_out:
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
out:
	वापस error;
पूर्ण

SYSCALL_DEFINE1(fस_बदलो, अचिन्हित पूर्णांक, fd)
अणु
	काष्ठा fd f = fdget_raw(fd);
	पूर्णांक error;

	error = -EBADF;
	अगर (!f.file)
		जाओ out;

	error = -ENOTसूची;
	अगर (!d_can_lookup(f.file->f_path.dentry))
		जाओ out_putf;

	error = file_permission(f.file, MAY_EXEC | MAY_CHसूची);
	अगर (!error)
		set_fs_pwd(current->fs, &f.file->f_path);
out_putf:
	fdput(f);
out:
	वापस error;
पूर्ण

SYSCALL_DEFINE1(chroot, स्थिर अक्षर __user *, filename)
अणु
	काष्ठा path path;
	पूर्णांक error;
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_FOLLOW | LOOKUP_सूचीECTORY;
retry:
	error = user_path_at(AT_FDCWD, filename, lookup_flags, &path);
	अगर (error)
		जाओ out;

	error = path_permission(&path, MAY_EXEC | MAY_CHसूची);
	अगर (error)
		जाओ dput_and_out;

	error = -EPERM;
	अगर (!ns_capable(current_user_ns(), CAP_SYS_CHROOT))
		जाओ dput_and_out;
	error = security_path_chroot(&path);
	अगर (error)
		जाओ dput_and_out;

	set_fs_root(current->fs, &path);
	error = 0;
dput_and_out:
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
out:
	वापस error;
पूर्ण

पूर्णांक chmod_common(स्थिर काष्ठा path *path, umode_t mode)
अणु
	काष्ठा inode *inode = path->dentry->d_inode;
	काष्ठा inode *delegated_inode = शून्य;
	काष्ठा iattr newattrs;
	पूर्णांक error;

	error = mnt_want_ग_लिखो(path->mnt);
	अगर (error)
		वापस error;
retry_deleg:
	inode_lock(inode);
	error = security_path_chmod(path, mode);
	अगर (error)
		जाओ out_unlock;
	newattrs.ia_mode = (mode & S_IALLUGO) | (inode->i_mode & ~S_IALLUGO);
	newattrs.ia_valid = ATTR_MODE | ATTR_CTIME;
	error = notअगरy_change(mnt_user_ns(path->mnt), path->dentry,
			      &newattrs, &delegated_inode);
out_unlock:
	inode_unlock(inode);
	अगर (delegated_inode) अणु
		error = अवरोध_deleg_रुको(&delegated_inode);
		अगर (!error)
			जाओ retry_deleg;
	पूर्ण
	mnt_drop_ग_लिखो(path->mnt);
	वापस error;
पूर्ण

पूर्णांक vfs_fchmod(काष्ठा file *file, umode_t mode)
अणु
	audit_file(file);
	वापस chmod_common(&file->f_path, mode);
पूर्ण

SYSCALL_DEFINE2(fchmod, अचिन्हित पूर्णांक, fd, umode_t, mode)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक err = -EBADF;

	अगर (f.file) अणु
		err = vfs_fchmod(f.file, mode);
		fdput(f);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक करो_fchmodat(पूर्णांक dfd, स्थिर अक्षर __user *filename, umode_t mode)
अणु
	काष्ठा path path;
	पूर्णांक error;
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_FOLLOW;
retry:
	error = user_path_at(dfd, filename, lookup_flags, &path);
	अगर (!error) अणु
		error = chmod_common(&path, mode);
		path_put(&path);
		अगर (retry_estale(error, lookup_flags)) अणु
			lookup_flags |= LOOKUP_REVAL;
			जाओ retry;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE3(fchmodat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename,
		umode_t, mode)
अणु
	वापस करो_fchmodat(dfd, filename, mode);
पूर्ण

SYSCALL_DEFINE2(chmod, स्थिर अक्षर __user *, filename, umode_t, mode)
अणु
	वापस करो_fchmodat(AT_FDCWD, filename, mode);
पूर्ण

पूर्णांक chown_common(स्थिर काष्ठा path *path, uid_t user, gid_t group)
अणु
	काष्ठा user_namespace *mnt_userns;
	काष्ठा inode *inode = path->dentry->d_inode;
	काष्ठा inode *delegated_inode = शून्य;
	पूर्णांक error;
	काष्ठा iattr newattrs;
	kuid_t uid;
	kgid_t gid;

	uid = make_kuid(current_user_ns(), user);
	gid = make_kgid(current_user_ns(), group);

	mnt_userns = mnt_user_ns(path->mnt);
	uid = kuid_from_mnt(mnt_userns, uid);
	gid = kgid_from_mnt(mnt_userns, gid);

retry_deleg:
	newattrs.ia_valid =  ATTR_CTIME;
	अगर (user != (uid_t) -1) अणु
		अगर (!uid_valid(uid))
			वापस -EINVAL;
		newattrs.ia_valid |= ATTR_UID;
		newattrs.ia_uid = uid;
	पूर्ण
	अगर (group != (gid_t) -1) अणु
		अगर (!gid_valid(gid))
			वापस -EINVAL;
		newattrs.ia_valid |= ATTR_GID;
		newattrs.ia_gid = gid;
	पूर्ण
	अगर (!S_ISसूची(inode->i_mode))
		newattrs.ia_valid |=
			ATTR_KILL_SUID | ATTR_KILL_SGID | ATTR_KILL_PRIV;
	inode_lock(inode);
	error = security_path_chown(path, uid, gid);
	अगर (!error)
		error = notअगरy_change(mnt_userns, path->dentry, &newattrs,
				      &delegated_inode);
	inode_unlock(inode);
	अगर (delegated_inode) अणु
		error = अवरोध_deleg_रुको(&delegated_inode);
		अगर (!error)
			जाओ retry_deleg;
	पूर्ण
	वापस error;
पूर्ण

पूर्णांक करो_fchownat(पूर्णांक dfd, स्थिर अक्षर __user *filename, uid_t user, gid_t group,
		पूर्णांक flag)
अणु
	काष्ठा path path;
	पूर्णांक error = -EINVAL;
	पूर्णांक lookup_flags;

	अगर ((flag & ~(AT_SYMLINK_NOFOLLOW | AT_EMPTY_PATH)) != 0)
		जाओ out;

	lookup_flags = (flag & AT_SYMLINK_NOFOLLOW) ? 0 : LOOKUP_FOLLOW;
	अगर (flag & AT_EMPTY_PATH)
		lookup_flags |= LOOKUP_EMPTY;
retry:
	error = user_path_at(dfd, filename, lookup_flags, &path);
	अगर (error)
		जाओ out;
	error = mnt_want_ग_लिखो(path.mnt);
	अगर (error)
		जाओ out_release;
	error = chown_common(&path, user, group);
	mnt_drop_ग_लिखो(path.mnt);
out_release:
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
out:
	वापस error;
पूर्ण

SYSCALL_DEFINE5(fchownat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename, uid_t, user,
		gid_t, group, पूर्णांक, flag)
अणु
	वापस करो_fchownat(dfd, filename, user, group, flag);
पूर्ण

SYSCALL_DEFINE3(chown, स्थिर अक्षर __user *, filename, uid_t, user, gid_t, group)
अणु
	वापस करो_fchownat(AT_FDCWD, filename, user, group, 0);
पूर्ण

SYSCALL_DEFINE3(lchown, स्थिर अक्षर __user *, filename, uid_t, user, gid_t, group)
अणु
	वापस करो_fchownat(AT_FDCWD, filename, user, group,
			   AT_SYMLINK_NOFOLLOW);
पूर्ण

पूर्णांक vfs_fchown(काष्ठा file *file, uid_t user, gid_t group)
अणु
	पूर्णांक error;

	error = mnt_want_ग_लिखो_file(file);
	अगर (error)
		वापस error;
	audit_file(file);
	error = chown_common(&file->f_path, user, group);
	mnt_drop_ग_लिखो_file(file);
	वापस error;
पूर्ण

पूर्णांक ksys_fchown(अचिन्हित पूर्णांक fd, uid_t user, gid_t group)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक error = -EBADF;

	अगर (f.file) अणु
		error = vfs_fchown(f.file, user, group);
		fdput(f);
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE3(fchown, अचिन्हित पूर्णांक, fd, uid_t, user, gid_t, group)
अणु
	वापस ksys_fchown(fd, user, group);
पूर्ण

अटल पूर्णांक करो_dentry_खोलो(काष्ठा file *f,
			  काष्ठा inode *inode,
			  पूर्णांक (*खोलो)(काष्ठा inode *, काष्ठा file *))
अणु
	अटल स्थिर काष्ठा file_operations empty_fops = अणुपूर्ण;
	पूर्णांक error;

	path_get(&f->f_path);
	f->f_inode = inode;
	f->f_mapping = inode->i_mapping;
	f->f_wb_err = filemap_sample_wb_err(f->f_mapping);
	f->f_sb_err = file_sample_sb_err(f);

	अगर (unlikely(f->f_flags & O_PATH)) अणु
		f->f_mode = FMODE_PATH | FMODE_OPENED;
		f->f_op = &empty_fops;
		वापस 0;
	पूर्ण

	अगर (f->f_mode & FMODE_WRITE && !special_file(inode->i_mode)) अणु
		error = get_ग_लिखो_access(inode);
		अगर (unlikely(error))
			जाओ cleanup_file;
		error = __mnt_want_ग_लिखो(f->f_path.mnt);
		अगर (unlikely(error)) अणु
			put_ग_लिखो_access(inode);
			जाओ cleanup_file;
		पूर्ण
		f->f_mode |= FMODE_WRITER;
	पूर्ण

	/* POSIX.1-2008/SUSv4 Section XSI 2.9.7 */
	अगर (S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode))
		f->f_mode |= FMODE_ATOMIC_POS;

	f->f_op = fops_get(inode->i_fop);
	अगर (WARN_ON(!f->f_op)) अणु
		error = -ENODEV;
		जाओ cleanup_all;
	पूर्ण

	error = security_file_खोलो(f);
	अगर (error)
		जाओ cleanup_all;

	error = अवरोध_lease(locks_inode(f), f->f_flags);
	अगर (error)
		जाओ cleanup_all;

	/* normally all 3 are set; ->खोलो() can clear them अगर needed */
	f->f_mode |= FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE;
	अगर (!खोलो)
		खोलो = f->f_op->खोलो;
	अगर (खोलो) अणु
		error = खोलो(inode, f);
		अगर (error)
			जाओ cleanup_all;
	पूर्ण
	f->f_mode |= FMODE_OPENED;
	अगर ((f->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ)
		i_पढ़ोcount_inc(inode);
	अगर ((f->f_mode & FMODE_READ) &&
	     likely(f->f_op->पढ़ो || f->f_op->पढ़ो_iter))
		f->f_mode |= FMODE_CAN_READ;
	अगर ((f->f_mode & FMODE_WRITE) &&
	     likely(f->f_op->ग_लिखो || f->f_op->ग_लिखो_iter))
		f->f_mode |= FMODE_CAN_WRITE;

	f->f_ग_लिखो_hपूर्णांक = WRITE_LIFE_NOT_SET;
	f->f_flags &= ~(O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC);

	file_ra_state_init(&f->f_ra, f->f_mapping->host->i_mapping);

	/* NB: we're sure to have correct a_ops only after f_op->खोलो */
	अगर (f->f_flags & O_सूचीECT) अणु
		अगर (!f->f_mapping->a_ops || !f->f_mapping->a_ops->direct_IO)
			वापस -EINVAL;
	पूर्ण

	/*
	 * XXX: Huge page cache करोesn't support writing yet. Drop all page
	 * cache क्रम this file beक्रमe processing ग_लिखोs.
	 */
	अगर ((f->f_mode & FMODE_WRITE) && filemap_nr_thps(inode->i_mapping))
		truncate_pagecache(inode, 0);

	वापस 0;

cleanup_all:
	अगर (WARN_ON_ONCE(error > 0))
		error = -EINVAL;
	fops_put(f->f_op);
	अगर (f->f_mode & FMODE_WRITER) अणु
		put_ग_लिखो_access(inode);
		__mnt_drop_ग_लिखो(f->f_path.mnt);
	पूर्ण
cleanup_file:
	path_put(&f->f_path);
	f->f_path.mnt = शून्य;
	f->f_path.dentry = शून्य;
	f->f_inode = शून्य;
	वापस error;
पूर्ण

/**
 * finish_खोलो - finish खोलोing a file
 * @file: file poपूर्णांकer
 * @dentry: poपूर्णांकer to dentry
 * @खोलो: खोलो callback
 * @खोलोed: state of खोलो
 *
 * This can be used to finish खोलोing a file passed to i_op->atomic_खोलो().
 *
 * If the खोलो callback is set to शून्य, then the standard f_op->खोलो()
 * fileप्रणाली callback is substituted.
 *
 * NB: the dentry reference is _not_ consumed.  If, क्रम example, the dentry is
 * the वापस value of d_splice_alias(), then the caller needs to perक्रमm dput()
 * on it after finish_खोलो().
 *
 * Returns zero on success or -त्रुटि_सं अगर the खोलो failed.
 */
पूर्णांक finish_खोलो(काष्ठा file *file, काष्ठा dentry *dentry,
		पूर्णांक (*खोलो)(काष्ठा inode *, काष्ठा file *))
अणु
	BUG_ON(file->f_mode & FMODE_OPENED); /* once it's opened, it's खोलोed */

	file->f_path.dentry = dentry;
	वापस करो_dentry_खोलो(file, d_backing_inode(dentry), खोलो);
पूर्ण
EXPORT_SYMBOL(finish_खोलो);

/**
 * finish_no_खोलो - finish ->atomic_खोलो() without खोलोing the file
 *
 * @file: file poपूर्णांकer
 * @dentry: dentry or शून्य (as वापसed from ->lookup())
 *
 * This can be used to set the result of a successful lookup in ->atomic_खोलो().
 *
 * NB: unlike finish_खोलो() this function करोes consume the dentry reference and
 * the caller need not dput() it.
 *
 * Returns "0" which must be the वापस value of ->atomic_खोलो() after having
 * called this function.
 */
पूर्णांक finish_no_खोलो(काष्ठा file *file, काष्ठा dentry *dentry)
अणु
	file->f_path.dentry = dentry;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(finish_no_खोलो);

अक्षर *file_path(काष्ठा file *filp, अक्षर *buf, पूर्णांक buflen)
अणु
	वापस d_path(&filp->f_path, buf, buflen);
पूर्ण
EXPORT_SYMBOL(file_path);

/**
 * vfs_खोलो - खोलो the file at the given path
 * @path: path to खोलो
 * @file: newly allocated file with f_flag initialized
 * @cred: credentials to use
 */
पूर्णांक vfs_खोलो(स्थिर काष्ठा path *path, काष्ठा file *file)
अणु
	file->f_path = *path;
	वापस करो_dentry_खोलो(file, d_backing_inode(path->dentry), शून्य);
पूर्ण

काष्ठा file *dentry_खोलो(स्थिर काष्ठा path *path, पूर्णांक flags,
			 स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक error;
	काष्ठा file *f;

	validate_creds(cred);

	/* We must always pass in a valid mount poपूर्णांकer. */
	BUG_ON(!path->mnt);

	f = alloc_empty_file(flags, cred);
	अगर (!IS_ERR(f)) अणु
		error = vfs_खोलो(path, f);
		अगर (error) अणु
			fput(f);
			f = ERR_PTR(error);
		पूर्ण
	पूर्ण
	वापस f;
पूर्ण
EXPORT_SYMBOL(dentry_खोलो);

काष्ठा file *खोलो_with_fake_path(स्थिर काष्ठा path *path, पूर्णांक flags,
				काष्ठा inode *inode, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा file *f = alloc_empty_file_noaccount(flags, cred);
	अगर (!IS_ERR(f)) अणु
		पूर्णांक error;

		f->f_path = *path;
		error = करो_dentry_खोलो(f, inode, शून्य);
		अगर (error) अणु
			fput(f);
			f = ERR_PTR(error);
		पूर्ण
	पूर्ण
	वापस f;
पूर्ण
EXPORT_SYMBOL(खोलो_with_fake_path);

#घोषणा WILL_CREATE(flags)	(flags & (O_CREAT | __O_TMPखाता))
#घोषणा O_PATH_FLAGS		(O_सूचीECTORY | O_NOFOLLOW | O_PATH | O_CLOEXEC)

अंतरभूत काष्ठा खोलो_how build_खोलो_how(पूर्णांक flags, umode_t mode)
अणु
	काष्ठा खोलो_how how = अणु
		.flags = flags & VALID_OPEN_FLAGS,
		.mode = mode & S_IALLUGO,
	पूर्ण;

	/* O_PATH beats everything अन्यथा. */
	अगर (how.flags & O_PATH)
		how.flags &= O_PATH_FLAGS;
	/* Modes should only be set क्रम create-like flags. */
	अगर (!WILL_CREATE(how.flags))
		how.mode = 0;
	वापस how;
पूर्ण

अंतरभूत पूर्णांक build_खोलो_flags(स्थिर काष्ठा खोलो_how *how, काष्ठा खोलो_flags *op)
अणु
	पूर्णांक flags = how->flags;
	पूर्णांक lookup_flags = 0;
	पूर्णांक acc_mode = ACC_MODE(flags);

	/* Must never be set by userspace */
	flags &= ~(FMODE_NONOTIFY | O_CLOEXEC);

	/*
	 * Older syscalls implicitly clear all of the invalid flags or argument
	 * values beक्रमe calling build_खोलो_flags(), but खोलोat2(2) checks all
	 * of its arguments.
	 */
	अगर (flags & ~VALID_OPEN_FLAGS)
		वापस -EINVAL;
	अगर (how->resolve & ~VALID_RESOLVE_FLAGS)
		वापस -EINVAL;

	/* Scoping flags are mutually exclusive. */
	अगर ((how->resolve & RESOLVE_BENEATH) && (how->resolve & RESOLVE_IN_ROOT))
		वापस -EINVAL;

	/* Deal with the mode. */
	अगर (WILL_CREATE(flags)) अणु
		अगर (how->mode & ~S_IALLUGO)
			वापस -EINVAL;
		op->mode = how->mode | S_IFREG;
	पूर्ण अन्यथा अणु
		अगर (how->mode != 0)
			वापस -EINVAL;
		op->mode = 0;
	पूर्ण

	/*
	 * In order to ensure programs get explicit errors when trying to use
	 * O_TMPखाता on old kernels, O_TMPखाता is implemented such that it
	 * looks like (O_सूचीECTORY|O_RDWR & ~O_CREAT) to old kernels. But we
	 * have to require userspace to explicitly set it.
	 */
	अगर (flags & __O_TMPखाता) अणु
		अगर ((flags & O_TMPखाता_MASK) != O_TMPखाता)
			वापस -EINVAL;
		अगर (!(acc_mode & MAY_WRITE))
			वापस -EINVAL;
	पूर्ण
	अगर (flags & O_PATH) अणु
		/* O_PATH only permits certain other flags to be set. */
		अगर (flags & ~O_PATH_FLAGS)
			वापस -EINVAL;
		acc_mode = 0;
	पूर्ण

	/*
	 * O_SYNC is implemented as __O_SYNC|O_DSYNC.  As many places only
	 * check क्रम O_DSYNC अगर the need any syncing at all we enक्रमce it's
	 * always set instead of having to deal with possibly weird behaviour
	 * क्रम malicious applications setting only __O_SYNC.
	 */
	अगर (flags & __O_SYNC)
		flags |= O_DSYNC;

	op->खोलो_flag = flags;

	/* O_TRUNC implies we need access checks क्रम ग_लिखो permissions */
	अगर (flags & O_TRUNC)
		acc_mode |= MAY_WRITE;

	/* Allow the LSM permission hook to distinguish append
	   access from general ग_लिखो access. */
	अगर (flags & O_APPEND)
		acc_mode |= MAY_APPEND;

	op->acc_mode = acc_mode;

	op->पूर्णांकent = flags & O_PATH ? 0 : LOOKUP_OPEN;

	अगर (flags & O_CREAT) अणु
		op->पूर्णांकent |= LOOKUP_CREATE;
		अगर (flags & O_EXCL) अणु
			op->पूर्णांकent |= LOOKUP_EXCL;
			flags |= O_NOFOLLOW;
		पूर्ण
	पूर्ण

	अगर (flags & O_सूचीECTORY)
		lookup_flags |= LOOKUP_सूचीECTORY;
	अगर (!(flags & O_NOFOLLOW))
		lookup_flags |= LOOKUP_FOLLOW;

	अगर (how->resolve & RESOLVE_NO_XDEV)
		lookup_flags |= LOOKUP_NO_XDEV;
	अगर (how->resolve & RESOLVE_NO_MAGICLINKS)
		lookup_flags |= LOOKUP_NO_MAGICLINKS;
	अगर (how->resolve & RESOLVE_NO_SYMLINKS)
		lookup_flags |= LOOKUP_NO_SYMLINKS;
	अगर (how->resolve & RESOLVE_BENEATH)
		lookup_flags |= LOOKUP_BENEATH;
	अगर (how->resolve & RESOLVE_IN_ROOT)
		lookup_flags |= LOOKUP_IN_ROOT;
	अगर (how->resolve & RESOLVE_CACHED) अणु
		/* Don't bother even trying क्रम create/truncate/क्षणिक_ख खोलो */
		अगर (flags & (O_TRUNC | O_CREAT | O_TMPखाता))
			वापस -EAGAIN;
		lookup_flags |= LOOKUP_CACHED;
	पूर्ण

	op->lookup_flags = lookup_flags;
	वापस 0;
पूर्ण

/**
 * file_खोलो_name - खोलो file and वापस file poपूर्णांकer
 *
 * @name:	काष्ठा filename containing path to खोलो
 * @flags:	खोलो flags as per the खोलो(2) second argument
 * @mode:	mode क्रम the new file अगर O_CREAT is set, अन्यथा ignored
 *
 * This is the helper to खोलो a file from kernelspace अगर you really
 * have to.  But in generally you should not करो this, so please move
 * aदीर्घ, nothing to see here..
 */
काष्ठा file *file_खोलो_name(काष्ठा filename *name, पूर्णांक flags, umode_t mode)
अणु
	काष्ठा खोलो_flags op;
	काष्ठा खोलो_how how = build_खोलो_how(flags, mode);
	पूर्णांक err = build_खोलो_flags(&how, &op);
	अगर (err)
		वापस ERR_PTR(err);
	वापस करो_filp_खोलो(AT_FDCWD, name, &op);
पूर्ण

/**
 * filp_खोलो - खोलो file and वापस file poपूर्णांकer
 *
 * @filename:	path to खोलो
 * @flags:	खोलो flags as per the खोलो(2) second argument
 * @mode:	mode क्रम the new file अगर O_CREAT is set, अन्यथा ignored
 *
 * This is the helper to खोलो a file from kernelspace अगर you really
 * have to.  But in generally you should not करो this, so please move
 * aदीर्घ, nothing to see here..
 */
काष्ठा file *filp_खोलो(स्थिर अक्षर *filename, पूर्णांक flags, umode_t mode)
अणु
	काष्ठा filename *name = getname_kernel(filename);
	काष्ठा file *file = ERR_CAST(name);
	
	अगर (!IS_ERR(name)) अणु
		file = file_खोलो_name(name, flags, mode);
		putname(name);
	पूर्ण
	वापस file;
पूर्ण
EXPORT_SYMBOL(filp_खोलो);

काष्ठा file *file_खोलो_root(काष्ठा dentry *dentry, काष्ठा vfsmount *mnt,
			    स्थिर अक्षर *filename, पूर्णांक flags, umode_t mode)
अणु
	काष्ठा खोलो_flags op;
	काष्ठा खोलो_how how = build_खोलो_how(flags, mode);
	पूर्णांक err = build_खोलो_flags(&how, &op);
	अगर (err)
		वापस ERR_PTR(err);
	वापस करो_file_खोलो_root(dentry, mnt, filename, &op);
पूर्ण
EXPORT_SYMBOL(file_खोलो_root);

अटल दीर्घ करो_sys_खोलोat2(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			   काष्ठा खोलो_how *how)
अणु
	काष्ठा खोलो_flags op;
	पूर्णांक fd = build_खोलो_flags(how, &op);
	काष्ठा filename *पंचांगp;

	अगर (fd)
		वापस fd;

	पंचांगp = getname(filename);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);

	fd = get_unused_fd_flags(how->flags);
	अगर (fd >= 0) अणु
		काष्ठा file *f = करो_filp_खोलो(dfd, पंचांगp, &op);
		अगर (IS_ERR(f)) अणु
			put_unused_fd(fd);
			fd = PTR_ERR(f);
		पूर्ण अन्यथा अणु
			fsnotअगरy_खोलो(f);
			fd_install(fd, f);
		पूर्ण
	पूर्ण
	putname(पंचांगp);
	वापस fd;
पूर्ण

दीर्घ करो_sys_खोलो(पूर्णांक dfd, स्थिर अक्षर __user *filename, पूर्णांक flags, umode_t mode)
अणु
	काष्ठा खोलो_how how = build_खोलो_how(flags, mode);
	वापस करो_sys_खोलोat2(dfd, filename, &how);
पूर्ण


SYSCALL_DEFINE3(खोलो, स्थिर अक्षर __user *, filename, पूर्णांक, flags, umode_t, mode)
अणु
	अगर (क्रमce_o_largefile())
		flags |= O_LARGEखाता;
	वापस करो_sys_खोलो(AT_FDCWD, filename, flags, mode);
पूर्ण

SYSCALL_DEFINE4(खोलोat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename, पूर्णांक, flags,
		umode_t, mode)
अणु
	अगर (क्रमce_o_largefile())
		flags |= O_LARGEखाता;
	वापस करो_sys_खोलो(dfd, filename, flags, mode);
पूर्ण

SYSCALL_DEFINE4(खोलोat2, पूर्णांक, dfd, स्थिर अक्षर __user *, filename,
		काष्ठा खोलो_how __user *, how, माप_प्रकार, usize)
अणु
	पूर्णांक err;
	काष्ठा खोलो_how पंचांगp;

	BUILD_BUG_ON(माप(काष्ठा खोलो_how) < OPEN_HOW_SIZE_VER0);
	BUILD_BUG_ON(माप(काष्ठा खोलो_how) != OPEN_HOW_SIZE_LATEST);

	अगर (unlikely(usize < OPEN_HOW_SIZE_VER0))
		वापस -EINVAL;

	err = copy_काष्ठा_from_user(&पंचांगp, माप(पंचांगp), how, usize);
	अगर (err)
		वापस err;

	/* O_LARGEखाता is only allowed क्रम non-O_PATH. */
	अगर (!(पंचांगp.flags & O_PATH) && क्रमce_o_largefile())
		पंचांगp.flags |= O_LARGEखाता;

	वापस करो_sys_खोलोat2(dfd, filename, &पंचांगp);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * Exactly like sys_खोलो(), except that it करोesn't set the
 * O_LARGEखाता flag.
 */
COMPAT_SYSCALL_DEFINE3(खोलो, स्थिर अक्षर __user *, filename, पूर्णांक, flags, umode_t, mode)
अणु
	वापस करो_sys_खोलो(AT_FDCWD, filename, flags, mode);
पूर्ण

/*
 * Exactly like sys_खोलोat(), except that it करोesn't set the
 * O_LARGEखाता flag.
 */
COMPAT_SYSCALL_DEFINE4(खोलोat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename, पूर्णांक, flags, umode_t, mode)
अणु
	वापस करो_sys_खोलो(dfd, filename, flags, mode);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __alpha__

/*
 * For backward compatibility?  Maybe this should be moved
 * पूर्णांकo arch/i386 instead?
 */
SYSCALL_DEFINE2(creat, स्थिर अक्षर __user *, pathname, umode_t, mode)
अणु
	पूर्णांक flags = O_CREAT | O_WRONLY | O_TRUNC;

	अगर (क्रमce_o_largefile())
		flags |= O_LARGEखाता;
	वापस करो_sys_खोलो(AT_FDCWD, pathname, flags, mode);
पूर्ण
#पूर्ण_अगर

/*
 * "id" is the POSIX thपढ़ो ID. We use the
 * files poपूर्णांकer क्रम this..
 */
पूर्णांक filp_बंद(काष्ठा file *filp, fl_owner_t id)
अणु
	पूर्णांक retval = 0;

	अगर (!file_count(filp)) अणु
		prपूर्णांकk(KERN_ERR "VFS: Close: file count is 0\n");
		वापस 0;
	पूर्ण

	अगर (filp->f_op->flush)
		retval = filp->f_op->flush(filp, id);

	अगर (likely(!(filp->f_mode & FMODE_PATH))) अणु
		dnotअगरy_flush(filp, id);
		locks_हटाओ_posix(filp, id);
	पूर्ण
	fput(filp);
	वापस retval;
पूर्ण

EXPORT_SYMBOL(filp_बंद);

/*
 * Careful here! We test whether the file poपूर्णांकer is शून्य beक्रमe
 * releasing the fd. This ensures that one clone task can't release
 * an fd जबतक another clone is खोलोing it.
 */
SYSCALL_DEFINE1(बंद, अचिन्हित पूर्णांक, fd)
अणु
	पूर्णांक retval = बंद_fd(fd);

	/* can't restart बंद syscall because file table entry was cleared */
	अगर (unlikely(retval == -ERESTARTSYS ||
		     retval == -ERESTARTNOINTR ||
		     retval == -ERESTARTNOHAND ||
		     retval == -ERESTART_RESTARTBLOCK))
		retval = -EINTR;

	वापस retval;
पूर्ण

/**
 * बंद_range() - Close all file descriptors in a given range.
 *
 * @fd:     starting file descriptor to बंद
 * @max_fd: last file descriptor to बंद
 * @flags:  reserved क्रम future extensions
 *
 * This बंदs a range of file descriptors. All file descriptors
 * from @fd up to and including @max_fd are बंदd.
 * Currently, errors to बंद a given file descriptor are ignored.
 */
SYSCALL_DEFINE3(बंद_range, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, max_fd,
		अचिन्हित पूर्णांक, flags)
अणु
	वापस __बंद_range(fd, max_fd, flags);
पूर्ण

/*
 * This routine simulates a hangup on the tty, to arrange that users
 * are given clean terminals at login समय.
 */
SYSCALL_DEFINE0(vhangup)
अणु
	अगर (capable(CAP_SYS_TTY_CONFIG)) अणु
		tty_vhangup_self();
		वापस 0;
	पूर्ण
	वापस -EPERM;
पूर्ण

/*
 * Called when an inode is about to be खोलो.
 * We use this to disallow खोलोing large files on 32bit प्रणालीs अगर
 * the caller didn't specअगरy O_LARGEखाता.  On 64bit प्रणालीs we क्रमce
 * on this flag in sys_खोलो.
 */
पूर्णांक generic_file_खोलो(काष्ठा inode * inode, काष्ठा file * filp)
अणु
	अगर (!(filp->f_flags & O_LARGEखाता) && i_size_पढ़ो(inode) > MAX_NON_LFS)
		वापस -EOVERFLOW;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(generic_file_खोलो);

/*
 * This is used by subप्रणालीs that करोn't want seekable
 * file descriptors. The function is not supposed to ever fail, the only
 * reason it वापसs an 'int' and not 'void' is so that it can be plugged
 * directly पूर्णांकo file_operations काष्ठाure.
 */
पूर्णांक nonseekable_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	filp->f_mode &= ~(FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(nonseekable_खोलो);

/*
 * stream_खोलो is used by subप्रणालीs that want stream-like file descriptors.
 * Such file descriptors are not seekable and करोn't have notion of position
 * (file.f_pos is always 0 and ppos passed to .पढ़ो()/.ग_लिखो() is always शून्य).
 * Contrary to file descriptors of other regular files, .पढ़ो() and .ग_लिखो()
 * can run simultaneously.
 *
 * stream_खोलो never fails and is marked to वापस पूर्णांक so that it could be
 * directly used as file_operations.खोलो .
 */
पूर्णांक stream_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	filp->f_mode &= ~(FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE | FMODE_ATOMIC_POS);
	filp->f_mode |= FMODE_STREAM;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(stream_खोलो);
