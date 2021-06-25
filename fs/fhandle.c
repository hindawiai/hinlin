<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/syscalls.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/personality.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/compat.h>
#समावेश "internal.h"
#समावेश "mount.h"

अटल दीर्घ करो_sys_name_to_handle(काष्ठा path *path,
				  काष्ठा file_handle __user *ufh,
				  पूर्णांक __user *mnt_id)
अणु
	दीर्घ retval;
	काष्ठा file_handle f_handle;
	पूर्णांक handle_dwords, handle_bytes;
	काष्ठा file_handle *handle = शून्य;

	/*
	 * We need to make sure whether the file प्रणाली
	 * support decoding of the file handle
	 */
	अगर (!path->dentry->d_sb->s_export_op ||
	    !path->dentry->d_sb->s_export_op->fh_to_dentry)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&f_handle, ufh, माप(काष्ठा file_handle)))
		वापस -EFAULT;

	अगर (f_handle.handle_bytes > MAX_HANDLE_SZ)
		वापस -EINVAL;

	handle = kदो_स्मृति(माप(काष्ठा file_handle) + f_handle.handle_bytes,
			 GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	/* convert handle size to multiple of माप(u32) */
	handle_dwords = f_handle.handle_bytes >> 2;

	/* we ask क्रम a non connected handle */
	retval = exportfs_encode_fh(path->dentry,
				    (काष्ठा fid *)handle->f_handle,
				    &handle_dwords,  0);
	handle->handle_type = retval;
	/* convert handle size to bytes */
	handle_bytes = handle_dwords * माप(u32);
	handle->handle_bytes = handle_bytes;
	अगर ((handle->handle_bytes > f_handle.handle_bytes) ||
	    (retval == खाताID_INVALID) || (retval == -ENOSPC)) अणु
		/* As per old exportfs_encode_fh करोcumentation
		 * we could वापस ENOSPC to indicate overflow
		 * But file प्रणाली वापसed 255 always. So handle
		 * both the values
		 */
		/*
		 * set the handle size to zero so we copy only
		 * non variable part of the file_handle
		 */
		handle_bytes = 0;
		retval = -EOVERFLOW;
	पूर्ण अन्यथा
		retval = 0;
	/* copy the mount id */
	अगर (put_user(real_mount(path->mnt)->mnt_id, mnt_id) ||
	    copy_to_user(ufh, handle,
			 माप(काष्ठा file_handle) + handle_bytes))
		retval = -EFAULT;
	kमुक्त(handle);
	वापस retval;
पूर्ण

/**
 * sys_name_to_handle_at: convert name to handle
 * @dfd: directory relative to which name is पूर्णांकerpreted अगर not असलolute
 * @name: name that should be converted to handle.
 * @handle: resulting file handle
 * @mnt_id: mount id of the file प्रणाली containing the file
 * @flag: flag value to indicate whether to follow symlink or not
 *
 * @handle->handle_size indicate the space available to store the
 * variable part of the file handle in bytes. If there is not
 * enough space, the field is updated to वापस the minimum
 * value required.
 */
SYSCALL_DEFINE5(name_to_handle_at, पूर्णांक, dfd, स्थिर अक्षर __user *, name,
		काष्ठा file_handle __user *, handle, पूर्णांक __user *, mnt_id,
		पूर्णांक, flag)
अणु
	काष्ठा path path;
	पूर्णांक lookup_flags;
	पूर्णांक err;

	अगर ((flag & ~(AT_SYMLINK_FOLLOW | AT_EMPTY_PATH)) != 0)
		वापस -EINVAL;

	lookup_flags = (flag & AT_SYMLINK_FOLLOW) ? LOOKUP_FOLLOW : 0;
	अगर (flag & AT_EMPTY_PATH)
		lookup_flags |= LOOKUP_EMPTY;
	err = user_path_at(dfd, name, lookup_flags, &path);
	अगर (!err) अणु
		err = करो_sys_name_to_handle(&path, handle, mnt_id);
		path_put(&path);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा vfsmount *get_vfsmount_from_fd(पूर्णांक fd)
अणु
	काष्ठा vfsmount *mnt;

	अगर (fd == AT_FDCWD) अणु
		काष्ठा fs_काष्ठा *fs = current->fs;
		spin_lock(&fs->lock);
		mnt = mntget(fs->pwd.mnt);
		spin_unlock(&fs->lock);
	पूर्ण अन्यथा अणु
		काष्ठा fd f = fdget(fd);
		अगर (!f.file)
			वापस ERR_PTR(-EBADF);
		mnt = mntget(f.file->f_path.mnt);
		fdput(f);
	पूर्ण
	वापस mnt;
पूर्ण

अटल पूर्णांक vfs_dentry_acceptable(व्योम *context, काष्ठा dentry *dentry)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक करो_handle_to_path(पूर्णांक mountdirfd, काष्ठा file_handle *handle,
			     काष्ठा path *path)
अणु
	पूर्णांक retval = 0;
	पूर्णांक handle_dwords;

	path->mnt = get_vfsmount_from_fd(mountdirfd);
	अगर (IS_ERR(path->mnt)) अणु
		retval = PTR_ERR(path->mnt);
		जाओ out_err;
	पूर्ण
	/* change the handle size to multiple of माप(u32) */
	handle_dwords = handle->handle_bytes >> 2;
	path->dentry = exportfs_decode_fh(path->mnt,
					  (काष्ठा fid *)handle->f_handle,
					  handle_dwords, handle->handle_type,
					  vfs_dentry_acceptable, शून्य);
	अगर (IS_ERR(path->dentry)) अणु
		retval = PTR_ERR(path->dentry);
		जाओ out_mnt;
	पूर्ण
	वापस 0;
out_mnt:
	mntput(path->mnt);
out_err:
	वापस retval;
पूर्ण

अटल पूर्णांक handle_to_path(पूर्णांक mountdirfd, काष्ठा file_handle __user *ufh,
		   काष्ठा path *path)
अणु
	पूर्णांक retval = 0;
	काष्ठा file_handle f_handle;
	काष्ठा file_handle *handle = शून्य;

	/*
	 * With handle we करोn't look at the execute bit on the
	 * directory. Ideally we would like CAP_DAC_SEARCH.
	 * But we करोn't have that
	 */
	अगर (!capable(CAP_DAC_READ_SEARCH)) अणु
		retval = -EPERM;
		जाओ out_err;
	पूर्ण
	अगर (copy_from_user(&f_handle, ufh, माप(काष्ठा file_handle))) अणु
		retval = -EFAULT;
		जाओ out_err;
	पूर्ण
	अगर ((f_handle.handle_bytes > MAX_HANDLE_SZ) ||
	    (f_handle.handle_bytes == 0)) अणु
		retval = -EINVAL;
		जाओ out_err;
	पूर्ण
	handle = kदो_स्मृति(माप(काष्ठा file_handle) + f_handle.handle_bytes,
			 GFP_KERNEL);
	अगर (!handle) अणु
		retval = -ENOMEM;
		जाओ out_err;
	पूर्ण
	/* copy the full handle */
	*handle = f_handle;
	अगर (copy_from_user(&handle->f_handle,
			   &ufh->f_handle,
			   f_handle.handle_bytes)) अणु
		retval = -EFAULT;
		जाओ out_handle;
	पूर्ण

	retval = करो_handle_to_path(mountdirfd, handle, path);

out_handle:
	kमुक्त(handle);
out_err:
	वापस retval;
पूर्ण

अटल दीर्घ करो_handle_खोलो(पूर्णांक mountdirfd, काष्ठा file_handle __user *ufh,
			   पूर्णांक खोलो_flag)
अणु
	दीर्घ retval = 0;
	काष्ठा path path;
	काष्ठा file *file;
	पूर्णांक fd;

	retval = handle_to_path(mountdirfd, ufh, &path);
	अगर (retval)
		वापस retval;

	fd = get_unused_fd_flags(खोलो_flag);
	अगर (fd < 0) अणु
		path_put(&path);
		वापस fd;
	पूर्ण
	file = file_खोलो_root(path.dentry, path.mnt, "", खोलो_flag, 0);
	अगर (IS_ERR(file)) अणु
		put_unused_fd(fd);
		retval =  PTR_ERR(file);
	पूर्ण अन्यथा अणु
		retval = fd;
		fsnotअगरy_खोलो(file);
		fd_install(fd, file);
	पूर्ण
	path_put(&path);
	वापस retval;
पूर्ण

/**
 * sys_खोलो_by_handle_at: Open the file handle
 * @mountdirfd: directory file descriptor
 * @handle: file handle to be खोलोed
 * @flags: खोलो flags.
 *
 * @mountdirfd indicate the directory file descriptor
 * of the mount poपूर्णांक. file handle is decoded relative
 * to the vfsmount poपूर्णांकed by the @mountdirfd. @flags
 * value is same as the खोलो(2) flags.
 */
SYSCALL_DEFINE3(खोलो_by_handle_at, पूर्णांक, mountdirfd,
		काष्ठा file_handle __user *, handle,
		पूर्णांक, flags)
अणु
	दीर्घ ret;

	अगर (क्रमce_o_largefile())
		flags |= O_LARGEखाता;

	ret = करो_handle_खोलो(mountdirfd, handle, flags);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * Exactly like fs/खोलो.c:sys_खोलो_by_handle_at(), except that it
 * करोesn't set the O_LARGEखाता flag.
 */
COMPAT_SYSCALL_DEFINE3(खोलो_by_handle_at, पूर्णांक, mountdirfd,
			     काष्ठा file_handle __user *, handle, पूर्णांक, flags)
अणु
	वापस करो_handle_खोलो(mountdirfd, handle, flags);
पूर्ण
#पूर्ण_अगर
