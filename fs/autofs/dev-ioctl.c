<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2008 Red Hat, Inc. All rights reserved.
 * Copyright 2008 Ian Kent <raven@themaw.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/compat.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/magic.h>
#समावेश <linux/nospec.h>

#समावेश "autofs_i.h"

/*
 * This module implements an पूर्णांकerface क्रम routing स्वतःfs ioctl control
 * commands via a miscellaneous device file.
 *
 * The alternate पूर्णांकerface is needed because we need to be able खोलो
 * an ioctl file descriptor on an स्वतःfs mount that may be covered by
 * another mount. This situation arises when starting स्वतःmount(8)
 * or other user space daemon which uses direct mounts or offset
 * mounts (used क्रम स्वतःfs lazy mount/umount of nested mount trees),
 * which have been left busy at service shutकरोwn.
 */

प्रकार पूर्णांक (*ioctl_fn)(काष्ठा file *, काष्ठा स्वतःfs_sb_info *,
			काष्ठा स्वतःfs_dev_ioctl *);

अटल पूर्णांक check_name(स्थिर अक्षर *name)
अणु
	अगर (!म_अक्षर(name, '/'))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Check a string करोesn't overrun the chunk of
 * memory we copied from user land.
 */
अटल पूर्णांक invalid_str(अक्षर *str, माप_प्रकार size)
अणु
	अगर (स_प्रथम(str, 0, size))
		वापस 0;
	वापस -EINVAL;
पूर्ण

/*
 * Check that the user compiled against correct version of स्वतःfs
 * misc device code.
 *
 * As well as checking the version compatibility this always copies
 * the kernel पूर्णांकerface version out.
 */
अटल पूर्णांक check_dev_ioctl_version(पूर्णांक cmd, काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	पूर्णांक err = 0;

	अगर ((param->ver_major != AUTOFS_DEV_IOCTL_VERSION_MAJOR) ||
	    (param->ver_minor > AUTOFS_DEV_IOCTL_VERSION_MINOR)) अणु
		pr_warn("ioctl control interface version mismatch: "
			"kernel(%u.%u), user(%u.%u), cmd(0x%08x)\n",
			AUTOFS_DEV_IOCTL_VERSION_MAJOR,
			AUTOFS_DEV_IOCTL_VERSION_MINOR,
			param->ver_major, param->ver_minor, cmd);
		err = -EINVAL;
	पूर्ण

	/* Fill in the kernel version. */
	param->ver_major = AUTOFS_DEV_IOCTL_VERSION_MAJOR;
	param->ver_minor = AUTOFS_DEV_IOCTL_VERSION_MINOR;

	वापस err;
पूर्ण

/*
 * Copy parameter control काष्ठा, including a possible path allocated
 * at the end of the काष्ठा.
 */
अटल काष्ठा स्वतःfs_dev_ioctl *
copy_dev_ioctl(काष्ठा स्वतःfs_dev_ioctl __user *in)
अणु
	काष्ठा स्वतःfs_dev_ioctl पंचांगp, *res;

	अगर (copy_from_user(&पंचांगp, in, AUTOFS_DEV_IOCTL_SIZE))
		वापस ERR_PTR(-EFAULT);

	अगर (पंचांगp.size < AUTOFS_DEV_IOCTL_SIZE)
		वापस ERR_PTR(-EINVAL);

	अगर (पंचांगp.size > AUTOFS_DEV_IOCTL_SIZE + PATH_MAX)
		वापस ERR_PTR(-ENAMETOOLONG);

	res = memdup_user(in, पंचांगp.size);
	अगर (!IS_ERR(res))
		res->size = पंचांगp.size;

	वापस res;
पूर्ण

अटल अंतरभूत व्योम मुक्त_dev_ioctl(काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	kमुक्त(param);
पूर्ण

/*
 * Check sanity of parameter control fields and अगर a path is present
 * check that it is terminated and contains at least one "/".
 */
अटल पूर्णांक validate_dev_ioctl(पूर्णांक cmd, काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	पूर्णांक err;

	err = check_dev_ioctl_version(cmd, param);
	अगर (err) अणु
		pr_warn("invalid device control module version "
			"supplied for cmd(0x%08x)\n", cmd);
		जाओ out;
	पूर्ण

	अगर (param->size > AUTOFS_DEV_IOCTL_SIZE) अणु
		err = invalid_str(param->path, param->size - AUTOFS_DEV_IOCTL_SIZE);
		अगर (err) अणु
			pr_warn(
			  "path string terminator missing for cmd(0x%08x)\n",
			  cmd);
			जाओ out;
		पूर्ण

		err = check_name(param->path);
		अगर (err) अणु
			pr_warn("invalid path supplied for cmd(0x%08x)\n",
				cmd);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक inr = _IOC_NR(cmd);

		अगर (inr == AUTOFS_DEV_IOCTL_OPENMOUNT_CMD ||
		    inr == AUTOFS_DEV_IOCTL_REQUESTER_CMD ||
		    inr == AUTOFS_DEV_IOCTL_ISMOUNTPOINT_CMD) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	err = 0;
out:
	वापस err;
पूर्ण

/* Return स्वतःfs dev ioctl version */
अटल पूर्णांक स्वतःfs_dev_ioctl_version(काष्ठा file *fp,
				    काष्ठा स्वतःfs_sb_info *sbi,
				    काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	/* This should have alपढ़ोy been set. */
	param->ver_major = AUTOFS_DEV_IOCTL_VERSION_MAJOR;
	param->ver_minor = AUTOFS_DEV_IOCTL_VERSION_MINOR;
	वापस 0;
पूर्ण

/* Return स्वतःfs module protocol version */
अटल पूर्णांक स्वतःfs_dev_ioctl_protover(काष्ठा file *fp,
				     काष्ठा स्वतःfs_sb_info *sbi,
				     काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	param->protover.version = sbi->version;
	वापस 0;
पूर्ण

/* Return स्वतःfs module protocol sub version */
अटल पूर्णांक स्वतःfs_dev_ioctl_protosubver(काष्ठा file *fp,
					काष्ठा स्वतःfs_sb_info *sbi,
					काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	param->protosubver.sub_version = sbi->sub_version;
	वापस 0;
पूर्ण

/* Find the topmost mount satisfying test() */
अटल पूर्णांक find_स्वतःfs_mount(स्थिर अक्षर *pathname,
			     काष्ठा path *res,
			     पूर्णांक test(स्थिर काष्ठा path *path, व्योम *data),
			     व्योम *data)
अणु
	काष्ठा path path;
	पूर्णांक err;

	err = kern_path(pathname, LOOKUP_MOUNTPOINT, &path);
	अगर (err)
		वापस err;
	err = -ENOENT;
	जबतक (path.dentry == path.mnt->mnt_root) अणु
		अगर (path.dentry->d_sb->s_magic == AUTOFS_SUPER_MAGIC) अणु
			अगर (test(&path, data)) अणु
				path_get(&path);
				*res = path;
				err = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!follow_up(&path))
			अवरोध;
	पूर्ण
	path_put(&path);
	वापस err;
पूर्ण

अटल पूर्णांक test_by_dev(स्थिर काष्ठा path *path, व्योम *p)
अणु
	वापस path->dentry->d_sb->s_dev == *(dev_t *)p;
पूर्ण

अटल पूर्णांक test_by_type(स्थिर काष्ठा path *path, व्योम *p)
अणु
	काष्ठा स्वतःfs_info *ino = स्वतःfs_dentry_ino(path->dentry);

	वापस ino && ino->sbi->type & *(अचिन्हित *)p;
पूर्ण

/*
 * Open a file descriptor on the स्वतःfs mount poपूर्णांक corresponding
 * to the given path and device number (aka. new_encode_dev(sb->s_dev)).
 */
अटल पूर्णांक स्वतःfs_dev_ioctl_खोलो_mountpoपूर्णांक(स्थिर अक्षर *name, dev_t devid)
अणु
	पूर्णांक err, fd;

	fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (likely(fd >= 0)) अणु
		काष्ठा file *filp;
		काष्ठा path path;

		err = find_स्वतःfs_mount(name, &path, test_by_dev, &devid);
		अगर (err)
			जाओ out;

		filp = dentry_खोलो(&path, O_RDONLY, current_cred());
		path_put(&path);
		अगर (IS_ERR(filp)) अणु
			err = PTR_ERR(filp);
			जाओ out;
		पूर्ण

		fd_install(fd, filp);
	पूर्ण

	वापस fd;

out:
	put_unused_fd(fd);
	वापस err;
पूर्ण

/* Open a file descriptor on an स्वतःfs mount poपूर्णांक */
अटल पूर्णांक स्वतःfs_dev_ioctl_खोलोmount(काष्ठा file *fp,
				      काष्ठा स्वतःfs_sb_info *sbi,
				      काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	स्थिर अक्षर *path;
	dev_t devid;
	पूर्णांक err, fd;

	/* param->path has been checked in validate_dev_ioctl() */

	अगर (!param->खोलोmount.devid)
		वापस -EINVAL;

	param->ioctlfd = -1;

	path = param->path;
	devid = new_decode_dev(param->खोलोmount.devid);

	err = 0;
	fd = स्वतःfs_dev_ioctl_खोलो_mountpoपूर्णांक(path, devid);
	अगर (unlikely(fd < 0)) अणु
		err = fd;
		जाओ out;
	पूर्ण

	param->ioctlfd = fd;
out:
	वापस err;
पूर्ण

/* Close file descriptor allocated above (user can also use बंद(2)). */
अटल पूर्णांक स्वतःfs_dev_ioctl_बंदmount(काष्ठा file *fp,
				       काष्ठा स्वतःfs_sb_info *sbi,
				       काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	वापस बंद_fd(param->ioctlfd);
पूर्ण

/*
 * Send "ready" status क्रम an existing रुको (either a mount or an expire
 * request).
 */
अटल पूर्णांक स्वतःfs_dev_ioctl_पढ़ोy(काष्ठा file *fp,
				  काष्ठा स्वतःfs_sb_info *sbi,
				  काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	स्वतःfs_wqt_t token;

	token = (स्वतःfs_wqt_t) param->पढ़ोy.token;
	वापस स्वतःfs_रुको_release(sbi, token, 0);
पूर्ण

/*
 * Send "fail" status क्रम an existing रुको (either a mount or an expire
 * request).
 */
अटल पूर्णांक स्वतःfs_dev_ioctl_fail(काष्ठा file *fp,
				 काष्ठा स्वतःfs_sb_info *sbi,
				 काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	स्वतःfs_wqt_t token;
	पूर्णांक status;

	token = (स्वतःfs_wqt_t) param->fail.token;
	status = param->fail.status < 0 ? param->fail.status : -ENOENT;
	वापस स्वतःfs_रुको_release(sbi, token, status);
पूर्ण

/*
 * Set the pipe fd क्रम kernel communication to the daemon.
 *
 * Normally this is set at mount using an option but अगर we
 * are reconnecting to a busy mount then we need to use this
 * to tell the स्वतःfs mount about the new kernel pipe fd. In
 * order to protect mounts against incorrectly setting the
 * pipefd we also require that the स्वतःfs mount be catatonic.
 *
 * This also sets the process group id used to identअगरy the
 * controlling process (eg. the owning स्वतःmount(8) daemon).
 */
अटल पूर्णांक स्वतःfs_dev_ioctl_setpipefd(काष्ठा file *fp,
				      काष्ठा स्वतःfs_sb_info *sbi,
				      काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	पूर्णांक pipefd;
	पूर्णांक err = 0;
	काष्ठा pid *new_pid = शून्य;

	अगर (param->setpipefd.pipefd == -1)
		वापस -EINVAL;

	pipefd = param->setpipefd.pipefd;

	mutex_lock(&sbi->wq_mutex);
	अगर (!(sbi->flags & AUTOFS_SBI_CATATONIC)) अणु
		mutex_unlock(&sbi->wq_mutex);
		वापस -EBUSY;
	पूर्ण अन्यथा अणु
		काष्ठा file *pipe;

		new_pid = get_task_pid(current, PIDTYPE_PGID);

		अगर (ns_of_pid(new_pid) != ns_of_pid(sbi->oz_pgrp)) अणु
			pr_warn("not allowed to change PID namespace\n");
			err = -EINVAL;
			जाओ out;
		पूर्ण

		pipe = fget(pipefd);
		अगर (!pipe) अणु
			err = -EBADF;
			जाओ out;
		पूर्ण
		अगर (स्वतःfs_prepare_pipe(pipe) < 0) अणु
			err = -EPIPE;
			fput(pipe);
			जाओ out;
		पूर्ण
		swap(sbi->oz_pgrp, new_pid);
		sbi->pipefd = pipefd;
		sbi->pipe = pipe;
		sbi->flags &= ~AUTOFS_SBI_CATATONIC;
	पूर्ण
out:
	put_pid(new_pid);
	mutex_unlock(&sbi->wq_mutex);
	वापस err;
पूर्ण

/*
 * Make the स्वतःfs mount poपूर्णांक catatonic, no दीर्घer responsive to
 * mount requests. Also बंदs the kernel pipe file descriptor.
 */
अटल पूर्णांक स्वतःfs_dev_ioctl_catatonic(काष्ठा file *fp,
				      काष्ठा स्वतःfs_sb_info *sbi,
				      काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	स्वतःfs_catatonic_mode(sbi);
	वापस 0;
पूर्ण

/* Set the स्वतःfs mount समयout */
अटल पूर्णांक स्वतःfs_dev_ioctl_समयout(काष्ठा file *fp,
				    काष्ठा स्वतःfs_sb_info *sbi,
				    काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = param->समयout.समयout;
	param->समयout.समयout = sbi->exp_समयout / HZ;
	sbi->exp_समयout = समयout * HZ;
	वापस 0;
पूर्ण

/*
 * Return the uid and gid of the last request क्रम the mount
 *
 * When reस्थिरructing an स्वतःfs mount tree with active mounts
 * we need to re-connect to mounts that may have used the original
 * process uid and gid (or string variations of them) क्रम mount
 * lookups within the map entry.
 */
अटल पूर्णांक स्वतःfs_dev_ioctl_requester(काष्ठा file *fp,
				      काष्ठा स्वतःfs_sb_info *sbi,
				      काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	काष्ठा स्वतःfs_info *ino;
	काष्ठा path path;
	dev_t devid;
	पूर्णांक err = -ENOENT;

	/* param->path has been checked in validate_dev_ioctl() */

	devid = sbi->sb->s_dev;

	param->requester.uid = param->requester.gid = -1;

	err = find_स्वतःfs_mount(param->path, &path, test_by_dev, &devid);
	अगर (err)
		जाओ out;

	ino = स्वतःfs_dentry_ino(path.dentry);
	अगर (ino) अणु
		err = 0;
		स्वतःfs_expire_रुको(&path, 0);
		spin_lock(&sbi->fs_lock);
		param->requester.uid =
			from_kuid_munged(current_user_ns(), ino->uid);
		param->requester.gid =
			from_kgid_munged(current_user_ns(), ino->gid);
		spin_unlock(&sbi->fs_lock);
	पूर्ण
	path_put(&path);
out:
	वापस err;
पूर्ण

/*
 * Call repeatedly until it वापसs -EAGAIN, meaning there's nothing
 * more that can be करोne.
 */
अटल पूर्णांक स्वतःfs_dev_ioctl_expire(काष्ठा file *fp,
				   काष्ठा स्वतःfs_sb_info *sbi,
				   काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	काष्ठा vfsmount *mnt;
	पूर्णांक how;

	how = param->expire.how;
	mnt = fp->f_path.mnt;

	वापस स्वतःfs_करो_expire_multi(sbi->sb, mnt, sbi, how);
पूर्ण

/* Check अगर स्वतःfs mount poपूर्णांक is in use */
अटल पूर्णांक स्वतःfs_dev_ioctl_askumount(काष्ठा file *fp,
				      काष्ठा स्वतःfs_sb_info *sbi,
				      काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	param->askumount.may_umount = 0;
	अगर (may_umount(fp->f_path.mnt))
		param->askumount.may_umount = 1;
	वापस 0;
पूर्ण

/*
 * Check अगर the given path is a mountpoपूर्णांक.
 *
 * If we are supplied with the file descriptor of an स्वतःfs
 * mount we're looking क्रम a specअगरic mount. In this हाल
 * the path is considered a mountpoपूर्णांक अगर it is itself a
 * mountpoपूर्णांक or contains a mount, such as a multi-mount
 * without a root mount. In this हाल we वापस 1 अगर the
 * path is a mount poपूर्णांक and the super magic of the covering
 * mount अगर there is one or 0 अगर it isn't a mountpoपूर्णांक.
 *
 * If we aren't supplied with a file descriptor then we
 * lookup the path and check अगर it is the root of a mount.
 * If a type is given we are looking क्रम a particular स्वतःfs
 * mount and अगर we करोn't find a match we वापस fail. If the
 * located path is the root of a mount we वापस 1 aदीर्घ with
 * the super magic of the mount or 0 otherwise.
 *
 * In both हालs the device number (as वापसed by
 * new_encode_dev()) is also वापसed.
 */
अटल पूर्णांक स्वतःfs_dev_ioctl_ismountpoपूर्णांक(काष्ठा file *fp,
					 काष्ठा स्वतःfs_sb_info *sbi,
					 काष्ठा स्वतःfs_dev_ioctl *param)
अणु
	काष्ठा path path;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक devid, magic;
	पूर्णांक err = -ENOENT;

	/* param->path has been checked in validate_dev_ioctl() */

	name = param->path;
	type = param->ismountpoपूर्णांक.in.type;

	param->ismountpoपूर्णांक.out.devid = devid = 0;
	param->ismountpoपूर्णांक.out.magic = magic = 0;

	अगर (!fp || param->ioctlfd == -1) अणु
		अगर (स्वतःfs_type_any(type))
			err = kern_path(name, LOOKUP_FOLLOW | LOOKUP_MOUNTPOINT,
					&path);
		अन्यथा
			err = find_स्वतःfs_mount(name, &path,
						test_by_type, &type);
		अगर (err)
			जाओ out;
		devid = new_encode_dev(path.dentry->d_sb->s_dev);
		err = 0;
		अगर (path.mnt->mnt_root == path.dentry) अणु
			err = 1;
			magic = path.dentry->d_sb->s_magic;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_t dev = sbi->sb->s_dev;

		err = find_स्वतःfs_mount(name, &path, test_by_dev, &dev);
		अगर (err)
			जाओ out;

		devid = new_encode_dev(dev);

		err = path_has_submounts(&path);

		अगर (follow_करोwn_one(&path))
			magic = path.dentry->d_sb->s_magic;
	पूर्ण

	param->ismountpoपूर्णांक.out.devid = devid;
	param->ismountpoपूर्णांक.out.magic = magic;
	path_put(&path);
out:
	वापस err;
पूर्ण

/*
 * Our range of ioctl numbers isn't 0 based so we need to shअगरt
 * the array index by _IOC_NR(AUTOFS_CTL_IOC_FIRST) क्रम the table
 * lookup.
 */
#घोषणा cmd_idx(cmd)	(cmd - _IOC_NR(AUTOFS_DEV_IOCTL_IOC_FIRST))

अटल ioctl_fn lookup_dev_ioctl(अचिन्हित पूर्णांक cmd)
अणु
	अटल स्थिर ioctl_fn _ioctls[] = अणु
		स्वतःfs_dev_ioctl_version,
		स्वतःfs_dev_ioctl_protover,
		स्वतःfs_dev_ioctl_protosubver,
		स्वतःfs_dev_ioctl_खोलोmount,
		स्वतःfs_dev_ioctl_बंदmount,
		स्वतःfs_dev_ioctl_पढ़ोy,
		स्वतःfs_dev_ioctl_fail,
		स्वतःfs_dev_ioctl_setpipefd,
		स्वतःfs_dev_ioctl_catatonic,
		स्वतःfs_dev_ioctl_समयout,
		स्वतःfs_dev_ioctl_requester,
		स्वतःfs_dev_ioctl_expire,
		स्वतःfs_dev_ioctl_askumount,
		स्वतःfs_dev_ioctl_ismountpoपूर्णांक,
	पूर्ण;
	अचिन्हित पूर्णांक idx = cmd_idx(cmd);

	अगर (idx >= ARRAY_SIZE(_ioctls))
		वापस शून्य;
	idx = array_index_nospec(idx, ARRAY_SIZE(_ioctls));
	वापस _ioctls[idx];
पूर्ण

/* ioctl dispatcher */
अटल पूर्णांक _स्वतःfs_dev_ioctl(अचिन्हित पूर्णांक command,
			     काष्ठा स्वतःfs_dev_ioctl __user *user)
अणु
	काष्ठा स्वतःfs_dev_ioctl *param;
	काष्ठा file *fp;
	काष्ठा स्वतःfs_sb_info *sbi;
	अचिन्हित पूर्णांक cmd_first, cmd;
	ioctl_fn fn = शून्य;
	पूर्णांक err = 0;

	cmd_first = _IOC_NR(AUTOFS_DEV_IOCTL_IOC_FIRST);
	cmd = _IOC_NR(command);

	अगर (_IOC_TYPE(command) != _IOC_TYPE(AUTOFS_DEV_IOCTL_IOC_FIRST) ||
	    cmd - cmd_first > AUTOFS_DEV_IOCTL_IOC_COUNT) अणु
		वापस -ENOTTY;
	पूर्ण

	/* Only root can use ioctls other than AUTOFS_DEV_IOCTL_VERSION_CMD
	 * and AUTOFS_DEV_IOCTL_ISMOUNTPOINT_CMD
	 */
	अगर (cmd != AUTOFS_DEV_IOCTL_VERSION_CMD &&
	    cmd != AUTOFS_DEV_IOCTL_ISMOUNTPOINT_CMD &&
	    !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/* Copy the parameters पूर्णांकo kernel space. */
	param = copy_dev_ioctl(user);
	अगर (IS_ERR(param))
		वापस PTR_ERR(param);

	err = validate_dev_ioctl(command, param);
	अगर (err)
		जाओ out;

	fn = lookup_dev_ioctl(cmd);
	अगर (!fn) अणु
		pr_warn("unknown command 0x%08x\n", command);
		err = -ENOTTY;
		जाओ out;
	पूर्ण

	fp = शून्य;
	sbi = शून्य;

	/*
	 * For obvious reasons the खोलोmount can't have a file
	 * descriptor yet. We करोn't take a reference to the
	 * file during बंद to allow क्रम immediate release,
	 * and the same क्रम retrieving ioctl version.
	 */
	अगर (cmd != AUTOFS_DEV_IOCTL_VERSION_CMD &&
	    cmd != AUTOFS_DEV_IOCTL_OPENMOUNT_CMD &&
	    cmd != AUTOFS_DEV_IOCTL_CLOSEMOUNT_CMD) अणु
		काष्ठा super_block *sb;

		fp = fget(param->ioctlfd);
		अगर (!fp) अणु
			अगर (cmd == AUTOFS_DEV_IOCTL_ISMOUNTPOINT_CMD)
				जाओ cont;
			err = -EBADF;
			जाओ out;
		पूर्ण

		sb = file_inode(fp)->i_sb;
		अगर (sb->s_type != &स्वतःfs_fs_type) अणु
			err = -EINVAL;
			fput(fp);
			जाओ out;
		पूर्ण
		sbi = स्वतःfs_sbi(sb);

		/*
		 * Admin needs to be able to set the mount catatonic in
		 * order to be able to perक्रमm the re-खोलो.
		 */
		अगर (!स्वतःfs_oz_mode(sbi) &&
		    cmd != AUTOFS_DEV_IOCTL_CATATONIC_CMD) अणु
			err = -EACCES;
			fput(fp);
			जाओ out;
		पूर्ण
	पूर्ण
cont:
	err = fn(fp, sbi, param);

	अगर (fp)
		fput(fp);
	अगर (err >= 0 && copy_to_user(user, param, AUTOFS_DEV_IOCTL_SIZE))
		err = -EFAULT;
out:
	मुक्त_dev_ioctl(param);
	वापस err;
पूर्ण

अटल दीर्घ स्वतःfs_dev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक command,
			     अचिन्हित दीर्घ u)
अणु
	पूर्णांक err;

	err = _स्वतःfs_dev_ioctl(command, (काष्ठा स्वतःfs_dev_ioctl __user *) u);
	वापस (दीर्घ) err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ स्वतःfs_dev_ioctl_compat(काष्ठा file *file, अचिन्हित पूर्णांक command,
				    अचिन्हित दीर्घ u)
अणु
	वापस स्वतःfs_dev_ioctl(file, command, (अचिन्हित दीर्घ) compat_ptr(u));
पूर्ण
#अन्यथा
#घोषणा स्वतःfs_dev_ioctl_compat शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations _dev_ioctl_fops = अणु
	.unlocked_ioctl	 = स्वतःfs_dev_ioctl,
	.compat_ioctl = स्वतःfs_dev_ioctl_compat,
	.owner	 = THIS_MODULE,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice _स्वतःfs_dev_ioctl_misc = अणु
	.minor		= AUTOFS_MINOR,
	.name		= AUTOFS_DEVICE_NAME,
	.fops		= &_dev_ioctl_fops,
	.mode           = 0644,
पूर्ण;

MODULE_ALIAS_MISCDEV(AUTOFS_MINOR);
MODULE_ALIAS("devname:autofs");

/* Register/deरेजिस्टर misc अक्षरacter device */
पूर्णांक __init स्वतःfs_dev_ioctl_init(व्योम)
अणु
	पूर्णांक r;

	r = misc_रेजिस्टर(&_स्वतःfs_dev_ioctl_misc);
	अगर (r) अणु
		pr_err("misc_register failed for control device\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

व्योम स्वतःfs_dev_ioctl_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&_स्वतःfs_dev_ioctl_misc);
पूर्ण
