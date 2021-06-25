<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * umd - User mode driver support
 */
#समावेश <linux/shmem_fs.h>
#समावेश <linux/pipe_fs_i.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/task_work.h>
#समावेश <linux/usermode_driver.h>

अटल काष्ठा vfsmount *blob_to_mnt(स्थिर व्योम *data, माप_प्रकार len, स्थिर अक्षर *name)
अणु
	काष्ठा file_प्रणाली_type *type;
	काष्ठा vfsmount *mnt;
	काष्ठा file *file;
	sमाप_प्रकार written;
	loff_t pos = 0;

	type = get_fs_type("tmpfs");
	अगर (!type)
		वापस ERR_PTR(-ENODEV);

	mnt = kern_mount(type);
	put_fileप्रणाली(type);
	अगर (IS_ERR(mnt))
		वापस mnt;

	file = file_खोलो_root(mnt->mnt_root, mnt, name, O_CREAT | O_WRONLY, 0700);
	अगर (IS_ERR(file)) अणु
		mntput(mnt);
		वापस ERR_CAST(file);
	पूर्ण

	written = kernel_ग_लिखो(file, data, len, &pos);
	अगर (written != len) अणु
		पूर्णांक err = written;
		अगर (err >= 0)
			err = -ENOMEM;
		filp_बंद(file, शून्य);
		mntput(mnt);
		वापस ERR_PTR(err);
	पूर्ण

	fput(file);

	/* Flush delayed fput so exec can खोलो the file पढ़ो-only */
	flush_delayed_fput();
	task_work_run();
	वापस mnt;
पूर्ण

/**
 * umd_load_blob - Remember a blob of bytes क्रम विभाजन_usermode_driver
 * @info: inक्रमmation about usermode driver
 * @data: a blob of bytes that can be executed as a file
 * @len:  The lentgh of the blob
 *
 */
पूर्णांक umd_load_blob(काष्ठा umd_info *info, स्थिर व्योम *data, माप_प्रकार len)
अणु
	काष्ठा vfsmount *mnt;

	अगर (WARN_ON_ONCE(info->wd.dentry || info->wd.mnt))
		वापस -EBUSY;

	mnt = blob_to_mnt(data, len, info->driver_name);
	अगर (IS_ERR(mnt))
		वापस PTR_ERR(mnt);

	info->wd.mnt = mnt;
	info->wd.dentry = mnt->mnt_root;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(umd_load_blob);

/**
 * umd_unload_blob - Disassociate @info from a previously loaded blob
 * @info: inक्रमmation about usermode driver
 *
 */
पूर्णांक umd_unload_blob(काष्ठा umd_info *info)
अणु
	अगर (WARN_ON_ONCE(!info->wd.mnt ||
			 !info->wd.dentry ||
			 info->wd.mnt->mnt_root != info->wd.dentry))
		वापस -EINVAL;

	kern_unmount(info->wd.mnt);
	info->wd.mnt = शून्य;
	info->wd.dentry = शून्य;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(umd_unload_blob);

अटल पूर्णांक umd_setup(काष्ठा subprocess_info *info, काष्ठा cred *new)
अणु
	काष्ठा umd_info *umd_info = info->data;
	काष्ठा file *from_umh[2];
	काष्ठा file *to_umh[2];
	पूर्णांक err;

	/* create pipe to send data to umh */
	err = create_pipe_files(to_umh, 0);
	अगर (err)
		वापस err;
	err = replace_fd(0, to_umh[0], 0);
	fput(to_umh[0]);
	अगर (err < 0) अणु
		fput(to_umh[1]);
		वापस err;
	पूर्ण

	/* create pipe to receive data from umh */
	err = create_pipe_files(from_umh, 0);
	अगर (err) अणु
		fput(to_umh[1]);
		replace_fd(0, शून्य, 0);
		वापस err;
	पूर्ण
	err = replace_fd(1, from_umh[1], 0);
	fput(from_umh[1]);
	अगर (err < 0) अणु
		fput(to_umh[1]);
		replace_fd(0, शून्य, 0);
		fput(from_umh[0]);
		वापस err;
	पूर्ण

	set_fs_pwd(current->fs, &umd_info->wd);
	umd_info->pipe_to_umh = to_umh[1];
	umd_info->pipe_from_umh = from_umh[0];
	umd_info->tgid = get_pid(task_tgid(current));
	वापस 0;
पूर्ण

अटल व्योम umd_cleanup(काष्ठा subprocess_info *info)
अणु
	काष्ठा umd_info *umd_info = info->data;

	/* cleanup अगर umh_setup() was successful but exec failed */
	अगर (info->retval)
		umd_cleanup_helper(umd_info);
पूर्ण

/**
 * umd_cleanup_helper - release the resources which were allocated in umd_setup
 * @info: inक्रमmation about usermode driver
 */
व्योम umd_cleanup_helper(काष्ठा umd_info *info)
अणु
	fput(info->pipe_to_umh);
	fput(info->pipe_from_umh);
	put_pid(info->tgid);
	info->tgid = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(umd_cleanup_helper);

/**
 * विभाजन_usermode_driver - विभाजन a usermode driver
 * @info: inक्रमmation about usermode driver (shouldn't be शून्य)
 *
 * Returns either negative error or zero which indicates success in
 * executing a usermode driver. In such हाल 'struct umd_info *info'
 * is populated with two pipes and a tgid of the process. The caller is
 * responsible क्रम health check of the user process, समाप्तing it via
 * tgid, and closing the pipes when user process is no दीर्घer needed.
 */
पूर्णांक विभाजन_usermode_driver(काष्ठा umd_info *info)
अणु
	काष्ठा subprocess_info *sub_info;
	स्थिर अक्षर *argv[] = अणु info->driver_name, शून्य पूर्ण;
	पूर्णांक err;

	अगर (WARN_ON_ONCE(info->tgid))
		वापस -EBUSY;

	err = -ENOMEM;
	sub_info = call_usermodehelper_setup(info->driver_name,
					     (अक्षर **)argv, शून्य, GFP_KERNEL,
					     umd_setup, umd_cleanup, info);
	अगर (!sub_info)
		जाओ out;

	err = call_usermodehelper_exec(sub_info, UMH_WAIT_EXEC);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(विभाजन_usermode_driver);


