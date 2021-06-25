<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor LSM hooks.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/lsm_hooks.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/audit.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/zlib.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/mount.h>

#समावेश "include/apparmor.h"
#समावेश "include/apparmorfs.h"
#समावेश "include/audit.h"
#समावेश "include/capability.h"
#समावेश "include/cred.h"
#समावेश "include/file.h"
#समावेश "include/ipc.h"
#समावेश "include/net.h"
#समावेश "include/path.h"
#समावेश "include/label.h"
#समावेश "include/policy.h"
#समावेश "include/policy_ns.h"
#समावेश "include/procattr.h"
#समावेश "include/mount.h"
#समावेश "include/secid.h"

/* Flag indicating whether initialization completed */
पूर्णांक apparmor_initialized;

जोड़ aa_buffer अणु
	काष्ठा list_head list;
	अक्षर buffer[1];
पूर्ण;

#घोषणा RESERVE_COUNT 2
अटल पूर्णांक reserve_count = RESERVE_COUNT;
अटल पूर्णांक buffer_count;

अटल LIST_HEAD(aa_global_buffers);
अटल DEFINE_SPINLOCK(aa_buffers_lock);

/*
 * LSM hook functions
 */

/*
 * put the associated labels
 */
अटल व्योम apparmor_cred_मुक्त(काष्ठा cred *cred)
अणु
	aa_put_label(cred_label(cred));
	set_cred_label(cred, शून्य);
पूर्ण

/*
 * allocate the apparmor part of blank credentials
 */
अटल पूर्णांक apparmor_cred_alloc_blank(काष्ठा cred *cred, gfp_t gfp)
अणु
	set_cred_label(cred, शून्य);
	वापस 0;
पूर्ण

/*
 * prepare new cred label क्रम modअगरication by prepare_cred block
 */
अटल पूर्णांक apparmor_cred_prepare(काष्ठा cred *new, स्थिर काष्ठा cred *old,
				 gfp_t gfp)
अणु
	set_cred_label(new, aa_get_newest_label(cred_label(old)));
	वापस 0;
पूर्ण

/*
 * transfer the apparmor data to a blank set of creds
 */
अटल व्योम apparmor_cred_transfer(काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु
	set_cred_label(new, aa_get_newest_label(cred_label(old)));
पूर्ण

अटल व्योम apparmor_task_मुक्त(काष्ठा task_काष्ठा *task)
अणु

	aa_मुक्त_task_ctx(task_ctx(task));
पूर्ण

अटल पूर्णांक apparmor_task_alloc(काष्ठा task_काष्ठा *task,
			       अचिन्हित दीर्घ clone_flags)
अणु
	काष्ठा aa_task_ctx *new = task_ctx(task);

	aa_dup_task_ctx(new, task_ctx(current));

	वापस 0;
पूर्ण

अटल पूर्णांक apparmor_ptrace_access_check(काष्ठा task_काष्ठा *child,
					अचिन्हित पूर्णांक mode)
अणु
	काष्ठा aa_label *tracer, *tracee;
	पूर्णांक error;

	tracer = __begin_current_label_crit_section();
	tracee = aa_get_task_label(child);
	error = aa_may_ptrace(tracer, tracee,
			(mode & PTRACE_MODE_READ) ? AA_PTRACE_READ
						  : AA_PTRACE_TRACE);
	aa_put_label(tracee);
	__end_current_label_crit_section(tracer);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_ptrace_traceme(काष्ठा task_काष्ठा *parent)
अणु
	काष्ठा aa_label *tracer, *tracee;
	पूर्णांक error;

	tracee = __begin_current_label_crit_section();
	tracer = aa_get_task_label(parent);
	error = aa_may_ptrace(tracer, tracee, AA_PTRACE_TRACE);
	aa_put_label(tracer);
	__end_current_label_crit_section(tracee);

	वापस error;
पूर्ण

/* Derived from security/commoncap.c:cap_capget */
अटल पूर्णांक apparmor_capget(काष्ठा task_काष्ठा *target, kernel_cap_t *effective,
			   kernel_cap_t *inheritable, kernel_cap_t *permitted)
अणु
	काष्ठा aa_label *label;
	स्थिर काष्ठा cred *cred;

	rcu_पढ़ो_lock();
	cred = __task_cred(target);
	label = aa_get_newest_cred_label(cred);

	/*
	 * cap_capget is stacked ahead of this and will
	 * initialize effective and permitted.
	 */
	अगर (!unconfined(label)) अणु
		काष्ठा aa_profile *profile;
		काष्ठा label_it i;

		label_क्रम_each_confined(i, label, profile) अणु
			अगर (COMPLAIN_MODE(profile))
				जारी;
			*effective = cap_पूर्णांकersect(*effective,
						   profile->caps.allow);
			*permitted = cap_पूर्णांकersect(*permitted,
						   profile->caps.allow);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	aa_put_label(label);

	वापस 0;
पूर्ण

अटल पूर्णांक apparmor_capable(स्थिर काष्ठा cred *cred, काष्ठा user_namespace *ns,
			    पूर्णांक cap, अचिन्हित पूर्णांक opts)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	label = aa_get_newest_cred_label(cred);
	अगर (!unconfined(label))
		error = aa_capable(label, cap, opts);
	aa_put_label(label);

	वापस error;
पूर्ण

/**
 * common_perm - basic common permission check wrapper fn क्रम paths
 * @op: operation being checked
 * @path: path to check permission of  (NOT शून्य)
 * @mask: requested permissions mask
 * @cond: conditional info क्रम the permission request  (NOT शून्य)
 *
 * Returns: %0 अन्यथा error code अगर error or permission denied
 */
अटल पूर्णांक common_perm(स्थिर अक्षर *op, स्थिर काष्ठा path *path, u32 mask,
		       काष्ठा path_cond *cond)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	label = __begin_current_label_crit_section();
	अगर (!unconfined(label))
		error = aa_path_perm(op, label, path, 0, mask, cond);
	__end_current_label_crit_section(label);

	वापस error;
पूर्ण

/**
 * common_perm_cond - common permission wrapper around inode cond
 * @op: operation being checked
 * @path: location to check (NOT शून्य)
 * @mask: requested permissions mask
 *
 * Returns: %0 अन्यथा error code अगर error or permission denied
 */
अटल पूर्णांक common_perm_cond(स्थिर अक्षर *op, स्थिर काष्ठा path *path, u32 mask)
अणु
	काष्ठा user_namespace *mnt_userns = mnt_user_ns(path->mnt);
	काष्ठा path_cond cond = अणु
		i_uid_पूर्णांकo_mnt(mnt_userns, d_backing_inode(path->dentry)),
		d_backing_inode(path->dentry)->i_mode
	पूर्ण;

	अगर (!path_mediated_fs(path->dentry))
		वापस 0;

	वापस common_perm(op, path, mask, &cond);
पूर्ण

/**
 * common_perm_dir_dentry - common permission wrapper when path is dir, dentry
 * @op: operation being checked
 * @dir: directory of the dentry  (NOT शून्य)
 * @dentry: dentry to check  (NOT शून्य)
 * @mask: requested permissions mask
 * @cond: conditional info क्रम the permission request  (NOT शून्य)
 *
 * Returns: %0 अन्यथा error code अगर error or permission denied
 */
अटल पूर्णांक common_perm_dir_dentry(स्थिर अक्षर *op, स्थिर काष्ठा path *dir,
				  काष्ठा dentry *dentry, u32 mask,
				  काष्ठा path_cond *cond)
अणु
	काष्ठा path path = अणु .mnt = dir->mnt, .dentry = dentry पूर्ण;

	वापस common_perm(op, &path, mask, cond);
पूर्ण

/**
 * common_perm_rm - common permission wrapper क्रम operations करोing rm
 * @op: operation being checked
 * @dir: directory that the dentry is in  (NOT शून्य)
 * @dentry: dentry being rm'd  (NOT शून्य)
 * @mask: requested permission mask
 *
 * Returns: %0 अन्यथा error code अगर error or permission denied
 */
अटल पूर्णांक common_perm_rm(स्थिर अक्षर *op, स्थिर काष्ठा path *dir,
			  काष्ठा dentry *dentry, u32 mask)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा user_namespace *mnt_userns = mnt_user_ns(dir->mnt);
	काष्ठा path_cond cond = अणु पूर्ण;

	अगर (!inode || !path_mediated_fs(dentry))
		वापस 0;

	cond.uid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
	cond.mode = inode->i_mode;

	वापस common_perm_dir_dentry(op, dir, dentry, mask, &cond);
पूर्ण

/**
 * common_perm_create - common permission wrapper क्रम operations करोing create
 * @op: operation being checked
 * @dir: directory that dentry will be created in  (NOT शून्य)
 * @dentry: dentry to create   (NOT शून्य)
 * @mask: request permission mask
 * @mode: created file mode
 *
 * Returns: %0 अन्यथा error code अगर error or permission denied
 */
अटल पूर्णांक common_perm_create(स्थिर अक्षर *op, स्थिर काष्ठा path *dir,
			      काष्ठा dentry *dentry, u32 mask, umode_t mode)
अणु
	काष्ठा path_cond cond = अणु current_fsuid(), mode पूर्ण;

	अगर (!path_mediated_fs(dir->dentry))
		वापस 0;

	वापस common_perm_dir_dentry(op, dir, dentry, mask, &cond);
पूर्ण

अटल पूर्णांक apparmor_path_unlink(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry)
अणु
	वापस common_perm_rm(OP_UNLINK, dir, dentry, AA_MAY_DELETE);
पूर्ण

अटल पूर्णांक apparmor_path_सूची_गढ़ो(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
			       umode_t mode)
अणु
	वापस common_perm_create(OP_MKसूची, dir, dentry, AA_MAY_CREATE,
				  S_IFसूची);
पूर्ण

अटल पूर्णांक apparmor_path_सूची_हटाओ(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry)
अणु
	वापस common_perm_rm(OP_RMसूची, dir, dentry, AA_MAY_DELETE);
पूर्ण

अटल पूर्णांक apparmor_path_mknod(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
			       umode_t mode, अचिन्हित पूर्णांक dev)
अणु
	वापस common_perm_create(OP_MKNOD, dir, dentry, AA_MAY_CREATE, mode);
पूर्ण

अटल पूर्णांक apparmor_path_truncate(स्थिर काष्ठा path *path)
अणु
	वापस common_perm_cond(OP_TRUNC, path, MAY_WRITE | AA_MAY_SETATTR);
पूर्ण

अटल पूर्णांक apparmor_path_symlink(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
				 स्थिर अक्षर *old_name)
अणु
	वापस common_perm_create(OP_SYMLINK, dir, dentry, AA_MAY_CREATE,
				  S_IFLNK);
पूर्ण

अटल पूर्णांक apparmor_path_link(काष्ठा dentry *old_dentry, स्थिर काष्ठा path *new_dir,
			      काष्ठा dentry *new_dentry)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	अगर (!path_mediated_fs(old_dentry))
		वापस 0;

	label = begin_current_label_crit_section();
	अगर (!unconfined(label))
		error = aa_path_link(label, old_dentry, new_dir, new_dentry);
	end_current_label_crit_section(label);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_path_नाम(स्थिर काष्ठा path *old_dir, काष्ठा dentry *old_dentry,
				स्थिर काष्ठा path *new_dir, काष्ठा dentry *new_dentry)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	अगर (!path_mediated_fs(old_dentry))
		वापस 0;

	label = begin_current_label_crit_section();
	अगर (!unconfined(label)) अणु
		काष्ठा user_namespace *mnt_userns = mnt_user_ns(old_dir->mnt);
		काष्ठा path old_path = अणु .mnt = old_dir->mnt,
					 .dentry = old_dentry पूर्ण;
		काष्ठा path new_path = अणु .mnt = new_dir->mnt,
					 .dentry = new_dentry पूर्ण;
		काष्ठा path_cond cond = अणु
			i_uid_पूर्णांकo_mnt(mnt_userns, d_backing_inode(old_dentry)),
			d_backing_inode(old_dentry)->i_mode
		पूर्ण;

		error = aa_path_perm(OP_RENAME_SRC, label, &old_path, 0,
				     MAY_READ | AA_MAY_GETATTR | MAY_WRITE |
				     AA_MAY_SETATTR | AA_MAY_DELETE,
				     &cond);
		अगर (!error)
			error = aa_path_perm(OP_RENAME_DEST, label, &new_path,
					     0, MAY_WRITE | AA_MAY_SETATTR |
					     AA_MAY_CREATE, &cond);

	पूर्ण
	end_current_label_crit_section(label);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_path_chmod(स्थिर काष्ठा path *path, umode_t mode)
अणु
	वापस common_perm_cond(OP_CHMOD, path, AA_MAY_CHMOD);
पूर्ण

अटल पूर्णांक apparmor_path_chown(स्थिर काष्ठा path *path, kuid_t uid, kgid_t gid)
अणु
	वापस common_perm_cond(OP_CHOWN, path, AA_MAY_CHOWN);
पूर्ण

अटल पूर्णांक apparmor_inode_getattr(स्थिर काष्ठा path *path)
अणु
	वापस common_perm_cond(OP_GETATTR, path, AA_MAY_GETATTR);
पूर्ण

अटल पूर्णांक apparmor_file_खोलो(काष्ठा file *file)
अणु
	काष्ठा aa_file_ctx *fctx = file_ctx(file);
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	अगर (!path_mediated_fs(file->f_path.dentry))
		वापस 0;

	/* If in exec, permission is handled by bprm hooks.
	 * Cache permissions granted by the previous exec check, with
	 * implicit पढ़ो and executable mmap which are required to
	 * actually execute the image.
	 */
	अगर (current->in_execve) अणु
		fctx->allow = MAY_EXEC | MAY_READ | AA_EXEC_MMAP;
		वापस 0;
	पूर्ण

	label = aa_get_newest_cred_label(file->f_cred);
	अगर (!unconfined(label)) अणु
		काष्ठा user_namespace *mnt_userns = file_mnt_user_ns(file);
		काष्ठा inode *inode = file_inode(file);
		काष्ठा path_cond cond = अणु
			i_uid_पूर्णांकo_mnt(mnt_userns, inode),
			inode->i_mode
		पूर्ण;

		error = aa_path_perm(OP_OPEN, label, &file->f_path, 0,
				     aa_map_file_to_perms(file), &cond);
		/* toकरो cache full allowed permissions set and state */
		fctx->allow = aa_map_file_to_perms(file);
	पूर्ण
	aa_put_label(label);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_file_alloc_security(काष्ठा file *file)
अणु
	काष्ठा aa_file_ctx *ctx = file_ctx(file);
	काष्ठा aa_label *label = begin_current_label_crit_section();

	spin_lock_init(&ctx->lock);
	rcu_assign_poपूर्णांकer(ctx->label, aa_get_label(label));
	end_current_label_crit_section(label);
	वापस 0;
पूर्ण

अटल व्योम apparmor_file_मुक्त_security(काष्ठा file *file)
अणु
	काष्ठा aa_file_ctx *ctx = file_ctx(file);

	अगर (ctx)
		aa_put_label(rcu_access_poपूर्णांकer(ctx->label));
पूर्ण

अटल पूर्णांक common_file_perm(स्थिर अक्षर *op, काष्ठा file *file, u32 mask,
			    bool in_atomic)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	/* करोn't reaudit files बंदd during inheritance */
	अगर (file->f_path.dentry == aa_null.dentry)
		वापस -EACCES;

	label = __begin_current_label_crit_section();
	error = aa_file_perm(op, label, file, mask, in_atomic);
	__end_current_label_crit_section(label);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_file_receive(काष्ठा file *file)
अणु
	वापस common_file_perm(OP_FRECEIVE, file, aa_map_file_to_perms(file),
				false);
पूर्ण

अटल पूर्णांक apparmor_file_permission(काष्ठा file *file, पूर्णांक mask)
अणु
	वापस common_file_perm(OP_FPERM, file, mask, false);
पूर्ण

अटल पूर्णांक apparmor_file_lock(काष्ठा file *file, अचिन्हित पूर्णांक cmd)
अणु
	u32 mask = AA_MAY_LOCK;

	अगर (cmd == F_WRLCK)
		mask |= MAY_WRITE;

	वापस common_file_perm(OP_FLOCK, file, mask, false);
पूर्ण

अटल पूर्णांक common_mmap(स्थिर अक्षर *op, काष्ठा file *file, अचिन्हित दीर्घ prot,
		       अचिन्हित दीर्घ flags, bool in_atomic)
अणु
	पूर्णांक mask = 0;

	अगर (!file || !file_ctx(file))
		वापस 0;

	अगर (prot & PROT_READ)
		mask |= MAY_READ;
	/*
	 * Private mappings करोn't require write perms since they don't
	 * ग_लिखो back to the files
	 */
	अगर ((prot & PROT_WRITE) && !(flags & MAP_PRIVATE))
		mask |= MAY_WRITE;
	अगर (prot & PROT_EXEC)
		mask |= AA_EXEC_MMAP;

	वापस common_file_perm(op, file, mask, in_atomic);
पूर्ण

अटल पूर्णांक apparmor_mmap_file(काष्ठा file *file, अचिन्हित दीर्घ reqprot,
			      अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags)
अणु
	वापस common_mmap(OP_FMMAP, file, prot, flags, GFP_ATOMIC);
पूर्ण

अटल पूर्णांक apparmor_file_mprotect(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ reqprot, अचिन्हित दीर्घ prot)
अणु
	वापस common_mmap(OP_FMPROT, vma->vm_file, prot,
			   !(vma->vm_flags & VM_SHARED) ? MAP_PRIVATE : 0,
			   false);
पूर्ण

अटल पूर्णांक apparmor_sb_mount(स्थिर अक्षर *dev_name, स्थिर काष्ठा path *path,
			     स्थिर अक्षर *type, अचिन्हित दीर्घ flags, व्योम *data)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	/* Discard magic */
	अगर ((flags & MS_MGC_MSK) == MS_MGC_VAL)
		flags &= ~MS_MGC_MSK;

	flags &= ~AA_MS_IGNORE_MASK;

	label = __begin_current_label_crit_section();
	अगर (!unconfined(label)) अणु
		अगर (flags & MS_REMOUNT)
			error = aa_remount(label, path, flags, data);
		अन्यथा अगर (flags & MS_BIND)
			error = aa_bind_mount(label, path, dev_name, flags);
		अन्यथा अगर (flags & (MS_SHARED | MS_PRIVATE | MS_SLAVE |
				  MS_UNBINDABLE))
			error = aa_mount_change_type(label, path, flags);
		अन्यथा अगर (flags & MS_MOVE)
			error = aa_move_mount(label, path, dev_name);
		अन्यथा
			error = aa_new_mount(label, dev_name, path, type,
					     flags, data);
	पूर्ण
	__end_current_label_crit_section(label);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_sb_umount(काष्ठा vfsmount *mnt, पूर्णांक flags)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	label = __begin_current_label_crit_section();
	अगर (!unconfined(label))
		error = aa_umount(label, mnt, flags);
	__end_current_label_crit_section(label);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_sb_pivotroot(स्थिर काष्ठा path *old_path,
				 स्थिर काष्ठा path *new_path)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	label = aa_get_current_label();
	अगर (!unconfined(label))
		error = aa_pivotroot(label, old_path, new_path);
	aa_put_label(label);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_getprocattr(काष्ठा task_काष्ठा *task, अक्षर *name,
				अक्षर **value)
अणु
	पूर्णांक error = -ENOENT;
	/* released below */
	स्थिर काष्ठा cred *cred = get_task_cred(task);
	काष्ठा aa_task_ctx *ctx = task_ctx(current);
	काष्ठा aa_label *label = शून्य;

	अगर (म_भेद(name, "current") == 0)
		label = aa_get_newest_label(cred_label(cred));
	अन्यथा अगर (म_भेद(name, "prev") == 0  && ctx->previous)
		label = aa_get_newest_label(ctx->previous);
	अन्यथा अगर (म_भेद(name, "exec") == 0 && ctx->onexec)
		label = aa_get_newest_label(ctx->onexec);
	अन्यथा
		error = -EINVAL;

	अगर (label)
		error = aa_getprocattr(label, value);

	aa_put_label(label);
	put_cred(cred);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_setprocattr(स्थिर अक्षर *name, व्योम *value,
				माप_प्रकार size)
अणु
	अक्षर *command, *largs = शून्य, *args = value;
	माप_प्रकार arg_size;
	पूर्णांक error;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, OP_SETPROCATTR);

	अगर (size == 0)
		वापस -EINVAL;

	/* AppArmor requires that the buffer must be null terminated aपंचांग */
	अगर (args[size - 1] != '\0') अणु
		/* null terminate */
		largs = args = kदो_स्मृति(size + 1, GFP_KERNEL);
		अगर (!args)
			वापस -ENOMEM;
		स_नकल(args, value, size);
		args[size] = '\0';
	पूर्ण

	error = -EINVAL;
	args = strim(args);
	command = strsep(&args, " ");
	अगर (!args)
		जाओ out;
	args = skip_spaces(args);
	अगर (!*args)
		जाओ out;

	arg_size = size - (args - (largs ? largs : (अक्षर *) value));
	अगर (म_भेद(name, "current") == 0) अणु
		अगर (म_भेद(command, "changehat") == 0) अणु
			error = aa_setprocattr_changehat(args, arg_size,
							 AA_CHANGE_NOFLAGS);
		पूर्ण अन्यथा अगर (म_भेद(command, "permhat") == 0) अणु
			error = aa_setprocattr_changehat(args, arg_size,
							 AA_CHANGE_TEST);
		पूर्ण अन्यथा अगर (म_भेद(command, "changeprofile") == 0) अणु
			error = aa_change_profile(args, AA_CHANGE_NOFLAGS);
		पूर्ण अन्यथा अगर (म_भेद(command, "permprofile") == 0) अणु
			error = aa_change_profile(args, AA_CHANGE_TEST);
		पूर्ण अन्यथा अगर (म_भेद(command, "stack") == 0) अणु
			error = aa_change_profile(args, AA_CHANGE_STACK);
		पूर्ण अन्यथा
			जाओ fail;
	पूर्ण अन्यथा अगर (म_भेद(name, "exec") == 0) अणु
		अगर (म_भेद(command, "exec") == 0)
			error = aa_change_profile(args, AA_CHANGE_ONEXEC);
		अन्यथा अगर (म_भेद(command, "stack") == 0)
			error = aa_change_profile(args, (AA_CHANGE_ONEXEC |
							 AA_CHANGE_STACK));
		अन्यथा
			जाओ fail;
	पूर्ण अन्यथा
		/* only support the "current" and "exec" process attributes */
		जाओ fail;

	अगर (!error)
		error = size;
out:
	kमुक्त(largs);
	वापस error;

fail:
	aad(&sa)->label = begin_current_label_crit_section();
	aad(&sa)->info = name;
	aad(&sa)->error = error = -EINVAL;
	aa_audit_msg(AUDIT_APPARMOR_DENIED, &sa, शून्य);
	end_current_label_crit_section(aad(&sa)->label);
	जाओ out;
पूर्ण

/**
 * apparmor_bprm_committing_creds - करो task cleanup on committing new creds
 * @bprm: binprm क्रम the exec  (NOT शून्य)
 */
अटल व्योम apparmor_bprm_committing_creds(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा aa_label *label = aa_current_raw_label();
	काष्ठा aa_label *new_label = cred_label(bprm->cred);

	/* bail out अगर unconfined or not changing profile */
	अगर ((new_label->proxy == label->proxy) ||
	    (unconfined(new_label)))
		वापस;

	aa_inherit_files(bprm->cred, current->files);

	current->pdeath_संकेत = 0;

	/* reset soft limits and set hard limits क्रम the new label */
	__aa_transition_rlimits(label, new_label);
पूर्ण

/**
 * apparmor_bprm_committed_cred - करो cleanup after new creds committed
 * @bprm: binprm क्रम the exec  (NOT शून्य)
 */
अटल व्योम apparmor_bprm_committed_creds(काष्ठा linux_binprm *bprm)
अणु
	/* clear out temporary/transitional state from the context */
	aa_clear_task_ctx_trans(task_ctx(current));

	वापस;
पूर्ण

अटल व्योम apparmor_task_माला_लोecid(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	काष्ठा aa_label *label = aa_get_task_label(p);
	*secid = label->secid;
	aa_put_label(label);
पूर्ण

अटल पूर्णांक apparmor_task_setrlimit(काष्ठा task_काष्ठा *task,
		अचिन्हित पूर्णांक resource, काष्ठा rlimit *new_rlim)
अणु
	काष्ठा aa_label *label = __begin_current_label_crit_section();
	पूर्णांक error = 0;

	अगर (!unconfined(label))
		error = aa_task_setrlimit(label, task, resource, new_rlim);
	__end_current_label_crit_section(label);

	वापस error;
पूर्ण

अटल पूर्णांक apparmor_task_समाप्त(काष्ठा task_काष्ठा *target, काष्ठा kernel_siginfo *info,
			      पूर्णांक sig, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा aa_label *cl, *tl;
	पूर्णांक error;

	अगर (cred) अणु
		/*
		 * Dealing with USB IO specअगरic behavior
		 */
		cl = aa_get_newest_cred_label(cred);
		tl = aa_get_task_label(target);
		error = aa_may_संकेत(cl, tl, sig);
		aa_put_label(cl);
		aa_put_label(tl);
		वापस error;
	पूर्ण

	cl = __begin_current_label_crit_section();
	tl = aa_get_task_label(target);
	error = aa_may_संकेत(cl, tl, sig);
	aa_put_label(tl);
	__end_current_label_crit_section(cl);

	वापस error;
पूर्ण

/**
 * apparmor_sk_alloc_security - allocate and attach the sk_security field
 */
अटल पूर्णांक apparmor_sk_alloc_security(काष्ठा sock *sk, पूर्णांक family, gfp_t flags)
अणु
	काष्ठा aa_sk_ctx *ctx;

	ctx = kzalloc(माप(*ctx), flags);
	अगर (!ctx)
		वापस -ENOMEM;

	SK_CTX(sk) = ctx;

	वापस 0;
पूर्ण

/**
 * apparmor_sk_मुक्त_security - मुक्त the sk_security field
 */
अटल व्योम apparmor_sk_मुक्त_security(काष्ठा sock *sk)
अणु
	काष्ठा aa_sk_ctx *ctx = SK_CTX(sk);

	SK_CTX(sk) = शून्य;
	aa_put_label(ctx->label);
	aa_put_label(ctx->peer);
	kमुक्त(ctx);
पूर्ण

/**
 * apparmor_clone_security - clone the sk_security field
 */
अटल व्योम apparmor_sk_clone_security(स्थिर काष्ठा sock *sk,
				       काष्ठा sock *newsk)
अणु
	काष्ठा aa_sk_ctx *ctx = SK_CTX(sk);
	काष्ठा aa_sk_ctx *new = SK_CTX(newsk);

	अगर (new->label)
		aa_put_label(new->label);
	new->label = aa_get_label(ctx->label);

	अगर (new->peer)
		aa_put_label(new->peer);
	new->peer = aa_get_label(ctx->peer);
पूर्ण

/**
 * apparmor_socket_create - check perms beक्रमe creating a new socket
 */
अटल पूर्णांक apparmor_socket_create(पूर्णांक family, पूर्णांक type, पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा aa_label *label;
	पूर्णांक error = 0;

	AA_BUG(in_पूर्णांकerrupt());

	label = begin_current_label_crit_section();
	अगर (!(kern || unconfined(label)))
		error = af_select(family,
				  create_perm(label, family, type, protocol),
				  aa_af_perm(label, OP_CREATE, AA_MAY_CREATE,
					     family, type, protocol));
	end_current_label_crit_section(label);

	वापस error;
पूर्ण

/**
 * apparmor_socket_post_create - setup the per-socket security काष्ठा
 *
 * Note:
 * -   kernel sockets currently labeled unconfined but we may want to
 *     move to a special kernel label
 * -   socket may not have sk here अगर created with sock_create_lite or
 *     sock_alloc. These should be accept हालs which will be handled in
 *     sock_graft.
 */
अटल पूर्णांक apparmor_socket_post_create(काष्ठा socket *sock, पूर्णांक family,
				       पूर्णांक type, पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा aa_label *label;

	अगर (kern) अणु
		काष्ठा aa_ns *ns = aa_get_current_ns();

		label = aa_get_label(ns_unconfined(ns));
		aa_put_ns(ns);
	पूर्ण अन्यथा
		label = aa_get_current_label();

	अगर (sock->sk) अणु
		काष्ठा aa_sk_ctx *ctx = SK_CTX(sock->sk);

		aa_put_label(ctx->label);
		ctx->label = aa_get_label(label);
	पूर्ण
	aa_put_label(label);

	वापस 0;
पूर्ण

/**
 * apparmor_socket_bind - check perms beक्रमe bind addr to socket
 */
अटल पूर्णांक apparmor_socket_bind(काष्ठा socket *sock,
				काष्ठा sockaddr *address, पूर्णांक addrlen)
अणु
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(!address);
	AA_BUG(in_पूर्णांकerrupt());

	वापस af_select(sock->sk->sk_family,
			 bind_perm(sock, address, addrlen),
			 aa_sk_perm(OP_BIND, AA_MAY_BIND, sock->sk));
पूर्ण

/**
 * apparmor_socket_connect - check perms beक्रमe connecting @sock to @address
 */
अटल पूर्णांक apparmor_socket_connect(काष्ठा socket *sock,
				   काष्ठा sockaddr *address, पूर्णांक addrlen)
अणु
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(!address);
	AA_BUG(in_पूर्णांकerrupt());

	वापस af_select(sock->sk->sk_family,
			 connect_perm(sock, address, addrlen),
			 aa_sk_perm(OP_CONNECT, AA_MAY_CONNECT, sock->sk));
पूर्ण

/**
 * apparmor_socket_list - check perms beक्रमe allowing listen
 */
अटल पूर्णांक apparmor_socket_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(in_पूर्णांकerrupt());

	वापस af_select(sock->sk->sk_family,
			 listen_perm(sock, backlog),
			 aa_sk_perm(OP_LISTEN, AA_MAY_LISTEN, sock->sk));
पूर्ण

/**
 * apparmor_socket_accept - check perms beक्रमe accepting a new connection.
 *
 * Note: जबतक @newsock is created and has some inक्रमmation, the accept
 *       has not been करोne.
 */
अटल पूर्णांक apparmor_socket_accept(काष्ठा socket *sock, काष्ठा socket *newsock)
अणु
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(!newsock);
	AA_BUG(in_पूर्णांकerrupt());

	वापस af_select(sock->sk->sk_family,
			 accept_perm(sock, newsock),
			 aa_sk_perm(OP_ACCEPT, AA_MAY_ACCEPT, sock->sk));
पूर्ण

अटल पूर्णांक aa_sock_msg_perm(स्थिर अक्षर *op, u32 request, काष्ठा socket *sock,
			    काष्ठा msghdr *msg, पूर्णांक size)
अणु
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(!msg);
	AA_BUG(in_पूर्णांकerrupt());

	वापस af_select(sock->sk->sk_family,
			 msg_perm(op, request, sock, msg, size),
			 aa_sk_perm(op, request, sock->sk));
पूर्ण

/**
 * apparmor_socket_sendmsg - check perms beक्रमe sending msg to another socket
 */
अटल पूर्णांक apparmor_socket_sendmsg(काष्ठा socket *sock,
				   काष्ठा msghdr *msg, पूर्णांक size)
अणु
	वापस aa_sock_msg_perm(OP_SENDMSG, AA_MAY_SEND, sock, msg, size);
पूर्ण

/**
 * apparmor_socket_recvmsg - check perms beक्रमe receiving a message
 */
अटल पूर्णांक apparmor_socket_recvmsg(काष्ठा socket *sock,
				   काष्ठा msghdr *msg, पूर्णांक size, पूर्णांक flags)
अणु
	वापस aa_sock_msg_perm(OP_RECVMSG, AA_MAY_RECEIVE, sock, msg, size);
पूर्ण

/* revaliation, get/set attr, shutकरोwn */
अटल पूर्णांक aa_sock_perm(स्थिर अक्षर *op, u32 request, काष्ठा socket *sock)
अणु
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(in_पूर्णांकerrupt());

	वापस af_select(sock->sk->sk_family,
			 sock_perm(op, request, sock),
			 aa_sk_perm(op, request, sock->sk));
पूर्ण

/**
 * apparmor_socket_माला_लोockname - check perms beक्रमe getting the local address
 */
अटल पूर्णांक apparmor_socket_माला_लोockname(काष्ठा socket *sock)
अणु
	वापस aa_sock_perm(OP_GETSOCKNAME, AA_MAY_GETATTR, sock);
पूर्ण

/**
 * apparmor_socket_getpeername - check perms beक्रमe getting remote address
 */
अटल पूर्णांक apparmor_socket_getpeername(काष्ठा socket *sock)
अणु
	वापस aa_sock_perm(OP_GETPEERNAME, AA_MAY_GETATTR, sock);
पूर्ण

/* revaliation, get/set attr, opt */
अटल पूर्णांक aa_sock_opt_perm(स्थिर अक्षर *op, u32 request, काष्ठा socket *sock,
			    पूर्णांक level, पूर्णांक optname)
अणु
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(in_पूर्णांकerrupt());

	वापस af_select(sock->sk->sk_family,
			 opt_perm(op, request, sock, level, optname),
			 aa_sk_perm(op, request, sock->sk));
पूर्ण

/**
 * apparmor_माला_लोockopt - check perms beक्रमe getting socket options
 */
अटल पूर्णांक apparmor_socket_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level,
				      पूर्णांक optname)
अणु
	वापस aa_sock_opt_perm(OP_GETSOCKOPT, AA_MAY_GETOPT, sock,
				level, optname);
पूर्ण

/**
 * apparmor_setsockopt - check perms beक्रमe setting socket options
 */
अटल पूर्णांक apparmor_socket_setsockopt(काष्ठा socket *sock, पूर्णांक level,
				      पूर्णांक optname)
अणु
	वापस aa_sock_opt_perm(OP_SETSOCKOPT, AA_MAY_SETOPT, sock,
				level, optname);
पूर्ण

/**
 * apparmor_socket_shutकरोwn - check perms beक्रमe shutting करोwn @sock conn
 */
अटल पूर्णांक apparmor_socket_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	वापस aa_sock_perm(OP_SHUTDOWN, AA_MAY_SHUTDOWN, sock);
पूर्ण

#अगर_घोषित CONFIG_NETWORK_SECMARK
/**
 * apparmor_socket_sock_recv_skb - check perms beक्रमe associating skb to sk
 *
 * Note: can not sleep may be called with locks held
 *
 * करोnt want protocol specअगरic in __skb_recv_datagram()
 * to deny an incoming connection  socket_sock_rcv_skb()
 */
अटल पूर्णांक apparmor_socket_sock_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा aa_sk_ctx *ctx = SK_CTX(sk);

	अगर (!skb->secmark)
		वापस 0;

	वापस apparmor_secmark_check(ctx->label, OP_RECVMSG, AA_MAY_RECEIVE,
				      skb->secmark, sk);
पूर्ण
#पूर्ण_अगर


अटल काष्ठा aa_label *sk_peer_label(काष्ठा sock *sk)
अणु
	काष्ठा aa_sk_ctx *ctx = SK_CTX(sk);

	अगर (ctx->peer)
		वापस ctx->peer;

	वापस ERR_PTR(-ENOPROTOOPT);
पूर्ण

/**
 * apparmor_socket_getpeersec_stream - get security context of peer
 *
 * Note: क्रम tcp only valid अगर using ipsec or cipso on lan
 */
अटल पूर्णांक apparmor_socket_getpeersec_stream(काष्ठा socket *sock,
					     अक्षर __user *optval,
					     पूर्णांक __user *optlen,
					     अचिन्हित पूर्णांक len)
अणु
	अक्षर *name;
	पूर्णांक slen, error = 0;
	काष्ठा aa_label *label;
	काष्ठा aa_label *peer;

	label = begin_current_label_crit_section();
	peer = sk_peer_label(sock->sk);
	अगर (IS_ERR(peer)) अणु
		error = PTR_ERR(peer);
		जाओ करोne;
	पूर्ण
	slen = aa_label_asxprपूर्णांक(&name, labels_ns(label), peer,
				 FLAG_SHOW_MODE | FLAG_VIEW_SUBNS |
				 FLAG_HIDDEN_UNCONFINED, GFP_KERNEL);
	/* करोn't include terminating \0 in slen, it अवरोधs some apps */
	अगर (slen < 0) अणु
		error = -ENOMEM;
	पूर्ण अन्यथा अणु
		अगर (slen > len) अणु
			error = -दुस्फल;
		पूर्ण अन्यथा अगर (copy_to_user(optval, name, slen)) अणु
			error = -EFAULT;
			जाओ out;
		पूर्ण
		अगर (put_user(slen, optlen))
			error = -EFAULT;
out:
		kमुक्त(name);

	पूर्ण

करोne:
	end_current_label_crit_section(label);

	वापस error;
पूर्ण

/**
 * apparmor_socket_getpeersec_dgram - get security label of packet
 * @sock: the peer socket
 * @skb: packet data
 * @secid: poपूर्णांकer to where to put the secid of the packet
 *
 * Sets the netlabel socket state on sk from parent
 */
अटल पूर्णांक apparmor_socket_getpeersec_dgram(काष्ठा socket *sock,
					    काष्ठा sk_buff *skb, u32 *secid)

अणु
	/* TODO: requires secid support */
	वापस -ENOPROTOOPT;
पूर्ण

/**
 * apparmor_sock_graft - Initialize newly created socket
 * @sk: child sock
 * @parent: parent socket
 *
 * Note: could set off of SOCK_CTX(parent) but need to track inode and we can
 *       just set sk security inक्रमmation off of current creating process label
 *       Labeling of sk क्रम accept हाल - probably should be sock based
 *       instead of task, because of the हाल where an implicitly labeled
 *       socket is shared by dअगरferent tasks.
 */
अटल व्योम apparmor_sock_graft(काष्ठा sock *sk, काष्ठा socket *parent)
अणु
	काष्ठा aa_sk_ctx *ctx = SK_CTX(sk);

	अगर (!ctx->label)
		ctx->label = aa_get_current_label();
पूर्ण

#अगर_घोषित CONFIG_NETWORK_SECMARK
अटल पूर्णांक apparmor_inet_conn_request(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				      काष्ठा request_sock *req)
अणु
	काष्ठा aa_sk_ctx *ctx = SK_CTX(sk);

	अगर (!skb->secmark)
		वापस 0;

	वापस apparmor_secmark_check(ctx->label, OP_CONNECT, AA_MAY_CONNECT,
				      skb->secmark, sk);
पूर्ण
#पूर्ण_अगर

/*
 * The cred blob is a poपूर्णांकer to, not an instance of, an aa_task_ctx.
 */
काष्ठा lsm_blob_sizes apparmor_blob_sizes __lsm_ro_after_init = अणु
	.lbs_cred = माप(काष्ठा aa_task_ctx *),
	.lbs_file = माप(काष्ठा aa_file_ctx),
	.lbs_task = माप(काष्ठा aa_task_ctx),
पूर्ण;

अटल काष्ठा security_hook_list apparmor_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(ptrace_access_check, apparmor_ptrace_access_check),
	LSM_HOOK_INIT(ptrace_traceme, apparmor_ptrace_traceme),
	LSM_HOOK_INIT(capget, apparmor_capget),
	LSM_HOOK_INIT(capable, apparmor_capable),

	LSM_HOOK_INIT(sb_mount, apparmor_sb_mount),
	LSM_HOOK_INIT(sb_umount, apparmor_sb_umount),
	LSM_HOOK_INIT(sb_pivotroot, apparmor_sb_pivotroot),

	LSM_HOOK_INIT(path_link, apparmor_path_link),
	LSM_HOOK_INIT(path_unlink, apparmor_path_unlink),
	LSM_HOOK_INIT(path_symlink, apparmor_path_symlink),
	LSM_HOOK_INIT(path_सूची_गढ़ो, apparmor_path_सूची_गढ़ो),
	LSM_HOOK_INIT(path_सूची_हटाओ, apparmor_path_सूची_हटाओ),
	LSM_HOOK_INIT(path_mknod, apparmor_path_mknod),
	LSM_HOOK_INIT(path_नाम, apparmor_path_नाम),
	LSM_HOOK_INIT(path_chmod, apparmor_path_chmod),
	LSM_HOOK_INIT(path_chown, apparmor_path_chown),
	LSM_HOOK_INIT(path_truncate, apparmor_path_truncate),
	LSM_HOOK_INIT(inode_getattr, apparmor_inode_getattr),

	LSM_HOOK_INIT(file_खोलो, apparmor_file_खोलो),
	LSM_HOOK_INIT(file_receive, apparmor_file_receive),
	LSM_HOOK_INIT(file_permission, apparmor_file_permission),
	LSM_HOOK_INIT(file_alloc_security, apparmor_file_alloc_security),
	LSM_HOOK_INIT(file_मुक्त_security, apparmor_file_मुक्त_security),
	LSM_HOOK_INIT(mmap_file, apparmor_mmap_file),
	LSM_HOOK_INIT(file_mprotect, apparmor_file_mprotect),
	LSM_HOOK_INIT(file_lock, apparmor_file_lock),

	LSM_HOOK_INIT(getprocattr, apparmor_getprocattr),
	LSM_HOOK_INIT(setprocattr, apparmor_setprocattr),

	LSM_HOOK_INIT(sk_alloc_security, apparmor_sk_alloc_security),
	LSM_HOOK_INIT(sk_मुक्त_security, apparmor_sk_मुक्त_security),
	LSM_HOOK_INIT(sk_clone_security, apparmor_sk_clone_security),

	LSM_HOOK_INIT(socket_create, apparmor_socket_create),
	LSM_HOOK_INIT(socket_post_create, apparmor_socket_post_create),
	LSM_HOOK_INIT(socket_bind, apparmor_socket_bind),
	LSM_HOOK_INIT(socket_connect, apparmor_socket_connect),
	LSM_HOOK_INIT(socket_listen, apparmor_socket_listen),
	LSM_HOOK_INIT(socket_accept, apparmor_socket_accept),
	LSM_HOOK_INIT(socket_sendmsg, apparmor_socket_sendmsg),
	LSM_HOOK_INIT(socket_recvmsg, apparmor_socket_recvmsg),
	LSM_HOOK_INIT(socket_माला_लोockname, apparmor_socket_माला_लोockname),
	LSM_HOOK_INIT(socket_getpeername, apparmor_socket_getpeername),
	LSM_HOOK_INIT(socket_माला_लोockopt, apparmor_socket_माला_लोockopt),
	LSM_HOOK_INIT(socket_setsockopt, apparmor_socket_setsockopt),
	LSM_HOOK_INIT(socket_shutकरोwn, apparmor_socket_shutकरोwn),
#अगर_घोषित CONFIG_NETWORK_SECMARK
	LSM_HOOK_INIT(socket_sock_rcv_skb, apparmor_socket_sock_rcv_skb),
#पूर्ण_अगर
	LSM_HOOK_INIT(socket_getpeersec_stream,
		      apparmor_socket_getpeersec_stream),
	LSM_HOOK_INIT(socket_getpeersec_dgram,
		      apparmor_socket_getpeersec_dgram),
	LSM_HOOK_INIT(sock_graft, apparmor_sock_graft),
#अगर_घोषित CONFIG_NETWORK_SECMARK
	LSM_HOOK_INIT(inet_conn_request, apparmor_inet_conn_request),
#पूर्ण_अगर

	LSM_HOOK_INIT(cred_alloc_blank, apparmor_cred_alloc_blank),
	LSM_HOOK_INIT(cred_मुक्त, apparmor_cred_मुक्त),
	LSM_HOOK_INIT(cred_prepare, apparmor_cred_prepare),
	LSM_HOOK_INIT(cred_transfer, apparmor_cred_transfer),

	LSM_HOOK_INIT(bprm_creds_क्रम_exec, apparmor_bprm_creds_क्रम_exec),
	LSM_HOOK_INIT(bprm_committing_creds, apparmor_bprm_committing_creds),
	LSM_HOOK_INIT(bprm_committed_creds, apparmor_bprm_committed_creds),

	LSM_HOOK_INIT(task_मुक्त, apparmor_task_मुक्त),
	LSM_HOOK_INIT(task_alloc, apparmor_task_alloc),
	LSM_HOOK_INIT(task_माला_लोecid_subj, apparmor_task_माला_लोecid),
	LSM_HOOK_INIT(task_माला_लोecid_obj, apparmor_task_माला_लोecid),
	LSM_HOOK_INIT(task_setrlimit, apparmor_task_setrlimit),
	LSM_HOOK_INIT(task_समाप्त, apparmor_task_समाप्त),

#अगर_घोषित CONFIG_AUDIT
	LSM_HOOK_INIT(audit_rule_init, aa_audit_rule_init),
	LSM_HOOK_INIT(audit_rule_known, aa_audit_rule_known),
	LSM_HOOK_INIT(audit_rule_match, aa_audit_rule_match),
	LSM_HOOK_INIT(audit_rule_मुक्त, aa_audit_rule_मुक्त),
#पूर्ण_अगर

	LSM_HOOK_INIT(secid_to_secctx, apparmor_secid_to_secctx),
	LSM_HOOK_INIT(secctx_to_secid, apparmor_secctx_to_secid),
	LSM_HOOK_INIT(release_secctx, apparmor_release_secctx),
पूर्ण;

/*
 * AppArmor sysfs module parameters
 */

अटल पूर्णांक param_set_aabool(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक param_get_aabool(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_aabool param_check_bool
अटल स्थिर काष्ठा kernel_param_ops param_ops_aabool = अणु
	.flags = KERNEL_PARAM_OPS_FL_NOARG,
	.set = param_set_aabool,
	.get = param_get_aabool
पूर्ण;

अटल पूर्णांक param_set_aauपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक param_get_aauपूर्णांक(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_aauपूर्णांक param_check_uपूर्णांक
अटल स्थिर काष्ठा kernel_param_ops param_ops_aauपूर्णांक = अणु
	.set = param_set_aauपूर्णांक,
	.get = param_get_aauपूर्णांक
पूर्ण;

अटल पूर्णांक param_set_aacompressionlevel(स्थिर अक्षर *val,
					स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक param_get_aacompressionlevel(अक्षर *buffer,
					स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_aacompressionlevel param_check_पूर्णांक
अटल स्थिर काष्ठा kernel_param_ops param_ops_aacompressionlevel = अणु
	.set = param_set_aacompressionlevel,
	.get = param_get_aacompressionlevel
पूर्ण;

अटल पूर्णांक param_set_aalockpolicy(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक param_get_aalockpolicy(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_aalockpolicy param_check_bool
अटल स्थिर काष्ठा kernel_param_ops param_ops_aalockpolicy = अणु
	.flags = KERNEL_PARAM_OPS_FL_NOARG,
	.set = param_set_aalockpolicy,
	.get = param_get_aalockpolicy
पूर्ण;

अटल पूर्णांक param_set_audit(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक param_get_audit(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);

अटल पूर्णांक param_set_mode(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक param_get_mode(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);

/* Flag values, also controllable via /sys/module/apparmor/parameters
 * We define special types as we want to करो additional mediation.
 */

/* AppArmor global enक्रमcement चयन - complain, enक्रमce, समाप्त */
क्रमागत profile_mode aa_g_profile_mode = APPARMOR_ENFORCE;
module_param_call(mode, param_set_mode, param_get_mode,
		  &aa_g_profile_mode, S_IRUSR | S_IWUSR);

/* whether policy verअगरication hashing is enabled */
bool aa_g_hash_policy = IS_ENABLED(CONFIG_SECURITY_APPARMOR_HASH_DEFAULT);
#अगर_घोषित CONFIG_SECURITY_APPARMOR_HASH
module_param_named(hash_policy, aa_g_hash_policy, aabool, S_IRUSR | S_IWUSR);
#पूर्ण_अगर

/* policy loaddata compression level */
पूर्णांक aa_g_rawdata_compression_level = Z_DEFAULT_COMPRESSION;
module_param_named(rawdata_compression_level, aa_g_rawdata_compression_level,
		   aacompressionlevel, 0400);

/* Debug mode */
bool aa_g_debug = IS_ENABLED(CONFIG_SECURITY_APPARMOR_DEBUG_MESSAGES);
module_param_named(debug, aa_g_debug, aabool, S_IRUSR | S_IWUSR);

/* Audit mode */
क्रमागत audit_mode aa_g_audit;
module_param_call(audit, param_set_audit, param_get_audit,
		  &aa_g_audit, S_IRUSR | S_IWUSR);

/* Determines अगर audit header is included in audited messages.  This
 * provides more context अगर the audit daemon is not running
 */
bool aa_g_audit_header = true;
module_param_named(audit_header, aa_g_audit_header, aabool,
		   S_IRUSR | S_IWUSR);

/* lock out loading/removal of policy
 * TODO: add in at boot loading of policy, which is the only way to
 *       load policy, अगर lock_policy is set
 */
bool aa_g_lock_policy;
module_param_named(lock_policy, aa_g_lock_policy, aalockpolicy,
		   S_IRUSR | S_IWUSR);

/* Syscall logging mode */
bool aa_g_logsyscall;
module_param_named(logsyscall, aa_g_logsyscall, aabool, S_IRUSR | S_IWUSR);

/* Maximum pathname length beक्रमe accesses will start getting rejected */
अचिन्हित पूर्णांक aa_g_path_max = 2 * PATH_MAX;
module_param_named(path_max, aa_g_path_max, aauपूर्णांक, S_IRUSR);

/* Determines how paranoid loading of policy is and how much verअगरication
 * on the loaded policy is करोne.
 * DEPRECATED: पढ़ो only as strict checking of load is always करोne now
 * that none root users (user namespaces) can load policy.
 */
bool aa_g_paranoid_load = true;
module_param_named(paranoid_load, aa_g_paranoid_load, aabool, S_IRUGO);

अटल पूर्णांक param_get_aaपूर्णांकbool(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक param_set_aaपूर्णांकbool(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_aaपूर्णांकbool param_check_पूर्णांक
अटल स्थिर काष्ठा kernel_param_ops param_ops_aaपूर्णांकbool = अणु
	.set = param_set_aaपूर्णांकbool,
	.get = param_get_aaपूर्णांकbool
पूर्ण;
/* Boot समय disable flag */
अटल पूर्णांक apparmor_enabled __lsm_ro_after_init = 1;
module_param_named(enabled, apparmor_enabled, aaपूर्णांकbool, 0444);

अटल पूर्णांक __init apparmor_enabled_setup(अक्षर *str)
अणु
	अचिन्हित दीर्घ enabled;
	पूर्णांक error = kम_से_अदीर्घ(str, 0, &enabled);
	अगर (!error)
		apparmor_enabled = enabled ? 1 : 0;
	वापस 1;
पूर्ण

__setup("apparmor=", apparmor_enabled_setup);

/* set global flag turning off the ability to load policy */
अटल पूर्णांक param_set_aalockpolicy(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_admin_capable(शून्य))
		वापस -EPERM;
	वापस param_set_bool(val, kp);
पूर्ण

अटल पूर्णांक param_get_aalockpolicy(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_view_capable(शून्य))
		वापस -EPERM;
	वापस param_get_bool(buffer, kp);
पूर्ण

अटल पूर्णांक param_set_aabool(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_admin_capable(शून्य))
		वापस -EPERM;
	वापस param_set_bool(val, kp);
पूर्ण

अटल पूर्णांक param_get_aabool(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_view_capable(शून्य))
		वापस -EPERM;
	वापस param_get_bool(buffer, kp);
पूर्ण

अटल पूर्णांक param_set_aauपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक error;

	अगर (!apparmor_enabled)
		वापस -EINVAL;
	/* file is ro but enक्रमce 2nd line check */
	अगर (apparmor_initialized)
		वापस -EPERM;

	error = param_set_uपूर्णांक(val, kp);
	aa_g_path_max = max_t(uपूर्णांक32_t, aa_g_path_max, माप(जोड़ aa_buffer));
	pr_info("AppArmor: buffer size set to %d bytes\n", aa_g_path_max);

	वापस error;
पूर्ण

अटल पूर्णांक param_get_aauपूर्णांक(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_view_capable(शून्य))
		वापस -EPERM;
	वापस param_get_uपूर्णांक(buffer, kp);
पूर्ण

/* Can only be set beक्रमe AppArmor is initialized (i.e. on boot cmdline). */
अटल पूर्णांक param_set_aaपूर्णांकbool(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा kernel_param kp_local;
	bool value;
	पूर्णांक error;

	अगर (apparmor_initialized)
		वापस -EPERM;

	/* Create local copy, with arg poपूर्णांकing to bool type. */
	value = !!*((पूर्णांक *)kp->arg);
	स_नकल(&kp_local, kp, माप(kp_local));
	kp_local.arg = &value;

	error = param_set_bool(val, &kp_local);
	अगर (!error)
		*((पूर्णांक *)kp->arg) = *((bool *)kp_local.arg);
	वापस error;
पूर्ण

/*
 * To aव्योम changing /sys/module/apparmor/parameters/enabled from Y/N to
 * 1/0, this converts the "int that is actually bool" back to bool क्रम
 * display in the /sys fileप्रणाली, जबतक keeping it "int" क्रम the LSM
 * infraकाष्ठाure.
 */
अटल पूर्णांक param_get_aaपूर्णांकbool(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा kernel_param kp_local;
	bool value;

	/* Create local copy, with arg poपूर्णांकing to bool type. */
	value = !!*((पूर्णांक *)kp->arg);
	स_नकल(&kp_local, kp, माप(kp_local));
	kp_local.arg = &value;

	वापस param_get_bool(buffer, &kp_local);
पूर्ण

अटल पूर्णांक param_set_aacompressionlevel(स्थिर अक्षर *val,
					स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक error;

	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized)
		वापस -EPERM;

	error = param_set_पूर्णांक(val, kp);

	aa_g_rawdata_compression_level = clamp(aa_g_rawdata_compression_level,
					       Z_NO_COMPRESSION,
					       Z_BEST_COMPRESSION);
	pr_info("AppArmor: policy rawdata compression level set to %u\n",
		aa_g_rawdata_compression_level);

	वापस error;
पूर्ण

अटल पूर्णांक param_get_aacompressionlevel(अक्षर *buffer,
					स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_view_capable(शून्य))
		वापस -EPERM;
	वापस param_get_पूर्णांक(buffer, kp);
पूर्ण

अटल पूर्णांक param_get_audit(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_view_capable(शून्य))
		वापस -EPERM;
	वापस प्र_लिखो(buffer, "%s", audit_mode_names[aa_g_audit]);
पूर्ण

अटल पूर्णांक param_set_audit(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i;

	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (!val)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_admin_capable(शून्य))
		वापस -EPERM;

	i = match_string(audit_mode_names, AUDIT_MAX_INDEX, val);
	अगर (i < 0)
		वापस -EINVAL;

	aa_g_audit = i;
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_mode(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_view_capable(शून्य))
		वापस -EPERM;

	वापस प्र_लिखो(buffer, "%s", aa_profile_mode_names[aa_g_profile_mode]);
पूर्ण

अटल पूर्णांक param_set_mode(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i;

	अगर (!apparmor_enabled)
		वापस -EINVAL;
	अगर (!val)
		वापस -EINVAL;
	अगर (apparmor_initialized && !policy_admin_capable(शून्य))
		वापस -EPERM;

	i = match_string(aa_profile_mode_names, APPARMOR_MODE_NAMES_MAX_INDEX,
			 val);
	अगर (i < 0)
		वापस -EINVAL;

	aa_g_profile_mode = i;
	वापस 0;
पूर्ण

अक्षर *aa_get_buffer(bool in_atomic)
अणु
	जोड़ aa_buffer *aa_buf;
	bool try_again = true;
	gfp_t flags = (GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN);

retry:
	spin_lock(&aa_buffers_lock);
	अगर (buffer_count > reserve_count ||
	    (in_atomic && !list_empty(&aa_global_buffers))) अणु
		aa_buf = list_first_entry(&aa_global_buffers, जोड़ aa_buffer,
					  list);
		list_del(&aa_buf->list);
		buffer_count--;
		spin_unlock(&aa_buffers_lock);
		वापस &aa_buf->buffer[0];
	पूर्ण
	अगर (in_atomic) अणु
		/*
		 * out of reserve buffers and in atomic context so increase
		 * how many buffers to keep in reserve
		 */
		reserve_count++;
		flags = GFP_ATOMIC;
	पूर्ण
	spin_unlock(&aa_buffers_lock);

	अगर (!in_atomic)
		might_sleep();
	aa_buf = kदो_स्मृति(aa_g_path_max, flags);
	अगर (!aa_buf) अणु
		अगर (try_again) अणु
			try_again = false;
			जाओ retry;
		पूर्ण
		pr_warn_once("AppArmor: Failed to allocate a memory buffer.\n");
		वापस शून्य;
	पूर्ण
	वापस &aa_buf->buffer[0];
पूर्ण

व्योम aa_put_buffer(अक्षर *buf)
अणु
	जोड़ aa_buffer *aa_buf;

	अगर (!buf)
		वापस;
	aa_buf = container_of(buf, जोड़ aa_buffer, buffer[0]);

	spin_lock(&aa_buffers_lock);
	list_add(&aa_buf->list, &aa_global_buffers);
	buffer_count++;
	spin_unlock(&aa_buffers_lock);
पूर्ण

/*
 * AppArmor init functions
 */

/**
 * set_init_ctx - set a task context and profile on the first task.
 *
 * TODO: allow setting an alternate profile than unconfined
 */
अटल पूर्णांक __init set_init_ctx(व्योम)
अणु
	काष्ठा cred *cred = (__क्रमce काष्ठा cred *)current->real_cred;

	set_cred_label(cred, aa_get_label(ns_unconfined(root_ns)));

	वापस 0;
पूर्ण

अटल व्योम destroy_buffers(व्योम)
अणु
	जोड़ aa_buffer *aa_buf;

	spin_lock(&aa_buffers_lock);
	जबतक (!list_empty(&aa_global_buffers)) अणु
		aa_buf = list_first_entry(&aa_global_buffers, जोड़ aa_buffer,
					 list);
		list_del(&aa_buf->list);
		spin_unlock(&aa_buffers_lock);
		kमुक्त(aa_buf);
		spin_lock(&aa_buffers_lock);
	पूर्ण
	spin_unlock(&aa_buffers_lock);
पूर्ण

अटल पूर्णांक __init alloc_buffers(व्योम)
अणु
	जोड़ aa_buffer *aa_buf;
	पूर्णांक i, num;

	/*
	 * A function may require two buffers at once. Usually the buffers are
	 * used क्रम a लघु period of समय and are shared. On UP kernel buffers
	 * two should be enough, with more CPUs it is possible that more
	 * buffers will be used simultaneously. The pपुनः_स्मृतिated pool may grow.
	 * This pपुनः_स्मृतिation has also the side-effect that AppArmor will be
	 * disabled early at boot अगर aa_g_path_max is extremly high.
	 */
	अगर (num_online_cpus() > 1)
		num = 4 + RESERVE_COUNT;
	अन्यथा
		num = 2 + RESERVE_COUNT;

	क्रम (i = 0; i < num; i++) अणु

		aa_buf = kदो_स्मृति(aa_g_path_max, GFP_KERNEL |
				 __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
		अगर (!aa_buf) अणु
			destroy_buffers();
			वापस -ENOMEM;
		पूर्ण
		aa_put_buffer(&aa_buf->buffer[0]);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक apparmor_करोपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अगर (!policy_admin_capable(शून्य))
		वापस -EPERM;
	अगर (!apparmor_enabled)
		वापस -EINVAL;

	वापस proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल काष्ठा ctl_path apparmor_sysctl_path[] = अणु
	अणु .procname = "kernel", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table apparmor_sysctl_table[] = अणु
	अणु
		.procname       = "unprivileged_userns_apparmor_policy",
		.data           = &unprivileged_userns_apparmor_policy,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0600,
		.proc_handler   = apparmor_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init apparmor_init_sysctl(व्योम)
अणु
	वापस रेजिस्टर_sysctl_paths(apparmor_sysctl_path,
				     apparmor_sysctl_table) ? 0 : -ENOMEM;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक apparmor_init_sysctl(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

#अगर defined(CONFIG_NETFILTER) && defined(CONFIG_NETWORK_SECMARK)
अटल अचिन्हित पूर्णांक apparmor_ip_postroute(व्योम *priv,
					  काष्ठा sk_buff *skb,
					  स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा aa_sk_ctx *ctx;
	काष्ठा sock *sk;

	अगर (!skb->secmark)
		वापस NF_ACCEPT;

	sk = skb_to_full_sk(skb);
	अगर (sk == शून्य)
		वापस NF_ACCEPT;

	ctx = SK_CTX(sk);
	अगर (!apparmor_secmark_check(ctx->label, OP_SENDMSG, AA_MAY_SEND,
				    skb->secmark, sk))
		वापस NF_ACCEPT;

	वापस NF_DROP_ERR(-ECONNREFUSED);

पूर्ण

अटल अचिन्हित पूर्णांक apparmor_ipv4_postroute(व्योम *priv,
					    काष्ठा sk_buff *skb,
					    स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस apparmor_ip_postroute(priv, skb, state);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अचिन्हित पूर्णांक apparmor_ipv6_postroute(व्योम *priv,
					    काष्ठा sk_buff *skb,
					    स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस apparmor_ip_postroute(priv, skb, state);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा nf_hook_ops apparmor_nf_ops[] = अणु
	अणु
		.hook =         apparmor_ipv4_postroute,
		.pf =           NFPROTO_IPV4,
		.hooknum =      NF_INET_POST_ROUTING,
		.priority =     NF_IP_PRI_SELINUX_FIRST,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IPV6)
	अणु
		.hook =         apparmor_ipv6_postroute,
		.pf =           NFPROTO_IPV6,
		.hooknum =      NF_INET_POST_ROUTING,
		.priority =     NF_IP6_PRI_SELINUX_FIRST,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __net_init apparmor_nf_रेजिस्टर(काष्ठा net *net)
अणु
	पूर्णांक ret;

	ret = nf_रेजिस्टर_net_hooks(net, apparmor_nf_ops,
				    ARRAY_SIZE(apparmor_nf_ops));
	वापस ret;
पूर्ण

अटल व्योम __net_निकास apparmor_nf_unरेजिस्टर(काष्ठा net *net)
अणु
	nf_unरेजिस्टर_net_hooks(net, apparmor_nf_ops,
				ARRAY_SIZE(apparmor_nf_ops));
पूर्ण

अटल काष्ठा pernet_operations apparmor_net_ops = अणु
	.init = apparmor_nf_रेजिस्टर,
	.निकास = apparmor_nf_unरेजिस्टर,
पूर्ण;

अटल पूर्णांक __init apparmor_nf_ip_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!apparmor_enabled)
		वापस 0;

	err = रेजिस्टर_pernet_subsys(&apparmor_net_ops);
	अगर (err)
		panic("Apparmor: register_pernet_subsys: error %d\n", err);

	वापस 0;
पूर्ण
__initcall(apparmor_nf_ip_init);
#पूर्ण_अगर

अटल पूर्णांक __init apparmor_init(व्योम)
अणु
	पूर्णांक error;

	aa_secids_init();

	error = aa_setup_dfa_engine();
	अगर (error) अणु
		AA_ERROR("Unable to setup dfa engine\n");
		जाओ alloc_out;
	पूर्ण

	error = aa_alloc_root_ns();
	अगर (error) अणु
		AA_ERROR("Unable to allocate default profile namespace\n");
		जाओ alloc_out;
	पूर्ण

	error = apparmor_init_sysctl();
	अगर (error) अणु
		AA_ERROR("Unable to register sysctls\n");
		जाओ alloc_out;

	पूर्ण

	error = alloc_buffers();
	अगर (error) अणु
		AA_ERROR("Unable to allocate work buffers\n");
		जाओ alloc_out;
	पूर्ण

	error = set_init_ctx();
	अगर (error) अणु
		AA_ERROR("Failed to set context on init task\n");
		aa_मुक्त_root_ns();
		जाओ buffers_out;
	पूर्ण
	security_add_hooks(apparmor_hooks, ARRAY_SIZE(apparmor_hooks),
				"apparmor");

	/* Report that AppArmor successfully initialized */
	apparmor_initialized = 1;
	अगर (aa_g_profile_mode == APPARMOR_COMPLAIN)
		aa_info_message("AppArmor initialized: complain mode enabled");
	अन्यथा अगर (aa_g_profile_mode == APPARMOR_KILL)
		aa_info_message("AppArmor initialized: kill mode enabled");
	अन्यथा
		aa_info_message("AppArmor initialized");

	वापस error;

buffers_out:
	destroy_buffers();
alloc_out:
	aa_destroy_aafs();
	aa_tearकरोwn_dfa_engine();

	apparmor_enabled = false;
	वापस error;
पूर्ण

DEFINE_LSM(apparmor) = अणु
	.name = "apparmor",
	.flags = LSM_FLAG_LEGACY_MAJOR | LSM_FLAG_EXCLUSIVE,
	.enabled = &apparmor_enabled,
	.blobs = &apparmor_blob_sizes,
	.init = apparmor_init,
पूर्ण;
