<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/tomoyo.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश <linux/lsm_hooks.h>
#समावेश "common.h"

/**
 * tomoyo_करोमुख्य - Get "struct tomoyo_domain_info" क्रम current thपढ़ो.
 *
 * Returns poपूर्णांकer to "struct tomoyo_domain_info" क्रम current thपढ़ो.
 */
काष्ठा tomoyo_करोमुख्य_info *tomoyo_करोमुख्य(व्योम)
अणु
	काष्ठा tomoyo_task *s = tomoyo_task(current);

	अगर (s->old_करोमुख्य_info && !current->in_execve) अणु
		atomic_dec(&s->old_करोमुख्य_info->users);
		s->old_करोमुख्य_info = शून्य;
	पूर्ण
	वापस s->करोमुख्य_info;
पूर्ण

/**
 * tomoyo_cred_prepare - Target क्रम security_prepare_creds().
 *
 * @new: Poपूर्णांकer to "struct cred".
 * @old: Poपूर्णांकer to "struct cred".
 * @gfp: Memory allocation flags.
 *
 * Returns 0.
 */
अटल पूर्णांक tomoyo_cred_prepare(काष्ठा cred *new, स्थिर काष्ठा cred *old,
			       gfp_t gfp)
अणु
	/* Restore old_करोमुख्य_info saved by previous execve() request. */
	काष्ठा tomoyo_task *s = tomoyo_task(current);

	अगर (s->old_करोमुख्य_info && !current->in_execve) अणु
		atomic_dec(&s->करोमुख्य_info->users);
		s->करोमुख्य_info = s->old_करोमुख्य_info;
		s->old_करोमुख्य_info = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * tomoyo_bprm_committed_creds - Target क्रम security_bprm_committed_creds().
 *
 * @bprm: Poपूर्णांकer to "struct linux_binprm".
 */
अटल व्योम tomoyo_bprm_committed_creds(काष्ठा linux_binprm *bprm)
अणु
	/* Clear old_करोमुख्य_info saved by execve() request. */
	काष्ठा tomoyo_task *s = tomoyo_task(current);

	atomic_dec(&s->old_करोमुख्य_info->users);
	s->old_करोमुख्य_info = शून्य;
पूर्ण

#अगर_अघोषित CONFIG_SECURITY_TOMOYO_OMIT_USERSPACE_LOADER
/**
 * tomoyo_bprm_क्रम_exec - Target क्रम security_bprm_creds_क्रम_exec().
 *
 * @bprm: Poपूर्णांकer to "struct linux_binprm".
 *
 * Returns 0.
 */
अटल पूर्णांक tomoyo_bprm_creds_क्रम_exec(काष्ठा linux_binprm *bprm)
अणु
	/*
	 * Load policy अगर /sbin/tomoyo-init exists and /sbin/init is requested
	 * क्रम the first समय.
	 */
	अगर (!tomoyo_policy_loaded)
		tomoyo_load_policy(bprm->filename);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * tomoyo_bprm_check_security - Target क्रम security_bprm_check().
 *
 * @bprm: Poपूर्णांकer to "struct linux_binprm".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_bprm_check_security(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा tomoyo_task *s = tomoyo_task(current);

	/*
	 * Execute permission is checked against pathname passed to execve()
	 * using current करोमुख्य.
	 */
	अगर (!s->old_करोमुख्य_info) अणु
		स्थिर पूर्णांक idx = tomoyo_पढ़ो_lock();
		स्थिर पूर्णांक err = tomoyo_find_next_करोमुख्य(bprm);

		tomoyo_पढ़ो_unlock(idx);
		वापस err;
	पूर्ण
	/*
	 * Read permission is checked against पूर्णांकerpreters using next करोमुख्य.
	 */
	वापस tomoyo_check_खोलो_permission(s->करोमुख्य_info,
					    &bprm->file->f_path, O_RDONLY);
पूर्ण

/**
 * tomoyo_inode_getattr - Target क्रम security_inode_getattr().
 *
 * @mnt:    Poपूर्णांकer to "struct vfsmount".
 * @dentry: Poपूर्णांकer to "struct dentry".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_inode_getattr(स्थिर काष्ठा path *path)
अणु
	वापस tomoyo_path_perm(TOMOYO_TYPE_GETATTR, path, शून्य);
पूर्ण

/**
 * tomoyo_path_truncate - Target क्रम security_path_truncate().
 *
 * @path: Poपूर्णांकer to "struct path".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_truncate(स्थिर काष्ठा path *path)
अणु
	वापस tomoyo_path_perm(TOMOYO_TYPE_TRUNCATE, path, शून्य);
पूर्ण

/**
 * tomoyo_path_unlink - Target क्रम security_path_unlink().
 *
 * @parent: Poपूर्णांकer to "struct path".
 * @dentry: Poपूर्णांकer to "struct dentry".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_unlink(स्थिर काष्ठा path *parent, काष्ठा dentry *dentry)
अणु
	काष्ठा path path = अणु .mnt = parent->mnt, .dentry = dentry पूर्ण;

	वापस tomoyo_path_perm(TOMOYO_TYPE_UNLINK, &path, शून्य);
पूर्ण

/**
 * tomoyo_path_सूची_गढ़ो - Target क्रम security_path_सूची_गढ़ो().
 *
 * @parent: Poपूर्णांकer to "struct path".
 * @dentry: Poपूर्णांकer to "struct dentry".
 * @mode:   DAC permission mode.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_सूची_गढ़ो(स्थिर काष्ठा path *parent, काष्ठा dentry *dentry,
			     umode_t mode)
अणु
	काष्ठा path path = अणु .mnt = parent->mnt, .dentry = dentry पूर्ण;

	वापस tomoyo_path_number_perm(TOMOYO_TYPE_MKसूची, &path,
				       mode & S_IALLUGO);
पूर्ण

/**
 * tomoyo_path_सूची_हटाओ - Target क्रम security_path_सूची_हटाओ().
 *
 * @parent: Poपूर्णांकer to "struct path".
 * @dentry: Poपूर्णांकer to "struct dentry".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_सूची_हटाओ(स्थिर काष्ठा path *parent, काष्ठा dentry *dentry)
अणु
	काष्ठा path path = अणु .mnt = parent->mnt, .dentry = dentry पूर्ण;

	वापस tomoyo_path_perm(TOMOYO_TYPE_RMसूची, &path, शून्य);
पूर्ण

/**
 * tomoyo_path_symlink - Target क्रम security_path_symlink().
 *
 * @parent:   Poपूर्णांकer to "struct path".
 * @dentry:   Poपूर्णांकer to "struct dentry".
 * @old_name: Symlink's content.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_symlink(स्थिर काष्ठा path *parent, काष्ठा dentry *dentry,
			       स्थिर अक्षर *old_name)
अणु
	काष्ठा path path = अणु .mnt = parent->mnt, .dentry = dentry पूर्ण;

	वापस tomoyo_path_perm(TOMOYO_TYPE_SYMLINK, &path, old_name);
पूर्ण

/**
 * tomoyo_path_mknod - Target क्रम security_path_mknod().
 *
 * @parent: Poपूर्णांकer to "struct path".
 * @dentry: Poपूर्णांकer to "struct dentry".
 * @mode:   DAC permission mode.
 * @dev:    Device attributes.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_mknod(स्थिर काष्ठा path *parent, काष्ठा dentry *dentry,
			     umode_t mode, अचिन्हित पूर्णांक dev)
अणु
	काष्ठा path path = अणु .mnt = parent->mnt, .dentry = dentry पूर्ण;
	पूर्णांक type = TOMOYO_TYPE_CREATE;
	स्थिर अचिन्हित पूर्णांक perm = mode & S_IALLUGO;

	चयन (mode & S_IFMT) अणु
	हाल S_IFCHR:
		type = TOMOYO_TYPE_MKCHAR;
		अवरोध;
	हाल S_IFBLK:
		type = TOMOYO_TYPE_MKBLOCK;
		अवरोध;
	शेष:
		जाओ no_dev;
	पूर्ण
	वापस tomoyo_mkdev_perm(type, &path, perm, dev);
 no_dev:
	चयन (mode & S_IFMT) अणु
	हाल S_IFIFO:
		type = TOMOYO_TYPE_MKFIFO;
		अवरोध;
	हाल S_IFSOCK:
		type = TOMOYO_TYPE_MKSOCK;
		अवरोध;
	पूर्ण
	वापस tomoyo_path_number_perm(type, &path, perm);
पूर्ण

/**
 * tomoyo_path_link - Target क्रम security_path_link().
 *
 * @old_dentry: Poपूर्णांकer to "struct dentry".
 * @new_dir:    Poपूर्णांकer to "struct path".
 * @new_dentry: Poपूर्णांकer to "struct dentry".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_link(काष्ठा dentry *old_dentry, स्थिर काष्ठा path *new_dir,
			    काष्ठा dentry *new_dentry)
अणु
	काष्ठा path path1 = अणु .mnt = new_dir->mnt, .dentry = old_dentry पूर्ण;
	काष्ठा path path2 = अणु .mnt = new_dir->mnt, .dentry = new_dentry पूर्ण;

	वापस tomoyo_path2_perm(TOMOYO_TYPE_LINK, &path1, &path2);
पूर्ण

/**
 * tomoyo_path_नाम - Target क्रम security_path_नाम().
 *
 * @old_parent: Poपूर्णांकer to "struct path".
 * @old_dentry: Poपूर्णांकer to "struct dentry".
 * @new_parent: Poपूर्णांकer to "struct path".
 * @new_dentry: Poपूर्णांकer to "struct dentry".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_नाम(स्थिर काष्ठा path *old_parent,
			      काष्ठा dentry *old_dentry,
			      स्थिर काष्ठा path *new_parent,
			      काष्ठा dentry *new_dentry)
अणु
	काष्ठा path path1 = अणु .mnt = old_parent->mnt, .dentry = old_dentry पूर्ण;
	काष्ठा path path2 = अणु .mnt = new_parent->mnt, .dentry = new_dentry पूर्ण;

	वापस tomoyo_path2_perm(TOMOYO_TYPE_RENAME, &path1, &path2);
पूर्ण

/**
 * tomoyo_file_fcntl - Target क्रम security_file_fcntl().
 *
 * @file: Poपूर्णांकer to "struct file".
 * @cmd:  Command क्रम fcntl().
 * @arg:  Argument क्रम @cmd.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_file_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	अगर (!(cmd == F_SETFL && ((arg ^ file->f_flags) & O_APPEND)))
		वापस 0;
	वापस tomoyo_check_खोलो_permission(tomoyo_करोमुख्य(), &file->f_path,
					    O_WRONLY | (arg & O_APPEND));
पूर्ण

/**
 * tomoyo_file_खोलो - Target क्रम security_file_खोलो().
 *
 * @f:    Poपूर्णांकer to "struct file".
 * @cred: Poपूर्णांकer to "struct cred".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_file_खोलो(काष्ठा file *f)
अणु
	/* Don't check पढ़ो permission here अगर called from execve(). */
	अगर (current->in_execve)
		वापस 0;
	वापस tomoyo_check_खोलो_permission(tomoyo_करोमुख्य(), &f->f_path,
					    f->f_flags);
पूर्ण

/**
 * tomoyo_file_ioctl - Target क्रम security_file_ioctl().
 *
 * @file: Poपूर्णांकer to "struct file".
 * @cmd:  Command क्रम ioctl().
 * @arg:  Argument क्रम @cmd.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	वापस tomoyo_path_number_perm(TOMOYO_TYPE_IOCTL, &file->f_path, cmd);
पूर्ण

/**
 * tomoyo_path_chmod - Target क्रम security_path_chmod().
 *
 * @path: Poपूर्णांकer to "struct path".
 * @mode: DAC permission mode.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_chmod(स्थिर काष्ठा path *path, umode_t mode)
अणु
	वापस tomoyo_path_number_perm(TOMOYO_TYPE_CHMOD, path,
				       mode & S_IALLUGO);
पूर्ण

/**
 * tomoyo_path_chown - Target क्रम security_path_chown().
 *
 * @path: Poपूर्णांकer to "struct path".
 * @uid:  Owner ID.
 * @gid:  Group ID.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_chown(स्थिर काष्ठा path *path, kuid_t uid, kgid_t gid)
अणु
	पूर्णांक error = 0;

	अगर (uid_valid(uid))
		error = tomoyo_path_number_perm(TOMOYO_TYPE_CHOWN, path,
						from_kuid(&init_user_ns, uid));
	अगर (!error && gid_valid(gid))
		error = tomoyo_path_number_perm(TOMOYO_TYPE_CHGRP, path,
						from_kgid(&init_user_ns, gid));
	वापस error;
पूर्ण

/**
 * tomoyo_path_chroot - Target क्रम security_path_chroot().
 *
 * @path: Poपूर्णांकer to "struct path".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_path_chroot(स्थिर काष्ठा path *path)
अणु
	वापस tomoyo_path_perm(TOMOYO_TYPE_CHROOT, path, शून्य);
पूर्ण

/**
 * tomoyo_sb_mount - Target क्रम security_sb_mount().
 *
 * @dev_name: Name of device file. Maybe शून्य.
 * @path:     Poपूर्णांकer to "struct path".
 * @type:     Name of fileप्रणाली type. Maybe शून्य.
 * @flags:    Mount options.
 * @data:     Optional data. Maybe शून्य.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_sb_mount(स्थिर अक्षर *dev_name, स्थिर काष्ठा path *path,
			   स्थिर अक्षर *type, अचिन्हित दीर्घ flags, व्योम *data)
अणु
	वापस tomoyo_mount_permission(dev_name, path, type, flags, data);
पूर्ण

/**
 * tomoyo_sb_umount - Target क्रम security_sb_umount().
 *
 * @mnt:   Poपूर्णांकer to "struct vfsmount".
 * @flags: Unmount options.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_sb_umount(काष्ठा vfsmount *mnt, पूर्णांक flags)
अणु
	काष्ठा path path = अणु .mnt = mnt, .dentry = mnt->mnt_root पूर्ण;

	वापस tomoyo_path_perm(TOMOYO_TYPE_UMOUNT, &path, शून्य);
पूर्ण

/**
 * tomoyo_sb_pivotroot - Target क्रम security_sb_pivotroot().
 *
 * @old_path: Poपूर्णांकer to "struct path".
 * @new_path: Poपूर्णांकer to "struct path".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_sb_pivotroot(स्थिर काष्ठा path *old_path, स्थिर काष्ठा path *new_path)
अणु
	वापस tomoyo_path2_perm(TOMOYO_TYPE_PIVOT_ROOT, new_path, old_path);
पूर्ण

/**
 * tomoyo_socket_listen - Check permission क्रम listen().
 *
 * @sock:    Poपूर्णांकer to "struct socket".
 * @backlog: Backlog parameter.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_socket_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	वापस tomoyo_socket_listen_permission(sock);
पूर्ण

/**
 * tomoyo_socket_connect - Check permission क्रम connect().
 *
 * @sock:     Poपूर्णांकer to "struct socket".
 * @addr:     Poपूर्णांकer to "struct sockaddr".
 * @addr_len: Size of @addr.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_socket_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
				 पूर्णांक addr_len)
अणु
	वापस tomoyo_socket_connect_permission(sock, addr, addr_len);
पूर्ण

/**
 * tomoyo_socket_bind - Check permission क्रम bind().
 *
 * @sock:     Poपूर्णांकer to "struct socket".
 * @addr:     Poपूर्णांकer to "struct sockaddr".
 * @addr_len: Size of @addr.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_socket_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			      पूर्णांक addr_len)
अणु
	वापस tomoyo_socket_bind_permission(sock, addr, addr_len);
पूर्ण

/**
 * tomoyo_socket_sendmsg - Check permission क्रम sendmsg().
 *
 * @sock: Poपूर्णांकer to "struct socket".
 * @msg:  Poपूर्णांकer to "struct msghdr".
 * @size: Size of message.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_socket_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
				 पूर्णांक size)
अणु
	वापस tomoyo_socket_sendmsg_permission(sock, msg, size);
पूर्ण

काष्ठा lsm_blob_sizes tomoyo_blob_sizes __lsm_ro_after_init = अणु
	.lbs_task = माप(काष्ठा tomoyo_task),
पूर्ण;

/**
 * tomoyo_task_alloc - Target क्रम security_task_alloc().
 *
 * @task:  Poपूर्णांकer to "struct task_struct".
 * @flags: clone() flags.
 *
 * Returns 0.
 */
अटल पूर्णांक tomoyo_task_alloc(काष्ठा task_काष्ठा *task,
			     अचिन्हित दीर्घ clone_flags)
अणु
	काष्ठा tomoyo_task *old = tomoyo_task(current);
	काष्ठा tomoyo_task *new = tomoyo_task(task);

	new->करोमुख्य_info = old->करोमुख्य_info;
	atomic_inc(&new->करोमुख्य_info->users);
	new->old_करोमुख्य_info = शून्य;
	वापस 0;
पूर्ण

/**
 * tomoyo_task_मुक्त - Target क्रम security_task_मुक्त().
 *
 * @task: Poपूर्णांकer to "struct task_struct".
 */
अटल व्योम tomoyo_task_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा tomoyo_task *s = tomoyo_task(task);

	अगर (s->करोमुख्य_info) अणु
		atomic_dec(&s->करोमुख्य_info->users);
		s->करोमुख्य_info = शून्य;
	पूर्ण
	अगर (s->old_करोमुख्य_info) अणु
		atomic_dec(&s->old_करोमुख्य_info->users);
		s->old_करोमुख्य_info = शून्य;
	पूर्ण
पूर्ण

/*
 * tomoyo_security_ops is a "struct security_operations" which is used क्रम
 * रेजिस्टरing TOMOYO.
 */
अटल काष्ठा security_hook_list tomoyo_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(cred_prepare, tomoyo_cred_prepare),
	LSM_HOOK_INIT(bprm_committed_creds, tomoyo_bprm_committed_creds),
	LSM_HOOK_INIT(task_alloc, tomoyo_task_alloc),
	LSM_HOOK_INIT(task_मुक्त, tomoyo_task_मुक्त),
#अगर_अघोषित CONFIG_SECURITY_TOMOYO_OMIT_USERSPACE_LOADER
	LSM_HOOK_INIT(bprm_creds_क्रम_exec, tomoyo_bprm_creds_क्रम_exec),
#पूर्ण_अगर
	LSM_HOOK_INIT(bprm_check_security, tomoyo_bprm_check_security),
	LSM_HOOK_INIT(file_fcntl, tomoyo_file_fcntl),
	LSM_HOOK_INIT(file_खोलो, tomoyo_file_खोलो),
	LSM_HOOK_INIT(path_truncate, tomoyo_path_truncate),
	LSM_HOOK_INIT(path_unlink, tomoyo_path_unlink),
	LSM_HOOK_INIT(path_सूची_गढ़ो, tomoyo_path_सूची_गढ़ो),
	LSM_HOOK_INIT(path_सूची_हटाओ, tomoyo_path_सूची_हटाओ),
	LSM_HOOK_INIT(path_symlink, tomoyo_path_symlink),
	LSM_HOOK_INIT(path_mknod, tomoyo_path_mknod),
	LSM_HOOK_INIT(path_link, tomoyo_path_link),
	LSM_HOOK_INIT(path_नाम, tomoyo_path_नाम),
	LSM_HOOK_INIT(inode_getattr, tomoyo_inode_getattr),
	LSM_HOOK_INIT(file_ioctl, tomoyo_file_ioctl),
	LSM_HOOK_INIT(path_chmod, tomoyo_path_chmod),
	LSM_HOOK_INIT(path_chown, tomoyo_path_chown),
	LSM_HOOK_INIT(path_chroot, tomoyo_path_chroot),
	LSM_HOOK_INIT(sb_mount, tomoyo_sb_mount),
	LSM_HOOK_INIT(sb_umount, tomoyo_sb_umount),
	LSM_HOOK_INIT(sb_pivotroot, tomoyo_sb_pivotroot),
	LSM_HOOK_INIT(socket_bind, tomoyo_socket_bind),
	LSM_HOOK_INIT(socket_connect, tomoyo_socket_connect),
	LSM_HOOK_INIT(socket_listen, tomoyo_socket_listen),
	LSM_HOOK_INIT(socket_sendmsg, tomoyo_socket_sendmsg),
पूर्ण;

/* Lock क्रम GC. */
DEFINE_SRCU(tomoyo_ss);

पूर्णांक tomoyo_enabled __lsm_ro_after_init = 1;

/**
 * tomoyo_init - Register TOMOYO Linux as a LSM module.
 *
 * Returns 0.
 */
अटल पूर्णांक __init tomoyo_init(व्योम)
अणु
	काष्ठा tomoyo_task *s = tomoyo_task(current);

	/* रेजिस्टर ourselves with the security framework */
	security_add_hooks(tomoyo_hooks, ARRAY_SIZE(tomoyo_hooks), "tomoyo");
	pr_info("TOMOYO Linux initialized\n");
	s->करोमुख्य_info = &tomoyo_kernel_करोमुख्य;
	atomic_inc(&tomoyo_kernel_करोमुख्य.users);
	s->old_करोमुख्य_info = शून्य;
	tomoyo_mm_init();

	वापस 0;
पूर्ण

DEFINE_LSM(tomoyo) = अणु
	.name = "tomoyo",
	.enabled = &tomoyo_enabled,
	.flags = LSM_FLAG_LEGACY_MAJOR,
	.blobs = &tomoyo_blob_sizes,
	.init = tomoyo_init,
पूर्ण;
