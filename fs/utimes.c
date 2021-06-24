<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/uसमय.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/compat.h>
#समावेश <यंत्र/unistd.h>

अटल bool nsec_valid(दीर्घ nsec)
अणु
	अगर (nsec == UTIME_OMIT || nsec == UTIME_NOW)
		वापस true;

	वापस nsec >= 0 && nsec <= 999999999;
पूर्ण

पूर्णांक vfs_uबार(स्थिर काष्ठा path *path, काष्ठा बारpec64 *बार)
अणु
	पूर्णांक error;
	काष्ठा iattr newattrs;
	काष्ठा inode *inode = path->dentry->d_inode;
	काष्ठा inode *delegated_inode = शून्य;

	अगर (बार) अणु
		अगर (!nsec_valid(बार[0].tv_nsec) ||
		    !nsec_valid(बार[1].tv_nsec))
			वापस -EINVAL;
		अगर (बार[0].tv_nsec == UTIME_NOW &&
		    बार[1].tv_nsec == UTIME_NOW)
			बार = शून्य;
	पूर्ण

	error = mnt_want_ग_लिखो(path->mnt);
	अगर (error)
		जाओ out;

	newattrs.ia_valid = ATTR_CTIME | ATTR_MTIME | ATTR_ATIME;
	अगर (बार) अणु
		अगर (बार[0].tv_nsec == UTIME_OMIT)
			newattrs.ia_valid &= ~ATTR_ATIME;
		अन्यथा अगर (बार[0].tv_nsec != UTIME_NOW) अणु
			newattrs.ia_aसमय = बार[0];
			newattrs.ia_valid |= ATTR_ATIME_SET;
		पूर्ण

		अगर (बार[1].tv_nsec == UTIME_OMIT)
			newattrs.ia_valid &= ~ATTR_MTIME;
		अन्यथा अगर (बार[1].tv_nsec != UTIME_NOW) अणु
			newattrs.ia_mसमय = बार[1];
			newattrs.ia_valid |= ATTR_MTIME_SET;
		पूर्ण
		/*
		 * Tell setattr_prepare(), that this is an explicit समय
		 * update, even अगर neither ATTR_ATIME_SET nor ATTR_MTIME_SET
		 * were used.
		 */
		newattrs.ia_valid |= ATTR_TIMES_SET;
	पूर्ण अन्यथा अणु
		newattrs.ia_valid |= ATTR_TOUCH;
	पूर्ण
retry_deleg:
	inode_lock(inode);
	error = notअगरy_change(mnt_user_ns(path->mnt), path->dentry, &newattrs,
			      &delegated_inode);
	inode_unlock(inode);
	अगर (delegated_inode) अणु
		error = अवरोध_deleg_रुको(&delegated_inode);
		अगर (!error)
			जाओ retry_deleg;
	पूर्ण

	mnt_drop_ग_लिखो(path->mnt);
out:
	वापस error;
पूर्ण

अटल पूर्णांक करो_uबार_path(पूर्णांक dfd, स्थिर अक्षर __user *filename,
		काष्ठा बारpec64 *बार, पूर्णांक flags)
अणु
	काष्ठा path path;
	पूर्णांक lookup_flags = 0, error;

	अगर (flags & ~(AT_SYMLINK_NOFOLLOW | AT_EMPTY_PATH))
		वापस -EINVAL;

	अगर (!(flags & AT_SYMLINK_NOFOLLOW))
		lookup_flags |= LOOKUP_FOLLOW;
	अगर (flags & AT_EMPTY_PATH)
		lookup_flags |= LOOKUP_EMPTY;

retry:
	error = user_path_at(dfd, filename, lookup_flags, &path);
	अगर (error)
		वापस error;

	error = vfs_uबार(&path, बार);
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक करो_uबार_fd(पूर्णांक fd, काष्ठा बारpec64 *बार, पूर्णांक flags)
अणु
	काष्ठा fd f;
	पूर्णांक error;

	अगर (flags)
		वापस -EINVAL;

	f = fdget(fd);
	अगर (!f.file)
		वापस -EBADF;
	error = vfs_uबार(&f.file->f_path, बार);
	fdput(f);
	वापस error;
पूर्ण

/*
 * करो_uबार - change बार on filename or file descriptor
 * @dfd: खोलो file descriptor, -1 or AT_FDCWD
 * @filename: path name or शून्य
 * @बार: new बार or शून्य
 * @flags: zero or more flags (only AT_SYMLINK_NOFOLLOW क्रम the moment)
 *
 * If filename is शून्य and dfd refers to an खोलो file, then operate on
 * the file.  Otherwise look up filename, possibly using dfd as a
 * starting poपूर्णांक.
 *
 * If बार==शून्य, set access and modअगरication to current समय,
 * must be owner or have ग_लिखो permission.
 * Else, update from *बार, must be owner or super user.
 */
दीर्घ करो_uबार(पूर्णांक dfd, स्थिर अक्षर __user *filename, काष्ठा बारpec64 *बार,
	       पूर्णांक flags)
अणु
	अगर (filename == शून्य && dfd != AT_FDCWD)
		वापस करो_uबार_fd(dfd, बार, flags);
	वापस करो_uबार_path(dfd, filename, बार, flags);
पूर्ण

SYSCALL_DEFINE4(uसमयnsat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename,
		काष्ठा __kernel_बारpec __user *, uबार, पूर्णांक, flags)
अणु
	काष्ठा बारpec64 tsबार[2];

	अगर (uबार) अणु
		अगर ((get_बारpec64(&tsबार[0], &uबार[0]) ||
			get_बारpec64(&tsबार[1], &uबार[1])))
			वापस -EFAULT;

		/* Nothing to करो, we must not even check the path.  */
		अगर (tsबार[0].tv_nsec == UTIME_OMIT &&
		    tsबार[1].tv_nsec == UTIME_OMIT)
			वापस 0;
	पूर्ण

	वापस करो_uबार(dfd, filename, uबार ? tsबार : शून्य, flags);
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_UTIME
/*
 * fuबारat(), uबार() and uसमय() are older versions of uसमयnsat()
 * that are provided क्रम compatibility with traditional C libraries.
 * On modern architectures, we always use libc wrappers around
 * uसमयnsat() instead.
 */
अटल दीर्घ करो_fuबारat(पूर्णांक dfd, स्थिर अक्षर __user *filename,
			 काष्ठा __kernel_old_समयval __user *uबार)
अणु
	काष्ठा __kernel_old_समयval बार[2];
	काष्ठा बारpec64 tsबार[2];

	अगर (uबार) अणु
		अगर (copy_from_user(&बार, uबार, माप(बार)))
			वापस -EFAULT;

		/* This test is needed to catch all invalid values.  If we
		   would test only in करो_uबार we would miss those invalid
		   values truncated by the multiplication with 1000.  Note
		   that we also catch UTIME_अणुNOW,OMITपूर्ण here which are only
		   valid क्रम uसमयnsat.  */
		अगर (बार[0].tv_usec >= 1000000 || बार[0].tv_usec < 0 ||
		    बार[1].tv_usec >= 1000000 || बार[1].tv_usec < 0)
			वापस -EINVAL;

		tsबार[0].tv_sec = बार[0].tv_sec;
		tsबार[0].tv_nsec = 1000 * बार[0].tv_usec;
		tsबार[1].tv_sec = बार[1].tv_sec;
		tsबार[1].tv_nsec = 1000 * बार[1].tv_usec;
	पूर्ण

	वापस करो_uबार(dfd, filename, uबार ? tsबार : शून्य, 0);
पूर्ण


SYSCALL_DEFINE3(fuबारat, पूर्णांक, dfd, स्थिर अक्षर __user *, filename,
		काष्ठा __kernel_old_समयval __user *, uबार)
अणु
	वापस करो_fuबारat(dfd, filename, uबार);
पूर्ण

SYSCALL_DEFINE2(uबार, अक्षर __user *, filename,
		काष्ठा __kernel_old_समयval __user *, uबार)
अणु
	वापस करो_fuबारat(AT_FDCWD, filename, uबार);
पूर्ण

SYSCALL_DEFINE2(uसमय, अक्षर __user *, filename, काष्ठा utimbuf __user *, बार)
अणु
	काष्ठा बारpec64 tv[2];

	अगर (बार) अणु
		अगर (get_user(tv[0].tv_sec, &बार->aस_समय) ||
		    get_user(tv[1].tv_sec, &बार->modसमय))
			वापस -EFAULT;
		tv[0].tv_nsec = 0;
		tv[1].tv_nsec = 0;
	पूर्ण
	वापस करो_uबार(AT_FDCWD, filename, बार ? tv : शून्य, 0);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
/*
 * Not all architectures have sys_uसमय, so implement this in terms
 * of sys_uबार.
 */
#अगर_घोषित __ARCH_WANT_SYS_UTIME32
SYSCALL_DEFINE2(uसमय32, स्थिर अक्षर __user *, filename,
		काष्ठा old_utimbuf32 __user *, t)
अणु
	काष्ठा बारpec64 tv[2];

	अगर (t) अणु
		अगर (get_user(tv[0].tv_sec, &t->aस_समय) ||
		    get_user(tv[1].tv_sec, &t->modसमय))
			वापस -EFAULT;
		tv[0].tv_nsec = 0;
		tv[1].tv_nsec = 0;
	पूर्ण
	वापस करो_uबार(AT_FDCWD, filename, t ? tv : शून्य, 0);
पूर्ण
#पूर्ण_अगर

SYSCALL_DEFINE4(uसमयnsat_समय32, अचिन्हित पूर्णांक, dfd, स्थिर अक्षर __user *, filename, काष्ठा old_बारpec32 __user *, t, पूर्णांक, flags)
अणु
	काष्ठा बारpec64 tv[2];

	अगर  (t) अणु
		अगर (get_old_बारpec32(&tv[0], &t[0]) ||
		    get_old_बारpec32(&tv[1], &t[1]))
			वापस -EFAULT;

		अगर (tv[0].tv_nsec == UTIME_OMIT && tv[1].tv_nsec == UTIME_OMIT)
			वापस 0;
	पूर्ण
	वापस करो_uबार(dfd, filename, t ? tv : शून्य, flags);
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_UTIME32
अटल दीर्घ करो_compat_fuबारat(अचिन्हित पूर्णांक dfd, स्थिर अक्षर __user *filename,
				काष्ठा old_समयval32 __user *t)
अणु
	काष्ठा बारpec64 tv[2];

	अगर (t) अणु
		अगर (get_user(tv[0].tv_sec, &t[0].tv_sec) ||
		    get_user(tv[0].tv_nsec, &t[0].tv_usec) ||
		    get_user(tv[1].tv_sec, &t[1].tv_sec) ||
		    get_user(tv[1].tv_nsec, &t[1].tv_usec))
			वापस -EFAULT;
		अगर (tv[0].tv_nsec >= 1000000 || tv[0].tv_nsec < 0 ||
		    tv[1].tv_nsec >= 1000000 || tv[1].tv_nsec < 0)
			वापस -EINVAL;
		tv[0].tv_nsec *= 1000;
		tv[1].tv_nsec *= 1000;
	पूर्ण
	वापस करो_uबार(dfd, filename, t ? tv : शून्य, 0);
पूर्ण

SYSCALL_DEFINE3(fuबारat_समय32, अचिन्हित पूर्णांक, dfd,
		       स्थिर अक्षर __user *, filename,
		       काष्ठा old_समयval32 __user *, t)
अणु
	वापस करो_compat_fuबारat(dfd, filename, t);
पूर्ण

SYSCALL_DEFINE2(uबार_समय32, स्थिर अक्षर __user *, filename, काष्ठा old_समयval32 __user *, t)
अणु
	वापस करो_compat_fuबारat(AT_FDCWD, filename, t);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
