<शैली गुरु>
/*
 * Linux Security plug
 *
 * Copyright (C) 2001 WireX Communications, Inc <chris@wirex.com>
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2001 Networks Associates Technology, Inc <ssmalley@nai.com>
 * Copyright (C) 2001 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (C) 2001 Silicon Graphics, Inc. (Trust Technology Group)
 * Copyright (C) 2016 Mellanox Techonologies
 *
 *	This program is मुक्त software; you can redistribute it and/or modअगरy
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	Due to this file being licensed under the GPL there is controversy over
 *	whether this permits you to ग_लिखो a module that #समावेशs this file
 *	without placing your module under the GPL.  Please consult a lawyer क्रम
 *	advice beक्रमe करोing this.
 *
 */

#अगर_अघोषित __LINUX_SECURITY_H
#घोषणा __LINUX_SECURITY_H

#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/key.h>
#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>

काष्ठा linux_binprm;
काष्ठा cred;
काष्ठा rlimit;
काष्ठा kernel_siginfo;
काष्ठा sembuf;
काष्ठा kern_ipc_perm;
काष्ठा audit_context;
काष्ठा super_block;
काष्ठा inode;
काष्ठा dentry;
काष्ठा file;
काष्ठा vfsmount;
काष्ठा path;
काष्ठा qstr;
काष्ठा iattr;
काष्ठा fown_काष्ठा;
काष्ठा file_operations;
काष्ठा msg_msg;
काष्ठा xattr;
काष्ठा kernfs_node;
काष्ठा xfrm_sec_ctx;
काष्ठा mm_काष्ठा;
काष्ठा fs_context;
काष्ठा fs_parameter;
क्रमागत fs_value_type;
काष्ठा watch;
काष्ठा watch_notअगरication;

/* Default (no) options क्रम the capable function */
#घोषणा CAP_OPT_NONE 0x0
/* If capable should audit the security request */
#घोषणा CAP_OPT_NOAUDIT BIT(1)
/* If capable is being called by a setid function */
#घोषणा CAP_OPT_INSETID BIT(2)

/* LSM Agnostic defines क्रम fs_context::lsm_flags */
#घोषणा SECURITY_LSM_NATIVE_LABELS	1

काष्ठा ctl_table;
काष्ठा audit_krule;
काष्ठा user_namespace;
काष्ठा समयzone;

क्रमागत lsm_event अणु
	LSM_POLICY_CHANGE,
पूर्ण;

/*
 * These are reasons that can be passed to the security_locked_करोwn()
 * LSM hook. Lockकरोwn reasons that protect kernel पूर्णांकegrity (ie, the
 * ability क्रम userland to modअगरy kernel code) are placed beक्रमe
 * LOCKDOWN_INTEGRITY_MAX.  Lockकरोwn reasons that protect kernel
 * confidentiality (ie, the ability क्रम userland to extract
 * inक्रमmation from the running kernel that would otherwise be
 * restricted) are placed beक्रमe LOCKDOWN_CONFIDENTIALITY_MAX.
 *
 * LSM authors should note that the semantics of any given lockकरोwn
 * reason are not guaranteed to be stable - the same reason may block
 * one set of features in one kernel release, and a slightly dअगरferent
 * set of features in a later kernel release. LSMs that seek to expose
 * lockकरोwn policy at any level of granularity other than "none",
 * "integrity" or "confidentiality" are responsible क्रम either
 * ensuring that they expose a consistent level of functionality to
 * userland, or ensuring that userland is aware that this is
 * potentially a moving target. It is easy to misuse this inक्रमmation
 * in a way that could अवरोध userspace. Please be careful not to करो
 * so.
 *
 * If you add to this, remember to extend lockकरोwn_reasons in
 * security/lockकरोwn/lockकरोwn.c.
 */
क्रमागत lockकरोwn_reason अणु
	LOCKDOWN_NONE,
	LOCKDOWN_MODULE_SIGNATURE,
	LOCKDOWN_DEV_MEM,
	LOCKDOWN_EFI_TEST,
	LOCKDOWN_KEXEC,
	LOCKDOWN_HIBERNATION,
	LOCKDOWN_PCI_ACCESS,
	LOCKDOWN_IOPORT,
	LOCKDOWN_MSR,
	LOCKDOWN_ACPI_TABLES,
	LOCKDOWN_PCMCIA_CIS,
	LOCKDOWN_TIOCSSERIAL,
	LOCKDOWN_MODULE_PARAMETERS,
	LOCKDOWN_MMIOTRACE,
	LOCKDOWN_DEBUGFS,
	LOCKDOWN_XMON_WR,
	LOCKDOWN_INTEGRITY_MAX,
	LOCKDOWN_KCORE,
	LOCKDOWN_KPROBES,
	LOCKDOWN_BPF_READ,
	LOCKDOWN_PERF,
	LOCKDOWN_TRACEFS,
	LOCKDOWN_XMON_RW,
	LOCKDOWN_XFRM_SECRET,
	LOCKDOWN_CONFIDENTIALITY_MAX,
पूर्ण;

बाह्य स्थिर अक्षर *स्थिर lockकरोwn_reasons[LOCKDOWN_CONFIDENTIALITY_MAX+1];

/* These functions are in security/commoncap.c */
बाह्य पूर्णांक cap_capable(स्थिर काष्ठा cred *cred, काष्ठा user_namespace *ns,
		       पूर्णांक cap, अचिन्हित पूर्णांक opts);
बाह्य पूर्णांक cap_समय_रखो(स्थिर काष्ठा बारpec64 *ts, स्थिर काष्ठा समयzone *tz);
बाह्य पूर्णांक cap_ptrace_access_check(काष्ठा task_काष्ठा *child, अचिन्हित पूर्णांक mode);
बाह्य पूर्णांक cap_ptrace_traceme(काष्ठा task_काष्ठा *parent);
बाह्य पूर्णांक cap_capget(काष्ठा task_काष्ठा *target, kernel_cap_t *effective, kernel_cap_t *inheritable, kernel_cap_t *permitted);
बाह्य पूर्णांक cap_capset(काष्ठा cred *new, स्थिर काष्ठा cred *old,
		      स्थिर kernel_cap_t *effective,
		      स्थिर kernel_cap_t *inheritable,
		      स्थिर kernel_cap_t *permitted);
बाह्य पूर्णांक cap_bprm_creds_from_file(काष्ठा linux_binprm *bprm, काष्ठा file *file);
पूर्णांक cap_inode_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name,
		       स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);
पूर्णांक cap_inode_हटाओxattr(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, स्थिर अक्षर *name);
पूर्णांक cap_inode_need_समाप्तpriv(काष्ठा dentry *dentry);
पूर्णांक cap_inode_समाप्तpriv(काष्ठा user_namespace *mnt_userns,
		       काष्ठा dentry *dentry);
पूर्णांक cap_inode_माला_लोecurity(काष्ठा user_namespace *mnt_userns,
			  काष्ठा inode *inode, स्थिर अक्षर *name, व्योम **buffer,
			  bool alloc);
बाह्य पूर्णांक cap_mmap_addr(अचिन्हित दीर्घ addr);
बाह्य पूर्णांक cap_mmap_file(काष्ठा file *file, अचिन्हित दीर्घ reqprot,
			 अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags);
बाह्य पूर्णांक cap_task_fix_setuid(काष्ठा cred *new, स्थिर काष्ठा cred *old, पूर्णांक flags);
बाह्य पूर्णांक cap_task_prctl(पूर्णांक option, अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			  अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5);
बाह्य पूर्णांक cap_task_setscheduler(काष्ठा task_काष्ठा *p);
बाह्य पूर्णांक cap_task_setioprio(काष्ठा task_काष्ठा *p, पूर्णांक ioprio);
बाह्य पूर्णांक cap_task_setnice(काष्ठा task_काष्ठा *p, पूर्णांक nice);
बाह्य पूर्णांक cap_vm_enough_memory(काष्ठा mm_काष्ठा *mm, दीर्घ pages);

काष्ठा msghdr;
काष्ठा sk_buff;
काष्ठा sock;
काष्ठा sockaddr;
काष्ठा socket;
काष्ठा flowi_common;
काष्ठा dst_entry;
काष्ठा xfrm_selector;
काष्ठा xfrm_policy;
काष्ठा xfrm_state;
काष्ठा xfrm_user_sec_ctx;
काष्ठा seq_file;
काष्ठा sctp_endpoपूर्णांक;

#अगर_घोषित CONFIG_MMU
बाह्य अचिन्हित दीर्घ mmap_min_addr;
बाह्य अचिन्हित दीर्घ dac_mmap_min_addr;
#अन्यथा
#घोषणा mmap_min_addr		0UL
#घोषणा dac_mmap_min_addr	0UL
#पूर्ण_अगर

/*
 * Values used in the task_security_ops calls
 */
/* setuid or setgid, id0 == uid or gid */
#घोषणा LSM_SETID_ID	1

/* setreuid or setregid, id0 == real, id1 == eff */
#घोषणा LSM_SETID_RE	2

/* setresuid or setresgid, id0 == real, id1 == eff, uid2 == saved */
#घोषणा LSM_SETID_RES	4

/* setfsuid or setfsgid, id0 == fsuid or fsgid */
#घोषणा LSM_SETID_FS	8

/* Flags क्रम security_task_prlimit(). */
#घोषणा LSM_PRLIMIT_READ  1
#घोषणा LSM_PRLIMIT_WRITE 2

/* क्रमward declares to aव्योम warnings */
काष्ठा sched_param;
काष्ठा request_sock;

/* bprm->unsafe reasons */
#घोषणा LSM_UNSAFE_SHARE	1
#घोषणा LSM_UNSAFE_PTRACE	2
#घोषणा LSM_UNSAFE_NO_NEW_PRIVS	4

#अगर_घोषित CONFIG_MMU
बाह्य पूर्णांक mmap_min_addr_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
#पूर्ण_अगर

/* security_inode_init_security callback function to ग_लिखो xattrs */
प्रकार पूर्णांक (*initxattrs) (काष्ठा inode *inode,
			   स्थिर काष्ठा xattr *xattr_array, व्योम *fs_data);


/* Keep the kernel_load_data_id क्रमागत in sync with kernel_पढ़ो_file_id */
#घोषणा __data_id_क्रमागतअगरy(ENUM, dummy) LOADING_ ## ENUM,
#घोषणा __data_id_stringअगरy(dummy, str) #str,

क्रमागत kernel_load_data_id अणु
	__kernel_पढ़ो_file_id(__data_id_क्रमागतअगरy)
पूर्ण;

अटल स्थिर अक्षर * स्थिर kernel_load_data_str[] = अणु
	__kernel_पढ़ो_file_id(__data_id_stringअगरy)
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *kernel_load_data_id_str(क्रमागत kernel_load_data_id id)
अणु
	अगर ((अचिन्हित)id >= LOADING_MAX_ID)
		वापस kernel_load_data_str[LOADING_UNKNOWN];

	वापस kernel_load_data_str[id];
पूर्ण

#अगर_घोषित CONFIG_SECURITY

पूर्णांक call_blocking_lsm_notअगरier(क्रमागत lsm_event event, व्योम *data);
पूर्णांक रेजिस्टर_blocking_lsm_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_blocking_lsm_notअगरier(काष्ठा notअगरier_block *nb);

/* prototypes */
बाह्य पूर्णांक security_init(व्योम);
बाह्य पूर्णांक early_security_init(व्योम);

/* Security operations */
पूर्णांक security_binder_set_context_mgr(काष्ठा task_काष्ठा *mgr);
पूर्णांक security_binder_transaction(काष्ठा task_काष्ठा *from,
				काष्ठा task_काष्ठा *to);
पूर्णांक security_binder_transfer_binder(काष्ठा task_काष्ठा *from,
				    काष्ठा task_काष्ठा *to);
पूर्णांक security_binder_transfer_file(काष्ठा task_काष्ठा *from,
				  काष्ठा task_काष्ठा *to, काष्ठा file *file);
पूर्णांक security_ptrace_access_check(काष्ठा task_काष्ठा *child, अचिन्हित पूर्णांक mode);
पूर्णांक security_ptrace_traceme(काष्ठा task_काष्ठा *parent);
पूर्णांक security_capget(काष्ठा task_काष्ठा *target,
		    kernel_cap_t *effective,
		    kernel_cap_t *inheritable,
		    kernel_cap_t *permitted);
पूर्णांक security_capset(काष्ठा cred *new, स्थिर काष्ठा cred *old,
		    स्थिर kernel_cap_t *effective,
		    स्थिर kernel_cap_t *inheritable,
		    स्थिर kernel_cap_t *permitted);
पूर्णांक security_capable(स्थिर काष्ठा cred *cred,
		       काष्ठा user_namespace *ns,
		       पूर्णांक cap,
		       अचिन्हित पूर्णांक opts);
पूर्णांक security_quotactl(पूर्णांक cmds, पूर्णांक type, पूर्णांक id, काष्ठा super_block *sb);
पूर्णांक security_quota_on(काष्ठा dentry *dentry);
पूर्णांक security_syslog(पूर्णांक type);
पूर्णांक security_समय_रखो64(स्थिर काष्ठा बारpec64 *ts, स्थिर काष्ठा समयzone *tz);
पूर्णांक security_vm_enough_memory_mm(काष्ठा mm_काष्ठा *mm, दीर्घ pages);
पूर्णांक security_bprm_creds_क्रम_exec(काष्ठा linux_binprm *bprm);
पूर्णांक security_bprm_creds_from_file(काष्ठा linux_binprm *bprm, काष्ठा file *file);
पूर्णांक security_bprm_check(काष्ठा linux_binprm *bprm);
व्योम security_bprm_committing_creds(काष्ठा linux_binprm *bprm);
व्योम security_bprm_committed_creds(काष्ठा linux_binprm *bprm);
पूर्णांक security_fs_context_dup(काष्ठा fs_context *fc, काष्ठा fs_context *src_fc);
पूर्णांक security_fs_context_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param);
पूर्णांक security_sb_alloc(काष्ठा super_block *sb);
व्योम security_sb_delete(काष्ठा super_block *sb);
व्योम security_sb_मुक्त(काष्ठा super_block *sb);
व्योम security_मुक्त_mnt_opts(व्योम **mnt_opts);
पूर्णांक security_sb_eat_lsm_opts(अक्षर *options, व्योम **mnt_opts);
पूर्णांक security_sb_mnt_opts_compat(काष्ठा super_block *sb, व्योम *mnt_opts);
पूर्णांक security_sb_remount(काष्ठा super_block *sb, व्योम *mnt_opts);
पूर्णांक security_sb_kern_mount(काष्ठा super_block *sb);
पूर्णांक security_sb_show_options(काष्ठा seq_file *m, काष्ठा super_block *sb);
पूर्णांक security_sb_statfs(काष्ठा dentry *dentry);
पूर्णांक security_sb_mount(स्थिर अक्षर *dev_name, स्थिर काष्ठा path *path,
		      स्थिर अक्षर *type, अचिन्हित दीर्घ flags, व्योम *data);
पूर्णांक security_sb_umount(काष्ठा vfsmount *mnt, पूर्णांक flags);
पूर्णांक security_sb_pivotroot(स्थिर काष्ठा path *old_path, स्थिर काष्ठा path *new_path);
पूर्णांक security_sb_set_mnt_opts(काष्ठा super_block *sb,
				व्योम *mnt_opts,
				अचिन्हित दीर्घ kern_flags,
				अचिन्हित दीर्घ *set_kern_flags);
पूर्णांक security_sb_clone_mnt_opts(स्थिर काष्ठा super_block *oldsb,
				काष्ठा super_block *newsb,
				अचिन्हित दीर्घ kern_flags,
				अचिन्हित दीर्घ *set_kern_flags);
पूर्णांक security_add_mnt_opt(स्थिर अक्षर *option, स्थिर अक्षर *val,
				पूर्णांक len, व्योम **mnt_opts);
पूर्णांक security_move_mount(स्थिर काष्ठा path *from_path, स्थिर काष्ठा path *to_path);
पूर्णांक security_dentry_init_security(काष्ठा dentry *dentry, पूर्णांक mode,
					स्थिर काष्ठा qstr *name, व्योम **ctx,
					u32 *ctxlen);
पूर्णांक security_dentry_create_files_as(काष्ठा dentry *dentry, पूर्णांक mode,
					काष्ठा qstr *name,
					स्थिर काष्ठा cred *old,
					काष्ठा cred *new);
पूर्णांक security_path_notअगरy(स्थिर काष्ठा path *path, u64 mask,
					अचिन्हित पूर्णांक obj_type);
पूर्णांक security_inode_alloc(काष्ठा inode *inode);
व्योम security_inode_मुक्त(काष्ठा inode *inode);
पूर्णांक security_inode_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				 स्थिर काष्ठा qstr *qstr,
				 initxattrs initxattrs, व्योम *fs_data);
पूर्णांक security_inode_init_security_anon(काष्ठा inode *inode,
				      स्थिर काष्ठा qstr *name,
				      स्थिर काष्ठा inode *context_inode);
पूर्णांक security_old_inode_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				     स्थिर काष्ठा qstr *qstr, स्थिर अक्षर **name,
				     व्योम **value, माप_प्रकार *len);
पूर्णांक security_inode_create(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode);
पूर्णांक security_inode_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
			 काष्ठा dentry *new_dentry);
पूर्णांक security_inode_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry);
पूर्णांक security_inode_symlink(काष्ठा inode *dir, काष्ठा dentry *dentry,
			   स्थिर अक्षर *old_name);
पूर्णांक security_inode_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode);
पूर्णांक security_inode_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry);
पूर्णांक security_inode_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode, dev_t dev);
पूर्णांक security_inode_नाम(काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			  काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			  अचिन्हित पूर्णांक flags);
पूर्णांक security_inode_पढ़ोlink(काष्ठा dentry *dentry);
पूर्णांक security_inode_follow_link(काष्ठा dentry *dentry, काष्ठा inode *inode,
			       bool rcu);
पूर्णांक security_inode_permission(काष्ठा inode *inode, पूर्णांक mask);
पूर्णांक security_inode_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr);
पूर्णांक security_inode_getattr(स्थिर काष्ठा path *path);
पूर्णांक security_inode_setxattr(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry, स्थिर अक्षर *name,
			    स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);
व्योम security_inode_post_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name,
				  स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);
पूर्णांक security_inode_getxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name);
पूर्णांक security_inode_listxattr(काष्ठा dentry *dentry);
पूर्णांक security_inode_हटाओxattr(काष्ठा user_namespace *mnt_userns,
			       काष्ठा dentry *dentry, स्थिर अक्षर *name);
पूर्णांक security_inode_need_समाप्तpriv(काष्ठा dentry *dentry);
पूर्णांक security_inode_समाप्तpriv(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry);
पूर्णांक security_inode_माला_लोecurity(काष्ठा user_namespace *mnt_userns,
			       काष्ठा inode *inode, स्थिर अक्षर *name,
			       व्योम **buffer, bool alloc);
पूर्णांक security_inode_setsecurity(काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);
पूर्णांक security_inode_listsecurity(काष्ठा inode *inode, अक्षर *buffer, माप_प्रकार buffer_size);
व्योम security_inode_माला_लोecid(काष्ठा inode *inode, u32 *secid);
पूर्णांक security_inode_copy_up(काष्ठा dentry *src, काष्ठा cred **new);
पूर्णांक security_inode_copy_up_xattr(स्थिर अक्षर *name);
पूर्णांक security_kernfs_init_security(काष्ठा kernfs_node *kn_dir,
				  काष्ठा kernfs_node *kn);
पूर्णांक security_file_permission(काष्ठा file *file, पूर्णांक mask);
पूर्णांक security_file_alloc(काष्ठा file *file);
व्योम security_file_मुक्त(काष्ठा file *file);
पूर्णांक security_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक security_mmap_file(काष्ठा file *file, अचिन्हित दीर्घ prot,
			अचिन्हित दीर्घ flags);
पूर्णांक security_mmap_addr(अचिन्हित दीर्घ addr);
पूर्णांक security_file_mprotect(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ reqprot,
			   अचिन्हित दीर्घ prot);
पूर्णांक security_file_lock(काष्ठा file *file, अचिन्हित पूर्णांक cmd);
पूर्णांक security_file_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
व्योम security_file_set_fowner(काष्ठा file *file);
पूर्णांक security_file_send_sigiotask(काष्ठा task_काष्ठा *tsk,
				 काष्ठा fown_काष्ठा *fown, पूर्णांक sig);
पूर्णांक security_file_receive(काष्ठा file *file);
पूर्णांक security_file_खोलो(काष्ठा file *file);
पूर्णांक security_task_alloc(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ clone_flags);
व्योम security_task_मुक्त(काष्ठा task_काष्ठा *task);
पूर्णांक security_cred_alloc_blank(काष्ठा cred *cred, gfp_t gfp);
व्योम security_cred_मुक्त(काष्ठा cred *cred);
पूर्णांक security_prepare_creds(काष्ठा cred *new, स्थिर काष्ठा cred *old, gfp_t gfp);
व्योम security_transfer_creds(काष्ठा cred *new, स्थिर काष्ठा cred *old);
व्योम security_cred_माला_लोecid(स्थिर काष्ठा cred *c, u32 *secid);
पूर्णांक security_kernel_act_as(काष्ठा cred *new, u32 secid);
पूर्णांक security_kernel_create_files_as(काष्ठा cred *new, काष्ठा inode *inode);
पूर्णांक security_kernel_module_request(अक्षर *kmod_name);
पूर्णांक security_kernel_load_data(क्रमागत kernel_load_data_id id, bool contents);
पूर्णांक security_kernel_post_load_data(अक्षर *buf, loff_t size,
				   क्रमागत kernel_load_data_id id,
				   अक्षर *description);
पूर्णांक security_kernel_पढ़ो_file(काष्ठा file *file, क्रमागत kernel_पढ़ो_file_id id,
			      bool contents);
पूर्णांक security_kernel_post_पढ़ो_file(काष्ठा file *file, अक्षर *buf, loff_t size,
				   क्रमागत kernel_पढ़ो_file_id id);
पूर्णांक security_task_fix_setuid(काष्ठा cred *new, स्थिर काष्ठा cred *old,
			     पूर्णांक flags);
पूर्णांक security_task_fix_setgid(काष्ठा cred *new, स्थिर काष्ठा cred *old,
			     पूर्णांक flags);
पूर्णांक security_task_setpgid(काष्ठा task_काष्ठा *p, pid_t pgid);
पूर्णांक security_task_getpgid(काष्ठा task_काष्ठा *p);
पूर्णांक security_task_माला_लोid(काष्ठा task_काष्ठा *p);
व्योम security_task_माला_लोecid_subj(काष्ठा task_काष्ठा *p, u32 *secid);
व्योम security_task_माला_लोecid_obj(काष्ठा task_काष्ठा *p, u32 *secid);
पूर्णांक security_task_setnice(काष्ठा task_काष्ठा *p, पूर्णांक nice);
पूर्णांक security_task_setioprio(काष्ठा task_काष्ठा *p, पूर्णांक ioprio);
पूर्णांक security_task_getioprio(काष्ठा task_काष्ठा *p);
पूर्णांक security_task_prlimit(स्थिर काष्ठा cred *cred, स्थिर काष्ठा cred *tcred,
			  अचिन्हित पूर्णांक flags);
पूर्णांक security_task_setrlimit(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक resource,
		काष्ठा rlimit *new_rlim);
पूर्णांक security_task_setscheduler(काष्ठा task_काष्ठा *p);
पूर्णांक security_task_माला_लोcheduler(काष्ठा task_काष्ठा *p);
पूर्णांक security_task_movememory(काष्ठा task_काष्ठा *p);
पूर्णांक security_task_समाप्त(काष्ठा task_काष्ठा *p, काष्ठा kernel_siginfo *info,
			पूर्णांक sig, स्थिर काष्ठा cred *cred);
पूर्णांक security_task_prctl(पूर्णांक option, अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5);
व्योम security_task_to_inode(काष्ठा task_काष्ठा *p, काष्ठा inode *inode);
पूर्णांक security_ipc_permission(काष्ठा kern_ipc_perm *ipcp, लघु flag);
व्योम security_ipc_माला_लोecid(काष्ठा kern_ipc_perm *ipcp, u32 *secid);
पूर्णांक security_msg_msg_alloc(काष्ठा msg_msg *msg);
व्योम security_msg_msg_मुक्त(काष्ठा msg_msg *msg);
पूर्णांक security_msg_queue_alloc(काष्ठा kern_ipc_perm *msq);
व्योम security_msg_queue_मुक्त(काष्ठा kern_ipc_perm *msq);
पूर्णांक security_msg_queue_associate(काष्ठा kern_ipc_perm *msq, पूर्णांक msqflg);
पूर्णांक security_msg_queue_msgctl(काष्ठा kern_ipc_perm *msq, पूर्णांक cmd);
पूर्णांक security_msg_queue_msgsnd(काष्ठा kern_ipc_perm *msq,
			      काष्ठा msg_msg *msg, पूर्णांक msqflg);
पूर्णांक security_msg_queue_msgrcv(काष्ठा kern_ipc_perm *msq, काष्ठा msg_msg *msg,
			      काष्ठा task_काष्ठा *target, दीर्घ type, पूर्णांक mode);
पूर्णांक security_shm_alloc(काष्ठा kern_ipc_perm *shp);
व्योम security_shm_मुक्त(काष्ठा kern_ipc_perm *shp);
पूर्णांक security_shm_associate(काष्ठा kern_ipc_perm *shp, पूर्णांक shmflg);
पूर्णांक security_shm_shmctl(काष्ठा kern_ipc_perm *shp, पूर्णांक cmd);
पूर्णांक security_shm_shmat(काष्ठा kern_ipc_perm *shp, अक्षर __user *shmaddr, पूर्णांक shmflg);
पूर्णांक security_sem_alloc(काष्ठा kern_ipc_perm *sma);
व्योम security_sem_मुक्त(काष्ठा kern_ipc_perm *sma);
पूर्णांक security_sem_associate(काष्ठा kern_ipc_perm *sma, पूर्णांक semflg);
पूर्णांक security_sem_semctl(काष्ठा kern_ipc_perm *sma, पूर्णांक cmd);
पूर्णांक security_sem_semop(काष्ठा kern_ipc_perm *sma, काष्ठा sembuf *sops,
			अचिन्हित nsops, पूर्णांक alter);
व्योम security_d_instantiate(काष्ठा dentry *dentry, काष्ठा inode *inode);
पूर्णांक security_getprocattr(काष्ठा task_काष्ठा *p, स्थिर अक्षर *lsm, अक्षर *name,
			 अक्षर **value);
पूर्णांक security_setprocattr(स्थिर अक्षर *lsm, स्थिर अक्षर *name, व्योम *value,
			 माप_प्रकार size);
पूर्णांक security_netlink_send(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक security_ismaclabel(स्थिर अक्षर *name);
पूर्णांक security_secid_to_secctx(u32 secid, अक्षर **secdata, u32 *seclen);
पूर्णांक security_secctx_to_secid(स्थिर अक्षर *secdata, u32 seclen, u32 *secid);
व्योम security_release_secctx(अक्षर *secdata, u32 seclen);
व्योम security_inode_invalidate_secctx(काष्ठा inode *inode);
पूर्णांक security_inode_notअगरysecctx(काष्ठा inode *inode, व्योम *ctx, u32 ctxlen);
पूर्णांक security_inode_setsecctx(काष्ठा dentry *dentry, व्योम *ctx, u32 ctxlen);
पूर्णांक security_inode_माला_लोecctx(काष्ठा inode *inode, व्योम **ctx, u32 *ctxlen);
पूर्णांक security_locked_करोwn(क्रमागत lockकरोwn_reason what);
#अन्यथा /* CONFIG_SECURITY */

अटल अंतरभूत पूर्णांक call_blocking_lsm_notअगरier(क्रमागत lsm_event event, व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक रेजिस्टर_blocking_lsm_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत  पूर्णांक unरेजिस्टर_blocking_lsm_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_मुक्त_mnt_opts(व्योम **mnt_opts)
अणु
पूर्ण

/*
 * This is the शेष capabilities functionality.  Most of these functions
 * are just stubbed out, but a few must call the proper capable code.
 */

अटल अंतरभूत पूर्णांक security_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक early_security_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_binder_set_context_mgr(काष्ठा task_काष्ठा *mgr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_binder_transaction(काष्ठा task_काष्ठा *from,
					      काष्ठा task_काष्ठा *to)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_binder_transfer_binder(काष्ठा task_काष्ठा *from,
						  काष्ठा task_काष्ठा *to)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_binder_transfer_file(काष्ठा task_काष्ठा *from,
						काष्ठा task_काष्ठा *to,
						काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_ptrace_access_check(काष्ठा task_काष्ठा *child,
					     अचिन्हित पूर्णांक mode)
अणु
	वापस cap_ptrace_access_check(child, mode);
पूर्ण

अटल अंतरभूत पूर्णांक security_ptrace_traceme(काष्ठा task_काष्ठा *parent)
अणु
	वापस cap_ptrace_traceme(parent);
पूर्ण

अटल अंतरभूत पूर्णांक security_capget(काष्ठा task_काष्ठा *target,
				   kernel_cap_t *effective,
				   kernel_cap_t *inheritable,
				   kernel_cap_t *permitted)
अणु
	वापस cap_capget(target, effective, inheritable, permitted);
पूर्ण

अटल अंतरभूत पूर्णांक security_capset(काष्ठा cred *new,
				   स्थिर काष्ठा cred *old,
				   स्थिर kernel_cap_t *effective,
				   स्थिर kernel_cap_t *inheritable,
				   स्थिर kernel_cap_t *permitted)
अणु
	वापस cap_capset(new, old, effective, inheritable, permitted);
पूर्ण

अटल अंतरभूत पूर्णांक security_capable(स्थिर काष्ठा cred *cred,
				   काष्ठा user_namespace *ns,
				   पूर्णांक cap,
				   अचिन्हित पूर्णांक opts)
अणु
	वापस cap_capable(cred, ns, cap, opts);
पूर्ण

अटल अंतरभूत पूर्णांक security_quotactl(पूर्णांक cmds, पूर्णांक type, पूर्णांक id,
				     काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_quota_on(काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_syslog(पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_समय_रखो64(स्थिर काष्ठा बारpec64 *ts,
				     स्थिर काष्ठा समयzone *tz)
अणु
	वापस cap_समय_रखो(ts, tz);
पूर्ण

अटल अंतरभूत पूर्णांक security_vm_enough_memory_mm(काष्ठा mm_काष्ठा *mm, दीर्घ pages)
अणु
	वापस __vm_enough_memory(mm, pages, cap_vm_enough_memory(mm, pages));
पूर्ण

अटल अंतरभूत पूर्णांक security_bprm_creds_क्रम_exec(काष्ठा linux_binprm *bprm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_bprm_creds_from_file(काष्ठा linux_binprm *bprm,
						काष्ठा file *file)
अणु
	वापस cap_bprm_creds_from_file(bprm, file);
पूर्ण

अटल अंतरभूत पूर्णांक security_bprm_check(काष्ठा linux_binprm *bprm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_bprm_committing_creds(काष्ठा linux_binprm *bprm)
अणु
पूर्ण

अटल अंतरभूत व्योम security_bprm_committed_creds(काष्ठा linux_binprm *bprm)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_fs_context_dup(काष्ठा fs_context *fc,
					  काष्ठा fs_context *src_fc)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक security_fs_context_parse_param(काष्ठा fs_context *fc,
						  काष्ठा fs_parameter *param)
अणु
	वापस -ENOPARAM;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_alloc(काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_sb_delete(काष्ठा super_block *sb)
अणु पूर्ण

अटल अंतरभूत व्योम security_sb_मुक्त(काष्ठा super_block *sb)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_sb_eat_lsm_opts(अक्षर *options,
					   व्योम **mnt_opts)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_remount(काष्ठा super_block *sb,
				      व्योम *mnt_opts)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_mnt_opts_compat(काष्ठा super_block *sb,
					      व्योम *mnt_opts)
अणु
	वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक security_sb_kern_mount(काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_show_options(काष्ठा seq_file *m,
					   काष्ठा super_block *sb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_statfs(काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_mount(स्थिर अक्षर *dev_name, स्थिर काष्ठा path *path,
				    स्थिर अक्षर *type, अचिन्हित दीर्घ flags,
				    व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_umount(काष्ठा vfsmount *mnt, पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_pivotroot(स्थिर काष्ठा path *old_path,
					स्थिर काष्ठा path *new_path)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_set_mnt_opts(काष्ठा super_block *sb,
					   व्योम *mnt_opts,
					   अचिन्हित दीर्घ kern_flags,
					   अचिन्हित दीर्घ *set_kern_flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sb_clone_mnt_opts(स्थिर काष्ठा super_block *oldsb,
					      काष्ठा super_block *newsb,
					      अचिन्हित दीर्घ kern_flags,
					      अचिन्हित दीर्घ *set_kern_flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_add_mnt_opt(स्थिर अक्षर *option, स्थिर अक्षर *val,
					पूर्णांक len, व्योम **mnt_opts)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_move_mount(स्थिर काष्ठा path *from_path,
				      स्थिर काष्ठा path *to_path)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_notअगरy(स्थिर काष्ठा path *path, u64 mask,
				अचिन्हित पूर्णांक obj_type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_alloc(काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_inode_मुक्त(काष्ठा inode *inode)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_dentry_init_security(काष्ठा dentry *dentry,
						 पूर्णांक mode,
						 स्थिर काष्ठा qstr *name,
						 व्योम **ctx,
						 u32 *ctxlen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक security_dentry_create_files_as(काष्ठा dentry *dentry,
						  पूर्णांक mode, काष्ठा qstr *name,
						  स्थिर काष्ठा cred *old,
						  काष्ठा cred *new)
अणु
	वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक security_inode_init_security(काष्ठा inode *inode,
						काष्ठा inode *dir,
						स्थिर काष्ठा qstr *qstr,
						स्थिर initxattrs xattrs,
						व्योम *fs_data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_init_security_anon(काष्ठा inode *inode,
						    स्थिर काष्ठा qstr *name,
						    स्थिर काष्ठा inode *context_inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_old_inode_init_security(काष्ठा inode *inode,
						   काष्ठा inode *dir,
						   स्थिर काष्ठा qstr *qstr,
						   स्थिर अक्षर **name,
						   व्योम **value, माप_प्रकार *len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_create(काष्ठा inode *dir,
					 काष्ठा dentry *dentry,
					 umode_t mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_link(काष्ठा dentry *old_dentry,
				       काष्ठा inode *dir,
				       काष्ठा dentry *new_dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_unlink(काष्ठा inode *dir,
					 काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_symlink(काष्ठा inode *dir,
					  काष्ठा dentry *dentry,
					  स्थिर अक्षर *old_name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_सूची_गढ़ो(काष्ठा inode *dir,
					काष्ठा dentry *dentry,
					पूर्णांक mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_सूची_हटाओ(काष्ठा inode *dir,
					काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_mknod(काष्ठा inode *dir,
					काष्ठा dentry *dentry,
					पूर्णांक mode, dev_t dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_नाम(काष्ठा inode *old_dir,
					 काष्ठा dentry *old_dentry,
					 काष्ठा inode *new_dir,
					 काष्ठा dentry *new_dentry,
					 अचिन्हित पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_पढ़ोlink(काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_follow_link(काष्ठा dentry *dentry,
					     काष्ठा inode *inode,
					     bool rcu)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_permission(काष्ठा inode *inode, पूर्णांक mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_setattr(काष्ठा dentry *dentry,
					  काष्ठा iattr *attr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_getattr(स्थिर काष्ठा path *path)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_setxattr(काष्ठा user_namespace *mnt_userns,
		काष्ठा dentry *dentry, स्थिर अक्षर *name, स्थिर व्योम *value,
		माप_प्रकार size, पूर्णांक flags)
अणु
	वापस cap_inode_setxattr(dentry, name, value, size, flags);
पूर्ण

अटल अंतरभूत व्योम security_inode_post_setxattr(काष्ठा dentry *dentry,
		स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_inode_getxattr(काष्ठा dentry *dentry,
			स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_listxattr(काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_हटाओxattr(काष्ठा user_namespace *mnt_userns,
					     काष्ठा dentry *dentry,
					     स्थिर अक्षर *name)
अणु
	वापस cap_inode_हटाओxattr(mnt_userns, dentry, name);
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_need_समाप्तpriv(काष्ठा dentry *dentry)
अणु
	वापस cap_inode_need_समाप्तpriv(dentry);
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_समाप्तpriv(काष्ठा user_namespace *mnt_userns,
					  काष्ठा dentry *dentry)
अणु
	वापस cap_inode_समाप्तpriv(mnt_userns, dentry);
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_माला_लोecurity(काष्ठा user_namespace *mnt_userns,
					     काष्ठा inode *inode,
					     स्थिर अक्षर *name, व्योम **buffer,
					     bool alloc)
अणु
	वापस cap_inode_माला_लोecurity(mnt_userns, inode, name, buffer, alloc);
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_setsecurity(काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_listsecurity(काष्ठा inode *inode, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_inode_माला_लोecid(काष्ठा inode *inode, u32 *secid)
अणु
	*secid = 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_copy_up(काष्ठा dentry *src, काष्ठा cred **new)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_kernfs_init_security(काष्ठा kernfs_node *kn_dir,
						काष्ठा kernfs_node *kn)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_copy_up_xattr(स्थिर अक्षर *name)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक security_file_permission(काष्ठा file *file, पूर्णांक mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_file_alloc(काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_file_मुक्त(काष्ठा file *file)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ arg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_mmap_file(काष्ठा file *file, अचिन्हित दीर्घ prot,
				     अचिन्हित दीर्घ flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_mmap_addr(अचिन्हित दीर्घ addr)
अणु
	वापस cap_mmap_addr(addr);
पूर्ण

अटल अंतरभूत पूर्णांक security_file_mprotect(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ reqprot,
					 अचिन्हित दीर्घ prot)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_file_lock(काष्ठा file *file, अचिन्हित पूर्णांक cmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_file_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ arg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_file_set_fowner(काष्ठा file *file)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक security_file_send_sigiotask(काष्ठा task_काष्ठा *tsk,
					       काष्ठा fown_काष्ठा *fown,
					       पूर्णांक sig)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_file_receive(काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_file_खोलो(काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_alloc(काष्ठा task_काष्ठा *task,
				      अचिन्हित दीर्घ clone_flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_task_मुक्त(काष्ठा task_काष्ठा *task)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_cred_alloc_blank(काष्ठा cred *cred, gfp_t gfp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_cred_मुक्त(काष्ठा cred *cred)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_prepare_creds(काष्ठा cred *new,
					 स्थिर काष्ठा cred *old,
					 gfp_t gfp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_transfer_creds(काष्ठा cred *new,
					   स्थिर काष्ठा cred *old)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_kernel_act_as(काष्ठा cred *cred, u32 secid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_kernel_create_files_as(काष्ठा cred *cred,
						  काष्ठा inode *inode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_kernel_module_request(अक्षर *kmod_name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_kernel_load_data(क्रमागत kernel_load_data_id id, bool contents)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_kernel_post_load_data(अक्षर *buf, loff_t size,
						 क्रमागत kernel_load_data_id id,
						 अक्षर *description)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_kernel_पढ़ो_file(काष्ठा file *file,
					    क्रमागत kernel_पढ़ो_file_id id,
					    bool contents)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_kernel_post_पढ़ो_file(काष्ठा file *file,
						 अक्षर *buf, loff_t size,
						 क्रमागत kernel_पढ़ो_file_id id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_fix_setuid(काष्ठा cred *new,
					   स्थिर काष्ठा cred *old,
					   पूर्णांक flags)
अणु
	वापस cap_task_fix_setuid(new, old, flags);
पूर्ण

अटल अंतरभूत पूर्णांक security_task_fix_setgid(काष्ठा cred *new,
					   स्थिर काष्ठा cred *old,
					   पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_setpgid(काष्ठा task_काष्ठा *p, pid_t pgid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_getpgid(काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_माला_लोid(काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_task_माला_लोecid_subj(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	*secid = 0;
पूर्ण

अटल अंतरभूत व्योम security_task_माला_लोecid_obj(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	*secid = 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_setnice(काष्ठा task_काष्ठा *p, पूर्णांक nice)
अणु
	वापस cap_task_setnice(p, nice);
पूर्ण

अटल अंतरभूत पूर्णांक security_task_setioprio(काष्ठा task_काष्ठा *p, पूर्णांक ioprio)
अणु
	वापस cap_task_setioprio(p, ioprio);
पूर्ण

अटल अंतरभूत पूर्णांक security_task_getioprio(काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_prlimit(स्थिर काष्ठा cred *cred,
					स्थिर काष्ठा cred *tcred,
					अचिन्हित पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_setrlimit(काष्ठा task_काष्ठा *p,
					  अचिन्हित पूर्णांक resource,
					  काष्ठा rlimit *new_rlim)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_setscheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस cap_task_setscheduler(p);
पूर्ण

अटल अंतरभूत पूर्णांक security_task_माला_लोcheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_movememory(काष्ठा task_काष्ठा *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_समाप्त(काष्ठा task_काष्ठा *p,
				     काष्ठा kernel_siginfo *info, पूर्णांक sig,
				     स्थिर काष्ठा cred *cred)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_task_prctl(पूर्णांक option, अचिन्हित दीर्घ arg2,
				      अचिन्हित दीर्घ arg3,
				      अचिन्हित दीर्घ arg4,
				      अचिन्हित दीर्घ arg5)
अणु
	वापस cap_task_prctl(option, arg2, arg3, arg4, arg5);
पूर्ण

अटल अंतरभूत व्योम security_task_to_inode(काष्ठा task_काष्ठा *p, काष्ठा inode *inode)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_ipc_permission(काष्ठा kern_ipc_perm *ipcp,
					  लघु flag)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_ipc_माला_लोecid(काष्ठा kern_ipc_perm *ipcp, u32 *secid)
अणु
	*secid = 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_msg_msg_alloc(काष्ठा msg_msg *msg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_msg_msg_मुक्त(काष्ठा msg_msg *msg)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_msg_queue_alloc(काष्ठा kern_ipc_perm *msq)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_msg_queue_मुक्त(काष्ठा kern_ipc_perm *msq)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_msg_queue_associate(काष्ठा kern_ipc_perm *msq,
					       पूर्णांक msqflg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_msg_queue_msgctl(काष्ठा kern_ipc_perm *msq, पूर्णांक cmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_msg_queue_msgsnd(काष्ठा kern_ipc_perm *msq,
					    काष्ठा msg_msg *msg, पूर्णांक msqflg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_msg_queue_msgrcv(काष्ठा kern_ipc_perm *msq,
					    काष्ठा msg_msg *msg,
					    काष्ठा task_काष्ठा *target,
					    दीर्घ type, पूर्णांक mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_shm_alloc(काष्ठा kern_ipc_perm *shp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_shm_मुक्त(काष्ठा kern_ipc_perm *shp)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_shm_associate(काष्ठा kern_ipc_perm *shp,
					 पूर्णांक shmflg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_shm_shmctl(काष्ठा kern_ipc_perm *shp, पूर्णांक cmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_shm_shmat(काष्ठा kern_ipc_perm *shp,
				     अक्षर __user *shmaddr, पूर्णांक shmflg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sem_alloc(काष्ठा kern_ipc_perm *sma)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_sem_मुक्त(काष्ठा kern_ipc_perm *sma)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_sem_associate(काष्ठा kern_ipc_perm *sma, पूर्णांक semflg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sem_semctl(काष्ठा kern_ipc_perm *sma, पूर्णांक cmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sem_semop(काष्ठा kern_ipc_perm *sma,
				     काष्ठा sembuf *sops, अचिन्हित nsops,
				     पूर्णांक alter)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_d_instantiate(काष्ठा dentry *dentry,
					  काष्ठा inode *inode)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_getprocattr(काष्ठा task_काष्ठा *p, स्थिर अक्षर *lsm,
				       अक्षर *name, अक्षर **value)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक security_setprocattr(स्थिर अक्षर *lsm, अक्षर *name,
				       व्योम *value, माप_प्रकार size)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक security_netlink_send(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_ismaclabel(स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_secid_to_secctx(u32 secid, अक्षर **secdata, u32 *seclen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक security_secctx_to_secid(स्थिर अक्षर *secdata,
					   u32 seclen,
					   u32 *secid)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम security_release_secctx(अक्षर *secdata, u32 seclen)
अणु
पूर्ण

अटल अंतरभूत व्योम security_inode_invalidate_secctx(काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_inode_notअगरysecctx(काष्ठा inode *inode, व्योम *ctx, u32 ctxlen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक security_inode_setsecctx(काष्ठा dentry *dentry, व्योम *ctx, u32 ctxlen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक security_inode_माला_लोecctx(काष्ठा inode *inode, व्योम **ctx, u32 *ctxlen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक security_locked_करोwn(क्रमागत lockकरोwn_reason what)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_SECURITY */

#अगर defined(CONFIG_SECURITY) && defined(CONFIG_WATCH_QUEUE)
पूर्णांक security_post_notअगरication(स्थिर काष्ठा cred *w_cred,
			       स्थिर काष्ठा cred *cred,
			       काष्ठा watch_notअगरication *n);
#अन्यथा
अटल अंतरभूत पूर्णांक security_post_notअगरication(स्थिर काष्ठा cred *w_cred,
					     स्थिर काष्ठा cred *cred,
					     काष्ठा watch_notअगरication *n)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SECURITY) && defined(CONFIG_KEY_NOTIFICATIONS)
पूर्णांक security_watch_key(काष्ठा key *key);
#अन्यथा
अटल अंतरभूत पूर्णांक security_watch_key(काष्ठा key *key)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_NETWORK

पूर्णांक security_unix_stream_connect(काष्ठा sock *sock, काष्ठा sock *other, काष्ठा sock *newsk);
पूर्णांक security_unix_may_send(काष्ठा socket *sock,  काष्ठा socket *other);
पूर्णांक security_socket_create(पूर्णांक family, पूर्णांक type, पूर्णांक protocol, पूर्णांक kern);
पूर्णांक security_socket_post_create(काष्ठा socket *sock, पूर्णांक family,
				पूर्णांक type, पूर्णांक protocol, पूर्णांक kern);
पूर्णांक security_socket_socketpair(काष्ठा socket *socka, काष्ठा socket *sockb);
पूर्णांक security_socket_bind(काष्ठा socket *sock, काष्ठा sockaddr *address, पूर्णांक addrlen);
पूर्णांक security_socket_connect(काष्ठा socket *sock, काष्ठा sockaddr *address, पूर्णांक addrlen);
पूर्णांक security_socket_listen(काष्ठा socket *sock, पूर्णांक backlog);
पूर्णांक security_socket_accept(काष्ठा socket *sock, काष्ठा socket *newsock);
पूर्णांक security_socket_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक size);
पूर्णांक security_socket_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    पूर्णांक size, पूर्णांक flags);
पूर्णांक security_socket_माला_लोockname(काष्ठा socket *sock);
पूर्णांक security_socket_getpeername(काष्ठा socket *sock);
पूर्णांक security_socket_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname);
पूर्णांक security_socket_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname);
पूर्णांक security_socket_shutकरोwn(काष्ठा socket *sock, पूर्णांक how);
पूर्णांक security_sock_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक security_socket_getpeersec_stream(काष्ठा socket *sock, अक्षर __user *optval,
				      पूर्णांक __user *optlen, अचिन्हित len);
पूर्णांक security_socket_getpeersec_dgram(काष्ठा socket *sock, काष्ठा sk_buff *skb, u32 *secid);
पूर्णांक security_sk_alloc(काष्ठा sock *sk, पूर्णांक family, gfp_t priority);
व्योम security_sk_मुक्त(काष्ठा sock *sk);
व्योम security_sk_clone(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk);
व्योम security_sk_classअगरy_flow(काष्ठा sock *sk, काष्ठा flowi_common *flic);
व्योम security_req_classअगरy_flow(स्थिर काष्ठा request_sock *req,
				काष्ठा flowi_common *flic);
व्योम security_sock_graft(काष्ठा sock*sk, काष्ठा socket *parent);
पूर्णांक security_inet_conn_request(स्थिर काष्ठा sock *sk,
			काष्ठा sk_buff *skb, काष्ठा request_sock *req);
व्योम security_inet_csk_clone(काष्ठा sock *newsk,
			स्थिर काष्ठा request_sock *req);
व्योम security_inet_conn_established(काष्ठा sock *sk,
			काष्ठा sk_buff *skb);
पूर्णांक security_secmark_relabel_packet(u32 secid);
व्योम security_secmark_refcount_inc(व्योम);
व्योम security_secmark_refcount_dec(व्योम);
पूर्णांक security_tun_dev_alloc_security(व्योम **security);
व्योम security_tun_dev_मुक्त_security(व्योम *security);
पूर्णांक security_tun_dev_create(व्योम);
पूर्णांक security_tun_dev_attach_queue(व्योम *security);
पूर्णांक security_tun_dev_attach(काष्ठा sock *sk, व्योम *security);
पूर्णांक security_tun_dev_खोलो(व्योम *security);
पूर्णांक security_sctp_assoc_request(काष्ठा sctp_endpoपूर्णांक *ep, काष्ठा sk_buff *skb);
पूर्णांक security_sctp_bind_connect(काष्ठा sock *sk, पूर्णांक optname,
			       काष्ठा sockaddr *address, पूर्णांक addrlen);
व्योम security_sctp_sk_clone(काष्ठा sctp_endpoपूर्णांक *ep, काष्ठा sock *sk,
			    काष्ठा sock *newsk);

#अन्यथा	/* CONFIG_SECURITY_NETWORK */
अटल अंतरभूत पूर्णांक security_unix_stream_connect(काष्ठा sock *sock,
					       काष्ठा sock *other,
					       काष्ठा sock *newsk)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_unix_may_send(काष्ठा socket *sock,
					 काष्ठा socket *other)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_create(पूर्णांक family, पूर्णांक type,
					 पूर्णांक protocol, पूर्णांक kern)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_post_create(काष्ठा socket *sock,
					      पूर्णांक family,
					      पूर्णांक type,
					      पूर्णांक protocol, पूर्णांक kern)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_socketpair(काष्ठा socket *socka,
					     काष्ठा socket *sockb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_bind(काष्ठा socket *sock,
				       काष्ठा sockaddr *address,
				       पूर्णांक addrlen)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_connect(काष्ठा socket *sock,
					  काष्ठा sockaddr *address,
					  पूर्णांक addrlen)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_accept(काष्ठा socket *sock,
					 काष्ठा socket *newsock)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_sendmsg(काष्ठा socket *sock,
					  काष्ठा msghdr *msg, पूर्णांक size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_recvmsg(काष्ठा socket *sock,
					  काष्ठा msghdr *msg, पूर्णांक size,
					  पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_माला_लोockname(काष्ठा socket *sock)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_getpeername(काष्ठा socket *sock)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_माला_लोockopt(काष्ठा socket *sock,
					     पूर्णांक level, पूर्णांक optname)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_setsockopt(काष्ठा socket *sock,
					     पूर्णांक level, पूर्णांक optname)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक security_sock_rcv_skb(काष्ठा sock *sk,
					काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_getpeersec_stream(काष्ठा socket *sock, अक्षर __user *optval,
						    पूर्णांक __user *optlen, अचिन्हित len)
अणु
	वापस -ENOPROTOOPT;
पूर्ण

अटल अंतरभूत पूर्णांक security_socket_getpeersec_dgram(काष्ठा socket *sock, काष्ठा sk_buff *skb, u32 *secid)
अणु
	वापस -ENOPROTOOPT;
पूर्ण

अटल अंतरभूत पूर्णांक security_sk_alloc(काष्ठा sock *sk, पूर्णांक family, gfp_t priority)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_sk_मुक्त(काष्ठा sock *sk)
अणु
पूर्ण

अटल अंतरभूत व्योम security_sk_clone(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
पूर्ण

अटल अंतरभूत व्योम security_sk_classअगरy_flow(काष्ठा sock *sk,
					     काष्ठा flowi_common *flic)
अणु
पूर्ण

अटल अंतरभूत व्योम security_req_classअगरy_flow(स्थिर काष्ठा request_sock *req,
					      काष्ठा flowi_common *flic)
अणु
पूर्ण

अटल अंतरभूत व्योम security_sock_graft(काष्ठा sock *sk, काष्ठा socket *parent)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_inet_conn_request(स्थिर काष्ठा sock *sk,
			काष्ठा sk_buff *skb, काष्ठा request_sock *req)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_inet_csk_clone(काष्ठा sock *newsk,
			स्थिर काष्ठा request_sock *req)
अणु
पूर्ण

अटल अंतरभूत व्योम security_inet_conn_established(काष्ठा sock *sk,
			काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_secmark_relabel_packet(u32 secid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_secmark_refcount_inc(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम security_secmark_refcount_dec(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_tun_dev_alloc_security(व्योम **security)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_tun_dev_मुक्त_security(व्योम *security)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_tun_dev_create(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_tun_dev_attach_queue(व्योम *security)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_tun_dev_attach(काष्ठा sock *sk, व्योम *security)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_tun_dev_खोलो(व्योम *security)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sctp_assoc_request(काष्ठा sctp_endpoपूर्णांक *ep,
					      काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_sctp_bind_connect(काष्ठा sock *sk, पूर्णांक optname,
					     काष्ठा sockaddr *address,
					     पूर्णांक addrlen)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_sctp_sk_clone(काष्ठा sctp_endpoपूर्णांक *ep,
					  काष्ठा sock *sk,
					  काष्ठा sock *newsk)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_SECURITY_NETWORK */

#अगर_घोषित CONFIG_SECURITY_INFINIBAND
पूर्णांक security_ib_pkey_access(व्योम *sec, u64 subnet_prefix, u16 pkey);
पूर्णांक security_ib_endport_manage_subnet(व्योम *sec, स्थिर अक्षर *name, u8 port_num);
पूर्णांक security_ib_alloc_security(व्योम **sec);
व्योम security_ib_मुक्त_security(व्योम *sec);
#अन्यथा	/* CONFIG_SECURITY_INFINIBAND */
अटल अंतरभूत पूर्णांक security_ib_pkey_access(व्योम *sec, u64 subnet_prefix, u16 pkey)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_ib_endport_manage_subnet(व्योम *sec, स्थिर अक्षर *dev_name, u8 port_num)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_ib_alloc_security(व्योम **sec)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_ib_मुक्त_security(व्योम *sec)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_SECURITY_INFINIBAND */

#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM

पूर्णांक security_xfrm_policy_alloc(काष्ठा xfrm_sec_ctx **ctxp,
			       काष्ठा xfrm_user_sec_ctx *sec_ctx, gfp_t gfp);
पूर्णांक security_xfrm_policy_clone(काष्ठा xfrm_sec_ctx *old_ctx, काष्ठा xfrm_sec_ctx **new_ctxp);
व्योम security_xfrm_policy_मुक्त(काष्ठा xfrm_sec_ctx *ctx);
पूर्णांक security_xfrm_policy_delete(काष्ठा xfrm_sec_ctx *ctx);
पूर्णांक security_xfrm_state_alloc(काष्ठा xfrm_state *x, काष्ठा xfrm_user_sec_ctx *sec_ctx);
पूर्णांक security_xfrm_state_alloc_acquire(काष्ठा xfrm_state *x,
				      काष्ठा xfrm_sec_ctx *polsec, u32 secid);
पूर्णांक security_xfrm_state_delete(काष्ठा xfrm_state *x);
व्योम security_xfrm_state_मुक्त(काष्ठा xfrm_state *x);
पूर्णांक security_xfrm_policy_lookup(काष्ठा xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir);
पूर्णांक security_xfrm_state_pol_flow_match(काष्ठा xfrm_state *x,
				       काष्ठा xfrm_policy *xp,
				       स्थिर काष्ठा flowi_common *flic);
पूर्णांक security_xfrm_decode_session(काष्ठा sk_buff *skb, u32 *secid);
व्योम security_skb_classअगरy_flow(काष्ठा sk_buff *skb, काष्ठा flowi_common *flic);

#अन्यथा	/* CONFIG_SECURITY_NETWORK_XFRM */

अटल अंतरभूत पूर्णांक security_xfrm_policy_alloc(काष्ठा xfrm_sec_ctx **ctxp,
					     काष्ठा xfrm_user_sec_ctx *sec_ctx,
					     gfp_t gfp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_xfrm_policy_clone(काष्ठा xfrm_sec_ctx *old, काष्ठा xfrm_sec_ctx **new_ctxp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_xfrm_policy_मुक्त(काष्ठा xfrm_sec_ctx *ctx)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_xfrm_policy_delete(काष्ठा xfrm_sec_ctx *ctx)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_xfrm_state_alloc(काष्ठा xfrm_state *x,
					काष्ठा xfrm_user_sec_ctx *sec_ctx)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_xfrm_state_alloc_acquire(काष्ठा xfrm_state *x,
					काष्ठा xfrm_sec_ctx *polsec, u32 secid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_xfrm_state_मुक्त(काष्ठा xfrm_state *x)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_xfrm_state_delete(काष्ठा xfrm_state *x)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_xfrm_policy_lookup(काष्ठा xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_xfrm_state_pol_flow_match(काष्ठा xfrm_state *x,
						     काष्ठा xfrm_policy *xp,
						     स्थिर काष्ठा flowi_common *flic)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक security_xfrm_decode_session(काष्ठा sk_buff *skb, u32 *secid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_skb_classअगरy_flow(काष्ठा sk_buff *skb,
					      काष्ठा flowi_common *flic)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_SECURITY_NETWORK_XFRM */

#अगर_घोषित CONFIG_SECURITY_PATH
पूर्णांक security_path_unlink(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry);
पूर्णांक security_path_सूची_गढ़ो(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry, umode_t mode);
पूर्णांक security_path_सूची_हटाओ(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry);
पूर्णांक security_path_mknod(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry, umode_t mode,
			अचिन्हित पूर्णांक dev);
पूर्णांक security_path_truncate(स्थिर काष्ठा path *path);
पूर्णांक security_path_symlink(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
			  स्थिर अक्षर *old_name);
पूर्णांक security_path_link(काष्ठा dentry *old_dentry, स्थिर काष्ठा path *new_dir,
		       काष्ठा dentry *new_dentry);
पूर्णांक security_path_नाम(स्थिर काष्ठा path *old_dir, काष्ठा dentry *old_dentry,
			 स्थिर काष्ठा path *new_dir, काष्ठा dentry *new_dentry,
			 अचिन्हित पूर्णांक flags);
पूर्णांक security_path_chmod(स्थिर काष्ठा path *path, umode_t mode);
पूर्णांक security_path_chown(स्थिर काष्ठा path *path, kuid_t uid, kgid_t gid);
पूर्णांक security_path_chroot(स्थिर काष्ठा path *path);
#अन्यथा	/* CONFIG_SECURITY_PATH */
अटल अंतरभूत पूर्णांक security_path_unlink(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_सूची_गढ़ो(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
				      umode_t mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_सूची_हटाओ(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_mknod(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
				      umode_t mode, अचिन्हित पूर्णांक dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_truncate(स्थिर काष्ठा path *path)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_symlink(स्थिर काष्ठा path *dir, काष्ठा dentry *dentry,
					स्थिर अक्षर *old_name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_link(काष्ठा dentry *old_dentry,
				     स्थिर काष्ठा path *new_dir,
				     काष्ठा dentry *new_dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_नाम(स्थिर काष्ठा path *old_dir,
				       काष्ठा dentry *old_dentry,
				       स्थिर काष्ठा path *new_dir,
				       काष्ठा dentry *new_dentry,
				       अचिन्हित पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_chmod(स्थिर काष्ठा path *path, umode_t mode)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_chown(स्थिर काष्ठा path *path, kuid_t uid, kgid_t gid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_path_chroot(स्थिर काष्ठा path *path)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_SECURITY_PATH */

#अगर_घोषित CONFIG_KEYS
#अगर_घोषित CONFIG_SECURITY

पूर्णांक security_key_alloc(काष्ठा key *key, स्थिर काष्ठा cred *cred, अचिन्हित दीर्घ flags);
व्योम security_key_मुक्त(काष्ठा key *key);
पूर्णांक security_key_permission(key_ref_t key_ref, स्थिर काष्ठा cred *cred,
			    क्रमागत key_need_perm need_perm);
पूर्णांक security_key_माला_लोecurity(काष्ठा key *key, अक्षर **_buffer);

#अन्यथा

अटल अंतरभूत पूर्णांक security_key_alloc(काष्ठा key *key,
				     स्थिर काष्ठा cred *cred,
				     अचिन्हित दीर्घ flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_key_मुक्त(काष्ठा key *key)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_key_permission(key_ref_t key_ref,
					  स्थिर काष्ठा cred *cred,
					  क्रमागत key_need_perm need_perm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_key_माला_लोecurity(काष्ठा key *key, अक्षर **_buffer)
अणु
	*_buffer = शून्य;
	वापस 0;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_KEYS */

#अगर_घोषित CONFIG_AUDIT
#अगर_घोषित CONFIG_SECURITY
पूर्णांक security_audit_rule_init(u32 field, u32 op, अक्षर *rulestr, व्योम **lsmrule);
पूर्णांक security_audit_rule_known(काष्ठा audit_krule *krule);
पूर्णांक security_audit_rule_match(u32 secid, u32 field, u32 op, व्योम *lsmrule);
व्योम security_audit_rule_मुक्त(व्योम *lsmrule);

#अन्यथा

अटल अंतरभूत पूर्णांक security_audit_rule_init(u32 field, u32 op, अक्षर *rulestr,
					   व्योम **lsmrule)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_audit_rule_known(काष्ठा audit_krule *krule)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_audit_rule_match(u32 secid, u32 field, u32 op,
					    व्योम *lsmrule)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_audit_rule_मुक्त(व्योम *lsmrule)
अणु पूर्ण

#पूर्ण_अगर /* CONFIG_SECURITY */
#पूर्ण_अगर /* CONFIG_AUDIT */

#अगर_घोषित CONFIG_SECURITYFS

बाह्य काष्ठा dentry *securityfs_create_file(स्थिर अक्षर *name, umode_t mode,
					     काष्ठा dentry *parent, व्योम *data,
					     स्थिर काष्ठा file_operations *fops);
बाह्य काष्ठा dentry *securityfs_create_dir(स्थिर अक्षर *name, काष्ठा dentry *parent);
काष्ठा dentry *securityfs_create_symlink(स्थिर अक्षर *name,
					 काष्ठा dentry *parent,
					 स्थिर अक्षर *target,
					 स्थिर काष्ठा inode_operations *iops);
बाह्य व्योम securityfs_हटाओ(काष्ठा dentry *dentry);

#अन्यथा /* CONFIG_SECURITYFS */

अटल अंतरभूत काष्ठा dentry *securityfs_create_dir(स्थिर अक्षर *name,
						   काष्ठा dentry *parent)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा dentry *securityfs_create_file(स्थिर अक्षर *name,
						    umode_t mode,
						    काष्ठा dentry *parent,
						    व्योम *data,
						    स्थिर काष्ठा file_operations *fops)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा dentry *securityfs_create_symlink(स्थिर अक्षर *name,
					काष्ठा dentry *parent,
					स्थिर अक्षर *target,
					स्थिर काष्ठा inode_operations *iops)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम securityfs_हटाओ(काष्ठा dentry *dentry)
अणुपूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_BPF_SYSCALL
जोड़ bpf_attr;
काष्ठा bpf_map;
काष्ठा bpf_prog;
काष्ठा bpf_prog_aux;
#अगर_घोषित CONFIG_SECURITY
बाह्य पूर्णांक security_bpf(पूर्णांक cmd, जोड़ bpf_attr *attr, अचिन्हित पूर्णांक size);
बाह्य पूर्णांक security_bpf_map(काष्ठा bpf_map *map, भ_शेषe_t भ_शेषe);
बाह्य पूर्णांक security_bpf_prog(काष्ठा bpf_prog *prog);
बाह्य पूर्णांक security_bpf_map_alloc(काष्ठा bpf_map *map);
बाह्य व्योम security_bpf_map_मुक्त(काष्ठा bpf_map *map);
बाह्य पूर्णांक security_bpf_prog_alloc(काष्ठा bpf_prog_aux *aux);
बाह्य व्योम security_bpf_prog_मुक्त(काष्ठा bpf_prog_aux *aux);
#अन्यथा
अटल अंतरभूत पूर्णांक security_bpf(पूर्णांक cmd, जोड़ bpf_attr *attr,
					     अचिन्हित पूर्णांक size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_bpf_map(काष्ठा bpf_map *map, भ_शेषe_t भ_शेषe)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_bpf_prog(काष्ठा bpf_prog *prog)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_bpf_map_alloc(काष्ठा bpf_map *map)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_bpf_map_मुक्त(काष्ठा bpf_map *map)
अणु पूर्ण

अटल अंतरभूत पूर्णांक security_bpf_prog_alloc(काष्ठा bpf_prog_aux *aux)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_bpf_prog_मुक्त(काष्ठा bpf_prog_aux *aux)
अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SECURITY */
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */

#अगर_घोषित CONFIG_PERF_EVENTS
काष्ठा perf_event_attr;
काष्ठा perf_event;

#अगर_घोषित CONFIG_SECURITY
बाह्य पूर्णांक security_perf_event_खोलो(काष्ठा perf_event_attr *attr, पूर्णांक type);
बाह्य पूर्णांक security_perf_event_alloc(काष्ठा perf_event *event);
बाह्य व्योम security_perf_event_मुक्त(काष्ठा perf_event *event);
बाह्य पूर्णांक security_perf_event_पढ़ो(काष्ठा perf_event *event);
बाह्य पूर्णांक security_perf_event_ग_लिखो(काष्ठा perf_event *event);
#अन्यथा
अटल अंतरभूत पूर्णांक security_perf_event_खोलो(काष्ठा perf_event_attr *attr,
					   पूर्णांक type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_perf_event_alloc(काष्ठा perf_event *event)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम security_perf_event_मुक्त(काष्ठा perf_event *event)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक security_perf_event_पढ़ो(काष्ठा perf_event *event)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक security_perf_event_ग_लिखो(काष्ठा perf_event *event)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SECURITY */
#पूर्ण_अगर /* CONFIG_PERF_EVENTS */

#पूर्ण_अगर /* ! __LINUX_SECURITY_H */
