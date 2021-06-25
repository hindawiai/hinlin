<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Fileप्रणाली access-by-fd.
 *
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/security.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/namei.h>
#समावेश <linux/file.h>
#समावेश <uapi/linux/mount.h>
#समावेश "internal.h"
#समावेश "mount.h"

/*
 * Allow the user to पढ़ो back any error, warning or inक्रमmational messages.
 */
अटल sमाप_प्रकार fscontext_पढ़ो(काष्ठा file *file,
			      अक्षर __user *_buf, माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा fs_context *fc = file->निजी_data;
	काष्ठा fc_log *log = fc->log.log;
	अचिन्हित पूर्णांक logsize = ARRAY_SIZE(log->buffer);
	sमाप_प्रकार ret;
	अक्षर *p;
	bool need_मुक्त;
	पूर्णांक index, n;

	ret = mutex_lock_पूर्णांकerruptible(&fc->uapi_mutex);
	अगर (ret < 0)
		वापस ret;

	अगर (log->head == log->tail) अणु
		mutex_unlock(&fc->uapi_mutex);
		वापस -ENODATA;
	पूर्ण

	index = log->tail & (logsize - 1);
	p = log->buffer[index];
	need_मुक्त = log->need_मुक्त & (1 << index);
	log->buffer[index] = शून्य;
	log->need_मुक्त &= ~(1 << index);
	log->tail++;
	mutex_unlock(&fc->uapi_mutex);

	ret = -EMSGSIZE;
	n = म_माप(p);
	अगर (n > len)
		जाओ err_मुक्त;
	ret = -EFAULT;
	अगर (copy_to_user(_buf, p, n) != 0)
		जाओ err_मुक्त;
	ret = n;

err_मुक्त:
	अगर (need_मुक्त)
		kमुक्त(p);
	वापस ret;
पूर्ण

अटल पूर्णांक fscontext_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fs_context *fc = file->निजी_data;

	अगर (fc) अणु
		file->निजी_data = शून्य;
		put_fs_context(fc);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations fscontext_fops = अणु
	.पढ़ो		= fscontext_पढ़ो,
	.release	= fscontext_release,
	.llseek		= no_llseek,
पूर्ण;

/*
 * Attach a fileप्रणाली context to a file and an fd.
 */
अटल पूर्णांक fscontext_create_fd(काष्ठा fs_context *fc, अचिन्हित पूर्णांक o_flags)
अणु
	पूर्णांक fd;

	fd = anon_inode_getfd("[fscontext]", &fscontext_fops, fc,
			      O_RDWR | o_flags);
	अगर (fd < 0)
		put_fs_context(fc);
	वापस fd;
पूर्ण

अटल पूर्णांक fscontext_alloc_log(काष्ठा fs_context *fc)
अणु
	fc->log.log = kzalloc(माप(*fc->log.log), GFP_KERNEL);
	अगर (!fc->log.log)
		वापस -ENOMEM;
	refcount_set(&fc->log.log->usage, 1);
	fc->log.log->owner = fc->fs_type->owner;
	वापस 0;
पूर्ण

/*
 * Open a fileप्रणाली by name so that it can be configured क्रम mounting.
 *
 * We are allowed to specअगरy a container in which the fileप्रणाली will be
 * खोलोed, thereby indicating which namespaces will be used (notably, which
 * network namespace will be used क्रम network fileप्रणालीs).
 */
SYSCALL_DEFINE2(fsखोलो, स्थिर अक्षर __user *, _fs_name, अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा file_प्रणाली_type *fs_type;
	काष्ठा fs_context *fc;
	स्थिर अक्षर *fs_name;
	पूर्णांक ret;

	अगर (!ns_capable(current->nsproxy->mnt_ns->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (flags & ~FSOPEN_CLOEXEC)
		वापस -EINVAL;

	fs_name = strndup_user(_fs_name, PAGE_SIZE);
	अगर (IS_ERR(fs_name))
		वापस PTR_ERR(fs_name);

	fs_type = get_fs_type(fs_name);
	kमुक्त(fs_name);
	अगर (!fs_type)
		वापस -ENODEV;

	fc = fs_context_क्रम_mount(fs_type, 0);
	put_fileप्रणाली(fs_type);
	अगर (IS_ERR(fc))
		वापस PTR_ERR(fc);

	fc->phase = FS_CONTEXT_CREATE_PARAMS;

	ret = fscontext_alloc_log(fc);
	अगर (ret < 0)
		जाओ err_fc;

	वापस fscontext_create_fd(fc, flags & FSOPEN_CLOEXEC ? O_CLOEXEC : 0);

err_fc:
	put_fs_context(fc);
	वापस ret;
पूर्ण

/*
 * Pick a superblock पूर्णांकo a context क्रम reconfiguration.
 */
SYSCALL_DEFINE3(fspick, पूर्णांक, dfd, स्थिर अक्षर __user *, path, अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा fs_context *fc;
	काष्ठा path target;
	अचिन्हित पूर्णांक lookup_flags;
	पूर्णांक ret;

	अगर (!ns_capable(current->nsproxy->mnt_ns->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर ((flags & ~(FSPICK_CLOEXEC |
		       FSPICK_SYMLINK_NOFOLLOW |
		       FSPICK_NO_AUTOMOUNT |
		       FSPICK_EMPTY_PATH)) != 0)
		वापस -EINVAL;

	lookup_flags = LOOKUP_FOLLOW | LOOKUP_AUTOMOUNT;
	अगर (flags & FSPICK_SYMLINK_NOFOLLOW)
		lookup_flags &= ~LOOKUP_FOLLOW;
	अगर (flags & FSPICK_NO_AUTOMOUNT)
		lookup_flags &= ~LOOKUP_AUTOMOUNT;
	अगर (flags & FSPICK_EMPTY_PATH)
		lookup_flags |= LOOKUP_EMPTY;
	ret = user_path_at(dfd, path, lookup_flags, &target);
	अगर (ret < 0)
		जाओ err;

	ret = -EINVAL;
	अगर (target.mnt->mnt_root != target.dentry)
		जाओ err_path;

	fc = fs_context_क्रम_reconfigure(target.dentry, 0, 0);
	अगर (IS_ERR(fc)) अणु
		ret = PTR_ERR(fc);
		जाओ err_path;
	पूर्ण

	fc->phase = FS_CONTEXT_RECONF_PARAMS;

	ret = fscontext_alloc_log(fc);
	अगर (ret < 0)
		जाओ err_fc;

	path_put(&target);
	वापस fscontext_create_fd(fc, flags & FSPICK_CLOEXEC ? O_CLOEXEC : 0);

err_fc:
	put_fs_context(fc);
err_path:
	path_put(&target);
err:
	वापस ret;
पूर्ण

/*
 * Check the state and apply the configuration.  Note that this function is
 * allowed to 'steal' the value by setting param->xxx to शून्य beक्रमe वापसing.
 */
अटल पूर्णांक vfs_fsconfig_locked(काष्ठा fs_context *fc, पूर्णांक cmd,
			       काष्ठा fs_parameter *param)
अणु
	काष्ठा super_block *sb;
	पूर्णांक ret;

	ret = finish_clean_context(fc);
	अगर (ret)
		वापस ret;
	चयन (cmd) अणु
	हाल FSCONFIG_CMD_CREATE:
		अगर (fc->phase != FS_CONTEXT_CREATE_PARAMS)
			वापस -EBUSY;
		अगर (!mount_capable(fc))
			वापस -EPERM;
		fc->phase = FS_CONTEXT_CREATING;
		ret = vfs_get_tree(fc);
		अगर (ret)
			अवरोध;
		sb = fc->root->d_sb;
		ret = security_sb_kern_mount(sb);
		अगर (unlikely(ret)) अणु
			fc_drop_locked(fc);
			अवरोध;
		पूर्ण
		up_ग_लिखो(&sb->s_umount);
		fc->phase = FS_CONTEXT_AWAITING_MOUNT;
		वापस 0;
	हाल FSCONFIG_CMD_RECONFIGURE:
		अगर (fc->phase != FS_CONTEXT_RECONF_PARAMS)
			वापस -EBUSY;
		fc->phase = FS_CONTEXT_RECONFIGURING;
		sb = fc->root->d_sb;
		अगर (!ns_capable(sb->s_user_ns, CAP_SYS_ADMIN)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण
		करोwn_ग_लिखो(&sb->s_umount);
		ret = reconfigure_super(fc);
		up_ग_लिखो(&sb->s_umount);
		अगर (ret)
			अवरोध;
		vfs_clean_context(fc);
		वापस 0;
	शेष:
		अगर (fc->phase != FS_CONTEXT_CREATE_PARAMS &&
		    fc->phase != FS_CONTEXT_RECONF_PARAMS)
			वापस -EBUSY;

		वापस vfs_parse_fs_param(fc, param);
	पूर्ण
	fc->phase = FS_CONTEXT_FAILED;
	वापस ret;
पूर्ण

/**
 * sys_fsconfig - Set parameters and trigger actions on a context
 * @fd: The fileप्रणाली context to act upon
 * @cmd: The action to take
 * @_key: Where appropriate, the parameter key to set
 * @_value: Where appropriate, the parameter value to set
 * @aux: Additional inक्रमmation क्रम the value
 *
 * This प्रणाली call is used to set parameters on a context, including
 * superblock settings, data source and security labelling.
 *
 * Actions include triggering the creation of a superblock and the
 * reconfiguration of the superblock attached to the specअगरied context.
 *
 * When setting a parameter, @cmd indicates the type of value being proposed
 * and @_key indicates the parameter to be altered.
 *
 * @_value and @aux are used to specअगरy the value, should a value be required:
 *
 * (*) fsconfig_set_flag: No value is specअगरied.  The parameter must be boolean
 *     in nature.  The key may be prefixed with "no" to invert the
 *     setting. @_value must be शून्य and @aux must be 0.
 *
 * (*) fsconfig_set_string: A string value is specअगरied.  The parameter can be
 *     expecting boolean, पूर्णांकeger, string or take a path.  A conversion to an
 *     appropriate type will be attempted (which may include looking up as a
 *     path).  @_value poपूर्णांकs to a NUL-terminated string and @aux must be 0.
 *
 * (*) fsconfig_set_binary: A binary blob is specअगरied.  @_value poपूर्णांकs to the
 *     blob and @aux indicates its size.  The parameter must be expecting a
 *     blob.
 *
 * (*) fsconfig_set_path: A non-empty path is specअगरied.  The parameter must be
 *     expecting a path object.  @_value poपूर्णांकs to a NUL-terminated string that
 *     is the path and @aux is a file descriptor at which to start a relative
 *     lookup or AT_FDCWD.
 *
 * (*) fsconfig_set_path_empty: As fsconfig_set_path, but with AT_EMPTY_PATH
 *     implied.
 *
 * (*) fsconfig_set_fd: An खोलो file descriptor is specअगरied.  @_value must be
 *     शून्य and @aux indicates the file descriptor.
 */
SYSCALL_DEFINE5(fsconfig,
		पूर्णांक, fd,
		अचिन्हित पूर्णांक, cmd,
		स्थिर अक्षर __user *, _key,
		स्थिर व्योम __user *, _value,
		पूर्णांक, aux)
अणु
	काष्ठा fs_context *fc;
	काष्ठा fd f;
	पूर्णांक ret;
	पूर्णांक lookup_flags = 0;

	काष्ठा fs_parameter param = अणु
		.type	= fs_value_is_undefined,
	पूर्ण;

	अगर (fd < 0)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल FSCONFIG_SET_FLAG:
		अगर (!_key || _value || aux)
			वापस -EINVAL;
		अवरोध;
	हाल FSCONFIG_SET_STRING:
		अगर (!_key || !_value || aux)
			वापस -EINVAL;
		अवरोध;
	हाल FSCONFIG_SET_BINARY:
		अगर (!_key || !_value || aux <= 0 || aux > 1024 * 1024)
			वापस -EINVAL;
		अवरोध;
	हाल FSCONFIG_SET_PATH:
	हाल FSCONFIG_SET_PATH_EMPTY:
		अगर (!_key || !_value || (aux != AT_FDCWD && aux < 0))
			वापस -EINVAL;
		अवरोध;
	हाल FSCONFIG_SET_FD:
		अगर (!_key || _value || aux < 0)
			वापस -EINVAL;
		अवरोध;
	हाल FSCONFIG_CMD_CREATE:
	हाल FSCONFIG_CMD_RECONFIGURE:
		अगर (_key || _value || aux)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	f = fdget(fd);
	अगर (!f.file)
		वापस -EBADF;
	ret = -EINVAL;
	अगर (f.file->f_op != &fscontext_fops)
		जाओ out_f;

	fc = f.file->निजी_data;
	अगर (fc->ops == &legacy_fs_context_ops) अणु
		चयन (cmd) अणु
		हाल FSCONFIG_SET_BINARY:
		हाल FSCONFIG_SET_PATH:
		हाल FSCONFIG_SET_PATH_EMPTY:
		हाल FSCONFIG_SET_FD:
			ret = -EOPNOTSUPP;
			जाओ out_f;
		पूर्ण
	पूर्ण

	अगर (_key) अणु
		param.key = strndup_user(_key, 256);
		अगर (IS_ERR(param.key)) अणु
			ret = PTR_ERR(param.key);
			जाओ out_f;
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल FSCONFIG_SET_FLAG:
		param.type = fs_value_is_flag;
		अवरोध;
	हाल FSCONFIG_SET_STRING:
		param.type = fs_value_is_string;
		param.string = strndup_user(_value, 256);
		अगर (IS_ERR(param.string)) अणु
			ret = PTR_ERR(param.string);
			जाओ out_key;
		पूर्ण
		param.size = म_माप(param.string);
		अवरोध;
	हाल FSCONFIG_SET_BINARY:
		param.type = fs_value_is_blob;
		param.size = aux;
		param.blob = memdup_user_nul(_value, aux);
		अगर (IS_ERR(param.blob)) अणु
			ret = PTR_ERR(param.blob);
			जाओ out_key;
		पूर्ण
		अवरोध;
	हाल FSCONFIG_SET_PATH_EMPTY:
		lookup_flags = LOOKUP_EMPTY;
		fallthrough;
	हाल FSCONFIG_SET_PATH:
		param.type = fs_value_is_filename;
		param.name = getname_flags(_value, lookup_flags, शून्य);
		अगर (IS_ERR(param.name)) अणु
			ret = PTR_ERR(param.name);
			जाओ out_key;
		पूर्ण
		param.dirfd = aux;
		param.size = म_माप(param.name->name);
		अवरोध;
	हाल FSCONFIG_SET_FD:
		param.type = fs_value_is_file;
		ret = -EBADF;
		param.file = fget(aux);
		अगर (!param.file)
			जाओ out_key;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&fc->uapi_mutex);
	अगर (ret == 0) अणु
		ret = vfs_fsconfig_locked(fc, cmd, &param);
		mutex_unlock(&fc->uapi_mutex);
	पूर्ण

	/* Clean up the our record of any value that we obtained from
	 * userspace.  Note that the value may have been stolen by the LSM or
	 * fileप्रणाली, in which हाल the value poपूर्णांकer will have been cleared.
	 */
	चयन (cmd) अणु
	हाल FSCONFIG_SET_STRING:
	हाल FSCONFIG_SET_BINARY:
		kमुक्त(param.string);
		अवरोध;
	हाल FSCONFIG_SET_PATH:
	हाल FSCONFIG_SET_PATH_EMPTY:
		अगर (param.name)
			putname(param.name);
		अवरोध;
	हाल FSCONFIG_SET_FD:
		अगर (param.file)
			fput(param.file);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out_key:
	kमुक्त(param.key);
out_f:
	fdput(f);
	वापस ret;
पूर्ण
