<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Routines that mimic syscalls, but करोn't use the user address space or file
 * descriptors.  Only क्रम init/ and related early init code.
 */
#समावेश <linux/init.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/file.h>
#समावेश <linux/init_syscalls.h>
#समावेश <linux/security.h>
#समावेश "internal.h"

पूर्णांक __init init_mount(स्थिर अक्षर *dev_name, स्थिर अक्षर *dir_name,
		स्थिर अक्षर *type_page, अचिन्हित दीर्घ flags, व्योम *data_page)
अणु
	काष्ठा path path;
	पूर्णांक ret;

	ret = kern_path(dir_name, LOOKUP_FOLLOW, &path);
	अगर (ret)
		वापस ret;
	ret = path_mount(dev_name, &path, type_page, flags, data_page);
	path_put(&path);
	वापस ret;
पूर्ण

पूर्णांक __init init_umount(स्थिर अक्षर *name, पूर्णांक flags)
अणु
	पूर्णांक lookup_flags = LOOKUP_MOUNTPOINT;
	काष्ठा path path;
	पूर्णांक ret;

	अगर (!(flags & UMOUNT_NOFOLLOW))
		lookup_flags |= LOOKUP_FOLLOW;
	ret = kern_path(name, lookup_flags, &path);
	अगर (ret)
		वापस ret;
	वापस path_umount(&path, flags);
पूर्ण

पूर्णांक __init init_स_बदलो(स्थिर अक्षर *filename)
अणु
	काष्ठा path path;
	पूर्णांक error;

	error = kern_path(filename, LOOKUP_FOLLOW | LOOKUP_सूचीECTORY, &path);
	अगर (error)
		वापस error;
	error = path_permission(&path, MAY_EXEC | MAY_CHसूची);
	अगर (!error)
		set_fs_pwd(current->fs, &path);
	path_put(&path);
	वापस error;
पूर्ण

पूर्णांक __init init_chroot(स्थिर अक्षर *filename)
अणु
	काष्ठा path path;
	पूर्णांक error;

	error = kern_path(filename, LOOKUP_FOLLOW | LOOKUP_सूचीECTORY, &path);
	अगर (error)
		वापस error;
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
dput_and_out:
	path_put(&path);
	वापस error;
पूर्ण

पूर्णांक __init init_chown(स्थिर अक्षर *filename, uid_t user, gid_t group, पूर्णांक flags)
अणु
	पूर्णांक lookup_flags = (flags & AT_SYMLINK_NOFOLLOW) ? 0 : LOOKUP_FOLLOW;
	काष्ठा path path;
	पूर्णांक error;

	error = kern_path(filename, lookup_flags, &path);
	अगर (error)
		वापस error;
	error = mnt_want_ग_लिखो(path.mnt);
	अगर (!error) अणु
		error = chown_common(&path, user, group);
		mnt_drop_ग_लिखो(path.mnt);
	पूर्ण
	path_put(&path);
	वापस error;
पूर्ण

पूर्णांक __init init_chmod(स्थिर अक्षर *filename, umode_t mode)
अणु
	काष्ठा path path;
	पूर्णांक error;

	error = kern_path(filename, LOOKUP_FOLLOW, &path);
	अगर (error)
		वापस error;
	error = chmod_common(&path, mode);
	path_put(&path);
	वापस error;
पूर्ण

पूर्णांक __init init_eaccess(स्थिर अक्षर *filename)
अणु
	काष्ठा path path;
	पूर्णांक error;

	error = kern_path(filename, LOOKUP_FOLLOW, &path);
	अगर (error)
		वापस error;
	error = path_permission(&path, MAY_ACCESS);
	path_put(&path);
	वापस error;
पूर्ण

पूर्णांक __init init_stat(स्थिर अक्षर *filename, काष्ठा kstat *stat, पूर्णांक flags)
अणु
	पूर्णांक lookup_flags = (flags & AT_SYMLINK_NOFOLLOW) ? 0 : LOOKUP_FOLLOW;
	काष्ठा path path;
	पूर्णांक error;

	error = kern_path(filename, lookup_flags, &path);
	अगर (error)
		वापस error;
	error = vfs_getattr(&path, stat, STATX_BASIC_STATS,
			    flags | AT_NO_AUTOMOUNT);
	path_put(&path);
	वापस error;
पूर्ण

पूर्णांक __init init_mknod(स्थिर अक्षर *filename, umode_t mode, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा dentry *dentry;
	काष्ठा path path;
	पूर्णांक error;

	अगर (S_ISFIFO(mode) || S_ISSOCK(mode))
		dev = 0;
	अन्यथा अगर (!(S_ISBLK(mode) || S_ISCHR(mode)))
		वापस -EINVAL;

	dentry = kern_path_create(AT_FDCWD, filename, &path, 0);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	अगर (!IS_POSIXACL(path.dentry->d_inode))
		mode &= ~current_umask();
	error = security_path_mknod(&path, dentry, mode, dev);
	अगर (!error)
		error = vfs_mknod(mnt_user_ns(path.mnt), path.dentry->d_inode,
				  dentry, mode, new_decode_dev(dev));
	करोne_path_create(&path, dentry);
	वापस error;
पूर्ण

पूर्णांक __init init_link(स्थिर अक्षर *oldname, स्थिर अक्षर *newname)
अणु
	काष्ठा dentry *new_dentry;
	काष्ठा path old_path, new_path;
	काष्ठा user_namespace *mnt_userns;
	पूर्णांक error;

	error = kern_path(oldname, 0, &old_path);
	अगर (error)
		वापस error;

	new_dentry = kern_path_create(AT_FDCWD, newname, &new_path, 0);
	error = PTR_ERR(new_dentry);
	अगर (IS_ERR(new_dentry))
		जाओ out;

	error = -EXDEV;
	अगर (old_path.mnt != new_path.mnt)
		जाओ out_dput;
	mnt_userns = mnt_user_ns(new_path.mnt);
	error = may_linkat(mnt_userns, &old_path);
	अगर (unlikely(error))
		जाओ out_dput;
	error = security_path_link(old_path.dentry, &new_path, new_dentry);
	अगर (error)
		जाओ out_dput;
	error = vfs_link(old_path.dentry, mnt_userns, new_path.dentry->d_inode,
			 new_dentry, शून्य);
out_dput:
	करोne_path_create(&new_path, new_dentry);
out:
	path_put(&old_path);
	वापस error;
पूर्ण

पूर्णांक __init init_symlink(स्थिर अक्षर *oldname, स्थिर अक्षर *newname)
अणु
	काष्ठा dentry *dentry;
	काष्ठा path path;
	पूर्णांक error;

	dentry = kern_path_create(AT_FDCWD, newname, &path, 0);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);
	error = security_path_symlink(&path, dentry, oldname);
	अगर (!error)
		error = vfs_symlink(mnt_user_ns(path.mnt), path.dentry->d_inode,
				    dentry, oldname);
	करोne_path_create(&path, dentry);
	वापस error;
पूर्ण

पूर्णांक __init init_unlink(स्थिर अक्षर *pathname)
अणु
	वापस करो_unlinkat(AT_FDCWD, getname_kernel(pathname));
पूर्ण

पूर्णांक __init init_सूची_गढ़ो(स्थिर अक्षर *pathname, umode_t mode)
अणु
	काष्ठा dentry *dentry;
	काष्ठा path path;
	पूर्णांक error;

	dentry = kern_path_create(AT_FDCWD, pathname, &path, LOOKUP_सूचीECTORY);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);
	अगर (!IS_POSIXACL(path.dentry->d_inode))
		mode &= ~current_umask();
	error = security_path_सूची_गढ़ो(&path, dentry, mode);
	अगर (!error)
		error = vfs_सूची_गढ़ो(mnt_user_ns(path.mnt), path.dentry->d_inode,
				  dentry, mode);
	करोne_path_create(&path, dentry);
	वापस error;
पूर्ण

पूर्णांक __init init_सूची_हटाओ(स्थिर अक्षर *pathname)
अणु
	वापस करो_सूची_हटाओ(AT_FDCWD, getname_kernel(pathname));
पूर्ण

पूर्णांक __init init_uबार(अक्षर *filename, काष्ठा बारpec64 *ts)
अणु
	काष्ठा path path;
	पूर्णांक error;

	error = kern_path(filename, 0, &path);
	अगर (error)
		वापस error;
	error = vfs_uबार(&path, ts);
	path_put(&path);
	वापस error;
पूर्ण

पूर्णांक __init init_dup(काष्ठा file *file)
अणु
	पूर्णांक fd;

	fd = get_unused_fd_flags(0);
	अगर (fd < 0)
		वापस fd;
	fd_install(fd, get_file(file));
	वापस 0;
पूर्ण
