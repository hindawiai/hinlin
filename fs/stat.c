<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/stat.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/file.h>
#समावेश <linux/highuid.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/security.h>
#समावेश <linux/cred.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/compat.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>

#समावेश "internal.h"
#समावेश "mount.h"

/**
 * generic_fillattr - Fill in the basic attributes from the inode काष्ठा
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode:	Inode to use as the source
 * @stat:	Where to fill in the attributes
 *
 * Fill in the basic attributes in the kstat काष्ठाure from data that's to be
 * found on the VFS inode काष्ठाure.  This is the शेष अगर no getattr inode
 * operation is supplied.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe filling in the
 * uid and gid filds. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 */
व्योम generic_fillattr(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		      काष्ठा kstat *stat)
अणु
	stat->dev = inode->i_sb->s_dev;
	stat->ino = inode->i_ino;
	stat->mode = inode->i_mode;
	stat->nlink = inode->i_nlink;
	stat->uid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
	stat->gid = i_gid_पूर्णांकo_mnt(mnt_userns, inode);
	stat->rdev = inode->i_rdev;
	stat->size = i_size_पढ़ो(inode);
	stat->aसमय = inode->i_aसमय;
	stat->mसमय = inode->i_mसमय;
	stat->स_समय = inode->i_स_समय;
	stat->blksize = i_blocksize(inode);
	stat->blocks = inode->i_blocks;
पूर्ण
EXPORT_SYMBOL(generic_fillattr);

/**
 * vfs_getattr_nosec - getattr without security checks
 * @path: file to get attributes from
 * @stat: काष्ठाure to वापस attributes in
 * @request_mask: STATX_xxx flags indicating what the caller wants
 * @query_flags: Query mode (AT_STATX_SYNC_TYPE)
 *
 * Get attributes without calling security_inode_getattr.
 *
 * Currently the only caller other than vfs_getattr is पूर्णांकernal to the
 * filehandle lookup code, which uses only the inode number and वापसs no
 * attributes to any user.  Any other code probably wants vfs_getattr.
 */
पूर्णांक vfs_getattr_nosec(स्थिर काष्ठा path *path, काष्ठा kstat *stat,
		      u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा user_namespace *mnt_userns;
	काष्ठा inode *inode = d_backing_inode(path->dentry);

	स_रखो(stat, 0, माप(*stat));
	stat->result_mask |= STATX_BASIC_STATS;
	query_flags &= AT_STATX_SYNC_TYPE;

	/* allow the fs to override these अगर it really wants to */
	/* SB_NOATIME means fileप्रणाली supplies dummy aसमय value */
	अगर (inode->i_sb->s_flags & SB_NOATIME)
		stat->result_mask &= ~STATX_ATIME;

	/*
	 * Note: If you add another clause to set an attribute flag, please
	 * update attributes_mask below.
	 */
	अगर (IS_AUTOMOUNT(inode))
		stat->attributes |= STATX_ATTR_AUTOMOUNT;

	अगर (IS_DAX(inode))
		stat->attributes |= STATX_ATTR_DAX;

	stat->attributes_mask |= (STATX_ATTR_AUTOMOUNT |
				  STATX_ATTR_DAX);

	mnt_userns = mnt_user_ns(path->mnt);
	अगर (inode->i_op->getattr)
		वापस inode->i_op->getattr(mnt_userns, path, stat,
					    request_mask, query_flags);

	generic_fillattr(mnt_userns, inode, stat);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vfs_getattr_nosec);

/*
 * vfs_getattr - Get the enhanced basic attributes of a file
 * @path: The file of पूर्णांकerest
 * @stat: Where to वापस the statistics
 * @request_mask: STATX_xxx flags indicating what the caller wants
 * @query_flags: Query mode (AT_STATX_SYNC_TYPE)
 *
 * Ask the fileप्रणाली क्रम a file's attributes.  The caller must indicate in
 * request_mask and query_flags to indicate what they want.
 *
 * If the file is remote, the fileप्रणाली can be क्रमced to update the attributes
 * from the backing store by passing AT_STATX_FORCE_SYNC in query_flags or can
 * suppress the update by passing AT_STATX_DONT_SYNC.
 *
 * Bits must have been set in request_mask to indicate which attributes the
 * caller wants retrieving.  Any such attribute not requested may be वापसed
 * anyway, but the value may be approximate, and, अगर remote, may not have been
 * synchronised with the server.
 *
 * 0 will be वापसed on success, and a -ve error code अगर unsuccessful.
 */
पूर्णांक vfs_getattr(स्थिर काष्ठा path *path, काष्ठा kstat *stat,
		u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	पूर्णांक retval;

	retval = security_inode_getattr(path);
	अगर (retval)
		वापस retval;
	वापस vfs_getattr_nosec(path, stat, request_mask, query_flags);
पूर्ण
EXPORT_SYMBOL(vfs_getattr);

/**
 * vfs_ख_स्थिति - Get the basic attributes by file descriptor
 * @fd: The file descriptor referring to the file of पूर्णांकerest
 * @stat: The result काष्ठाure to fill in.
 *
 * This function is a wrapper around vfs_getattr().  The मुख्य dअगरference is
 * that it uses a file descriptor to determine the file location.
 *
 * 0 will be वापसed on success, and a -ve error code अगर unsuccessful.
 */
पूर्णांक vfs_ख_स्थिति(पूर्णांक fd, काष्ठा kstat *stat)
अणु
	काष्ठा fd f;
	पूर्णांक error;

	f = fdget_raw(fd);
	अगर (!f.file)
		वापस -EBADF;
	error = vfs_getattr(&f.file->f_path, stat, STATX_BASIC_STATS, 0);
	fdput(f);
	वापस error;
पूर्ण

/**
 * vfs_statx - Get basic and extra attributes by filename
 * @dfd: A file descriptor representing the base dir क्रम a relative filename
 * @filename: The name of the file of पूर्णांकerest
 * @flags: Flags to control the query
 * @stat: The result काष्ठाure to fill in.
 * @request_mask: STATX_xxx flags indicating what the caller wants
 *
 * This function is a wrapper around vfs_getattr().  The मुख्य dअगरference is
 * that it uses a filename and base directory to determine the file location.
 * Additionally, the use of AT_SYMLINK_NOFOLLOW in flags will prevent a symlink
 * at the given name from being referenced.
 *
 * 0 will be वापसed on success, and a -ve error code अगर unsuccessful.
 */
अटल पूर्णांक vfs_statx(पूर्णांक dfd, स्थिर अक्षर __user *filename, पूर्णांक flags,
	      काष्ठा kstat *stat, u32 request_mask)
अणु
	काष्ठा path path;
	अचिन्हित lookup_flags = 0;
	पूर्णांक error;

	अगर (flags & ~(AT_SYMLINK_NOFOLLOW | AT_NO_AUTOMOUNT | AT_EMPTY_PATH |
		      AT_STATX_SYNC_TYPE))
		वापस -EINVAL;

	अगर (!(flags & AT_SYMLINK_NOFOLLOW))
		lookup_flags |= LOOKUP_FOLLOW;
	अगर (!(flags & AT_NO_AUTOMOUNT))
		lookup_flags |= LOOKUP_AUTOMOUNT;
	अगर (flags & AT_EMPTY_PATH)
		lookup_flags |= LOOKUP_EMPTY;

retry:
	error = user_path_at(dfd, filename, lookup_flags, &path);
	अगर (error)
		जाओ out;

	error = vfs_getattr(&path, stat, request_mask, flags);
	stat->mnt_id = real_mount(path.mnt)->mnt_id;
	stat->result_mask |= STATX_MNT_ID;
	अगर (path.mnt->mnt_root == path.dentry)
		stat->attributes |= STATX_ATTR_MOUNT_ROOT;
	stat->attributes_mask |= STATX_ATTR_MOUNT_ROOT;
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
out:
	वापस error;
पूर्ण

पूर्णांक vfs_ख_स्थितिat(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			      काष्ठा kstat *stat, पूर्णांक flags)
अणु
	वापस vfs_statx(dfd, filename, flags | AT_NO_AUTOMOUNT,
			 stat, STATX_BASIC_STATS);
पूर्ण

#अगर_घोषित __ARCH_WANT_OLD_STAT

/*
 * For backward compatibility?  Maybe this should be moved
 * पूर्णांकo arch/i386 instead?
 */
अटल पूर्णांक cp_old_stat(काष्ठा kstat *stat, काष्ठा __old_kernel_stat __user * statbuf)
अणु
	अटल पूर्णांक warncount = 5;
	काष्ठा __old_kernel_stat पंचांगp;

	अगर (warncount > 0) अणु
		warncount--;
		prपूर्णांकk(KERN_WARNING "VFS: Warning: %s using old stat() call. Recompile your binary.\n",
			current->comm);
	पूर्ण अन्यथा अगर (warncount < 0) अणु
		/* it's laughable, but... */
		warncount = 0;
	पूर्ण

	स_रखो(&पंचांगp, 0, माप(काष्ठा __old_kernel_stat));
	पंचांगp.st_dev = old_encode_dev(stat->dev);
	पंचांगp.st_ino = stat->ino;
	अगर (माप(पंचांगp.st_ino) < माप(stat->ino) && पंचांगp.st_ino != stat->ino)
		वापस -EOVERFLOW;
	पंचांगp.st_mode = stat->mode;
	पंचांगp.st_nlink = stat->nlink;
	अगर (पंचांगp.st_nlink != stat->nlink)
		वापस -EOVERFLOW;
	SET_UID(पंचांगp.st_uid, from_kuid_munged(current_user_ns(), stat->uid));
	SET_GID(पंचांगp.st_gid, from_kgid_munged(current_user_ns(), stat->gid));
	पंचांगp.st_rdev = old_encode_dev(stat->rdev);
#अगर BITS_PER_LONG == 32
	अगर (stat->size > MAX_NON_LFS)
		वापस -EOVERFLOW;
#पूर्ण_अगर
	पंचांगp.st_size = stat->size;
	पंचांगp.st_aसमय = stat->aसमय.tv_sec;
	पंचांगp.st_mसमय = stat->mसमय.tv_sec;
	पंचांगp.st_स_समय = stat->स_समय.tv_sec;
	वापस copy_to_user(statbuf,&पंचांगp,माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

SYSCALL_DEFINE2(stat, स्थिर अक्षर __user *, filename,
		काष्ठा __old_kernel_stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_stat(filename, &stat);
	अगर (error)
		वापस error;

	वापस cp_old_stat(&stat, statbuf);
पूर्ण

SYSCALL_DEFINE2(lstat, स्थिर अक्षर __user *, filename,
		काष्ठा __old_kernel_stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_lstat(filename, &stat);
	अगर (error)
		वापस error;

	वापस cp_old_stat(&stat, statbuf);
पूर्ण

SYSCALL_DEFINE2(ख_स्थिति, अचिन्हित पूर्णांक, fd, काष्ठा __old_kernel_stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_ख_स्थिति(fd, &stat);

	अगर (!error)
		error = cp_old_stat(&stat, statbuf);

	वापस error;
पूर्ण

#पूर्ण_अगर /* __ARCH_WANT_OLD_STAT */

#अगर_घोषित __ARCH_WANT_NEW_STAT

#अगर BITS_PER_LONG == 32
#  define choose_32_64(a,b) a
#अन्यथा
#  define choose_32_64(a,b) b
#पूर्ण_अगर

#घोषणा valid_dev(x)  choose_32_64(old_valid_dev(x),true)
#घोषणा encode_dev(x) choose_32_64(old_encode_dev,new_encode_dev)(x)

#अगर_अघोषित INIT_STRUCT_STAT_PADDING
#  define INIT_STRUCT_STAT_PADDING(st) स_रखो(&st, 0, माप(st))
#पूर्ण_अगर

अटल पूर्णांक cp_new_stat(काष्ठा kstat *stat, काष्ठा stat __user *statbuf)
अणु
	काष्ठा stat पंचांगp;

	अगर (!valid_dev(stat->dev) || !valid_dev(stat->rdev))
		वापस -EOVERFLOW;
#अगर BITS_PER_LONG == 32
	अगर (stat->size > MAX_NON_LFS)
		वापस -EOVERFLOW;
#पूर्ण_अगर

	INIT_STRUCT_STAT_PADDING(पंचांगp);
	पंचांगp.st_dev = encode_dev(stat->dev);
	पंचांगp.st_ino = stat->ino;
	अगर (माप(पंचांगp.st_ino) < माप(stat->ino) && पंचांगp.st_ino != stat->ino)
		वापस -EOVERFLOW;
	पंचांगp.st_mode = stat->mode;
	पंचांगp.st_nlink = stat->nlink;
	अगर (पंचांगp.st_nlink != stat->nlink)
		वापस -EOVERFLOW;
	SET_UID(पंचांगp.st_uid, from_kuid_munged(current_user_ns(), stat->uid));
	SET_GID(पंचांगp.st_gid, from_kgid_munged(current_user_ns(), stat->gid));
	पंचांगp.st_rdev = encode_dev(stat->rdev);
	पंचांगp.st_size = stat->size;
	पंचांगp.st_aसमय = stat->aसमय.tv_sec;
	पंचांगp.st_mसमय = stat->mसमय.tv_sec;
	पंचांगp.st_स_समय = stat->स_समय.tv_sec;
#अगर_घोषित STAT_HAVE_NSEC
	पंचांगp.st_aसमय_nsec = stat->aसमय.tv_nsec;
	पंचांगp.st_mसमय_nsec = stat->mसमय.tv_nsec;
	पंचांगp.st_स_समय_nsec = stat->स_समय.tv_nsec;
#पूर्ण_अगर
	पंचांगp.st_blocks = stat->blocks;
	पंचांगp.st_blksize = stat->blksize;
	वापस copy_to_user(statbuf,&पंचांगp,माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

SYSCALL_DEFINE2(newstat, स्थिर अक्षर __user *, filename,
		काष्ठा stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_stat(filename, &stat);

	अगर (error)
		वापस error;
	वापस cp_new_stat(&stat, statbuf);
पूर्ण

SYSCALL_DEFINE2(newlstat, स्थिर अक्षर __user *, filename,
		काष्ठा stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_lstat(filename, &stat);
	अगर (error)
		वापस error;

	वापस cp_new_stat(&stat, statbuf);
पूर्ण

#अगर !defined(__ARCH_WANT_STAT64) || defined(__ARCH_WANT_SYS_NEWFSTATAT)
SYSCALL_DEFINE4(newख_स्थितिat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename,
		काष्ठा stat __user *, statbuf, पूर्णांक, flag)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_ख_स्थितिat(dfd, filename, &stat, flag);
	अगर (error)
		वापस error;
	वापस cp_new_stat(&stat, statbuf);
पूर्ण
#पूर्ण_अगर

SYSCALL_DEFINE2(newख_स्थिति, अचिन्हित पूर्णांक, fd, काष्ठा stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_ख_स्थिति(fd, &stat);

	अगर (!error)
		error = cp_new_stat(&stat, statbuf);

	वापस error;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक करो_पढ़ोlinkat(पूर्णांक dfd, स्थिर अक्षर __user *pathname,
			 अक्षर __user *buf, पूर्णांक bufsiz)
अणु
	काष्ठा path path;
	पूर्णांक error;
	पूर्णांक empty = 0;
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_EMPTY;

	अगर (bufsiz <= 0)
		वापस -EINVAL;

retry:
	error = user_path_at_empty(dfd, pathname, lookup_flags, &path, &empty);
	अगर (!error) अणु
		काष्ठा inode *inode = d_backing_inode(path.dentry);

		error = empty ? -ENOENT : -EINVAL;
		/*
		 * AFS mountpoपूर्णांकs allow पढ़ोlink(2) but are not symlinks
		 */
		अगर (d_is_symlink(path.dentry) || inode->i_op->पढ़ोlink) अणु
			error = security_inode_पढ़ोlink(path.dentry);
			अगर (!error) अणु
				touch_aसमय(&path);
				error = vfs_पढ़ोlink(path.dentry, buf, bufsiz);
			पूर्ण
		पूर्ण
		path_put(&path);
		अगर (retry_estale(error, lookup_flags)) अणु
			lookup_flags |= LOOKUP_REVAL;
			जाओ retry;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE4(पढ़ोlinkat, पूर्णांक, dfd, स्थिर अक्षर __user *, pathname,
		अक्षर __user *, buf, पूर्णांक, bufsiz)
अणु
	वापस करो_पढ़ोlinkat(dfd, pathname, buf, bufsiz);
पूर्ण

SYSCALL_DEFINE3(पढ़ोlink, स्थिर अक्षर __user *, path, अक्षर __user *, buf,
		पूर्णांक, bufsiz)
अणु
	वापस करो_पढ़ोlinkat(AT_FDCWD, path, buf, bufsiz);
पूर्ण


/* ---------- LFS-64 ----------- */
#अगर defined(__ARCH_WANT_STAT64) || defined(__ARCH_WANT_COMPAT_STAT64)

#अगर_अघोषित INIT_STRUCT_STAT64_PADDING
#  define INIT_STRUCT_STAT64_PADDING(st) स_रखो(&st, 0, माप(st))
#पूर्ण_अगर

अटल दीर्घ cp_new_stat64(काष्ठा kstat *stat, काष्ठा stat64 __user *statbuf)
अणु
	काष्ठा stat64 पंचांगp;

	INIT_STRUCT_STAT64_PADDING(पंचांगp);
#अगर_घोषित CONFIG_MIPS
	/* mips has weird padding, so we करोn't get 64 bits there */
	पंचांगp.st_dev = new_encode_dev(stat->dev);
	पंचांगp.st_rdev = new_encode_dev(stat->rdev);
#अन्यथा
	पंचांगp.st_dev = huge_encode_dev(stat->dev);
	पंचांगp.st_rdev = huge_encode_dev(stat->rdev);
#पूर्ण_अगर
	पंचांगp.st_ino = stat->ino;
	अगर (माप(पंचांगp.st_ino) < माप(stat->ino) && पंचांगp.st_ino != stat->ino)
		वापस -EOVERFLOW;
#अगर_घोषित STAT64_HAS_BROKEN_ST_INO
	पंचांगp.__st_ino = stat->ino;
#पूर्ण_अगर
	पंचांगp.st_mode = stat->mode;
	पंचांगp.st_nlink = stat->nlink;
	पंचांगp.st_uid = from_kuid_munged(current_user_ns(), stat->uid);
	पंचांगp.st_gid = from_kgid_munged(current_user_ns(), stat->gid);
	पंचांगp.st_aसमय = stat->aसमय.tv_sec;
	पंचांगp.st_aसमय_nsec = stat->aसमय.tv_nsec;
	पंचांगp.st_mसमय = stat->mसमय.tv_sec;
	पंचांगp.st_mसमय_nsec = stat->mसमय.tv_nsec;
	पंचांगp.st_स_समय = stat->स_समय.tv_sec;
	पंचांगp.st_स_समय_nsec = stat->स_समय.tv_nsec;
	पंचांगp.st_size = stat->size;
	पंचांगp.st_blocks = stat->blocks;
	पंचांगp.st_blksize = stat->blksize;
	वापस copy_to_user(statbuf,&पंचांगp,माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

SYSCALL_DEFINE2(stat64, स्थिर अक्षर __user *, filename,
		काष्ठा stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_stat(filename, &stat);

	अगर (!error)
		error = cp_new_stat64(&stat, statbuf);

	वापस error;
पूर्ण

SYSCALL_DEFINE2(lstat64, स्थिर अक्षर __user *, filename,
		काष्ठा stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_lstat(filename, &stat);

	अगर (!error)
		error = cp_new_stat64(&stat, statbuf);

	वापस error;
पूर्ण

SYSCALL_DEFINE2(ख_स्थिति64, अचिन्हित दीर्घ, fd, काष्ठा stat64 __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_ख_स्थिति(fd, &stat);

	अगर (!error)
		error = cp_new_stat64(&stat, statbuf);

	वापस error;
पूर्ण

SYSCALL_DEFINE4(ख_स्थितिat64, पूर्णांक, dfd, स्थिर अक्षर __user *, filename,
		काष्ठा stat64 __user *, statbuf, पूर्णांक, flag)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_ख_स्थितिat(dfd, filename, &stat, flag);
	अगर (error)
		वापस error;
	वापस cp_new_stat64(&stat, statbuf);
पूर्ण
#पूर्ण_अगर /* __ARCH_WANT_STAT64 || __ARCH_WANT_COMPAT_STAT64 */

अटल noअंतरभूत_क्रम_stack पूर्णांक
cp_statx(स्थिर काष्ठा kstat *stat, काष्ठा statx __user *buffer)
अणु
	काष्ठा statx पंचांगp;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));

	पंचांगp.stx_mask = stat->result_mask;
	पंचांगp.stx_blksize = stat->blksize;
	पंचांगp.stx_attributes = stat->attributes;
	पंचांगp.stx_nlink = stat->nlink;
	पंचांगp.stx_uid = from_kuid_munged(current_user_ns(), stat->uid);
	पंचांगp.stx_gid = from_kgid_munged(current_user_ns(), stat->gid);
	पंचांगp.stx_mode = stat->mode;
	पंचांगp.stx_ino = stat->ino;
	पंचांगp.stx_size = stat->size;
	पंचांगp.stx_blocks = stat->blocks;
	पंचांगp.stx_attributes_mask = stat->attributes_mask;
	पंचांगp.stx_aसमय.tv_sec = stat->aसमय.tv_sec;
	पंचांगp.stx_aसमय.tv_nsec = stat->aसमय.tv_nsec;
	पंचांगp.stx_bसमय.tv_sec = stat->bसमय.tv_sec;
	पंचांगp.stx_bसमय.tv_nsec = stat->bसमय.tv_nsec;
	पंचांगp.stx_स_समय.tv_sec = stat->स_समय.tv_sec;
	पंचांगp.stx_स_समय.tv_nsec = stat->स_समय.tv_nsec;
	पंचांगp.stx_mसमय.tv_sec = stat->mसमय.tv_sec;
	पंचांगp.stx_mसमय.tv_nsec = stat->mसमय.tv_nsec;
	पंचांगp.stx_rdev_major = MAJOR(stat->rdev);
	पंचांगp.stx_rdev_minor = MINOR(stat->rdev);
	पंचांगp.stx_dev_major = MAJOR(stat->dev);
	पंचांगp.stx_dev_minor = MINOR(stat->dev);
	पंचांगp.stx_mnt_id = stat->mnt_id;

	वापस copy_to_user(buffer, &पंचांगp, माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

पूर्णांक करो_statx(पूर्णांक dfd, स्थिर अक्षर __user *filename, अचिन्हित flags,
	     अचिन्हित पूर्णांक mask, काष्ठा statx __user *buffer)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	अगर (mask & STATX__RESERVED)
		वापस -EINVAL;
	अगर ((flags & AT_STATX_SYNC_TYPE) == AT_STATX_SYNC_TYPE)
		वापस -EINVAL;

	error = vfs_statx(dfd, filename, flags, &stat, mask);
	अगर (error)
		वापस error;

	वापस cp_statx(&stat, buffer);
पूर्ण

/**
 * sys_statx - System call to get enhanced stats
 * @dfd: Base directory to pathwalk from *or* fd to stat.
 * @filename: File to stat or "" with AT_EMPTY_PATH
 * @flags: AT_* flags to control pathwalk.
 * @mask: Parts of statx काष्ठा actually required.
 * @buffer: Result buffer.
 *
 * Note that ख_स्थिति() can be emulated by setting dfd to the fd of पूर्णांकerest,
 * supplying "" as the filename and setting AT_EMPTY_PATH in the flags.
 */
SYSCALL_DEFINE5(statx,
		पूर्णांक, dfd, स्थिर अक्षर __user *, filename, अचिन्हित, flags,
		अचिन्हित पूर्णांक, mask,
		काष्ठा statx __user *, buffer)
अणु
	वापस करो_statx(dfd, filename, flags, mask, buffer);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक cp_compat_stat(काष्ठा kstat *stat, काष्ठा compat_stat __user *ubuf)
अणु
	काष्ठा compat_stat पंचांगp;

	अगर (!old_valid_dev(stat->dev) || !old_valid_dev(stat->rdev))
		वापस -EOVERFLOW;

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	पंचांगp.st_dev = old_encode_dev(stat->dev);
	पंचांगp.st_ino = stat->ino;
	अगर (माप(पंचांगp.st_ino) < माप(stat->ino) && पंचांगp.st_ino != stat->ino)
		वापस -EOVERFLOW;
	पंचांगp.st_mode = stat->mode;
	पंचांगp.st_nlink = stat->nlink;
	अगर (पंचांगp.st_nlink != stat->nlink)
		वापस -EOVERFLOW;
	SET_UID(पंचांगp.st_uid, from_kuid_munged(current_user_ns(), stat->uid));
	SET_GID(पंचांगp.st_gid, from_kgid_munged(current_user_ns(), stat->gid));
	पंचांगp.st_rdev = old_encode_dev(stat->rdev);
	अगर ((u64) stat->size > MAX_NON_LFS)
		वापस -EOVERFLOW;
	पंचांगp.st_size = stat->size;
	पंचांगp.st_aसमय = stat->aसमय.tv_sec;
	पंचांगp.st_aसमय_nsec = stat->aसमय.tv_nsec;
	पंचांगp.st_mसमय = stat->mसमय.tv_sec;
	पंचांगp.st_mसमय_nsec = stat->mसमय.tv_nsec;
	पंचांगp.st_स_समय = stat->स_समय.tv_sec;
	पंचांगp.st_स_समय_nsec = stat->स_समय.tv_nsec;
	पंचांगp.st_blocks = stat->blocks;
	पंचांगp.st_blksize = stat->blksize;
	वापस copy_to_user(ubuf, &पंचांगp, माप(पंचांगp)) ? -EFAULT : 0;
पूर्ण

COMPAT_SYSCALL_DEFINE2(newstat, स्थिर अक्षर __user *, filename,
		       काष्ठा compat_stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_stat(filename, &stat);
	अगर (error)
		वापस error;
	वापस cp_compat_stat(&stat, statbuf);
पूर्ण

COMPAT_SYSCALL_DEFINE2(newlstat, स्थिर अक्षर __user *, filename,
		       काष्ठा compat_stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_lstat(filename, &stat);
	अगर (error)
		वापस error;
	वापस cp_compat_stat(&stat, statbuf);
पूर्ण

#अगर_अघोषित __ARCH_WANT_STAT64
COMPAT_SYSCALL_DEFINE4(newख_स्थितिat, अचिन्हित पूर्णांक, dfd,
		       स्थिर अक्षर __user *, filename,
		       काष्ठा compat_stat __user *, statbuf, पूर्णांक, flag)
अणु
	काष्ठा kstat stat;
	पूर्णांक error;

	error = vfs_ख_स्थितिat(dfd, filename, &stat, flag);
	अगर (error)
		वापस error;
	वापस cp_compat_stat(&stat, statbuf);
पूर्ण
#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE2(newख_स्थिति, अचिन्हित पूर्णांक, fd,
		       काष्ठा compat_stat __user *, statbuf)
अणु
	काष्ठा kstat stat;
	पूर्णांक error = vfs_ख_स्थिति(fd, &stat);

	अगर (!error)
		error = cp_compat_stat(&stat, statbuf);
	वापस error;
पूर्ण
#पूर्ण_अगर

/* Caller is here responsible क्रम sufficient locking (ie. inode->i_lock) */
व्योम __inode_add_bytes(काष्ठा inode *inode, loff_t bytes)
अणु
	inode->i_blocks += bytes >> 9;
	bytes &= 511;
	inode->i_bytes += bytes;
	अगर (inode->i_bytes >= 512) अणु
		inode->i_blocks++;
		inode->i_bytes -= 512;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__inode_add_bytes);

व्योम inode_add_bytes(काष्ठा inode *inode, loff_t bytes)
अणु
	spin_lock(&inode->i_lock);
	__inode_add_bytes(inode, bytes);
	spin_unlock(&inode->i_lock);
पूर्ण

EXPORT_SYMBOL(inode_add_bytes);

व्योम __inode_sub_bytes(काष्ठा inode *inode, loff_t bytes)
अणु
	inode->i_blocks -= bytes >> 9;
	bytes &= 511;
	अगर (inode->i_bytes < bytes) अणु
		inode->i_blocks--;
		inode->i_bytes += 512;
	पूर्ण
	inode->i_bytes -= bytes;
पूर्ण

EXPORT_SYMBOL(__inode_sub_bytes);

व्योम inode_sub_bytes(काष्ठा inode *inode, loff_t bytes)
अणु
	spin_lock(&inode->i_lock);
	__inode_sub_bytes(inode, bytes);
	spin_unlock(&inode->i_lock);
पूर्ण

EXPORT_SYMBOL(inode_sub_bytes);

loff_t inode_get_bytes(काष्ठा inode *inode)
अणु
	loff_t ret;

	spin_lock(&inode->i_lock);
	ret = __inode_get_bytes(inode);
	spin_unlock(&inode->i_lock);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(inode_get_bytes);

व्योम inode_set_bytes(काष्ठा inode *inode, loff_t bytes)
अणु
	/* Caller is here responsible क्रम sufficient locking
	 * (ie. inode->i_lock) */
	inode->i_blocks = bytes >> 9;
	inode->i_bytes = bytes & 511;
पूर्ण

EXPORT_SYMBOL(inode_set_bytes);
