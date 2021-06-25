<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Linux Security Module Hook declarations.
 *
 * Copyright (C) 2001 WireX Communications, Inc <chris@wirex.com>
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2001 Networks Associates Technology, Inc <ssmalley@nai.com>
 * Copyright (C) 2001 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (C) 2001 Silicon Graphics, Inc. (Trust Technology Group)
 * Copyright (C) 2015 Intel Corporation.
 * Copyright (C) 2015 Casey Schaufler <हालy@schaufler-ca.com>
 * Copyright (C) 2016 Mellanox Techonologies
 * Copyright (C) 2020 Google LLC.
 */

/*
 * The macro LSM_HOOK is used to define the data काष्ठाures required by
 * the LSM framework using the pattern:
 *
 *	LSM_HOOK(<वापस_type>, <शेष_value>, <hook_name>, args...)
 *
 * काष्ठा security_hook_heads अणु
 *   #घोषणा LSM_HOOK(RET, DEFAULT, NAME, ...) काष्ठा hlist_head NAME;
 *   #समावेश <linux/lsm_hook_defs.h>
 *   #अघोषित LSM_HOOK
 * पूर्ण;
 */
LSM_HOOK(पूर्णांक, 0, binder_set_context_mgr, काष्ठा task_काष्ठा *mgr)
LSM_HOOK(पूर्णांक, 0, binder_transaction, काष्ठा task_काष्ठा *from,
	 काष्ठा task_काष्ठा *to)
LSM_HOOK(पूर्णांक, 0, binder_transfer_binder, काष्ठा task_काष्ठा *from,
	 काष्ठा task_काष्ठा *to)
LSM_HOOK(पूर्णांक, 0, binder_transfer_file, काष्ठा task_काष्ठा *from,
	 काष्ठा task_काष्ठा *to, काष्ठा file *file)
LSM_HOOK(पूर्णांक, 0, ptrace_access_check, काष्ठा task_काष्ठा *child,
	 अचिन्हित पूर्णांक mode)
LSM_HOOK(पूर्णांक, 0, ptrace_traceme, काष्ठा task_काष्ठा *parent)
LSM_HOOK(पूर्णांक, 0, capget, काष्ठा task_काष्ठा *target, kernel_cap_t *effective,
	 kernel_cap_t *inheritable, kernel_cap_t *permitted)
LSM_HOOK(पूर्णांक, 0, capset, काष्ठा cred *new, स्थिर काष्ठा cred *old,
	 स्थिर kernel_cap_t *effective, स्थिर kernel_cap_t *inheritable,
	 स्थिर kernel_cap_t *permitted)
LSM_HOOK(पूर्णांक, 0, capable, स्थिर काष्ठा cred *cred, काष्ठा user_namespace *ns,
	 पूर्णांक cap, अचिन्हित पूर्णांक opts)
LSM_HOOK(पूर्णांक, 0, quotactl, पूर्णांक cmds, पूर्णांक type, पूर्णांक id, काष्ठा super_block *sb)
LSM_HOOK(पूर्णांक, 0, quota_on, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, syslog, पूर्णांक type)
LSM_HOOK(पूर्णांक, 0, समय_रखो, स्थिर काष्ठा बारpec64 *ts,
	 स्थिर काष्ठा समयzone *tz)
LSM_HOOK(पूर्णांक, 0, vm_enough_memory, काष्ठा mm_काष्ठा *mm, दीर्घ pages)
LSM_HOOK(पूर्णांक, 0, bprm_creds_क्रम_exec, काष्ठा linux_binprm *bprm)
LSM_HOOK(पूर्णांक, 0, bprm_creds_from_file, काष्ठा linux_binprm *bprm, काष्ठा file *file)
LSM_HOOK(पूर्णांक, 0, bprm_check_security, काष्ठा linux_binprm *bprm)
LSM_HOOK(व्योम, LSM_RET_VOID, bprm_committing_creds, काष्ठा linux_binprm *bprm)
LSM_HOOK(व्योम, LSM_RET_VOID, bprm_committed_creds, काष्ठा linux_binprm *bprm)
LSM_HOOK(पूर्णांक, 0, fs_context_dup, काष्ठा fs_context *fc,
	 काष्ठा fs_context *src_sc)
LSM_HOOK(पूर्णांक, -ENOPARAM, fs_context_parse_param, काष्ठा fs_context *fc,
	 काष्ठा fs_parameter *param)
LSM_HOOK(पूर्णांक, 0, sb_alloc_security, काष्ठा super_block *sb)
LSM_HOOK(व्योम, LSM_RET_VOID, sb_delete, काष्ठा super_block *sb)
LSM_HOOK(व्योम, LSM_RET_VOID, sb_मुक्त_security, काष्ठा super_block *sb)
LSM_HOOK(व्योम, LSM_RET_VOID, sb_मुक्त_mnt_opts, व्योम *mnt_opts)
LSM_HOOK(पूर्णांक, 0, sb_eat_lsm_opts, अक्षर *orig, व्योम **mnt_opts)
LSM_HOOK(पूर्णांक, 0, sb_mnt_opts_compat, काष्ठा super_block *sb, व्योम *mnt_opts)
LSM_HOOK(पूर्णांक, 0, sb_remount, काष्ठा super_block *sb, व्योम *mnt_opts)
LSM_HOOK(पूर्णांक, 0, sb_kern_mount, काष्ठा super_block *sb)
LSM_HOOK(पूर्णांक, 0, sb_show_options, काष्ठा seq_file *m, काष्ठा super_block *sb)
LSM_HOOK(पूर्णांक, 0, sb_statfs, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, sb_mount, स्थिर अक्षर *dev_name, स्थिर काष्ठा path *path,
	 स्थिर अक्षर *type, अचिन्हित दीर्घ flags, व्योम *data)
LSM_HOOK(पूर्णांक, 0, sb_umount, काष्ठा vfsmount *mnt, पूर्णांक flags)
LSM_HOOK(पूर्णांक, 0, sb_pivotroot, स्थिर काष्ठा path *old_path,
	 स्थिर काष्ठा path *new_path)
LSM_HOOK(पूर्णांक, 0, sb_set_mnt_opts, काष्ठा super_block *sb, व्योम *mnt_opts,
	 अचिन्हित दीर्घ kern_flags, अचिन्हित दीर्घ *set_kern_flags)
LSM_HOOK(पूर्णांक, 0, sb_clone_mnt_opts, स्थिर काष्ठा super_block *oldsb,
	 काष्ठा super_block *newsb, अचिन्हित दीर्घ kern_flags,
	 अचिन्हित दीर्घ *set_kern_flags)
LSM_HOOK(पूर्णांक, 0, sb_add_mnt_opt, स्थिर अक्षर *option, स्थिर अक्षर *val,
	 पूर्णांक len, व्योम **mnt_opts)
LSM_HOOK(पूर्णांक, 0, move_mount, स्थिर काष्ठा path *from_path,
	 स्थिर काष्ठा path *to_path)
LSM_HOOK(पूर्णांक, 0, dentry_init_security, काष्ठा dentry *dentry,
	 पूर्णांक mode, स्थिर काष्ठा qstr *name, व्योम **ctx, u32 *ctxlen)
LSM_HOOK(पूर्णांक, 0, dentry_create_files_as, काष्ठा dentry *dentry, पूर्णांक mode,
	 काष्ठा qstr *name, स्थिर काष्ठा cred *old, काष्ठा cred *new)

#अगर_घोषित CONFIG_SECURITY_PATH
LSM_HOOK(पूर्णांक, 0, path_unlink, स्थिर काष्ठा path *dir, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, path_सूची_गढ़ो, स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
	 umode_t mode)
LSM_HOOK(पूर्णांक, 0, path_सूची_हटाओ, स्थिर काष्ठा path *dir, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, path_mknod, स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
	 umode_t mode, अचिन्हित पूर्णांक dev)
LSM_HOOK(पूर्णांक, 0, path_truncate, स्थिर काष्ठा path *path)
LSM_HOOK(पूर्णांक, 0, path_symlink, स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
	 स्थिर अक्षर *old_name)
LSM_HOOK(पूर्णांक, 0, path_link, काष्ठा dentry *old_dentry,
	 स्थिर काष्ठा path *new_dir, काष्ठा dentry *new_dentry)
LSM_HOOK(पूर्णांक, 0, path_नाम, स्थिर काष्ठा path *old_dir,
	 काष्ठा dentry *old_dentry, स्थिर काष्ठा path *new_dir,
	 काष्ठा dentry *new_dentry)
LSM_HOOK(पूर्णांक, 0, path_chmod, स्थिर काष्ठा path *path, umode_t mode)
LSM_HOOK(पूर्णांक, 0, path_chown, स्थिर काष्ठा path *path, kuid_t uid, kgid_t gid)
LSM_HOOK(पूर्णांक, 0, path_chroot, स्थिर काष्ठा path *path)
#पूर्ण_अगर /* CONFIG_SECURITY_PATH */

/* Needed क्रम inode based security check */
LSM_HOOK(पूर्णांक, 0, path_notअगरy, स्थिर काष्ठा path *path, u64 mask,
	 अचिन्हित पूर्णांक obj_type)
LSM_HOOK(पूर्णांक, 0, inode_alloc_security, काष्ठा inode *inode)
LSM_HOOK(व्योम, LSM_RET_VOID, inode_मुक्त_security, काष्ठा inode *inode)
LSM_HOOK(पूर्णांक, 0, inode_init_security, काष्ठा inode *inode,
	 काष्ठा inode *dir, स्थिर काष्ठा qstr *qstr, स्थिर अक्षर **name,
	 व्योम **value, माप_प्रकार *len)
LSM_HOOK(पूर्णांक, 0, inode_init_security_anon, काष्ठा inode *inode,
	 स्थिर काष्ठा qstr *name, स्थिर काष्ठा inode *context_inode)
LSM_HOOK(पूर्णांक, 0, inode_create, काष्ठा inode *dir, काष्ठा dentry *dentry,
	 umode_t mode)
LSM_HOOK(पूर्णांक, 0, inode_link, काष्ठा dentry *old_dentry, काष्ठा inode *dir,
	 काष्ठा dentry *new_dentry)
LSM_HOOK(पूर्णांक, 0, inode_unlink, काष्ठा inode *dir, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, inode_symlink, काष्ठा inode *dir, काष्ठा dentry *dentry,
	 स्थिर अक्षर *old_name)
LSM_HOOK(पूर्णांक, 0, inode_सूची_गढ़ो, काष्ठा inode *dir, काष्ठा dentry *dentry,
	 umode_t mode)
LSM_HOOK(पूर्णांक, 0, inode_सूची_हटाओ, काष्ठा inode *dir, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, inode_mknod, काष्ठा inode *dir, काष्ठा dentry *dentry,
	 umode_t mode, dev_t dev)
LSM_HOOK(पूर्णांक, 0, inode_नाम, काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
	 काष्ठा inode *new_dir, काष्ठा dentry *new_dentry)
LSM_HOOK(पूर्णांक, 0, inode_पढ़ोlink, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, inode_follow_link, काष्ठा dentry *dentry, काष्ठा inode *inode,
	 bool rcu)
LSM_HOOK(पूर्णांक, 0, inode_permission, काष्ठा inode *inode, पूर्णांक mask)
LSM_HOOK(पूर्णांक, 0, inode_setattr, काष्ठा dentry *dentry, काष्ठा iattr *attr)
LSM_HOOK(पूर्णांक, 0, inode_getattr, स्थिर काष्ठा path *path)
LSM_HOOK(पूर्णांक, 0, inode_setxattr, काष्ठा user_namespace *mnt_userns,
	 काष्ठा dentry *dentry, स्थिर अक्षर *name, स्थिर व्योम *value,
	 माप_प्रकार size, पूर्णांक flags)
LSM_HOOK(व्योम, LSM_RET_VOID, inode_post_setxattr, काष्ठा dentry *dentry,
	 स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
LSM_HOOK(पूर्णांक, 0, inode_getxattr, काष्ठा dentry *dentry, स्थिर अक्षर *name)
LSM_HOOK(पूर्णांक, 0, inode_listxattr, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, inode_हटाओxattr, काष्ठा user_namespace *mnt_userns,
	 काष्ठा dentry *dentry, स्थिर अक्षर *name)
LSM_HOOK(पूर्णांक, 0, inode_need_समाप्तpriv, काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, 0, inode_समाप्तpriv, काष्ठा user_namespace *mnt_userns,
	 काष्ठा dentry *dentry)
LSM_HOOK(पूर्णांक, -EOPNOTSUPP, inode_माला_लोecurity, काष्ठा user_namespace *mnt_userns,
	 काष्ठा inode *inode, स्थिर अक्षर *name, व्योम **buffer, bool alloc)
LSM_HOOK(पूर्णांक, -EOPNOTSUPP, inode_setsecurity, काष्ठा inode *inode,
	 स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
LSM_HOOK(पूर्णांक, 0, inode_listsecurity, काष्ठा inode *inode, अक्षर *buffer,
	 माप_प्रकार buffer_size)
LSM_HOOK(व्योम, LSM_RET_VOID, inode_माला_लोecid, काष्ठा inode *inode, u32 *secid)
LSM_HOOK(पूर्णांक, 0, inode_copy_up, काष्ठा dentry *src, काष्ठा cred **new)
LSM_HOOK(पूर्णांक, -EOPNOTSUPP, inode_copy_up_xattr, स्थिर अक्षर *name)
LSM_HOOK(पूर्णांक, 0, kernfs_init_security, काष्ठा kernfs_node *kn_dir,
	 काष्ठा kernfs_node *kn)
LSM_HOOK(पूर्णांक, 0, file_permission, काष्ठा file *file, पूर्णांक mask)
LSM_HOOK(पूर्णांक, 0, file_alloc_security, काष्ठा file *file)
LSM_HOOK(व्योम, LSM_RET_VOID, file_मुक्त_security, काष्ठा file *file)
LSM_HOOK(पूर्णांक, 0, file_ioctl, काष्ठा file *file, अचिन्हित पूर्णांक cmd,
	 अचिन्हित दीर्घ arg)
LSM_HOOK(पूर्णांक, 0, mmap_addr, अचिन्हित दीर्घ addr)
LSM_HOOK(पूर्णांक, 0, mmap_file, काष्ठा file *file, अचिन्हित दीर्घ reqprot,
	 अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags)
LSM_HOOK(पूर्णांक, 0, file_mprotect, काष्ठा vm_area_काष्ठा *vma,
	 अचिन्हित दीर्घ reqprot, अचिन्हित दीर्घ prot)
LSM_HOOK(पूर्णांक, 0, file_lock, काष्ठा file *file, अचिन्हित पूर्णांक cmd)
LSM_HOOK(पूर्णांक, 0, file_fcntl, काष्ठा file *file, अचिन्हित पूर्णांक cmd,
	 अचिन्हित दीर्घ arg)
LSM_HOOK(व्योम, LSM_RET_VOID, file_set_fowner, काष्ठा file *file)
LSM_HOOK(पूर्णांक, 0, file_send_sigiotask, काष्ठा task_काष्ठा *tsk,
	 काष्ठा fown_काष्ठा *fown, पूर्णांक sig)
LSM_HOOK(पूर्णांक, 0, file_receive, काष्ठा file *file)
LSM_HOOK(पूर्णांक, 0, file_खोलो, काष्ठा file *file)
LSM_HOOK(पूर्णांक, 0, task_alloc, काष्ठा task_काष्ठा *task,
	 अचिन्हित दीर्घ clone_flags)
LSM_HOOK(व्योम, LSM_RET_VOID, task_मुक्त, काष्ठा task_काष्ठा *task)
LSM_HOOK(पूर्णांक, 0, cred_alloc_blank, काष्ठा cred *cred, gfp_t gfp)
LSM_HOOK(व्योम, LSM_RET_VOID, cred_मुक्त, काष्ठा cred *cred)
LSM_HOOK(पूर्णांक, 0, cred_prepare, काष्ठा cred *new, स्थिर काष्ठा cred *old,
	 gfp_t gfp)
LSM_HOOK(व्योम, LSM_RET_VOID, cred_transfer, काष्ठा cred *new,
	 स्थिर काष्ठा cred *old)
LSM_HOOK(व्योम, LSM_RET_VOID, cred_माला_लोecid, स्थिर काष्ठा cred *c, u32 *secid)
LSM_HOOK(पूर्णांक, 0, kernel_act_as, काष्ठा cred *new, u32 secid)
LSM_HOOK(पूर्णांक, 0, kernel_create_files_as, काष्ठा cred *new, काष्ठा inode *inode)
LSM_HOOK(पूर्णांक, 0, kernel_module_request, अक्षर *kmod_name)
LSM_HOOK(पूर्णांक, 0, kernel_load_data, क्रमागत kernel_load_data_id id, bool contents)
LSM_HOOK(पूर्णांक, 0, kernel_post_load_data, अक्षर *buf, loff_t size,
	 क्रमागत kernel_load_data_id id, अक्षर *description)
LSM_HOOK(पूर्णांक, 0, kernel_पढ़ो_file, काष्ठा file *file,
	 क्रमागत kernel_पढ़ो_file_id id, bool contents)
LSM_HOOK(पूर्णांक, 0, kernel_post_पढ़ो_file, काष्ठा file *file, अक्षर *buf,
	 loff_t size, क्रमागत kernel_पढ़ो_file_id id)
LSM_HOOK(पूर्णांक, 0, task_fix_setuid, काष्ठा cred *new, स्थिर काष्ठा cred *old,
	 पूर्णांक flags)
LSM_HOOK(पूर्णांक, 0, task_fix_setgid, काष्ठा cred *new, स्थिर काष्ठा cred * old,
	 पूर्णांक flags)
LSM_HOOK(पूर्णांक, 0, task_setpgid, काष्ठा task_काष्ठा *p, pid_t pgid)
LSM_HOOK(पूर्णांक, 0, task_getpgid, काष्ठा task_काष्ठा *p)
LSM_HOOK(पूर्णांक, 0, task_माला_लोid, काष्ठा task_काष्ठा *p)
LSM_HOOK(व्योम, LSM_RET_VOID, task_माला_लोecid_subj,
	 काष्ठा task_काष्ठा *p, u32 *secid)
LSM_HOOK(व्योम, LSM_RET_VOID, task_माला_लोecid_obj,
	 काष्ठा task_काष्ठा *p, u32 *secid)
LSM_HOOK(पूर्णांक, 0, task_setnice, काष्ठा task_काष्ठा *p, पूर्णांक nice)
LSM_HOOK(पूर्णांक, 0, task_setioprio, काष्ठा task_काष्ठा *p, पूर्णांक ioprio)
LSM_HOOK(पूर्णांक, 0, task_getioprio, काष्ठा task_काष्ठा *p)
LSM_HOOK(पूर्णांक, 0, task_prlimit, स्थिर काष्ठा cred *cred,
	 स्थिर काष्ठा cred *tcred, अचिन्हित पूर्णांक flags)
LSM_HOOK(पूर्णांक, 0, task_setrlimit, काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक resource,
	 काष्ठा rlimit *new_rlim)
LSM_HOOK(पूर्णांक, 0, task_setscheduler, काष्ठा task_काष्ठा *p)
LSM_HOOK(पूर्णांक, 0, task_माला_लोcheduler, काष्ठा task_काष्ठा *p)
LSM_HOOK(पूर्णांक, 0, task_movememory, काष्ठा task_काष्ठा *p)
LSM_HOOK(पूर्णांक, 0, task_समाप्त, काष्ठा task_काष्ठा *p, काष्ठा kernel_siginfo *info,
	 पूर्णांक sig, स्थिर काष्ठा cred *cred)
LSM_HOOK(पूर्णांक, -ENOSYS, task_prctl, पूर्णांक option, अचिन्हित दीर्घ arg2,
	 अचिन्हित दीर्घ arg3, अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5)
LSM_HOOK(व्योम, LSM_RET_VOID, task_to_inode, काष्ठा task_काष्ठा *p,
	 काष्ठा inode *inode)
LSM_HOOK(पूर्णांक, 0, ipc_permission, काष्ठा kern_ipc_perm *ipcp, लघु flag)
LSM_HOOK(व्योम, LSM_RET_VOID, ipc_माला_लोecid, काष्ठा kern_ipc_perm *ipcp,
	 u32 *secid)
LSM_HOOK(पूर्णांक, 0, msg_msg_alloc_security, काष्ठा msg_msg *msg)
LSM_HOOK(व्योम, LSM_RET_VOID, msg_msg_मुक्त_security, काष्ठा msg_msg *msg)
LSM_HOOK(पूर्णांक, 0, msg_queue_alloc_security, काष्ठा kern_ipc_perm *perm)
LSM_HOOK(व्योम, LSM_RET_VOID, msg_queue_मुक्त_security,
	 काष्ठा kern_ipc_perm *perm)
LSM_HOOK(पूर्णांक, 0, msg_queue_associate, काष्ठा kern_ipc_perm *perm, पूर्णांक msqflg)
LSM_HOOK(पूर्णांक, 0, msg_queue_msgctl, काष्ठा kern_ipc_perm *perm, पूर्णांक cmd)
LSM_HOOK(पूर्णांक, 0, msg_queue_msgsnd, काष्ठा kern_ipc_perm *perm,
	 काष्ठा msg_msg *msg, पूर्णांक msqflg)
LSM_HOOK(पूर्णांक, 0, msg_queue_msgrcv, काष्ठा kern_ipc_perm *perm,
	 काष्ठा msg_msg *msg, काष्ठा task_काष्ठा *target, दीर्घ type, पूर्णांक mode)
LSM_HOOK(पूर्णांक, 0, shm_alloc_security, काष्ठा kern_ipc_perm *perm)
LSM_HOOK(व्योम, LSM_RET_VOID, shm_मुक्त_security, काष्ठा kern_ipc_perm *perm)
LSM_HOOK(पूर्णांक, 0, shm_associate, काष्ठा kern_ipc_perm *perm, पूर्णांक shmflg)
LSM_HOOK(पूर्णांक, 0, shm_shmctl, काष्ठा kern_ipc_perm *perm, पूर्णांक cmd)
LSM_HOOK(पूर्णांक, 0, shm_shmat, काष्ठा kern_ipc_perm *perm, अक्षर __user *shmaddr,
	 पूर्णांक shmflg)
LSM_HOOK(पूर्णांक, 0, sem_alloc_security, काष्ठा kern_ipc_perm *perm)
LSM_HOOK(व्योम, LSM_RET_VOID, sem_मुक्त_security, काष्ठा kern_ipc_perm *perm)
LSM_HOOK(पूर्णांक, 0, sem_associate, काष्ठा kern_ipc_perm *perm, पूर्णांक semflg)
LSM_HOOK(पूर्णांक, 0, sem_semctl, काष्ठा kern_ipc_perm *perm, पूर्णांक cmd)
LSM_HOOK(पूर्णांक, 0, sem_semop, काष्ठा kern_ipc_perm *perm, काष्ठा sembuf *sops,
	 अचिन्हित nsops, पूर्णांक alter)
LSM_HOOK(पूर्णांक, 0, netlink_send, काष्ठा sock *sk, काष्ठा sk_buff *skb)
LSM_HOOK(व्योम, LSM_RET_VOID, d_instantiate, काष्ठा dentry *dentry,
	 काष्ठा inode *inode)
LSM_HOOK(पूर्णांक, -EINVAL, getprocattr, काष्ठा task_काष्ठा *p, अक्षर *name,
	 अक्षर **value)
LSM_HOOK(पूर्णांक, -EINVAL, setprocattr, स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
LSM_HOOK(पूर्णांक, 0, ismaclabel, स्थिर अक्षर *name)
LSM_HOOK(पूर्णांक, -EOPNOTSUPP, secid_to_secctx, u32 secid, अक्षर **secdata,
	 u32 *seclen)
LSM_HOOK(पूर्णांक, 0, secctx_to_secid, स्थिर अक्षर *secdata, u32 seclen, u32 *secid)
LSM_HOOK(व्योम, LSM_RET_VOID, release_secctx, अक्षर *secdata, u32 seclen)
LSM_HOOK(व्योम, LSM_RET_VOID, inode_invalidate_secctx, काष्ठा inode *inode)
LSM_HOOK(पूर्णांक, 0, inode_notअगरysecctx, काष्ठा inode *inode, व्योम *ctx, u32 ctxlen)
LSM_HOOK(पूर्णांक, 0, inode_setsecctx, काष्ठा dentry *dentry, व्योम *ctx, u32 ctxlen)
LSM_HOOK(पूर्णांक, 0, inode_माला_लोecctx, काष्ठा inode *inode, व्योम **ctx,
	 u32 *ctxlen)

#अगर defined(CONFIG_SECURITY) && defined(CONFIG_WATCH_QUEUE)
LSM_HOOK(पूर्णांक, 0, post_notअगरication, स्थिर काष्ठा cred *w_cred,
	 स्थिर काष्ठा cred *cred, काष्ठा watch_notअगरication *n)
#पूर्ण_अगर /* CONFIG_SECURITY && CONFIG_WATCH_QUEUE */

#अगर defined(CONFIG_SECURITY) && defined(CONFIG_KEY_NOTIFICATIONS)
LSM_HOOK(पूर्णांक, 0, watch_key, काष्ठा key *key)
#पूर्ण_अगर /* CONFIG_SECURITY && CONFIG_KEY_NOTIFICATIONS */

#अगर_घोषित CONFIG_SECURITY_NETWORK
LSM_HOOK(पूर्णांक, 0, unix_stream_connect, काष्ठा sock *sock, काष्ठा sock *other,
	 काष्ठा sock *newsk)
LSM_HOOK(पूर्णांक, 0, unix_may_send, काष्ठा socket *sock, काष्ठा socket *other)
LSM_HOOK(पूर्णांक, 0, socket_create, पूर्णांक family, पूर्णांक type, पूर्णांक protocol, पूर्णांक kern)
LSM_HOOK(पूर्णांक, 0, socket_post_create, काष्ठा socket *sock, पूर्णांक family, पूर्णांक type,
	 पूर्णांक protocol, पूर्णांक kern)
LSM_HOOK(पूर्णांक, 0, socket_socketpair, काष्ठा socket *socka, काष्ठा socket *sockb)
LSM_HOOK(पूर्णांक, 0, socket_bind, काष्ठा socket *sock, काष्ठा sockaddr *address,
	 पूर्णांक addrlen)
LSM_HOOK(पूर्णांक, 0, socket_connect, काष्ठा socket *sock, काष्ठा sockaddr *address,
	 पूर्णांक addrlen)
LSM_HOOK(पूर्णांक, 0, socket_listen, काष्ठा socket *sock, पूर्णांक backlog)
LSM_HOOK(पूर्णांक, 0, socket_accept, काष्ठा socket *sock, काष्ठा socket *newsock)
LSM_HOOK(पूर्णांक, 0, socket_sendmsg, काष्ठा socket *sock, काष्ठा msghdr *msg,
	 पूर्णांक size)
LSM_HOOK(पूर्णांक, 0, socket_recvmsg, काष्ठा socket *sock, काष्ठा msghdr *msg,
	 पूर्णांक size, पूर्णांक flags)
LSM_HOOK(पूर्णांक, 0, socket_माला_लोockname, काष्ठा socket *sock)
LSM_HOOK(पूर्णांक, 0, socket_getpeername, काष्ठा socket *sock)
LSM_HOOK(पूर्णांक, 0, socket_माला_लोockopt, काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname)
LSM_HOOK(पूर्णांक, 0, socket_setsockopt, काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname)
LSM_HOOK(पूर्णांक, 0, socket_shutकरोwn, काष्ठा socket *sock, पूर्णांक how)
LSM_HOOK(पूर्णांक, 0, socket_sock_rcv_skb, काष्ठा sock *sk, काष्ठा sk_buff *skb)
LSM_HOOK(पूर्णांक, 0, socket_getpeersec_stream, काष्ठा socket *sock,
	 अक्षर __user *optval, पूर्णांक __user *optlen, अचिन्हित len)
LSM_HOOK(पूर्णांक, 0, socket_getpeersec_dgram, काष्ठा socket *sock,
	 काष्ठा sk_buff *skb, u32 *secid)
LSM_HOOK(पूर्णांक, 0, sk_alloc_security, काष्ठा sock *sk, पूर्णांक family, gfp_t priority)
LSM_HOOK(व्योम, LSM_RET_VOID, sk_मुक्त_security, काष्ठा sock *sk)
LSM_HOOK(व्योम, LSM_RET_VOID, sk_clone_security, स्थिर काष्ठा sock *sk,
	 काष्ठा sock *newsk)
LSM_HOOK(व्योम, LSM_RET_VOID, sk_माला_लोecid, काष्ठा sock *sk, u32 *secid)
LSM_HOOK(व्योम, LSM_RET_VOID, sock_graft, काष्ठा sock *sk, काष्ठा socket *parent)
LSM_HOOK(पूर्णांक, 0, inet_conn_request, स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
	 काष्ठा request_sock *req)
LSM_HOOK(व्योम, LSM_RET_VOID, inet_csk_clone, काष्ठा sock *newsk,
	 स्थिर काष्ठा request_sock *req)
LSM_HOOK(व्योम, LSM_RET_VOID, inet_conn_established, काष्ठा sock *sk,
	 काष्ठा sk_buff *skb)
LSM_HOOK(पूर्णांक, 0, secmark_relabel_packet, u32 secid)
LSM_HOOK(व्योम, LSM_RET_VOID, secmark_refcount_inc, व्योम)
LSM_HOOK(व्योम, LSM_RET_VOID, secmark_refcount_dec, व्योम)
LSM_HOOK(व्योम, LSM_RET_VOID, req_classअगरy_flow, स्थिर काष्ठा request_sock *req,
	 काष्ठा flowi_common *flic)
LSM_HOOK(पूर्णांक, 0, tun_dev_alloc_security, व्योम **security)
LSM_HOOK(व्योम, LSM_RET_VOID, tun_dev_मुक्त_security, व्योम *security)
LSM_HOOK(पूर्णांक, 0, tun_dev_create, व्योम)
LSM_HOOK(पूर्णांक, 0, tun_dev_attach_queue, व्योम *security)
LSM_HOOK(पूर्णांक, 0, tun_dev_attach, काष्ठा sock *sk, व्योम *security)
LSM_HOOK(पूर्णांक, 0, tun_dev_खोलो, व्योम *security)
LSM_HOOK(पूर्णांक, 0, sctp_assoc_request, काष्ठा sctp_endpoपूर्णांक *ep,
	 काष्ठा sk_buff *skb)
LSM_HOOK(पूर्णांक, 0, sctp_bind_connect, काष्ठा sock *sk, पूर्णांक optname,
	 काष्ठा sockaddr *address, पूर्णांक addrlen)
LSM_HOOK(व्योम, LSM_RET_VOID, sctp_sk_clone, काष्ठा sctp_endpoपूर्णांक *ep,
	 काष्ठा sock *sk, काष्ठा sock *newsk)
#पूर्ण_अगर /* CONFIG_SECURITY_NETWORK */

#अगर_घोषित CONFIG_SECURITY_INFINIBAND
LSM_HOOK(पूर्णांक, 0, ib_pkey_access, व्योम *sec, u64 subnet_prefix, u16 pkey)
LSM_HOOK(पूर्णांक, 0, ib_endport_manage_subnet, व्योम *sec, स्थिर अक्षर *dev_name,
	 u8 port_num)
LSM_HOOK(पूर्णांक, 0, ib_alloc_security, व्योम **sec)
LSM_HOOK(व्योम, LSM_RET_VOID, ib_मुक्त_security, व्योम *sec)
#पूर्ण_अगर /* CONFIG_SECURITY_INFINIBAND */

#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM
LSM_HOOK(पूर्णांक, 0, xfrm_policy_alloc_security, काष्ठा xfrm_sec_ctx **ctxp,
	 काष्ठा xfrm_user_sec_ctx *sec_ctx, gfp_t gfp)
LSM_HOOK(पूर्णांक, 0, xfrm_policy_clone_security, काष्ठा xfrm_sec_ctx *old_ctx,
	 काष्ठा xfrm_sec_ctx **new_ctx)
LSM_HOOK(व्योम, LSM_RET_VOID, xfrm_policy_मुक्त_security,
	 काष्ठा xfrm_sec_ctx *ctx)
LSM_HOOK(पूर्णांक, 0, xfrm_policy_delete_security, काष्ठा xfrm_sec_ctx *ctx)
LSM_HOOK(पूर्णांक, 0, xfrm_state_alloc, काष्ठा xfrm_state *x,
	 काष्ठा xfrm_user_sec_ctx *sec_ctx)
LSM_HOOK(पूर्णांक, 0, xfrm_state_alloc_acquire, काष्ठा xfrm_state *x,
	 काष्ठा xfrm_sec_ctx *polsec, u32 secid)
LSM_HOOK(व्योम, LSM_RET_VOID, xfrm_state_मुक्त_security, काष्ठा xfrm_state *x)
LSM_HOOK(पूर्णांक, 0, xfrm_state_delete_security, काष्ठा xfrm_state *x)
LSM_HOOK(पूर्णांक, 0, xfrm_policy_lookup, काष्ठा xfrm_sec_ctx *ctx, u32 fl_secid,
	 u8 dir)
LSM_HOOK(पूर्णांक, 1, xfrm_state_pol_flow_match, काष्ठा xfrm_state *x,
	 काष्ठा xfrm_policy *xp, स्थिर काष्ठा flowi_common *flic)
LSM_HOOK(पूर्णांक, 0, xfrm_decode_session, काष्ठा sk_buff *skb, u32 *secid,
	 पूर्णांक ckall)
#पूर्ण_अगर /* CONFIG_SECURITY_NETWORK_XFRM */

/* key management security hooks */
#अगर_घोषित CONFIG_KEYS
LSM_HOOK(पूर्णांक, 0, key_alloc, काष्ठा key *key, स्थिर काष्ठा cred *cred,
	 अचिन्हित दीर्घ flags)
LSM_HOOK(व्योम, LSM_RET_VOID, key_मुक्त, काष्ठा key *key)
LSM_HOOK(पूर्णांक, 0, key_permission, key_ref_t key_ref, स्थिर काष्ठा cred *cred,
	 क्रमागत key_need_perm need_perm)
LSM_HOOK(पूर्णांक, 0, key_माला_लोecurity, काष्ठा key *key, अक्षर **_buffer)
#पूर्ण_अगर /* CONFIG_KEYS */

#अगर_घोषित CONFIG_AUDIT
LSM_HOOK(पूर्णांक, 0, audit_rule_init, u32 field, u32 op, अक्षर *rulestr,
	 व्योम **lsmrule)
LSM_HOOK(पूर्णांक, 0, audit_rule_known, काष्ठा audit_krule *krule)
LSM_HOOK(पूर्णांक, 0, audit_rule_match, u32 secid, u32 field, u32 op, व्योम *lsmrule)
LSM_HOOK(व्योम, LSM_RET_VOID, audit_rule_मुक्त, व्योम *lsmrule)
#पूर्ण_अगर /* CONFIG_AUDIT */

#अगर_घोषित CONFIG_BPF_SYSCALL
LSM_HOOK(पूर्णांक, 0, bpf, पूर्णांक cmd, जोड़ bpf_attr *attr, अचिन्हित पूर्णांक size)
LSM_HOOK(पूर्णांक, 0, bpf_map, काष्ठा bpf_map *map, भ_शेषe_t भ_शेषe)
LSM_HOOK(पूर्णांक, 0, bpf_prog, काष्ठा bpf_prog *prog)
LSM_HOOK(पूर्णांक, 0, bpf_map_alloc_security, काष्ठा bpf_map *map)
LSM_HOOK(व्योम, LSM_RET_VOID, bpf_map_मुक्त_security, काष्ठा bpf_map *map)
LSM_HOOK(पूर्णांक, 0, bpf_prog_alloc_security, काष्ठा bpf_prog_aux *aux)
LSM_HOOK(व्योम, LSM_RET_VOID, bpf_prog_मुक्त_security, काष्ठा bpf_prog_aux *aux)
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */

LSM_HOOK(पूर्णांक, 0, locked_करोwn, क्रमागत lockकरोwn_reason what)

#अगर_घोषित CONFIG_PERF_EVENTS
LSM_HOOK(पूर्णांक, 0, perf_event_खोलो, काष्ठा perf_event_attr *attr, पूर्णांक type)
LSM_HOOK(पूर्णांक, 0, perf_event_alloc, काष्ठा perf_event *event)
LSM_HOOK(व्योम, LSM_RET_VOID, perf_event_मुक्त, काष्ठा perf_event *event)
LSM_HOOK(पूर्णांक, 0, perf_event_पढ़ो, काष्ठा perf_event *event)
LSM_HOOK(पूर्णांक, 0, perf_event_ग_लिखो, काष्ठा perf_event *event)
#पूर्ण_अगर /* CONFIG_PERF_EVENTS */
